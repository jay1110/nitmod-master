#ifndef CGAME_FIRETEAMS_H
#define CGAME_FIRETEAMS_H

/* Fireteam UI and state */

#include "nitmod_types.h"
#include "nitmod_globals.h"

uint32_t CG_FireteamHasClass(int param_1,int param_2);
void CG_Fireteams_MenuTitleText_Draw(int param_1);
void CG_Fireteams_MenuText_Draw(int param_1);
void CG_Fireteams_Setup(void);
void CG_Fireteams_KeyHandling(uint param_1,int param_2);
void CG_Fireteams_Draw(void);
uint32_t CG_FireteamCheckExecKey(uint param_1,int param_2);

#endif

