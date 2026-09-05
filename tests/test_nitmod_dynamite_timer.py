from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
CONFIG = (ROOT / "src_2.60/game/g_nitmod_config.c").read_text(encoding="utf-8")
WEAPON = (ROOT / "src_2.60/game/g_weapon.c").read_text(encoding="utf-8")


def test_dynamite_timer_is_clamped_published_and_consumed():
    assert 'G_NITMOD_LegacyCvarInteger("n_dynamiteTimer", 30000)' in CONFIG
    assert "nitrox_ClampInt(&timer, 5000.0f, 60000.0f);" in CONFIG
    assert "simple.dynamiteTimer = G_NITMOD_DynamiteTimer();" in CONFIG
    assert "int dynamiteTimer = G_NITMOD_DynamiteTimer();" in WEAPON
    assert "traceEnt->nextthink = level.time + dynamiteTimer;" in WEAPON
    assert "traceEnt->s.time = dynamiteTimer;" in WEAPON
    assert "dynamiteTimer / 1000" in WEAPON


if __name__ == "__main__":
    test_dynamite_timer_is_clamped_published_and_consumed()
    print("nitmod dynamite timer checks passed")
