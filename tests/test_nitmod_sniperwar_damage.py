from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
COMBAT = (ROOT / "src_2.60" / "game" / "g_combat.c").read_text(encoding="utf-8")
CLIENT = (ROOT / "src_2.60" / "game" / "g_client.c").read_text(encoding="utf-8")
PROTOCOL = (ROOT / "src_2.60" / "game" / "nitmod_protocol.h").read_text(encoding="utf-8")


def run_checks() -> None:
    assert 'G_NITMOD_LegacyCvarInteger( "g_war", 0 ) != 2' in COMBAT
    assert "mod != MOD_K43_SCOPE && mod != MOD_GARAND_SCOPE" in COMBAT
    assert '"n_sniperWarOptions", 7' in COMBAT
    assert "options & 2u" in COMBAT
    assert "*dflags |= DAMAGE_NO_PROTECTION" in COMBAT
    assert "SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS" in COMBAT
    assert "scopedRewards & ( 1u << 5 )" in COMBAT
    assert "*damage = targ->health" in COMBAT
    assert "NITMOD_HIT_SOUND_HEAD" in COMBAT
    assert "G_NITMOD_ApplySniperWarHeadshot" in COMBAT
    assert 'G_NITMOD_LegacyCvarInteger("n_sniperWarOptions", 7)' in CLIENT
    assert "#define NITMOD_HIT_SOUND_HEAD 4" in PROTOCOL


if __name__ == "__main__":
    run_checks()
    print("Nitmod sniper-war damage checks passed")
