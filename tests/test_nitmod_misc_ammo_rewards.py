from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ITEMS = (ROOT / "src_2.60/game/g_items.c").read_text(encoding="utf-8")


def test_misc_bit_eight_only_suppresses_ammo_pack_rewards():
    gate = 'if( !(G_NITMOD_LegacyCvarInteger("g_misc", 0) & 8) )'
    start = ITEMS.index(gate)
    end = ITEMS.index("PCSpecialPickedUpCount++;", start)
    reward = ITEMS[start:end]
    assert "AddScore(ent->parent, WOLF_AMMO_UP)" in reward
    assert "G_AddSkillPoints( ent->parent, SK_SIGNALS, 1.f )" in reward
    assert "G_DebugAddSkillPoints" in reward
    # The accounting update is deliberately outside the reward gate.
    assert end > start + len(reward) - 1


def test_misc_bit_four_only_suppresses_health_pack_rewards():
    gate = 'if( !(G_NITMOD_LegacyCvarInteger("g_misc", 0) & 4) )'
    start = ITEMS.index(gate)
    end = ITEMS.index("PCSpecialPickedUpCount++;", start)
    reward = ITEMS[start:end]
    assert "AddScore(ent->parent, WOLF_HEALTH_UP)" in reward
    assert "G_AddSkillPoints( ent->parent, SK_FIRST_AID, 1.f )" in reward
    assert "G_DebugAddSkillPoints" in reward
    heal = ITEMS[end:ITEMS.index("return -1;", end)]
    assert "other->health += ent->item->quantity" in heal


if __name__ == "__main__":
    test_misc_bit_eight_only_suppresses_ammo_pack_rewards()
    test_misc_bit_four_only_suppresses_health_pack_rewards()
    print("nitmod g_misc ammo reward checks passed")
