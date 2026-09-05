from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SVCMDS = (ROOT / "src_2.60" / "game" / "g_svcmds.c").read_text(encoding="utf-8")
MAIN = (ROOT / "src_2.60" / "game" / "g_main.c").read_text(encoding="utf-8")


def run_checks() -> None:
    assert 'Q_stricmp( cmd, "crazygravity" ) == 0' in SVCMDS
    assert "trap_Argc() != 2" in SVCMDS
    assert "value[1]" in SVCMDS
    assert "value[0] != '0' && value[0] != '1'" in SVCMDS
    assert 'trap_Cvar_Set( "n_crazyGravity", value )' in SVCMDS
    assert "^xcrazygravity: ^2Enabled !" in SVCMDS
    assert "^xcrazygravity: ^1Disabled!" in SVCMDS
    assert 'G_NITMOD_LegacyCvarInteger("n_crazyGravity", 0)' in MAIN
    assert 'trap_Cvar_Set("g_gravity", "800")' in MAIN


if __name__ == "__main__":
    run_checks()
    print("Nitmod crazy-gravity command checks passed")
