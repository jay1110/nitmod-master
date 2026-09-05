from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
STATS = (ROOT / "src_2.60" / "game" / "g_stats.c").read_text(encoding="utf-8")
MAIN = (ROOT / "src_2.60" / "game" / "g_main.c").read_text(encoding="utf-8")
CMDS = (ROOT / "src_2.60" / "game" / "g_cmds.c").read_text(encoding="utf-8")
MAPVOTE = (ROOT / "src_2.60" / "game" / "g_nitmod_mapvote.c").read_text(encoding="utf-8")


def test_tdm_frag_score_is_separate_from_xp_score():
    assert 'G_NITMOD_LegacyCvarInteger("g_TDMOptions", 0) & 1' in STATS
    assert "level.teamScores[team]++" in STATS
    assert "level.teamScores[ ent->client->ps.persistant[PERS_TEAM] ] += points" in STATS


def test_tdm_timelimit_requires_option_bit_16():
    assert 'G_NITMOD_LegacyCvarInteger("g_TDMOptions", 0) & 16' in MAIN
    assert "g_gametype.integer != GT_WOLF_TDM" in MAIN


def test_existing_tdm_selfkill_and_mapvote_bits_remain_wired():
    assert 'G_NITMOD_LegacyCvarInteger("g_TDMOptions", 0) & 2' in CMDS
    assert 'G_NITMOD_LegacyCvarInteger("g_TDMOptions", 0) & 8' in MAPVOTE


if __name__ == "__main__":
    test_tdm_frag_score_is_separate_from_xp_score()
    test_tdm_timelimit_requires_option_bit_16()
    test_existing_tdm_selfkill_and_mapvote_bits_remain_wired()
    print("Nitmod TDM option runtime checks passed")
