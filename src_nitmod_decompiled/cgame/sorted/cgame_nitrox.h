#ifndef CGAME_NITROX_H
#define CGAME_NITROX_H

/* Nitrox extensions, integrity and crash reporting */

#include "nitmod_types.h"
#include "nitmod_globals.h"

uint32_t Nit_RemoveWordInString(char *param_1,char *param_2);
uint32_t nitrox_GetTokenForString(char *param_1);
bool nitrox_CreateDirectory(uint32_t param_1);
void nitrox_MinimizeET_f(void);
void nitmod_PrintCGS(void);
void nitrox_GlobalStatsCmd_f(void);
uint32_t nitrox_ClassNumForLetter(char *param_1);
void nitrox_DrawPopup(void);
uint32_t nitrox_DrawGlobalStats(void);
void nitrox_LoadPanel_LoadingBar(void);
void nitrox_ConfigStringModified(void);
void nitrox_ProcessNewCS(uint param_1);
bool nitrox_NextKey(uint32_t *param_1,char *param_2);
void nitrox_ClampFloat(float *param_1,float param_2,float param_3);
void nitrox_ClampInt(int *param_1,float param_2,float param_3);
void nitrox_stripLeadingSpaces(char *param_1);
void Nit_TDMScore_C(void);
long double Nit_TDMScore_R(float param_1,int param_2);
void Nit_SpecMines(int param_1,int param_2);
void Nit_LiveStats(void);
void nitmod_ObjectiveEvent(void);
void Nit_TDMInfo(void);
int nitmod_DMTeamScoreboard(int param_1,int param_2,float param_3,uint param_4);
void nitmod_GetSimpleCS(void);
void nitmod_ClientCheck(void);
void nitmod_AddKillPrint(void);
void nitmod_DrawKillPrint(void);
void nitmod_AddSpreePrint(void);
void nitmod_SpreePrint(void);
void nitmod_GetMapEndStats(void);
void nitrox_DrawSpecialPrint(void);
void nitmod_ParseNCS(void);
void nitrox_ParseChargeTimes(void);
int nitrox_ConfigString(uint param_1);
void nitmod_DrawObjectiveHint(int param_1);
void nitmod_DrawArtilleryHint(void);
void nitmod_CheckArtilleryHint(int param_1);
void MD5Print(byte *param_1);
void MD5toStr(byte *param_1,char *param_2);
void nitrox_OpenCrashLog(void);
void nitrox_CloseCrashLog(void);
void Crash_Printf(char *param_1);
void installcrashhandler(void);
void restorecrashhandler(void);
void installinthandler(void);
void EnableStackTrace(void);
void DisableStackTrace(void);
bool checkGuid(char *param_1);
void nitrox_GenerateNKeyFile(void);
uint32_t nitrox_ReadNKey(void);
uint8_t * G_SHA1(char *param_1);
void SHA1Reset(uint32_t *param_1);
void SHA1ProcessMessageBlock(uint *param_1);
int SHA1Input(int param_1,uint8_t *param_2,int param_3);
uint64_t SHA1Result(int param_1);
void SHA1PadMessage(int param_1);
uint32_t nitrox_TCPResolve(void);
uint32_t nitrox_TCPOpen(void);
void nitrox_TCPSendHB(void);
uint32_t nitrox_TCPConnect(void);
void nitrox_TCPSend(uint32_t param_1);
void nitrox_TCPClose(void);
void nitrox_SendScreenshot(void);
void nitrox_ScreenshotFile(uint param_1);
uint32_t nitrox_ScreenshotFileExists(char *param_1);
uint32_t nitrox_Screenshot(void);
void nitrox_ScreenshotMD5(uint32_t param_1);
void nitrox_InitFileTransfer(void);
uint32_t nitrox_OpenScreenshotFile(void);
void nitrox_CacheScreenshot(void);
void nitrox_PrepareScreenshot(void);
void nitrox_FreeScreenshot(void);
void nitrox_ScreenshotThink(void);
void MD5Transform(int *param_1,int param_2);
void MD5Init(uint32_t *param_1);
void MD5Update(int param_1,uint32_t *param_2,uint param_3);
void MD5Final(uint8_t *param_1,uint32_t *param_2);

#endif

