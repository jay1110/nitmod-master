#include "g_local.h"
#include <assert.h>
#include <stdio.h>

level_locals_t level;
static int notifications, callbacks, unlinks;
void G_NITMOD_BotEntityDeleted(gentity_t *ent) { ++notifications; }
void Bot_Event_EntityDeleted(gentity_t *ent) { ++notifications; }
void G_NITMOD_UnregisterSatchel(gentity_t *ent) {}
void G_NITMOD_UnregisterLandmine(gentity_t *ent) {}
void trap_UnlinkEntity(gentity_t *ent) { ++unlinks; }
static void released(gentity_t *ent) {
    assert(ent->nitmodDynamiteObjective == 100);
    assert(ent->etpro_misc_1 & 1);
    ++callbacks;
}
int main(void) {
    static gentity_t ent;
    level.time = 1234;
    ent.inuse = qtrue; ent.spawnCount = 7;
    ent.etpro_misc_1 = 1; ent.nitmodDynamiteObjective = 100;
    ent.free = released;
    G_FreeEntity(&ent);
    assert(notifications == 2 && callbacks == 1 && unlinks == 1);
    assert(!ent.inuse && ent.spawnCount == 7 && ent.freetime == 1234);
    assert(ent.etpro_misc_1 == 0 && ent.nitmodDynamiteObjective == 0);
    ent.inuse = qtrue; ent.neverFree = qtrue;
    ent.etpro_misc_1 = 1; ent.nitmodDynamiteObjective = 100;
    ent.free = released;
    G_FreeEntity(&ent);
    assert(notifications == 4 && callbacks == 2 && unlinks == 2);
    assert(ent.inuse && ent.nitmodDynamiteObjective == 100 && ent.etpro_misc_1 == 1);
    puts("WASM G_FreeEntity: association cleared after callbacks; neverFree preserved");
    return 0;
}
