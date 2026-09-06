#include "q_shared.h"
#include "bg_public.h"
#include "nitmod_grenade_rewards.h"
#include <assert.h>
#include <stdio.h>
vmCvar_t ui_gameType;
int main(void) {
    float rows[7][6]={{0},{4,8,8,8,8,8},{1,2,2,2,2,3},
        {1,2,2,2,2,3},{0},{4,4,4,4,4,5},{2,2,2,2,2,3}};
    const int skills[]={5,2,1,3,6};
    unsigned int masks[7]={0};
    int cls,mask,war,cases=0;
    for(cls=0;cls<5;++cls) for(mask=0;mask<64;++mask) for(war=0;war<2;++war) {
        int expected=(int)NITMOD_RewardTableValue(rows[skills[cls]],mask);
        masks[skills[cls]]=mask;
        assert(NITMOD_GrenadeRewardCount(cls,rows,masks,war)==(war?0:expected));
        assert(BG_NitmodGrenadesForClass(cls,masks,war)==(war?0:expected));
        masks[skills[cls]]=0; ++cases;
    }
    rows[SK_LIGHT_WEAPONS][1]=2;
    masks[SK_LIGHT_WEAPONS]=2;
    assert(NITMOD_GrenadeRewardCount(PC_ENGINEER,rows,masks,0)==6);
    /* Original x87 control word sets truncation before EACH fistpl. */
    rows[SK_LIGHT_WEAPONS][1]=1.75f;
    rows[SK_EXPLOSIVES_AND_CONSTRUCTION][0]=4.75f;
    assert(NITMOD_GrenadeRewardCount(PC_ENGINEER,rows,masks,0)==5);
    rows[SK_LIGHT_WEAPONS][1]=-1.75f;
    assert(NITMOD_GrenadeRewardCount(PC_ENGINEER,rows,masks,0)==3);
    puts("Grenade rewards WASM: 640 class/mask/war cases and additive light-weapons reward passed");
    return 0;
}
