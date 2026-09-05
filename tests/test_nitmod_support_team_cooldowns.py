from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
WEAPON = (ROOT / "src_2.60/game/g_weapon.c").read_text(encoding="utf-8")
MAIN = (ROOT / "src_2.60/game/g_main.c").read_text(encoding="utf-8")
LOCAL = (ROOT / "src_2.60/game/g_local.h").read_text(encoding="utf-8")


def test_support_cooldowns_are_separate_and_team_scoped():
    assert "nitmodAirstrikeCounter[2]" in LOCAL
    assert "nitmodArtilleryCounter[2]" in LOCAL
    assert 'G_NITMOD_LegacyCvarInteger("team_airstrikeTime", 10)' in WEAPON
    assert 'G_NITMOD_LegacyCvarInteger("team_artyTime", 10)' in WEAPON
    assert "team - TEAM_AXIS" in WEAPON


def test_artillery_does_not_consume_airstrike_availability():
    start = WEAPON.index("void Weapon_Artillery")
    body = WEAPON[start:]
    assert "G_NITMOD_AvailableArtillery( ent )" in body
    assert "G_NITMOD_AddArtilleryCounter( ent )" in body


def test_all_four_counters_decay_and_clamp_each_frame():
    assert "level.nitmodAirstrikeCounter[teamIndex] -= msec" in MAIN
    assert "level.nitmodArtilleryCounter[teamIndex] -= msec" in MAIN
    assert "level.nitmodAirstrikeCounter[teamIndex] = 0" in MAIN
    assert "level.nitmodArtilleryCounter[teamIndex] = 0" in MAIN


if __name__ == "__main__":
    test_support_cooldowns_are_separate_and_team_scoped()
    test_artillery_does_not_consume_airstrike_availability()
    test_all_four_counters_decay_and_clamp_each_frame()
    print("Nitmod team support cooldown checks passed")
