#include "g_local.h"
#include <stddef.h>
#include <stdio.h>
vmCvar_t n_preciseLandmineTrigger;
vec_t VectorLengthSquared(const vec3_t v) { return v[0]*v[0]+v[1]*v[1]+v[2]*v[2]; }
static gclient_t client;
static int CheckBotPolicy(void) {
    gentity_t candidate;
    int flags, bot, same, spotted, errors = 0, cases = 0;
    memset(&candidate, 0, sizeof(candidate)); candidate.client = &client;
    if(SVF_BOT != 8 || offsetof(entityState_t, modelindex2) != 0xa8) ++errors;
    for(flags = 0; flags < 256; ++flags) for(bot = 0; bot < 2; ++bot)
    for(same = 0; same < 2; ++same) for(spotted = 0; spotted < 2; ++spotted) {
        int expected = !(!(flags & 32) && bot && (same || spotted));
        candidate.r.svFlags = SVF_BROADCAST | (bot ? SVF_BOT : 0);
        client.sess.sessionTeam = same ? TEAM_AXIS : TEAM_ALLIES;
        if(G_NITMOD_MineBotContact(&candidate, TEAM_AXIS, (qboolean)spotted, flags) != expected) ++errors;
        ++cases;
    }
    candidate.client = NULL;
    if(G_NITMOD_MineBotContact(NULL, TEAM_AXIS, qfalse, 32) ||
       G_NITMOD_MineBotContact(&candidate, TEAM_AXIS, qfalse, 32)) ++errors;
    printf("Mine bot policy: %d cases, %d errors\n", cases, errors);
    return errors;
}
static int CheckTeamPolicy(void) {
    gentity_t candidate, owner;
    static const int weapons[] = {WP_MP40, WP_PLIERS, WP_SMOKE_MARKER};
    int flags, team, present, same, weapon, errors = 0, cases = 0;
    memset(&candidate, 0, sizeof(candidate)); memset(&owner, 0, sizeof(owner));
    candidate.client = &client; candidate.s.clientNum = 7; owner.s.number = 99;
    if(offsetof(entityState_t, clientNum) != 0xac) ++errors;
    for(flags = 0; flags < 512; ++flags) for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team)
    for(present = 0; present < 2; ++present) for(same = 0; same < 2; ++same)
    for(weapon = 0; weapon < 3; ++weapon) {
        int expected = !(present && (((flags & 32) && team == TEAM_AXIS && !same) ||
                                    ((flags & 256) && same && weapon != 1)));
        client.sess.sessionTeam = (team_t)team;
        candidate.s.weapon = weapons[weapon];
        /* Deliberate mismatch: original reads entityState, not playerState. */
        client.ps.weapon = weapon == 1 ? WP_MP40 : WP_PLIERS;
        owner.s.clientNum = same ? 7 : 8;
        if(G_NITMOD_MineTeamContact(&candidate, present ? &owner : NULL,
                                   TEAM_AXIS, flags) != expected) ++errors;
        ++cases;
    }
    candidate.client = NULL;
    if(G_NITMOD_MineTeamContact(&candidate, &owner, TEAM_AXIS, 0) ||
       G_NITMOD_MineTeamContact(NULL, &owner, TEAM_AXIS, 0)) ++errors;
    printf("Mine team policy: %d cases, %d errors\n", cases, errors);
    return errors;
}
int main(void) {
    static const float positions[] = {-64, -24, -23.99f, -23.5f, 0, 23.5f, 23.99f, 24, 64, 64.01f};
    static const int flags[] = {0, EF_DEAD, EF_PRONE, EF_SPARE0, EF_TALK};
    gentity_t player, mine;
    int enabled, latch, flag, x, axis, cases = 0, errors = 0;
    errors += CheckTeamPolicy();
    errors += CheckBotPolicy();
    if(offsetof(playerState_t, eFlags) != 0x68 || (EF_DEAD|EF_PRONE|EF_SPARE0) != 0x880001) ++errors;
    memset(&player, 0, sizeof(player)); memset(&mine, 0, sizeof(mine));
    player.s.eType = ET_PLAYER; player.client = &client;
    VectorSet(mine.r.mins, -16,-16,0); VectorSet(mine.r.maxs,16,16,16);
    for(enabled=0; enabled<2; ++enabled) for(latch=0; latch<2; ++latch)
    for(flag=0; flag<5; ++flag) for(axis=0; axis<2; ++axis) for(x=0; x<10; ++x) {
        int broad = !enabled || latch || (flags[flag] & 0x880001);
        int expected = broad ? fabs(positions[x]) <= 64 : fabs(positions[x]) < 24;
        n_preciseLandmineTrigger.integer=enabled; mine.s.onFireStart=latch;
        client.ps.eFlags=flags[flag]; VectorClear(player.r.currentOrigin);
        player.r.currentOrigin[axis]=positions[x];
        if(sEntWillTriggerMine(&player,&mine) != expected) ++errors;
        ++cases;
    }
    n_preciseLandmineTrigger.integer=1; mine.s.onFireStart=0; client.ps.eFlags=0;
    VectorClear(player.r.currentOrigin);
    player.r.currentOrigin[2]=29; if(sEntWillTriggerMine(&player,&mine)) ++errors;
    player.r.currentOrigin[2]=28.99f; if(!sEntWillTriggerMine(&player,&mine)) ++errors;
    player.r.currentOrigin[2]=-61; if(sEntWillTriggerMine(&player,&mine)) ++errors;
    player.r.currentOrigin[2]=-60.99f; if(!sEntWillTriggerMine(&player,&mine)) ++errors;
    VectorClear(player.r.currentOrigin);
    mine.r.mins[0]=-10; mine.r.maxs[0]=20;
    player.r.currentOrigin[0]=14; if(sEntWillTriggerMine(&player,&mine)) ++errors;
    player.r.currentOrigin[0]=13.99f; if(!sEntWillTriggerMine(&player,&mine)) ++errors;
    player.s.eType=ET_GENERAL; if(sEntWillTriggerMine(&player,&mine)) ++errors;
    player.s.eType=ET_PLAYER; player.client=NULL; if(sEntWillTriggerMine(&player,&mine)) ++errors;
    if(sEntWillTriggerMine(NULL,&mine) || sEntWillTriggerMine(&player,NULL)) ++errors;
    printf("Mine contact: %d policy cases plus boundary/guard checks, %d errors\n", cases, errors);
    return errors != 0;
}
