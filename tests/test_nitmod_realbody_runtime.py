from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ACTIVE = (ROOT / "src_2.60/game/g_active.c").read_text(encoding="utf-8")


def test_realbody_uses_typed_player_state_after_pmove():
    copy = ACTIVE.index("VectorCopy (pm.maxs, ent->r.maxs);")
    options = ACTIVE.index('G_NITMOD_LegacyCvarInteger("g_realBody", 0)', copy)
    link = ACTIVE.index("trap_LinkEntity (ent);", options)
    assert copy < options < link


def test_recovered_vertical_modes_are_present():
    assert "(realBody & 4) || hitboxes" in ACTIVE
    assert "ent->r.maxs[2] = 4.0f" in ACTIVE
    assert "realBody & 8" in ACTIVE
    assert "ent->r.maxs[2] = 18.0f" in ACTIVE
    assert "realBody & 2" in ACTIVE
    assert "ent->r.maxs[2] = 36.0f" in ACTIVE


def test_horizontal_box_is_not_expanded_twice():
    block = ACTIVE[ACTIVE.index("Original nitrox_HitboxHeight"):ACTIVE.index("ent->waterlevel", ACTIVE.index("Original nitrox_HitboxHeight"))]
    assert "mins[0]" not in block
    assert "maxs[0]" not in block

