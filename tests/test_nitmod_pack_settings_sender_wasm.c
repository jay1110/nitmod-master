#include "../src_2.60/game/g_nitmod_config.c"
#include <assert.h>
#include <stdio.h>
level_locals_t level;
void Com_Error(int code,const char *format,...) { abort(); }
static int testWar,testNoCharge,sent[2],chargeMessages[2];
int G_NITMOD_ConfiguredWarMode(void) { return testWar; }
int G_NITMOD_LegacyCvarInteger(const char *name,int fallback) {
    assert(!strcmp(name,"g_noCharge")); return testNoCharge;
}
void trap_SendServerCommand(int client,const char *command) {
    assert(client==0 || client==1);
    if(!strncmp(command,"npcc ",5)) {
        char expected[32];
        sprintf(expected,"npcc %i",testNoCharge!=0 || testWar==1 || testWar==3);
        assert(!strcmp(command,expected)); ++sent[client];
    } else { assert(!strncmp(command,"ct ",3)); ++chargeMessages[client]; }
}
int main(void) {
    int caps,target,count=0;
    nitmodClientCapabilities[1]=NITMOD_FEATURE_CHARGE_TIMES;
    for(caps=0;caps<4;++caps) for(testWar=-1;testWar<=5;++testWar)
    for(testNoCharge=0;testNoCharge<=1;++testNoCharge) for(target=-1;target<=0;++target) {
        memset(sent,0,sizeof(sent)); memset(chargeMessages,0,sizeof(chargeMessages));
        nitmodClientCapabilities[0]=((caps&1) ? NITMOD_FEATURE_PACK_CHARGE : 0) |
            ((caps&2) ? NITMOD_FEATURE_CHARGE_TIMES : 0);
        nitmod_SendChargeTimes(target);
        assert(sent[0]==!!(caps&1) && sent[1]==0);
        assert(chargeMessages[0]==!!(caps&2) && chargeMessages[1]==(target==-1));
        ++count;
    }
    printf("Pack settings sender: %d capability/war/bypass/target cases passed\n",count);
    return 0;
}
