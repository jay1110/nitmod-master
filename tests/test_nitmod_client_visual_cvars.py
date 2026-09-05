from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
WEAPONS = (ROOT / "src_2.60/cgame/cg_weapons.c").read_text(encoding="utf-8")
HUD = (ROOT / "src_2.60/cgame/cg_nitmod_hud.c").read_text(encoding="utf-8")
POPUPS = (ROOT / "src_2.60/cgame/cg_popupmessages.c").read_text(encoding="utf-8")
EVENTS = (ROOT / "src_2.60/cgame/cg_nitmod_events.c").read_text(encoding="utf-8")


def test_weapon_effect_controls_are_consumed():
    assert "CG_NitmodMuzzleFlashEnabled(cg_muzzleFlash.integer, ps)" in WEAPONS
    assert "CG_NitmodTracerEnabled(cg_tracers.integer" in WEAPONS


def test_hud_and_popup_controls_are_consumed():
    for token in ("cg_drawspeed.integer", "cg_speedunit.integer", "cg_speedinterval.integer"):
        assert token in HUD
    for token in ("cg_numPopups.integer", "cg_popupFadeTime.integer", "cg_HUDFlags.integer"):
        assert token in POPUPS or token in HUD
    assert "cg_obituary.integer" in EVENTS


if __name__ == "__main__":
    test_weapon_effect_controls_are_consumed()
    test_hud_and_popup_controls_are_consumed()
    print("nitmod client visual cvar checks passed")
