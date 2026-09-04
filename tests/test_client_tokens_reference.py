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
assert {key: tokens[key] for key in ('sc', 'tv', 'xp')} == {'sc': 0x59, 'tv': 0x5a, 'xp': 0x70}
source = (root / 'src_2.60/cgame/cg_players.c').read_text()
assert 'NITMOD_ParseClientExtras(configstring, &newInfo);' in source
assert 'NITMOD_DecodeClientSkills(v, newInfo.skill, newInfo.nitmodSkillLevels);' in source
assert 'CG_NITMOD_SkillRewardText(i, shownLevel)' in source
assert source.count('nativeUpgrade && newInfo.skill[i] == 4') == 2
debrief = (root / 'src_2.60/cgame/cg_debriefing.c').read_text()
stars = debrief.split('void CG_Debriefing_PlayerSkills_Draw', 1)[1].split('void CG_Debriefing_PlayerACC_Draw', 1)[0]
assert 'ci->nitmodSkillLevels[button->data[0]]' in stars
assert 'for(i = 0; i < 5; ++i)' in stars
assert 'button->rect.w * .8f' in stars
assert 'i < SK_NUM_SKILLS && *v' in source
board = (root / 'src_2.60/cgame/cg_scoreboard.c').read_text()
assert board.count('CG_NitmodSpectatorLabel(ci, score->ping)') == 2
rows = (root / 'src_2.60/cgame/cg_nitmod_scoreboard.c').read_text()
assert 'CG_NitmodDrawDMScoreRow(x, y, score, fade)' in board
assert rows.count('CG_NitmodSpectatorLabel(client, score->ping)') == 2
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
