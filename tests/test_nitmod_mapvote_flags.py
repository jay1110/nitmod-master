from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
GAME = ROOT / "src_2.60" / "game"
MAPVOTE = (GAME / "g_nitmod_mapvote.c").read_text(encoding="utf-8")
VOTE = (GAME / "g_vote.c").read_text(encoding="utf-8")
MAIN = (GAME / "g_main.c").read_text(encoding="utf-8")

assert "!(g_mapVoteFlags.integer & 8)" in MAPVOTE
assert "g_mapVoteFlags.integer & 16" in VOTE
assert 'LogExit("Nextmap vote passed!")' in VOTE
assert 'Choose a new map!' in VOTE
assert "G_NITMOD_LoadMapCycleConfig();" in MAIN
assert '"exec %s/vote_%d.cfg\\n"' in MAIN
assert "configNumber = 2" in MAIN
assert "configNumber = 1" in MAIN
print("Nitmod map-vote flag/cycle-config checks passed")
