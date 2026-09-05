from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_slash_kill_ports_typed_original_guards():
    source = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
    start = source.index("void Cmd_Kill_f")
    end = source.index("void BotRecordTeamChange", start)
    function = source[start:end]

    assert "if(ent->health <= 0)" in function
    assert "limbo(ent, qtrue);" in function
    assert "g_gametype.integer == 8" in function
    assert "g_DMOptions.integer & 4" in function
    assert "g_gametype.integer == 7" in function
    assert 'G_NITMOD_LegacyCvarInteger("g_TDMOptions", 0) & 2' in function
    assert 'G_NITMOD_LegacyCvarInteger("g_slashKill", 0)' in function
    assert "if(slashKill & 8)" in function
    assert "Selfkill disabled on this server" in function
    assert "if((slashKill & 16)" in function
    assert "NITMOD_EF_POISONED" in function
    assert "if((slashKill & 64)" in function
    assert "nitmodLastHurtTime" in function
    assert "< 3000" in function
    assert 'G_NITMOD_LegacyCvarInteger("g_fear", 2000)' in function
    assert "attackerNum >= 0 && attackerNum < level.maxclients" in function
    assert "candidate->client->sess.sessionTeam != ent->client->sess.sessionTeam" in function
    assert "player_die(ent, fearAttacker, fearAttacker, 150, MOD_SWAP_PLACES);" in function
    assert "MOD_SUICIDE" in function

    combat = (ROOT / "src_2.60/game/g_combat.c").read_text(encoding="utf-8")
    assert "targ->client->nitmodLastHurtTime = level.time;" in combat


if __name__ == "__main__":
    test_slash_kill_ports_typed_original_guards()
