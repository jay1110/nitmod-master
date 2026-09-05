from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_client.c").read_text(encoding="utf-8")


def test_minimum_name_length_uses_visible_characters():
    assert "G_NITMOD_VisibleNameLength" in SOURCE
    assert "*name == Q_COLOR_ESCAPE && name[1]" in SOURCE
    assert "*name != ' '" in SOURCE


def test_human_connection_is_rejected_before_session_initialization():
    read = SOURCE.index("minimumNameLength = G_NITMOD_LegacyCvarInteger")
    reset = SOURCE.index("memset( client, 0, sizeof(*client) )", read)
    assert read < reset
    assert "if( !isBot && minimumNameLength > 0 )" in SOURCE[read:reset]
    assert "Your name is too short" in SOURCE[read:reset]


if __name__ == "__main__":
    test_minimum_name_length_uses_visible_characters()
    test_human_connection_is_rejected_before_session_initialization()
    print("nitmod minimum-name checks passed")
