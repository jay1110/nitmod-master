#ifndef CGAME_UNKNOWN_H
#define CGAME_UNKNOWN_H

/* Unclassified recovered functions */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void unk_func_0001a090(void);
void __x86_get_pc_thunk_bx(void);
void __x86_get_pc_thunk_cx(void);
uint32_t SkillForClass(int param_1);
void ConcatArgs(int param_1);
void etpro_FinalizeTracemapClamp(int *param_1,int *param_2);
uint8_t * in_word_set(byte *param_1,uint param_2);
void __x86_get_pc_thunk_dx(void);
long double lt_random(int param_1,int param_2);
long double lt_crandom(int param_1,int param_2);
void InitSmokeSprites(void);
void CGRefEntityToTag(int param_1,uint32_t *param_2);
void CGTagToRefEntity(int param_1,uint32_t *param_2);
uint32_t SkillNumForClass(uint param_1);
int weaponIconScale(int param_1);
void GetMacAddress(void);
uint32_t ValidBloodPool(float *param_1);
void InitSkillLevelStructure(int param_1);
void dllEntry(uint32_t param_1);
void testPrintInt(uint32_t param_1,uint32_t param_2);
void testPrintFloat(uint32_t param_1,uint32_t param_2);
bool isET260(void);
void AddLean(uint32_t param_1,float *param_2,float param_3);
bool is_sidearm_smg(void);
void ToWindowCoords(float *param_1,float *param_2,float *param_3);
uint32_t ParseColorRange(int param_1,uint32_t param_2,int param_3);
char pingColor(int param_1);
void CheckETLegacy(void);
uint8_t * G_GetDateAndTimeFileName(void);
uint32_t INTHandler(void);
void linux_siginfo(int param_1,int param_2);
void linux_backtrace(int param_1);
void CrashHandler(int param_1,int param_2,uint32_t param_3);

#endif

