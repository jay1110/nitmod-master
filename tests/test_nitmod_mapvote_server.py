from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_nitmod_mapvote.c").read_text(encoding="utf-8")
CMDS = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
MAIN = (ROOT / "src_2.60/game/g_main.c").read_text(encoding="utf-8")
LEGACY = (ROOT / "src_2.60/game/g_nitmod_legacy_cvars.c").read_text(encoding="utf-8")

for name in ("g_maxMapsVotedFor", "g_minMapAge", "g_mapVoteFlags", "g_excludedMaps"):
    assert f'&{name}, "{name}"' in MAIN
    assert f'"{name}"' not in LEGACY
for command, function in (("immaplist", "G_NITMOD_MapVoteSendList"),
                          ("imvotetally", "G_NITMOD_MapVoteSendTally"),
                          ("mapvote", "G_NITMOD_MapVoteCast")):
    assert f'cmd, "{command}"' in CMDS
    assert function in CMDS
assert 'trap_FS_GetFileList( "maps", ".bsp"' in SOURCE
assert "id >= mapVoteCount" in SOURCE
assert "!mapVoteMaps[id].available" in SOURCE
assert "nitmodMapVotes[old] == id + 1" in SOURCE
assert "mapVoteMaps[old].votes >= slot" in SOURCE
assert "mapVoteMaps[id].votes += slot" in SOURCE
assert "entry->lastPlayed, entry->totalVotes" in SOURCE
assert "mapVoteMaps[mapVoteVisible[position - 1]].randomOrder, entry->randomOrder" in SOURCE
assert "++mapVoteMaps[mapVoteVisible[index]].voteEligible" in SOURCE
assert "Q_strncpyz( key, token, sizeof(key) )" in SOURCE
assert "level.intermissiontime" in SOURCE
assert "NITMOD_ParseProtocolInteger(argument, &id)" in SOURCE
assert "NITMOD_ParseProtocolInteger(argument, &slot)" in SOURCE
cast_body = SOURCE[SOURCE.index("void G_NITMOD_MapVoteCast("):SOURCE.index("qboolean G_NITMOD_MapVoteExitLevel(")]
assert "if( argc != 2 && argc != 3 ) return;" in cast_body
assert "if( argc == 3 )" in cast_body
assert "g_mapVoteFlags.integer & 4" not in cast_body
assert "argc == 3 && old != slot - 1" in cast_body
assert "g_mapVoteFlags.integer & 2" in SOURCE
assert "client->ps.eFlags & EF_VOTED" in SOURCE
assert "g_intermissionReadyPercent.value" in SOURCE
assert "G_NITMOD_MapVoteExitReady" in MAIN
exit_body = SOURCE[SOURCE.index("qboolean G_NITMOD_MapVoteExitLevel("):]
load_body = SOURCE[SOURCE.index("static void G_NITMOD_MapVoteLoad("):SOURCE.index("static int G_NITMOD_MapVoteVisibleCount( void ) {")]
assert "++entry->timesPlayed;" in load_body
assert "if( !entry->available && entry->lastPlayed >= 0 ) ++entry->lastPlayed;" in load_body
assert "timesPlayed" not in exit_body
assert "for( i = 0; i < visible; ++i )" in exit_body
assert "nitmodMapVoteEntry_t *entry = &mapVoteMaps[mapVoteVisible[i]];" in exit_body
assert "if( visible <= 0 ) {\n\t\tG_NITMOD_MapVoteWriteHistory();" in exit_body
assert exit_body.index("G_NITMOD_MapVoteWriteHistory();") < exit_body.index("if( mapVoteMaps[winner].votes <= 0 ) return qfalse;") < exit_body.index("trap_SendConsoleCommand(")
assert '!G_NITMOD_MapVoteExitLevel()' in MAIN
assert 'va("map %s;set nextmap %s\\n", mapVoteMaps[winner].name, g_nextmap.string)' in exit_body
assert "G_NITMOD_MapNameSafe" in SOURCE
assert SOURCE.index("if( length >= sizeof(name) )") < SOURCE.index('Q_strncpyz( name, file, sizeof(name) )')
assert "strlen(message) + strlen(record)" in SOURCE
print("Nitmod qagame map-vote protocol checks passed")
