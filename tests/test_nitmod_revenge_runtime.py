from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
COMBAT = (ROOT / "src_2.60/game/g_combat.c").read_text(encoding="utf-8")
CG_HUD = (ROOT / "src_2.60/cgame/cg_nitmod_hud.c").read_text(encoding="utf-8")
CG_COMMANDS = (ROOT / "src_2.60/cgame/cg_servercmds.c").read_text(encoding="utf-8")


def test_server_revenge_uses_typed_kill_history_and_battle_sense():
    assert 'G_NITMOD_LegacyCvarInteger("g_revenge", 0)' in COMBAT
    assert "nitmodLastKillerClient == victimNum" in COMBAT
    assert 'trap_SendServerCommand(attackerNum, "an -2 1")' in COMBAT
    assert "G_AddSkillPoints(attacker, SK_BATTLE_SENSE, 1.f)" in COMBAT
    assert "nitmodLastKillerClient = -1" in COMBAT


def test_original_client_announcement_path_accepts_revenge():
    assert 'case -2: text = "REVENGE!"' in CG_HUD
    assert '!Q_stricmp( cmd, "an" )' in CG_COMMANDS
    assert "CG_NitmodSpecialAnnouncement(type, xp)" in CG_COMMANDS


if __name__ == "__main__":
    test_server_revenge_uses_typed_kill_history_and_battle_sense()
    test_original_client_announcement_path_accepts_revenge()
    print("nitmod revenge runtime checks passed")
