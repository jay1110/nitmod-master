#include "g_local.h"

/* qagame ELF 0x8a570: restore the connected covert-op's satchel inventory.
 * Unlike ET baseline, the original does not emit EV_NOAMMO here. */
void G_FreeSatchel( gentity_t *entity ) {
    gentity_t *owner;
    if( !entity ) return;
    entity->free = NULL;
    if( entity->s.eType != ET_MISSILE ) return;
    /* Defensive bounds check absent from the original; preserve valid owners. */
    if( entity->s.clientNum < 0 || entity->s.clientNum >= MAX_GENTITIES ) return;
    owner = &g_entities[entity->s.clientNum];
    if( !owner->client || owner->client->pers.connected != CON_CONNECTED ||
        owner->client->sess.playerType != PC_COVERTOPS ) return;
    owner->client->ps.ammo[WP_SATCHEL_DET] = 0;
    owner->client->ps.ammoclip[WP_SATCHEL_DET] = 0;
    owner->client->ps.ammoclip[WP_SATCHEL] = 1;
}
