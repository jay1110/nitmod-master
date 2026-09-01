#ifndef NITMOD_ANTICHEAT_H
#define NITMOD_ANTICHEAT_H

/* NxAC anti-cheat */

#include "nitmod_types.h"
#include "nitmod_globals.h"

uint32_t NxAC_ViolationStringForIndex(int param_1);
uint32_t NxAC_FlagToIndex(uint param_1,uint param_2);
void NxAC_BanClient(int param_1);
void NxAC_CheckClient(int param_1);
void NxAC_Log(int param_1,int param_2,int param_3,char *param_4);
void NxAC_CvarScanViolation(int param_1,int param_2,int param_3,uint32_t param_4);
void NxAC_ReportToAdminchat(uint8_t *param_1,uint32_t param_2);
int NxAC_LoadChecksums(void);
void NxAC_ClearChecksumList(void);
uint32_t NxAC_VerifyChecksum(char *param_1);
int NxAC_LoadCvarList(void);
void NxAC_ClearCvarList(void);
void NxAC_ScanClientCvars(int param_1,int param_2);
void NxAC_Init(void);
bool NxAC_ClientActiveFileTransfer(int param_1);
void NxAC_ClearClientFileHandle(int param_1);
uint NxAC_UpdateClientFileHandleBuffer(int param_1,uint32_t *param_2,uint param_3);

#endif

