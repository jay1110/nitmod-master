#ifndef ET_UI_UI_MISC_H
#define ET_UI_UI_MISC_H

/* Other functions
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"

void UI_StartServerRefresh(void) {;
void ConcatArgs(int param_1) {;
int ClampShort(int param_1) {;
int DirToByte(float *param_1) {;
void ByteToDir(uint param_1,uint32_t *param_2) {;
uint32_t PlaneFromPoints(float *param_1,float *param_2,float *param_3,float *param_4) {;
void vectoangles(float *param_1,float *param_2) {;
void AnglesToAxis(float *param_1,float *param_2) {;
void AxisClear(uint32_t *param_1) {;
void AxisCopy(uint32_t *param_1,uint32_t *param_2) {;
void ProjectPointOnPlane(float *param_1,float *param_2,float *param_3) {;
void MakeNormalVectors(float *param_1,float *param_2,float *param_3) {;
long double LerpAngle(float param_1,float param_2,float param_3) {;
void LerpPosition(float *param_1,float *param_2,float param_3,float *param_4) {;
void AnglesSubtract(float *param_1,float *param_2,float *param_3) {;
void SetPlaneSignbits(float *param_1) {;
long double RadiusFromBounds(float *param_1,float *param_2) {;
void AddPointToBounds(float *param_1,float *param_2,float *param_3) {;
void VectorNormalize(float *param_1) {;
void VectorNormalizeFast(float *param_1) {;
long double VectorNormalize2(float *param_1,float *param_2) {;
long double VectorLength(float *param_1) {;
long double Distance(float *param_1,float *param_2) {;
void MatrixMultiply(float *param_1,float *param_2,float *param_3) {;
void AngleVectors(float *param_1,float *param_2,float *param_3,float *param_4) {;
void PerpendicularVector(float *param_1,float *param_2) {;
void RotatePointAroundVector(float *param_1,float *param_2,float *param_3,float param_4) {;
void GetPerpendicularViewVector(float *param_1,float *param_2,float *param_3,float *param_4) {;
void ProjectPointOntoVector(float *param_1,float *param_2,float *param_3,float *param_4) {;
void ProjectPointOntoVectorBounded(float *param_1,float *param_2,float *param_3,float *param_4) {;
long double DistanceFromLineSquared(float *param_1,float *param_2,float *param_3) {;
long double DistanceFromVectorSquared(float *param_1,float *param_2,float *param_3) {;
long double vectoyaw(float *param_1) {;
void AxisToAngles(int param_1,float *param_2) {;
long double VectorDistance(float *param_1,float *param_2) {;
void SkipBracedSection_Depth(int *param_1,int param_2) {;
void SkipBracedSection(int *param_1) {;
void SkipRestOfLine(uint32_t *param_1) {;
void va(char *param_1) {;
uint32_t encode64(byte *param_1,char *param_2,int param_3) {;
void decode64(int param_1) {;
uint32_t FileExists(uint32_t param_1) {;
void nitrox_ClampFloat(float *param_1,float param_2,float param_3) {;
void nitrox_ClampInt(int *param_1,float param_2,float param_3) {;
uint32_t need_escape(byte *param_1) {;
void nitrox_stripLeadingSpaces(char *param_1) {;
uint32_t UI_ConsoleCommand(int param_1) {;
void UI_AdjustFrom640(float *param_1,float *param_2,float *param_3,float *param_4) {;
void UI_SortArenas(uint32_t *param_1,uint32_t *param_2) {;
void UI_SortCampaigns(int param_1,int param_2) {;
void UI_LoadArenas(void) {;
void UI_Load(void) {;
if ((((tmp_i11 != 0) && (tmp_f3 = (float)(int)tmp_f6, tmp_f6 = param_1[2], tmp_f6 < tmp_f3)) || ((tmp_b7 & 0xdf) == 10)) || (tmp_b7 == 0)) {;
if (((byte)(tmp_b5 - 9) < 2) || ((tmp_b5 & 0xdf) == 0)) {;
void UI_ServersSort(int param_1,int param_2) {;
void WM_setVisibility(uint32_t param_1,int param_2) {;
void UI_Update(uint32_t param_1) {;
void _UI_MouseEvent(int param_1,int param_2) {;
void UI_LoadNonIngame(void) {;
uint vmMain(uint32_t param_1,int param_2,int param_3) {;
void UI_ReadableSize(char *param_1,int param_2,uint param_3) {;
void UI_PrintTime(uint32_t param_1,uint32_t param_2,int param_3) {;
void UI_RegisterCvars(void) {;
void UI_UpdateCvars(void) {;
void UI_Campaign_f(void) {;
void UI_ListCampaigns_f(void) {;
void Scroll_Slider_ThumbFunc(int param_1) {;
void Script_ExecWolfConfig(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Tooltip_ComputePosition(int param_1) {;
uint8_t * UI_Alloc(int param_1) {;
void Script_SetAsset(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_ClearCvar(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_SetPlayerModel(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_SetPlayerHead(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_SetBackground(int param_1,uint32_t param_2,uint32_t param_3) {;
void Script_Exec(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_ExecNOW(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_Play(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_playLooped(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_SetCvar(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_CopyCvar(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_ToggleCvarBit(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_CloseAll(void) {;
void Fade(uint *param_1,float *param_2,float param_3,int *param_4,int param_5,int param_6, float param_7) {;
void Window_Paint(float *param_1,float param_2,float param_3,float param_4) {;
void Script_SetFocus(int param_1,uint32_t param_2,uint32_t param_3) {;
void Script_SetEditFocus(int param_1,uint32_t param_2,uint32_t param_3) {;
void Script_FadeIn(int param_1,uint32_t param_2,uint32_t param_3) {;
void Script_FadeOut(int param_1,uint32_t param_2,uint32_t param_3) {;
void Script_Show(int param_1,uint32_t param_2,uint32_t param_3) {;
void Script_Hide(int param_1,uint32_t param_2,uint32_t param_3) {;
void Script_ConditionalHideShow(int param_1,uint32_t param_2,uint32_t param_3) {;
void Script_Transition(int param_1,uint32_t param_2,uint32_t param_3) {;
if (pfVar3 != (float *)0x0) {;
void Script_Orbit(int param_1,uint32_t param_2,uint32_t param_3) {;
uint32_t Script_CheckProfile(uint32_t param_1) {;
uint32_t Script_WriteProfile(uint32_t param_1) {;
void Script_ConditionalScript(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Controls_GetConfig(void) {;
void Controls_SetConfig(int param_1) {;
void Controls_SetDefaults(int param_1) {;
int BindingIDFromName(uint32_t param_1) {;
uint8_t * BindingFromName(uint32_t param_1) {;
void AdjustFrom640(float *param_1,float *param_2,float *param_3,float *param_4) {;
void Script_Open(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_ConditionalOpen(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Script_Close(uint32_t param_1,uint32_t param_2,uint32_t param_3) {;
void Scroll_ListBox_ThumbFunc(int *param_1) {;
void Scroll_ListBox_AutoFunc(int *param_1) {;

#endif /* ET_UI_UI_MISC_H */
