/**
 * @file ui_ui_parse.c
 * @brief ui_parse
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 */

#include "ui_types.h"
#include "ui_globals.h"
#include "ui_imports.h"
#include "ui_ui_parse.h"

void COM_BackupParseSession(uint32_t *param_1) {
  backup_lines = com_lines;
  backup_text = *param_1;
  return;
}

void COM_BeginParseSession(uint32_t param_1) {
  com_lines = 0;
  Com_sprintf(com_parsename,0x400,&g_dat_0005580c,param_1);
  return;
}

uint32_t COM_GetCurrentParseLine(void) {
  return com_lines;
}

void COM_Parse(void) {
  COM_ParseExt_constprop_2();
  return;
}

void COM_ParseError(char *param_1) {
  vsnprintf(string_5132,0x1000,param_1,&stack0x00000008);
  Com_Printf("ERROR: %s, line %d: %s\n",com_parsename,com_lines,string_5132);
  return;
}

uint8_t * COM_ParseExt(int *param_1,int param_2) {
  bool tmp_b1;
  char *tmp_pc2;
  char tmp_c3;
  char *tmp_pc4;
  char *tmp_pc5;
  int tmp_i6;
  bool tmp_b7;

  tmp_pc5 = (char *)*param_1;
  com_token = 0;
  if (tmp_pc5 != (char *)0x0) {
    tmp_b1 = false;
    backup_text = *param_1;
    tmp_c3 = *tmp_pc5;
    backup_lines = com_lines;
LAB_0001dbcc:
    do {
      if (' ' < tmp_c3) {
        if ((tmp_b1) && (param_2 == 0)) {
          *param_1 = (int)tmp_pc5;
          return &com_token;
        }
        if (tmp_c3 == '/') {
          if (tmp_pc5[1] == '/') {
            tmp_c3 = tmp_pc5[2];
            tmp_pc5 = tmp_pc5 + 2;
            if (tmp_c3 == '\n') {
              tmp_c3 = '\n';
            }
            else {
              do {
                if (tmp_c3 == '\0') {
                  tmp_c3 = '\0';
                  break;
                }
                tmp_pc5 = tmp_pc5 + 1;
                tmp_c3 = *tmp_pc5;
              } while (tmp_c3 != '\n');
            }
            goto LAB_0001dbcc;
          }
          if (tmp_pc5[1] == '*') {
            tmp_c3 = tmp_pc5[2];
            tmp_pc4 = tmp_pc5 + 2;
            while (tmp_c3 != '\0') {
              tmp_b7 = tmp_c3 == '*';
              tmp_c3 = tmp_pc4[1];
              if ((tmp_b7) && (tmp_c3 == '/')) {
                tmp_pc5 = tmp_pc4 + 2;
                tmp_c3 = tmp_pc4[2];
                goto LAB_0001dbcc;
              }
              tmp_pc4 = tmp_pc4 + 1;
            }
            tmp_c3 = '\0';
            tmp_pc5 = tmp_pc4;
            goto LAB_0001dbcc;
          }
        }
        else if (tmp_c3 == '\"') {
          tmp_pc4 = tmp_pc5 + 1;
          tmp_c3 = *tmp_pc4;
          tmp_i6 = 0;
          tmp_pc5 = tmp_pc5 + 2;
          if (tmp_c3 == '\\') goto LAB_0001dc5e;
LAB_0001dc34:
          do {
            if ((tmp_c3 == '\0') || (tmp_c3 == '\"')) {
LAB_0001dcc2:
              (&com_token)[tmp_i6] = 0;
              *param_1 = (int)tmp_pc5;
              return &com_token;
            }
            do {
              tmp_pc4 = tmp_pc5;
              if (tmp_i6 < 0x400) {
                (&com_token)[tmp_i6] = tmp_c3;
                tmp_i6 = tmp_i6 + 1;
              }
              tmp_c3 = *tmp_pc4;
              tmp_pc5 = tmp_pc4 + 1;
              if (tmp_c3 != '\\') goto LAB_0001dc34;
LAB_0001dc5e:
            } while (tmp_pc4[1] != '\"');
            if (tmp_i6 < 0x400) {
              (&com_token)[tmp_i6] = 0x22;
              tmp_i6 = tmp_i6 + 1;
            }
            tmp_c3 = tmp_pc4[2];
            tmp_pc2 = tmp_pc4 + 2;
            tmp_pc5 = tmp_pc4 + 3;
            while( true ) {
              if (tmp_c3 == '\0') {
                (&com_token)[tmp_i6] = 0;
                *param_1 = (int)tmp_pc5;
                goto LAB_0001dcc2;
              }
              if ((tmp_c3 == '\\') && (*tmp_pc5 == '\"')) break;
              if (tmp_i6 < 0x400) {
                (&com_token)[tmp_i6] = tmp_c3;
                tmp_i6 = tmp_i6 + 1;
              }
              tmp_c3 = *tmp_pc5;
              tmp_pc2 = tmp_pc5;
              tmp_pc5 = tmp_pc5 + 1;
            }
            if (tmp_i6 < 0x400) {
              (&com_token)[tmp_i6] = 0x22;
              tmp_i6 = tmp_i6 + 1;
            }
            tmp_pc5 = tmp_pc2 + 3;
            tmp_c3 = tmp_pc2[2];
          } while( true );
        }
        tmp_i6 = 0;
        goto LAB_0001dd80;
      }
      if (tmp_c3 == '\0') break;
      if (tmp_c3 == '\n') {
        com_lines = com_lines + 1;
        tmp_b1 = true;
      }
      tmp_c3 = tmp_pc5[1];
      tmp_pc5 = tmp_pc5 + 1;
    } while( true );
  }
  *param_1 = 0;
  return &com_token;
LAB_0001dd80:
  if (tmp_i6 < 0x400) {
    (&com_token)[tmp_i6] = tmp_c3;
    tmp_i6 = tmp_i6 + 1;
  }
  tmp_pc5 = tmp_pc5 + 1;
  tmp_c3 = *tmp_pc5;
  if (tmp_c3 == '\n') {
    com_lines = com_lines + 1;
    goto LAB_0001dda6;
  }
  if (tmp_c3 < '!') {
LAB_0001dda6:
    if (tmp_i6 == 0x400) {
      tmp_i6 = 0;
    }
    (&com_token)[tmp_i6] = 0;
    *param_1 = (int)tmp_pc5;
    return &com_token;
  }
  goto LAB_0001dd80;
}

uint64_t COM_ParseExt_constprop_2(int *param_1) {
  char *tmp_pc1;
  char tmp_c2;
  int tmp_i3;
  char *tmp_pc4;
  char *tmp_pc5;
  bool tmp_b6;
  uint32_t local_14;

  tmp_pc5 = (char *)*param_1;
  com_token = 0;
  if (tmp_pc5 != (char *)0x0) {
    backup_text = *param_1;
    backup_lines = com_lines;
    tmp_c2 = *tmp_pc5;
joined_r0x0001d2c3:
    do {
      if (' ' < tmp_c2) {
        if (tmp_c2 == '/') {
          if (tmp_pc5[1] == '/') {
            tmp_c2 = tmp_pc5[2];
            tmp_pc5 = tmp_pc5 + 2;
            if (tmp_c2 == '\n') {
              tmp_c2 = '\n';
            }
            else {
              do {
                if (tmp_c2 == '\0') {
                  tmp_c2 = '\0';
                  break;
                }
                tmp_pc5 = tmp_pc5 + 1;
                tmp_c2 = *tmp_pc5;
              } while (tmp_c2 != '\n');
            }
            goto joined_r0x0001d2c3;
          }
          if (tmp_pc5[1] == '*') {
            tmp_c2 = tmp_pc5[2];
            tmp_pc4 = tmp_pc5 + 2;
            while (tmp_c2 != '\0') {
              tmp_b6 = tmp_c2 == '*';
              tmp_c2 = tmp_pc4[1];
              if ((tmp_b6) && (tmp_c2 == '/')) {
                tmp_pc5 = tmp_pc4 + 2;
                tmp_c2 = tmp_pc4[2];
                goto joined_r0x0001d2c3;
              }
              tmp_pc4 = tmp_pc4 + 1;
            }
            tmp_c2 = '\0';
            tmp_pc5 = tmp_pc4;
            goto joined_r0x0001d2c3;
          }
          tmp_c2 = '/';
        }
        else if (tmp_c2 == '\"') {
          tmp_pc4 = tmp_pc5 + 1;
          tmp_i3 = 0;
          tmp_c2 = *tmp_pc4;
          tmp_pc5 = tmp_pc5 + 2;
          if (tmp_c2 == '\\') goto LAB_0001d367;
LAB_0001d33d:
          do {
            if ((tmp_c2 == '\0') || (tmp_c2 == '\"')) {
LAB_0001d3bd:
              (&com_token)[tmp_i3] = 0;
              *param_1 = (int)tmp_pc5;
              return CONCAT44(param_1,&com_token);
            }
            do {
              tmp_pc4 = tmp_pc5;
              if (tmp_i3 < 0x400) {
                (&com_token)[tmp_i3] = tmp_c2;
                tmp_i3 = tmp_i3 + 1;
              }
              tmp_c2 = *tmp_pc4;
              tmp_pc5 = tmp_pc4 + 1;
              if (tmp_c2 != '\\') goto LAB_0001d33d;
LAB_0001d367:
            } while (tmp_pc4[1] != '\"');
            if (tmp_i3 < 0x400) {
              (&com_token)[tmp_i3] = 0x22;
              tmp_i3 = tmp_i3 + 1;
            }
            tmp_c2 = tmp_pc4[2];
            tmp_pc1 = tmp_pc4 + 2;
            tmp_pc5 = tmp_pc4 + 3;
            while( true ) {
              if (tmp_c2 == '\0') {
                (&com_token)[tmp_i3] = 0;
                *param_1 = (int)tmp_pc5;
                goto LAB_0001d3bd;
              }
              if ((tmp_c2 == '\\') && (*tmp_pc5 == '\"')) break;
              if (tmp_i3 < 0x400) {
                (&com_token)[tmp_i3] = tmp_c2;
                tmp_i3 = tmp_i3 + 1;
              }
              tmp_c2 = *tmp_pc5;
              tmp_pc1 = tmp_pc5;
              tmp_pc5 = tmp_pc5 + 1;
            }
            if (tmp_i3 < 0x400) {
              (&com_token)[tmp_i3] = 0x22;
              tmp_i3 = tmp_i3 + 1;
            }
            tmp_pc5 = tmp_pc1 + 3;
            tmp_c2 = tmp_pc1[2];
          } while( true );
        }
        tmp_i3 = 0;
        goto LAB_0001d470;
      }
      if (tmp_c2 == '\0') break;
      com_lines = com_lines + (uint)(tmp_c2 == '\n');
      tmp_c2 = tmp_pc5[1];
      tmp_pc5 = tmp_pc5 + 1;
    } while( true );
  }
  *param_1 = 0;
  return CONCAT44(local_14,&com_token);
LAB_0001d470:
  if (tmp_i3 < 0x400) {
    (&com_token)[tmp_i3] = tmp_c2;
    tmp_i3 = tmp_i3 + 1;
  }
  tmp_pc5 = tmp_pc5 + 1;
  tmp_c2 = *tmp_pc5;
  if (tmp_c2 == '\n') {
    com_lines = com_lines + 1;
    goto LAB_0001d496;
  }
  if (tmp_c2 < '!') {
LAB_0001d496:
    if (tmp_i3 == 0x400) {
      tmp_i3 = 0;
    }
    (&com_token)[tmp_i3] = 0;
    *param_1 = (int)tmp_pc5;
    return CONCAT44(local_14,&com_token);
  }
  goto LAB_0001d470;
}

uint64_t COM_ParseExt_nico(uint32_t *param_1,int param_2) {
  bool tmp_b1;
  char tmp_c2;
  int tmp_i3;
  char *tmp_pc4;
  char *tmp_pc5;
  bool tmp_b6;
  int local_14;

  tmp_pc5 = (char *)*param_1;
  com_token = 0;
  if (tmp_pc5 != (char *)0x0) {
    backup_text = *param_1;
    tmp_b1 = false;
    tmp_c2 = *tmp_pc5;
    backup_lines = com_lines;
joined_r0x0001fa66:
    if (' ' < tmp_c2) {
      if ((tmp_b1) && (param_2 == 0)) {
        *param_1 = tmp_pc5;
        goto LAB_0001faf4;
      }
      if (tmp_c2 == '/') {
        if (tmp_pc5[1] == '/') {
          tmp_c2 = tmp_pc5[2];
          tmp_pc5 = tmp_pc5 + 2;
          if (tmp_c2 == '\n') {
            tmp_c2 = '\n';
          }
          else {
            do {
              if (tmp_c2 == '\0') {
                tmp_c2 = '\0';
                break;
              }
              tmp_pc5 = tmp_pc5 + 1;
              tmp_c2 = *tmp_pc5;
            } while (tmp_c2 != '\n');
          }
          goto joined_r0x0001fa66;
        }
        if (tmp_pc5[1] == '*') {
          tmp_c2 = tmp_pc5[2];
          tmp_pc4 = tmp_pc5 + 2;
          while (tmp_c2 != '\0') {
            tmp_b6 = tmp_c2 == '*';
            tmp_c2 = tmp_pc4[1];
            if ((tmp_b6) && (tmp_c2 == '/')) {
              tmp_pc5 = tmp_pc4 + 2;
              tmp_c2 = tmp_pc4[2];
              goto joined_r0x0001fa66;
            }
            tmp_pc4 = tmp_pc4 + 1;
          }
          tmp_c2 = '\0';
          tmp_pc5 = tmp_pc4;
          goto joined_r0x0001fa66;
        }
      }
      tmp_i3 = 0;
      local_14 = com_lines;
      do {
        while( true ) {
          if (tmp_i3 < 0x400) {
            (&com_token)[tmp_i3] = tmp_c2;
            tmp_i3 = tmp_i3 + 1;
          }
          tmp_pc5 = tmp_pc5 + 1;
          tmp_c2 = *tmp_pc5;
          if (tmp_c2 != '\n') break;
          local_14 = local_14 + 1;
        }
      } while (tmp_c2 != '\0');
      if (tmp_i3 == 0x400) {
        tmp_i3 = 0;
      }
      (&com_token)[tmp_i3] = 0;
      *param_1 = tmp_pc5;
      com_lines = local_14;
LAB_0001faf4:
      return CONCAT44(local_14,&com_token);
    }
    if (tmp_c2 != '\0') {
      if (tmp_c2 == '\n') {
        tmp_c2 = tmp_pc5[1];
        com_lines = com_lines + 1;
        tmp_b1 = true;
        tmp_pc5 = tmp_pc5 + 1;
      }
      else {
        tmp_c2 = tmp_pc5[1];
        tmp_pc5 = tmp_pc5 + 1;
      }
      goto joined_r0x0001fa66;
    }
  }
  *param_1 = 0;
  return CONCAT44(local_14,&com_token);
}

void COM_RestoreParseSession(uint32_t *param_1) {
  com_lines = backup_lines;
  *param_1 = backup_text;
  return;
}

uint32_t Float_Parse(uint32_t param_1,float *param_2) {
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

uint32_t Int_Parse(uint32_t param_1,long *param_2) {
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

bool ItemParse_accept(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x108);
  return tmp_i1 != 0;
}

bool ItemParse_action(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x104);
  return tmp_i1 != 0;
}

bool ItemParse_align(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xcc);
  return tmp_i1 != 0;
}

uint32_t ItemParse_asset_model(int param_1,uint32_t param_2) {
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

bool ItemParse_asset_shader(int param_1,uint32_t param_2) {
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

uint32_t ItemParse_autowrapped(int param_1) {
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x80000;
  return 1;
}

bool ItemParse_background(int param_1,uint32_t param_2) {
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

bool ItemParse_bitflag(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x274);
  return tmp_i1 != 0;
}

bool ItemParse_border(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x38);
  return tmp_i1 != 0;
}

bool ItemParse_bordersize(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x44);
  return tmp_i1 != 0;
}

bool ItemParse_cinematic(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x2c);
  return tmp_i1 != 0;
}

uint32_t ItemParse_columns(int param_1,uint32_t param_2) {
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

bool ItemParse_contextMenu(int param_1,uint32_t param_2) {
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

uint32_t ItemParse_cvar(int param_1,uint32_t param_2) {
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

bool ItemParse_cvarFloat(int param_1,uint32_t param_2) {
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

uint32_t ItemParse_cvarFloatList(int param_1,uint32_t param_2) {
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

uint32_t ItemParse_cvarListUndefined(int param_1,uint32_t param_2) {
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

uint32_t ItemParse_cvarStrList(int param_1,uint32_t param_2) {
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

bool ItemParse_cvarTest(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x118);
  return tmp_i1 != 0;
}

uint32_t ItemParse_decoration(int param_1) {
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x10;
  return 1;
}

bool ItemParse_disableCvar(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x11c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x120) = 2;
  }
  return tmp_i1 != 0;
}

bool ItemParse_doubleClick(int param_1,uint32_t param_2) {
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

bool ItemParse_elementheight(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Float_Parse(param_2,tmp_i1 + 0x14);
  return tmp_i1 != 0;
}

bool ItemParse_elementtype(int param_1,uint32_t param_2) {
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

bool ItemParse_elementwidth(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Float_Parse(param_2,tmp_i1 + 0x10);
  return tmp_i1 != 0;
}

bool ItemParse_enableCvar(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x11c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x120) = 1;
  }
  return tmp_i1 != 0;
}

bool ItemParse_execKey(int param_1,uint32_t param_2) {
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

bool ItemParse_feeder(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x248);
  return tmp_i1 != 0;
}

bool ItemParse_focusSound(int param_1,uint32_t param_2) {
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

bool ItemParse_group(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x28);
  return tmp_i1 != 0;
}

bool ItemParse_hideCvar(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x11c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x120) = 8;
  }
  return tmp_i1 != 0;
}

uint32_t ItemParse_horizontalscroll(int param_1) {
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x400;
  return 1;
}

bool ItemParse_leaveFocus(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x110);
  return tmp_i1 != 0;
}

uint32_t ItemParse_maxChars(int param_1,uint32_t param_2) {
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

bool ItemParse_model_angle(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Int_Parse(param_2,tmp_i1);
  return tmp_i1 != 0;
}

uint32_t ItemParse_model_animplay(int param_1,uint32_t param_2) {
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

bool ItemParse_model_fovx(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Float_Parse(param_2,tmp_i1 + 0x10);
  return tmp_i1 != 0;
}

bool ItemParse_model_fovy(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Float_Parse(param_2,tmp_i1 + 0x14);
  return tmp_i1 != 0;
}

bool ItemParse_model_origin(int param_1,uint32_t param_2) {
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

bool ItemParse_model_rotation(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
  }
  tmp_i1 = PC_Int_Parse(param_2,tmp_i1 + 0x18);
  return tmp_i1 != 0;
}

bool ItemParse_mouseEnter(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xfc);
  return tmp_i1 != 0;
}

bool ItemParse_mouseEnterText(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xf4);
  return tmp_i1 != 0;
}

bool ItemParse_mouseExit(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x100);
  return tmp_i1 != 0;
}

bool ItemParse_mouseExitText(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xf8);
  return tmp_i1 != 0;
}

bool ItemParse_name(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x20);
  return tmp_i1 != 0;
}

uint32_t ItemParse_noToggle(int param_1) {
  *(uint *)(param_1 + 0x120) = *(uint *)(param_1 + 0x120) | 0x10;
  return 1;
}

uint32_t ItemParse_notselectable(int param_1) {
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

bool ItemParse_onEnter(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x26c);
  return tmp_i1 != 0;
}

bool ItemParse_onEsc(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x268);
  return tmp_i1 != 0;
}

bool ItemParse_onFocus(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x10c);
  return tmp_i1 != 0;
}

uint32_t ItemParse_origin(int param_1,uint32_t param_2) {
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

bool ItemParse_rect(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x10);
  if (((tmp_i1 != 0) && (tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x14), tmp_i1 != 0)) &&
     (tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x18), tmp_i1 != 0)) {
    tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x1c);
    return tmp_i1 != 0;
  }
  return false;
}

void ItemParse_settingDisabled(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x25c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x260) = 1;
  }
  return;
}

void ItemParse_settingEnabled(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x25c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x260) = 2;
  }
  return;
}

bool ItemParse_showCvar(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0x11c);
  if (tmp_i1 != 0) {
    *(uint32_t *)(param_1 + 0x120) = 4;
  }
  return tmp_i1 != 0;
}

bool ItemParse_special(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x248);
  return tmp_i1 != 0;
}

bool ItemParse_style(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x34);
  return tmp_i1 != 0;
}

bool ItemParse_text(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_String_Parse(param_2,param_1 + 0xe8);
  return tmp_i1 != 0;
}

bool ItemParse_textalign(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xd0);
  return tmp_i1 != 0;
}

bool ItemParse_textalignx(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xd4);
  return tmp_i1 != 0;
}

bool ItemParse_textaligny(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xd8);
  return tmp_i1 != 0;
}

uint32_t ItemParse_textasfloat(int param_1) {
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x20000000;
  return 1;
}

uint32_t ItemParse_textasint(int param_1) {
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x10000000;
  return 1;
}

bool ItemParse_textfile(int param_1,uint32_t param_2) {
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

bool ItemParse_textfont(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xe0);
  return tmp_i1 != 0;
}

bool ItemParse_textscale(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xdc);
  return tmp_i1 != 0;
}

bool ItemParse_textstyle(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xe4);
  return tmp_i1 != 0;
}

bool ItemParse_tooltip(int param_1,uint32_t param_2) {
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

bool ItemParse_tooltipalignx(int param_1,uint32_t param_2) {
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

bool ItemParse_tooltipaligny(int param_1,uint32_t param_2) {
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

uint32_t ItemParse_type(int param_1,uint32_t param_2) {
  int tmp_i1;
  uint32_t tmp_u2;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 200);
  tmp_u2 = 0;
  if ((tmp_i1 != 0) && (tmp_u2 = 1, *(int *)(param_1 + 0x250) == 0)) {
    Item_ValidateTypeData_part_21();
  }
  return tmp_u2;
}

uint32_t ItemParse_visible(int param_1,uint32_t param_2) {
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

void ItemParse_voteFlag(int param_1,uint32_t param_2) {
  PC_Int_Parse(param_2,param_1 + 0x264);
  return;
}

uint32_t ItemParse_wrapped(int param_1) {
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x40000;
  return 1;
}

bool MenuParse_background(int param_1,uint32_t param_2) {
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

bool MenuParse_border(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x38);
  return tmp_i1 != 0;
}

bool MenuParse_borderSize(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0x44);
  return tmp_i1 != 0;
}

bool MenuParse_cinematic(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x2c);
  return tmp_i1 != 0;
}

bool MenuParse_execKey(int param_1,uint32_t param_2) {
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

bool MenuParse_execKeyInt(int param_1,uint32_t param_2) {
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

bool MenuParse_fadeAmount(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xd4);
  return tmp_i1 != 0;
}

bool MenuParse_fadeClamp(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xd0);
  return tmp_i1 != 0;
}

bool MenuParse_fadeCycle(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xcc);
  return tmp_i1 != 0;
}

bool MenuParse_fullscreen(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xbc);
  return tmp_i1 != 0;
}

uint32_t MenuParse_itemDef(int param_1,uint32_t param_2) {
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

bool MenuParse_itemHotkeyMode(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xd14);
  return tmp_i1 != 0;
}

uint32_t MenuParse_modal(int param_1) {
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x4000000;
  return 1;
}

bool MenuParse_name(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x20);
  if (tmp_i1 != 0) {
    Q_stricmp(*(uint32_t *)(param_1 + 0x20),"main");
  }
  return tmp_i1 != 0;
}

bool MenuParse_onClose(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xdc);
  return tmp_i1 != 0;
}

bool MenuParse_onESC(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xe0);
  return tmp_i1 != 0;
}

bool MenuParse_onEnter(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xe4);
  return tmp_i1 != 0;
}

bool MenuParse_onOpen(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xd8);
  return tmp_i1 != 0;
}

bool MenuParse_onTimeout(int param_1,uint32_t param_2) {
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

uint32_t MenuParse_outOfBounds(int param_1) {
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x20000;
  return 1;
}

uint32_t MenuParse_popup(int param_1) {
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x200000;
  return 1;
}

bool MenuParse_rect(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Float_Parse(param_2,param_1);
  if (((tmp_i1 != 0) && (tmp_i1 = PC_Float_Parse(param_2,param_1 + 4), tmp_i1 != 0)) &&
     (tmp_i1 = PC_Float_Parse(param_2,param_1 + 8), tmp_i1 != 0)) {
    tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xc);
    return tmp_i1 != 0;
  }
  return false;
}

bool MenuParse_soundLoop(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x4f0);
  return tmp_i1 != 0;
}

bool MenuParse_style(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0x34);
  return tmp_i1 != 0;
}

uint32_t MenuParse_visible(int param_1,uint32_t param_2) {
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

bool PC_Char_Parse(uint32_t param_1,uint8_t *param_2) {
  int tmp_i1;
  uint8_t local_424 [16];
  uint8_t local_414;

  tmp_i1 = trap_PC_ReadToken(param_1,local_424);
  if (tmp_i1 != 0) {
    *param_2 = local_414;
  }
  return tmp_i1 != 0;
}

uint32_t PC_Color_Parse(uint32_t param_1,int param_2) {
  int tmp_i1;
  int tmp_i2;
  uint32_t local_10;

  tmp_i2 = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_1,&local_10);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_2 + tmp_i2 * 4) = local_10;
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 4);
  return 1;
}

uint32_t PC_Float_Parse(uint32_t param_1,float *param_2) {
  int tmp_i1;
  int local_424 [3];
  float local_418;
  char local_414 [1032];

  tmp_i1 = trap_PC_ReadToken(param_1,local_424);
  if (tmp_i1 != 0) {
    if (local_414[0] == '-') {
      tmp_i1 = trap_PC_ReadToken(param_1,local_424);
      if (tmp_i1 == 0) {
        return 0;
      }
      if (local_424[0] == 3) {
        *param_2 = -local_418;
        return 1;
      }
    }
    else if (local_424[0] == 3) {
      *param_2 = local_418;
      return 1;
    }
    PC_SourceError(param_1,"expected float but found %s\n",local_414);
  }
  return 0;
}

uint32_t PC_Int_Parse(uint32_t param_1,int *param_2) {
  int tmp_i1;
  int local_424 [2];
  int local_41c;
  char local_414 [1032];

  tmp_i1 = trap_PC_ReadToken(param_1,local_424);
  if (tmp_i1 != 0) {
    if (local_414[0] == '-') {
      tmp_i1 = trap_PC_ReadToken(param_1,local_424);
      if (tmp_i1 == 0) {
        return 0;
      }
      if (local_424[0] == 3) {
        *param_2 = -local_41c;
        return 1;
      }
    }
    else if (local_424[0] == 3) {
      *param_2 = local_41c;
      return 1;
    }
    PC_SourceError(param_1,"expected integer but found %s\n",local_414);
  }
  return 0;
}

uint32_t PC_Script_Parse(uint32_t param_1,uint32_t *param_2) {
  int tmp_i1;
  uint32_t tmp_u2;
  uint tmp_u3;
  uint32_t *tmp_pu4;
  uint8_t local_1434 [16];
  uint8_t local_1424;
  char local_1423;
  uint32_t local_101c;
  uint32_t local_1018 [1026];

  tmp_u3 = 0x1000;
  tmp_pu4 = &local_101c;
  if (((uint)&local_101c & 4) != 0) {
    tmp_u3 = 0xffc;
    local_101c = 0;
    tmp_pu4 = local_1018;
  }
  for (tmp_u3 = tmp_u3 >> 2; tmp_u3 != 0; tmp_u3 = tmp_u3 - 1) {
    *tmp_pu4 = 0;
    tmp_pu4 = tmp_pu4 + 1;
  }
  tmp_i1 = trap_PC_ReadToken(param_1,local_1434);
  if (tmp_i1 != 0) {
    tmp_i1 = Q_stricmp(&local_1424,&g_dat_00055ec2);
    if (tmp_i1 == 0) {
      while (tmp_i1 = trap_PC_ReadToken(param_1,local_1434), tmp_i1 != 0) {
        tmp_i1 = Q_stricmp(&local_1424,&g_dat_00055b39);
        if (tmp_i1 == 0) {
          tmp_u2 = String_Alloc(&local_101c);
          *param_2 = tmp_u2;
          return 1;
        }
        if (local_1423 == '\0') {
          Q_strcat(&local_101c,0x1000,&local_1424);
        }
        else {
          tmp_u2 = va(&g_dat_00056ccb,&local_1424);
          Q_strcat(&local_101c,0x1000,tmp_u2);
        }
        Q_strcat(&local_101c,0x1000,&g_dat_0005661b);
      }
    }
  }
  return 0;
}

void PC_SourceError(uint32_t param_1,char *param_2) {
  uint32_t local_90;
  uint8_t local_8c [128];

  vsnprintf(string_7433,0x1000,param_2,&stack0x0000000c);
  local_90 = 0;
  local_8c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_8c,&local_90);
  Com_Printf("^1ERROR: %s, line %d: %s\n",local_8c,local_90,string_7433);
  return;
}

void PC_SourceWarning(uint32_t param_1,char *param_2) {
  uint32_t local_90;
  uint8_t local_8c [128];

  vsnprintf(string_7425,0x1000,param_2,&stack0x0000000c);
  local_90 = 0;
  local_8c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_8c,&local_90);
  Com_Printf("^3WARNING: %s, line %d: %s\n",local_8c,local_90,string_7425);
  return;
}

bool PC_String_Parse(uint32_t param_1,uint32_t *param_2) {
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

bool PC_String_ParseNoAlloc(uint32_t param_1,uint32_t param_2,uint32_t param_3) {
  int tmp_i1;
  uint8_t local_424 [16];
  uint8_t local_414 [1040];

  tmp_i1 = trap_PC_ReadToken(param_1,local_424);
  if (tmp_i1 != 0) {
    Q_strncpyz(param_2,local_414,param_3);
  }
  return tmp_i1 != 0;
}

void PC_String_tolower(char *param_1) {
  char tmp_c1;
  __int32_t **pp_Var2;

  tmp_c1 = *param_1;
  if (tmp_c1 != '\0') {
    pp_Var2 = __ctype_tolower_loc();
    do {
      *param_1 = (char)(*pp_Var2)[tmp_c1];
      tmp_c1 = param_1[1];
      param_1 = param_1 + 1;
    } while (tmp_c1 != '\0');
  }
  return;
}

uint32_t PC_Vec_Parse(uint32_t param_1,int param_2) {
  int tmp_i1;
  int tmp_i2;
  uint32_t local_10;

  tmp_i2 = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_1,&local_10);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_2 + tmp_i2 * 4) = local_10;
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 3);
  return 1;
}

void Parse1DMatrix(uint32_t param_1,uint param_2,int param_3) {
  byte *tmp_pb1;
  char *__nptr;
  int tmp_i2;
  uint tmp_u3;
  byte *tmp_pb4;
  uint8_t tmp_u5;
  uint8_t tmp_u6;
  byte tmp_b7;
  double tmp_d8;

  tmp_b7 = 0;
  tmp_u5 = &stack0xfffffff0 < (uint8_t *)0x2c;
  tmp_u6 = &stack0x00000000 == (uint8_t *)0x3c;
  tmp_pb1 = (byte *)COM_ParseExt_constprop_2();
  tmp_i2 = 2;
  tmp_pb4 = &g_dat_00055296;
  do {
    if (tmp_i2 == 0) break;
    tmp_i2 = tmp_i2 + -1;
    tmp_u5 = *tmp_pb1 < *tmp_pb4;
    tmp_u6 = *tmp_pb1 == *tmp_pb4;
    tmp_pb1 = tmp_pb1 + (uint)tmp_b7 * -2 + 1;
    tmp_pb4 = tmp_pb4 + (uint)tmp_b7 * -2 + 1;
  } while ((bool)tmp_u6);
  if ((!(bool)tmp_u5 && !(bool)tmp_u6) != (bool)tmp_u5) {
    Com_Error();
  }
  tmp_u5 = false;
  tmp_u6 = param_2 == 0;
  if (0 < (int)param_2) {
    tmp_u3 = 0;
    do {
      __nptr = (char *)COM_ParseExt_constprop_2();
      tmp_d8 = strtod(__nptr,(char **)0x0);
      *(float *)(param_3 + tmp_u3 * 4) = (float)tmp_d8;
      tmp_u3 = tmp_u3 + 1;
      tmp_u5 = tmp_u3 < param_2;
      tmp_u6 = tmp_u3 == param_2;
    } while (!(bool)tmp_u6);
  }
  tmp_pb1 = (byte *)COM_ParseExt_constprop_2();
  tmp_i2 = 2;
  tmp_pb4 = &g_dat_00055298;
  do {
    if (tmp_i2 == 0) break;
    tmp_i2 = tmp_i2 + -1;
    tmp_u5 = *tmp_pb1 < *tmp_pb4;
    tmp_u6 = *tmp_pb1 == *tmp_pb4;
    tmp_pb1 = tmp_pb1 + (uint)tmp_b7 * -2 + 1;
    tmp_pb4 = tmp_pb4 + (uint)tmp_b7 * -2 + 1;
  } while ((bool)tmp_u6);
  if ((!(bool)tmp_u5 && !(bool)tmp_u6) != (bool)tmp_u5) {
    Com_Error();
  }
  return;
}

void Parse2DMatrix(uint32_t param_1,int param_2,int param_3,int param_4) {
  char *tmp_pc1;
  int tmp_i2;
  char *tmp_pc3;
  uint8_t tmp_u4;
  byte tmp_b5;
  double tmp_d6;
  int local_34;
  char *local_30;

  tmp_b5 = 0;
  tmp_u4 = &stack0x00000000 == (uint8_t *)0x4c;
  tmp_pc1 = (char *)COM_ParseExt_constprop_2();
  tmp_i2 = 2;
  tmp_pc3 = "(";
  do {
    if (tmp_i2 == 0) break;
    tmp_i2 = tmp_i2 + -1;
    tmp_u4 = *tmp_pc1 == *tmp_pc3;
    tmp_pc1 = tmp_pc1 + (uint)tmp_b5 * -2 + 1;
    tmp_pc3 = tmp_pc3 + (uint)tmp_b5 * -2 + 1;
  } while ((bool)tmp_u4);
  if (!(bool)tmp_u4) {
    Com_Error();
  }
  tmp_u4 = param_2 == 0;
  if (0 < param_2) {
    tmp_u4 = true;
    local_34 = 0;
    do {
      tmp_pc1 = (char *)COM_ParseExt_constprop_2();
      tmp_i2 = 2;
      tmp_pc3 = "(";
      do {
        if (tmp_i2 == 0) break;
        tmp_i2 = tmp_i2 + -1;
        tmp_u4 = *tmp_pc1 == *tmp_pc3;
        tmp_pc1 = tmp_pc1 + (uint)tmp_b5 * -2 + 1;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b5 * -2 + 1;
      } while ((bool)tmp_u4);
      if (!(bool)tmp_u4) {
        Com_Error();
      }
      tmp_u4 = param_3 == 0;
      if (0 < param_3) {
        tmp_i2 = 0;
        do {
          tmp_pc1 = (char *)COM_ParseExt_constprop_2();
          tmp_d6 = strtod(tmp_pc1,(char **)0x0);
          *(float *)(param_4 + tmp_i2 * 4) = (float)tmp_d6;
          tmp_i2 = tmp_i2 + 1;
          tmp_u4 = tmp_i2 == param_3;
        } while (!(bool)tmp_u4);
      }
      tmp_pc1 = (char *)COM_ParseExt_constprop_2();
      tmp_i2 = 2;
      tmp_pc3 = ")";
      do {
        if (tmp_i2 == 0) break;
        tmp_i2 = tmp_i2 + -1;
        tmp_u4 = *tmp_pc1 == *tmp_pc3;
        tmp_pc1 = tmp_pc1 + (uint)tmp_b5 * -2 + 1;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b5 * -2 + 1;
      } while ((bool)tmp_u4);
      if (!(bool)tmp_u4) {
        Com_Error();
      }
      local_34 = local_34 + 1;
      param_4 = param_4 + param_3 * 4;
      tmp_u4 = local_34 == param_2;
    } while (!(bool)tmp_u4);
  }
  local_30 = ")";
  tmp_pc1 = (char *)COM_ParseExt_constprop_2();
  tmp_i2 = 2;
  do {
    if (tmp_i2 == 0) break;
    tmp_i2 = tmp_i2 + -1;
    tmp_u4 = *tmp_pc1 == *local_30;
    tmp_pc1 = tmp_pc1 + (uint)tmp_b5 * -2 + 1;
    local_30 = local_30 + (uint)tmp_b5 * -2 + 1;
  } while ((bool)tmp_u4);
  if (!(bool)tmp_u4) {
    Com_Error();
  }
  return;
}

void Parse3DMatrix(uint32_t param_1,int param_2,int param_3,int param_4,int param_5) {
  char *tmp_pc1;
  char *tmp_pc2;
  int tmp_i3;
  int tmp_i4;
  char *tmp_pc5;
  uint8_t tmp_u6;
  byte tmp_b7;
  double tmp_d8;
  int local_40;
  char *local_3c;
  int local_2c;
  int local_28;

  tmp_b7 = 0;
  tmp_u6 = &stack0x00000000 == (uint8_t *)0x5c;
  tmp_pc1 = (char *)COM_ParseExt_constprop_2();
  tmp_pc2 = "(";
  tmp_i3 = 2;
  tmp_pc5 = tmp_pc2;
  do {
    if (tmp_i3 == 0) break;
    tmp_i3 = tmp_i3 + -1;
    tmp_u6 = *tmp_pc1 == *tmp_pc5;
    tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
    tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
  } while ((bool)tmp_u6);
  if (!(bool)tmp_u6) {
    Com_Error();
  }
  tmp_u6 = param_2 == 0;
  if (0 < param_2) {
    local_2c = 0;
    local_28 = param_5;
    tmp_u6 = param_4 * 4 == 0;
    do {
      tmp_pc1 = (char *)COM_ParseExt_constprop_2();
      tmp_i3 = 2;
      tmp_pc5 = tmp_pc2;
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_u6 = *tmp_pc1 == *tmp_pc5;
        tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
      } while ((bool)tmp_u6);
      if (!(bool)tmp_u6) {
        Com_Error();
      }
      local_40 = 0;
      tmp_u6 = param_3 == 0;
      tmp_i3 = local_28;
      if (0 < param_3) {
        do {
          tmp_pc1 = (char *)COM_ParseExt_constprop_2();
          tmp_i4 = 2;
          tmp_pc5 = tmp_pc2;
          do {
            if (tmp_i4 == 0) break;
            tmp_i4 = tmp_i4 + -1;
            tmp_u6 = *tmp_pc1 == *tmp_pc5;
            tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
            tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
          } while ((bool)tmp_u6);
          if (!(bool)tmp_u6) {
            Com_Error();
          }
          tmp_u6 = param_4 == 0;
          if (0 < param_4) {
            tmp_i4 = 0;
            do {
              tmp_pc1 = (char *)COM_ParseExt_constprop_2();
              tmp_d8 = strtod(tmp_pc1,(char **)0x0);
              *(float *)(tmp_i3 + tmp_i4 * 4) = (float)tmp_d8;
              tmp_i4 = tmp_i4 + 1;
              tmp_u6 = tmp_i4 == param_4;
            } while (!(bool)tmp_u6);
          }
          tmp_pc1 = (char *)COM_ParseExt_constprop_2();
          tmp_i4 = 2;
          tmp_pc5 = ")";
          do {
            if (tmp_i4 == 0) break;
            tmp_i4 = tmp_i4 + -1;
            tmp_u6 = *tmp_pc1 == *tmp_pc5;
            tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
            tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
          } while ((bool)tmp_u6);
          if (!(bool)tmp_u6) {
            Com_Error();
          }
          local_40 = local_40 + 1;
          tmp_u6 = local_40 == param_3;
          tmp_i3 = tmp_i3 + param_4 * 4;
        } while (!(bool)tmp_u6);
      }
      tmp_pc1 = (char *)COM_ParseExt_constprop_2();
      tmp_i3 = 2;
      tmp_pc5 = ")";
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_u6 = *tmp_pc1 == *tmp_pc5;
        tmp_pc1 = tmp_pc1 + (uint)tmp_b7 * -2 + 1;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
      } while ((bool)tmp_u6);
      if (!(bool)tmp_u6) {
        Com_Error();
      }
      local_2c = local_2c + 1;
      local_28 = local_28 + param_4 * param_3 * 4;
      tmp_u6 = local_2c == param_2;
    } while (!(bool)tmp_u6);
  }
  local_3c = ")";
  tmp_pc2 = (char *)COM_ParseExt_constprop_2();
  tmp_i3 = 2;
  do {
    if (tmp_i3 == 0) break;
    tmp_i3 = tmp_i3 + -1;
    tmp_u6 = *tmp_pc2 == *local_3c;
    tmp_pc2 = tmp_pc2 + (uint)tmp_b7 * -2 + 1;
    local_3c = local_3c + (uint)tmp_b7 * -2 + 1;
  } while ((bool)tmp_u6);
  if (!(bool)tmp_u6) {
    Com_Error();
  }
  return;
}

bool Rect_Parse(uint32_t param_1,float *param_2) {
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

uint32_t String_Parse(uint32_t param_1,uint32_t *param_2) {
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

void UI_ReadableSize(char *param_1,int param_2,uint param_3) {
  size_t tmp_s1;

  if ((int)param_3 < 0x40000001) {
    if ((int)param_3 < 0x100001) {
      if ((int)param_3 < 0x401) {
        Com_sprintf(param_1,param_2,"%d bytes",param_3);
      }
      else {
        Com_sprintf(param_1,param_2,"%d KB",(int)param_3 >> 10);
      }
    }
    else {
      Com_sprintf(param_1,param_2,"%d",(int)param_3 >> 0x14);
      tmp_s1 = strlen(param_1);
      Com_sprintf(param_1 + tmp_s1,param_2 - tmp_s1,".%02d MB",(param_3 & 0xfffff) * 0x19 >> 0x12);
    }
  }
  else {
    Com_sprintf(param_1,param_2,"%d",1);
    tmp_s1 = strlen(param_1);
    Com_sprintf(param_1 + tmp_s1,param_2 - tmp_s1,".%02d GB",
                (int)(((param_3 & 0x3fffffff) + param_3 * 4) * 0x14) >> 0x1e);
  }
  return;
}
