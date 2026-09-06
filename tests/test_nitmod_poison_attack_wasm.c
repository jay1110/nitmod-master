#include "g_local.h"
#include <assert.h>
#include <stdio.h>
level_locals_t level;
gentity_t g_entities[MAX_GENTITIES];
vmCvar_t g_poison, g_friendlyFire, g_gametype;
static gclient_t clients[3];
static int sounds, sameTeam, checkMuzzle;
static float expectedHeight = 40;
static int target = 1;
static float hitFraction = .5f;
void CalcMuzzlePointForActivate(gentity_t *ent, vec3_t f, vec3_t r, vec3_t u, vec3_t out) { VectorClear(out); }
void G_HistoricalTrace(gentity_t *ent, trace_t *trace, const vec3_t start,
    const vec3_t mins, const vec3_t maxs, const vec3_t end, int pass, int mask) {
    if(checkMuzzle) {
        assert(fabs(start[0] - 10.25f) < .0001f);
        assert(fabs(start[1] - (20.5f - ent->client->ps.leanf)) < .0001f);
        vec3_t delta;
        assert(fabs(start[2] - (30.75f + expectedHeight - fabs(ent->client->ps.leanf / 3.5f))) < .0001f);
        VectorSubtract(end, start, delta);
        assert(fabs(VectorLength(delta) - 64) < .0001f);
        assert(pass == ent->s.number && mask == MASK_SHOT);
    }
    trace->fraction = hitFraction; trace->entityNum = target;
}
qboolean OnSameTeam(gentity_t *a, gentity_t *b) { return sameTeam; }
void NITMOD_PlaySoundEvent(gentity_t *ent, int sound) { assert(ent == &g_entities[1] && sound == 8); ++sounds; }
int main(void) {
    int i, mode, ff, team, cases = 0;
    level.maxclients = 3; level.time = 1000; g_poison.integer = 1;
    for(i = 0; i < 3; ++i) { g_entities[i].client = &clients[i]; g_entities[i].s.number = i; g_entities[i].health = 100; }
    assert(G_NITMOD_PoisonAttack(&g_entities[0]));
    assert(clients[1].nitmodPoisonStacks == 1 && clients[1].nitmodPoisonNextTick == 1000);
    clients[1].nitmodPoisonNextTick = 2500;
    level.time = 1100;
    assert(G_NITMOD_PoisonAttack(&g_entities[2]));
    assert(clients[1].nitmodPoisonStacks == 2 && clients[1].nitmodPoisonAttacker == 2);
    assert(clients[1].nitmodPoisonNextTick == 2500 && sounds == 2);
    G_NITMOD_ClearPoison(&g_entities[1]);
    level.time = 3000;
    assert(G_NITMOD_PoisonAttack(&g_entities[0]));
    assert(clients[1].nitmodPoisonStacks == 1 && clients[1].nitmodPoisonNextTick == 3000);
    for(mode = GT_WOLF; mode < GT_MAX_GAME_TYPE; ++mode)
    for(ff = 0; ff < 8; ++ff) for(team = 0; team < 2; ++team) {
        int allowed = (ff & 1) || mode == GT_WOLF_DM || !team;
        G_NITMOD_ClearPoison(&g_entities[1]);
        sounds = 0; sameTeam = team; g_friendlyFire.integer = ff; g_gametype.integer = mode;
        assert(!!G_NITMOD_PoisonAttack(&g_entities[0]) == !!allowed);
        assert(sounds == !!allowed);
        assert(clients[1].nitmodPoisonStacks == !!allowed);
        assert(!!(clients[1].ps.eFlags & NITMOD_EF_POISONED) == !!allowed);
        ++cases;
    }
    sameTeam = 0; checkMuzzle = 1;
    VectorSet(g_entities[0].s.pos.trBase, 10.25f, 20.5f, 30.75f);
    clients[0].ps.viewheight = 40;
    for(i = -1; i <= 1; ++i) {
        clients[0].ps.leanf = i * 7.f;
        assert(G_NITMOD_PoisonAttack(&g_entities[0]));
    }
    clients[0].ps.leanf = 0;
    for(i = 0; i < 3; ++i) {
        static const float pitch[] = {29.99f, 30, 30.01f};
        int stance;
        clients[0].ps.viewangles[PITCH] = pitch[i];
        for(stance = 0; stance < 3; ++stance) {
            clients[0].ps.eFlags = stance == 1 ? EF_CROUCHING : stance == 2 ? EF_PRONE : 0;
            expectedHeight = stance == 1 && i == 2 ? 30 : 40;
            assert(G_NITMOD_PoisonAttack(&g_entities[0]));
        }
    }
    expectedHeight = 25;
    for(i = -1; i <= 0; ++i) {
        g_entities[0].health = i;
        assert(G_NITMOD_PoisonAttack(&g_entities[0]));
    }
    checkMuzzle = 0;
    for(i = -1; i <= 1; ++i) {
        G_NITMOD_ClearPoison(&g_entities[1]); sounds = 0;
        clients[1].ps.powerups[PW_INVULNERABLE] = level.time + i;
        clients[1].invulnerabilityTime = 0;
        assert(!!G_NITMOD_PoisonAttack(&g_entities[0]) == (i < 0));
        assert(sounds == (i < 0) && clients[1].nitmodPoisonStacks == (i < 0));
    }
    clients[1].ps.powerups[PW_INVULNERABLE] = 0;
    clients[1].invulnerabilityTime = level.time + 1000;
    assert(G_NITMOD_PoisonAttack(&g_entities[0]));
    for(i = 0; i < 5; ++i) {
        G_NITMOD_ClearPoison(&g_entities[1]); sounds = 0;
        hitFraction = i == 0 ? 1 : .5f;
        target = i == 1 ? -1 : i == 2 ? level.maxclients : 1;
        g_entities[1].health = i == 3 ? 0 : 100;
        g_entities[1].client = i == 4 ? NULL : &clients[1];
        assert(!G_NITMOD_PoisonAttack(&g_entities[0]));
        assert(!sounds && !clients[1].nitmodPoisonStacks);
    }
    printf("WASM poison attack: immunity/rejection, muzzle, timing and %d team-rule cases passed\n", cases);
    return 0;
}
