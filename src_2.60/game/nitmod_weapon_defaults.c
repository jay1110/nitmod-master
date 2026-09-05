#include "nitmod_weapon_defaults.h"

int NITMOD_WeaponBlastDefaults(int weapon, int *damage, int *splash, int *radius) {
    static const struct { int weapon, damage, splash, radius; } blast[] = {
        {WP_GRENADE_LAUNCHER, 0, 250, 250},
        {WP_GRENADE_PINEAPPLE, 0, 250, 250},
        {WP_PANZERFAUST, 400, 400, 300},
        {WP_DYNAMITE, 0, 400, 400},
        {WP_LANDMINE, 0, 250, 250},
        {WP_SATCHEL, 0, 250, 250},
        {WP_SMOKE_BOMB, 0, 0, 0},
        {WP_SMOKE_MARKER, 400, 400, 400},
        {WP_GPG40, 250, 250, 250},
        {WP_M7, 250, 250, 250},
        {WP_MORTAR_SET, 400, 400, 400},
        {WP_BOMB, 0, 350, 300},
        {WP_TRIPMINE, 0, 300, 300},
        {WP_POISON_BOMB, 20, 0, 250},
        {WP_POISON_MINE, 20, 0, 250}
    };
    unsigned int i;
    if(!damage || !splash || !radius) return 0;
    for(i=0;i<sizeof(blast)/sizeof(blast[0]);++i) if(blast[i].weapon==weapon) {
        *damage=blast[i].damage; *splash=blast[i].splash; *radius=blast[i].radius;
        return 1;
    }
    return 0;
}

typedef struct {
    weapon_t weapon;
    int maxammo, uses, maxclip, defaultStartingAmmo, defaultStartingClip;
    int reloadTime, fireDelayTime, nextShotTime, maxHeat, coolRate;
} weaponDefaults_t;
/* Original ELF ammoTableMP uses 72-byte records. The verified ten-int
 * prefix is translated by identity; original mod IDs are not copied. */
static const weaponDefaults_t defaults[] = {
    { WP_KNIFE, 8, 0, 8, 0, 4, 0, 50, 200, 0, 0 },
    { WP_LUGER, 24, 1, 8, 24, 8, 1500, 100, 400, 0, 0 },
    { WP_MP40, 90, 1, 30, 30, 30, 2400, 100, 150, 0, 0 },
    { WP_GRENADE_LAUNCHER, 45, 1, 9, 0, 4, 1000, 250, 1600, 0, 0 },
    { WP_PANZERFAUST, 4, 1, 1, 0, 4, 1000, 750, 2000, 0, 0 },
    { WP_FLAMETHROWER, 200, 1, 200, 0, 200, 1000, 100, 50, 0, 0 },
    { WP_COLT, 24, 1, 8, 24, 8, 1500, 100, 400, 0, 0 },
    { WP_THOMPSON, 90, 1, 30, 30, 30, 2400, 100, 150, 0, 0 },
    { WP_GRENADE_PINEAPPLE, 45, 1, 9, 0, 4, 1000, 250, 1600, 0, 0 },
    { WP_STEN, 96, 1, 32, 64, 32, 3100, 100, 150, 1200, 450 },
    { WP_MEDIC_SYRINGE, 10, 1, 1, 0, 10, 1500, 50, 750, 0, 0 },
    { WP_AMMO, 1, 0, 1, 0, 0, 3000, 50, 1000, 0, 0 },
    { WP_SILENCER, 24, 1, 8, 24, 8, 1500, 100, 400, 0, 0 },
    { WP_DYNAMITE, 1, 0, 10, 0, 0, 1000, 250, 1600, 0, 0 },
    { WP_SMOKETRAIL, 999, 0, 999, 0, 0, 0, 50, 0, 0, 0 },
    { WP_MEDKIT, 999, 0, 999, 1, 1, 0, 50, 1000, 0, 0 },
    { WP_BINOCULARS, 999, 0, 999, 0, 0, 0, 50, 0, 0, 0 },
    { WP_PLIERS, 999, 0, 999, 0, 0, 0, 50, 50, 0, 0 },
    { WP_SMOKE_MARKER, 999, 0, 999, 0, 1, 0, 50, 1000, 0, 0 },
    { WP_KAR98, 30, 1, 10, 20, 10, 1500, 100, 400, 0, 0 },
    { WP_CARBINE, 30, 1, 10, 20, 10, 1500, 100, 400, 0, 0 },
    { WP_GARAND, 30, 1, 10, 20, 10, 1500, 100, 400, 0, 0 },
    { WP_LANDMINE, 1, 0, 1, 0, 1, 100, 100, 100, 0, 0 },
    { WP_SATCHEL, 1, 1, 1, 0, 0, 3000, 100, 2000, 0, 0 },
    { WP_SATCHEL_DET, 1, 0, 1, 0, 0, 3000, 722, 2000, 0, 0 },
    { WP_SMOKE_BOMB, 1, 0, 10, 0, 1, 1000, 250, 1600, 0, 0 },
    { WP_MOBILE_MG42, 450, 1, 150, 0, 150, 3000, 100, 66, 1500, 300 },
    { WP_K43, 30, 1, 10, 20, 10, 1500, 100, 400, 0, 0 },
    { WP_FG42, 60, 1, 20, 40, 20, 2000, 100, 100, 0, 0 },
    { WP_MORTAR, 15, 1, 1, 0, 0, 0, 750, 1600, 0, 0 },
    { WP_AKIMBO_COLT, 48, 1, 8, 48, 8, 2700, 100, 200, 0, 0 },
    { WP_AKIMBO_LUGER, 48, 1, 8, 48, 8, 2700, 100, 200, 0, 0 },
    { WP_GPG40, 4, 1, 1, 4, 1, 3000, 100, 400, 0, 0 },
    { WP_M7, 4, 1, 1, 4, 1, 3000, 100, 400, 0, 0 },
    { WP_SILENCED_COLT, 24, 1, 8, 24, 8, 1500, 100, 400, 0, 0 },
    { WP_GARAND_SCOPE, 30, 1, 10, 20, 10, 1500, 0, 400, 0, 0 },
    { WP_K43_SCOPE, 30, 1, 10, 20, 10, 1500, 0, 400, 0, 0 },
    { WP_FG42SCOPE, 60, 1, 20, 40, 20, 2000, 100, 400, 0, 0 },
    { WP_MORTAR_SET, 16, 1, 1, 12, 0, 0, 750, 1400, 0, 0 },
    { WP_MEDIC_ADRENALINE, 10, 1, 1, 0, 10, 1500, 50, 1000, 0, 0 },
    { WP_AKIMBO_SILENCEDCOLT, 48, 1, 8, 48, 8, 2700, 100, 200, 0, 0 },
    { WP_AKIMBO_SILENCEDLUGER, 48, 1, 8, 48, 8, 2700, 100, 200, 0, 0 },
    { WP_MOBILE_MG42_SET, 450, 1, 150, 0, 150, 3000, 100, 66, 1500, 300 },
    { WP_TRIPMINE, 1, 0, 1, 1, 1, 100, 100, 100, 0, 0 },
    { WP_BOMB, 1, 1, 1, 0, 1, 1000, 250, 1600, 0, 0 },
    { WP_POISON_SYRINGE, 8, 1, 1, 0, 4, 1500, 50, 500, 0, 0 },
    { WP_POISON_BOMB, 1, 0, 10, 0, 1, 1000, 250, 1600, 0, 0 },
    { WP_POISON_MINE, 1, 0, 1, 0, 1, 100, 100, 100, 0, 0 },
};
int NITMOD_WeaponAutoReloadDefault( int weapon, int *requiresSetting ) {
    unsigned int i;
    if( !requiresSetting ) return 0;
    for( i = 0; i < sizeof(defaults) / sizeof(defaults[0]); ++i ) {
        if( defaults[i].weapon != weapon ) continue;
        switch( weapon ) {
        case WP_LUGER: case WP_MP40: case WP_COLT: case WP_THOMPSON:
        case WP_STEN: case WP_SILENCER: case WP_KAR98: case WP_CARBINE:
        case WP_GARAND: case WP_MOBILE_MG42: case WP_K43: case WP_FG42:
        case WP_AKIMBO_COLT: case WP_AKIMBO_LUGER: case WP_SILENCED_COLT:
        case WP_GARAND_SCOPE: case WP_K43_SCOPE: case WP_FG42SCOPE:
        case WP_AKIMBO_SILENCEDCOLT: case WP_AKIMBO_SILENCEDLUGER:
        case WP_MOBILE_MG42_SET:
            *requiresSetting = 1;
            break;
        default: *requiresSetting = 0; break;
        }
        return 1;
    }
    return 0;
}
int NITMOD_WeaponAmmoDefaults( int weapon, ammotable_t *ammo ) {
    unsigned int i;
    const weaponDefaults_t *entry;
    if( !ammo || weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS ) return 0;
    for( i = 0; i < sizeof(defaults) / sizeof(defaults[0]); ++i ) {
        entry = &defaults[i];
        if( entry->weapon != weapon ) continue;
        ammo->maxammo = entry->maxammo;
        ammo->uses = entry->uses;
        ammo->maxclip = entry->maxclip;
        ammo->defaultStartingAmmo = entry->defaultStartingAmmo;
        ammo->defaultStartingClip = entry->defaultStartingClip;
        ammo->reloadTime = entry->reloadTime;
        ammo->fireDelayTime = entry->fireDelayTime;
        ammo->nextShotTime = entry->nextShotTime;
        ammo->maxHeat = entry->maxHeat;
        ammo->coolRate = entry->coolRate;
        return 1;
    }
    return 0;
}
