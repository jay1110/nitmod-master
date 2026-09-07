#define main pack_team_fixture_main
#include "test_nitmod_pack_team_wasm.c"
#undef main
vmCvar_t g_dropHealth, g_dropAmmo, g_gamestate;
static int testWar;
int trap_Cvar_VariableIntegerValue(const char *name) {
    assert(!strcmp(name,"g_war")); return testWar;
}
int main(void) {
    static gclient_t client;
    static gentity_t owner;
    const int available[]={-10,0,6000,6001,10000,90000};
    const int requested[]={1,4,12};
    int team,health,mask,numeric,a,n,count=0;
    owner.client=&client; owner.s.number=7;
    level.time=100000; g_gamestate.integer=GS_PLAYING;
    level.medicChargeTime[0]=40000; level.medicChargeTime[1]=30000;
    level.lieutenantChargeTime[0]=20000; level.lieutenantChargeTime[1]=60000;
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team)
    for(health=0;health<2;++health)
    for(mask=0;mask<64;++mask)
    for(numeric=0;numeric<2;++numeric)
    for(a=0;a<6;++a)
    for(n=0;n<3;++n)
    for(testNoCharge=0;testNoCharge<2;++testNoCharge)
    for(testWar=0;testWar<=5;++testWar) {
        int duration=health ? level.medicChargeTime[team-1] : level.lieutenantChargeTime[team-1];
        int expected=level.time-available[a];
        int drops=(testWar>=1 && testWar<=4) ? 0 : requested[n]>10 ? 10 : requested[n];
        int i;
        memset(&client,0,sizeof(client));
        client.sess.sessionTeam=team;
        client.sess.playerType=health ? PC_MEDIC : PC_FIELDOPS;
        client.sess.skill[SK_FIRST_AID]=client.sess.skill[SK_SIGNALS]=numeric ? 5 : 0;
        client.sess.nitmodSkillMasks[health ? SK_FIRST_AID : SK_SIGNALS]=mask;
        client.sess.nitmodSkillMasks[health ? SK_SIGNALS : SK_FIRST_AID]=mask^63;
        client.ps.classWeaponTime=expected;
        g_dropHealth.integer=g_dropAmmo.integer=requested[n];
        for(i=0;i<drops && !testNoCharge;++i) {
            const long long denominator=33554432LL;
            long long cost=(long long)duration*((mask&2) ? 5033165 : 8388608);
            if(level.time-expected>duration) expected=level.time-duration;
            if((long long)(level.time-expected)*denominator>=cost)
                expected=(int)(((long long)expected*denominator+cost)/denominator);
        }
        launches=0;
        NITMOD_DropLimboPacks(&owner);
        assert(launches==drops);
        assert(client.ps.classWeaponTime==expected);
        if(drops) assert(pack.parent==&owner && pack.s.teamNum==team);
        ++count;
    }
    printf("Limbo charge: %d actual drop/mask/team/timing/bypass cases passed\n",count);
    return 0;
}
