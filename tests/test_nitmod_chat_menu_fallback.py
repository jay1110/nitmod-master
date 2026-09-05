from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_message_popup_keeps_original_menu_and_has_localhost_fallback():
    source = (ROOT / "src_2.60/ui/ui_main.c").read_text(encoding="utf-8")
    start = source.index("case UIMENU_INGAME_MESSAGEMODE:")
    block = source[start : source.index("default:", start)]

    assert '"ingame_messagemode"' in block
    assert "Menus_FindByName(menuName)" in block
    assert 'menuName = "ingame_messagemode4";' in block
    assert "Menus_OpenByName(menuName);" in block


if __name__ == "__main__":
    test_message_popup_keeps_original_menu_and_has_localhost_fallback()
