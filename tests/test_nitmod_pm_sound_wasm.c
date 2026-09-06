#include "cg_local.h"
#include "cg_nitmod_config.h"
#include <assert.h>
#include <stdio.h>
cg_t cg;
static int loads, plays, enabled = 1, handle = 73;
sfxHandle_t trap_S_RegisterSound(const char *name, qboolean compressed) {
    assert(!strcmp(name, "sound/nit/pm.wav") && !compressed);
    ++loads; return handle;
}
void trap_Cvar_Update(vmCvar_t *cvar) { cvar->integer = enabled; }
void trap_S_StartSoundVControl(vec3_t origin, int entity, int channel, sfxHandle_t sound, int volume) {
    assert(!origin && entity == 5 && channel == CHAN_VOICE && sound == 73 && volume == 255);
    ++plays;
}
int main(void) {
    cg.clientNum = 5;
    NITMOD_PrivateMessageSound(5);
    assert(!loads && !plays);
    NITMOD_RegisterPrivateMessageSound();
    assert(loads == 1 && !plays);
    NITMOD_PrivateMessageSound(4);
    NITMOD_PrivateMessageSound(-1);
    enabled = 0; NITMOD_PrivateMessageSound(5);
    assert(!plays);
    enabled = 1;
    NITMOD_PrivateMessageSound(5); NITMOD_PrivateMessageSound(5);
    assert(plays == 2 && loads == 1);
    handle = 0; NITMOD_RegisterPrivateMessageSound();
    NITMOD_PrivateMessageSound(5);
    assert(plays == 2 && loads == 2);
    puts("WASM PM sound: eager registration, cvar/recipient gating and missing asset passed");
    return 0;
}
