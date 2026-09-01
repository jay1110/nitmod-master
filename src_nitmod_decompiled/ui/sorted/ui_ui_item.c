/**
 * @file ui_ui_item.c
 * @brief ui_item
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 */

#include "ui_types.h"
#include "ui_globals.h"
#include "ui_imports.h"
#include "ui_ui_item.h"

void Item_Action(int param_1) {
  if (param_1 != 0) {
    Item_RunScript_constprop_37();
    return;
  }
  return;
}

uint32_t Item_Bind_HandleKey(float *param_1,uint param_2,int param_3) {
  uint tmp_u1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint32_t tmp_u6;
  int tmp_i7;
  uint tmp_u8;
  uint32_t **tmp_ppu9;
  int tmp_i10;
  uint *tmp_pu11;
  bool tmp_b12;
  uint local_24;
  uint local_20 [3];
  uint32_t uStack_14;

  uStack_14 = 0x480b9;
  tmp_f3 = (float)*(int *)(DC + 0x124);
  if (param_1 != (float *)0x0) {
    tmp_f2 = *(float *)(&g_dat_0002003c + DC);
    if (1.3333334 < tmp_f2) {
      tmp_f4 = tmp_f2 * 0.75;
      tmp_f3 = tmp_f3 * tmp_f4;
      if (tmp_f4 * *param_1 < tmp_f3) {
        tmp_f5 = *param_1 + param_1[2];
        if (1.3333334 < tmp_f2) {
          tmp_f5 = tmp_f5 * tmp_f4;
        }
        goto LAB_00048132;
      }
    }
    else if (*param_1 < tmp_f3) {
      tmp_f5 = *param_1 + param_1[2];
LAB_00048132:
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
          goto LAB_0004819e;
        }
      }
    }
  }
  if (g_waitingForKey == 0) {
    return 0;
  }
LAB_0004819e:
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
            (**(void **)(DC + 0xc4))((&g_dat_000693f8)[tmp_i10 * 8],"");
            (**(void **)(DC + 0xc4))((&g_dat_000693fc)[tmp_i10 * 8],"");
            (&g_dat_000693f8)[tmp_i10 * 8] = 0xffffffff;
            (&g_dat_000693fc)[tmp_i10 * 8] = 0xffffffff;
            goto LAB_000483c8;
          }
          tmp_i10 = tmp_i10 + 1;
        } while (tmp_i10 != 0x3d);
        (**(void **)(DC + 0xbc))(param_1[0x45],&local_24,local_20);
        if (local_24 != 0xffffffff) {
          (**(void **)(DC + 0xc4))(local_24,"");
        }
        if (local_20[0] != 0xffffffff) {
          (**(void **)(DC + 0xc4))(local_20[0],"");
        }
LAB_000483c8:
        tmp_ppu9 = &g_bindings;
        do {
          if (tmp_ppu9[6] != (uint32_t *)0xffffffff) {
            (**(void **)(DC + 0xc4))(tmp_ppu9[6],*tmp_ppu9);
            if (tmp_ppu9[7] != (uint32_t *)0xffffffff) {
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
          if (tmp_i7 == 0) goto LAB_00048218;
          tmp_i10 = tmp_i10 + 1;
        } while (tmp_i10 != 0x3d);
        tmp_i10 = -1;
LAB_00048218:
        tmp_i7 = 0;
        tmp_pu11 = &g_dat_000693f8;
        do {
          if (tmp_i7 != tmp_i10) {
            tmp_u8 = tmp_pu11[1];
            if (param_2 == tmp_u8) {
              (**(void **)(DC + 0xc4))(*tmp_pu11,"");
              tmp_u8 = 0xffffffff;
              tmp_u1 = *tmp_pu11;
              tmp_pu11[1] = 0xffffffff;
            }
            else {
              tmp_u1 = *tmp_pu11;
            }
            if (param_2 == tmp_u1) {
              *tmp_pu11 = tmp_u8;
              (**(void **)(DC + 0xc4))(tmp_u8,"");
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
            (**(void **)(DC + 0xc4))(local_20[0],"");
          }
          else {
            (**(void **)(DC + 0xc4))(param_2,param_1[0x45]);
          }
        }
        else {
          tmp_u8 = (&g_dat_000693f8)[tmp_i10 * 8];
          if (tmp_u8 == 0xffffffff) {
            (&g_dat_000693f8)[tmp_i10 * 8] = param_2;
          }
          else if ((param_2 == tmp_u8) || ((&g_dat_000693fc)[tmp_i10 * 8] != -1)) {
            (**(void **)(DC + 0xc4))(tmp_u8,"");
            (**(void **)(DC + 0xc4))((&g_dat_000693fc)[tmp_i10 * 8],"");
            (&g_dat_000693f8)[tmp_i10 * 8] = param_2;
            (&g_dat_000693fc)[tmp_i10 * 8] = 0xffffffff;
          }
          else {
            (&g_dat_000693fc)[tmp_i10 * 8] = param_2;
          }
        }
        tmp_ppu9 = &g_bindings;
        do {
          if (tmp_ppu9[6] != (uint32_t *)0xffffffff) {
            (**(void **)(DC + 0xc4))(tmp_ppu9[6],*tmp_ppu9);
            if (tmp_ppu9[7] != (uint32_t *)0xffffffff) {
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

void Item_Bind_Paint(int param_1) {
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
      goto joined_r0x00047e6d;
    }
LAB_00047fea:
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
    if (local_30 < 0.0) goto LAB_00047fea;
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
joined_r0x00047e6d:
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

uint32_t Item_CheckBox_HandleKey(float *param_1,int param_2) {
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
    tmp_f1 = *(float *)(&g_dat_0002003c + DC);
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

void Item_CheckBox_Paint(float *param_1) {
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
      if (!NAN(tmp_l6) && !NAN((long double)2.0)) goto LAB_00046b82;
      goto LAB_00046b84;
    }
    tmp_l6 = (long double)0;
    tmp_b3 = false;
    tmp_b5 = false;
    if (((uint)param_1[0x12] & 0x8000002) == 0x8000002) goto LAB_00046c7a;
LAB_00046bbb:
    tmp_b3 = tmp_b5;
    if (tmp_f8 != 0.0) goto LAB_00046bc3;
LAB_00046da7:
    tmp_b5 = false;
    if (param_1[0x3a] == 0.0) {
      tmp_b5 = false;
      goto LAB_00046dc0;
    }
  }
  else {
    tmp_l6 = (long double)(**(void **)(DC + 0x74))(tmp_f1);
    tmp_l6 = (long double)(int)((int)ROUND(tmp_l6) & (uint)param_1[0x9d]);
    tmp_b5 = tmp_l6 == (long double)2.0;
    if (NAN(tmp_l6) || NAN((long double)2.0)) {
LAB_00046b84:
      tmp_b3 = false;
    }
    else {
LAB_00046b82:
      tmp_b3 = true;
      if (!tmp_b5) goto LAB_00046b84;
    }
    tmp_b5 = tmp_b3;
    if (((uint)param_1[0x12] & 0x8000002) != 0x8000002) goto LAB_00046bbb;
LAB_00046c7a:
    tmp_f1 = *(float *)((int)tmp_f9 + 0x500);
    tmp_d7 = sin((double)(*(int *)(DC + 0x11c) / 0x4b));
    tmp_l6 = (long double)(float)tmp_l6;
    tmp_f9 = *(float *)((int)tmp_f9 + 0x500);
    tmp_b5 = tmp_b3;
    if (tmp_f9 + (tmp_f1 * 0.8 - tmp_f9) * ((float)tmp_d7 * 0.5 + 0.5) < 0.0) goto LAB_00046bbb;
    if (tmp_f8 == 0.0) goto LAB_00046da7;
LAB_00046bc3:
    tmp_b5 = *(int *)((int)tmp_f8 + 0x180) != 0;
    if (param_1[0x3a] == 0.0) {
LAB_00046dc0:
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
      goto LAB_00046c35;
    }
    tmp_f9 = param_1[3];
    tmp_u4 = *(uint32_t *)(DC + 0x1e30c);
  }
  tmp_f8 = param_1[1];
LAB_00046c35:
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

uint32_t * Item_CorrectedTextRect(int param_1) {
  rect_10156 = 0;
  g_dat_0008c160 = 0.0;
  g_dat_0008c164 = 0.0;
  g_dat_0008c168 = 0.0;
  if (param_1 != 0) {
    rect_10156 = *(uint32_t *)(param_1 + 0xb8);
    g_dat_0008c160 = *(float *)(param_1 + 0xbc);
    g_dat_0008c164 = *(float *)(param_1 + 0xc0);
    g_dat_0008c168 = *(float *)(param_1 + 0xc4);
    if (g_dat_0008c164 != 0.0) {
      g_dat_0008c160 = g_dat_0008c160 - g_dat_0008c168;
    }
  }
  return &rect_10156;
}

bool Item_EnableShowViaCvar(int param_1,uint param_2) {
  uint tmp_u1;
  char *tmp_pc2;
  int tmp_i3;
  uint32_t *local_820;
  uint32_t local_81c [256];
  uint8_t local_41c [1032];
  uint32_t uStack_14;

  tmp_u1 = 0;
  uStack_14 = 0x41f7b;
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

uint32_t Item_HandleKey(float *param_1,uint param_2,int param_3) {
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
LAB_0004bcbe:
      Item_RunScript_constprop_37();
      return 1;
    }
    switch(param_1[0x32]) {
    case 4.2039e-45:
    case 2.24208e-44:
_L4869:
      tmp_u9 = Item_CheckBox_HandleKey();
      return tmp_u9;
    default:
      break;
    case 8.40779e-45:
_L4871:
      tmp_u9 = Item_ListBox_HandleKey(param_1,param_2,param_3,0);
      return tmp_u9;
    case 1.12104e-44:
_L4872:
      if (*(void **)(DC + 0x8c) != (void *)0x0) {
        tmp_u9 = (**(void **)(DC + 0x8c))(param_1[0xf],param_1[0x10],param_1 + 0x92,param_2);
        return tmp_u9;
      }
      break;
    case 1.4013e-44:
_L4873:
      if ((((uint)param_1[0x12] & 2) != 0) && (param_1[0x45] != 0.0)) {
        tmp_f8 = (float)*(int *)(DC + 0x124);
        tmp_f1 = *(float *)(&g_dat_0002003c + DC);
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
                tmp_u9 = va("%f",(double)(*pfVar3 + (pfVar3[1] - *pfVar3) * ((tmp_f8 - tmp_f2) / 96.0))
                          );
                (*tmp_pc4)(param_1[0x45],tmp_u9);
                return 1;
              }
            }
          }
        }
      }
      break;
    case 1.54143e-44:
_L4874:
      tmp_u9 = Item_YesNo_HandleKey();
      return tmp_u9;
    case 1.68156e-44:
_L4875:
      tmp_u9 = Item_Multi_HandleKey();
      return tmp_u9;
    case 1.82169e-44:
_L4876:
      tmp_u9 = Item_Bind_HandleKey();
      return tmp_u9;
    }
LAB_0004bc92:
    return 0;
  }
  if (param_1[0x9a] != 0.0) goto LAB_0004bcbe;
  switch(param_1[0x32]) {
  case 4.2039e-45:
  case 2.24208e-44:
    goto _L4869;
  default:
    goto LAB_0004bc92;
  case 8.40779e-45:
    goto _L4871;
  case 1.12104e-44:
    goto _L4872;
  case 1.4013e-44:
    goto _L4873;
  case 1.54143e-44:
    goto _L4874;
  case 1.68156e-44:
    goto _L4875;
  case 1.82169e-44:
    goto _L4876;
  }
}

void Item_Image_Paint(float *param_1) {
  if (param_1 != (float *)0x0) {
    (**(void **)(DC + 8))
              (*param_1 + 1.0,param_1[1] + 1.0,param_1[2] - 2.0,param_1[3] - 2.0,param_1[0x3c]);
  }
  return;
}

void Item_Init(uint16_t *param_1) {
  uint tmp_u1;
  uint32_t *tmp_pu2;
  uint16_t *tmp_pu3;
  uint tmp_u4;
  bool tmp_b5;

  tmp_u4 = 0x278;
  tmp_b5 = false;
  if (((uint)param_1 & 1) == 0) {
    tmp_pu3 = param_1;
    if (((uint)param_1 & 2) == 0) goto LAB_0004c0db;
  }
  else {
    tmp_pu3 = (uint16_t *)((int)param_1 + 1);
    tmp_u4 = 0x277;
    tmp_b5 = true;
    *(uint8_t *)param_1 = 0;
    if (((uint)tmp_pu3 & 2) == 0) goto LAB_0004c0db;
    tmp_u4 = 0x277;
    tmp_b5 = true;
  }
  *tmp_pu3 = 0;
  tmp_u4 = tmp_u4 - 2;
  tmp_pu3 = tmp_pu3 + 1;
LAB_0004c0db:
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

void Item_InitControls(int param_1) {
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

uint32_t Item_ListBox_HandleKey(float *param_1,uint param_2,uint32_t param_3,int param_4) {
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
    tmp_f6 = *(float *)(&g_dat_0002003c + DC);
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
      if (((param_2 & 0xffffffef) != 0xa7) && (param_2 != 0x85)) goto LAB_0004b364;
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
        goto LAB_0004b499;
      }
LAB_0004b5f0:
      if ((int)*pfVar1 + 1 <= (int)tmp_f6) {
        *pfVar1 = (float)((int)*pfVar1 + 1);
        return 1;
      }
LAB_0004b660:
      *pfVar1 = tmp_f6;
      return 1;
    }
    if (pfVar1[0x3a] == 0.0) {
      tmp_f6 = (float)((int)pfVar1[3] + -1);
      if ((int)tmp_f6 < 0) {
LAB_0004b690:
        pfVar1[3] = 0.0;
        tmp_f6 = 0.0;
      }
      else {
LAB_0004b4f8:
        pfVar1[3] = tmp_f6;
      }
      tmp_f9 = *pfVar1;
      if ((int)tmp_f6 < (int)*pfVar1) {
        *pfVar1 = tmp_f6;
        tmp_f9 = tmp_f6;
      }
      goto LAB_0004b420;
    }
LAB_0004b510:
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
LAB_0004b499:
        if ((int)tmp_f6 + tmp_i8 <= (int)tmp_f9) {
          *pfVar1 = (float)(((int)tmp_f9 - tmp_i8) + 1);
        }
        param_1[0x93] = tmp_f9;
        (**(void **)(DC + 0xa0))(param_1[0x92],tmp_f9);
        return 1;
      }
      goto LAB_0004b510;
    }
    if ((param_2 == 0xa5) || (param_2 == 0x87)) {
      if (pfVar1[0x3a] != 0.0) {
        tmp_f6 = (float)((int)*pfVar1 + 1);
        if (tmp_i4 <= (int)tmp_f6) {
          *pfVar1 = (float)(tmp_i4 + -1);
          return 1;
        }
        goto LAB_0004b515;
      }
      tmp_f9 = *pfVar1;
      tmp_f6 = (float)((int)pfVar1[3] + 1);
      pfVar1[3] = tmp_f6;
      if ((int)tmp_f6 < (int)tmp_f9) {
LAB_0004b400:
        *pfVar1 = tmp_f6;
        tmp_f9 = tmp_f6;
      }
LAB_0004b404:
      if (tmp_i4 <= (int)tmp_f6) {
        tmp_f6 = (float)(tmp_i4 + -1);
        pfVar1[3] = tmp_f6;
      }
LAB_0004b420:
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
LAB_0004b364:
    if (1 < param_2 - 0xb2) {
      if ((param_2 == 0xa0) || (param_2 == 0x8f)) goto LAB_0004b530;
      if ((param_2 == 0xa6) || (param_2 == 0x90)) goto LAB_0004b660;
      if ((param_2 == 0xa2) || (param_2 == 0x8e)) {
        if (pfVar1[0x3a] == 0.0) {
          tmp_f6 = (float)((int)pfVar1[3] - tmp_i8);
          if (-1 < (int)tmp_f6) goto LAB_0004b4f8;
          goto LAB_0004b690;
        }
        goto LAB_0004b528;
      }
      if ((param_2 != 0xa8) && (param_2 != 0x8d)) {
        return 0;
      }
      if (pfVar1[0x3a] != 0.0) {
        tmp_f9 = (float)(tmp_i8 + (int)*pfVar1);
        if ((int)tmp_f9 <= (int)tmp_f6) goto LAB_0004b6ba;
        goto LAB_0004b515;
      }
      tmp_f6 = (float)((int)pfVar1[3] + tmp_i8);
      pfVar1[3] = tmp_f6;
      tmp_f9 = *pfVar1;
      if ((int)tmp_f6 < (int)*pfVar1) goto LAB_0004b400;
      goto LAB_0004b404;
    }
    Item_ListBox_MouseEnter(param_1,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128),1);
    tmp_f9 = param_1[0x12];
    if (((uint)tmp_f9 & 0x800) != 0) goto LAB_0004b510;
    if (((uint)tmp_f9 & 0x1000) != 0) goto LAB_0004b5f0;
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
LAB_0004b6ba:
        *pfVar1 = tmp_f9;
        return 1;
      }
      goto LAB_0004b660;
    }
LAB_0004b528:
    tmp_f6 = (float)((int)*pfVar1 - tmp_i8);
  }
  if (-1 < (int)tmp_f6) {
LAB_0004b515:
    *pfVar1 = tmp_f6;
    return 1;
  }
LAB_0004b530:
  *pfVar1 = 0.0;
  return 1;
}

int Item_ListBox_MaxScroll(int param_1) {
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

void Item_ListBox_MouseEnter(float *param_1,float param_2,float param_3,int param_4) {
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
    tmp_f1 = *(float *)(&g_dat_0002003c + DC);
    tmp_f5 = param_2;
    tmp_f6 = local_2c;
    if (1.3333334 < tmp_f1) {
      tmp_f5 = param_2 * tmp_f1 * 0.75;
      tmp_f6 = tmp_f1 * 0.75 * local_2c;
    }
    tmp_f4 = param_2;
    if (tmp_f5 <= tmp_f6) {
LAB_000437d0:
      local_28 = (tmp_f2 + param_1[3]) - 16.0;
      if (1.3333334 < tmp_f1) {
        tmp_f4 = param_2 * tmp_f1 * 0.75;
        tmp_f2 = tmp_f1 * 0.75 * local_2c;
        goto LAB_00043805;
      }
      if (local_2c < param_2) {
        tmp_f2 = local_2c + 16.0;
        goto LAB_0004382b;
      }
    }
    else {
      if (1.3333334 < tmp_f1) {
        if ((tmp_f5 < tmp_f1 * 0.75 * (local_2c + 16.0)) && (tmp_f2 < param_3)) goto LAB_00043794;
        goto LAB_000437d0;
      }
      if ((tmp_f5 < local_2c + 16.0) && (tmp_f2 < param_3)) {
LAB_00043794:
        if (param_3 < tmp_f2 + 16.0) {
          tmp_u10 = 0x800;
          goto LAB_00043670;
        }
        goto LAB_000437d0;
      }
      local_28 = (tmp_f2 + param_1[3]) - 16.0;
      tmp_f2 = local_2c;
LAB_00043805:
      if (tmp_f2 < tmp_f4) {
        tmp_f2 = local_2c + 16.0;
        if (1.3333334 < tmp_f1) {
          tmp_f2 = tmp_f1 * 0.75 * tmp_f2;
        }
LAB_0004382b:
        if (((tmp_f4 < tmp_f2) && (local_28 < param_3)) && (param_3 < local_28 + 16.0)) {
          tmp_u10 = 0x1000;
          goto LAB_00043670;
        }
      }
    }
    local_20 = local_24;
    tmp_i8 = Item_ListBox_ThumbDrawPosition(param_1);
    local_28 = (float)tmp_i8;
    tmp_i9 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i9 != 0) goto LAB_0004365a;
    tmp_f2 = param_1[1];
    local_28 = tmp_f2 + 16.0;
    local_20 = (float)tmp_i8 - local_28;
    tmp_i9 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i9 != 0) goto LAB_00043961;
    local_28 = (float)tmp_i8 + 16.0;
    tmp_f7 = param_1[3];
    local_20 = (tmp_f2 + tmp_f7) - 16.0;
    tmp_i8 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i8 != 0) goto LAB_00043cc3;
    local_28 = tmp_f2;
    local_20 = tmp_f7;
    tmp_i8 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    tmp_f7 = param_1[0x12];
    if (tmp_i8 == 0) {
      tmp_u10 = 0;
      goto LAB_00043670;
    }
  }
  else {
    tmp_f2 = *param_1;
    local_24 = 16.0;
    local_28 = (param_1[1] + param_1[3]) - 16.0;
    tmp_f1 = *(float *)(&g_dat_0002003c + DC);
    tmp_f5 = param_2;
    tmp_f6 = tmp_f2;
    if (1.3333334 < tmp_f1) {
      tmp_f5 = param_2 * tmp_f1 * 0.75;
      tmp_f6 = tmp_f1 * 0.75 * tmp_f2;
    }
    tmp_f4 = param_2;
    if (tmp_f5 <= tmp_f6) {
LAB_00043560:
      local_2c = (tmp_f2 + param_1[2]) - 16.0;
      if (1.3333334 < tmp_f1) {
        tmp_f4 = param_2 * tmp_f1 * 0.75;
        tmp_f2 = tmp_f1 * 0.75 * local_2c;
        goto LAB_00043595;
      }
      if (local_2c < param_2) {
        tmp_f2 = local_2c + 16.0;
        goto LAB_000435b7;
      }
    }
    else {
      if (1.3333334 < tmp_f1) {
        if ((tmp_f5 < tmp_f1 * 0.75 * (tmp_f2 + 16.0)) && (local_28 < param_3)) goto LAB_00043517;
        goto LAB_00043560;
      }
      if ((tmp_f5 < tmp_f2 + 16.0) && (local_28 < param_3)) {
LAB_00043517:
        tmp_u10 = 0x800;
        if (param_3 < local_28 + 16.0) goto LAB_00043670;
        goto LAB_00043560;
      }
      local_2c = (tmp_f2 + param_1[2]) - 16.0;
      tmp_f2 = local_2c;
LAB_00043595:
      if (tmp_f2 < tmp_f4) {
        tmp_f2 = local_2c + 16.0;
        if (1.3333334 < tmp_f1) {
          tmp_f2 = tmp_f1 * 0.75 * tmp_f2;
        }
LAB_000435b7:
        if (((tmp_f4 < tmp_f2) && (local_28 < param_3)) &&
           (tmp_u10 = 0x1000, param_3 < local_28 + 16.0)) goto LAB_00043670;
      }
    }
    local_20 = local_24;
    tmp_i8 = Item_ListBox_ThumbDrawPosition(param_1);
    local_2c = (float)tmp_i8;
    tmp_i9 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i9 != 0) {
LAB_0004365a:
      tmp_f7 = param_1[0x12];
      tmp_u10 = 0x2000;
      goto LAB_00043670;
    }
    tmp_f2 = *param_1;
    local_2c = tmp_f2 + 16.0;
    local_24 = (float)tmp_i8 - local_2c;
    tmp_i9 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i9 != 0) {
LAB_00043961:
      tmp_f7 = param_1[0x12];
      tmp_u10 = 0x4000;
      goto LAB_00043670;
    }
    local_2c = (float)tmp_i8 + 16.0;
    tmp_f7 = param_1[2];
    local_24 = (tmp_f2 + tmp_f7) - 16.0;
    tmp_i8 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i8 != 0) {
LAB_00043cc3:
      tmp_f7 = param_1[0x12];
      tmp_u10 = 0x8000;
      goto LAB_00043670;
    }
    local_2c = tmp_f2;
    local_24 = tmp_f7;
    tmp_i8 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    tmp_f7 = param_1[0x12];
    if (tmp_i8 == 0) {
      tmp_u10 = 0;
      goto LAB_00043670;
    }
  }
  tmp_u10 = 0x40000000;
LAB_00043670:
  param_1[0x12] = (float)((uint)tmp_f7 | tmp_u10);
  if (param_4 == 0) {
    return;
  }
  if (((uint)tmp_f7 & 0x400) == 0) {
    if (((uint)tmp_f7 & 0x4000f800) != 0 || tmp_u10 != 0) {
      return;
    }
    tmp_f2 = *param_1;
    tmp_f7 = param_1[1];
    tmp_f1 = *(float *)(&g_dat_0002003c + DC);
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
    if (tmp_f2 <= param_2) {
      return;
    }
    if (param_3 <= tmp_f7) {
      return;
    }
    if ((param_1[3] - (float)tmp_pi3[2]) + tmp_f7 <= param_3) {
      return;
    }
    tmp_i9 = (int)ROUND(((param_3 - 2.0) - tmp_f7) / (float)tmp_pi3[5]) + *tmp_pi3;
    tmp_i8 = tmp_pi3[1];
    tmp_pi3[3] = tmp_i9;
    if (tmp_i9 <= tmp_i8) {
      return;
    }
  }
  else {
    if (((uint)tmp_f7 & 0x4000f800) != 0 || tmp_u10 != 0) {
      return;
    }
    if (tmp_pi3[6] != 1) {
      return;
    }
    tmp_f2 = *param_1;
    local_28 = param_1[1];
    local_20 = param_1[3] - 16.0;
    local_24 = param_1[2] - (float)tmp_pi3[2];
    local_2c = tmp_f2;
    tmp_i8 = Rect_ContainsPoint(&local_2c,param_2,param_3);
    if (tmp_i8 == 0) {
      return;
    }
    tmp_i8 = tmp_pi3[1];
    tmp_i9 = (int)ROUND((param_2 - tmp_f2) / (float)tmp_pi3[4]) + *tmp_pi3;
    tmp_pi3[3] = tmp_i9;
    if (tmp_i9 < tmp_i8) {
      return;
    }
  }
  tmp_pi3[3] = tmp_i8;
  return;
}

uint32_t Item_ListBox_OverLB(float *param_1,float param_2,float param_3) {
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
    tmp_f2 = *(float *)(&g_dat_0002003c + DC);
    tmp_f4 = param_2;
    tmp_f5 = local_1c;
    if (1.3333334 < tmp_f2) {
      tmp_f4 = param_2 * tmp_f2 * 0.75;
      tmp_f5 = tmp_f2 * 0.75 * local_1c;
    }
    tmp_f3 = param_2;
    if (tmp_f5 < tmp_f4) {
      if (1.3333334 < tmp_f2) {
        if ((tmp_f4 < tmp_f2 * 0.75 * (local_1c + 16.0)) && (tmp_f1 < param_3)) goto LAB_00042fa0;
        goto LAB_00042fe0;
      }
      if ((tmp_f4 < local_1c + 16.0) && (tmp_f1 < param_3)) {
LAB_00042fa0:
        if (param_3 < tmp_f1 + 16.0) {
          return 0x800;
        }
        goto LAB_00042fe0;
      }
      local_18 = (tmp_f1 + param_1[3]) - 16.0;
      tmp_f1 = local_1c;
LAB_00043015:
      if (tmp_f1 < tmp_f3) {
        tmp_f1 = local_1c + 16.0;
        if (1.3333334 < tmp_f2) {
          tmp_f1 = tmp_f2 * 0.75 * tmp_f1;
        }
LAB_0004303b:
        if (((tmp_f3 < tmp_f1) && (local_18 < param_3)) && (param_3 < local_18 + 16.0)) {
          return 0x1000;
        }
      }
    }
    else {
LAB_00042fe0:
      local_18 = (tmp_f1 + param_1[3]) - 16.0;
      if (1.3333334 < tmp_f2) {
        tmp_f3 = param_2 * tmp_f2 * 0.75;
        tmp_f1 = tmp_f2 * 0.75 * local_1c;
        goto LAB_00043015;
      }
      if (local_1c < param_2) {
        tmp_f1 = local_1c + 16.0;
        goto LAB_0004303b;
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
    goto joined_r0x00043407;
  }
  local_14 = 16.0;
  local_18 = (param_1[1] + param_1[3]) - 16.0;
  tmp_f2 = *(float *)(&g_dat_0002003c + DC);
  tmp_f4 = param_2;
  tmp_f5 = tmp_f1;
  if (1.3333334 < tmp_f2) {
    tmp_f4 = param_2 * tmp_f2 * 0.75;
    tmp_f5 = tmp_f2 * 0.75 * tmp_f1;
  }
  tmp_f3 = param_2;
  if (tmp_f4 <= tmp_f5) {
LAB_00042e00:
    local_1c = (tmp_f1 + param_1[2]) - 16.0;
    if (1.3333334 < tmp_f2) {
      tmp_f3 = param_2 * tmp_f2 * 0.75;
      tmp_f1 = tmp_f2 * 0.75 * local_1c;
      goto LAB_00042e35;
    }
    if (local_1c < param_2) {
      tmp_f1 = local_1c + 16.0;
      goto LAB_00042e57;
    }
  }
  else {
    if (1.3333334 < tmp_f2) {
      if ((tmp_f4 < tmp_f2 * 0.75 * (tmp_f1 + 16.0)) && (local_18 < param_3)) goto LAB_00042dc1;
      goto LAB_00042e00;
    }
    if ((tmp_f4 < tmp_f1 + 16.0) && (local_18 < param_3)) {
LAB_00042dc1:
      if (param_3 < local_18 + 16.0) {
        return 0x800;
      }
      goto LAB_00042e00;
    }
    local_1c = (tmp_f1 + param_1[2]) - 16.0;
    tmp_f1 = local_1c;
LAB_00042e35:
    if (tmp_f1 < tmp_f3) {
      tmp_f1 = local_1c + 16.0;
      if (1.3333334 < tmp_f2) {
        tmp_f1 = tmp_f2 * 0.75 * tmp_f1;
      }
LAB_00042e57:
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
joined_r0x00043407:
  if (tmp_i6 == 0) {
    return 0;
  }
  return 0x40000000;
}

void Item_ListBox_Paint(float *param_1) {
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
        if (tmp_pi4[7] < 1) goto LAB_000490e4;
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
LAB_000490e4:
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
LAB_000493fb:
              tmp_pi4[2] = (int)ROUND(tmp_f1);
              return;
            }
          }
          else {
            tmp_f3 = (float)tmp_pi4[4];
            tmp_f1 = tmp_f1 - tmp_f3;
            if (tmp_f1 < tmp_f3) goto LAB_000493fb;
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

int Item_ListBox_ThumbDrawPosition(float *param_1) {
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
        goto LAB_000428ae;
      }
    }
    tmp_f1 = 0.0;
LAB_000428ae:
    return (int)ROUND(param_1[1] + 1.0 + 16.0 + (float)*tmp_pi2 * tmp_f1);
  }
  tmp_i4 = tmp_i4 - (int)ROUND(param_1[2] / (float)tmp_pi2[4]);
  if (-1 < tmp_i4) {
    tmp_f1 = (float)tmp_i4;
    if (0.0 < tmp_f1) {
      tmp_f1 = (((param_1[2] - 32.0) - 2.0) - 16.0) / tmp_f1;
      goto LAB_00042810;
    }
  }
  tmp_f1 = 0.0;
LAB_00042810:
  return (int)ROUND(*param_1 + 1.0 + 16.0 + (float)*tmp_pi2 * tmp_f1);
}

int Item_ListBox_ThumbPosition(float *param_1) {
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
        goto LAB_00042712;
      }
    }
    tmp_f2 = 0.0;
LAB_00042712:
    return (int)ROUND(param_1[1] + 1.0 + 16.0 + (float)*tmp_pi1 * tmp_f2);
  }
  tmp_i3 = tmp_i3 - (int)ROUND(param_1[2] / (float)tmp_pi1[4]);
  if (-1 < tmp_i3) {
    tmp_f2 = (float)tmp_i3;
    if (0.0 < tmp_f2) {
      tmp_f2 = (((param_1[2] - 32.0) - 2.0) - 16.0) / tmp_f2;
      goto LAB_00042652;
    }
  }
  tmp_f2 = 0.0;
LAB_00042652:
  return (int)ROUND(*param_1 + 1.0 + 16.0 + (float)*tmp_pi1 * tmp_f2);
}

void Item_Model_Paint(float *param_1) {
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
    if (1.3333334 < *(float *)(&g_dat_0002003c + DC)) {
      tmp_f6 = 1.3333334 / *(float *)(&g_dat_0002003c + DC);
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

void Item_MouseEnter(int param_1,float param_2,float param_3) {
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
  tmp_f5 = *(float *)(&g_dat_0002003c + DC);
  if (1.3333334 < tmp_f5) {
    tmp_f6 = tmp_f5 * 0.75;
    tmp_f7 = param_2 * tmp_f6;
    if (tmp_f7 <= tmp_f1 * tmp_f6) goto LAB_00043f00;
    if (tmp_f5 <= 1.3333334) goto LAB_00043fc0;
    if ((tmp_f1 + tmp_f3) * tmp_f6 <= tmp_f7) goto LAB_00043f00;
  }
  else {
    tmp_f7 = param_2;
    if (param_2 <= tmp_f1) goto LAB_00043f00;
LAB_00043fc0:
    if (tmp_f1 + tmp_f3 <= tmp_f7) goto LAB_00043f00;
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
LAB_00043f00:
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

void Item_MouseLeave(int param_1) {
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

uint32_t Item_Multi_CountSettings(int param_1) {
  if (*(int *)(param_1 + 0x250) != 0) {
    return *(uint32_t *)(*(int *)(param_1 + 0x250) + 0x180);
  }
  return 0;
}

int Item_Multi_FindCvarByValue(int param_1) {
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

uint32_t Item_Multi_HandleKey(float *param_1,int param_2) {
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
  tmp_f1 = *(float *)(&g_dat_0002003c + DC);
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
      goto LAB_000449f8;
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
LAB_000449f8:
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
      tmp_u8 = va("%f",(double)tmp_f2);
    }
    (*tmp_pc10)(param_1[0x45],tmp_u8);
    return 1;
  }
  (**(void **)(DC + 0x78))(param_1[0x45],*(uint32_t *)((int)tmp_f2 + (tmp_i7 + 0x20) * 4));
  return 1;
}

void Item_Multi_Paint(int param_1) {
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

char * Item_Multi_Setting(int param_1) {
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
LAB_00044956:
            return *(char **)(tmp_i1 + tmp_i5 * 4);
          }
          tmp_i2 = *(int *)(tmp_i1 + 0x180);
          tmp_i5 = tmp_i5 + 1;
          pfVar4 = pfVar4 + 1;
          if (tmp_i2 <= tmp_i5) goto LAB_0004490a;
        }
        if ((long double)*pfVar4 == tmp_l6) goto LAB_00044956;
        tmp_i5 = tmp_i5 + 1;
        pfVar4 = pfVar4 + 1;
      } while (tmp_i5 < tmp_i2);
    }
  }
LAB_0004490a:
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

uint32_t Item_OwnerDraw_HandleKey(int param_1,uint32_t param_2) {
  uint32_t tmp_u1;

  if ((param_1 != 0) && (*(void **)(DC + 0x8c) != (void *)0x0)) {
    tmp_u1 = (**(void **)(DC + 0x8c))
                      (*(uint32_t *)(param_1 + 0x3c),*(uint32_t *)(param_1 + 0x40),
                       param_1 + 0x248,param_2);
    return tmp_u1;
  }
  return 0;
}

void Item_OwnerDraw_Paint(uint32_t *param_1) {
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
        if (tmp_i5 == 1) goto LAB_00049860;
        if ((tmp_l6 < (long double)(float)param_1[0x57]) || ((long double)(float)param_1[0x58] < tmp_l6)
           ) {
          if (tmp_i5 == 2) goto LAB_00049860;
          if ((tmp_l6 < (long double)(float)param_1[0x5e]) ||
             ((long double)(float)param_1[0x5f] < tmp_l6)) {
            if (tmp_i5 == 3) goto LAB_00049860;
            if ((tmp_l6 < (long double)(float)param_1[0x65]) ||
               ((long double)(float)param_1[0x66] < tmp_l6)) {
              if (tmp_i5 == 4) goto LAB_00049860;
              if ((tmp_l6 < (long double)(float)param_1[0x6c]) ||
                 ((long double)(float)param_1[0x6d] < tmp_l6)) {
                if (tmp_i5 == 5) goto LAB_00049860;
                if ((tmp_l6 < (long double)(float)param_1[0x73]) ||
                   ((long double)(float)param_1[0x74] < tmp_l6)) {
                  if (tmp_i5 == 6) goto LAB_00049860;
                  if ((tmp_l6 < (long double)(float)param_1[0x7a]) ||
                     ((long double)(float)param_1[0x7b] < tmp_l6)) {
                    if (tmp_i5 == 7) goto LAB_00049860;
                    if ((tmp_l6 < (long double)(float)param_1[0x81]) ||
                       ((long double)(float)param_1[0x82] < tmp_l6)) {
                      if (tmp_i5 == 8) goto LAB_00049860;
                      if ((tmp_l6 < (long double)(float)param_1[0x88]) ||
                         ((long double)(float)param_1[0x89] < tmp_l6)) {
                        if ((tmp_i5 == 9) ||
                           ((tmp_l6 < (long double)(float)param_1[0x8f] ||
                            (tmp_i5 = 9, (long double)(float)param_1[0x90] < tmp_l6))))
                        goto LAB_00049860;
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
LAB_00049860:
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
    if ((param_1[0x39] != 1) || ((*(int *)(DC + 0x11c) / 200 & 1U) != 0)) goto LAB_00049880;
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
LAB_00049880:
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

void Item_Paint(float *param_1) {
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
LAB_00049faf:
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
          if (tmp_f1 <= tmp_f5) goto LAB_0004a2b2;
        }
        else {
          tmp_f5 = tmp_f5 + param_1[0x17];
          if (tmp_f5 <= tmp_f1) {
LAB_0004a2b2:
            param_1[4] = tmp_f5;
            tmp_i8 = 1;
            tmp_i6 = 0;
            goto LAB_00049ff9;
          }
        }
        param_1[4] = tmp_f1;
        tmp_i8 = 2;
        tmp_i6 = 1;
      }
LAB_00049ff9:
      tmp_f5 = param_1[5];
      tmp_f1 = param_1[0x14];
      if (tmp_f5 != tmp_f1) {
        if (tmp_f1 <= tmp_f5) {
          tmp_f5 = tmp_f5 - param_1[0x18];
          if (tmp_f5 < tmp_f1) goto LAB_0004a31a;
        }
        else {
          tmp_f5 = tmp_f5 + param_1[0x18];
          if (tmp_f1 < tmp_f5) {
LAB_0004a31a:
            param_1[5] = tmp_f1;
            goto LAB_0004a044;
          }
        }
        param_1[5] = tmp_f5;
        tmp_i8 = tmp_i6;
      }
LAB_0004a044:
      tmp_f5 = param_1[6];
      tmp_f1 = param_1[0x15];
      if (tmp_f5 == tmp_f1) {
LAB_0004a2f4:
        tmp_i8 = tmp_i8 + 1;
      }
      else {
        if (tmp_f1 <= tmp_f5) {
          tmp_f5 = tmp_f5 - param_1[0x19];
          if (tmp_f5 < tmp_f1) goto LAB_0004a2e2;
        }
        else {
          tmp_f5 = tmp_f5 + param_1[0x19];
          if (tmp_f1 < tmp_f5) {
LAB_0004a2e2:
            param_1[6] = tmp_f1;
            goto LAB_0004a2f4;
          }
        }
        param_1[6] = tmp_f5;
      }
      tmp_f5 = param_1[7];
      tmp_f1 = param_1[0x16];
      if (tmp_f5 == tmp_f1) {
LAB_0004a09e:
        tmp_i8 = tmp_i8 + 1;
        pfVar7 = (float *)param_1[0x3b];
        if (pfVar7 != (float *)0x0) {
LAB_0004a0ac:
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
          if (tmp_f5 < tmp_f1) goto LAB_0004a34a;
        }
        else {
          tmp_f5 = tmp_f5 + param_1[0x1a];
          if (tmp_f1 < tmp_f5) {
LAB_0004a34a:
            param_1[7] = tmp_f1;
            tmp_f5 = tmp_f1;
            goto LAB_0004a09e;
          }
        }
        pfVar7 = (float *)param_1[0x3b];
        param_1[7] = tmp_f5;
        if (pfVar7 != (float *)0x0) goto LAB_0004a0ac;
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
    goto LAB_00049faf;
  }
  if ((param_1[0x10] != 0.0) && (*(void **)(DC + 100) != (void *)0x0)) {
    tmp_i8 = (**(void **)(DC + 100))(param_1[0x10]);
    if (tmp_i8 == 0) {
      param_1[0x12] = (float)((uint)param_1[0x12] & 0xfffffffa);
      tmp_b3 = *(byte *)(param_1 + 0x48);
      goto joined_r0x0004a1a9;
    }
    param_1[0x12] = (float)((uint)param_1[0x12] | 4);
  }
  tmp_b3 = *(byte *)(param_1 + 0x48);
joined_r0x0004a1a9:
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

int Item_Parse(uint32_t param_1,uint32_t param_2) {
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
  uStack_460 = 0x4e4f0;
  local_444 = local_458;
  tmp_i2 = trap_PC_ReadToken();
  if ((tmp_i2 == 0) || (local_424 != '{')) {
    return 0;
  }
  local_440 = "unknown menu item keyword %s";
LAB_0004e520:
  do {
    local_458 = local_444;
    local_45c = param_1;
    uStack_460 = 0x4e537;
    tmp_i2 = trap_PC_ReadToken();
    if (tmp_i2 == 0) {
      local_458 = "end of file inside menu item\n";
      local_45c = param_1;
      uStack_460 = 0x4e65c;
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
      uStack_460 = 0x4e5c5;
      local_458 = &local_424;
      tmp_i2 = Q_stricmp();
      if (tmp_i2 == 0) {
        local_458 = (char *)param_1;
        local_45c = param_2;
        uStack_460 = 0x4e5e1;
        tmp_i2 = (*(void *)tmp_pu4[1])();
        if (tmp_i2 == 0) {
          local_458 = "couldn\'t parse menu item keyword %s";
          local_45c = param_1;
          uStack_460 = 0x4e60a;
          local_454 = &local_424;
          local_444 = (uint8_t *)tmp_i2;
          PC_SourceError();
          return (int)local_444;
        }
        goto LAB_0004e520;
      }
    }
    local_45c = param_1;
    uStack_460 = 0x4e633;
    local_458 = local_440;
    local_454 = &local_424;
    PC_SourceError();
  } while( true );
}

void Item_RunScript(int param_1,int *param_2,char *param_3) {
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
LAB_00041310:
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
          (*(void *)(&PTR_Script_FadeIn_00069b84)[tmp_i4 * 2])(param_1,local_1020,&local_1024);
          if (local_1020[0] != 0) {
            if (param_2 == (int *)0x0) {
              return;
            }
            *param_2 = local_1020[0];
            return;
          }
          goto LAB_00041310;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 < scriptCommandCount);
    }
    (**(void **)(DC + 0x68))(&local_1024);
  } while( true );
}

void Item_RunScript_constprop_37(int param_1,char *param_2) {
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
LAB_0003cdd0:
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
          (*(void *)(&PTR_Script_FadeIn_00069b84)[tmp_i4 * 2])(param_1,local_1020,&local_1024);
          if (local_1020[0] != 0) {
            return;
          }
          goto LAB_0003cdd0;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 < scriptCommandCount);
    }
    (**(void **)(DC + 0x68))(&local_1024);
  } while( true );
}

uint32_t Item_SetFocus(int param_1,float param_2,float param_3) {
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
    tmp_f2 = *(float *)(&g_dat_0002003c + DC);
    if (tmp_f2 <= 1.3333334) {
      if (tmp_f1 < param_2) {
        tmp_f1 = *(float *)(param_1 + 0xc0) + tmp_f1;
        goto LAB_0004231a;
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
LAB_0004231a:
        tmp_f2 = *(float *)(param_1 + 0xbc) - *(float *)(param_1 + 0xc4);
        tmp_b9 = param_2 < tmp_f1 && tmp_f2 < param_3;
        if ((param_2 < tmp_f1 && tmp_f2 < param_3) && (param_3 < tmp_f2 + *(float *)(param_1 + 0xc4)))
        {
          *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 2;
          if (*(int *)(param_1 + 0x124) == 0) goto LAB_00042480;
          tmp_pi8 = (int *)(param_1 + 0x124);
          goto LAB_00042485;
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
LAB_00042480:
      tmp_b9 = tmp_pi8 != (int *)0x0;
LAB_00042485:
      if (!tmp_b9) goto LAB_00042447;
      tmp_i6 = *tmp_pi8;
    }
    (**(void **)(DC + 0x88))(tmp_i6,6);
  }
LAB_00042447:
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

void Item_SetMouseOver(int param_1,int param_2) {
  if (param_1 != 0) {
    if (param_2 != 0) {
      *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 1;
      return;
    }
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xfffffffe;
  }
  return;
}

void Item_SetScreenCoords(float *param_1,float param_2,float param_3) {
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

void Item_SetTextExtents(float *param_1,int *param_2,int *param_3,float param_4) {
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
      goto LAB_000456b7;
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
      goto LAB_000456b7;
    }
  }
  if (tmp_f1 == 4.2039e-45) {
    tmp_i2 = (**(void **)(DC + 0x18))(param_4,param_1[0x37],0);
    local_12c = local_12c + tmp_i2;
  }
LAB_000456b7:
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

uint Item_SettingShow(int param_1,int param_2) {
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

uint Item_SettingShow_constprop_35(int param_1) {
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

bool Item_SettingShow_constprop_36(int param_1) {
  uint tmp_u1;
  char local_40c [1024];

  trap_Cvar_VariableStringBuffer("cg_ui_voteFlags",local_40c,0x400);
  tmp_u1 = strtol(local_40c,(char **)0x0,10);
  return *(uint *)(param_1 + 0x264) != (tmp_u1 & *(uint *)(param_1 + 0x264));
}

void Item_SetupKeywordHash(void) {
  uint32_t *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  char tmp_c6;
  char *tmp_pc7;
  uint32_t **local_18;
  uint32_t *local_14;

  local_14 = &itemParseKeywordHash;
  tmp_pu4 = &itemParseKeywordHash;
  for (tmp_i5 = 0x200; tmp_i5 != 0; tmp_i5 = tmp_i5 + -1) {
    *tmp_pu4 = 0;
    tmp_pu4 = tmp_pu4 + 1;
  }
  if (itemParseKeywords != (uint32_t *)0x0) {
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
      tmp_pu1 = (uint32_t *)*tmp_pu4;
      *tmp_pu4 = local_18;
      local_18[2] = tmp_pu1;
      tmp_pc7 = local_18[3];
      local_18 = local_18 + 3;
    } while (tmp_pc7 != (char *)0x0);
  }
  return;
}

uint32_t Item_Slider_HandleKey(float *param_1,int param_2) {
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
  tmp_f1 = *(float *)(&g_dat_0002003c + DC);
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
      goto LAB_0004503d;
    }
  }
  if (tmp_f6 <= tmp_f7) {
    return 0;
  }
LAB_0004503d:
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
        tmp_u9 = va("%f",(double)(*pfVar3 + (pfVar3[1] - *pfVar3) * ((tmp_f8 - tmp_f2) / 96.0)));
        (*tmp_pc4)(param_1[0x45],tmp_u9);
        return 1;
      }
    }
  }
  return 0;
}

uint32_t Item_Slider_OverSlider(float *param_1,float param_2,float param_3) {
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
  tmp_l7 = (long double)*(float *)(&g_dat_0002003c + DC);
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

void Item_Slider_Paint(float *param_1) {
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
  (**(void **)(DC + 8))(tmp_f1,tmp_f2 + 1.0,0x42c00000,0x41200000,*(uint32_t *)(DC + 0x1e300));
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

long double Item_Slider_ThumbPosition(float *param_1) {
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

void Item_StartCapture(float *param_1,uint32_t param_2) {
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
      tmp_l10 = (long double)*(float *)(&g_dat_0002003c + DC);
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
      _DAT_002ee1ec = param_2;
      _DAT_002ee1f0 = (float)*(int *)(DC + 0x124);
      _DAT_002ee1f4 = (float)*(int *)(DC + 0x128);
      _DAT_002ee1f8 = param_1;
      return;
    }
  }
  tmp_u5 = Item_ListBox_OverLB(param_1,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128));
  if ((tmp_u5 & 0x1800) == 0) {
    if ((tmp_u5 & 0x2000) != 0) {
      _DAT_002ee1f8 = param_1;
      itemCapture = param_1;
      _DAT_002ee1ec = param_2;
      _DAT_002ee1f0 = (float)*(int *)(DC + 0x124);
      _DAT_002ee1f4 = (float)*(int *)(DC + 0x128);
      captureData = &scrollInfo;
      captureFunc = Scroll_ListBox_ThumbFunc;
    }
  }
  else {
    _DAT_002ee1fc = tmp_u5 >> 0xb & 1;
    captureData = &scrollInfo;
    _DAT_002ee1ec = param_2;
    _DAT_002ee1f8 = param_1;
    captureFunc = Scroll_ListBox_AutoFunc;
    scrollInfo = *(int *)(DC + 0x11c) + 500;
    g_dat_002ee1e4 = *(int *)(DC + 0x11c) + 0x96;
    g_dat_002ee1e8 = 500;
    itemCapture = param_1;
  }
  return;
}

void Item_StopCapture(void) {
  return;
}

void Item_TextColor(int param_1,float *param_2) {
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
LAB_00045904:
    if ((*(uint *)(param_1 + 0x48) & 0x8000002) != 0x8000002) goto LAB_00045917;
LAB_00045af0:
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
      goto LAB_00045904;
    }
    tmp_f1 = tmp_f1 + *(float *)(param_1 + 0x80);
    if (tmp_f1 < tmp_f2) {
      *(float *)(param_1 + 0x80) = tmp_f1;
      goto LAB_00045904;
    }
    *(uint *)(param_1 + 0x48) = tmp_u6 & 0xffffffbf;
    *(float *)(param_1 + 0x80) = tmp_f2;
    if ((*(uint *)(param_1 + 0x48) & 0x8000002) == 0x8000002) goto LAB_00045af0;
LAB_00045917:
    if ((*(int *)(param_1 + 0xe4) != 1) || ((*(int *)(DC + 0x11c) / 200 & 1U) != 0)) {
      *param_2 = *(float *)(param_1 + 0x74);
      param_2[1] = *(float *)(param_1 + 0x78);
      param_2[2] = *(float *)(param_1 + 0x7c);
      param_2[3] = *(float *)(param_1 + 0x80);
      goto LAB_0004593b;
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
LAB_0004593b:
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

bool Item_TextField_HandleKey(int param_1,uint param_2) {
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
      goto LAB_0004d20b;
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
    goto LAB_0004d060;
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
LAB_0004d20b:
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
LAB_0004cffa:
    if ((*(int *)(tmp_i2 + 0x10) != 0) && (*(int *)(tmp_i2 + 0x10) <= tmp_i10)) {
      return true;
    }
  }
  else {
    tmp_i10 = (**(void **)(DC + 0x84))();
    if (tmp_i10 != 0) {
      tmp_i10 = *(int *)(param_1 + 0x24c);
      goto LAB_0004cffa;
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
LAB_0004d060:
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
          goto LAB_0004d33a;
        }
        tmp_i10 = *(int *)(tmp_i10 + 0x514 + tmp_i2 * 4);
LAB_0004d4b6:
        if ((tmp_i10 != 0) && ((*(int *)(tmp_i10 + 200) == 9 || (*(int *)(tmp_i10 + 200) == 4)))) {
          g_editItem = tmp_i10;
        }
        goto LAB_0004d083;
      }
LAB_0004d33a:
      tmp_i9 = Item_SetFocus(*(uint32_t *)(tmp_i10 + 0x514 + tmp_i9 * 4),(float)*(int *)(DC + 0x124),
                            (float)*(int *)(DC + 0x128));
      if (tmp_i9 != 0) {
        pfVar4 = *(float **)(tmp_i10 + 0x514 + *(int *)(tmp_i10 + 200) * 4);
        Menu_HandleMouseMove(tmp_i10,*pfVar4 + 1.0,pfVar4[1] + 1.0);
        tmp_i10 = *(int *)(tmp_i10 + 0x514 + *(int *)(tmp_i10 + 200) * 4);
        goto LAB_0004d4b6;
      }
      tmp_i9 = *(int *)(tmp_i10 + 200);
    }
    *(int *)(tmp_i10 + 200) = tmp_i2;
  }
LAB_0004d083:
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

void Item_TextField_Paint(float *param_1) {
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
      goto joined_r0x00046a43;
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
joined_r0x00046a43:
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

void Item_Text_AutoWrapped_Paint(float *param_1) {
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
LAB_00045e30:
        if ((((local_860 == 0) || ((float)tmp_i4 <= param_1[2])) && (tmp_b5 != 10)) && (tmp_b5 != 0))
        goto LAB_00045e54;
        if (tmp_i6 != 0) {
LAB_00045e88:
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
          goto LAB_00045e30;
        }
        if ((float)tmp_i4 <= param_1[2]) goto LAB_00045e30;
        local_860 = tmp_i6;
        local_858 = tmp_i4;
        local_850 = tmp_pb7;
        if (tmp_i6 != 0) goto LAB_00045e88;
        local_860 = 0;
LAB_00045e54:
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

void Item_Text_Paint(float *param_1) {
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
      if (((uint)param_1[0x12] & 0x20000000) == 0) goto LAB_00046271;
      tmp_d7 = strtod(__nptr,(char **)0x0);
      tmp_u6 = va("%.2f",tmp_d7);
      Q_strncpyz(__nptr,tmp_u6,0x400);
      param_1[0x30] = 0.0;
    }
    else {
      COM_StripExtension(__nptr,__nptr);
      param_1[0x30] = 0.0;
    }
    if (param_1[0x32] == 2.10195e-44) goto LAB_00046530;
  }
  else {
LAB_00046271:
    if (param_1[0x32] == 2.10195e-44) {
LAB_00046530:
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
          (param_1[0x34] != 4.2039e-45)) && (param_1[0x32] != 2.10195e-44)) goto LAB_000462d5;
    }
  }
  tmp_i1 = (**(void **)(DC + 0x18))(__nptr,param_1[0x37],0);
  if (param_1[0x32] == 1.12104e-44) {
    tmp_f2 = param_1[0x34];
    if (1 < (int)tmp_f2 - 1U) goto LAB_000463ec;
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
LAB_000463ec:
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
LAB_000462d5:
  if (*__nptr != '\0') {
    Item_TextColor(param_1,local_51c);
    (**(void **)(DC + 0x10))
              (param_1[0x2e],param_1[0x2f],param_1[0x37],local_51c,__nptr,0,0,param_1[0x39]);
  }
  return;
}

void Item_Text_Wrapped_Paint(int param_1) {
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

void Item_UpdatePosition(float *param_1) {
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

uint32_t Item_ValidateTooltipData(int param_1) {
  uint32_t tmp_u1;

  if (*(int *)(param_1 + 0x270) != 0) {
    return 1;
  }
  tmp_u1 = Item_ValidateTooltipData_part_24();
  return tmp_u1;
}

uint32_t Item_ValidateTooltipData_part_24(int param_1) {
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

void Item_ValidateTypeData(int param_1) {
  if (*(int *)(param_1 + 0x250) != 0) {
    return;
  }
  Item_ValidateTypeData_part_21();
  return;
}

void Item_ValidateTypeData_part_21(int param_1) {
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

uint32_t Item_YesNo_HandleKey(float *param_1,int param_2) {
  float tmp_f1;
  void *tmp_pc2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint32_t tmp_u6;
  long double tmp_l7;

  tmp_f4 = (float)*(int *)(DC + 0x124);
  if (param_1 != (float *)0x0) {
    tmp_f1 = *(float *)(&g_dat_0002003c + DC);
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

void Item_YesNo_Paint(int param_1) {
  int tmp_i1;
  uint tmp_u2;
  float tmp_f3;
  uint32_t *tmp_pu4;
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
      tmp_pu4 = &g_dat_00058959;
    }
    else {
      tmp_pu4 = &g_dat_00058955;
    }
    (**(void **)(DC + 0x10))
              (*(uint32_t *)(param_1 + 0xb8),*(uint32_t *)(param_1 + 0xbc),
               *(uint32_t *)(param_1 + 0xdc),&local_2c,tmp_pu4,0,0,*(uint32_t *)(param_1 + 0xe4))
    ;
    return;
  }
  Item_Text_Paint(param_1);
  if (local_38 == 0.0) {
    tmp_pu4 = &g_dat_00058959;
  }
  else {
    tmp_pu4 = &g_dat_00058955;
  }
  (**(void **)(DC + 0x10))
            (*(float *)(param_1 + 0xb8) + *(float *)(param_1 + 0xc0) + 8.0,
             *(uint32_t *)(param_1 + 0xbc),*(uint32_t *)(param_1 + 0xdc),&local_2c,tmp_pu4,0,0,
             *(uint32_t *)(param_1 + 0xe4));
  return;
}
