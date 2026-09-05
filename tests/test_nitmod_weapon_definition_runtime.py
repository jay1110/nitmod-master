from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

def test_server_commits_complete_custom_weapon_record_atomically():
    source = (ROOT / "src_2.60/game/g_nitmod_weapon_definition.c").read_text(encoding="utf-8")
    assert "parsedAmmo = ammoTableMP[weapon]" in source
    parse = source.index("G_NITMOD_LoadNativeWeaponOptions")
    commit = source.index("ammoTableMP[weapon] = parsedAmmo")
    assert parse < commit
    assert "weaponRecoil[weapon] = parsedRecoil" in source
    assert "pickupDefinitionState[weapon] = 1" in source

if __name__ == "__main__":
    test_server_commits_complete_custom_weapon_record_atomically()
