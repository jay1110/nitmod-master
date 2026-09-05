from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CMDS = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
CVARS = (ROOT / "src_2.60/game/g_nitmod_legacy_cvars.c").read_text(encoding="utf-8")
CLIENT = (ROOT / "src_2.60/game/g_client.c").read_text(encoding="utf-8")


def test_comma_separated_censor_rewrites_chat():
    assert "*cursor == ','" in CVARS
    assert "Q_stricmpn(scan,word,length)" in CVARS
    assert "memset(scan,'*',length)" in CVARS
    assert 'G_NITMOD_CensorText("g_censor", text, sizeof(text))' in CMDS


def test_typed_penalties_are_applied():
    assert 'G_NITMOD_LegacyCvarInteger("g_censorPenalty", 1)' in CMDS
    assert 'G_NITMOD_LegacyCvarInteger("g_censorMuteTime", 0)' in CMDS
    assert "G_NITMOD_SetClientMute(ent, qtrue, duration)" in CMDS
    assert "G_LoseSkillPoints(ent, skill, 10.f)" in CMDS
    assert "ent->client->ps.eFlags |= NITMOD_EF_POISONED" in CMDS
    assert "G_BurnMeGood(ent, ent)" in CMDS
    assert "G_Damage(ent, ent, ent" in CMDS
    assert "if( playable && (penalty & 1) )" in CMDS
    assert "else if( playable && (penalty & 4) )" in CMDS
    assert "void G_NITMOD_LegacyCvarString" in CVARS


def test_censored_names_are_masked_or_rejected_by_penalty_bit_two():
    assert CLIENT.count('G_NITMOD_CensorText("g_censorNames"') == 2
    assert 'G_NITMOD_LegacyCvarInteger("g_censorPenalty", 1) & 2' in CLIENT
    assert 'trap_DropClient(clientNum, "Name censor. Please change your name.", 0)' in CLIENT


if __name__ == "__main__":
    test_comma_separated_censor_rewrites_chat()
    test_typed_penalties_are_applied()
    test_censored_names_are_masked_or_rejected_by_penalty_bit_two()
    print("nitmod censor runtime checks passed")
