from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60" / "game" / "g_svcmds.c").read_text(encoding="utf-8")
SPAWN = (ROOT / "src_2.60" / "game" / "g_client.c").read_text(encoding="utf-8")


def run_checks() -> None:
    assert 'Svcmd_WarMode_f( "panzerwar", 1, "Panzerwar" )' in SOURCE
    assert 'Svcmd_WarMode_f( "sniperwar", 2, "Sniperwar" )' in SOURCE
    assert 'G_NITMOD_LegacyCvarInteger( "g_war", 0 )' in SOURCE
    assert '!Q_stricmp( value, "on" )' in SOURCE
    assert '!Q_stricmp( value, "off" )' in SOURCE
    assert "level.numConnectedClients" in SOURCE
    assert "level.sortedClients[i]" in SOURCE
    assert "DAMAGE_NO_PROTECTION | DAMAGE_NO_KNOCKBACK" in SOURCE
    assert "MOD_UNKNOWN" in SOURCE
    assert 'trap_Cvar_Set( "g_war"' in SOURCE
    assert "G_NITMOD_GrantWarLoadout" in SPAWN
    assert "warMode < 1 || warMode > 4" in SPAWN
    assert "warMode == 1" in SPAWN
    assert "warMode == 3" in SPAWN
    assert "warMode == 4" in SPAWN


if __name__ == "__main__":
    run_checks()
    print("Nitmod war-mode command checks passed")
