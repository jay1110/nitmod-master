#include "cg_local.h"
#include "cg_nitmod_config.h"
#include <assert.h>
#include <stdio.h>
cg_t cg;
cgs_t cgs;
static int loads, plays, missing, enabled, argcValue=2;
static int expectedEntity, expectedChannel, samples[4];
static const char *argument="4";
static const char *paths[]={"sound/hitsounds/head.wav","sound/nit/hs.wav",
    "sound/hitsounds/body.wav","sound/hitsounds/team.wav"};
sfxHandle_t trap_S_RegisterSound(const char *path,qboolean compressed) {
    int slot=loads++%4;
    assert(!compressed && !strcmp(path,paths[slot]));
    return (missing&(1<<slot)) ? 0 : slot+71;
}
void trap_Cvar_Update(vmCvar_t *cvar) { assert(cvar==&nitmodHitSounds); cvar->integer=enabled; }
void trap_S_StartSound(vec3_t origin,int entity,int channel,sfxHandle_t sound) {
    assert(!origin && entity==expectedEntity && channel==expectedChannel);
    assert(plays<4); samples[plays++]=sound;
}
int trap_Argc(void) { return argcValue; }
const char *CG_Argv(int n) { assert(n==1); return argument; }
void CG_Printf(const char *format,...) {}
void Com_Error(int code,const char *format,...) { abort(); }
void CG_NitmodObituaryReset(void) {}
void CG_NitmodHudReset(void) {}
void CG_NitmodGlobalStatsReset(void) {}
int main(void) {
    static snapshot_t snapshot;
    static const char *invalid[]={"", "-1", "3x", "4294967296", " 4", "4 "};
    int type,channel,cycle,i,count=0;
    char number[16];
    cg.snap=&snapshot; snapshot.ps.clientNum=5; expectedEntity=5;
    enabled=1; expectedChannel=CHAN_VOICE;
    NITMOD_HitSoundEvent(4); assert(!loads && !plays);
    for(missing=0;missing<16;++missing) {
        NITMOD_RegisterHitSounds();
        for(enabled=0;enabled<2;++enabled)
        for(type=0;type<7;++type)
        for(channel=0;channel<2;++channel) {
            int sample=type==3 ? 74 : 72;
            int expected=enabled && (type==3 || type==4) && !(missing&(type==3 ? 8 : 2));
            int savedLoads=loads;
            expectedChannel=channel ? CHAN_VOICE : CHAN_AUTO;
            sprintf(number,"%d",type); argument=number;
            for(cycle=0;cycle<2;++cycle) {
                plays=0;
                if(channel) NITMOD_HitSoundEvent(type); else NITMOD_HitSoundCommand();
                assert(plays==expected && loads==savedLoads);
                if(expected) assert(samples[0]==sample);
                ++count;
            }
        }
    }
    missing=0; enabled=1; NITMOD_RegisterHitSounds();
    for(i=0;i<sizeof(invalid)/sizeof(invalid[0]);++i) {
        argument=invalid[i]; plays=0; NITMOD_HitSoundCommand(); assert(!plays);
    }
    argument="4";
    for(argcValue=0;argcValue<4;++argcValue) if(argcValue!=2) {
        plays=0; NITMOD_HitSoundCommand(); assert(!plays);
    }
    argcValue=2;
    cg.snap=NULL; plays=0; NITMOD_HitSoundEvent(4); assert(!plays);
    cg.snap=&snapshot;
    snapshot.ps.clientNum=-1; NITMOD_HitSoundEvent(4); assert(!plays);
    snapshot.ps.clientNum=MAX_CLIENTS; NITMOD_HitSoundEvent(4); assert(!plays);
    snapshot.ps.clientNum=5;
    NITMOD_ClearConfigStrings();
    NITMOD_HitSoundEvent(4); assert(!plays);
    NITMOD_RegisterHitSounds(); expectedChannel=CHAN_VOICE;
    NITMOD_HitSoundEvent(4); assert(plays==1 && samples[0]==72);
    printf("Hit lifecycle: %d media/preference/type/channel/repeat cases plus parser/reset bounds passed\n",count);
    return 0;
}
