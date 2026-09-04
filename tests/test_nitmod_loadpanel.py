from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
UI_LOADPANEL = ROOT / "src_2.60" / "ui" / "ui_loadpanel.c"
CG_LOADPANEL = ROOT / "src_2.60" / "cgame" / "cg_loadpanel.c"


def test_ui_loadpanel_ports_original_download_states_and_bounds():
    source = UI_LOADPANEL.read_text(encoding="utf-8")

    assert "cstate.connState == CA_DISCONNECTED" in source
    assert "cstate.connState == CA_CONNECTED" in source
    assert "fraction < 0.f" in source
    assert "fraction > 1.f" in source
    assert 'trap_Cvar_VariableValue( "cl_downloadSize" )' in source
    assert 'trap_Cvar_VariableValue( "cl_downloadCount" )' in source
    assert 'return va( "File: \'%s\'\\nSpeed: %s/s' in source
    assert '"Estimating download time for \'%s\'..."' in source


def test_ui_loadpanel_clears_physical_viewport_and_handles_widescreen():
    source = UI_LOADPANEL.read_text(encoding="utf-8")

    assert "uiInfo.uiDC.glconfig.vidWidth" in source
    assert "uiInfo.uiDC.glconfig.vidHeight" in source
    assert "UI_NitmodWideXOffset" in source
    assert "UI_NitmodDrawDownloadBar" in source


def test_cgame_loadpanel_has_all_original_nitmod_gametypes():
    source = CG_LOADPANEL.read_text(encoding="utf-8")

    assert 'case 6: return "Map Voting";' in source
    assert 'case 7: return "Team Death Match";' in source
    assert 'case 8: return "Death Match";' in source


if __name__ == "__main__":
    test_ui_loadpanel_ports_original_download_states_and_bounds()
    test_ui_loadpanel_clears_physical_viewport_and_handles_widescreen()
    test_cgame_loadpanel_has_all_original_nitmod_gametypes()
