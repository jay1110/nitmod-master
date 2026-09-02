#include "g_local.h"
#include "g_nitmod_restrictions.h"

/* Original G_SetClientWeapons: latch secondary regardless of primary denial;
 * clear a denied primary; publish only if either latch changed. Invalid
 * reconstruction inputs are an atomic failure, not a gameplay denial. */
int G_NITMOD_SetClientWeapons( gentity_t *entity, int primary, int secondary,
    int updateClient ) {
    nitmodWeaponPolicyResult_t result;
    int slot, nextPrimary, changed;
    if( !entity || !entity->client || !level.clients ||
        primary < WP_NONE || primary >= WP_NUM_WEAPONS ||
        secondary < WP_NONE || secondary >= WP_NUM_WEAPONS ) return -1;
    for( slot = 0; slot < MAX_CLIENTS; slot++ ) if( entity == &g_entities[slot] ) break;
    if( slot == MAX_CLIENTS || entity->client != &level.clients[slot] ) return -1;
    result = G_NITMOD_CheckWeaponAndNotify(entity, primary, 0, 0);
    if( result.limit == NITMOD_LIMIT_INVALID || result.decision == NITMOD_WEAPON_DEFER ) return -1;
    nextPrimary = result.decision == NITMOD_WEAPON_ALLOW ? primary : WP_NONE;
    changed = entity->client->sess.latchPlayerWeapon != nextPrimary ||
        entity->client->sess.latchPlayerWeapon2 != secondary;
    entity->client->sess.latchPlayerWeapon = nextPrimary;
    entity->client->sess.latchPlayerWeapon2 = secondary;
    if( changed && updateClient ) ClientUserinfoChanged(slot);
    return changed;
}
