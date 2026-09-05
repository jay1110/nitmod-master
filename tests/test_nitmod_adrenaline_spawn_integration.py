from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CLIENT = (ROOT / "src_2.60/game/g_client.c").read_text(encoding="utf-8")

def test_spawn_loadout_calls_typed_adrenaline_grant():
    start = CLIENT.index("void SetWolfSpawnWeapons")
    end = CLIENT.index("int G_CountTeamMedics", start)
    spawn = CLIENT[start:end]
    assert "G_NITMOD_GrantAdrenalineSpawn(client, G_NITMOD_FirstAidUnlocks(client)" in spawn
    assert 'G_NITMOD_LegacyCvarInteger("g_adrenClasses", 2)' in spawn
    assert 'G_NITMOD_LegacyCvarInteger("g_adrenaline", 0)' in spawn
    assert "G_NITMOD_ConfiguredWarMode()" in spawn

def test_skill_levels_are_converted_to_original_unlock_bits():
    abilities = (ROOT / "src_2.60/game/g_nitmod_abilities.c").read_text(encoding="utf-8")
    assert "skill[SK_FIRST_AID] >= 2 ) unlocks |= 4u" in abilities
    assert "skill[SK_FIRST_AID] >= 4 ) unlocks |= 16u" in abilities

def test_live_client_think_revokes_ineligible_adrenaline():
    active = (ROOT / "src_2.60/game/g_active.c").read_text(encoding="utf-8")
    assert "G_NITMOD_CheckAdrenaline(ent, qfalse, G_NITMOD_FirstAidUnlocks(client)" in active
    assert 'G_NITMOD_LegacyCvarInteger("g_adrenClasses", 2)' in active

if __name__ == "__main__":
    test_spawn_loadout_calls_typed_adrenaline_grant()
    test_skill_levels_are_converted_to_original_unlock_bits()
    test_live_client_think_revokes_ineligible_adrenaline()
    print("nitmod adrenaline spawn integration tests passed")
