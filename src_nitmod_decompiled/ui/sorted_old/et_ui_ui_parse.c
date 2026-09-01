/* Configuration parsing, script loading
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"
#include "et_ui_imports.h"
#include "et_ui_ui_parse.h"

void PC_SourceWarning(uint32_t param_1,char *param_2)

{
{  uint32_t local_90;
  uint8_t local_8c [128];
  
  vsnprintf(string_7425,0x1000,param_2,&stack0x0000000c);
  local_90 = 0;
  local_8c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_8c,&local_90);
  Com_Printf("^3WARNING: %s, line %d: %s\n",local_8c,local_90,string_7425);
  return;
}

void PC_SourceError(uint32_t param_1,char *param_2)

{
{  uint32_t local_90;
  uint8_t local_8c [128];
  
  vsnprintf(string_7433,0x1000,param_2,&stack0x0000000c);
  local_90 = 0;
  local_8c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_8c,&local_90);
  Com_Printf("^1ERROR: %s, line %d: %s\n",local_8c,local_90,string_7433);
  return;
}

uint32_t PC_Float_Parse(uint32_t param_1,float *param_2)

{
{  int tmp_i1;
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

uint32_t PC_Color_Parse(uint32_t param_1,int param_2)

{
{  int tmp_i1;
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

uint32_t PC_Vec_Parse(uint32_t param_1,int param_2)

{
{  int tmp_i1;
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

uint32_t PC_Int_Parse(uint32_t param_1,int *param_2)

{
{  int tmp_i1;
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

bool PC_String_Parse(uint32_t param_1,uint32_t *param_2)

{
{  int tmp_i1;
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

bool PC_String_ParseNoAlloc(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  int tmp_i1;
  uint8_t local_424 [16];
  uint8_t local_414 [1040];
  
  tmp_i1 = trap_PC_ReadToken(param_1,local_424);
  if (tmp_i1 != 0) {
    Q_strncpyz(param_2,local_414,param_3);
  }
  return tmp_i1 != 0;
}

uint64_t COM_ParseExt_constprop_2(int *param_1)

{
{  char *tmp_pc1;
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

void COM_FixPath(char *param_1)

{
{  char tmp_c1;
  
  tmp_c1 = *param_1;
  do {
    if (tmp_c1 == '\0') {
      return;
    }
    while (tmp_c1 != '\\') {
      param_1 = param_1 + 1;
      tmp_c1 = *param_1;
      if (tmp_c1 == '\0') {
        return;
      }
    }
    *param_1 = '/';
    param_1 = param_1 + 1;
    tmp_c1 = *param_1;
  } while( true );
}

char * COM_SkipPath(char *param_1)

{
{  char tmp_c1;
  char *tmp_pc2;
  
  tmp_c1 = *param_1;
  tmp_pc2 = param_1;
  while (tmp_c1 != '\0') {
    tmp_pc2 = tmp_pc2 + 1;
    if (tmp_c1 == '/') {
      param_1 = tmp_pc2;
    }
    tmp_c1 = *tmp_pc2;
  }
  return param_1;
}

void COM_StripExtension(char *param_1,char *param_2)

{
{  char tmp_c1;
  
  tmp_c1 = *param_1;
  while ((tmp_c1 != '.' && (tmp_c1 != '\0'))) {
    param_1 = param_1 + 1;
    *param_2 = tmp_c1;
    param_2 = param_2 + 1;
    tmp_c1 = *param_1;
  }
  *param_2 = '\0';
  return;
}

void COM_StripFilename(char *param_1,char *param_2)

{
{  char tmp_c1;
  size_t __n;
  char *tmp_pc2;
  
  __n = strlen(param_1);
  if (__n == 0xffffffff) {
    Com_Error(0,"Q_strncpyz: destsize < 1");
  }
  strncpy(param_2,param_1,__n);
  param_2[__n] = '\0';
  tmp_c1 = *param_2;
  tmp_pc2 = param_2;
  while (tmp_c1 != '\0') {
    param_2 = param_2 + 1;
    if (tmp_c1 == '/') {
      tmp_pc2 = param_2;
    }
    tmp_c1 = *param_2;
  }
  *tmp_pc2 = '\0';
  return;
}

uint COM_BitCheck(int param_1,uint param_2)

{
{  uint tmp_u1;
  int tmp_i2;
  
  if ((int)param_2 < 0x20) {
    tmp_i2 = 0;
  }
  else {
    param_2 = param_2 - 0x20;
    tmp_u1 = (param_2 >> 5) + 1;
    if (3 < tmp_u1) {
      return 0;
    }
    tmp_i2 = tmp_u1 * 4;
  }
  return *(int *)(param_1 + tmp_i2) >> ((byte)param_2 & 0x1f) & 1;
}

void COM_BitSet(int param_1,uint param_2)

{
{  uint tmp_u1;
  int tmp_i2;
  
  if ((int)param_2 < 0x20) {
    tmp_i2 = 0;
  }
  else {
    param_2 = param_2 - 0x20;
    tmp_u1 = (param_2 >> 5) + 1;
    if (3 < tmp_u1) {
      return;
    }
    tmp_i2 = tmp_u1 * 4;
  }
  *(uint *)(param_1 + tmp_i2) = *(uint *)(param_1 + tmp_i2) | 1 << ((byte)param_2 & 0x1f);
  return;
}

void COM_BitClear(int param_1,uint param_2)

{
{  uint tmp_u1;
  byte tmp_b2;
  int tmp_i3;
  
  if ((int)param_2 < 0x20) {
    tmp_i3 = 0;
  }
  else {
    param_2 = param_2 - 0x20;
    tmp_u1 = (param_2 >> 5) + 1;
    if (3 < tmp_u1) {
      return;
    }
    tmp_i3 = tmp_u1 * 4;
  }
  tmp_b2 = (byte)param_2 & 0x1f;
  *(uint *)(param_1 + tmp_i3) =
       *(uint *)(param_1 + tmp_i3) & (-2 << tmp_b2 | 0xfffffffeU >> 0x20 - tmp_b2);
  return;
}

void COM_ParseError(char *param_1)

{
{  vsnprintf(string_5132,0x1000,param_1,&stack0x00000008);
  Com_Printf("ERROR: %s, line %d: %s\n",com_parsename,com_lines,string_5132);
  return;
}

int COM_Compress(char *param_1)

{
{  void *tmp_pc1;
  char tmp_c2;
  char *tmp_pc3;
  char *tmp_pc4;
  int tmp_i5;
  bool tmp_b6;
  
  if (param_1 == (char *)0x0) {
    g_dat_00000000 = 0;
    tmp_pc1 = (void *)invalidInstructionException();
    (*tmp_pc1)();
  }
  tmp_c2 = *param_1;
  tmp_i5 = 0;
  tmp_pc4 = param_1;
LAB_0001dad9:
  do {
    if (tmp_c2 == '\0') {
      *param_1 = '\0';
      return tmp_i5;
    }
    while( true ) {
      if (((tmp_c2 == '\n') || (tmp_c2 == '\r')) || (tmp_c2 != '/')) goto LAB_0001dad0;
      if (tmp_pc4[1] != '/') break;
      while( true ) {
        tmp_pc4 = tmp_pc4 + 1;
        tmp_c2 = *tmp_pc4;
        if (tmp_c2 == '\n') break;
        if (tmp_c2 == '\0') goto LAB_0001dad9;
      }
    }
    if (tmp_pc4[1] == '*') {
      tmp_c2 = tmp_pc4[2];
      tmp_pc3 = tmp_pc4 + 2;
      if (tmp_c2 == '\0') goto LAB_0001db70;
      break;
    }
LAB_0001dad0:
    *param_1 = tmp_c2;
    tmp_i5 = tmp_i5 + 1;
    param_1 = param_1 + 1;
    tmp_c2 = tmp_pc4[1];
    tmp_pc4 = tmp_pc4 + 1;
  } while( true );
  while (tmp_pc3 = tmp_pc3 + 1, tmp_c2 != '\0') {
    tmp_b6 = tmp_c2 == '*';
    tmp_c2 = tmp_pc3[1];
    if ((tmp_b6) && (tmp_c2 == '/')) {
      tmp_pc4 = tmp_pc3 + 2;
      tmp_c2 = tmp_pc3[2];
      goto LAB_0001dad9;
    }
  }
LAB_0001db70:
  tmp_c2 = '\0';
  tmp_pc4 = tmp_pc3;
  goto LAB_0001dad9;
}

uint8_t * COM_ParseExt(int *param_1,int param_2)

{
{  bool tmp_b1;
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

void COM_MatchToken(uint32_t param_1,char *param_2)

{
{  char *__s1;
  int tmp_i1;
  
  __s1 = (char *)COM_ParseExt_constprop_2();
  tmp_i1 = strcmp(__s1,param_2);
  if (tmp_i1 != 0) {
    Com_Error(2,"MatchToken: %s != %s",__s1,param_2);
  }
  return;
}

void Parse1DMatrix(uint32_t param_1,uint param_2,int param_3)

{
{  byte *tmp_pb1;
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

void Parse2DMatrix(uint32_t param_1,int param_2,int param_3,int param_4)

{
{  char *tmp_pc1;
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

void Parse3DMatrix(uint32_t param_1,int param_2,int param_3,int param_4,int param_5)

{
{  char *tmp_pc1;
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

void Com_sprintf(char *param_1,size_t param_2,char *param_3)

{
{  int tmp_i1;
  
  tmp_i1 = vsnprintf(param_1,param_2,param_3,&stack0x00000010);
  if (tmp_i1 != -1) {
    return;
  }
  Com_Printf("Com_sprintf: overflow of %i bytes buffer\n",param_2);
  return;
}

uint32_t Info_NextPair(uint32_t *param_1,char *param_2,char *param_3)

{
{  char tmp_c1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  char *tmp_pc4;
  
  tmp_pc3 = (char *)*param_1;
  tmp_c1 = *tmp_pc3;
  *param_2 = '\0';
  *param_3 = '\0';
  tmp_pc3 = tmp_pc3 + (tmp_c1 == '\\');
  tmp_c1 = *tmp_pc3;
  tmp_pc4 = param_2;
  while( true ) {
    if (tmp_c1 == '\\') {
      *tmp_pc4 = '\0';
      tmp_u2 = 0;
      if (*param_2 != '\0') {
        tmp_pc4 = tmp_pc3 + 1;
        tmp_c1 = tmp_pc3[1];
        while ((tmp_c1 != '\0' && (tmp_c1 != '\\'))) {
          tmp_pc4 = tmp_pc4 + 1;
          *param_3 = tmp_c1;
          param_3 = param_3 + 1;
          tmp_c1 = *tmp_pc4;
        }
        *param_3 = '\0';
        tmp_u2 = 1;
        *param_1 = tmp_pc4;
      }
      return tmp_u2;
    }
    if (tmp_c1 == '\0') break;
    tmp_pc3 = tmp_pc3 + 1;
    *tmp_pc4 = tmp_c1;
    tmp_c1 = *tmp_pc3;
    tmp_pc4 = tmp_pc4 + 1;
  }
  *param_2 = '\0';
  *param_1 = tmp_pc3;
  return 1;
}

bool Info_Validate(char *param_1)

{
{  char *tmp_pc1;
  
  tmp_pc1 = strchr(param_1,0x22);
  if (tmp_pc1 != (char *)0x0) {
    return false;
  }
  tmp_pc1 = strchr(param_1,0x3b);
  return tmp_pc1 == (char *)0x0;
}

uint64_t COM_ParseExt_nico(uint32_t *param_1,int param_2)

{
{  bool tmp_b1;
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

void Com_Error(uint32_t param_1,char *param_2)

{
{  uint32_t tmp_u1;
  char local_40c [1028];
  
  vsnprintf(local_40c,0x400,param_2,&stack0x0000000c);
  tmp_u1 = va(&g_dat_0005580c,local_40c);
  trap_Error(tmp_u1);
  return;
}

void Com_Printf(char *param_1)

{
{  uint32_t tmp_u1;
  char local_40c [1028];
  
  vsnprintf(local_40c,0x400,param_1,&stack0x00000008);
  tmp_u1 = va(&g_dat_0005580c,local_40c);
  trap_Print(tmp_u1);
  return;
}

void Com_DPrintf(char *param_1)

{
{  long double tmp_l1;
  char local_100c [4100];
  
  tmp_l1 = (long double)trap_Cvar_VariableValue("developer");
  if ((int)ROUND(tmp_l1) != 0) {
    vsnprintf(local_100c,0x1000,param_1,&stack0x00000008);
    Com_Printf(&g_dat_0005580c,local_100c);
  }
  return;
}

uint32_t Float_Parse(uint32_t param_1,float *param_2)

{
{  char *__nptr;
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
{  char *__nptr;
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
{  char *__nptr;
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
{  char *tmp_pc1;
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
{  char *tmp_pc1;
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

uint32_t PC_Script_Parse(uint32_t param_1,uint32_t *param_2)

{
{  int tmp_i1;
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

uint32_t ParseColorRange(int param_1,uint32_t param_2,int param_3)

{
{  uint16_t tmp_u1;
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
