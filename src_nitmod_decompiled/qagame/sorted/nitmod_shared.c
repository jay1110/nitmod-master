/* Q_ / COM_ / Info_ string helpers — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_shared.h"

long double Com_GetFlamethrowerRange(void)
{
  return (long double)2500.0;
}

void Q_SayConcatArgs(int param_1)
{
  char tmp_c1;
  char *tmp_pc2;
  int tmp_i3;
  
  tmp_pc2 = (char *)ConcatArgs(0);
  tmp_i3 = 0;
  tmp_c1 = *tmp_pc2;
  do {
    while( true ) {
      if ((tmp_c1 == '\0') || (tmp_i3 == param_1)) {
        return;
      }
      if (tmp_c1 == ' ') break;
LAB_000730a3:
      tmp_c1 = tmp_pc2[1];
      tmp_pc2 = tmp_pc2 + 1;
    }
    tmp_c1 = tmp_pc2[1];
    tmp_pc2 = tmp_pc2 + 1;
    if (tmp_c1 == ' ') {
      do {
        tmp_pc2 = tmp_pc2 + 1;
      } while (*tmp_pc2 == ' ');
      tmp_i3 = tmp_i3 + 1;
      goto LAB_000730a3;
    }
    tmp_i3 = tmp_i3 + 1;
  } while( true );
}

void Q_AddCR(char *param_1)
{
  char tmp_c1;
  char *tmp_pc2;
  char *tmp_pc3;
  
  tmp_c1 = *param_1;
  do {
    if (tmp_c1 == '\0') {
      return;
    }
    if (tmp_c1 == '\\') {
      if (param_1[1] != 'n') {
        param_1 = param_1 + 1;
        goto LAB_00073105;
      }
      tmp_c1 = param_1[2];
      tmp_pc3 = param_1 + 2;
      *param_1 = '\n';
      tmp_pc2 = param_1;
      while (tmp_c1 != '\0') {
        tmp_pc2 = tmp_pc2 + 1;
        tmp_pc3 = tmp_pc3 + 1;
        *tmp_pc2 = tmp_c1;
        tmp_c1 = *tmp_pc3;
      }
      tmp_pc2[1] = '\0';
    }
    else {
LAB_00073105:
      param_1 = param_1 + 1;
    }
    tmp_c1 = *param_1;
  } while( true );
}

int Q_SayArgc(void)
{
  char *tmp_pc1;
  int tmp_i2;
  char tmp_c3;
  
  tmp_pc1 = (char *)ConcatArgs(0);
  tmp_c3 = *tmp_pc1;
  if (tmp_c3 == '\0') {
    return 0;
  }
  tmp_i2 = 1;
  do {
    while (tmp_c3 != ' ') {
LAB_00073180:
      tmp_c3 = tmp_pc1[1];
      tmp_pc1 = tmp_pc1 + 1;
      if (tmp_c3 == '\0') {
        return tmp_i2;
      }
    }
    tmp_c3 = tmp_pc1[1];
    tmp_pc1 = tmp_pc1 + 1;
    if (tmp_c3 == ' ') {
      do {
        tmp_pc1 = tmp_pc1 + 1;
      } while (*tmp_pc1 == ' ');
      tmp_i2 = tmp_i2 + 1;
      goto LAB_00073180;
    }
    tmp_i2 = tmp_i2 + 1;
    if (tmp_c3 == '\0') {
      return tmp_i2;
    }
  } while( true );
}

uint32_t Q_SayArgv(int param_1,char *param_2,int param_3)
{
  char *tmp_pc1;
  int tmp_i2;
  char tmp_c3;
  int tmp_i4;
  
  if ((param_3 < 1) || (param_1 < 0)) {
    return 0;
  }
  *param_2 = '\0';
  tmp_i4 = 0;
  tmp_pc1 = (char *)ConcatArgs(0);
  tmp_c3 = *tmp_pc1;
LAB_0007321f:
  if (tmp_c3 == '\0') {
    return 0;
  }
  do {
    if (param_1 == tmp_i4) {
      if (param_3 < 2) goto LAB_00073298;
      tmp_i4 = 1;
      break;
    }
    if (tmp_c3 == ' ') {
      tmp_c3 = tmp_pc1[1];
      tmp_pc1 = tmp_pc1 + 1;
      if (tmp_c3 != ' ') goto code_r0x0007324c;
      do {
        tmp_pc1 = tmp_pc1 + 1;
      } while (*tmp_pc1 == ' ');
      tmp_i4 = tmp_i4 + 1;
    }
    tmp_c3 = tmp_pc1[1];
    tmp_pc1 = tmp_pc1 + 1;
    if (tmp_c3 == '\0') {
      return 0;
    }
  } while( true );
joined_r0x00073277:
  if (tmp_c3 == ' ') {
LAB_00073298:
    *param_2 = '\0';
    return 1;
  }
  *param_2 = tmp_c3;
  tmp_i2 = tmp_i4 + 1;
  param_2 = param_2 + 1;
  tmp_c3 = tmp_pc1[tmp_i4];
  if ((tmp_c3 == '\0') || (tmp_i4 = tmp_i2, param_3 <= tmp_i2)) goto LAB_00073298;
  goto joined_r0x00073277;
code_r0x0007324c:
  tmp_i4 = tmp_i4 + 1;
  goto LAB_0007321f;
}

void Com_Error(uint32_t param_1,char *param_2)
{
  char local_40c [1028];
  
  vsnprintf(local_40c,0x400,param_2,&stack0x0000000c);
  G_Error(&g_unk_0024e6e9,local_40c);
  return;
}

void Com_Printf(char *param_1)
{
  char local_40c [1028];
  
  vsnprintf(local_40c,0x400,param_1,&stack0x00000008);
  G_Printf(&g_unk_0024e6e9,local_40c);
  return;
}

void Q_rand(int *param_1)
{
  *param_1 = *param_1 * 0x10dcd + 1;
  return;
}

uint Q_random(uint *param_1)
{
  uint tmp_u1;
  
  tmp_u1 = *param_1 * 0x10dcd + 1;
  *param_1 = tmp_u1;
  return tmp_u1 & 0xffff;
}

long double Q_crandom(uint *param_1)
{
  float tmp_f1;
  uint tmp_u2;
  
  tmp_u2 = *param_1 * 0x10dcd + 1;
  *param_1 = tmp_u2;
  tmp_f1 = (float)(tmp_u2 & 0xffff) * 1.5258789e-05 - 0.5;
  return (long double)(tmp_f1 + tmp_f1);
}

int Q_rsqrt(int param_1)
{
  return 0x5f3759df - (param_1 >> 1);
}

uint Q_fabs(uint param_1)
{
  return param_1 & 0x7fffffff;
}

int Q_log2(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = 0;
  param_1 = param_1 >> 1;
  if (param_1 == 0) {
    return tmp_i1;
  }
  do {
    tmp_i1 = tmp_i1 + 1;
    param_1 = param_1 >> 1;
  } while (param_1 != 0);
  return tmp_i1;
}

uint64_t COM_ParseExt_constprop_2(int *param_1)
{
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
joined_r0x001103e3:
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
            goto joined_r0x001103e3;
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
                goto joined_r0x001103e3;
              }
              tmp_pc4 = tmp_pc4 + 1;
            }
            tmp_c2 = '\0';
            tmp_pc5 = tmp_pc4;
            goto joined_r0x001103e3;
          }
          tmp_c2 = '/';
        }
        else if (tmp_c2 == '\"') {
          tmp_pc4 = tmp_pc5 + 1;
          tmp_i3 = 0;
          tmp_c2 = *tmp_pc4;
          tmp_pc5 = tmp_pc5 + 2;
          if (tmp_c2 == '\\') goto LAB_00110487;
LAB_0011045d:
          do {
            if ((tmp_c2 == '\0') || (tmp_c2 == '\"')) {
LAB_001104dd:
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
              if (tmp_c2 != '\\') goto LAB_0011045d;
LAB_00110487:
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
                goto LAB_001104dd;
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
        goto LAB_00110590;
      }
      if (tmp_c2 == '\0') break;
      com_lines = com_lines + (uint)(tmp_c2 == '\n');
      tmp_c2 = tmp_pc5[1];
      tmp_pc5 = tmp_pc5 + 1;
    } while( true );
  }
  *param_1 = 0;
  return CONCAT44(local_14,&com_token);
LAB_00110590:
  if (tmp_i3 < 0x400) {
    (&com_token)[tmp_i3] = tmp_c2;
    tmp_i3 = tmp_i3 + 1;
  }
  tmp_pc5 = tmp_pc5 + 1;
  tmp_c2 = *tmp_pc5;
  if (tmp_c2 == '\n') {
    com_lines = com_lines + 1;
    goto LAB_001105b6;
  }
  if (tmp_c2 < '!') {
LAB_001105b6:
    if (tmp_i3 == 0x400) {
      tmp_i3 = 0;
    }
    (&com_token)[tmp_i3] = 0;
    *param_1 = (int)tmp_pc5;
    return CONCAT44(local_14,&com_token);
  }
  goto LAB_00110590;
}

void Info_RemoveKey_Big_part_1(char *param_1,char *param_2)
{
  char tmp_c1;
  char tmp_c2;
  int tmp_i3;
  char tmp_c4;
  char *tmp_pc5;
  int tmp_i7;
  int tmp_i8;
  char *local_402c;
  char local_401c [8192];
  char local_201c [8204];
  char *tmp_pc6;
  
  tmp_c4 = *param_1;
  local_402c = param_1;
  if (tmp_c4 == '\\') goto LAB_0011072b;
LAB_00110645:
  if (tmp_c4 == '\0') {
    return;
  }
  tmp_pc6 = local_401c;
  while( true ) {
    tmp_pc5 = tmp_pc6 + 1;
    param_1 = param_1 + 1;
    *tmp_pc6 = tmp_c4;
    tmp_c4 = *param_1;
    if (tmp_c4 == '\\') break;
    tmp_pc6 = tmp_pc5;
    if (tmp_c4 == '\0') {
      return;
    }
  }
  do {
    tmp_c4 = param_1[1];
    param_1 = param_1 + 1;
    *tmp_pc5 = '\0';
    tmp_pc6 = local_201c;
    while ((tmp_c4 != '\0' && (tmp_c4 != '\\'))) {
      param_1 = param_1 + 1;
      *tmp_pc6 = tmp_c4;
      tmp_pc6 = tmp_pc6 + 1;
      tmp_c4 = *param_1;
    }
    *tmp_pc6 = '\0';
    if (param_2 != (char *)0x0) {
      tmp_c1 = *param_2;
      tmp_i3 = 0;
      tmp_c2 = local_401c[0];
      do {
        tmp_i7 = (int)tmp_c1;
        tmp_i8 = (int)tmp_c2;
        if (tmp_i7 != tmp_i8) {
          if (tmp_i7 - 0x61U < 0x1a) {
            tmp_i7 = tmp_i7 + -0x20;
            if (tmp_i8 - 0x61U < 0x1a) goto LAB_001106d3;
          }
          else {
            if (0x19 < tmp_i8 - 0x61U) break;
LAB_001106d3:
            tmp_i8 = tmp_i8 + -0x20;
          }
          if (tmp_i7 != tmp_i8) break;
        }
        if (tmp_i8 == 0) goto LAB_00110748;
        tmp_c1 = param_2[tmp_i3 + 1];
        tmp_c2 = local_401c[tmp_i3 + 1];
        tmp_i3 = tmp_i3 + 1;
        if (tmp_i3 == 99999) {
LAB_00110748:
          strcpy(local_402c,param_1);
          return;
        }
      } while( true );
    }
    if (tmp_c4 == '\0') {
      return;
    }
    local_402c = param_1;
    if (tmp_c4 != '\\') goto LAB_00110645;
LAB_0011072b:
    param_1 = local_402c + 1;
    tmp_c4 = local_402c[1];
    if (tmp_c4 != '\\') goto LAB_00110645;
    tmp_pc5 = local_401c;
  } while( true );
}

void Info_RemoveKey_part_0(char *param_1,char *param_2)
{
  char tmp_c1;
  char tmp_c2;
  int tmp_i3;
  size_t tmp_s4;
  char tmp_c5;
  char *tmp_pc6;
  int tmp_i8;
  int tmp_i9;
  char *local_82c;
  char local_81c [1024];
  char local_41c [1036];
  char *tmp_pc7;
  
  tmp_c5 = *param_1;
  local_82c = param_1;
  if (tmp_c5 == '\\') goto LAB_0011088b;
LAB_001107a5:
  if (tmp_c5 == '\0') {
    return;
  }
  tmp_pc7 = local_81c;
  while( true ) {
    tmp_pc6 = tmp_pc7 + 1;
    param_1 = param_1 + 1;
    *tmp_pc7 = tmp_c5;
    tmp_c5 = *param_1;
    if (tmp_c5 == '\\') break;
    tmp_pc7 = tmp_pc6;
    if (tmp_c5 == '\0') {
      return;
    }
  }
  do {
    tmp_c5 = param_1[1];
    param_1 = param_1 + 1;
    *tmp_pc6 = '\0';
    tmp_pc7 = local_41c;
    while ((tmp_c5 != '\0' && (tmp_c5 != '\\'))) {
      param_1 = param_1 + 1;
      *tmp_pc7 = tmp_c5;
      tmp_pc7 = tmp_pc7 + 1;
      tmp_c5 = *param_1;
    }
    *tmp_pc7 = '\0';
    if (param_2 != (char *)0x0) {
      tmp_c1 = *param_2;
      tmp_i3 = 0;
      tmp_c2 = local_81c[0];
      do {
        tmp_i8 = (int)tmp_c1;
        tmp_i9 = (int)tmp_c2;
        if (tmp_i8 != tmp_i9) {
          if (tmp_i8 - 0x61U < 0x1a) {
            tmp_i8 = tmp_i8 + -0x20;
            if (tmp_i9 - 0x61U < 0x1a) goto LAB_00110833;
          }
          else {
            if (0x19 < tmp_i9 - 0x61U) break;
LAB_00110833:
            tmp_i9 = tmp_i9 + -0x20;
          }
          if (tmp_i8 != tmp_i9) break;
        }
        if (tmp_i9 == 0) goto LAB_001108a8;
        tmp_c1 = param_2[tmp_i3 + 1];
        tmp_c2 = local_81c[tmp_i3 + 1];
        tmp_i3 = tmp_i3 + 1;
        if (tmp_i3 == 99999) {
LAB_001108a8:
          tmp_s4 = strlen(param_1);
          memmove(local_82c,param_1,tmp_s4 + 1);
          return;
        }
      } while( true );
    }
    if (tmp_c5 == '\0') {
      return;
    }
    local_82c = param_1;
    if (tmp_c5 != '\\') goto LAB_001107a5;
LAB_0011088b:
    param_1 = local_82c + 1;
    tmp_c5 = local_82c[1];
    if (tmp_c5 != '\\') goto LAB_001107a5;
    tmp_pc6 = local_81c;
  } while( true );
}

void Com_Clamp(void)
{
  return;
}

void COM_FixPath(char *param_1)
{
  char tmp_c1;
  
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
  char tmp_c1;
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
  char tmp_c1;
  
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
  char tmp_c1;
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
  uint tmp_u1;
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
  uint tmp_u1;
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
  uint tmp_u1;
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

void COM_BackupParseSession(uint32_t *param_1)
{
  backup_lines = com_lines;
  backup_text = *param_1;
  return;
}

void COM_RestoreParseSession(uint32_t *param_1)
{
  com_lines = backup_lines;
  *param_1 = backup_text;
  return;
}

uint32_t COM_GetCurrentParseLine(void)
{
  return com_lines;
}

void COM_Parse(void)
{
  COM_ParseExt_constprop_2();
  return;
}

void COM_ParseError(char *param_1)
{
  vsnprintf(string_5132,0x1000,param_1,&stack0x00000008);
  Com_Printf("ERROR: %s, line %d: %s\n",com_parsename,com_lines,string_5132);
  return;
}

int COM_Compress(char *param_1)
{
  void *tmp_pc1;
  char tmp_c2;
  char *tmp_pc3;
  char *tmp_pc4;
  int tmp_i5;
  bool tmp_b6;
  
  if (param_1 == (char *)0x0) {
    g_unk_00000000 = 0;
    tmp_pc1 = (void *)invalidInstructionException();
    (*tmp_pc1)();
  }
  tmp_c2 = *param_1;
  tmp_i5 = 0;
  tmp_pc4 = param_1;
LAB_00110bf9:
  do {
    if (tmp_c2 == '\0') {
      *param_1 = '\0';
      return tmp_i5;
    }
    while( true ) {
      if (((tmp_c2 == '\n') || (tmp_c2 == '\r')) || (tmp_c2 != '/')) goto LAB_00110bf0;
      if (tmp_pc4[1] != '/') break;
      while( true ) {
        tmp_pc4 = tmp_pc4 + 1;
        tmp_c2 = *tmp_pc4;
        if (tmp_c2 == '\n') break;
        if (tmp_c2 == '\0') goto LAB_00110bf9;
      }
    }
    if (tmp_pc4[1] == '*') {
      tmp_c2 = tmp_pc4[2];
      tmp_pc3 = tmp_pc4 + 2;
      if (tmp_c2 == '\0') goto LAB_00110c90;
      break;
    }
LAB_00110bf0:
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
      goto LAB_00110bf9;
    }
  }
LAB_00110c90:
  tmp_c2 = '\0';
  tmp_pc4 = tmp_pc3;
  goto LAB_00110bf9;
}

uint8_t * COM_ParseExt(int *param_1,int param_2)
{
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
LAB_00110cec:
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
            goto LAB_00110cec;
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
                goto LAB_00110cec;
              }
              tmp_pc4 = tmp_pc4 + 1;
            }
            tmp_c3 = '\0';
            tmp_pc5 = tmp_pc4;
            goto LAB_00110cec;
          }
        }
        else if (tmp_c3 == '\"') {
          tmp_pc4 = tmp_pc5 + 1;
          tmp_c3 = *tmp_pc4;
          tmp_i6 = 0;
          tmp_pc5 = tmp_pc5 + 2;
          if (tmp_c3 == '\\') goto LAB_00110d7e;
LAB_00110d54:
          do {
            if ((tmp_c3 == '\0') || (tmp_c3 == '\"')) {
LAB_00110de2:
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
              if (tmp_c3 != '\\') goto LAB_00110d54;
LAB_00110d7e:
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
                goto LAB_00110de2;
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
        goto LAB_00110ea0;
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
LAB_00110ea0:
  if (tmp_i6 < 0x400) {
    (&com_token)[tmp_i6] = tmp_c3;
    tmp_i6 = tmp_i6 + 1;
  }
  tmp_pc5 = tmp_pc5 + 1;
  tmp_c3 = *tmp_pc5;
  if (tmp_c3 == '\n') {
    com_lines = com_lines + 1;
    goto LAB_00110ec6;
  }
  if (tmp_c3 < '!') {
LAB_00110ec6:
    if (tmp_i6 == 0x400) {
      tmp_i6 = 0;
    }
    (&com_token)[tmp_i6] = 0;
    *param_1 = (int)tmp_pc5;
    return &com_token;
  }
  goto LAB_00110ea0;
}

void COM_MatchToken(uint32_t param_1,char *param_2)
{
  char *__s1;
  int tmp_i1;
  
  __s1 = (char *)COM_ParseExt_constprop_2();
  tmp_i1 = strcmp(__s1,param_2);
  if (tmp_i1 != 0) {
    Com_Error(2,"MatchToken: %s != %s",__s1,param_2);
  }
  return;
}

bool Q_isprint(int param_1)
{
  return param_1 - 0x20U < 0x5f;
}

bool Q_islower(int param_1)
{
  return param_1 - 0x61U < 0x1a;
}

bool Q_isupper(int param_1)
{
  return param_1 - 0x41U < 0x1a;
}

bool Q_isalpha(uint param_1)
{
  return (param_1 & 0xffffffdf) - 0x41 < 0x1a;
}

bool Q_isnumeric(int param_1)
{
  return param_1 - 0x30U < 10;
}

bool Q_isalphanumeric(uint param_1)
{
  if ((param_1 & 0xffffffdf) - 0x41 < 0x1a) {
    return true;
  }
  return param_1 - 0x30 < 10;
}

bool Q_isforfilename(uint param_1)
{
  if ((param_1 & 0xffffffdf) - 0x41 < 0x1a) {
    return param_1 != 0x20;
  }
  if (9 < param_1 - 0x30) {
    return param_1 == 0x5f;
  }
  return true;
}

char * Q_strrchr(char *param_1,char param_2)
{
  char tmp_c1;
  char *tmp_pc2;
  
  tmp_pc2 = (char *)0x0;
  tmp_c1 = *param_1;
  if (tmp_c1 != '\0') {
    tmp_pc2 = (char *)0x0;
    do {
      if (param_2 == tmp_c1) {
        tmp_pc2 = param_1;
      }
      param_1 = param_1 + 1;
      tmp_c1 = *param_1;
    } while (tmp_c1 != '\0');
  }
  if (param_2 == '\0') {
    tmp_pc2 = param_1;
  }
  return tmp_pc2;
}

void Q_strncpyz(char *param_1,char *param_2,int param_3)
{
  if (param_2 == (char *)0x0) {
    Com_Error(0,"Q_strncpyz: NULL src");
  }
  if (param_3 == 0) {
    Com_Error(0,"Q_strncpyz: destsize < 1");
  }
  strncpy(param_1,param_2,param_3 - 1U);
  param_1[param_3 - 1U] = '\0';
  return;
}

int Q_stricmpn(char *param_1,char *param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  char *tmp_pc3;
  
  tmp_pc3 = param_1 + param_3;
  do {
    tmp_i2 = (int)*param_1;
    tmp_i1 = (int)*param_2;
    if (param_1 == tmp_pc3) {
      return 0;
    }
    if (tmp_i2 != tmp_i1) {
      if (tmp_i2 - 0x61U < 0x1a) {
        tmp_i2 = tmp_i2 + -0x20;
        if (tmp_i1 - 0x61U < 0x1a) goto LAB_00111753;
      }
      else {
        if (0x19 < tmp_i1 - 0x61U) goto LAB_0011177f;
LAB_00111753:
        tmp_i1 = tmp_i1 + -0x20;
      }
      if (tmp_i2 != tmp_i1) {
LAB_0011177f:
        return (uint)(tmp_i1 <= tmp_i2) * 2 + -1;
      }
    }
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    if (tmp_i1 == 0) {
      return 0;
    }
  } while( true );
}

int Q_strncmp(char *param_1,char *param_2,int param_3)
{
  char tmp_c1;
  char *tmp_pc2;
  
  tmp_pc2 = param_1 + param_3;
  while( true ) {
    tmp_c1 = *param_1;
    if (param_1 == tmp_pc2) {
      return 0;
    }
    if (tmp_c1 != *param_2) break;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
    if (tmp_c1 == '\0') {
      return 0;
    }
  }
  return (uint)(*param_2 <= tmp_c1) * 2 + -1;
}

int Q_stricmp(char *param_1,char *param_2)
{
  char tmp_c1;
  char tmp_c2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  
  if ((param_1 == (char *)0x0) || (param_2 == (char *)0x0)) {
    return -1;
  }
  tmp_c1 = *param_1;
  tmp_c2 = *param_2;
  tmp_i3 = 0;
  do {
    tmp_i5 = (int)tmp_c2;
    tmp_i4 = (int)tmp_c1;
    if (tmp_i4 != tmp_i5) {
      if (tmp_i4 - 0x61U < 0x1a) {
        tmp_i4 = tmp_i4 + -0x20;
        if (tmp_i5 - 0x61U < 0x1a) goto LAB_0011182b;
      }
      else {
        if (0x19 < tmp_i5 - 0x61U) goto LAB_00111868;
LAB_0011182b:
        tmp_i5 = tmp_i5 + -0x20;
      }
      if (tmp_i4 != tmp_i5) {
LAB_00111868:
        return (uint)(tmp_i5 <= tmp_i4) * 2 + -1;
      }
    }
    if (tmp_i5 == 0) {
      return 0;
    }
    tmp_c1 = param_1[tmp_i3 + 1];
    tmp_c2 = param_2[tmp_i3 + 1];
    tmp_i3 = tmp_i3 + 1;
    if (tmp_i3 == 99999) {
      return 0;
    }
  } while( true );
}

char * Q_strlwr(char *param_1)
{
  char tmp_c1;
  char *tmp_pc2;
  
  tmp_c1 = *param_1;
  tmp_pc2 = param_1;
  while (tmp_c1 != '\0') {
    if ((byte)(tmp_c1 + 0xbfU) < 0x1a) {
      *tmp_pc2 = tmp_c1 + ' ';
    }
    tmp_pc2 = tmp_pc2 + 1;
    tmp_c1 = *tmp_pc2;
  }
  return param_1;
}

char * Q_strupr(char *param_1)
{
  char tmp_c1;
  char *tmp_pc2;
  
  tmp_c1 = *param_1;
  tmp_pc2 = param_1;
  while (tmp_c1 != '\0') {
    if ((byte)(tmp_c1 + 0x9fU) < 0x1a) {
      *tmp_pc2 = tmp_c1 + -0x20;
    }
    tmp_pc2 = tmp_pc2 + 1;
    tmp_c1 = *tmp_pc2;
  }
  return param_1;
}

void Q_strcat(char *param_1,uint param_2,char *param_3)
{
  size_t tmp_s1;
  size_t __n;
  
  tmp_s1 = strlen(param_1);
  if (param_2 <= tmp_s1) {
    Com_Error(0,"Q_strcat: already overflowed");
  }
  if (param_3 == (char *)0x0) {
    Com_Error(0,"Q_strncpyz: NULL src");
  }
  if (param_2 - tmp_s1 == 0) {
    Com_Error(0,"Q_strncpyz: destsize < 1");
  }
  __n = (param_2 - tmp_s1) - 1;
  strncpy(param_1 + tmp_s1,param_3,__n);
  (param_1 + tmp_s1)[__n] = '\0';
  return;
}

int Q_PrintStrlen(char *param_1)
{
  int tmp_i1;
  char tmp_c2;
  bool tmp_b3;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  tmp_c2 = *param_1;
  tmp_i1 = 0;
  do {
    if (tmp_c2 == '\0') {
      return tmp_i1;
    }
    while (((tmp_b3 = tmp_c2 != '^', tmp_c2 = param_1[1], tmp_b3 || (tmp_c2 == '\0')) || (tmp_c2 == '^')))
    {
      param_1 = param_1 + 1;
      tmp_i1 = tmp_i1 + 1;
      if (tmp_c2 == '\0') {
        return tmp_i1;
      }
    }
    tmp_c2 = param_1[2];
    param_1 = param_1 + 2;
  } while( true );
}

void Q_CleanStr(char *param_1)
{
  char tmp_c1;
  char *tmp_pc2;
  
  tmp_c1 = *param_1;
  tmp_pc2 = param_1;
  do {
    while( true ) {
      if (tmp_c1 == '\0') {
        *tmp_pc2 = '\0';
        return;
      }
      if (tmp_c1 != '^') break;
      if ((param_1[1] == '\0') || (param_1[1] == '^')) goto LAB_00111a4d;
      param_1 = param_1 + 1;
LAB_00111a30:
      tmp_c1 = param_1[1];
      param_1 = param_1 + 1;
    }
    if (0x5e < (int)tmp_c1 - 0x20U) goto LAB_00111a30;
LAB_00111a4d:
    *tmp_pc2 = tmp_c1;
    tmp_pc2 = tmp_pc2 + 1;
    tmp_c1 = param_1[1];
    param_1 = param_1 + 1;
  } while( true );
}

uint32_t Q_isBadDirChar(char param_1)
{
  char tmp_c1;
  uint tmp_u2;
  char *tmp_pc3;
  char local_24 [16];
  uint32_t uStack_14;
  
  uStack_14 = 0x111a7e;
  tmp_u2 = 0;
  do {
    *(uint32_t *)(local_24 + tmp_u2) = *(uint32_t *)((int)&g_unk_0025c961 + tmp_u2);
    tmp_u2 = tmp_u2 + 4;
  } while (tmp_u2 < 0x14);
  if (param_1 != ';') {
    tmp_pc3 = local_24;
    do {
      tmp_c1 = *tmp_pc3;
      if (tmp_c1 == '\0') {
        return 0;
      }
      tmp_pc3 = tmp_pc3 + 1;
    } while (tmp_c1 != param_1);
  }
  return 1;
}

char * Q_CleanDirName(char *param_1)
{
  char tmp_c1;
  uint16_t tmp_u2;
  char *tmp_pc3;
  char *tmp_pc4;
  uint tmp_u5;
  int tmp_i6;
  char *tmp_pc7;
  uint32_t *tmp_pu8;
  uint tmp_u9;
  bool tmp_b10;
  char local_45;
  char *local_40;
  char local_25;
  char acStack_24 [20];
  
  local_45 = *param_1;
  tmp_pc7 = param_1;
  while (local_45 == '.') {
    tmp_pc7 = tmp_pc7 + 1;
    local_45 = *tmp_pc7;
  }
  if (local_45 == '\0') {
    *param_1 = '\0';
    return param_1;
  }
  local_40 = param_1;
  do {
    tmp_u9 = 0x15;
    tmp_b10 = ((uint)&local_25 & 1) != 0;
    tmp_pc4 = &local_25;
    tmp_pu8 = (uint32_t *)&g_unk_0025c960;
    if (tmp_b10) {
      tmp_u9 = 0x14;
      tmp_pu8 = &g_unk_0025c961;
      local_25 = ';';
      tmp_pc4 = acStack_24;
    }
    tmp_pc3 = tmp_pc4;
    if (((uint)tmp_pc4 & 2) != 0) {
      tmp_u2 = *(uint16_t *)tmp_pu8;
      tmp_pc3 = tmp_pc4 + 2;
      tmp_pu8 = (uint32_t *)((int)tmp_pu8 + 2);
      tmp_u9 = tmp_u9 - 2;
      *(uint16_t *)tmp_pc4 = tmp_u2;
    }
    tmp_u5 = 0;
    do {
      *(uint32_t *)(tmp_pc3 + tmp_u5) = *(uint32_t *)((int)tmp_pu8 + tmp_u5);
      tmp_u5 = tmp_u5 + 4;
    } while (tmp_u5 < (tmp_u9 & 0xfffffffc));
    tmp_i6 = 0;
    if ((tmp_u9 & 2) != 0) {
      *(uint16_t *)(tmp_pc3 + tmp_u5) = *(uint16_t *)((int)tmp_pu8 + tmp_u5);
      tmp_i6 = 2;
    }
    if (!tmp_b10) {
      (tmp_pc3 + tmp_u5)[tmp_i6] = *(char *)((int)((int)tmp_pu8 + tmp_u5) + tmp_i6);
    }
    if (local_25 == '\0') {
LAB_00111c60:
      *local_40 = local_45;
      local_40 = local_40 + 1;
    }
    else if (local_45 != local_25) {
      tmp_pc4 = acStack_24;
      do {
        tmp_c1 = *tmp_pc4;
        if (tmp_c1 == '\0') goto LAB_00111c60;
        tmp_pc4 = tmp_pc4 + 1;
      } while (local_45 != tmp_c1);
    }
    tmp_pc7 = tmp_pc7 + 1;
    local_45 = *tmp_pc7;
    if (local_45 == '\0') {
      *local_40 = '\0';
      return param_1;
    }
  } while( true );
}

void Com_sprintf(char *param_1,size_t param_2,char *param_3)
{
  int tmp_i1;
  
  tmp_i1 = vsnprintf(param_1,param_2,param_3,&stack0x00000010);
  if (tmp_i1 != -1) {
    return;
  }
  Com_Printf("Com_sprintf: overflow of %i bytes buffer\n",param_2);
  return;
}

void COM_BeginParseSession(uint32_t param_1)
{
  com_lines = 0;
  Com_sprintf(com_parsename,0x400,&g_unk_0024e6e9,param_1);
  return;
}

char * Info_ValueForKey(char *param_1,char *param_2)
{
  char *tmp_pc1;
  char tmp_c2;
  char tmp_c3;
  size_t tmp_s4;
  int tmp_i5;
  char *tmp_pc6;
  int tmp_i7;
  int tmp_i8;
  char *tmp_pc9;
  char local_201c [8204];
  
  if ((param_1 == (char *)0x0) || (param_2 == (char *)0x0)) {
LAB_00112090:
    return "";
  }
  tmp_s4 = strlen(param_1);
  if (0x1fff < tmp_s4) {
    Com_Error(2,"Info_ValueForKey: oversize infostring [%s] [%s]",param_1,param_2);
  }
  tmp_c3 = *param_1;
  valueindex_5390 = valueindex_5390 ^ 1;
  if (tmp_c3 == '\\') {
    tmp_c3 = param_1[1];
    param_1 = param_1 + 1;
  }
  tmp_pc1 = value_5389 + valueindex_5390 * 0x2000;
LAB_00111fb6:
  if (tmp_c3 == '\\') {
    tmp_pc6 = local_201c;
  }
  else {
    if (tmp_c3 == '\0') goto LAB_00112090;
    tmp_pc9 = local_201c;
    while( true ) {
      tmp_pc6 = tmp_pc9 + 1;
      param_1 = param_1 + 1;
      *tmp_pc9 = tmp_c3;
      tmp_c3 = *param_1;
      if (tmp_c3 == '\\') break;
      tmp_pc9 = tmp_pc6;
      if (tmp_c3 == '\0') goto LAB_00112090;
    }
  }
  tmp_c3 = param_1[1];
  tmp_pc9 = param_1 + 1;
  *tmp_pc6 = '\0';
  tmp_pc6 = tmp_pc1;
  while ((tmp_c3 != '\0' && (tmp_c3 != '\\'))) {
    tmp_pc9 = tmp_pc9 + 1;
    *tmp_pc6 = tmp_c3;
    tmp_pc6 = tmp_pc6 + 1;
    tmp_c3 = *tmp_pc9;
  }
  *tmp_pc6 = '\0';
  tmp_c3 = *param_2;
  tmp_i5 = 0;
  tmp_c2 = local_201c[0];
  do {
    tmp_i8 = (int)tmp_c2;
    tmp_i7 = (int)tmp_c3;
    if (tmp_i7 != tmp_i8) {
      if (tmp_i7 - 0x61U < 0x1a) {
        tmp_i7 = tmp_i7 + -0x20;
        if (tmp_i8 - 0x61U < 0x1a) goto LAB_0011203b;
      }
      else {
        if (0x19 < tmp_i8 - 0x61U) break;
LAB_0011203b:
        tmp_i8 = tmp_i8 + -0x20;
      }
      if (tmp_i7 != tmp_i8) break;
    }
    if (tmp_i8 == 0) {
      return tmp_pc1;
    }
    tmp_c3 = param_2[tmp_i5 + 1];
    tmp_c2 = local_201c[tmp_i5 + 1];
    tmp_i5 = tmp_i5 + 1;
    if (tmp_i5 == 99999) {
      return tmp_pc1;
    }
  } while( true );
  if (*tmp_pc9 == '\0') goto LAB_00112090;
  param_1 = tmp_pc9 + 1;
  tmp_c3 = tmp_pc9[1];
  goto LAB_00111fb6;
}

uint32_t Info_NextPair(uint32_t *param_1,char *param_2,char *param_3)
{
  char tmp_c1;
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

void Info_RemoveKey(char *param_1,char *param_2)
{
  size_t tmp_s1;
  char *tmp_pc2;
  
  tmp_s1 = strlen(param_1);
  if (0x3ff < tmp_s1) {
    Com_Error(2,"Info_RemoveKey: oversize infostring [%s] [%s]",param_1,param_2);
  }
  tmp_pc2 = strchr(param_2,0x5c);
  if (tmp_pc2 != (char *)0x0) {
    return;
  }
  Info_RemoveKey_part_0();
  return;
}

void Info_RemoveKey_Big(char *param_1,char *param_2)
{
  size_t tmp_s1;
  char *tmp_pc2;
  
  tmp_s1 = strlen(param_1);
  if (0x1fff < tmp_s1) {
    Com_Error(2,"Info_RemoveKey_Big: oversize infostring [%s] [%s]",param_1,param_2);
  }
  tmp_pc2 = strchr(param_2,0x5c);
  if (tmp_pc2 != (char *)0x0) {
    return;
  }
  Info_RemoveKey_Big_part_1();
  return;
}

bool Info_Validate(char *param_1)
{
  char *tmp_pc1;
  
  tmp_pc1 = strchr(param_1,0x22);
  if (tmp_pc1 != (char *)0x0) {
    return false;
  }
  tmp_pc1 = strchr(param_1,0x3b);
  return tmp_pc1 == (char *)0x0;
}

void Info_SetValueForKey(char *param_1,char *param_2,char *param_3)
{
  char tmp_c1;
  uint16_t tmp_u2;
  uint32_t tmp_u3;
  size_t tmp_s4;
  char *tmp_pc5;
  char *tmp_pc6;
  uint tmp_u7;
  uint tmp_u8;
  byte tmp_b9;
  char local_41c;
  char local_41b [1035];
  
  tmp_b9 = 0;
  tmp_s4 = strlen(param_1);
  if (0x3ff < tmp_s4) {
    Com_Error(2,"Info_SetValueForKey: oversize infostring [%s] [%s] [%s]",param_1,param_2,param_3);
  }
  tmp_pc5 = strchr(param_2,0x5c);
  if ((tmp_pc5 == (char *)0x0) && (tmp_pc5 = strchr(param_3,0x5c), tmp_pc5 == (char *)0x0)) {
    tmp_pc5 = strchr(param_2,0x3b);
    if ((tmp_pc5 == (char *)0x0) && (tmp_pc5 = strchr(param_3,0x3b), tmp_pc5 == (char *)0x0)) {
      tmp_pc5 = strchr(param_2,0x22);
      if ((tmp_pc5 == (char *)0x0) && (tmp_pc5 = strchr(param_3,0x22), tmp_pc5 == (char *)0x0)) {
        Info_RemoveKey(param_1,param_2);
        if (*param_3 != '\0') {
          tmp_pc5 = &local_41c;
          Com_sprintf(tmp_pc5,0x400,"\\%s\\%s",param_2,param_3);
          tmp_u7 = 0xffffffff;
          tmp_pc6 = tmp_pc5;
          do {
            if (tmp_u7 == 0) break;
            tmp_u7 = tmp_u7 - 1;
            tmp_c1 = *tmp_pc6;
            tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
          } while (tmp_c1 != '\0');
          tmp_u7 = ~tmp_u7;
          tmp_u8 = 0xffffffff;
          tmp_pc6 = param_1;
          do {
            if (tmp_u8 == 0) break;
            tmp_u8 = tmp_u8 - 1;
            tmp_c1 = *tmp_pc6;
            tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
          } while (tmp_c1 != '\0');
          if ((~tmp_u8 - 1) + (tmp_u7 - 1) < 0x401) {
            param_1 = param_1 + (~tmp_u8 - 1);
            if (7 < tmp_u7) {
              if (((uint)param_1 & 1) != 0) {
                tmp_pc5 = local_41b;
                *param_1 = local_41c;
                param_1 = param_1 + 1;
                tmp_u7 = tmp_u7 - 1;
              }
              tmp_pc6 = param_1;
              if (((uint)param_1 & 2) != 0) {
                tmp_u2 = *(uint16_t *)tmp_pc5;
                tmp_pc6 = param_1 + 2;
                tmp_pc5 = tmp_pc5 + 2;
                tmp_u7 = tmp_u7 - 2;
                *(uint16_t *)param_1 = tmp_u2;
              }
              param_1 = tmp_pc6;
              if (((uint)tmp_pc6 & 4) != 0) {
                tmp_u3 = *(uint32_t *)tmp_pc5;
                param_1 = tmp_pc6 + 4;
                tmp_pc5 = tmp_pc5 + 4;
                tmp_u7 = tmp_u7 - 4;
                *(uint32_t *)tmp_pc6 = tmp_u3;
              }
            }
            for (; tmp_u7 != 0; tmp_u7 = tmp_u7 - 1) {
              *param_1 = *tmp_pc5;
              tmp_pc5 = tmp_pc5 + (uint)tmp_b9 * -2 + 1;
              param_1 = param_1 + (uint)tmp_b9 * -2 + 1;
            }
          }
          else {
            Com_Printf("Info string length exceeded\n");
          }
        }
      }
      else {
        Com_Printf("Can\'t use keys or values with a \"\n");
      }
    }
    else {
      Com_Printf("Can\'t use keys or values with a semicolon\n");
    }
  }
  else {
    Com_Printf("Can\'t use keys or values with a \\\n");
  }
  return;
}

void Info_SetValueForKey_Big(char *param_1,char *param_2,char *param_3)
{
  char tmp_c1;
  uint16_t tmp_u2;
  uint32_t tmp_u3;
  size_t tmp_s4;
  char *tmp_pc5;
  char *tmp_pc6;
  uint tmp_u7;
  uint tmp_u8;
  byte tmp_b9;
  char local_201c;
  char local_201b [8203];
  
  tmp_b9 = 0;
  tmp_s4 = strlen(param_1);
  if (0x1fff < tmp_s4) {
    Com_Error(2,"Info_SetValueForKey: oversize infostring [%s] [%s] [%s]",param_1,param_2,param_3);
  }
  tmp_pc5 = strchr(param_2,0x5c);
  if ((tmp_pc5 == (char *)0x0) && (tmp_pc5 = strchr(param_3,0x5c), tmp_pc5 == (char *)0x0)) {
    tmp_pc5 = strchr(param_2,0x3b);
    if ((tmp_pc5 == (char *)0x0) && (tmp_pc5 = strchr(param_3,0x3b), tmp_pc5 == (char *)0x0)) {
      tmp_pc5 = strchr(param_2,0x22);
      if ((tmp_pc5 == (char *)0x0) && (tmp_pc5 = strchr(param_3,0x22), tmp_pc5 == (char *)0x0)) {
        Info_RemoveKey_Big(param_1,param_2);
        if (*param_3 != '\0') {
          tmp_pc5 = &local_201c;
          Com_sprintf(tmp_pc5,0x2000,"\\%s\\%s",param_2,param_3);
          tmp_u7 = 0xffffffff;
          tmp_pc6 = tmp_pc5;
          do {
            if (tmp_u7 == 0) break;
            tmp_u7 = tmp_u7 - 1;
            tmp_c1 = *tmp_pc6;
            tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
          } while (tmp_c1 != '\0');
          tmp_u7 = ~tmp_u7;
          tmp_u8 = 0xffffffff;
          tmp_pc6 = param_1;
          do {
            if (tmp_u8 == 0) break;
            tmp_u8 = tmp_u8 - 1;
            tmp_c1 = *tmp_pc6;
            tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
          } while (tmp_c1 != '\0');
          if ((~tmp_u8 - 1) + (tmp_u7 - 1) < 0x2001) {
            param_1 = param_1 + (~tmp_u8 - 1);
            if (7 < tmp_u7) {
              if (((uint)param_1 & 1) != 0) {
                tmp_pc5 = local_201b;
                *param_1 = local_201c;
                param_1 = param_1 + 1;
                tmp_u7 = tmp_u7 - 1;
              }
              tmp_pc6 = param_1;
              if (((uint)param_1 & 2) != 0) {
                tmp_u2 = *(uint16_t *)tmp_pc5;
                tmp_pc6 = param_1 + 2;
                tmp_pc5 = tmp_pc5 + 2;
                tmp_u7 = tmp_u7 - 2;
                *(uint16_t *)param_1 = tmp_u2;
              }
              param_1 = tmp_pc6;
              if (((uint)tmp_pc6 & 4) != 0) {
                tmp_u3 = *(uint32_t *)tmp_pc5;
                param_1 = tmp_pc6 + 4;
                tmp_pc5 = tmp_pc5 + 4;
                tmp_u7 = tmp_u7 - 4;
                *(uint32_t *)tmp_pc6 = tmp_u3;
              }
            }
            for (; tmp_u7 != 0; tmp_u7 = tmp_u7 - 1) {
              *param_1 = *tmp_pc5;
              tmp_pc5 = tmp_pc5 + (uint)tmp_b9 * -2 + 1;
              param_1 = param_1 + (uint)tmp_b9 * -2 + 1;
            }
          }
          else {
            Com_Printf("BIG Info string length exceeded\n");
          }
        }
      }
      else {
        Com_Printf("Can\'t use keys or values with a \"\n");
      }
    }
    else {
      Com_Printf("Can\'t use keys or values with a semicolon\n");
    }
  }
  else {
    Com_Printf("Can\'t use keys or values with a \\\n");
  }
  return;
}

uint8_t * Q_StrReplace(uint *param_1,char *param_2,char *param_3)
{
  size_t tmp_s1;
  uint tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  uint *tmp_pu5;
  uint tmp_u6;
  uint *tmp_pu7;
  int tmp_i8;
  char *__dest;
  uint *tmp_pu9;
  char *tmp_pc10;
  uint *tmp_pu11;
  char local_831;
  uint *local_82c;
  char acStack_81f [3];
  uint local_81c [255];
  char acStack_420 [4];
  uint local_41c;
  uint32_t local_418 [254];
  uint8_t local_1d;
  uint32_t uStack_14;
  
  uStack_14 = 0x11280d;
  local_81c[0] = 0;
  tmp_u2 = 0;
  do {
    tmp_u3 = tmp_u2;
    *(uint32_t *)((int)local_81c + tmp_u3 + 4) = 0;
    *(uint32_t *)((int)local_81c + tmp_u3 + 8) = 0;
    tmp_u2 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0x3f8);
  *(uint32_t *)((int)local_81c + tmp_u3 + 0xc) = 0;
  local_41c = 0;
  tmp_u2 = 0;
  do {
    tmp_u3 = tmp_u2;
    *(uint32_t *)((int)local_418 + tmp_u3) = 0;
    *(uint32_t *)((int)local_418 + tmp_u3 + 4) = 0;
    tmp_u2 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0x3f8);
  *(uint32_t *)((int)local_418 + tmp_u3 + 8) = 0;
  local_831 = (char)*param_1;
  if (local_831 != '\0') {
    if (*param_2 != '\0') {
      if (*param_3 != '\0') {
        strncpy((char *)&local_41c,param_3,0x3ff);
        local_1d = 0;
      }
      tmp_s1 = strlen(param_2);
      tmp_pu7 = &local_41c;
      do {
        tmp_pu11 = tmp_pu7;
        tmp_u2 = *tmp_pu11 + 0xfefefeff & ~*tmp_pu11;
        tmp_u3 = tmp_u2 & 0x80808080;
        tmp_pu7 = tmp_pu11 + 1;
      } while (tmp_u3 == 0);
      tmp_u6 = tmp_u3 >> 0x10;
      tmp_pu7 = (uint *)((int)tmp_pu11 + 6);
      if ((tmp_u2 & 0x8080) != 0) {
        tmp_pu7 = tmp_pu11 + 1;
        tmp_u6 = tmp_u3;
      }
      tmp_pu11 = param_1;
      local_82c = local_81c;
LAB_00112930:
      param_1 = tmp_pu11;
      tmp_pu11 = (uint *)(tmp_s1 + (int)param_1);
      tmp_pu5 = param_1;
      tmp_pc10 = param_2;
      do {
        tmp_i8 = (int)(char)*tmp_pu5;
        tmp_i4 = (int)*tmp_pc10;
        tmp_pu9 = local_81c;
        if (tmp_pu5 == tmp_pu11) break;
        if (tmp_i8 != tmp_i4) {
          if (tmp_i8 - 0x61U < 0x1a) {
            tmp_i8 = tmp_i8 + -0x20;
            if (tmp_i4 - 0x61U < 0x1a) goto LAB_0011295b;
          }
          else {
            if (0x19 < tmp_i4 - 0x61U) goto LAB_00112993;
LAB_0011295b:
            tmp_i4 = tmp_i4 + -0x20;
          }
          if (tmp_i8 != tmp_i4) goto LAB_00112993;
        }
        tmp_pu5 = (uint *)((int)tmp_pu5 + 1);
        tmp_pc10 = tmp_pc10 + 1;
      } while (tmp_i4 != 0);
      do {
        tmp_pu5 = tmp_pu9;
        tmp_u3 = *tmp_pu5 + 0xfefefeff & ~*tmp_pu5;
        tmp_u2 = tmp_u3 & 0x80808080;
        tmp_pu9 = tmp_pu5 + 1;
      } while (tmp_u2 == 0);
      if ((tmp_u3 & 0x8080) == 0) {
        tmp_pu9 = (uint *)((int)tmp_pu5 + 6);
        tmp_u2 = tmp_u2 >> 0x10;
      }
      tmp_pc10 = (char *)((int)tmp_pu9 +
                        ((-3 - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) - (int)local_81c));
      if (((char *)0x3ff < tmp_pc10) &&
         (Com_Error(0,"Q_strcat: already overflowed"), tmp_pc10 == (char *)0x400)) {
        Com_Error(0,"Q_strncpyz: destsize < 1");
      }
      __dest = (char *)((int)local_81c + (int)tmp_pc10);
      strncpy(__dest,(char *)&local_41c,0x3ffU - (int)tmp_pc10);
      __dest[0x3ffU - (int)tmp_pc10] = '\0';
      local_82c = (uint *)((int)local_82c +
                          (int)((int)tmp_pu7 +
                               ((-3 - (uint)CARRY1((byte)tmp_u6,(byte)tmp_u6)) - (int)&local_41c)));
      goto LAB_001129f4;
    }
LAB_00112a10:
    strncpy(final_5463,(char *)param_1,0x3ff);
    final_5463[0x3ff] = 0;
  }
  return final_5463;
LAB_00112993:
  do {
    tmp_pu11 = tmp_pu9;
    tmp_u3 = *tmp_pu11 + 0xfefefeff & ~*tmp_pu11;
    tmp_u2 = tmp_u3 & 0x80808080;
    tmp_pu9 = tmp_pu11 + 1;
  } while (tmp_u2 == 0);
  tmp_pu5 = tmp_pu11 + 1;
  if ((tmp_u3 & 0x8080) == 0) {
    tmp_pu5 = (uint *)((int)tmp_pu11 + 6);
    tmp_u2 = tmp_u2 >> 0x10;
  }
  if ((char *)((int)tmp_pu5 + (-(int)local_81c - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) + -2) <
      (char *)0x400) {
    *(char *)((int)local_82c + 1) = '\0';
    *(char *)local_82c = local_831;
    local_82c = (uint *)((int)local_82c + 1);
  }
  tmp_pu11 = (uint *)((int)param_1 + 1);
LAB_001129f4:
  local_831 = (char)*tmp_pu11;
  param_1 = local_81c;
  if (local_831 == '\0') goto LAB_00112a10;
  goto LAB_00112930;
}

uint64_t COM_ParseExt_nico(uint32_t *param_1,int param_2)
{
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
joined_r0x00112b86:
    if (' ' < tmp_c2) {
      if ((tmp_b1) && (param_2 == 0)) {
        *param_1 = tmp_pc5;
        goto LAB_00112c14;
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
          goto joined_r0x00112b86;
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
              goto joined_r0x00112b86;
            }
            tmp_pc4 = tmp_pc4 + 1;
          }
          tmp_c2 = '\0';
          tmp_pc5 = tmp_pc4;
          goto joined_r0x00112b86;
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
LAB_00112c14:
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
      goto joined_r0x00112b86;
    }
  }
  *param_1 = 0;
  return CONCAT44(local_14,&com_token);
}

