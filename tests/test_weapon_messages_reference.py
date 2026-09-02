"""Pin ncp weapon text and both ends of the gated subset transport."""
import importlib.util
import pathlib
import re
import sys
import json

root = pathlib.Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('weapon_messages', root / 'tools/extract_weapon_messages.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
original = module.extract(root)
source = (root / 'src_2.60/game/nitmod_protocol.c').read_text()
body = source.split('const char *NITMOD_WeaponLimitText', 1)[1].split('\n}', 1)[0]
texts = [json.loads(line.rstrip(',')) for line in (root / 'src_2.60/game/nitmod_server_messages.inc').read_text().splitlines() if line.startswith('"')][19:26]
assert 'return NITMOD_ServerMessageText(reason)' in body
assert texts == [original[i] for i in range(19, 26)]
server = (root / 'src_2.60/game/g_nitmod_config.c').read_text()
sender = server.split('void NITMOD_SendWeaponLimitMessage', 1)[1].split('\n}', 1)[0]
assert 'NITMOD_WeaponLimitText(reason)' in sender
assert 'G_NITMOD_ClientSupports(clientNum, NITMOD_FEATURE_WEAPON_MESSAGES)' in sender
assert 'trap_SendServerCommand(clientNum, va("ncp %i", reason))' in sender
client = (root / 'src_2.60/cgame/cg_servercmds.c').read_text()
assert 'if ( !Q_stricmp( cmd, "ncp" ) )' in client
assert 'trap_Argc() == 2 && NITMOD_ParseProtocolInteger(CG_Argv(1), &reason)' in client
assert 'if( text ) CG_CenterPrint(text, 384, 8);' in client
