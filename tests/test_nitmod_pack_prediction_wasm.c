#include "../src_2.60/game/bg_pmove.c"
#include <assert.h>
#include <stdio.h>
int main(void) {
    pmove_t move;
    playerState_t state, saved;
    const int skills[]={SK_HEAVY_WEAPONS,SK_FIRST_AID,SK_EXPLOSIVES_AND_CONSTRUCTION,SK_SIGNALS,SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS};
    const int durations[]={40000,30000,20000,60000,1000};
    const int elapsed[]={-1,0,149,150,151,6000,6001,10000,90000};
    int cls, weapon, mask, a, numeric, count=0, levels[SK_NUM_SKILLS];
    memset(&move,0,sizeof(move)); memset(&state,0,sizeof(state));
    move.ps=&state; move.skill=levels; move.cmd.serverTime=100000;
    move.soldierChargeTime=durations[0]; move.medicChargeTime=durations[1];
    move.engineerChargeTime=durations[2]; move.ltChargeTime=durations[3];
    move.covertopsChargeTime=durations[4];
    for(cls=0;cls<5;++cls) for(weapon=0;weapon<2;++weapon)
    for(mask=0;mask<64;++mask) for(a=0;a<9;++a) for(numeric=0;numeric<2;++numeric) {
        int i;
        long long cost=(long long)durations[cls]*((mask&2) ? 5033165 : 8388608);
        int expected=(long long)elapsed[a]*33554432LL>=cost;
        state.stats[STAT_PLAYER_CLASS]=cls;
        state.weapon=weapon ? WP_MEDKIT : WP_AMMO;
        state.classWeaponTime=move.cmd.serverTime-elapsed[a];
        for(i=0;i<SK_NUM_SKILLS;++i) {
            levels[i]=numeric ? 5 : 0;
            move.nitmodPackSkillMasks[i]=mask^63;
        }
        move.nitmodPackSkillMasks[skills[cls]]=mask;
        saved=state;
        assert(PM_NITMOD_PackChargeAvailable(&move)==expected);
        assert(!memcmp(&saved,&state,sizeof(state)));
        ++count;
    }
    move.nitmodPackChargeBypass=qtrue;
    state.classWeaponTime=move.cmd.serverTime+10000;
    assert(PM_NITMOD_PackChargeAvailable(&move));
    printf("Pack prediction: %d actual gate class/mask/time cases plus bypass passed\n",count);
    return 0;
}
