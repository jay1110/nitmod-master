/* Engine trap syscalls — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_traps.h"

void trap_PumpEventLoop(void)
{
  if (GHIDRA_FIELD(cgs, 33703444, 4) != 0) {
    (*syscall)(0xad);
  }
  return;
}

void trap_Print(uint32_t param_1)
{
  (*syscall)(0,param_1);
  return;
}

void trap_Error(uint32_t param_1)
{
  (*syscall)(1,param_1);
  return;
}

void trap_Milliseconds(void)
{
  (*syscall)(2);
  return;
}

void trap_Cvar_Register(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  (*syscall)(3,param_1,param_2,param_3,param_4);
  return;
}

void trap_Cvar_Update(uint32_t param_1)
{
  (*syscall)(4,param_1);
  return;
}

void trap_Cvar_Set(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(5,param_1,param_2);
  return;
}

void trap_Cvar_VariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(6,param_1,param_2,param_3);
  return;
}

void trap_Cvar_LatchedVariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(7,param_1,param_2,param_3);
  return;
}

void trap_Argc(void)
{
  (*syscall)(8);
  return;
}

void trap_Argv(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(9,param_1,param_2,param_3);
  return;
}

void trap_Args(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(10,param_1,param_2);
  return;
}

void trap_FS_FOpenFile(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0xb,param_1,param_2,param_3);
  return;
}

void trap_FS_Read(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0xc,param_1,param_2,param_3);
  return;
}

void trap_FS_Write(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0xd,param_1,param_2,param_3);
  return;
}

void trap_FS_FCloseFile(uint32_t param_1)
{
  (*syscall)(0xe,param_1);
  return;
}

void trap_FS_GetFileList(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        )

{
  (*syscall)(0xf,param_1,param_2,param_3,param_4);
  return;
}

void trap_FS_Delete(uint32_t param_1)
{
  (*syscall)(0x10,param_1);
  return;
}

void trap_SendConsoleCommand(uint32_t param_1)
{
  (*syscall)(0x11,param_1);
  return;
}

void trap_AddCommand(uint32_t param_1)
{
  (*syscall)(0x12,param_1);
  return;
}

void trap_RemoveCommand(uint32_t param_1)
{
  (*syscall)(0x67,param_1);
  return;
}

void trap_SendClientCommand(uint32_t param_1)
{
  (*syscall)(0x13,param_1);
  return;
}

void trap_UpdateScreen(void)
{
  (*syscall)(0x14);
  return;
}

void trap_CM_NumInlineModels(void)
{
  (*syscall)(0x16);
  return;
}

void trap_CM_InlineModel(uint32_t param_1)
{
  (*syscall)(0x17,param_1);
  return;
}

void trap_CM_TempBoxModel(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x19,param_1,param_2);
  return;
}

void trap_CM_TempCapsuleModel(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x20,param_1,param_2);
  return;
}

void trap_CM_PointContents(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x1a,param_1,param_2);
  return;
}

void trap_CM_TransformedPointContents
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  (*syscall)(0x1b,param_1,param_2,param_3,param_4);
  return;
}

void trap_CM_BoxTrace(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
                     uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x1c,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}

void trap_CM_TransformedBoxTrace
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8,
               uint32_t param_9)

{
  (*syscall)(0x1d,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

void trap_CM_CapsuleTrace
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x1e,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}

void trap_CM_TransformedCapsuleTrace
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8,
               uint32_t param_9)

{
  (*syscall)(0x1f,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

void trap_CM_MarkFragments
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x21,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}

void trap_R_ProjectDecal(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        ,uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x22,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}

void trap_R_ClearDecals(void)
{
  (*syscall)(0x23);
  return;
}

void trap_S_StartSound(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  (*syscall)(0x24,param_1,param_2,param_3,param_4,0x7f);
  return;
}

void trap_S_StartSoundVControl
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5)

{
  (*syscall)(0x24,param_1,param_2,param_3,param_4,param_5);
  return;
}

void trap_S_StartSoundEx(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        ,uint32_t param_5)

{
  (*syscall)(0x25,param_1,param_2,param_3,param_4,param_5,0x7f);
  return;
}

void trap_S_StartSoundExVControl
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6)

{
  (*syscall)(0x25,param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}

void trap_S_StartLocalSound(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x26,param_1,param_2,0x7f);
  return;
}

void trap_S_ClearLoopingSounds(void)
{
  (*syscall)(0x27);
  return;
}

void trap_S_ClearSounds(uint32_t param_1)
{
  (*syscall)(0x28,param_1);
  return;
}

void trap_S_AddLoopingSound
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5)

{
  (*syscall)(0x29,param_1,param_2,0x4e2,param_3,param_4,param_5);
  return;
}

void trap_S_AddRealLoopingSound
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6)

{
  (*syscall)(0x6f,param_1,param_2,param_4,param_3,param_5,param_6);
  return;
}

void trap_S_StopStreamingSound(uint32_t param_1)
{
  (*syscall)(0x70,param_1);
  return;
}

void trap_S_UpdateEntityPosition(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x2a,param_1,param_2);
  return;
}

void trap_S_GetVoiceAmplitude(uint32_t param_1)
{
  (*syscall)(0x2b,param_1);
  return;
}

void trap_S_Respatialize(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        )

{
  (*syscall)(0x2c,param_1,param_2,param_3,param_4);
  return;
}

void trap_S_GetSoundLength(uint32_t param_1)
{
  (*syscall)(0x32,param_1);
  return;
}

void trap_S_GetCurrentSoundTime(void)
{
  (*syscall)(0x33);
  return;
}

void trap_S_StartBackgroundTrack(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x2e,param_1,param_2,param_3);
  return;
}

void trap_S_FadeBackgroundTrack(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x2f,param_1,param_2,param_3);
  return;
}

void trap_S_FadeAllSound(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x30,param_1,param_2,param_3);
  return;
}

void trap_S_StartStreamingSound
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5)

{
  (*syscall)(0x31,param_1,param_2,param_3,param_4,param_5);
  return;
}

void trap_R_GetSkinModel(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x38,param_1,param_2,param_3);
  return;
}

void trap_R_GetShaderFromModel(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x39,param_1,param_2,param_3);
  return;
}

void trap_R_ClearScene(void)
{
  (*syscall)(0x3b);
  return;
}

void trap_R_AddRefEntityToScene(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 4);
  (*syscall)(0x3c,param_1);
  if (GHIDRA_FIELD(cgs, 33823068, 4) == 0) {
    if (((int)GHIDRA_FIELD(cgs, 33823072, 4) < 0x1f5) || (*(int *)(param_1 + 4) == tmp_i1)) {
      GHIDRA_FIELD(cgs, 33823072, 4) = GHIDRA_FIELD(cgs, 33823072, 4) + 1;
      return;
    }
    GHIDRA_FIELD(cgs, 33823112, 4) = GHIDRA_FIELD(cgs, 33823112, 4) | 0x20;
    GHIDRA_FIELD(cgs, 33823068, 4) = 1;
  }
  return;
}

void trap_R_AddPolyToScene(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x3e,param_1,param_2,param_3);
  return;
}

void trap_R_AddPolyBufferToScene(uint32_t param_1)
{
  (*syscall)(0x40,param_1);
  return;
}

void trap_R_AddPolysToScene
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  (*syscall)(0x3f,param_1,param_2,param_3,param_4);
  return;
}

void trap_R_AddLightToScene
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8)

{
  (*syscall)(0x41,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}

void trap_R_AddCoronaToScene
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x42,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}

void trap_R_SetFog(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
                  uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x43,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  return;
}

void trap_R_SetGlobalFog(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        ,uint32_t param_5,uint32_t param_6)

{
  (*syscall)(0x44,param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}

void trap_R_RenderScene(uint32_t param_1)
{
  (*syscall)(0x45,param_1);
  return;
}

void trap_R_SaveViewParms(void)
{
  (*syscall)(0x46);
  return;
}

void trap_R_RestoreViewParms(void)
{
  (*syscall)(0x47);
  return;
}

void trap_R_SetColor(uint32_t param_1)
{
  (*syscall)(0x48,param_1);
  return;
}

void trap_R_DrawStretchPic
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8,
               uint32_t param_9)

{
  (*syscall)(0x49,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

void trap_R_DrawRotatedPic
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8,
               uint32_t param_9,uint32_t param_10)

{
  (*syscall)(0xa4,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10);
  return;
}

void trap_R_DrawStretchPicGradient
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8,
               uint32_t param_9,uint32_t param_10,uint32_t param_11)

{
  (*syscall)(0x4a,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
             param_11);
  return;
}

void trap_R_Add2dPolys(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0xa5,param_1,param_2,param_3);
  return;
}

void trap_R_ModelBounds(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x4b,param_1,param_2,param_3);
  return;
}

void trap_R_LerpTag(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  (*syscall)(0x4c,param_1,param_2,param_3,param_4);
  return;
}

void trap_R_RemapShader(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x6e,param_1,param_2,param_3);
  return;
}

void trap_GetGlconfig(uint32_t param_1)
{
  (*syscall)(0x4d,param_1);
  return;
}

void trap_GetGameState(uint32_t param_1)
{
  (*syscall)(0x4e,param_1);
  return;
}

void trap_GetCurrentSnapshotNumber(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x4f,param_1,param_2);
  return;
}

void trap_GetSnapshot(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x50,param_1,param_2);
  return;
}

void trap_GetServerCommand(uint32_t param_1)
{
  (*syscall)(0x51,param_1);
  return;
}

void trap_GetCurrentCmdNumber(void)
{
  (*syscall)(0x52);
  return;
}

void trap_GetUserCmd(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x53,param_1,param_2);
  return;
}

void trap_SetUserCmdValue
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  (*syscall)(0x54,param_1,param_2,param_3,param_4);
  return;
}

void trap_SetClientLerpOrigin(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x55,param_1,param_2,param_3);
  return;
}

void trap_MemoryRemaining(void)
{
  (*syscall)(0x57);
  return;
}

void trap_loadCamera(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x71,param_1,param_2);
  return;
}

void trap_startCamera(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x72,param_1,param_2);
  return;
}

void trap_stopCamera(uint32_t param_1)
{
  (*syscall)(0x73,param_1);
  return;
}

void trap_getCameraInfo(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
                       uint32_t param_5)

{
  (*syscall)(0x74,param_1,param_2,param_3,param_4,param_5);
  return;
}

void trap_Key_IsDown(uint32_t param_1)
{
  (*syscall)(0x58,param_1);
  return;
}

void trap_Key_GetCatcher(void)
{
  (*syscall)(0x59);
  return;
}

void trap_Key_GetOverstrikeMode(void)
{
  (*syscall)(0x5c);
  return;
}

void trap_Key_SetOverstrikeMode(uint32_t param_1)
{
  (*syscall)(0x5d,param_1);
  return;
}

void trap_Key_KeysForBinding(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0xa9,param_1,param_2,param_3);
  return;
}

void trap_Key_SetCatcher(uint32_t param_1)
{
  (*syscall)(0x5a,param_1);
  return;
}

void trap_Key_GetKey(uint32_t param_1)
{
  (*syscall)(0x5b,param_1);
  return;
}

void trap_PC_AddGlobalDefine(uint32_t param_1)
{
  (*syscall)(0x5e,param_1);
  return;
}

void trap_PC_LoadSource(uint32_t param_1)
{
  (*syscall)(0x5f,param_1);
  return;
}

void trap_PC_FreeSource(uint32_t param_1)
{
  (*syscall)(0x60,param_1);
  return;
}

void trap_PC_ReadToken(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x61,param_1,param_2);
  return;
}

void trap_PC_SourceFileAndLine(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x62,param_1,param_2,param_3);
  return;
}

void trap_PC_UnReadToken(uint32_t param_1)
{
  (*syscall)(99,param_1);
  return;
}

void trap_S_StopBackgroundTrack(void)
{
  (*syscall)(100);
  return;
}

void trap_RealTime(uint32_t param_1)
{
  (*syscall)(0x65,param_1);
  return;
}

void trap_SnapVector(uint32_t param_1)
{
  (*syscall)(0x66,param_1);
  return;
}

void trap_CIN_PlayCinematic
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6)

{
  (*syscall)(0x69,param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}

void trap_CIN_StopCinematic(uint32_t param_1)
{
  (*syscall)(0x6a,param_1);
  return;
}

void trap_CIN_RunCinematic(uint32_t param_1)
{
  (*syscall)(0x6b,param_1);
  return;
}

void trap_CIN_DrawCinematic(uint32_t param_1)
{
  (*syscall)(0x6c,param_1);
  return;
}

void trap_CIN_SetExtents(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        ,uint32_t param_5)

{
  (*syscall)(0x6d,param_1,param_2,param_3,param_4,param_5);
  return;
}

void trap_GetEntityToken(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x3d,param_1,param_2);
  return;
}

void trap_UI_Popup(uint32_t param_1)
{
  (*syscall)(0xa2,param_1);
  return;
}

void trap_Key_GetBindingBuf(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0xa6,param_1,param_2,param_3);
  return;
}

void trap_Key_SetBinding(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0xa7,param_1,param_2);
  return;
}

void trap_Key_KeynumToStringBuf(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0xa8,param_1,param_2,param_3);
  return;
}

void trap_S_RegisterSound(uint32_t param_1)
{
  CG_DrawInformation(1);
  (*syscall)(0x2d,param_1,0);
  return;
}

void trap_R_RegisterModel(uint32_t param_1)
{
  CG_DrawInformation(1);
  (*syscall)(0x35,param_1);
  return;
}

void trap_R_RegisterSkin(uint32_t param_1)
{
  CG_DrawInformation(1);
  (*syscall)(0x36,param_1);
  return;
}

void trap_R_RegisterShader(uint32_t param_1)
{
  CG_DrawInformation(1);
  (*syscall)(0x37,param_1);
  return;
}

void trap_R_RegisterShaderNoMip(uint32_t param_1)
{
  CG_DrawInformation(1);
  (*syscall)(0x56,param_1);
  return;
}

void trap_R_RegisterFont(uint32_t param_1,uint32_t param_2,int param_3)
{
  uint32_t tmp_u1;
  
  CG_DrawInformation(1);
  (*syscall)(0x3a,param_1,param_2,param_3);
  if (*(int *)(param_3 + 0x4fdc) == 0) {
    CG_DrawInformation(1);
    tmp_u1 = (*syscall)(0x56,param_3 + 0x4fe0);
    *(uint32_t *)(param_3 + 0x4fdc) = tmp_u1;
  }
  return;
}

void trap_CM_LoadMap(uint32_t param_1)
{
  CG_DrawInformation(1);
  (*syscall)(0x15,param_1);
  return;
}

void trap_R_LoadWorldMap(uint32_t param_1)
{
  CG_DrawInformation(1);
  (*syscall)(0x34,param_1);
  return;
}

void trap_R_inPVS(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0xab,param_1,param_2);
  return;
}

void trap_GetHunkData(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0xac,param_1,param_2);
  return;
}

void trap_SendMessage(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  char local_10c [260];
  
  (*syscall)(6,"version",local_10c,0x100);
  tmp_pc1 = strstr(local_10c,"2.55");
  if (tmp_pc1 == (char *)0x0) {
    tmp_pc1 = strstr(local_10c,"2.56");
    if (tmp_pc1 == (char *)0x0) {
      (*syscall)(0xae,param_1,param_2);
    }
  }
  return;
}

uint32_t trap_MessageStatus(void)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  char local_10c [260];
  
  (*syscall)(6,"version",local_10c,0x100);
  tmp_pc1 = strstr(local_10c,"2.55");
  if ((tmp_pc1 == (char *)0x0) && (tmp_pc1 = strstr(local_10c,"2.56"), tmp_pc1 == (char *)0x0)) {
    tmp_u2 = (*syscall)(0xaf);
    return tmp_u2;
  }
  return 0;
}

uint32_t trap_R_LoadDynamicShader(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  char local_10c [260];
  
  (*syscall)(6,"version",local_10c,0x100);
  tmp_pc1 = strstr(local_10c,"2.55");
  if ((tmp_pc1 == (char *)0x0) && (tmp_pc1 = strstr(local_10c,"2.56"), tmp_pc1 == (char *)0x0)) {
    tmp_u2 = (*syscall)(0xb0,param_1,param_2);
    return tmp_u2;
  }
  return 0;
}

void trap_R_RenderToTexture
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5)

{
  char *tmp_pc1;
  char local_10c [260];
  
  (*syscall)(6,"version",local_10c,0x100);
  tmp_pc1 = strstr(local_10c,"2.55");
  if (tmp_pc1 == (char *)0x0) {
    tmp_pc1 = strstr(local_10c,"2.56");
    if (tmp_pc1 == (char *)0x0) {
      (*syscall)(0xb1,param_1,param_2,param_3,param_4,param_5);
    }
  }
  return;
}

uint32_t trap_R_GetTextureId(uint32_t param_1)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  char local_10c [260];
  
  (*syscall)(6,"version",local_10c,0x100);
  tmp_pc1 = strstr(local_10c,"2.55");
  if ((tmp_pc1 == (char *)0x0) && (tmp_pc1 = strstr(local_10c,"2.56"), tmp_pc1 == (char *)0x0)) {
    tmp_u2 = (*syscall)(0xb2,param_1);
    return tmp_u2;
  }
  return 0xffffffff;
}

void trap_R_Finish(void)
{
  char *tmp_pc1;
  char local_10c [260];
  
  (*syscall)(6,"version",local_10c,0x100);
  tmp_pc1 = strstr(local_10c,"2.55");
  if (tmp_pc1 == (char *)0x0) {
    tmp_pc1 = strstr(local_10c,"2.56");
    if (tmp_pc1 == (char *)0x0) {
      (*syscall)(0xb3);
    }
  }
  return;
}

