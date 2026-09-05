"""Ensure every formerly absent original qagame registration is represented."""
import csv
import re
from pathlib import Path

root = Path(__file__).resolve().parents[1]
source = (root / "src_2.60/game/g_nitmod_legacy_cvars.c").read_text(encoding="utf-8")
rows = list(csv.DictReader((root / "reference/original-cvar-inventory.csv").open(encoding="utf-8")))
registered = re.findall(r'\{\{0\},"([^"]+)","([^"]*)",(\d+)\}', source)
assert len(registered) == 142  # includes the recovered n_tankMountDelay runtime control
by_name = {}
for name, default, flags in registered:
    by_name.setdefault(name, []).append((default, int(flags)))
assert len(by_name) == 141
for row in rows:
    if row["module"] != "qagame" or row["name"] not in by_name:
        continue
    choices = by_name[row["name"]]
    if row["name"] == "mod_build":
        assert (row["default"], int(row["flags"])) in choices and ("wasm32", 68) in choices
    else:
        assert choices == [(row["default"], int(row["flags"]))], row["name"]
assert 'G_NITMOD_LegacyCvarInteger("g_teamChangeKills", 1)' in (root / "src_2.60/game/g_cmds.c").read_text()
active = (root / "src_2.60/game/g_active.c").read_text()
assert 'G_NITMOD_LegacyCvarInteger("g_noCharge", 0)' in active
assert 'G_NITMOD_LegacyCvarInteger("g_instantSpawn", 0)' in active
print("legacy cvar surface: ok")
