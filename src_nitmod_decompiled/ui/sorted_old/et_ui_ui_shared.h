#ifndef ET_UI_UI_SHARED_H
#define ET_UI_UI_SHARED_H

/* Common utilities, string helpers
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"

uint32_t BG_LoadCampaignSave(uint32_t param_1,int *param_2,char *param_3) {;
uint32_t BG_StoreCampaignSave(uint32_t param_1,uint32_t *param_2,char *param_3) {;
int BG_FindClipForWeapon(int param_1) {;
int BG_FindAmmoForWeapon(int param_1) {;
uint32_t BG_WeaponInWolfMP(uint32_t param_1) {;
int BG_GrenadesForClass(int param_1,int param_2) {;
void BG_CalculateSpline_r(int param_1,float *param_2,uint32_t *param_3,float param_4) {;
uint32_t BG_TraverseSpline(float *param_1,int *param_2) {;
BG_RaySphereIntersection(float param_1,float *param_2,float *param_3,float *param_4,float *param_5) {;
void BG_LinearPathOrigin2(float param_1,int *param_2,float *param_3,float *param_4) {;
void BG_ComputeSegments(int param_1) {;
void BG_EvaluateTrajectory(uint32_t *param_1,int param_2,float *param_3,int param_4,int param_5) {;
void BG_EvaluateTrajectoryDelta(uint32_t *param_1,int param_2,float *param_3) {;
void BG_GetMarkDir(float *param_1,int param_2,float *param_3) {;
byte BG_GetPrimaryWeaponForPlayerState(int param_1) {;
void BG_PlayerStateToEntityState(int param_1,uint32_t *param_2,uint32_t param_3,int param_4) {;
uint BG_DuplicateWeapon(uint param_1) {;
int * BG_ValidStatWeapon(uint param_1) {;
int BG_WeaponForMOD(int param_1) {;
uint8_t * BG_Find_PathCorner(uint32_t param_1) {;
void BG_AddPathCorner(uint32_t param_1,uint32_t *param_2) {;
uint8_t * BG_Find_Spline(uint32_t param_1) {;
uint8_t * BG_AddSplinePath(uint32_t param_1,char *param_2,uint32_t *param_3) {;
void BG_AddSplineControl(int param_1,uint32_t param_2) {;
long double BG_SplineLength(uint32_t param_1) {;
void BG_BuildSplinePaths(void) {;
uint8_t * BG_GetSplineData(int param_1,uint *param_2) {;
int BG_MaxAmmoForWeapon(int param_1,int param_2) {;
bool BG_AddMagicAmmo(int param_1,int param_2,int param_3,int param_4) {;
void BG_CreateRotationMatrix(uint32_t param_1,int param_2) {;
void BG_TransposeMatrix(uint32_t *param_1,uint32_t *param_2) {;
void BG_RotatePoint(float *param_1,float *param_2) {;
byte BG_simpleWeaponState(int param_1) {;
int BG_cleanName(char *param_1,char *param_2,int param_3,int param_4) {;
void BG_setCrosshair(char *param_1,float *param_2,float param_3,uint32_t param_4) {;
void BG_ClipVelocity(float *param_1,float *param_2,float *param_3,float param_4) {;
uint32_t BG_FootstepForSurface(uint param_1) {;
bool BG_CheckCharge(int *param_1) {;
int Q_log2(int param_1) {;
char * Q_strrchr(char *param_1,char param_2) {;
void Q_strncpyz(char *param_1,char *param_2,int param_3) {;
int Q_stricmpn(char *param_1,char *param_2,int param_3) {;
int Q_strncmp(char *param_1,char *param_2,int param_3) {;
int Q_stricmp(char *param_1,char *param_2) {;
char * Q_strlwr(char *param_1) {;
char * Q_strupr(char *param_1) {;
void Q_strcat(char *param_1,uint param_2,char *param_3) {;
int Q_PrintStrlen(char *param_1) {;
void Q_CleanStr(char *param_1) {;
uint32_t Q_isBadDirChar(char param_1) {;
char * Q_CleanDirName(char *param_1) {;
uint8_t * Q_StrReplace(uint *param_1,char *param_2,char *param_3) {;

#endif /* ET_UI_UI_SHARED_H */
