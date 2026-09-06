#ifndef NITMOD_AMMO_REWARDS_H
#define NITMOD_AMMO_REWARDS_H
#include "nitmod_heavy_ammo.h"
/* Original BG_MaxAmmoForWeapon, using native weapon names and explicit masks.
 * Knife remains on its existing path pending reserve/clip reconciliation. */
static int NITMOD_AmmoRewardCapacity(int weapon, const unsigned int *r, int base, int clip) {
    int heavy = NITMOD_HeavyAmmoCapacity(weapon, r[SK_HEAVY_WEAPONS], base, clip);
    if(heavy >= 0) return heavy;
    switch(weapon) {
    case WP_LUGER: case WP_COLT: case WP_STEN: case WP_SILENCER:
    case WP_KAR98: case WP_CARBINE: case WP_SILENCED_COLT:
        return base + ((r[SK_LIGHT_WEAPONS] & 2u) ? clip : 0);
    case WP_MP40: case WP_THOMPSON:
        return base + (((r[SK_LIGHT_WEAPONS] | r[SK_FIRST_AID]) & 2u) ? clip : 0);
    case WP_GARAND: case WP_K43: case WP_FG42:
    case WP_GARAND_SCOPE: case WP_K43_SCOPE: case WP_FG42SCOPE:
        return base + (((r[SK_LIGHT_WEAPONS] | r[SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS]) & 2u) ? clip : 0);
    case WP_MEDIC_SYRINGE: case WP_MEDIC_ADRENALINE:
        return base + ((r[SK_FIRST_AID] & 4u) ? 2 : 0);
    case WP_GPG40: case WP_M7:
        return base + ((r[SK_EXPLOSIVES_AND_CONSTRUCTION] & 2u) ? 4 : 0);
    case WP_GRENADE_LAUNCHER: case WP_GRENADE_PINEAPPLE:
        return base + (!(r[SK_EXPLOSIVES_AND_CONSTRUCTION] & 2u) && (r[SK_FIRST_AID] & 2u) ? 1 : 0);
    default: return base;
    }
}
#endif
