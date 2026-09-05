from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_poison_mine_out_of_ammo_switches_to_pliers():
    source = (ROOT / "src_2.60/cgame/cg_nitmod_ammo.c").read_text(encoding="utf-8")
    assert "current == WP_TRIPMINE || current == WP_POISON_MINE" in source
    assert "CG_WeaponSelectable(WP_PLIERS)" in source
    assert "*choice = WP_PLIERS" in source


if __name__ == "__main__":
    test_poison_mine_out_of_ammo_switches_to_pliers()
