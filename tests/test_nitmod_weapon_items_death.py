from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_combat.c").read_text(encoding="utf-8")


def test_original_weapon_item_death_drop_bits_are_consumed():
    start = SOURCE.index("void TossClientItems")
    end = SOURCE.index("void LookAtKiller", start)
    body = SOURCE[start:end]
    assert 'G_NITMOD_LegacyCvarInteger("g_weaponItems", 1)' in body
    assert "options & 1" in body
    assert "(g_dualSMG.integer & 3) == 3" in body
    assert "options & 2" in body and "WP_BINOCULARS" in body
    assert "options & 32" in body and "WP_KNIFE" in body
    assert "BG_FindAmmoForWeapon(WP_KNIFE)] > 1" in body


if __name__ == "__main__":
    test_original_weapon_item_death_drop_bits_are_consumed()
    print("nitmod g_weaponItems death-drop checks passed")
