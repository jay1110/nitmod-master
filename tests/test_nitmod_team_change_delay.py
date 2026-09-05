from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_team_change_delay_uses_typed_et_timestamp_and_preserves_forced_joins():
    source = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
    start = source.index("qboolean SetTeam(")
    end = source.index("void Cmd_Team_f", start)
    function = source[start:end]

    assert '!force && team != client->sess.sessionTeam' in function
    assert 'client->switchTeamTime > 0' in function
    assert 'G_NITMOD_LegacyCvarInteger("g_teamChangeDelay", 0)' in function
    assert 'level.time - client->switchTeamTime' in function
    assert 'client->switchTeamTime = level.time;' in function


if __name__ == "__main__":
    test_team_change_delay_uses_typed_et_timestamp_and_preserves_forced_joins()
