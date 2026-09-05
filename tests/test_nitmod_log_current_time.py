from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
MAIN = (ROOT / "src_2.60/game/g_main.c").read_text(encoding="utf-8")


def test_log_current_time_selects_wall_clock_prefix():
    start = MAIN.index("void QDECL G_LogPrintf")
    end = MAIN.index("void QDECL G_LogPrintf", start + 1)
    block = MAIN[start:end]
    assert 'G_NITMOD_LegacyCvarInteger("n_LogCurrentTime", 0)' in block
    assert "trap_RealTime(&realTime)" in block
    assert '"%02i:%02i:%02i "' in block


def test_elapsed_match_time_remains_the_default():
    start = MAIN.index("void QDECL G_LogPrintf")
    end = MAIN.index("void QDECL G_LogPrintf", start + 1)
    block = MAIN[start:end]
    assert "sec = level.time / 1000" in block
    assert '"%i:%i%i "' in block

