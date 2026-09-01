/**
 * @file ui_ui_draw.c
 * @brief ui_draw
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 */

#include "ui_types.h"
#include "ui_globals.h"
#include "ui_imports.h"
#include "ui_ui_draw.h"

void GradientBar_Paint(uint32_t *param_1,uint32_t param_2) {
  (**(void **)(DC + 4))(param_2);
  (**(void **)(DC + 8))(*param_1,param_1[1],param_1[2],param_1[3],*(uint32_t *)(DC + 0x1e2d8));
  (**(void **)(DC + 4))(0);
  return;
}

uint32_t ItemParse_maxPaintChars(int param_1,uint32_t param_2) {
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

bool ItemParse_ownerdraw(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x3c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 200) = 8;
  }
  return tmp_i1 != 0;
}

bool ItemParse_ownerdrawFlag(int param_1,uint32_t param_2) {
  int tmp_i1;
  uint local_10 [2];

  local_10[0] = 0;
  tmp_i1 = PC_Int_Parse(param_2,local_10);
  if (tmp_i1 != 0) {
    *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | local_10[0];
  }
  return tmp_i1 != 0;
}

uint32_t MenuParse_drawAlwaysOnTop(int param_1) {
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x2000000;
  return 1;
}

bool MenuParse_ownerdraw(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x3c);
  return tmp_i1 != 0;
}

bool MenuParse_ownerdrawFlag(int param_1,uint32_t param_2) {
  int tmp_i1;
  uint local_10 [2];

  local_10[0] = 0;
  tmp_i1 = PC_Int_Parse(param_2,local_10);
  if (tmp_i1 != 0) {
    *(uint *)(param_1 + 0x40) = *(uint *)(param_1 + 0x40) | local_10[0];
  }
  return tmp_i1 != 0;
}

void Text_PaintCenter(float param_1,uint32_t param_2,float param_3,uint32_t param_4,
                     byte *param_5) {
  byte tmp_b1;
  float tmp_f2;
  int tmp_i3;
  size_t tmp_s4;
  byte *tmp_pb5;
  int tmp_i6;
  int tmp_i7;

  tmp_i3 = g_dat_003e7e2c;
  tmp_i6 = g_dat_003e7e2c * 0x5044;
  if (param_5 == (byte *)0x0) {
    tmp_f2 = 0.0;
  }
  else {
    tmp_i7 = 0;
    tmp_s4 = strlen((char *)param_5);
    tmp_f2 = 0.0;
    tmp_pb5 = param_5;
    do {
      while( true ) {
        tmp_b1 = *tmp_pb5;
        if ((tmp_b1 == 0) || ((int)tmp_s4 <= tmp_i7)) goto LAB_00038780;
        if ((tmp_b1 != 0x5e) || ((tmp_pb5[1] == 0 || (tmp_pb5[1] == 0x5e)))) break;
        tmp_pb5 = tmp_pb5 + 2;
        if (tmp_pb5 == (byte *)0x0) goto LAB_00038780;
      }
      tmp_pb5 = tmp_pb5 + 1;
      tmp_i7 = tmp_i7 + 1;
      tmp_f2 = (float)*(int *)(&g_dat_0039800c + (uint)tmp_b1 * 0x50 + tmp_i6) + tmp_f2;
    } while (tmp_pb5 != (byte *)0x0);
  }
LAB_00038780:
  Text_Paint_Ext(param_1 - (float)(int)ROUND(param_3 * tmp_f2 *
                                             *(float *)(&g_dat_0039cffc + tmp_i3 * 0x5044)) * 0.5,
                 param_2,param_3,param_3,param_4,param_5,0,0,6,&g_dat_00397ffc + tmp_i6);
  return;
}

void UI_DrawCampaignDescription
               (float *param_1,float param_2,uint32_t param_3,float param_4,uint32_t param_5,
               uint32_t param_6,int param_7,int param_8) {
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  size_t tmp_s4;
  uint tmp_u5;
  float tmp_f6;
  byte tmp_b7;
  byte *tmp_pb8;
  char *__s;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  float local_444;
  float local_43c;
  byte *local_438;
  float local_430;
  byte local_41c [1032];
  uint32_t uStack_14;

  uStack_14 = 0x2e509;
  if (ui_netGameType._12_4_ == 4) {
    tmp_i9 = ui_currentNetMap._12_4_;
    if (param_8 == 0) {
      tmp_i9 = ui_currentMap._12_4_;
    }
    __s = *(char **)(&g_dat_003cab7c + tmp_i9 * 0x74);
  }
  else if (ui_netGameType._12_4_ == 5) {
    tmp_i9 = ui_currentNetMap._12_4_;
    if (param_8 == 0) {
      tmp_i9 = ui_currentMap._12_4_;
    }
    __s = *(char **)(&g_dat_003babe8 + tmp_i9 * 0x80);
  }
  else {
    tmp_i9 = ui_currentNetMap._12_4_;
    if (param_8 == 0) {
      tmp_i9 = ui_currentMap._12_4_;
    }
    __s = *(char **)(&g_dat_003babe4 + tmp_i9 * 0x80);
  }
  if (((byte *)__s == (byte *)0x0) || (*__s == 0)) {
    tmp_u5 = 0x5e;
    tmp_s4 = 0x12;
    __s = "^1No text supplied";
  }
  else {
    tmp_u5 = (uint)(byte)*__s;
    tmp_s4 = strlen(__s);
    tmp_u5 = tmp_u5 & 0xff;
  }
  tmp_f2 = 0.0;
  tmp_i9 = 0;
  tmp_pb8 = (byte *)__s;
  while (((char)tmp_u5 != '\0' && (tmp_i9 < (int)tmp_s4))) {
    if (((char)tmp_u5 == '^') && ((tmp_pb8[1] != 0 && (tmp_pb8[1] != 0x5e)))) {
      tmp_pb8 = tmp_pb8 + 2;
    }
    else {
      tmp_f1 = (float)*(int *)(&g_dat_00397ffc + tmp_u5 * 0x50 + g_dat_003e7e2c * 0x5044);
      if ((float)*(int *)(&g_dat_00397ffc + tmp_u5 * 0x50 + g_dat_003e7e2c * 0x5044) <= tmp_f2) {
        tmp_f1 = tmp_f2;
      }
      tmp_pb8 = tmp_pb8 + 1;
      tmp_i9 = tmp_i9 + 1;
      tmp_f2 = tmp_f1;
    }
    if (tmp_pb8 == (byte *)0x0) break;
    tmp_u5 = (uint)*tmp_pb8;
  }
  local_444 = 0.0;
  local_41c[0] = 0;
  local_438 = (byte *)0x0;
  tmp_f1 = *(float *)(&g_dat_0039cffc + g_dat_003e7e2c * 0x5044);
  tmp_i11 = 0;
  local_430 = 0.0;
  local_43c = 0.0;
  tmp_i9 = 0;
  do {
    tmp_f6 = (float)(**(void **)(DC + 0x18))(local_41c,param_2,0);
    tmp_b7 = *__s;
    if (((tmp_b7 & 0xdf) == 0 || tmp_b7 == 0x2a) || ((byte)(tmp_b7 - 9) < 2)) {
      local_438 = (byte *)(__s + 1);
      tmp_i11 = tmp_i9;
      local_444 = tmp_f6;
    }
    if ((((tmp_i11 != 0) && (tmp_f3 = (float)(int)tmp_f6, tmp_f6 = param_1[2], tmp_f6 < tmp_f3)) ||
        ((tmp_b7 & 0xdf) == 10)) || (tmp_b7 == 0)) {
      if (tmp_i9 != 0) {
        if (param_7 == 0) {
          local_430 = param_4;
        }
        else if (param_7 == 2) {
          local_430 = param_4 - (float)(int)local_444;
        }
        else if (param_7 == 1) {
          local_430 = param_4 - (float)(int)local_444 * 0.5;
        }
        local_41c[tmp_i11] = 0;
        local_430 = local_430 + *param_1;
        (**(void **)(DC + 0x10))
                  (local_430,local_43c + param_1[1],param_2,param_3,local_41c,0,0,param_6,tmp_f6);
        tmp_b7 = *__s;
      }
      if (tmp_b7 == 0) {
        return;
      }
      tmp_i11 = 0;
      local_43c = (float)((int)ROUND(tmp_f2 * param_2 * tmp_f1) + 5) + local_43c;
      tmp_i10 = 0;
      local_444 = 0.0;
      __s = (char *)local_438;
    }
    else {
      tmp_i10 = tmp_i9 + 1;
      if (tmp_b7 == 0xd) {
        local_41c[tmp_i9] = 0x20;
      }
      else {
        local_41c[tmp_i9] = tmp_b7;
      }
      local_41c[tmp_i9 + 1] = 0;
      __s = __s + 1;
    }
    tmp_i9 = tmp_i10;
    if ((byte *)__s == (byte *)0x0) {
      return;
    }
  } while( true );
}

void UI_DrawConnectScreen(int param_1) {
  if (param_1 == 0) {
    UI_DrawLoadPanel(0,0,0);
  }
  return;
}

void UI_DrawGametypeDescription
               (float *param_1,float param_2,uint32_t param_3,float param_4,uint32_t param_5,
               uint32_t param_6,int param_7) {
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  size_t tmp_s4;
  byte tmp_b5;
  int tmp_i6;
  byte *tmp_pb7;
  char *__s;
  int tmp_i8;
  int local_440;
  byte *local_43c;
  float local_438;
  float local_434;
  byte local_41c [1032];
  uint32_t uStack_14;

  tmp_i8 = g_dat_003e7e2c;
  uStack_14 = 0x2e909;
  if (g_dat_003b8b48 < 1) {
    tmp_i6 = 0;
  }
  else {
    if (g_dat_003b8b54 == ui_netGameType._12_4_) {
      tmp_i6 = 0;
LAB_0002eda0:
      __s = (char *)(&g_dat_00397ed8)[(tmp_i6 + 0x20c8) * 4];
      if ((byte *)__s == (byte *)0x0) {
        return;
      }
      tmp_s4 = strlen(__s);
      goto LAB_0002ea98;
    }
    if (g_dat_003b8b48 == 1) {
      tmp_i6 = 1;
    }
    else {
      if (g_dat_003b8b64 == ui_netGameType._12_4_) {
        tmp_i6 = 1;
        goto LAB_0002eda0;
      }
      if (g_dat_003b8b48 == 2) {
        tmp_i6 = 2;
      }
      else {
        if (g_dat_003b8b74 == ui_netGameType._12_4_) {
          tmp_i6 = 2;
          goto LAB_0002eda0;
        }
        if (g_dat_003b8b48 == 3) {
          tmp_i6 = 3;
        }
        else {
          if (g_dat_003b8b84 == ui_netGameType._12_4_) {
            tmp_i6 = 3;
            goto LAB_0002eda0;
          }
          if (g_dat_003b8b48 == 4) {
            tmp_i6 = 4;
          }
          else {
            if (g_dat_003b8b94 == ui_netGameType._12_4_) {
              tmp_i6 = 4;
              goto LAB_0002eda0;
            }
            if (g_dat_003b8b48 == 5) {
              tmp_i6 = 5;
            }
            else {
              if (g_dat_003b8ba4 == ui_netGameType._12_4_) {
                tmp_i6 = 5;
                goto LAB_0002eda0;
              }
              if (g_dat_003b8b48 == 6) {
                tmp_i6 = 6;
              }
              else {
                if (g_dat_003b8bb4 == ui_netGameType._12_4_) {
                  tmp_i6 = 6;
                  goto LAB_0002eda0;
                }
                if (g_dat_003b8b48 == 7) {
                  tmp_i6 = 7;
                }
                else {
                  if (g_dat_003b8bc4 == ui_netGameType._12_4_) {
                    tmp_i6 = 7;
                    goto LAB_0002eda0;
                  }
                  if (g_dat_003b8b48 == 8) {
                    tmp_i6 = 8;
                  }
                  else {
                    if (g_dat_003b8bd4 == ui_netGameType._12_4_) {
                      tmp_i6 = 8;
                      goto LAB_0002eda0;
                    }
                    if (g_dat_003b8b48 == 9) {
                      tmp_i6 = 9;
                    }
                    else {
                      if (g_dat_003b8be4 == ui_netGameType._12_4_) {
                        tmp_i6 = 9;
                        goto LAB_0002eda0;
                      }
                      if (g_dat_003b8b48 == 10) {
                        tmp_i6 = 10;
                      }
                      else {
                        if (g_dat_003b8bf4 == ui_netGameType._12_4_) {
                          tmp_i6 = 10;
                          goto LAB_0002eda0;
                        }
                        if (g_dat_003b8b48 == 0xb) {
                          tmp_i6 = 0xb;
                        }
                        else {
                          if (g_dat_003b8c04 == ui_netGameType._12_4_) {
                            tmp_i6 = 0xb;
                            goto LAB_0002eda0;
                          }
                          if (g_dat_003b8b48 == 0xc) {
                            tmp_i6 = 0xc;
                          }
                          else {
                            if (g_dat_003b8c14 == ui_netGameType._12_4_) {
                              tmp_i6 = 0xc;
                              goto LAB_0002eda0;
                            }
                            if (g_dat_003b8b48 == 0xd) {
                              tmp_i6 = 0xd;
                            }
                            else {
                              if (g_dat_003b8c24 == ui_netGameType._12_4_) {
                                tmp_i6 = 0xd;
                                goto LAB_0002eda0;
                              }
                              if (g_dat_003b8b48 == 0xe) {
                                tmp_i6 = 0xe;
                              }
                              else {
                                if (g_dat_003b8c34 == ui_netGameType._12_4_) {
                                  tmp_i6 = 0xe;
                                  goto LAB_0002eda0;
                                }
                                if (g_dat_003b8b48 == 0xf) {
                                  tmp_i6 = 0xf;
                                }
                                else {
                                  if (g_dat_003b8c44 == ui_netGameType._12_4_) {
                                    tmp_i6 = 0xf;
                                    goto LAB_0002eda0;
                                  }
                                  tmp_i6 = 0x10;
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
  if (tmp_i6 != g_dat_003b8b48) {
    return;
  }
  tmp_s4 = 7;
  __s = "Unknown";
LAB_0002ea98:
  tmp_i6 = 0;
  tmp_f2 = 0.0;
  tmp_pb7 = (byte *)__s;
  do {
    while( true ) {
      tmp_b5 = *tmp_pb7;
      if ((tmp_b5 == 0) || ((int)tmp_s4 <= tmp_i6)) goto LAB_0002eb00;
      if ((tmp_b5 != 0x5e) || ((tmp_pb7[1] == 0 || (tmp_pb7[1] == 0x5e)))) break;
      tmp_pb7 = tmp_pb7 + 2;
      if (tmp_pb7 == (byte *)0x0) goto LAB_0002eb00;
    }
    tmp_f1 = (float)*(int *)(&g_dat_00397ffc + (uint)tmp_b5 * 0x50 + tmp_i8 * 0x5044);
    if ((float)*(int *)(&g_dat_00397ffc + (uint)tmp_b5 * 0x50 + tmp_i8 * 0x5044) <= tmp_f2) {
      tmp_f1 = tmp_f2;
    }
    tmp_f2 = tmp_f1;
    tmp_pb7 = tmp_pb7 + 1;
    tmp_i6 = tmp_i6 + 1;
  } while (tmp_pb7 != (byte *)0x0);
LAB_0002eb00:
  local_43c = (byte *)0x0;
  local_41c[0] = 0;
  local_440 = 0;
  tmp_f1 = *(float *)(&g_dat_0039cffc + tmp_i8 * 0x5044);
  tmp_i6 = 0;
  local_434 = 0.0;
  local_438 = 0.0;
  tmp_i8 = 0;
  do {
    tmp_i3 = (**(void **)(DC + 0x18))(local_41c,param_2,0);
    tmp_b5 = *__s;
    if (((byte)(tmp_b5 - 9) < 2) || ((tmp_b5 & 0xdf) == 0)) {
      local_43c = (byte *)(__s + 1);
      tmp_i6 = tmp_i8;
      local_440 = tmp_i3;
LAB_0002ebb0:
      if (tmp_i6 == 0) {
LAB_0002ebd2:
        if ((tmp_b5 == 10) || (tmp_b5 == 0)) goto LAB_0002ec30;
        if (tmp_b5 != 0x2a) {
          if (tmp_b5 == 0xd) {
            local_41c[tmp_i8] = 0x20;
          }
          else {
            local_41c[tmp_i8] = tmp_b5;
          }
          goto LAB_0002ebf9;
        }
        if (__s[1] != 0x2a) goto LAB_0002ed16;
        if (tmp_i8 == 0) goto LAB_0002ecd3;
LAB_0002ec38:
        if (param_7 == 0) {
          local_434 = param_4;
        }
        else if (param_7 == 2) {
          local_434 = param_4 - (float)local_440;
        }
        else if (param_7 == 1) {
          local_434 = param_4 - (float)local_440 * 0.5;
        }
        local_41c[tmp_i6] = 0;
        local_434 = local_434 + *param_1;
        (**(void **)(DC + 0x10))
                  (local_434,local_438 + param_1[1],param_2,param_3,local_41c,0,0,param_6);
        tmp_b5 = *__s;
      }
      else {
LAB_0002ebb4:
        if ((float)tmp_i3 <= param_1[2]) goto LAB_0002ebd2;
LAB_0002ec30:
        if (tmp_i8 != 0) goto LAB_0002ec38;
      }
      if (tmp_b5 == 0) {
        return;
      }
LAB_0002ecd3:
      tmp_i6 = 0;
      local_438 = (float)((int)ROUND(tmp_f2 * param_2 * tmp_f1) + 5) + local_438;
      tmp_i3 = 0;
      local_440 = 0;
      __s = (char *)local_43c;
    }
    else {
      if (tmp_b5 != 0x2a) goto LAB_0002ebb0;
      if (__s[1] == 0x2a) {
        local_43c = (byte *)(__s + 2);
        tmp_i6 = tmp_i8;
        local_440 = tmp_i3;
        if (tmp_i8 != 0) goto LAB_0002ebb4;
        goto LAB_0002ecd3;
      }
      if (tmp_i6 != 0) goto LAB_0002ebb4;
LAB_0002ed16:
      local_41c[tmp_i8] = 0x2a;
LAB_0002ebf9:
      tmp_i3 = tmp_i8 + 1;
      local_41c[tmp_i8 + 1] = 0;
      __s = __s + 1;
    }
    tmp_i8 = tmp_i3;
    if ((byte *)__s == (byte *)0x0) {
      return;
    }
  } while( true );
}

void UI_DrawHandlePic(float param_1,float param_2,float param_3,float param_4,uint32_t param_5) {
  uint32_t tmp_u1;
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

void UI_DrawMapCinematic(float *param_1,uint32_t param_2,uint32_t param_3,int param_4) {
  int *tmp_pi1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;

  tmp_i4 = ui_currentNetMap._12_4_;
  tmp_i3 = ui_netGameType._12_4_;
  if (param_4 == 0) {
    tmp_i4 = ui_currentMap._12_4_;
    tmp_i3 = (&g_dat_00397ed4)[(ui_gameType._12_4_ + 0x20c8) * 4];
  }
  if (tmp_i3 == 4) {
    if ((tmp_i4 < 0) || (g_dat_003cab70 < tmp_i4)) {
      if (param_4 == 0) {
        ui_currentMap._12_4_ = 0;
        trap_Cvar_Set("ui_currentMap","0");
      }
      else {
        ui_currentNetMap._12_4_ = 0;
        trap_Cvar_Set("ui_currentNetMap","0");
      }
    }
  }
  else {
    if ((tmp_i4 < 0) || (g_dat_003bab6c < tmp_i4)) {
      if (param_4 == 0) {
        tmp_i4 = 0;
        ui_currentMap._12_4_ = 0;
        trap_Cvar_Set("ui_currentMap","0");
      }
      else {
        ui_currentNetMap._12_4_ = 0;
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

void UI_DrawMapPreview(float *param_1,float param_2,uint32_t param_3,int param_4) {
  float tmp_f1;
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

  tmp_i10 = ui_currentNetMap._12_4_;
  tmp_i8 = ui_netGameType._12_4_;
  if (param_4 == 0) {
    tmp_i10 = ui_currentMap._12_4_;
    tmp_i8 = (&g_dat_00397ed4)[(ui_gameType._12_4_ + 0x20c8) * 4];
  }
  if (tmp_i8 == 4) {
    if ((tmp_i10 < 0) || (g_dat_003cab70 < tmp_i10)) {
      if (param_4 == 0) {
        tmp_i10 = 0;
        ui_currentMap._12_4_ = 0;
        trap_Cvar_Set("ui_currentMap","0");
      }
      else {
        tmp_i10 = 0;
        ui_currentNetMap._12_4_ = 0;
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

void UI_DrawNamedPic(float param_1,float param_2,float param_3,float param_4,uint32_t param_5) {
  uint32_t tmp_u1;

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

void UI_DrawNetMapPreview(uint32_t *param_1) {
  uint32_t tmp_u1;

  if (0 < g_dat_003e53dc) {
    UI_DrawHandlePic(*param_1,param_1[1],param_1[2],param_1[3],g_dat_003e53dc);
    return;
  }
  tmp_u1 = trap_R_RegisterShaderNoMip("levelshots/unknownmap");
  UI_DrawHandlePic(*param_1,param_1[1],param_1[2],param_1[3],tmp_u1);
  return;
}

void UI_DrawRect(float param_1,float param_2,float param_3,float param_4,uint32_t param_5) {
  trap_R_SetColor(param_5);
  UI_DrawTopBottom(param_1,param_2,param_3,param_4);
  param_1 = param_1 * g_dat_00397fd4;
  param_2 = param_2 * g_dat_00397fd0;
  param_3 = param_3 * g_dat_00397fd4;
  param_4 = param_4 * g_dat_00397fd0;
  if (1.3333334 < g_dat_003b7efc) {
    param_1 = param_1 * (1.3333334 / g_dat_003b7efc);
    param_3 = (1.3333334 / g_dat_003b7efc) * param_3;
  }
  trap_R_DrawStretchPic(param_1,param_2,0x3f800000,param_4,0,0,0,0,g_dat_003b7f10);
  trap_R_DrawStretchPic((param_3 + param_1) - 1.0,param_2,0x3f800000,param_4,0,0,0,0,g_dat_003b7f10);
  trap_R_SetColor(0);
  return;
}

void UI_DrawRotatedPic(float param_1,float param_2,float param_3,float param_4,uint32_t param_5,
                      uint32_t param_6) {
  param_1 = g_dat_00397fd4 * param_1;
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

void UI_DrawSides(float param_1,float param_2,float param_3,float param_4) {
  param_1 = g_dat_00397fd4 * param_1;
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

void UI_DrawTextBox(int param_1,int param_2,int param_3,int param_4) {
  float tmp_f1;
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

void UI_DrawTopBottom(float param_1,float param_2,float param_3,float param_4) {
  param_1 = g_dat_00397fd4 * param_1;
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

void UI_OwnerDraw(float param_1,float param_2,float param_3,float param_4,float param_5,
                 float param_6,int param_7,uint32_t param_8,uint32_t param_9,uint32_t param_10
                 ,float param_11,float *param_12,uint32_t param_13,uint32_t param_14) {
  byte tmp_b1;
  int tmp_i2;
  float tmp_f3;
  float tmp_f4;
  uint32_t *tmp_pu5;
  uint32_t tmp_u6;
  char *tmp_pc7;
  uint32_t *tmp_pu8;
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
                   (&g_dat_00397ecc)[(ui_gameType._12_4_ + 0x20c8) * 4],0,0,param_14,
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
    if (1 < (uint)ui_serverFilterType._12_4_) {
      ui_serverFilterType._12_4_ = 0;
    }
    tmp_u6 = va("Filter: %s",(&serverFilters)[ui_serverFilterType._12_4_ * 2]);
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
    tmp_f4 = (float)(int)cg_crosshairSize._12_4_;
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
      tmp_u6 = va("ui_lastServerRefresh_%i",ui_netSource._12_4_);
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
      tmp_i13 = trap_LAN_GetServerCount(ui_netSource._12_4_);
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
    if (((int)ui_currentCampaign._12_4_ < 0) || (g_dat_003cab70 < (int)ui_currentCampaign._12_4_)) {
      ui_currentCampaign._12_4_ = 0;
      trap_Cvar_Set("ui_currentCampaign","0");
      if (g_dat_003cabcc < -1) {
        if (((int)ui_currentCampaign._12_4_ < 0) ||
           (tmp_i13 = ui_currentCampaign._12_4_, g_dat_003cab70 < (int)ui_currentCampaign._12_4_)) {
          ui_currentCampaign._12_4_ = 0;
          trap_Cvar_Set("ui_currentCampaign","0");
          tmp_i13 = 0;
        }
        goto LAB_000308c9;
      }
      tmp_i13 = 0;
      tmp_i9 = g_dat_003cabcc;
    }
    else {
      tmp_i9 = (&g_dat_003cabcc)[ui_currentCampaign._12_4_ * 0x1d];
      tmp_i13 = ui_currentCampaign._12_4_;
      if ((&g_dat_003cabcc)[ui_currentCampaign._12_4_ * 0x1d] < -1) {
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
    if (((int)ui_currentCampaign._12_4_ < 0) ||
       (tmp_i13 = ui_currentCampaign._12_4_, g_dat_003cab70 < (int)ui_currentCampaign._12_4_)) {
      ui_currentCampaign._12_4_ = 0;
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
    if (((int)ui_currentCampaign._12_4_ < 0) ||
       (tmp_i13 = ui_currentCampaign._12_4_, g_dat_003cab70 < (int)ui_currentCampaign._12_4_)) {
      tmp_i13 = 0;
      ui_currentCampaign._12_4_ = 0;
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

void Window_Paint(float *param_1,float param_2,float param_3,float param_4) {
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

  local_10 = 0x3e058;
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
LAB_0003e090:
    tmp_f1 = param_1[0x11];
    tmp_f7 = tmp_f7 + tmp_f1;
    tmp_f4 = tmp_f4 + tmp_f1;
    tmp_f5 = tmp_f5 - (tmp_f1 + tmp_f1);
    tmp_f6 = tmp_f6 - (tmp_f1 + tmp_f1);
    if (tmp_f3 == 1.4013e-45) goto LAB_0003e124;
LAB_0003e0a6:
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
              goto LAB_0003e0d2;
            }
            param_1[0xc] = tmp_f3;
          }
          if (-1 < (int)tmp_f3) {
            (**(void **)(DC + 0xf4))(tmp_f3);
            (**(void **)(DC + 0xf0))(param_1[0xc],tmp_f7,tmp_f4,tmp_f5,tmp_f6);
          }
        }
        goto LAB_0003e0d2;
      }
      if ((*(byte *)((int)param_1 + 0x49) & 2) != 0) {
        (**(void **)(DC + 4))(param_1 + 0x1d);
      }
      tmp_f3 = param_1[0x2d];
      goto LAB_0003e204;
    }
    (**(void **)(DC + 4))(param_1 + 0x21);
    (**(void **)(DC + 8))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,*(uint32_t *)(DC + 0x1e2d8));
    (**(void **)(DC + 4))(0);
  }
  else {
    if (param_1[0xe] != 0.0) goto LAB_0003e090;
    if (tmp_f3 != 1.4013e-45) goto LAB_0003e0a6;
LAB_0003e124:
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
LAB_0003e204:
      (**(void **)(DC + 8))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,tmp_f3);
      (**(void **)(DC + 4))(0);
      tmp_f7 = param_1[0xe];
      goto joined_r0x0003e226;
    }
    (**(void **)(DC + 0x3c))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,param_1 + 0x21);
  }
LAB_0003e0d2:
  tmp_f7 = param_1[0xe];
joined_r0x0003e226:
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
