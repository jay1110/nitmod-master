from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
PMOVE = (ROOT / "src_2.60/game/bg_pmove.c").read_text(encoding="utf-8")
UI = (ROOT / "src_2.60/ui/ui_shared.c").read_text(encoding="utf-8")


def test_attack2_uses_wbuttons_for_nitmod_actions():
    assert "pm->cmd.wbuttons & WBUTTON_ATTACK2" in PMOVE
    assert "PM_NitmodThrowKnife()) return" in PMOVE


def test_primary_fire_does_not_mix_button_namespaces():
    assert "pm->cmd.buttons & (BUTTON_ATTACK | WBUTTON_ATTACK2)" not in PMOVE
    assert "!(pm->cmd.buttons & BUTTON_ATTACK)" in PMOVE


def test_ui_exposes_attack2_binding():
    assert '{ "+attack2",\tK_MOUSE2' in UI


if __name__ == "__main__":
    test_attack2_uses_wbuttons_for_nitmod_actions()
    test_primary_fire_does_not_mix_button_namespaces()
    test_ui_exposes_attack2_binding()
    print("nitmod attack2 input tests passed")
