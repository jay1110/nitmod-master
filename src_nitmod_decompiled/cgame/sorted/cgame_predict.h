#ifndef CGAME_PREDICT_H
#define CGAME_PREDICT_H

/* Client-side prediction and collision */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void CG_InterpolateEntityPosition_part_3(int param_1);
void CG_PredictLean(int param_1,int param_2,int param_3,int param_4);
void CG_TransitionPlayerState(uint32_t *param_1,uint32_t *param_2);
uint CG_PointContents(uint32_t param_1,int param_2);
void CG_InterpolatePlayerState(int param_1);
void CG_BuildSolidList(void);
uint32_t CG_PredictionOk(int param_1,int param_2);
void CG_PredictPlayerState(void);
void CG_TransitionEntity(int param_1);
void CG_Tracer(float *param_1,float *param_2,int param_3);

#endif

