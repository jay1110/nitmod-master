from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ANTILAG = (ROOT / "src_2.60/game/g_antilag.c").read_text(encoding="utf-8")
ACTIVE = (ROOT / "src_2.60/game/g_active.c").read_text(encoding="utf-8")
LOCAL = (ROOT / "src_2.60/game/g_local.h").read_text(encoding="utf-8")

def run_checks() -> None:
    for token in ("EF_DEAD", "EF_PRONE", "EF_SPARE0", "EF_CROUCHING"):
        assert token in ANTILAG
    for height in ("48.0f", "36.0f", "18.0f", "32.0f", "4.0f", "24.0f"):
        assert height in ANTILAG
    for weapon in ("WP_POISON_SYRINGE", "WP_MEDIC_SYRINGE", "WP_KNIFE"):
        assert weapon in ANTILAG
    assert 'G_NITMOD_LegacyCvarInteger( "g_realBody", 0 ) & 1' in ANTILAG
    assert 'G_NITMOD_LegacyCvarInteger( "g_hitboxes", 0 )' in ANTILAG
    assert "nitmodSavedBodyMins" in LOCAL and "nitmodSavedBodyMaxs" in LOCAL
    assert "VectorCopy( list->client->nitmodSavedBodyMins, list->r.mins )" in ANTILAG
    assert "G_NITMOD_HitboxHeight( ent, NULL )" in ACTIVE

if __name__ == "__main__":
    run_checks()
    print("Nitmod hitbox-height checks passed")
