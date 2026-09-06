#include "cg_local.h"
#include "cg_nitmod_config.h"
#include <assert.h>
#include <stdio.h>
cg_t cg;
static snapshot_t snapshot;
static int loads, plays, enabled = 1, missing;
static const char *paths[] = {"sound/hitsounds/head.wav", "sound/nit/hs.wav",
    "sound/hitsounds/body.wav", "sound/hitsounds/team.wav"};
sfxHandle_t trap_S_RegisterSound(const char *path, qboolean compressed) {
    int index = loads++ % 4;
    assert(!strcmp(path, paths[index]) && !compressed);
    return missing ? 0 : index + 71;
}
void trap_Cvar_Update(vmCvar_t *cvar) {
    assert(cvar == &nitmodHitSounds); cvar->integer = enabled;
}
void trap_S_StartSound(vec3_t origin, int entity, int channel, sfxHandle_t sound) {
    assert(!origin && entity == 5 && channel == CHAN_VOICE);
    assert(sound == (plays % 2 ? 74 : 72)); ++plays;
}
int main(void) {
    cg.snap = &snapshot; snapshot.ps.clientNum = 5;
    NITMOD_HitSoundEvent(4); assert(!loads && !plays);
    NITMOD_RegisterHitSounds(); assert(loads == 4 && !plays);
    NITMOD_HitSoundEvent(4); NITMOD_HitSoundEvent(3);
    NITMOD_HitSoundEvent(4); NITMOD_HitSoundEvent(3);
    assert(plays == 4 && loads == 4);
    enabled = 0; NITMOD_HitSoundEvent(4); assert(plays == 4);
    enabled = 1; NITMOD_HitSoundEvent(2); assert(plays == 4);
    snapshot.ps.clientNum = -1; NITMOD_HitSoundEvent(4); assert(plays == 4);
    snapshot.ps.clientNum = 5;
    missing = 1; NITMOD_RegisterHitSounds();
    NITMOD_HitSoundEvent(4); NITMOD_HitSoundEvent(3);
    assert(loads == 8 && plays == 4);
    puts("WASM hit media: eager four-sample registration and event gating passed");
    return 0;
}
