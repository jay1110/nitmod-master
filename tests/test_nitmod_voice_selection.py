"""Source wiring checks for the original voice variant protocol."""
from pathlib import Path
root = Path(__file__).resolve().parents[1]
source = (root / 'src_2.60/cgame/cg_servercmds.c').read_text()
assert 'CG_Argv(mode == SAY_ALL ? 5 : 8)' in source
assert 'selection * voiceChatList->voiceChats[i].numSounds' in source
assert '!(selection >= 0.0f && selection <= 1.0f)' in source
assert 'if( rnd >= voiceChatList->voiceChats[i].numSounds )' in source
assert 'CG_GetVoiceChat( voiceChatList, cmd, &snd, &sprite, &chat, selection )' in source
local_voice = source.split('void CG_VoiceChatLocal(', 1)[1].split('void CG_VoiceChat(', 1)[0]
assert 'CG_NitmodLocationText(location, sizeof(location), origin, 2)' in local_voice
assert 'BG_GetLocationString' not in local_voice
assert '"(%s^7)^3(%s)^7:^%c%s"' in local_voice
assert '"<%s^7>%c%c<%s>: %c%c%s"' in local_voice
server = (root / 'src_2.60/game/g_cmds.c').read_text()
voice = server.split('static void G_VoiceWithText( ', 1)[1].split('static void Cmd_Voice_f', 1)[0]
assert voice.count('float selection = random();') == 1
assert voice.count('voiceonly, selection)') == 2
assert 'voiceonly, selection );' in voice  # direct target
assert voice.count('!COM_BitCheck( level.clients[level.sortedClients[j]].sess.ignoreClients,') == 2
# Original targeted G_VoiceTo bypasses the broadcast ignore filter.
target = voice.split('if ( target ) {', 1)[1].split('// echo', 1)[0]
assert 'COM_BitCheck' not in target
assert 'if( text && strlen(text) > 1 )' in voice
assert 'G_Say(ent, target, mode, text);\n\t\tvoiceonly = qtrue;' in voice
assert 'G_VoiceWithText(ent, target, mode, id, "", voiceonly);' in voice
assert 'ConcatArgs(arg0 ? 1 : 2)' in server
assert 'ConcatArgs(arg0 ? 3 + index : 4 + index)' in server
assert '"%s %d %d %d %s %i %i %i %f"' in server
assert '"%s %d %d %d %s %f"' in server
# The reconstructed server uses ET260 configstring layout, but the same voice
# extension. Its selector must not depend on original configstring numbering.
client_voice = source.split('void CG_VoiceChat(', 1)[1].split('// -NERVE - SMF', 1)[0]
assert 'NITMOD_UsesOriginalProtocol()' not in client_voice
print('Voice selector reaches sound/sprite/text variant lookup with range guards.')

commands = (root / 'src_2.60/cgame/cg_consolecmds.c').read_text()
for name in ('CG_VoiceChat_f', 'CG_TeamVoiceChat_f', 'CG_BuddyVoiceChat_f'):
    body = commands.split('static void ' + name + '( void ) {', 1)[1].split('\n}', 1)[0]
    assert 'trap_Argc() != 2' in body
    assert 'trap_Argv( 1, chatCmd, 64 )' in body
    assert 'trap_SendConsoleCommand' in body
    assert 'TEAM_SPECTATOR' not in body
    assert 'cg.snap' not in body
print('All three client voice commands defer recipient policy to the server, as in original.')
