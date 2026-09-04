"""Check the bounded lifecycle integration, not original runtime parity."""
import pathlib
import re
import sys

root = pathlib.Path(sys.argv[1]).resolve()
client = (root / 'src_2.60/game/g_client.c').read_text()
main = (root / 'src_2.60/game/g_main.c').read_text()
cmds = (root / 'src_2.60/game/g_cmds.c').read_text()
setteam = cmds.split('qboolean SetTeam(', 1)[1].split('void StopFollowing', 1)[0]
assert re.search(r'if\( setweapons \) \{\s*G_NITMOD_RefreshTeamPopulation\(\);\s*'
                 r'G_SetClientWeapons\( ent, w1, w2, qfalse \);', setteam)
assert setteam.index('client->sess.sessionTeam = team;') < setteam.index('G_NITMOD_RefreshTeamPopulation();')
assert setteam.index('G_NITMOD_RefreshTeamPopulation();') < setteam.index('ClientBegin( clientNum );')
assert re.search(r'if\( !SetTeam\( ent, s, qfalse, w, w2, qtrue \) \) \{\s*'
                 r'G_NITMOD_RefreshTeamPopulation\(\);\s*'
                 r'G_SetClientWeapons\( ent, w, w2, qtrue \);', cmds)
assert len(re.findall(r'CalculateRanks\(\);\s*G_NITMOD_RefreshTeamPopulation\(\);', client)) == 3
assert client.count('G_NITMOD_RefreshTeamPopulation();') == 3
init = main.split('void G_InitGame( int levelTime, int randomSeed, int restart ) {', 1)[1]
assert init.count('G_NITMOD_ResetTeamPopulation();') == 1
assert init.index('G_NITMOD_ResetTeamPopulation();') < init.index('G_NITMOD_ResetEntityLists();')
disabled = cmds.split('qboolean G_IsWeaponDisabled(', 1)[1].split('void G_SetClientWeapons(', 1)[0]
assert 'G_NITMOD_EvaluateServerWeaponPolicy(ent, weapon, 0, 1)' in disabled
assert 'policy.limit != NITMOD_LIMIT_INVALID' in disabled
setter = cmds.split('void G_SetClientWeapons(', 1)[1].split('Cmd_Team_f', 1)[0]
assert 'G_NITMOD_SetClientWeapons(ent, w1, w2, updateclient) >= 0' in setter
extensions = (root / 'src_2.60/game/g_cmds_ext.c').read_text()
assert re.search(r'^\s*\{ "setclass",.*Cmd_SetClass_f', extensions, re.M)
