#ifndef ET_UI_UI_SHARED_H
#define ET_UI_UI_SHARED_H

/**
 * @file ui_ui_shared.h
 * @brief ui_shared
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 * Original decompilation: Ghidra
 */

#include "ui_types.h"
#include "ui_globals.h"

bool BG_AddMagicAmmo(int param_1,int param_2,int param_3,int param_4);
void BG_AddPathCorner(uint32_t param_1,uint32_t *param_2);
void BG_AddPredictableEventToPlayerstate(uint32_t param_1,uint32_t param_2,int param_3);
void BG_AddSplineControl(int param_1,uint32_t param_2);
uint8_t * BG_AddSplinePath(uint32_t param_1,char *param_2,uint32_t *param_3);
uint BG_AkimboFireSequence(int param_1,int param_2,int param_3);
uint32_t BG_AkimboSidearm(int param_1);
bool BG_BBoxCollision(float *param_1,float *param_2,float *param_3,float *param_4);
void BG_BuildSplinePaths(void);
void BG_CalculateSpline_r(int param_1,float *param_2,uint32_t *param_3,float param_4);
uint BG_CanItemBeGrabbed(int param_1,int param_2,uint32_t param_3);
bool BG_CheckCharge(int *param_1);
void BG_ClipVelocity(float *param_1,float *param_2,float *param_3,float param_4);
void BG_ComputeSegments(int param_1);
void BG_CreateRotationMatrix(uint32_t param_1,int param_2);
uint BG_DuplicateWeapon(uint param_1);
void BG_EvaluateTrajectory(uint32_t *param_1,int param_2,float *param_3,int param_4,int param_5);
void BG_EvaluateTrajectoryDelta(uint32_t *param_1,int param_2,float *param_3);
int BG_FindAmmoForWeapon(int param_1);
int BG_FindClipForWeapon(int param_1);
int * BG_FindItem(uint32_t param_1);
int * BG_FindItemForClassName(uint32_t param_1);
int * BG_FindItemForWeapon(int param_1);
uint8_t * BG_Find_PathCorner(uint32_t param_1);
uint8_t * BG_Find_Spline(uint32_t param_1);
uint32_t BG_FootstepForSurface(uint param_1);
void BG_GetFromTable(int param_1);
uint8_t * BG_GetLocationString(float *param_1);
void BG_GetMarkDir(float *param_1,int param_2,float *param_3);
byte BG_GetPrimaryWeaponForPlayerState(int param_1);
uint8_t * BG_GetSplineData(int param_1,uint *param_2);
char BG_GrenadeTypeForTeam(int param_1);
int BG_GrenadesForClass(int param_1,int param_2);
void BG_InitLocations(float *param_1,float *param_2);
bool BG_IsAkimboSideArm(int param_1,int param_2);
bool BG_IsAkimboWeapon(int param_1);
bool BG_IsScopedWeapon(int param_1);
void BG_LinearPathOrigin2(float param_1,int *param_2,float *param_3,float *param_4);
uint32_t BG_LoadCampaignSave(uint32_t param_1,int *param_2,char *param_3);
int BG_MaxAmmoForWeapon(int param_1,int param_2);
void BG_PlayerStateToEntityState(int param_1,uint32_t *param_2,uint32_t param_3,int param_4);
bool BG_PlayerTouchesItem(int param_1,int param_2,int param_3);
uint32_t BG_RaySphereIntersection(float param_1,float *param_2,float *param_3,float *param_4,float *param_5);
void BG_RotatePoint(float *param_1,float *param_2);
long double BG_SplineLength(uint32_t param_1);
uint32_t BG_StoreCampaignSave(uint32_t param_1,uint32_t *param_2,char *param_3);
void BG_TransposeMatrix(uint32_t *param_1,uint32_t *param_2);
uint32_t BG_TraverseSpline(float *param_1,int *param_2);
int * BG_ValidStatWeapon(uint param_1);
int BG_WeaponForMOD(int param_1);
uint32_t BG_WeaponInWolfMP(uint32_t param_1);
int BG_cleanName(char *param_1,char *param_2,int param_3,int param_4);
bool BG_isLightWeaponSupportingFastReload(uint param_1);
void BG_setCrosshair(char *param_1,float *param_2,float param_3,uint32_t param_4);
byte BG_simpleWeaponState(int param_1);

#endif /* ET_UI_UI_SHARED_H */
