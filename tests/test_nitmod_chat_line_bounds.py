"""Source wiring guard; this is not a browser rendering test."""
from pathlib import Path

root = Path(__file__).resolve().parents[1]
source = (root / 'src_2.60/cgame/cg_servercmds.c').read_text()
body = source.split('void CG_AddToTeamChat(', 1)[1].split('void CG_AddToNotify', 1)[0]
guard = '(int)sizeof(cgs.teamChatMsgs[0]) - 3'
assert body.index(guard) < body.index('if ( Q_IsColorString( str ) )')
assert 'len > TEAMCHAT_WIDTH - 1 ||' in body
assert 'teamChatMsgTeams[cgs.teamChatPos % chatHeight] = chatTeam;' in body
print('Chat line byte guard precedes color writes; normal width and team storage retained.')
