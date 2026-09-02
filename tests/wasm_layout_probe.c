/* Compile separately against each tree's own headers; never mix definitions. */
#include "q_shared.h"
#include "cg_public.h"
#include <stddef.h>
#include <stdio.h>
#define SIZE(t) printf("%s.size=%lu\n", #t, (unsigned long)sizeof(t))
#define FIELD(t, f) printf("%s.%s=%lu,%lu\n", #t, #f, (unsigned long)offsetof(t, f), (unsigned long)sizeof(((t *)0)->f))
int main(void) {
    SIZE(void *);
    SIZE(usercmd_t);
    FIELD(usercmd_t, serverTime); FIELD(usercmd_t, buttons);
    FIELD(usercmd_t, wbuttons); FIELD(usercmd_t, weapon);
    FIELD(usercmd_t, flags); FIELD(usercmd_t, angles);
    FIELD(usercmd_t, forwardmove); FIELD(usercmd_t, rightmove);
    FIELD(usercmd_t, upmove); FIELD(usercmd_t, doubleTap);
    FIELD(usercmd_t, identClient);
    SIZE(playerState_t);
    FIELD(playerState_t, commandTime); FIELD(playerState_t, pm_type);
    FIELD(playerState_t, eFlags);
    FIELD(playerState_t, origin); FIELD(playerState_t, velocity);
    FIELD(playerState_t, viewangles);
    FIELD(playerState_t, viewheight);
    FIELD(playerState_t, weaponTime); FIELD(playerState_t, weapon);
    FIELD(playerState_t, stats); FIELD(playerState_t, persistant);
    FIELD(playerState_t, ammo); FIELD(playerState_t, ammoclip);
    FIELD(playerState_t, ping);
    SIZE(entityState_t);
    FIELD(entityState_t, number); FIELD(entityState_t, eType);
    FIELD(entityState_t, eFlags); FIELD(entityState_t, pos);
    FIELD(entityState_t, apos); FIELD(entityState_t, weapon);
    FIELD(entityState_t, density); FIELD(entityState_t, dmgFlags);
    FIELD(entityState_t, onFireStart); FIELD(entityState_t, onFireEnd);
    FIELD(entityState_t, nextWeapon); FIELD(entityState_t, teamNum);
    SIZE(snapshot_t);
    FIELD(snapshot_t, snapFlags); FIELD(snapshot_t, ping);
    FIELD(snapshot_t, serverTime); FIELD(snapshot_t, areamask);
    FIELD(snapshot_t, ps); FIELD(snapshot_t, numEntities);
    FIELD(snapshot_t, entities); FIELD(snapshot_t, numServerCommands);
    FIELD(snapshot_t, serverCommandSequence);
    printf("MAX_ENTITIES_IN_SNAPSHOT=%d\nCMD_BACKUP=%d\n", MAX_ENTITIES_IN_SNAPSHOT, CMD_BACKUP);
    SIZE(gameState_t);
    FIELD(gameState_t, stringOffsets); FIELD(gameState_t, stringData);
    FIELD(gameState_t, dataCount);
    SIZE(vmCvar_t);
    FIELD(vmCvar_t, handle); FIELD(vmCvar_t, modificationCount);
    FIELD(vmCvar_t, value); FIELD(vmCvar_t, integer); FIELD(vmCvar_t, string);
    return 0;
}
