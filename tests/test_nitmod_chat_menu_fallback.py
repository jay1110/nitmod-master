from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_message_popup_matches_original_nitmod_dispatch():
    source = (ROOT / "src_2.60/ui/ui_main.c").read_text(encoding="utf-8")
    start = source.index("case UIMENU_INGAME_MESSAGEMODE:")
    block = source[start : source.index("default:", start)]

    assert '"ingame_messagemode"' in block
    assert 'trap_Cvar_VariableStringBuffer("cg_messageType"' in block
    assert "atoi(messageType) == 4" in block
    assert 'Menus_OpenByName("ingame_messagemode4");' in block
    assert 'Menus_OpenByName("ingame_messagemode");' in block
    assert "UI_ParseMenu" not in block
    assert "Menus_FindByName" not in block


def test_original_nitmod_menu_capacity_is_preserved():
    shared = (ROOT / "src_2.60/ui/ui_shared.h").read_text(encoding="utf-8")
    assert "#define MAX_MENUS 256" in shared


def test_original_nitmod_ui_memory_capacity_is_preserved():
    shared = (ROOT / "src_2.60/ui/ui_shared.c").read_text(encoding="utf-8")
    assert "#define MEM_POOL_SIZE  2048 * 1024" in shared


if __name__ == "__main__":
    test_message_popup_matches_original_nitmod_dispatch()
    test_original_nitmod_menu_capacity_is_preserved()
    test_original_nitmod_ui_memory_capacity_is_preserved()
