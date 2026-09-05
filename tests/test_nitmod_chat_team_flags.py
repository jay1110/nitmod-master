from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DRAW = (ROOT / "src_2.60/cgame/cg_draw.c").read_text(encoding="utf-8")
SERVERCMDS = (ROOT / "src_2.60/cgame/cg_servercmds.c").read_text(encoding="utf-8")


def test_chat_lines_keep_sender_team_for_wrapped_text_and_voice_chat():
    assert "cgs.teamChatMsgTeams[cgs.teamChatPos % chatHeight] = chatTeam;" in SERVERCMDS
    assert "CG_AddToTeamChat( vchat->message, vchat->clientNum );" in SERVERCMDS


def test_nitmod_chat_draws_original_team_flag_set():
    draw = DRAW[DRAW.index("static void CG_DrawTeamInfo( void )"):]
    draw = draw[:draw.index("const char* CG_PickupItemText")]
    assert "messageTeam == TEAM_AXIS" in draw
    assert "teamFlag = cgs.media.axisFlag" in draw
    assert "messageTeam == TEAM_ALLIES" in draw
    assert "teamFlag = cgs.media.alliedFlag" in draw
    assert "messageTeam == TEAM_SPECTATOR" in draw
    assert "teamFlag = cgs.media.limboSpectator" in draw
    assert "CG_DrawPic( CHATLOC_TEXT_X - 14" in draw
    assert "if ( NITMOD_UsesNitmodHud() )" in draw
