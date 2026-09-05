from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_ui_and_sound_inputs_cannot_corrupt_wasm_state():
    ui = (ROOT / "src_2.60/ui/ui_shared.c").read_text(encoding="utf-8")
    sound = (ROOT / "src_2.60/cgame/cg_sound.c").read_text(encoding="utf-8")
    view = (ROOT / "src_2.60/cgame/cg_nitmod_view.h").read_text(encoding="utf-8")
    public = (ROOT / "src_2.60/game/bg_public.h").read_text(encoding="utf-8")
    assert "amt <= 0.0f" in ui
    assert ui.count("fabsf(rectTo.") >= 4
    assert "numSounds >= MAX_SOUND_FILES - 1" in sound
    assert 'MAX_QPATH, "%s", token' in sound
    assert "len >= sizeof(bigTextBuffer)" in sound
    assert "#define NITMOD_EF_POISONED" not in view
    assert "#define NITMOD_EF_POISONED" in public


if __name__ == "__main__":
    test_ui_and_sound_inputs_cannot_corrupt_wasm_state()
