from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CG_CONFIG = (ROOT / "src_2.60/cgame/cg_nitmod_config.c").read_text(encoding="utf-8")
CG_NAMES = (ROOT / "src_2.60/cgame/cg_nitmod_names.c").read_text(encoding="utf-8")
CG_HUD = (ROOT / "src_2.60/cgame/cg_nitmod_hud.c").read_text(encoding="utf-8")
UI_BROWSER = (ROOT / "src_2.60/ui/ui_nitmod_browser.c").read_text(encoding="utf-8")
UI_SEARCH = (ROOT / "src_2.60/ui/ui_nitmod_search.c").read_text(encoding="utf-8")
UI_MAIN = (ROOT / "src_2.60/ui/ui_main.c").read_text(encoding="utf-8")
UI_SETTINGS = (ROOT / "src_2.60/ui/ui_nitmod_settings.c").read_text(encoding="utf-8")
UI_SHARED = (ROOT / "src_2.60/ui/ui_shared.c").read_text(encoding="utf-8")


def test_cgame_runtime_cvars_have_real_consumers():
    assert "trap_Cvar_Update(&cg_noGreetingSounds)" in CG_CONFIG
    assert "cg_noGreetingSounds.integer" in CG_CONFIG
    assert "trap_Cvar_Update(&cg_drawBanners)" in CG_CONFIG
    assert "cg_drawBanners.integer" in CG_CONFIG
    assert "cg_woundedNames.integer" in CG_NAMES
    assert "cg_drawHUDStats.integer" in CG_HUD


def test_ui_browser_filters_have_runtime_consumers():
    assert "trap_Cvar_Update( &ui_browserNitmodonly )" in UI_BROWSER
    assert "ui_browserNitmodonly.integer == 2" in UI_BROWSER
    assert "trap_Cvar_Update( &ui_browserNxAConly )" in UI_BROWSER
    assert "ui_browserNxAConly.integer == 2" in UI_BROWSER


def test_ui_standard_server_filters_and_timeout_have_runtime_consumers():
    for name in (
        "ui_browserShowEmptyOrFull", "ui_browserShowPasswordProtected",
        "ui_browserShowFriendlyFire", "ui_browserShowMaxlives",
        "ui_browserShowPunkBuster", "ui_browserShowAntilag",
        "ui_browserShowWeaponsRestricted", "ui_browserShowTeamBalanced",
    ):
        assert f"trap_Cvar_Update( &{name} )" in UI_BROWSER
        assert f"{name}.integer" in UI_BROWSER
    assert "ui_serverStatusTimeOut.integer" in UI_SEARCH


def test_ui_profile_rate_and_redirect_cvars_have_runtime_consumers():
    assert 'trap_Cvar_VariableValue("ui_rate")' in UI_SETTINGS
    assert 'UI_ProfileSelector("ui_handedness"' in UI_SETTINGS
    assert 'UI_ProfileSelector("ui_profile_mousePitch"' in UI_SETTINGS
    assert "UI_NitmodRedirectAddress(buf, buf, sizeof(buf))" in UI_MAIN
    assert "switch( ui_autoredirect.integer )" in UI_MAIN


def test_ui_profile_persistence_and_tooltips_have_runtime_consumers():
    assert 'trap_Cvar_Set( "ui_profile", uiInfo.profileList[index].name )' in UI_MAIN
    assert 'DC->getCVarString( "ui_profile", ui_profileStr' in UI_SHARED
    assert '"profiles/%s/profile.dat"' in UI_SHARED
    assert 'DC->getCVarValue( "ui_showtooltips" )' in UI_SHARED


if __name__ == "__main__":
    test_cgame_runtime_cvars_have_real_consumers()
    test_ui_browser_filters_have_runtime_consumers()
    test_ui_standard_server_filters_and_timeout_have_runtime_consumers()
    test_ui_profile_rate_and_redirect_cvars_have_runtime_consumers()
    test_ui_profile_persistence_and_tooltips_have_runtime_consumers()
    print("nitmod cgame/ui runtime cvar checks passed")
