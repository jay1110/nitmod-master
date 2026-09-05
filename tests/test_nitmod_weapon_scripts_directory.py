from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_map_weapon_registry_honors_server_directory_through_vfs():
    source = (ROOT / "src_2.60/game/g_nitmod_weapon_definition.c").read_text(encoding="utf-8")
    cvars = (ROOT / "src_2.60/game/g_nitmod_legacy_cvars.c").read_text(encoding="utf-8")
    assert '"g_weaponScriptsDir","",0' in cvars
    assert 'trap_Cvar_VariableStringBuffer("g_weaponScriptsDir"' in source
    assert "G_NITMOD_WeaponScriptsDirectory(), &ignoredAmmo" in source
    assert 'memcpy(fallback, "weapons/"' in source
    assert "trap_PC_LoadSource(preferred)" in source
    assert "trap_PC_LoadSource(fallback)" in source


if __name__ == "__main__":
    test_map_weapon_registry_honors_server_directory_through_vfs()
