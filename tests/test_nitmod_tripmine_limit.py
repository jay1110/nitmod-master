from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_weapon.c").read_text(encoding="utf-8")
MAIN = (ROOT / "src_2.60/game/g_main.c").read_text(encoding="utf-8")
CG_DRAW = (ROOT / "src_2.60/cgame/cg_draw.c").read_text(encoding="utf-8")


def test_tripmine_limit_is_checked_before_spawn():
    function = SOURCE[SOURCE.index("void G_PlaceTripmine"):SOURCE.index("/*void Weapon_SatchelCharge")]
    assert function.index('G_NITMOD_LegacyCvarInteger("team_maxTripmines", 5)') < function.index("bomb = G_Spawn()")
    assert "teamLimit <= G_NITMOD_CountTeamTripmines(team)" in function


def test_tripmine_count_and_entity_use_typed_team_state():
    assert "mine->s.weapon == WP_TRIPMINE && mine->s.teamNum == team" in SOURCE
    assert "bomb->s.teamNum = team;" in SOURCE


def test_remaining_slots_are_published_on_original_game_manager_fields():
    assert 'level.gameManager->s.time = G_NITMOD_LegacyCvarInteger("team_maxTripmines", 5)' in MAIN
    assert "G_NITMOD_CountTeamTripmines(TEAM_AXIS)" in MAIN
    assert 'level.gameManager->s.time2 = G_NITMOD_LegacyCvarInteger("team_maxTripmines", 5)' in MAIN
    assert "G_NITMOD_CountTeamTripmines(TEAM_ALLIES)" in MAIN


def test_client_hud_consumes_team_tripmine_slots():
    branch = CG_DRAW[CG_DRAW.index("} else if( weap == WP_TRIPMINE )"):
                     CG_DRAW.index("} else if( weap == WP_MORTAR", CG_DRAW.index("} else if( weap == WP_TRIPMINE )"))]
    assert "currentState.time;" in branch
    assert "currentState.time2;" in branch
    assert "TEAM_AXIS" in branch
    skip_switch = CG_DRAW[CG_DRAW.index("switch(weap)"):CG_DRAW.index("// total ammo in clips")]
    assert "case WP_TRIPMINE:" in skip_switch


if __name__ == "__main__":
    test_tripmine_limit_is_checked_before_spawn()
    test_tripmine_count_and_entity_use_typed_team_state()
    test_remaining_slots_are_published_on_original_game_manager_fields()
    test_client_hud_consumes_team_tripmine_slots()
    print("nitmod tripmine team-limit tests passed")
