#ifndef NITMOD_COMBAT_H
#define NITMOD_COMBAT_H

/* Damage, death, kill logging */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void G_LogDeath(int param_1,uint32_t param_2);
void G_LogKill(int param_1,uint32_t param_2);
void G_KillEnts(uint32_t param_1,int param_2,int param_3,uint32_t param_4);
void G_KillBox(int param_1);

#endif

