#include "g_local.h"
#include <limits.h>

/* Original satchel spawn option. Called after baseline spawn initialization;
 * no retroactive mutation of already spawned entities on Cvar updates. */
void G_NITMOD_ConfigureSatchelDamage( gentity_t *entity, int damageWeaponFlags ) {
    if( entity && (damageWeaponFlags & 2) ) {
        entity->health = 40;
        entity->takedamage = qtrue;
        entity->die = G_NITMOD_SatchelDie;
    }
}

/* Original Nit_SatchelDie, ELF 0x8a5f0. */
void G_NITMOD_SatchelDie( gentity_t *self, gentity_t *inflictor,
    gentity_t *attacker, int damage, int mod ) {
    gentity_t *owner;
    (void)inflictor; (void)attacker; (void)damage; (void)mod;
    if( !self || self->s.eType != ET_MISSILE ) return;
    self->free = NULL;
    self->r.contents = CONTENTS_CORPSE;
    self->nextthink = level.time == INT_MAX ? INT_MIN : level.time + 1;
    self->think = G_ExplodeMissile;
    /* Original assumes a valid owner; reject malformed indices safely. */
    if( self->s.clientNum < 0 || self->s.clientNum >= MAX_GENTITIES ) return;
    owner = &g_entities[self->s.clientNum];
    if( !owner->client ) return;
    owner->client->ps.ammo[WP_SATCHEL_DET] = 0;
    owner->client->ps.ammoclip[WP_SATCHEL_DET] = 0;
    owner->client->ps.ammoclip[WP_SATCHEL] = 1;
    if( owner->client->ps.weapon == WP_SATCHEL_DET ) G_AddEvent(owner, EV_NOAMMO, 0);
}
