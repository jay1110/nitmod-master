/* Low-level drawing, shader management
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"
#include "et_ui_imports.h"
#include "et_ui_ui_draw.h"

void UI_DrawNamedPic(float param_1,float param_2,float param_3,float param_4,uint32_t param_5)

{
{  uint32_t tmp_u1;
  
  tmp_u1 = trap_R_RegisterShaderNoMip(param_5);
  param_1 = g_dat_00397fd4 * param_1;
  param_3 = g_dat_00397fd4 * param_3;
  if (1.3333334 < g_dat_003b7efc) {
    param_1 = param_1 * (1.3333334 / g_dat_003b7efc);
    param_3 = (1.3333334 / g_dat_003b7efc) * param_3;
  }
  trap_R_DrawStretchPic
            (param_1,g_dat_00397fd0 * param_2,param_3,g_dat_00397fd0 * param_4,0,0,0x3f800000,0x3f800000
             ,tmp_u1);
  return;
}

void UI_DrawHandlePic(float param_1,float param_2,float param_3,float param_4,uint32_t param_5)

{
{  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t local_14;
  uint32_t local_10;
  
  if (param_3 < 0.0) {
    param_3 = -param_3;
    local_14 = 0x3f800000;
    tmp_u2 = 0;
  }
  else {
    tmp_u2 = 0x3f800000;
    local_14 = 0;
  }
  if (param_4 < 0.0) {
    param_4 = -param_4;
    local_10 = 0x3f800000;
    tmp_u1 = 0;
  }
  else {
    tmp_u1 = 0x3f800000;
    local_10 = 0;
  }
  param_1 = g_dat_00397fd4 * param_1;
  param_3 = param_3 * g_dat_00397fd4;
  if (1.3333334 < g_dat_003b7efc) {
    param_1 = param_1 * (1.3333334 / g_dat_003b7efc);
    param_3 = (1.3333334 / g_dat_003b7efc) * param_3;
  }
  trap_R_DrawStretchPic
            (param_1,g_dat_00397fd0 * param_2,param_3,param_4 * g_dat_00397fd0,local_14,local_10,tmp_u2,
             tmp_u1,param_5);
  return;
}

void UI_DrawRotatedPic(float param_1,float param_2,float param_3,float param_4,uint32_t param_5,
                      uint32_t param_6)

{
{  param_1 = g_dat_00397fd4 * param_1;
  param_3 = g_dat_00397fd4 * param_3;
  if (1.3333334 < g_dat_003b7efc) {
    param_1 = param_1 * (1.3333334 / g_dat_003b7efc);
    param_3 = (1.3333334 / g_dat_003b7efc) * param_3;
  }
  trap_R_DrawRotatedPic
            (param_1,g_dat_00397fd0 * param_2,param_3,g_dat_00397fd0 * param_4,0,0,0x3f800000,0x3f800000
             ,param_5,param_6);
  return;
}

void UI_DrawSides(float param_1,float param_2,float param_3,float param_4)

{
{  param_1 = g_dat_00397fd4 * param_1;
  param_2 = g_dat_00397fd0 * param_2;
  param_3 = g_dat_00397fd4 * param_3;
  param_4 = g_dat_00397fd0 * param_4;
  if (1.3333334 < g_dat_003b7efc) {
    param_1 = param_1 * (1.3333334 / g_dat_003b7efc);
    param_3 = (1.3333334 / g_dat_003b7efc) * param_3;
  }
  trap_R_DrawStretchPic(param_1,param_2,0x3f800000,param_4,0,0,0,0,g_dat_003b7f10);
  trap_R_DrawStretchPic((param_3 + param_1) - 1.0,param_2,0x3f800000,param_4,0,0,0,0,g_dat_003b7f10);
  return;
}

void UI_DrawTopBottom(float param_1,float param_2,float param_3,float param_4)

{
{  param_1 = g_dat_00397fd4 * param_1;
  param_2 = g_dat_00397fd0 * param_2;
  param_3 = g_dat_00397fd4 * param_3;
  param_4 = g_dat_00397fd0 * param_4;
  if (1.3333334 < g_dat_003b7efc) {
    param_1 = param_1 * (1.3333334 / g_dat_003b7efc);
    param_3 = (1.3333334 / g_dat_003b7efc) * param_3;
  }
  trap_R_DrawStretchPic(param_1,param_2,param_3,0x3f800000,0,0,0,0,g_dat_003b7f10);
  trap_R_DrawStretchPic(param_1,(param_2 + param_4) - 1.0,param_3,0x3f800000,0,0,0,0,g_dat_003b7f10);
  return;
}

void UI_DrawTextBox(int param_1,int param_2,int param_3,int param_4)

{
{  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  
  tmp_f1 = (float)((param_4 + 1) * 0x10);
  tmp_f2 = (float)((param_3 + 1) * 0x10);
  tmp_f3 = (float)(param_2 + 8);
  tmp_f4 = (float)(param_1 + 8);
  trap_R_SetColor(colorBlack);
  tmp_f5 = tmp_f4 * g_dat_00397fd4;
  tmp_f6 = tmp_f2 * g_dat_00397fd4;
  if (1.3333334 < g_dat_003b7efc) {
    tmp_f5 = tmp_f5 * (1.3333334 / g_dat_003b7efc);
    tmp_f6 = (1.3333334 / g_dat_003b7efc) * tmp_f6;
  }
  trap_R_DrawStretchPic(tmp_f5,tmp_f3 * g_dat_00397fd0,tmp_f6,tmp_f1 * g_dat_00397fd0,0,0,0,0,g_dat_003b7f10);
  trap_R_SetColor(0);
  trap_R_SetColor(&colorWhite);
  UI_DrawTopBottom(tmp_f4,tmp_f3,tmp_f2,tmp_f1);
  UI_DrawSides(tmp_f4,tmp_f3,tmp_f2,tmp_f1);
  trap_R_SetColor(0);
  return;
}

void UI_DrawMapPreview(float *param_1,float param_2,uint32_t param_3,int param_4)

{
{  float tmp_f1;
  float tmp_f2;
  byte tmp_b3;
  uint32_t *tmp_pu4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  int tmp_i8;
  uint32_t tmp_u9;
  int tmp_i10;
  size_t tmp_s11;
  byte *__s;
  int tmp_i12;
  int local_74;
  uint32_t *local_70;
  float local_3c;
  float local_38;
  float local_34;
  float local_30 [8];
  
  tmp_i10 = GHIDRA_FIELD(ui_currentNetMap, 12, 4);
  tmp_i8 = GHIDRA_FIELD(ui_netGameType, 12, 4);
  if (param_4 == 0) {
    tmp_i10 = GHIDRA_FIELD(ui_currentMap, 12, 4);
    tmp_i8 = (&g_dat_00397ed4)[(GHIDRA_FIELD(ui_gameType, 12, 4) + 0x20c8) * 4];
  }
  if (tmp_i8 == 4) {
    if ((tmp_i10 < 0) || (g_dat_003cab70 < tmp_i10)) {
      if (param_4 == 0) {
        tmp_i10 = 0;
        GHIDRA_FIELD(ui_currentMap, 12, 4) = 0;
        trap_Cvar_Set("ui_currentMap","0");
      }
      else {
        tmp_i10 = 0;
        GHIDRA_FIELD(ui_currentNetMap, 12, 4) = 0;
        trap_Cvar_Set("ui_currentNetMap","0");
      }
    }
    if ((*(float *)(&g_dat_003cabb4 + tmp_i10 * 0x74) == 0.0) ||
       (*(float *)(&g_dat_003cabbc + tmp_i10 * 0x74) == 0.0)) {
      tmp_i10 = trap_R_RegisterShaderNoMip("levelshots/unknownmap");
LAB_0002dc15:
      UI_DrawHandlePic(*param_1,param_1[1],param_1[2],param_1[3],tmp_i10);
      return;
    }
    local_3c = *param_1;
    local_38 = param_1[1];
    local_34 = param_1[2];
    local_30[0] = param_1[3];
    UI_AdjustFrom640(&local_3c,&local_38,&local_34,local_30);
    tmp_i10 = tmp_i10 * 0x74;
    trap_R_DrawStretchPic
              (local_3c,local_38,local_34,local_30[0],
               *(float *)(&g_dat_003cabb4 + tmp_i10) * 0.0009765625,
               *(float *)(&g_dat_003cabb8 + tmp_i10) * 0.0009765625,
               *(float *)(&g_dat_003cabbc + tmp_i10) * 0.0009765625,
               *(float *)(&g_dat_003cabc0 + tmp_i10) * 0.0009765625,g_dat_003e8074);
    if (0 < *(int *)(&g_dat_003cab88 + tmp_i10)) {
      local_70 = (uint32_t *)(&g_dat_003cab8c + tmp_i10);
      local_74 = 0;
      do {
        tmp_i8 = g_dat_003e7e2c;
        local_30[1] = 0.0;
        local_30[2] = 0.0;
        tmp_f1 = *param_1;
        tmp_f2 = param_1[2];
        local_30[3] = 0.0;
        tmp_pu4 = (uint32_t *)*local_70;
        local_30[4] = 0.4;
        tmp_f5 = (((float)tmp_pu4[0x1b] - *(float *)(&g_dat_003cabb4 + tmp_i10)) / 650.0) * tmp_f2 + tmp_f1
        ;
        tmp_f6 = (((float)tmp_pu4[0x1c] - *(float *)(&g_dat_003cabb8 + tmp_i10)) / 650.0) * param_1[3] +
                param_1[1];
        __s = (byte *)*tmp_pu4;
        local_3c = tmp_f5;
        local_38 = tmp_f6;
        if (__s == (byte *)0x0) {
          tmp_f7 = 0.0;
        }
        else {
          tmp_i12 = 0;
          tmp_s11 = strlen((char *)__s);
          tmp_f7 = 0.0;
          do {
            while( true ) {
              tmp_b3 = *__s;
              if ((tmp_b3 == 0) || ((int)tmp_s11 <= tmp_i12)) goto LAB_0002ded2;
              if ((tmp_b3 != 0x5e) || ((__s[1] == 0 || (__s[1] == 0x5e)))) break;
              __s = __s + 2;
              if (__s == (byte *)0x0) goto LAB_0002ded2;
            }
            __s = __s + 1;
            tmp_i12 = tmp_i12 + 1;
            tmp_f7 = (float)*(int *)(&g_dat_0039800c + (uint)tmp_b3 * 0x50 + tmp_i8 * 0x5044) + tmp_f7;
          } while (__s != (byte *)0x0);
        }
LAB_0002ded2:
        local_34 = (float)(int)ROUND(tmp_f7 * param_2 * *(float *)(&g_dat_0039cffc + tmp_i8 * 0x5044));
        if (tmp_f5 + 10.0 + local_34 <= tmp_f2 + tmp_f1) {
          UI_FillRect(tmp_f5 + 1.0,(tmp_f6 - 6.0) + 1.0,local_34 + 10.0,0x41400000,local_30 + 1);
          UI_FillRect(local_3c,local_38 - 6.0,local_34 + 10.0,0x41400000,colorBlack);
        }
        else {
          UI_FillRect(((tmp_f5 - local_34) - 12.0) + 1.0,(tmp_f6 - 6.0) + 1.0,local_34 + 12.0,
                      0x41400000,local_30 + 1);
          UI_FillRect((local_3c - local_34) - 12.0,local_38 - 6.0,local_34 + 12.0,0x41400000,
                      colorBlack);
        }
        tmp_u9 = trap_R_RegisterShaderNoMip("gfx/loading/pin_neutral");
        UI_DrawHandlePic(local_3c - 8.0,local_38 - 8.0,0x41800000,0x41800000,tmp_u9);
        if (local_3c + 10.0 + local_34 <= param_1[2] + *param_1) {
          Text_Paint_Ext(local_3c + 8.0,local_38 + 3.0,param_2,param_2,&colorWhite,
                         *(uint32_t *)*local_70,0,0,0,&g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
        }
        else {
          Text_Paint_Ext((local_3c - local_34) - 10.0,local_38 + 3.0,param_2,param_2,&colorWhite,
                         *(uint32_t *)*local_70,0,0,0,&g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
        }
        local_74 = local_74 + 1;
        local_70 = local_70 + 1;
      } while (local_74 < *(int *)(&g_dat_003cab88 + tmp_i10));
    }
  }
  else if (*(int *)(&g_dat_003bab74 + tmp_i10 * 0x80) != 0) {
    tmp_u9 = va("levelshots/%s",*(int *)(&g_dat_003bab74 + tmp_i10 * 0x80));
    tmp_i10 = trap_R_RegisterShaderNoMip(tmp_u9);
    if (tmp_i10 != 0) goto LAB_0002dc15;
    tmp_u9 = trap_R_RegisterShaderNoMip("levelshots/unknownmap");
    UI_DrawHandlePic(*param_1,param_1[1],param_1[2],param_1[3],tmp_u9);
  }
  return;
}

UI_DrawMapCinematic(float *param_1,uint32_t param_2,uint32_t param_3,int param_4)

{
{  int *tmp_pi1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i4 = GHIDRA_FIELD(ui_currentNetMap, 12, 4);
  tmp_i3 = GHIDRA_FIELD(ui_netGameType, 12, 4);
  if (param_4 == 0) {
    tmp_i4 = GHIDRA_FIELD(ui_currentMap, 12, 4);
    tmp_i3 = (&g_dat_00397ed4)[(GHIDRA_FIELD(ui_gameType, 12, 4) + 0x20c8) * 4];
  }
  if (tmp_i3 == 4) {
    if ((tmp_i4 < 0) || (g_dat_003cab70 < tmp_i4)) {
      if (param_4 == 0) {
        GHIDRA_FIELD(ui_currentMap, 12, 4) = 0;
        trap_Cvar_Set("ui_currentMap","0");
      }
      else {
        GHIDRA_FIELD(ui_currentNetMap, 12, 4) = 0;
        trap_Cvar_Set("ui_currentNetMap","0");
      }
    }
  }
  else {
    if ((tmp_i4 < 0) || (g_dat_003bab6c < tmp_i4)) {
      if (param_4 == 0) {
        tmp_i4 = 0;
        GHIDRA_FIELD(ui_currentMap, 12, 4) = 0;
        trap_Cvar_Set("ui_currentMap","0");
      }
      else {
        GHIDRA_FIELD(ui_currentNetMap, 12, 4) = 0;
        tmp_i4 = 0;
        trap_Cvar_Set("ui_currentNetMap","0");
      }
    }
    tmp_pi1 = &g_dat_003bab80 + tmp_i4 * 0x20;
    tmp_i3 = *tmp_pi1;
    if (-2 < tmp_i3) {
      if (tmp_i3 == -1) {
        tmp_u2 = va(&g_dat_00055bd9,*(uint32_t *)(&g_dat_003bab74 + tmp_i4 * 0x80));
        tmp_i3 = trap_CIN_PlayCinematic(tmp_u2,0,0,0,0,10);
        *tmp_pi1 = tmp_i3;
        if (tmp_i3 < 0) {
          *tmp_pi1 = -2;
          return;
        }
      }
      trap_CIN_RunCinematic(tmp_i3);
      trap_CIN_SetExtents((&g_dat_003bab80)[tmp_i4 * 0x20],(int)ROUND(*param_1),(int)ROUND(param_1[1]),
                          (int)ROUND(param_1[2]),(int)ROUND(param_1[3]));
      trap_CIN_DrawCinematic((&g_dat_003bab80)[tmp_i4 * 0x20]);
      return;
    }
  }
  UI_DrawMapPreview(param_1,param_3,param_2,param_4);
  return;
}

void UI_DrawNetMapPreview(uint32_t *param_1)

{
{  uint32_t tmp_u1;
  
  if (0 < g_dat_003e53dc) {
    UI_DrawHandlePic(*param_1,param_1[1],param_1[2],param_1[3],g_dat_003e53dc);
    return;
  }
  tmp_u1 = trap_R_RegisterShaderNoMip("levelshots/unknownmap");
  UI_DrawHandlePic(*param_1,param_1[1],param_1[2],param_1[3],tmp_u1);
  return;
}

void UI_OwnerDraw(float param_1,float param_2,float param_3,float param_4,float param_5,
                 float param_6,int param_7,uint32_t param_8,uint32_t param_9,uint32_t param_10
                 ,float param_11,float *param_12,uint32_t param_13,uint32_t param_14)

{
{  byte tmp_b1;
  int tmp_i2;
  float tmp_f3;
  float tmp_f4;
  uint32_t *tmp_pu5;
  uint32_t tmp_u6;
  char *tmp_pc7;
  uint8_t *tmp_pu8;
  int tmp_i9;
  size_t tmp_s10;
  size_t tmp_s11;
  int tmp_i12;
  int tmp_i13;
  byte *__s;
  long double tmp_l14;
  double tmp_d15;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c [19];
  
  tmp_i13 = g_dat_003e7e2c;
  param_1 = param_1 + param_5;
  param_2 = param_2 + param_6;
  local_74 = param_3;
  local_70 = param_4;
  local_7c = param_1;
  local_78 = param_2;
  switch(param_7) {
  case 200:
    tmp_l14 = (long double)trap_Cvar_VariableValue("handicap");
    tmp_l14 = (long double)Com_Clamp(0x40a00000,0x42c80000,(float)tmp_l14);
    tmp_u6 = *(uint32_t *)(handicapValues + ((int)ROUND(tmp_l14) / 5) * -4 + 0x50);
    goto LAB_0002f7fe;
  case 0xc9:
    UI_DrawHandlePic(param_1,param_2,0x43000000,0x41000000,g_dat_003b6210);
    UI_DrawHandlePic((float)(g_dat_003e7e20 << 4) + local_7c + 8.0,local_78,0x41800000,0x41400000,
                     *(uint32_t *)(&g_dat_003b6214 + g_dat_003e7e20 * 4));
    break;
  case 0xca:
  case 0xcc:
  case 0xd2:
  case 0xd3:
  case 0xd4:
  case 0xd5:
  case 0xd6:
  case 0xd7:
  case 0xd8:
  case 0xd9:
  case 0xda:
  case 0xdb:
  case 0xdc:
  case 0xdd:
  case 0xdf:
  case 0xe0:
  case 0xe1:
  case 0xe2:
  case 0xe3:
  case 0xea:
  case 0xeb:
  case 0xec:
  case 0xee:
  case 0xef:
  case 0xf0:
  case 0xf3:
  case 0xf5:
  case 0xf6:
  case 0xf9:
  case 0xfb:
  case 0xfc:
  case 0xfd:
  case 0x100:
  case 0x102:
  case 0x103:
  case 0x113:
  case 0x114:
  case 0x115:
  case 0x116:
  case 0x117:
  case 0x119:
  case 0x11a:
  case 0x11b:
  case 0x11c:
  case 0x11d:
  case 0x11e:
  case 0x11f:
  case 0x120:
  case 0x121:
  case 0x122:
  case 0x123:
  case 0x124:
  case 0x125:
  case 0x126:
  case 0x127:
  case 0x128:
  case 0x129:
  case 0x12a:
  case 299:
    break;
  case 0xcb:
    tmp_u6 = UI_Cvar_VariableString("ui_teamName");
    goto LAB_0002f7fe;
  case 0xcd:
    Text_Paint_Ext(param_1,param_2,param_11,param_11,param_12,
                   (&g_dat_00397ecc)[(GHIDRA_FIELD(ui_gameType, 12, 4) + 0x20c8) * 4],0,0,param_14,
                   &g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
    break;
  case 0xce:
    UI_DrawMapPreview(&local_7c,param_11,param_12,1);
    break;
  case 0xcf:
    if (g_dat_003e53dc < 1) {
      tmp_u6 = trap_R_RegisterShaderNoMip("levelshots/unknownmap");
      UI_DrawHandlePic(local_7c,local_78,local_74,local_70,tmp_u6);
    }
    else {
      UI_DrawHandlePic(param_1,param_2,param_3,param_4,g_dat_003e53dc);
    }
    break;
  case 0xd0:
    tmp_pc7 = (char *)UI_Cvar_VariableString("ui_blueTeam");
    if (((tmp_pc7 != (char *)0x0) && (*tmp_pc7 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_i13 = 0;
      do {
        tmp_i9 = Q_stricmp(tmp_pc7);
        if (tmp_i9 == 0) {
          if (tmp_i13 < 0) {
            return;
          }
          goto LAB_0002f5e9;
        }
        tmp_i13 = tmp_i13 + 1;
      } while (tmp_i13 < g_dat_003b8544);
    }
    tmp_i13 = 0;
LAB_0002f5e9:
    if (g_dat_003b8544 <= tmp_i13) {
      return;
    }
    tmp_u6 = (&g_dat_003b8548)[tmp_i13 * 6];
    tmp_pu8 = &g_dat_00055c9f;
    goto LAB_0002ff05;
  case 0xd1:
    tmp_pc7 = (char *)UI_Cvar_VariableString("ui_redTeam");
    if (((tmp_pc7 != (char *)0x0) && (*tmp_pc7 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_i13 = 0;
      do {
        tmp_i9 = Q_stricmp(tmp_pc7);
        if (tmp_i9 == 0) {
          if (tmp_i13 < 0) {
            return;
          }
          goto LAB_0002fee9;
        }
        tmp_i13 = tmp_i13 + 1;
      } while (tmp_i13 < g_dat_003b8544);
    }
    tmp_i13 = 0;
LAB_0002fee9:
    if (g_dat_003b8544 <= tmp_i13) {
      return;
    }
    tmp_u6 = (&g_dat_003b8548)[tmp_i13 * 6];
    tmp_pu8 = &g_dat_00055caf;
LAB_0002ff05:
    tmp_u6 = va("%s: %s",tmp_pu8,tmp_u6);
LAB_0002fbe0:
    Text_Paint_Ext(local_7c,local_78,param_11,param_11,param_12,tmp_u6,0,0,param_14,
                   &g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
    break;
  case 0xde:
    if (1 < (uint)GHIDRA_FIELD(ui_serverFilterType, 12, 4)) {
      GHIDRA_FIELD(ui_serverFilterType, 12, 4) = 0;
    }
    tmp_u6 = va("Filter: %s",(&serverFilters)[GHIDRA_FIELD(ui_serverFilterType, 12, 4) * 2]);
    goto LAB_0002f2e0;
  case 0xe4:
    tmp_pc7 = (char *)UI_Cvar_VariableString("ui_teamName");
    if (((tmp_pc7 != (char *)0x0) && (*tmp_pc7 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_pu5 = &g_dat_003b8548;
      tmp_i13 = 0;
      do {
        tmp_i9 = Q_stricmp(tmp_pc7,*tmp_pu5);
        if (tmp_i9 == 0) goto LAB_0002fd79;
        tmp_i13 = tmp_i13 + 1;
        tmp_pu5 = tmp_pu5 + 6;
      } while (tmp_i13 < g_dat_003b8544);
    }
    goto LAB_0002fd77;
  case 0xe5:
    tmp_pc7 = (char *)UI_Cvar_VariableString("ui_opponentName");
    if (((tmp_pc7 != (char *)0x0) && (*tmp_pc7 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_pu5 = &g_dat_003b8548;
      tmp_i13 = 0;
      do {
        tmp_i9 = Q_stricmp(tmp_pc7,*tmp_pu5);
        if (tmp_i9 == 0) goto LAB_0002fd79;
        tmp_i13 = tmp_i13 + 1;
        tmp_pu5 = tmp_pu5 + 6;
      } while (tmp_i13 < g_dat_003b8544);
    }
LAB_0002fd77:
    tmp_i13 = 0;
LAB_0002fd79:
    if ((&g_dat_003b8550)[tmp_i13 * 6] == -1) {
      tmp_u6 = trap_R_RegisterShaderNoMip((&g_dat_003b854c)[tmp_i13 * 6]);
      (&g_dat_003b8550)[tmp_i13 * 6] = tmp_u6;
      tmp_u6 = va("%s_metal",(&g_dat_003b854c)[tmp_i13 * 6]);
      tmp_u6 = trap_R_RegisterShaderNoMip(tmp_u6);
      (&g_dat_003b8554)[tmp_i13 * 6] = tmp_u6;
      tmp_u6 = va("%s_name",(&g_dat_003b854c)[tmp_i13 * 6]);
      tmp_u6 = trap_R_RegisterShaderNoMip(tmp_u6);
      (&g_dat_003b8558)[tmp_i13 * 6] = tmp_u6;
    }
    trap_R_SetColor(param_12);
    tmp_u6 = (&g_dat_003b8550)[tmp_i13 * 6];
LAB_0002f4d9:
    UI_DrawHandlePic(local_7c,local_78,local_74,local_70,tmp_u6);
    trap_R_SetColor(0);
    break;
  case 0xe6:
    tmp_pc7 = (char *)UI_Cvar_VariableString("ui_teamName");
    if (((tmp_pc7 != (char *)0x0) && (*tmp_pc7 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_pu5 = &g_dat_003b8548;
      tmp_i13 = 0;
      do {
        tmp_i9 = Q_stricmp(tmp_pc7,*tmp_pu5);
        if (tmp_i9 == 0) goto LAB_0002f4a7;
        tmp_i13 = tmp_i13 + 1;
        tmp_pu5 = tmp_pu5 + 6;
      } while (tmp_i13 < g_dat_003b8544);
    }
    goto LAB_0002f4a5;
  case 0xe7:
    tmp_pc7 = (char *)UI_Cvar_VariableString("ui_opponentName");
    if (((tmp_pc7 != (char *)0x0) && (*tmp_pc7 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_pu5 = &g_dat_003b8548;
      tmp_i13 = 0;
      do {
        tmp_i9 = Q_stricmp(tmp_pc7,*tmp_pu5);
        if (tmp_i9 == 0) goto LAB_0002f4a7;
        tmp_i13 = tmp_i13 + 1;
        tmp_pu5 = tmp_pu5 + 6;
      } while (tmp_i13 < g_dat_003b8544);
    }
LAB_0002f4a5:
    tmp_i13 = 0;
LAB_0002f4a7:
    if ((&g_dat_003b8550)[tmp_i13 * 6] == -1) {
      tmp_u6 = trap_R_RegisterShaderNoMip((&g_dat_003b854c)[tmp_i13 * 6]);
      (&g_dat_003b8550)[tmp_i13 * 6] = tmp_u6;
      tmp_u6 = va("%s_metal",(&g_dat_003b854c)[tmp_i13 * 6]);
      tmp_u6 = trap_R_RegisterShaderNoMip(tmp_u6);
      (&g_dat_003b8554)[tmp_i13 * 6] = tmp_u6;
      tmp_u6 = va("%s_name",(&g_dat_003b854c)[tmp_i13 * 6]);
      tmp_u6 = trap_R_RegisterShaderNoMip(tmp_u6);
      (&g_dat_003b8558)[tmp_i13 * 6] = tmp_u6;
    }
    trap_R_SetColor(param_12);
    tmp_u6 = (&g_dat_003b8554)[tmp_i13 * 6];
    goto LAB_0002f4d9;
  case 0xe8:
    tmp_pc7 = (char *)UI_Cvar_VariableString("ui_teamName");
    if (((tmp_pc7 != (char *)0x0) && (*tmp_pc7 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_pu5 = &g_dat_003b8548;
      tmp_i13 = 0;
      do {
        tmp_i9 = Q_stricmp(tmp_pc7,*tmp_pu5);
        if (tmp_i9 == 0) goto LAB_0002f847;
        tmp_i13 = tmp_i13 + 1;
        tmp_pu5 = tmp_pu5 + 6;
      } while (tmp_i13 < g_dat_003b8544);
    }
    goto LAB_0002f845;
  case 0xe9:
    tmp_pc7 = (char *)UI_Cvar_VariableString("ui_opponentName");
    if (((tmp_pc7 != (char *)0x0) && (*tmp_pc7 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_pu5 = &g_dat_003b8548;
      tmp_i13 = 0;
      do {
        tmp_i9 = Q_stricmp(tmp_pc7,*tmp_pu5);
        if (tmp_i9 == 0) goto LAB_0002f847;
        tmp_i13 = tmp_i13 + 1;
        tmp_pu5 = tmp_pu5 + 6;
      } while (tmp_i13 < g_dat_003b8544);
    }
LAB_0002f845:
    tmp_i13 = 0;
LAB_0002f847:
    if ((&g_dat_003b8550)[tmp_i13 * 6] == -1) {
      tmp_u6 = trap_R_RegisterShaderNoMip((&g_dat_003b854c)[tmp_i13 * 6]);
      (&g_dat_003b8550)[tmp_i13 * 6] = tmp_u6;
      tmp_u6 = va("%s_metal",(&g_dat_003b854c)[tmp_i13 * 6]);
      tmp_u6 = trap_R_RegisterShaderNoMip(tmp_u6);
      (&g_dat_003b8554)[tmp_i13 * 6] = tmp_u6;
      tmp_u6 = va("%s_name",(&g_dat_003b854c)[tmp_i13 * 6]);
      tmp_u6 = trap_R_RegisterShaderNoMip(tmp_u6);
      (&g_dat_003b8558)[tmp_i13 * 6] = tmp_u6;
    }
    trap_R_SetColor(param_12);
    tmp_u6 = (&g_dat_003b8558)[tmp_i13 * 6];
    goto LAB_0002f4d9;
  case 0xed:
    tmp_u6 = UI_Cvar_VariableString("ui_opponentName");
    goto LAB_0002f2e0;
  case 0xf1:
    if (g_dat_003b8d50 == 0) {
      tmp_pu8 = &g_dat_00055caf;
    }
    else {
      tmp_pu8 = &g_dat_00055c9f;
    }
    Text_Paint_Ext(param_1,param_2,param_11,param_11,param_12,tmp_pu8,0,0,param_14,
                   &g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
    break;
  case 0xf2:
    tmp_f4 = (float)(int)GHIDRA_FIELD(cg_crosshairSize, 12, 4);
    if (0xf < g_dat_003e7e14) {
      g_dat_003e7e14 = 0;
    }
    tmp_f3 = 96.0;
    if ((tmp_f4 <= 96.0) && (tmp_f3 = 24.0, 24.0 <= tmp_f4)) {
      tmp_f3 = tmp_f4;
    }
    tmp_f3 = tmp_f3 * (param_3 / 96.0);
    trap_R_SetColor(&g_dat_003e8034);
    UI_DrawHandlePic((local_74 - tmp_f3) * 0.5 + local_7c,(local_70 - tmp_f3) * 0.5 + local_78,tmp_f3,
                     tmp_f3,(&g_dat_003b6230)[g_dat_003e7e14]);
    trap_R_SetColor(&g_dat_003e8044);
    UI_DrawHandlePic((local_74 - tmp_f3) * 0.5 + local_7c,(local_70 - tmp_f3) * 0.5 + local_78,tmp_f3,
                     tmp_f3,(&uiInfo)[g_dat_003e7e14 + 0x78ec]);
    trap_R_SetColor(0);
    break;
  case 0xf4:
    UI_DrawMapCinematic(param_11,0);
    break;
  case 0xf7:
    if (g_dat_003e13b8 == 0) {
      tmp_u6 = va("ui_lastServerRefresh_%i",GHIDRA_FIELD(ui_netSource, 12, 4));
      tmp_u6 = UI_Cvar_VariableString(tmp_u6);
      Q_strncpyz(local_5c,tmp_u6,0x40);
      tmp_u6 = va("Refresh Time: %s",local_5c);
    }
    else {
      local_6c = *param_12 * 0.8;
      local_68 = param_12[1] * 0.8;
      local_64 = param_12[2] * 0.8;
      local_60 = param_12[3] * 0.8;
      tmp_d15 = sin((double)(g_dat_00397fdc / 0x4b));
      LerpColor(param_12,&local_6c,local_5c,(float)tmp_d15 * 0.5 + 0.5);
      tmp_i13 = trap_LAN_GetServerCount(GHIDRA_FIELD(ui_netSource, 12, 4));
      if (tmp_i13 < 0) {
        Text_Paint_Ext(local_7c,local_78,param_11,param_11,local_5c,
                       "Waiting for response from Master Server",0,0,param_14,
                       &g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
        return;
      }
      tmp_u6 = va("Getting info for %d servers (ESC to cancel)",tmp_i13);
      param_12 = local_5c;
    }
    goto LAB_0002fbe0;
  case 0xf8:
    if (g_dat_003e53e4 != 0) {
      if (g_dat_003e53e8 == -1) {
        g_dat_003e53e8 = 0;
        g_dat_003e53ec = (int)ROUND(param_1 + 1.0);
        g_dat_003e53f0 = -1;
      }
      if (g_dat_003e53e4 < g_dat_003e53f4) {
        g_dat_003e53f4 = 0;
        g_dat_003e53ec = (int)ROUND(param_1 + 1.0);
        g_dat_003e53f0 = -1;
      }
      tmp_i2 = g_dat_003e53f4;
      tmp_i9 = g_dat_003e53ec;
      if (g_dat_003e53f8 < g_dat_00397fdc) {
        g_dat_003e53f8 = g_dat_00397fdc + 10;
        if (param_1 + 2.0 < (float)g_dat_003e53ec) {
          g_dat_003e53ec = g_dat_003e53ec + -2;
          if (-1 < g_dat_003e53f0) {
            g_dat_003e53f0 = g_dat_003e53f0 + -2;
          }
        }
        else if (g_dat_003e53f4 < g_dat_003e53e4) {
          __s = &g_dat_003e53fc + g_dat_003e53f4;
          tmp_s10 = strlen((char *)__s);
          tmp_s11 = 1;
          if ((int)tmp_s10 < 1) {
            tmp_s11 = tmp_s10;
          }
          tmp_f4 = 0.0;
          tmp_i12 = 0;
          do {
            tmp_b1 = *__s;
            if ((tmp_b1 == 0) || ((int)tmp_s11 <= tmp_i12)) break;
            if ((tmp_b1 == 0x5e) && ((__s[1] != 0 && (__s[1] != 0x5e)))) {
              __s = __s + 2;
              tmp_i12 = 0;
            }
            else {
              __s = __s + 1;
              tmp_i12 = 1;
              tmp_f4 = (float)*(int *)(&g_dat_0039800c + (uint)tmp_b1 * 0x50 + tmp_i13 * 0x5044) + tmp_f4;
            }
          } while (__s != (byte *)0x0);
          g_dat_003e53f4 = tmp_i2 + 1;
          g_dat_003e53ec = tmp_i9 + -1 +
                         (int)ROUND(tmp_f4 * param_11 * *(float *)(&g_dat_0039cffc + tmp_i13 * 0x5044));
        }
        else {
          g_dat_003e53f4 = 0;
          g_dat_003e53ec = g_dat_003e53f0;
          if (g_dat_003e53f0 < 0) {
            g_dat_003e53ec = (int)ROUND((param_1 + param_3) - 2.0);
          }
          g_dat_003e53f0 = -1;
        }
      }
      local_6c = (param_1 + param_3) - 2.0;
      Text_Paint_Limit_constprop_55
                ((float)g_dat_003e53ec,param_2,param_11,&g_dat_003e53fc + g_dat_003e53f4,0);
      if (-1 < g_dat_003e53f0) {
        local_5c[0] = (local_7c + local_74) - 2.0;
        Text_Paint_Limit_constprop_55
                  ((float)g_dat_003e53f0,local_78,param_11,&g_dat_003e53fc,g_dat_003e53f4);
      }
      if ((g_dat_003e53f4 == 0) || (local_6c <= 0.0)) {
        g_dat_003e53f0 = -1;
      }
      else if (g_dat_003e53f0 == -1) {
        g_dat_003e53f0 = (int)ROUND((local_7c + local_74) - 2.0);
      }
    }
    break;
  case 0xfa:
    tmp_i13 = Display_KeyBindPending();
    if (tmp_i13 == 0) {
      tmp_pc7 = "Press ENTER or CLICK to change, Press BACKSPACE to clear";
    }
    else {
      tmp_pc7 = "Waiting for new key... Press ESCAPE to cancel";
    }
    Text_Paint_Ext(param_5 + local_7c,param_6 + local_78,param_11,param_11,param_12,tmp_pc7,0,0,
                   param_14,&g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
    break;
  case 0xfe:
    if (-2 < g_dat_003e13a8) {
      tmp_u6 = va(&g_dat_00055bd9,*(uint32_t *)(&g_dat_003e0fa0 + g_dat_003e13a4 * 4));
      g_dat_003e13a8 = trap_CIN_PlayCinematic(tmp_u6,0,0,0,0,10);
      if (g_dat_003e13a8 < 0) {
        g_dat_003e13a8 = -2;
      }
      else {
        trap_CIN_RunCinematic(g_dat_003e13a8);
        trap_CIN_SetExtents(g_dat_003e13a8,(int)ROUND(local_7c),(int)ROUND(local_78),
                            (int)ROUND(local_74),(int)ROUND(local_70));
        trap_CIN_DrawCinematic(g_dat_003e13a8);
      }
    }
    break;
  case 0xff:
    UI_DrawMapCinematic(param_11,1);
    break;
  case 0x101:
    UI_DrawLoadPanel(0,1,0);
    break;
  case 0x104:
    if (((int)GHIDRA_FIELD(ui_currentCampaign, 12, 4) < 0) || (g_dat_003cab70 < (int)GHIDRA_FIELD(ui_currentCampaign, 12, 4))) {
      GHIDRA_FIELD(ui_currentCampaign, 12, 4) = 0;
      trap_Cvar_Set("ui_currentCampaign","0");
      if (g_dat_003cabcc < -1) {
        if (((int)GHIDRA_FIELD(ui_currentCampaign, 12, 4) < 0) ||
           (tmp_i13 = GHIDRA_FIELD(ui_currentCampaign, 12, 4), g_dat_003cab70 < (int)GHIDRA_FIELD(ui_currentCampaign, 12, 4))) {
          GHIDRA_FIELD(ui_currentCampaign, 12, 4) = 0;
          trap_Cvar_Set("ui_currentCampaign","0");
          tmp_i13 = 0;
        }
        goto LAB_000308c9;
      }
      tmp_i13 = 0;
      tmp_i9 = g_dat_003cabcc;
    }
    else {
      tmp_i9 = (&g_dat_003cabcc)[GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x1d];
      tmp_i13 = GHIDRA_FIELD(ui_currentCampaign, 12, 4);
      if ((&g_dat_003cabcc)[GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x1d] < -1) {
LAB_000308c9:
        tmp_i9 = (&g_dat_003cabd0)[tmp_i13 * 0x1d];
        if (tmp_i9 == -1) {
          tmp_i9 = trap_R_RegisterShaderNoMip(*(uint32_t *)(&g_dat_003cabc8 + tmp_i13 * 0x74));
          (&g_dat_003cabd0)[tmp_i13 * 0x1d] = tmp_i9;
        }
        if (0 < tmp_i9) {
          UI_DrawHandlePic(local_7c,local_78,local_74,local_70,tmp_i9);
          return;
        }
        tmp_i13 = trap_R_RegisterShaderNoMip("levelshots/unknownmap");
        goto LAB_0003067c;
      }
    }
    if (tmp_i9 == -1) {
      tmp_u6 = va(&g_dat_00055bd9,*(uint32_t *)(&g_dat_003cab74 + tmp_i13 * 0x74));
      tmp_i9 = trap_CIN_PlayCinematic(tmp_u6,0,0,0,0,10);
      (&g_dat_003cabcc)[tmp_i13 * 0x1d] = tmp_i9;
      if (tmp_i9 < 0) {
        (&g_dat_003cabcc)[tmp_i13 * 0x1d] = 0xfffffffe;
        return;
      }
    }
    trap_CIN_RunCinematic(tmp_i9);
    trap_CIN_SetExtents((&g_dat_003cabcc)[tmp_i13 * 0x1d],(int)ROUND(local_7c),(int)ROUND(local_78),
                        (int)ROUND(local_74),(int)ROUND(local_70));
    trap_CIN_DrawCinematic((&g_dat_003cabcc)[tmp_i13 * 0x1d]);
    break;
  case 0x105:
    if (((int)GHIDRA_FIELD(ui_currentCampaign, 12, 4) < 0) ||
       (tmp_i13 = GHIDRA_FIELD(ui_currentCampaign, 12, 4), g_dat_003cab70 < (int)GHIDRA_FIELD(ui_currentCampaign, 12, 4))) {
      GHIDRA_FIELD(ui_currentCampaign, 12, 4) = 0;
      trap_Cvar_Set("ui_currentCampaign","0");
      tmp_i13 = 0;
    }
    if ((&g_dat_003cabd4)[tmp_i13 * 0x1d] == 0) {
      return;
    }
    tmp_u6 = va(&g_dat_0005580c,(&g_dat_003cab78)[tmp_i13 * 0x1d]);
LAB_0002f2e0:
    Text_Paint_Ext(local_7c,local_78,param_11,param_11,param_12,tmp_u6,0,0,param_14,
                   &g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
    break;
  case 0x106:
    UI_DrawCampaignDescription(&local_7c,param_11,param_12,param_5,param_6,param_14,param_9,1);
    break;
  case 0x107:
  case 0x108:
  case 0x109:
  case 0x10a:
  case 0x10b:
  case 0x10c:
    if (((int)GHIDRA_FIELD(ui_currentCampaign, 12, 4) < 0) ||
       (tmp_i13 = GHIDRA_FIELD(ui_currentCampaign, 12, 4), g_dat_003cab70 < (int)GHIDRA_FIELD(ui_currentCampaign, 12, 4))) {
      tmp_i13 = 0;
      GHIDRA_FIELD(ui_currentCampaign, 12, 4) = 0;
      trap_Cvar_Set("ui_currentCampaign","0");
    }
    tmp_i9 = param_7 + 0xca29 + tmp_i13 * 0x1d;
    tmp_i2 = (&g_dat_00397ecc)[tmp_i9];
    if (tmp_i2 == 0) {
LAB_000303f0:
      tmp_u6 = trap_R_RegisterShaderNoMip("levelshots/unknownmap");
      UI_DrawHandlePic(local_7c,local_78,local_74,local_70,tmp_u6);
      tmp_i13 = (&g_dat_003cabd8)[tmp_i13 * 0x1d];
    }
    else {
      tmp_i12 = *(int *)(tmp_i2 + 0x58);
      if (tmp_i12 == -1) {
        tmp_u6 = trap_R_RegisterShaderNoMip(*(uint32_t *)(tmp_i2 + 8));
        *(uint32_t *)(tmp_i2 + 0x58) = tmp_u6;
        if ((&g_dat_00397ecc)[tmp_i9] == 0) goto LAB_000303f0;
        tmp_i12 = *(int *)((&g_dat_00397ecc)[tmp_i9] + 0x58);
      }
      if (tmp_i12 < 1) goto LAB_000303f0;
      UI_DrawHandlePic(local_7c,local_78,local_74,local_70,tmp_i12);
      tmp_i13 = (&g_dat_003cabd8)[tmp_i13 * 0x1d];
    }
    if (tmp_i13 < param_7 + -0x107) {
      tmp_u6 = trap_R_RegisterShaderNoMip("gfx/2d/friendlycross.tga");
      UI_DrawHandlePic(local_7c + 8.0,local_78 + 8.0,local_74 - 16.0,local_70 - 16.0,tmp_u6);
    }
    break;
  case 0x10d:
  case 0x10e:
  case 0x10f:
  case 0x110:
  case 0x111:
  case 0x112:
    UI_DrawCampaignMapDescription_constprop_54
              (param_11,param_5,param_6,param_14,param_9,param_7 + -0x10d);
    break;
  case 0x118:
    UI_DrawGametypeDescription(&local_7c,param_11,param_12,param_5,param_6,param_14,param_9,1);
    break;
  case 300:
    if (image_9756 == -1) {
      trap_Cvar_VariableStringBuffer("mapname",local_5c,0x40);
      tmp_u6 = va("levelshots/%s_cc.tga",local_5c);
      image_9756 = trap_R_RegisterShaderNoMip(tmp_u6);
    }
    tmp_i13 = image_9756;
    if (image_9756 == 0) {
      tmp_u6 = trap_R_RegisterShaderNoMip("levelshots/unknownmap");
      UI_DrawHandlePic(local_7c,local_78,local_74,local_70,tmp_u6);
      return;
    }
LAB_0003067c:
    UI_DrawHandlePic(local_7c,local_78,local_74,local_70,tmp_i13);
    break;
  case 0x12d:
    trap_Cvar_VariableStringBuffer("mapname",local_5c,0x40);
    tmp_pu5 = (uint32_t *)UI_FindMapInfoByMapname(local_5c);
    if (tmp_pu5 == (uint32_t *)0x0) {
      return;
    }
    tmp_u6 = va("%s Objectives",*tmp_pu5);
LAB_0002f7fe:
    Text_Paint_Ext(local_7c,local_78,param_11,param_11,param_12,tmp_u6,0,0,param_14,
                   &g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
    break;
  case 0x12e:
    UI_DrawMissionBriefingObjectives(param_11,param_5,param_6,param_14,param_9);
  }
  return;
}
