from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
COMBAT = (ROOT / "src_2.60/game/g_combat.c").read_text(encoding="utf-8")


def test_attacker_health_uses_typed_original_guards():
    assert 'G_NITMOD_LegacyCvarInteger("g_drawAttackerHP", 1) > 0' in COMBAT
    assert "!(self->r.svFlags & SVF_BOT)" in COMBAT
    assert "!killedintank" in COMBAT
    assert "attacker->health > 0" in COMBAT


def test_attacker_health_uses_original_chat_payload():
    assert 'chat \\\"%s ^ghad ^3%i HP\\\" -2' in COMBAT
    assert "attacker->client->pers.netname, attacker->health" in COMBAT
