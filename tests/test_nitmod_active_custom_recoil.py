from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
GAME=ROOT/"src_2.60"/"game"
CGAME=ROOT/"src_2.60"/"cgame"
PUBLIC=(GAME/"bg_public.h").read_text()
PMOVE=(GAME/"bg_pmove.c").read_text()
SERVER=(GAME/"g_active.c").read_text()
DEFS=(GAME/"g_nitmod_weapon_definition.c").read_text()
CLIENT=(CGAME/"cg_predict.c").read_text()
WEAPONS=(CGAME/"cg_weapons.c").read_text()
COMBAT=(GAME/"g_combat.c").read_text()
OBITUARY=(CGAME/"cg_nitmod_obituary.c").read_text()

for field in ("nitmodCustomRecoilEnabled", "nitmodCustomRecoilDuration",
              "nitmodCustomRecoilYaw", "nitmodCustomRecoilPitch"):
    assert field in PUBLIC and field in SERVER and field in CLIENT
assert "G_NITMOD_WeaponRecoil(client->ps.weapon, &recoil)" in SERVER
assert "pickupDefinitionState[weapon]!=1" in DEFS
assert "NITMOD_ApplyWeaponRecoil(pm->pmext, pm->cmd.serverTime, &recoil)" in PMOVE
for token in ("recoilDuration", "recoilYaw", "recoilPitch"):
    assert token in WEAPONS
assert "wi->customRecoilEnabled" in CLIENT
assert "nitmodNoMidclipReload" in PUBLIC
assert "G_NITMOD_WeaponNoMidclipReload(client->ps.weapon)" in SERVER
assert 'Q_stricmp(token.string, "noMidclipReload")' in WEAPONS
assert "wi->noMidclipReload" in CLIENT
assert "pm->nitmodNoMidclipReload || weapon == WP_GARAND_SCOPE" in PMOVE
for field in ("nitmodSpreadScaleAdd", "nitmodSpreadScaleAddRand",
              "nitmodSpreadRatio", "nitmodVelocityToSpread",
              "nitmodViewChangeToSpread"):
    assert field in PUBLIC and field in SERVER and field in CLIENT
assert "G_NITMOD_WeaponSpreadOptions(client->ps.weapon, &options)" in SERVER
assert "rand() % pm->nitmodSpreadScaleAddRand" in PMOVE
for token in ("SpreadScaleAdd", "SpreadScaleAddRand", "spreadRatio",
              "velocity2spread", "viewchange2spread"):
    assert token in WEAPONS
assert "G_NITMOD_WeaponForcesLimbo(BG_WeaponForMOD(meansOfDeath))" in COMBAT
assert 'Q_stricmp(token.string, "KillMessage")' in WEAPONS
assert "cg_weapons[weapon].killMessage" in OBITUARY
print("Nitmod active custom recoil contract checks passed")
