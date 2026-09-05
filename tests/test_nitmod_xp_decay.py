from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
STATS = (ROOT / "src_2.60/game/g_stats.c").read_text(encoding="utf-8")
ACTIVE = (ROOT / "src_2.60/game/g_active.c").read_text(encoding="utf-8")
CVARS = (ROOT / "src_2.60/game/g_nitmod_legacy_cvars.c").read_text(encoding="utf-8")


def test_decay_reads_all_three_runtime_cvars():
    block = STATS[STATS.index("void G_NITMOD_XPDecay"):]
    for name in ("g_XPDecay", "g_XPDecayRate", "g_XPDecayFloor"):
        assert f'"{name}"' in block
    assert "G_NITMOD_LegacyCvarValue" in CVARS


def test_decay_option_bits_and_class_mapping_match_original():
    block = STATS[STATS.index("void G_NITMOD_XPDecay"):]
    for bit in (1, 4, 8, 16, 32, 64, 128):
        assert f"options & {bit}" in block
    for skill in ("SK_HEAVY_WEAPONS", "SK_FIRST_AID", "SK_EXPLOSIVES_AND_CONSTRUCTION",
                  "SK_SIGNALS", "SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS"):
        assert skill in block


def test_decay_runs_from_original_minute_boundary():
    assert "level.time % 60000 == 0" in ACTIVE
    assert "G_NITMOD_XPDecay(ent, 60, qfalse)" in ACTIVE
