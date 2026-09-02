#include "g_local.h"
#include "g_nitmod_restrictions.h"

int G_NITMOD_PickupPolicy( const gentity_t *entity, int weapon,
    nitmodWeaponDecision_t restriction, int warMode, int pickAnyWeapon,
    unsigned int classMask, unsigned int medicOptions ) {
    int cls;
    if( !entity || !entity->client || weapon < WP_NONE || weapon >= WP_NUM_WEAPONS ||
        restriction != NITMOD_WEAPON_ALLOW ) return 0;
    /* Original G_CanPickupWeapon: unlike the restriction precheck, war modes
     * return the final allowlist result, with no class/pickAny override. */
    switch( warMode ) {
    case 1: return weapon == WP_PANZERFAUST;
    case 2: return weapon == WP_GARAND || weapon == WP_K43;
    case 3: return weapon == WP_KAR98 || weapon == WP_CARBINE;
    case 4: return weapon == WP_KNIFE;
    }
    if( weapon == WP_KNIFE || pickAnyWeapon ) return 1;
    cls = entity->client->sess.playerType;
    if( cls < PC_SOLDIER || cls > PC_COVERTOPS ) return 0;
    /* Explicit caller-owned BG_Weapons class mask, not an inferred skill. */
    if( classMask & (1u << cls) ) return 1;
    switch( cls ) {
    case PC_SOLDIER:
        return weapon == WP_PANZERFAUST || weapon == WP_FLAMETHROWER ||
            weapon == WP_MOBILE_MG42 || weapon == WP_MORTAR ||
            weapon == WP_MP40 || weapon == WP_THOMPSON;
    case PC_MEDIC:
        return !(medicOptions & 4u) &&
            (weapon == WP_MP40 || weapon == WP_THOMPSON || weapon == WP_STEN);
    case PC_ENGINEER:
        return weapon == WP_MP40 || weapon == WP_THOMPSON ||
            weapon == WP_KAR98 || weapon == WP_CARBINE;
    case PC_FIELDOPS:
        return weapon == WP_MP40 || weapon == WP_THOMPSON || weapon == WP_STEN;
    case PC_COVERTOPS:
        return weapon == WP_STEN || weapon == WP_FG42 ||
            weapon == WP_GARAND || weapon == WP_K43;
    }
    return 0;
}
