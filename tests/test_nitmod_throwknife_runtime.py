from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PMOVE = (ROOT / "src_2.60/game/bg_pmove.c").read_text(encoding="utf-8")
WEAPON = (ROOT / "src_2.60/game/g_weapon.c").read_text(encoding="utf-8")
ACTIVE = (ROOT / "src_2.60/game/g_active.c").read_text(encoding="utf-8")
EVENTS = (ROOT / "src_2.60/cgame/cg_nitmod_events.c").read_text(encoding="utf-8")


def test_attack2_is_edge_gated_and_emits_private_throw_event():
    throw = PMOVE[PMOVE.index("static qboolean PM_NitmodThrowKnife(void)"):]
    throw = throw[:throw.index("static void PM_Weapon( void )")]
    assert "WBUTTON_ATTACK2" in throw
    assert "pm->ps->weaponstate != WEAPON_FIRING" in throw
    assert "PM_StartWeaponAnim(WEAP_ATTACK2)" in throw
    assert "PM_AddEvent(EV_NITMOD_THROW_KNIFE)" in throw


def test_server_spawns_a_pickable_dropped_knife():
    throw = WEAPON[WEAPON.index("void G_NITMOD_ThrowKnife"):]
    throw = throw[:throw.index("int G_GetWeaponDamage")]
    assert "BG_FindItemForWeapon(WP_KNIFE)" in throw
    assert "LaunchItem(item, muzzleEffect, velocity" in throw
    assert 'knife->classname = "knife"' in throw
    assert "knife->r.svFlags |= SVF_BROADCAST" in throw
    assert "knife->s.clientNum = ent->s.number" in throw
    assert "knife->s.teamNum = ent->client->sess.sessionTeam" in throw
    assert "knife->damage = G_GetWeaponDamage(WP_KNIFE)" in throw
    assert "knife->s.pos.trType = TR_GRAVITY_LOW" in throw
    assert "knife->nextthink = level.time + 20000" in throw
    assert "G_NITMOD_ThrowKnife(ent);" in ACTIVE
    assert ACTIVE.count("pm.nitmodAuthoritativeWeapons = qtrue;") == 2


def test_client_accepts_original_and_reconstructed_event_ids():
    assert "case 95:" in EVENTS
    assert "case EV_NITMOD_THROW_KNIFE:" in EVENTS
    assert "NITMOD_FIRE_THROWKNIFE" in EVENTS
