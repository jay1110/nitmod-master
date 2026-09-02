#include "g_local.h"
#include "g_nitmod_weapon_definition.h"
#include "nitmod_weapon_recoil.h"
#include "g_nitmod_weapon_registry.h"
#include "nitmod_weapon_defaults.h"
#include "nitmod_weapon_paths.h"
#include "g_nitmod_abilities.h"
#include "nitmod_weapon_reload.h"

static const char *tokens[] = {
    "weaponDef", "{", "both", "{", "maxammo", "42", "classes", "3",
    "recoilDuration", "200", "recoilYaw", "-", "0.5", "recoilPitch", "1.25", "}",
    "both_altweap", "{", "maxclip", "7", "classes", "5",
    "recoilDuration", "100", "recoilYaw", "0.25", "}", "}"
};
static int count, reads, opens, frees, failOpens, quoted, unterminated, badHandle;
static char paths[2][MAX_QPATH];
int trap_PC_LoadSource( const char *filename ) {
    if( opens < 2 ) {
        strncpy(paths[opens], filename, MAX_QPATH - 1);
        paths[opens][MAX_QPATH - 1] = 0;
    }
    ++opens;
    return opens <= failOpens ? 0 : 31;
}
int trap_PC_FreeSource( int handle ) {
    if( handle != 31 ) badHandle = 1;
    ++frees;
    return 1;
}
int trap_PC_ReadToken( int handle, pc_token_t *token ) {
    if( handle != 31 ) badHandle = 1;
    if( reads >= count ) return 0;
    token->type = reads == quoted ? TT_STRING : TT_NAME;
    if( reads == unterminated ) memset(token->string, 'x', sizeof(token->string));
    else strcpy(token->string, tokens[reads]);
    ++reads;
    return 1;
}
static void Reset( void ) {
    count = 28; reads = opens = frees = failOpens = badHandle = 0;
    quoted = unterminated = -1;
    memset(paths, 0, sizeof(paths));
}
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    ammotable_t ammo, baseline = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    nitmodWeaponRecoil_t recoil, saved = { 1, 19, 3, 4 };
    pmoveExt_t movement, before;
    unsigned int mask;
    int alt, i, weapon;
    char oversized[MAX_QPATH + 1];
    nitmodWeaponRegistry_t registry, snapshot;
    const nitmodWeaponRecord_t *record;
    gclient_t spawnClient;
    nitmodWeaponOptions_t options;
    const char *flagTokens[] = {
        "weaponDef", "{", "both", "{", "noMidclipReload", "noMidclipReload",
        "maxclip", "7", "}", "both_altweap", "{", "classes", "5", "}", "}"
    };
    for( alt = 0; alt < 2; ++alt ) {
        weapon = alt ? WP_K43_SCOPE : WP_K43;
        Reset(); failOpens = alt; ammo = baseline; recoil = saved; mask = 77;
        CHECK( G_NITMOD_LoadNativeWeaponRecoil(weapon, "custom", &ammo, &mask, &recoil) );
        CHECK( opens == alt + 1 && frees == 1 && !badHandle );
        CHECK( !strcmp(paths[0], "custom/k43.weap") );
        if( alt ) CHECK( !strcmp(paths[1], "weapons/k43.weap") );
        CHECK( mask == (alt ? 5u : 3u) && recoil.enabled == 1 );
        CHECK( ammo.maxammo == (alt ? 1 : 42) && ammo.maxclip == (alt ? 7 : 3) );
        CHECK( ammo.uses == 2 && ammo.mod == 11 );
        CHECK( recoil.duration == (alt ? 100 : 200) && recoil.yaw == (alt ? 0.25f : -0.5f) );
        CHECK( recoil.pitch == (alt ? 0.0f : 1.25f) );
        memset(&movement, 0, sizeof(movement));
        CHECK( NITMOD_ApplyWeaponRecoil(&movement, 0, &recoil) == 1 );
        CHECK( movement.weapRecoilDuration == recoil.duration );
        CHECK( movement.weapRecoilYaw == recoil.yaw && movement.weapRecoilPitch == recoil.pitch );
        for( i = 0; i < 28; ++i ) {
            Reset(); count = i; ammo = baseline; recoil = saved; mask = 77;
            CHECK( !G_NITMOD_LoadNativeWeaponRecoil(weapon, "custom", &ammo, &mask, &recoil) );
            CHECK( opens == 1 && frees == 1 && !badHandle );
            CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && !memcmp(&recoil, &saved, sizeof(recoil)) && mask == 77 );
        }
    }
    Reset(); quoted = 25;
    CHECK( !G_NITMOD_LoadNativeWeaponRecoil(WP_K43_SCOPE, "custom", &ammo, &mask, &recoil) );
    CHECK( opens == 1 && frees == 1 && mask == 77 && !memcmp(&recoil, &saved, sizeof(recoil)) );
    Reset(); unterminated = 25;
    CHECK( !G_NITMOD_LoadNativeWeaponRecoil(WP_K43_SCOPE, "custom", &ammo, &mask, &recoil) );
    CHECK( opens == 1 && frees == 1 && mask == 77 && !memcmp(&ammo, &baseline, sizeof(ammo)) );
    Reset(); failOpens = 2;
    CHECK( !G_NITMOD_LoadNativeWeaponRecoil(WP_K43, "custom", &ammo, &mask, &recoil) );
    CHECK( opens == 2 && !frees && !reads && mask == 77 );
    Reset(); failOpens = 1;
    CHECK( !G_NITMOD_LoadNativeWeaponRecoil(WP_K43, "weapons", &ammo, &mask, &recoil) );
    CHECK( opens == 1 && !frees );
    Reset();
    CHECK( !G_NITMOD_LoadNativeWeaponRecoil(WP_ARTY, "custom", &ammo, &mask, &recoil) );
    CHECK( !G_NITMOD_LoadNativeWeaponRecoil(WP_K43, NULL, &ammo, &mask, &recoil) );
    CHECK( !G_NITMOD_LoadNativeWeaponRecoil(WP_K43, "", &ammo, &mask, &recoil) );
    CHECK( !G_NITMOD_LoadNativeWeaponRecoil(WP_K43, "custom", NULL, &mask, &recoil) );
    CHECK( !G_NITMOD_LoadNativeWeaponRecoil(WP_K43, "custom", &ammo, NULL, &recoil) );
    CHECK( !G_NITMOD_LoadNativeWeaponRecoil(WP_K43, "custom", &ammo, &mask, NULL) );
    memset(oversized, 'x', sizeof(oversized)); oversized[MAX_QPATH] = 0;
    CHECK( !G_NITMOD_LoadNativeWeaponRecoil(WP_K43, oversized, &ammo, &mask, &recoil) );
    CHECK( !opens && !frees && !memcmp(&ammo, &baseline, sizeof(ammo)) );
    CHECK( mask == 77 && !memcmp(&recoil, &saved, sizeof(recoil)) );
    /* Reload with no selected attributes clears old mask/recoil but keeps
     * caller's ammo defaults, rather than accidentally retaining an override. */
    tokens[2] = "}"; count = 3;
    CHECK( G_NITMOD_LoadNativeWeaponRecoil(WP_K43, "custom", &ammo, &mask, &recoil) );
    CHECK( !mask && !recoil.enabled && !recoil.duration && !recoil.yaw && !recoil.pitch );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) );
    memset(&movement, 0x35, sizeof(movement)); before = movement;
    CHECK( !NITMOD_ApplyWeaponRecoil(&movement, 10, &recoil) );
    CHECK( !memcmp(&movement, &before, sizeof(movement)) && frees == 1 && !badHandle );
    tokens[2] = "both";
    Reset(); G_NITMOD_ResetWeaponRegistry(&registry);
    CHECK( !G_NITMOD_RegisteredWeapon(&registry, WP_K43) );
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43, "custom", &baseline, 0) == 1 );
    record = G_NITMOD_RegisteredWeapon(&registry, WP_K43);
    CHECK( record && record->ammo.maxammo == 42 && record->classMask == 3 );
    CHECK( record->recoil.enabled && record->recoil.duration == 200 && frees == 1 );
    snapshot = registry;
    Reset();
    CHECK( !G_NITMOD_RegisterWeapon(&registry, WP_K43, NULL, NULL, 0) );
    CHECK( !opens && !memcmp(&registry, &snapshot, sizeof(registry)) );
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43_SCOPE, "custom", &baseline, 0) == 1 );
    record = G_NITMOD_RegisteredWeapon(&registry, WP_K43_SCOPE);
    CHECK( record && record->ammo.maxclip == 7 && record->classMask == 5 );
    CHECK( G_NITMOD_RegisteredWeapon(&registry, WP_K43)->classMask == 3 );
    snapshot = registry;
    Reset(); count = 27;
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43, "custom", &baseline, 1) == -1 );
    CHECK( opens == 1 && frees == 1 && !memcmp(&registry, &snapshot, sizeof(registry)) );
    Reset(); failOpens = 2;
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43, "custom", &baseline, 1) == -1 );
    CHECK( opens == 2 && !frees && !memcmp(&registry, &snapshot, sizeof(registry)) );
    Reset(); count = 3; tokens[2] = "}";
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43, "custom", &baseline, 1) == 1 );
    record = G_NITMOD_RegisteredWeapon(&registry, WP_K43);
    CHECK( record && !record->classMask && !record->recoil.enabled );
    CHECK( !memcmp(&record->ammo, &baseline, sizeof(baseline)) );
    CHECK( G_NITMOD_RegisteredWeapon(&registry, WP_K43_SCOPE)->classMask == 5 );
    snapshot = registry;
    Reset();
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_ARTY, "custom", &baseline, 1) == -1 );
    CHECK( G_NITMOD_RegisterWeapon(&registry, -1, "custom", &baseline, 1) == -1 );
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_NUM_WEAPONS, "custom", &baseline, 1) == -1 );
    CHECK( G_NITMOD_RegisterWeapon(NULL, WP_K43, "custom", &baseline, 1) == -1 );
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43, "custom", NULL, 1) == -1 );
    CHECK( !G_NITMOD_RegisteredWeapon(NULL, WP_K43) && !G_NITMOD_RegisteredWeapon(&registry, -1) );
    CHECK( !opens && !memcmp(&registry, &snapshot, sizeof(registry)) );
    G_NITMOD_ResetWeaponRegistry(&registry);
    for( i = 0; i < WP_NUM_WEAPONS; ++i ) CHECK( !G_NITMOD_RegisteredWeapon(&registry, i) );
    G_NITMOD_ResetWeaponRegistry(NULL);
    Reset(); count = 2;
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43, "custom", &baseline, 0) == -1 );
    CHECK( !G_NITMOD_RegisteredWeapon(&registry, WP_K43) && frees == 1 );
    Reset(); tokens[2] = "both";
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43, "custom", &baseline, 0) == 1 );
    CHECK( G_NITMOD_RegisteredWeapon(&registry, WP_K43)->classMask == 3 && frees == 1 );
    for( i = 0; i < WP_NUM_WEAPONS; ++i ) {
        ammo = baseline;
        CHECK( NITMOD_WeaponAmmoDefaults(i, &ammo) == (NITMOD_WeaponPath(i) != NULL) );
        CHECK( ammo.mod == baseline.mod );
        if( !NITMOD_WeaponPath(i) ) CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) );
        else {
            switch( i ) {
            case WP_KNIFE: case WP_AMMO: case WP_DYNAMITE: case WP_SMOKETRAIL:
            case WP_MEDKIT: case WP_BINOCULARS: case WP_PLIERS: case WP_SMOKE_MARKER:
            case WP_LANDMINE: case WP_SATCHEL_DET: case WP_SMOKE_BOMB: case WP_TRIPMINE:
                CHECK( ammo.uses == 0 ); break;
            default: CHECK( ammo.uses == 1 ); break;
            }
        }
    }
    ammo = baseline;
    CHECK( !NITMOD_WeaponAmmoDefaults(-1, &ammo) && !NITMOD_WeaponAmmoDefaults(WP_NUM_WEAPONS, &ammo) );
    CHECK( !NITMOD_WeaponAmmoDefaults(WP_KNIFE, NULL) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) );
    CHECK( NITMOD_WeaponAmmoDefaults(WP_KNIFE, &ammo) );
    CHECK( ammo.maxammo == 8 && ammo.maxclip == 8 && ammo.defaultStartingClip == 4 && ammo.uses == 0 );
    CHECK( ammo.defaultStartingAmmo == 0 && ammo.nextShotTime == 200 );
    CHECK( NITMOD_WeaponAmmoDefaults(WP_GRENADE_LAUNCHER, &ammo) && ammo.maxclip == 9 && ammo.uses == 1 );
    /* Explicit defaults -> real registration -> empty definition preserves
     * original timing/ammo/uses values without changing native mod. */
    Reset(); tokens[2] = "}"; count = 3;
    G_NITMOD_ResetWeaponRegistry(&registry);
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_GRENADE_LAUNCHER, "custom", &ammo, 0) == 1 );
    record = G_NITMOD_RegisteredWeapon(&registry, WP_GRENADE_LAUNCHER);
    CHECK( record && !memcmp(&record->ammo, &ammo, sizeof(ammo)) && !record->classMask && !record->recoil.enabled );
    CHECK( record->ammo.uses == 1 && record->ammo.mod == baseline.mod );
    Reset(); tokens[2] = "}"; count = 3;
    CHECK( NITMOD_WeaponAmmoDefaults(WP_MEDIC_ADRENALINE, &ammo) );
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_MEDIC_ADRENALINE, "custom", &ammo, 0) == 1 );
    record = G_NITMOD_RegisteredWeapon(&registry, WP_MEDIC_ADRENALINE);
    CHECK( record );
    memset(&spawnClient, 0, sizeof(spawnClient));
    spawnClient.sess.playerType = PC_MEDIC;
    spawnClient.ps.ammoclip[WP_MEDIC_SYRINGE] = 23;
    CHECK( G_NITMOD_GrantAdrenalineSpawn(&spawnClient, 20, 2, 0, 0, &record->ammo) == 1 );
    CHECK( spawnClient.ps.ammoclip[WP_MEDIC_ADRENALINE] == ammo.defaultStartingClip + 2 );
    CHECK( spawnClient.ps.ammo[WP_MEDIC_ADRENALINE] == ammo.defaultStartingAmmo );
    CHECK( spawnClient.ps.ammoclip[WP_MEDIC_SYRINGE] == 23 );
    for( i = 0; i < 15; ++i ) tokens[i] = flagTokens[i];
    for( alt = 0; alt < 2; ++alt ) {
        weapon = alt ? WP_K43_SCOPE : WP_K43;
        Reset(); count = 15; failOpens = alt;
        ammo = baseline; recoil = saved; mask = 77; options.noMidclipReload = 99;
        CHECK( G_NITMOD_LoadNativeWeaponOptions(weapon, "custom", &ammo, &mask, &recoil, &options) );
        CHECK( options.noMidclipReload == !alt && ammo.maxclip == (alt ? 3 : 7) );
        CHECK( mask == (alt ? 5u : 0u) && !recoil.enabled );
        CHECK( opens == alt + 1 && frees == 1 && !badHandle );
        for( i = 0; i < 15; ++i ) {
            Reset(); count = i; ammo = baseline; recoil = saved; mask = 77; options.noMidclipReload = 99;
            CHECK( !G_NITMOD_LoadNativeWeaponOptions(weapon, "custom", &ammo, &mask, &recoil, &options) );
            CHECK( options.noMidclipReload == 99 && mask == 77 );
            CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && !memcmp(&recoil, &saved, sizeof(recoil)) );
            CHECK( opens == 1 && frees == 1 && !badHandle );
        }
    }
    Reset(); count = 15;
    G_NITMOD_ResetWeaponRegistry(&registry);
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43, "custom", &baseline, 0) == 1 );
    CHECK( registry.weapons[WP_K43].options.noMidclipReload == 1 );
    memset(&spawnClient, 0, sizeof(spawnClient));
    spawnClient.ps.ammoclip[WP_K43] = 1;
    CHECK( !NITMOD_MidclipReloadAllowed(&spawnClient.ps, WP_K43,
        &registry.weapons[WP_K43].options, ~0u) );
    snapshot = registry;
    Reset(); count = 15; tokens[5] = "0"; /* Bare flag must not consume a value. */
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43, "custom", &baseline, 1) == -1 );
    CHECK( !memcmp(&registry, &snapshot, sizeof(registry)) && frees == 1 );
    tokens[5] = "noMidclipReload";
    Reset(); count = 15; quoted = 4;
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43, "custom", &baseline, 1) == -1 );
    CHECK( !memcmp(&registry, &snapshot, sizeof(registry)) && frees == 1 );
    Reset(); count = 15;
    CHECK( !G_NITMOD_LoadNativeWeaponOptions(WP_K43, "custom", &ammo, &mask, &recoil, NULL) );
    CHECK( !opens && !frees );
    Reset(); count = 3; tokens[2] = "}";
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_K43, "custom", &baseline, 1) == 1 );
    CHECK( !registry.weapons[WP_K43].options.noMidclipReload && frees == 1 );
    CHECK( NITMOD_MidclipReloadAllowed(&spawnClient.ps, WP_K43,
        &registry.weapons[WP_K43].options, 0) );
    /* Same loaded flag, different MG42 override policy; no fake skill level. */
    Reset(); count = 15; tokens[2] = "both";
    CHECK( G_NITMOD_RegisterWeapon(&registry, WP_MOBILE_MG42, "custom", &baseline, 0) == 1 );
    record = G_NITMOD_RegisteredWeapon(&registry, WP_MOBILE_MG42);
    CHECK( record && record->options.noMidclipReload );
    spawnClient.ps.ammoclip[WP_MOBILE_MG42] = 1;
    CHECK( !NITMOD_MidclipReloadAllowed(&spawnClient.ps, WP_MOBILE_MG42, &record->options, 0) );
    CHECK( NITMOD_MidclipReloadAllowed(&spawnClient.ps, WP_MOBILE_MG42, &record->options, 0x20u) );
    return 0;
}
