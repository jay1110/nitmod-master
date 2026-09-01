/* Key binding, keyboard events
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"
#include "et_ui_imports.h"
#include "et_ui_ui_key.h"

void Info_RemoveKey_Big_part_1(char *param_1,char *param_2)

{
{  char tmp_c1;
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
  if (tmp_c4 == '\\') goto LAB_0001d60b;
LAB_0001d525:
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
            if (tmp_i8 - 0x61U < 0x1a) goto LAB_0001d5b3;
          }
          else {
            if (0x19 < tmp_i8 - 0x61U) break;
LAB_0001d5b3:
            tmp_i8 = tmp_i8 + -0x20;
          }
          if (tmp_i7 != tmp_i8) break;
        }
        if (tmp_i8 == 0) goto LAB_0001d628;
        tmp_c1 = param_2[tmp_i3 + 1];
        tmp_c2 = local_401c[tmp_i3 + 1];
        tmp_i3 = tmp_i3 + 1;
        if (tmp_i3 == 99999) {
LAB_0001d628:
          strcpy(local_402c,param_1);
          return;
        }
      } while( true );
    }
    if (tmp_c4 == '\0') {
      return;
    }
    local_402c = param_1;
    if (tmp_c4 != '\\') goto LAB_0001d525;
LAB_0001d60b:
    param_1 = local_402c + 1;
    tmp_c4 = local_402c[1];
    if (tmp_c4 != '\\') goto LAB_0001d525;
    tmp_pc5 = local_401c;
  } while( true );
}

void Info_RemoveKey_part_0(char *param_1,char *param_2)

{
{  char tmp_c1;
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
  if (tmp_c5 == '\\') goto LAB_0001d76b;
LAB_0001d685:
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
            if (tmp_i9 - 0x61U < 0x1a) goto LAB_0001d713;
          }
          else {
            if (0x19 < tmp_i9 - 0x61U) break;
LAB_0001d713:
            tmp_i9 = tmp_i9 + -0x20;
          }
          if (tmp_i8 != tmp_i9) break;
        }
        if (tmp_i9 == 0) goto LAB_0001d788;
        tmp_c1 = param_2[tmp_i3 + 1];
        tmp_c2 = local_81c[tmp_i3 + 1];
        tmp_i3 = tmp_i3 + 1;
        if (tmp_i3 == 99999) {
LAB_0001d788:
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
    if (tmp_c5 != '\\') goto LAB_0001d685;
LAB_0001d76b:
    param_1 = local_82c + 1;
    tmp_c5 = local_82c[1];
    if (tmp_c5 != '\\') goto LAB_0001d685;
    tmp_pc6 = local_81c;
  } while( true );
}

char * Info_ValueForKey(char *param_1,char *param_2)

{
{  char *tmp_pc1;
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
LAB_0001ef70:
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
LAB_0001ee96:
  if (tmp_c3 == '\\') {
    tmp_pc6 = local_201c;
  }
  else {
    if (tmp_c3 == '\0') goto LAB_0001ef70;
    tmp_pc9 = local_201c;
    while( true ) {
      tmp_pc6 = tmp_pc9 + 1;
      param_1 = param_1 + 1;
      *tmp_pc9 = tmp_c3;
      tmp_c3 = *param_1;
      if (tmp_c3 == '\\') break;
      tmp_pc9 = tmp_pc6;
      if (tmp_c3 == '\0') goto LAB_0001ef70;
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
        if (tmp_i8 - 0x61U < 0x1a) goto LAB_0001ef1b;
      }
      else {
        if (0x19 < tmp_i8 - 0x61U) break;
LAB_0001ef1b:
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
  if (*tmp_pc9 == '\0') goto LAB_0001ef70;
  param_1 = tmp_pc9 + 1;
  tmp_c3 = tmp_pc9[1];
  goto LAB_0001ee96;
}

void Info_RemoveKey(char *param_1,char *param_2)

{
{  size_t tmp_s1;
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
{  size_t tmp_s1;
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

void Info_SetValueForKey(char *param_1,char *param_2,char *param_3)

{
{  char tmp_c1;
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
{  char tmp_c1;
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

bool UI_CheckExecKey(int param_1)

{
{  int tmp_i1;
  bool tmp_b2;
  
  tmp_i1 = Menu_GetFocused();
  if (g_editingField == 0) {
    tmp_b2 = false;
    if (param_1 < 0x101) {
      if (tmp_i1 == 0) {
        if (GHIDRA_FIELD(cl_bypassMouseInput, 12, 4) != 0) {
          tmp_i1 = trap_Key_GetCatcher();
          if (tmp_i1 == 0) {
            trap_Cvar_Set("cl_bypassMouseInput","0");
          }
        }
      }
      else {
        tmp_b2 = *(int *)(tmp_i1 + 0xf4 + param_1 * 4) != 0;
      }
    }
    return tmp_b2;
  }
  return true;
}

void _UI_KeyEvent(uint32_t param_1,uint32_t param_2)

{
{  int tmp_i1;
  uint tmp_u2;
  long double tmp_l3;
  
  tmp_i1 = Menu_Count();
  if (0 < tmp_i1) {
    tmp_i1 = Menu_GetFocused();
    if (tmp_i1 == 0) {
      tmp_u2 = trap_Key_GetCatcher();
      trap_Key_SetCatcher(tmp_u2 & 0xfffffffd);
      if (bypassKeyClear_10730 == 0) {
        trap_Key_ClearStates();
      }
      if ((GHIDRA_FIELD(cl_bypassMouseInput, 12, 4) != 0) && (tmp_i1 = trap_Key_GetCatcher(), tmp_i1 == 0)) {
        trap_Cvar_Set("cl_bypassMouseInput",0);
      }
      bypassKeyClear_10730 = 0;
      trap_Cvar_Set("cl_paused","0");
    }
    else {
      tmp_l3 = (long double)trap_Cvar_VariableValue("cl_bypassMouseInput");
      if (tmp_l3 != (long double)0) {
        bypassKeyClear_10730 = 1;
      }
      Menu_HandleKey(tmp_i1,param_1,param_2);
    }
  }
  return;
}

uint KeywordHash_Key(char *param_1)

{
{  int tmp_i1;
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
{  int tmp_i1;
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
{  uint32_t *tmp_pu1;
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
