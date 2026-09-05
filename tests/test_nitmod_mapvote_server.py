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
assert "voteEligible > entry->voteEligible" in SOURCE
assert "++mapVoteMaps[mapVoteVisible[index]].voteEligible" in SOURCE
assert "Q_strncpyz( key, token, sizeof(key) )" in SOURCE
assert "level.intermissiontime" in SOURCE
assert "NITMOD_ParseProtocolInteger(argument, &id)" in SOURCE
assert "NITMOD_ParseProtocolInteger(argument, &slot)" in SOURCE
assert "g_mapVoteFlags.integer & 2" in SOURCE
assert "client->ps.eFlags & EF_VOTED" in SOURCE
assert "g_intermissionReadyPercent.value" in SOURCE
assert "G_NITMOD_MapVoteExitReady" in MAIN
assert "G_NITMOD_MapNameSafe" in SOURCE
assert "strlen(message) + strlen(record)" in SOURCE
print("Nitmod qagame map-vote protocol checks passed")
