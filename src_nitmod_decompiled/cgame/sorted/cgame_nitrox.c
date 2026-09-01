/* Nitrox extensions, integrity and crash reporting — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_nitrox.h"

uint32_t Nit_RemoveWordInString(char *param_1,char *param_2)
{
  size_t tmp_s1;
  int tmp_i2;
  size_t tmp_s3;
  char tmp_c4;
  char *__src;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  tmp_s1 = strlen(param_2);
  tmp_c4 = *param_1;
  if (tmp_c4 != '\0') {
    tmp_s3 = 0;
    tmp_i2 = 0;
    __src = param_1 + 1;
    do {
      while (tmp_c4 == param_2[tmp_i2]) {
        tmp_s3 = tmp_s3 + 1;
        tmp_i2 = tmp_i2 + 1;
        if (tmp_s3 == tmp_s1) goto LAB_000264a8;
LAB_00026494:
        tmp_c4 = *__src;
        __src = __src + 1;
        if (tmp_c4 == '\0') {
          return 1;
        }
      }
      if (tmp_s3 != tmp_s1) goto LAB_00026494;
LAB_000264a8:
      strcpy(__src + -tmp_s3,__src);
      tmp_c4 = *__src;
      tmp_s3 = 0;
      tmp_i2 = 0;
      __src = __src + 1;
    } while (tmp_c4 != '\0');
  }
  return 1;
}

void nitrox_AddPredictableDamage
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,int param_4)

{
  *(int *)(param_4 + 0xc0) = *(int *)(param_4 + 0xc0) + 1;
  *(uint32_t *)(param_4 + 0xcc) = param_1;
  *(uint32_t *)(param_4 + 200) = param_2;
  *(uint32_t *)(param_4 + 0xc4) = param_3;
  return;
}

uint32_t nitrox_GetTokenForString(char *param_1)
{
  size_t tmp_s1;
  int tmp_i2;
  
  tmp_s1 = strlen(param_1);
  tmp_i2 = in_word_set(param_1,tmp_s1);
  if (tmp_i2 != 0) {
    return *(uint32_t *)(tmp_i2 + 4);
  }
  return 0x117;
}

bool nitrox_CreateDirectory(uint32_t param_1)
{
  uint tmp_u1;
  uint tmp_u2;
  int tmp_i3;
  bool tmp_b4;
  stat local_364;
  char local_30c [4];
  uint32_t local_308 [191];
  
  local_30c[0] = '\0';
  local_30c[1] = '\0';
  local_30c[2] = '\0';
  local_30c[3] = '\0';
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_308 + tmp_u2) = 0;
    *(uint32_t *)((int)local_308 + tmp_u2 + 4) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xf8);
  *(uint32_t *)((int)local_308 + tmp_u2 + 8) = 0;
  local_308[0x3f] = 0;
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x100) = 0;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x104) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xf8);
  *(uint32_t *)((int)local_308 + tmp_u2 + 0x108) = 0;
  local_308[0x7f] = 0;
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x200) = 0;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x204) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xf8);
  *(uint32_t *)((int)local_308 + tmp_u2 + 0x208) = 0;
  trap_Cvar_VariableStringBuffer("fs_homepath",local_308 + 0x7f,0x100);
  trap_Cvar_VariableStringBuffer("fs_game",local_308 + 0x3f,0x100);
  Com_sprintf(local_30c,0x100,"%s/%s/%s",local_308 + 0x7f,local_308 + 0x3f,param_1);
  tmp_i3 = __xstat(3,local_30c,&local_364);
  if ((tmp_i3 == -1) || (tmp_b4 = true, (local_364.GHIDRA_FIELD(st_mode, 1, 1) & 0x40) == 0)) {
    tmp_i3 = mkdir(local_30c,0x1c0);
    tmp_b4 = tmp_i3 == 0;
  }
  return tmp_b4;
}

uint8_t * BG_BuildFilePath(char *param_1,uint32_t param_2,uint32_t param_3,uint8_t *param_4,
                uint32_t param_5)

{
  size_t tmp_s1;
  
  tmp_s1 = strlen(param_1);
  *param_4 = 0;
  Q_strcat(param_4,param_5,param_1);
  if (((tmp_s1 != 0) && (param_1[tmp_s1 - 1] != '/')) && (param_1[tmp_s1 - 1] != '\\')) {
    Q_strcat(param_4,param_5,"/");
  }
  Q_strcat(param_4,param_5,param_2);
  Q_strcat(param_4,param_5,param_3);
  return param_4;
}

void nitrox_MinimizeET_f(void)
{
  CG_Printf("Sorry, minimize command is not yet supported by your OS.\n");
  return;
}

void nitmod_PrintCGS(void)
{
  size_t tmp_s1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_i6 = 0;
  tmp_i5 = 0;
  do {
    tmp_pc2 = (char *)CG_ConfigString(tmp_i5);
    if (*tmp_pc2 != '\0') {
      tmp_u3 = CG_ConfigString(tmp_i5);
      CG_Printf(&g_unk_00112636,tmp_i5,tmp_u3);
    }
    tmp_i4 = tmp_i5 + 1;
    tmp_pc2 = (char *)CG_ConfigString(tmp_i5);
    tmp_s1 = strlen(tmp_pc2);
    tmp_i6 = tmp_i6 + tmp_s1;
    tmp_i5 = tmp_i4;
  } while (tmp_i4 != 0x400);
  CG_Printf("^9|------------------------------\n^2%d ^7chars in Gamestate\n^9|------------------------------\n"
            ,tmp_i6);
  return;
}

void nitrox_GlobalStatsCmd_f(void)
{
  if (g_unk_01047aec != 0) {
    g_unk_010ef1f4 = 0;
    return;
  }
  if (g_unk_010ef1f4 == 0) {
    if ((g_unk_010ef1fc == 0) || (g_unk_010ef244 != 1)) {
      g_unk_010ef1f4 = 1;
      g_unk_010ef244 = 1;
      g_unk_010ef1fc = g_unk_010906e0;
    }
  }
  else if ((g_unk_010ef1fc == 0) || (g_unk_010ef244 != 2)) {
    if (0x1c2 < g_unk_010906e0 - g_unk_010ef1fc) {
      g_unk_010ef1fc = g_unk_010906e0;
    }
    g_unk_010ef244 = 2;
    return;
  }
  return;
}

uint32_t nitrox_ClassNumForLetter(char *param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 0;
  if ((byte)(*param_1 + 0x9dU) < 0xb) {
    tmp_u1 = *(uint32_t *)(CSWTCH_54 + (uint)(byte)(*param_1 + 0x9dU) * 4);
  }
  return tmp_u1;
}

void nitrox_DrawPopup(void)
{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint tmp_u6;
  uint tmp_u7;
  size_t tmp_s8;
  byte *tmp_pb9;
  int tmp_i10;
  uint *tmp_pu11;
  uint *tmp_pu12;
  int tmp_i13;
  float local_70;
  float local_44;
  float local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x59759;
  local_44 = (float)GHIDRA_FIELD(cg_notificationFadeTime, 8, 4);
  local_40 = (float)GHIDRA_FIELD(cg_notificationTime, 8, 4);
  nitrox_ClampFloat(&local_44,0,0x437a0000);
  nitrox_ClampFloat(&local_40,0x44bb8000,0x461c4000);
  if (local_44 == 0.0) {
    return;
  }
  if (g_unk_010ef25c == 0) {
    g_unk_010ef258 = 0;
    return;
  }
  if (g_unk_010ef258 == 2) {
    if (**(char **)(globalAwards + g_unk_010ef250 * 0x14 + 0xc) == '\0') {
      g_unk_010ef258 = 0;
      g_unk_010ef25c = 0;
      g_unk_010ef260 = 0;
      return;
    }
    Q_strncpyz(&g_unk_010ef264,*(uint32_t *)(globalAwards + g_unk_010ef250 * 0x14 + 0x10),0x400);
    local_70 = (float)(g_unk_010906e0 - g_unk_010ef25c);
    if (g_unk_010ef258 != 2) goto LAB_000597fe;
    local_3c = colorMdBlue;
    local_38 = g_unk_0014a294;
    local_34 = g_unk_0014a298;
  }
  else {
    local_70 = (float)(g_unk_010906e0 - g_unk_010ef25c);
LAB_000597fe:
    local_3c = HUD_Background;
    local_38 = g_unk_00143edc;
    local_34 = g_unk_00143ee0;
  }
  local_2c = colorWhite;
  local_28 = g_unk_0014a334;
  local_24 = g_unk_0014a338;
  if (g_unk_010ef260 == 1) {
    local_20 = (float)(int)local_70 / local_44;
    if (1.0 <= local_20) {
      g_unk_010ef260 = 2;
      g_unk_010ef25c = (int)ROUND((float)g_unk_010906e0 + local_40);
      local_30 = 0.5;
      local_20 = 1.0;
      goto LAB_0005989c;
    }
LAB_00059be4:
    local_30 = local_20 * 0.5;
  }
  else {
    if (g_unk_010ef260 == 2) {
      local_20 = 1.0 - (float)(int)local_70 / local_44;
      if (local_20 <= 0.0) {
        g_unk_010ef25c = 0;
        g_unk_010ef260 = 0;
        return;
      }
      if (local_20 < 1.0) goto LAB_00059be4;
    }
    local_30 = 0.5;
    local_20 = 1.0;
  }
LAB_0005989c:
  tmp_pu12 = &g_unk_010ef264;
  do {
    tmp_pu11 = tmp_pu12;
    tmp_u6 = *tmp_pu11 + 0xfefefeff & ~*tmp_pu11;
    tmp_u7 = tmp_u6 & 0x80808080;
    tmp_pu12 = tmp_pu11 + 1;
  } while (tmp_u7 == 0);
  if ((tmp_u6 & 0x8080) == 0) {
    tmp_pu12 = (uint *)((int)tmp_pu11 + 6);
    tmp_u7 = tmp_u7 >> 0x10;
  }
  tmp_i10 = 0;
  tmp_i13 = (int)tmp_pu12 + (-0x10ef267 - (uint)CARRY1((byte)tmp_u7,(byte)tmp_u7));
  tmp_f2 = 0.0;
  tmp_pb9 = (byte *)&g_unk_010ef264;
  do {
    while( true ) {
      tmp_b1 = *tmp_pb9;
      if ((tmp_b1 == 0) || (tmp_i13 <= tmp_i10)) goto LAB_00059950;
      if ((tmp_b1 != 0x5e) || ((tmp_pb9[1] == 0 || (tmp_pb9[1] == 0x5e)))) break;
      tmp_pb9 = tmp_pb9 + 2;
      if (tmp_pb9 == (byte *)0x0) goto LAB_00059950;
    }
    tmp_pb9 = tmp_pb9 + 1;
    tmp_i10 = tmp_i10 + 1;
    tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x1b19c) + tmp_f2;
  } while (tmp_pb9 != (byte *)0x0);
LAB_00059950:
  tmp_i10 = 0;
  tmp_pb9 = (byte *)&g_unk_010ef264;
  tmp_f3 = 0.0;
  do {
    while( true ) {
      tmp_b1 = *tmp_pb9;
      if ((tmp_b1 == 0) || (tmp_i13 <= tmp_i10)) goto LAB_000599c0;
      if ((tmp_b1 != 0x5e) || ((tmp_pb9[1] == 0 || (tmp_pb9[1] == 0x5e)))) break;
      tmp_pb9 = tmp_pb9 + 2;
      if (tmp_pb9 == (byte *)0x0) goto LAB_000599c0;
    }
    tmp_f5 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x1b18c);
    if ((float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x1b18c) <= tmp_f3) {
      tmp_f5 = tmp_f3;
    }
    tmp_f3 = tmp_f5;
    tmp_pb9 = tmp_pb9 + 1;
    tmp_i10 = tmp_i10 + 1;
  } while (tmp_pb9 != (byte *)0x0);
LAB_000599c0:
  tmp_f5 = (float)(int)ROUND(tmp_f3 * (float)GHIDRA_FIELD(cgs, 131468, 4) * 0.2) * 0.5;
  tmp_f3 = (float)(int)ROUND(tmp_f2 * (float)GHIDRA_FIELD(cgs, 131468, 4) * 0.2) + 20.0;
  tmp_f2 = 639.0 - tmp_f3 * local_20;
  if (g_unk_010ef258 == 2) {
    local_70 = 50.0;
  }
  else {
    local_70 = 24.0;
  }
  CG_HudPlacement(2);
  CG_FillRect(tmp_f2,0,tmp_f3,local_70,&local_3c);
  CG_DrawRect_FixedBorder(tmp_f2,0,tmp_f3,local_70,1,&local_2c);
  if (g_unk_010ef258 == 1) {
    tmp_pu12 = &g_unk_010ef264;
    do {
      tmp_pu11 = tmp_pu12;
      tmp_u6 = *tmp_pu11 + 0xfefefeff & ~*tmp_pu11;
      tmp_u7 = tmp_u6 & 0x80808080;
      tmp_pu12 = tmp_pu11 + 1;
    } while (tmp_u7 == 0);
    if ((tmp_u6 & 0x8080) == 0) {
      tmp_pu12 = (uint *)((int)tmp_pu11 + 6);
      tmp_u7 = tmp_u7 >> 0x10;
    }
    tmp_i10 = 0;
    tmp_f4 = 0.0;
    tmp_pb9 = (byte *)&g_unk_010ef264;
    do {
      tmp_b1 = *tmp_pb9;
      if ((tmp_b1 == 0) ||
         ((int)((int)tmp_pu12 + (-0x10ef267 - (uint)CARRY1((byte)tmp_u7,(byte)tmp_u7))) <= tmp_i10))
      break;
      if ((tmp_b1 == 0x5e) && ((tmp_pb9[1] != 0 && (tmp_pb9[1] != 0x5e)))) {
        tmp_pb9 = tmp_pb9 + 2;
      }
      else {
        tmp_pb9 = tmp_pb9 + 1;
        tmp_i10 = tmp_i10 + 1;
        tmp_f4 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x1b19c) + tmp_f4;
      }
    } while (tmp_pb9 != (byte *)0x0);
    CG_Text_Paint_Ext_constprop_18
              ((tmp_f2 + tmp_f3 * 0.5) - (float)(int)ROUND((float)GHIDRA_FIELD(cgs, 131468, 4) * 0.2 * tmp_f4) * 0.5,
               local_70 * 0.5 + tmp_f5 + 0.0,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
  }
  else {
    tmp_i10 = 0;
    tmp_f5 = tmp_f5 + 0.0;
    tmp_pb9 = cgs + g_unk_010ef24c * 0x1a4 + 0x9414;
    tmp_f2 = tmp_f3 * 0.5 + tmp_f2;
    tmp_f3 = (float)GHIDRA_FIELD(cgs, 131468, 4) * 0.2;
    tmp_s8 = strlen((char *)tmp_pb9);
    tmp_f4 = 0.0;
    do {
      tmp_b1 = *tmp_pb9;
      if ((tmp_b1 == 0) || ((int)tmp_s8 <= tmp_i10)) break;
      if ((tmp_b1 == 0x5e) && ((tmp_pb9[1] != 0 && (tmp_pb9[1] != 0x5e)))) {
        tmp_pb9 = tmp_pb9 + 2;
      }
      else {
        tmp_pb9 = tmp_pb9 + 1;
        tmp_i10 = tmp_i10 + 1;
        tmp_f4 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x1b19c) + tmp_f4;
      }
    } while (tmp_pb9 != (byte *)0x0);
    CG_Text_Paint_Ext_constprop_18
              (tmp_f2 - (float)(int)ROUND(tmp_f4 * tmp_f3) * 0.5,local_70 * 0.25 + tmp_f5,0x3e4ccccd,
               0x3e4ccccd,7,0x110afec);
    tmp_pb9 = *(byte **)(globalAwards + g_unk_010ef250 * 0x14 + 0xc);
    tmp_f3 = (float)GHIDRA_FIELD(cgs, 131468, 4) * 0.2;
    if (tmp_pb9 == (byte *)0x0) {
      tmp_f4 = 0.0;
    }
    else {
      tmp_i10 = 0;
      tmp_s8 = strlen((char *)tmp_pb9);
      tmp_f4 = 0.0;
      do {
        tmp_b1 = *tmp_pb9;
        if ((tmp_b1 == 0) || ((int)tmp_s8 <= tmp_i10)) break;
        if ((tmp_b1 == 0x5e) && ((tmp_pb9[1] != 0 && (tmp_pb9[1] != 0x5e)))) {
          tmp_pb9 = tmp_pb9 + 2;
        }
        else {
          tmp_pb9 = tmp_pb9 + 1;
          tmp_i10 = tmp_i10 + 1;
          tmp_f4 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x1b19c) + tmp_f4;
        }
      } while (tmp_pb9 != (byte *)0x0);
    }
    CG_Text_Paint_Ext_constprop_18
              (tmp_f2 - (float)(int)ROUND(tmp_f4 * tmp_f3) * 0.5,local_70 * 0.5 + tmp_f5,0x3e4ccccd,
               0x3e4ccccd,7,0x110afec);
    tmp_pu12 = &g_unk_010ef264;
    do {
      tmp_pu11 = tmp_pu12;
      tmp_u6 = *tmp_pu11 + 0xfefefeff & ~*tmp_pu11;
      tmp_u7 = tmp_u6 & 0x80808080;
      tmp_pu12 = tmp_pu11 + 1;
    } while (tmp_u7 == 0);
    if ((tmp_u6 & 0x8080) == 0) {
      tmp_pu12 = (uint *)((int)tmp_pu11 + 6);
      tmp_u7 = tmp_u7 >> 0x10;
    }
    tmp_i10 = 0;
    tmp_f3 = 0.0;
    tmp_pb9 = (byte *)&g_unk_010ef264;
    do {
      tmp_b1 = *tmp_pb9;
      if ((tmp_b1 == 0) ||
         ((int)((int)tmp_pu12 + (-0x10ef267 - (uint)CARRY1((byte)tmp_u7,(byte)tmp_u7))) <= tmp_i10))
      break;
      if ((tmp_b1 == 0x5e) && ((tmp_pb9[1] != 0 && (tmp_pb9[1] != 0x5e)))) {
        tmp_pb9 = tmp_pb9 + 2;
      }
      else {
        tmp_pb9 = tmp_pb9 + 1;
        tmp_i10 = tmp_i10 + 1;
        tmp_f3 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x1b19c) + tmp_f3;
      }
    } while (tmp_pb9 != (byte *)0x0);
    CG_Text_Paint_Ext_constprop_18
              (tmp_f2 - (float)(int)ROUND((float)GHIDRA_FIELD(cgs, 131468, 4) * 0.2 * tmp_f3) * 0.5,
               local_70 * 0.75 + tmp_f5,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
    if (g_unk_010ef254 == 0) {
      CG_Printf("^7N^1!^7tmod ^5Global Awards ^g[^7%s^g] ^3%s ^7- ^8%s^7\n",
                g_unk_010ef24c * 0x1a4 + 0x10f9274,
                *(uint32_t *)(globalAwards + g_unk_010ef250 * 0x14 + 0xc),&g_unk_010ef264);
      g_unk_010ef254 = 1;
    }
  }
  return;
}

uint32_t nitrox_DrawGlobalStats(void)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  byte *tmp_pb6;
  size_t tmp_s7;
  uint32_t tmp_u8;
  char *tmp_pc9;
  byte tmp_b10;
  int tmp_i11;
  int tmp_i12;
  float local_8c;
  byte *local_88;
  int local_84;
  float local_7c;
  float local_74;
  float local_6c;
  float local_44;
  float local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x5a52b;
  if (g_unk_010ef1fc == 0) {
    return 0;
  }
  if (g_unk_010ef1f4 == 0) {
    return 0;
  }
  local_44 = 0.8;
  local_40 = 1.0;
  if ((g_unk_010ef1f8 < g_unk_010906e0) || (g_unk_010ef248 != *(int *)(g_unk_01047b00 + 0xcc))) {
    g_unk_010ef200 = 0;
    statsRequested_13004 = 0;
  }
  local_3c = colorBlack;
  local_38 = g_unk_0014a3b4;
  local_34 = g_unk_0014a3b8;
  local_30 = (float)g_unk_0014a3bc;
  local_2c = colorWhite;
  local_28 = g_unk_0014a334;
  local_24 = g_unk_0014a338;
  local_20 = (float)g_unk_0014a33c;
  if (g_unk_010ef244 == 1) {
    local_44 = (float)(g_unk_010906e0 - g_unk_010ef1fc) / 250.0;
    local_40 = local_44;
    nitrox_ClampFloat(&local_44,0,0x3f4ccccd);
    nitrox_ClampFloat(&local_40,0,0x3f800000);
    if (local_40 < 1.0) {
      tmp_f1 = local_40 * 600.0;
      local_8c = local_40 * 120.0;
      local_7c = 320.0 - tmp_f1 * 0.5;
      local_6c = local_8c * 0.5;
      local_74 = 300.0 - local_6c;
    }
    else {
      local_74 = 240.0;
      local_6c = 60.0;
      local_40 = 1.0;
      local_7c = 20.0;
      local_44 = 1.0;
      local_8c = 120.0;
      g_unk_010ef244 = 0;
      tmp_f1 = 600.0;
    }
  }
  else if (g_unk_010ef244 == 2) {
    local_44 = 0.8 - (float)(g_unk_010906e0 - g_unk_010ef1fc) / 250.0;
    if (local_44 <= 0.0) {
      g_unk_010ef1f4 = 0;
      g_unk_010ef1fc = 0;
      g_unk_010ef244 = 0;
      return 0;
    }
    tmp_f1 = local_44 * 600.0;
    local_8c = local_44 * 120.0;
    local_7c = 320.0 - tmp_f1 * 0.5;
    local_6c = local_8c * 0.5;
    local_74 = 300.0 - local_6c;
    local_40 = local_44;
  }
  else {
    local_74 = 240.0;
    local_6c = 60.0;
    local_7c = 20.0;
    local_8c = 120.0;
    tmp_f1 = 600.0;
  }
  tmp_i11 = 0;
  local_30 = local_44;
  local_20 = local_40;
  CG_HudPlacement(0);
  CG_FillRect(local_7c,local_74,tmp_f1,local_8c,&local_3c);
  tmp_pc9 = "^7N^1!^7tmod ^5Global Player Stats^7";
  tmp_f1 = local_40 * 0.22;
  tmp_f2 = 0.0;
  do {
    while( true ) {
      tmp_b10 = *tmp_pc9;
      if ((tmp_b10 == 0) || (0x23 < tmp_i11)) goto LAB_0005a714;
      if ((tmp_b10 != 0x5e) || ((tmp_pc9[1] == 0 || (tmp_pc9[1] == 0x5e)))) break;
      tmp_pc9 = tmp_pc9 + 2;
      if ((byte *)tmp_pc9 == (byte *)0x0) goto LAB_0005a714;
    }
    tmp_pc9 = tmp_pc9 + 1;
    tmp_i11 = tmp_i11 + 1;
    tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b10 * 0x50 + 0x11114) + tmp_f2;
  } while ((byte *)tmp_pc9 != (byte *)0x0);
LAB_0005a714:
  CG_Text_Paint_Ext_constprop_18
            (320.0 - (float)(int)ROUND((float)GHIDRA_FIELD(cgs, 90372, 4) * tmp_f1 * tmp_f2) * 0.5,
             local_40 * 20.0 + local_74,tmp_f1,tmp_f1,7,0x1100f64);
  tmp_pb6 = (byte *)va("Displaying stats for player ^7%s^7",g_unk_010ef248 * 0x1a4 + 0x10f9274);
  tmp_f1 = local_40 * 0.21;
  tmp_f3 = local_40 * 30.0;
  tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * tmp_f1;
  if (tmp_pb6 == (byte *)0x0) {
    tmp_f4 = 0.0;
  }
  else {
    tmp_i11 = 0;
    tmp_s7 = strlen((char *)tmp_pb6);
    tmp_f4 = 0.0;
    do {
      while( true ) {
        tmp_b10 = *tmp_pb6;
        if ((tmp_b10 == 0) || ((int)tmp_s7 <= tmp_i11)) goto LAB_0005a848;
        if ((tmp_b10 != 0x5e) || ((tmp_pb6[1] == 0 || (tmp_pb6[1] == 0x5e)))) break;
        tmp_pb6 = tmp_pb6 + 2;
        if (tmp_pb6 == (byte *)0x0) goto LAB_0005a848;
      }
      tmp_pb6 = tmp_pb6 + 1;
      tmp_i11 = tmp_i11 + 1;
      tmp_f4 = (float)*(int *)(cgs + (uint)tmp_b10 * 0x50 + 0x11114) + tmp_f4;
    } while (tmp_pb6 != (byte *)0x0);
  }
LAB_0005a848:
  CG_Text_Paint_Ext_constprop_18
            (320.0 - (float)(int)ROUND(tmp_f4 * tmp_f2) * 0.5,tmp_f3 + local_74,tmp_f1,tmp_f1,7,0x1100f64
            );
  tmp_u8 = BindingFromName("globalstats");
  tmp_pb6 = (byte *)va("^7Press %s to close.^7",tmp_u8);
  tmp_f1 = local_40 * 0.2;
  tmp_f3 = local_8c + local_74;
  tmp_f4 = local_40 * 5.0;
  tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * tmp_f1;
  if (tmp_pb6 == (byte *)0x0) {
    tmp_f5 = 0.0;
  }
  else {
    tmp_i11 = 0;
    tmp_s7 = strlen((char *)tmp_pb6);
    tmp_f5 = 0.0;
    do {
      while( true ) {
        tmp_b10 = *tmp_pb6;
        if ((tmp_b10 == 0) || ((int)tmp_s7 <= tmp_i11)) goto LAB_0005a974;
        if ((tmp_b10 != 0x5e) || ((tmp_pb6[1] == 0 || (tmp_pb6[1] == 0x5e)))) break;
        tmp_pb6 = tmp_pb6 + 2;
        if (tmp_pb6 == (byte *)0x0) goto LAB_0005a974;
      }
      tmp_pb6 = tmp_pb6 + 1;
      tmp_i11 = tmp_i11 + 1;
      tmp_f5 = (float)*(int *)(cgs + (uint)tmp_b10 * 0x50 + 0x11114) + tmp_f5;
    } while (tmp_pb6 != (byte *)0x0);
  }
LAB_0005a974:
  CG_Text_Paint_Ext_constprop_18
            (320.0 - (float)(int)ROUND(tmp_f5 * tmp_f2) * 0.5,tmp_f3 - tmp_f4,tmp_f1,tmp_f1,7,0x1100f64);
  if (g_unk_010ef200 == 0) {
    tmp_i11 = 0;
    tmp_f1 = local_40 * 0.2;
    tmp_pc9 = "^7Please wait while updating your stats...^7";
    tmp_f2 = 0.0;
    do {
      tmp_b10 = *tmp_pc9;
      if ((tmp_b10 == 0) || (0x2b < tmp_i11)) break;
      if ((tmp_b10 == 0x5e) && ((tmp_pc9[1] != 0 && (tmp_pc9[1] != 0x5e)))) {
        tmp_pc9 = tmp_pc9 + 2;
      }
      else {
        tmp_pc9 = tmp_pc9 + 1;
        tmp_i11 = tmp_i11 + 1;
        tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b10 * 0x50 + 0x11114) + tmp_f2;
      }
    } while ((byte *)tmp_pc9 != (byte *)0x0);
    CG_Text_Paint_Ext_constprop_18
              (320.0 - (float)(int)ROUND((float)GHIDRA_FIELD(cgs, 90372, 4) * tmp_f1 * tmp_f2) * 0.5,
               tmp_f3 - local_40 * 15.0,tmp_f1,tmp_f1,7,0x1100f64);
    if (statsRequested_13004 != 0) {
      return 1;
    }
    g_unk_010ef248 = *(uint32_t *)(g_unk_01047b00 + 0xcc);
    tmp_u8 = va("ggs %i",g_unk_010ef248);
    trap_SendConsoleCommand(tmp_u8);
    statsRequested_13004 = 1;
    g_unk_010ef1f8 = g_unk_010906e0 + 15000;
    return 1;
  }
  if (g_unk_010ef204 != -1) {
    local_8c = 0.0;
    do {
      tmp_i11 = 0;
      do {
        while (tmp_f1 = local_40, local_84 = (int)ROUND(local_74), local_8c == 0.0) {
          local_88 = *(byte **)(GlobalStatsNames + tmp_i11);
          if (**(char **)((int)&GlobalStatsNames2 + tmp_i11) == '\0') {
            local_84 = (int)ROUND(local_40 * 5.0 + local_74);
          }
          tmp_b10 = *local_88;
          if (tmp_b10 != 0) goto LAB_0005aa72;
LAB_0005b242:
          va("%d",*(uint32_t *)((int)&g_unk_010ef204 + tmp_i11));
          tmp_f1 = local_40;
          tmp_i12 = CG_Text_Width_Ext_constprop_17(local_40 * 0.18);
          CG_Text_Paint_Ext_constprop_18
                    (((float)*(int *)(statsPositions + tmp_i11) * tmp_f1 + local_7c + tmp_f1 * 30.0) -
                     (float)tmp_i12 * 0.5 * tmp_f1,tmp_f1 * 80.0 + local_74,tmp_f1 * 0.19,tmp_f1 * 0.19,7
                     ,0x110afec);
LAB_0005aa40:
          tmp_i11 = tmp_i11 + 4;
          if (tmp_i11 == 0x34) goto LAB_0005aca2;
        }
        local_88 = *(byte **)((int)&GlobalStatsNames2 + tmp_i11);
        tmp_b10 = *local_88;
        if (tmp_b10 == 0) goto LAB_0005aa40;
LAB_0005aa72:
        tmp_f2 = local_40 * 0.18 * (float)GHIDRA_FIELD(cgs, 131468, 4);
        tmp_s7 = strlen((char *)local_88);
        tmp_i12 = 0;
        tmp_f4 = 0.0;
        while ((tmp_b10 != 0 && (tmp_i12 < (int)tmp_s7))) {
          if ((tmp_b10 == 0x5e) && ((local_88[1] != 0 && (local_88[1] != 0x5e)))) {
            local_88 = local_88 + 2;
          }
          else {
            local_88 = local_88 + 1;
            tmp_i12 = tmp_i12 + 1;
            tmp_f4 = (float)*(int *)(cgs + (uint)tmp_b10 * 0x50 + 0x1b19c) + tmp_f4;
          }
          if (local_88 == (byte *)0x0) break;
          tmp_b10 = *local_88;
        }
        CG_Text_Paint_Ext_constprop_18
                  (((float)*(int *)(statsPositions + tmp_i11) * tmp_f1 + local_7c + tmp_f1 * 30.0) -
                   (float)(int)ROUND(tmp_f4 * tmp_f2) * 0.5 * tmp_f1,
                   (float)((int)local_8c * 10) * tmp_f1 + tmp_f1 * 50.0 + (float)local_84,tmp_f1 * 0.19
                   ,tmp_f1 * 0.19,7,0x110afec);
        if (local_8c == 0.0) goto LAB_0005b242;
        tmp_i11 = tmp_i11 + 4;
      } while (tmp_i11 != 0x34);
LAB_0005aca2:
      if (local_8c == 1.4013e-45) goto LAB_0005aac0;
      local_8c = 1.4013e-45;
    } while( true );
  }
  tmp_i11 = 0;
  tmp_f1 = local_40 * 0.19;
  tmp_pc9 = "^1ERROR: ^7Unable to retrieve stats!^7";
  tmp_f2 = 0.0;
  do {
    tmp_b10 = *tmp_pc9;
    if ((tmp_b10 == 0) || (0x25 < tmp_i11)) break;
    if ((tmp_b10 == 0x5e) && ((tmp_pc9[1] != 0 && (tmp_pc9[1] != 0x5e)))) {
      tmp_pc9 = tmp_pc9 + 2;
    }
    else {
      tmp_pc9 = tmp_pc9 + 1;
      tmp_i11 = tmp_i11 + 1;
      tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b10 * 0x50 + 0x11114) + tmp_f2;
    }
  } while ((byte *)tmp_pc9 != (byte *)0x0);
  tmp_i11 = 0;
  CG_Text_Paint_Ext_constprop_18
            (320.0 - (float)(int)ROUND((float)GHIDRA_FIELD(cgs, 90372, 4) * tmp_f1 * tmp_f2) * 0.5,
             local_6c + local_74,tmp_f1,tmp_f1,7,0x1100f64);
  tmp_pc9 = "Contact admin@etmods.net if problem persists.^7";
  tmp_f1 = local_40 * 0.19;
  tmp_f2 = 0.0;
  do {
    tmp_b10 = *tmp_pc9;
    if ((tmp_b10 == 0) || (0x2e < tmp_i11)) break;
    if ((tmp_b10 == 0x5e) && ((tmp_pc9[1] != 0 && (tmp_pc9[1] != 0x5e)))) {
      tmp_pc9 = tmp_pc9 + 2;
    }
    else {
      tmp_pc9 = tmp_pc9 + 1;
      tmp_i11 = tmp_i11 + 1;
      tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b10 * 0x50 + 0x11114) + tmp_f2;
    }
  } while ((byte *)tmp_pc9 != (byte *)0x0);
  CG_Text_Paint_Ext_constprop_18
            (320.0 - (float)(int)ROUND((float)GHIDRA_FIELD(cgs, 90372, 4) * tmp_f1 * tmp_f2) * 0.5,
             local_6c + local_74 + local_40 * 10.0,tmp_f1,tmp_f1,7,0x1100f64);
  return 1;
LAB_0005aac0:
  tmp_pb6 = (byte *)va("^7Stats will be updated in %i seconds.^7",
                      (g_unk_010ef1f8 - g_unk_010906e0) / 1000 + 1);
  tmp_f1 = local_40 * 0.2;
  tmp_f4 = local_40 * 15.0;
  tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * tmp_f1;
  if (tmp_pb6 == (byte *)0x0) {
    tmp_f5 = 0.0;
  }
  else {
    tmp_i11 = 0;
    tmp_s7 = strlen((char *)tmp_pb6);
    tmp_f5 = 0.0;
    do {
      tmp_b10 = *tmp_pb6;
      if ((tmp_b10 == 0) || ((int)tmp_s7 <= tmp_i11)) break;
      if ((tmp_b10 == 0x5e) && ((tmp_pb6[1] != 0 && (tmp_pb6[1] != 0x5e)))) {
        tmp_pb6 = tmp_pb6 + 2;
      }
      else {
        tmp_pb6 = tmp_pb6 + 1;
        tmp_i11 = tmp_i11 + 1;
        tmp_f5 = (float)*(int *)(cgs + (uint)tmp_b10 * 0x50 + 0x11114) + tmp_f5;
      }
    } while (tmp_pb6 != (byte *)0x0);
  }
  CG_Text_Paint_Ext_constprop_18
            (320.0 - (float)(int)ROUND(tmp_f5 * tmp_f2) * 0.5,tmp_f3 - tmp_f4,tmp_f1,tmp_f1,7,0x1100f64);
  return 1;
}

void nitrox_LoadPanel_LoadingBar(void)
{
  float tmp_f1;
  int local_14;
  int local_10 [2];
  uint32_t uStack_8;
  
  uStack_8 = 0x8ba56;
  trap_GetHunkData(&local_14,local_10);
  if (0 < local_10[0]) {
    tmp_f1 = (float)local_14 / (float)local_10[0];
    if (tmp_f1 < 0.0) {
      tmp_f1 = 0.0;
    }
    else if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    CG_FilledBar(0x43820000,0x43e50000,0x42f00000,0x41200000,colorMdRed,0,0,tmp_f1,0x50);
    CG_DrawRect_FixedBorder(0x43820000,0x43e50000,0x42f00000,0x41200000,1,colorDkGrey);
  }
  return;
}

void nitrox_ConfigStringModified(void)
{
  char tmp_c1;
  uint16_t tmp_u2;
  char *tmp_pc3;
  uint tmp_u4;
  uint32_t tmp_u5;
  int tmp_i6;
  size_t tmp_s7;
  uint tmp_u8;
  uint tmp_u9;
  uint8_t *tmp_pu10;
  char *__s;
  int *tmp_pi11;
  char *tmp_pc12;
  char *tmp_pc13;
  byte tmp_b14;
  size_t local_876c;
  int local_875c [655];
  char acStack_7d20 [32012];
  uint32_t uStack_14;
  
  tmp_b14 = 0;
  uStack_14 = 0xb4880;
  tmp_pc3 = (char *)CG_Argv(1);
  tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
  if (0x28e < tmp_u4) {
    Com_Error(2,"nitrox_ConfigStringModified; NCS > MAX_NCONFIGSTRINGS");
  }
  tmp_u5 = CG_Argv(2);
  tmp_pc3 = (char *)va("%s",tmp_u5);
  tmp_i6 = strcmp(cgs + *(int *)(cgs + tmp_u4 * 4 + 0x20390f4) + 0x2039b30,tmp_pc3);
  if (tmp_i6 != 0) {
    tmp_i6 = 0x8740;
    tmp_pu10 = cgs + 0x20390f4;
    tmp_pi11 = local_875c;
    if (((uint)local_875c & 4) != 0) {
      local_875c[0] = GHIDRA_FIELD(cgs, 33788148, 4);
      tmp_pi11 = local_875c + 1;
      tmp_i6 = 0x873c;
      tmp_pu10 = cgs + 0x20390f8;
    }
    for (; tmp_i6 != 0; tmp_i6 = tmp_i6 + -1) {
      *(uint8_t *)tmp_pi11 = *tmp_pu10;
      tmp_pu10 = tmp_pu10 + (uint)tmp_b14 * -2 + 1;
      tmp_pi11 = (int *)((int)tmp_pi11 + (uint)tmp_b14 * -2 + 1);
    }
    memset(cgs + 0x20390f4,0,0x8740);
    GHIDRA_FIELD(cgs, 33822768, 4) = 1;
    tmp_u9 = 0;
    do {
      __s = tmp_pc3;
      if (tmp_u9 != tmp_u4) {
        __s = acStack_7d20 + local_875c[tmp_u9];
      }
      if (*__s != '\0') {
        tmp_s7 = strlen(__s);
        tmp_u8 = tmp_s7 + 1;
        if (32000 < (int)(tmp_u8 + GHIDRA_FIELD(cgs, 33822768, 4))) {
          Com_Error(2,"MAX_NGAMESTATE_CHARS exceeded");
        }
        tmp_u5 = GHIDRA_FIELD(cgs, 33822768, 4);
        *(uint32_t *)(cgs + tmp_u9 * 4 + 0x20390f4) = GHIDRA_FIELD(cgs, 33822768, 4);
        tmp_pc12 = cgs + tmp_u5 + 0x2039b30;
        local_876c = tmp_u8;
        if (7 < tmp_u8) {
          if (((uint)tmp_pc12 & 1) != 0) {
            tmp_c1 = *__s;
            __s = __s + 1;
            tmp_pc12 = cgs + tmp_u5 + 0x2039b31;
            cgs[tmp_u5 + 0x2039b30] = tmp_c1;
            local_876c = tmp_s7;
          }
          tmp_pc13 = tmp_pc12;
          if (((uint)tmp_pc12 & 2) != 0) {
            tmp_u2 = *(uint16_t *)__s;
            tmp_pc13 = tmp_pc12 + 2;
            __s = __s + 2;
            *(uint16_t *)tmp_pc12 = tmp_u2;
            local_876c = local_876c - 2;
          }
          tmp_pc12 = tmp_pc13;
          if (((uint)tmp_pc13 & 4) != 0) {
            tmp_u5 = *(uint32_t *)__s;
            tmp_pc12 = tmp_pc13 + 4;
            __s = __s + 4;
            *(uint32_t *)tmp_pc13 = tmp_u5;
            local_876c = local_876c - 4;
          }
        }
        for (; local_876c != 0; local_876c = local_876c - 1) {
          *tmp_pc12 = *__s;
          __s = __s + (uint)tmp_b14 * -2 + 1;
          tmp_pc12 = tmp_pc12 + (uint)tmp_b14 * -2 + 1;
        }
        GHIDRA_FIELD(cgs, 33822768, 4) = GHIDRA_FIELD(cgs, 33822768, 4) + tmp_u8;
      }
      tmp_u9 = tmp_u9 + 1;
    } while (tmp_u9 != 0x28f);
  }
  return;
}

void nitrox_ProcessNewCS(uint param_1)
{
  char *__haystack;
  char *tmp_pc1;
  uint32_t tmp_u2;
  
  __haystack = (char *)nitrox_ConfigString(param_1);
  if (param_1 < 0x100) {
    tmp_u2 = trap_R_RegisterModel(__haystack);
    *(uint32_t *)(cgs + param_1 * 4 + 0x6f48) = tmp_u2;
  }
  else if (param_1 - 0x100 < 0x100) {
    if (*__haystack != '*') {
      tmp_pc1 = strstr(__haystack,".wav");
      if (tmp_pc1 == (char *)0x0) {
        CG_SoundScriptPrecache(__haystack);
      }
      else {
        tmp_u2 = trap_S_RegisterSound(__haystack,0);
        *(uint32_t *)(cgs + param_1 * 4 + 0x7c08) = tmp_u2;
      }
    }
  }
  else if (param_1 - 0x200 < 0x20) {
    if (*__haystack == '*') {
      tmp_u2 = trap_R_RegisterShader(__haystack + 1);
    }
    else {
      tmp_u2 = trap_R_RegisterShaderNoMip(__haystack);
    }
    *(uint32_t *)(cgs + (param_1 - 0x200) * 4 + 0x7b48) = tmp_u2;
    Q_strncpyz((param_1 - 0x33) * 0x40 + 0x10efe68,__haystack + (*__haystack == '*'),0x40);
  }
  else if (param_1 - 0x221 < 0x40) {
    tmp_u2 = trap_R_RegisterSkin(__haystack);
    *(uint32_t *)(cgs + param_1 * 4 + 0x7344) = tmp_u2;
  }
  else {
    if (param_1 - 0x273 < 0x10) {
      CG_ParseSpawns();
      return;
    }
    if (param_1 - 0x261 < 0x12) {
      CG_ParseOIDInfo();
      return;
    }
    if (param_1 - 0x283 < 0xc) {
      CG_ParseFireteams();
    }
    else if (param_1 == 0x220) {
      CG_ShaderStateChanged();
      return;
    }
  }
  return;
}

bool nitrox_NextKey(uint32_t *param_1,char *param_2)
{
  char tmp_c1;
  char *tmp_pc2;
  char *tmp_pc3;
  
  tmp_pc3 = (char *)*param_1;
  tmp_c1 = *tmp_pc3;
  *param_2 = '\0';
  tmp_pc3 = tmp_pc3 + (tmp_c1 == '\\');
  tmp_c1 = *tmp_pc3;
  tmp_pc2 = param_2;
  while ((tmp_c1 != '\0' && (tmp_c1 != '\\'))) {
    tmp_pc3 = tmp_pc3 + 1;
    *tmp_pc2 = tmp_c1;
    tmp_pc2 = tmp_pc2 + 1;
    tmp_c1 = *tmp_pc3;
  }
  *tmp_pc2 = '\0';
  tmp_c1 = *param_2;
  if (tmp_c1 != '\0') {
    *param_1 = tmp_pc3 + 1;
  }
  return tmp_c1 != '\0';
}

void nitrox_ClampFloat(float *param_1,float param_2,float param_3)
{
  float tmp_f1;
  
  tmp_f1 = *param_1;
  if (tmp_f1 < param_2) {
    *param_1 = param_2;
    tmp_f1 = param_2;
  }
  if (param_3 < tmp_f1) {
    *param_1 = param_3;
  }
  return;
}

void nitrox_ClampInt(int *param_1,float param_2,float param_3)
{
  float tmp_f1;
  
  tmp_f1 = (float)*param_1;
  if (tmp_f1 < param_2) {
    *param_1 = (int)ROUND(param_2);
    tmp_f1 = (float)(int)ROUND(param_2);
  }
  if (param_3 < tmp_f1) {
    *param_1 = (int)ROUND(param_3);
  }
  return;
}

void nitrox_stripLeadingSpaces(char *param_1)
{
  char tmp_c1;
  char *tmp_pc2;
  
  tmp_c1 = *param_1;
  tmp_pc2 = param_1;
  while (tmp_c1 == ' ') {
    tmp_pc2 = tmp_pc2 + 1;
    tmp_c1 = *tmp_pc2;
  }
  while (tmp_c1 != '\0') {
    tmp_pc2 = tmp_pc2 + 1;
    *param_1 = tmp_c1;
    param_1 = param_1 + 1;
    tmp_c1 = *tmp_pc2;
  }
  *param_1 = '\0';
  return;
}

void Nit_TDMScore_C(void)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  uint8_t *tmp_pu12;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x103a19;
  local_2c = 0x3f000000;
  local_28 = 0x3f000000;
  local_24 = 0x3f000000;
  local_20 = 0x3f000000;
  tmp_u3 = va("%i",g_unk_01091e8c);
  tmp_u4 = va("%i",g_unk_01091e90);
  tmp_u5 = va("%i",GHIDRA_FIELD(cgs, 33787492, 4));
  tmp_i6 = CG_DrawScoreboard();
  if (tmp_i6 == 0) {
    CG_HudPlacement(0);
    tmp_i7 = CG_Text_Width_Ext(tmp_u3,0x3e4ccccd,0,0x1100f64);
    tmp_i8 = CG_Text_Width_Ext(tmp_u4,0x3e4ccccd,0,0x1100f64);
    tmp_i9 = CG_Text_Width_Ext("Axis",0x3e4ccccd,0,0x1100f64);
    tmp_i10 = CG_Text_Width_Ext("Allies",0x3e4ccccd,0,0x1100f64);
    tmp_i11 = CG_Text_Width_Ext(tmp_u5,0x3e4ccccd,0,0x1100f64);
    tmp_u2 = GHIDRA_FIELD(cgs, 28480, 4);
    tmp_u1 = GHIDRA_FIELD(cgs, 27396, 4);
    tmp_i6 = g_unk_010906e0;
    CG_FillRect(0x43700000,0x420c0000,0x43200000,0x41f00000,&local_2c);
    CG_DrawRect_FixedBorder(0x43700000,0x420c0000,0x43200000,0x420c0000,1,&HUD_Border);
    CG_Text_Paint_Ext(0x437f0000,0x42340000,0x3e4ccccd,0x3e4ccccd,colorMdRed,"Axis",0,0,3,0x1100f64)
    ;
    if (g_unk_010906e0 - g_unk_010ef1e0 < 0x2ee) {
      if (g_unk_010ef1e8 == 0) {
        tmp_pu12 = colorRed;
      }
      else {
        tmp_pu12 = colorGreen;
      }
      CG_Text_Paint_Ext(((float)tmp_i9 * 0.5 + 255.0) - (float)tmp_i7 * 0.5,0x425c0000,0x3e4ccccd,
                        0x3e4ccccd,tmp_pu12,tmp_u3,0,0,3,0x1100f64);
    }
    else {
      CG_Text_Paint_Ext(((float)tmp_i9 * 0.5 + 255.0) - (float)tmp_i7 * 0.5,0x425c0000,0x3e4ccccd,
                        0x3e4ccccd,&colorWhite,tmp_u3,0,0,3,0x1100f64);
    }
    CG_FilledBar(0x43700000,0x42820000,0x42a00000,0x40800000,colorMdRed,0,0,
                 (float)g_unk_01091e8c / (float)(int)GHIDRA_FIELD(cgs, 33787492, 4),0x51);
    CG_Text_Paint_Ext(385.0 - (float)tmp_i10,0x42340000,0x3e4ccccd,0x3e4ccccd,&colorMdBlue,"Allies",0
                      ,0,3,0x1100f64);
    if (g_unk_010906e0 - g_unk_010ef1e4 < 0x2ee) {
      if (g_unk_010ef1ec == 0) {
        tmp_pu12 = colorRed;
      }
      else {
        tmp_pu12 = colorGreen;
      }
      CG_Text_Paint_Ext((385.0 - (float)tmp_i10 * 0.5) - (float)tmp_i8 * 0.5,0x425c0000,0x3e4ccccd,
                        0x3e4ccccd,tmp_pu12,tmp_u4,0,0,3,0x1100f64);
    }
    else {
      CG_Text_Paint_Ext((385.0 - (float)tmp_i10 * 0.5) - (float)tmp_i8 * 0.5,0x425c0000,0x3e4ccccd,
                        0x3e4ccccd,&colorWhite,tmp_u4,0,0,3,0x1100f64);
    }
    CG_FilledBar(0x43a00000,0x42820000,0x42a00000,0x40800000,&colorMdBlue,0,0,
                 (float)g_unk_01091e90 / (float)(int)GHIDRA_FIELD(cgs, 33787492, 4),0x50);
    CG_Text_Paint_Ext(320.0 - (float)tmp_i11 * 0.5,0x42700000,0x3e4ccccd,0x3e4ccccd,&colorWhite,tmp_u5
                      ,0,0,3,0x1100f64);
    if ((GHIDRA_FIELD(cgs, 33525356, 4) == 0) && ((cgs[0x20390d8] & 0x10) != 0)) {
      CG_FilledBar(0x43700000,0x428c0000,0x43200000,0x40800000,colorRed,0,0,
                   (float)(tmp_i6 - tmp_u2) / ((float)tmp_u1 * 60000.0),0x50);
    }
  }
  return;
}

long double Nit_TDMScore_R(float param_1,int param_2)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  
  if (param_2 != 0) {
    CG_HudPlacement(2);
    tmp_u1 = va("^_Axis ^7%d",g_unk_01091e8c);
    tmp_u2 = va("^4Allies ^7%d",g_unk_01091e90);
    tmp_i3 = CG_Text_Width_Ext(tmp_u1,0x3e428f5c,0,0x1100f64);
    tmp_i4 = CG_Text_Width_Ext(tmp_u2,0x3e428f5c,0,0x1100f64);
    CG_FillRect((float)(0x278 - tmp_i3),param_1,(float)(tmp_i3 + 5),0x41600000,&HUD_Background);
    CG_DrawRect_FixedBorder
              ((float)(0x278 - tmp_i3),param_1,(float)(tmp_i3 + 5),0x41600000,1,&HUD_Border);
    CG_Text_Paint_Ext((float)(0x27a - tmp_i3),param_1 + 11.0,0x3e428f5c,0x3e428f5c,HUD_Text,tmp_u1,0,0
                      ,0,0x1100f64);
    CG_FillRect((float)(0x278 - tmp_i4),param_1 + 16.0,(float)(tmp_i4 + 5),0x41600000,&HUD_Background)
    ;
    CG_DrawRect_FixedBorder
              ((float)(0x278 - tmp_i4),param_1 + 16.0,(float)(tmp_i4 + 5),0x41600000,1,&HUD_Border);
    CG_Text_Paint_Ext((float)(0x27a - tmp_i4),param_1 + 27.0,0x3e428f5c,0x3e428f5c,HUD_Text,tmp_u2,0,0
                      ,0,0x1100f64);
  }
  return (long double)param_1 + (long double)28.0 + (long double)4.0;
}

void Nit_SpecMines(int param_1,int param_2)
{
  uint32_t tmp_u1;
  uint8_t tmp_u2;
  double tmp_d3;
  
  tmp_d3 = sin((double)g_unk_010906e0 * 0.001);
  tmp_u1 = trap_R_RegisterShader("nitmod/SpecMines");
  *(float *)(param_2 + 0x70) = *(float *)(param_2 + 0x70) - 2.0;
  *(float *)(param_2 + 0x8c) = *(float *)(param_2 + 0x8c) - 2.0;
  tmp_u2 = (uint8_t)(int)ROUND(255.0 - ABS(tmp_d3) * 255.0);
  if (*(int *)(param_1 + 0x108) % 4 == 1) {
    *(uint8_t *)(param_2 + 0xb4) = 0xff;
    *(uint8_t *)(param_2 + 0xb5) = tmp_u2;
    *(uint8_t *)(param_2 + 0xb6) = tmp_u2;
    *(uint8_t *)(param_2 + 0xb7) = 0xff;
  }
  else {
    *(uint8_t *)(param_2 + 0xb4) = tmp_u2;
    *(uint8_t *)(param_2 + 0xb5) = tmp_u2;
    *(uint8_t *)(param_2 + 0xb6) = 0xff;
    *(uint8_t *)(param_2 + 0xb7) = 0xff;
  }
  *(uint32_t *)(param_2 + 0xb0) = tmp_u1;
  return;
}

void Nit_LiveStats(void)
{
  float tmp_f1;
  int tmp_i2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  size_t tmp_s5;
  int local_28;
  int local_24;
  
  if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95ac) == 0) {
    tmp_i2 = CG_DrawScoreboard();
    if (tmp_i2 == 0) {
      tmp_u3 = BG_GetKillSpree(g_unk_01047b00 + 0x2c);
      tmp_pc4 = (char *)va("^7Spree: ^f%d",tmp_u3);
      tmp_s5 = strlen(tmp_pc4);
      tmp_i2 = CG_Text_Width_Ext(tmp_pc4,0x3e2e147b,tmp_s5,0x110afec);
      if ((cg_HUDFlags[0xc] & 1) == 0) {
        local_28 = 0x270 - tmp_i2;
        local_24 = 0x273 - tmp_i2;
        tmp_u3 = 2;
      }
      else {
        local_24 = 8;
        local_28 = 5;
        tmp_u3 = 1;
      }
      CG_HudPlacement(tmp_u3);
      CG_FillRect((float)local_28,0x43a78000,(float)(tmp_i2 + 10),0x42480000,&HUD_Background);
      CG_DrawRect_FixedBorder
                ((float)local_28,0x43a78000,(float)(tmp_i2 + 10),0x42480000,1,&HUD_Border);
      tmp_f1 = (float)local_24;
      CG_Text_Paint_Ext(tmp_f1,0x43ab8000,0x3e2e147b,0x3e2e147b,&colorWhite,tmp_pc4,0,0,3,0x110afec);
      if (g_unk_010906e0 - g_unk_010ef674 < 100) {
        tmp_pc4 = "2";
      }
      else {
        tmp_pc4 = "f";
      }
      tmp_u3 = va(&g_unk_00121549,tmp_pc4,*(uint32_t *)(g_unk_01047b00 + 0x154));
      CG_Text_Paint_Ext(tmp_f1,0x43b08000,0x3e2e147b,0x3e2e147b,&colorWhite,tmp_u3,0,0,3,0x110afec);
      if (g_unk_010906e0 - g_unk_010ef678 < 100) {
        tmp_pc4 = "2";
      }
      else {
        tmp_pc4 = "f";
      }
      tmp_u3 = va("^7HS: ^%s%d",tmp_pc4,*(uint32_t *)(g_unk_01047b00 + 0x150));
      CG_Text_Paint_Ext(tmp_f1,0x43b58000,0x3e2e147b,0x3e2e147b,&colorWhite,tmp_u3,0,0,3,0x110afec);
      tmp_u3 = va("^7K: ^f%d",*(uint32_t *)(g_unk_01047b00 + 0x148));
      CG_Text_Paint_Ext(tmp_f1,0x43ba8000,0x3e2e147b,0x3e2e147b,&colorWhite,tmp_u3,0,0,3,0x110afec);
      tmp_u3 = va("^7D: ^f%d",*(uint32_t *)(g_unk_01047b00 + 0x14c));
      CG_Text_Paint_Ext(tmp_f1,0x43bf8000,0x3e2e147b,0x3e2e147b,&colorWhite,tmp_u3,0,0,3,0x110afec);
    }
  }
  return;
}

void nitmod_ObjectiveEvent(void)
{
  char *tmp_pc1;
  long tmp_l2;
  long tmp_l3;
  long tmp_l4;
  long tmp_l5;
  long tmp_l6;
  uint32_t tmp_u7;
  uint32_t tmp_u8;
  uint32_t *tmp_pu9;
  uint tmp_u10;
  char tmp_c11;
  int tmp_i12;
  uint8_t *tmp_pu13;
  
  tmp_pc1 = (char *)CG_Argv(1);
  tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(2);
  tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(3);
  tmp_l4 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(4);
  tmp_l5 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(5);
  tmp_l6 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pu9 = &cg;
  tmp_c11 = g_unk_01047ac4 == tmp_l5;
  if (tmp_l2 == 4) {
    tmp_pu13 = cgs;
    tmp_u7 = *(uint32_t *)(PopMsgs + tmp_l3 * 4);
    tmp_u10 = tmp_l4 + 0x261;
    tmp_i12 = tmp_l5 * 0x1a4 + 0x10f9274;
    if (0x28e < tmp_u10) {
      CG_Error("nitrox_ConfigString: bad index: %i",tmp_u10);
    }
    tmp_u8 = Info_ValueForKey(*(int *)(cgs + tmp_u10 * 4 + 0x20390f4) + 0x3129990,&g_unk_0010d2bf);
    tmp_u7 = va("^g%s %s ^7%s",tmp_u8,tmp_u7,tmp_i12);
    if (tmp_c11 == '\0') goto LAB_00104ae0;
    if (tmp_l3 == 3) {
      tmp_pc1 = "Objective Destroyed";
    }
    else {
      if (tmp_l3 == 4) {
        Q_strncpyz(tmp_pu9 + 0x29da2,"Objective Damaged",0x80,tmp_i12,tmp_pu9,tmp_u7);
        tmp_pu9[0x29da1] = 0x5a;
        tmp_pu9[0x29dc6] = 0;
        tmp_pu9[0x29dc2] = 0x3f800000;
        tmp_pu9[0x29dc3] = 0x3f800000;
        tmp_pu9[0x29dc4] = 0x3f800000;
        tmp_pu9[0x29d9f] = 200;
        tmp_pu9[0x29d9e] = tmp_pu9[0x12308] + 200;
        tmp_pu9[0x29da0] = tmp_pu9[0x12308] + 0x578;
        goto LAB_00104ae0;
      }
      if (tmp_l3 != 2) goto LAB_00104ae0;
      tmp_pc1 = "Objective Constructed";
    }
    Q_strncpyz(tmp_pu9 + 0x29da2,tmp_pc1,0x80,tmp_i12,tmp_pu9,tmp_u7);
    tmp_pu9[0x29d9f] = 200;
    tmp_pu9[0x29da1] = 0x5a;
    tmp_pu9[0x29dc6] = 0;
    tmp_pu9[0x29dc2] = 0x3f800000;
    tmp_pu9[0x29dc3] = 0x3f800000;
    tmp_pu9[0x29dc4] = 0x3f800000;
    tmp_pu9[0x29d9e] = tmp_pu9[0x12308] + 200;
    tmp_pu9[0x29da0] = tmp_pu9[0x12308] + 0x578;
LAB_00104ae0:
    CG_AddPMItem(4,tmp_u7,*(uint32_t *)(tmp_pu13 + 0x202c8),0);
    return;
  }
  if (4 < tmp_l2) {
    if (1 < tmp_l2 - 9U) {
      return;
    }
    tmp_u7 = va("%s ^gcaptured the Flag!",tmp_l5 * 0x1a4 + 0x10f9274);
    CG_AddPMItem(tmp_l2,tmp_u7,*(uint32_t *)(cgs + tmp_l2 * 4 + 0x202b8),0);
    return;
  }
  if (tmp_l2 != 0) {
    return;
  }
  tmp_pu13 = cgs;
  tmp_u10 = tmp_l4 + 0x261;
  tmp_i12 = tmp_l5 * 0x1a4 + 0x10f9274;
  if (0x28e < tmp_u10) {
    CG_Error("nitrox_ConfigString: bad index: %i",tmp_u10);
  }
  tmp_u7 = Info_ValueForKey(*(int *)(cgs + tmp_u10 * 4 + 0x20390f4) + 0x3129990,&g_unk_0010d2bf);
  tmp_u7 = va("%s %s ^gby ^7%s",*(uint32_t *)(PopMsgs + tmp_l3 * 4),tmp_u7,tmp_i12);
  if (tmp_c11 != '\0') {
    if (tmp_l3 == 0) {
      Q_strncpyz(tmp_pu9 + 0x29da2,"Dynamite Planted",0x80,tmp_i12,tmp_pu9,tmp_u7);
      tmp_pu9[0x29d9f] = 200;
      tmp_pu9[0x29da1] = 0x5a;
      tmp_pu9[0x29dc6] = 0;
      tmp_pu9[0x29dc2] = 0x3f800000;
      tmp_pu9[0x29dc3] = 0x3f800000;
      tmp_pu9[0x29dc4] = 0x3f800000;
      tmp_pu9[0x29d9e] = tmp_pu9[0x12308] + 200;
      tmp_pu9[0x29da0] = tmp_pu9[0x12308] + 0x578;
      CG_AddPMItem(0,tmp_u7,*(uint32_t *)(tmp_pu13 + 0x202b8),0);
      goto LAB_00104c23;
    }
    if (tmp_l3 == 1) {
      Q_strncpyz(tmp_pu9 + 0x29da2,"Dynamite Defused",0x80,tmp_i12,tmp_pu9,tmp_u7);
      tmp_pu9[0x29d9f] = 200;
      tmp_pu9[0x29dc6] = 0;
      tmp_pu9[0x29dc2] = 0x3f800000;
      tmp_pu9[0x29dc3] = 0x3f800000;
      tmp_pu9[0x29d9e] = tmp_pu9[0x12308] + 200;
      tmp_pu9[0x29da0] = tmp_pu9[0x12308] + 0x578;
      tmp_pu9[0x29da1] = 0x5a;
      tmp_pu9[0x29dc4] = 0x3f800000;
      CG_AddPMItem(0,tmp_u7,*(uint32_t *)(tmp_pu13 + 0x202b8),0);
      goto LAB_001049f5;
    }
  }
  CG_AddPMItem(0,tmp_u7,*(uint32_t *)(tmp_pu13 + 0x202b8),0);
  if (tmp_l3 != 0) {
    if (tmp_l3 != 1) {
      return;
    }
LAB_001049f5:
    if (tmp_l6 == 1) {
      CG_SoundPlaySoundScript("axis_hq_dynamite_defused",0,0xffffffff,1);
    }
    else {
      CG_SoundPlaySoundScript("allies_hq_dynamite_defused",0,0xffffffff,1);
    }
    return;
  }
LAB_00104c23:
  if (tmp_l6 != 1) {
    CG_SoundPlaySoundScript("allies_hq_dynamite_planted",0,0xffffffff,1);
    return;
  }
  CG_SoundPlaySoundScript("axis_hq_dynamite_planted",0,0xffffffff,1);
  return;
}

void Nit_TDMInfo(void)
{
  uint32_t tmp_u1;
  
  if ((GHIDRA_FIELD(cgs, 27388, 4) == 7) && (0 < (int)GHIDRA_FIELD(cgs, 33787492, 4))) {
    CG_Printf("^7N^1!^7tmod: ^3Team Death Match Informations.\n");
    CG_Printf("^5> ^3Score to reach:\n");
    tmp_u1 = GHIDRA_FIELD(cgs, 33787492, 4);
    CG_Printf("- To win the match, your team has to reach %d points.\n",GHIDRA_FIELD(cgs, 33787492, 4));
    CG_Printf("^5> ^3Timelimit rules:\n");
    if ((GHIDRA_FIELD(cgs, 33788120, 4) & 0x10) == 0) {
      CG_Printf("- The map will ^1NOT ^7end as long as the score is not reached.\n",tmp_u1);
    }
    else {
      CG_Printf("- If the timelimit is over, the map will end and the team with most points will win the round.\n"
                ,tmp_u1);
      CG_Printf("- Reaching the score limit before timelimit hits will end the map.\n");
    }
    CG_Printf("^5> ^3Server TDM Options:\n",tmp_u1);
    if ((GHIDRA_FIELD(cgs, 33788120, 4) & 1) == 0) {
      CG_Printf("- Every earned XP counts in the team score.\n");
    }
    else {
      CG_Printf(
               "- Using \'Kill Based Scoring\'. The only way to get points is by killing an enemy (1 point for your team per enemy killed).\n"
               );
    }
    if ((GHIDRA_FIELD(cgs, 33788120, 4) & 4) != 0) {
      CG_Printf("- Artillery support is disabled.\n");
    }
    if ((GHIDRA_FIELD(cgs, 33788120, 4) & 8) != 0) {
      CG_Printf("- Intermission map voting is enabled.\n");
    }
    CG_Printf(
             "- Objective: Completing the final objective will ^1NOT ^7end the match. Depending on server settings, the winning team will earn ^2Bonus Points!^7.\n"
             );
    return;
  }
  return;
}

int nitmod_DMTeamScoreboard(int param_1,int param_2,float param_3,uint param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint tmp_u7;
  uint32_t *tmp_pu8;
  int tmp_i9;
  int local_5c;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x105899;
  local_2c = 0x3f19999a;
  local_28 = 0x3f19999a;
  local_24 = 0x3f19999a;
  local_20 = 0x3f800000;
  tmp_u4 = Info_ValueForKey(CachedServerInfo,"sv_hostname");
  tmp_f1 = (float)(param_2 + -2);
  tmp_f2 = (float)(param_1 + -5);
  CG_FillRect(tmp_f2,tmp_f1,0x44188000,0x41a80000,clrUiBack);
  CG_FillRect(tmp_f2,tmp_f1,0x44188000,0x41a80000,clrUiBar);
  local_3c = 0;
  local_30 = param_3;
  local_38 = 0;
  local_34 = 0;
  CG_DrawRect_FixedBorder(tmp_f2,tmp_f1,0x44188000,0x41a80000,1,&colorBlack);
  tmp_f1 = (float)param_1;
  CG_Text_Paint_Ext(tmp_f1,(float)(param_2 + 0xd),0x3e800000,0x3e800000,&local_2c,
                    "^1Death Match ^f- ^1Free For All^7",0,0,0,0x1100f64);
  tmp_i5 = CG_DrawStrlen(tmp_u4);
  tmp_i9 = param_2 + 0x13;
  CG_Text_Paint_Ext((float)(tmp_i5 * -8 + 0x267),(float)(param_2 + 0xd),0x3e800000,0x3e800000,
                    &local_2c,tmp_u4,0,0,0,0x1100f64);
  CG_FillRect(tmp_f2,(float)tmp_i9,0x44188000,0x41900000,clrUiBack);
  trap_R_SetColor(&colorBlack);
  CG_DrawBottom_NoScale(tmp_f2,(float)tmp_i9,0x44188000,0x41900000,0x3f800000);
  trap_R_SetColor(0);
  CG_DrawSmallString((int)ROUND(tmp_f1),tmp_i9,"Name",param_3);
  CG_DrawSmallString((int)ROUND(tmp_f1 + 210.0),tmp_i9,&g_unk_0011ccf0,param_3);
  tmp_f1 = tmp_f1 + 210.0 + 100.0;
  CG_DrawSmallString((int)ROUND(tmp_f1 + 8.0),tmp_i9,"XP",param_3);
  CG_DrawSmallString((int)ROUND(tmp_f1 + 260.0),tmp_i9,"Ping",param_3);
  local_5c = param_2 + 0x25;
  tmp_f1 = (float)local_5c;
  if (0 < (int)param_4) {
    tmp_u7 = 0;
    tmp_f3 = tmp_f1;
    while( true ) {
      if ((tmp_u7 & 1) == 0) {
        local_3c = 0x3ea0a0a1;
        local_38 = 0x3ea0a0a1;
        local_34 = 0x3ea0a0a1;
      }
      else {
        local_3c = 0;
        local_38 = 0;
        local_34 = 0;
      }
      tmp_u7 = tmp_u7 + 1;
      local_30 = param_3 * 0.3;
      CG_FillRect(tmp_f2,tmp_f3,0x44188000,0x41800000,&local_3c);
      trap_R_SetColor(&colorBlack);
      CG_DrawBottom_NoScale(tmp_f2,tmp_f3,0x44188000,0x41800000,0x3f800000);
      trap_R_SetColor(0);
      local_5c = local_5c + 0x10;
      if (tmp_u7 == param_4) break;
      tmp_f3 = (float)local_5c;
    }
  }
  local_3c = 0x3f800000;
  local_38 = 0x3f800000;
  local_34 = 0x3f800000;
  tmp_i9 = (int)ROUND(tmp_f1);
  local_30 = param_3;
  if (0 < g_unk_01091e84) {
    tmp_i6 = 0;
    tmp_pu8 = &g_unk_01091ea4;
    tmp_i5 = tmp_i9;
    do {
      tmp_i6 = tmp_i6 + 1;
      tmp_i9 = tmp_i5 + 0x10;
      WM_DrawClientScoreDM(param_1,tmp_i5,tmp_pu8,&local_3c,param_3);
      tmp_pu8 = tmp_pu8 + 10;
      tmp_i5 = tmp_i9;
    } while (tmp_i6 < g_unk_01091e84);
  }
  return tmp_i9;
}

void nitmod_GetSimpleCS(void)
{
  char *tmp_pc1;
  
  tmp_pc1 = (char *)CG_Argv(1);
  GHIDRA_FIELD(cgs, 33785376, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(2);
  GHIDRA_FIELD(cgs, 33788116, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(3);
  GHIDRA_FIELD(cgs, 33787756, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(4);
  GHIDRA_FIELD(cgs, 33787760, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(5);
  g_unk_010aabf8 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(6);
  GHIDRA_FIELD(cgs, 33787772, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(7);
  _DAT_010ef1dc = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(8);
  GHIDRA_FIELD(cgs, 33788132, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(9);
  GHIDRA_FIELD(cgs, 33788144, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(10);
  GHIDRA_FIELD(cgs, 33788136, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(0xb);
  GHIDRA_FIELD(cgs, 33788140, 4) = strtol(tmp_pc1,(char **)0x0,10);
  return;
}

void nitmod_ClientCheck(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  uint tmp_u4;
  uint32_t tmp_u5;
  uint *tmp_pu6;
  uint *tmp_pu7;
  uint8_t *tmp_pu8;
  char *tmp_pc9;
  uint8_t *tmp_pu10;
  uint8_t local_63 [7];
  uint local_5c [18];
  uint32_t uStack_14;
  
  tmp_u5 = CachedServerInfo;
  uStack_14 = 0x106693;
  local_63[0] = 0;
  Q_strcat(local_63,7,&g_unk_0010d2e7);
  Q_strcat(local_63,7,"i");
  Q_strcat(local_63,7,&g_unk_0010d2bf);
  Q_strcat(local_63,7,&g_unk_00113436);
  Q_strcat(local_63,7,&g_unk_00120a20);
  Q_strcat(local_63,7,"d");
  tmp_u1 = Info_ValueForKey(tmp_u5,"gamename");
  tmp_i2 = Q_stricmp(tmp_u1,local_63);
  if (tmp_i2 != 0) {
LAB_001068a0:
    trap_SendConsoleCommand("disconnect");
    return;
  }
  trap_Cvar_VariableStringBuffer("fs_game",local_5c,0x40);
  tmp_i2 = Q_stricmp(local_5c,local_63);
  if (tmp_i2 != 0) goto LAB_001068a0;
  if ((n_guid[0x10] == '\0') || (tmp_i2 = checkGuid(0x1046e70), tmp_i2 == 0)) {
    nitrox_ReadNKey();
  }
  trap_Cvar_VariableStringBuffer(&g_unk_00115a05,local_5c,0x40);
  tmp_pu7 = local_5c;
  if ((char)local_5c[0] != '\0') {
    do {
      tmp_pu6 = tmp_pu7;
      tmp_u3 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
      tmp_u4 = tmp_u3 & 0x80808080;
      tmp_pu7 = tmp_pu6 + 1;
    } while (tmp_u4 == 0);
    if ((tmp_u3 & 0x8080) == 0) {
      tmp_pu7 = (uint *)((int)tmp_pu6 + 6);
      tmp_u4 = tmp_u4 >> 0x10;
    }
    if (0x10 < (int)tmp_pu7 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_5c))
    goto LAB_0010680f;
  }
  GetMacAddress();
LAB_0010680f:
  tmp_pu10 = &g_unk_00121675;
  tmp_u1 = Info_ValueForKey(tmp_u5,"mod_build");
  tmp_u5 = Info_ValueForKey(tmp_u5,"mod_version");
  CG_Printf("^gServer: ^7N^1!^7tmod ^3%s ^g(%s) + ^9Nx^7AC %s\n",tmp_u5,tmp_u1,&g_unk_00121675);
  tmp_pc9 = "linux-i386";
  tmp_pu8 = &g_unk_00116f02;
  CG_Printf("^gClient: ^7N^1!^7tmod ^3%s ^g(%s) + ^9Nx^7AC %s\n",&g_unk_00116f02,"linux-i386",
            &g_unk_00121675);
  if (GHIDRA_FIELD(cgs, 27388, 4) == 7) {
    CG_Printf("^7N^1!^7tmod: ^gDetected Team Death Match server, type ^2/tdminfo ^gfor further informations.\n"
              ,tmp_pu8,tmp_pc9,tmp_pu10);
  }
  trap_SendClientCommand("imhere");
  return;
}

void nitmod_AddKillPrint(void)
{
  g_unk_010ef0d4 = 0x73a;
  g_unk_010ef0d0 = g_unk_010906e0 + 0x73a;
  return;
}

void nitmod_DrawKillPrint(void)
{
  float tmp_f1;
  double tmp_d2;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  float local_10;
  
  if ((g_unk_010ef0d0 != 0) && (g_unk_010906e0 - g_unk_010ef0d0 <= g_unk_010ef0d4)) {
    CG_HudPlacement(0);
    local_10 = (float)(g_unk_010ef0d0 - g_unk_010906e0) / (float)g_unk_010ef0d4;
    if (0.0 < local_10) {
      local_1c = colorWhite;
      local_18 = g_unk_0014a334;
      local_14 = g_unk_0014a338;
      tmp_d2 = sin((double)(local_10 * 1.1));
      tmp_f1 = ((float)tmp_d2 + 0.7) * 0.2;
      CG_Text_Paint_Centred_Ext
                (0x43a00000,0x42f00000,tmp_f1,tmp_f1,&local_1c,&g_unk_010ef0d8,0,0,3,0x1100f64);
    }
    else {
      g_unk_010ef0d0 = 0;
    }
  }
  return;
}

void nitmod_AddSpreePrint(void)
{
  uint32_t tmp_u1;
  
  if (g_unk_010ef124 != 4) {
    g_unk_010ef118 = g_unk_010906e0 + 0x109a;
    g_unk_010ef11c = 0x109a;
  }
  if (*(int *)(cgs + g_unk_010ef120 * 0x1a4 + 0x940c) == 0) {
    return;
  }
  if (cgs[g_unk_010ef120 * 0x1a4 + 0x9414] == '\0') {
    return;
  }
  switch(g_unk_010ef124) {
  default:
    goto _L275;
  case 1:
    CG_Printf("^2>>> ^7%s^7:%s <<<^7\n",g_unk_010ef120 * 0x1a4 + 0x10f9274,
              *(uint32_t *)(KSpreeMsg + GHIDRA_FIELD(cgs, 33787768, 4) * 4));
    tmp_u1 = *(uint32_t *)(cgs + GHIDRA_FIELD(cgs, 33787768, 4) * 4 + 0x204ec);
    break;
  case 2:
    CG_Printf("^1>>> ^7%s^7:%s <<<^7\n",g_unk_010ef120 * 0x1a4 + 0x10f9274,
              *(uint32_t *)(LSpreeMsg + GHIDRA_FIELD(cgs, 33787768, 4) * 4));
    return;
  case 3:
    CG_Printf("^f>>> ^7%s^7:%s <<<^7\n",g_unk_010ef120 * 0x1a4 + 0x10f9274,
              *(uint32_t *)(MKName + GHIDRA_FIELD(cgs, 33787768, 4) * 4));
    tmp_u1 = *(uint32_t *)(cgs + GHIDRA_FIELD(cgs, 33787768, 4) * 4 + 0x204d8);
    break;
  case 4:
    tmp_u1 = va("^f>>> ^7%s ^gis on a revive spree ! (^8%d^g) ^f<<<",g_unk_010ef120 * 0x1a4 + 0x10f9274
               ,GHIDRA_FIELD(cgs, 33787768, 4));
    CG_AddToTeamChat(tmp_u1,0xffffffff);
    CG_Printf(&g_unk_00121ff9,tmp_u1);
    return;
  case 5:
    CG_Printf("^f>>> ^7%s^7:%s <<<^7\n",g_unk_010ef120 * 0x1a4 + 0x10f9274,
              *(uint32_t *)(MRName + GHIDRA_FIELD(cgs, 33787768, 4) * 4));
    tmp_u1 = *(uint32_t *)(cgs + GHIDRA_FIELD(cgs, 33787768, 4) * 4 + 0x20518);
  }
  trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),0,tmp_u1);
_L275:
  return;
}

void nitmod_SpreePrint(void)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  float tmp_f4;
  uint32_t tmp_u5;
  int tmp_i6;
  double tmp_d7;
  
  if (g_unk_010ef118 <= g_unk_010906e0) {
    return;
  }
  if (*(int *)(cgs + g_unk_010ef120 * 0x1a4 + 0x940c) == 0) {
    return;
  }
  if (cgs[g_unk_010ef120 * 0x1a4 + 0x9414] == '\0') {
    return;
  }
  tmp_i6 = g_unk_010ef118 - g_unk_010906e0;
  tmp_d7 = sin((double)((float)g_unk_010906e0 / 150.0));
  tmp_f4 = ((float)tmp_i6 / (float)g_unk_010ef11c + 0.5 + (float)tmp_d7 * 0.5) * 0.1;
  CG_HudPlacement(2);
  if (((cg_HUDFlags[0xc] & 8) == 0) && (g_unk_010ef260 == 0)) {
    tmp_u1 = 0x41c80000;
    tmp_u2 = 0x41700000;
    tmp_u3 = 0x44020000;
  }
  else {
    CG_HudPlacement(1);
    tmp_u1 = 0x43520000;
    tmp_u2 = 0x43480000;
    tmp_u3 = 0x41200000;
  }
  if (g_unk_010ef124 == 2) {
    tmp_u5 = *(uint32_t *)(LSpreeMsg + GHIDRA_FIELD(cgs, 33787768, 4) * 4);
  }
  else if (g_unk_010ef124 < 3) {
    if (g_unk_010ef124 != 1) goto LAB_00106e07;
    tmp_u5 = *(uint32_t *)(KSpreeMsg + GHIDRA_FIELD(cgs, 33787768, 4) * 4);
  }
  else {
    if (g_unk_010ef124 != 3) {
      if (g_unk_010ef124 == 5) {
        tmp_f4 = tmp_f4 + 0.1;
        CG_Text_Paint_Ext(tmp_u3,tmp_u2,tmp_f4,tmp_f4,&colorWhite,
                          *(uint32_t *)(MRName + GHIDRA_FIELD(cgs, 33787768, 4) * 4),0,0,3,0x1100f64);
      }
      goto LAB_00106e07;
    }
    tmp_u5 = *(uint32_t *)(MKName + GHIDRA_FIELD(cgs, 33787768, 4) * 4);
  }
  tmp_f4 = tmp_f4 + 0.1;
  CG_Text_Paint_Ext(tmp_u3,tmp_u2,tmp_f4,tmp_f4,&colorWhite,tmp_u5,0,0,3,0x1100f64);
LAB_00106e07:
  CG_Text_Paint_Ext(tmp_u3,tmp_u1,0x3e4ccccd,0x3e4ccccd,&colorWhite,g_unk_010ef120 * 0x1a4 + 0x10f9274,0
                    ,0x10,3,0x1100f64);
  return;
}

void nitmod_GetMapEndStats(void)
{
  char *tmp_pc1;
  long tmp_l2;
  long tmp_l3;
  long tmp_l4;
  long tmp_l5;
  long tmp_l6;
  uint32_t tmp_u7;
  uint32_t tmp_u8;
  
  tmp_pc1 = (char *)CG_Argv(5);
  tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(4);
  tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(3);
  tmp_l4 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(2);
  tmp_l5 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(1);
  tmp_l6 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_u7 = BG_ClassnameForNumber(*(uint32_t *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94b8));
  tmp_u8 = CG_TeamnameForNumber(*(uint32_t *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494));
  tmp_u7 = va("Map: %s ^2| ^7Team: %s ^2| ^7Class: ^7%s\nBodyshots: ^2%d\n^7Headshots: ^2%d\n^7Kills: ^2%d\n^7Deaths: ^2%d\n^7Revives: ^2%d^7\n"
             ,0x10f69ac,tmp_u8,tmp_u7,tmp_l6,tmp_l5,tmp_l4,tmp_l3,tmp_l2);
  CG_Printf(tmp_u7);
  return;
}

void nitrox_AddSpecialPrint
               (int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6)

{
  if (param_1 != 0) {
    Q_strncpyz(&g_unk_010ef148,param_1,0x80);
    g_unk_010ef13c = 200;
    g_unk_010ef138 = g_unk_010906e0 + 200;
    g_unk_010ef140 = g_unk_010906e0 + 0x578;
    g_unk_010ef1c8 = param_2;
    g_unk_010ef144 = param_5;
    g_unk_010ef1cc = param_3;
    g_unk_010ef1d0 = param_4;
    g_unk_010ef1d8 = param_6;
  }
  return;
}

void nitrox_DrawSpecialPrint(void)
{
  float tmp_f1;
  uint32_t tmp_u2;
  uint8_t *tmp_pu3;
  
  if (g_unk_010906e0 < g_unk_010ef140) {
    CG_HudPlacement(0);
    tmp_f1 = (float)(g_unk_010ef138 - g_unk_010906e0) / (float)g_unk_010ef13c;
    g_unk_010ef1d4 = -tmp_f1;
    if (0.28 < tmp_f1) {
      CG_Text_Paint_Centred_Ext
                (0x43a00000,(float)g_unk_010ef144,tmp_f1,tmp_f1,&g_unk_010ef1c8,&g_unk_010ef148,0,0,3,
                 0x1100f64);
      if (tmp_f1 != 0.28) {
        return;
      }
    }
    else {
      g_unk_010ef1d4 = 0.7;
      CG_Text_Paint_Centred_Ext
                (0x43a00000,(float)g_unk_010ef144,0x3e8f5c29,0x3e8f5c29,&g_unk_010ef1c8,&g_unk_010ef148,0,
                 0,3,0x1100f64);
    }
    if (g_unk_010ef1d8 != 0) {
      tmp_pu3 = &g_unk_001169a9;
      if (g_unk_010ef1d8 < 1) {
        tmp_pu3 = &g_unk_0011d841;
      }
      tmp_u2 = va("%s%iXP",tmp_pu3,g_unk_010ef1d8);
      CG_Text_Paint_Centred_Ext
                (0x43a00000,(float)(g_unk_010ef144 + 10),0x3e4ccccd,0x3e4ccccd,&g_unk_010ef1c8,tmp_u2,0,0
                 ,3,0x1100f64);
      return;
    }
  }
  else {
    g_unk_010ef148 = 0;
    g_unk_010ef1d8 = 0;
  }
  return;
}

void nitmod_ParseNCS(void)
{
  char *tmp_pc1;
  long tmp_l2;
  double tmp_d3;
  
  tmp_pc1 = (char *)CG_Argv(1);
  tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
  GHIDRA_FIELD(cgs, 33785388, 4) = (float)tmp_l2 * 0.01;
  tmp_pc1 = (char *)CG_Argv(2);
  GHIDRA_FIELD(cgs, 33785392, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(3);
  GHIDRA_FIELD(cgs, 33785396, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(4);
  GHIDRA_FIELD(cgs, 33785400, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(5);
  GHIDRA_FIELD(cgs, 33785404, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(6);
  GHIDRA_FIELD(cgs, 33785408, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(7);
  GHIDRA_FIELD(cgs, 33787480, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(8);
  GHIDRA_FIELD(cgs, 33785384, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(9);
  GHIDRA_FIELD(cgs, 33785412, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(10);
  GHIDRA_FIELD(cgs, 33785416, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(0xb);
  GHIDRA_FIELD(cgs, 33785420, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(0xc);
  GHIDRA_FIELD(cgs, 33785424, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(0xd);
  GHIDRA_FIELD(cgs, 33785428, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(0xe);
  GHIDRA_FIELD(cgs, 33787496, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(0xf);
  tmp_d3 = strtod(tmp_pc1,(char **)0x0);
  GHIDRA_FIELD(cgs, 33785380, 4) = (uint32_t)tmp_d3;
  tmp_pc1 = (char *)CG_Argv(0x10);
  GHIDRA_FIELD(cgs, 33788120, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(0x11);
  GHIDRA_FIELD(cgs, 33788124, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(0x12);
  GHIDRA_FIELD(cgs, 33788128, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(0x13);
  GHIDRA_FIELD(cgs, 33787484, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(0x14);
  GHIDRA_FIELD(cgs, 33787488, 4) = strtol(tmp_pc1,(char **)0x0,10);
  return;
}

void nitrox_ParseChargeTimes(void)
{
  char *tmp_pc1;
  
  tmp_pc1 = (char *)CG_Argv(1);
  g_unk_010b3b04 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(2);
  g_unk_010b3b08 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(3);
  g_unk_010b3b14 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(4);
  g_unk_010b3b18 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(5);
  g_unk_010b3b0c = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(6);
  g_unk_010b3b10 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(7);
  g_unk_010b3afc = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(8);
  g_unk_010b3b00 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(9);
  g_unk_010b3b1c = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(10);
  g_unk_010b3b20 = strtol(tmp_pc1,(char **)0x0,10);
  return;
}

int nitrox_ConfigString(uint param_1)
{
  if (0x28e < param_1) {
    CG_Error("nitrox_ConfigString: bad index: %i",param_1);
  }
  return *(int *)(cgs + param_1 * 4 + 0x20390f4) + 0x3129990;
}

void nitmod_DrawObjectiveHint(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  float tmp_f4;
  uint tmp_u5;
  int tmp_i6;
  long double tmp_l7;
  double tmp_d8;
  float local_200;
  float local_1fc;
  float local_1f8;
  uint local_1f4 [26];
  float local_18c;
  float local_188;
  float local_184;
  uint32_t local_144;
  uint8_t local_140;
  uint8_t local_13e;
  byte local_13d;
  uint32_t local_130;
  uint local_108 [26];
  float local_a0;
  float local_9c;
  float local_98;
  uint32_t local_58;
  uint8_t local_54;
  uint8_t local_53;
  uint8_t local_52;
  byte local_51;
  uint32_t local_44;
  
  tmp_i6 = g_unk_01047b00;
  if ((((GHIDRA_FIELD(cg_draw2D, 12, 4) != 0) && (GHIDRA_FIELD(cg_objectiveHints, 12, 4) != 0)) &&
      (tmp_i1 = *(int *)(g_unk_01047b00 + 0x158), tmp_i1 != 3)) &&
     (tmp_i2 = *(int *)(param_1 + 0x108), tmp_i2 != 0)) {
    tmp_u5 = 0;
    do {
      *(uint32_t *)((int)local_1f4 + tmp_u5) = 0;
      *(uint32_t *)((int)local_1f4 + tmp_u5 + 4) = 0;
      tmp_u5 = tmp_u5 + 8;
    } while (tmp_u5 < 0xe8);
    *(uint32_t *)((int)local_1f4 + tmp_u5) = 0;
    tmp_u5 = 0;
    do {
      *(uint32_t *)((int)local_108 + tmp_u5) = 0;
      *(uint32_t *)((int)local_108 + tmp_u5 + 4) = 0;
      tmp_u5 = tmp_u5 + 8;
    } while (tmp_u5 < 0xe8);
    local_1f4[0] = 2;
    local_130 = 0x41200000;
    *(uint32_t *)((int)local_108 + tmp_u5) = 0;
    local_144 = GHIDRA_FIELD(cgs, 131992, 4);
    tmp_d8 = sin((double)((float)g_unk_010906e0 / 250.0));
    local_13d = (byte)(short)ROUND((0.8 - tmp_d8 * 0.5) * 130.0);
    tmp_i3 = *(int *)(cgs + *(int *)(tmp_i6 + 0xcc) * 0x1a4 + 0x9494);
    if (tmp_i3 == 2) {
      local_13e = 0xff;
    }
    else if (tmp_i3 == 1) {
      local_140 = 0xff;
    }
    if (*(int *)(cgs + *(int *)(tmp_i6 + 0xcc) * 0x1a4 + 0x94b8) == 2) {
      if (*(int *)(param_1 + 4) == 0x1f) {
        local_58 = GHIDRA_FIELD(cgs, 131980, 4);
        if ((tmp_i2 != 3) && (tmp_i1 != tmp_i2)) {
          return;
        }
      }
      else if (*(int *)(param_1 + 4) == 0xd) {
        local_58 = GHIDRA_FIELD(cgs, 68196, 4);
        if (tmp_i3 == 1) {
          if (tmp_i2 == 1) {
            return;
          }
        }
        else if ((tmp_i3 == 2) && (tmp_i2 == 2)) {
          return;
        }
      }
      tmp_i6 = trap_R_inPVS(g_unk_010afbcc + 0x18,param_1 + 0x18);
      if (tmp_i6 != 0) {
        local_108[0] = 2;
        local_52 = 0xff;
        local_54 = 0xff;
        local_53 = 0xff;
        tmp_f4 = (float)g_unk_010906e0;
        local_44 = 0x41800000;
        tmp_d8 = sin((double)(tmp_f4 / 250.0));
        local_51 = (byte)(short)ROUND((0.8 - tmp_d8 * 0.5) * 130.0);
        local_18c = *(float *)(param_1 + 0x18);
        local_188 = *(float *)(param_1 + 0x1c);
        tmp_d8 = sin((double)(tmp_f4 / 250.0));
        local_184 = (float)((int)ROUND((tmp_d8 * 0.5 + 0.5) * 10.0) + 0x32) +
                    *(float *)(param_1 + 0x20);
        AngleVectors(&g_unk_01091a54,0,&local_200,0);
        local_18c = local_200 * 0.0 + local_18c;
        local_188 = local_1fc * 0.0 + local_188;
        local_184 = local_1f8 * 0.0 + local_184;
        local_98 = local_184 + 24.0;
        local_a0 = local_18c;
        local_9c = local_188;
        tmp_l7 = (long double)Distance(&g_unk_01090710,&local_18c);
        if ((long double)784.0 <= tmp_l7) {
          if ((long double)2304.0 <= tmp_l7) {
            local_1f4[1] = 0;
            local_108[1] = 0;
            trap_R_AddRefEntityToScene(local_108);
          }
          else {
            local_108[1] = local_108[1] | 8;
            trap_R_AddRefEntityToScene(local_108);
          }
        }
        else {
          local_1f4[1] = local_1f4[1] | 8;
          local_108[1] = local_108[1] | 8;
          if (tmp_l7 < (long double)256.0) {
            tmp_d8 = sin((double)((float)g_unk_010906e0 / 100.0));
            tmp_d8 = 0.5 - tmp_d8 * 0.5;
            local_13d = (byte)(short)ROUND((double)local_13d * tmp_d8);
            local_51 = (byte)(short)ROUND((double)local_51 * tmp_d8);
          }
          trap_R_AddRefEntityToScene(local_1f4);
          trap_R_AddRefEntityToScene(local_108);
        }
      }
    }
  }
  return;
}

void nitmod_DrawArtilleryHint(void)
{
  double tmp_d1;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  float local_10;
  
  local_1c = 0x3f800000;
  local_18 = 0x3f800000;
  local_14 = 0x3f800000;
  local_10 = 0.5;
  if ((GHIDRA_FIELD(cg_artilleryHints, 12, 4) != 0) && (g_unk_010ef66c != 0)) {
    CG_HudPlacement(0);
    tmp_d1 = sin((double)g_unk_010906e0 / (double)g_unk_010ef670);
    local_10 = ((float)tmp_d1 * 0.5 + 0.5) * local_10;
    trap_R_SetColor(&local_1c);
    CG_DrawPic(0x43970000,0x43a00000,0x42100000,0x42100000,GHIDRA_FIELD(cgs, 131976, 4));
    trap_R_SetColor(0);
    g_unk_010ef66c = 0;
    return;
  }
  return;
}

void nitmod_CheckArtilleryHint(int param_1)
{
  long double tmp_l1;
  
  if ((((GHIDRA_FIELD(cg_draw2D, 12, 4) != 0) && (GHIDRA_FIELD(cg_artilleryHints, 12, 4) != 0)) &&
      (*(int *)(g_unk_01047b00 + 0x158) != 3)) &&
     (*(int *)(param_1 + 0x108) == *(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494)))
  {
    tmp_l1 = (long double)Distance(&g_unk_01090710,param_1 + 0x18);
    if ((long double)576.0 <= tmp_l1) {
      g_unk_010ef66c = 0;
      g_unk_010ef670 = 0;
    }
    else {
      g_unk_010ef66c = g_unk_010906e0;
      g_unk_010ef670 = 0x96;
      if ((long double)400.0 <= tmp_l1) {
        g_unk_010ef670 = 300;
      }
    }
  }
  return;
}

void MD5Print(byte *param_1)
{
  byte *tmp_pb1;
  uint tmp_u2;
  
  CG_Printf(&g_unk_001216cc);
  tmp_pb1 = param_1 + 0x10;
  do {
    tmp_u2 = (uint)*param_1;
    param_1 = param_1 + 1;
    CG_Printf(&g_unk_001216d0,tmp_u2);
  } while (param_1 != tmp_pb1);
  CG_Printf(&g_unk_001216d5,tmp_u2);
  return;
}

void MD5toStr(byte *param_1,char *param_2)
{
  byte tmp_b1;
  char *__s;
  char *tmp_pc2;
  
  __s = param_2;
  do {
    tmp_b1 = *param_1;
    param_1 = param_1 + 1;
    tmp_pc2 = __s + 2;
    sprintf(__s,"%02x",(uint)tmp_b1);
    __s = tmp_pc2;
  } while (tmp_pc2 != param_2 + 0x20);
  return;
}

void nitrox_OpenCrashLog(void)
{
  time_t *ptVar1;
  uint tmp_u2;
  time_t tVar3;
  tm *__tp;
  uint8_t *tmp_pu4;
  time_t local_74 [27];
  
  tmp_u2 = 0;
  local_74[0x1a] = 0x10835b;
  local_74[1] = 0;
  do {
    *(uint32_t *)((int)local_74 + tmp_u2 + 8) = 0;
    *(uint32_t *)((int)local_74 + tmp_u2 + 0xc) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x60);
  tVar3 = time(local_74);
  tmp_pu4 = &g_unk_0011d841;
  if (tVar3 != 0) {
    __tp = localtime(local_74);
    tmp_pu4 = tstr_11942;
    strftime(tstr_11942,0x32,"%m-%d-%y_%H-%M-%S",__tp);
  }
  ptVar1 = local_74 + 1;
  Com_sprintf(ptVar1,100,"crash_%s.log",tmp_pu4);
  trap_FS_FOpenFile(ptVar1,&crashLog,3);
  if (crashLog == 0) {
    CG_Printf("^3WARNING: Couldn\'t open crashlog: %s\n",ptVar1);
  }
  return;
}

void nitrox_CloseCrashLog(void)
{
  if (crashLog != 0) {
    trap_FS_FCloseFile(crashLog);
    crashLog = 0;
  }
  return;
}

void Crash_Printf(char *param_1)
{
  uint tmp_u1;
  uint tmp_u2;
  uint *tmp_pu3;
  uint *tmp_pu4;
  uint local_40c [256];
  
  vsnprintf((char *)local_40c,0x400,param_1,&stack0x00000008);
  tmp_pu4 = local_40c;
  if (crashLog != 0) {
    do {
      tmp_pu3 = tmp_pu4;
      tmp_u1 = *tmp_pu3 + 0xfefefeff & ~*tmp_pu3;
      tmp_u2 = tmp_u1 & 0x80808080;
      tmp_pu4 = tmp_pu3 + 1;
    } while (tmp_u2 == 0);
    if ((tmp_u1 & 0x8080) == 0) {
      tmp_pu4 = (uint *)((int)tmp_pu3 + 6);
      tmp_u2 = tmp_u2 >> 0x10;
    }
    trap_FS_Write(local_40c,
                  (char *)((int)tmp_pu4 +
                          ((-3 - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) - (int)local_40c)),crashLog)
    ;
  }
  trap_Print(local_40c);
  return;
}

void installcrashhandler(void)
{
  uint tmp_u1;
  uint tmp_u2;
  _union_1051 local_98;
  sigset_t local_94;
  uint32_t local_14;
  
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)&local_98 + tmp_u2) = 0;
    *(uint32_t *)((int)local_94.__val + tmp_u2) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0x88);
  *(uint32_t *)((int)&local_98 + tmp_u2 + 8) = 0;
  memset(oldact,0,0x238c);
  local_98.sa_handler = CrashHandler;
  sigemptyset(&local_94);
  local_14 = 4;
  sigaction(0xb,(sigaction *)&local_98,(sigaction *)(oldact + 0x604));
  sigaction(4,(sigaction *)&local_98,(sigaction *)(oldact + 0x230));
  sigaction(8,(sigaction *)&local_98,(sigaction *)(oldact + 0x460));
  sigaction(7,(sigaction *)&local_98,(sigaction *)(oldact + 0x3d4));
  return;
}

void restorecrashhandler(void)
{
  sigaction(0xb,(sigaction *)(oldact + 0x604),(sigaction *)0x0);
  return;
}

void installinthandler(void)
{
  signal(2,INTHandler);
  return;
}

void EnableStackTrace(void)
{
  uint tmp_u1;
  uint tmp_u2;
  _union_1051 local_98;
  sigset_t local_94;
  uint32_t local_14;
  
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)&local_98 + tmp_u2) = 0;
    *(uint32_t *)((int)local_94.__val + tmp_u2) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0x88);
  *(uint32_t *)((int)&local_98 + tmp_u2 + 8) = 0;
  memset(oldact,0,0x238c);
  local_98.sa_handler = CrashHandler;
  sigemptyset(&local_94);
  local_14 = 4;
  sigaction(0xb,(sigaction *)&local_98,(sigaction *)(oldact + 0x604));
  sigaction(4,(sigaction *)&local_98,(sigaction *)(oldact + 0x230));
  sigaction(8,(sigaction *)&local_98,(sigaction *)(oldact + 0x460));
  sigaction(7,(sigaction *)&local_98,(sigaction *)(oldact + 0x3d4));
  return;
}

void DisableStackTrace(void)
{
  sigaction(0xb,(sigaction *)(oldact + 0x604),(sigaction *)0x0);
  return;
}

bool checkGuid(char *param_1)
{
  char *tmp_pc1;
  char tmp_c2;
  size_t tmp_s3;
  int tmp_i4;
  
  tmp_s3 = strlen(param_1);
  if (tmp_s3 != 0x20) {
    return false;
  }
  tmp_i4 = 0;
  tmp_pc1 = param_1 + 0x21;
  do {
    tmp_c2 = *param_1;
    param_1 = param_1 + 1;
    tmp_i4 = tmp_i4 + tmp_c2;
  } while (param_1 != tmp_pc1);
  return tmp_i4 == (tmp_i4 / 100) * 100;
}

void nitrox_GenerateNKeyFile(void)
{
  int tmp_i1;
  int tmp_i2;
  time_t tVar3;
  tm *__tp;
  uint32_t tmp_u4;
  char *tmp_pc5;
  uint tmp_u6;
  int tmp_i7;
  size_t tmp_s8;
  uint tmp_u9;
  char tmp_c10;
  uint *tmp_pu11;
  uint *tmp_pu12;
  int tmp_i13;
  int tmp_i14;
  int local_c4;
  uint32_t local_b8;
  time_t local_b4;
  char local_b0 [15];
  char local_a1 [28];
  char local_85 [4];
  uint8_t local_81;
  uint local_80 [27];
  uint32_t uStack_14;
  
  uStack_14 = 0x108bc9;
  tVar3 = time(&local_b4);
  if (tVar3 != 0) {
    __tp = localtime(&local_b4);
    strftime(local_b0,0xf,"%S%j%M%d%w%U%H",__tp);
    tmp_u4 = G_SHA1(local_b0);
    Q_strncpyz(local_a1,tmp_u4,0x21);
    tmp_i13 = 0;
    tmp_pc5 = local_a1;
    do {
      tmp_c10 = *tmp_pc5;
      tmp_pc5 = tmp_pc5 + 1;
      tmp_i13 = tmp_i13 + tmp_c10;
    } while (tmp_pc5 != local_85);
    memmove(local_a1 + 2,local_a1,0x1c);
    local_c4 = 0;
    tmp_i13 = (tmp_i13 + 0x104) % 100;
    do {
      tmp_i1 = local_c4 + 1;
      tmp_i2 = tmp_i1 * 0x19;
      if (tmp_i13 < tmp_i2) {
        do {
          tmp_i14 = 0;
          while( true ) {
            if (0x68 < tmp_i13 + tmp_i14) {
              tmp_i14 = 0x1a - tmp_i14;
            }
            if (tmp_i14 == 0x1a) break;
            tmp_u6 = rand();
            tmp_i14 = (int)((tmp_u6 ^ (int)tmp_u6 >> 0x1f) - ((int)tmp_u6 >> 0x1f)) % (0x1a - tmp_i14);
            tmp_i7 = tmp_i14 + tmp_i13;
            if ((tmp_i2 <= tmp_i7) && (tmp_i7 < 0x65)) goto LAB_00108d07;
          }
        } while( true );
      }
      tmp_i14 = 0;
      do {
        if (0x68 < tmp_i13 + tmp_i14) {
          tmp_i14 = 0x1a - tmp_i14;
        }
        if (tmp_i14 == 0x1a) {
          tmp_c10 = 'A';
          goto LAB_00108d10;
        }
        tmp_u6 = rand();
        tmp_i14 = (int)((tmp_u6 ^ (int)tmp_u6 >> 0x1f) - ((int)tmp_u6 >> 0x1f)) % (0x1a - tmp_i14);
        tmp_i7 = tmp_i14 + tmp_i13;
      } while ((tmp_i7 < tmp_i2) || (100 < tmp_i7));
LAB_00108d07:
      tmp_c10 = (char)tmp_i14 + 'A';
      tmp_i13 = tmp_i7;
LAB_00108d10:
      local_a1[local_c4 + 0x1eU & 0x1f] = tmp_c10;
      local_c4 = tmp_i1;
    } while (tmp_i1 != 4);
    local_81 = 0;
    tmp_s8 = strlen(local_a1);
    encode64(local_a1,local_80,tmp_s8);
    tmp_i13 = trap_FS_FOpenFile("nkey.dat",&local_b8,1);
    tmp_pu12 = local_80;
    if (tmp_i13 < 0) {
      CG_Error("^1ERROR: ^7Coudln\'t create \'nkey.dat\' file!\n");
      return;
    }
    do {
      tmp_pu11 = tmp_pu12;
      tmp_u9 = *tmp_pu11 + 0xfefefeff & ~*tmp_pu11;
      tmp_u6 = tmp_u9 & 0x80808080;
      tmp_pu12 = tmp_pu11 + 1;
    } while (tmp_u6 == 0);
    if ((tmp_u9 & 0x8080) == 0) {
      tmp_pu12 = (uint *)((int)tmp_pu11 + 6);
      tmp_u6 = tmp_u6 >> 0x10;
    }
    trap_FS_Write(local_80,(int)tmp_pu12 +
                           ((-3 - (uint)CARRY1((byte)tmp_u6,(byte)tmp_u6)) - (int)local_80),local_b8);
    trap_FS_FCloseFile(local_b8);
    nitrox_ReadNKey();
  }
  return;
}

uint32_t nitrox_ReadNKey(void)
{
  int tmp_i1;
  uint tmp_u2;
  uint tmp_u3;
  uint *tmp_pu4;
  uint *tmp_pu5;
  uint32_t local_410;
  uint local_40c [8];
  uint local_3eb [246];
  uint32_t uStack_10;
  
  uStack_10 = 0x108e3a;
  tmp_i1 = trap_FS_FOpenFile("nkey.dat",&local_410,0);
  if (tmp_i1 < 0) {
    CG_Printf("^7N^1!^7tmod: ^3Couldn\'t find \'nkey.dat\' file.\n");
    nitrox_GenerateNKeyFile();
    return 0;
  }
  trap_FS_Read(local_40c,tmp_i1,local_410);
  decode64(local_40c);
  tmp_pu4 = local_40c;
  do {
    tmp_pu5 = tmp_pu4;
    tmp_u2 = *tmp_pu5 + 0xfefefeff & ~*tmp_pu5;
    tmp_u3 = tmp_u2 & 0x80808080;
    tmp_pu4 = tmp_pu5 + 1;
  } while (tmp_u3 == 0);
  if ((tmp_u2 & 0x8080) == 0) {
    tmp_pu4 = (uint *)((int)tmp_pu5 + 6);
    tmp_u3 = tmp_u3 >> 0x10;
  }
  if ((char *)((int)tmp_pu4 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_40c)) ==
      (char *)0x20) {
    tmp_i1 = 0;
    tmp_pu4 = local_40c;
    do {
      tmp_u3 = *tmp_pu4;
      tmp_pu4 = (uint *)((int)tmp_pu4 + 1);
      tmp_i1 = tmp_i1 + (char)tmp_u3;
    } while (tmp_pu4 != local_3eb);
    if (tmp_i1 == (tmp_i1 / 100) * 100) {
      if (FirstTime_11951 != 0) {
        CG_Printf("^7N^1!^7tmod GUID: ^5%s\n",local_40c);
        FirstTime_11951 = 0;
      }
      trap_Cvar_Set("n_guid",local_40c);
      trap_FS_FCloseFile(local_410);
      g_unk_010ef664 = 0;
      return 1;
    }
  }
  CG_Printf("^7N^1!^7tmod: ^1Invalid/corrupted \'nkey.dat\' file found.\n");
  trap_FS_FCloseFile(local_410);
  nitrox_GenerateNKeyFile();
  return 0;
}

uint8_t * G_SHA1(char *param_1)
{
  size_t tmp_s1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  
  SHA1Reset(&local_74);
  tmp_s1 = strlen(param_1);
  SHA1Input(&local_74,param_1,tmp_s1);
  tmp_i2 = SHA1Result(&local_74);
  tmp_pu3 = &g_unk_0011d841;
  if (tmp_i2 != 0) {
    tmp_pu3 = (uint8_t *)va("%08X%08X%08X%08X%08X",local_74,local_70,local_6c,local_68,local_64);
  }
  return tmp_pu3;
}

void SHA1Reset(uint32_t *param_1)
{
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[0x17] = 0;
  *param_1 = 0x67452301;
  param_1[1] = 0xefcdab89;
  param_1[2] = 0x98badcfe;
  param_1[3] = 0x10325476;
  param_1[4] = 0xc3d2e1f0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  return;
}

void SHA1ProcessMessageBlock(uint *param_1)
{
  uint *tmp_pu1;
  uint tmp_u2;
  uint tmp_u3;
  uint tmp_u4;
  uint *tmp_pu5;
  uint *tmp_pu6;
  int tmp_i7;
  uint tmp_u8;
  uint tmp_u9;
  uint tmp_u10;
  uint local_170;
  uint local_16c;
  uint local_168;
  uint local_14c [20];
  uint local_fc [20];
  uint local_ac [20];
  uint local_5c [3];
  uint local_50 [8];
  uint local_30 [5];
  uint local_1c [4];
  
  tmp_i7 = 0;
  tmp_pu6 = local_14c;
  tmp_pu1 = param_1 + 7;
  do {
    tmp_pu6[tmp_i7] =
         (uint)*(byte *)((int)tmp_pu1 + 1) << 0x10 | (uint)(byte)*tmp_pu1 << 0x18 |
         (uint)*(byte *)((int)tmp_pu1 + 3) | (uint)*(byte *)((int)tmp_pu1 + 2) << 8;
    tmp_i7 = tmp_i7 + 1;
    tmp_pu1 = tmp_pu1 + 1;
  } while (tmp_i7 != 0x10);
  local_16c = local_14c[0xe];
  local_170 = 0x10;
  tmp_pu1 = local_14c + 8;
  do {
    tmp_u8 = local_14c[0xd] ^ local_14c[0];
    local_170 = local_170 + 3;
    local_14c[0] = tmp_pu1[-5];
    tmp_u8 = tmp_u8 ^ *tmp_pu1 ^ tmp_pu1[-6];
    local_14c[0xd] = tmp_u8 << 1 | (uint)((int)tmp_u8 < 0);
    tmp_pu1[8] = local_14c[0xd];
    tmp_u8 = local_14c[1] ^ local_16c ^ tmp_pu1[1] ^ local_14c[0];
    local_16c = tmp_u8 << 1 | (uint)((int)tmp_u8 < 0);
    tmp_pu1[9] = local_16c;
    local_14c[1] = tmp_pu1[-4];
    tmp_u8 = local_14c[0xf] ^ tmp_pu1[2] ^ local_14c[1] ^ tmp_pu1[-6];
    local_14c[0xf] = tmp_u8 << 1 | (uint)((int)tmp_u8 < 0);
    tmp_pu1[10] = local_14c[0xf];
    tmp_pu1 = tmp_pu1 + 3;
  } while (local_170 != 0x4f);
  tmp_pu1 = local_1c;
  do {
    tmp_pu5 = tmp_pu1 + 1;
    tmp_u8 = tmp_pu1[-5] ^ *tmp_pu1 ^ tmp_pu1[-0xb] ^ tmp_pu1[-0xd];
    tmp_pu1[3] = tmp_u8 << 1 | (uint)((int)tmp_u8 < 0);
    tmp_pu1 = tmp_pu5;
  } while (tmp_pu5 != local_1c + 1);
  tmp_u4 = param_1[2];
  tmp_u10 = param_1[1];
  tmp_u8 = *param_1;
  tmp_u2 = param_1[3];
  local_168 = param_1[4];
  do {
    local_16c = tmp_u2;
    tmp_u9 = tmp_u8;
    tmp_u2 = tmp_u4;
    tmp_u8 = local_168;
    tmp_u3 = *tmp_pu6;
    tmp_pu6 = tmp_pu6 + 1;
    tmp_u4 = tmp_u10 >> 2 | tmp_u10 << 0x1e;
    local_168 = local_16c;
    tmp_u8 = (tmp_u9 << 5 | tmp_u9 >> 0x1b) + tmp_u3 + 0x5a827999 +
            (tmp_u2 & tmp_u10 | ~tmp_u10 & local_16c) + tmp_u8;
    tmp_u10 = tmp_u9;
  } while (tmp_pu6 != local_fc);
  do {
    local_170 = tmp_u2;
    local_168 = tmp_u8;
    tmp_u2 = tmp_u4;
    tmp_u8 = *tmp_pu6;
    tmp_pu6 = tmp_pu6 + 1;
    tmp_u4 = tmp_u9 >> 2 | tmp_u9 << 0x1e;
    tmp_u8 = local_16c +
            (local_168 << 5 | local_168 >> 0x1b) + 0x6ed9eba1 + (tmp_u2 ^ tmp_u9 ^ local_170) + tmp_u8;
    tmp_u9 = local_168;
    local_16c = local_170;
  } while (tmp_pu6 != local_ac);
  do {
    local_16c = tmp_u8;
    tmp_u3 = tmp_u2;
    tmp_u8 = *tmp_pu6;
    tmp_pu6 = tmp_pu6 + 1;
    tmp_u8 = (local_16c << 5 | local_16c >> 0x1b) + tmp_u8 + -0x70e44324 +
            (tmp_u3 & tmp_u4 | (tmp_u3 | tmp_u4) & local_168) + local_170;
    tmp_u10 = local_168 >> 2 | local_168 << 0x1e;
    tmp_u2 = tmp_u4;
    tmp_u4 = tmp_u10;
    local_170 = tmp_u3;
    local_168 = local_16c;
  } while (tmp_pu6 != local_5c);
  do {
    tmp_u9 = tmp_u10;
    tmp_u3 = tmp_u8;
    tmp_u4 = tmp_u2;
    tmp_pu1 = tmp_pu6 + 1;
    tmp_u8 = (tmp_u3 << 5 | tmp_u3 >> 0x1b) + 0xca62c1d6 + (local_16c ^ tmp_u9 ^ tmp_u4) + *tmp_pu6 +
            local_170;
    tmp_u10 = local_16c >> 2 | local_16c << 0x1e;
    tmp_u2 = tmp_u9;
    tmp_pu6 = tmp_pu1;
    local_170 = tmp_u4;
    local_16c = tmp_u3;
  } while (tmp_pu1 != (uint *)&stack0xfffffff4);
  *param_1 = tmp_u8 + *param_1;
  param_1[0x17] = 0;
  param_1[1] = tmp_u3 + param_1[1];
  param_1[2] = tmp_u10 + param_1[2];
  param_1[3] = param_1[3] + tmp_u9;
  param_1[4] = tmp_u4 + param_1[4];
  return;
}

int SHA1Input(int param_1,uint8_t *param_2,int param_3)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  int local_10;
  
  if (param_3 != 0) {
    if ((*(int *)(param_1 + 0x60) != 0) || (*(int *)(param_1 + 100) != 0)) {
      *(uint32_t *)(param_1 + 100) = 1;
      return local_10;
    }
    tmp_pu4 = param_2;
    do {
      tmp_i3 = *(int *)(param_1 + 0x5c);
      tmp_i1 = tmp_i3 + 1;
      *(int *)(param_1 + 0x5c) = tmp_i1;
      *(uint8_t *)(param_1 + 0x1c + tmp_i3) = *tmp_pu4;
      tmp_pi2 = (int *)(param_1 + 0x14);
      *tmp_pi2 = *tmp_pi2 + 8;
      if (*tmp_pi2 == 0) {
        tmp_pi2 = (int *)(param_1 + 0x18);
        *tmp_pi2 = *tmp_pi2 + 1;
        if (*tmp_pi2 == 0) {
          *(uint32_t *)(param_1 + 100) = 1;
        }
      }
      if (tmp_i1 == 0x40) {
        SHA1ProcessMessageBlock();
        local_10 = param_1;
      }
    } while ((tmp_pu4 + 1 != param_2 + param_3) &&
            (tmp_pu4 = tmp_pu4 + 1, *(int *)(param_1 + 100) == 0));
  }
  return local_10;
}

uint64_t SHA1Result(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint tmp_u4;
  uint tmp_u5;
  uint32_t *tmp_pu6;
  byte tmp_b7;
  uint32_t in_stack_fffffff4;
  int tmp_i8;
  
  tmp_b7 = 0;
  tmp_u3 = 0;
  if ((*(int *)(param_1 + 100) != 0) || (tmp_u3 = 1, *(int *)(param_1 + 0x60) != 0)) {
    return CONCAT44(in_stack_fffffff4,tmp_u3);
  }
  tmp_i1 = *(int *)(param_1 + 0x5c);
  tmp_i8 = tmp_i1 + 1;
  *(int *)(param_1 + 0x5c) = tmp_i8;
  *(uint8_t *)(param_1 + 0x1c + tmp_i1) = 0x80;
  if (tmp_i1 < 0x38) {
    if (tmp_i8 == 0x38) goto LAB_001094e2;
    tmp_u5 = 0x37 - tmp_i1;
    tmp_pu6 = (uint32_t *)(param_1 + 0x1d + tmp_i1);
  }
  else {
    if (tmp_i8 < 0x40) {
      if (tmp_i1 != 0x3f) {
        tmp_u5 = 0;
        do {
          *(uint8_t *)(param_1 + 0x1d + tmp_i1 + tmp_u5) = 0;
          tmp_u5 = tmp_u5 + 1;
        } while (tmp_u5 < 0x3fU - tmp_i1);
      }
      *(uint32_t *)(param_1 + 0x5c) = 0x40;
    }
    SHA1ProcessMessageBlock(param_1);
    tmp_i8 = *(int *)(param_1 + 0x5c);
    if (0x37 < tmp_i8) goto LAB_001094e2;
    tmp_u5 = 0x38 - tmp_i8;
    tmp_pu6 = (uint32_t *)(param_1 + 0x1c + tmp_i8);
  }
  if (7 < tmp_u5) {
    tmp_u4 = tmp_u5;
    if (((uint)tmp_pu6 & 1) != 0) {
      *(uint8_t *)tmp_pu6 = 0;
      tmp_u4 = tmp_u5 - 1;
      tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 1);
    }
    if (((uint)tmp_pu6 & 2) != 0) {
      *(uint16_t *)tmp_pu6 = 0;
      tmp_u4 = tmp_u4 - 2;
      tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
    }
    if (((uint)tmp_pu6 & 4) != 0) {
      *tmp_pu6 = 0;
      tmp_u4 = tmp_u4 - 4;
      tmp_pu6 = tmp_pu6 + 1;
    }
    tmp_u5 = tmp_u4 & 3;
    for (tmp_u4 = tmp_u4 >> 2; tmp_u4 != 0; tmp_u4 = tmp_u4 - 1) {
      *tmp_pu6 = 0;
      tmp_pu6 = tmp_pu6 + (uint)tmp_b7 * -2 + 1;
    }
  }
  if ((tmp_u5 & 4) != 0) {
    *tmp_pu6 = 0;
    tmp_pu6 = tmp_pu6 + 1;
  }
  if ((tmp_u5 & 2) != 0) {
    *(uint16_t *)tmp_pu6 = 0;
    tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
  }
  if ((tmp_u5 & 1) != 0) {
    *(uint8_t *)tmp_pu6 = 0;
  }
  *(uint32_t *)(param_1 + 0x5c) = 0x38;
LAB_001094e2:
  tmp_u3 = *(uint32_t *)(param_1 + 0x18);
  *(char *)(param_1 + 0x54) = (char)((uint)tmp_u3 >> 0x18);
  *(char *)(param_1 + 0x55) = (char)((uint)tmp_u3 >> 0x10);
  *(char *)(param_1 + 0x57) = (char)tmp_u3;
  tmp_u2 = *(uint32_t *)(param_1 + 0x14);
  *(char *)(param_1 + 0x56) = (char)((uint)tmp_u3 >> 8);
  *(char *)(param_1 + 0x58) = (char)((uint)tmp_u2 >> 0x18);
  *(char *)(param_1 + 0x59) = (char)((uint)tmp_u2 >> 0x10);
  *(char *)(param_1 + 0x5a) = (char)((uint)tmp_u2 >> 8);
  *(char *)(param_1 + 0x5b) = (char)tmp_u2;
  tmp_i8 = param_1;
  SHA1ProcessMessageBlock();
  *(uint32_t *)(param_1 + 0x60) = 1;
  return CONCAT44(tmp_i8,1);
}

void SHA1PadMessage(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint tmp_u5;
  uint tmp_u6;
  uint32_t *tmp_pu7;
  byte tmp_b8;
  
  tmp_b8 = 0;
  tmp_i2 = *(int *)(param_1 + 0x5c);
  tmp_i1 = tmp_i2 + 1;
  *(int *)(param_1 + 0x5c) = tmp_i1;
  *(uint8_t *)(param_1 + 0x1c + tmp_i2) = 0x80;
  if (tmp_i2 < 0x38) {
    if (tmp_i1 == 0x38) goto LAB_001096bf;
    tmp_u5 = 0x37 - tmp_i2;
    tmp_pu7 = (uint32_t *)(param_1 + 0x1d + tmp_i2);
  }
  else {
    if (tmp_i1 < 0x40) {
      if (tmp_i2 != 0x3f) {
        tmp_u5 = 0;
        do {
          *(uint8_t *)(param_1 + 0x1d + tmp_i2 + tmp_u5) = 0;
          tmp_u5 = tmp_u5 + 1;
        } while (tmp_u5 < 0x3fU - tmp_i2);
      }
      *(uint32_t *)(param_1 + 0x5c) = 0x40;
    }
    SHA1ProcessMessageBlock(param_1);
    tmp_i1 = *(int *)(param_1 + 0x5c);
    if (0x37 < tmp_i1) goto LAB_001096bf;
    tmp_u5 = 0x38 - tmp_i1;
    tmp_pu7 = (uint32_t *)(param_1 + 0x1c + tmp_i1);
  }
  if (7 < tmp_u5) {
    tmp_u6 = tmp_u5;
    if (((uint)tmp_pu7 & 1) != 0) {
      *(uint8_t *)tmp_pu7 = 0;
      tmp_u6 = tmp_u5 - 1;
      tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 1);
    }
    if (((uint)tmp_pu7 & 2) != 0) {
      *(uint16_t *)tmp_pu7 = 0;
      tmp_u6 = tmp_u6 - 2;
      tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
    }
    if (((uint)tmp_pu7 & 4) != 0) {
      *tmp_pu7 = 0;
      tmp_u6 = tmp_u6 - 4;
      tmp_pu7 = tmp_pu7 + 1;
    }
    tmp_u5 = tmp_u6 & 3;
    for (tmp_u6 = tmp_u6 >> 2; tmp_u6 != 0; tmp_u6 = tmp_u6 - 1) {
      *tmp_pu7 = 0;
      tmp_pu7 = tmp_pu7 + (uint)tmp_b8 * -2 + 1;
    }
  }
  if ((tmp_u5 & 4) != 0) {
    *tmp_pu7 = 0;
    tmp_pu7 = tmp_pu7 + 1;
  }
  if ((tmp_u5 & 2) != 0) {
    *(uint16_t *)tmp_pu7 = 0;
    tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
  }
  if ((tmp_u5 & 1) != 0) {
    *(uint8_t *)tmp_pu7 = 0;
  }
  *(uint32_t *)(param_1 + 0x5c) = 0x38;
LAB_001096bf:
  tmp_u3 = *(uint32_t *)(param_1 + 0x18);
  *(char *)(param_1 + 0x54) = (char)((uint)tmp_u3 >> 0x18);
  *(char *)(param_1 + 0x55) = (char)((uint)tmp_u3 >> 0x10);
  *(char *)(param_1 + 0x57) = (char)tmp_u3;
  tmp_u4 = *(uint32_t *)(param_1 + 0x14);
  *(char *)(param_1 + 0x56) = (char)((uint)tmp_u3 >> 8);
  *(char *)(param_1 + 0x58) = (char)((uint)tmp_u4 >> 0x18);
  *(char *)(param_1 + 0x59) = (char)((uint)tmp_u4 >> 0x10);
  *(char *)(param_1 + 0x5a) = (char)((uint)tmp_u4 >> 8);
  *(char *)(param_1 + 0x5b) = (char)tmp_u4;
  SHA1ProcessMessageBlock();
  return;
}

uint32_t nitrox_TCPResolve(void)
{
  uint tmp_u1;
  int tmp_i2;
  hostent *phVar3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  int tmp_i6;
  uint tmp_u7;
  char tmp_c8;
  char *tmp_pc9;
  byte tmp_b10;
  char local_130 [36];
  uint32_t local_10c;
  uint32_t local_108 [63];
  
  tmp_b10 = 0;
  local_108[0x3e] = 0x10975a;
  local_10c = 0;
  tmp_u7 = 0;
  do {
    tmp_u1 = tmp_u7;
    *(uint32_t *)((int)local_108 + tmp_u1) = 0;
    *(uint32_t *)((int)local_108 + tmp_u1 + 4) = 0;
    tmp_u7 = tmp_u1 + 8;
  } while (tmp_u1 + 8 < 0xf8);
  *(uint32_t *)((int)local_108 + tmp_u1 + 8) = 0;
  trap_Cvar_VariableStringBuffer("cl_currentServerIP",&local_10c,0x100);
  if ((char)local_10c != '\0') {
    tmp_i2 = 0;
    tmp_c8 = (char)local_10c;
    if ((char)local_10c != ':') {
      do {
        tmp_i6 = tmp_i2 + 1;
        local_130[tmp_i2] = tmp_c8;
        tmp_c8 = *(char *)((int)&local_10c + tmp_i6);
        if ((tmp_c8 == '\0') || (tmp_i6 == 0x24)) break;
        tmp_i2 = tmp_i6;
      } while (tmp_c8 != ':');
      goto LAB_001097e6;
    }
  }
  tmp_i6 = 0;
LAB_001097e6:
  local_130[tmp_i6] = '\0';
  phVar3 = gethostbyname(local_130);
  if (phVar3 != (hostent *)0x0) {
    tmp_u4 = CG_ConfigString(0);
    tmp_pc5 = (char *)Info_ValueForKey(tmp_u4,"nport");
    GHIDRA_FIELD(cgs, 33822772, 4) = strtol(tmp_pc5,(char **)0x0,10);
    _DAT_00e9a360 = 0;
    tmp_pc5 = &g_unk_00e9a35c;
    _DAT_00e9a35c = 0;
    g_unk_00e9a364 = 0;
    tmp_u7 = phVar3->h_length;
    tmp_pc9 = *phVar3->h_addr_list;
    if (7 < tmp_u7) {
      _DAT_00e9a35c = *(uint32_t *)tmp_pc9;
      tmp_pc5 = &g_unk_00e9a360;
      tmp_pc9 = tmp_pc9 + 4;
      tmp_u7 = tmp_u7 - 4;
    }
    for (; tmp_u7 != 0; tmp_u7 = tmp_u7 - 1) {
      *tmp_pc5 = *tmp_pc9;
      tmp_pc9 = tmp_pc9 + (uint)tmp_b10 * -2 + 1;
      tmp_pc5 = tmp_pc5 + (uint)tmp_b10 * -2 + 1;
    }
    _svSaddrIn = CONCAT22((ushort)GHIDRA_FIELD(cgs, 33822772, 4) >> 8 | (ushort)GHIDRA_FIELD(cgs, 33822772, 4) << 8,2);
    return 1;
  }
  return 0;
}

uint32_t nitrox_TCPOpen(void)
{
  uint tmp_u1;
  uint tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint32_t local_110;
  uint32_t local_10c;
  uint32_t local_108 [63];
  
  local_108[0x3e] = 0x1098ec;
  local_10c = 0;
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_108 + tmp_u2) = 0;
    *(uint32_t *)((int)local_108 + tmp_u2 + 4) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xf8);
  *(uint32_t *)((int)local_108 + tmp_u2 + 8) = 0;
  local_110 = 1;
  GHIDRA_FIELD(cgs, 33823076, 4) = socket(2,1,0);
  if (GHIDRA_FIELD(cgs, 33823076, 4) != -1) {
    g_unk_041ccb14 = 0;
    g_unk_041ccb18 = 0;
    g_unk_041ccb1c = 0;
    _clSaddrIn = 2;
    trap_Cvar_VariableStringBuffer("net_port",&local_10c,0x100);
    _clSaddrIn = _clSaddrIn & 0xffff;
    trap_Cvar_VariableStringBuffer("net_ip",&local_10c,0x100);
    tmp_i3 = Q_stricmp(&local_10c,"localhost");
    if ((tmp_i3 == 0) || (tmp_i3 = Q_stricmp(&local_10c,"127.0.0.1"), tmp_i3 == 0)) {
      g_unk_041ccb14 = 0;
    }
    else {
      g_unk_041ccb14 = inet_addr((char *)&local_10c);
    }
    tmp_i3 = setsockopt(GHIDRA_FIELD(cgs, 33823076, 4),1,2,&local_110,4);
    if (tmp_i3 < 0) {
      if (GHIDRA_FIELD(cgs, 33823076, 4) != 0) {
        close(GHIDRA_FIELD(cgs, 33823076, 4));
        GHIDRA_FIELD(cgs, 33823076, 4) = 0;
      }
    }
    else {
      tmp_i3 = bind(GHIDRA_FIELD(cgs, 33823076, 4),(sockaddr *)&clSaddrIn,clSaddrInSz);
      if (-1 < tmp_i3) {
        getsockname(GHIDRA_FIELD(cgs, 33823076, 4),(sockaddr *)&clSaddrIn,&clSaddrInSz);
        GHIDRA_FIELD(cgs, 33823080, 4) = ZEXT24((ushort)(g_unk_041ccb12 >> 8 | g_unk_041ccb12 << 8));
        trap_Cvar_Register(0,"cnport",&g_unk_0011d841,0x442);
        tmp_u4 = va("%i",GHIDRA_FIELD(cgs, 33823080, 4));
        trap_Cvar_Set("cnport",tmp_u4);
        tmp_i3 = nitrox_TCPResolve();
        if (tmp_i3 != 0) {
          return 1;
        }
      }
      if (GHIDRA_FIELD(cgs, 33823076, 4) != 0) {
        close(GHIDRA_FIELD(cgs, 33823076, 4));
        GHIDRA_FIELD(cgs, 33823076, 4) = 0;
      }
    }
    trap_Cvar_Set("cnport",&g_unk_0011e957);
    return 0;
  }
  return 0;
}

void nitrox_TCPSendHB(void)
{
  uint tmp_u1;
  uint tmp_u2;
  uint *tmp_pu3;
  uint *tmp_pu4;
  uint local_400c;
  uint8_t local_4008 [16380];
  
  local_400c = 0;
  memset(local_4008,0,0x3ffc);
  if (GHIDRA_FIELD(cgs, 33823076, 4) != 0) {
    Com_sprintf(&local_400c,0x4000,"hb %i",GHIDRA_FIELD(cgs, 33823080, 4));
    tmp_pu4 = &local_400c;
    do {
      tmp_pu3 = tmp_pu4;
      tmp_u1 = *tmp_pu3 + 0xfefefeff & ~*tmp_pu3;
      tmp_u2 = tmp_u1 & 0x80808080;
      tmp_pu4 = tmp_pu3 + 1;
    } while (tmp_u2 == 0);
    if ((tmp_u1 & 0x8080) == 0) {
      tmp_pu4 = (uint *)((int)tmp_pu3 + 6);
      tmp_u2 = tmp_u2 >> 0x10;
    }
    sendto(GHIDRA_FIELD(cgs, 33823076, 4),&local_400c,
           (int)tmp_pu4 + ((-3 - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) - (int)&local_400c),0,
           (sockaddr *)&svSaddrIn,0x10);
  }
  return;
}

uint32_t nitrox_TCPConnect(void)
{
  byte tmp_b1;
  int tmp_i2;
  uint tmp_u3;
  uint32_t tmp_u4;
  __fd_mask *p_Var5;
  uint32_t local_128;
  timeval local_124;
  uint local_11c [32];
  uint local_9c [35];
  
  local_128 = 1;
  tmp_u4 = 0;
  if (GHIDRA_FIELD(cgs, 33823076, 4) != 0) {
    local_124.tv_sec = 2;
    local_124.tv_usec = 0;
    tmp_u4 = 1;
    ioctl(GHIDRA_FIELD(cgs, 33823076, 4),0x5421,&local_128);
    tmp_i2 = connect(GHIDRA_FIELD(cgs, 33823076, 4),(sockaddr *)&svSaddrIn,0x10);
    if (tmp_i2 != 0) {
      local_128 = 0;
      ioctl(GHIDRA_FIELD(cgs, 33823076, 4),0x5421,&local_128);
      p_Var5 = (__fd_mask *)local_11c;
      for (tmp_i2 = 0x20; tmp_i2 != 0; tmp_i2 = tmp_i2 + -1) {
        *p_Var5 = 0;
        p_Var5 = p_Var5 + 1;
      }
      p_Var5 = (__fd_mask *)local_9c;
      for (tmp_i2 = 0x20; tmp_i2 != 0; tmp_i2 = tmp_i2 + -1) {
        *p_Var5 = 0;
        p_Var5 = p_Var5 + 1;
      }
      tmp_i2 = GHIDRA_FIELD(cgs, 33823076, 4) + 0x1f;
      if (-1 < (int)GHIDRA_FIELD(cgs, 33823076, 4)) {
        tmp_i2 = GHIDRA_FIELD(cgs, 33823076, 4);
      }
      tmp_b1 = SUB41(GHIDRA_FIELD(cgs, 33823076, 4),3) >> 7;
      tmp_u3 = 1 << (((char)GHIDRA_FIELD(cgs, 33823076, 4) + (tmp_b1 >> 3) & 0x1f) - (tmp_b1 >> 3) & 0x1f);
      local_11c[tmp_i2 >> 5] = local_11c[tmp_i2 >> 5] | tmp_u3;
      local_9c[tmp_i2 >> 5] = local_9c[tmp_i2 >> 5] | tmp_u3;
      select(0,(fd_set *)0x0,(fd_set *)local_11c,(fd_set *)local_9c,&local_124);
      tmp_i2 = GHIDRA_FIELD(cgs, 33823076, 4) + 0x1f;
      if (-1 < (int)GHIDRA_FIELD(cgs, 33823076, 4)) {
        tmp_i2 = GHIDRA_FIELD(cgs, 33823076, 4);
      }
      tmp_b1 = SUB41(GHIDRA_FIELD(cgs, 33823076, 4),3) >> 7;
      if (((int)local_11c[tmp_i2 >> 5] >>
           (((char)GHIDRA_FIELD(cgs, 33823076, 4) + (tmp_b1 >> 3) & 0x1f) - (tmp_b1 >> 3) & 0x1f) & 1U) == 0) {
        if (GHIDRA_FIELD(cgs, 33823076, 4) != 0) {
          close(GHIDRA_FIELD(cgs, 33823076, 4));
          GHIDRA_FIELD(cgs, 33823076, 4) = 0;
        }
        tmp_u4 = 0;
        trap_Cvar_Set("cnport",&g_unk_0011e957);
      }
      else {
        nitrox_TCPSendHB();
        tmp_u4 = 1;
      }
    }
  }
  return tmp_u4;
}

void nitrox_TCPSend(uint32_t param_1)
{
  uint tmp_u1;
  uint tmp_u2;
  uint *tmp_pu3;
  uint *tmp_pu4;
  uint local_400c;
  uint8_t local_4008 [16380];
  
  local_400c = 0;
  memset(local_4008,0,0x3ffc);
  if (GHIDRA_FIELD(cgs, 33823076, 4) != 0) {
    Com_sprintf(&local_400c,0x4000,"%s",param_1);
    tmp_pu4 = &local_400c;
    do {
      tmp_pu3 = tmp_pu4;
      tmp_u1 = *tmp_pu3 + 0xfefefeff & ~*tmp_pu3;
      tmp_u2 = tmp_u1 & 0x80808080;
      tmp_pu4 = tmp_pu3 + 1;
    } while (tmp_u2 == 0);
    if ((tmp_u1 & 0x8080) == 0) {
      tmp_pu4 = (uint *)((int)tmp_pu3 + 6);
      tmp_u2 = tmp_u2 >> 0x10;
    }
    sendto(GHIDRA_FIELD(cgs, 33823076, 4),&local_400c,
           (int)tmp_pu4 + ((-3 - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) - (int)&local_400c),0,
           (sockaddr *)&svSaddrIn,0x10);
  }
  return;
}

void nitrox_TCPClose(void)
{
  if (GHIDRA_FIELD(cgs, 33823076, 4) != 0) {
    close(GHIDRA_FIELD(cgs, 33823076, 4));
    GHIDRA_FIELD(cgs, 33823076, 4) = 0;
  }
  trap_Cvar_Set("cnport",&g_unk_0011e957);
  return;
}

void nitrox_SendScreenshot(void)
{
  size_t __n;
  ssize_t tmp_s1;
  
  if ((GHIDRA_FIELD(cgs, 33823044, 4) != 0) && (GHIDRA_FIELD(cgs, 33823076, 4) != 0)) {
    __n = GHIDRA_FIELD(cgs, 33823044, 4) - GHIDRA_FIELD(cgs, 33823052, 4);
    if (0x4000 < (int)__n) {
      __n = 0x4000;
    }
    tmp_s1 = sendto(GHIDRA_FIELD(cgs, 33823076, 4),(void *)(GHIDRA_FIELD(cgs, 33823052, 4) + GHIDRA_FIELD(cgs, 33823060, 4)),__n,0,
                   (sockaddr *)&svSaddrIn,0x10);
    if (tmp_s1 != -1) {
      GHIDRA_FIELD(cgs, 33823052, 4) = tmp_s1 + GHIDRA_FIELD(cgs, 33823052, 4);
      if (GHIDRA_FIELD(cgs, 33823052, 4) == GHIDRA_FIELD(cgs, 33823044, 4)) {
        GHIDRA_FIELD(cgs, 33822776, 4) = 6;
      }
      GHIDRA_FIELD(cgs, 33822780, 4) = g_unk_010906e0 + 0x32;
      return;
    }
    GHIDRA_FIELD(cgs, 33822776, 4) = 6;
    GHIDRA_FIELD(cgs, 33822780, 4) = g_unk_010906e0 + 100;
  }
  return;
}

void nitrox_ScreenshotFile(uint param_1)
{
  uint32_t *tmp_pu1;
  uint32_t *tmp_pu2;
  uint tmp_u3;
  uint tmp_u4;
  char *tmp_pc5;
  uint32_t local_31c;
  uint32_t local_318 [194];
  
  local_31c = 0;
  tmp_u3 = 0;
  do {
    tmp_u4 = tmp_u3;
    *(uint32_t *)((int)local_318 + tmp_u4) = 0;
    *(uint32_t *)((int)local_318 + tmp_u4 + 4) = 0;
    tmp_u3 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0xf8);
  *(uint32_t *)((int)local_318 + tmp_u4 + 8) = 0;
  local_318[0x3f] = 0;
  tmp_u3 = 0;
  do {
    tmp_u4 = tmp_u3;
    *(uint32_t *)((int)local_318 + tmp_u4 + 0x100) = 0;
    *(uint32_t *)((int)local_318 + tmp_u4 + 0x104) = 0;
    tmp_u3 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0xf8);
  *(uint32_t *)((int)local_318 + tmp_u4 + 0x108) = 0;
  local_318[0x7f] = 0;
  tmp_u3 = 0;
  do {
    tmp_u4 = tmp_u3;
    *(uint32_t *)((int)local_318 + tmp_u4 + 0x200) = 0;
    *(uint32_t *)((int)local_318 + tmp_u4 + 0x204) = 0;
    tmp_u3 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0xf8);
  *(uint32_t *)((int)local_318 + tmp_u4 + 0x208) = 0;
  tmp_pu1 = local_318 + 0x7f;
  tmp_pu2 = local_318 + 0x3f;
  trap_Cvar_VariableStringBuffer("fs_homepath",tmp_pu1,0x100);
  trap_Cvar_VariableStringBuffer("fs_game",tmp_pu2,0x100);
  if (param_1 < 10000) {
    if (GHIDRA_FIELD(cgs, 33823104, 4) == 0) {
      tmp_pc5 = "%s/%s/screenshots/shot%04i.jpg";
    }
    else {
      tmp_pc5 = "%s/%s/screenshots/shot%04i.png";
    }
    Com_sprintf(&local_31c,0x100,tmp_pc5,tmp_pu1,tmp_pu2,param_1);
  }
  else {
    if (GHIDRA_FIELD(cgs, 33823104, 4) == 0) {
      tmp_pc5 = "%s/%s/screenshots/shot9999.jpg";
    }
    else {
      tmp_pc5 = "%s/%s/screenshots/shot9999.png";
    }
    Com_sprintf(&local_31c,0x100,tmp_pc5,tmp_pu1,tmp_pu2);
  }
  Q_strncpyz(0x31316a0,&local_31c,0x100);
  return;
}

uint32_t nitrox_ScreenshotFileExists(char *param_1)
{
  FILE *__stream;
  
  __stream = fopen(param_1,"rb");
  if (__stream != (FILE *)0x0) {
    fclose(__stream);
    return 1;
  }
  return 0;
}

uint32_t nitrox_Screenshot(void)
{
  char tmp_c1;
  char tmp_c2;
  FILE *__stream;
  char *tmp_pc3;
  int tmp_i4;
  uint32_t tmp_u5;
  char local_2c [24];
  uint32_t uStack_14;
  
  uStack_14 = 0x10a349;
  while( true ) {
    if (9999 < (int)GHIDRA_FIELD(cgs, 33823048, 4)) {
      GHIDRA_FIELD(cgs, 33823048, 4) = 0;
      GHIDRA_FIELD(cgs, 33822776, 4) = 1;
      return 0;
    }
    nitrox_ScreenshotFile(GHIDRA_FIELD(cgs, 33823048, 4));
    __stream = fopen(cgs + 0x2041840,"rb");
    if (__stream == (FILE *)0x0) break;
    fclose(__stream);
    GHIDRA_FIELD(cgs, 33823048, 4) = GHIDRA_FIELD(cgs, 33823048, 4) + 1;
  }
  if (9999 < (int)GHIDRA_FIELD(cgs, 33823048, 4)) {
    GHIDRA_FIELD(cgs, 33822776, 4) = 1;
    GHIDRA_FIELD(cgs, 33823048, 4) = 0;
    return 0;
  }
  tmp_pc3 = strrchr(cgs + 0x2041840,0x2f);
  tmp_c1 = tmp_pc3[1];
  if ((tmp_c1 == '\0') || (tmp_c1 == '.')) {
    tmp_i4 = 0;
  }
  else {
    tmp_c2 = tmp_pc3[2];
    local_2c[0] = tmp_c1;
    if ((tmp_c2 == '\0') || (tmp_c2 == '.')) {
      tmp_i4 = 1;
    }
    else {
      tmp_c1 = tmp_pc3[3];
      local_2c[1] = tmp_c2;
      if ((tmp_c1 == '\0') || (tmp_c1 == '.')) {
        tmp_i4 = 2;
      }
      else {
        tmp_c2 = tmp_pc3[4];
        local_2c[2] = tmp_c1;
        if ((tmp_c2 == '\0') || (tmp_c2 == '.')) {
          tmp_i4 = 3;
        }
        else {
          tmp_c1 = tmp_pc3[5];
          local_2c[3] = tmp_c2;
          if ((tmp_c1 == '\0') || (tmp_c1 == '.')) {
            tmp_i4 = 4;
          }
          else {
            tmp_c2 = tmp_pc3[6];
            local_2c[4] = tmp_c1;
            if ((tmp_c2 == '\0') || (tmp_c2 == '.')) {
              tmp_i4 = 5;
            }
            else {
              tmp_c1 = tmp_pc3[7];
              local_2c[5] = tmp_c2;
              if ((tmp_c1 == '\0') || (tmp_c1 == '.')) {
                tmp_i4 = 6;
              }
              else {
                tmp_c2 = tmp_pc3[8];
                local_2c[6] = tmp_c1;
                if ((tmp_c2 == '\0') || (tmp_c2 == '.')) {
                  tmp_i4 = 7;
                }
                else {
                  tmp_c1 = tmp_pc3[9];
                  local_2c[7] = tmp_c2;
                  if ((tmp_c1 == '\0') || (tmp_c1 == '.')) {
                    tmp_i4 = 8;
                  }
                  else {
                    tmp_c2 = tmp_pc3[10];
                    local_2c[8] = tmp_c1;
                    if ((tmp_c2 == '\0') || (tmp_c2 == '.')) {
                      tmp_i4 = 9;
                    }
                    else {
                      tmp_c1 = tmp_pc3[0xb];
                      local_2c[9] = tmp_c2;
                      if ((tmp_c1 == '\0') || (tmp_c1 == '.')) {
                        tmp_i4 = 10;
                      }
                      else {
                        tmp_c2 = tmp_pc3[0xc];
                        local_2c[10] = tmp_c1;
                        if ((tmp_c2 == '\0') || (tmp_c2 == '.')) {
                          tmp_i4 = 0xb;
                        }
                        else {
                          tmp_c1 = tmp_pc3[0xd];
                          local_2c[0xb] = tmp_c2;
                          if ((tmp_c1 == '\0') || (tmp_c1 == '.')) {
                            tmp_i4 = 0xc;
                          }
                          else {
                            tmp_c2 = tmp_pc3[0xe];
                            local_2c[0xc] = tmp_c1;
                            if ((tmp_c2 == '\0') || (tmp_c2 == '.')) {
                              tmp_i4 = 0xd;
                            }
                            else {
                              tmp_c1 = tmp_pc3[0xf];
                              local_2c[0xd] = tmp_c2;
                              if ((tmp_c1 == '\0') || (tmp_c1 == '.')) {
                                tmp_i4 = 0xe;
                              }
                              else {
                                tmp_c2 = tmp_pc3[0x10];
                                local_2c[0xe] = tmp_c1;
                                if ((tmp_c2 == '\0') || (tmp_c2 == '.')) {
                                  tmp_i4 = 0xf;
                                }
                                else {
                                  tmp_i4 = 0x10;
                                  local_2c[0xf] = tmp_c2;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  local_2c[tmp_i4] = '\0';
  if (GHIDRA_FIELD(cgs, 33823104, 4) == 0) {
    tmp_u5 = va("screenshotJPEG %s\n",local_2c);
    trap_SendConsoleCommand(tmp_u5);
  }
  else {
    tmp_u5 = va("screenshot %s\n",local_2c);
    trap_SendConsoleCommand(tmp_u5);
  }
  GHIDRA_FIELD(cgs, 33822776, 4) = 2;
  GHIDRA_FIELD(cgs, 33822780, 4) = g_unk_010906e0 + 500;
  return 1;
}

void nitrox_ScreenshotMD5(uint32_t param_1)
{
  void *__ptr;
  size_t tmp_s1;
  uint8_t local_84 [16];
  uint8_t local_74 [100];
  
  __ptr = malloc(GHIDRA_FIELD(cgs, 33823044, 4));
  MD5Init(local_74);
  tmp_s1 = fread(__ptr,1,GHIDRA_FIELD(cgs, 33823044, 4),(FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
  MD5Update(local_74,__ptr,tmp_s1);
  MD5Final(local_84,local_74);
  MD5toStr(local_84,param_1);
  free(__ptr);
  return;
}

void nitrox_InitFileTransfer(void)
{
  uint tmp_u1;
  uint tmp_u2;
  void *__ptr;
  size_t tmp_s3;
  uint8_t *tmp_pu4;
  uint32_t tmp_u5;
  uint8_t local_a5 [16];
  uint32_t local_95;
  uint8_t local_91;
  uint32_t local_90 [7];
  uint8_t local_74 [100];
  
  local_95 = 0;
  local_91 = 0;
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_90 + tmp_u2) = 0;
    *(uint32_t *)((int)local_90 + tmp_u2 + 4) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0x18);
  *(uint32_t *)((int)local_90 + tmp_u2 + 8) = 0;
  __ptr = malloc(GHIDRA_FIELD(cgs, 33823044, 4));
  MD5Init(local_74);
  tmp_s3 = fread(__ptr,1,GHIDRA_FIELD(cgs, 33823044, 4),(FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
  MD5Update(local_74,__ptr,tmp_s3);
  MD5Final(local_a5,local_74);
  MD5toStr(local_a5,&local_95);
  free(__ptr);
  if (GHIDRA_FIELD(cgs, 33823104, 4) == 0) {
    tmp_pu4 = &g_unk_00122185;
  }
  else {
    tmp_pu4 = &g_unk_00122181;
  }
  tmp_u5 = va("ift \\fs\\%ld\\ext\\%s\\csm\\%s\\",GHIDRA_FIELD(cgs, 33823044, 4),tmp_pu4,&local_95);
  nitrox_TCPSend(tmp_u5);
  GHIDRA_FIELD(cgs, 33822776, 4) = 4;
  GHIDRA_FIELD(cgs, 33822780, 4) = g_unk_010906e0 + 500;
  return;
}

uint32_t nitrox_OpenScreenshotFile(void)
{
  GHIDRA_FIELD(cgs, 33823040, 4) = fopen(cgs + 0x2041840,"rb");
  if ((FILE *)GHIDRA_FIELD(cgs, 33823040, 4) != (FILE *)0x0) {
    fseek((FILE *)GHIDRA_FIELD(cgs, 33823040, 4),0,2);
    GHIDRA_FIELD(cgs, 33823044, 4) = ftell((FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
    rewind((FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
    return 1;
  }
  cgs[0x2041840] = 0;
  GHIDRA_FIELD(cgs, 33823044, 4) = 0;
  GHIDRA_FIELD(cgs, 33822776, 4) = 0;
  return 0;
}

void nitrox_CacheScreenshot(void)
{
  uint32_t __n;
  
  __n = GHIDRA_FIELD(cgs, 33823044, 4);
  GHIDRA_FIELD(cgs, 33823060, 4) = malloc(GHIDRA_FIELD(cgs, 33823044, 4));
  fread((void *)GHIDRA_FIELD(cgs, 33823060, 4),1,__n,(FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
  rewind((FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
  return;
}

void nitrox_PrepareScreenshot(void)
{
  uint32_t __n;
  
  GHIDRA_FIELD(cgs, 33823040, 4) = fopen(cgs + 0x2041840,"rb");
  if ((FILE *)GHIDRA_FIELD(cgs, 33823040, 4) != (FILE *)0x0) {
    fseek((FILE *)GHIDRA_FIELD(cgs, 33823040, 4),0,2);
    GHIDRA_FIELD(cgs, 33823044, 4) = ftell((FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
    rewind((FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
    __n = GHIDRA_FIELD(cgs, 33823044, 4);
    GHIDRA_FIELD(cgs, 33823060, 4) = malloc(GHIDRA_FIELD(cgs, 33823044, 4));
    fread((void *)GHIDRA_FIELD(cgs, 33823060, 4),1,__n,(FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
    rewind((FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
    GHIDRA_FIELD(cgs, 33822776, 4) = 3;
    GHIDRA_FIELD(cgs, 33822780, 4) = g_unk_010906e0 + 500;
    return;
  }
  GHIDRA_FIELD(cgs, 33823044, 4) = 0;
  cgs[0x2041840] = 0;
  GHIDRA_FIELD(cgs, 33822776, 4) = 0;
  return;
}

void nitrox_FreeScreenshot(void)
{
  if (GHIDRA_FIELD(cgs, 33823040, 4) != 0) {
    fclose((FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
  }
  remove(cgs + 0x2041840);
  GHIDRA_FIELD(cgs, 33823052, 4) = 0;
  GHIDRA_FIELD(cgs, 33823064, 4) = 0;
  GHIDRA_FIELD(cgs, 33823040, 4) = 0;
  cgs[0x2041840] = 0;
  GHIDRA_FIELD(cgs, 33823044, 4) = 0;
  if (GHIDRA_FIELD(cgs, 33823060, 4) != 0) {
    free((void *)GHIDRA_FIELD(cgs, 33823060, 4));
  }
  GHIDRA_FIELD(cgs, 33823060, 4) = 0;
  return;
}

void nitrox_ScreenshotThink(void)
{
  uint32_t __n;
  int tmp_i1;
  
  if ((int)GHIDRA_FIELD(cgs, 33822780, 4) < g_unk_010906e0) {
    switch(GHIDRA_FIELD(cgs, 33822776, 4)) {
    case 1:
      tmp_i1 = nitrox_Screenshot();
      if (tmp_i1 != 0) {
        nitrox_TCPOpen();
      }
      break;
    case 2:
      tmp_i1 = nitrox_TCPConnect();
      if (tmp_i1 == 0) {
        GHIDRA_FIELD(cgs, 33823112, 4) = GHIDRA_FIELD(cgs, 33823112, 4) | 0x80;
        GHIDRA_FIELD(cgs, 33822776, 4) = 0;
      }
      else {
        GHIDRA_FIELD(cgs, 33823040, 4) = fopen(cgs + 0x2041840,"rb");
        if ((FILE *)GHIDRA_FIELD(cgs, 33823040, 4) == (FILE *)0x0) {
          GHIDRA_FIELD(cgs, 33823044, 4) = 0;
          cgs[0x2041840] = 0;
          GHIDRA_FIELD(cgs, 33822776, 4) = 0;
        }
        else {
          fseek((FILE *)GHIDRA_FIELD(cgs, 33823040, 4),0,2);
          GHIDRA_FIELD(cgs, 33823044, 4) = ftell((FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
          rewind((FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
          __n = GHIDRA_FIELD(cgs, 33823044, 4);
          GHIDRA_FIELD(cgs, 33823060, 4) = malloc(GHIDRA_FIELD(cgs, 33823044, 4));
          fread((void *)GHIDRA_FIELD(cgs, 33823060, 4),1,__n,(FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
          rewind((FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
          GHIDRA_FIELD(cgs, 33822776, 4) = 3;
          GHIDRA_FIELD(cgs, 33822780, 4) = g_unk_010906e0 + 500;
        }
      }
      break;
    case 3:
      nitrox_InitFileTransfer();
      return;
    case 5:
      nitrox_SendScreenshot();
      break;
    case 6:
      if (GHIDRA_FIELD(cgs, 33823040, 4) != 0) {
        fclose((FILE *)GHIDRA_FIELD(cgs, 33823040, 4));
      }
      remove(cgs + 0x2041840);
      GHIDRA_FIELD(cgs, 33823064, 4) = 0;
      GHIDRA_FIELD(cgs, 33823040, 4) = 0;
      cgs[0x2041840] = 0;
      GHIDRA_FIELD(cgs, 33823044, 4) = 0;
      GHIDRA_FIELD(cgs, 33823052, 4) = 0;
      if (GHIDRA_FIELD(cgs, 33823060, 4) != 0) {
        free((void *)GHIDRA_FIELD(cgs, 33823060, 4));
      }
      GHIDRA_FIELD(cgs, 33823060, 4) = 0;
      break;
    case 7:
      nitrox_TCPSend(&g_unk_00118bb6);
      nitrox_TCPClose();
      GHIDRA_FIELD(cgs, 33822776, 4) = 0;
    }
  }
  return;
}

void MD5Transform(int *param_1,int param_2)
{
  int tmp_i1;
  uint tmp_u2;
  uint tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  uint tmp_u6;
  uint tmp_u7;
  uint tmp_u8;
  uint tmp_u9;
  uint tmp_u10;
  uint tmp_u11;
  uint tmp_u12;
  uint local_4c [16];
  
  tmp_i1 = *param_1;
  tmp_u2 = param_1[1];
  tmp_u3 = param_1[2];
  tmp_u4 = param_1[3];
  tmp_i5 = 0;
  do {
    *(uint *)((int)local_4c + tmp_i5) =
         (uint)*(byte *)(param_2 + 2 + tmp_i5) << 0x10 | (uint)*(byte *)(param_2 + 1 + tmp_i5) << 8 |
         (uint)*(byte *)(param_2 + tmp_i5) | (uint)*(byte *)(param_2 + 3 + tmp_i5) << 0x18;
    tmp_i5 = tmp_i5 + 4;
  } while (tmp_i5 != 0x40);
  tmp_u6 = (tmp_u3 & tmp_u2 | ~tmp_u2 & tmp_u4) + tmp_i1 + -0x28955b88 + local_4c[0];
  tmp_u6 = (tmp_u6 * 0x80 | tmp_u6 >> 0x19) + tmp_u2;
  tmp_u7 = (tmp_u2 & tmp_u6 | ~tmp_u6 & tmp_u3) + tmp_u4 + 0xe8c7b756 + local_4c[1];
  tmp_u7 = (tmp_u7 * 0x1000 | tmp_u7 >> 0x14) + tmp_u6;
  tmp_u8 = (tmp_u7 & tmp_u6 | ~tmp_u7 & tmp_u2) + tmp_u3 + 0x242070db + local_4c[2];
  tmp_u8 = (tmp_u8 >> 0xf | tmp_u8 * 0x20000) + tmp_u7;
  tmp_u11 = (tmp_u8 & tmp_u7 | ~tmp_u8 & tmp_u6) + tmp_u2 + 0xc1bdceee + local_4c[3];
  tmp_u11 = (tmp_u11 >> 10 | tmp_u11 * 0x400000) + tmp_u8;
  tmp_u6 = (tmp_u11 & tmp_u8 | ~tmp_u11 & tmp_u7) + tmp_u6 + 0xf57c0faf + local_4c[4];
  tmp_u6 = (tmp_u6 * 0x80 | tmp_u6 >> 0x19) + tmp_u11;
  tmp_u7 = (tmp_u6 & tmp_u11 | ~tmp_u6 & tmp_u8) + tmp_u7 + 0x4787c62a + local_4c[5];
  tmp_u7 = (tmp_u7 * 0x1000 | tmp_u7 >> 0x14) + tmp_u6;
  tmp_u8 = (tmp_u7 & tmp_u6 | ~tmp_u7 & tmp_u11) + tmp_u8 + 0xa8304613 + local_4c[6];
  tmp_u8 = (tmp_u8 >> 0xf | tmp_u8 * 0x20000) + tmp_u7;
  tmp_u11 = (tmp_u8 & tmp_u7 | ~tmp_u8 & tmp_u6) + tmp_u11 + 0xfd469501 + local_4c[7];
  tmp_u11 = (tmp_u11 >> 10 | tmp_u11 * 0x400000) + tmp_u8;
  tmp_u6 = (tmp_u11 & tmp_u8 | ~tmp_u11 & tmp_u7) + tmp_u6 + 0x698098d8 + local_4c[8];
  tmp_u6 = (tmp_u6 * 0x80 | tmp_u6 >> 0x19) + tmp_u11;
  tmp_u7 = (tmp_u6 & tmp_u11 | ~tmp_u6 & tmp_u8) + tmp_u7 + 0x8b44f7af + local_4c[9];
  tmp_u7 = (tmp_u7 * 0x1000 | tmp_u7 >> 0x14) + tmp_u6;
  tmp_u8 = (tmp_u7 & tmp_u6 | ~tmp_u7 & tmp_u11) + (tmp_u8 - 0xa44f) + local_4c[10];
  tmp_u8 = (tmp_u8 >> 0xf | tmp_u8 * 0x20000) + tmp_u7;
  tmp_u11 = (tmp_u8 & tmp_u7 | ~tmp_u8 & tmp_u6) + tmp_u11 + 0x895cd7be + local_4c[0xb];
  tmp_u11 = (tmp_u11 >> 10 | tmp_u11 * 0x400000) + tmp_u8;
  tmp_u6 = (tmp_u11 & tmp_u8 | ~tmp_u11 & tmp_u7) + tmp_u6 + 0x6b901122 + local_4c[0xc];
  tmp_u6 = (tmp_u6 * 0x80 | tmp_u6 >> 0x19) + tmp_u11;
  tmp_u7 = (tmp_u6 & tmp_u11 | ~tmp_u6 & tmp_u8) + tmp_u7 + 0xfd987193 + local_4c[0xd];
  tmp_u7 = (tmp_u7 * 0x1000 | tmp_u7 >> 0x14) + tmp_u6;
  tmp_u8 = tmp_u8 + 0xa679438e + local_4c[0xe] + (tmp_u7 & tmp_u6 | ~tmp_u7 & tmp_u11);
  tmp_u9 = (tmp_u8 >> 0xf | tmp_u8 * 0x20000) + tmp_u7;
  tmp_u8 = tmp_u11 + 0x49b40821 + local_4c[0xf] + (tmp_u9 & tmp_u7 | ~tmp_u9 & tmp_u6);
  tmp_u11 = (tmp_u8 >> 10 | tmp_u8 * 0x400000) + tmp_u9;
  tmp_u6 = local_4c[1] + -0x9e1da9e + tmp_u6 + (~tmp_u7 & tmp_u9 | tmp_u11 & tmp_u7);
  tmp_u8 = (tmp_u6 * 0x20 | tmp_u6 >> 0x1b) + tmp_u11;
  tmp_u6 = (tmp_u8 & tmp_u9 | ~tmp_u9 & tmp_u11) + local_4c[6] + -0x3fbf4cc0 + tmp_u7;
  tmp_u7 = (tmp_u6 * 0x200 | tmp_u6 >> 0x17) + tmp_u8;
  tmp_u6 = local_4c[0xb] + 0x265e5a51 + tmp_u9 + (~tmp_u11 & tmp_u8 | tmp_u7 & tmp_u11);
  tmp_u12 = (tmp_u6 * 0x4000 | tmp_u6 >> 0x12) + tmp_u7;
  tmp_u6 = local_4c[0] + 0xe9b6c7aa + tmp_u11 + (~tmp_u8 & tmp_u7 | tmp_u12 & tmp_u8);
  tmp_u10 = (tmp_u6 >> 0xc | tmp_u6 * 0x100000) + tmp_u12;
  tmp_u6 = local_4c[5] + -0x29d0efa3 + tmp_u8 + (~tmp_u7 & tmp_u12 | tmp_u10 & tmp_u7);
  tmp_u9 = (tmp_u6 * 0x20 | tmp_u6 >> 0x1b) + tmp_u10;
  tmp_u6 = local_4c[10] + 0x2441453 + tmp_u7 + (~tmp_u12 & tmp_u10 | tmp_u9 & tmp_u12);
  tmp_u8 = (tmp_u6 * 0x200 | tmp_u6 >> 0x17) + tmp_u9;
  tmp_u6 = local_4c[0xf] + -0x275e197f + tmp_u12 + (~tmp_u10 & tmp_u9 | tmp_u8 & tmp_u10);
  tmp_u11 = (tmp_u6 * 0x4000 | tmp_u6 >> 0x12) + tmp_u8;
  tmp_u6 = local_4c[4] + -0x182c0438 + tmp_u10 + (~tmp_u9 & tmp_u8 | tmp_u11 & tmp_u9);
  tmp_u10 = (tmp_u6 >> 0xc | tmp_u6 * 0x100000) + tmp_u11;
  tmp_u6 = local_4c[9] + 0x21e1cde6 + tmp_u9 + (~tmp_u8 & tmp_u11 | tmp_u10 & tmp_u8);
  tmp_u7 = (tmp_u6 * 0x20 | tmp_u6 >> 0x1b) + tmp_u10;
  tmp_u6 = local_4c[0xe] + -0x3cc8f82a + tmp_u8 + (~tmp_u11 & tmp_u10 | tmp_u7 & tmp_u11);
  tmp_u8 = (tmp_u6 * 0x200 | tmp_u6 >> 0x17) + tmp_u7;
  tmp_u6 = local_4c[3] + -0xb2af279 + tmp_u11 + (~tmp_u10 & tmp_u7 | tmp_u8 & tmp_u10);
  tmp_u12 = (tmp_u6 * 0x4000 | tmp_u6 >> 0x12) + tmp_u8;
  tmp_u6 = local_4c[8] + 0x455a14ed + tmp_u10 + (~tmp_u7 & tmp_u8 | tmp_u12 & tmp_u7);
  tmp_u11 = (tmp_u6 >> 0xc | tmp_u6 * 0x100000) + tmp_u12;
  tmp_u6 = local_4c[0xd] + -0x561c16fb + tmp_u7 + (~tmp_u8 & tmp_u12 | tmp_u11 & tmp_u8);
  tmp_u7 = (tmp_u6 * 0x20 | tmp_u6 >> 0x1b) + tmp_u11;
  tmp_u6 = local_4c[2] + -0x3105c08 + tmp_u8 + (~tmp_u12 & tmp_u11 | tmp_u7 & tmp_u12);
  tmp_u9 = (tmp_u6 * 0x200 | tmp_u6 >> 0x17) + tmp_u7;
  tmp_u6 = local_4c[7] + 0x676f02d9 + tmp_u12 + (~tmp_u11 & tmp_u7 | tmp_u9 & tmp_u11);
  tmp_u8 = (tmp_u6 * 0x4000 | tmp_u6 >> 0x12) + tmp_u9;
  tmp_u6 = local_4c[0xc] + -0x72d5b376 + tmp_u11 + (~tmp_u7 & tmp_u9 | tmp_u8 & tmp_u7);
  tmp_u10 = (tmp_u6 >> 0xc | tmp_u6 * 0x100000) + tmp_u8;
  tmp_u6 = (tmp_u8 ^ tmp_u9 ^ tmp_u10) + local_4c[5] + -0x5c6be + tmp_u7;
  tmp_u6 = (tmp_u6 * 0x10 | tmp_u6 >> 0x1c) + tmp_u10;
  tmp_u7 = (tmp_u10 ^ tmp_u8 ^ tmp_u6) + local_4c[8] + -0x788e097f + tmp_u9;
  tmp_u11 = (tmp_u7 * 0x800 | tmp_u7 >> 0x15) + tmp_u6;
  tmp_u7 = (tmp_u6 ^ tmp_u10 ^ tmp_u11) + local_4c[0xb] + 0x6d9d6122 + tmp_u8;
  tmp_u7 = (tmp_u7 * 0x10000 | tmp_u7 >> 0x10) + tmp_u11;
  tmp_u8 = (tmp_u11 ^ tmp_u6 ^ tmp_u7) + local_4c[0xe] + -0x21ac7f4 + tmp_u10;
  tmp_u9 = (tmp_u8 >> 9 | tmp_u8 * 0x800000) + tmp_u7;
  tmp_u6 = (tmp_u7 ^ tmp_u11 ^ tmp_u9) + local_4c[1] + -0x5b4115bc + tmp_u6;
  tmp_u8 = (tmp_u6 * 0x10 | tmp_u6 >> 0x1c) + tmp_u9;
  tmp_u6 = (tmp_u9 ^ tmp_u7 ^ tmp_u8) + local_4c[4] + 0x4bdecfa9 + tmp_u11;
  tmp_u6 = (tmp_u6 * 0x800 | tmp_u6 >> 0x15) + tmp_u8;
  tmp_u7 = (tmp_u8 ^ tmp_u9 ^ tmp_u6) + local_4c[7] + -0x944b4a0 + tmp_u7;
  tmp_u7 = (tmp_u7 * 0x10000 | tmp_u7 >> 0x10) + tmp_u6;
  tmp_u11 = (tmp_u6 ^ tmp_u8 ^ tmp_u7) + local_4c[10] + -0x41404390 + tmp_u9;
  tmp_u9 = (tmp_u11 >> 9 | tmp_u11 * 0x800000) + tmp_u7;
  tmp_u8 = (tmp_u7 ^ tmp_u6 ^ tmp_u9) + local_4c[0xd] + 0x289b7ec6 + tmp_u8;
  tmp_u8 = (tmp_u8 * 0x10 | tmp_u8 >> 0x1c) + tmp_u9;
  tmp_u6 = (tmp_u9 ^ tmp_u7 ^ tmp_u8) + local_4c[0] + 0xeaa127fa + tmp_u6;
  tmp_u6 = (tmp_u6 * 0x800 | tmp_u6 >> 0x15) + tmp_u8;
  tmp_u7 = (tmp_u8 ^ tmp_u9 ^ tmp_u6) + local_4c[3] + -0x2b10cf7b + tmp_u7;
  tmp_u11 = (tmp_u7 * 0x10000 | tmp_u7 >> 0x10) + tmp_u6;
  tmp_u7 = (tmp_u6 ^ tmp_u8 ^ tmp_u11) + local_4c[6] + 0x4881d05 + tmp_u9;
  tmp_u7 = (tmp_u7 >> 9 | tmp_u7 * 0x800000) + tmp_u11;
  tmp_u8 = (tmp_u11 ^ tmp_u6 ^ tmp_u7) + local_4c[9] + -0x262b2fc7 + tmp_u8;
  tmp_u8 = (tmp_u8 * 0x10 | tmp_u8 >> 0x1c) + tmp_u7;
  tmp_u6 = (tmp_u7 ^ tmp_u11 ^ tmp_u8) + local_4c[0xc] + -0x1924661b + tmp_u6;
  tmp_u9 = (tmp_u6 * 0x800 | tmp_u6 >> 0x15) + tmp_u8;
  tmp_u6 = (tmp_u8 ^ tmp_u7 ^ tmp_u9) + local_4c[0xf] + 0x1fa27cf8 + tmp_u11;
  tmp_u6 = (tmp_u6 * 0x10000 | tmp_u6 >> 0x10) + tmp_u9;
  tmp_u7 = (tmp_u9 ^ tmp_u8 ^ tmp_u6) + local_4c[2] + -0x3b53a99b + tmp_u7;
  tmp_u7 = (tmp_u7 >> 9 | tmp_u7 * 0x800000) + tmp_u6;
  tmp_u8 = ((~tmp_u9 | tmp_u7) ^ tmp_u6) + local_4c[0] + 0xf4292244 + tmp_u8;
  tmp_u11 = (tmp_u8 * 0x40 | tmp_u8 >> 0x1a) + tmp_u7;
  tmp_u8 = ((~tmp_u6 | tmp_u11) ^ tmp_u7) + local_4c[7] + 0x432aff97 + tmp_u9;
  tmp_u8 = (tmp_u8 * 0x400 | tmp_u8 >> 0x16) + tmp_u11;
  tmp_u6 = ((~tmp_u7 | tmp_u8) ^ tmp_u11) + local_4c[0xe] + -0x546bdc59 + tmp_u6;
  tmp_u6 = (tmp_u6 * 0x8000 | tmp_u6 >> 0x11) + tmp_u8;
  tmp_u7 = ((~tmp_u11 | tmp_u6) ^ tmp_u8) + local_4c[5] + -0x36c5fc7 + tmp_u7;
  tmp_u9 = (tmp_u7 >> 0xb | tmp_u7 * 0x200000) + tmp_u6;
  tmp_u7 = ((~tmp_u8 | tmp_u9) ^ tmp_u6) + local_4c[0xc] + 0x655b59c3 + tmp_u11;
  tmp_u7 = (tmp_u7 * 0x40 | tmp_u7 >> 0x1a) + tmp_u9;
  tmp_u8 = ((~tmp_u6 | tmp_u7) ^ tmp_u9) + local_4c[3] + -0x70f3336e + tmp_u8;
  tmp_u8 = (tmp_u8 * 0x400 | tmp_u8 >> 0x16) + tmp_u7;
  tmp_u6 = ((~tmp_u9 | tmp_u8) ^ tmp_u7) + local_4c[10] + -0x100b83 + tmp_u6;
  tmp_u11 = (tmp_u6 * 0x8000 | tmp_u6 >> 0x11) + tmp_u8;
  tmp_u6 = ((~tmp_u7 | tmp_u11) ^ tmp_u8) + local_4c[1] + -0x7a7ba22f + tmp_u9;
  tmp_u6 = (tmp_u6 >> 0xb | tmp_u6 * 0x200000) + tmp_u11;
  tmp_u7 = ((~tmp_u8 | tmp_u6) ^ tmp_u11) + local_4c[8] + 0x6fa87e4f + tmp_u7;
  tmp_u7 = (tmp_u7 * 0x40 | tmp_u7 >> 0x1a) + tmp_u6;
  tmp_u8 = ((~tmp_u11 | tmp_u7) ^ tmp_u6) + local_4c[0xf] + -0x1d31920 + tmp_u8;
  tmp_u9 = (tmp_u8 * 0x400 | tmp_u8 >> 0x16) + tmp_u7;
  tmp_u8 = ((~tmp_u6 | tmp_u9) ^ tmp_u7) + local_4c[6] + -0x5cfebcec + tmp_u11;
  tmp_u8 = (tmp_u8 * 0x8000 | tmp_u8 >> 0x11) + tmp_u9;
  tmp_u6 = ((~tmp_u7 | tmp_u8) ^ tmp_u9) + local_4c[0xd] + 0x4e0811a1 + tmp_u6;
  tmp_u6 = (tmp_u6 >> 0xb | tmp_u6 * 0x200000) + tmp_u8;
  tmp_u7 = ((~tmp_u9 | tmp_u6) ^ tmp_u8) + local_4c[4] + -0x8ac817e + tmp_u7;
  tmp_u7 = (tmp_u7 * 0x40 | tmp_u7 >> 0x1a) + tmp_u6;
  tmp_u11 = ((~tmp_u8 | tmp_u7) ^ tmp_u6) + local_4c[0xb] + -0x42c50dcb + tmp_u9;
  tmp_u11 = (tmp_u11 * 0x400 | tmp_u11 >> 0x16) + tmp_u7;
  tmp_u8 = ((~tmp_u6 | tmp_u11) ^ tmp_u7) + local_4c[2] + 0x2ad7d2bb + tmp_u8;
  tmp_u8 = (tmp_u8 * 0x8000 | tmp_u8 >> 0x11) + tmp_u11;
  tmp_u6 = ((~tmp_u7 | tmp_u8) ^ tmp_u11) + local_4c[9] + -0x14792c6f + tmp_u6;
  *param_1 = tmp_u7 + tmp_i1;
  param_1[1] = (tmp_u6 >> 0xb | tmp_u6 * 0x200000) + tmp_u8 + tmp_u2;
  param_1[2] = tmp_u8 + tmp_u3;
  param_1[3] = tmp_u11 + tmp_u4;
  return;
}

void MD5Init(uint32_t *param_1)
{
  param_1[5] = 0;
  param_1[4] = 0;
  *param_1 = 0x67452301;
  param_1[1] = 0xefcdab89;
  param_1[2] = 0x98badcfe;
  param_1[3] = 0x10325476;
  return;
}

void MD5Update(int param_1,uint32_t *param_2,uint param_3)
{
  uint32_t *tmp_pu1;
  uint tmp_u2;
  int tmp_i3;
  uint tmp_u4;
  uint tmp_u5;
  uint tmp_u6;
  uint tmp_u7;
  
  tmp_u5 = *(uint *)(param_1 + 0x10) >> 3 & 0x3f;
  tmp_u7 = param_3 * 8;
  tmp_u2 = *(uint *)(param_1 + 0x10) + tmp_u7;
  *(uint *)(param_1 + 0x10) = tmp_u2;
  if (tmp_u7 < tmp_u2 || tmp_u7 - tmp_u2 == 0) {
    tmp_i3 = *(int *)(param_1 + 0x14);
  }
  else {
    tmp_i3 = *(int *)(param_1 + 0x14) + 1;
  }
  tmp_u7 = 0x40 - tmp_u5;
  *(uint *)(param_1 + 0x14) = (param_3 >> 0x1d) + tmp_i3;
  if (param_3 < tmp_u7) {
    tmp_u4 = 0;
    tmp_u2 = param_1 + 0x18 + tmp_u5;
  }
  else {
    tmp_pu1 = (uint32_t *)(param_1 + 0x18 + tmp_u5);
    if ((param_2 < (uint32_t *)(param_1 + 0x1c + tmp_u5) && tmp_pu1 < param_2 + 1 || tmp_u7 < 10) ||
       ((((uint)tmp_pu1 | (uint)param_2) & 3) != 0)) {
      tmp_u2 = 0;
      do {
        *(uint8_t *)((int)tmp_pu1 + tmp_u2) = *(uint8_t *)((int)param_2 + tmp_u2);
        tmp_u2 = tmp_u2 + 1;
      } while (tmp_u2 != tmp_u7);
    }
    else {
      tmp_i3 = (0x3c - tmp_u5 >> 2) + 1;
      *tmp_pu1 = *param_2;
      tmp_u2 = tmp_i3 * 4;
      tmp_pu1[1] = param_2[1];
      if ((((((tmp_i3 != 2) && (tmp_pu1[2] = param_2[2], tmp_i3 != 3)) &&
            (tmp_pu1[3] = param_2[3], tmp_i3 != 4)) &&
           ((tmp_pu1[4] = param_2[4], tmp_i3 != 5 && (tmp_pu1[5] = param_2[5], tmp_i3 != 6)))) &&
          ((tmp_pu1[6] = param_2[6], tmp_i3 != 7 &&
           ((tmp_pu1[7] = param_2[7], tmp_i3 != 8 && (tmp_pu1[8] = param_2[8], tmp_i3 != 9)))))) &&
         ((tmp_pu1[9] = param_2[9], tmp_i3 != 10 &&
          ((((tmp_pu1[10] = param_2[10], tmp_i3 != 0xb && (tmp_pu1[0xb] = param_2[0xb], tmp_i3 != 0xc))
            && (tmp_pu1[0xc] = param_2[0xc], tmp_i3 != 0xd)) &&
           ((tmp_pu1[0xd] = param_2[0xd], tmp_i3 != 0xe && (tmp_pu1[0xe] = param_2[0xe], tmp_i3 == 0x10)
            ))))))) {
        tmp_pu1[0xf] = param_2[0xf];
      }
      if ((tmp_u7 != tmp_u2) &&
         (*(uint8_t *)(tmp_pu1 + tmp_i3) = *(uint8_t *)(param_2 + tmp_i3), tmp_u2 + 1 < tmp_u7)) {
        *(uint8_t *)((int)tmp_pu1 + tmp_u2 + 1) = *(uint8_t *)((int)param_2 + tmp_u2 + 1);
        tmp_u2 = tmp_u2 + 2;
        if (tmp_u2 < tmp_u7) {
          *(uint8_t *)((int)tmp_pu1 + tmp_u2) = *(uint8_t *)((int)param_2 + tmp_u2);
        }
      }
    }
    tmp_u2 = param_1 + 0x18;
    MD5Transform();
    tmp_u5 = -tmp_u5;
    while (tmp_u4 = tmp_u7, tmp_u5 + 0x7f < param_3) {
      MD5Transform();
      tmp_u7 = tmp_u4 + 0x40;
      tmp_u5 = tmp_u4;
    }
  }
  param_3 = param_3 - tmp_u4;
  if (param_3 != 0) {
    tmp_u7 = (int)param_2 + tmp_u4;
    if ((tmp_u2 < (int)param_2 + tmp_u4 + 4 && tmp_u7 < tmp_u2 + 4 || param_3 < 10) ||
       (((tmp_u2 | tmp_u7) & 3) != 0)) {
      tmp_u5 = 0;
      do {
        *(uint8_t *)(tmp_u2 + tmp_u5) = *(uint8_t *)(tmp_u7 + tmp_u5);
        tmp_u5 = tmp_u5 + 1;
      } while (tmp_u5 != param_3);
      return;
    }
    tmp_u4 = 0;
    tmp_u6 = (param_3 - 4 >> 2) + 1;
    tmp_u5 = tmp_u6 * 4;
    do {
      *(uint32_t *)(tmp_u2 + tmp_u4 * 4) = *(uint32_t *)(tmp_u7 + tmp_u4 * 4);
      tmp_u4 = tmp_u4 + 1;
    } while (tmp_u4 < tmp_u6);
    if ((param_3 != tmp_u5) &&
       (*(uint8_t *)(tmp_u2 + tmp_u5) = *(uint8_t *)(tmp_u7 + tmp_u5), tmp_u5 + 1 < param_3)) {
      *(uint8_t *)(tmp_u2 + 1 + tmp_u5) = *(uint8_t *)(tmp_u5 + 1 + tmp_u7);
      tmp_u5 = tmp_u5 + 2;
      if (tmp_u5 < param_3) {
        *(uint8_t *)(tmp_u2 + tmp_u5) = *(uint8_t *)(tmp_u7 + tmp_u5);
      }
    }
  }
  return;
}

void MD5Final(uint8_t *param_1,uint32_t *param_2)
{
  uint8_t tmp_u1;
  uint16_t tmp_u2;
  uint32_t tmp_u3;
  uint tmp_u4;
  uint32_t *tmp_pu5;
  uint16_t *tmp_pu6;
  uint tmp_u7;
  int tmp_i8;
  uint32_t *tmp_pu9;
  uint tmp_u10;
  uint16_t *tmp_pu11;
  uint16_t *tmp_pu12;
  uint32_t *tmp_pu13;
  uint32_t *tmp_pu14;
  bool tmp_b15;
  byte tmp_b16;
  uint local_30;
  uint local_2c;
  uint8_t local_18 [2];
  uint8_t uStack_16;
  uint8_t uStack_15;
  uint8_t local_14;
  uint8_t local_13;
  uint8_t local_12;
  uint8_t local_11;
  
  tmp_b16 = 0;
  tmp_u4 = param_2[4];
  local_18[1] = (char)(tmp_u4 >> 8);
  uStack_16 = (char)(tmp_u4 >> 0x10);
  uStack_15 = (char)(tmp_u4 >> 0x18);
  tmp_i8 = param_2[5];
  local_18[0] = (char)tmp_u4;
  local_13 = (char)((uint)tmp_i8 >> 8);
  local_12 = (char)((uint)tmp_i8 >> 0x10);
  local_11 = (char)((uint)tmp_i8 >> 0x18);
  tmp_u7 = tmp_u4 >> 3 & 0x3f;
  local_14 = (char)tmp_i8;
  if (tmp_u7 < 0x38) {
    local_2c = 0x38 - tmp_u7;
  }
  else {
    local_2c = 0x78 - tmp_u7;
  }
  tmp_u10 = local_2c * 8;
  tmp_u4 = tmp_u4 + tmp_u10;
  param_2[4] = tmp_u4;
  if (tmp_u4 <= tmp_u10 && tmp_u10 - tmp_u4 != 0) {
    param_2[5] = tmp_i8 + 1;
  }
  local_30 = 0x40 - tmp_u7;
  tmp_pu5 = (uint32_t *)((int)param_2 + tmp_u7 + 0x18);
  if (local_2c < local_30) {
    local_30 = 0;
LAB_0010ba57:
    tmp_pu9 = (uint32_t *)(&PADDING + local_30);
    if ((tmp_pu9 < tmp_pu5 + 1 && tmp_pu5 < (uint32_t *)((int)&g_unk_0014b384 + local_30) ||
         local_2c < 10) || ((((uint)tmp_pu5 | (uint)tmp_pu9) & 3) != 0)) {
      tmp_u4 = 0;
      do {
        *(uint8_t *)((int)tmp_pu5 + tmp_u4) = *(uint8_t *)((int)tmp_pu9 + tmp_u4);
        tmp_u4 = tmp_u4 + 1;
      } while (tmp_u4 != local_2c);
    }
    else {
      tmp_u10 = (local_2c - 4 >> 2) + 1;
      tmp_u4 = tmp_u10 * 4;
      tmp_u7 = 0;
      do {
        tmp_pu5[tmp_u7] = tmp_pu9[tmp_u7];
        tmp_u7 = tmp_u7 + 1;
      } while (tmp_u7 < tmp_u10);
      if (local_2c != tmp_u4) {
        *(uint8_t *)(tmp_pu5 + tmp_u10) = (&PADDING)[local_30 + tmp_u4];
        tmp_u7 = tmp_u4 + 1;
        if (tmp_u7 < local_2c) {
          *(uint8_t *)((int)tmp_pu5 + tmp_u7) = (&PADDING)[local_30 + tmp_u7];
          tmp_u4 = tmp_u4 + 2;
          if (tmp_u4 < local_2c) {
            *(uint8_t *)((int)tmp_pu5 + tmp_u4) = (&PADDING)[local_30 + tmp_u4];
          }
        }
      }
    }
  }
  else {
    if ((&PADDING < (uint8_t *)((int)param_2 + tmp_u7 + 0x1c) && tmp_pu5 < &g_unk_0014b384 ||
         local_30 < 9) || (((uint)tmp_pu5 & 3) != 0)) {
      tmp_u4 = 0;
      do {
        *(uint8_t *)((int)tmp_pu5 + tmp_u4) = (&PADDING)[tmp_u4];
        tmp_u4 = tmp_u4 + 1;
      } while (tmp_u4 != local_30);
    }
    else {
      tmp_i8 = (0x3c - tmp_u7 >> 2) + 1;
      tmp_u4 = tmp_i8 * 4;
      *tmp_pu5 = _PADDING;
      tmp_pu5[1] = g_unk_0014b384;
      if ((((((tmp_i8 != 2) && (tmp_pu5[2] = g_unk_0014b388, tmp_i8 != 3)) &&
            (tmp_pu5[3] = g_unk_0014b38c, tmp_i8 != 4)) &&
           ((tmp_pu5[4] = g_unk_0014b390, tmp_i8 != 5 && (tmp_pu5[5] = g_unk_0014b394, tmp_i8 != 6)))) &&
          ((tmp_pu5[6] = g_unk_0014b398, tmp_i8 != 7 &&
           ((tmp_pu5[7] = g_unk_0014b39c, tmp_i8 != 8 && (tmp_pu5[8] = g_unk_0014b3a0, tmp_i8 != 9)))))) &&
         ((tmp_pu5[9] = g_unk_0014b3a4, tmp_i8 != 10 &&
          ((((tmp_pu5[10] = g_unk_0014b3a8, tmp_i8 != 0xb && (tmp_pu5[0xb] = g_unk_0014b3ac, tmp_i8 != 0xc))
            && (tmp_pu5[0xc] = g_unk_0014b3b0, tmp_i8 != 0xd)) &&
           ((tmp_pu5[0xd] = g_unk_0014b3b4, tmp_i8 != 0xe && (tmp_pu5[0xe] = g_unk_0014b3b8, tmp_i8 == 0x10)
            ))))))) {
        tmp_pu5[0xf] = g_unk_0014b3bc;
      }
      if (tmp_u4 != local_30) {
        *(uint8_t *)(tmp_pu5 + tmp_i8) = (&PADDING)[tmp_u4];
        if (tmp_u4 + 1 < local_30) {
          *(uint8_t *)((int)tmp_pu5 + tmp_u4 + 1) = (&g_unk_0014b381)[tmp_u4];
          if (tmp_u4 + 2 < local_30) {
            *(uint8_t *)((int)tmp_pu5 + tmp_u4 + 2) = (&g_unk_0014b382)[tmp_u4];
          }
        }
      }
    }
    tmp_pu5 = param_2 + 6;
    MD5Transform();
    local_2c = local_2c - local_30;
    if (local_2c != 0) goto LAB_0010ba57;
  }
  tmp_u4 = param_2[4] + 0x40;
  tmp_u7 = (uint)param_2[4] >> 3 & 0x3f;
  param_2[4] = tmp_u4;
  if (tmp_u4 < 0x40) {
    param_2[5] = param_2[5] + 1;
  }
  tmp_u4 = -tmp_u7 + 0x40;
  if (tmp_u4 < 9) {
    tmp_pu6 = (uint16_t *)local_18;
    tmp_pu11 = (uint16_t *)((int)param_2 + tmp_u7 + 0x18);
    local_2c = tmp_u4;
    if (3 < tmp_u4) {
      tmp_pu12 = tmp_pu11;
      if (((uint)tmp_pu11 & 1) != 0) {
        local_2c = -tmp_u7 + 0x3f;
        tmp_pu12 = (uint16_t *)((int)tmp_pu11 + 1);
        *(uint8_t *)tmp_pu11 = local_18[0];
        tmp_pu6 = (uint16_t *)(local_18 + 1);
      }
      tmp_pu11 = tmp_pu12;
      if (((uint)tmp_pu12 & 2) != 0) {
        tmp_u2 = *tmp_pu6;
        tmp_pu11 = tmp_pu12 + 1;
        tmp_pu6 = tmp_pu6 + 1;
        *tmp_pu12 = tmp_u2;
        local_2c = local_2c - 2;
      }
      if (3 < local_2c) {
        tmp_u10 = 0;
        do {
          *(uint32_t *)((int)tmp_pu11 + tmp_u10) = *(uint32_t *)((int)tmp_pu6 + tmp_u10);
          tmp_u10 = tmp_u10 + 4;
        } while (tmp_u10 < (local_2c & 0xfffffffc));
        tmp_pu11 = (uint16_t *)((int)tmp_pu11 + tmp_u10);
        tmp_pu6 = (uint16_t *)((int)tmp_pu6 + tmp_u10);
      }
    }
    tmp_i8 = 0;
    if ((local_2c & 2) != 0) {
      *tmp_pu11 = *tmp_pu6;
      tmp_i8 = 2;
    }
    if ((local_2c & 1) != 0) {
      *(uint8_t *)((int)tmp_pu11 + tmp_i8) = *(uint8_t *)((int)tmp_pu6 + tmp_i8);
    }
    tmp_pu5 = param_2 + 6;
    MD5Transform();
    tmp_u7 = tmp_u7 - 0x38;
    if (tmp_u7 == 0) goto LAB_0010bb9b;
  }
  else {
    tmp_u4 = 0;
    tmp_pu5 = (uint32_t *)((int)param_2 + tmp_u7 + 0x18);
    tmp_u7 = 8;
  }
  tmp_u10 = 1;
  if (tmp_u7 != 0) {
    tmp_u10 = tmp_u7;
  }
  tmp_pu9 = (uint32_t *)(local_18 + tmp_u4);
  if (7 < tmp_u10) {
    tmp_pu13 = tmp_pu5;
    if (((uint)tmp_pu5 & 1) != 0) {
      tmp_u1 = *(uint8_t *)tmp_pu9;
      tmp_pu13 = (uint32_t *)((int)tmp_pu5 + 1);
      tmp_pu9 = (uint32_t *)(local_18 + tmp_u4 + 1);
      tmp_u10 = tmp_u10 - 1;
      *(uint8_t *)tmp_pu5 = tmp_u1;
    }
    tmp_pu14 = tmp_pu13;
    if (((uint)tmp_pu13 & 2) != 0) {
      tmp_u2 = *(uint16_t *)tmp_pu9;
      tmp_pu14 = (uint32_t *)((int)tmp_pu13 + 2);
      tmp_pu9 = (uint32_t *)((int)tmp_pu9 + 2);
      tmp_u10 = tmp_u10 - 2;
      *(uint16_t *)tmp_pu13 = tmp_u2;
    }
    tmp_pu5 = tmp_pu14;
    if (((uint)tmp_pu14 & 4) != 0) {
      tmp_u3 = *tmp_pu9;
      tmp_pu5 = tmp_pu14 + 1;
      tmp_pu9 = tmp_pu9 + 1;
      tmp_u10 = tmp_u10 - 4;
      *tmp_pu14 = tmp_u3;
    }
  }
  for (; tmp_u10 != 0; tmp_u10 = tmp_u10 - 1) {
    *(uint8_t *)tmp_pu5 = *(uint8_t *)tmp_pu9;
    tmp_pu9 = (uint32_t *)((int)tmp_pu9 + (uint)tmp_b16 * -2 + 1);
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + (uint)tmp_b16 * -2 + 1);
  }
LAB_0010bb9b:
  tmp_u4 = 0x58;
  *param_1 = (char)*param_2;
  param_1[1] = (char)((uint)*param_2 >> 8);
  param_1[2] = (char)((uint)*param_2 >> 0x10);
  param_1[3] = (char)((uint)*param_2 >> 0x18);
  param_1[4] = (char)param_2[1];
  param_1[5] = (char)((uint)param_2[1] >> 8);
  param_1[6] = (char)*(uint16_t *)((int)param_2 + 6);
  param_1[7] = *(uint8_t *)((int)param_2 + 7);
  param_1[8] = (char)param_2[2];
  param_1[9] = (char)((uint)param_2[2] >> 8);
  param_1[10] = (char)*(uint16_t *)((int)param_2 + 10);
  param_1[0xb] = *(uint8_t *)((int)param_2 + 0xb);
  param_1[0xc] = (char)param_2[3];
  tmp_b15 = ((uint)param_2 & 1) != 0;
  param_1[0xd] = (char)((uint)param_2[3] >> 8);
  param_1[0xe] = (char)*(uint16_t *)((int)param_2 + 0xe);
  param_1[0xf] = *(uint8_t *)((int)param_2 + 0xf);
  if (tmp_b15) {
    *(uint8_t *)param_2 = 0;
    tmp_u4 = 0x57;
    param_2 = (uint32_t *)((int)param_2 + 1);
  }
  if (((uint)param_2 & 2) != 0) {
    *(uint16_t *)param_2 = 0;
    tmp_u4 = tmp_u4 - 2;
    param_2 = (uint32_t *)((int)param_2 + 2);
  }
  tmp_u7 = 0;
  do {
    *(uint32_t *)((int)param_2 + tmp_u7) = 0;
    *(uint32_t *)((int)param_2 + tmp_u7 + 4) = 0;
    tmp_u7 = tmp_u7 + 8;
  } while (tmp_u7 < (tmp_u4 & 0xfffffff8));
  param_2 = (uint32_t *)((int)param_2 + tmp_u7);
  if ((tmp_u4 & 4) != 0) {
    *param_2 = 0;
    param_2 = param_2 + 1;
  }
  if ((tmp_u4 & 2) != 0) {
    *(uint16_t *)param_2 = 0;
    param_2 = (uint32_t *)((int)param_2 + 2);
  }
  if (tmp_b15) {
    *(uint8_t *)param_2 = 0;
  }
  return;
}

