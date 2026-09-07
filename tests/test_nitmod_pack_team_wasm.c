/* Real throw functions and native item lookup; engine launch/trace doubles. */
#include "../src_2.60/game/g_weapon.c"
#include <assert.h>
#include <stdio.h>
level_locals_t level;
vmCvar_t n_medPackSinkDelay, n_ammoPackSinkDelay;
static gentity_t pack;
static gitem_t *launchedItem;
static int launches;
static int packFrees;
static int testNoCharge;
static int testPackCapability, testPackWar;
qboolean G_NITMOD_ClientSupports(int client, unsigned int feature) {
    assert(client==7 && feature==NITMOD_FEATURE_PACK_CHARGE);
    return testPackCapability;
}
int G_NITMOD_LegacyCvarInteger(const char *name, int fallback) {
    return !strcmp(name,"g_noCharge") ? testNoCharge : !strcmp(name,"g_war") ? testPackWar : fallback;
}
void G_TempTraceIgnorePlayersAndBodies(void) {}
void G_ResetTempTraceIgnoreEnts(void) {}
void trap_Trace(trace_t *tr, const vec3_t start, const vec3_t mins,
    const vec3_t maxs, const vec3_t end, int pass, int mask) {
    memset(tr,0,sizeof(*tr)); tr->fraction=1; VectorCopy(end,tr->endpos);
}
void G_FreeEntity(gentity_t *ent) { assert(ent==&pack); ++packFrees; }
gentity_t *LaunchItem(gitem_t *item, vec3_t origin, vec3_t velocity, int owner) {
    assert(item && owner==7);
    memset(&pack,0,sizeof(pack)); pack.s.teamNum=-1;
    launchedItem=item; ++launches;
    return &pack;
}
int main(void) {
    static gclient_t client;
    static gentity_t owner;
    const int delays[]={-1,4999,5000,30000,60000,60001};
    int team, health, mask, numeric, delay, repeat, count=0;
    level.time=100000;
    level.medicChargeTime[0]=level.medicChargeTime[1]=40000;
    level.lieutenantChargeTime[0]=level.lieutenantChargeTime[1]=40000;
    owner.client=&client; owner.s.number=7;
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team)
    for(health=0;health<2;++health)
    for(mask=0;mask<64;++mask)
    for(numeric=0;numeric<2;++numeric)
    for(delay=0;delay<6;++delay) {
        memset(&client,0,sizeof(client));
        client.sess.sessionTeam=team;
        client.sess.nitmodSkillMasks[SK_SIGNALS]=mask;
        client.sess.skill[SK_SIGNALS]=client.sess.skill[SK_FIRST_AID]=numeric ? 5 : 0;
        n_medPackSinkDelay.integer=n_ammoPackSinkDelay.integer=delays[delay];
        for(repeat=0;repeat<2;++repeat) {
            gitem_t *expected=health ? BG_FindItemForClassName("item_health") :
                BG_FindItem((mask&32) ? "Huge Ammo Pack" : (mask&2) ? "Mega Ammo Pack" : "Ammo Pack");
            int sink=delays[delay]>=5000 && delays[delay]<=60000 ? delays[delay] : 30000;
            launches=0;
            if(health) Weapon_Medic(&owner); else Weapon_MagicAmmo(&owner);
            assert(launches==1 && launchedItem==expected);
            assert(pack.parent==&owner && pack.s.teamNum==team);
            assert(pack.think==MagicSink && pack.nextthink==level.time+sink);
            if(!health) assert(pack.count==((mask&2) ? 2 : 1) && pack.s.density==pack.count);
            ++count;
        }
    }
    printf("Pack team: %d actual throw ownership/item/lifetime cases passed\n",count);
    return 0;
}
