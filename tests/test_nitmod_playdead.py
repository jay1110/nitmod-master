from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def require(text: str, fragment: str) -> None:
    assert fragment in text, fragment


def test_playdead_protocol_and_shared_prediction_path():
    public = (ROOT / "src_2.60/game/bg_public.h").read_text(encoding="utf-8")
    pmove = (ROOT / "src_2.60/game/bg_pmove.c").read_text(encoding="utf-8")
    commands = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")

    require(public, "PM_INTERMISSION,")
    require(public, "PM_PLAYDEAD")
    require(pmove, "if( pm->ps->pm_type == PM_PLAYDEAD )")
    require(pmove, "pm->ps->eFlags |= EF_SPARE0;")
    require(pmove, "pm->ps->eFlags &= ~EF_SPARE0;")
    require(pmove, "maxs[2] = pm->ps->crouchMaxZ;")
    require(commands, '!Q_stricmp(cmd, "playdead")')
    require(commands, 'G_NITMOD_LegacyCvarInteger("g_playDead", 1)')
    require(commands, "ps->pm_flags != 0")


if __name__ == "__main__":
    test_playdead_protocol_and_shared_prediction_path()
    print("nitmod playdead checks passed")
