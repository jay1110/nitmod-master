#ifndef CGAME_TRAPS_H
#define CGAME_TRAPS_H

/* Engine trap syscalls */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void trap_PumpEventLoop(void);
void trap_Print(uint32_t param_1);
void trap_Error(uint32_t param_1);
void trap_Milliseconds(void);
void trap_Cvar_Register(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4);
void trap_Cvar_Update(uint32_t param_1);
void trap_Cvar_Set(uint32_t param_1,uint32_t param_2);
void trap_Cvar_VariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_Cvar_LatchedVariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_Argc(void);
void trap_Argv(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_Args(uint32_t param_1,uint32_t param_2);
void trap_FS_FOpenFile(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_FS_Read(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_FS_Write(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_FS_FCloseFile(uint32_t param_1);
void trap_FS_Delete(uint32_t param_1);
void trap_SendConsoleCommand(uint32_t param_1);
void trap_AddCommand(uint32_t param_1);
void trap_RemoveCommand(uint32_t param_1);
void trap_SendClientCommand(uint32_t param_1);
void trap_UpdateScreen(void);
void trap_CM_NumInlineModels(void);
void trap_CM_InlineModel(uint32_t param_1);
void trap_CM_TempBoxModel(uint32_t param_1,uint32_t param_2);
void trap_CM_TempCapsuleModel(uint32_t param_1,uint32_t param_2);
void trap_CM_PointContents(uint32_t param_1,uint32_t param_2);
void trap_R_ClearDecals(void);
void trap_S_StartSound(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4);
void trap_S_StartLocalSound(uint32_t param_1,uint32_t param_2);
void trap_S_ClearLoopingSounds(void);
void trap_S_ClearSounds(uint32_t param_1);
void trap_S_StopStreamingSound(uint32_t param_1);
void trap_S_UpdateEntityPosition(uint32_t param_1,uint32_t param_2);
void trap_S_GetVoiceAmplitude(uint32_t param_1);
void trap_S_GetSoundLength(uint32_t param_1);
void trap_S_GetCurrentSoundTime(void);
void trap_S_StartBackgroundTrack(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_S_FadeBackgroundTrack(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_S_FadeAllSound(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_R_GetSkinModel(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_R_GetShaderFromModel(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_R_ClearScene(void);
void trap_R_AddRefEntityToScene(int param_1);
void trap_R_AddPolyToScene(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_R_AddPolyBufferToScene(uint32_t param_1);
void trap_R_RenderScene(uint32_t param_1);
void trap_R_SaveViewParms(void);
void trap_R_RestoreViewParms(void);
void trap_R_SetColor(uint32_t param_1);
void trap_R_Add2dPolys(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_R_ModelBounds(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_R_LerpTag(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4);
void trap_R_RemapShader(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_GetGlconfig(uint32_t param_1);
void trap_GetGameState(uint32_t param_1);
void trap_GetCurrentSnapshotNumber(uint32_t param_1,uint32_t param_2);
void trap_GetSnapshot(uint32_t param_1,uint32_t param_2);
void trap_GetServerCommand(uint32_t param_1);
void trap_GetCurrentCmdNumber(void);
void trap_GetUserCmd(uint32_t param_1,uint32_t param_2);
void trap_SetClientLerpOrigin(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_MemoryRemaining(void);
void trap_loadCamera(uint32_t param_1,uint32_t param_2);
void trap_startCamera(uint32_t param_1,uint32_t param_2);
void trap_stopCamera(uint32_t param_1);
void trap_Key_IsDown(uint32_t param_1);
void trap_Key_GetCatcher(void);
void trap_Key_GetOverstrikeMode(void);
void trap_Key_SetOverstrikeMode(uint32_t param_1);
void trap_Key_KeysForBinding(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_Key_SetCatcher(uint32_t param_1);
void trap_Key_GetKey(uint32_t param_1);
void trap_PC_AddGlobalDefine(uint32_t param_1);
void trap_PC_LoadSource(uint32_t param_1);
void trap_PC_FreeSource(uint32_t param_1);
void trap_PC_ReadToken(uint32_t param_1,uint32_t param_2);
void trap_PC_SourceFileAndLine(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_PC_UnReadToken(uint32_t param_1);
void trap_S_StopBackgroundTrack(void);
void trap_RealTime(uint32_t param_1);
void trap_SnapVector(uint32_t param_1);
void trap_CIN_StopCinematic(uint32_t param_1);
void trap_CIN_RunCinematic(uint32_t param_1);
void trap_CIN_DrawCinematic(uint32_t param_1);
void trap_GetEntityToken(uint32_t param_1,uint32_t param_2);
void trap_UI_Popup(uint32_t param_1);
void trap_Key_GetBindingBuf(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_Key_SetBinding(uint32_t param_1,uint32_t param_2);
void trap_Key_KeynumToStringBuf(uint32_t param_1,uint32_t param_2,uint32_t param_3);
void trap_S_RegisterSound(uint32_t param_1);
void trap_R_RegisterModel(uint32_t param_1);
void trap_R_RegisterSkin(uint32_t param_1);
void trap_R_RegisterShader(uint32_t param_1);
void trap_R_RegisterShaderNoMip(uint32_t param_1);
void trap_R_RegisterFont(uint32_t param_1,uint32_t param_2,int param_3);
void trap_CM_LoadMap(uint32_t param_1);
void trap_R_LoadWorldMap(uint32_t param_1);
void trap_R_inPVS(uint32_t param_1,uint32_t param_2);
void trap_GetHunkData(uint32_t param_1,uint32_t param_2);
void trap_SendMessage(uint32_t param_1,uint32_t param_2);
uint32_t trap_MessageStatus(void);
uint32_t trap_R_LoadDynamicShader(uint32_t param_1,uint32_t param_2);
uint32_t trap_R_GetTextureId(uint32_t param_1);
void trap_R_Finish(void);

#endif

