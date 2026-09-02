#include "g_local.h"
#include <limits.h>

/* Nit_WeapDie, original qagame ELF 0x89390. Unlike the satchel-specific
 * handler, this has no missile guard and no owner inventory/event updates. */
void G_NITMOD_WeaponDie( gentity_t *self, gentity_t *inflictor,
    gentity_t *attacker, int damage, int mod ) {
    (void)inflictor; (void)attacker; (void)damage; (void)mod;
    if( !self ) return;
    self->free = NULL;
    self->r.contents = CONTENTS_CORPSE;
    self->nextthink = level.time == INT_MAX ? INT_MIN : level.time + 1;
    self->think = G_ExplodeMissile;
}

static void ConfigureSmallCanisterDamage( gentity_t *entity, int damageWeaponFlags, int mask ) {
    int axis;
    if( !entity || !(damageWeaponFlags & mask) ) return;
    entity->health = 40;
    entity->takedamage = qtrue;
    entity->r.contents = CONTENTS_BODY;
    entity->r.mins[0] = entity->r.mins[1] = -4.0f;
    entity->r.mins[2] = 0.0f;
    entity->r.maxs[0] = entity->r.maxs[1] = 4.0f;
    entity->r.maxs[2] = 6.0f;
    for( axis = 0; axis < 3; ++axis ) {
        entity->r.absmin[axis] = entity->r.mins[axis];
        entity->r.absmax[axis] = entity->r.maxs[axis];
    }
    entity->die = G_NITMOD_WeaponDie;
}

void G_NITMOD_ConfigureSmokeDamage( gentity_t *entity, int damageWeaponFlags ) {
    ConfigureSmallCanisterDamage( entity, damageWeaponFlags, 8 );
}

void G_NITMOD_ConfigureGrenadeDamage( gentity_t *entity, int damageWeaponFlags ) {
    ConfigureSmallCanisterDamage( entity, damageWeaponFlags, 1 );
}

void G_NITMOD_ConfigureAirstrikeMarkerDamage( gentity_t *entity, int damageWeaponFlags ) {
    ConfigureSmallCanisterDamage( entity, damageWeaponFlags, 4 );
}
