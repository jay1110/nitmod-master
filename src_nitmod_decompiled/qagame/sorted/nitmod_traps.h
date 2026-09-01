#ifndef NITMOD_TRAPS_H
#define NITMOD_TRAPS_H

/* Engine trap_* syscalls */

#include "nitmod_types.h"
#include "nitmod_globals.h"

int trap_R_RegisterModel(char *param_1);
uint32_t trap_R_LerpTagNumber(float *param_1,int *param_2,int param_3);
int trap_R_LookupTag(int *param_1,uint32_t param_2);
void trap_R_LerpTag(uint32_t param_1,int *param_2,uint32_t param_3,int param_4);
void trap_Printf(uint32_t param_1);
void trap_Error(uint32_t param_1);
void trap_Milliseconds(void);
void trap_Argc(void);
void trap_Argv(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_FS_FOpenFile(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_FS_Read(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_FS_Write(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_FS_Rename(uint32_t param_1,uint32_t param_2);
void trap_FS_FCloseFile(uint32_t param_1);
void trap_SendConsoleCommand(uint32_t param_1,uint32_t param_2);
void trap_Cvar_Update(uint32_t param_1);
void trap_Cvar_Set(uint32_t param_1,uint32_t param_2);
void trap_Cvar_VariableIntegerValue(uint32_t param_1);
void trap_Cvar_VariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_Cvar_LatchedVariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_DropClient(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_SendServerCommand(int param_1,char *param_2);
void trap_SetConfigstring(uint32_t param_1,uint32_t param_2);
void trap_GetConfigstring(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_GetUserinfo(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_SetUserinfo(uint32_t param_1,uint32_t param_2);
void trap_GetServerinfo(uint32_t param_1,uint32_t param_2);
void trap_SetBrushModel(uint32_t param_1,uint32_t param_2);
void trap_PointContents(uint32_t param_1,uint32_t param_2);
void trap_InPVS(uint32_t param_1,uint32_t param_2);
void trap_AdjustAreaPortalState(uint32_t param_1,uint32_t param_2);
void trap_LinkEntity(uint32_t param_1);
void trap_UnlinkEntity(uint32_t param_1);
void trap_EntitiesInBox(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4);
void trap_EntityContactCapsule(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_BotAllocateClient(uint32_t param_1);
void trap_RegisterSound(uint32_t param_1,uint32_t param_2);
void trap_GetUsercmd(uint32_t param_1,uint32_t param_2);
void trap_GetEntityToken(uint32_t param_1,uint32_t param_2);
void trap_DebugPolygonCreate(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_RealTime(uint32_t param_1);
void trap_SnapVector(uint32_t param_1);
void trap_GetTag(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4);
void trap_LoadTag(uint32_t param_1);
void trap_PC_LoadSource(uint32_t param_1);
void trap_PC_FreeSource(uint32_t param_1);
void trap_PC_ReadToken(uint32_t param_1,uint32_t param_2);
void trap_PC_SourceFileAndLine(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_BotGetServerCommand(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_BotUserCommand(uint32_t param_1,uint32_t param_2);
void trap_EA_Command(uint32_t param_1,uint32_t param_2);
void trap_PbStat(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_SendMessage(uint32_t param_1,uint32_t param_2,uint32_t param_3);

#endif

