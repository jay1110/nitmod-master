from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_thrown_knife_is_an_immediately_active_item_pickup():
    source = (ROOT / "src_2.60/game/g_weapon.c").read_text(encoding="utf-8")
    start = source.index("void G_NITMOD_ThrowKnife")
    end = source.index("qboolean G_WeaponIsExplosive", start)
    function = source[start:end]

    assert "LaunchItem(item, muzzleEffect, velocity" in function
    assert "knife->active = qtrue;" in function
    assert "knife->use = Use_Item;" in function
    assert "knife->s.weapon = WP_KNIFE;" in function
    assert "knife->s.eFlags &= ~EF_BOUNCE_HALF;" in function
    assert "knife->s.eFlags |= EF_BOUNCE;" in function
    assert "knife->s.pos.trTime = level.time - 50;" in function
    assert "knife->physicsBounce = 1.0f;" in function
    assert "CONTENTS_BODY | CONTENTS_CORPSE" in function
    assert "knife->count = 0;" in function
    assert "knife->nextthink = level.time + 20000;" in function


def test_pickup_restores_exactly_one_knife_with_original_cap():
    source = (ROOT / "src_2.60/game/g_items.c").read_text(encoding="utf-8")
    start = source.index("int Pickup_Weapon")
    end = source.index("int Pickup_Health", start)
    function = source[start:end]
    knife = function.index("if( ent->item->giTag == WP_KNIFE )")
    general = function.index("quantity = ent->count")
    assert knife < general
    assert "ps.ammo[ammo] > 7" in function
    assert "Add_Ammo(other, WP_KNIFE, 1, qfalse);" in function
    assert "return -1;" in function[knife:general]
    assert "if(weapon < WP_KNIFE || weapon >= WP_NUM_WEAPONS)" in source


def test_shared_prediction_consumes_the_same_knife_ammo_slot():
    source = (ROOT / "src_2.60/game/bg_pmove.c").read_text(encoding="utf-8")
    start = source.index("static qboolean PM_NitmodThrowKnife")
    end = source.index("static void PM_Weapon", start)
    function = source[start:end]
    assert "ammo = BG_FindAmmoForWeapon(WP_KNIFE);" in function
    assert "if(pm->ps->ammo[ammo] <= 0)" in function
    assert "pm->ps->ammo[ammo]--;" in function


if __name__ == "__main__":
    test_thrown_knife_is_an_immediately_active_item_pickup()
    test_pickup_restores_exactly_one_knife_with_original_cap()
    test_shared_prediction_consumes_the_same_knife_ammo_slot()
    print("nitmod thrown-knife pickup checks passed")
