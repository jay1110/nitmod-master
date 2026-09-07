#define main pack_team_fixture_main
#include "test_nitmod_pack_team_wasm.c"
#undef main
int main(void) {
    static gclient_t client;
    static gentity_t owner;
    int team,health,mask,numeric,a,repeat,count=0;
    const int available[]={-1,0,6000,6001,10000,90000};
    owner.client=&client; owner.s.number=7; level.time=100000;
    level.medicChargeTime[0]=40000; level.medicChargeTime[1]=30000;
    level.lieutenantChargeTime[0]=20000; level.lieutenantChargeTime[1]=60000;
    for(testPackCapability=0;testPackCapability<2;++testPackCapability)
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team) for(health=0;health<2;++health)
    for(mask=0;mask<64;++mask) for(numeric=0;numeric<2;++numeric)
    for(a=0;a<6;++a) for(testNoCharge=0;testNoCharge<2;++testNoCharge)
    for(testPackWar=0;testPackWar<6;++testPackWar) {
        int duration=health ? level.medicChargeTime[team-1] : level.lieutenantChargeTime[team-1];
        int expected=level.time-available[a];
        memset(&client,0,sizeof(client)); client.sess.sessionTeam=team;
        client.sess.playerType=health ? PC_MEDIC : PC_FIELDOPS;
        client.sess.nitmodSkillMasks[health ? SK_FIRST_AID : SK_SIGNALS]=mask;
        client.sess.skill[SK_FIRST_AID]=client.sess.skill[SK_SIGNALS]=numeric ? 5 : 0;
        client.ps.classWeaponTime=expected;
        for(repeat=0;repeat<3;++repeat) {
            if(!testPackCapability) {
                if(level.time-expected>duration) expected=level.time-duration;
                expected=(int)(expected+duration*(numeric ? 0.15 : 0.25));
            } else if(!testNoCharge && testPackWar!=1 && testPackWar!=3) {
                const long long denominator=33554432LL;
                long long cost=(long long)duration*((mask&2) ? 5033165 : 8388608);
                if(level.time-expected>duration) expected=level.time-duration;
                if((long long)(level.time-expected)*denominator>=cost)
                    expected=(int)(((long long)expected*denominator+cost)/denominator);
            }
            launches=0;
            if(health) Weapon_Medic(&owner); else Weapon_MagicAmmo(&owner);
            assert(launches==1 && client.ps.classWeaponTime==expected);
            ++count;
        }
    }
    printf("Native pack charge: %d negotiated/legacy actual throws passed\n",count);
    return 0;
}
