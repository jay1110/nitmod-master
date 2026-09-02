#include "g_local.h"
#include "g_nitmod_teamcount.h"
#include "g_nitmod_config.h"

int G_NITMOD_CanPickupWeapon( gentity_t *entity, int nativeWeapon,
    unsigned int classMask ) {
    nitmodWeaponPolicyInput_t input;
    nitmodWeaponPolicyResult_t result;
    unsigned int medicOptions;
    int slot;
    if( !entity || !entity->client || !level.clients ||
        nativeWeapon < WP_NONE || nativeWeapon >= WP_NUM_WEAPONS ) return -1;
    for( slot = 0; slot < MAX_CLIENTS; slot++ ) if( entity == &g_entities[slot] ) break;
    if( slot == MAX_CLIENTS || entity->client != &level.clients[slot] ) return -1;
    memset(&input, 0, sizeof(input));
    input.pickupContext = 1;
    if( !G_NITMOD_ReadWeaponConfiguration(&input) || !G_NITMOD_ReadMedicOptions(&medicOptions) ) return -1;
    if( G_NITMOD_WeaponPrecheck(entity, nativeWeapon, input.warMode) == NITMOD_WEAPON_DEFER &&
        !G_NITMOD_ReadCachedWeaponCounts(entity, nativeWeapon, &input) ) return -1;
    result = G_NITMOD_EvaluateWeaponPolicy(entity, nativeWeapon, &input);
    if( result.limit == NITMOD_LIMIT_INVALID || result.decision == NITMOD_WEAPON_DEFER ) return -1;
    if( result.decision == NITMOD_WEAPON_DENY ) {
        if( result.messageReason ) NITMOD_SendWeaponLimitMessage(slot, result.messageReason);
        return 0;
    }
    return G_NITMOD_PickupPolicy(entity, nativeWeapon, result.decision,
        input.warMode, input.pickAnyWeapon, classMask, medicOptions);
}

nitmodWeaponPolicyResult_t G_NITMOD_EvaluateServerWeaponPolicy(
    gentity_t *entity, int nativeWeapon, int pickupContext, int silent ) {
    nitmodWeaponPolicyInput_t input;
    nitmodWeaponPolicyResult_t invalid;
    invalid.decision = NITMOD_WEAPON_DENY;
    invalid.limit = NITMOD_LIMIT_INVALID;
    invalid.messageReason = 0;
    if( !entity || !entity->client || nativeWeapon < WP_NONE ||
        nativeWeapon >= WP_NUM_WEAPONS ) return invalid;
    memset(&input, 0, sizeof(input));
    input.pickupContext = pickupContext;
    input.silent = silent;
    if( !G_NITMOD_ReadWeaponConfiguration(&input) ) return invalid;
    /* Original exemptions precede counts; an uninitialized cache must not
     * change those decisions. No implicit population refresh here. */
    if( G_NITMOD_WeaponPrecheck(entity, nativeWeapon, input.warMode) == NITMOD_WEAPON_DEFER &&
        !G_NITMOD_ReadCachedWeaponCounts(entity, nativeWeapon, &input) ) return invalid;
    return G_NITMOD_EvaluateWeaponPolicy(entity, nativeWeapon, &input);
}

nitmodWeaponPolicyResult_t G_NITMOD_CheckWeaponAndNotify(
    gentity_t *entity, int nativeWeapon, int pickupContext, int silent ) {
    nitmodWeaponPolicyResult_t result;
    int slot;
    result.decision = NITMOD_WEAPON_DENY;
    result.limit = NITMOD_LIMIT_INVALID;
    result.messageReason = 0;
    if( !entity || !entity->client || !level.clients ) return result;
    for( slot = 0; slot < MAX_CLIENTS; slot++ )
        if( entity == &g_entities[slot] ) break;
    if( slot == MAX_CLIENTS || entity->client != &level.clients[slot] ) return result;
    result = G_NITMOD_EvaluateServerWeaponPolicy(entity, nativeWeapon, pickupContext, silent);
    if( result.decision == NITMOD_WEAPON_DENY && result.messageReason )
        NITMOD_SendWeaponLimitMessage(slot, result.messageReason);
    return result;
}
