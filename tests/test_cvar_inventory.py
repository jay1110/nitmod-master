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
ui_main = (root / 'src_2.60/ui/ui_main.c').read_text()
assert '{ &ui_browserNitmodonly, "ui_browserNitmodonly", "1", CVAR_ARCHIVE }' in ui_main
for name, default in [('vote_allow_shuffleteams', '1'), ('vote_allow_shuffleteams_norestart', '1'),
                      ('vote_allow_swapteamsrestart', '1'), ('cg_hitSounds', '1'),
                      ('cg_goatSound', '3'), ('r_dynamicTextures', '0'),
                      ('cg_markDistance', '384'), ('cg_optimizePrediction', '1'),
                      ('cg_locations', '3'), ('cg_weapAltReloads', '0'),
                      ('cg_FTAutoSelect', '1'), ('cg_shoveSounds', '1')]:
    record = next(r for r in rows if r['module'] == 'ui' and r['name'] == name)
    assert (record['default'], record['flags']) == (default, 1)
    assert ('{ NULL, "' + name + '", "' + default + '", CVAR_ARCHIVE }') in ui_main
record = next(r for r in rows if r['module'] == 'ui' and r['name'] == 'g_mapScriptDirectory')
assert (record['default'], record['flags']) == ('', 0)
assert '{ NULL, "g_mapScriptDirectory", "", 0 }' in ui_main
for name, default in [('cg_countryflags', '1'), ('cg_optimizePrediction', '1'),
                      ('cg_locations', '3'), ('cg_logFile', 'client.log'),
                      ('cg_clientLog', '0'), ('cg_drawCam', '1'),
                      ('cg_locationMaxChars', '12'), ('cg_TDMScorePos', '0'),
                      ('cg_earlyTransition', '1')]:
    record = next(r for r in rows if r['module'] == 'cgame' and r['name'] == name)
    assert (record['default'], record['flags']) == (default, 1)
    assert ('{ &' + name + ', "' + name + '", "' + default + '", CVAR_ARCHIVE }') in main
for name, default in [('cg_numPopups', '6'), ('cg_popupFadeTime', '6000'), ('cg_HUDFlags', '4'),
                      ('cg_notificationTime', '8000'), ('cg_notificationFadeTime', '250'), ('cg_pmColor', '^7'),
                      ('cg_pingColors', '1'), ('cg_automapZoom', '5.159')]:
    record = next(r for r in rows if r['module'] == 'cgame' and r['name'] == name)
    assert (record['default'], record['flags']) == (default, 1)
    assert ('{ &' + name + ', "' + name + '", "' + default + '", CVAR_ARCHIVE }') in main
    assert ('{ NULL, "' + name + '", "' + default + '", CVAR_ARCHIVE }') in ui_main
for name, default in [('cg_tracers', '1'), ('cg_muzzleFlash', '1'),
                      ('cg_smokeparticles', '1'), ('cg_trailparticles', '1'),
                      ('cg_impactparticles', '1'), ('cg_drawPing', '0'), ('cg_drawTime', '1'),
                      ('cg_drawTimeSeconds', '0'), ('cg_drawspeed', '0'),
                      ('cg_speedunit', '0'), ('cg_speedinterval', '100'),
                      ('cg_HUDBackgroundColor', '.16 .2 .17'),
                      ('cg_HUDBorderColor', '.5  .5 .5'), ('cg_HUDAlpha', '0.8')]:
    for owner in ['cgame', 'ui']:
        record = next(r for r in rows if r['module'] == owner and r['name'] == name)
        assert (record['default'], record['flags']) == (default, 1)
    assert ('{ &' + name + ', "' + name + '", "' + default + '", CVAR_ARCHIVE }') in main
    assert ('{ NULL, "' + name + '", "' + default + '", CVAR_ARCHIVE }') in ui_main
assert 'CG_NitmodHud(y)' in (root / 'src_2.60/cgame/cg_draw.c').read_text()
assert '{ "resetmaxspeed", CG_NitmodResetMaxSpeed }' in (root / 'src_2.60/cgame/cg_consolecmds.c').read_text()
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
record = next(r for r in rows if r['module'] == 'qagame' and r['name'] == 'g_inactivityOptions')
assert (record['default'], record['flags'], record['track_change'], record['reset']) == ('0', 0, 1, 0)
assert '{ &g_inactivityOptions, "g_inactivityOptions", "0", 0, 0, qtrue, qfalse }' in server
for relative in ['game/g_main.c', 'game/g_script.c', 'game/g_weapon.c',
                 'game/g_missile.c', 'botai/ai_dmgoal_mp.c']:
    text = (root / 'src_2.60' / relative).read_text()
    assert 'MAX_TEAM_LANDMINES' not in text, relative
    assert 'team_maxLandmines.integer' in text, relative
