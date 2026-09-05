from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_missile.c").read_text(encoding="utf-8")


def test_mortar_bbox_matches_original_two_unit_trace_box():
    block = SOURCE[SOURCE.index("case WP_MORTAR_SET:"):]
    block = block[:block.index("case WP_LANDMINE:")]
    assert 'G_NITMOD_LegacyCvarInteger("g_mortarBBox", 0)' in block
    assert "VectorSet(bolt->r.mins, -2, -2, -2)" in block
    assert "VectorSet(bolt->r.maxs, 2, 2, 2)" in block
    assert "VectorCopy(bolt->r.mins, bolt->r.absmin)" in block
    assert "VectorCopy(bolt->r.maxs, bolt->r.absmax)" in block
