from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ITEMS = (ROOT / "src_2.60/game/g_items.c").read_text(encoding="utf-8")

def test_supplier_precedes_reward_eligibility():
    ammo = ITEMS.split("int Pickup_Weapon(", 1)[1].split("int Pickup_Health", 1)[0]
    health = ITEMS.split("int Pickup_Health", 1)[1].split("void RespawnItem", 1)[0]
    for body, field, cls in ((ammo, "nitmodLastAmmoClient", "PC_FIELDOPS"),
                             (health, "nitmodLastHealthClient", "PC_MEDIC")):
        assert body.index(field) < body.index("!= " + cls)
        prefix = body[:body.index(field)]
        assert "ent->parent != other" not in prefix
        assert "sess.sessionTeam ==" not in prefix

def reward_block(gate):
    start = ITEMS.index("{", ITEMS.index(gate))
    depth = 1
    end = start + 1
    while depth:
        depth += (ITEMS[end] == "{") - (ITEMS[end] == "}")
        end += 1
    return ITEMS[start:end], end


def test_misc_bit_eight_only_suppresses_ammo_pack_rewards():
    gate = 'if( !(G_NITMOD_LegacyCvarInteger("g_misc", 0) & 8) )'
    start = ITEMS.index(gate)
    reward, end = reward_block(gate)
    assert "AddScore(ent->parent, WOLF_AMMO_UP)" in reward
    assert "G_AddSkillPoints( ent->parent, SK_SIGNALS, 1.f )" in reward
    assert "G_DebugAddSkillPoints" in reward
    assert "PCSpecialPickedUpCount++;" in reward
    assert reward.index("PCSpecialPickedUpCount++;") < reward.index("G_AddSkillPoints")


def test_misc_bit_four_only_suppresses_health_pack_rewards():
    gate = 'if( !(G_NITMOD_LegacyCvarInteger("g_misc", 0) & 4) )'
    start = ITEMS.index(gate)
    reward, end = reward_block(gate)
    assert "PCSpecialPickedUpCount++;" in reward
    assert reward.index("PCSpecialPickedUpCount++;") < reward.index("G_AddSkillPoints")
    assert "AddScore(ent->parent, WOLF_HEALTH_UP)" in reward
    assert "G_AddSkillPoints( ent->parent, SK_FIRST_AID, 1.f )" in reward
    assert "G_DebugAddSkillPoints" in reward
    heal = ITEMS[end:ITEMS.index("return -1;", end)]
    assert "other->health += ent->item->quantity" in heal


if __name__ == "__main__":
    test_supplier_precedes_reward_eligibility()
    test_misc_bit_eight_only_suppresses_ammo_pack_rewards()
    test_misc_bit_four_only_suppresses_health_pack_rewards()
    print("nitmod g_misc ammo reward checks passed")
