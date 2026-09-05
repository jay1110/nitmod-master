from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
GAME = ROOT / "src_2.60" / "game"
CMDS = (GAME / "g_cmds.c").read_text(encoding="utf-8")
MAIN = (GAME / "g_main.c").read_text(encoding="utf-8")
LOCAL = (GAME / "g_local.h").read_text(encoding="utf-8")

# Original Cmd_CallVote_f 0x69679 clamps only the validated timelimit vote.
vote = CMDS.split("qboolean Cmd_CallVote_f", 1)[1].split("Cmd_Vote_f", 1)[0]
assert 'G_NITMOD_LegacyCvarInteger("n_voteMaxTimelimit", 0)' in vote
assert 'strtol(arg2, NULL, 10) > maximum' in vote
assert vote.index("G_voteCmdCheck") < vote.index('!Q_stricmp(arg1, "timelimit")')
assert vote.index('!Q_stricmp(arg1, "timelimit")') < vote.index("voteInfo.voteString")

# Original G_TankIsMountable/G_LeaveTank 0x69b00/0x6d1e0 use a player-entity
# deadline. Hint scans are silent and a positioned dismount starts the delay.
assert "int\t\t\tnitmodTankMountTime;" in LOCAL
mount = CMDS.split("qboolean G_TankIsMountable", 1)[1].split("G_NITMOD_RemoveClassTools", 1)[0]
assert 'G_NITMOD_LegacyCvarInteger("n_tankMountDelay", 0)' in mount
assert "other->nitmodTankMountTime > level.time" in mount
assert "if( notify )" in mount
leave = CMDS.split("void G_LeaveTank", 1)[1].split("void Cmd_Activate_f", 1)[0]
assert "if( position &&" in leave
assert "ent->nitmodTankMountTime = level.time" in leave
assert "G_TankIsMountable( traceEnt, ent, qtrue )" in CMDS
assert "G_TankIsMountable( checkEnt, ent, qfalse )" in MAIN

print("Nitmod vote cap and tank-mount delay checks passed")
