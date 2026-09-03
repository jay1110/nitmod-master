#include "g_local.h"
#include <limits.h>
#include <stdio.h>
level_locals_t level;
static int errors;
void G_ExplodeMissile(gentity_t *entity) { (void)entity; ++errors; }
int main(void) {
    static const int times[] = {0, -1, 100, INT_MAX};
    gentity_t entity, expected;
    int flags, axis, t, type, kind, mask;
    G_NITMOD_ConfigureSmokeDamage(NULL, 8);
    G_NITMOD_WeaponDie(NULL, NULL, NULL, 0, 0);
    G_NITMOD_ConfigureGrenadeDamage(NULL, 1);
    G_NITMOD_ConfigureAirstrikeMarkerDamage(NULL, 4);
    for(kind = 0; kind < 3; ++kind) for(flags = 0; flags < 256; ++flags) {
        mask = kind == 2 ? 4 : kind ? 1 : 8;
        memset(&entity, 0, sizeof(entity)); entity.health = 5;
        expected = entity;
        if(flags & mask) {
            expected.health = 40; expected.takedamage = qtrue;
            expected.r.contents = CONTENTS_CORPSE; expected.die = G_NITMOD_WeaponDie;
            for(axis = 0; axis < 3; ++axis) {
                expected.r.mins[axis] = expected.r.absmin[axis] = axis == 2 ? 0 : -4;
                expected.r.maxs[axis] = expected.r.absmax[axis] = axis == 2 ? 6 : 4;
            }
        }
        if(kind == 2) G_NITMOD_ConfigureAirstrikeMarkerDamage(&entity, flags);
        else if(kind) G_NITMOD_ConfigureGrenadeDamage(&entity, flags);
        else G_NITMOD_ConfigureSmokeDamage(&entity, flags);
        if(memcmp(&entity, &expected, sizeof(entity))) ++errors;
    }
    for(t = 0; t < 4; ++t) for(type = 0; type < 2; ++type) {
        memset(&entity, 0, sizeof(entity));
        entity.s.eType = type ? ET_MISSILE : ET_GENERAL;
        G_NITMOD_ConfigureSmokeDamage(&entity, 8);
        entity.free = G_ExplodeMissile; level.time = times[t];
        expected = entity;
        expected.free = NULL; expected.r.contents = CONTENTS_CORPSE;
        expected.think = G_ExplodeMissile;
        expected.nextthink = times[t] == INT_MAX ? INT_MIN : times[t] + 1;
        entity.die(&entity, &entity, NULL, 42, 0);
        if(memcmp(&entity, &expected, sizeof(entity))) ++errors;
    }
    printf("Smoke/grenade/marker damage: 768 mask cases, 8 death cases, %d errors\n", errors);
    return errors != 0;
}
