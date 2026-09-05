from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_weapon.c").read_text(encoding="utf-8")


def function(name: str, following: str) -> str:
    start = SOURCE.index(name)
    return SOURCE[start:SOURCE.index(following, start)]


def test_pack_launchers_consume_legacy_throw_distance():
    medic = function("void Weapon_Medic(", "void G_PlaceTripmine")
    ammo = function("void Weapon_MagicAmmo(", "qboolean ReviveEntity")
    expression = 'G_NITMOD_LegacyCvarInteger("g_throwDistance", 75)'
    assert expression in medic
    assert expression in ammo
    assert "VectorScale( velocity, 75, velocity );" not in medic
    assert "VectorScale( velocity, 75, velocity );" not in ammo


if __name__ == "__main__":
    test_pack_launchers_consume_legacy_throw_distance()
    print("nitmod g_throwDistance runtime checks passed")
