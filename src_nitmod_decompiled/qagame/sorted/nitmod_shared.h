#ifndef NITMOD_SHARED_H
#define NITMOD_SHARED_H

/* Q_ / COM_ / Info_ string helpers */

#include "nitmod_types.h"
#include "nitmod_globals.h"

long double Com_GetFlamethrowerRange(void);
void Q_SayConcatArgs(int param_1);
void Q_AddCR(char *param_1);
int Q_SayArgc(void);
uint32_t Q_SayArgv(int param_1,char *param_2,int param_3);
void Com_Error(uint32_t param_1,char *param_2);
void Com_Printf(char *param_1);
void Q_rand(int *param_1);
uint Q_random(uint *param_1);
long double Q_crandom(uint *param_1);
int Q_rsqrt(int param_1);
uint Q_fabs(uint param_1);
int Q_log2(int param_1);
uint64_t COM_ParseExt_constprop_2(int *param_1);
void Info_RemoveKey_Big_part_1(char *param_1,char *param_2);
void Info_RemoveKey_part_0(char *param_1,char *param_2);
void Com_Clamp(void);
void COM_FixPath(char *param_1);
char * COM_SkipPath(char *param_1);
void COM_StripExtension(char *param_1,char *param_2);
void COM_StripFilename(char *param_1,char *param_2);
uint COM_BitCheck(int param_1,uint param_2);
void COM_BitSet(int param_1,uint param_2);
void COM_BitClear(int param_1,uint param_2);
void COM_BackupParseSession(uint32_t *param_1);
void COM_RestoreParseSession(uint32_t *param_1);
uint32_t COM_GetCurrentParseLine(void);
void COM_Parse(void);
void COM_ParseError(char *param_1);
int COM_Compress(char *param_1);
uint8_t * COM_ParseExt(int *param_1,int param_2);
void COM_MatchToken(uint32_t param_1,char *param_2);
bool Q_isprint(int param_1);
bool Q_islower(int param_1);
bool Q_isupper(int param_1);
bool Q_isalpha(uint param_1);
bool Q_isnumeric(int param_1);
bool Q_isalphanumeric(uint param_1);
bool Q_isforfilename(uint param_1);
char * Q_strrchr(char *param_1,char param_2);
void Q_strncpyz(char *param_1,char *param_2,int param_3);
int Q_stricmpn(char *param_1,char *param_2,int param_3);
int Q_strncmp(char *param_1,char *param_2,int param_3);
int Q_stricmp(char *param_1,char *param_2);
char * Q_strlwr(char *param_1);
char * Q_strupr(char *param_1);
void Q_strcat(char *param_1,uint param_2,char *param_3);
int Q_PrintStrlen(char *param_1);
void Q_CleanStr(char *param_1);
uint32_t Q_isBadDirChar(char param_1);
char * Q_CleanDirName(char *param_1);
void Com_sprintf(char *param_1,size_t param_2,char *param_3);
void COM_BeginParseSession(uint32_t param_1);
char * Info_ValueForKey(char *param_1,char *param_2);
uint32_t Info_NextPair(uint32_t *param_1,char *param_2,char *param_3);
void Info_RemoveKey(char *param_1,char *param_2);
void Info_RemoveKey_Big(char *param_1,char *param_2);
bool Info_Validate(char *param_1);
void Info_SetValueForKey(char *param_1,char *param_2,char *param_3);
void Info_SetValueForKey_Big(char *param_1,char *param_2,char *param_3);
uint8_t * Q_StrReplace(uint *param_1,char *param_2,char *param_3);
uint64_t COM_ParseExt_nico(uint32_t *param_1,int param_2);

#endif

