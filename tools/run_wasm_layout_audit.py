"""Compile selected layout probes separately; not a complete ABI certification."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess


def parse(text):
    result = {}
    for line in text.splitlines():
        match = re.fullmatch(r"([^=]+)=(\d+(?:,\d+)?)", line)
        if not match or match[1] in result:
            raise ValueError("Invalid/duplicate layout row: " + line)
        result[match[1]] = [int(value) for value in match[2].split(",")]
    if result.get("void *.size") != [4]:
        raise ValueError("Expected wasm32 pointer size")
    return result


def compare(mod, engine):
    if mod.keys() != engine.keys():
        raise ValueError("Layout probes reported different keys")
    return [{"field": key, "mod": value, "engine": engine[key]}
            for key, value in mod.items() if value != engine[key]]


def run(root, legacy, runner=subprocess.run, locate=shutil.which):
    commands = {name: locate(name) for name in ("emcc", "node")}
    if not all(commands.values()):
        raise RuntimeError("Activate Emscripten and Node first")
    root, legacy = Path(root).resolve(), Path(legacy).resolve()
    build = root / "build/wasm-layout-audit"
    build.mkdir(parents=True, exist_ok=True)
    probe = root / "tests/wasm_layout_probe.c"
    layouts, sources, invocations = {}, {}, []
    for name, include in (("mod", root / "src_2.60/game"), ("engine", legacy / "src/qcommon")):
        header = include / "q_shared.h"
        sources[str(header)] = hashlib.sha256(header.read_bytes()).hexdigest()
        cgame_include = include.parent / "cgame"
        cgame_header = cgame_include / "cg_public.h"
        sources[str(cgame_header)] = hashlib.sha256(cgame_header.read_bytes()).hexdigest()
        output = build / (name + ".js")
        compile_args = [commands["emcc"], str(probe), "-I", str(include), "-I", str(cgame_include),
                        "-sENVIRONMENT=node", "-o", str(output)]
        runner(compile_args, cwd=root, check=True)
        execute_args = [commands["node"], str(output)]
        result = runner(execute_args, cwd=root, check=True, capture_output=True, text=True)
        layouts[name] = parse(result.stdout)
        invocations.extend([compile_args, execute_args])
    return {"schema_version": 2, "full_abi_verified": False,
            "probe_sha256": hashlib.sha256(probe.read_bytes()).hexdigest(),
            "inspected_header_sha256": sources, "commands": invocations, "layouts": layouts,
            "differences": compare(layouts["mod"], layouts["engine"])}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("legacy", type=Path)
    args = parser.parse_args()
    report = run(Path(__file__).resolve().parents[1], args.legacy)
    print(json.dumps(report, indent=2))
    raise SystemExit(1 if report["differences"] else 0)
