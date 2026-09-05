from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ENTS = (ROOT / "src_2.60/cgame/cg_ents.c").read_text(encoding="utf-8")
EFFECTS = (ROOT / "src_2.60/cgame/cg_effects.c").read_text(encoding="utf-8")
MISSILE = (ROOT / "src_2.60/game/g_missile.c").read_text(encoding="utf-8")
PMOVE = (ROOT / "src_2.60/game/bg_pmove.c").read_text(encoding="utf-8")


def test_poison_mine_smokes_only_after_server_trigger():
    missile = ENTS[ENTS.index("void CG_Missile( centity_t *cent )"):]
    assert "s1->weapon == WP_POISON_MINE && s1->teamNum >= 8" in missile
    assert "weapon->missileTrailFunc && s1->weapon != WP_POISON_MINE" in missile
    assert "if(self->s.weapon == WP_POISON_MINE)" in MISSILE
    assert "self->think = weapon_smokeBombExplode" in MISSILE


def test_triggered_poison_cloud_uses_normalized_green():
    style = EFFECTS[EFFECTS.index("void CG_NitmodSmokeSpriteStyle"):]
    style = style[:style.index("qboolean CG_SpawnSmokeSprite")]
    assert "weapon == WP_POISON_BOMB || weapon == WP_POISON_MINE" in style
    assert "Vector4Set(color, .15f, .8f, .1f, .25f)" in style


def test_poison_mine_placement_requests_pliers():
    assert "PM_BeginWeaponChange(WP_POISON_MINE, WP_PLIERS, qfalse)" in PMOVE
