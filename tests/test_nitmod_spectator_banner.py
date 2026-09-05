from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DRAW = (ROOT / "src_2.60/cgame/cg_draw.c").read_text(encoding="utf-8")


def test_et_spectator_label_is_suppressed_only_for_nitmod_hud():
    spectator = DRAW[DRAW.index("if ( cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR ) {"):]
    spectator = spectator[:spectator.index("} else {")]
    assert "if ( !NITMOD_UsesNitmodHud() )" in spectator
    assert "CG_DrawSpectator();" in spectator
    assert spectator.index("if ( !NITMOD_UsesNitmodHud() )") < spectator.index("CG_DrawSpectator();")
    assert "CG_DrawCrosshair();" in spectator
    assert "CG_DrawTeamInfo();" in spectator
