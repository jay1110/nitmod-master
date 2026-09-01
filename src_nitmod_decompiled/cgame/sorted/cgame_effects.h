#ifndef CGAME_EFFECTS_H
#define CGAME_EFFECTS_H

/* Missiles, impacts and visual effects */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void CG_Bleed(float *param_1,int param_2);
void CG_GibPlayer(uint32_t *param_1,float *param_2,float *param_3);
void CG_Missile(int param_1);
void CG_FlameLerpVec(float *param_1,float *param_2,float param_3,float *param_4);
void CG_FlameAdjustSpeed(int param_1,float param_2);
int CG_FlameCalcOrg(int param_1,int param_2,float *param_3);
void CG_FlameDamage(void);
void CG_RailTrail_part_5(uint32_t param_1,float *param_2,float *param_3,uint32_t param_4);
void CG_MissileHitWall(int param_1,int param_2,float *param_3,float *param_4,uint param_5);
void CG_MissileHitWallSmall(uint32_t param_1,uint32_t param_2,float *param_3,float *param_4);

#endif

