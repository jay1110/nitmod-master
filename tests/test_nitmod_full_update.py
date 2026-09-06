from pathlib import Path

root = Path(__file__).resolve().parents[1]
client = (root / 'src_2.60/cgame/cg_consolecmds.c').read_text()
server = (root / 'src_2.60/game/g_cmds.c').read_text()
assert 'NITMOD_ServerSupports(NITMOD_FEATURE_SCORE_KD) ? "fu" : "score"' in client
assert 'if(!cg.demoPlayback && cg.mvTotalClients < 1)' in client
assert 'Q_stricmp (cmd, "fu") == 0' in server
handler = server.split('void Cmd_FullUpdate_f', 1)[1].split('\n}', 1)[0]
assert handler.index('G_SendScore(ent)') < handler.index('TeamplayInfoMessage(TEAM_AXIS)')
assert handler.index('TeamplayInfoMessage(TEAM_AXIS)') < handler.index('TeamplayInfoMessage(TEAM_ALLIES)')
print('Full update: negotiated request and ordered server dispatch wired')
receiver = (root / 'src_2.60/cgame/cg_servercmds.c').read_text()
assert '(!NITMOD_UsesOriginalProtocol() && !NITMOD_ServerSupports(NITMOD_FEATURE_SCORE_KD))' in receiver
assert 'score->client != values[i][0]' in receiver
