from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_default_mute_drives_vote_duration_and_expires():
    cmds = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
    vote = (ROOT / "src_2.60/game/g_vote.c").read_text(encoding="utf-8")
    local = (ROOT / "src_2.60/game/g_local.h").read_text(encoding="utf-8")

    assert "nitmodMuteUntil" in local
    assert "level.time >= ent->client->nitmodMuteUntil" in cmds
    assert "G_NITMOD_SetClientMute" in cmds
    assert "if(durationSeconds > 2147483) durationSeconds = 2147483;" in cmds
    assert 'G_NITMOD_LegacyCvarInteger("g_defaultMute", 3600)' in vote
    assert "if(duration < 60) duration = 60;" in vote
    assert "G_NITMOD_SetClientMute(&g_entities[pid], qtrue, duration);" in vote


if __name__ == "__main__":
    test_default_mute_drives_vote_duration_and_expires()
