from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ENTITIES = (ROOT / "src_2.60/game/g_nitmod_entities.c").read_text(encoding="utf-8")
WEAPON = (ROOT / "src_2.60/game/g_weapon.c").read_text(encoding="utf-8")
CLIENT = (ROOT / "src_2.60/cgame/cg_nitmod_hints.c").read_text(encoding="utf-8")
UI = (ROOT / "src_2.60/ui/ui_main.c").read_text(encoding="utf-8")


def run_checks() -> None:
    assert 'G_NITMOD_LegacyCvarInteger( "g_artilleryHints", 1 ) != 1' in ENTITIES
    assert "hint->s.eType = ET_LANDMINESPOT_HINT" in ENTITIES
    assert "hint->s.teamNum" in ENTITIES and "hint->parent = shell->parent" in ENTITIES
    assert "shell->s.pos.trTime == hint->s.pos.trTime" in ENTITIES
    assert "hint->r.svFlags = SVF_BROADCAST" in ENTITIES
    assert "G_NITMOD_SpawnArtilleryHint( bomb );" in WEAPON
    assert CLIENT.count("NITMOD_UsesNitmodHud()") >= 2
    assert "original ? ORIGINAL_BUILD_HINT : ET_CONSTRUCTIBLE_INDICATOR" in CLIENT
    assert "if(!explosiveHint && !buildHint && !artilleryHint)" in CLIENT
    assert "if(buildHint)" in CLIENT
    assert "distance < 400 ? 150 : distance < 576 ? 300 : 0" in CLIENT
    for name in ("cg_objectiveHints", "cg_artilleryHints"):
        assert f'{{ NULL, "{name}", "1", CVAR_ARCHIVE }}' in UI


if __name__ == "__main__":
    run_checks()
    print("Nitmod artillery-hint integration checks passed")
