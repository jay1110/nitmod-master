from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def text(path: str) -> str:
    return (ROOT / path).read_text(encoding="utf-8", errors="replace")


def main() -> None:
    public = text("src_2.60/game/bg_public.h")
    main_c = text("src_2.60/game/g_main.c")
    local = text("src_2.60/game/g_local.h")
    match = text("src_2.60/game/g_match.c")
    load = text("src_2.60/cgame/cg_loadpanel.c")
    window = text("src_2.60/cgame/cg_window.c")
    legacy = text("src_2.60/game/g_nitmod_legacy_cvars.c")

    assert "#define MAX_MOTDLINES\t7" in public
    assert '"server_motd6", ""' in main_c
    assert "extern vmCvar_t\t\tserver_motd6;" in local
    assert "CS_CUSTMOTD + 6, server_motd6.string" in match
    assert "for(i = 0; i < 7; ++i)" in load
    assert "i<MAX_MOTDLINES" in window
    assert '"server_motd6"' not in legacy
    print("nitmod seven-line MOTD layout: ok")


if __name__ == "__main__":
    main()
