from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def source(name):
    return (ROOT / "src_2.60/cgame" / name).read_text(encoding="utf-8")


def test_hud_and_menu_controls_have_runtime_consumers():
    draw = source("cg_draw.c")
    console = source("cg_consolecmds.c")
    main = source("cg_main.c")
    assert "cg_drawCompass.integer" in draw
    assert "cg_popupLimboMenu.integer" in draw
    assert "cg_descriptiveText.integer" in draw
    assert "cg_drawNotifyText.integer" in main
    assert "cg_quickMessageAlt.integer" in console
    assert "cg_specHelp.integer" in console


def test_gameplay_feedback_controls_have_runtime_consumers():
    assert "cg_announcer.integer" in source("cg_nitmod_hud.c")
    assert "cg_autoReload.integer" in source("cg_playerstate.c")
    assert "cg_noAmmoAutoSwitch.integer" in source("cg_event.c")
    assert "cg_printObjectiveInfo.integer" in source("cg_servercmds.c")
    assert "cg_useScreenshotJPEG.integer" in source("cg_consolecmds.c")


if __name__ == "__main__":
    test_hud_and_menu_controls_have_runtime_consumers()
    test_gameplay_feedback_controls_have_runtime_consumers()
    print("nitmod client control cvar checks passed")
