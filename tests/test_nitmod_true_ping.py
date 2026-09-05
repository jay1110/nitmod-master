from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ACTIVE = (ROOT / "src_2.60/game/g_active.c").read_text(encoding="utf-8")
LOCAL = (ROOT / "src_2.60/game/g_local.h").read_text(encoding="utf-8")


def test_true_ping_uses_private_sixty_four_sample_ring():
    assert "nitmodPingSamples[64]" in LOCAL
    assert "nitmodPingSampleHead" in LOCAL
    assert "level.time - ent->client->pers.cmd.serverTime" in ACTIVE
    assert "pingTotal / 64" in ACTIVE


def test_true_ping_is_runtime_gated_and_clamped():
    assert 'G_NITMOD_LegacyCvarInteger("g_truePing", 0)' in ACTIVE
    assert "ent->client->ps.ping < 0" in ACTIVE
