"""Reproduce every static original registration row, without claiming parity."""
import csv
import importlib.util
from pathlib import Path
import sys

root = Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('inventory', root / 'tools/extract_cvar_inventory.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
rows = module.extract(root)
assert len(rows) == 749
with (root / 'reference/original-cvar-inventory.csv').open(newline='', encoding='utf-8') as stream:
    stored = list(csv.DictReader(stream))
assert stored == [{k: str(v) for k, v in row.items()} for row in rows]
record = next(r for r in rows if r['module'] == 'cgame' and r['name'] == 'cg_pmSounds')
assert (record['default'], record['flags']) == ('1', 1)
main = (root / 'src_2.60/cgame/cg_main.c').read_text()
assert '{ &cg_pmSounds, "cg_pmSounds", "1", CVAR_ARCHIVE }' in main
record = next(r for r in rows if r['module'] == 'cgame' and r['name'] == 'cg_shoveSounds')
assert (record['default'], record['flags']) == ('1', 1)
assert '{ &cg_shoveSounds, "cg_shoveSounds", "1", CVAR_ARCHIVE }' in main
record = next(r for r in rows if r['module'] == 'cgame' and r['name'] == 'cg_noGreetingSounds')
assert (record['default'], record['flags']) == ('0', 1)
assert '{ &cg_noGreetingSounds, "cg_noGreetingSounds", "0", CVAR_ARCHIVE }' in main
server = (root / 'src_2.60/game/g_main.c').read_text()
for name, default in [('g_doubleJump', '0'), ('g_DJHeight', '1.4'), ('g_spawnInvul', '3'),
                      ('g_healthCabinetTime', '10000'), ('g_ammoCabinetTime', '60000'),
                      ('team_maxLandmines', '10'), ('team_maxSoldiers', '-1'),
                      ('team_maxMedics', '-1'), ('team_maxEngineers', '-1'),
                      ('team_maxFieldops', '-1'), ('team_maxCovertops', '-1'),
                      ('g_dropHealth', '0'), ('g_dropAmmo', '0'),
                      ('n_medPackSinkDelay', '30000'), ('n_ammoPackSinkDelay', '30000'),
                      ('g_intermissionTime', '60'), ('g_intermissionReadyPercent', '100')]:
    record = next(r for r in rows if r['module'] == 'qagame' and r['name'] == name)
    assert (record['default'], record['flags'], record['track_change'], record['reset']) == (default, 0, 0, 0)
    assert ('{ &' + name + ', "' + name + '", "' + default + '", 0, 0, qfalse, qfalse }') in server
print('749 original static Cvar records reproduced; source mentions are not functional parity')
for relative in ['game/g_main.c', 'game/g_script.c', 'game/g_weapon.c',
                 'game/g_missile.c', 'botai/ai_dmgoal_mp.c']:
    text = (root / 'src_2.60' / relative).read_text()
    assert 'MAX_TEAM_LANDMINES' not in text, relative
    assert 'team_maxLandmines.integer' in text, relative
