from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/cgame/cg_nitmod_mapvote.c").read_text(encoding="utf-8")
SERVER = (ROOT / "src_2.60/cgame/cg_servercmds.c").read_text(encoding="utf-8")
CONSOLE = (ROOT / "src_2.60/cgame/cg_consolecmds.c").read_text(encoding="utf-8")
DEBRIEF = (ROOT / "src_2.60/cgame/cg_debriefing.c").read_text(encoding="utf-8")


def main():
    assert "( argc - 2 ) / 4" in SOURCE
    assert "NITMOD_MAX_MAPVOTE_MAPS" in SOURCE
    assert "records = NITMOD_MAX_MAPVOTE_MAPS" in SOURCE
    assert "CG_NitmodParseMapVoteList" in SERVER and '"immaplist"' in SERVER
    assert "CG_NitmodParseMapVoteTally" in SERVER and '"imvotetally"' in SERVER
    assert '"mapvote %d"' in SOURCE
    assert '"mapvote %d %d"' in SOURCE
    assert "Can't vote for the same map twice" in SOURCE
    assert '"nitmaplist"' in CONSOLE and '"nitmapvote"' in CONSOLE
    assert "#define NITMOD_MAPVOTE_VISIBLE 19" in SOURCE
    assert 'trap_SendClientCommand( "immaplist" )' in SOURCE
    assert 'trap_SendClientCommand( "imvotetally" )' in SOURCE
    assert '"levelshots/unknownmap"' in SOURCE
    assert "K_MWHEELUP" in SOURCE and "K_MWHEELDOWN" in SOURCE
    assert "CG_NitmodMapVoteReset" in DEBRIEF
    assert "CG_NitmodMapVoteRequest" in DEBRIEF
    assert "CG_NitmodMapVoteDraw" in DEBRIEF
    assert "CG_NitmodMapVoteKeyEvent" in DEBRIEF
    assert '#include "cg_nitmod_config.h"' in DEBRIEF


if __name__ == "__main__":
    main()
