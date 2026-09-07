"""Read-only accounting; these counts are NOT functional completion estimates."""
import csv
import hashlib
import json
from collections import Counter, defaultdict
from pathlib import Path

root = Path(__file__).resolve().parents[1]
inventory = root / "reference/port_inventory.csv"
symbols = root / "reference/original_function_symbols.csv"
rows = list(csv.DictReader(inventory.open(encoding="utf-8-sig")))
elf = list(csv.DictReader(symbols.open(encoding="utf-8-sig")))
groups = defaultdict(list)
for row in rows:
    groups[(row["component"], row["source_file"], row["function"])].append(row)
for key, values in groups.items():
    if len({r["port_status"] for r in values}) != 1:
        raise SystemExit(f"Conflicting duplicate statuses: {key}")
unique = [values[0] for values in groups.values()]
report = {
    "meaning": "Inventory documentation coverage only; not feature, runtime or original-parity completion",
    "inventory_sha256": hashlib.sha256(inventory.read_bytes()).hexdigest(),
    "symbol_inventory_sha256": hashlib.sha256(symbols.read_bytes()).hexdigest(),
    "raw_rows": len(rows), "unique_entries": len(unique),
    "duplicates_removed": len(rows)-len(unique),
    "duplicate_keys": [key for key, values in groups.items() if len(values)>1],
    "modules": {},
}
for module in ("qagame", "cgame", "ui"):
    selected = [r for r in unique if r["component"] == module]
    counts = Counter(r["port_status"] for r in selected)
    total = len(selected)
    covered = sum(counts[s] for s in ("ported", "ported_partial", "partial"))
    artifact = root / "build/wasm" / (module + ".mp.wasm32.so")
    report["modules"][module] = {
        "entries": total,
        "status_counts": dict(counts),
        "marked_ported_percent": counts["ported"]*100/total,
        "partial_or_ported_percent": covered*100/total,
        "original_elf_function_symbols": sum(r["module"] == module+".mp.i386.so" for r in elf),
        "artifact_sha256": hashlib.sha256(artifact.read_bytes()).hexdigest(),
        "artifact_bytes": artifact.stat().st_size,
    }
recent = {"BG_CheckCharge", "jP_DoChargeCost", "MagicSink", "Weapon_Medic_Ext",
          "Weapon_MagicAmmo_Ext", "G_DropLimboHealth", "G_DropLimboAmmo", "SetWolfSpawnWeapons"}
report["recent_work_still_untriaged"] = [
    {key: r[key] for key in ("component", "source_file", "function", "port_status")}
    for r in unique if r["function"] in recent and r["port_status"] == "untriaged"
]
print(json.dumps(report, indent=2))
