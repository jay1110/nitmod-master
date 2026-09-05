from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CMDS = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
LOCAL = (ROOT / "src_2.60/game/g_local.h").read_text(encoding="utf-8")


def test_all_original_flood_cvars_drive_runtime():
    for name in ("g_floodprotect", "g_floodthreshold", "g_floodWait"):
        assert f'G_NITMOD_LegacyCvarInteger("{name}"' in CMDS
    for field in ("nitmodFloodNextTime", "nitmodFloodWindowTime", "nitmodFloodCount"):
        assert field in LOCAL


def test_text_and_voice_commands_share_gate():
    say = CMDS[CMDS.index("void Cmd_Say_f"):CMDS.index("extern void BotRecordVoiceChat")]
    voice = CMDS[CMDS.index("static void Cmd_Voice_f"):]
    assert "G_NITMOD_ClientIsFlooding(ent)" in say
    assert "G_NITMOD_ClientIsFlooding(ent)" in voice
    assert "30000" in CMDS and "level.time + 500" in CMDS


if __name__ == "__main__":
    test_all_original_flood_cvars_drive_runtime()
    test_text_and_voice_commands_share_gate()
    print("nitmod flood runtime checks passed")
