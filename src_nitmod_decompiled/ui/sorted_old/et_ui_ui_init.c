/* Module initialization, setup routines
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"
#include "et_ui_imports.h"
#include "et_ui_ui_init.h"

void BG_InitLocations(float *param_1,float *param_2)

{
{  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  
  g_dat_0006c108 = 1200.0;
  tmp_f2 = *param_2 - *param_1;
  tmp_f1 = tmp_f2 / 1200.0;
  while (tmp_f1 < 7.0) {
    g_dat_0006c108 = g_dat_0006c108 - 50.0;
    tmp_f1 = tmp_f2 / g_dat_0006c108;
  }
  tmp_f2 = param_1[1] - param_2[1];
  g_dat_0006c10c = 1200.0;
  tmp_f3 = tmp_f2 / 1200.0;
  while (tmp_f3 < 7.0) {
    g_dat_0006c10c = g_dat_0006c10c - 50.0;
    tmp_f3 = tmp_f2 / g_dat_0006c10c;
  }
  locInfo = (tmp_f1 - (float)(int)ROUND(tmp_f1)) * g_dat_0006c108 * 0.5 + *param_1;
  g_dat_0006c104 = param_1[1] - (tmp_f3 - (float)(int)ROUND(tmp_f3)) * g_dat_0006c10c * 0.5;
  return;
}

void _UI_Init(void)

{
{  uint32_t *tmp_pu1;
  byte tmp_b2;
  int tmp_i3;
  byte *tmp_pb4;
  uint tmp_u6;
  char *tmp_pc7;
  uint8_t **tmp_ppu8;
  int tmp_i9;
  long double tmp_l10;
  byte *tmp_pb5;
  
  if (0 < cvarTableSize) {
    tmp_ppu8 = &cvarTable;
    tmp_i9 = 0;
    do {
      trap_Cvar_Register(*tmp_ppu8,tmp_ppu8[1],tmp_ppu8[2],tmp_ppu8[3]);
      if (*tmp_ppu8 != (uint8_t *)0x0) {
        tmp_ppu8[4] = *(uint8_t **)(*tmp_ppu8 + 4);
      }
      tmp_i9 = tmp_i9 + 1;
      tmp_ppu8 = tmp_ppu8 + 5;
    } while (tmp_i9 < cvarTableSize);
  }
  trap_Cvar_Set("ui_blackout","0");
  BG_setCrosshair(0x393490,&g_dat_003e8034,GHIDRA_FIELD(cg_crosshairAlpha, 8, 4),"cg_crosshairColor");
  BG_setCrosshair(0x396bb0,&g_dat_003e8044,GHIDRA_FIELD(cg_crosshairAlphaAlt, 8, 4),"cg_crosshairColorAlt");
  UI_InitMemory();
  trap_PC_RemoveAllGlobalDefines();
  trap_Cvar_Set("ui_menuFiles","ui/menus.txt");
  trap_GetGlconfig(&g_dat_003b62b0);
  tmp_i9 = 0;
  g_dat_003e8030 = 0;
  tmp_pb5 = &g_dat_003b6eb0;
  tmp_i3 = g_dat_003e8030;
  tmp_b2 = g_dat_003b6eb0;
  while (tmp_b2 != 0) {
    tmp_pb4 = tmp_pb5;
    g_dat_003e8030 = tmp_i9;
    if (tmp_b2 == 0x20) {
      do {
        g_dat_003e8030 = tmp_i3;
        tmp_pb4 = tmp_pb5 + 1;
        *tmp_pb5 = 0;
        tmp_pb5 = tmp_pb4;
        tmp_i3 = g_dat_003e8030;
      } while (*tmp_pb4 == 0x20);
      tmp_i9 = g_dat_003e8030;
      if (*tmp_pb4 != 0) goto LAB_0003765c;
    }
    else {
LAB_0003765c:
      tmp_i9 = g_dat_003e8030 + 1;
      tmp_pu1 = &g_dat_003e7e30 + g_dat_003e8030;
      g_dat_003e8030 = tmp_i9;
      *tmp_pu1 = tmp_pb4;
    }
    if (tmp_i9 == 0x80) break;
    for (; tmp_b2 = *tmp_pb4, tmp_pb5 = tmp_pb4, tmp_i3 = g_dat_003e8030, (tmp_b2 & 0xdf) != 0;
        tmp_pb4 = tmp_pb4 + 1) {
    }
  }
  g_dat_003e8030 = tmp_i9 + 4;
  g_dat_00397fd0 = (float)g_dat_003b7ef8 * 0.0020833334;
  g_dat_00397fd4 = (float)g_dat_003b7ef4 * 0.0015625;
  if (g_dat_003b7ef8 * 0x280 < g_dat_003b7ef4 * 0x1e0) {
    g_dat_00397fd8 = ((float)g_dat_003b7ef4 - (float)g_dat_003b7ef8 * 1.3333334) * 0.5;
  }
  else {
    g_dat_00397fd8 = 0.0;
  }
  uiInfo = trap_R_RegisterShaderNoMip;
  g_dat_003b7efc = (float)g_dat_003b7ef4 / (float)g_dat_003b7ef8;
  g_dat_00397ec4 = UI_SetColor;
  g_dat_00397ec8 = UI_DrawHandlePic;
  g_dat_00397ecc = trap_R_DrawStretchPic;
  g_dat_00397ed0 = Text_Paint;
  g_dat_00397ed4 = Text_Paint_Ext;
  g_dat_00397ed8 = Text_Width;
  g_dat_00397edc = Text_Width_Ext;
  g_dat_00397ee0 = Multiline_Text_Width;
  g_dat_00397ee4 = Text_Height;
  g_dat_00397ee8 = Text_Height_Ext;
  g_dat_00397eec = Multiline_Text_Height;
  g_dat_00397ef0 = Text_SetActiveFont;
  g_dat_00397ef4 = trap_R_RegisterModel;
  g_dat_00397ef8 = trap_R_ModelBounds;
  g_dat_00397efc = UI_FillRect;
  g_dat_00397f00 = _UI_DrawRect;
  g_dat_00397f04 = _UI_DrawSides;
  g_dat_00397f08 = _UI_DrawTopBottom;
  g_dat_00397f0c = trap_R_ClearScene;
  g_dat_00397f10 = trap_R_AddRefEntityToScene;
  g_dat_00397f14 = trap_R_RenderScene;
  g_dat_00397f18 = trap_R_RegisterFont;
  g_dat_00397f1c = UI_OwnerDraw;
  g_dat_00397f20 = UI_GetValue;
  g_dat_00397f24 = UI_OwnerDrawVisible;
  g_dat_00397f28 = UI_RunMenuScript;
  g_dat_00397f2c = UI_GetTeamColor;
  g_dat_00397f38 = trap_Cvar_Set;
  g_dat_00397f30 = trap_Cvar_VariableStringBuffer;
  g_dat_00397f34 = trap_Cvar_VariableValue;
  g_dat_00397f3c = Text_PaintWithCursor;
  g_dat_00397f40 = trap_Key_SetOverstrikeMode;
  g_dat_00397f44 = trap_Key_GetOverstrikeMode;
  g_dat_00397f48 = trap_S_StartLocalSound;
  g_dat_00397f4c = UI_OwnerDrawHandleKey;
  g_dat_00397f50 = UI_FeederCount;
  g_dat_00397f5c = UI_FeederItemImage;
  g_dat_00397f54 = UI_FeederItemText;
  g_dat_00397f58 = UI_FileText;
  g_dat_00397f60 = UI_FeederSelection;
  g_dat_00397f64 = UI_FeederSelectionClick;
  g_dat_00397f68 = UI_FeederAddItem;
  g_dat_00397f84 = trap_Key_SetBinding;
  g_dat_00397f78 = trap_Key_GetBindingBuf;
  g_dat_00397f7c = trap_Key_KeysForBinding;
  g_dat_00397f74 = trap_Key_KeynumToStringBuf;
  g_dat_00397f80 = trap_Key_IsDown;
  g_dat_00397f88 = trap_Cmd_ExecuteText;
  g_dat_00397f8c = Com_Error;
  g_dat_00397f90 = Com_Printf;
  g_dat_00397f94 = UI_Pause;
  g_dat_00397f98 = UI_OwnerDrawWidth;
  g_dat_00397f9c = trap_S_RegisterSound;
  g_dat_00397fa0 = trap_S_StartBackgroundTrack;
  g_dat_00397fa4 = trap_S_StopBackgroundTrack;
  g_dat_00397fa8 = UI_PlayCinematic;
  g_dat_00397fac = UI_StopCinematic;
  g_dat_00397fb0 = UI_DrawCinematic;
  g_dat_00397fb4 = UI_RunCinematicFrame;
  g_dat_00397f6c = trap_CheckAutoUpdate;
  g_dat_00397f70 = trap_GetAutoUpdate;
  g_dat_00397fb8 = UI_DescriptionForCampaign;
  g_dat_00397fbc = UI_NameForCampaign;
  g_dat_00397fc0 = trap_R_Add2dPolys;
  g_dat_00397fc4 = trap_UpdateScreen;
  g_dat_00397fc8 = trap_GetHunkData;
  g_dat_00397fcc = trap_GetConfigString;
  Init_Display(&uiInfo);
  String_Init();
  g_dat_003b7f10 = trap_R_RegisterShaderNoMip("white");
  AssetCache();
  g_dat_003e8054 = trap_R_RegisterShaderNoMip("ui/assets/filter_pass.tga");
  g_dat_003e8058 = trap_R_RegisterShaderNoMip("ui/assets/filter_ff.tga");
  g_dat_003e805c = trap_R_RegisterShaderNoMip("ui/assets/filter_lives.tga");
  g_dat_003e8060 = trap_R_RegisterShaderNoMip("ui/assets/filter_pb.tga");
  g_dat_003e8064 = trap_R_RegisterShaderNoMip("ui/assets/filter_weap.tga");
  g_dat_003e8068 = trap_R_RegisterShaderNoMip("ui/assets/filter_antilag.tga");
  g_dat_003e806c = trap_R_RegisterShaderNoMip("ui/assets/filter_balance.tga");
  g_dat_003e8070 = trap_R_RegisterShaderNoMip("ui/assets/filter_nxac_loading.tga");
  g_dat_003e8074 = trap_R_RegisterShaderNoMip("gfx/loading/camp_map.tga");
  trap_Milliseconds();
  g_dat_003b7f38 = 0;
  g_dat_003b8544 = 0;
  g_dat_003b8340 = 0;
  UI_ParseGameInfo_constprop_57();
  UI_LoadMenus("ui/menus.txt",0);
  Menus_CloseAll();
  trap_LAN_LoadCachedServers();
  tmp_l10 = (long double)trap_Cvar_VariableValue("color");
  tmp_u6 = (int)ROUND(tmp_l10) - 1;
  if (6 < tmp_u6) {
    tmp_u6 = 0;
  }
  g_dat_003e7e20 = (&gamecodetoui)[tmp_u6];
  tmp_l10 = (long double)trap_Cvar_VariableValue("cg_drawCrosshair");
  g_dat_003e7e14 = (int)ROUND(tmp_l10);
  tmp_l10 = (long double)trap_Cvar_VariableValue("m_pitch");
  tmp_pc7 = "0";
  if (tmp_l10 < (long double)0) {
    tmp_pc7 = "1";
  }
  trap_Cvar_Set("ui_mousePitch",tmp_pc7);
  g_dat_003e53e0 = 0xffffffff;
  g_dat_003e13a8 = 0xffffffff;
  tmp_l10 = (long double)trap_Cvar_VariableValue("ui_TeamArenaFirstRun");
  if (tmp_l10 == (long double)0) {
    trap_Cvar_Set("s_volume",&g_dat_000571af);
    trap_Cvar_Set("s_musicvolume",&g_dat_000571bc);
    trap_Cvar_Set("ui_TeamArenaFirstRun","1");
  }
  trap_Cvar_Register(0,"debug_protocol","",0);
  trap_AddCommand("campaign");
  trap_AddCommand("listcampaigns");
  return;
}

void Tooltip_Initialize(int param_1)

{
{  *(uint32_t *)(param_1 + 0x44) = 0x3f800000;
  *(uint32_t *)(param_1 + 0xe8) = 0;
  *(uint32_t *)(param_1 + 0xe0) = 2;
  *(uint32_t *)(param_1 + 0x84) = 0x3f666666;
  *(uint32_t *)(param_1 + 0x88) = 0x3f666666;
  *(uint32_t *)(param_1 + 0x90) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x94) = 0;
  *(uint32_t *)(param_1 + 0x98) = 0;
  *(uint32_t *)(param_1 + 0x9c) = 0;
  *(uint32_t *)(param_1 + 0xa0) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x74) = 0;
  *(uint32_t *)(param_1 + 0x78) = 0;
  *(uint32_t *)(param_1 + 0x7c) = 0;
  *(uint32_t *)(param_1 + 0xd4) = 0x40400000;
  *(uint32_t *)(param_1 + 0x80) = 0x3f800000;
  *(uint32_t *)(param_1 + 0xd8) = 0x41200000;
  *(uint32_t *)(param_1 + 0xdc) = 0x3e4ccccd;
  *(uint32_t *)(param_1 + 0x38) = 1;
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xfffffffb | 0x2080000;
  *(uint32_t *)(param_1 + 0x8c) = 0x3f400000;
  return;
}

void Window_Init(uint16_t *param_1)

{
{  bool tmp_b1;
  uint tmp_u2;
  uint16_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint tmp_u5;
  
  tmp_u5 = 0xb8;
  tmp_b1 = false;
  if (((uint)param_1 & 1) == 0) {
    tmp_pu3 = param_1;
    if (((uint)param_1 & 2) == 0) goto LAB_0003defb;
  }
  else {
    tmp_pu3 = (uint16_t *)((int)param_1 + 1);
    tmp_u5 = 0xb7;
    tmp_b1 = true;
    *(uint8_t *)param_1 = 0;
    if (((uint)tmp_pu3 & 2) == 0) goto LAB_0003defb;
    tmp_u5 = 0xb7;
    tmp_b1 = true;
  }
  *tmp_pu3 = 0;
  tmp_u5 = tmp_u5 - 2;
  tmp_pu3 = tmp_pu3 + 1;
LAB_0003defb:
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)tmp_pu3 + tmp_u2) = 0;
    *(uint32_t *)((int)tmp_pu3 + tmp_u2 + 4) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < (tmp_u5 & 0xfffffff8));
  tmp_pu4 = (uint32_t *)((int)tmp_pu3 + tmp_u2);
  if ((tmp_u5 & 4) != 0) {
    *tmp_pu4 = 0;
    tmp_pu4 = tmp_pu4 + 1;
  }
  if ((tmp_u5 & 2) != 0) {
    *(uint16_t *)tmp_pu4 = 0;
    tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
  }
  if (tmp_b1) {
    *(uint8_t *)tmp_pu4 = 0;
  }
  *(uint32_t *)(param_1 + 0x22) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x40) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x3e) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x3c) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x3a) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x18) = 0xffffffff;
  return;
}
