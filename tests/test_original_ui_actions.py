"""Pin the command spellings to the unmodified original UI reference."""
from pathlib import Path
import re

root = Path(__file__).resolve().parents[1]
binary = (root / 'original_nitmod_shared_objects_32bit/ui.mp.i386.so').read_bytes()
source = (root / 'src_2.60/ui/ui_nitmod_actions.c').read_text()
rows = re.findall(r'\{ "(\w+)", "([\w ]+)" \}', source)
# Original UI_RunMenuScript's immediate configstring index is 29.
assert binary[0x2362b:0x23632] == bytes.fromhex('c7 04 24 1d 00 00 00')
# Both local-player lookup and roster traversal use CS_PLAYERS=689.
# These are ELF file offsets in the supplied unmodified UI reference.
assert binary[0x15d06:0x15d0b] == bytes.fromhex('05 b1 02 00 00')
assert binary[0x15dcb:0x15dd1] == bytes.fromhex('8d 85 b1 02 00 00')
toggle_init = source.split('if(!Q_stricmp(name, "voteInitToggles")) {')[1].split('if(!Q_stricmp(name, "clientCheckVote"))')[0]
assert 'int toggles = CS_SERVERTOGGLES;' in toggle_init
assert '"nitmod_csLayout"), "et260")) toggles = 29;' in toggle_init
assert 'trap_GetConfigString(toggles, info, sizeof(info));' in toggle_init
vote_check = source.split('if(!Q_stricmp(name, "clientCheckVote")) {')[1].split('for(i = 0;')[0]
assert vote_check.index('(double)raw <= INT_MAX') < vote_check.index('flags = (int)raw')
assert 'flags == VOTING_DISABLED || flags == ET_VOTING_DISABLED' in vote_check
assert len(rows) == 21
for name, command in rows:
    assert name.encode() + b'\0' in binary, name
    assert (command + ' "%s"\n\0').encode() in binary, command
# Disassembly 0x230fc..0x23176: spelling, cvar, and emitted format.
for offset, expected in {
    0x46742: b'votePoll', 0x4674b: b'ui_poll',
    0x46753: b'callvote poll "%s"\n',
    0x46bf2: b'ref warn "%s" "%s"\n',
    0x46c1a: b'ref warmup "%s"\n',
}.items():
    assert binary[offset:offset + len(expected) + 1] == expected + b'\0'
print('24 menu-action names/formats match original UI; runtime tests check dispatch.')

# Roster inputs are remote-controlled. These are wiring checks, not a UI replay.
main = (root / 'src_2.60/ui/ui_main.c').read_text()
roster = main.split('static void UI_BuildPlayerList()', 1)[1].split('static void UI_DrawSelectedPlayer', 1)[0]
assert 'trap_GetConfigString( CS_PLAYERS + cs.clientNum' in roster
assert 'trap_GetConfigString( CS_PLAYERS + n' in roster
assert 'if( count > MAX_CLIENTS ) count = MAX_CLIENTS;' in roster
assert 'if( count < 0 ) count = 0;' in roster
assert 'cs.clientNum >= 0 && cs.clientNum < MAX_CLIENTS' in roster
for field in ('playerNames', 'playerMuted', 'playerRefereeStatus', 'teamNames', 'teamClientNums'):
    assert 'memset( uiInfo.' + field in roster
assert 'uiInfo.playerIndex >= uiInfo.playerCount' in roster
assert 'uiInfo.teamIndex >= uiInfo.myTeamCount' in roster
assert 'key < 0 || key >= (int)(sizeof(menu->onKey)' in main

# Original Nitmod's UI dispatcher assigns class/classAlt/chat to 15/16/17.
console = (root / 'src_2.60/cgame/cg_consolecmds.c').read_text()
shared = (root / 'src_2.60/game/bg_public.h').read_text()
assert '{ "classmenu", CG_NitmodClassMenu_f }' in console
assert 'cg_quickMessageAlt.integer ? UIMENU_NITMOD_CLASSALT : UIMENU_NITMOD_CLASS' in console
assert 'CG_EventHandling(CGAME_EVENT_NONE, qfalse)' in console
assert 'UIMENU_INGAME_MESSAGEMODE,' in shared
assert shared.index('UIMENU_NITMOD_CLASS,') < shared.index('UIMENU_NITMOD_CLASSALT,')
assert shared.index('UIMENU_NITMOD_CLASSALT,') < shared.index('UIMENU_INGAME_MESSAGEMODE,')
for name in ('wm_class', 'wm_classAlt', 'ingame_messagemode4'):
    assert '"' + name + '"' in main
    assert name.lower().encode() in binary.lower()
assert 'trap_Cvar_VariableStringBuffer("cg_messageType"' in main
assert 'atoi(messageType) == 4' in main
assert '{ "messageMode4", CG_MessageMode_f }' in console

# Nitmod's message types remain intact behind the engine-compatible popup ID.
assert 'else if( !Q_stricmp( cmd, "messagemode4" ) )' in console
assert 'trap_Cvar_Set( "cg_messageType", "4" )' in console
send = console.split('static void CG_MessageSend_f', 1)[1].split('static void CG_SetWeaponCrosshair_f', 1)[0]
assert 'messageType == 4' in send
assert 'va( "ma \\"%s\\"\\n", messageText )' in send
assert send.index('messageType == 4') < send.index('// normal say')

# Console chat interception must precede local dispatch, but never the
# snapshot/protocol gates. This covers all seven original aliases as a group.
dispatch = console.split('qboolean CG_ConsoleCommand( void )', 1)[1].split('void CG_InitConsoleCommands', 1)[0]
assert dispatch.index('if ( !cg.snap )') < dispatch.index('CG_NitmodConsoleChat(cmd)')
assert dispatch.index('CG_NitmodConsoleChat(cmd)') < dispatch.index('commands[i].function()')
chat = console.split('static qboolean CG_NitmodConsoleChat', 1)[1].split('static void CG_MessageSend_f', 1)[0]
assert '!NITMOD_UsesOriginalProtocol() || !name' in chat
assert 'trap_Argv(i, arg, sizeof(arg))' in chat
assert 'if (!NITMOD_TextNeedsEncoding(text)) return qfalse;' in chat
assert 'CG_NitmodSendChat(name, text)' in chat
sender = console.split('void CG_NitmodSendChat', 1)[1].split('static qboolean CG_NitmodConsoleChat', 1)[0]
assert 'NITMOD_BuildChatCommand' in sender
assert 'trap_SendClientCommand(reliable)' in sender
assert 'trap_SendConsoleCommand' not in sender

# The remaining original vote/referee scalar actions are kept out of the
# monolithic UI_RunMenuScript dispatcher and reject non-finite conversions.
actions = (root / 'src_2.60/ui/ui_nitmod_actions.c').read_text()
for name in ('voteTimelimit', 'refTimelimit', 'voteWarmupDamage',
             'refWarmupDamage', 'voteInitToggles', 'clientCheckVote'):
    assert ('"' + name + '"') in actions
    assert name.encode() + b'\0' in binary
for fmt in (b'callvote timelimit %f\n', b'ref timelimit %f\n',
            b'callvote warmupdamage %d\n', b'ref warmupdamage %d\n'):
    assert fmt + b'\0' in binary
assert '#include <float.h>' in actions
assert '#include <limits.h>' in actions
