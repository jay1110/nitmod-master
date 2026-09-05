from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_missile.c").read_text(encoding="utf-8")


def _rocket():
    block = SOURCE[SOURCE.index("gentity_t *fire_rocket"):]
    return block[:block.index("gentity_t *fire_flamebarrel")]


def test_missile_speed_preserves_original_default_and_override():
    block = _rocket()
    assert 'G_NITMOD_LegacyCvarInteger("g_missileSpeed", 0)' in block
    assert "missileSpeed > 0 ? missileSpeed : 2500" in block


def test_missile_gravity_maps_original_trajectory_modes():
    block = _rocket()
    assert 'G_NITMOD_LegacyCvarInteger("g_missileGravity", 0)' in block
    assert 'G_NITMOD_LegacyCvarInteger("g_rockets", 0)' in block
    assert "TR_GRAVITY" in block
    assert "TR_GRAVITY_LOW" in block
    assert "TR_GRAVITY_FLOAT" in block
    assert "TR_LINEAR" in block


def test_positive_missile_health_enables_typed_damage_entity():
    block = _rocket()
    assert 'G_NITMOD_LegacyCvarInteger("g_missileHealth", 5)' in block
    assert "bolt->takedamage = qtrue" in block
    assert "bolt->die = G_MissileDie" in block
    assert "bolt->r.contents = CONTENTS_CORPSE" in block
    assert "VectorSet(bolt->r.mins, -10, -3, 0)" in block
    assert "VectorSet(bolt->r.maxs, 10, 3, 6)" in block
