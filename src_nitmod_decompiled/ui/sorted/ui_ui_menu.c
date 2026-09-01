/**
 * @file ui_ui_menu.c
 * @brief ui_menu
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 */

#include "ui_types.h"
#include "ui_globals.h"
#include "ui_imports.h"
#include "ui_ui_menu.h"

int Menu_ClearFocus(int param_1) {
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

void Menu_FadeItemByName(uint32_t param_1,uint32_t param_2,int param_3) {
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

void Menu_FadeMenuByName(uint32_t param_1,uint32_t param_2,int param_3) {
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *tmp_pu5;

  if (0 < menuCount) {
    tmp_pu5 = &g_dat_003f16a0;
    tmp_i4 = 0;
    do {
      tmp_i3 = Q_stricmp(*tmp_pu5,param_1);
      if (tmp_i3 == 0) {
        tmp_pi1 = &g_dat_003f1740 + tmp_i4 * 0x346;
        if (*tmp_pi1 < 1) {
          return;
        }
        tmp_i3 = 0;
        if (param_3 == 0) {
          do {
            tmp_i2 = tmp_i4 * 0x346 + tmp_i3;
            tmp_i3 = tmp_i3 + 1;
            *(uint *)((&g_dat_003f1b94)[tmp_i2] + 0x48) =
                 *(uint *)((&g_dat_003f1b94)[tmp_i2] + 0x48) & 0xffffffdf | 0x44;
          } while (tmp_i3 < *tmp_pi1);
          return;
        }
        do {
          tmp_i2 = tmp_i4 * 0x346 + tmp_i3;
          tmp_i3 = tmp_i3 + 1;
          *(uint *)((&g_dat_003f1b94)[tmp_i2] + 0x48) =
               *(uint *)((&g_dat_003f1b94)[tmp_i2] + 0x48) & 0xffffffbf | 0x24;
        } while (tmp_i3 < *tmp_pi1);
        return;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu5 = tmp_pu5 + 0x346;
    } while (tmp_i4 < menuCount);
  }
  return;
}

uint32_t Menu_FindItemByName(int param_1,int param_2) {
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

uint32_t * Menu_GetFocused(void) {
  uint tmp_u1;
  uint *tmp_pu2;
  int tmp_i3;

  if (menuCount < 1) {
    return (uint32_t *)0x0;
  }
  if ((g_dat_003f16c8 & 6) == 6) {
    tmp_i3 = 0;
  }
  else {
    tmp_pu2 = &g_dat_003f23e0;
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

int Menu_GetFocusedItem(int param_1) {
  int tmp_i1;
  int tmp_i2;

  if ((param_1 == 0) || (*(int *)(param_1 + 0xc0) < 1)) {
LAB_0004a89a:
    tmp_i1 = 0;
  }
  else {
    tmp_i1 = *(int *)(param_1 + 0x514);
    if ((*(byte *)(tmp_i1 + 0x48) & 2) == 0) {
      tmp_i2 = 0;
      do {
        tmp_i2 = tmp_i2 + 1;
        if (tmp_i2 == *(int *)(param_1 + 0xc0)) goto LAB_0004a89a;
        tmp_i1 = *(int *)(param_1 + 0x514 + tmp_i2 * 4);
      } while ((*(byte *)(tmp_i1 + 0x48) & 2) == 0);
    }
  }
  return tmp_i1;
}

uint32_t Menu_GetMatchingItemByNumber(int param_1,int param_2,char *param_3) {
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

void Menu_HandleKey(int param_1,int param_2,int param_3) {
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
    goto LAB_0004d60d;
  }
  if (((param_2 == 0xa9) || (param_2 == 0xd)) && (*(int *)(param_1 + 0xe4) != 0)) goto LAB_0004d84e;
  if (g_waitingForKey != 0) {
    Item_Bind_HandleKey(g_bindItem,param_2,param_3);
    return;
  }
  if (g_editingField == 0) {
LAB_0004d9a9:
    tmp_b2 = true;
LAB_0004d60d:
    if (param_1 == 0) {
      return;
    }
    if (tmp_b2) goto LAB_0004d6d0;
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
      goto LAB_0004d60d;
    }
    g_editingField = 0;
    g_editItem = 0;
    tmp_i4 = *(int *)(DC + 0x128);
    tmp_i3 = *(int *)(DC + 0x124);
    if (menuCount < 1) goto LAB_0004d9a9;
    if ((g_dat_003f16c8 & 6) == 6) {
      tmp_i8 = 0;
      tmp_u9 = g_dat_003f16c8;
    }
    else {
      tmp_pu7 = &g_dat_003f23e0;
      tmp_i8 = 0;
      do {
        tmp_i8 = tmp_i8 + 1;
        if (tmp_i8 == menuCount) goto LAB_0004db28;
        tmp_u9 = *tmp_pu7;
        tmp_pu7 = tmp_pu7 + 0x346;
      } while ((tmp_u9 & 6) != 6);
    }
    if ((tmp_u9 & 0x200000) == 0) {
LAB_0004db28:
      tmp_i8 = 0;
      tmp_pu10 = &Menus;
      do {
        tmp_i8 = tmp_i8 + 1;
        Menu_HandleMouseMove(tmp_pu10,(float)tmp_i3,(float)tmp_i4);
        tmp_pu10 = tmp_pu10 + 0x346;
      } while (tmp_i8 < menuCount);
      tmp_b2 = true;
      goto LAB_0004d60d;
    }
    Menu_HandleMouseMove(&Menus + tmp_i8 * 0x346,(float)tmp_i3,(float)tmp_i4);
    if (param_1 == 0) {
      return;
    }
LAB_0004d6d0:
    if ((((*(byte *)(param_1 + 0x4a) & 0x20) == 0) &&
        (tmp_i4 = Rect_ContainsPoint(param_1,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128))
        , tmp_i4 == 0)) && ((inHandleKey_10166 == 0 && (param_2 - 0xb2U < 3)))) {
      inHandleKey_10166 = 1;
      Menus_HandleOOBClick(param_1,param_2,param_3);
      inHandleKey_10166 = 0;
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
    goto LAB_0004d677;
  }
  if (param_3 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0xd14) == 0) {
    if ((param_2 - 1U < 0xff) && (*(int *)(param_1 + 0xf4 + param_2 * 4) != 0)) goto LAB_0004d84e;
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
LAB_0004d84e:
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
        goto LAB_0004da0a;
      }
LAB_0004d99f:
      Menu_SetNextCursorItem(param_1);
      return;
    }
    if (param_2 == 9) {
      tmp_i4 = (**(void **)(DC + 0xc0))(0x8a);
      if (tmp_i4 != 0) {
        Menu_SetPrevCursorItem(param_1);
        return;
      }
      goto LAB_0004d99f;
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
        goto LAB_0004d99f;
      }
LAB_0004da0a:
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
        goto LAB_0004d677;
      }
      if ((tmp_i3 != 9) && (tmp_i3 != 4)) {
        tmp_i4 = Rect_ContainsPoint(tmp_i4,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128));
        if (tmp_i4 == 0) {
          return;
        }
        goto LAB_0004d677;
      }
      tmp_i3 = Rect_ContainsPoint(tmp_i4,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128));
      if (tmp_i3 == 0) {
        return;
      }
      if (*(int *)(tmp_i4 + 0x250) != 0) {
        *(uint32_t *)(*(int *)(tmp_i4 + 0x250) + 0x18) = 0;
      }
      goto LAB_0004da3f;
    }
    if (param_2 != 0xb4) {
      return;
    }
  }
  if (tmp_i4 == 0) {
    return;
  }
  if ((*(int *)(tmp_i4 + 200) != 9) && (*(int *)(tmp_i4 + 200) != 4)) {
LAB_0004d677:
    Item_RunScript_constprop_37();
    return;
  }
LAB_0004da3f:
  *(uint32_t *)(tmp_i4 + 0x24c) = 0;
  g_editingField = 1;
  g_editItem = tmp_i4;
  return;
}

void Menu_HandleMouseMove(int param_1,float param_2,float param_3) {
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
LAB_0004c548:
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
LAB_0004c3d0:
            tmp_i8 = *(int *)(param_1 + 0xc0);
            if (tmp_i8 <= tmp_i10) goto LAB_0004c548;
          }
          else {
            tmp_f3 = pfVar11[0x48];
            if (((uint)tmp_f3 & 3) != 0) {
              tmp_i8 = Item_EnableShowViaCvar(pfVar11,1);
              if (tmp_i8 == 0) goto LAB_0004c3d0;
              pfVar11 = (float *)*tmp_pi12;
              tmp_f3 = pfVar11[0x48];
            }
            if (((uint)tmp_f3 & 0xc) == 0) {
              tmp_b2 = *(byte *)(pfVar11 + 0x98);
            }
            else {
              tmp_i8 = Item_EnableShowViaCvar(pfVar11,4);
              if (tmp_i8 == 0) goto LAB_0004c3d0;
              pfVar11 = (float *)*tmp_pi12;
              tmp_b2 = *(byte *)(pfVar11 + 0x98);
            }
            if ((tmp_b2 & 3) == 0) {
              tmp_f3 = pfVar11[0x99];
            }
            else {
              tmp_i8 = Item_SettingShow_constprop_35();
              if (tmp_i8 == 0) goto LAB_0004c3d0;
              pfVar11 = (float *)*tmp_pi12;
              tmp_f3 = pfVar11[0x99];
            }
            if (tmp_f3 != 0.0) {
              tmp_i8 = Item_SettingShow_constprop_36();
              if (tmp_i8 == 0) goto LAB_0004c3d0;
              pfVar11 = (float *)*tmp_pi12;
            }
            if (pfVar11 == (float *)0x0) {
LAB_0004c3c0:
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
              goto LAB_0004c3d0;
            }
            tmp_f3 = *(float *)(&g_dat_0002003c + DC);
            if (tmp_f3 <= 1.3333334) {
              if (*pfVar11 < param_2) {
                tmp_f6 = *pfVar11 + pfVar11[2];
                tmp_f5 = param_2;
                goto LAB_0004c372;
              }
              goto LAB_0004c3c0;
            }
            tmp_f4 = tmp_f3 * 0.75;
            tmp_f5 = param_2 * tmp_f4;
            if (tmp_f5 <= tmp_f4 * *pfVar11) goto LAB_0004c3c0;
            tmp_f6 = *pfVar11 + pfVar11[2];
            if (1.3333334 < tmp_f3) {
              tmp_f6 = tmp_f4 * tmp_f6;
            }
LAB_0004c372:
            if (((tmp_f6 <= tmp_f5) || (param_3 <= pfVar11[1])) ||
               (pfVar11[1] + pfVar11[3] <= param_3)) goto LAB_0004c3c0;
            if (!tmp_b7) goto LAB_0004c3d0;
            if ((pfVar11[0x32] == 0.0) && (pfVar11[0x3a] != 0.0)) {
              tmp_u9 = Item_CorrectedTextRect();
              tmp_i8 = Rect_ContainsPoint(tmp_u9,param_2,param_3);
              if (tmp_i8 != 0) goto LAB_0004c528;
            }
            else {
LAB_0004c528:
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

float * Menu_HitTest(int param_1,float param_2,float param_3) {
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
        tmp_f1 = *(float *)(&g_dat_0002003c + DC);
        if (1.3333334 < tmp_f1) {
          tmp_f5 = tmp_f1 * 0.75;
          tmp_f3 = param_2 * tmp_f5;
          if (tmp_f5 * *pfVar2 < tmp_f3) {
            tmp_f4 = *pfVar2 + pfVar2[2];
            if (1.3333334 < tmp_f1) {
              tmp_f4 = tmp_f4 * tmp_f5;
            }
            goto LAB_000441fc;
          }
        }
        else if (*pfVar2 < param_2) {
          tmp_f4 = *pfVar2 + pfVar2[2];
          tmp_f3 = param_2;
LAB_000441fc:
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

void Menu_Init(uint32_t *param_1) {
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
LAB_0004a800:
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
      goto LAB_0004a800;
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
    if (((uint)param_1 & 2) == 0) goto LAB_0004a761;
  }
  else {
    tmp_pu6 = (uint32_t *)((int)param_1 + 1);
    tmp_u5 = 0xb7;
    tmp_b2 = true;
    *(uint8_t *)param_1 = 0;
    if (((uint)tmp_pu6 & 2) == 0) goto LAB_0004a761;
    tmp_u5 = 0xb7;
    tmp_b2 = true;
  }
  *(uint16_t *)tmp_pu6 = 0;
  tmp_u5 = tmp_u5 - 2;
  tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
LAB_0004a761:
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

int Menu_ItemsMatchingGroup(int param_1,char *param_2) {
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
LAB_0003fae0:
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
      if (tmp_i2 == -1) goto LAB_0003fae0;
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

void Menu_OrbitItemByName
               (uint32_t param_1,uint32_t param_2,float param_3,float param_4,float param_5,
               float param_6,float param_7) {
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

void Menu_Paint(int param_1,int param_2) {
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

void Menu_Paint_part_20(uint32_t *param_1,int param_2) {
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

int Menu_Parse(uint32_t param_1,uint32_t param_2) {
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
  uStack_460 = 0x4ec10;
  local_444 = (uint32_t *)local_458;
  tmp_i2 = trap_PC_ReadToken();
  if ((tmp_i2 == 0) || (local_424 != '{')) {
    return 0;
  }
  local_440 = "unknown menu keyword %s";
  local_424 = '{';
  local_458 = (char *)local_444;
joined_r0x0004ec4d:
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
    uStack_460 = 0x4ec71;
    local_444 = (uint32_t *)local_458;
    tmp_i2 = trap_PC_ReadToken();
    if (tmp_i2 == 0) {
      local_458 = "end of file inside menu\n";
      local_45c = param_1;
      uStack_460 = 0x4edbe;
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
      uStack_460 = 0x4ed05;
      local_458 = &local_424;
      tmp_i2 = Q_stricmp();
      if (tmp_i2 == 0) {
        local_458 = (char *)param_1;
        local_45c = param_2;
        uStack_460 = 0x4ed21;
        tmp_i2 = (*(void *)tmp_pu3[1])();
        local_458 = (char *)local_444;
        if (tmp_i2 == 0) {
          local_458 = "couldn\'t parse menu keyword %s";
          local_45c = param_1;
          uStack_460 = 0x4ed4a;
          local_454 = &local_424;
          local_444 = (uint32_t *)tmp_i2;
          PC_SourceError();
          return (int)local_444;
        }
        goto joined_r0x0004ec4d;
      }
    }
    local_45c = param_1;
    uStack_460 = 0x4ed73;
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
    (&g_dat_003f1748)[tmp_i1 * 0x346] = 0xffffffff;
    *(uint32_t *)(&g_dat_003f1754 + tmp_i4) = *(uint32_t *)(tmp_i2 + 0x1e32c);
    *(uint32_t *)(&g_dat_003f1750 + tmp_i4) = *(uint32_t *)(tmp_i2 + 0x1e324);
    *(uint32_t *)(&g_dat_003f174c + tmp_i4) = *(uint32_t *)(tmp_i2 + 0x1e328);
    *(uint32_t *)(&g_dat_003f2394 + tmp_i4) = 0;
    tmp_u3 = 0;
    do {
      *(uint32_t *)((int)tmp_pu6 + tmp_u3) = 0;
      *(uint32_t *)((int)&g_dat_003f1684 + tmp_u3 + tmp_i5) = 0;
      tmp_u3 = tmp_u3 + 8;
    } while (tmp_u3 < 0xb8);
    *(uint32_t *)(&g_dat_003f16c4 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_dat_003f1700 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_dat_003f16fc + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_dat_003f16f8 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_dat_003f16f4 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_dat_003f16b0 + tmp_i5) = 0xffffffff;
    tmp_i4 = Menu_Parse(param_1,tmp_pu6);
    if (tmp_i4 != 0) {
      if ((&g_dat_003f173c)[tmp_i1 * 0x346] != 0) {
        (&Menus)[tmp_i1 * 0x346] = 0;
        (&g_dat_003f1684)[tmp_i1 * 0x346] = 0;
        (&g_dat_003f1688)[tmp_i1 * 0x346] = 0x44200000;
        (&g_dat_003f168c)[tmp_i1 * 0x346] = 0x43f00000;
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

  uStack_14 = 0x4f0a9;
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
        if (tmp_i3 <= tmp_i5) goto LAB_0004f13e;
      }
      Menu_Paint_part_20();
      tmp_i5 = tmp_i5 + 1;
      tmp_pu7 = tmp_pu7 + 0x346;
      tmp_i3 = menuCount;
    } while (tmp_i5 < menuCount);
LAB_0004f13e:
    if (0 < tmp_i3) {
      tmp_i5 = 0;
      do {
        while ((tmp_pu6[0x12] & 0x2000004) != 0x2000004) {
LAB_0004f160:
          tmp_i5 = tmp_i5 + 1;
          tmp_pu6 = tmp_pu6 + 0x346;
          if (tmp_i3 <= tmp_i5) goto LAB_0004f1b0;
        }
        if (((tmp_pu6[0x10] == 0) || (*(void **)(DC + 100) == (void *)0x0)) ||
           (tmp_i3 = (**(void **)(DC + 100))(tmp_pu6[0x10]), tmp_i3 != 0)) {
          Menu_Paint_part_20();
          tmp_i3 = menuCount;
          goto LAB_0004f160;
        }
        tmp_i5 = tmp_i5 + 1;
        tmp_pu6 = tmp_pu6 + 0x346;
        tmp_i3 = menuCount;
      } while (tmp_i5 < menuCount);
    }
  }
LAB_0004f1b0:
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
    if (*(float *)(&g_dat_0002003c + DC) <= 1.3333334) {
      tmp_i5 = 0;
      do {
        if ((((*pfVar4 < tmp_f2) && (tmp_f2 < *pfVar4 + pfVar4[2])) && (pfVar4[1] < tmp_f3)) &&
           (tmp_f3 < pfVar4[1] + pfVar4[3])) goto LAB_0004f424;
        tmp_i5 = tmp_i5 + 1;
        pfVar4 = pfVar4 + 0x346;
      } while (tmp_i5 != menuCount);
    }
    else {
      tmp_f1 = *(float *)(&g_dat_0002003c + DC) * 0.75;
      tmp_i5 = 0;
      do {
        if (((tmp_f1 * *pfVar4 < tmp_f2 * tmp_f1) && (tmp_f2 * tmp_f1 < (*pfVar4 + pfVar4[2]) * tmp_f1))
           && ((pfVar4[1] < tmp_f3 && (tmp_f3 < pfVar4[1] + pfVar4[3])))) {
LAB_0004f424:
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
      if ((g_dat_003f16c8 & 6) == 6) {
        tmp_i1 = 0;
        tmp_u2 = g_dat_003f16c8;
      }
      else {
        tmp_pu3 = &g_dat_003f23e0;
        tmp_i1 = 0;
        do {
          tmp_i1 = tmp_i1 + 1;
          if (tmp_i1 == menuCount) goto LAB_0004f4af;
          tmp_u2 = *tmp_pu3;
          tmp_pu3 = tmp_pu3 + 0x346;
        } while ((tmp_u2 & 6) != 6);
      }
      if ((tmp_u2 & 0x200000) == 0) {
LAB_0004f4af:
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
    if (*(float *)(&g_dat_0002003c + DC) <= 1.3333334) {
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
      tmp_f1 = *(float *)(&g_dat_0002003c + DC) * 0.75;
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
  if (*(float *)(&g_dat_0002003c + DC) <= 1.3333334) {
    tmp_i5 = 0;
    do {
      if ((((*pfVar6 < tmp_f3) && (tmp_f3 < *pfVar6 + pfVar6[2])) && (pfVar6[1] < tmp_f4)) &&
         (tmp_f4 < pfVar6[1] + pfVar6[3])) goto LAB_0004f7e4;
      tmp_i5 = tmp_i5 + 1;
      pfVar6 = pfVar6 + 0x346;
    } while (tmp_i5 != menuCount);
  }
  else {
    tmp_f2 = *(float *)(&g_dat_0002003c + DC) * 0.75;
    tmp_i5 = 0;
    do {
      if (((tmp_f2 * *pfVar6 < tmp_f3 * tmp_f2) && (tmp_f3 * tmp_f2 < (*pfVar6 + pfVar6[2]) * tmp_f2)) &&
         ((pfVar6[1] < tmp_f4 && (tmp_f4 < pfVar6[1] + pfVar6[3])))) goto LAB_0004f7e4;
      tmp_i5 = tmp_i5 + 1;
      pfVar6 = pfVar6 + 0x346;
    } while (tmp_i5 != menuCount);
  }
  if ((g_dat_003f16c8 & 6) != 6) {
    tmp_pu7 = &g_dat_003f23e0;
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
LAB_0004f7e4:
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

bool PC_String_Parse_Trans(uint32_t param_1,uint32_t *param_2)

{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t local_424 [16];
  uint8_t local_414 [1040];

  tmp_i1 = trap_PC_ReadToken(param_1,local_424);
  if (tmp_i1 != 0) {
    tmp_u2 = String_Alloc(local_414);
    *param_2 = tmp_u2;
  }
  return tmp_i1 != 0;
}

bool PC_Rect_Parse(uint32_t param_1,int param_2)

{
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_1,param_2);
  if (((tmp_i1 != 0) && (tmp_i1 = PC_Float_Parse(param_1,param_2 + 4), tmp_i1 != 0)) &&
     (tmp_i1 = PC_Float_Parse(param_1,param_2 + 8), tmp_i1 != 0)) {
    tmp_i1 = PC_Float_Parse(param_1,param_2 + 0xc);
    return tmp_i1 != 0;
  }
  return false;
}

bool BG_RectContainsPoint
               (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6)

{
  if (((param_1 < param_5) && (param_5 < param_3 + param_1)) && (param_2 < param_6)) {
    return param_6 < param_4 + param_2;
  }
  return false;
}

longlong BG_CursorInRect(float *param_1)

{
  uint tmp_u1;
  uint local_8;

  local_8 = 0x4fb26;
  tmp_u1 = *(uint *)(DC + 0x128);
  if (((*param_1 < (float)*(int *)(DC + 0x124)) &&
      (local_8 = tmp_u1, (float)*(int *)(DC + 0x124) < *param_1 + param_1[2])) &&
     (param_1[1] < (float)(int)tmp_u1)) {
    return CONCAT44(tmp_u1,(uint)((float)(int)tmp_u1 < param_1[1] + param_1[3]));
  }
  return (ulonglong)local_8 << 0x20;
}

void BG_PanelButton_RenderEdit(int param_1)

{
  uint32_t *tmp_pu1;
  void *tmp_pc2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  int tmp_i6;
  uint32_t *tmp_pu7;
  int tmp_i8;
  uint32_t tmp_u9;
  char *tmp_pc10;
  char local_11d [269];

  if (*(int *)(param_1 + 0x18) == 0) {
    trap_Cvar_VariableStringBuffer(*(uint32_t *)(param_1 + 4),local_11d,0x101);
    if ((param_1 == bg_focusButton) && ((*(int *)(DC + 0x11c) / 1000 & 1U) != 0)) {
      tmp_i6 = trap_Key_GetOverstrikeMode();
      if (tmp_i6 == 0) {
        tmp_pu7 = &g_dat_00058a0a;
      }
      else {
        tmp_pu7 = &g_dat_00058a02;
      }
    }
    else {
      tmp_pu7 = &g_dat_0005661b;
    }
    tmp_i6 = -1;
    Q_strcat(local_11d,0x101,tmp_pu7);
    tmp_pc5 = local_11d;
    do {
      tmp_pc10 = tmp_pc5;
      tmp_i6 = tmp_i6 + 1;
      if (*tmp_pc10 == '\0') {
        tmp_pc10 = local_11d + tmp_i6;
        break;
      }
      tmp_i8 = (**(void **)(DC + 0x1c))
                        (tmp_pc10,**(uint32_t **)(param_1 + 0x38),0,
                         (*(uint32_t **)(param_1 + 0x38))[8]);
      tmp_pc5 = tmp_pc10 + 1;
    } while (*(float *)(param_1 + 0x10) < (float)tmp_i8);
    tmp_pc2 = *(void **)(DC + 0x14);
    tmp_u3 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
    tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x18);
    tmp_u9 = va(&g_dat_00055b27,tmp_pc10);
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    (*tmp_pc2)(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14),
              *tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u9,0,0,tmp_u4,tmp_u3);
    return;
  }
  if ((param_1 == bg_focusButton) && ((*(int *)(DC + 0x11c) / 1000 & 1U) != 0)) {
    tmp_i6 = (**(void **)(DC + 0x84))();
    if (tmp_i6 == 0) {
      tmp_pc5 = (char *)va(&g_dat_00058a06,*(uint32_t *)(param_1 + 4));
    }
    else {
      tmp_pc5 = (char *)va(&g_dat_000589fe,*(uint32_t *)(param_1 + 4));
    }
  }
  else {
    tmp_pc5 = (char *)va("^7%s ",*(uint32_t *)(param_1 + 4));
  }
  do {
    tmp_pc10 = tmp_pc5;
    if (*tmp_pc10 == '\0') break;
    tmp_i6 = (**(void **)(DC + 0x1c))
                      (tmp_pc10,**(uint32_t **)(param_1 + 0x38),0,
                       (*(uint32_t **)(param_1 + 0x38))[8]);
    tmp_pc5 = tmp_pc10 + 1;
  } while (*(float *)(param_1 + 0x10) < (float)tmp_i6);
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  (**(void **)(DC + 0x14))
            (*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14),
             *tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_pc10,0,0,tmp_pu1[6],tmp_pu1[8]);
  return;
}

uint32_t BG_PanelButton_EditClick(int param_1,uint param_2)

{
  uint tmp_u1;
  uint tmp_u2;
  uint *tmp_pu3;
  uint *tmp_pu4;
  char *__s;
  int tmp_i5;
  bool tmp_b6;
  size_t local_128;
  uint32_t local_120;
  uint32_t local_11c;

  if (param_2 == 0xb2) {
    if (((((*(float *)(param_1 + 8) < (float)*(int *)(DC + 0x124)) &&
          ((float)*(int *)(DC + 0x124) < *(float *)(param_1 + 8) + *(float *)(param_1 + 0x10))) &&
         (*(float *)(param_1 + 0xc) < (float)*(int *)(DC + 0x128))) &&
        ((float)*(int *)(DC + 0x128) < *(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14))) ||
       (param_1 != bg_focusButton)) {
      bg_focusButton = param_1;
      return 1;
    }
    bg_focusButton = 0;
    if (*(void **)(param_1 + 0x48) != (void *)0x0) {
      (**(void **)(param_1 + 0x48))(param_1);
      return 0;
    }
  }
  else if (param_1 == bg_focusButton) {
    tmp_i5 = *(int *)(param_1 + 0x18);
    tmp_b6 = tmp_i5 == 0;
    if (tmp_b6) {
      (**(void **)(DC + 0x70))(*(uint32_t *)(param_1 + 4),&local_11c,0x100);
      tmp_pu4 = &local_11c;
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
      __s = (char *)0x0;
      local_128 = (int)tmp_pu4 + ((-3 - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) - (int)&local_11c);
      tmp_i5 = 0x100;
    }
    else {
      __s = *(char **)(param_1 + 4);
      local_128 = strlen(__s);
    }
    if ((param_2 & 0x400) != 0) {
      param_2 = param_2 & 0xfffffbff;
      if (param_2 == 8) {
        if (local_128 == 0) {
          return 1;
        }
        if (!tmp_b6) {
          __s[local_128 - 1] = '\0';
          return 1;
        }
        *(uint8_t *)((int)&local_120 + local_128 + 3) = 0;
        (**(void **)(DC + 0x78))(*(uint32_t *)(param_1 + 4),&local_11c);
        return 1;
      }
      if ((int)param_2 < 0x20) {
        return 1;
      }
      local_120 = *(int *)(param_1 + 0x1c);
      if ((local_120 != 0) && (9 < param_2 - 0x30)) {
        if (local_120 == 2) {
          return 1;
        }
        if ((local_128 != 0) || (param_2 != 0x2d)) {
          return 1;
        }
      }
      if (tmp_i5 + -1 <= (int)local_128) {
        return 1;
      }
      if (!tmp_b6) {
        __s[local_128] = (char)param_2;
        __s[local_128 + 1] = '\0';
        return 1;
      }
      *(char *)((int)&local_11c + local_128) = (char)param_2;
      *(uint8_t *)((int)&local_11c + local_128 + 1) = 0;
      trap_Cvar_Set(*(uint32_t *)(param_1 + 4),&local_11c);
      return 1;
    }
    if ((param_2 != 0xa9) && (param_2 != 0xd)) {
      return 1;
    }
    if (*(void **)(param_1 + 0x48) != (void *)0x0) {
      (**(void **)(param_1 + 0x48))(param_1);
    }
    bg_focusButton = 0;
  }
  return 0;
}

uint32_t BG_PanelButtonsKeyEvent(uint32_t param_1,int param_2,int *param_3)

{
  int tmp_i1;
  int tmp_i2;

  if (bg_focusButton == 0) {
    if (param_2 == 0) {
      for (; tmp_i1 = *param_3, tmp_i1 != 0; param_3 = param_3 + 1) {
        if (*(void **)(tmp_i1 + 0x40) != (void *)0x0) {
          if ((((*(float *)(tmp_i1 + 8) < (float)*(int *)(DC + 0x124)) &&
               ((float)*(int *)(DC + 0x124) < *(float *)(tmp_i1 + 8) + *(float *)(tmp_i1 + 0x10))) &&
              (*(float *)(tmp_i1 + 0xc) < (float)*(int *)(DC + 0x128))) &&
             (((float)*(int *)(DC + 0x128) < *(float *)(tmp_i1 + 0xc) + *(float *)(tmp_i1 + 0x14) &&
              (tmp_i1 = (**(void **)(tmp_i1 + 0x40))(tmp_i1,param_1), tmp_i1 != 0)))) {
            return 1;
          }
        }
      }
    }
    else {
      tmp_i1 = *param_3;
      while (tmp_i1 != 0) {
        if (*(void **)(tmp_i1 + 0x3c) != (void *)0x0) {
          if (((*(float *)(tmp_i1 + 8) < (float)*(int *)(DC + 0x124)) &&
              ((float)*(int *)(DC + 0x124) < *(float *)(tmp_i1 + 8) + *(float *)(tmp_i1 + 0x10))) &&
             ((*(float *)(tmp_i1 + 0xc) < (float)*(int *)(DC + 0x128) &&
              (((float)*(int *)(DC + 0x128) < *(float *)(tmp_i1 + 0xc) + *(float *)(tmp_i1 + 0x14) &&
               (tmp_i1 = (**(void **)(tmp_i1 + 0x3c))(tmp_i1,param_1), tmp_i1 != 0)))))) {
            return 1;
          }
        }
        param_3 = param_3 + 1;
        tmp_i1 = *param_3;
      }
    }
  }
  else {
    tmp_i1 = *param_3;
    tmp_i2 = bg_focusButton;
    while (tmp_i1 != 0) {
      if (tmp_i1 == tmp_i2) {
        tmp_i2 = tmp_i1;
        if ((param_2 != 0) && (*(void **)(tmp_i1 + 0x3c) != (void *)0x0)) {
          tmp_i2 = (**(void **)(tmp_i1 + 0x3c))(tmp_i1,param_1);
          if (tmp_i2 != 0) {
            return 1;
          }
          tmp_i2 = 0;
          if (bg_focusButton != 0) {
            return 0;
          }
        }
        if ((param_2 == 0) && (*(void **)(tmp_i1 + 0x40) != (void *)0x0)) {
          tmp_i1 = (**(void **)(tmp_i1 + 0x40))(tmp_i1,param_1);
          if (tmp_i1 != 0) {
            return 1;
          }
          tmp_i2 = 0;
          if (bg_focusButton != 0) {
            return 0;
          }
        }
      }
      param_3 = param_3 + 1;
      tmp_i1 = *param_3;
    }
  }
  return 0;
}

void BG_PanelButtonsSetup(uint32_t *param_1)

{
  int *tmp_pi1;
  int tmp_i2;

  tmp_pi1 = (int *)*param_1;
  while (tmp_pi1 != (int *)0x0) {
    if (*tmp_pi1 != 0) {
      tmp_i2 = trap_R_RegisterShaderNoMip(*tmp_pi1);
      tmp_pi1[0x13] = tmp_i2;
    }
    param_1 = param_1 + 1;
    tmp_pi1 = (int *)*param_1;
  }
  return;
}

uint64_t BG_PanelButtonsGetHighlightButton(int *param_1)

{
  int tmp_i1;
  int tmp_i2;
  int local_c;

  tmp_i2 = *param_1;
  if (tmp_i2 == 0) {
    tmp_i2 = 0;
  }
  else {
    do {
      if (*(int *)(tmp_i2 + 0x3c) != 0) {
        tmp_i1 = *(int *)(DC + 0x128);
        if ((((*(float *)(tmp_i2 + 8) < (float)*(int *)(DC + 0x124)) &&
             (local_c = tmp_i1,
             (float)*(int *)(DC + 0x124) < *(float *)(tmp_i2 + 8) + *(float *)(tmp_i2 + 0x10))) &&
            (*(float *)(tmp_i2 + 0xc) < (float)tmp_i1)) &&
           ((float)tmp_i1 < *(float *)(tmp_i2 + 0xc) + *(float *)(tmp_i2 + 0x14))) break;
      }
      param_1 = param_1 + 1;
      tmp_i2 = *param_1;
    } while (tmp_i2 != 0);
  }
  return CONCAT44(local_c,tmp_i2);
}

void BG_PanelButtonsRender(int *param_1)

{
  int tmp_i1;

  tmp_i1 = *param_1;
  while (tmp_i1 != 0) {
    if (*(void **)(tmp_i1 + 0x44) != (void *)0x0) {
      (**(void **)(tmp_i1 + 0x44))(tmp_i1);
    }
    param_1 = param_1 + 1;
    tmp_i1 = *param_1;
  }
  return;
}

void BG_PanelButtonsRender_TextExt(int param_1,uint32_t param_2)

{
  float tmp_f1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;

  tmp_pu3 = *(uint32_t **)(param_1 + 0x38);
  tmp_f1 = *(float *)(param_1 + 8);
  if (tmp_pu3 != (uint32_t *)0x0) {
    if (tmp_pu3[7] == 1) {
      tmp_i4 = (**(void **)(DC + 0x1c))(param_2,*tmp_pu3,0,tmp_pu3[8]);
      tmp_f1 = tmp_f1 + (*(float *)(param_1 + 0x10) - (float)tmp_i4) * 0.5;
    }
    else if (tmp_pu3[7] == 2) {
      tmp_f2 = *(float *)(param_1 + 0x10);
      tmp_i4 = (**(void **)(DC + 0x1c))(param_2,*tmp_pu3,0,tmp_pu3[8]);
      tmp_f1 = tmp_f1 + (tmp_f2 - (float)tmp_i4);
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      local_2c = 0x3f000000;
      local_28 = 0x3f000000;
      local_24 = 0x3f000000;
      local_20 = 0x3f800000;
      local_1c = 0;
      local_18 = 0;
      local_14 = 0;
      local_10 = 0x3f4ccccd;
      (**(void **)(DC + 0x3c))
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_1c);
      (**(void **)(DC + 0x40))
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),0x3f800000,
                 &local_2c);
    }
    tmp_pu3 = *(uint32_t **)(param_1 + 0x38);
    (**(void **)(DC + 0x14))
              (tmp_f1,(float)*(int *)(param_1 + 0x18) + *(float *)(param_1 + 0xc),*tmp_pu3,tmp_pu3[1],
               tmp_pu3 + 2,param_2,0,0,tmp_pu3[6],tmp_pu3[8]);
  }
  return;
}

void BG_PanelButtonsRender_Text(int param_1)

{
  float tmp_f1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  uint32_t tmp_u4;
  int tmp_i5;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;

  tmp_pu3 = *(uint32_t **)(param_1 + 0x38);
  tmp_u4 = *(uint32_t *)(param_1 + 4);
  tmp_f1 = *(float *)(param_1 + 8);
  if (tmp_pu3 != (uint32_t *)0x0) {
    if (tmp_pu3[7] == 1) {
      tmp_i5 = (**(void **)(DC + 0x1c))(tmp_u4,*tmp_pu3,0,tmp_pu3[8]);
      tmp_f1 = tmp_f1 + (*(float *)(param_1 + 0x10) - (float)tmp_i5) * 0.5;
    }
    else if (tmp_pu3[7] == 2) {
      tmp_f2 = *(float *)(param_1 + 0x10);
      tmp_i5 = (**(void **)(DC + 0x1c))(tmp_u4,*tmp_pu3,0,tmp_pu3[8]);
      tmp_f1 = tmp_f1 + (tmp_f2 - (float)tmp_i5);
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      local_2c = 0x3f000000;
      local_28 = 0x3f000000;
      local_24 = 0x3f000000;
      local_20 = 0x3f800000;
      local_1c = 0;
      local_18 = 0;
      local_14 = 0;
      local_10 = 0x3f4ccccd;
      (**(void **)(DC + 0x3c))
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_1c);
      (**(void **)(DC + 0x40))
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),0x3f800000,
                 &local_2c);
    }
    tmp_pu3 = *(uint32_t **)(param_1 + 0x38);
    (**(void **)(DC + 0x14))
              (tmp_f1,(float)*(int *)(param_1 + 0x18) + *(float *)(param_1 + 0xc),*tmp_pu3,tmp_pu3[1],
               tmp_pu3 + 2,tmp_u4,0,0,tmp_pu3[6],tmp_pu3[8]);
  }
  return;
}

void BG_PanelButtonsRender_Img(int param_1)

{
  float local_1c;
  float local_18;
  float local_14;
  float local_10;

  local_1c = 1.0;
  local_18 = 1.0;
  local_14 = 1.0;
  local_10 = 1.0;
  if (*(int *)(param_1 + 0x18) != 0) {
    local_1c = (float)*(int *)(param_1 + 0x1c) / 255.0;
    local_18 = (float)*(int *)(param_1 + 0x20) / 255.0;
    local_14 = (float)*(int *)(param_1 + 0x24) / 255.0;
    local_10 = (float)*(int *)(param_1 + 0x28) / 255.0;
    trap_R_SetColor(&local_1c);
  }
  if (*(int *)(param_1 + 0x2c) == 0) {
    (**(void **)(DC + 8))
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),
               *(uint32_t *)(param_1 + 0x4c));
  }
  else {
    (**(void **)(DC + 0x40))
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),0x3f800000,&local_1c)
    ;
  }
  if (*(int *)(param_1 + 0x18) != 0) {
    trap_R_SetColor(0);
  }
  return;
}

uint32_t BG_PanelButtons_GetFocusButton(void)

{
  return bg_focusButton;
}

void BG_PanelButtons_SetFocusButton(uint32_t param_1)

{
  bg_focusButton = param_1;
  return;
}

void BG_FitTextToWidth_Ext
               (char *param_1,uint32_t param_2,float param_3,uint param_4,uint32_t param_5)

{
  char *tmp_pc1;
  char tmp_c2;
  char *tmp_pc3;
  int tmp_i4;
  uint tmp_u5;
  char *tmp_pc6;
  char *tmp_pc7;
  char *tmp_pc8;
  byte tmp_b9;
  char local_41c [1036];

  tmp_b9 = 0;
  Q_strncpyz(local_41c,param_1,0x400);
  tmp_pc8 = param_1;
  if (7 < param_4) {
    tmp_u5 = param_4;
    if (((uint)param_1 & 1) != 0) {
      *param_1 = '\0';
      tmp_pc8 = param_1 + 1;
      tmp_u5 = param_4 - 1;
    }
    if (((uint)tmp_pc8 & 2) != 0) {
      tmp_pc8[0] = '\0';
      tmp_pc8[1] = '\0';
      tmp_u5 = tmp_u5 - 2;
      tmp_pc8 = tmp_pc8 + 2;
    }
    if (((uint)tmp_pc8 & 4) != 0) {
      tmp_pc8[0] = '\0';
      tmp_pc8[1] = '\0';
      tmp_pc8[2] = '\0';
      tmp_pc8[3] = '\0';
      tmp_u5 = tmp_u5 - 4;
      tmp_pc8 = tmp_pc8 + 4;
    }
    param_4 = tmp_u5 & 3;
    for (tmp_u5 = tmp_u5 >> 2; tmp_u5 != 0; tmp_u5 = tmp_u5 - 1) {
      tmp_pc8[0] = '\0';
      tmp_pc8[1] = '\0';
      tmp_pc8[2] = '\0';
      tmp_pc8[3] = '\0';
      tmp_pc8 = tmp_pc8 + (uint)tmp_b9 * -8 + 4;
    }
  }
  if ((param_4 & 4) != 0) {
    tmp_pc8[0] = '\0';
    tmp_pc8[1] = '\0';
    tmp_pc8[2] = '\0';
    tmp_pc8[3] = '\0';
    tmp_pc8 = tmp_pc8 + 4;
  }
  if ((param_4 & 2) != 0) {
    tmp_pc8[0] = '\0';
    tmp_pc8[1] = '\0';
    tmp_pc8 = tmp_pc8 + 2;
  }
  if ((param_4 & 1) != 0) {
    *tmp_pc8 = '\0';
  }
  tmp_pc6 = (char *)0x0;
  tmp_pc8 = local_41c;
  tmp_pc3 = param_1;
  while (local_41c[0] != '\0') {
    tmp_pc8 = tmp_pc8 + 1;
    if (local_41c[0] == ' ') {
      tmp_pc6 = tmp_pc3;
    }
    tmp_c2 = *tmp_pc8;
    *tmp_pc3 = local_41c[0];
    tmp_pc1 = tmp_pc3 + 1;
    tmp_pc7 = tmp_pc1;
    if (tmp_c2 == '\n') {
      param_1 = tmp_pc3 + 2;
    }
    else {
      tmp_i4 = (**(void **)(DC + 0x1c))(param_1,param_2,0,param_5);
      if (param_3 < (float)tmp_i4) {
        if (tmp_pc6 == (char *)0x0) {
          tmp_c2 = *tmp_pc3;
          *tmp_pc3 = '\n';
          tmp_pc3[1] = tmp_c2;
          tmp_pc7 = tmp_pc3 + 2;
          param_1 = tmp_pc1;
        }
        else {
          param_1 = tmp_pc6 + 1;
          *tmp_pc6 = '\n';
          tmp_pc6 = (char *)0x0;
        }
      }
    }
    tmp_pc3 = tmp_pc7;
    local_41c[0] = *tmp_pc8;
  }
  if (tmp_pc3 != local_41c) {
    tmp_pc8 = tmp_pc3;
    if (tmp_pc3[-1] != '\n') {
      tmp_pc8 = tmp_pc3 + 1;
      *tmp_pc3 = '\n';
    }
    *tmp_pc8 = '\0';
    return;
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

void dllEntry(uint32_t param_1)

{
  syscall = param_1;
  return;
}

uint32_t PASSFLOAT(uint32_t param_1)

{
  return param_1;
}

void trap_Print(uint32_t param_1)

{
  (*syscall)(1,param_1,0xfffffac7);
  return;
}

void trap_Error(uint32_t param_1)

{
  (*syscall)(0,param_1,0xfffffac7);
  return;
}

void trap_Milliseconds(void)

{
  (*syscall)(2,0xfffffac7);
  return;
}

void trap_Cvar_Register(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  (*syscall)(0x41,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_Cvar_Update(uint32_t param_1)

{
  (*syscall)(0x42,param_1,0xfffffac7);
  return;
}

void trap_Cvar_Set(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(3,param_1,param_2,0xfffffac7);
  return;
}

long double trap_Cvar_VariableValue(uint32_t param_1)

{
  float tmp_f1;

  tmp_f1 = (float)(*syscall)(4,param_1,0xfffffac7);
  return (long double)tmp_f1;
}

void trap_Cvar_VariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(5,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Cvar_LatchedVariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(6,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Cvar_SetValue(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(7,param_1,param_2,0xfffffac7);
  return;
}

void trap_Cvar_Reset(uint32_t param_1)

{
  (*syscall)(8,param_1,0xfffffac7);
  return;
}

void trap_Cvar_Create(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(9,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Cvar_InfoStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(10,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Argc(void)

{
  (*syscall)(0xb,0xfffffac7);
  return;
}

void trap_Argv(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0xc,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Cmd_ExecuteText(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0xd,param_1,param_2,0xfffffac7);
  return;
}

void trap_AddCommand(uint32_t param_1)

{
  (*syscall)(0xe,param_1,0xfffffac7);
  return;
}

void trap_FS_FOpenFile(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0xf,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_FS_Read(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x10,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_FS_Write(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x11,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_FS_FCloseFile(uint32_t param_1)

{
  (*syscall)(0x12,param_1,0xfffffac7);
  return;
}

void trap_FS_GetFileList(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        )

{
  (*syscall)(0x13,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_FS_Delete(uint32_t param_1)

{
  (*syscall)(0x14,param_1,0xfffffac7);
  return;
}

void trap_R_RegisterModel(uint32_t param_1)

{
  (*syscall)(0x16,param_1,0xfffffac7);
  return;
}

void trap_R_RegisterSkin(uint32_t param_1)

{
  (*syscall)(0x17,param_1,0xfffffac7);
  return;
}

void trap_R_RegisterFont(uint32_t param_1,uint32_t param_2,int param_3)

{
  uint32_t tmp_u1;

  (*syscall)(0x46,param_1,param_2,param_3,0xfffffac7);
  if (*(int *)(param_3 + 0x4fdc) == 0) {
    tmp_u1 = (*syscall)(0x18,param_3 + 0x4fe0,0xfffffac7);
    *(uint32_t *)(param_3 + 0x4fdc) = tmp_u1;
  }
  return;
}

void trap_R_RegisterShaderNoMip(uint32_t param_1)

{
  (*syscall)(0x18,param_1,0xfffffac7);
  return;
}

void trap_R_ClearScene(void)

{
  (*syscall)(0x19,0xfffffac7);
  return;
}

void trap_R_AddRefEntityToScene(uint32_t param_1)

{
  (*syscall)(0x1a,param_1,0xfffffac7);
  return;
}

void trap_R_AddPolyToScene(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x1b,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_R_AddLightToScene
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8)

{
  (*syscall)(0x1d,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xfffffac7);
  return;
}

void trap_R_AddCoronaToScene
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x1e,param_1,param_2,param_3,param_4,param_5,param_6,param_7,0xfffffac7);
  return;
}

void trap_R_RenderScene(uint32_t param_1)

{
  (*syscall)(0x1f,param_1,0xfffffac7);
  return;
}

void trap_R_SetColor(uint32_t param_1)

{
  (*syscall)(0x20,param_1,0xfffffac7);
  return;
}

void trap_R_Add2dPolys(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x21,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_R_DrawStretchPic
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8,
               uint32_t param_9)

{
  (*syscall)(0x22,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xfffffac7
            );
  return;
}

void trap_R_DrawRotatedPic
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8,
               uint32_t param_9,uint32_t param_10)

{
  (*syscall)(0x23,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
             0xfffffac7);
  return;
}

void trap_R_ModelBounds(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x47,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_UpdateScreen(void)

{
  (*syscall)(0x24,0xfffffac7);
  return;
}

void trap_CM_LerpTag(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x25,param_1,param_2,param_3,0,0xfffffac7);
  return;
}

void trap_S_StartLocalSound(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x28,param_1,param_2,0x7f,0xfffffac7);
  return;
}

void trap_S_RegisterSound(uint32_t param_1)

{
  (*syscall)(0x27,param_1,0,0xfffffac7);
  return;
}

void trap_S_FadeBackgroundTrack(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x29,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_S_FadeAllSound(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x2a,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Key_KeynumToStringBuf(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x2b,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Key_GetBindingBuf(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x2c,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Key_KeysForBinding(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x2e,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Key_SetBinding(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x2d,param_1,param_2,0xfffffac7);
  return;
}

void trap_Key_IsDown(uint32_t param_1)

{
  (*syscall)(0x2f,param_1,0xfffffac7);
  return;
}

void trap_Key_GetOverstrikeMode(void)

{
  (*syscall)(0x30,0xfffffac7);
  return;
}

void trap_Key_SetOverstrikeMode(uint32_t param_1)

{
  (*syscall)(0x31,param_1,0xfffffac7);
  return;
}

void trap_Key_ClearStates(void)

{
  (*syscall)(0x32,0xfffffac7);
  return;
}

void trap_Key_GetCatcher(void)

{
  (*syscall)(0x33,0xfffffac7);
  return;
}

void trap_Key_SetCatcher(uint32_t param_1)

{
  (*syscall)(0x34,param_1,0xfffffac7);
  return;
}

void trap_GetClipboardData(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x35,param_1,param_2,0xfffffac7);
  return;
}

void trap_GetClientState(uint32_t param_1)

{
  (*syscall)(0x37,param_1,0xfffffac7);
  return;
}

void trap_GetGlconfig(uint32_t param_1)

{
  (*syscall)(0x36,param_1,0xfffffac7);
  return;
}

void trap_GetConfigString(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x38,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_GetLocalServerCount(void)

{
  (*syscall)(0x39,0xfffffac7);
  return;
}

void trap_LAN_GetLocalServerAddressString(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x3a,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_GetGlobalServerCount(void)

{
  (*syscall)(0x3b,0xfffffac7);
  return;
}

void trap_LAN_GetGlobalServerAddressString(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x3c,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_GetPingQueueCount(void)

{
  (*syscall)(0x3d,0xfffffac7);
  return;
}

void trap_LAN_ClearPing(uint32_t param_1)

{
  (*syscall)(0x3e,param_1,0xfffffac7);
  return;
}

void trap_LAN_GetPing(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  (*syscall)(0x3f,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_LAN_GetPingInfo(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x40,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_UpdateVisiblePings(uint32_t param_1)

{
  (*syscall)(0x56,param_1,0xfffffac7);
  return;
}

void trap_LAN_GetServerCount(uint32_t param_1)

{
  (*syscall)(0x52,param_1,0xfffffac7);
  return;
}

void trap_LAN_CompareServers
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5)

{
  (*syscall)(0x66,param_1,param_2,param_3,param_4,param_5,0xfffffac7);
  return;
}

void trap_LAN_GetServerAddressString
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  (*syscall)(0x53,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_LAN_GetServerInfo
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  (*syscall)(0x54,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_LAN_AddServer(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x5a,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_RemoveServer(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x5b,param_1,param_2,0xfffffac7);
  return;
}

void trap_LAN_GetServerPing(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(100,param_1,param_2,0xfffffac7);
  return;
}

void trap_LAN_ServerIsVisible(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x65,param_1,param_2,0xfffffac7);
  return;
}

void trap_LAN_ServerStatus(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(99,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_ServerIsInFavoriteList(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x67,param_1,param_2,0xfffffac7);
  return;
}

void trap_LAN_SaveCachedServers(void)

{
  (*syscall)(0x59,0xfffffac7);
  return;
}

void trap_LAN_LoadCachedServers(void)

{
  (*syscall)(0x58,0xfffffac7);
  return;
}

void trap_LAN_MarkServerVisible(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x55,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_SetPbClStatus(uint32_t param_1)

{
  (*syscall)(0x69,param_1,0xfffffac7);
  return;
}

void trap_SetPbSvStatus(uint32_t param_1)

{
  (*syscall)(0x6e,param_1,0xfffffac7);
  return;
}

void trap_LAN_ResetPings(uint32_t param_1)

{
  (*syscall)(0x57,param_1,0xfffffac7);
  return;
}

void trap_MemoryRemaining(void)

{
  (*syscall)(0x43,0xfffffac7);
  return;
}

void trap_GetCDKey(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x44,param_1,param_2,0xfffffac7);
  return;
}

void trap_SetCDKey(uint32_t param_1)

{
  (*syscall)(0x45,param_1,0xfffffac7);
  return;
}

void trap_PC_AddGlobalDefine(uint32_t param_1)

{
  (*syscall)(0x48,param_1,0xfffffac7);
  return;
}

void trap_PC_RemoveAllGlobalDefines(void)

{
  (*syscall)(0x49,0xfffffac7);
  return;
}

void trap_PC_LoadSource(uint32_t param_1)

{
  (*syscall)(0x4a,param_1,0xfffffac7);
  return;
}

void trap_PC_FreeSource(uint32_t param_1)

{
  (*syscall)(0x4b,param_1,0xfffffac7);
  return;
}

void trap_PC_ReadToken(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x4c,param_1,param_2,0xfffffac7);
  return;
}

void trap_PC_SourceFileAndLine(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x4d,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_PC_UnReadToken(uint32_t param_1)

{
  (*syscall)(0x4e,param_1,0xfffffac7);
  return;
}

void trap_S_StopBackgroundTrack(void)

{
  (*syscall)(0x4f,0xfffffac7);
  return;
}

void trap_S_StartBackgroundTrack(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x50,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_RealTime(uint32_t param_1)

{
  (*syscall)(0x51,param_1,0xfffffac7);
  return;
}

void trap_CIN_PlayCinematic
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6)

{
  (*syscall)(0x5c,param_1,param_2,param_3,param_4,param_5,param_6,0xfffffac7);
  return;
}

void trap_CIN_StopCinematic(uint32_t param_1)

{
  (*syscall)(0x5d,param_1,0xfffffac7);
  return;
}

void trap_CIN_RunCinematic(uint32_t param_1)

{
  (*syscall)(0x5e,param_1,0xfffffac7);
  return;
}

void trap_CIN_DrawCinematic(uint32_t param_1)

{
  (*syscall)(0x5f,param_1,0xfffffac7);
  return;
}

void trap_CIN_SetExtents(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        ,uint32_t param_5)

{
  (*syscall)(0x60,param_1,param_2,param_3,param_4,param_5,0xfffffac7);
  return;
}

void trap_R_RemapShader(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x61,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_VerifyCDKey(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x62,param_1,param_2,0xfffffac7);
  return;
}

void trap_GetLimboString(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x68,param_1,param_2,0xfffffac7);
  return;
}

void trap_CheckAutoUpdate(void)

{
  (*syscall)(0x6a,0xfffffac7);
  return;
}

void trap_GetAutoUpdate(void)

{
  (*syscall)(0x6b,0xfffffac7);
  return;
}

void trap_openURL(uint32_t param_1)

{
  (*syscall)(0x6d,param_1,0xfffffac7);
  return;
}

void trap_GetHunkData(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0xd1,param_1,param_2,0xfffffac7);
  return;
}

void _fini(void)

{
  return;
}

}

void Menu_PostParse(uint32_t *param_1) {
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

void Menu_RunCloseScript_part_10(int param_1) {
  if (*(int *)(param_1 + 0xdc) != 0) {
    Item_RunScript_constprop_37();
  }
  return;
}

void Menu_ScrollFeeder(int param_1,int param_2,int param_3) {
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

void Menu_SetFeederSelection(uint32_t *param_1,int param_2,int param_3,int param_4) {
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
      if ((g_dat_003f16c8 & 6) == 6) {
        tmp_i6 = 0;
      }
      else {
        tmp_pu4 = &g_dat_003f23e0;
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
      tmp_pu5 = &g_dat_003f16a0;
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

uint32_t Menu_SetNextCursorItem(int param_1) {
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
LAB_0004cb06:
        if (((tmp_u11 & 0xc) != 0) && (tmp_i12 = Item_EnableShowViaCvar(tmp_i5,4), tmp_i12 == 0))
        goto LAB_0004cd01;
        if (((*(byte *)(tmp_i5 + 0x260) & 3) == 0) ||
           (tmp_i12 = Item_SettingShow_constprop_35(), tmp_i12 != 0)) {
          if ((*(int *)(tmp_i5 + 0x264) != 0) &&
             (tmp_i12 = Item_SettingShow_constprop_36(), tmp_i12 == 0)) goto LAB_0004cd01;
          tmp_i12 = Menu_ClearFocus(*(uint32_t *)(tmp_i5 + 0xec));
          tmp_i13 = DC;
          if (*(int *)(tmp_i5 + 200) == 0) {
            tmp_f7 = (float)tmp_i4;
            tmp_f1 = *(float *)(tmp_i5 + 0xb8);
            tmp_f2 = *(float *)(&g_dat_0002003c + DC);
            if (tmp_f2 <= 1.3333334) {
              if (tmp_f1 < tmp_f7) {
LAB_0004cc8f:
                if (tmp_f7 < tmp_f1 + *(float *)(tmp_i5 + 0xc0)) {
LAB_0004cca5:
                  tmp_f1 = *(float *)(tmp_i5 + 0xbc) - *(float *)(tmp_i5 + 0xc4);
                  if ((tmp_f1 < (float)tmp_i3) && ((float)tmp_i3 < tmp_f1 + *(float *)(tmp_i5 + 0xc4))) {
                    tmp_i12 = *(int *)(tmp_i5 + 0x124);
                    *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) | 2;
                    if (tmp_i12 == 0) {
                      tmp_i12 = *(int *)(tmp_i9 + 0x1e320);
                    }
                    goto LAB_0004cd97;
                  }
                }
              }
            }
            else {
              tmp_f8 = tmp_f2 * 0.75;
              tmp_f7 = tmp_f7 * tmp_f8;
              if (tmp_f8 * tmp_f1 < tmp_f7) {
                if (tmp_f2 <= 1.3333334) goto LAB_0004cc8f;
                if (tmp_f7 < (tmp_f1 + *(float *)(tmp_i5 + 0xc0)) * tmp_f8) goto LAB_0004cca5;
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
LAB_0004cd97:
            (**(void **)(tmp_i13 + 0x88))(tmp_i12,6);
          }
          if (*(int *)(tmp_i10 + 0xc0) < 1) goto LAB_0004cc3a;
          tmp_i12 = 0;
          tmp_i13 = *(int *)(tmp_i10 + 0x514);
          goto joined_r0x0004cc1b;
        }
        tmp_i10 = *(int *)(param_1 + 200);
        tmp_i12 = *(int *)(param_1 + 0xc0);
      }
      else {
        tmp_i12 = Item_EnableShowViaCvar(tmp_i5,1);
        if (tmp_i12 != 0) {
          tmp_u11 = *(uint *)(tmp_i5 + 0x120);
          goto LAB_0004cb06;
        }
LAB_0004cd01:
        tmp_i10 = *(int *)(param_1 + 200);
        tmp_i12 = *(int *)(param_1 + 0xc0);
      }
      if (tmp_i12 <= tmp_i10) goto LAB_0004cd20;
    }
  }
LAB_0004cd20:
  *(int *)(param_1 + 200) = tmp_i13;
  return 0;
joined_r0x0004cc1b:
  if (tmp_i5 == tmp_i13) {
    *(int *)(tmp_i10 + 200) = tmp_i12;
LAB_0004cc3a:
    pfVar6 = *(float **)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
    Menu_HandleMouseMove(param_1,*pfVar6 + 1.0,pfVar6[1] + 1.0);
    return *(uint32_t *)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
  }
  tmp_i12 = tmp_i12 + 1;
  if (tmp_i12 == *(int *)(tmp_i10 + 0xc0)) goto LAB_0004cc3a;
  tmp_i13 = *(int *)(tmp_i10 + 0x514 + tmp_i12 * 4);
  goto joined_r0x0004cc1b;
}

uint32_t Menu_SetPrevCursorItem(int param_1) {
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
LAB_0004c670:
  do {
    if (tmp_i10 < 0) {
LAB_0004c8e0:
      *(int *)(param_1 + 200) = tmp_i13;
      return 0;
    }
    tmp_i10 = tmp_i10 + -1;
    *(int *)(param_1 + 200) = tmp_i10;
    if (tmp_i10 == -1) {
      if (tmp_b8) goto LAB_0004c8e0;
      tmp_i10 = *(int *)(param_1 + 0xc0) + -1;
      *(int *)(param_1 + 200) = tmp_i10;
      if (tmp_i10 < 0) goto LAB_0004c8e0;
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
LAB_0004c6d0:
    if (((tmp_u11 & 0xc) == 0) || (tmp_i12 = Item_EnableShowViaCvar(tmp_i3,4), tmp_i12 != 0)) {
      if (((*(byte *)(tmp_i3 + 0x260) & 3) != 0) &&
         (tmp_i12 = Item_SettingShow_constprop_35(), tmp_i12 == 0)) {
        tmp_i10 = *(int *)(param_1 + 200);
        goto LAB_0004c670;
      }
      if ((*(int *)(tmp_i3 + 0x264) == 0) || (tmp_i12 = Item_SettingShow_constprop_36(), tmp_i12 != 0))
      {
        tmp_i12 = Menu_ClearFocus(*(uint32_t *)(tmp_i3 + 0xec));
        tmp_i13 = DC;
        if (*(int *)(tmp_i3 + 200) == 0) {
          tmp_f6 = (float)tmp_i4;
          tmp_f1 = *(float *)(tmp_i3 + 0xb8);
          tmp_f2 = *(float *)(&g_dat_0002003c + DC);
          if (tmp_f2 <= 1.3333334) {
            if (tmp_f1 < tmp_f6) {
LAB_0004c85f:
              if (tmp_f6 < tmp_f1 + *(float *)(tmp_i3 + 0xc0)) {
LAB_0004c875:
                tmp_f1 = *(float *)(tmp_i3 + 0xbc) - *(float *)(tmp_i3 + 0xc4);
                if ((tmp_f1 < (float)tmp_i14) && ((float)tmp_i14 < tmp_f1 + *(float *)(tmp_i3 + 0xc4))) {
                  tmp_i14 = *(int *)(tmp_i3 + 0x124);
                  *(uint *)(tmp_i3 + 0x48) = *(uint *)(tmp_i3 + 0x48) | 2;
                  if (tmp_i14 == 0) {
                    tmp_i14 = *(int *)(tmp_i9 + 0x1e320);
                  }
                  goto LAB_0004c977;
                }
              }
            }
          }
          else {
            tmp_f7 = tmp_f2 * 0.75;
            tmp_f6 = tmp_f6 * tmp_f7;
            if (tmp_f7 * tmp_f1 < tmp_f6) {
              if (tmp_f2 <= 1.3333334) goto LAB_0004c85f;
              if (tmp_f6 < (tmp_f1 + *(float *)(tmp_i3 + 0xc0)) * tmp_f7) goto LAB_0004c875;
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
LAB_0004c977:
          (**(void **)(tmp_i13 + 0x88))(tmp_i14,6);
        }
        if (*(int *)(tmp_i10 + 0xc0) < 1) goto LAB_0004c80a;
        tmp_i13 = 0;
        if (tmp_i3 == *(int *)(tmp_i10 + 0x514)) goto LAB_0004c9a0;
        goto LAB_0004c805;
      }
    }
  }
  else {
    tmp_i12 = Item_EnableShowViaCvar(tmp_i3,1);
    if (tmp_i12 != 0) {
      tmp_u11 = *(uint *)(tmp_i3 + 0x120);
      goto LAB_0004c6d0;
    }
  }
  tmp_i10 = *(int *)(param_1 + 200);
  goto LAB_0004c670;
  while (tmp_i3 != *(int *)(tmp_i10 + 0x514 + tmp_i13 * 4)) {
LAB_0004c805:
    tmp_i13 = tmp_i13 + 1;
    if (tmp_i13 == *(int *)(tmp_i10 + 0xc0)) goto LAB_0004c80a;
  }
LAB_0004c9a0:
  *(int *)(tmp_i10 + 200) = tmp_i13;
LAB_0004c80a:
  pfVar5 = *(float **)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
  Menu_HandleMouseMove(param_1,*pfVar5 + 1.0,pfVar5[1] + 1.0);
  return *(uint32_t *)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
}

void Menu_SetupKeywordHash(void) {
  uint32_t *tmp_pu1;
  char *tmp_pc2;
  int tmp_i3;
  uint32_t **tmp_ppu4;
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
    tmp_pu1 = (uint32_t *)*tmp_pu6;
    *tmp_pu6 = tmp_ppu4;
    tmp_ppu4[2] = tmp_pu1;
    tmp_pc2 = tmp_ppu4[3];
    tmp_ppu4 = tmp_ppu4 + 3;
  }
  return;
}

void Menu_ShowItemByName(uint32_t param_1,uint32_t param_2,int param_3) {
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

void Menu_TransitionItemByName
               (uint32_t param_1,uint32_t param_2,float param_3,float param_4,float param_5,
               float param_6,float param_7,float param_8,float param_9,float param_10,
               uint32_t param_11,float param_12) {
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

void Menu_UpdatePosition(float *param_1) {
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

  if (*(float *)(&g_dat_0002003c + DC) <= 1.3333334) {
    local_40 = 0.0;
  }
  else {
    local_40 = (*(float *)(&g_dat_0002003c + DC) * 0.75 * 640.0 - 640.0) * 0.5;
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
      goto LAB_0003eee3;
    }
    tmp_b10 = false;
  }
  tmp_b11 = false;
LAB_0003eee3:
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
LAB_0003ef90:
          *(float *)((int)tmp_f9 + 0x18) = local_40 + local_40 + *(float *)((int)tmp_f9 + 0x18);
        }
        if (!tmp_b12) goto LAB_0003efa2;
LAB_0003efad:
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
        goto LAB_0003ef90;
      }
      *(float *)((int)tmp_f9 + 0x10) = *(float *)((int)tmp_f9 + 0x10) * *(float *)(DC + 0x114);
      *(float *)((int)tmp_f9 + 0x14) = *(float *)((int)tmp_f9 + 0x14) * *(float *)(tmp_i14 + 0x110);
      *(float *)((int)tmp_f9 + 0x18) = *(float *)((int)tmp_f9 + 0x18) * *(float *)(tmp_i14 + 0x114);
      *(float *)((int)tmp_f9 + 0x1c) = *(float *)((int)tmp_f9 + 0x1c) * *(float *)(tmp_i14 + 0x110);
      if ((1.3333334 < *(float *)(&g_dat_0002003c + tmp_i14)) &&
         (tmp_l16 = (long double)(**(void **)(tmp_i14 + 0x74))("r_mode"), tmp_i14 = DC,
         tmp_l16 != (long double)11.0)) {
        *(float *)((int)tmp_f9 + 0x10) =
             (1.3333334 / *(float *)(&g_dat_0002003c + DC)) * *(float *)((int)tmp_f9 + 0x10);
        *(float *)((int)tmp_f9 + 0x18) =
             (1.3333334 / *(float *)(&g_dat_0002003c + tmp_i14)) * *(float *)((int)tmp_f9 + 0x18);
      }
LAB_0003efa2:
      if (tmp_b11) goto LAB_0003efad;
      Item_SetScreenCoords(param_1[tmp_i15 + 0x145],tmp_f1,tmp_f2);
      tmp_i15 = tmp_i15 + 1;
    } while (tmp_i15 < (int)param_1[0x30]);
  }
  return;
}
