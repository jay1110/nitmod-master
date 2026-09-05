from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/cgame/cg_predict.c").read_text(encoding="utf-8")


def test_fast_solids_is_live_and_bounded():
    assert "if(cg_fastSolids.integer)" in SOURCE
    assert SOURCE.count("cg_numSolidEntities < MAX_ENTITIES_IN_SNAPSHOT") >= 2
    assert SOURCE.count("cg_numSolidFTEntities < MAX_ENTITIES_IN_SNAPSHOT") >= 2


def test_inline_midpoint_index_is_validated():
    assert "cent->currentState.modelindex > 0" in SOURCE
    assert "cent->currentState.modelindex < MAX_MODELS" in SOURCE
    assert "DotProduct( vec, vec )" in SOURCE
    assert "(512 * 512)" in SOURCE

