/**
 * @file ui_ui_color.c
 * @brief ui_color
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 */

#include "ui_types.h"
#include "ui_globals.h"
#include "ui_imports.h"
#include "ui_ui_color.h"

uint32_t ColorBytes3(float param_1,float param_2,float param_3) {
  uint8_t local_4 [2];
  uint8_t uStack_2;

  _local_4 = CONCAT12((char)(short)ROUND(param_3 * 255.0),
                      CONCAT11((char)(short)ROUND(param_2 * 255.0),
                               (char)(short)ROUND(param_1 * 255.0)));
  return _local_4;
}

uint32_t ColorBytes4(float param_1,float param_2,float param_3,float param_4) {
  uint32_t local_4;

  local_4 = CONCAT13((char)(short)ROUND(param_4 * 255.0),
                     CONCAT12((char)(short)ROUND(param_3 * 255.0),
                              CONCAT11((char)(short)ROUND(param_2 * 255.0),
                                       (char)(short)ROUND(param_1 * 255.0))));
  return local_4;
}

uint32_t Color_Parse(uint32_t param_1,int param_2) {
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

uint32_t ItemParse_addColorRange(int param_1,uint32_t param_2) {
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

uint32_t ItemParse_addColorRangeRel(int param_1,uint32_t param_2) {
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

uint32_t ItemParse_backcolor(int param_1,uint32_t param_2) {
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

uint32_t ItemParse_bordercolor(int param_1,uint32_t param_2) {
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

uint32_t ItemParse_forecolor(int param_1,uint32_t param_2) {
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

bool ItemParse_outlinecolor(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Color_Parse(param_2,param_1 + 0xa4);
  return tmp_i1 != 0;
}

void LerpColor(float *param_1,float *param_2,float *param_3,float param_4) {
  float tmp_f1;

  tmp_f1 = (*param_2 - *param_1) * param_4 + *param_1;
  if (tmp_f1 < 0.0) {
    *param_3 = 0.0;
  }
  else {
    if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    *param_3 = tmp_f1;
  }
  tmp_f1 = (param_2[1] - param_1[1]) * param_4 + param_1[1];
  if (tmp_f1 < 0.0) {
    param_3[1] = 0.0;
  }
  else {
    if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    param_3[1] = tmp_f1;
  }
  tmp_f1 = (param_2[2] - param_1[2]) * param_4 + param_1[2];
  if (tmp_f1 < 0.0) {
    param_3[2] = 0.0;
  }
  else {
    if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    param_3[2] = tmp_f1;
  }
  tmp_f1 = param_1[3] + (param_2[3] - param_1[3]) * param_4;
  if (0.0 <= tmp_f1) {
    if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    param_3[3] = tmp_f1;
    return;
  }
  param_3[3] = 0.0;
  return;
}

uint32_t MenuParse_backcolor(int param_1,uint32_t param_2) {
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

uint32_t MenuParse_bordercolor(int param_1,uint32_t param_2) {
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

uint32_t MenuParse_disablecolor(int param_1,uint32_t param_2) {
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

uint32_t MenuParse_focuscolor(int param_1,uint32_t param_2) {
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

uint32_t MenuParse_forecolor(int param_1,uint32_t param_2) {
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

bool MenuParse_outlinecolor(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Color_Parse(param_2,param_1 + 0xa4);
  return tmp_i1 != 0;
}

void NormalizeColor(float *param_1,float *param_2) {
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;

  tmp_f1 = *param_1;
  tmp_f3 = param_1[1];
  if (param_1[1] <= tmp_f1) {
    tmp_f3 = tmp_f1;
  }
  tmp_f2 = param_1[2];
  if (param_1[2] <= tmp_f3) {
    tmp_f2 = tmp_f3;
  }
  if (tmp_f2 != 0.0) {
    *param_2 = tmp_f1 / tmp_f2;
    param_2[1] = param_1[1] / tmp_f2;
    param_2[2] = param_1[2] / tmp_f2;
    return;
  }
  param_2[2] = 0.0;
  param_2[1] = 0.0;
  *param_2 = 0.0;
  return;
}

uint32_t ParseColorRange(int param_1,uint32_t param_2,int param_3) {
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

  if ((*(int *)(param_1 + 0x128) == 0) || (*(int *)(param_1 + 0x244) == param_3)) {
    *(int *)(param_1 + 0x244) = param_3;
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

void Script_SetColor(int param_1,uint32_t param_2,uint32_t param_3) {
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

void Script_SetItemColor(int param_1,uint32_t param_2,uint32_t param_3) {
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
                if (tmp_i6 != 0) goto LAB_0003fdf1;
              }
            }
            *pfVar7 = local_2c[0];
            pfVar7[1] = local_2c[1];
            pfVar7[2] = local_2c[2];
            pfVar7[3] = local_2c[3];
          }
LAB_0003fdf1:
          tmp_i9 = tmp_i9 + 1;
        } while (tmp_i9 != tmp_i4);
      }
    }
  }
  return;
}

void Script_SetMenuItemColor(uint32_t param_1,uint32_t param_2,uint32_t param_3) {
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
  tmp_pu9 = &g_dat_003f16a0;
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
          if (tmp_i8 != 0) goto LAB_0003fff1;
        }
      }
      *tmp_pu9 = local_2c;
      tmp_pu9[1] = local_28;
      tmp_pu9[2] = local_24;
      tmp_pu9[3] = local_20;
    }
LAB_0003fff1:
    tmp_i6 = tmp_i6 + 1;
    if (tmp_i6 == tmp_i5) {
      return;
    }
  } while( true );
}

void Script_SetTeamColor(int param_1) {
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

void UI_SetColor(uint32_t param_1) {
  trap_R_SetColor(param_1);
  return;
}
