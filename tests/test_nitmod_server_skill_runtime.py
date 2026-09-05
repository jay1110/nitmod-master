from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
STATS = (ROOT / "src_2.60/game/g_stats.c").read_text(encoding="utf-8")
CLIENT = (ROOT / "src_2.60/game/g_client.c").read_text(encoding="utf-8")
CONFIG = (ROOT / "src_2.60/game/g_nitmod_config.c").read_text(encoding="utf-8")


def test_server_uses_all_threshold_and_maximum_cvars():
    for name in ("skill_battlesense", "skill_engineer", "skill_medic", "skill_fieldops",
                 "skill_lightweapons", "skill_soldier", "skill_covertops",
                 "g_maxLevelBattleSense", "g_maxLevelEngineer", "g_maxLevelMedic",
                 "g_maxLevelFieldOp", "g_maxLevelLightWeapons", "g_maxLevelSoldier",
                 "g_maxLevelCovertOp"):
        assert f'"{name}"' in STATS
    assert '"n_noSkillUpgrades"' in STATS


def test_independent_unlock_masks_reach_player_info():
    assert "client->sess.nitmodSkillMasks[i]" in CLIENT
    assert "\\\\xp\\\\%s" in CLIENT
    assert "progress.unlocked" in STATS


def test_threshold_rows_are_sent_after_capability_negotiation():
    capability = CONFIG[CONFIG.index("void G_NITMOD_ClientCapabilities"):]
    capability = capability[:capability.index("const char *G_NITMOD_ConfigString")]
    assert "nitmod_SendSkillLevels( clientNum )" in capability
    assert 'trap_SendServerCommand(clientNum, va("sl %s", info))' in CONFIG
