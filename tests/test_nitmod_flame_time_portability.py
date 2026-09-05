from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FLAME = (ROOT / "src_2.60/cgame/cg_flamethrower.c").read_text(encoding="utf-8")


def test_flame_chunk_timestamps_stay_integer_on_wasm():
    assert "abs(f->timeStart - fNext->timeStart) < 100" in FLAME
    assert "fabs(f->timeStart - fNext->timeStart)" not in FLAME


if __name__ == "__main__":
    test_flame_chunk_timestamps_stay_integer_on_wasm()
    print("nitmod flame timestamp portability checks passed")
