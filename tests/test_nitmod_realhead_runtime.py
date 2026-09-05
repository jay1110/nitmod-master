from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
COMBAT = (ROOT / "src_2.60/game/g_combat.c").read_text(encoding="utf-8")


def test_realhead_reads_the_original_default_and_bit():
    block = COMBAT[COMBAT.index("gentity_t* G_BuildHead"):COMBAT.index("gentity_t* G_BuildLeg")]
    assert 'G_NITMOD_LegacyCvarInteger("g_realHead", 1) & 1' in block
    assert 'trap_GetTag( ent->s.number, 0, "tag_head", &or )' in block


def test_realhead_and_legacy_boxes_are_both_preserved():
    block = COMBAT[COMBAT.index("gentity_t* G_BuildHead"):COMBAT.index("gentity_t* G_BuildLeg")]
    assert "VectorSet(head->r.mins, -6, -6, -6)" in block
    assert "VectorSet(head->r.maxs,  6,  6,  6)" in block
    assert "VectorSet(head->r.mins, -6, -6, -2)" in block
    assert "VectorSet(head->r.maxs,  6,  6, 10)" in block
