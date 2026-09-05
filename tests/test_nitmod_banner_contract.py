from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SERVER = (ROOT / "src_2.60/game/g_nitmod_banners.c").read_text(encoding="utf-8")
MAIN = (ROOT / "src_2.60/game/g_main.c").read_text(encoding="utf-8")
CLIENT = (ROOT / "src_2.60/cgame/cg_nitmod_config.c").read_text(encoding="utf-8")


def test_banner_cvars_have_runtime_consumers():
    assert 'G_NITMOD_LegacyCvarInteger("g_msgs", 0)' in SERVER
    assert 'G_NITMOD_LegacyCvarInteger("g_msgpos", 0)' in SERVER
    assert 'va("g_msg%i", bannerIndex)' in SERVER
    assert 'va("bp %i \\"%s\\"", position, message)' in SERVER


def test_banner_lifecycle_and_client_protocol_are_connected():
    assert "G_NITMOD_BannersReset();" in MAIN
    assert "G_NITMOD_BannersRunFrame();" in MAIN
    assert 'if(!strcmp(command, "bp"))' in CLIENT
    assert "NITMOD_DrawBanner(void)" in CLIENT


def test_top_centre_banner_uses_centred_widescreen_viewport():
    draw = CLIENT[CLIENT.index("void NITMOD_DrawBanner(void)"):]
    draw = draw[:draw.index("static sfxHandle_t nitmodPrivateMessageSound")]
    assert "CG_NitmodHudAnchor(NITMOD_HUD_CENTER)" in draw
    assert "CG_NitmodHudAnchor(previous);" in draw
