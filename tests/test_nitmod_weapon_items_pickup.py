from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ITEMS = (ROOT / "src_2.60/game/g_items.c").read_text(encoding="utf-8")
LOCAL = (ROOT / "src_2.60/game/g_local.h").read_text(encoding="utf-8")


def test_drop_reserve_and_pickup_mask_consumers():
    assert "int nitmodDropAmmo;" in LOCAL
    assert "ent2->nitmodDropAmmo = client->ps.ammo" in ITEMS
    assert "client->ps.ammo[BG_FindAmmoForWeapon(weapon)] = 0;" in ITEMS
    assert '(options & 4) ? ent->nitmodDropAmmo : 0' in ITEMS
    assert "!ammoAdded && (options & 16)" in ITEMS
    assert "ps.ammo[BG_FindAmmoForWeapon(ent->item->giTag)] = reserveQuantity" in ITEMS
    assert "(options & 8) && ent->item->giTag != WP_BINOCULARS" in ITEMS
    assert "pickupEvent = EV_ITEM_PICKUP_QUIET" in ITEMS
    assert "ent->nitmodDropAmmo = 0;" in ITEMS


if __name__ == "__main__":
    test_drop_reserve_and_pickup_mask_consumers()
    print("nitmod g_weaponItems pickup checks passed")
