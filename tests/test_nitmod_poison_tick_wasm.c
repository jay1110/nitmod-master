#include "g_local.h"
#include <assert.h>
#include <stdio.h>
level_locals_t level;
gentity_t g_entities[MAX_GENTITIES];
vmCvar_t g_poison;
static gclient_t client;
static int intervalOverride, damageOverride, calls, expectedDamage;
static gentity_t *expectedAttacker;
int G_NITMOD_PoisonInterval(int fallback) { return intervalOverride ? intervalOverride : fallback; }
void G_NITMOD_WeaponDamageOverrides(int weapon, int *damage, int *splash, int *radius) {
    assert(weapon == WP_POISON_SYRINGE && !splash && !radius);
    if(damageOverride) *damage = damageOverride;
}
void G_Damage(gentity_t *target, gentity_t *inflictor, gentity_t *attacker,
    vec3_t dir, vec3_t point, int damage, int flags, int mod) {
    assert(target == &g_entities[0] && attacker == expectedAttacker && inflictor == attacker);
    assert(!dir && !point && !flags && mod == MOD_POISON && damage == expectedDamage);
    ++calls;
}
int main(void) {
    int option, custom, stacks, owner, cases = 0;
    level.maxclients = 2;
    g_entities[0].client = &client;
    g_entities[0].health = 100;
    client.sess.sessionTeam = TEAM_AXIS;
    for(option = 0; option < 2; ++option)
    for(custom = 0; custom < 2; ++custom)
    for(stacks = 1; stacks <= 3; ++stacks)
    for(owner = -1; owner <= 2; ++owner) {
        int interval = custom ? 750 : option ? 1500 : 50;
        client.ps.eFlags = NITMOD_EF_POISONED;
        client.nitmodPoisonStacks = stacks;
        client.nitmodPoisonAttacker = owner;
        client.nitmodPoisonNextTick = 1000;
        g_poison.integer = option ? 4 : 1;
        intervalOverride = custom ? 750 : 0;
        damageOverride = custom ? 7 : 0;
        expectedDamage = (custom ? 7 : option ? 10 : 1) * stacks;
        expectedAttacker = owner >= 0 && owner < 2 ? &g_entities[owner] : NULL;
        calls = 0; level.time = 999;
        G_NITMOD_RunPoison(&g_entities[0]); assert(!calls);
        level.time = 1000;
        G_NITMOD_RunPoison(&g_entities[0]); assert(!calls);
        level.time = 1001;
        G_NITMOD_RunPoison(&g_entities[0]);
        assert(calls == 1 && client.nitmodPoisonNextTick == 1001 + interval);
        G_NITMOD_RunPoison(&g_entities[0]); assert(calls == 1);
        ++cases;
    }
    client.sess.sessionTeam = TEAM_SPECTATOR;
    G_NITMOD_RunPoison(&g_entities[0]);
    assert(!(client.ps.eFlags & NITMOD_EF_POISONED) && !client.nitmodPoisonStacks);
    assert(client.nitmodPoisonAttacker == -1 && !client.nitmodPoisonNextTick);
    printf("WASM poison ticks: %d timing/damage/owner combinations and spectator cleanup passed\n", cases);
    return 0;
}
