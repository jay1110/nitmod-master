from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
GAME = ROOT / "src_2.60" / "game"


def test_reset_xp_map_count_is_typed_and_not_legacy():
    main = (GAME / "g_main.c").read_text(encoding="utf-8")
    legacy = (GAME / "g_nitmod_legacy_cvars.c").read_text(encoding="utf-8")
    assert '{ &g_resetXPMapCount, "g_resetXPMapCount", "0"' in main
    assert '"g_resetXPMapCount"' not in legacy


def test_cycle_is_persisted_and_advanced_before_world_session_write():
    session = (GAME / "g_session.c").read_text(encoding="utf-8")
    main = (GAME / "g_main.c").read_text(encoding="utf-8")
    assert '"%i %i %i %i %s"' in session
    assert "G_NITMOD_MapCycleCount()" in session
    exit_level = main[main.index("void ExitLevel (void)"):main.index("void G_LogPrintf", main.index("void ExitLevel (void)"))]
    assert exit_level.index("G_NITMOD_AdvanceMapCycle();") < exit_level.index("G_WriteSessionData( qfalse );")


def test_reset_is_once_per_world_init_and_permanent_xp_bypasses_it():
    session = (GAME / "g_session.c").read_text(encoding="utf-8")
    config = (GAME / "g_nitmod_config.c").read_text(encoding="utf-8")
    read_client = session[session.index("void G_ReadSessionData"):session.index("void G_InitSessionData")]
    world = session[session.index("void G_InitWorldSession"):session.index("void G_WriteSessionData")]
    assert "G_NITMOD_MapCycleResetsXP" not in read_client
    assert "G_NITMOD_MapCycleResetsXP" in world
    assert "sessionstats%i" in world
    assert "!(g_XPSave.integer & 4)" in config


def test_ncs_uses_authoritative_cycle_fields():
    config = (GAME / "g_nitmod_config.c").read_text(encoding="utf-8")
    assert "state.mapCount = G_NITMOD_MapCycleCount();" in config
    assert "state.resetXPMapCount = (g_XPSave.integer & 4) ? 0" in config
