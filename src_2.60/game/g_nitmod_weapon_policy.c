#include <limits.h>
#include "g_local.h"
#include "g_nitmod_restrictions.h"

nitmodWeaponPolicyResult_t G_NITMOD_EvaluateWeaponPolicy(
    const gentity_t *entity, int nativeWeapon,
    const nitmodWeaponPolicyInput_t *input ) {
    nitmodWeaponPolicyResult_t result;
    nitmodWeaponLimitInput_t numeric;
    int cap = -1, count;
    result.decision = NITMOD_WEAPON_DENY;
    result.limit = NITMOD_LIMIT_INVALID;
    result.messageReason = 0;
    if( !input || !entity || !entity->client ||
        nativeWeapon < WP_NONE || nativeWeapon >= WP_NUM_WEAPONS ) return result;
    result.limit = NITMOD_LIMIT_NONE;
    result.decision = G_NITMOD_WeaponPrecheck(entity, nativeWeapon, input->warMode);
    if( result.decision != NITMOD_WEAPON_DEFER ) return result;

    memset(&numeric, 0, sizeof(numeric));
    /* Original six-entry bg_heavyWeapons table, ELF 0x2a5144. */
    numeric.isHeavy = nativeWeapon == WP_FLAMETHROWER ||
        nativeWeapon == WP_MOBILE_MG42 || nativeWeapon == WP_MOBILE_MG42_SET ||
        nativeWeapon == WP_PANZERFAUST || nativeWeapon == WP_MORTAR ||
        nativeWeapon == WP_MORTAR_SET;
    numeric.fixedCap = -1;
    if( numeric.isHeavy ) {
        numeric.isPanzer = nativeWeapon == WP_PANZERFAUST;
        numeric.teamSize = input->teamSize;
        numeric.weaponCount = input->weaponCount;
        numeric.heavyPercent = input->heavyPercent;
        numeric.maxClients = input->maxClients;
        numeric.panzerPercent = input->panzerPercent;
        result.limit = NITMOD_EvaluateWeaponLimits(&numeric);
        if( result.limit != NITMOD_LIMIT_NONE ) goto denied;
    }

    if( nativeWeapon == WP_STEN && !G_NITMOD_StenAllowed(entity,
        input->pickupContext, input->pickAnyWeapon, input->weaponsOptions) ) goto denied;
    switch( nativeWeapon ) {
    case WP_PANZERFAUST: cap = input->maxPanzers; break;
    case WP_FLAMETHROWER: cap = input->maxFlamers; break;
    case WP_MOBILE_MG42: cap = input->maxMG42s; break;
    case WP_MORTAR: cap = input->maxMortars; break;
    case WP_GPG40:
    case WP_M7: cap = input->maxRifleGrenades; break;
    default: break;
    }
    /* Unlimited rifle caps return before reading either family count. */
    if( cap != -1 ) {
        count = input->weaponCount;
        if( count < 0 ) { result.limit = NITMOD_LIMIT_INVALID; goto denied; }
        if( nativeWeapon == WP_GPG40 || nativeWeapon == WP_M7 ) {
            if( input->oppositeRifleCount < 0 ||
                input->oppositeRifleCount > INT_MAX - count ) {
                result.limit = NITMOD_LIMIT_INVALID;
                goto denied;
            }
            count += input->oppositeRifleCount;
        }
        if( count >= cap ) { result.limit = NITMOD_LIMIT_FIXED; goto denied; }
    }
    result.decision = NITMOD_WEAPON_ALLOW;
    return result;
denied:
    result.decision = NITMOD_WEAPON_DENY;
    result.messageReason = G_NITMOD_LimitMessage(entity, nativeWeapon,
        result.limit, G_NITMOD_IsClassPrimary(entity, nativeWeapon,
            input->pickupContext, input->pickAnyWeapon), input->silent);
    return result;
}
