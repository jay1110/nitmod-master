"""Original dictionary identity and active optional equipment receive hook."""
import importlib.util
import pathlib
import re
import sys

root = pathlib.Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('client_tokens', root / 'tools/extract_client_tokens.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
tokens = module.extract(root)
assert len(tokens) == 279
assert {key: tokens[key] for key in ('rn', 'w', 'lw', 'sw', 'lc')} == {
    'rn': 0x89, 'w': 0x49, 'lw': 0x86, 'sw': 0x88, 'lc': 0x87
}
assert tokens['B'] != tokens['b']  # Preserve dictionary case, no case-folding.
source = (root / 'src_2.60/cgame/cg_players.c').read_text()
assert re.search(r'memset\( &newInfo, 0, sizeof\( newInfo \) \);.*?'
                 r'Info_ValueForKey\( configstring, "rn" \);\s*'
                 r'NITMOD_ParseProtocolSigned\( v, &newInfo.rifleGrenadeStatus \);', source, re.S)
assert re.search(r'if \( !\*configstring \) \{\s*memset\( ci, 0, sizeof\( \*ci \) \);', source)
server = (root / 'src_2.60/game/g_client.c').read_text()
session = (root / 'src_2.60/game/g_session.c').read_text()
assert 's = va( "%s\\\\rn\\\\%i\\\\lc\\\\%i", s, client->sess.rifleGrenadeStatus, client->sess.latchPlayerType );' in server
assert 'newInfo.latchedClass = NITMOD_ParseLatchedClass(configstring, newInfo.cls);' in source
limbo = (root / 'src_2.60/cgame/cg_limbopanel.c').read_text()
assert 'if(NITMOD_ClassIsDisabled(CG_LimboPanel_GetTeam(), button->data[1])) return qfalse;' in limbo
assert re.search(r'if\(NITMOD_ClassIsDisabled.*?CG_DrawPic\([^;]*cgs.media.friendShader\);', limbo, re.S)
assert re.search(r'SetWolfSpawnWeapons\( client \);.*?ClientUserinfoChanged\( index \);', server, re.S)
for weapon in ('WP_GPG40', 'WP_M7'):
    assert f'client->sess.rifleGrenadeStatus = AddWeaponToPlayer( client, {weapon},' in server
assert 'G_NITMOD_WriteEquipment( client, client - level.clients );' in session
assert 'G_NITMOD_ReadEquipment( client, client - level.clients );' in session
assert 'sess->rifleGrenadeStatus = 0;' in session
