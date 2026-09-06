#include "g_local.h"
#include <assert.h>
#include <stdio.h>
vmCvar_t g_gametype, g_DMOptions;
static unsigned int unlocks;
unsigned int G_NITMOD_FirstAidUnlocks(const gclient_t *client) { return unlocks; }
int BG_EffectiveMaxHealth(const playerState_t *ps) { return 112; }
int main(void) {
    static gentity_t ent;
    static gclient_t client;
    int flags, health, cases = 0, war;
    ent.client = &client;
    client.ps.stats[STAT_MAX_HEALTH] = 100;
    client.sess.playerType = PC_MEDIC;
    for(flags = 0; flags < 4; ++flags) for(health = 97; health <= 114; ++health) {
        unsigned int options = (flags & 1 ? 64 : 0) | (flags & 2 ? 128 : 0);
        int expected = health, tick, extra = flags & 1 ? 1 : flags & 2 ? 0 : 2;
        ent.health = health; client.timeResidual = 500;
        for(tick = 0; tick < 2; ++tick) {
            if(expected < 100) { expected += extra + 1; if(expected > 100) expected = 100; }
            else if(expected < 112) { expected += extra; if(expected > 112) expected = 112; }
        }
        G_NITMOD_HealthTimer(&ent, 1750, options, 0);
        assert(ent.health == expected && client.timeResidual == 250); ++cases;
    }
    for(war = 1; war <= 4; ++war) {
        ent.health = 90; client.timeResidual = 900;
        G_NITMOD_HealthTimer(&ent, 2000, 0, war);
        assert(ent.health == 90 && client.timeResidual == 900);
    }
    G_NITMOD_HealthTimer(&ent, 2000, 32, 0);
    assert(ent.health == 90 && client.timeResidual == 900);
    client.sess.playerType = PC_SOLDIER; client.timeResidual = 0;
    ent.health = 115;
    G_NITMOD_HealthTimer(&ent, 2500, 0, 0);
    assert(ent.health == 113 && client.timeResidual == 500);
    g_gametype.integer = GT_WOLF_DM;
    ent.health = 90; client.timeResidual = 0; unlocks = 32;
    G_NITMOD_HealthTimer(&ent, 1000, 16, 0);
    assert(ent.health == 93 && client.timeResidual == 0);
    printf("WASM health timer: %d rate/limit cases, gates, decay and DM reward passed\n", cases);
    return 0;
}
