from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_missile.c").read_text(encoding="utf-8")


def test_homing_rocket_uses_original_search_envelope():
    assert "G_NITMOD_HomingMissileThink" in SOURCE
    assert "bestDistance = 768.0f" in SOURCE
    assert "DotProduct(desired, forward) < 0.9f" in SOURCE
    assert "trace.entityNum != candidate->s.number" in SOURCE
    assert "speed >= 750.0f" in SOURCE


def test_guided_rocket_tracks_owner_view_and_camera_mode():
    assert "G_NITMOD_GuidedMissileThink" in SOURCE
    assert "owner->client->ps.viewangles" in SOURCE
    assert 'G_NITMOD_LegacyCvarInteger("g_missileCams", 0) & 1' in SOURCE
    assert "distance = VectorLength(aim) + 400.0f" in SOURCE
    assert "speed > 300.0f" in SOURCE


def test_rocket_option_bits_install_matching_think_routines():
    block = SOURCE[SOURCE.index("gentity_t *fire_rocket"):]
    block = block[:block.index("gentity_t *fire_flamebarrel")]
    assert "rocketOptions & 1" in block
    assert "bolt->think = G_NITMOD_GuidedMissileThink" in block
    assert "rocketOptions & 2" in block
    assert "bolt->think = G_NITMOD_HomingMissileThink" in block
