#ifndef NITMOD_MDX_H
#define NITMOD_MDX_H

/* MDX hit detection / antilag helpers */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void etpro_FinalizeTracemapClamp(int *param_1,int *param_2);
mdx_SwingAngles(float *param_1,int *param_2,float param_3,float param_4,float param_5,float param_6);
void Init_Hit_ETKill(void);
void mdx_cleanup(void);
void mdx_gentity_to_grefEntity(int param_1,uint32_t *param_2,int param_3);
void mdx_calculate_bones_single(int param_1,int param_2);
void mdx_PlayerAngles(int param_1,float *param_2,float *param_3,float *param_4,int param_5);
void mdx_PlayerAnimation(uint32_t *param_1);
void mdx_head_position(uint32_t param_1,int *param_2,float *param_3);
void mdx_legs_position(uint32_t param_1,int *param_2,float *param_3);
void etseb_AddDebugAxis(uint32_t *param_1,uint32_t *param_2);
void etseb_AddDebugBox(uint32_t *param_1,uint32_t *param_2,float *param_3,uint32_t param_4);
void etpro_AddDebugLine(uint32_t *param_1,uint32_t *param_2,int param_3);
void etpro_AddUsercmd(int param_1,int param_2);
void etpro_PlayerInfo(void);
uint32_t etpro_ScriptAction_SetValues(int param_1,uint32_t param_2);
uint32_t etpro_ScriptAction_DeleteEntity(int param_1,uint32_t param_2);

#endif

