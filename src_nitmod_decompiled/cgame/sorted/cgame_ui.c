/* HUD, menus, scoreboards and drawing — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_ui.h"

void CG_DrawGrid_constprop_8(int param_1,float param_2,float param_3,float param_4,float param_5)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  int tmp_i7;
  int tmp_i8;
  float local_9c;
  float local_98;
  float local_88;
  char local_3f [3];
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  tmp_f5 = g_unk_010abd60;
  tmp_f4 = g_unk_010abd58;
  uStack_14 = 0x3a3d9;
  tmp_f1 = g_unk_010abd5c - g_unk_010abd54;
  if (gridInitDone == 0) {
    gridStep = 1200.0;
    tmp_f2 = tmp_f1 / 1200.0;
    while (tmp_f2 < 7.0) {
      gridStep = gridStep - 50.0;
      tmp_f2 = tmp_f1 / gridStep;
    }
    g_unk_002a7584 = 1200.0;
    tmp_f3 = (g_unk_010abd58 - g_unk_010abd60) / 1200.0;
    while (tmp_f3 < 7.0) {
      g_unk_002a7584 = g_unk_002a7584 - 50.0;
      tmp_f3 = (g_unk_010abd58 - g_unk_010abd60) / g_unk_002a7584;
    }
    gridInitDone = 1;
    gridStartCoord = (tmp_f2 - (float)(int)ROUND(tmp_f2)) * gridStep * 0.5;
    g_unk_002a758c = (tmp_f3 - (float)(int)ROUND(tmp_f3)) * g_unk_002a7584 * 0.5;
  }
  if (param_1 == 0) {
    CG_HudPlacement(2);
  }
  else {
    CG_HudPlacement(0);
  }
  param_4 = param_4 / tmp_f1;
  local_20 = 0x3f800000;
  local_3f[0] = '@';
  param_5 = param_5 / -(tmp_f5 - tmp_f4);
  tmp_f1 = (g_unk_010abd54 - g_unk_010abd54) * param_4;
  tmp_f4 = (g_unk_010abd5c - g_unk_010abd54) * param_4;
  tmp_f2 = (g_unk_010abd60 - g_unk_010abd60) * param_5;
  tmp_f3 = (g_unk_010abd58 - g_unk_010abd60) * param_5;
  tmp_f5 = gridStartCoord * param_4;
  local_9c = g_unk_002a758c * param_5;
  param_4 = param_4 * gridStep;
  param_5 = param_5 * g_unk_002a7584;
  local_2c = clrBrownLine;
  local_28 = g_unk_0014a244;
  local_24 = g_unk_0014a248;
  local_3f[1] = 0;
  if (tmp_f5 < tmp_f4) {
    local_88 = tmp_f5 + param_2;
    tmp_f6 = param_3 + tmp_f2;
    local_98 = tmp_f5;
    while( true ) {
      trap_R_SetColor(&local_2c);
      local_34 = 1.0;
      local_3c = local_88;
      local_38 = tmp_f6;
      local_30 = tmp_f4 - tmp_f1;
      CG_AdjustFrom640(&local_3c,&local_38,&local_34,&local_30);
      trap_R_DrawStretchPic(local_3c,local_38,local_34,local_30,0,0,0,0x3f800000,GHIDRA_FIELD(cgs, 67836, 4));
      local_3f[0] = local_3f[0] + '\x01';
      local_98 = local_98 + param_4;
      if (tmp_f4 <= local_98) break;
      if (local_3f[0] < 'A') {
        local_88 = local_98 + param_2;
      }
      else {
        tmp_i7 = CG_Text_Width_Ext(local_3f,0x3e4ccccd,0,0x110afec);
        tmp_i8 = CG_Text_Height_Ext(local_3f,0x3e4ccccd,0,0x110afec);
        local_88 = local_98 + param_2;
        CG_Text_Paint_Ext((local_88 - param_4 * 0.5) - (float)tmp_i7 * 0.5,
                          local_9c + tmp_f6 + (float)tmp_i8 * 1.5,0x3e4ccccd,0x3e4ccccd,&colorBlack,
                          local_3f,0,0,0,0x110afec);
      }
    }
  }
  if (local_9c < tmp_f3) {
    local_88 = local_9c + param_3;
    tmp_f1 = tmp_f1 + param_2;
    GHIDRA_FIELD(local_98, 0, 1) = -1;
    while( true ) {
      trap_R_SetColor(&local_2c);
      local_30 = 1.0;
      local_38 = local_88;
      local_3c = tmp_f1;
      local_34 = tmp_f3 - tmp_f2;
      CG_AdjustFrom640(&local_3c,&local_38,&local_34,&local_30);
      trap_R_DrawStretchPic(local_3c,local_38,local_34,local_30,0,0,0,0x3f800000,GHIDRA_FIELD(cgs, 67836, 4));
      GHIDRA_FIELD(local_98, 0, 1) = GHIDRA_FIELD(local_98, 0, 1) + '\x01';
      local_9c = local_9c + param_5;
      if (tmp_f3 <= local_9c) break;
      if (GHIDRA_FIELD(local_98, 0, 1) < '\0') {
        local_88 = local_9c + param_3;
      }
      else {
        Com_sprintf(local_3f,3,"%i",(int)GHIDRA_FIELD(local_98, 0, 1));
        tmp_i7 = CG_Text_Width_Ext(&g_unk_0011e957,0x3e4ccccd,0,0x110afec);
        tmp_i8 = CG_Text_Height_Ext(local_3f,0x3e4ccccd,0,0x110afec);
        local_88 = local_9c + param_3;
        CG_Text_Paint_Ext(tmp_f5 + tmp_f1 + (float)tmp_i7 * 0.5,
                          (float)tmp_i8 * 0.5 + (local_88 - param_5 * 0.5),0x3e4ccccd,0x3e4ccccd,
                          &colorBlack,local_3f,0,0,0,0x110afec);
      }
    }
  }
  trap_R_SetColor(0);
  return;
}

int CG_DrawSpawnPointInfo_constprop_5(int param_1,int param_2,int param_3,int param_4,int *param_5)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  uint tmp_u9;
  int tmp_i10;
  float *pfVar11;
  int *tmp_pi12;
  int local_90;
  float local_8c;
  uint8_t *local_88;
  int local_74;
  uint8_t local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0x3aee9;
  tmp_u9 = CG_LimboPanel_GetRealTeam();
  if ((cgs[0x20201cc] & 4) == 0) {
    local_8c = (float)g_unk_010ad280;
    if (g_unk_010ad280 < 2) {
      local_74 = -1;
    }
    else {
      local_88 = &g_unk_010abe00;
      local_74 = -1;
      tmp_pi12 = &g_unk_010ad184;
      pfVar11 = (float *)&g_unk_010acd8c;
      local_90 = 1;
      do {
        if (*tmp_pi12 == 0) {
          tmp_f3 = 0.0;
        }
        else {
          tmp_f3 = (float)(g_unk_010906e0 - *tmp_pi12);
          if ((1000.0 < tmp_f3) || (tmp_f3 < 0.0)) {
            *tmp_pi12 = 0;
            tmp_f3 = 0.0;
          }
        }
        if (((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3) || (tmp_u9 == tmp_pi12[-0x40])) &&
           (((tmp_pi12[-0x40] & 0x100U) == 0 || (tmp_f3 != 0.0)))) {
          if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
            tmp_i10 = (int)ROUND(pfVar11[0x62]);
            if (((int)GHIDRA_FIELD(cgs, 33575852, 4) < tmp_i10) && (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
              if (((int)GHIDRA_FIELD(cgs, 33575856, 4) < tmp_i10) && (GHIDRA_FIELD(cgs, 33575848, 4) != 1)) {
                if (((int)GHIDRA_FIELD(cgs, 33575860, 4) < tmp_i10) && (GHIDRA_FIELD(cgs, 33575848, 4) != 2)) {
                  if (((int)GHIDRA_FIELD(cgs, 33575864, 4) < tmp_i10) && (GHIDRA_FIELD(cgs, 33575848, 4) != 3)) {
                    if (((int)GHIDRA_FIELD(cgs, 33575868, 4) < tmp_i10) && (GHIDRA_FIELD(cgs, 33575848, 4) != 4)) {
                      if (((int)GHIDRA_FIELD(cgs, 33575872, 4) < tmp_i10) && (GHIDRA_FIELD(cgs, 33575848, 4) != 5)) {
                        if (((int)GHIDRA_FIELD(cgs, 33575876, 4) < tmp_i10) && (GHIDRA_FIELD(cgs, 33575848, 4) != 6)) {
                          if (((int)GHIDRA_FIELD(cgs, 33575880, 4) < tmp_i10) && (GHIDRA_FIELD(cgs, 33575848, 4) != 7)) {
                            if (((int)GHIDRA_FIELD(cgs, 33575884, 4) < tmp_i10) && (GHIDRA_FIELD(cgs, 33575848, 4) != 8)) {
                              if (((int)GHIDRA_FIELD(cgs, 33575888, 4) < tmp_i10) && (GHIDRA_FIELD(cgs, 33575848, 4) != 9)) {
                                if (((int)GHIDRA_FIELD(cgs, 33575892, 4) < tmp_i10) && (GHIDRA_FIELD(cgs, 33575848, 4) != 10)) {
                                  if (((int)GHIDRA_FIELD(cgs, 33575896, 4) < tmp_i10) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xb))
                                  {
                                    if (((int)GHIDRA_FIELD(cgs, 33575900, 4) < tmp_i10) &&
                                       (GHIDRA_FIELD(cgs, 33575848, 4) != 0xc)) {
                                      if (((int)GHIDRA_FIELD(cgs, 33575904, 4) < tmp_i10) &&
                                         (GHIDRA_FIELD(cgs, 33575848, 4) != 0xd)) {
                                        if ((tmp_i10 <= (int)GHIDRA_FIELD(cgs, 33575908, 4)) ||
                                           (tmp_i10 = 0xf, GHIDRA_FIELD(cgs, 33575848, 4) == 0xe)) {
                                          tmp_i10 = 0xe;
                                        }
                                      }
                                      else {
                                        tmp_i10 = 0xd;
                                      }
                                    }
                                    else {
                                      tmp_i10 = 0xc;
                                    }
                                  }
                                  else {
                                    tmp_i10 = 0xb;
                                  }
                                }
                                else {
                                  tmp_i10 = 10;
                                }
                              }
                              else {
                                tmp_i10 = 9;
                              }
                            }
                            else {
                              tmp_i10 = 8;
                            }
                          }
                          else {
                            tmp_i10 = 7;
                          }
                        }
                        else {
                          tmp_i10 = 6;
                        }
                      }
                      else {
                        tmp_i10 = 5;
                      }
                    }
                    else {
                      tmp_i10 = 4;
                    }
                  }
                  else {
                    tmp_i10 = 3;
                  }
                }
                else {
                  tmp_i10 = 2;
                }
              }
              else {
                tmp_i10 = 1;
              }
              if (GHIDRA_FIELD(cgs, 33575848, 4) == tmp_i10) {
                CG_Printf("^3Warning: no valid command map layer for z\n");
                tmp_i10 = 0;
              }
            }
            else {
              tmp_i10 = 0;
            }
            if (GHIDRA_FIELD(cgs, 33685900, 4) != tmp_i10) {
              return local_74;
            }
          }
          if (param_5 == (int *)0x0) {
            tmp_f4 = (float)param_3 * (*pfVar11 - g_unk_010abd54) * g_unk_010abd64 + (float)param_1;
            tmp_f5 = (float)param_4 * (pfVar11[1] - g_unk_010abd58) * g_unk_010abd68 + (float)param_2;
            tmp_f1 = (float)GHIDRA_FIELD(cgs, 33575916, 4);
LAB_0003b0da:
            if ((tmp_f3 == 0.0) && (expanded == 0)) {
              tmp_f4 = tmp_f4 - tmp_f1 * 32.0 * 0.3046875;
              tmp_f5 = tmp_f1 * 32.0 * 0.2421875 + tmp_f5;
              tmp_i10 = BG_RectContainsPoint
                                 (tmp_f4 - 16.0,tmp_f5 - 16.0,0x42000000,0x42000000,
                                  (float)g_unk_010261a4,(float)g_unk_010261a8);
              if (tmp_i10 != 0) {
                if (param_5 == (int *)0x0) {
                  Com_sprintf(local_5c,0x40,"%s (Troops: %i)",local_88,tmp_pi12[0x20]);
                  tmp_i10 = CG_Text_Width_Ext(local_5c,0x3e4ccccd,0,0x110afec);
                  Q_strncpyz(&cg_highlightText,local_5c,0x100);
                  expanded = 1;
                  local_8c = (float)g_unk_010ad280;
                  g_unk_00f5eb44 = tmp_f5 - 8.0;
                  local_74 = local_90;
                  cg_highlightTextRect = tmp_f4 - (float)tmp_i10 * 0.5;
                }
                else {
                  local_8c = (float)g_unk_010ad280;
                  local_74 = local_90;
                }
                goto LAB_0003afc0;
              }
            }
          }
          else {
            tmp_f1 = (float)param_5[1];
            tmp_f4 = (float)param_3 * (*pfVar11 - g_unk_010abd54) * g_unk_010abd64 * tmp_f1;
            tmp_f5 = (float)param_4 * (pfVar11[1] - g_unk_010abd58) * g_unk_010abd68 * tmp_f1;
            if (*param_5 != 0) {
              tmp_f2 = (float)param_5[2];
              tmp_f7 = ((float)param_5[4] - tmp_f2) * 0.5;
              tmp_f6 = tmp_f4 - (tmp_f2 + tmp_f7);
              local_8c = (float)param_5[3];
              tmp_f8 = tmp_f5 - (((float)param_5[5] - local_8c) * 0.5 + local_8c);
              if (GHIDRA_FIELD(cg_drawCompass, 12, 4) != 2) {
                tmp_f7 = ((float)param_5[4] - tmp_f2) * 0.8;
              }
              if (tmp_f7 * tmp_f7 < tmp_f8 * tmp_f8 + tmp_f6 * tmp_f6) {
                local_8c = (float)g_unk_010ad280;
                goto LAB_0003afc0;
              }
LAB_0003b0b0:
              tmp_f4 = ((float)param_1 - tmp_f2) + tmp_f4;
              tmp_f5 = ((float)param_2 - local_8c) + tmp_f5;
              tmp_f1 = tmp_f1 / 5.159;
              goto LAB_0003b0da;
            }
            tmp_f2 = (float)param_5[2];
            if ((((tmp_f2 <= tmp_f4) && (tmp_f4 <= (float)param_5[4])) &&
                (local_8c = (float)param_5[3], local_8c <= tmp_f5)) && (tmp_f5 <= (float)param_5[5]))
            goto LAB_0003b0b0;
          }
          local_8c = (float)g_unk_010ad280;
        }
LAB_0003afc0:
        local_90 = local_90 + 1;
        tmp_pi12 = tmp_pi12 + 1;
        local_88 = local_88 + 0x80;
        pfVar11 = pfVar11 + 3;
      } while (local_90 < (int)local_8c);
    }
  }
  else {
    local_74 = -1;
  }
  return local_74;
}

void CG_DrawExpandedAutoMap(void)
{
  uint tmp_u1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint32_t tmp_u6;
  uint32_t tmp_u7;
  int tmp_i8;
  uint tmp_u9;
  int tmp_i10;
  float *pfVar11;
  uint32_t *tmp_pu12;
  uint *tmp_pu13;
  int tmp_i14;
  long double tmp_l15;
  int local_a0;
  int local_9c;
  int local_90;
  float local_88;
  int local_84;
  float local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  float local_50;
  uint32_t uStack_14;
  
  tmp_u6 = GHIDRA_FIELD(cgs, 33685964, 4);
  uStack_14 = 0x3dd59;
  tmp_f2 = (float)(g_unk_010906e0 - GHIDRA_FIELD(cgs, 33575976, 4));
  if (GHIDRA_FIELD(cgs, 33575972, 4) == 0) {
    if (250.0 <= tmp_f2) {
      return;
    }
    local_88 = (tmp_f2 / 250.0) * 382.0 + 268.0;
  }
  else {
    if (250.0 <= tmp_f2) {
      local_88 = 268.0;
      local_90 = 0x10c;
      goto LAB_0003ddd3;
    }
    local_88 = 650.0 - (tmp_f2 / 250.0) * 382.0;
  }
  local_90 = (int)ROUND(local_88);
LAB_0003ddd3:
  expanded = 0;
  local_84 = g_unk_01047b04;
  if (((g_unk_01047b04 == 0) || (g_unk_010906d8 != 0)) || (g_unk_010906d4 != 0)) {
    local_84 = g_unk_01047b00;
  }
  CG_HudPlacement(2);
  local_5c = 0x3f800000;
  local_58 = 0x3f800000;
  local_54 = 0x3f800000;
  local_50 = 0.7;
  trap_R_SetColor(&local_5c);
  CG_DrawPic(local_88,0x41a00000,0x43b00000,0x43b00000,GHIDRA_FIELD(cgs, 68476, 4));
  tmp_u7 = GHIDRA_FIELD(cgs, 68316, 4);
  if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
    tmp_u7 = *(uint32_t *)(cgs + GHIDRA_FIELD(cgs, 33685900, 4) * 4 + 0x10adc);
  }
  CG_DrawPic(local_88,0x41a00000,0x43b00000,0x43b00000,tmp_u7);
  trap_R_SetColor(0);
  CG_DrawGrid_constprop_8(local_88,0x41a00000,0x43b00000,0x43b00000);
  tmp_i8 = CG_DrawSpawnPointInfo_constprop_5(0x160,0x160,0);
  if (0 < mapEntityCount) {
    tmp_i10 = 0;
    tmp_i14 = mapEntityCount;
    tmp_pu12 = &mapEntities;
    do {
      while (((tmp_pu12[10] == *(int *)(local_84 + 0x158) || (*(int *)(local_84 + 0x158) == 3)) &&
             (2 < *(byte *)(tmp_pu12 + 5)))) {
        tmp_i10 = tmp_i10 + 1;
        CG_DrawMapEntity(tmp_pu12,local_88,0x41a00000,0x43b00000,0x43b00000,tmp_u6,0,0,local_84,6);
        tmp_i14 = mapEntityCount;
        tmp_pu12 = tmp_pu12 + 0xb;
        if (mapEntityCount <= tmp_i10) goto LAB_0003dfe4;
      }
      tmp_i10 = tmp_i10 + 1;
      tmp_pu12 = tmp_pu12 + 0xb;
    } while (tmp_i10 < tmp_i14);
  }
LAB_0003dfe4:
  tmp_u9 = CG_LimboPanel_GetRealTeam();
  if (((GHIDRA_FIELD(cgs, 33685964, 4) & 4) == 0) && (local_9c = g_unk_010ad280, 1 < g_unk_010ad280)) {
    tmp_pu13 = &g_unk_010ad084;
    pfVar11 = (float *)&g_unk_010acd8c;
    local_a0 = 1;
    do {
      if (tmp_pu13[0x40] == 0) {
        tmp_f2 = 0.0;
      }
      else {
        tmp_f2 = (float)(int)(g_unk_010906e0 - tmp_pu13[0x40]);
        if ((1000.0 < tmp_f2) || (tmp_f2 < 0.0)) {
          tmp_pu13[0x40] = 0;
          tmp_f2 = 0.0;
        }
      }
      if (((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3) || (tmp_u9 == *tmp_pu13)) &&
         (((*tmp_pu13 & 0x100) == 0 || (tmp_f2 != 0.0)))) {
        if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
          tmp_i14 = (int)ROUND(pfVar11[0x62]);
          if (((int)GHIDRA_FIELD(cgs, 33575852, 4) < tmp_i14) && (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
            if (((int)GHIDRA_FIELD(cgs, 33575856, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 1)) {
              if (((int)GHIDRA_FIELD(cgs, 33575860, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 2)) {
                if (((int)GHIDRA_FIELD(cgs, 33575864, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 3)) {
                  if (((int)GHIDRA_FIELD(cgs, 33575868, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 4)) {
                    if (((int)GHIDRA_FIELD(cgs, 33575872, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 5)) {
                      if (((int)GHIDRA_FIELD(cgs, 33575876, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 6)) {
                        if (((int)GHIDRA_FIELD(cgs, 33575880, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 7)) {
                          if (((int)GHIDRA_FIELD(cgs, 33575884, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 8)) {
                            if (((int)GHIDRA_FIELD(cgs, 33575888, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 9)) {
                              if (((int)GHIDRA_FIELD(cgs, 33575892, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 10)) {
                                if (((int)GHIDRA_FIELD(cgs, 33575896, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xb)) {
                                  if (((int)GHIDRA_FIELD(cgs, 33575900, 4) < tmp_i14) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xc))
                                  {
                                    if (((int)GHIDRA_FIELD(cgs, 33575904, 4) < tmp_i14) &&
                                       (GHIDRA_FIELD(cgs, 33575848, 4) != 0xd)) {
                                      if ((tmp_i14 <= (int)GHIDRA_FIELD(cgs, 33575908, 4)) ||
                                         (tmp_i14 = 0xf, GHIDRA_FIELD(cgs, 33575848, 4) == 0xe)) {
                                        tmp_i14 = 0xe;
                                      }
                                    }
                                    else {
                                      tmp_i14 = 0xd;
                                    }
                                  }
                                  else {
                                    tmp_i14 = 0xc;
                                  }
                                }
                                else {
                                  tmp_i14 = 0xb;
                                }
                              }
                              else {
                                tmp_i14 = 10;
                              }
                            }
                            else {
                              tmp_i14 = 9;
                            }
                          }
                          else {
                            tmp_i14 = 8;
                          }
                        }
                        else {
                          tmp_i14 = 7;
                        }
                      }
                      else {
                        tmp_i14 = 6;
                      }
                    }
                    else {
                      tmp_i14 = 5;
                    }
                  }
                  else {
                    tmp_i14 = 4;
                  }
                }
                else {
                  tmp_i14 = 3;
                }
              }
              else {
                tmp_i14 = 2;
              }
            }
            else {
              tmp_i14 = 1;
            }
            if (tmp_i14 == GHIDRA_FIELD(cgs, 33575848, 4)) {
              CG_Printf("^3Warning: no valid command map layer for z\n");
              tmp_i14 = 0;
            }
          }
          else {
            tmp_i14 = 0;
          }
          if (GHIDRA_FIELD(cgs, 33685900, 4) != tmp_i14) break;
        }
        tmp_f5 = (float)GHIDRA_FIELD(cgs, 33575916, 4) * 32.0;
        tmp_f4 = ((*pfVar11 - g_unk_010abd54) * g_unk_010abd64 * 352.0 + (float)local_90) -
                tmp_f5 * 0.3046875;
        tmp_f3 = tmp_f5 * 0.2421875 + (pfVar11[1] - g_unk_010abd58) * g_unk_010abd68 * 352.0 + 20.0;
        if (tmp_f2 == 0.0) {
          if (tmp_i8 != local_a0) {
            if (expanded == 0) {
              tmp_i14 = BG_RectContainsPoint
                                 (tmp_f4 - 16.0,tmp_f3 - 16.0,0x42000000,0x42000000,
                                  (float)g_unk_010261a4,(float)g_unk_010261a8);
              if (tmp_i14 != 0) goto LAB_0003eca6;
              tmp_f5 = (float)GHIDRA_FIELD(cgs, 33575916, 4) * 32.0;
            }
            CG_DrawPic(tmp_f4 - tmp_f5 * 0.1953125,tmp_f3 - tmp_f5 * 0.7421875,tmp_f5,tmp_f5,
                       *(uint32_t *)(cgs + ((*tmp_pu13 != 1) + 0x42d8) * 4 + 0x14));
            Com_sprintf(&local_5c,0x40,"(Troops: %i)",tmp_pu13[0x60]);
            CG_Text_Paint_Ext(tmp_f4 + 8.0,tmp_f3,0x3e4ccccd,0x3e4ccccd,&colorWhite,&local_5c,0,0,3,
                              0x110afec);
            local_9c = g_unk_010ad280;
            goto LAB_0003e090;
          }
LAB_0003eca6:
          tmp_f2 = (float)GHIDRA_FIELD(cgs, 33575916, 4) * 48.0;
          tmp_u1 = *tmp_pu13;
        }
        else {
          tmp_u1 = *tmp_pu13;
          tmp_f2 = tmp_f2 / 1000.0;
          if (tmp_u9 != tmp_u1) {
            tmp_f2 = 1.0 - tmp_f2;
          }
          tmp_f2 = tmp_f2 * 20.0 * (float)GHIDRA_FIELD(cgs, 33575916, 4);
        }
        CG_DrawPic(tmp_f4 - tmp_f2 * 0.1953125,tmp_f3 - tmp_f2 * 0.7421875,tmp_f2,tmp_f2,
                   *(uint32_t *)(cgs + ((tmp_u1 != 1) + 0x42d8) * 4 + 0x14));
        local_9c = g_unk_010ad280;
      }
LAB_0003e090:
      local_a0 = local_a0 + 1;
      tmp_pu13 = tmp_pu13 + 1;
      pfVar11 = pfVar11 + 3;
    } while (local_a0 < local_9c);
  }
  if ((g_unk_010aacfc == 0x2a) && (-1 < g_unk_010b4564)) {
    if (*(int *)(g_unk_01047b00 + 0xd0) == 0x2a) {
      local_5c = 0x3f800000;
      local_58 = 0x3f800000;
      local_54 = 0x3f800000;
      local_50 = 1.0;
      tmp_f2 = (g_unk_010b4568 - g_unk_010abd54) * g_unk_010abd64 * 352.0 + (float)local_90;
      tmp_f3 = (g_unk_010b456c - g_unk_010abd58) * g_unk_010abd68 * 352.0 + 20.0;
      if (g_unk_010b4574 != 0) {
        if (tmp_f2 + 8.0 <= (float)(local_90 + 0x160)) {
          if (tmp_f2 - 8.0 < (float)local_90) {
            tmp_f2 = tmp_f2 + 8.0;
          }
        }
        else {
          tmp_f2 = tmp_f2 - 8.0;
        }
        if (tmp_f3 + 8.0 <= 372.0) {
          tmp_f4 = tmp_f3 + 8.0;
          if (20.0 <= tmp_f3 - 8.0) {
            tmp_f4 = tmp_f3;
          }
        }
        else {
          tmp_f4 = tmp_f3 - 8.0;
        }
        local_50 = 0.5;
        tmp_f3 = tmp_f4;
      }
      trap_R_SetColor(&local_5c);
      CG_DrawRotatedPic(tmp_f2 - 8.0,tmp_f3 - 8.0,0x41800000,0x41800000,GHIDRA_FIELD(cgs, 69792, 4),
                        0.5 - (g_unk_010b4560 + 45.0) / 360.0);
      trap_R_SetColor(0);
    }
    else {
      g_unk_010b4564 = 0;
    }
  }
  tmp_i8 = COM_BitCheck(g_unk_01047b00 + 0x400,0x2a);
  if ((tmp_i8 != 0) && (0 < (int)GHIDRA_FIELD(cgs, 27400, 4))) {
    pfVar11 = (float *)&g_unk_010b4578;
    tmp_i14 = 0;
    tmp_i8 = GHIDRA_FIELD(cgs, 27400, 4);
    do {
      tmp_i10 = (-25000 - (&g_unk_010b4878)[tmp_i14]) + g_unk_010906e0;
      local_5c = 0x3f800000;
      local_58 = 0x3f800000;
      local_54 = 0x3f800000;
      local_50 = 1.0;
      if (tmp_i10 < 5000) {
        if (0 < tmp_i10) {
          local_50 = 1.0 - (float)tmp_i10 / 5000.0;
        }
        tmp_f2 = (*pfVar11 - g_unk_010abd54) * g_unk_010abd64;
        tmp_f3 = (pfVar11[1] - g_unk_010abd58) * g_unk_010abd68;
        trap_R_SetColor(&local_5c);
        CG_DrawPic((tmp_f2 * 352.0 + (float)local_90) - 8.0,(tmp_f3 * 352.0 + 20.0) - 8.0,0x41800000,
                   0x41800000,GHIDRA_FIELD(cgs, 69796, 4));
        trap_R_SetColor(0);
        tmp_i8 = GHIDRA_FIELD(cgs, 27400, 4);
      }
      tmp_i14 = tmp_i14 + 1;
      pfVar11 = pfVar11 + 3;
    } while (tmp_i14 < tmp_i8);
  }
  if (0 < mapEntityCount) {
    tmp_pu12 = &mapEntities;
    tmp_i8 = 0;
    do {
      tmp_i14 = tmp_pu12[10];
      tmp_i10 = CG_LimboPanel_GetRealTeam();
      if (((tmp_i14 == tmp_i10) ||
          ((((tmp_u9 = tmp_pu12[4], tmp_u9 < 0x40 && (*(int *)(cgs + tmp_u9 * 0x1a4 + 0x940c) != 0)) &&
            ((cg_entities[tmp_u9 * 0xaf8 + 0xe4] & 0x80) != 0)) &&
           (tmp_l15 = (long double)VectorDistance(g_unk_01047b00 + 0x40,tmp_u9 * 0xaf8 + 0x31345d4),
           (long double)512.0 <= tmp_l15)))) && (*(byte *)(tmp_pu12 + 5) < 3)) {
        CG_DrawMapEntity(tmp_pu12,local_88,0x41a00000,0x43b00000,0x43b00000,tmp_u6,0,0,local_84,6);
      }
      tmp_i8 = tmp_i8 + 1;
      tmp_pu12 = tmp_pu12 + 0xb;
    } while (tmp_i8 < mapEntityCount);
  }
  if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3) {
    tmp_f2 = (float)GHIDRA_FIELD(cgs, 33575916, 4) * 12.0;
    tmp_f3 = local_88 + (g_unk_0109143c - g_unk_010abd54) * g_unk_010abd64 * 352.0;
    tmp_f4 = (g_unk_01091440 - g_unk_010abd58) * g_unk_010abd68 * 352.0 + 20.0;
    if (*(int *)(local_84 + 0x158) == 3) {
      CG_DrawRotatedPic(tmp_f3 - tmp_f2 * 0.5,tmp_f4 - tmp_f2 * 0.5,tmp_f2,tmp_f2,GHIDRA_FIELD(cgs, 69800, 4),
                        0.625 - (g_unk_010907b0 - 180.0) / 360.0);
    }
    else {
      tmp_i8 = CG_PlayerClassForClientinfo
                        (*(int *)(local_84 + 0xcc) * 0x1a4 + 0x10f926c,
                         cg_entities + *(int *)(local_84 + 0xcc) * 0xaf8);
      tmp_f4 = tmp_f4 - tmp_f2 * 0.5;
      tmp_f3 = tmp_f3 - tmp_f2 * 0.5;
      CG_DrawPic(tmp_f3,tmp_f4,tmp_f2,tmp_f2,*(uint32_t *)(tmp_i8 + 0x28));
      CG_DrawRotatedPic(tmp_f3 - 1.0,tmp_f4 - 1.0,tmp_f2 + 2.0,tmp_f2 + 2.0,
                        *(uint32_t *)(tmp_i8 + 0x2c),0.5 - (g_unk_010907b0 - 180.0) / 360.0);
    }
  }
  tmp_f2 = local_88 - 8.0;
  local_64 = 0x41400000;
  local_60 = 0x41000000;
  local_5c = 0x41000000;
  local_68 = tmp_f2;
  CG_AdjustFrom640(&local_68,&local_64,&local_60,&local_5c);
  trap_R_DrawStretchPic(local_68,local_64,local_60,local_5c,0,0,0x3f800000,0x3f800000,GHIDRA_FIELD(cgs, 68456, 4))
  ;
  local_64 = 0x41400000;
  local_68 = local_88;
  local_60 = 0x43b00000;
  local_5c = 0x41000000;
  CG_AdjustFrom640(&local_68,&local_64,&local_60,&local_5c);
  trap_R_DrawStretchPic(local_68,local_64,local_60,local_5c,0,0,0x3fb00000,0x3f800000,GHIDRA_FIELD(cgs, 68448, 4))
  ;
  tmp_f3 = local_88 + 352.0;
  local_64 = 0x41400000;
  local_60 = 0x41000000;
  local_5c = 0x41000000;
  local_68 = tmp_f3;
  CG_AdjustFrom640(&local_68,&local_64,&local_60,&local_5c);
  trap_R_DrawStretchPic(local_68,local_64,local_60,local_5c,0x3f800000,0,0,0x3f800000,GHIDRA_FIELD(cgs, 68456, 4))
  ;
  local_64 = 0x41a00000;
  local_60 = 0x41000000;
  local_5c = 0x43b00000;
  local_68 = tmp_f3;
  CG_AdjustFrom640(&local_68,&local_64,&local_60,&local_5c);
  trap_R_DrawStretchPic(local_68,local_64,local_60,local_5c,0x3f800000,0x3fb00000,0,0,GHIDRA_FIELD(cgs, 68452, 4))
  ;
  local_64 = 0x43ba0000;
  local_60 = 0x41000000;
  local_5c = 0x41000000;
  local_68 = tmp_f3;
  CG_AdjustFrom640(&local_68,&local_64,&local_60,&local_5c);
  trap_R_DrawStretchPic(local_68,local_64,local_60,local_5c,0x3f800000,0x3f800000,0,0,GHIDRA_FIELD(cgs, 68456, 4))
  ;
  local_64 = 0x43ba0000;
  local_68 = local_88;
  local_60 = 0x43b00000;
  local_5c = 0x41000000;
  CG_AdjustFrom640(&local_68,&local_64,&local_60,&local_5c);
  trap_R_DrawStretchPic(local_68,local_64,local_60,local_5c,0x3fb00000,0x3f800000,0,0,GHIDRA_FIELD(cgs, 68448, 4))
  ;
  local_64 = 0x43ba0000;
  local_60 = 0x41000000;
  local_5c = 0x41000000;
  local_68 = tmp_f2;
  CG_AdjustFrom640(&local_68,&local_64,&local_60,&local_5c);
  trap_R_DrawStretchPic(local_68,local_64,local_60,local_5c,0,0x3f800000,0x3f800000,0,GHIDRA_FIELD(cgs, 68456, 4))
  ;
  local_64 = 0x41a00000;
  local_60 = 0x41000000;
  local_5c = 0x43b00000;
  local_68 = tmp_f2;
  CG_AdjustFrom640(&local_68,&local_64,&local_60,&local_5c);
  trap_R_DrawStretchPic(local_68,local_64,local_60,local_5c,0,0,0x3f800000,0x3fb00000,GHIDRA_FIELD(cgs, 68452, 4))
  ;
  return;
}

int CG_DrawSpawnPointInfo
              (int param_1,int param_2,int param_3,int param_4,int param_5,int *param_6,int param_7)

{
  float tmp_f1;
  float tmp_f2;
  uint tmp_u3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  float tmp_f9;
  uint tmp_u10;
  int tmp_i11;
  float *pfVar12;
  uint *tmp_pu13;
  bool tmp_b14;
  int local_8c;
  float local_88;
  uint8_t *local_84;
  int local_74;
  uint8_t local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0x3f109;
  tmp_u10 = CG_LimboPanel_GetRealTeam();
  if ((cgs[0x20201cc] & 4) == 0) {
    local_88 = (float)g_unk_010ad280;
    if (g_unk_010ad280 < 2) {
      local_74 = -1;
    }
    else {
      tmp_pu13 = &g_unk_010ad084;
      pfVar12 = (float *)&g_unk_010acd8c;
      tmp_b14 = param_5 == 0;
      local_84 = &g_unk_010abe00;
      local_74 = -1;
      local_8c = 1;
      do {
        if (tmp_pu13[0x40] == 0) {
          tmp_f4 = 0.0;
        }
        else {
          tmp_f4 = (float)(int)(g_unk_010906e0 - tmp_pu13[0x40]);
          if ((1000.0 < tmp_f4) || (tmp_f4 < 0.0)) {
            tmp_pu13[0x40] = 0;
            tmp_f4 = 0.0;
          }
        }
        if (((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3) && (*tmp_pu13 != tmp_u10)) ||
           (((*tmp_pu13 & 0x100) != 0 && (tmp_f4 == 0.0)))) goto LAB_0003f1f0;
        if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
          tmp_i11 = (int)ROUND(pfVar12[0x62]);
          if (((int)GHIDRA_FIELD(cgs, 33575852, 4) < tmp_i11) && (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
            if (((int)GHIDRA_FIELD(cgs, 33575856, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 1)) {
              if (((int)GHIDRA_FIELD(cgs, 33575860, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 2)) {
                if (((int)GHIDRA_FIELD(cgs, 33575864, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 3)) {
                  if (((int)GHIDRA_FIELD(cgs, 33575868, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 4)) {
                    if (((int)GHIDRA_FIELD(cgs, 33575872, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 5)) {
                      if (((int)GHIDRA_FIELD(cgs, 33575876, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 6)) {
                        if (((int)GHIDRA_FIELD(cgs, 33575880, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 7)) {
                          if (((int)GHIDRA_FIELD(cgs, 33575884, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 8)) {
                            if (((int)GHIDRA_FIELD(cgs, 33575888, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 9)) {
                              if (((int)GHIDRA_FIELD(cgs, 33575892, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 10)) {
                                if (((int)GHIDRA_FIELD(cgs, 33575896, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xb)) {
                                  if (((int)GHIDRA_FIELD(cgs, 33575900, 4) < tmp_i11) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xc))
                                  {
                                    if (((int)GHIDRA_FIELD(cgs, 33575904, 4) < tmp_i11) &&
                                       (GHIDRA_FIELD(cgs, 33575848, 4) != 0xd)) {
                                      if ((tmp_i11 <= (int)GHIDRA_FIELD(cgs, 33575908, 4)) ||
                                         (tmp_i11 = 0xf, GHIDRA_FIELD(cgs, 33575848, 4) == 0xe)) {
                                        tmp_i11 = 0xe;
                                      }
                                    }
                                    else {
                                      tmp_i11 = 0xd;
                                    }
                                  }
                                  else {
                                    tmp_i11 = 0xc;
                                  }
                                }
                                else {
                                  tmp_i11 = 0xb;
                                }
                              }
                              else {
                                tmp_i11 = 10;
                              }
                            }
                            else {
                              tmp_i11 = 9;
                            }
                          }
                          else {
                            tmp_i11 = 8;
                          }
                        }
                        else {
                          tmp_i11 = 7;
                        }
                      }
                      else {
                        tmp_i11 = 6;
                      }
                    }
                    else {
                      tmp_i11 = 5;
                    }
                  }
                  else {
                    tmp_i11 = 4;
                  }
                }
                else {
                  tmp_i11 = 3;
                }
              }
              else {
                tmp_i11 = 2;
              }
            }
            else {
              tmp_i11 = 1;
            }
            if (GHIDRA_FIELD(cgs, 33575848, 4) == tmp_i11) {
              CG_Printf("^3Warning: no valid command map layer for z\n");
              tmp_i11 = 0;
            }
          }
          else {
            tmp_i11 = 0;
          }
          if (GHIDRA_FIELD(cgs, 33685900, 4) != tmp_i11) {
            return local_74;
          }
        }
        if (param_6 == (int *)0x0) {
          tmp_f9 = (float)param_3 * (*pfVar12 - g_unk_010abd54) * g_unk_010abd64 + (float)param_1;
          tmp_f5 = (float)param_4 * (pfVar12[1] - g_unk_010abd58) * g_unk_010abd68 + (float)param_2;
          tmp_f1 = (float)GHIDRA_FIELD(cgs, 33575916, 4);
LAB_0003f310:
          tmp_f9 = tmp_f9 - tmp_f1 * 32.0 * 0.3046875;
          tmp_f5 = tmp_f1 * 32.0 * 0.2421875 + tmp_f5;
          if (tmp_f4 == 0.0) {
            if ((local_8c != param_7) || (tmp_b14)) {
              if ((expanded == 0) &&
                 (tmp_i11 = BG_RectContainsPoint
                                     (tmp_f9 - 16.0,tmp_f5 - 16.0,0x42000000,0x42000000,
                                      (float)g_unk_010261a4,(float)g_unk_010261a8), tmp_i11 != 0)) {
                if (!tmp_b14) goto LAB_0003f6f0;
                if (param_6 == (int *)0x0) {
                  Com_sprintf(local_5c,0x40,"%s (Troops: %i)",local_84,tmp_pu13[0x60]);
                  tmp_i11 = CG_Text_Width_Ext(local_5c,0x3e4ccccd,0,0x110afec);
                  Q_strncpyz(&cg_highlightText,local_5c,0x100);
                  expanded = 1;
                  local_88 = (float)g_unk_010ad280;
                  g_unk_00f5eb44 = tmp_f5 - 8.0;
                  local_74 = local_8c;
                  cg_highlightTextRect = tmp_f9 - (float)tmp_i11 * 0.5;
                }
                else {
                  local_88 = (float)g_unk_010ad280;
                  local_74 = local_8c;
                }
                goto LAB_0003f1f0;
              }
              if (tmp_b14) goto LAB_0003f45e;
              if (param_6 == (int *)0x0) {
                tmp_f4 = (float)GHIDRA_FIELD(cgs, 33575916, 4) * 32.0;
                CG_DrawPic(tmp_f9 - tmp_f4 * 0.1953125,tmp_f5 - tmp_f4 * 0.7421875,tmp_f4,tmp_f4,
                           *(uint32_t *)(cgs + ((*tmp_pu13 != 1) + 0x42d8) * 4 + 0x14));
                Com_sprintf(local_5c,0x40,"(Troops: %i)",tmp_pu13[0x60]);
                CG_Text_Paint_Ext(tmp_f9 + 8.0,tmp_f5,0x3e4ccccd,0x3e4ccccd,&colorWhite,local_5c,0,0,3
                                  ,0x110afec);
                local_88 = (float)g_unk_010ad280;
                goto LAB_0003f1f0;
              }
              tmp_f1 = ((float)param_6[1] / 5.159) * 32.0;
            }
            else {
LAB_0003f6f0:
              tmp_f1 = (float)GHIDRA_FIELD(cgs, 33575916, 4);
              if (param_6 != (int *)0x0) {
                tmp_f1 = (float)param_6[1] / 5.159;
              }
              tmp_f1 = tmp_f1 * 48.0;
            }
            tmp_u3 = *tmp_pu13;
          }
          else {
            if (tmp_b14) goto LAB_0003f45e;
            tmp_u3 = *tmp_pu13;
            tmp_f4 = tmp_f4 / 1000.0;
            if (tmp_u3 != tmp_u10) {
              tmp_f4 = 1.0 - tmp_f4;
            }
            tmp_f1 = (float)GHIDRA_FIELD(cgs, 33575916, 4);
            if (param_6 != (int *)0x0) {
              tmp_f1 = (float)param_6[1] / 5.159;
            }
            tmp_f1 = tmp_f1 * tmp_f4 * 20.0;
          }
          CG_DrawPic(tmp_f9 - tmp_f1 * 0.1953125,tmp_f5 - tmp_f1 * 0.7421875,tmp_f1,tmp_f1,
                     *(uint32_t *)(cgs + ((tmp_u3 != 1) + 0x42d8) * 4 + 0x14));
          local_88 = (float)g_unk_010ad280;
        }
        else {
          tmp_f1 = (float)param_6[1];
          tmp_f9 = (float)param_3 * (*pfVar12 - g_unk_010abd54) * g_unk_010abd64 * tmp_f1;
          tmp_f5 = (float)param_4 * (pfVar12[1] - g_unk_010abd58) * g_unk_010abd68 * tmp_f1;
          if (*param_6 != 0) {
            tmp_f2 = (float)param_6[2];
            tmp_f7 = ((float)param_6[4] - tmp_f2) * 0.5;
            tmp_f8 = tmp_f9 - (tmp_f2 + tmp_f7);
            local_88 = (float)param_6[3];
            tmp_f6 = tmp_f5 - (((float)param_6[5] - local_88) * 0.5 + local_88);
            if (GHIDRA_FIELD(cg_drawCompass, 12, 4) != 2) {
              tmp_f7 = ((float)param_6[4] - tmp_f2) * 0.8;
            }
            if (tmp_f7 * tmp_f7 < tmp_f6 * tmp_f6 + tmp_f8 * tmp_f8) {
              local_88 = (float)g_unk_010ad280;
              goto LAB_0003f1f0;
            }
LAB_0003f2e0:
            tmp_f9 = ((float)param_1 - tmp_f2) + tmp_f9;
            tmp_f5 = ((float)param_2 - local_88) + tmp_f5;
            tmp_f1 = tmp_f1 / 5.159;
            goto LAB_0003f310;
          }
          tmp_f2 = (float)param_6[2];
          if ((((tmp_f2 <= tmp_f9) && (tmp_f9 <= (float)param_6[4])) &&
              (local_88 = (float)param_6[3], local_88 <= tmp_f5)) && (tmp_f5 <= (float)param_6[5]))
          goto LAB_0003f2e0;
LAB_0003f45e:
          local_88 = (float)g_unk_010ad280;
        }
LAB_0003f1f0:
        local_8c = local_8c + 1;
        tmp_pu13 = tmp_pu13 + 1;
        local_84 = local_84 + 0x80;
        pfVar12 = pfVar12 + 3;
      } while (local_8c < (int)local_88);
    }
  }
  else {
    local_74 = -1;
  }
  return local_74;
}

void CG_DrawMortarMarker(int param_1,int param_2,int param_3,int param_4,uint32_t param_5,
                        int *param_6)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  int tmp_i8;
  int tmp_i9;
  float *pfVar10;
  int tmp_i11;
  float local_38;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x3fb49;
  if ((g_unk_010aacfc != 0x2a) || (g_unk_010b4564 < 0)) goto LAB_0003fba0;
  if (*(int *)(g_unk_01047b00 + 0xd0) != 0x2a) {
    g_unk_010b4564 = 0;
    goto LAB_0003fba0;
  }
  local_2c = 0x3f800000;
  local_28 = 0x3f800000;
  local_24 = 0x3f800000;
  local_20 = 1.0;
  if (param_6 == (int *)0x0) {
    tmp_f6 = (float)param_3 * (g_unk_010b4568 - g_unk_010abd54) * g_unk_010abd64 + (float)param_1;
    tmp_f1 = (float)param_4 * (g_unk_010b456c - g_unk_010abd58) * g_unk_010abd68 + (float)param_2;
    if (g_unk_010b4574 != 0) {
      if (tmp_f6 + 8.0 <= (float)(param_1 + param_3)) {
        if (tmp_f6 - 8.0 < (float)param_1) {
          tmp_f6 = tmp_f6 + 8.0;
        }
      }
      else {
        tmp_f6 = tmp_f6 - 8.0;
      }
      if (tmp_f1 + 8.0 <= (float)(param_2 + param_4)) {
        if (tmp_f1 - 8.0 < (float)param_2) {
          tmp_f1 = tmp_f1 + 8.0;
        }
      }
      else {
        tmp_f1 = tmp_f1 - 8.0;
      }
      goto LAB_0003ff7d;
    }
  }
  else {
    tmp_f6 = (float)param_3 * (g_unk_010b4568 - g_unk_010abd54) * g_unk_010abd64 * (float)param_6[1];
    tmp_f1 = (float)param_4 * (g_unk_010b456c - g_unk_010abd58) * g_unk_010abd68 * (float)param_6[1];
    if (*param_6 == 0) {
      tmp_f2 = (float)param_6[2];
      if ((((tmp_f6 < tmp_f2) || ((float)param_6[4] < tmp_f6)) ||
          (tmp_f3 = (float)param_6[3], tmp_f1 < tmp_f3)) || ((float)param_6[5] < tmp_f1))
      goto LAB_0003fba0;
    }
    else {
      tmp_f2 = (float)param_6[2];
      tmp_f5 = ((float)param_6[4] - tmp_f2) * 0.5;
      tmp_f4 = tmp_f6 - (tmp_f2 + tmp_f5);
      tmp_f3 = (float)param_6[3];
      tmp_f7 = tmp_f1 - (((float)param_6[5] - tmp_f3) * 0.5 + tmp_f3);
      if (GHIDRA_FIELD(cg_drawCompass, 12, 4) != 2) {
        tmp_f5 = ((float)param_6[4] - tmp_f2) * 0.8;
      }
      if (tmp_f5 * tmp_f5 < tmp_f7 * tmp_f7 + tmp_f4 * tmp_f4) goto LAB_0003fba0;
    }
    tmp_f6 = tmp_f6 + ((float)param_1 - tmp_f2);
    tmp_f1 = tmp_f1 + ((float)param_2 - tmp_f3);
    if (g_unk_010b4574 != 0) {
LAB_0003ff7d:
      local_20 = 0.5;
    }
  }
  trap_R_SetColor(&local_2c);
  CG_DrawRotatedPic(tmp_f6 - 8.0,tmp_f1 - 8.0,0x41800000,0x41800000,GHIDRA_FIELD(cgs, 69792, 4),
                    0.5 - (g_unk_010b4560 + 45.0) / 360.0);
  trap_R_SetColor(0);
LAB_0003fba0:
  tmp_i8 = COM_BitCheck(g_unk_01047b00 + 0x400,0x2a);
  if ((tmp_i8 != 0) && (0 < (int)GHIDRA_FIELD(cgs, 27400, 4))) {
    pfVar10 = (float *)&g_unk_010b4578;
    tmp_i11 = 0;
    tmp_i8 = GHIDRA_FIELD(cgs, 27400, 4);
    do {
      while( true ) {
        tmp_i9 = (-25000 - (&g_unk_010b4878)[tmp_i11]) + g_unk_010906e0;
        local_2c = 0x3f800000;
        local_28 = 0x3f800000;
        local_24 = 0x3f800000;
        local_20 = 1.0;
        if (tmp_i9 < 5000) break;
LAB_0003fd02:
        tmp_i11 = tmp_i11 + 1;
        pfVar10 = pfVar10 + 3;
        if (tmp_i8 <= tmp_i11) {
          return;
        }
      }
      if (0 < tmp_i9) {
        local_20 = 1.0 - (float)tmp_i9 / 5000.0;
      }
      if (param_6 == (int *)0x0) {
        local_38 = (float)param_3 * (*pfVar10 - g_unk_010abd54) * g_unk_010abd64 + (float)param_1;
        tmp_f6 = (float)param_4 * (pfVar10[1] - g_unk_010abd58) * g_unk_010abd68 + (float)param_2;
LAB_0003fc46:
        trap_R_SetColor(&local_2c);
        CG_DrawPic(local_38 - 8.0,tmp_f6 - 8.0,0x41800000,0x41800000,GHIDRA_FIELD(cgs, 69796, 4));
        trap_R_SetColor(0);
        tmp_i8 = GHIDRA_FIELD(cgs, 27400, 4);
        goto LAB_0003fd02;
      }
      local_38 = (float)param_3 * (*pfVar10 - g_unk_010abd54) * g_unk_010abd64 * (float)param_6[1];
      tmp_f6 = (float)param_4 * (pfVar10[1] - g_unk_010abd58) * g_unk_010abd68 * (float)param_6[1];
      if (*param_6 == 0) {
        tmp_f1 = (float)param_6[2];
        if (((local_38 < tmp_f1) || ((float)param_6[4] < local_38)) ||
           ((tmp_f2 = (float)param_6[3], tmp_f6 < tmp_f2 || ((float)param_6[5] < tmp_f6))))
        goto LAB_0003fd02;
LAB_0003fc30:
        local_38 = local_38 + ((float)param_1 - tmp_f1);
        tmp_f6 = tmp_f6 + ((float)param_2 - tmp_f2);
        goto LAB_0003fc46;
      }
      tmp_f1 = (float)param_6[2];
      tmp_f4 = ((float)param_6[4] - tmp_f1) * 0.5;
      tmp_f3 = local_38 - (tmp_f1 + tmp_f4);
      tmp_f2 = (float)param_6[3];
      tmp_f5 = tmp_f6 - (((float)param_6[5] - tmp_f2) * 0.5 + tmp_f2);
      if (GHIDRA_FIELD(cg_drawCompass, 12, 4) != 2) {
        tmp_f4 = ((float)param_6[4] - tmp_f1) * 0.8;
      }
      if (tmp_f5 * tmp_f5 + tmp_f3 * tmp_f3 <= tmp_f4 * tmp_f4) goto LAB_0003fc30;
      tmp_i11 = tmp_i11 + 1;
      pfVar10 = pfVar10 + 3;
    } while (tmp_i11 < tmp_i8);
  }
  return;
}

void CG_DrawMap(float param_1,float param_2,float param_3,float param_4,uint32_t param_5,
               int *param_6,int param_7,uint32_t param_8,int param_9)

{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  uint tmp_u8;
  int tmp_i9;
  float tmp_f10;
  float tmp_f11;
  float tmp_f12;
  float tmp_f13;
  float tmp_f14;
  float tmp_f15;
  float tmp_f16;
  uint32_t tmp_u17;
  int tmp_i18;
  int tmp_i19;
  uint32_t *tmp_pu20;
  int tmp_i21;
  int tmp_i22;
  long double tmp_l23;
  long double tmp_l24;
  float local_6c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x4013b;
  expanded = 0;
  tmp_i18 = g_unk_01047b00;
  if (((g_unk_01047b04 != 0) && (g_unk_010906d8 == 0)) && (g_unk_010906d4 == 0)) {
    tmp_i18 = g_unk_01047b04;
  }
  if (param_6 != (int *)0x0) {
    CG_HudPlacement(1);
    if ((float)param_6[2] <= (float)param_6[4]) {
      local_38 = param_1;
      local_34 = param_2;
      local_30 = param_3;
      local_2c = param_4;
      CG_DrawPic(param_1,param_2,param_3,param_4,GHIDRA_FIELD(cgs, 68444, 4));
      tmp_f4 = (float)param_6[1];
      tmp_f2 = (float)param_6[2];
      tmp_f3 = (float)param_6[4];
      tmp_f5 = (float)param_6[1];
      tmp_f6 = (float)param_6[3];
      tmp_f7 = (float)param_6[5];
      CG_AdjustFrom640(&local_38,&local_34,&local_30,&local_2c);
      tmp_u17 = GHIDRA_FIELD(cgs, 68380, 4);
      if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
        tmp_u17 = *(uint32_t *)(cgs + GHIDRA_FIELD(cgs, 33685900, 4) * 4 + 0x10b1c);
      }
      trap_R_DrawStretchPic
                (local_38,local_34,local_30,local_2c,tmp_f2 / (tmp_f4 * param_3),
                 tmp_f6 / (param_4 * tmp_f5),tmp_f3 / (tmp_f4 * param_3),tmp_f7 / (param_4 * tmp_f5),
                 tmp_u17);
      trap_R_DrawStretchPic(0,0,0,0,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
    }
    tmp_f4 = g_unk_010abd5c - g_unk_010abd54;
    if (gridInitDone == 0) {
      gridStep = 1200.0;
      tmp_f2 = tmp_f4 / 1200.0;
      while (tmp_f2 < 7.0) {
        gridStep = gridStep - 50.0;
        tmp_f2 = tmp_f4 / gridStep;
      }
      g_unk_002a7584 = 1200.0;
      tmp_f3 = (g_unk_010abd58 - g_unk_010abd60) / 1200.0;
      while (tmp_f3 < 7.0) {
        g_unk_002a7584 = g_unk_002a7584 - 50.0;
        tmp_f3 = (g_unk_010abd58 - g_unk_010abd60) / g_unk_002a7584;
      }
      gridStartCoord = (tmp_f2 - (float)(int)ROUND(tmp_f2)) * gridStep * 0.5;
      g_unk_002a758c = (tmp_f3 - (float)(int)ROUND(tmp_f3)) * g_unk_002a7584 * 0.5;
      gridInitDone = 1;
    }
    tmp_f5 = g_unk_010abd60 - g_unk_010abd58;
    CG_HudPlacement(1);
    tmp_f2 = (float)param_6[1];
    tmp_f10 = (param_3 * tmp_f2) / tmp_f4;
    tmp_f12 = (param_4 * tmp_f2) / -tmp_f5;
    tmp_f7 = (g_unk_010abd54 - g_unk_010abd54) * tmp_f10;
    tmp_f6 = g_unk_010abd5c - g_unk_010abd54;
    tmp_f13 = (g_unk_010abd60 - g_unk_010abd60) * tmp_f12;
    tmp_f15 = g_unk_010abd58 - g_unk_010abd60;
    tmp_f4 = gridStartCoord / tmp_f4;
    tmp_f3 = (float)param_6[2];
    tmp_f11 = (-g_unk_002a758c / tmp_f5) * param_4 * tmp_f2 - (float)param_6[3];
    tmp_f5 = tmp_f10 * gridStep;
    tmp_f14 = tmp_f12 * g_unk_002a7584;
    local_2c = clrBrownLine;
    local_28 = g_unk_0014a244;
    local_24 = g_unk_0014a248;
    local_20 = 0x3ecccccd;
    trap_R_SetColor(&local_2c);
    for (tmp_f3 = param_3 * tmp_f4 * tmp_f2 - tmp_f3; tmp_f3 < tmp_f6 * tmp_f10; tmp_f3 = tmp_f3 + tmp_f5) {
      if (tmp_f7 <= tmp_f3) {
        if (param_3 < tmp_f3) break;
        tmp_f4 = tmp_f3 + param_1;
        if (*param_6 == 0) {
          tmp_l23 = (long double)tmp_f13 + (long double)param_2;
          tmp_l24 = (long double)param_4;
        }
        else {
          tmp_f16 = param_3 * 0.5;
          tmp_f2 = param_1 + tmp_f16;
          if (tmp_f4 < tmp_f2) {
            tmp_f2 = tmp_f2 - tmp_f4;
          }
          else {
            tmp_f2 = tmp_f4 - tmp_f2;
          }
          tmp_l24 = (long double)Q_rsqrt(tmp_f16 * tmp_f16 - tmp_f2 * tmp_f2);
          tmp_l24 = (long double)1.0 / tmp_l24;
          tmp_l23 = ((long double)param_4 * (long double)0.5 + (long double)param_2) - tmp_l24;
          tmp_l24 = tmp_l24 + tmp_l24;
        }
        trap_R_DrawStretchPic
                  (tmp_f4 * (float)GHIDRA_FIELD(cgs, 27364, 4),(float)(tmp_l23 * (long double)(float)GHIDRA_FIELD(cgs, 27368, 4)),
                   0x3f800000,(float)(tmp_l24 * (long double)(float)GHIDRA_FIELD(cgs, 27368, 4)),0,0,0,0x3f800000,
                   GHIDRA_FIELD(cgs, 67836, 4));
      }
    }
    do {
      if (tmp_f15 * tmp_f12 <= tmp_f11) goto LAB_00040a34;
      if (tmp_f13 <= tmp_f11) {
        if (param_4 < tmp_f11) goto LAB_00040a34;
        if (*param_6 == 0) {
          tmp_l23 = (long double)tmp_f7 + (long double)param_1;
          tmp_l24 = (long double)param_3;
        }
        else {
          tmp_f4 = param_2 + tmp_f11;
          tmp_f3 = param_4 * 0.5;
          tmp_f2 = param_2 + tmp_f3;
          if (tmp_f4 < tmp_f2) {
            tmp_f2 = tmp_f2 - tmp_f4;
          }
          else {
            tmp_f2 = tmp_f4 - tmp_f2;
          }
          tmp_l24 = (long double)Q_rsqrt(tmp_f3 * tmp_f3 - tmp_f2 * tmp_f2);
          tmp_l24 = (long double)1.0 / tmp_l24;
          tmp_l23 = ((long double)param_3 * (long double)0.5 + (long double)param_1) - tmp_l24;
          tmp_l24 = tmp_l24 + tmp_l24;
        }
        trap_R_DrawStretchPic
                  ((float)(tmp_l23 * (long double)(float)GHIDRA_FIELD(cgs, 27364, 4)),
                   (param_2 + tmp_f11) * (float)GHIDRA_FIELD(cgs, 27368, 4),
                   (float)(tmp_l24 * (long double)(float)GHIDRA_FIELD(cgs, 27364, 4)),0x3f800000,0,0,0,0x3f800000,
                   GHIDRA_FIELD(cgs, 67836, 4));
      }
      tmp_f11 = tmp_f11 + tmp_f14;
    } while( true );
  }
  if (param_9 == 0) {
    CG_HudPlacement(2);
  }
  else {
    CG_HudPlacement(0);
  }
  local_20 = param_8;
  local_2c = 1.0;
  local_28 = 0x3f800000;
  local_24 = 0x3f800000;
  trap_R_SetColor(&local_2c);
  CG_DrawPic(param_1,param_2,param_3,param_4,GHIDRA_FIELD(cgs, 68476, 4));
  tmp_u17 = GHIDRA_FIELD(cgs, 68316, 4);
  if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
    tmp_u17 = *(uint32_t *)(cgs + GHIDRA_FIELD(cgs, 33685900, 4) * 4 + 0x10adc);
  }
  CG_DrawPic(param_1,param_2,param_3,param_4,tmp_u17);
  trap_R_SetColor(0);
  CG_DrawGrid_constprop_8(param_1,param_2,param_3,param_4);
  local_6c = 8.40779e-45;
joined_r0x000406ab:
  if (param_9 != 0) {
    local_2c = 0.0;
    local_28 = 0;
    local_24 = 0;
    local_20 = 0x3f400000;
    CG_HudPlacement(0);
    trap_R_SetColor(&local_2c);
    CG_DrawPic(param_1,param_2,param_3,param_4,GHIDRA_FIELD(cgs, 131680, 4));
    trap_R_SetColor(0);
  }
  tmp_i22 = (int)ROUND(param_4);
  tmp_i1 = (int)ROUND(param_3);
  tmp_u17 = CG_DrawSpawnPointInfo_constprop_5(tmp_i1,tmp_i22,param_6);
  if (0 < mapEntityCount) {
    if (param_7 == 0) {
      tmp_i21 = 0;
      tmp_pu20 = &mapEntities;
      do {
        while (((tmp_pu20[10] == *(int *)(tmp_i18 + 0x158) || (*(int *)(tmp_i18 + 0x158) == 3)) &&
               (2 < *(byte *)(tmp_pu20 + 5)))) {
          tmp_i21 = tmp_i21 + 1;
          CG_DrawMapEntity(tmp_pu20,param_1,param_2,param_3,param_4,param_5,param_6,0,tmp_i18,local_6c
                          );
          tmp_pu20 = tmp_pu20 + 0xb;
          if (mapEntityCount <= tmp_i21) goto LAB_00040bcb;
        }
        tmp_i21 = tmp_i21 + 1;
        tmp_pu20 = tmp_pu20 + 0xb;
      } while (tmp_i21 < mapEntityCount);
    }
    else {
      tmp_pu20 = &mapEntities;
      tmp_i21 = 0;
      do {
        tmp_i9 = tmp_pu20[10];
        tmp_i19 = CG_LimboPanel_GetRealTeam();
        if (((tmp_i9 == tmp_i19) &&
            ((tmp_pu20[10] == *(int *)(tmp_i18 + 0x158) || (*(int *)(tmp_i18 + 0x158) == 3)))) &&
           (2 < *(byte *)(tmp_pu20 + 5))) {
          CG_DrawMapEntity(tmp_pu20,param_1,param_2,param_3,param_4,param_5,param_6,param_7,tmp_i18,
                           local_6c);
        }
        tmp_i21 = tmp_i21 + 1;
        tmp_pu20 = tmp_pu20 + 0xb;
      } while (tmp_i21 < mapEntityCount);
    }
  }
LAB_00040bcb:
  CG_DrawSpawnPointInfo((int)ROUND(param_1),(int)ROUND(param_2),tmp_i1,tmp_i22,1,param_6,tmp_u17);
  CG_DrawMortarMarker((int)ROUND(param_1),(int)ROUND(param_2),tmp_i1,tmp_i22,1,param_6,tmp_u17);
  if (0 < mapEntityCount) {
    tmp_pu20 = &mapEntities;
    tmp_i22 = 0;
LAB_00040cdb:
    do {
      tmp_i1 = tmp_pu20[10];
      tmp_i21 = CG_LimboPanel_GetRealTeam();
      if (tmp_i1 == tmp_i21) {
LAB_00040c60:
        if (*(byte *)(tmp_pu20 + 5) < 3) {
          CG_DrawMapEntity(tmp_pu20,param_1,param_2,param_3,param_4,param_5,param_6,param_7,tmp_i18,
                           local_6c);
        }
      }
      else {
        tmp_u8 = tmp_pu20[4];
        if (((tmp_u8 < 0x40) && (*(int *)(cgs + tmp_u8 * 0x1a4 + 0x940c) != 0)) &&
           ((cg_entities[tmp_u8 * 0xaf8 + 0xe4] & 0x80) != 0)) {
          tmp_l23 = (long double)VectorDistance(g_unk_01047b00 + 0x40,tmp_u8 * 0xaf8 + 0x31345d4);
          if ((long double)512.0 <= tmp_l23) goto LAB_00040c60;
          tmp_i22 = tmp_i22 + 1;
          tmp_pu20 = tmp_pu20 + 0xb;
          if (mapEntityCount <= tmp_i22) break;
          goto LAB_00040cdb;
        }
      }
      tmp_i22 = tmp_i22 + 1;
      tmp_pu20 = tmp_pu20 + 0xb;
    } while (tmp_i22 < mapEntityCount);
  }
  if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3) {
    return;
  }
  if (param_6 == (int *)0x0) {
    param_3 = (g_unk_0109143c - g_unk_010abd54) * g_unk_010abd64 * param_3;
    param_4 = (g_unk_01091440 - g_unk_010abd58) * g_unk_010abd68 * param_4;
    local_6c = (float)GHIDRA_FIELD(cgs, 33575916, 4);
  }
  else {
    param_3 = (g_unk_0109143c - g_unk_010abd54) * g_unk_010abd64 * param_3 * (float)param_6[1] -
              (float)param_6[2];
    param_4 = (g_unk_01091440 - g_unk_010abd58) * g_unk_010abd68 * param_4 * (float)param_6[1] -
              (float)param_6[3];
    local_6c = (float)param_6[1] / 5.159;
  }
  local_6c = local_6c * 12.0;
  if (*(int *)(tmp_i18 + 0x158) != 3) {
    tmp_i18 = CG_PlayerClassForClientinfo
                       (*(int *)(tmp_i18 + 0xcc) * 0x1a4 + 0x10f926c,
                        cg_entities + *(int *)(tmp_i18 + 0xcc) * 0xaf8);
    tmp_f4 = (param_4 + param_2) - local_6c * 0.5;
    tmp_f2 = (param_3 + param_1) - local_6c * 0.5;
    CG_DrawPic(tmp_f2,tmp_f4,local_6c,local_6c,*(uint32_t *)(tmp_i18 + 0x28));
    CG_DrawRotatedPic(tmp_f2 - 1.0,tmp_f4 - 1.0,local_6c + 2.0,local_6c + 2.0,
                      *(uint32_t *)(tmp_i18 + 0x2c),0.5 - (g_unk_010907b0 - 180.0) / 360.0);
    return;
  }
  CG_DrawRotatedPic((param_3 + param_1) - local_6c * 0.5,(param_4 + param_2) - local_6c * 0.5,
                    local_6c,local_6c,GHIDRA_FIELD(cgs, 69800, 4),0.625 - (g_unk_010907b0 - 180.0) / 360.0);
  return;
LAB_00040a34:
  trap_R_SetColor(0);
  local_6c = 7.00649e-45;
  goto joined_r0x000406ab;
}

void CG_DrawAutoMap(void)
{
  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  float local_34 [8];
  uint32_t uStack_14;
  
  tmp_u2 = 0;
  uStack_14 = 0x4112b;
  do {
    *(uint32_t *)((int)local_34 + tmp_u2) = 0;
    *(uint32_t *)((int)local_34 + tmp_u2 + 4) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x18);
  tmp_i3 = GHIDRA_FIELD(cgs, 33685900, 4);
  if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
    tmp_i3 = (int)ROUND(g_unk_01091444);
    if (((int)GHIDRA_FIELD(cgs, 33575852, 4) < tmp_i3) && (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
      if (((int)GHIDRA_FIELD(cgs, 33575856, 4) < tmp_i3) && (1 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
        if (((int)GHIDRA_FIELD(cgs, 33575860, 4) < tmp_i3) && (2 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
          if (((int)GHIDRA_FIELD(cgs, 33575864, 4) < tmp_i3) && (3 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
            if (((int)GHIDRA_FIELD(cgs, 33575868, 4) < tmp_i3) && (4 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
              if (((int)GHIDRA_FIELD(cgs, 33575872, 4) < tmp_i3) && (5 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                if (((int)GHIDRA_FIELD(cgs, 33575876, 4) < tmp_i3) && (6 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                  if (((int)GHIDRA_FIELD(cgs, 33575880, 4) < tmp_i3) && (7 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                    if (((int)GHIDRA_FIELD(cgs, 33575884, 4) < tmp_i3) && (8 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                      if (((int)GHIDRA_FIELD(cgs, 33575888, 4) < tmp_i3) && (9 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                        if (((int)GHIDRA_FIELD(cgs, 33575892, 4) < tmp_i3) && (10 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                          if (((int)GHIDRA_FIELD(cgs, 33575896, 4) < tmp_i3) && (0xb < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                            if (((int)GHIDRA_FIELD(cgs, 33575900, 4) < tmp_i3) && (0xc < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                              if (((int)GHIDRA_FIELD(cgs, 33575904, 4) < tmp_i3) && (0xd < (int)GHIDRA_FIELD(cgs, 33575848, 4)))
                              {
                                if ((tmp_i3 <= (int)GHIDRA_FIELD(cgs, 33575908, 4)) ||
                                   (tmp_i3 = 0xf, (int)GHIDRA_FIELD(cgs, 33575848, 4) < 0xf)) {
                                  tmp_i3 = 0xe;
                                }
                              }
                              else {
                                tmp_i3 = 0xd;
                              }
                            }
                            else {
                              tmp_i3 = 0xc;
                            }
                          }
                          else {
                            tmp_i3 = 0xb;
                          }
                        }
                        else {
                          tmp_i3 = 10;
                        }
                      }
                      else {
                        tmp_i3 = 9;
                      }
                    }
                    else {
                      tmp_i3 = 8;
                    }
                  }
                  else {
                    tmp_i3 = 7;
                  }
                }
                else {
                  tmp_i3 = 6;
                }
              }
              else {
                tmp_i3 = 5;
              }
            }
            else {
              tmp_i3 = 4;
            }
          }
          else {
            tmp_i3 = 3;
          }
        }
        else {
          tmp_i3 = 2;
        }
      }
      else {
        tmp_i3 = 1;
      }
      if (GHIDRA_FIELD(cgs, 33575848, 4) == tmp_i3) {
        CG_Printf("^3Warning: no valid command map layer for z\n");
        tmp_i3 = 0;
      }
    }
    else {
      tmp_i3 = 0;
    }
  }
  GHIDRA_FIELD(cgs, 33685900, 4) = tmp_i3;
  if (((GHIDRA_FIELD(cgs, 33575972, 4) != 0) || (tmp_f1 = (float)(g_unk_010906e0 - GHIDRA_FIELD(cgs, 33575976, 4)), tmp_f1 <= 150.0)
      ) || ((150.0 < tmp_f1 && (tmp_f1 < 250.0)))) {
    CG_DrawExpandedAutoMap();
  }
  local_34[0] = 1.4013e-45;
  local_34[1] = (float)GHIDRA_FIELD(cg_automapZoom, 8, 4);
  local_34[3] = (g_unk_01091440 - g_unk_010abd58) * g_unk_010abd68 * 70.0 * (float)GHIDRA_FIELD(cg_automapZoom, 8, 4);
  local_34[2] = (g_unk_0109143c - g_unk_010abd54) * g_unk_010abd64 * 70.0 * (float)GHIDRA_FIELD(cg_automapZoom, 8, 4) -
                35.0;
  if (local_34[2] < 0.0) {
    local_34[2] = 0.0;
    local_34[4] = 70.0;
  }
  else {
    local_34[4] = local_34[2] + 70.0;
  }
  tmp_f1 = (float)GHIDRA_FIELD(cg_automapZoom, 8, 4) * 70.0;
  if (tmp_f1 < local_34[4]) {
    local_34[2] = tmp_f1 - 70.0;
    local_34[4] = tmp_f1;
    if (0.0 <= local_34[3] - 35.0) goto LAB_0004125a;
LAB_00041314:
    local_34[5] = 70.0;
    local_34[3] = 0.0;
    if (70.0 <= tmp_f1) goto LAB_00041280;
  }
  else {
    if (local_34[3] - 35.0 < 0.0) goto LAB_00041314;
LAB_0004125a:
    local_34[3] = local_34[3] - 35.0;
    local_34[5] = local_34[3] + 70.0;
    if (local_34[5] <= tmp_f1) goto LAB_00041280;
  }
  local_34[3] = tmp_f1 - 70.0;
  local_34[5] = tmp_f1;
LAB_00041280:
  CG_DrawMap(0x42580000,0x43c30000,0x428c0000,0x428c0000,GHIDRA_FIELD(cgs, 33685964, 4),local_34,0,0x3f800000,0);
  return;
}

void CG_LimboMenu_f(void)
{
  if (g_unk_010abd78 == 0) {
    CG_EventHandling(1,0);
    return;
  }
  CG_EventHandling(0,0);
  return;
}

void CG_Debriefing_ChatEdit_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  char *tmp_pc6;
  char local_11d [269];
  
  trap_Cvar_VariableStringBuffer(*(uint32_t *)(param_1 + 4),local_11d,0x101);
  if ((g_unk_010906e0 / 1000 & 1U) == 0) {
    tmp_pu3 = &g_unk_0011d7f6;
  }
  else {
    tmp_i2 = trap_Key_GetOverstrikeMode();
    if (tmp_i2 == 0) {
      tmp_pu3 = &g_unk_00112ef4;
    }
    else {
      tmp_pu3 = &g_unk_00112ef0;
    }
  }
  tmp_i2 = -1;
  Q_strcat(local_11d,0x101,tmp_pu3);
  tmp_pc6 = local_11d;
  do {
    tmp_i2 = tmp_i2 + 1;
    if (*tmp_pc6 == '\0') break;
    tmp_i4 = CG_Text_Width_Ext(tmp_pc6,**(uint32_t **)(param_1 + 0x38),0,
                              (*(uint32_t **)(param_1 + 0x38))[8]);
    tmp_pc6 = tmp_pc6 + 1;
  } while (*(float *)(param_1 + 0x10) < (float)tmp_i4);
  if (GHIDRA_FIELD(cgs, 33687744, 4) == 1) {
    tmp_pu5 = (uint8_t *)va(&g_unk_00112ef8,local_11d + tmp_i2);
  }
  else if (GHIDRA_FIELD(cgs, 33687744, 4) == 2) {
    tmp_pu5 = (uint8_t *)va(&g_unk_0011ccd0,local_11d + tmp_i2);
  }
  else if (GHIDRA_FIELD(cgs, 33687744, 4) == 0) {
    tmp_pu5 = (uint8_t *)va("^7%s",local_11d + tmp_i2);
  }
  else {
    tmp_pu5 = &g_unk_0011d841;
  }
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),
                    *(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14),*tmp_pu1,tmp_pu1[1],
                    tmp_pu1 + 2,tmp_pu5,0,0,tmp_pu1[6],tmp_pu1[8]);
  return;
}

void CG_Debriefing_PlayerTime_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int *tmp_pi3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  
  if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
    return;
  }
  tmp_i6 = 0;
  tmp_pi3 = &g_unk_01091ecc;
  if (g_unk_01091ea4 == GHIDRA_FIELD(cgs, 33686236, 4)) {
    tmp_i6 = 0;
  }
  else {
    do {
      tmp_i6 = tmp_i6 + 1;
      if (tmp_i6 == GHIDRA_FIELD(cgs, 27400, 4)) {
        return;
      }
      tmp_i4 = *tmp_pi3;
      tmp_pi3 = tmp_pi3 + 10;
    } while (tmp_i4 != GHIDRA_FIELD(cgs, 33686236, 4));
  }
  tmp_i4 = CG_Text_Width_Ext("Time: ",**(uint32_t **)(param_1 + 0x38),0,
                            (*(uint32_t **)(param_1 + 0x38))[8]);
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,tmp_pu1[1],
                    tmp_pu1 + 2,"Time:",0,0,3,tmp_pu1[8]);
  tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
  tmp_u5 = va("%i",(&g_unk_01091eb0)[tmp_i6 * 10]);
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext((float)tmp_i4 + *(float *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,
                    tmp_pu1[1],tmp_pu1 + 2,tmp_u5,0,0,3,tmp_u2);
  return;
}

void CG_Debriefing2TeamSkillHeaders_Draw(int param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  char *tmp_pc5;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x44769;
  local_2c = 0x3f19999a;
  local_28 = 0x3f19999a;
  local_24 = 0x3f19999a;
  local_20 = 0x3f800000;
  if (GHIDRA_FIELD(cg_gameType, 12, 4) != 5) {
    tmp_i2 = 0;
    while( true ) {
      tmp_i4 = 0;
      if (tmp_i2 != 0) break;
      do {
        if (tmp_i4 == 7) {
          tmp_pc5 = "Total";
        }
        else {
          tmp_pc5 = (&skillNamesLine1)[tmp_i4];
        }
        if (*tmp_pc5 != '\0') {
          tmp_i2 = CG_Text_Width_Ext(tmp_pc5,0x3e4ccccd,0,0x110afec);
          CG_Text_Paint_Ext(((float)(int)(&skillPositions)[tmp_i4] + *(float *)(param_1 + 8) + 100.0)
                            - (float)tmp_i2 * 0.5,*(float *)(param_1 + 0xc) + 0.0,0x3e4ccccd,
                            0x3e4ccccd,&local_2c,tmp_pc5,0,0,0,0x110afec);
        }
        tmp_i4 = tmp_i4 + 1;
        tmp_i2 = 1;
      } while (tmp_i4 != 8);
    }
    do {
      while( true ) {
        if (tmp_i4 == 7) {
          tmp_pc5 = "";
        }
        else {
          tmp_pc5 = (&skillNamesLine2)[tmp_i4];
        }
        if (*tmp_pc5 == '\0') break;
        tmp_i3 = CG_Text_Width_Ext(tmp_pc5,0x3e4ccccd,0,0x110afec);
        tmp_pi1 = &skillPositions + tmp_i4;
        tmp_i4 = tmp_i4 + 1;
        CG_Text_Paint_Ext(((float)*tmp_pi1 + *(float *)(param_1 + 8) + 100.0) - (float)tmp_i3 * 0.5,
                          (float)(tmp_i2 * 0xb) + *(float *)(param_1 + 0xc),0x3e4ccccd,0x3e4ccccd,
                          &local_2c,tmp_pc5,0,0,0,0x110afec);
        if (tmp_i4 == 8) {
          return;
        }
      }
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_i4 != 8);
  }
  return;
}

void CG_DebriefingPlayerWeaponStats_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int *tmp_pi3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  float local_30;
  int local_2c;
  
  local_30 = *(float *)(param_1 + 0xc);
  if (GHIDRA_FIELD(cgs, 33686256, 4) == 0) {
    return;
  }
  tmp_pi3 = (int *)(cgs + 0x2020790);
  tmp_i6 = 0;
  do {
    tmp_i5 = GHIDRA_FIELD(cgs, 33687428, 4);
    if (*tmp_pi3 != 0) goto joined_r0x000449dd;
    tmp_i6 = tmp_i6 + 1;
    tmp_pi3 = tmp_pi3 + 3;
  } while (tmp_i6 != 0x1a);
LAB_00044a2c:
  tmp_i7 = -1;
  goto LAB_00044a31;
joined_r0x000449dd:
  tmp_i7 = tmp_i6;
  if (0 < tmp_i5) {
    tmp_i5 = tmp_i5 + -1;
    tmp_i6 = tmp_i7 + 1;
    if (tmp_i6 == 0x1a) goto LAB_00044a2c;
    if (*(int *)(cgs + tmp_i6 * 0xc + 0x2020790) == 0) {
      tmp_pi3 = (int *)(cgs + tmp_i7 * 0xc + 0x20207a8);
      do {
        tmp_i6 = tmp_i6 + 1;
        if (tmp_i6 == 0x1a) goto LAB_00044a2c;
        tmp_i7 = *tmp_pi3;
        tmp_pi3 = tmp_pi3 + 3;
      } while (tmp_i7 == 0);
    }
    goto joined_r0x000449dd;
  }
LAB_00044a31:
  local_2c = 0;
  while ((local_30 = local_30 + 12.0, tmp_i7 != -1 && (local_2c < 7))) {
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    tmp_i6 = tmp_i7 * 0xc;
    CG_Text_Paint_Ext(0x41900000,local_30,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,
                      (&g_ptr_s_Knife_001152df_0xc_0013b0e8)[tmp_i7 * 3],0,0,0,tmp_pu1[8]);
    tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
    tmp_u4 = va("%i",*(uint32_t *)(cgs + tmp_i6 + 0x2020790));
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    CG_Text_Paint_Ext(0x429c0000,local_30,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u4,0,0,0,tmp_u2);
    tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
    tmp_u4 = va("%i",*(uint32_t *)(cgs + tmp_i6 + 0x202078c));
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    CG_Text_Paint_Ext(0x42ec0000,local_30,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u4,0,0,0,tmp_u2);
    tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
    tmp_u4 = va("%i",*(uint32_t *)(cgs + tmp_i6 + 0x2020788));
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    CG_Text_Paint_Ext(0x43140000,local_30,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u4,0,0,0,tmp_u2);
    tmp_i7 = tmp_i7 + 1;
    local_2c = local_2c + 1;
    if (tmp_i7 == 0x1a) {
      return;
    }
    if (*(int *)(cgs + tmp_i7 * 0xc + 0x2020790) == 0) {
      tmp_pi3 = (int *)(cgs + tmp_i6 + 0x20207a8);
      do {
        tmp_i7 = tmp_i7 + 1;
        if (tmp_i7 == 0x1a) {
          return;
        }
        tmp_i6 = *tmp_pi3;
        tmp_pi3 = tmp_pi3 + 3;
      } while (tmp_i6 == 0);
    }
  }
  return;
}

void CG_Debriefing_ChatBox_Draw(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  uint tmp_u4;
  uint tmp_u5;
  int tmp_i6;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  tmp_f1 = *(float *)(param_1 + 0x10);
  tmp_f2 = *(float *)(param_1 + 0x14);
  if (GHIDRA_FIELD(cgs, 66536, 4) != GHIDRA_FIELD(cgs, 66532, 4)) {
    tmp_i3 = GHIDRA_FIELD(cgs, 66536, 4);
    if ((int)GHIDRA_FIELD(cgs, 66536, 4) < (int)GHIDRA_FIELD(cgs, 66532, 4)) {
      do {
        tmp_i6 = tmp_i3 + 1;
        CG_Text_Width_Ext((tmp_i3 % (int)ROUND(tmp_f2)) * 0xd3 + 0x10ffb6c,0x3e4ccccd,0,0x110afec);
        tmp_i3 = tmp_i6;
      } while (tmp_i6 < (int)GHIDRA_FIELD(cgs, 66532, 4));
    }
    if ((int)GHIDRA_FIELD(cgs, 66536, 4) <= (int)(GHIDRA_FIELD(cgs, 66532, 4) - 1)) {
      tmp_u5 = GHIDRA_FIELD(cgs, 66532, 4) - 1;
      do {
        if (*(int *)(g_unk_01047b00 + 0x158) == 1) {
          local_2c = 0x3f800000;
          local_28 = 0;
          local_24 = 0;
        }
        else {
          local_2c = 0;
          if (*(int *)(g_unk_01047b00 + 0x158) == 2) {
            local_28 = 0;
            local_24 = 0x3f800000;
          }
          else {
            local_28 = 0x3f800000;
            local_24 = 0;
          }
        }
        local_20 = 0x3ea8f5c3;
        trap_R_SetColor(&local_2c);
        CG_DrawPic(*(uint32_t *)(param_1 + 8),
                   *(float *)(param_1 + 0xc) - (float)(int)(GHIDRA_FIELD(cgs, 66532, 4) - tmp_u5) * 9.0,
                   (float)(int)ROUND(tmp_f1),0x41100000,GHIDRA_FIELD(cgs, 67864, 4));
        trap_R_SetColor(0);
        tmp_i3 = (int)tmp_u5 % (int)ROUND(tmp_f2);
        if (*(int *)(cgs + tmp_i3 * 4 + 0x103c4) == 1) {
          CG_DrawPic(*(uint32_t *)(param_1 + 8),
                     (*(float *)(param_1 + 0xc) - (float)(int)(~tmp_u5 + GHIDRA_FIELD(cgs, 66532, 4)) * 9.0) - 8.0,
                     0x41400000,0x41200000,GHIDRA_FIELD(cgs, 131848, 4));
        }
        else if (*(int *)(cgs + tmp_i3 * 4 + 0x103c4) == 2) {
          CG_DrawPic(*(uint32_t *)(param_1 + 8),
                     (*(float *)(param_1 + 0xc) - (float)(int)(~tmp_u5 + GHIDRA_FIELD(cgs, 66532, 4)) * 9.0) - 8.0,
                     0x41400000,0x41200000,GHIDRA_FIELD(cgs, 131852, 4));
        }
        tmp_u4 = tmp_u5 - 1;
        CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 12.0,
                          *(float *)(param_1 + 0xc) - (float)(int)(~tmp_u5 + GHIDRA_FIELD(cgs, 66532, 4)) * 9.0,
                          0x3e4ccccd,0x3e4ccccd,&colorWhite,tmp_i3 * 0xd3 + 0x10ffb6c,0,0,0,0x110afec
                         );
        tmp_u5 = tmp_u4;
      } while ((int)GHIDRA_FIELD(cgs, 66536, 4) <= (int)tmp_u4);
    }
  }
  return;
}

void CG_Debriefing_PlayerHitReg_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x44ff9;
  local_3c = 0x3f19999a;
  local_38 = 0x3f19999a;
  local_34 = 0x3f19999a;
  local_30 = 0x3f000000;
  local_2c = 0x3f800000;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0.5;
  if (GHIDRA_FIELD(cgs, 33701692, 4) == 0) {
    return;
  }
  trap_R_SetColor(&local_3c);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) - 4.0,0x42480000,0x42480000,
             GHIDRA_FIELD(cgs, 132412, 4));
  local_20 = (float)GHIDRA_FIELD(cgs, 33701676, 4) / 100.0;
  trap_R_SetColor(0);
  trap_R_SetColor(&local_2c);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) - 4.0,0x42480000,0x42480000,
             GHIDRA_FIELD(cgs, 132416, 4));
  trap_R_SetColor(0);
  local_20 = (float)GHIDRA_FIELD(cgs, 33701680, 4) / 100.0;
  trap_R_SetColor(&local_2c);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) - 4.0,0x42480000,0x42480000,
             GHIDRA_FIELD(cgs, 132420, 4));
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) - 4.0,0x42480000,0x42480000,
             GHIDRA_FIELD(cgs, 132424, 4));
  trap_R_SetColor(0);
  local_20 = (float)GHIDRA_FIELD(cgs, 33701684, 4) / 100.0;
  trap_R_SetColor(&local_2c);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) - 4.0,0x42480000,0x42480000,
             GHIDRA_FIELD(cgs, 132428, 4));
  trap_R_SetColor(0);
  local_20 = (float)GHIDRA_FIELD(cgs, 33701688, 4) / 100.0;
  trap_R_SetColor(&local_2c);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) - 4.0,0x42480000,0x42480000,
             GHIDRA_FIELD(cgs, 132432, 4));
  trap_R_SetColor(0);
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) - 10.0,*tmp_pu1,tmp_pu1[1],
                    tmp_pu1 + 2,"Hit Regions:",0,0,3,tmp_pu1[8]);
  tmp_i3 = CG_Text_Width_Ext("Head: ",0x3e23d70a,0,*(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20));
  CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 22.0,*(float *)(param_1 + 0xc) + 8.0,0x3e23d70a,
                    0x3e23d70a,*(int *)(param_1 + 0x38) + 8,"Head:",0,0,3,
                    *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20));
  tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
  tmp_u4 = va("%.1f%%(%i)",(double)(float)GHIDRA_FIELD(cgs, 33701676, 4),GHIDRA_FIELD(cgs, 33701660, 4));
  CG_Text_Paint_Ext((float)tmp_i3 + *(float *)(param_1 + 8) + 22.0,*(float *)(param_1 + 0xc) + 8.0,
                    0x3e23d70a,0x3e23d70a,*(int *)(param_1 + 0x38) + 8,tmp_u4,0,0,3,tmp_u2);
  tmp_i3 = CG_Text_Width_Ext("Torso: ",0x3e23d70a,0,*(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20))
  ;
  CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 22.0,*(float *)(param_1 + 0xc) + 16.0,0x3e23d70a,
                    0x3e23d70a,*(int *)(param_1 + 0x38) + 8,"Torso:",0,0,3,
                    *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20));
  tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
  tmp_u4 = va("%.1f%%(%i)",(double)(float)GHIDRA_FIELD(cgs, 33701684, 4),GHIDRA_FIELD(cgs, 33701668, 4));
  CG_Text_Paint_Ext((float)tmp_i3 + *(float *)(param_1 + 8) + 22.0,*(float *)(param_1 + 0xc) + 16.0,
                    0x3e23d70a,0x3e23d70a,*(int *)(param_1 + 0x38) + 8,tmp_u4,0,0,3,tmp_u2);
  tmp_i3 = CG_Text_Width_Ext("Arms: ",0x3e23d70a,0,*(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20));
  CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 22.0,*(float *)(param_1 + 0xc) + 24.0,0x3e23d70a,
                    0x3e23d70a,*(int *)(param_1 + 0x38) + 8,"Arms:",0,0,3,
                    *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20));
  tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
  tmp_u4 = va("%.1f%%(%i)",(double)(float)GHIDRA_FIELD(cgs, 33701680, 4),GHIDRA_FIELD(cgs, 33701664, 4));
  CG_Text_Paint_Ext((float)tmp_i3 + *(float *)(param_1 + 8) + 22.0,*(float *)(param_1 + 0xc) + 24.0,
                    0x3e23d70a,0x3e23d70a,*(int *)(param_1 + 0x38) + 8,tmp_u4,0,0,3,tmp_u2);
  tmp_i3 = CG_Text_Width_Ext("Legs: ",0x3e23d70a,0,*(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20));
  CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 22.0,*(float *)(param_1 + 0xc) + 32.0,0x3e23d70a,
                    0x3e23d70a,*(int *)(param_1 + 0x38) + 8,"Legs:",0,0,3,
                    *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20));
  tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
  tmp_u4 = va("%.1f%%(%i)",(double)(float)GHIDRA_FIELD(cgs, 33701688, 4),GHIDRA_FIELD(cgs, 33701672, 4));
  CG_Text_Paint_Ext((float)tmp_i3 + *(float *)(param_1 + 8) + 22.0,*(float *)(param_1 + 0xc) + 32.0,
                    0x3e23d70a,0x3e23d70a,*(int *)(param_1 + 0x38) + 8,tmp_u4,0,0,3,tmp_u2);
  return;
}

void CG_DebriefingPlayerList_Draw(int param_1)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  int tmp_i5;
  int *tmp_pi6;
  int tmp_i7;
  float local_48;
  int local_44;
  uint8_t *local_40;
  int local_3c;
  uint32_t *local_38;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x458b9;
  local_48 = *(float *)(param_1 + 0xc) + 12.0;
  local_40 = (uint8_t *)GHIDRA_FIELD(cgs, 33687424, 4);
  if (((int)GHIDRA_FIELD(cgs, 33687424, 4) < (int)GHIDRA_FIELD(cgs, 27400, 4)) &&
     (tmp_i7 = *(int *)(cgs + GHIDRA_FIELD(cgs, 33687424, 4) * 4 + 0x20201dc),
     *(int *)(cgs + tmp_i7 * 0x1a4 + 0x940c) != 0)) {
    local_38 = (uint32_t *)0x0;
    local_44 = 0;
    tmp_i5 = GHIDRA_FIELD(cgs, 27400, 4);
    do {
      if (tmp_i5 < 1) {
        local_3c = 0;
      }
      else {
        if (tmp_i7 == g_unk_01091ea4) {
          local_3c = 0;
        }
        else {
          local_3c = 0;
          tmp_pi6 = &g_unk_01091ecc;
          do {
            local_3c = local_3c + 1;
            if (local_3c == tmp_i5) goto LAB_00045955;
            tmp_i1 = *tmp_pi6;
            tmp_pi6 = tmp_pi6 + 10;
          } while (tmp_i7 != tmp_i1);
        }
        local_38 = &g_unk_01091ea4 + local_3c * 10;
      }
      if (local_3c != tmp_i5) {
        if (tmp_i7 == GHIDRA_FIELD(cgs, 33686236, 4)) {
          local_2c = 0x3f800000;
          local_28 = 0x3f800000;
          local_24 = 0x3f800000;
          local_20 = 0x3e99999a;
          CG_FillRect(*(uint32_t *)(param_1 + 8),local_48 - 10.0,606.0 - *(float *)(param_1 + 8),
                      0x41400000,&local_2c);
        }
        tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
        local_40 = &g_unk_00112f70;
        if (*(int *)(cgs + tmp_i7 * 0x1a4 + 0x9494) - 1U < 2) {
          if (*(int *)(cgs + tmp_i7 * 0x1a4 + 0x9494) == 1) {
            local_40 = *(uint8_t **)
                        (miniRankNames_Axis + *(int *)(cgs + tmp_i7 * 0x1a4 + 0x94c0) * 4);
          }
          else {
            local_40 = *(uint8_t **)
                        (miniRankNames_Allies + *(int *)(cgs + tmp_i7 * 0x1a4 + 0x94c0) * 4);
          }
        }
        tmp_i7 = tmp_i7 * 0x1a4;
        CG_Text_Paint_Ext(0x43590000,local_48,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,local_40,0,0,0,tmp_pu2[8])
        ;
        tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
        CG_Text_Paint_Ext(0x43750000,local_48,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,tmp_i7 + 0x10f9274,0,0x1c,
                          0,tmp_pu2[8]);
        tmp_u3 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
        tmp_u4 = va("%i",local_38[3]);
        tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
        CG_Text_Paint_Ext(0x43d48000,local_48,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,tmp_u4,0,0,0,tmp_u3);
        tmp_u3 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
        tmp_u4 = va("%i",*(uint32_t *)(cgs + tmp_i7 + 0x9498));
        tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
        CG_Text_Paint_Ext(0x44104000,local_48,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,tmp_u4,0,0,0,tmp_u3);
        tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
        if (GHIDRA_FIELD(cgs, 33686252, 4) == 0) {
          CG_Text_Paint_Ext(0x43ec8000,local_48,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,&g_unk_0011cc11,0,0,0,
                            tmp_pu2[8]);
          tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
          CG_Text_Paint_Ext(0x44024000,local_48,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,&g_unk_0011cc11,0,0,0,
                            tmp_pu2[8]);
        }
        else {
          tmp_u3 = tmp_pu2[8];
          tmp_u4 = va("%i",*(uint32_t *)(cgs + tmp_i7 + 0x9584));
          tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
          CG_Text_Paint_Ext(0x43ec8000,local_48,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,tmp_u4,0,0,0,tmp_u3);
          tmp_u3 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
          tmp_u4 = va("%i",*(uint32_t *)(cgs + tmp_i7 + 0x9588));
          tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
          CG_Text_Paint_Ext(0x44024000,local_48,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,tmp_u4,0,0,0,tmp_u3);
        }
        local_48 = local_48 + 12.0;
        local_40 = (uint8_t *)GHIDRA_FIELD(cgs, 33687424, 4);
        tmp_i5 = GHIDRA_FIELD(cgs, 27400, 4);
      }
LAB_00045955:
      local_44 = local_44 + 1;
    } while ((((int)local_40 + local_44 < tmp_i5) && (local_44 != 0x18)) &&
            (tmp_i7 = *(int *)(cgs + ((int)local_40 + local_44) * 4 + 0x20201dc),
            *(int *)(cgs + tmp_i7 * 0x1a4 + 0x940c) != 0));
  }
  return;
}

void CG_DebriefingXPHeader_Draw(uint32_t param_1)
{
  if (GHIDRA_FIELD(cgs, 27388, 4) != 5) {
    BG_PanelButtonsRender_TextExt(param_1,"XP");
    return;
  }
  BG_PanelButtonsRender_TextExt(param_1,"Score");
  return;
}

uint32_t CG_Debriefing_QCButton_KeyDown(uint32_t param_1,int param_2)
{
  if (param_2 != 0xb2) {
    return 0;
  }
  CG_QuickMessage_f();
  return 1;
}

void CG_Debriefing_ChatEditFinish(int param_1)
{
  uint32_t tmp_u1;
  uint8_t local_10c [256];
  
  trap_Cvar_VariableStringBuffer(*(uint32_t *)(param_1 + 4),local_10c,0x100);
  if (GHIDRA_FIELD(cgs, 33687744, 4) == 1) {
    tmp_u1 = escape_string(local_10c);
    tmp_u1 = va("say_team %s\n",tmp_u1);
    trap_SendClientCommand(tmp_u1);
  }
  else if (GHIDRA_FIELD(cgs, 33687744, 4) == 2) {
    tmp_u1 = escape_string(local_10c);
    tmp_u1 = va("say_buddy %s\n",tmp_u1);
    trap_SendClientCommand(tmp_u1);
  }
  else if (GHIDRA_FIELD(cgs, 33687744, 4) == 0) {
    tmp_u1 = escape_string(local_10c);
    tmp_u1 = va("say %s\n",tmp_u1);
    trap_SendClientCommand(tmp_u1);
  }
  trap_Cvar_Set(*(uint32_t *)(param_1 + 4),&g_unk_0011d841);
  return;
}

uint32_t CG_Debriefing_NextButton_KeyDown(uint32_t param_1,int param_2)
{
  byte tmp_b1;
  uint32_t tmp_u2;
  
  tmp_u2 = 0;
  if (param_2 == 0xb2) {
    GHIDRA_FIELD(cgs, 33686240, 4) = (GHIDRA_FIELD(cgs, 33686240, 4) + 1) % 4;
    tmp_u2 = 1;
    if (GHIDRA_FIELD(cgs, 33686240, 4) == 0) {
      if (GHIDRA_FIELD(cgs, 27388, 4) == 7) {
        tmp_b1 = cgs[0x20390d8] & 8;
      }
      else {
        if (GHIDRA_FIELD(cgs, 27388, 4) != 8) {
          if (GHIDRA_FIELD(cgs, 27388, 4) == 6) {
            return 1;
          }
          GHIDRA_FIELD(cgs, 33686240, 4) = 1;
          return tmp_u2;
        }
        tmp_b1 = cgs[0x20390dd] & 0x40;
      }
      if (tmp_b1 == 0) {
        GHIDRA_FIELD(cgs, 33686240, 4) = 1;
        return 1;
      }
    }
  }
  return tmp_u2;
}

uint32_t CG_Debriefing2_Maps_KeyDown(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_u2 = 0;
  if ((param_2 == 0xb2) && (tmp_u2 = 1, GHIDRA_FIELD(cg_gameType, 12, 4) == 4)) {
    tmp_i1 = (int)ROUND((float)(int)GHIDRA_FIELD(cgs, 33701652, 4) +
                       ((float)(int)GHIDRA_FIELD(cgs, 67780, 4) - *(float *)(param_1 + 0xc)) / 14.0);
    if (tmp_i1 < 0) {
      tmp_u2 = 0;
    }
    else {
      tmp_u2 = 0;
      if (tmp_i1 <= GHIDRA_FIELD(cgs, 33525616, 4) + 1) {
        tmp_u2 = 1;
        GHIDRA_FIELD(cgs, 33701656, 4) = tmp_i1;
      }
    }
  }
  return tmp_u2;
}

uint32_t CG_Debriefing_ReadyButton_KeyDown(uint32_t param_1,int param_2)
{
  if (((param_2 == 0xb2) && (g_unk_01047b00 != 0)) && ((*(byte *)(g_unk_01047b00 + 0x94) & 8) == 0)) {
    trap_SendClientCommand("imready");
    return 1;
  }
  return 0;
}

uint32_t CG_Debriefing_Scrollbar_KeyUp(int param_1,int param_2)
{
  int tmp_i1;
  
  if (param_2 == 0xb2) {
    tmp_i1 = BG_PanelButtons_GetFocusButton();
    if (param_1 == tmp_i1) {
      BG_PanelButtons_SetFocusButton(0);
    }
  }
  return 0;
}

uint32_t CG_Debriefing_ChatButton_KeyDown(uint32_t param_1,int param_2)
{
  int tmp_i1;
  
  if (param_2 == 0xb2) {
    GHIDRA_FIELD(cgs, 33687744, 4) = (GHIDRA_FIELD(cgs, 33687744, 4) + 1) % 3;
    if ((0 < (int)GHIDRA_FIELD(cgs, 33687744, 4)) &&
       ((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3 ||
        ((GHIDRA_FIELD(cgs, 33687744, 4) == 2 && (tmp_i1 = CG_IsOnFireteam(g_unk_01047ac4), tmp_i1 == 0)))))) {
      GHIDRA_FIELD(cgs, 33687744, 4) = 0;
    }
    return 1;
  }
  return 0;
}

uint32_t CG_DebriefingPlayerList_KeyDown(uint32_t param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = 0;
  if (param_2 == 0xb2) {
    tmp_i2 = (GHIDRA_FIELD(cgs, 67780, 4) + -0x3c) / 0xc + GHIDRA_FIELD(cgs, 33687424, 4);
    if ((-1 < tmp_i2) && (tmp_i2 < (int)GHIDRA_FIELD(cgs, 27400, 4))) {
      tmp_i2 = *(int *)(cgs + tmp_i2 * 4 + 0x20201dc);
      tmp_u1 = 0;
      if (*(int *)(cgs + tmp_i2 * 0x1a4 + 0x940c) != 0) {
        if (((tmp_i2 < (int)GHIDRA_FIELD(cgs, 27400, 4)) && (-1 < tmp_i2)) && (GHIDRA_FIELD(cgs, 33686236, 4) != tmp_i2)) {
          GHIDRA_FIELD(cgs, 33686256, 4) = 0;
          tmp_u1 = 1;
          GHIDRA_FIELD(cgs, 33701692, 4) = 0;
          GHIDRA_FIELD(cgs, 33686236, 4) = tmp_i2;
        }
        else {
          tmp_u1 = 1;
        }
      }
    }
  }
  return tmp_u1;
}

void CG_Debriefing_PlayerName_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  
  if (((int)GHIDRA_FIELD(cgs, 33686236, 4) < 0) || ((int)GHIDRA_FIELD(cgs, 27400, 4) < (int)GHIDRA_FIELD(cgs, 33686236, 4))) {
    if ((g_unk_01047ac4 < 0) ||
       (((int)GHIDRA_FIELD(cgs, 27400, 4) <= g_unk_01047ac4 || (GHIDRA_FIELD(cgs, 33686236, 4) == g_unk_01047ac4)))) {
      tmp_i2 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
      goto LAB_00046fc0;
    }
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
  }
  tmp_i2 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
  if ((((*(int *)(cgs + GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x940c) == 0) && (-1 < g_unk_01047ac4)) &&
      (g_unk_01047ac4 < (int)GHIDRA_FIELD(cgs, 27400, 4))) && (g_unk_01047ac4 != GHIDRA_FIELD(cgs, 33686236, 4))) {
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    tmp_i2 = g_unk_01047ac4 * 0x1a4 + 0x10f926c;
  }
LAB_00046fc0:
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,tmp_pu1[1],
                    tmp_pu1 + 2,tmp_i2 + 8,0,0,3,tmp_pu1[8]);
  return;
}

void CG_Debriefing_PlayerRank_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  char *tmp_pc3;
  int tmp_i4;
  
  if (((int)GHIDRA_FIELD(cgs, 33686236, 4) < 0) || ((int)GHIDRA_FIELD(cgs, 27400, 4) < (int)GHIDRA_FIELD(cgs, 33686236, 4))) {
    if ((g_unk_01047ac4 < 0) ||
       (((int)GHIDRA_FIELD(cgs, 27400, 4) <= g_unk_01047ac4 || (GHIDRA_FIELD(cgs, 33686236, 4) == g_unk_01047ac4)))) {
      tmp_i4 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
      goto LAB_00047110;
    }
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
  }
  tmp_i4 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
  if ((((*(int *)(cgs + GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x940c) == 0) && (-1 < g_unk_01047ac4)) &&
      (g_unk_01047ac4 < (int)GHIDRA_FIELD(cgs, 27400, 4))) && (g_unk_01047ac4 != GHIDRA_FIELD(cgs, 33686236, 4))) {
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    tmp_i4 = g_unk_01047ac4 * 0x1a4 + 0x10f926c;
  }
LAB_00047110:
  tmp_i2 = CG_Text_Width_Ext("Rank: ",**(uint32_t **)(param_1 + 0x38),0,
                            (*(uint32_t **)(param_1 + 0x38))[8]);
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,tmp_pu1[1],
                    tmp_pu1 + 2,"Rank:",0,0,3,tmp_pu1[8]);
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  tmp_pc3 = "Spectator";
  if (*(int *)(tmp_i4 + 0x88) - 1U < 2) {
    if (*(int *)(tmp_i4 + 0x88) == 1) {
      tmp_pc3 = *(char **)(rankNames_Axis + *(int *)(tmp_i4 + 0xb4) * 4);
    }
    else {
      tmp_pc3 = *(char **)(rankNames_Allies + *(int *)(tmp_i4 + 0xb4) * 4);
    }
  }
  CG_Text_Paint_Ext((float)tmp_i2 + *(float *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,
                    tmp_pu1[1],tmp_pu1 + 2,tmp_pc3,0,0,3,tmp_pu1[8]);
  return;
}

void CG_Debriefing_PlayerACC_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  
  if (((int)GHIDRA_FIELD(cgs, 33686236, 4) < 0) || ((int)GHIDRA_FIELD(cgs, 27400, 4) < (int)GHIDRA_FIELD(cgs, 33686236, 4))) {
    if ((g_unk_01047ac4 < 0) ||
       (((int)GHIDRA_FIELD(cgs, 27400, 4) <= g_unk_01047ac4 || (GHIDRA_FIELD(cgs, 33686236, 4) == g_unk_01047ac4)))) {
      tmp_i5 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
      goto LAB_00047320;
    }
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
  }
  tmp_i5 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
  if ((((*(int *)(cgs + GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x940c) == 0) && (-1 < g_unk_01047ac4)) &&
      (g_unk_01047ac4 < (int)GHIDRA_FIELD(cgs, 27400, 4))) && (g_unk_01047ac4 != GHIDRA_FIELD(cgs, 33686236, 4))) {
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    tmp_i5 = g_unk_01047ac4 * 0x1a4 + 0x10f926c;
  }
LAB_00047320:
  tmp_i3 = CG_Text_Width_Ext("ACC: ",**(uint32_t **)(param_1 + 0x38),0,
                            (*(uint32_t **)(param_1 + 0x38))[8]);
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,tmp_pu1[1],
                    tmp_pu1 + 2,&g_unk_0011305f,0,0,3,tmp_pu1[8]);
  tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
  tmp_u4 = va(&g_unk_00113064,*(uint32_t *)(tmp_i5 + 0x174));
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext((float)tmp_i3 + *(float *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,
                    tmp_pu1[1],tmp_pu1 + 2,tmp_u4,0,0,3,tmp_u2);
  return;
}

void CG_Debriefing_PlayerXP_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  
  if (((int)GHIDRA_FIELD(cgs, 33686236, 4) < 0) || ((int)GHIDRA_FIELD(cgs, 27400, 4) < (int)GHIDRA_FIELD(cgs, 33686236, 4))) {
    if ((g_unk_01047ac4 < 0) ||
       (((int)GHIDRA_FIELD(cgs, 27400, 4) <= g_unk_01047ac4 || (GHIDRA_FIELD(cgs, 33686236, 4) == g_unk_01047ac4)))) {
      tmp_i5 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
      goto LAB_00047500;
    }
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
  }
  tmp_i5 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
  if ((((*(int *)(cgs + GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x940c) == 0) && (-1 < g_unk_01047ac4)) &&
      (g_unk_01047ac4 < (int)GHIDRA_FIELD(cgs, 27400, 4))) && (g_unk_01047ac4 != GHIDRA_FIELD(cgs, 33686236, 4))) {
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    tmp_i5 = g_unk_01047ac4 * 0x1a4 + 0x10f926c;
  }
LAB_00047500:
  tmp_i3 = CG_Text_Width_Ext(&g_unk_00113069,**(uint32_t **)(param_1 + 0x38),0,
                            (*(uint32_t **)(param_1 + 0x38))[8]);
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,tmp_pu1[1],
                    tmp_pu1 + 2,&g_unk_0011306e,0,0,3,tmp_pu1[8]);
  tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
  tmp_u4 = va("%i",*(uint32_t *)(tmp_i5 + 0x8c));
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext((float)tmp_i3 + *(float *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,
                    tmp_pu1[1],tmp_pu1 + 2,tmp_u4,0,0,3,tmp_u2);
  return;
}

void CG_DebriefingTitle_Draw(int param_1)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  long tmp_l5;
  int tmp_i6;
  long tmp_l7;
  
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 3) {
    tmp_u3 = CG_ConfigString(0xd);
    tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,"d");
    tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
    tmp_u3 = CG_ConfigString(0xe);
    tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,"w");
    tmp_l7 = strtol(tmp_pc4,(char **)0x0,10);
    if (GHIDRA_FIELD(cgs, 33525344, 4) == 0) {
      if (tmp_l5 == 0) {
        tmp_pc4 = "ALLIES SUCCESSFULLY BEAT THE CLOCK!";
        if (tmp_l7 == 0) {
          tmp_pc4 = "ALLIES COULDN\'T BEAT THE CLOCK!";
        }
      }
      else {
        tmp_pc4 = "AXIS SUCCESSFULLY BEAT THE CLOCK!";
        if (tmp_l5 == tmp_l7) {
          tmp_pc4 = "AXIS COULDN\'T BEAT THE CLOCK!";
        }
      }
    }
    else {
      tmp_i1 = (int)ROUND(((float)GHIDRA_FIELD(cgs, 33525348, 4) * 60.0 * 1000.0) / 1000.0);
      tmp_i6 = tmp_i1 % 0x3c;
      tmp_u3 = va("%i:%i%i",tmp_i1 / 0x3c,tmp_i6 / 10,tmp_i6 % 10);
      tmp_pc4 = (char *)va("Clock is now set to %s!",tmp_u3);
    }
  }
  else {
    tmp_u3 = CG_ConfigString(0xe);
    tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,"w");
    tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
    if (tmp_l5 == -1) {
      tmp_pc4 = "It\'s a TIE!";
    }
    else {
      tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
      if (tmp_l5 == 0) {
        tmp_pc4 = "Axis Win!";
      }
      else {
        tmp_pc4 = "Allies Win!";
      }
    }
  }
  CG_Text_Width_Ext(tmp_pc4,**(uint32_t **)(param_1 + 0x38),0,(*(uint32_t **)(param_1 + 0x38))[8]
                   );
  tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 4.0,*(uint32_t *)(param_1 + 0xc),*tmp_pu2,tmp_pu2[1],
                    tmp_pu2 + 2,tmp_pc4,0,0,0,tmp_pu2[8]);
  tmp_i6 = 0;
  if (g_unk_010906e0 - GHIDRA_FIELD(cgs, 28484, 4) < 60000) {
    tmp_i6 = 0x3c - (g_unk_010906e0 - GHIDRA_FIELD(cgs, 28484, 4)) / 1000;
  }
  tmp_u3 = va("%i seconds to next map",tmp_i6);
  tmp_i6 = CG_Text_Width_Ext(tmp_u3,**(uint32_t **)(param_1 + 0x38),0,
                            (*(uint32_t **)(param_1 + 0x38))[8]);
  tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(((*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10)) - (float)tmp_i6) - 4.0,
                    *(uint32_t *)(param_1 + 0xc),*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,tmp_u3,0,0,0,
                    tmp_pu2[8]);
  return;
}

void CG_Debriefing_PlayerMedals_Draw(int param_1)
{
  float tmp_f1;
  uint32_t *tmp_pu2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  
  if (((int)GHIDRA_FIELD(cgs, 33686236, 4) < 0) || ((int)GHIDRA_FIELD(cgs, 27400, 4) < (int)GHIDRA_FIELD(cgs, 33686236, 4))) {
    if ((g_unk_01047ac4 < 0) ||
       (((int)GHIDRA_FIELD(cgs, 27400, 4) <= g_unk_01047ac4 || (GHIDRA_FIELD(cgs, 33686236, 4) == g_unk_01047ac4)))) {
      tmp_i5 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
      goto LAB_00047a30;
    }
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
  }
  tmp_i5 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
  if ((((*(int *)(cgs + GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x940c) == 0) && (-1 < g_unk_01047ac4)) &&
      (g_unk_01047ac4 < (int)GHIDRA_FIELD(cgs, 27400, 4))) && (g_unk_01047ac4 != GHIDRA_FIELD(cgs, 33686236, 4))) {
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    tmp_i5 = g_unk_01047ac4 * 0x1a4 + 0x10f926c;
  }
LAB_00047a30:
  tmp_i4 = CG_Text_Width_Ext("Medals: ",**(uint32_t **)(param_1 + 0x38),0,
                            (*(uint32_t **)(param_1 + 0x38))[8]);
  tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
  tmp_f3 = (float)tmp_i4;
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu2,tmp_pu2[1],
                    tmp_pu2 + 2,"Medals:",0,0,3,tmp_pu2[8]);
  tmp_f1 = *(float *)(param_1 + 8);
  if (*(int *)(tmp_i5 + 0xbc) != 0) {
    CG_DrawPic(tmp_f3 + tmp_f1,*(float *)(param_1 + 0xc) - 10.0,0x41800000,0x41800000,GHIDRA_FIELD(cgs, 69860, 4));
    tmp_f1 = tmp_f1 + 18.0;
  }
  if (*(int *)(tmp_i5 + 0xc0) != 0) {
    CG_DrawPic(tmp_f3 + tmp_f1,*(float *)(param_1 + 0xc) - 10.0,0x41800000,0x41800000,GHIDRA_FIELD(cgs, 69864, 4));
    tmp_f1 = tmp_f1 + 18.0;
  }
  if (*(int *)(tmp_i5 + 0xc4) != 0) {
    CG_DrawPic(tmp_f3 + tmp_f1,*(float *)(param_1 + 0xc) - 10.0,0x41800000,0x41800000,GHIDRA_FIELD(cgs, 69868, 4));
    tmp_f1 = tmp_f1 + 18.0;
  }
  if (*(int *)(tmp_i5 + 200) != 0) {
    CG_DrawPic(tmp_f3 + tmp_f1,*(float *)(param_1 + 0xc) - 10.0,0x41800000,0x41800000,GHIDRA_FIELD(cgs, 69872, 4));
    tmp_f1 = tmp_f1 + 18.0;
  }
  if (*(int *)(tmp_i5 + 0xcc) != 0) {
    CG_DrawPic(tmp_f3 + tmp_f1,*(float *)(param_1 + 0xc) - 10.0,0x41800000,0x41800000,GHIDRA_FIELD(cgs, 69876, 4));
    tmp_f1 = tmp_f1 + 18.0;
  }
  if (*(int *)(tmp_i5 + 0xd0) != 0) {
    CG_DrawPic(tmp_f3 + tmp_f1,*(float *)(param_1 + 0xc) - 10.0,0x41800000,0x41800000,GHIDRA_FIELD(cgs, 69880, 4));
    tmp_f1 = tmp_f1 + 18.0;
  }
  if (*(int *)(tmp_i5 + 0xd4) == 0) {
    return;
  }
  CG_DrawPic(tmp_f1 + tmp_f3,*(float *)(param_1 + 0xc) - 10.0,0x41800000,0x41800000,GHIDRA_FIELD(cgs, 69884, 4));
  return;
}

void CG_Debriefing_NextButton_Draw(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  uint32_t local_50;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  local_6c = 0x3dcccccd;
  local_68 = 0x3dcccccd;
  tmp_i1 = *(int *)(param_1 + 4);
  local_64 = 0x3dcccccd;
  local_60 = 0x3f000000;
  local_5c = 0x3e99999a;
  local_58 = 0x3e99999a;
  local_54 = 0x3e99999a;
  local_50 = 0x3ecccccd;
  local_4c = 0x3f19999a;
  local_48 = 0x3f19999a;
  local_44 = 0x3f19999a;
  local_40 = 0x3f800000;
  local_3c = 0x3f000000;
  local_38 = 0x3f000000;
  local_34 = 0x3f000000;
  local_30 = 0x3ecccccd;
  local_2c = 0x3f666666;
  local_28 = 0x3f666666;
  local_24 = 0x3f666666;
  local_20 = 0x3f800000;
  tmp_i2 = BG_CursorInRect(param_1 + 8);
  if (tmp_i2 == 0) {
    CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_5c);
    CG_DrawRect_FixedBorder
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&local_6c);
    if (tmp_i1 == 0) {
      return;
    }
    tmp_i2 = CG_Text_Width_Ext(tmp_i1,0x3e4ccccd,0,0x110afec);
    tmp_pu3 = &local_4c;
  }
  else {
    CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_3c);
    CG_DrawRect_FixedBorder
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&local_6c);
    if (tmp_i1 == 0) {
      return;
    }
    tmp_i2 = CG_Text_Width_Ext(tmp_i1,0x3e4ccccd,0,0x110afec);
    tmp_pu3 = &local_2c;
  }
  CG_Text_Paint_Ext(((*(float *)(param_1 + 0x10) + 2.0) - (float)tmp_i2) * 0.5 +
                    *(float *)(param_1 + 8),*(float *)(param_1 + 0xc) + 11.0,0x3e428f5c,0x3e428f5c,
                    tmp_pu3,tmp_i1,0,0,0,0x110afec);
  return;
}

void CG_Debriefing_ChatButton_Draw(int param_1)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  char *tmp_pc3;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  uint32_t local_50;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x484a9;
  if (GHIDRA_FIELD(cgs, 33687744, 4) == 1) {
    tmp_pc3 = "^5TO TEAM";
  }
  else if (GHIDRA_FIELD(cgs, 33687744, 4) == 2) {
    tmp_pc3 = "^3TO FIRETEAM";
  }
  else {
    tmp_pc3 = "^2TO GLOBAL";
  }
  local_6c = 0x3dcccccd;
  local_68 = 0x3dcccccd;
  local_64 = 0x3dcccccd;
  local_60 = 0x3f000000;
  local_5c = 0x3e99999a;
  local_58 = 0x3e99999a;
  local_54 = 0x3e99999a;
  local_50 = 0x3ecccccd;
  local_4c = 0x3f19999a;
  local_48 = 0x3f19999a;
  local_44 = 0x3f19999a;
  local_40 = 0x3f800000;
  local_3c = 0x3f000000;
  local_38 = 0x3f000000;
  local_34 = 0x3f000000;
  local_30 = 0x3ecccccd;
  local_2c = 0x3f666666;
  local_28 = 0x3f666666;
  local_24 = 0x3f666666;
  local_20 = 0x3f800000;
  tmp_i1 = BG_CursorInRect(param_1 + 8);
  if (tmp_i1 == 0) {
    CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_5c);
    CG_DrawRect_FixedBorder
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&local_6c);
    tmp_i1 = CG_Text_Width_Ext(tmp_pc3,0x3e4ccccd,0,0x110afec);
    tmp_pu2 = &local_4c;
  }
  else {
    CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_3c);
    CG_DrawRect_FixedBorder
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&local_6c);
    tmp_i1 = CG_Text_Width_Ext(tmp_pc3,0x3e4ccccd,0,0x110afec);
    tmp_pu2 = &local_2c;
  }
  CG_Text_Paint_Ext(((*(float *)(param_1 + 0x10) + 2.0) - (float)tmp_i1) * 0.5 +
                    *(float *)(param_1 + 8),*(float *)(param_1 + 0xc) + 11.0,0x3e428f5c,0x3e428f5c,
                    tmp_pu2,tmp_pc3,0,0,0,0x110afec);
  return;
}

void CG_Debriefing_ReadyButton_Draw(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  uint32_t local_50;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  if ((g_unk_01047b00 != 0) && ((*(byte *)(g_unk_01047b00 + 0x94) & 8) == 0)) {
    tmp_i1 = *(int *)(param_1 + 4);
    local_6c = 0x3dcccccd;
    local_68 = 0x3dcccccd;
    local_64 = 0x3dcccccd;
    local_60 = 0x3f000000;
    local_5c = 0x3e99999a;
    local_58 = 0x3e99999a;
    local_54 = 0x3e99999a;
    local_50 = 0x3ecccccd;
    local_4c = 0x3f19999a;
    local_48 = 0x3f19999a;
    local_44 = 0x3f19999a;
    local_40 = 0x3f800000;
    local_3c = 0x3f000000;
    local_38 = 0x3f000000;
    local_34 = 0x3f000000;
    local_30 = 0x3ecccccd;
    local_2c = 0x3f666666;
    local_28 = 0x3f666666;
    local_24 = 0x3f666666;
    local_20 = 0x3f800000;
    tmp_i2 = BG_CursorInRect(param_1 + 8);
    if (tmp_i2 == 0) {
      CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                  *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_5c);
      CG_DrawRect_FixedBorder
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&local_6c);
      if (tmp_i1 == 0) {
        return;
      }
      tmp_i2 = CG_Text_Width_Ext(tmp_i1,0x3e4ccccd,0,0x110afec);
      tmp_pu3 = &local_4c;
    }
    else {
      CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                  *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_3c);
      CG_DrawRect_FixedBorder
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&local_6c);
      if (tmp_i1 == 0) {
        return;
      }
      tmp_i2 = CG_Text_Width_Ext(tmp_i1,0x3e4ccccd,0,0x110afec);
      tmp_pu3 = &local_2c;
    }
    CG_Text_Paint_Ext(((*(float *)(param_1 + 0x10) + 2.0) - (float)tmp_i2) * 0.5 +
                      *(float *)(param_1 + 8),*(float *)(param_1 + 0xc) + 11.0,0x3e428f5c,0x3e428f5c
                      ,tmp_pu3,tmp_i1,0,0,0,0x110afec);
  }
  return;
}

void CG_Debriefing_PlayerSkills_Draw(int param_1)
{
  float tmp_f1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  float local_38;
  int local_34;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x48a29;
  if (((int)GHIDRA_FIELD(cgs, 33686236, 4) < 0) || ((int)GHIDRA_FIELD(cgs, 27400, 4) < (int)GHIDRA_FIELD(cgs, 33686236, 4))) {
    if ((g_unk_01047ac4 < 0) ||
       (((int)GHIDRA_FIELD(cgs, 27400, 4) <= g_unk_01047ac4 || (GHIDRA_FIELD(cgs, 33686236, 4) == g_unk_01047ac4)))) {
      local_34 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
      goto LAB_00048ab0;
    }
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
  }
  local_34 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
  if ((((*(int *)(cgs + GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x940c) == 0) && (-1 < g_unk_01047ac4)) &&
      (g_unk_01047ac4 != GHIDRA_FIELD(cgs, 33686236, 4))) && (g_unk_01047ac4 < (int)GHIDRA_FIELD(cgs, 27400, 4))) {
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    local_34 = g_unk_01047ac4 * 0x1a4 + 0x10f926c;
  }
LAB_00048ab0:
  tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) - 2.0,*tmp_pu2,tmp_pu2[1],
                    tmp_pu2 + 2,(&skillNames)[*(int *)(param_1 + 0x18)],0,0,3,tmp_pu2[8]);
  local_38 = *(float *)(param_1 + 8);
  CG_DrawPic(local_38,*(uint32_t *)(param_1 + 0xc),*(uint32_t *)(param_1 + 0x10),
             *(uint32_t *)(param_1 + 0x14),
             *(uint32_t *)(cgs + *(int *)(param_1 + 0x18) * 4 + 0x11084));
  tmp_f1 = *(float *)(param_1 + 0x10);
  tmp_i3 = *(int *)(local_34 + 0xd8 + *(int *)(param_1 + 0x18) * 4);
  local_38 = local_38 + (tmp_f1 - 4.0);
  if (0 < tmp_i3) {
    do {
      CG_DrawPicST(local_38 + 4.0,*(float *)(param_1 + 0xc) + 1.0,tmp_f1 * 0.8,
                   *(float *)(param_1 + 0x14) * 0.8,0,0,0x3f800000,0x3f000000,GHIDRA_FIELD(cgs, 131544, 4));
      tmp_i3 = tmp_i3 + -1;
      tmp_f1 = *(float *)(param_1 + 0x10);
      local_38 = (tmp_f1 - 4.0) + local_38;
    } while (tmp_i3 != 0);
  }
  local_2c = 0x3f800000;
  local_28 = 0x3f800000;
  local_24 = 0x3f800000;
  local_20 = 0x3e4ccccd;
  trap_R_SetColor(&local_2c);
  tmp_i3 = *(int *)(local_34 + 0xd8 + *(int *)(param_1 + 0x18) * 4);
  if (tmp_i3 < 5) {
    tmp_f1 = *(float *)(param_1 + 0x10);
    do {
      tmp_i3 = tmp_i3 + 1;
      CG_DrawPicST(local_38 + 4.0,*(float *)(param_1 + 0xc) + 1.0,tmp_f1 * 0.8,
                   *(float *)(param_1 + 0x14) * 0.8,0,0,0x3f800000,0x3f000000,GHIDRA_FIELD(cgs, 131544, 4));
      tmp_f1 = *(float *)(param_1 + 0x10);
      local_38 = (tmp_f1 - 4.0) + local_38;
    } while (tmp_i3 != 5);
  }
  trap_R_SetColor(0);
  return;
}

void CG_Debriefing_Startup(void)
{
  byte tmp_b1;
  uint32_t tmp_u2;
  char *__nptr;
  long tmp_l3;
  
  GHIDRA_FIELD(cgs, 33686256, 4) = 0;
  GHIDRA_FIELD(cgs, 33686252, 4) = 0;
  GHIDRA_FIELD(cgs, 33701692, 4) = 0;
  GHIDRA_FIELD(cgs, 33687416, 4) = 0;
  GHIDRA_FIELD(cgs, 33686244, 4) = 1;
  GHIDRA_FIELD(cgs, 33686248, 4) = 0;
  GHIDRA_FIELD(cgs, 33701084, 4) = 0xffffffff;
  GHIDRA_FIELD(cgs, 33701080, 4) = 0xffffffff;
  GHIDRA_FIELD(cgs, 33701088, 4) = 0xffffffff;
  GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
  GHIDRA_FIELD(cgs, 33701068, 4) = 0xffffffff;
  GHIDRA_FIELD(cgs, 33701072, 4) = 0;
  GHIDRA_FIELD(cgs, 33686260, 4) = 0;
  tmp_u2 = CG_ConfigString(0xe);
  __nptr = (char *)Info_ValueForKey(tmp_u2,"w");
  trap_Cvar_Set("chattext",&g_unk_0011d841);
  tmp_l3 = strtol(__nptr,(char **)0x0,10);
  if (tmp_l3 != -1) {
    tmp_l3 = strtol(__nptr,(char **)0x0,10);
    if (tmp_l3 == 0) {
      trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 132368, 4),6);
    }
    else {
      trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 132372, 4),6);
    }
  }
  if (GHIDRA_FIELD(cgs, 27388, 4) == 7) {
    tmp_b1 = cgs[0x20390d8] & 8;
  }
  else {
    if (GHIDRA_FIELD(cgs, 27388, 4) != 8) {
      GHIDRA_FIELD(cgs, 33686240, 4) = (uint)(GHIDRA_FIELD(cgs, 27388, 4) != 6);
      return;
    }
    tmp_b1 = cgs[0x20390dd] & 0x40;
  }
  if (tmp_b1 != 0) {
    GHIDRA_FIELD(cgs, 33686240, 4) = 0;
    return;
  }
  GHIDRA_FIELD(cgs, 33686240, 4) = 1;
  return;
}

void CG_Debriefing_Shutdown(void)
{
  GHIDRA_FIELD(cgs, 33686244, 4) = 0;
  return;
}

void CG_Debriefing_InfoRequests(void)
{
  byte tmp_b1;
  uint32_t tmp_u2;
  
  if ((GHIDRA_FIELD(cgs, 33687416, 4) != 0) && (g_unk_010906e0 - GHIDRA_FIELD(cgs, 33687416, 4) < 1000)) {
    return;
  }
  GHIDRA_FIELD(cgs, 33687416, 4) = g_unk_010906e0;
  if (GHIDRA_FIELD(cgs, 33701072, 4) != 0) {
LAB_000492f5:
    if (GHIDRA_FIELD(cgs, 33686252, 4) == 0) {
      trap_SendClientCommand("impkd");
      return;
    }
    if (GHIDRA_FIELD(cgs, 33686248, 4) != 0) {
      if (GHIDRA_FIELD(cgs, 33686256, 4) == 0) {
        tmp_u2 = va(&g_unk_0011313c,GHIDRA_FIELD(cgs, 33686236, 4));
        trap_SendClientCommand(tmp_u2);
        if (GHIDRA_FIELD(cgs, 33701692, 4) == 0) {
          tmp_u2 = va("imhr %i",GHIDRA_FIELD(cgs, 33686236, 4));
          trap_SendClientCommand(tmp_u2);
        }
      }
      else if ((GHIDRA_FIELD(cgs, 33687420, 4) == 0) || (1000 < g_unk_010906e0 - GHIDRA_FIELD(cgs, 33687420, 4))) {
        GHIDRA_FIELD(cgs, 33687420, 4) = g_unk_010906e0;
        trap_SendClientCommand("score");
      }
      return;
    }
    trap_SendClientCommand(&g_unk_00113137);
    return;
  }
  if (GHIDRA_FIELD(cgs, 27388, 4) != 6) {
    if (GHIDRA_FIELD(cgs, 27388, 4) == 7) {
      tmp_b1 = cgs[0x20390d8] & 8;
    }
    else {
      if (GHIDRA_FIELD(cgs, 27388, 4) != 8) goto LAB_000492f5;
      tmp_b1 = cgs[0x20390dd] & 0x40;
    }
    if (tmp_b1 == 0) goto LAB_000492f5;
  }
  trap_SendClientCommand("immaplist");
  return;
}

uint32_t CG_Debriefing_Draw(void)
{
  uint32_t __nmemb;
  uint tmp_u1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  
  if (GHIDRA_FIELD(cgs, 33686244, 4) == 0) {
    CG_Debriefing_Startup();
  }
  CG_HudPlacement(0);
  CG_Debriefing_InfoRequests();
  tmp_u1 = trap_Key_GetCatcher();
  if ((tmp_u1 & 2) == 0) {
    tmp_i2 = trap_Key_GetCatcher();
    if (tmp_i2 == 0) {
      trap_Key_SetCatcher(8);
    }
    if ((g_unk_01091e7c + 1000 < g_unk_010906e0) && (GHIDRA_FIELD(cgs, 33686240, 4) == 0)) {
      g_unk_01091e7c = g_unk_010906e0;
      trap_SendClientCommand("imvotetally");
    }
    __nmemb = GHIDRA_FIELD(cgs, 27400, 4);
    if (GHIDRA_FIELD(cgs, 33686240, 4) == 1) {
      CG_DrawScoreboard();
    }
    else {
      if ((int)GHIDRA_FIELD(cgs, 33686240, 4) < 2) {
        if (GHIDRA_FIELD(cgs, 33686240, 4) != 0) {
          return 1;
        }
        tmp_pu3 = mapVoteButtons;
      }
      else if (GHIDRA_FIELD(cgs, 33686240, 4) == 2) {
        tmp_pu3 = teamDebriefPanelButtons;
      }
      else {
        if (GHIDRA_FIELD(cgs, 33686240, 4) != 3) {
          return 1;
        }
        if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
          tmp_i2 = 0;
          do {
            *(int *)(cgs + tmp_i2 * 4 + 0x20201dc) = tmp_i2;
            tmp_i2 = tmp_i2 + 1;
          } while (tmp_i2 != __nmemb);
        }
        qsort(cgs + 0x20201dc,__nmemb,4,CG_SortPlayersByXP);
        tmp_pu3 = debriefPanelButtons;
      }
      BG_PanelButtonsRender(tmp_pu3);
    }
    BG_PanelButtonsRender(chatPanelButtons);
    CG_DrawPic((float)g_unk_010261a4,(float)g_unk_010261a8,0x42000000,0x42000000,GHIDRA_FIELD(cgs, 131752, 4));
    return 1;
  }
  return 1;
}

int CG_Debriefing_GetNextWeaponStat(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  
  tmp_i2 = param_1 + 1;
  if (tmp_i2 < 0x1a) {
    if (*(int *)(cgs + tmp_i2 * 0xc + 0x2020790) == 0) {
      tmp_pi3 = (int *)(cgs + param_1 * 0xc + 0x20207a8);
      do {
        tmp_i2 = tmp_i2 + 1;
        if (tmp_i2 == 0x1a) goto LAB_00049660;
        tmp_i1 = *tmp_pi3;
        tmp_pi3 = tmp_pi3 + 3;
      } while (tmp_i1 == 0);
    }
  }
  else {
LAB_00049660:
    tmp_i2 = -1;
  }
  return tmp_i2;
}

void CG_Debriefing_TimeToString(float param_1)
{
  int tmp_i1;
  
  tmp_i1 = (int)ROUND(param_1 / 1000.0) % 0x3c;
  va("%i:%i%i",(int)ROUND(param_1 / 1000.0) / 0x3c,tmp_i1 / 10,tmp_i1 % 10);
  return;
}

char * CG_Debriefing_FullRankNameForClientInfo(int param_1)
{
  if (1 < *(int *)(param_1 + 0x88) - 1U) {
    return "Spectator";
  }
  if (*(int *)(param_1 + 0x88) != 1) {
    return *(char **)(rankNames_Allies + *(int *)(param_1 + 0xb4) * 4);
  }
  return *(char **)(rankNames_Axis + *(int *)(param_1 + 0xb4) * 4);
}

uint8_t * CG_Debriefing_RankNameForClientInfo(int param_1)
{
  if (1 < *(int *)(param_1 + 0x88) - 1U) {
    return &g_unk_00112f70;
  }
  if (*(int *)(param_1 + 0x88) != 1) {
    return *(uint8_t **)(miniRankNames_Allies + *(int *)(param_1 + 0xb4) * 4);
  }
  return *(uint8_t **)(miniRankNames_Axis + *(int *)(param_1 + 0xb4) * 4);
}

void CG_Debriefing_ParseWeaponAccuracies(void)
{
  char *__nptr;
  long tmp_l1;
  int tmp_i2;
  long *plVar3;
  
  if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
    tmp_i2 = 0;
    plVar3 = (long *)(cgs + 0x9580);
    do {
      tmp_i2 = tmp_i2 + 1;
      __nptr = (char *)CG_Argv(tmp_i2);
      tmp_l1 = strtol(__nptr,(char **)0x0,10);
      *plVar3 = tmp_l1;
      plVar3 = plVar3 + 0x69;
    } while (tmp_i2 < (int)GHIDRA_FIELD(cgs, 27400, 4));
  }
  GHIDRA_FIELD(cgs, 33686248, 4) = 1;
  return;
}

void CG_Debriefing_ParsePlayerKillsDeaths(void)
{
  char *tmp_pc1;
  long tmp_l2;
  int tmp_i3;
  int tmp_i4;
  long *plVar5;
  
  if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
    tmp_i4 = 0;
    tmp_i3 = 1;
    plVar5 = (long *)(cgs + 0x9584);
    do {
      tmp_i4 = tmp_i4 + 1;
      tmp_pc1 = (char *)CG_Argv(tmp_i3);
      tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
      *plVar5 = tmp_l2;
      tmp_pc1 = (char *)CG_Argv(tmp_i4 * 2);
      tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
      plVar5[1] = tmp_l2;
      tmp_i3 = tmp_i3 + 2;
      plVar5 = plVar5 + 0x69;
    } while (tmp_i4 < (int)GHIDRA_FIELD(cgs, 27400, 4));
  }
  GHIDRA_FIELD(cgs, 33686252, 4) = 1;
  return;
}

void CG_Debriefing_ParseWeaponStats(void)
{
  int tmp_i1;
  char *tmp_pc2;
  long tmp_l3;
  int tmp_i4;
  long *plVar5;
  
  tmp_i4 = 1;
  plVar5 = (long *)(cgs + 0x2020790);
  do {
    tmp_pc2 = (char *)CG_Argv(tmp_i4);
    tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    *plVar5 = tmp_l3;
    tmp_pc2 = (char *)CG_Argv(tmp_i4 + 1);
    tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    plVar5[-1] = tmp_l3;
    tmp_i1 = tmp_i4 + 2;
    tmp_i4 = tmp_i4 + 3;
    tmp_pc2 = (char *)CG_Argv(tmp_i1);
    tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    plVar5[-2] = tmp_l3;
    plVar5 = plVar5 + 3;
  } while (tmp_i4 != 0x4f);
  GHIDRA_FIELD(cgs, 33686256, 4) = 1;
  return;
}

void CG_Debriefing_ParseHitRegions(void)
{
  int tmp_i1;
  char *tmp_pc2;
  long tmp_l3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  double tmp_d6;
  
  tmp_i4 = 1;
  tmp_pu5 = cgs;
  do {
    tmp_pc2 = (char *)CG_Argv(tmp_i4);
    tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    *(long *)(cgs + (int)(tmp_pu5 + 0xf340bc)) = tmp_l3;
    tmp_i1 = tmp_i4 + 1;
    tmp_i4 = tmp_i4 + 2;
    tmp_pc2 = (char *)CG_Argv(tmp_i1);
    tmp_d6 = strtod(tmp_pc2,(char **)0x0);
    *(float *)(cgs + (int)(tmp_pu5 + 0xf340cc)) = (float)tmp_d6;
    tmp_pu5 = tmp_pu5 + 4;
  } while (tmp_i4 != 9);
  GHIDRA_FIELD(cgs, 33701692, 4) = 1;
  return;
}

uint32_t CG_Debriefing_ServerCommand(uint32_t param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  long tmp_l4;
  int tmp_i5;
  long *plVar6;
  uint8_t *tmp_pu7;
  double tmp_d8;
  
  tmp_i1 = Q_stricmp(param_1,&g_unk_00113137);
  if (tmp_i1 == 0) {
    if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
      tmp_i1 = 0;
      plVar6 = (long *)(cgs + 0x9580);
      do {
        tmp_i1 = tmp_i1 + 1;
        tmp_pc3 = (char *)CG_Argv(tmp_i1);
        tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
        *plVar6 = tmp_l4;
        plVar6 = plVar6 + 0x69;
      } while (tmp_i1 < (int)GHIDRA_FIELD(cgs, 27400, 4));
    }
    GHIDRA_FIELD(cgs, 33686248, 4) = 1;
    return 1;
  }
  tmp_i1 = Q_stricmp(param_1,&g_unk_00113158);
  if (tmp_i1 == 0) {
    tmp_i1 = 1;
    plVar6 = (long *)(cgs + 0x2020790);
    do {
      tmp_pc3 = (char *)CG_Argv(tmp_i1);
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      *plVar6 = tmp_l4;
      tmp_pc3 = (char *)CG_Argv(tmp_i1 + 1);
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      plVar6[-1] = tmp_l4;
      tmp_i5 = tmp_i1 + 2;
      tmp_i1 = tmp_i1 + 3;
      tmp_pc3 = (char *)CG_Argv(tmp_i5);
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      plVar6[-2] = tmp_l4;
      plVar6 = plVar6 + 3;
    } while (tmp_i1 != 0x4f);
    tmp_u2 = 1;
    GHIDRA_FIELD(cgs, 33686256, 4) = 1;
  }
  else {
    tmp_i1 = Q_stricmp(param_1,&g_unk_0011315d);
    if (tmp_i1 == 0) {
      tmp_i1 = 1;
      tmp_pu7 = cgs;
      do {
        tmp_pc3 = (char *)CG_Argv(tmp_i1);
        tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
        *(long *)(cgs + (int)(tmp_pu7 + 0xf340bc)) = tmp_l4;
        tmp_i5 = tmp_i1 + 1;
        tmp_i1 = tmp_i1 + 2;
        tmp_pc3 = (char *)CG_Argv(tmp_i5);
        tmp_d8 = strtod(tmp_pc3,(char **)0x0);
        *(float *)(cgs + (int)(tmp_pu7 + 0xf340cc)) = (float)tmp_d8;
        tmp_pu7 = tmp_pu7 + 4;
      } while (tmp_i1 != 9);
      GHIDRA_FIELD(cgs, 33701692, 4) = 1;
      return 1;
    }
    tmp_i1 = Q_stricmp(param_1,"impkd");
    tmp_u2 = 0;
    if (tmp_i1 == 0) {
      if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
        tmp_i1 = 1;
        tmp_i5 = 0;
        plVar6 = (long *)(cgs + 0x9584);
        do {
          tmp_i5 = tmp_i5 + 1;
          tmp_pc3 = (char *)CG_Argv(tmp_i1);
          tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
          *plVar6 = tmp_l4;
          tmp_pc3 = (char *)CG_Argv(tmp_i5 * 2);
          tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
          tmp_i1 = tmp_i1 + 2;
          plVar6[1] = tmp_l4;
          plVar6 = plVar6 + 0x69;
        } while (tmp_i5 < (int)GHIDRA_FIELD(cgs, 27400, 4));
      }
      tmp_u2 = 1;
      GHIDRA_FIELD(cgs, 33686252, 4) = 1;
    }
  }
  return tmp_u2;
}

uint32_t CG_Debriefing_ScrollGetMax(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 0;
  if (*(uint *)(param_1 + 0x18) < 4) {
    tmp_u1 = *(uint32_t *)(CSWTCH_63 + *(uint *)(param_1 + 0x18) * 4);
  }
  return tmp_u1;
}

int CG_Debriefing_ScrollGetCount(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int *tmp_pi4;
  
  tmp_i1 = *(int *)(param_1 + 0x18);
  if (tmp_i1 == 1) {
    tmp_i2 = 0;
    if (GHIDRA_FIELD(cgs, 33686256, 4) != 0) {
      tmp_pi4 = (int *)(cgs + 0x2020790);
      do {
        if (*tmp_pi4 != 0) {
          tmp_i2 = tmp_i2 + 1;
        }
        tmp_pi4 = tmp_pi4 + 3;
      } while (tmp_pi4 != (int *)(cgs + 0x20208c8));
      return tmp_i2;
    }
  }
  else if (tmp_i1 < 2) {
    if (tmp_i1 != 0) {
      return 0;
    }
    tmp_i2 = GHIDRA_FIELD(cgs, 27400, 4);
    if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
      tmp_i1 = *(int *)(cgs + GHIDRA_FIELD(cgs, 33685980, 4) * 0x1a4 + 0x940c);
      tmp_i2 = 0;
      while ((tmp_i1 != 0 && (tmp_i3 = tmp_i2 + 1, tmp_i2 = GHIDRA_FIELD(cgs, 27400, 4), tmp_i3 != GHIDRA_FIELD(cgs, 27400, 4)))) {
        tmp_i1 = *(int *)(cgs + *(int *)(cgs + tmp_i3 * 4 + 0x20201dc) * 0x1a4 + 0x940c);
        tmp_i2 = tmp_i3;
      }
    }
  }
  else if (tmp_i1 == 2) {
    tmp_i2 = 0;
    if (GHIDRA_FIELD(cgs, 33526364, 4) != 0) {
      return GHIDRA_FIELD(cgs, 33571584, 4);
    }
  }
  else {
    tmp_i2 = GHIDRA_FIELD(cgs, 33687752, 4);
    if (tmp_i1 != 3) {
      return 0;
    }
  }
  return tmp_i2;
}

uint32_t CG_Debriefing_ScrollGetOffset(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x18);
  if (tmp_i1 == 1) {
    return GHIDRA_FIELD(cgs, 33687428, 4);
  }
  if (tmp_i1 < 2) {
    if (tmp_i1 == 0) {
      return GHIDRA_FIELD(cgs, 33687424, 4);
    }
  }
  else {
    if (tmp_i1 == 2) {
      return GHIDRA_FIELD(cgs, 33701652, 4);
    }
    if (tmp_i1 == 3) {
      return GHIDRA_FIELD(cgs, 33687748, 4);
    }
  }
  return 0;
}

void CG_Debriefing_ScrollSetOffset(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x18);
  if (tmp_i1 == 1) {
    GHIDRA_FIELD(cgs, 33687428, 4) = param_2;
    return;
  }
  if (tmp_i1 < 2) {
    if (tmp_i1 == 0) {
      GHIDRA_FIELD(cgs, 33687424, 4) = param_2;
      return;
    }
  }
  else {
    if (tmp_i1 == 2) {
      GHIDRA_FIELD(cgs, 33701652, 4) = param_2;
      return;
    }
    if (tmp_i1 == 3) {
      GHIDRA_FIELD(cgs, 33687748, 4) = param_2;
    }
  }
  return;
}

int CG_Debriefing_ScrollGetBarRect(int param_1,uint32_t *param_2)
{
  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  float tmp_f4;
  int tmp_i5;
  int tmp_i6;
  int *tmp_pi7;
  int tmp_i8;
  int local_14;
  
  local_14 = 0;
  tmp_u2 = *(uint *)(param_1 + 0x18);
  if (tmp_u2 < 4) {
    local_14 = *(int *)(CSWTCH_63 + tmp_u2 * 4);
  }
  tmp_i8 = GHIDRA_FIELD(cgs, 33687428, 4);
  if (tmp_u2 == 1) {
    tmp_i5 = 0;
    if (GHIDRA_FIELD(cgs, 33686256, 4) != 0) {
      tmp_i5 = 0;
      tmp_pi7 = (int *)(cgs + 0x2020790);
      do {
        if (*tmp_pi7 != 0) {
          tmp_i5 = tmp_i5 + 1;
        }
        tmp_pi7 = tmp_pi7 + 3;
      } while (tmp_pi7 != (int *)(cgs + 0x20208c8));
    }
    goto joined_r0x0004a009;
  }
  tmp_i8 = GHIDRA_FIELD(cgs, 33687424, 4);
  if ((int)tmp_u2 < 2) {
    if (tmp_u2 == 0) {
      tmp_i5 = GHIDRA_FIELD(cgs, 27400, 4);
      if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
        tmp_i3 = *(int *)(cgs + GHIDRA_FIELD(cgs, 33685980, 4) * 0x1a4 + 0x940c);
        tmp_i5 = 0;
        while ((tmp_i3 != 0 && (tmp_i6 = tmp_i5 + 1, tmp_i5 = GHIDRA_FIELD(cgs, 27400, 4), tmp_i6 != GHIDRA_FIELD(cgs, 27400, 4)))) {
          tmp_i3 = *(int *)(cgs + *(int *)(cgs + tmp_i6 * 4 + 0x20201dc) * 0x1a4 + 0x940c);
          tmp_i5 = tmp_i6;
        }
      }
      goto joined_r0x0004a009;
    }
  }
  else {
    if (tmp_u2 == 2) {
      tmp_i8 = GHIDRA_FIELD(cgs, 33701652, 4);
      tmp_i5 = 0;
      if (GHIDRA_FIELD(cgs, 33526364, 4) != 0) {
        tmp_i5 = GHIDRA_FIELD(cgs, 33571584, 4);
      }
      goto joined_r0x0004a009;
    }
    tmp_i8 = GHIDRA_FIELD(cgs, 33687748, 4);
    tmp_i5 = GHIDRA_FIELD(cgs, 33687752, 4);
    if (tmp_u2 == 3) goto joined_r0x0004a009;
  }
  if (tmp_u2 == 1) {
    tmp_i5 = 0;
    tmp_i8 = GHIDRA_FIELD(cgs, 33687428, 4);
    goto joined_r0x0004a009;
  }
  if ((int)tmp_u2 < 2) {
    if (tmp_u2 == 0) {
      tmp_i5 = 0;
      tmp_i8 = GHIDRA_FIELD(cgs, 33687424, 4);
      goto joined_r0x0004a009;
    }
  }
  else {
    if (tmp_u2 == 2) {
      tmp_i8 = GHIDRA_FIELD(cgs, 33701652, 4);
      tmp_i5 = 0;
      goto joined_r0x0004a009;
    }
    if (tmp_u2 == 3) {
      tmp_i5 = 0;
      tmp_i8 = GHIDRA_FIELD(cgs, 33687748, 4);
      goto joined_r0x0004a009;
    }
  }
  tmp_i5 = 0;
  tmp_i8 = 0;
joined_r0x0004a009:
  if (local_14 < tmp_i5) {
    tmp_f1 = *(float *)(param_1 + 0x14);
    tmp_f4 = (float)local_14;
    local_14 = tmp_i5 - local_14;
    tmp_f4 = (tmp_f4 / (float)tmp_i5) * tmp_f1;
    param_2[3] = tmp_f4;
    param_2[1] = (tmp_f1 - tmp_f4) * ((float)tmp_i8 / (float)local_14) + *(float *)(param_1 + 0xc);
  }
  else {
    param_2[3] = *(uint32_t *)(param_1 + 0x14);
    param_2[1] = *(uint32_t *)(param_1 + 0xc);
  }
  *param_2 = *(uint32_t *)(param_1 + 8);
  param_2[2] = *(uint32_t *)(param_1 + 0x10);
  return local_14;
}

void CG_Debriefing_ScrollCheckOffset(int param_1)
{
  uint tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int *tmp_pi4;
  int tmp_i5;
  int local_14;
  
  tmp_u1 = *(uint *)(param_1 + 0x18);
  local_14 = 0;
  if (tmp_u1 < 4) {
    local_14 = *(int *)(CSWTCH_63 + tmp_u1 * 4);
  }
  if (tmp_u1 == 1) {
    tmp_i5 = 0;
    if (GHIDRA_FIELD(cgs, 33686256, 4) != 0) {
      tmp_pi4 = (int *)(cgs + 0x2020790);
      do {
        if (*tmp_pi4 != 0) {
          tmp_i5 = tmp_i5 + 1;
        }
        tmp_pi4 = tmp_pi4 + 3;
      } while (tmp_pi4 != (int *)(cgs + 0x20208c8));
    }
LAB_0004a2f0:
    tmp_i5 = tmp_i5 - local_14;
    if (tmp_i5 < 0) {
      tmp_i5 = 0;
    }
    tmp_i2 = GHIDRA_FIELD(cgs, 33687428, 4);
    if (tmp_i5 < (int)GHIDRA_FIELD(cgs, 33687428, 4)) {
      GHIDRA_FIELD(cgs, 33687428, 4) = tmp_i5;
      return;
    }
  }
  else {
    if (1 < (int)tmp_u1) {
      if (tmp_u1 == 2) {
        tmp_i5 = 0;
        if (GHIDRA_FIELD(cgs, 33526364, 4) != 0) {
          tmp_i5 = GHIDRA_FIELD(cgs, 33571584, 4);
        }
LAB_0004a218:
        tmp_i5 = tmp_i5 - local_14;
        if (tmp_i5 < 0) {
          tmp_i5 = 0;
        }
        tmp_i2 = GHIDRA_FIELD(cgs, 33701652, 4);
        if (tmp_i5 < (int)GHIDRA_FIELD(cgs, 33701652, 4)) {
          GHIDRA_FIELD(cgs, 33701652, 4) = tmp_i5;
          return;
        }
        goto LAB_0004a1dd;
      }
      tmp_i5 = GHIDRA_FIELD(cgs, 33687752, 4);
      if (tmp_u1 != 3) goto LAB_0004a318;
LAB_0004a1c4:
      tmp_i5 = tmp_i5 - local_14;
      if (tmp_i5 < 0) {
        tmp_i5 = 0;
      }
      tmp_i2 = GHIDRA_FIELD(cgs, 33687748, 4);
      if (tmp_i5 < (int)GHIDRA_FIELD(cgs, 33687748, 4)) {
        GHIDRA_FIELD(cgs, 33687748, 4) = tmp_i5;
        return;
      }
      goto LAB_0004a1dd;
    }
    if (tmp_u1 == 0) {
      tmp_i5 = GHIDRA_FIELD(cgs, 27400, 4);
      if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
        tmp_i2 = *(int *)(cgs + GHIDRA_FIELD(cgs, 33685980, 4) * 0x1a4 + 0x940c);
        tmp_i5 = 0;
        while ((tmp_i2 != 0 && (tmp_i3 = tmp_i5 + 1, tmp_i5 = GHIDRA_FIELD(cgs, 27400, 4), tmp_i3 != GHIDRA_FIELD(cgs, 27400, 4)))) {
          tmp_i2 = *(int *)(cgs + *(int *)(cgs + tmp_i3 * 4 + 0x20201dc) * 0x1a4 + 0x940c);
          tmp_i5 = tmp_i3;
        }
      }
    }
    else {
LAB_0004a318:
      if (tmp_u1 == 1) {
        tmp_i5 = 0;
        goto LAB_0004a2f0;
      }
      if (1 < (int)tmp_u1) {
        if (tmp_u1 == 2) {
          tmp_i5 = 0;
          goto LAB_0004a218;
        }
        if (tmp_u1 != 3) {
          return;
        }
        tmp_i5 = 0;
        goto LAB_0004a1c4;
      }
      if (tmp_u1 != 0) {
        return;
      }
      tmp_i5 = 0;
    }
    tmp_i5 = tmp_i5 - local_14;
    if (tmp_i5 < 0) {
      tmp_i5 = 0;
    }
    tmp_i2 = GHIDRA_FIELD(cgs, 33687424, 4);
    if (tmp_i5 < (int)GHIDRA_FIELD(cgs, 33687424, 4)) {
      GHIDRA_FIELD(cgs, 33687424, 4) = tmp_i5;
      return;
    }
  }
LAB_0004a1dd:
  if (tmp_i2 < 0) {
    if (tmp_u1 == 1) {
      GHIDRA_FIELD(cgs, 33687428, 4) = 0;
    }
    else if ((int)tmp_u1 < 2) {
      if (tmp_u1 == 0) {
        GHIDRA_FIELD(cgs, 33687424, 4) = 0;
      }
    }
    else if (tmp_u1 == 2) {
      GHIDRA_FIELD(cgs, 33701652, 4) = 0;
    }
    else if (tmp_u1 == 3) {
      GHIDRA_FIELD(cgs, 33687748, 4) = 0;
    }
  }
  return;
}

void CG_Debriefing_Scrollbar_Draw(int param_1)
{
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_2c = 0x3e24a4a5;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_28 = 0x3e4ccccd;
  local_24 = 0x3e2cacad;
  local_20 = 0x3f4ccccd;
  local_10 = 0x3f19999a;
  CG_Debriefing_ScrollCheckOffset(param_1);
  CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
              *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_1c);
  CG_DrawRect_FixedBorder
            (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
             *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,colorMdGrey);
  CG_Debriefing_ScrollGetBarRect(param_1,&local_3c);
  CG_FillRect(local_3c,local_38,local_34,local_30,&local_2c);
  CG_DrawRect_FixedBorder(local_3c,local_38,local_34,local_30,1,colorMdGrey);
  return;
}

uint32_t CG_Debriefing_Scrollbar_KeyDown(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  uint8_t local_1c [4];
  float local_18;
  
  if (param_2 == 0xb2) {
    CG_Debriefing_ScrollGetBarRect(param_1,local_1c);
    tmp_i2 = BG_CursorInRect(local_1c);
    if (tmp_i2 == 0) {
      return 0;
    }
    BG_PanelButtons_SetFocusButton(param_1);
    *(uint32_t *)(param_1 + 0x1c) = 0;
    *(int *)(param_1 + 0x20) = (int)ROUND((float)(int)GHIDRA_FIELD(cgs, 67780, 4) - local_18);
    return 0;
  }
  if (param_2 == 0xb7) {
    tmp_i2 = *(int *)(param_1 + 0x18);
    if (tmp_i2 == 1) {
      if (GHIDRA_FIELD(cgs, 33686256, 4) == 0) {
        return 0;
      }
      tmp_pi3 = (int *)(cgs + 0x2020790);
      tmp_i2 = 0;
      do {
        if (*tmp_pi3 != 0) {
          tmp_i2 = tmp_i2 + 1;
        }
        tmp_pi3 = tmp_pi3 + 3;
      } while (tmp_pi3 != (int *)(cgs + 0x20208c8));
      if (tmp_i2 == 0) {
        return 0;
      }
      GHIDRA_FIELD(cgs, 33687428, 4) = GHIDRA_FIELD(cgs, 33687428, 4) + 1;
    }
    else if (tmp_i2 < 2) {
      if (tmp_i2 != 0) {
        return 0;
      }
      tmp_i2 = GHIDRA_FIELD(cgs, 27400, 4);
      if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
        tmp_i2 = 0;
        tmp_i1 = *(int *)(cgs + GHIDRA_FIELD(cgs, 33685980, 4) * 0x1a4 + 0x940c);
        while (tmp_i1 != 0) {
          tmp_i2 = tmp_i2 + 1;
          if (tmp_i2 == GHIDRA_FIELD(cgs, 27400, 4)) goto LAB_0004a6df;
          tmp_i1 = *(int *)(cgs + *(int *)(cgs + tmp_i2 * 4 + 0x20201dc) * 0x1a4 + 0x940c);
        }
      }
      if (tmp_i2 == 0) {
        return 0;
      }
LAB_0004a6df:
      GHIDRA_FIELD(cgs, 33687424, 4) = GHIDRA_FIELD(cgs, 33687424, 4) + 1;
    }
    else if (tmp_i2 == 2) {
      if (GHIDRA_FIELD(cgs, 33526364, 4) == 0) {
        return 0;
      }
      if (GHIDRA_FIELD(cgs, 33571584, 4) == 0) {
        return 0;
      }
      GHIDRA_FIELD(cgs, 33701652, 4) = GHIDRA_FIELD(cgs, 33701652, 4) + 1;
    }
    else {
      if (tmp_i2 != 3) {
        return 0;
      }
      if (GHIDRA_FIELD(cgs, 33687752, 4) == 0) {
        return 0;
      }
      GHIDRA_FIELD(cgs, 33687748, 4) = GHIDRA_FIELD(cgs, 33687748, 4) + 1;
    }
  }
  else {
    if (param_2 != 0xb8) {
      return 0;
    }
    tmp_i2 = *(int *)(param_1 + 0x18);
    if (tmp_i2 == 1) {
      if (GHIDRA_FIELD(cgs, 33686256, 4) == 0) {
        return 0;
      }
      tmp_pi3 = (int *)(cgs + 0x2020790);
      tmp_i2 = 0;
      do {
        if (*tmp_pi3 != 0) {
          tmp_i2 = tmp_i2 + 1;
        }
        tmp_pi3 = tmp_pi3 + 3;
      } while (tmp_pi3 != (int *)(cgs + 0x20208c8));
      if (tmp_i2 == 0) {
        return 0;
      }
      GHIDRA_FIELD(cgs, 33687428, 4) = GHIDRA_FIELD(cgs, 33687428, 4) + -1;
    }
    else if (tmp_i2 < 2) {
      if (tmp_i2 != 0) {
        return 0;
      }
      tmp_i2 = GHIDRA_FIELD(cgs, 27400, 4);
      if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
        tmp_i2 = 0;
        tmp_i1 = *(int *)(cgs + GHIDRA_FIELD(cgs, 33685980, 4) * 0x1a4 + 0x940c);
        while (tmp_i1 != 0) {
          tmp_i2 = tmp_i2 + 1;
          if (tmp_i2 == GHIDRA_FIELD(cgs, 27400, 4)) goto LAB_0004a74f;
          tmp_i1 = *(int *)(cgs + *(int *)(cgs + tmp_i2 * 4 + 0x20201dc) * 0x1a4 + 0x940c);
        }
      }
      if (tmp_i2 == 0) {
        return 0;
      }
LAB_0004a74f:
      GHIDRA_FIELD(cgs, 33687424, 4) = GHIDRA_FIELD(cgs, 33687424, 4) + -1;
    }
    else if (tmp_i2 == 2) {
      if (GHIDRA_FIELD(cgs, 33526364, 4) == 0) {
        return 0;
      }
      if (GHIDRA_FIELD(cgs, 33571584, 4) == 0) {
        return 0;
      }
      GHIDRA_FIELD(cgs, 33701652, 4) = GHIDRA_FIELD(cgs, 33701652, 4) + -1;
    }
    else {
      if (tmp_i2 != 3) {
        return 0;
      }
      if (GHIDRA_FIELD(cgs, 33687752, 4) == 0) {
        return 0;
      }
      GHIDRA_FIELD(cgs, 33687748, 4) = GHIDRA_FIELD(cgs, 33687748, 4) + -1;
    }
  }
  CG_Debriefing_ScrollCheckOffset(param_1);
  return 0;
}

void CG_Debriefing_MouseEvent(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int *tmp_pi5;
  int tmp_i6;
  int local_40;
  uint8_t local_2c [4];
  float local_28;
  float local_20;
  
  if ((((GHIDRA_FIELD(cgs, 33686240, 4) != 0) && (GHIDRA_FIELD(cgs, 33686240, 4) != 3)) ||
      (tmp_i2 = BG_PanelButtons_GetFocusButton(), tmp_i2 == 0)) ||
     (*(void **)(tmp_i2 + 0x44) != CG_Debriefing_Scrollbar_Draw)) {
    GHIDRA_FIELD(cgs, 67776, 4) = param_1 + GHIDRA_FIELD(cgs, 67776, 4);
    if ((int)GHIDRA_FIELD(cgs, 67776, 4) < 0) {
      GHIDRA_FIELD(cgs, 67776, 4) = 0;
    }
    else if (0x280 < (int)GHIDRA_FIELD(cgs, 67776, 4)) {
      GHIDRA_FIELD(cgs, 67776, 4) = 0x280;
    }
    GHIDRA_FIELD(cgs, 67780, 4) = param_2 + GHIDRA_FIELD(cgs, 67780, 4);
    if (-1 < (int)GHIDRA_FIELD(cgs, 67780, 4)) {
      if ((int)GHIDRA_FIELD(cgs, 67780, 4) < 0x1e1) {
        return;
      }
      GHIDRA_FIELD(cgs, 67780, 4) = 0x1e0;
      return;
    }
    GHIDRA_FIELD(cgs, 67780, 4) = 0;
    return;
  }
  tmp_i1 = *(int *)(tmp_i2 + 0x18);
  if (tmp_i1 == 1) {
    tmp_i6 = 0;
    if (GHIDRA_FIELD(cgs, 33686256, 4) != 0) {
      tmp_pi5 = (int *)(cgs + 0x2020790);
      tmp_i6 = 0;
      do {
        if (*tmp_pi5 != 0) {
          tmp_i6 = tmp_i6 + 1;
        }
        tmp_pi5 = tmp_pi5 + 3;
      } while (tmp_pi5 != (int *)(cgs + 0x20208c8));
    }
  }
  else if (tmp_i1 < 2) {
    if (tmp_i1 == 0) {
      tmp_i6 = GHIDRA_FIELD(cgs, 27400, 4);
      if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
        tmp_i1 = *(int *)(cgs + GHIDRA_FIELD(cgs, 33685980, 4) * 0x1a4 + 0x940c);
        tmp_i6 = 0;
        while ((tmp_i1 != 0 && (tmp_i4 = tmp_i6 + 1, tmp_i6 = GHIDRA_FIELD(cgs, 27400, 4), tmp_i4 != GHIDRA_FIELD(cgs, 27400, 4)))) {
          tmp_i1 = *(int *)(cgs + *(int *)(cgs + tmp_i4 * 4 + 0x20201dc) * 0x1a4 + 0x940c);
          tmp_i6 = tmp_i4;
        }
      }
    }
    else {
LAB_0004ab95:
      tmp_i6 = 0;
    }
  }
  else if (tmp_i1 == 2) {
    tmp_i6 = 0;
    if (GHIDRA_FIELD(cgs, 33526364, 4) != 0) {
      tmp_i6 = GHIDRA_FIELD(cgs, 33571584, 4);
    }
  }
  else {
    tmp_i6 = GHIDRA_FIELD(cgs, 33687752, 4);
    if (tmp_i1 != 3) goto LAB_0004ab95;
  }
  CG_Debriefing_ScrollGetBarRect(tmp_i2,local_2c);
  param_2 = param_2 + *(int *)(tmp_i2 + 0x1c);
  *(int *)(tmp_i2 + 0x1c) = param_2;
  tmp_i1 = (int)ROUND(((float)(param_2 * tmp_i6) * 0.5) / local_20);
  if (tmp_i1 == 0) goto LAB_0004a9d0;
  tmp_i4 = *(int *)(tmp_i2 + 0x18);
  if (tmp_i4 == 1) {
    local_40 = GHIDRA_FIELD(cgs, 33687428, 4);
    GHIDRA_FIELD(cgs, 33687428, 4) = GHIDRA_FIELD(cgs, 33687428, 4) + tmp_i1;
LAB_0004aa73:
    CG_Debriefing_ScrollCheckOffset(tmp_i2);
    tmp_i4 = *(int *)(tmp_i2 + 0x18);
    tmp_i3 = GHIDRA_FIELD(cgs, 33687428, 4);
    if (tmp_i4 != 1) {
      if (tmp_i4 < 2) {
        tmp_i3 = GHIDRA_FIELD(cgs, 33687424, 4);
        if (tmp_i4 != 0) goto LAB_0004abe1;
      }
      else {
        tmp_i3 = GHIDRA_FIELD(cgs, 33701652, 4);
        if ((tmp_i4 != 2) && (tmp_i3 = GHIDRA_FIELD(cgs, 33687748, 4), tmp_i4 != 3)) {
LAB_0004abe1:
          tmp_i3 = 0;
        }
      }
    }
  }
  else {
    if (1 < tmp_i4) {
      if (tmp_i4 == 2) {
        local_40 = GHIDRA_FIELD(cgs, 33701652, 4);
        GHIDRA_FIELD(cgs, 33701652, 4) = GHIDRA_FIELD(cgs, 33701652, 4) + tmp_i1;
      }
      else {
        if (tmp_i4 != 3) goto LAB_0004ac15;
        local_40 = GHIDRA_FIELD(cgs, 33687748, 4);
        GHIDRA_FIELD(cgs, 33687748, 4) = GHIDRA_FIELD(cgs, 33687748, 4) + tmp_i1;
      }
      goto LAB_0004aa73;
    }
    if (tmp_i4 == 0) {
      local_40 = GHIDRA_FIELD(cgs, 33687424, 4);
      GHIDRA_FIELD(cgs, 33687424, 4) = GHIDRA_FIELD(cgs, 33687424, 4) + tmp_i1;
      goto LAB_0004aa73;
    }
LAB_0004ac15:
    if (tmp_i4 == 1) {
      local_40 = 0;
      GHIDRA_FIELD(cgs, 33687428, 4) = tmp_i1;
      goto LAB_0004aa73;
    }
    if (1 < tmp_i4) {
      if (tmp_i4 == 2) {
        local_40 = 0;
        GHIDRA_FIELD(cgs, 33701652, 4) = tmp_i1;
      }
      else {
        if (tmp_i4 != 3) goto LAB_0004ac2d;
        local_40 = 0;
        GHIDRA_FIELD(cgs, 33687748, 4) = tmp_i1;
      }
      goto LAB_0004aa73;
    }
    if (tmp_i4 == 0) {
      local_40 = 0;
      GHIDRA_FIELD(cgs, 33687424, 4) = tmp_i1;
      goto LAB_0004aa73;
    }
LAB_0004ac2d:
    local_40 = 0;
    CG_Debriefing_ScrollCheckOffset(tmp_i2);
    tmp_i4 = *(int *)(tmp_i2 + 0x18);
    tmp_i3 = GHIDRA_FIELD(cgs, 33687428, 4);
    if (tmp_i4 != 1) {
      if (tmp_i4 < 2) {
        tmp_i3 = GHIDRA_FIELD(cgs, 33687424, 4);
        if (tmp_i4 != 0) goto LAB_0004a9d0;
      }
      else {
        tmp_i3 = GHIDRA_FIELD(cgs, 33701652, 4);
        if ((tmp_i4 != 2) && (tmp_i3 = GHIDRA_FIELD(cgs, 33687748, 4), tmp_i4 != 3)) goto LAB_0004a9d0;
      }
    }
  }
  if (tmp_i3 - local_40 == tmp_i1) {
    *(int *)(tmp_i2 + 0x1c) =
         (int)ROUND((float)*(int *)(tmp_i2 + 0x1c) - (local_20 / (float)tmp_i6) * (float)tmp_i1);
  }
LAB_0004a9d0:
  CG_Debriefing_ScrollGetBarRect(tmp_i2,local_2c);
  GHIDRA_FIELD(cgs, 67780, 4) = (int)ROUND((float)*(int *)(tmp_i2 + 0x20) + local_28);
  return;
}

void CG_Debriefing_KeyEvent(int param_1,int param_2)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  
  if (GHIDRA_FIELD(cgs, 33686240, 4) == 2) {
    tmp_pu2 = teamDebriefPanelButtons;
  }
  else if (GHIDRA_FIELD(cgs, 33686240, 4) == 3) {
    tmp_pu2 = debriefPanelButtons;
  }
  else {
    if (GHIDRA_FIELD(cgs, 33686240, 4) != 0) goto LAB_0004ad24;
    tmp_pu2 = mapVoteButtons;
  }
  tmp_i1 = BG_PanelButtonsKeyEvent(param_1,param_2,tmp_pu2);
  if (tmp_i1 != 0) {
    return;
  }
LAB_0004ad24:
  tmp_i1 = BG_PanelButtonsKeyEvent(param_1,param_2,chatPanelButtons);
  if ((((tmp_i1 == 0) && (tmp_i1 = BG_PanelButtons_GetFocusButton(), tmp_i1 == 0)) && (param_2 != 0))
     && (param_1 != 0xb2)) {
    BG_PanelButtons_SetFocusButton(charPanelEdit);
    BG_PanelButton_EditClick(charPanelEdit,param_1);
    BG_PanelButtons_SetFocusButton(0);
  }
  return;
}

int CG_Debriefing_GetSelectedClientInfo(void)
{
  int tmp_i1;
  
  if (((int)GHIDRA_FIELD(cgs, 33686236, 4) < 0) || ((int)GHIDRA_FIELD(cgs, 27400, 4) < (int)GHIDRA_FIELD(cgs, 33686236, 4))) {
    if ((g_unk_01047ac4 < 0) ||
       (((int)GHIDRA_FIELD(cgs, 27400, 4) <= g_unk_01047ac4 || (GHIDRA_FIELD(cgs, 33686236, 4) == g_unk_01047ac4)))) {
      return GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
    }
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
  }
  tmp_i1 = GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x10f926c;
  if ((((*(int *)(cgs + GHIDRA_FIELD(cgs, 33686236, 4) * 0x1a4 + 0x940c) == 0) && (-1 < g_unk_01047ac4)) &&
      (g_unk_01047ac4 < (int)GHIDRA_FIELD(cgs, 27400, 4))) && (g_unk_01047ac4 != GHIDRA_FIELD(cgs, 33686236, 4))) {
    GHIDRA_FIELD(cgs, 33686236, 4) = g_unk_01047ac4;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
    tmp_i1 = g_unk_01047ac4 * 0x1a4 + 0x10f926c;
  }
  return tmp_i1;
}

long double CG_Debriefing_CalcCampaignProgress(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if ((GHIDRA_FIELD(cgs, 33526364, 4) != 0) && (0 < (int)GHIDRA_FIELD(cgs, 33571584, 4))) {
    tmp_i3 = 0;
    tmp_i2 = 0x30e9940;
    do {
      tmp_i1 = Q_stricmp(tmp_i2,0x10f69ac);
      if (tmp_i1 == 0) {
        return (long double)(tmp_i3 + 1) / (long double)(int)GHIDRA_FIELD(cgs, 33571584, 4);
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_i2 = tmp_i2 + 0x40;
    } while (tmp_i3 < (int)GHIDRA_FIELD(cgs, 33571584, 4));
  }
  return (long double)0;
}

int CG_Debriefing_FindWinningTeamForMap(void)
{
  uint32_t tmp_u1;
  char *__nptr;
  long tmp_l2;
  int tmp_i3;
  
  tmp_u1 = CG_ConfigString(0xe);
  __nptr = (char *)Info_ValueForKey(tmp_u1,"w");
  tmp_l2 = strtol(__nptr,(char **)0x0,10);
  tmp_i3 = 0;
  if (tmp_l2 != -1) {
    tmp_l2 = strtol(__nptr,(char **)0x0,10);
    tmp_i3 = 2 - (uint)(tmp_l2 == 0);
  }
  return tmp_i3;
}

uint32_t CG_Debriefing_FindWinningTeamForPos(int param_1)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  long tmp_l3;
  int tmp_i4;
  byte tmp_b5;
  int tmp_i6;
  int tmp_i7;
  
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 4) {
    if (param_1 == 0) {
      if ((int)GHIDRA_FIELD(cgs, 33571584, 4) < 1) {
        return 0;
      }
      tmp_i4 = 0;
      tmp_i6 = 0;
      tmp_i7 = 0;
      do {
        while ((g_unk_010aabf4 >> ((byte)tmp_i4 & 0x1f) & 1U) == 0) {
          tmp_i6 = (tmp_i6 + 1) - (uint)((g_unk_010aabf0 >> ((byte)tmp_i4 & 0x1f) & 1U) == 0);
          tmp_i4 = tmp_i4 + 1;
          if (tmp_i4 == GHIDRA_FIELD(cgs, 33571584, 4)) goto LAB_0004bda3;
        }
        tmp_i4 = tmp_i4 + 1;
        tmp_i7 = tmp_i7 + 1;
      } while (tmp_i4 != GHIDRA_FIELD(cgs, 33571584, 4));
LAB_0004bda3:
      if (tmp_i7 <= tmp_i6) {
        if (tmp_i7 < tmp_i6) {
          return 2;
        }
        return 0;
      }
    }
    else {
      tmp_b5 = (char)param_1 - 1;
      if ((g_unk_010aabf4 >> (tmp_b5 & 0x1f) & 1U) == 0) {
        if ((g_unk_010aabf0 >> (tmp_b5 & 0x1f) & 1U) != 0) {
          return 2;
        }
        return 0;
      }
    }
  }
  else {
    if ((GHIDRA_FIELD(cg_gameType, 12, 4) - 5 < 4) || (GHIDRA_FIELD(cg_gameType, 12, 4) == 2)) {
      tmp_u1 = CG_ConfigString(0xe);
      tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"w");
      tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
      if (tmp_l3 == -1) {
        return 0;
      }
      tmp_i4 = strtol(tmp_pc2,(char **)0x0,10);
    }
    else {
      if (GHIDRA_FIELD(cg_gameType, 12, 4) != 3) {
        return 0;
      }
      tmp_u1 = CG_ConfigString(0xd);
      tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"d");
      tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_u1 = CG_ConfigString(0xe);
      tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"w");
      tmp_i4 = strtol(tmp_pc2,(char **)0x0,10);
      if (GHIDRA_FIELD(cgs, 33525344, 4) != 0) {
        return 0;
      }
      if (tmp_l3 != 0) {
        if (tmp_l3 != tmp_i4) {
          return 1;
        }
        return 2;
      }
    }
    if (tmp_i4 != 0) {
      return 2;
    }
  }
  return 1;
}

void CG_Debriefing2TeamSkillXP_Draw(int param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  int tmp_i6;
  char tmp_c7;
  char *tmp_pc8;
  uint8_t *local_4c;
  uint32_t local_3c;
  uint32_t *local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x4c809;
  tmp_i2 = CG_Debriefing_FindWinningTeamForPos(0);
  local_2c = 0x3f19999a;
  local_28 = 0x3f19999a;
  local_24 = 0x3f19999a;
  local_20 = 0x3f800000;
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 5) {
    return;
  }
  if (*(int *)(param_1 + 0x18) == 0) {
    if (tmp_i2 == 1) {
      tmp_c7 = '\x01';
LAB_0004caec:
      local_3c = 0x3e99999a;
      goto LAB_0004c872;
    }
    tmp_c7 = '\x02';
    if (tmp_i2 == 2) goto LAB_0004caec;
    local_3c = 0x3e4ccccd;
  }
  else {
    local_3c = 0x3e4ccccd;
    tmp_c7 = (tmp_i2 == 1) + '\x01';
LAB_0004c872:
    if (tmp_c7 == '\x01') {
      tmp_pc8 = "Axis";
      goto LAB_0004c8c4;
    }
  }
  tmp_pc8 = "Allies";
LAB_0004c8c4:
  local_30 = &local_2c;
  local_4c = cgs;
  tmp_i2 = 0;
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) + 11.0,local_3c,local_3c,
                    &local_2c,tmp_pc8,0,0,0,0x110afec);
  do {
    if (tmp_i2 == 7) {
      tmp_i4 = CG_TeamDebriefing_CalcXP_constprop_18();
    }
    else if (GHIDRA_FIELD(cg_gameType, 12, 4) == 4) {
      if ((int)GHIDRA_FIELD(cgs, 33571584, 4) < 1) {
        tmp_i4 = 0;
      }
      else {
        tmp_i4 = 0;
        tmp_i6 = 0;
        tmp_pu5 = local_4c;
        do {
          if ((GHIDRA_FIELD(cgs, 33701656, 4) + -1 == tmp_i6) || (GHIDRA_FIELD(cgs, 33701656, 4) == 0)) {
            if (tmp_i2 == 0) {
              if (tmp_c7 == '\x01') {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf33e84));
              }
              else {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf33f9c));
              }
            }
            else if (tmp_i2 == 1) {
              if (tmp_c7 == '\x01') {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf33eac));
              }
              else {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf33fc4));
              }
            }
            else if (tmp_i2 == 2) {
              if (tmp_c7 == '\x01') {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf33ed4));
              }
              else {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf33fec));
              }
            }
            else if (tmp_i2 == 3) {
              if (tmp_c7 == '\x01') {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf33efc));
              }
              else {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf34014));
              }
            }
            else if (tmp_i2 == 4) {
              if (tmp_c7 == '\x01') {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf33f24));
              }
              else {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf3403c));
              }
            }
            else if (tmp_i2 == 5) {
              if (tmp_c7 == '\x01') {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf33f4c));
              }
              else {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf34064));
              }
            }
            else if (tmp_i2 == 6) {
              if (tmp_c7 == '\x01') {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf33f74));
              }
              else {
                tmp_i4 = tmp_i4 + *(int *)(cgs + (int)(tmp_pu5 + 0xf3408c));
              }
            }
          }
          tmp_i6 = tmp_i6 + 1;
          tmp_pu5 = tmp_pu5 + 4;
        } while (tmp_i6 != GHIDRA_FIELD(cgs, 33571584, 4));
      }
    }
    else if ((GHIDRA_FIELD(cg_gameType, 12, 4) - 6 < 3) || (tmp_i4 = 0, GHIDRA_FIELD(cg_gameType, 12, 4) - 2 < 2)) {
      if (tmp_i2 == 0) {
        tmp_i4 = GHIDRA_FIELD(cgs, 33701092, 4);
        if (tmp_c7 != '\x01') {
          tmp_i4 = GHIDRA_FIELD(cgs, 33701372, 4);
        }
      }
      else if (tmp_i2 == 1) {
        tmp_i4 = GHIDRA_FIELD(cgs, 33701132, 4);
        if (tmp_c7 != '\x01') {
          tmp_i4 = GHIDRA_FIELD(cgs, 33701412, 4);
        }
      }
      else {
        tmp_i4 = 0;
        if (tmp_i2 == 2) {
          tmp_i4 = GHIDRA_FIELD(cgs, 33701172, 4);
          if (tmp_c7 != '\x01') {
            tmp_i4 = GHIDRA_FIELD(cgs, 33701452, 4);
          }
        }
        else if (tmp_i2 == 3) {
          tmp_i4 = GHIDRA_FIELD(cgs, 33701212, 4);
          if (tmp_c7 != '\x01') {
            tmp_i4 = GHIDRA_FIELD(cgs, 33701492, 4);
          }
        }
        else if (tmp_i2 == 4) {
          tmp_i4 = GHIDRA_FIELD(cgs, 33701252, 4);
          if (tmp_c7 != '\x01') {
            tmp_i4 = GHIDRA_FIELD(cgs, 33701532, 4);
          }
        }
        else if (tmp_i2 == 5) {
          tmp_i4 = GHIDRA_FIELD(cgs, 33701292, 4);
          if (tmp_c7 != '\x01') {
            tmp_i4 = GHIDRA_FIELD(cgs, 33701572, 4);
          }
        }
        else if ((tmp_i2 == 6) && (tmp_i4 = GHIDRA_FIELD(cgs, 33701332, 4), tmp_c7 != '\x01')) {
          tmp_i4 = GHIDRA_FIELD(cgs, 33701612, 4);
        }
      }
    }
    tmp_u3 = va("%i",tmp_i4);
    tmp_i4 = CG_Text_Width_Ext(tmp_u3,local_3c,0,0x110afec);
    tmp_pi1 = &skillPositions + tmp_i2;
    tmp_i2 = tmp_i2 + 1;
    CG_Text_Paint_Ext(((float)*tmp_pi1 + *(float *)(param_1 + 8) + 100.0) - (float)tmp_i4 * 0.5,
                      *(float *)(param_1 + 0xc) + 11.0,local_3c,local_3c,local_30,tmp_u3,0,0,0,
                      0x110afec);
  } while (tmp_i2 != 8);
  return;
}

uint32_t CG_Debriefing_FindOveralWinningTeam(void)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  long tmp_l3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 4) {
    if ((int)GHIDRA_FIELD(cgs, 33571584, 4) < 1) {
      return 0;
    }
    tmp_i4 = 0;
    tmp_i5 = 0;
    tmp_i6 = 0;
    do {
      while ((g_unk_010aabf4 >> ((byte)tmp_i4 & 0x1f) & 1U) == 0) {
        tmp_i5 = (tmp_i5 + 1) - (uint)((g_unk_010aabf0 >> ((byte)tmp_i4 & 0x1f) & 1U) == 0);
        tmp_i4 = tmp_i4 + 1;
        if (tmp_i4 == GHIDRA_FIELD(cgs, 33571584, 4)) goto LAB_0004d7d3;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_i6 = tmp_i6 + 1;
    } while (tmp_i4 != GHIDRA_FIELD(cgs, 33571584, 4));
LAB_0004d7d3:
    if (tmp_i6 <= tmp_i5) {
      if (tmp_i6 < tmp_i5) {
        return 2;
      }
      return 0;
    }
  }
  else {
    if ((GHIDRA_FIELD(cg_gameType, 12, 4) - 5 < 4) || (GHIDRA_FIELD(cg_gameType, 12, 4) == 2)) {
      tmp_u1 = CG_ConfigString(0xe);
      tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"w");
      tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
      if (tmp_l3 == -1) {
        return 0;
      }
      tmp_i4 = strtol(tmp_pc2,(char **)0x0,10);
    }
    else {
      if (GHIDRA_FIELD(cg_gameType, 12, 4) != 3) {
        return 0;
      }
      tmp_u1 = CG_ConfigString(0xd);
      tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"d");
      tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_u1 = CG_ConfigString(0xe);
      tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"w");
      tmp_i4 = strtol(tmp_pc2,(char **)0x0,10);
      if (GHIDRA_FIELD(cgs, 33525344, 4) != 0) {
        return 0;
      }
      if (tmp_l3 != 0) {
        if (tmp_l3 != tmp_i4) {
          return 1;
        }
        return 2;
      }
    }
    if (tmp_i4 != 0) {
      return 2;
    }
  }
  return 1;
}

int CG_Debriefing_FindWinningTeam(void)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  long tmp_l3;
  int tmp_i4;
  
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 4) {
    tmp_i4 = CG_Debriefing_FindWinningTeamForPos(GHIDRA_FIELD(cgs, 33701656, 4));
    return tmp_i4;
  }
  if ((GHIDRA_FIELD(cg_gameType, 12, 4) - 5 < 4) || (GHIDRA_FIELD(cg_gameType, 12, 4) == 2)) {
    tmp_u1 = CG_ConfigString(0xe);
    tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"w");
    tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    if (tmp_l3 != -1) {
      tmp_i4 = strtol(tmp_pc2,(char **)0x0,10);
LAB_0004d921:
      if (tmp_i4 == 0) {
        return 1;
      }
      return 2;
    }
  }
  else if (GHIDRA_FIELD(cg_gameType, 12, 4) == 3) {
    tmp_u1 = CG_ConfigString(0xd);
    tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"d");
    tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    tmp_u1 = CG_ConfigString(0xe);
    tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"w");
    tmp_i4 = strtol(tmp_pc2,(char **)0x0,10);
    if (GHIDRA_FIELD(cgs, 33525344, 4) == 0) {
      if (tmp_l3 != 0) {
        return (tmp_l3 == tmp_i4) + 1;
      }
      goto LAB_0004d921;
    }
  }
  return 0;
}

void CG_DrawFlashFade(void)
{
  byte tmp_b1;
  bool tmp_b2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  char *local_38;
  char *local_34;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x4da09;
  tmp_b2 = (int)GHIDRA_FIELD(int_ui_blackout, 12, 4) < 1;
  if ((int)(GHIDRA_FIELD(cgs, 67812, 4) + GHIDRA_FIELD(cgs, 67808, 4)) < g_unk_010906e0) {
    GHIDRA_FIELD(cgs, 67804, 4) = GHIDRA_FIELD(cgs, 67800, 4);
  }
  else if ((float)GHIDRA_FIELD(cgs, 67804, 4) != (float)GHIDRA_FIELD(cgs, 67800, 4)) {
    tmp_i4 = trap_Milliseconds();
    tmp_i6 = tmp_i4 - lastTime_12566;
    lastTime_12566 = tmp_i4;
    if (tmp_i6 - 1U < 499) {
      if ((float)GHIDRA_FIELD(cgs, 67800, 4) < (float)GHIDRA_FIELD(cgs, 67804, 4)) {
        GHIDRA_FIELD(cgs, 67804, 4) = (float)GHIDRA_FIELD(cgs, 67804, 4) - (float)tmp_i6 / (float)(int)GHIDRA_FIELD(cgs, 67812, 4);
        if ((float)GHIDRA_FIELD(cgs, 67804, 4) < (float)GHIDRA_FIELD(cgs, 67800, 4)) goto LAB_0004dc74;
      }
      else {
        GHIDRA_FIELD(cgs, 67804, 4) = (float)tmp_i6 / (float)(int)GHIDRA_FIELD(cgs, 67812, 4) + (float)GHIDRA_FIELD(cgs, 67804, 4);
        if ((float)GHIDRA_FIELD(cgs, 67800, 4) < (float)GHIDRA_FIELD(cgs, 67804, 4)) {
LAB_0004dc74:
          GHIDRA_FIELD(cgs, 67804, 4) = GHIDRA_FIELD(cgs, 67800, 4);
        }
      }
    }
  }
  if (GHIDRA_FIELD(int_ui_blackout, 12, 4) == 0) {
    if (*(int *)(g_unk_01047b00 + 0x1b4) < 1) goto LAB_0004da97;
    tmp_pu3 = (uint8_t *)va("%d",*(int *)(g_unk_01047b00 + 0x1b4));
  }
  else {
    if (*(int *)(g_unk_01047b00 + 0x1b4) != 0) goto LAB_0004da97;
    tmp_pu3 = &g_unk_0011e957;
  }
  trap_Cvar_Set("ui_blackout",tmp_pu3);
LAB_0004da97:
  if ((*(byte *)(g_unk_01047b00 + 0x96) & 0x40) != 0) {
    trap_Cvar_Set("ui_blackout",&g_unk_0011e9db);
  }
  local_40 = GHIDRA_FIELD(cgs, 67804, 4);
  if ((float)GHIDRA_FIELD(cgs, 67804, 4) <= 0.0) {
    if (tmp_b2) {
      return;
    }
  }
  else {
    local_44 = 0;
    local_48 = 0;
    local_4c = 0;
    if (tmp_b2) {
      CG_FillRectFullScreen(0,0,0x44200000,0x43f00000,&local_4c);
      return;
    }
  }
  local_44 = 0;
  local_48 = 0;
  local_4c = 0;
  local_40 = 0x3f800000;
  CG_FillRectFullScreen(0,0,0x44200000,0x43f00000,&local_4c);
  if ((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3) || (GHIDRA_FIELD(cg_draw2D, 12, 4) != 0)) {
    local_34 = "ALLIES";
    tmp_u7 = 0x5a;
    local_38 = "AXIS";
    local_2c = 0x3f800000;
    local_28 = 0x3f800000;
    local_24 = 0;
    local_20 = 0x3f800000;
    if ((*(byte *)(g_unk_01047b00 + 0x1b4) & 1) == 0) {
      tmp_b1 = *(byte *)(g_unk_01047b00 + 0x1b4);
    }
    else {
      tmp_u5 = va("The %s team is speclocked!","AXIS");
      tmp_u7 = 0x66;
      CG_DrawStringExt(8,0x5a,tmp_u5,&local_2c,1,0,10,10,0);
      tmp_b1 = *(byte *)(g_unk_01047b00 + 0x1b4);
    }
    if ((tmp_b1 & 2) != 0) {
      tmp_u5 = va("The %s team is speclocked!",local_34);
      CG_DrawStringExt(8,tmp_u7,tmp_u5,&local_2c,1,0,10,10,0);
      return;
    }
  }
  return;
}

void CG_DrawBinocReticle(void)
{
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  uint32_t uStack_c;
  
  uStack_c = 0x4ddf7;
  local_14 = 0;
  local_18 = 0;
  local_1c = 0;
  local_10 = 0x3f800000;
  if (GHIDRA_FIELD(cgs, 68080, 4) != 0) {
    CG_DrawPicFullScreen(0,0,0x44200000,0x43f00000,GHIDRA_FIELD(cgs, 68080, 4));
  }
  CG_FillRectFullScreen(0x43120000,0x436f0000,0x43ae0000,0x3f800000,&local_1c);
  CG_FillRectFullScreen(0x433c0000,0x436a0000,0x3f800000,0x41500000,&local_1c);
  CG_FillRectFullScreen(0x436a0000,0x43620000,0x3f800000,0x41e80000,&local_1c);
  CG_FillRectFullScreen(0x43890000,0x436a0000,0x3f800000,0x41500000,&local_1c);
  CG_FillRectFullScreen(0x43a00000,0x43550000,0x3f800000,0x425c0000,&local_1c);
  CG_FillRectFullScreen(0x43b40000,0x436a0000,0x3f800000,0x41500000,&local_1c);
  CG_FillRectFullScreen(0x43cb0000,0x43620000,0x3f800000,0x41e80000,&local_1c);
  CG_FillRectFullScreen(0x43e20000,0x436a0000,0x3f800000,0x41500000,&local_1c);
  return;
}

void CG_DrawAnnouncement(void)
{
  float tmp_f1;
  int tmp_i2;
  char tmp_c3;
  int tmp_i4;
  int tmp_i5;
  char *tmp_pc6;
  bool tmp_b7;
  int local_438;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x4dfb9;
  if (g_unk_01093110 != 0) {
    CG_HudPlacement(0);
    tmp_i4 = CG_FadeColor(g_unk_01093110,(int)ROUND((float)GHIDRA_FIELD(cg_centertime, 8, 4) * 1000.0));
    if (tmp_i4 != 0) {
      tmp_pc6 = &g_unk_01093124;
      trap_R_SetColor(tmp_i4);
      tmp_f1 = (float)g_unk_01093118 - (float)(g_unk_0109311c << 4) * 0.5;
      do {
        tmp_i2 = g_unk_01093114;
        local_438 = (int)ROUND(tmp_f1);
        tmp_i5 = 0;
        do {
          tmp_c3 = tmp_pc6[tmp_i5];
          if ((tmp_c3 == '\n') || (tmp_c3 == '\0')) break;
          local_41c[tmp_i5] = tmp_c3;
          tmp_i5 = tmp_i5 + 1;
        } while (tmp_i5 != 0x38);
        local_41c[tmp_i5] = '\0';
        tmp_i5 = CG_DrawStrlen(local_41c);
        CG_DrawStringExt((int)ROUND((float)(0x280 - tmp_i5 * tmp_i2) * 0.5),local_438,local_41c,tmp_i4,
                         0,1,g_unk_01092d04,(int)ROUND((float)g_unk_01092d04 * 1.5),0);
        tmp_f1 = (float)g_unk_01093114 * 1.5 + (float)local_438;
        tmp_c3 = *tmp_pc6;
        if (tmp_c3 == '\n') {
          tmp_c3 = '\n';
        }
        else {
          do {
            tmp_b7 = tmp_c3 == '\0';
            tmp_c3 = '\0';
            if (tmp_b7) break;
            tmp_pc6 = tmp_pc6 + 1;
            tmp_c3 = *tmp_pc6;
          } while (tmp_c3 != '\n');
        }
        if (tmp_c3 == '\0') {
          trap_R_SetColor(0);
          return;
        }
        tmp_pc6 = tmp_pc6 + 1;
      } while( true );
    }
    g_unk_01092d00 = 0;
  }
  return;
}

void CG_DrawObjectiveInfo(void)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  char tmp_c4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  char *tmp_pc9;
  bool tmp_b10;
  int local_458;
  int local_454;
  int local_44c;
  int local_444;
  uint32_t local_42c;
  uint32_t local_428;
  uint32_t local_424;
  float local_420;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x4e1d9;
  local_42c = 0x3e4ccccd;
  local_428 = 0x3e4ccccd;
  local_424 = 0x3f800000;
  if (g_unk_010aaed4 != 0) {
    tmp_pu5 = (uint32_t *)CG_FadeColor(g_unk_010aaed4,0xfa);
    if (tmp_pu5 != (uint32_t *)0x0) {
      CG_HudPlacement(0);
      trap_R_SetColor(tmp_pu5);
      local_444 = 0x141;
      local_44c = (0x32 - g_unk_010ab2e0) * 8;
      tmp_i6 = local_44c + -2;
      tmp_pc9 = &g_unk_010aaee0;
      local_454 = 0x13f;
      do {
        tmp_i8 = g_unk_010aaed8;
        tmp_i7 = 0;
        do {
          tmp_c4 = tmp_pc9[tmp_i7];
          if ((tmp_c4 == '\n') || (tmp_c4 == '\0')) break;
          local_41c[tmp_i7] = tmp_c4;
          tmp_i7 = tmp_i7 + 1;
        } while (tmp_i7 != 0x38);
        local_41c[tmp_i7] = '\0';
        tmp_i7 = CG_DrawStrlen(local_41c);
        tmp_i8 = (tmp_i7 * tmp_i8 + 10) / 2;
        tmp_i7 = 0x140 - tmp_i8;
        if (tmp_i7 < local_454) {
          local_444 = tmp_i8 + 0x140;
          local_454 = tmp_i7;
        }
        tmp_f1 = (float)g_unk_010aaed8;
        local_44c = (int)ROUND((float)local_44c + tmp_f1 * 1.5);
        tmp_c4 = *tmp_pc9;
        if (tmp_c4 == '\n') {
          tmp_c4 = '\n';
        }
        else {
          do {
            tmp_b10 = tmp_c4 == '\0';
            tmp_c4 = '\0';
            if (tmp_b10) break;
            tmp_pc9 = tmp_pc9 + 1;
            tmp_c4 = *tmp_pc9;
          } while (tmp_c4 != '\n');
        }
        if (tmp_c4 == '\0') {
          local_42c = *tmp_pu5;
          local_428 = tmp_pu5[1];
          local_424 = tmp_pu5[2];
          local_420 = (float)tmp_pu5[3] * 0.5;
          trap_R_SetColor(&local_42c);
          tmp_f1 = (float)((int)ROUND(((float)local_44c - tmp_f1 * 1.5) + 4.0) - tmp_i6);
          tmp_f2 = (float)((local_444 + 4) - local_454);
          tmp_f3 = (float)tmp_i6;
          CG_DrawPic((float)local_454,tmp_f3,tmp_f2,tmp_f1,GHIDRA_FIELD(cgs, 67864, 4));
          tmp_pc9 = &g_unk_010aaee0;
          local_42c = 0;
          local_428 = 0;
          local_424 = 0;
          CG_DrawRect((float)local_454,tmp_f3,tmp_f2,tmp_f1,0x3f800000,&local_42c);
          trap_R_SetColor(tmp_pu5);
          local_458 = (0x32 - g_unk_010ab2e0) * 8;
          do {
            tmp_i6 = g_unk_010aaed8;
            tmp_i8 = 0;
            do {
              tmp_c4 = tmp_pc9[tmp_i8];
              if ((tmp_c4 == '\n') || (tmp_c4 == '\0')) break;
              local_41c[tmp_i8] = tmp_c4;
              tmp_i8 = tmp_i8 + 1;
            } while (tmp_i8 != 0x38);
            local_41c[tmp_i8] = '\0';
            tmp_i8 = CG_DrawStrlen(local_41c);
            CG_DrawStringExt(0x140 - (tmp_i8 * tmp_i6) / 2,local_458,local_41c,tmp_pu5,0,1,g_unk_010aaed8
                             ,(int)ROUND((float)g_unk_010aaed8 * 1.5),0);
            local_458 = (int)ROUND((float)g_unk_010aaed8 * 1.5 + (float)local_458);
            tmp_c4 = *tmp_pc9;
            if (tmp_c4 == '\n') {
              tmp_c4 = '\n';
            }
            else {
              do {
                tmp_b10 = tmp_c4 == '\0';
                tmp_c4 = '\0';
                if (tmp_b10) break;
                tmp_pc9 = tmp_pc9 + 1;
                tmp_c4 = *tmp_pc9;
              } while (tmp_c4 != '\n');
            }
            if (tmp_c4 == '\0') {
              trap_R_SetColor(0);
              return;
            }
            tmp_pc9 = tmp_pc9 + 1;
          } while( true );
        }
        tmp_pc9 = tmp_pc9 + 1;
      } while( true );
    }
    g_unk_010aaed4 = 0;
  }
  return;
}

int CG_Text_Width_Ext_constprop_17(byte *param_1,int param_2,float param_3)
{
  float tmp_f1;
  byte tmp_b2;
  float tmp_f3;
  size_t tmp_s4;
  int tmp_i5;
  
  tmp_f1 = *(float *)(param_2 + 0x5000);
  if (param_1 == (byte *)0x0) {
    tmp_f3 = 0.0;
  }
  else {
    tmp_i5 = 0;
    tmp_s4 = strlen((char *)param_1);
    tmp_f3 = 0.0;
    do {
      while( true ) {
        tmp_b2 = *param_1;
        if ((tmp_b2 == 0) || ((int)tmp_s4 <= tmp_i5)) goto LAB_0004e7f0;
        if ((tmp_b2 != 0x5e) || ((param_1[1] == 0 || (param_1[1] == 0x5e)))) break;
        param_1 = param_1 + 2;
        if (param_1 == (byte *)0x0) goto LAB_0004e7f0;
      }
      param_1 = param_1 + 1;
      tmp_i5 = tmp_i5 + 1;
      tmp_f3 = (float)*(int *)(param_2 + 0x10 + (uint)tmp_b2 * 0x50) + tmp_f3;
    } while (param_1 != (byte *)0x0);
  }
LAB_0004e7f0:
  return (int)ROUND(tmp_f3 * param_3 * tmp_f1);
}

void CG_Text_Paint_Ext_constprop_18
          (uint32_t *param_1,byte *param_2,float param_3,float param_4,float param_5,float param_6
          ,int param_7,int param_8)

{
  uint32_t *tmp_pu1;
  int *tmp_pi2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  int tmp_i6;
  float tmp_f7;
  byte tmp_b8;
  uint32_t tmp_u9;
  uint32_t tmp_u10;
  float tmp_f11;
  size_t tmp_s12;
  int tmp_i13;
  uint tmp_u14;
  int local_7c;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  param_5 = *(float *)(param_8 + 0x5000) * param_5;
  param_6 = *(float *)(param_8 + 0x5000) * param_6;
  if (param_2 != (byte *)0x0) {
    trap_R_SetColor(param_1);
    local_2c = *param_1;
    local_28 = param_1[1];
    local_24 = param_1[2];
    local_20 = param_1[3];
    tmp_s12 = strlen((char *)param_2);
    local_7c = 0;
    do {
      while( true ) {
        tmp_b8 = *param_2;
        if ((tmp_b8 == 0) || ((int)tmp_s12 <= local_7c)) goto LAB_0004eae0;
        tmp_u14 = (uint)tmp_b8;
        if (tmp_b8 == 0x5e) break;
LAB_0004e8f8:
        tmp_i13 = tmp_u14 * 0x50 + param_8;
        tmp_f11 = (float)*(int *)(tmp_i13 + 4) * param_6;
        if (param_7 - 6U < 2 || param_7 == 3) {
          if (param_7 == 6) {
            tmp_f7 = 2.0;
          }
          else if (param_7 == 7) {
            tmp_f7 = 0.75;
          }
          else {
            tmp_f7 = 1.0;
          }
          g_unk_0014a3bc = local_20;
          trap_R_SetColor(&colorBlack);
          tmp_pu1 = (uint32_t *)(param_8 + 0x20 + tmp_u14 * 0x50);
          tmp_i6 = param_8 + 0x10 + tmp_u14 * 0x50;
          tmp_u10 = tmp_pu1[3];
          tmp_u3 = tmp_pu1[2];
          tmp_u4 = tmp_pu1[1];
          tmp_u5 = *tmp_pu1;
          tmp_u9 = *(uint32_t *)(tmp_i6 + 0xc);
          local_4c = (float)*(int *)(tmp_i13 + 0xc) * param_5 + param_3 + tmp_f7;
          local_48 = tmp_f7 + (param_4 - tmp_f11);
          local_44 = param_5 * (float)*(int *)(tmp_i6 + 4);
          local_40 = (float)*(int *)(tmp_i6 + 8) * param_6;
          CG_AdjustFrom640(&local_4c,&local_48,&local_44,&local_40);
          trap_R_DrawStretchPic(local_4c,local_48,local_44,local_40,tmp_u9,tmp_u5,tmp_u4,tmp_u3,tmp_u10);
          g_unk_0014a3bc = 0x3f800000;
          trap_R_SetColor(&local_2c);
        }
        local_38 = param_4 - tmp_f11;
        tmp_pu1 = (uint32_t *)(param_8 + 0x20 + tmp_u14 * 0x50);
        tmp_u3 = tmp_pu1[2];
        tmp_pi2 = (int *)(param_8 + 0x10 + tmp_u14 * 0x50);
        tmp_u9 = tmp_pu1[3];
        tmp_u4 = tmp_pu1[1];
        tmp_u5 = *tmp_pu1;
        tmp_i6 = tmp_pi2[3];
        local_3c = (float)*(int *)(tmp_i13 + 0xc) * param_5 + param_3;
        local_34 = (float)tmp_pi2[1] * param_5;
        local_30 = (float)tmp_pi2[2] * param_6;
        CG_AdjustFrom640(&local_3c,&local_38,&local_34,&local_30);
        trap_R_DrawStretchPic(local_3c,local_38,local_34,local_30,tmp_i6,tmp_u5,tmp_u4,tmp_u3,tmp_u9);
        local_7c = local_7c + 1;
        param_2 = param_2 + 1;
        param_3 = (float)*tmp_pi2 * param_5 + 0.0 + param_3;
        if (param_2 == (byte *)0x0) goto LAB_0004eae0;
      }
      tmp_b8 = param_2[1];
      if ((tmp_b8 == 0) || (tmp_b8 == 0x5e)) goto LAB_0004e8f8;
      if (tmp_b8 == 0x2a) {
        local_2c = *param_1;
        local_28 = param_1[1];
        local_24 = param_1[2];
        local_20 = param_1[3];
      }
      else {
        tmp_i13 = ((int)(char)tmp_b8 - 0x30U & 0x1f) * 0x10;
        local_2c = *(uint32_t *)(g_color_table + tmp_i13);
        local_28 = *(uint32_t *)(g_color_table + tmp_i13 + 4);
        local_24 = *(uint32_t *)(g_color_table + tmp_i13 + 8);
        local_20 = param_1[3];
      }
      trap_R_SetColor(&local_2c);
      param_2 = param_2 + 2;
    } while (param_2 != (byte *)0x0);
LAB_0004eae0:
    trap_R_SetColor(0);
  }
  return;
}

void CG_DrawCrosshair(void)
{
  float *pfVar1;
  float *pfVar2;
  float tmp_f3;
  float tmp_f4;
  byte tmp_b5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  bool tmp_b9;
  bool tmp_b10;
  byte *tmp_pb11;
  size_t tmp_s12;
  int tmp_i13;
  int tmp_i14;
  int tmp_i15;
  byte *tmp_pb16;
  float *pfVar17;
  long double tmp_l18;
  long double tmp_l19;
  long double tmp_l20;
  double tmp_d21;
  float tmp_f22;
  uint local_c0;
  int local_98;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  float local_5c [18];
  uint32_t uStack_14;
  
  uStack_14 = 0x4ecc9;
  if (g_unk_010906f4 == 0) {
    if (g_unk_01091a64 != 0) {
      CG_DrawBinocReticle();
      return;
    }
    if (((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) != 0) || (tmp_i13 = g_unk_01091814, g_unk_01047aec != 0)
       ) {
      tmp_i13 = *(int *)(g_unk_01047b00 + 0xd0);
    }
    if (tmp_i13 == 0) {
      if (*(int *)(g_unk_01047b00 + 0x158) != 3) {
        return;
      }
    }
    else if (((-1 < tmp_i13) && (tmp_i13 - 0x27U < 3)) &&
            ((*(uint *)(g_unk_01047b00 + 0x94) & 0x8020) == 0)) {
      tmp_l18 = (long double)VectorLengthSquared(g_unk_01047b00 + 0x4c);
      if ((long double)16129.0 < tmp_l18) {
        tmp_i13 = *(int *)(g_unk_01047b00 + 0xd0);
        if (tmp_i13 == 0x29) {
          CG_FinishWeaponChange(0x29,0x1f);
          tmp_i13 = *(int *)(g_unk_01047b00 + 0xd0);
        }
        if (tmp_i13 == 0x27) {
          CG_FinishWeaponChange(0x27,0x18);
          tmp_i13 = *(int *)(g_unk_01047b00 + 0xd0);
        }
        if (tmp_i13 == 0x28) {
          CG_FinishWeaponChange(0x28,0x1e);
        }
      }
      if (*(int *)(g_unk_01047b00 + 0xfc) < 1) {
        return;
      }
      local_5c[0xc] = 0.0;
      local_5c[0xd] = 0.0;
      local_5c[0xe] = 0.0;
      local_5c[0xf] = 1.0;
      if (((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) != 0) ||
         (tmp_i13 = g_unk_01091814, g_unk_01047aec != 0)) {
        tmp_i13 = *(int *)(g_unk_01047b00 + 0xd0);
      }
      if (tmp_i13 != 0x29) {
        if ((tmp_i13 != 0x27) && (tmp_i13 != 0x28)) {
          return;
        }
        pfVar1 = local_5c + 0xc;
        CG_FillRectFullScreen(0,0,0x42a00000,0x43f00000,pfVar1);
        CG_FillRectFullScreen(0x440c0000,0,0x42a00000,0x43f00000,pfVar1);
        if (GHIDRA_FIELD(cgs, 68076, 4) != 0) {
          CG_DrawPicFullScreen(0x42a00000,0,0x43f00000,0x43f00000,GHIDRA_FIELD(cgs, 68076, 4));
        }
        CG_FillRectFullScreen(0x42a80000,0x436f0000,0x43310000,0x40000000,pfVar1);
        CG_FillRectFullScreen(0x43a00000,0x43720000,0x3f800000,0x42680000,pfVar1);
        CG_FillRectFullScreen(0x439f8000,0x43960000,0x40000000,0x43320000,pfVar1);
        CG_FillRectFullScreen(0x43be0000,0x436f0000,0x43310000,0x40000000,pfVar1);
        return;
      }
      pfVar1 = local_5c + 0xc;
      CG_FillRectFullScreen(0,0,0x42a00000,0x43f00000,pfVar1);
      CG_FillRectFullScreen(0x440c0000,0,0x42a00000,0x43f00000,pfVar1);
      if (GHIDRA_FIELD(cgs, 68076, 4) != 0) {
        CG_DrawPicFullScreen(0x42a00000,0,0x43f00000,0x43f00000,GHIDRA_FIELD(cgs, 68076, 4));
      }
      CG_FillRectFullScreen(0x42a80000,0x436f0000,0x43160000,0x40400000,pfVar1);
      CG_FillRectFullScreen(0x436a0000,0x43700000,0x432d0000,0x3f800000,pfVar1);
      CG_FillRectFullScreen(0x43cb8000,0x436f0000,0x43160000,0x40400000,pfVar1);
      CG_FillRectFullScreen(0x439f8000,0x40000000,0x40400000,0x43170000,pfVar1);
      CG_FillRectFullScreen(0x43a00000,0x43190000,0x3f800000,0x42e40000,pfVar1);
      CG_FillRectFullScreen(0x43a00000,0x43710000,0x3f800000,0x42ae0000,pfVar1);
      CG_FillRectFullScreen(0x439f8000,0x43a38000,0x40400000,0x43170000,pfVar1);
      return;
    }
    if ((g_unk_01090766 & 0x10) == 0) {
      if ((g_unk_010907a0 == 0x2a) && (g_unk_010907a4 != 1)) {
        local_6c = 0x3f800000;
        local_68 = 0x3f800000;
        local_64 = 0x3f800000;
        local_60 = 0x3f000000;
        local_5c[0] = 0.0;
        local_5c[1] = 0.0;
        local_5c[2] = 0.0;
        local_5c[3] = 0.25;
        local_5c[4] = 0.77;
        local_5c[5] = 0.73;
        local_5c[6] = 0.1;
        local_5c[7] = 1.0;
        local_5c[8] = 0.77;
        local_5c[9] = 0.1;
        local_5c[10] = 0.1;
        local_5c[0xb] = 1.0;
        local_5c[0xc] = 1.0;
        local_5c[0xd] = 1.0;
        local_5c[0xe] = 1.0;
        local_5c[0xf] = 1.0;
        CG_FillRect(0x43080000,0x436c0000,0x431a0000,0x42180000,local_5c);
        CG_FillRect(0x43910000,0x43200000,0x42700000,0x43500000,local_5c);
        CG_FillRect(0x43af0000,0x436c0000,0x431a0000,0x42180000,local_5c);
        CG_FillRect(0x430c0000,0x43840000,0x43160000,0x3f800000,&local_6c);
        CG_FillRect(0x43af0000,0x43840000,0x43160000,0x3f800000,&local_6c);
        tmp_l18 = (long double)AngleNormalize360(g_unk_010907b0 - 90.0);
        tmp_f3 = (float)((long double)360.0 - tmp_l18);
        tmp_l18 = ((long double)360.0 - tmp_l18) - (long double)90.0;
        AngleNormalize360((float)tmp_l18);
        tmp_l18 = (long double)AngleNormalize360((float)tmp_l18);
        tmp_f22 = floorf((float)tmp_l18);
        tmp_i13 = 0;
        tmp_f4 = (float)((int)ROUND(tmp_f3 * 13107.2) & 0xffff) * 7.6293945e-05;
        do {
          tmp_f6 = (float)tmp_i13 * 10.0 + tmp_f4 + tmp_f4;
          if ((tmp_f6 < 150.0) || (210.0 < tmp_f6)) {
            if ((int)ROUND(ROUND((float)((int)ROUND(tmp_f22) % 0xf)) / 5.0) == tmp_i13 % 3) {
              tmp_pb11 = (byte *)va("%i");
              tmp_f7 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.15;
              if (tmp_pb11 == (byte *)0x0) {
                tmp_f8 = 0.0;
              }
              else {
                tmp_s12 = strlen((char *)tmp_pb11);
                tmp_i14 = 0;
                tmp_f8 = 0.0;
                do {
                  tmp_b5 = *tmp_pb11;
                  if ((tmp_b5 == 0) || ((int)tmp_s12 <= tmp_i14)) break;
                  if ((tmp_b5 == 0x5e) && ((tmp_pb11[1] != 0 && (tmp_pb11[1] != 0x5e)))) {
                    tmp_pb11 = tmp_pb11 + 2;
                  }
                  else {
                    tmp_pb11 = tmp_pb11 + 1;
                    tmp_i14 = tmp_i14 + 1;
                    tmp_f8 = (float)*(int *)(cgs + (uint)tmp_b5 * 0x50 + 0x11114) + tmp_f8;
                  }
                } while (tmp_pb11 != (byte *)0x0);
              }
              CG_Text_Paint_Ext_constprop_18
                        ((500.0 - tmp_f6) - (float)(int)ROUND(tmp_f8 * tmp_f7) * 0.5,0x43740000,
                         0x3e19999a,0x3e19999a,0,0x1100f64);
              CG_FillRect();
            }
            else {
              CG_FillRect(500.0 - tmp_f6,0x43800000,0x3f800000,0x41000000,&local_6c);
            }
          }
          tmp_i13 = tmp_i13 + 1;
        } while (tmp_i13 != 0x24);
        tmp_l18 = (long double)AngleNormalize360((360.0 - (g_unk_010b16a8 - 90.0)) - 45.0);
        tmp_l19 = (long double)AngleNormalize360((360.0 - (g_unk_010b16a8 - 90.0)) + 45.0);
        tmp_l18 = (long double)AngleNormalize360(tmp_f3 - (float)tmp_l18);
        pfVar1 = local_5c + 4;
        CG_FillRect((float)((long double)320.0 - (tmp_l18 / (long double)5.0) * (long double)10.0),
                    0x437c0000,0x40000000,0x41900000,pfVar1);
        tmp_l18 = (long double)AngleNormalize360((float)tmp_l19 - tmp_f3);
        CG_FillRect((float)((tmp_l18 / (long double)5.0) * (long double)10.0 + (long double)320.0),
                    0x437c0000,0x40000000,0x41900000,pfVar1);
        local_98 = 0;
        if (((g_unk_010aacfc == 0x2a) && (-2 < g_unk_010b4564)) &&
           (local_98 = (-5000 - g_unk_01090ef0) + g_unk_010906e0, local_98 < 3000)) {
          if (0 < local_98) {
            local_5c[0xb] = 1.0 - (float)local_98 / 3000.0;
          }
          AngleNormalize360(360.0 - (g_unk_010b4560 - 90.0));
          tmp_l18 = (long double)AngleSubtract(tmp_f3);
          CG_FillRect((float)((long double)320.0 - (tmp_l18 / (long double)5.0) * (long double)10.0),
                      0x437c0000,0x40000000,0x41900000,local_5c + 8);
        }
        if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
          tmp_b9 = false;
          pfVar2 = local_5c + 0xc;
          tmp_b10 = false;
          pfVar17 = (float *)&g_unk_010b4578;
          tmp_i14 = 0;
          tmp_i13 = GHIDRA_FIELD(cgs, 27400, 4);
          do {
            tmp_i15 = (-25000 - (&g_unk_010b4878)[tmp_i14]) + g_unk_010906e0;
            if (tmp_i15 < 5000) {
              tmp_f4 = *pfVar17 - g_unk_0109143c;
              tmp_f22 = pfVar17[1] - g_unk_01091440;
              if ((tmp_f22 == 0.0) && (tmp_f4 == 0.0)) {
                tmp_f4 = 450.0;
              }
              else if (tmp_f4 == 0.0) {
                if (tmp_f22 <= 0.0) {
                  tmp_f4 = 180.0;
                }
                else {
                  tmp_f4 = 360.0;
                }
              }
              else {
                tmp_d21 = atan2((double)tmp_f22,(double)tmp_f4);
                tmp_f4 = ((float)tmp_d21 * 180.0) / 3.1415927;
                if (0.0 <= tmp_f4) {
                  tmp_f4 = 360.0 - (tmp_f4 - 90.0);
                }
                else {
                  tmp_f4 = 360.0 - ((tmp_f4 + 360.0) - 90.0);
                }
              }
              if (0 < tmp_i15) {
                local_5c[0xf] = 1.0 - (float)tmp_i15 / 5000.0;
              }
              tmp_l18 = (long double)AngleNormalize360(tmp_f4);
              tmp_l18 = (long double)AngleSubtract((float)tmp_l18);
              tmp_i13 = GHIDRA_FIELD(cgs, 27400, 4);
              if (tmp_l18 < (long double)0) {
                if (!tmp_b10) {
                  trap_R_SetColor(pfVar2);
                  CG_DrawPic(0x430a0000,0x43848000,0x41000000,0x41000000,GHIDRA_FIELD(cgs, 69800, 4));
                  trap_R_SetColor(0);
                  tmp_b10 = true;
                  tmp_i13 = GHIDRA_FIELD(cgs, 27400, 4);
                }
              }
              else if (tmp_l18 <= (long double)90.0) {
                tmp_l18 = (long double)AngleSubtract(tmp_f3);
                trap_R_SetColor(pfVar2);
                CG_DrawPic((320.0 - ((float)tmp_l18 / 5.0) * 10.0) - 8.0,0x43800000,0x41800000,
                           0x41800000,GHIDRA_FIELD(cgs, 69796, 4));
                trap_R_SetColor(0);
                tmp_i13 = GHIDRA_FIELD(cgs, 27400, 4);
              }
              else if (!tmp_b9) {
                trap_R_SetColor(pfVar2);
                CG_DrawPic(0x43f70000,0x43848000,0xc1000000,0x41000000,GHIDRA_FIELD(cgs, 69800, 4));
                trap_R_SetColor(0);
                tmp_b9 = true;
                tmp_i13 = GHIDRA_FIELD(cgs, 27400, 4);
              }
            }
            tmp_i14 = tmp_i14 + 1;
            pfVar17 = pfVar17 + 3;
          } while (tmp_i14 < tmp_i13);
        }
        CG_FillRect(0x43938000,0x43240000,0x3f800000,0x43480000,&local_6c);
        CG_FillRect(0x43ac8000,0x43240000,0x3f800000,0x43480000,&local_6c);
        tmp_l18 = (long double)AngleNormalize180(360.0 - (g_unk_010907ac - 60.0));
        tmp_f3 = (float)tmp_l18;
        local_c0 = 0;
        do {
          tmp_f4 = (float)(int)local_c0 * 10.0 +
                  (float)((int)ROUND((long double)26214.4 * tmp_l18) & 0xffff) * 3.8146973e-05 * 4.0;
          if ((int)ROUND(ROUND((float)((int)ROUND((long double)10.0 * ((long double)25.0 + tmp_l18)) %
                                      100)) / 25.0) == (local_c0 & 3)) {
            tmp_pb11 = (byte *)va("%i");
            tmp_f4 = tmp_f4 + 164.0;
            tmp_f22 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.15;
            if (tmp_pb11 == (byte *)0x0) {
              tmp_f6 = (float)(int)ROUND(tmp_f22 * 0.0) * 0.5;
              tmp_f22 = tmp_f6;
            }
            else {
              tmp_i13 = 0;
              tmp_s12 = strlen((char *)tmp_pb11);
              tmp_f7 = 0.0;
              tmp_pb16 = tmp_pb11;
              do {
                tmp_b5 = *tmp_pb16;
                if ((tmp_b5 == 0) || ((int)tmp_s12 <= tmp_i13)) break;
                if ((tmp_b5 == 0x5e) && ((tmp_pb16[1] != 0 && (tmp_pb16[1] != 0x5e)))) {
                  tmp_pb16 = tmp_pb16 + 2;
                }
                else {
                  tmp_f6 = (float)*(int *)(cgs + (uint)tmp_b5 * 0x50 + 0x11104);
                  if ((float)*(int *)(cgs + (uint)tmp_b5 * 0x50 + 0x11104) <= tmp_f7) {
                    tmp_f6 = tmp_f7;
                  }
                  tmp_f7 = tmp_f6;
                  tmp_pb16 = tmp_pb16 + 1;
                  tmp_i13 = tmp_i13 + 1;
                }
              } while (tmp_pb16 != (byte *)0x0);
              tmp_i13 = 0;
              tmp_f6 = 0.0;
              do {
                tmp_b5 = *tmp_pb11;
                if ((tmp_b5 == 0) || ((int)tmp_s12 <= tmp_i13)) break;
                if ((tmp_b5 == 0x5e) && ((tmp_pb11[1] != 0 && (tmp_pb11[1] != 0x5e)))) {
                  tmp_pb11 = tmp_pb11 + 2;
                }
                else {
                  tmp_pb11 = tmp_pb11 + 1;
                  tmp_i13 = tmp_i13 + 1;
                  tmp_f6 = (float)*(int *)(cgs + (uint)tmp_b5 * 0x50 + 0x11114) + tmp_f6;
                }
              } while (tmp_pb11 != (byte *)0x0);
              tmp_f6 = (float)(int)ROUND(tmp_f6 * tmp_f22) * 0.5;
              tmp_f22 = (float)(int)ROUND(tmp_f7 * tmp_f22) * 0.5;
            }
            CG_Text_Paint_Ext_constprop_18
                      (320.0 - tmp_f6,tmp_f22 + tmp_f4,0x3e19999a,0x3e19999a,0,0x1100f64);
            CG_FillRect(0x43940000,tmp_f4,0x41400000,0x3f800000,&local_6c);
            CG_FillRect(0x43a68000);
          }
          else {
            CG_FillRect(0x43940000,tmp_f4 + 164.0,0x41000000,0x3f800000,&local_6c);
            CG_FillRect(0x43a88000);
          }
          local_c0 = local_c0 + 1;
        } while (local_c0 != 0x14);
        tmp_l19 = (long double)AngleNormalize180(360.0 - (g_unk_010b16a4 - 60.0));
        tmp_l18 = (long double)AngleNormalize180(360.0 - (g_unk_010b16a4 - 60.0));
        tmp_l20 = (tmp_l18 + (long double)30.0) - (long double)tmp_f3;
        tmp_l18 = (long double)0;
        if ((long double)0 <= tmp_l20) {
          tmp_l18 = tmp_l20;
        }
        tmp_l18 = (long double)AngleNormalize360((float)tmp_l18);
        tmp_l18 = (tmp_l18 / (long double)2.5) * (long double)10.0;
        if (tmp_l18 < (long double)100.0) {
          tmp_l18 = (long double)264.0 - tmp_l18;
          CG_FillRect(0x43928000,(float)tmp_l18,0x40c00000,0x40000000,pfVar1);
          CG_FillRect(0x43ab0000,(float)tmp_l18,0x40c00000,0x40000000,pfVar1);
        }
        tmp_f4 = tmp_f3 - (float)(tmp_l19 - (long double)20.0);
        tmp_f22 = 0.0;
        if (0.0 <= tmp_f4) {
          tmp_f22 = tmp_f4;
        }
        tmp_l18 = (long double)AngleNormalize360(tmp_f22);
        tmp_l18 = (tmp_l18 / (long double)2.5) * (long double)10.0;
        if (tmp_l18 < (long double)100.0) {
          tmp_l18 = tmp_l18 + (long double)264.0;
          CG_FillRect(0x43928000,(float)tmp_l18,0x40c00000,0x40000000,pfVar1);
          CG_FillRect(0x43ab0000,(float)tmp_l18,0x40c00000,0x40000000,pfVar1);
        }
        if (((g_unk_010aacfc == 0x2a) && (-2 < g_unk_010b4564)) && (local_98 < 3000)) {
          tmp_l18 = (long double)AngleNormalize180(360.0 - (g_unk_010b455c - 60.0));
          if (tmp_l18 <= (long double)tmp_f3) {
            tmp_l19 = (long double)0;
            if ((long double)0 <= (long double)tmp_f3 - tmp_l18) {
              tmp_l19 = (long double)tmp_f3 - tmp_l18;
            }
            tmp_l18 = (long double)AngleNormalize360((float)tmp_l19);
            tmp_l18 = (tmp_l18 / (long double)2.5) * (long double)10.0;
            if ((long double)100.0 <= tmp_l18) {
              return;
            }
            tmp_l18 = tmp_l18 + (long double)264.0;
          }
          else {
            tmp_l18 = tmp_l18 - (long double)tmp_f3;
            tmp_l19 = (long double)0;
            if ((long double)0 <= tmp_l18) {
              tmp_l19 = tmp_l18;
            }
            tmp_l18 = (long double)AngleNormalize360((float)tmp_l19);
            tmp_l18 = (tmp_l18 / (long double)2.5) * (long double)10.0;
            if ((long double)100.0 <= tmp_l18) {
              return;
            }
            tmp_l18 = (long double)264.0 - tmp_l18;
          }
          CG_FillRect(0x43928000,(float)tmp_l18,0x40c00000,0x40000000,local_5c + 8);
          CG_FillRect(0x43ab0000,(float)tmp_l18,0x40c00000,0x40000000,local_5c + 8);
        }
      }
      else if ((-1 < (int)GHIDRA_FIELD(cg_drawCrosshair, 12, 4)) && (1 < *(int *)(g_unk_01047b00 + 0x454) - 0x17U))
      {
        if (GHIDRA_FIELD(r_dynamicTextures, 12, 4) != 0) {
          if (texid_12391 == 0) {
            texid_12391 = trap_R_GetTextureId("textures/effects/envmap_slate.tga");
          }
          else {
            trap_R_RenderToTexture(texid_12391,0x1c3,0x126,0x100,0x100);
          }
        }
        if (GHIDRA_FIELD(cg_crosshairHealth, 12, 4) == 0) {
          trap_R_SetColor(&g_unk_010b14c8);
        }
        else {
          CG_ColorForHealth(local_5c + 0xc);
          trap_R_SetColor(local_5c + 0xc);
        }
        CG_HudPlacement(0);
        if (GHIDRA_FIELD(cg_crosshairPulse, 12, 4) == 0) {
          local_5c[0] = 1.0;
        }
        else {
          tmp_f3 = (float)*(int *)(g_unk_01047b00 + 0x4b8) / 255.0;
          local_5c[0] = tmp_f3 + tmp_f3 + 1.0;
        }
        local_5c[0] = local_5c[0] * (float)GHIDRA_FIELD(cg_crosshairSize, 8, 4);
        local_5c[8] = (float)(int)GHIDRA_FIELD(cg_crosshairX, 12, 4);
        local_5c[0xc] = (float)(int)GHIDRA_FIELD(cg_crosshairY, 12, 4);
        local_5c[4] = local_5c[0];
        CG_AdjustFrom640(local_5c + 8,local_5c + 0xc,local_5c,local_5c + 4);
        local_5c[8] = local_5c[8] - (float)GHIDRA_FIELD(cgs, 27372, 4);
        trap_R_DrawStretchPic
                  (((float)*(int *)(g_unk_010afbcc + 8) - local_5c[0]) * 0.5 + local_5c[8],
                   ((float)*(int *)(g_unk_010afbcc + 0xc) - local_5c[4]) * 0.5 + local_5c[0xc],
                   local_5c[0],local_5c[4],0,0,0x3f800000,0x3f800000,
                   *(uint32_t *)
                    (cgs + (int)(&WORD_000109a8 + ((int)GHIDRA_FIELD(cg_drawCrosshair, 12, 4) % 0x10) * 2)));
        if ((&g_unk_010ab2f4)[(int)GHIDRA_FIELD(cg_drawCrosshair, 12, 4) % 0x10] != 0) {
          local_5c[0] = (float)GHIDRA_FIELD(cg_crosshairSize, 8, 4);
          local_5c[8] = (float)(int)GHIDRA_FIELD(cg_crosshairX, 12, 4);
          local_5c[0xc] = (float)(int)GHIDRA_FIELD(cg_crosshairY, 12, 4);
          local_5c[4] = local_5c[0];
          CG_AdjustFrom640(local_5c + 8,local_5c + 0xc,local_5c,local_5c + 4);
          local_5c[8] = local_5c[8] - (float)GHIDRA_FIELD(cgs, 27372, 4);
          if (GHIDRA_FIELD(cg_crosshairHealth, 12, 4) == 0) {
            trap_R_SetColor(&g_unk_010b14d8);
          }
          trap_R_DrawStretchPic
                    (((float)*(int *)(g_unk_010afbcc + 8) - local_5c[0]) * 0.5 + local_5c[8],
                     ((float)*(int *)(g_unk_010afbcc + 0xc) - local_5c[4]) * 0.5 + local_5c[0xc],
                     local_5c[0],local_5c[4],0,0,0x3f800000,0x3f800000,
                     (&g_unk_010ab2f4)[(int)GHIDRA_FIELD(cg_drawCrosshair, 12, 4) % 0x10]);
        }
      }
    }
  }
  return;
}

void CG_DrawBannerPrint(void)
{
  byte tmp_b1;
  char tmp_c2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  char tmp_c7;
  int tmp_i8;
  uint tmp_u9;
  uint tmp_u10;
  byte *tmp_pb11;
  char *tmp_pc12;
  uint *tmp_pu13;
  uint *tmp_pu14;
  uint *tmp_pu15;
  bool tmp_b16;
  char local_449;
  int local_448;
  uint local_41c [258];
  uint32_t uStack_14;
  
  uStack_14 = 0x50729;
  if ((GHIDRA_FIELD(cg_drawBanners, 12, 4) != 0) && (g_unk_010eeccc != 0)) {
    tmp_i8 = CG_FadeColor(g_unk_010eeccc,10000);
    if (tmp_i8 != 0) {
      CG_HudPlacement(0);
      trap_R_SetColor(tmp_i8);
      tmp_b16 = false;
      tmp_pb11 = &g_unk_0010dbdb;
      tmp_f3 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.2;
      tmp_f5 = 0.0;
      do {
        tmp_b1 = *tmp_pb11;
        if ((tmp_b1 == 0) || (tmp_b16)) break;
        if ((tmp_b1 == 0x5e) && ((tmp_pb11[1] != 0 && (tmp_pb11[1] != 0x5e)))) {
          tmp_pb11 = tmp_pb11 + 2;
          tmp_b16 = false;
        }
        else {
          tmp_b16 = true;
          tmp_f4 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11104);
          if ((float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11104) <= tmp_f5) {
            tmp_f4 = tmp_f5;
          }
          tmp_f5 = tmp_f4;
          tmp_pb11 = tmp_pb11 + 1;
        }
      } while (tmp_pb11 != (byte *)0x0);
      local_448 = 0;
      tmp_pu15 = (uint *)&g_unk_010eecd0;
      tmp_c7 = '7';
      do {
        tmp_pc12 = (char *)0x0;
        tmp_pu14 = (uint *)&g_unk_010eecd0;
        local_449 = tmp_c7;
        while( true ) {
          do {
            tmp_pu13 = tmp_pu14;
            tmp_u9 = *tmp_pu13 + 0xfefefeff & ~*tmp_pu13;
            tmp_u10 = tmp_u9 & 0x80808080;
            tmp_pu14 = tmp_pu13 + 1;
          } while (tmp_u10 == 0);
          if ((tmp_u9 & 0x8080) == 0) {
            tmp_pu14 = (uint *)((int)tmp_pu13 + 6);
            tmp_u10 = tmp_u10 >> 0x10;
          }
          if ((((char *)((int)tmp_pu14 + (-0x10eecd3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10))) <=
                tmp_pc12) || (tmp_b1 = *(byte *)((int)tmp_pu15 + (int)tmp_pc12), tmp_b1 == 10)) ||
             (tmp_b1 == 0)) break;
          if (((tmp_b1 == 0x5e) &&
              (tmp_c2 = *(char *)((int)tmp_pu15 + (int)(tmp_pc12 + 1)), tmp_c2 != '\0')) &&
             (tmp_c2 != '^')) {
            local_449 = tmp_c2;
          }
          *(byte *)((int)local_41c + (int)tmp_pc12) = tmp_b1;
          tmp_pc12 = tmp_pc12 + 1;
          tmp_pu14 = (uint *)&g_unk_010eecd0;
        }
        tmp_f4 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.2;
        *(char *)((int)local_41c + (int)tmp_pc12) = '\0';
        tmp_pu14 = local_41c;
        do {
          tmp_pu13 = tmp_pu14;
          tmp_u9 = *tmp_pu13 + 0xfefefeff & ~*tmp_pu13;
          tmp_u10 = tmp_u9 & 0x80808080;
          tmp_pu14 = tmp_pu13 + 1;
        } while (tmp_u10 == 0);
        if ((tmp_u9 & 0x8080) == 0) {
          tmp_pu14 = (uint *)((int)tmp_pu13 + 6);
          tmp_u10 = tmp_u10 >> 0x10;
        }
        tmp_i8 = 0;
        tmp_f6 = 0.0;
        tmp_pu13 = local_41c;
        do {
          while( true ) {
            tmp_b1 = (byte)*tmp_pu13;
            if ((tmp_b1 == 0) ||
               ((int)((int)tmp_pu14 +
                     ((-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)) - (int)local_41c)) <= tmp_i8))
            goto LAB_00050970;
            if ((tmp_b1 != 0x5e) ||
               ((*(byte *)((int)tmp_pu13 + 1) == 0 || (*(byte *)((int)tmp_pu13 + 1) == 0x5e)))) break;
            tmp_pu13 = (uint *)((int)tmp_pu13 + 2);
            if (tmp_pu13 == (uint *)0x0) goto LAB_00050970;
          }
          tmp_pu13 = (uint *)((int)tmp_pu13 + 1);
          tmp_i8 = tmp_i8 + 1;
          tmp_f6 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f6;
        } while (tmp_pu13 != (uint *)0x0);
LAB_00050970:
        local_448 = (int)ROUND((float)(int)ROUND(tmp_f5 * tmp_f3) * 1.5 + (float)local_448);
        va("^%c%s",(int)tmp_c7,local_41c);
        CG_Text_Paint_Ext_constprop_18
                  ((float)(int)ROUND((float)(0x280 - (int)ROUND(tmp_f6 * tmp_f4)) * 0.5),
                   (float)local_448,0x3e4ccccd,0x3e4ccccd,3,0x1100f64);
        tmp_c7 = (char)*tmp_pu15;
        if (tmp_c7 == '\n') {
          tmp_c7 = '\n';
        }
        else {
          do {
            tmp_b16 = tmp_c7 == '\0';
            tmp_c7 = '\0';
            if (tmp_b16) break;
            tmp_pu15 = (uint *)((int)tmp_pu15 + 1);
            tmp_c7 = *(char *)tmp_pu15;
          } while (tmp_c7 != '\n');
        }
        if (tmp_c7 == '\0') {
          trap_R_SetColor(0);
          return;
        }
        tmp_pu15 = (uint *)((int)tmp_pu15 + 1);
        tmp_c7 = local_449;
      } while( true );
    }
    g_unk_010eeccc = 0;
  }
  return;
}

void CG_DrawCenterString(void)
{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  char tmp_c4;
  int tmp_i5;
  uint tmp_u6;
  uint tmp_u7;
  uint *tmp_pu8;
  uint *tmp_pu9;
  char *tmp_pc10;
  bool tmp_b11;
  int local_434;
  uint local_41c [258];
  uint32_t uStack_14;
  
  uStack_14 = 0x50ab9;
  if (g_unk_01092d00 != 0) {
    tmp_i5 = CG_FadeColor(g_unk_01092d00,(int)ROUND((float)GHIDRA_FIELD(cg_centertime, 8, 4) * 1000.0));
    if (tmp_i5 != 0) {
      tmp_pc10 = &g_unk_01092d0c;
      CG_HudPlacement(0);
      trap_R_SetColor(tmp_i5);
      local_434 = (int)ROUND((float)g_unk_01092d08 - (float)(g_unk_0109310c << 4) * 0.5);
      do {
        tmp_i5 = 0;
        do {
          tmp_b1 = tmp_pc10[tmp_i5];
          if ((tmp_b1 == 10) || (tmp_b1 == 0)) break;
          *(byte *)((int)local_41c + tmp_i5) = tmp_b1;
          tmp_i5 = tmp_i5 + 1;
        } while (tmp_i5 != 0x38);
        *(uint8_t *)((int)local_41c + tmp_i5) = 0;
        tmp_pu9 = local_41c;
        do {
          tmp_pu8 = tmp_pu9;
          tmp_u6 = *tmp_pu8 + 0xfefefeff & ~*tmp_pu8;
          tmp_u7 = tmp_u6 & 0x80808080;
          tmp_pu9 = tmp_pu8 + 1;
        } while (tmp_u7 == 0);
        if ((tmp_u6 & 0x8080) == 0) {
          tmp_pu9 = (uint *)((int)tmp_pu8 + 6);
          tmp_u7 = tmp_u7 >> 0x10;
        }
        tmp_i5 = 0;
        tmp_f2 = 0.0;
        tmp_pu8 = local_41c;
        do {
          while( true ) {
            tmp_b1 = (byte)*tmp_pu8;
            if ((tmp_b1 == 0) ||
               ((int)((int)tmp_pu9 + ((-3 - (uint)CARRY1((byte)tmp_u7,(byte)tmp_u7)) - (int)local_41c))
                <= tmp_i5)) goto LAB_00050c7a;
            if ((tmp_b1 != 0x5e) ||
               ((*(byte *)((int)tmp_pu8 + 1) == 0 || (*(byte *)((int)tmp_pu8 + 1) == 0x5e)))) break;
            tmp_pu8 = (uint *)((int)tmp_pu8 + 2);
            if (tmp_pu8 == (uint *)0x0) goto LAB_00050c7a;
          }
          tmp_pu8 = (uint *)((int)tmp_pu8 + 1);
          tmp_i5 = tmp_i5 + 1;
          tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x1b19c) + tmp_f2;
        } while (tmp_pu8 != (uint *)0x0);
LAB_00050c7a:
        CG_Text_Paint_Ext_constprop_18
                  (320.0 - (float)(int)ROUND((float)GHIDRA_FIELD(cgs, 131468, 4) * 0.25 * tmp_f2) * 0.5,
                   (float)local_434,0x3e800000,0x3e800000,7,0x110afec);
        tmp_pu9 = local_41c;
        do {
          tmp_pu8 = tmp_pu9;
          tmp_u6 = *tmp_pu8 + 0xfefefeff & ~*tmp_pu8;
          tmp_u7 = tmp_u6 & 0x80808080;
          tmp_pu9 = tmp_pu8 + 1;
        } while (tmp_u7 == 0);
        if ((tmp_u6 & 0x8080) == 0) {
          tmp_pu9 = (uint *)((int)tmp_pu8 + 6);
          tmp_u7 = tmp_u7 >> 0x10;
        }
        tmp_i5 = 0;
        tmp_f2 = 0.0;
        tmp_pu8 = local_41c;
        do {
          while( true ) {
            tmp_b1 = (byte)*tmp_pu8;
            if ((tmp_b1 == 0) ||
               ((int)((int)tmp_pu9 + ((-3 - (uint)CARRY1((byte)tmp_u7,(byte)tmp_u7)) - (int)local_41c))
                <= tmp_i5)) goto LAB_00050d70;
            if ((tmp_b1 != 0x5e) ||
               ((*(byte *)((int)tmp_pu8 + 1) == 0 || (*(byte *)((int)tmp_pu8 + 1) == 0x5e)))) break;
            tmp_pu8 = (uint *)((int)tmp_pu8 + 2);
            if (tmp_pu8 == (uint *)0x0) goto LAB_00050d70;
          }
          tmp_f3 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x1b18c);
          if ((float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x1b18c) <= tmp_f2) {
            tmp_f3 = tmp_f2;
          }
          tmp_f2 = tmp_f3;
          tmp_pu8 = (uint *)((int)tmp_pu8 + 1);
          tmp_i5 = tmp_i5 + 1;
        } while (tmp_pu8 != (uint *)0x0);
LAB_00050d70:
        local_434 = local_434 + 2 + (int)ROUND(tmp_f2 * (float)GHIDRA_FIELD(cgs, 131468, 4) * 0.25);
        tmp_c4 = *tmp_pc10;
        if (tmp_c4 == '\n') {
          tmp_c4 = '\n';
        }
        else {
          do {
            tmp_b11 = tmp_c4 == '\0';
            tmp_c4 = '\0';
            if (tmp_b11) break;
            tmp_pc10 = tmp_pc10 + 1;
            tmp_c4 = *tmp_pc10;
          } while (tmp_c4 != '\n');
        }
        if (tmp_c4 == '\0') {
          trap_R_SetColor(0);
          return;
        }
        tmp_pc10 = tmp_pc10 + 1;
      } while( true );
    }
    g_unk_01092d00 = 0;
  }
  return;
}

void CG_DrawDemoRecording_part_3(void)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  byte tmp_b5;
  byte tmp_b6;
  uint32_t tmp_u7;
  float tmp_f8;
  float tmp_f9;
  int tmp_i10;
  uint tmp_u11;
  uint tmp_u12;
  int tmp_i13;
  uint *tmp_pu14;
  uint tmp_u15;
  uint *tmp_pu16;
  int tmp_i17;
  uint *tmp_pu18;
  float local_560;
  float local_53c;
  float local_538;
  float local_534;
  float local_530;
  uint32_t local_52c;
  uint32_t local_528;
  uint32_t local_524;
  uint32_t local_520;
  char local_51c [128];
  char local_49c [128];
  uint local_41c [258];
  uint32_t uStack_14;
  
  uStack_14 = 0x50df9;
  CG_HudPlacement(1);
  if (GHIDRA_FIELD(cl_demorecording, 12, 4) == 0) {
    strncpy(local_51c,"",0x80);
  }
  else {
    tmp_i10 = GHIDRA_FIELD(cl_demooffset, 12, 4) + 0x3ff;
    if (-1 < (int)GHIDRA_FIELD(cl_demooffset, 12, 4)) {
      tmp_i10 = GHIDRA_FIELD(cl_demooffset, 12, 4);
    }
    Com_sprintf(local_51c,0x80," demo %s: %ik ",0x3132590,tmp_i10 >> 10);
  }
  if (GHIDRA_FIELD(cl_waverecording, 12, 4) == 0) {
    strncpy(local_49c,"",0x80);
  }
  else {
    tmp_i10 = GHIDRA_FIELD(cl_waveoffset, 12, 4) + 0x3ff;
    if (-1 < (int)GHIDRA_FIELD(cl_waveoffset, 12, 4)) {
      tmp_i10 = GHIDRA_FIELD(cl_waveoffset, 12, 4);
    }
    Com_sprintf(local_49c,0x80," audio %s: %ik ",0x101f530,tmp_i10 >> 10);
  }
  tmp_pu18 = local_41c;
  Com_sprintf(tmp_pu18,0x400,"RECORDING%s%s",local_51c,local_49c);
  tmp_f8 = (float)(int)GHIDRA_FIELD(cg_recording_statusline, 12, 4);
  tmp_f9 = (float)GHIDRA_FIELD(cgs, 131468, 4) * 0.2;
  trap_R_SetColor(&colorWhite);
  local_52c = colorWhite;
  local_528 = g_unk_0014a334;
  local_524 = g_unk_0014a338;
  local_520 = g_unk_0014a33c;
  tmp_pu16 = tmp_pu18;
  do {
    tmp_pu14 = tmp_pu16;
    tmp_u11 = *tmp_pu14 + 0xfefefeff & ~*tmp_pu14;
    tmp_u12 = tmp_u11 & 0x80808080;
    tmp_pu16 = tmp_pu14 + 1;
  } while (tmp_u12 == 0);
  local_560 = 5.0;
  tmp_u15 = tmp_u12 >> 0x10;
  tmp_pu16 = (uint *)((int)tmp_pu14 + 6);
  if ((tmp_u11 & 0x8080) != 0) {
    tmp_pu16 = tmp_pu14 + 1;
    tmp_u15 = tmp_u12;
  }
  tmp_i10 = (-3 - (uint)CARRY1((byte)tmp_u15,(byte)tmp_u15)) - (int)tmp_pu18;
  tmp_i17 = 0;
  do {
    while( true ) {
      tmp_b5 = (byte)*tmp_pu18;
      if ((tmp_b5 == 0) || ((int)((int)tmp_pu16 + tmp_i10) <= tmp_i17)) goto LAB_00051150;
      if (tmp_b5 == 0x5e) break;
LAB_00050fa0:
      tmp_pu18 = (uint *)((int)tmp_pu18 + 1);
      tmp_i13 = (uint)tmp_b5 * 0x50;
      tmp_u1 = *(uint32_t *)(cgs + tmp_i13 + 0x1b1b4);
      tmp_u7 = *(uint32_t *)(cgs + tmp_i13 + 0x1b1b8);
      tmp_u2 = *(uint32_t *)(cgs + tmp_i13 + 0x1b1b0);
      tmp_u3 = *(uint32_t *)(cgs + tmp_i13 + 0x1b1ac);
      tmp_u4 = *(uint32_t *)(cgs + tmp_i13 + 0x1b1a8);
      local_538 = tmp_f8 - (float)*(int *)(cgs + tmp_i13 + 0x1b190) * tmp_f9;
      local_53c = (float)*(int *)(cgs + tmp_i13 + 0x1b198) * tmp_f9 + local_560;
      local_534 = (float)*(int *)(cgs + tmp_i13 + 0x1b1a0) * tmp_f9;
      local_530 = tmp_f9 * (float)*(int *)(cgs + tmp_i13 + 0x1b1a4);
      CG_AdjustFrom640(&local_53c,&local_538,&local_534,&local_530);
      trap_R_DrawStretchPic(local_53c,local_538,local_534,local_530,tmp_u4,tmp_u3,tmp_u2,tmp_u1,tmp_u7);
      tmp_i17 = tmp_i17 + 1;
      local_560 = (float)*(int *)(cgs + tmp_i13 + 0x1b19c) * tmp_f9 + 0.0 + local_560;
      if (tmp_pu18 == (uint *)0x0) goto LAB_00051150;
    }
    tmp_b6 = *(byte *)((int)tmp_pu18 + 1);
    if ((tmp_b6 == 0) || (tmp_b6 == 0x5e)) goto LAB_00050fa0;
    if (tmp_b6 == 0x2a) {
      local_52c = colorWhite;
      local_528 = g_unk_0014a334;
      local_524 = g_unk_0014a338;
    }
    else {
      tmp_i13 = ((int)(char)tmp_b6 - 0x30U & 0x1f) * 0x10;
      local_52c = *(uint32_t *)(g_color_table + tmp_i13);
      local_528 = *(uint32_t *)(g_color_table + tmp_i13 + 4);
      local_524 = *(uint32_t *)(g_color_table + tmp_i13 + 8);
    }
    local_520 = g_unk_0014a33c;
    tmp_pu18 = (uint *)((int)tmp_pu18 + 2);
    trap_R_SetColor(&local_52c);
  } while (tmp_pu18 != (uint *)0x0);
LAB_00051150:
  trap_R_SetColor(0);
  return;
}

void CG_Text_Paint_Centred_Ext_constprop_15
          (uint32_t *param_1,byte *param_2,float param_3,float param_4,float param_5,float param_6
          ,int param_7)

{
  uint32_t *tmp_pu1;
  int *tmp_pi2;
  float tmp_f3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  byte tmp_b7;
  byte tmp_b8;
  uint32_t tmp_u9;
  float tmp_f10;
  size_t tmp_s11;
  int tmp_i12;
  byte *tmp_pb13;
  int tmp_i14;
  int tmp_i15;
  float local_84;
  int local_7c;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  tmp_f3 = *(float *)(param_7 + 0x5000);
  param_5 = tmp_f3 * param_5;
  if (param_2 != (byte *)0x0) {
    tmp_i14 = 0;
    tmp_s11 = strlen((char *)param_2);
    tmp_f10 = 0.0;
    tmp_pb13 = param_2;
    do {
      while( true ) {
        tmp_b7 = *tmp_pb13;
        if ((tmp_b7 == 0) || ((int)tmp_s11 <= tmp_i14)) goto LAB_000512c2;
        if ((tmp_b7 != 0x5e) || ((tmp_pb13[1] == 0 || (tmp_pb13[1] == 0x5e)))) break;
        tmp_pb13 = tmp_pb13 + 2;
        if (tmp_pb13 == (byte *)0x0) goto LAB_000512c2;
      }
      tmp_pb13 = tmp_pb13 + 1;
      tmp_i14 = tmp_i14 + 1;
      tmp_f10 = (float)*(int *)(param_7 + 0x10 + (uint)tmp_b7 * 0x50) + tmp_f10;
    } while (tmp_pb13 != (byte *)0x0);
LAB_000512c2:
    local_84 = param_3 - (float)(int)ROUND(tmp_f10 * param_5) * 0.5;
    tmp_f3 = tmp_f3 * param_6;
    trap_R_SetColor(param_1);
    local_2c = *param_1;
    local_28 = param_1[1];
    local_24 = param_1[2];
    local_20 = param_1[3];
    tmp_s11 = strlen((char *)param_2);
    local_7c = 0;
    do {
      while( true ) {
        tmp_b7 = *param_2;
        if ((tmp_b7 == 0) || ((int)tmp_s11 <= local_7c)) goto LAB_00051650;
        if (tmp_b7 == 0x5e) break;
LAB_00051360:
        param_2 = param_2 + 1;
        tmp_i15 = (uint)tmp_b7 * 0x50;
        tmp_i12 = param_7 + tmp_i15;
        tmp_i14 = *(int *)(tmp_i12 + 4);
        g_unk_0014a3bc = local_20;
        trap_R_SetColor(&colorBlack);
        tmp_pu1 = (uint32_t *)(param_7 + 0x20 + tmp_i15);
        tmp_u4 = tmp_pu1[2];
        tmp_pi2 = (int *)(param_7 + 0x10 + tmp_i15);
        tmp_u9 = tmp_pu1[3];
        tmp_u5 = tmp_pu1[1];
        tmp_u6 = *tmp_pu1;
        tmp_i15 = tmp_pi2[3];
        tmp_f10 = param_4 - (float)tmp_i14 * tmp_f3;
        local_4c = (float)*(int *)(tmp_i12 + 0xc) * param_5 + local_84 + 0.75;
        local_48 = tmp_f10 + 0.75;
        local_44 = param_5 * (float)tmp_pi2[1];
        local_40 = (float)tmp_pi2[2] * tmp_f3;
        CG_AdjustFrom640(&local_4c,&local_48,&local_44,&local_40);
        trap_R_DrawStretchPic(local_4c,local_48,local_44,local_40,tmp_i15,tmp_u6,tmp_u5,tmp_u4,tmp_u9);
        g_unk_0014a3bc = 0x3f800000;
        trap_R_SetColor(&local_2c);
        tmp_u9 = tmp_pu1[3];
        tmp_u4 = tmp_pu1[2];
        tmp_u5 = tmp_pu1[1];
        tmp_u6 = *tmp_pu1;
        tmp_i14 = tmp_pi2[3];
        local_3c = (float)*(int *)(tmp_i12 + 0xc) * param_5 + local_84;
        local_34 = param_5 * (float)tmp_pi2[1];
        local_30 = (float)tmp_pi2[2] * tmp_f3;
        local_38 = tmp_f10;
        CG_AdjustFrom640(&local_3c,&local_38,&local_34,&local_30);
        trap_R_DrawStretchPic(local_3c,local_38,local_34,local_30,tmp_i14,tmp_u6,tmp_u5,tmp_u4,tmp_u9);
        local_7c = local_7c + 1;
        local_84 = (float)*tmp_pi2 * param_5 + 0.0 + local_84;
        if (param_2 == (byte *)0x0) goto LAB_00051650;
      }
      tmp_b8 = param_2[1];
      if ((tmp_b8 == 0) || (tmp_b8 == 0x5e)) goto LAB_00051360;
      if (tmp_b8 == 0x2a) {
        local_2c = *param_1;
        local_28 = param_1[1];
        local_24 = param_1[2];
        local_20 = param_1[3];
      }
      else {
        tmp_i14 = ((int)(char)tmp_b8 - 0x30U & 0x1f) * 0x10;
        local_2c = *(uint32_t *)(g_color_table + tmp_i14);
        local_28 = *(uint32_t *)(g_color_table + tmp_i14 + 4);
        local_24 = *(uint32_t *)(g_color_table + tmp_i14 + 8);
        local_20 = param_1[3];
      }
      param_2 = param_2 + 2;
      trap_R_SetColor(&local_2c);
    } while (param_2 != (byte *)0x0);
LAB_00051650:
    trap_R_SetColor(0);
  }
  return;
}

void CG_DrawPlayerStatus(void)
{
  byte tmp_b1;
  float tmp_f2;
  bool tmp_b3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  uint8_t *tmp_pu8;
  int tmp_i9;
  float *pfVar10;
  int tmp_i11;
  uint tmp_u12;
  uint tmp_u13;
  uint32_t tmp_u14;
  uint8_t *tmp_pu15;
  uint *tmp_pu16;
  uint *tmp_pu17;
  uint *tmp_pu18;
  int tmp_i19;
  int tmp_i20;
  double tmp_d21;
  double tmp_d22;
  double tmp_d23;
  float tmp_f24;
  int local_ec;
  float *local_d0;
  int local_cc;
  float *local_ac;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  uint32_t local_8c;
  uint32_t local_88;
  uint32_t local_84;
  uint32_t local_80;
  float local_7c [16];
  uint local_3c [10];
  uint32_t uStack_14;
  
  uStack_14 = 0x516a9;
  CG_HudPlacement(2);
  tmp_i20 = g_unk_01047b00;
  tmp_i9 = *(int *)(g_unk_01047b00 + 0xcc);
  if (tmp_i9 == g_unk_01047ac4) {
    tmp_pu8 = &g_unk_01090ca8;
  }
  else {
    tmp_pu8 = cg_entities + tmp_i9 * 0xaf8;
  }
  tmp_i19 = *(int *)(tmp_pu8 + 0xe8);
  if (tmp_i19 == 0) {
_L855:
    goto LAB_00051724;
  }
  switch(tmp_i19) {
  case 1:
    tmp_b3 = true;
    if ((cgs[tmp_i9 * 0x1a4 + 0x959c] & 0x20) == 0) goto LAB_00051724;
    break;
  default:
    tmp_b3 = false;
    break;
  case 4:
  case 5:
  case 6:
  case 9:
  case 0xb:
  case 0x19:
  case 0x21:
  case 0x2a:
  case 0x2b:
  case 0x2f:
  case 0x31:
  case 0x33:
    tmp_b3 = true;
    break;
  case 0xc:
  case 0xf:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x30:
  case 0x32:
    goto _L855;
  }
  if ((*(uint *)(g_unk_01047b00 + 0x94) & 0x8020) != 0) goto LAB_00051724;
  tmp_i9 = BG_FindAmmoForWeapon(tmp_i19);
  tmp_i9 = *(int *)(tmp_i20 + 0x1bc + tmp_i9 * 4);
  tmp_i11 = BG_FindClipForWeapon(tmp_i19);
  local_ec = *(int *)(tmp_i20 + 700 + tmp_i11 * 4);
  if ((tmp_i19 - 0x2cU < 2) || (local_cc = -1, tmp_i19 - 0x22U < 2)) {
    tmp_u14 = BG_AkimboSidearm(tmp_i19);
    tmp_i11 = BG_FindClipForWeapon(tmp_u14);
    local_cc = *(int *)(tmp_i20 + 700 + tmp_i11 * 4);
  }
  if ((tmp_i19 == 0x33) || (tmp_i19 == 0x19)) {
    if (GHIDRA_FIELD(cgs, 33575844, 4) == 0) {
LAB_00052ee8:
      local_ec = 0;
    }
    else if (*(int *)(cgs + *(int *)(tmp_i20 + 0xcc) * 0x1a4 + 0x9494) == 1) {
      local_ec = *(int *)(GHIDRA_FIELD(cgs, 33575844, 4) + 0x8c);
    }
    else {
      local_ec = *(int *)(GHIDRA_FIELD(cgs, 33575844, 4) + 0x90);
    }
  }
  else if (tmp_i19 == 0x31) {
    if (GHIDRA_FIELD(cgs, 33575844, 4) == 0) goto LAB_00052ee8;
    if (*(int *)(cgs + *(int *)(tmp_i20 + 0xcc) * 0x1a4 + 0x9494) == 1) {
      local_ec = *(int *)(GHIDRA_FIELD(cgs, 33575844, 4) + 0x54);
    }
    else {
      local_ec = *(int *)(GHIDRA_FIELD(cgs, 33575844, 4) + 0x58);
    }
  }
  else if ((tmp_i19 == 0x2a || tmp_i19 == 0x21) || (tmp_i19 == 5)) {
    local_ec = local_ec + tmp_i9;
  }
  if (tmp_b3) {
    tmp_i9 = -1;
    if (local_cc < 0) {
LAB_00052dc0:
      if (local_ec < 0) goto LAB_00051724;
      tmp_pu16 = local_3c;
      Com_sprintf(tmp_pu16,0x20,&g_unk_0011341c,local_ec);
      tmp_f24 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.25;
      tmp_pu17 = tmp_pu16;
      do {
        tmp_pu18 = tmp_pu17;
        tmp_u12 = *tmp_pu18 + 0xfefefeff & ~*tmp_pu18;
        tmp_u13 = tmp_u12 & 0x80808080;
        tmp_pu17 = tmp_pu18 + 1;
      } while (tmp_u13 == 0);
      if ((tmp_u12 & 0x8080) == 0) {
        tmp_pu17 = (uint *)((int)tmp_pu18 + 6);
        tmp_u13 = tmp_u13 >> 0x10;
      }
      tmp_i20 = 0;
      tmp_f2 = 0.0;
      tmp_i9 = (-3 - (uint)CARRY1((byte)tmp_u13,(byte)tmp_u13)) - (int)tmp_pu16;
      do {
        tmp_b1 = (byte)*tmp_pu16;
        if ((tmp_b1 == 0) || ((int)((int)tmp_pu17 + tmp_i9) <= tmp_i20)) break;
        if ((tmp_b1 == 0x5e) &&
           ((*(byte *)((int)tmp_pu16 + 1) != 0 && (*(byte *)((int)tmp_pu16 + 1) != 0x5e)))) {
          tmp_pu16 = (uint *)((int)tmp_pu16 + 2);
        }
        else {
          tmp_pu16 = (uint *)((int)tmp_pu16 + 1);
          tmp_i20 = tmp_i20 + 1;
          tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f2;
        }
      } while (tmp_pu16 != (uint *)0x0);
    }
    else {
LAB_00052430:
      if ((cg_HUDFlags[0xc] & 0x10) != 0) {
        local_7c[0] = 590.0;
        local_7c[4] = 458.0;
        local_7c[8] = 1.0;
        local_7c[0xc] = 4.0;
        local_3c[0] = 0x3f800000;
        tmp_i20 = *(int *)(ammoTableMP + g_unk_010907a0 * 0x48 + 8);
        local_3c[1] = 0x3f800000;
        local_3c[2] = 0x3f800000;
        local_3c[3] = 0x3f800000;
        CG_AdjustFrom640(local_7c,local_7c + 4,local_7c + 8,local_7c + 0xc);
        tmp_i19 = tmp_i20 + 3;
        if (-1 < tmp_i20) {
          tmp_i19 = tmp_i20;
        }
        if (local_cc <= tmp_i19 >> 2) {
          local_3c[2] = 0;
          local_3c[1] = 0;
        }
        tmp_i11 = 0;
        tmp_pu16 = local_3c;
        if (0 < tmp_i20) {
          do {
            if (local_cc <= tmp_i11) {
              local_3c[3] = 0x3eb33333;
            }
            tmp_i11 = tmp_i11 + 1;
            trap_R_SetColor(tmp_pu16);
            trap_R_DrawStretchPic
                      (local_7c[0],local_7c[4],local_7c[8],local_7c[0xc],0,0,0,0x3f800000,
                       GHIDRA_FIELD(cgs, 67836, 4));
            trap_R_SetColor(0);
            local_7c[0] = local_7c[0] - 3.0;
          } while (tmp_i11 != tmp_i20);
        }
        local_3c[3] = 0x3f800000;
        local_3c[2] = 0x3f800000;
        local_3c[1] = 0x3f800000;
        local_3c[0] = 0x3f800000;
        local_7c[0] = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27364, 4) * 590.0;
        local_7c[4] = (float)GHIDRA_FIELD(cgs, 27368, 4) * 464.0;
        if (local_ec <= tmp_i19 >> 2) {
          local_3c[2] = 0;
          local_3c[1] = 0;
        }
        if (0 < tmp_i20) {
          tmp_i19 = 0;
          do {
            if (local_ec <= tmp_i19) {
              local_3c[3] = 0x3eb33333;
            }
            tmp_i19 = tmp_i19 + 1;
            trap_R_SetColor(tmp_pu16);
            trap_R_DrawStretchPic
                      (local_7c[0],local_7c[4],local_7c[8],local_7c[0xc],0,0,0,0x3f800000,
                       GHIDRA_FIELD(cgs, 67836, 4));
            trap_R_SetColor(0);
            local_7c[0] = local_7c[0] - 3.0;
          } while (tmp_i19 != tmp_i20);
        }
        Com_sprintf(tmp_pu16,0x20,&g_unk_0011341c,tmp_i9);
        tmp_pu17 = tmp_pu16;
        do {
          tmp_pu18 = tmp_pu17;
          tmp_u12 = *tmp_pu18 + 0xfefefeff & ~*tmp_pu18;
          tmp_u13 = tmp_u12 & 0x80808080;
          tmp_pu17 = tmp_pu18 + 1;
        } while (tmp_u13 == 0);
        if ((tmp_u12 & 0x8080) == 0) {
          tmp_pu17 = (uint *)((int)tmp_pu18 + 6);
          tmp_u13 = tmp_u13 >> 0x10;
        }
        tmp_i20 = 0;
        tmp_f2 = 0.0;
        tmp_i9 = (-3 - (uint)CARRY1((byte)tmp_u13,(byte)tmp_u13)) - (int)tmp_pu16;
        do {
          while( true ) {
            tmp_b1 = (byte)*tmp_pu16;
            if ((tmp_b1 == 0) || ((int)((int)tmp_pu17 + tmp_i9) <= tmp_i20)) goto LAB_000527b0;
            if ((tmp_b1 != 0x5e) ||
               ((*(byte *)((int)tmp_pu16 + 1) == 0 || (*(byte *)((int)tmp_pu16 + 1) == 0x5e)))) break;
            tmp_pu16 = (uint *)((int)tmp_pu16 + 2);
            if (tmp_pu16 == (uint *)0x0) goto LAB_000527b0;
          }
          tmp_pu16 = (uint *)((int)tmp_pu16 + 1);
          tmp_i20 = tmp_i20 + 1;
          tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f2;
        } while (tmp_pu16 != (uint *)0x0);
LAB_000527b0:
        tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.2;
        tmp_f24 = 466.0;
        goto LAB_000527dd;
      }
      tmp_pu16 = local_3c;
      Com_sprintf(tmp_pu16,0x20,"^7%i|%i/%i",local_cc,local_ec,tmp_i9);
      tmp_f24 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.25;
      tmp_pu17 = tmp_pu16;
      do {
        tmp_pu18 = tmp_pu17;
        tmp_u12 = *tmp_pu18 + 0xfefefeff & ~*tmp_pu18;
        tmp_u13 = tmp_u12 & 0x80808080;
        tmp_pu17 = tmp_pu18 + 1;
      } while (tmp_u13 == 0);
      if ((tmp_u12 & 0x8080) == 0) {
        tmp_pu17 = (uint *)((int)tmp_pu18 + 6);
        tmp_u13 = tmp_u13 >> 0x10;
      }
      tmp_i20 = 0;
      tmp_f2 = 0.0;
      tmp_i9 = (-3 - (uint)CARRY1((byte)tmp_u13,(byte)tmp_u13)) - (int)tmp_pu16;
      do {
        while( true ) {
          tmp_b1 = (byte)*tmp_pu16;
          if ((tmp_b1 == 0) || ((int)((int)tmp_pu17 + tmp_i9) <= tmp_i20)) goto LAB_00052b70;
          if ((tmp_b1 != 0x5e) ||
             ((*(byte *)((int)tmp_pu16 + 1) == 0 || (*(byte *)((int)tmp_pu16 + 1) == 0x5e)))) break;
          tmp_pu16 = (uint *)((int)tmp_pu16 + 2);
          if (tmp_pu16 == (uint *)0x0) goto LAB_00052b70;
        }
        tmp_pu16 = (uint *)((int)tmp_pu16 + 1);
        tmp_i20 = tmp_i20 + 1;
        tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f2;
      } while (tmp_pu16 != (uint *)0x0);
    }
LAB_00052b70:
    CG_Text_Paint_Ext_constprop_18
              ((float)(0x26a - (int)ROUND(tmp_f2 * tmp_f24)),0x43eb0000,0x3e6147ae,0x3e6147ae,3,
               0x1100f64);
  }
  else {
    if (-1 < local_cc) goto LAB_00052430;
    if (tmp_i9 < 0) goto LAB_00052dc0;
    if ((cg_HUDFlags[0xc] & 0x10) == 0) {
      tmp_pu16 = local_3c;
      Com_sprintf(tmp_pu16,0x20,"^7%i/%i",local_ec,tmp_i9);
      tmp_f24 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.25;
      tmp_pu17 = tmp_pu16;
      do {
        tmp_pu18 = tmp_pu17;
        tmp_u12 = *tmp_pu18 + 0xfefefeff & ~*tmp_pu18;
        tmp_u13 = tmp_u12 & 0x80808080;
        tmp_pu17 = tmp_pu18 + 1;
      } while (tmp_u13 == 0);
      if ((tmp_u12 & 0x8080) == 0) {
        tmp_pu17 = (uint *)((int)tmp_pu18 + 6);
        tmp_u13 = tmp_u13 >> 0x10;
      }
      tmp_i20 = 0;
      tmp_f2 = 0.0;
      tmp_i9 = (-3 - (uint)CARRY1((byte)tmp_u13,(byte)tmp_u13)) - (int)tmp_pu16;
      do {
        tmp_b1 = (byte)*tmp_pu16;
        if ((tmp_b1 == 0) || ((int)((int)tmp_pu17 + tmp_i9) <= tmp_i20)) break;
        if ((tmp_b1 == 0x5e) &&
           ((*(byte *)((int)tmp_pu16 + 1) != 0 && (*(byte *)((int)tmp_pu16 + 1) != 0x5e)))) {
          tmp_pu16 = (uint *)((int)tmp_pu16 + 2);
        }
        else {
          tmp_pu16 = (uint *)((int)tmp_pu16 + 1);
          tmp_i20 = tmp_i20 + 1;
          tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f2;
        }
      } while (tmp_pu16 != (uint *)0x0);
      goto LAB_00052b70;
    }
    local_7c[0] = 590.0;
    local_7c[4] = 458.0;
    local_7c[8] = 1.0;
    local_7c[0xc] = 4.0;
    local_3c[0] = 0x3f800000;
    tmp_i20 = *(int *)(ammoTableMP + g_unk_010907a0 * 0x48 + 8);
    local_3c[1] = 0x3f800000;
    local_3c[2] = 0x3f800000;
    local_3c[3] = 0x3f800000;
    CG_AdjustFrom640(local_7c,local_7c + 4,local_7c + 8,local_7c + 0xc);
    tmp_i19 = tmp_i20 + 3;
    if (-1 < tmp_i20) {
      tmp_i19 = tmp_i20;
    }
    if (local_ec <= tmp_i19 >> 2) {
      local_3c[2] = 0;
      local_3c[1] = 0;
    }
    if (tmp_i20 < 1) {
      local_ec = 0;
    }
    else {
      tmp_i19 = 0;
      tmp_i11 = 0;
      do {
        if (local_ec <= tmp_i11) {
          local_3c[3] = 0x3eb33333;
        }
        if ((tmp_i11 == 100) || (tmp_i11 == 0x32)) {
          tmp_i19 = tmp_i19 + 1;
          local_7c[4] = (float)GHIDRA_FIELD(cgs, 27368, 4) * 5.0 + local_7c[4];
          local_7c[0] = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27364, 4) * 590.0;
        }
        tmp_i11 = tmp_i11 + 1;
        trap_R_SetColor(local_3c);
        trap_R_DrawStretchPic
                  (local_7c[0],local_7c[4],local_7c[8],local_7c[0xc],0,0,0,0x3f800000,GHIDRA_FIELD(cgs, 67836, 4))
        ;
        trap_R_SetColor(0);
        local_7c[0] = local_7c[0] - 3.0;
      } while (tmp_i11 != tmp_i20);
      local_ec = tmp_i19 * 5;
    }
    tmp_pu17 = local_3c;
    Com_sprintf(tmp_pu17,0x20,&g_unk_0011341c,tmp_i9);
    tmp_f24 = (float)local_ec * 0.5 + 463.0;
    tmp_pu16 = tmp_pu17;
    do {
      tmp_pu18 = tmp_pu16;
      tmp_u12 = *tmp_pu18 + 0xfefefeff & ~*tmp_pu18;
      tmp_u13 = tmp_u12 & 0x80808080;
      tmp_pu16 = tmp_pu18 + 1;
    } while (tmp_u13 == 0);
    if ((tmp_u12 & 0x8080) == 0) {
      tmp_pu16 = (uint *)((int)tmp_pu18 + 6);
      tmp_u13 = tmp_u13 >> 0x10;
    }
    tmp_i20 = 0;
    tmp_f2 = 0.0;
    tmp_i9 = (-3 - (uint)CARRY1((byte)tmp_u13,(byte)tmp_u13)) - (int)tmp_pu17;
    do {
      tmp_b1 = (byte)*tmp_pu17;
      if ((tmp_b1 == 0) || ((int)((int)tmp_pu16 + tmp_i9) <= tmp_i20)) break;
      if ((tmp_b1 == 0x5e) &&
         ((*(byte *)((int)tmp_pu17 + 1) != 0 && (*(byte *)((int)tmp_pu17 + 1) != 0x5e)))) {
        tmp_pu17 = (uint *)((int)tmp_pu17 + 2);
      }
      else {
        tmp_pu17 = (uint *)((int)tmp_pu17 + 1);
        tmp_i20 = tmp_i20 + 1;
        tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f2;
      }
    } while (tmp_pu17 != (uint *)0x0);
    tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.2 * tmp_f2;
LAB_000527dd:
    CG_Text_Paint_Ext_constprop_18
              (606.0 - (float)(int)ROUND(tmp_f2) * 0.5,tmp_f24,0x3e4ccccd,0x3e4ccccd,3,0x1100f64);
  }
LAB_00051724:
  local_ac = local_7c + 8;
  local_d0 = local_7c + 0xc;
  local_9c = 558.0;
  local_98 = 424.0;
  local_94 = 60.0;
  local_90 = 32.0;
  CG_DrawWeapHeat(&local_9c,1);
  if (GHIDRA_FIELD(cg_drawWeaponIconFlash, 12, 4) == 0) {
    CG_DrawPlayerWeaponIcon(&local_9c,1,2,&colorWhite);
  }
  else {
    tmp_i9 = BG_simpleWeaponState(*(uint32_t *)(g_unk_01047b00 + 0xd4));
    if (tmp_i9 == 1) {
      tmp_pu15 = (uint8_t *)&colorWhite;
    }
    else if (tmp_i9 == 2) {
      tmp_pu15 = colorRed;
    }
    else {
      tmp_pu15 = (uint8_t *)&colorYellow;
    }
    CG_DrawPlayerWeaponIcon(&local_9c,tmp_i9 != 0,2,tmp_pu15);
  }
  local_9c = 18.0;
  local_98 = 388.0;
  local_94 = 12.0;
  local_90 = 72.0;
  CG_HudPlacement(1);
  CG_ColorForHealth(local_d0);
  local_7c[0xf] = 0.5;
  if (((*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x94b8) == 1) && (GHIDRA_FIELD(cgs, 27388, 4) != 8)
      ) && (GHIDRA_FIELD(cgs, 33787756, 4) == 0)) {
    tmp_f24 = (float)*(int *)(g_unk_01047b00 + 0xfc) / (float)*(int *)(g_unk_01047b00 + 0x120);
  }
  else {
    tmp_f24 = (float)*(int *)(g_unk_01047b00 + 0xfc) / (float)*(int *)(g_unk_01047b00 + 0x10c);
  }
  CG_FilledBar(local_9c,local_90 * 0.1 + local_98,local_94,local_90 * 0.84,local_d0,0,bgcolour,
               tmp_f24,0x55);
  trap_R_SetColor(0);
  CG_DrawPic(local_9c,local_98,local_94,local_90,GHIDRA_FIELD(cgs, 67844, 4));
  CG_DrawPic(local_9c,local_98 + local_90 + 4.0,local_94,local_94,GHIDRA_FIELD(cgs, 131764, 4));
  local_9c = 4.0;
  local_98 = 388.0;
  local_94 = 12.0;
  local_90 = 72.0;
  tmp_i9 = BG_GetConditionValue(*(uint32_t *)(g_unk_01047b00 + 0xcc),3,1);
  if (tmp_i9 == 0) {
    local_7c[8] = 0.1;
    local_7c[9] = 1.0;
    local_7c[10] = 0.1;
    local_7c[0xb] = 0.5;
    local_7c[0xc] = 1.0;
    local_7c[0xd] = 0.1;
    local_7c[0xe] = 0.1;
    local_7c[0xf] = 0.5;
    tmp_f24 = (float)*(int *)(g_unk_01047b00 + 0x114) / 20000.0;
    CG_HudPlacement(1);
    tmp_f2 = local_7c[8];
    pfVar10 = local_ac;
    if (*(int *)(g_unk_01047b00 + 0x1a8) == 0) {
      if (tmp_f24 < 0.25) {
        pfVar10 = local_d0;
      }
    }
    else {
      tmp_i9 = *(int *)(g_unk_01047b00 + 0x1a8) - g_unk_010906e0;
      if (0.0 <= (float)tmp_i9) {
        tmp_d23 = (double)tmp_i9;
        tmp_f5 = SQRT((float)tmp_i9);
        tmp_f4 = tmp_f5;
        if (NAN(tmp_f5)) {
          tmp_d21 = sqrt((double)tmp_i9);
          tmp_f4 = (float)tmp_d21;
        }
        tmp_d21 = sin((double)((tmp_f4 * 0.2 + tmp_f4 * 0.2) * 3.1415927));
        tmp_f6 = colorWhite;
        tmp_f4 = tmp_f5;
        if (NAN(tmp_f5)) {
          tmp_d22 = sqrt(tmp_d23);
          tmp_f4 = (float)tmp_d22;
        }
        tmp_d22 = sin((double)((tmp_f4 * 0.2 + tmp_f4 * 0.2) * 3.1415927));
        tmp_f4 = local_7c[9];
        local_7c[8] = ((float)tmp_d22 * 0.5 + 0.5) * tmp_f6 +
                      (1.0 - ((float)tmp_d21 * 0.5 + 0.5)) * tmp_f2;
        tmp_f2 = tmp_f5;
        if (NAN(tmp_f5)) {
          tmp_d21 = sqrt(tmp_d23);
          tmp_f2 = (float)tmp_d21;
        }
        tmp_d21 = sin((double)((tmp_f2 * 0.2 + tmp_f2 * 0.2) * 3.1415927));
        tmp_f6 = g_unk_0014a334;
        tmp_f2 = tmp_f5;
        if (NAN(tmp_f5)) {
          tmp_d22 = sqrt(tmp_d23);
          tmp_f2 = (float)tmp_d22;
        }
        tmp_d22 = sin((double)((tmp_f2 * 0.2 + tmp_f2 * 0.2) * 3.1415927));
        tmp_f7 = local_7c[10];
        local_7c[9] = ((float)tmp_d22 * 0.5 + 0.5) * tmp_f6 +
                      (1.0 - ((float)tmp_d21 * 0.5 + 0.5)) * tmp_f4;
        tmp_f2 = tmp_f5;
        if (NAN(tmp_f5)) {
          tmp_d21 = sqrt(tmp_d23);
          tmp_f2 = (float)tmp_d21;
        }
        tmp_d21 = sin((double)((tmp_f2 * 0.2 + tmp_f2 * 0.2) * 3.1415927));
        tmp_f4 = g_unk_0014a338;
        tmp_f2 = tmp_f5;
        if (NAN(tmp_f5)) {
          tmp_d22 = sqrt(tmp_d23);
          tmp_f2 = (float)tmp_d22;
        }
        tmp_d22 = sin((double)((tmp_f2 * 0.2 + tmp_f2 * 0.2) * 3.1415927));
        tmp_f6 = local_7c[0xb];
        local_7c[10] = ((float)tmp_d22 * 0.5 + 0.5) * tmp_f4 +
                       (1.0 - ((float)tmp_d21 * 0.5 + 0.5)) * tmp_f7;
        tmp_f2 = tmp_f5;
        if (NAN(tmp_f5)) {
          tmp_d21 = sqrt(tmp_d23);
          tmp_f2 = (float)tmp_d21;
        }
        tmp_d21 = sin((double)((tmp_f2 * 0.2 + tmp_f2 * 0.2) * 3.1415927));
        tmp_f2 = g_unk_0014a33c;
        if (NAN(tmp_f5)) {
          tmp_d23 = sqrt(tmp_d23);
          tmp_f5 = (float)tmp_d23;
        }
        tmp_d23 = sin((double)((tmp_f5 * 0.2 + tmp_f5 * 0.2) * 3.1415927));
        local_7c[0xb] =
             ((float)tmp_d23 * 0.5 + 0.5) * tmp_f2 + (1.0 - ((float)tmp_d21 * 0.5 + 0.5)) * tmp_f6;
      }
    }
    CG_FilledBar(local_9c,local_90 * 0.1 + local_98,local_94,local_90 * 0.84,pfVar10,0,bgcolour,
                 tmp_f24,0x55);
    trap_R_SetColor(0);
    CG_DrawPic(local_9c,local_98,local_94,local_90,GHIDRA_FIELD(cgs, 67844, 4));
    CG_DrawPic(local_9c,local_98 + local_90 + 4.0,local_94,local_94,GHIDRA_FIELD(cgs, 131760, 4));
  }
  else {
    CG_HudPlacement(1);
    local_7c[0xf] = 0.5;
    CG_FilledBar(local_9c,local_90 * 0.1 + local_98,local_94,local_90 * 0.84,local_d0,0,bgcolour,
                 (float)(g_unk_010b5e40 - g_unk_010906e0) / 12000.0,0x55);
    trap_R_SetColor(0);
    CG_DrawPic(local_9c,local_98,local_94,local_90,GHIDRA_FIELD(cgs, 67844, 4));
    CG_DrawPic(local_9c,local_98 + local_90 + 4.0,local_94,local_94,GHIDRA_FIELD(cgs, 68160, 4));
  }
  local_9c = 624.0;
  local_98 = 388.0;
  local_94 = 12.0;
  local_90 = 72.0;
  local_8c = 0x3f800000;
  local_88 = 0x3f000000;
  local_84 = 0;
  local_80 = 0x3f800000;
  local_7c[0] = 1.0;
  local_7c[1] = 1.0;
  local_7c[2] = 0.0;
  local_7c[3] = 1.0;
  local_7c[4] = 1.0;
  local_7c[5] = 0.0;
  local_7c[6] = 0.0;
  local_7c[7] = 1.0;
  local_7c[8] = 1.0;
  local_7c[9] = 1.0;
  local_7c[10] = 1.0;
  local_7c[0xb] = 0.25;
  CG_HudPlacement(2);
  tmp_i9 = *(int *)(g_unk_01047b00 + 0x110);
  if (tmp_i9 == 2) {
    local_7c[0xd] = (float)(int)(&g_unk_010b3b08)[*(int *)(g_unk_01047b00 + 0x158)];
  }
  else if (tmp_i9 == 1) {
    local_7c[0xd] = (float)(int)(&g_unk_010b3b10)[*(int *)(g_unk_01047b00 + 0x158)];
  }
  else if (tmp_i9 == 3) {
    local_7c[0xd] = (float)*(int *)(&g_unk_010b3af8 + *(int *)(g_unk_01047b00 + 0x158) * 4);
  }
  else if (tmp_i9 == 4) {
    local_7c[0xd] = (float)(int)(&g_unk_010b3b18)[*(int *)(g_unk_01047b00 + 0x158)];
  }
  else {
    local_7c[0xd] = (float)(int)(&g_unk_010b3b00)[*(int *)(g_unk_01047b00 + 0x158)];
  }
  local_7c[0xd] = (float)(g_unk_010906e0 - *(int *)(g_unk_01047b00 + 0x4a4)) / local_7c[0xd];
  if (local_7c[0xd] <= 1.0) {
    local_7c[0xf] = local_7c[0xd] * 0.5 + 0.25;
  }
  else {
    local_7c[0xf] = 0.75;
    local_7c[0xd] = 1.0;
  }
  local_7c[0xc] = 1.0;
  local_7c[0xe] = local_7c[0xd];
  CG_FilledBar(local_9c,local_90 * 0.1 + local_98,local_94,local_90 * 0.84,local_d0,0,local_ac,
               local_7c[0xd],0x55);
  trap_R_SetColor(0);
  CG_DrawPic(local_9c,local_98,local_94,local_90,GHIDRA_FIELD(cgs, 67844, 4));
  if (*(int *)(g_unk_01047b00 + 0x110) == 3) {
    tmp_u13 = *(uint *)(g_unk_01047b00 + 0x1f0);
    if ((tmp_u13 & 1) == 0) {
      if ((tmp_u13 & 2) != 0) {
        trap_R_SetColor(&local_8c);
      }
    }
    else if ((tmp_u13 & 2) == 0) {
      trap_R_SetColor(local_7c);
    }
    else {
      trap_R_SetColor(local_7c + 4);
    }
  }
  CG_DrawPic((local_94 * 0.25 + local_9c) - 1.0,local_98 + local_90 + 4.0,local_94 * 0.5 + 2.0,
             local_94 + 2.0,GHIDRA_FIELD(cgs, 131756, 4));
  if (*(int *)(g_unk_01047b00 + 0x1f0) != 0) {
    trap_R_SetColor(0);
  }
  return;
}

void CG_Text_SetActiveFont(uint32_t param_1)
{
  activeFont = param_1;
  return;
}

int CG_Text_Width_Ext(byte *param_1,float param_2,size_t param_3,int param_4)
{
  float tmp_f1;
  byte tmp_b2;
  float tmp_f3;
  size_t tmp_s4;
  int tmp_i5;
  
  tmp_f1 = *(float *)(param_4 + 0x5000);
  if (param_1 == (byte *)0x0) {
    tmp_f3 = 0.0;
  }
  else {
    tmp_s4 = strlen((char *)param_1);
    if (((int)tmp_s4 <= (int)param_3) || ((int)param_3 < 1)) {
      param_3 = tmp_s4;
    }
    tmp_f3 = 0.0;
    tmp_i5 = 0;
    do {
      while( true ) {
        tmp_b2 = *param_1;
        if ((tmp_b2 == 0) || ((int)param_3 <= tmp_i5)) goto LAB_00053050;
        if ((tmp_b2 != 0x5e) || ((param_1[1] == 0 || (param_1[1] == 0x5e)))) break;
        param_1 = param_1 + 2;
        if (param_1 == (byte *)0x0) goto LAB_00053050;
      }
      param_1 = param_1 + 1;
      tmp_i5 = tmp_i5 + 1;
      tmp_f3 = (float)*(int *)(param_4 + 0x10 + (uint)tmp_b2 * 0x50) + tmp_f3;
    } while (param_1 != (byte *)0x0);
  }
LAB_00053050:
  return (int)ROUND(tmp_f3 * param_2 * tmp_f1);
}

int CG_Text_Width(byte *param_1,float param_2,size_t param_3)
{
  float tmp_f1;
  byte tmp_b2;
  float tmp_f3;
  int tmp_i4;
  size_t tmp_s5;
  int tmp_i6;
  
  tmp_i4 = activeFont;
  tmp_f1 = *(float *)(&g_unk_0102b1bc + activeFont * 0x5044);
  if (param_1 == (byte *)0x0) {
    tmp_f3 = 0.0;
  }
  else {
    tmp_s5 = strlen((char *)param_1);
    if (((int)tmp_s5 <= (int)param_3) || ((int)param_3 < 1)) {
      param_3 = tmp_s5;
    }
    tmp_i6 = 0;
    tmp_f3 = 0.0;
    do {
      while( true ) {
        tmp_b2 = *param_1;
        if ((tmp_b2 == 0) || ((int)param_3 <= tmp_i6)) goto LAB_00053160;
        if ((tmp_b2 != 0x5e) || ((param_1[1] == 0 || (param_1[1] == 0x5e)))) break;
        param_1 = param_1 + 2;
        if (param_1 == (byte *)0x0) goto LAB_00053160;
      }
      param_1 = param_1 + 1;
      tmp_i6 = tmp_i6 + 1;
      tmp_f3 = (float)*(int *)(&g_unk_010261cc + (uint)tmp_b2 * 0x50 + tmp_i4 * 0x5044) + tmp_f3;
    } while (param_1 != (byte *)0x0);
  }
LAB_00053160:
  return (int)ROUND(tmp_f3 * param_2 * tmp_f1);
}

int CG_Text_Height_Ext(byte *param_1,float param_2,size_t param_3,int param_4)
{
  float tmp_f1;
  byte tmp_b2;
  float tmp_f3;
  float tmp_f4;
  size_t tmp_s5;
  int tmp_i6;
  
  tmp_f1 = *(float *)(param_4 + 0x5000);
  if (param_1 == (byte *)0x0) {
    tmp_f3 = 0.0;
  }
  else {
    tmp_s5 = strlen((char *)param_1);
    if (((int)tmp_s5 <= (int)param_3) || ((int)param_3 < 1)) {
      param_3 = tmp_s5;
    }
    tmp_f3 = 0.0;
    tmp_i6 = 0;
    do {
      while( true ) {
        tmp_b2 = *param_1;
        if ((tmp_b2 == 0) || ((int)param_3 <= tmp_i6)) goto LAB_00053240;
        if ((tmp_b2 != 0x5e) || ((param_1[1] == 0 || (param_1[1] == 0x5e)))) break;
        param_1 = param_1 + 2;
        if (param_1 == (byte *)0x0) goto LAB_00053240;
      }
      tmp_f4 = (float)*(int *)(param_4 + (uint)tmp_b2 * 0x50);
      if (tmp_f4 <= tmp_f3) {
        tmp_f4 = tmp_f3;
      }
      tmp_f3 = tmp_f4;
      param_1 = param_1 + 1;
      tmp_i6 = tmp_i6 + 1;
    } while (param_1 != (byte *)0x0);
  }
LAB_00053240:
  return (int)ROUND(tmp_f3 * param_2 * tmp_f1);
}

int CG_Text_Height(byte *param_1,float param_2,size_t param_3)
{
  float tmp_f1;
  byte tmp_b2;
  float tmp_f3;
  int tmp_i4;
  float tmp_f5;
  size_t tmp_s6;
  int tmp_i7;
  
  tmp_i4 = activeFont;
  tmp_f1 = *(float *)(&g_unk_0102b1bc + activeFont * 0x5044);
  if (param_1 == (byte *)0x0) {
    tmp_f3 = 0.0;
  }
  else {
    tmp_s6 = strlen((char *)param_1);
    if (((int)tmp_s6 <= (int)param_3) || ((int)param_3 < 1)) {
      param_3 = tmp_s6;
    }
    tmp_i7 = 0;
    tmp_f3 = 0.0;
    do {
      while( true ) {
        tmp_b2 = *param_1;
        if ((tmp_b2 == 0) || ((int)param_3 <= tmp_i7)) goto LAB_00053350;
        if ((tmp_b2 != 0x5e) || ((param_1[1] == 0 || (param_1[1] == 0x5e)))) break;
        param_1 = param_1 + 2;
        if (param_1 == (byte *)0x0) goto LAB_00053350;
      }
      tmp_f5 = (float)*(int *)(&g_unk_010261bc + (uint)tmp_b2 * 0x50 + tmp_i4 * 0x5044);
      if ((float)*(int *)(&g_unk_010261bc + (uint)tmp_b2 * 0x50 + tmp_i4 * 0x5044) <= tmp_f3) {
        tmp_f5 = tmp_f3;
      }
      tmp_f3 = tmp_f5;
      param_1 = param_1 + 1;
      tmp_i7 = tmp_i7 + 1;
    } while (param_1 != (byte *)0x0);
  }
LAB_00053350:
  return (int)ROUND(tmp_f3 * param_2 * tmp_f1);
}

void CG_Text_PaintChar_Ext
               (uint32_t param_1,uint32_t param_2,float param_3,float param_4,float param_5,
               float param_6,uint32_t param_7,uint32_t param_8,uint32_t param_9,
               uint32_t param_10,uint32_t param_11)

{
  param_3 = param_3 * param_5;
  param_4 = param_4 * param_6;
  CG_AdjustFrom640(&param_1,&param_2,&param_3,&param_4);
  trap_R_DrawStretchPic(param_1,param_2,param_3,param_4,param_7,param_8,param_9,param_10,param_11);
  return;
}

void CG_Text_Paint_Ext(float param_1,float param_2,float param_3,float param_4,uint32_t *param_5,
                      byte *param_6,float param_7,size_t param_8,int param_9,int param_10)

{
  uint32_t *tmp_pu1;
  int *tmp_pi2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  int tmp_i6;
  float tmp_f7;
  byte tmp_b8;
  uint32_t tmp_u9;
  uint32_t tmp_u10;
  float tmp_f11;
  size_t tmp_s12;
  int tmp_i13;
  uint tmp_u14;
  int local_74;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  param_3 = *(float *)(param_10 + 0x5000) * param_3;
  param_4 = *(float *)(param_10 + 0x5000) * param_4;
  if (param_6 != (byte *)0x0) {
    trap_R_SetColor(param_5);
    local_2c = *param_5;
    local_28 = param_5[1];
    local_24 = param_5[2];
    local_20 = param_5[3];
    tmp_s12 = strlen((char *)param_6);
    if (((int)tmp_s12 <= (int)param_8) || ((int)param_8 < 1)) {
      param_8 = tmp_s12;
    }
    local_74 = 0;
    do {
      while( true ) {
        tmp_b8 = *param_6;
        if ((tmp_b8 == 0) || ((int)param_8 <= local_74)) goto LAB_00053710;
        tmp_u14 = (uint)tmp_b8;
        if (tmp_b8 == 0x5e) break;
LAB_00053540:
        tmp_i13 = tmp_u14 * 0x50 + param_10;
        tmp_f11 = (float)*(int *)(tmp_i13 + 4) * param_4;
        if (param_9 - 6U < 2 || param_9 == 3) {
          if (param_9 == 6) {
            tmp_f7 = 2.0;
          }
          else if (param_9 == 7) {
            tmp_f7 = 0.75;
          }
          else {
            tmp_f7 = 1.0;
          }
          g_unk_0014a3bc = local_20;
          trap_R_SetColor(&colorBlack);
          tmp_pu1 = (uint32_t *)(param_10 + 0x20 + tmp_u14 * 0x50);
          tmp_i6 = param_10 + 0x10 + tmp_u14 * 0x50;
          tmp_u10 = tmp_pu1[3];
          tmp_u3 = tmp_pu1[2];
          tmp_u4 = tmp_pu1[1];
          tmp_u5 = *tmp_pu1;
          tmp_u9 = *(uint32_t *)(tmp_i6 + 0xc);
          local_4c = (float)*(int *)(tmp_i13 + 0xc) * param_3 + param_1 + tmp_f7;
          local_48 = tmp_f7 + (param_2 - tmp_f11);
          local_44 = param_3 * (float)*(int *)(tmp_i6 + 4);
          local_40 = (float)*(int *)(tmp_i6 + 8) * param_4;
          CG_AdjustFrom640(&local_4c,&local_48,&local_44,&local_40);
          trap_R_DrawStretchPic(local_4c,local_48,local_44,local_40,tmp_u9,tmp_u5,tmp_u4,tmp_u3,tmp_u10);
          g_unk_0014a3bc = 0x3f800000;
          trap_R_SetColor(&local_2c);
        }
        local_38 = param_2 - tmp_f11;
        tmp_pu1 = (uint32_t *)(param_10 + 0x20 + tmp_u14 * 0x50);
        tmp_u3 = tmp_pu1[2];
        tmp_pi2 = (int *)(param_10 + 0x10 + tmp_u14 * 0x50);
        tmp_u9 = tmp_pu1[3];
        tmp_u4 = tmp_pu1[1];
        tmp_u5 = *tmp_pu1;
        tmp_i6 = tmp_pi2[3];
        local_3c = (float)*(int *)(tmp_i13 + 0xc) * param_3 + param_1;
        local_34 = (float)tmp_pi2[1] * param_3;
        local_30 = (float)tmp_pi2[2] * param_4;
        CG_AdjustFrom640(&local_3c,&local_38,&local_34,&local_30);
        trap_R_DrawStretchPic(local_3c,local_38,local_34,local_30,tmp_i6,tmp_u5,tmp_u4,tmp_u3,tmp_u9);
        local_74 = local_74 + 1;
        param_6 = param_6 + 1;
        param_1 = (float)*tmp_pi2 * param_3 + param_7 + param_1;
        if (param_6 == (byte *)0x0) goto LAB_00053710;
      }
      tmp_b8 = param_6[1];
      if ((tmp_b8 == 0) || (tmp_b8 == 0x5e)) goto LAB_00053540;
      if (tmp_b8 == 0x2a) {
        local_2c = *param_5;
        local_28 = param_5[1];
        local_24 = param_5[2];
        local_20 = param_5[3];
      }
      else {
        tmp_i13 = ((int)(char)tmp_b8 - 0x30U & 0x1f) * 0x10;
        local_2c = *(uint32_t *)(g_color_table + tmp_i13);
        local_28 = *(uint32_t *)(g_color_table + tmp_i13 + 4);
        local_24 = *(uint32_t *)(g_color_table + tmp_i13 + 8);
        local_20 = param_5[3];
      }
      trap_R_SetColor(&local_2c);
      param_6 = param_6 + 2;
    } while (param_6 != (byte *)0x0);
LAB_00053710:
    trap_R_SetColor(0);
  }
  return;
}

void CG_Text_Paint_Centred_Ext(void)
{
  size_t tmp_s1;
  int tmp_i2;
  char *in_stack_00000018;
  size_t in_stack_00000020;
  
  if (in_stack_00000018 != (char *)0x0) {
    tmp_s1 = strlen(in_stack_00000018);
    if (((int)in_stack_00000020 < (int)tmp_s1) && (0 < (int)in_stack_00000020)) {
      tmp_s1 = in_stack_00000020;
    }
    tmp_i2 = 0;
    do {
      while( true ) {
        if ((*in_stack_00000018 == '\0') || ((int)tmp_s1 <= tmp_i2)) goto LAB_00053a02;
        if ((*in_stack_00000018 != '^') ||
           ((in_stack_00000018[1] == '\0' || (in_stack_00000018[1] == '^')))) break;
        in_stack_00000018 = in_stack_00000018 + 2;
        if (in_stack_00000018 == (char *)0x0) goto LAB_00053a02;
      }
      in_stack_00000018 = in_stack_00000018 + 1;
      tmp_i2 = tmp_i2 + 1;
    } while (in_stack_00000018 != (char *)0x0);
  }
LAB_00053a02:
  CG_Text_Paint_Ext();
  return;
}

void CG_Text_Paint(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
                  uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8)

{
  CG_Text_Paint_Ext(param_1,param_2,param_3,param_3,param_4,param_5,param_6,param_7,param_8,
                    &g_unk_010261bc + activeFont * 0x5044);
  return;
}

int CG_DrawField(int param_1,int param_2,char *param_3,int param_4,int param_5,int param_6,
                int param_7,int param_8)

{
  uint *tmp_pu1;
  uint *tmp_pu2;
  char *tmp_pc3;
  uint tmp_u4;
  uint tmp_u5;
  int tmp_i6;
  uint *tmp_pu7;
  int local_3c;
  uint32_t local_2c;
  
  if ((int)param_3 < 1) {
    return 0;
  }
  if ((int)param_3 < 6) {
    if (param_3 == (char *)0x2) {
      if (99 < param_4) {
        param_4 = 99;
      }
      if (param_4 < -9) {
        param_4 = -9;
      }
    }
    else if ((int)param_3 < 3) {
      if (param_3 == (char *)0x1) {
        if (9 < param_4) {
          param_4 = 9;
        }
        if (param_4 < 0) {
          param_4 = 0;
        }
      }
    }
    else if (param_3 == (char *)0x3) {
      if (999 < param_4) {
        param_4 = 999;
      }
      if (param_4 < -99) {
        param_4 = -99;
      }
    }
    else if (param_3 == (char *)0x4) {
      if (9999 < param_4) {
        param_4 = 9999;
      }
      if (param_4 < -999) {
        param_4 = -999;
      }
    }
  }
  else {
    param_3 = (char *)0x5;
  }
  tmp_pu7 = &local_2c;
  Com_sprintf(tmp_pu7,0x10,"%i",param_4);
  tmp_pu2 = tmp_pu7;
  do {
    tmp_pu1 = tmp_pu2;
    tmp_u4 = *tmp_pu1 + 0xfefefeff & ~*tmp_pu1;
    tmp_u5 = tmp_u4 & 0x80808080;
    tmp_pu2 = tmp_pu1 + 1;
  } while (tmp_u5 == 0);
  if ((tmp_u4 & 0x8080) == 0) {
    tmp_pu2 = (uint *)((int)tmp_pu1 + 6);
    tmp_u5 = tmp_u5 >> 0x10;
  }
  tmp_pc3 = (char *)((int)tmp_pu2 + ((-3 - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5)) - (int)tmp_pu7));
  if ((int)tmp_pc3 <= (int)param_3) {
    param_3 = tmp_pc3;
  }
  if (param_8 == 0) {
    param_1 = (param_1 - param_5 * (int)param_3) + -2;
  }
  if (((param_3 != (char *)0x0) && ((char)local_2c != '\0')) && (param_7 != 0)) {
    local_3c = param_1;
    do {
      if ((char)local_2c == '-') {
        tmp_i6 = 10;
      }
      else {
        tmp_i6 = (char)local_2c + -0x30;
      }
      tmp_pu7 = (uint *)((int)tmp_pu7 + 1);
      param_3 = param_3 + -1;
      CG_DrawPic((float)local_3c,(float)param_2,(float)param_5,(float)param_6,
                 *(uint32_t *)(cgs + tmp_i6 * 4 + 0x10c54));
      GHIDRA_FIELD(local_2c, 0, 1) = *(char *)tmp_pu7;
      local_3c = local_3c + param_5;
    } while (((char)local_2c != '\0') && (param_3 != (char *)0x0));
    return param_1;
  }
  return param_1;
}

long double CG_DrawTime(float param_1,int param_2)
{
  byte tmp_b1;
  float tmp_f2;
  uint32_t tmp_u3;
  uint8_t *tmp_pu4;
  uint tmp_u5;
  uint tmp_u6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  int tmp_i9;
  uint *tmp_pu10;
  uint *tmp_pu11;
  uint *local_60;
  uint8_t local_4c [12];
  uint32_t local_40;
  uint32_t local_3c;
  int local_38;
  
  if (param_2 != 0) {
    CG_HudPlacement(2);
    trap_RealTime(&local_40);
    local_4c[0] = 0;
    if (GHIDRA_FIELD(cg_drawTime, 12, 4) == 1) {
      tmp_pu7 = &g_unk_0011d841;
      if (GHIDRA_FIELD(cg_drawTimeSeconds, 12, 4) != 0) {
        tmp_pu7 = (uint8_t *)va(":%02d",local_40);
      }
      tmp_u3 = va("%d:%02d%s",local_38,local_3c,tmp_pu7);
      Q_strcat(local_4c,0xc,tmp_u3);
    }
    else {
      if ((local_38 == 0xc) || (local_38 == 0)) {
        tmp_i8 = 0xc;
      }
      else {
        tmp_i8 = local_38 % 0xc;
      }
      tmp_u3 = va(&g_unk_00113446,tmp_i8,local_3c);
      Q_strcat(local_4c,0xc,tmp_u3);
      if (GHIDRA_FIELD(cg_drawTimeSeconds, 12, 4) != 0) {
        tmp_u3 = va(":%02d",local_40);
        Q_strcat(local_4c,0xc,tmp_u3);
      }
      if (local_38 < 0xc) {
        tmp_pu4 = &g_unk_00113434;
      }
      else {
        tmp_pu4 = &g_unk_00113438;
      }
      Q_strcat(local_4c,0xc,tmp_pu4);
    }
    local_60 = (uint *)local_4c;
    tmp_pu11 = local_60;
    do {
      tmp_pu10 = tmp_pu11;
      tmp_u5 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
      tmp_u6 = tmp_u5 & 0x80808080;
      tmp_pu11 = tmp_pu10 + 1;
    } while (tmp_u6 == 0);
    if ((tmp_u5 & 0x8080) == 0) {
      tmp_pu11 = (uint *)((int)tmp_pu10 + 6);
      tmp_u6 = tmp_u6 >> 0x10;
    }
    tmp_i9 = 0;
    tmp_f2 = 0.0;
    tmp_i8 = (-3 - (uint)CARRY1((byte)tmp_u6,(byte)tmp_u6)) - (int)local_60;
    do {
      while( true ) {
        tmp_b1 = (byte)*local_60;
        if ((tmp_b1 == 0) || ((int)((int)tmp_pu11 + tmp_i8) <= tmp_i9)) goto LAB_00053ee0;
        if ((tmp_b1 != 0x5e) ||
           ((*(byte *)((int)local_60 + 1) == 0 || (*(byte *)((int)local_60 + 1) == 0x5e)))) break;
        local_60 = (uint *)((int)local_60 + 2);
        if (local_60 == (uint *)0x0) goto LAB_00053ee0;
      }
      local_60 = (uint *)((int)local_60 + 1);
      tmp_i9 = tmp_i9 + 1;
      tmp_f2 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f2;
    } while (local_60 != (uint *)0x0);
LAB_00053ee0:
    tmp_i8 = (int)ROUND(tmp_f2 * (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.19);
    CG_FillRect((float)(0x278 - tmp_i8),param_1,(float)(tmp_i8 + 5),0x41600000,&HUD_Background);
    CG_DrawRect_FixedBorder
              ((float)(0x278 - tmp_i8),param_1,(float)(tmp_i8 + 5),0x41600000,1,&HUD_Border);
    CG_Text_Paint_Ext_constprop_18
              ((float)(0x27a - tmp_i8),param_1 + 11.0,0x3e428f5c,0x3e428f5c,0,0x1100f64);
  }
  return (long double)param_1 + (long double)12.0 + (long double)4.0;
}

void CG_DrawDisconnect(uint32_t param_1)
{
  int tmp_i1;
  int local_28 [7];
  
  CG_HudPlacement(0);
  if (((g_unk_01047aec == 0) || ((float)GHIDRA_FIELD(cg_timescale, 8, 4) == 1.0)) && (g_unk_010b4558 == 0)) {
    tmp_i1 = trap_GetCurrentCmdNumber();
    trap_GetUserCmd(tmp_i1 + -0x3f,local_28);
    if ((*(int *)(g_unk_01047b00 + 0x2c) < local_28[0]) && (local_28[0] <= (int)g_unk_010906e0)) {
      tmp_i1 = CG_DrawStrlen("Connection Interrupted");
      CG_DrawBigString(0x140 - ((tmp_i1 << 4) >> 1),100,"Connection Interrupted",0x3f800000);
      if (((g_unk_010906e0 & 0x200) == 0) && (GHIDRA_FIELD(cg_lagometer, 12, 4) != 0)) {
        CG_HudPlacement(2);
        CG_DrawPic(0x44140000,param_1,0x42400000,0x42400000,GHIDRA_FIELD(cgs, 131856, 4));
      }
    }
  }
  return;
}

long double CG_DrawLagometer(float param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  bool tmp_b7;
  uint tmp_u8;
  uint tmp_u9;
  int local_50;
  float local_3c;
  float local_38;
  float local_34;
  float local_30 [7];
  uint32_t uStack_14;
  
  uStack_14 = 0x54339;
  local_30[1] = 0.0;
  local_30[2] = 1.0;
  local_30[3] = 0.0;
  local_30[4] = 0.5;
  if (GHIDRA_FIELD(cg_lagometer, 12, 4) == 0) {
    CG_DrawDisconnect(param_1);
    return (long double)0;
  }
  CG_HudPlacement(2);
  trap_R_SetColor(0);
  CG_FillRect(0x44140000,param_1,0x42400000,0x42400000,&HUD_Background);
  CG_DrawRect_FixedBorder(0x44140000,param_1,0x42400000,0x42400000,1,&HUD_Border);
  local_3c = 592.0;
  local_38 = param_1;
  local_34 = 48.0;
  local_30[0] = 48.0;
  CG_AdjustFrom640(&local_3c,&local_38,&local_34,local_30);
  tmp_f1 = local_30[0] / 3.0;
  tmp_f2 = local_38 + tmp_f1;
  tmp_f3 = local_34;
  if (0.0 < local_34) {
    tmp_f4 = 0.0;
    local_50 = -1;
    tmp_u9 = 0;
    do {
      while (tmp_f6 = (float)*(int *)(lagometer + (~tmp_u9 + GHIDRA_FIELD(lagometer, 512, 4) & 0x7f) * 4) *
                     (tmp_f1 / 300.0), 0.0 < tmp_f6) {
        if (local_50 != 1) {
          trap_R_SetColor(&colorYellow);
          tmp_f3 = local_34;
        }
        if (tmp_f1 < tmp_f6) {
          tmp_f6 = tmp_f1;
        }
        trap_R_DrawStretchPic
                  ((tmp_f3 + local_3c) - tmp_f4,tmp_f2 - tmp_f6,0x3f800000,tmp_f6,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
        local_50 = 1;
        tmp_f3 = local_34;
LAB_00054534:
        tmp_u9 = tmp_u9 + 1;
        tmp_f4 = (float)(int)tmp_u9;
        if (tmp_f3 <= tmp_f4) goto LAB_00054646;
      }
      if (0.0 <= tmp_f6) goto LAB_00054534;
      if (local_50 != 2) {
        trap_R_SetColor(&colorBlue);
        tmp_f3 = local_34;
      }
      tmp_f5 = -tmp_f6;
      if (tmp_f1 < -tmp_f6) {
        tmp_f5 = tmp_f1;
      }
      tmp_u9 = tmp_u9 + 1;
      trap_R_DrawStretchPic((tmp_f3 + local_3c) - tmp_f4,tmp_f2,0x3f800000,tmp_f5,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4))
      ;
      local_50 = 2;
      tmp_f4 = (float)(int)tmp_u9;
      tmp_f3 = local_34;
    } while (tmp_f4 < local_34);
  }
  else {
    local_50 = -1;
  }
LAB_00054646:
  tmp_f1 = local_30[0] * 0.5;
  if (0.0 < tmp_f3) {
    tmp_b7 = false;
    tmp_f2 = 0.0;
    tmp_u9 = 0;
    do {
      tmp_u8 = ~tmp_u9 + GHIDRA_FIELD(lagometer, 1540, 4) & 0x7f;
      tmp_f4 = (float)*(int *)(lagometer + tmp_u8 * 4 + 0x608);
      if ((((0.0 < tmp_f4) &&
           (tmp_f6 = (float)*(int *)(lagometer + tmp_u8 * 4 + 0x404),
           tmp_f4 < (float)*(int *)(lagometer + tmp_u8 * 4 + 0x404))) || (tmp_f6 = tmp_f4, tmp_b7)) &&
         (tmp_b7 = true, 0.0 < tmp_f6)) {
        trap_R_SetColor(local_30 + 1);
        tmp_f6 = tmp_f6 * (tmp_f1 / 900.0);
        if (tmp_f1 < tmp_f6) {
          tmp_f6 = tmp_f1;
        }
        trap_R_DrawStretchPic
                  ((local_3c + local_34) - tmp_f2,(local_38 + local_30[0]) - tmp_f6,0x3f800000,tmp_f6,0
                   ,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
        tmp_b7 = true;
        tmp_f3 = local_34;
      }
      tmp_u9 = tmp_u9 + 1;
      tmp_f2 = (float)(int)tmp_u9;
    } while (tmp_f2 < tmp_f3);
  }
  if (0.0 < tmp_f3) {
    tmp_f2 = 0.0;
    tmp_u9 = 0;
    do {
      while( true ) {
        tmp_u8 = ~tmp_u9 + GHIDRA_FIELD(lagometer, 1540, 4) & 0x7f;
        tmp_f4 = (float)*(int *)(lagometer + tmp_u8 * 4 + 0x404);
        tmp_f6 = (float)*(int *)(lagometer + tmp_u8 * 4 + 0x608);
        if ((0.0 < tmp_f6) && (tmp_f6 < tmp_f4)) {
          tmp_f4 = tmp_f6;
        }
        if (tmp_f4 <= 0.0) break;
        if ((lagometer[tmp_u8 * 4 + 0x204] & 1) == 0) {
          if (local_50 != 3) {
            trap_R_SetColor(colorGreen);
            local_50 = 3;
            tmp_f3 = local_34;
          }
        }
        else if (local_50 != 5) {
          trap_R_SetColor(&colorYellow);
          local_50 = 5;
          tmp_f3 = local_34;
        }
        tmp_f4 = tmp_f4 * (tmp_f1 / 900.0);
        if (tmp_f1 < tmp_f4) {
          tmp_f4 = tmp_f1;
        }
        trap_R_DrawStretchPic
                  ((tmp_f3 + local_3c) - tmp_f2,(local_38 + local_30[0]) - tmp_f4,0x3f800000,tmp_f4,0,0,
                   0,0,GHIDRA_FIELD(cgs, 67836, 4));
        tmp_f3 = local_34;
LAB_0005488a:
        tmp_u9 = tmp_u9 + 1;
        tmp_f2 = (float)(int)tmp_u9;
        if (tmp_f3 <= tmp_f2) goto LAB_00054a04;
      }
      if (0.0 <= tmp_f4) goto LAB_0005488a;
      if (local_50 != 4) {
        trap_R_SetColor(colorRed);
        tmp_f3 = local_34;
      }
      tmp_u9 = tmp_u9 + 1;
      trap_R_DrawStretchPic
                ((tmp_f3 + local_3c) - tmp_f2,(local_38 + local_30[0]) - tmp_f1,0x3f800000,tmp_f1,0,0,0,
                 0,GHIDRA_FIELD(cgs, 67836, 4));
      local_50 = 4;
      tmp_f2 = (float)(int)tmp_u9;
      tmp_f3 = local_34;
    } while (tmp_f2 < local_34);
  }
LAB_00054a04:
  trap_R_SetColor(0);
  if ((((GHIDRA_FIELD(cg_lagometer, 12, 4) & 2) != 0) && (g_unk_01047b00 != 0)) && (g_unk_01047b04 != 0)) {
    va("%d",g_unk_010ef1f0);
    CG_Text_Paint_Ext_constprop_18(0x441d8000,param_1 + 6.0,0x3e19999a,0x3e19999a,0,0x110afec);
  }
  if (GHIDRA_FIELD(cg_nopredict, 12, 4) != 0) {
    CG_DrawBigString((int)ROUND(local_3c),(int)ROUND(local_38),&g_unk_00113465,0x3f800000);
  }
  CG_DrawDisconnect(param_1);
  return (long double)param_1 + (long double)64.0;
}

void CG_DrawUpperRight(void)
{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  uint32_t tmp_u4;
  int tmp_i5;
  byte *__s;
  size_t tmp_s6;
  int tmp_i7;
  int *tmp_pi8;
  int tmp_i9;
  int tmp_i10;
  char *__s_00;
  uint8_t *tmp_pu11;
  int tmp_i12;
  long double tmp_l13;
  double tmp_d14;
  byte *local_50;
  byte *local_48;
  uint8_t *local_40;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x54b59;
  if ((GHIDRA_FIELD(cg_drawFireteamOverlay, 12, 4) == 1) && (tmp_i5 = CG_IsOnFireteam(g_unk_01047ac4), tmp_i5 != 0)) {
    local_2c = 0x40800000;
    local_28 = 0x40800000;
    local_24 = 0x42c80000;
    local_20 = 100.0;
    CG_DrawFireTeamOverlay(&local_2c);
  }
  if (((*(byte *)(g_unk_01047b00 + 0x39) & 0x40) == 0) && (*(int *)(g_unk_01047b00 + 0x158) != 3)) {
    if (GHIDRA_FIELD(cgs, 33575972, 4) != 0) {
      return;
    }
    if ((float)(g_unk_010906e0 - GHIDRA_FIELD(cgs, 33575976, 4)) < 250.0) {
      return;
    }
  }
  if (GHIDRA_FIELD(cg_drawRoundTimer, 12, 4) == 0) {
    local_50 = (byte *)0x42f00000;
  }
  else {
    local_2c = 0x3f200000;
    local_28 = 0x3f200000;
    local_24 = 0x3f19999a;
    local_20 = 1.0;
    CG_HudPlacement(2);
    if ((GHIDRA_FIELD(cgs, 27388, 4) == 5) ||
       (((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3 &&
         ((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) == 0)) ||
        ((int)GHIDRA_FIELD(cg_drawReinforcementTime, 12, 4) < 1)))) {
      local_40 = &g_unk_0011d841;
    }
    else {
      if ((float)GHIDRA_FIELD(cgs, 27396, 4) <= 0.0) {
        tmp_pu11 = &g_unk_0011d841;
      }
      else {
        tmp_pu11 = &g_unk_0011d7f6;
      }
      tmp_i5 = GHIDRA_FIELD(cg_redlimbotime, 12, 4);
      if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) != 1) {
        tmp_i5 = GHIDRA_FIELD(cg_bluelimbotime, 12, 4);
      }
      local_40 = (uint8_t *)
                 va("^F%d%s",(int)ROUND((float)(tmp_i5 - ((g_unk_010906e0 +
                                                         *(int *)(cgs + *(int *)(cgs + *(int *)(
                                                  g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) * 4 +
                                                  0x2005434)) - GHIDRA_FIELD(cgs, 28480, 4)) % tmp_i5) * 0.001 +
                                        1.0),tmp_pu11);
    }
    tmp_f2 = (float)GHIDRA_FIELD(cgs, 27396, 4) * 60.0 * 1000.0 - (float)(g_unk_010906e0 - GHIDRA_FIELD(cgs, 28480, 4));
    tmp_i5 = (int)ROUND(tmp_f2 / 1000.0);
    tmp_i10 = tmp_i5 / 0x3c;
    if (tmp_i10 < 0x3c) {
      tmp_i12 = 0;
      local_48 = (byte *)0x0;
      if (GHIDRA_FIELD(cgs, 33525356, 4) != 0) goto LAB_000551a4;
LAB_00055903:
      local_50 = (byte *)(tmp_i5 % 0x3c);
      if (GHIDRA_FIELD(cgs, 27388, 4) - 7 < 2) {
        local_50 = (byte *)va(" %s",local_40);
      }
      else if ((0.0 <= tmp_f2) || ((float)GHIDRA_FIELD(cgs, 27396, 4) <= 0.0)) {
        if ((float)GHIDRA_FIELD(cgs, 27396, 4) <= 0.0) {
          local_50 = (byte *)va("%s",local_40);
        }
        else {
          tmp_i9 = (int)local_50 / 10;
          tmp_i7 = (int)local_50 % 10;
          if (local_48 == (byte *)0x0) {
            if (tmp_i12 < 1) {
              local_50 = (byte *)va("%s^7%ld:%ld%ld",local_40,tmp_i10,tmp_i9,tmp_i7);
            }
            else {
              local_50 = (byte *)va("%s^7%ld:%ld:%ld%ld",local_40,tmp_i12,tmp_i10,tmp_i9,tmp_i7);
            }
          }
          else {
            local_50 = (byte *)va("%s^7%ldd%ld:%ld:%ld%ld",local_40,local_48,tmp_i12,tmp_i10,tmp_i9,
                                  tmp_i7);
          }
        }
        local_20 = 1.0;
      }
      else {
        local_50 = (byte *)va("^N0:00");
        tmp_d14 = sin((double)g_unk_010906e0 * 0.002);
        local_20 = ABS((float)tmp_d14);
      }
      if ((GHIDRA_FIELD(cg_spawnTimer_set, 12, 4) != -1) && (0 < (int)GHIDRA_FIELD(cg_spawnTimer_period, 12, 4))) {
LAB_000551e9:
        local_50 = (byte *)va("^1%ld %s",
                              (tmp_i5 - GHIDRA_FIELD(cg_spawnTimer_set, 12, 4)) % (int)GHIDRA_FIELD(cg_spawnTimer_period, 12, 4)
                              + GHIDRA_FIELD(cg_spawnTimer_period, 12, 4),local_50);
      }
      tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.19;
      if (local_50 != (byte *)0x0) {
        tmp_s6 = strlen((char *)local_50);
        goto LAB_0005523c;
      }
      tmp_f3 = 0.0;
    }
    else {
      tmp_i12 = tmp_i10 / 0x3c;
      if (tmp_i12 < 0x18) {
        local_48 = (byte *)0x0;
      }
      else {
        local_48 = (byte *)(tmp_i12 / 0x18);
        tmp_i12 = tmp_i12 % 0x18;
      }
      tmp_i10 = tmp_i10 % 0x3c;
      if (GHIDRA_FIELD(cgs, 33525356, 4) == 0) goto LAB_00055903;
LAB_000551a4:
      tmp_d14 = sin((double)g_unk_010906e0 * 0.002);
      local_20 = ABS((float)tmp_d14);
      if (GHIDRA_FIELD(cg_spawnTimer_set, 12, 4) != -1) {
        local_50 = (byte *)0x113469;
        if ((int)GHIDRA_FIELD(cg_spawnTimer_period, 12, 4) < 1) {
          tmp_s6 = 8;
          tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.19;
          goto LAB_0005523c;
        }
        goto LAB_000551e9;
      }
      local_50 = (byte *)0x113469;
      tmp_s6 = 8;
      tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.19;
LAB_0005523c:
      tmp_i5 = 0;
      tmp_f3 = 0.0;
      do {
        tmp_b1 = *local_50;
        if ((tmp_b1 == 0) || ((int)tmp_s6 <= tmp_i5)) break;
        if ((tmp_b1 == 0x5e) && ((local_50[1] != 0 && (local_50[1] != 0x5e)))) {
          local_50 = local_50 + 2;
        }
        else {
          local_50 = local_50 + 1;
          tmp_i5 = tmp_i5 + 1;
          tmp_f3 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f3;
        }
      } while (local_50 != (byte *)0x0);
    }
    tmp_i5 = (int)ROUND(tmp_f3 * tmp_f2);
    CG_FillRect((float)(0x278 - tmp_i5),0x42f00000,(float)(tmp_i5 + 5),0x41600000,&HUD_Background);
    CG_DrawRect_FixedBorder
              ((float)(0x278 - tmp_i5),0x42f00000,(float)(tmp_i5 + 5),0x41600000,1,&HUD_Border);
    CG_Text_Paint_Ext_constprop_18
              ((float)(0x27a - tmp_i5),0x43030000,0x3e428f5c,0x3e428f5c,0,0x1100f64);
    local_50 = (byte *)0x43080000;
  }
  if (GHIDRA_FIELD(cg_drawFPS, 12, 4) != 0) {
    tmp_i5 = trap_Milliseconds();
    tmp_i10 = tmp_i5 - previous_12101;
    previous_12101 = tmp_i5;
    CG_HudPlacement(2);
    if ((int)GHIDRA_FIELD(cg_drawFPS, 12, 4) < 4) {
      tmp_i5 = 4;
    }
    else {
      tmp_i5 = GHIDRA_FIELD(cg_drawFPS, 12, 4);
      if (500 < (int)GHIDRA_FIELD(cg_drawFPS, 12, 4)) {
        tmp_i5 = 500;
      }
    }
    if (oldSamples_12103 == tmp_i5) {
      tmp_i12 = index_12102 + 1;
      tmp_i9 = index_12102 % tmp_i5;
      tmp_pi8 = &previousTimes_12100;
      index_12102 = tmp_i12;
      oldSamples_12103 = tmp_i5;
      (&previousTimes_12100)[tmp_i9] = tmp_i10;
      if (tmp_i12 <= tmp_i5) goto LAB_00054f36;
      tmp_i10 = 0;
      do {
        tmp_i12 = *tmp_pi8;
        tmp_pi8 = tmp_pi8 + 1;
        tmp_i10 = tmp_i10 + tmp_i12;
      } while (tmp_pi8 != &previousTimes_12100 + tmp_i5);
      if (tmp_i10 == 0) {
        tmp_i10 = 1;
      }
      __s_00 = (char *)va("%i FPS",(tmp_i5 * 1000) / tmp_i10);
      tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.19;
      if ((byte *)__s_00 != (byte *)0x0) {
        tmp_s6 = strlen(__s_00);
        goto LAB_00054f53;
      }
      tmp_f3 = 0.0;
    }
    else {
      index_12102 = 1;
      previousTimes_12100 = tmp_i10;
      oldSamples_12103 = tmp_i5;
LAB_00054f36:
      __s_00 = "estimating";
      tmp_s6 = 10;
      tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.19;
LAB_00054f53:
      tmp_i5 = 0;
      tmp_f3 = 0.0;
      do {
        tmp_b1 = *__s_00;
        if ((tmp_b1 == 0) || ((int)tmp_s6 <= tmp_i5)) break;
        if ((tmp_b1 == 0x5e) && ((__s_00[1] != 0 && (__s_00[1] != 0x5e)))) {
          __s_00 = __s_00 + 2;
        }
        else {
          __s_00 = __s_00 + 1;
          tmp_i5 = tmp_i5 + 1;
          tmp_f3 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f3;
        }
      } while ((byte *)__s_00 != (byte *)0x0);
    }
    tmp_i5 = (int)ROUND(tmp_f3 * tmp_f2);
    CG_FillRect((float)(0x278 - tmp_i5),local_50,(float)(tmp_i5 + 5),0x41600000,&HUD_Background);
    CG_DrawRect_FixedBorder
              ((float)(0x278 - tmp_i5),local_50,(float)(tmp_i5 + 5),0x41600000,1,&HUD_Border);
    CG_Text_Paint_Ext_constprop_18
              ((float)(0x27a - tmp_i5),(float)local_50 + 11.0,0x3e428f5c,0x3e428f5c,0,0x1100f64);
    local_50 = (byte *)((float)local_50 + 12.0 + 4.0);
  }
  if (GHIDRA_FIELD(cg_drawPing, 12, 4) != 0) {
    tmp_i5 = *(int *)(g_unk_01047b00 + 4);
    CG_HudPlacement(2);
    if (GHIDRA_FIELD(cg_drawPing, 12, 4) == 1) {
      if (999 < tmp_i5) {
        tmp_i5 = 999;
      }
      __s = (byte *)va("Ping %d",tmp_i5);
    }
    else {
      __s = (byte *)va("Avg Ping %0.2f",(double)(((float)tmp_i5 + 0.0) * 0.5));
    }
    tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.19;
    if (__s == (byte *)0x0) {
      tmp_f3 = 0.0;
    }
    else {
      tmp_i5 = 0;
      tmp_s6 = strlen((char *)__s);
      tmp_f3 = 0.0;
      do {
        tmp_b1 = *__s;
        if ((tmp_b1 == 0) || ((int)tmp_s6 <= tmp_i5)) break;
        if ((tmp_b1 == 0x5e) && ((__s[1] != 0 && (__s[1] != 0x5e)))) {
          __s = __s + 2;
        }
        else {
          __s = __s + 1;
          tmp_i5 = tmp_i5 + 1;
          tmp_f3 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f3;
        }
      } while (__s != (byte *)0x0);
    }
    tmp_i5 = (int)ROUND(tmp_f3 * tmp_f2);
    CG_FillRect((float)(0x278 - tmp_i5),local_50,(float)(tmp_i5 + 5),0x41600000,&HUD_Background);
    CG_DrawRect_FixedBorder
              ((float)(0x278 - tmp_i5),local_50,(float)(tmp_i5 + 5),0x41600000,1,&HUD_Border);
    CG_Text_Paint_Ext_constprop_18
              ((float)(0x27a - tmp_i5),(float)local_50 + 11.0,0x3e428f5c,0x3e428f5c,0,0x1100f64);
    local_50 = (byte *)((float)local_50 + 12.0 + 4.0);
  }
  if ((GHIDRA_FIELD(cgs, 27388, 4) == 7) && (GHIDRA_FIELD(cgs, 33525356, 4) == 0)) {
    if (GHIDRA_FIELD(cg_TDMScorePos, 12, 4) == 1) {
      tmp_l13 = (long double)Nit_TDMScore_R(local_50,1);
      local_50 = (byte *)(float)tmp_l13;
    }
    else {
      Nit_TDMScore_C();
    }
  }
  if (GHIDRA_FIELD(cg_drawTime, 12, 4) != 0) {
    tmp_l13 = (long double)CG_DrawTime(local_50,1);
    local_50 = (byte *)(float)tmp_l13;
  }
  if (GHIDRA_FIELD(cg_drawspeed, 12, 4) == 0) goto LAB_00054c3c;
  local_2c = 0x3f200000;
  local_28 = 0x3f200000;
  local_24 = 0x3f19999a;
  local_20 = 1.0;
  if (resetmaxspeed != 0) {
    highestSpeed_12133 = 0.0;
    resetmaxspeed = 0;
  }
  CG_HudPlacement(2);
  tmp_i5 = trap_Milliseconds();
  if (lasttime_12135 + GHIDRA_FIELD(cg_speedinterval, 12, 4) < tmp_i5) {
    tmp_l13 = (long double)VectorLength(&g_unk_0109071c);
    speed_12134 = (float)tmp_l13;
    lasttime_12135 = tmp_i5;
    if ((long double)highestSpeed_12133 < tmp_l13) {
      highestSpeed_12133 = (float)tmp_l13;
    }
  }
  if (GHIDRA_FIELD(cg_drawspeed, 12, 4) == 1) {
    if (GHIDRA_FIELD(cg_speedunit, 12, 4) == 1) {
      local_48 = (byte *)va("%.1f KPH",(double)(speed_12134 / 15.58));
    }
    else if (GHIDRA_FIELD(cg_speedunit, 12, 4) == 2) {
      local_48 = (byte *)va("%.1f MPH",(double)(speed_12134 / 23.44));
    }
    else {
      if (GHIDRA_FIELD(cg_speedunit, 12, 4) != 0) goto LAB_00055768;
      local_48 = (byte *)va("%.1f UPS",(double)speed_12134);
    }
LAB_00055310:
    tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.19;
    if (local_48 != (byte *)0x0) {
      tmp_s6 = strlen((char *)local_48);
      goto LAB_00055782;
    }
    tmp_f3 = 0.0;
  }
  else {
    if (GHIDRA_FIELD(cg_drawspeed, 12, 4) == 2) {
      if (GHIDRA_FIELD(cg_speedunit, 12, 4) == 1) {
        local_48 = (byte *)va("%.1f KPH (%.1f MAX)",(double)(speed_12134 / 15.58),
                              (double)(highestSpeed_12133 / 15.58));
      }
      else if (GHIDRA_FIELD(cg_speedunit, 12, 4) == 2) {
        local_48 = (byte *)va("%.1f MPH (%.1f MAX)",(double)(speed_12134 / 23.44),
                              (double)(highestSpeed_12133 / 23.44));
      }
      else {
        if (GHIDRA_FIELD(cg_speedunit, 12, 4) != 0) goto LAB_00055768;
        local_48 = (byte *)va("%.1f UPS (%.1f MAX)",(double)speed_12134,(double)highestSpeed_12133);
      }
      goto LAB_00055310;
    }
LAB_00055768:
    local_48 = &g_unk_0011d841;
    tmp_s6 = 0;
    tmp_f2 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.19;
LAB_00055782:
    tmp_i5 = 0;
    tmp_f3 = 0.0;
    do {
      tmp_b1 = *local_48;
      if ((tmp_b1 == 0) || ((int)tmp_s6 <= tmp_i5)) break;
      if ((tmp_b1 == 0x5e) && ((local_48[1] != 0 && (local_48[1] != 0x5e)))) {
        local_48 = local_48 + 2;
      }
      else {
        local_48 = local_48 + 1;
        tmp_i5 = tmp_i5 + 1;
        tmp_f3 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f3;
      }
    } while (local_48 != (byte *)0x0);
  }
  tmp_i5 = (int)ROUND(tmp_f3 * tmp_f2);
  CG_FillRect((float)(0x278 - tmp_i5),local_50,(float)(tmp_i5 + 5),0x41600000,&HUD_Background);
  CG_DrawRect_FixedBorder
            ((float)(0x278 - tmp_i5),local_50,(float)(tmp_i5 + 5),0x41600000,1,&HUD_Border);
  CG_Text_Paint_Ext_constprop_18
            ((float)(0x27a - tmp_i5),(float)local_50 + 11.0,0x3e428f5c,0x3e428f5c,0,0x1100f64);
  local_50 = (byte *)((float)local_50 + 12.0 + 4.0);
LAB_00054c3c:
  tmp_l13 = (long double)CG_DrawLagometer(local_50,1);
  if (GHIDRA_FIELD(cg_drawSnapshot, 12, 4) != 0) {
    tmp_u4 = va("time:%i snap:%i cmd:%i",*(uint32_t *)(g_unk_01047b00 + 8),g_unk_01047af8,GHIDRA_FIELD(cgs, 27376, 4)
              );
    tmp_i5 = CG_DrawStrlen(tmp_u4);
    CG_DrawBigString(tmp_i5 * -0x10 + 0x27a,(int)ROUND((float)tmp_l13 + 2.0),tmp_u4,0x3f800000);
  }
  if (GHIDRA_FIELD(cg_drawHUDStats, 12, 4) != 0) {
    Nit_LiveStats();
  }
  nitrox_DrawSpecialPrint();
  return;
}

void CG_DrawLivesLeft(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  uint tmp_u4;
  uint *tmp_pu5;
  uint *tmp_pu6;
  char *tmp_pc7;
  uint *tmp_pu8;
  char *tmp_pc9;
  int local_30;
  uint32_t local_2c;
  uint32_t uStack_14;
  
  uStack_14 = 0x55e99;
  if ((GHIDRA_FIELD(cg_gameType, 12, 4) != 5) && (-1 < *(int *)(g_unk_01047b00 + 0x160))) {
    tmp_pu8 = &local_2c;
    CG_HudPlacement(1);
    tmp_u1 = GHIDRA_FIELD(cgs, 67852, 4);
    if (*(int *)(g_unk_01047b00 + 0x158) != 2) {
      tmp_u1 = GHIDRA_FIELD(cgs, 67848, 4);
    }
    CG_DrawPic(0x40800000,0x43b40000,0x42400000,0x41c00000,tmp_u1);
    tmp_i2 = 999;
    if (*(int *)(g_unk_01047b00 + 0x160) < 1000) {
      tmp_i2 = *(int *)(g_unk_01047b00 + 0x160);
    }
    if (tmp_i2 < -99) {
      tmp_i2 = -99;
    }
    Com_sprintf(tmp_pu8,0x10,"%i",tmp_i2);
    tmp_pu6 = tmp_pu8;
    do {
      tmp_pu5 = tmp_pu6;
      tmp_u3 = *tmp_pu5 + 0xfefefeff & ~*tmp_pu5;
      tmp_u4 = tmp_u3 & 0x80808080;
      tmp_pu6 = tmp_pu5 + 1;
    } while (tmp_u4 == 0);
    if ((tmp_u3 & 0x8080) == 0) {
      tmp_pu6 = (uint *)((int)tmp_pu5 + 6);
      tmp_u4 = tmp_u4 >> 0x10;
    }
    tmp_pc7 = (char *)((int)tmp_pu6 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)tmp_pu8));
    tmp_pc9 = (char *)0x3;
    if ((int)tmp_pc7 < 4) {
      tmp_pc9 = tmp_pc7;
    }
    if ((tmp_pc9 != (char *)0x0) && (local_30 = 0x2c, (char)local_2c != '\0')) {
      do {
        if ((char)local_2c == '-') {
          tmp_i2 = 10;
        }
        else {
          tmp_i2 = (char)local_2c + -0x30;
        }
        tmp_pu8 = (uint *)((int)tmp_pu8 + 1);
        tmp_pc9 = tmp_pc9 + -1;
        CG_DrawPic((float)local_30,0x43b40000,0x41600000,0x41a00000,
                   *(uint32_t *)(cgs + tmp_i2 * 4 + 0x10c54));
        GHIDRA_FIELD(local_2c, 0, 1) = *(char *)tmp_pu8;
        local_30 = local_30 + 0xe;
      } while (((char)local_2c != '\0') && (tmp_pc9 != (char *)0x0));
    }
  }
  return;
}

void CG_DrawCrosshairNames(void)
{
  float tmp_f1;
  byte tmp_b2;
  float tmp_f3;
  bool tmp_b4;
  byte *__s;
  size_t tmp_s5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint32_t tmp_u8;
  char *tmp_pc9;
  uint tmp_u10;
  int tmp_i11;
  int tmp_i12;
  long double tmp_l13;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  uint32_t local_84;
  uint32_t local_80;
  uint32_t local_7c;
  float local_78;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  float local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  uint32_t local_50;
  uint32_t local_4c;
  float local_48 [10];
  int local_20;
  uint32_t uStack_14;
  
  tmp_u7 = GHIDRA_FIELD(cg_drawCrosshairNames, 12, 4);
  uStack_14 = 0x56a79;
  local_84 = 0x3f800000;
  local_80 = 0x3f800000;
  local_7c = 0x3f800000;
  local_78 = 0.3;
  local_74 = 0x3f800000;
  local_70 = 0x3f800000;
  local_6c = 0x3f800000;
  local_68 = 0.125;
  local_64 = 0x3f800000;
  local_60 = 0x3f800000;
  local_5c = 0x3f800000;
  local_58 = 0x3f000000;
  if ((int)GHIDRA_FIELD(cg_drawCrosshair, 12, 4) < 0) {
    return;
  }
  if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
    return;
  }
  CG_HudPlacement(0);
  if (-1 < g_unk_01093560) {
    CG_FadeColor(g_unk_01093564,1000);
    __s = (byte *)va("%s^7\'s landmine",g_unk_01093560 * 0x1a4 + 0x10f9274);
    tmp_f1 = (float)GHIDRA_FIELD(cgs, 131468, 4) * 0.18;
    if (__s == (byte *)0x0) {
      tmp_f3 = 0.0;
    }
    else {
      tmp_i12 = 0;
      tmp_s5 = strlen((char *)__s);
      tmp_f3 = 0.0;
      do {
        tmp_b2 = *__s;
        if ((tmp_b2 == 0) || ((int)tmp_s5 <= tmp_i12)) break;
        if ((tmp_b2 == 0x5e) && ((__s[1] != 0 && (__s[1] != 0x5e)))) {
          __s = __s + 2;
        }
        else {
          __s = __s + 1;
          tmp_i12 = tmp_i12 + 1;
          tmp_f3 = (float)*(int *)(cgs + (uint)tmp_b2 * 0x50 + 0x1b19c) + tmp_f3;
        }
      } while (__s != (byte *)0x0);
    }
    CG_Text_Paint_Ext_constprop_18
              (320.0 - (float)(int)ROUND(tmp_f3 * tmp_f1) * 0.5,0x43360000,0x3e3851ec,0x3e3851ec,7,
               0x110afec);
    g_unk_01093560 = 0xffffffff;
    return;
  }
  local_a0 = g_unk_010918c0;
  g_unk_010aabe4 = 0;
  local_9c = g_unk_010918c4;
  local_98 = g_unk_010918c8;
  local_94 = g_unk_010918cc * 8192.0 + g_unk_010918c0;
  local_90 = g_unk_010918d0 * 8192.0 + g_unk_010918c4;
  local_8c = g_unk_010918d4 * 8192.0 + g_unk_010918c8;
  CG_Trace(&local_54,&local_a0,0,0,&local_94,*(uint32_t *)(g_unk_01047b00 + 0xcc),0x2000101);
  tmp_l13 = (long double)VectorDistance(&local_a0,local_48);
  if (local_20 < 0x40) {
    g_unk_010aabd8 = 0;
    g_unk_01093558 = local_20;
    g_unk_010aabdc = g_unk_010906e0;
    g_unk_0109355c = g_unk_010906e0;
    if (local_20 != *(int *)(g_unk_01047b00 + 0x5cc)) {
      g_unk_010aac04 = local_20;
    }
    if (((cg_entities[local_20 * 0xaf8 + 0xe4] & 0x80) != 0) &&
       (*(int *)(cgs + local_20 * 0x1a4 + 0x9494) == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494)))
    {
      g_unk_010aabe4 = 1;
    }
  }
  else {
    if ((cg_entities[local_20 * 0xaf8 + 9] & 0x80) != 0) {
      local_20 = *(int *)(cg_entities + local_20 * 0xaf8 + 0xab4);
    }
    if (*(int *)(cg_entities + local_20 * 0xaf8 + 4) == 4) {
      if (*(int *)(cg_entities + local_20 * 0xaf8 + 0x10c) != 0) goto LAB_00057144;
    }
    else if (*(int *)(cg_entities + local_20 * 0xaf8 + 4) == 0x21) {
LAB_00057144:
      g_unk_0109355c = g_unk_010906e0;
      g_unk_01093558 = local_20;
      g_unk_010aac04 = local_20;
    }
    g_unk_010aabd8 = 1;
  }
  if (g_unk_010906f4 != 0) {
    return;
  }
  tmp_i12 = CG_FadeColor(g_unk_0109355c,1000);
  trap_R_SetColor(0);
  if (tmp_i12 == 0) {
    return;
  }
  if (g_unk_01093558 < 0x41) {
    tmp_i6 = *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4;
    if (*(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x9494) == *(int *)(cgs + tmp_i6 + 0x9494)) {
      tmp_f1 = 1.0;
      tmp_i6 = 0;
    }
    else {
      if ((*(uint *)(cg_entities + g_unk_01093558 * 0xaf8 + 0xe4) & 0x80) == 0) {
        return;
      }
      if (*(int *)(cgs + tmp_i6 + 0x9494) == 3) {
        return;
      }
      if (((cgs[tmp_i6 + 0x9598] & 0x10) != 0) &&
         ((*(int *)(cgs + tmp_i6 + 0x94b8) == 3 || ((cgs[0x2038628] & 2) != 0)))) {
        CG_Text_Paint_Centred_Ext_constprop_15
                  (0x43a00000,0x43360000,0x3e4ccccd,0x3e4ccccd,0x110afec);
        return;
      }
      if ((float)tmp_l13 <= 512.0) {
        g_unk_0109355c = 0;
        return;
      }
      if (GHIDRA_FIELD(cg_drawCrosshairNames, 12, 4) == 0) {
        return;
      }
      tmp_u10 = (int)*(uint *)(cg_entities + g_unk_01093558 * 0xaf8 + 0xe4) >> 8 & 7;
      va(&g_unk_00116f17,g_unk_01093558 * 0x1a4 + 0x10f937c);
      tmp_i6 = CG_Text_Width_Ext_constprop_17(0x3e4ccccd);
      if (((tmp_u7 & 2) == 0) || (*(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x955c) < 1)) {
        tmp_i11 = SkillNumForClass(tmp_u10);
        tmp_u8 = *(uint32_t *)(cgs + tmp_i11 * 4 + 0x11084);
      }
      else {
        tmp_i11 = SkillNumForClass(tmp_u10);
        CG_DrawPic(304.0 - (float)tmp_i6 * 0.5,0x432a0000,0x41600000,0x41600000,
                   *(uint32_t *)(cgs + tmp_i11 * 4 + 0x11084));
        tmp_u8 = *(uint32_t *)
                 (rankicons +
                 ((uint)(*(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x9494) != 1) +
                 *(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x955c) * 2) * 0x20);
      }
      CG_DrawPic(320.0 - (float)tmp_i6 * 0.5,0x432a0000,0x41600000,0x41600000,tmp_u8);
      CG_Text_Paint_Centred_Ext_constprop_15(0x43a80000,0x43360000,0x3e4ccccd,0x3e4ccccd,0x110afec);
      if (g_unk_01093558 == *(int *)(g_unk_01047b00 + 0x5cc)) {
        tmp_i6 = *(int *)(g_unk_01047b00 + 0x5d0);
        tmp_f1 = 100.0;
      }
      else {
        tmp_f1 = 100.0;
        tmp_i6 = *(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x94a8);
      }
    }
    if (GHIDRA_FIELD(cg_drawCrosshairNames, 12, 4) == 0) {
      return;
    }
    if ((*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) == 3) ||
       (tmp_b4 = false,
       *(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) ==
       *(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x9494))) {
      va(&g_unk_00116f17,g_unk_01093558 * 0x1a4 + 0x10f9274);
      tmp_i6 = CG_Text_Width_Ext_constprop_17(0x3e4ccccd);
      if (((tmp_u7 & 2) == 0) || (*(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x94c0) < 1)) {
        tmp_i11 = SkillNumForClass(*(uint32_t *)(cgs + g_unk_01093558 * 0x1a4 + 0x94b8));
        tmp_u7 = *(uint32_t *)(cgs + tmp_i11 * 4 + 0x11084);
      }
      else {
        tmp_i11 = SkillNumForClass(*(uint32_t *)(cgs + g_unk_01093558 * 0x1a4 + 0x94b8));
        CG_DrawPic(304.0 - (float)tmp_i6 * 0.5,0x432a0000,0x41600000,0x41600000,
                   *(uint32_t *)(cgs + tmp_i11 * 4 + 0x11084));
        tmp_u7 = *(uint32_t *)
                 (rankicons +
                 ((uint)(*(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x9494) == 1) +
                 *(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x94c0) * 2) * 0x20);
      }
      CG_DrawPic(320.0 - (float)tmp_i6 * 0.5,0x432a0000,0x41600000,0x41600000,tmp_u7);
      CG_Text_Paint_Centred_Ext_constprop_15(0x43a80000,0x43360000,0x3e4ccccd,0x3e4ccccd,0x110afec);
      if (g_unk_01093558 == *(int *)(g_unk_01047b00 + 0x5cc)) {
        tmp_i6 = *(int *)(g_unk_01047b00 + 0x5d0);
      }
      else {
        tmp_i6 = *(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x94a8);
      }
      tmp_i11 = CG_CrosshairClientMaxHealth();
      tmp_b4 = false;
      tmp_f1 = (float)tmp_i11;
    }
    goto LAB_00056e6c;
  }
  if (GHIDRA_FIELD(cg_drawCrosshairNames, 12, 4) == 0) {
    return;
  }
  if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) == 3) {
    return;
  }
  tmp_i6 = g_unk_01093558 * 0xaf8;
  if (*(int *)(cg_entities + tmp_i6 + 4) == 4) {
    if (*(int *)(cg_entities + tmp_i6 + 0x10c) == 0) goto LAB_00056d44;
    tmp_i6 = *(int *)(cg_entities + tmp_i6 + 0x9c);
    tmp_u7 = va("%i",g_unk_01093558);
    tmp_u8 = CG_ConfigString(0x1a);
    tmp_pc9 = (char *)Info_ValueForKey(tmp_u8,tmp_u7);
    if (*tmp_pc9 == '\0') {
      return;
    }
    tmp_b4 = false;
    CG_Text_Paint_Centred_Ext_constprop_15(0x43a00000,0x43360000,0x3e4ccccd,0x3e4ccccd,0x110afec);
    tmp_i11 = 0xff;
  }
  else {
    if (*(int *)(cg_entities + tmp_i6 + 4) == 0x21) {
      tmp_u7 = va("%i",g_unk_01093558);
      tmp_u8 = CG_ConfigString(0x1b);
      tmp_pc9 = (char *)Info_ValueForKey(tmp_u8,tmp_u7);
      if (*tmp_pc9 == '\0') {
        return;
      }
      CG_Text_Paint_Centred_Ext_constprop_15(0x43a00000,0x43360000,0x3e4ccccd,0x3e4ccccd,0x110afec);
      return;
    }
LAB_00056d44:
    if (g_unk_010aabd0 < 0) {
      return;
    }
    tmp_l13 = (long double)Distance(&g_unk_01090710,g_unk_01093558 * 0xaf8 + 0x31345d4);
    if ((long double)4096.0 < tmp_l13) {
      return;
    }
    if (*(int *)(cg_entities + g_unk_01093558 * 0xaf8 + 0x108) % 4 ==
        *(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494)) {
      va("%s^7\'s dynamite",g_unk_010aabd0 * 0x1a4 + 0x10f9274);
      CG_Text_Paint_Centred_Ext_constprop_15(0x43a00000,0x43360000,0x3e3851ec,0x3e3851ec,0x110afec);
    }
    else {
      CG_Text_Paint_Centred_Ext_constprop_15(0x43a00000,0x43360000,0x3e3851ec,0x3e3851ec,0x110afec);
    }
    tmp_i6 = g_unk_01093558 * 0xaf8;
    if (3 < *(int *)(cg_entities + tmp_i6 + 0x108)) {
      return;
    }
    tmp_i11 = *(int *)(cg_entities + tmp_i6 + 0x58);
    tmp_b4 = true;
    tmp_i6 = (*(int *)(cg_entities + tmp_i6 + 0x10c) + tmp_i11) - g_unk_010906e0;
    g_unk_010aabd0 = -1;
  }
  if (GHIDRA_FIELD(cg_drawCrosshairNames, 12, 4) == 0) {
    return;
  }
  tmp_f1 = (float)tmp_i11;
LAB_00056e6c:
  local_90 = (float)tmp_i6 / tmp_f1;
  if (local_90 <= 1.0) {
    if (local_90 < 0.0) {
      local_88 = 0.25;
      local_90 = 0.0;
    }
    else {
      local_88 = local_90 * 0.5 + 0.25;
    }
  }
  else {
    local_88 = 0.75;
    local_90 = 1.0;
  }
  local_94 = 1.0;
  local_88 = local_88 * *(float *)(tmp_i12 + 0xc);
  local_54 = 0x3f800000;
  local_50 = 0x3f800000;
  local_4c = 0x3f800000;
  local_48[0] = *(float *)(tmp_i12 + 0xc) * 0.25;
  local_8c = local_90;
  if (tmp_b4) {
    local_78 = local_78 * *(float *)(tmp_i12 + 0xc);
    local_68 = local_68 * *(float *)(tmp_i12 + 0xc);
    CG_FilledBar(0x43910000,0x43410000,0x42700000,0x40e00000,&local_84,0,&local_74,local_90,0x10);
  }
  else {
    CG_FilledBar(0x43870000,0x433e0000,0x42c80000,0x41200000,&local_94,0,&local_54,local_90,0x10);
  }
  trap_R_SetColor(0);
  return;
}

void CG_DrawTimedMenus(void)
{
  if ((g_unk_010aac1c != 0) && (0x9c4 < g_unk_010906e0 - g_unk_010aac1c)) {
    Menus_CloseByName("voiceMenu");
    trap_Cvar_Set("cl_conXOffset",&g_unk_0011e957);
    g_unk_010aac1c = 0;
    return;
  }
  return;
}

void CG_DrawCompassIcon(float param_1,float param_2,float param_3,float param_4,float *param_5,
                       float *param_6,uint32_t param_7,float param_8,int param_9)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  long double tmp_l4;
  long double tmp_l5;
  double tmp_d6;
  double local_3c;
  double local_34 [2];
  float local_24;
  float local_20;
  float local_1c;
  uint8_t local_18 [4];
  float local_14;
  
  local_24 = *param_5 - *param_6;
  local_20 = param_5[1] - param_6[1];
  local_1c = param_5[2] - param_6[2];
  tmp_l4 = (long double)VectorLength(&local_24);
  VectorNormalize(&local_24);
  vectoangles(&local_24,local_18);
  if (((local_24 == 0.0) && (local_20 == 0.0)) && (local_1c == 0.0)) {
    return;
  }
  CG_HudPlacement(1);
  tmp_l5 = (long double)AngleSubtract(g_unk_010907b0,local_14);
  local_14 = (float)tmp_l5;
  param_3 = param_3 * 0.5;
  param_4 = param_4 * 0.5;
  tmp_f1 = param_4 * param_4 + param_3 * param_3;
  tmp_f2 = SQRT(tmp_f1);
  if (NAN(tmp_f2)) {
    tmp_d6 = sqrt((double)tmp_f1);
    tmp_f2 = (float)tmp_d6;
    tmp_l5 = (long double)(float)tmp_l5;
  }
  sincos((double)(float)(((tmp_l5 + (long double)180.0) / (long double)360.0 - (long double)0.25) *
                        (long double)6.2831855),local_34,&local_3c);
  tmp_f1 = (tmp_f2 / 3.0 + tmp_f2 / 3.0) * 0.9;
  tmp_f2 = (float)tmp_l4 / (param_8 * 2000.0);
  if (tmp_f2 <= 1.0) {
    tmp_f2 = 1.0 - tmp_f2;
  }
  else {
    tmp_f2 = 0.0;
  }
  tmp_f3 = (float)param_9 * tmp_f2 + 8.0;
  tmp_f2 = ((float)param_9 * tmp_f2 + 4.0) * 0.5;
  CG_DrawPic(((float)local_3c * tmp_f1 + param_3 + param_1) - tmp_f2,
             (tmp_f1 * (float)local_34[0] + param_4 + param_2) - tmp_f2,tmp_f3,tmp_f3,param_7);
  return;
}

void CG_DrawSkillLevels(void)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  byte tmp_b5;
  byte tmp_b6;
  int tmp_i7;
  uint32_t tmp_u8;
  float tmp_f9;
  float tmp_f10;
  int tmp_i11;
  size_t tmp_s12;
  char *tmp_pc13;
  int tmp_i14;
  int tmp_i15;
  float local_a4;
  byte *local_a0;
  int local_9c;
  int local_74;
  int local_70;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  uint8_t local_3c [16];
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x57f09;
  tmp_i7 = *(int *)(g_unk_01047b00 + 0xcc);
  CG_ColorForHealth(local_3c);
  if (GHIDRA_FIELD(cgs, 27388, 4) != 5) {
    CG_HudPlacement(1);
    if (g_unk_010906e0 - g_unk_01047acc < 1000) {
      tmp_pc13 = "^3";
    }
    else {
      tmp_pc13 = "^7";
    }
    va("%sXP %i^7",tmp_pc13,*(int *)(g_unk_01047b00 + 0x108) * 0x8000 + *(int *)(g_unk_01047b00 + 0x11c))
    ;
    CG_Text_Paint_Ext_constprop_18(0x42960000,0x43ed0000,0x3e4ccccd,0x3e4ccccd,3,0x1100f64);
    local_74 = 2;
    tmp_i11 = tmp_i7 * 0x1a4;
    local_70 = 0x184;
    do {
      if (local_74 == 0) {
        tmp_i14 = BG_ClassSkillForClass(*(uint32_t *)(cgs + tmp_i11 + 0x94b8));
      }
      else if (local_74 == 2) {
        if (pm == (int *)0x0) {
          tmp_i14 = 4;
        }
        else if ((*(int *)(*pm + 0x140) != 0) || (tmp_i14 = 4, (*(byte *)(*pm + 0x69) & 0x80) != 0))
        {
          tmp_i14 = 5 - (uint)(*(int *)(cgs + tmp_i11 + 0x94b8) == 0);
        }
      }
      else {
        tmp_i14 = 0;
      }
      trap_R_SetColor(&colorBlack);
      CG_DrawPic(0x42040000,(float)local_70,0x41500000,0x41500000,
                 *(uint32_t *)(cgs + (tmp_i14 + 0x441c) * 4 + 0x14));
      trap_R_SetColor(0);
      CG_DrawPic(0x42000000,(float)(local_70 + -1),0x41500000,0x41500000,
                 *(uint32_t *)(cgs + (tmp_i14 + 0x441c) * 4 + 0x14));
      local_a0 = (byte *)va("^7%d",*(uint32_t *)
                                    (cgs + (tmp_i14 + 0x2534 + tmp_i7 * 0x69) * 4 + 0x14));
      tmp_f9 = (float)GHIDRA_FIELD(cgs, 90372, 4) * 0.2;
      if (local_a0 != (byte *)0x0) {
        trap_R_SetColor(&colorWhite);
        local_2c = colorWhite;
        local_28 = g_unk_0014a334;
        local_24 = g_unk_0014a338;
        local_20 = g_unk_0014a33c;
        tmp_s12 = strlen((char *)local_a0);
        local_9c = 0;
        local_a4 = 35.0;
        do {
          while( true ) {
            tmp_b5 = *local_a0;
            if ((tmp_b5 == 0) || ((int)tmp_s12 <= local_9c)) goto LAB_00058500;
            if (tmp_b5 == 0x5e) break;
LAB_000581b8:
            tmp_i15 = (uint)tmp_b5 * 0x50;
            tmp_i14 = *(int *)(cgs + tmp_i15 + 0x11108);
            g_unk_0014a3bc = local_20;
            trap_R_SetColor(&colorBlack);
            tmp_u8 = *(uint32_t *)(cgs + tmp_i15 + 0x11130);
            tmp_u1 = *(uint32_t *)(cgs + tmp_i15 + 0x1112c);
            tmp_u2 = *(uint32_t *)(cgs + tmp_i15 + 0x11128);
            tmp_u3 = *(uint32_t *)(cgs + tmp_i15 + 0x11124);
            tmp_u4 = *(uint32_t *)(cgs + tmp_i15 + 0x11120);
            tmp_f10 = (float)(local_74 * -0x17 + 0x1c9) - (float)tmp_i14 * tmp_f9;
            local_5c = (float)*(int *)(cgs + tmp_i15 + 0x11110) * tmp_f9 + local_a4 + 1.0;
            local_58 = tmp_f10 + 1.0;
            local_54 = (float)*(int *)(cgs + tmp_i15 + 0x11118) * tmp_f9;
            local_50 = tmp_f9 * (float)*(int *)(cgs + tmp_i15 + 0x1111c);
            CG_AdjustFrom640(&local_5c,&local_58,&local_54,&local_50);
            trap_R_DrawStretchPic(local_5c,local_58,local_54,local_50,tmp_u4,tmp_u3,tmp_u2,tmp_u1,tmp_u8)
            ;
            g_unk_0014a3bc = 0x3f800000;
            trap_R_SetColor(&local_2c);
            tmp_u8 = *(uint32_t *)(cgs + tmp_i15 + 0x11130);
            tmp_u1 = *(uint32_t *)(cgs + tmp_i15 + 0x1112c);
            tmp_u2 = *(uint32_t *)(cgs + tmp_i15 + 0x11128);
            tmp_u3 = *(uint32_t *)(cgs + tmp_i15 + 0x11124);
            tmp_u4 = *(uint32_t *)(cgs + tmp_i15 + 0x11120);
            local_4c = (float)*(int *)(cgs + tmp_i15 + 0x11110) * tmp_f9 + local_a4;
            local_44 = (float)*(int *)(cgs + tmp_i15 + 0x11118) * tmp_f9;
            local_40 = tmp_f9 * (float)*(int *)(cgs + tmp_i15 + 0x1111c);
            local_48 = tmp_f10;
            CG_AdjustFrom640(&local_4c,&local_48,&local_44,&local_40);
            trap_R_DrawStretchPic(local_4c,local_48,local_44,local_40,tmp_u4,tmp_u3,tmp_u2,tmp_u1,tmp_u8)
            ;
            local_a0 = local_a0 + 1;
            local_9c = local_9c + 1;
            local_a4 = (float)*(int *)(cgs + tmp_i15 + 0x11114) * tmp_f9 + 0.0 + local_a4;
            if (local_a0 == (byte *)0x0) goto LAB_00058500;
          }
          tmp_b6 = local_a0[1];
          if ((tmp_b6 == 0) || (tmp_b6 == 0x5e)) goto LAB_000581b8;
          if (tmp_b6 == 0x2a) {
            local_2c = colorWhite;
            local_28 = g_unk_0014a334;
            local_24 = g_unk_0014a338;
          }
          else {
            tmp_i14 = ((int)(char)tmp_b6 - 0x30U & 0x1f) * 0x10;
            local_2c = *(uint32_t *)(g_color_table + tmp_i14);
            local_28 = *(uint32_t *)(g_color_table + tmp_i14 + 4);
            local_24 = *(uint32_t *)(g_color_table + tmp_i14 + 8);
          }
          local_20 = g_unk_0014a33c;
          trap_R_SetColor(&local_2c);
          local_a0 = local_a0 + 2;
        } while (local_a0 != (byte *)0x0);
LAB_00058500:
        trap_R_SetColor(0);
      }
      local_74 = local_74 + -1;
      local_70 = local_70 + 0x18;
    } while (local_74 != -1);
    va("%i^7HP",*(uint32_t *)(g_unk_01047b00 + 0xfc));
    CG_Text_Paint_Ext_constprop_18(0x42080000,0x43ed0000,0x3e4ccccd,0x3e4ccccd,3,0x1100f64);
  }
  return;
}

void CG_DrawActivePowerups(void)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  byte tmp_b4;
  
  CG_HudPlacement(2);
  tmp_i2 = g_unk_01047b00;
  if ((*(int *)(g_unk_01047b00 + 400) == 0) && (*(int *)(g_unk_01047b00 + 0x194) == 0)) {
    if (*(int *)(g_unk_01047b00 + 0x198) != 0) {
      tmp_u3 = GHIDRA_FIELD(cgs, 68900, 4);
      if (*(int *)(g_unk_01047b00 + 0x158) == 1) {
        tmp_u3 = GHIDRA_FIELD(cgs, 68896, 4);
      }
      CG_DrawPic(0x44110000,0x43c30000,0x41700000,0x41700000,tmp_u3);
      tmp_b4 = *(int *)(tmp_i2 + 0x19c) != 0;
      if (*(int *)(tmp_i2 + 0x1a0) != 0) {
        tmp_b4 = tmp_b4 | 2;
      }
      if (*(int *)(tmp_i2 + 0x1a4) != 0) {
        tmp_b4 = tmp_b4 | 4;
      }
      tmp_u3 = BG_ShortClassnameForNumber(tmp_b4);
      tmp_u3 = va("%s",tmp_u3);
      CG_DrawStringExt(0x242,0x186,tmp_u3,&colorWhite,0,1,4,0xc,0);
      tmp_b4 = *(byte *)(g_unk_01047b00 + 0x100);
      goto joined_r0x000586d1;
    }
  }
  else {
    trap_R_SetColor(0);
    CG_DrawPic(0x44160000,0x43c30000,0x41700000,0x41700000,GHIDRA_FIELD(cgs, 67992, 4));
  }
  tmp_b4 = *(byte *)(g_unk_01047b00 + 0x100);
joined_r0x000586d1:
  if ((tmp_b4 & 0x40) == 0) {
    tmp_b4 = *(byte *)(tmp_i2 + 0x95);
  }
  else {
    CG_DrawPic(0x440c0000,0x43cc8000,0x41700000,0x41700000,GHIDRA_FIELD(cgs, 131896, 4));
    tmp_b4 = *(byte *)(tmp_i2 + 0x95);
  }
  if ((tmp_b4 & 0x10) == 0) {
    CG_DrawPic(0x44110000,0x43cd0000,0x41700000,0x41700000,GHIDRA_FIELD(cgs, 131888, 4));
    tmp_i1 = *(int *)(tmp_i2 + 0x180);
  }
  else {
    tmp_i1 = *(int *)(tmp_i2 + 0x180);
  }
  tmp_u3 = GHIDRA_FIELD(cgs, 67968, 4);
  if ((tmp_i1 == 0) && (tmp_u3 = GHIDRA_FIELD(cgs, 131884, 4), *(int *)(tmp_i2 + 0x184) == 0)) {
    return;
  }
  CG_DrawPic(0x44160000,0x43cc8000,0x41700000,0x41700000,tmp_u3);
  return;
}

void CG_DrawDemoRecording(void)
{
  if (((GHIDRA_FIELD(cl_demorecording, 12, 4) != 0) || (GHIDRA_FIELD(cl_waverecording, 12, 4) != 0)) &&
     (GHIDRA_FIELD(cg_recording_statusline, 12, 4) != 0)) {
    CG_DrawDemoRecording_part_3();
    return;
  }
  return;
}

void CG_DrawOnScreenNames(void)
{
  int *tmp_pi1;
  float tmp_f2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  byte tmp_b7;
  byte tmp_b8;
  uint32_t tmp_u9;
  float tmp_f10;
  float tmp_f11;
  int tmp_i12;
  size_t tmp_s13;
  uint tmp_u14;
  uint32_t *tmp_pu15;
  int tmp_i16;
  float local_f0;
  byte *local_ec;
  int local_e8;
  uint8_t *local_c8;
  int local_bc;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90 [12];
  uint32_t local_60;
  uint32_t local_5c;
  float local_58;
  uint8_t local_54 [8];
  float local_4c;
  uint32_t uStack_14;
  
  uStack_14 = 0x58af9;
  local_90[7] = 1.0;
  local_90[8] = 1.0;
  local_90[9] = 1.0;
  local_90[10] = 1.0;
  local_90[1] = -1.0;
  local_90[2] = -1.0;
  local_90[3] = -1.0;
  local_90[4] = 1.0;
  local_90[5] = 1.0;
  local_90[6] = 1.0;
  CG_HudPlacement(0);
  if ((0 < g_unk_010ee740) && (g_unk_010ee4a8 != 0)) {
    local_bc = 0;
    local_c8 = &g_unk_010ee494;
    do {
      CG_Trace(local_54,&g_unk_010918c0,local_90 + 1,local_90 + 4,local_c8,0xffffffff,1);
      tmp_i12 = g_unk_010906e0;
      if (local_4c < 1.0) {
        *(int *)(local_c8 + 0x10) = g_unk_010906e0;
        tmp_i12 = tmp_i12 - *(int *)(local_c8 + 0xc);
        if (tmp_i12 == 0) goto LAB_00058cb0;
        tmp_f2 = (float)tmp_i12;
        if (tmp_f2 <= 250.0) {
          local_90[10] = 1.0 - tmp_f2 / 250.0;
          tmp_f2 = *(float *)(local_c8 + -8);
          if (tmp_f2 < local_90[10]) goto LAB_000592fa;
          goto LAB_00058cb0;
        }
        local_90[10] = 0.0;
        tmp_f2 = *(float *)(local_c8 + -8);
        if (tmp_f2 < 0.0) {
LAB_000592fa:
          local_90[10] = tmp_f2;
          goto LAB_00058cb0;
        }
LAB_00059292:
        *(float *)(local_c8 + -8) = local_90[10];
        if (0.0 < local_90[10]) goto LAB_00058ccc;
      }
      else {
        *(int *)(local_c8 + 0xc) = g_unk_010906e0;
        tmp_i12 = tmp_i12 - *(int *)(local_c8 + 0x10);
        if (tmp_i12 != 0) {
          local_90[10] = (float)tmp_i12;
          if (250.0 < local_90[10]) {
            local_90[10] = 1.0;
          }
          else {
            local_90[10] = local_90[10] / 250.0;
          }
          if (local_90[10] < *(float *)(local_c8 + -8)) {
            local_90[10] = *(float *)(local_c8 + -8);
          }
        }
LAB_00058cb0:
        if (local_90[10] <= 1.0) goto LAB_00059292;
        local_90[10] = 1.0;
        *(uint32_t *)(local_c8 + -8) = 0x3f800000;
LAB_00058ccc:
        tmp_f2 = *(float *)(local_c8 + -0x10);
        local_ec = *(byte **)(local_c8 + -4);
        local_f0 = *(float *)(local_c8 + -0x14);
        tmp_f10 = (float)GHIDRA_FIELD(cgs, 90372, 4) * *(float *)(local_c8 + -0xc);
        if (local_ec != (byte *)0x0) {
          trap_R_SetColor(local_90 + 7);
          local_90[0xb] = local_90[7];
          local_60 = local_90[8];
          local_5c = local_90[9];
          local_58 = local_90[10];
          tmp_s13 = strlen((char *)local_ec);
          local_e8 = 0;
          do {
            while( true ) {
              tmp_b7 = *local_ec;
              if ((tmp_b7 == 0) || ((int)tmp_s13 <= local_e8)) goto LAB_000590b0;
              if (tmp_b7 == 0x5e) break;
LAB_00058d60:
              tmp_i16 = (uint)tmp_b7 * 0x50;
              tmp_i12 = *(int *)(cgs + tmp_i16 + 0x11108);
              g_unk_0014a3bc = local_58;
              trap_R_SetColor(&colorBlack);
              tmp_u9 = *(uint32_t *)(cgs + tmp_i16 + 0x11130);
              tmp_u3 = *(uint32_t *)(cgs + tmp_i16 + 0x1112c);
              tmp_u4 = *(uint32_t *)(cgs + tmp_i16 + 0x11128);
              tmp_u5 = *(uint32_t *)(cgs + tmp_i16 + 0x11124);
              tmp_u6 = *(uint32_t *)(cgs + tmp_i16 + 0x11120);
              tmp_f11 = tmp_f2 - (float)tmp_i12 * tmp_f10;
              local_ac = (float)*(int *)(cgs + tmp_i16 + 0x11110) * tmp_f10 + local_f0 + 0.75;
              local_a8 = tmp_f11 + 0.75;
              local_a4 = (float)*(int *)(cgs + tmp_i16 + 0x11118) * tmp_f10;
              local_a0 = tmp_f10 * (float)*(int *)(cgs + tmp_i16 + 0x1111c);
              CG_AdjustFrom640(&local_ac,&local_a8,&local_a4,&local_a0);
              trap_R_DrawStretchPic
                        (local_ac,local_a8,local_a4,local_a0,tmp_u6,tmp_u5,tmp_u4,tmp_u3,tmp_u9);
              g_unk_0014a3bc = 1.0;
              trap_R_SetColor(local_90 + 0xb);
              tmp_u9 = *(uint32_t *)(cgs + tmp_i16 + 0x11130);
              tmp_u3 = *(uint32_t *)(cgs + tmp_i16 + 0x1112c);
              tmp_u4 = *(uint32_t *)(cgs + tmp_i16 + 0x11128);
              tmp_u5 = *(uint32_t *)(cgs + tmp_i16 + 0x11124);
              tmp_u6 = *(uint32_t *)(cgs + tmp_i16 + 0x11120);
              local_9c = (float)*(int *)(cgs + tmp_i16 + 0x11110) * tmp_f10 + local_f0;
              local_94 = (float)*(int *)(cgs + tmp_i16 + 0x11118) * tmp_f10;
              local_90[0] = tmp_f10 * (float)*(int *)(cgs + tmp_i16 + 0x1111c);
              local_98 = tmp_f11;
              CG_AdjustFrom640(&local_9c,&local_98,&local_94,local_90);
              trap_R_DrawStretchPic
                        (local_9c,local_98,local_94,local_90[0],tmp_u6,tmp_u5,tmp_u4,tmp_u3,tmp_u9);
              local_ec = local_ec + 1;
              local_e8 = local_e8 + 1;
              local_f0 = (float)*(int *)(cgs + tmp_i16 + 0x11114) * tmp_f10 + 0.0 + local_f0;
              if (local_ec == (byte *)0x0) goto LAB_000590b0;
            }
            tmp_b8 = local_ec[1];
            if ((tmp_b8 == 0) || (tmp_b8 == 0x5e)) goto LAB_00058d60;
            if (tmp_b8 == 0x2a) {
              local_90[0xb] = local_90[7];
              local_60 = local_90[8];
              local_5c = local_90[9];
            }
            else {
              tmp_i12 = ((int)(char)tmp_b8 - 0x30U & 0x1f) * 0x10;
              local_90[0xb] = *(float *)(g_color_table + tmp_i12);
              local_60 = *(uint32_t *)(g_color_table + tmp_i12 + 4);
              local_5c = *(uint32_t *)(g_color_table + tmp_i12 + 8);
            }
            local_58 = local_90[10];
            trap_R_SetColor(local_90 + 0xb);
            local_ec = local_ec + 2;
          } while (local_ec != (byte *)0x0);
LAB_000590b0:
          trap_R_SetColor(0);
        }
      }
      local_bc = local_bc + 1;
    } while ((local_bc < g_unk_010ee740) &&
            (tmp_pi1 = (int *)(local_c8 + 0x40), local_c8 = local_c8 + 0x2c, *tmp_pi1 != 0));
  }
  g_unk_010ee740 = 0;
  if (0 < g_unk_010eecc4) {
    tmp_pu15 = (uint32_t *)&g_unk_010ee744;
    tmp_i12 = 0;
    do {
      CG_Trace(local_54,&g_unk_010918c0,local_90 + 1,local_90 + 4,tmp_pu15 + 5,0xffffffff,1);
      if (1.0 <= local_4c) {
        local_90[10] = 0.75;
        CG_Text_Paint_Ext_constprop_18(*tmp_pu15,tmp_pu15[1],tmp_pu15[2],tmp_pu15[2],7,0x110afec);
        tmp_u14 = 0;
        do {
          *(uint32_t *)((int)tmp_pu15 + tmp_u14) = 0;
          *(uint32_t *)((int)tmp_pu15 + tmp_u14 + 4) = 0;
          tmp_u14 = tmp_u14 + 8;
        } while (tmp_u14 < 0x28);
        *(uint32_t *)((int)tmp_pu15 + tmp_u14) = 0;
      }
      tmp_i12 = tmp_i12 + 1;
      tmp_pu15 = tmp_pu15 + 0xb;
    } while (tmp_i12 < g_unk_010eecc4);
  }
  g_unk_010eecc4 = 0;
  return;
}

void CG_DrawMiscGamemodels(void)
{
  uint tmp_u1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  uint32_t local_108 [7];
  uint32_t local_ec;
  uint32_t local_e8;
  uint32_t local_e4;
  uint32_t local_e0;
  uint32_t local_dc;
  uint32_t local_d8;
  uint32_t local_d4;
  uint32_t local_d0;
  uint32_t local_cc;
  uint32_t local_a4;
  uint32_t local_a0;
  uint32_t local_9c;
  uint32_t local_98;
  uint32_t local_84;
  uint32_t local_80;
  uint32_t local_7c;
  
  tmp_u1 = 0;
  do {
    *(uint32_t *)((int)local_108 + tmp_u1) = 0;
    *(uint32_t *)((int)local_108 + tmp_u1 + 4) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0xe8);
  *(uint32_t *)((int)local_108 + tmp_u1) = 0;
  local_a4 = 1;
  local_108[1] = 0x10;
  if (0 < g_unk_010abd70) {
    tmp_i4 = 0;
    tmp_pu3 = (uint32_t *)(cgs + 0x200b190);
    do {
      if ((((float)tmp_pu3[0xc] == 0.0) ||
          (tmp_i2 = CG_CullPointAndRadius(tmp_pu3,tmp_pu3[0xc]), tmp_i2 == 0)) &&
         (tmp_i2 = trap_R_inPVS(g_unk_010afbcc + 0x18,tmp_pu3), tmp_i2 != 0)) {
        local_108[3] = *tmp_pu3;
        local_108[2] = tmp_pu3[-1];
        local_108[4] = tmp_pu3[1];
        local_108[5] = tmp_pu3[2];
        local_ec = tmp_pu3[3];
        local_e8 = tmp_pu3[4];
        local_e4 = tmp_pu3[5];
        local_e0 = tmp_pu3[6];
        local_dc = tmp_pu3[7];
        local_d8 = tmp_pu3[8];
        local_d4 = tmp_pu3[9];
        local_d0 = tmp_pu3[10];
        local_cc = tmp_pu3[0xb];
        local_a0 = local_108[3];
        local_9c = local_108[4];
        local_98 = local_108[5];
        local_84 = local_108[3];
        local_80 = local_108[4];
        local_7c = local_108[5];
        trap_R_AddRefEntityToScene(local_108);
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu3 = tmp_pu3 + 0xe;
    } while (tmp_i4 < g_unk_010abd70);
  }
  return;
}

void CG_DrawMissileCamera(float *param_1)
{
  int tmp_i1;
  uint tmp_u2;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  float local_1d8;
  float local_1d4;
  float local_1d0;
  float local_1cc;
  int local_1c8 [6];
  float local_1b0;
  float local_1ac;
  float local_1a8;
  uint8_t local_1a4 [36];
  uint32_t local_180;
  uint32_t auStack_178 [90];
  
  if (g_unk_010ee054 != 0) {
    CG_HudPlacement(1);
    trap_R_SaveViewParms();
    tmp_i1 = g_unk_010ee054;
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)local_1c8 + tmp_u2) = 0;
      *(uint32_t *)((int)local_1c8 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < 0x1a8);
    *(uint32_t *)((int)local_1c8 + tmp_u2) = 0;
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)auStack_178 + tmp_u2) = *(uint32_t *)(g_unk_01047b00 + 0xc + tmp_u2);
      tmp_u2 = tmp_u2 + 4;
    } while (tmp_u2 < 0x20);
    g_unk_010ee058 = 1;
    local_1e4 = *param_1;
    local_1e0 = param_1[1];
    local_1dc = param_1[2];
    local_1d8 = param_1[3];
    CG_AdjustFrom640(&local_1e4,&local_1e0,&local_1dc,&local_1d8);
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)local_1c8 + tmp_u2) = 0;
      *(uint32_t *)((int)local_1c8 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < 0x1a8);
    *(uint32_t *)((int)local_1c8 + tmp_u2) = 0;
    AxisClear(local_1a4);
    local_1c8[4] = g_unk_010afbcc[4];
    local_1c8[5] = g_unk_010afbcc[5];
    local_180 = g_unk_010906e0;
    local_1c8[0] = (int)ROUND(local_1e4);
    local_1c8[1] = (int)ROUND(local_1e0);
    local_1c8[2] = (int)ROUND(local_1dc);
    local_1c8[3] = (int)ROUND(local_1d8);
    local_1b0 = *(float *)(tmp_i1 + 0x794);
    local_1ac = *(float *)(tmp_i1 + 0x798);
    local_1a8 = *(float *)(tmp_i1 + 0x79c);
    *(uint32_t *)(tmp_i1 + 0x7a8) = 0;
    AnglesToAxis(tmp_i1 + 0x7a0,local_1a4);
    AngleVectors(tmp_i1 + 0x7a0,&local_1d4,0,0);
    local_1b0 = local_1d4 * 32.0 + local_1b0;
    local_1ac = local_1d0 * 32.0 + local_1ac;
    local_1a8 = local_1cc * 32.0 + local_1a8;
    g_unk_010afbcc = local_1c8;
    trap_R_ClearScene();
    CG_SetupFrustum();
    CG_DrawSkyBoxPortal(0);
    if (g_unk_010906f8 == 0) {
      CG_AddPacketEntities();
      CG_AddMarks();
      CG_AddParticles();
      CG_AddLocalEntities();
      CG_AddSmokeSprites();
      CG_AddAtmosphericEffects();
      CG_AddFlameChunks();
      CG_AddTrails();
      CG_PB_RenderPolyBuffers();
      CG_DrawMiscGamemodels();
      if (GHIDRA_FIELD(cg_coronas, 12, 4) != 0) {
        CG_Coronas_part_4();
      }
    }
    local_180 = g_unk_010906e0;
    trap_SetClientLerpOrigin(local_1b0,local_1ac,local_1a8);
    trap_R_RenderScene(local_1c8);
    g_unk_010afbcc = &g_unk_010918a8;
    g_unk_010ee058 = 0;
    CG_DrawPic(*param_1,param_1[1],param_1[2],param_1[3],GHIDRA_FIELD(cgs, 131900, 4));
    trap_R_RestoreViewParms();
  }
  return;
}

void CG_DrawAnnouncer(void)
{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  uint tmp_u5;
  byte *tmp_pb6;
  uint *tmp_pu7;
  uint *tmp_pu8;
  int tmp_i9;
  double tmp_d10;
  
  if ((GHIDRA_FIELD(cg_announcer, 12, 4) != 0) && (g_unk_010906e0 < g_unk_010ee060)) {
    CG_HudPlacement(0);
    tmp_f2 = (float)(g_unk_010ee060 - g_unk_010906e0) / (float)g_unk_010ee468;
    if (g_unk_010ee478 == 2) {
      tmp_d10 = sin((double)(tmp_f2 * 3.1415927));
      tmp_f2 = (1.1 - (float)tmp_d10) * g_unk_010ee464;
    }
    else {
      if (g_unk_010ee478 == 3) {
        tmp_d10 = sin((double)(tmp_f2 * 3.1415927));
        tmp_f2 = 1.0 - (float)tmp_d10;
      }
      tmp_f2 = (1.1 - tmp_f2) * g_unk_010ee464;
    }
    tmp_pu8 = &g_unk_010ee064;
    do {
      tmp_pu7 = tmp_pu8;
      tmp_u4 = *tmp_pu7 + 0xfefefeff & ~*tmp_pu7;
      tmp_u5 = tmp_u4 & 0x80808080;
      tmp_pu8 = tmp_pu7 + 1;
    } while (tmp_u5 == 0);
    if ((tmp_u4 & 0x8080) == 0) {
      tmp_pu8 = (uint *)((int)tmp_pu7 + 6);
      tmp_u5 = tmp_u5 >> 0x10;
    }
    tmp_i9 = 0;
    tmp_f3 = 0.0;
    tmp_pb6 = (byte *)&g_unk_010ee064;
    do {
      tmp_b1 = *tmp_pb6;
      if ((tmp_b1 == 0) ||
         ((int)((int)tmp_pu8 + (-0x10ee067 - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5))) <= tmp_i9))
      break;
      if ((tmp_b1 == 0x5e) && ((tmp_pb6[1] != 0 && (tmp_pb6[1] != 0x5e)))) {
        tmp_pb6 = tmp_pb6 + 2;
      }
      else {
        tmp_pb6 = tmp_pb6 + 1;
        tmp_i9 = tmp_i9 + 1;
        tmp_f3 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x11114) + tmp_f3;
      }
    } while (tmp_pb6 != (byte *)0x0);
    CG_Text_Paint_Ext_constprop_18
              (320.0 - (float)(int)ROUND(tmp_f2 * (float)GHIDRA_FIELD(cgs, 90372, 4) * tmp_f3) * 0.5,
               (float)(int)ROUND(240.0 - (float)g_unk_010ee47c),tmp_f2,tmp_f2,3,0x1100f64);
  }
  return;
}

void CG_DrawActive(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  byte tmp_b3;
  byte tmp_b4;
  uint32_t tmp_u5;
  float tmp_f6;
  float tmp_f7;
  int tmp_i8;
  uint32_t tmp_u9;
  char *tmp_pc10;
  int tmp_i11;
  size_t tmp_s12;
  uint32_t tmp_u13;
  long tmp_l14;
  uint tmp_u15;
  int tmp_i16;
  byte *__s;
  uint8_t *tmp_pu17;
  int tmp_i18;
  uint *tmp_pu19;
  uint *tmp_pu20;
  uint tmp_u21;
  char *tmp_pc22;
  long double tmp_l23;
  double tmp_d24;
  float *local_128;
  float *local_124;
  int local_120;
  uint32_t local_11c;
  int local_fc;
  int local_f8;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc [12];
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  uint32_t uStack_14;
  
  uStack_14 = 0x5b8a9;
  if (g_unk_01047b00 == 0) {
    CG_DrawInformation(0);
    return;
  }
  if (param_1 == 1) {
    local_128 = (float *)(-(float)GHIDRA_FIELD(cg_stereoSeparation, 8, 4) * 0.5);
LAB_0005b8f9:
    CG_TileClear();
    local_124 = *(float **)(g_unk_010afbcc + 0x18);
    local_120 = *(uint32_t *)(g_unk_010afbcc + 0x1c);
    local_11c = *(uint32_t *)(g_unk_010afbcc + 0x20);
    if ((float)local_128 != 0.0) {
      tmp_f6 = -(float)local_128;
      *(float *)(g_unk_010afbcc + 0x18) = *(float *)(g_unk_010afbcc + 0x30) * tmp_f6 + (float)local_124;
      *(float *)(g_unk_010afbcc + 0x1c) =
           *(float *)(g_unk_010afbcc + 0x34) * tmp_f6 + *(float *)(g_unk_010afbcc + 0x1c);
      *(float *)(g_unk_010afbcc + 0x20) =
           tmp_f6 * *(float *)(g_unk_010afbcc + 0x38) + *(float *)(g_unk_010afbcc + 0x20);
    }
  }
  else {
    if (param_1 == 0) {
      local_128 = (float *)0x0;
      goto LAB_0005b8f9;
    }
    if (param_1 == 2) {
      local_128 = (float *)((float)GHIDRA_FIELD(cg_stereoSeparation, 8, 4) * 0.5);
      goto LAB_0005b8f9;
    }
    CG_Error("CG_DrawActive: Undefined stereoView");
    CG_TileClear();
    local_124 = *(float **)(g_unk_010afbcc + 0x18);
    local_120 = *(uint32_t *)(g_unk_010afbcc + 0x1c);
    local_11c = *(uint32_t *)(g_unk_010afbcc + 0x20);
    local_128 = (float *)0x0;
  }
  *(uint32_t *)(g_unk_010afbcc + 0x1a0) = 0;
  CG_ShakeCamera();
  CG_PB_RenderPolyBuffers();
  CG_DrawMiscGamemodels();
  if (GHIDRA_FIELD(cg_coronas, 12, 4) != 0) {
    CG_Coronas_part_4();
  }
  if ((g_unk_010906e0 < g_unk_010b3b28) && (g_unk_010abd78 != 0)) {
    if ((float)local_128 == 0.0) goto LAB_0005bcb0;
LAB_0005b9bd:
    *(float **)(g_unk_010afbcc + 0x18) = local_124;
    *(int *)(g_unk_010afbcc + 0x1c) = local_120;
    *(uint32_t *)(g_unk_010afbcc + 0x20) = local_11c;
  }
  else {
    trap_R_RenderScene(g_unk_010afbcc);
    if ((float)local_128 != 0.0) goto LAB_0005b9bd;
  }
  if (g_unk_010abd78 != 0) {
LAB_0005bcb0:
    CG_LimboPanel_Draw();
    return;
  }
  jP_SetHUDColors();
  if (*(int *)(g_unk_01047b00 + 0x30) == 5) {
    if (g_unk_01047aec == 0) {
      if (g_unk_010ab344 == 0) {
        g_unk_010ab344 = 1;
        if ((GHIDRA_FIELD(cg_autoAction, 12, 4) & 2) != 0) {
          doScreenshot_12512 = g_unk_010906e0 + 1000;
        }
        if ((GHIDRA_FIELD(cg_autoAction, 12, 4) & 4) != 0) {
          CG_dumpStats_f();
        }
        if (((GHIDRA_FIELD(cg_autoAction, 12, 4) & 1) != 0) && ((GHIDRA_FIELD(cgs, 27388, 4) != 3 || (GHIDRA_FIELD(cgs, 33525344, 4) == 0))))
        {
          doDemostop_12513 = g_unk_010906e0 + 5000;
        }
      }
      if ((0 < doScreenshot_12512) && (doScreenshot_12512 < g_unk_010906e0)) {
        CG_autoScreenShot_f();
        doScreenshot_12512 = 0;
      }
      if ((0 < doDemostop_12513) && (doDemostop_12513 < g_unk_010906e0)) {
        trap_SendConsoleCommand("stoprecord\n");
        doDemostop_12513 = 0;
      }
    }
    CG_Debriefing_Draw();
    return;
  }
  tmp_pu17 = cgs;
  if (GHIDRA_FIELD(cgs, 33686244, 4) != 0) {
    CG_Debriefing_Shutdown();
  }
  if (g_unk_010b4554 != 0) {
    CG_SpeakerEditorDraw();
    return;
  }
  CG_DrawOnScreenNames();
  tmp_i8 = g_unk_010aacf4;
  if ((g_unk_01090730 != 0) && (g_unk_010907a0 != 1)) {
    if (g_unk_010907a0 == 0xf) {
      tmp_i8 = g_unk_01090730;
      if (g_unk_01090730 % 1000 < g_unk_010aacf4 % 1000) {
LAB_0005babb:
        trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69496, 4));
        tmp_i8 = g_unk_01090730;
      }
    }
    else {
      tmp_i11 = g_unk_01090730 / 1000;
      tmp_i8 = g_unk_01090730;
      if (g_unk_010aacf4 % 1000 < g_unk_01090730 % 1000) {
        if (tmp_i11 == 1) {
          trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69504, 4));
          tmp_i8 = g_unk_01090730;
        }
        else if (tmp_i11 < 2) {
          tmp_i8 = g_unk_01090730;
          if (tmp_i11 == 0) {
            trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69508, 4));
            tmp_i8 = g_unk_01090730;
          }
        }
        else if (tmp_i11 == 2) {
          trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69500, 4));
          tmp_i8 = g_unk_01090730;
        }
        else {
          tmp_i8 = g_unk_01090730;
          if (tmp_i11 == 3) goto LAB_0005babb;
        }
      }
    }
  }
  g_unk_010aacf4 = tmp_i8;
  if (GHIDRA_FIELD(cg_draw2D, 12, 4) == 0) {
    if (g_unk_01047aec != 0) {
      return;
    }
    CG_DrawCrosshair();
    CG_DrawFlashFade();
    return;
  }
  if (g_unk_010aaecc == 0) {
    if (g_unk_01047b00 != 0) {
      if ((*(uint *)(g_unk_01047b00 + 0x94) & 0x8020) == 0) {
        if ((g_unk_010906f4 == 0) && ((float)(g_unk_010906e0 - g_unk_01091a6c) < 400.0)) {
          local_9c = 0.0;
          local_98 = 0.0;
          local_94 = 0.0;
          local_90 = 1.0 - (float)(g_unk_010906e0 - g_unk_01091a6c) / 400.0;
          CG_FillRectFullScreen(0xc1200000,0xc1200000,0x44228000,0x43f50000,&local_9c);
        }
      }
      else {
        g_unk_01091a6c = g_unk_010906e0;
      }
    }
    CG_DrawFlashFade();
    if (*(int *)(g_unk_01047b00 + 0x158) == 3) {
      CG_DrawCrosshair();
      CG_DrawCrosshairNames();
    }
    else {
      if ((0 < *(int *)(g_unk_01047b00 + 0xfc)) || ((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) != 0)) {
        CG_DrawCrosshair();
        CG_DrawCrosshairNames();
        if (((g_unk_01090766 & 8) == 0) || (*(int *)(g_unk_01047b00 + 0xd0) != 5)) {
          if ((g_unk_010aabe4 != 0) || (*(int *)(g_unk_01047b00 + 0x454) - 0x19U < 2)) {
            tmp_i8 = CG_FadeColor(g_unk_0109355c);
            if (tmp_i8 != 0) {
              trap_R_SetColor(tmp_i8);
              goto LAB_0005d6f8;
            }
            trap_R_SetColor(0);
          }
        }
        else {
          trap_R_SetColor(colorRed);
LAB_0005d6f8:
          CG_HudPlacement(0);
          local_9c = 48.0;
          local_cc[4] = 48.0;
          local_d0 = (float)(GHIDRA_FIELD(cg_crosshairX, 12, 4) + 1);
          local_cc[0] = (float)(GHIDRA_FIELD(cg_crosshairY, 12, 4) + 1);
          CG_AdjustFrom640(&local_d0,local_cc,local_cc + 4,&local_9c);
          local_d0 = local_d0 - (float)GHIDRA_FIELD(cgs, 27372, 4);
          trap_R_DrawStretchPic
                    (((float)*(int *)(g_unk_010afbcc + 8) - local_cc[4]) * 0.5 + local_d0,
                     ((float)*(int *)(g_unk_010afbcc + 0xc) - local_9c) * 0.5 + local_cc[0],
                     local_cc[4],local_9c,0,0,0x3f800000,0x3f800000,GHIDRA_FIELD(cgs, 67964, 4));
        }
      }
      if (((GHIDRA_FIELD(cg_drawStatus, 12, 4) != 0) && (Menu_PaintAll(), g_unk_010aac1c != 0)) &&
         (0x9c4 < g_unk_010906e0 - g_unk_010aac1c)) {
        Menus_CloseByName("voiceMenu");
        trap_Cvar_Set("cl_conXOffset");
        g_unk_010aac1c = 0;
      }
    }
  }
  tmp_i8 = CG_DrawScoreboard();
  if (tmp_i8 != 0) {
    if (GHIDRA_FIELD(cgs, 67784, 4) != 0) {
      trap_R_SetColor(0);
      CG_DrawPic((float)(g_unk_010261a4 + -0xe),(float)(g_unk_010261a8 + -0xe),0x42000000,0x42000000,
                 GHIDRA_FIELD(cgs, 131752, 4));
    }
    goto LAB_0005bb20;
  }
  local_cc[0] = 1.0;
  local_cc[1] = 1.0;
  local_cc[2] = 0.0;
  local_cc[3] = 1.0;
  CG_HudPlacement(1);
  if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
LAB_0005d439:
    if (GHIDRA_FIELD(cgs, 27664, 4) == 0) {
      if ((((g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33525624, 4)) && (g_unk_01047aec == 0)) &&
          (0 < (int)GHIDRA_FIELD(cg_complaintPopUp, 12, 4))) && ((int)GHIDRA_FIELD(cgs, 33525620, 4) < 0)) {
        tmp_pc10 = (char *)0x0;
        switch(GHIDRA_FIELD(cgs, 33525620, 4)) {
        case 0xfffffffb:
          break;
        case 0xfffffffc:
          break;
        case 0xfffffffd:
          break;
        case 0xfffffffe:
          break;
        case 0xffffffff:
          break;
        default:
          goto switchD_0005e9fa_default;
        }
      }
      else if ((g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33575932, 4)) && ((int)GHIDRA_FIELD(cgs, 33575928, 4) < 0)) {
        if (GHIDRA_FIELD(cgs, 33575928, 4) == -3) {
          tmp_pc10 = (char *)0x0;
        }
        else if ((int)GHIDRA_FIELD(cgs, 33575928, 4) < -2) {
          if (GHIDRA_FIELD(cgs, 33575928, 4) != -4) goto switchD_0005e9fa_default;
          tmp_pc10 = (char *)0x0;
        }
        else if (GHIDRA_FIELD(cgs, 33575928, 4) == -2) {
          tmp_pc10 = (char *)0x0;
        }
        else {
          if (GHIDRA_FIELD(cgs, 33575928, 4) != -1) goto switchD_0005e9fa_default;
          tmp_pc10 = (char *)0x0;
        }
      }
      else if ((g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33575944, 4)) && ((int)GHIDRA_FIELD(cgs, 33575936, 4) < 0)) {
        if (GHIDRA_FIELD(cgs, 33575936, 4) == -3) {
          tmp_pc10 = (char *)0x0;
        }
        else if ((int)GHIDRA_FIELD(cgs, 33575936, 4) < -2) {
          if (GHIDRA_FIELD(cgs, 33575936, 4) != -4) goto switchD_0005e9fa_default;
          tmp_pc10 = (char *)0x0;
        }
        else if (GHIDRA_FIELD(cgs, 33575936, 4) == -2) {
          tmp_pc10 = (char *)0x0;
        }
        else {
          if (GHIDRA_FIELD(cgs, 33575936, 4) != -1) goto switchD_0005e9fa_default;
          tmp_pc10 = (char *)0x0;
        }
      }
      else if ((g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33575924, 4)) && ((int)GHIDRA_FIELD(cgs, 33575920, 4) < 0)) {
        if (GHIDRA_FIELD(cgs, 33575920, 4) == -3) {
          tmp_pc10 = (char *)0x0;
        }
        else if ((int)GHIDRA_FIELD(cgs, 33575920, 4) < -2) {
          if (GHIDRA_FIELD(cgs, 33575920, 4) != -4) goto switchD_0005e9fa_default;
          tmp_pc10 = (char *)0x0;
        }
        else if (GHIDRA_FIELD(cgs, 33575920, 4) == -2) {
          tmp_pc10 = (char *)0x0;
        }
        else {
          if (GHIDRA_FIELD(cgs, 33575920, 4) != -1) goto switchD_0005e9fa_default;
          tmp_pc10 = (char *)0x0;
        }
      }
      else {
        if ((((int)GHIDRA_FIELD(cgs, 33575948, 4) <= g_unk_010906e0) || (GHIDRA_FIELD(cgs, 33575952, 4) != -2)) &&
           ((((int)GHIDRA_FIELD(cgs, 33575956, 4) <= g_unk_010906e0 || (GHIDRA_FIELD(cgs, 33575960, 4) != -2)) &&
            (((int)GHIDRA_FIELD(cgs, 33575964, 4) <= g_unk_010906e0 || (GHIDRA_FIELD(cgs, 33575968, 4) != -2))))))
        goto switchD_0005e9fa_default;
        tmp_pc10 = (char *)0x0;
      }
      goto LAB_0005c026;
    }
    if (GHIDRA_FIELD(cgs, 27676, 4) != 0) {
      GHIDRA_FIELD(cgs, 27676, 4) = 0;
    }
    tmp_i8 = ((GHIDRA_FIELD(cgs, 27664, 4) - g_unk_010906e0) + 30000) / 1000;
    if (-1 < tmp_i8) {
      tmp_i11 = Q_stricmpn(0x10f6a80,"kick",4);
      tmp_pu20 = (uint *)(cgs + 0x6c20);
      if (tmp_i11 == 0) {
        do {
          tmp_pu19 = tmp_pu20;
          tmp_u15 = *tmp_pu19 + 0xfefefeff & ~*tmp_pu19;
          tmp_u21 = tmp_u15 & 0x80808080;
          tmp_pu20 = tmp_pu19 + 1;
        } while (tmp_u21 == 0);
        if ((tmp_u15 & 0x8080) == 0) {
          tmp_pu20 = (uint *)((int)tmp_pu19 + 6);
          tmp_u21 = tmp_u21 >> 0x10;
        }
        if (5 < (int)tmp_pu20 + (-0x10f6a83 - (uint)CARRY1((byte)tmp_u21,(byte)tmp_u21))) {
          Q_strncpyz(&local_9c,0x10f6a85,0x80);
          tmp_i11 = 0x10f92b4;
          Q_CleanStr(&local_9c);
          do {
            if ((((*(int *)(tmp_i11 + -0x48) != 0) && (tmp_i16 = Q_stricmp(tmp_i11), tmp_i16 == 0)) &&
                (*(int *)(tmp_i11 + 0x40) != 3)) &&
               (*(int *)(tmp_i11 + 0x40) != *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494)))
            goto switchD_0005e9fa_default;
            tmp_i11 = tmp_i11 + 0x1a4;
          } while (tmp_i11 != 0x10ffbb4);
        }
      }
      if ((*(byte *)(g_unk_01047b00 + 0x95) & 0x40) != 0) {
        tmp_i8 = va("YOU VOTED ON: %s");
        tmp_pc10 = (char *)va("Y:%i, N:%i",GHIDRA_FIELD(cgs, 27668, 4),GHIDRA_FIELD(cgs, 27672, 4));
        goto LAB_0005c022;
      }
      tmp_i8 = va("VOTE(%i): %s",tmp_i8,0x10f6a80);
      if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) - 1U < 2) {
        tmp_u9 = BindingFromName("vote yes");
        Q_strncpyz(local_cc + 4,tmp_u9,0x20);
        tmp_u9 = BindingFromName("vote no");
        Q_strncpyz(&local_9c,tmp_u9,0x20);
        tmp_pc10 = (char *)va("YES(%s):%i, NO(%s):%i",local_cc + 4,GHIDRA_FIELD(cgs, 27668, 4),&local_9c,
                             GHIDRA_FIELD(cgs, 27672, 4));
        goto LAB_0005c022;
      }
      tmp_pc10 = "Cannot vote as Spectator";
      if (tmp_i8 != 0) goto LAB_0005c026;
      goto LAB_0005c072;
    }
    GHIDRA_FIELD(cgs, 27664, 4) = 0;
    GHIDRA_FIELD(cgs, 33525624, 4) = 0;
    GHIDRA_FIELD(cgs, 33575932, 4) = 0;
    GHIDRA_FIELD(cgs, 33575944, 4) = 0;
    GHIDRA_FIELD(cgs, 33575924, 4) = 0;
    GHIDRA_FIELD(cgs, 33575948, 4) = 0;
    GHIDRA_FIELD(cgs, 33575956, 4) = 0;
    GHIDRA_FIELD(cgs, 33575964, 4) = 0;
  }
  else {
    if (((g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33525624, 4)) && (g_unk_01047aec == 0)) &&
       ((0 < (int)GHIDRA_FIELD(cg_complaintPopUp, 12, 4) && (-1 < (int)GHIDRA_FIELD(cgs, 33525620, 4))))) {
      tmp_u9 = BindingFromName("vote yes");
      Q_strncpyz(local_cc + 4,tmp_u9,0x20);
      tmp_u9 = BindingFromName("vote no");
      Q_strncpyz(&local_9c,tmp_u9,0x20);
      tmp_pc10 = "File complaint against ^7%s^3 for team-killing?";
LAB_0005bff8:
      tmp_i8 = va(tmp_pc10);
    }
    else {
      if ((g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33575932, 4)) && (-1 < (int)GHIDRA_FIELD(cgs, 33575928, 4))) {
        tmp_u9 = BindingFromName("vote yes");
        Q_strncpyz(local_cc + 4,tmp_u9,0x20);
        tmp_u9 = BindingFromName("vote no");
        Q_strncpyz(&local_9c,tmp_u9,0x20);
        tmp_pc10 = "Accept ^7%s^3\'s application to join your fireteam?";
        goto LAB_0005bff8;
      }
      if (((int)GHIDRA_FIELD(cgs, 33575944, 4) <= g_unk_010906e0) || ((int)GHIDRA_FIELD(cgs, 33575936, 4) < 0)) {
        if (((int)GHIDRA_FIELD(cgs, 33575924, 4) <= g_unk_010906e0) || ((int)GHIDRA_FIELD(cgs, 33575920, 4) < 0)) {
          if ((g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33575948, 4)) && (GHIDRA_FIELD(cgs, 33575952, 4) == -1)) {
            tmp_u9 = BindingFromName("vote yes");
            Q_strncpyz(local_cc + 4,tmp_u9,0x20);
            tmp_u9 = BindingFromName("vote no");
            Q_strncpyz(&local_9c,tmp_u9,0x20);
            tmp_pc10 = (char *)va("Press \'%s\' for YES, or \'%s\' for No",local_cc + 4,&local_9c);
          }
          else if ((g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33575956, 4)) && (GHIDRA_FIELD(cgs, 33575960, 4) == -1)) {
            tmp_u9 = BindingFromName("vote yes");
            Q_strncpyz(local_cc + 4,tmp_u9,0x20);
            tmp_u9 = BindingFromName("vote no");
            Q_strncpyz(&local_9c,tmp_u9,0x20);
            tmp_pc10 = (char *)va("Press \'%s\' for YES, or \'%s\' for No",local_cc + 4,&local_9c);
          }
          else {
            if (((int)GHIDRA_FIELD(cgs, 33575964, 4) <= g_unk_010906e0) || (GHIDRA_FIELD(cgs, 33575968, 4) != -1))
            goto LAB_0005d439;
            tmp_u9 = BindingFromName("vote yes");
            Q_strncpyz(local_cc + 4,tmp_u9,0x20);
            tmp_u9 = BindingFromName("vote no");
            Q_strncpyz(&local_9c,tmp_u9,0x20);
            tmp_pc10 = (char *)va("Press \'%s\' for YES, or \'%s\' for No",local_cc + 4,&local_9c);
          }
          goto LAB_0005c026;
        }
        tmp_u9 = BindingFromName("vote yes");
        Q_strncpyz(local_cc + 4,tmp_u9,0x20);
        tmp_u9 = BindingFromName("vote no");
        Q_strncpyz(&local_9c,tmp_u9,0x20);
        tmp_pc10 = "Accept ^7%s^3\'s invitation to join their fireteam?";
        goto LAB_0005bff8;
      }
      tmp_u9 = BindingFromName("vote yes");
      Q_strncpyz(local_cc + 4,tmp_u9,0x20);
      tmp_u9 = BindingFromName("vote no");
      Q_strncpyz(&local_9c,tmp_u9,0x20);
      tmp_i8 = va("Accept ^7%s^3\'s proposition to invite ^7%s^3 to join your fireteam?",
                 GHIDRA_FIELD(cgs, 33575940, 4) * 0x1a4 + 0x10f9274,GHIDRA_FIELD(cgs, 33575936, 4) * 0x1a4 + 0x10f9274);
    }
    local_124 = local_cc + 4;
    local_128 = &local_9c;
    tmp_pc10 = (char *)va("Press \'%s\' for YES, or \'%s\' for No",local_124,local_128);
LAB_0005c022:
    if (tmp_i8 != 0) {
LAB_0005c026:
      CG_Text_Paint_Ext_constprop_18(0x41000000,0x43340000,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
    }
    if (tmp_pc10 != (char *)0x0) {
LAB_0005c072:
      CG_Text_Paint_Ext_constprop_18(0x41000000,0x433c0000,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
    }
  }
switchD_0005e9fa_default:
  CG_HudPlacement(0);
  tmp_u9 = GHIDRA_FIELD(cgs, 66532, 4);
  tmp_i8 = g_unk_010906e0;
  local_124 = (float *)GHIDRA_FIELD(cg_teamChatHeight, 12, 4);
  if ((int)GHIDRA_FIELD(cg_teamChatHeight, 12, 4) < 8) {
    if (0 < (int)GHIDRA_FIELD(cg_teamChatHeight, 12, 4)) goto LAB_0005ca23;
  }
  else {
    local_124 = (float *)0x8;
LAB_0005ca23:
    if (GHIDRA_FIELD(cgs, 66536, 4) != GHIDRA_FIELD(cgs, 66532, 4)) {
      local_120 = GHIDRA_FIELD(cg_teamChatTime, 12, 4);
      if ((int)GHIDRA_FIELD(cg_teamChatTime, 12, 4) <
          g_unk_010906e0 - *(int *)(cgs + ((int)GHIDRA_FIELD(cgs, 66536, 4) % (int)local_124) * 4 + 0x103a4)) {
        GHIDRA_FIELD(cgs, 66536, 4) = GHIDRA_FIELD(cgs, 66536, 4) + 1;
      }
      tmp_u13 = GHIDRA_FIELD(cgs, 66536, 4);
      if ((int)GHIDRA_FIELD(cgs, 66536, 4) < (int)GHIDRA_FIELD(cgs, 66532, 4)) {
        local_128 = (float *)GHIDRA_FIELD(cgs, 66536, 4);
        do {
          tmp_pc10 = cgs + ((int)local_128 % (int)local_124) * 0xd3 + 0xfd0c;
          tmp_s12 = strlen(tmp_pc10);
          tmp_i11 = 0;
          do {
            if ((*tmp_pc10 == '\0') || ((int)tmp_s12 <= tmp_i11)) break;
            if ((*tmp_pc10 == '^') && ((tmp_pc10[1] != '\0' && (tmp_pc10[1] != '^')))) {
              tmp_pc10 = tmp_pc10 + 2;
            }
            else {
              tmp_pc10 = tmp_pc10 + 1;
              tmp_i11 = tmp_i11 + 1;
            }
          } while (tmp_pc10 != (char *)0x0);
          local_128 = (float *)((int)local_128 + 1);
        } while (local_128 != (float *)tmp_u9);
      }
      tmp_u21 = tmp_u9 - 1;
      if ((int)tmp_u13 <= (int)tmp_u21) {
        while( true ) {
          tmp_f6 = 1.0 - (float)(tmp_i8 - *(int *)(cgs + ((int)tmp_u21 % (int)local_124) * 4 + 0x103a4)
                               ) / (float)local_120;
          if (tmp_f6 <= 1.0) {
            if (tmp_f6 < 0.0) {
              local_90 = 0.0;
              tmp_f6 = 0.0;
            }
            else {
              local_90 = tmp_f6 * 0.33;
            }
          }
          else {
            local_90 = 0.33;
            tmp_f6 = 1.0;
          }
          tmp_i8 = (int)tmp_u21 % (int)local_124 + 0x40f0;
          tmp_i11 = *(int *)(cgs + tmp_i8 * 4 + 4);
          if (tmp_i11 == 1) {
            local_9c = 1.0;
            local_98 = 0.0;
            local_94 = 0.0;
          }
          else {
            local_9c = 0.0;
            if (tmp_i11 == 2) {
              local_98 = 0.0;
              local_94 = 1.0;
            }
            else {
              local_98 = 1.0;
              local_94 = 0.0;
              if (tmp_i11 == 0) {
                local_90 = tmp_f6 * 0.55;
                local_9c = 1.0;
                local_94 = 1.0;
              }
            }
          }
          trap_R_SetColor(&local_9c);
          CG_DrawPic(0x43110000,478.0 - (float)(int)(GHIDRA_FIELD(cgs, 66532, 4) - tmp_u21) * 9.0,0x43c58000,
                     0x41100000,GHIDRA_FIELD(cgs, 67864, 4));
          local_94 = 1.0;
          local_98 = 1.0;
          local_9c = 1.0;
          local_90 = tmp_f6;
          trap_R_SetColor(&local_9c);
          tmp_i8 = *(int *)(cgs + tmp_i8 * 4 + 4);
          tmp_u9 = GHIDRA_FIELD(cgs, 131848, 4);
          if (((tmp_i8 == 1) || (tmp_u9 = GHIDRA_FIELD(cgs, 131852, 4), tmp_i8 == 2)) ||
             (tmp_u9 = GHIDRA_FIELD(cgs, 131676, 4), tmp_i8 == 3)) {
            CG_DrawPic(0x43030000,(478.0 - ((float)(int)(GHIDRA_FIELD(cgs, 66532, 4) - tmp_u21) - 0.9) * 9.0) - 8.0
                       ,0x41400000,0x41200000,tmp_u9);
          }
          CG_Text_Paint_Ext_constprop_18
                    (0x43130000,(478.0 - (float)(int)(~tmp_u21 + GHIDRA_FIELD(cgs, 66532, 4)) * 9.0) - 1.0,
                     0x3e428f5c,0x3e428f5c,7,0x110afec);
          if ((int)(tmp_u21 - 1) < (int)GHIDRA_FIELD(cgs, 66536, 4)) break;
          local_120 = GHIDRA_FIELD(cg_teamChatTime, 12, 4);
          tmp_i8 = g_unk_010906e0;
          tmp_u21 = tmp_u21 - 1;
        }
      }
    }
  }
  if (*(int *)(g_unk_01047b00 + 0x158) != 3) {
    if (0 < *(int *)(g_unk_01047b00 + 0xfc)) {
      CG_DrawPlayerStatus();
      CG_DrawSkillLevels();
      CG_DrawActivePowerups();
    }
    CG_DrawLivesLeft();
    local_cc[3] = 48.0;
    local_cc[2] = 48.0;
    local_cc[0] = 296.0;
    local_cc[1] = 260.0;
    CG_DrawCursorhint(local_cc);
    local_cc[0] = 50.0;
    local_cc[1] = 208.0;
    local_cc[2] = 10.0;
    local_cc[3] = 64.0;
    CG_DrawWeapStability(local_cc);
    if (GHIDRA_FIELD(cg_debugSkills, 12, 4) != 0) {
      tmp_i8 = 0;
      if ((g_unk_010906e0 <= _DAT_002b2e04 + 8999) && (-1 < _DAT_002b2dec)) {
        tmp_i8 = _DAT_002b2dec;
      }
      if ((g_unk_010906e0 <= g_unk_002b2e00 + 8999) && (tmp_i8 < g_unk_002b2de8)) {
        tmp_i8 = g_unk_002b2de8;
      }
      if ((g_unk_010906e0 <= g_unk_002b2dfc + 8999) && (tmp_i8 < g_unk_002b2de4)) {
        tmp_i8 = g_unk_002b2de4;
      }
      if ((g_unk_010906e0 <= g_unk_002b2df8 + 8999) && (tmp_i8 < g_unk_002b2de0)) {
        tmp_i8 = g_unk_002b2de0;
      }
      if ((g_unk_010906e0 <= g_unk_002b2df4 + 8999) && (tmp_i8 < g_unk_002b2ddc)) {
        tmp_i8 = g_unk_002b2ddc;
      }
      if ((g_unk_010906e0 <= statsDebugTime + 8999) && (tmp_i8 < statsDebugTextWidth)) {
        tmp_i8 = statsDebugTextWidth;
      }
      local_fc = statsDebugPos;
      local_f8 = 0x18d;
      do {
        if ((&statsDebugTime)[local_fc] + 8999 < g_unk_010906e0) break;
        local_cc[4] = 0.5;
        tmp_i11 = g_unk_010906e0 - (&statsDebugTime)[local_fc];
        local_cc[7] = local_cc[4];
        if (5000 < tmp_i11) {
          local_cc[7] = 0.5 - ((float)(tmp_i11 + -5000) / 4000.0) * 0.5;
        }
        local_cc[5] = local_cc[4];
        local_cc[6] = local_cc[4];
        CG_FillRect((float)(0x27a - tmp_i8),(float)local_f8,(float)(tmp_i8 + 6),0x41100000,
                    local_cc + 4);
        local_cc[7] = 1.0;
        local_cc[6] = 1.0;
        local_cc[5] = 1.0;
        local_cc[4] = 1.0;
        if (5000 < g_unk_010906e0 - (&statsDebugTime)[local_fc]) {
          local_cc[7] = 1.0 - (float)((g_unk_010906e0 - (&statsDebugTime)[local_fc]) + -5000) / 4000.0
          ;
        }
        __s = (byte *)(&statsDebugStrings + local_fc * 0x80);
        local_128 = (float *)(637.0 - (float)(&statsDebugTextWidth)[local_fc]);
        tmp_f6 = (float)GHIDRA_FIELD(cgs, 131468, 4) * 0.15;
        trap_R_SetColor(local_cc + 4);
        local_9c = local_cc[4];
        local_98 = local_cc[5];
        local_94 = local_cc[6];
        local_90 = local_cc[7];
        tmp_s12 = strlen((char *)__s);
        local_120 = 0;
        do {
          tmp_b3 = *__s;
          if ((tmp_b3 == 0) || ((int)tmp_s12 <= local_120)) break;
          if (tmp_b3 == 0x5e) {
            tmp_b4 = __s[1];
            if ((tmp_b4 == 0) || (tmp_b4 == 0x5e)) goto LAB_0005c3f0;
            if (tmp_b4 == 0x2a) {
              local_9c = local_cc[4];
              local_98 = local_cc[5];
              local_94 = local_cc[6];
            }
            else {
              tmp_i11 = ((int)(char)tmp_b4 - 0x30U & 0x1f) * 0x10;
              local_9c = *(float *)(g_color_table + tmp_i11);
              local_98 = *(float *)(g_color_table + tmp_i11 + 4);
              local_94 = *(float *)(g_color_table + tmp_i11 + 8);
            }
            local_90 = local_cc[7];
            trap_R_SetColor();
            __s = __s + 2;
          }
          else {
LAB_0005c3f0:
            tmp_i11 = (uint)tmp_b3 * 0x50;
            tmp_u9 = *(uint32_t *)(cgs + tmp_i11 + 0x1b1b4);
            tmp_u5 = *(uint32_t *)(cgs + tmp_i11 + 0x1b1b8);
            tmp_u13 = *(uint32_t *)(cgs + tmp_i11 + 0x1b1b0);
            tmp_u1 = *(uint32_t *)(cgs + tmp_i11 + 0x1b1ac);
            tmp_u2 = *(uint32_t *)(cgs + tmp_i11 + 0x1b1a8);
            local_d8 = (float)(local_f8 + 7) - (float)*(int *)(cgs + tmp_i11 + 0x1b190) * tmp_f6;
            local_dc = (float)*(int *)(cgs + tmp_i11 + 0x1b198) * tmp_f6 + (float)local_128;
            local_d4 = (float)*(int *)(cgs + tmp_i11 + 0x1b1a0) * tmp_f6;
            local_d0 = tmp_f6 * (float)*(int *)(cgs + tmp_i11 + 0x1b1a4);
            CG_AdjustFrom640(&local_dc,&local_d8,&local_d4,&local_d0);
            trap_R_DrawStretchPic
                      (local_dc,local_d8,local_d4,local_d0,tmp_u2,tmp_u1,tmp_u13,tmp_u9,tmp_u5);
            local_120 = local_120 + 1;
            __s = __s + 1;
            local_128 = (float *)((float)*(int *)(cgs + tmp_i11 + 0x1b19c) * tmp_f6 + 0.0 +
                                 (float)local_128);
          }
        } while (__s != (byte *)0x0);
        trap_R_SetColor();
        local_f8 = local_f8 + -9;
        tmp_i11 = local_fc + -1;
        local_fc = 5;
        if (-1 < tmp_i11) {
          local_fc = tmp_i11;
        }
      } while (statsDebugPos != local_fc);
    }
  }
  if (GHIDRA_FIELD(cg_paused, 12, 4) == 0) {
    CG_DrawUpperRight();
  }
  CG_DrawBannerPrint();
  CG_DrawCenterString();
  CG_DrawAnnouncement();
  CG_DrawPMItems();
  CG_DrawPMItemsBig();
  if ((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) != 0) {
    CG_HudPlacement(1);
    if ((*(byte *)(g_unk_01047b00 + 0x39) & 0x40) == 0) {
      tmp_i8 = *(int *)(g_unk_01047b00 + 0xcc);
      tmp_i11 = *(int *)(cgs + tmp_i8 * 0x1a4 + 0x9494);
      tmp_u9 = GHIDRA_FIELD(cgs, 131848, 4);
      if ((tmp_i11 == 1) || (tmp_u9 = GHIDRA_FIELD(cgs, 131852, 4), tmp_i11 == 2)) {
        CG_DrawPic(0x41000000,0x42f80000,0x41700000,0x41400000,tmp_u9);
        tmp_i8 = SkillNumForClass(*(uint32_t *)
                                  (cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x94b8));
        CG_DrawPic(0x41b80000,0x42f80000,0x41500000,0x41500000,
                   *(uint32_t *)(cgs + tmp_i8 * 4 + 0x11084));
        tmp_i8 = *(int *)(g_unk_01047b00 + 0xcc);
        tmp_i11 = *(int *)(cgs + tmp_i8 * 0x1a4 + 0x9494);
        local_128 = (float *)0x26;
      }
      else {
        local_128 = (float *)0x8;
      }
      if (tmp_i11 == 2) {
        tmp_u9 = *(uint32_t *)(rankNames_Allies + *(int *)(cgs + tmp_i8 * 0x1a4 + 0x94c0) * 4);
      }
      else {
        tmp_u9 = *(uint32_t *)(rankNames_Axis + *(int *)(cgs + tmp_i8 * 0x1a4 + 0x94c0) * 4);
      }
      va("^7Following ^7%s ^7%s^7",tmp_u9,tmp_i8 * 0x1a4 + 0x10f9274);
      CG_Text_Paint_Ext_constprop_18
                ((float)(int)local_128,0x43060000,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
    }
    else {
      if (GHIDRA_FIELD(cgs, 27388, 4) != 5) {
        if (*(int *)(g_unk_01047b00 + 0x160) == 0) {
          if (-1 < *(int *)(g_unk_01047b00 + 0x164)) {
            va("^7Bonus Life! Deploying in ^3%d ^7seconds^7");
          }
        }
        else {
          va("^7Deploying in ^3%d ^7seconds^7");
        }
      }
      CG_Text_Paint_Ext_constprop_18(0x41000000,0x43020000,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
      if (*(int *)(g_unk_01047b00 + 0xcc) != g_unk_01047ac4) {
        tmp_u9 = BG_ClassnameForNumber
                          (*(uint32_t *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x94b8));
        tmp_i8 = *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4;
        if (*(int *)(cgs + tmp_i8 + 0x9494) == 2) {
          tmp_u13 = *(uint32_t *)(rankNames_Allies + *(int *)(cgs + tmp_i8 + 0x94c0) * 4);
        }
        else {
          tmp_u13 = *(uint32_t *)(rankNames_Axis + *(int *)(cgs + tmp_i8 + 0x94c0) * 4);
        }
        va("^7(Following %s %s ^7[%s])^7",tmp_u13,tmp_i8 + 0x10f9274,tmp_u9);
        CG_Text_Paint_Ext_constprop_18(0x41000000,0x430c0000,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
      }
    }
  }
  CG_HudPlacement(0);
  if (g_unk_010aac20 == 0) {
    if ((GHIDRA_FIELD(cgs, 33525356, 4) - 2 & 0xfffffffd) == 0) {
      if (cgs[0x2038e6c] != '\0') {
        tmp_u9 = va("^3Config:^7%s^7",0x3128ccc);
        tmp_i8 = CG_DrawStrlen(tmp_u9);
        CG_DrawStringExt(tmp_i8 * -6 + 0x154,0x3e,tmp_u9,&colorWhite,0,1,10,0xe,0);
      }
      if (GHIDRA_FIELD(cgs, 33525352, 4) == 1) {
        tmp_pc10 = "tag_player";
      }
      else {
        tmp_pc10 = "listplayers";
      }
      tmp_u9 = va("^3WARMUP:^7 Waiting on ^2%i^7 %s",GHIDRA_FIELD(cgs, 33525352, 4),tmp_pc10 + 4);
      tmp_i8 = CG_DrawStrlen(tmp_u9);
      CG_DrawStringExt(tmp_i8 * -6 + 0x154,0x56,tmp_u9,&colorWhite,0,1,10,0xe,0);
      if (((g_unk_01047aec == 0) && (*(int *)(g_unk_01047b00 + 0x158) != 3)) &&
         ((*(uint *)(g_unk_01047b00 + 0x38) & 0x5000) != 0x1000)) {
        tmp_u9 = BindingFromName("ready");
        Q_strncpyz(&local_9c,tmp_u9,0x20);
        tmp_i8 = Q_stricmp(&local_9c,"(???)");
        tmp_pc10 = "Type ^3\\ready^7 in the console to start";
        if (tmp_i8 != 0) {
          tmp_pc10 = (char *)va("Press ^3%s^7 to start",&local_9c);
        }
        tmp_i8 = CG_DrawStrlen(tmp_pc10);
        CG_DrawStringExt(0x145 - (tmp_i8 * 9) / 2,0x62,tmp_pc10,&colorWhite,0,1,9,0xb,0);
      }
    }
  }
  else {
    tmp_u21 = (g_unk_010aac20 - g_unk_010906e0) / 1000;
    if (tmp_u21 == 5) {
      if (prepAnnounced_12558 == 0) {
        if (GHIDRA_FIELD(cg_announcer, 12, 4) != 0) {
          if (GHIDRA_FIELD(cgs, 68908, 4) != 0) {
            trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 68908, 4));
          }
          Q_strncpyz(&g_unk_010ee064,"PREPARE TO FIGHT!",0x400);
          g_unk_010ee464 = 0x3f59999a;
          g_unk_010ee46c = 0x3f800000;
          g_unk_010ee470 = 0x3f800000;
          g_unk_010ee060 = g_unk_010906e0 + 0x5dc;
          g_unk_010ee468 = 0x5dc;
          g_unk_010ee478 = 1;
          g_unk_010ee474 = 0;
          g_unk_010ee47c = 0;
        }
        prepAnnounced_12558 = 1;
        toPrint_12559 = 4;
      }
LAB_0005e277:
      tmp_u9 = va("(WARMUP) Match begins in: %i");
      tmp_i8 = CG_DrawStrlen(tmp_u9);
      CG_DrawStringExt(tmp_i8 * -6 + 0x154,0x41,tmp_u9,&colorYellow,0,1,9,0xe,0);
    }
    else {
      prepAnnounced_12558 = 0;
      if (tmp_u21 < 5) {
        if (tmp_u21 == toPrint_12559) {
          tmp_i8 = va("%i");
          if ((tmp_i8 != 0) && (GHIDRA_FIELD(cg_announcer, 12, 4) != 0)) {
            Q_strncpyz(&g_unk_010ee064,tmp_i8,0x400);
            g_unk_010ee464 = 0x3f19999a;
            g_unk_010ee468 = 1000;
            g_unk_010ee46c = 0;
            g_unk_010ee060 = g_unk_010906e0 + 1000;
            g_unk_010ee470 = 0x3f800000;
            g_unk_010ee474 = 0;
            g_unk_010ee478 = 1;
            g_unk_010ee47c = 0x5a;
          }
          toPrint_12559 = toPrint_12559 - 1;
        }
LAB_0005d15c:
        if (4 < (int)tmp_u21) goto LAB_0005e277;
      }
      else if (-1 < (int)tmp_u21) goto LAB_0005d15c;
    }
    if (GHIDRA_FIELD(cgs, 27388, 4) == 3) {
      tmp_u9 = va("Stopwatch Round %i");
      tmp_u13 = CG_ConfigString(0xd);
      tmp_pc10 = (char *)Info_ValueForKey(tmp_u13);
      tmp_l14 = strtol(tmp_pc10,(char **)0x0,10);
      tmp_i8 = *(int *)(g_unk_01047b00 + 0x158);
      if (tmp_l14 == 0) {
        if (tmp_i8 == 1) {
          if (GHIDRA_FIELD(cgs, 33525344, 4) == 1) {
            tmp_pc22 = "Keep the Allies from beating the clock!";
            tmp_pc10 = "You have been switched to the Axis team";
          }
          else {
LAB_0005e9d2:
            tmp_pc22 = "";
            tmp_pc10 = "You are on the Axis team";
          }
        }
        else if (tmp_i8 == 2) {
          if (GHIDRA_FIELD(cgs, 33525344, 4) == 1) {
            tmp_pc22 = "Try to beat the clock!";
            tmp_pc10 = "You have been switched to the Allied team";
          }
          else {
LAB_0005e56f:
            tmp_pc22 = "";
            tmp_pc10 = "You are on the Allied team";
          }
        }
        else {
LAB_0005d1e7:
          tmp_pc10 = "";
          tmp_pc22 = tmp_pc10;
        }
      }
      else if (tmp_i8 == 1) {
        if (GHIDRA_FIELD(cgs, 33525344, 4) != 1) goto LAB_0005e9d2;
        tmp_pc22 = "Try to beat the clock!";
        tmp_pc10 = "You have been switched to the Axis team";
      }
      else {
        if (tmp_i8 != 2) goto LAB_0005d1e7;
        if (GHIDRA_FIELD(cgs, 33525344, 4) != 1) goto LAB_0005e56f;
        tmp_pc22 = "Keep the Axis from beating the clock!";
        tmp_pc10 = "You have been switched to the Allied team";
      }
      tmp_i8 = CG_DrawStrlen(tmp_u9);
      CG_DrawStringExt(0x140 - (tmp_i8 * 9) / 2,0x8c,tmp_u9,&colorWhite,0,1,9,0xb,0);
      tmp_i8 = CG_DrawStrlen(tmp_pc10);
      CG_DrawStringExt(0x140 - (tmp_i8 * 9) / 2,0xa0,tmp_pc10,&colorWhite,0,1,9,0xb,0);
      tmp_i8 = CG_DrawStrlen(tmp_pc22);
      CG_DrawStringExt(0x140 - (tmp_i8 * 9) / 2,0xb4,tmp_pc22,&colorWhite,0,1,9,0xb,0);
    }
  }
  if (g_unk_010aaed4 != 0) {
    CG_DrawObjectiveInfo();
  }
  nitmod_DrawArtilleryHint();
  if ((GHIDRA_FIELD(cg_descriptiveText, 12, 4) != 0) &&
     ((((*(uint *)(g_unk_01047b00 + 0x38) & 0x4000) != 0 || (*(int *)(g_unk_01047b00 + 0x158) == 3)) ||
      ((*(uint *)(g_unk_01047b00 + 0x38) & 0x1000) != 0)))) {
    CG_HudPlacement(1);
    if (1000 < g_unk_010906e0 - lastconfigGet_12520) {
      Controls_GetConfig();
      lastconfigGet_12520 = g_unk_010906e0;
    }
    tmp_pc10 = (char *)BindingFromName("openlimbomenu");
    tmp_i8 = Q_stricmp(tmp_pc10,"(openlimbomenu)");
    if (tmp_i8 == 0) {
      tmp_pc10 = "ESCAPE";
    }
    va("Press %s to open Limbo Menu",tmp_pc10);
    CG_Text_Paint_Ext_constprop_18(0x41000000,0x43160000,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
    tmp_u9 = BindingFromName("+attack");
    va("Press %s to follow next player",tmp_u9);
    CG_Text_Paint_Ext_constprop_18(0x41000000,0x431e0000,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
  }
  tmp_i8 = g_unk_01047b00;
  local_9c = 1.0;
  local_98 = 1.0;
  local_94 = 1.0;
  local_90 = 1.0;
  if (((*(int *)(g_unk_01047b00 + 0xfc) < 1) && ((*(byte *)(g_unk_01047b00 + 0x39) & 0x40) == 0)) &&
     (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3)) {
    CG_HudPlacement(1);
    if (GHIDRA_FIELD(cg_descriptiveText, 12, 4) == 0) {
      tmp_u9 = 0x42ec0000;
LAB_0005dc41:
      if (GHIDRA_FIELD(cgs, 27388, 4) != 5) {
        if (*(int *)(tmp_i8 + 0x160) != 0) {
          tmp_l23 = (long double)CG_CalculateReinfTime_Float(0);
          va("^7Reinforcements deploy in ^3%d ^7seconds.",(int)ROUND(tmp_l23));
        }
        CG_Text_Paint_Ext_constprop_18(0x41000000,tmp_u9,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
      }
    }
    else {
      CG_Text_Paint_Ext_constprop_18(0x41000000,0x42ec0000,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
      if ((GHIDRA_FIELD(cgs, 27388, 4) != 5) || ((*(byte *)(tmp_i8 + 0x96) & 0x80) != 0)) {
        CG_Text_Paint_Ext_constprop_18(0x41000000,0x43020000,0x3e4ccccd,0x3e4ccccd,7,0x110afec);
        tmp_u9 = 0x430e0000;
        goto LAB_0005dc41;
      }
    }
    trap_R_SetColor(0);
  }
  if (GHIDRA_FIELD(cg_drawCompass, 12, 4) == 0) {
    CG_DrawExpandedAutoMap();
  }
  else {
    CG_HudPlacement(1);
    local_124 = (float *)g_unk_01047b04;
    if (((g_unk_01047b04 == 0) || (g_unk_010906d8 != 0)) || (g_unk_010906d4 != 0)) {
      local_124 = (float *)g_unk_01047b00;
    }
    CG_DrawAutoMap();
    CG_DrawPic(0x42480000,0x43c10000,0x429c0000,0x429c0000,GHIDRA_FIELD(cgs, 68504, 4));
    tmp_l23 = (long double)
             AngleSubtract(((g_unk_010907b0 + 180.0) / 360.0 - 0.125) * 360.0,lastangle_12679 * 360.0)
    ;
    tmp_l23 = (tmp_l23 / (long double)360.0) * (long double)0.01 +
             (long double)anglespeed_12680 / (long double)1.08;
    anglespeed_12680 = (float)tmp_l23;
    tmp_l23 = (long double)Q_fabs((float)tmp_l23);
    if (tmp_l23 < (long double)1e-05) {
      anglespeed_12680 = 0.0;
    }
    lastangle_12679 = anglespeed_12680 + lastangle_12679;
    CG_DrawRotatedPic(0x42480000,0x43c10000,0x429c0000,0x429c0000,GHIDRA_FIELD(cgs, 68508, 4),lastangle_12679);
    local_128 = (float *)GHIDRA_FIELD(cgs, 27400, 4);
    if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
      tmp_i11 = 0;
      tmp_i8 = 0x31345d4;
      do {
        if (((g_unk_0109079c != tmp_i11) && (*(int *)(tmp_pu17 + 0x940c) != 0)) &&
           ((_DAT_01090828 == *(int *)(tmp_pu17 + 0x9494) &&
            (g_unk_010906e0 <= *(int *)(tmp_i8 + 0x1fc))))) {
          if (*(int *)(tmp_pu17 + 0x94a8) < 1) {
            *(int *)(tmp_i8 + 0x1fc) = g_unk_010906e0;
          }
          else {
            CG_DrawCompassIcon(0x42380000,0x43bf0000,0x42ac0000,0x42ac0000,&g_unk_01090710,tmp_i8,
                               *(uint32_t *)(tmp_i8 + 0x1f8),0x3f800000,0xe);
            local_128 = (float *)GHIDRA_FIELD(cgs, 27400, 4);
          }
        }
        tmp_i11 = tmp_i11 + 1;
        tmp_pu17 = tmp_pu17 + 0x1a4;
        tmp_i8 = tmp_i8 + 0xaf8;
      } while (tmp_i11 < (int)local_128);
    }
    if (g_unk_010907e0 == 1) {
      tmp_i8 = *(int *)((int)local_124 + 0x5d8);
      if (tmp_i8 < 1) goto LAB_0005bb20;
      tmp_i11 = (int)local_124 + 0x5f4;
      tmp_i16 = 0;
      do {
        if (((*(int *)(tmp_i11 + -0x14) == 1) && ((*(byte *)(tmp_i11 + -0x10) & 1) != 0)) &&
           ((*(int *)(tmp_i11 + -0x18) == *(int *)(tmp_i11 + 0x94) &&
            ((tmp_i18 = *(int *)(tmp_i11 + -0x18) * 0x1a4, *(int *)(cgs + tmp_i18 + 0x940c) != 0 &&
             (_DAT_01090828 == *(int *)(cgs + tmp_i18 + 0x9494))))))) {
          CG_DrawCompassIcon(0x42380000,0x43bf0000,0x42ac0000,0x42ac0000,&g_unk_01090710,tmp_i11,
                             GHIDRA_FIELD(cgs, 67980, 4),0x3f800000,0xe);
          tmp_i8 = *(int *)((int)local_124 + 0x5d8);
        }
        tmp_i16 = tmp_i16 + 1;
        tmp_i11 = tmp_i11 + 0x120;
      } while (tmp_i16 < tmp_i8);
    }
    else {
      tmp_i8 = *(int *)((int)local_124 + 0x5d8);
    }
    if (0 < tmp_i8) {
      tmp_i11 = (int)local_124 + 0x5f4;
      tmp_i16 = 0;
      do {
        if ((*(int *)(tmp_i11 + -0x14) == 1) && ((*(byte *)(tmp_i11 + -0x10) & 1) == 0)) {
          tmp_i18 = *(int *)(tmp_i11 + 0x94) * 0x1a4;
          if ((*(int *)(cgs + tmp_i18 + 0x940c) != 0) &&
             (_DAT_01090828 == *(int *)(cgs + tmp_i18 + 0x9494))) {
            tmp_i8 = CG_IsOnSameFireteam(g_unk_01047ac4,*(int *)(tmp_i11 + 0x94));
            if (tmp_i8 == 0) {
              tmp_i8 = *(int *)((int)local_124 + 0x5d8);
            }
            else {
              CG_DrawCompassIcon(0x42380000,0x43bf0000,0x42ac0000,0x42ac0000,&g_unk_01090710,tmp_i11,
                                 GHIDRA_FIELD(cgs, 68488, 4),0x3f800000,0xe);
              tmp_i8 = *(int *)((int)local_124 + 0x5d8);
            }
          }
        }
        tmp_i16 = tmp_i16 + 1;
        tmp_i11 = tmp_i11 + 0x120;
      } while (tmp_i16 < tmp_i8);
    }
  }
LAB_0005bb20:
  if (g_unk_010abd7c != 0) {
    CG_Fireteams_Draw();
  }
  CG_DrawAnnouncer();
  nitmod_DrawKillPrint();
  nitmod_SpreePrint();
  nitrox_DrawPopup();
  CG_DrawOverlays();
  CG_windowDraw();
  if ((((*(byte *)(g_unk_01047b00 + 0x39) & 0x40) == 0) &&
      (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3)) || (g_unk_010abd78 == 0)) {
    local_9c = 1.0;
    local_98 = 1.0;
    local_94 = 1.0;
    local_90 = 1.0;
    tmp_i8 = _DAT_010aad64;
    if (g_unk_010906f4 == 0) {
      if (*(int *)(g_unk_01047b00 + 0x450) == 0) {
        tmp_i8 = g_unk_010906e0;
      }
      else {
        tmp_f6 = (float)((*(int *)(g_unk_01047b00 + 0x450) - g_unk_010906e0) + 1000) / 1000.0;
        tmp_i8 = g_unk_010906e0;
        if (0.0 < tmp_f6) {
          if (1.0 <= tmp_f6) {
            tmp_f6 = 1.0;
          }
          tmp_f7 = (float)(g_unk_010906e0 - _DAT_010aad64) / 1000.0;
          if ((0.0 <= tmp_f7) && (tmp_f7 < 1.0)) {
            tmp_f6 = tmp_f7;
          }
          tmp_d24 = sin((double)((float)((g_unk_010906e0 / 10) % 1000) / 1000.0));
          tmp_f7 = (float)tmp_d24 * 0.5 + 0.5;
          if (tmp_f7 < tmp_f6) {
            tmp_f6 = tmp_f7;
          }
          local_9c = tmp_f6;
          local_98 = tmp_f6;
          local_94 = tmp_f6;
          local_90 = tmp_f6;
          trap_R_SetColor(&local_9c);
          CG_DrawPicFullScreen
                    (0xc1200000,0xc1200000,0x44228000,0x43f50000,
                     *(uint32_t *)(cgs + ((g_unk_010906e0 / 0x32) % 0x10) * 4 + 0x10bdc));
          trap_R_SetColor(0);
          trap_S_AddLoopingSound
                    (g_unk_01047b00 + 0x40,&vec3_origin,GHIDRA_FIELD(cgs, 69516, 4),(int)ROUND(tmp_f6 * 255.0),0);
          trap_S_AddLoopingSound
                    (g_unk_01047b00 + 0x40,&vec3_origin,GHIDRA_FIELD(cgs, 69532, 4),(int)ROUND(tmp_f6 * 255.0),0);
          tmp_i8 = _DAT_010aad64;
        }
      }
    }
    _DAT_010aad64 = tmp_i8;
    if ((g_unk_01047b00 != 0) && ((float)g_unk_010906e0 < g_unk_010aad40)) {
      tmp_f6 = ABS(((g_unk_010aad40 - (float)g_unk_010906e0) / 500.0) * g_unk_010aad44);
      if (5.0 < tmp_f6) {
        tmp_f6 = 0.7;
      }
      else {
        tmp_f6 = (tmp_f6 / 5.0) * 0.7;
      }
      local_9c = 0.2;
      local_98 = 0.0;
      local_94 = 0.0;
      if ((float)GHIDRA_FIELD(cg_bloodFlash, 8, 4) <= 1.0) {
        local_90 = (float)GHIDRA_FIELD(cg_bloodFlash, 8, 4);
        if ((float)GHIDRA_FIELD(cg_bloodFlash, 8, 4) < 0.0) {
          local_90 = 0.0;
        }
      }
      else {
        local_90 = 1.0;
      }
      local_90 = local_90 * tmp_f6;
      CG_FillRectFullScreen(0xc1200000,0xc1200000,0x44228000,0x43f50000,&local_9c);
    }
  }
  if (((GHIDRA_FIELD(cl_demorecording, 12, 4) != 0) || (GHIDRA_FIELD(cl_waverecording, 12, 4) != 0)) &&
     (GHIDRA_FIELD(cg_recording_statusline, 12, 4) != 0)) {
    CG_DrawDemoRecording_part_3();
  }
  nitrox_DrawGlobalStats();
  return;
}

void CG_AddAnnouncer(int param_1,int param_2,uint32_t param_3,int param_4,uint32_t param_5,
                    uint32_t param_6,uint32_t param_7,uint32_t param_8,uint32_t param_9)

{
  if (GHIDRA_FIELD(cg_announcer, 12, 4) != 0) {
    if (param_2 != 0) {
      trap_S_StartLocalSound(param_2,7);
    }
    if (param_1 != 0) {
      Q_strncpyz(&g_unk_010ee064,param_1,0x400);
      g_unk_010ee060 = param_4 + g_unk_010906e0;
      g_unk_010ee464 = param_3;
      g_unk_010ee468 = param_4;
      g_unk_010ee46c = param_5;
      g_unk_010ee470 = param_6;
      g_unk_010ee478 = param_8;
      g_unk_010ee474 = param_7;
      g_unk_010ee47c = param_9;
    }
  }
  return;
}

void CG_DrawStringExt3_constprop_0(int param_1,int param_2,byte *param_3,uint32_t *param_4)
{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  byte tmp_b5;
  int tmp_i6;
  uint tmp_u7;
  byte *tmp_pb8;
  int tmp_i9;
  int local_48;
  int local_44;
  int local_3c;
  int local_38;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  if (*param_3 == 0) {
    local_44 = 0;
  }
  else {
    local_44 = 0;
    tmp_pb8 = param_3;
    do {
      tmp_pb8 = tmp_pb8 + 1;
      local_44 = local_44 + 0x10;
    } while (*tmp_pb8 != 0);
  }
  local_44 = param_1 - local_44;
  local_24 = 0;
  local_28 = 0;
  local_2c = 0;
  local_20 = param_4[3];
  trap_R_SetColor(&local_2c);
  tmp_i9 = 0;
  local_48 = local_44;
  for (tmp_pb8 = param_3; tmp_b5 = *tmp_pb8, tmp_b5 != 0; tmp_pb8 = tmp_pb8 + 1) {
    while( true ) {
      if (0x7ffe < tmp_i9) goto LAB_0005ee80;
      if (tmp_b5 != 0x5e) {
        tmp_u7 = (uint)tmp_b5;
        if (tmp_u7 != 0x20) goto LAB_0005ed84;
        goto LAB_0005ed40;
      }
      if ((tmp_pb8[1] == 0) || (tmp_pb8[1] == 0x5e)) break;
      tmp_pb8 = tmp_pb8 + 2;
      tmp_b5 = *tmp_pb8;
      if (tmp_b5 == 0) goto LAB_0005ee80;
    }
    tmp_u7 = 0x5e;
LAB_0005ed84:
    local_38 = local_48 + 2;
    local_3c = param_2 + 2;
    tmp_f2 = (float)local_38;
    if (cg_hudPlacement == 1) {
      tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else if (cg_hudPlacement == 2) {
      tmp_f2 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else {
      tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
    tmp_f3 = (float)((int)tmp_u7 >> 4) * 0.0625;
    tmp_f4 = (float)(short)(char)(tmp_b5 & 0xf) * 0.0625;
    trap_R_DrawStretchPic
              (tmp_f2,(float)GHIDRA_FIELD(cgs, 27368, 4) * (float)local_3c,(float)GHIDRA_FIELD(cgs, 27364, 4) * 16.0,
               (float)GHIDRA_FIELD(cgs, 27368, 4) * 16.0,tmp_f4,tmp_f3,tmp_f4 + 0.0625,tmp_f3 + 0.0625,GHIDRA_FIELD(cgs, 67820, 4));
LAB_0005ed40:
    local_48 = local_48 + 0x10;
    tmp_i9 = tmp_i9 + 1;
  }
LAB_0005ee80:
  tmp_i9 = 0;
  trap_R_SetColor(param_4);
  for (; tmp_b5 = *param_3, tmp_b5 != 0; param_3 = param_3 + 1) {
    while( true ) {
      if (0x7ffe < tmp_i9) goto LAB_0005f010;
      if (tmp_b5 != 0x5e) {
        tmp_u7 = (uint)tmp_b5;
        if (tmp_u7 == 0x20) goto LAB_0005eea0;
        goto LAB_0005eecf;
      }
      tmp_b1 = param_3[1];
      if ((tmp_b1 == 0) || (tmp_b1 == 0x5e)) break;
      if (tmp_b1 == 0x2a) {
        local_2c = *param_4;
        local_28 = param_4[1];
        local_24 = param_4[2];
        local_20 = param_4[3];
      }
      else {
        tmp_i6 = ((int)(char)tmp_b1 - 0x30U & 0x1f) * 0x10;
        local_2c = *(uint32_t *)(g_color_table + tmp_i6);
        local_28 = *(uint32_t *)(g_color_table + tmp_i6 + 4);
        local_24 = *(uint32_t *)(g_color_table + tmp_i6 + 8);
        local_20 = param_4[3];
      }
      param_3 = param_3 + 2;
      trap_R_SetColor(&local_2c);
      tmp_b5 = *param_3;
      if (tmp_b5 == 0) goto LAB_0005f010;
    }
    tmp_u7 = 0x5e;
LAB_0005eecf:
    tmp_f2 = (float)local_44;
    if (cg_hudPlacement == 1) {
      tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else if (cg_hudPlacement == 2) {
      tmp_f2 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else {
      tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
    tmp_f3 = (float)((int)tmp_u7 >> 4) * 0.0625;
    tmp_f4 = (float)(short)(char)(tmp_b5 & 0xf) * 0.0625;
    trap_R_DrawStretchPic
              (tmp_f2,(float)GHIDRA_FIELD(cgs, 27368, 4) * (float)param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * 16.0,
               (float)GHIDRA_FIELD(cgs, 27368, 4) * 16.0,tmp_f4,tmp_f3,tmp_f4 + 0.0625,tmp_f3 + 0.0625,GHIDRA_FIELD(cgs, 67820, 4));
LAB_0005eea0:
    local_44 = local_44 + 0x10;
    tmp_i9 = tmp_i9 + 1;
  }
LAB_0005f010:
  trap_R_SetColor(0);
  return;
}

void CG_HudPlacement(uint32_t param_1)
{
  cg_hudPlacement = param_1;
  return;
}

void CG_FillRect(float param_1,float param_2,float param_3,float param_4,uint32_t param_5)
{
  trap_R_SetColor(param_5);
  if (cg_hudPlacement == 1) {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else if (cg_hudPlacement == 2) {
    param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
  }
  trap_R_DrawStretchPic
            (param_1,(float)GHIDRA_FIELD(cgs, 27368, 4) * param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * param_3,
             param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4),0,0,0,0x3f800000,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_SetColor(0);
  return;
}

void CG_FillRectGradient(float param_1,float param_2,float param_3,float param_4,uint32_t param_5,
                        uint32_t param_6,uint32_t param_7)

{
  trap_R_SetColor(param_5);
  if (cg_hudPlacement == 1) {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else if (cg_hudPlacement == 2) {
    param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
  }
  trap_R_DrawStretchPicGradient
            (param_1,(float)GHIDRA_FIELD(cgs, 27368, 4) * param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * param_3,
             param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4),0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4),param_6,param_7);
  trap_R_SetColor(0);
  return;
}

void CG_FilledBar(float param_1,float param_2,float param_3,float param_4,float *param_5,
                 float *param_6,uint32_t *param_7,float param_8,uint param_9)

{
  float tmp_f1;
  float tmp_f2;
  uint tmp_u3;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_f1 = 1.0;
  local_3c = 0x3f800000;
  local_38 = 0x3f800000;
  local_34 = 0x3f800000;
  local_30 = 0x3e800000;
  if ((param_8 <= 1.0) && (tmp_f1 = 0.0, 0.0 <= param_8)) {
    tmp_f1 = param_8;
  }
  if (((param_9 >> 4 & 1) != 0) && (param_7 != (uint32_t *)0x0)) {
    local_3c = *param_7;
    local_38 = param_7[1];
    local_34 = param_7[2];
    local_30 = param_7[3];
  }
  tmp_u3 = param_9 & 0x100;
  if (tmp_u3 != 0) {
    tmp_f2 = 1.0 - tmp_f1;
    local_2c = *param_6 * tmp_f1 + *param_5 * tmp_f2;
    local_28 = param_6[1] * tmp_f1 + param_5[1] * tmp_f2;
    local_24 = param_6[2] * tmp_f1 + param_5[2] * tmp_f2;
    local_20 = param_6[3] * tmp_f1 + tmp_f2 * param_5[3];
  }
  if (((param_9 >> 4 & 1) != 0) &&
     (CG_FillRect(param_1,param_2,param_3,param_4,&local_3c), (param_9 & 0x40) == 0)) {
    if ((param_9 & 0x20) == 0) {
      param_1 = param_1 + 2.0;
      param_2 = param_2 + 2.0;
      param_3 = param_3 - 4.0;
      param_4 = param_4 - 4.0;
    }
    else {
      param_2 = param_2 + 6.0;
      param_4 = param_4 - 12.0;
    }
  }
  if ((param_9 & 4) == 0) {
    if ((param_9 & 1) == 0) {
      if ((param_9 & 2) != 0) {
        param_1 = (1.0 - tmp_f1) * param_3 * 0.5 + param_1;
      }
    }
    else {
      param_1 = (1.0 - tmp_f1) * param_3 + param_1;
    }
    if (tmp_u3 != 0) {
      CG_FillRect(param_1,param_2,tmp_f1 * param_3,param_4,&local_2c);
      return;
    }
    param_3 = tmp_f1 * param_3;
  }
  else {
    if ((param_9 & 1) == 0) {
      if ((param_9 & 2) != 0) {
        param_2 = (1.0 - tmp_f1) * param_4 * 0.5 + param_2;
      }
    }
    else {
      param_2 = (1.0 - tmp_f1) * param_4 + param_2;
    }
    if (tmp_u3 != 0) {
      CG_FillRect(param_1,param_2,param_3,tmp_f1 * param_4,&local_2c);
      return;
    }
    param_4 = tmp_f1 * param_4;
  }
  CG_FillRect(param_1,param_2,param_3,param_4,param_5);
  return;
}

void CG_DrawSides(float param_1,float param_2,float param_3,float param_4,float param_5)
{
  param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  if (cg_hudPlacement != 1) {
    if (cg_hudPlacement == 2) {
      param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + param_1;
    }
    else {
      param_1 = param_1 + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
  }
  param_2 = (float)GHIDRA_FIELD(cgs, 27368, 4) * param_2;
  param_3 = param_3 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  param_4 = (float)GHIDRA_FIELD(cgs, 27368, 4) * param_4;
  param_5 = (float)GHIDRA_FIELD(cgs, 27364, 4) * param_5;
  trap_R_DrawStretchPic(param_1,param_2,param_5,param_4,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_DrawStretchPic((param_1 + param_3) - param_5,param_2,param_5,param_4,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4))
  ;
  return;
}

void CG_DrawTopBottom(float param_1,float param_2,float param_3,float param_4,float param_5)
{
  param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  if (cg_hudPlacement != 1) {
    if (cg_hudPlacement == 2) {
      param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + param_1;
    }
    else {
      param_1 = param_1 + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
  }
  param_2 = param_2 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  param_3 = (float)GHIDRA_FIELD(cgs, 27364, 4) * param_3;
  param_4 = param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  param_5 = (float)GHIDRA_FIELD(cgs, 27368, 4) * param_5;
  trap_R_DrawStretchPic(param_1,param_2,param_3,param_5,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_DrawStretchPic(param_1,(param_2 + param_4) - param_5,param_3,param_5,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4))
  ;
  return;
}

void CG_DrawSides_NoScale(float param_1,float param_2,float param_3,float param_4,float param_5)
{
  if (cg_hudPlacement == 1) {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else if (cg_hudPlacement == 2) {
    param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
  }
  param_2 = (float)GHIDRA_FIELD(cgs, 27368, 4) * param_2;
  param_3 = (float)GHIDRA_FIELD(cgs, 27364, 4) * param_3;
  param_4 = (float)GHIDRA_FIELD(cgs, 27368, 4) * param_4;
  trap_R_DrawStretchPic(param_1,param_2,param_5,param_4,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_DrawStretchPic((param_1 + param_3) - param_5,param_2,param_5,param_4,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4))
  ;
  return;
}

void CG_DrawTopBottom_NoScale(float param_1,float param_2,float param_3,float param_4,float param_5)
{
  if (cg_hudPlacement == 1) {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else if (cg_hudPlacement == 2) {
    param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
  }
  param_2 = (float)GHIDRA_FIELD(cgs, 27368, 4) * param_2;
  param_3 = (float)GHIDRA_FIELD(cgs, 27364, 4) * param_3;
  param_4 = (float)GHIDRA_FIELD(cgs, 27368, 4) * param_4;
  trap_R_DrawStretchPic(param_1,param_2,param_3,param_5,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_DrawStretchPic(param_1,(param_2 + param_4) - param_5,param_3,param_5,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4))
  ;
  return;
}

void CG_DrawRect(float param_1,float param_2,float param_3,float param_4,float param_5,
                uint32_t param_6)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  
  trap_R_SetColor(param_6);
  tmp_f1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  if (cg_hudPlacement != 1) {
    if (cg_hudPlacement == 2) {
      tmp_f1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f1;
    }
    else {
      tmp_f1 = tmp_f1 + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
  }
  tmp_f3 = param_2 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  tmp_f2 = (float)GHIDRA_FIELD(cgs, 27364, 4) * param_3;
  tmp_f4 = param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  tmp_f5 = (float)GHIDRA_FIELD(cgs, 27368, 4) * param_5;
  trap_R_DrawStretchPic(tmp_f1,tmp_f3,tmp_f2,tmp_f5,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_DrawStretchPic(tmp_f1,(tmp_f3 + tmp_f4) - tmp_f5,tmp_f2,tmp_f5,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  if (cg_hudPlacement != 1) {
    if (cg_hudPlacement == 2) {
      param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + param_1;
    }
    else {
      param_1 = param_1 + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
  }
  param_2 = param_2 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  param_3 = param_3 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  param_4 = param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  param_5 = (float)GHIDRA_FIELD(cgs, 27364, 4) * param_5;
  trap_R_DrawStretchPic(param_1,param_2,param_5,param_4,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_DrawStretchPic((param_1 + param_3) - param_5,param_2,param_5,param_4,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4))
  ;
  trap_R_SetColor(0);
  return;
}

void CG_DrawRect_FixedBorder
               (float param_1,float param_2,float param_3,float param_4,int param_5,
               uint32_t param_6)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  
  trap_R_SetColor(param_6);
  tmp_f1 = (float)param_5;
  tmp_f2 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  if (cg_hudPlacement != 1) {
    if (cg_hudPlacement == 2) {
      tmp_f2 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f2;
    }
    else {
      tmp_f2 = tmp_f2 + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
  }
  tmp_f4 = param_2 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  tmp_f3 = (float)GHIDRA_FIELD(cgs, 27364, 4) * param_3;
  tmp_f5 = param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  trap_R_DrawStretchPic(tmp_f2,tmp_f4,tmp_f3,tmp_f1,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_DrawStretchPic(tmp_f2,(tmp_f4 + tmp_f5) - tmp_f1,tmp_f3,tmp_f1,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  if (cg_hudPlacement == 1) {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else if (cg_hudPlacement == 2) {
    param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
  }
  param_2 = param_2 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  param_3 = (float)GHIDRA_FIELD(cgs, 27364, 4) * param_3;
  param_4 = param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  trap_R_DrawStretchPic(param_1,param_2,tmp_f1,param_4,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_DrawStretchPic((param_1 + param_3) - tmp_f1,param_2,tmp_f1,param_4,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_SetColor(0);
  return;
}

void CG_DrawPicST(float param_1,float param_2,float param_3,float param_4,uint32_t param_5,
                 uint32_t param_6,uint32_t param_7,uint32_t param_8,uint32_t param_9)

{
  if (cg_hudPlacement == 1) {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else if (cg_hudPlacement == 2) {
    param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
  }
  trap_R_DrawStretchPic
            (param_1,(float)GHIDRA_FIELD(cgs, 27368, 4) * param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * param_3,
             param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4),param_5,param_6,param_7,param_8,param_9);
  return;
}

void CG_DrawPic(float param_1,float param_2,float param_3,float param_4,uint32_t param_5)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  
  if (param_3 < 0.0) {
    param_3 = -param_3;
    tmp_u2 = 0;
    tmp_u4 = 0x3f800000;
  }
  else {
    tmp_u2 = 0x3f800000;
    tmp_u4 = 0;
  }
  if (param_4 < 0.0) {
    param_4 = -param_4;
    tmp_u1 = 0;
    if (cg_hudPlacement == 1) {
      tmp_u3 = 0x3f800000;
      goto LAB_000604c5;
    }
    tmp_u3 = 0x3f800000;
    tmp_u1 = 0;
  }
  else {
    tmp_u1 = 0x3f800000;
    tmp_u3 = 0;
    if (cg_hudPlacement == 1) {
LAB_000604c5:
      param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
      goto LAB_00060457;
    }
  }
  if (cg_hudPlacement == 2) {
    param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
  }
LAB_00060457:
  trap_R_DrawStretchPic
            (param_1,(float)GHIDRA_FIELD(cgs, 27368, 4) * param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * param_3,
             param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4),tmp_u4,tmp_u3,tmp_u2,tmp_u1,param_5);
  return;
}

void CG_DrawRotatedPic(float param_1,float param_2,float param_3,float param_4,uint32_t param_5,
                      uint32_t param_6)

{
  if (cg_hudPlacement == 1) {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else if (cg_hudPlacement == 2) {
    param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else {
    param_1 = param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
  }
  trap_R_DrawRotatedPic
            (param_1,(float)GHIDRA_FIELD(cgs, 27368, 4) * param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * param_3,
             param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4),0,0,0x3f800000,0x3f800000,param_5,param_6);
  return;
}

void CG_DrawChar(int param_1,int param_2,int param_3,int param_4,uint param_5)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  
  if ((param_5 & 0xff) == 0x20) {
    return;
  }
  if (cg_hudPlacement == 1) {
    tmp_f1 = (float)param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else {
    tmp_f1 = (float)param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    if (cg_hudPlacement == 2) {
      tmp_f1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f1;
    }
    else {
      tmp_f1 = tmp_f1 + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
  }
  tmp_f2 = (float)((int)(param_5 & 0xff) >> 4) * 0.0625;
  tmp_f3 = (float)(param_5 & 0xf) * 0.0625;
  trap_R_DrawStretchPic
            (tmp_f1,(float)GHIDRA_FIELD(cgs, 27368, 4) * (float)param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * (float)param_3,
             (float)param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4),tmp_f3,tmp_f2,tmp_f3 + 0.0625,tmp_f2 + 0.0625,
             GHIDRA_FIELD(cgs, 67816, 4));
  return;
}

void CG_DrawChar2(int param_1,int param_2,int param_3,int param_4,uint param_5)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  
  if ((param_5 & 0xff) == 0x20) {
    return;
  }
  if (cg_hudPlacement == 1) {
    tmp_f1 = (float)param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else {
    tmp_f1 = (float)param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    if (cg_hudPlacement == 2) {
      tmp_f1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f1;
    }
    else {
      tmp_f1 = tmp_f1 + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
  }
  tmp_f2 = (float)((int)(param_5 & 0xff) >> 4) * 0.0625;
  tmp_f3 = (float)(param_5 & 0xf) * 0.0625;
  trap_R_DrawStretchPic
            (tmp_f1,(float)GHIDRA_FIELD(cgs, 27368, 4) * (float)param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * (float)param_3,
             (float)param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4),tmp_f3,tmp_f2,tmp_f3 + 0.0625,tmp_f2 + 0.0625,
             GHIDRA_FIELD(cgs, 67820, 4));
  return;
}

void CG_DrawStringExt(int param_1,int param_2,byte *param_3,uint32_t *param_4,int param_5,
                     int param_6,int param_7,int param_8,int param_9)

{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  byte tmp_b5;
  int tmp_i6;
  uint tmp_u7;
  int tmp_i8;
  byte *tmp_pb9;
  int local_38;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  if (param_9 < 1) {
    param_9 = 0x7fff;
  }
  if (param_6 != 0) {
    local_24 = 0;
    local_28 = 0;
    local_2c = 0;
    local_20 = param_4[3];
    trap_R_SetColor(&local_2c);
    local_38 = 0;
    tmp_pb9 = param_3;
    tmp_i8 = param_1;
    while( true ) {
      tmp_b5 = *tmp_pb9;
      if ((tmp_b5 == 0) || (param_9 <= local_38)) break;
      if ((tmp_b5 == 0x5e) && ((tmp_pb9[1] != 0 && (tmp_pb9[1] != 0x5e)))) {
        tmp_pb9 = tmp_pb9 + 2;
      }
      else {
        tmp_pb9 = tmp_pb9 + 1;
        CG_DrawChar(tmp_i8 + 1,param_2 + 1,param_7,param_8,(int)(char)tmp_b5);
        local_38 = local_38 + 1;
        tmp_i8 = tmp_i8 + param_7;
      }
    }
  }
  tmp_i8 = 0;
  trap_R_SetColor(param_4);
  for (; tmp_b5 = *param_3, tmp_b5 != 0; param_3 = param_3 + 1) {
    while( true ) {
      if (param_9 <= tmp_i8) goto LAB_000609f0;
      if (tmp_b5 != 0x5e) {
        tmp_u7 = (uint)tmp_b5;
        if (tmp_u7 == 0x20) goto LAB_00060850;
        goto LAB_00060886;
      }
      tmp_b1 = param_3[1];
      if ((tmp_b1 == 0) || (tmp_b1 == 0x5e)) break;
      if (param_5 == 0) {
        if (tmp_b1 == 0x2a) {
          local_2c = *param_4;
          local_28 = param_4[1];
          local_24 = param_4[2];
          local_20 = param_4[3];
        }
        else {
          tmp_i6 = ((int)(char)tmp_b1 - 0x30U & 0x1f) * 0x10;
          local_2c = *(uint32_t *)(g_color_table + tmp_i6);
          local_28 = *(uint32_t *)(g_color_table + tmp_i6 + 4);
          local_24 = *(uint32_t *)(g_color_table + tmp_i6 + 8);
          local_20 = param_4[3];
        }
        trap_R_SetColor(&local_2c);
        *param_4 = local_2c;
        param_4[1] = local_28;
        param_4[2] = local_24;
        param_4[3] = local_20;
      }
      param_3 = param_3 + 2;
      tmp_b5 = *param_3;
      if (tmp_b5 == 0) goto LAB_000609f0;
    }
    tmp_u7 = 0x5e;
LAB_00060886:
    tmp_f2 = (float)param_1;
    if (cg_hudPlacement == 1) {
      tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else if (cg_hudPlacement == 2) {
      tmp_f2 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else {
      tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
    tmp_f3 = (float)((int)tmp_u7 >> 4) * 0.0625;
    tmp_f4 = (float)(short)(char)(tmp_b5 & 0xf) * 0.0625;
    trap_R_DrawStretchPic
              (tmp_f2,(float)GHIDRA_FIELD(cgs, 27368, 4) * (float)param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * (float)param_7,
               (float)param_8 * (float)GHIDRA_FIELD(cgs, 27368, 4),tmp_f4,tmp_f3,tmp_f4 + 0.0625,tmp_f3 + 0.0625,
               GHIDRA_FIELD(cgs, 67816, 4));
LAB_00060850:
    tmp_i8 = tmp_i8 + 1;
    param_1 = param_1 + param_7;
  }
LAB_000609f0:
  trap_R_SetColor(0);
  return;
}

void CG_DrawStringExt_Shadow
               (int param_1,int param_2,byte *param_3,uint32_t *param_4,int param_5,int param_6,
               int param_7,int param_8,int param_9)

{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  byte tmp_b5;
  int tmp_i6;
  uint tmp_u7;
  int tmp_i8;
  byte *tmp_pb9;
  int local_38;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  if (param_9 < 1) {
    param_9 = 0x7fff;
  }
  if (param_6 != 0) {
    local_24 = 0;
    local_28 = 0;
    local_2c = 0;
    local_20 = param_4[3];
    trap_R_SetColor(&local_2c);
    tmp_i8 = param_2 + 1 + (uint)(0xb < param_8);
    local_38 = 0;
    tmp_i6 = param_1;
    tmp_pb9 = param_3;
    if (param_7 < 0xc) {
      while( true ) {
        tmp_b5 = *tmp_pb9;
        if ((tmp_b5 == 0) || (param_9 <= local_38)) break;
        if ((tmp_b5 == 0x5e) && ((tmp_pb9[1] != 0 && (tmp_pb9[1] != 0x5e)))) {
          tmp_pb9 = tmp_pb9 + 2;
        }
        else {
          tmp_pb9 = tmp_pb9 + 1;
          CG_DrawChar2(tmp_i6 + 1,tmp_i8,param_7,param_8,(int)(char)tmp_b5);
          local_38 = local_38 + 1;
          tmp_i6 = tmp_i6 + param_7;
        }
      }
    }
    else {
      while( true ) {
        tmp_b5 = *tmp_pb9;
        if ((tmp_b5 == 0) || (param_9 <= local_38)) break;
        if ((tmp_b5 == 0x5e) && ((tmp_pb9[1] != 0 && (tmp_pb9[1] != 0x5e)))) {
          tmp_pb9 = tmp_pb9 + 2;
        }
        else {
          CG_DrawChar2(tmp_i6 + 2,tmp_i8,param_7,param_8,(int)(char)tmp_b5);
          local_38 = local_38 + 1;
          tmp_i6 = tmp_i6 + param_7;
          tmp_pb9 = tmp_pb9 + 1;
        }
      }
    }
  }
  tmp_i8 = 0;
  trap_R_SetColor(param_4);
  for (; tmp_b5 = *param_3, tmp_b5 != 0; param_3 = param_3 + 1) {
    while( true ) {
      if (param_9 <= tmp_i8) goto LAB_00060d20;
      if (tmp_b5 != 0x5e) {
        tmp_u7 = (uint)tmp_b5;
        if (tmp_u7 == 0x20) goto LAB_00060ba0;
        goto LAB_00060bd5;
      }
      tmp_b1 = param_3[1];
      if ((tmp_b1 == 0) || (tmp_b1 == 0x5e)) break;
      if (param_5 == 0) {
        if (tmp_b1 == 0x2a) {
          local_2c = *param_4;
          local_28 = param_4[1];
          local_24 = param_4[2];
          local_20 = param_4[3];
        }
        else {
          tmp_i6 = ((int)(char)tmp_b1 - 0x30U & 0x1f) * 0x10;
          local_2c = *(uint32_t *)(g_color_table + tmp_i6);
          local_28 = *(uint32_t *)(g_color_table + tmp_i6 + 4);
          local_24 = *(uint32_t *)(g_color_table + tmp_i6 + 8);
          local_20 = param_4[3];
        }
        trap_R_SetColor(&local_2c);
      }
      param_3 = param_3 + 2;
      tmp_b5 = *param_3;
      if (tmp_b5 == 0) goto LAB_00060d20;
    }
    tmp_u7 = 0x5e;
LAB_00060bd5:
    tmp_f2 = (float)param_1;
    if (cg_hudPlacement == 1) {
      tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else if (cg_hudPlacement == 2) {
      tmp_f2 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else {
      tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
    tmp_f3 = (float)((int)tmp_u7 >> 4) * 0.0625;
    tmp_f4 = (float)(short)(char)(tmp_b5 & 0xf) * 0.0625;
    trap_R_DrawStretchPic
              (tmp_f2,(float)GHIDRA_FIELD(cgs, 27368, 4) * (float)param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * (float)param_7,
               (float)param_8 * (float)GHIDRA_FIELD(cgs, 27368, 4),tmp_f4,tmp_f3,tmp_f4 + 0.0625,tmp_f3 + 0.0625,
               GHIDRA_FIELD(cgs, 67820, 4));
LAB_00060ba0:
    tmp_i8 = tmp_i8 + 1;
    param_1 = param_1 + param_7;
  }
LAB_00060d20:
  trap_R_SetColor(0);
  return;
}

void CG_DrawStringExt2(void)
{
  CG_DrawStringExt_Shadow();
  return;
}

void CG_DrawStringExt3(int param_1,int param_2,byte *param_3,uint32_t *param_4,int param_5,
                      int param_6,int param_7,int param_8,int param_9)

{
  int tmp_i1;
  byte tmp_b2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  byte tmp_b6;
  int tmp_i7;
  byte *tmp_pb8;
  int tmp_i9;
  uint tmp_u10;
  int tmp_i11;
  int local_3c;
  int local_38;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  tmp_i7 = 0x7fff;
  if (0 < param_9) {
    tmp_i7 = param_9;
  }
  if (*param_3 == 0) {
    local_3c = 0;
  }
  else {
    local_3c = 0;
    tmp_pb8 = param_3;
    do {
      tmp_pb8 = tmp_pb8 + 1;
      local_3c = local_3c + param_7;
    } while (*tmp_pb8 != 0);
  }
  local_3c = param_1 - local_3c;
  if (param_6 != 0) {
    local_24 = 0;
    local_28 = 0;
    local_2c = 0;
    local_20 = param_4[3];
    trap_R_SetColor(&local_2c);
    tmp_i11 = param_2 + 1 + (uint)(0xb < param_8);
    local_38 = 0;
    tmp_i9 = local_3c;
    tmp_pb8 = param_3;
    if (param_7 < 0xc) {
      while( true ) {
        tmp_b6 = *tmp_pb8;
        if ((tmp_b6 == 0) || (tmp_i7 <= local_38)) break;
        if ((tmp_b6 == 0x5e) && ((tmp_pb8[1] != 0 && (tmp_pb8[1] != 0x5e)))) {
          tmp_pb8 = tmp_pb8 + 2;
        }
        else {
          tmp_pb8 = tmp_pb8 + 1;
          tmp_i1 = tmp_i9 + 1;
          tmp_i9 = tmp_i9 + param_7;
          CG_DrawChar2(tmp_i1,tmp_i11,param_7,param_8,(int)(char)tmp_b6);
          local_38 = local_38 + 1;
        }
      }
    }
    else {
      while( true ) {
        tmp_b6 = *tmp_pb8;
        if ((tmp_b6 == 0) || (tmp_i7 <= local_38)) break;
        if ((tmp_b6 == 0x5e) && ((tmp_pb8[1] != 0 && (tmp_pb8[1] != 0x5e)))) {
          tmp_pb8 = tmp_pb8 + 2;
        }
        else {
          CG_DrawChar2(tmp_i9 + 2,tmp_i11,param_7,param_8,(int)(char)tmp_b6);
          local_38 = local_38 + 1;
          tmp_i9 = tmp_i9 + param_7;
          tmp_pb8 = tmp_pb8 + 1;
        }
      }
    }
  }
  tmp_i11 = 0;
  trap_R_SetColor(param_4);
  for (; tmp_b6 = *param_3, tmp_b6 != 0; param_3 = param_3 + 1) {
    while( true ) {
      if (tmp_i7 <= tmp_i11) goto LAB_00061120;
      if (tmp_b6 != 0x5e) {
        tmp_u10 = (uint)tmp_b6;
        if (tmp_u10 == 0x20) goto LAB_00060fa8;
        goto LAB_00060fd6;
      }
      tmp_b2 = param_3[1];
      if ((tmp_b2 == 0) || (tmp_b2 == 0x5e)) break;
      if (param_5 == 0) {
        if (tmp_b2 == 0x2a) {
          local_2c = *param_4;
          local_28 = param_4[1];
          local_24 = param_4[2];
          local_20 = param_4[3];
        }
        else {
          tmp_i9 = ((int)(char)tmp_b2 - 0x30U & 0x1f) * 0x10;
          local_2c = *(uint32_t *)(g_color_table + tmp_i9);
          local_28 = *(uint32_t *)(g_color_table + tmp_i9 + 4);
          local_24 = *(uint32_t *)(g_color_table + tmp_i9 + 8);
          local_20 = param_4[3];
        }
        trap_R_SetColor(&local_2c);
      }
      param_3 = param_3 + 2;
      tmp_b6 = *param_3;
      if (tmp_b6 == 0) goto LAB_00061120;
    }
    tmp_u10 = 0x5e;
LAB_00060fd6:
    if (cg_hudPlacement == 1) {
      tmp_f3 = (float)local_3c * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else {
      tmp_f3 = (float)local_3c * (float)GHIDRA_FIELD(cgs, 27364, 4);
      if (cg_hudPlacement == 2) {
        tmp_f3 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f3;
      }
      else {
        tmp_f3 = tmp_f3 + (float)GHIDRA_FIELD(cgs, 27372, 4);
      }
    }
    tmp_f4 = (float)((int)tmp_u10 >> 4) * 0.0625;
    tmp_f5 = (float)(short)(char)(tmp_b6 & 0xf) * 0.0625;
    trap_R_DrawStretchPic
              (tmp_f3,(float)GHIDRA_FIELD(cgs, 27368, 4) * (float)param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * (float)param_7,
               (float)param_8 * (float)GHIDRA_FIELD(cgs, 27368, 4),tmp_f5,tmp_f4,tmp_f5 + 0.0625,tmp_f4 + 0.0625,
               GHIDRA_FIELD(cgs, 67820, 4));
LAB_00060fa8:
    local_3c = local_3c + param_7;
    tmp_i11 = tmp_i11 + 1;
  }
LAB_00061120:
  trap_R_SetColor(0);
  return;
}

void CG_DrawBigString(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_14 = 0x3f800000;
  local_18 = 0x3f800000;
  local_1c = 0x3f800000;
  local_10 = param_4;
  CG_DrawStringExt_Shadow(param_1,param_2,param_3,&local_1c,0,2,0x10,0x10,0);
  return;
}

void CG_DrawBigStringColor
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  CG_DrawStringExt_Shadow(param_1,param_2,param_3,param_4,0,2,0x10,0x10,0);
  return;
}

void CG_DrawBigString2(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_14 = 0x3f800000;
  local_18 = 0x3f800000;
  local_1c = 0x3f800000;
  local_10 = param_4;
  CG_DrawStringExt3_constprop_0(param_3,&local_1c);
  return;
}

void CG_DrawBigStringColor2
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  param_2 = param_4;
  param_1 = param_3;
  CG_DrawStringExt3_constprop_0();
  return;
}

void CG_DrawSmallString(int param_1,int param_2,byte *param_3,uint32_t param_4)
{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  byte tmp_b5;
  int tmp_i6;
  uint tmp_u7;
  int tmp_i8;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  tmp_i8 = 0;
  uStack_14 = 0x6142b;
  local_34 = 0x3f800000;
  local_30 = param_4;
  local_38 = 0x3f800000;
  local_3c = 0x3f800000;
  trap_R_SetColor(&local_3c);
  for (; tmp_b5 = *param_3, tmp_b5 != 0; param_3 = param_3 + 1) {
    while( true ) {
      if (0x7ffe < tmp_i8) goto LAB_00061600;
      if (tmp_b5 != 0x5e) {
        tmp_u7 = (uint)tmp_b5;
        if (tmp_u7 == 0x20) goto LAB_00061478;
        goto LAB_000614a9;
      }
      tmp_b1 = param_3[1];
      if ((tmp_b1 == 0) || (tmp_b1 == 0x5e)) break;
      if (tmp_b1 == 0x2a) {
        local_2c = local_3c;
        local_28 = local_38;
        local_24 = local_34;
      }
      else {
        tmp_i6 = ((int)(char)tmp_b1 - 0x30U & 0x1f) * 0x10;
        local_2c = *(uint32_t *)(g_color_table + tmp_i6);
        local_28 = *(uint32_t *)(g_color_table + tmp_i6 + 4);
        local_24 = *(uint32_t *)(g_color_table + tmp_i6 + 8);
      }
      local_20 = local_30;
      param_3 = param_3 + 2;
      trap_R_SetColor(&local_2c);
      local_3c = local_2c;
      local_38 = local_28;
      local_34 = local_24;
      local_30 = local_20;
      tmp_b5 = *param_3;
      if (tmp_b5 == 0) goto LAB_00061600;
    }
    tmp_u7 = 0x5e;
LAB_000614a9:
    tmp_f2 = (float)param_1;
    if (cg_hudPlacement == 1) {
      tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else if (cg_hudPlacement == 2) {
      tmp_f2 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else {
      tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
    tmp_f3 = (float)((int)tmp_u7 >> 4) * 0.0625;
    tmp_f4 = (float)(short)(char)(tmp_b5 & 0xf) * 0.0625;
    trap_R_DrawStretchPic
              (tmp_f2,(float)GHIDRA_FIELD(cgs, 27368, 4) * (float)param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * 8.0,
               (float)GHIDRA_FIELD(cgs, 27368, 4) * 16.0,tmp_f4,tmp_f3,tmp_f4 + 0.0625,tmp_f3 + 0.0625,GHIDRA_FIELD(cgs, 67816, 4));
LAB_00061478:
    param_1 = param_1 + 8;
    tmp_i8 = tmp_i8 + 1;
  }
LAB_00061600:
  trap_R_SetColor(0);
  return;
}

void CG_DrawSmallStringColor(int param_1,int param_2,byte *param_3,uint32_t param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  byte tmp_b4;
  uint tmp_u5;
  int tmp_i6;
  
  tmp_i6 = 0;
  trap_R_SetColor(param_4);
  for (; tmp_b4 = *param_3, tmp_b4 != 0; param_3 = param_3 + 1) {
    while( true ) {
      if (0x7ffe < tmp_i6) goto LAB_000617d0;
      if (tmp_b4 != 0x5e) {
        tmp_u5 = (uint)tmp_b4;
        if (tmp_u5 == 0x20) goto LAB_000616c0;
        goto LAB_000616ee;
      }
      if ((param_3[1] == 0) || (param_3[1] == 0x5e)) break;
      param_3 = param_3 + 2;
      tmp_b4 = *param_3;
      if (tmp_b4 == 0) goto LAB_000617d0;
    }
    tmp_u5 = 0x5e;
LAB_000616ee:
    tmp_f1 = (float)param_1;
    if (cg_hudPlacement == 1) {
      tmp_f1 = tmp_f1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else if (cg_hudPlacement == 2) {
      tmp_f1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else {
      tmp_f1 = tmp_f1 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
    tmp_f2 = (float)((int)tmp_u5 >> 4) * 0.0625;
    tmp_f3 = (float)(short)(char)(tmp_b4 & 0xf) * 0.0625;
    trap_R_DrawStretchPic
              (tmp_f1,(float)GHIDRA_FIELD(cgs, 27368, 4) * (float)param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * 8.0,
               (float)GHIDRA_FIELD(cgs, 27368, 4) * 16.0,tmp_f3,tmp_f2,tmp_f3 + 0.0625,tmp_f2 + 0.0625,GHIDRA_FIELD(cgs, 67816, 4));
LAB_000616c0:
    param_1 = param_1 + 8;
    tmp_i6 = tmp_i6 + 1;
  }
LAB_000617d0:
  trap_R_SetColor(0);
  return;
}

void CG_DrawTinyStringColor(int param_1,int param_2,byte *param_3,uint32_t param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  byte tmp_b4;
  uint tmp_u5;
  int tmp_i6;
  
  tmp_i6 = 0;
  trap_R_SetColor(param_4);
  for (; tmp_b4 = *param_3, tmp_b4 != 0; param_3 = param_3 + 1) {
    while( true ) {
      if (0x7ffe < tmp_i6) goto LAB_00061970;
      if (tmp_b4 != 0x5e) {
        tmp_u5 = (uint)tmp_b4;
        if (tmp_u5 == 0x20) goto LAB_00061860;
        goto LAB_0006188e;
      }
      if ((param_3[1] == 0) || (param_3[1] == 0x5e)) break;
      param_3 = param_3 + 2;
      tmp_b4 = *param_3;
      if (tmp_b4 == 0) goto LAB_00061970;
    }
    tmp_u5 = 0x5e;
LAB_0006188e:
    tmp_f1 = (float)param_1;
    if (cg_hudPlacement == 1) {
      tmp_f1 = tmp_f1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else if (cg_hudPlacement == 2) {
      tmp_f1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + tmp_f1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
    }
    else {
      tmp_f1 = tmp_f1 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
    }
    tmp_f2 = (float)((int)tmp_u5 >> 4) * 0.0625;
    tmp_f3 = (float)(short)(char)(tmp_b4 & 0xf) * 0.0625;
    trap_R_DrawStretchPic
              (tmp_f1,(float)GHIDRA_FIELD(cgs, 27368, 4) * (float)param_2,(float)GHIDRA_FIELD(cgs, 27364, 4) * 6.0,
               (float)GHIDRA_FIELD(cgs, 27368, 4) * 14.0,tmp_f3,tmp_f2,tmp_f3 + 0.0625,tmp_f2 + 0.0625,GHIDRA_FIELD(cgs, 67816, 4));
LAB_00061860:
    param_1 = param_1 + 6;
    tmp_i6 = tmp_i6 + 1;
  }
LAB_00061970:
  trap_R_SetColor(0);
  return;
}

int CG_DrawStrlen(char *param_1)
{
  int tmp_i1;
  char tmp_c2;
  bool tmp_b3;
  
  tmp_i1 = 0;
  tmp_c2 = *param_1;
  do {
    if (tmp_c2 == '\0') {
      return tmp_i1;
    }
    while (((tmp_b3 = tmp_c2 != '^', tmp_c2 = param_1[1], tmp_b3 || (tmp_c2 == '\0')) || (tmp_c2 == '^')))
    {
      tmp_i1 = tmp_i1 + 1;
      param_1 = param_1 + 1;
      if (tmp_c2 == '\0') {
        return tmp_i1;
      }
    }
    tmp_c2 = param_1[2];
    param_1 = param_1 + 2;
  } while( true );
}

int CG_DrawMineMarkerFlag_isra_0(int param_1,int param_2,uint32_t param_3,uint32_t *param_4)
{
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t local_14;
  
  if (*(int *)(param_1 + 0x90) != 0) {
    param_3 = *param_4;
  }
  *(uint32_t *)(param_2 + 8) = param_3;
  *(float *)(param_2 + 0x70) = *(float *)(param_2 + 0x70) + 8.0;
  *(float *)(param_2 + 0x8c) = *(float *)(param_2 + 0x8c) + 8.0;
  local_14 = *(int *)(param_1 + 0x848);
  tmp_i3 = local_14;
  if (g_unk_010906e0 < local_14) {
    tmp_i2 = *(int *)(param_1 + 0x844);
    local_14 = *(int *)(param_1 + 0x83c);
  }
  else {
    tmp_i2 = *(int *)(param_1 + 0x844);
    *(int *)(param_1 + 0x83c) = local_14;
    *(int *)(param_1 + 0x838) = tmp_i2;
    while (tmp_i3 <= g_unk_010906e0) {
      tmp_i2 = tmp_i2 + 1;
      tmp_i3 = tmp_i3 + 0x32;
      *(int *)(param_1 + 0x848) = tmp_i3;
      *(int *)(param_1 + 0x844) = tmp_i2;
      if (0x13 < tmp_i2) {
        *(uint32_t *)(param_1 + 0x844) = 0;
        tmp_i2 = 0;
      }
    }
  }
  if (local_14 == tmp_i3) {
    tmp_f1 = 0.0;
  }
  else {
    tmp_i4 = g_unk_010906e0 - local_14;
    local_14 = tmp_i3 - local_14;
    tmp_f1 = 1.0 - (float)tmp_i4 / (float)local_14;
  }
  *(float *)(param_1 + 0x850) = tmp_f1;
  tmp_i2 = tmp_i2 + *(int *)(param_1 + 0xb0);
  if (0x13 < tmp_i2) {
    tmp_i2 = tmp_i2 + -0x14;
  }
  *(int *)(param_2 + 0x74) = tmp_i2;
  tmp_i3 = *(int *)(param_1 + 0xb0) + *(int *)(param_1 + 0x838);
  if (0x13 < tmp_i3) {
    tmp_i3 = tmp_i3 + -0x14;
  }
  *(int *)(param_2 + 0x90) = tmp_i3;
  *(uint32_t *)(param_2 + 0xa0) = *(uint32_t *)(param_1 + 0x850);
  return local_14;
}

void CG_DrawFireTeamOverlay(float *param_1)
{
  float *pfVar1;
  float tmp_f2;
  float tmp_f3;
  int *tmp_pi4;
  uint tmp_u5;
  int tmp_i6;
  int tmp_i7;
  uint32_t tmp_u8;
  char *tmp_pc9;
  uint8_t *tmp_pu10;
  int tmp_i11;
  int tmp_i12;
  float local_d4;
  int local_d0;
  float local_c0;
  float local_9c;
  float local_98;
  uint32_t local_94;
  uint32_t local_90;
  uint32_t local_8c;
  uint32_t local_88;
  uint32_t local_84;
  uint32_t local_80;
  uint32_t local_7c;
  uint32_t local_78;
  float local_74 [7];
  float local_58;
  float local_54;
  uint32_t uStack_14;
  
  uStack_14 = 0x76b09;
  local_94 = 0;
  local_90 = 0;
  local_8c = 0;
  tmp_f2 = *param_1;
  tmp_f3 = param_1[1];
  local_88 = 0x3f4ccccd;
  local_84 = 0;
  local_80 = 0;
  local_7c = 0;
  local_78 = 0x3e4ccccd;
  if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
    return;
  }
  CG_HudPlacement(1);
  tmp_u5 = 0;
  do {
    *(uint32_t *)((int)local_74 + tmp_u5) = 0;
    *(uint32_t *)((int)local_74 + tmp_u5 + 4) = 0;
    tmp_u5 = tmp_u5 + 8;
  } while (tmp_u5 < 0x18);
  if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
    return;
  }
  if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3) {
    return;
  }
  tmp_pi4 = *(int **)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9578);
  if (tmp_pi4 == (int *)0x0) {
    return;
  }
  local_d4 = 16.0;
  tmp_i6 = 0;
  do {
    while( true ) {
      if ((((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) || (*(int *)(cgs + sortedFireTeamClients * 0x1a4 + 0x9494) == 3)
          ) || (tmp_pi4 != *(int **)(cgs + sortedFireTeamClients * 0x1a4 + 0x9578)))
      goto LAB_00076d98;
      if (tmp_i6 != 0) break;
LAB_00077980:
      tmp_i6 = tmp_i6 + 1;
      local_d4 = local_d4 + 12.0;
    }
    if (((GHIDRA_FIELD(cgs, 27400, 4) == 1) || (*(int *)(cgs + g_unk_002bb284 * 0x1a4 + 0x9494) == 3)) ||
       (tmp_pi4 != *(int **)(cgs + g_unk_002bb284 * 0x1a4 + 0x9578))) break;
    if (tmp_i6 == 1) goto LAB_00077980;
    if (((GHIDRA_FIELD(cgs, 27400, 4) == 2) || (*(int *)(cgs + g_unk_002bb288 * 0x1a4 + 0x9494) == 3)) ||
       (tmp_pi4 != *(int **)(cgs + g_unk_002bb288 * 0x1a4 + 0x9578))) break;
    if (tmp_i6 == 2) goto LAB_00077980;
    if (((GHIDRA_FIELD(cgs, 27400, 4) == 3) || (*(int *)(cgs + g_unk_002bb28c * 0x1a4 + 0x9494) == 3)) ||
       (tmp_pi4 != *(int **)(cgs + g_unk_002bb28c * 0x1a4 + 0x9578))) break;
    if (tmp_i6 == 3) goto LAB_00077980;
    if (((GHIDRA_FIELD(cgs, 27400, 4) == 4) || (*(int *)(cgs + g_unk_002bb290 * 0x1a4 + 0x9494) == 3)) ||
       (tmp_pi4 != *(int **)(cgs + g_unk_002bb290 * 0x1a4 + 0x9578))) break;
    if (tmp_i6 == 4) goto LAB_00077980;
    if (((GHIDRA_FIELD(cgs, 27400, 4) == 5) || (*(int *)(cgs + g_unk_002bb294 * 0x1a4 + 0x9494) == 3)) ||
       ((tmp_pi4 != *(int **)(cgs + g_unk_002bb294 * 0x1a4 + 0x9578) ||
        (local_d4 = local_d4 + 12.0, tmp_i6 == 5)))) break;
    tmp_i6 = tmp_i6 + 1;
  } while( true );
LAB_00076d98:
  tmp_i6 = 0;
  pfVar1 = local_74 + 6;
  local_d0 = -1;
  while (((((tmp_i7 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9578), tmp_i7 != 0 &&
            (0 < (int)GHIDRA_FIELD(cgs, 27400, 4))) &&
           (*(int *)(cgs + sortedFireTeamClients * 0x1a4 + 0x9494) != 3)) &&
          (tmp_i7 == *(int *)(cgs + sortedFireTeamClients * 0x1a4 + 0x9578))) &&
         ((tmp_i12 = sortedFireTeamClients, tmp_i6 == 0 ||
          ((((GHIDRA_FIELD(cgs, 27400, 4) != 1 && (*(int *)(cgs + g_unk_002bb284 * 0x1a4 + 0x9494) != 3)) &&
            (tmp_i7 == *(int *)(cgs + g_unk_002bb284 * 0x1a4 + 0x9578))) &&
           ((tmp_i12 = g_unk_002bb284, tmp_i6 == 1 ||
            ((((GHIDRA_FIELD(cgs, 27400, 4) != 2 && (*(int *)(cgs + g_unk_002bb288 * 0x1a4 + 0x9494) != 3)) &&
              (tmp_i7 == *(int *)(cgs + g_unk_002bb288 * 0x1a4 + 0x9578))) &&
             ((tmp_i12 = g_unk_002bb288, tmp_i6 == 2 ||
              ((((GHIDRA_FIELD(cgs, 27400, 4) != 3 && (*(int *)(cgs + g_unk_002bb28c * 0x1a4 + 0x9494) != 3)) &&
                (tmp_i7 == *(int *)(cgs + g_unk_002bb28c * 0x1a4 + 0x9578))) &&
               ((tmp_i12 = g_unk_002bb28c, tmp_i6 == 3 ||
                ((((GHIDRA_FIELD(cgs, 27400, 4) != 4 && (*(int *)(cgs + g_unk_002bb290 * 0x1a4 + 0x9494) != 3)) &&
                  (tmp_i7 == *(int *)(cgs + g_unk_002bb290 * 0x1a4 + 0x9578))) &&
                 ((tmp_i12 = g_unk_002bb290, tmp_i6 == 4 ||
                  (((GHIDRA_FIELD(cgs, 27400, 4) != 5 && (*(int *)(cgs + g_unk_002bb294 * 0x1a4 + 0x9494) != 3)) &&
                   (tmp_i12 = g_unk_002bb294, tmp_i7 == *(int *)(cgs + g_unk_002bb294 * 0x1a4 + 0x9578))))
                  )))))))))))))))))))) {
    tmp_i7 = tmp_i12 * 0x1a4;
    local_9c = (float)*(int *)(cgs + tmp_i7 + 0x949c);
    local_98 = (float)*(int *)(cgs + tmp_i7 + 0x94a0);
    if ((GHIDRA_FIELD(cg_locations, 12, 4) & 1) == 0) {
LAB_00077734:
      tmp_u8 = BG_GetLocationString(&local_9c);
      tmp_pc9 = (char *)va(&g_unk_0011d97e,tmp_u8);
      local_74[tmp_i6] = (float)tmp_pc9;
    }
    else {
      local_54 = (float)*(int *)(cgs + tmp_i7 + 0x94a4);
      local_74[6] = local_9c;
      local_58 = local_98;
      tmp_u8 = CG_GetLocationMsg(pfVar1);
      tmp_pc9 = (char *)va(&g_unk_0011ccd0,tmp_u8);
      local_74[tmp_i6] = (float)tmp_pc9;
      if (((GHIDRA_FIELD(cg_locations, 12, 4) & 8) == 0) && (tmp_i7 = Q_stricmp(tmp_pc9,"^3Unknown"), tmp_i7 == 0))
      goto LAB_00077734;
      if ((GHIDRA_FIELD(cg_locations, 12, 4) & 0x10) != 0) {
        tmp_u8 = BG_GetLocationString(&local_9c);
        tmp_u8 = va(&g_unk_0011d97d,tmp_u8);
        Q_strcat(tmp_pc9,0x40,tmp_u8);
      }
    }
    if ((tmp_pc9[1] == '\0') || (*tmp_pc9 == '\0')) {
      tmp_pc9 = " ";
      local_74[tmp_i6] = (float)&g_unk_0011d7f6;
    }
    tmp_i7 = CG_Text_Width_Ext(tmp_pc9,0x3e4ccccd,GHIDRA_FIELD(cg_locationMaxChars, 12, 4),0x110afec);
    tmp_i7 = (-(uint)(*(int *)(cgs + tmp_i12 * 0x1a4 + 0x94a8) == 0) & 7) + 0x52 + tmp_i7;
    if (tmp_i7 <= local_d0) {
      tmp_i7 = local_d0;
    }
    tmp_i6 = tmp_i6 + 1;
    local_d0 = tmp_i7;
    if (((tmp_i6 == 6) || (GHIDRA_FIELD(cgs, 27388, 4) == 8)) ||
       (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3)) break;
  }
  tmp_i6 = (int)ROUND(tmp_f2);
  tmp_i7 = (int)ROUND(tmp_f3 + 1.0);
  CG_DrawRect((float)tmp_i6,(float)tmp_i7,(float)(local_d0 + 0x28),local_d4,0x3f800000,&HUD_Border);
  CG_FillRect((float)(tmp_i6 + 1),(float)(tmp_i7 + 1),(float)(local_d0 + 0x26),local_d4 - 2.0,
              &HUD_Background);
  tmp_i12 = 0;
  local_c0 = (float)(tmp_i7 + 2);
  CG_FillRect((float)(tmp_i6 + 2),local_c0,(float)(local_d0 + 0x24),0x41400000,&local_94);
  Com_sprintf(pfVar1,0x40,"Fireteam: %s",*(uint32_t *)(bg_fireteamNames + *tmp_pi4 * 4));
  Q_strupr(pfVar1);
  CG_Text_Paint_Ext((float)(tmp_i6 + 5),local_c0 + 10.0,0x3e3851ec,0x3e3851ec,HUD_Text,pfVar1,0,0,0,
                    0x1100f64);
  while( true ) {
    if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
      return;
    }
    if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3) {
      return;
    }
    tmp_i6 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9578);
    if (tmp_i6 == 0) {
      return;
    }
    if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) break;
    if (*(int *)(cgs + sortedFireTeamClients * 0x1a4 + 0x9494) == 3) {
      return;
    }
    if (tmp_i6 != *(int *)(cgs + sortedFireTeamClients * 0x1a4 + 0x9578)) {
      return;
    }
    tmp_i7 = sortedFireTeamClients;
    if (tmp_i12 != 0) {
      if (GHIDRA_FIELD(cgs, 27400, 4) == 1) {
        return;
      }
      if (*(int *)(cgs + g_unk_002bb284 * 0x1a4 + 0x9494) == 3) {
        return;
      }
      if (tmp_i6 != *(int *)(cgs + g_unk_002bb284 * 0x1a4 + 0x9578)) {
        return;
      }
      tmp_i7 = g_unk_002bb284;
      if (tmp_i12 != 1) {
        if (GHIDRA_FIELD(cgs, 27400, 4) == 2) {
          return;
        }
        if (*(int *)(cgs + g_unk_002bb288 * 0x1a4 + 0x9494) == 3) {
          return;
        }
        if (tmp_i6 != *(int *)(cgs + g_unk_002bb288 * 0x1a4 + 0x9578)) {
          return;
        }
        tmp_i7 = g_unk_002bb288;
        if (tmp_i12 != 2) {
          if (GHIDRA_FIELD(cgs, 27400, 4) == 3) {
            return;
          }
          if (*(int *)(cgs + g_unk_002bb28c * 0x1a4 + 0x9494) == 3) {
            return;
          }
          if (tmp_i6 != *(int *)(cgs + g_unk_002bb28c * 0x1a4 + 0x9578)) {
            return;
          }
          tmp_i7 = g_unk_002bb28c;
          if (tmp_i12 != 3) {
            if (GHIDRA_FIELD(cgs, 27400, 4) == 4) {
              return;
            }
            if (*(int *)(cgs + g_unk_002bb290 * 0x1a4 + 0x9494) == 3) {
              return;
            }
            if (tmp_i6 != *(int *)(cgs + g_unk_002bb290 * 0x1a4 + 0x9578)) {
              return;
            }
            tmp_i7 = g_unk_002bb290;
            if (tmp_i12 != 4) {
              if (GHIDRA_FIELD(cgs, 27400, 4) == 5) {
                return;
              }
              if (*(int *)(cgs + g_unk_002bb294 * 0x1a4 + 0x9494) == 3) {
                return;
              }
              tmp_i7 = g_unk_002bb294;
              if (tmp_i6 != *(int *)(cgs + g_unk_002bb294 * 0x1a4 + 0x9578)) {
                return;
              }
            }
          }
        }
      }
    }
    tmp_f2 = local_c0 + 12.0;
    tmp_i6 = (int)ROUND(*param_1 + 2.0);
    local_c0 = (float)(int)ROUND(tmp_f2);
    CG_FillRect((float)tmp_i6,local_c0 + 2.0,(float)(local_d0 + 0x24),0x41200000,&local_84);
    tmp_i11 = 0;
    if (*(uint *)(cgs + tmp_i7 * 0x1a4 + 0x94b8) < 5) {
      tmp_i11 = *(int *)(CSWTCH_11 + *(uint *)(cgs + tmp_i7 * 0x1a4 + 0x94b8) * 4);
    }
    CG_DrawPic((float)(tmp_i6 + 2),(float)((int)ROUND(tmp_f2) + 2),0x41200000,0x41200000,
               *(uint32_t *)(cgs + tmp_i11 * 4 + 0x11084));
    tmp_f2 = local_c0 + 10.0;
    CG_Text_Paint_Ext((float)(tmp_i6 + 0xc),tmp_f2,0x3e2e147b,0x3e2e147b,HUD_Text,
                      tmp_i7 * 0x1a4 + 0x10f9274,0,0xe,3,0x110afec);
    local_d4 = (float)(tmp_i6 + 0x5c);
    tmp_i7 = *(int *)(cgs + tmp_i7 * 0x1a4 + 0x94a8);
    if (tmp_i7 < 0x51) {
      if (tmp_i7 < 1) {
        if (tmp_i7 == 0) {
          if (g_unk_010906e0 % 500 < 0xfb) {
            tmp_pu10 = colorRed;
          }
          else {
            tmp_pu10 = (uint8_t *)&colorWhite;
          }
          CG_Text_Paint_Ext((float)(int)local_d4,tmp_f2,0x3e2e147b,0x3e2e147b,tmp_pu10,"*",0,0x11,3,
                            0x110afec);
          local_d4 = (float)(tmp_i6 + 99);
          if (g_unk_010906e0 % 500 < 0xfb) {
            tmp_pu10 = (uint8_t *)&colorWhite;
          }
          else {
            tmp_pu10 = colorRed;
          }
        }
        else {
          tmp_pu10 = colorRed;
        }
        CG_Text_Paint_Ext((float)(int)local_d4,tmp_f2,0x3e2e147b,0x3e2e147b,tmp_pu10,&g_unk_0011e957,0,0
                          ,3,0x110afec);
      }
      else {
        tmp_u8 = va("%i",tmp_i7);
        CG_Text_Paint_Ext((float)(int)local_d4,tmp_f2,0x3e2e147b,0x3e2e147b,&colorYellow,tmp_u8,0,0,3,
                          0x110afec);
      }
    }
    else {
      if (tmp_i7 < 0) {
        tmp_i7 = 0;
      }
      tmp_u8 = va("%i",tmp_i7);
      CG_Text_Paint_Ext((float)(int)local_d4,tmp_f2,0x3e2e147b,0x3e2e147b,HUD_Text,tmp_u8,0,0,3,
                        0x110afec);
    }
    pfVar1 = local_74 + tmp_i12;
    tmp_i12 = tmp_i12 + 1;
    CG_Text_Paint_Ext((float)((int)local_d4 + 0x18),tmp_f2,0x3e2e147b,0x3e2e147b,HUD_Text,*pfVar1,0,
                      GHIDRA_FIELD(cg_locationMaxChars, 12, 4),3,0x110afec);
    if (tmp_i12 == 6) {
      return;
    }
  }
  return;
}

void CG_DrawFireteamsByTeam(int param_1,int param_2)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int *tmp_pi3;
  float local_20;
  
  local_20 = *(float *)(param_1 + 0xc);
  if (param_2 - 1U < 2) {
    tmp_pi3 = &g_unk_010b3b30;
    do {
      if ((tmp_pi3[0x12] != 0) && (*(int *)(cgs + tmp_pi3[0x11] * 0x1a4 + 0x9494) == param_2)) {
        if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
          tmp_u2 = va("%c. %s",*tmp_pi3 + 0x41,*(uint32_t *)(bg_fireteamNames + *tmp_pi3 * 4));
        }
        else {
          tmp_u2 = va("%i. %s",(*tmp_pi3 + 1) % 10,*(uint32_t *)(bg_fireteamNames + *tmp_pi3 * 4));
        }
        tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
        CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_20,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u2,0
                          ,0,tmp_pu1[6],tmp_pu1[8]);
        local_20 = local_20 + *(float *)(param_1 + 0x14);
      }
      tmp_pi3 = tmp_pi3 + 0x14;
    } while (tmp_pi3 != (int *)&g_unk_010b3ef0);
  }
  return;
}

void CG_DrawPlayerSF(int param_1,int *param_2)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint8_t *tmp_pu7;
  float local_28;
  
  tmp_i6 = 1;
  local_28 = *(float *)(param_1 + 0xc);
  do {
    tmp_i2 = CG_PlayerSFFromPos(tmp_i6 + -1,param_2);
    if (tmp_i2 == -1) break;
    tmp_i2 = tmp_i2 * 0x1a4 + 0x10f9274;
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      tmp_u3 = va("%c. %s",tmp_i6 + 0x40,tmp_i2);
    }
    else {
      tmp_u3 = va("%i. %s",tmp_i6 % 10,tmp_i2);
    }
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    tmp_i6 = tmp_i6 + 1;
    CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_28,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u3,0,0,
                      tmp_pu1[6],tmp_pu1[8]);
    local_28 = local_28 + *(float *)(param_1 + 0x14);
  } while (tmp_i6 != 9);
  if (*param_2 == 0) {
    if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
      return;
    }
  }
  else {
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      tmp_u3 = va("%c. %s",0x50,"Previous");
    }
    else {
      tmp_u3 = va("%i. %s",9,"Previous");
    }
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_28,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u3,0,0,
                      tmp_pu1[6],tmp_pu1[8]);
    local_28 = local_28 + *(float *)(param_1 + 0x14);
    if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
      tmp_i2 = 0;
      goto LAB_00078f49;
    }
  }
  tmp_pu7 = cgs;
  tmp_i2 = 0;
  tmp_i6 = 0;
  do {
    if (((g_unk_01047ac4 != tmp_i6) && (*(int *)(tmp_pu7 + 0x940c) != 0)) &&
       (*(int *)(tmp_pu7 + 0x9494) == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) {
      tmp_i4 = CG_IsOnFireteam(tmp_i6);
      tmp_i5 = CG_IsOnFireteam(g_unk_01047ac4);
      tmp_i2 = tmp_i2 + (uint)(tmp_i4 == tmp_i5);
    }
    tmp_i6 = tmp_i6 + 1;
    tmp_pu7 = tmp_pu7 + 0x1a4;
  } while (tmp_i6 < (int)GHIDRA_FIELD(cgs, 27400, 4));
LAB_00078f49:
  if (*param_2 * 8 + 8 < tmp_i2) {
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      tmp_u3 = va("%c. %s",0x4e,&g_unk_00115b20);
    }
    else {
      tmp_u3 = va("%i. %s",0,&g_unk_00115b20);
    }
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_28,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u3,0,0,
                      tmp_pu1[6],tmp_pu1[8]);
  }
  return;
}

void CG_DrawPlayerNF(int param_1,int *param_2)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  float local_28;
  int local_24;
  
  tmp_i5 = 1;
  local_28 = *(float *)(param_1 + 0xc);
  do {
    tmp_i2 = CG_PlayerNFFromPos(tmp_i5 + -1,param_2);
    if (tmp_i2 == -1) break;
    tmp_i2 = tmp_i2 * 0x1a4 + 0x10f9274;
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      tmp_u3 = va("%c. %s",tmp_i5 + 0x40,tmp_i2);
    }
    else {
      tmp_u3 = va("%i. %s",tmp_i5 % 10,tmp_i2);
    }
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    tmp_i5 = tmp_i5 + 1;
    CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_28,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u3,0,0,
                      tmp_pu1[6],tmp_pu1[8]);
    local_28 = local_28 + *(float *)(param_1 + 0x14);
  } while (tmp_i5 != 9);
  if (*param_2 == 0) {
    if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
      return;
    }
  }
  else {
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      tmp_u3 = va("%c. %s",0x50,"Previous");
    }
    else {
      tmp_u3 = va("%i. %s",9,"Previous");
    }
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_28,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u3,0,0,
                      tmp_pu1[6],tmp_pu1[8]);
    local_28 = local_28 + *(float *)(param_1 + 0x14);
    if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
      local_24 = 0;
      goto LAB_000792ad;
    }
  }
  tmp_pu4 = cgs;
  tmp_i5 = 0;
  local_24 = 0;
  do {
    if (((g_unk_01047ac4 != tmp_i5) && (*(int *)(tmp_pu4 + 0x940c) != 0)) &&
       (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu4 + 0x9494))) {
      tmp_i2 = CG_IsOnFireteam(tmp_i5);
      local_24 = local_24 + (uint)(tmp_i2 == 0);
    }
    tmp_i5 = tmp_i5 + 1;
    tmp_pu4 = tmp_pu4 + 0x1a4;
  } while (tmp_i5 < (int)GHIDRA_FIELD(cgs, 27400, 4));
LAB_000792ad:
  if (*param_2 * 8 + 8 < local_24) {
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      tmp_u3 = va("%c. %s",0x4e,&g_unk_00115b20);
    }
    else {
      tmp_u3 = va("%i. %s",0,&g_unk_00115b20);
    }
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_28,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u3,0,0,
                      tmp_pu1[6],tmp_pu1[8]);
  }
  return;
}

void CG_DrawInformation(uint32_t param_1)
{
  int tmp_i1;
  
  if ((lastcalled_11943 != 0) && (tmp_i1 = trap_Milliseconds(), tmp_i1 - lastcalled_11943 < 0x32)) {
    return;
  }
  lastcalled_11943 = trap_Milliseconds();
  if (g_unk_01047b00 == 0) {
    CG_DrawConnectScreen(param_1);
  }
  return;
}

void CG_DrawOverlays(void)
{
  CG_GameStatsDraw();
  CG_TopShotsDraw();
  if ((g_unk_01047aec != 0) && (g_unk_010afbc8 != 0)) {
    CG_DemoHelpDraw_part_1();
    return;
  }
  return;
}

void CG_LimboPanelRenderText_NoLMS(uint32_t param_1)
{
  if (GHIDRA_FIELD(cg_gameType, 12, 4) != 5) {
    BG_PanelButtonsRender_Text(param_1);
  }
  return;
}

void CG_LimboPanelRenderText_SkillsText(uint32_t param_1)
{
  if (GHIDRA_FIELD(cg_gameType, 12, 4) != 5) {
    BG_PanelButtonsRender_Text(param_1);
  }
  return;
}

void CG_LimboPanel_RenderObjectiveBack(int param_1)
{
  CG_HudPlacement(0);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
             *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131720, 4));
  return;
}

void CG_LimboPanel_Filter_Draw(int param_1)
{
  CG_HudPlacement(0);
  if (((int)GHIDRA_FIELD(cgs, 33685964, 4) >> ((byte)*(uint32_t *)(param_1 + 0x18) & 0x1f) & 1U) == 0) {
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 69708, 4));
  }
  else {
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 69712, 4));
  }
  CG_DrawPic(*(float *)(param_1 + 8) + 1.0,*(float *)(param_1 + 0xc) + 1.0,
             *(float *)(param_1 + 0x10) - 2.0,*(float *)(param_1 + 0x14) - 2.0,
             *(uint32_t *)(cgs + *(int *)(param_1 + 0x18) * 4 + 0x11024));
  return;
}

void CG_LimboPanel_RenderMedal(int param_1)
{
  CG_HudPlacement(0);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
             *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 69888, 4));
  if (*(int *)(cgs + (*(int *)(param_1 + 0x18) + 0x252c + g_unk_01047ac4 * 0x69) * 4 + 0x18) != 0) {
    CG_DrawPic(*(float *)(param_1 + 8) - 2.0,*(uint32_t *)(param_1 + 0xc),
               *(float *)(param_1 + 0x10) + 4.0,*(uint32_t *)(param_1 + 0x14),
               *(uint32_t *)(cgs + *(int *)(param_1 + 0x18) * 4 + 0x110e4));
  }
  return;
}

void CG_LimboPanel_RenderSkillIcon(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 5) {
    return;
  }
  tmp_i1 = *(int *)(param_1 + 0x18);
  tmp_u2 = GHIDRA_FIELD(cgs, 131688, 4);
  if (tmp_i1 != 1) {
    if (tmp_i1 == 2) {
      tmp_u2 = *(uint32_t *)(cgs + (int)(&UNK_0002020c + GHIDRA_FIELD(cgs, 33685916, 4) * 4));
    }
    else {
      tmp_u2 = GHIDRA_FIELD(cgs, 131692, 4);
      if (tmp_i1 != 0) {
        return;
      }
    }
  }
  CG_HudPlacement(0);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
             *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),tmp_u2);
  return;
}

void CG_LimboPanel_NameEditFinish(int param_1)
{
  uint8_t local_10c [260];
  
  trap_Cvar_VariableStringBuffer(*(uint32_t *)(param_1 + 4),local_10c,0x100);
  trap_Cvar_Set("name",local_10c);
  return;
}

void CG_LimboPanel_RenderTeamButton(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  CG_HudPlacement(0);
  trap_R_SetColor(&colorBlack);
  CG_DrawPic(*(float *)(param_1 + 8) + 1.0,*(float *)(param_1 + 0xc) + 1.0,
             *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131664, 4));
  trap_R_SetColor(0);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
             *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131664, 4));
  if ((&teamOrder)[*(int *)(param_1 + 0x18)] == (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)]) {
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131660, 4));
    tmp_i1 = *(int *)(param_1 + 0x18);
  }
  else {
    tmp_i1 = BG_CursorInRect(param_1 + 8);
    if (tmp_i1 != 0) {
      CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131660, 4));
      trap_R_SetColor(0);
    }
    tmp_i1 = *(int *)(param_1 + 0x18);
  }
  tmp_u2 = GHIDRA_FIELD(cgs, 131672, 4);
  if (((tmp_i1 != 1) && (tmp_u2 = GHIDRA_FIELD(cgs, 131676, 4), tmp_i1 != 2)) && (tmp_u2 = GHIDRA_FIELD(cgs, 131668, 4), tmp_i1 != 0)
     ) {
    return;
  }
  trap_R_SetColor(0);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
             *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),tmp_u2);
  return;
}

void CG_LimboPanel_ClassBar_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  char *tmp_pc3;
  uint8_t local_4c [60];
  uint32_t uStack_10;
  
  uStack_10 = 0x83648;
  CG_HudPlacement(0);
  tmp_i2 = BG_CursorInRect(0x1469c8);
  tmp_pc3 = skillNames;
  if ((((tmp_i2 != 0) ||
       (tmp_i2 = BG_CursorInRect(0x146968), tmp_pc3 = g_ptr_s_Engineering_00140bf8, tmp_i2 != 0)) ||
      (tmp_i2 = BG_CursorInRect(0x146908), tmp_pc3 = g_ptr_s_First_Aid_00140bfc, tmp_i2 != 0)) ||
     (((tmp_i2 = BG_CursorInRect(0x1468a8), tmp_pc3 = g_ptr_s_Signals_0011c696_9_00140c00, tmp_i2 != 0 ||
       (tmp_i2 = BG_CursorInRect(0x146848), tmp_pc3 = g_ptr_s_Light_Weapons_00140c04, tmp_i2 != 0)) ||
      ((tmp_i2 = BG_CursorInRect(0x1467e8), tmp_pc3 = g_ptr_s_Heavy_Weapons_00140c08, tmp_i2 != 0 ||
       (tmp_i2 = BG_CursorInRect(0x146788), tmp_pc3 = g_ptr_s_Covert_Ops_00140c0c, tmp_i2 != 0))))))
  goto joined_r0x0008374d;
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) {
    tmp_pc3 = "JOIN A TEAM";
    goto LAB_0008368a;
  }
  tmp_i2 = BG_CursorInRect(0x146308);
  if (tmp_i2 == 0) {
    tmp_i2 = BG_CursorInRect(0x146248);
    if (tmp_i2 != 0) {
      tmp_pc3 = (char *)BG_ClassnameForNumber(1);
      goto joined_r0x0008374d;
    }
    tmp_i2 = BG_CursorInRect(0x146188);
    if (tmp_i2 != 0) {
      tmp_pc3 = (char *)BG_ClassnameForNumber(2);
      goto joined_r0x0008374d;
    }
    tmp_i2 = BG_CursorInRect(0x1460c8);
    if (tmp_i2 != 0) {
      tmp_pc3 = (char *)BG_ClassnameForNumber(3);
      goto joined_r0x0008374d;
    }
    tmp_i2 = BG_CursorInRect(0x146008);
    if (tmp_i2 != 0) {
      tmp_pc3 = (char *)BG_ClassnameForNumber(4);
      goto joined_r0x0008374d;
    }
  }
  else {
    tmp_pc3 = (char *)BG_ClassnameForNumber(0);
joined_r0x0008374d:
    if (tmp_pc3 != (char *)0x0) goto LAB_0008368a;
  }
  tmp_pc3 = (char *)BG_ClassnameForNumber(GHIDRA_FIELD(cgs, 33685916, 4));
LAB_0008368a:
  Q_strncpyz(local_4c,tmp_pc3,0x40);
  Q_strupr(local_4c);
  tmp_i2 = CG_Text_Width_Ext(local_4c,**(uint32_t **)(param_1 + 0x38),0,
                            (*(uint32_t **)(param_1 + 0x38))[8]);
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext((*(float *)(param_1 + 0x10) - (float)tmp_i2) * 0.5 + *(float *)(param_1 + 8),
                    *(uint32_t *)(param_1 + 0xc),*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,local_4c,0,0,
                    tmp_pu1[6],tmp_pu1[8]);
  return;
}

void CG_LimboPanel_RenderCommandMap(int param_1)
{
  CG_HudPlacement(0);
  CG_DrawMap(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
             *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 33685964, 4),0,1,
             0x3f800000,1);
  CG_CommandMap_DrawHighlightText();
  return;
}

uint32_t CG_LimboPanel_PlusButton_KeyDown(uint32_t param_1,int param_2)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 0;
  if (param_2 == 0xb2) {
    trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69628, 4),6);
    GHIDRA_FIELD(cgs, 33575916, 4) = (float)GHIDRA_FIELD(cgs, 33575916, 4) / 0.75;
    if (1.0 < (float)GHIDRA_FIELD(cgs, 33575916, 4)) {
      GHIDRA_FIELD(cgs, 33575916, 4) = 0x3f800000;
      return 1;
    }
    tmp_u1 = 1;
  }
  return tmp_u1;
}

uint32_t CG_LimboPanel_MinusButton_KeyDown(uint32_t param_1,int param_2)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 0;
  if (param_2 == 0xb2) {
    trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69628, 4),6);
    GHIDRA_FIELD(cgs, 33575916, 4) = (float)GHIDRA_FIELD(cgs, 33575916, 4) * 0.75;
    if ((float)GHIDRA_FIELD(cgs, 33575916, 4) < 0.23730469) {
      GHIDRA_FIELD(cgs, 33575916, 4) = 0x3e730000;
      return 1;
    }
    tmp_u1 = 1;
  }
  return tmp_u1;
}

uint32_t CG_LimboPanel_Filter_KeyDown(int param_1,int param_2)
{
  if (param_2 != 0xb2) {
    return 0;
  }
  trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69632, 4),6);
  GHIDRA_FIELD(cgs, 33685964, 4) = GHIDRA_FIELD(cgs, 33685964, 4) ^ 1 << ((byte)*(uint32_t *)(param_1 + 0x18) & 0x1f);
  return 1;
}

uint32_t CG_LimboPanel_BriefingButton_KeyDown(uint32_t param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  if ((param_2 == 0xb2) && (GHIDRA_FIELD(cg_gameType, 12, 4) != 5)) {
    trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69628, 4),6);
    tmp_i1 = g_unk_010906e0;
    if (g_unk_010906e0 < g_unk_010b3b28) {
      trap_S_StopStreamingSound(0xffffffff);
      g_unk_010b3b28 = 0;
      tmp_u2 = 1;
    }
    else {
      tmp_u2 = va("news_%s",0x10f69ac);
      tmp_i3 = CG_SoundPlaySoundScript(tmp_u2,0,0xffffffff,0);
      g_unk_010b3b28 = tmp_i1 + tmp_i3;
      tmp_u2 = 1;
    }
  }
  else {
    tmp_u2 = 0;
  }
  return tmp_u2;
}

void CG_LimboPanel_BriefingButton_Draw(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  if (GHIDRA_FIELD(cg_gameType, 12, 4) != 5) {
    CG_HudPlacement(0);
    if (g_unk_010b3b28 <= g_unk_010906e0) {
      tmp_i1 = BG_CursorInRect(param_1 + 8);
      tmp_u2 = GHIDRA_FIELD(cgs, 131732, 4);
      if (tmp_i1 != 0) {
        tmp_u2 = GHIDRA_FIELD(cgs, 131728, 4);
      }
      CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),tmp_u2);
      return;
    }
    tmp_i1 = BG_CursorInRect(param_1 + 8);
    tmp_u2 = GHIDRA_FIELD(cgs, 131740, 4);
    if (tmp_i1 != 0) {
      tmp_u2 = GHIDRA_FIELD(cgs, 131736, 4);
    }
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),tmp_u2);
  }
  return;
}

uint32_t CG_LimboPanel_CancelButton_KeyDown(uint32_t param_1,int param_2)
{
  if (param_2 != 0xb2) {
    return 0;
  }
  trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69636, 4),6);
  if (GHIDRA_FIELD(cgs, 33701712, 4) != 0) {
    trap_SendClientCommand("rs");
    GHIDRA_FIELD(cgs, 33701708, 4) = 0;
  }
  CG_EventHandling(0,0);
  return 1;
}

void CG_DrawLimboPlayerHead_part_6
          (float *param_1,int param_2,uint32_t param_3,uint32_t param_4,uint32_t param_5,
          int param_6,int param_7)

{
  int *tmp_pi1;
  int *tmp_pi2;
  uint tmp_u3;
  float local_4c0;
  float local_4bc;
  float local_4b8;
  float local_4b4;
  uint8_t local_4b0 [4];
  float local_4ac;
  float local_4a8;
  uint8_t local_4a4 [4];
  float local_4a0;
  float local_49c;
  uint32_t local_498;
  uint32_t local_494;
  uint32_t local_490;
  uint32_t local_48c [7];
  uint8_t local_470 [76];
  float local_424;
  float local_420;
  float local_41c;
  uint8_t local_418 [28];
  uint8_t local_3fc [16];
  uint8_t local_3ec [12];
  uint32_t local_3e0;
  int local_3a0 [127];
  uint8_t local_1a4 [36];
  uint32_t local_180;
  uint32_t local_17c;
  uint32_t uStack_14;
  
  uStack_14 = 0x83dad;
  CG_HudPlacement(0);
  trap_R_SaveViewParms();
  local_4c0 = *param_1;
  local_4bc = param_1[1];
  local_4b8 = param_1[2];
  local_4b4 = param_1[3];
  tmp_pi1 = local_3a0 + 0x76;
  CG_AdjustFrom640(&local_4c0,&local_4bc,&local_4b8,&local_4b4);
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)tmp_pi1 + tmp_u3) = 0;
    *(uint32_t *)((int)local_3a0 + tmp_u3 + 0x1dc) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0x1a8);
  *(uint32_t *)((int)tmp_pi1 + tmp_u3) = 0;
  local_17c = 1;
  AxisClear(local_1a4);
  local_3a0[0x7a] = 0x41000000;
  local_3a0[0x7b] = 0x41200000;
  local_3a0[0x76] = (int)ROUND(local_4c0);
  local_180 = g_unk_010906e0;
  local_3a0[0x77] = (int)ROUND(local_4bc);
  local_3a0[0x78] = (int)ROUND(local_4b8);
  local_3a0[0x79] = (int)ROUND(local_4b4);
  trap_R_ClearScene();
  trap_R_ModelBounds(*(uint32_t *)(param_2 + 0xa0),local_4b0,local_4a4);
  tmp_u3 = 0;
  local_490 = 0;
  local_498 = param_4;
  local_494 = param_3;
  do {
    *(uint32_t *)((int)local_48c + tmp_u3) = 0;
    *(uint32_t *)((int)local_48c + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0xe8);
  *(uint32_t *)((int)local_48c + tmp_u3) = 0;
  AnglesToAxis(&local_498,local_470);
  local_48c[1] = 0x410;
  local_424 = ((local_49c - local_4a8) * 3.5) / 0.64836085;
  local_41c = (local_4a8 + local_49c) * -0.7;
  local_48c[2] = *(uint32_t *)(param_2 + 0xa0);
  local_3e0 = *(uint32_t *)(param_2 + 0xa4);
  if (g_unk_010abd78 == 0) {
    local_48c[1] = 0x411;
  }
  local_420 = (local_4ac + local_4a0) * 0.5;
  CG_HudHeadAnimation(param_2,&g_unk_01091060,local_3fc,local_418,local_3ec,param_5,0);
  tmp_pi2 = local_3a0 + 0x3b;
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)tmp_pi2 + tmp_u3) = 0;
    *(uint32_t *)((int)local_3a0 + tmp_u3 + 0xf0) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0xe8);
  *(uint32_t *)((int)tmp_pi2 + tmp_u3) = 0;
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)local_3a0 + tmp_u3) = 0;
    *(uint32_t *)((int)local_3a0 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0xe8);
  *(uint32_t *)((int)local_3a0 + tmp_u3) = 0;
  local_3a0[2] = *(uint32_t *)(param_2 + 0x60);
  local_3a0[1] = 0x410;
  local_3a0[0x2b] = *(uint32_t *)(param_2 + 0x8c);
  CG_PositionEntityOnTag(local_3a0,local_48c,"tag_mouth",0,0);
  if (param_7 == 0) {
    trap_R_AddRefEntityToScene(local_48c);
    trap_R_AddRefEntityToScene(local_3a0);
  }
  else {
    local_3a0[0x3d] = *(uint32_t *)(param_2 + 0x70);
    local_3a0[0x67] = *(int *)(rankicons + ((uint)(param_6 == 1) + param_7 * 2) * 0x20 + 0x10);
    local_3a0[0x3c] = 0x410;
    CG_PositionEntityOnTag(tmp_pi2,local_48c,"tag_mouth",0,0);
    trap_R_AddRefEntityToScene(local_48c);
    trap_R_AddRefEntityToScene(local_3a0);
    trap_R_AddRefEntityToScene(tmp_pi2);
  }
  trap_R_RenderScene(tmp_pi1);
  trap_R_RestoreViewParms();
  return;
}

void CG_LimboPanel_RenderHead(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x841a9;
  local_2c = 0x3d4ccccd;
  local_28 = 0x3d4ccccd;
  local_24 = 0x3d4ccccd;
  local_20 = 0x3f800000;
  CG_HudPlacement(0);
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) {
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131744, 4));
  }
  else {
    CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_2c);
    tmp_u1 = *(uint32_t *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94c0);
    tmp_u2 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
    tmp_i3 = BG_GetCharacter(tmp_u2,GHIDRA_FIELD(cgs, 33685916, 4));
    if (tmp_i3 != 0) {
      CG_DrawLimboPlayerHead_part_6(0x43340000,0,3,tmp_u2,tmp_u1);
    }
  }
  local_2c = 0x3f19999a;
  local_28 = 0x3f19999a;
  local_24 = 0x3f19999a;
  trap_R_SetColor(&local_2c);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) - 2.0,
             *(uint32_t *)(param_1 + 0x10),0x40000000,GHIDRA_FIELD(cgs, 131564, 4));
  CG_DrawPicST(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14),
               *(uint32_t *)(param_1 + 0x10),0x40000000,0,0x3f800000,0x3f800000,0,GHIDRA_FIELD(cgs, 131564, 4));
  CG_DrawPic(*(float *)(param_1 + 8) - 2.0,*(uint32_t *)(param_1 + 0xc),0x40000000,
             *(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131568, 4));
  CG_DrawPicST(*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0xc),
               0x40000000,*(uint32_t *)(param_1 + 0x14),0x3f800000,0,0,0x3f800000,GHIDRA_FIELD(cgs, 131568, 4));
  CG_DrawPicST(*(float *)(param_1 + 8) - 2.0,*(float *)(param_1 + 0xc) - 2.0,0x40000000,0x40000000,0
               ,0,0x3f800000,0x3f800000,GHIDRA_FIELD(cgs, 131572, 4));
  CG_DrawPicST(*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10),*(float *)(param_1 + 0xc) - 2.0,
               0x40000000,0x40000000,0x3f800000,0,0,0x3f800000,GHIDRA_FIELD(cgs, 131572, 4));
  CG_DrawPicST(*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10),
               *(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14),0x40000000,0x40000000,
               0x3f800000,0x3f800000,0,0,GHIDRA_FIELD(cgs, 131572, 4));
  CG_DrawPicST(*(float *)(param_1 + 8) - 2.0,*(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14),
               0x40000000,0x40000000,0,0x3f800000,0x3f800000,0,GHIDRA_FIELD(cgs, 131572, 4));
  trap_R_SetColor(0);
  return;
}

void CG_LimboPanel_WeaponLights(int param_1)
{
  uint32_t tmp_u1;
  
  CG_HudPlacement(0);
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) {
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131552, 4));
  }
  else {
    tmp_u1 = GHIDRA_FIELD(cgs, 131556, 4);
    if (*(int *)(param_1 + 0x18) != GHIDRA_FIELD(cgs, 33685912, 4)) {
      tmp_u1 = GHIDRA_FIELD(cgs, 131552, 4);
    }
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),tmp_u1);
  }
  return;
}

uint32_t CG_LimboPanel_WeaponPanel_KeyDown(int param_1,int param_2)
{
  *(uint32_t *)(param_1 + 0x34) = 0;
  if ((param_2 == 0xb2) && ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3)) {
    trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69628, 4),6);
    BG_PanelButtons_SetFocusButton(param_1);
    return 1;
  }
  return 0;
}

void CG_LimboPanel_RenderLight(int param_1)
{
  uint tmp_u1;
  bool tmp_b2;
  uint32_t tmp_u3;
  
  CG_HudPlacement(0);
  tmp_u3 = GHIDRA_FIELD(cgs, 131592, 4);
  if (*(int *)(param_1 + 0x18) == 0) {
    tmp_b2 = GHIDRA_FIELD(cgs, 33685916, 4) == *(int *)(param_1 + 0x1c);
  }
  else {
    if (*(int *)(param_1 + 0x18) != 1) goto LAB_00084712;
    tmp_b2 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == (&teamOrder)[*(int *)(param_1 + 0x1c)];
  }
  if ((tmp_b2) &&
     (tmp_u1 = *(uint *)(param_1 + 0x24), *(uint *)(param_1 + 0x24) = tmp_u1 ^ 1,
     tmp_u3 = GHIDRA_FIELD(cgs, 131588, 4), tmp_u1 == 1)) {
    tmp_u3 = GHIDRA_FIELD(cgs, 131584, 4);
  }
LAB_00084712:
  CG_DrawPic(*(float *)(param_1 + 8) - 4.0,*(float *)(param_1 + 0xc) - 2.0,
             *(float *)(param_1 + 0x10) + 4.0,*(float *)(param_1 + 0x14) + 4.0,tmp_u3);
  return;
}

uint32_t CG_LimboPanel_ObjectiveText_KeyDown(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  long tmp_l4;
  int tmp_i5;
  int tmp_i6;
  
  if (param_2 != 0xb2) {
    return 0;
  }
  trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69628, 4),6);
  tmp_i6 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
  tmp_i1 = 0;
  if (tmp_i6 != 3) {
    tmp_u2 = CG_ConfigString(0xd);
    tmp_pc3 = (char *)Info_ValueForKey(tmp_u2,&g_unk_00120a20);
    tmp_i1 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_i6 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
  }
  if (*(int *)(param_1 + 0x34) == 0) {
    GHIDRA_FIELD(cgs, 33685904, 4) = GHIDRA_FIELD(cgs, 33685904, 4) + 1;
    if (tmp_i1 < (int)GHIDRA_FIELD(cgs, 33685904, 4)) {
      GHIDRA_FIELD(cgs, 33685904, 4) = 0;
    }
  }
  else {
    tmp_i5 = GHIDRA_FIELD(cgs, 33685904, 4) + -1;
    GHIDRA_FIELD(cgs, 33685904, 4) = tmp_i1;
    if (-1 < tmp_i5) {
      GHIDRA_FIELD(cgs, 33685904, 4) = tmp_i5;
    }
  }
  if (tmp_i6 != 3) {
    tmp_u2 = CG_ConfigString(0xd);
    tmp_pc3 = (char *)Info_ValueForKey(tmp_u2,&g_unk_00120a20);
    tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
    if ((GHIDRA_FIELD(cgs, 33685904, 4) != tmp_l4) &&
       (tmp_u2 = GHIDRA_FIELD(cgs, 33685904, 4), (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3)) goto LAB_000848bb;
  }
  tmp_u2 = 0xffffffff;
LAB_000848bb:
  tmp_u2 = va("obj %i",tmp_u2);
  trap_SendClientCommand(tmp_u2);
  GHIDRA_FIELD(cgs, 33685972, 4) = GHIDRA_FIELD(cgs, 33685904, 4);
  GHIDRA_FIELD(cgs, 33685976, 4) = g_unk_010906e0;
  return 1;
}

void CG_LimboPanel_Border_Draw(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  int tmp_i9;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_3c = 0x3dcccccd;
  local_38 = 0x3dcccccd;
  tmp_f1 = *(float *)(param_1 + 0x14);
  local_34 = 0x3dcccccd;
  tmp_f2 = *(float *)(param_1 + 0x10);
  local_30 = 0x3f800000;
  tmp_f3 = *(float *)(param_1 + 0xc);
  local_2c = 0x3e4ccccd;
  tmp_f4 = *(float *)(param_1 + 8);
  local_28 = 0x3e4ccccd;
  local_24 = 0x3e4ccccd;
  local_20 = 0x3f800000;
  CG_HudPlacement(0);
  tmp_f5 = tmp_f3 - 4.0;
  CG_DrawPic(tmp_f4,tmp_f5,tmp_f2,0x40800000,GHIDRA_FIELD(cgs, 131564, 4));
  tmp_f6 = tmp_f1 + tmp_f3;
  CG_DrawPicST(tmp_f4,tmp_f6,tmp_f2,0x40800000,0,0x3f800000,0x3f800000,0,GHIDRA_FIELD(cgs, 131564, 4));
  tmp_f7 = tmp_f4 - 4.0;
  CG_DrawPic(tmp_f7,tmp_f3,0x40800000,tmp_f1,GHIDRA_FIELD(cgs, 131568, 4));
  tmp_f8 = tmp_f2 + tmp_f4;
  CG_DrawPicST(tmp_f8,tmp_f3,0x40800000,tmp_f1,0x3f800000,0,0,0x3f800000,GHIDRA_FIELD(cgs, 131568, 4));
  CG_DrawPicST(tmp_f7,tmp_f5,0x40800000,0x40800000,0,0,0x3f800000,0x3f800000,GHIDRA_FIELD(cgs, 131572, 4));
  CG_DrawPicST(tmp_f8,tmp_f5,0x40800000,0x40800000,0x3f800000,0,0,0x3f800000,GHIDRA_FIELD(cgs, 131572, 4));
  CG_DrawPicST(tmp_f8,tmp_f6,0x40800000,0x40800000,0x3f800000,0x3f800000,0,0,GHIDRA_FIELD(cgs, 131572, 4));
  CG_DrawPicST(tmp_f7,tmp_f6,0x40800000,0x40800000,0,0x3f800000,0x3f800000,0,GHIDRA_FIELD(cgs, 131572, 4));
  local_1c = tmp_f4;
  local_18 = tmp_f3;
  local_14 = tmp_f2;
  local_10 = tmp_f1;
  tmp_i9 = BG_CursorInRect(&local_1c);
  if (tmp_i9 != 0) {
    CG_FillRect(tmp_f4,tmp_f3,tmp_f2,tmp_f1,&local_2c);
    return;
  }
  CG_FillRect(tmp_f4,tmp_f3,tmp_f2,tmp_f1,&local_3c);
  return;
}

void CG_LimboPanel_RenderObjectiveText(int param_1)
{
  uint32_t *tmp_pu1;
  float tmp_f2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  long tmp_l5;
  uint32_t tmp_u6;
  char *tmp_pc7;
  int tmp_i8;
  uint8_t *tmp_pu9;
  char tmp_c10;
  int local_428;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x84ca9;
  CG_HudPlacement(0);
  tmp_u6 = GHIDRA_FIELD(cgs, 33685904, 4);
  if ((GHIDRA_FIELD(cg_gameType, 12, 4) == 5) || ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3)) {
    tmp_pu9 = &g_unk_010b4cc0;
  }
  else {
    tmp_u3 = CG_ConfigString(0xd);
    tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,&g_unk_00120a20);
    tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
    if (tmp_u6 != tmp_l5) {
      tmp_u6 = CG_ConfigString(0xf);
      if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) {
        tmp_pc4 = (char *)(GHIDRA_FIELD(cgs, 33685904, 4) * 0x100 + 0x10b4e40);
        tmp_pu9 = &g_unk_00116957;
      }
      else {
        tmp_pc4 = &g_unk_010b5640 + GHIDRA_FIELD(cgs, 33685904, 4) * 0x100;
        tmp_pu9 = &g_unk_0011695b;
      }
      tmp_u3 = va(tmp_pu9,GHIDRA_FIELD(cgs, 33685904, 4) + 1);
      tmp_pc7 = (char *)Info_ValueForKey(tmp_u6,tmp_u3);
      local_428 = strtol(tmp_pc7,(char **)0x0,10);
      if (*tmp_pc4 == '\0') {
        tmp_pc4 = "No Information Supplied";
      }
      Q_strncpyz(local_41c,tmp_pc4,0x400);
      goto LAB_00084de3;
    }
    if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) {
      tmp_pu9 = &g_unk_010b49c0;
    }
    else {
      tmp_pu9 = &g_unk_010b4b40;
    }
  }
  Q_strncpyz(local_41c,tmp_pu9,0x400);
  local_428 = 0;
LAB_00084de3:
  while( true ) {
    tmp_pc4 = local_41c;
    tmp_pc7 = strchr(tmp_pc4,0x2a);
    if (tmp_pc7 == (char *)0x0) break;
    *tmp_pc7 = '\n';
  }
  CG_FitTextToWidth_Ext
            (tmp_pc4,**(uint32_t **)(param_1 + 0x38),*(float *)(param_1 + 0x10) - 16.0,0x400,
             0x110afec);
  tmp_f2 = *(float *)(param_1 + 0xc) + 12.0;
  while (tmp_u6 = GHIDRA_FIELD(cgs, 33685904, 4), tmp_c10 = *tmp_pc4, tmp_pc7 = tmp_pc4, tmp_c10 != '\0') {
    while (tmp_c10 != '\n') {
      tmp_pc7 = tmp_pc7 + 1;
      tmp_c10 = *tmp_pc7;
      if (tmp_c10 == '\0') goto LAB_00084e62;
    }
    *tmp_pc7 = '\0';
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 4.0,tmp_f2,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_pc4,0,0,0,
                      0x110afec);
    tmp_f2 = tmp_f2 + 8.0;
    tmp_pc4 = tmp_pc7 + 1;
  }
LAB_00084e62:
  if ((GHIDRA_FIELD(cg_gameType, 12, 4) != 5) && ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3)) {
    tmp_u3 = CG_ConfigString(0xd);
    tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,&g_unk_00120a20);
    tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
    tmp_i8 = 1;
    if (tmp_u6 == tmp_l5) {
      if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3) {
        tmp_u6 = CG_ConfigString(0xd);
        tmp_pc4 = (char *)Info_ValueForKey(tmp_u6,&g_unk_00120a20);
        tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
        tmp_i8 = tmp_l5 + 1;
      }
      tmp_u6 = va("1of%i",tmp_i8);
    }
    else {
      if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3) {
        tmp_u6 = CG_ConfigString(0xd);
        tmp_pc4 = (char *)Info_ValueForKey(tmp_u6,&g_unk_00120a20);
        tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
        tmp_i8 = tmp_l5 + 1;
      }
      tmp_u6 = va("%iof%i",GHIDRA_FIELD(cgs, 33685904, 4) + 2,tmp_i8);
    }
    tmp_i8 = CG_Text_Width_Ext(tmp_u6,0x3e4ccccd,0,0x110afec);
    CG_Text_Paint_Ext(((*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10)) - (float)tmp_i8) - 4.0,
                      (*(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14)) - 2.0,0x3e4ccccd,
                      0x3e4ccccd,&colorBlack,tmp_u6,0,0,0,0x110afec);
  }
  tmp_u6 = GHIDRA_FIELD(cgs, 69660, 4);
  if ((local_428 != 1) && (tmp_u6 = GHIDRA_FIELD(cgs, 69664, 4), local_428 != 2)) {
    return;
  }
  CG_DrawPic(*(float *)(param_1 + 8) + 87.0,*(float *)(param_1 + 0xc) + 8.0,
             *(float *)(param_1 + 0x10) - 174.0,*(float *)(param_1 + 0x14) - 8.0,tmp_u6);
  return;
}

long CG_LimboPanel_GetMaxObjectives(void)
{
  long tmp_l1;
  uint32_t tmp_u2;
  char *__nptr;
  
  tmp_l1 = 0;
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3) {
    tmp_u2 = CG_ConfigString(0xd);
    __nptr = (char *)Info_ValueForKey(tmp_u2,&g_unk_00120a20);
    tmp_l1 = strtol(__nptr,(char **)0x0,10);
  }
  return tmp_l1;
}

bool CG_LimboPanel_RenderLight_GetValue(int param_1)
{
  if (*(int *)(param_1 + 0x18) == 0) {
    return *(int *)(param_1 + 0x1c) == GHIDRA_FIELD(cgs, 33685916, 4);
  }
  if (*(int *)(param_1 + 0x18) == 1) {
    return (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == (&teamOrder)[*(int *)(param_1 + 0x1c)];
  }
  return false;
}

uint32_t CG_DrawLimboPlayerHead(uint32_t param_1,int param_2)
{
  uint32_t tmp_u1;
  
  if (param_2 != 0) {
    tmp_u1 = CG_DrawLimboPlayerHead_part_6();
    return tmp_u1;
  }
  return param_1;
}

void CG_DrawBorder(float param_1,float param_2,float param_3,float param_4,int param_5,int param_6)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  uint32_t uStack_c;
  
  uStack_c = 0x852d7;
  local_3c = 0x3dcccccd;
  local_38 = 0x3dcccccd;
  local_34 = 0x3dcccccd;
  local_30 = 0x3f800000;
  local_2c = 0x3e4ccccd;
  local_28 = 0x3e4ccccd;
  local_24 = 0x3e4ccccd;
  local_20 = 0x3f800000;
  CG_HudPlacement(0);
  tmp_f1 = param_2 - 4.0;
  CG_DrawPic(param_1,tmp_f1,param_3,0x40800000,GHIDRA_FIELD(cgs, 131564, 4));
  tmp_f2 = param_2 + param_4;
  CG_DrawPicST(param_1,tmp_f2,param_3,0x40800000,0,0x3f800000,0x3f800000,0,GHIDRA_FIELD(cgs, 131564, 4));
  tmp_f3 = param_1 - 4.0;
  CG_DrawPic(tmp_f3,param_2,0x40800000,param_4,GHIDRA_FIELD(cgs, 131568, 4));
  tmp_f4 = param_1 + param_3;
  CG_DrawPicST(tmp_f4,param_2,0x40800000,param_4,0x3f800000,0,0,0x3f800000,GHIDRA_FIELD(cgs, 131568, 4));
  CG_DrawPicST(tmp_f3,tmp_f1,0x40800000,0x40800000,0,0,0x3f800000,0x3f800000,GHIDRA_FIELD(cgs, 131572, 4));
  CG_DrawPicST(tmp_f4,tmp_f1,0x40800000,0x40800000,0x3f800000,0,0,0x3f800000,GHIDRA_FIELD(cgs, 131572, 4));
  CG_DrawPicST(tmp_f4,tmp_f2,0x40800000,0x40800000,0x3f800000,0x3f800000,0,0,GHIDRA_FIELD(cgs, 131572, 4));
  CG_DrawPicST(tmp_f3,tmp_f2,0x40800000,0x40800000,0,0x3f800000,0x3f800000,0,GHIDRA_FIELD(cgs, 131572, 4));
  if (param_5 != 0) {
    if (param_6 == 0) {
      CG_FillRectFullScreen(param_1,param_2,param_3,param_4,&local_3c);
      return;
    }
    local_1c = param_1;
    local_18 = param_2;
    local_14 = param_3;
    local_10 = param_4;
    tmp_i5 = BG_CursorInRect(&local_1c);
    if (tmp_i5 == 0) {
      tmp_pu6 = &local_3c;
    }
    else {
      tmp_pu6 = &local_2c;
    }
    CG_FillRect(param_1,param_2,param_3,param_4,tmp_pu6);
  }
  return;
}

void CG_LimboPanel_RenderCounterNumber
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               float param_5,uint32_t param_6,uint32_t param_7,int param_8)

{
  float tmp_f1;
  float tmp_f2;
  
  tmp_f1 = (float)(param_8 + -1) - param_5;
  tmp_f2 = (float)param_8;
  CG_HudPlacement(0);
  CG_AdjustFrom640(&param_1,&param_2,&param_3,&param_4);
  trap_R_DrawStretchPic(param_1,param_2,param_3,param_4,0,0,0x3f800000,0x3f800000,param_6);
  trap_R_DrawStretchPic
            (param_1,param_2,param_3,param_4,0,(tmp_f1 + 0.0) * (1.0 / tmp_f2),0x3f800000,
             (1.0 / tmp_f2) * (tmp_f1 + 1.0),param_7);
  return;
}

int CG_LimboPanel_RenderCounter_ValueForButton(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  long double tmp_l4;
  
  tmp_i1 = g_unk_01047ac4;
  tmp_i2 = *(int *)(param_1 + 0x18);
  switch(tmp_i2) {
  case 0:
    tmp_i1 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
    if (tmp_i1 == 3) {
      return tmp_i2;
    }
    if ((tmp_i1 != *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494)) &&
       (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3)) {
      return tmp_i2;
    }
    if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
      tmp_pi3 = (int *)(cgs + 0x940c);
      tmp_i2 = 0;
      do {
        if ((*tmp_pi3 != 0) && (tmp_pi3[0x22] == tmp_i1)) {
          tmp_i2 = tmp_i2 + (uint)(tmp_pi3[0x2b] == *(int *)(param_1 + 0x1c));
        }
        tmp_pi3 = tmp_pi3 + 0x69;
      } while (tmp_pi3 != (int *)(cgs + GHIDRA_FIELD(cgs, 27400, 4) * 0x1a4 + 0x940c));
      return tmp_i2;
    }
    break;
  case 1:
    if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
      tmp_i2 = 0;
    }
    else {
      tmp_pi3 = (int *)(cgs + 0x940c);
      tmp_i2 = 0;
      do {
        if (*tmp_pi3 != 0) {
          tmp_i2 = tmp_i2 + (uint)(tmp_pi3[0x22] == (&teamOrder)[*(int *)(param_1 + 0x1c)]);
        }
        tmp_pi3 = tmp_pi3 + 0x69;
      } while (tmp_pi3 != (int *)(cgs + GHIDRA_FIELD(cgs, 27400, 4) * 0x1a4 + 0x940c));
    }
    return tmp_i2;
  case 2:
    return g_unk_01047ac8;
  case 3:
    tmp_l4 = (long double)CG_CalculateReinfTime_Float(1);
    return (int)ROUND(tmp_l4);
  case 4:
    tmp_i2 = *(int *)(param_1 + 0x1c);
    if (tmp_i2 == 1) {
      return (1 << ((byte)*(uint32_t *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94f4) & 0x1f)) + -1;
    }
    if (tmp_i2 == 2) {
      tmp_i2 = BG_ClassSkillForClass(GHIDRA_FIELD(cgs, 33685916, 4));
      return (1 << ((byte)*(uint32_t *)(cgs + (tmp_i2 + 0x2534 + tmp_i1 * 0x69) * 4 + 0x14) & 0x1f))
             + -1;
    }
    if (tmp_i2 == 0) {
      return (1 << ((byte)*(uint32_t *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94e4) & 0x1f)) + -1;
    }
    break;
  case 5:
    if ((float)GHIDRA_FIELD(cgs, 27396, 4) == 0.0) {
      return 0;
    }
    tmp_i2 = (int)ROUND(((float)GHIDRA_FIELD(cgs, 27396, 4) * 60.0 * 1000.0 - (float)(g_unk_010906e0 - GHIDRA_FIELD(cgs, 28480, 4))
                       ) / 1000.0);
    if (*(int *)(param_1 + 0x1c) == 0) {
      return tmp_i2 % 0x3c;
    }
    if (*(int *)(param_1 + 0x1c) == 1) {
      return tmp_i2 / 0x3c;
    }
    break;
  case 6:
    tmp_i2 = *(int *)(param_1 + 0x1c);
    if (tmp_i2 == 1) {
      return GHIDRA_FIELD(cgs, 33685932, 4);
    }
    if (tmp_i2 == 2) {
      if (GHIDRA_FIELD(cgs, 33685928, 4) == 0) {
        return 0;
      }
      return (GHIDRA_FIELD(cgs, 33685932, 4) * 100) / (int)GHIDRA_FIELD(cgs, 33685928, 4);
    }
    if (tmp_i2 == 0) {
      return GHIDRA_FIELD(cgs, 33685928, 4);
    }
  }
  return 0;
}

uint CG_LimboPanel_RenderCounter(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  uint tmp_u3;
  float tmp_f4;
  uint tmp_u5;
  int tmp_i6;
  uint32_t tmp_u7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  int tmp_i12;
  uint tmp_u13;
  long double tmp_l14;
  float local_9c;
  int local_98;
  uint32_t local_94;
  uint32_t local_90;
  float local_8c;
  float local_88;
  uint local_84;
  float local_50;
  uint32_t local_4c;
  float local_48;
  uint32_t local_44;
  float local_40;
  uint32_t local_3c;
  float local_38;
  uint32_t local_34;
  float local_30 [4];
  float local_20;
  
  tmp_u7 = *(uint32_t *)(param_1 + 0x18);
  switch(tmp_u7) {
  case 0:
  case 1:
    tmp_f2 = 100.0;
    break;
  case 2:
    tmp_f2 = 15.0;
    goto _L327;
  case 3:
  case 5:
    tmp_f2 = 50.0;
    break;
  case 4:
    tmp_f2 = 1000.0;
    goto _L329;
  case 6:
    tmp_i12 = *(int *)(param_1 + 0x24);
    tmp_i11 = CG_LimboPanel_RenderCounter_ValueForButton(param_1);
    tmp_l14 = (long double)Q_fabs((float)(tmp_i12 - tmp_i11));
    if (tmp_l14 < (long double)5.0) {
      tmp_u7 = *(uint32_t *)(param_1 + 0x18);
      tmp_f2 = (float)(int)ROUND((long double)200.0 / tmp_l14);
    }
    else {
      tmp_u7 = *(uint32_t *)(param_1 + 0x18);
      tmp_f2 = 50.0;
    }
    break;
  default:
    tmp_f2 = 1000.0;
  }
  switch(tmp_u7) {
  case 0:
  case 1:
  case 3:
  case 5:
    local_98 = 2;
    break;
  case 2:
_L327:
    if (GHIDRA_FIELD(cg_gameType, 12, 4) == 5) goto switchD_00085d98_default;
    tmp_u5 = CG_LimboPanel_RenderCounter_ValueForButton(param_1);
    local_98 = 5;
    local_84 = *(uint *)(param_1 + 0x18);
    tmp_f1 = 5.0;
    goto joined_r0x00085e1f;
  case 4:
_L329:
    local_98 = (uint)(GHIDRA_FIELD(cg_gameType, 12, 4) != 5) * 5;
    break;
  case 6:
    tmp_i12 = *(int *)(param_1 + 0x1c);
    if (tmp_i12 < 0) goto _L327;
    if (tmp_i12 < 2) {
      local_98 = 4;
    }
    else {
      local_98 = 3;
      if (tmp_i12 != 2) goto _L327;
    }
    break;
  default:
switchD_00085d98_default:
    local_98 = 0;
  }
  tmp_u5 = CG_LimboPanel_RenderCounter_ValueForButton(param_1);
  local_84 = *(uint *)(param_1 + 0x18);
  tmp_f1 = (float)local_98;
joined_r0x00085e1f:
  if (local_84 == 4) {
    local_88 = 0.5;
    local_90 = GHIDRA_FIELD(cgs, 131548, 4);
    local_94 = GHIDRA_FIELD(cgs, 131544, 4);
    local_8c = 1.0;
    tmp_i12 = 2;
  }
  else {
    local_88 = 0.1;
    local_90 = GHIDRA_FIELD(cgs, 131540, 4);
    local_8c = 9.0;
    local_94 = GHIDRA_FIELD(cgs, 131536, 4);
    tmp_i12 = 10;
  }
  tmp_f4 = (float)(int)(g_unk_010906e0 - *(int *)(param_1 + 0x28));
  if (tmp_f2 <= tmp_f4) {
    tmp_u3 = *(uint *)(param_1 + 0x24);
    tmp_u13 = *(uint *)(param_1 + 0x2c);
    if (tmp_u3 == tmp_u13) {
      if (tmp_u5 != tmp_u3) {
        tmp_u13 = (int)(tmp_u5 - tmp_u3) >> 0x1f;
        local_9c = (float)((tmp_u5 - tmp_u3 ^ tmp_u13) - tmp_u13);
        if ((local_84 == 2) || (local_84 == 6)) {
          tmp_i11 = 5;
        }
        else {
          tmp_i11 = 1;
        }
        if (tmp_i11 < (int)local_9c) {
          if ((local_84 == 2) || (local_84 == 6)) {
            local_9c = 7.00649e-45;
          }
          else {
            local_9c = 1.4013e-45;
          }
        }
        if ((int)tmp_u3 < (int)tmp_u5) {
          if (2 < local_84 - 3) {
            tmp_u5 = (int)local_9c + tmp_u3;
          }
LAB_000865b1:
          *(uint *)(param_1 + 0x2c) = tmp_u5;
        }
        else {
          if ((local_84 == 2) || (local_84 == 4)) goto LAB_000865b1;
          *(uint *)(param_1 + 0x2c) = tmp_u3 - (int)local_9c;
        }
        tmp_u5 = g_unk_010906e0;
        *(uint *)(param_1 + 0x28) = g_unk_010906e0;
        tmp_u13 = tmp_u3;
      }
    }
    else {
      *(uint *)(param_1 + 0x24) = tmp_u13;
    }
    if (local_98 != 0) {
      local_30[0] = (float)(int)tmp_u13;
      if (local_98 != 1) {
        tmp_u5 = (int)tmp_u13 / tmp_i12;
        local_30[1] = (float)(int)tmp_u5;
        if (local_98 != 2) {
          tmp_u5 = (int)tmp_u13 / (tmp_i12 * tmp_i12);
          tmp_i11 = tmp_i12 * tmp_i12 * tmp_i12;
          local_30[2] = (float)(int)tmp_u5;
          if (local_98 != 3) {
            tmp_u5 = (int)tmp_u13 / tmp_i11;
            local_30[3] = (float)(int)tmp_u5;
            if (local_98 == 5) {
              tmp_u5 = (int)tmp_u13 / (tmp_i12 * tmp_i11);
              local_20 = (float)(int)tmp_u5;
            }
          }
        }
      }
      goto LAB_00085f40;
    }
LAB_00086122:
    tmp_f2 = *(float *)(param_1 + 8);
    if (local_84 == 4) {
      return tmp_u5;
    }
    local_9c = *(float *)(param_1 + 0x10) / tmp_f1;
LAB_00086140:
    local_98 = local_98 + -1;
    if (local_98 == -1) goto LAB_000860f0;
    do {
      local_3c = *(uint32_t *)(param_1 + 0xc);
      local_38 = local_9c;
      local_34 = *(uint32_t *)(param_1 + 0x14);
      tmp_f1 = local_30[local_98];
      local_98 = local_98 + -1;
      local_40 = tmp_f2;
      CG_HudPlacement(0);
      CG_AdjustFrom640(&local_40,&local_3c,&local_38,&local_34);
      trap_R_DrawStretchPic(local_40,local_3c,local_38,local_34,0,0,0x3f800000,0x3f800000,local_90);
      trap_R_DrawStretchPic
                (local_40,local_3c,local_38,local_34,0,((local_8c - tmp_f1) + 0.0) * local_88,
                 0x3f800000,local_88 * ((local_8c - tmp_f1) + 1.0),local_94);
      tmp_f2 = tmp_f2 + (float)*(int *)(param_1 + 0x30) + local_9c;
    } while (local_98 != -1);
  }
  else {
    tmp_f4 = tmp_f4 / tmp_f2;
    if (local_98 == 0) {
      tmp_u5 = 0;
      goto LAB_00086122;
    }
    tmp_i11 = *(int *)(param_1 + 0x24);
    tmp_i6 = *(int *)(param_1 + 0x2c);
    if (tmp_i11 < tmp_i6) {
      tmp_i8 = tmp_i11 % tmp_i12;
      tmp_u5 = tmp_i6 / tmp_i12;
      tmp_i9 = tmp_i6 % tmp_i12;
      if (tmp_i9 == tmp_i8) {
        local_30[0] = (float)tmp_i9;
      }
      else if (tmp_i8 < tmp_i9) {
        local_30[0] = (float)(tmp_i9 - tmp_i8) * tmp_f4 + (float)tmp_i8;
      }
      else {
        local_30[0] = (float)tmp_i8 + tmp_f4;
      }
      if (local_98 != 1) {
        tmp_i8 = (tmp_i11 / tmp_i12) % tmp_i12;
        tmp_u5 = (tmp_i6 / tmp_i12) / tmp_i12;
        tmp_i9 = (tmp_i6 / tmp_i12) % tmp_i12;
        if (tmp_i9 == tmp_i8) {
          local_30[1] = (float)tmp_i9;
        }
        else if (tmp_i8 < tmp_i9) {
          local_30[1] = (float)(tmp_i9 - tmp_i8) * tmp_f4 + (float)tmp_i8;
        }
        else {
          local_30[1] = (float)tmp_i8 + tmp_f4;
        }
        tmp_i8 = tmp_i12 * tmp_i12;
        if (local_98 != 2) {
          tmp_i9 = (tmp_i11 / tmp_i8) % tmp_i12;
          tmp_u5 = (tmp_i6 / tmp_i8) / tmp_i12;
          tmp_i10 = (tmp_i6 / tmp_i8) % tmp_i12;
          if (tmp_i10 == tmp_i9) {
            local_30[2] = (float)tmp_i10;
          }
          else if (tmp_i9 < tmp_i10) {
            local_30[2] = (float)(tmp_i10 - tmp_i9) * tmp_f4 + (float)tmp_i9;
          }
          else {
            local_30[2] = (float)tmp_i9 + tmp_f4;
          }
          tmp_i8 = tmp_i8 * tmp_i12;
          if (local_98 != 3) {
            tmp_i9 = (tmp_i11 / tmp_i8) % tmp_i12;
            tmp_u5 = (tmp_i6 / tmp_i8) / tmp_i12;
            tmp_i10 = (tmp_i6 / tmp_i8) % tmp_i12;
            if (tmp_i10 == tmp_i9) {
              local_30[3] = (float)tmp_i10;
            }
            else if (tmp_i9 < tmp_i10) {
              local_30[3] = (float)(tmp_i10 - tmp_i9) * tmp_f4 + (float)tmp_i9;
            }
            else {
              local_30[3] = (float)tmp_i9 + tmp_f4;
            }
            if (local_98 == 5) {
              tmp_i11 = (tmp_i11 / (tmp_i8 * tmp_i12)) % tmp_i12;
              tmp_i6 = tmp_i6 / (tmp_i8 * tmp_i12);
              tmp_u5 = tmp_i6 / tmp_i12;
              tmp_i6 = tmp_i6 % tmp_i12;
              if (tmp_i6 == tmp_i11) goto LAB_000865da;
              if (tmp_i11 < tmp_i6) goto LAB_000865f0;
              local_20 = (float)tmp_i11 + tmp_f4;
            }
          }
        }
      }
    }
    else {
      tmp_i8 = tmp_i11 % tmp_i12;
      tmp_u5 = tmp_i6 / tmp_i12;
      tmp_i9 = tmp_i6 % tmp_i12;
      if (tmp_i9 == tmp_i8) {
        local_30[0] = (float)tmp_i9;
      }
      else if (tmp_i8 < tmp_i9) {
        local_30[0] = (float)tmp_i8 - tmp_f4;
      }
      else {
        local_30[0] = (float)(tmp_i9 - tmp_i8) * tmp_f4 + (float)tmp_i8;
      }
      if (local_98 != 1) {
        tmp_i8 = (tmp_i11 / tmp_i12) % tmp_i12;
        tmp_u5 = (tmp_i6 / tmp_i12) / tmp_i12;
        tmp_i9 = (tmp_i6 / tmp_i12) % tmp_i12;
        if (tmp_i9 == tmp_i8) {
          local_30[1] = (float)tmp_i9;
        }
        else if (tmp_i8 < tmp_i9) {
          local_30[1] = (float)tmp_i8 - tmp_f4;
        }
        else {
          local_30[1] = (float)(tmp_i9 - tmp_i8) * tmp_f4 + (float)tmp_i8;
        }
        tmp_i8 = tmp_i12 * tmp_i12;
        if (local_98 != 2) {
          tmp_i9 = (tmp_i11 / tmp_i8) % tmp_i12;
          tmp_u5 = (tmp_i6 / tmp_i8) / tmp_i12;
          tmp_i10 = (tmp_i6 / tmp_i8) % tmp_i12;
          if (tmp_i10 == tmp_i9) {
            local_30[2] = (float)tmp_i10;
          }
          else if (tmp_i9 < tmp_i10) {
            local_30[2] = (float)tmp_i9 - tmp_f4;
          }
          else {
            local_30[2] = (float)(tmp_i10 - tmp_i9) * tmp_f4 + (float)tmp_i9;
          }
          tmp_i8 = tmp_i8 * tmp_i12;
          if (local_98 != 3) {
            tmp_i9 = (tmp_i11 / tmp_i8) % tmp_i12;
            tmp_u5 = (tmp_i6 / tmp_i8) / tmp_i12;
            tmp_i10 = (tmp_i6 / tmp_i8) % tmp_i12;
            if (tmp_i10 == tmp_i9) {
              local_30[3] = (float)tmp_i10;
            }
            else if (tmp_i9 < tmp_i10) {
              local_30[3] = (float)tmp_i9 - tmp_f4;
            }
            else {
              local_30[3] = (float)(tmp_i10 - tmp_i9) * tmp_f4 + (float)tmp_i9;
            }
            if (local_98 == 5) {
              tmp_i11 = (tmp_i11 / (tmp_i8 * tmp_i12)) % tmp_i12;
              tmp_i6 = tmp_i6 / (tmp_i8 * tmp_i12);
              tmp_u5 = tmp_i6 / tmp_i12;
              tmp_i6 = tmp_i6 % tmp_i12;
              if (tmp_i6 == tmp_i11) {
LAB_000865da:
                local_20 = (float)tmp_i6;
              }
              else if (tmp_i11 < tmp_i6) {
                local_20 = (float)tmp_i11 - tmp_f4;
              }
              else {
LAB_000865f0:
                local_20 = (float)tmp_i11 + (float)(tmp_i6 - tmp_i11) * tmp_f4;
              }
            }
          }
        }
      }
    }
LAB_00085f40:
    tmp_f2 = *(float *)(param_1 + 8);
    local_9c = *(float *)(param_1 + 0x10) / tmp_f1;
    if (local_84 != 4) goto LAB_00086140;
    tmp_i12 = 0;
    do {
      local_4c = *(uint32_t *)(param_1 + 0xc);
      local_44 = *(uint32_t *)(param_1 + 0x14);
      tmp_f1 = local_30[tmp_i12];
      tmp_i12 = tmp_i12 + 1;
      local_50 = tmp_f2;
      local_48 = local_9c;
      CG_HudPlacement(0);
      CG_AdjustFrom640(&local_50,&local_4c,&local_48,&local_44);
      trap_R_DrawStretchPic(local_50,local_4c,local_48,local_44,0,0,0x3f800000,0x3f800000,local_90);
      trap_R_DrawStretchPic
                (local_50,local_4c,local_48,local_44,0,((local_8c - tmp_f1) + 0.0) * local_88,
                 0x3f800000,local_88 * ((local_8c - tmp_f1) + 1.0),local_94);
      tmp_f2 = tmp_f2 + (float)*(int *)(param_1 + 0x30) + local_9c;
    } while (tmp_i12 < local_98);
  }
  tmp_u5 = *(uint *)(param_1 + 0x18);
  local_84 = tmp_u5;
LAB_000860f0:
  if (1 < local_84) {
    return tmp_u5;
  }
  CG_HudPlacement(0);
  tmp_u5 = CG_DrawPic(*(float *)(param_1 + 8) - 2.0,*(float *)(param_1 + 0xc) - 2.0,
                     *(float *)(param_1 + 0x10) * 1.4,*(float *)(param_1 + 0x14) + 7.0,
                     GHIDRA_FIELD(cgs, 131696, 4));
  return tmp_u5;
}

int CG_LimboPanel_RenderCounter_RollTimeForButton(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  long double tmp_l3;
  
  switch(*(uint32_t *)(param_1 + 0x18)) {
  case 0:
  case 1:
    return 100;
  case 2:
    return 0xf;
  case 3:
  case 5:
    goto _L505;
  default:
    return 1000;
  case 6:
    tmp_i1 = *(int *)(param_1 + 0x24);
    tmp_i2 = CG_LimboPanel_RenderCounter_ValueForButton(param_1);
    tmp_l3 = (long double)Q_fabs((float)(tmp_i1 - tmp_i2));
    if (tmp_l3 < (long double)5.0) {
      return (int)ROUND((long double)200.0 / tmp_l3);
    }
_L505:
    return 0x32;
  }
}

uint32_t CG_LimboPanel_RenderCounter_MaxChangeForButton(int param_1)
{
  if ((*(int *)(param_1 + 0x18) != 2) && (*(int *)(param_1 + 0x18) != 6)) {
    return 1;
  }
  return 5;
}

char CG_LimboPanel_RenderCounter_NumRollers(int param_1)
{
  int tmp_i1;
  char tmp_c2;
  
  switch(*(uint32_t *)(param_1 + 0x18)) {
  case 0:
  case 1:
  case 3:
  case 5:
    return '\x02';
  case 2:
    goto _L524;
  case 4:
    return (GHIDRA_FIELD(cg_gameType, 12, 4) != 5) * '\x05';
  case 6:
    tmp_i1 = *(int *)(param_1 + 0x1c);
    if (-1 < tmp_i1) {
      if (tmp_i1 < 2) {
        return '\x04';
      }
      if (tmp_i1 == 2) {
        return '\x03';
      }
    }
_L524:
    tmp_c2 = '\0';
    if (GHIDRA_FIELD(cg_gameType, 12, 4) != 5) {
      tmp_c2 = '\x06';
    }
    return tmp_c2;
  default:
    return '\0';
  }
}

uint32_t CG_LimboPanel_RenderCounter_CountsDown(int param_1)
{
  if ((*(int *)(param_1 + 0x18) != 2) && (*(int *)(param_1 + 0x18) != 4)) {
    return 1;
  }
  return 0;
}

bool CG_LimboPanel_RenderCounter_CountsUp(int param_1)
{
  return 2 < *(int *)(param_1 + 0x18) - 3U;
}

uint32_t CG_LimboPanel_RenderCounter_StartSet(int param_1)
{
  if ((*(int *)(param_1 + 0x18) != 3) && (*(int *)(param_1 + 0x18) != 5)) {
    return 0;
  }
  return 1;
}

bool CG_LimboPanel_RenderCounter_IsReversed(int param_1)
{
  return *(int *)(param_1 + 0x18) == 4;
}

void CG_LimboPanel_RenderCounter_GetShaders
               (int param_1,uint32_t *param_2,uint32_t *param_3,uint32_t *param_4)

{
  if (*(int *)(param_1 + 0x18) != 4) {
    *param_2 = GHIDRA_FIELD(cgs, 131540, 4);
    *param_3 = GHIDRA_FIELD(cgs, 131536, 4);
    *param_4 = 10;
    return;
  }
  *param_2 = GHIDRA_FIELD(cgs, 131548, 4);
  *param_3 = GHIDRA_FIELD(cgs, 131544, 4);
  *param_4 = 2;
  return;
}

void CG_LimboPanel_Init(void)
{
  BG_PanelButtonsSetup(&limboPanelButtons);
  return;
}

uint32_t CG_LimboPanel_Draw(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  long tmp_l4;
  uint32_t tmp_u5;
  
  tmp_i1 = BG_PanelButtonsGetHighlightButton(&limboPanelButtons);
  if ((tmp_i1 != 0) && (tmp_i1 != lastHighlight_12462)) {
    lastHighlight_12462 = tmp_i1;
  }
  if (g_unk_010906e0 < g_unk_010b3b28) {
    CG_DrawPic(0x43918000,0x43bb0000,0x42f00000,0x42f00000,GHIDRA_FIELD(cgs, 131748, 4));
  }
  BG_PanelButtonsRender(&limboPanelButtons);
  trap_R_SetColor(0);
  CG_DrawPic((float)g_unk_010261a4,(float)g_unk_010261a8,0x42000000,0x42000000,GHIDRA_FIELD(cgs, 131752, 4));
  tmp_u5 = GHIDRA_FIELD(cgs, 33685972, 4);
  if (GHIDRA_FIELD(cgs, 33685972, 4) == -1) {
    return 1;
  }
  if (g_unk_010906e0 - GHIDRA_FIELD(cgs, 33685976, 4) < 0x3e9) {
    return 1;
  }
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) {
    if ((GHIDRA_FIELD(cgs, 33685968, 4) == -1) && (GHIDRA_FIELD(cgs, 33685960, 4) == -1)) {
      return 1;
    }
  }
  else {
    if (GHIDRA_FIELD(cgs, 33685972, 4) != GHIDRA_FIELD(cgs, 33685904, 4)) {
      return 1;
    }
    if ((GHIDRA_FIELD(cgs, 33685972, 4) == GHIDRA_FIELD(cgs, 33685968, 4)) && (GHIDRA_FIELD(cgs, 33685960, 4) == -1)) {
      return 1;
    }
    tmp_u2 = CG_ConfigString(0xd);
    tmp_pc3 = (char *)Info_ValueForKey(tmp_u2,&g_unk_00120a20);
    tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
    if (((tmp_u5 == tmp_l4) && (GHIDRA_FIELD(cgs, 33685968, 4) == -1)) && (GHIDRA_FIELD(cgs, 33685960, 4) == -1)) {
      return 1;
    }
    if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3) {
      tmp_u5 = CG_ConfigString(0xd);
      tmp_pc3 = (char *)Info_ValueForKey(tmp_u5,&g_unk_00120a20);
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      if ((GHIDRA_FIELD(cgs, 33685904, 4) != tmp_l4) &&
         (tmp_u5 = GHIDRA_FIELD(cgs, 33685904, 4), (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3)) goto LAB_00086d2d;
    }
  }
  tmp_u5 = 0xffffffff;
LAB_00086d2d:
  tmp_u5 = va("obj %i",tmp_u5);
  trap_SendClientCommand(tmp_u5);
  GHIDRA_FIELD(cgs, 33685976, 4) = g_unk_010906e0;
  GHIDRA_FIELD(cgs, 33685972, 4) = GHIDRA_FIELD(cgs, 33685904, 4);
  return 1;
}

void CG_LimboPanel_KeyHandling(int param_1,int param_2)
{
  int tmp_i1;
  int local_14;
  int local_10;
  
  tmp_i1 = BG_PanelButtonsKeyEvent(param_1,param_2,&limboPanelButtons);
  if ((tmp_i1 == 0) && (param_2 != 0)) {
    (*g_unk_0102613c)("openlimbomenu",&local_14,&local_10);
    if (((param_1 == local_14) && (local_14 != -1)) || ((param_1 == local_10 && (local_10 != -1))))
    {
      CG_EventHandling(0,0);
    }
    else if (param_1 != 0) {
      CG_CommandCentreSpawnPointClick();
      return;
    }
  }
  return;
}

void CG_LimboPanel_GetWeaponCardIconData
               (uint param_1,uint32_t *param_2,uint32_t *param_3,uint32_t *param_4,
               uint32_t *param_5,uint32_t *param_6,uint32_t *param_7,uint32_t *param_8)

{
  switch(param_1) {
  default:
    *param_2 = 0;
    break;
  case 2:
  case 7:
  case 0xe:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x1e:
  case 0x22:
  case 0x23:
  case 0x26:
  case 0x2c:
  case 0x2d:
    *param_2 = GHIDRA_FIELD(cgs, 131704, 4);
    if (param_1 != 7) goto LAB_00086ecf;
    goto LAB_00086f20;
  case 3:
  case 5:
  case 6:
  case 8:
  case 10:
  case 0x1d:
  case 0x1f:
  case 0x21:
    *param_2 = GHIDRA_FIELD(cgs, 131700, 4);
  }
  if (param_1 == 7) {
LAB_00086f20:
    *param_5 = 0;
    *param_7 = 0x3f000000;
  }
  else {
LAB_00086ecf:
    if (param_1 < 8) {
      if (param_1 == 2) goto LAB_00086f20;
    }
    else if ((param_1 == 0xe) || (param_1 == 0x26)) goto LAB_00086f20;
    *param_5 = 0;
    *param_7 = 0x3f800000;
  }
  switch(param_1) {
  default:
    *param_6 = 0;
    *param_8 = 0x3f800000;
    break;
  case 2:
  case 6:
  case 0x23:
    *param_6 = 0x3e800000;
    *param_8 = 0x3ec00000;
    break;
  case 3:
  case 0x16:
    *param_6 = 0x3f200000;
    *param_8 = 0x3f400000;
    break;
  case 5:
  case 0x26:
  case 0x2c:
    *param_6 = 0x3e000000;
    *param_8 = 0x3e800000;
    break;
  case 7:
  case 0x1f:
  case 0x22:
    *param_6 = 0x3ec00000;
    *param_8 = 0x3f000000;
    break;
  case 8:
  case 0x18:
    *param_6 = 0x3f600000;
    *param_8 = 0x3f800000;
    break;
  case 10:
  case 0x1e:
    *param_6 = 0x3f400000;
    *param_8 = 0x3f600000;
    break;
  case 0xe:
  case 0x21:
  case 0x2d:
    *param_6 = 0;
    *param_8 = 0x3e000000;
    break;
  case 0x17:
  case 0x1d:
    *param_6 = 0x3f000000;
    *param_8 = 0x3f200000;
  }
  *param_4 = 0x3f800000;
  if (param_1 != 7) {
    if (param_1 < 8) {
      if (param_1 != 2) goto LAB_00086fab;
    }
    else if ((param_1 != 0xe) && (param_1 != 0x26)) {
LAB_00086fab:
      *param_3 = 0x3f800000;
      return;
    }
  }
  *param_3 = 0x3f000000;
  return;
}

uint32_t CG_LimboPanel_GetTeam(void)
{
  return (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
}

int CG_LimboPanel_GetRealTeam(void)
{
  if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3) {
    return *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
  }
  return (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
}

uint32_t CG_LimboPanel_GetClass(void)
{
  return GHIDRA_FIELD(cgs, 33685916, 4);
}

void CG_LimboPanel_GetCharacter(void)
{
  BG_GetCharacter((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
  return;
}

void CG_LimboPanel_GetPlayerClass(void)
{
  BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
  return;
}

void CG_LimboPanel_SetSelectedWeaponNumForSlot(int param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  
  if (param_1 == 0) {
    GHIDRA_FIELD(cgs, 33685920, 4) = param_2;
    return;
  }
  GHIDRA_FIELD(cgs, 33685924, 4) = param_2;
  tmp_u1 = va("%i",param_2);
  trap_Cvar_Set("cg_limbo_secondary",tmp_u1);
  return;
}

void CG_LimboPanel_RequestObjective(void)
{
  uint32_t tmp_u1;
  char *__nptr;
  long tmp_l2;
  
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3) {
    tmp_u1 = CG_ConfigString(0xd);
    __nptr = (char *)Info_ValueForKey(tmp_u1,&g_unk_00120a20);
    tmp_l2 = strtol(__nptr,(char **)0x0,10);
    if ((GHIDRA_FIELD(cgs, 33685904, 4) != tmp_l2) &&
       (tmp_u1 = GHIDRA_FIELD(cgs, 33685904, 4), (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3)) goto LAB_000872c6;
  }
  tmp_u1 = 0xffffffff;
LAB_000872c6:
  tmp_u1 = va("obj %i",tmp_u1);
  trap_SendClientCommand(tmp_u1);
  GHIDRA_FIELD(cgs, 33685972, 4) = GHIDRA_FIELD(cgs, 33685904, 4);
  GHIDRA_FIELD(cgs, 33685976, 4) = g_unk_010906e0;
  return;
}

uint64_t CG_LimboPanel_ClassCount(int param_1)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint local_14;
  
  local_14 = (uint)(param_1 == -1);
  tmp_pu1 = cgs;
  if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
    if (param_1 == -1) {
      tmp_i2 = 0;
      local_14 = 1;
      do {
        if ((g_unk_01047ac4 != tmp_i2) && (*(int *)(tmp_pu1 + 0x940c) != 0)) {
          local_14 = local_14 + (*(int *)(tmp_pu1 + 0x9494) == (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)]);
        }
        tmp_i2 = tmp_i2 + 1;
        tmp_pu1 = tmp_pu1 + 0x1a4;
      } while (tmp_i2 != GHIDRA_FIELD(cgs, 27400, 4));
      return CONCAT44(local_14,local_14);
    }
    tmp_i2 = 0;
    do {
      while ((((g_unk_01047ac4 == tmp_i2 || (*(int *)(tmp_pu1 + 0x940c) == 0)) ||
              (*(int *)(tmp_pu1 + 0x9494) != (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)])) ||
             ((*(int *)(tmp_pu1 + 0x94b8) != param_1 && (*(int *)(tmp_pu1 + 0x94bc) != param_1))))) {
        tmp_i2 = tmp_i2 + 1;
        tmp_pu1 = tmp_pu1 + 0x1a4;
        if (tmp_i2 == GHIDRA_FIELD(cgs, 27400, 4)) goto LAB_000873c0;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pu1 = tmp_pu1 + 0x1a4;
      local_14 = local_14 + 1;
    } while (tmp_i2 != GHIDRA_FIELD(cgs, 27400, 4));
  }
LAB_000873c0:
  return CONCAT44(local_14,local_14);
}

uint CG_LimboPanel_TeamCount(int param_1)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint local_20;
  
  local_20 = (uint)(param_1 == -1);
  tmp_pu1 = cgs;
  if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
    if (param_1 - 0x24U < 2) {
      tmp_i2 = 0;
      do {
        if ((((g_unk_01047ac4 != tmp_i2) && (*(int *)(tmp_pu1 + 0x940c) != 0)) &&
            (*(int *)(tmp_pu1 + 0x9494) == (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)])) &&
           ((*(int *)(tmp_pu1 + 0x956c) != 0 &&
            ((*(int *)(tmp_pu1 + 0x9560) == *(int *)(weapAlts + param_1 * 4) ||
             (*(int *)(weapAlts + param_1 * 4) == *(int *)(tmp_pu1 + 0x9568))))))) {
          local_20 = local_20 + 1;
        }
        tmp_i2 = tmp_i2 + 1;
        tmp_pu1 = tmp_pu1 + 0x1a4;
      } while (tmp_i2 != GHIDRA_FIELD(cgs, 27400, 4));
    }
    else {
      if (param_1 == -1) {
        tmp_i2 = 0;
        local_20 = 1;
        do {
          if ((g_unk_01047ac4 != tmp_i2) && (*(int *)(tmp_pu1 + 0x940c) != 0)) {
            local_20 = local_20 + (*(int *)(tmp_pu1 + 0x9494) == (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)]);
          }
          tmp_i2 = tmp_i2 + 1;
          tmp_pu1 = tmp_pu1 + 0x1a4;
        } while (tmp_i2 != GHIDRA_FIELD(cgs, 27400, 4));
        return local_20;
      }
      tmp_i2 = 0;
      do {
        while ((((g_unk_01047ac4 == tmp_i2 || (*(int *)(tmp_pu1 + 0x940c) == 0)) ||
                (*(int *)(tmp_pu1 + 0x9494) != (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)])) ||
               (((*(int *)(tmp_pu1 + 0x9560) != param_1 && (*(int *)(tmp_pu1 + 0x9568) != param_1)) &&
                ((*(int *)(tmp_pu1 + 0x9560) != *(int *)(weapTeamConversion + param_1 * 4) &&
                 (*(int *)(tmp_pu1 + 0x9568) != *(int *)(weapTeamConversion + param_1 * 4)))))))) {
          tmp_i2 = tmp_i2 + 1;
          tmp_pu1 = tmp_pu1 + 0x1a4;
          if (tmp_i2 == GHIDRA_FIELD(cgs, 27400, 4)) {
            return local_20;
          }
        }
        tmp_i2 = tmp_i2 + 1;
        tmp_pu1 = tmp_pu1 + 0x1a4;
        local_20 = local_20 + 1;
      } while (tmp_i2 != GHIDRA_FIELD(cgs, 27400, 4));
    }
  }
  return local_20;
}

bool CG_LimboPanel_ClassIsDisabled(int param_1)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  uint local_14;
  
  tmp_pu2 = cgs;
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3) {
    local_14 = (uint)(param_1 == -1);
    if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
      if (param_1 == -1) {
        tmp_i1 = 0;
        do {
          tmp_i1 = tmp_i1 + 1;
        } while (tmp_i1 != GHIDRA_FIELD(cgs, 27400, 4));
        return false;
      }
      tmp_i1 = 0;
      do {
        while ((((tmp_i1 != g_unk_01047ac4 && (*(int *)(tmp_pu2 + 0x940c) != 0)) &&
                ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == *(int *)(tmp_pu2 + 0x9494))) &&
               ((param_1 == *(int *)(tmp_pu2 + 0x94b8) || (param_1 == *(int *)(tmp_pu2 + 0x94bc))))))
        {
          tmp_i1 = tmp_i1 + 1;
          tmp_pu2 = tmp_pu2 + 0x1a4;
          local_14 = local_14 + 1;
          if (tmp_i1 == GHIDRA_FIELD(cgs, 27400, 4)) goto LAB_000876d0;
        }
        tmp_i1 = tmp_i1 + 1;
        tmp_pu2 = tmp_pu2 + 0x1a4;
      } while (tmp_i1 != GHIDRA_FIELD(cgs, 27400, 4));
    }
LAB_000876d0:
    switch(param_1) {
    case 0:
      tmp_i1 = GHIDRA_FIELD(cgs, 33785412, 4);
      break;
    case 1:
      tmp_i1 = GHIDRA_FIELD(cgs, 33785416, 4);
      break;
    case 2:
      tmp_i1 = GHIDRA_FIELD(cgs, 33785420, 4);
      break;
    case 3:
      tmp_i1 = GHIDRA_FIELD(cgs, 33785424, 4);
      break;
    case 4:
      tmp_i1 = GHIDRA_FIELD(cgs, 33785428, 4);
      break;
    default:
      goto switchD_000876e4_default;
    }
    return tmp_i1 != -1 && tmp_i1 <= (int)local_14;
  }
switchD_000876e4_default:
  return false;
}

void CG_LimboPanel_RenderClassButton(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint local_7c;
  float local_78;
  float local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_64;
  float local_5c;
  float local_58;
  float local_54;
  float local_50 [15];
  uint32_t uStack_14;
  
  uStack_14 = 0x87789;
  local_50[1] = 1.0;
  local_50[2] = 1.0;
  local_50[3] = 1.0;
  local_50[4] = 0.4;
  local_50[5] = 1.0;
  local_50[6] = 1.0;
  local_50[7] = 1.0;
  local_50[8] = 0.75;
  local_50[9] = 1.0;
  local_50[10] = 1.0;
  local_50[0xb] = 1.0;
  local_50[0xc] = 0.6;
  CG_HudPlacement(0);
  CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
             *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131620, 4));
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3) {
    if (*(int *)(param_1 + 0x1c) == GHIDRA_FIELD(cgs, 33685916, 4)) {
      CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131616, 4));
    }
    else {
      tmp_i2 = BG_CursorInRect(param_1 + 8);
      if (tmp_i2 != 0) {
        trap_R_SetColor(local_50 + 1);
        CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                   *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131616, 4));
        trap_R_SetColor(0);
      }
    }
  }
  local_7c = 0;
  do {
    tmp_i2 = g_unk_01047ac4;
    tmp_i3 = BG_ClassSkillForClass(*(uint32_t *)(param_1 + 0x1c));
    tmp_i1 = g_unk_01047ac4;
    if (*(int *)(cgs + (tmp_i3 + 0x2534 + tmp_i2 * 0x69) * 4 + 0x14) <= (int)local_7c) break;
    if (local_7c < 2) {
      local_6c = 0x3f800000;
      local_74 = 0.5;
    }
    else {
      local_6c = 0x3f000000;
      local_74 = 0.0;
    }
    if (local_7c - 1 < 2) {
      local_70 = 0x3f800000;
      local_78 = 0.5;
    }
    else {
      local_70 = 0x3f000000;
      local_78 = 0.0;
    }
    tmp_i2 = BG_ClassSkillForClass(*(uint32_t *)(param_1 + 0x1c));
    if (*(int *)(cgs + (tmp_i2 + 0x2534 + tmp_i1 * 0x69) * 4 + 0x14) < 5) {
      local_64 = GHIDRA_FIELD(cgs, 131628, 4);
      tmp_u4 = GHIDRA_FIELD(cgs, 131624, 4);
    }
    else {
      local_64 = GHIDRA_FIELD(cgs, 131656, 4);
      tmp_u4 = GHIDRA_FIELD(cgs, 131652, 4);
    }
    local_5c = local_74 * *(float *)(param_1 + 0x10) + *(float *)(param_1 + 8);
    local_58 = local_78 * *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0xc);
    local_54 = *(float *)(param_1 + 0x10) * 0.5;
    local_50[0] = *(float *)(param_1 + 0x14) * 0.5;
    CG_AdjustFrom640(&local_5c,&local_58,&local_54,local_50);
    if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) {
LAB_00087b40:
      trap_R_DrawStretchPic
                (local_5c,local_58,local_54,local_50[0],local_74,local_78,local_6c,local_70,local_64
                );
    }
    else if (*(int *)(param_1 + 0x1c) == GHIDRA_FIELD(cgs, 33685916, 4)) {
      trap_R_DrawStretchPic
                (local_5c,local_58,local_54,local_50[0],local_74,local_78,local_6c,local_70,tmp_u4);
    }
    else {
      tmp_i2 = BG_CursorInRect(param_1 + 8);
      if (tmp_i2 == 0) goto LAB_00087b40;
      trap_R_SetColor(local_50 + 9);
      trap_R_DrawStretchPic
                (local_5c,local_58,local_54,local_50[0],local_74,local_78,local_6c,local_70,tmp_u4);
      trap_R_SetColor(0);
    }
    local_7c = local_7c + 1;
  } while (local_7c != 4);
  if (((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) || (*(int *)(param_1 + 0x1c) != GHIDRA_FIELD(cgs, 33685916, 4))) {
    trap_R_SetColor(local_50 + 5);
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),
               *(uint32_t *)(cgs + *(int *)(param_1 + 0x1c) * 4 + 0x20230));
    trap_R_SetColor(0);
  }
  else {
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),
               *(uint32_t *)(cgs + *(int *)(param_1 + 0x1c) * 4 + 0x20230));
  }
  tmp_i2 = CG_LimboPanel_ClassIsDisabled(*(uint32_t *)(param_1 + 0x1c));
  if (tmp_i2 != 0) {
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 67964, 4));
  }
  return;
}

bool CG_LimboPanel_RealWeaponIsDisabled(int param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  int local_3c;
  
  tmp_pu3 = cgs;
  tmp_pi1 = (int *)BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) {
    return true;
  }
  if (param_1 == 3) {
    return false;
  }
  if (param_1 == 8) {
    return false;
  }
  if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
    local_3c = 1;
  }
  else {
    local_3c = 1;
    tmp_i2 = 0;
    do {
      if ((tmp_i2 != g_unk_01047ac4) && (*(int *)(tmp_pu3 + 0x940c) != 0)) {
        local_3c = local_3c + (uint)((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == *(int *)(tmp_pu3 + 0x9494));
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pu3 = tmp_pu3 + 0x1a4;
    } while (tmp_i2 != GHIDRA_FIELD(cgs, 27400, 4));
  }
  tmp_i2 = CG_LimboPanel_TeamCount(param_1);
  if (((((param_1 == bg_heavyWeapons) || (param_1 == g_unk_0013e4a8)) || (param_1 == g_unk_0013e4ac)) ||
      (((param_1 == g_unk_0013e4b0 || (param_1 == g_unk_0013e4b4)) || (param_1 == g_unk_0013e4b8)))) &&
     (ROUND((float)local_3c * (float)GHIDRA_FIELD(cgs, 27660, 4)) <= (float)tmp_i2)) {
    return true;
  }
  if (param_1 == 5) {
    tmp_i4 = GHIDRA_FIELD(cgs, 33785392, 4);
    if ((float)local_3c / ((float)(int)GHIDRA_FIELD(cgs, 27400, 4) * 0.5) <= (float)GHIDRA_FIELD(cgs, 33785388, 4)) {
      return true;
    }
    goto joined_r0x00087e36;
  }
  switch(param_1) {
  case 6:
    tmp_i4 = GHIDRA_FIELD(cgs, 33785400, 4);
    break;
  default:
    goto LAB_00087e42;
  case 10:
    if (*tmp_pi1 == 4) {
      return false;
    }
    return (cgs[0x2038e69] & 2) == 0;
  case 0x1d:
    tmp_i4 = GHIDRA_FIELD(cgs, 33785396, 4);
    goto joined_r0x00087eb5;
  case 0x21:
    tmp_i4 = GHIDRA_FIELD(cgs, 33785404, 4);
joined_r0x00087eb5:
    if (tmp_i2 < tmp_i4) {
      return false;
    }
    goto LAB_00087e38;
  case 0x24:
  case 0x25:
    tmp_i4 = GHIDRA_FIELD(cgs, 33785408, 4);
  }
joined_r0x00087e36:
  if (tmp_i4 <= tmp_i2) {
LAB_00087e38:
    if (tmp_i4 != -1) {
      return true;
    }
  }
LAB_00087e42:
  return false;
}

void CG_LimboPanel_WeaponPanel_DrawWeapon
               (float *param_1,int param_2,int param_3,uint32_t param_4,int param_5)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  int tmp_i6;
  uint32_t *tmp_pu7;
  uint32_t tmp_u8;
  uint32_t local_48;
  float local_44;
  float local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x87f3b;
  local_48 = GHIDRA_FIELD(cgs, 131560, 4);
  tmp_i5 = CG_Text_Width_Ext(param_4,0x3e4ccccd,0,0x110afec);
  local_2c = 0x3f800000;
  local_28 = 0x3f800000;
  local_24 = 0x3f800000;
  local_20 = 0.6;
  tmp_f1 = *param_1;
  tmp_f2 = param_1[2];
  CG_HudPlacement(0);
  CG_DrawPic(*param_1,param_1[1],param_1[2],param_1[3],local_48);
  if ((param_3 == 0) || (tmp_i6 = BG_CursorInRect(param_1), tmp_i6 == 0)) {
    tmp_u8 = *(uint32_t *)(ammoTableMP + param_2 * 0x48 + 0x40);
    tmp_pu7 = &g_unk_00147608;
  }
  else {
    local_2c = g_unk_00147608;
    local_28 = g_unk_0014760c;
    local_24 = g_unk_00147610;
    local_20 = g_unk_00147614 * 1.5;
    tmp_u8 = *(uint32_t *)(ammoTableMP + param_2 * 0x48 + 0x40);
    tmp_pu7 = &local_2c;
  }
  CG_Text_Paint_Ext(*param_1 + 4.0,param_1[1] + 12.0,weaponPanelNameFont,g_unk_00147604,tmp_pu7,tmp_u8,0
                    ,0,g_unk_00147618,g_unk_00147620);
  trap_R_SetColor(0);
  tmp_f3 = *param_1;
  tmp_f4 = param_1[3] * 0.25 + param_1[1];
  CG_LimboPanel_GetWeaponCardIconData
            (param_2,&local_48,&local_44,&local_40,&local_3c,&local_34,&local_38,&local_30);
  local_44 = param_1[2] * local_44;
  local_40 = local_40 * param_1[3] * 0.75;
  CG_DrawPicST(tmp_f3,tmp_f4,local_44,local_40,local_3c,local_34,local_38,local_30,local_48);
  if (param_5 == 0) {
    if (param_2 != 0x16) goto LAB_0008815f;
LAB_00088235:
    tmp_i6 = CG_LimboPanel_RealWeaponIsDisabled(0x24);
  }
  else {
    trap_R_SetColor(&local_2c);
    CG_DrawPic(tmp_f3,(local_40 - 16.0) * 0.5 + tmp_f4 + 4.0,local_44,0x41800000,GHIDRA_FIELD(cgs, 131576, 4));
    trap_R_SetColor(0);
    if (param_2 == 0x16) goto LAB_00088235;
LAB_0008815f:
    if (param_2 != 0x17) goto LAB_00088168;
    tmp_i6 = CG_LimboPanel_RealWeaponIsDisabled(0x25);
  }
  if (tmp_i6 != 0) {
    trap_R_SetColor(&local_2c);
    CG_DrawPic(*param_1,param_1[1],param_1[2],param_1[3],GHIDRA_FIELD(cgs, 131580, 4));
    trap_R_SetColor(0);
  }
LAB_00088168:
  CG_Text_Paint_Ext(((tmp_f1 + tmp_f2) - (float)tmp_i5) - 4.0,(param_1[1] + param_1[3]) - 2.0,
                    0x3e4ccccd,0x3e4ccccd,&colorBlack,param_4,0,0,0,0x110afec);
  return;
}

int CG_LimboPanel_WeaponCount_ForSlot(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (param_1 != 1) {
    if (((cgs[g_unk_01047ac4 * 0x1a4 + 0x95a0] & 0x10) != 0) && (GHIDRA_FIELD(cgs, 33685916, 4) == 0)) {
      return 3 - (uint)((*(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x959c) & 0x10) == 0);
    }
    return 2 - (uint)((*(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x959c) & 0x10) == 0);
  }
  tmp_i1 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
  if (*(int *)(tmp_i1 + 0x10) == 0) {
    return 0;
  }
  if (*(int *)(tmp_i1 + 0x10) == 10) {
    tmp_i3 = 0;
    tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10);
    if (tmp_i2 != 0) goto LAB_00088420;
  }
  tmp_i3 = 1;
LAB_00088420:
  if (*(int *)(tmp_i1 + 0x14) != 0) {
    if ((*(int *)(tmp_i1 + 0x14) != 10) ||
       (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
      tmp_i3 = tmp_i3 + 1;
    }
    if (*(int *)(tmp_i1 + 0x18) != 0) {
      if ((*(int *)(tmp_i1 + 0x18) != 10) ||
         (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
        tmp_i3 = tmp_i3 + 1;
      }
      if (*(int *)(tmp_i1 + 0x1c) != 0) {
        if ((*(int *)(tmp_i1 + 0x1c) != 10) ||
           (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
          tmp_i3 = tmp_i3 + 1;
        }
        if (*(int *)(tmp_i1 + 0x20) != 0) {
          if ((*(int *)(tmp_i1 + 0x20) != 10) ||
             (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
            tmp_i3 = tmp_i3 + 1;
          }
          if ((*(int *)(tmp_i1 + 0x24) != 0) &&
             ((*(int *)(tmp_i1 + 0x24) != 10 ||
              (tmp_i1 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i1 == 0)))) {
            tmp_i3 = tmp_i3 + 1;
          }
        }
      }
    }
  }
  return tmp_i3;
}

void CG_LimboPanel_WeaponIsDisabled(void)
{
  BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
  CG_LimboPanel_RealWeaponIsDisabled();
  return;
}

uint32_t CG_LimboPanel_GetSelectedWeaponNum(void)
{
  int tmp_i1;
  int tmp_i2;
  
  if (GHIDRA_FIELD(cgs, 33685912, 4) == 0) {
    return GHIDRA_FIELD(cgs, 33685924, 4);
  }
  tmp_i2 = GHIDRA_FIELD(cgs, 33685920, 4) + 4;
  tmp_i1 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
  tmp_i1 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i1 + tmp_i2 * 4));
  if (tmp_i1 != 0) {
    GHIDRA_FIELD(cgs, 33685920, 4) = 0;
    return 0;
  }
  return GHIDRA_FIELD(cgs, 33685920, 4);
}

int CG_LimboPanel_GetWeaponForNumber(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  
  if (((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) ||
     (tmp_i1 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4)), tmp_i1 == 0)) {
LAB_00088700:
    tmp_i1 = 0;
  }
  else {
    if (param_2 == 1) {
      if (param_3 == 0) {
        tmp_i2 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
        tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i2 + (param_1 + 4) * 4));
        if (tmp_i2 != 0) {
          if (param_1 != 0) {
            return *(int *)(tmp_i1 + 0x10);
          }
          if (GHIDRA_FIELD(cgs, 33685916, 4) == 0) goto LAB_000887f0;
        }
      }
      return *(int *)(tmp_i1 + (param_1 + 4) * 4);
    }
    if (((cgs[g_unk_01047ac4 * 0x1a4 + 0x95a0] & 0x10) == 0) || (GHIDRA_FIELD(cgs, 33685916, 4) != 0)) {
      if ((0 < param_1) && ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) != 0)) {
        if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
          return ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x2c;
        }
LAB_000886db:
        return ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x22;
      }
      if (param_1 != 0) goto LAB_00088700;
      if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
        if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) {
          return 0xe;
        }
        return 0x26;
      }
    }
    else {
      if ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) == 0) {
        if (param_1 == 1) goto LAB_000887f0;
      }
      else {
        if (param_1 == 2) {
LAB_000887f0:
          if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) {
            return 8;
          }
          return 3;
        }
        if (0 < param_1) goto LAB_000886db;
      }
      if (param_1 != 0) goto LAB_00088700;
    }
    tmp_i1 = (uint)((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) * 5 + 2;
  }
  return tmp_i1;
}

int CG_LimboPanel_WeaponCount(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (GHIDRA_FIELD(cgs, 33685912, 4) != 1) {
    if (((cgs[g_unk_01047ac4 * 0x1a4 + 0x95a0] & 0x10) != 0) && (GHIDRA_FIELD(cgs, 33685916, 4) == 0)) {
      return 3 - (uint)((*(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x959c) & 0x10) == 0);
    }
    return 2 - (uint)((*(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x959c) & 0x10) == 0);
  }
  tmp_i1 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
  if (*(int *)(tmp_i1 + 0x10) == 0) {
    return 0;
  }
  if (*(int *)(tmp_i1 + 0x10) == 10) {
    tmp_i3 = 0;
    tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10);
    if (tmp_i2 != 0) goto LAB_0008895a;
  }
  tmp_i3 = 1;
LAB_0008895a:
  if (*(int *)(tmp_i1 + 0x14) != 0) {
    if ((*(int *)(tmp_i1 + 0x14) != 10) ||
       (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
      tmp_i3 = tmp_i3 + 1;
    }
    if (*(int *)(tmp_i1 + 0x18) != 0) {
      if ((*(int *)(tmp_i1 + 0x18) != 10) ||
         (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
        tmp_i3 = tmp_i3 + 1;
      }
      if (*(int *)(tmp_i1 + 0x1c) != 0) {
        if ((*(int *)(tmp_i1 + 0x1c) != 10) ||
           (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
          tmp_i3 = tmp_i3 + 1;
        }
        if (*(int *)(tmp_i1 + 0x20) != 0) {
          if ((*(int *)(tmp_i1 + 0x20) != 10) ||
             (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
            tmp_i3 = tmp_i3 + 1;
          }
          if ((*(int *)(tmp_i1 + 0x24) != 0) &&
             ((*(int *)(tmp_i1 + 0x24) != 10 ||
              (tmp_i1 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i1 == 0)))) {
            tmp_i3 = tmp_i3 + 1;
          }
        }
      }
    }
  }
  return tmp_i3;
}

void CG_LimboPanel_SendSetupMsg(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  int tmp_i6;
  int tmp_i7;
  
  CG_HudPlacement(0);
  tmp_u3 = GHIDRA_FIELD(cgs, 33685920, 4);
  if (param_1 == 0) {
    tmp_i7 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
    if (tmp_i7 == 3) {
      return;
    }
    tmp_i1 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
    if (tmp_i1 == 3) {
      tmp_i6 = 0;
      tmp_i1 = 0;
      goto LAB_00088c1f;
    }
  }
  else {
    tmp_i1 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
    tmp_i7 = tmp_i1;
    if (tmp_i1 == 3) {
      if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3) {
        trap_SendClientCommand("team s 0 0 0\n");
      }
      CG_EventHandling(0,0);
      return;
    }
  }
  tmp_i1 = BG_GetPlayerClassInfo(tmp_i1,GHIDRA_FIELD(cgs, 33685916, 4));
  if (tmp_i1 == 0) {
    tmp_i6 = 0;
    tmp_i1 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
LAB_00088b50:
    tmp_u3 = GHIDRA_FIELD(cgs, 33685916, 4);
    if (tmp_i1 != 3) goto LAB_00088b69;
  }
  else {
    tmp_i2 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
    tmp_i6 = tmp_u3 + 4;
    tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i2 + tmp_i6 * 4));
    if (tmp_i2 == 0) {
LAB_00088d60:
      tmp_i6 = *(int *)(tmp_i1 + tmp_i6 * 4);
      tmp_i1 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
      goto LAB_00088b50;
    }
    if (tmp_u3 != 0) {
      tmp_i6 = *(int *)(tmp_i1 + 0x10);
      tmp_i1 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
      goto LAB_00088b50;
    }
    if (GHIDRA_FIELD(cgs, 33685916, 4) != 0) goto LAB_00088d60;
    tmp_i1 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
    if (tmp_i1 != 1) {
      tmp_i6 = 8;
      goto LAB_00088b50;
    }
    tmp_i6 = 3;
    tmp_u3 = 0;
LAB_00088b69:
    tmp_u4 = GHIDRA_FIELD(cgs, 33685924, 4);
    tmp_i1 = BG_GetPlayerClassInfo(tmp_i1,tmp_u3);
    if (tmp_i1 != 0) {
      if (((cgs[g_unk_01047ac4 * 0x1a4 + 0x95a0] & 0x10) == 0) || (GHIDRA_FIELD(cgs, 33685916, 4) != 0)) {
        if ((0 < (int)tmp_u4) && ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) != 0)) {
          if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
            tmp_i1 = ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x2c;
            goto LAB_00088c1f;
          }
LAB_00088d9d:
          tmp_i1 = ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x22;
          goto LAB_00088c1f;
        }
        tmp_i1 = 0;
        if (tmp_u4 != 0) goto LAB_00088c1f;
        if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
          tmp_i1 = 0x26;
          if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) {
            tmp_i1 = 0xe;
          }
          goto LAB_00088c1f;
        }
      }
      else {
        if ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) == 0) {
          if (tmp_u4 == 1) goto LAB_00088ed0;
        }
        else {
          if (tmp_u4 == 2) {
LAB_00088ed0:
            tmp_i1 = (uint)((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) * 5 + 3;
            goto LAB_00088c1f;
          }
          if (0 < (int)tmp_u4) goto LAB_00088d9d;
        }
        if (tmp_u4 != 0) goto LAB_00088e6b;
      }
      tmp_i1 = (uint)((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) * 5 + 2;
      goto LAB_00088c1f;
    }
  }
LAB_00088e6b:
  tmp_i1 = 0;
LAB_00088c1f:
  if (tmp_i7 == 1) {
    tmp_pc5 = "r";
  }
  else {
    if (tmp_i7 != 2) {
      return;
    }
    tmp_pc5 = "b";
  }
  tmp_u3 = va("team %s %i %i %i\n",tmp_pc5,GHIDRA_FIELD(cgs, 33685916, 4),tmp_i6,tmp_i1);
  trap_SendClientCommand(tmp_u3);
  if (param_1 != 0) {
    CG_EventHandling(0,0);
  }
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) {
    tmp_pc5 = "Axis";
  }
  else if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 2) {
    tmp_pc5 = "Allied";
  }
  else {
    tmp_pc5 = "unknown";
  }
  tmp_u3 = *(uint32_t *)(ammoTableMP + tmp_i6 * 0x48 + 0x40);
  tmp_u4 = BG_ClassnameForNumber(GHIDRA_FIELD(cgs, 33685916, 4));
  tmp_u3 = va("You will spawn as an %s %s with a %s.",tmp_pc5,tmp_u4,tmp_u3,tmp_i1);
  CG_CenterPrint(tmp_u3,0x188,8);
  GHIDRA_FIELD(cgs, 33701712, 4) = 1;
  GHIDRA_FIELD(cgs, 33701708, 4) = 1;
  return;
}

uint32_t CG_LimboPanel_OkButton_KeyDown(uint32_t param_1,int param_2)
{
  if (param_2 != 0xb2) {
    return 0;
  }
  trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69628, 4),6);
  CG_LimboPanel_SendSetupMsg(1);
  return 1;
}

int CG_LimboPanel_GetSelectedWeaponForSlot(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i2 = GHIDRA_FIELD(cgs, 33685924, 4);
  if (param_1 == 1) {
    tmp_i2 = GHIDRA_FIELD(cgs, 33685920, 4);
  }
  if (((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) ||
     (tmp_i1 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4)), tmp_i1 == 0)) {
LAB_00089050:
    tmp_i2 = 0;
  }
  else {
    if (param_1 == 1) {
      tmp_i3 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
      tmp_i3 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i3 + (tmp_i2 + 4) * 4));
      if (tmp_i3 != 0) {
        if (tmp_i2 != 0) {
          return *(int *)(tmp_i1 + 0x10);
        }
        if (GHIDRA_FIELD(cgs, 33685916, 4) == 0) goto LAB_000890c4;
      }
      return *(int *)(tmp_i1 + (tmp_i2 + 4) * 4);
    }
    if (((cgs[g_unk_01047ac4 * 0x1a4 + 0x95a0] & 0x10) == 0) || (GHIDRA_FIELD(cgs, 33685916, 4) != 0)) {
      if ((0 < tmp_i2) && ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) != 0)) {
        if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
          return ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x2c;
        }
LAB_00089028:
        return ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x22;
      }
      if (tmp_i2 != 0) goto LAB_00089050;
      if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
        if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) {
          return 0xe;
        }
        return 0x26;
      }
    }
    else {
      if ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) == 0) {
        if (tmp_i2 == 1) goto LAB_000890c4;
      }
      else {
        if (tmp_i2 == 2) {
LAB_000890c4:
          if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) {
            return 8;
          }
          return 3;
        }
        if (0 < tmp_i2) goto LAB_00089028;
      }
      if (tmp_i2 != 0) goto LAB_00089050;
    }
    tmp_i2 = (uint)((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) * 5 + 2;
  }
  return tmp_i2;
}

int CG_LimboPanel_GetSelectedWeapon(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_u1 = GHIDRA_FIELD(cgs, 33685912, 4);
  tmp_i3 = GHIDRA_FIELD(cgs, 33685924, 4);
  if (GHIDRA_FIELD(cgs, 33685912, 4) != 0) {
    tmp_i2 = GHIDRA_FIELD(cgs, 33685920, 4) + 4;
    tmp_i3 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
    tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i3 + tmp_i2 * 4));
    tmp_i3 = GHIDRA_FIELD(cgs, 33685920, 4);
    if (tmp_i2 != 0) {
      GHIDRA_FIELD(cgs, 33685920, 4) = 0;
      tmp_i3 = 0;
    }
  }
  if (((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) ||
     (tmp_i2 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4)), tmp_i2 == 0)) {
LAB_000892a0:
    tmp_i3 = 0;
  }
  else {
    if (tmp_u1 == 1) {
      tmp_i4 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
      tmp_i4 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i4 + (tmp_i3 + 4) * 4));
      if (tmp_i4 != 0) {
        if (tmp_i3 != 0) {
          return *(int *)(tmp_i2 + 0x10);
        }
        if (GHIDRA_FIELD(cgs, 33685916, 4) == 0) goto LAB_00089373;
      }
      return *(int *)(tmp_i2 + (tmp_i3 + 4) * 4);
    }
    if (((cgs[g_unk_01047ac4 * 0x1a4 + 0x95a0] & 0x10) == 0) || (GHIDRA_FIELD(cgs, 33685916, 4) != 0)) {
      if ((0 < tmp_i3) && ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) != 0)) {
        if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
          return ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x2c;
        }
LAB_0008927d:
        return ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x22;
      }
      if (tmp_i3 != 0) goto LAB_000892a0;
      if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
        if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) {
          return 0xe;
        }
        return 0x26;
      }
    }
    else {
      if ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) == 0) {
        if (tmp_i3 == 1) goto LAB_00089373;
      }
      else {
        if (tmp_i3 == 2) {
LAB_00089373:
          if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) {
            return 8;
          }
          return 3;
        }
        if (0 < tmp_i3) goto LAB_0008927d;
      }
      if (tmp_i3 != 0) goto LAB_000892a0;
    }
    tmp_i3 = (uint)((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) * 5 + 2;
  }
  return tmp_i3;
}

uint32_t CG_LimboPanel_WeaponLights_KeyDown(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  
  if ((param_2 == 0xb2) && ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3)) {
    trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69628, 4),6);
    tmp_i2 = *(int *)(param_1 + 0x18);
    tmp_u1 = GHIDRA_FIELD(cgs, 33685924, 4);
    GHIDRA_FIELD(cgs, 33685912, 4) = tmp_i2;
    if (tmp_i2 != 0) {
      tmp_i4 = GHIDRA_FIELD(cgs, 33685920, 4) + 4;
      tmp_i3 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
      tmp_i3 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i3 + tmp_i4 * 4));
      tmp_u1 = GHIDRA_FIELD(cgs, 33685920, 4);
      if (tmp_i3 != 0) {
        GHIDRA_FIELD(cgs, 33685920, 4) = 0;
        tmp_u1 = 0;
      }
    }
    tmp_u5 = 1;
    tmp_u1 = CG_LimboPanel_GetWeaponForNumber(tmp_u1,tmp_i2,0);
    tmp_i2 = BG_WeapStatForWeapon(tmp_u1);
    if (tmp_i2 != 0x1a) {
      tmp_u1 = va("ws %i",tmp_i2);
      trap_SendClientCommand(tmp_u1);
    }
  }
  else {
    tmp_u5 = 0;
  }
  return tmp_u5;
}

uint32_t CG_LimboPanel_TeamButton_KeyDown(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  int tmp_i5;
  long tmp_l6;
  
  tmp_u1 = 0;
  if (param_2 == 0xb2) {
    trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69628, 4),6);
    tmp_i5 = *(int *)(param_1 + 0x18);
    if (GHIDRA_FIELD(cgs, 33685908, 4) == tmp_i5) {
      tmp_u1 = 1;
    }
    else {
      tmp_i2 = 0;
      if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3) {
        tmp_u1 = CG_ConfigString(0xd);
        tmp_pc3 = (char *)Info_ValueForKey(tmp_u1,&g_unk_00120a20);
        tmp_i2 = strtol(tmp_pc3,(char **)0x0,10);
        tmp_i5 = *(int *)(param_1 + 0x18);
      }
      tmp_l6 = GHIDRA_FIELD(cgs, 33685904, 4);
      GHIDRA_FIELD(cgs, 33685908, 4) = tmp_i5;
      if ((GHIDRA_FIELD(cgs, 33685904, 4) == tmp_i2) && (tmp_l6 = 0, (&teamOrder)[tmp_i5] != 3)) {
        tmp_u1 = CG_ConfigString(0xd);
        tmp_pc3 = (char *)Info_ValueForKey(tmp_u1,&g_unk_00120a20);
        tmp_l6 = strtol(tmp_pc3,(char **)0x0,10);
      }
      GHIDRA_FIELD(cgs, 33685904, 4) = tmp_l6;
      tmp_u1 = GHIDRA_FIELD(cgs, 33685912, 4);
      GHIDRA_FIELD(cgs, 33685920, 4) = 0;
      tmp_u4 = GHIDRA_FIELD(cgs, 33685924, 4);
      if (GHIDRA_FIELD(cgs, 33685912, 4) != 0) {
        tmp_i5 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
        tmp_i5 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i5 + 0x10));
        tmp_u4 = GHIDRA_FIELD(cgs, 33685920, 4);
        if (tmp_i5 != 0) {
          GHIDRA_FIELD(cgs, 33685920, 4) = 0;
          tmp_u4 = 0;
        }
      }
      tmp_u1 = CG_LimboPanel_GetWeaponForNumber(tmp_u4,tmp_u1,0);
      tmp_i5 = BG_WeapStatForWeapon(tmp_u1);
      if (tmp_i5 != 0x1a) {
        tmp_u1 = va("ws %i",tmp_i5);
        trap_SendClientCommand(tmp_u1);
      }
      GHIDRA_FIELD(cgs, 33701712, 4) = 1;
      tmp_u1 = 1;
    }
  }
  return tmp_u1;
}

void CG_LimboPanel_GetSelectedWeaponStat(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_u1 = GHIDRA_FIELD(cgs, 33685912, 4);
  tmp_i3 = GHIDRA_FIELD(cgs, 33685924, 4);
  if (GHIDRA_FIELD(cgs, 33685912, 4) != 0) {
    tmp_i2 = GHIDRA_FIELD(cgs, 33685920, 4) + 4;
    tmp_i3 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
    tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i3 + tmp_i2 * 4));
    tmp_i3 = GHIDRA_FIELD(cgs, 33685920, 4);
    if (tmp_i2 != 0) {
      GHIDRA_FIELD(cgs, 33685920, 4) = 0;
      tmp_i3 = 0;
    }
  }
  if (((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) ||
     (tmp_i2 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4)), tmp_i2 == 0)) {
LAB_00089880:
    tmp_i3 = 0;
  }
  else {
    if (tmp_u1 == 1) {
      tmp_i4 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
      tmp_i4 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i4 + (tmp_i3 + 4) * 4));
      if (tmp_i4 != 0) {
        if (tmp_i3 != 0) {
          tmp_i3 = *(int *)(tmp_i2 + 0x10);
          goto LAB_00089882;
        }
        if (GHIDRA_FIELD(cgs, 33685916, 4) == 0) goto LAB_00089953;
      }
      tmp_i3 = *(int *)(tmp_i2 + (tmp_i3 + 4) * 4);
      goto LAB_00089882;
    }
    if (((cgs[g_unk_01047ac4 * 0x1a4 + 0x95a0] & 0x10) == 0) || (GHIDRA_FIELD(cgs, 33685916, 4) != 0)) {
      if ((0 < tmp_i3) && ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) != 0)) {
        if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
          tmp_i3 = ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x2c;
          goto LAB_00089882;
        }
LAB_0008985d:
        tmp_i3 = ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x22;
        goto LAB_00089882;
      }
      if (tmp_i3 != 0) goto LAB_00089880;
      if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
        tmp_i3 = 0xe;
        if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) {
          tmp_i3 = 0x26;
        }
        goto LAB_00089882;
      }
    }
    else {
      if ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) == 0) {
        if (tmp_i3 == 1) goto LAB_00089953;
      }
      else {
        if (tmp_i3 == 2) {
LAB_00089953:
          if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) {
            tmp_i3 = 3;
          }
          else {
            tmp_i3 = 8;
          }
          goto LAB_00089882;
        }
        if (0 < tmp_i3) goto LAB_0008985d;
      }
      if (tmp_i3 != 0) goto LAB_00089880;
    }
    tmp_i3 = (uint)((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) * 5 + 2;
  }
LAB_00089882:
  BG_WeapStatForWeapon(tmp_i3);
  return;
}

void CG_LimboPanel_RequestWeaponStats(void)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  
  tmp_u3 = GHIDRA_FIELD(cgs, 33685912, 4);
  tmp_i2 = GHIDRA_FIELD(cgs, 33685924, 4);
  if (GHIDRA_FIELD(cgs, 33685912, 4) != 0) {
    tmp_i1 = GHIDRA_FIELD(cgs, 33685920, 4) + 4;
    tmp_i2 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
    tmp_i1 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i2 + tmp_i1 * 4));
    tmp_i2 = GHIDRA_FIELD(cgs, 33685920, 4);
    if (tmp_i1 != 0) {
      GHIDRA_FIELD(cgs, 33685920, 4) = 0;
      tmp_i2 = 0;
    }
  }
  if (((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) ||
     (tmp_i1 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4)), tmp_i1 == 0)) {
LAB_00089b30:
    tmp_i2 = 0;
  }
  else {
    if (tmp_u3 == 1) {
      tmp_i4 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
      tmp_i4 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i4 + (tmp_i2 + 4) * 4));
      if (tmp_i4 != 0) {
        if (tmp_i2 != 0) {
          tmp_i2 = *(int *)(tmp_i1 + 0x10);
          goto LAB_00089b32;
        }
        if (GHIDRA_FIELD(cgs, 33685916, 4) == 0) goto LAB_00089c23;
      }
      tmp_i2 = *(int *)(tmp_i1 + (tmp_i2 + 4) * 4);
      goto LAB_00089b32;
    }
    if (((cgs[g_unk_01047ac4 * 0x1a4 + 0x95a0] & 0x10) == 0) || (GHIDRA_FIELD(cgs, 33685916, 4) != 0)) {
      if ((0 < tmp_i2) && ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) != 0)) {
        if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
          tmp_i2 = ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x2c;
          goto LAB_00089b32;
        }
LAB_00089b0d:
        tmp_i2 = ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x22;
        goto LAB_00089b32;
      }
      if (tmp_i2 != 0) goto LAB_00089b30;
      if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
        tmp_i2 = 0xe;
        if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) {
          tmp_i2 = 0x26;
        }
        goto LAB_00089b32;
      }
    }
    else {
      if ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) == 0) {
        if (tmp_i2 == 1) goto LAB_00089c23;
      }
      else {
        if (tmp_i2 == 2) {
LAB_00089c23:
          if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) {
            tmp_i2 = 3;
          }
          else {
            tmp_i2 = 8;
          }
          goto LAB_00089b32;
        }
        if (0 < tmp_i2) goto LAB_00089b0d;
      }
      if (tmp_i2 != 0) goto LAB_00089b30;
    }
    tmp_i2 = (uint)((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) * 5 + 2;
  }
LAB_00089b32:
  tmp_i2 = BG_WeapStatForWeapon(tmp_i2);
  if (tmp_i2 != 0x1a) {
    tmp_u3 = va("ws %i",tmp_i2);
    trap_SendClientCommand(tmp_u3);
  }
  return;
}

uint32_t CG_LimboPanel_ClassButton_KeyDown(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t local_10;
  
  if ((param_2 == 0xb2) && ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3)) {
    trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69628, 4),6);
    tmp_i1 = *(int *)(param_1 + 0x1c);
    if (GHIDRA_FIELD(cgs, 33685916, 4) == tmp_i1) {
      local_10 = 1;
    }
    else {
      tmp_i2 = CG_LimboPanel_ClassIsDisabled(tmp_i1);
      local_10 = 1;
      if (tmp_i2 == 0) {
        local_10 = 1;
        GHIDRA_FIELD(cgs, 33685920, 4) = 0;
        GHIDRA_FIELD(cgs, 33685916, 4) = tmp_i1;
        CG_LimboPanel_RequestWeaponStats();
      }
    }
  }
  else {
    local_10 = 0;
  }
  return local_10;
}

void CG_LimboPanel_Setup(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  long tmp_l4;
  int tmp_i5;
  int tmp_i6;
  uint tmp_u7;
  uint8_t **tmp_ppu8;
  uint8_t *tmp_pu9;
  uint8_t local_11c [264];
  uint32_t uStack_14;
  
  tmp_i5 = g_unk_01047ac4;
  uStack_14 = 0x89de9;
  GHIDRA_FIELD(cgs, 33701712, 4) = 0;
  trap_Cvar_VariableStringBuffer("name",local_11c,0x100);
  trap_Cvar_Set("limboname",local_11c);
  if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
    GHIDRA_FIELD(cgs, 33685900, 4) = CG_CurLayerForZ((int)ROUND(g_unk_01091444));
  }
  if (limboPanelButtons != (uint8_t *)0x0) {
    tmp_ppu8 = &limboPanelButtons;
    tmp_pu9 = limboPanelButtons;
    do {
      while ((*(void **)(tmp_pu9 + 0x44) != CG_LimboPanel_RenderCounter ||
             ((*(int *)(tmp_pu9 + 0x18) != 3 && (*(int *)(tmp_pu9 + 0x18) != 5))))) {
        tmp_ppu8 = tmp_ppu8 + 1;
        tmp_pu9 = *tmp_ppu8;
        if (tmp_pu9 == (uint8_t *)0x0) goto LAB_00089ec0;
      }
      tmp_ppu8 = tmp_ppu8 + 1;
      tmp_u2 = CG_LimboPanel_RenderCounter_ValueForButton(tmp_pu9);
      *(uint32_t *)(tmp_pu9 + 0x28) = 0;
      *(uint32_t *)(tmp_pu9 + 0x2c) = tmp_u2;
      *(uint32_t *)(tmp_pu9 + 0x24) = tmp_u2;
      tmp_pu9 = *tmp_ppu8;
    } while (tmp_pu9 != (uint8_t *)0x0);
  }
LAB_00089ec0:
  if (GHIDRA_FIELD(cgs, 33701708, 4) == 0) {
    tmp_i6 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
    if (*(int *)(tmp_i6 + 0x10) == 0) {
LAB_0008a280:
      GHIDRA_FIELD(cgs, 33685920, 4) = 0;
    }
    else {
      tmp_i1 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9568);
      if (*(int *)(tmp_i6 + 0x10) == tmp_i1) {
        GHIDRA_FIELD(cgs, 33685920, 4) = 0;
      }
      else {
        if (*(int *)(tmp_i6 + 0x14) == 0) goto LAB_0008a280;
        if (*(int *)(tmp_i6 + 0x14) == tmp_i1) {
          GHIDRA_FIELD(cgs, 33685920, 4) = 1;
        }
        else {
          if (*(int *)(tmp_i6 + 0x18) == 0) goto LAB_0008a280;
          if (tmp_i1 == *(int *)(tmp_i6 + 0x18)) {
            GHIDRA_FIELD(cgs, 33685920, 4) = 2;
          }
          else {
            if (*(int *)(tmp_i6 + 0x1c) == 0) goto LAB_0008a280;
            if (tmp_i1 == *(int *)(tmp_i6 + 0x1c)) {
              GHIDRA_FIELD(cgs, 33685920, 4) = 3;
            }
            else {
              if (*(int *)(tmp_i6 + 0x20) == 0) goto LAB_0008a280;
              if (tmp_i1 == *(int *)(tmp_i6 + 0x20)) {
                GHIDRA_FIELD(cgs, 33685920, 4) = 4;
              }
              else {
                if (*(int *)(tmp_i6 + 0x24) == 0) goto LAB_0008a280;
                if (*(int *)(tmp_i6 + 0x24) == tmp_i1) {
                  GHIDRA_FIELD(cgs, 33685920, 4) = 5;
                }
              }
            }
          }
        }
      }
    }
    GHIDRA_FIELD(cgs, 33685924, 4) = GHIDRA_FIELD(cg_limbo_secondary, 12, 4);
    if (((*(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95a0) & 0x10) == 0) || (GHIDRA_FIELD(cgs, 33685916, 4) != 0)) {
      tmp_u7 = *(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x959c) & 0x10;
      if ((int)(2 - (uint)(tmp_u7 == 0)) <= (int)GHIDRA_FIELD(cg_limbo_secondary, 12, 4)) {
        if (((*(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95a0) & 0x10) != 0) &&
           (GHIDRA_FIELD(cgs, 33685916, 4) == 0)) goto LAB_0008a20e;
        GHIDRA_FIELD(cgs, 33685924, 4) = ZEXT14(tmp_u7 != 0);
      }
    }
    else {
      tmp_u7 = *(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x959c) & 0x10;
      if ((int)(3 - (uint)(tmp_u7 == 0)) <= (int)GHIDRA_FIELD(cg_limbo_secondary, 12, 4)) {
LAB_0008a20e:
        GHIDRA_FIELD(cgs, 33685924, 4) = 2 - (uint)(tmp_u7 == 0);
      }
    }
    tmp_i6 = *(int *)(cgs + tmp_i5 * 0x1a4 + 0x9494);
    if (teamOrder == tmp_i6) {
      GHIDRA_FIELD(cgs, 33685908, 4) = 0;
    }
    if (g_unk_00145144 == tmp_i6) {
      GHIDRA_FIELD(cgs, 33685908, 4) = 1;
    }
    if (g_unk_00145148 == tmp_i6) {
      GHIDRA_FIELD(cgs, 33685908, 4) = 2;
    }
    if (tmp_i6 != 3) {
      GHIDRA_FIELD(cgs, 33685916, 4) = *(uint32_t *)(cgs + tmp_i5 * 0x1a4 + 0x94b8);
    }
  }
  CG_LimboPanel_RequestWeaponStats();
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) {
    GHIDRA_FIELD(cgs, 33685904, 4) = 0;
    GHIDRA_FIELD(cgs, 33685972, 4) = 0;
  }
  else {
    tmp_u2 = CG_ConfigString(0xd);
    tmp_pc3 = (char *)Info_ValueForKey(tmp_u2,&g_unk_00120a20);
    GHIDRA_FIELD(cgs, 33685904, 4) = strtol(tmp_pc3,(char **)0x0,10);
    GHIDRA_FIELD(cgs, 33685972, 4) = GHIDRA_FIELD(cgs, 33685904, 4);
    if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3) {
      tmp_u2 = CG_ConfigString(0xd);
      tmp_pc3 = (char *)Info_ValueForKey(tmp_u2,&g_unk_00120a20);
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      if ((GHIDRA_FIELD(cgs, 33685904, 4) != tmp_l4) &&
         (tmp_u2 = GHIDRA_FIELD(cgs, 33685904, 4), (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 3)) goto LAB_00089f8a;
    }
  }
  tmp_u2 = 0xffffffff;
LAB_00089f8a:
  tmp_u2 = va("obj %i",tmp_u2);
  trap_SendClientCommand(tmp_u2);
  GHIDRA_FIELD(cgs, 33685972, 4) = GHIDRA_FIELD(cgs, 33685904, 4);
  GHIDRA_FIELD(cgs, 33685976, 4) = g_unk_010906e0;
  tmp_i5 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
  tmp_l4 = 0;
  if (tmp_i5 != 3) {
    tmp_u2 = CG_ConfigString(0xd);
    tmp_pc3 = (char *)Info_ValueForKey(tmp_u2,&g_unk_00120a20);
    tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_i5 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
  }
  tmp_u2 = GHIDRA_FIELD(cgs, 33685920, 4);
  GHIDRA_FIELD(cgs, 33685912, 4) = 1;
  GHIDRA_FIELD(cgs, 33685904, 4) = tmp_l4;
  tmp_i5 = BG_GetPlayerClassInfo(tmp_i5,GHIDRA_FIELD(cgs, 33685916, 4));
  tmp_i5 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i5 + (tmp_u2 + 4) * 4));
  if (tmp_i5 != 0) {
    GHIDRA_FIELD(cgs, 33685920, 4) = 0;
  }
  return;
}

void CG_LimboPanel_SetSelectedWeaponNum(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  
  if (GHIDRA_FIELD(cgs, 33685912, 4) == 1) {
    tmp_i2 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
    tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i2 + (param_1 + 4) * 4));
    if (tmp_i2 == 0) {
      GHIDRA_FIELD(cgs, 33685920, 4) = param_1;
    }
  }
  else {
    GHIDRA_FIELD(cgs, 33685924, 4) = param_1;
  }
  tmp_u3 = GHIDRA_FIELD(cgs, 33685912, 4);
  tmp_i2 = GHIDRA_FIELD(cgs, 33685924, 4);
  if (GHIDRA_FIELD(cgs, 33685912, 4) != 0) {
    tmp_i1 = GHIDRA_FIELD(cgs, 33685920, 4) + 4;
    tmp_i2 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
    tmp_i1 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i2 + tmp_i1 * 4));
    tmp_i2 = GHIDRA_FIELD(cgs, 33685920, 4);
    if (tmp_i1 != 0) {
      GHIDRA_FIELD(cgs, 33685920, 4) = 0;
      tmp_i2 = 0;
    }
  }
  if (((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) ||
     (tmp_i1 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4)), tmp_i1 == 0)) {
LAB_0008a3a0:
    tmp_i2 = 0;
  }
  else {
    if (tmp_u3 == 1) {
      tmp_i4 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
      tmp_i4 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i4 + (tmp_i2 + 4) * 4));
      if (tmp_i4 == 0) {
LAB_0008a510:
        tmp_i2 = *(int *)(tmp_i1 + (tmp_i2 + 4) * 4);
        goto LAB_0008a3a2;
      }
      if (tmp_i2 != 0) {
        tmp_i2 = *(int *)(tmp_i1 + 0x10);
        goto LAB_0008a3a2;
      }
      if (GHIDRA_FIELD(cgs, 33685916, 4) != 0) goto LAB_0008a510;
      tmp_i2 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
joined_r0x0008a4a1:
      if (tmp_i2 == 1) {
        tmp_i2 = 3;
      }
      else {
        tmp_i2 = 8;
      }
      goto LAB_0008a3a2;
    }
    if (((cgs[g_unk_01047ac4 * 0x1a4 + 0x95a0] & 0x10) == 0) || (GHIDRA_FIELD(cgs, 33685916, 4) != 0)) {
      if ((0 < tmp_i2) && ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) != 0)) {
        if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
          tmp_i2 = ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x2c;
          goto LAB_0008a3a2;
        }
LAB_0008a380:
        tmp_i2 = ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 1) + 0x22;
        goto LAB_0008a3a2;
      }
      if (tmp_i2 != 0) goto LAB_0008a3a0;
      if (GHIDRA_FIELD(cgs, 33685916, 4) == 4) {
        tmp_i2 = 0xe;
        if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) {
          tmp_i2 = 0x26;
        }
        goto LAB_0008a3a2;
      }
    }
    else {
      if ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) == 0) {
        if (tmp_i2 == 1) goto LAB_0008a575;
      }
      else {
        if (tmp_i2 == 2) {
LAB_0008a575:
          tmp_i2 = (&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)];
          goto joined_r0x0008a4a1;
        }
        if (0 < tmp_i2) goto LAB_0008a380;
      }
      if (tmp_i2 != 0) goto LAB_0008a3a0;
    }
    tmp_i2 = (uint)((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] != 1) * 5 + 2;
  }
LAB_0008a3a2:
  tmp_i2 = BG_WeapStatForWeapon(tmp_i2);
  if (tmp_i2 != 0x1a) {
    tmp_u3 = va("ws %i",tmp_i2);
    trap_SendClientCommand(tmp_u3);
  }
  return;
}

void CG_LimboPanel_WeaponPanel(int param_1)
{
  bool tmp_b1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  int tmp_i7;
  int tmp_i8;
  int local_58;
  uint local_50;
  int local_48;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  float local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  tmp_u6 = GHIDRA_FIELD(cgs, 33685912, 4);
  uStack_14 = 0x8a5e9;
  tmp_u5 = GHIDRA_FIELD(cgs, 33685924, 4);
  if (GHIDRA_FIELD(cgs, 33685912, 4) != 0) {
    tmp_i4 = GHIDRA_FIELD(cgs, 33685920, 4) + 4;
    tmp_i2 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
    tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i2 + tmp_i4 * 4));
    tmp_u5 = GHIDRA_FIELD(cgs, 33685920, 4);
    if (tmp_i2 != 0) {
      GHIDRA_FIELD(cgs, 33685920, 4) = 0;
      tmp_u5 = 0;
    }
  }
  tmp_i2 = CG_LimboPanel_GetWeaponForNumber(tmp_u5,tmp_u6,0);
  if (GHIDRA_FIELD(cgs, 33685912, 4) == 1) {
    tmp_i4 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
    if (*(int *)(tmp_i4 + 0x10) == 0) {
      local_58 = 0;
    }
    else {
      if (*(int *)(tmp_i4 + 0x10) == 10) {
        local_58 = 0;
        tmp_i7 = CG_LimboPanel_RealWeaponIsDisabled(10);
        if (tmp_i7 == 0) goto LAB_0008ad15;
      }
      else {
LAB_0008ad15:
        local_58 = 1;
      }
      if (*(int *)(tmp_i4 + 0x14) != 0) {
        if ((*(int *)(tmp_i4 + 0x14) != 10) ||
           (tmp_i7 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i7 == 0)) {
          local_58 = local_58 + 1;
        }
        if (*(int *)(tmp_i4 + 0x18) != 0) {
          if ((*(int *)(tmp_i4 + 0x18) != 10) ||
             (tmp_i7 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i7 == 0)) {
            local_58 = local_58 + 1;
          }
          if (*(int *)(tmp_i4 + 0x1c) != 0) {
            if ((*(int *)(tmp_i4 + 0x1c) != 10) ||
               (tmp_i7 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i7 == 0)) {
              local_58 = local_58 + 1;
            }
            if (*(int *)(tmp_i4 + 0x20) != 0) {
              if ((*(int *)(tmp_i4 + 0x20) != 10) ||
                 (tmp_i7 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i7 == 0)) {
                local_58 = local_58 + 1;
              }
              if ((*(int *)(tmp_i4 + 0x24) != 0) &&
                 ((*(int *)(tmp_i4 + 0x24) != 10 ||
                  (tmp_i4 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i4 == 0)))) {
                local_58 = local_58 + 1;
              }
            }
          }
        }
      }
    }
    tmp_i4 = g_unk_01047ac4 * 0x1a4;
    local_50 = *(uint *)(cgs + tmp_i4 + 0x95a0) & 0x10;
    if (local_50 == 0) {
      tmp_u3 = *(uint *)(cgs + tmp_i4 + 0x959c) & 0x10;
    }
    else {
      tmp_u3 = *(uint *)(cgs + tmp_i4 + 0x959c) & 0x10;
      if (GHIDRA_FIELD(cgs, 33685916, 4) == 0) goto LAB_0008a687;
    }
    tmp_i4 = 2;
    if (tmp_u3 == 0) {
LAB_0008ab29:
      tmp_u3 = 0;
      tmp_i4 = 1;
    }
LAB_0008ab30:
    if (tmp_i4 <= (int)GHIDRA_FIELD(cgs, 33685924, 4)) {
      if ((local_50 == 0) || (GHIDRA_FIELD(cgs, 33685916, 4) != 0)) {
        GHIDRA_FIELD(cgs, 33685924, 4) = ZEXT14(tmp_u3 != 0);
      }
      else {
        GHIDRA_FIELD(cgs, 33685924, 4) = 2 - (uint)(tmp_u3 == 0);
      }
    }
  }
  else {
    tmp_u3 = *(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x959c);
    local_50 = *(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95a0) & 0x10;
    if (local_50 == 0) {
      if ((tmp_u3 & 0x10) == 0) {
        local_58 = 1;
        if (0 < (int)GHIDRA_FIELD(cgs, 33685924, 4)) {
          GHIDRA_FIELD(cgs, 33685924, 4) = 0;
        }
        goto LAB_0008a6d0;
      }
      local_58 = 2;
    }
    else {
      if (GHIDRA_FIELD(cgs, 33685916, 4) != 0) {
        tmp_u3 = tmp_u3 & 0x10;
        if (tmp_u3 == 0) {
          local_58 = 1;
          if (GHIDRA_FIELD(cgs, 33685916, 4) == 0) goto joined_r0x0008a6c9;
          goto LAB_0008ab29;
        }
        tmp_i4 = 2;
        local_58 = 2;
        goto LAB_0008ab30;
      }
      tmp_u3 = tmp_u3 & 0x10;
      local_58 = 3 - (uint)(tmp_u3 == 0);
LAB_0008a687:
      if (tmp_u3 != 0) {
        if (2 < (int)GHIDRA_FIELD(cgs, 33685924, 4)) {
          GHIDRA_FIELD(cgs, 33685924, 4) = 2;
        }
        goto LAB_0008a6d0;
      }
    }
joined_r0x0008a6c9:
    if (1 < (int)GHIDRA_FIELD(cgs, 33685924, 4)) {
      GHIDRA_FIELD(cgs, 33685924, 4) = 1;
    }
  }
LAB_0008a6d0:
  CG_HudPlacement(0);
  if ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3) {
    local_2c = 0;
    local_28 = 0.0;
    local_24 = 0;
    local_20 = 0.4;
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131560, 4));
    trap_R_SetColor(&local_2c);
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131684, 4));
    trap_R_SetColor(0);
    CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 4.0,*(float *)(param_1 + 0xc) + 12.0,
                      weaponPanelNameFont,g_unk_00147604,&g_unk_00147608,"SPECTATOR",0,0,g_unk_00147618,
                      g_unk_00147620);
    return;
  }
  tmp_i4 = BG_PanelButtons_GetFocusButton();
  if ((param_1 != tmp_i4) || (1 >= local_58)) {
    local_3c = 0;
    local_38 = 0;
    local_34 = 0;
    local_30 = 0x3ecccccd;
    local_2c = 0x3f800000;
    local_28 = 1.0;
    local_24 = 0x3f800000;
    local_20 = 0.4;
    tmp_u5 = CG_LimboPanel_RealWeaponIsDisabled(tmp_i2);
    tmp_u6 = GHIDRA_FIELD(cgs, 33685920, 4);
    if (GHIDRA_FIELD(cgs, 33685912, 4) == 0) {
      tmp_i4 = GHIDRA_FIELD(cgs, 33685924, 4) + 1;
    }
    else {
      tmp_i4 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
      tmp_i4 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i4 + (tmp_u6 + 4) * 4));
      if (tmp_i4 == 0) {
        tmp_i4 = GHIDRA_FIELD(cgs, 33685920, 4) + 1;
      }
      else {
        GHIDRA_FIELD(cgs, 33685920, 4) = 0;
        tmp_i4 = 1;
      }
    }
    tmp_u6 = va("%iof%i",tmp_i4,local_58);
    CG_LimboPanel_WeaponPanel_DrawWeapon(param_1 + 8,tmp_i2,1 < local_58,tmp_u6,tmp_u5);
    if ((local_58 < 2) || (tmp_i2 = BG_CursorInRect(param_1 + 8), tmp_i2 == 0)) {
      trap_R_SetColor(&local_2c);
    }
    CG_DrawPic((*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10)) - 20.0,
               *(float *)(param_1 + 0xc) + 4.0,0x41800000,0x41400000,GHIDRA_FIELD(cgs, 131708, 4));
    trap_R_SetColor(&local_3c);
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),GHIDRA_FIELD(cgs, 131684, 4));
    trap_R_SetColor(0);
    return;
  }
  local_2c = *(uint32_t *)(param_1 + 8);
  local_20 = *(float *)(param_1 + 0x14);
  local_28 = *(float *)(param_1 + 0xc);
  local_24 = *(uint32_t *)(param_1 + 0x10);
  tmp_u5 = CG_LimboPanel_RealWeaponIsDisabled(tmp_i2);
  tmp_u6 = GHIDRA_FIELD(cgs, 33685920, 4);
  if (GHIDRA_FIELD(cgs, 33685912, 4) == 0) {
    tmp_i4 = GHIDRA_FIELD(cgs, 33685924, 4) + 1;
  }
  else {
    tmp_i4 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
    tmp_i4 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i4 + (tmp_u6 + 4) * 4));
    if (tmp_i4 == 0) {
      tmp_i4 = GHIDRA_FIELD(cgs, 33685920, 4) + 1;
    }
    else {
      GHIDRA_FIELD(cgs, 33685920, 4) = 0;
      tmp_i4 = 1;
    }
  }
  tmp_u6 = va("%iof%i",tmp_i4,local_58);
  CG_LimboPanel_WeaponPanel_DrawWeapon(&local_2c,tmp_i2,1,tmp_u6,tmp_u5);
  tmp_i4 = BG_CursorInRect(&local_2c);
  if ((tmp_i4 != 0) && (*(int *)(param_1 + 0x34) != 0)) {
    *(uint32_t *)(param_1 + 0x34) = 0;
  }
  local_28 = local_28 - local_20;
  local_48 = 1;
  tmp_i4 = 1;
  do {
    while (((tmp_i7 = CG_LimboPanel_GetWeaponForNumber(tmp_i4 + -1,GHIDRA_FIELD(cgs, 33685912, 4),1), tmp_i7 != 10 ||
            (tmp_i8 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i8 == 0)) && (tmp_i7 != tmp_i2))) {
      tmp_u6 = CG_LimboPanel_RealWeaponIsDisabled(tmp_i7);
      tmp_u5 = va("%iof%i",tmp_i4,local_58);
      CG_LimboPanel_WeaponPanel_DrawWeapon(&local_2c,tmp_i7,1,tmp_u5,tmp_u6);
      tmp_i7 = BG_CursorInRect(&local_2c);
      if ((tmp_i7 != 0) && (*(int *)(param_1 + 0x34) != local_48)) {
        *(int *)(param_1 + 0x34) = local_48;
      }
      local_28 = local_28 - local_20;
      local_48 = local_48 + 1;
      tmp_b1 = local_58 <= tmp_i4;
      tmp_i4 = tmp_i4 + 1;
      if (tmp_b1) goto LAB_0008a8a3;
    }
    tmp_b1 = tmp_i4 < local_58;
    tmp_i4 = tmp_i4 + 1;
  } while (tmp_b1);
LAB_0008a8a3:
  CG_DrawBorder(*(uint32_t *)(param_1 + 8),
                *(float *)(param_1 + 0xc) - (float)(local_58 + -1) * *(float *)(param_1 + 0x14),
                *(uint32_t *)(param_1 + 0x10),(float)local_58 * *(float *)(param_1 + 0x14),0,0);
  return;
}

uint32_t CG_LimboPanel_WeaponPanel_KeyUp(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint local_3c;
  uint32_t local_2c;
  float local_28;
  uint32_t local_24;
  float local_20;
  
  if (((param_2 != 0xb2) || ((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)] == 3)) ||
     (tmp_i2 = BG_PanelButtons_GetFocusButton(), tmp_i2 != param_1)) {
    return 0;
  }
  local_2c = *(uint32_t *)(tmp_i2 + 8);
  local_24 = *(uint32_t *)(tmp_i2 + 0x10);
  local_20 = *(float *)(tmp_i2 + 0x14);
  local_28 = *(float *)(tmp_i2 + 0xc) - local_20;
  if (GHIDRA_FIELD(cgs, 33685912, 4) == 1) {
    tmp_i2 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
    if (*(int *)(tmp_i2 + 0x10) == 0) goto LAB_0008b250;
    if (*(int *)(tmp_i2 + 0x10) == 10) {
      local_3c = 0;
      tmp_i5 = CG_LimboPanel_RealWeaponIsDisabled(10);
      if (tmp_i5 == 0) goto LAB_0008b294;
    }
    else {
LAB_0008b294:
      local_3c = 1;
    }
    if (*(int *)(tmp_i2 + 0x14) != 0) {
      if ((*(int *)(tmp_i2 + 0x14) != 10) ||
         (tmp_i5 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i5 == 0)) {
        local_3c = local_3c + 1;
      }
      if (*(int *)(tmp_i2 + 0x18) != 0) {
        if ((*(int *)(tmp_i2 + 0x18) != 10) ||
           (tmp_i5 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i5 == 0)) {
          local_3c = local_3c + 1;
        }
        if (*(int *)(tmp_i2 + 0x1c) != 0) {
          if ((*(int *)(tmp_i2 + 0x1c) != 10) ||
             (tmp_i5 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i5 == 0)) {
            local_3c = local_3c + 1;
          }
          if (*(int *)(tmp_i2 + 0x20) != 0) {
            if ((*(int *)(tmp_i2 + 0x20) != 10) ||
               (tmp_i5 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i5 == 0)) {
              local_3c = local_3c + 1;
            }
            if ((*(int *)(tmp_i2 + 0x24) != 0) &&
               ((*(int *)(tmp_i2 + 0x24) != 10 ||
                (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)))) {
              local_3c = local_3c + 1;
            }
          }
        }
      }
    }
    if (local_3c < 2) goto LAB_0008b250;
  }
  else if (((cgs[g_unk_01047ac4 * 0x1a4 + 0x95a0] & 0x10) == 0) || (GHIDRA_FIELD(cgs, 33685916, 4) != 0)) {
    local_3c = 2;
    if ((cgs[g_unk_01047ac4 * 0x1a4 + 0x959c] & 0x10) == 0) goto LAB_0008b250;
  }
  else {
    local_3c = 3 - ((*(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x959c) & 0x10) == 0);
  }
  tmp_i5 = 1;
  tmp_i2 = 0;
  do {
    tmp_i3 = BG_CursorInRect(&local_2c);
    tmp_u1 = GHIDRA_FIELD(cgs, 33685920, 4);
    if (tmp_i3 != 0) {
      tmp_i3 = tmp_i2;
      if (GHIDRA_FIELD(cgs, 33685912, 4) == 0) {
        if (GHIDRA_FIELD(cgs, 33685924, 4) != 0) {
LAB_0008b07e:
          if (tmp_i5 <= (int)GHIDRA_FIELD(cgs, 33685924, 4)) goto LAB_0008b090;
        }
LAB_0008b1c0:
        tmp_i3 = tmp_i5;
      }
      else {
        tmp_i4 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
        tmp_i4 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i4 + (tmp_u1 + 4) * 4));
        tmp_u1 = GHIDRA_FIELD(cgs, 33685920, 4);
        if (tmp_i4 == 0) {
          if (GHIDRA_FIELD(cgs, 33685920, 4) != 0) {
            if (GHIDRA_FIELD(cgs, 33685912, 4) == 0) goto LAB_0008b07e;
            tmp_i4 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
            tmp_i4 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i4 + (tmp_u1 + 4) * 4));
            if (tmp_i4 != 0) goto LAB_0008b1d0;
            if (tmp_i5 <= (int)GHIDRA_FIELD(cgs, 33685920, 4)) {
              if (GHIDRA_FIELD(cgs, 33685912, 4) == 1) {
                tmp_i3 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
                tmp_i4 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i3 + (tmp_i2 + 4) * 4))
                ;
                tmp_i3 = GHIDRA_FIELD(cgs, 33685924, 4);
                if (tmp_i4 == 0) {
                  GHIDRA_FIELD(cgs, 33685920, 4) = tmp_i2;
                }
              }
              goto LAB_0008b090;
            }
          }
        }
        else {
LAB_0008b1d0:
          GHIDRA_FIELD(cgs, 33685920, 4) = 0;
        }
        if (GHIDRA_FIELD(cgs, 33685912, 4) != 1) goto LAB_0008b1c0;
        tmp_i3 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
        tmp_i4 = CG_LimboPanel_RealWeaponIsDisabled(*(uint32_t *)(tmp_i3 + (tmp_i5 + 4) * 4));
        tmp_i3 = GHIDRA_FIELD(cgs, 33685924, 4);
        if (tmp_i4 == 0) {
          GHIDRA_FIELD(cgs, 33685920, 4) = tmp_i5;
        }
      }
LAB_0008b090:
      GHIDRA_FIELD(cgs, 33685924, 4) = tmp_i3;
      CG_LimboPanel_RequestWeaponStats();
    }
    tmp_i5 = tmp_i5 + 1;
    tmp_i2 = tmp_i2 + 1;
    local_28 = local_28 - local_20;
  } while (tmp_i5 < (int)local_3c);
LAB_0008b250:
  BG_PanelButtons_SetFocusButton(0);
  return 1;
}

int CG_LimboPanel_GetWeaponNumberForPos(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int local_20;
  
  if (GHIDRA_FIELD(cgs, 33685912, 4) == 0) {
    return param_1;
  }
  if (param_1 < 0) {
    return 0;
  }
  if (GHIDRA_FIELD(cgs, 33685912, 4) != 1) {
    if (((cgs[g_unk_01047ac4 * 0x1a4 + 0x95a0] & 0x10) == 0) || (GHIDRA_FIELD(cgs, 33685916, 4) != 0)) {
      tmp_i1 = 2 - (uint)((*(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x959c) & 0x10) == 0);
    }
    else {
      tmp_i1 = 3 - (uint)((*(uint *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x959c) & 0x10) == 0);
    }
    goto LAB_0008b40e;
  }
  tmp_i3 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
  if (*(int *)(tmp_i3 + 0x10) == 0) {
    tmp_i1 = 0;
    goto LAB_0008b40e;
  }
  if (*(int *)(tmp_i3 + 0x10) == 10) {
    tmp_i1 = 0;
    tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10);
    if (tmp_i2 == 0) goto LAB_0008b4e0;
  }
  else {
LAB_0008b4e0:
    tmp_i1 = 1;
  }
  if (*(int *)(tmp_i3 + 0x14) != 0) {
    if ((*(int *)(tmp_i3 + 0x14) != 10) ||
       (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
      tmp_i1 = tmp_i1 + 1;
    }
    if (*(int *)(tmp_i3 + 0x18) != 0) {
      if ((*(int *)(tmp_i3 + 0x18) != 10) ||
         (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
        tmp_i1 = tmp_i1 + 1;
      }
      if (*(int *)(tmp_i3 + 0x1c) != 0) {
        if ((*(int *)(tmp_i3 + 0x1c) != 10) ||
           (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
          tmp_i1 = tmp_i1 + 1;
        }
        if (*(int *)(tmp_i3 + 0x20) != 0) {
          if ((*(int *)(tmp_i3 + 0x20) != 10) ||
             (tmp_i2 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i2 == 0)) {
            tmp_i1 = tmp_i1 + 1;
          }
          if ((*(int *)(tmp_i3 + 0x24) != 0) &&
             ((*(int *)(tmp_i3 + 0x24) != 10 ||
              (tmp_i3 = CG_LimboPanel_RealWeaponIsDisabled(10), tmp_i3 == 0)))) {
            tmp_i1 = tmp_i1 + 1;
          }
        }
      }
    }
  }
LAB_0008b40e:
  if (param_1 <= tmp_i1) {
    tmp_i3 = 0;
    local_20 = 0;
    do {
      while( true ) {
        tmp_i1 = BG_GetPlayerClassInfo((&teamOrder)[GHIDRA_FIELD(cgs, 33685908, 4)],GHIDRA_FIELD(cgs, 33685916, 4));
        tmp_i1 = CG_LimboPanel_RealWeaponIsDisabled
                          (*(uint32_t *)(tmp_i1 + (tmp_i3 + 4 + local_20) * 4));
        if (tmp_i1 == 0) break;
        tmp_i3 = tmp_i3 + 1;
      }
      local_20 = local_20 + 1;
    } while (local_20 <= param_1);
    return param_1 + tmp_i3;
  }
  return 0;
}

void CG_LoadPanel_RenderMissionDescriptionText(int param_1)
{
  uint32_t *tmp_pu1;
  float tmp_f2;
  int tmp_i3;
  char *tmp_pc4;
  char *tmp_pc5;
  char tmp_c6;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x8b5c9;
  if (GHIDRA_FIELD(cgs, 27388, 4) == 4) {
    tmp_i3 = (**(void **)(DC + 0xf8))();
    if (tmp_i3 == 0) {
      return;
    }
  }
  else if (GHIDRA_FIELD(cgs, 27388, 4) == 5) {
    tmp_i3 = 0x30f417c;
    if (GHIDRA_FIELD(cgs, 33571608, 4) == 0) {
      return;
    }
  }
  else {
    if (GHIDRA_FIELD(cgs, 33571608, 4) == 0) {
      return;
    }
    tmp_i3 = 0x30f457c;
  }
  Q_strncpyz(local_41c,tmp_i3,0x400);
  while (tmp_pc4 = strchr(local_41c,0x2a), tmp_pc4 != (char *)0x0) {
    *tmp_pc4 = '\n';
  }
  BG_FitTextToWidth_Ext
            (local_41c,**(uint32_t **)(param_1 + 0x38),*(float *)(param_1 + 0x10) - 16.0,0x400,
             (*(uint32_t **)(param_1 + 0x38))[8]);
  tmp_f2 = *(float *)(param_1 + 0xc) + 12.0;
  tmp_pc4 = local_41c;
  do {
    tmp_c6 = *tmp_pc4;
    tmp_pc5 = tmp_pc4;
    if (tmp_c6 == '\0') {
      return;
    }
    while (tmp_c6 != '\n') {
      tmp_pc5 = tmp_pc5 + 1;
      tmp_c6 = *tmp_pc5;
      if (tmp_c6 == '\0') {
        return;
      }
    }
    *tmp_pc5 = '\0';
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    (**(void **)(DC + 0x14))
              (*(float *)(param_1 + 8) + 4.0,tmp_f2,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_pc4,0,0,0,
               tmp_pu1[8]);
    tmp_f2 = tmp_f2 + 8.0;
    tmp_pc4 = tmp_pc5 + 1;
  } while( true );
}

void CG_LoadPanel_RenderCampaignNameText(int param_1)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  uint32_t tmp_u3;
  
  if (GHIDRA_FIELD(cgs, 27388, 4) == 4) {
    tmp_i2 = (**(void **)(DC + 0xfc))();
    if (tmp_i2 != 0) {
      tmp_u3 = va("%s",tmp_i2);
      tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
      CG_Text_Paint_Centred_Ext
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,tmp_pu1[1],
                 tmp_pu1 + 2,tmp_u3,0,0,0,tmp_pu1[8]);
      tmp_u3 = va("%iof%i",GHIDRA_FIELD(cgs, 33525616, 4) + 1,GHIDRA_FIELD(cgs, 33571584, 4));
      tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
      CG_Text_Paint_Centred_Ext
                (*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) + 15.0,*tmp_pu1,tmp_pu1[1],
                 tmp_pu1 + 2,tmp_u3,0,0,0,tmp_pu1[8]);
    }
  }
  else if (GHIDRA_FIELD(cgs, 33571608, 4) != 0) {
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    CG_Text_Paint_Centred_Ext
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,tmp_pu1[1],
               tmp_pu1 + 2,0x30f517c,0,0,0,tmp_pu1[8]);
  }
  return;
}

void CG_LoadPanel_RenderCampaignTypeText(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  
  tmp_u1 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
  tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x18);
  switch(GHIDRA_FIELD(cgs, 27388, 4)) {
  case 0:
    tmp_pc4 = "Single Player";
    break;
  case 1:
    tmp_pc4 = "Co-op";
    break;
  case 2:
    tmp_pc4 = "Objective";
    break;
  case 3:
    tmp_pc4 = "Stopwatch";
    break;
  case 4:
    tmp_pc4 = "Campaign";
    break;
  case 5:
    tmp_pc4 = "Last Man Standing";
    break;
  case 6:
    tmp_pc4 = "Map Voting";
    break;
  case 7:
    tmp_pc4 = "Team Death Match";
    break;
  case 8:
    tmp_pc4 = "Death Match";
    break;
  default:
    tmp_pc4 = "Invalid";
  }
  tmp_u5 = va(&g_unk_00116e3c,tmp_pc4);
  tmp_pu3 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu3,tmp_pu3[1],
                    tmp_pu3 + 2,tmp_u5,0,0,tmp_u2,tmp_u1);
  return;
}

char * CG_LoadPanel_GameTypeName(uint32_t param_1)
{
  switch(param_1) {
  case 0:
    return "Single Player";
  case 1:
    return "Co-op";
  case 2:
    return "Objective";
  case 3:
    return "Stopwatch";
  case 4:
    return "Campaign";
  case 5:
    return "Last Man Standing";
  case 6:
    return "Map Voting";
  case 7:
    return "Team Death Match";
  case 8:
    return "Death Match";
  default:
    return "Invalid";
  }
}

void CG_DrawConnectScreen(int param_1)
{
  void *tmp_pc1;
  float tmp_f2;
  bool tmp_b3;
  bool tmp_b4;
  bool tmp_b5;
  bool tmp_b6;
  bool tmp_b7;
  int *tmp_pi8;
  bool tmp_b9;
  bool tmp_b10;
  bool tmp_b11;
  bool tmp_b12;
  bool tmp_b13;
  uint tmp_u14;
  uint32_t tmp_u15;
  uint tmp_u16;
  char *tmp_pc17;
  long tmp_l18;
  int tmp_i19;
  int tmp_i20;
  float local_c74;
  float local_c70;
  int local_c68;
  int *local_c44;
  int local_c40 [9];
  int local_c1c [256];
  uint32_t local_81c;
  uint32_t local_818 [255];
  char local_41c [4];
  uint32_t local_418 [257];
  uint32_t uStack_14;
  
  uStack_14 = 0x8bc0d;
  local_81c = 0;
  tmp_u16 = 0;
  do {
    tmp_u14 = tmp_u16;
    *(uint32_t *)((int)local_818 + tmp_u14) = 0;
    *(uint32_t *)((int)local_818 + tmp_u14 + 4) = 0;
    tmp_u16 = tmp_u14 + 8;
  } while (tmp_u14 + 8 < 0x3f8);
  *(uint32_t *)((int)local_818 + tmp_u14 + 8) = 0;
  local_41c[0] = '\0';
  local_41c[1] = '\0';
  local_41c[2] = '\0';
  local_41c[3] = '\0';
  tmp_u16 = 0;
  do {
    tmp_u14 = tmp_u16;
    *(uint32_t *)((int)local_418 + tmp_u14) = 0;
    *(uint32_t *)((int)local_418 + tmp_u14 + 4) = 0;
    tmp_u16 = tmp_u14 + 8;
  } while (tmp_u14 + 8 < 0x3f8);
  *(uint32_t *)((int)local_418 + tmp_u14 + 8) = 0;
  local_c44 = (int *)0x0;
  local_c40[1] = 0x3f800000;
  local_c40[2] = 0x3f800000;
  local_c40[3] = 0x3f800000;
  local_c40[4] = 0x3f800000;
  local_c40[5] = 0x3e19999a;
  local_c40[6] = 0x3e19999a;
  local_c40[7] = 0x3e19999a;
  local_c40[8] = 0x3eb33333;
  if ((DC != (uint32_t *)0x0) && (inside_12265 == 0)) {
    inside_12265 = 1;
    if (bg_loadscreeninited == 0) {
      trap_Cvar_Set("ui_connecting",&g_unk_0011e957);
      (*(void *)DC[0x16])("ariblk",0x1b,bg_loadscreenfont1);
      (*(void *)DC[0x16])("courbd",0x1e,bg_loadscreenfont2);
      bg_filter_nxac = (*(void *)*DC)("ui/assets/filter_nxac_loading.tga");
      bg_filter_ff = (*(void *)*DC)("ui/assets/filter_ff");
      bg_filter_hw = (*(void *)*DC)("ui/assets/filter_weap");
      bg_filter_lv = (*(void *)*DC)("ui/assets/filter_lives");
      bg_filter_al = (*(void *)*DC)("ui/assets/filter_antilag");
      bg_filter_bt = (*(void *)*DC)("ui/assets/filter_balance");
      bg_mappic = 0;
      BG_PanelButtonsSetup(loadpanelButtons);
      bg_loadscreeninited = 1;
    }
    CG_FillRectFullScreen(0,0,0x44200000,0x43f00000,&colorBlack);
    BG_PanelButtonsRender(loadpanelButtons);
    trap_GetHunkData(local_c40,local_c1c);
    if (0 < local_c1c[0]) {
      tmp_f2 = (float)local_c40[0] / (float)local_c1c[0];
      if (tmp_f2 < 0.0) {
        tmp_f2 = 0.0;
      }
      else if (1.0 < tmp_f2) {
        tmp_f2 = 1.0;
      }
      CG_FilledBar(0x43820000,0x43e50000,0x42f00000,0x41200000,colorMdRed,0,0,tmp_f2,0x50);
      CG_DrawRect_FixedBorder(0x43820000,0x43e50000,0x42f00000,0x41200000,1,colorDkGrey);
    }
    CG_Text_Paint_Centred_Ext
              (0x43a00000,0x43e90000,0x3e4ccccd,0x3e4ccccd,&colorWhite,&g_unk_01091a7c,0,0,7,
               bg_loadscreenfont2);
    if (cgs[0x6b4c] != '\0') {
      if (bg_mappic == 0) {
        tmp_pc1 = (void *)*DC;
        tmp_u15 = va("levelshots/%s",0x10f69ac);
        bg_mappic = (*tmp_pc1)(tmp_u15);
        if (bg_mappic == 0) {
          bg_mappic = (*(void *)*DC)("levelshots/unknownmap");
        }
      }
      trap_R_SetColor(0);
      CG_DrawPic(0x43600000,0x40000000,0x43400000,0x43100000,bg_mappic);
    }
    (*(void *)DC[0x43])(0,local_c1c,0x400);
    if ((char)local_c1c[0] != '\0') {
      local_c70 = 0.0;
      local_c44 = local_c1c;
      tmp_b9 = false;
      tmp_b10 = false;
      tmp_b11 = false;
      tmp_b12 = false;
      tmp_b13 = false;
      while( true ) {
        tmp_b7 = tmp_b13;
        tmp_b6 = tmp_b12;
        tmp_b5 = tmp_b11;
        tmp_b4 = tmp_b10;
        tmp_b3 = tmp_b9;
        Info_NextPair(&local_c44,&local_81c,local_41c);
        if ((char)local_81c == '\0') break;
        tmp_u15 = nitrox_GetTokenForString(&local_81c);
        tmp_b9 = tmp_b3;
        tmp_b10 = tmp_b4;
        tmp_b11 = tmp_b5;
        tmp_b12 = tmp_b6;
        tmp_b13 = tmp_b7;
        switch(tmp_u15) {
        case 0x4c:
          tmp_pc17 = "ETHost";
          if (local_41c[0] != '\0') {
            tmp_pc17 = local_41c;
          }
          tmp_i20 = CG_Text_Width_Ext(tmp_pc17,0x3e800000,0x20,bg_loadscreenfont1);
          local_c70 = (float)tmp_i20;
          tmp_pc17 = "ETHost";
          if (local_41c[0] != '\0') {
            tmp_pc17 = local_41c;
          }
          CG_Text_Paint_Centred_Ext
                    (0x43a00000,0x438c0000,0x3e800000,0x3e800000,&colorWhite,tmp_pc17,0,0x20,0,
                     bg_loadscreenfont1);
          break;
        case 0x4d:
          tmp_u16 = strtol(local_41c,(char **)0x0,10);
          tmp_b9 = true;
          if ((tmp_u16 & 1) == 0) {
            tmp_b9 = tmp_b3;
          }
          break;
        case 0x4f:
        case 0x50:
        case 0x51:
          tmp_l18 = strtol(local_41c,(char **)0x0,10);
          tmp_b13 = true;
          if (tmp_l18 == 0) {
            tmp_b13 = tmp_b7;
          }
          break;
        case 0x53:
          tmp_l18 = strtol(local_41c,(char **)0x0,10);
          tmp_b12 = true;
          if (tmp_l18 == 100) {
            tmp_b12 = tmp_b6;
          }
          break;
        case 0x54:
          tmp_l18 = strtol(local_41c,(char **)0x0,10);
          tmp_b11 = true;
          if (tmp_l18 == 0) {
            tmp_b11 = tmp_b5;
          }
          break;
        case 0x55:
          tmp_l18 = strtol(local_41c,(char **)0x0,10);
          tmp_b10 = true;
          if (tmp_l18 == 0) {
            tmp_b10 = tmp_b4;
          }
        }
      }
      tmp_i20 = 0;
      tmp_pc17 = (char *)Info_ValueForKey(local_c1c,&g_unk_00116efa);
      tmp_l18 = strtol(tmp_pc17,(char **)0x0,10);
      local_c68 = -1;
      local_c74 = 300.0;
      do {
        tmp_pc17 = (char *)CG_ConfigString(tmp_i20 + 0x349);
        if ((tmp_pc17 != (char *)0x0) && (*tmp_pc17 != '\0')) {
          if ((local_c70 == 0.0) ||
             (tmp_i19 = CG_Text_Width_Ext(tmp_pc17,0x3e800000,0x32,bg_loadscreenfont1),
             local_c70 < (float)tmp_i19)) {
            tmp_i19 = CG_Text_Width_Ext(tmp_pc17,0x3e800000,0x32,bg_loadscreenfont1);
            local_c70 = (float)tmp_i19;
          }
          CG_Text_Paint_Centred_Ext
                    (0x43a00000,local_c74,0x3e4ccccd,0x3e4ccccd,&colorWhite,tmp_pc17,0,0x32,0,
                     bg_loadscreenfont2);
          local_c68 = tmp_i20;
        }
        local_c74 = local_c74 + 11.0;
        tmp_i20 = tmp_i20 + 1;
      } while (tmp_i20 != 7);
      if (local_c68 != -1) {
        CG_FillRect((320.0 - local_c70 * 0.5) - 4.0,0x43860000,local_c70 + 8.0,
                    (float)(local_c68 * 0xb + 0x23),local_c40 + 5);
      }
      tmp_pi8 = local_c40 + 1;
      local_c40[4] = 0x3f800000;
      if (!tmp_b3) {
        local_c40[4] = 0x3e4ccccd;
      }
      trap_R_SetColor(tmp_pi8);
      CG_DrawPic(0x436c0000,0x43cc0000,0x41800000,0x41800000,bg_filter_ff);
      trap_R_SetColor(0);
      local_c40[4] = 0x3f800000;
      if (!tmp_b4) {
        local_c40[4] = 0x3e4ccccd;
      }
      trap_R_SetColor(tmp_pi8);
      CG_DrawPic(0x43840000,0x43cc0000,0x41800000,0x41800000,bg_filter_bt);
      trap_R_SetColor(0);
      local_c40[4] = 0x3f800000;
      if (!tmp_b5) {
        local_c40[4] = 0x3e4ccccd;
      }
      trap_R_SetColor(tmp_pi8);
      CG_DrawPic(0x43920000,0x43cc0000,0x41800000,0x41800000,bg_filter_al);
      trap_R_SetColor(0);
      local_c40[4] = 0x3f800000;
      if (!tmp_b6) {
        local_c40[4] = 0x3e4ccccd;
      }
      trap_R_SetColor(tmp_pi8);
      CG_DrawPic(0x43a00000,0x43cc0000,0x41800000,0x41800000,bg_filter_hw);
      trap_R_SetColor(0);
      local_c40[4] = 0x3f800000;
      if (!tmp_b7) {
        local_c40[4] = 0x3e4ccccd;
      }
      trap_R_SetColor(tmp_pi8);
      CG_DrawPic(0x43ae0000,0x43cc0000,0x41800000,0x41800000,bg_filter_lv);
      trap_R_SetColor(0);
      local_c40[4] = 0x3f800000;
      if (tmp_l18 == 0) {
        local_c40[4] = 0x3e4ccccd;
      }
      trap_R_SetColor(tmp_pi8);
      CG_DrawPic(0x43bc0000,0x43cc0000,0x41800000,0x41800000,bg_filter_nxac);
      trap_R_SetColor(0);
      tmp_u15 = va(&g_unk_00116f08,&g_unk_00116f02);
      CG_Text_Paint_Centred_Ext
                (0x43a00000,0x43e10000,0x3e4ccccd,0x3e4ccccd,&colorWhite,tmp_u15,0,0,0,
                 bg_loadscreenfont2);
      if (param_1 != 0) {
        (*(void *)DC[0x41])();
      }
    }
    inside_12265 = 0;
  }
  return;
}

void CG_LoadPanel_KeyHandling(uint32_t param_1,uint32_t param_2)
{
  BG_PanelButtonsKeyEvent(param_1,param_2,loadpanelButtons);
  return;
}

uint32_t CG_LoadPanel_ContinueButtonKeyDown(uint32_t param_1,int param_2)
{
  if (param_2 != 0xb2) {
    return 0;
  }
  CG_EventHandling(1,0);
  return 1;
}

void CG_DrawCinematic(uint32_t param_1,float param_2,float param_3,float param_4,float param_5)
{
  trap_CIN_SetExtents(param_1,(int)ROUND(param_2),(int)ROUND(param_3),(int)ROUND(param_4),
                      (int)ROUND(param_5));
  trap_CIN_DrawCinematic(param_1);
  return;
}

void jP_SetHUDColors(void)
{
  char *tmp_pc1;
  int tmp_i2;
  char *tmp_pc3;
  uint8_t tmp_u4;
  uint8_t tmp_u5;
  bool tmp_b6;
  byte tmp_b7;
  double tmp_d8;
  float local_234 [6];
  char local_21c;
  char local_21b;
  char local_21a;
  char local_219;
  char local_11c;
  char local_11b;
  char local_11a;
  char local_119;
  uint32_t uStack_14;
  
  tmp_b7 = 0;
  uStack_14 = 0x96783;
  tmp_u4 = &stack0x00000000 == (uint8_t *)0x25c;
  Q_strncpyz();
  Q_strncpyz();
  tmp_i2 = 8;
  tmp_pc1 = &local_11c;
  tmp_pc3 = "default";
  do {
    if (tmp_i2 == 0) break;
    tmp_i2 = tmp_i2 + -1;
    tmp_u4 = *tmp_pc1 == *tmp_pc3;
    tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
    tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
  } while ((bool)tmp_u4);
  tmp_u5 = true;
  if ((bool)tmp_u4) {
LAB_00096864:
    trap_Cvar_Set();
  }
  else {
    if (local_11c == 'd') {
      tmp_u5 = local_11b == 'e';
      if (((!(bool)tmp_u5) || (tmp_u5 = local_11a == 'f', !(bool)tmp_u5)) ||
         (tmp_u5 = local_119 == '\0', !(bool)tmp_u5)) goto LAB_00096a10;
      goto LAB_00096864;
    }
    tmp_u5 = false;
    if (((local_11c == 'r') && (tmp_u5 = false, local_11b == 'e')) &&
       ((tmp_u5 = false, local_11a == 'd' && (tmp_u5 = local_119 == '\0', (bool)tmp_u5))))
    goto LAB_00096864;
LAB_00096a10:
    tmp_i2 = 6;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "green";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
    tmp_i2 = 5;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "blue";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
    tmp_i2 = 6;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "black";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
    tmp_i2 = 6;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "white";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
    tmp_i2 = 7;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "dkgrey";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
    tmp_i2 = 9;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "darkgrey";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
    tmp_i2 = 7;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "dkgray";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
    tmp_i2 = 9;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "darkgray";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
    tmp_i2 = 5;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "grey";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
    tmp_i2 = 5;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "gray";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
    tmp_i2 = 8;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "cthulhu";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
    tmp_i2 = 0xe;
    tmp_pc1 = &local_11c;
    tmp_pc3 = "cthulhu_green";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_u5 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while ((bool)tmp_u5);
    if ((bool)tmp_u5) goto LAB_00096864;
  }
  tmp_i2 = 8;
  tmp_pc1 = &local_21c;
  tmp_pc3 = "default";
  do {
    if (tmp_i2 == 0) break;
    tmp_i2 = tmp_i2 + -1;
    tmp_u5 = *tmp_pc1 == *tmp_pc3;
    tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
    tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
  } while ((bool)tmp_u5);
  if ((bool)tmp_u5) {
LAB_00096901:
    trap_Cvar_Set();
  }
  else {
    if (local_21c == 'd') {
      if (((local_21b == 'e') && (local_21a == 'f')) && (local_219 == '\0')) goto LAB_00096901;
    }
    else if ((((local_21c == 'r') && (local_21b == 'e')) && (local_21a == 'd')) &&
            (local_219 == '\0')) {
      trap_Cvar_Set();
      goto LAB_00096919;
    }
    tmp_b6 = false;
    tmp_i2 = 6;
    tmp_pc1 = &local_21c;
    tmp_pc3 = "green";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_b6 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while (tmp_b6);
    if (tmp_b6) {
      trap_Cvar_Set();
      goto LAB_00096919;
    }
    tmp_i2 = 5;
    tmp_b6 = false;
    tmp_pc1 = &local_21c;
    tmp_pc3 = "blue";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_b6 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while (tmp_b6);
    if (tmp_b6) {
      trap_Cvar_Set();
      goto LAB_00096919;
    }
    tmp_i2 = 6;
    tmp_b6 = false;
    tmp_pc1 = &local_21c;
    tmp_pc3 = "black";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_b6 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while (tmp_b6);
    if (tmp_b6) {
      trap_Cvar_Set();
      goto LAB_00096919;
    }
    tmp_i2 = 6;
    tmp_b6 = false;
    tmp_pc1 = &local_21c;
    tmp_pc3 = "white";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_b6 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while (tmp_b6);
    if (tmp_b6) {
      trap_Cvar_Set();
      goto LAB_00096919;
    }
    tmp_i2 = 7;
    tmp_b6 = false;
    tmp_pc1 = &local_21c;
    tmp_pc3 = "dkgrey";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_b6 = *tmp_pc1 == *tmp_pc3;
      tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
    } while (tmp_b6);
    if (!tmp_b6) {
      tmp_i2 = 9;
      tmp_pc1 = &local_21c;
      tmp_pc3 = "darkgrey";
      do {
        if (tmp_i2 == 0) break;
        tmp_i2 = tmp_i2 + -1;
        tmp_b6 = *tmp_pc1 == *tmp_pc3;
        tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
      } while (tmp_b6);
      if (!tmp_b6) {
        tmp_i2 = 7;
        tmp_pc1 = &local_21c;
        tmp_pc3 = "dkgray";
        do {
          if (tmp_i2 == 0) break;
          tmp_i2 = tmp_i2 + -1;
          tmp_b6 = *tmp_pc1 == *tmp_pc3;
          tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
          tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
        } while (tmp_b6);
        if (!tmp_b6) {
          tmp_i2 = 9;
          tmp_pc1 = &local_21c;
          tmp_pc3 = "darkgray";
          do {
            if (tmp_i2 == 0) break;
            tmp_i2 = tmp_i2 + -1;
            tmp_b6 = *tmp_pc1 == *tmp_pc3;
            tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
            tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
          } while (tmp_b6);
          if (!tmp_b6) {
            tmp_i2 = 5;
            tmp_pc1 = &local_21c;
            tmp_pc3 = "grey";
            do {
              if (tmp_i2 == 0) break;
              tmp_i2 = tmp_i2 + -1;
              tmp_b6 = *tmp_pc1 == *tmp_pc3;
              tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
              tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
            } while (tmp_b6);
            if (!tmp_b6) {
              tmp_i2 = 5;
              tmp_pc1 = &local_21c;
              tmp_pc3 = "gray";
              do {
                if (tmp_i2 == 0) break;
                tmp_i2 = tmp_i2 + -1;
                tmp_b6 = *tmp_pc1 == *tmp_pc3;
                tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
                tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
              } while (tmp_b6);
              if (!tmp_b6) {
                tmp_i2 = 8;
                tmp_pc1 = &local_11c;
                tmp_pc3 = "cthulhu";
                do {
                  if (tmp_i2 == 0) break;
                  tmp_i2 = tmp_i2 + -1;
                  tmp_b6 = *tmp_pc1 == *tmp_pc3;
                  tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
                  tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
                } while (tmp_b6);
                if (!tmp_b6) {
                  tmp_i2 = 0xe;
                  tmp_pc1 = &local_11c;
                  tmp_pc3 = "cthulhu_green";
                  do {
                    if (tmp_i2 == 0) break;
                    tmp_i2 = tmp_i2 + -1;
                    tmp_b6 = *tmp_pc1 == *tmp_pc3;
                    tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
                    tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
                  } while (tmp_b6);
                  if (!tmp_b6) goto LAB_00096919;
                }
                trap_Cvar_Set();
                goto LAB_00096919;
              }
            }
            goto LAB_00096901;
          }
        }
      }
    }
    trap_Cvar_Set();
  }
LAB_00096919:
  tmp_pc1 = strtok(&local_11c," ");
  if (tmp_pc1 != (char *)0x0) {
    tmp_i2 = 0;
    do {
      tmp_d8 = strtod(tmp_pc1,(char **)0x0);
      local_234[tmp_i2 + 3] = (float)tmp_d8;
      tmp_i2 = tmp_i2 + 1;
      tmp_pc1 = strtok((char *)0x0," ,");
      if (2 < tmp_i2) break;
    } while (tmp_pc1 != (char *)0x0);
  }
  tmp_pc1 = strtok(&local_21c," ");
  if (tmp_pc1 != (char *)0x0) {
    tmp_i2 = 0;
    do {
      tmp_d8 = strtod(tmp_pc1,(char **)0x0);
      local_234[tmp_i2] = (float)tmp_d8;
      tmp_i2 = tmp_i2 + 1;
      tmp_pc1 = strtok((char *)0x0," ,");
      if (2 < tmp_i2) {
        HUD_Alpha = GHIDRA_FIELD(cg_HUDAlpha, 8, 4);
        HUD_Border = local_234[3];
        g_unk_00143ecc = local_234[4];
        g_unk_00143ed0 = local_234[5];
        g_unk_00143ed4 = GHIDRA_FIELD(cg_HUDAlpha, 8, 4);
        HUD_Background = local_234[0];
        g_unk_00143edc = local_234[1];
        g_unk_00143ee0 = local_234[2];
        g_unk_00143ee4 = GHIDRA_FIELD(cg_HUDAlpha, 8, 4);
        return;
      }
    } while (tmp_pc1 != (char *)0x0);
  }
  HUD_Alpha = GHIDRA_FIELD(cg_HUDAlpha, 8, 4);
  HUD_Border = local_234[3];
  g_unk_00143ecc = local_234[4];
  g_unk_00143ed0 = local_234[5];
  g_unk_00143ed4 = GHIDRA_FIELD(cg_HUDAlpha, 8, 4);
  HUD_Background = local_234[0];
  g_unk_00143edc = local_234[1];
  g_unk_00143ee0 = local_234[2];
  g_unk_00143ee4 = GHIDRA_FIELD(cg_HUDAlpha, 8, 4);
  return;
}

void CG_DrawPlayerWeaponIcon(float *param_1,uint32_t param_2,int param_3,uint32_t *param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  local_2c = *param_4;
  local_20 = 0x3f800000;
  local_28 = param_4[1];
  local_24 = param_4[2];
  if ((g_unk_01090cb0 & 0x8020) == 0) {
    tmp_i7 = g_unk_010907a0;
    tmp_i9 = *(int *)(cg_weapons + g_unk_010907a0 * 0x17ac + 0x1798);
    if (*(int *)(cg_weapons + g_unk_010907a0 * 0x17ac + 0x1798) == 0) {
      switch(g_unk_010907a0) {
      case 3:
      case 5:
      case 6:
      case 8:
      case 10:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x1d:
      case 0x1e:
      case 0x1f:
      case 0x21:
      case 0x24:
      case 0x25:
      case 0x27:
      case 0x28:
      case 0x29:
      case 0x2a:
      case 0x2e:
        goto _L48;
      default:
        tmp_i9 = 1;
      }
    }
  }
  else {
    tmp_i7 = 0x1d;
    tmp_i9 = GHIDRA_FIELD(cg_weapons, 181780, 4);
    if (GHIDRA_FIELD(cg_weapons, 181780, 4) != 0) goto LAB_00098962;
_L48:
    tmp_i9 = 2;
  }
LAB_00098962:
  CG_HudPlacement(2);
  if (((g_unk_01090cb0 & 0x8000) == 0) ||
     (tmp_i8 = GHIDRA_FIELD(cgs, 131844, 4),
     (cg_entities
      [*(int *)(cg_entities +
               *(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xab4) * 0xaf8 + 0x9bc
               ) * 0xaf8 + 0xf4] & 8) == 0)) {
    tmp_i8 = *(int *)(cg_weapons + tmp_i7 * 0x17ac + 0x1714);
  }
  if (g_unk_01090730 == 0) {
    tmp_f5 = 0.0;
    tmp_f6 = tmp_f5;
  }
  else {
    if (tmp_i7 == 1) {
      tmp_f5 = (float)g_unk_01090730 / 50.0;
    }
    else {
      tmp_f5 = (float)(g_unk_01090730 % 1000) / 100.0;
    }
    tmp_f6 = tmp_f5 * 0.5;
    g_unk_010aacf4 = g_unk_01090730;
  }
  if (tmp_i8 != 0) {
    tmp_f2 = *param_1 - tmp_f6;
    tmp_f1 = param_1[1];
    if (tmp_i9 == 1) {
      tmp_f3 = param_1[2] * 0.5;
      tmp_f4 = tmp_f3 + tmp_f5;
      tmp_f5 = tmp_f5 + param_1[3];
      if (param_3 == 1) {
        tmp_f2 = param_1[2] * 0.25 + tmp_f2;
      }
      else if (param_3 == 2) {
        tmp_f2 = tmp_f2 + tmp_f3;
      }
    }
    else {
      tmp_f4 = param_1[2] + tmp_f5;
      tmp_f5 = tmp_f5 + param_1[3];
    }
    trap_R_SetColor(&local_2c);
    CG_DrawPic(tmp_f2,tmp_f1 - tmp_f6,tmp_f4,tmp_f5,tmp_i8);
  }
  return;
}

void CG_DrawCursorhint(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  double tmp_d10;
  float local_3c;
  float local_38;
  
  if (GHIDRA_FIELD(cg_cursorHints, 12, 4) != 0) {
    CG_HudPlacement(0);
    CG_CheckForCursorHints();
    switch(g_unk_010aac08) {
    case 0:
    case 1:
    case 0x19:
    case 0x1a:
    case 0x1c:
      goto _L79;
    default:
      tmp_i9 = GHIDRA_FIELD(cgs, 68104, 4);
      break;
    case 4:
      tmp_i9 = GHIDRA_FIELD(cgs, 68112, 4);
      break;
    case 5:
      tmp_i9 = GHIDRA_FIELD(cgs, 68116, 4);
      break;
    case 6:
      tmp_i9 = GHIDRA_FIELD(cgs, 68120, 4);
      break;
    case 7:
      tmp_i9 = GHIDRA_FIELD(cgs, 68124, 4);
      break;
    case 8:
      tmp_i9 = GHIDRA_FIELD(cgs, 68128, 4);
      break;
    case 9:
      tmp_i9 = GHIDRA_FIELD(cgs, 68132, 4);
      break;
    case 10:
    case 0x20:
      tmp_i9 = GHIDRA_FIELD(cgs, 68196, 4);
      break;
    case 0xb:
      tmp_i9 = GHIDRA_FIELD(cgs, 68108, 4);
      break;
    case 0xc:
      tmp_i9 = GHIDRA_FIELD(cgs, 68140, 4);
      break;
    case 0xd:
      tmp_i9 = GHIDRA_FIELD(cgs, 68144, 4);
      break;
    case 0xe:
      tmp_i9 = GHIDRA_FIELD(cgs, 68148, 4);
      break;
    case 0xf:
      tmp_i9 = GHIDRA_FIELD(cgs, 68152, 4);
      break;
    case 0x10:
      tmp_i9 = GHIDRA_FIELD(cgs, 68156, 4);
      break;
    case 0x11:
      tmp_i9 = GHIDRA_FIELD(cgs, 68160, 4);
      break;
    case 0x12:
      tmp_i9 = GHIDRA_FIELD(cgs, 68164, 4);
      break;
    case 0x13:
      tmp_i9 = GHIDRA_FIELD(cgs, 68168, 4);
      break;
    case 0x14:
      tmp_i9 = GHIDRA_FIELD(cgs, 68172, 4);
      break;
    case 0x15:
      tmp_i9 = GHIDRA_FIELD(cgs, 68180, 4);
      break;
    case 0x1d:
    case 0x21:
      tmp_i9 = GHIDRA_FIELD(cgs, 68184, 4);
      break;
    case 0x1e:
      tmp_i9 = GHIDRA_FIELD(cgs, 68188, 4);
      break;
    case 0x1f:
      tmp_i9 = GHIDRA_FIELD(cgs, 68192, 4);
      break;
    case 0x22:
      tmp_i9 = GHIDRA_FIELD(cgs, 68208, 4);
      break;
    case 0x23:
      tmp_i9 = GHIDRA_FIELD(cgs, 68480, 4);
      break;
    case 0x24:
      tmp_i9 = GHIDRA_FIELD(cgs, 68200, 4);
      break;
    case 0x25:
      tmp_i9 = GHIDRA_FIELD(cgs, 68204, 4);
      break;
    case 0x26:
      tmp_i9 = GHIDRA_FIELD(cgs, 67964, 4);
    }
    if (tmp_i9 != 0) {
      tmp_pu6 = (uint32_t *)CG_FadeColor(g_unk_010aac0c,g_unk_010aac10);
      if (tmp_pu6 != (uint32_t *)0x0) {
        if (GHIDRA_FIELD(cg_cursorHints, 12, 4) == 3) {
          tmp_d10 = sin((double)((float)g_unk_010906e0 / 150.0));
          tmp_pu6[3] = ((float)tmp_d10 * 0.5 + 0.5) * (float)tmp_pu6[3];
        }
        if ((int)GHIDRA_FIELD(cg_cursorHints, 12, 4) < 3) {
          if (GHIDRA_FIELD(cg_cursorHints, 12, 4) == 2) {
            local_3c = (float)(g_unk_010aac0c % 1000) / 100.0;
          }
          else {
            tmp_d10 = sin((double)((float)g_unk_010906e0 / 150.0));
            local_3c = ((float)tmp_d10 * 0.5 + 0.5) * 10.0;
          }
          local_38 = local_3c * 0.5;
        }
        else {
          local_38 = 0.0;
          local_3c = 0.0;
        }
        trap_R_SetColor(tmp_pu6);
        if (1 < g_unk_010aac08 - 0x12U) {
          CG_DrawPic(*param_1 - local_38,param_1[1] - local_38,param_1[2] + local_3c,
                     param_1[3] + local_3c,tmp_i9);
          trap_R_SetColor(0);
          if (g_unk_010aac14 == 0) {
            return;
          }
          *tmp_pu6 = 0;
          tmp_pu6[1] = 0;
          tmp_pu6[2] = 0x3f800000;
          tmp_pu6[3] = 0x3f000000;
          CG_FilledBar(*param_1,param_1[3] + param_1[1] + 4.0,param_1[2],0x41000000,tmp_pu6,0,0,
                       (float)g_unk_010aac14 / 255.0,0);
          return;
        }
        tmp_i5 = *(int *)(cg_weapons + g_unk_010aac14 * 0x17ac + 0x1714);
        if (tmp_i5 != 0) {
          tmp_f1 = param_1[3];
          tmp_i7 = weaponIconScale(g_unk_010aac14);
          tmp_f2 = param_1[2];
          tmp_f3 = param_1[1];
          tmp_f4 = *param_1;
          tmp_i8 = weaponIconScale(g_unk_010aac14);
          CG_DrawPic(tmp_f4 - (float)tmp_i8 * local_38,tmp_f3 - local_38,
                     (local_3c + tmp_f2) * (float)tmp_i7,local_3c + tmp_f1,tmp_i5);
        }
        if (g_unk_010aac08 == 0x13) {
          CG_DrawPic(*param_1 - local_38,param_1[1] - local_38,param_1[2] + local_3c,
                     param_1[3] + local_3c,tmp_i9);
        }
      }
      trap_R_SetColor(0);
    }
  }
_L79:
  return;
}

void CG_DrawWeapStability(uint32_t *param_1)
{
  int tmp_i1;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_2c = 0;
  local_28 = 0x3f800000;
  local_24 = 0;
  local_20 = 0x3f000000;
  local_1c = 0x3f800000;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0x3f000000;
  if (((GHIDRA_FIELD(cg_drawSpreadScale, 12, 4) != 0) &&
      (((GHIDRA_FIELD(cg_drawSpreadScale, 12, 4) != 1 || (tmp_i1 = BG_IsScopedWeapon(g_unk_010907a0), tmp_i1 != 0)) &&
       (g_unk_010907a4 == 0)))) && ((*(int *)(g_unk_01047b00 + 0x4b8) != 0 && (g_unk_010906f4 == 0)))) {
    CG_HudPlacement(1);
    CG_FilledBar(*param_1,param_1[1],param_1[2],param_1[3],&local_2c,&local_1c,0,
                 (float)*(int *)(g_unk_01047b00 + 0x4b8) / 255.0,0x106);
  }
  return;
}

void CG_DrawWeapHeat(uint32_t *param_1)
{
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_2c = 0x3f800000;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0x3e4ccccd;
  local_1c = 0x3f800000;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0x3f000000;
  if (*(int *)(g_unk_01047b00 + 0x5c8) == 0) {
    return;
  }
  CG_HudPlacement(2);
  CG_FilledBar(*param_1,param_1[1],param_1[2],param_1[3],&local_2c,&local_1c,0,
               (float)*(int *)(g_unk_01047b00 + 0x5c8) / 255.0,0);
  return;
}

void CG_DrawPMItems(void)
{
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  float local_44;
  int local_40;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  tmp_i3 = cg_pmOldList;
  uStack_14 = 0xa9f19;
  local_2c = 0x3f800000;
  local_28 = 0x3f800000;
  local_24 = 0x3f800000;
  local_20 = 1.0;
  tmp_i4 = GHIDRA_FIELD(cg_numPopups, 12, 4);
  if (8.0 < (float)GHIDRA_FIELD(cg_numPopups, 8, 4)) {
    tmp_i4 = 8;
  }
  if (0 < (int)GHIDRA_FIELD(cg_numPopups, 12, 4)) {
    CG_HudPlacement(1);
    if ((GHIDRA_FIELD(cg_HUDFlags, 12, 4) & 2) == 0) {
      if ((GHIDRA_FIELD(cg_HUDFlags, 12, 4) & 1) == 0) {
        local_44 = 360.0;
      }
      else {
        local_44 = 310.0;
      }
    }
    else {
      local_44 = 70.0;
      tmp_i4 = 5;
    }
    if (cg_pmWaitingList != 0) {
      tmp_f1 = (float)(*(int *)(cg_pmWaitingList + 8) + 0x5dc);
      if (tmp_f1 < (float)g_unk_010906e0) {
        local_20 = 1.0 - ((float)g_unk_010906e0 - tmp_f1) / (float)(int)GHIDRA_FIELD(cg_popupFadeTime, 12, 4);
      }
      if (0 < *(int *)(cg_pmWaitingList + 0x114)) {
        local_2c = *(uint32_t *)(cg_pmWaitingList + 0x118);
        local_28 = *(uint32_t *)(cg_pmWaitingList + 0x11c);
        local_24 = *(uint32_t *)(cg_pmWaitingList + 0x120);
        trap_R_SetColor(&local_2c);
        CG_DrawPic(0x40800000,local_44,0x41400000,0x41400000,
                   *(uint32_t *)(cg_pmWaitingList + 0x114));
        local_2c = 0x3f800000;
        local_28 = 0x3f800000;
        local_24 = 0x3f800000;
        trap_R_SetColor(0);
      }
      CG_Text_Paint_Ext(0x41900000,local_44 + 12.0,0x3e4ccccd,0x3e4ccccd,&local_2c,
                        cg_pmWaitingList + 0xc,0,0,7,0x110afec);
      if (*(char *)(cg_pmWaitingList + 0x8c) != '\0') {
        tmp_i2 = CG_Text_Width_Ext(cg_pmWaitingList + 0xc,0x3e4ccccd,0,0x110afec);
        local_2c = *(uint32_t *)(cg_pmWaitingList + 0x118);
        local_28 = *(uint32_t *)(cg_pmWaitingList + 0x11c);
        local_24 = *(uint32_t *)(cg_pmWaitingList + 0x120);
        trap_R_SetColor(&local_2c);
        CG_DrawPic((float)tmp_i2 + 4.0 + 12.0 + 10.0,local_44,
                   (float)(*(int *)(cg_pmWaitingList + 0x110) << 4),0x41800000,
                   *(uint32_t *)(cg_pmWaitingList + 0x10c));
        local_2c = 0x3f800000;
        local_28 = 0x3f800000;
        local_24 = 0x3f800000;
        trap_R_SetColor(0);
        CG_Text_Paint_Ext((float)(*(int *)(cg_pmWaitingList + 0x110) << 4) + 16.0 + 16.0 +
                          (float)tmp_i2,local_44 + 12.0,0x3e4ccccd,0x3e4ccccd,&local_2c,
                          cg_pmWaitingList + 0x8c,0,0,7,0x110afec);
      }
      if (0 < tmp_i4 + -1) {
        local_40 = 0;
        do {
          if (tmp_i3 == 0) {
            return;
          }
          local_44 = local_44 - 14.0;
          tmp_f1 = (float)(*(int *)(tmp_i3 + 8) + 0x5dc);
          if (tmp_f1 < (float)g_unk_010906e0) {
            local_20 = 1.0 - ((float)g_unk_010906e0 - tmp_f1) / (float)(int)GHIDRA_FIELD(cg_popupFadeTime, 12, 4);
          }
          else {
            local_20 = 1.0;
          }
          if (0 < *(int *)(tmp_i3 + 0x114)) {
            local_2c = *(uint32_t *)(tmp_i3 + 0x118);
            local_28 = *(uint32_t *)(tmp_i3 + 0x11c);
            local_24 = *(uint32_t *)(tmp_i3 + 0x120);
            trap_R_SetColor(&local_2c);
            CG_DrawPic(0x40800000,local_44,0x41400000,0x41400000,*(uint32_t *)(tmp_i3 + 0x114));
            local_2c = 0x3f800000;
            local_28 = 0x3f800000;
            local_24 = 0x3f800000;
            trap_R_SetColor(0);
          }
          CG_Text_Paint_Ext(0x41900000,local_44 + 12.0,0x3e4ccccd,0x3e4ccccd,&local_2c,tmp_i3 + 0xc,0
                            ,0,7,0x110afec);
          if (*(char *)(tmp_i3 + 0x8c) != '\0') {
            tmp_i2 = CG_Text_Width_Ext(tmp_i3 + 0xc,0x3e4ccccd,0,0x110afec);
            local_2c = *(uint32_t *)(tmp_i3 + 0x118);
            local_28 = *(uint32_t *)(tmp_i3 + 0x11c);
            local_24 = *(uint32_t *)(tmp_i3 + 0x120);
            trap_R_SetColor(&local_2c);
            CG_DrawPic((float)tmp_i2 + 16.0 + 10.0,local_44,(float)(*(int *)(tmp_i3 + 0x110) << 4),
                       0x41800000,*(uint32_t *)(tmp_i3 + 0x10c));
            local_2c = 0x3f800000;
            local_28 = 0x3f800000;
            local_24 = 0x3f800000;
            trap_R_SetColor(0);
            CG_Text_Paint_Ext((float)(*(int *)(tmp_i3 + 0x110) << 4) + 16.0 + 16.0 + (float)tmp_i2,
                              local_44 + 12.0,0x3e4ccccd,0x3e4ccccd,&local_2c,tmp_i3 + 0x8c,0,0,7,
                              0x110afec);
          }
          local_40 = local_40 + 1;
          tmp_i3 = *(int *)(tmp_i3 + 0x124);
        } while (local_40 < tmp_i4 + -1);
      }
    }
  }
  return;
}

void CG_DrawPMItemsBig(void)
{
  int tmp_i1;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  float local_10;
  
  local_1c = 0x3f800000;
  local_18 = 0x3f800000;
  local_14 = 0x3f800000;
  local_10 = 1.0;
  if (cg_pmWaitingListBig != 0) {
    CG_HudPlacement(2);
    if ((float)*(int *)(cg_pmWaitingListBig + 8) < (float)g_unk_010906e0) {
      local_10 = 1.0 - ((float)g_unk_010906e0 - (float)*(int *)(cg_pmWaitingListBig + 8)) / 5000.0;
    }
    local_1c = *(uint32_t *)(cg_pmWaitingListBig + 0x90);
    local_18 = *(uint32_t *)(cg_pmWaitingListBig + 0x94);
    local_14 = *(uint32_t *)(cg_pmWaitingListBig + 0x98);
    trap_R_SetColor(&local_1c);
    CG_DrawPic(0x44120000,0x43870000,0x42400000,0x42400000,
               *(uint32_t *)(cg_pmWaitingListBig + 0x8c));
    local_1c = 0x3f800000;
    local_18 = 0x3f800000;
    local_14 = 0x3f800000;
    trap_R_SetColor(0);
    tmp_i1 = CG_Text_Width_Ext(cg_pmWaitingListBig + 0xc,0x3e6147ae,0,0x110afec);
    CG_Text_Paint_Ext(636.0 - (float)tmp_i1,0x43a30000,0x3e6147ae,0x3e75c28f,&local_1c,
                      cg_pmWaitingListBig + 0xc,0,0,7,0x110afec);
  }
  return;
}

void WM_DrawClientScore_Small_isra_1(int param_1,int param_2,int *param_3,float param_4,int param_5)
{
  float tmp_f1;
  float tmp_f2;
  bool tmp_b3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  char *tmp_pc7;
  uint tmp_u8;
  byte tmp_b9;
  int tmp_i10;
  byte tmp_b11;
  float local_80;
  uint32_t local_74;
  int local_70;
  uint32_t local_60;
  uint32_t local_58;
  uint32_t local_54;
  uint32_t local_50;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  
  if (0x1c7 < param_2) {
    return;
  }
  tmp_i6 = *param_3;
  if (tmp_i6 == *(int *)(g_unk_01047b00 + 0xcc)) {
    local_20 = param_4 * 0.3;
    local_2c = 0x3f000000;
    local_28 = 0x3f000000;
    local_24 = 0x3e4ccccd;
    CG_FillRect((float)(param_1 + -5),(float)param_2,0x438e8000,0x41400000,&local_2c);
  }
  local_80 = (float)param_1;
  local_2c = 0x3f800000;
  local_28 = 0x3f800000;
  local_24 = 0x3f800000;
  local_20 = param_4;
  if ((param_3[2] == 999) || (param_3[2] == -1)) {
    local_50 = 10;
    local_74 = 0x10;
    tmp_u4 = 8;
    local_54 = 0xc;
    local_60 = 0xe;
    tmp_b3 = false;
    local_58 = 0x12;
  }
  else {
    tmp_u8 = *(uint *)(ClientFlags + *(int *)(cgs + tmp_i6 * 0x1a4 + 0x9410) * 4);
    if ((tmp_u8 < 0xff) && (GHIDRA_FIELD(cg_countryflags, 12, 4) != 0)) {
      tmp_f2 = (float)((tmp_u8 & 0xf) << 5);
      tmp_f1 = ROUND((float)(int)tmp_u8 * 32.0 * 0.001953125) * 32.0;
      CG_DrawPicST((local_80 - 11.0) - 1.0,(float)(param_2 + -0xc) + 3.0,0x42000000,0x42000000,
                   tmp_f2 * 0.001953125,tmp_f1 * 0.001953125,(tmp_f2 + 32.0) * 0.001953125,
                   (tmp_f1 + 32.0) * 0.001953125,GHIDRA_FIELD(cgs, 131908, 4));
      local_50 = 8;
      tmp_u4 = 6;
      local_54 = 10;
      local_60 = 0xc;
      local_74 = 0xe;
      local_80 = local_80 + 16.0;
      tmp_b3 = true;
      local_58 = 0x10;
    }
    else {
      local_50 = 10;
      tmp_u4 = 8;
      local_54 = 0xc;
      local_60 = 0xe;
      local_74 = 0x10;
      tmp_b3 = false;
      local_58 = 0x12;
    }
  }
  tmp_b11 = (*(byte *)(param_3 + 6) & 4) != 0;
  if ((bool)tmp_b11) {
    CG_DrawPic(local_80,(float)param_2,0x41400000,0x41400000,GHIDRA_FIELD(cgs, 67964, 4));
    local_58 = local_74;
    tmp_b9 = 2;
    local_74 = local_60;
    local_80 = local_80 + 14.0;
    local_60 = local_54;
    local_54 = local_50;
    local_70 = 0x78;
    local_50 = tmp_u4;
  }
  else {
    tmp_b9 = 1;
    local_70 = 0x86;
  }
  if (*(int *)(cgs + tmp_i6 * 0x1a4 + 0x9494) == 3) {
    local_74 = local_58;
LAB_000adcdf:
    CG_DrawStringExt((int)ROUND(local_80),param_2 + -1,tmp_i6 * 0x1a4 + 0x10f9274,&local_2c,0,1,6,0xc
                     ,local_74);
  }
  else {
    if ((cgs[tmp_i6 * 0x1a4 + 0x94b0] & 0x60) != 0) {
      CG_DrawPic(local_80,(float)param_2,0x41400000,0x41400000,GHIDRA_FIELD(cgs, 67992, 4));
      local_58 = local_74;
      local_74 = local_60;
      local_80 = local_80 + 14.0;
      local_60 = local_54;
      local_54 = local_50;
      local_70 = 0x78;
      tmp_b11 = tmp_b9;
    }
    if (((*(byte *)(param_3 + 6) & 3) != 0) && (GHIDRA_FIELD(cgs, 33525356, 4) != 0)) {
      CG_DrawPic(local_80,(float)param_2,0x41400000,0x41400000,GHIDRA_FIELD(cgs, 131760, 4));
      tmp_b11 = tmp_b11 + 1;
      local_70 = 0x78;
      local_58 = local_74;
      local_80 = local_80 + 14.0;
      local_74 = local_60;
      local_60 = local_54;
    }
    tmp_i5 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
    if (tmp_i5 == 3) {
      if (param_3[7] == -2) goto LAB_000ae6d4;
      tmp_i10 = *(int *)(cgs + tmp_i6 * 0x1a4 + 0x9494);
      local_74 = local_58;
LAB_000adcc0:
      tmp_i5 = tmp_i10;
      if (tmp_i10 == 3) goto LAB_000adcdf;
    }
    else {
      tmp_i10 = tmp_i6 * 0x1a4;
      if (tmp_i5 != *(int *)(cgs + tmp_i10 + 0x9494)) {
        if (param_3[7] == -2) goto LAB_000ae6d4;
        tmp_i10 = *(int *)(cgs + tmp_i10 + 0x9494);
        local_74 = local_58;
        goto LAB_000adcc0;
      }
      if ((cgs[tmp_i10 + 0x94b0] & 0x80) != 0) {
        CG_DrawPic(local_80,(float)param_2,0x41400000,0x41400000,GHIDRA_FIELD(cgs, 68900, 4));
        tmp_b11 = tmp_b11 + 1;
        local_80 = local_80 + 14.0;
        if (param_3[7] != -2) {
          local_70 = 0x78;
          tmp_i5 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
          tmp_i10 = *(int *)(cgs + tmp_i10 + 0x9494);
          if ((tmp_i5 == 3) || (tmp_i5 != tmp_i10)) goto LAB_000adcc0;
          goto LAB_000ae1d8;
        }
        local_74 = local_60;
LAB_000ae6d4:
        CG_DrawPic(local_80,(float)param_2,0x41400000,0x41400000,GHIDRA_FIELD(cgs, 67972, 4));
        tmp_b11 = tmp_b11 + 1;
        local_80 = local_80 + 14.0;
        tmp_i10 = *(int *)(cgs + tmp_i6 * 0x1a4 + 0x9494);
        local_70 = 0x78;
        goto LAB_000adcc0;
      }
      if (param_3[7] == -2) goto LAB_000ae6d4;
      local_60 = local_74;
      local_74 = local_58;
LAB_000ae1d8:
      if (*(int *)(cgs + *param_3 * 0x1a4 + 0x94a8) == -1) {
        local_74 = local_60;
        goto LAB_000ae6d4;
      }
      if (*(int *)(cgs + *param_3 * 0x1a4 + 0x94a8) == 0) {
        CG_DrawPic(local_80,(float)param_2,0x41400000,0x41400000,GHIDRA_FIELD(cgs, 69808, 4));
        tmp_b11 = tmp_b11 + 1;
        local_80 = local_80 + 14.0;
        tmp_i10 = *(int *)(cgs + tmp_i6 * 0x1a4 + 0x9494);
        local_74 = local_60;
        local_70 = 0x78;
        goto LAB_000adcc0;
      }
    }
    if ((tmp_i5 != *(int *)(g_unk_01047b00 + 0x158)) && (*(int *)(g_unk_01047b00 + 0x158) != 3))
    goto LAB_000adcdf;
    tmp_i5 = SkillNumForClass(*(uint32_t *)(cgs + tmp_i6 * 0x1a4 + 0x94b8));
    CG_DrawPic(local_80,(float)param_2,0x41500000,0x41500000,
               *(uint32_t *)(cgs + tmp_i5 * 4 + 0x11084));
    CG_DrawStringExt((int)ROUND(local_80 + 14.0),param_2 + -1,tmp_i6 * 0x1a4 + 0x10f9274,&local_2c,0,
                     1,6,0xc,local_74);
  }
  param_2 = param_2 + -1;
  local_80 = (float)local_70 + (local_80 - 14.0);
  if (1 < tmp_b11) {
    local_80 = local_80 - 14.0;
  }
  tmp_i5 = tmp_i6 * 0x1a4;
  if (*(int *)(cgs + tmp_i5 + 0x9494) == 3) {
LAB_000ae27a:
    if (!tmp_b3) {
      local_80 = local_80 + 16.0;
    }
    if (param_3[2] == -1) {
      tmp_pc7 = "^3CONNECTING";
    }
    else {
      tmp_i6 = tmp_i6 * 0x1a4;
      if (*(int *)(cgs + tmp_i6 + 0x95ac) == 0) {
        if (*(int *)(cgs + tmp_i6 + 0x95a8) == 0) {
          tmp_pc7 = "^3SPECTATOR";
        }
        else {
          tmp_pc7 = "^3SHOUTCASTER";
        }
      }
      else {
        if (*(int *)(cgs + tmp_i6 + 0x95a8) == 0) {
          tmp_pc7 = "^3SPECTATOR";
        }
        else {
          tmp_pc7 = "^3SHOUTCASTER";
        }
        tmp_pc7 = (char *)va("^5TV^7|^3%s",tmp_pc7 + 2);
      }
    }
    tmp_u8 = CG_DrawStrlen(tmp_pc7);
    tmp_f1 = (local_80 + 146.0) - (float)(int)(~tmp_u8 + tmp_u8 * 8);
    goto LAB_000ae680;
  }
  tmp_u4 = va(&g_unk_0011cbcf,param_3[8],param_3[9]);
  CG_DrawStringExt(param_1 + 0x82,param_2,tmp_u4,&local_2c,0,1,6,0xc,0);
  if (param_5 == 0) {
    if (*(int *)(cgs + tmp_i5 + 0x9494) == 3) goto LAB_000ae27a;
    local_80 = local_80 + 24.0;
  }
  else if (*(int *)(cgs + tmp_i5 + 0x9494) == 3) goto LAB_000ae27a;
  local_80 = local_80 + 50.0;
  if (!tmp_b3) {
    local_80 = local_80 + 16.0;
  }
  tmp_u4 = va("^7%3i",param_3[1]);
  CG_DrawStringExt((int)ROUND(local_80 - 8.0),param_2,tmp_u4,&local_2c,0,1,6,0xc,0);
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 5) {
    tmp_f1 = 56.0;
  }
  else {
    tmp_f1 = 36.0;
  }
  local_80 = local_80 + tmp_f1;
  if (param_5 != 0) {
    local_80 = local_80 + 8.0;
  }
  if ((*(byte *)(param_3 + 6) & 2) == 0) {
    tmp_i6 = param_3[2];
    if (tmp_i6 == -1) {
      tmp_pc7 = "^2CONN.^7";
      goto LAB_000ae4f5;
    }
    tmp_u4 = pingColor(tmp_i6);
    tmp_u4 = va("^%i%4i^7",tmp_u4,tmp_i6);
    CG_DrawStringExt((int)ROUND(local_80),param_2,tmp_u4,&local_2c,0,1,6,0xc,0);
  }
  else {
    tmp_pc7 = "^7 BOT";
LAB_000ae4f5:
    CG_DrawStringExt((int)ROUND(local_80),param_2,tmp_pc7,&local_2c,0,1,6,0xc,0);
  }
  if ((param_5 != 0) && (tmp_f1 = (local_80 + 40.0) - 8.0, GHIDRA_FIELD(cg_gameType, 12, 4) != 5)) {
    if (param_3[7] < 0) {
      tmp_pc7 = "^7 -";
LAB_000ae680:
      CG_DrawStringExt((int)ROUND(tmp_f1),param_2,tmp_pc7,&local_2c,0,1,6,0xc,0);
      return;
    }
    tmp_u4 = va(&g_unk_0011cc08,param_3[7]);
    CG_DrawStringExt((int)ROUND(tmp_f1),param_2,tmp_u4,&local_2c,0,1,6,0xc,0);
  }
  return;
}

void WM_TimeToString(float param_1)
{
  int tmp_i1;
  
  tmp_i1 = (int)ROUND(param_1 / 1000.0) % 0x3c;
  va("%i:%i%i",(int)ROUND(param_1 / 1000.0) / 0x3c,tmp_i1 / 10,tmp_i1 % 10);
  return;
}

void CG_DrawBottom_NoScale
               (uint32_t param_1,float param_2,uint32_t param_3,float param_4,float param_5)

{
  CG_AdjustFrom640(&param_1,&param_2,&param_3,&param_4);
  trap_R_DrawStretchPic(param_1,(param_2 + param_4) - param_5,param_3,param_5,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4))
  ;
  return;
}

uint32_t cf_draw(float param_1,float param_2,uint32_t param_3,int param_4)
{
  uint tmp_u1;
  float tmp_f2;
  float tmp_f3;
  
  tmp_u1 = *(uint *)(ClientFlags + param_4 * 4);
  if ((tmp_u1 < 0xff) && (GHIDRA_FIELD(cg_countryflags, 12, 4) != 0)) {
    tmp_f3 = (float)((tmp_u1 & 0xf) << 5);
    tmp_f2 = ROUND((float)(int)tmp_u1 * 32.0 * 0.001953125) * 32.0;
    CG_DrawPicST(param_1 - 1.0,param_2 + 3.0,0x42000000,0x42000000,tmp_f3 * 0.001953125,
                 tmp_f2 * 0.001953125,(tmp_f3 + 32.0) * 0.001953125,(tmp_f2 + 32.0) * 0.001953125,
                 GHIDRA_FIELD(cgs, 131908, 4));
    return 1;
  }
  return 0;
}

int WM_DrawObjectives(int param_1,int param_2,int param_3)
{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint32_t tmp_u6;
  long tmp_l7;
  uint8_t *tmp_pu8;
  char *tmp_pc9;
  int tmp_i10;
  int tmp_i11;
  int local_34;
  
  if (*(int *)(g_unk_01047b00 + 0x30) == 5) {
    param_2 = param_2 + 0x30;
    tmp_u6 = CG_ConfigString(0xe);
    tmp_pc9 = (char *)Info_ValueForKey(tmp_u6,"w");
    tmp_l7 = strtol(tmp_pc9,(char **)0x0,10);
    if (tmp_l7 == -1) {
      tmp_i11 = 0;
      tmp_i5 = 0;
    }
    else {
      tmp_l7 = strtol(tmp_pc9,(char **)0x0,10);
      tmp_i5 = GHIDRA_FIELD(cgs, 132400, 4);
      tmp_i11 = GHIDRA_FIELD(cgs, 132404, 4);
      if (tmp_l7 != 0) {
        tmp_i5 = GHIDRA_FIELD(cgs, 132392, 4);
        tmp_i11 = GHIDRA_FIELD(cgs, 132396, 4);
      }
    }
    if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
      tmp_u6 = va("%s^7 wins!",GHIDRA_FIELD(cgs, 33787764, 4) * 0x1a4 + 0x10f9274);
      tmp_i10 = CG_Text_Width_Ext(tmp_u6,0x3eb33333,0,0x110afec);
      CG_Text_Paint_Ext(320.0 - (float)tmp_i10 * 0.5,0x41f00000,0x3eb33333,0x3eb33333,&colorWhite,
                        tmp_u6,0,0,0,0x110afec);
      if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
        return param_2;
      }
    }
    if (tmp_i5 != 0) {
      CG_DrawPic(0x438eb333,0x40400000,0x428a6666,0x42340000,tmp_i5);
    }
    if (tmp_i11 == 0) {
      return param_2;
    }
    CG_DrawPic(0x43533333,0x41200000,0x42820000,0x4204cccd,tmp_i11);
    CG_DrawPic(0x43b3cccd,0x41200000,0x42820000,0x4204cccd,GHIDRA_FIELD(cgs, 132408, 4));
    return param_2;
  }
  tmp_f2 = (float)(param_3 + 5);
  tmp_f3 = (float)(param_2 + -2);
  tmp_f4 = (float)(param_1 + -5);
  CG_FillRect(tmp_f4,tmp_f3,tmp_f2,0x41880000,clrUiBack);
  CG_FillRect(tmp_f4,tmp_f3,tmp_f2,0x41880000,clrUiBar);
  CG_DrawRect_FixedBorder(tmp_f4,tmp_f3,tmp_f2,0x41880000,1,&colorBlack);
  if ((float)GHIDRA_FIELD(cgs, 27396, 4) <= 0.0) {
    if (GHIDRA_FIELD(cgs, 33525356, 4) != 0) goto LAB_000aec0d;
    tmp_i5 = 0;
    tmp_i10 = 0;
    tmp_i11 = 0;
LAB_000af10e:
    tmp_u6 = va("%i:%i%i",tmp_i11,tmp_i10,tmp_i5);
    tmp_pc9 = (char *)va("MISSION TIME:   %s",tmp_u6);
  }
  else if (GHIDRA_FIELD(cgs, 33525356, 4) == 0) {
    tmp_pc9 = "MISSION TIME:SUDDEN DEATH";
    tmp_i5 = (int)ROUND((float)GHIDRA_FIELD(cgs, 27396, 4) * 60.0 * 1000.0 - (float)(g_unk_010906e0 - GHIDRA_FIELD(cgs, 28480, 4)))
    ;
    if (-1 < tmp_i5) {
      tmp_i5 = (int)ROUND((float)tmp_i5 / 1000.0);
      tmp_i11 = tmp_i5 / 0x3c;
      tmp_i5 = tmp_i5 % 0x3c;
      tmp_i10 = tmp_i5 / 10;
      tmp_i5 = tmp_i5 % 10;
      goto LAB_000af10e;
    }
  }
  else {
LAB_000aec0d:
    tmp_pc9 = "MISSION TIME:WARMUP";
  }
  tmp_f2 = (float)(param_2 + 0xd);
  CG_Text_Paint_Ext((float)param_1,tmp_f2,0x3e800000,0x3e800000,HUD_Text,tmp_pc9,0,0,0,0x1100f64);
  if (GHIDRA_FIELD(cgs, 27388, 4) == 5) {
LAB_000aee20:
    tmp_pu8 = (uint8_t *)
             va("ROUND %i  SCORE %i-%i",GHIDRA_FIELD(cgs, 33525344, 4) + 1,g_unk_010aabf4,g_unk_010aabf0);
LAB_000aee4f:
    local_34 = CG_Text_Width_Ext(tmp_pu8,0x3e800000,0,0x1100f64);
  }
  else {
    if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) - 1U < 2) {
      tmp_i5 = CG_CalculateReinfTime(0);
      if (tmp_i5 * 1000 != 0) {
        tmp_i11 = (int)ROUND((float)(tmp_i5 * 1000) / 1000.0);
        tmp_i5 = tmp_i11 % 0x3c;
        tmp_u6 = va("%i:%i%i",tmp_i11 / 0x3c,tmp_i5 / 10,tmp_i5 % 10);
        tmp_u6 = va("REINFORCE TIME: %s",tmp_u6);
        tmp_i5 = CG_Text_Width_Ext(tmp_u6,0x3e800000,0,0x1100f64);
        CG_Text_Paint_Ext((float)(0x26c - tmp_i5),tmp_f2,0x3e800000,0x3e800000,HUD_Text,tmp_u6,0,0,0,
                          0x1100f64);
      }
      if (GHIDRA_FIELD(cgs, 27388, 4) == 3) goto LAB_000af140;
      if (GHIDRA_FIELD(cgs, 27388, 4) == 5) goto LAB_000aee20;
    }
    else if (GHIDRA_FIELD(cgs, 27388, 4) == 3) {
LAB_000af140:
      tmp_pu8 = (uint8_t *)va("STOPWATCH ROUND %i",GHIDRA_FIELD(cgs, 33525344, 4) + 1);
      goto LAB_000aee4f;
    }
    if (GHIDRA_FIELD(cgs, 27388, 4) != 4) {
      if (GHIDRA_FIELD(cgs, 27388, 4) != 6) {
        if (GHIDRA_FIELD(cgs, 27388, 4) == 7) {
          tmp_b1 = cgs[0x20390d8] & 8;
        }
        else {
          if (GHIDRA_FIELD(cgs, 27388, 4) != 8) goto LAB_000aecd0;
          tmp_b1 = cgs[0x20390dd] & 0x40;
        }
        if (tmp_b1 == 0) goto LAB_000aecd0;
      }
      tmp_pu8 = &g_unk_0011d841;
      if (GHIDRA_FIELD(cgs, 33787488, 4) != 0) {
        tmp_pu8 = (uint8_t *)va("MAP %i of %i",GHIDRA_FIELD(cgs, 33787484, 4) + 1,GHIDRA_FIELD(cgs, 33787488, 4));
      }
      goto LAB_000aee4f;
    }
    tmp_pu8 = (uint8_t *)va("MAP %i of %i",GHIDRA_FIELD(cgs, 33525616, 4) + 1,GHIDRA_FIELD(cgs, 33571584, 4));
    local_34 = CG_Text_Width_Ext(tmp_pu8,0x3e800000,0,0x1100f64);
  }
  CG_Text_Paint_Ext((float)(param_1 + 300) - (float)local_34 * 0.5,tmp_f2,0x3e800000,0x3e800000,
                    HUD_Text,tmp_pu8,0,0,0,0x1100f64);
LAB_000aecd0:
  return param_2 + 0x20;
}

void WM_DrawClientScore(int param_1,int param_2,int *param_3,uint32_t param_4,float param_5,
                       int param_6)

{
  float tmp_f1;
  uint tmp_u2;
  float tmp_f3;
  bool tmp_b4;
  char tmp_c5;
  uint32_t tmp_u6;
  int tmp_i7;
  char *tmp_pc8;
  int tmp_i9;
  uint32_t tmp_u10;
  char tmp_c11;
  float local_70;
  int local_60;
  uint32_t local_58;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  
  if (0x1c5 < param_2) {
    return;
  }
  tmp_i7 = *param_3;
  if (tmp_i7 == *(int *)(g_unk_01047b00 + 0xcc)) {
    local_20 = param_5 * 0.3;
    local_2c = 0x3f000000;
    local_28 = 0x3f000000;
    local_24 = 0x3e4ccccd;
    CG_FillRect((float)(param_1 + -5),(float)param_2,0x438e8000,0x41700000,&local_2c);
  }
  local_70 = (float)param_1;
  local_2c = 0x3f800000;
  local_28 = 0x3f800000;
  local_24 = 0x3f800000;
  local_20 = param_5;
  if ((param_3[2] == 999) || (param_3[2] == -1)) {
    local_58 = 0x10;
    tmp_u6 = 0xe;
    tmp_b4 = false;
    tmp_u10 = 0x12;
  }
  else {
    tmp_u2 = *(uint *)(ClientFlags + *(int *)(cgs + tmp_i7 * 0x1a4 + 0x9410) * 4);
    if ((tmp_u2 < 0xff) && (GHIDRA_FIELD(cg_countryflags, 12, 4) != 0)) {
      tmp_f3 = (float)((tmp_u2 & 0xf) << 5);
      tmp_f1 = ROUND((float)(int)tmp_u2 * 32.0 * 0.001953125) * 32.0;
      CG_DrawPicST((local_70 - 10.0) - 1.0,(float)(param_2 + -10) + 3.0,0x42000000,0x42000000,
                   tmp_f3 * 0.001953125,tmp_f1 * 0.001953125,(tmp_f3 + 32.0) * 0.001953125,
                   (tmp_f1 + 32.0) * 0.001953125,GHIDRA_FIELD(cgs, 131908, 4));
      tmp_b4 = true;
      tmp_u6 = 0xc;
      tmp_u10 = 0x10;
      local_58 = 0xe;
      local_70 = local_70 + 16.0;
    }
    else {
      local_58 = 0x10;
      tmp_u6 = 0xe;
      tmp_u10 = 0x12;
      tmp_b4 = false;
    }
  }
  tmp_c11 = (*(byte *)(param_3 + 6) & 4) != 0;
  if ((bool)tmp_c11) {
    CG_DrawPic(local_70,(float)(param_2 + 2),0x41400000,0x41400000,GHIDRA_FIELD(cgs, 67964, 4));
    local_70 = local_70 + 12.0;
    local_60 = 0x7a;
    tmp_c5 = '\x02';
    tmp_u10 = local_58;
    local_58 = tmp_u6;
  }
  else {
    local_60 = 0x86;
    tmp_c5 = '\x01';
  }
  tmp_i9 = *(int *)(cgs + tmp_i7 * 0x1a4 + 0x9494);
  if (tmp_i9 == 3) {
LAB_000af469:
    tmp_i9 = tmp_i7 * 0x1a4 + 0x10f9274;
    CG_DrawStringExt((int)ROUND(local_70),param_2 + 1,tmp_i9,&local_2c,0,1,7,0xe,tmp_u10);
  }
  else {
    tmp_u6 = GHIDRA_FIELD(cgs, 67992, 4);
    if (((*(uint *)(cgs + tmp_i7 * 0x1a4 + 0x94b0) & 0x60) == 0) &&
       (((*(byte *)(param_3 + 6) & 3) == 0 || (tmp_u6 = GHIDRA_FIELD(cgs, 131760, 4), GHIDRA_FIELD(cgs, 33525356, 4) == 0)))) {
      tmp_u6 = GHIDRA_FIELD(cgs, 67972, 4);
      if (tmp_i9 == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494)) {
        if ((*(uint *)(cgs + tmp_i7 * 0x1a4 + 0x94b0) & 0x80) != 0) {
          CG_DrawPic(local_70,(float)(param_2 + 2),0x41400000,0x41400000,GHIDRA_FIELD(cgs, 68900, 4));
          goto LAB_000afd2a;
        }
        if (((param_3[7] == -2) || (*(int *)(cgs + *param_3 * 0x1a4 + 0x94a8) == -1)) ||
           (tmp_u6 = GHIDRA_FIELD(cgs, 69808, 4), *(int *)(cgs + *param_3 * 0x1a4 + 0x94a8) == 0))
        goto LAB_000afb52;
      }
      else if (param_3[7] == -2) {
LAB_000afb52:
        CG_DrawPic(local_70,(float)(param_2 + 2),0x41400000,0x41400000,tmp_u6);
        goto LAB_000afd2a;
      }
    }
    else {
      CG_DrawPic(local_70,(float)(param_2 + 2),0x41400000,0x41400000,tmp_u6);
LAB_000afd2a:
      local_70 = local_70 + 12.0;
      tmp_i9 = *(int *)(cgs + tmp_i7 * 0x1a4 + 0x9494);
      tmp_u10 = local_58;
      tmp_c11 = tmp_c5;
      if (tmp_i9 == 3) {
        local_60 = 0x7a;
        goto LAB_000af469;
      }
      local_60 = 0x7a;
    }
    if ((tmp_i9 != *(int *)(g_unk_01047b00 + 0x158)) && (*(int *)(g_unk_01047b00 + 0x158) != 3))
    goto LAB_000af469;
    tmp_i9 = SkillNumForClass(*(uint32_t *)(cgs + tmp_i7 * 0x1a4 + 0x94b8));
    CG_DrawPic(local_70,(float)(param_2 + 2),0x41500000,0x41500000,
               *(uint32_t *)(cgs + tmp_i9 * 4 + 0x11084));
    tmp_i9 = tmp_i7 * 0x1a4 + 0x10f9274;
    CG_DrawStringExt((int)ROUND(local_70 + 14.0),param_2 + 1,tmp_i9,&local_2c,0,1,7,0xe,tmp_u10);
  }
  local_70 = local_70 - 14.0;
  CG_DrawStrlen(tmp_i9);
  tmp_i9 = *(int *)(cgs + tmp_i7 * 0x1a4 + 0x9494);
  local_70 = (float)local_60 + local_70;
  if (tmp_i9 != 3) {
    tmp_u10 = va(&g_unk_0011cbcf,param_3[8],param_3[9]);
    CG_DrawStringExt(param_1 + 0x84,param_2 + 1,tmp_u10,&local_2c,0,1,7,0xe,0);
    tmp_i9 = *(int *)(cgs + tmp_i7 * 0x1a4 + 0x9494);
  }
  if (tmp_c11 == '\x02') {
    local_70 = local_70 - 12.0;
  }
  if (param_6 == 0) {
    if (tmp_i9 == 3) {
LAB_000af7f9:
      if (!tmp_b4) {
        local_70 = local_70 + 16.0;
      }
      if (param_3[2] == -1) {
        tmp_pc8 = "^3CONNECTING";
      }
      else {
        tmp_i7 = tmp_i7 * 0x1a4;
        if (*(int *)(cgs + tmp_i7 + 0x95ac) == 0) {
          if (*(int *)(cgs + tmp_i7 + 0x95a8) == 0) {
            tmp_pc8 = "^3SPECTATOR";
          }
          else {
            tmp_pc8 = "^3SHOUTCASTER";
          }
        }
        else {
          if (*(int *)(cgs + tmp_i7 + 0x95a8) == 0) {
            tmp_pc8 = "^3SPECTATOR";
          }
          else {
            tmp_pc8 = "^3SHOUTCASTER";
          }
          tmp_pc8 = (char *)va("^5TV^7|^3%s",tmp_pc8 + 2);
        }
      }
      tmp_i7 = CG_DrawStrlen(tmp_pc8);
      tmp_f1 = (local_70 + 146.0) - (float)(tmp_i7 * 8 + -1);
      goto LAB_000afe25;
    }
    local_70 = local_70 + 24.0;
  }
  else if (tmp_i9 == 3) goto LAB_000af7f9;
  local_70 = local_70 + 50.0;
  if (!tmp_b4) {
    local_70 = local_70 + 16.0;
  }
  tmp_u10 = va("^7%3i",param_3[1]);
  CG_DrawStringExt((int)ROUND(local_70 - 10.0),param_2,tmp_u10,&local_2c,0,1,7,0xe,0);
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 5) {
    tmp_f1 = 56.0;
  }
  else {
    tmp_f1 = 36.0;
  }
  local_70 = local_70 + tmp_f1;
  if (param_6 == 0) {
    if ((*(byte *)(param_3 + 6) & 2) == 0) goto LAB_000af68a;
LAB_000af870:
    tmp_pc8 = "^7 BOT";
LAB_000afa2d:
    CG_DrawStringExt((int)ROUND(local_70),param_2,tmp_pc8,&local_2c,0,1,7,0xe,0);
  }
  else {
    local_70 = local_70 + 8.0;
    if ((*(byte *)(param_3 + 6) & 2) != 0) goto LAB_000af870;
LAB_000af68a:
    tmp_i7 = param_3[2];
    if (tmp_i7 == -1) {
      tmp_pc8 = "^2CONN.^7";
      goto LAB_000afa2d;
    }
    tmp_u10 = pingColor(tmp_i7);
    tmp_u10 = va("^%i%4i^7",tmp_u10,tmp_i7);
    CG_DrawStringExt((int)ROUND(local_70),param_2,tmp_u10,&local_2c,0,1,7,0xe,0);
  }
  if ((param_6 != 0) && (tmp_f1 = (local_70 + 40.0) - 8.0, GHIDRA_FIELD(cg_gameType, 12, 4) != 5)) {
    if (param_3[7] < 0) {
      tmp_pc8 = " -";
LAB_000afe25:
      CG_DrawStringExt((int)ROUND(tmp_f1),param_2,tmp_pc8,&local_2c,0,1,7,0xe,0);
      return;
    }
    tmp_u10 = va(&g_unk_0011cc0a,param_3[7]);
    CG_DrawStringExt((int)ROUND(tmp_f1),param_2,tmp_u10,&local_2c,0,1,7,0xe,0);
  }
  return;
}

int WM_TeamScoreboard(int param_1,int param_2,int param_3,float param_4,int param_5,int param_6)
{
  float tmp_f1;
  bool tmp_b2;
  bool tmp_b3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  int tmp_i7;
  char *tmp_pc8;
  int tmp_i9;
  int *tmp_pi10;
  long tmp_l11;
  uint32_t tmp_u12;
  int tmp_i13;
  size_t tmp_s14;
  uint tmp_u15;
  int local_19c;
  int local_18c;
  float local_188;
  float local_16c;
  float local_168;
  uint32_t local_164;
  float local_160;
  float local_15c;
  float local_158;
  uint32_t local_154;
  float local_150;
  float local_14c;
  float local_148;
  uint32_t local_144;
  float local_140 [5];
  uint32_t local_12c;
  uint32_t local_128;
  uint32_t local_124;
  uint32_t local_120;
  size_t local_11c [66];
  uint32_t uStack_14;
  
  tmp_u12 = CachedServerInfo;
  uStack_14 = 0xaffd9;
  local_12c = 0x3f19999a;
  local_128 = 0x3f19999a;
  local_124 = 0x3f19999a;
  local_120 = 0x3f800000;
  tmp_pc8 = (char *)Info_ValueForKey(CachedServerInfo,"g_maxlives");
  if ((((tmp_pc8 == (char *)0x0) || (*tmp_pc8 == '\0')) ||
      (tmp_l11 = strtol(tmp_pc8,(char **)0x0,10), 0 < tmp_l11)) ||
     (((tmp_pc8 = (char *)Info_ValueForKey(tmp_u12,"g_alliedmaxlives"), tmp_pc8 != (char *)0x0 &&
       (*tmp_pc8 != '\0')) && (tmp_l11 = strtol(tmp_pc8,(char **)0x0,10), 0 < tmp_l11)))) {
    tmp_b2 = true;
  }
  else {
    tmp_pc8 = (char *)Info_ValueForKey(tmp_u12,"g_axismaxlives");
    tmp_b2 = false;
    if ((tmp_pc8 != (char *)0x0) && (*tmp_pc8 != '\0')) {
      tmp_l11 = strtol(tmp_pc8,(char **)0x0,10);
      tmp_b2 = 0 < tmp_l11;
    }
  }
  tmp_f4 = (float)(param_2 + -2);
  tmp_f5 = (float)(param_1 + -5);
  CG_FillRect(tmp_f5,tmp_f4,0x438e8000,0x41a80000,clrUiBack);
  CG_FillRect(tmp_f5,tmp_f4,0x438e8000,0x41a80000,clrUiBar);
  local_140[1] = 0.0;
  local_140[4] = param_4;
  local_140[2] = 0.0;
  local_140[3] = 0.0;
  CG_DrawRect_FixedBorder(tmp_f5,tmp_f4,0x438e8000,0x41a80000,1,&colorBlack);
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 5) {
    if (param_3 == 1) {
      tmp_u12 = va("^1AXIS [%d] (%d PLAYERS)",g_unk_01091e8c,g_unk_01091e98);
      if (g_unk_010aabec == 1) {
        tmp_pc8 = "FIRST BLOOD";
      }
      else {
        tmp_pc8 = "";
      }
      tmp_u12 = va(&g_unk_0011cccd,tmp_u12,tmp_pc8);
      CG_Text_Paint_Ext((float)param_1,(float)(param_2 + 0xd),0x3e800000,0x3e800000,&local_12c,
                        tmp_u12,0,0,0,0x1100f64);
    }
    else if (param_3 == 2) {
      tmp_u12 = va("^4ALLIES [%d] (%d PLAYERS)",g_unk_01091e90,g_unk_01091e9c);
      if (g_unk_010aabec == 2) {
        tmp_pc8 = "FIRST BLOOD";
      }
      else {
        tmp_pc8 = "";
      }
      tmp_u12 = va(&g_unk_0011cccd,tmp_u12,tmp_pc8);
      CG_Text_Paint_Ext((float)param_1,(float)(param_2 + 0xd),0x3e800000,0x3e800000,&local_12c,
                        tmp_u12,0,0,0,0x1100f64);
    }
  }
  else if (param_3 == 1) {
    tmp_u12 = va("^1AXIS [%d] (%d PLAYERS)",g_unk_01091e8c,g_unk_01091e98);
    CG_Text_Paint_Ext((float)param_1,(float)(param_2 + 0xd),0x3e800000,0x3e800000,&local_12c,tmp_u12,
                      0,0,0,0x1100f64);
  }
  else if (param_3 == 2) {
    tmp_u12 = va("^4ALLIES [%d] (%d PLAYERS)",g_unk_01091e90,g_unk_01091e9c);
    CG_Text_Paint_Ext((float)param_1,(float)(param_2 + 0xd),0x3e800000,0x3e800000,&local_12c,tmp_u12,
                      0,0,0,0x1100f64);
  }
  local_188 = (float)param_1;
  tmp_i9 = param_2 + 0x13;
  (&g_unk_01047ac4)[param_3 + 0x128f4] = 0;
  if ((int)g_unk_01091e84 < 1) {
    tmp_i13 = 0;
  }
  else {
    tmp_pi10 = &g_unk_01091ea4;
    tmp_i7 = g_unk_01091e84 * 10;
    tmp_i13 = 0;
    do {
      while (*(int *)(cgs + *tmp_pi10 * 0x1a4 + 0x9494) != param_3) {
        tmp_pi10 = tmp_pi10 + 10;
        if (tmp_pi10 == &g_unk_01091ea4 + tmp_i7) goto LAB_000b01f0;
      }
      tmp_pi10 = tmp_pi10 + 10;
      tmp_i13 = tmp_i13 + 1;
      (&g_unk_01047ac4)[param_3 + 0x128f4] = tmp_i13;
    } while (tmp_pi10 != &g_unk_01091ea4 + tmp_i7);
  }
LAB_000b01f0:
  tmp_b3 = param_5 < tmp_i13;
  if (tmp_b3) {
    param_5 = param_6;
  }
  tmp_f4 = (float)tmp_i9;
  CG_FillRect(tmp_f5,tmp_f4,0x438e8000,0x41900000,clrUiBack);
  trap_R_SetColor(&colorBlack);
  local_164 = 0x438e8000;
  local_160 = 18.0;
  local_16c = tmp_f5;
  local_168 = tmp_f4;
  CG_AdjustFrom640(&local_16c,&local_168,&local_164,&local_160);
  trap_R_DrawStretchPic
            (local_16c,(local_168 + local_160) - 1.0,local_164,0x3f800000,0,0,0,0,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_SetColor(0);
  CG_DrawSmallString((int)ROUND(local_188),tmp_i9,"Name",param_4);
  if (tmp_b3) {
    CG_DrawSmallString(param_1 + 0x8c,tmp_i9,&g_unk_0011ccf0,param_4);
  }
  else {
    CG_DrawSmallString(param_1 + 0x92,tmp_i9,&g_unk_0011ccf0,param_4);
  }
  tmp_f6 = local_188 + 134.0 + 50.0;
  if (tmp_b2 == false) {
    tmp_f6 = tmp_f6 + 22.0;
  }
  if (GHIDRA_FIELD(cgs, 27388, 4) == 5) {
    CG_DrawSmallString((int)ROUND(tmp_f6 - 6.0),tmp_i9,"Score",param_4);
    tmp_f1 = 56.0;
  }
  else {
    CG_DrawSmallString((int)ROUND(tmp_f6 + 8.0),tmp_i9,"XP",param_4);
    tmp_f1 = 36.0;
  }
  if (tmp_b2 == false) {
    CG_DrawSmallString((int)ROUND(tmp_f6 + tmp_f1),tmp_i9,"Ping",param_4);
  }
  else {
    tmp_f6 = tmp_f6 + tmp_f1 + 8.0;
    CG_DrawSmallString((int)ROUND(tmp_f6),tmp_i9,"Ping",param_4);
    if (GHIDRA_FIELD(cgs, 27388, 4) != 5) {
      tmp_u12 = GHIDRA_FIELD(cgs, 67852, 4);
      if (param_3 != 2) {
        tmp_u12 = GHIDRA_FIELD(cgs, 67848, 4);
      }
      CG_DrawPicST(((tmp_f6 + 40.0) - 8.0) + 2.0,tmp_f4,0x41800000,0x41800000,0,0,0x3f000000,
                   0x3f800000,tmp_u12);
    }
  }
  local_19c = param_2 + 0x25;
  tmp_f4 = (float)local_19c;
  if (0 < param_5) {
    tmp_u15 = 0;
    tmp_f6 = tmp_f4;
    while( true ) {
      if ((tmp_u15 & 1) == 0) {
        local_140[1] = 0.3137255;
        local_140[2] = 0.3137255;
        local_140[3] = 0.3137255;
      }
      else {
        local_140[1] = 0.0;
        local_140[2] = 0.0;
        local_140[3] = 0.0;
      }
      local_140[4] = param_4 * 0.3;
      if (tmp_b3) {
        CG_FillRect(tmp_f5,tmp_f6,0x438e8000,0x41400000,local_140 + 1);
        trap_R_SetColor(&colorBlack);
        local_154 = 0x438e8000;
        local_150 = 12.0;
        local_15c = tmp_f5;
        local_158 = tmp_f6;
        CG_AdjustFrom640(&local_15c,&local_158,&local_154,&local_150);
        trap_R_DrawStretchPic
                  (local_15c,(local_158 + local_150) - 1.0,local_154,0x3f800000,0,0,0,0,
                   GHIDRA_FIELD(cgs, 67836, 4));
        trap_R_SetColor(0);
        local_19c = local_19c + 0xc;
      }
      else {
        CG_FillRect(tmp_f5,tmp_f6,0x438e8000,0x41800000,local_140 + 1);
        trap_R_SetColor(&colorBlack);
        local_144 = 0x438e8000;
        local_140[0] = 16.0;
        local_14c = tmp_f5;
        local_148 = tmp_f6;
        CG_AdjustFrom640(&local_14c,&local_148,&local_144,local_140);
        trap_R_DrawStretchPic
                  (local_14c,(local_148 + local_140[0]) - 1.0,local_144,0x3f800000,0,0,0,0,
                   GHIDRA_FIELD(cgs, 67836, 4));
        trap_R_SetColor(0);
        local_19c = local_19c + 0x10;
      }
      if (tmp_u15 + 1 == param_5) break;
      tmp_u15 = tmp_u15 + 1;
      tmp_f6 = (float)local_19c;
    }
  }
  local_140[1] = 1.0;
  local_140[2] = 1.0;
  local_140[3] = 1.0;
  local_18c = (int)ROUND(tmp_f4);
  local_140[4] = param_4;
  if ((int)g_unk_01091e84 < 1) {
    if (g_unk_010928b8 != 1) {
      tmp_s14 = g_unk_01091e84;
      if (tmp_b3) {
        return local_18c + 0xc;
      }
      goto LAB_000b0930;
    }
LAB_000b0ef6:
    qsort(local_11c,g_unk_01091e84,4,CG_SortPlayersByKD);
  }
  else {
    tmp_s14 = 0;
    do {
      local_11c[tmp_s14] = tmp_s14;
      tmp_s14 = tmp_s14 + 1;
    } while (tmp_s14 != g_unk_01091e84);
    if (g_unk_010928b8 == 1) goto LAB_000b0ef6;
  }
  tmp_s14 = g_unk_01091e84;
  if ((0 < (int)g_unk_01091e84) && (0 < param_5)) {
    local_19c = 0;
    if (!tmp_b3) {
      tmp_i9 = 0;
      do {
        if (*(int *)(cgs + (&g_unk_01091ea4)[local_11c[tmp_i9] * 10] * 0x1a4 + 0x9494) == param_3) {
          WM_DrawClientScore(param_1,local_18c,&g_unk_01091ea4 + local_11c[tmp_i9] * 10,local_140 + 1,
                             param_4,tmp_b2);
          local_18c = local_18c + 0x10;
          local_19c = local_19c + 1;
          tmp_s14 = g_unk_01091e84;
          if ((int)g_unk_01091e84 <= tmp_i9 + 1) break;
        }
        else if ((int)tmp_s14 <= tmp_i9 + 1) break;
        tmp_i9 = tmp_i9 + 1;
      } while (local_19c < param_5);
      goto LAB_000b0930;
    }
    tmp_i9 = 0;
    do {
      if (*(int *)(cgs + (&g_unk_01091ea4)[local_11c[tmp_i9] * 10] * 0x1a4 + 0x9494) == param_3) {
        WM_DrawClientScore_Small_isra_1(&g_unk_01091ea4 + local_11c[tmp_i9] * 10,param_4,tmp_b2);
        local_18c = local_18c + 0xc;
        local_19c = local_19c + 1;
        tmp_s14 = g_unk_01091e84;
      }
      tmp_i9 = tmp_i9 + 1;
    } while ((tmp_i9 < (int)tmp_s14) && (local_19c < param_5));
  }
  if (tmp_b3) {
    local_19c = local_18c + 0xc;
    if ((int)tmp_s14 < 1) {
      return local_19c;
    }
    tmp_pi10 = &g_unk_01091ea4;
    if (param_3 != 1) {
      tmp_u15 = 1;
      if (param_3 == 2) {
        do {
          if ((*(int *)(cgs + *tmp_pi10 * 0x1a4 + 0x9494) == 3) && ((tmp_u15 & 1) == 0)) {
            WM_DrawClientScore_Small_isra_1(tmp_pi10,param_4,0);
            local_19c = local_19c + 0xc;
            tmp_s14 = g_unk_01091e84;
          }
          tmp_pi10 = tmp_pi10 + 10;
          tmp_b2 = (int)tmp_u15 < (int)tmp_s14;
          tmp_u15 = tmp_u15 + 1;
        } while (tmp_b2);
        return local_19c;
      }
      do {
        if (*(int *)(cgs + *tmp_pi10 * 0x1a4 + 0x9494) == 3) {
          WM_DrawClientScore_Small_isra_1(tmp_pi10,param_4,0);
          local_19c = local_19c + 0xc;
          tmp_s14 = g_unk_01091e84;
        }
        tmp_pi10 = tmp_pi10 + 10;
        tmp_b2 = (int)tmp_u15 < (int)tmp_s14;
        tmp_u15 = tmp_u15 + 1;
      } while (tmp_b2);
      return local_19c;
    }
    tmp_u15 = 1;
    do {
      if ((*(int *)(cgs + *tmp_pi10 * 0x1a4 + 0x9494) == 3) && ((tmp_u15 & 1) != 0)) {
        WM_DrawClientScore_Small_isra_1(tmp_pi10,param_4,0);
        local_19c = local_19c + 0xc;
        tmp_s14 = g_unk_01091e84;
      }
      tmp_pi10 = tmp_pi10 + 10;
      tmp_b2 = (int)tmp_u15 < (int)tmp_s14;
      tmp_u15 = tmp_u15 + 1;
    } while (tmp_b2);
    return local_19c;
  }
LAB_000b0930:
  local_19c = local_18c + 0x10;
  if (0 < (int)tmp_s14) {
    if (param_3 == 1) {
      tmp_pi10 = &g_unk_01091ea4;
      tmp_u15 = 1;
      do {
        if ((*(int *)(cgs + *tmp_pi10 * 0x1a4 + 0x9494) == 3) && ((tmp_u15 & 1) != 0)) {
          WM_DrawClientScore(param_1,local_19c,tmp_pi10,local_140 + 1,param_4,0);
          local_19c = local_19c + 0x10;
          tmp_s14 = g_unk_01091e84;
        }
        tmp_pi10 = tmp_pi10 + 10;
        tmp_b2 = (int)tmp_u15 < (int)tmp_s14;
        tmp_u15 = tmp_u15 + 1;
      } while (tmp_b2);
    }
    else {
      if (param_3 == 2) {
        tmp_u15 = 1;
        tmp_pi10 = &g_unk_01091ea4;
        do {
          while ((*(int *)(cgs + *tmp_pi10 * 0x1a4 + 0x9494) == 3 && ((tmp_u15 & 1) == 0))) {
            WM_DrawClientScore(param_1,local_19c,tmp_pi10,local_140 + 1,param_4,0);
            local_19c = local_19c + 0x10;
            tmp_b2 = (int)g_unk_01091e84 <= (int)tmp_u15;
            tmp_s14 = g_unk_01091e84;
            tmp_u15 = tmp_u15 + 1;
            tmp_pi10 = tmp_pi10 + 10;
            if (tmp_b2) {
              return local_19c;
            }
          }
          tmp_pi10 = tmp_pi10 + 10;
          tmp_b2 = (int)tmp_u15 < (int)tmp_s14;
          tmp_u15 = tmp_u15 + 1;
        } while (tmp_b2);
        return local_19c;
      }
      tmp_pi10 = &g_unk_01091ea4;
      tmp_i9 = 1;
      do {
        while (*(int *)(cgs + *tmp_pi10 * 0x1a4 + 0x9494) == 3) {
          WM_DrawClientScore(param_1,local_19c,tmp_pi10,local_140 + 1,param_4,0);
          local_19c = local_19c + 0x10;
          tmp_b2 = (int)g_unk_01091e84 <= tmp_i9;
          tmp_s14 = g_unk_01091e84;
          tmp_pi10 = tmp_pi10 + 10;
          tmp_i9 = tmp_i9 + 1;
          if (tmp_b2) {
            return local_19c;
          }
        }
        tmp_pi10 = tmp_pi10 + 10;
        tmp_b2 = tmp_i9 < (int)tmp_s14;
        tmp_i9 = tmp_i9 + 1;
      } while (tmp_b2);
    }
  }
  return local_19c;
}

uint32_t CG_DrawScoreboard(void)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  long tmp_l4;
  long tmp_l5;
  int tmp_i6;
  int tmp_i7;
  uint32_t tmp_u8;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  if (GHIDRA_FIELD(cg_paused, 12, 4) != 0) {
    return 0;
  }
  if ((g_unk_010aac20 == 0) && ((g_unk_01047aec == 0 || (*(int *)(g_unk_01047b00 + 0x30) == 5)))) {
    if (g_unk_010aaecc != 0) {
      return 1;
    }
    if ((g_unk_010928a4 != 0) || (g_unk_01090700 == 5)) goto LAB_000b12c6;
    tmp_i6 = CG_FadeColor(g_unk_010928ac,200);
    if (tmp_i6 == 0) {
      g_unk_010928bc = 0;
      return 0;
    }
    tmp_u1 = *(uint32_t *)(tmp_i6 + 0xc);
  }
  else {
    if (g_unk_010928a4 == 0) {
      return 0;
    }
    if (g_unk_010aaecc != 0) {
      return 1;
    }
LAB_000b12c6:
    tmp_u1 = 0x3f800000;
  }
  tmp_u2 = WM_DrawObjectives(0x14,10,0x25d,tmp_u1);
  if (GHIDRA_FIELD(cgs, 27388, 4) == 3) {
    if (*(int *)(g_unk_01047b00 + 0x30) == 5) {
      local_2c = 0x3f19999a;
      local_28 = 0x3f19999a;
      local_24 = 0x3f19999a;
      local_20 = 0x3f800000;
      tmp_u2 = CG_ConfigString(0xd);
      tmp_pc3 = (char *)Info_ValueForKey(tmp_u2,"d");
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_u2 = CG_ConfigString(0xe);
      tmp_pc3 = (char *)Info_ValueForKey(tmp_u2,"w");
      tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
      if (GHIDRA_FIELD(cgs, 33525344, 4) == 0) {
        if (tmp_l4 == 0) {
          tmp_pc3 = "ALLIES SUCCESSFULLY BEAT THE CLOCK!";
          if (tmp_l5 == 0) {
            tmp_pc3 = "ALLIES COULDN\'T BEAT THE CLOCK!";
          }
        }
        else {
          tmp_pc3 = "AXIS SUCCESSFULLY BEAT THE CLOCK!";
          if (tmp_l4 == tmp_l5) {
            tmp_pc3 = "AXIS COULDN\'T BEAT THE CLOCK!";
          }
        }
      }
      else {
        tmp_i6 = (int)ROUND(((float)GHIDRA_FIELD(cgs, 33525348, 4) * 60.0 * 1000.0) / 1000.0);
        tmp_i7 = tmp_i6 % 0x3c;
        tmp_u2 = va("%i:%i%i",tmp_i6 / 0x3c,tmp_i7 / 10,tmp_i7 % 10);
        tmp_pc3 = (char *)va("CLOCK IS NOW SET TO %s!",tmp_u2);
      }
      CG_FillRect(0x430c0000,0x42820000,0x43b40000,0x41a00000,clrUiBar);
      CG_DrawRect_FixedBorder(0x430c0000,0x42820000,0x43b40000,0x41a00000,1,&colorBlack);
      tmp_i6 = CG_Text_Width_Ext(tmp_pc3,0x3e800000,0,0x1100f64);
      CG_Text_Paint_Ext(320.0 - (float)tmp_i6 * 0.5,0x42a00000,0x3e800000,0x3e800000,&local_2c,tmp_pc3
                        ,0,0,0,0x1100f64);
      WM_TeamScoreboard(0x14,0x5a,1,tmp_u1,0xf,0x21);
      WM_TeamScoreboard(0x159,0x5a,2,tmp_u1,0xf,0x21);
      return 1;
    }
  }
  else {
    if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
      nitmod_DMTeamScoreboard(0x14,tmp_u2,tmp_u1,0x19,0x21);
      return 1;
    }
    if (*(int *)(g_unk_01047b00 + 0x30) == 5) {
      WM_TeamScoreboard(0x14,tmp_u2,1,tmp_u1,0x14,0x21);
      tmp_u8 = 0x14;
      goto LAB_000b1364;
    }
  }
  WM_TeamScoreboard(0x14,tmp_u2,1,tmp_u1,0x19,0x21);
  tmp_u8 = 0x19;
LAB_000b1364:
  WM_TeamScoreboard(0x159,tmp_u2,2,tmp_u1,tmp_u8,0x21);
  return 1;
}

void CG_DrawSkyBoxPortal_part_0(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  float tmp_f3;
  float tmp_f4;
  uint tmp_u5;
  double tmp_d6;
  int local_1c8 [4];
  float local_1b8;
  float local_1b4;
  uint32_t local_1b0;
  uint32_t local_1ac;
  uint32_t local_1a8;
  int local_180;
  uint local_17c;
  
  tmp_u5 = 0;
  do {
    tmp_u2 = *(uint32_t *)(g_unk_010afbcc + tmp_u5);
    *(uint32_t *)((int)local_1c8 + tmp_u5 + 4) = *(uint32_t *)(g_unk_010afbcc + 4 + tmp_u5);
    *(uint32_t *)((int)local_1c8 + tmp_u5) = tmp_u2;
    tmp_u5 = tmp_u5 + 8;
  } while (tmp_u5 < 0x1a8);
  local_1b0 = g_unk_010b4538;
  local_1ac = g_unk_010b453c;
  *(uint32_t *)((int)local_1c8 + tmp_u5) = *(uint32_t *)(g_unk_010afbcc + tmp_u5);
  local_1a8 = g_unk_010b4540;
  if (param_1 == 0) goto LAB_000ca9b9;
  if (g_unk_01090700 == 5) {
    tmp_f1 = 90.0;
  }
  else {
    if ((float)GHIDRA_FIELD(cg_fov, 8, 4) < 1.0) {
      tmp_f3 = 1.0;
    }
    else {
      tmp_f3 = (float)GHIDRA_FIELD(cg_fov, 8, 4);
      if (160.0 < (float)GHIDRA_FIELD(cg_fov, 8, 4)) {
        tmp_f3 = 160.0;
      }
    }
    if (g_unk_01091a74 == 0.0) {
      if (g_unk_01091a64 == 0) {
        tmp_f4 = (float)(g_unk_010906e0 - g_unk_01091a6c) / 150.0;
        tmp_f1 = tmp_f3;
        if (tmp_f4 <= 1.0) {
          tmp_f1 = lastfov_12143 + (tmp_f3 - lastfov_12143) * tmp_f4;
        }
      }
      else {
LAB_000caa62:
        tmp_f4 = (float)(g_unk_010906e0 - g_unk_01091a6c) / 150.0;
        tmp_f1 = lastfov_12143;
        if (tmp_f4 <= 1.0) {
          lastfov_12143 = (lastfov_12143 - tmp_f3) * tmp_f4 + tmp_f3;
          tmp_f1 = lastfov_12143;
        }
      }
    }
    else {
      if (g_unk_01091a74 < 1.0) {
        lastfov_12143 = 1.0;
      }
      else {
        lastfov_12143 = 160.0;
        if (g_unk_01091a74 <= 160.0) {
          lastfov_12143 = g_unk_01091a74;
        }
      }
      if (g_unk_01091a64 != 0) goto LAB_000caa62;
      lastfov_12143 = g_unk_01091a74;
      tmp_f1 = g_unk_01091a74;
    }
  }
  local_17c = local_17c & 0xffffffbf;
  if (((*(uint *)(g_unk_01047b00 + 0x94) & 0x8020) == 0) && (g_unk_010907a0 != 0x2e)) {
    tmp_d6 = tan((double)((tmp_f1 / 360.0) * 3.1415927));
  }
  else {
    tmp_d6 = 0.5205670439407086;
    tmp_f1 = 55.0;
  }
  tmp_d6 = atan2((double)local_1c8[3],(double)((float)local_1c8[2] / (float)tmp_d6));
  local_1b4 = ((float)tmp_d6 * 360.0) / 3.1415927;
  local_1b8 = tmp_f1;
LAB_000ca9b9:
  local_180 = g_unk_010906e0;
  local_17c = local_17c | 8;
  trap_R_RenderScene(local_1c8);
  return;
}

uint32_t CG_DrawSkyBoxPortal(uint32_t param_1)
{
  uint32_t tmp_u1;
  
  if ((GHIDRA_FIELD(cg_skybox, 12, 4) != 0) && (g_unk_010b4534 != 0)) {
    tmp_u1 = CG_DrawSkyBoxPortal_part_0();
    return tmp_u1;
  }
  return param_1;
}

void CG_DrawActiveFrame(int param_1,int param_2,int param_3)
{
  char *__nptr;
  uint8_t *tmp_pu1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  byte *tmp_pb7;
  uint tmp_u8;
  int tmp_i9;
  long tmp_l10;
  char *tmp_pc11;
  size_t tmp_s12;
  uint32_t tmp_u13;
  uint8_t *tmp_pu14;
  float *pfVar15;
  int tmp_i16;
  long double tmp_l17;
  double tmp_d18;
  int local_15c;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  char local_11c [4];
  uint32_t local_118;
  float local_114 [43];
  uint8_t local_68;
  uint8_t local_67;
  uint8_t local_66;
  uint8_t local_65;
  float local_58;
  uint32_t uStack_14;
  
  uStack_14 = 0xce099;
  if (firstFrame_12209 == 0) {
    firstFrame_12209 = 1;
  }
  g_unk_010906e0 = param_1;
  g_unk_0102619c = param_1;
  g_unk_01047aec = param_3;
  if (g_unk_010ef664 != 0) {
    nitrox_ReadNKey();
  }
  nitrox_ScreenshotThink();
  if (0 < g_unk_010d604c) {
    tmp_pu14 = &g_unk_010bde4c;
    tmp_i16 = 0;
    do {
      trap_Cvar_VariableStringBuffer(tmp_pu14,local_11c,0x100);
      tmp_d18 = strtod(local_11c,(char **)0x0);
      tmp_f4 = (float)tmp_d18;
      tmp_pc11 = tmp_pu14 + 0x104;
      tmp_d18 = strtod(tmp_pc11,(char **)0x0);
      tmp_f5 = (float)tmp_d18;
      __nptr = tmp_pu14 + 0x204;
      tmp_d18 = strtod(__nptr,(char **)0x0);
      tmp_f6 = (float)tmp_d18;
      switch(*(uint32_t *)(tmp_pu14 + 0x100)) {
      case 0:
        tmp_i9 = Q_stricmp(tmp_pc11,local_11c);
        if (tmp_i9 != 0) {
          trap_Cvar_Set(tmp_pu14,tmp_pc11);
        }
        break;
      case 1:
        if (tmp_f4 <= tmp_f5) {
          tmp_f5 = tmp_f5 + 1.0;
LAB_000ce8fe:
          tmp_d18 = (double)tmp_f5;
LAB_000ce9e0:
          tmp_u13 = va(&g_unk_0011e95f,tmp_d18);
          trap_Cvar_Set(tmp_pu14,tmp_u13);
        }
        break;
      case 2:
        if (tmp_f4 < tmp_f5) {
          trap_Cvar_Set(tmp_pu14,tmp_pc11);
        }
        break;
      case 3:
        if (tmp_f5 <= tmp_f4) {
          tmp_f5 = tmp_f5 - 1.0;
          goto LAB_000ce8fe;
        }
        break;
      case 4:
        tmp_d18 = strtod(tmp_pc11,(char **)0x0);
        if (tmp_d18 != 0.0) {
          tmp_d18 = strtod(tmp_pc11,(char **)0x0);
          tmp_l10 = strtol(local_11c,(char **)0x0,10);
          if (tmp_d18 < (double)tmp_l10) {
            trap_Cvar_Set(tmp_pu14,tmp_pc11);
          }
        }
        break;
      case 5:
        if ((tmp_f5 != 0.0) && (tmp_f4 < tmp_f5)) {
          trap_Cvar_Set(tmp_pu14,tmp_pc11);
        }
        if ((tmp_f6 != 0.0) && (tmp_f6 < tmp_f4)) {
LAB_000ce884:
          trap_Cvar_Set(tmp_pu14,__nptr);
        }
        break;
      case 6:
        if (((tmp_f5 != 0.0) && (tmp_f5 <= tmp_f4)) && ((tmp_f6 == 0.0 || (tmp_f4 < tmp_f6)))) {
          tmp_d18 = strtod(tmp_pc11,(char **)0x0);
          tmp_u13 = va(&g_unk_0011e95f,tmp_d18 - 1.0);
          trap_Cvar_Set(tmp_pu14,tmp_u13);
        }
        if ((tmp_f6 != 0.0 && tmp_f4 <= tmp_f6) && (tmp_f5 < tmp_f4)) {
          tmp_d18 = strtod(__nptr,(char **)0x0);
          tmp_d18 = tmp_d18 + 1.0;
          goto LAB_000ce9e0;
        }
        break;
      case 7:
        tmp_pc11 = strstr(local_11c,tmp_pc11);
        if (tmp_pc11 == (char *)0x0) goto LAB_000ce884;
        break;
      case 8:
        tmp_pc11 = strstr(local_11c,tmp_pc11);
        if (tmp_pc11 != (char *)0x0) goto LAB_000ce884;
      }
      tmp_i16 = tmp_i16 + 1;
      tmp_pu14 = tmp_pu14 + 0x304;
    } while (tmp_i16 < g_unk_010d604c);
  }
  CG_UpdateCvars();
  if ((g_unk_010b5e44 != 0) && (0 < g_unk_010bde48)) {
    tmp_pu14 = &g_unk_010b5e48;
    tmp_i16 = 0;
    do {
      tmp_u8 = 0;
      do {
        tmp_pc11 = local_11c + tmp_u8;
        tmp_pc11[0] = '\0';
        tmp_pc11[1] = '\0';
        tmp_pc11[2] = '\0';
        tmp_pc11[3] = '\0';
        *(uint32_t *)((int)&local_118 + tmp_u8) = 0;
        tmp_u8 = tmp_u8 + 8;
      } while (tmp_u8 < 0x80);
      trap_Cvar_VariableStringBuffer(tmp_pu14,local_11c,0x80);
      tmp_pu1 = tmp_pu14 + 0x100;
      tmp_i9 = Q_stricmp(tmp_pu1,local_11c);
      if (tmp_i9 != 0) {
        CG_Printf("server forcing cvar %s to %s\n",tmp_pu14,tmp_pu1);
        trap_Cvar_Register(0,tmp_pu14,tmp_pu1,0);
        trap_Cvar_Set(tmp_pu14,tmp_pu1);
      }
      tmp_i16 = tmp_i16 + 1;
      tmp_pu14 = tmp_pu14 + 0x200;
    } while (tmp_i16 < g_unk_010bde48);
  }
  if ((GHIDRA_FIELD(cg_FTAutoSelect, 12, 4) != 0) && (tmp_i16 = CG_IsOnFireteam(g_unk_01047ac4), tmp_i16 != 0)) {
    tmp_i16 = 0;
    do {
      tmp_i9 = CG_SortedFireTeamPlayerForPosition(tmp_i16);
      if (tmp_i9 == 0) break;
      tmp_i16 = tmp_i16 + 1;
      *(uint32_t *)(tmp_i9 + 0x170) = 1;
    } while (tmp_i16 != 6);
  }
  if (g_unk_01091a7c != '\0') {
LAB_000cea59:
    CG_DrawInformation(0);
    return;
  }
  CG_PB_ClearPolyBuffers();
  CG_UpdatePMLists();
  trap_S_ClearLoopingSounds();
  CG_UpdateBufferedSoundScripts();
  CG_ProcessSnapshots();
  if ((g_unk_01047b00 == (byte *)0x0) || ((*g_unk_01047b00 & 2) != 0)) goto LAB_000cea59;
  if (g_unk_01091814 == 0) {
    if (*(int *)(g_unk_01047b00 + 0xd0) != 0) {
      g_unk_010aac34 = g_unk_010906e0;
      g_unk_01091814 = *(int *)(g_unk_01047b00 + 0xd0);
      goto LAB_000ce38b;
    }
    if (((cg != 0) || (g_unk_01047aec != 0)) || (tmp_i16 = 0, GHIDRA_FIELD(cgs, 33525356, 4) != 0))
    goto LAB_000ce3c7;
LAB_000ce3ae:
    if ((cg_autoAction[0xc] & 1) != 0) {
      CG_autoRecord_f();
      tmp_i16 = g_unk_01091814;
    }
  }
  else {
LAB_000ce38b:
    tmp_i16 = g_unk_01091814;
    if (((cg == 0) && (g_unk_01047aec == 0)) && (GHIDRA_FIELD(cgs, 33525356, 4) == 0)) goto LAB_000ce3ae;
  }
  if ((tmp_i16 == 0x29) &&
     (tmp_l17 = (long double)VectorLength(g_unk_01047b00 + 0x4c), (long double)180.0 < tmp_l17)) {
    CG_FinishWeaponChange(0x29,0x1f);
  }
LAB_000ce3c7:
  if (g_unk_01092cfc == 0) {
    CG_SetupDlightstyles();
  }
  if (GHIDRA_FIELD(cg_norender, 12, 4) != 0) {
    return;
  }
  cg = cg + 1;
  CG_PredictPlayerState();
  trap_R_ClearScene();
  g_unk_010906f4 = 1;
  if ((GHIDRA_FIELD(cg_thirdPerson, 12, 4) == 0) && (0 < *(int *)(g_unk_01047b00 + 0xfc))) {
    g_unk_010906f4 = (uint)(g_unk_010abd78 != 0);
  }
  tmp_i16 = CG_CalcViewValues();
  CG_SetupFrustum();
  if ((GHIDRA_FIELD(cg_skybox, 12, 4) != 0) && (g_unk_010b4534 != 0)) {
    CG_DrawSkyBoxPortal_part_0();
  }
  if (tmp_i16 != 0) {
    trap_S_AddLoopingSound(g_unk_01047b00 + 0x40,&vec3_origin,GHIDRA_FIELD(cgs, 69492, 4),0x100ff,0);
  }
  if ((g_unk_010906f4 == 0) &&
     (((((g_unk_01047b00[0x39] & 0x40) == 0 && (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3))
       || (g_unk_010abd78 == 0)) && (GHIDRA_FIELD(cgs, 27292, 4) != 3)))) {
    pfVar15 = (float *)&g_unk_010aac50;
    do {
      tmp_f4 = *pfVar15;
      if (tmp_f4 != 0.0) {
        tmp_f5 = pfVar15[-3];
        tmp_f6 = pfVar15[-4];
        tmp_i9 = g_unk_010906e0 - (int)tmp_f6;
        if ((tmp_i9 < (int)tmp_f5) && (0 < tmp_i9)) {
          tmp_f2 = pfVar15[-2];
          tmp_f3 = pfVar15[-1];
          if ((tmp_f2 != 0.0) || (tmp_f3 != 0.0)) {
            tmp_u8 = 0;
            do {
              tmp_pc11 = local_11c + tmp_u8;
              tmp_pc11[0] = '\0';
              tmp_pc11[1] = '\0';
              tmp_pc11[2] = '\0';
              tmp_pc11[3] = '\0';
              *(uint32_t *)((int)&local_118 + tmp_u8) = 0;
              tmp_u8 = tmp_u8 + 8;
            } while (tmp_u8 < 0xe8);
            tmp_pc11 = local_11c + tmp_u8;
            tmp_pc11[0] = '\0';
            tmp_pc11[1] = '\0';
            tmp_pc11[2] = '\0';
            tmp_pc11[3] = '\0';
            local_11c[0] = '\x02';
            local_11c[1] = '\0';
            local_11c[2] = '\0';
            local_11c[3] = '\0';
            local_118 = 4;
            tmp_f2 = tmp_f2 * -8.0;
            tmp_f3 = tmp_f3 * 8.0;
            local_114[0x18] =
                 *(float *)(g_unk_010afbcc + 0x3c) * tmp_f3 +
                 *(float *)(g_unk_010afbcc + 0x30) * tmp_f2 +
                 *(float *)(g_unk_010afbcc + 0x24) * 8.0 + *(float *)(g_unk_010afbcc + 0x18);
            local_114[0x19] =
                 *(float *)(g_unk_010afbcc + 0x40) * tmp_f3 +
                 *(float *)(g_unk_010afbcc + 0x34) * tmp_f2 +
                 *(float *)(g_unk_010afbcc + 0x28) * 8.0 + *(float *)(g_unk_010afbcc + 0x1c);
            local_114[0x1a] =
                 tmp_f3 * *(float *)(g_unk_010afbcc + 0x44) +
                 tmp_f2 * *(float *)(g_unk_010afbcc + 0x38) +
                 *(float *)(g_unk_010afbcc + 0x2c) * 8.0 + *(float *)(g_unk_010afbcc + 0x20);
            tmp_d18 = sin((double)(int)tmp_f6);
            local_58 = (ABS((float)tmp_d18) * 0.5 + 0.75) *
                       (((float)tmp_i9 * 0.5) / (float)(int)tmp_f5 + 0.5) * tmp_f4 * 0.4;
            tmp_d18 = floor((double)(((float)tmp_i9 / (float)(int)tmp_f5) * 4.9));
            local_114[0x2a] = *(float *)(cgs + (int)ROUND(tmp_d18) * 4 + 0x10bc4);
            local_68 = 0xff;
            local_67 = 0xff;
            local_66 = 0xff;
            local_65 = 0xff;
            if ((float)GHIDRA_FIELD(cg_bloodDamageBlend, 8, 4) <= 1.0) {
              if ((float)GHIDRA_FIELD(cg_bloodDamageBlend, 8, 4) < 0.0) {
                local_65 = 0;
              }
              else {
                local_65 = (uint8_t)(short)ROUND((float)GHIDRA_FIELD(cg_bloodDamageBlend, 8, 4) * 255.0);
              }
            }
            trap_R_AddRefEntityToScene(local_11c);
          }
        }
        else {
          *pfVar15 = 0.0;
        }
      }
      pfVar15 = pfVar15 + 5;
    } while (pfVar15 != (float *)&g_unk_010aacf0);
  }
  g_unk_010ee054 = 0;
  if (g_unk_010906f8 == 0) {
    CG_AddPacketEntities();
    CG_AddMarks();
    CG_AddScriptSpeakers();
    if (((cg_locations[0xd] & 2) != 0) && (0 < (int)GHIDRA_FIELD(cgs, 33785368, 4))) {
      pfVar15 = (float *)(cgs + 0x202461c);
      local_15c = 0;
      do {
        local_130 = -1.0;
        local_12c = -1.0;
        tmp_l17 = (long double)VectorDistance(&g_unk_010918c0,pfVar15);
        if ((tmp_l17 <= (long double)3000.0) &&
           (tmp_i9 = trap_R_inPVS(&g_unk_010918c0,pfVar15), tmp_i9 != 0)) {
          local_128 = *(float *)(g_unk_010afbcc + 0x18) - *pfVar15;
          local_124 = *(float *)(g_unk_010afbcc + 0x1c) - pfVar15[1];
          local_120 = *(float *)(g_unk_010afbcc + 0x20) - pfVar15[2];
          VectorNormalize2(&local_128,&local_128);
          if (((local_120 * *(float *)(g_unk_010afbcc + 0x2c) +
                local_124 * *(float *)(g_unk_010afbcc + 0x28) +
                local_128 * *(float *)(g_unk_010afbcc + 0x24) < -0.6) &&
              (((tmp_i9 = CG_WorldCoordToScreenCoordFloat(pfVar15,&local_130,&local_12c), tmp_i9 != 0
                && (0.0 <= local_130)) && (local_130 <= 640.0)))) &&
             ((0.0 <= local_12c && (local_12c <= 480.0)))) {
            tmp_u8 = 0;
            do {
              tmp_pc11 = local_11c + tmp_u8;
              tmp_pc11[0] = '\0';
              tmp_pc11[1] = '\0';
              tmp_pc11[2] = '\0';
              tmp_pc11[3] = '\0';
              *(uint32_t *)((int)&local_118 + tmp_u8) = 0;
              tmp_u8 = tmp_u8 + 8;
            } while (tmp_u8 < 0xe8);
            tmp_f4 = *pfVar15;
            tmp_pc11 = local_11c + tmp_u8;
            tmp_pc11[0] = '\0';
            tmp_pc11[1] = '\0';
            tmp_pc11[2] = '\0';
            tmp_pc11[3] = '\0';
            local_114[0x19] = pfVar15[1];
            local_11c[0] = '\x02';
            local_11c[1] = '\0';
            local_11c[2] = '\0';
            local_11c[3] = '\0';
            local_114[0x1a] = pfVar15[2];
            local_114[0x18] = tmp_f4;
            local_114[0x1f] = tmp_f4;
            local_114[0x20] = local_114[0x19];
            local_114[0x21] = local_114[0x1a];
            tmp_s12 = strlen((char *)(pfVar15 + 3));
            local_114[0x2a] = (float)GHIDRA_FIELD(cgs, 68096, 4);
            local_58 = (float)(tmp_s12 + 8);
            local_68 = 0xff;
            local_67 = 0xff;
            local_66 = 0xff;
            local_65 = 0xff;
            trap_R_AddRefEntityToScene(local_11c);
            tmp_u13 = va("%i:%s",pfVar15[-1],pfVar15 + 3);
            CG_AddOnScreenText(tmp_u13,pfVar15);
          }
        }
        local_15c = local_15c + 1;
        pfVar15 = pfVar15 + 0x14;
      } while (local_15c < (int)GHIDRA_FIELD(cgs, 33785368, 4));
    }
    CG_AddParticles();
    CG_AddLocalEntities();
    CG_AddSmokeSprites();
    CG_AddAtmosphericEffects();
  }
  if ((g_unk_010abd78 == 0) && (GHIDRA_FIELD(cgs, 33686244, 4) == 0)) {
    if (*(int *)(g_unk_01047b00 + 0x16c) == 0) {
      CG_AddViewWeapon(&g_unk_010906fc);
    }
    else if (g_unk_010906e0 - g_unk_01090ef4 < 3000) {
      CG_CalcMuzzlePoint(*(uint32_t *)(g_unk_01047b00 + 0xcc),local_11c);
      local_114[0] = local_114[0] - 32.0;
      tmp_i9 = rand();
      if (tmp_i9 == (tmp_i9 / 3) * 3) {
        CG_ParticleImpactSmokePuffExtended
                  (GHIDRA_FIELD(cgs, 68876, 4),local_11c,1000,8,0x14,0x1e,
                   (1.0 - (float)(g_unk_010906e0 - g_unk_01090ef4) / 3000.0) * 0.25,0x41000000);
      }
    }
  }
  CG_PlayBufferedVoiceChats();
  if (g_unk_010906f8 == 0) {
    CG_AddFlameChunks();
    CG_AddTrails();
  }
  if (g_unk_010aad84 != 0) {
    g_unk_010aad84 = trap_R_RegisterModel(&g_unk_010aae68);
    if (g_unk_010aad84 == 0) {
      CG_Printf("Can\'t register model\n");
    }
    else {
      if (g_unk_010aaea8 != 0) {
        g_unk_010aad98 = g_unk_010918cc;
        g_unk_010aad9c = g_unk_010918d0;
        g_unk_010aada0 = g_unk_010918d4;
        g_unk_010aada4 = g_unk_010918d8;
        g_unk_010aada8 = g_unk_010918dc;
        g_unk_010aadac = g_unk_010918e0;
        g_unk_010aadb0 = g_unk_010918e4;
        g_unk_010aadb4 = g_unk_010918e8;
        g_unk_010aadb8 = g_unk_010918ec;
        g_unk_010aade4 = g_unk_010918e4 * (float)GHIDRA_FIELD(cg_gun_z, 8, 4) +
                       g_unk_010918d8 * (float)GHIDRA_FIELD(cg_gun_y, 8, 4) +
                       g_unk_010918cc * (float)GHIDRA_FIELD(cg_gun_x, 8, 4) + g_unk_010918c0;
        g_unk_010aade8 = g_unk_010918e8 * (float)GHIDRA_FIELD(cg_gun_z, 8, 4) +
                       g_unk_010918dc * (float)GHIDRA_FIELD(cg_gun_y, 8, 4) +
                       g_unk_010918d0 * (float)GHIDRA_FIELD(cg_gun_x, 8, 4) + g_unk_010918c4;
        g_unk_010aadec = (float)GHIDRA_FIELD(cg_gun_y, 8, 4) * g_unk_010918e0 +
                       (float)GHIDRA_FIELD(cg_gun_x, 8, 4) * g_unk_010918d4 + g_unk_010918c8 +
                       (float)GHIDRA_FIELD(cg_gun_z, 8, 4) * g_unk_010918ec;
      }
      trap_R_AddRefEntityToScene(&g_unk_010aad7c);
    }
  }
  tmp_i9 = g_unk_010906e0;
  tmp_pb7 = g_unk_01047b00;
  g_unk_010918f0 = g_unk_010906e0;
  tmp_u8 = 0;
  do {
    *(uint32_t *)((int)&g_unk_010918f8 + tmp_u8) = *(uint32_t *)(tmp_pb7 + tmp_u8 + 0xc);
    tmp_u8 = tmp_u8 + 4;
  } while (tmp_u8 < 0x20);
  if (param_2 != 2) {
    g_unk_010906dc = tmp_i9 - g_unk_010906e4;
    g_unk_010906e4 = tmp_i9;
    if (g_unk_010906dc < 0) {
      g_unk_010906dc = 0;
    }
    CG_AddLagometerFrameInfo();
  }
  trap_SetClientLerpOrigin(g_unk_010918c0,g_unk_010918c4,g_unk_010918c8);
  CG_DrawActive(param_2);
  trap_S_Respatialize(*(uint32_t *)(g_unk_01047b00 + 0xcc),&g_unk_010918c0,&g_unk_010918cc,tmp_i16);
  if (((((g_unk_01047b00[0x96] & 0x40) == 0) && (GHIDRA_FIELD(cg_drawCam, 12, 4) != 0)) &&
      (0 < (int)GHIDRA_FIELD(cgs, 33788116, 4))) && ((g_unk_010ee054 != 0 && (g_unk_010abd78 == 0)))) {
    local_114[1] = 120.0;
    local_114[0] = 160.0;
    local_11c[0] = '\0';
    local_11c[1] = '\0';
    local_11c[2] = -0x80;
    local_11c[3] = 'A';
    local_118 = 0x43200000;
    CG_DrawMissileCamera(local_11c);
  }
  if (GHIDRA_FIELD(cg_stats, 12, 4) != 0) {
    CG_Printf("cg.clientFrame:%i\n",cg);
  }
  tmp_u8 = (uint)(g_unk_010abd78 != 0);
  if (((GHIDRA_FIELD(cgs, 33823108, 4) == -1) || ((int)GHIDRA_FIELD(cgs, 33823108, 4) < g_unk_010906e0)) &&
     (GHIDRA_FIELD(cgs, 33823108, 4) = g_unk_010906e0 + 10000, 0 < (int)GHIDRA_FIELD(cgs, 33823112, 4))) {
    tmp_u8 = tmp_u8 | GHIDRA_FIELD(cgs, 33823112, 4);
  }
  trap_SetUserCmdValue(g_unk_01091814,tmp_u8,g_unk_01091a70,g_unk_010aac04);
  return;
}

void CG_DrawHitBoxOnHit_part_11(uint32_t *param_1)
{
  float tmp_f1;
  uint tmp_u2;
  uint tmp_u3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint32_t *tmp_pu7;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  uint8_t local_a8 [12];
  uint8_t local_9c [12];
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  byte local_21;
  int local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0xd3e4b;
  local_c0 = g_unk_01090710;
  local_bc = g_unk_01090714;
  local_b8 = (float)g_unk_010907b8 + g_unk_01090718;
  AngleVectors(&g_unk_010907ac,&local_b4,local_a8,local_9c);
  local_c0 = local_b4 * 14.0 + local_c0;
  local_bc = local_b0 * 14.0 + local_bc;
  local_b8 = local_ac * 14.0 + local_b8;
  tmp_f1 = (float)param_1[0x1d4];
  if (tmp_f1 != 0.0) {
    AngleVectors(param_1 + 0x1e8,&local_60,&local_54,0);
    local_c0 = local_54 * tmp_f1 + local_c0;
    local_bc = local_50 * tmp_f1 + local_bc;
    local_b8 = (local_4c * tmp_f1 + local_b8) - ABS(tmp_f1 / 3.5);
  }
  local_90 = local_b4 * 8192.0 + local_c0;
  local_8c = local_b0 * 8192.0 + local_bc;
  local_88 = local_ac * 8192.0 + local_b8;
  CG_Trace(&local_54,&local_c0,&vec3_origin,&vec3_origin,&local_90,*param_1,0x2000001);
  if ((local_4c < 1.0) && ((local_21 & 2) != 0)) {
    tmp_i5 = local_20 * 0xaf8;
    tmp_u2 = *(uint *)(cg_entities + tmp_i5 + 0xb4);
    local_80 = (float)(int)-(tmp_u2 & 0xff);
    local_74 = (float)(tmp_u2 & 0xff);
    local_84 = *(float *)(cg_entities + tmp_i5 + 0x794) + local_80;
    local_80 = local_80 + *(float *)(cg_entities + tmp_i5 + 0x798);
    local_7c = (float)(int)-(tmp_u2 >> 8 & 0xff) + *(float *)(cg_entities + tmp_i5 + 0x79c);
    local_78 = *(float *)(cg_entities + tmp_i5 + 0x794) + local_74;
    tmp_u3 = *(uint *)(cg_entities + tmp_i5);
    local_74 = local_74 + *(float *)(cg_entities + tmp_i5 + 0x798);
    local_70 = (float)(int)(((int)tmp_u2 >> 0x10 & 0xffU) - 0x20) +
               *(float *)(cg_entities + tmp_i5 + 0x79c);
    tv(0x3e800000,0x3f000000,0x3f800000);
    CG_RailTrail_part_5(&local_78,tmp_u3 | 0x1000);
    tmp_i6 = g_unk_01047b00;
    if (g_unk_01047b04 != 0) {
      tmp_i6 = local_20 * 0xaf8;
      BG_EvaluateTrajectory
                (tmp_i6 + 0x3133e4c,*(uint32_t *)(g_unk_01047b00 + 8),&local_6c,0,
                 *(uint32_t *)(cg_entities + tmp_i6 + 0x110));
      BG_EvaluateTrajectory
                (tmp_i6 + 0x3133f6c,*(uint32_t *)(g_unk_01047b04 + 8),&local_60,0,
                 *(uint32_t *)(cg_entities + tmp_i6 + 0x110));
      CG_Printf("^3Int: time: %d, j: %d, k: %d, origin: %0.2f %0.2f %0.2f\n",g_unk_010906e4,
                *(uint32_t *)(g_unk_01047b00 + 8),*(uint32_t *)(g_unk_01047b04 + 8),
                (double)*(float *)(cg_entities + tmp_i6 + 0x794),
                (double)*(float *)(cg_entities + tmp_i6 + 0x798),
                (double)*(float *)(cg_entities + tmp_i6 + 0x79c));
      CG_Printf("^5frac: %0.4f, origin1: %0.2f %0.2f %0.2f, origin2: %0.2f %0.2f %0.2f\n",
                (double)g_unk_010906d0,(double)local_6c,(double)local_68,(double)local_64,
                (double)local_60,(double)local_5c,(double)local_58);
      return;
    }
    tmp_pu7 = (uint32_t *)(cg_entities + tmp_i5 + 0xc);
    *tmp_pu7 = 3;
    tmp_u4 = *(uint32_t *)(tmp_i6 + 8);
    *(uint32_t *)(cg_entities + tmp_i5 + 0x14) = 0x32;
    *(uint32_t *)(cg_entities + tmp_i5 + 0x10) = tmp_u4;
    BG_EvaluateTrajectory
              (tmp_pu7,*(uint32_t *)(tmp_i6 + 8),&local_6c,0,
               *(uint32_t *)(cg_entities + tmp_i5 + 0x110));
    BG_EvaluateTrajectory
              (tmp_pu7,(int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4)) + *(int *)(g_unk_01047b00 + 8),
               &local_60,0,*(uint32_t *)(cg_entities + tmp_i5 + 0x110));
    CG_Printf("^3Ext: time: %d, j: %d, k: %d, origin: %0.2f %0.2f %0.2f\n",g_unk_010906e4,
              *(uint32_t *)(g_unk_01047b00 + 8),*(uint32_t *)(g_unk_01047b00 + 8),
              (double)*(float *)(cg_entities + tmp_i5 + 0x794),
              (double)*(float *)(cg_entities + tmp_i5 + 0x798),
              (double)*(float *)(cg_entities + tmp_i5 + 0x79c));
    CG_Printf("^5frac: %0.4f, origin1: %0.2f %0.2f %0.2f, origin2: %0.2f %0.2f %0.2f\n",
              (double)g_unk_010906d0,(double)local_6c,(double)local_68,(double)local_64,
              (double)local_60,(double)local_5c,(double)local_58);
  }
  return;
}

void CG_RailTrail(uint32_t *param_1,uint32_t *param_2,uint32_t *param_3,int param_4,
                 int param_5)

{
  uint32_t tmp_u1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  
  if (param_4 != 0) {
    CG_RailTrail_part_5();
    return;
  }
  if (param_5 == 0) {
    tmp_i4 = CG_AllocLocalEntity();
  }
  else {
    tmp_i4 = CG_FindLocalEntity(param_5,0xffffffff);
    if (tmp_i4 == 0) {
      tmp_i4 = CG_AllocLocalEntity();
    }
    *(int *)(tmp_i4 + 0x1b4) = param_5;
    *(uint32_t *)(tmp_i4 + 0x1b8) = 0xffffffff;
  }
  *(uint32_t *)(tmp_i4 + 8) = 6;
  tmp_i3 = g_unk_010906e0;
  *(int *)(tmp_i4 + 0x10) = g_unk_010906e0;
  tmp_f2 = (float)g_unk_010906e0 + (float)GHIDRA_FIELD(cg_railTrailTime, 8, 4);
  *(int *)(tmp_i4 + 0x14) = (int)ROUND(tmp_f2);
  *(float *)(tmp_i4 + 0x1c) = 1.0 / (float)((int)ROUND(tmp_f2) - tmp_i3);
  tmp_f2 = (float)g_unk_010906e0;
  *(uint32_t *)(tmp_i4 + 0x98) = 5;
  *(float *)(tmp_i4 + 0x158) = tmp_f2 / 1000.0;
  *(uint32_t *)(tmp_i4 + 0x148) = GHIDRA_FIELD(cgs, 67956, 4);
  *(uint32_t *)(tmp_i4 + 0x100) = *param_2;
  *(uint32_t *)(tmp_i4 + 0x104) = param_2[1];
  *(uint32_t *)(tmp_i4 + 0x108) = param_2[2];
  *(uint32_t *)(tmp_i4 + 0x11c) = *param_3;
  *(uint32_t *)(tmp_i4 + 0x120) = param_3[1];
  *(uint32_t *)(tmp_i4 + 0x124) = param_3[2];
  *(uint32_t *)(tmp_i4 + 0x6c) = *param_1;
  *(uint32_t *)(tmp_i4 + 0x70) = param_1[1];
  tmp_u1 = param_1[2];
  *(uint32_t *)(tmp_i4 + 0x78) = 0x3f800000;
  *(uint32_t *)(tmp_i4 + 0x74) = tmp_u1;
  AxisClear(tmp_i4 + 0xb4);
  return;
}

void CG_DrawHitBoxOnHit(int *param_1)
{
  if (*param_1 != g_unk_0109079c) {
    return;
  }
  CG_DrawHitBoxOnHit_part_11();
  return;
}

void CG_DrawTracer(float *param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint8_t local_58;
  uint8_t local_57;
  uint8_t local_56;
  uint8_t local_55;
  float local_54;
  float local_50;
  float local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint8_t local_40;
  uint8_t local_3f;
  uint8_t local_3e;
  uint8_t local_3d;
  float local_3c;
  float local_38;
  float local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint8_t local_28;
  uint8_t local_27;
  uint8_t local_26;
  uint8_t local_25;
  float local_24;
  float local_20;
  float local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint8_t local_10;
  uint8_t local_f;
  uint8_t local_e;
  uint8_t local_d;
  
  tmp_f2 = *(float *)(g_unk_010afbcc + 0x44) * (param_2[2] - param_1[2]) +
          *(float *)(g_unk_010afbcc + 0x40) * (param_2[1] - param_1[1]) +
          (*param_2 - *param_1) * *(float *)(g_unk_010afbcc + 0x3c);
  tmp_f1 = -((param_2[1] - param_1[1]) * *(float *)(g_unk_010afbcc + 0x34) +
            (*param_2 - *param_1) * *(float *)(g_unk_010afbcc + 0x30) +
           (param_2[2] - param_1[2]) * *(float *)(g_unk_010afbcc + 0x38));
  local_78 = *(float *)(g_unk_010afbcc + 0x3c) * tmp_f1 + *(float *)(g_unk_010afbcc + 0x30) * tmp_f2;
  local_74 = *(float *)(g_unk_010afbcc + 0x40) * tmp_f1 + *(float *)(g_unk_010afbcc + 0x34) * tmp_f2;
  local_70 = tmp_f1 * *(float *)(g_unk_010afbcc + 0x44) + tmp_f2 * *(float *)(g_unk_010afbcc + 0x38);
  VectorNormalize(&local_78);
  local_60 = 0x3f800000;
  local_5c = 0x3f800000;
  local_58 = 0xff;
  local_57 = 0xff;
  local_56 = 0xff;
  local_55 = 0xff;
  local_48 = 0x3f800000;
  local_40 = 0xff;
  local_6c = *param_2 + local_78 * (float)GHIDRA_FIELD(cg_tracerWidth, 8, 4);
  local_3f = 0xff;
  local_3e = 0xff;
  local_3d = 0xff;
  local_68 = param_2[1] + local_74 * (float)GHIDRA_FIELD(cg_tracerWidth, 8, 4);
  local_64 = param_2[2] + local_70 * (float)GHIDRA_FIELD(cg_tracerWidth, 8, 4);
  tmp_f1 = -(float)GHIDRA_FIELD(cg_tracerWidth, 8, 4);
  local_54 = *param_2 + local_78 * tmp_f1;
  local_50 = param_2[1] + local_74 * tmp_f1;
  local_4c = param_2[2] + tmp_f1 * local_70;
  local_44 = 0;
  local_3c = local_78 * tmp_f1 + *param_1;
  local_38 = local_74 * tmp_f1 + param_1[1];
  local_34 = tmp_f1 * local_70 + param_1[2];
  local_10 = 0xff;
  local_d = 0xff;
  local_30 = 0;
  local_2c = 0;
  local_24 = local_78 * (float)GHIDRA_FIELD(cg_tracerWidth, 8, 4) + *param_1;
  local_28 = 0xff;
  local_27 = 0xff;
  local_20 = local_74 * (float)GHIDRA_FIELD(cg_tracerWidth, 8, 4) + param_1[1];
  local_26 = 0xff;
  local_25 = 0xff;
  local_14 = 0x3f800000;
  local_1c = local_70 * (float)GHIDRA_FIELD(cg_tracerWidth, 8, 4) + param_1[2];
  local_f = 0xff;
  local_e = 0xff;
  local_18 = 0;
  trap_R_AddPolyToScene(GHIDRA_FIELD(cgs, 68004, 4),4,&local_6c);
  return;
}

void Script_SetTeamColor(int param_1)
{
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  if (*(void **)(DC + 0x6c) != (void *)0x0) {
    (**(void **)(DC + 0x6c))(&local_1c);
    *(uint32_t *)(param_1 + 0x84) = local_1c;
    *(uint32_t *)(param_1 + 0x88) = local_18;
    *(uint32_t *)(param_1 + 0x8c) = local_14;
    *(uint32_t *)(param_1 + 0x90) = local_10;
  }
  return;
}

void Script_CheckAutoUpdate(void)
{
  (**(void **)(DC + 0xac))();
  return;
}

void Script_GetAutoUpdate(void)
{
  (**(void **)(DC + 0xb0))();
  return;
}

void Script_Abort(uint32_t param_1,uint32_t *param_2)
{
  *param_2 = 1;
  return;
}

uint32_t ItemParse_decoration(int param_1)
{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x10;
  return 1;
}

uint32_t ItemParse_textasint(int param_1)
{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x10000000;
  return 1;
}

uint32_t ItemParse_textasfloat(int param_1)
{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x20000000;
  return 1;
}

uint32_t ItemParse_wrapped(int param_1)
{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x40000;
  return 1;
}

uint32_t ItemParse_autowrapped(int param_1)
{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x80000;
  return 1;
}

uint32_t ItemParse_horizontalscroll(int param_1)
{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x400;
  return 1;
}

uint32_t ItemParse_noToggle(int param_1)
{
  *(uint *)(param_1 + 0x120) = *(uint *)(param_1 + 0x120) | 0x10;
  return 1;
}

uint32_t MenuParse_popup(int param_1)
{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x200000;
  return 1;
}

uint32_t MenuParse_outOfBounds(int param_1)
{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x20000;
  return 1;
}

uint32_t MenuParse_drawAlwaysOnTop(int param_1)
{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x2000000;
  return 1;
}

uint32_t MenuParse_modal(int param_1)
{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x4000000;
  return 1;
}

void Scroll_Slider_ThumbFunc(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  void *tmp_pc4;
  float tmp_f5;
  uint32_t tmp_u6;
  
  pfVar3 = *(float **)(param_1 + 0x18);
  if (pfVar3[0x3a] == 0.0) {
    tmp_f2 = *pfVar3;
  }
  else {
    tmp_f2 = pfVar3[0x2e] + pfVar3[0x30] + 8.0;
  }
  tmp_f1 = (float)*(int *)(DC + 0x124);
  tmp_f5 = tmp_f2;
  if ((tmp_f2 <= tmp_f1) && (tmp_f5 = tmp_f1, tmp_f2 + 96.0 < tmp_f1)) {
    tmp_f5 = tmp_f2 + 96.0;
  }
  tmp_pc4 = *(void **)(DC + 0x78);
  tmp_f1 = *(float *)pfVar3[0x94];
  tmp_u6 = va(&g_unk_0011e95f,
             (double)(tmp_f1 + (((float *)pfVar3[0x94])[1] - tmp_f1) * ((tmp_f5 - tmp_f2) / 96.0)));
  (*tmp_pc4)(*(uint32_t *)(*(int *)(param_1 + 0x18) + 0x114),tmp_u6);
  return;
}

bool ItemParse_name(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x20);
  return tmp_i1 != 0;
}

bool ItemParse_focusSound(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t local_10 [3];
  
  local_10[0] = 0;
  tmp_i1 = PC_String_Parse(param_2,local_10);
  if (tmp_i1 != 0) {
    tmp_u2 = (**(void **)(DC + 0xdc))(local_10[0],1);
    *(uint32_t *)(param_1 + 0x124) = tmp_u2;
  }
  return tmp_i1 != 0;
}

bool ItemParse_text(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_String_Parse(param_2,param_1 + 0xe8);
  return tmp_i1 != 0;
}

bool ItemParse_group(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x28);
  return tmp_i1 != 0;
}

bool ItemParse_asset_shader(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t local_10 [3];
  
  local_10[0] = 0;
  tmp_i1 = PC_String_Parse(param_2,local_10);
  if (tmp_i1 != 0) {
    tmp_u2 = (*(void *)*DC)(local_10[0]);
    *(uint32_t *)(param_1 + 0xf0) = tmp_u2;
  }
  return tmp_i1 != 0;
}

bool ItemParse_background(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t local_10 [3];
  
  local_10[0] = 0;
  tmp_i1 = PC_String_Parse(param_2,local_10);
  if (tmp_i1 != 0) {
    tmp_u2 = (*(void *)*DC)(local_10[0]);
    *(uint32_t *)(param_1 + 0xb4) = tmp_u2;
  }
  return tmp_i1 != 0;
}

bool ItemParse_cinematic(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x2c);
  return tmp_i1 != 0;
}

bool ItemParse_cvarTest(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x118);
  return tmp_i1 != 0;
}

bool MenuParse_background(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t local_10 [3];
  
  local_10[0] = 0;
  tmp_i1 = PC_String_Parse(param_2,local_10);
  if (tmp_i1 != 0) {
    tmp_u2 = (*(void *)*DC)(local_10[0]);
    *(uint32_t *)(param_1 + 0xb4) = tmp_u2;
  }
  return tmp_i1 != 0;
}

bool MenuParse_cinematic(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x2c);
  return tmp_i1 != 0;
}

bool MenuParse_soundLoop(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x4f0);
  return tmp_i1 != 0;
}

bool ItemParse_feeder(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x248);
  return tmp_i1 != 0;
}

bool ItemParse_bordersize(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x44);
  return tmp_i1 != 0;
}

bool ItemParse_textalignx(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xd4);
  return tmp_i1 != 0;
}

bool ItemParse_textaligny(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xd8);
  return tmp_i1 != 0;
}

bool ItemParse_textscale(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xdc);
  return tmp_i1 != 0;
}

uint32_t ItemParse_backcolor(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t local_20 [4];
  
  tmp_i2 = 0;
  local_20[0] = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_1 + 0x84 + tmp_i2 * 4) = local_20[0];
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 4);
  return 1;
}

uint32_t ItemParse_forecolor(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t *tmp_pu3;
  uint32_t local_20 [4];
  
  local_20[0] = 0;
  tmp_pu2 = (uint32_t *)(param_1 + 0x74);
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    tmp_pu3 = tmp_pu2 + 1;
    *tmp_pu2 = local_20[0];
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x200;
    tmp_pu2 = tmp_pu3;
  } while (tmp_pu3 != (uint32_t *)(param_1 + 0x84));
  return 1;
}

uint32_t ItemParse_bordercolor(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t local_20 [4];
  
  tmp_i2 = 0;
  local_20[0] = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_1 + 0x94 + tmp_i2 * 4) = local_20[0];
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 4);
  return 1;
}

bool ItemParse_special(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x248);
  return tmp_i1 != 0;
}

bool MenuParse_borderSize(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x44);
  return tmp_i1 != 0;
}

uint32_t MenuParse_backcolor(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t local_20 [4];
  
  tmp_i2 = 0;
  local_20[0] = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_1 + 0x84 + tmp_i2 * 4) = local_20[0];
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 4);
  return 1;
}

uint32_t MenuParse_forecolor(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t *tmp_pu3;
  uint32_t local_20 [4];
  
  local_20[0] = 0;
  tmp_pu2 = (uint32_t *)(param_1 + 0x74);
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    tmp_pu3 = tmp_pu2 + 1;
    *tmp_pu2 = local_20[0];
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x200;
    tmp_pu2 = tmp_pu3;
  } while (tmp_pu3 != (uint32_t *)(param_1 + 0x84));
  return 1;
}

uint32_t MenuParse_bordercolor(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t local_20 [4];
  
  tmp_i2 = 0;
  local_20[0] = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_1 + 0x94 + tmp_i2 * 4) = local_20[0];
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 4);
  return 1;
}

uint32_t MenuParse_focuscolor(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t local_20 [4];
  
  tmp_i2 = 0;
  local_20[0] = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_1 + 0x4f4 + tmp_i2 * 4) = local_20[0];
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 4);
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x8000000;
  return 1;
}

uint32_t MenuParse_disablecolor(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t local_20 [4];
  
  tmp_i2 = 0;
  local_20[0] = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_1 + 0x504 + tmp_i2 * 4) = local_20[0];
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 4);
  return 1;
}

bool MenuParse_fadeClamp(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xd0);
  return tmp_i1 != 0;
}

bool MenuParse_fadeAmount(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xd4);
  return tmp_i1 != 0;
}

uint32_t ItemParse_origin(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int local_14;
  int local_10 [2];
  
  local_14 = 0;
  local_10[0] = 0;
  tmp_i1 = PC_Int_Parse(param_2,&local_14);
  if (tmp_i1 != 0) {
    tmp_i1 = PC_Int_Parse(param_2,local_10);
    if (tmp_i1 != 0) {
      *(float *)(param_1 + 0x10) = (float)local_14 + *(float *)(param_1 + 0x10);
      *(float *)(param_1 + 0x14) = (float)local_10[0] + *(float *)(param_1 + 0x14);
      return 1;
    }
  }
  return 0;
}

bool ItemParse_style(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x34);
  return tmp_i1 != 0;
}

bool ItemParse_bitflag(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x274);
  return tmp_i1 != 0;
}

bool ItemParse_border(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x38);
  return tmp_i1 != 0;
}

uint32_t ItemParse_visible(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int local_10 [3];
  
  local_10[0] = 0;
  tmp_i1 = PC_Int_Parse(param_2,local_10);
  tmp_u2 = 0;
  if ((tmp_i1 != 0) && (tmp_u2 = 1, local_10[0] != 0)) {
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 4;
  }
  return tmp_u2;
}

bool ItemParse_ownerdraw(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x3c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 200) = 8;
  }
  return tmp_i1 != 0;
}

bool ItemParse_align(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xcc);
  return tmp_i1 != 0;
}

bool ItemParse_textalign(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xd0);
  return tmp_i1 != 0;
}

bool ItemParse_textstyle(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xe4);
  return tmp_i1 != 0;
}

bool ItemParse_textfont(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xe0);
  return tmp_i1 != 0;
}

bool ItemParse_ownerdrawFlag(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint local_10 [2];
  
  local_10[0] = 0;
  tmp_i1 = PC_Int_Parse(param_2,local_10);
  if (tmp_i1 != 0) {
    *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | local_10[0];
  }
  return tmp_i1 != 0;
}

void ItemParse_settingDisabled(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x25c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x260) = 1;
  }
  return;
}

void ItemParse_settingEnabled(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x25c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x260) = 2;
  }
  return;
}

void ItemParse_voteFlag(int param_1,uint32_t param_2)
{
  PC_Int_Parse(param_2,param_1 + 0x264);
  return;
}

bool MenuParse_fullscreen(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xbc);
  return tmp_i1 != 0;
}

bool MenuParse_style(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x34);
  return tmp_i1 != 0;
}

uint32_t MenuParse_visible(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int local_10 [3];
  
  local_10[0] = 0;
  tmp_i1 = PC_Int_Parse(param_2,local_10);
  tmp_u2 = 0;
  if ((tmp_i1 != 0) && (tmp_u2 = 1, local_10[0] != 0)) {
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 4;
  }
  return tmp_u2;
}

bool MenuParse_border(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x38);
  return tmp_i1 != 0;
}

bool MenuParse_ownerdrawFlag(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint local_10 [2];
  
  local_10[0] = 0;
  tmp_i1 = PC_Int_Parse(param_2,local_10);
  if (tmp_i1 != 0) {
    *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | local_10[0];
  }
  return tmp_i1 != 0;
}

bool MenuParse_ownerdraw(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x3c);
  return tmp_i1 != 0;
}

bool MenuParse_fadeCycle(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xcc);
  return tmp_i1 != 0;
}

bool MenuParse_itemHotkeyMode(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xd14);
  return tmp_i1 != 0;
}

bool ItemParse_outlinecolor(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Color_Parse(param_2,param_1 + 0xa4);
  return tmp_i1 != 0;
}

bool MenuParse_outlinecolor(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Color_Parse(param_2,param_1 + 0xa4);
  return tmp_i1 != 0;
}

uint32_t * Item_CorrectedTextRect(int param_1)
{
  rect_10157 = 0;
  g_unk_00c38260 = 0.0;
  g_unk_00c38264 = 0.0;
  g_unk_00c38268 = 0.0;
  if (param_1 != 0) {
    rect_10157 = *(uint32_t *)(param_1 + 0xb8);
    g_unk_00c38260 = *(float *)(param_1 + 0xbc);
    g_unk_00c38264 = *(float *)(param_1 + 0xc0);
    g_unk_00c38268 = *(float *)(param_1 + 0xc4);
    if (g_unk_00c38264 != 0.0) {
      g_unk_00c38260 = g_unk_00c38260 - g_unk_00c38268;
    }
  }
  return &rect_10157;
}

bool MenuParse_name(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x20);
  if (tmp_i1 != 0) {
    Q_stricmp(*(uint32_t *)(param_1 + 0x20),"main");
  }
  return tmp_i1 != 0;
}

uint Item_SettingShow_constprop_35(int param_1)
{
  uint tmp_u1;
  char local_40c [1024];
  
  (**(void **)(DC + 0x10c))(0x1d,local_40c,0x400);
  if ((*(uint *)(param_1 + 0x260) & 2) == 0) {
    tmp_u1 = 1;
    if ((*(uint *)(param_1 + 0x260) & 1) != 0) {
      tmp_u1 = strtol(local_40c,(char **)0x0,10);
      tmp_u1 = (uint)((*(uint *)(param_1 + 0x25c) & tmp_u1) == 0);
    }
  }
  else {
    tmp_u1 = strtol(local_40c,(char **)0x0,10);
    tmp_u1 = tmp_u1 & *(uint *)(param_1 + 0x25c);
  }
  return tmp_u1;
}

bool Item_SettingShow_constprop_36(int param_1)
{
  uint tmp_u1;
  char local_40c [1024];
  
  trap_Cvar_VariableStringBuffer("cg_ui_voteFlags",local_40c,0x400);
  tmp_u1 = strtol(local_40c,(char **)0x0,10);
  return *(uint *)(param_1 + 0x264) != (tmp_u1 & *(uint *)(param_1 + 0x264));
}

bool MenuParse_rect(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1);
  if (((tmp_i1 != 0) && (tmp_i1 = PC_Float_Parse(param_2,param_1 + 4), tmp_i1 != 0)) &&
     (tmp_i1 = PC_Float_Parse(param_2,param_1 + 8), tmp_i1 != 0)) {
    tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xc);
    return tmp_i1 != 0;
  }
  return false;
}

bool ItemParse_rect(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x10);
  if (((tmp_i1 != 0) && (tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x14), tmp_i1 != 0)) &&
     (tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x18), tmp_i1 != 0)) {
    tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x1c);
    return tmp_i1 != 0;
  }
  return false;
}

uint32_t Item_ValidateTooltipData_part_24(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint16_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint tmp_u5;
  uint16_t *tmp_pu6;
  uint tmp_u7;
  bool tmp_b8;
  
  tmp_i1 = allocPoint;
  if (allocPoint < 0x1ffd89) {
    tmp_pu6 = (uint16_t *)(memoryPool + allocPoint);
    allocPoint = allocPoint + 0x280;
    tmp_b8 = ((uint)tmp_pu6 & 1) != 0;
    tmp_u7 = 0x278;
    *(uint16_t **)(param_1 + 0x270) = tmp_pu6;
    tmp_pu3 = tmp_pu6;
    if (tmp_b8) {
      *(uint8_t *)tmp_pu6 = 0;
      tmp_pu3 = (uint16_t *)(memoryPool + tmp_i1 + 1);
      tmp_u7 = 0x277;
    }
    if (((uint)tmp_pu3 & 2) != 0) {
      *tmp_pu3 = 0;
      tmp_u7 = tmp_u7 - 2;
      tmp_pu3 = tmp_pu3 + 1;
    }
    tmp_u5 = 0;
    do {
      *(uint32_t *)((int)tmp_pu3 + tmp_u5) = 0;
      *(uint32_t *)((int)tmp_pu3 + tmp_u5 + 4) = 0;
      tmp_u5 = tmp_u5 + 8;
    } while (tmp_u5 < (tmp_u7 & 0xfffffff8));
    tmp_pu4 = (uint32_t *)((int)tmp_pu3 + tmp_u5);
    if ((tmp_u7 & 4) != 0) {
      *tmp_pu4 = 0;
      tmp_pu4 = tmp_pu4 + 1;
    }
    if ((tmp_u7 & 2) != 0) {
      *(uint16_t *)tmp_pu4 = 0;
      tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
    }
    if (tmp_b8) {
      *(uint8_t *)tmp_pu4 = 0;
    }
    tmp_b8 = ((uint)tmp_pu6 & 1) != 0;
    tmp_u7 = 0xb8;
    *(uint32_t *)(memoryPool + tmp_i1 + 0x254) = 0xffffffff;
    *(uint32_t *)(memoryPool + tmp_i1 + 0xdc) = 0x3f0ccccd;
    *(uint32_t *)(memoryPool + tmp_i1 + 0x274) = 0;
    if (tmp_b8) {
      *(uint8_t *)tmp_pu6 = 0;
      tmp_pu6 = (uint16_t *)(memoryPool + tmp_i1 + 1);
      tmp_u7 = 0xb7;
    }
    if (((uint)tmp_pu6 & 2) != 0) {
      *tmp_pu6 = 0;
      tmp_u7 = tmp_u7 - 2;
      tmp_pu6 = tmp_pu6 + 1;
    }
    tmp_u5 = 0;
    do {
      *(uint32_t *)((int)tmp_pu6 + tmp_u5) = 0;
      *(uint32_t *)((int)tmp_pu6 + tmp_u5 + 4) = 0;
      tmp_u5 = tmp_u5 + 8;
    } while (tmp_u5 < (tmp_u7 & 0xfffffff8));
    tmp_pu4 = (uint32_t *)((int)tmp_pu6 + tmp_u5);
    if ((tmp_u7 & 4) != 0) {
      *tmp_pu4 = 0;
      tmp_pu4 = tmp_pu4 + 1;
    }
    if ((tmp_u7 & 2) != 0) {
      *(uint16_t *)tmp_pu4 = 0;
      tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
    }
    if (tmp_b8) {
      *(uint8_t *)tmp_pu4 = 0;
    }
    *(uint32_t *)(memoryPool + tmp_i1 + 0x44) = 0x3f800000;
    *(uint32_t *)(memoryPool + tmp_i1 + 0x80) = 0x3f800000;
    *(uint32_t *)(memoryPool + tmp_i1 + 0x7c) = 0x3f800000;
    *(uint32_t *)(memoryPool + tmp_i1 + 0x78) = 0x3f800000;
    *(uint32_t *)(memoryPool + tmp_i1 + 0x74) = 0x3f800000;
    *(uint32_t *)(memoryPool + tmp_i1 + 0x30) = 0xffffffff;
    tmp_i1 = *(int *)(param_1 + 0x270);
    *(uint32_t *)(tmp_i1 + 0xe8) = 0;
    *(uint32_t *)(tmp_i1 + 0xe0) = 2;
    *(uint32_t *)(tmp_i1 + 0xd4) = 0x40400000;
    *(uint32_t *)(tmp_i1 + 0xd8) = 0x41200000;
    *(uint32_t *)(tmp_i1 + 0xdc) = 0x3e4ccccd;
    *(uint32_t *)(tmp_i1 + 0x38) = 1;
    *(uint32_t *)(tmp_i1 + 0x44) = 0x3f800000;
    *(uint *)(tmp_i1 + 0x48) = *(uint *)(tmp_i1 + 0x48) & 0xfffffffb | 0x2080000;
    *(uint32_t *)(tmp_i1 + 0x84) = 0x3f666666;
    *(uint32_t *)(tmp_i1 + 0x88) = 0x3f666666;
    *(uint32_t *)(tmp_i1 + 0x8c) = 0x3f400000;
    *(uint32_t *)(tmp_i1 + 0x90) = 0x3f800000;
    *(uint32_t *)(tmp_i1 + 0x94) = 0;
    *(uint32_t *)(tmp_i1 + 0x98) = 0;
    *(uint32_t *)(tmp_i1 + 0x9c) = 0;
    *(uint32_t *)(tmp_i1 + 0xa0) = 0x3f800000;
    *(uint32_t *)(tmp_i1 + 0x74) = 0;
    *(uint32_t *)(tmp_i1 + 0x78) = 0;
    *(uint32_t *)(tmp_i1 + 0x7c) = 0;
    *(uint32_t *)(tmp_i1 + 0x80) = 0x3f800000;
    tmp_u2 = 1;
  }
  else {
    outOfMemory = 1;
    if (*(void **)(DC + 0xd0) != (void *)0x0) {
      (**(void **)(DC + 0xd0))("UI_Alloc: Failure. Out of memory!\n");
    }
    *(uint32_t *)(param_1 + 0x270) = 0;
    tmp_u2 = 0;
  }
  return tmp_u2;
}

bool ItemParse_tooltip(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x270);
  if (tmp_i1 == 0) {
    tmp_i1 = Item_ValidateTooltipData_part_24();
    if (tmp_i1 == 0) {
      return false;
    }
    tmp_i1 = *(int *)(param_1 + 0x270);
  }
  tmp_i1 = PC_String_Parse(param_2,tmp_i1 + 0xe8);
  return tmp_i1 != 0;
}

bool ItemParse_tooltipalignx(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x270);
  if (tmp_i1 == 0) {
    tmp_i1 = Item_ValidateTooltipData_part_24();
    if (tmp_i1 == 0) {
      return false;
    }
    tmp_i1 = *(int *)(param_1 + 0x270);
  }
  tmp_i1 = PC_Float_Parse(param_2,tmp_i1 + 0xd4);
  return tmp_i1 != 0;
}

bool ItemParse_tooltipaligny(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x270);
  if (tmp_i1 == 0) {
    tmp_i1 = Item_ValidateTooltipData_part_24();
    if (tmp_i1 == 0) {
      return false;
    }
    tmp_i1 = *(int *)(param_1 + 0x270);
  }
  tmp_i1 = PC_Float_Parse(param_2,tmp_i1 + 0xd8);
  return tmp_i1 != 0;
}

uint32_t ItemParse_addColorRangeRel(int param_1,uint32_t param_2)
{
  uint16_t tmp_u1;
  int tmp_i2;
  uint16_t *tmp_pu3;
  uint16_t *tmp_pu4;
  uint16_t *tmp_pu5;
  uint tmp_u6;
  uint tmp_u7;
  bool tmp_b8;
  uint8_t local_38;
  uint16_t auStack_37 [9];
  uint8_t local_24 [4];
  uint8_t local_20 [16];
  
  if ((*(int *)(param_1 + 0x128) == 0) || (*(int *)(param_1 + 0x244) == 1)) {
    *(uint32_t *)(param_1 + 0x244) = 1;
    tmp_pu3 = (uint16_t *)&local_38;
    tmp_i2 = PC_Float_Parse(param_2,local_24);
    if ((tmp_i2 != 0) &&
       ((tmp_i2 = PC_Float_Parse(param_2,local_20), tmp_i2 != 0 &&
        (tmp_i2 = PC_Color_Parse(param_2,tmp_pu3), tmp_i2 != 0)))) {
      if (*(int *)(param_1 + 0x128) < 10) {
        tmp_i2 = param_1 + 0x120 + *(int *)(param_1 + 0x128) * 0x1c;
        tmp_u7 = 0x1c;
        tmp_pu4 = (uint16_t *)(tmp_i2 + 0xc);
        tmp_b8 = ((uint)tmp_pu4 & 1) != 0;
        if (tmp_b8) {
          tmp_pu4 = (uint16_t *)(tmp_i2 + 0xd);
          tmp_u7 = 0x1b;
          *(uint8_t *)(tmp_i2 + 0xc) = local_38;
          tmp_pu3 = auStack_37;
        }
        tmp_pu5 = tmp_pu4;
        if (((uint)tmp_pu4 & 2) != 0) {
          tmp_u1 = *tmp_pu3;
          tmp_pu5 = tmp_pu4 + 1;
          tmp_pu3 = tmp_pu3 + 1;
          tmp_u7 = tmp_u7 - 2;
          *tmp_pu4 = tmp_u1;
        }
        tmp_u6 = 0;
        do {
          *(uint32_t *)((int)tmp_pu5 + tmp_u6) = *(uint32_t *)((int)tmp_pu3 + tmp_u6);
          tmp_u6 = tmp_u6 + 4;
        } while (tmp_u6 < (tmp_u7 & 0xfffffffc));
        tmp_i2 = 0;
        if ((tmp_u7 & 2) != 0) {
          *(uint16_t *)((int)tmp_pu5 + tmp_u6) = *(uint16_t *)((int)tmp_pu3 + tmp_u6);
          tmp_i2 = 2;
        }
        if (tmp_b8) {
          *(uint8_t *)((int)((int)tmp_pu5 + tmp_u6) + tmp_i2) =
               *(uint8_t *)((int)((int)tmp_pu3 + tmp_u6) + tmp_i2);
        }
        *(int *)(param_1 + 0x128) = *(int *)(param_1 + 0x128) + 1;
        return 1;
      }
      return 1;
    }
  }
  else {
    PC_SourceError(param_2,"both addColorRange and addColorRangeRel - set within same itemdef\n");
  }
  return 0;
}

uint32_t ItemParse_addColorRange(int param_1,uint32_t param_2)
{
  uint16_t tmp_u1;
  int tmp_i2;
  uint16_t *tmp_pu3;
  uint16_t *tmp_pu4;
  uint16_t *tmp_pu5;
  uint tmp_u6;
  uint tmp_u7;
  bool tmp_b8;
  uint8_t local_38;
  uint16_t auStack_37 [9];
  uint8_t local_24 [4];
  uint8_t local_20 [16];
  
  if ((*(int *)(param_1 + 0x128) == 0) || (*(int *)(param_1 + 0x244) == 0)) {
    *(uint32_t *)(param_1 + 0x244) = 0;
    tmp_pu3 = (uint16_t *)&local_38;
    tmp_i2 = PC_Float_Parse(param_2,local_24);
    if ((tmp_i2 != 0) &&
       ((tmp_i2 = PC_Float_Parse(param_2,local_20), tmp_i2 != 0 &&
        (tmp_i2 = PC_Color_Parse(param_2,tmp_pu3), tmp_i2 != 0)))) {
      if (*(int *)(param_1 + 0x128) < 10) {
        tmp_i2 = param_1 + 0x120 + *(int *)(param_1 + 0x128) * 0x1c;
        tmp_u7 = 0x1c;
        tmp_pu4 = (uint16_t *)(tmp_i2 + 0xc);
        tmp_b8 = ((uint)tmp_pu4 & 1) != 0;
        if (tmp_b8) {
          tmp_pu4 = (uint16_t *)(tmp_i2 + 0xd);
          tmp_u7 = 0x1b;
          *(uint8_t *)(tmp_i2 + 0xc) = local_38;
          tmp_pu3 = auStack_37;
        }
        tmp_pu5 = tmp_pu4;
        if (((uint)tmp_pu4 & 2) != 0) {
          tmp_u1 = *tmp_pu3;
          tmp_pu5 = tmp_pu4 + 1;
          tmp_pu3 = tmp_pu3 + 1;
          tmp_u7 = tmp_u7 - 2;
          *tmp_pu4 = tmp_u1;
        }
        tmp_u6 = 0;
        do {
          *(uint32_t *)((int)tmp_pu5 + tmp_u6) = *(uint32_t *)((int)tmp_pu3 + tmp_u6);
          tmp_u6 = tmp_u6 + 4;
        } while (tmp_u6 < (tmp_u7 & 0xfffffffc));
        tmp_i2 = 0;
        if ((tmp_u7 & 2) != 0) {
          *(uint16_t *)((int)tmp_pu5 + tmp_u6) = *(uint16_t *)((int)tmp_pu3 + tmp_u6);
          tmp_i2 = 2;
        }
        if (tmp_b8) {
          *(uint8_t *)((int)((int)tmp_pu5 + tmp_u6) + tmp_i2) =
               *(uint8_t *)((int)((int)tmp_pu3 + tmp_u6) + tmp_i2);
        }
        *(int *)(param_1 + 0x128) = *(int *)(param_1 + 0x128) + 1;
        return 1;
      }
      return 1;
    }
  }
  else {
    PC_SourceError(param_2,"both addColorRange and addColorRangeRel - set within same itemdef\n");
  }
  return 0;
}

void Script_ExecWolfConfig(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  void *tmp_pc1;
  char *__nptr;
  long tmp_l2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  long tmp_l6;
  uint tmp_u7;
  uint tmp_u8;
  uint *tmp_pu9;
  uint *tmp_pu10;
  uint32_t local_448;
  uint32_t local_444;
  uint32_t local_440;
  int local_43c [8];
  char local_41c [256];
  uint8_t local_31c [256];
  uint8_t local_21c [256];
  uint local_11c [67];
  
  __nptr = (char *)COM_ParseExt(param_3,0);
  if ((__nptr != (char *)0x0) && (*__nptr != '\0')) {
    tmp_l2 = strtol(__nptr,(char **)0x0,10);
    (**(void **)(DC + 0x70))("cl_profile",local_41c,0x100);
    if ((tmp_l2 == 0) || (local_41c[0] == '\0')) {
      tmp_pc1 = *(void **)(DC + 200);
      tmp_u3 = va("exec %s\n","etconfig.cfg");
      (*tmp_pc1)(0,tmp_u3);
    }
    else {
      Com_sprintf(local_31c,0x100,"profiles/%s/%s",local_41c,"etconfig.cfg");
      Com_sprintf(local_21c,0x100,"profiles/%s/%s.bak",local_41c,"etconfig.cfg");
      tmp_i4 = trap_FS_FOpenFile(local_21c,&local_444,0);
      trap_FS_FCloseFile(local_444);
      if ((0 < tmp_i4) && (tmp_i5 = trap_FS_FOpenFile(local_31c,&local_448,1), tmp_i5 == 0)) {
        trap_FS_FOpenFile(local_21c,&local_444,0);
        tmp_i5 = 0;
        do {
          tmp_i5 = tmp_i5 + 1;
          trap_FS_Read(local_11c,1,local_444);
          trap_FS_Write(local_11c,1,local_448);
        } while (tmp_i5 != tmp_i4);
        trap_FS_FCloseFile(local_448);
        trap_FS_FCloseFile(local_444);
        tmp_u3 = trap_FS_Delete(local_21c);
        Com_Printf("Delete %s %d\n",local_21c,tmp_u3);
      }
      tmp_u3 = va("profiles/%s/profile.pid",local_41c);
      tmp_i4 = trap_FS_FOpenFile(tmp_u3,&local_440,0);
      if (-1 < tmp_i4) {
        trap_FS_Read(local_43c,0x1f,local_440);
        (**(void **)(DC + 0x70))("com_pid",local_11c,0x100);
        tmp_l2 = strtol((char *)local_11c,(char **)0x0,10);
        tmp_l6 = strtol((char *)local_43c,(char **)0x0,10);
        if (tmp_l2 != tmp_l6) {
          trap_FS_FCloseFile(local_440);
          Com_Printf("^3WARNING: profile.pid found for profile \'%s\' - not executing %s\n",
                     local_41c,"etconfig.cfg");
          return;
        }
        trap_FS_FCloseFile(local_440);
      }
      (**(void **)(DC + 200))(0,local_31c);
      tmp_u3 = va("profiles/%s/profile.pid",local_41c);
      tmp_i4 = FileExists(tmp_u3);
      if (tmp_i4 != 0) {
        trap_FS_Delete(tmp_u3);
      }
      tmp_i4 = trap_FS_FOpenFile(tmp_u3,local_43c,1);
      if ((tmp_i4 < 0) || (local_43c[0] < 0)) {
        Com_Printf("Script_WriteProfile: Can\'t write %s.\n",tmp_u3);
        Com_Printf("^3WARNING: couldn\'t write profiles/%s/profile.pid\n",local_41c);
      }
      else {
        (**(void **)(DC + 0x70))("com_pid",local_11c,0x100);
        tmp_pu10 = local_11c;
        do {
          tmp_pu9 = tmp_pu10;
          tmp_u7 = *tmp_pu9 + 0xfefefeff & ~*tmp_pu9;
          tmp_u8 = tmp_u7 & 0x80808080;
          tmp_pu10 = tmp_pu9 + 1;
        } while (tmp_u8 == 0);
        if ((tmp_u7 & 0x8080) == 0) {
          tmp_pu10 = (uint *)((int)tmp_pu9 + 6);
          tmp_u8 = tmp_u8 >> 0x10;
        }
        trap_FS_Write(local_11c,
                      (int)tmp_pu10 + ((-3 - (uint)CARRY1((byte)tmp_u8,(byte)tmp_u8)) - (int)local_11c)
                      ,local_43c[0]);
        trap_FS_FCloseFile(local_43c[0]);
      }
    }
  }
  return;
}

void Tooltip_Initialize(int param_1)
{
  *(uint32_t *)(param_1 + 0x44) = 0x3f800000;
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

void Tooltip_ComputePosition(int param_1)
{
  uint *tmp_pu1;
  int tmp_i2;
  float tmp_f3;
  int tmp_i4;
  
  tmp_i2 = *(int *)(param_1 + 0x270);
  (**(void **)(DC + 0x30))(*(uint32_t *)(tmp_i2 + 0xe0));
  *(float *)(tmp_i2 + 0x10) = *(float *)(param_1 + 0x18) / 3.0 + *(float *)(param_1 + 0x10);
  *(float *)(tmp_i2 + 0x14) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x1c) + 8.0;
  tmp_i4 = (**(void **)(DC + 0x2c))
                    (*(uint32_t *)(*(int *)(param_1 + 0x270) + 0xe8),
                     *(uint32_t *)(*(int *)(param_1 + 0x270) + 0xdc),0);
  *(float *)(tmp_i2 + 0x1c) = (float)tmp_i4 + 9.0;
  tmp_i4 = (**(void **)(DC + 0x20))
                    (*(uint32_t *)(*(int *)(param_1 + 0x270) + 0xe8),
                     *(uint32_t *)(*(int *)(param_1 + 0x270) + 0xdc),0);
  *(float *)(tmp_i2 + 0x18) = (float)tmp_i4 + 6.0;
  tmp_f3 = (float)tmp_i4 + 6.0 + *(float *)(tmp_i2 + 0x10);
  if (635.0 < tmp_f3) {
    *(float *)(tmp_i2 + 0x10) = *(float *)(tmp_i2 + 0x10) - (tmp_f3 - 635.0);
  }
  *(uint32_t *)(*(int *)(param_1 + 0x270) + 0xec) = *(uint32_t *)(param_1 + 0xec);
  *(uint32_t *)(*(int *)(param_1 + 0x270) + 200) = 0;
  *(uint32_t *)(*(int *)(param_1 + 0x270) + 0x34) = 1;
  tmp_pu1 = (uint *)(*(int *)(param_1 + 0x270) + 0x48);
  *tmp_pu1 = *tmp_pu1 | 4;
  return;
}

void Cui_WideRect(float *param_1)
{
  int tmp_i1;
  long double tmp_l2;
  
  *param_1 = *param_1 * *(float *)(DC + 0x114);
  tmp_i1 = DC;
  param_1[1] = param_1[1] * *(float *)(DC + 0x110);
  param_1[2] = param_1[2] * *(float *)(tmp_i1 + 0x114);
  param_1[3] = param_1[3] * *(float *)(tmp_i1 + 0x110);
  if ((1.3333334 < *(float *)(tmp_i1 + 0x2003c)) &&
     (tmp_l2 = (long double)(**(void **)(tmp_i1 + 0x74))("r_mode"), tmp_l2 != (long double)11.0)) {
    *param_1 = (1.3333334 / *(float *)(DC + 0x2003c)) * *param_1;
    param_1[2] = (1.3333334 / *(float *)(DC + 0x2003c)) * param_1[2];
    return;
  }
  return;
}

long double Cui_WideX(float param_1)
{
  long double tmp_l1;
  
  tmp_l1 = (long double)param_1;
  if ((long double)1.3333334 < (long double)*(float *)(DC + 0x2003c)) {
    tmp_l1 = (long double)*(float *)(DC + 0x2003c) * (long double)0.75 * tmp_l1;
  }
  return tmp_l1;
}

long double Cui_WideXoffset(void)
{
  if ((long double)1.3333334 < (long double)*(float *)(DC + 0x2003c)) {
    return ((long double)*(float *)(DC + 0x2003c) * (long double)0.75 * (long double)640.0 -
           (long double)640.0) * (long double)0.5;
  }
  return (long double)0;
}

uint8_t * UI_Alloc(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = allocPoint;
  if (allocPoint + param_1 < 0x200001) {
    allocPoint = (param_1 + 0xfU & 0xfffffff0) + allocPoint;
    return memoryPool + tmp_i1;
  }
  outOfMemory = 1;
  if (*(void **)(DC + 0xd0) != (void *)0x0) {
    (**(void **)(DC + 0xd0))("UI_Alloc: Failure. Out of memory!\n");
    return (uint8_t *)0x0;
  }
  return (uint8_t *)0x0;
}

void Item_ValidateTypeData_part_21(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  uint8_t *tmp_pu3;
  uint tmp_u4;
  uint32_t *tmp_pu5;
  uint16_t *tmp_pu6;
  bool tmp_b7;
  
  tmp_u2 = *(uint *)(param_1 + 200);
  if (tmp_u2 == 6) {
    if (allocPoint < 0x1fff15) {
      tmp_pu6 = (uint16_t *)(memoryPool + allocPoint);
      allocPoint = allocPoint + 0xf0;
    }
    else {
      outOfMemory = 1;
      if (*(void **)(DC + 0xd0) == (void *)0x0) {
        tmp_pu6 = (uint16_t *)0x0;
      }
      else {
        (**(void **)(DC + 0xd0))("UI_Alloc: Failure. Out of memory!\n");
        tmp_pu6 = (uint16_t *)0x0;
      }
    }
    tmp_b7 = ((uint)tmp_pu6 & 1) != 0;
    tmp_u2 = 0xec;
    *(uint16_t **)(param_1 + 0x250) = tmp_pu6;
    if (tmp_b7) {
      *(uint8_t *)tmp_pu6 = 0;
      tmp_u2 = 0xeb;
      tmp_pu6 = (uint16_t *)((int)tmp_pu6 + 1);
    }
    if (((uint)tmp_pu6 & 2) != 0) {
      *tmp_pu6 = 0;
      tmp_u2 = tmp_u2 - 2;
      tmp_pu6 = tmp_pu6 + 1;
    }
    tmp_u4 = 0;
    do {
      *(uint32_t *)((int)tmp_pu6 + tmp_u4) = 0;
      *(uint32_t *)((int)tmp_pu6 + tmp_u4 + 4) = 0;
      tmp_u4 = tmp_u4 + 8;
    } while (tmp_u4 < (tmp_u2 & 0xfffffff8));
    tmp_pu5 = (uint32_t *)((int)tmp_pu6 + tmp_u4);
    if ((tmp_u2 & 4) != 0) {
      *tmp_pu5 = 0;
      tmp_pu5 = tmp_pu5 + 1;
    }
    if ((tmp_u2 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
    }
    if (tmp_b7) {
      *(uint8_t *)tmp_pu5 = 0;
      return;
    }
    return;
  }
  if (((tmp_u2 & 0xfffffffb) != 0 && tmp_u2 != 0xd) && (2 < tmp_u2 - 9)) {
    if (((tmp_u2 - 0xc & 0xfffffffb) == 0) || (tmp_u2 == 3)) {
      if (allocPoint < 0x1ffe75) {
        tmp_pu3 = memoryPool + allocPoint;
        allocPoint = allocPoint + 400;
      }
      else {
        outOfMemory = 1;
        if (*(void **)(DC + 0xd0) == (void *)0x0) {
          tmp_pu3 = (uint8_t *)0x0;
        }
        else {
          (**(void **)(DC + 0xd0))("UI_Alloc: Failure. Out of memory!\n");
          tmp_pu3 = (uint8_t *)0x0;
        }
      }
    }
    else {
      if ((tmp_u2 != 7) && (tmp_u2 != 0xe)) {
        return;
      }
      tmp_pu3 = (uint8_t *)UI_Alloc(0x40);
    }
    *(uint8_t **)(param_1 + 0x250) = tmp_pu3;
    return;
  }
  if (allocPoint < 0x1fffe5) {
    tmp_pu6 = (uint16_t *)(memoryPool + allocPoint);
    allocPoint = allocPoint + 0x20;
  }
  else {
    outOfMemory = 1;
    if (*(void **)(DC + 0xd0) == (void *)0x0) {
      tmp_pu6 = (uint16_t *)0x0;
    }
    else {
      (**(void **)(DC + 0xd0))("UI_Alloc: Failure. Out of memory!\n");
      tmp_pu6 = (uint16_t *)0x0;
    }
  }
  tmp_b7 = ((uint)tmp_pu6 & 1) != 0;
  tmp_u2 = 0x1c;
  *(uint16_t **)(param_1 + 0x250) = tmp_pu6;
  if (tmp_b7) {
    *(uint8_t *)tmp_pu6 = 0;
    tmp_u2 = 0x1b;
    tmp_pu6 = (uint16_t *)((int)tmp_pu6 + 1);
  }
  if (((uint)tmp_pu6 & 2) != 0) {
    *tmp_pu6 = 0;
    tmp_u2 = tmp_u2 - 2;
    tmp_pu6 = tmp_pu6 + 1;
  }
  tmp_u4 = 0;
  do {
    *(uint32_t *)((int)tmp_pu6 + tmp_u4) = 0;
    *(uint32_t *)((int)tmp_pu6 + tmp_u4 + 4) = 0;
    tmp_u4 = tmp_u4 + 8;
  } while (tmp_u4 < (tmp_u2 & 0xfffffff8));
  tmp_pu5 = (uint32_t *)((int)tmp_pu6 + tmp_u4);
  if ((tmp_u2 & 4) != 0) {
    *tmp_pu5 = 0;
    tmp_pu5 = tmp_pu5 + 1;
  }
  if ((tmp_u2 & 2) != 0) {
    *(uint16_t *)tmp_pu5 = 0;
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
  }
  if (tmp_b7) {
    *(uint8_t *)tmp_pu5 = 0;
    tmp_i1 = *(int *)(param_1 + 200);
  }
  else {
    tmp_i1 = *(int *)(param_1 + 200);
  }
  if ((tmp_i1 == 4) && (*(int *)(*(int *)(param_1 + 0x250) + 0x14) == 0)) {
    *(uint32_t *)(*(int *)(param_1 + 0x250) + 0x14) = 0x100;
    return;
  }
  return;
}

uint32_t ItemParse_asset_model(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t local_10;
  
  local_10 = 0;
  if (*(int *)(param_1 + 0x250) == 0) {
    Item_ValidateTypeData_part_21();
  }
  tmp_i1 = PC_String_Parse(param_2,&local_10);
  tmp_u3 = 0;
  if ((tmp_i1 != 0) && (tmp_u3 = 1, *(int *)(param_1 + 0xf0) == 0)) {
    tmp_u2 = (**(void **)(DC + 0x34))(local_10);
    *(uint32_t *)(param_1 + 0xf0) = tmp_u2;
  }
  return tmp_u3;
}

bool ItemParse_model_origin(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = *(int *)(param_1 + 0x250);
  if (tmp_i2 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i2 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Float_Parse(param_2,tmp_i2 + 4);
  if ((tmp_i1 != 0) && (tmp_i1 = PC_Float_Parse(param_2,tmp_i2 + 8), tmp_i1 != 0)) {
    tmp_i2 = PC_Float_Parse(param_2,tmp_i2 + 0xc);
    return tmp_i2 != 0;
  }
  return false;
}

bool ItemParse_model_fovx(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Float_Parse(param_2,tmp_i1 + 0x10);
  return tmp_i1 != 0;
}

bool ItemParse_model_fovy(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Float_Parse(param_2,tmp_i1 + 0x14);
  return tmp_i1 != 0;
}

bool ItemParse_model_rotation(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Int_Parse(param_2,tmp_i1 + 0x18);
  return tmp_i1 != 0;
}

bool ItemParse_model_angle(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Int_Parse(param_2,tmp_i1);
  return tmp_i1 != 0;
}

uint32_t ItemParse_model_animplay(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = *(int *)(param_1 + 0x250);
  if (tmp_i2 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i2 = *(int *)(param_1 + 0x250);
  }
  *(uint32_t *)(tmp_i2 + 0x1c) = 1;
  tmp_i1 = PC_Int_Parse(param_2,tmp_i2 + 0x20);
  if ((((tmp_i1 != 0) && (tmp_i1 = PC_Int_Parse(param_2,tmp_i2 + 0x24), tmp_i1 != 0)) &&
      (tmp_i1 = PC_Int_Parse(param_2,tmp_i2 + 0x28), tmp_i1 != 0)) &&
     (tmp_i1 = PC_Int_Parse(param_2,tmp_i2 + 0x2c), tmp_i1 != 0)) {
    *(uint32_t *)(tmp_i2 + 0x38) = 0;
    *(int *)(tmp_i2 + 0x34) = *(int *)(tmp_i2 + 0x20);
    tmp_i1 = DC;
    *(int *)(tmp_i2 + 0x30) = *(int *)(tmp_i2 + 0x20) + 1;
    *(uint32_t *)(tmp_i2 + 0x3c) = *(uint32_t *)(tmp_i1 + 0x11c);
    return 1;
  }
  return 0;
}

uint32_t ItemParse_notselectable(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  if ((tmp_i1 != 0) && (*(int *)(param_1 + 200) == 6)) {
    *(uint32_t *)(tmp_i1 + 0xe8) = 1;
  }
  return 1;
}

uint32_t ItemParse_type(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 200);
  tmp_u2 = 0;
  if ((tmp_i1 != 0) && (tmp_u2 = 1, *(int *)(param_1 + 0x250) == 0)) {
    Item_ValidateTypeData_part_21();
  }
  return tmp_u2;
}

bool ItemParse_elementwidth(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Float_Parse(param_2,tmp_i1 + 0x10);
  return tmp_i1 != 0;
}

bool ItemParse_elementheight(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Float_Parse(param_2,tmp_i1 + 0x14);
  return tmp_i1 != 0;
}

bool ItemParse_elementtype(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
    if (tmp_i1 == 0) {
      return false;
    }
  }
  tmp_i1 = PC_Int_Parse(param_2,tmp_i1 + 0x18);
  return tmp_i1 != 0;
}

uint32_t ItemParse_columns(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  int local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20 [4];
  
  local_2c = 0;
  tmp_i2 = *(int *)(param_1 + 0x250);
  if (tmp_i2 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i2 = *(int *)(param_1 + 0x250);
    if (tmp_i2 == 0) {
      return 0;
    }
  }
  tmp_i1 = PC_Int_Parse(param_2,&local_2c);
  if (tmp_i1 == 0) {
    return 0;
  }
  if (local_2c < 0x11) {
    *(int *)(tmp_i2 + 0x1c) = local_2c;
    if (local_2c < 1) {
      return 1;
    }
  }
  else {
    local_2c = 0x10;
    *(uint32_t *)(tmp_i2 + 0x1c) = 0x10;
  }
  tmp_i1 = 0;
  tmp_pu3 = (uint32_t *)(tmp_i2 + 0x20);
  do {
    local_28 = 0;
    local_24 = 0;
    local_20[0] = 0;
    tmp_i2 = PC_Int_Parse(param_2,&local_28);
    if (tmp_i2 == 0) {
      return 0;
    }
    tmp_i2 = PC_Int_Parse(param_2,&local_24);
    if (tmp_i2 == 0) {
      return 0;
    }
    tmp_i2 = PC_Int_Parse(param_2,local_20);
    if (tmp_i2 == 0) {
      return 0;
    }
    tmp_i1 = tmp_i1 + 1;
    *tmp_pu3 = local_28;
    tmp_pu3[1] = local_24;
    tmp_pu3[2] = local_20[0];
    tmp_pu3 = tmp_pu3 + 3;
  } while (tmp_i1 < local_2c);
  return 1;
}

bool ItemParse_contextMenu(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
    if (tmp_i1 == 0) {
      return false;
    }
  }
  tmp_i1 = PC_String_Parse(param_2,tmp_i1 + 0xe4);
  return tmp_i1 != 0;
}

uint32_t ItemParse_cvar(int param_1,uint32_t param_2)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  uint32_t tmp_u3;
  
  if (*(int *)(param_1 + 0x250) == 0) {
    Item_ValidateTypeData_part_21();
  }
  tmp_i2 = PC_String_Parse(param_2,param_1 + 0x114);
  tmp_u3 = 0;
  if (tmp_i2 != 0) {
    Q_strlwr(*(uint32_t *)(param_1 + 0x114));
    tmp_pu1 = *(uint32_t **)(param_1 + 0x250);
    if (tmp_pu1 != (uint32_t *)0x0) {
      *tmp_pu1 = 0xbf800000;
      tmp_pu1[1] = 0xbf800000;
      tmp_pu1[2] = 0xbf800000;
      return 1;
    }
    tmp_u3 = 1;
  }
  return tmp_u3;
}

uint32_t ItemParse_maxChars(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t local_10 [2];
  
  local_10[0] = 0;
  if (((*(int *)(param_1 + 0x250) != 0) ||
      (Item_ValidateTypeData_part_21(), *(int *)(param_1 + 0x250) != 0)) &&
     (tmp_i1 = PC_Int_Parse(param_2,local_10), tmp_i1 != 0)) {
    *(uint32_t *)(*(int *)(param_1 + 0x250) + 0x10) = local_10[0];
    return 1;
  }
  return 0;
}

uint32_t ItemParse_maxPaintChars(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t local_10 [2];
  
  local_10[0] = 0;
  if (((*(int *)(param_1 + 0x250) != 0) ||
      (Item_ValidateTypeData_part_21(), *(int *)(param_1 + 0x250) != 0)) &&
     (tmp_i1 = PC_Int_Parse(param_2,local_10), tmp_i1 != 0)) {
    *(uint32_t *)(*(int *)(param_1 + 0x250) + 0x14) = local_10[0];
    return 1;
  }
  return 0;
}

bool ItemParse_cvarFloat(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = *(int *)(param_1 + 0x250);
  if (tmp_i2 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i2 = *(int *)(param_1 + 0x250);
    if (tmp_i2 == 0) {
      return false;
    }
  }
  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x114);
  if (((tmp_i1 != 0) && (tmp_i1 = PC_Float_Parse(param_2,tmp_i2 + 8), tmp_i1 != 0)) &&
     (tmp_i1 = PC_Float_Parse(param_2,tmp_i2), tmp_i1 != 0)) {
    tmp_i2 = PC_Float_Parse(param_2,tmp_i2 + 4);
    return tmp_i2 != 0;
  }
  return false;
}

void UI_InitMemory(void)
{
  allocPoint = 0;
  outOfMemory = 0;
  return;
}

uint32_t UI_OutOfMemory(void)
{
  return outOfMemory;
}

char * String_Alloc(char *param_1)
{
  char tmp_c1;
  uint16_t tmp_u2;
  uint32_t *tmp_pu3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  void *tmp_pc6;
  __int32_t **pp_Var7;
  int tmp_i8;
  size_t tmp_s9;
  uint tmp_u10;
  uint tmp_u11;
  uint tmp_u12;
  uint32_t *tmp_pu13;
  char *tmp_pc14;
  char *tmp_pc15;
  byte tmp_b16;
  
  tmp_b16 = 0;
  if (param_1 != (char *)0x0) {
    tmp_c1 = *param_1;
    if (tmp_c1 == '\0') {
      return "";
    }
    pp_Var7 = __ctype_tolower_loc();
    tmp_u10 = 0;
    tmp_i8 = 0x77;
    do {
      tmp_u10 = tmp_u10 + (char)(*pp_Var7)[tmp_c1] * tmp_i8;
      tmp_c1 = param_1[tmp_i8 + -0x76];
      tmp_i8 = tmp_i8 + 1;
    } while (tmp_c1 != '\0');
    tmp_pu3 = (uint32_t *)(&strHandle)[tmp_u10 & 0x7ff];
    tmp_pu13 = tmp_pu3;
    if (tmp_pu3 == (uint32_t *)0x0) {
      tmp_s9 = strlen(param_1);
      if ((int)(strPoolIndex + tmp_s9) < 0x5ffff) {
        tmp_pc4 = strPool + strPoolIndex;
        tmp_u11 = tmp_s9 + 1;
        tmp_u12 = tmp_u11;
        tmp_pc15 = tmp_pc4;
        if (7 < tmp_u11) {
          if (((uint)tmp_pc4 & 1) != 0) {
            tmp_c1 = *param_1;
            tmp_pc15 = strPool + strPoolIndex + 1;
            param_1 = param_1 + 1;
            *tmp_pc4 = tmp_c1;
            tmp_u12 = tmp_s9;
          }
          tmp_pc14 = tmp_pc15;
          if (((uint)tmp_pc15 & 2) != 0) {
            tmp_u2 = *(uint16_t *)param_1;
            tmp_pc14 = tmp_pc15 + 2;
            param_1 = param_1 + 2;
            tmp_u12 = tmp_u12 - 2;
            *(uint16_t *)tmp_pc15 = tmp_u2;
          }
          tmp_pc15 = tmp_pc14;
          if (((uint)tmp_pc14 & 4) != 0) {
            tmp_u5 = *(uint32_t *)param_1;
            tmp_pc15 = tmp_pc14 + 4;
            param_1 = param_1 + 4;
            tmp_u12 = tmp_u12 - 4;
            *(uint32_t *)tmp_pc14 = tmp_u5;
          }
        }
        for (; tmp_i8 = allocPoint, tmp_u12 != 0; tmp_u12 = tmp_u12 - 1) {
          *tmp_pc15 = *param_1;
          param_1 = param_1 + (uint)tmp_b16 * -2 + 1;
          tmp_pc15 = tmp_pc15 + (uint)tmp_b16 * -2 + 1;
        }
        strPoolIndex = strPoolIndex + tmp_u11;
        if (allocPoint < 0x1ffff9) {
          tmp_pu3 = (uint32_t *)(memoryPool + allocPoint);
          allocPoint = allocPoint + 0x10;
          (&strHandle)[tmp_u10 & 0x7ff] = tmp_pu3;
          *tmp_pu3 = 0;
          *(char **)(memoryPool + tmp_i8 + 4) = tmp_pc4;
          return tmp_pc4;
        }
        goto LAB_000eec70;
      }
    }
    else {
      do {
        tmp_pc4 = (char *)tmp_pu13[1];
        tmp_i8 = strcmp(param_1,tmp_pc4);
        if (tmp_i8 == 0) {
          return tmp_pc4;
        }
        tmp_pu13 = (uint32_t *)*tmp_pu13;
      } while (tmp_pu13 != (uint32_t *)0x0);
      tmp_s9 = strlen(param_1);
      if ((int)(tmp_s9 + strPoolIndex) < 0x5ffff) {
        tmp_u10 = tmp_s9 + 1;
        tmp_pc4 = strPool + strPoolIndex;
        tmp_u11 = tmp_u10;
        tmp_pc15 = tmp_pc4;
        if (7 < tmp_u10) {
          if (((uint)tmp_pc4 & 1) != 0) {
            tmp_c1 = *param_1;
            tmp_pc15 = strPool + strPoolIndex + 1;
            param_1 = param_1 + 1;
            *tmp_pc4 = tmp_c1;
            tmp_u11 = tmp_s9;
          }
          tmp_pc14 = tmp_pc15;
          if (((uint)tmp_pc15 & 2) != 0) {
            tmp_u2 = *(uint16_t *)param_1;
            tmp_pc14 = tmp_pc15 + 2;
            param_1 = param_1 + 2;
            tmp_u11 = tmp_u11 - 2;
            *(uint16_t *)tmp_pc15 = tmp_u2;
          }
          tmp_pc15 = tmp_pc14;
          if (((uint)tmp_pc14 & 4) != 0) {
            tmp_u5 = *(uint32_t *)param_1;
            tmp_pc15 = tmp_pc14 + 4;
            param_1 = param_1 + 4;
            tmp_u11 = tmp_u11 - 4;
            *(uint32_t *)tmp_pc14 = tmp_u5;
          }
        }
        for (; tmp_i8 = allocPoint, tmp_u11 != 0; tmp_u11 = tmp_u11 - 1) {
          *tmp_pc15 = *param_1;
          param_1 = param_1 + (uint)tmp_b16 * -2 + 1;
          tmp_pc15 = tmp_pc15 + (uint)tmp_b16 * -2 + 1;
        }
        strPoolIndex = strPoolIndex + tmp_u10;
        for (tmp_pu13 = (uint32_t *)*tmp_pu3; tmp_pu13 != (uint32_t *)0x0;
            tmp_pu13 = (uint32_t *)*tmp_pu13) {
          tmp_pu3 = tmp_pu13;
        }
        if (allocPoint < 0x1ffff9) {
          tmp_pu13 = (uint32_t *)(memoryPool + allocPoint);
          allocPoint = allocPoint + 0x10;
          *tmp_pu13 = 0;
          *(char **)(memoryPool + tmp_i8 + 4) = tmp_pc4;
          *tmp_pu3 = tmp_pu13;
          return tmp_pc4;
        }
LAB_000eec70:
        outOfMemory = 1;
        if (*(void **)(DC + 0xd0) != (void *)0x0) {
          (**(void **)(DC + 0xd0))("UI_Alloc: Failure. Out of memory!\n");
        }
        _DAT_00000000 = 0;
        tmp_pc6 = (void *)invalidInstructionException();
        (*tmp_pc6)();
      }
    }
  }
  return (char *)0x0;
}

bool ItemParse_textfile(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t local_424 [16];
  uint8_t local_414 [1040];
  
  tmp_i1 = trap_PC_ReadToken(param_2,local_424);
  if (tmp_i1 != 0) {
    tmp_u2 = (**(void **)(DC + 0x98))(local_414);
    tmp_u2 = String_Alloc(tmp_u2);
    *(uint32_t *)(param_1 + 0xe8) = tmp_u2;
  }
  return tmp_i1 != 0;
}

uint32_t ItemParse_cvarStrList(int param_1,uint32_t param_2)
{
  bool tmp_b1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint8_t local_434 [16];
  char local_424 [1044];
  
  tmp_i4 = *(int *)(param_1 + 0x250);
  if (tmp_i4 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i4 = *(int *)(param_1 + 0x250);
    if (tmp_i4 == 0) {
      return 0;
    }
  }
  *(uint32_t *)(tmp_i4 + 0x180) = 0;
  *(uint32_t *)(tmp_i4 + 0x184) = 1;
  tmp_i2 = trap_PC_ReadToken(param_2,local_434);
  if ((tmp_i2 != 0) && (local_424[0] == '{')) {
    tmp_b1 = false;
    while (tmp_i2 = trap_PC_ReadToken(param_2,local_434), tmp_i2 != 0) {
      if (local_424[0] == '}') {
        return 1;
      }
      if ((local_424[0] != ';') && (local_424[0] != ',')) {
        tmp_i2 = *(int *)(tmp_i4 + 0x180);
        if (tmp_b1) {
          tmp_u3 = String_Alloc(local_424);
          *(uint32_t *)(tmp_i4 + 0x80 + tmp_i2 * 4) = tmp_u3;
          tmp_i2 = *(int *)(tmp_i4 + 0x180) + 1;
          *(int *)(tmp_i4 + 0x180) = tmp_i2;
          if (0x1f < tmp_i2) {
            return 0;
          }
          tmp_b1 = false;
        }
        else {
          tmp_u3 = String_Alloc(local_424);
          *(uint32_t *)(tmp_i4 + tmp_i2 * 4) = tmp_u3;
          tmp_b1 = true;
        }
      }
    }
    PC_SourceError(param_2,"end of file inside menu item\n");
  }
  return 0;
}

uint32_t ItemParse_cvarFloatList(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint8_t local_434 [16];
  char local_424 [1044];
  
  tmp_i3 = *(int *)(param_1 + 0x250);
  if (tmp_i3 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i3 = *(int *)(param_1 + 0x250);
    if (tmp_i3 == 0) {
      return 0;
    }
  }
  *(uint32_t *)(tmp_i3 + 0x180) = 0;
  *(uint32_t *)(tmp_i3 + 0x184) = 0;
  tmp_i1 = trap_PC_ReadToken(param_2,local_434);
  if ((tmp_i1 != 0) && (local_424[0] == '{')) {
    while (tmp_i1 = trap_PC_ReadToken(param_2,local_434), tmp_i1 != 0) {
      if (local_424[0] == '}') {
        return 1;
      }
      if ((local_424[0] != ';') && (local_424[0] != ',')) {
        tmp_i1 = *(int *)(tmp_i3 + 0x180);
        tmp_u2 = String_Alloc(local_424);
        *(uint32_t *)(tmp_i3 + tmp_i1 * 4) = tmp_u2;
        tmp_i1 = PC_Float_Parse(param_2,*(int *)(tmp_i3 + 0x180) * 4 + 0x100 + tmp_i3);
        if (tmp_i1 == 0) {
          return 0;
        }
        tmp_i1 = *(int *)(tmp_i3 + 0x180) + 1;
        *(int *)(tmp_i3 + 0x180) = tmp_i1;
        if (0x1f < tmp_i1) {
          return 0;
        }
      }
    }
    PC_SourceError(param_2,"end of file inside menu item\n");
  }
  return 0;
}

uint32_t ItemParse_cvarListUndefined(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint8_t local_424 [16];
  uint8_t local_414 [1032];
  
  tmp_i3 = *(int *)(param_1 + 0x250);
  if (tmp_i3 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i3 = *(int *)(param_1 + 0x250);
    if (tmp_i3 == 0) {
      return 0;
    }
  }
  *(uint32_t *)(tmp_i3 + 0x188) = 0;
  tmp_i1 = trap_PC_ReadToken(param_2,local_424);
  if (tmp_i1 == 0) {
    return 0;
  }
  tmp_u2 = String_Alloc(local_414);
  *(uint32_t *)(tmp_i3 + 0x188) = tmp_u2;
  return 1;
}

void Script_SetAsset(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    String_Alloc();
    return;
  }
  return;
}

void Script_ClearCvar(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    (**(void **)(DC + 0x78))(tmp_u2,&g_unk_0011d841);
  }
  return;
}

void Script_SetPlayerModel(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    (**(void **)(DC + 0x78))("team_model",tmp_u2);
  }
  return;
}

void Script_SetPlayerHead(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    (**(void **)(DC + 0x78))("team_headmodel",tmp_u2);
  }
  return;
}

void Script_SetBackground(int param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_u2 = (*(void *)*DC)(tmp_u2);
    *(uint32_t *)(param_1 + 0xb4) = tmp_u2;
  }
  return;
}

void Script_Exec(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  void *tmp_pc1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_pc1 = *(void **)(DC + 200);
    tmp_u3 = va("%s ; ",tmp_u3);
    (*tmp_pc1)(2,tmp_u3);
  }
  return;
}

void Script_ExecNOW(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  void *tmp_pc1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_pc1 = *(void **)(DC + 200);
    tmp_u3 = va("%s ; ",tmp_u3);
    (*tmp_pc1)(0,tmp_u3);
  }
  return;
}

void Script_Play(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  void *tmp_pc1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_pc1 = *(void **)(DC + 0x88);
    tmp_u3 = (**(void **)(DC + 0xdc))(tmp_u3,0);
    (*tmp_pc1)(tmp_u3,6);
  }
  return;
}

void Script_playLooped(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    (**(void **)(DC + 0xe4))();
    (**(void **)(DC + 0xe0))(tmp_u2,tmp_u2,0);
  }
  return;
}

void Script_SetColor(int param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  double tmp_d5;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_i3 = Q_stricmp(tmp_u2,"backcolor");
    if (tmp_i3 == 0) {
      *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x400000;
      tmp_i3 = param_1 + 0x84;
    }
    else {
      tmp_i3 = Q_stricmp(tmp_u2,"forecolor");
      if (tmp_i3 == 0) {
        tmp_i3 = param_1 + 0x74;
        *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x200;
      }
      else {
        tmp_i3 = Q_stricmp(tmp_u2,"bordercolor");
        if (tmp_i3 != 0) {
          return;
        }
        tmp_i3 = param_1 + 0x94;
      }
    }
    if (tmp_i3 != 0) {
      tmp_i4 = 0;
      do {
        tmp_pc1 = (char *)COM_ParseExt(param_3,0);
        if (tmp_pc1 == (char *)0x0) {
          return;
        }
        if (*tmp_pc1 == '\0') {
          return;
        }
        tmp_d5 = strtod(tmp_pc1,(char **)0x0);
        *(float *)(tmp_i3 + tmp_i4 * 4) = (float)tmp_d5;
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 != 4);
    }
  }
  return;
}

void Script_SetCvar(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_pc1 = (char *)COM_ParseExt(param_3,0);
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_u3 = String_Alloc(tmp_pc1);
      (**(void **)(DC + 0x78))(tmp_u2,tmp_u3);
      return;
    }
  }
  return;
}

void Script_CopyCvar(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint8_t local_11c [268];
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_pc1 = (char *)COM_ParseExt(param_3,0);
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_u3 = String_Alloc(tmp_pc1);
      (**(void **)(DC + 0x70))(tmp_u2,local_11c,0x100);
      (**(void **)(DC + 0x78))(tmp_u3,local_11c);
    }
  }
  return;
}

void Script_ToggleCvarBit(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  void *tmp_pc1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  uint tmp_u4;
  uint tmp_u5;
  uint32_t tmp_u6;
  char local_11c [268];
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_pc2 = (char *)COM_ParseExt(param_3,0);
    if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
      tmp_pc2 = (char *)String_Alloc(tmp_pc2);
      (**(void **)(DC + 0x70))(tmp_u3,local_11c,0x100);
      tmp_u4 = strtol(local_11c,(char **)0x0,10);
      tmp_u5 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_pc1 = *(void **)(DC + 0x78);
      tmp_u6 = va("%i",tmp_u4 ^ tmp_u5);
      (*tmp_pc1)(tmp_u3,tmp_u6);
    }
  }
  return;
}

void Item_RunScript_constprop_37(int param_1,char *param_2)
{
  char *tmp_pc1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  int *tmp_pi5;
  int *local_1024;
  int local_1020 [1028];
  
  tmp_u3 = 0x1000;
  local_1024 = local_1020 + 1;
  local_1020[0] = 0;
  tmp_pi5 = local_1024;
  if (((uint)local_1024 & 4) != 0) {
    tmp_u3 = 0xffc;
    local_1020[1] = 0;
    tmp_pi5 = local_1020 + 2;
  }
  for (tmp_u3 = tmp_u3 >> 2; tmp_u3 != 0; tmp_u3 = tmp_u3 - 1) {
    *tmp_pi5 = 0;
    tmp_pi5 = tmp_pi5 + 1;
  }
  if (((param_1 == 0) || (param_2 == (char *)0x0)) || (*param_2 == '\0')) {
    return;
  }
  Q_strcat(local_1024,0x1000,param_2);
LAB_000ef890:
  do {
    do {
      tmp_pc1 = (char *)COM_ParseExt(&local_1024,0);
      if (tmp_pc1 == (char *)0x0) {
        return;
      }
      if (*tmp_pc1 == '\0') {
        return;
      }
      tmp_pc1 = (char *)String_Alloc(tmp_pc1);
    } while ((*tmp_pc1 == ';') && (tmp_pc1[1] == '\0'));
    tmp_i4 = 0;
    if (0 < scriptCommandCount) {
      do {
        tmp_i2 = Q_stricmp(tmp_pc1,(&commandList)[tmp_i4 * 2]);
        if (tmp_i2 == 0) {
          (*(void *)(&g_ptr_Script_FadeIn_0014b164)[tmp_i4 * 2])(param_1,local_1020,&local_1024);
          if (local_1020[0] != 0) {
            return;
          }
          goto LAB_000ef890;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 < scriptCommandCount);
    }
    (**(void **)(DC + 0x68))(&local_1024);
  } while( true );
}

void Menu_RunCloseScript_part_10(int param_1)
{
  if (*(int *)(param_1 + 0xdc) != 0) {
    Item_RunScript_constprop_37();
  }
  return;
}

void Script_CloseAllOtherMenus(int param_1)
{
  uint tmp_u1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  
  if (0 < menuCount) {
    tmp_pu3 = &Menus;
    tmp_i4 = 0;
    tmp_i2 = menuCount;
    do {
      if (tmp_pu3 != *(uint32_t **)(param_1 + 0xec)) {
        tmp_u1 = tmp_pu3[0x12];
        if ((tmp_u1 & 4) != 0) {
          Menu_RunCloseScript_part_10();
          tmp_u1 = tmp_pu3[0x12];
          tmp_i2 = menuCount;
        }
        tmp_pu3[0x12] = tmp_u1 & 0xfffffff8;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu3 = tmp_pu3 + 0x346;
    } while (tmp_i4 < tmp_i2);
  }
  return;
}

void Script_CloseAll(void)
{
  int tmp_i1;
  uint tmp_u2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  
  if (0 < menuCount) {
    tmp_pu3 = &Menus;
    tmp_i4 = 0;
    tmp_i1 = menuCount;
    do {
      tmp_u2 = tmp_pu3[0x12];
      if ((tmp_u2 & 4) != 0) {
        Menu_RunCloseScript_part_10();
        tmp_u2 = tmp_pu3[0x12];
        tmp_i1 = menuCount;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu3[0x12] = tmp_u2 & 0xfffffff8;
      tmp_pu3 = tmp_pu3 + 0x346;
    } while (tmp_i4 < tmp_i1);
  }
  return;
}

void Script_FadeOutMenu(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if (((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) &&
     (tmp_u3 = String_Alloc(tmp_pc2), 0 < menuCount)) {
    tmp_pu6 = &g_unk_040f8f60;
    tmp_i5 = 0;
    do {
      tmp_i4 = Q_stricmp(*tmp_pu6,tmp_u3);
      if (tmp_i4 == 0) {
        if ((int)(&g_unk_040f9000)[tmp_i5 * 0x346] < 1) {
          return;
        }
        tmp_i4 = 0;
        do {
          tmp_i1 = tmp_i5 * 0x346 + tmp_i4;
          tmp_i4 = tmp_i4 + 1;
          *(uint *)((&g_unk_040f9454)[tmp_i1] + 0x48) =
               *(uint *)((&g_unk_040f9454)[tmp_i1] + 0x48) & 0xffffffbf | 0x24;
        } while (tmp_i4 < (int)(&g_unk_040f9000)[tmp_i5 * 0x346]);
        return;
      }
      tmp_i5 = tmp_i5 + 1;
      tmp_pu6 = tmp_pu6 + 0x346;
    } while (tmp_i5 < menuCount);
  }
  return;
}

void Script_FadeInMenu(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if (((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) &&
     (tmp_u3 = String_Alloc(tmp_pc2), 0 < menuCount)) {
    tmp_pu6 = &g_unk_040f8f60;
    tmp_i5 = 0;
    do {
      tmp_i4 = Q_stricmp(*tmp_pu6,tmp_u3);
      if (tmp_i4 == 0) {
        if ((int)(&g_unk_040f9000)[tmp_i5 * 0x346] < 1) {
          return;
        }
        tmp_i4 = 0;
        do {
          tmp_i1 = tmp_i5 * 0x346 + tmp_i4;
          tmp_i4 = tmp_i4 + 1;
          *(uint *)((&g_unk_040f9454)[tmp_i1] + 0x48) =
               *(uint *)((&g_unk_040f9454)[tmp_i1] + 0x48) & 0xffffffdf | 0x44;
        } while (tmp_i4 < (int)(&g_unk_040f9000)[tmp_i5 * 0x346]);
        return;
      }
      tmp_i5 = tmp_i5 + 1;
      tmp_pu6 = tmp_pu6 + 0x346;
    } while (tmp_i5 < menuCount);
  }
  return;
}

void String_Report(void)
{
  Com_Printf("Memory/String Pool Info\n");
  Com_Printf("----------------\n");
  Com_Printf("String Pool is %.1f%% full, %i bytes out of %i used.\n",
             (double)(((float)strPoolIndex / 393216.0) * 100.0),strPoolIndex,0x60000);
  Com_Printf("Memory Pool is %.1f%% full, %i bytes out of %i used.\n",
             (double)((float)allocPoint * 4.7683716e-07 * 100.0),allocPoint,0x200000);
  return;
}

uint32_t Float_Parse(uint32_t param_1,float *param_2)
{
  char *__nptr;
  uint32_t tmp_u1;
  double tmp_d2;
  
  __nptr = (char *)COM_ParseExt(param_1,0);
  tmp_u1 = 0;
  if ((__nptr != (char *)0x0) && (*__nptr != '\0')) {
    tmp_d2 = strtod(__nptr,(char **)0x0);
    *param_2 = (float)tmp_d2;
    tmp_u1 = 1;
  }
  return tmp_u1;
}

uint32_t Color_Parse(uint32_t param_1,int param_2)
{
  char *__nptr;
  int tmp_i1;
  double tmp_d2;
  
  tmp_i1 = 0;
  while ((__nptr = (char *)COM_ParseExt(param_1,0), __nptr != (char *)0x0 && (*__nptr != '\0'))) {
    tmp_d2 = strtod(__nptr,(char **)0x0);
    *(float *)(param_2 + tmp_i1 * 4) = (float)tmp_d2;
    tmp_i1 = tmp_i1 + 1;
    if (tmp_i1 == 4) {
      return 1;
    }
  }
  return 0;
}

uint32_t Int_Parse(uint32_t param_1,long *param_2)
{
  char *__nptr;
  uint32_t tmp_u1;
  long tmp_l2;
  
  __nptr = (char *)COM_ParseExt(param_1,0);
  tmp_u1 = 0;
  if ((__nptr != (char *)0x0) && (*__nptr != '\0')) {
    tmp_l2 = strtol(__nptr,(char **)0x0,10);
    *param_2 = tmp_l2;
    tmp_u1 = 1;
  }
  return tmp_u1;
}

bool Rect_Parse(uint32_t param_1,float *param_2)
{
  char *tmp_pc1;
  int tmp_i2;
  double tmp_d3;
  
  tmp_pc1 = (char *)COM_ParseExt(param_1,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_d3 = strtod(tmp_pc1,(char **)0x0);
    *param_2 = (float)tmp_d3;
    tmp_pc1 = (char *)COM_ParseExt(param_1,0);
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_d3 = strtod(tmp_pc1,(char **)0x0);
      param_2[1] = (float)tmp_d3;
      tmp_pc1 = (char *)COM_ParseExt(param_1,0);
      if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
        tmp_d3 = strtod(tmp_pc1,(char **)0x0);
        param_2[2] = (float)tmp_d3;
        tmp_i2 = Float_Parse(param_1,param_2 + 3);
        return tmp_i2 != 0;
      }
    }
  }
  return false;
}

uint32_t String_Parse(uint32_t param_1,uint32_t *param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)COM_ParseExt(param_1,0);
  tmp_u2 = 0;
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    *param_2 = tmp_u2;
    tmp_u2 = 1;
  }
  return tmp_u2;
}

bool ItemParse_onEsc(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x268);
  return tmp_i1 != 0;
}

bool ItemParse_onEnter(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x26c);
  return tmp_i1 != 0;
}

bool ItemParse_onFocus(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x10c);
  return tmp_i1 != 0;
}

bool ItemParse_leaveFocus(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x110);
  return tmp_i1 != 0;
}

bool ItemParse_mouseEnter(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xfc);
  return tmp_i1 != 0;
}

bool ItemParse_mouseExit(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x100);
  return tmp_i1 != 0;
}

bool ItemParse_mouseEnterText(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xf4);
  return tmp_i1 != 0;
}

bool ItemParse_mouseExitText(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xf8);
  return tmp_i1 != 0;
}

bool ItemParse_action(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x104);
  return tmp_i1 != 0;
}

bool ItemParse_accept(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x108);
  return tmp_i1 != 0;
}

bool ItemParse_enableCvar(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x11c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x120) = 1;
  }
  return tmp_i1 != 0;
}

bool ItemParse_disableCvar(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x11c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x120) = 2;
  }
  return tmp_i1 != 0;
}

bool ItemParse_showCvar(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x11c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x120) = 4;
  }
  return tmp_i1 != 0;
}

bool ItemParse_hideCvar(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x11c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x120) = 8;
  }
  return tmp_i1 != 0;
}

bool ItemParse_execKey(int param_1,uint32_t param_2)
{
  int tmp_i1;
  bool tmp_b2;
  char local_d [9];
  
  tmp_i1 = PC_Char_Parse(param_2,local_d);
  tmp_b2 = false;
  if (tmp_i1 != 0) {
    *(int *)(param_1 + 0x254) = (int)local_d[0];
    tmp_i1 = PC_Script_Parse(param_2,param_1 + 600);
    tmp_b2 = tmp_i1 != 0;
  }
  return tmp_b2;
}

bool MenuParse_onOpen(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xd8);
  return tmp_i1 != 0;
}

bool MenuParse_onClose(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xdc);
  return tmp_i1 != 0;
}

bool MenuParse_onESC(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xe0);
  return tmp_i1 != 0;
}

bool MenuParse_onEnter(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xe4);
  return tmp_i1 != 0;
}

bool MenuParse_onTimeout(int param_1,uint32_t param_2)
{
  int tmp_i1;
  bool tmp_b2;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xe8);
  tmp_b2 = false;
  if (tmp_i1 != 0) {
    tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xf0);
    tmp_b2 = tmp_i1 != 0;
  }
  return tmp_b2;
}

bool MenuParse_execKey(int param_1,uint32_t param_2)
{
  int tmp_i1;
  bool tmp_b2;
  char local_d [9];
  
  local_d[0] = '\0';
  tmp_i1 = PC_Char_Parse(param_2,local_d);
  tmp_b2 = false;
  if (tmp_i1 != 0) {
    tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xf4 + local_d[0] * 4);
    tmp_b2 = tmp_i1 != 0;
  }
  return tmp_b2;
}

bool MenuParse_execKeyInt(int param_1,uint32_t param_2)
{
  int tmp_i1;
  bool tmp_b2;
  int local_10 [2];
  
  local_10[0] = 0;
  tmp_i1 = PC_Int_Parse(param_2,local_10);
  tmp_b2 = false;
  if (tmp_i1 != 0) {
    tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xf4 + local_10[0] * 4);
    tmp_b2 = tmp_i1 != 0;
  }
  return tmp_b2;
}

bool ItemParse_doubleClick(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
    if (tmp_i1 == 0) {
      return false;
    }
  }
  tmp_i1 = PC_Script_Parse(param_2,tmp_i1 + 0xe0);
  return tmp_i1 != 0;
}

void Init_Display(uint32_t param_1)
{
  DC = param_1;
  return;
}

void GradientBar_Paint(uint32_t *param_1,uint32_t param_2)
{
  (**(void **)(DC + 4))(param_2);
  (**(void **)(DC + 8))(*param_1,param_1[1],param_1[2],param_1[3],*(uint32_t *)(DC + 0x1e2d8));
  (**(void **)(DC + 4))(0);
  return;
}

void Window_Init(uint16_t *param_1)
{
  bool tmp_b1;
  uint tmp_u2;
  uint16_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint tmp_u5;
  
  tmp_u5 = 0xb8;
  tmp_b1 = false;
  if (((uint)param_1 & 1) == 0) {
    tmp_pu3 = param_1;
    if (((uint)param_1 & 2) == 0) goto LAB_000f076b;
  }
  else {
    tmp_pu3 = (uint16_t *)((int)param_1 + 1);
    tmp_u5 = 0xb7;
    tmp_b1 = true;
    *(uint8_t *)param_1 = 0;
    if (((uint)tmp_pu3 & 2) == 0) goto LAB_000f076b;
    tmp_u5 = 0xb7;
    tmp_b1 = true;
  }
  *tmp_pu3 = 0;
  tmp_u5 = tmp_u5 - 2;
  tmp_pu3 = tmp_pu3 + 1;
LAB_000f076b:
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

void Fade(uint *param_1,float *param_2,float param_3,int *param_4,int param_5,int param_6,
         float param_7)

{
  float tmp_f1;
  
  if ((*param_1 & 0x60) != 0) {
    if (*param_4 < *(int *)(DC + 0x11c)) {
      *param_4 = *(int *)(DC + 0x11c) + param_5;
      if ((*param_1 & 0x20) == 0) {
        if (param_7 + *param_2 < param_3) {
          *param_2 = param_7 + *param_2;
          return;
        }
        *param_2 = param_3;
        if (param_6 != 0) {
          *param_1 = *param_1 & 0xffffffbf;
          return;
        }
      }
      else {
        tmp_f1 = *param_2;
        *param_2 = tmp_f1 - param_7;
        if ((tmp_f1 - param_7 <= 0.0) && (param_6 != 0)) {
          *param_1 = *param_1 & 0xffffffdb;
        }
      }
    }
  }
  return;
}

void Window_Paint(float *param_1,float param_2,float param_3,float param_4)
{
  float tmp_f1;
  int tmp_i2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float *pfVar8;
  float local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_10 = 0xf08c8;
  tmp_f7 = *param_1;
  tmp_f4 = param_1[1];
  tmp_f5 = param_1[2];
  tmp_f6 = param_1[3];
  if (debugMode != 0) {
    local_10 = 0x3f800000;
    local_14 = 0x3f800000;
    local_18 = 0x3f800000;
    local_1c = 1.0;
    (**(void **)(DC + 0x40))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,0x3f800000,&local_1c);
  }
  tmp_i2 = DC;
  tmp_f3 = param_1[0xd];
  if (tmp_f3 == 0.0) {
    if (param_1[0xe] == 0.0) {
      return;
    }
LAB_000f0900:
    tmp_f1 = param_1[0x11];
    tmp_f7 = tmp_f7 + tmp_f1;
    tmp_f4 = tmp_f4 + tmp_f1;
    tmp_f5 = tmp_f5 - (tmp_f1 + tmp_f1);
    tmp_f6 = tmp_f6 - (tmp_f1 + tmp_f1);
    if (tmp_f3 == 1.4013e-45) goto LAB_000f0994;
LAB_000f0916:
    if (tmp_f3 != 2.8026e-45) {
      if (tmp_f3 != 4.2039e-45) {
        if (tmp_f3 == 5.60519e-45) {
          if (*(void **)(DC + 0x6c) != (void *)0x0) {
            (**(void **)(DC + 0x6c))(&local_1c);
            (**(void **)(DC + 0x3c))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,&local_1c);
          }
        }
        else if (tmp_f3 == 7.00649e-45) {
          tmp_f3 = param_1[0xc];
          if (tmp_f3 == -NAN) {
            tmp_f3 = (float)(**(void **)(DC + 0xe8))(param_1[0xb],tmp_f7,tmp_f4,tmp_f5,tmp_f6);
            if (tmp_f3 == -NAN) {
              param_1[0xc] = -NAN;
              goto LAB_000f0942;
            }
            param_1[0xc] = tmp_f3;
          }
          if (-1 < (int)tmp_f3) {
            (**(void **)(DC + 0xf4))(tmp_f3);
            (**(void **)(DC + 0xf0))(param_1[0xc],tmp_f7,tmp_f4,tmp_f5,tmp_f6);
          }
        }
        goto LAB_000f0942;
      }
      if ((*(byte *)((int)param_1 + 0x49) & 2) != 0) {
        (**(void **)(DC + 4))(param_1 + 0x1d);
      }
      tmp_f3 = param_1[0x2d];
      goto LAB_000f0a74;
    }
    (**(void **)(DC + 4))(param_1 + 0x21);
    (**(void **)(DC + 8))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,*(uint32_t *)(DC + 0x1e2d8));
    (**(void **)(DC + 4))(0);
  }
  else {
    if (param_1[0xe] != 0.0) goto LAB_000f0900;
    if (tmp_f3 != 1.4013e-45) goto LAB_000f0916;
LAB_000f0994:
    if (param_1[0x2d] != 0.0) {
      tmp_f3 = param_1[0x12];
      if ((((uint)tmp_f3 & 0x60) != 0) && ((int)param_1[0x1c] < *(int *)(DC + 0x11c))) {
        param_1[0x1c] = (float)(*(int *)(DC + 0x11c) + (int)ROUND(param_4));
        if (((uint)tmp_f3 & 0x20) == 0) {
          if (param_2 + param_1[0x24] < param_3) {
            param_1[0x24] = param_2 + param_1[0x24];
          }
          else {
            param_1[0x12] = (float)((uint)tmp_f3 & 0xffffffbf);
            param_1[0x24] = param_3;
          }
        }
        else {
          tmp_f1 = param_1[0x24];
          param_1[0x24] = tmp_f1 - param_2;
          if (tmp_f1 - param_2 <= 0.0) {
            param_1[0x12] = (float)((uint)tmp_f3 & 0xffffffdb);
          }
        }
      }
      (**(void **)(tmp_i2 + 4))(param_1 + 0x21);
      tmp_f3 = param_1[0x2d];
LAB_000f0a74:
      (**(void **)(DC + 8))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,tmp_f3);
      (**(void **)(DC + 4))(0);
      tmp_f7 = param_1[0xe];
      goto joined_r0x000f0a96;
    }
    (**(void **)(DC + 0x3c))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,param_1 + 0x21);
  }
LAB_000f0942:
  tmp_f7 = param_1[0xe];
joined_r0x000f0a96:
  if (tmp_f7 != 1.4013e-45) {
    if (tmp_f7 == 2.8026e-45) {
      (**(void **)(DC + 4))(param_1 + 0x25);
      (**(void **)(DC + 0x48))(*param_1,param_1[1],param_1[2],param_1[3],param_1[0x11]);
      (**(void **)(DC + 4))(0);
    }
    else if (tmp_f7 == 4.2039e-45) {
      (**(void **)(DC + 4))(param_1 + 0x25);
      (**(void **)(DC + 0x44))(*param_1,param_1[1],param_1[2],param_1[3],param_1[0x11]);
      (**(void **)(DC + 4))(0);
    }
    else if (tmp_f7 == 5.60519e-45) {
      tmp_f7 = *param_1;
      tmp_f4 = param_1[1];
      tmp_f5 = param_1[2];
      tmp_f6 = param_1[0x11];
      (**(void **)(DC + 4))(param_1 + 0x25);
      (**(void **)(DC + 8))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,*(uint32_t *)(DC + 0x1e2d8));
      (**(void **)(DC + 4))(0);
      tmp_f4 = param_1[1];
      tmp_f3 = param_1[3];
      (**(void **)(DC + 4))(param_1 + 0x25);
      (**(void **)(DC + 8))(tmp_f7,(tmp_f4 + tmp_f3) - 1.0,tmp_f5,tmp_f6,*(uint32_t *)(DC + 0x1e2d8));
      (**(void **)(DC + 4))(0);
    }
    return;
  }
  if (param_1[0xd] == 5.60519e-45) {
    if (local_1c <= 0.0) {
      local_14 = 0x3f800000;
      local_1c = 0.5;
    }
    else {
      local_1c = 1.0;
      local_14 = 0x3f000000;
    }
    local_18 = 0x3f000000;
    pfVar8 = &local_1c;
    tmp_f7 = param_1[0x11];
    local_10 = 0x3f800000;
  }
  else {
    pfVar8 = param_1 + 0x25;
    tmp_f7 = param_1[0x11];
  }
  (**(void **)(DC + 0x40))(*param_1,param_1[1],param_1[2],param_1[3],tmp_f7,pfVar8);
  return;
}

void Item_SetScreenCoords(float *param_1,float param_2,float param_3)
{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float tmp_f6;
  
  if (param_1 != (float *)0x0) {
    pfVar1 = (float *)param_1[0x9c];
    *param_1 = param_1[4] + param_2;
    param_1[1] = param_1[5] + param_3;
    param_1[2] = param_1[6];
    param_1[3] = param_1[7];
    if (pfVar1 != (float *)0x0) {
      pfVar2 = (float *)pfVar1[0x9c];
      *pfVar1 = param_2 + pfVar1[4];
      pfVar1[1] = param_3 + pfVar1[5];
      pfVar1[2] = pfVar1[6];
      pfVar1[3] = pfVar1[7];
      if (pfVar2 != (float *)0x0) {
        pfVar3 = (float *)pfVar2[0x9c];
        *pfVar2 = param_2 + pfVar2[4];
        pfVar2[1] = param_3 + pfVar2[5];
        pfVar2[2] = pfVar2[6];
        pfVar2[3] = pfVar2[7];
        if (pfVar3 != (float *)0x0) {
          pfVar4 = (float *)pfVar3[0x9c];
          *pfVar3 = param_2 + pfVar3[4];
          pfVar3[1] = param_3 + pfVar3[5];
          pfVar3[2] = pfVar3[6];
          pfVar3[3] = pfVar3[7];
          if (pfVar4 != (float *)0x0) {
            *pfVar4 = param_2 + pfVar4[4];
            pfVar4[1] = param_3 + pfVar4[5];
            pfVar4[2] = pfVar4[6];
            pfVar4[3] = pfVar4[7];
            if (pfVar4[0x9c] != 0.0) {
              Item_SetScreenCoords(pfVar4[0x9c],param_2,param_3);
              pfVar5 = (float *)pfVar4[0x9c];
              tmp_f6 = (*pfVar5 + pfVar5[2]) - 635.0;
              if (0.0 < tmp_f6) {
                pfVar5[4] = pfVar5[4] - tmp_f6;
                *(float *)pfVar4[0x9c] = *(float *)pfVar4[0x9c] - tmp_f6;
              }
            }
            pfVar4[0x30] = 0.0;
            pfVar4[0x31] = 0.0;
            pfVar4 = (float *)pfVar3[0x9c];
            tmp_f6 = (*pfVar4 + pfVar4[2]) - 635.0;
            if (0.0 < tmp_f6) {
              pfVar4[4] = pfVar4[4] - tmp_f6;
              *(float *)pfVar3[0x9c] = *(float *)pfVar3[0x9c] - tmp_f6;
            }
          }
          pfVar3[0x30] = 0.0;
          pfVar3[0x31] = 0.0;
          pfVar3 = (float *)pfVar2[0x9c];
          tmp_f6 = (*pfVar3 + pfVar3[2]) - 635.0;
          if (0.0 < tmp_f6) {
            pfVar3[4] = pfVar3[4] - tmp_f6;
            *(float *)pfVar2[0x9c] = *(float *)pfVar2[0x9c] - tmp_f6;
          }
        }
        pfVar2[0x30] = 0.0;
        pfVar2[0x31] = 0.0;
        pfVar2 = (float *)pfVar1[0x9c];
        tmp_f6 = (*pfVar2 + pfVar2[2]) - 635.0;
        if (0.0 < tmp_f6) {
          pfVar2[4] = pfVar2[4] - tmp_f6;
          *(float *)pfVar1[0x9c] = *(float *)pfVar1[0x9c] - tmp_f6;
        }
      }
      pfVar1[0x30] = 0.0;
      pfVar1[0x31] = 0.0;
      pfVar1 = (float *)param_1[0x9c];
      tmp_f6 = (*pfVar1 + pfVar1[2]) - 635.0;
      if (0.0 < tmp_f6) {
        pfVar1[4] = pfVar1[4] - tmp_f6;
        *(float *)param_1[0x9c] = *(float *)param_1[0x9c] - tmp_f6;
      }
    }
    param_1[0x30] = 0.0;
    param_1[0x31] = 0.0;
  }
  return;
}

void Item_UpdatePosition(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  
  if ((param_1 != (float *)0x0) && (pfVar3 = (float *)param_1[0x3b], pfVar3 != (float *)0x0)) {
    tmp_f1 = *pfVar3;
    tmp_f2 = pfVar3[1];
    pfVar3 = (float *)param_1[0x9c];
    *param_1 = param_1[4] + tmp_f1;
    param_1[1] = param_1[5] + tmp_f2;
    param_1[2] = param_1[6];
    param_1[3] = param_1[7];
    if (pfVar3 != (float *)0x0) {
      pfVar4 = (float *)pfVar3[0x9c];
      *pfVar3 = pfVar3[4] + tmp_f1;
      pfVar3[1] = pfVar3[5] + tmp_f2;
      pfVar3[2] = pfVar3[6];
      pfVar3[3] = pfVar3[7];
      if (pfVar4 != (float *)0x0) {
        pfVar5 = (float *)pfVar4[0x9c];
        *pfVar4 = pfVar4[4] + tmp_f1;
        pfVar4[1] = pfVar4[5] + tmp_f2;
        pfVar4[2] = pfVar4[6];
        pfVar4[3] = pfVar4[7];
        if (pfVar5 != (float *)0x0) {
          pfVar6 = (float *)pfVar5[0x9c];
          *pfVar5 = pfVar5[4] + tmp_f1;
          pfVar5[1] = pfVar5[5] + tmp_f2;
          pfVar5[2] = pfVar5[6];
          pfVar5[3] = pfVar5[7];
          if (pfVar6 != (float *)0x0) {
            pfVar7 = (float *)pfVar6[0x9c];
            *pfVar6 = pfVar6[4] + tmp_f1;
            pfVar6[1] = pfVar6[5] + tmp_f2;
            pfVar6[2] = pfVar6[6];
            pfVar6[3] = pfVar6[7];
            if (pfVar7 != (float *)0x0) {
              *pfVar7 = pfVar7[4] + tmp_f1;
              pfVar7[1] = pfVar7[5] + tmp_f2;
              pfVar7[2] = pfVar7[6];
              pfVar7[3] = pfVar7[7];
              if (pfVar7[0x9c] != 0.0) {
                Item_SetScreenCoords(pfVar7[0x9c],tmp_f1,tmp_f2);
                pfVar8 = (float *)pfVar7[0x9c];
                tmp_f1 = (pfVar8[2] + *pfVar8) - 635.0;
                if (0.0 < tmp_f1) {
                  pfVar8[4] = pfVar8[4] - tmp_f1;
                  *(float *)pfVar7[0x9c] = *(float *)pfVar7[0x9c] - tmp_f1;
                }
              }
              pfVar7[0x30] = 0.0;
              pfVar7[0x31] = 0.0;
              pfVar7 = (float *)pfVar6[0x9c];
              tmp_f1 = (*pfVar7 + pfVar7[2]) - 635.0;
              if (0.0 < tmp_f1) {
                pfVar7[4] = pfVar7[4] - tmp_f1;
                *(float *)pfVar6[0x9c] = *(float *)pfVar6[0x9c] - tmp_f1;
              }
            }
            pfVar6[0x30] = 0.0;
            pfVar6[0x31] = 0.0;
            pfVar6 = (float *)pfVar5[0x9c];
            tmp_f1 = (*pfVar6 + pfVar6[2]) - 635.0;
            if (0.0 < tmp_f1) {
              pfVar6[4] = pfVar6[4] - tmp_f1;
              *(float *)pfVar5[0x9c] = *(float *)pfVar5[0x9c] - tmp_f1;
            }
          }
          pfVar5[0x30] = 0.0;
          pfVar5[0x31] = 0.0;
          pfVar5 = (float *)pfVar4[0x9c];
          tmp_f1 = (*pfVar5 + pfVar5[2]) - 635.0;
          if (0.0 < tmp_f1) {
            pfVar5[4] = pfVar5[4] - tmp_f1;
            *(float *)pfVar4[0x9c] = *(float *)pfVar4[0x9c] - tmp_f1;
          }
        }
        pfVar4[0x30] = 0.0;
        pfVar4[0x31] = 0.0;
        pfVar4 = (float *)pfVar3[0x9c];
        tmp_f1 = (*pfVar4 + pfVar4[2]) - 635.0;
        if (0.0 < tmp_f1) {
          pfVar4[4] = pfVar4[4] - tmp_f1;
          *(float *)pfVar3[0x9c] = *(float *)pfVar3[0x9c] - tmp_f1;
        }
      }
      pfVar3[0x30] = 0.0;
      pfVar3[0x31] = 0.0;
      pfVar3 = (float *)param_1[0x9c];
      tmp_f1 = (*pfVar3 + pfVar3[2]) - 635.0;
      if (0.0 < tmp_f1) {
        pfVar3[4] = pfVar3[4] - tmp_f1;
        *(float *)param_1[0x9c] = *(float *)param_1[0x9c] - tmp_f1;
      }
    }
    param_1[0x30] = 0.0;
    param_1[0x31] = 0.0;
  }
  return;
}

void Menu_UpdatePosition(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float tmp_f9;
  bool tmp_b10;
  bool tmp_b11;
  bool tmp_b12;
  int tmp_i13;
  int tmp_i14;
  int tmp_i15;
  long double tmp_l16;
  float local_40;
  
  if (*(float *)(DC + 0x2003c) <= 1.3333334) {
    local_40 = 0.0;
  }
  else {
    local_40 = (*(float *)(DC + 0x2003c) * 0.75 * 640.0 - 640.0) * 0.5;
  }
  if (param_1 == (float *)0x0) {
    return;
  }
  tmp_f1 = *param_1;
  tmp_f2 = param_1[1];
  if (((tmp_f1 == 0.0) && (tmp_f2 == 0.0)) && (param_1[2] == 640.0)) {
    tmp_b10 = param_1[3] == 480.0;
  }
  else {
    if ((tmp_f1 == 16.0) && (param_1[2] == 608.0)) {
      tmp_b11 = true;
      *param_1 = local_40 + 16.0;
      tmp_b10 = false;
      goto LAB_000f1753;
    }
    tmp_b10 = false;
  }
  tmp_b11 = false;
LAB_000f1753:
  if (0 < (int)param_1[0x30]) {
    tmp_i15 = 0;
    do {
      while( true ) {
        tmp_f9 = param_1[tmp_i15 + 0x145];
        if (((*(float *)((int)tmp_f9 + 0x10) == 0.0) && (*(float *)((int)tmp_f9 + 0x14) == 0.0)) &&
           ((*(float *)((int)tmp_f9 + 0x18) == 640.0 && (*(float *)((int)tmp_f9 + 0x1c) == 480.0))))
        break;
        tmp_i14 = Q_stricmp(*(uint32_t *)((int)tmp_f9 + 0x20),"clouds");
        tmp_b12 = tmp_b10;
        if (tmp_i14 == 0) {
LAB_000f1800:
          *(float *)((int)tmp_f9 + 0x18) = local_40 + local_40 + *(float *)((int)tmp_f9 + 0x18);
        }
        if (!tmp_b12) goto LAB_000f1812;
LAB_000f181d:
        tmp_f9 = tmp_f1 + local_40;
        pfVar3 = (float *)param_1[tmp_i15 + 0x145];
        if (pfVar3 != (float *)0x0) {
          pfVar4 = (float *)pfVar3[0x9c];
          *pfVar3 = pfVar3[4] + tmp_f9;
          pfVar3[1] = pfVar3[5] + tmp_f2;
          pfVar3[2] = pfVar3[6];
          pfVar3[3] = pfVar3[7];
          if (pfVar4 != (float *)0x0) {
            pfVar5 = (float *)pfVar4[0x9c];
            *pfVar4 = pfVar4[4] + tmp_f9;
            pfVar4[1] = pfVar4[5] + tmp_f2;
            pfVar4[2] = pfVar4[6];
            pfVar4[3] = pfVar4[7];
            if (pfVar5 != (float *)0x0) {
              pfVar6 = (float *)pfVar5[0x9c];
              *pfVar5 = pfVar5[4] + tmp_f9;
              pfVar5[1] = pfVar5[5] + tmp_f2;
              pfVar5[2] = pfVar5[6];
              pfVar5[3] = pfVar5[7];
              if (pfVar6 != (float *)0x0) {
                pfVar7 = (float *)pfVar6[0x9c];
                *pfVar6 = pfVar6[4] + tmp_f9;
                pfVar6[1] = pfVar6[5] + tmp_f2;
                pfVar6[2] = pfVar6[6];
                pfVar6[3] = pfVar6[7];
                if (pfVar7 != (float *)0x0) {
                  *pfVar7 = pfVar7[4] + tmp_f9;
                  pfVar7[1] = pfVar7[5] + tmp_f2;
                  pfVar7[2] = pfVar7[6];
                  pfVar7[3] = pfVar7[7];
                  if (pfVar7[0x9c] != 0.0) {
                    Item_SetScreenCoords(pfVar7[0x9c],tmp_f9,tmp_f2);
                    pfVar8 = (float *)pfVar7[0x9c];
                    tmp_f9 = (pfVar8[2] + *pfVar8) - 635.0;
                    if (0.0 < tmp_f9) {
                      pfVar8[4] = pfVar8[4] - tmp_f9;
                      *(float *)pfVar7[0x9c] = *(float *)pfVar7[0x9c] - tmp_f9;
                    }
                  }
                  pfVar7[0x30] = 0.0;
                  pfVar7[0x31] = 0.0;
                  pfVar7 = (float *)pfVar6[0x9c];
                  tmp_f9 = (*pfVar7 + pfVar7[2]) - 635.0;
                  if (0.0 < tmp_f9) {
                    pfVar7[4] = pfVar7[4] - tmp_f9;
                    *(float *)pfVar6[0x9c] = *(float *)pfVar6[0x9c] - tmp_f9;
                  }
                }
                pfVar6[0x30] = 0.0;
                pfVar6[0x31] = 0.0;
                pfVar6 = (float *)pfVar5[0x9c];
                tmp_f9 = (*pfVar6 + pfVar6[2]) - 635.0;
                if (0.0 < tmp_f9) {
                  pfVar6[4] = pfVar6[4] - tmp_f9;
                  *(float *)pfVar5[0x9c] = *(float *)pfVar5[0x9c] - tmp_f9;
                }
              }
              pfVar5[0x30] = 0.0;
              pfVar5[0x31] = 0.0;
              pfVar5 = (float *)pfVar4[0x9c];
              tmp_f9 = (*pfVar5 + pfVar5[2]) - 635.0;
              if (0.0 < tmp_f9) {
                pfVar5[4] = pfVar5[4] - tmp_f9;
                *(float *)pfVar4[0x9c] = *(float *)pfVar4[0x9c] - tmp_f9;
              }
            }
            pfVar4[0x30] = 0.0;
            pfVar4[0x31] = 0.0;
            pfVar4 = (float *)pfVar3[0x9c];
            tmp_f9 = (*pfVar4 + pfVar4[2]) - 635.0;
            if (0.0 < tmp_f9) {
              pfVar4[4] = pfVar4[4] - tmp_f9;
              *(float *)pfVar3[0x9c] = *(float *)pfVar3[0x9c] - tmp_f9;
            }
          }
          pfVar3[0x30] = 0.0;
          pfVar3[0x31] = 0.0;
        }
        tmp_i15 = tmp_i15 + 1;
        if ((int)param_1[0x30] <= tmp_i15) {
          return;
        }
      }
      tmp_i13 = Q_stricmp(*(uint32_t *)((int)tmp_f9 + 0x20),"clouds");
      tmp_i14 = DC;
      if (tmp_i13 == 0) {
        tmp_b12 = false;
        goto LAB_000f1800;
      }
      *(float *)((int)tmp_f9 + 0x10) = *(float *)((int)tmp_f9 + 0x10) * *(float *)(DC + 0x114);
      *(float *)((int)tmp_f9 + 0x14) = *(float *)((int)tmp_f9 + 0x14) * *(float *)(tmp_i14 + 0x110);
      *(float *)((int)tmp_f9 + 0x18) = *(float *)((int)tmp_f9 + 0x18) * *(float *)(tmp_i14 + 0x114);
      *(float *)((int)tmp_f9 + 0x1c) = *(float *)((int)tmp_f9 + 0x1c) * *(float *)(tmp_i14 + 0x110);
      if ((1.3333334 < *(float *)(tmp_i14 + 0x2003c)) &&
         (tmp_l16 = (long double)(**(void **)(tmp_i14 + 0x74))("r_mode"), tmp_i14 = DC,
         tmp_l16 != (long double)11.0)) {
        *(float *)((int)tmp_f9 + 0x10) =
             (1.3333334 / *(float *)(DC + 0x2003c)) * *(float *)((int)tmp_f9 + 0x10);
        *(float *)((int)tmp_f9 + 0x18) =
             (1.3333334 / *(float *)(tmp_i14 + 0x2003c)) * *(float *)((int)tmp_f9 + 0x18);
      }
LAB_000f1812:
      if (tmp_b11) goto LAB_000f181d;
      Item_SetScreenCoords(param_1[tmp_i15 + 0x145],tmp_f1,tmp_f2);
      tmp_i15 = tmp_i15 + 1;
    } while (tmp_i15 < (int)param_1[0x30]);
  }
  return;
}

void Menu_PostParse(uint32_t *param_1)
{
  if (param_1 != (uint32_t *)0x0) {
    if (param_1[0x2f] != 0) {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0x44200000;
      param_1[3] = 0x43f00000;
    }
    Menu_UpdatePosition();
    return;
  }
  return;
}

int Menu_ClearFocus(int param_1)
{
  uint *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint32_t local_10;
  
  if (param_1 == 0) {
    local_10 = 0;
  }
  else {
    local_10 = 0;
    if (0 < *(int *)(param_1 + 0xc0)) {
      tmp_i5 = 0;
      do {
        tmp_i2 = *(int *)(param_1 + 0x514 + tmp_i5 * 4);
        tmp_u3 = *(uint *)(tmp_i2 + 0x48);
        tmp_i4 = tmp_i2;
        if ((tmp_u3 & 2) != 0) {
          *(uint *)(tmp_i2 + 0x48) = tmp_u3 & 0xfffffffd;
          tmp_i4 = *(int *)(param_1 + 0x514 + tmp_i5 * 4);
          tmp_u3 = *(uint *)(tmp_i4 + 0x48);
          local_10 = tmp_i2;
        }
        if ((tmp_u3 & 1) != 0) {
          if ((tmp_u3 & 0x80) != 0) {
            Item_RunScript_constprop_37();
            *(uint *)(tmp_i4 + 0x48) = *(uint *)(tmp_i4 + 0x48) & 0xffffff7f;
          }
          Item_RunScript_constprop_37();
          *(uint *)(tmp_i4 + 0x48) = *(uint *)(tmp_i4 + 0x48) & 0xffffe7ff;
          tmp_i2 = *(int *)(param_1 + 0x514 + tmp_i5 * 4);
          tmp_i4 = 0;
          if (tmp_i2 != 0) {
            tmp_pu1 = (uint *)(tmp_i2 + 0x48);
            *tmp_pu1 = *tmp_pu1 & 0xfffffffe;
            tmp_i4 = *(int *)(param_1 + 0x514 + tmp_i5 * 4);
          }
        }
        if (*(int *)(tmp_i4 + 0x110) != 0) {
          Item_RunScript_constprop_37();
        }
        tmp_i5 = tmp_i5 + 1;
      } while (tmp_i5 < *(int *)(param_1 + 0xc0));
    }
  }
  return local_10;
}

void Script_SetFocus(int param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  char *tmp_pc2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_i3 = String_Alloc(tmp_pc2);
    tmp_i1 = *(int *)(param_1 + 0xec);
    if ((tmp_i3 != 0) && ((tmp_i1 != 0 && (0 < *(int *)(tmp_i1 + 0xc0))))) {
      tmp_i5 = 0;
      do {
        tmp_i4 = Q_stricmp(tmp_i3,*(uint32_t *)(*(int *)(tmp_i1 + 0x514 + tmp_i5 * 4) + 0x20));
        if (tmp_i4 == 0) {
          tmp_i1 = *(int *)(tmp_i1 + 0x514 + tmp_i5 * 4);
          if (tmp_i1 == 0) {
            return;
          }
          if ((*(byte *)(tmp_i1 + 0x48) & 0x12) != 0) {
            return;
          }
          Menu_ClearFocus(*(uint32_t *)(param_1 + 0xec));
          *(uint *)(tmp_i1 + 0x48) = *(uint *)(tmp_i1 + 0x48) | 2;
          if (*(int *)(tmp_i1 + 0x10c) != 0) {
            Item_RunScript_constprop_37();
          }
          if (*(int *)(DC + 0x1e320) == 0) {
            return;
          }
          (**(void **)(DC + 0x88))(*(int *)(DC + 0x1e320),6);
          return;
        }
        tmp_i5 = tmp_i5 + 1;
      } while (tmp_i5 < *(int *)(tmp_i1 + 0xc0));
    }
  }
  return;
}

void Script_ClearFocus(void)
{
  Menu_ClearFocus();
  return;
}

void Script_SetMenuFocus(int param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) &&
     (tmp_u2 = String_Alloc(tmp_pc1), 0 < menuCount)) {
    tmp_pu5 = &g_unk_040f8f60;
    tmp_i4 = 0;
    do {
      tmp_i3 = Q_stricmp(*tmp_pu5,tmp_u2);
      if (tmp_i3 == 0) {
        if ((*(byte *)(&g_unk_040f8f88 + tmp_i4 * 0x346) & 2) != 0) {
          return;
        }
        Menu_ClearFocus(*(uint32_t *)(param_1 + 0xec));
        (&g_unk_040f8f88)[tmp_i4 * 0x346] = (&g_unk_040f8f88)[tmp_i4 * 0x346] | 2;
        return;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu5 = tmp_pu5 + 0x346;
    } while (tmp_i4 < menuCount);
  }
  return;
}

void Script_SetEditFocus(int param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  char *tmp_pc2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_i3 = String_Alloc(tmp_pc2);
    tmp_i1 = *(int *)(param_1 + 0xec);
    if ((tmp_i3 != 0) && ((tmp_i1 != 0 && (0 < *(int *)(tmp_i1 + 0xc0))))) {
      tmp_i5 = 0;
      do {
        tmp_i4 = Q_stricmp(tmp_i3,*(uint32_t *)(*(int *)(tmp_i1 + 0x514 + tmp_i5 * 4) + 0x20));
        if (tmp_i4 == 0) {
          tmp_i1 = *(int *)(tmp_i1 + 0x514 + tmp_i5 * 4);
          if (tmp_i1 == 0) {
            return;
          }
          if ((*(int *)(tmp_i1 + 200) != 9) && (*(int *)(tmp_i1 + 200) != 4)) {
            return;
          }
          tmp_i3 = *(int *)(tmp_i1 + 0x250);
          Menu_ClearFocus(*(uint32_t *)(param_1 + 0xec));
          *(uint *)(tmp_i1 + 0x48) = *(uint *)(tmp_i1 + 0x48) | 2;
          if (*(int *)(tmp_i1 + 0x10c) != 0) {
            Item_RunScript_constprop_37();
          }
          if (*(int *)(DC + 0x1e320) != 0) {
            (**(void **)(DC + 0x88))(*(int *)(DC + 0x1e320),6);
          }
          if (tmp_i3 != 0) {
            *(uint32_t *)(tmp_i3 + 0x18) = 0;
          }
          *(uint32_t *)(tmp_i1 + 0x24c) = 0;
          g_editItem = tmp_i1;
          g_editingField = 1;
          return;
        }
        tmp_i5 = tmp_i5 + 1;
      } while (tmp_i5 < *(int *)(tmp_i1 + 0xc0));
    }
  }
  return;
}

bool IsVisible(uint param_1)
{
  return (param_1 & 0x24) == 4;
}

bool Rect_ContainsPoint(float *param_1,float param_2,float param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  
  if (param_1 != (float *)0x0) {
    tmp_f1 = *(float *)(DC + 0x2003c);
    if (tmp_f1 <= 1.3333334) {
      if (param_2 <= *param_1) {
        return false;
      }
      tmp_f3 = *param_1 + param_1[2];
    }
    else {
      tmp_f2 = tmp_f1 * 0.75;
      param_2 = param_2 * tmp_f2;
      if (param_2 <= *param_1 * tmp_f2) {
        return false;
      }
      tmp_f3 = *param_1 + param_1[2];
      if (1.3333334 < tmp_f1) {
        tmp_f3 = tmp_f2 * tmp_f3;
      }
    }
    if ((param_2 < tmp_f3) && (param_1[1] < param_3)) {
      return param_3 < param_1[1] + param_1[3];
    }
  }
  return false;
}

int Menu_ItemsMatchingGroup(int param_1,char *param_2)
{
  char *tmp_pc1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int local_20;
  
  tmp_pc1 = strchr(param_2,0x2a);
  if (tmp_pc1 == (char *)0x0) {
    tmp_i4 = 0;
    local_20 = 0;
    if (0 < *(int *)(param_1 + 0xc0)) {
LAB_000f2350:
      do {
        tmp_i2 = Q_stricmp(*(uint32_t *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x20),param_2);
        if ((tmp_i2 == 0) ||
           ((tmp_i2 = *(int *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x28), tmp_i2 != 0 &&
            (tmp_i2 = Q_stricmp(tmp_i2,param_2), tmp_i2 == 0)))) {
          local_20 = local_20 + 1;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 < *(int *)(param_1 + 0xc0));
      return local_20;
    }
  }
  else {
    tmp_i2 = (int)tmp_pc1 - (int)param_2;
    local_20 = 0;
    if (0 < *(int *)(param_1 + 0xc0)) {
      tmp_i4 = 0;
      if (tmp_i2 == -1) goto LAB_000f2350;
      tmp_i4 = 0;
      do {
        tmp_i3 = Q_strncmp(*(uint32_t *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x20),param_2,
                          tmp_i2);
        if ((tmp_i3 == 0) ||
           ((tmp_i3 = *(int *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x28), tmp_i3 != 0 &&
            (tmp_i3 = Q_strncmp(tmp_i3,param_2,tmp_i2), tmp_i3 == 0)))) {
          local_20 = local_20 + 1;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 < *(int *)(param_1 + 0xc0));
    }
  }
  return local_20;
}

uint32_t Menu_GetMatchingItemByNumber(int param_1,int param_2,char *param_3)
{
  char *tmp_pc1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int local_24;
  int local_20;
  
  tmp_pc1 = strchr(param_3,0x2a);
  if (tmp_pc1 == (char *)0x0) {
    tmp_i2 = 0;
    local_24 = 0;
    if (*(int *)(param_1 + 0xc0) < 1) {
      return 0;
    }
  }
  else {
    tmp_i2 = (int)tmp_pc1 - (int)param_3;
    if (*(int *)(param_1 + 0xc0) < 1) {
      return 0;
    }
    if (tmp_i2 != -1) {
      local_20 = 0;
      tmp_i4 = 0;
      do {
        tmp_i3 = Q_strncmp(*(uint32_t *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x20),param_3,
                          tmp_i2);
        if ((tmp_i3 == 0) ||
           ((tmp_i3 = *(int *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x28), tmp_i3 != 0 &&
            (tmp_i3 = Q_strncmp(tmp_i3,param_3,tmp_i2), tmp_i3 == 0)))) {
          if (local_20 == param_2) {
            return *(uint32_t *)(param_1 + 0x514 + tmp_i4 * 4);
          }
          local_20 = local_20 + 1;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 < *(int *)(param_1 + 0xc0));
      return 0;
    }
    local_24 = 0;
    tmp_i2 = 0;
  }
  do {
    tmp_i4 = Q_stricmp(*(uint32_t *)(*(int *)(param_1 + 0x514 + tmp_i2 * 4) + 0x20),param_3);
    if ((tmp_i4 == 0) ||
       ((tmp_i4 = *(int *)(*(int *)(param_1 + 0x514 + tmp_i2 * 4) + 0x28), tmp_i4 != 0 &&
        (tmp_i4 = Q_stricmp(tmp_i4,param_3), tmp_i4 == 0)))) {
      if (local_24 == param_2) {
        return *(uint32_t *)(param_1 + 0x514 + tmp_i2 * 4);
      }
      local_24 = local_24 + 1;
    }
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 < *(int *)(param_1 + 0xc0));
  return 0;
}

void Script_SetItemColor(int param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  float *pfVar7;
  float *pfVar8;
  int tmp_i9;
  double tmp_d10;
  float local_2c [4];
  float local_1c [3];
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_pc1 = (char *)COM_ParseExt(param_3,0);
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_u3 = String_Alloc(tmp_pc1);
      tmp_i4 = Menu_ItemsMatchingGroup(*(uint32_t *)(param_1 + 0xec),tmp_u2);
      pfVar7 = local_2c;
      do {
        tmp_pc1 = (char *)COM_ParseExt(param_3,0);
        if (tmp_pc1 == (char *)0x0) {
          return;
        }
        if (*tmp_pc1 == '\0') {
          return;
        }
        pfVar8 = pfVar7 + 1;
        tmp_d10 = strtod(tmp_pc1,(char **)0x0);
        *pfVar7 = (float)tmp_d10;
        pfVar7 = pfVar8;
      } while (pfVar8 != local_1c);
      if (0 < tmp_i4) {
        tmp_i9 = 0;
        do {
          tmp_i5 = Menu_GetMatchingItemByNumber(*(uint32_t *)(param_1 + 0xec),tmp_i9,tmp_u2);
          if (tmp_i5 != 0) {
            tmp_i6 = Q_stricmp(tmp_u3,"backcolor");
            if (tmp_i6 == 0) {
              pfVar7 = (float *)(tmp_i5 + 0x84);
            }
            else {
              tmp_i6 = Q_stricmp(tmp_u3,"forecolor");
              if (tmp_i6 == 0) {
                pfVar7 = (float *)(tmp_i5 + 0x74);
                *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) | 0x200;
              }
              else {
                tmp_i6 = Q_stricmp(tmp_u3,"bordercolor");
                pfVar7 = (float *)(tmp_i5 + 0x94);
                if (tmp_i6 != 0) goto LAB_000f2661;
              }
            }
            *pfVar7 = local_2c[0];
            pfVar7[1] = local_2c[1];
            pfVar7[2] = local_2c[2];
            pfVar7[3] = local_2c[3];
          }
LAB_000f2661:
          tmp_i9 = tmp_i9 + 1;
        } while (tmp_i9 != tmp_i4);
      }
    }
  }
  return;
}

void Script_SetMenuItemColor(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  uint32_t *tmp_pu9;
  int tmp_i10;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_u2 = String_Alloc(tmp_pc1);
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_u3 = String_Alloc(tmp_pc1);
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_u4 = String_Alloc(tmp_pc1);
  if (menuCount < 1) {
    return;
  }
  tmp_pu9 = &g_unk_040f8f60;
  tmp_i10 = 0;
  while (tmp_i5 = Q_stricmp(*tmp_pu9,tmp_u2), tmp_i5 != 0) {
    tmp_i10 = tmp_i10 + 1;
    tmp_pu9 = tmp_pu9 + 0x346;
    if (menuCount <= tmp_i10) {
      return;
    }
  }
  tmp_i5 = Menu_ItemsMatchingGroup(&Menus + tmp_i10 * 0x346,tmp_u3);
  tmp_i6 = Color_Parse(param_3,&local_2c);
  if (tmp_i6 == 0) {
    return;
  }
  tmp_i6 = 0;
  if (tmp_i5 < 1) {
    return;
  }
  do {
    tmp_i7 = Menu_GetMatchingItemByNumber(&Menus + tmp_i10 * 0x346,tmp_i6,tmp_u3);
    if (tmp_i7 != 0) {
      tmp_i8 = Q_stricmp(tmp_u4,"backcolor");
      if (tmp_i8 == 0) {
        tmp_pu9 = (uint32_t *)(tmp_i7 + 0x84);
      }
      else {
        tmp_i8 = Q_stricmp(tmp_u4,"forecolor");
        if (tmp_i8 == 0) {
          tmp_pu9 = (uint32_t *)(tmp_i7 + 0x74);
          *(uint *)(tmp_i7 + 0x48) = *(uint *)(tmp_i7 + 0x48) | 0x200;
        }
        else {
          tmp_i8 = Q_stricmp(tmp_u4,"bordercolor");
          tmp_pu9 = (uint32_t *)(tmp_i7 + 0x94);
          if (tmp_i8 != 0) goto LAB_000f2861;
        }
      }
      *tmp_pu9 = local_2c;
      tmp_pu9[1] = local_28;
      tmp_pu9[2] = local_24;
      tmp_pu9[3] = local_20;
    }
LAB_000f2861:
    tmp_i6 = tmp_i6 + 1;
    if (tmp_i6 == tmp_i5) {
      return;
    }
  } while( true );
}

void Script_FadeIn(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_u1 = *(uint32_t *)(param_1 + 0xec);
    tmp_i4 = Menu_ItemsMatchingGroup(tmp_u1,tmp_u3);
    if (0 < tmp_i4) {
      tmp_i6 = 0;
      do {
        tmp_i5 = Menu_GetMatchingItemByNumber(tmp_u1,tmp_i6,tmp_u3);
        if (tmp_i5 != 0) {
          *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) & 0xffffffdf | 0x44;
        }
        tmp_i6 = tmp_i6 + 1;
      } while (tmp_i6 != tmp_i4);
      return;
    }
  }
  return;
}

void Script_FadeOut(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_u1 = *(uint32_t *)(param_1 + 0xec);
    tmp_i4 = Menu_ItemsMatchingGroup(tmp_u1,tmp_u3);
    if (0 < tmp_i4) {
      tmp_i6 = 0;
      do {
        tmp_i5 = Menu_GetMatchingItemByNumber(tmp_u1,tmp_i6,tmp_u3);
        if (tmp_i5 != 0) {
          *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) & 0xffffffbf | 0x24;
        }
        tmp_i6 = tmp_i6 + 1;
      } while (tmp_i6 != tmp_i4);
      return;
    }
  }
  return;
}

void Script_Show(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_u1 = *(uint32_t *)(param_1 + 0xec);
    tmp_i4 = Menu_ItemsMatchingGroup(tmp_u1,tmp_u3);
    if (0 < tmp_i4) {
      tmp_i6 = 0;
      do {
        tmp_i5 = Menu_GetMatchingItemByNumber(tmp_u1,tmp_i6,tmp_u3);
        if (tmp_i5 != 0) {
          *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) | 4;
        }
        tmp_i6 = tmp_i6 + 1;
      } while (tmp_i6 != tmp_i4);
    }
  }
  return;
}

void Script_Hide(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  int tmp_i7;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_u1 = *(uint32_t *)(param_1 + 0xec);
    tmp_i4 = Menu_ItemsMatchingGroup(tmp_u1,tmp_u3);
    if (0 < tmp_i4) {
      tmp_i7 = 0;
      do {
        tmp_i5 = Menu_GetMatchingItemByNumber(tmp_u1,tmp_i7,tmp_u3);
        if (tmp_i5 != 0) {
          tmp_u6 = *(uint *)(tmp_i5 + 0x48);
          if ((tmp_u6 & 1) != 0) {
            if ((tmp_u6 & 0x80) != 0) {
              Item_RunScript_constprop_37();
              *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) & 0xffffff7f;
            }
            Item_RunScript_constprop_37();
            tmp_u6 = *(uint *)(tmp_i5 + 0x48) & 0xffffe7fe;
          }
          *(uint *)(tmp_i5 + 0x48) = tmp_u6 & 0xfffffffb;
          if (-1 < *(int *)(tmp_i5 + 0x30)) {
            (**(void **)(DC + 0xec))(*(int *)(tmp_i5 + 0x30));
            *(uint32_t *)(tmp_i5 + 0x30) = 0xffffffff;
          }
        }
        tmp_i7 = tmp_i7 + 1;
      } while (tmp_i7 != tmp_i4);
    }
  }
  return;
}

uint32_t Menu_FindItemByName(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  
  if (((param_1 != 0) && (param_2 != 0)) && (0 < *(int *)(param_1 + 0xc0))) {
    tmp_i2 = 0;
    do {
      tmp_i1 = Q_stricmp(param_2,*(uint32_t *)(*(int *)(param_1 + 0x514 + tmp_i2 * 4) + 0x20));
      if (tmp_i1 == 0) {
        return *(uint32_t *)(param_1 + 0x514 + tmp_i2 * 4);
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 < *(int *)(param_1 + 0xc0));
  }
  return 0;
}

void Menu_ShowItemByName(uint32_t param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  
  tmp_i1 = Menu_ItemsMatchingGroup(param_1,param_2);
  if (0 < tmp_i1) {
    tmp_i4 = 0;
    if (param_3 == 0) {
      do {
        tmp_i2 = Menu_GetMatchingItemByNumber(param_1,tmp_i4,param_2);
        if (tmp_i2 != 0) {
          tmp_u3 = *(uint *)(tmp_i2 + 0x48);
          if ((tmp_u3 & 1) != 0) {
            if ((tmp_u3 & 0x80) != 0) {
              Item_RunScript_constprop_37();
              *(uint *)(tmp_i2 + 0x48) = *(uint *)(tmp_i2 + 0x48) & 0xffffff7f;
            }
            Item_RunScript_constprop_37();
            tmp_u3 = *(uint *)(tmp_i2 + 0x48) & 0xffffe7fe;
          }
          *(uint *)(tmp_i2 + 0x48) = tmp_u3 & 0xfffffffb;
          if (-1 < *(int *)(tmp_i2 + 0x30)) {
            (**(void **)(DC + 0xec))(*(int *)(tmp_i2 + 0x30));
            *(uint32_t *)(tmp_i2 + 0x30) = 0xffffffff;
          }
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 != tmp_i1);
    }
    else {
      tmp_i4 = 0;
      do {
        tmp_i2 = Menu_GetMatchingItemByNumber(param_1,tmp_i4,param_2);
        if (tmp_i2 != 0) {
          *(uint *)(tmp_i2 + 0x48) = *(uint *)(tmp_i2 + 0x48) | 4;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 != tmp_i1);
    }
  }
  return;
}

void Script_ConditionalHideShow(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  long double tmp_l7;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_l7 = (long double)(**(void **)(DC + 0x74))(*(uint32_t *)(param_1 + 0x114));
    if (tmp_l7 == (long double)0) {
      Menu_ShowItemByName();
      return;
    }
    tmp_u1 = *(uint32_t *)(param_1 + 0xec);
    tmp_i4 = Menu_ItemsMatchingGroup(tmp_u1,tmp_u3);
    if (0 < tmp_i4) {
      tmp_i6 = 0;
      do {
        tmp_i5 = Menu_GetMatchingItemByNumber(tmp_u1,tmp_i6,tmp_u3);
        if (tmp_i5 != 0) {
          *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) | 4;
        }
        tmp_i6 = tmp_i6 + 1;
      } while (tmp_i6 != tmp_i4);
    }
  }
  return;
}

void Menu_FadeItemByName(uint32_t param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i1 = Menu_ItemsMatchingGroup(param_1,param_2);
  if (0 < tmp_i1) {
    tmp_i3 = 0;
    if (param_3 != 0) {
      do {
        tmp_i2 = Menu_GetMatchingItemByNumber(param_1,tmp_i3,param_2);
        if (tmp_i2 != 0) {
          *(uint *)(tmp_i2 + 0x48) = *(uint *)(tmp_i2 + 0x48) & 0xffffffbf | 0x24;
        }
        tmp_i3 = tmp_i3 + 1;
      } while (tmp_i3 != tmp_i1);
      return;
    }
    do {
      tmp_i2 = Menu_GetMatchingItemByNumber(param_1,tmp_i3,param_2);
      if (tmp_i2 != 0) {
        *(uint *)(tmp_i2 + 0x48) = *(uint *)(tmp_i2 + 0x48) & 0xffffffdf | 0x44;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != tmp_i1);
  }
  return;
}

uint32_t * Menus_FindByName(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  
  if (0 < menuCount) {
    tmp_pu3 = &g_unk_040f8f60;
    tmp_i2 = 0;
    do {
      tmp_i1 = Q_stricmp(*tmp_pu3,param_1);
      if (tmp_i1 == 0) {
        return &Menus + tmp_i2 * 0x346;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pu3 = tmp_pu3 + 0x346;
    } while (tmp_i2 < menuCount);
  }
  return (uint32_t *)0x0;
}

void Menus_CloseAll(void)
{
  int tmp_i1;
  uint tmp_u2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  
  if (0 < menuCount) {
    tmp_pu3 = &Menus;
    tmp_i4 = 0;
    tmp_i1 = menuCount;
    do {
      tmp_u2 = tmp_pu3[0x12];
      if ((tmp_u2 & 4) != 0) {
        Menu_RunCloseScript_part_10();
        tmp_u2 = tmp_pu3[0x12];
        tmp_i1 = menuCount;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu3[0x12] = tmp_u2 & 0xfffffff8;
      tmp_pu3 = tmp_pu3 + 0x346;
    } while (tmp_i4 < tmp_i1);
  }
  return;
}

void Menu_FadeMenuByName(uint32_t param_1,uint32_t param_2,int param_3)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  
  if (0 < menuCount) {
    tmp_pu5 = &g_unk_040f8f60;
    tmp_i4 = 0;
    do {
      tmp_i3 = Q_stricmp(*tmp_pu5,param_1);
      if (tmp_i3 == 0) {
        tmp_pi1 = &g_unk_040f9000 + tmp_i4 * 0x346;
        if (*tmp_pi1 < 1) {
          return;
        }
        tmp_i3 = 0;
        if (param_3 == 0) {
          do {
            tmp_i2 = tmp_i4 * 0x346 + tmp_i3;
            tmp_i3 = tmp_i3 + 1;
            *(uint *)((&g_unk_040f9454)[tmp_i2] + 0x48) =
                 *(uint *)((&g_unk_040f9454)[tmp_i2] + 0x48) & 0xffffffdf | 0x44;
          } while (tmp_i3 < *tmp_pi1);
          return;
        }
        do {
          tmp_i2 = tmp_i4 * 0x346 + tmp_i3;
          tmp_i3 = tmp_i3 + 1;
          *(uint *)((&g_unk_040f9454)[tmp_i2] + 0x48) =
               *(uint *)((&g_unk_040f9454)[tmp_i2] + 0x48) & 0xffffffbf | 0x24;
        } while (tmp_i3 < *tmp_pi1);
        return;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu5 = tmp_pu5 + 0x346;
    } while (tmp_i4 < menuCount);
  }
  return;
}

void Menu_TransitionItemByName
               (uint32_t param_1,uint32_t param_2,float param_3,float param_4,float param_5,
               float param_6,float param_7,float param_8,float param_9,float param_10,
               uint32_t param_11,float param_12)

{
  uint32_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i2 = Menu_ItemsMatchingGroup(param_1,param_2);
  if (0 < tmp_i2) {
    tmp_i4 = 0;
    do {
      tmp_i3 = Menu_GetMatchingItemByNumber(param_1,tmp_i4,param_2);
      if (tmp_i3 != 0) {
        *(uint *)(tmp_i3 + 0x48) = *(uint *)(tmp_i3 + 0x48) | 0x104;
        *(uint32_t *)(tmp_i3 + 0x6c) = param_11;
        *(float *)(tmp_i3 + 0x10) = param_3;
        *(float *)(tmp_i3 + 0x14) = param_4;
        *(float *)(tmp_i3 + 0x18) = param_5;
        *(float *)(tmp_i3 + 0x1c) = param_6;
        *(float *)(tmp_i3 + 0x5c) = ABS(param_7 - param_3) / param_12;
        *(float *)(tmp_i3 + 0x4c) = param_7;
        *(float *)(tmp_i3 + 0x50) = param_8;
        *(float *)(tmp_i3 + 0x54) = param_9;
        *(float *)(tmp_i3 + 0x58) = param_10;
        *(float *)(tmp_i3 + 0x60) = ABS(param_8 - param_4) / param_12;
        *(float *)(tmp_i3 + 100) = ABS(param_9 - param_5) / param_12;
        tmp_pu1 = *(uint32_t **)(tmp_i3 + 0xec);
        *(float *)(tmp_i3 + 0x68) = ABS(param_10 - param_6) / param_12;
        if (tmp_pu1 != (uint32_t *)0x0) {
          Item_SetScreenCoords(tmp_i3,*tmp_pu1,tmp_pu1[1]);
        }
      }
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_i4 != tmp_i2);
  }
  return;
}

void Script_Transition(int param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  double tmp_d4;
  uint32_t local_30;
  float local_2c;
  float local_28;
  uint32_t local_24;
  float local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_30 = 0;
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_pc1 = (char *)COM_ParseExt(param_3,0);
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_d4 = strtod(tmp_pc1,(char **)0x0);
      local_2c = (float)tmp_d4;
      tmp_pc1 = (char *)COM_ParseExt(param_3,0);
      if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
        tmp_d4 = strtod(tmp_pc1,(char **)0x0);
        local_28 = (float)tmp_d4;
        tmp_i3 = Float_Parse(param_3,&local_24);
        if (tmp_i3 != 0) {
          tmp_pc1 = (char *)COM_ParseExt(param_3,0);
          if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
            tmp_d4 = strtod(tmp_pc1,(char **)0x0);
            local_20 = (float)tmp_d4;
            tmp_i3 = Rect_Parse(param_3,&local_1c);
            if (tmp_i3 != 0) {
              tmp_i3 = Int_Parse(param_3,&local_30);
              if (tmp_i3 != 0) {
                tmp_pc1 = (char *)COM_ParseExt(param_3,0);
                if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
                  tmp_d4 = strtod(tmp_pc1,(char **)0x0);
                  Menu_TransitionItemByName
                            (*(uint32_t *)(param_1 + 0xec),tmp_u2,local_2c,local_28,local_24,
                             local_20,local_1c,local_18,local_14,local_10,local_30,(float)tmp_d4);
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}

void Menu_OrbitItemByName
               (uint32_t param_1,uint32_t param_2,float param_3,float param_4,float param_5,
               float param_6,float param_7)

{
  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  int tmp_i8;
  float *pfVar9;
  int tmp_i10;
  
  tmp_i10 = 0;
  tmp_i8 = Menu_ItemsMatchingGroup(param_1,param_2);
  if (0 < tmp_i8) {
    do {
      pfVar9 = (float *)Menu_GetMatchingItemByNumber(param_1,tmp_i10,param_2);
      if (pfVar9 != (float *)0x0) {
        pfVar3 = (float *)pfVar9[0x3b];
        pfVar9[0x13] = param_5;
        pfVar9[0x12] = (float)((uint)pfVar9[0x12] | 0x10004);
        pfVar9[0x14] = param_6;
        pfVar9[0x1b] = param_7;
        pfVar9[4] = param_3;
        pfVar9[5] = param_4;
        if (pfVar3 != (float *)0x0) {
          tmp_f1 = *pfVar3;
          tmp_f2 = pfVar3[1];
          pfVar3 = (float *)pfVar9[0x9c];
          *pfVar9 = tmp_f1 + param_3;
          pfVar9[1] = tmp_f2 + param_4;
          pfVar9[2] = pfVar9[6];
          pfVar9[3] = pfVar9[7];
          if (pfVar3 != (float *)0x0) {
            pfVar4 = (float *)pfVar3[0x9c];
            *pfVar3 = pfVar3[4] + tmp_f1;
            pfVar3[1] = pfVar3[5] + tmp_f2;
            pfVar3[2] = pfVar3[6];
            pfVar3[3] = pfVar3[7];
            if (pfVar4 != (float *)0x0) {
              pfVar5 = (float *)pfVar4[0x9c];
              *pfVar4 = pfVar4[4] + tmp_f1;
              pfVar4[1] = pfVar4[5] + tmp_f2;
              pfVar4[2] = pfVar4[6];
              pfVar4[3] = pfVar4[7];
              if (pfVar5 != (float *)0x0) {
                pfVar6 = (float *)pfVar5[0x9c];
                *pfVar5 = pfVar5[4] + tmp_f1;
                pfVar5[1] = pfVar5[5] + tmp_f2;
                pfVar5[2] = pfVar5[6];
                pfVar5[3] = pfVar5[7];
                if (pfVar6 != (float *)0x0) {
                  *pfVar6 = pfVar6[4] + tmp_f1;
                  pfVar6[1] = pfVar6[5] + tmp_f2;
                  pfVar6[2] = pfVar6[6];
                  pfVar6[3] = pfVar6[7];
                  if (pfVar6[0x9c] != 0.0) {
                    Item_SetScreenCoords(pfVar6[0x9c],tmp_f1,tmp_f2);
                    pfVar7 = (float *)pfVar6[0x9c];
                    tmp_f1 = (pfVar7[2] + *pfVar7) - 635.0;
                    if (0.0 < tmp_f1) {
                      pfVar7[4] = pfVar7[4] - tmp_f1;
                      *(float *)pfVar6[0x9c] = *(float *)pfVar6[0x9c] - tmp_f1;
                    }
                  }
                  pfVar6[0x30] = 0.0;
                  pfVar6[0x31] = 0.0;
                  pfVar6 = (float *)pfVar5[0x9c];
                  tmp_f1 = (*pfVar6 + pfVar6[2]) - 635.0;
                  if (0.0 < tmp_f1) {
                    pfVar6[4] = pfVar6[4] - tmp_f1;
                    *(float *)pfVar5[0x9c] = *(float *)pfVar5[0x9c] - tmp_f1;
                  }
                }
                pfVar5[0x30] = 0.0;
                pfVar5[0x31] = 0.0;
                pfVar5 = (float *)pfVar4[0x9c];
                tmp_f1 = (*pfVar5 + pfVar5[2]) - 635.0;
                if (0.0 < tmp_f1) {
                  pfVar5[4] = pfVar5[4] - tmp_f1;
                  *(float *)pfVar4[0x9c] = *(float *)pfVar4[0x9c] - tmp_f1;
                }
              }
              pfVar4[0x30] = 0.0;
              pfVar4[0x31] = 0.0;
              pfVar4 = (float *)pfVar3[0x9c];
              tmp_f1 = (*pfVar4 + pfVar4[2]) - 635.0;
              if (0.0 < tmp_f1) {
                pfVar4[4] = pfVar4[4] - tmp_f1;
                *(float *)pfVar3[0x9c] = *(float *)pfVar3[0x9c] - tmp_f1;
              }
            }
            pfVar3[0x30] = 0.0;
            pfVar3[0x31] = 0.0;
            pfVar3 = (float *)pfVar9[0x9c];
            tmp_f1 = (*pfVar3 + pfVar3[2]) - 635.0;
            if (0.0 < tmp_f1) {
              pfVar3[4] = pfVar3[4] - tmp_f1;
              *(float *)pfVar9[0x9c] = *(float *)pfVar9[0x9c] - tmp_f1;
            }
          }
          pfVar9[0x30] = 0.0;
          pfVar9[0x31] = 0.0;
        }
      }
      tmp_i10 = tmp_i10 + 1;
    } while (tmp_i10 != tmp_i8);
  }
  return;
}

void Script_Orbit(int param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  double tmp_d4;
  double tmp_d5;
  double tmp_d6;
  uint32_t local_14;
  uint32_t local_10;
  
  local_10 = 0;
  local_14 = 0;
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_pc1 = (char *)COM_ParseExt(param_3,0);
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_d4 = strtod(tmp_pc1,(char **)0x0);
      tmp_pc1 = (char *)COM_ParseExt(param_3,0);
      if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
        tmp_d5 = strtod(tmp_pc1,(char **)0x0);
        tmp_i3 = Float_Parse(param_3,&local_14);
        if ((tmp_i3 != 0) &&
           ((tmp_pc1 = (char *)COM_ParseExt(param_3,0), tmp_pc1 != (char *)0x0 && (*tmp_pc1 != '\0'))))
        {
          tmp_d6 = strtod(tmp_pc1,(char **)0x0);
          tmp_i3 = Int_Parse(param_3,&local_10);
          if (tmp_i3 != 0) {
            Menu_OrbitItemByName
                      (*(uint32_t *)(param_1 + 0xec),tmp_u2,(float)tmp_d4,(float)tmp_d5,local_14,
                       (float)tmp_d6,local_10);
          }
        }
      }
    }
  }
  return;
}

uint32_t Script_CheckProfile(uint32_t param_1)
{
  int tmp_i1;
  long tmp_l2;
  long tmp_l3;
  uint32_t tmp_u4;
  uint32_t local_130;
  char local_12c [32];
  char local_10c [256];
  
  tmp_i1 = trap_FS_FOpenFile(param_1,&local_130,0);
  if (tmp_i1 < 0) {
    tmp_u4 = 1;
  }
  else {
    trap_FS_Read(local_12c,0x1f,local_130);
    (**(void **)(DC + 0x70))("com_pid",local_10c,0x100);
    tmp_l2 = strtol(local_10c,(char **)0x0,10);
    tmp_l3 = strtol(local_12c,(char **)0x0,10);
    if (tmp_l2 == tmp_l3) {
      trap_FS_FCloseFile(local_130);
      tmp_u4 = 1;
    }
    else {
      trap_FS_FCloseFile(local_130);
      tmp_u4 = 0;
    }
  }
  return tmp_u4;
}

uint32_t Script_WriteProfile(uint32_t param_1)
{
  int tmp_i1;
  uint tmp_u2;
  uint tmp_u3;
  uint *tmp_pu4;
  uint *tmp_pu5;
  int local_110;
  uint local_10c [65];
  
  tmp_i1 = FileExists(param_1);
  if (tmp_i1 != 0) {
    trap_FS_Delete(param_1);
  }
  tmp_i1 = trap_FS_FOpenFile(param_1,&local_110,1);
  if ((-1 < tmp_i1) && (-1 < local_110)) {
    (**(void **)(DC + 0x70))("com_pid",local_10c,0x100);
    tmp_pu5 = local_10c;
    do {
      tmp_pu4 = tmp_pu5;
      tmp_u2 = *tmp_pu4 + 0xfefefeff & ~*tmp_pu4;
      tmp_u3 = tmp_u2 & 0x80808080;
      tmp_pu5 = tmp_pu4 + 1;
    } while (tmp_u3 == 0);
    if ((tmp_u2 & 0x8080) == 0) {
      tmp_pu5 = (uint *)((int)tmp_pu4 + 6);
      tmp_u3 = tmp_u3 >> 0x10;
    }
    trap_FS_Write(local_10c,
                  (int)tmp_pu5 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_10c),
                  local_110);
    trap_FS_FCloseFile(local_110);
    return 1;
  }
  Com_Printf("Script_WriteProfile: Can\'t write %s.\n",param_1);
  return 0;
}

void Item_RunScript(int param_1,int *param_2,char *param_3)
{
  char *tmp_pc1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  int *tmp_pi5;
  int *local_1024;
  int local_1020 [1028];
  
  tmp_u3 = 0x1000;
  local_1024 = local_1020 + 1;
  local_1020[0] = 0;
  tmp_pi5 = local_1024;
  if (((uint)local_1024 & 4) != 0) {
    tmp_u3 = 0xffc;
    local_1020[1] = 0;
    tmp_pi5 = local_1020 + 2;
  }
  for (tmp_u3 = tmp_u3 >> 2; tmp_u3 != 0; tmp_u3 = tmp_u3 - 1) {
    *tmp_pi5 = 0;
    tmp_pi5 = tmp_pi5 + 1;
  }
  if (((param_1 == 0) || (param_3 == (char *)0x0)) || (*param_3 == '\0')) {
    return;
  }
  Q_strcat(local_1024,0x1000,param_3);
LAB_000f3b60:
  do {
    do {
      tmp_pc1 = (char *)COM_ParseExt(&local_1024,0);
      if (tmp_pc1 == (char *)0x0) {
        return;
      }
      if (*tmp_pc1 == '\0') {
        return;
      }
      tmp_pc1 = (char *)String_Alloc(tmp_pc1);
    } while ((*tmp_pc1 == ';') && (tmp_pc1[1] == '\0'));
    if (0 < scriptCommandCount) {
      tmp_i4 = 0;
      do {
        tmp_i2 = Q_stricmp(tmp_pc1,(&commandList)[tmp_i4 * 2]);
        if (tmp_i2 == 0) {
          (*(void *)(&g_ptr_Script_FadeIn_0014b164)[tmp_i4 * 2])(param_1,local_1020,&local_1024);
          if (local_1020[0] != 0) {
            if (param_2 == (int *)0x0) {
              return;
            }
            *param_2 = local_1020[0];
            return;
          }
          goto LAB_000f3b60;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 < scriptCommandCount);
    }
    (**(void **)(DC + 0x68))(&local_1024);
  } while( true );
}

void Script_ConditionalScript(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  long tmp_l3;
  int tmp_i4;
  long double tmp_l5;
  long double tmp_l6;
  long double tmp_l7;
  long double tmp_l8;
  long double tmp_l9;
  long double tmp_l10;
  long double tmp_l11;
  long double tmp_l12;
  long double tmp_l13;
  long double tmp_l14;
  long double tmp_l15;
  long double tmp_l16;
  long double tmp_l17;
  long double tmp_l18;
  long double tmp_l19;
  long double tmp_l20;
  long double tmp_l21;
  long double tmp_l22;
  long double tmp_l23;
  long double tmp_l24;
  uint32_t local_52c;
  uint32_t local_528;
  char *local_524;
  uint32_t local_520;
  uint32_t local_51c [64];
  int local_41c [259];
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_u2 = String_Alloc(tmp_pc1);
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  local_524 = (char *)String_Alloc(tmp_pc1);
  if (local_524 == (char *)0x0) {
    return;
  }
  if (*local_524 != '(') {
    return;
  }
  tmp_i4 = String_Parse(param_3,&local_52c);
  if (tmp_i4 == 0) {
    return;
  }
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  local_524 = (char *)String_Alloc(tmp_pc1);
  if (local_524 == (char *)0x0) {
    return;
  }
  if (*local_524 != ')') {
    return;
  }
  tmp_i4 = String_Parse(param_3,&local_524);
  if (tmp_i4 == 0) {
    return;
  }
  if (local_524 == (char *)0x0) {
    return;
  }
  if (*local_524 != '(') {
    return;
  }
  tmp_i4 = String_Parse(param_3,&local_528);
  if (tmp_i4 == 0) {
    return;
  }
  tmp_i4 = String_Parse(param_3,&local_524);
  if (tmp_i4 == 0) {
    return;
  }
  if (local_524 == (char *)0x0) {
    return;
  }
  if (*local_524 != ')') {
    return;
  }
  if (tmp_l3 == 2) {
    tmp_i4 = Q_stricmp(tmp_u2,"UIProfileIsActiveProfile");
    if (tmp_i4 == 0) {
      (**(void **)(DC + 0x70))("ui_profile",local_51c,0x100);
      Q_CleanStr(local_51c);
      Q_CleanDirName(local_51c);
      (**(void **)(DC + 0x70))("cl_profile",local_41c,0x100);
      tmp_i4 = Q_stricmp(local_51c,local_41c);
      if (tmp_i4 != 0) goto LAB_000f3e31;
    }
    else {
      tmp_i4 = Q_stricmp(tmp_u2,"UIProfileValidName");
      if (tmp_i4 != 0) {
        tmp_i4 = Q_stricmp(tmp_u2,"UIProfileAlreadyExists");
        if (tmp_i4 == 0) {
          tmp_pc1 = "ui_profile";
        }
        else {
          tmp_i4 = Q_stricmp(tmp_u2,"UIProfileAlreadyExists_Rename");
          if (tmp_i4 != 0) {
            tmp_i4 = Q_stricmp(tmp_u2,"ReadyToCreateProfile");
            if (tmp_i4 == 0) {
              (**(void **)(DC + 0x70))("ui_profile",local_51c,0x100);
              Q_strncpyz(local_41c,local_51c,0x100);
              Q_CleanStr(local_41c);
              Q_CleanDirName(local_41c);
              tmp_u2 = va("profiles/%s/profile.dat",local_41c);
              tmp_i4 = trap_FS_FOpenFile(tmp_u2,&local_520,0);
              if (-1 < tmp_i4) {
                trap_FS_FCloseFile(local_520);
                (**(void **)(DC + 0x74))("ui_rate");
                goto LAB_000f3e31;
              }
              tmp_l5 = (long double)(**(void **)(DC + 0x74))("ui_rate");
              local_41c[0]._0_1_ = (char)local_51c[0];
              if ((int)ROUND(tmp_l5) < 1) goto LAB_000f3e31;
              goto joined_r0x000f4665;
            }
            tmp_i4 = Q_stricmp(tmp_u2,"vidrestartIsRequired");
            if (tmp_i4 != 0) {
              tmp_i4 = Q_stricmp(tmp_u2,"ROldModeCheck");
              if (tmp_i4 != 0) {
                return;
              }
              tmp_l5 = (long double)(**(void **)(DC + 0x74))("r_mode");
              (**(void **)(DC + 0x70))("r_oldMode",local_41c,0x100);
              tmp_l3 = strtol((char *)local_41c,(char **)0x0,10);
              if ((char)local_41c[0] == '\0') {
                if ((int)ROUND(tmp_l5) != tmp_l3) goto LAB_000f3e31;
              }
              else if ((int)ROUND(tmp_l5) != tmp_l3) goto LAB_000f3ed8;
              trap_Cvar_Set("r_oldMode",&g_unk_0011d841);
              goto LAB_000f3e31;
            }
            tmp_l5 = (long double)(**(void **)(DC + 0x74))("ui_r_mode");
            tmp_l6 = (long double)(**(void **)(DC + 0x74))("ui_r_colorbits");
            tmp_l7 = (long double)(**(void **)(DC + 0x74))("ui_r_fullscreen");
            tmp_l8 = (long double)(**(void **)(DC + 0x74))("ui_r_texturebits");
            tmp_l9 = (long double)(**(void **)(DC + 0x74))("ui_r_depthbits");
            tmp_l10 = (long double)(**(void **)(DC + 0x74))("ui_r_ext_compressed_textures");
            tmp_l11 = (long double)(**(void **)(DC + 0x74))("ui_r_allowextensions");
            tmp_l12 = (long double)(**(void **)(DC + 0x74))(&g_unk_001209b2);
            tmp_l13 = (long double)(**(void **)(DC + 0x74))("ui_r_detailtextures");
            tmp_l14 = (long double)(**(void **)(DC + 0x74))("ui_r_subdivisions");
            tmp_l15 = (long double)(**(void **)(DC + 0x74))("r_mode");
            tmp_l16 = (long double)(**(void **)(DC + 0x74))("r_colorbits");
            tmp_l17 = (long double)(**(void **)(DC + 0x74))("r_fullscreen");
            tmp_l18 = (long double)(**(void **)(DC + 0x74))("r_texturebits");
            tmp_l19 = (long double)(**(void **)(DC + 0x74))("r_depthbits");
            tmp_l20 = (long double)(**(void **)(DC + 0x74))("r_ext_compressed_textures");
            tmp_l21 = (long double)(**(void **)(DC + 0x74))("r_allowextensions");
            tmp_l22 = (long double)(**(void **)(DC + 0x74))("s_khz");
            tmp_l23 = (long double)(**(void **)(DC + 0x74))("r_detailtextures");
            tmp_l24 = (long double)(**(void **)(DC + 0x74))("r_subdivisions");
            trap_Cvar_VariableStringBuffer("ui_r_texturemode",local_51c,0x100);
            trap_Cvar_VariableStringBuffer("r_texturemode",local_41c,0x100);
            if (((((((int)ROUND((float)tmp_l14) == (int)ROUND((float)tmp_l24)) &&
                   ((int)ROUND((float)tmp_l5) == (int)ROUND((float)tmp_l15))) &&
                  ((int)ROUND(tmp_l6) == (int)ROUND(tmp_l16))) &&
                 (((int)ROUND(tmp_l7) == (int)ROUND(tmp_l17) &&
                  ((int)ROUND(tmp_l8) == (int)ROUND(tmp_l18))))) &&
                (((int)ROUND(tmp_l9) == (int)ROUND(tmp_l19) &&
                 (((int)ROUND(tmp_l10) == (int)ROUND(tmp_l20) &&
                  ((int)ROUND(tmp_l11) == (int)ROUND(tmp_l21))))))) &&
               (((int)ROUND(tmp_l12) == (int)ROUND(tmp_l22) &&
                (((int)ROUND(tmp_l13) == (int)ROUND(tmp_l23) &&
                 (tmp_i4 = Q_stricmp(local_41c,local_51c), tmp_i4 == 0)))))) goto LAB_000f3e31;
            goto LAB_000f3ed8;
          }
          tmp_pc1 = "ui_profile_renameto";
        }
        (**(void **)(DC + 0x70))(tmp_pc1,local_41c,0x100);
        Q_CleanStr(local_41c);
        Q_CleanDirName(local_41c);
        tmp_u2 = va("profiles/%s/profile.dat",local_41c);
        tmp_i4 = trap_FS_FOpenFile(tmp_u2,local_51c,0);
        if (-1 < tmp_i4) {
          trap_FS_FCloseFile(local_51c[0]);
          local_528 = local_52c;
        }
        goto LAB_000f3e31;
      }
      (**(void **)(DC + 0x70))("ui_profile",local_51c,0x100);
      Q_strncpyz(local_41c,local_51c,0x100);
      Q_CleanStr(local_41c);
      Q_CleanDirName(local_41c);
      if ((char)local_51c[0] == '\0') goto LAB_000f3e31;
joined_r0x000f4665:
      if ((char)local_41c[0] == '\0') goto LAB_000f3e31;
    }
  }
  else if (tmp_l3 == 3) {
    tmp_i4 = Int_Parse(param_3,local_41c);
    if (tmp_i4 == 0) {
      return;
    }
    tmp_l5 = (long double)(**(void **)(DC + 0x74))(tmp_u2);
    if ((long double)local_41c[0] != tmp_l5) goto LAB_000f3e31;
  }
  else {
    if (tmp_l3 == 1) {
      (**(void **)(DC + 0x70))(tmp_u2,local_41c,0x400);
      goto joined_r0x000f4665;
    }
    tmp_l5 = (long double)(**(void **)(DC + 0x74))(tmp_u2);
    if (tmp_l5 == (long double)0) goto LAB_000f3e31;
  }
LAB_000f3ed8:
  local_528 = local_52c;
LAB_000f3e31:
  Item_RunScript(param_1,param_2,local_528);
  return;
}

bool Item_EnableShowViaCvar(int param_1,uint param_2)
{
  uint tmp_u1;
  char *tmp_pc2;
  int tmp_i3;
  uint32_t *local_820;
  uint32_t local_81c [256];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  tmp_u1 = 0;
  uStack_14 = 0xf474b;
  local_820 = local_81c;
  do {
    *(uint32_t *)((int)local_820 + tmp_u1) = 0;
    *(uint32_t *)((int)local_81c + tmp_u1 + 4) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x400);
  if (param_1 != 0) {
    if (*(char **)(param_1 + 0x11c) == (char *)0x0) {
      return true;
    }
    if (**(char **)(param_1 + 0x11c) == '\0') {
      return true;
    }
    tmp_pc2 = *(char **)(param_1 + 0x118);
    if (tmp_pc2 == (char *)0x0) {
      return true;
    }
    if (*tmp_pc2 == '\0') {
      return true;
    }
    (**(void **)(DC + 0x70))(tmp_pc2,local_41c,0x400);
    Q_strcat(local_820,0x400,*(uint32_t *)(param_1 + 0x11c));
    do {
      while( true ) {
        do {
          tmp_pc2 = (char *)COM_ParseExt(&local_820,0);
          if ((tmp_pc2 == (char *)0x0) || (*tmp_pc2 == '\0')) {
            return (*(uint *)(param_1 + 0x120) & param_2) == 0;
          }
          tmp_pc2 = (char *)String_Alloc(tmp_pc2);
        } while ((*tmp_pc2 == ';') && (tmp_pc2[1] == '\0'));
        if ((*(uint *)(param_1 + 0x120) & param_2) != 0) break;
        tmp_i3 = Q_stricmp(local_41c,tmp_pc2);
        if (tmp_i3 == 0) {
          return false;
        }
      }
      tmp_i3 = Q_stricmp(local_41c,tmp_pc2);
    } while (tmp_i3 != 0);
  }
  return true;
}

uint Item_SettingShow(int param_1,int param_2)
{
  uint tmp_u1;
  char local_40c [1024];
  
  if (param_2 == 0) {
    (**(void **)(DC + 0x10c))(0x1d);
    if ((*(uint *)(param_1 + 0x260) & 2) == 0) {
      tmp_u1 = 1;
      if ((*(uint *)(param_1 + 0x260) & 1) != 0) {
        tmp_u1 = strtol(local_40c,(char **)0x0,10);
        tmp_u1 = (uint)((*(uint *)(param_1 + 0x25c) & tmp_u1) == 0);
      }
    }
    else {
      tmp_u1 = strtol(local_40c,(char **)0x0,10);
      tmp_u1 = tmp_u1 & *(uint *)(param_1 + 0x25c);
    }
  }
  else {
    trap_Cvar_VariableStringBuffer("cg_ui_voteFlags",local_40c,0x400);
    tmp_u1 = strtol(local_40c,(char **)0x0,10);
    tmp_u1 = (uint)(*(uint *)(param_1 + 0x264) != (tmp_u1 & *(uint *)(param_1 + 0x264)));
  }
  return tmp_u1;
}

uint32_t Item_SetFocus(int param_1,float param_2,float param_3)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  float tmp_f4;
  uint tmp_u5;
  int tmp_i6;
  int tmp_i7;
  int *tmp_pi8;
  bool tmp_b9;
  
  tmp_i6 = DC;
  if ((param_1 == 0) || ((*(uint *)(param_1 + 0x48) & 0x16) != 4)) {
    return 0;
  }
  tmp_u5 = *(uint *)(param_1 + 0x120);
  tmp_i3 = *(int *)(param_1 + 0xec);
  if ((tmp_u5 & 3) != 0) {
    tmp_i7 = Item_EnableShowViaCvar(param_1,1);
    if (tmp_i7 == 0) {
      return 0;
    }
    tmp_u5 = *(uint *)(param_1 + 0x120);
  }
  if (((tmp_u5 & 0xc) != 0) && (tmp_i7 = Item_EnableShowViaCvar(param_1,4), tmp_i7 == 0)) {
    return 0;
  }
  if (((*(byte *)(param_1 + 0x260) & 3) != 0) &&
     (tmp_i7 = Item_SettingShow_constprop_35(), tmp_i7 == 0)) {
    return 0;
  }
  if ((*(int *)(param_1 + 0x264) != 0) && (tmp_i7 = Item_SettingShow_constprop_36(), tmp_i7 == 0)) {
    return 0;
  }
  tmp_pi8 = (int *)(tmp_i6 + 0x1e320);
  tmp_i6 = Menu_ClearFocus(*(uint32_t *)(param_1 + 0xec));
  if (*(int *)(param_1 + 200) == 0) {
    tmp_f1 = *(float *)(param_1 + 0xb8);
    tmp_f2 = *(float *)(DC + 0x2003c);
    if (tmp_f2 <= 1.3333334) {
      if (tmp_f1 < param_2) {
        tmp_f1 = *(float *)(param_1 + 0xc0) + tmp_f1;
        goto LAB_000f4aea;
      }
    }
    else {
      tmp_f4 = tmp_f2 * 0.75;
      param_2 = param_2 * tmp_f4;
      if (tmp_f1 * tmp_f4 < param_2) {
        tmp_f1 = *(float *)(param_1 + 0xc0) + tmp_f1;
        if (1.3333334 < tmp_f2) {
          tmp_f1 = tmp_f4 * tmp_f1;
        }
LAB_000f4aea:
        tmp_f2 = *(float *)(param_1 + 0xbc) - *(float *)(param_1 + 0xc4);
        tmp_b9 = param_2 < tmp_f1 && tmp_f2 < param_3;
        if ((param_2 < tmp_f1 && tmp_f2 < param_3) && (param_3 < tmp_f2 + *(float *)(param_1 + 0xc4)))
        {
          *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 2;
          if (*(int *)(param_1 + 0x124) == 0) goto LAB_000f4c50;
          tmp_pi8 = (int *)(param_1 + 0x124);
          goto LAB_000f4c55;
        }
      }
    }
    if ((tmp_i6 != 0) &&
       (*(uint *)(tmp_i6 + 0x48) = *(uint *)(tmp_i6 + 0x48) | 2, *(int *)(tmp_i6 + 0x10c) != 0)) {
      Item_RunScript_constprop_37();
    }
  }
  else {
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 2;
    if (*(int *)(param_1 + 0x10c) != 0) {
      Item_RunScript_constprop_37();
    }
    tmp_i6 = *(int *)(param_1 + 0x124);
    if (tmp_i6 == 0) {
LAB_000f4c50:
      tmp_b9 = tmp_pi8 != (int *)0x0;
LAB_000f4c55:
      if (!tmp_b9) goto LAB_000f4c17;
      tmp_i6 = *tmp_pi8;
    }
    (**(void **)(DC + 0x88))(tmp_i6,6);
  }
LAB_000f4c17:
  if (0 < *(int *)(tmp_i3 + 0xc0)) {
    tmp_i7 = 0;
    tmp_i6 = *(int *)(tmp_i3 + 0x514);
    while( true ) {
      if (tmp_i6 == param_1) {
        *(int *)(tmp_i3 + 200) = tmp_i7;
        return 1;
      }
      tmp_i7 = tmp_i7 + 1;
      if (tmp_i7 == *(int *)(tmp_i3 + 0xc0)) break;
      tmp_i6 = *(int *)(tmp_i3 + 0x514 + tmp_i7 * 4);
    }
  }
  return 1;
}

int Item_ListBox_MaxScroll(int param_1)
{
  int tmp_i1;
  float tmp_f2;
  int tmp_i3;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  tmp_i3 = (**(void **)(DC + 0x90))(*(uint32_t *)(param_1 + 0x248));
  if ((*(byte *)(param_1 + 0x49) & 4) == 0) {
    tmp_f2 = *(float *)(param_1 + 0xc) / *(float *)(tmp_i1 + 0x14);
  }
  else {
    tmp_f2 = *(float *)(param_1 + 8) / *(float *)(tmp_i1 + 0x10);
  }
  tmp_i3 = tmp_i3 - (int)ROUND(tmp_f2);
  if (tmp_i3 < 0) {
    tmp_i3 = 0;
  }
  return tmp_i3;
}

int Item_ListBox_ThumbPosition(float *param_1)
{
  int *tmp_pi1;
  float tmp_f2;
  int tmp_i3;
  
  tmp_pi1 = (int *)param_1[0x94];
  tmp_i3 = (**(void **)(DC + 0x90))(param_1[0x92]);
  if ((*(byte *)((int)param_1 + 0x49) & 4) == 0) {
    tmp_i3 = tmp_i3 - (int)ROUND(param_1[3] / (float)tmp_pi1[5]);
    if (-1 < tmp_i3) {
      tmp_f2 = (float)tmp_i3;
      if (0.0 < tmp_f2) {
        tmp_f2 = (((param_1[3] - 32.0) - 2.0) - 16.0) / tmp_f2;
        goto LAB_000f4ee2;
      }
    }
    tmp_f2 = 0.0;
LAB_000f4ee2:
    return (int)ROUND(param_1[1] + 1.0 + 16.0 + (float)*tmp_pi1 * tmp_f2);
  }
  tmp_i3 = tmp_i3 - (int)ROUND(param_1[2] / (float)tmp_pi1[4]);
  if (-1 < tmp_i3) {
    tmp_f2 = (float)tmp_i3;
    if (0.0 < tmp_f2) {
      tmp_f2 = (((param_1[2] - 32.0) - 2.0) - 16.0) / tmp_f2;
      goto LAB_000f4e22;
    }
  }
  tmp_f2 = 0.0;
LAB_000f4e22:
  return (int)ROUND(*param_1 + 1.0 + 16.0 + (float)*tmp_pi1 * tmp_f2);
}

int Item_ListBox_ThumbDrawPosition(float *param_1)
{
  float tmp_f1;
  int *tmp_pi2;
  float tmp_f3;
  int tmp_i4;
  int local_1c;
  
  if (itemCapture == param_1) {
    if ((*(byte *)((int)itemCapture + 0x49) & 4) == 0) {
      tmp_f1 = itemCapture[1];
      tmp_f3 = itemCapture[3] + tmp_f1;
      tmp_i4 = *(int *)(DC + 0x128);
    }
    else {
      tmp_f1 = *itemCapture;
      tmp_f3 = itemCapture[2] + tmp_f1;
      tmp_i4 = *(int *)(DC + 0x124);
    }
    local_1c = (int)ROUND((tmp_f3 - 32.0) - 1.0);
    tmp_f3 = (float)tmp_i4;
    if (((float)(int)ROUND(tmp_f1 + 16.0 + 1.0) + 8.0 <= tmp_f3) && (tmp_f3 <= (float)local_1c + 8.0))
    {
      return (int)ROUND(tmp_f3 - 8.0);
    }
    tmp_i4 = Item_ListBox_ThumbPosition();
    return tmp_i4;
  }
  tmp_pi2 = (int *)param_1[0x94];
  tmp_i4 = (**(void **)(DC + 0x90))(param_1[0x92]);
  if ((*(byte *)((int)param_1 + 0x49) & 4) == 0) {
    tmp_i4 = tmp_i4 - (int)ROUND(param_1[3] / (float)tmp_pi2[5]);
    if (-1 < tmp_i4) {
      tmp_f1 = (float)tmp_i4;
      if (0.0 < tmp_f1) {
        tmp_f1 = (((param_1[3] - 32.0) - 2.0) - 16.0) / tmp_f1;
        goto LAB_000f507e;
      }
    }
    tmp_f1 = 0.0;
LAB_000f507e:
    return (int)ROUND(param_1[1] + 1.0 + 16.0 + (float)*tmp_pi2 * tmp_f1);
  }
  tmp_i4 = tmp_i4 - (int)ROUND(param_1[2] / (float)tmp_pi2[4]);
  if (-1 < tmp_i4) {
    tmp_f1 = (float)tmp_i4;
    if (0.0 < tmp_f1) {
      tmp_f1 = (((param_1[2] - 32.0) - 2.0) - 16.0) / tmp_f1;
      goto LAB_000f4fe0;
    }
  }
  tmp_f1 = 0.0;
LAB_000f4fe0:
  return (int)ROUND(*param_1 + 1.0 + 16.0 + (float)*tmp_pi2 * tmp_f1);
}

long double Item_Slider_ThumbPosition(float *param_1)
{
  float *pfVar1;
  long double tmp_l2;
  long double tmp_l3;
  long double tmp_l4;
  long double tmp_l5;
  long double tmp_l6;
  
  pfVar1 = (float *)param_1[0x94];
  if (param_1[0x3a] == 0.0) {
    tmp_l2 = (long double)*param_1;
  }
  else {
    tmp_l2 = (long double)param_1[0x2e] + (long double)param_1[0x30] + (long double)8.0;
  }
  if ((pfVar1 == (float *)0x0) && (param_1[0x45] != 0.0)) {
    return tmp_l2;
  }
  tmp_l3 = (long double)(**(void **)(DC + 0x74))(param_1[0x45]);
  tmp_l4 = (long double)*pfVar1;
  tmp_l5 = (long double)pfVar1[1];
  tmp_l6 = tmp_l4;
  if ((tmp_l4 <= tmp_l3) && (tmp_l6 = tmp_l3, tmp_l5 < tmp_l3)) {
    tmp_l6 = tmp_l5;
  }
  return ((tmp_l6 - tmp_l4) / (tmp_l5 - tmp_l4)) * (long double)96.0 + (long double)(float)tmp_l2;
}

uint32_t Item_Slider_OverSlider(float *param_1,float param_2,float param_3)
{
  float *pfVar1;
  uint32_t tmp_u2;
  long double tmp_l3;
  long double tmp_l4;
  long double tmp_l5;
  long double tmp_l6;
  long double tmp_l7;
  
  pfVar1 = (float *)param_1[0x94];
  if (param_1[0x3a] == 0.0) {
    tmp_l3 = (long double)*param_1;
  }
  else {
    tmp_l3 = (long double)param_1[0x2e] + (long double)param_1[0x30] + (long double)8.0;
  }
  if ((pfVar1 != (float *)0x0) || (param_1[0x45] == 0.0)) {
    tmp_l4 = (long double)(**(void **)(DC + 0x74))(param_1[0x45]);
    tmp_l5 = (long double)*pfVar1;
    tmp_l6 = (long double)pfVar1[1];
    tmp_l7 = tmp_l5;
    if ((tmp_l5 <= tmp_l4) && (tmp_l7 = tmp_l4, tmp_l6 < tmp_l4)) {
      tmp_l7 = tmp_l6;
    }
    tmp_l3 = ((tmp_l7 - tmp_l5) / (tmp_l6 - tmp_l5)) * (long double)96.0 + (long double)(float)tmp_l3;
  }
  tmp_l3 = tmp_l3 - (long double)6.0;
  tmp_l7 = (long double)*(float *)(DC + 0x2003c);
  if (tmp_l7 <= (long double)1.3333334) {
    if ((long double)param_2 <= tmp_l3) {
      return 0;
    }
    tmp_l3 = tmp_l3 + (long double)12.0;
    tmp_l4 = (long double)param_2;
  }
  else {
    tmp_l5 = (long double)0.75 * tmp_l7;
    tmp_l4 = (long double)param_2 * tmp_l5;
    if (tmp_l4 <= tmp_l3 * tmp_l5) {
      return 0;
    }
    tmp_l3 = tmp_l3 + (long double)12.0;
    if ((long double)1.3333334 < tmp_l7) {
      tmp_l3 = tmp_l3 * tmp_l5;
    }
  }
  if ((tmp_l4 < tmp_l3) && (param_1[1] < param_3)) {
    tmp_u2 = 0x2000;
    if (param_1[1] + 12.0 <= param_3) {
      tmp_u2 = 0;
    }
    return tmp_u2;
  }
  return 0;
}

uint32_t Item_ListBox_OverLB(float *param_1,float param_2,float param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  int tmp_i7;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_f1 = *param_1;
  if ((*(byte *)((int)param_1 + 0x49) & 4) == 0) {
    local_14 = 16.0;
    local_1c = (tmp_f1 + param_1[2]) - 16.0;
    tmp_f1 = param_1[1];
    tmp_f2 = *(float *)(DC + 0x2003c);
    tmp_f4 = param_2;
    tmp_f5 = local_1c;
    if (1.3333334 < tmp_f2) {
      tmp_f4 = param_2 * tmp_f2 * 0.75;
      tmp_f5 = tmp_f2 * 0.75 * local_1c;
    }
    tmp_f3 = param_2;
    if (tmp_f5 < tmp_f4) {
      if (1.3333334 < tmp_f2) {
        if ((tmp_f4 < tmp_f2 * 0.75 * (local_1c + 16.0)) && (tmp_f1 < param_3)) goto LAB_000f5770;
        goto LAB_000f57b0;
      }
      if ((tmp_f4 < local_1c + 16.0) && (tmp_f1 < param_3)) {
LAB_000f5770:
        if (param_3 < tmp_f1 + 16.0) {
          return 0x800;
        }
        goto LAB_000f57b0;
      }
      local_18 = (tmp_f1 + param_1[3]) - 16.0;
      tmp_f1 = local_1c;
LAB_000f57e5:
      if (tmp_f1 < tmp_f3) {
        tmp_f1 = local_1c + 16.0;
        if (1.3333334 < tmp_f2) {
          tmp_f1 = tmp_f2 * 0.75 * tmp_f1;
        }
LAB_000f580b:
        if (((tmp_f3 < tmp_f1) && (local_18 < param_3)) && (param_3 < local_18 + 16.0)) {
          return 0x1000;
        }
      }
    }
    else {
LAB_000f57b0:
      local_18 = (tmp_f1 + param_1[3]) - 16.0;
      if (1.3333334 < tmp_f2) {
        tmp_f3 = param_2 * tmp_f2 * 0.75;
        tmp_f1 = tmp_f2 * 0.75 * local_1c;
        goto LAB_000f57e5;
      }
      if (local_1c < param_2) {
        tmp_f1 = local_1c + 16.0;
        goto LAB_000f580b;
      }
    }
    local_10 = local_14;
    tmp_i6 = Item_ListBox_ThumbDrawPosition(param_1);
    local_18 = (float)tmp_i6;
    tmp_i7 = Rect_ContainsPoint(&local_1c,param_2,param_3);
    if (tmp_i7 != 0) {
      return 0x2000;
    }
    tmp_f1 = param_1[1];
    local_18 = tmp_f1 + 16.0;
    local_10 = (float)tmp_i6 - local_18;
    tmp_i7 = Rect_ContainsPoint(&local_1c,param_2,param_3);
    if (tmp_i7 != 0) {
      return 0x4000;
    }
    local_18 = (float)tmp_i6 + 16.0;
    tmp_f2 = param_1[3];
    local_10 = (tmp_f1 + tmp_f2) - 16.0;
    tmp_i6 = Rect_ContainsPoint(&local_1c,param_2,param_3);
    if (tmp_i6 != 0) {
      return 0x8000;
    }
    local_18 = tmp_f1;
    local_10 = tmp_f2;
    tmp_i6 = Rect_ContainsPoint(&local_1c,param_2,param_3);
    goto joined_r0x000f5bd7;
  }
  local_14 = 16.0;
  local_18 = (param_1[1] + param_1[3]) - 16.0;
  tmp_f2 = *(float *)(DC + 0x2003c);
  tmp_f4 = param_2;
  tmp_f5 = tmp_f1;
  if (1.3333334 < tmp_f2) {
    tmp_f4 = param_2 * tmp_f2 * 0.75;
    tmp_f5 = tmp_f2 * 0.75 * tmp_f1;
  }
  tmp_f3 = param_2;
  if (tmp_f4 <= tmp_f5) {
LAB_000f55d0:
    local_1c = (tmp_f1 + param_1[2]) - 16.0;
    if (1.3333334 < tmp_f2) {
      tmp_f3 = param_2 * tmp_f2 * 0.75;
      tmp_f1 = tmp_f2 * 0.75 * local_1c;
      goto LAB_000f5605;
    }
    if (local_1c < param_2) {
      tmp_f1 = local_1c + 16.0;
      goto LAB_000f5627;
    }
  }
  else {
    if (1.3333334 < tmp_f2) {
      if ((tmp_f4 < tmp_f2 * 0.75 * (tmp_f1 + 16.0)) && (local_18 < param_3)) goto LAB_000f5591;
      goto LAB_000f55d0;
    }
    if ((tmp_f4 < tmp_f1 + 16.0) && (local_18 < param_3)) {
LAB_000f5591:
      if (param_3 < local_18 + 16.0) {
        return 0x800;
      }
      goto LAB_000f55d0;
    }
    local_1c = (tmp_f1 + param_1[2]) - 16.0;
    tmp_f1 = local_1c;
LAB_000f5605:
    if (tmp_f1 < tmp_f3) {
      tmp_f1 = local_1c + 16.0;
      if (1.3333334 < tmp_f2) {
        tmp_f1 = tmp_f2 * 0.75 * tmp_f1;
      }
LAB_000f5627:
      if (((tmp_f3 < tmp_f1) && (local_18 < param_3)) && (param_3 < local_18 + 16.0)) {
        return 0x1000;
      }
    }
  }
  local_10 = local_14;
  tmp_i6 = Item_ListBox_ThumbDrawPosition(param_1);
  local_1c = (float)tmp_i6;
  tmp_i7 = Rect_ContainsPoint(&local_1c,param_2,param_3);
  if (tmp_i7 != 0) {
    return 0x2000;
  }
  tmp_f1 = *param_1;
  local_1c = tmp_f1 + 16.0;
  local_14 = (float)tmp_i6 - local_1c;
  tmp_i7 = Rect_ContainsPoint(&local_1c,param_2,param_3);
  if (tmp_i7 != 0) {
    return 0x4000;
  }
  local_1c = (float)tmp_i6 + 16.0;
  tmp_f2 = param_1[2];
  local_14 = (tmp_f1 + tmp_f2) - 16.0;
  tmp_i6 = Rect_ContainsPoint(&local_1c,param_2,param_3);
  if (tmp_i6 != 0) {
    return 0x8000;
  }
  local_1c = tmp_f1;
  local_14 = tmp_f2;
  tmp_i6 = Rect_ContainsPoint(&local_1c,param_2,param_3);
joined_r0x000f5bd7:
  if (tmp_i6 == 0) {
    return 0;
  }
  return 0x40000000;
}

void Item_ListBox_MouseEnter(float *param_1,float param_2,float param_3,int param_4)
{
  float tmp_f1;
  float tmp_f2;
  int *tmp_pi3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  int tmp_i8;
  int tmp_i9;
  uint tmp_u10;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_f2 = param_1[0x12];
  tmp_pi3 = (int *)param_1[0x94];
  tmp_f7 = (float)((uint)tmp_f2 & 0xbfff07ff);
  param_1[0x12] = tmp_f7;
  if (((uint)tmp_f2 & 0x400) == 0) {
    local_24 = 16.0;
    local_2c = (*param_1 + param_1[2]) - 16.0;
    tmp_f2 = param_1[1];
    tmp_f1 = *(float *)(DC + 0x2003c);
    tmp_f5 = param_2;
    tmp_f6 = local_2c;
    if (1.3333334 < tmp_f1) {
      tmp_f5 = param_2 * tmp_f1 * 0.75;
      tmp_f6 = tmp_f1 * 0.75 * local_2c;
    }
    tmp_f4 = param_2;
    if (tmp_f5 <= tmp_f6) {
LAB_000f6000:
      local_28 = (tmp_f2 + param_1[3]) - 16.0;
      if (1.3333334 < tmp_f1) {
        tmp_f4 = param_2 * tmp_f1 * 0.75;
        tmp_f2 = tmp_f1 * 0.75 * local_2c;
        goto LAB_000f6035;
      }
      if (local_2c < param_2) {
        tmp_f2 = local_2c + 16.0;
        goto LAB_000f605b;
      }
    }
    else {
      if (1.3333334 < tmp_f1) {
        if ((tmp_f5 < tmp_f1 * 0.75 * (local_2c + 16.0)) && (tmp_f2 < param_3)) goto LAB_000f5fc4;
        goto LAB_000f6000;
      }
      if ((tmp_f5 < local_2c + 16.0) && (tmp_f2 < param_3)) {
LAB_000f5fc4:
        if (param_3 < tmp_f2 + 16.0) {
          tmp_u10 = 0x800;
          goto LAB_000f5e40;
        }
        goto LAB_000f6000;
      }
      local_28 = (tmp_f2 + param_1[3]) - 16.0;
      tmp_f2 = local_2c;
LAB_000f6035:
      if (tmp_f2 < tmp_f4) {
        tmp_f2 = local_2c + 16.0;
        if (1.3333334 < tmp_f1) {
          tmp_f2 = tmp_f1 * 0.75 * tmp_f2;
        }
LAB_000f605b:
        if (((tmp_f4 < tmp_f2) && (local_28 < param_3)) && (param_3 < local_28 + 16.0)) {
          tmp_u10 = 0x1000;
          goto LAB_000f5e40;
        }
      }
    }
    local_20 = local_24;
    tmp_i8 = Item_ListBox_ThumbDrawPosition(param_1);
    local_28 = (float)tmp_i8;
    tmp_i9 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i9 != 0) goto LAB_000f5e2a;
    tmp_f2 = param_1[1];
    local_28 = tmp_f2 + 16.0;
    local_20 = (float)tmp_i8 - local_28;
    tmp_i9 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i9 != 0) goto LAB_000f6191;
    local_28 = (float)tmp_i8 + 16.0;
    tmp_f7 = param_1[3];
    local_20 = (tmp_f2 + tmp_f7) - 16.0;
    tmp_i8 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i8 != 0) goto LAB_000f654b;
    local_28 = tmp_f2;
    local_20 = tmp_f7;
    tmp_i8 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    tmp_f7 = param_1[0x12];
    if (tmp_i8 == 0) {
      tmp_u10 = 0;
      goto LAB_000f5e40;
    }
  }
  else {
    tmp_f2 = *param_1;
    local_24 = 16.0;
    local_28 = (param_1[1] + param_1[3]) - 16.0;
    tmp_f1 = *(float *)(DC + 0x2003c);
    tmp_f5 = param_2;
    tmp_f6 = tmp_f2;
    if (1.3333334 < tmp_f1) {
      tmp_f5 = param_2 * tmp_f1 * 0.75;
      tmp_f6 = tmp_f1 * 0.75 * tmp_f2;
    }
    tmp_f4 = param_2;
    if (tmp_f5 <= tmp_f6) {
LAB_000f5d30:
      local_2c = (tmp_f2 + param_1[2]) - 16.0;
      if (1.3333334 < tmp_f1) {
        tmp_f4 = param_2 * tmp_f1 * 0.75;
        tmp_f2 = tmp_f1 * 0.75 * local_2c;
        goto LAB_000f5d65;
      }
      if (local_2c < param_2) {
        tmp_f2 = local_2c + 16.0;
        goto LAB_000f5d87;
      }
    }
    else {
      if (1.3333334 < tmp_f1) {
        if ((tmp_f5 < tmp_f1 * 0.75 * (tmp_f2 + 16.0)) && (local_28 < param_3)) goto LAB_000f5ce7;
        goto LAB_000f5d30;
      }
      if ((tmp_f5 < tmp_f2 + 16.0) && (local_28 < param_3)) {
LAB_000f5ce7:
        tmp_u10 = 0x800;
        if (param_3 < local_28 + 16.0) goto LAB_000f5e40;
        goto LAB_000f5d30;
      }
      local_2c = (tmp_f2 + param_1[2]) - 16.0;
      tmp_f2 = local_2c;
LAB_000f5d65:
      if (tmp_f2 < tmp_f4) {
        tmp_f2 = local_2c + 16.0;
        if (1.3333334 < tmp_f1) {
          tmp_f2 = tmp_f1 * 0.75 * tmp_f2;
        }
LAB_000f5d87:
        if (((tmp_f4 < tmp_f2) && (local_28 < param_3)) &&
           (tmp_u10 = 0x1000, param_3 < local_28 + 16.0)) goto LAB_000f5e40;
      }
    }
    local_20 = local_24;
    tmp_i8 = Item_ListBox_ThumbDrawPosition(param_1);
    local_2c = (float)tmp_i8;
    tmp_i9 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i9 != 0) {
LAB_000f5e2a:
      tmp_f7 = param_1[0x12];
      tmp_u10 = 0x2000;
      goto LAB_000f5e40;
    }
    tmp_f2 = *param_1;
    local_2c = tmp_f2 + 16.0;
    local_24 = (float)tmp_i8 - local_2c;
    tmp_i9 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i9 != 0) {
LAB_000f6191:
      tmp_f7 = param_1[0x12];
      tmp_u10 = 0x4000;
      goto LAB_000f5e40;
    }
    local_2c = (float)tmp_i8 + 16.0;
    tmp_f7 = param_1[2];
    local_24 = (tmp_f2 + tmp_f7) - 16.0;
    tmp_i8 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i8 != 0) {
LAB_000f654b:
      tmp_f7 = param_1[0x12];
      tmp_u10 = 0x8000;
      goto LAB_000f5e40;
    }
    local_2c = tmp_f2;
    local_24 = tmp_f7;
    tmp_i8 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    tmp_f7 = param_1[0x12];
    if (tmp_i8 == 0) {
      tmp_u10 = 0;
      goto LAB_000f5e40;
    }
  }
  tmp_u10 = 0x40000000;
LAB_000f5e40:
  param_1[0x12] = (float)((uint)tmp_f7 | tmp_u10);
  if (param_4 != 0) {
    if (((uint)tmp_f7 & 0x400) == 0) {
      if (((uint)tmp_f7 & 0x4000f800) == 0 && tmp_u10 == 0) {
        tmp_f2 = *param_1;
        tmp_f7 = param_1[1];
        tmp_f1 = *(float *)(DC + 0x2003c);
        if (tmp_f1 <= 1.3333334) {
          if (param_2 <= tmp_f2) {
            return;
          }
          tmp_f2 = (param_1[2] - 16.0) + tmp_f2;
        }
        else {
          tmp_f5 = tmp_f1 * 0.75;
          param_2 = param_2 * tmp_f5;
          if (param_2 <= tmp_f2 * tmp_f5) {
            return;
          }
          tmp_f2 = (param_1[2] - 16.0) + tmp_f2;
          if (1.3333334 < tmp_f1) {
            tmp_f2 = tmp_f5 * tmp_f2;
          }
        }
        if (((param_2 < tmp_f2) && (tmp_f7 < param_3)) &&
           (param_3 < (param_1[3] - (float)tmp_pi3[2]) + tmp_f7)) {
          tmp_i8 = (int)ROUND(((param_3 - 2.0) - tmp_f7) / (float)tmp_pi3[5]) + *tmp_pi3;
          tmp_pi3[3] = tmp_i8;
          if (tmp_pi3[1] < tmp_i8) {
            tmp_pi3[3] = tmp_pi3[1];
          }
        }
      }
    }
    else if ((((uint)tmp_f7 & 0x4000f800) == 0 && tmp_u10 == 0) && (tmp_pi3[6] == 1)) {
      tmp_f2 = *param_1;
      tmp_f7 = *(float *)(DC + 0x2003c);
      if (1.3333334 < tmp_f7) {
        tmp_f5 = tmp_f7 * 0.75;
        tmp_f1 = param_2 * tmp_f5;
        if (tmp_f1 <= tmp_f2 * tmp_f5) {
          return;
        }
        tmp_f6 = (param_1[2] - (float)tmp_pi3[2]) + tmp_f2;
        if (1.3333334 < tmp_f7) {
          tmp_f6 = tmp_f5 * tmp_f6;
        }
      }
      else {
        if (param_2 <= tmp_f2) {
          return;
        }
        tmp_f6 = (param_1[2] - (float)tmp_pi3[2]) + tmp_f2;
        tmp_f1 = param_2;
      }
      if (((tmp_f1 < tmp_f6) && (param_1[1] < param_3)) &&
         (param_3 < (param_1[3] - 16.0) + param_1[1])) {
        tmp_i8 = (int)ROUND((param_2 - tmp_f2) / (float)tmp_pi3[4]) + *tmp_pi3;
        tmp_pi3[3] = tmp_i8;
        if (tmp_pi3[1] <= tmp_i8) {
          tmp_pi3[3] = tmp_pi3[1];
        }
      }
    }
  }
  return;
}

void Item_MouseEnter(int param_1,float param_2,float param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  int tmp_i8;
  uint tmp_u9;
  
  if (param_1 == 0) {
    return;
  }
  tmp_f1 = *(float *)(param_1 + 0xb8);
  tmp_u9 = *(uint *)(param_1 + 0x120);
  tmp_f2 = *(float *)(param_1 + 0xbc);
  tmp_f3 = *(float *)(param_1 + 0xc0);
  tmp_f4 = *(float *)(param_1 + 0xc4);
  if ((tmp_u9 & 3) != 0) {
    tmp_i8 = Item_EnableShowViaCvar(param_1,1);
    if (tmp_i8 == 0) {
      return;
    }
    tmp_u9 = *(uint *)(param_1 + 0x120);
  }
  if (((tmp_u9 & 0xc) != 0) && (tmp_i8 = Item_EnableShowViaCvar(param_1,4), tmp_i8 == 0)) {
    return;
  }
  if (((*(byte *)(param_1 + 0x260) & 3) != 0) &&
     (tmp_i8 = Item_SettingShow_constprop_35(), tmp_i8 == 0)) {
    return;
  }
  if ((*(int *)(param_1 + 0x264) != 0) && (tmp_i8 = Item_SettingShow_constprop_36(), tmp_i8 == 0)) {
    return;
  }
  tmp_f5 = *(float *)(DC + 0x2003c);
  if (1.3333334 < tmp_f5) {
    tmp_f6 = tmp_f5 * 0.75;
    tmp_f7 = param_2 * tmp_f6;
    if (tmp_f7 <= tmp_f1 * tmp_f6) goto LAB_000f67a0;
    if (tmp_f5 <= 1.3333334) goto LAB_000f6860;
    if ((tmp_f1 + tmp_f3) * tmp_f6 <= tmp_f7) goto LAB_000f67a0;
  }
  else {
    tmp_f7 = param_2;
    if (param_2 <= tmp_f1) goto LAB_000f67a0;
LAB_000f6860:
    if (tmp_f1 + tmp_f3 <= tmp_f7) goto LAB_000f67a0;
  }
  tmp_f2 = tmp_f2 - tmp_f4;
  if ((tmp_f2 < param_3) && (param_3 < tmp_f2 + tmp_f4)) {
    tmp_u9 = *(uint *)(param_1 + 0x48);
    if ((tmp_u9 & 0x80) == 0) {
      Item_RunScript_constprop_37();
      tmp_u9 = *(uint *)(param_1 + 0x48) | 0x80;
      *(uint *)(param_1 + 0x48) = tmp_u9;
    }
    if ((tmp_u9 & 1) != 0) {
      return;
    }
    Item_RunScript_constprop_37();
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 1;
    return;
  }
LAB_000f67a0:
  tmp_u9 = *(uint *)(param_1 + 0x48);
  if ((tmp_u9 & 0x80) != 0) {
    Item_RunScript_constprop_37();
    tmp_u9 = *(uint *)(param_1 + 0x48) & 0xffffff7f;
    *(uint *)(param_1 + 0x48) = tmp_u9;
  }
  if ((tmp_u9 & 1) == 0) {
    Item_RunScript_constprop_37();
    tmp_u9 = *(uint *)(param_1 + 0x48) | 1;
    *(uint *)(param_1 + 0x48) = tmp_u9;
  }
  if (*(int *)(param_1 + 200) == 6) {
    *(uint *)(param_1 + 0x48) = tmp_u9 & 0xbfff07ff;
    tmp_u9 = Item_ListBox_OverLB(param_1,param_2,param_3);
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | tmp_u9;
  }
  return;
}

void Item_MouseLeave(int param_1)
{
  if (param_1 != 0) {
    if ((*(byte *)(param_1 + 0x48) & 0x80) != 0) {
      Item_RunScript_constprop_37();
      *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xffffff7f;
    }
    Item_RunScript_constprop_37();
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xffffe7ff;
  }
  return;
}

float * Menu_HitTest(int param_1,float param_2,float param_3)
{
  float tmp_f1;
  float *pfVar2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  
  if (0 < *(int *)(param_1 + 0xc0)) {
    tmp_i6 = 0;
    do {
      pfVar2 = *(float **)(param_1 + 0x514 + tmp_i6 * 4);
      if (pfVar2 != (float *)0x0) {
        tmp_f1 = *(float *)(DC + 0x2003c);
        if (1.3333334 < tmp_f1) {
          tmp_f5 = tmp_f1 * 0.75;
          tmp_f3 = param_2 * tmp_f5;
          if (tmp_f5 * *pfVar2 < tmp_f3) {
            tmp_f4 = *pfVar2 + pfVar2[2];
            if (1.3333334 < tmp_f1) {
              tmp_f4 = tmp_f4 * tmp_f5;
            }
            goto LAB_000f6a9c;
          }
        }
        else if (*pfVar2 < param_2) {
          tmp_f4 = *pfVar2 + pfVar2[2];
          tmp_f3 = param_2;
LAB_000f6a9c:
          if (((tmp_f3 < tmp_f4) && (pfVar2[1] < param_3)) && (param_3 < pfVar2[1] + pfVar2[3])) {
            return pfVar2;
          }
        }
      }
      tmp_i6 = tmp_i6 + 1;
    } while (tmp_i6 != *(int *)(param_1 + 0xc0));
  }
  return (float *)0x0;
}

void Item_SetMouseOver(int param_1,int param_2)
{
  if (param_1 != 0) {
    if (param_2 != 0) {
      *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 1;
      return;
    }
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xfffffffe;
  }
  return;
}

uint32_t Item_OwnerDraw_HandleKey(int param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  
  if ((param_1 != 0) && (*(void **)(DC + 0x8c) != (void *)0x0)) {
    tmp_u1 = (**(void **)(DC + 0x8c))
                      (*(uint32_t *)(param_1 + 0x3c),*(uint32_t *)(param_1 + 0x40),
                       param_1 + 0x248,param_2);
    return tmp_u1;
  }
  return 0;
}

uint32_t Item_CheckBox_HandleKey(float *param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  void *tmp_pc3;
  float tmp_f4;
  float tmp_f5;
  uint32_t tmp_u6;
  int tmp_i7;
  long double tmp_l8;
  
  tmp_f2 = (float)*(int *)(DC + 0x124);
  if (param_1 != (float *)0x0) {
    tmp_f1 = *(float *)(DC + 0x2003c);
    if (tmp_f1 <= 1.3333334) {
      if (tmp_f2 <= *param_1) {
        return 0;
      }
      tmp_f5 = *param_1 + param_1[2];
    }
    else {
      tmp_f4 = tmp_f1 * 0.75;
      tmp_f2 = tmp_f2 * tmp_f4;
      if (tmp_f2 <= tmp_f4 * *param_1) {
        return 0;
      }
      tmp_f5 = *param_1 + param_1[2];
      if (1.3333334 < tmp_f1) {
        tmp_f5 = tmp_f5 * tmp_f4;
      }
    }
    if (tmp_f2 < tmp_f5) {
      if ((((param_1[1] < (float)*(int *)(DC + 0x128)) &&
           ((float)*(int *)(DC + 0x128) < param_1[1] + param_1[3])) &&
          (((uint)param_1[0x12] & 2) != 0)) && (tmp_f2 = param_1[0x45], tmp_f2 != 0.0)) {
        if ((2 < param_2 - 0xb2U) && (param_2 != 0xd)) {
          return 0;
        }
        if (((uint)param_1[0x48] & 0x10) != 0) {
          return 1;
        }
        if (param_1[0x32] == 2.24208e-44) {
          tmp_l8 = (long double)(**(void **)(DC + 0x74))(tmp_f2);
          tmp_i7 = (int)ROUND(tmp_l8 + (long double)1.0);
          if (2 < tmp_i7) {
            tmp_i7 = 0;
          }
          tmp_pc3 = *(void **)(DC + 0x78);
          tmp_u6 = va("%i",tmp_i7);
          (*tmp_pc3)(param_1[0x45],tmp_u6);
          return 1;
        }
        if (param_1[0x9d] == 0.0) {
          tmp_pc3 = *(void **)(DC + 0x78);
          tmp_l8 = (long double)(**(void **)(DC + 0x74))(tmp_f2);
          tmp_u6 = va("%i",(long double)0 == tmp_l8);
          (*tmp_pc3)(param_1[0x45],tmp_u6);
          return 1;
        }
        return 1;
      }
    }
  }
  return 0;
}

uint32_t Item_YesNo_HandleKey(float *param_1,int param_2)
{
  float tmp_f1;
  void *tmp_pc2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint32_t tmp_u6;
  long double tmp_l7;
  
  tmp_f4 = (float)*(int *)(DC + 0x124);
  if (param_1 != (float *)0x0) {
    tmp_f1 = *(float *)(DC + 0x2003c);
    if (tmp_f1 <= 1.3333334) {
      if (tmp_f4 <= *param_1) {
        return 0;
      }
      tmp_f5 = *param_1 + param_1[2];
    }
    else {
      tmp_f3 = tmp_f1 * 0.75;
      tmp_f4 = tmp_f4 * tmp_f3;
      if (tmp_f4 <= tmp_f3 * *param_1) {
        return 0;
      }
      tmp_f5 = *param_1 + param_1[2];
      if (1.3333334 < tmp_f1) {
        tmp_f5 = tmp_f5 * tmp_f3;
      }
    }
    if (tmp_f4 < tmp_f5) {
      if ((((param_1[1] < (float)*(int *)(DC + 0x128)) &&
           ((float)*(int *)(DC + 0x128) < param_1[1] + param_1[3])) &&
          (((uint)param_1[0x12] & 2) != 0)) && (param_1[0x45] != 0.0)) {
        if ((2 < param_2 - 0xb2U) && (param_2 != 0xd)) {
          return 0;
        }
        if (((uint)param_1[0x48] & 0x10) == 0) {
          tmp_pc2 = *(void **)(DC + 0x78);
          tmp_l7 = (long double)(**(void **)(DC + 0x74))(param_1[0x45]);
          tmp_u6 = va("%i",(long double)0 == tmp_l7);
          (*tmp_pc2)(param_1[0x45],tmp_u6);
          return 1;
        }
        return 1;
      }
    }
  }
  return 0;
}

uint32_t Item_Multi_CountSettings(int param_1)
{
  if (*(int *)(param_1 + 0x250) != 0) {
    return *(uint32_t *)(*(int *)(param_1 + 0x250) + 0x180);
  }
  return 0;
}

int Item_Multi_FindCvarByValue(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  float *pfVar4;
  long double tmp_l5;
  uint8_t local_41c [1036];
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 != 0) {
    if (*(int *)(tmp_i1 + 0x184) == 0) {
      tmp_l5 = (long double)(**(void **)(DC + 0x74))(*(uint32_t *)(param_1 + 0x114));
    }
    else {
      (**(void **)(DC + 0x70))(*(uint32_t *)(param_1 + 0x114),local_41c,0x400);
      tmp_l5 = (long double)0;
    }
    tmp_i2 = *(int *)(tmp_i1 + 0x180);
    if (0 < tmp_i2) {
      tmp_i3 = 0;
      pfVar4 = (float *)(tmp_i1 + 0x100);
      do {
        while (*(int *)(tmp_i1 + 0x184) != 0) {
          tmp_i2 = Q_stricmp(local_41c,pfVar4[-0x20]);
          tmp_l5 = (long double)(float)tmp_l5;
          if (tmp_i2 == 0) {
            return tmp_i3;
          }
          tmp_i2 = *(int *)(tmp_i1 + 0x180);
          tmp_i3 = tmp_i3 + 1;
          pfVar4 = pfVar4 + 1;
          if (tmp_i2 <= tmp_i3) {
            return 0;
          }
        }
        if ((long double)*pfVar4 == tmp_l5) {
          return tmp_i3;
        }
        tmp_i3 = tmp_i3 + 1;
        pfVar4 = pfVar4 + 1;
      } while (tmp_i3 < tmp_i2);
    }
  }
  return 0;
}

char * Item_Multi_Setting(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  char *tmp_pc3;
  float *pfVar4;
  int tmp_i5;
  long double tmp_l6;
  uint8_t local_41c [1036];
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 != 0) {
    if (*(int *)(tmp_i1 + 0x184) == 0) {
      tmp_l6 = (long double)(**(void **)(DC + 0x74))(*(uint32_t *)(param_1 + 0x114));
    }
    else {
      (**(void **)(DC + 0x70))(*(uint32_t *)(param_1 + 0x114),local_41c,0x400);
      tmp_l6 = (long double)0;
    }
    tmp_i2 = *(int *)(tmp_i1 + 0x180);
    if (0 < tmp_i2) {
      tmp_i5 = 0;
      pfVar4 = (float *)(tmp_i1 + 0x100);
      do {
        while (*(int *)(tmp_i1 + 0x184) != 0) {
          tmp_i2 = Q_stricmp(local_41c,pfVar4[-0x20]);
          tmp_l6 = (long double)(float)tmp_l6;
          if (tmp_i2 == 0) {
LAB_000f71f6:
            return *(char **)(tmp_i1 + tmp_i5 * 4);
          }
          tmp_i2 = *(int *)(tmp_i1 + 0x180);
          tmp_i5 = tmp_i5 + 1;
          pfVar4 = pfVar4 + 1;
          if (tmp_i2 <= tmp_i5) goto LAB_000f71aa;
        }
        if ((long double)*pfVar4 == tmp_l6) goto LAB_000f71f6;
        tmp_i5 = tmp_i5 + 1;
        pfVar4 = pfVar4 + 1;
      } while (tmp_i5 < tmp_i2);
    }
  }
LAB_000f71aa:
  tmp_pc3 = *(char **)(tmp_i1 + 0x188);
  if (tmp_pc3 == (char *)0x0) {
    if (*(int *)(tmp_i1 + 0x180) == 0) {
      tmp_pc3 = "None Defined";
    }
    else {
      tmp_pc3 = "Custom";
    }
  }
  return tmp_pc3;
}

uint32_t Item_Multi_HandleKey(float *param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  int tmp_i7;
  uint32_t tmp_u8;
  int tmp_i9;
  void *tmp_pc10;
  
  tmp_f2 = param_1[0x94];
  if (tmp_f2 == 0.0) {
    return 0;
  }
  tmp_f4 = (float)*(int *)(DC + 0x124);
  tmp_f1 = *(float *)(DC + 0x2003c);
  if (1.3333334 < tmp_f1) {
    tmp_f3 = tmp_f1 * 0.75;
    tmp_f4 = tmp_f4 * tmp_f3;
    if (tmp_f4 <= tmp_f3 * *param_1) {
      return 0;
    }
    tmp_f5 = *param_1 + param_1[2];
    if (1.3333334 < tmp_f1) {
      if (tmp_f5 * tmp_f3 <= tmp_f4) {
        return 0;
      }
      goto LAB_000f7298;
    }
  }
  else {
    if (tmp_f4 <= *param_1) {
      return 0;
    }
    tmp_f5 = *param_1 + param_1[2];
  }
  if (tmp_f5 <= tmp_f4) {
    return 0;
  }
LAB_000f7298:
  if (((((float)*(int *)(DC + 0x128) <= param_1[1]) ||
       (param_1[1] + param_1[3] <= (float)*(int *)(DC + 0x128))) || (((uint)param_1[0x12] & 2) == 0)
      ) || (param_1[0x45] == 0.0)) {
    return 0;
  }
  if ((2 < param_2 - 0xb2U) && (param_2 != 0xd)) {
    return 0;
  }
  tmp_i6 = Item_Multi_FindCvarByValue(param_1);
  if (param_1[0x94] == 0.0) {
    tmp_i9 = 0;
  }
  else {
    tmp_i9 = *(int *)((int)param_1[0x94] + 0x180);
  }
  tmp_i7 = tmp_i6 + 1;
  if (param_2 == 0xb3) {
    tmp_i7 = tmp_i6 + -1;
  }
  if (tmp_i7 < 0) {
    tmp_i7 = tmp_i9 + -1;
  }
  else if (tmp_i9 <= tmp_i7) {
    tmp_i7 = 0;
  }
  if (*(int *)((int)tmp_f2 + 0x184) == 0) {
    tmp_f2 = *(float *)((int)tmp_f2 + (tmp_i7 + 0x40) * 4);
    if ((float)(int)ROUND(tmp_f2) == tmp_f2) {
      tmp_pc10 = *(void **)(DC + 0x78);
      tmp_u8 = va("%i",(int)ROUND(tmp_f2));
    }
    else {
      tmp_pc10 = *(void **)(DC + 0x78);
      tmp_u8 = va(&g_unk_0011e95f,(double)tmp_f2);
    }
    (*tmp_pc10)(param_1[0x45],tmp_u8);
    return 1;
  }
  (**(void **)(DC + 0x78))(param_1[0x45],*(uint32_t *)((int)tmp_f2 + (tmp_i7 + 0x20) * 4));
  return 1;
}

void Item_StartCapture(float *param_1,uint32_t param_2)
{
  int tmp_i1;
  float tmp_f2;
  float *pfVar3;
  int tmp_i4;
  uint tmp_u5;
  long double tmp_l6;
  long double tmp_l7;
  long double tmp_l8;
  long double tmp_l9;
  long double tmp_l10;
  
  tmp_f2 = param_1[0x32];
  if (tmp_f2 != 8.40779e-45) {
    if ((int)tmp_f2 < 7) {
      if (tmp_f2 != 5.60519e-45) {
        return;
      }
    }
    else if (tmp_f2 != 1.26117e-44) {
      if (tmp_f2 != 1.4013e-44) {
        return;
      }
      pfVar3 = (float *)param_1[0x94];
      tmp_i4 = *(int *)(DC + 0x128);
      tmp_i1 = *(int *)(DC + 0x124);
      if (param_1[0x3a] == 0.0) {
        tmp_l6 = (long double)*param_1;
      }
      else {
        tmp_l6 = (long double)param_1[0x2e] + (long double)param_1[0x30] + (long double)8.0;
      }
      if ((pfVar3 != (float *)0x0) || (param_1[0x45] == 0.0)) {
        tmp_l7 = (long double)(**(void **)(DC + 0x74))(param_1[0x45]);
        tmp_l8 = (long double)*pfVar3;
        tmp_l9 = (long double)pfVar3[1];
        tmp_l10 = tmp_l8;
        if ((tmp_l8 <= tmp_l7) && (tmp_l10 = tmp_l7, tmp_l9 < tmp_l7)) {
          tmp_l10 = tmp_l9;
        }
        tmp_l6 = ((tmp_l10 - tmp_l8) / (tmp_l9 - tmp_l8)) * (long double)96.0 + (long double)(float)tmp_l6;
      }
      tmp_l7 = (long double)tmp_i1;
      tmp_l6 = tmp_l6 - (long double)6.0;
      tmp_l10 = (long double)*(float *)(DC + 0x2003c);
      if (tmp_l10 <= (long double)1.3333334) {
        if (tmp_l7 <= tmp_l6) {
          return;
        }
        tmp_l6 = tmp_l6 + (long double)12.0;
      }
      else {
        tmp_l8 = (long double)0.75 * tmp_l10;
        tmp_l7 = tmp_l7 * tmp_l8;
        if (tmp_l7 <= tmp_l6 * tmp_l8) {
          return;
        }
        tmp_l6 = tmp_l6 + (long double)12.0;
        if ((long double)1.3333334 < tmp_l10) {
          tmp_l6 = tmp_l6 * tmp_l8;
        }
      }
      if (tmp_l6 <= tmp_l7) {
        return;
      }
      if ((float)tmp_i4 <= param_1[1]) {
        return;
      }
      if (param_1[1] + 12.0 <= (float)tmp_i4) {
        return;
      }
      captureData = &scrollInfo;
      captureFunc = Scroll_Slider_ThumbFunc;
      itemCapture = param_1;
      _DAT_00e9a2ec = param_2;
      _DAT_00e9a2f0 = (float)*(int *)(DC + 0x124);
      _DAT_00e9a2f4 = (float)*(int *)(DC + 0x128);
      _DAT_00e9a2f8 = param_1;
      return;
    }
  }
  tmp_u5 = Item_ListBox_OverLB(param_1,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128));
  if ((tmp_u5 & 0x1800) == 0) {
    if ((tmp_u5 & 0x2000) != 0) {
      _DAT_00e9a2f8 = param_1;
      itemCapture = param_1;
      _DAT_00e9a2ec = param_2;
      _DAT_00e9a2f0 = (float)*(int *)(DC + 0x124);
      _DAT_00e9a2f4 = (float)*(int *)(DC + 0x128);
      captureData = &scrollInfo;
      captureFunc = Scroll_ListBox_ThumbFunc;
    }
  }
  else {
    _DAT_00e9a2fc = tmp_u5 >> 0xb & 1;
    captureData = &scrollInfo;
    _DAT_00e9a2ec = param_2;
    _DAT_00e9a2f8 = param_1;
    captureFunc = Scroll_ListBox_AutoFunc;
    scrollInfo = *(int *)(DC + 0x11c) + 500;
    g_unk_00e9a2e4 = *(int *)(DC + 0x11c) + 0x96;
    g_unk_00e9a2e8 = 500;
    itemCapture = param_1;
  }
  return;
}

void Item_StopCapture(void)
{
  return;
}

uint32_t Item_Slider_HandleKey(float *param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  void *tmp_pc4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  uint32_t tmp_u9;
  
  if (((uint)param_1[0x12] & 2) == 0) {
    return 0;
  }
  if (param_1[0x45] == 0.0) {
    return 0;
  }
  tmp_f8 = (float)*(int *)(DC + 0x124);
  tmp_f1 = *(float *)(DC + 0x2003c);
  if (tmp_f1 <= 1.3333334) {
    tmp_f2 = *param_1;
    if (tmp_f8 <= tmp_f2) {
      return 0;
    }
    tmp_f6 = param_1[2] + tmp_f2;
    tmp_f7 = tmp_f8;
  }
  else {
    tmp_f5 = tmp_f1 * 0.75;
    tmp_f7 = tmp_f8 * tmp_f5;
    tmp_f2 = *param_1;
    if (tmp_f7 <= tmp_f5 * tmp_f2) {
      return 0;
    }
    tmp_f6 = param_1[2] + tmp_f2;
    if (1.3333334 < tmp_f1) {
      if (tmp_f6 * tmp_f5 <= tmp_f7) {
        return 0;
      }
      goto LAB_000f78dd;
    }
  }
  if (tmp_f6 <= tmp_f7) {
    return 0;
  }
LAB_000f78dd:
  if ((((param_1[1] < (float)*(int *)(DC + 0x128)) &&
       ((float)*(int *)(DC + 0x128) < param_1[1] + param_1[3])) &&
      ((param_2 - 0xb2U < 3 || (param_2 == 0xd)))) &&
     (pfVar3 = (float *)param_1[0x94], pfVar3 != (float *)0x0)) {
    if (param_1[0x3a] != 0.0) {
      tmp_f2 = param_1[0x2e] + param_1[0x30] + 8.0;
    }
    tmp_f6 = tmp_f2 - 6.0;
    tmp_f7 = tmp_f6;
    tmp_f5 = tmp_f8;
    if (1.3333334 < tmp_f1) {
      tmp_f7 = tmp_f1 * 0.75 * tmp_f6;
      tmp_f5 = tmp_f8 * tmp_f1 * 0.75;
    }
    if (tmp_f7 < tmp_f5) {
      tmp_f6 = tmp_f6 + 102.0;
      if (1.3333334 < tmp_f1) {
        tmp_f6 = tmp_f1 * 0.75 * tmp_f6;
      }
      if (tmp_f5 < tmp_f6) {
        tmp_pc4 = *(void **)(DC + 0x78);
        tmp_u9 = va(&g_unk_0011e95f,
                   (double)(*pfVar3 + (pfVar3[1] - *pfVar3) * ((tmp_f8 - tmp_f2) / 96.0)));
        (*tmp_pc4)(param_1[0x45],tmp_u9);
        return 1;
      }
    }
  }
  return 0;
}

void Item_Action(int param_1)
{
  if (param_1 != 0) {
    Item_RunScript_constprop_37();
    return;
  }
  return;
}

void Menus_Activate(int param_1)
{
  char *tmp_pc1;
  uint *tmp_pu2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  int local_2a0;
  
  if (0 < menuCount) {
    tmp_pu2 = &g_unk_040f8f88;
    tmp_i4 = menuCount * 0x346;
    do {
      *tmp_pu2 = *tmp_pu2 & 0xfffffffc;
      tmp_pu2 = tmp_pu2 + 0x346;
    } while (tmp_pu2 != &g_unk_040f8f88 + tmp_i4);
  }
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 6;
  if (*(int *)(param_1 + 0xd8) != 0) {
    Item_RunScript_constprop_37();
  }
  tmp_i4 = DC;
  *(uint32_t *)(param_1 + 0xec) = *(uint32_t *)(DC + 0x11c);
  tmp_pc1 = *(char **)(param_1 + 0x4f0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    (**(void **)(tmp_i4 + 0xe0))(tmp_pc1,tmp_pc1,0);
  }
  if (0 < menuCount) {
    tmp_pu3 = &Menus;
    local_2a0 = 0;
    do {
      if ((tmp_pu3[0xd] == 5) && (-1 < (int)tmp_pu3[0xc])) {
        (**(void **)(DC + 0xec))(tmp_pu3[0xc]);
        tmp_pu3[0xc] = 0xffffffff;
      }
      if (0 < (int)tmp_pu3[0x30]) {
        tmp_i4 = 0;
        do {
          while( true ) {
            tmp_i5 = tmp_pu3[tmp_i4 + 0x145];
            if ((*(int *)(tmp_i5 + 0x34) == 5) && (-1 < *(int *)(tmp_i5 + 0x30))) break;
            if (*(int *)(tmp_i5 + 200) != 8) goto LAB_000f7c39;
LAB_000f7c90:
            tmp_i4 = tmp_i4 + 1;
            (**(void **)(DC + 0xec))(-*(int *)(tmp_i5 + 0x3c));
            if ((int)tmp_pu3[0x30] <= tmp_i4) goto LAB_000f7cb0;
          }
          (**(void **)(DC + 0xec))(*(int *)(tmp_i5 + 0x30));
          *(uint32_t *)(tmp_i5 + 0x30) = 0xffffffff;
          tmp_i5 = tmp_pu3[tmp_i4 + 0x145];
          if (*(int *)(tmp_i5 + 200) == 8) goto LAB_000f7c90;
LAB_000f7c39:
          tmp_i4 = tmp_i4 + 1;
        } while (tmp_i4 < (int)tmp_pu3[0x30]);
      }
LAB_000f7cb0:
      local_2a0 = local_2a0 + 1;
      tmp_pu3 = tmp_pu3 + 0x346;
    } while (local_2a0 < menuCount);
  }
  return;
}

void Menus_ShowByName(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  
  if (0 < menuCount) {
    tmp_pu3 = &g_unk_040f8f60;
    tmp_i2 = 0;
    do {
      tmp_i1 = Q_stricmp(*tmp_pu3,param_1);
      if (tmp_i1 == 0) {
        Menus_Activate();
        return;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pu3 = tmp_pu3 + 0x346;
    } while (tmp_i2 < menuCount);
  }
  return;
}

bool Menus_CaptureFuncActive(void)
{
  return captureFunc != 0;
}

int Display_VisibleMenuCount(void)
{
  int tmp_i1;
  uint *tmp_pu2;
  
  if (menuCount < 1) {
    tmp_i1 = 0;
  }
  else {
    tmp_pu2 = &g_unk_040f8f88;
    tmp_i1 = 0;
    do {
      if ((*tmp_pu2 & 0x100004) != 0) {
        tmp_i1 = tmp_i1 + 1;
      }
      tmp_pu2 = tmp_pu2 + 0x346;
    } while (tmp_pu2 != &g_unk_040f8f88 + menuCount * 0x346);
  }
  return tmp_i1;
}

void Rect_ToWindowCoords(float *param_1,float *param_2)
{
  *param_1 = *param_1 + *param_2;
  param_1[1] = param_1[1] + param_2[1];
  return;
}

void Item_SetTextExtents(float *param_1,int *param_2,int *param_3,float param_4)
{
  float tmp_f1;
  int tmp_i2;
  float tmp_f3;
  int local_12c;
  uint8_t local_11c [268];
  
  tmp_f3 = param_4;
  if ((param_4 == 0.0) && (tmp_f3 = param_1[0x3a], tmp_f3 == 0.0)) {
    return;
  }
  *param_2 = (int)ROUND(param_1[0x30]);
  *param_3 = (int)ROUND(param_1[0x31]);
  if (*param_2 != 0) {
    if ((((param_1[0x32] != 1.12104e-44) || (param_1[0x34] != 1.4013e-45)) &&
        (param_1[0x34] != 4.2039e-45)) && (param_1[0x32] != 2.10195e-44)) {
      return;
    }
  }
  local_12c = (**(void **)(DC + 0x18))(tmp_f3,param_1[0x37],0);
  if (param_1[0x32] == 1.12104e-44) {
    tmp_f1 = param_1[0x34];
    if ((int)tmp_f1 - 1U < 2) {
      tmp_i2 = (**(void **)(DC + 0xd8))(param_1[0xf],param_1[0x37]);
      local_12c = local_12c + tmp_i2;
      goto LAB_000f7f57;
    }
  }
  else {
    tmp_f1 = param_1[0x34];
    if ((param_1[0x32] == 5.60519e-45) && (tmp_f1 == 1.4013e-45)) {
      if (param_1[0x45] != 0.0) {
        (**(void **)(DC + 0x70))(param_1[0x45],local_11c,0x100);
        tmp_i2 = (**(void **)(DC + 0x18))(local_11c,param_1[0x37],0);
        local_12c = local_12c + tmp_i2;
      }
      goto LAB_000f7f57;
    }
  }
  if (tmp_f1 == 4.2039e-45) {
    tmp_i2 = (**(void **)(DC + 0x18))(param_4,param_1[0x37],0);
    local_12c = local_12c + tmp_i2;
  }
LAB_000f7f57:
  tmp_i2 = (**(void **)(DC + 0x18))(tmp_f3,param_1[0x37],0);
  *param_2 = tmp_i2;
  tmp_i2 = (**(void **)(DC + 0x24))(tmp_f3,param_1[0x37],0);
  *param_3 = tmp_i2;
  param_1[0x30] = (float)*param_2;
  param_1[0x31] = (float)*param_3;
  tmp_f3 = param_1[0x35];
  param_1[0x2e] = tmp_f3;
  param_1[0x2f] = param_1[0x36];
  if (param_1[0x34] == 2.8026e-45) {
    tmp_f3 = tmp_f3 - (float)local_12c;
  }
  else if (((uint)param_1[0x34] & 0xfffffffd) == 1) {
    tmp_f3 = tmp_f3 - (float)local_12c * 0.5;
  }
  param_1[0x2e] = tmp_f3 + *param_1;
  param_1[0x2f] = param_1[0x36] + param_1[1];
  return;
}

void Item_TextColor(int param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint tmp_u6;
  float tmp_f7;
  int tmp_i8;
  double tmp_d9;
  
  tmp_i5 = *(int *)(param_1 + 0xec);
  tmp_u6 = *(uint *)(param_1 + 0x48);
  tmp_f1 = *(float *)(tmp_i5 + 0xd4);
  tmp_f2 = *(float *)(tmp_i5 + 0xd0);
  if (((tmp_u6 & 0x60) == 0) || (*(int *)(DC + 0x11c) <= *(int *)(param_1 + 0x70))) {
LAB_000f81a4:
    if ((*(uint *)(param_1 + 0x48) & 0x8000002) != 0x8000002) goto LAB_000f81b7;
LAB_000f8390:
    tmp_f1 = *(float *)(tmp_i5 + 0x4f4);
    tmp_f2 = *(float *)(tmp_i5 + 0x4f8);
    tmp_f3 = *(float *)(tmp_i5 + 0x4fc);
    tmp_f4 = *(float *)(tmp_i5 + 0x500);
    tmp_d9 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_f7 = (float)tmp_d9 * 0.5 + 0.5;
    tmp_f1 = (tmp_f1 * 0.8 - *(float *)(tmp_i5 + 0x4f4)) * tmp_f7 + *(float *)(tmp_i5 + 0x4f4);
    if (tmp_f1 < 0.0) {
      *param_2 = 0.0;
    }
    else {
      if (1.0 < tmp_f1) {
        tmp_f1 = 1.0;
      }
      *param_2 = tmp_f1;
    }
    tmp_f1 = (tmp_f2 * 0.8 - *(float *)(tmp_i5 + 0x4f8)) * tmp_f7 + *(float *)(tmp_i5 + 0x4f8);
    if (tmp_f1 < 0.0) {
      param_2[1] = 0.0;
    }
    else {
      if (1.0 < tmp_f1) {
        tmp_f1 = 1.0;
      }
      param_2[1] = tmp_f1;
    }
    tmp_f1 = (tmp_f3 * 0.8 - *(float *)(tmp_i5 + 0x4fc)) * tmp_f7 + *(float *)(tmp_i5 + 0x4fc);
    if (tmp_f1 < 0.0) {
      param_2[2] = 0.0;
    }
    else {
      if (1.0 < tmp_f1) {
        tmp_f1 = 1.0;
      }
      param_2[2] = tmp_f1;
    }
    tmp_f1 = (tmp_f4 * 0.8 - *(float *)(tmp_i5 + 0x500)) * tmp_f7 + *(float *)(tmp_i5 + 0x500);
  }
  else {
    *(int *)(param_1 + 0x70) = *(int *)(DC + 0x11c) + *(int *)(tmp_i5 + 0xcc);
    if ((tmp_u6 & 0x20) != 0) {
      tmp_f1 = *(float *)(param_1 + 0x80) - tmp_f1;
      *(float *)(param_1 + 0x80) = tmp_f1;
      if (tmp_f1 <= 0.0) {
        *(uint *)(param_1 + 0x48) = tmp_u6 & 0xffffffdb;
      }
      goto LAB_000f81a4;
    }
    tmp_f1 = tmp_f1 + *(float *)(param_1 + 0x80);
    if (tmp_f1 < tmp_f2) {
      *(float *)(param_1 + 0x80) = tmp_f1;
      goto LAB_000f81a4;
    }
    *(uint *)(param_1 + 0x48) = tmp_u6 & 0xffffffbf;
    *(float *)(param_1 + 0x80) = tmp_f2;
    if ((*(uint *)(param_1 + 0x48) & 0x8000002) == 0x8000002) goto LAB_000f8390;
LAB_000f81b7:
    if ((*(int *)(param_1 + 0xe4) != 1) || ((*(int *)(DC + 0x11c) / 200 & 1U) != 0)) {
      *param_2 = *(float *)(param_1 + 0x74);
      param_2[1] = *(float *)(param_1 + 0x78);
      param_2[2] = *(float *)(param_1 + 0x7c);
      param_2[3] = *(float *)(param_1 + 0x80);
      goto LAB_000f81db;
    }
    tmp_f1 = *(float *)(param_1 + 0x74);
    tmp_f2 = *(float *)(param_1 + 0x78);
    tmp_f3 = *(float *)(param_1 + 0x7c);
    tmp_f4 = *(float *)(param_1 + 0x80);
    tmp_d9 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_f7 = (float)tmp_d9 * 0.5 + 0.5;
    tmp_f1 = (tmp_f1 * 0.8 - *(float *)(param_1 + 0x74)) * tmp_f7 + *(float *)(param_1 + 0x74);
    if (tmp_f1 < 0.0) {
      *param_2 = 0.0;
    }
    else {
      if (1.0 < tmp_f1) {
        tmp_f1 = 1.0;
      }
      *param_2 = tmp_f1;
    }
    tmp_f1 = (tmp_f2 * 0.8 - *(float *)(param_1 + 0x78)) * tmp_f7 + *(float *)(param_1 + 0x78);
    if (tmp_f1 < 0.0) {
      param_2[1] = 0.0;
    }
    else {
      if (1.0 < tmp_f1) {
        tmp_f1 = 1.0;
      }
      param_2[1] = tmp_f1;
    }
    tmp_f1 = (tmp_f3 * 0.8 - *(float *)(param_1 + 0x7c)) * tmp_f7 + *(float *)(param_1 + 0x7c);
    if (tmp_f1 < 0.0) {
      param_2[2] = 0.0;
    }
    else {
      if (1.0 < tmp_f1) {
        tmp_f1 = 1.0;
      }
      param_2[2] = tmp_f1;
    }
    tmp_f1 = (tmp_f4 * 0.8 - *(float *)(param_1 + 0x80)) * tmp_f7 + *(float *)(param_1 + 0x80);
  }
  if (tmp_f1 < 0.0) {
    param_2[3] = 0.0;
  }
  else {
    if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    param_2[3] = tmp_f1;
  }
LAB_000f81db:
  if ((((*(char **)(param_1 + 0x11c) != (char *)0x0) && (**(char **)(param_1 + 0x11c) != '\0')) &&
      (*(char **)(param_1 + 0x118) != (char *)0x0)) &&
     (((**(char **)(param_1 + 0x118) != '\0' && ((*(byte *)(param_1 + 0x120) & 3) != 0)) &&
      (tmp_i8 = Item_EnableShowViaCvar(param_1,1), tmp_i8 == 0)))) {
    *param_2 = *(float *)(tmp_i5 + 0x504);
    param_2[1] = *(float *)(tmp_i5 + 0x508);
    param_2[2] = *(float *)(tmp_i5 + 0x50c);
    param_2[3] = *(float *)(tmp_i5 + 0x510);
  }
  return;
}

void Item_Text_AutoWrapped_Paint(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  bool tmp_b3;
  int tmp_i4;
  byte tmp_b5;
  int tmp_i6;
  byte *tmp_pb7;
  int local_860;
  int local_858;
  byte *local_850;
  float local_84c;
  uint8_t local_834 [4];
  int local_830;
  uint8_t local_82c [16];
  byte local_81c [1024];
  byte local_41c [1036];
  
  tmp_pb7 = (byte *)param_1[0x3a];
  if (tmp_pb7 == (byte *)0x0) {
    if (param_1[0x45] == 0.0) {
      return;
    }
    tmp_pb7 = local_81c;
    (**(void **)(DC + 0x70))(param_1[0x45],tmp_pb7,0x400);
  }
  if (*tmp_pb7 != 0) {
    Item_TextColor(param_1,local_82c);
    Item_SetTextExtents(param_1,local_834,&local_830,tmp_pb7);
    local_41c[0] = 0;
    tmp_b3 = false;
    local_858 = 0;
    local_860 = 0;
    local_84c = param_1[0x36];
    local_850 = (byte *)0x0;
    tmp_i6 = 0;
    do {
      tmp_i4 = (**(void **)(DC + 0x18))(local_41c,param_1[0x37],0);
      tmp_b5 = *tmp_pb7;
      if (((byte)(tmp_b5 - 9) < 2) || ((tmp_b5 & 0xdf) == 0)) {
        local_850 = tmp_pb7 + 1;
        tmp_b3 = true;
        local_860 = tmp_i6;
        local_858 = tmp_i4;
LAB_000f86d0:
        if ((((local_860 == 0) || ((float)tmp_i4 <= param_1[2])) && (tmp_b5 != 10)) && (tmp_b5 != 0))
        goto LAB_000f86f4;
        if (tmp_i6 != 0) {
LAB_000f8728:
          tmp_f2 = param_1[0x34];
          if (tmp_f2 == 0.0) {
            tmp_f2 = param_1[0x35];
          }
          else if (tmp_f2 == 2.8026e-45) {
            tmp_f2 = param_1[0x35] - (float)local_858;
          }
          else if (tmp_f2 == 1.4013e-45) {
            tmp_f2 = param_1[0x35] - (float)local_858 * 0.5;
          }
          else {
            tmp_f2 = param_1[0x2e];
          }
          tmp_f1 = *param_1;
          local_41c[local_860] = 0;
          param_1[0x2e] = tmp_f2 + tmp_f1;
          param_1[0x2f] = local_84c + param_1[1];
          (**(void **)(DC + 0x10))
                    (tmp_f2 + tmp_f1,local_84c + param_1[1],param_1[0x37],local_82c,local_41c,0,0,
                     param_1[0x39]);
          tmp_b5 = *tmp_pb7;
        }
        if (tmp_b5 == 0) {
          return;
        }
        tmp_b3 = false;
        tmp_i4 = 0;
        local_84c = (float)(local_830 + 5) + local_84c;
        local_858 = 0;
        local_860 = 0;
        tmp_pb7 = local_850;
      }
      else {
        if (tmp_b3) {
          tmp_b3 = true;
          goto LAB_000f86d0;
        }
        if ((float)tmp_i4 <= param_1[2]) goto LAB_000f86d0;
        local_860 = tmp_i6;
        local_858 = tmp_i4;
        local_850 = tmp_pb7;
        if (tmp_i6 != 0) goto LAB_000f8728;
        local_860 = 0;
LAB_000f86f4:
        tmp_i4 = tmp_i6 + 1;
        if (tmp_b5 == 0xd) {
          local_41c[tmp_i6] = 0x20;
        }
        else {
          local_41c[tmp_i6] = tmp_b5;
        }
        local_41c[tmp_i6 + 1] = 0;
        tmp_pb7 = tmp_pb7 + 1;
      }
      tmp_i6 = tmp_i4;
    } while (tmp_pb7 != (byte *)0x0);
  }
  return;
}

void Item_Text_Wrapped_Paint(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  char *__s;
  float local_854;
  uint8_t local_834 [4];
  int local_830;
  uint8_t local_82c [16];
  char local_81c [1024];
  char local_41c [1036];
  
  __s = *(char **)(param_1 + 0xe8);
  if (__s == (char *)0x0) {
    if (*(int *)(param_1 + 0x114) == 0) {
      return;
    }
    __s = local_81c;
    (**(void **)(DC + 0x70))(*(int *)(param_1 + 0x114),__s,0x400);
  }
  if (*__s == '\0') {
    return;
  }
  Item_TextColor(param_1,local_82c);
  Item_SetTextExtents(param_1,local_834,&local_830,__s);
  tmp_u1 = *(uint32_t *)(param_1 + 0xb8);
  local_854 = *(float *)(param_1 + 0xbc);
  tmp_pc3 = strchr(__s,0xd);
  if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
    do {
      strncpy(local_41c,__s,(size_t)(tmp_pc3 + (1 - (int)__s)));
      tmp_u2 = *(uint32_t *)(param_1 + 0xe4);
      tmp_pc3[(int)(local_41c + -(int)__s)] = '\0';
      (**(void **)(DC + 0x10))
                (tmp_u1,local_854,*(uint32_t *)(param_1 + 0xdc),local_82c,local_41c,0,0,tmp_u2);
      __s = __s + (int)(tmp_pc3 + (1 - (int)__s));
      local_854 = (float)(local_830 + 5) + local_854;
      tmp_pc3 = strchr(tmp_pc3 + 1,0xd);
      if (tmp_pc3 == (char *)0x0) break;
    } while (*tmp_pc3 != '\0');
  }
  (**(void **)(DC + 0x10))
            (tmp_u1,local_854,*(uint32_t *)(param_1 + 0xdc),local_82c,__s,0,0,
             *(uint32_t *)(param_1 + 0xe4));
  return;
}

void Item_Text_Paint(float *param_1)
{
  int tmp_i1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  char *tmp_pc5;
  uint32_t tmp_u6;
  char *__nptr;
  double tmp_d7;
  uint8_t local_51c [256];
  char local_41c [1036];
  
  tmp_f2 = param_1[0x3b];
  if (((uint)param_1[0x12] & 0x40000) != 0) {
    Item_Text_Wrapped_Paint(param_1);
    return;
  }
  if (((uint)param_1[0x12] & 0x80000) != 0) {
    Item_Text_AutoWrapped_Paint(param_1);
    return;
  }
  __nptr = (char *)param_1[0x3a];
  if (__nptr == (char *)0x0) {
    if (param_1[0x45] == 0.0) {
      return;
    }
    __nptr = local_41c;
    (**(void **)(DC + 0x70))(param_1[0x45],__nptr);
    if (((uint)param_1[0x12] & 0x10000000) == 0) {
      if (((uint)param_1[0x12] & 0x20000000) == 0) goto LAB_000f8b11;
      tmp_d7 = strtod(__nptr,(char **)0x0);
      tmp_u6 = va("%.2f",tmp_d7);
      Q_strncpyz(__nptr,tmp_u6,0x400);
      param_1[0x30] = 0.0;
    }
    else {
      COM_StripExtension(__nptr,__nptr);
      param_1[0x30] = 0.0;
    }
    if (param_1[0x32] == 2.10195e-44) goto LAB_000f8dd0;
  }
  else {
LAB_000f8b11:
    if (param_1[0x32] == 2.10195e-44) {
LAB_000f8dd0:
      if ((tmp_f2 != 0.0) && (0 < *(int *)((int)tmp_f2 + 0xec))) {
        tmp_i1 = (((*(int *)((int)tmp_f2 + 0xec) + *(int *)((int)tmp_f2 + 0xe8)) - *(int *)(DC + 0x11c)
                 ) + 999) / 1000;
        if (tmp_i1 < 3) {
          tmp_pc5 = "^1%d^*";
        }
        else {
          tmp_pc5 = "%d";
        }
        __nptr = local_41c;
        tmp_u6 = va(tmp_pc5,tmp_i1);
        Com_sprintf(__nptr,0xff,param_1[0x3a],tmp_u6);
      }
    }
    if ((int)ROUND(param_1[0x30]) != 0) {
      if ((((param_1[0x32] != 1.12104e-44) || (param_1[0x34] != 1.4013e-45)) &&
          (param_1[0x34] != 4.2039e-45)) && (param_1[0x32] != 2.10195e-44)) goto LAB_000f8b75;
    }
  }
  tmp_i1 = (**(void **)(DC + 0x18))(__nptr,param_1[0x37],0);
  if (param_1[0x32] == 1.12104e-44) {
    tmp_f2 = param_1[0x34];
    if (1 < (int)tmp_f2 - 1U) goto LAB_000f8c8c;
    tmp_i3 = (**(void **)(DC + 0xd8))(param_1[0xf],param_1[0x37]);
    tmp_i1 = tmp_i1 + tmp_i3;
  }
  else {
    tmp_f2 = param_1[0x34];
    if ((param_1[0x32] == 5.60519e-45) && (tmp_f2 == 1.4013e-45)) {
      if (param_1[0x45] != 0.0) {
        (**(void **)(DC + 0x70))(param_1[0x45],local_51c,0x100);
        tmp_i3 = (**(void **)(DC + 0x18))(local_51c,param_1[0x37],0);
        tmp_i1 = tmp_i1 + tmp_i3;
      }
    }
    else {
LAB_000f8c8c:
      if (tmp_f2 == 4.2039e-45) {
        tmp_i3 = (**(void **)(DC + 0x18))(__nptr,param_1[0x37],0);
        tmp_i1 = tmp_i1 + tmp_i3;
      }
    }
  }
  tmp_i3 = (**(void **)(DC + 0x18))(__nptr,param_1[0x37],0);
  tmp_i4 = (**(void **)(DC + 0x24))(__nptr,param_1[0x37],0);
  param_1[0x30] = (float)tmp_i3;
  param_1[0x31] = (float)tmp_i4;
  tmp_f2 = param_1[0x35];
  param_1[0x2e] = tmp_f2;
  param_1[0x2f] = param_1[0x36];
  if (param_1[0x34] == 2.8026e-45) {
    tmp_f2 = tmp_f2 - (float)tmp_i1;
  }
  else if (((uint)param_1[0x34] & 0xfffffffd) == 1) {
    tmp_f2 = tmp_f2 - (float)tmp_i1 * 0.5;
  }
  param_1[0x2e] = tmp_f2 + *param_1;
  param_1[0x2f] = param_1[0x36] + param_1[1];
LAB_000f8b75:
  if (*__nptr != '\0') {
    Item_TextColor(param_1,local_51c);
    (**(void **)(DC + 0x10))
              (param_1[0x2e],param_1[0x2f],param_1[0x37],local_51c,__nptr,0,0,param_1[0x39]);
  }
  return;
}

void Item_TextField_Paint(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  char *tmp_pc3;
  float tmp_f4;
  byte tmp_b5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  double tmp_d9;
  int local_45c;
  int local_44c;
  float local_43c;
  float local_438;
  float local_434;
  float local_430;
  float local_42c;
  float local_428;
  float local_424;
  float local_420;
  uint8_t local_41c;
  char acStack_41b [1035];
  
  tmp_f1 = param_1[0x94];
  Item_Text_Paint(param_1);
  local_41c = 0;
  if (param_1[0x45] != 0.0) {
    (**(void **)(DC + 0x70))(param_1[0x45],&local_41c,0x400);
  }
  tmp_i6 = DC;
  tmp_f2 = param_1[0x3b];
  if (((uint)param_1[0x12] & 0x8000002) == 0x8000002) {
    local_42c = *(float *)((int)tmp_f2 + 0x4f4) * 0.8;
    local_428 = *(float *)((int)tmp_f2 + 0x4f8) * 0.8;
    local_424 = *(float *)((int)tmp_f2 + 0x4fc) * 0.8;
    local_420 = *(float *)((int)tmp_f2 + 0x500) * 0.8;
    tmp_d9 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_f4 = (float)tmp_d9 * 0.5 + 0.5;
    local_43c = (local_42c - *(float *)((int)tmp_f2 + 0x4f4)) * tmp_f4 +
                *(float *)((int)tmp_f2 + 0x4f4);
    if (local_43c < 0.0) {
      local_43c = 0.0;
    }
    else if (1.0 < local_43c) {
      local_43c = 1.0;
    }
    local_438 = (local_428 - *(float *)((int)tmp_f2 + 0x4f8)) * tmp_f4 +
                *(float *)((int)tmp_f2 + 0x4f8);
    if (local_438 < 0.0) {
      local_438 = 0.0;
    }
    else if (1.0 < local_438) {
      local_438 = 1.0;
    }
    local_434 = (local_424 - *(float *)((int)tmp_f2 + 0x4fc)) * tmp_f4 +
                *(float *)((int)tmp_f2 + 0x4fc);
    if (local_434 < 0.0) {
      local_434 = 0.0;
    }
    else if (1.0 < local_434) {
      local_434 = 1.0;
    }
    local_430 = *(float *)((int)tmp_f2 + 0x500) +
                (local_420 - *(float *)((int)tmp_f2 + 0x500)) * tmp_f4;
    if (0.0 <= local_430) {
      tmp_pc3 = (char *)param_1[0x3a];
      if (1.0 < local_430) {
        local_430 = 1.0;
      }
      goto joined_r0x000f92e3;
    }
    local_430 = 0.0;
  }
  else {
    local_43c = param_1[0x1d];
    local_430 = param_1[0x20];
    local_438 = param_1[0x1e];
    local_434 = param_1[0x1f];
  }
  tmp_pc3 = (char *)param_1[0x3a];
joined_r0x000f92e3:
  if (tmp_pc3 == (char *)0x0) {
    tmp_b5 = 0;
  }
  else {
    tmp_b5 = ~-(*tmp_pc3 == '\0') & 8;
  }
  tmp_f2 = (float)tmp_b5;
  local_45c = 0;
  tmp_i7 = -1;
  do {
    tmp_i8 = tmp_i7 + 1;
    if (acStack_41b[*(int *)((int)tmp_f1 + 0x18) + tmp_i7] == '\0') break;
    local_45c = (**(void **)(tmp_i6 + 0x18))
                          (acStack_41b + *(int *)((int)tmp_f1 + 0x18) + tmp_i8 + -1,param_1[0x37],0);
    tmp_i6 = DC;
    tmp_i7 = tmp_i8;
  } while (*param_1 + param_1[2] < (float)local_45c + param_1[0x2e] + param_1[0x30] + tmp_f2);
  local_44c = 0;
  if (tmp_i8 != 0) {
    local_44c = (int)ROUND((*param_1 + param_1[2]) -
                           ((float)local_45c + param_1[0x2e] + param_1[0x30] + tmp_f2));
  }
  if ((((uint)param_1[0x12] & 2) != 0) && (g_editingField != 0)) {
    tmp_i6 = (**(void **)(tmp_i6 + 0x84))();
    (**(void **)(DC + 0x7c))
              ((float)local_44c + param_1[0x2e] + param_1[0x30] + tmp_f2,param_1[0x2f],param_1[0x37],
               &local_43c,acStack_41b + *(int *)((int)tmp_f1 + 0x18) + tmp_i8 + -1,
               ((int)param_1[0x93] - *(int *)((int)tmp_f1 + 0x18)) - tmp_i8,
               (-(tmp_i6 == 0) & 0x1dU) + 0x5f,*(uint32_t *)((int)tmp_f1 + 0x14),param_1[0x39]);
    return;
  }
  (**(void **)(tmp_i6 + 0x10))
            ((float)local_44c + param_1[0x2e] + param_1[0x30] + tmp_f2,param_1[0x2f],param_1[0x37],
             &local_43c,acStack_41b + tmp_i8 + *(int *)((int)tmp_f1 + 0x18) + -1,0,
             *(uint32_t *)((int)tmp_f1 + 0x14),param_1[0x39]);
  return;
}

void Item_CheckBox_Paint(float *param_1)
{
  float tmp_f1;
  void *tmp_pc2;
  bool tmp_b3;
  uint32_t tmp_u4;
  bool tmp_b5;
  long double tmp_l6;
  double tmp_d7;
  float tmp_f8;
  float tmp_f9;
  uint8_t local_2c [28];
  
  tmp_f9 = param_1[0x3b];
  tmp_f8 = param_1[0x94];
  tmp_f1 = param_1[0x45];
  if (param_1[0x9d] == 0.0) {
    if (tmp_f1 != 0.0) {
      tmp_l6 = (long double)(**(void **)(DC + 0x74))(tmp_f1);
      tmp_b5 = tmp_l6 == (long double)2.0;
      if (!NAN(tmp_l6) && !NAN((long double)2.0)) goto LAB_000f9422;
      goto LAB_000f9424;
    }
    tmp_l6 = (long double)0;
    tmp_b3 = false;
    tmp_b5 = false;
    if (((uint)param_1[0x12] & 0x8000002) == 0x8000002) goto LAB_000f951a;
LAB_000f945b:
    tmp_b3 = tmp_b5;
    if (tmp_f8 != 0.0) goto LAB_000f9463;
LAB_000f9647:
    tmp_b5 = false;
    if (param_1[0x3a] == 0.0) {
      tmp_b5 = false;
      goto LAB_000f9660;
    }
  }
  else {
    tmp_l6 = (long double)(**(void **)(DC + 0x74))(tmp_f1);
    tmp_l6 = (long double)(int)((int)ROUND(tmp_l6) & (uint)param_1[0x9d]);
    tmp_b5 = tmp_l6 == (long double)2.0;
    if (NAN(tmp_l6) || NAN((long double)2.0)) {
LAB_000f9424:
      tmp_b3 = false;
    }
    else {
LAB_000f9422:
      tmp_b3 = true;
      if (!tmp_b5) goto LAB_000f9424;
    }
    tmp_b5 = tmp_b3;
    if (((uint)param_1[0x12] & 0x8000002) != 0x8000002) goto LAB_000f945b;
LAB_000f951a:
    tmp_f1 = *(float *)((int)tmp_f9 + 0x500);
    tmp_d7 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_l6 = (long double)(float)tmp_l6;
    tmp_f9 = *(float *)((int)tmp_f9 + 0x500);
    tmp_b5 = tmp_b3;
    if (tmp_f9 + (tmp_f1 * 0.8 - tmp_f9) * ((float)tmp_d7 * 0.5 + 0.5) < 0.0) goto LAB_000f945b;
    if (tmp_f8 == 0.0) goto LAB_000f9647;
LAB_000f9463:
    tmp_b5 = *(int *)((int)tmp_f8 + 0x180) != 0;
    if (param_1[0x3a] == 0.0) {
LAB_000f9660:
      if ((tmp_b3) && (param_1[0x32] == 2.24208e-44)) {
        (**(void **)(DC + 8))
                  (*param_1,param_1[1],param_1[3],param_1[3],*(uint32_t *)(DC + 0x1e310));
      }
      else if (tmp_l6 == (long double)0) {
        (**(void **)(DC + 8))
                  (*param_1,param_1[1],param_1[3],param_1[3],*(uint32_t *)(DC + 0x1e30c));
      }
      else {
        (**(void **)(DC + 8))
                  (*param_1,param_1[1],param_1[3],param_1[3],*(uint32_t *)(DC + 0x1e308));
      }
      if (!tmp_b5) {
        return;
      }
      Item_TextColor(param_1,local_2c);
      tmp_f9 = param_1[0x39];
      tmp_pc2 = *(void **)(DC + 0x10);
      tmp_u4 = Item_Multi_Setting(param_1);
      (*tmp_pc2)(*param_1 + param_1[3] + 4.0,param_1[1] + param_1[0x36],param_1[0x37],local_2c,tmp_u4,
                0,0,tmp_f9);
      return;
    }
  }
  Item_Text_Paint(param_1);
  if ((tmp_b3) && (param_1[0x32] == 2.24208e-44)) {
    tmp_f9 = param_1[3];
    tmp_u4 = *(uint32_t *)(DC + 0x1e310);
  }
  else {
    if ((float)tmp_l6 != 0.0) {
      tmp_f9 = param_1[3];
      tmp_u4 = *(uint32_t *)(DC + 0x1e308);
      tmp_f8 = param_1[1];
      goto LAB_000f94d5;
    }
    tmp_f9 = param_1[3];
    tmp_u4 = *(uint32_t *)(DC + 0x1e30c);
  }
  tmp_f8 = param_1[1];
LAB_000f94d5:
  (**(void **)(DC + 8))(param_1[0x2e] + param_1[0x30] + 8.0,tmp_f8,tmp_f9,tmp_f9,tmp_u4);
  if (!tmp_b5) {
    return;
  }
  Item_TextColor(param_1,local_2c);
  tmp_f9 = param_1[0x39];
  tmp_pc2 = *(void **)(DC + 0x10);
  tmp_u4 = Item_Multi_Setting(param_1);
  (*tmp_pc2)(param_1[0x2e] + param_1[0x30] + 8.0 + param_1[3] + 4.0,param_1[0x2f],param_1[0x37],
            local_2c,tmp_u4,0,0,tmp_f9);
  return;
}

void Item_YesNo_Paint(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  float tmp_f3;
  uint8_t *tmp_pu4;
  long double tmp_l5;
  double tmp_d6;
  float local_38;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_i1 = *(int *)(param_1 + 0xec);
  if (*(int *)(param_1 + 0x114) == 0) {
    tmp_u2 = *(uint *)(param_1 + 0x48);
    local_38 = 0.0;
  }
  else {
    tmp_l5 = (long double)(**(void **)(DC + 0x74))(*(int *)(param_1 + 0x114));
    tmp_u2 = *(uint *)(param_1 + 0x48);
    local_38 = (float)tmp_l5;
  }
  if ((tmp_u2 & 0x8000002) == 0x8000002) {
    local_1c = *(float *)(tmp_i1 + 0x4f4) * 0.8;
    local_18 = *(float *)(tmp_i1 + 0x4f8) * 0.8;
    local_14 = *(float *)(tmp_i1 + 0x4fc) * 0.8;
    local_10 = *(float *)(tmp_i1 + 0x500) * 0.8;
    tmp_d6 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_f3 = (float)tmp_d6 * 0.5 + 0.5;
    local_2c = (local_1c - *(float *)(tmp_i1 + 0x4f4)) * tmp_f3 + *(float *)(tmp_i1 + 0x4f4);
    if (local_2c < 0.0) {
      local_2c = 0.0;
    }
    else if (1.0 < local_2c) {
      local_2c = 1.0;
    }
    local_28 = (local_18 - *(float *)(tmp_i1 + 0x4f8)) * tmp_f3 + *(float *)(tmp_i1 + 0x4f8);
    if (local_28 < 0.0) {
      local_28 = 0.0;
    }
    else if (1.0 < local_28) {
      local_28 = 1.0;
    }
    local_24 = (local_14 - *(float *)(tmp_i1 + 0x4fc)) * tmp_f3 + *(float *)(tmp_i1 + 0x4fc);
    if (local_24 < 0.0) {
      local_24 = 0.0;
    }
    else if (1.0 < local_24) {
      local_24 = 1.0;
    }
    local_20 = *(float *)(tmp_i1 + 0x500) + (local_10 - *(float *)(tmp_i1 + 0x500)) * tmp_f3;
    if (local_20 < 0.0) {
      local_20 = 0.0;
    }
    else if (1.0 < local_20) {
      local_20 = 1.0;
    }
  }
  else {
    local_2c = *(float *)(param_1 + 0x74);
    local_20 = *(float *)(param_1 + 0x80);
    local_28 = *(float *)(param_1 + 0x78);
    local_24 = *(float *)(param_1 + 0x7c);
  }
  if (*(int *)(param_1 + 0xe8) == 0) {
    if (local_38 == 0.0) {
      tmp_pu4 = &g_unk_00120a1f;
    }
    else {
      tmp_pu4 = &g_unk_00120a1b;
    }
    (**(void **)(DC + 0x10))
              (*(uint32_t *)(param_1 + 0xb8),*(uint32_t *)(param_1 + 0xbc),
               *(uint32_t *)(param_1 + 0xdc),&local_2c,tmp_pu4,0,0,*(uint32_t *)(param_1 + 0xe4))
    ;
    return;
  }
  Item_Text_Paint(param_1);
  if (local_38 == 0.0) {
    tmp_pu4 = &g_unk_00120a1f;
  }
  else {
    tmp_pu4 = &g_unk_00120a1b;
  }
  (**(void **)(DC + 0x10))
            (*(float *)(param_1 + 0xb8) + *(float *)(param_1 + 0xc0) + 8.0,
             *(uint32_t *)(param_1 + 0xbc),*(uint32_t *)(param_1 + 0xdc),&local_2c,tmp_pu4,0,0,
             *(uint32_t *)(param_1 + 0xe4));
  return;
}

void Item_Multi_Paint(int param_1)
{
  int tmp_i1;
  float tmp_f2;
  uint32_t tmp_u3;
  double tmp_d4;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_i1 = *(int *)(param_1 + 0xec);
  if ((*(uint *)(param_1 + 0x48) & 0x8000002) == 0x8000002) {
    local_1c = *(float *)(tmp_i1 + 0x4f4) * 0.8;
    local_18 = *(float *)(tmp_i1 + 0x4f8) * 0.8;
    local_14 = *(float *)(tmp_i1 + 0x4fc) * 0.8;
    local_10 = *(float *)(tmp_i1 + 0x500) * 0.8;
    tmp_d4 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_f2 = (float)tmp_d4 * 0.5 + 0.5;
    local_2c = (local_1c - *(float *)(tmp_i1 + 0x4f4)) * tmp_f2 + *(float *)(tmp_i1 + 0x4f4);
    if (local_2c < 0.0) {
      local_2c = 0.0;
    }
    else if (1.0 < local_2c) {
      local_2c = 1.0;
    }
    local_28 = (local_18 - *(float *)(tmp_i1 + 0x4f8)) * tmp_f2 + *(float *)(tmp_i1 + 0x4f8);
    if (local_28 < 0.0) {
      local_28 = 0.0;
    }
    else if (1.0 < local_28) {
      local_28 = 1.0;
    }
    local_24 = (local_14 - *(float *)(tmp_i1 + 0x4fc)) * tmp_f2 + *(float *)(tmp_i1 + 0x4fc);
    if (local_24 < 0.0) {
      local_24 = 0.0;
    }
    else if (1.0 < local_24) {
      local_24 = 1.0;
    }
    local_20 = *(float *)(tmp_i1 + 0x500) + (local_10 - *(float *)(tmp_i1 + 0x500)) * tmp_f2;
    if (local_20 < 0.0) {
      local_20 = 0.0;
    }
    else if (1.0 < local_20) {
      local_20 = 1.0;
    }
  }
  else {
    local_2c = *(float *)(param_1 + 0x74);
    local_20 = *(float *)(param_1 + 0x80);
    local_28 = *(float *)(param_1 + 0x78);
    local_24 = *(float *)(param_1 + 0x7c);
  }
  tmp_u3 = Item_Multi_Setting(param_1);
  if (*(int *)(param_1 + 0xe8) == 0) {
    (**(void **)(DC + 0x10))
              (*(uint32_t *)(param_1 + 0xb8),*(uint32_t *)(param_1 + 0xbc),
               *(uint32_t *)(param_1 + 0xdc),&local_2c,tmp_u3,0,0,*(uint32_t *)(param_1 + 0xe4));
    return;
  }
  Item_Text_Paint(param_1);
  (**(void **)(DC + 0x10))
            (*(float *)(param_1 + 0xb8) + *(float *)(param_1 + 0xc0) + 8.0,
             *(uint32_t *)(param_1 + 0xbc),*(uint32_t *)(param_1 + 0xdc),&local_2c,tmp_u3,0,0,
             *(uint32_t *)(param_1 + 0xe4));
  return;
}

void Controls_GetConfig(void)
{
  uint8_t **tmp_ppu1;
  uint8_t **tmp_ppu2;
  
  tmp_ppu1 = (uint8_t **)&g_unk_0014a9d8;
  do {
    tmp_ppu2 = tmp_ppu1 + 8;
    (**(void **)(DC + 0xbc))(tmp_ppu1[-6],tmp_ppu1,tmp_ppu1 + 1);
    tmp_ppu1 = tmp_ppu2;
  } while (tmp_ppu2 != &g_ptr_DAT_0014b178);
  return;
}

void Controls_SetConfig(int param_1)
{
  uint8_t **tmp_ppu1;
  
  tmp_ppu1 = &g_bindings;
  do {
    if (tmp_ppu1[6] != (uint8_t *)0xffffffff) {
      (**(void **)(DC + 0xc4))(tmp_ppu1[6],*tmp_ppu1);
      if (tmp_ppu1[7] != (uint8_t *)0xffffffff) {
        (**(void **)(DC + 0xc4))(tmp_ppu1[7],*tmp_ppu1);
      }
    }
    tmp_ppu1 = tmp_ppu1 + 8;
  } while (tmp_ppu1 != &commandList);
  if (param_1 != 0) {
    (**(void **)(DC + 200))(2,"in_restart\n");
  }
  return;
}

void Controls_SetDefaults(int param_1)
{
  uint8_t **tmp_ppu1;
  uint8_t **tmp_ppu2;
  
  if (param_1 == 0) {
    tmp_ppu2 = (uint8_t **)&g_unk_0014a9c8;
    do {
      tmp_ppu1 = tmp_ppu2 + 8;
      tmp_ppu2[5] = tmp_ppu2[1];
      tmp_ppu2[4] = *tmp_ppu2;
      tmp_ppu2 = tmp_ppu1;
    } while (tmp_ppu1 != &g_ptr_s_fadeout_0014b168);
    return;
  }
  tmp_ppu2 = (uint8_t **)&g_unk_0014a9d0;
  do {
    tmp_ppu1 = tmp_ppu2 + 8;
    tmp_ppu2[3] = tmp_ppu2[1];
    tmp_ppu2[2] = *tmp_ppu2;
    tmp_ppu2 = tmp_ppu1;
  } while (tmp_ppu1 != &g_ptr_s_show_0012109e_8_0014b170);
  return;
}

int BindingIDFromName(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = 0;
  do {
    tmp_i1 = Q_stricmp(param_1,(&g_bindings)[tmp_i2 * 8]);
    if (tmp_i1 == 0) {
      return tmp_i2;
    }
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 0x3d);
  return -1;
}

uint8_t * BindingFromName(uint32_t param_1)
{
  uint32_t tmp_u1;
  int local_14;
  int local_10;
  
  (**(void **)(DC + 0xbc))(param_1,&local_14,&local_10);
  if (local_14 == -1) {
    tmp_u1 = va(&g_unk_00120a33,param_1);
    Q_strncpyz(g_nameBind1,tmp_u1,0x20);
  }
  else {
    (**(void **)(DC + 0xb4))(local_14,g_nameBind1,0x20);
    Q_strupr(g_nameBind1);
    if (local_10 != -1) {
      (**(void **)(DC + 0xb4))(local_10,g_nameBind2,0x20);
      Q_strupr(g_nameBind2);
      Q_strcat(g_nameBind1,0x20,&g_unk_00120a2e);
      Q_strcat(g_nameBind1,0x20,g_nameBind2);
    }
  }
  return g_nameBind1;
}

void Item_Slider_Paint(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  long double tmp_l4;
  long double tmp_l5;
  long double tmp_l6;
  long double tmp_l7;
  long double tmp_l8;
  double tmp_d9;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_f2 = param_1[0x3b];
  if (((uint)param_1[0x12] & 0x8000002) == 0x8000002) {
    local_1c = *(float *)((int)tmp_f2 + 0x4f4) * 0.8;
    local_18 = *(float *)((int)tmp_f2 + 0x4f8) * 0.8;
    local_14 = *(float *)((int)tmp_f2 + 0x4fc) * 0.8;
    local_10 = *(float *)((int)tmp_f2 + 0x500) * 0.8;
    tmp_d9 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_f1 = (float)tmp_d9 * 0.5 + 0.5;
    local_2c = (local_1c - *(float *)((int)tmp_f2 + 0x4f4)) * tmp_f1 + *(float *)((int)tmp_f2 + 0x4f4);
    if (local_2c < 0.0) {
      local_2c = 0.0;
    }
    else if (1.0 < local_2c) {
      local_2c = 1.0;
    }
    local_28 = (local_18 - *(float *)((int)tmp_f2 + 0x4f8)) * tmp_f1 + *(float *)((int)tmp_f2 + 0x4f8);
    if (local_28 < 0.0) {
      local_28 = 0.0;
    }
    else if (1.0 < local_28) {
      local_28 = 1.0;
    }
    local_24 = (local_14 - *(float *)((int)tmp_f2 + 0x4fc)) * tmp_f1 + *(float *)((int)tmp_f2 + 0x4fc);
    if (local_24 < 0.0) {
      local_24 = 0.0;
    }
    else if (1.0 < local_24) {
      local_24 = 1.0;
    }
    local_20 = *(float *)((int)tmp_f2 + 0x500) + (local_10 - *(float *)((int)tmp_f2 + 0x500)) * tmp_f1;
    if (local_20 < 0.0) {
      local_20 = 0.0;
    }
    else if (1.0 < local_20) {
      local_20 = 1.0;
    }
  }
  else {
    local_2c = param_1[0x1d];
    local_20 = param_1[0x20];
    local_28 = param_1[0x1e];
    local_24 = param_1[0x1f];
  }
  tmp_f2 = param_1[1];
  if (param_1[0x3a] == 0.0) {
    tmp_f1 = *param_1;
  }
  else {
    Item_Text_Paint(param_1);
    tmp_f1 = param_1[0x2e] + param_1[0x30] + 8.0;
  }
  (**(void **)(DC + 4))(&local_2c);
  (**(void **)(DC + 8))
            (tmp_f1,tmp_f2 + 1.0,0x42c00000,0x41200000,*(uint32_t *)(BG_GetAnimString + DC));
  pfVar3 = (float *)param_1[0x94];
  if (param_1[0x3a] == 0.0) {
    tmp_l4 = (long double)*param_1;
  }
  else {
    tmp_l4 = (long double)param_1[0x2e] + (long double)param_1[0x30] + (long double)8.0;
  }
  if ((pfVar3 != (float *)0x0) || (param_1[0x45] == 0.0)) {
    tmp_l5 = (long double)(**(void **)(DC + 0x74))(param_1[0x45]);
    tmp_l6 = (long double)*pfVar3;
    tmp_l7 = (long double)pfVar3[1];
    tmp_l8 = tmp_l6;
    if ((tmp_l6 <= tmp_l5) && (tmp_l8 = tmp_l5, tmp_l7 < tmp_l5)) {
      tmp_l8 = tmp_l7;
    }
    tmp_l4 = ((tmp_l8 - tmp_l6) / (tmp_l7 - tmp_l6)) * (long double)96.0 + (long double)(float)tmp_l4;
  }
  (**(void **)(DC + 8))
            ((float)(tmp_l4 - (long double)6.0),tmp_f2,0x41400000,0x41400000,
             *(uint32_t *)(DC + 0x1e304));
  return;
}

void Item_Bind_Paint(int param_1)
{
  int tmp_i1;
  float tmp_f2;
  int tmp_i3;
  uint32_t tmp_u4;
  double tmp_d5;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i1 = *(int *)(param_1 + 0xec);
  if (*(int *)(param_1 + 0x250) == 0) {
    tmp_u4 = 0;
  }
  else {
    tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x250) + 0x14);
  }
  if (*(int *)(param_1 + 0x114) != 0) {
    (**(void **)(DC + 0x74))(*(int *)(param_1 + 0x114));
  }
  tmp_i3 = g_bindItem;
  if ((*(uint *)(param_1 + 0x48) & 0x8000002) == 0x8000002) {
    if (g_bindItem == param_1) {
      local_2c = 0.8;
      local_28 = 0.0;
      local_24 = 0.0;
      local_20 = 0.8;
    }
    else {
      local_2c = *(float *)(tmp_i1 + 0x4f4) * 0.8;
      local_28 = *(float *)(tmp_i1 + 0x4f8) * 0.8;
      local_24 = *(float *)(tmp_i1 + 0x4fc) * 0.8;
      local_20 = *(float *)(tmp_i1 + 0x500) * 0.8;
    }
    tmp_d5 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_f2 = (float)tmp_d5 * 0.5 + 0.5;
    local_3c = (local_2c - *(float *)(tmp_i1 + 0x4f4)) * tmp_f2 + *(float *)(tmp_i1 + 0x4f4);
    if (local_3c < 0.0) {
      local_3c = 0.0;
    }
    else if (1.0 < local_3c) {
      local_3c = 1.0;
    }
    local_38 = (local_28 - *(float *)(tmp_i1 + 0x4f8)) * tmp_f2 + *(float *)(tmp_i1 + 0x4f8);
    if (local_38 < 0.0) {
      local_38 = 0.0;
    }
    else if (1.0 < local_38) {
      local_38 = 1.0;
    }
    local_34 = (local_24 - *(float *)(tmp_i1 + 0x4fc)) * tmp_f2 + *(float *)(tmp_i1 + 0x4fc);
    if (local_34 < 0.0) {
      local_34 = 0.0;
    }
    else if (1.0 < local_34) {
      local_34 = 1.0;
    }
    local_30 = *(float *)(tmp_i1 + 0x500) + (local_20 - *(float *)(tmp_i1 + 0x500)) * tmp_f2;
    if (0.0 <= local_30) {
      tmp_i1 = *(int *)(param_1 + 0xe8);
      if (1.0 < local_30) {
        local_30 = 1.0;
      }
      goto joined_r0x000fa70d;
    }
LAB_000fa88a:
    local_30 = 0.0;
  }
  else if (g_bindItem == param_1) {
    local_2c = 0.8;
    local_28 = 0.0;
    local_24 = 0.0;
    local_20 = 0.8;
    tmp_d5 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_f2 = (float)tmp_d5 * 0.5 + 0.5;
    local_3c = (0.8 - *(float *)(param_1 + 0x74)) * tmp_f2 + *(float *)(param_1 + 0x74);
    if (local_3c < 0.0) {
      local_3c = 0.0;
    }
    else if (1.0 < local_3c) {
      local_3c = 1.0;
    }
    local_38 = (local_28 - *(float *)(tmp_i3 + 0x78)) * tmp_f2 + *(float *)(tmp_i3 + 0x78);
    if (local_38 < 0.0) {
      local_38 = 0.0;
    }
    else if (1.0 < local_38) {
      local_38 = 1.0;
    }
    local_34 = (local_24 - *(float *)(tmp_i3 + 0x7c)) * tmp_f2 + *(float *)(tmp_i3 + 0x7c);
    if (local_34 < 0.0) {
      local_34 = 0.0;
    }
    else if (1.0 < local_34) {
      local_34 = 1.0;
    }
    local_30 = *(float *)(tmp_i3 + 0x80) + (local_20 - *(float *)(tmp_i3 + 0x80)) * tmp_f2;
    if (local_30 < 0.0) goto LAB_000fa88a;
    if (1.0 < local_30) {
      local_30 = 1.0;
    }
  }
  else {
    local_3c = *(float *)(param_1 + 0x74);
    local_30 = *(float *)(param_1 + 0x80);
    local_38 = *(float *)(param_1 + 0x78);
    local_34 = *(float *)(param_1 + 0x7c);
  }
  tmp_i1 = *(int *)(param_1 + 0xe8);
joined_r0x000fa70d:
  if (tmp_i1 == 0) {
    (**(void **)(DC + 0x10))
              (*(uint32_t *)(param_1 + 0xb8),*(uint32_t *)(param_1 + 0xbc),
               *(uint32_t *)(param_1 + 0xdc),&local_3c,"FIXME",0,tmp_u4,
               *(uint32_t *)(param_1 + 0xe4));
    return;
  }
  Item_Text_Paint(param_1);
  BindingFromName(*(uint32_t *)(param_1 + 0x114));
  (**(void **)(DC + 0x10))
            (*(float *)(param_1 + 0xb8) + *(float *)(param_1 + 0xc0) + 8.0,
             *(uint32_t *)(param_1 + 0xbc),*(uint32_t *)(param_1 + 0xdc),&local_3c,g_nameBind1,0
             ,tmp_u4,*(uint32_t *)(param_1 + 0xe4));
  return;
}

uint32_t Display_KeyBindPending(void)
{
  return g_waitingForKey;
}

uint32_t Item_Bind_HandleKey(float *param_1,uint param_2,int param_3)
{
  uint tmp_u1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint32_t tmp_u6;
  int tmp_i7;
  uint tmp_u8;
  uint8_t **tmp_ppu9;
  int tmp_i10;
  uint *tmp_pu11;
  bool tmp_b12;
  uint local_24;
  uint local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0xfa959;
  tmp_f3 = (float)*(int *)(DC + 0x124);
  if (param_1 != (float *)0x0) {
    tmp_f2 = *(float *)(DC + 0x2003c);
    if (1.3333334 < tmp_f2) {
      tmp_f4 = tmp_f2 * 0.75;
      tmp_f3 = tmp_f3 * tmp_f4;
      if (tmp_f4 * *param_1 < tmp_f3) {
        tmp_f5 = *param_1 + param_1[2];
        if (1.3333334 < tmp_f2) {
          tmp_f5 = tmp_f5 * tmp_f4;
        }
        goto LAB_000fa9d2;
      }
    }
    else if (*param_1 < tmp_f3) {
      tmp_f5 = *param_1 + param_1[2];
LAB_000fa9d2:
      if (tmp_f3 < tmp_f5) {
        if ((param_1[1] < (float)*(int *)(DC + 0x128)) &&
           ((float)*(int *)(DC + 0x128) < param_1[1] + param_1[3])) {
          if (g_waitingForKey == 0) {
            if (param_3 == 0) {
              return 0;
            }
            if ((param_2 != 0xd) && (param_2 != 0xb2)) {
              return 0;
            }
            g_bindItem = param_1;
            g_waitingForKey = 1;
            return 1;
          }
          goto LAB_000faa3e;
        }
      }
    }
  }
  if (g_waitingForKey == 0) {
    return 0;
  }
LAB_000faa3e:
  if (g_bindItem == (float *)0x0) {
    tmp_u6 = 0;
  }
  else {
    tmp_u6 = 1;
    if (((param_2 & 0x400) == 0) && (param_2 != 0x60)) {
      if (param_2 == 0x7f) {
        tmp_i10 = 0;
        tmp_f3 = param_1[0x45];
        do {
          tmp_i7 = Q_stricmp(tmp_f3,(&g_bindings)[tmp_i10 * 8]);
          if (tmp_i7 == 0) {
            (**(void **)(DC + 0xc4))((&g_unk_0014a9d8)[tmp_i10 * 8],&g_unk_0011d841);
            (**(void **)(DC + 0xc4))((&g_unk_0014a9dc)[tmp_i10 * 8],&g_unk_0011d841);
            (&g_unk_0014a9d8)[tmp_i10 * 8] = 0xffffffff;
            (&g_unk_0014a9dc)[tmp_i10 * 8] = 0xffffffff;
            goto LAB_000fac68;
          }
          tmp_i10 = tmp_i10 + 1;
        } while (tmp_i10 != 0x3d);
        (**(void **)(DC + 0xbc))(param_1[0x45],&local_24,local_20);
        if (local_24 != 0xffffffff) {
          (**(void **)(DC + 0xc4))(local_24,&g_unk_0011d841);
        }
        if (local_20[0] != 0xffffffff) {
          (**(void **)(DC + 0xc4))(local_20[0],&g_unk_0011d841);
        }
LAB_000fac68:
        tmp_ppu9 = &g_bindings;
        do {
          if (tmp_ppu9[6] != (uint8_t *)0xffffffff) {
            (**(void **)(DC + 0xc4))(tmp_ppu9[6],*tmp_ppu9);
            if (tmp_ppu9[7] != (uint8_t *)0xffffffff) {
              (**(void **)(DC + 0xc4))(tmp_ppu9[7],*tmp_ppu9);
            }
          }
          tmp_ppu9 = tmp_ppu9 + 8;
        } while (tmp_ppu9 != &commandList);
      }
      else {
        if (param_2 == 0x1b) {
          g_bindItem = (float *)0x0;
          g_waitingForKey = 0;
          return 1;
        }
        tmp_i10 = 0;
        tmp_f3 = param_1[0x45];
        do {
          tmp_i7 = Q_stricmp(tmp_f3,(&g_bindings)[tmp_i10 * 8]);
          if (tmp_i7 == 0) goto LAB_000faab8;
          tmp_i10 = tmp_i10 + 1;
        } while (tmp_i10 != 0x3d);
        tmp_i10 = -1;
LAB_000faab8:
        tmp_i7 = 0;
        tmp_pu11 = &g_unk_0014a9d8;
        do {
          if (tmp_i7 != tmp_i10) {
            tmp_u8 = tmp_pu11[1];
            if (param_2 == tmp_u8) {
              (**(void **)(DC + 0xc4))(*tmp_pu11,&g_unk_0011d841);
              tmp_u8 = 0xffffffff;
              tmp_u1 = *tmp_pu11;
              tmp_pu11[1] = 0xffffffff;
            }
            else {
              tmp_u1 = *tmp_pu11;
            }
            if (param_2 == tmp_u1) {
              *tmp_pu11 = tmp_u8;
              (**(void **)(DC + 0xc4))(tmp_u8,&g_unk_0011d841);
              tmp_pu11[1] = 0xffffffff;
            }
          }
          tmp_i7 = tmp_i7 + 1;
          tmp_pu11 = tmp_pu11 + 8;
        } while (tmp_i7 != 0x3d);
        if (tmp_i10 == -1) {
          (**(void **)(DC + 0xbc))(param_1[0x45],&local_24,local_20);
          if (((param_2 == local_24) ||
              (tmp_b12 = param_2 == local_20[0], local_20[0] = local_24, tmp_b12)) &&
             (local_20[0] != 0xffffffff)) {
            (**(void **)(DC + 0xc4))(local_20[0],&g_unk_0011d841);
          }
          else {
            (**(void **)(DC + 0xc4))(param_2,param_1[0x45]);
          }
        }
        else {
          tmp_u8 = (&g_unk_0014a9d8)[tmp_i10 * 8];
          if (tmp_u8 == 0xffffffff) {
            (&g_unk_0014a9d8)[tmp_i10 * 8] = param_2;
          }
          else if ((param_2 == tmp_u8) || ((&g_unk_0014a9dc)[tmp_i10 * 8] != -1)) {
            (**(void **)(DC + 0xc4))(tmp_u8,&g_unk_0011d841);
            (**(void **)(DC + 0xc4))((&g_unk_0014a9dc)[tmp_i10 * 8],&g_unk_0011d841);
            (&g_unk_0014a9d8)[tmp_i10 * 8] = param_2;
            (&g_unk_0014a9dc)[tmp_i10 * 8] = 0xffffffff;
          }
          else {
            (&g_unk_0014a9dc)[tmp_i10 * 8] = param_2;
          }
        }
        tmp_ppu9 = &g_bindings;
        do {
          if (tmp_ppu9[6] != (uint8_t *)0xffffffff) {
            (**(void **)(DC + 0xc4))(tmp_ppu9[6],*tmp_ppu9);
            if (tmp_ppu9[7] != (uint8_t *)0xffffffff) {
              (**(void **)(DC + 0xc4))(tmp_ppu9[7],*tmp_ppu9);
            }
          }
          tmp_ppu9 = tmp_ppu9 + 8;
        } while (tmp_ppu9 != &commandList);
      }
      (**(void **)(DC + 200))(2,"in_restart\n");
      g_waitingForKey = 0;
      g_bindItem = (float *)0x0;
      return 1;
    }
  }
  return tmp_u6;
}

void AdjustFrom640(float *param_1,float *param_2,float *param_3,float *param_4)
{
  *param_1 = *param_1 * *(float *)(DC + 0x114);
  *param_2 = *param_2 * *(float *)(DC + 0x110);
  *param_3 = *param_3 * *(float *)(DC + 0x114);
  *param_4 = *param_4 * *(float *)(DC + 0x110);
  if (1.3333334 < *(float *)(DC + 0x2003c)) {
    *param_1 = (1.3333334 / *(float *)(DC + 0x2003c)) * *param_1;
    *param_3 = (1.3333334 / *(float *)(DC + 0x2003c)) * *param_3;
  }
  return;
}

void Item_Model_Paint(float *param_1)
{
  int tmp_i1;
  float __x;
  int *tmp_pi2;
  int tmp_i3;
  int tmp_i4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  int tmp_i8;
  uint tmp_u9;
  int tmp_i10;
  float tmp_f11;
  uint8_t local_2d8 [4];
  float local_2d4;
  float local_2d0;
  uint8_t local_2cc [4];
  float local_2c8;
  float local_2c4;
  uint32_t local_2c0;
  float local_2bc;
  uint32_t local_2b8;
  float local_2b4 [7];
  uint8_t local_298 [76];
  float local_24c;
  float local_248;
  float local_244;
  int local_240;
  float local_230;
  float local_22c;
  float local_228;
  int local_224;
  float local_214;
  int local_1c8 [4];
  float local_1b8;
  float local_1b4;
  uint8_t local_1a4 [36];
  int local_180;
  uint32_t local_17c;
  
  tmp_pi2 = (int *)param_1[0x94];
  if ((tmp_pi2 != (int *)0x0) && (tmp_f11 = param_1[0x3c], tmp_f11 != 0.0)) {
    tmp_u9 = 0;
    do {
      *(uint32_t *)((int)local_1c8 + tmp_u9) = 0;
      *(uint32_t *)((int)local_1c8 + tmp_u9 + 4) = 0;
      tmp_u9 = tmp_u9 + 8;
    } while (tmp_u9 < 0x1a8);
    *(uint32_t *)((int)local_1c8 + tmp_u9) = 0;
    local_17c = 1;
    AxisClear(local_1a4);
    tmp_f5 = (*param_1 + 1.0) * *(float *)(DC + 0x114);
    local_1b8 = (param_1[2] - 2.0) * *(float *)(DC + 0x114);
    local_1b4 = (param_1[3] - 2.0) * *(float *)(DC + 0x110);
    if (1.3333334 < *(float *)(DC + 0x2003c)) {
      tmp_f6 = 1.3333334 / *(float *)(DC + 0x2003c);
      tmp_f5 = tmp_f5 * tmp_f6;
      local_1b8 = tmp_f6 * local_1b8;
    }
    local_1c8[0] = (int)ROUND(tmp_f5);
    local_1c8[1] = (int)ROUND((param_1[1] + 1.0) * *(float *)(DC + 0x110));
    local_1c8[2] = (int)ROUND(local_1b8);
    local_1c8[3] = (int)ROUND(local_1b4);
    (**(void **)(DC + 0x38))(tmp_f11,local_2d8,local_2cc);
    tmp_f5 = (local_2d0 + local_2c4) * -0.5;
    tmp_f6 = (local_2d4 + local_2c8) * 0.5;
    tmp_f7 = ((local_2c4 - local_2d0) * 0.5) / 0.268;
    if ((float)tmp_pi2[4] != 0.0) {
      local_1b8 = (float)tmp_pi2[4];
    }
    if ((float)tmp_pi2[5] != 0.0) {
      local_1b4 = (float)tmp_pi2[5];
    }
    (**(void **)(DC + 0x4c))();
    local_180 = *(int *)(DC + 0x11c);
    tmp_u9 = 0;
    do {
      *(uint32_t *)((int)local_2b4 + tmp_u9) = 0;
      *(uint32_t *)((int)local_2b4 + tmp_u9 + 4) = 0;
      tmp_u9 = tmp_u9 + 8;
    } while (tmp_u9 < 0xe8);
    *(uint32_t *)((int)local_2b4 + tmp_u9) = 0;
    if ((tmp_pi2[6] != 0) && ((int)param_1[0x1c] < local_180)) {
      param_1[0x1c] = (float)(local_180 + tmp_pi2[6]);
      *tmp_pi2 = (*tmp_pi2 + 1) % 0x168;
    }
    local_2c0 = 0;
    local_2bc = (float)*tmp_pi2;
    local_2b8 = 0;
    AnglesToAxis(&local_2c0,local_298);
    tmp_i8 = DC;
    if (tmp_pi2[0xf] == 0) {
      __x = (float)tmp_pi2[0xe];
    }
    else {
      __x = (float)tmp_pi2[0xb] * ((float)(*(int *)(DC + 0x11c) - tmp_pi2[0xf]) / 1000.0) +
            (float)tmp_pi2[0xe];
      tmp_pi2[0xe] = (int)__x;
    }
    local_2b4[2] = tmp_f11;
    if (__x <= 1.0) {
      local_240 = tmp_pi2[0xc];
    }
    else {
      tmp_f11 = floorf(__x);
      tmp_i1 = (int)ROUND(tmp_f11);
      tmp_i3 = tmp_pi2[9];
      local_240 = tmp_i1 + tmp_pi2[0xc];
      tmp_i4 = tmp_pi2[8];
      tmp_pi2[0xc] = local_240;
      if (tmp_i3 < local_240 - tmp_i4) {
        local_240 = tmp_i4 + local_240 % tmp_i3;
        tmp_pi2[0xc] = local_240;
      }
      tmp_i10 = tmp_i1 + tmp_pi2[0xd];
      if (tmp_i3 < tmp_i10 - tmp_i4) {
        tmp_i10 = tmp_i4 + tmp_i10 % tmp_i3;
      }
      tmp_pi2[0xd] = tmp_i10;
      tmp_pi2[0xe] = (int)(__x - (float)tmp_i1);
    }
    tmp_pi2[0xf] = *(int *)(tmp_i8 + 0x11c);
    local_224 = tmp_pi2[0xd];
    local_214 = 1.0 - (float)tmp_pi2[0xe];
    local_2b4[1] = 6.72623e-44;
    local_2b4[3] = tmp_f7;
    local_2b4[4] = tmp_f6;
    local_2b4[5] = tmp_f5;
    local_24c = tmp_f7;
    local_248 = tmp_f6;
    local_244 = tmp_f5;
    local_230 = tmp_f7;
    local_22c = tmp_f6;
    local_228 = tmp_f5;
    (**(void **)(tmp_i8 + 0x50))(local_2b4);
    (**(void **)(DC + 0x54))(local_1c8);
  }
  return;
}

void Item_Image_Paint(float *param_1)
{
  if (param_1 != (float *)0x0) {
    (**(void **)(DC + 8))
              (*param_1 + 1.0,param_1[1] + 1.0,param_1[2] - 2.0,param_1[3] - 2.0,param_1[0x3c]);
  }
  return;
}

void Item_ListBox_Paint(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int *tmp_pi4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  int *tmp_pi11;
  float local_90;
  int local_88;
  float local_84;
  float local_6c;
  float local_68;
  int local_40;
  int local_3c [11];
  
  local_90 = *param_1;
  tmp_pi4 = (int *)param_1[0x94];
  local_84 = param_1[1];
  tmp_f1 = param_1[2];
  local_68 = param_1[3];
  tmp_i8 = (**(void **)(DC + 0x90))(param_1[0x92]);
  tmp_f5 = (float)tmp_i8;
  if ((*(byte *)((int)param_1 + 0x49) & 4) == 0) {
    tmp_f2 = ((tmp_f1 + local_90) - 16.0) - 1.0;
    tmp_f3 = local_84 + 1.0;
    (**(void **)(DC + 8))(tmp_f2,tmp_f3,0x41800000,0x41800000,*(uint32_t *)(DC + 0x1e2dc));
    tmp_pi4[1] = *tmp_pi4;
    (**(void **)(DC + 8))
              (tmp_f2,tmp_f3 + 15.0,0x41800000,(local_68 - 32.0) + 1.0,*(uint32_t *)(DC + 0x1e2ec));
    tmp_f6 = tmp_f3 + 15.0 + ((local_68 - 32.0) - 1.0);
    (**(void **)(DC + 8))(tmp_f2,tmp_f6,0x41800000,0x41800000,*(uint32_t *)(DC + 0x1e2e0));
    tmp_i8 = Item_ListBox_ThumbDrawPosition(param_1);
    tmp_f7 = (float)tmp_i8;
    tmp_f6 = (tmp_f6 - 16.0) - 1.0;
    if (tmp_f6 < tmp_f7) {
      tmp_f7 = tmp_f6;
    }
    (**(void **)(DC + 8))(tmp_f2,tmp_f7,0x41800000,0x41800000,*(uint32_t *)(DC + 0x1e2f0));
    if (tmp_pi4[6] == 1) {
      local_90 = local_90 + 1.0;
      for (tmp_f1 = (float)*tmp_pi4; tmp_f1 < tmp_f5; tmp_f1 = tmp_f1 + 1.0) {
        if ((float)(int)param_1[0x93] == tmp_f1) {
          (**(void **)(DC + 0x3c))
                    (local_90,tmp_f3,(float)tmp_pi4[4] - 1.0,(float)tmp_pi4[5] - 1.0,param_1 + 0x29);
        }
        tmp_i8 = (**(void **)(DC + 0x9c))(param_1[0x92],(int)ROUND(tmp_f1));
        if (tmp_i8 != 0) {
          (**(void **)(DC + 8))
                    (local_90 + 1.0,tmp_f3 + 1.0,(float)tmp_pi4[4] - 2.0,(float)tmp_pi4[5] - 2.0,tmp_i8)
          ;
        }
        if ((float)(int)param_1[0x93] == tmp_f1) {
          (**(void **)(DC + 0x40))
                    (local_90,tmp_f3,(float)tmp_pi4[4] - 1.0,(float)tmp_pi4[5] - 1.0,param_1[0x11],
                     param_1 + 0x25);
        }
        tmp_f2 = (float)tmp_pi4[5];
        local_68 = local_68 - tmp_f2;
        tmp_pi4[1] = tmp_pi4[1] + 1;
        if (local_68 < tmp_f2) {
          tmp_pi4[2] = (int)ROUND(local_68);
          return;
        }
        tmp_f3 = tmp_f2 + tmp_f3;
      }
    }
    else {
      local_6c = (float)*tmp_pi4;
      if (local_6c < tmp_f5) {
        if (tmp_pi4[7] < 1) goto LAB_000fb984;
        do {
          local_88 = 0;
          tmp_pi11 = tmp_pi4 + 8;
          do {
            tmp_i10 = 0;
            tmp_i9 = (**(void **)(DC + 0x94))
                              (param_1[0x92],(int)ROUND(local_6c),local_88,local_3c,&local_40);
            tmp_i8 = local_40;
            if (local_40 < 1) {
              if (tmp_i9 != 0) {
                (**(void **)(DC + 0x10))
                          ((float)*tmp_pi11 + local_90 + 4.0 + param_1[0x35],
                           local_84 + (float)tmp_pi4[5] + param_1[0x36],param_1[0x37],param_1 + 0x1d,
                           tmp_i9,0,tmp_pi11[2],param_1[0x39]);
              }
            }
            else {
              do {
                tmp_i9 = local_3c[tmp_i10];
                if (-1 < tmp_i9) {
                  tmp_f2 = (float)tmp_pi4[5] - 2.0;
                  (**(void **)(DC + 8))
                            ((float)*tmp_pi11 + local_90 + (float)tmp_i10 * (float)tmp_pi4[5] + 1.0,
                             local_84 + 1.0,tmp_f2,tmp_f2,tmp_i9);
                  tmp_i8 = local_40;
                }
                tmp_i10 = tmp_i10 + 1;
              } while (tmp_i10 < tmp_i8);
            }
            local_88 = local_88 + 1;
            tmp_pi11 = tmp_pi11 + 3;
          } while (local_88 < tmp_pi4[7]);
          while( true ) {
            if ((float)(int)param_1[0x93] == local_6c) {
              (**(void **)(DC + 0x3c))
                        (local_90,local_84,(tmp_f1 - 16.0) - 2.0,tmp_pi4[5],param_1 + 0x29);
            }
            tmp_f2 = (float)tmp_pi4[5];
            local_68 = local_68 - tmp_f2;
            if (local_68 < tmp_f2) {
              tmp_pi4[2] = (int)ROUND(local_68);
              return;
            }
            local_84 = tmp_f2 + local_84;
            tmp_pi4[1] = tmp_pi4[1] + 1;
            local_6c = local_6c + 1.0;
            if (tmp_f5 <= local_6c) {
              return;
            }
            if (0 < tmp_pi4[7]) break;
LAB_000fb984:
            tmp_i8 = (**(void **)(DC + 0x94))
                              (param_1[0x92],(int)ROUND(local_6c),0,local_3c,&local_40);
            if ((tmp_i8 != 0) && (local_40 < 0)) {
              (**(void **)(DC + 0x10))
                        (local_90 + 4.0 + param_1[0x35],local_84 + (float)tmp_pi4[5] + param_1[0x36],
                         param_1[0x37],param_1 + 0x1d,tmp_i8,0,0,param_1[0x39]);
            }
          }
        } while( true );
      }
    }
  }
  else {
    local_90 = local_90 + 1.0;
    tmp_f2 = ((local_68 + local_84) - 16.0) - 1.0;
    (**(void **)(DC + 8))(local_90,tmp_f2,0x41800000,0x41800000,*(uint32_t *)(DC + 0x1e2e4));
    (**(void **)(DC + 8))
              (local_90 + 15.0,tmp_f2,(tmp_f1 - 32.0) + 1.0,0x41800000,*(uint32_t *)(DC + 0x1e2ec));
    tmp_f3 = local_90 + 15.0 + ((tmp_f1 - 32.0) - 1.0);
    (**(void **)(DC + 8))(tmp_f3,tmp_f2,0x41800000,0x41800000,*(uint32_t *)(DC + 0x1e2e8));
    tmp_i8 = Item_ListBox_ThumbDrawPosition(param_1);
    tmp_f6 = (float)tmp_i8;
    tmp_f3 = (tmp_f3 - 16.0) - 1.0;
    if (tmp_f3 < tmp_f6) {
      tmp_f6 = tmp_f3;
    }
    (**(void **)(DC + 8))(tmp_f6,tmp_f2,0x41800000,0x41800000,*(uint32_t *)(DC + 0x1e2f0));
    tmp_pi4[1] = *tmp_pi4;
    if (tmp_pi4[6] == 1) {
      tmp_f2 = (float)*tmp_pi4;
      if (tmp_f2 < tmp_f5) {
        tmp_f1 = tmp_f1 - 2.0;
        do {
          tmp_i8 = (**(void **)(DC + 0x9c))(param_1[0x92],(int)ROUND(tmp_f2));
          if (tmp_i8 != 0) {
            (**(void **)(DC + 8))
                      (local_90 + 1.0,local_84 + 1.0 + 1.0,(float)tmp_pi4[4] - 2.0,
                       (float)tmp_pi4[5] - 2.0,tmp_i8);
          }
          if ((float)(int)param_1[0x93] == tmp_f2) {
            (**(void **)(DC + 0x40))
                      (local_90,local_84 + 1.0,(float)tmp_pi4[4] - 1.0,(float)tmp_pi4[5] - 1.0,
                       param_1[0x11],param_1 + 0x25);
            tmp_f3 = (float)tmp_pi4[4];
            tmp_f1 = tmp_f1 - tmp_f3;
            if (tmp_f1 < tmp_f3) {
LAB_000fbc9b:
              tmp_pi4[2] = (int)ROUND(tmp_f1);
              return;
            }
          }
          else {
            tmp_f3 = (float)tmp_pi4[4];
            tmp_f1 = tmp_f1 - tmp_f3;
            if (tmp_f1 < tmp_f3) goto LAB_000fbc9b;
          }
          local_90 = tmp_f3 + local_90;
          tmp_pi4[1] = tmp_pi4[1] + 1;
          tmp_f2 = tmp_f2 + 1.0;
        } while (tmp_f2 < tmp_f5);
      }
    }
  }
  return;
}

void Item_OwnerDraw_Paint(uint32_t *param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  uint tmp_u4;
  int tmp_i5;
  long double tmp_l6;
  double tmp_d7;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i5 = DC;
  if (param_1 == (uint32_t *)0x0) {
    return;
  }
  if (*(int *)(DC + 0x5c) == 0) {
    return;
  }
  tmp_i3 = param_1[0x3b];
  tmp_u4 = param_1[0x12];
  tmp_f1 = *(float *)(tmp_i3 + 0xd4);
  tmp_f2 = *(float *)(tmp_i3 + 0xd0);
  if (((tmp_u4 & 0x60) != 0) && ((int)param_1[0x1c] < *(int *)(DC + 0x11c))) {
    param_1[0x1c] = *(int *)(DC + 0x11c) + *(int *)(tmp_i3 + 0xcc);
    if ((tmp_u4 & 0x20) == 0) {
      tmp_f1 = tmp_f1 + (float)param_1[0x20];
      if (tmp_f1 < tmp_f2) {
        param_1[0x20] = tmp_f1;
      }
      else {
        param_1[0x20] = tmp_f2;
        param_1[0x12] = tmp_u4 & 0xffffffbf;
      }
    }
    else {
      tmp_f1 = (float)param_1[0x20] - tmp_f1;
      param_1[0x20] = tmp_f1;
      if (tmp_f1 <= 0.0) {
        param_1[0x12] = tmp_u4 & 0xffffffdb;
      }
    }
  }
  local_3c = (float)param_1[0x1d];
  local_30 = (float)param_1[0x20];
  local_38 = (float)param_1[0x1e];
  local_34 = (float)param_1[0x1f];
  if ((0 < (int)param_1[0x4a]) && (*(void **)(tmp_i5 + 0x60) != (void *)0x0)) {
    tmp_l6 = (long double)(**(void **)(tmp_i5 + 0x60))(param_1[0xf],param_1[0x91]);
    tmp_i5 = param_1[0x4a];
    if (0 < tmp_i5) {
      if ((tmp_l6 < (long double)(float)param_1[0x50]) || ((long double)(float)param_1[0x51] < tmp_l6))
      {
        if (tmp_i5 == 1) goto LAB_000fc100;
        if ((tmp_l6 < (long double)(float)param_1[0x57]) || ((long double)(float)param_1[0x58] < tmp_l6)
           ) {
          if (tmp_i5 == 2) goto LAB_000fc100;
          if ((tmp_l6 < (long double)(float)param_1[0x5e]) ||
             ((long double)(float)param_1[0x5f] < tmp_l6)) {
            if (tmp_i5 == 3) goto LAB_000fc100;
            if ((tmp_l6 < (long double)(float)param_1[0x65]) ||
               ((long double)(float)param_1[0x66] < tmp_l6)) {
              if (tmp_i5 == 4) goto LAB_000fc100;
              if ((tmp_l6 < (long double)(float)param_1[0x6c]) ||
                 ((long double)(float)param_1[0x6d] < tmp_l6)) {
                if (tmp_i5 == 5) goto LAB_000fc100;
                if ((tmp_l6 < (long double)(float)param_1[0x73]) ||
                   ((long double)(float)param_1[0x74] < tmp_l6)) {
                  if (tmp_i5 == 6) goto LAB_000fc100;
                  if ((tmp_l6 < (long double)(float)param_1[0x7a]) ||
                     ((long double)(float)param_1[0x7b] < tmp_l6)) {
                    if (tmp_i5 == 7) goto LAB_000fc100;
                    if ((tmp_l6 < (long double)(float)param_1[0x81]) ||
                       ((long double)(float)param_1[0x82] < tmp_l6)) {
                      if (tmp_i5 == 8) goto LAB_000fc100;
                      if ((tmp_l6 < (long double)(float)param_1[0x88]) ||
                         ((long double)(float)param_1[0x89] < tmp_l6)) {
                        if ((tmp_i5 == 9) ||
                           ((tmp_l6 < (long double)(float)param_1[0x8f] ||
                            (tmp_i5 = 9, (long double)(float)param_1[0x90] < tmp_l6))))
                        goto LAB_000fc100;
                      }
                      else {
                        tmp_i5 = 8;
                      }
                    }
                    else {
                      tmp_i5 = 7;
                    }
                  }
                  else {
                    tmp_i5 = 6;
                  }
                }
                else {
                  tmp_i5 = 5;
                }
              }
              else {
                tmp_i5 = 4;
              }
            }
            else {
              tmp_i5 = 3;
            }
          }
          else {
            tmp_i5 = 2;
          }
        }
        else {
          tmp_i5 = 1;
        }
      }
      else {
        tmp_i5 = 0;
      }
      local_3c = (float)param_1[tmp_i5 * 7 + 0x4b];
      local_38 = (float)param_1[tmp_i5 * 7 + 0x4c];
      local_34 = (float)param_1[tmp_i5 * 7 + 0x4d];
      local_30 = (float)param_1[tmp_i5 * 7 + 0x4e];
    }
  }
LAB_000fc100:
  if ((param_1[0x12] & 0x8000002) == 0x8000002) {
    local_2c = *(float *)(tmp_i3 + 0x4f4) * 0.8;
    local_28 = *(float *)(tmp_i3 + 0x4f8) * 0.8;
    local_24 = *(float *)(tmp_i3 + 0x4fc) * 0.8;
    local_20 = *(float *)(tmp_i3 + 0x500) * 0.8;
    tmp_d7 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_f1 = (float)tmp_d7 * 0.5 + 0.5;
    local_3c = (local_2c - *(float *)(tmp_i3 + 0x4f4)) * tmp_f1 + *(float *)(tmp_i3 + 0x4f4);
    if (local_3c < 0.0) {
      local_3c = 0.0;
    }
    else if (1.0 < local_3c) {
      local_3c = 1.0;
    }
    local_38 = (local_28 - *(float *)(tmp_i3 + 0x4f8)) * tmp_f1 + *(float *)(tmp_i3 + 0x4f8);
    if (local_38 < 0.0) {
      local_38 = 0.0;
    }
    else if (1.0 < local_38) {
      local_38 = 1.0;
    }
    local_34 = (local_24 - *(float *)(tmp_i3 + 0x4fc)) * tmp_f1 + *(float *)(tmp_i3 + 0x4fc);
    if (local_34 < 0.0) {
      local_34 = 0.0;
    }
    else if (1.0 < local_34) {
      local_34 = 1.0;
    }
    local_30 = (local_20 - *(float *)(tmp_i3 + 0x500)) * tmp_f1 + *(float *)(tmp_i3 + 0x500);
  }
  else {
    if ((param_1[0x39] != 1) || ((*(int *)(DC + 0x11c) / 200 & 1U) != 0)) goto LAB_000fc120;
    local_2c = (float)param_1[0x1d] * 0.8;
    local_28 = (float)param_1[0x1e] * 0.8;
    local_24 = (float)param_1[0x1f] * 0.8;
    local_20 = (float)param_1[0x20] * 0.8;
    tmp_d7 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_f1 = (float)tmp_d7 * 0.5 + 0.5;
    local_3c = (local_2c - (float)param_1[0x1d]) * tmp_f1 + (float)param_1[0x1d];
    if (local_3c < 0.0) {
      local_3c = 0.0;
    }
    else if (1.0 < local_3c) {
      local_3c = 1.0;
    }
    local_38 = (local_28 - (float)param_1[0x1e]) * tmp_f1 + (float)param_1[0x1e];
    if (local_38 < 0.0) {
      local_38 = 0.0;
    }
    else if (1.0 < local_38) {
      local_38 = 1.0;
    }
    local_34 = (local_24 - (float)param_1[0x1f]) * tmp_f1 + (float)param_1[0x1f];
    if (local_34 < 0.0) {
      local_34 = 0.0;
    }
    else if (1.0 < local_34) {
      local_34 = 1.0;
    }
    local_30 = (local_20 - (float)param_1[0x20]) * tmp_f1 + (float)param_1[0x20];
  }
  if (0.0 <= local_30) {
    if (1.0 < local_30) {
      local_30 = 1.0;
    }
  }
  else {
    local_30 = 0.0;
  }
LAB_000fc120:
  if (((*(byte *)(param_1 + 0x48) & 3) != 0) &&
     (tmp_i5 = Item_EnableShowViaCvar(param_1,1), tmp_i5 == 0)) {
    local_3c = *(float *)(tmp_i3 + 0x504);
    local_30 = *(float *)(tmp_i3 + 0x510);
    local_38 = *(float *)(tmp_i3 + 0x508);
    local_34 = *(float *)(tmp_i3 + 0x50c);
  }
  if (param_1[0x3a] == 0) {
    (**(void **)(DC + 0x5c))
              (*param_1,param_1[1],param_1[2],param_1[3],param_1[0x35],param_1[0x36],param_1[0xf],
               param_1[0x10],param_1[0x33],param_1[0x92],param_1[0x37],&local_3c,param_1[0x2d],
               param_1[0x39]);
    return;
  }
  Item_Text_Paint(param_1);
  if (*(char *)param_1[0x3a] == '\0') {
    (**(void **)(DC + 0x5c))
              ((float)param_1[0x2e] + (float)param_1[0x30],param_1[1],param_1[2],param_1[3],0,
               param_1[0x36],param_1[0xf],param_1[0x10],param_1[0x33],param_1[0x92],param_1[0x37],
               &local_3c,param_1[0x2d],param_1[0x39]);
    return;
  }
  (**(void **)(DC + 0x5c))((float)param_1[0x2e] + (float)param_1[0x30] + 8.0);
  return;
}

void Item_Paint(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  byte tmp_b3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  float *pfVar7;
  int tmp_i8;
  uint32_t *tmp_pu9;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  tmp_f4 = param_1[0x3b];
  if (*(void **)(DC + 0x30) != (void *)0x0) {
    (**(void **)(DC + 0x30))(param_1[0x38]);
  }
  tmp_f5 = param_1[0x12];
  if (((uint)tmp_f5 & 0x10000) == 0) {
LAB_000fc84f:
    if ((((uint)tmp_f5 & 0x100) != 0) && ((int)param_1[0x1c] < *(int *)(DC + 0x11c))) {
      tmp_f5 = param_1[4];
      tmp_f1 = param_1[0x13];
      param_1[0x1c] = (float)(*(int *)(DC + 0x11c) + (int)param_1[0x1b]);
      if (tmp_f5 == tmp_f1) {
        tmp_i8 = 2;
        tmp_i6 = 1;
      }
      else {
        if (tmp_f1 <= tmp_f5) {
          tmp_f5 = tmp_f5 - param_1[0x17];
          if (tmp_f1 <= tmp_f5) goto LAB_000fcb52;
        }
        else {
          tmp_f5 = tmp_f5 + param_1[0x17];
          if (tmp_f5 <= tmp_f1) {
LAB_000fcb52:
            param_1[4] = tmp_f5;
            tmp_i8 = 1;
            tmp_i6 = 0;
            goto LAB_000fc899;
          }
        }
        param_1[4] = tmp_f1;
        tmp_i8 = 2;
        tmp_i6 = 1;
      }
LAB_000fc899:
      tmp_f5 = param_1[5];
      tmp_f1 = param_1[0x14];
      if (tmp_f5 != tmp_f1) {
        if (tmp_f1 <= tmp_f5) {
          tmp_f5 = tmp_f5 - param_1[0x18];
          if (tmp_f5 < tmp_f1) goto LAB_000fcbba;
        }
        else {
          tmp_f5 = tmp_f5 + param_1[0x18];
          if (tmp_f1 < tmp_f5) {
LAB_000fcbba:
            param_1[5] = tmp_f1;
            goto LAB_000fc8e4;
          }
        }
        param_1[5] = tmp_f5;
        tmp_i8 = tmp_i6;
      }
LAB_000fc8e4:
      tmp_f5 = param_1[6];
      tmp_f1 = param_1[0x15];
      if (tmp_f5 == tmp_f1) {
LAB_000fcb94:
        tmp_i8 = tmp_i8 + 1;
      }
      else {
        if (tmp_f1 <= tmp_f5) {
          tmp_f5 = tmp_f5 - param_1[0x19];
          if (tmp_f5 < tmp_f1) goto LAB_000fcb82;
        }
        else {
          tmp_f5 = tmp_f5 + param_1[0x19];
          if (tmp_f1 < tmp_f5) {
LAB_000fcb82:
            param_1[6] = tmp_f1;
            goto LAB_000fcb94;
          }
        }
        param_1[6] = tmp_f5;
      }
      tmp_f5 = param_1[7];
      tmp_f1 = param_1[0x16];
      if (tmp_f5 == tmp_f1) {
LAB_000fc93e:
        tmp_i8 = tmp_i8 + 1;
        pfVar7 = (float *)param_1[0x3b];
        if (pfVar7 != (float *)0x0) {
LAB_000fc94c:
          tmp_f1 = *pfVar7;
          tmp_f2 = pfVar7[1];
          *param_1 = param_1[4] + tmp_f1;
          param_1[1] = param_1[5] + tmp_f2;
          param_1[2] = param_1[6];
          param_1[3] = tmp_f5;
          if (param_1[0x9c] != 0.0) {
            Item_SetScreenCoords(param_1[0x9c],tmp_f1,tmp_f2);
            pfVar7 = (float *)param_1[0x9c];
            tmp_f5 = (*pfVar7 + pfVar7[2]) - 635.0;
            if (0.0 < tmp_f5) {
              pfVar7[4] = pfVar7[4] - tmp_f5;
              *(float *)param_1[0x9c] = *(float *)param_1[0x9c] - tmp_f5;
            }
          }
          param_1[0x30] = 0.0;
          param_1[0x31] = 0.0;
        }
        if (tmp_i8 == 4) {
          param_1[0x12] = (float)((uint)param_1[0x12] & 0xfffffeff);
        }
      }
      else {
        if (tmp_f1 <= tmp_f5) {
          tmp_f5 = tmp_f5 - param_1[0x1a];
          if (tmp_f5 < tmp_f1) goto LAB_000fcbea;
        }
        else {
          tmp_f5 = tmp_f5 + param_1[0x1a];
          if (tmp_f1 < tmp_f5) {
LAB_000fcbea:
            param_1[7] = tmp_f1;
            tmp_f5 = tmp_f1;
            goto LAB_000fc93e;
          }
        }
        pfVar7 = (float *)param_1[0x3b];
        param_1[7] = tmp_f5;
        if (pfVar7 != (float *)0x0) goto LAB_000fc94c;
      }
    }
  }
  else if ((int)param_1[0x1c] < *(int *)(DC + 0x11c)) {
    param_1[0x1c] = (float)(*(int *)(DC + 0x11c) + (int)param_1[0x1b]);
    tmp_f1 = (param_1[4] + param_1[6] * 0.5) - param_1[0x13];
    tmp_f5 = (param_1[5] + param_1[7] * 0.5) - param_1[0x14];
    param_1[4] = ((tmp_f1 * 0.9986295 - tmp_f5 * 0.05233596) + param_1[0x13]) - param_1[6] * 0.5;
    param_1[5] = (tmp_f5 * 0.9986295 + tmp_f1 * 0.05233596 + param_1[0x14]) - param_1[7] * 0.5;
    Item_UpdatePosition(param_1);
    tmp_f5 = param_1[0x12];
    goto LAB_000fc84f;
  }
  if ((param_1[0x10] != 0.0) && (*(void **)(DC + 100) != (void *)0x0)) {
    tmp_i8 = (**(void **)(DC + 100))(param_1[0x10]);
    if (tmp_i8 == 0) {
      param_1[0x12] = (float)((uint)param_1[0x12] & 0xfffffffa);
      tmp_b3 = *(byte *)(param_1 + 0x48);
      goto joined_r0x000fca49;
    }
    param_1[0x12] = (float)((uint)param_1[0x12] | 4);
  }
  tmp_b3 = *(byte *)(param_1 + 0x48);
joined_r0x000fca49:
  if (((((tmp_b3 & 0xc) == 0) || (tmp_i8 = Item_EnableShowViaCvar(param_1,4), tmp_i8 != 0)) &&
      ((((uint)param_1[0x98] & 3) == 0 || (tmp_i8 = Item_SettingShow_constprop_35(), tmp_i8 != 0))))
     && (((param_1[0x99] == 0.0 || (tmp_i8 = Item_SettingShow_constprop_36(), tmp_i8 != 0)) &&
         (((uint)param_1[0x12] & 4) != 0)))) {
    Window_Paint(param_1,*(uint32_t *)((int)tmp_f4 + 0xd4),*(uint32_t *)((int)tmp_f4 + 0xd0),
                 (float)*(int *)((int)tmp_f4 + 0xcc));
    if (debugMode != 0) {
      tmp_pu9 = (uint32_t *)Item_CorrectedTextRect();
      local_20 = 0x3f800000;
      local_28 = 0x3f800000;
      local_24 = 0;
      local_2c = 0;
      (**(void **)(DC + 0x40))(*tmp_pu9,tmp_pu9[1],tmp_pu9[2],tmp_pu9[3],0x3f800000,&local_2c);
    }
    switch(param_1[0x32]) {
    case 0.0:
    case 1.4013e-45:
    case 2.10195e-44:
      Item_Text_Paint(param_1);
      break;
    case 4.2039e-45:
    case 2.24208e-44:
      Item_CheckBox_Paint(param_1);
      break;
    case 5.60519e-45:
    case 1.26117e-44:
      Item_TextField_Paint(param_1);
      break;
    case 8.40779e-45:
      Item_ListBox_Paint(param_1);
      break;
    case 9.80909e-45:
    case 1.96182e-44:
      Item_Model_Paint(param_1);
      break;
    case 1.12104e-44:
      Item_OwnerDraw_Paint(param_1);
      break;
    case 1.4013e-44:
      Item_Slider_Paint(param_1);
      break;
    case 1.54143e-44:
      Item_YesNo_Paint(param_1);
      break;
    case 1.68156e-44:
      Item_Multi_Paint(param_1);
      break;
    case 1.82169e-44:
      Item_Bind_Paint(param_1);
    }
  }
  return;
}

void Menu_Paint_part_20(uint32_t *param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  long double tmp_l3;
  uint32_t local_294;
  uint32_t local_290;
  uint32_t local_28c;
  uint32_t local_288;
  uint32_t *local_1a8;
  
  if (param_2 != 0) {
    param_1[0x12] = param_1[0x12] | 0x100000;
  }
  if (param_1[0x2f] != 0) {
    (**(void **)(DC + 8))(0,0,0x44200000,0x43f00000,param_1[0x2d]);
  }
  Window_Paint(param_1,param_1[0x35],param_1[0x34],(float)(int)param_1[0x33]);
  if ((int)param_1[0x30] < 1) {
    (**(void **)(DC + 0x74))("ui_showtooltips");
  }
  else {
    tmp_i1 = 0;
    tmp_i2 = 0;
    do {
      Item_Paint(param_1[tmp_i2 + 0x145]);
      if ((*(byte *)(param_1[tmp_i2 + 0x145] + 0x48) & 1) != 0) {
        tmp_i1 = param_1[tmp_i2 + 0x145];
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 < (int)param_1[0x30]);
    tmp_l3 = (long double)(**(void **)(DC + 0x74))("ui_showtooltips");
    if ((((tmp_l3 != (long double)0) && (tmp_i1 != 0)) && (tmp_i1 = *(int *)(tmp_i1 + 0x270), tmp_i1 != 0)
        ) && ((*(char **)(tmp_i1 + 0xe8) != (char *)0x0 && (**(char **)(tmp_i1 + 0xe8) != '\0')))) {
      Item_Paint(tmp_i1);
    }
  }
  if (param_1[0x3b] == 0) {
    param_1[0x3b] = *(uint32_t *)(DC + 0x11c);
  }
  else if ((((*(byte *)(param_1 + 0x12) & 4) != 0) && (0 < (int)param_1[0x3a])) &&
          ((param_1[0x3c] != 0 && ((int)(param_1[0x3b] + param_1[0x3a]) <= *(int *)(DC + 0x11c)))))
  {
    local_1a8 = param_1;
    Item_RunScript_constprop_37();
  }
  if (debugMode != 0) {
    local_288 = 0x3f800000;
    local_28c = 0x3f800000;
    local_294 = 0x3f800000;
    local_290 = 0;
    (**(void **)(DC + 0x40))(*param_1,param_1[1],param_1[2],param_1[3],0x3f800000,&local_294);
  }
  return;
}

void Menu_Init(uint32_t *param_1)
{
  uint32_t tmp_u1;
  bool tmp_b2;
  int tmp_i3;
  uint tmp_u4;
  uint tmp_u5;
  uint32_t *tmp_pu6;
  
  tmp_u5 = 0xd18;
  tmp_b2 = false;
  if (((uint)param_1 & 1) == 0) {
    tmp_pu6 = param_1;
    if (((uint)param_1 & 2) != 0) {
LAB_000fd0a0:
      *(uint16_t *)tmp_pu6 = 0;
      tmp_u5 = tmp_u5 - 2;
      tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
    }
  }
  else {
    tmp_pu6 = (uint32_t *)((int)param_1 + 1);
    tmp_u5 = 0xd17;
    tmp_b2 = true;
    *(uint8_t *)param_1 = 0;
    if (((uint)tmp_pu6 & 2) != 0) {
      tmp_u5 = 0xd17;
      tmp_b2 = true;
      goto LAB_000fd0a0;
    }
  }
  if (((uint)tmp_pu6 & 4) != 0) {
    *tmp_pu6 = 0;
    tmp_u5 = tmp_u5 - 4;
    tmp_pu6 = tmp_pu6 + 1;
  }
  for (tmp_u4 = tmp_u5 >> 2; tmp_u4 != 0; tmp_u4 = tmp_u4 - 1) {
    *tmp_pu6 = 0;
    tmp_pu6 = tmp_pu6 + 1;
  }
  if ((tmp_u5 & 2) != 0) {
    *(uint16_t *)tmp_pu6 = 0;
    tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
  }
  if (tmp_b2) {
    *(uint8_t *)tmp_pu6 = 0;
  }
  param_1[0x32] = 0xffffffff;
  tmp_i3 = DC;
  tmp_u5 = 0xb8;
  tmp_b2 = false;
  param_1[0x35] = *(uint32_t *)(DC + 0x1e32c);
  param_1[0x34] = *(uint32_t *)(tmp_i3 + 0x1e324);
  tmp_u1 = *(uint32_t *)(tmp_i3 + 0x1e328);
  param_1[0x345] = 0;
  param_1[0x33] = tmp_u1;
  if (((uint)param_1 & 1) == 0) {
    tmp_pu6 = param_1;
    if (((uint)param_1 & 2) == 0) goto LAB_000fd001;
  }
  else {
    tmp_pu6 = (uint32_t *)((int)param_1 + 1);
    tmp_u5 = 0xb7;
    tmp_b2 = true;
    *(uint8_t *)param_1 = 0;
    if (((uint)tmp_pu6 & 2) == 0) goto LAB_000fd001;
    tmp_u5 = 0xb7;
    tmp_b2 = true;
  }
  *(uint16_t *)tmp_pu6 = 0;
  tmp_u5 = tmp_u5 - 2;
  tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
LAB_000fd001:
  tmp_u4 = 0;
  do {
    *(uint32_t *)((int)tmp_pu6 + tmp_u4) = 0;
    *(uint32_t *)((int)tmp_pu6 + tmp_u4 + 4) = 0;
    tmp_u4 = tmp_u4 + 8;
  } while (tmp_u4 < (tmp_u5 & 0xfffffff8));
  tmp_pu6 = (uint32_t *)((int)tmp_pu6 + tmp_u4);
  if ((tmp_u5 & 4) != 0) {
    *tmp_pu6 = 0;
    tmp_pu6 = tmp_pu6 + 1;
  }
  if ((tmp_u5 & 2) != 0) {
    *(uint16_t *)tmp_pu6 = 0;
    tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
  }
  if (tmp_b2) {
    *(uint8_t *)tmp_pu6 = 0;
  }
  param_1[0x11] = 0x3f800000;
  param_1[0x20] = 0x3f800000;
  param_1[0x1f] = 0x3f800000;
  param_1[0x1e] = 0x3f800000;
  param_1[0x1d] = 0x3f800000;
  param_1[0xc] = 0xffffffff;
  return;
}

int Menu_GetFocusedItem(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 0xc0) < 1)) {
LAB_000fd13a:
    tmp_i1 = 0;
  }
  else {
    tmp_i1 = *(int *)(param_1 + 0x514);
    if ((*(byte *)(tmp_i1 + 0x48) & 2) == 0) {
      tmp_i2 = 0;
      do {
        tmp_i2 = tmp_i2 + 1;
        if (tmp_i2 == *(int *)(param_1 + 0xc0)) goto LAB_000fd13a;
        tmp_i1 = *(int *)(param_1 + 0x514 + tmp_i2 * 4);
      } while ((*(byte *)(tmp_i1 + 0x48) & 2) == 0);
    }
  }
  return tmp_i1;
}

uint32_t * Menu_GetFocused(void)
{
  uint tmp_u1;
  uint *tmp_pu2;
  int tmp_i3;
  
  if (menuCount < 1) {
    return (uint32_t *)0x0;
  }
  if ((g_unk_040f8f88 & 6) == 6) {
    tmp_i3 = 0;
  }
  else {
    tmp_pu2 = &g_unk_040f9ca0;
    tmp_i3 = 0;
    do {
      tmp_i3 = tmp_i3 + 1;
      if (tmp_i3 == menuCount) {
        return (uint32_t *)0x0;
      }
      tmp_u1 = *tmp_pu2;
      tmp_pu2 = tmp_pu2 + 0x346;
    } while ((tmp_u1 & 6) != 6);
  }
  return &Menus + tmp_i3 * 0x346;
}

void Menu_SetFeederSelection(uint32_t *param_1,int param_2,int param_3,int param_4)
{
  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  uint *tmp_pu4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  
  if (param_1 == (uint32_t *)0x0) {
    if (param_4 == 0) {
      if (menuCount < 1) {
        return;
      }
      if ((g_unk_040f8f88 & 6) == 6) {
        tmp_i6 = 0;
      }
      else {
        tmp_pu4 = &g_unk_040f9ca0;
        tmp_i6 = 0;
        do {
          tmp_i6 = tmp_i6 + 1;
          if (tmp_i6 == menuCount) {
            return;
          }
          tmp_u2 = *tmp_pu4;
          tmp_pu4 = tmp_pu4 + 0x346;
        } while ((tmp_u2 & 6) != 6);
      }
      param_1 = &Menus + tmp_i6 * 0x346;
    }
    else {
      if (menuCount < 1) {
        return;
      }
      tmp_pu5 = &g_unk_040f8f60;
      tmp_i6 = 0;
      while (tmp_i3 = Q_stricmp(*tmp_pu5,param_4), tmp_i3 != 0) {
        tmp_i6 = tmp_i6 + 1;
        tmp_pu5 = tmp_pu5 + 0x346;
        if (menuCount <= tmp_i6) {
          return;
        }
      }
      param_1 = &Menus + tmp_i6 * 0x346;
    }
  }
  if (0 < (int)param_1[0x30]) {
    tmp_i6 = param_1[0x145];
    tmp_f1 = *(float *)(tmp_i6 + 0x248);
    tmp_i3 = 0;
    while( true ) {
      if (tmp_f1 == (float)param_2) {
        if (param_3 == 0) {
          tmp_pu5 = *(uint32_t **)(tmp_i6 + 0x250);
          tmp_pu5[3] = 0;
          *tmp_pu5 = 0;
          tmp_i6 = param_1[tmp_i3 + 0x145];
        }
        *(int *)(tmp_i6 + 0x24c) = param_3;
        (**(void **)(DC + 0xa0))
                  (*(uint32_t *)(param_1[tmp_i3 + 0x145] + 0x248),
                   *(uint32_t *)(param_1[tmp_i3 + 0x145] + 0x24c));
        return;
      }
      if (tmp_i3 + 1 == param_1[0x30]) break;
      tmp_i6 = param_1[tmp_i3 + 0x146];
      tmp_f1 = *(float *)(tmp_i6 + 0x248);
      tmp_i3 = tmp_i3 + 1;
    }
  }
  return;
}

uint32_t Menus_AnyFullScreenVisible(void)
{
  byte *tmp_pb1;
  int tmp_i2;
  
  if (0 < menuCount) {
    tmp_pb1 = (byte *)&g_unk_040f8f88;
    tmp_i2 = 0;
    do {
      if (((*tmp_pb1 & 4) != 0) && (*(int *)(tmp_pb1 + 0x74) != 0)) {
        return 1;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pb1 = tmp_pb1 + 0xd18;
    } while (tmp_i2 != menuCount);
  }
  return 0;
}

uint32_t * Menus_ActivateByName(uint32_t param_1,int param_2)
{
  uint tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint *tmp_pu4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  uint32_t *local_28;
  int local_24;
  uint32_t *local_20;
  
  if (menuCount < 1) {
    local_20 = (uint32_t *)0x0;
  }
  else {
    if ((g_unk_040f8f88 & 6) == 6) {
      tmp_i5 = 0;
    }
    else {
      tmp_pu4 = &g_unk_040f9ca0;
      tmp_i5 = 0;
      do {
        tmp_i5 = tmp_i5 + 1;
        if (tmp_i5 == menuCount) {
          local_28 = (uint32_t *)0x0;
          goto LAB_000fd3df;
        }
        tmp_u1 = *tmp_pu4;
        tmp_pu4 = tmp_pu4 + 0x346;
      } while ((tmp_u1 & 6) != 6);
    }
    local_28 = &Menus + tmp_i5 * 0x346;
LAB_000fd3df:
    tmp_pu4 = &g_unk_040f8f88;
    tmp_i5 = 0;
    do {
      tmp_i2 = Q_stricmp(tmp_pu4[-10],param_1);
      tmp_i3 = menuCount;
      if (tmp_i2 == 0) {
        local_20 = &Menus + tmp_i5 * 0x346;
        Menus_Activate(local_20);
        tmp_i3 = menuCount;
        if ((param_2 != 0) && ((*(byte *)((int)&g_unk_040f8f88 + tmp_i5 * 0xd18 + 3) & 4) != 0)) {
          if (0xf < modalMenuCount) {
            Com_Error(2,"MAX_MODAL_MENUS exceeded\n");
          }
          tmp_i5 = modalMenuCount * 4;
          modalMenuCount = modalMenuCount + 1;
          *(uint32_t **)(modalMenuStack + tmp_i5) = local_28;
          tmp_i3 = menuCount;
        }
        goto LAB_000fd448;
      }
      tmp_i5 = tmp_i5 + 1;
      *tmp_pu4 = *tmp_pu4 & 0xfffffffc;
      tmp_pu4 = tmp_pu4 + 0x346;
    } while (tmp_i5 < tmp_i3);
    local_20 = (uint32_t *)0x0;
LAB_000fd448:
    if (0 < tmp_i3) {
      tmp_pu6 = &Menus;
      local_24 = 0;
      do {
        if ((tmp_pu6[0xd] == 5) && (-1 < (int)tmp_pu6[0xc])) {
          (**(void **)(DC + 0xec))(tmp_pu6[0xc]);
          tmp_pu6[0xc] = 0xffffffff;
        }
        if (0 < (int)tmp_pu6[0x30]) {
          tmp_i5 = 0;
          do {
            while( true ) {
              tmp_i3 = tmp_pu6[tmp_i5 + 0x145];
              if ((*(int *)(tmp_i3 + 0x34) == 5) && (-1 < *(int *)(tmp_i3 + 0x30))) break;
              if (*(int *)(tmp_i3 + 200) != 8) goto LAB_000fd489;
LAB_000fd4e0:
              tmp_i5 = tmp_i5 + 1;
              (**(void **)(DC + 0xec))(-*(int *)(tmp_i3 + 0x3c));
              if ((int)tmp_pu6[0x30] <= tmp_i5) goto LAB_000fd500;
            }
            (**(void **)(DC + 0xec))(*(int *)(tmp_i3 + 0x30));
            *(uint32_t *)(tmp_i3 + 0x30) = 0xffffffff;
            tmp_i3 = tmp_pu6[tmp_i5 + 0x145];
            if (*(int *)(tmp_i3 + 200) == 8) goto LAB_000fd4e0;
LAB_000fd489:
            tmp_i5 = tmp_i5 + 1;
          } while (tmp_i5 < (int)tmp_pu6[0x30]);
        }
LAB_000fd500:
        local_24 = local_24 + 1;
        tmp_pu6 = tmp_pu6 + 0x346;
      } while (local_24 < menuCount);
    }
  }
  return local_20;
}

void Menus_OpenByName(uint32_t param_1)
{
  Menus_ActivateByName(param_1,1);
  return;
}

void Script_Open(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    String_Alloc(tmp_pc1);
    Menus_ActivateByName();
    return;
  }
  return;
}

void Script_ConditionalOpen(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  long tmp_l3;
  uint32_t tmp_u4;
  int tmp_i5;
  long double tmp_l6;
  uint32_t local_420;
  char local_41c [1036];
  
  local_420 = 0;
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_u2 = String_Alloc(tmp_pc1);
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_u4 = String_Alloc(tmp_pc1);
  tmp_i5 = String_Parse(param_3,&local_420);
  if (tmp_i5 == 0) {
    return;
  }
  if (tmp_l3 == 1) {
    (**(void **)(DC + 0x70))(tmp_u2,local_41c,0x400);
    if (local_41c[0] != '\0') goto LAB_000fd7a5;
  }
  else {
    tmp_l6 = (long double)(**(void **)(DC + 0x74))(tmp_u2);
    if (tmp_l6 != (long double)0) {
LAB_000fd7a5:
      Menus_ActivateByName(tmp_u4,1);
      return;
    }
  }
  Menus_ActivateByName(local_420,1);
  return;
}

void Menus_CloseByName(uint32_t param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  uint tmp_u3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  
  if (0 < menuCount) {
    tmp_pu5 = &g_unk_040f8f60;
    tmp_i4 = 0;
    do {
      tmp_i1 = Q_stricmp(*tmp_pu5,param_1);
      if (tmp_i1 == 0) {
        tmp_i1 = g_editItem;
        if (0 < (int)(&g_unk_040f9000)[tmp_i4 * 0x346]) {
          tmp_pi2 = &g_unk_040f9454 + tmp_i4 * 0x346;
          do {
            if (*tmp_pi2 == g_editItem) {
              tmp_i1 = 0;
              g_editingField = 0;
              g_editItem = 0;
            }
            tmp_pi2 = tmp_pi2 + 1;
          } while (tmp_pi2 != &Menus + (&g_unk_040f9000)[tmp_i4 * 0x346] + 0x145 + tmp_i4 * 0x346);
        }
        g_editItem = tmp_i1;
        (&g_unk_040f9008)[tmp_i4 * 0x346] = 0xffffffff;
        Menu_ClearFocus(&Menus + tmp_i4 * 0x346);
        tmp_u3 = (&g_unk_040f8f88)[tmp_i4 * 0x346];
        if ((tmp_u3 & 4) != 0) {
          Menu_RunCloseScript_part_10();
          tmp_u3 = (&g_unk_040f8f88)[tmp_i4 * 0x346];
        }
        (&g_unk_040f8f88)[tmp_i4 * 0x346] = tmp_u3 & 0xfffffff8;
        if ((tmp_u3 & 0x4000000) == 0) {
          return;
        }
        if (modalMenuCount < 1) {
          Com_Printf("^3WARNING: tried closing a modal window with an empty modal stack!\n");
          return;
        }
        modalMenuCount = modalMenuCount + -1;
        if (*(int *)(modalMenuStack + modalMenuCount * 4) == 0) {
          return;
        }
        Menus_ActivateByName
                  (*(uint32_t *)(*(int *)(modalMenuStack + modalMenuCount * 4) + 0x20),0);
        return;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu5 = tmp_pu5 + 0x346;
    } while (tmp_i4 < menuCount);
  }
  return;
}

void Script_Close(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    String_Alloc(tmp_pc1);
    Menus_CloseByName();
    return;
  }
  return;
}

uint32_t Item_ListBox_HandleKey(float *param_1,uint param_2,uint32_t param_3,int param_4)
{
  float *pfVar1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  float tmp_f6;
  float *pfVar7;
  int tmp_i8;
  float tmp_f9;
  
  pfVar1 = (float *)param_1[0x94];
  tmp_i4 = (**(void **)(DC + 0x90))(param_1[0x92]);
  if (param_4 == 0) {
    tmp_f9 = (float)*(int *)(DC + 0x124);
    tmp_f6 = *(float *)(DC + 0x2003c);
    if (1.3333334 < tmp_f6) {
      tmp_f2 = tmp_f6 * 0.75;
      tmp_f9 = tmp_f9 * tmp_f2;
      if (tmp_f9 <= tmp_f2 * *param_1) {
        return 0;
      }
      tmp_f3 = *param_1 + param_1[2];
      if (1.3333334 < tmp_f6) {
        tmp_f3 = tmp_f3 * tmp_f2;
      }
    }
    else {
      if (tmp_f9 <= *param_1) {
        return 0;
      }
      tmp_f3 = *param_1 + param_1[2];
    }
    if (tmp_f3 <= tmp_f9) {
      return 0;
    }
    if ((float)*(int *)(DC + 0x128) <= param_1[1]) {
      return 0;
    }
    if (param_1[1] + param_1[3] <= (float)*(int *)(DC + 0x128)) {
      return 0;
    }
    if (((uint)param_1[0x12] & 2) == 0) {
      return 0;
    }
  }
  tmp_f6 = param_1[0x94];
  tmp_i5 = (**(void **)(DC + 0x90))(param_1[0x92]);
  if (((uint)param_1[0x12] & 0x400) == 0) {
    tmp_i8 = (int)ROUND(param_1[3] / pfVar1[5]);
    if ((param_2 != 0xa1 && param_2 != 0x84) && (param_2 != 0xb8)) {
      tmp_f6 = (float)(tmp_i5 - (int)ROUND(param_1[3] / *(float *)((int)tmp_f6 + 0x14)));
      if ((int)tmp_f6 < 0) {
        tmp_f6 = 0.0;
      }
      if (((param_2 & 0xffffffef) != 0xa7) && (param_2 != 0x85)) goto LAB_000fdc04;
      if (pfVar1[0x3a] == 0.0) {
        tmp_f9 = (float)((int)pfVar1[3] + 1);
        pfVar1[3] = tmp_f9;
        tmp_f6 = *pfVar1;
        if ((int)tmp_f9 < (int)*pfVar1) {
          *pfVar1 = tmp_f9;
          tmp_f6 = tmp_f9;
        }
        if (tmp_i4 <= (int)tmp_f9) {
          tmp_f9 = (float)(tmp_i4 + -1);
          pfVar1[3] = tmp_f9;
        }
        goto LAB_000fdd39;
      }
LAB_000fde90:
      if ((int)*pfVar1 + 1 <= (int)tmp_f6) {
        *pfVar1 = (float)((int)*pfVar1 + 1);
        return 1;
      }
LAB_000fdf00:
      *pfVar1 = tmp_f6;
      return 1;
    }
    if (pfVar1[0x3a] == 0.0) {
      tmp_f6 = (float)((int)pfVar1[3] + -1);
      if ((int)tmp_f6 < 0) {
LAB_000fdf30:
        pfVar1[3] = 0.0;
        tmp_f6 = 0.0;
      }
      else {
LAB_000fdd98:
        pfVar1[3] = tmp_f6;
      }
      tmp_f9 = *pfVar1;
      if ((int)tmp_f6 < (int)*pfVar1) {
        *pfVar1 = tmp_f6;
        tmp_f9 = tmp_f6;
      }
      goto LAB_000fdcc0;
    }
LAB_000fddb0:
    tmp_f6 = (float)((int)*pfVar1 + -1);
  }
  else {
    tmp_i8 = (int)ROUND(param_1[2] / pfVar1[4]);
    if ((param_2 == 0xa3) || (param_2 == 0x86)) {
      if (pfVar1[0x3a] == 0.0) {
        tmp_f9 = (float)((int)pfVar1[3] + -1);
        if ((int)tmp_f9 < 0) {
          pfVar1[3] = 0.0;
          tmp_f9 = 0.0;
        }
        else {
          pfVar1[3] = tmp_f9;
        }
        tmp_f6 = *pfVar1;
        if ((int)tmp_f9 < (int)*pfVar1) {
          *pfVar1 = tmp_f9;
          tmp_f6 = tmp_f9;
        }
LAB_000fdd39:
        if ((int)tmp_f6 + tmp_i8 <= (int)tmp_f9) {
          *pfVar1 = (float)(((int)tmp_f9 - tmp_i8) + 1);
        }
        param_1[0x93] = tmp_f9;
        (**(void **)(DC + 0xa0))(param_1[0x92],tmp_f9);
        return 1;
      }
      goto LAB_000fddb0;
    }
    if ((param_2 == 0xa5) || (param_2 == 0x87)) {
      if (pfVar1[0x3a] != 0.0) {
        tmp_f6 = (float)((int)*pfVar1 + 1);
        if (tmp_i4 <= (int)tmp_f6) {
          *pfVar1 = (float)(tmp_i4 + -1);
          return 1;
        }
        goto LAB_000fddb5;
      }
      tmp_f9 = *pfVar1;
      tmp_f6 = (float)((int)pfVar1[3] + 1);
      pfVar1[3] = tmp_f6;
      if ((int)tmp_f6 < (int)tmp_f9) {
LAB_000fdca0:
        *pfVar1 = tmp_f6;
        tmp_f9 = tmp_f6;
      }
LAB_000fdca4:
      if (tmp_i4 <= (int)tmp_f6) {
        tmp_f6 = (float)(tmp_i4 + -1);
        pfVar1[3] = tmp_f6;
      }
LAB_000fdcc0:
      if ((int)tmp_f9 + tmp_i8 <= (int)tmp_f6) {
        *pfVar1 = (float)(((int)tmp_f6 - tmp_i8) + 1);
      }
      param_1[0x93] = tmp_f6;
      (**(void **)(DC + 0xa0))(param_1[0x92],tmp_f6);
      return 1;
    }
    tmp_f6 = (float)(tmp_i5 - (int)ROUND(param_1[2] / *(float *)((int)tmp_f6 + 0x10)));
    if ((int)tmp_f6 < 0) {
      tmp_f6 = 0.0;
    }
LAB_000fdc04:
    if (1 < param_2 - 0xb2) {
      if ((param_2 == 0xa0) || (param_2 == 0x8f)) goto LAB_000fddd0;
      if ((param_2 == 0xa6) || (param_2 == 0x90)) goto LAB_000fdf00;
      if ((param_2 == 0xa2) || (param_2 == 0x8e)) {
        if (pfVar1[0x3a] == 0.0) {
          tmp_f6 = (float)((int)pfVar1[3] - tmp_i8);
          if (-1 < (int)tmp_f6) goto LAB_000fdd98;
          goto LAB_000fdf30;
        }
        goto LAB_000fddc8;
      }
      if ((param_2 != 0xa8) && (param_2 != 0x8d)) {
        return 0;
      }
      if (pfVar1[0x3a] != 0.0) {
        tmp_f9 = (float)(tmp_i8 + (int)*pfVar1);
        if ((int)tmp_f9 <= (int)tmp_f6) goto LAB_000fdf5a;
        goto LAB_000fddb5;
      }
      tmp_f6 = (float)((int)pfVar1[3] + tmp_i8);
      pfVar1[3] = tmp_f6;
      tmp_f9 = *pfVar1;
      if ((int)tmp_f6 < (int)*pfVar1) goto LAB_000fdca0;
      goto LAB_000fdca4;
    }
    Item_ListBox_MouseEnter(param_1,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128),1);
    tmp_f9 = param_1[0x12];
    if (((uint)tmp_f9 & 0x800) != 0) goto LAB_000fddb0;
    if (((uint)tmp_f9 & 0x1000) != 0) goto LAB_000fde90;
    if (((uint)tmp_f9 & 0x4000) == 0) {
      if (((uint)tmp_f9 & 0x8000) == 0) {
        if (((uint)tmp_f9 & 0x40002000) != 0) {
          return 1;
        }
        if (tmp_i4 <= (int)pfVar1[3]) {
          pfVar1[3] = (float)(tmp_i4 + -1);
        }
        if (((param_1[0x93] == pfVar1[3]) && (*(int *)(DC + 0x11c) < lastListBoxClickTime)) &&
           (pfVar1[0x38] != 0.0)) {
          Item_RunScript_constprop_37();
        }
        tmp_i4 = DC;
        lastListBoxClickTime = *(int *)(DC + 0x11c) + 300;
        tmp_f6 = pfVar1[3];
        if (param_1[0x93] != tmp_f6) {
          param_1[0x93] = tmp_f6;
          (**(void **)(tmp_i4 + 0xa0))(param_1[0x92],tmp_f6);
        }
        if (param_2 == 0xb2) {
          (**(void **)(DC + 0xa4))(param_1);
          return 1;
        }
        if (pfVar1[0x39] == 0.0) {
          return 1;
        }
        pfVar7 = (float *)Menus_FindByName(pfVar1[0x39]);
        if (pfVar7 == (float *)0x0) {
          return 1;
        }
        *pfVar7 = (float)*(int *)(DC + 0x124);
        pfVar7[1] = (float)*(int *)(DC + 0x128);
        Menu_UpdatePosition(pfVar7);
        Menus_ActivateByName(pfVar1[0x39],1);
        return 1;
      }
      tmp_f9 = (float)(tmp_i8 + (int)*pfVar1);
      if ((int)tmp_f9 <= (int)tmp_f6) {
LAB_000fdf5a:
        *pfVar1 = tmp_f9;
        return 1;
      }
      goto LAB_000fdf00;
    }
LAB_000fddc8:
    tmp_f6 = (float)((int)*pfVar1 - tmp_i8);
  }
  if (-1 < (int)tmp_f6) {
LAB_000fddb5:
    *pfVar1 = tmp_f6;
    return 1;
  }
LAB_000fddd0:
  *pfVar1 = 0.0;
  return 1;
}

void Scroll_ListBox_ThumbFunc(int *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  int *tmp_pi4;
  float tmp_f5;
  int tmp_i6;
  int tmp_i7;
  
  pfVar3 = (float *)param_1[6];
  tmp_pi4 = (int *)pfVar3[0x94];
  if ((*(byte *)((int)pfVar3 + 0x49) & 4) == 0) {
    tmp_i6 = DC;
    if ((float)*(int *)(DC + 0x128) != (float)param_1[5]) {
      tmp_f1 = pfVar3[1];
      tmp_f2 = pfVar3[3];
      tmp_i6 = (**(void **)(DC + 0x90))(pfVar3[0x92]);
      if ((*(byte *)((int)pfVar3 + 0x49) & 4) == 0) {
        tmp_f5 = pfVar3[3] / (float)tmp_pi4[5];
      }
      else {
        tmp_f5 = pfVar3[2] / (float)tmp_pi4[4];
      }
      tmp_i6 = tmp_i6 - (int)ROUND(tmp_f5);
      if (tmp_i6 < 0) {
        tmp_i6 = 0;
      }
      tmp_i7 = (int)ROUND(((float)tmp_i6 *
                         (((float)*(int *)(DC + 0x128) - (tmp_f1 + 16.0 + 1.0)) - 8.0)) /
                         (((tmp_f2 - 32.0) - 2.0) - 16.0));
      if (tmp_i7 < 0) {
        tmp_i7 = 0;
      }
      else if (tmp_i6 < tmp_i7) {
        tmp_i7 = tmp_i6;
      }
      *tmp_pi4 = tmp_i7;
      tmp_i6 = DC;
      param_1[5] = (int)(float)*(int *)(DC + 0x128);
    }
    tmp_i6 = *(int *)(tmp_i6 + 0x11c);
    if (tmp_i6 <= *param_1) goto LAB_000fe225;
  }
  else {
    if ((float)*(int *)(DC + 0x124) == (float)param_1[4]) {
      return;
    }
    tmp_f1 = *pfVar3;
    tmp_f2 = pfVar3[2];
    tmp_i6 = (**(void **)(DC + 0x90))(pfVar3[0x92]);
    if ((*(byte *)((int)pfVar3 + 0x49) & 4) == 0) {
      tmp_f5 = pfVar3[3] / (float)tmp_pi4[5];
    }
    else {
      tmp_f5 = pfVar3[2] / (float)tmp_pi4[4];
    }
    tmp_i6 = tmp_i6 - (int)ROUND(tmp_f5);
    if (tmp_i6 < 0) {
      tmp_i6 = 0;
    }
    tmp_i7 = (int)ROUND(((float)tmp_i6 * (((float)*(int *)(DC + 0x124) - (tmp_f1 + 16.0 + 1.0)) - 8.0))
                       / (((tmp_f2 - 32.0) - 2.0) - 16.0));
    if (tmp_i7 < 0) {
      tmp_i7 = 0;
    }
    else if (tmp_i6 < tmp_i7) {
      tmp_i7 = tmp_i6;
    }
    *tmp_pi4 = tmp_i7;
    tmp_i6 = DC;
    param_1[4] = (int)(float)*(int *)(DC + 0x124);
    tmp_i6 = *(int *)(tmp_i6 + 0x11c);
    if (tmp_i6 <= *param_1) goto LAB_000fe225;
  }
  lastListBoxClickTime = 0;
  Item_ListBox_HandleKey(param_1[6],param_1[3],1,0);
  *param_1 = param_1[2] + *(int *)(DC + 0x11c);
  tmp_i6 = *(int *)(DC + 0x11c);
LAB_000fe225:
  if (param_1[1] < tmp_i6) {
    param_1[1] = tmp_i6 + 0x96;
    if (0x14 < param_1[2]) {
      param_1[2] = param_1[2] + -0x28;
    }
  }
  return;
}

void Scroll_ListBox_AutoFunc(int *param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(DC + 0x11c);
  if (*param_1 < tmp_i1) {
    Item_ListBox_HandleKey(param_1[6],param_1[3],1,0);
    *param_1 = param_1[2] + *(int *)(DC + 0x11c);
    tmp_i1 = *(int *)(DC + 0x11c);
  }
  if (param_1[1] < tmp_i1) {
    param_1[1] = tmp_i1 + 0x96;
    if (0x14 < param_1[2]) {
      param_1[2] = param_1[2] + -0x28;
    }
  }
  return;
}

uint32_t Item_HandleKey(float *param_1,uint param_2,int param_3)
{
  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  void *tmp_pc4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  uint32_t tmp_u9;
  uint tmp_u10;
  
  tmp_u10 = param_2 & 0xfffffbff;
  if ((param_2 & 0x400) == 0) {
    tmp_u10 = param_2;
  }
  if (itemCapture == 0) {
    if (param_3 == 0) {
      return 0;
    }
    if (tmp_u10 - 0xb2 < 3) {
      Item_StartCapture(param_1,param_2);
    }
  }
  else {
    itemCapture = 0;
    captureFunc = 0;
    captureData = 0;
    if (param_3 == 0) {
      itemCapture = 0;
      captureData = 0;
      captureFunc = 0;
      return 0;
    }
  }
  if (tmp_u10 != 0x1b) {
    if ((tmp_u10 == 0xd) && (param_1[0x9b] != 0.0)) {
LAB_000fe55e:
      Item_RunScript_constprop_37();
      return 1;
    }
    switch(param_1[0x32]) {
    case 4.2039e-45:
    case 2.24208e-44:
_L4836:
      tmp_u9 = Item_CheckBox_HandleKey();
      return tmp_u9;
    default:
      break;
    case 8.40779e-45:
_L4838:
      tmp_u9 = Item_ListBox_HandleKey(param_1,param_2,param_3,0);
      return tmp_u9;
    case 1.12104e-44:
_L4839:
      if (*(void **)(DC + 0x8c) != (void *)0x0) {
        tmp_u9 = (**(void **)(DC + 0x8c))(param_1[0xf],param_1[0x10],param_1 + 0x92,param_2);
        return tmp_u9;
      }
      break;
    case 1.4013e-44:
_L4840:
      if ((((uint)param_1[0x12] & 2) != 0) && (param_1[0x45] != 0.0)) {
        tmp_f8 = (float)*(int *)(DC + 0x124);
        tmp_f1 = *(float *)(DC + 0x2003c);
        if (tmp_f1 <= 1.3333334) {
          tmp_f2 = *param_1;
          if (tmp_f8 <= tmp_f2) {
            return 0;
          }
          tmp_f6 = param_1[2] + tmp_f2;
          tmp_f7 = tmp_f8;
        }
        else {
          tmp_f5 = tmp_f1 * 0.75;
          tmp_f7 = tmp_f8 * tmp_f5;
          tmp_f2 = *param_1;
          if (tmp_f7 <= tmp_f5 * tmp_f2) {
            return 0;
          }
          tmp_f6 = param_1[2] + tmp_f2;
          if (1.3333334 < tmp_f1) {
            tmp_f6 = tmp_f6 * tmp_f5;
          }
        }
        if (tmp_f7 < tmp_f6) {
          if ((((param_1[1] < (float)*(int *)(DC + 0x128)) &&
               ((float)*(int *)(DC + 0x128) < param_1[1] + param_1[3])) &&
              ((param_2 - 0xb2 < 3 || (param_2 == 0xd)))) &&
             (pfVar3 = (float *)param_1[0x94], pfVar3 != (float *)0x0)) {
            if (param_1[0x3a] != 0.0) {
              tmp_f2 = param_1[0x2e] + param_1[0x30] + 8.0;
            }
            tmp_f6 = tmp_f2 - 6.0;
            tmp_f7 = tmp_f6;
            tmp_f5 = tmp_f8;
            if (1.3333334 < tmp_f1) {
              tmp_f7 = tmp_f1 * 0.75 * tmp_f6;
              tmp_f5 = tmp_f8 * tmp_f1 * 0.75;
            }
            if (tmp_f7 < tmp_f5) {
              tmp_f6 = tmp_f6 + 102.0;
              if (1.3333334 < tmp_f1) {
                tmp_f6 = tmp_f1 * 0.75 * tmp_f6;
              }
              if (tmp_f5 < tmp_f6) {
                tmp_pc4 = *(void **)(DC + 0x78);
                tmp_u9 = va(&g_unk_0011e95f,
                           (double)(*pfVar3 + (pfVar3[1] - *pfVar3) * ((tmp_f8 - tmp_f2) / 96.0)));
                (*tmp_pc4)(param_1[0x45],tmp_u9);
                return 1;
              }
            }
          }
        }
      }
      break;
    case 1.54143e-44:
_L4841:
      tmp_u9 = Item_YesNo_HandleKey();
      return tmp_u9;
    case 1.68156e-44:
_L4842:
      tmp_u9 = Item_Multi_HandleKey();
      return tmp_u9;
    case 1.82169e-44:
_L4843:
      tmp_u9 = Item_Bind_HandleKey();
      return tmp_u9;
    }
LAB_000fe532:
    return 0;
  }
  if (param_1[0x9a] != 0.0) goto LAB_000fe55e;
  switch(param_1[0x32]) {
  case 4.2039e-45:
  case 2.24208e-44:
    goto _L4836;
  default:
    goto LAB_000fe532;
  case 8.40779e-45:
    goto _L4838;
  case 1.12104e-44:
    goto _L4839;
  case 1.4013e-44:
    goto _L4840;
  case 1.54143e-44:
    goto _L4841;
  case 1.68156e-44:
    goto _L4842;
  case 1.82169e-44:
    goto _L4843;
  }
}

void Menu_ScrollFeeder(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  
  if ((param_1 != 0) && (0 < *(int *)(param_1 + 0xc0))) {
    tmp_i2 = *(int *)(param_1 + 0x514);
    if (*(float *)(tmp_i2 + 0x248) != (float)param_2) {
      tmp_i1 = 0;
      do {
        tmp_i1 = tmp_i1 + 1;
        if (tmp_i1 == *(int *)(param_1 + 0xc0)) {
          return;
        }
        tmp_i2 = *(int *)(param_1 + 0x514 + tmp_i1 * 4);
      } while (*(float *)(tmp_i2 + 0x248) != (float)param_2);
    }
    Item_ListBox_HandleKey(tmp_i2,0x85 - (uint)(param_3 == 0),1,1);
    return;
  }
  return;
}

void Item_Init(uint16_t *param_1)
{
  uint tmp_u1;
  uint32_t *tmp_pu2;
  uint16_t *tmp_pu3;
  uint tmp_u4;
  bool tmp_b5;
  
  tmp_u4 = 0x278;
  tmp_b5 = false;
  if (((uint)param_1 & 1) == 0) {
    tmp_pu3 = param_1;
    if (((uint)param_1 & 2) == 0) goto LAB_000fe97b;
  }
  else {
    tmp_pu3 = (uint16_t *)((int)param_1 + 1);
    tmp_u4 = 0x277;
    tmp_b5 = true;
    *(uint8_t *)param_1 = 0;
    if (((uint)tmp_pu3 & 2) == 0) goto LAB_000fe97b;
    tmp_u4 = 0x277;
    tmp_b5 = true;
  }
  *tmp_pu3 = 0;
  tmp_u4 = tmp_u4 - 2;
  tmp_pu3 = tmp_pu3 + 1;
LAB_000fe97b:
  tmp_u1 = 0;
  do {
    *(uint32_t *)((int)tmp_pu3 + tmp_u1) = 0;
    *(uint32_t *)((int)tmp_pu3 + tmp_u1 + 4) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < (tmp_u4 & 0xfffffff8));
  tmp_pu2 = (uint32_t *)((int)tmp_pu3 + tmp_u1);
  if ((tmp_u4 & 4) != 0) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + 1;
  }
  if ((tmp_u4 & 2) != 0) {
    *(uint16_t *)tmp_pu2 = 0;
    tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
  }
  if (tmp_b5) {
    *(uint8_t *)tmp_pu2 = 0;
  }
  tmp_b5 = ((uint)param_1 & 1) != 0;
  tmp_u4 = 0xb8;
  *(uint32_t *)(param_1 + 0x13a) = 0;
  *(uint32_t *)(param_1 + 0x6e) = 0x3f0ccccd;
  *(uint32_t *)(param_1 + 0x12a) = 0xffffffff;
  tmp_pu3 = param_1;
  if (tmp_b5) {
    *(uint8_t *)param_1 = 0;
    tmp_pu3 = (uint16_t *)((int)param_1 + 1);
    tmp_u4 = 0xb7;
  }
  if (((uint)tmp_pu3 & 2) != 0) {
    *tmp_pu3 = 0;
    tmp_u4 = tmp_u4 - 2;
    tmp_pu3 = tmp_pu3 + 1;
  }
  tmp_u1 = 0;
  do {
    *(uint32_t *)((int)tmp_pu3 + tmp_u1) = 0;
    *(uint32_t *)((int)tmp_pu3 + tmp_u1 + 4) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < (tmp_u4 & 0xfffffff8));
  tmp_pu2 = (uint32_t *)((int)tmp_pu3 + tmp_u1);
  if ((tmp_u4 & 4) != 0) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + 1;
  }
  if ((tmp_u4 & 2) != 0) {
    *(uint16_t *)tmp_pu2 = 0;
    tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
  }
  if (tmp_b5) {
    *(uint8_t *)tmp_pu2 = 0;
  }
  *(uint32_t *)(param_1 + 0x22) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x40) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x3e) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x3c) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x3a) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x18) = 0xffffffff;
  return;
}

void Menu_HandleMouseMove(int param_1,float param_2,float param_3)
{
  uint *tmp_pu1;
  byte tmp_b2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  bool tmp_b7;
  int tmp_i8;
  uint32_t tmp_u9;
  int tmp_i10;
  float *pfVar11;
  int *tmp_pi12;
  int local_20;
  
  if ((param_1 != 0) && ((*(uint *)(param_1 + 0x48) & 0x100004) != 0)) {
    if (itemCapture == 0) {
      if ((g_waitingForKey == 0) && (g_editingField == 0)) {
        tmp_i8 = *(int *)(param_1 + 0xc0);
        local_20 = 0;
        tmp_b7 = false;
        while (tmp_i8 < 1) {
LAB_000fede8:
          if (tmp_b7) {
            return;
          }
          tmp_b7 = true;
        }
        tmp_pi12 = (int *)(param_1 + 0x514);
        tmp_i10 = 1;
        do {
          pfVar11 = (float *)*tmp_pi12;
          if (((uint)pfVar11[0x12] & 0x100004) == 0) {
LAB_000fec70:
            tmp_i8 = *(int *)(param_1 + 0xc0);
            if (tmp_i8 <= tmp_i10) goto LAB_000fede8;
          }
          else {
            tmp_f3 = pfVar11[0x48];
            if (((uint)tmp_f3 & 3) != 0) {
              tmp_i8 = Item_EnableShowViaCvar(pfVar11,1);
              if (tmp_i8 == 0) goto LAB_000fec70;
              pfVar11 = (float *)*tmp_pi12;
              tmp_f3 = pfVar11[0x48];
            }
            if (((uint)tmp_f3 & 0xc) == 0) {
              tmp_b2 = *(byte *)(pfVar11 + 0x98);
            }
            else {
              tmp_i8 = Item_EnableShowViaCvar(pfVar11,4);
              if (tmp_i8 == 0) goto LAB_000fec70;
              pfVar11 = (float *)*tmp_pi12;
              tmp_b2 = *(byte *)(pfVar11 + 0x98);
            }
            if ((tmp_b2 & 3) == 0) {
              tmp_f3 = pfVar11[0x99];
            }
            else {
              tmp_i8 = Item_SettingShow_constprop_35();
              if (tmp_i8 == 0) goto LAB_000fec70;
              pfVar11 = (float *)*tmp_pi12;
              tmp_f3 = pfVar11[0x99];
            }
            if (tmp_f3 != 0.0) {
              tmp_i8 = Item_SettingShow_constprop_36();
              if (tmp_i8 == 0) goto LAB_000fec70;
              pfVar11 = (float *)*tmp_pi12;
            }
            if (pfVar11 == (float *)0x0) {
LAB_000fec60:
              if (((uint)pfVar11[0x12] & 1) != 0) {
                if (((uint)pfVar11[0x12] & 0x80) != 0) {
                  Item_RunScript_constprop_37();
                  pfVar11[0x12] = (float)((uint)pfVar11[0x12] & 0xffffff7f);
                }
                Item_RunScript_constprop_37();
                pfVar11[0x12] = (float)((uint)pfVar11[0x12] & 0xffffe7ff);
                if (*tmp_pi12 != 0) {
                  tmp_pu1 = (uint *)(*tmp_pi12 + 0x48);
                  *tmp_pu1 = *tmp_pu1 & 0xfffffffe;
                }
              }
              goto LAB_000fec70;
            }
            tmp_f3 = *(float *)(DC + 0x2003c);
            if (tmp_f3 <= 1.3333334) {
              if (*pfVar11 < param_2) {
                tmp_f6 = *pfVar11 + pfVar11[2];
                tmp_f5 = param_2;
                goto LAB_000fec12;
              }
              goto LAB_000fec60;
            }
            tmp_f4 = tmp_f3 * 0.75;
            tmp_f5 = param_2 * tmp_f4;
            if (tmp_f5 <= tmp_f4 * *pfVar11) goto LAB_000fec60;
            tmp_f6 = *pfVar11 + pfVar11[2];
            if (1.3333334 < tmp_f3) {
              tmp_f6 = tmp_f4 * tmp_f6;
            }
LAB_000fec12:
            if (((tmp_f6 <= tmp_f5) || (param_3 <= pfVar11[1])) ||
               (pfVar11[1] + pfVar11[3] <= param_3)) goto LAB_000fec60;
            if (!tmp_b7) goto LAB_000fec70;
            if ((pfVar11[0x32] == 0.0) && (pfVar11[0x3a] != 0.0)) {
              tmp_u9 = Item_CorrectedTextRect();
              tmp_i8 = Rect_ContainsPoint(tmp_u9,param_2,param_3);
              if (tmp_i8 != 0) goto LAB_000fedc8;
            }
            else {
LAB_000fedc8:
              if ((((uint)pfVar11[0x12] & 0x24) == 4) &&
                 (Item_MouseEnter(pfVar11,param_2,param_3), local_20 == 0)) {
                local_20 = Item_SetFocus(pfVar11,param_2,param_3);
              }
            }
            if (*(int *)(param_1 + 0xc0) <= tmp_i10) {
              return;
            }
          }
          tmp_pi12 = tmp_pi12 + 1;
          tmp_i10 = tmp_i10 + 1;
        } while( true );
      }
    }
    else if ((*(int *)(itemCapture + 200) == 6) &&
            (tmp_i8 = Rect_ContainsPoint(itemCapture,param_2,param_3), tmp_i8 == 0)) {
      itemCapture = 0;
      captureFunc = 0;
      captureData = 0;
    }
  }
  return;
}

uint32_t Menu_SetPrevCursorItem(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  float *pfVar5;
  float tmp_f6;
  float tmp_f7;
  bool tmp_b8;
  int tmp_i9;
  int tmp_i10;
  uint tmp_u11;
  int tmp_i12;
  int tmp_i13;
  int tmp_i14;
  
  tmp_i13 = *(int *)(param_1 + 200);
  if (tmp_i13 < 0) {
    tmp_b8 = true;
    tmp_i10 = *(int *)(param_1 + 0xc0) + -1;
    *(int *)(param_1 + 200) = tmp_i10;
  }
  else {
    tmp_b8 = false;
    tmp_i10 = tmp_i13;
  }
LAB_000fef10:
  do {
    if (tmp_i10 < 0) {
LAB_000ff180:
      *(int *)(param_1 + 200) = tmp_i13;
      return 0;
    }
    tmp_i10 = tmp_i10 + -1;
    *(int *)(param_1 + 200) = tmp_i10;
    if (tmp_i10 == -1) {
      if (tmp_b8) goto LAB_000ff180;
      tmp_i10 = *(int *)(param_1 + 0xc0) + -1;
      *(int *)(param_1 + 200) = tmp_i10;
      if (tmp_i10 < 0) goto LAB_000ff180;
      tmp_b8 = true;
    }
    tmp_i9 = DC;
    tmp_i3 = *(int *)(param_1 + 0x514 + tmp_i10 * 4);
    tmp_i14 = *(int *)(DC + 0x128);
    tmp_i4 = *(int *)(DC + 0x124);
  } while ((tmp_i3 == 0) || ((*(uint *)(tmp_i3 + 0x48) & 0x16) != 4));
  tmp_i10 = *(int *)(tmp_i3 + 0xec);
  tmp_u11 = *(uint *)(tmp_i3 + 0x120);
  if ((tmp_u11 & 3) == 0) {
LAB_000fef70:
    if (((tmp_u11 & 0xc) == 0) || (tmp_i12 = Item_EnableShowViaCvar(tmp_i3,4), tmp_i12 != 0)) {
      if (((*(byte *)(tmp_i3 + 0x260) & 3) != 0) &&
         (tmp_i12 = Item_SettingShow_constprop_35(), tmp_i12 == 0)) {
        tmp_i10 = *(int *)(param_1 + 200);
        goto LAB_000fef10;
      }
      if ((*(int *)(tmp_i3 + 0x264) == 0) || (tmp_i12 = Item_SettingShow_constprop_36(), tmp_i12 != 0))
      {
        tmp_i12 = Menu_ClearFocus(*(uint32_t *)(tmp_i3 + 0xec));
        tmp_i13 = DC;
        if (*(int *)(tmp_i3 + 200) == 0) {
          tmp_f6 = (float)tmp_i4;
          tmp_f1 = *(float *)(tmp_i3 + 0xb8);
          tmp_f2 = *(float *)(DC + 0x2003c);
          if (tmp_f2 <= 1.3333334) {
            if (tmp_f1 < tmp_f6) {
LAB_000ff0ff:
              if (tmp_f6 < tmp_f1 + *(float *)(tmp_i3 + 0xc0)) {
LAB_000ff115:
                tmp_f1 = *(float *)(tmp_i3 + 0xbc) - *(float *)(tmp_i3 + 0xc4);
                if ((tmp_f1 < (float)tmp_i14) && ((float)tmp_i14 < tmp_f1 + *(float *)(tmp_i3 + 0xc4))) {
                  tmp_i14 = *(int *)(tmp_i3 + 0x124);
                  *(uint *)(tmp_i3 + 0x48) = *(uint *)(tmp_i3 + 0x48) | 2;
                  if (tmp_i14 == 0) {
                    tmp_i14 = *(int *)(tmp_i9 + 0x1e320);
                  }
                  goto LAB_000ff217;
                }
              }
            }
          }
          else {
            tmp_f7 = tmp_f2 * 0.75;
            tmp_f6 = tmp_f6 * tmp_f7;
            if (tmp_f7 * tmp_f1 < tmp_f6) {
              if (tmp_f2 <= 1.3333334) goto LAB_000ff0ff;
              if (tmp_f6 < (tmp_f1 + *(float *)(tmp_i3 + 0xc0)) * tmp_f7) goto LAB_000ff115;
            }
          }
          if ((tmp_i12 != 0) &&
             (*(uint *)(tmp_i12 + 0x48) = *(uint *)(tmp_i12 + 0x48) | 2, *(int *)(tmp_i12 + 0x10c) != 0
             )) {
            Item_RunScript_constprop_37();
          }
        }
        else {
          *(uint *)(tmp_i3 + 0x48) = *(uint *)(tmp_i3 + 0x48) | 2;
          if (*(int *)(tmp_i3 + 0x10c) != 0) {
            Item_RunScript_constprop_37();
          }
          tmp_i14 = *(int *)(tmp_i3 + 0x124);
          tmp_i13 = DC;
          if (tmp_i14 == 0) {
            tmp_i14 = *(int *)(tmp_i9 + 0x1e320);
          }
LAB_000ff217:
          (**(void **)(tmp_i13 + 0x88))(tmp_i14,6);
        }
        if (*(int *)(tmp_i10 + 0xc0) < 1) goto LAB_000ff0aa;
        tmp_i13 = 0;
        if (tmp_i3 == *(int *)(tmp_i10 + 0x514)) goto LAB_000ff240;
        goto LAB_000ff0a5;
      }
    }
  }
  else {
    tmp_i12 = Item_EnableShowViaCvar(tmp_i3,1);
    if (tmp_i12 != 0) {
      tmp_u11 = *(uint *)(tmp_i3 + 0x120);
      goto LAB_000fef70;
    }
  }
  tmp_i10 = *(int *)(param_1 + 200);
  goto LAB_000fef10;
  while (tmp_i3 != *(int *)(tmp_i10 + 0x514 + tmp_i13 * 4)) {
LAB_000ff0a5:
    tmp_i13 = tmp_i13 + 1;
    if (tmp_i13 == *(int *)(tmp_i10 + 0xc0)) goto LAB_000ff0aa;
  }
LAB_000ff240:
  *(int *)(tmp_i10 + 200) = tmp_i13;
LAB_000ff0aa:
  pfVar5 = *(float **)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
  Menu_HandleMouseMove(param_1,*pfVar5 + 1.0,pfVar5[1] + 1.0);
  return *(uint32_t *)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
}

uint32_t Menu_SetNextCursorItem(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  float *pfVar6;
  float tmp_f7;
  float tmp_f8;
  int tmp_i9;
  int tmp_i10;
  uint tmp_u11;
  int tmp_i12;
  int tmp_i13;
  bool tmp_b14;
  
  if (param_1 == 0) {
    return 0;
  }
  tmp_i13 = *(int *)(param_1 + 200);
  tmp_b14 = tmp_i13 == -1;
  tmp_i10 = tmp_i13;
  if (tmp_b14) {
    *(uint32_t *)(param_1 + 200) = 0;
    tmp_i10 = 0;
  }
  tmp_i12 = *(int *)(param_1 + 0xc0);
  while (tmp_i10 < tmp_i12) {
    while( true ) {
      tmp_i10 = tmp_i10 + 1;
      *(int *)(param_1 + 200) = tmp_i10;
      if (tmp_i12 <= tmp_i10) {
        if (tmp_b14) {
          return *(uint32_t *)(param_1 + 0x514 + tmp_i13 * 4);
        }
        *(uint32_t *)(param_1 + 200) = 0;
        tmp_i10 = 0;
        tmp_b14 = true;
      }
      tmp_i9 = DC;
      tmp_i3 = *(int *)(DC + 0x128);
      tmp_i4 = *(int *)(DC + 0x124);
      tmp_i5 = *(int *)(param_1 + 0x514 + tmp_i10 * 4);
      if ((tmp_i5 == 0) || ((*(uint *)(tmp_i5 + 0x48) & 0x16) != 4)) break;
      tmp_u11 = *(uint *)(tmp_i5 + 0x120);
      tmp_i10 = *(int *)(tmp_i5 + 0xec);
      if ((tmp_u11 & 3) == 0) {
LAB_000ff3a6:
        if (((tmp_u11 & 0xc) != 0) && (tmp_i12 = Item_EnableShowViaCvar(tmp_i5,4), tmp_i12 == 0))
        goto LAB_000ff5a1;
        if (((*(byte *)(tmp_i5 + 0x260) & 3) == 0) ||
           (tmp_i12 = Item_SettingShow_constprop_35(), tmp_i12 != 0)) {
          if ((*(int *)(tmp_i5 + 0x264) != 0) &&
             (tmp_i12 = Item_SettingShow_constprop_36(), tmp_i12 == 0)) goto LAB_000ff5a1;
          tmp_i12 = Menu_ClearFocus(*(uint32_t *)(tmp_i5 + 0xec));
          tmp_i13 = DC;
          if (*(int *)(tmp_i5 + 200) == 0) {
            tmp_f7 = (float)tmp_i4;
            tmp_f1 = *(float *)(tmp_i5 + 0xb8);
            tmp_f2 = *(float *)(DC + 0x2003c);
            if (tmp_f2 <= 1.3333334) {
              if (tmp_f1 < tmp_f7) {
LAB_000ff52f:
                if (tmp_f7 < tmp_f1 + *(float *)(tmp_i5 + 0xc0)) {
LAB_000ff545:
                  tmp_f1 = *(float *)(tmp_i5 + 0xbc) - *(float *)(tmp_i5 + 0xc4);
                  if ((tmp_f1 < (float)tmp_i3) && ((float)tmp_i3 < tmp_f1 + *(float *)(tmp_i5 + 0xc4))) {
                    tmp_i12 = *(int *)(tmp_i5 + 0x124);
                    *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) | 2;
                    if (tmp_i12 == 0) {
                      tmp_i12 = *(int *)(tmp_i9 + 0x1e320);
                    }
                    goto LAB_000ff637;
                  }
                }
              }
            }
            else {
              tmp_f8 = tmp_f2 * 0.75;
              tmp_f7 = tmp_f7 * tmp_f8;
              if (tmp_f8 * tmp_f1 < tmp_f7) {
                if (tmp_f2 <= 1.3333334) goto LAB_000ff52f;
                if (tmp_f7 < (tmp_f1 + *(float *)(tmp_i5 + 0xc0)) * tmp_f8) goto LAB_000ff545;
              }
            }
            if ((tmp_i12 != 0) &&
               (*(uint *)(tmp_i12 + 0x48) = *(uint *)(tmp_i12 + 0x48) | 2,
               *(int *)(tmp_i12 + 0x10c) != 0)) {
              Item_RunScript_constprop_37();
            }
          }
          else {
            *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) | 2;
            if (*(int *)(tmp_i5 + 0x10c) != 0) {
              Item_RunScript_constprop_37();
            }
            tmp_i12 = *(int *)(tmp_i5 + 0x124);
            tmp_i13 = DC;
            if (tmp_i12 == 0) {
              tmp_i12 = *(int *)(tmp_i9 + 0x1e320);
            }
LAB_000ff637:
            (**(void **)(tmp_i13 + 0x88))(tmp_i12,6);
          }
          if (*(int *)(tmp_i10 + 0xc0) < 1) goto LAB_000ff4da;
          tmp_i12 = 0;
          tmp_i13 = *(int *)(tmp_i10 + 0x514);
          goto joined_r0x000ff4bb;
        }
        tmp_i10 = *(int *)(param_1 + 200);
        tmp_i12 = *(int *)(param_1 + 0xc0);
      }
      else {
        tmp_i12 = Item_EnableShowViaCvar(tmp_i5,1);
        if (tmp_i12 != 0) {
          tmp_u11 = *(uint *)(tmp_i5 + 0x120);
          goto LAB_000ff3a6;
        }
LAB_000ff5a1:
        tmp_i10 = *(int *)(param_1 + 200);
        tmp_i12 = *(int *)(param_1 + 0xc0);
      }
      if (tmp_i12 <= tmp_i10) goto LAB_000ff5c0;
    }
  }
LAB_000ff5c0:
  *(int *)(param_1 + 200) = tmp_i13;
  return 0;
joined_r0x000ff4bb:
  if (tmp_i5 == tmp_i13) {
    *(int *)(tmp_i10 + 200) = tmp_i12;
LAB_000ff4da:
    pfVar6 = *(float **)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
    Menu_HandleMouseMove(param_1,*pfVar6 + 1.0,pfVar6[1] + 1.0);
    return *(uint32_t *)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
  }
  tmp_i12 = tmp_i12 + 1;
  if (tmp_i12 == *(int *)(tmp_i10 + 0xc0)) goto LAB_000ff4da;
  tmp_i13 = *(int *)(tmp_i10 + 0x514 + tmp_i12 * 4);
  goto joined_r0x000ff4bb;
}

bool Item_TextField_HandleKey(int param_1,uint param_2)
{
  int tmp_i1;
  int tmp_i2;
  void *tmp_pc3;
  float *pfVar4;
  bool tmp_b5;
  uint tmp_u6;
  uint *tmp_pu7;
  uint *tmp_pu8;
  int tmp_i9;
  int tmp_i10;
  uint tmp_u11;
  uint8_t uStack_41d;
  uint32_t local_41c;
  uint32_t auStack_418 [258];
  
  tmp_i10 = *(int *)(param_1 + 0x114);
  tmp_i2 = *(int *)(param_1 + 0x250);
  if (tmp_i10 == 0) {
    return false;
  }
  tmp_u6 = 0;
  do {
    *(uint32_t *)((int)&local_41c + tmp_u6) = 0;
    *(uint32_t *)((int)auStack_418 + tmp_u6) = 0;
    tmp_u6 = tmp_u6 + 8;
  } while (tmp_u6 < 0x400);
  (**(void **)(DC + 0x70))(tmp_i10,&local_41c,0x400);
  tmp_pu8 = &local_41c;
  do {
    tmp_pu7 = tmp_pu8;
    tmp_u11 = *tmp_pu7 + 0xfefefeff & ~*tmp_pu7;
    tmp_u6 = tmp_u11 & 0x80808080;
    tmp_pu8 = tmp_pu7 + 1;
  } while (tmp_u6 == 0);
  if ((tmp_u11 & 0x8080) == 0) {
    tmp_pu8 = (uint *)((int)tmp_pu7 + 6);
    tmp_u6 = tmp_u6 >> 0x10;
  }
  tmp_i9 = (int)tmp_pu8 + ((-3 - (uint)CARRY1((byte)tmp_u6,(byte)tmp_u6)) - (int)&local_41c);
  tmp_i10 = *(int *)(tmp_i2 + 0x10);
  if ((tmp_i10 < tmp_i9) && (tmp_i10 != 0)) {
    tmp_i9 = tmp_i10;
  }
  tmp_i10 = *(int *)(param_1 + 0x24c);
  if ((tmp_i9 < tmp_i10) || (tmp_i10 < 0)) {
    tmp_i10 = 0;
    *(uint32_t *)(param_1 + 0x24c) = 0;
  }
  if ((param_2 & 0x400) == 0) {
    if ((param_2 == 0xab) || (param_2 == 0x8c)) {
      if (tmp_i9 <= tmp_i10) {
        return true;
      }
      memmove((void *)(tmp_i10 + (int)&local_41c),(void *)((int)auStack_418 + tmp_i10 + -3),
              tmp_i9 - tmp_i10);
      *(uint8_t *)((int)auStack_418 + tmp_i9 + -4) = 0;
      goto LAB_000ffaab;
    }
    if ((param_2 == 0xa5) || (param_2 == 0x87)) {
      if ((*(int *)(tmp_i2 + 0x14) != 0) &&
         ((*(int *)(tmp_i2 + 0x14) + *(int *)(tmp_i2 + 0x18) <= tmp_i10 && (tmp_i10 < tmp_i9)))) {
        *(int *)(param_1 + 0x24c) = tmp_i10 + 1;
        *(int *)(tmp_i2 + 0x18) = *(int *)(tmp_i2 + 0x18) + 1;
        return true;
      }
      if (tmp_i9 <= tmp_i10) {
        return true;
      }
      *(int *)(param_1 + 0x24c) = tmp_i10 + 1;
      return true;
    }
    if ((param_2 == 0xa3) || (param_2 == 0x86)) {
      if (tmp_i10 != 0) {
        tmp_i10 = tmp_i10 + -1;
        *(int *)(param_1 + 0x24c) = tmp_i10;
      }
      if (*(int *)(tmp_i2 + 0x18) <= tmp_i10) {
        return true;
      }
      *(int *)(tmp_i2 + 0x18) = *(int *)(tmp_i2 + 0x18) + -1;
      return true;
    }
    if ((param_2 == 0xa0) || (param_2 == 0x8f)) {
      *(uint32_t *)(param_1 + 0x24c) = 0;
      *(uint32_t *)(tmp_i2 + 0x18) = 0;
      return true;
    }
    if ((param_2 == 0xa6) || (param_2 == 0x90)) {
      *(int *)(param_1 + 0x24c) = tmp_i9;
      if (tmp_i9 <= *(int *)(tmp_i2 + 0x14)) {
        return true;
      }
      *(int *)(tmp_i2 + 0x18) = tmp_i9 - *(int *)(tmp_i2 + 0x14);
      return true;
    }
    if ((param_2 == 0xaa) || (param_2 == 0x8b)) {
      tmp_pc3 = *(void **)(DC + 0x80);
      tmp_i10 = (**(void **)(DC + 0x84))();
      (*tmp_pc3)(tmp_i10 == 0);
      return true;
    }
    goto LAB_000ff900;
  }
  param_2 = param_2 & 0xfffffbff;
  if (param_2 == 8) {
    if (tmp_i10 != 0) {
      tmp_i1 = tmp_i10 + -1;
      memmove((void *)((int)&local_41c + tmp_i1),(void *)(tmp_i10 + (int)&local_41c),
              (tmp_i9 + 1) - tmp_i10);
      *(int *)(param_1 + 0x24c) = tmp_i1;
      if (tmp_i1 < *(int *)(tmp_i2 + 0x18)) {
        *(int *)(tmp_i2 + 0x18) = *(int *)(tmp_i2 + 0x18) + -1;
      }
      *(uint8_t *)((int)auStack_418 + tmp_i9 + -4) = 0;
    }
LAB_000ffaab:
    (**(void **)(DC + 0x78))(*(uint32_t *)(param_1 + 0x114),&local_41c);
    return true;
  }
  if ((int)param_2 < 0x20) {
    return true;
  }
  if (*(int *)(param_1 + 0x114) == 0) {
    return true;
  }
  if (((*(int *)(param_1 + 200) == 9) && (9 < param_2 - 0x30)) && (param_2 != 0x2e)) {
    return false;
  }
  if (*(void **)(DC + 0x84) == (void *)0x0) {
LAB_000ff89a:
    if ((*(int *)(tmp_i2 + 0x10) != 0) && (*(int *)(tmp_i2 + 0x10) <= tmp_i10)) {
      return true;
    }
  }
  else {
    tmp_i10 = (**(void **)(DC + 0x84))();
    if (tmp_i10 != 0) {
      tmp_i10 = *(int *)(param_1 + 0x24c);
      goto LAB_000ff89a;
    }
    if (tmp_i9 == 0xff) {
      return true;
    }
    if ((*(int *)(tmp_i2 + 0x10) <= tmp_i9) && (*(int *)(tmp_i2 + 0x10) != 0)) {
      return true;
    }
    tmp_i10 = *(int *)(param_1 + 0x24c);
    memmove((void *)((int)auStack_418 + tmp_i10 + -3),(void *)((int)&local_41c + tmp_i10),
            (tmp_i9 + 1) - tmp_i10);
  }
  *(char *)((int)auStack_418 + tmp_i10 + -4) = (char)param_2;
  (**(void **)(DC + 0x78))(*(uint32_t *)(param_1 + 0x114),&local_41c);
  if (*(int *)(param_1 + 0x24c) <= tmp_i9) {
    tmp_i10 = *(int *)(param_1 + 0x24c) + 1;
    *(int *)(param_1 + 0x24c) = tmp_i10;
    if ((*(int *)(tmp_i2 + 0x14) < tmp_i10) && (*(int *)(tmp_i2 + 0x14) != 0)) {
      *(int *)(tmp_i2 + 0x18) = *(int *)(tmp_i2 + 0x18) + 1;
    }
  }
LAB_000ff900:
  if (((param_2 == 0x85 || param_2 == 9) || (param_2 == 0xa7)) &&
     (tmp_i10 = *(int *)(param_1 + 0xec), tmp_i10 != 0)) {
    tmp_i2 = *(int *)(tmp_i10 + 200);
    if (tmp_i2 == -1) {
      tmp_i9 = 0;
      *(uint32_t *)(tmp_i10 + 200) = 0;
      tmp_b5 = true;
    }
    else {
      tmp_b5 = false;
      tmp_i9 = tmp_i2;
    }
    while (tmp_i9 < *(int *)(tmp_i10 + 0xc0)) {
      tmp_i9 = tmp_i9 + 1;
      *(int *)(tmp_i10 + 200) = tmp_i9;
      if (*(int *)(tmp_i10 + 0xc0) <= tmp_i9) {
        if (!tmp_b5) {
          tmp_b5 = true;
          *(uint32_t *)(tmp_i10 + 200) = 0;
          tmp_i9 = 0;
          goto LAB_000ffbda;
        }
        tmp_i10 = *(int *)(tmp_i10 + 0x514 + tmp_i2 * 4);
LAB_000ffd56:
        if ((tmp_i10 != 0) && ((*(int *)(tmp_i10 + 200) == 9 || (*(int *)(tmp_i10 + 200) == 4)))) {
          g_editItem = tmp_i10;
        }
        goto LAB_000ff923;
      }
LAB_000ffbda:
      tmp_i9 = Item_SetFocus(*(uint32_t *)(tmp_i10 + 0x514 + tmp_i9 * 4),(float)*(int *)(DC + 0x124),
                            (float)*(int *)(DC + 0x128));
      if (tmp_i9 != 0) {
        pfVar4 = *(float **)(tmp_i10 + 0x514 + *(int *)(tmp_i10 + 200) * 4);
        Menu_HandleMouseMove(tmp_i10,*pfVar4 + 1.0,pfVar4[1] + 1.0);
        tmp_i10 = *(int *)(tmp_i10 + 0x514 + *(int *)(tmp_i10 + 200) * 4);
        goto LAB_000ffd56;
      }
      tmp_i9 = *(int *)(tmp_i10 + 200);
    }
    *(int *)(tmp_i10 + 200) = tmp_i2;
  }
LAB_000ff923:
  if (((param_2 == 0xa1) || (param_2 == 0x84)) &&
     ((tmp_i10 = Menu_SetPrevCursorItem(*(uint32_t *)(param_1 + 0xec)), tmp_i10 != 0 &&
      ((*(int *)(tmp_i10 + 200) == 9 || (*(int *)(tmp_i10 + 200) == 4)))))) {
    g_editItem = tmp_i10;
  }
  if ((param_2 != 0xa9) && (param_2 != 0xd)) {
    return param_2 != 0x1b;
  }
  if (*(int *)(param_1 + 0x108) != 0) {
    Item_RunScript_constprop_37();
  }
  return false;
}

void Menu_HandleKey(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  bool tmp_b2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  int *tmp_pi6;
  uint *tmp_pu7;
  int tmp_i8;
  uint tmp_u9;
  uint32_t *tmp_pu10;
  long double tmp_l11;
  
  Menu_HandleMouseMove(param_1,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128));
  if (param_3 == 0) {
    tmp_b2 = false;
    goto LAB_000ffead;
  }
  if (((param_2 == 0xa9) || (param_2 == 0xd)) && (*(int *)(param_1 + 0xe4) != 0)) goto LAB_001000ee;
  if (g_waitingForKey != 0) {
    Item_Bind_HandleKey(g_bindItem,param_2,param_3);
    return;
  }
  if (g_editingField == 0) {
LAB_00100249:
    tmp_b2 = true;
LAB_000ffead:
    if (param_1 == 0) {
      return;
    }
    if (tmp_b2) goto LAB_000fff70;
  }
  else {
    tmp_i4 = Item_TextField_HandleKey(g_editItem,param_2);
    if (tmp_i4 == 0) {
      g_editItem = 0;
      g_editingField = 0;
      return;
    }
    if (2 < param_2 - 0xb2U) {
      if (param_2 - 0x84U < 2) {
        return;
      }
      tmp_b2 = true;
      if (param_2 == 9) {
        return;
      }
      goto LAB_000ffead;
    }
    g_editingField = 0;
    g_editItem = 0;
    tmp_i4 = *(int *)(DC + 0x128);
    tmp_i3 = *(int *)(DC + 0x124);
    if (menuCount < 1) goto LAB_00100249;
    if ((g_unk_040f8f88 & 6) == 6) {
      tmp_i8 = 0;
      tmp_u9 = g_unk_040f8f88;
    }
    else {
      tmp_pu7 = &g_unk_040f9ca0;
      tmp_i8 = 0;
      do {
        tmp_i8 = tmp_i8 + 1;
        if (tmp_i8 == menuCount) goto LAB_001003c8;
        tmp_u9 = *tmp_pu7;
        tmp_pu7 = tmp_pu7 + 0x346;
      } while ((tmp_u9 & 6) != 6);
    }
    if ((tmp_u9 & 0x200000) == 0) {
LAB_001003c8:
      tmp_i8 = 0;
      tmp_pu10 = &Menus;
      do {
        tmp_i8 = tmp_i8 + 1;
        Menu_HandleMouseMove(tmp_pu10,(float)tmp_i3,(float)tmp_i4);
        tmp_pu10 = tmp_pu10 + 0x346;
      } while (tmp_i8 < menuCount);
      tmp_b2 = true;
      goto LAB_000ffead;
    }
    Menu_HandleMouseMove(&Menus + tmp_i8 * 0x346,(float)tmp_i3,(float)tmp_i4);
    if (param_1 == 0) {
      return;
    }
LAB_000fff70:
    if ((((*(byte *)(param_1 + 0x4a) & 0x20) == 0) &&
        (tmp_i4 = Rect_ContainsPoint(param_1,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128))
        , tmp_i4 == 0)) && ((inHandleKey_10167 == 0 && (param_2 - 0xb2U < 3)))) {
      inHandleKey_10167 = 1;
      Menus_HandleOOBClick(param_1,param_2,param_3);
      inHandleKey_10167 = 0;
      return;
    }
  }
  if (*(int *)(param_1 + 0xc0) < 1) {
    tmp_i4 = 0;
  }
  else {
    tmp_i4 = 0;
    tmp_pi6 = (int *)(param_1 + 0x514);
    do {
      if ((*(byte *)(*tmp_pi6 + 0x48) & 2) != 0) {
        tmp_i4 = *tmp_pi6;
      }
      tmp_pi6 = tmp_pi6 + 1;
    } while (tmp_pi6 != (int *)(*(int *)(param_1 + 0xc0) * 4 + 0x514 + param_1));
    if ((tmp_i4 != 0) && (tmp_i3 = Item_HandleKey(tmp_i4,param_2,param_3), tmp_i3 != 0))
    goto LAB_000fff17;
  }
  if (param_3 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0xd14) == 0) {
    if ((param_2 - 1U < 0xff) && (*(int *)(param_1 + 0xf4 + param_2 * 4) != 0)) goto LAB_001000ee;
  }
  else if ((param_2 - 1U < 0xff) && (tmp_i3 = *(int *)(param_1 + 0xc0), 0 < tmp_i3)) {
    tmp_i8 = 0;
    do {
      tmp_i1 = *(int *)(param_1 + 0x514 + tmp_i8 * 4);
      if (*(int *)(tmp_i1 + 0x254) == param_2) {
        tmp_i3 = Item_EnableShowViaCvar(tmp_i1,4);
        if (tmp_i3 != 0) {
          Item_RunScript_constprop_37();
          return;
        }
        tmp_i3 = *(int *)(param_1 + 0xc0);
      }
      tmp_i8 = tmp_i8 + 1;
    } while (tmp_i8 < tmp_i3);
  }
  if (param_2 == 0x9c) {
    tmp_l11 = (long double)(**(void **)(DC + 0x74))("developer");
    if (tmp_l11 == (long double)0) {
      return;
    }
    (**(void **)(DC + 200))(2,"screenshot\n");
    return;
  }
  if (param_2 < 0x9d) {
    if (param_2 == 0x1b) {
      if (g_waitingForKey != 0) {
        return;
      }
      if (*(int *)(param_1 + 0xe0) == 0) {
        return;
      }
LAB_001000ee:
      Item_RunScript_constprop_37();
      return;
    }
    if (0x1b < param_2) {
      if (param_2 != 0x85) {
        if (param_2 == 0x9b) {
          tmp_l11 = (long double)(**(void **)(DC + 0x74))("developer");
          if (tmp_l11 == (long double)0) {
            return;
          }
          debugMode = debugMode ^ 1;
          return;
        }
        if (param_2 != 0x84) {
          return;
        }
        goto LAB_001002aa;
      }
LAB_0010023f:
      Menu_SetNextCursorItem(param_1);
      return;
    }
    if (param_2 == 9) {
      tmp_i4 = (**(void **)(DC + 0xc0))(0x8a);
      if (tmp_i4 != 0) {
        Menu_SetPrevCursorItem(param_1);
        return;
      }
      goto LAB_0010023f;
    }
    if (param_2 != 0xd) {
      return;
    }
  }
  else if (param_2 != 0xa9) {
    if (param_2 < 0xaa) {
      if (param_2 != 0xa1) {
        if (param_2 != 0xa7) {
          return;
        }
        goto LAB_0010023f;
      }
LAB_001002aa:
      Menu_SetPrevCursorItem(param_1);
      return;
    }
    if (param_2 < 0xb2) {
      return;
    }
    if (param_2 < 0xb4) {
      if (tmp_i4 == 0) {
        return;
      }
      tmp_i3 = *(int *)(tmp_i4 + 200);
      if (tmp_i3 == 0) {
        tmp_i4 = *(int *)(DC + 0x128);
        tmp_i3 = *(int *)(DC + 0x124);
        tmp_u5 = Item_CorrectedTextRect();
        tmp_i4 = Rect_ContainsPoint(tmp_u5,(float)tmp_i3,(float)tmp_i4);
        if (tmp_i4 == 0) {
          return;
        }
        goto LAB_000fff17;
      }
      if ((tmp_i3 != 9) && (tmp_i3 != 4)) {
        tmp_i4 = Rect_ContainsPoint(tmp_i4,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128));
        if (tmp_i4 == 0) {
          return;
        }
        goto LAB_000fff17;
      }
      tmp_i3 = Rect_ContainsPoint(tmp_i4,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128));
      if (tmp_i3 == 0) {
        return;
      }
      if (*(int *)(tmp_i4 + 0x250) != 0) {
        *(uint32_t *)(*(int *)(tmp_i4 + 0x250) + 0x18) = 0;
      }
      goto LAB_001002df;
    }
    if (param_2 != 0xb4) {
      return;
    }
  }
  if (tmp_i4 == 0) {
    return;
  }
  if ((*(int *)(tmp_i4 + 200) != 9) && (*(int *)(tmp_i4 + 200) != 4)) {
LAB_000fff17:
    Item_RunScript_constprop_37();
    return;
  }
LAB_001002df:
  *(uint32_t *)(tmp_i4 + 0x24c) = 0;
  g_editingField = 1;
  g_editItem = tmp_i4;
  return;
}

void Menus_HandleOOBClick(int param_1,uint32_t param_2,int param_3)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint *tmp_pu6;
  void *tmp_pc7;
  uint tmp_u8;
  int tmp_i9;
  uint32_t *tmp_pu10;
  int tmp_i11;
  int local_38;
  int local_34;
  int local_28;
  
  if (param_1 == 0) {
    return;
  }
  if ((param_3 == 0) || (tmp_u8 = *(uint *)(param_1 + 0x48), (tmp_u8 & 0x20000) == 0)) {
    if (menuCount < 1) goto LAB_00100894;
LAB_0010051a:
    local_38 = 0;
    tmp_pu10 = &Menus;
    local_28 = menuCount;
    do {
      tmp_i9 = DC;
      if ((tmp_pu10[0x12] & 0x100004) != 0) {
        tmp_f1 = (float)*(int *)(DC + 0x128);
        tmp_f2 = (float)*(int *)(DC + 0x124);
        tmp_i3 = Rect_ContainsPoint(tmp_pu10,tmp_f2,tmp_f1);
        if ((tmp_i3 != 0) && (tmp_i3 = tmp_pu10[0x30], 0 < tmp_i3)) {
          tmp_i11 = 0;
          do {
            tmp_i5 = tmp_pu10[tmp_i11 + 0x145];
            if ((((*(uint *)(tmp_i5 + 0x48) & 0x100004) != 0) &&
                ((*(uint *)(tmp_i5 + 0x48) & 0x10) == 0)) &&
               (tmp_i4 = Rect_ContainsPoint(tmp_i5,tmp_f2,tmp_f1), tmp_i4 != 0)) {
              if ((*(int *)(tmp_i5 + 200) == 0) && (*(int *)(tmp_i5 + 0xe8) != 0)) {
                rect_10157 = *(uint32_t *)(tmp_i5 + 0xb8);
                g_unk_00c38260 = *(float *)(tmp_i5 + 0xbc);
                g_unk_00c38264 = *(float *)(tmp_i5 + 0xc0);
                g_unk_00c38268 = *(float *)(tmp_i5 + 0xc4);
                if (g_unk_00c38264 != 0.0) {
                  g_unk_00c38260 = g_unk_00c38260 - g_unk_00c38268;
                }
                tmp_i5 = Rect_ContainsPoint(&rect_10157,tmp_f2,tmp_f1);
                if (tmp_i5 == 0) goto LAB_001005a0;
              }
              *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xfffffffc;
              tmp_pu10[0x12] = tmp_pu10[0x12] | 6;
              Menu_HandleMouseMove
                        (tmp_pu10,(float)*(int *)(tmp_i9 + 0x124),(float)*(int *)(tmp_i9 + 0x128));
              Menu_HandleKey(tmp_pu10,param_2,param_3);
              local_28 = menuCount;
              break;
            }
LAB_001005a0:
            tmp_i11 = tmp_i11 + 1;
          } while (tmp_i11 != tmp_i3);
        }
      }
      local_38 = local_38 + 1;
      tmp_pu10 = tmp_pu10 + 0x346;
    } while (local_38 < local_28);
    if (0 < local_28) {
      tmp_pu6 = &g_unk_040f8f88;
      tmp_i9 = 0;
      do {
        if ((*tmp_pu6 & 0x100004) != 0) {
          tmp_i9 = tmp_i9 + 1;
        }
        tmp_pu6 = tmp_pu6 + 0x346;
      } while (tmp_pu6 != &g_unk_040f8f88 + local_28 * 0x346);
      if (tmp_i9 != 0) goto LAB_0010072d;
    }
    tmp_pc7 = *(void **)(DC + 0xd4);
    if (tmp_pc7 == (void *)0x0) goto LAB_0010072d;
  }
  else {
    if ((tmp_u8 & 4) != 0) {
      Menu_RunCloseScript_part_10();
      tmp_u8 = *(uint *)(param_1 + 0x48);
    }
    *(uint *)(param_1 + 0x48) = tmp_u8 & 0xfffffff8;
    if (0 < menuCount) goto LAB_0010051a;
LAB_00100894:
    tmp_pc7 = *(void **)(DC + 0xd4);
    if (tmp_pc7 == (void *)0x0) {
      return;
    }
  }
  (*tmp_pc7)(0);
  local_28 = menuCount;
LAB_0010072d:
  if (0 < local_28) {
    tmp_pu10 = &Menus;
    local_34 = 0;
    do {
      if ((tmp_pu10[0xd] == 5) && (-1 < (int)tmp_pu10[0xc])) {
        (**(void **)(DC + 0xec))(tmp_pu10[0xc]);
        tmp_pu10[0xc] = 0xffffffff;
      }
      if (0 < (int)tmp_pu10[0x30]) {
        tmp_i9 = 0;
        do {
          while ((tmp_i3 = tmp_pu10[tmp_i9 + 0x145], *(int *)(tmp_i3 + 0x34) != 5 ||
                 (*(int *)(tmp_i3 + 0x30) < 0))) {
            if (*(int *)(tmp_i3 + 200) != 8) goto LAB_00100779;
LAB_001007d0:
            tmp_i9 = tmp_i9 + 1;
            (**(void **)(DC + 0xec))(-*(int *)(tmp_i3 + 0x3c));
            if ((int)tmp_pu10[0x30] <= tmp_i9) goto LAB_001007f0;
          }
          (**(void **)(DC + 0xec))(*(int *)(tmp_i3 + 0x30));
          *(uint32_t *)(tmp_i3 + 0x30) = 0xffffffff;
          tmp_i3 = tmp_pu10[tmp_i9 + 0x145];
          if (*(int *)(tmp_i3 + 200) == 8) goto LAB_001007d0;
LAB_00100779:
          tmp_i9 = tmp_i9 + 1;
        } while (tmp_i9 < (int)tmp_pu10[0x30]);
      }
LAB_001007f0:
      local_34 = local_34 + 1;
      tmp_pu10 = tmp_pu10 + 0x346;
    } while (local_34 < menuCount);
  }
  return;
}

void Menu_Paint(int param_1,int param_2)
{
  int tmp_i1;
  
  if ((param_1 == 0) || ((param_2 == 0 && ((*(byte *)(param_1 + 0x48) & 4) == 0)))) {
    return;
  }
  if ((*(int *)(param_1 + 0x40) != 0) &&
     ((*(void **)(DC + 100) != (void *)0x0 &&
      (tmp_i1 = (**(void **)(DC + 100))(*(int *)(param_1 + 0x40)), tmp_i1 == 0)))) {
    return;
  }
  Menu_Paint_part_20();
  return;
}

void Item_ValidateTypeData(int param_1)
{
  if (*(int *)(param_1 + 0x250) != 0) {
    return;
  }
  Item_ValidateTypeData_part_21();
  return;
}

uint32_t Item_ValidateTooltipData(int param_1)
{
  uint32_t tmp_u1;
  
  if (*(int *)(param_1 + 0x270) != 0) {
    return 1;
  }
  tmp_u1 = Item_ValidateTooltipData_part_24();
  return tmp_u1;
}

uint KeywordHash_Key(char *param_1)
{
  int tmp_i1;
  uint tmp_u2;
  char tmp_c3;
  int tmp_i4;
  
  tmp_c3 = *param_1;
  if (tmp_c3 == '\0') {
    tmp_u2 = 0;
  }
  else {
    tmp_u2 = 0;
    tmp_i4 = 0x77;
    do {
      tmp_i1 = (int)tmp_c3;
      if ((byte)(tmp_c3 + 0xbfU) < 0x1a) {
        tmp_i1 = tmp_c3 + 0x20;
      }
      tmp_u2 = tmp_i1 * tmp_i4 + tmp_u2;
      tmp_c3 = param_1[tmp_i4 + -0x76];
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_c3 != '\0');
    tmp_u2 = (tmp_u2 ^ (int)tmp_u2 >> 0x14 ^ (int)tmp_u2 >> 10) & 0x1ff;
  }
  return tmp_u2;
}

void KeywordHash_Add(int param_1,uint32_t *param_2)
{
  int tmp_i1;
  uint tmp_u2;
  int tmp_i3;
  char tmp_c4;
  
  tmp_c4 = *(char *)*param_2;
  if (tmp_c4 == '\0') {
    tmp_i3 = 0;
  }
  else {
    tmp_u2 = 0;
    tmp_i3 = 0x77;
    do {
      tmp_i1 = (int)tmp_c4;
      if ((byte)(tmp_c4 + 0xbfU) < 0x1a) {
        tmp_i1 = tmp_c4 + 0x20;
      }
      tmp_u2 = tmp_i1 * tmp_i3 + tmp_u2;
      tmp_c4 = ((char *)*param_2)[tmp_i3 + -0x76];
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_c4 != '\0');
    tmp_i3 = ((tmp_u2 ^ (int)tmp_u2 >> 10 ^ (int)tmp_u2 >> 0x14) & 0x1ff) << 2;
  }
  param_2[2] = *(uint32_t *)(tmp_i3 + param_1);
  *(uint32_t *)(tmp_i3 + param_1) = param_2;
  return;
}

uint32_t * KeywordHash_Find(int param_1,char *param_2)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  char tmp_c4;
  uint tmp_u5;
  
  tmp_c4 = *param_2;
  if (tmp_c4 == '\0') {
    tmp_i3 = 0;
  }
  else {
    tmp_u5 = 0;
    tmp_i3 = 0x77;
    do {
      tmp_i2 = (int)tmp_c4;
      if ((byte)(tmp_c4 + 0xbfU) < 0x1a) {
        tmp_i2 = tmp_c4 + 0x20;
      }
      tmp_u5 = tmp_i2 * tmp_i3 + tmp_u5;
      tmp_c4 = param_2[tmp_i3 + -0x76];
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_c4 != '\0');
    tmp_i3 = (((int)tmp_u5 >> 10 ^ (int)tmp_u5 >> 0x14 ^ tmp_u5) & 0x1ff) << 2;
  }
  tmp_pu1 = *(uint32_t **)(param_1 + tmp_i3);
  while( true ) {
    if (tmp_pu1 == (uint32_t *)0x0) {
      return (uint32_t *)0x0;
    }
    tmp_i3 = Q_stricmp(*tmp_pu1,param_2);
    if (tmp_i3 == 0) break;
    tmp_pu1 = (uint32_t *)tmp_pu1[2];
  }
  return tmp_pu1;
}

void Item_SetupKeywordHash(void)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  char tmp_c6;
  char *tmp_pc7;
  uint8_t **local_18;
  uint32_t *local_14;
  
  local_14 = &itemParseKeywordHash;
  tmp_pu4 = &itemParseKeywordHash;
  for (tmp_i5 = 0x200; tmp_i5 != 0; tmp_i5 = tmp_i5 + -1) {
    *tmp_pu4 = 0;
    tmp_pu4 = tmp_pu4 + 1;
  }
  if (itemParseKeywords != (uint8_t *)0x0) {
    tmp_pc7 = itemParseKeywords;
    local_18 = &itemParseKeywords;
    do {
      tmp_c6 = *tmp_pc7;
      tmp_pu4 = local_14;
      if (tmp_c6 != '\0') {
        tmp_u3 = 0;
        tmp_i5 = 0x77;
        do {
          tmp_i2 = (int)tmp_c6;
          if ((byte)(tmp_c6 + 0xbfU) < 0x1a) {
            tmp_i2 = tmp_c6 + 0x20;
          }
          tmp_u3 = tmp_i2 * tmp_i5 + tmp_u3;
          tmp_c6 = tmp_pc7[tmp_i5 + -0x76];
          tmp_i5 = tmp_i5 + 1;
        } while (tmp_c6 != '\0');
        tmp_pu4 = &itemParseKeywordHash + ((tmp_u3 ^ (int)tmp_u3 >> 0x14 ^ (int)tmp_u3 >> 10) & 0x1ff);
      }
      tmp_pu1 = (uint8_t *)*tmp_pu4;
      *tmp_pu4 = local_18;
      local_18[2] = tmp_pu1;
      tmp_pc7 = local_18[3];
      local_18 = local_18 + 3;
    } while (tmp_pc7 != (char *)0x0);
  }
  return;
}

void String_Init(void)
{
  uint8_t *tmp_pu1;
  char *tmp_pc2;
  int tmp_i3;
  uint tmp_u4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  char tmp_c7;
  uint8_t **tmp_ppu8;
  uint8_t **tmp_ppu9;
  byte tmp_b10;
  uint32_t *local_20;
  
  tmp_b10 = 0;
  tmp_pu5 = &strHandle;
  for (tmp_i6 = 0x800; tmp_i6 != 0; tmp_i6 = tmp_i6 + -1) {
    *tmp_pu5 = 0;
    tmp_pu5 = tmp_pu5 + 1;
  }
  modalMenuCount = 0;
  allocPoint = 0;
  strPoolIndex = 0;
  outOfMemory = 0;
  strHandleCount = 0;
  menuCount = 0;
  Item_SetupKeywordHash();
  local_20 = &menuParseKeywordHash;
  tmp_pu5 = &menuParseKeywordHash;
  for (tmp_i6 = 0x200; tmp_i6 != 0; tmp_i6 = tmp_i6 + -1) {
    *tmp_pu5 = 0;
    tmp_pu5 = tmp_pu5 + (uint)tmp_b10 * -2 + 1;
  }
  tmp_ppu8 = &menuParseKeywords;
  tmp_pc2 = menuParseKeywords;
  while (tmp_pc2 != (char *)0x0) {
    tmp_c7 = *tmp_pc2;
    tmp_pu5 = local_20;
    if (tmp_c7 != '\0') {
      tmp_u4 = 0;
      tmp_i6 = 0x77;
      do {
        tmp_i3 = (int)tmp_c7;
        if ((byte)(tmp_c7 + 0xbfU) < 0x1a) {
          tmp_i3 = tmp_c7 + 0x20;
        }
        tmp_u4 = tmp_i3 * tmp_i6 + tmp_u4;
        tmp_c7 = tmp_pc2[tmp_i6 + -0x76];
        tmp_i6 = tmp_i6 + 1;
      } while (tmp_c7 != '\0');
      tmp_pu5 = &menuParseKeywordHash + ((tmp_u4 ^ (int)tmp_u4 >> 0x14 ^ (int)tmp_u4 >> 10) & 0x1ff);
    }
    tmp_pu1 = (uint8_t *)*tmp_pu5;
    *tmp_pu5 = tmp_ppu8;
    tmp_ppu8[2] = tmp_pu1;
    tmp_pc2 = tmp_ppu8[3];
    tmp_ppu8 = tmp_ppu8 + 3;
  }
  if ((DC != 0) && (*(int *)(DC + 0xb8) != 0)) {
    tmp_ppu8 = (uint8_t **)&g_unk_0014a9d8;
    do {
      tmp_ppu9 = tmp_ppu8 + 8;
      (**(void **)(DC + 0xbc))(tmp_ppu8[-6],tmp_ppu8,tmp_ppu8 + 1);
      tmp_ppu8 = tmp_ppu9;
    } while (tmp_ppu9 != &g_ptr_DAT_0014b178);
  }
  return;
}

int Item_Parse(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  uint32_t *tmp_pu4;
  char tmp_c5;
  char acStack_49a [58];
  uint32_t uStack_460;
  uint32_t local_45c;
  char *local_458;
  char *local_454;
  uint8_t *local_444;
  char *local_440;
  uint8_t local_434 [16];
  char local_424;
  char acStack_423 [1043];
  
  local_458 = local_434;
  local_45c = param_1;
  uStack_460 = 0x100f10;
  local_444 = local_458;
  tmp_i2 = trap_PC_ReadToken();
  if ((tmp_i2 == 0) || (local_424 != '{')) {
    return 0;
  }
  local_440 = "unknown menu item keyword %s";
LAB_00100f40:
  do {
    local_458 = local_444;
    local_45c = param_1;
    uStack_460 = 0x100f57;
    tmp_i2 = trap_PC_ReadToken();
    if (tmp_i2 == 0) {
      local_458 = "end of file inside menu item\n";
      local_45c = param_1;
      uStack_460 = 0x10107c;
      PC_SourceError();
      return 0;
    }
    if (local_424 == '}') {
      return 1;
    }
    if (local_424 == '\0') {
      tmp_pu4 = &itemParseKeywordHash;
    }
    else {
      tmp_u3 = 0;
      tmp_i2 = 0x77;
      tmp_c5 = local_424;
      do {
        tmp_i1 = (int)tmp_c5;
        if ((byte)(tmp_c5 + 0xbfU) < 0x1a) {
          tmp_i1 = tmp_c5 + 0x20;
        }
        tmp_u3 = tmp_i1 * tmp_i2 + tmp_u3;
        tmp_c5 = acStack_49a[tmp_i2];
        tmp_i2 = tmp_i2 + 1;
      } while (tmp_c5 != '\0');
      tmp_pu4 = &itemParseKeywordHash + ((tmp_u3 ^ (int)tmp_u3 >> 10 ^ (int)tmp_u3 >> 0x14) & 0x1ff);
    }
    for (tmp_pu4 = (uint32_t *)*tmp_pu4; tmp_pu4 != (uint32_t *)0x0;
        tmp_pu4 = (uint32_t *)tmp_pu4[2]) {
      local_45c = *tmp_pu4;
      uStack_460 = 0x100fe5;
      local_458 = &local_424;
      tmp_i2 = Q_stricmp();
      if (tmp_i2 == 0) {
        local_458 = (char *)param_1;
        local_45c = param_2;
        uStack_460 = 0x101001;
        tmp_i2 = (*(void *)tmp_pu4[1])();
        if (tmp_i2 == 0) {
          local_458 = "couldn\'t parse menu item keyword %s";
          local_45c = param_1;
          uStack_460 = 0x10102a;
          local_454 = &local_424;
          local_444 = (uint8_t *)tmp_i2;
          PC_SourceError();
          return (int)local_444;
        }
        goto LAB_00100f40;
      }
    }
    local_45c = param_1;
    uStack_460 = 0x101053;
    local_458 = local_440;
    local_454 = &local_424;
    PC_SourceError();
  } while( true );
}

uint32_t MenuParse_itemDef(int param_1,uint32_t param_2)
{
  uint16_t *tmp_pu1;
  uint tmp_u2;
  uint16_t *tmp_pu3;
  int tmp_i4;
  uint32_t tmp_u5;
  uint8_t *tmp_pu6;
  int tmp_i7;
  uint32_t *tmp_pu8;
  uint tmp_u9;
  uint32_t tmp_u10;
  bool tmp_b11;
  
  tmp_i4 = *(int *)(param_1 + 0xc0);
  if (tmp_i4 < 0x200) {
    tmp_i7 = tmp_i4;
    if (allocPoint < 0x1ffd89) {
      tmp_pu6 = memoryPool + allocPoint;
      allocPoint = allocPoint + 0x280;
    }
    else {
      outOfMemory = 1;
      if (*(void **)(DC + 0xd0) == (void *)0x0) {
        tmp_pu6 = (uint8_t *)0x0;
      }
      else {
        (**(void **)(DC + 0xd0))("UI_Alloc: Failure. Out of memory!\n");
        tmp_pu6 = (uint8_t *)0x0;
        tmp_i7 = *(int *)(param_1 + 0xc0);
      }
    }
    *(uint8_t **)(param_1 + 0x514 + tmp_i4 * 4) = tmp_pu6;
    tmp_u9 = 0x278;
    tmp_pu1 = *(uint16_t **)(param_1 + 0x514 + tmp_i7 * 4);
    tmp_b11 = ((uint)tmp_pu1 & 1) != 0;
    tmp_pu3 = tmp_pu1;
    if (tmp_b11) {
      *(uint8_t *)tmp_pu1 = 0;
      tmp_pu3 = (uint16_t *)((int)tmp_pu1 + 1);
      tmp_u9 = 0x277;
    }
    if (((uint)tmp_pu3 & 2) != 0) {
      *tmp_pu3 = 0;
      tmp_u9 = tmp_u9 - 2;
      tmp_pu3 = tmp_pu3 + 1;
    }
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)tmp_pu3 + tmp_u2) = 0;
      *(uint32_t *)((int)tmp_pu3 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < (tmp_u9 & 0xfffffff8));
    tmp_pu8 = (uint32_t *)((int)tmp_pu3 + tmp_u2);
    if ((tmp_u9 & 4) != 0) {
      *tmp_pu8 = 0;
      tmp_pu8 = tmp_pu8 + 1;
    }
    if ((tmp_u9 & 2) != 0) {
      *(uint16_t *)tmp_pu8 = 0;
      tmp_pu8 = (uint32_t *)((int)tmp_pu8 + 2);
    }
    if (tmp_b11) {
      *(uint8_t *)tmp_pu8 = 0;
    }
    tmp_b11 = ((uint)tmp_pu1 & 1) != 0;
    tmp_u9 = 0xb8;
    *(uint32_t *)(tmp_pu1 + 0x12a) = 0xffffffff;
    *(uint32_t *)(tmp_pu1 + 0x6e) = 0x3f0ccccd;
    *(uint32_t *)(tmp_pu1 + 0x13a) = 0;
    tmp_pu3 = tmp_pu1;
    if (tmp_b11) {
      *(uint8_t *)tmp_pu1 = 0;
      tmp_pu3 = (uint16_t *)((int)tmp_pu1 + 1);
      tmp_u9 = 0xb7;
    }
    if (((uint)tmp_pu3 & 2) != 0) {
      *tmp_pu3 = 0;
      tmp_u9 = tmp_u9 - 2;
      tmp_pu3 = tmp_pu3 + 1;
    }
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)tmp_pu3 + tmp_u2) = 0;
      *(uint32_t *)((int)tmp_pu3 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < (tmp_u9 & 0xfffffff8));
    tmp_pu8 = (uint32_t *)((int)tmp_pu3 + tmp_u2);
    if ((tmp_u9 & 4) != 0) {
      *tmp_pu8 = 0;
      tmp_pu8 = tmp_pu8 + 1;
    }
    if ((tmp_u9 & 2) != 0) {
      *(uint16_t *)tmp_pu8 = 0;
      tmp_pu8 = (uint32_t *)((int)tmp_pu8 + 2);
    }
    if (tmp_b11) {
      *(uint8_t *)tmp_pu8 = 0;
    }
    *(uint32_t *)(tmp_pu1 + 0x22) = 0x3f800000;
    *(uint32_t *)(tmp_pu1 + 0x40) = 0x3f800000;
    *(uint32_t *)(tmp_pu1 + 0x3e) = 0x3f800000;
    *(uint32_t *)(tmp_pu1 + 0x3c) = 0x3f800000;
    *(uint32_t *)(tmp_pu1 + 0x3a) = 0x3f800000;
    *(uint32_t *)(tmp_pu1 + 0x18) = 0xffffffff;
    tmp_i4 = Item_Parse(param_2,*(uint32_t *)(param_1 + 0x514 + *(int *)(param_1 + 0xc0) * 4));
    tmp_u10 = 0;
    if (tmp_i4 != 0) {
      *(int *)(*(int *)(param_1 + 0x514 + *(int *)(param_1 + 0xc0) * 4) + 0xec) = param_1;
      tmp_i4 = *(int *)(param_1 + 0xc0);
      *(int *)(param_1 + 0xc0) = tmp_i4 + 1;
      tmp_i4 = *(int *)(param_1 + 0x514 + tmp_i4 * 4);
      if (tmp_i4 != 0) {
        if (*(int *)(tmp_i4 + 200) == 6) {
          tmp_pu8 = *(uint32_t **)(tmp_i4 + 0x250);
          *(uint32_t *)(tmp_i4 + 0x24c) = 0;
          if (tmp_pu8 != (uint32_t *)0x0) {
            tmp_pu8[3] = 0;
            *tmp_pu8 = 0;
            tmp_pu8[1] = 0;
          }
        }
        if (*(int *)(tmp_i4 + 0x270) != 0) {
          Tooltip_ComputePosition(tmp_i4);
        }
      }
      tmp_u10 = 1;
      if (*(int *)(param_1 + 0xd14) != 0) {
        tmp_i4 = *(int *)(param_1 + 0x510 + *(int *)(param_1 + 0xc0) * 4);
        tmp_i7 = *(int *)(tmp_i4 + 0x254);
        if (-1 < tmp_i7) {
          tmp_u5 = String_Alloc(*(uint32_t *)(tmp_i4 + 600));
          *(uint32_t *)(param_1 + 0xf4 + tmp_i7 * 4) = tmp_u5;
        }
      }
    }
  }
  else {
    tmp_u10 = 1;
    trap_Print("^3UI WARNING: Reached MAX_MENUITEMS\n");
  }
  return tmp_u10;
}

void Item_InitControls(int param_1)
{
  uint *tmp_pu1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  float tmp_f4;
  int tmp_i5;
  
  if (param_1 != 0) {
    if (*(int *)(param_1 + 200) == 6) {
      tmp_pu3 = *(uint32_t **)(param_1 + 0x250);
      *(uint32_t *)(param_1 + 0x24c) = 0;
      if (tmp_pu3 != (uint32_t *)0x0) {
        tmp_pu3[3] = 0;
        *tmp_pu3 = 0;
        tmp_pu3[1] = 0;
      }
    }
    tmp_i2 = *(int *)(param_1 + 0x270);
    if (tmp_i2 != 0) {
      (**(void **)(DC + 0x30))(*(uint32_t *)(tmp_i2 + 0xe0));
      *(float *)(tmp_i2 + 0x10) = *(float *)(param_1 + 0x18) / 3.0 + *(float *)(param_1 + 0x10);
      *(float *)(tmp_i2 + 0x14) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x1c) + 8.0;
      tmp_i5 = (**(void **)(DC + 0x2c))
                        (*(uint32_t *)(*(int *)(param_1 + 0x270) + 0xe8),
                         *(uint32_t *)(*(int *)(param_1 + 0x270) + 0xdc),0);
      *(float *)(tmp_i2 + 0x1c) = (float)tmp_i5 + 9.0;
      tmp_i5 = (**(void **)(DC + 0x20))
                        (*(uint32_t *)(*(int *)(param_1 + 0x270) + 0xe8),
                         *(uint32_t *)(*(int *)(param_1 + 0x270) + 0xdc),0);
      *(float *)(tmp_i2 + 0x18) = (float)tmp_i5 + 6.0;
      tmp_f4 = (float)tmp_i5 + 6.0 + *(float *)(tmp_i2 + 0x10);
      if (635.0 < tmp_f4) {
        *(float *)(tmp_i2 + 0x10) = *(float *)(tmp_i2 + 0x10) - (tmp_f4 - 635.0);
      }
      *(uint32_t *)(*(int *)(param_1 + 0x270) + 0xec) = *(uint32_t *)(param_1 + 0xec);
      *(uint32_t *)(*(int *)(param_1 + 0x270) + 200) = 0;
      *(uint32_t *)(*(int *)(param_1 + 0x270) + 0x34) = 1;
      tmp_pu1 = (uint *)(*(int *)(param_1 + 0x270) + 0x48);
      *tmp_pu1 = *tmp_pu1 | 4;
    }
  }
  return;
}

void Menu_SetupKeywordHash(void)
{
  uint8_t *tmp_pu1;
  char *tmp_pc2;
  int tmp_i3;
  uint8_t **tmp_ppu4;
  uint tmp_u5;
  uint32_t *tmp_pu6;
  int tmp_i7;
  char tmp_c8;
  uint32_t *local_14;
  
  local_14 = &menuParseKeywordHash;
  tmp_pu6 = &menuParseKeywordHash;
  for (tmp_i7 = 0x200; tmp_i7 != 0; tmp_i7 = tmp_i7 + -1) {
    *tmp_pu6 = 0;
    tmp_pu6 = tmp_pu6 + 1;
  }
  tmp_ppu4 = &menuParseKeywords;
  tmp_pc2 = menuParseKeywords;
  while (tmp_pc2 != (char *)0x0) {
    tmp_c8 = *tmp_pc2;
    tmp_pu6 = local_14;
    if (tmp_c8 != '\0') {
      tmp_u5 = 0;
      tmp_i7 = 0x77;
      do {
        tmp_i3 = (int)tmp_c8;
        if ((byte)(tmp_c8 + 0xbfU) < 0x1a) {
          tmp_i3 = tmp_c8 + 0x20;
        }
        tmp_u5 = tmp_i3 * tmp_i7 + tmp_u5;
        tmp_c8 = tmp_pc2[tmp_i7 + -0x76];
        tmp_i7 = tmp_i7 + 1;
      } while (tmp_c8 != '\0');
      tmp_pu6 = &menuParseKeywordHash + ((tmp_u5 ^ (int)tmp_u5 >> 0x14 ^ (int)tmp_u5 >> 10) & 0x1ff);
    }
    tmp_pu1 = (uint8_t *)*tmp_pu6;
    *tmp_pu6 = tmp_ppu4;
    tmp_ppu4[2] = tmp_pu1;
    tmp_pc2 = tmp_ppu4[3];
    tmp_ppu4 = tmp_ppu4 + 3;
  }
  return;
}

int Menu_Parse(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint tmp_u4;
  char tmp_c5;
  byte tmp_b6;
  char acStack_49a [58];
  uint32_t uStack_460;
  uint32_t local_45c;
  char *local_458;
  char *local_454;
  uint32_t *local_444;
  char *local_440;
  uint32_t local_434;
  uint32_t local_430 [3];
  char local_424;
  char acStack_423 [1043];
  
  tmp_b6 = 0;
  local_458 = (char *)&local_434;
  local_45c = param_1;
  uStack_460 = 0x101630;
  local_444 = (uint32_t *)local_458;
  tmp_i2 = trap_PC_ReadToken();
  if ((tmp_i2 == 0) || (local_424 != '{')) {
    return 0;
  }
  local_440 = "unknown menu keyword %s";
  local_424 = '{';
  local_458 = (char *)local_444;
joined_r0x0010166d:
  do {
    tmp_u4 = 0x418;
    tmp_pu3 = (uint32_t *)local_458;
    if (((uint)local_458 & 4) != 0) {
      *(uint32_t *)local_458 = 0;
      tmp_pu3 = local_430;
      tmp_u4 = 0x414;
    }
    for (tmp_u4 = tmp_u4 >> 2; tmp_u4 != 0; tmp_u4 = tmp_u4 - 1) {
      *tmp_pu3 = 0;
      tmp_pu3 = tmp_pu3 + (uint)tmp_b6 * -2 + 1;
    }
    local_45c = param_1;
    uStack_460 = 0x101691;
    local_444 = (uint32_t *)local_458;
    tmp_i2 = trap_PC_ReadToken();
    if (tmp_i2 == 0) {
      local_458 = "end of file inside menu\n";
      local_45c = param_1;
      uStack_460 = 0x1017de;
      PC_SourceError();
      return 0;
    }
    if (local_424 == '}') {
      return 1;
    }
    if (local_424 == '\0') {
      tmp_pu3 = &menuParseKeywordHash;
    }
    else {
      tmp_u4 = 0;
      tmp_i2 = 0x77;
      tmp_c5 = local_424;
      do {
        tmp_i1 = (int)tmp_c5;
        if ((byte)(tmp_c5 + 0xbfU) < 0x1a) {
          tmp_i1 = tmp_c5 + 0x20;
        }
        tmp_u4 = tmp_i1 * tmp_i2 + tmp_u4;
        tmp_c5 = acStack_49a[tmp_i2];
        tmp_i2 = tmp_i2 + 1;
      } while (tmp_c5 != '\0');
      tmp_pu3 = &menuParseKeywordHash + ((tmp_u4 ^ (int)tmp_u4 >> 10 ^ (int)tmp_u4 >> 0x14) & 0x1ff);
    }
    for (tmp_pu3 = (uint32_t *)*tmp_pu3; tmp_pu3 != (uint32_t *)0x0;
        tmp_pu3 = (uint32_t *)tmp_pu3[2]) {
      local_45c = *tmp_pu3;
      uStack_460 = 0x101725;
      local_458 = &local_424;
      tmp_i2 = Q_stricmp();
      if (tmp_i2 == 0) {
        local_458 = (char *)param_1;
        local_45c = param_2;
        uStack_460 = 0x101741;
        tmp_i2 = (*(void *)tmp_pu3[1])();
        local_458 = (char *)local_444;
        if (tmp_i2 == 0) {
          local_458 = "couldn\'t parse menu keyword %s";
          local_45c = param_1;
          uStack_460 = 0x10176a;
          local_454 = &local_424;
          local_444 = (uint32_t *)tmp_i2;
          PC_SourceError();
          return (int)local_444;
        }
        goto joined_r0x0010166d;
      }
    }
    local_45c = param_1;
    uStack_460 = 0x101793;
    local_458 = local_440;
    local_454 = &local_424;
    PC_SourceError();
    local_458 = (char *)local_444;
  } while( true );
}

void Menu_New(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  uint32_t *tmp_pu7;
  
  tmp_i1 = menuCount;
  if (menuCount < 0x100) {
    tmp_i5 = menuCount * 0xd18;
    tmp_pu6 = &Menus + menuCount * 0x346;
    tmp_pu7 = tmp_pu6;
    for (tmp_i4 = 0x346; tmp_i2 = DC, tmp_i4 != 0; tmp_i4 = tmp_i4 + -1) {
      *tmp_pu7 = 0;
      tmp_pu7 = tmp_pu7 + 1;
    }
    tmp_i4 = tmp_i1 * 0xd18;
    (&g_unk_040f9008)[tmp_i1 * 0x346] = 0xffffffff;
    *(uint32_t *)(&g_unk_040f9014 + tmp_i4) = *(uint32_t *)(tmp_i2 + 0x1e32c);
    *(uint32_t *)(&g_unk_040f9010 + tmp_i4) = *(uint32_t *)(tmp_i2 + 0x1e324);
    *(uint32_t *)(&g_unk_040f900c + tmp_i4) = *(uint32_t *)(tmp_i2 + 0x1e328);
    *(uint32_t *)(&g_unk_040f9c54 + tmp_i4) = 0;
    tmp_u3 = 0;
    do {
      *(uint32_t *)((int)tmp_pu6 + tmp_u3) = 0;
      *(uint32_t *)((int)&g_unk_040f8f44 + tmp_u3 + tmp_i5) = 0;
      tmp_u3 = tmp_u3 + 8;
    } while (tmp_u3 < 0xb8);
    *(uint32_t *)(&g_unk_040f8f84 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_unk_040f8fc0 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_unk_040f8fbc + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_unk_040f8fb8 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_unk_040f8fb4 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_unk_040f8f70 + tmp_i5) = 0xffffffff;
    tmp_i4 = Menu_Parse(param_1,tmp_pu6);
    if (tmp_i4 != 0) {
      if ((&g_unk_040f8ffc)[tmp_i1 * 0x346] != 0) {
        (&Menus)[tmp_i1 * 0x346] = 0;
        (&g_unk_040f8f44)[tmp_i1 * 0x346] = 0;
        (&g_unk_040f8f48)[tmp_i1 * 0x346] = 0x44200000;
        (&g_unk_040f8f4c)[tmp_i1 * 0x346] = 0x43f00000;
      }
      Menu_UpdatePosition(tmp_pu6);
      menuCount = menuCount + 1;
    }
  }
  else {
    trap_Print("^3UI WARNING: Reached MAX_MENUS\n");
  }
  return;
}

uint32_t Menu_Count(void)
{
  return menuCount;
}

uint32_t * Menu_Get(int param_1)
{
  if ((-1 < param_1) && (param_1 < menuCount)) {
    return &Menus + param_1 * 0x346;
  }
  return (uint32_t *)0x0;
}

void Menu_PaintAll(void)
{
  void *tmp_pc1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  uint32_t *tmp_pu7;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x101ac9;
  if (captureFunc != (void *)0x0) {
    (*captureFunc)(captureData);
  }
  if (0 < menuCount) {
    tmp_pu6 = &Menus;
    tmp_i5 = 0;
    tmp_i3 = menuCount;
    tmp_pu7 = tmp_pu6;
    do {
      while ((((tmp_pu7[0x12] & 0x2000000) != 0 || ((tmp_pu7[0x12] & 4) == 0)) ||
             ((tmp_pu7[0x10] != 0 &&
              ((*(void **)(DC + 100) != (void *)0x0 &&
               (tmp_i2 = (**(void **)(DC + 100))(tmp_pu7[0x10]), tmp_i3 = menuCount, tmp_i2 == 0)))))))
      {
        tmp_i5 = tmp_i5 + 1;
        tmp_pu7 = tmp_pu7 + 0x346;
        if (tmp_i3 <= tmp_i5) goto LAB_00101b5e;
      }
      Menu_Paint_part_20();
      tmp_i5 = tmp_i5 + 1;
      tmp_pu7 = tmp_pu7 + 0x346;
      tmp_i3 = menuCount;
    } while (tmp_i5 < menuCount);
LAB_00101b5e:
    if (0 < tmp_i3) {
      tmp_i5 = 0;
      do {
        while ((tmp_pu6[0x12] & 0x2000004) != 0x2000004) {
LAB_00101b80:
          tmp_i5 = tmp_i5 + 1;
          tmp_pu6 = tmp_pu6 + 0x346;
          if (tmp_i3 <= tmp_i5) goto LAB_00101bd0;
        }
        if (((tmp_pu6[0x10] == 0) || (*(void **)(DC + 100) == (void *)0x0)) ||
           (tmp_i3 = (**(void **)(DC + 100))(tmp_pu6[0x10]), tmp_i3 != 0)) {
          Menu_Paint_part_20();
          tmp_i3 = menuCount;
          goto LAB_00101b80;
        }
        tmp_i5 = tmp_i5 + 1;
        tmp_pu6 = tmp_pu6 + 0x346;
        tmp_i3 = menuCount;
      } while (tmp_i5 < menuCount);
    }
  }
LAB_00101bd0:
  if (debugMode != 0) {
    local_2c = 0x3f800000;
    local_28 = 0x3f800000;
    local_24 = 0x3f800000;
    local_20 = 0x3f800000;
    (**(void **)(DC + 0x30))(2);
    tmp_pc1 = *(void **)(DC + 0x10);
    tmp_u4 = va("fps: %.2f",(double)*(float *)(DC + 0x2005c));
    (*tmp_pc1)(0x40a00000,0x41200000,0x3e4ccccd,&local_2c,tmp_u4,0,0,0);
    tmp_pc1 = *(void **)(DC + 0x10);
    tmp_u4 = va("mouse: %i %i",*(uint32_t *)(DC + 0x124),*(uint32_t *)(DC + 0x128));
    (*tmp_pc1)(0x40a00000,0x41a00000,0x3e4ccccd,&local_2c,tmp_u4,0,0,0);
  }
  return;
}

void Menu_Reset(void)
{
  menuCount = 0;
  return;
}

uint32_t Display_GetContext(void)
{
  return DC;
}

uint32_t * Display_CaptureItem(int param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float *pfVar4;
  int tmp_i5;
  
  if (0 < menuCount) {
    tmp_f3 = (float)param_2;
    tmp_f2 = (float)param_1;
    pfVar4 = (float *)&Menus;
    if (*(float *)(DC + 0x2003c) <= 1.3333334) {
      tmp_i5 = 0;
      do {
        if ((((*pfVar4 < tmp_f2) && (tmp_f2 < *pfVar4 + pfVar4[2])) && (pfVar4[1] < tmp_f3)) &&
           (tmp_f3 < pfVar4[1] + pfVar4[3])) goto LAB_00101e44;
        tmp_i5 = tmp_i5 + 1;
        pfVar4 = pfVar4 + 0x346;
      } while (tmp_i5 != menuCount);
    }
    else {
      tmp_f1 = *(float *)(DC + 0x2003c) * 0.75;
      tmp_i5 = 0;
      do {
        if (((tmp_f1 * *pfVar4 < tmp_f2 * tmp_f1) && (tmp_f2 * tmp_f1 < (*pfVar4 + pfVar4[2]) * tmp_f1))
           && ((pfVar4[1] < tmp_f3 && (tmp_f3 < pfVar4[1] + pfVar4[3])))) {
LAB_00101e44:
          return &Menus + tmp_i5 * 0x346;
        }
        tmp_i5 = tmp_i5 + 1;
        pfVar4 = pfVar4 + 0x346;
      } while (tmp_i5 != menuCount);
    }
  }
  return (uint32_t *)0x0;
}

uint32_t Display_MouseMove(float *param_1,int param_2,int param_3)
{
  int tmp_i1;
  uint tmp_u2;
  uint *tmp_pu3;
  uint32_t *tmp_pu4;
  
  if (param_1 == (float *)0x0) {
    if (0 < menuCount) {
      if ((g_unk_040f8f88 & 6) == 6) {
        tmp_i1 = 0;
        tmp_u2 = g_unk_040f8f88;
      }
      else {
        tmp_pu3 = &g_unk_040f9ca0;
        tmp_i1 = 0;
        do {
          tmp_i1 = tmp_i1 + 1;
          if (tmp_i1 == menuCount) goto LAB_00101ecf;
          tmp_u2 = *tmp_pu3;
          tmp_pu3 = tmp_pu3 + 0x346;
        } while ((tmp_u2 & 6) != 6);
      }
      if ((tmp_u2 & 0x200000) == 0) {
LAB_00101ecf:
        tmp_i1 = 0;
        tmp_pu4 = &Menus;
        do {
          tmp_i1 = tmp_i1 + 1;
          Menu_HandleMouseMove(tmp_pu4,(float)param_2,(float)param_3);
          tmp_pu4 = tmp_pu4 + 0x346;
        } while (tmp_i1 < menuCount);
        return 1;
      }
      Menu_HandleMouseMove(&Menus + tmp_i1 * 0x346,(float)param_2,(float)param_3);
    }
  }
  else {
    *param_1 = (float)param_2 + *param_1;
    param_1[1] = (float)param_3 + param_1[1];
    Menu_UpdatePosition(param_1);
  }
  return 1;
}

uint32_t Display_CursorType(int param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float *pfVar4;
  int tmp_i5;
  
  if (0 < menuCount) {
    tmp_f3 = (float)param_2;
    tmp_f2 = (float)param_1;
    pfVar4 = (float *)&Menus;
    if (*(float *)(DC + 0x2003c) <= 1.3333334) {
      tmp_i5 = 0;
      do {
        if ((((*pfVar4 - 3.0 < tmp_f2) && (tmp_f2 < (*pfVar4 - 3.0) + 7.0)) &&
            (pfVar4[1] - 3.0 < tmp_f3)) && (tmp_f3 < (pfVar4[1] - 3.0) + 7.0)) {
          return 4;
        }
        tmp_i5 = tmp_i5 + 1;
        pfVar4 = pfVar4 + 0x346;
      } while (tmp_i5 != menuCount);
    }
    else {
      tmp_f1 = *(float *)(DC + 0x2003c) * 0.75;
      tmp_i5 = 0;
      do {
        if ((((*pfVar4 - 3.0) * tmp_f1 < tmp_f2 * tmp_f1) &&
            (tmp_f2 * tmp_f1 < ((*pfVar4 - 3.0) + 7.0) * tmp_f1)) &&
           ((pfVar4[1] - 3.0 < tmp_f3 && (tmp_f3 < (pfVar4[1] - 3.0) + 7.0)))) {
          return 4;
        }
        tmp_i5 = tmp_i5 + 1;
        pfVar4 = pfVar4 + 0x346;
      } while (tmp_i5 != menuCount);
    }
  }
  return 2;
}

void Display_HandleKey(uint32_t param_1,uint32_t param_2,int param_3,int param_4)
{
  uint tmp_u1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  float *pfVar6;
  uint *tmp_pu7;
  
  if (menuCount < 1) {
    return;
  }
  pfVar6 = (float *)&Menus;
  tmp_f4 = (float)param_4;
  tmp_f3 = (float)param_3;
  if (*(float *)(DC + 0x2003c) <= 1.3333334) {
    tmp_i5 = 0;
    do {
      if ((((*pfVar6 < tmp_f3) && (tmp_f3 < *pfVar6 + pfVar6[2])) && (pfVar6[1] < tmp_f4)) &&
         (tmp_f4 < pfVar6[1] + pfVar6[3])) goto LAB_00102204;
      tmp_i5 = tmp_i5 + 1;
      pfVar6 = pfVar6 + 0x346;
    } while (tmp_i5 != menuCount);
  }
  else {
    tmp_f2 = *(float *)(DC + 0x2003c) * 0.75;
    tmp_i5 = 0;
    do {
      if (((tmp_f2 * *pfVar6 < tmp_f3 * tmp_f2) && (tmp_f3 * tmp_f2 < (*pfVar6 + pfVar6[2]) * tmp_f2)) &&
         ((pfVar6[1] < tmp_f4 && (tmp_f4 < pfVar6[1] + pfVar6[3])))) goto LAB_00102204;
      tmp_i5 = tmp_i5 + 1;
      pfVar6 = pfVar6 + 0x346;
    } while (tmp_i5 != menuCount);
  }
  if ((g_unk_040f8f88 & 6) != 6) {
    tmp_pu7 = &g_unk_040f9ca0;
    tmp_i5 = 0;
    do {
      tmp_i5 = tmp_i5 + 1;
      if (tmp_i5 == menuCount) {
        return;
      }
      tmp_u1 = *tmp_pu7;
      tmp_pu7 = tmp_pu7 + 0x346;
    } while ((tmp_u1 & 6) != 6);
  }
LAB_00102204:
  Menu_HandleKey();
  return;
}

void Display_CacheAll(void)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  int tmp_i7;
  
  if (0 < menuCount) {
    tmp_pu5 = &Menus;
    tmp_i7 = 0;
    do {
      if (tmp_pu5[0xb] != 0) {
        tmp_u3 = (**(void **)(DC + 0xe8))(tmp_pu5[0xb],0,0,0,0);
        (**(void **)(DC + 0xec))(tmp_u3);
      }
      tmp_i4 = tmp_pu5[0x30];
      if (0 < tmp_i4) {
        tmp_i6 = 0;
        do {
          if ((tmp_pu5[tmp_i6 + 0x145] != 0) &&
             (tmp_i1 = *(int *)(tmp_pu5[tmp_i6 + 0x145] + 0x2c), tmp_i1 != 0)) {
            tmp_u3 = (**(void **)(DC + 0xe8))(tmp_i1,0,0,0,0);
            (**(void **)(DC + 0xec))(tmp_u3);
            tmp_i4 = tmp_pu5[0x30];
          }
          tmp_i6 = tmp_i6 + 1;
        } while (tmp_i6 < tmp_i4);
      }
      tmp_pc2 = (char *)tmp_pu5[0x13c];
      if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
        (**(void **)(DC + 0xdc))(tmp_pc2,1);
      }
      tmp_i7 = tmp_i7 + 1;
      tmp_pu5 = tmp_pu5 + 0x346;
    } while (tmp_i7 < menuCount);
  }
  return;
}

void C_PanelButtonsSetup(int *param_1,float param_2)
{
  int tmp_i1;
  
  if (param_2 != 0.0) {
    for (; tmp_i1 = *param_1, tmp_i1 != 0; param_1 = param_1 + 1) {
      *(float *)(tmp_i1 + 8) = *(float *)(tmp_i1 + 8) + param_2;
    }
  }
  return;
}

void WM_DrawClientScoreDM(int param_1,int param_2,int *param_3,uint32_t param_4,float param_5)
{
  float tmp_f1;
  bool tmp_b2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  int tmp_i5;
  uint32_t tmp_u6;
  char tmp_c7;
  uint32_t tmp_u8;
  int tmp_i9;
  float local_48;
  float local_44;
  int local_40;
  int local_38;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  
  if (0x1c5 < param_2) {
    return;
  }
  tmp_i9 = *param_3;
  if (tmp_i9 == *(int *)(g_unk_01047b00 + 0xcc)) {
    local_20 = param_5 * 0.3;
    local_2c = 0x3f000000;
    local_28 = 0x3f000000;
    local_24 = 0x3e4ccccd;
    CG_FillRect((float)(param_1 + -5),(float)param_2,0x44188000,0x41700000,&local_2c);
  }
  tmp_f1 = (float)param_1;
  local_2c = 0x3f800000;
  local_28 = 0x3f800000;
  local_20 = param_5;
  local_24 = 0x3f800000;
  if ((param_3[2] == 999) || (param_3[2] == -1)) {
    local_44 = 1.68156e-44;
    tmp_u3 = 0xe;
    local_48 = 0.0;
    tmp_u8 = 0x10;
    tmp_b2 = false;
    tmp_u6 = 0x12;
  }
  else {
    tmp_i5 = cf_draw(tmp_f1 - 10.0,(float)(param_2 + -10),param_5,
                    *(uint32_t *)(cgs + tmp_i9 * 0x1a4 + 0x9410));
    if (tmp_i5 == 0) {
      tmp_u3 = 0xe;
      local_44 = 1.68156e-44;
      tmp_u8 = 0x10;
      tmp_b2 = false;
      local_48 = 0.0;
      tmp_u6 = 0x12;
    }
    else {
      tmp_u3 = 0xc;
      local_44 = 3.92364e-44;
      tmp_u8 = 0xe;
      tmp_b2 = true;
      local_48 = 2.24208e-44;
      tmp_u6 = 0x10;
      tmp_f1 = tmp_f1 + 16.0;
    }
  }
  if ((*(byte *)(param_3 + 6) & 4) != 0) {
    CG_DrawPic(tmp_f1,(float)(param_2 + 2),0x41400000,0x41400000,GHIDRA_FIELD(cgs, 67964, 4));
    local_48 = local_44;
    tmp_f1 = tmp_f1 + 12.0;
    tmp_u6 = tmp_u8;
    tmp_u8 = tmp_u3;
  }
  local_44 = tmp_f1;
  if (*(int *)(cgs + tmp_i9 * 0x1a4 + 0x9494) != 3) {
    if (((*(byte *)(param_3 + 6) & 1) != 0) && (GHIDRA_FIELD(cgs, 33525356, 4) != 0)) {
      CG_DrawPic(tmp_f1,(float)(param_2 + 2),0x41400000,0x41400000,GHIDRA_FIELD(cgs, 131760, 4));
      local_48 = (float)((int)local_48 + 0xc);
      tmp_f1 = tmp_f1 + 12.0;
      tmp_u6 = tmp_u8;
      local_44 = tmp_f1;
      if (*(int *)(cgs + tmp_i9 * 0x1a4 + 0x9494) == 3) goto LAB_001051c5;
    }
    local_44 = tmp_f1;
    tmp_f1 = tmp_f1 + 14.0;
  }
LAB_001051c5:
  local_38 = tmp_i9 * 0x1a4 + 0x10f9274;
  local_40 = param_2 + 1;
  CG_DrawStringExt((int)ROUND(tmp_f1),param_2 + 1,local_38,&local_2c,0,1,7,0xe,tmp_u6);
  CG_DrawStrlen(local_38);
  local_48 = (float)(0xd2 - (int)local_48) + (local_44 - 14.0);
  if (*(int *)(cgs + tmp_i9 * 0x1a4 + 0x9494) != 3) {
    tmp_u6 = va(&g_unk_0011cbcf,param_3[8],param_3[9]);
    CG_DrawStringExt((int)ROUND(local_48),local_40,tmp_u6,&local_2c,0,1,7,0xe,0);
    if (*(int *)(cgs + tmp_i9 * 0x1a4 + 0x9494) != 3) {
      tmp_u6 = va("^7%3i",param_3[1]);
      CG_DrawStringExt((int)ROUND((local_48 + 116.0) - 2.0),param_2,tmp_u6,&local_2c,0,1,7,0xe,0);
      tmp_f1 = local_48 + 116.0 + 260.0;
      if ((*(byte *)(param_3 + 6) & 2) == 0) {
        tmp_i9 = param_3[2];
        if (tmp_i9 != -1) {
          tmp_c7 = '\a';
          if (((GHIDRA_FIELD(cg_pingColors, 12, 4) != 0) && (tmp_c7 = '\x02', 100 < tmp_i9)) &&
             (tmp_c7 = '\x03', 99 < tmp_i9 - 0x65U)) {
            tmp_c7 = (-(tmp_i9 - 0xc9U < 0x96) & 7U) + 1;
          }
          tmp_u6 = va("^%i%4i^7",tmp_c7,tmp_i9);
          CG_DrawStringExt((int)ROUND(tmp_f1),param_2,tmp_u6,&local_2c,0,1,7,0xe,0);
          return;
        }
        tmp_pc4 = "^2CONN.^7";
      }
      else {
        tmp_pc4 = "^7 BOT";
      }
      goto LAB_001053f0;
    }
  }
  if (!tmp_b2) {
    local_48 = local_48 + 16.0;
  }
  if (param_3[2] == -1) {
    tmp_pc4 = "^3CONNECTING";
  }
  else {
    tmp_i9 = tmp_i9 * 0x1a4;
    if (*(int *)(cgs + tmp_i9 + 0x95ac) == 0) {
      if (*(int *)(cgs + tmp_i9 + 0x95a8) == 0) {
        tmp_pc4 = "^3SPECTATOR";
      }
      else {
        tmp_pc4 = "^3SHOUTCASTER";
      }
    }
    else {
      if (*(int *)(cgs + tmp_i9 + 0x95a8) == 0) {
        tmp_pc4 = "^3SPECTATOR";
      }
      else {
        tmp_pc4 = "^3SHOUTCASTER";
      }
      tmp_pc4 = (char *)va("^5TV^7|^3%s",tmp_pc4 + 2);
    }
  }
  tmp_i9 = CG_DrawStrlen(tmp_pc4);
  tmp_f1 = (local_48 + 400.0) - (float)(tmp_i9 * 8 + -1);
LAB_001053f0:
  CG_DrawStringExt((int)ROUND(tmp_f1),param_2,tmp_pc4,&local_2c,0,1,7,0xe,0);
  return;
}

