from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_original_nitmod_server_commands_are_registered_for_forwarding():
    source = (ROOT / "src_2.60/cgame/cg_consolecmds.c").read_text(encoding="utf-8")
    init = source[source.index("void CG_InitConsoleCommands( void )"):]
    for command in ("playdead", "dropobj", "damage", "sslogin", "sslogout", "sclogin", "sclogout"):
        assert f'trap_AddCommand ("{command}");' in init
        assert f'{{ "{command}",' not in source


if __name__ == "__main__":
    test_original_nitmod_server_commands_are_registered_for_forwarding()
