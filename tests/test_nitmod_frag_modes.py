from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_extended_gametypes_are_shared_by_all_modules():
    public = (ROOT / "src_2.60/game/bg_public.h").read_text(encoding="utf-8")
    block = public.split("typedef enum {", 1)[1].split("} gametype_t;", 1)[0]
    assert block.index("GT_WOLF_MAPVOTE") < block.index("GT_WOLF_TDM")
    assert block.index("GT_WOLF_TDM") < block.index("GT_WOLF_DM")
    assert block.index("GT_WOLF_DM") < block.index("GT_MAX_GAME_TYPE")


def test_tdm_and_dm_exit_rules_consume_original_cvars():
    source = (ROOT / "src_2.60/game/g_main.c").read_text(encoding="utf-8")
    rules = source.split("void CheckExitRules( void )", 1)[1].split(
        "FUNCTIONS CALLED EVERY FRAME", 1
    )[0]
    assert 'G_NITMOD_LegacyCvarInteger("g_TDMScore", 500)' in rules
    assert "level.teamScores[TEAM_AXIS] >= limit" in rules
    assert "level.teamScores[TEAM_ALLIES] >= limit" in rules
    assert 'G_NITMOD_LegacyCvarInteger("g_DMFragLimit", 25)' in rules
    assert "client->sess.game_points < limit" in rules
    assert 'trap_SendServerCommand(-1, va("DM %i", i))' in rules
    assert 'Info_SetValueForKey(cs, "winner", "-1")' in rules


def test_tdm_map_objective_bonus_is_applied_before_exit_check():
    source = (ROOT / "src_2.60/game/g_script_actions.c").read_text(encoding="utf-8")
    endround = source.split("qboolean G_ScriptAction_EndRound", 1)[1].split(
        "G_ScriptAction_SetRoundTimelimit", 1
    )[0]
    assert "g_gametype.integer == GT_WOLF_TDM" in endround
    assert 'G_NITMOD_LegacyCvarInteger("g_TDMObjBonus", 100)' in endround
    assert "level.teamScores[winner == 0 ? TEAM_AXIS : TEAM_ALLIES] += bonus" in endround
    assert "nitmod_TeamScores()" in endround


if __name__ == "__main__":
    test_extended_gametypes_are_shared_by_all_modules()
    test_tdm_and_dm_exit_rules_consume_original_cvars()
    test_tdm_map_objective_bonus_is_applied_before_exit_check()
    print("Nitmod extended frag-mode runtime contract passed")
