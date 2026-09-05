"""Require bounded parsing on server-controlled client statistics tuples."""
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/cgame/cg_servercmds.c").read_text(encoding="utf-8")


def main():
    assert "static qboolean CG_NitmodStatsArg" in SOURCE
    assert "*index >= trap_Argc()" in SOURCE
    assert "NITMOD_ParseProtocolSigned" in SOURCE
    for function in ("CG_topshotsParse_cmd", "CG_ParseWeaponStats",
                     "CG_parseBestShotsStats_cmd", "CG_parseTopShotsStats_cmd"):
        start = SOURCE.index("void " + function)
        body = SOURCE[start:SOURCE.find("\nvoid ", start + 6)]
        assert "CG_NitmodStatsArg" in body, function
    assert "iWeap < 1 || iWeap > NITMOD_WeaponStatCount()" in SOURCE
    assert "cnum < 0 || cnum >= MAX_CLIENTS" in SOURCE
    assert "cClients > MAX_CLIENTS" in SOURCE
    assert "trap_Argc() != 3" in SOURCE
    assert "shots < 0 || hits < 0" in SOURCE
    assert "static qboolean CG_NitmodValidateWeaponStatsTuple" in SOURCE
    assert "index != trap_Argc()" in SOURCE
    assert "(unsigned int)weaponMask & ~validWeapons" in SOURCE
    assert "(unsigned int)skillMask & ~validSkills" in SOURCE
    assert SOURCE.count("CG_NitmodValidateWeaponStatsTuple( &") >= 2
    assert "damageReceived < 0 || teamDamage < 0" in SOURCE
    assert "static qboolean CG_ParseAccuracyLog" in SOURCE
    assert "objectives > MAX_OBJECTIVES || objectives > MAX_OID_TRIGGERS" in SOURCE
    assert "NITMOD_WeaponFromWire( i )" in SOURCE
    assert "cgs.playerStats = next" in SOURCE
    assert "Original WeaponStats carries no region counts" in SOURCE
    # Every selected original wire ID must really have an item record.
    import importlib.util
    spec = importlib.util.spec_from_file_location("items", ROOT / "tools/extract_weapon_items.py")
    items = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(items)
    ids = {item["id"] for item in items.extract(ROOT, "cgame")}
    selected = [i for i in range(1, 52) if i not in (9, 17, 32, 37, 39, 40)
                and not (11 <= i <= 28 and 0x202a3 & (1 << (i - 11)))]
    assert set(selected) <= ids


if __name__ == "__main__":
    main()
