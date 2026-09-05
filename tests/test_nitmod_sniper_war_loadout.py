from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60" / "game" / "g_client.c").read_text(encoding="utf-8")


def test_sniper_war_replaces_class_loadout():
    assert "warMode < 1 || warMode > 4" in SOURCE
    assert "if(G_NITMOD_GrantWarLoadout(client)) return;" in SOURCE


def test_sniper_war_uses_typed_team_rifles_and_original_ammo():
    for token in ("WP_K43", "WP_K43_SCOPE", "WP_GARAND", "WP_GARAND_SCOPE"):
        assert token in SOURCE
    assert "AddWeaponToPlayer(client, rifle, 500, 10, qtrue);" in SOURCE
    assert "AddWeaponToPlayer(client, scopedRifle, 500, 10, qfalse);" in SOURCE


def test_sniper_war_option_bits_are_consumed():
    assert 'G_NITMOD_LegacyCvarInteger("n_sniperWarOptions", 7)' in SOURCE
    assert "options & 1u" in SOURCE
    assert "options & 4u" in SOURCE
    assert "(1 << INV_BINOCS)" in SOURCE


def test_all_original_war_loadouts_replace_class_weapons():
    assert "if(warMode == 4) return qtrue;" in SOURCE
    assert "AddWeaponToPlayer(client, WP_PANZERFAUST, 1, 0, qtrue);" in SOURCE
    for token in ("WP_KAR98", "WP_GPG40", "WP_CARBINE", "WP_M7"):
        assert token in SOURCE
    assert "AddWeaponToPlayer(client, rifleGrenade, 500," in SOURCE
    assert "client->sess.rifleGrenadeStatus = 1;" in SOURCE


if __name__ == "__main__":
    test_sniper_war_replaces_class_loadout()
    test_sniper_war_uses_typed_team_rifles_and_original_ammo()
    test_sniper_war_option_bits_are_consumed()
    test_all_original_war_loadouts_replace_class_weapons()
    print("sniper-war loadout source checks passed")
