#include "g_local.h"
#include "g_nitmod_restrictions.h"
#include "nitmod_class_primaries.h"

int G_NITMOD_IsClassPrimary( const gentity_t *entity, int nativeWeapon,
    int pickupContext, int pickAnyWeapon ) {
    int team, cls;
    if( !entity || !entity->client || nativeWeapon < WP_NONE ||
        nativeWeapon >= WP_NUM_WEAPONS ) return 0;
    team = entity->client->sess.sessionTeam;
    if( team != TEAM_AXIS && team != TEAM_ALLIES ) return 0;
    /* Original override precedes WP_NONE rejection and class-table access. */
    if( pickupContext && pickAnyWeapon ) return 1;
    cls = entity->client->sess.playerType;
    if( nativeWeapon == WP_NONE || cls < PC_SOLDIER || cls > PC_COVERTOPS ) return 0;
    return NITMOD_ClassHasPrimary(team, cls, nativeWeapon);
}

int G_NITMOD_StenAllowed( const gentity_t *entity, int pickupContext,
    int pickAnyWeapon, unsigned int weaponsOptions ) {
    if( !entity || !entity->client ) return 0;
    return entity->client->sess.playerType == PC_COVERTOPS ||
        (pickupContext && pickAnyWeapon) || (weaponsOptions & 0x200u) != 0;
}

int G_NITMOD_LimitMessage( const gentity_t *entity, int nativeWeapon,
    nitmodWeaponLimit_t limit, int isClassPrimary, int silent ) {
    if( !entity || !entity->client || !isClassPrimary || silent ||
        (entity->client->ps.pm_flags & PMF_LIMBO) ) return 0;
    if( limit == NITMOD_LIMIT_HEAVY ) return 0x13;
    if( limit == NITMOD_LIMIT_PANZER_TEAM ) return 0x14;
    if( limit != NITMOD_LIMIT_FIXED ) return 0;
    switch( nativeWeapon ) {
    case WP_PANZERFAUST: return 0x15;
    case WP_FLAMETHROWER: return 0x16;
    case WP_MOBILE_MG42: return 0x17;
    case WP_MORTAR: return 0x18;
    case WP_GPG40:
    case WP_M7: return 0x19;
    default: return 0;
    }
}

nitmodWeaponDecision_t G_NITMOD_WeaponPrecheck( const gentity_t *entity,
    int nativeWeapon, int warMode ) {
    if( !entity || !entity->client || nativeWeapon < WP_NONE || nativeWeapon >= WP_NUM_WEAPONS )
        return NITMOD_WEAPON_DENY;
    if( entity->client->sess.sessionTeam == TEAM_SPECTATOR && !(entity->r.svFlags & SVF_BOT) )
        return NITMOD_WEAPON_DENY;
    switch( warMode ) {
    case 1:
        if( nativeWeapon == WP_PANZERFAUST ) return NITMOD_WEAPON_ALLOW;
        break;
    case 2:
        /* Original IDs 24/30: base Garand/K43, NOT scoped variants. */
        if( nativeWeapon == WP_GARAND || nativeWeapon == WP_K43 ) return NITMOD_WEAPON_ALLOW;
        break;
    case 3:
        if( nativeWeapon == WP_GPG40 || nativeWeapon == WP_M7 ||
            nativeWeapon == WP_KAR98 || nativeWeapon == WP_CARBINE ) return NITMOD_WEAPON_ALLOW;
        break;
    case 4:
        if( nativeWeapon == WP_KNIFE ) return NITMOD_WEAPON_ALLOW;
        break;
    }
    /* Caller must continue with team counts, heavy limits, class rules and
     * notification policy. Do not replace native G_IsWeaponDisabled with
     * this incomplete precheck, or interpret non-DENY as allowed. */
    return NITMOD_WEAPON_DEFER;
}
