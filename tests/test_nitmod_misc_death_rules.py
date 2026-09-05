from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
COMBAT = (ROOT / "src_2.60/game/g_combat.c").read_text(encoding="utf-8")
PUBLIC = (ROOT / "src_2.60/game/bg_public.h").read_text(encoding="utf-8")


def test_misc_bit_64_forces_dynamite_victims_to_limbo():
    gate = ('meansOfDeath == MOD_DYNAMITE &&\n\t\t'
            '(G_NITMOD_LegacyCvarInteger("g_misc", 0) & 64)')
    assert gate in COMBAT
    start = COMBAT.index(gate)
    assert "limbo( self, qtrue );" in COMBAT[start:start + 400]


def test_original_numeric_mod_maps_to_typed_dynamite_enum():
    enum = PUBLIC[PUBLIC.index("typedef enum {\n\tMOD_UNKNOWN"):PUBLIC.index("MOD_NUM_MODS")]
    names = [line.strip().split(",")[0] for line in enum.splitlines()
             if line.strip().startswith("MOD_")]
    assert names.index("MOD_DYNAMITE") == 0x1A


if __name__ == "__main__":
    test_misc_bit_64_forces_dynamite_victims_to_limbo()
    test_original_numeric_mod_maps_to_typed_dynamite_enum()
    print("nitmod g_misc death rule checks passed")
