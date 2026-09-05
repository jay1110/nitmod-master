from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_dropobj_is_forwarded_and_has_authoritative_typed_consumer():
    cgame = (ROOT / "src_2.60/cgame/cg_consolecmds.c").read_text(encoding="utf-8")
    game = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
    local = (ROOT / "src_2.60/game/g_local.h").read_text(encoding="utf-8")
    start = game.index("static void G_NITMOD_DropObjective_f")
    end = game.index("void BotRecordTeamChange", start)
    function = game[start:end]

    assert 'trap_AddCommand ("dropobj");' in cgame
    assert '!Q_stricmp(cmd, "dropobj")' in game
    assert 'G_NITMOD_LegacyCvarInteger("g_dropObj", 0)' in function
    assert 'PW_REDFLAG' in function and 'PW_BLUEFLAG' in function
    assert 'VectorMA(ent->client->ps.origin, 36.0f, forward, origin);' in function
    assert 'VectorScale(forward, 96.0f, velocity);' in function
    assert 'LaunchItem(item, origin, velocity, ent->s.number)' in function
    assert 'int nitmodObjectiveDrops;' in local


if __name__ == "__main__":
    test_dropobj_is_forwarded_and_has_authoritative_typed_consumer()
