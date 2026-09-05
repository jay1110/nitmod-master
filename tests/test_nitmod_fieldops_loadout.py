from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CLIENT = (ROOT / "src_2.60/game/g_client.c").read_text(encoding="utf-8")


def test_fieldops_bit_one_gates_binocular_loadout():
    start = CLIENT.index("if ( pc == PC_FIELDOPS )")
    end = CLIENT.index("} else if( pc == PC_MEDIC )", start)
    block = CLIENT[start:end]
    assert 'G_NITMOD_LegacyCvarInteger("g_fieldOps", 0)' in block
    assert "fieldOpsOptions & 1u" in block
    assert "nitmodSkillMasks[SK_BATTLE_SENSE] & 2u" in block
    assert "nitmodSkillMasks[SK_SIGNALS] & 2u" in block
    assert "grantBinoculars &&" in block
    assert "AddWeaponToPlayer( client, WP_BINOCULARS" in block


if __name__ == "__main__":
    test_fieldops_bit_one_gates_binocular_loadout()
    print("nitmod field-ops loadout checks passed")
