from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_weapon.c").read_text(encoding="utf-8")


def test_fieldops_support_charge_policy_is_shared_by_airstrike_and_artillery():
    assert 'G_NITMOD_LegacyCvarInteger("g_fieldOps", 0)' in SOURCE
    assert "if(options & 2) refund" in SOURCE
    assert "else if(options & 4) refund" in SOURCE
    assert "G_NITMOD_ConsumeFieldOpsSupport(ent);" in SOURCE
    assert SOURCE.count("G_NITMOD_RefundRejectedFieldOpsSupport(ent->parent);") >= 4
    assert SOURCE.count("G_NITMOD_RefundRejectedFieldOpsSupport(ent);") >= 4


if __name__ == "__main__":
    test_fieldops_support_charge_policy_is_shared_by_airstrike_and_artillery()
    print("nitmod g_fieldOps support-charge checks passed")
