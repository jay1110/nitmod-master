from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_max_xp_is_consumed_by_authoritative_skill_awards():
    source = (ROOT / "src_2.60/game/g_stats.c").read_text(encoding="utf-8")
    start = source.index("void G_AddSkillPoints")
    end = source.index("void G_LoseKillSkillPoints", start)
    function = source[start:end]

    assert 'G_NITMOD_LegacyCvarInteger("g_maxXP", -1)' in function
    assert "(float)oldScore + points >= (float)maxXP" in function
    assert "memset(ent->client->sess.skillpoints, 0" in function
    assert "memset(ent->client->sess.skill, 0" in function
    assert "ent->client->ps.persistant[PERS_SCORE] = 0;" in function
    assert "level.teamXP[i][ent->client->sess.sessionTeam - TEAM_AXIS] = 0.f;" in function
    assert "if( maxXP != 0 )" in function


if __name__ == "__main__":
    test_max_xp_is_consumed_by_authoritative_skill_awards()
