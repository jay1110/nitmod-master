from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_animation_records_are_fully_initialized():
    animation = (ROOT / "src_2.60/game/bg_animation.c").read_text(encoding="utf-8")
    character = (ROOT / "src_2.60/game/g_character.c").read_text(encoding="utf-8")
    local = (ROOT / "src_2.60/cgame/cg_local.h").read_text(encoding="utf-8")
    assert "memset( result, 0, sizeof(int) * 2 )" in animation
    assert "memset( command, 0, sizeof(*command) )" in animation
    assert "memset( *animModelInfo, 0, sizeof(**animModelInfo) )" in character
    assert "cgameEvent_t eventHandling" in local
    assert "qboolean eventHandling" not in local


if __name__ == "__main__":
    test_animation_records_are_fully_initialized()
