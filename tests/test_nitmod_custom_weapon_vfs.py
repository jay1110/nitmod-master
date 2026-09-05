from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_client_uses_canonical_vfs_path_and_accepts_combined_files():
    weapons = (ROOT / "src_2.60/cgame/cg_weapons.c").read_text(encoding="utf-8")
    commands = (ROOT / "src_2.60/cgame/cg_consolecmds.c").read_text(encoding="utf-8")
    assert 'va( "weapons/%s", filename )' in weapons
    assert '!Q_stricmp( token.string, "server" )' in weapons
    assert "CG_RW_ParseSharedDefinition( handle, qfalse" in weapons
    assert "CG_RegisterWeapon( i, qtrue )" in commands
    assert '"loadweapons", CG_LoadWeapons_f' in commands


if __name__ == "__main__":
    test_client_uses_canonical_vfs_path_and_accepts_combined_files()
