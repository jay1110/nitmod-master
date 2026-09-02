"""Strict source-enum comparison, not a compiled engine compatibility test."""
import argparse
import hashlib
import json
from pathlib import Path
import re


def uncomment(source):
    return re.sub(r"/\*.*?\*/|//[^\n]*", "", source, flags=re.S)


def parse_enum(source, typedef, constants=None):
    constants = constants or {}
    matches = re.findall(r"typedef\s+enum(?:\s+\w+)?\s*\{([^{}]*)\}\s*" +
                         re.escape(typedef) + r"\s*;", uncomment(source), re.S)
    if len(matches) != 1:
        raise ValueError("Expected exactly one enum: " + typedef)
    result, value = {}, -1
    for field in matches[0].split(","):
        if not field.strip():
            continue
        match = re.fullmatch(r"\s*([A-Za-z_]\w*)\s*(?:=\s*(\w+))?\s*", field)
        if not match:
            raise ValueError("Unsupported enum expression/directive: " + field.strip())
        name, explicit = match.groups()
        if name in result:
            raise ValueError("Duplicate enum name: " + name)
        if explicit is None:
            value += 1
        elif re.fullmatch(r"0[xX][0-9a-fA-F]+|0|[1-9][0-9]*", explicit):
            value = int(explicit, 16 if explicit.lower().startswith("0x") else 10)
        elif explicit in result or explicit in constants:
            value = result[explicit] if explicit in result else constants[explicit]
        else:
            raise ValueError("Unresolved enum value: " + explicit)
        result[name] = value
    return result


def compare(original, engine):
    return [{"name": name, "mod_number": value, "engine_number": engine.get(name),
             "status": "missing-engine-name" if name not in engine else
                       "same-number" if engine[name] == value else "different-number"}
            for name, value in original.items()]


def compare_exports(original, engine):
    """Include engine-only commands and numeric collisions in either direction."""
    rows = compare(original, engine)
    for name, value in engine.items():
        if name not in original:
            rows.append({"name": name, "mod_number": None, "engine_number": value,
                         "status": "missing-mod-name"})
    for row in rows:
        row["engine_names_at_mod_number"] = [name for name, value in engine.items()
                                              if value == row["mod_number"]]
        row["mod_names_at_engine_number"] = [name for name, value in original.items()
                                              if value == row["engine_number"]]
    return {"counts": {status: sum(row["status"] == status for row in rows)
                       for status in ("same-number", "different-number", "missing-engine-name", "missing-mod-name")},
            "entries": rows}


def audit(root, legacy):
    files = {}
    def read(path):
        data = path.read_bytes()
        files[str(path)] = hashlib.sha256(data).hexdigest()
        return data.decode("utf-8-sig")
    shared = uncomment(read(legacy / "src/qcommon/q_shared.h"))
    constants = {}
    for name in ("COM_TRAP_GETVALUE", "MOD_EXPORT_PADDING"):
        match = re.findall(r"^\s*#define\s+" + name + r"\s+(\d+)\s*$", shared, re.M)
        if len(match) != 1:
            raise ValueError("Expected one literal definition: " + name)
        constants[name] = int(match[0])
    modules = {}
    for folder, prefix, typedef in (("game", "g", "gameImport_t"),
                                   ("cgame", "cg", "cgameImport_t"),
                                   ("ui", "ui", "uiImport_t")):
        relative = folder + "/" + prefix + "_public.h"
        original_source = read(root / "src_2.60" / relative)
        engine_source = read(legacy / "src" / relative)
        original = parse_enum(original_source, typedef)
        engine = parse_enum(engine_source, typedef, constants)
        rows = compare(original, engine)
        modules[folder] = {"counts": {status: sum(row["status"] == status for row in rows)
                                     for status in ("same-number", "different-number", "missing-engine-name")},
                           "entries": rows}
        export_type = typedef.replace("Import_t", "Export_t")
        modules[folder]["exports"] = compare_exports(parse_enum(original_source, export_type),
                                                     parse_enum(engine_source, export_type, constants))
    return {"schema_version": 2, "runtime_verified": False, "source_sha256": files, "modules": modules}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("legacy", type=Path)
    args = parser.parse_args()
    print(json.dumps(audit(Path(__file__).resolve().parents[1], args.legacy.resolve()), indent=2))
