/* Shared background game logic — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_bg.h"

int BG_StringHashValue(char *param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  if (param_1 == (char *)0x0) {
    return -1;
  }
  tmp_i2 = (int)*param_1;
  tmp_i4 = 0;
  tmp_i3 = 0x77;
  if (*param_1 != '\0') {
    do {
      while( true ) {
        tmp_i2 = Q_isupper(tmp_i2);
        if (tmp_i2 != 0) break;
        tmp_i4 = tmp_i4 + param_1[tmp_i3 + -0x77] * tmp_i3;
        tmp_i1 = tmp_i3 + -0x76;
        tmp_i2 = (int)param_1[tmp_i1];
        tmp_i3 = tmp_i3 + 1;
        if (param_1[tmp_i1] == '\0') goto LAB_0001b0c2;
      }
      tmp_i4 = tmp_i4 + (param_1[tmp_i3 + -0x77] + 0x20) * tmp_i3;
      tmp_i1 = tmp_i3 + -0x76;
      tmp_i2 = (int)param_1[tmp_i1];
      tmp_i3 = tmp_i3 + 1;
    } while (param_1[tmp_i1] != '\0');
LAB_0001b0c2:
    if (tmp_i4 != -1) {
      return tmp_i4;
    }
  }
  return 0;
}

int BG_StringHashValue_Lwr(char *param_1)
{
  char tmp_c1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_c1 = *param_1;
  if (tmp_c1 != '\0') {
    tmp_i2 = 0;
    tmp_i3 = 0x77;
    do {
      tmp_i2 = tmp_i2 + tmp_c1 * tmp_i3;
      tmp_c1 = param_1[tmp_i3 + -0x76];
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_c1 != '\0');
    if (tmp_i2 == -1) {
      tmp_i2 = 0;
    }
    return tmp_i2;
  }
  return 0;
}

void BG_AnimParseError(char *param_1)
{
  int tmp_i1;
  char local_40c [1028];
  
  vsnprintf(local_40c,0x400,param_1,&stack0x00000008);
  if (globalFilename != 0) {
    tmp_i1 = COM_GetCurrentParseLine();
    Com_Error(2,"%s: (%s, line %i)",local_40c,globalFilename,tmp_i1 + 1);
    return;
  }
  Com_Error(2,"%s",local_40c);
  return;
}

void BG_ParseCommands_isra_0(int *param_1,int param_2,int param_3)
{
  uint *tmp_pu1;
  short *psVar2;
  char tmp_c3;
  short tmp_s4;
  uint16_t tmp_u5;
  char *tmp_pc6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  size_t tmp_s10;
  long tmp_l11;
  int tmp_i12;
  uint8_t **tmp_ppu13;
  char *tmp_pc14;
  uint8_t *tmp_pu15;
  uint8_t *local_40;
  int local_38;
  uint local_2c;
  
  local_2c = 0;
  local_38 = 0;
  do {
    tmp_pc6 = (char *)COM_ParseExt(param_1,local_2c ^ 1);
    if (tmp_pc6 == (char *)0x0) {
      return;
    }
    if (*tmp_pc6 == '\0') {
      return;
    }
    tmp_i7 = Q_stricmp(tmp_pc6,&g_unk_0010c012);
    if (tmp_i7 == 0) {
      tmp_s10 = strlen(tmp_pc6);
      *param_1 = *param_1 - tmp_s10;
      return;
    }
    if (local_2c == 0) {
      tmp_i7 = *(int *)(param_2 + 0x164);
      if (7 < tmp_i7) {
        BG_AnimParseError("BG_ParseCommands: exceeded maximum number of animations (%i)",8);
        tmp_i7 = *(int *)(param_2 + 0x164);
      }
      *(int *)(param_2 + 0x164) = tmp_i7 + 1;
      tmp_i7 = param_2 + 0x160 + tmp_i7 * 0xe;
      local_38 = tmp_i7 + 8;
      *(uint32_t *)(tmp_i7 + 8) = 0;
      *(uint32_t *)(tmp_i7 + 0xc) = 0;
      *(uint32_t *)(tmp_i7 + 0x10) = 0;
      *(uint16_t *)(tmp_i7 + 0x14) = 0;
    }
    tmp_i7 = (int)*tmp_pc6;
    if (*tmp_pc6 == '\0') {
LAB_0001b6c8:
      local_40 = (uint8_t *)0x0;
    }
    else {
      tmp_i12 = 0x77;
      local_40 = (uint8_t *)0x0;
      tmp_pc14 = tmp_pc6;
      do {
        while( true ) {
          tmp_i7 = Q_isupper(tmp_i7);
          tmp_c3 = *tmp_pc14;
          if (tmp_i7 != 0) break;
          tmp_i7 = tmp_c3 * tmp_i12;
          tmp_pc14 = tmp_pc14 + 1;
          tmp_i12 = tmp_i12 + 1;
          local_40 = local_40 + tmp_i7;
          tmp_i7 = (int)*tmp_pc14;
          if (*tmp_pc14 == '\0') goto LAB_0001b2fe;
        }
        tmp_pc14 = tmp_pc14 + 1;
        tmp_i7 = (tmp_c3 + 0x20) * tmp_i12;
        tmp_i12 = tmp_i12 + 1;
        local_40 = local_40 + tmp_i7;
        tmp_i7 = (int)*tmp_pc14;
      } while (*tmp_pc14 != '\0');
LAB_0001b2fe:
      if (local_40 == (uint8_t *)0xffffffff) goto LAB_0001b6c8;
    }
    if (animBodyPartsStr == (uint8_t *)0x0) {
LAB_0001b5c0:
      *(uint16_t *)(local_38 + local_2c * 2) = 0xffff;
LAB_0001b5ce:
      tmp_s10 = strlen(tmp_pc6);
      *param_1 = *param_1 - tmp_s10;
LAB_0001b5f0:
      while ((tmp_pc6 = (char *)COM_ParseExt(param_1,0), tmp_pc6 != (char *)0x0 && (*tmp_pc6 != '\0')))
      {
        tmp_i7 = Q_stricmp(tmp_pc6,"sound");
        if (tmp_i7 == 0) {
          tmp_pc6 = (char *)COM_ParseExt(param_1,0);
          if ((tmp_pc6 == (char *)0x0) || (*tmp_pc6 == '\0')) {
            BG_AnimParseError("BG_ParseCommands: expected sound");
          }
          tmp_pc14 = strstr(tmp_pc6,".wav");
          if (tmp_pc14 != (char *)0x0) {
            BG_AnimParseError("BG_ParseCommands: wav files not supported, only sound scripts");
          }
          if (*(void **)(cgs + globalScriptData + 0xee8aa0) == (void *)0x0) {
            tmp_u5 = 0;
          }
          else {
            tmp_u5 = (**(void **)(cgs + globalScriptData + 0xee8aa0))(tmp_pc6);
          }
          *(uint16_t *)(local_38 + 0xc) = tmp_u5;
        }
        else {
          BG_AnimParseError("BG_ParseCommands: unknown parameter \'%s\'",tmp_pc6);
        }
      }
      local_2c = 0;
    }
    else {
      tmp_s4 = 0;
      tmp_ppu13 = &animBodyPartsStr;
      tmp_pc14 = animBodyPartsStr;
      while (tmp_ppu13[1] != (uint8_t *)0xffffffff) {
        if (local_40 == tmp_ppu13[1]) goto LAB_0001b3c0;
LAB_0001b33a:
        tmp_ppu13 = tmp_ppu13 + 2;
        tmp_pc14 = *tmp_ppu13;
        tmp_s4 = tmp_s4 + 1;
        if (tmp_pc14 == (char *)0x0) goto LAB_0001b5c0;
      }
      tmp_i7 = (int)*tmp_pc14;
      if (*tmp_pc14 == '\0') {
LAB_0001b5b0:
        tmp_pu15 = (uint8_t *)0x0;
      }
      else {
        tmp_i12 = 0x77;
        tmp_pu15 = (uint8_t *)0x0;
        do {
          while( true ) {
            tmp_i7 = Q_isupper(tmp_i7);
            tmp_c3 = *tmp_pc14;
            if (tmp_i7 != 0) break;
            tmp_i7 = tmp_c3 * tmp_i12;
            tmp_pc14 = tmp_pc14 + 1;
            tmp_i12 = tmp_i12 + 1;
            tmp_pu15 = tmp_pu15 + tmp_i7;
            tmp_i7 = (int)*tmp_pc14;
            if (*tmp_pc14 == '\0') goto LAB_0001b39e;
          }
          tmp_pc14 = tmp_pc14 + 1;
          tmp_i7 = (tmp_c3 + 0x20) * tmp_i12;
          tmp_i12 = tmp_i12 + 1;
          tmp_pu15 = tmp_pu15 + tmp_i7;
          tmp_i7 = (int)*tmp_pc14;
        } while (*tmp_pc14 != '\0');
LAB_0001b39e:
        if (tmp_pu15 == (uint8_t *)0xffffffff) goto LAB_0001b5b0;
      }
      tmp_ppu13[1] = tmp_pu15;
      if (local_40 != tmp_pu15) goto LAB_0001b33a;
LAB_0001b3c0:
      tmp_i7 = Q_stricmp(tmp_pc6,*tmp_ppu13);
      if (tmp_i7 != 0) goto LAB_0001b33a;
      psVar2 = (short *)(local_38 + local_2c * 2);
      *psVar2 = tmp_s4;
      if (tmp_s4 < 1) goto LAB_0001b5ce;
      tmp_pc6 = (char *)COM_ParseExt(param_1,0);
      if (tmp_pc6 == (char *)0x0) {
        tmp_i7 = -1;
        BG_AnimParseError("BG_ParseCommands: expected animation");
        goto LAB_0001b487;
      }
      tmp_c3 = *tmp_pc6;
      if (tmp_c3 == '\0') {
        BG_AnimParseError("BG_ParseCommands: expected animation");
        tmp_c3 = *tmp_pc6;
        if (tmp_c3 == '\0') goto LAB_0001b706;
      }
      tmp_i12 = 0x77;
      tmp_i7 = 0;
      tmp_pc14 = tmp_pc6;
      do {
        tmp_i8 = Q_isupper((int)tmp_c3);
        tmp_i9 = (int)*tmp_pc14;
        if (tmp_i8 == 0) {
          tmp_c3 = tmp_pc14[1];
        }
        else {
          tmp_i9 = tmp_i9 + 0x20;
          tmp_c3 = tmp_pc14[1];
        }
        tmp_i7 = tmp_i7 + tmp_i9 * tmp_i12;
        tmp_i12 = tmp_i12 + 1;
        tmp_pc14 = tmp_pc14 + 1;
      } while (tmp_c3 != '\0');
      if (tmp_i7 == -1) {
LAB_0001b706:
        tmp_i7 = 0;
      }
LAB_0001b487:
      tmp_i9 = 0;
      tmp_i12 = *(int *)(param_3 + 0x89c);
      if (tmp_i12 < 1) {
LAB_0001b4e4:
        tmp_i7 = -1;
        BG_AnimParseError("BG_AnimationIndexForString: unknown index \'%s\' for animation group \'%s\'"
                          ,tmp_pc6,param_3);
      }
      else {
        while( true ) {
          while (tmp_i8 = *(int *)(param_3 + 0x9c + tmp_i9 * 4), *(int *)(tmp_i8 + 100) != tmp_i7) {
            tmp_i9 = tmp_i9 + 1;
            if (tmp_i12 <= tmp_i9) goto LAB_0001b4e4;
          }
          tmp_i12 = Q_stricmp(tmp_pc6,tmp_i8 + 4);
          if (tmp_i12 == 0) break;
          tmp_i12 = *(int *)(param_3 + 0x89c);
          tmp_i9 = tmp_i9 + 1;
          if (tmp_i12 <= tmp_i9) goto LAB_0001b4e4;
        }
        tmp_i7 = (int)(short)tmp_i9;
      }
      psVar2[2] = (short)tmp_i7;
      tmp_i7 = param_3 + tmp_i7 * 4;
      psVar2[4] = (short)*(uint32_t *)(*(int *)(tmp_i7 + 0x9c) + 0x60);
      if ((parseMovetype != 0) && (*psVar2 != 2)) {
        tmp_pu1 = (uint *)(*(int *)(tmp_i7 + 0x9c) + 0x6c);
        *tmp_pu1 = *tmp_pu1 | 1 << ((byte)parseMovetype & 0x1f);
      }
      if ((parseEvent == 0x13) || (parseEvent == 2)) {
        tmp_pu1 = (uint *)(*(int *)(param_3 + 0x9c + psVar2[2] * 4) + 0x68);
        *tmp_pu1 = *tmp_pu1 | 2;
        *(uint32_t *)(*(int *)(param_3 + 0x9c + psVar2[2] * 4) + 0x54) = 0x28;
      }
      tmp_pc6 = (char *)COM_ParseExt(param_1,0);
      if (((tmp_pc6 == (char *)0x0) || (*tmp_pc6 == '\0')) ||
         (tmp_i7 = Q_stricmp(tmp_pc6,"duration"), tmp_i7 != 0)) {
        COM_RestoreParseSession(param_1);
      }
      else {
        tmp_pc6 = (char *)COM_ParseExt(param_1,0);
        if ((tmp_pc6 == (char *)0x0) || (*tmp_pc6 == '\0')) {
          BG_AnimParseError("BG_ParseCommands: expected duration value");
        }
        tmp_l11 = strtol(tmp_pc6,(char **)0x0,10);
        psVar2[4] = (short)tmp_l11;
      }
      if ((*psVar2 == 3) || (local_2c != 0)) goto LAB_0001b5f0;
      local_2c = 1;
    }
  } while( true );
}

int BG_IndexForString_constprop_4(char *param_1,uint32_t *param_2)
{
  char tmp_c1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  char *tmp_pc5;
  int local_2c;
  int local_28;
  
  if (param_1 == (char *)0x0) {
    local_2c = -1;
  }
  else {
    tmp_i2 = (int)*param_1;
    if (*param_1 != '\0') {
      tmp_i3 = 0x77;
      local_2c = 0;
      tmp_pc5 = param_1;
      do {
        while( true ) {
          tmp_i2 = Q_isupper(tmp_i2);
          tmp_c1 = *tmp_pc5;
          if (tmp_i2 != 0) break;
          tmp_i2 = tmp_c1 * tmp_i3;
          tmp_pc5 = tmp_pc5 + 1;
          tmp_i3 = tmp_i3 + 1;
          local_2c = local_2c + tmp_i2;
          tmp_i2 = (int)*tmp_pc5;
          if (*tmp_pc5 == '\0') goto LAB_0001b84e;
        }
        tmp_pc5 = tmp_pc5 + 1;
        tmp_i2 = (tmp_c1 + 0x20) * tmp_i3;
        tmp_i3 = tmp_i3 + 1;
        local_2c = local_2c + tmp_i2;
        tmp_i2 = (int)*tmp_pc5;
      } while (*tmp_pc5 != '\0');
LAB_0001b84e:
      if (local_2c != -1) goto LAB_0001b85f;
    }
    local_2c = 0;
  }
LAB_0001b85f:
  tmp_pc5 = (char *)*param_2;
  local_28 = 0;
  do {
    if (tmp_pc5 == (char *)0x0) {
      BG_AnimParseError("BG_IndexForString: unknown token \'%s\'",param_1);
      return -1;
    }
    tmp_i2 = param_2[1];
    if (tmp_i2 == -1) {
      tmp_i3 = (int)*tmp_pc5;
      if (*tmp_pc5 == '\0') {
LAB_0001b930:
        tmp_i2 = 0;
      }
      else {
        tmp_i4 = 0x77;
        tmp_i2 = 0;
        do {
          while( true ) {
            tmp_i3 = Q_isupper(tmp_i3);
            tmp_c1 = *tmp_pc5;
            if (tmp_i3 != 0) break;
            tmp_i3 = tmp_c1 * tmp_i4;
            tmp_pc5 = tmp_pc5 + 1;
            tmp_i4 = tmp_i4 + 1;
            tmp_i2 = tmp_i2 + tmp_i3;
            tmp_i3 = (int)*tmp_pc5;
            if (*tmp_pc5 == '\0') goto LAB_0001b8ee;
          }
          tmp_pc5 = tmp_pc5 + 1;
          tmp_i3 = (tmp_c1 + 0x20) * tmp_i4;
          tmp_i4 = tmp_i4 + 1;
          tmp_i2 = tmp_i2 + tmp_i3;
          tmp_i3 = (int)*tmp_pc5;
        } while (*tmp_pc5 != '\0');
LAB_0001b8ee:
        if (tmp_i2 == -1) goto LAB_0001b930;
      }
      param_2[1] = tmp_i2;
    }
    if ((local_2c == tmp_i2) && (tmp_i2 = Q_stricmp(param_1,*param_2), tmp_i2 == 0)) {
      return local_28;
    }
    param_2 = param_2 + 2;
    tmp_pc5 = (char *)*param_2;
    local_28 = local_28 + 1;
  } while( true );
}

int BG_AnimationForString(char *param_1,int param_2)
{
  char tmp_c1;
  int tmp_i2;
  int tmp_i3;
  char *tmp_pc4;
  int tmp_i5;
  int local_20;
  
  if (param_1 == (char *)0x0) {
    local_20 = -1;
  }
  else {
    tmp_i3 = (int)*param_1;
    if (*param_1 != '\0') {
      tmp_i5 = 0x77;
      local_20 = 0;
      tmp_pc4 = param_1;
      do {
        while( true ) {
          tmp_i3 = Q_isupper(tmp_i3);
          tmp_c1 = *tmp_pc4;
          if (tmp_i3 != 0) break;
          tmp_i3 = tmp_c1 * tmp_i5;
          tmp_pc4 = tmp_pc4 + 1;
          tmp_i5 = tmp_i5 + 1;
          local_20 = local_20 + tmp_i3;
          tmp_i3 = (int)*tmp_pc4;
          if (*tmp_pc4 == '\0') goto LAB_0001b9fd;
        }
        tmp_pc4 = tmp_pc4 + 1;
        tmp_i3 = (tmp_c1 + 0x20) * tmp_i5;
        tmp_i5 = tmp_i5 + 1;
        local_20 = local_20 + tmp_i3;
        tmp_i3 = (int)*tmp_pc4;
      } while (*tmp_pc4 != '\0');
LAB_0001b9fd:
      if (local_20 != -1) goto LAB_0001ba0c;
    }
    local_20 = 0;
  }
LAB_0001ba0c:
  tmp_i3 = *(int *)(param_2 + 0x89c);
  tmp_i5 = 0;
  if (0 < tmp_i3) {
    do {
      while (tmp_i2 = *(int *)(param_2 + 0x9c + tmp_i5 * 4), *(int *)(tmp_i2 + 100) != local_20) {
        tmp_i5 = tmp_i5 + 1;
        if (tmp_i3 <= tmp_i5) goto LAB_0001ba60;
      }
      tmp_i3 = Q_stricmp(param_1,tmp_i2 + 4);
      if (tmp_i3 == 0) {
        return tmp_i2;
      }
      tmp_i3 = *(int *)(param_2 + 0x89c);
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 < tmp_i3);
  }
LAB_0001ba60:
  Com_Error(2,"BG_AnimationForString: unknown animation \'%s\' for animation group \'%s\'",param_1,
            param_2);
  return 0;
}

int BG_IndexForString(char *param_1,uint32_t *param_2,int param_3)
{
  char tmp_c1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  char *tmp_pc5;
  int local_24;
  int local_20;
  
  if (param_1 == (char *)0x0) {
    local_24 = -1;
  }
  else {
    tmp_i2 = (int)*param_1;
    if (*param_1 != '\0') {
      tmp_i3 = 0x77;
      local_24 = 0;
      tmp_pc5 = param_1;
      do {
        while( true ) {
          tmp_i2 = Q_isupper(tmp_i2);
          tmp_c1 = *tmp_pc5;
          if (tmp_i2 != 0) break;
          tmp_i2 = tmp_c1 * tmp_i3;
          tmp_pc5 = tmp_pc5 + 1;
          tmp_i3 = tmp_i3 + 1;
          local_24 = local_24 + tmp_i2;
          tmp_i2 = (int)*tmp_pc5;
          if (*tmp_pc5 == '\0') goto LAB_0001bb2e;
        }
        tmp_pc5 = tmp_pc5 + 1;
        tmp_i2 = (tmp_c1 + 0x20) * tmp_i3;
        tmp_i3 = tmp_i3 + 1;
        local_24 = local_24 + tmp_i2;
        tmp_i2 = (int)*tmp_pc5;
      } while (*tmp_pc5 != '\0');
LAB_0001bb2e:
      if (local_24 != -1) goto LAB_0001bb3f;
    }
    local_24 = 0;
  }
LAB_0001bb3f:
  tmp_pc5 = (char *)*param_2;
  local_20 = 0;
  do {
    if (tmp_pc5 == (char *)0x0) {
      if (param_3 == 0) {
        BG_AnimParseError("BG_IndexForString: unknown token \'%s\'",param_1);
      }
      return -1;
    }
    tmp_i2 = param_2[1];
    if (tmp_i2 == -1) {
      tmp_i3 = (int)*tmp_pc5;
      if (*tmp_pc5 == '\0') {
LAB_0001bc10:
        tmp_i2 = 0;
      }
      else {
        tmp_i4 = 0x77;
        tmp_i2 = 0;
        do {
          while( true ) {
            tmp_i3 = Q_isupper(tmp_i3);
            tmp_c1 = *tmp_pc5;
            if (tmp_i3 != 0) break;
            tmp_i3 = tmp_c1 * tmp_i4;
            tmp_pc5 = tmp_pc5 + 1;
            tmp_i4 = tmp_i4 + 1;
            tmp_i2 = tmp_i2 + tmp_i3;
            tmp_i3 = (int)*tmp_pc5;
            if (*tmp_pc5 == '\0') goto LAB_0001bbce;
          }
          tmp_pc5 = tmp_pc5 + 1;
          tmp_i3 = (tmp_c1 + 0x20) * tmp_i4;
          tmp_i4 = tmp_i4 + 1;
          tmp_i2 = tmp_i2 + tmp_i3;
          tmp_i3 = (int)*tmp_pc5;
        } while (*tmp_pc5 != '\0');
LAB_0001bbce:
        if (tmp_i2 == -1) goto LAB_0001bc10;
      }
      param_2[1] = tmp_i2;
    }
    if ((local_24 == tmp_i2) && (tmp_i2 = Q_stricmp(param_1,*param_2), tmp_i2 == 0)) {
      return local_20;
    }
    param_2 = param_2 + 2;
    tmp_pc5 = (char *)*param_2;
    local_20 = local_20 + 1;
  } while( true );
}

char * BG_CopyStringIntoBuffer(char *param_1,int param_2,uint param_3,int *param_4)
{
  size_t tmp_s1;
  int tmp_i2;
  
  tmp_i2 = *param_4;
  tmp_s1 = strlen(param_1);
  if (param_3 <= tmp_i2 + 1 + tmp_s1) {
    BG_AnimParseError("BG_CopyStringIntoBuffer: out of buffer space");
    tmp_i2 = *param_4;
  }
  strcpy((char *)(tmp_i2 + param_2),param_1);
  tmp_s1 = strlen(param_1);
  *param_4 = tmp_s1 + 1 + *param_4;
  return (char *)(tmp_i2 + param_2);
}

void BG_InitWeaponStrings(void)
{
  char tmp_c1;
  uint tmp_u2;
  int tmp_i3;
  int tmp_i4;
  int *tmp_pi5;
  char *tmp_pc6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  uint32_t *local_2c;
  
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)&weaponStrings + tmp_u2) = 0;
    *(uint32_t *)((int)&g_unk_00e9a384 + tmp_u2) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x1a0);
  local_2c = &weaponStrings;
  tmp_i4 = 0;
  do {
    tmp_pi5 = (int *)(bg_itemlist + 0x38);
    if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
LAB_0001bd75:
      if ((tmp_pi5[9] != 1) || (tmp_pi5[10] != tmp_i4)) break;
      tmp_pc6 = (char *)tmp_pi5[7];
      *local_2c = tmp_pc6;
      if (tmp_pc6 == (char *)0x0) {
        tmp_i8 = -1;
      }
      else {
        tmp_c1 = *tmp_pc6;
        if (tmp_c1 == '\0') goto LAB_0001be93;
        tmp_i7 = 0x77;
        tmp_i8 = 0;
        do {
          tmp_i9 = Q_isupper((int)tmp_c1);
          tmp_i3 = (int)*tmp_pc6;
          if (tmp_i9 == 0) {
            tmp_c1 = tmp_pc6[1];
          }
          else {
            tmp_i3 = tmp_i3 + 0x20;
            tmp_c1 = tmp_pc6[1];
          }
          tmp_i8 = tmp_i8 + tmp_i3 * tmp_i7;
          tmp_i7 = tmp_i7 + 1;
          tmp_pc6 = tmp_pc6 + 1;
        } while (tmp_c1 != '\0');
        if (tmp_i8 == -1) {
LAB_0001be93:
          tmp_i8 = 0;
        }
      }
      tmp_i7 = *tmp_pi5;
      local_2c[1] = tmp_i8;
      if (tmp_i7 == 0) goto LAB_0001be24;
      goto LAB_0001be06;
    }
LAB_0001be24:
    tmp_i7 = 0;
    *local_2c = "(unknown)";
    tmp_c1 = '(';
    tmp_i8 = 0x77;
    do {
      while( true ) {
        tmp_i9 = (int)tmp_c1;
        tmp_i3 = Q_isupper(tmp_i9);
        if (tmp_i3 != 0) break;
        tmp_i7 = tmp_i7 + tmp_i9 * tmp_i8;
        tmp_c1 = *(char *)(tmp_i8 + 0x10bf9e);
        tmp_i8 = tmp_i8 + 1;
        if (tmp_c1 == '\0') goto LAB_0001be78;
      }
      tmp_i7 = tmp_i7 + (tmp_i9 + 0x20) * tmp_i8;
      tmp_c1 = *(char *)(tmp_i8 + 0x10bf9e);
      tmp_i8 = tmp_i8 + 1;
    } while (tmp_c1 != '\0');
LAB_0001be78:
    if (tmp_i7 == -1) {
      tmp_i7 = 0;
    }
    local_2c[1] = tmp_i7;
LAB_0001be06:
    tmp_i4 = tmp_i4 + 1;
    local_2c = local_2c + 2;
    if (tmp_i4 == 0x34) {
      return;
    }
  } while( true );
  tmp_pi5 = tmp_pi5 + 0xe;
  if (*tmp_pi5 == 0) goto LAB_0001be24;
  goto LAB_0001bd75;
}

void BG_ParseConditionBits(uint32_t param_1,uint32_t param_2,int param_3,uint *param_4)
{
  char tmp_c1;
  bool tmp_b2;
  char *tmp_pc3;
  int tmp_i4;
  uint tmp_u5;
  size_t tmp_s6;
  int tmp_i7;
  uint tmp_u8;
  uint32_t *tmp_pu9;
  int tmp_i10;
  bool tmp_b11;
  bool tmp_b12;
  int local_84;
  uint local_64;
  uint local_60;
  
  local_64 = 0;
  local_60 = 0;
  *param_4 = 0;
  tmp_b2 = false;
LAB_0001bf00:
  do {
    tmp_pc3 = (char *)COM_ParseExt();
    if ((tmp_pc3 == (char *)0x0) || (*tmp_pc3 == '\0')) {
      COM_RestoreParseSession();
      return;
    }
    tmp_i4 = Q_stricmp();
    tmp_b11 = tmp_i4 == 0;
    tmp_i4 = Q_stricmp();
    if (tmp_i4 == 0) {
      COM_BitSet();
      tmp_b12 = tmp_b2;
    }
    else {
      tmp_i4 = Q_stricmp();
      if (tmp_i4 == 0) {
        COM_BitSet();
        return;
      }
      tmp_i4 = Q_stricmp();
      if (tmp_i4 == 0) {
        tmp_pc3 = "MINUS";
        if (!tmp_b11) goto LAB_0001c0fe;
LAB_0001c010:
        tmp_b11 = true;
LAB_0001c01f:
        tmp_i4 = Q_stricmp();
      }
      else {
        if (tmp_b11) goto LAB_0001c010;
LAB_0001c0fe:
        tmp_i4 = Q_stricmp();
        if ((tmp_i4 == 0) || (tmp_i4 = Q_stricmp(), tmp_i4 == 0)) goto LAB_0001c01f;
        tmp_s6 = strlen(tmp_pc3);
        tmp_b12 = tmp_pc3[tmp_s6 - 1] == ',';
        if (tmp_b12) {
          tmp_pc3[tmp_s6 - 1] = '\0';
        }
        tmp_b11 = tmp_b12 || tmp_b11;
        Q_strcat();
        tmp_i4 = Q_stricmp();
      }
      if (((tmp_i4 != 0) && (tmp_i4 = Q_stricmp(), tmp_i4 != 0)) && (!tmp_b11)) goto LAB_0001bf00;
      if (tmp_b11) {
        BG_AnimParseError();
      }
      else {
        tmp_i4 = Q_stricmp();
        if (tmp_i4 == 0) {
          tmp_b2 = true;
          goto LAB_0001bf00;
        }
        BG_AnimParseError();
      }
      tmp_i4 = Q_stricmp();
      if (tmp_i4 == 0) {
        local_64 = 0xffffffff;
        local_60 = 0xffffffff;
      }
      else {
        tmp_pu9 = &defineStr + param_3 * 0x20;
        tmp_pc3 = (char *)*tmp_pu9;
        if (tmp_pc3 != (char *)0x0) {
          local_84 = 0;
          do {
            tmp_i4 = tmp_pu9[1];
            if (tmp_i4 == -1) {
              if (*tmp_pc3 == '\0') {
LAB_0001c370:
                tmp_i4 = 0;
              }
              else {
                tmp_i10 = 0x77;
                tmp_i4 = 0;
                do {
                  while( true ) {
                    tmp_i7 = Q_isupper();
                    tmp_c1 = *tmp_pc3;
                    if (tmp_i7 != 0) break;
                    tmp_i7 = tmp_c1 * tmp_i10;
                    tmp_pc3 = tmp_pc3 + 1;
                    tmp_i10 = tmp_i10 + 1;
                    tmp_i4 = tmp_i4 + tmp_i7;
                    if (*tmp_pc3 == '\0') goto LAB_0001c30e;
                  }
                  tmp_pc3 = tmp_pc3 + 1;
                  tmp_i7 = (tmp_c1 + 0x20) * tmp_i10;
                  tmp_i10 = tmp_i10 + 1;
                  tmp_i4 = tmp_i4 + tmp_i7;
                } while (*tmp_pc3 != '\0');
LAB_0001c30e:
                if (tmp_i4 == -1) goto LAB_0001c370;
              }
              tmp_pu9[1] = tmp_i4;
            }
            if ((tmp_i4 == 0) && (tmp_i4 = Q_stricmp(), tmp_i4 == 0)) {
              local_84 = param_3 * 0x10 + local_84;
              local_64 = (&defineBits)[local_84 * 2];
              local_60 = (&g_unk_0014b404)[local_84 * 2];
              goto LAB_0001c092;
            }
            tmp_pu9 = tmp_pu9 + 2;
            tmp_pc3 = (char *)*tmp_pu9;
            local_84 = local_84 + 1;
          } while (tmp_pc3 != (char *)0x0);
        }
        BG_IndexForString_constprop_4();
        COM_BitSet();
      }
LAB_0001c092:
      if (tmp_b2) {
        tmp_u8 = ~local_64 & *param_4;
        tmp_u5 = ~local_60 & param_4[1];
      }
      else {
        tmp_u8 = local_64 | *param_4;
        tmp_u5 = local_60 | param_4[1];
      }
      param_4[1] = tmp_u5;
      *param_4 = tmp_u8;
      tmp_i4 = Q_stricmp();
      tmp_b12 = true;
      if (tmp_i4 != 0) {
        tmp_b12 = tmp_b2;
      }
    }
    tmp_b2 = tmp_b12;
    if (tmp_b11) {
      return;
    }
  } while( true );
}

uint32_t BG_ParseConditions(uint32_t param_1,int *param_2)
{
  char tmp_c1;
  int tmp_i2;
  size_t tmp_s3;
  int tmp_i4;
  uint8_t **tmp_ppu5;
  char *tmp_pc6;
  uint8_t *tmp_pu7;
  uint8_t *local_44;
  int local_40;
  char *local_3c;
  int local_34;
  int local_24;
  int local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x1c41d;
  local_20 = 0;
  local_24 = 0;
  do {
    local_3c = (char *)COM_ParseExt(param_1,0);
    if ((local_3c == (char *)0x0) || (*local_3c == '\0')) goto LAB_0001c74e;
    tmp_i2 = Q_stricmp(local_3c,"default");
    if (tmp_i2 == 0) {
      return 1;
    }
    tmp_i2 = Q_stricmp(local_3c,&g_unk_0010c02f);
    if ((tmp_i2 == 0) || (tmp_i2 = Q_stricmp(local_3c,"MINUS"), tmp_i2 == 0)) {
      local_3c = (char *)COM_ParseExt(param_1,0);
      if ((local_3c == (char *)0x0) || (tmp_c1 = *local_3c, tmp_c1 == '\0')) {
LAB_0001c74e:
        if (*param_2 == 0) {
          BG_AnimParseError("BG_ParseConditions: no conditions found");
        }
        return 1;
      }
      local_34 = 1;
LAB_0001c4d0:
      tmp_i2 = (int)tmp_c1;
      tmp_i4 = 0x77;
      local_44 = (uint8_t *)0x0;
      tmp_pc6 = local_3c;
      do {
        while( true ) {
          tmp_i2 = Q_isupper(tmp_i2);
          tmp_c1 = *tmp_pc6;
          if (tmp_i2 != 0) break;
          tmp_i2 = tmp_c1 * tmp_i4;
          tmp_pc6 = tmp_pc6 + 1;
          tmp_i4 = tmp_i4 + 1;
          local_44 = local_44 + tmp_i2;
          tmp_i2 = (int)*tmp_pc6;
          if (*tmp_pc6 == '\0') goto LAB_0001c50e;
        }
        tmp_pc6 = tmp_pc6 + 1;
        tmp_i2 = (tmp_c1 + 0x20) * tmp_i4;
        tmp_i4 = tmp_i4 + 1;
        local_44 = local_44 + tmp_i2;
        tmp_i2 = (int)*tmp_pc6;
      } while (*tmp_pc6 != '\0');
LAB_0001c50e:
      if (local_44 == (uint8_t *)0xffffffff) goto LAB_0001c730;
    }
    else {
      local_34 = 0;
      tmp_c1 = *local_3c;
      if (tmp_c1 != '\0') goto LAB_0001c4d0;
LAB_0001c730:
      local_44 = (uint8_t *)0x0;
    }
    if (animConditionsStr != (uint8_t *)0x0) {
      local_40 = 0;
      tmp_ppu5 = &animConditionsStr;
      tmp_pc6 = animConditionsStr;
      do {
        tmp_pu7 = tmp_ppu5[1];
        if (tmp_pu7 == (uint8_t *)0xffffffff) {
          tmp_i2 = (int)*tmp_pc6;
          if (*tmp_pc6 == '\0') {
LAB_0001c698:
            tmp_pu7 = (uint8_t *)0x0;
          }
          else {
            tmp_i4 = 0x77;
            tmp_pu7 = (uint8_t *)0x0;
            do {
              while( true ) {
                tmp_i2 = Q_isupper(tmp_i2);
                tmp_c1 = *tmp_pc6;
                if (tmp_i2 != 0) break;
                tmp_i2 = tmp_c1 * tmp_i4;
                tmp_pc6 = tmp_pc6 + 1;
                tmp_i4 = tmp_i4 + 1;
                tmp_pu7 = tmp_pu7 + tmp_i2;
                tmp_i2 = (int)*tmp_pc6;
                if (*tmp_pc6 == '\0') goto LAB_0001c5ae;
              }
              tmp_pc6 = tmp_pc6 + 1;
              tmp_i2 = (tmp_c1 + 0x20) * tmp_i4;
              tmp_i4 = tmp_i4 + 1;
              tmp_pu7 = tmp_pu7 + tmp_i2;
              tmp_i2 = (int)*tmp_pc6;
            } while (*tmp_pc6 != '\0');
LAB_0001c5ae:
            if (tmp_pu7 == (uint8_t *)0xffffffff) goto LAB_0001c698;
          }
          tmp_ppu5[1] = tmp_pu7;
        }
        if ((local_44 == tmp_pu7) && (tmp_i2 = Q_stricmp(local_3c,*tmp_ppu5), tmp_i2 == 0)) {
          tmp_i2 = *(int *)(animConditionsTable + local_40 * 8);
          goto joined_r0x0001c6c6;
        }
        tmp_ppu5 = tmp_ppu5 + 2;
        tmp_pc6 = *tmp_ppu5;
        local_40 = local_40 + 1;
      } while (tmp_pc6 != (char *)0x0);
    }
    local_40 = -1;
    BG_AnimParseError("BG_IndexForString: unknown token \'%s\'",local_3c);
    tmp_i2 = _DAT_0013b018;
joined_r0x0001c6c6:
    if (tmp_i2 == 0) {
      BG_ParseConditionBits
                (param_1,*(uint32_t *)(animConditionsTable + local_40 * 8 + 4),local_40,&local_24)
      ;
    }
    else if (tmp_i2 == 1) {
      if (*(int *)(animConditionsTable + local_40 * 8 + 4) == 0) {
        local_24 = 1;
      }
      else {
        tmp_pc6 = (char *)COM_ParseExt(param_1,0);
        if ((tmp_pc6 == (char *)0x0) || (*tmp_pc6 == '\0')) {
          BG_AnimParseError("BG_AnimParseAnimScript: expected condition value, found end of line");
        }
        tmp_s3 = strlen(tmp_pc6);
        if (tmp_pc6[tmp_s3 - 1] == ',') {
          tmp_pc6[tmp_s3 - 1] = '\0';
        }
        local_24 = BG_IndexForString_constprop_4();
      }
    }
    tmp_i2 = *param_2;
    param_2[tmp_i2 * 4 + 2] = local_24;
    param_2[tmp_i2 * 4 + 1] = local_40;
    param_2[tmp_i2 * 4 + 3] = local_20;
    param_2[tmp_i2 * 4 + 4] = local_34;
    *param_2 = tmp_i2 + 1;
  } while( true );
}

void BG_AnimParseAnimScript(int param_1,uint32_t param_2,uint32_t param_3,int param_4)
{
  char *tmp_pc1;
  char tmp_c2;
  uint32_t tmp_u3;
  uint tmp_u4;
  char *tmp_pc5;
  uint8_t *tmp_pu6;
  size_t tmp_s7;
  int tmp_i8;
  int *tmp_pi9;
  uint32_t *tmp_pu10;
  int tmp_i11;
  uint tmp_u12;
  int tmp_i13;
  uint8_t **tmp_ppu14;
  int tmp_i15;
  uint8_t *tmp_pu16;
  char *tmp_pc17;
  bool tmp_b18;
  char *tmp_pc19;
  uint local_23c;
  uint local_22c;
  int local_224;
  int *local_220;
  int local_204;
  int local_200 [3];
  char local_1f4 [4];
  uint32_t auStack_1f0 [119];
  uint32_t uStack_14;
  
  uStack_14 = 0x1c793;
  globalScriptData = param_2;
  globalFilename = param_3;
  tmp_pu10 = &defineStr;
  for (tmp_i11 = 0x2c0; tmp_i11 != 0; tmp_i11 = tmp_i11 + -1) {
    *tmp_pu10 = 0;
    tmp_pu10 = tmp_pu10 + 1;
  }
  tmp_pc19 = (char *)0x0;
  memset(defineStrings,0,10000);
  tmp_u4 = 0;
  do {
    *(uint32_t *)((int)&numDefines + tmp_u4) = 0;
    *(uint32_t *)((int)&g_unk_0014f144 + tmp_u4) = 0;
    tmp_u4 = tmp_u4 + 8;
  } while (tmp_u4 < 0x58);
  defineStringsOffset = 0;
  local_200[0] = -1;
  local_200[1] = -1;
  local_200[2] = -1;
  local_204 = param_4;
  COM_BeginParseSession("BG_AnimParseAnimScript");
  local_22c = 0;
  tmp_pc1 = "{";
  local_224 = 0;
  local_220 = (int *)0x0;
LAB_0001c870:
  do {
    tmp_pc5 = (char *)COM_Parse(&local_204);
    if ((tmp_pc5 == (char *)0x0) || (tmp_i11 = (int)*tmp_pc5, *tmp_pc5 == '\0')) {
      if (local_224 != 0) {
        BG_AnimParseError("BG_AnimParseAnimScript: unexpected end of file: %s",tmp_pc19);
      }
      globalFilename = 0;
      return;
    }
    tmp_i13 = 0x77;
    tmp_pu16 = (uint8_t *)0x0;
    tmp_pc17 = tmp_pc5;
    do {
      while( true ) {
        tmp_i11 = Q_isupper(tmp_i11);
        tmp_c2 = *tmp_pc17;
        if (tmp_i11 != 0) break;
        tmp_i11 = tmp_c2 * tmp_i13;
        tmp_pc17 = tmp_pc17 + 1;
        tmp_i13 = tmp_i13 + 1;
        tmp_pu16 = tmp_pu16 + tmp_i11;
        tmp_i11 = (int)*tmp_pc17;
        if (*tmp_pc17 == '\0') goto LAB_0001c8ce;
      }
      tmp_pc17 = tmp_pc17 + 1;
      tmp_i11 = (tmp_c2 + 0x20) * tmp_i13;
      tmp_i13 = tmp_i13 + 1;
      tmp_pu16 = tmp_pu16 + tmp_i11;
      tmp_i11 = (int)*tmp_pc17;
    } while (*tmp_pc17 != '\0');
LAB_0001c8ce:
    tmp_pu6 = (uint8_t *)0x0;
    if (tmp_pu16 != (uint8_t *)0xffffffff) {
      tmp_pu6 = tmp_pu16;
    }
    if (animParseModesStr != (uint8_t *)0x0) {
      local_23c = 0;
      tmp_ppu14 = &animParseModesStr;
      tmp_pc17 = animParseModesStr;
      do {
        tmp_pu16 = tmp_ppu14[1];
        if (tmp_pu16 == (uint8_t *)0xffffffff) {
          tmp_i11 = (int)*tmp_pc17;
          if (*tmp_pc17 == '\0') {
LAB_0001c9e0:
            tmp_pu16 = (uint8_t *)0x0;
          }
          else {
            tmp_i13 = 0x77;
            tmp_pu16 = (uint8_t *)0x0;
            do {
              while( true ) {
                tmp_i11 = Q_isupper(tmp_i11);
                tmp_c2 = *tmp_pc17;
                if (tmp_i11 != 0) break;
                tmp_i11 = tmp_c2 * tmp_i13;
                tmp_pc17 = tmp_pc17 + 1;
                tmp_i13 = tmp_i13 + 1;
                tmp_pu16 = tmp_pu16 + tmp_i11;
                tmp_i11 = (int)*tmp_pc17;
                if (*tmp_pc17 == '\0') goto LAB_0001c96e;
              }
              tmp_pc17 = tmp_pc17 + 1;
              tmp_i11 = (tmp_c2 + 0x20) * tmp_i13;
              tmp_i13 = tmp_i13 + 1;
              tmp_pu16 = tmp_pu16 + tmp_i11;
              tmp_i11 = (int)*tmp_pc17;
            } while (*tmp_pc17 != '\0');
LAB_0001c96e:
            if (tmp_pu16 == (uint8_t *)0xffffffff) goto LAB_0001c9e0;
          }
          tmp_ppu14[1] = tmp_pu16;
        }
        if (tmp_pu16 == tmp_pu6) {
          tmp_pc19 = *tmp_ppu14;
          tmp_i11 = Q_stricmp(tmp_pc5);
          if (tmp_i11 == 0) {
            if (local_224 != 0) {
              BG_AnimParseError("BG_AnimParseAnimScript: unexpected \'%s\'",tmp_pc5);
              tmp_pc19 = tmp_pc5;
            }
            local_22c = local_23c;
            parseMovetype = 0;
            parseEvent = -1;
            goto LAB_0001c870;
          }
        }
        tmp_ppu14 = tmp_ppu14 + 2;
        tmp_pc17 = *tmp_ppu14;
        local_23c = local_23c + 1;
      } while (tmp_pc17 != (char *)0x0);
    }
    if (2 < local_22c) break;
    if (local_22c == 0) {
      tmp_pc19 = "set";
      tmp_i11 = Q_stricmp(tmp_pc5);
      if (tmp_i11 == 0) {
        tmp_pc19 = (char *)COM_ParseExt(&local_204,0);
        if ((tmp_pc19 == (char *)0x0) || (*tmp_pc19 == '\0')) {
          BG_AnimParseError("BG_AnimParseAnimScript: expected condition type string");
        }
        tmp_i11 = BG_IndexForString_constprop_4();
        tmp_pc19 = (char *)COM_ParseExt(&local_204,0);
        if ((tmp_pc19 == (char *)0x0) || (*tmp_pc19 == '\0')) {
          BG_AnimParseError("BG_AnimParseAnimScript: expected condition define string");
        }
        tmp_i15 = defineStringsOffset;
        tmp_i8 = (&numDefines)[tmp_i11];
        tmp_s7 = strlen(tmp_pc19);
        tmp_i13 = tmp_i15 + 1;
        local_23c = tmp_i8;
        if (9999 < tmp_s7 + tmp_i13) {
          BG_AnimParseError("BG_CopyStringIntoBuffer: out of buffer space");
          local_23c = (&numDefines)[tmp_i11];
          tmp_i13 = defineStringsOffset + 1;
          tmp_i15 = defineStringsOffset;
        }
        strcpy(defineStrings + tmp_i15,tmp_pc19);
        tmp_s7 = strlen(tmp_pc19);
        defineStringsOffset = tmp_i13 + tmp_s7;
        (&defineStr)[(tmp_i8 + tmp_i11 * 0x10) * 2] = defineStrings + tmp_i15;
        tmp_pc19 = (char *)(&defineStr)[(tmp_i11 * 0x10 + local_23c) * 2];
        if (tmp_pc19 == (char *)0x0) {
          tmp_i13 = -1;
        }
        else {
          tmp_i8 = (int)*tmp_pc19;
          if (*tmp_pc19 != '\0') {
            tmp_i15 = 0x77;
            tmp_i13 = 0;
            do {
              while( true ) {
                tmp_i8 = Q_isupper(tmp_i8);
                tmp_c2 = *tmp_pc19;
                if (tmp_i8 != 0) break;
                tmp_i8 = tmp_c2 * tmp_i15;
                tmp_pc19 = tmp_pc19 + 1;
                tmp_i15 = tmp_i15 + 1;
                tmp_i13 = tmp_i13 + tmp_i8;
                tmp_i8 = (int)*tmp_pc19;
                if (*tmp_pc19 == '\0') goto LAB_0001cb71;
              }
              tmp_pc19 = tmp_pc19 + 1;
              tmp_i8 = (tmp_c2 + 0x20) * tmp_i15;
              tmp_i15 = tmp_i15 + 1;
              tmp_i13 = tmp_i13 + tmp_i8;
              tmp_i8 = (int)*tmp_pc19;
            } while (*tmp_pc19 != '\0');
LAB_0001cb71:
            if (tmp_i13 != -1) goto LAB_0001cb82;
          }
          tmp_i13 = 0;
        }
LAB_0001cb82:
        (&g_unk_0014bf04)[(tmp_i11 * 0x10 + local_23c) * 2] = tmp_i13;
        tmp_i13 = COM_ParseExt(&local_204,0);
        if (tmp_i13 == 0) {
          BG_AnimParseError("BG_AnimParseAnimScript: expected \'=\', found end of line");
        }
        tmp_i8 = Q_stricmp(tmp_i13,&g_unk_0010c04a);
        if (tmp_i8 != 0) {
          BG_AnimParseError("BG_AnimParseAnimScript: expected \'=\', found \'%s\'",tmp_i13);
        }
        tmp_pc19 = *(char **)(animConditionsTable + tmp_i11 * 8 + 4);
        BG_ParseConditionBits
                  (&local_204,tmp_pc19,tmp_i11,
                   &defineBits + (tmp_i11 * 0x10 + (&numDefines)[tmp_i11]) * 2);
        tmp_u4 = 0;
        (&numDefines)[tmp_i11] = (&numDefines)[tmp_i11] + 1;
        do {
          *(uint32_t *)((int)&g_unk_0014c000 + tmp_u4) = *(uint32_t *)((int)&defineStr + tmp_u4);
          tmp_u4 = tmp_u4 + 4;
        } while (tmp_u4 < 0x80);
        tmp_u4 = 0;
        do {
          *(uint32_t *)((int)&g_unk_0014b500 + tmp_u4) = *(uint32_t *)((int)&defineBits + tmp_u4);
          tmp_u4 = tmp_u4 + 4;
        } while (tmp_u4 < 0x80);
        g_unk_0014f148 = numDefines;
      }
      goto LAB_0001c870;
    }
    tmp_pc19 = tmp_pc1;
    tmp_i11 = Q_stricmp(tmp_pc5);
    if (tmp_i11 == 0) goto LAB_0001cc77;
    tmp_pc19 = "}";
    tmp_i11 = Q_stricmp(tmp_pc5);
    if (tmp_i11 == 0) {
      if (local_224 + -1 < 0) goto LAB_0001d20a;
      tmp_pi9 = (int *)0x0;
      if (local_224 + -1 != 1) {
        tmp_pi9 = local_220;
      }
      goto LAB_0001cd08;
    }
    if (local_224 == 0) {
      if (-1 < local_200[0]) goto LAB_0001cdca;
      tmp_i11 = Q_stricmp(tmp_pc5,"state");
      if (tmp_i11 != 0) {
        BG_AnimParseError("BG_AnimParseAnimScript: expected \'state\'");
      }
      tmp_i11 = COM_ParseExt(&local_204,0);
      if (tmp_i11 == 0) {
        BG_AnimParseError("BG_AnimParseAnimScript: expected state type");
      }
      local_200[0] = BG_IndexForString_constprop_4();
      tmp_pc19 = (char *)0x1;
      tmp_i11 = COM_ParseExt(&local_204);
      if ((tmp_i11 == 0) || (tmp_pc19 = tmp_pc1, tmp_i11 = Q_stricmp(tmp_i11), tmp_i11 != 0)) {
        BG_AnimParseError("BG_AnimParseAnimScript: expected \'{\'",tmp_pc19);
      }
      local_224 = 1;
    }
    else {
      if (local_224 == 1) {
        if (-1 < local_200[1]) goto LAB_0001cdca;
        local_200[1] = BG_IndexForString_constprop_4();
        if (local_22c == 1) {
          tmp_i11 = local_200[1] * 0x204 + 0x8a4 + local_200[0] * 0x2e5c;
          parseMovetype = local_200[1];
        }
        else {
          tmp_i11 = local_200[1] * 0x204 + 0xc214;
        }
        local_220 = (int *)(param_1 + tmp_i11);
        tmp_b18 = ((uint)local_220 & 1) != 0;
        tmp_u4 = 0x204;
        tmp_pi9 = local_220;
        if (tmp_b18) {
          *(uint8_t *)local_220 = 0;
          tmp_pi9 = (int *)((int)local_220 + 1);
          tmp_u4 = 0x203;
        }
        if (((uint)tmp_pi9 & 2) != 0) {
          *(uint16_t *)tmp_pi9 = 0;
          tmp_u4 = tmp_u4 - 2;
          tmp_pi9 = (int *)((int)tmp_pi9 + 2);
        }
        tmp_u12 = 0;
        do {
          *(uint32_t *)((int)tmp_pi9 + tmp_u12) = 0;
          *(uint32_t *)((int)tmp_pi9 + tmp_u12 + 4) = 0;
          tmp_u12 = tmp_u12 + 8;
        } while (tmp_u12 < (tmp_u4 & 0xfffffff8));
        goto LAB_0001ce7e;
      }
      if (local_224 != 2) {
        if (local_224 != 3) goto LAB_0001cdca;
        goto LAB_0001cf66;
      }
      if (-1 < local_200[2]) goto LAB_0001cdca;
      tmp_s7 = strlen(tmp_pc5);
      tmp_i11 = local_204 - tmp_s7;
      local_204 = tmp_i11;
      tmp_s7 = strlen(tmp_pc5);
      tmp_i11 = Q_strncmp(tmp_i11,tmp_pc5,tmp_s7);
      if (tmp_i11 != 0) {
        BG_AnimParseError("BG_AnimParseAnimScript: internal error");
      }
      tmp_pc19 = local_1f4;
      tmp_u4 = 0;
      do {
        tmp_pc5 = tmp_pc19 + tmp_u4;
        tmp_pc5[0] = '\0';
        tmp_pc5[1] = '\0';
        tmp_pc5[2] = '\0';
        tmp_pc5[3] = '\0';
        *(uint32_t *)((int)auStack_1f0 + tmp_u4) = 0;
        tmp_u4 = tmp_u4 + 8;
      } while (tmp_u4 < 0x1d8);
      local_200[2] = BG_ParseConditions(&local_204);
      if (0x7f < *local_220) {
        tmp_pc19 = (char *)0x80;
        BG_AnimParseError("BG_AnimParseAnimScript: exceeded maximum items per script (%i)",0x80);
      }
      tmp_i11 = *(int *)(param_1 + 0xfeae4);
      if (0x7ff < tmp_i11) {
        tmp_pc19 = (char *)0x800;
        BG_AnimParseError("BG_AnimParseAnimScript: exceeded maximum global items (%i)",0x800);
        tmp_i11 = *(int *)(param_1 + 0xfeae4);
      }
      tmp_i13 = *local_220;
      *(int *)(param_1 + 0xfeae4) = tmp_i11 + 1;
      local_220[tmp_i13 + 1] = param_1 + 0x12ae4 + tmp_i11 * 0x1d8;
      tmp_i11 = local_220[*local_220 + 1];
      *local_220 = *local_220 + 1;
      tmp_u4 = 0;
      do {
        tmp_u3 = *(uint32_t *)((int)auStack_1f0 + tmp_u4);
        *(uint32_t *)(tmp_i11 + tmp_u4) = *(uint32_t *)((int)auStack_1f0 + (tmp_u4 - 4));
        *(uint32_t *)(tmp_i11 + 4 + tmp_u4) = tmp_u3;
        tmp_u4 = tmp_u4 + 8;
      } while (tmp_u4 < 0x1d8);
    }
  } while( true );
  if (local_22c == 4) {
    tmp_pc19 = tmp_pc1;
    tmp_i11 = Q_stricmp(tmp_pc5);
    if (tmp_i11 == 0) {
LAB_0001cc77:
      if (local_224 < 3) {
        tmp_i11 = local_200[local_224];
      }
      else {
        tmp_pc19 = tmp_pc5;
        BG_AnimParseError("BG_AnimParseAnimScript: unexpected \'%s\'",tmp_pc5);
        tmp_i11 = local_200[local_224];
      }
      if (tmp_i11 < 0) {
        BG_AnimParseError("BG_AnimParseAnimScript: unexpected \'%s\'",tmp_pc5);
        tmp_pc19 = tmp_pc5;
      }
      local_224 = local_224 + 1;
      goto LAB_0001c870;
    }
    tmp_pc19 = "}";
    tmp_i11 = Q_stricmp(tmp_pc5);
    if (tmp_i11 == 0) {
      if (local_224 + -1 < 0) {
LAB_0001d20a:
        BG_AnimParseError("BG_AnimParseAnimScript: unexpected \'%s\'",tmp_pc5);
        tmp_pc19 = tmp_pc5;
        tmp_pi9 = local_220;
      }
      else {
        tmp_pi9 = (int *)0x0;
        if (local_224 != 1) {
          tmp_pi9 = local_220;
        }
      }
LAB_0001cd08:
      local_220 = tmp_pi9;
      local_224 = local_224 + -1;
      local_200[local_224] = -1;
      goto LAB_0001c870;
    }
    if (local_224 == 0) {
      if (local_200[0] < 0) {
        local_200[0] = BG_IndexForString_constprop_4();
        local_220 = (int *)(local_200[0] * 0x204 + 0xf070 + param_1);
        tmp_b18 = ((uint)local_220 & 1) != 0;
        tmp_u4 = 0x204;
        tmp_pi9 = local_220;
        parseEvent = local_200[0];
        if (tmp_b18) {
          *(uint8_t *)local_220 = 0;
          tmp_pi9 = (int *)((int)local_220 + 1);
          tmp_u4 = 0x203;
        }
        if (((uint)tmp_pi9 & 2) != 0) {
          *(uint16_t *)tmp_pi9 = 0;
          tmp_u4 = tmp_u4 - 2;
          tmp_pi9 = (int *)((int)tmp_pi9 + 2);
        }
        tmp_u12 = 0;
        do {
          *(uint32_t *)((int)tmp_pi9 + tmp_u12) = 0;
          *(uint32_t *)((int)tmp_pi9 + tmp_u12 + 4) = 0;
          tmp_u12 = tmp_u12 + 8;
        } while (tmp_u12 < (tmp_u4 & 0xfffffff8));
LAB_0001ce7e:
        tmp_pu10 = (uint32_t *)((int)tmp_pi9 + tmp_u12);
        if ((tmp_u4 & 4) != 0) {
          *tmp_pu10 = 0;
          tmp_pu10 = tmp_pu10 + 1;
        }
        if ((tmp_u4 & 2) != 0) {
          *(uint16_t *)tmp_pu10 = 0;
          tmp_pu10 = (uint32_t *)((int)tmp_pu10 + 2);
        }
        if (tmp_b18) {
          *(uint8_t *)tmp_pu10 = 0;
        }
        goto LAB_0001c870;
      }
    }
    else if (local_224 == 1) {
      if (local_200[1] < 0) {
        tmp_s7 = strlen(tmp_pc5);
        tmp_i11 = local_204 - tmp_s7;
        local_204 = tmp_i11;
        tmp_s7 = strlen(tmp_pc5);
        tmp_i11 = Q_strncmp(tmp_i11,tmp_pc5,tmp_s7);
        if (tmp_i11 != 0) {
          BG_AnimParseError("BG_AnimParseAnimScript: internal error");
        }
        tmp_pc19 = local_1f4;
        tmp_u4 = 0;
        do {
          tmp_pc5 = tmp_pc19 + tmp_u4;
          tmp_pc5[0] = '\0';
          tmp_pc5[1] = '\0';
          tmp_pc5[2] = '\0';
          tmp_pc5[3] = '\0';
          *(uint32_t *)((int)auStack_1f0 + tmp_u4) = 0;
          tmp_u4 = tmp_u4 + 8;
        } while (tmp_u4 < 0x1d8);
        local_200[1] = BG_ParseConditions(&local_204);
        if (0x7f < *local_220) {
          tmp_pc19 = (char *)0x80;
          BG_AnimParseError("BG_AnimParseAnimScript: exceeded maximum items per script (%i)",0x80);
        }
        tmp_i11 = *(int *)(param_1 + 0xfeae4);
        if (0x7ff < tmp_i11) {
          tmp_pc19 = (char *)0x800;
          BG_AnimParseError("BG_AnimParseAnimScript: exceeded maximum global items (%i)",0x800);
          tmp_i11 = *(int *)(param_1 + 0xfeae4);
        }
        tmp_i13 = *local_220;
        *(int *)(param_1 + 0xfeae4) = tmp_i11 + 1;
        local_220[tmp_i13 + 1] = param_1 + 0x12ae4 + tmp_i11 * 0x1d8;
        tmp_i11 = local_220[*local_220 + 1];
        *local_220 = *local_220 + 1;
        tmp_u4 = 0;
        do {
          tmp_u3 = *(uint32_t *)((int)auStack_1f0 + tmp_u4);
          *(uint32_t *)(tmp_i11 + tmp_u4) = *(uint32_t *)((int)auStack_1f0 + (tmp_u4 - 4));
          *(uint32_t *)(tmp_i11 + 4 + tmp_u4) = tmp_u3;
          tmp_u4 = tmp_u4 + 8;
        } while (tmp_u4 < 0x1d8);
        goto LAB_0001c870;
      }
    }
    else if (local_224 == 2) {
LAB_0001cf66:
      tmp_s7 = strlen(tmp_pc5);
      tmp_i11 = local_204 - tmp_s7;
      local_204 = tmp_i11;
      tmp_s7 = strlen(tmp_pc5);
      tmp_i11 = Q_strncmp(tmp_i11,tmp_pc5,tmp_s7);
      tmp_pc19 = tmp_pc5;
      if (tmp_i11 != 0) {
        BG_AnimParseError("BG_AnimParseAnimScript: internal error");
        tmp_pc19 = tmp_pc5;
      }
      BG_ParseCommands_isra_0(param_1);
      goto LAB_0001c870;
    }
LAB_0001cdca:
    BG_AnimParseError("BG_AnimParseAnimScript: unexpected \'%s\'",tmp_pc5);
    tmp_pc19 = tmp_pc5;
  }
  goto LAB_0001c870;
}

uint32_t BG_EvaluateConditions(int param_1,int *param_2)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  
  tmp_pi3 = param_2 + 1;
  if (0 < *param_2) {
    tmp_i2 = 0;
    do {
      tmp_i1 = *tmp_pi3;
      if (*(int *)(animConditionsTable + tmp_i1 * 8) == 0) {
        tmp_i1 = tmp_i1 + param_1 * 0x16;
        if (((tmp_pi3[1] & *(uint *)(globalScriptData + (tmp_i1 + 0x3faba0) * 8)) != 0) ||
           ((*(uint *)(globalScriptData + 0x1fd5d04 + tmp_i1 * 8) & tmp_pi3[2]) != 0))
        goto LAB_0001d420;
LAB_0001d3c0:
        if (tmp_pi3[3] == 0) {
          return 0;
        }
      }
      else {
        if ((*(int *)(animConditionsTable + tmp_i1 * 8) == 1) &&
           (*(int *)(globalScriptData + (tmp_i1 + 0x3faba0 + param_1 * 0x16) * 8) != tmp_pi3[1]))
        goto LAB_0001d3c0;
LAB_0001d420:
        if (tmp_pi3[3] != 0) {
          return 0;
        }
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pi3 = tmp_pi3 + 4;
    } while (tmp_i2 != *param_2);
  }
  return 1;
}

int * BG_FirstValidItem(int param_1,int *param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  int *tmp_pi3;
  int tmp_i4;
  int local_20;
  
  if (*param_2 < 1) {
    return (int *)0x0;
  }
  local_20 = 0;
LAB_0001d490:
  tmp_pi1 = (int *)param_2[local_20 + 1];
  tmp_pi3 = tmp_pi1 + 1;
  if (*tmp_pi1 < 1) {
    return tmp_pi1;
  }
  tmp_i4 = 0;
  do {
    tmp_i2 = *tmp_pi3;
    if (*(int *)(animConditionsTable + tmp_i2 * 8) == 0) {
      tmp_i2 = tmp_i2 + param_1 * 0x16;
      if ((tmp_pi3[1] & *(uint *)(globalScriptData + (tmp_i2 + 0x3faba0) * 8)) == 0) {
        if ((*(uint *)(globalScriptData + 0x1fd5d04 + tmp_i2 * 8) & tmp_pi3[2]) == 0)
        goto LAB_0001d4d4;
        tmp_i2 = tmp_pi3[3];
      }
      else {
LAB_0001d4f0:
        tmp_i2 = tmp_pi3[3];
      }
      if (tmp_i2 != 0) break;
    }
    else {
      if ((*(int *)(animConditionsTable + tmp_i2 * 8) != 1) ||
         (*(int *)(globalScriptData + (tmp_i2 + 0x3faba0 + param_1 * 0x16) * 8) == tmp_pi3[1]))
      goto LAB_0001d4f0;
LAB_0001d4d4:
      if (tmp_pi3[3] == 0) break;
    }
    tmp_i4 = tmp_i4 + 1;
    tmp_pi3 = tmp_pi3 + 4;
    if (tmp_i4 == *tmp_pi1) {
      return tmp_pi1;
    }
  } while( true );
  local_20 = local_20 + 1;
  if (local_20 == *param_2) {
    return (int *)0x0;
  }
  goto LAB_0001d490;
}

int BG_PlayAnim(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7
               ,int param_8)

{
  bool tmp_b1;
  
  if (param_5 == 0) {
    param_5 = *(int *)(*(int *)(param_2 + 0x9c + param_3 * 4) + 0x60) + 0x32;
  }
  if (param_4 == 2) {
joined_r0x0001d5e6:
    if ((param_8 == 0) && (0x31 < *(int *)(param_1 + 0x5c))) {
      return -1;
    }
    tmp_b1 = false;
  }
  else {
    if ((param_4 != 3) && (param_4 != 1)) {
      return -1;
    }
    if ((param_8 == 0) && (0x31 < *(int *)(param_1 + 0x54))) {
LAB_0001d5ae:
      if (param_4 == 1) {
        return -1;
      }
      goto joined_r0x0001d5e6;
    }
    if ((param_7 != 0) && ((*(uint *)(param_1 + 0x58) & 0xfffffdff) == param_3)) {
      if ((param_6 != 0) && (*(int *)(*(int *)(param_2 + 0x9c + param_3 * 4) + 0x4c) != 0)) {
        *(int *)(param_1 + 0x54) = param_5;
      }
      goto LAB_0001d5ae;
    }
    *(uint *)(param_1 + 0x58) = ~*(uint *)(param_1 + 0x58) & 0x200 | param_3;
    if (param_6 != 0) {
      *(int *)(param_1 + 0x54) = param_5;
    }
    if (param_4 == 1) {
      return param_5;
    }
    if ((param_8 == 0) && (0x31 < *(int *)(param_1 + 0x5c))) {
      return param_5;
    }
    tmp_b1 = true;
  }
  if ((param_7 == 0) || ((*(uint *)(param_1 + 0x60) & 0xfffffdff) != param_3)) {
    *(uint *)(param_1 + 0x60) = param_3 | ~*(uint *)(param_1 + 0x60) & 0x200;
  }
  else {
    if (param_6 == 0) goto LAB_0001d61d;
    param_6 = *(int *)(*(int *)(param_2 + 0x9c + param_3 * 4) + 0x4c);
  }
  if (param_6 != 0) {
    *(int *)(param_1 + 0x5c) = param_5;
  }
LAB_0001d61d:
  if (!tmp_b1) {
    return -1;
  }
  return param_5;
}

void BG_PlayAnimName(uint32_t param_1,int param_2,char *param_3,uint32_t param_4,
                    uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  char tmp_c1;
  int tmp_i2;
  int tmp_i3;
  char *tmp_pc4;
  int tmp_i5;
  int local_20;
  
  if (param_3 == (char *)0x0) {
    local_20 = -1;
  }
  else {
    tmp_i3 = (int)*param_3;
    if (*param_3 != '\0') {
      tmp_i5 = 0x77;
      local_20 = 0;
      tmp_pc4 = param_3;
      do {
        while( true ) {
          tmp_i3 = Q_isupper(tmp_i3);
          tmp_c1 = *tmp_pc4;
          if (tmp_i3 != 0) break;
          tmp_i3 = tmp_c1 * tmp_i5;
          tmp_pc4 = tmp_pc4 + 1;
          tmp_i5 = tmp_i5 + 1;
          local_20 = local_20 + tmp_i3;
          tmp_i3 = (int)*tmp_pc4;
          if (*tmp_pc4 == '\0') goto LAB_0001d76a;
        }
        tmp_pc4 = tmp_pc4 + 1;
        tmp_i3 = (tmp_c1 + 0x20) * tmp_i5;
        tmp_i5 = tmp_i5 + 1;
        local_20 = local_20 + tmp_i3;
        tmp_i3 = (int)*tmp_pc4;
      } while (*tmp_pc4 != '\0');
LAB_0001d76a:
      if (local_20 != -1) goto LAB_0001d779;
    }
    local_20 = 0;
  }
LAB_0001d779:
  tmp_i3 = *(int *)(param_2 + 0x89c);
  tmp_i5 = 0;
  if (0 < tmp_i3) {
    do {
      while (tmp_i2 = *(int *)(param_2 + 0x9c + tmp_i5 * 4), *(int *)(tmp_i2 + 100) != local_20) {
        tmp_i5 = tmp_i5 + 1;
        if (tmp_i3 <= tmp_i5) goto LAB_0001d7d0;
      }
      tmp_i3 = Q_stricmp(param_3,tmp_i2 + 4);
      if (tmp_i3 == 0) goto LAB_0001d7ef;
      tmp_i3 = *(int *)(param_2 + 0x89c);
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 < tmp_i3);
  }
LAB_0001d7d0:
  tmp_i5 = -1;
  BG_AnimParseError("BG_AnimationIndexForString: unknown index \'%s\' for animation group \'%s\'",
                    param_3,param_2);
LAB_0001d7ef:
  BG_PlayAnim(param_1,param_2,tmp_i5,param_4,0,param_5,param_6,param_7);
  return;
}

uint BG_ExecuteCommand(int param_1,int param_2,short *param_3,int param_4,int param_5,int param_6)
{
  short tmp_s1;
  int tmp_i2;
  uint tmp_u3;
  uint tmp_u4;
  uint tmp_u5;
  bool tmp_b6;
  uint local_28;
  
  tmp_u4 = (uint)*param_3;
  if (tmp_u4 == 0) {
    tmp_u4 = 0;
    tmp_u5 = 0xffffffff;
LAB_0001d917:
    tmp_s1 = param_3[1];
  }
  else {
    tmp_u5 = (int)param_3[4] + 0x32;
    if ((tmp_u4 & 0xfffffffd) == 1) {
      tmp_u3 = (uint)param_3[2];
      if (tmp_u5 == 0) {
        local_28 = *(int *)(*(int *)(param_2 + 0x9c + tmp_u3 * 4) + 0x60) + 0x32;
        if (tmp_u4 != 2) goto LAB_0001da30;
LAB_0001d8b1:
        if (param_6 == 0) {
LAB_0001d8bd:
          if (0x31 < *(int *)(param_1 + 0x5c)) goto LAB_0001d8d0;
        }
LAB_0001da60:
        tmp_b6 = false;
LAB_0001da62:
        if ((param_5 == 0) || (tmp_u3 != (*(uint *)(param_1 + 0x60) & 0xfffffdff))) {
          *(uint *)(param_1 + 0x60) = ~*(uint *)(param_1 + 0x60) & 0x200 | tmp_u3;
          tmp_i2 = param_4;
joined_r0x0001da95:
          if (tmp_i2 != 0) {
            *(uint *)(param_1 + 0x5c) = local_28;
          }
        }
        else if (param_4 != 0) {
          tmp_i2 = *(int *)(*(int *)(param_2 + 0x9c + tmp_u3 * 4) + 0x4c);
          goto joined_r0x0001da95;
        }
        if (!tmp_b6) goto LAB_0001d8d0;
      }
      else {
        local_28 = tmp_u5;
        if (tmp_u4 == 2) goto LAB_0001d8b1;
LAB_0001da30:
        tmp_b6 = param_6 != 0;
        if ((!tmp_b6) && (0x31 < *(int *)(param_1 + 0x54))) {
LAB_0001da4b:
          if (tmp_u4 == 1) goto LAB_0001d8d0;
          if (!tmp_b6) goto LAB_0001d8bd;
          goto LAB_0001da60;
        }
        if ((param_5 != 0) && (tmp_u3 == (*(uint *)(param_1 + 0x58) & 0xfffffdff))) {
          if ((param_4 != 0) && (*(int *)(*(int *)(param_2 + 0x9c + tmp_u3 * 4) + 0x4c) != 0)) {
            *(uint *)(param_1 + 0x54) = local_28;
          }
          goto LAB_0001da4b;
        }
        *(uint *)(param_1 + 0x58) = ~*(uint *)(param_1 + 0x58) & 0x200 | tmp_u3;
        if (param_4 != 0) {
          *(uint *)(param_1 + 0x54) = local_28;
        }
        if ((tmp_u4 != 1) && ((tmp_b6 || (*(int *)(param_1 + 0x5c) < 0x32)))) {
          tmp_b6 = true;
          goto LAB_0001da62;
        }
      }
      tmp_u4 = ~local_28 >> 0x1f;
      goto LAB_0001d917;
    }
    BG_PlayAnim(param_1,param_2,(int)param_3[2],tmp_u4,tmp_u5,param_4,param_5,param_6);
LAB_0001d8d0:
    tmp_u4 = 0;
    tmp_s1 = param_3[1];
  }
  tmp_u3 = (uint)tmp_s1;
  if (tmp_u3 != 0) {
    tmp_u5 = (int)param_3[4] + 0x32;
    if ((tmp_u3 & 0xfffffffd) != 1) {
      BG_PlayAnim(param_1,param_2,(int)param_3[3],tmp_u3,tmp_u5,param_4,param_5,param_6);
      tmp_s1 = param_3[6];
      goto joined_r0x0001d9b6;
    }
    tmp_u4 = (uint)param_3[3];
    if (tmp_u5 == 0) {
      local_28 = *(int *)(*(int *)(param_2 + 0x9c + tmp_u4 * 4) + 0x60) + 0x32;
      if (tmp_u3 != 2) goto LAB_0001db00;
LAB_0001d94b:
      if (param_6 == 0) {
LAB_0001d957:
        if (*(int *)(param_1 + 0x5c) < 0x32) goto LAB_0001db30;
      }
      else {
LAB_0001db30:
        tmp_b6 = false;
LAB_0001db32:
        if ((param_5 == 0) || (tmp_u4 != (*(uint *)(param_1 + 0x60) & 0xfffffdff))) {
          *(uint *)(param_1 + 0x60) = ~*(uint *)(param_1 + 0x60) & 0x200 | tmp_u4;
joined_r0x0001db61:
          if (param_4 != 0) {
            *(uint *)(param_1 + 0x5c) = local_28;
          }
        }
        else if (param_4 != 0) {
          param_4 = *(int *)(*(int *)(param_2 + 0x9c + tmp_u4 * 4) + 0x4c);
          goto joined_r0x0001db61;
        }
        if (tmp_b6) goto LAB_0001db6b;
      }
LAB_0001d961:
      tmp_u4 = 0;
    }
    else {
      local_28 = tmp_u5;
      if (tmp_u3 == 2) goto LAB_0001d94b;
LAB_0001db00:
      tmp_b6 = param_6 != 0;
      if ((!tmp_b6) && (0x31 < *(int *)(param_1 + 0x54))) {
LAB_0001db1b:
        if (tmp_u3 == 1) goto LAB_0001d961;
        if (!tmp_b6) goto LAB_0001d957;
        goto LAB_0001db30;
      }
      if ((param_5 != 0) && (tmp_u4 == (*(uint *)(param_1 + 0x58) & 0xfffffdff))) {
        if ((param_4 != 0) && (*(int *)(*(int *)(param_2 + 0x9c + tmp_u4 * 4) + 0x4c) != 0)) {
          *(uint *)(param_1 + 0x54) = local_28;
        }
        goto LAB_0001db1b;
      }
      *(uint *)(param_1 + 0x58) = ~*(uint *)(param_1 + 0x58) & 0x200 | tmp_u4;
      if (param_4 != 0) {
        *(uint *)(param_1 + 0x54) = local_28;
      }
      if ((tmp_u3 != 1) && ((tmp_b6 || (*(int *)(param_1 + 0x5c) < 0x32)))) {
        tmp_b6 = true;
        goto LAB_0001db32;
      }
LAB_0001db6b:
      tmp_u4 = ~local_28 >> 0x1f;
    }
  }
  tmp_s1 = param_3[6];
joined_r0x0001d9b6:
  if (tmp_s1 != 0) {
    (**(void **)(cgs + globalScriptData + 0xee8aa4))
              ((int)tmp_s1,param_1 + 0x14,*(uint32_t *)(param_1 + 0xa0));
  }
  tmp_u3 = 0xffffffff;
  if (tmp_u4 != 0) {
    tmp_u3 = tmp_u5;
  }
  return tmp_u3;
}

uint BG_AnimScriptAnimation(int param_1,int param_2,uint param_3,uint32_t param_4)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  int *tmp_pi6;
  int tmp_i7;
  int tmp_i8;
  int local_34;
  int *local_30;
  
  tmp_i4 = globalScriptData;
  tmp_i7 = *(int *)(param_1 + 0x5a8);
  if (((param_3 != 0x16) && ((*(uint *)(param_1 + 0x68) & 0x800000) != 0)) ||
     (((*(uint *)(param_1 + 0x68) & 1) != 0 &&
      (((param_3 & 0xfffffffb) != 0x11 && (param_3 != 0x16)))))) {
    return 0xffffffff;
  }
  local_30 = (int *)0x0;
joined_r0x0001dda5:
  do {
    if ((3 < tmp_i7) || (local_30 != (int *)0x0)) {
      if (local_30 == (int *)0x0) {
        return 0xffffffff;
      }
      tmp_i7 = *(int *)(param_1 + 0xa0) * 0xb0;
      tmp_pu1 = (uint32_t *)(globalScriptData + 0x1fd5d28 + tmp_i7);
      *tmp_pu1 = 0;
      *(uint32_t *)(tmp_i4 + 0x1fd5d2c + tmp_i7) = 0;
      COM_BitSet(tmp_pu1,param_3);
      tmp_i7 = BG_ExecuteCommand(param_1,param_2,
                                (int)local_30 +
                                (*(int *)(param_1 + 0xa0) % local_30[0x59]) * 0xe + 0x168,0,param_4,
                                0);
      return (uint)(tmp_i7 != -1);
    }
    tmp_i5 = tmp_i7 * 0x2e5c + param_3 * 0x204;
    tmp_i2 = *(int *)(param_2 + 0x8a4 + tmp_i5);
    if (tmp_i2 != 0) {
      if (0 < tmp_i2) {
        local_34 = 0;
LAB_0001de20:
        local_30 = *(int **)(param_2 + 0x8a8 + tmp_i5 + local_34 * 4);
        tmp_pi6 = local_30 + 1;
        if (0 < *local_30) {
          tmp_i8 = 0;
          do {
            tmp_i3 = *tmp_pi6;
            if (*(int *)(animConditionsTable + tmp_i3 * 8) == 0) {
              tmp_i3 = tmp_i3 + *(int *)(param_1 + 0xa0) * 0x16;
              if ((tmp_pi6[1] & *(uint *)(globalScriptData + (tmp_i3 + 0x3faba0) * 8)) == 0) {
                if ((*(uint *)(globalScriptData + 0x1fd5d04 + tmp_i3 * 8) & tmp_pi6[2]) == 0)
                goto LAB_0001de64;
                tmp_i3 = tmp_pi6[3];
              }
              else {
LAB_0001de89:
                tmp_i3 = tmp_pi6[3];
              }
              if (tmp_i3 != 0) goto LAB_0001de90;
            }
            else {
              if ((*(int *)(animConditionsTable + tmp_i3 * 8) != 1) ||
                 (*(int *)(globalScriptData +
                          (tmp_i3 + 0x3faba0 + *(int *)(param_1 + 0xa0) * 0x16) * 8) == tmp_pi6[1]))
              goto LAB_0001de89;
LAB_0001de64:
              if (tmp_pi6[3] == 0) goto LAB_0001de90;
            }
            tmp_i8 = tmp_i8 + 1;
            tmp_pi6 = tmp_pi6 + 4;
            if (tmp_i8 == *local_30) break;
          } while( true );
        }
        goto joined_r0x0001dda5;
      }
    }
LAB_0001dea0:
    tmp_i7 = tmp_i7 + 1;
    local_30 = (int *)0x0;
  } while( true );
LAB_0001de90:
  local_34 = local_34 + 1;
  if (local_34 == tmp_i2) goto LAB_0001dea0;
  goto LAB_0001de20;
}

uint32_t BG_AnimScriptCannedAnimation(int param_1,int param_2)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  int *tmp_pi4;
  int tmp_i5;
  uint32_t tmp_u6;
  int tmp_i7;
  int tmp_i8;
  int local_2c;
  
  if ((*(uint *)(param_1 + 0x68) & 0x800001) == 0) {
    tmp_i5 = *(int *)(param_1 + 0xa0);
    tmp_i1 = *(int *)(globalScriptData + 0x1fd5d28 + tmp_i5 * 0xb0);
    if (tmp_i1 != 0) {
      tmp_i7 = tmp_i1 * 0x204 + 0xc210 + param_2;
      tmp_i1 = *(int *)(tmp_i7 + 4);
      if ((tmp_i1 != 0) && (0 < tmp_i1)) {
        local_2c = 0;
LAB_0001e050:
        tmp_pi2 = *(int **)(tmp_i7 + 8 + local_2c * 4);
        tmp_pi4 = tmp_pi2 + 1;
        if (*tmp_pi2 < 1) {
LAB_0001e108:
          tmp_i5 = rand();
          tmp_u6 = BG_ExecuteCommand(param_1,param_2,
                                    (int)tmp_pi2 + (tmp_i5 % tmp_pi2[0x59]) * 0xe + 0x168,1,0,0);
          return tmp_u6;
        }
        tmp_i8 = 0;
        do {
          tmp_i3 = *tmp_pi4;
          if (*(int *)(animConditionsTable + tmp_i3 * 8) == 0) {
            tmp_i3 = tmp_i3 + tmp_i5 * 0x16;
            if ((tmp_pi4[1] & *(uint *)(globalScriptData + (tmp_i3 + 0x3faba0) * 8)) == 0) {
              if ((*(uint *)(globalScriptData + 0x1fd5d04 + tmp_i3 * 8) & tmp_pi4[2]) == 0)
              goto LAB_0001e094;
              tmp_i3 = tmp_pi4[3];
            }
            else {
LAB_0001e0b1:
              tmp_i3 = tmp_pi4[3];
            }
            if (tmp_i3 != 0) goto LAB_0001e0b8;
          }
          else {
            if ((*(int *)(animConditionsTable + tmp_i3 * 8) != 1) ||
               (*(int *)(globalScriptData + (tmp_i3 + 0x3faba0 + tmp_i5 * 0x16) * 8) == tmp_pi4[1]))
            goto LAB_0001e0b1;
LAB_0001e094:
            if (tmp_pi4[3] == 0) goto LAB_0001e0b8;
          }
          tmp_i8 = tmp_i8 + 1;
          tmp_pi4 = tmp_pi4 + 4;
          if (tmp_i8 == *tmp_pi2) goto LAB_0001e108;
        } while( true );
      }
    }
  }
  return 0xffffffff;
LAB_0001e0b8:
  local_2c = local_2c + 1;
  if (local_2c == tmp_i1) {
    return 0xffffffff;
  }
  goto LAB_0001e050;
}

uint32_t BG_AnimScriptEvent(int param_1,int param_2,int param_3,uint32_t param_4,uint32_t param_5)
{
  int *tmp_pi1;
  int tmp_i2;
  int *tmp_pi3;
  int tmp_i4;
  uint32_t tmp_u5;
  int *tmp_pi6;
  int tmp_i7;
  int local_2c;
  
  if (((param_3 == 0x19) || (param_3 == 1)) || ((*(uint *)(param_1 + 0x68) & 0x800001) == 0)) {
    tmp_pi6 = (int *)(param_3 * 0x204 + 0xf070 + param_2);
    tmp_i4 = *tmp_pi6;
    if ((tmp_i4 != 0) && (0 < tmp_i4)) {
      local_2c = 0;
LAB_0001e1f0:
      tmp_pi1 = (int *)tmp_pi6[local_2c + 1];
      tmp_pi3 = tmp_pi1 + 1;
      if (*tmp_pi1 < 1) {
LAB_0001e2a8:
        tmp_i4 = rand();
        tmp_u5 = BG_ExecuteCommand(param_1,param_2,(int)tmp_pi1 + (tmp_i4 % tmp_pi1[0x59]) * 0xe + 0x168
                                  ,1,param_4,param_5);
        return tmp_u5;
      }
      tmp_i7 = 0;
      do {
        tmp_i2 = *tmp_pi3;
        if (*(int *)(animConditionsTable + tmp_i2 * 8) == 0) {
          tmp_i2 = tmp_i2 + *(int *)(param_1 + 0xa0) * 0x16;
          if ((tmp_pi3[1] & *(uint *)(globalScriptData + (tmp_i2 + 0x3faba0) * 8)) == 0) {
            if ((*(uint *)(globalScriptData + 0x1fd5d04 + tmp_i2 * 8) & tmp_pi3[2]) == 0)
            goto LAB_0001e234;
            tmp_i2 = tmp_pi3[3];
          }
          else {
LAB_0001e251:
            tmp_i2 = tmp_pi3[3];
          }
          if (tmp_i2 != 0) goto LAB_0001e258;
        }
        else {
          if ((*(int *)(animConditionsTable + tmp_i2 * 8) != 1) ||
             (*(int *)(globalScriptData + (tmp_i2 + 0x3faba0 + *(int *)(param_1 + 0xa0) * 0x16) * 8)
              == tmp_pi3[1])) goto LAB_0001e251;
LAB_0001e234:
          if (tmp_pi3[3] == 0) goto LAB_0001e258;
        }
        tmp_i7 = tmp_i7 + 1;
        tmp_pi3 = tmp_pi3 + 4;
        if (tmp_i7 == *tmp_pi1) goto LAB_0001e2a8;
      } while( true );
    }
  }
  return 0xffffffff;
LAB_0001e258:
  local_2c = local_2c + 1;
  if (local_2c == tmp_i4) {
    return 0xffffffff;
  }
  goto LAB_0001e1f0;
}

int BG_GetAnimString(int param_1,int param_2)
{
  if (*(int *)(param_1 + 0x89c) <= param_2) {
    BG_AnimParseError("BG_GetAnimString: anim index is out of range");
  }
  return *(int *)(param_1 + 0x9c + param_2 * 4) + 4;
}

void BG_UpdateConditionValue(int param_1,int param_2,uint32_t param_3,int param_4)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = globalScriptData;
  if ((param_4 == 1) && (*(int *)(animConditionsTable + param_2 * 8) == 0)) {
    param_2 = param_2 + param_1 * 0x16;
    tmp_i1 = param_2 + 0x3faba0;
    *(uint32_t *)(globalScriptData + tmp_i1 * 8) = 0;
    *(uint32_t *)(tmp_i2 + 0x1fd5d04 + param_2 * 8) = 0;
    COM_BitSet(tmp_i2 + tmp_i1 * 8,param_3);
  }
  else {
    *(uint32_t *)(globalScriptData + (param_2 + 0x3faba0 + param_1 * 0x16) * 8) = param_3;
  }
  return;
}

int BG_GetConditionValue(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  
  if (*(int *)(animConditionsTable + param_2 * 8) == 0) {
    if (param_3 == 0) {
      return globalScriptData + (param_2 + 0x3faba0 + param_1 * 0x16) * 8;
    }
    tmp_i2 = 0;
    do {
      tmp_i1 = COM_BitCheck(globalScriptData + (param_2 + 0x3faba0 + param_1 * 0x16) * 8,tmp_i2);
      if (tmp_i1 != 0) {
        return tmp_i2;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_i1 = 0;
    } while (tmp_i2 != 0x40);
  }
  else {
    tmp_i1 = *(int *)(globalScriptData + (param_2 + 0x3faba0 + param_1 * 0x16) * 8);
  }
  return tmp_i1;
}

uint32_t BG_GetConditionBitFlag(int param_1,int param_2,uint32_t param_3)
{
  uint32_t tmp_u1;
  
  if (*(int *)(animConditionsTable + param_2 * 8) != 0) {
    Com_Error(2,"BG_GetConditionBitFlag: animation condition %i is not a bitflag condition",
              *(int *)(animConditionsTable + param_2 * 8));
    return 0;
  }
  tmp_u1 = COM_BitCheck(globalScriptData + (param_2 + 0x3faba0 + param_1 * 0x16) * 8,param_3);
  return tmp_u1;
}

void BG_SetConditionBitFlag(int param_1,int param_2,uint32_t param_3)
{
  COM_BitSet(globalScriptData + (param_2 + 0x3faba0 + param_1 * 0x16) * 8,param_3);
  return;
}

void BG_ClearConditionBitFlag(int param_1,int param_2,uint32_t param_3)
{
  COM_BitClear(globalScriptData + (param_2 + 0x3faba0 + param_1 * 0x16) * 8,param_3);
  return;
}

int BG_GetAnimScriptAnimation(int param_1,int param_2,int param_3,int param_4)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  int tmp_i4;
  int tmp_i5;
  int local_24;
  int *local_20;
  
  local_20 = (int *)0x0;
joined_r0x0001e615:
  do {
    if ((3 < param_3) || (local_20 != (int *)0x0)) {
      if ((local_20 == (int *)0x0) ||
         (tmp_i4 = (param_1 % local_20[0x59]) * 0xe, *(short *)((int)local_20 + tmp_i4 + 0x168) == 0))
      {
        tmp_i4 = -1;
      }
      else {
        tmp_i4 = (int)*(short *)((int)local_20 + tmp_i4 + 0x16c);
      }
      return tmp_i4;
    }
    tmp_i2 = param_3 * 0x2e5c + param_4 * 0x204;
    tmp_i4 = *(int *)(param_2 + 0x8a4 + tmp_i2);
    if ((tmp_i4 != 0) && (0 < tmp_i4)) {
      local_24 = 0;
LAB_0001e680:
      local_20 = *(int **)(param_2 + 0x8a8 + tmp_i2 + local_24 * 4);
      tmp_pi3 = local_20 + 1;
      if (0 < *local_20) {
        tmp_i5 = 0;
        do {
          tmp_i1 = *tmp_pi3;
          if (*(int *)(animConditionsTable + tmp_i1 * 8) == 0) {
            tmp_i1 = tmp_i1 + param_1 * 0x16;
            if ((tmp_pi3[1] & *(uint *)(globalScriptData + (tmp_i1 + 0x3faba0) * 8)) == 0) {
              if ((*(uint *)(globalScriptData + 0x1fd5d04 + tmp_i1 * 8) & tmp_pi3[2]) == 0)
              goto LAB_0001e6c4;
              tmp_i1 = tmp_pi3[3];
            }
            else {
LAB_0001e6e4:
              tmp_i1 = tmp_pi3[3];
            }
            if (tmp_i1 != 0) goto LAB_0001e6eb;
          }
          else {
            if ((*(int *)(animConditionsTable + tmp_i1 * 8) != 1) ||
               (*(int *)(globalScriptData + (tmp_i1 + 0x3faba0 + param_1 * 0x16) * 8) == tmp_pi3[1]))
            goto LAB_0001e6e4;
LAB_0001e6c4:
            if (tmp_pi3[3] == 0) goto LAB_0001e6eb;
          }
          tmp_i5 = tmp_i5 + 1;
          tmp_pi3 = tmp_pi3 + 4;
          if (tmp_i5 == *local_20) break;
        } while( true );
      }
      goto joined_r0x0001e615;
    }
LAB_0001e6fb:
    param_3 = param_3 + 1;
    local_20 = (int *)0x0;
  } while( true );
LAB_0001e6eb:
  local_24 = local_24 + 1;
  if (local_24 == tmp_i4) goto LAB_0001e6fb;
  goto LAB_0001e680;
}

uint32_t BG_GetAnimationForIndex(int param_1,int param_2)
{
  if ((param_2 < 0) || (*(int *)(param_1 + 0x89c) <= param_2)) {
    Com_Error(2,"BG_GetAnimationForIndex: index out of bounds");
  }
  return *(uint32_t *)(param_1 + 0x9c + param_2 * 4);
}

void BG_AnimUpdatePlayerStateConditions(int *param_1)
{
  uint32_t *tmp_pu1;
  int *tmp_pi2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint tmp_u7;
  
  tmp_i5 = globalScriptData;
  tmp_i3 = *param_1;
  if ((*(byte *)(tmp_i3 + 0x6a) & 4) == 0) {
    tmp_u4 = *(uint32_t *)(tmp_i3 + 0xa4);
    tmp_i6 = *(int *)(tmp_i3 + 0xa0) * 0xb0;
    tmp_pu1 = (uint32_t *)(globalScriptData + 0x1fd5d00 + tmp_i6);
    *tmp_pu1 = 0;
    *(uint32_t *)(tmp_i5 + 0x1fd5d04 + tmp_i6) = 0;
    COM_BitSet(tmp_pu1,tmp_u4);
    COM_BitClear(globalScriptData + 0x1fd5d98 + *(int *)(tmp_i3 + 0xa0) * 0xb0,0);
  }
  else {
    tmp_i6 = *(int *)(tmp_i3 + 0xa0) * 0xb0;
    tmp_pu1 = (uint32_t *)(globalScriptData + 0x1fd5d00 + tmp_i6);
    *tmp_pu1 = 0;
    *(uint32_t *)(tmp_i5 + 0x1fd5d04 + tmp_i6) = 0;
    COM_BitSet(tmp_pu1,0x13);
    COM_BitSet(globalScriptData + 0x1fd5d98 + *(int *)(tmp_i3 + 0xa0) * 0xb0,0);
  }
  tmp_i5 = globalScriptData;
  *(uint32_t *)(globalScriptData + 0x1fd5d80 + *(int *)(tmp_i3 + 0xa0) * 0xb0) =
       *(uint32_t *)(tmp_i3 + 0xe4);
  if (*(int *)(tmp_i3 + 0xd0) < 0x42) {
    if (*(int *)(tmp_i3 + 0xd0) < 0x21) {
      *(uint32_t *)(tmp_i5 + 0x1fd5d88 + *(int *)(tmp_i3 + 0xa0) * 0xb0) = 1;
    }
    else {
      *(uint32_t *)(tmp_i5 + 0x1fd5d88 + *(int *)(tmp_i3 + 0xa0) * 0xb0) = 2;
    }
  }
  else {
    *(uint32_t *)(tmp_i5 + 0x1fd5d88 + *(int *)(tmp_i3 + 0xa0) * 0xb0) = 3;
  }
  if ((*(uint *)(tmp_i3 + 0x68) & 0x8020) == 0) {
    *(uint32_t *)(tmp_i5 + 0x1fd5d20 + *(int *)(tmp_i3 + 0xa0) * 0xb0) = 0;
  }
  else {
    *(uint32_t *)(tmp_i5 + 0x1fd5d20 + *(int *)(tmp_i3 + 0xa0) * 0xb0) = 1;
  }
  *(uint *)(tmp_i5 + 0x1fd5d30 + *(int *)(tmp_i3 + 0xa0) * 0xb0) =
       (uint)(0.0 < *(float *)(tmp_i3 + 0xb0));
  if ((float)*(int *)(tmp_i3 + 0xbc) == *(float *)(tmp_i3 + 0x3f8)) {
    tmp_u7 = *(uint *)(tmp_i3 + 0x68) | 0x10;
  }
  else {
    tmp_u7 = *(uint *)(tmp_i3 + 0x68) & 0xffffffef;
  }
  *(uint *)(tmp_i3 + 0x68) = tmp_u7;
  if ((*(byte *)(param_1 + 4) & 1) == 0) {
    *(uint32_t *)(tmp_i5 + 0x1fd5d58 + *(int *)(tmp_i3 + 0xa0) * 0xb0) = 0;
  }
  else {
    *(uint32_t *)(tmp_i5 + 0x1fd5d58 + *(int *)(tmp_i3 + 0xa0) * 0xb0) = 1;
  }
  if ((*(byte *)(tmp_i3 + 0xd) & 8) != 0) {
    if (*(int *)(tmp_i3 + 0x50) == 0x3ff) {
      *(uint32_t *)(tmp_i5 + 0x1fd5d90 + *(int *)(tmp_i3 + 0xa0) * 0xb0) = 1;
      *(uint32_t *)(tmp_i3 + 0x10) = 0x2ee;
    }
    else {
      tmp_pi2 = (int *)(tmp_i5 + 0x1fd5d90 + *(int *)(tmp_i3 + 0xa0) * 0xb0);
      if (*tmp_pi2 != 2) {
        *tmp_pi2 = 2;
        *(uint32_t *)(tmp_i3 + 0x10) = 0x2ee;
      }
    }
  }
  return;
}

uint32_t BG_RAG_ParseError(uint32_t param_1,char *param_2)
{
  uint32_t local_a0;
  uint8_t local_9c [140];
  
  vsnprintf(string_6901,0x1000,param_2,&stack0x0000000c);
  local_a0 = 0;
  local_9c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_9c,&local_a0);
  Com_Printf("^1ERROR: %s, line %d: %s\n",local_9c,local_a0,string_6901);
  trap_PC_FreeSource(param_1);
  return 0;
}

void BG_ClearAnimationPool(void)
{
  memset(&animationPool,0,0x46000);
  return;
}

uint32_t BG_R_RegisterAnimationGroup(uint32_t param_1,int param_2)
{
  int *__haystack;
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  char *tmp_pc6;
  uint8_t *tmp_pu7;
  int *tmp_pi8;
  int local_850;
  uint8_t local_84c [16];
  char local_83c [1032];
  uint8_t local_434 [16];
  char local_424 [1044];
  
  *(uint32_t *)(param_2 + 0x89c) = 0;
  *(uint32_t *)(param_2 + 0x84) = 0;
  *(uint32_t *)(param_2 + 0x80) = 0;
  *(uint32_t *)(param_2 + 0x98) = 1;
  *(uint32_t *)(param_2 + 0x94) = 3;
  *(uint32_t *)(param_2 + 0x8a0) = 0;
  tmp_i1 = trap_PC_LoadSource(param_1);
  if (tmp_i1 == 0) {
    return 0;
  }
  tmp_i2 = trap_PC_ReadToken(tmp_i1,local_84c);
  if (tmp_i2 != 0) {
    tmp_i2 = Q_stricmp(local_83c,"animgroup");
    if (tmp_i2 == 0) {
      tmp_i2 = trap_PC_ReadToken(tmp_i1,local_84c);
      if ((tmp_i2 == 0) || (tmp_i2 = Q_stricmp(local_83c,"{"), tmp_i2 != 0)) {
        tmp_u3 = BG_RAG_ParseError(tmp_i1,"expected \'{\'");
        return tmp_u3;
      }
LAB_0001ed20:
      do {
        tmp_i2 = trap_PC_ReadToken(tmp_i1,local_84c);
        if ((tmp_i2 == 0) || (local_83c[0] == '}')) {
          trap_PC_FreeSource(tmp_i1);
          return 1;
        }
        tmp_i2 = Q_stricmp(local_83c,"animfile");
        if (tmp_i2 != 0) {
          tmp_u3 = BG_RAG_ParseError(tmp_i1,"unknown token \'%s\'",local_83c);
          return tmp_u3;
        }
        tmp_i2 = trap_PC_ReadToken(tmp_i1,local_434);
        if (tmp_i2 == 0) {
          tmp_i2 = BG_RAG_ParseError(tmp_i1,"expected mdx filename");
        }
        else {
          tmp_i2 = trap_R_RegisterModel(local_424);
          if (tmp_i2 == 0) {
            tmp_i2 = BG_RAG_ParseError(tmp_i1,"failed to load %s",local_424);
          }
          else {
            tmp_i4 = trap_PC_ReadToken(tmp_i1,local_434);
            if ((tmp_i4 == 0) || (tmp_i4 = Q_stricmp(local_424,"{"), tmp_i4 != 0)) {
              tmp_i2 = BG_RAG_ParseError(tmp_i1,"expected \'{\'");
            }
            else {
              while (tmp_i4 = trap_PC_ReadToken(tmp_i1,local_434), tmp_i4 != 0) {
                if (local_424[0] == '}') goto LAB_0001ed20;
                tmp_i4 = 0;
                tmp_pu7 = &g_unk_001501a4;
                do {
                  if ((tmp_i2 == *(int *)(tmp_pu7 + -4)) &&
                     (tmp_i5 = Q_stricmp(tmp_pu7,local_424), tmp_i5 == 0)) {
                    tmp_pi8 = &animationPool + tmp_i4 * 0x1c;
                    goto LAB_0001ee7e;
                  }
                  tmp_pu7 = tmp_pu7 + 0x70;
                  tmp_i4 = tmp_i4 + 1;
                } while (tmp_pu7 != (uint8_t *)0x1961a4);
                tmp_pi8 = &animationPool;
                tmp_i4 = 0;
                while (*tmp_pi8 != 0) {
                  tmp_i4 = tmp_i4 + 1;
                  tmp_pi8 = tmp_pi8 + 0x1c;
                  if (tmp_i4 == 0xa00) {
                    tmp_i2 = BG_RAG_ParseError(tmp_i1,"out of animation storage space");
                    goto LAB_0001f0f6;
                  }
                }
                tmp_pi8 = &animationPool + tmp_i4 * 0x1c;
                *tmp_pi8 = tmp_i2;
                Q_strncpyz(&g_unk_001501a4 + tmp_i4 * 0x70,local_424,0x40);
LAB_0001ee7e:
                __haystack = tmp_pi8 + 1;
                Q_strncpyz(__haystack,local_424,0x40);
                Q_strlwr(__haystack);
                tmp_pi8[0x1a] = 0;
                tmp_i4 = PC_Int_Parse(tmp_i1,tmp_pi8 + 0x11);
                if (tmp_i4 == 0) {
                  tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected first frame integer");
LAB_0001f0d3:
                  if (tmp_i4 == 0) {
                    return 0;
                  }
                }
                else {
                  tmp_i4 = PC_Int_Parse(tmp_i1,tmp_pi8 + 0x12);
                  if (tmp_i4 == 0) {
                    tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected length integer");
                    goto LAB_0001f0d3;
                  }
                  tmp_i4 = PC_Int_Parse(tmp_i1,tmp_pi8 + 0x13);
                  if (tmp_i4 == 0) {
                    tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected looping integer");
                    goto LAB_0001f0d3;
                  }
                  tmp_i4 = PC_Int_Parse(tmp_i1,&local_850);
                  if (tmp_i4 == 0) {
                    tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected fps integer");
                    goto LAB_0001f0d3;
                  }
                  if (local_850 == 0) {
                    local_850 = 1;
                    tmp_i4 = 1000;
                  }
                  else {
                    tmp_i4 = (int)ROUND(1000.0 / (float)local_850);
                  }
                  tmp_pi8[0x14] = tmp_i4;
                  tmp_pi8[0x15] = tmp_i4;
                  tmp_i4 = PC_Int_Parse(tmp_i1,tmp_pi8 + 0x16);
                  if (tmp_i4 == 0) {
                    tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected move speed integer");
                    goto LAB_0001f0d3;
                  }
                  tmp_i4 = PC_Int_Parse(tmp_i1,tmp_pi8 + 0x17);
                  if (tmp_i4 == 0) {
                    tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected transition integer");
                    goto LAB_0001f0d3;
                  }
                  tmp_i4 = PC_Int_Parse(tmp_i1,&local_850);
                  if (tmp_i4 == 0) {
                    tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected reversed integer");
                    goto LAB_0001f0d3;
                  }
                  if (local_850 == 1) {
                    tmp_pi8[0x1a] = tmp_pi8[0x1a] | 4;
                  }
                  tmp_pi8[0x18] = tmp_pi8[0x14] * tmp_pi8[0x12] + tmp_pi8[0x15] + tmp_pi8[0x17];
                  tmp_i4 = BG_StringHashValue(__haystack);
                  tmp_pi8[0x19] = tmp_i4;
                  tmp_i4 = Q_strncmp(__haystack,"climb",5);
                  if (tmp_i4 == 0) {
                    tmp_pi8[0x1a] = tmp_pi8[0x1a] | 1;
                  }
                  tmp_pc6 = strstr((char *)__haystack,"firing");
                  if (tmp_pc6 != (char *)0x0) {
                    tmp_pi8[0x1a] = tmp_pi8[0x1a] | 2;
                    tmp_pi8[0x15] = 0x28;
                  }
                }
                tmp_i4 = *(int *)(param_2 + 0x89c);
                *(int **)(param_2 + 0x9c + tmp_i4 * 4) = tmp_pi8;
                *(int *)(param_2 + 0x89c) = tmp_i4 + 1;
              }
              tmp_i2 = BG_RAG_ParseError(tmp_i1,"unexpected EOF");
            }
          }
        }
LAB_0001f0f6:
        if (tmp_i2 == 0) {
          return 0;
        }
      } while( true );
    }
  }
  tmp_u3 = BG_RAG_ParseError(tmp_i1,"expected \'animgroup\'");
  return tmp_u3;
}

uint32_t BG_LoadCampaignSave(uint32_t param_1,int *param_2,char *param_3)
{
  char tmp_c1;
  int tmp_i2;
  __int32_t **pp_Var3;
  int tmp_i4;
  int *tmp_pi5;
  char *tmp_pc6;
  int *tmp_pi7;
  int local_30;
  uint32_t local_20 [4];
  
  memset(param_2,0,0x6010);
  tmp_i2 = trap_FS_FOpenFile(param_1,local_20,0);
  if (tmp_i2 < 0) {
    return 0;
  }
  trap_FS_Read(param_2,4,local_20[0]);
  if (*param_2 != 0x53504349) {
    trap_FS_FCloseFile(local_20[0]);
    Com_Printf("^1ERROR: BG_LoadCampaignSave: not a campaignsave\n");
    return 0;
  }
  trap_FS_Read(param_2 + 1,1,local_20[0]);
  trap_FS_Read(param_2 + 2,4,local_20[0]);
  trap_FS_Read(param_2 + 3,4,local_20[0]);
  tmp_c1 = *param_3;
  if (tmp_c1 == '\0') {
    tmp_i2 = 0;
  }
  else {
    pp_Var3 = __ctype_tolower_loc();
    tmp_i2 = 0;
    tmp_pc6 = param_3;
    do {
      tmp_i4 = (int)tmp_c1;
      tmp_c1 = tmp_pc6[1];
      tmp_i2 = tmp_i2 + (int)(tmp_pc6 + (0x77 - (int)param_3)) * (*pp_Var3)[tmp_i4];
      tmp_pc6 = tmp_pc6 + 1;
    } while (tmp_c1 != '\0');
  }
  if (param_2[3] == tmp_i2) {
    if (0 < param_2[2]) {
      tmp_pi7 = param_2 + 5;
      local_30 = 0;
      do {
        tmp_i2 = 0;
        trap_FS_Read(tmp_pi7 + -1,4,local_20[0]);
        trap_FS_Read(tmp_pi7,4,local_20[0]);
        tmp_pi5 = tmp_pi7;
        if (0 < *tmp_pi7) {
          do {
            tmp_pi5 = tmp_pi5 + 1;
            tmp_i2 = tmp_i2 + 1;
            trap_FS_Read(tmp_pi5,4,local_20[0]);
          } while (tmp_i2 < *tmp_pi7);
        }
        local_30 = local_30 + 1;
        tmp_pi7 = tmp_pi7 + 0xc;
      } while (local_30 < param_2[2]);
    }
    trap_FS_FCloseFile(local_20[0]);
    return 1;
  }
  trap_FS_FCloseFile(local_20[0]);
  Com_Printf("^1WARNING: BG_LoadCampaignSave: campaignsave is for another profile\n");
  return 0;
}

uint32_t BG_StoreCampaignSave(uint32_t param_1,uint32_t *param_2,char *param_3)
{
  char tmp_c1;
  int tmp_i2;
  __int32_t **pp_Var3;
  int tmp_i4;
  int *tmp_pi5;
  char *tmp_pc6;
  int *tmp_pi7;
  int local_30;
  uint32_t local_20 [4];
  
  tmp_i2 = trap_FS_FOpenFile(param_1,local_20,1);
  if (-1 < tmp_i2) {
    *param_2 = 0x53504349;
    param_2[1] = 1;
    trap_FS_Write(param_2,4,local_20[0]);
    trap_FS_Write(param_2 + 1,1,local_20[0]);
    trap_FS_Write(param_2 + 2,4,local_20[0]);
    tmp_c1 = *param_3;
    if (tmp_c1 == '\0') {
      tmp_i2 = 0;
    }
    else {
      pp_Var3 = __ctype_tolower_loc();
      tmp_i2 = 0;
      tmp_pc6 = param_3;
      do {
        tmp_i4 = (int)tmp_c1;
        tmp_c1 = tmp_pc6[1];
        tmp_i2 = tmp_i2 + (int)(tmp_pc6 + (0x77 - (int)param_3)) * (*pp_Var3)[tmp_i4];
        tmp_pc6 = tmp_pc6 + 1;
      } while (tmp_c1 != '\0');
    }
    param_2[3] = tmp_i2;
    trap_FS_Write(param_2 + 3,4,local_20[0]);
    if (0 < (int)param_2[2]) {
      tmp_pi7 = param_2 + 5;
      local_30 = 0;
      do {
        tmp_i2 = 0;
        trap_FS_Write(tmp_pi7 + -1,4,local_20[0]);
        trap_FS_Write(tmp_pi7,4,local_20[0]);
        tmp_pi5 = tmp_pi7;
        if (0 < *tmp_pi7) {
          do {
            tmp_pi5 = tmp_pi5 + 1;
            tmp_i2 = tmp_i2 + 1;
            trap_FS_Write(tmp_pi5,4,local_20[0]);
          } while (tmp_i2 < *tmp_pi7);
        }
        local_30 = local_30 + 1;
        tmp_pi7 = tmp_pi7 + 0xc;
      } while (local_30 < (int)param_2[2]);
    }
    trap_FS_FCloseFile(local_20[0]);
    return 1;
  }
  return 0;
}

uint32_t BG_PCF_ParseError(uint32_t param_1,char *param_2)
{
  uint32_t local_a0;
  uint8_t local_9c [140];
  
  vsnprintf(string_6899,0x1000,param_2,&stack0x0000000c);
  local_a0 = 0;
  local_9c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_9c,&local_a0);
  Com_Printf("^1ERROR: %s, line %d: %s\n",local_9c,local_a0,string_6899);
  trap_PC_FreeSource(param_1);
  return 0;
}

uint32_t BG_ParseCharacterFile(uint32_t param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint8_t local_434 [16];
  char local_424 [1044];
  
  tmp_i1 = trap_PC_LoadSource(param_1);
  tmp_u2 = 0;
  if (tmp_i1 != 0) {
    tmp_i3 = trap_PC_ReadToken(tmp_i1,local_434);
    if (tmp_i3 != 0) {
      tmp_i3 = Q_stricmp(local_424,"characterDef");
      if (tmp_i3 == 0) {
        tmp_i3 = trap_PC_ReadToken(tmp_i1,local_434);
        if ((tmp_i3 == 0) || (tmp_i3 = Q_stricmp(local_424,"{"), tmp_i3 != 0)) {
          tmp_u2 = BG_PCF_ParseError(tmp_i1,"expected \'{\'");
          return tmp_u2;
        }
        do {
          while( true ) {
            while( true ) {
              while( true ) {
                while( true ) {
                  while( true ) {
                    while( true ) {
                      while( true ) {
                        while( true ) {
                          tmp_i3 = trap_PC_ReadToken(tmp_i1,local_434);
                          if ((tmp_i3 == 0) || (local_424[0] == '}')) {
                            trap_PC_FreeSource(tmp_i1);
                            return 1;
                          }
                          tmp_i3 = Q_stricmp(local_424,"animationGroup");
                          if (tmp_i3 != 0) break;
                          tmp_i3 = PC_String_ParseNoAlloc(tmp_i1,param_2 + 0x80,0x40);
                          if (tmp_i3 == 0) {
                            tmp_u2 = BG_PCF_ParseError(tmp_i1,"expected animationGroup filename");
                            return tmp_u2;
                          }
                        }
                        tmp_i3 = Q_stricmp(local_424,"animationScript");
                        if (tmp_i3 != 0) break;
                        tmp_i3 = PC_String_ParseNoAlloc(tmp_i1,param_2 + 0xc0,0x40);
                        if (tmp_i3 == 0) {
                          tmp_u2 = BG_PCF_ParseError(tmp_i1,"expected animationScript filename");
                          return tmp_u2;
                        }
                      }
                      tmp_i3 = Q_stricmp(local_424,"undressedCorpseModel");
                      if (tmp_i3 != 0) break;
                      tmp_i3 = PC_String_ParseNoAlloc(tmp_i1,param_2,0x40);
                      if (tmp_i3 == 0) {
                        tmp_u2 = BG_PCF_ParseError(tmp_i1,"expected undressedCorpseModel filename");
                        return tmp_u2;
                      }
                    }
                    tmp_i3 = Q_stricmp(local_424,"undressedCorpseSkin");
                    if (tmp_i3 != 0) break;
                    tmp_i3 = PC_String_ParseNoAlloc(tmp_i1,param_2 + 0x40,0x40);
                    if (tmp_i3 == 0) {
                      tmp_u2 = BG_PCF_ParseError(tmp_i1,"expected undressedCorpseSkin filename");
                      return tmp_u2;
                    }
                  }
                  tmp_i3 = Q_stricmp(local_424,&g_unk_0010cc3a);
                  if (tmp_i3 != 0) break;
                  tmp_i3 = PC_String_ParseNoAlloc(tmp_i1,param_2 + 0x100,0x40);
                  if (tmp_i3 == 0) {
                    tmp_u2 = BG_PCF_ParseError(tmp_i1,"expected mesh filename");
                    return tmp_u2;
                  }
                }
                tmp_i3 = Q_stricmp(local_424,"skin");
                if (tmp_i3 != 0) break;
                tmp_i3 = PC_String_ParseNoAlloc(tmp_i1,param_2 + 0x140,0x40);
                if (tmp_i3 == 0) {
                  tmp_u2 = BG_PCF_ParseError(tmp_i1,"expected skin filename");
                  return tmp_u2;
                }
              }
              tmp_i3 = Q_stricmp(local_424,"hudhead");
              if (tmp_i3 != 0) break;
              tmp_i3 = PC_String_ParseNoAlloc(tmp_i1,param_2 + 0x180,0x40);
              if (tmp_i3 == 0) {
                tmp_u2 = BG_PCF_ParseError(tmp_i1,"expected hudhead filename");
                return tmp_u2;
              }
            }
            tmp_i3 = Q_stricmp(local_424,"hudheadskin");
            if (tmp_i3 != 0) break;
            tmp_i3 = PC_String_ParseNoAlloc(tmp_i1,param_2 + 0x1c0,0x40);
            if (tmp_i3 == 0) {
              tmp_u2 = BG_PCF_ParseError(tmp_i1,"expected hudheadskin filename");
              return tmp_u2;
            }
          }
          tmp_i3 = Q_stricmp(local_424,"hudheadanims");
          if (tmp_i3 != 0) {
            tmp_u2 = BG_PCF_ParseError(tmp_i1,"unknown token \'%s\'",local_424);
            return tmp_u2;
          }
          tmp_i3 = PC_String_ParseNoAlloc(tmp_i1,param_2 + 0x200,0x40);
        } while (tmp_i3 != 0);
        tmp_u2 = BG_PCF_ParseError(tmp_i1,"expected hudheadanims filename");
        return tmp_u2;
      }
    }
    tmp_u2 = BG_PCF_ParseError(tmp_i1,"expected \'characterDef\'");
  }
  return tmp_u2;
}

uint8_t * BG_GetCharacter(int param_1,int param_2)
{
  if (param_1 == 2) {
    return alliedClassCharacters + param_2 * 0x7f4;
  }
  return axisClassCharacters + param_2 * 0x7f4;
}

uint8_t * BG_GetCharacterForPlayerstate(int param_1)
{
  if (*(int *)(param_1 + 300) == 2) {
    return alliedClassCharacters + *(int *)(param_1 + 0xe4) * 0x7f4;
  }
  return axisClassCharacters + *(int *)(param_1 + 0xe4) * 0x7f4;
}

void BG_ClearCharacterPool(void)
{
  uint tmp_u1;
  
  memset(bg_characterPool,0,0x7f40);
  tmp_u1 = 0;
  do {
    *(uint32_t *)((int)&bg_characterPoolInuse + tmp_u1) = 0;
    *(uint32_t *)((int)&g_unk_00ea7684 + tmp_u1) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x40);
  return;
}

uint8_t * BG_FindFreeCharacter(uint32_t param_1)
{
  int tmp_i1;
  
  if (bg_characterPoolInuse != 0) {
    tmp_i1 = Q_stricmp(param_1,bg_characterPool);
    if (tmp_i1 == 0) {
      return bg_characterPool;
    }
  }
  if ((g_unk_00ea7684 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9af74), tmp_i1 == 0)) {
    return (uint8_t *)0xe9af74;
  }
  if ((g_unk_00ea7688 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9b768), tmp_i1 == 0)) {
    return (uint8_t *)0xe9b768;
  }
  if ((g_unk_00ea768c != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9bf5c), tmp_i1 == 0)) {
    return (uint8_t *)0xe9bf5c;
  }
  if ((g_unk_00ea7690 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9c750), tmp_i1 == 0)) {
    return (uint8_t *)0xe9c750;
  }
  if ((g_unk_00ea7694 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9cf44), tmp_i1 == 0)) {
    return (uint8_t *)0xe9cf44;
  }
  if ((g_unk_00ea7698 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9d738), tmp_i1 == 0)) {
    return (uint8_t *)0xe9d738;
  }
  if ((g_unk_00ea769c != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9df2c), tmp_i1 == 0)) {
    return (uint8_t *)0xe9df2c;
  }
  if ((g_unk_00ea76a0 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9e720), tmp_i1 == 0)) {
    return (uint8_t *)0xe9e720;
  }
  if ((g_unk_00ea76a4 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9ef14), tmp_i1 == 0)) {
    return (uint8_t *)0xe9ef14;
  }
  if ((g_unk_00ea76a8 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9f708), tmp_i1 == 0)) {
    return (uint8_t *)0xe9f708;
  }
  if ((g_unk_00ea76ac != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9fefc), tmp_i1 == 0)) {
    return (uint8_t *)0xe9fefc;
  }
  if ((g_unk_00ea76b0 != 0) && (tmp_i1 = Q_stricmp(param_1,0xea06f0), tmp_i1 == 0)) {
    return (uint8_t *)0xea06f0;
  }
  if ((g_unk_00ea76b4 != 0) && (tmp_i1 = Q_stricmp(param_1,0xea0ee4), tmp_i1 == 0)) {
    return (uint8_t *)0xea0ee4;
  }
  if ((g_unk_00ea76b8 != 0) && (tmp_i1 = Q_stricmp(param_1,0xea16d8), tmp_i1 == 0)) {
    return (uint8_t *)0xea16d8;
  }
  if ((g_unk_00ea76bc != 0) && (tmp_i1 = Q_stricmp(param_1,0xea1ecc), tmp_i1 == 0)) {
    return (uint8_t *)0xea1ecc;
  }
  if (bg_characterPoolInuse == 0) {
    tmp_i1 = 0;
  }
  else if (g_unk_00ea7684 == 0) {
    tmp_i1 = 1;
  }
  else if (g_unk_00ea7688 == 0) {
    tmp_i1 = 2;
  }
  else if (g_unk_00ea768c == 0) {
    tmp_i1 = 3;
  }
  else if (g_unk_00ea7690 == 0) {
    tmp_i1 = 4;
  }
  else if (g_unk_00ea7694 == 0) {
    tmp_i1 = 5;
  }
  else if (g_unk_00ea7698 == 0) {
    tmp_i1 = 6;
  }
  else if (g_unk_00ea769c == 0) {
    tmp_i1 = 7;
  }
  else if (g_unk_00ea76a0 == 0) {
    tmp_i1 = 8;
  }
  else if (g_unk_00ea76a4 == 0) {
    tmp_i1 = 9;
  }
  else if (g_unk_00ea76a8 == 0) {
    tmp_i1 = 10;
  }
  else if (g_unk_00ea76ac == 0) {
    tmp_i1 = 0xb;
  }
  else if (g_unk_00ea76b0 == 0) {
    tmp_i1 = 0xc;
  }
  else if (g_unk_00ea76b4 == 0) {
    tmp_i1 = 0xd;
  }
  else if (g_unk_00ea76b8 == 0) {
    tmp_i1 = 0xe;
  }
  else {
    if (g_unk_00ea76bc != 0) {
      return (uint8_t *)0x0;
    }
    tmp_i1 = 0xf;
  }
  (&bg_characterPoolInuse)[tmp_i1] = 1;
  Q_strncpyz(bg_characterPool + tmp_i1 * 0x7f4,param_1,0x40);
  return bg_characterPool + tmp_i1 * 0x7f4;
}

uint8_t * BG_FindCharacter(uint32_t param_1)
{
  int tmp_i1;
  
  if (bg_characterPoolInuse != 0) {
    tmp_i1 = Q_stricmp(param_1,bg_characterPool);
    if (tmp_i1 == 0) {
      return bg_characterPool;
    }
  }
  if ((g_unk_00ea7684 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9af74), tmp_i1 == 0)) {
    return (uint8_t *)0xe9af74;
  }
  if ((g_unk_00ea7688 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9b768), tmp_i1 == 0)) {
    return (uint8_t *)0xe9b768;
  }
  if ((g_unk_00ea768c != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9bf5c), tmp_i1 == 0)) {
    return (uint8_t *)0xe9bf5c;
  }
  if ((g_unk_00ea7690 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9c750), tmp_i1 == 0)) {
    return (uint8_t *)0xe9c750;
  }
  if ((g_unk_00ea7694 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9cf44), tmp_i1 == 0)) {
    return (uint8_t *)0xe9cf44;
  }
  if ((g_unk_00ea7698 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9d738), tmp_i1 == 0)) {
    return (uint8_t *)0xe9d738;
  }
  if ((g_unk_00ea769c != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9df2c), tmp_i1 == 0)) {
    return (uint8_t *)0xe9df2c;
  }
  if ((g_unk_00ea76a0 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9e720), tmp_i1 == 0)) {
    return (uint8_t *)0xe9e720;
  }
  if ((g_unk_00ea76a4 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9ef14), tmp_i1 == 0)) {
    return (uint8_t *)0xe9ef14;
  }
  if ((g_unk_00ea76a8 != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9f708), tmp_i1 == 0)) {
    return (uint8_t *)0xe9f708;
  }
  if ((g_unk_00ea76ac != 0) && (tmp_i1 = Q_stricmp(param_1,0xe9fefc), tmp_i1 == 0)) {
    return (uint8_t *)0xe9fefc;
  }
  if ((g_unk_00ea76b0 != 0) && (tmp_i1 = Q_stricmp(param_1,0xea06f0), tmp_i1 == 0)) {
    return (uint8_t *)0xea06f0;
  }
  if ((g_unk_00ea76b4 != 0) && (tmp_i1 = Q_stricmp(param_1,0xea0ee4), tmp_i1 == 0)) {
    return (uint8_t *)0xea0ee4;
  }
  if ((g_unk_00ea76b8 != 0) && (tmp_i1 = Q_stricmp(param_1,0xea16d8), tmp_i1 == 0)) {
    return (uint8_t *)0xea16d8;
  }
  if ((g_unk_00ea76bc != 0) && (tmp_i1 = Q_stricmp(param_1,0xea1ecc), tmp_i1 == 0)) {
    return (uint8_t *)0xea1ecc;
  }
  return (uint8_t *)0x0;
}

void BG_GetFromTable(int param_1)
{
  if (*(float *)(param_1 + 0x14) != *(float *)(param_1 + 0x10)) {
    return;
  }
  return;
}

int * BG_FindItemForWeapon(int param_1)
{
  int *tmp_pi1;
  char *tmp_pc2;
  
  if (param_1 == 0) {
    return (int *)0x0;
  }
  if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
    tmp_pi1 = (int *)(bg_itemlist + 0x38);
    do {
      if ((tmp_pi1[9] == 1) && (tmp_pi1[10] == param_1)) {
        return tmp_pi1;
      }
      tmp_pi1 = tmp_pi1 + 0xe;
    } while (*tmp_pi1 != 0);
  }
  if (param_1 - 1U < 0x33) {
    tmp_pc2 = (char *)(param_1 * 0x6b0 + 0xeb1474);
  }
  else {
    tmp_pc2 = "^1invalid";
  }
  Com_Printf("^1ERROR : ^7BG_FindItemForWeapon() ^9no item for weapon %i (%s^9)\n",param_1,tmp_pc2);
  return (int *)0x0;
}

int BG_FindClipForWeapon(int param_1)
{
  int *tmp_pi1;
  
  if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
    tmp_pi1 = (int *)(bg_itemlist + 0x38);
    do {
      if ((tmp_pi1[9] == 1) && (tmp_pi1[10] == param_1)) {
        return tmp_pi1[0xd];
      }
      tmp_pi1 = tmp_pi1 + 0xe;
    } while (*tmp_pi1 != 0);
  }
  return 0;
}

int BG_FindAmmoForWeapon(int param_1)
{
  int *tmp_pi1;
  
  if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
    tmp_pi1 = (int *)(bg_itemlist + 0x38);
    do {
      if ((tmp_pi1[9] == 1) && (tmp_pi1[10] == param_1)) {
        return tmp_pi1[0xc];
      }
      tmp_pi1 = tmp_pi1 + 0xe;
    } while (*tmp_pi1 != 0);
  }
  return 0;
}

uint BG_AkimboFireSequence(int param_1,int param_2,int param_3)
{
  uint tmp_u1;
  
  if ((((param_1 - 0x2cU < 2) || (tmp_u1 = 0, param_1 - 0x22U < 2)) && (tmp_u1 = 0, param_2 != 0)) &&
     (tmp_u1 = 1, param_3 != 0)) {
    return param_2 + param_3 & 1U ^ 1;
  }
  return tmp_u1;
}

bool BG_IsAkimboWeapon(int param_1)
{
  return param_1 - 0x22U < 2 || param_1 - 0x2cU < 2;
}

bool BG_IsAkimboSideArm(int param_1,int param_2)
{
  if (param_1 == 2) {
    return *(int *)(param_2 + 0xa4) == 0x23 || *(int *)(param_2 + 0xa4) == 0x2d;
  }
  if (param_1 == 7) {
    return *(int *)(param_2 + 0xa4) == 0x22 || *(int *)(param_2 + 0xa4) == 0x2c;
  }
  return false;
}

uint32_t BG_AkimboSidearm(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 0;
  if (param_1 - 0x22U < 0xc) {
    tmp_u1 = *(uint32_t *)(CSWTCH_86 + (param_1 - 0x22U) * 4);
  }
  return tmp_u1;
}

int * BG_FindItem(uint32_t param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  
  tmp_pi2 = (int *)(bg_itemlist + 0x38);
  tmp_i1 = GHIDRA_FIELD(bg_itemlist, 56, 4);
  while( true ) {
    if (tmp_i1 == 0) {
      return (int *)0x0;
    }
    tmp_i1 = Q_stricmp(tmp_pi2[7],param_1);
    if (tmp_i1 == 0) break;
    tmp_pi2 = tmp_pi2 + 0xe;
    tmp_i1 = *tmp_pi2;
  }
  return tmp_pi2;
}

int * BG_FindItemForClassName(uint32_t param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  
  tmp_pi2 = (int *)(bg_itemlist + 0x38);
  tmp_i1 = GHIDRA_FIELD(bg_itemlist, 56, 4);
  while( true ) {
    if (tmp_i1 == 0) {
      return (int *)0x0;
    }
    tmp_i1 = Q_stricmp(tmp_i1,param_1);
    if (tmp_i1 == 0) break;
    tmp_pi2 = tmp_pi2 + 0xe;
    tmp_i1 = *tmp_pi2;
  }
  return tmp_pi2;
}

uint32_t BG_WeaponInWolfMP(uint32_t param_1)
{
  switch(param_1) {
  default:
    return 0;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
  case 0x31:
  case 0x32:
  case 0x33:
    return 1;
  }
}

int BG_GrenadesForClass(int param_1,int param_2)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint tmp_u5;
  float tmp_f6;
  int tmp_i7;
  
  tmp_i7 = 0;
  if (GHIDRA_FIELD(cgs, 33787756, 4) == 0) {
    tmp_i7 = 5;
    if (param_1 - 1U < 4) {
      tmp_i7 = *(int *)(CSWTCH_91 + (param_1 - 1U) * 4);
    }
    tmp_u5 = *(uint *)(param_2 + 0x10);
    tmp_f6 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 96, 4);
    if (((float)GHIDRA_FIELD(jP_GrenadesPerLevel, 96, 4) != (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 100, 4)) &&
       ((tmp_u5 & 2) != 0)) {
      tmp_f6 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 100, 4);
    }
    if (((float)GHIDRA_FIELD(jP_GrenadesPerLevel, 104, 4) != (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 100, 4)) &&
       ((tmp_u5 & 4) != 0)) {
      tmp_f6 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 104, 4);
    }
    if (((float)GHIDRA_FIELD(jP_GrenadesPerLevel, 108, 4) != (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 104, 4)) &&
       ((tmp_u5 & 8) != 0)) {
      tmp_f6 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 108, 4);
    }
    if (((float)GHIDRA_FIELD(jP_GrenadesPerLevel, 112, 4) != (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 108, 4)) &&
       ((tmp_u5 & 0x10) != 0)) {
      tmp_f6 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 112, 4);
    }
    if (((float)GHIDRA_FIELD(jP_GrenadesPerLevel, 116, 4) != (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 112, 4)) &&
       ((tmp_u5 & 0x20) != 0)) {
      tmp_f6 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 116, 4);
    }
    tmp_i1 = tmp_i7 * 0x18;
    tmp_f2 = *(float *)(jP_GrenadesPerLevel + tmp_i1);
    tmp_f3 = *(float *)(jP_GrenadesPerLevel + tmp_i1 + 4);
    tmp_u5 = *(uint *)(param_2 + tmp_i7 * 4);
    if ((tmp_f3 != tmp_f2) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = tmp_f3;
    }
    tmp_f4 = *(float *)(jP_GrenadesPerLevel + tmp_i1 + 8);
    if ((tmp_f4 != tmp_f3) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = tmp_f4;
    }
    tmp_f3 = *(float *)(jP_GrenadesPerLevel + tmp_i1 + 0xc);
    if ((tmp_f3 != tmp_f4) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = tmp_f3;
    }
    tmp_f4 = *(float *)(jP_GrenadesPerLevel + tmp_i1 + 0x10);
    if ((tmp_f4 != tmp_f3) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = tmp_f4;
    }
    if ((*(float *)(jP_GrenadesPerLevel + tmp_i1 + 0x14) != tmp_f4) && ((tmp_u5 & 0x20) != 0)) {
      tmp_f2 = *(float *)(jP_GrenadesPerLevel + tmp_i1 + 0x14);
    }
    tmp_i7 = (int)ROUND(tmp_f2) + (int)ROUND(tmp_f6);
  }
  return tmp_i7;
}

char BG_GrenadeTypeForTeam(int param_1)
{
  if (param_1 != 1) {
    return (param_1 == 2) * '\t';
  }
  return '\x04';
}

void BG_CalculateSpline_r(int param_1,float *param_2,uint32_t *param_3,float param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float *pfVar4;
  int tmp_i5;
  int tmp_i7;
  float local_e4 [4];
  uint32_t local_d4;
  uint32_t local_d0;
  uint32_t local_cc;
  uint32_t local_c8;
  uint32_t local_c4;
  uint32_t local_c0;
  uint32_t local_bc;
  uint32_t local_b8;
  uint32_t local_b4;
  uint32_t local_b0;
  uint32_t local_ac;
  int tmp_i6;
  
  tmp_i5 = *(int *)(param_1 + 0x1c4);
  local_e4[0] = *(float *)(param_1 + 0x40);
  local_e4[1] = *(float *)(param_1 + 0x44);
  tmp_i6 = tmp_i5 + 2;
  local_e4[2] = *(float *)(param_1 + 0x48);
  if (tmp_i5 < 1) {
    tmp_i5 = 0;
  }
  else {
    local_e4[3] = (float)*(uint32_t *)(param_1 + 0xd4);
    local_d4 = *(uint32_t *)(param_1 + 0xd8);
    local_d0 = *(uint32_t *)(param_1 + 0xdc);
    if (tmp_i5 != 1) {
      local_cc = *(uint32_t *)(param_1 + 0x120);
      local_c8 = *(uint32_t *)(param_1 + 0x124);
      local_c4 = *(uint32_t *)(param_1 + 0x128);
      if (tmp_i5 != 2) {
        local_c0 = *(uint32_t *)(param_1 + 0x16c);
        local_bc = *(uint32_t *)(param_1 + 0x170);
        local_b8 = *(uint32_t *)(param_1 + 0x174);
        if (tmp_i5 != 3) {
          local_b4 = *(uint32_t *)(param_1 + 0x1b8);
          local_b0 = *(uint32_t *)(param_1 + 0x1bc);
          local_ac = *(uint32_t *)(param_1 + 0x1c0);
        }
      }
    }
  }
  tmp_i7 = *(int *)(param_1 + 0x8c);
  if (tmp_i7 != 0) {
    tmp_i5 = tmp_i5 * 3;
    local_e4[tmp_i5 + 3] = *(float *)(tmp_i7 + 0x40);
    local_e4[tmp_i5 + 4] = *(float *)(tmp_i7 + 0x44);
    local_e4[tmp_i5 + 5] = *(float *)(tmp_i7 + 0x48);
    if (2 < tmp_i6) {
      do {
        tmp_i5 = tmp_i6 + -1;
        tmp_i7 = 0;
        if (tmp_i5 != 2) {
          tmp_i7 = 0;
          pfVar4 = local_e4 + 3;
          tmp_f3 = local_e4[2];
          tmp_f2 = local_e4[1];
          tmp_f1 = local_e4[0];
          do {
            tmp_i7 = tmp_i7 + 2;
            pfVar4[-3] = (*pfVar4 - tmp_f1) * param_4 + tmp_f1;
            pfVar4[-2] = (pfVar4[1] - tmp_f2) * param_4 + tmp_f2;
            pfVar4[-1] = (pfVar4[2] - tmp_f3) * param_4 + tmp_f3;
            tmp_f1 = pfVar4[3];
            tmp_f2 = pfVar4[4];
            tmp_f3 = pfVar4[5];
            *pfVar4 = (tmp_f1 - *pfVar4) * param_4 + *pfVar4;
            pfVar4[1] = (tmp_f2 - pfVar4[1]) * param_4 + pfVar4[1];
            pfVar4[2] = (tmp_f3 - pfVar4[2]) * param_4 + pfVar4[2];
            pfVar4 = pfVar4 + 6;
          } while (tmp_i7 != (tmp_i6 - 4U & 0xfffffffe) + 2);
        }
        pfVar4 = local_e4 + tmp_i7 * 3 + 1;
        do {
          tmp_i7 = tmp_i7 + 1;
          pfVar4[-1] = (pfVar4[2] - pfVar4[-1]) * param_4 + pfVar4[-1];
          *pfVar4 = *pfVar4 + (pfVar4[3] - *pfVar4) * param_4;
          pfVar4[1] = pfVar4[1] + (pfVar4[4] - pfVar4[1]) * param_4;
          pfVar4 = pfVar4 + 3;
        } while (tmp_i7 < tmp_i5);
        tmp_i6 = tmp_i5;
      } while (tmp_i5 != 2);
    }
    *param_2 = local_e4[0];
    param_2[1] = local_e4[1];
    param_2[2] = local_e4[2];
    *param_3 = local_e4[3];
    param_3[1] = local_d4;
    param_3[2] = local_d0;
  }
  return;
}

bool BG_PlayerTouchesItem(int param_1,int param_2,int param_3)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  bool tmp_b6;
  long double tmp_l7;
  double tmp_d8;
  float tmp_f9;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i4 = *(int *)(param_2 + 0x110);
  switch(*(uint32_t *)(param_2 + 0xc)) {
  case 0:
  case 1:
  case 9:
    local_40 = *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x1c);
    local_38 = *(float *)(param_2 + 0x20);
    break;
  case 2:
    tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) * 0.001;
    goto LAB_0002108a;
  case 3:
    tmp_i4 = *(int *)(param_2 + 0x14) + *(int *)(param_2 + 0x10);
    if (param_3 <= tmp_i4) {
      tmp_i4 = param_3;
    }
    tmp_f9 = (float)(tmp_i4 - *(int *)(param_2 + 0x10)) * 0.001;
    tmp_f1 = 0.0;
    if (0.0 <= tmp_f9) {
      tmp_f1 = tmp_f9;
    }
    goto LAB_0002108a;
  default:
    Com_Error(2,"BG_EvaluateTrajectory: unknown trType: %i",*(uint32_t *)(param_2 + 0x10));
    break;
  case 5:
    tmp_d8 = ((double)(param_3 - *(int *)(param_2 + 0x10)) / (double)*(int *)(param_2 + 0x14)) *
            3.141592653589793;
    tmp_d8 = sin(tmp_d8 + tmp_d8);
    tmp_f1 = (float)tmp_d8;
LAB_0002108a:
    local_40 = *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x28) * tmp_f1 + *(float *)(param_2 + 0x1c);
    local_38 = tmp_f1 * *(float *)(param_2 + 0x2c) + *(float *)(param_2 + 0x20);
    break;
  case 6:
    tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) * 0.001;
    local_40 = *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x28) * tmp_f1 + *(float *)(param_2 + 0x1c);
    tmp_f9 = *(float *)(param_2 + 0x20) + tmp_f1 * *(float *)(param_2 + 0x2c);
    tmp_f2 = (float)(int)GHIDRA_FIELD(cgs, 33788128, 4);
    goto LAB_00021174;
  case 7:
    tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) * 0.001;
    local_40 = *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x28) * tmp_f1 + *(float *)(param_2 + 0x1c);
    tmp_f9 = *(float *)(param_2 + 0x20) + tmp_f1 * *(float *)(param_2 + 0x2c);
    tmp_f2 = (float)(int)GHIDRA_FIELD(cgs, 33788128, 4) * 0.3;
LAB_00021174:
    local_38 = tmp_f9 - tmp_f2 * 0.5 * tmp_f1 * tmp_f1;
    break;
  case 8:
    tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) * 0.001;
    local_40 = *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x28) * tmp_f1 + *(float *)(param_2 + 0x1c);
    local_38 = (*(float *)(param_2 + 0x2c) * tmp_f1 + *(float *)(param_2 + 0x20)) -
               (float)(int)GHIDRA_FIELD(cgs, 33788128, 4) * 0.2 * 0.5 * tmp_f1;
    break;
  case 10:
    tmp_i3 = *(int *)(param_2 + 0x10);
    tmp_i5 = tmp_i3 + *(int *)(param_2 + 0x14);
    tmp_l7 = (long double)VectorLength(param_2 + 0x24);
    tmp_i4 = *(int *)(param_2 + 0x14);
    VectorNormalize2(param_2 + 0x24,&local_40);
    if (param_3 <= tmp_i5) {
      tmp_i5 = param_3;
    }
    tmp_f1 = (float)(tmp_i5 - tmp_i3) * 0.001;
    tmp_f1 = (float)(tmp_l7 / ((long double)tmp_i4 * (long double)0.001)) * 0.5 * tmp_f1 * tmp_f1;
    local_40 = tmp_f1 * local_40 + *(float *)(param_2 + 0x18);
    local_3c = tmp_f1 * local_3c + *(float *)(param_2 + 0x1c);
    local_38 = tmp_f1 * local_38 + *(float *)(param_2 + 0x20);
    break;
  case 0xb:
    tmp_i4 = *(int *)(param_2 + 0x14) + *(int *)(param_2 + 0x10);
    if (param_3 <= tmp_i4) {
      tmp_i4 = param_3;
    }
    tmp_f1 = (float)(tmp_i4 - *(int *)(param_2 + 0x10)) * 0.001;
    tmp_l7 = (long double)VectorLength(param_2 + 0x24);
    tmp_i4 = *(int *)(param_2 + 0x14);
    VectorNormalize2(param_2 + 0x24,&local_40);
    tmp_f9 = -(float)(tmp_l7 / ((long double)tmp_i4 * (long double)0.001)) * 0.5 * tmp_f1 * tmp_f1;
    local_40 = tmp_f9 * local_40 + *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = tmp_f9 * local_3c + tmp_f1 * *(float *)(param_2 + 0x28) + *(float *)(param_2 + 0x1c);
    local_38 = tmp_f9 * local_38 + *(float *)(param_2 + 0x2c) * tmp_f1 + *(float *)(param_2 + 0x20);
    break;
  case 0xc:
    tmp_b6 = tmp_i4 < 0;
    if (tmp_b6) {
      tmp_i4 = -tmp_i4;
    }
    tmp_i4 = tmp_i4 + -1;
    if ((tmp_i4 != -1) && (tmp_i4 < numSplinePaths)) {
      if ((*(int *)(param_2 + 0x14) == 0) ||
         (tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) / (float)*(int *)(param_2 + 0x14),
         tmp_f1 < 0.0)) {
        tmp_f1 = 0.0;
      }
      else if (1.0 < tmp_f1) {
        tmp_f1 = 1.0;
      }
      if (tmp_b6) {
        tmp_f1 = 1.0 - tmp_f1;
      }
      BG_CalculateSpline_r(splinePaths + tmp_i4 * 0x394,&local_34,&local_28,tmp_f1);
      local_40 = (local_28 - local_34) * tmp_f1 + local_34;
      local_3c = (local_24 - local_30) * tmp_f1 + local_30;
      local_38 = (local_20 - local_2c) * tmp_f1 + local_2c;
    }
    break;
  case 0xd:
    tmp_b6 = tmp_i4 < 0;
    if (tmp_b6) {
      tmp_i4 = -tmp_i4;
    }
    tmp_i4 = tmp_i4 + -1;
    if ((tmp_i4 == -1) || (numSplinePaths <= tmp_i4)) break;
    if (*(int *)(param_2 + 0x14) == 0) {
      tmp_f1 = 0.0;
LAB_00020edf:
      if (tmp_b6) {
        tmp_f1 = 1.0 - tmp_f1;
      }
      tmp_f1 = tmp_f1 * 16.0;
      tmp_f9 = floorf(tmp_f1);
      tmp_i3 = (int)ROUND(tmp_f9);
LAB_00020f21:
      if (0xf < tmp_i3) goto LAB_00020f2c;
      tmp_f1 = tmp_f1 - (float)tmp_i3;
LAB_0002151a:
      tmp_f1 = tmp_f1 * *(float *)(splinePaths + tmp_i3 * 0x1c + tmp_i4 * 0x394 + 0x1e0);
    }
    else {
      tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) / (float)*(int *)(param_2 + 0x14);
      if (tmp_f1 < 0.0) {
        if (tmp_b6) {
          tmp_i3 = 0x10;
          tmp_f1 = 16.0;
          goto LAB_00020f21;
        }
        tmp_f1 = 0.0;
        tmp_i3 = 0;
        goto LAB_0002151a;
      }
      if (tmp_f1 <= 1.0) goto LAB_00020edf;
      if (tmp_b6) {
        tmp_i3 = 0;
        tmp_f1 = 0.0;
        goto LAB_00020f21;
      }
LAB_00020f2c:
      tmp_f1 = *(float *)(splinePaths + tmp_i4 * 0x394 + 900);
      tmp_i3 = 0xf;
    }
    tmp_i4 = tmp_i3 * 0x1c + tmp_i4 * 0x394;
    local_40 = *(float *)(splinePaths + tmp_i4 + 0x1d4) * tmp_f1 +
               *(float *)(splinePaths + tmp_i4 + 0x1c8);
    local_3c = *(float *)(splinePaths + tmp_i4 + 0x1d8) * tmp_f1 +
               *(float *)(splinePaths + tmp_i4 + 0x1cc);
    local_38 = tmp_f1 * *(float *)(splinePaths + tmp_i4 + 0x1dc) +
               *(float *)(splinePaths + tmp_i4 + 0x1d0);
  }
  tmp_f1 = *(float *)(param_1 + 0x14) - local_40;
  tmp_b6 = false;
  if ((((tmp_f1 <= 36.0) && (-36.0 <= tmp_f1)) &&
      (tmp_f1 = *(float *)(param_1 + 0x18) - local_3c, tmp_f1 <= 36.0)) &&
     ((-36.0 <= tmp_f1 && (tmp_f1 = *(float *)(param_1 + 0x1c) - local_38, tmp_f1 <= 36.0)))) {
    tmp_b6 = -36.0 <= tmp_f1;
  }
  return tmp_b6;
}

uint32_t BG_TraverseSpline(float *param_1,int *param_2)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  
  tmp_f1 = *param_1;
  if (tmp_f1 <= 1.0) {
LAB_00021620:
    if (0.0 <= tmp_f1) {
      return 1;
    }
    tmp_f1 = tmp_f1 * *(float *)(*param_2 + 0x388);
    tmp_i3 = *(int *)(*param_2 + 0x90);
    if (tmp_i3 != 0) {
      tmp_f2 = *(float *)(tmp_i3 + 0x388);
      while (tmp_f2 != 0.0) {
        *param_2 = tmp_i3;
        tmp_f1 = 1.0 - -tmp_f1 / *(float *)(tmp_i3 + 0x388);
        *param_1 = tmp_f1;
        if (0.0 <= tmp_f1) {
          return 1;
        }
        tmp_f1 = tmp_f1 * *(float *)(*param_2 + 0x388);
        tmp_i3 = *(int *)(*param_2 + 0x90);
        if (tmp_i3 == 0) {
          return 0;
        }
        tmp_f2 = *(float *)(tmp_i3 + 0x388);
      }
    }
  }
  else {
    *param_1 = tmp_f1 - 1.0;
    tmp_f1 = (tmp_f1 - 1.0) * *(float *)(*param_2 + 0x388);
    tmp_i3 = *(int *)(*param_2 + 0x8c);
    if (tmp_i3 != 0) {
      tmp_f2 = *(float *)(tmp_i3 + 0x388);
      while (tmp_f2 != 0.0) {
        *param_2 = tmp_i3;
        tmp_f1 = tmp_f1 / *(float *)(tmp_i3 + 0x388);
        if (tmp_f1 <= 1.0) {
          *param_1 = tmp_f1;
          goto LAB_00021620;
        }
        *param_1 = tmp_f1 - 1.0;
        tmp_f1 = (tmp_f1 - 1.0) * *(float *)(*param_2 + 0x388);
        tmp_i3 = *(int *)(*param_2 + 0x8c);
        if (tmp_i3 == 0) {
          return 0;
        }
        tmp_f2 = *(float *)(tmp_i3 + 0x388);
      }
    }
  }
  return 0;
}

uint32_t BG_RaySphereIntersection(float param_1,float *param_2,float *param_3,float *param_4,float *param_5)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  
  tmp_f1 = *param_3 - *param_2;
  tmp_f4 = param_3[1] - param_2[1];
  tmp_f3 = param_3[2] - param_2[2];
  tmp_f2 = param_3[5] * tmp_f3 + param_3[4] * tmp_f4 + param_3[3] * tmp_f1;
  tmp_f2 = tmp_f2 + tmp_f2;
  tmp_f1 = tmp_f2 * tmp_f2 -
          ((tmp_f3 * tmp_f3 + tmp_f4 * tmp_f4 + tmp_f1 * tmp_f1) - param_1 * param_1) * 4.0;
  if (tmp_f1 < 0.0) {
    return 0;
  }
  tmp_f4 = SQRT(tmp_f1);
  if (NAN(tmp_f4)) {
    tmp_f4 = sqrtf(tmp_f1);
  }
  *param_4 = (tmp_f4 - tmp_f2) * 0.5;
  *param_5 = (-tmp_f2 - tmp_f4) * 0.5;
  return 1;
}

void BG_LinearPathOrigin2(float param_1,int *param_2,float *param_3,float *param_4)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  bool tmp_b7;
  int tmp_i8;
  int tmp_i9;
  bool tmp_b10;
  float tmp_f11;
  float tmp_f12;
  
  tmp_f4 = *param_3;
  tmp_f11 = floorf(tmp_f4 * 16.0);
  tmp_i8 = (int)ROUND(tmp_f11);
  if (tmp_i8 < 0x10) {
    tmp_f4 = tmp_f4 * 16.0 - (float)tmp_i8;
  }
  else {
    tmp_i8 = 0xf;
    tmp_f4 = 1.0;
  }
  tmp_b10 = true;
  tmp_i9 = *param_2;
  do {
    tmp_i3 = tmp_i8 * 0x1c;
    tmp_i1 = tmp_i9 + 0x1c0 + tmp_i3;
    tmp_i2 = tmp_i9 + 0x1c4 + tmp_i3;
    tmp_f5 = *(float *)(tmp_i1 + 8) - *param_4;
    tmp_i3 = tmp_i9 + 0x1c8 + tmp_i3;
    tmp_f12 = *(float *)(tmp_i2 + 8) - param_4[1];
    tmp_f11 = *(float *)(tmp_i3 + 8) - param_4[2];
    tmp_f6 = *(float *)(tmp_i3 + 0x14) * tmp_f11 +
            *(float *)(tmp_i2 + 0x14) * tmp_f12 + *(float *)(tmp_i1 + 0x14) * tmp_f5;
    tmp_f6 = tmp_f6 + tmp_f6;
    tmp_f11 = tmp_f6 * tmp_f6 -
             ((tmp_f11 * tmp_f11 + tmp_f12 * tmp_f12 + tmp_f5 * tmp_f5) - param_1 * param_1) * 4.0;
    if (tmp_f11 < 0.0) {
LAB_000218fc:
      if (param_1 < 0.0) goto LAB_00021a80;
      tmp_i8 = tmp_i8 + 1;
      if (tmp_i8 == 0x10) {
        tmp_i8 = 0;
        if (0.0 <= param_1) {
          tmp_i9 = *(int *)(tmp_i9 + 0x8c);
          if (tmp_i9 == 0) {
            return;
          }
          tmp_i8 = 0;
          *param_2 = tmp_i9;
          goto LAB_0002192e;
        }
        goto LAB_00021a8c;
      }
    }
    else {
      tmp_f12 = SQRT(tmp_f11);
      if (NAN(tmp_f12)) {
        tmp_f12 = sqrtf(tmp_f11);
      }
      tmp_i9 = *param_2;
      tmp_f11 = *(float *)(tmp_i9 + 0x1e0 + tmp_i8 * 0x1c);
      tmp_f5 = ((tmp_f12 - tmp_f6) * 0.5) / tmp_f11;
      tmp_f11 = ((-tmp_f6 - tmp_f12) * 0.5) / tmp_f11;
      if (!tmp_b10) {
        if (param_1 < 0.0) {
          tmp_b10 = tmp_f11 < tmp_f5;
        }
        else {
          tmp_b10 = tmp_f5 < tmp_f11;
        }
        tmp_b7 = 0.0 <= tmp_f5;
        if (tmp_f5 <= 1.0 && ((!tmp_b10 && tmp_f5 != tmp_f11) && tmp_b7)) {
          tmp_b10 = true;
        }
        else {
          tmp_b10 = tmp_f11 <= 1.0;
          tmp_b7 = 0.0 <= tmp_f11;
          tmp_f5 = tmp_f11;
        }
LAB_000218d0:
        if ((tmp_b7) && (tmp_b10)) {
          tmp_i9 = tmp_i8 * 0x1c;
          *param_3 = tmp_f5 * 0.0625 + (float)tmp_i8 * 0.0625;
          tmp_i8 = *param_2;
          *param_4 = *(float *)(tmp_i8 + 0x1e0 + tmp_i9) * tmp_f5 * *(float *)(tmp_i8 + 0x1d4 + tmp_i9) +
                     *(float *)(tmp_i8 + 0x1c8 + tmp_i9);
          tmp_i8 = *param_2;
          param_4[1] = *(float *)(tmp_i8 + 0x1e0 + tmp_i9) * tmp_f5 * *(float *)(tmp_i8 + 0x1d8 + tmp_i9)
                       + *(float *)(tmp_i8 + 0x1cc + tmp_i9);
          tmp_i8 = *param_2;
          param_4[2] = tmp_f5 * *(float *)(tmp_i8 + 0x1e0 + tmp_i9) * *(float *)(tmp_i8 + 0x1dc + tmp_i9)
                       + *(float *)(tmp_i8 + 0x1d0 + tmp_i9);
          return;
        }
        goto LAB_000218fc;
      }
      if (0.0 <= param_1) {
        tmp_b7 = 0.0 <= tmp_f5;
        if (1.0 < tmp_f5 || (tmp_f5 <= tmp_f4 || !tmp_b7)) {
          if (tmp_f4 < tmp_f11) goto LAB_00021894;
          goto LAB_000218fc;
        }
        tmp_b10 = true;
        goto LAB_000218d0;
      }
      tmp_b7 = 0.0 <= tmp_f5;
      if (tmp_f5 <= 1.0 && (tmp_f5 < tmp_f4 && tmp_b7)) {
        tmp_b10 = true;
        goto LAB_000218d0;
      }
      if (tmp_f11 < tmp_f4) {
LAB_00021894:
        tmp_b10 = tmp_f11 <= 1.0;
        tmp_b7 = 0.0 <= tmp_f11;
        tmp_f5 = tmp_f11;
        goto LAB_000218d0;
      }
LAB_00021a80:
      tmp_i8 = tmp_i8 + -1;
      if (tmp_i8 < 0) {
        tmp_i8 = 0xf;
LAB_00021a8c:
        tmp_i9 = *(int *)(tmp_i9 + 0x90);
        if (tmp_i9 == 0) {
          return;
        }
        *param_2 = tmp_i9;
      }
    }
LAB_0002192e:
    tmp_b10 = false;
  } while( true );
}

void BG_ComputeSegments(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  long double tmp_l4;
  int local_64;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  local_64 = 0;
  tmp_f1 = 0.0;
  pfVar3 = (float *)(param_1 + 0x1d4);
  do {
    tmp_f1 = tmp_f1 * 0.0625;
    BG_CalculateSpline_r(param_1,&local_4c,&local_40,tmp_f1);
    local_64 = local_64 + 1;
    pfVar3[-3] = (local_40 - local_4c) * tmp_f1 + local_4c;
    pfVar3[-2] = (local_3c - local_48) * tmp_f1 + local_48;
    pfVar3[-1] = (local_38 - local_44) * tmp_f1 + local_44;
    tmp_f1 = (float)local_64;
    tmp_f2 = tmp_f1 * 0.0625;
    BG_CalculateSpline_r(param_1,&local_34,&local_28,tmp_f2);
    local_4c = (local_28 - local_34) * tmp_f2 + local_34;
    local_48 = (local_24 - local_30) * tmp_f2 + local_30;
    local_44 = tmp_f2 * (local_20 - local_2c) + local_2c;
    *pfVar3 = local_4c - pfVar3[-3];
    pfVar3[1] = local_48 - pfVar3[-2];
    pfVar3[2] = local_44 - pfVar3[-1];
    tmp_l4 = (long double)VectorLength(pfVar3);
    pfVar3[3] = (float)tmp_l4;
    VectorNormalize(pfVar3);
    pfVar3 = pfVar3 + 7;
  } while (local_64 != 0x10);
  return;
}

void BG_EvaluateTrajectory(uint32_t *param_1,int param_2,float *param_3,int param_4,int param_5)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  bool tmp_b5;
  uint8_t *tmp_pu6;
  int tmp_i7;
  bool tmp_b8;
  long double tmp_l9;
  float tmp_f10;
  double tmp_d11;
  int local_54;
  float local_3c;
  uint8_t *local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  switch(*param_1) {
  case 0:
  case 1:
  case 9:
    *param_3 = (float)param_1[3];
    param_3[1] = (float)param_1[4];
    param_3[2] = (float)param_1[5];
    break;
  case 2:
    tmp_f1 = (float)(param_2 - param_1[1]) * 0.001;
    goto LAB_00021fda;
  case 3:
    tmp_i7 = param_1[2] + param_1[1];
    if (param_2 <= tmp_i7) {
      tmp_i7 = param_2;
    }
    tmp_f10 = (float)(tmp_i7 - param_1[1]) * 0.001;
    tmp_f1 = 0.0;
    if (0.0 <= tmp_f10) {
      tmp_f1 = tmp_f10;
    }
    goto LAB_00021fda;
  default:
    Com_Error(2,"BG_EvaluateTrajectory: unknown trType: %i",param_1[1]);
    break;
  case 5:
    tmp_d11 = ((double)(param_2 - param_1[1]) / (double)(int)param_1[2]) * 3.141592653589793;
    tmp_d11 = sin(tmp_d11 + tmp_d11);
    tmp_f1 = (float)tmp_d11;
LAB_00021fda:
    *param_3 = (float)param_1[6] * tmp_f1 + (float)param_1[3];
    param_3[1] = (float)param_1[7] * tmp_f1 + (float)param_1[4];
    param_3[2] = tmp_f1 * (float)param_1[8] + (float)param_1[5];
    break;
  case 6:
    tmp_f1 = (float)(param_2 - param_1[1]) * 0.001;
    *param_3 = (float)param_1[6] * tmp_f1 + (float)param_1[3];
    param_3[1] = (float)param_1[7] * tmp_f1 + (float)param_1[4];
    tmp_f10 = (float)param_1[8] * tmp_f1 + (float)param_1[5];
    param_3[2] = tmp_f10;
    tmp_f2 = (float)(int)GHIDRA_FIELD(cgs, 33788128, 4);
    goto LAB_000220be;
  case 7:
    tmp_f1 = (float)(param_2 - param_1[1]) * 0.001;
    *param_3 = (float)param_1[6] * tmp_f1 + (float)param_1[3];
    param_3[1] = (float)param_1[7] * tmp_f1 + (float)param_1[4];
    tmp_f10 = (float)param_1[8] * tmp_f1 + (float)param_1[5];
    param_3[2] = tmp_f10;
    tmp_f2 = (float)(int)GHIDRA_FIELD(cgs, 33788128, 4) * 0.3;
LAB_000220be:
    param_3[2] = tmp_f10 - tmp_f2 * 0.5 * tmp_f1 * tmp_f1;
    break;
  case 8:
    tmp_f1 = (float)(param_2 - param_1[1]) * 0.001;
    *param_3 = (float)param_1[6] * tmp_f1 + (float)param_1[3];
    param_3[1] = (float)param_1[7] * tmp_f1 + (float)param_1[4];
    tmp_f10 = (float)param_1[8] * tmp_f1 + (float)param_1[5];
    param_3[2] = tmp_f10;
    param_3[2] = tmp_f10 - (float)(int)GHIDRA_FIELD(cgs, 33788128, 4) * 0.2 * 0.5 * tmp_f1;
    break;
  case 10:
    tmp_i7 = param_1[2] + param_1[1];
    if (param_2 <= tmp_i7) {
      tmp_i7 = param_2;
    }
    local_3c = (float)(tmp_i7 - param_1[1]) * 0.001;
    tmp_l9 = (long double)VectorLength(param_1 + 6);
    tmp_i7 = param_1[2];
    VectorNormalize2(param_1 + 6,param_3);
    local_3c = (float)(tmp_l9 / ((long double)tmp_i7 * (long double)0.001)) * 0.5 * local_3c * local_3c;
    *param_3 = local_3c * *param_3 + (float)param_1[3];
    param_3[1] = local_3c * param_3[1] + (float)param_1[4];
    param_3[2] = local_3c * param_3[2] + (float)param_1[5];
    break;
  case 0xb:
    tmp_i7 = param_1[2] + param_1[1];
    if (param_2 <= tmp_i7) {
      tmp_i7 = param_2;
    }
    local_3c = (float)(tmp_i7 - param_1[1]) * 0.001;
    tmp_l9 = (long double)VectorLength(param_1 + 6);
    tmp_i7 = param_1[2];
    VectorNormalize2(param_1 + 6,param_3);
    tmp_f1 = (float)param_1[7];
    tmp_f10 = (float)param_1[4];
    tmp_f2 = (float)param_1[8];
    tmp_f3 = (float)param_1[5];
    tmp_f4 = -(float)(tmp_l9 / ((long double)tmp_i7 * (long double)0.001)) * 0.5 * local_3c * local_3c;
    *param_3 = tmp_f4 * *param_3 + local_3c * (float)param_1[6] + (float)param_1[3];
    param_3[1] = tmp_f4 * param_3[1] + tmp_f1 * local_3c + tmp_f10;
    param_3[2] = tmp_f4 * param_3[2] + tmp_f3 + tmp_f2 * local_3c;
    break;
  case 0xc:
    tmp_b8 = param_5 < 0;
    if (tmp_b8) {
      param_5 = -param_5;
    }
    param_5 = param_5 + -1;
    if (param_5 == -1) {
      return;
    }
    if (numSplinePaths <= param_5) {
      return;
    }
    local_38 = splinePaths + param_5 * 0x394;
    if ((param_1[2] == 0) ||
       (local_3c = (float)(param_2 - param_1[1]) / (float)(int)param_1[2], local_3c < 0.0)) {
      local_3c = 0.0;
    }
    else if (1.0 < local_3c) {
      local_3c = 1.0;
    }
    if (tmp_b8) {
      local_3c = 1.0 - local_3c;
    }
    tmp_f1 = local_3c;
    BG_CalculateSpline_r(local_38,&local_34,&local_28,local_3c);
    if (param_4 == 0) {
      *param_3 = (local_28 - local_34) * local_3c + local_34;
      param_3[1] = (local_24 - local_30) * local_3c + local_30;
      param_3[2] = (local_20 - local_2c) * local_3c + local_2c;
      return;
    }
    if ((float)param_1[3] == 0.0) {
LAB_00022410:
      *param_3 = local_28 - local_34;
      param_3[1] = local_24 - local_30;
      param_3[2] = local_20 - local_2c;
    }
    else {
      tmp_f10 = *(float *)(local_38 + 0x388);
      tmp_f1 = (float)param_1[3] / tmp_f10 + tmp_f1;
      tmp_pu6 = local_38;
      if (1.0 < tmp_f1) {
        tmp_pu6 = *(uint8_t **)(local_38 + 0x8c);
        tmp_f1 = tmp_f10 * (tmp_f1 - 1.0);
        if (tmp_pu6 != (uint8_t *)0x0) {
          tmp_f10 = *(float *)(tmp_pu6 + 0x388);
          while (tmp_f10 != 0.0) {
            tmp_f1 = tmp_f1 / tmp_f10;
            if (tmp_f1 <= 1.0) goto LAB_000227b0;
            tmp_pu6 = *(uint8_t **)(tmp_pu6 + 0x8c);
            tmp_f1 = (tmp_f1 - 1.0) * tmp_f10;
            if (tmp_pu6 == (uint8_t *)0x0) break;
            tmp_f10 = *(float *)(tmp_pu6 + 0x388);
          }
        }
        goto LAB_00022410;
      }
LAB_000227b0:
      if (tmp_f1 < 0.0) {
        tmp_f1 = tmp_f1 * tmp_f10;
        tmp_pu6 = *(uint8_t **)(tmp_pu6 + 0x90);
        if (tmp_pu6 != (uint8_t *)0x0) {
          tmp_f10 = *(float *)(tmp_pu6 + 0x388);
          while (tmp_f10 != 0.0) {
            tmp_f1 = 1.0 - -tmp_f1 / tmp_f10;
            if (0.0 <= tmp_f1) goto LAB_0002283a;
            tmp_f1 = tmp_f1 * tmp_f10;
            tmp_pu6 = *(uint8_t **)(tmp_pu6 + 0x90);
            if (tmp_pu6 == (uint8_t *)0x0) break;
            tmp_f10 = *(float *)(tmp_pu6 + 0x388);
          }
        }
        goto LAB_00022410;
      }
LAB_0002283a:
      *param_3 = (local_28 - local_34) * local_3c + local_34;
      param_3[1] = (local_24 - local_30) * local_3c + local_30;
      param_3[2] = (local_20 - local_2c) * local_3c + local_2c;
      BG_CalculateSpline_r(tmp_pu6,&local_34,&local_28,tmp_f1);
      local_34 = (local_28 - local_34) * tmp_f1 + local_34;
      local_30 = (local_24 - local_30) * tmp_f1 + local_30;
      local_2c = (local_20 - local_2c) * tmp_f1 + local_2c;
      if ((float)param_1[3] < 0.0) {
        *param_3 = *param_3 - local_34;
        param_3[1] = param_3[1] - local_30;
        param_3[2] = param_3[2] - local_2c;
      }
      else {
        *param_3 = local_34 - *param_3;
        param_3[1] = local_30 - param_3[1];
        param_3[2] = local_2c - param_3[2];
      }
    }
    vectoangles(param_3,param_3);
    tmp_f1 = (float)param_1[4];
    if ((10000.0 <= tmp_f1) || (tmp_f1 < -10000.0)) {
      if (tmp_f1 < 0.0) {
        tmp_f1 = tmp_f1 + 10000.0;
        tmp_b5 = true;
        tmp_b8 = true;
      }
      else {
        tmp_f1 = tmp_f1 - 10000.0;
        tmp_b5 = true;
        tmp_b8 = true;
      }
    }
    else {
      tmp_b5 = false;
      tmp_b8 = false;
    }
    if ((1000.0 <= tmp_f1) || (tmp_f1 < -1000.0)) {
      if (tmp_f1 < 0.0) {
        tmp_f1 = tmp_f1 + 1000.0;
      }
      else {
        tmp_f1 = tmp_f1 - 1000.0;
      }
      if (tmp_b5) {
        tmp_d11 = sin((double)(((local_3c + local_3c) - 1.0) * 3.1415927 * 0.5));
        param_3[2] = tmp_f1 + ((float)tmp_d11 + 1.0) * 0.5 * (float)param_1[5];
        return;
      }
      if (!tmp_b8) {
        tmp_d11 = sin((double)((1.0 - local_3c) * 3.1415927 * 0.5));
        param_3[2] = tmp_f1 + (1.0 - (float)tmp_d11) * (float)param_1[5];
        return;
      }
    }
    else if (!tmp_b8) {
      param_3[2] = (float)param_1[5] * local_3c + tmp_f1;
      return;
    }
    tmp_d11 = sin((double)local_3c * 3.141592653589793 * 0.5);
    param_3[2] = tmp_f1 + (float)tmp_d11 * (float)param_1[5];
    break;
  case 0xd:
    tmp_b8 = param_5 < 0;
    if (tmp_b8) {
      param_5 = -param_5;
    }
    param_5 = param_5 + -1;
    if ((param_5 != -1) && (param_5 < numSplinePaths)) {
      local_38 = splinePaths + param_5 * 0x394;
      if ((param_1[2] == 0) ||
         (local_3c = (float)(param_2 - param_1[1]) / (float)(int)param_1[2], local_3c < 0.0)) {
        local_3c = 0.0;
      }
      else if (1.0 < local_3c) {
        local_3c = 1.0;
      }
      if (tmp_b8) {
        local_3c = 1.0 - local_3c;
      }
      if (param_4 == 0) {
        tmp_f1 = local_3c * 16.0;
        tmp_f10 = floorf(tmp_f1);
        tmp_i7 = (int)ROUND(tmp_f10);
        if (tmp_i7 < 0x10) {
          tmp_f1 = (tmp_f1 - (float)tmp_i7) *
                  *(float *)(splinePaths + tmp_i7 * 0x1c + param_5 * 0x394 + 0x1e0);
        }
        else {
          tmp_f1 = *(float *)(splinePaths + param_5 * 0x394 + 900);
          tmp_i7 = 0xf;
        }
        tmp_i7 = param_5 * 0x394 + tmp_i7 * 0x1c;
        *param_3 = *(float *)(splinePaths + tmp_i7 + 0x1d4) * tmp_f1 +
                   *(float *)(splinePaths + tmp_i7 + 0x1c8);
        param_3[1] = *(float *)(splinePaths + tmp_i7 + 0x1d8) * tmp_f1 +
                     *(float *)(splinePaths + tmp_i7 + 0x1cc);
        param_3[2] = tmp_f1 * *(float *)(splinePaths + tmp_i7 + 0x1dc) +
                     *(float *)(splinePaths + tmp_i7 + 0x1d0);
      }
      else {
        tmp_f1 = local_3c * 16.0;
        tmp_f10 = floorf(tmp_f1);
        local_54 = (int)ROUND(tmp_f10);
        if (local_54 < 0x10) {
          tmp_f1 = (tmp_f1 - (float)local_54) *
                  *(float *)(splinePaths + local_54 * 0x1c + param_5 * 0x394 + 0x1e0);
        }
        else {
          tmp_f1 = *(float *)(splinePaths + param_5 * 0x394 + 900);
          local_54 = 0xf;
        }
        if ((float)param_1[3] == 0.0) {
          vectoangles(local_54 * 0x1c + param_5 * 0x394 + 0xecbc94,param_3);
        }
        else {
          tmp_i7 = local_54 * 0x1c + param_5 * 0x394;
          local_34 = *(float *)(splinePaths + tmp_i7 + 0x1d4) * tmp_f1 +
                     *(float *)(splinePaths + tmp_i7 + 0x1c8);
          *param_3 = local_34;
          local_30 = *(float *)(splinePaths + tmp_i7 + 0x1d8) * tmp_f1 +
                     *(float *)(splinePaths + tmp_i7 + 0x1cc);
          param_3[1] = local_30;
          local_2c = tmp_f1 * *(float *)(splinePaths + tmp_i7 + 0x1dc) +
                     *(float *)(splinePaths + tmp_i7 + 0x1d0);
          param_3[2] = local_2c;
          BG_LinearPathOrigin2(param_1[3],&local_38,&local_3c,&local_34,tmp_b8);
          if ((float)param_1[3] < 0.0) {
            *param_3 = local_34 - *param_3;
            param_3[1] = local_30 - param_3[1];
            param_3[2] = local_2c - param_3[2];
          }
          else {
            *param_3 = *param_3 - local_34;
            param_3[1] = param_3[1] - local_30;
            param_3[2] = param_3[2] - local_2c;
          }
          vectoangles(param_3,param_3);
        }
      }
    }
  }
  return;
}

void BG_EvaluateTrajectoryDelta(uint32_t *param_1,int param_2,float *param_3)
{
  float tmp_f1;
  int tmp_i2;
  double tmp_d3;
  
  switch(*param_1) {
  case 0:
  case 1:
  case 0xc:
  case 0xd:
    break;
  case 2:
_L574:
    *param_3 = (float)param_1[6];
    param_3[1] = (float)param_1[7];
    param_3[2] = (float)param_1[8];
    return;
  case 3:
    if (param_2 <= (int)(param_1[2] + param_1[1])) goto _L574;
    break;
  default:
    Com_Error(2,"BG_EvaluateTrajectoryDelta: unknown trType: %i",param_1[1]);
    return;
  case 5:
    tmp_d3 = ((double)(param_2 - param_1[1]) / (double)(int)param_1[2]) * 3.141592653589793;
    tmp_d3 = cos(tmp_d3 + tmp_d3);
    tmp_f1 = (float)tmp_d3 * 0.5;
LAB_00022b96:
    *param_3 = (float)param_1[6] * tmp_f1;
    param_3[1] = (float)param_1[7] * tmp_f1;
    param_3[2] = tmp_f1 * (float)param_1[8];
    return;
  case 6:
    tmp_i2 = param_1[1];
    *param_3 = (float)param_1[6];
    param_3[1] = (float)param_1[7];
    tmp_f1 = (float)param_1[8];
    param_3[2] = tmp_f1;
    param_3[2] = tmp_f1 - (float)(int)GHIDRA_FIELD(cgs, 33788128, 4) * (float)(param_2 - tmp_i2) * 0.001;
    return;
  case 7:
    tmp_i2 = param_1[1];
    *param_3 = (float)param_1[6];
    param_3[1] = (float)param_1[7];
    tmp_f1 = (float)param_1[8];
    param_3[2] = tmp_f1;
    param_3[2] = tmp_f1 - (float)(int)GHIDRA_FIELD(cgs, 33788128, 4) * 0.3 * (float)(param_2 - tmp_i2) * 0.001;
    return;
  case 8:
    tmp_i2 = param_1[1];
    *param_3 = (float)param_1[6];
    param_3[1] = (float)param_1[7];
    tmp_f1 = (float)param_1[8];
    param_3[2] = tmp_f1;
    param_3[2] = tmp_f1 - (float)(int)GHIDRA_FIELD(cgs, 33788128, 4) * 0.2 * (float)(param_2 - tmp_i2) * 0.001;
    return;
  case 10:
    if (param_2 <= (int)(param_1[2] + param_1[1])) {
      tmp_f1 = (float)(param_2 - param_1[1]) * 0.001;
      tmp_f1 = tmp_f1 * tmp_f1;
      goto LAB_00022b96;
    }
    break;
  case 0xb:
    if (param_2 <= (int)(param_1[2] + param_1[1])) {
      tmp_f1 = (float)(param_2 - param_1[1]) * 0.001;
      goto LAB_00022b96;
    }
  }
  param_3[2] = 0.0;
  param_3[1] = 0.0;
  *param_3 = 0.0;
  return;
}

void BG_GetMarkDir(float *param_1,int param_2,float *param_3)
{
  int tmp_i1;
  long double tmp_l2;
  float local_44;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  if ((*param_1 < 0.001) && (param_1[1] < 0.001)) {
    *param_3 = *param_1;
    param_3[1] = param_1[1];
    param_3[2] = param_1[2];
    return;
  }
  tmp_l2 = (long double)VectorLengthSquared(param_2);
  if (tmp_l2 < (long double)1) {
    local_28 = 0.0;
    local_24 = 0.0;
    local_20 = 1.0;
  }
  else {
    VectorNormalize2(param_2,&local_28);
  }
  local_34 = -*param_1;
  local_30 = -param_1[1];
  local_2c = -param_1[2];
  VectorNormalize(&local_34);
  if (*(float *)(param_2 + 8) <= 0.8) {
    local_44 = 0.3;
  }
  else {
    local_44 = 0.7;
  }
  tmp_i1 = 0;
  if (local_2c * local_20 + local_30 * local_24 + local_34 * local_28 < local_44) {
    do {
      tmp_i1 = tmp_i1 + 1;
      local_34 = local_34 + local_28 * 0.5;
      local_30 = local_24 * 0.5 + local_30;
      local_2c = local_20 * 0.5 + local_2c;
      VectorNormalize(&local_34);
      if (local_44 <= local_2c * local_20 + local_30 * local_24 + local_34 * local_28) break;
    } while (tmp_i1 != 10);
  }
  *param_3 = local_34;
  param_3[1] = local_30;
  param_3[2] = local_2c;
  return;
}

void BG_AddPredictableEventToPlayerstate(uint32_t param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  uint tmp_u2;
  
  tmp_u2 = *(uint *)(param_3 + 0x6c);
  tmp_i1 = param_3 + (tmp_u2 & 3) * 4;
  *(uint32_t *)(tmp_i1 + 0x70) = param_1;
  *(uint32_t *)(tmp_i1 + 0x80) = param_2;
  *(uint *)(param_3 + 0x6c) = tmp_u2 + 1;
  return;
}

byte BG_GetPrimaryWeaponForPlayerState(int param_1)
{
  int tmp_i1;
  byte tmp_b2;
  
  param_1 = param_1 + 0x3d4;
  tmp_i1 = COM_BitCheck(param_1,5);
  tmp_b2 = 5;
  if (tmp_i1 == 0) {
    tmp_i1 = COM_BitCheck(param_1,0x1d);
    tmp_b2 = 0x1d;
    if (tmp_i1 == 0) {
      tmp_i1 = COM_BitCheck(param_1,0x21);
      tmp_b2 = 0x21;
      if (tmp_i1 == 0) {
        tmp_i1 = COM_BitCheck(param_1,6);
        tmp_b2 = 6;
        if (tmp_i1 == 0) {
          tmp_i1 = COM_BitCheck(param_1,0x1e);
          tmp_b2 = 0x1e;
          if (tmp_i1 == 0) {
            tmp_i1 = COM_BitCheck(param_1,0x18);
            tmp_b2 = 0x18;
            if (tmp_i1 == 0) {
              tmp_i1 = COM_BitCheck(param_1,0x17);
              tmp_b2 = 0x17;
              if (tmp_i1 == 0) {
                tmp_i1 = COM_BitCheck(param_1,0x16);
                tmp_b2 = 0x16;
                if (tmp_i1 == 0) {
                  tmp_i1 = COM_BitCheck(param_1,0x1f);
                  tmp_b2 = 0x1f;
                  if (tmp_i1 == 0) {
                    tmp_i1 = COM_BitCheck(param_1,10);
                    tmp_b2 = 10;
                    if (tmp_i1 == 0) {
                      tmp_i1 = COM_BitCheck(param_1,3);
                      tmp_b2 = 3;
                      if (tmp_i1 == 0) {
                        tmp_i1 = COM_BitCheck(param_1,8);
                        tmp_b2 = ~-(tmp_i1 == 0) & 8;
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
  return tmp_b2;
}

void BG_PlayerStateToEntityState(int param_1,uint32_t *param_2,uint32_t param_3,int param_4)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint32_t tmp_u5;
  uint tmp_u6;
  uint tmp_u7;
  uint tmp_u8;
  
  if (((*(int *)(param_1 + 4) == 2) || (*(int *)(param_1 + 4) == 5)) ||
     (*(int *)(param_1 + 0xd0) < -0xae)) {
    param_2[1] = 10;
  }
  else {
    param_2[1] = 1;
  }
  tmp_u5 = *(uint32_t *)(param_1 + 0xa0);
  param_2[3] = 1;
  *param_2 = tmp_u5;
  param_2[4] = param_3;
  tmp_f2 = *(float *)(param_1 + 0x14);
  param_2[6] = tmp_f2;
  tmp_f3 = *(float *)(param_1 + 0x18);
  param_2[7] = tmp_f3;
  tmp_f4 = *(float *)(param_1 + 0x1c);
  param_2[8] = tmp_f4;
  if (param_4 == 0) {
    param_2[9] = *(uint32_t *)(param_1 + 0x20);
    param_2[10] = *(uint32_t *)(param_1 + 0x24);
    tmp_u5 = *(uint32_t *)(param_1 + 0x28);
    param_2[0xc] = 1;
    param_2[0xb] = tmp_u5;
    param_2[0xf] = *(uint32_t *)(param_1 + 0xb0);
    param_2[0x10] = *(uint32_t *)(param_1 + 0xb4);
    param_2[0x11] = *(uint32_t *)(param_1 + 0xb8);
  }
  else {
    param_2[6] = (float)(int)ROUND(tmp_f2);
    param_2[7] = (float)(int)ROUND(tmp_f3);
    param_2[8] = (float)(int)ROUND(tmp_f4);
    tmp_f2 = *(float *)(param_1 + 0x20);
    param_2[9] = tmp_f2;
    tmp_f3 = *(float *)(param_1 + 0x24);
    param_2[10] = tmp_f3;
    tmp_f4 = *(float *)(param_1 + 0x28);
    param_2[9] = (float)(int)ROUND(tmp_f2);
    param_2[10] = (float)(int)ROUND(tmp_f3);
    param_2[0xc] = 1;
    param_2[0xb] = (float)(int)ROUND(tmp_f4);
    tmp_f2 = *(float *)(param_1 + 0xb0);
    param_2[0xf] = tmp_f2;
    tmp_f3 = *(float *)(param_1 + 0xb4);
    param_2[0x10] = tmp_f3;
    tmp_f4 = *(float *)(param_1 + 0xb8);
    param_2[0xf] = (float)(int)ROUND(tmp_f2);
    param_2[0x10] = (float)(int)ROUND(tmp_f3);
    param_2[0x11] = (float)(int)ROUND(tmp_f4);
  }
  tmp_f2 = (float)*(int *)(param_1 + 100);
  if (0x80 < *(int *)(param_1 + 100)) {
    tmp_f2 = tmp_f2 - 256.0;
  }
  param_2[0x21] = tmp_f2;
  if ((*(byte *)(param_1 + 0x6a) & 0x80) == 0) {
    tmp_f2 = 0.0;
  }
  else {
    tmp_f2 = (float)*(int *)(param_1 + 0xd8) * 0.005493164;
  }
  param_2[0x20] = tmp_f2;
  param_2[0x3b] = *(uint32_t *)(param_1 + 0x58);
  param_2[0x3c] = *(uint32_t *)(param_1 + 0x60);
  param_2[0x2b] = *(uint32_t *)(param_1 + 0xa0);
  tmp_u6 = *(uint *)(param_1 + 0x68);
  if ((tmp_u6 & 0x8000) == 0) {
    if (*(int *)(param_1 + 0x140) == 1) {
      tmp_u6 = tmp_u6 | 0x20;
      *(uint *)(param_1 + 0x68) = tmp_u6;
      *(uint32_t *)(param_1 + 0x16c) = 0;
      goto LAB_000231d4;
    }
    if (*(int *)(param_1 + 0x140) == 2) {
      tmp_u6 = tmp_u6 & 0xffffffdf;
      *(uint *)(param_1 + 0x68) = tmp_u6;
      *(uint32_t *)(param_1 + 0x16c) = 0;
      goto LAB_000231d4;
    }
  }
  tmp_u6 = tmp_u6 & 0xffffffdf;
  *(uint *)(param_1 + 0x68) = tmp_u6;
LAB_000231d4:
  param_2[2] = tmp_u6;
  tmp_u7 = tmp_u6 & 0xfffffffe;
  if (*(int *)(param_1 + 0xd0) < 1) {
    tmp_u7 = tmp_u6 | 1;
  }
  param_2[2] = tmp_u7;
  tmp_u6 = *(uint *)(param_1 + 0x470);
  tmp_u7 = *(uint *)(param_1 + 0x6c);
  if ((int)tmp_u6 < (int)tmp_u7) {
    tmp_u7 = tmp_u7 - 4;
    if ((int)tmp_u6 < (int)tmp_u7) {
      *(uint *)(param_1 + 0x470) = tmp_u7;
      tmp_u6 = tmp_u7;
    }
    tmp_i1 = param_1 + (tmp_u6 & 3) * 4;
    param_2[0x2e] = (tmp_u6 & 3) << 8 | *(uint *)(tmp_i1 + 0x70);
    param_2[0x2f] = *(uint32_t *)(tmp_i1 + 0x80);
    *(int *)(param_1 + 0x470) = *(int *)(param_1 + 0x470) + 1;
    tmp_u7 = *(uint *)(param_1 + 0x6c);
  }
  tmp_u6 = *(uint *)(param_1 + 0x90);
  if (tmp_u7 != tmp_u6) {
    tmp_u7 = param_2[0x30];
    tmp_u8 = tmp_u6;
    do {
      tmp_u6 = tmp_u8 + 1;
      tmp_i1 = param_1 + (tmp_u8 & 3) * 4;
      tmp_u8 = tmp_u7 & 3;
      tmp_u7 = tmp_u7 + 1;
      param_2[tmp_u8 + 0x31] = *(uint32_t *)(tmp_i1 + 0x70);
      param_2[tmp_u8 + 0x35] = *(uint32_t *)(tmp_i1 + 0x80);
      param_2[0x30] = tmp_u7;
      tmp_u8 = tmp_u6;
    } while (*(uint *)(param_1 + 0x6c) != tmp_u6);
  }
  *(uint *)(param_1 + 0x90) = tmp_u6;
  param_2[0x3a] = *(uint32_t *)(param_1 + 0xa4);
  param_2[0x25] = *(uint32_t *)(param_1 + 0x50);
  param_2[0x39] = 0;
  if (*(int *)(param_1 + 0x150) != 0) {
    param_2[0x39] = 1;
  }
  if (*(int *)(param_1 + 0x154) != 0) {
    param_2[0x39] = param_2[0x39] | 2;
  }
  if (*(int *)(param_1 + 0x158) != 0) {
    param_2[0x39] = param_2[0x39] | 4;
  }
  if (*(int *)(param_1 + 0x15c) != 0) {
    param_2[0x39] = param_2[0x39] | 8;
  }
  if (*(int *)(param_1 + 0x160) != 0) {
    param_2[0x39] = param_2[0x39] | 0x10;
  }
  if (*(int *)(param_1 + 0x164) != 0) {
    param_2[0x39] = param_2[0x39] | 0x20;
  }
  if (*(int *)(param_1 + 0x168) != 0) {
    param_2[0x39] = param_2[0x39] | 0x40;
  }
  if (*(int *)(param_1 + 0x16c) != 0) {
    param_2[0x39] = param_2[0x39] | 0x80;
  }
  if (*(int *)(param_1 + 0x170) != 0) {
    param_2[0x39] = param_2[0x39] | 0x100;
  }
  if (*(int *)(param_1 + 0x174) != 0) {
    param_2[0x39] = param_2[0x39] | 0x200;
  }
  if (*(int *)(param_1 + 0x178) != 0) {
    param_2[0x39] = param_2[0x39] | 0x400;
  }
  if (*(int *)(param_1 + 0x17c) != 0) {
    param_2[0x39] = param_2[0x39] | 0x800;
  }
  if (*(int *)(param_1 + 0x180) != 0) {
    param_2[0x39] = param_2[0x39] | 0x1000;
  }
  if (*(int *)(param_1 + 0x184) != 0) {
    param_2[0x39] = param_2[0x39] | 0x2000;
  }
  if (*(int *)(param_1 + 0x188) != 0) {
    param_2[0x39] = param_2[0x39] | 0x4000;
  }
  if (*(int *)(param_1 + 0x18c) != 0) {
    param_2[0x39] = param_2[0x39] | 0x8000;
  }
  param_2[0x41] = *(uint32_t *)(param_1 + 0x41c);
  param_2[0x42] = *(uint32_t *)(param_1 + 0x420);
  param_2[0x46] = *(uint32_t *)(param_1 + 0x5a8);
  if (*(int *)(param_1 + 4) != 2) {
    param_2[0x26] = *(uint32_t *)(param_1 + 0x398);
    param_2[0x27] = *(uint32_t *)(param_1 + 0xd0);
  }
  return;
}

uint BG_DuplicateWeapon(uint param_1)
{
  uint tmp_u1;
  
  if (param_1 == 0x25) {
    return 0x24;
  }
  if (param_1 < 0x26) {
    tmp_u1 = 4;
    if (param_1 != 9) {
      return param_1;
    }
  }
  else {
    tmp_u1 = 0x18;
    if ((param_1 != 0x27) && (tmp_u1 = 0x1e, param_1 != 0x28)) {
      return param_1;
    }
  }
  return tmp_u1;
}

int * BG_ValidStatWeapon(uint param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  
  if ((param_1 - 1 < 0x33) &&
     ((0x11 < param_1 - 0xb || ((1 << ((byte)(param_1 - 0xb) & 0x1f) & 0x202a3U) == 0)))) {
    switch(param_1) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
      if (param_1 != 0x25) {
        if (param_1 < 0x26) {
          if (param_1 != 9) {
LAB_00023578:
            tmp_pi2 = (int *)(bg_itemlist + 0x38);
            tmp_i1 = GHIDRA_FIELD(bg_itemlist, 56, 4);
            while (tmp_i1 != 0) {
              while (tmp_pi2[9] == 1) {
                if (param_1 == tmp_pi2[10]) {
                  return tmp_pi2;
                }
                tmp_pi2 = tmp_pi2 + 0xe;
                if (*tmp_pi2 == 0) goto LAB_000235ad;
              }
              tmp_pi2 = tmp_pi2 + 0xe;
              tmp_i1 = *tmp_pi2;
            }
LAB_000235ad:
            Com_Printf("^1ERROR : ^7BG_FindItemForWeapon() ^9no item for weapon %i (%s^9)\n",param_1
                       ,param_1 * 0x6b0 + 0xeb1474);
            return (int *)0x0;
          }
        }
        else if (1 < param_1 - 0x27) goto LAB_00023578;
      }
    }
  }
  return (int *)0x0;
}

int BG_WeaponForMOD(int param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  
  if (param_1 == 0x3f) {
    return 1;
  }
  tmp_pi2 = (int *)(ammoTableMP + 0x3c);
  tmp_i1 = 0;
  do {
    if (*tmp_pi2 == param_1) {
      return tmp_i1;
    }
    tmp_i1 = tmp_i1 + 1;
    tmp_pi2 = tmp_pi2 + 0x12;
  } while (tmp_i1 != 0x34);
  return 0;
}

uint8_t * BG_Find_PathCorner(uint32_t param_1)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  
  if (0 < numPathCorners) {
    tmp_pu2 = pathCorners;
    tmp_i3 = 0;
    do {
      tmp_i1 = Q_stricmp(tmp_pu2,param_1);
      if (tmp_i1 == 0) {
        return tmp_pu2;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu2 = tmp_pu2 + 0x4c;
    } while (tmp_i3 < numPathCorners);
  }
  return (uint8_t *)0x0;
}

void BG_AddPathCorner(uint32_t param_1,uint32_t *param_2)
{
  int tmp_i1;
  
  if (0x1ff < numPathCorners) {
    Com_Error(2,"MAX PATH CORNERS (%i) hit",0x200);
  }
  tmp_i1 = numPathCorners * 0x4c;
  *(uint32_t *)(pathCorners + tmp_i1 + 0x40) = *param_2;
  *(uint32_t *)(pathCorners + tmp_i1 + 0x44) = param_2[1];
  *(uint32_t *)(pathCorners + tmp_i1 + 0x48) = param_2[2];
  Q_strncpyz(pathCorners + tmp_i1,param_1,0x40);
  numPathCorners = numPathCorners + 1;
  return;
}

uint8_t * BG_Find_Spline(uint32_t param_1)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  
  if (0 < numSplinePaths) {
    tmp_pu2 = splinePaths;
    tmp_i3 = 0;
    do {
      tmp_i1 = Q_stricmp(tmp_pu2,param_1);
      if (tmp_i1 == 0) {
        return tmp_pu2;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu2 = tmp_pu2 + 0x394;
    } while (tmp_i3 < numSplinePaths);
  }
  return (uint8_t *)0x0;
}

uint8_t * BG_AddSplinePath(uint32_t param_1,uint8_t *param_2,uint32_t *param_3)
{
  uint tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  
  if (0x1ff < numSplinePaths) {
    Com_Error(2,"MAX SPLINES (%i) hit",0x200);
  }
  tmp_i2 = numSplinePaths;
  tmp_i3 = numSplinePaths * 0x394;
  tmp_pu4 = splinePaths + tmp_i3;
  tmp_u1 = 0;
  do {
    *(uint32_t *)(tmp_pu4 + tmp_u1) = 0;
    *(uint32_t *)(tmp_i3 + 0xecbac4 + tmp_u1) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x390);
  *(uint32_t *)(tmp_pu4 + tmp_u1) = 0;
  tmp_i3 = tmp_i2 * 0x394;
  *(uint32_t *)(splinePaths + tmp_i3 + 0x40) = *param_3;
  *(uint32_t *)(splinePaths + tmp_i3 + 0x44) = param_3[1];
  *(uint32_t *)(splinePaths + tmp_i3 + 0x48) = param_3[2];
  Q_strncpyz(tmp_pu4,param_1,0x40);
  if (param_2 == (uint8_t *)0x0) {
    param_2 = &g_unk_0011d841;
  }
  tmp_i2 = tmp_i2 * 0x394;
  Q_strncpyz(tmp_i2 + 0xecbb0c,param_2,0x40);
  *(uint32_t *)(splinePaths + tmp_i2 + 0x1c4) = 0;
  numSplinePaths = numSplinePaths + 1;
  return tmp_pu4;
}

void BG_AddSplineControl(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x1c4);
  if (3 < tmp_i1) {
    Com_Error(2,"MAX SPLINE CONTROLS (%i) hit",4);
    tmp_i1 = *(int *)(param_1 + 0x1c4);
  }
  Q_strncpyz(param_1 + 0x94 + tmp_i1 * 0x4c,param_2,0x40);
  *(int *)(param_1 + 0x1c4) = *(int *)(param_1 + 0x1c4) + 1;
  return;
}

long double BG_SplineLength(uint32_t param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  long double tmp_l6;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_f1 = 0.0;
  tmp_i5 = 0x65;
  local_64 = 0.0;
  local_5c = 0.0;
  local_60 = 0.0;
  local_58 = 0.0;
  do {
    BG_CalculateSpline_r(param_1,&local_34,&local_28,tmp_f1);
    tmp_f4 = (local_28 - local_34) * tmp_f1 + local_34;
    tmp_f3 = (local_24 - local_30) * tmp_f1 + local_30;
    tmp_f2 = (local_20 - local_2c) * tmp_f1 + local_2c;
    if (tmp_f1 != 0.0) {
      local_34 = tmp_f4 - local_60;
      local_30 = tmp_f3 - local_5c;
      local_2c = tmp_f2 - local_64;
      tmp_l6 = (long double)VectorLength(&local_34);
      local_58 = (float)(tmp_l6 + (long double)local_58);
    }
    tmp_i5 = tmp_i5 + -1;
    tmp_f1 = tmp_f1 + 0.01;
    local_64 = tmp_f2;
    local_60 = tmp_f4;
    local_5c = tmp_f3;
  } while (tmp_i5 != 0);
  return (long double)local_58;
}

void BG_BuildSplinePaths(void)
{
  char *tmp_pc1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  char *tmp_pc4;
  int tmp_i5;
  long double tmp_l6;
  int local_34;
  char *local_30;
  int local_28;
  
  if (0 < numSplinePaths) {
    local_30 = splinePaths + 0x4c;
    local_28 = 0;
    tmp_i5 = numSplinePaths;
    do {
      if (*local_30 != '\0') {
        tmp_pc1 = local_30 + -0x4c;
        if (*(int *)(local_30 + 0x178) < 1) {
LAB_00023c17:
          tmp_pu3 = splinePaths;
          tmp_i5 = 0;
          do {
            tmp_i2 = Q_stricmp(tmp_pu3,local_30);
            if (tmp_i2 == 0) {
              *(uint8_t **)(local_30 + 0x40) = tmp_pu3;
              tmp_l6 = (long double)BG_SplineLength(tmp_pc1);
              *(float *)(local_30 + 0x33c) = (float)tmp_l6;
              BG_ComputeSegments(tmp_pc1);
              tmp_i5 = numSplinePaths;
              goto LAB_00023c72;
            }
            tmp_i5 = tmp_i5 + 1;
            tmp_pu3 = tmp_pu3 + 0x394;
          } while (tmp_i5 < numSplinePaths);
        }
        else {
          tmp_pc4 = local_30 + 0x48;
          local_34 = 0;
          do {
            if (0 < numPathCorners) {
              tmp_pu3 = pathCorners;
              tmp_i5 = 0;
              do {
                tmp_i2 = Q_stricmp(tmp_pu3,tmp_pc4);
                if (tmp_i2 == 0) {
                  *(uint32_t *)(tmp_pc4 + 0x40) = *(uint32_t *)(tmp_pu3 + 0x40);
                  *(uint32_t *)(tmp_pc4 + 0x44) = *(uint32_t *)(tmp_pu3 + 0x44);
                  *(uint32_t *)(tmp_pc4 + 0x48) = *(uint32_t *)(tmp_pu3 + 0x48);
                  goto LAB_00023bf2;
                }
                tmp_i5 = tmp_i5 + 1;
                tmp_pu3 = tmp_pu3 + 0x4c;
              } while (tmp_i5 < numPathCorners);
            }
            Com_Printf("^1Cant find control point (%s) for spline (%s)\n",tmp_pc4,tmp_pc1);
LAB_00023bf2:
            local_34 = local_34 + 1;
            tmp_pc4 = tmp_pc4 + 0x4c;
          } while (local_34 < *(int *)(local_30 + 0x178));
          if (0 < numSplinePaths) goto LAB_00023c17;
        }
        Com_Printf("^1Cant find target point (%s) for spline (%s)\n",local_30,tmp_pc1);
        tmp_i5 = numSplinePaths;
      }
LAB_00023c72:
      local_28 = local_28 + 1;
      local_30 = local_30 + 0x394;
    } while (local_28 < tmp_i5);
    if (0 < tmp_i5) {
      tmp_pu3 = splinePaths;
      tmp_i2 = 0;
      do {
        if (*(int *)(tmp_pu3 + 0x8c) != 0) {
          *(uint8_t **)(*(int *)(tmp_pu3 + 0x8c) + 0x90) = tmp_pu3;
        }
        tmp_i2 = tmp_i2 + 1;
        tmp_pu3 = tmp_pu3 + 0x394;
      } while (tmp_i2 != tmp_i5);
    }
  }
  return;
}

uint8_t * BG_GetSplineData(int param_1,uint *param_2)
{
  bool tmp_b1;
  
  tmp_b1 = param_1 < 0;
  if (tmp_b1) {
    param_1 = -param_1;
  }
  param_1 = param_1 + -1;
  *param_2 = (uint)tmp_b1;
  if ((param_1 != -1) && (param_1 < numSplinePaths)) {
    return splinePaths + param_1 * 0x394;
  }
  return (uint8_t *)0x0;
}

int BG_MaxAmmoForWeapon(int param_1,int param_2)
{
  byte tmp_b1;
  uint tmp_u2;
  
  tmp_u2 = *(uint *)(param_2 + 0x10) >> 1 & 1;
  switch(param_1) {
  case 1:
    if ((*(uint *)(param_2 + 0x10) & 0x20) == 0) {
      return 1;
    }
    return GHIDRA_FIELD(ammoTableMP, 72, 4);
  case 2:
  case 7:
  case 10:
  case 0xe:
  case 0x16:
  case 0x17:
  case 0x26:
    goto _L859;
  case 3:
  case 8:
    tmp_b1 = *(byte *)(param_2 + 8);
    goto LAB_00023db4;
  case 4:
  case 9:
    if (((*(byte *)(param_2 + 4) & 2) == 0) && ((*(byte *)(param_2 + 8) & 2) != 0)) {
      return *(int *)(ammoTableMP + param_1 * 0x48) + 1;
    }
    break;
  case 5:
    return GHIDRA_FIELD(ammoTableMP, 360, 4);
  case 6:
    if ((*(byte *)(param_2 + 0x14) & 0x20) == 0) {
      return GHIDRA_FIELD(ammoTableMP, 432, 4);
    }
    return GHIDRA_FIELD(ammoTableMP, 432, 4) + 0x32;
  case 0xb:
  case 0x2b:
    tmp_b1 = *(byte *)(param_2 + 8) & 4;
    goto joined_r0x00023e74;
  case 0x18:
  case 0x1e:
  case 0x1f:
  case 0x27:
  case 0x28:
  case 0x29:
    tmp_b1 = *(byte *)(param_2 + 0x18);
LAB_00023db4:
    if ((tmp_b1 & 2) != 0) {
      tmp_u2 = 1;
    }
_L859:
    return tmp_u2 * *(int *)(ammoTableMP + param_1 * 0x48 + 8) +
           *(int *)(ammoTableMP + param_1 * 0x48);
  case 0x1d:
  case 0x2e:
    if ((*(byte *)(param_2 + 0x14) & 0x20) != 0) {
      return *(int *)(ammoTableMP + param_1 * 0x48 + 8) + *(int *)(ammoTableMP + param_1 * 0x48);
    }
    break;
  case 0x21:
  case 0x2a:
    tmp_b1 = *(byte *)(param_2 + 0x14) & 0x20;
joined_r0x00023e74:
    if (tmp_b1 != 0) {
      return *(int *)(ammoTableMP + param_1 * 0x48) + 2;
    }
    break;
  case 0x24:
  case 0x25:
    if ((*(byte *)(param_2 + 4) & 2) != 0) {
      return *(int *)(ammoTableMP + param_1 * 0x48) + 4;
    }
  }
  return *(int *)(ammoTableMP + param_1 * 0x48);
}

bool BG_AddMagicAmmo(int param_1,int param_2,int param_3,int param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  bool tmp_b5;
  uint tmp_u6;
  int tmp_i7;
  int tmp_i8;
  int *tmp_pi9;
  int tmp_i10;
  int tmp_i11;
  int *tmp_pi12;
  int tmp_i13;
  bool tmp_b14;
  
  tmp_b14 = (*(uint *)(param_1 + 0x68) & 0x1000) != 0;
  if (tmp_b14) {
    *(uint *)(param_1 + 0x68) = *(uint *)(param_1 + 0x68) & 0xffffefff;
  }
  tmp_i13 = 0;
  if (GHIDRA_FIELD(cgs, 33787756, 4) == 0) {
    tmp_u6 = *(int *)(param_1 + 0xe4) - 1;
    tmp_i13 = 5;
    if (tmp_u6 < 4) {
      tmp_i13 = *(int *)(CSWTCH_91 + tmp_u6 * 4);
    }
    tmp_u6 = *(uint *)(param_2 + 0x10);
    tmp_f4 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 96, 4);
    if (((float)GHIDRA_FIELD(jP_GrenadesPerLevel, 96, 4) != (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 100, 4)) &&
       ((tmp_u6 & 2) != 0)) {
      tmp_f4 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 100, 4);
    }
    if (((float)GHIDRA_FIELD(jP_GrenadesPerLevel, 104, 4) != (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 100, 4)) &&
       ((tmp_u6 & 4) != 0)) {
      tmp_f4 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 104, 4);
    }
    if (((float)GHIDRA_FIELD(jP_GrenadesPerLevel, 108, 4) != (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 104, 4)) &&
       ((tmp_u6 & 8) != 0)) {
      tmp_f4 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 108, 4);
    }
    if (((float)GHIDRA_FIELD(jP_GrenadesPerLevel, 112, 4) != (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 108, 4)) &&
       ((tmp_u6 & 0x10) != 0)) {
      tmp_f4 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 112, 4);
    }
    if (((float)GHIDRA_FIELD(jP_GrenadesPerLevel, 116, 4) != (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 112, 4)) &&
       ((tmp_u6 & 0x20) != 0)) {
      tmp_f4 = (float)GHIDRA_FIELD(jP_GrenadesPerLevel, 116, 4);
    }
    tmp_i7 = tmp_i13 * 0x18;
    tmp_f1 = *(float *)(jP_GrenadesPerLevel + tmp_i7);
    tmp_f2 = *(float *)(jP_GrenadesPerLevel + tmp_i7 + 4);
    tmp_u6 = *(uint *)(param_2 + tmp_i13 * 4);
    if ((tmp_f1 != tmp_f2) && ((tmp_u6 & 2) != 0)) {
      tmp_f1 = tmp_f2;
    }
    tmp_f3 = *(float *)(jP_GrenadesPerLevel + tmp_i7 + 8);
    if ((tmp_f3 != tmp_f2) && ((tmp_u6 & 4) != 0)) {
      tmp_f1 = tmp_f3;
    }
    tmp_f2 = *(float *)(jP_GrenadesPerLevel + tmp_i7 + 0xc);
    if ((tmp_f2 != tmp_f3) && ((tmp_u6 & 8) != 0)) {
      tmp_f1 = tmp_f2;
    }
    tmp_f3 = *(float *)(jP_GrenadesPerLevel + tmp_i7 + 0x10);
    if ((tmp_f3 != tmp_f2) && ((tmp_u6 & 0x10) != 0)) {
      tmp_f1 = tmp_f3;
    }
    if ((*(float *)(jP_GrenadesPerLevel + tmp_i7 + 0x14) != tmp_f3) && ((tmp_u6 & 0x20) != 0)) {
      tmp_f1 = *(float *)(jP_GrenadesPerLevel + tmp_i7 + 0x14);
    }
    tmp_i13 = (int)ROUND(tmp_f1) + (int)ROUND(tmp_f4);
  }
  if (param_3 == 1) {
    tmp_i7 = 4;
  }
  else {
    tmp_i7 = (uint)(param_3 == 2) * 9;
  }
  tmp_b5 = tmp_b14;
  if (GHIDRA_FIELD(bg_itemlist, 56, 4) == 0) {
    tmp_i10 = *(int *)(param_1 + 0x290);
    if (tmp_i10 < tmp_i13) {
      tmp_i8 = 0;
      goto LAB_000240c4;
    }
LAB_00024114:
    tmp_i13 = 0;
LAB_00024116:
    tmp_i7 = 1;
    if ((*(byte *)(param_2 + 0x10) & 0x20) != 0) {
      tmp_i7 = GHIDRA_FIELD(ammoTableMP, 72, 4);
    }
    if (tmp_i10 < tmp_i7) {
      if (param_4 == 0) goto LAB_000240d0;
      tmp_i13 = param_1 + tmp_i13 * 4;
      *(int *)(tmp_i13 + 0x290) = tmp_i10 + param_4;
      COM_BitSet(param_1 + 0x3d4,1);
      if (tmp_i7 < *(int *)(tmp_i13 + 0x290)) {
        *(int *)(tmp_i13 + 0x290) = tmp_i7;
        tmp_b5 = true;
        tmp_b14 = true;
      }
      else {
        tmp_b5 = true;
        tmp_b14 = true;
      }
    }
    tmp_i13 = param_1 + 0x3d4;
    tmp_i7 = COM_BitCheck(tmp_i13,0xb);
    if (tmp_i7 != 0) {
      tmp_i7 = GHIDRA_FIELD(ammoTableMP, 792, 4);
      if ((*(byte *)(param_2 + 8) & 4) != 0) {
        tmp_i7 = GHIDRA_FIELD(ammoTableMP, 792, 4) + 2;
      }
      if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
        tmp_pi9 = (int *)(bg_itemlist + 0x38);
        do {
          if ((tmp_pi9[9] == 1) && (tmp_pi9[10] == 0xb)) {
            tmp_i10 = tmp_pi9[0xd];
            goto LAB_00024234;
          }
          tmp_pi9 = tmp_pi9 + 0xe;
        } while (*tmp_pi9 != 0);
      }
      tmp_i10 = 0;
LAB_00024234:
      tmp_i10 = param_1 + tmp_i10 * 4;
      if (*(int *)(tmp_i10 + 0x290) < tmp_i7) {
        if (param_4 == 0) goto LAB_000240d0;
        tmp_i8 = *(int *)(tmp_i10 + 0x290) + param_4;
        if (tmp_i7 < tmp_i8) {
          tmp_b5 = true;
          *(int *)(tmp_i10 + 0x290) = tmp_i7;
          tmp_b14 = true;
        }
        else {
          *(int *)(tmp_i10 + 0x290) = tmp_i8;
          tmp_b5 = true;
          tmp_b14 = true;
        }
      }
    }
    tmp_i7 = COM_BitCheck(tmp_i13,0x2b);
    if ((tmp_i7 != 0) && ((GHIDRA_FIELD(cgs, 33787480, 4) & 2) == 0)) {
      tmp_i7 = 1;
      if (((GHIDRA_FIELD(cgs, 33787480, 4) & 4) == 0) &&
         (tmp_i7 = GHIDRA_FIELD(ammoTableMP, 3096, 4), (*(byte *)(param_2 + 8) & 4) != 0)) {
        tmp_i7 = GHIDRA_FIELD(ammoTableMP, 3096, 4) + 2;
      }
      tmp_i10 = 0;
      if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
        tmp_pi9 = (int *)(bg_itemlist + 0x38);
        do {
          if ((tmp_pi9[9] == 1) && (tmp_pi9[10] == 0x2b)) {
            tmp_i10 = tmp_pi9[0xd];
            break;
          }
          tmp_pi9 = tmp_pi9 + 0xe;
        } while (*tmp_pi9 != 0);
      }
      tmp_i10 = param_1 + tmp_i10 * 4;
      if (*(int *)(tmp_i10 + 0x290) < tmp_i7) {
        if (param_4 == 0) goto LAB_000240d0;
        tmp_i8 = *(int *)(tmp_i10 + 0x290) + param_4;
        if (tmp_i7 < tmp_i8) {
          tmp_b5 = true;
          *(int *)(tmp_i10 + 0x290) = tmp_i7;
          tmp_b14 = true;
        }
        else {
          *(int *)(tmp_i10 + 0x290) = tmp_i8;
          tmp_b5 = true;
          tmp_b14 = true;
        }
      }
    }
    tmp_i7 = COM_BitCheck(tmp_i13,0x2f);
    if (tmp_i7 != 0) {
      if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
        tmp_pi9 = (int *)(bg_itemlist + 0x38);
        do {
          if ((tmp_pi9[9] == 1) && (tmp_pi9[10] == 0x2f)) {
            tmp_i7 = tmp_pi9[0xd];
            goto LAB_00024690;
          }
          tmp_pi9 = tmp_pi9 + 0xe;
        } while (*tmp_pi9 != 0);
      }
      tmp_i7 = 0;
LAB_00024690:
      tmp_i7 = param_1 + tmp_i7 * 4;
      if (*(int *)(tmp_i7 + 0x290) < (int)GHIDRA_FIELD(ammoTableMP, 3384, 4)) {
        if (param_4 == 0) goto LAB_000240d0;
        tmp_i10 = *(int *)(tmp_i7 + 0x290) + param_4;
        if ((int)GHIDRA_FIELD(ammoTableMP, 3384, 4) < tmp_i10) {
          tmp_b5 = true;
          *(uint32_t *)(tmp_i7 + 0x290) = GHIDRA_FIELD(ammoTableMP, 3384, 4);
          tmp_b14 = true;
        }
        else {
          *(int *)(tmp_i7 + 0x290) = tmp_i10;
          tmp_b5 = true;
          tmp_b14 = true;
        }
      }
    }
    if (-1 < reloadableWeapons) {
      tmp_pi9 = &g_unk_0013e744;
      tmp_i7 = reloadableWeapons;
      do {
        tmp_i10 = COM_BitCheck(tmp_i13,tmp_i7);
        if (tmp_i10 != 0) {
          tmp_i10 = BG_MaxAmmoForWeapon(tmp_i7,param_2);
          if (tmp_i7 == 6) {
            if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
              tmp_pi12 = (int *)(bg_itemlist + 0x38);
              do {
                if ((tmp_pi12[9] == 1) && (tmp_pi12[10] == 6)) {
                  tmp_i7 = tmp_pi12[0xc];
                  goto LAB_000244bf;
                }
                tmp_pi12 = tmp_pi12 + 0xe;
              } while (*tmp_pi12 != 0);
            }
            tmp_i7 = 0;
LAB_000244bf:
            tmp_i7 = param_1 + tmp_i7 * 4;
            if (*(int *)(tmp_i7 + 0x290) < tmp_i10) {
              if (param_4 == 0) goto LAB_000240d0;
              *(int *)(tmp_i7 + 0x290) = tmp_i10;
              tmp_b14 = true;
            }
          }
          else if (tmp_i7 == 5) {
            if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
              tmp_pi12 = (int *)(bg_itemlist + 0x38);
              do {
                if ((tmp_pi12[9] == 1) && (tmp_pi12[10] == 5)) {
                  tmp_i7 = tmp_pi12[0xc];
                  goto LAB_00024527;
                }
                tmp_pi12 = tmp_pi12 + 0xe;
              } while (*tmp_pi12 != 0);
            }
            tmp_i7 = 0;
LAB_00024527:
            tmp_i7 = param_1 + tmp_i7 * 4;
            if (*(int *)(tmp_i7 + 0x290) < tmp_i10) {
              if (param_4 == 0) goto LAB_000240d0;
              tmp_i8 = *(int *)(tmp_i7 + 0x290) + param_4;
              if (tmp_i8 < tmp_i10) {
                *(int *)(tmp_i7 + 0x290) = tmp_i8;
                goto LAB_0002444d;
              }
              *(int *)(tmp_i7 + 0x290) = tmp_i10;
              tmp_b14 = true;
            }
          }
          else {
            tmp_pi12 = (int *)(bg_itemlist + 0x38);
            tmp_i8 = GHIDRA_FIELD(bg_itemlist, 56, 4);
            while (tmp_i8 != 0) {
              if ((tmp_pi12[9] == 1) && (tmp_i7 == tmp_pi12[10])) {
                tmp_i8 = tmp_pi12[0xc];
                goto LAB_000243f3;
              }
              tmp_pi12 = tmp_pi12 + 0xe;
              tmp_i8 = *tmp_pi12;
            }
            tmp_i8 = 0;
LAB_000243f3:
            tmp_i8 = param_1 + tmp_i8 * 4;
            if (*(int *)(tmp_i8 + 400) < tmp_i10) {
              if (param_4 == 0) goto LAB_000240d0;
              if ((tmp_i7 - 0x2cU < 2) || (tmp_i11 = param_4, tmp_i7 - 0x22U < 2)) {
                tmp_i11 = param_4 * 2;
              }
              tmp_i7 = tmp_i11 * *(int *)(ammoTableMP + tmp_i7 * 0x48 + 8) + *(int *)(tmp_i8 + 400);
              if (tmp_i10 < tmp_i7) {
                *(int *)(tmp_i8 + 400) = tmp_i10;
              }
              else {
                *(int *)(tmp_i8 + 400) = tmp_i7;
              }
LAB_0002444d:
              tmp_b14 = true;
            }
          }
        }
        tmp_i7 = *tmp_pi9;
        tmp_pi9 = tmp_pi9 + 1;
        if (tmp_i7 < 0) {
          return tmp_b14;
        }
      } while( true );
    }
  }
  else {
    tmp_pi9 = (int *)(bg_itemlist + 0x38);
    tmp_pi12 = tmp_pi9;
    do {
      if ((tmp_pi12[9] == 1) && (tmp_i7 == tmp_pi12[10])) {
        tmp_i8 = tmp_pi12[0xd];
        goto LAB_000240b2;
      }
      tmp_pi12 = tmp_pi12 + 0xe;
    } while (*tmp_pi12 != 0);
    tmp_i8 = 0;
LAB_000240b2:
    tmp_i10 = *(int *)(param_1 + (tmp_i8 + 0xa4) * 4);
    if (tmp_i13 <= tmp_i10) {
LAB_000240fb:
      do {
        while (tmp_pi9[9] == 1) {
          if (tmp_pi9[10] == 1) {
            tmp_i13 = tmp_pi9[0xd];
            tmp_i10 = *(int *)(param_1 + (tmp_i13 + 0xa4) * 4);
            goto LAB_00024116;
          }
          tmp_pi9 = tmp_pi9 + 0xe;
          if (*tmp_pi9 == 0) goto LAB_0002410a;
        }
        tmp_pi9 = tmp_pi9 + 0xe;
      } while (*tmp_pi9 != 0);
LAB_0002410a:
      tmp_i10 = *(int *)(param_1 + 0x290);
      goto LAB_00024114;
    }
LAB_000240c4:
    if (param_4 != 0) {
      tmp_i8 = param_1 + tmp_i8 * 4;
      *(int *)(tmp_i8 + 0x290) = tmp_i10 + param_4;
      COM_BitSet(param_1 + 0x3d4,tmp_i7);
      if (tmp_i13 < *(int *)(tmp_i8 + 0x290)) {
        *(int *)(tmp_i8 + 0x290) = tmp_i13;
      }
      if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
        tmp_b5 = true;
        tmp_b14 = true;
        tmp_pi9 = (int *)(bg_itemlist + 0x38);
        goto LAB_000240fb;
      }
      tmp_b5 = true;
      tmp_i13 = 0;
      tmp_b14 = true;
      tmp_i10 = *(int *)(param_1 + 0x290);
      goto LAB_00024116;
    }
LAB_000240d0:
    tmp_b5 = true;
  }
  return tmp_b5;
}

uint BG_CanItemBeGrabbed(int param_1,int param_2,uint32_t param_3)
{
  int tmp_i1;
  uint tmp_u2;
  int tmp_i3;
  int *tmp_pi4;
  int tmp_i5;
  
  tmp_i5 = *(int *)(param_1 + 0xa4);
  if ((tmp_i5 < 1) || (bg_numItems <= tmp_i5)) {
    Com_Error(2,"BG_CanItemBeGrabbed: index out of range");
    return 0;
  }
  switch(*(uint32_t *)(bg_itemlist + tmp_i5 * 0x38 + 0x24)) {
  case 0:
    Com_Error(2,"BG_CanItemBeGrabbed: IT_BAD");
    tmp_u2 = 0;
    break;
  case 1:
    if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x28) != 0xc) {
      return 1;
    }
    goto LAB_00024a9d;
  case 2:
    tmp_i1 = *(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x28);
    if (tmp_i1 != 0xc) {
      tmp_i3 = *(int *)(param_2 + (tmp_i1 + 100) * 4);
      tmp_i1 = BG_MaxAmmoForWeapon(tmp_i1,param_3);
      if (tmp_i1 <= tmp_i3) {
        return 0;
      }
      tmp_i1 = 0;
      do {
        tmp_i3 = COM_BitCheck(param_2 + 0x3d4,tmp_i1);
        if (tmp_i3 != 0) {
          if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
            tmp_pi4 = (int *)(bg_itemlist + 0x38);
            do {
              if ((tmp_pi4[9] == 1) && (tmp_i1 == tmp_pi4[10])) {
                tmp_i3 = tmp_pi4[0xc];
                goto LAB_00024a1b;
              }
              tmp_pi4 = tmp_pi4 + 0xe;
            } while (*tmp_pi4 != 0);
          }
          tmp_i3 = 0;
LAB_00024a1b:
          if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x28) == tmp_i3) {
            return 1;
          }
        }
        tmp_i1 = tmp_i1 + 1;
        if (tmp_i1 == 0x34) {
          return 0;
        }
      } while( true );
    }
LAB_00024a9d:
    tmp_u2 = BG_AddMagicAmmo();
    return tmp_u2;
  case 3:
    tmp_u2 = (uint)(*(int *)(param_2 + 0xd0) < *(int *)(param_2 + 0xf4));
    break;
  case 4:
    return 1;
  case 5:
    if (*(int *)(param_2 + 300) == 1) {
      if (*(int *)(param_1 + 0xf4) < 1) {
        return 0;
      }
      if (*(int *)(param_2 + 0x168) != 0) {
        return 0;
      }
      if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x2c) == 6) {
        return 1;
      }
      if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x2c) != 5) {
        return 0;
      }
    }
    else {
      if (*(int *)(param_2 + 300) != 2) {
        return 0;
      }
      if (*(int *)(param_1 + 0xf4) < 1) {
        return 0;
      }
      if (*(int *)(param_2 + 0x164) != 0) {
        return 0;
      }
      if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x2c) == 5) {
        return 1;
      }
      if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x2c) != 6) {
        return 0;
      }
    }
    tmp_u2 = 0;
    if (*(int *)(param_1 + 0x90) != 0) {
      return 1;
    }
    break;
  case 6:
    tmp_i3 = tmp_i5 * 0x38;
    tmp_i1 = *(int *)(bg_itemlist + tmp_i3 + 0x2c);
    if (tmp_i1 == 7) {
      if (*(int *)(bg_itemlist + tmp_i3 + 0x20) == *(int *)(param_2 + 0x420)) {
        tmp_i5 = *(int *)(bg_itemlist + tmp_i3 + 0x30);
        tmp_i1 = *(int *)(param_2 + 300);
        if (((*(byte *)(param_2 + 0x6a) & 1) != 0) && (tmp_i5 == tmp_i1)) {
          return 1;
        }
      }
      else {
        tmp_i5 = *(int *)(bg_itemlist + tmp_i3 + 0x30);
        tmp_i1 = *(int *)(param_2 + 300);
      }
      if (tmp_i5 == tmp_i1) {
        return 0;
      }
      if (*(int *)(param_2 + 0x420) == 4) {
        return (uint)(*(int *)(param_2 + 0x16c) == 0);
      }
      return 0;
    }
    if (tmp_i1 == 3) {
      if ((*(byte *)(param_2 + 0x69) & 0x10) == 0) {
        return 0;
      }
    }
    else {
      if (tmp_i1 == 2) {
        tmp_i3 = *(int *)(param_2 + 0x158);
      }
      else {
        if (tmp_i1 != 0xc) goto LAB_00024981;
        tmp_i3 = *(int *)(param_2 + 0x180);
      }
      if (tmp_i3 != 0) {
        return 0;
      }
    }
LAB_00024981:
    tmp_u2 = (uint)(*(int *)(param_2 + (tmp_i1 + 0x54) * 4) !=
                  *(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x20));
    break;
  default:
    return 0;
  }
  return tmp_u2;
}

void BG_CreateRotationMatrix(uint32_t param_1,int param_2)
{
  AngleVectors(param_1,param_2,param_2 + 0xc,param_2 + 0x18);
  VectorInverse(param_2 + 0xc);
  return;
}

void BG_TransposeMatrix(uint32_t *param_1,uint32_t *param_2)
{
  *param_2 = *param_1;
  param_2[1] = param_1[3];
  param_2[2] = param_1[6];
  param_2[3] = param_1[1];
  param_2[4] = param_1[4];
  param_2[5] = param_1[7];
  param_2[6] = param_1[2];
  param_2[7] = param_1[5];
  param_2[8] = param_1[8];
  return;
}

void BG_RotatePoint(float *param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  
  tmp_f1 = *param_1;
  tmp_f2 = param_1[1];
  tmp_f3 = param_1[2];
  *param_1 = param_2[2] * tmp_f3 + param_2[1] * tmp_f2 + *param_2 * tmp_f1;
  param_1[1] = param_2[5] * tmp_f3 + param_2[4] * tmp_f2 + param_2[3] * tmp_f1;
  param_1[2] = tmp_f3 * param_2[8] + tmp_f2 * param_2[7] + tmp_f1 * param_2[6];
  return;
}

void PC_SourceWarning(uint32_t param_1,char *param_2)
{
  uint32_t local_90;
  uint8_t local_8c [128];
  
  vsnprintf(string_12474,0x1000,param_2,&stack0x0000000c);
  local_90 = 0;
  local_8c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_8c,&local_90);
  Com_Printf("^3WARNING: %s, line %d: %s\n",local_8c,local_90,string_12474);
  return;
}

void PC_SourceError(uint32_t param_1,char *param_2)
{
  uint32_t local_90;
  uint8_t local_8c [128];
  
  vsnprintf(string_12482,0x1000,param_2,&stack0x0000000c);
  local_90 = 0;
  local_8c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_8c,&local_90);
  Com_Printf("^1ERROR: %s, line %d: %s\n",local_8c,local_90,string_12482);
  return;
}

uint32_t PC_Float_Parse(uint32_t param_1,float *param_2)
{
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

uint32_t PC_Color_Parse(uint32_t param_1,int param_2)
{
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

uint32_t PC_Vec_Parse(uint32_t param_1,int param_2)
{
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

uint32_t PC_Int_Parse(uint32_t param_1,int *param_2)
{
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

bool PC_String_Parse(uint32_t param_1,uint32_t *param_2)
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

void PC_String_tolower(char *param_1)
{
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

bool PC_String_ParseNoAlloc(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  uint8_t local_424 [16];
  uint8_t local_414 [1040];
  
  tmp_i1 = trap_PC_ReadToken(param_1,local_424);
  if (tmp_i1 != 0) {
    Q_strncpyz(param_2,local_414,param_3);
  }
  return tmp_i1 != 0;
}

byte BG_simpleWeaponState(int param_1)
{
  byte tmp_b1;
  uint tmp_u2;
  
  tmp_b1 = 0;
  if (param_1 - 1U < 7) {
    tmp_b1 = 1;
    tmp_u2 = 1 << ((byte)(param_1 - 1U) & 0x1f);
    if (((tmp_u2 & 0xd) == 0) && (tmp_b1 = 3, (tmp_u2 & 0x40) == 0)) {
      return ~-((tmp_u2 & 0x30) == 0) & 2;
    }
  }
  return tmp_b1;
}

int BG_cleanName(char *param_1,char *param_2,int param_3,int param_4)
{
  char tmp_c1;
  int tmp_i2;
  char *tmp_pc3;
  
  tmp_c1 = *param_1;
  tmp_pc3 = param_2;
joined_r0x00025172:
  do {
    if (tmp_c1 == '\0') {
LAB_000251a0:
      tmp_i2 = (int)tmp_pc3 - (int)param_2;
LAB_000251a4:
      *tmp_pc3 = '\0';
      return tmp_i2;
    }
    tmp_i2 = (int)tmp_pc3 - (int)param_2;
    if (param_3 + -1 <= tmp_i2) goto LAB_000251a4;
    if (tmp_c1 != '^') {
      if (tmp_c1 < ' ') {
        if ((tmp_c1 == '\n') && (param_4 != 0)) {
LAB_000251b5:
          *tmp_pc3 = tmp_c1;
          param_1 = param_1 + 1;
          tmp_pc3 = tmp_pc3 + 1;
          tmp_c1 = *param_1;
          goto joined_r0x00025172;
        }
      }
      else if (tmp_c1 != '\x7f') goto LAB_000251b5;
      tmp_c1 = param_1[1];
      param_1 = param_1 + 1;
      goto joined_r0x00025172;
    }
    if (param_1[1] == '\0') goto LAB_000251a0;
    tmp_c1 = param_1[2];
    param_1 = param_1 + 2;
  } while( true );
}

void BG_setCrosshair(char *param_1,float *param_2,float param_3,uint32_t param_4)
{
  byte tmp_b1;
  byte tmp_b2;
  byte tmp_b3;
  char tmp_c4;
  uint8_t *tmp_pu5;
  float tmp_f6;
  int tmp_i7;
  int tmp_i8;
  
  tmp_f6 = 1.0;
  *param_2 = 1.0;
  param_2[1] = 1.0;
  param_2[2] = 1.0;
  if ((param_3 <= 1.0) && (tmp_f6 = 0.0, 0.0 <= param_3)) {
    tmp_f6 = param_3;
  }
  param_2[3] = tmp_f6;
  if ((*param_1 == '0') && ((param_1[1] & 0xdfU) == 0x58)) {
    tmp_b1 = param_1[2];
    tmp_i8 = (int)(char)tmp_b1;
    if (((((tmp_b1 != 0) &&
          (((((byte)((tmp_b1 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b1 - 0x30) < 10)) &&
            (tmp_b2 = param_1[3], tmp_b2 != 0)) &&
           (((byte)((tmp_b2 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b2 - 0x30) < 10)))))) &&
         (tmp_b3 = param_1[4], tmp_b3 != 0)) &&
        ((((byte)((tmp_b3 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b3 - 0x30) < 10)) &&
         ((tmp_b3 = param_1[5], tmp_b3 != 0 &&
          ((((byte)((tmp_b3 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b3 - 0x30) < 10)) &&
           (tmp_b3 = param_1[6], tmp_b3 != 0)))))))) &&
       ((((byte)((tmp_b3 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b3 - 0x30) < 10)) &&
        ((tmp_b3 = param_1[7], tmp_b3 != 0 &&
         (((byte)((tmp_b3 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b3 - 0x30) < 10)))))))) {
      if ((char)tmp_b1 < ':') {
        tmp_i8 = (tmp_i8 + -0x30) * 0x10;
      }
      else if ((char)tmp_b1 < 'a') {
        tmp_i8 = (tmp_i8 + -0x37) * 0x10;
      }
      else {
        tmp_i8 = (tmp_i8 + -0x57) * 0x10;
      }
      tmp_i7 = (int)(char)tmp_b2;
      if ((char)tmp_b2 < ':') {
        tmp_i7 = tmp_i7 + -0x30;
      }
      else if ((char)tmp_b2 < 'a') {
        tmp_i7 = tmp_i7 + -0x37;
      }
      else {
        tmp_i7 = tmp_i7 + -0x57;
      }
      *param_2 = (float)(tmp_i8 + tmp_i7) / 255.0;
      tmp_c4 = param_1[4];
      tmp_i8 = (int)tmp_c4;
      if (tmp_c4 < ':') {
        tmp_i8 = (tmp_i8 + -0x30) * 0x10;
      }
      else if (tmp_c4 < 'a') {
        tmp_i8 = (tmp_i8 + -0x37) * 0x10;
      }
      else {
        tmp_i8 = (tmp_i8 + -0x57) * 0x10;
      }
      tmp_c4 = param_1[5];
      tmp_i7 = (int)tmp_c4;
      if (tmp_c4 < ':') {
        tmp_i7 = tmp_i7 + -0x30;
      }
      else if (tmp_c4 < 'a') {
        tmp_i7 = tmp_i7 + -0x37;
      }
      else {
        tmp_i7 = tmp_i7 + -0x57;
      }
      param_2[1] = (float)(tmp_i8 + tmp_i7) / 255.0;
      tmp_c4 = param_1[6];
      tmp_i8 = (int)tmp_c4;
      if (tmp_c4 < ':') {
        tmp_i8 = (tmp_i8 + -0x30) * 0x10;
      }
      else if (tmp_c4 < 'a') {
        tmp_i8 = (tmp_i8 + -0x37) * 0x10;
      }
      else {
        tmp_i8 = (tmp_i8 + -0x57) * 0x10;
      }
      tmp_c4 = param_1[7];
      tmp_i7 = (int)tmp_c4;
      if (tmp_c4 < ':') {
        tmp_i7 = tmp_i7 + -0x30;
      }
      else if (tmp_c4 < 'a') {
        tmp_i7 = tmp_i7 + -0x37;
      }
      else {
        tmp_i7 = tmp_i7 + -0x57;
      }
      param_2[2] = (float)(tmp_i8 + tmp_i7) / 255.0;
      return;
    }
  }
  else {
    tmp_i8 = 0;
    tmp_pu5 = OSP_Colortable;
    while (tmp_pu5 != (uint8_t *)0x0) {
      tmp_i7 = Q_stricmp(param_1,tmp_pu5);
      if (tmp_i7 == 0) {
        *param_2 = *(float *)(&g_ptr_colorWhite_00140c24)[tmp_i8 * 2];
        param_2[1] = *(float *)((&g_ptr_colorWhite_00140c24)[tmp_i8 * 2] + 4);
        param_2[2] = *(float *)((&g_ptr_colorWhite_00140c24)[tmp_i8 * 2] + 8);
        return;
      }
      tmp_i8 = tmp_i8 + 1;
      tmp_pu5 = (&OSP_Colortable)[tmp_i8 * 2];
    }
  }
  trap_Cvar_Set(param_4,"White");
  return;
}

bool BG_isLightWeaponSupportingFastReload(uint param_1)
{
  if (((1 < param_1 - 2) && (1 < param_1 - 7)) && ((param_1 & 0xfffffffb) != 10)) {
    return param_1 == 0x26 || param_1 == 0x1f;
  }
  return true;
}

bool BG_IsScopedWeapon(int param_1)
{
  return param_1 - 0x27U < 3;
}

void BG_InitLocations(float *param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  
  g_unk_001995c8 = 1200.0;
  tmp_f2 = *param_2 - *param_1;
  tmp_f1 = tmp_f2 / 1200.0;
  while (tmp_f1 < 7.0) {
    g_unk_001995c8 = g_unk_001995c8 - 50.0;
    tmp_f1 = tmp_f2 / g_unk_001995c8;
  }
  tmp_f2 = param_1[1] - param_2[1];
  g_unk_001995cc = 1200.0;
  tmp_f3 = tmp_f2 / 1200.0;
  while (tmp_f3 < 7.0) {
    g_unk_001995cc = g_unk_001995cc - 50.0;
    tmp_f3 = tmp_f2 / g_unk_001995cc;
  }
  locInfo = (tmp_f1 - (float)(int)ROUND(tmp_f1)) * g_unk_001995c8 * 0.5 + *param_1;
  g_unk_001995c4 = param_1[1] - (tmp_f3 - (float)(int)ROUND(tmp_f3)) * g_unk_001995cc * 0.5;
  return;
}

uint8_t * BG_GetLocationString(float *param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  coord_12606 = 0;
  tmp_i1 = (int)ROUND((*param_1 - locInfo) / g_unk_001995c8);
  tmp_i2 = (int)ROUND((g_unk_001995c4 - param_1[1]) / g_unk_001995cc);
  if (tmp_i2 < 0) {
    tmp_i2 = 0;
  }
  if (tmp_i1 < 0) {
    tmp_i1 = 0;
  }
  Com_sprintf(&coord_12606,6,"%c,%i",tmp_i1 + 0x41,tmp_i2);
  return &coord_12606;
}

void BG_ClipVelocity(float *param_1,float *param_2,float *param_3,float param_4)
{
  float tmp_f1;
  
  tmp_f1 = param_1[2] * param_2[2] + param_1[1] * param_2[1] + *param_1 * *param_2;
  if (tmp_f1 < 0.0) {
    tmp_f1 = tmp_f1 * param_4;
  }
  else {
    tmp_f1 = tmp_f1 / param_4;
  }
  *param_3 = *param_1 - *param_2 * tmp_f1;
  param_3[1] = param_1[1] - param_2[1] * tmp_f1;
  param_3[2] = param_1[2] - tmp_f1 * param_2[2];
  return;
}

bool BG_BBoxCollision(float *param_1,float *param_2,float *param_3,float *param_4)
{
  if ((((*param_1 <= *param_4) && (*param_3 <= *param_2)) && (param_1[1] <= param_4[1])) &&
     ((param_3[1] <= param_2[1] && (param_1[2] <= param_4[2])))) {
    return param_3[2] <= param_2[2];
  }
  return false;
}

uint32_t BG_FootstepForSurface(uint param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 9;
  if ((((((param_1 & 0x2000) == 0) && (tmp_u1 = 1, (param_1 & 0x1000) == 0)) &&
       (tmp_u1 = 2, (param_1 & 0x40000) == 0)) &&
      ((tmp_u1 = 3, (param_1 & 0x80000) == 0 && (tmp_u1 = 4, (param_1 & 0x100000) == 0)))) &&
     ((tmp_u1 = 6, (param_1 & 0x800000) == 0 &&
      ((tmp_u1 = 7, (param_1 & 0x400000) == 0 && (tmp_u1 = 8, (param_1 & 0x2000000) == 0)))))) {
    tmp_u1 = 0;
    if ((param_1 & 0x40) != 0) {
      tmp_u1 = 5;
    }
    return tmp_u1;
  }
  return tmp_u1;
}

bool BG_CheckCharge(int *param_1)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint tmp_u5;
  bool tmp_b6;
  int local_1c;
  int local_18;
  
  local_18 = 5;
  tmp_i1 = *param_1;
  tmp_u5 = *(int *)(tmp_i1 + 0xe4) - 1;
  if (tmp_u5 < 4) {
    local_18 = *(int *)(CSWTCH_91 + tmp_u5 * 4);
  }
  tmp_u5 = *(uint *)(tmp_i1 + 0xa4);
  if (((((((tmp_u5 != 0x12 && tmp_u5 != 0xf) && (tmp_u5 & 0xffffffef) != 5) &&
         (tmp_u5 & 0xffffffef) != 0xc) && 1 < tmp_u5 - 0x2a) && 3 < tmp_u5 - 0x30) && 1 < tmp_u5 - 0x24)
     && (1 < tmp_u5 - 0x19)) {
    return true;
  }
  switch(*(int *)(tmp_i1 + 0xe4)) {
  default:
    local_1c = param_1[0x15];
    break;
  case 1:
    local_1c = param_1[0x17];
    break;
  case 2:
    local_1c = param_1[0x16];
    break;
  case 3:
    local_1c = param_1[0x14];
    break;
  case 4:
    local_1c = param_1[0x18];
  }
  switch(tmp_u5) {
  case 5:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Panzer;
    if ((chargeCost_Panzer != g_unk_0013e2f8) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_0013e2f8;
    }
    if ((g_unk_0013e2fc != g_unk_0013e2f8) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_0013e2fc;
    }
    if ((g_unk_0013e300 != g_unk_0013e2fc) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_0013e300;
    }
    if ((g_unk_0013e304 != g_unk_0013e300) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_0013e304;
    }
    tmp_b6 = g_unk_0013e308 == g_unk_0013e304;
    tmp_f3 = g_unk_0013e308;
    if (!NAN(g_unk_0013e308) && !NAN(g_unk_0013e304)) {
LAB_00025a00:
      if (tmp_b6) goto LAB_00025a12;
    }
    break;
  default:
    return true;
  case 0xc:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Ammo;
    if ((chargeCost_Ammo != g_unk_0013e340) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_0013e340;
    }
    if ((g_unk_0013e344 != g_unk_0013e340) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_0013e344;
    }
    if ((g_unk_0013e348 != g_unk_0013e344) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_0013e348;
    }
    if ((g_unk_0013e34c != g_unk_0013e348) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_0013e34c;
    }
    tmp_b6 = g_unk_0013e350 == g_unk_0013e34c;
    tmp_f3 = g_unk_0013e350;
    if (!NAN(g_unk_0013e350) && !NAN(g_unk_0013e34c)) goto LAB_00025a00;
    break;
  case 0xf:
  case 0x30:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Dynamite;
    if ((chargeCost_Dynamite != g_unk_0013e3b8) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_0013e3b8;
    }
    if ((g_unk_0013e3bc != g_unk_0013e3b8) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_0013e3bc;
    }
    if ((g_unk_0013e3c0 != g_unk_0013e3bc) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_0013e3c0;
    }
    if ((g_unk_0013e3c4 != g_unk_0013e3c0) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_0013e3c4;
    }
    tmp_b6 = g_unk_0013e3c8 == g_unk_0013e3c4;
    tmp_f3 = g_unk_0013e3c8;
    if (!NAN(g_unk_0013e3c8) && !NAN(g_unk_0013e3c4)) goto LAB_00025a00;
    break;
  case 0x12:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Health;
    if ((chargeCost_Health != g_unk_0013e358) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_0013e358;
    }
    if ((g_unk_0013e35c != g_unk_0013e358) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_0013e35c;
    }
    if ((g_unk_0013e360 != g_unk_0013e35c) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_0013e360;
    }
    if ((g_unk_0013e364 != g_unk_0013e360) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_0013e364;
    }
    tmp_b6 = g_unk_0013e368 == g_unk_0013e364;
    tmp_f3 = g_unk_0013e368;
    if (!NAN(g_unk_0013e368) && !NAN(g_unk_0013e364)) goto LAB_00025a00;
    break;
  case 0x15:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Artillery;
    if ((chargeCost_Artillery != g_unk_0013e310) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_0013e310;
    }
    if ((g_unk_0013e314 != g_unk_0013e310) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_0013e314;
    }
    if ((g_unk_0013e318 != g_unk_0013e314) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_0013e318;
    }
    if ((g_unk_0013e31c != g_unk_0013e318) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_0013e31c;
    }
    tmp_b6 = g_unk_0013e320 == g_unk_0013e31c;
    tmp_f3 = g_unk_0013e320;
    if (!NAN(g_unk_0013e320) && !NAN(g_unk_0013e31c)) goto LAB_00025a00;
    break;
  case 0x19:
  case 0x33:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Landmine;
    if ((chargeCost_Landmine != g_unk_0013e3d0) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_0013e3d0;
    }
    if ((g_unk_0013e3d4 != g_unk_0013e3d0) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_0013e3d4;
    }
    if ((g_unk_0013e3d8 != g_unk_0013e3d4) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_0013e3d8;
    }
    if ((g_unk_0013e3dc != g_unk_0013e3d8) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_0013e3dc;
    }
    tmp_b6 = g_unk_0013e3e0 == g_unk_0013e3dc;
    tmp_f3 = g_unk_0013e3e0;
    if (!NAN(g_unk_0013e3e0) && !NAN(g_unk_0013e3dc)) goto LAB_00025a00;
    break;
  case 0x1a:
  case 0x1c:
  case 0x32:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Satchel;
    if ((chargeCost_Satchel != g_unk_0013e388) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_0013e388;
    }
    if ((g_unk_0013e38c != g_unk_0013e388) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_0013e38c;
    }
    if ((g_unk_0013e390 != g_unk_0013e38c) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_0013e390;
    }
    if ((g_unk_0013e394 != g_unk_0013e390) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_0013e394;
    }
    tmp_b6 = g_unk_0013e398 == g_unk_0013e394;
    tmp_f3 = g_unk_0013e398;
    if (!NAN(g_unk_0013e398) && !NAN(g_unk_0013e394)) goto LAB_00025a00;
    break;
  case 0x24:
  case 0x25:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Riflenade;
    if ((chargeCost_Riflenade != g_unk_0013e3a0) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_0013e3a0;
    }
    if ((g_unk_0013e3a4 != g_unk_0013e3a0) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_0013e3a4;
    }
    if ((g_unk_0013e3a8 != g_unk_0013e3a4) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_0013e3a8;
    }
    if ((g_unk_0013e3ac != g_unk_0013e3a8) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_0013e3ac;
    }
    tmp_b6 = g_unk_0013e3b0 == g_unk_0013e3ac;
    tmp_f3 = g_unk_0013e3b0;
    if (!NAN(g_unk_0013e3b0) && !NAN(g_unk_0013e3ac)) goto LAB_00025a00;
    break;
  case 0x2a:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Mortar;
    if ((chargeCost_Mortar != g_unk_0013e2e0) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_0013e2e0;
    }
    if ((g_unk_0013e2e4 != g_unk_0013e2e0) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_0013e2e4;
    }
    if ((g_unk_0013e2e8 != g_unk_0013e2e4) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_0013e2e8;
    }
    if ((g_unk_0013e2ec != g_unk_0013e2e8) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_0013e2ec;
    }
    tmp_b6 = g_unk_0013e2f0 == g_unk_0013e2ec;
    tmp_f3 = g_unk_0013e2f0;
    if (!NAN(g_unk_0013e2f0) && !NAN(g_unk_0013e2ec)) goto LAB_00025a00;
    break;
  case 0x2b:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Adrenaline;
    if ((chargeCost_Adrenaline != g_unk_0013e328) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_0013e328;
    }
    if ((g_unk_0013e32c != g_unk_0013e328) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_0013e32c;
    }
    if ((g_unk_0013e330 != g_unk_0013e32c) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_0013e330;
    }
    if ((g_unk_0013e334 != g_unk_0013e330) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_0013e334;
    }
    tmp_b6 = g_unk_0013e338 == g_unk_0013e334;
    tmp_f3 = g_unk_0013e338;
    if (!NAN(g_unk_0013e338) && !NAN(g_unk_0013e334)) goto LAB_00025a00;
    break;
  case 0x31:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Tripmine;
    if ((chargeCost_Tripmine != g_unk_0013e2c8) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_0013e2c8;
    }
    if ((g_unk_0013e2cc != g_unk_0013e2c8) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_0013e2cc;
    }
    if ((g_unk_0013e2d0 != g_unk_0013e2cc) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_0013e2d0;
    }
    if ((g_unk_0013e2d4 != g_unk_0013e2d0) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_0013e2d4;
    }
    tmp_b6 = g_unk_0013e2d8 == g_unk_0013e2d4;
    tmp_f3 = g_unk_0013e2d8;
    if (!NAN(g_unk_0013e2d8) && !NAN(g_unk_0013e2d4)) goto LAB_00025a00;
  }
  if ((tmp_u5 & 0x20) != 0) {
    tmp_f2 = tmp_f3;
  }
LAB_00025a12:
  return tmp_f2 * (float)local_1c <= tmp_f4;
}

uint8_t * BG_GetPlayerClassInfo(int param_1,uint param_2)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  
  tmp_i1 = 0;
  if (param_2 < 5) {
    tmp_i1 = param_2 * 0x30;
  }
  tmp_pu2 = bg_allies_playerclasses;
  if (param_1 != 2) {
    tmp_pu2 = bg_axis_playerclasses;
  }
  return tmp_pu2 + tmp_i1;
}

uint8_t * BG_PlayerClassForPlayerState(int param_1)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  
  tmp_i1 = 0;
  if (*(uint *)(param_1 + 0xe4) < 5) {
    tmp_i1 = *(uint *)(param_1 + 0xe4) * 0x30;
  }
  tmp_pu2 = bg_allies_playerclasses;
  if (*(int *)(param_1 + 300) != 2) {
    tmp_pu2 = bg_axis_playerclasses;
  }
  return tmp_pu2 + tmp_i1;
}

bool BG_ClassHasWeapon(int param_1,int param_2)
{
  bool tmp_b1;
  
  tmp_b1 = false;
  if (param_2 != 0) {
    if ((((param_2 != *(int *)(param_1 + 0x10)) && (param_2 != *(int *)(param_1 + 0x14))) &&
        (param_2 != *(int *)(param_1 + 0x18))) &&
       ((param_2 != *(int *)(param_1 + 0x1c) && (param_2 != *(int *)(param_1 + 0x20))))) {
      return param_2 == *(int *)(param_1 + 0x24);
    }
    tmp_b1 = true;
  }
  return tmp_b1;
}

bool BG_WeaponIsPrimaryForClassAndTeam(int param_1,int param_2,int param_3)
{
  bool tmp_b1;
  
  if (param_2 == 2) {
    tmp_b1 = false;
    if (param_3 != 0) {
      param_1 = param_1 * 0x30;
      if (param_3 == *(int *)(bg_allies_playerclasses + param_1 + 0x10)) {
        return true;
      }
      if (param_3 == *(int *)(bg_allies_playerclasses + param_1 + 0x14)) {
        return true;
      }
      if (param_3 == *(int *)(bg_allies_playerclasses + param_1 + 0x18)) {
        return true;
      }
      if (param_3 == *(int *)(bg_allies_playerclasses + param_1 + 0x1c)) {
        return true;
      }
      if (param_3 == *(int *)(bg_allies_playerclasses + param_1 + 0x20)) {
        return true;
      }
      return param_3 == *(int *)(bg_allies_playerclasses + param_1 + 0x24);
    }
  }
  else {
    if ((param_2 != 1) || (param_3 == 0)) {
      return false;
    }
    param_1 = param_1 * 0x30;
    if ((((param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x10)) ||
         (param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x14))) ||
        (param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x18))) ||
       ((param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x1c) ||
        (param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x20))))) {
      return true;
    }
    tmp_b1 = param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x24);
  }
  return tmp_b1;
}

char * BG_TeamName(int param_1)
{
  if (param_1 == 2) {
    return "allies";
  }
  if (param_1 != 3) {
    if (param_1 != 1) {
      return "";
    }
    return "axis";
  }
  return "spectator";
}

char * BG_ShortClassnameForNumber(uint32_t param_1)
{
  switch(param_1) {
  case 0:
    return "^wSoldr";
  case 1:
    return "^wMedic";
  case 2:
    return "^wEngr";
  case 3:
    return "^wFdOps";
  case 4:
    return "^wCvOps";
  default:
    return "^1ERROR";
  }
}

char * BG_ClassnameForNumber(uint32_t param_1)
{
  switch(param_1) {
  case 0:
    return "Soldier";
  case 1:
    return "Medic";
  case 2:
    return "Engineer";
  case 3:
    return "Field Ops";
  case 4:
    return "Covert Ops";
  default:
    return "^1ERROR";
  }
}

char * BG_ClassnameForNumber_Filename(uint32_t param_1)
{
  switch(param_1) {
  case 0:
    return "Soldier";
  case 1:
    return "Medic";
  case 2:
    return "Engineer";
  case 3:
    return "Fieldops";
  case 4:
    return "Covertops";
  default:
    return "ERROR";
  }
}

uint32_t BG_ClassSkillForClass(uint param_1)
{
  uint32_t tmp_u1;
  uint32_t local_14 [5];
  
  local_14[0] = 5;
  local_14[2] = 1;
  local_14[3] = 3;
  local_14[4] = 6;
  tmp_u1 = 0;
  local_14[1] = 2;
  if (param_1 < 5) {
    tmp_u1 = local_14[param_1];
  }
  return tmp_u1;
}

uint32_t BG_SS_ParseError(uint32_t param_1,char *param_2)
{
  uint32_t local_a0;
  uint8_t local_9c [140];
  
  vsnprintf(string_6917,0x1000,param_2,&stack0x0000000c);
  local_a0 = 0;
  local_9c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_9c,&local_a0);
  Com_Printf("^1ERROR: %s, line %d: %s\n",local_9c,local_a0,string_6917);
  trap_PC_FreeSource(param_1);
  return 0;
}

void BG_ClearScriptSpeakerPool(void)
{
  numScriptSpeakers = 0;
  return;
}

uint32_t BG_NumScriptSpeakers(void)
{
  return numScriptSpeakers;
}

int BG_GetIndexForSpeaker(int param_1)
{
  return (param_1 + -0x19a600 >> 3) * 0x286bca1b;
}

uint8_t * BG_GetScriptSpeaker(int param_1)
{
  if ((-1 < param_1) && (param_1 < numScriptSpeakers)) {
    return scriptSpeakers + param_1 * 0x98;
  }
  return (uint8_t *)0x0;
}

uint32_t BG_SS_DeleteSpeaker(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  uint8_t *tmp_pu5;
  
  if (param_1 < 0) {
    tmp_u1 = 0;
  }
  else {
    tmp_u1 = 0;
    if (param_1 < numScriptSpeakers) {
      tmp_i3 = numScriptSpeakers + -1;
      tmp_u1 = 1;
      tmp_pu4 = scriptSpeakers + (param_1 + 1) * 0x98;
      tmp_pu5 = scriptSpeakers + param_1 * 0x98;
      for (tmp_i2 = ((numScriptSpeakers - param_1) + -1) * 0x98; numScriptSpeakers = tmp_i3,
          tmp_i2 != 0; tmp_i2 = tmp_i2 + -1) {
        *tmp_pu5 = *tmp_pu4;
        tmp_pu4 = tmp_pu4 + 1;
        tmp_pu5 = tmp_pu5 + 1;
      }
    }
  }
  return tmp_u1;
}

uint32_t BG_SS_StoreSpeaker(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint tmp_u3;
  
  tmp_u2 = 0;
  if (numScriptSpeakers < 0x100) {
    tmp_i1 = numScriptSpeakers * 0x98;
    tmp_u3 = 0;
    numScriptSpeakers = numScriptSpeakers + 1;
    do {
      tmp_u2 = *(uint32_t *)(param_1 + tmp_u3);
      *(uint32_t *)(tmp_i1 + 0x19a604 + tmp_u3) = *(uint32_t *)(param_1 + 4 + tmp_u3);
      *(uint32_t *)(scriptSpeakers + tmp_u3 + tmp_i1) = tmp_u2;
      tmp_u3 = tmp_u3 + 8;
    } while (tmp_u3 < 0x98);
    tmp_u2 = 1;
  }
  return tmp_u2;
}

uint32_t BG_LoadSpeakerScript(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint tmp_u4;
  uint32_t local_8e4 [17];
  uint8_t local_8a0 [12];
  uint8_t local_894 [32];
  uint32_t local_874;
  uint32_t local_870;
  uint32_t local_86c;
  int local_868;
  int local_864;
  uint local_860;
  int local_85c [4];
  uint8_t local_84c [16];
  char local_83c [1032];
  uint8_t local_434 [16];
  char local_424 [1044];
  
  tmp_i1 = trap_PC_LoadSource(param_1);
  if (tmp_i1 == 0) {
    return 0;
  }
  tmp_i2 = trap_PC_ReadToken(tmp_i1,local_84c);
  if (tmp_i2 != 0) {
    tmp_i2 = Q_stricmp(local_83c,"speakerScript");
    if (tmp_i2 == 0) {
      tmp_i2 = trap_PC_ReadToken(tmp_i1,local_84c);
      if ((tmp_i2 == 0) || (tmp_i2 = Q_stricmp(local_83c,"{"), tmp_i2 != 0)) {
        tmp_u3 = BG_SS_ParseError(tmp_i1,"expected \'{\'");
        return tmp_u3;
      }
LAB_00033290:
      do {
        tmp_i2 = trap_PC_ReadToken(tmp_i1,local_84c);
        if ((tmp_i2 == 0) || (local_83c[0] == '}')) {
          trap_PC_FreeSource(tmp_i1);
          return 1;
        }
        tmp_i2 = Q_stricmp(local_83c,"speakerDef");
        if (tmp_i2 != 0) {
          tmp_u3 = BG_SS_ParseError(tmp_i1,"unknown token \'%s\'",local_83c);
          return tmp_u3;
        }
        tmp_u4 = 0;
        do {
          *(uint32_t *)((int)local_8e4 + tmp_u4) = 0;
          *(uint32_t *)((int)local_8e4 + tmp_u4 + 4) = 0;
          tmp_u4 = tmp_u4 + 8;
        } while (tmp_u4 < 0x98);
        local_860 = 0x7f;
        local_85c[0] = 0x4e2;
        tmp_i2 = trap_PC_ReadToken(tmp_i1,local_434);
        if (tmp_i2 == 0) {
LAB_000334f8:
          tmp_i2 = BG_SS_ParseError(tmp_i1,"expected \'{\'");
        }
        else {
          tmp_i2 = Q_stricmp(local_424,"{");
          if (tmp_i2 != 0) goto LAB_000334f8;
LAB_00033360:
          tmp_i2 = trap_PC_ReadToken(tmp_i1,local_434);
          if ((tmp_i2 == 0) || (local_424[0] == '}')) {
            if (0xff < numScriptSpeakers) {
              tmp_i2 = BG_SS_ParseError(tmp_i1,"Failed to store speaker",local_424);
              goto LAB_000333d0;
            }
            tmp_i2 = numScriptSpeakers * 0x98;
            tmp_u4 = 0;
            numScriptSpeakers = numScriptSpeakers + 1;
            do {
              tmp_u3 = *(uint32_t *)((int)local_8e4 + tmp_u4 + 4);
              *(uint32_t *)(scriptSpeakers + tmp_u4 + tmp_i2) =
                   *(uint32_t *)((int)local_8e4 + tmp_u4);
              *(uint32_t *)(tmp_i2 + 0x19a604 + tmp_u4) = tmp_u3;
              tmp_u4 = tmp_u4 + 8;
            } while (tmp_u4 < 0x98);
            goto LAB_00033290;
          }
          tmp_i2 = Q_stricmp(local_424,"noise");
          if (tmp_i2 != 0) {
            tmp_i2 = Q_stricmp(local_424,"origin");
            if (tmp_i2 == 0) {
              tmp_i2 = PC_Vec_Parse(tmp_i1,local_8a0);
              if (tmp_i2 == 0) {
                tmp_i2 = BG_SS_ParseError(tmp_i1,"expected origin vector");
                goto LAB_000333d0;
              }
            }
            else {
              tmp_i2 = Q_stricmp(local_424,"targetname");
              if (tmp_i2 == 0) {
                tmp_i2 = PC_String_ParseNoAlloc(tmp_i1,local_894,0x20);
                if (tmp_i2 == 0) {
                  tmp_i2 = BG_SS_ParseError(tmp_i1,"expected targetname string");
                  goto LAB_000333d0;
                }
                local_874 = BG_StringHashValue(local_894);
              }
              else {
                tmp_i2 = Q_stricmp(local_424,"looped");
                if (tmp_i2 == 0) {
                  tmp_i2 = trap_PC_ReadToken(tmp_i1,local_434);
                  if (tmp_i2 == 0) {
                    tmp_i2 = BG_SS_ParseError(tmp_i1,"expected loop value");
                    goto LAB_000333d0;
                  }
                  tmp_i2 = Q_stricmp(local_424,"no");
                  if (tmp_i2 == 0) {
                    local_870 = 0;
                  }
                  else {
                    tmp_i2 = Q_stricmp(local_424,"on");
                    if (tmp_i2 == 0) {
                      local_870 = 1;
                      local_85c[1] = 1;
                    }
                    else {
                      tmp_i2 = Q_stricmp(local_424,"off");
                      if (tmp_i2 != 0) {
                        tmp_i2 = BG_SS_ParseError(tmp_i1,"unknown loop value \'%s\'",local_424);
                        goto LAB_000333d0;
                      }
                      local_870 = 2;
                    }
                  }
                }
                else {
                  tmp_i2 = Q_stricmp(local_424,"broadcast");
                  if (tmp_i2 == 0) {
                    tmp_i2 = trap_PC_ReadToken(tmp_i1,local_434);
                    if (tmp_i2 == 0) {
                      tmp_i2 = BG_SS_ParseError(tmp_i1,"expected broadcast value");
                      goto LAB_000333d0;
                    }
                    tmp_i2 = Q_stricmp(local_424,"no");
                    if (tmp_i2 == 0) {
                      local_86c = 0;
                    }
                    else {
                      tmp_i2 = Q_stricmp(local_424,"global");
                      if (tmp_i2 == 0) {
                        local_86c = 1;
                      }
                      else {
                        tmp_i2 = Q_stricmp(local_424,"nopvs");
                        if (tmp_i2 != 0) {
                          tmp_i2 = BG_SS_ParseError(tmp_i1,"unknown broadcast value \'%s\'",local_424)
                          ;
                          goto LAB_000333d0;
                        }
                        local_86c = 2;
                      }
                    }
                  }
                  else {
                    tmp_i2 = Q_stricmp(local_424,&g_unk_001103a4);
                    if (tmp_i2 == 0) {
                      tmp_i2 = PC_Int_Parse(tmp_i1,&local_868);
                      if (tmp_i2 == 0) {
                        tmp_i2 = BG_SS_ParseError(tmp_i1,"expected wait value");
                        goto LAB_000333d0;
                      }
                      if (local_868 < 0) {
                        tmp_i2 = BG_SS_ParseError(tmp_i1,"wait value %i is invalid",local_868);
                        goto LAB_000333d0;
                      }
                    }
                    else {
                      tmp_i2 = Q_stricmp(local_424,"random");
                      if (tmp_i2 == 0) {
                        tmp_i2 = PC_Int_Parse(tmp_i1,&local_864);
                        if (tmp_i2 == 0) {
                          tmp_i2 = BG_SS_ParseError(tmp_i1,"expected random value");
                          goto LAB_000333d0;
                        }
                        if (local_864 < 0) {
                          tmp_i2 = BG_SS_ParseError(tmp_i1,"random value %i is invalid",local_864);
                          goto LAB_000333d0;
                        }
                      }
                      else {
                        tmp_i2 = Q_stricmp(local_424,"volume");
                        if (tmp_i2 == 0) {
                          tmp_i2 = PC_Int_Parse(tmp_i1,&local_860);
                          if (tmp_i2 == 0) {
                            tmp_i2 = BG_SS_ParseError(tmp_i1,"expected volume value");
                            goto LAB_000333d0;
                          }
                          if (0xffff < local_860) {
                            tmp_i2 = BG_SS_ParseError(tmp_i1,"volume value %i is invalid",local_860);
                            goto LAB_000333d0;
                          }
                        }
                        else {
                          tmp_i2 = Q_stricmp(local_424,"range");
                          if (tmp_i2 != 0) {
                            tmp_i2 = BG_SS_ParseError(tmp_i1,"unknown token \'%s\'",local_424);
                            goto LAB_000333d0;
                          }
                          tmp_i2 = PC_Int_Parse(tmp_i1,local_85c);
                          if (tmp_i2 == 0) {
                            tmp_i2 = BG_SS_ParseError(tmp_i1,"expected range value");
                            goto LAB_000333d0;
                          }
                          if (local_85c[0] < 0) {
                            tmp_i2 = BG_SS_ParseError(tmp_i1,"range value %i is invalid",local_85c[0])
                            ;
                            goto LAB_000333d0;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            goto LAB_00033360;
          }
          tmp_i2 = PC_String_ParseNoAlloc(tmp_i1,local_8e4,0x40);
          if (tmp_i2 != 0) goto LAB_00033360;
          tmp_i2 = BG_SS_ParseError(tmp_i1,"expected sound filename");
        }
LAB_000333d0:
        if (tmp_i2 == 0) {
          return 0;
        }
      } while( true );
    }
  }
  tmp_u3 = BG_SS_ParseError(tmp_i1,"expected \'soundScript\'");
  return tmp_u3;
}

uint32_t BG_WeapStatForWeapon(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = 0;
  do {
    if ((&aWeapID)[tmp_i1 * 2] == param_1) {
      return (&g_unk_001104a4)[tmp_i1 * 2];
    }
    tmp_i1 = tmp_i1 + 1;
  } while (tmp_i1 != 0x34);
  return 0x1a;
}

uint32_t BG_GetStatGoombas(int param_1)
{
  if (param_1 != 0) {
    return *(uint32_t *)(param_1 + 0x144);
  }
  return 0;
}

uint32_t BG_SetStatGoombas(int param_1,uint32_t param_2)
{
  *(uint32_t *)(param_1 + 0x144) = param_2;
  return 0;
}

uint32_t BG_GetStatBestSpree(int param_1)
{
  if (param_1 != 0) {
    return *(uint32_t *)(param_1 + 0x148);
  }
  return 0;
}

uint32_t BG_SetStatBestSpree(int param_1,uint32_t param_2)
{
  *(uint32_t *)(param_1 + 0x148) = param_2;
  return 0;
}

uint32_t BG_GetKillSpree(int param_1)
{
  if (param_1 != 0) {
    return *(uint32_t *)(param_1 + 0x14c);
  }
  return 0;
}

uint32_t BG_SetKillSpree(int param_1,uint32_t param_2)
{
  *(uint32_t *)(param_1 + 0x14c) = param_2;
  return 0;
}

uint32_t BG_AdjustKillSpree(int param_1,int param_2)
{
  *(int *)(param_1 + 0x14c) = *(int *)(param_1 + 0x14c) + param_2;
  return 0;
}

uint32_t BG_AdjustGoombas(int param_1,int param_2)
{
  if (param_1 != 0) {
    *(int *)(param_1 + 0x144) = *(int *)(param_1 + 0x144) + param_2;
    return 0;
  }
  iRam00000144 = param_2;
  return 0;
}

uint32_t BG_LoadTraceMap(uint32_t param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  float *pfVar4;
  float *pfVar5;
  byte *tmp_pb6;
  float *pfVar7;
  uint32_t *tmp_pu8;
  uint local_470;
  uint local_46c;
  uint local_468;
  uint local_460;
  uint local_448;
  uint local_444;
  int local_440;
  float *local_43c;
  uint8_t local_421;
  uint32_t local_420;
  byte local_41c;
  byte local_41b;
  byte local_41a;
  byte local_419;
  byte local_418;
  byte local_417;
  byte local_416;
  byte local_415;
  byte local_414;
  byte local_413;
  byte local_412;
  byte local_411;
  byte local_410;
  byte local_40f;
  byte local_40e;
  byte local_40d;
  byte local_40c;
  byte local_40b;
  byte local_40a;
  byte local_409;
  byte local_408;
  byte local_407;
  byte local_406;
  byte local_405;
  
  tmp_u2 = Q_strlwr(param_1);
  tmp_u2 = va("maps/%s_tracemap.tga",tmp_u2);
  tmp_i3 = trap_FS_FOpenFile(tmp_u2,&local_420,0);
  if (-1 < tmp_i3) {
    tmp_i3 = 0x12;
    do {
      trap_FS_Read(&local_421,1,local_420);
      tmp_i3 = tmp_i3 + -1;
    } while (tmp_i3 != 0);
    local_43c = (float *)&g_unk_00223a24;
    local_460 = 0xffff0000;
    local_470 = 0xffff0000;
    local_448 = 0x10000;
    local_46c = 0x10000;
    local_440 = 0;
    local_444 = 0x10000;
    local_468 = 0x10000;
    do {
      trap_FS_Read(&local_41c,0x400,local_420);
      tmp_i3 = 0;
      tmp_pb6 = &local_419;
      pfVar7 = local_43c;
      tmp_pu8 = &g_unk_001e3a24;
      do {
        if ((tmp_i3 < 6) && (local_440 == 0)) {
          switch(tmp_i3) {
          default:
            local_470 = (uint)local_41a << 0x10 | (uint)local_41b << 8 | (uint)local_41c |
                        (uint)local_419 << 0x18;
            break;
          case 1:
            local_460 = (uint)local_416 << 0x10 | (uint)local_417 << 8 | (uint)local_418 |
                        (uint)local_415 << 0x18;
            break;
          case 2:
            local_468 = (uint)local_412 << 0x10 | (uint)local_413 << 8 | (uint)local_414 |
                        (uint)local_411 << 0x18;
            break;
          case 3:
            local_444 = (uint)local_40e << 0x10 | (uint)local_40f << 8 | (uint)local_410 |
                        (uint)local_40d << 0x18;
            break;
          case 4:
            local_46c = (uint)local_40a << 0x10 | (uint)local_40b << 8 | (uint)local_40c |
                        (uint)local_409 << 0x18;
            break;
          case 5:
            local_448 = (uint)local_406 << 0x10 | (uint)local_407 << 8 | (uint)local_408 |
                        (uint)local_405 << 0x18;
          }
          *tmp_pu8 = 0x47800000;
          tmp_pu8[0x10000] = 0x47800000;
          tmp_pu8[0x20000] = 0xc7800000;
        }
        else {
          if ((float)tmp_pb6[-3] == 0.0) {
            pfVar7[-0x10000] = 65536.0;
          }
          else {
            pfVar7[-0x10000] = (float)tmp_pb6[-3];
          }
          if ((float)tmp_pb6[-2] == 0.0) {
            *pfVar7 = 65536.0;
          }
          else {
            *pfVar7 = (float)tmp_pb6[-2];
          }
          if ((float)tmp_pb6[-1] == 0.0) {
            pfVar7[0x10000] = -65536.0;
          }
          else {
            pfVar7[0x10000] = (float)tmp_pb6[-1];
          }
          if (*tmp_pb6 == 0) {
            *pfVar7 = 65536.0;
            pfVar7[0x10000] = -65536.0;
          }
        }
        tmp_i3 = tmp_i3 + 1;
        tmp_pu8 = tmp_pu8 + 1;
        tmp_pb6 = tmp_pb6 + 4;
        pfVar7 = pfVar7 + 1;
      } while (tmp_i3 != 0x100);
      local_440 = local_440 + 1;
      local_43c = local_43c + -0x100;
    } while (local_440 != 0x100);
    trap_FS_FCloseFile(local_420);
    if (local_460 == local_470) {
      tmp_f1 = 1.0;
    }
    else {
      tmp_f1 = 254.0 / (float)(int)(local_460 - local_470);
    }
    pfVar7 = (float *)&g_unk_00224224;
    do {
      pfVar4 = pfVar7 + -0x100;
      do {
        pfVar5 = pfVar4;
        if (*pfVar5 != -65536.0) {
          *pfVar5 = *pfVar5 / tmp_f1 + (float)(int)local_470;
        }
        pfVar4 = pfVar5 + 1;
      } while (pfVar5 + 1 != pfVar7);
      pfVar7 = pfVar5 + 0x101;
    } while (pfVar7 != (float *)(string_11988 + 0x3e4));
    if (local_444 == local_468) {
      tmp_f1 = 1.0;
    }
    else {
      tmp_f1 = 254.0 / (float)(int)(local_444 - local_468);
    }
    pfVar7 = (float *)&g_unk_001e4224;
    do {
      pfVar4 = pfVar7 + -0x100;
      do {
        if (*pfVar4 != 65536.0) {
          *pfVar4 = *pfVar4 / tmp_f1 + (float)(int)local_468;
        }
        pfVar4 = pfVar4 + 1;
      } while (pfVar7 != pfVar4);
      pfVar7 = pfVar7 + 0x100;
    } while (pfVar7 != (float *)&g_unk_00224224);
    if (local_448 == local_46c) {
      tmp_f1 = 1.0;
    }
    else {
      tmp_f1 = 254.0 / (float)(int)(local_448 - local_46c);
    }
    pfVar7 = (float *)&g_unk_001a4224;
    do {
      pfVar4 = pfVar7 + -0x100;
      do {
        pfVar5 = pfVar4;
        if (*pfVar5 != 65536.0) {
          *pfVar5 = *pfVar5 / tmp_f1 + (float)(int)local_46c;
        }
        pfVar4 = pfVar5 + 1;
      } while (pfVar5 + 1 != pfVar7);
      pfVar7 = pfVar5 + 0x101;
    } while (pfVar7 != (float *)&g_unk_001e4224);
    g_unk_00263e24 = *param_2;
    g_unk_00263e28 = param_2[1];
    g_unk_00263e2c = *param_3;
    g_unk_00263e30 = param_3[1];
    g_unk_00263e34 = local_470;
    g_unk_00263e38 = local_460;
    tracemap = 1;
    one_over_mapgrid_factor = 1.0 / ((*param_3 - *param_2) * 0.00390625);
    g_unk_001a3e0c = 1.0 / ((param_3[1] - param_2[1]) * 0.00390625);
    return 1;
  }
  tracemap = 0;
  return 0;
}

long double BG_GetSkyHeightAtPoint(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  if (tracemap != 0) {
    tmp_f1 = *param_1;
    tmp_f2 = g_unk_00263e24;
    if ((g_unk_00263e24 <= tmp_f1) && (tmp_f2 = tmp_f1, g_unk_00263e2c < tmp_f1)) {
      tmp_f2 = g_unk_00263e2c;
    }
    tmp_f1 = param_1[1];
    tmp_f3 = g_unk_00263e30;
    if ((g_unk_00263e30 <= tmp_f1) && (tmp_f3 = tmp_f1, g_unk_00263e28 < tmp_f1)) {
      tmp_f3 = g_unk_00263e28;
    }
    tmp_i4 = (int)ROUND((tmp_f2 - g_unk_00263e24) * one_over_mapgrid_factor);
    tmp_i6 = (int)ROUND((tmp_f3 - g_unk_00263e28) * g_unk_001a3e0c);
    if (0xff < tmp_i4) {
      tmp_i4 = 0xff;
    }
    tmp_i5 = 0xff;
    if (tmp_i6 < 0x100) {
      tmp_i5 = tmp_i6;
    }
    if (tmp_i5 < 0) {
      tmp_i5 = 0;
    }
    tmp_i6 = 0;
    if (-1 < tmp_i4) {
      tmp_i6 = tmp_i4;
    }
    return (long double)(float)(&g_unk_001a3e24)[tmp_i5 * 0x100 + tmp_i6];
  }
  return (long double)65536.0;
}

long double BG_GetSkyGroundHeightAtPoint(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  
  if (tracemap != 0) {
    tmp_f1 = *param_1;
    tmp_f2 = g_unk_00263e24;
    if ((g_unk_00263e24 <= tmp_f1) && (tmp_f2 = tmp_f1, g_unk_00263e2c < tmp_f1)) {
      tmp_f2 = g_unk_00263e2c;
    }
    tmp_f1 = param_1[1];
    tmp_f3 = g_unk_00263e30;
    if ((g_unk_00263e30 <= tmp_f1) && (tmp_f3 = tmp_f1, g_unk_00263e28 < tmp_f1)) {
      tmp_f3 = g_unk_00263e28;
    }
    tmp_i5 = (int)ROUND((tmp_f2 - g_unk_00263e24) * one_over_mapgrid_factor);
    tmp_i4 = (int)ROUND((tmp_f3 - g_unk_00263e28) * g_unk_001a3e0c);
    if (0xff < tmp_i5) {
      tmp_i5 = 0xff;
    }
    if (0xff < tmp_i4) {
      tmp_i4 = 0xff;
    }
    if (tmp_i4 < 0) {
      tmp_i4 = 0;
    }
    if (tmp_i5 < 0) {
      tmp_i5 = 0;
    }
    return (long double)(float)(&g_unk_001a3e24)[tmp_i5 + 0x10000 + tmp_i4 * 0x100];
  }
  return (long double)65536.0;
}

long double BG_GetGroundHeightAtPoint(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  
  if (tracemap != 0) {
    tmp_f1 = *param_1;
    tmp_f2 = g_unk_00263e24;
    if ((g_unk_00263e24 <= tmp_f1) && (tmp_f2 = tmp_f1, g_unk_00263e2c < tmp_f1)) {
      tmp_f2 = g_unk_00263e2c;
    }
    tmp_f1 = param_1[1];
    tmp_f3 = g_unk_00263e30;
    if ((g_unk_00263e30 <= tmp_f1) && (tmp_f3 = tmp_f1, g_unk_00263e28 < tmp_f1)) {
      tmp_f3 = g_unk_00263e28;
    }
    tmp_i5 = (int)ROUND((tmp_f2 - g_unk_00263e24) * one_over_mapgrid_factor);
    tmp_i4 = (int)ROUND((tmp_f3 - g_unk_00263e28) * g_unk_001a3e0c);
    if (0xff < tmp_i5) {
      tmp_i5 = 0xff;
    }
    if (0xff < tmp_i4) {
      tmp_i4 = 0xff;
    }
    if (tmp_i4 < 0) {
      tmp_i4 = 0;
    }
    if (tmp_i5 < 0) {
      tmp_i5 = 0;
    }
    return (long double)(float)(&g_unk_001a3e24)[tmp_i5 + 0x20000 + tmp_i4 * 0x100];
  }
  return (long double)-65536.0;
}

uint32_t BG_GetTracemapGroundFloor(void)
{
  if (tracemap != 0) {
    return g_unk_00263e34;
  }
  return 0xffff0000;
}

uint32_t BG_RW_ParseError(uint32_t param_1,char *param_2)
{
  uint32_t local_a0;
  uint8_t local_9c [140];
  
  vsnprintf(string_11988,0x1000,param_2,&stack0x0000000c);
  local_a0 = 0;
  local_9c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_9c,&local_a0);
  Com_Printf("^1ERROR: %s, line %d: %s\n",local_9c,local_a0,string_11988);
  trap_PC_FreeSource(param_1);
  return 0;
}

uint32_t BG_ParseWeaponConfig(uint32_t param_1,int param_2)
{
  bool tmp_b1;
  int tmp_i2;
  char *tmp_pc3;
  uint tmp_u4;
  long tmp_l5;
  char *tmp_pc6;
  uint *tmp_pu7;
  char *tmp_pc8;
  bool tmp_b9;
  byte tmp_b10;
  double tmp_d11;
  uint8_t *local_4e6c;
  uint8_t *local_4e44;
  uint32_t local_4e40;
  uint8_t local_4e3c [20008];
  uint32_t uStack_14;
  
  tmp_b10 = 0;
  uStack_14 = 0x3569d;
  tmp_i2 = trap_FS_FOpenFile(param_1,&local_4e40,0);
  if (tmp_i2 < 1) {
    return 0;
  }
  if (0x4e1e < tmp_i2) {
    Com_Printf("File %s too long\n",param_1);
    return 0;
  }
  trap_FS_Read(local_4e3c,tmp_i2,local_4e40);
  local_4e3c[tmp_i2] = 0;
  trap_FS_FCloseFile(local_4e40);
  tmp_b1 = false;
  local_4e44 = local_4e3c;
LAB_00035730:
  local_4e6c = local_4e44;
  tmp_pc3 = (char *)COM_Parse(&local_4e44);
  tmp_b9 = tmp_pc3 == (char *)0x0;
  if (!tmp_b9) {
    do {
      tmp_i2 = 7;
      tmp_pc6 = tmp_pc3;
      tmp_pc8 = "newfmt";
      do {
        if (tmp_i2 == 0) break;
        tmp_i2 = tmp_i2 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (!tmp_b9) goto LAB_00035998;
      tmp_b1 = true;
      local_4e6c = local_4e44;
      tmp_pc3 = (char *)COM_Parse(&local_4e44);
      tmp_b9 = false;
      if (tmp_pc3 == (char *)0x0) break;
    } while( true );
  }
  goto LAB_0003576e;
LAB_00035998:
  if (9 < (byte)(*tmp_pc3 - 0x30U)) {
    Com_Printf("unknown token in weapon cfg \'%s\' is %s\n",tmp_pc3,param_1);
    goto LAB_00035730;
  }
  local_4e44 = local_4e6c;
LAB_0003576e:
  tmp_pu7 = (uint *)(param_2 + 0x5c);
  do {
    tmp_pc3 = (char *)COM_Parse(&local_4e44);
    if (tmp_pc3 == (char *)0x0) goto LAB_000359d0;
    tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_pu7[-5] = tmp_u4;
    tmp_pc3 = (char *)COM_Parse(&local_4e44);
    if (tmp_pc3 == (char *)0x0) goto LAB_000359d0;
    tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_pu7[-4] = tmp_u4;
    tmp_pc3 = (char *)COM_Parse(&local_4e44);
    if (tmp_pc3 == (char *)0x0) goto LAB_000359d0;
    tmp_d11 = strtod(tmp_pc3,(char **)0x0);
    tmp_u4 = 1000;
    if ((float)tmp_d11 != 0.0) {
      tmp_u4 = (uint)ROUND(1000.0 / (float)tmp_d11);
    }
    tmp_pu7[-2] = tmp_u4;
    tmp_pu7[-1] = tmp_u4;
    tmp_pc3 = (char *)COM_Parse(&local_4e44);
    if (tmp_pc3 == (char *)0x0) goto LAB_000359d0;
    tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_pu7[-3] = tmp_u4;
    if ((int)tmp_pu7[-4] < (int)tmp_u4) {
      tmp_pu7[-3] = tmp_pu7[-4];
LAB_0003578b:
      *tmp_pu7 = 0;
    }
    else {
      if (-1 < (int)tmp_u4) goto LAB_0003578b;
      tmp_pu7[-3] = 0;
      *tmp_pu7 = 0;
    }
    if (tmp_b1) {
      tmp_pc3 = (char *)COM_Parse(&local_4e44);
      if (tmp_pc3 == (char *)0x0) {
LAB_000359d0:
        Com_Printf("Error parsing weapon animation file: %s",param_1);
        return 0;
      }
      tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
      *tmp_pu7 = tmp_u4;
      tmp_pc3 = (char *)COM_Parse(&local_4e44);
      if (tmp_pc3 == (char *)0x0) goto LAB_000359d0;
      tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
      if (tmp_l5 != 0) {
        *tmp_pu7 = *tmp_pu7 | 0x10000;
      }
      tmp_pc3 = (char *)COM_Parse(&local_4e44);
      if (tmp_pc3 == (char *)0x0) goto LAB_000359d0;
      tmp_u4 = *tmp_pu7;
      tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
      *tmp_pu7 = tmp_l5 << 8 | tmp_u4;
    }
    tmp_pu7 = tmp_pu7 + 0x1c;
    if (tmp_pu7 == (uint *)(param_2 + 0x60c)) {
      return 1;
    }
  } while( true );
}

uint32_t BG_RW_ParseDefinition(uint32_t param_1,int param_2,int param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  char *tmp_pc4;
  bool tmp_b5;
  byte tmp_b6;
  char local_474;
  char local_473;
  char local_472;
  char local_471;
  uint8_t local_434 [16];
  char local_424;
  char local_423;
  uint32_t uStack_14;
  
  tmp_b6 = 0;
  uStack_14 = 0x35a1b;
  tmp_i1 = trap_PC_ReadToken(param_1,local_434);
  if (((tmp_i1 == 0) || (local_424 != '{')) || (local_423 != '\0')) {
    return 0;
  }
LAB_00035a70:
  do {
    tmp_i1 = trap_PC_ReadToken(param_1,local_434);
    if ((tmp_i1 == 0) || (local_424 == '}')) {
      return 1;
    }
    tmp_i1 = 5;
    tmp_b5 = false;
    tmp_pc3 = &local_424;
    tmp_pc4 = "name";
    do {
      if (tmp_i1 == 0) break;
      tmp_i1 = tmp_i1 + -1;
      tmp_b5 = *tmp_pc3 == *tmp_pc4;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
      tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
    } while (tmp_b5);
    if (tmp_b5) {
      tmp_i1 = PC_String_ParseNoAlloc(param_1,param_2 + 0x5b4,0x20);
      if (tmp_i1 == 0) {
        tmp_u2 = BG_RW_ParseError(param_1,"name needs string");
        return tmp_u2;
      }
      goto LAB_00035a70;
    }
    tmp_i1 = 7;
    tmp_b5 = false;
    tmp_pc3 = &local_424;
    tmp_pc4 = "damage";
    do {
      if (tmp_i1 == 0) break;
      tmp_i1 = tmp_i1 + -1;
      tmp_b5 = *tmp_pc3 == *tmp_pc4;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
      tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
    } while (tmp_b5);
    if (!tmp_b5) {
      tmp_i1 = 0xd;
      tmp_b5 = false;
      tmp_pc3 = &local_424;
      tmp_pc4 = "splashdamage";
      do {
        if (tmp_i1 == 0) break;
        tmp_i1 = tmp_i1 + -1;
        tmp_b5 = *tmp_pc3 == *tmp_pc4;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
      } while (tmp_b5);
      if (tmp_b5) {
        tmp_i1 = PC_Int_Parse(param_1,param_2 + 0x690);
        if (tmp_i1 == 0) {
          tmp_u2 = BG_RW_ParseError(param_1,"splashdamage needs int");
          return tmp_u2;
        }
      }
      else {
        tmp_i1 = 0x14;
        tmp_b5 = false;
        tmp_pc3 = &local_424;
        tmp_pc4 = "splashdamage_radius";
        do {
          if (tmp_i1 == 0) break;
          tmp_i1 = tmp_i1 + -1;
          tmp_b5 = *tmp_pc3 == *tmp_pc4;
          tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
          tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
        } while (tmp_b5);
        if (tmp_b5) {
          tmp_i1 = PC_Int_Parse(param_1,param_2 + 0x694);
          if (tmp_i1 == 0) {
            tmp_u2 = BG_RW_ParseError(param_1,"splashdamage_radius needs int");
            return tmp_u2;
          }
        }
        else {
          tmp_i1 = 7;
          tmp_b5 = false;
          tmp_pc3 = &local_424;
          tmp_pc4 = "spread";
          do {
            if (tmp_i1 == 0) break;
            tmp_i1 = tmp_i1 + -1;
            tmp_b5 = *tmp_pc3 == *tmp_pc4;
            tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
            tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
          } while (tmp_b5);
          if (tmp_b5) {
            tmp_i1 = PC_Int_Parse(param_1,param_2 + 0x5d8);
            if (tmp_i1 == 0) {
              tmp_u2 = BG_RW_ParseError(param_1,"spread needs int");
              return tmp_u2;
            }
          }
          else {
            tmp_i1 = 9;
            tmp_b5 = false;
            tmp_pc3 = &local_424;
            tmp_pc4 = "coolRate";
            do {
              if (tmp_i1 == 0) break;
              tmp_i1 = tmp_i1 + -1;
              tmp_b5 = *tmp_pc3 == *tmp_pc4;
              tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
              tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
            } while (tmp_b5);
            if (tmp_b5) {
              tmp_i1 = PC_Int_Parse(param_1,param_3 + 0x24);
              if (tmp_i1 == 0) {
                tmp_u2 = BG_RW_ParseError(param_1,"coolRate needs int");
                return tmp_u2;
              }
            }
            else {
              tmp_i1 = 0x14;
              tmp_b5 = false;
              tmp_pc3 = &local_424;
              tmp_pc4 = "defaultStartingAmmo";
              do {
                if (tmp_i1 == 0) break;
                tmp_i1 = tmp_i1 + -1;
                tmp_b5 = *tmp_pc3 == *tmp_pc4;
                tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
              } while (tmp_b5);
              if (tmp_b5) {
                tmp_i1 = PC_Int_Parse(param_1,param_3 + 0xc);
                if (tmp_i1 == 0) {
                  tmp_u2 = BG_RW_ParseError(param_1,"defaultStartingAmmo needs int");
                  return tmp_u2;
                }
              }
              else {
                tmp_i1 = 0x14;
                tmp_b5 = false;
                tmp_pc3 = &local_424;
                tmp_pc4 = "defaultStartingClip";
                do {
                  if (tmp_i1 == 0) break;
                  tmp_i1 = tmp_i1 + -1;
                  tmp_b5 = *tmp_pc3 == *tmp_pc4;
                  tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                  tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                } while (tmp_b5);
                if (tmp_b5) {
                  tmp_i1 = PC_Int_Parse(param_1,param_3 + 0x10);
                  if (tmp_i1 == 0) {
                    tmp_u2 = BG_RW_ParseError(param_1,"defaultStartingClip needs int");
                    return tmp_u2;
                  }
                }
                else {
                  tmp_i1 = 0xe;
                  tmp_b5 = false;
                  tmp_pc3 = &local_424;
                  tmp_pc4 = "fireDelayTime";
                  do {
                    if (tmp_i1 == 0) break;
                    tmp_i1 = tmp_i1 + -1;
                    tmp_b5 = *tmp_pc3 == *tmp_pc4;
                    tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                    tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                  } while (tmp_b5);
                  if (tmp_b5) {
                    tmp_i1 = PC_Int_Parse(param_1,param_3 + 0x18);
                    if (tmp_i1 == 0) {
                      tmp_u2 = BG_RW_ParseError(param_1,"fireDelayTime needs int");
                      return tmp_u2;
                    }
                  }
                  else {
                    tmp_i1 = 8;
                    tmp_b5 = false;
                    tmp_pc3 = &local_424;
                    tmp_pc4 = "maxammo";
                    do {
                      if (tmp_i1 == 0) break;
                      tmp_i1 = tmp_i1 + -1;
                      tmp_b5 = *tmp_pc3 == *tmp_pc4;
                      tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                      tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                    } while (tmp_b5);
                    if (tmp_b5) {
                      tmp_i1 = PC_Int_Parse(param_1,param_3);
                      if (tmp_i1 == 0) {
                        tmp_u2 = BG_RW_ParseError(param_1,"maxammo needs int");
                        return tmp_u2;
                      }
                    }
                    else {
                      tmp_i1 = 8;
                      tmp_b5 = false;
                      tmp_pc3 = &local_424;
                      tmp_pc4 = "maxclip";
                      do {
                        if (tmp_i1 == 0) break;
                        tmp_i1 = tmp_i1 + -1;
                        tmp_b5 = *tmp_pc3 == *tmp_pc4;
                        tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                        tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                      } while (tmp_b5);
                      if (tmp_b5) {
                        tmp_i1 = PC_Int_Parse(param_1,param_3 + 8);
                        if (tmp_i1 == 0) {
                          tmp_u2 = BG_RW_ParseError(param_1,"maxclip needs int");
                          return tmp_u2;
                        }
                      }
                      else {
                        tmp_i1 = 8;
                        tmp_b5 = false;
                        tmp_pc3 = &local_424;
                        tmp_pc4 = "maxHeat";
                        do {
                          if (tmp_i1 == 0) break;
                          tmp_i1 = tmp_i1 + -1;
                          tmp_b5 = *tmp_pc3 == *tmp_pc4;
                          tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                          tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                        } while (tmp_b5);
                        if (tmp_b5) {
                          tmp_i1 = PC_Int_Parse(param_1,param_3 + 0x20);
                          if (tmp_i1 == 0) {
                            tmp_u2 = BG_RW_ParseError(param_1,"maxHeat needs int");
                            return tmp_u2;
                          }
                        }
                        else {
                          tmp_i1 = 0xd;
                          tmp_b5 = false;
                          tmp_pc3 = &local_424;
                          tmp_pc4 = "nextShotTime";
                          do {
                            if (tmp_i1 == 0) break;
                            tmp_i1 = tmp_i1 + -1;
                            tmp_b5 = *tmp_pc3 == *tmp_pc4;
                            tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                            tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                          } while (tmp_b5);
                          if (tmp_b5) {
                            tmp_i1 = PC_Int_Parse(param_1,param_3 + 0x1c);
                            if (tmp_i1 == 0) {
                              tmp_u2 = BG_RW_ParseError(param_1,"nextShotTime needs int");
                              return tmp_u2;
                            }
                          }
                          else {
                            tmp_i1 = 0xb;
                            tmp_b5 = false;
                            tmp_pc3 = &local_424;
                            tmp_pc4 = "reloadTime";
                            do {
                              if (tmp_i1 == 0) break;
                              tmp_i1 = tmp_i1 + -1;
                              tmp_b5 = *tmp_pc3 == *tmp_pc4;
                              tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                              tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                            } while (tmp_b5);
                            if (tmp_b5) {
                              tmp_i1 = PC_Int_Parse(param_1,param_3 + 0x14);
                              if (tmp_i1 == 0) {
                                tmp_u2 = BG_RW_ParseError(param_1,"reloadTime needs int");
                                return tmp_u2;
                              }
                            }
                            else {
                              tmp_i1 = 0xf;
                              tmp_b5 = false;
                              tmp_pc3 = &local_424;
                              tmp_pc4 = "SpreadScaleAdd";
                              do {
                                if (tmp_i1 == 0) break;
                                tmp_i1 = tmp_i1 + -1;
                                tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                              } while (tmp_b5);
                              if (tmp_b5) {
                                tmp_i1 = PC_Int_Parse(param_1,param_2 + 0x5ec);
                                if (tmp_i1 == 0) {
                                  tmp_u2 = BG_RW_ParseError(param_1,"SpreadScaleAdd needs int");
                                  return tmp_u2;
                                }
                              }
                              else {
                                tmp_i1 = 0x13;
                                tmp_b5 = false;
                                tmp_pc3 = &local_424;
                                tmp_pc4 = "SpreadScaleAddRand";
                                do {
                                  if (tmp_i1 == 0) break;
                                  tmp_i1 = tmp_i1 + -1;
                                  tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                  tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                  tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                } while (tmp_b5);
                                if (tmp_b5) {
                                  tmp_i1 = PC_Int_Parse(param_1,param_2 + 0x5f0);
                                  if (tmp_i1 == 0) {
                                    tmp_u2 = BG_RW_ParseError(param_1,
                                                  "aimSpreadScaleAddRand needs int");
                                    return tmp_u2;
                                  }
                                }
                                else {
                                  tmp_i1 = 0xf;
                                  tmp_b5 = false;
                                  tmp_pc3 = &local_424;
                                  tmp_pc4 = "recoilDuration";
                                  do {
                                    if (tmp_i1 == 0) break;
                                    tmp_i1 = tmp_i1 + -1;
                                    tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                    tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                    tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                  } while (tmp_b5);
                                  if (tmp_b5) {
                                    *(uint32_t *)(param_2 + 0x5dc) = 1;
                                    tmp_i1 = PC_Int_Parse(param_1,param_2 + 0x5e0);
                                    if (tmp_i1 == 0) {
                                      tmp_u2 = BG_RW_ParseError(param_1,"recoilDuration needs int");
                                      return tmp_u2;
                                    }
                                  }
                                  else {
                                    tmp_i1 = 10;
                                    tmp_b5 = false;
                                    tmp_pc3 = &local_424;
                                    tmp_pc4 = "recoilYaw";
                                    do {
                                      if (tmp_i1 == 0) break;
                                      tmp_i1 = tmp_i1 + -1;
                                      tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                      tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                      tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                    } while (tmp_b5);
                                    if (tmp_b5) {
                                      *(uint32_t *)(param_2 + 0x5dc) = 1;
                                      tmp_i1 = PC_Float_Parse(param_1,param_2 + 0x5e4);
                                      if (tmp_i1 == 0) {
                                        tmp_u2 = BG_RW_ParseError(param_1,"recoilYaw needs float");
                                        return tmp_u2;
                                      }
                                    }
                                    else {
                                      tmp_i1 = 0xc;
                                      tmp_b5 = false;
                                      tmp_pc3 = &local_424;
                                      tmp_pc4 = "recoilPitch";
                                      do {
                                        if (tmp_i1 == 0) break;
                                        tmp_i1 = tmp_i1 + -1;
                                        tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                        tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                        tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                      } while (tmp_b5);
                                      if (tmp_b5) {
                                        *(uint32_t *)(param_2 + 0x5dc) = 1;
                                        tmp_i1 = PC_Float_Parse(param_1,param_2 + 0x5e8);
                                        if (tmp_i1 == 0) {
                                          tmp_u2 = BG_RW_ParseError(param_1,"recoilPitch needs float"
                                                                  );
                                          return tmp_u2;
                                        }
                                      }
                                      else {
                                        tmp_i1 = 10;
                                        tmp_b5 = false;
                                        tmp_pc3 = &local_424;
                                        tmp_pc4 = "limboKill";
                                        do {
                                          if (tmp_i1 == 0) break;
                                          tmp_i1 = tmp_i1 + -1;
                                          tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                          tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                          tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                        } while (tmp_b5);
                                        if (tmp_b5) {
                                          *(uint32_t *)(param_2 + 0x5f8) = 1;
                                        }
                                        else {
                                          tmp_i1 = 0x10;
                                          tmp_b5 = false;
                                          tmp_pc3 = &local_424;
                                          tmp_pc4 = "noMidclipReload";
                                          do {
                                            if (tmp_i1 == 0) break;
                                            tmp_i1 = tmp_i1 + -1;
                                            tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                            tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                            tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                          } while (tmp_b5);
                                          if (tmp_b5) {
                                            *(uint32_t *)(param_2 + 0x5fc) = 1;
                                          }
                                          else {
                                            tmp_i1 = 0xc;
                                            tmp_b5 = false;
                                            tmp_pc3 = &local_424;
                                            tmp_pc4 = "KillMessage";
                                            do {
                                              if (tmp_i1 == 0) break;
                                              tmp_i1 = tmp_i1 + -1;
                                              tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                              tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                              tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                            } while (tmp_b5);
                                            if (tmp_b5) {
                                              tmp_i1 = PC_String_ParseNoAlloc
                                                                (param_1,param_2 + 0x604,0x40);
                                              if (tmp_i1 == 0) {
                                                tmp_u2 = BG_RW_ParseError(param_1,
                                                  "KillMessage needs string");
                                                return tmp_u2;
                                              }
                                            }
                                            else {
                                              tmp_i1 = 0xd;
                                              tmp_b5 = false;
                                              tmp_pc3 = &local_424;
                                              tmp_pc4 = "KillMessage2";
                                              do {
                                                if (tmp_i1 == 0) break;
                                                tmp_i1 = tmp_i1 + -1;
                                                tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                                tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                                tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                              } while (tmp_b5);
                                              if (tmp_b5) {
                                                tmp_i1 = PC_String_ParseNoAlloc
                                                                  (param_1,param_2 + 0x644,0x40);
                                                if (tmp_i1 == 0) {
                                                  tmp_u2 = BG_RW_ParseError(param_1,
                                                  "KillMessage2 needs string");
                                                  return tmp_u2;
                                                }
                                                goto LAB_00035a70;
                                              }
                                              tmp_i1 = 0xf;
                                              tmp_b5 = false;
                                              tmp_pc3 = &local_424;
                                              tmp_pc4 = "HeadshotWeapon";
                                              do {
                                                if (tmp_i1 == 0) break;
                                                tmp_i1 = tmp_i1 + -1;
                                                tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                                tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                                tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                              } while (tmp_b5);
                                              if (tmp_b5) {
                                                tmp_i1 = PC_String_ParseNoAlloc
                                                                  (param_1,&local_474,0x40);
                                                if (tmp_i1 == 0) {
                                                  tmp_u2 = BG_RW_ParseError(param_1,
                                                  "HeadshotWeapon needs \'yes\' or \'no\'");
                                                  return tmp_u2;
                                                }
                                                if (local_474 == 'y') {
                                                  if (((local_473 == 'e') && (local_472 == 's')) &&
                                                     (local_471 == '\0')) {
                                                    *(uint32_t *)(param_2 + 0x684) = 1;
                                                    goto LAB_00035a70;
                                                  }
                                                }
                                                else if (((local_474 == 'n') && (local_473 == 'o'))
                                                        && (local_472 == '\0')) {
                                                  *(uint32_t *)(param_2 + 0x684) = 2;
                                                  goto LAB_00035a70;
                                                }
                                                Com_Printf("expected yes/no \n");
                                                *(uint32_t *)(param_2 + 0x684) = 0;
                                                goto LAB_00035a70;
                                              }
                                              tmp_i1 = 0x10;
                                              tmp_b5 = false;
                                              tmp_pc3 = &local_424;
                                              tmp_pc4 = "DistanceFalloff";
                                              do {
                                                if (tmp_i1 == 0) break;
                                                tmp_i1 = tmp_i1 + -1;
                                                tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                                tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                                tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                              } while (tmp_b5);
                                              if (tmp_b5) {
                                                tmp_i1 = PC_String_ParseNoAlloc
                                                                  (param_1,&local_474,0x40);
                                                if (tmp_i1 == 0) {
                                                  tmp_u2 = BG_RW_ParseError(param_1,
                                                  "DistanceFalloff needs \'yes\' or \'no\'");
                                                  return tmp_u2;
                                                }
                                                if (local_474 == 'y') {
                                                  if (((local_473 == 'e') && (local_472 == 's')) &&
                                                     (local_471 == '\0')) {
                                                    *(uint32_t *)(param_2 + 0x68c) = 1;
                                                    goto LAB_00035a70;
                                                  }
                                                }
                                                else if (((local_474 == 'n') && (local_473 == 'o'))
                                                        && (local_472 == '\0')) {
                                                  *(uint32_t *)(param_2 + 0x68c) = 2;
                                                  goto LAB_00035a70;
                                                }
                                                Com_Printf("expected yes/no \n");
                                                *(uint32_t *)(param_2 + 0x68c) = 0;
                                                goto LAB_00035a70;
                                              }
                                              tmp_i1 = 0xe;
                                              tmp_b5 = false;
                                              tmp_pc3 = &local_424;
                                              tmp_pc4 = "GibbingWeapon";
                                              do {
                                                if (tmp_i1 == 0) break;
                                                tmp_i1 = tmp_i1 + -1;
                                                tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                                tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                                tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                              } while (tmp_b5);
                                              if (tmp_b5) {
                                                tmp_i1 = PC_String_ParseNoAlloc
                                                                  (param_1,&local_474,0x40);
                                                if (tmp_i1 == 0) {
                                                  tmp_u2 = BG_RW_ParseError(param_1,
                                                  "GibbingWeapon needs \'yes\' or \'no\'");
                                                  return tmp_u2;
                                                }
                                                if (local_474 == 'y') {
                                                  if (((local_473 == 'e') && (local_472 == 's')) &&
                                                     (local_471 == '\0')) {
                                                    *(uint32_t *)(param_2 + 0x688) = 1;
                                                    goto LAB_00035a70;
                                                  }
                                                }
                                                else if (((local_474 == 'n') && (local_473 == 'o'))
                                                        && (local_472 == '\0')) {
                                                  *(uint32_t *)(param_2 + 0x688) = 2;
                                                  goto LAB_00035a70;
                                                }
                                                Com_Printf("expected yes/no \n");
                                                *(uint32_t *)(param_2 + 0x688) = 0;
                                                goto LAB_00035a70;
                                              }
                                              tmp_i1 = 0x13;
                                              tmp_b5 = false;
                                              tmp_pc3 = &local_424;
                                              tmp_pc4 = "movementSpeedScale";
                                              do {
                                                if (tmp_i1 == 0) break;
                                                tmp_i1 = tmp_i1 + -1;
                                                tmp_b5 = *tmp_pc3 == *tmp_pc4;
                                                tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
                                                tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
                                              } while (tmp_b5);
                                              if (tmp_b5) {
                                                tmp_i1 = PC_Float_Parse(param_1,param_2 + 0x600);
                                                if (tmp_i1 == 0) {
                                                  tmp_u2 = BG_RW_ParseError(param_1,
                                                  "movementSpeedScale needs float");
                                                  return tmp_u2;
                                                }
                                              }
                                              else {
                                                tmp_i1 = strcmp(&local_424,"HeadshotRatio");
                                                if (tmp_i1 == 0) {
                                                  tmp_i1 = PC_Float_Parse(param_1,param_2 + 0x69c);
                                                  if (tmp_i1 == 0) {
                                                    tmp_u2 = BG_RW_ParseError(param_1,
                                                  "HeadshotRatio needs float");
                                                  return tmp_u2;
                                                  }
                                                }
                                                else {
                                                  tmp_i1 = strcmp(&local_424,"minHeadshotDamage");
                                                  if (tmp_i1 == 0) {
                                                    tmp_i1 = PC_Int_Parse(param_1,param_2 + 0x698);
                                                    if (tmp_i1 == 0) {
                                                      tmp_u2 = BG_RW_ParseError(param_1,
                                                  "minHeadshotDamage needs int");
                                                  return tmp_u2;
                                                  }
                                                  }
                                                  else {
                                                    tmp_i1 = strcmp(&local_424,"spreadRatio");
                                                    if (tmp_i1 == 0) {
                                                      tmp_i1 = PC_Float_Parse(param_1,param_2 + 0x6a0
                                                                            );
                                                      if (tmp_i1 == 0) {
                                                        tmp_u2 = BG_RW_ParseError(param_1,
                                                  "spreadRatio needs float");
                                                  return tmp_u2;
                                                  }
                                                  goto LAB_00035a70;
                                                  }
                                                  tmp_i1 = strcmp(&local_424,"velocity2spread");
                                                  if (tmp_i1 == 0) {
                                                    tmp_i1 = PC_String_ParseNoAlloc
                                                                      (param_1,&local_474,0x40);
                                                    if (tmp_i1 == 0) {
                                                      tmp_u2 = BG_RW_ParseError(param_1,
                                                  "velocity2spread needs \'yes\' or \'no\'");
                                                  return tmp_u2;
                                                  }
                                                  if (local_474 == 'y') {
                                                    if (((local_473 == 'e') && (local_472 == 's'))
                                                       && (local_471 == '\0')) {
                                                      *(uint32_t *)(param_2 + 0x6a4) = 1;
                                                      goto LAB_00035a70;
                                                    }
                                                  }
                                                  else if (((local_474 == 'n') && (local_473 == 'o')
                                                           ) && (local_472 == '\0')) {
                                                    *(uint32_t *)(param_2 + 0x6a4) = 2;
                                                    goto LAB_00035a70;
                                                  }
                                                  Com_Printf("expected yes/no \n");
                                                  *(uint32_t *)(param_2 + 0x6a4) = 0;
                                                  goto LAB_00035a70;
                                                  }
                                                  tmp_i1 = strcmp(&local_424,"viewchange2spread");
                                                  if (tmp_i1 == 0) {
                                                    tmp_i1 = PC_String_ParseNoAlloc
                                                                      (param_1,&local_474,0x40);
                                                    if (tmp_i1 == 0) {
                                                      tmp_u2 = BG_RW_ParseError(param_1,
                                                  "viewchange2spread needs \'yes\' or \'no\'");
                                                  return tmp_u2;
                                                  }
                                                  if (local_474 == 'y') {
                                                    if (((local_473 == 'e') && (local_472 == 's'))
                                                       && (local_471 == '\0')) {
                                                      *(uint32_t *)(param_2 + 0x6a8) = 1;
                                                      goto LAB_00035a70;
                                                    }
                                                  }
                                                  else if (((local_474 == 'n') && (local_473 == 'o')
                                                           ) && (local_472 == '\0')) {
                                                    *(uint32_t *)(param_2 + 0x6a8) = 2;
                                                    goto LAB_00035a70;
                                                  }
                                                  Com_Printf("expected yes/no \n");
                                                  *(uint32_t *)(param_2 + 0x6a8) = 0;
                                                  goto LAB_00035a70;
                                                  }
                                                  tmp_i1 = strcmp(&local_424,"classes");
                                                  if ((tmp_i1 == 0) &&
                                                     (tmp_i1 = PC_Int_Parse(param_1,param_2 + 0x6ac),
                                                     tmp_i1 == 0)) {
                                                    tmp_u2 = BG_RW_ParseError(param_1,
                                                  "classes needs int");
                                                  return tmp_u2;
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
                    }
                  }
                }
              }
            }
          }
        }
      }
      goto LAB_00035a70;
    }
    tmp_i1 = PC_Int_Parse(param_1,param_2 + 0x5d4);
    if (tmp_i1 == 0) {
      tmp_u2 = BG_RW_ParseError(param_1,"damage needs int");
      return tmp_u2;
    }
  } while( true );
}

uint32_t BG_RegisterWeaponFromWeaponFile(int param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  char *tmp_pc4;
  bool tmp_b5;
  uint8_t tmp_u6;
  uint8_t tmp_u7;
  byte tmp_b8;
  uint8_t local_88c [64];
  uint8_t local_84c [16];
  char local_83c;
  char local_83b;
  uint8_t local_434 [16];
  char local_424;
  char local_423;
  uint32_t uStack_14;
  
  tmp_b8 = 0;
  if (param_1 == 0) {
    return 0;
  }
  uStack_14 = 0x3676b;
  tmp_i1 = trap_PC_ReadToken(param_1,local_84c);
  tmp_b5 = tmp_i1 == 0;
  if (!tmp_b5) {
    tmp_i1 = 10;
    tmp_pc3 = &local_83c;
    tmp_pc4 = "weaponDef";
    do {
      if (tmp_i1 == 0) break;
      tmp_i1 = tmp_i1 + -1;
      tmp_b5 = *tmp_pc3 == *tmp_pc4;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
      tmp_pc4 = tmp_pc4 + (uint)tmp_b8 * -2 + 1;
    } while (tmp_b5);
    if (tmp_b5) {
      tmp_i1 = trap_PC_ReadToken(param_1,local_84c);
      if (((tmp_i1 == 0) || (local_83c != '{')) || (local_83b != '\0')) {
        return 0;
      }
LAB_00036810:
      do {
        do {
          tmp_i1 = trap_PC_ReadToken(param_1,local_84c);
          if ((tmp_i1 == 0) || (local_83c == '}')) {
            trap_PC_FreeSource(param_1);
            return 1;
          }
          tmp_i1 = 7;
          tmp_b5 = false;
          tmp_pc3 = &local_83c;
          tmp_pc4 = "client";
          do {
            if (tmp_i1 == 0) break;
            tmp_i1 = tmp_i1 + -1;
            tmp_b5 = *tmp_pc3 == *tmp_pc4;
            tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
            tmp_pc4 = tmp_pc4 + (uint)tmp_b8 * -2 + 1;
          } while (tmp_b5);
          tmp_u6 = 0;
          if (tmp_b5) {
            tmp_i1 = trap_PC_ReadToken(param_1,local_434);
            tmp_u6 = tmp_i1 == 0;
            if (((!(bool)tmp_u6) && (tmp_u6 = 0, local_424 == '{')) && (tmp_u6 = 0, local_423 == '\0'))
            {
              do {
                do {
                  tmp_i1 = trap_PC_ReadToken(param_1,local_434);
                  tmp_u6 = 1;
                  if ((tmp_i1 == 0) || (tmp_u6 = 1, local_424 == '}')) goto LAB_0003684d;
                  tmp_i1 = 0xd;
                  tmp_b5 = false;
                  tmp_pc3 = &local_424;
                  tmp_pc4 = "weaponConfig";
                  do {
                    if (tmp_i1 == 0) break;
                    tmp_i1 = tmp_i1 + -1;
                    tmp_b5 = *tmp_pc3 == *tmp_pc4;
                    tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
                    tmp_pc4 = tmp_pc4 + (uint)tmp_b8 * -2 + 1;
                  } while (tmp_b5);
                } while (!tmp_b5);
                tmp_i1 = PC_String_ParseNoAlloc(param_1,local_88c,0x40);
                tmp_u6 = tmp_i1 == 0;
                if ((bool)tmp_u6) {
                  BG_RW_ParseError(param_1,"missing weaponConfig string!!!");
                  goto LAB_0003684d;
                }
                tmp_i1 = BG_ParseWeaponConfig();
                tmp_u6 = tmp_i1 == 0;
              } while (!(bool)tmp_u6);
              BG_RW_ParseError(param_1,"error in weaponConfig!!!");
            }
          }
LAB_0003684d:
          tmp_i1 = 5;
          tmp_pc3 = &local_83c;
          tmp_pc4 = "both";
          do {
            if (tmp_i1 == 0) break;
            tmp_i1 = tmp_i1 + -1;
            tmp_u6 = *tmp_pc3 == *tmp_pc4;
            tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
            tmp_pc4 = tmp_pc4 + (uint)tmp_b8 * -2 + 1;
          } while ((bool)tmp_u6);
          tmp_u7 = 0;
          if ((bool)tmp_u6) {
            tmp_u7 = param_3 == 0;
            if ((bool)tmp_u7) {
              BG_RW_ParseDefinition(param_2);
            }
            else {
              tmp_i1 = trap_PC_ReadToken(param_1,local_434);
              tmp_u7 = tmp_i1 == 0;
              if (((!(bool)tmp_u7) && (tmp_u7 = 0, local_424 == '{')) &&
                 (tmp_u7 = 0, local_423 == '\0')) {
                do {
                  tmp_i1 = trap_PC_ReadToken(param_1,local_434);
                  if (tmp_i1 == 0) {
                    tmp_u7 = 1;
                    break;
                  }
                  tmp_u7 = local_424 == '}';
                } while (!(bool)tmp_u7);
              }
            }
          }
          tmp_i1 = 0xd;
          tmp_pc3 = &local_83c;
          tmp_pc4 = "both_altweap";
          do {
            if (tmp_i1 == 0) break;
            tmp_i1 = tmp_i1 + -1;
            tmp_u7 = *tmp_pc3 == *tmp_pc4;
            tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
            tmp_pc4 = tmp_pc4 + (uint)tmp_b8 * -2 + 1;
          } while ((bool)tmp_u7);
        } while (!(bool)tmp_u7);
        if (param_3 == 0) {
          tmp_i1 = trap_PC_ReadToken(param_1,local_434);
          if (((tmp_i1 != 0) && (local_424 == '{')) && (local_423 == '\0')) {
            do {
              tmp_i1 = trap_PC_ReadToken(param_1,local_434);
              if (tmp_i1 == 0) break;
            } while (local_424 != '}');
          }
          goto LAB_00036810;
        }
        BG_RW_ParseDefinition(param_2);
      } while( true );
    }
  }
  tmp_u2 = BG_RW_ParseError(param_1,"expected \'weaponDef\'");
  return tmp_u2;
}

void BG_RegisterWeapon(uint param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t *tmp_pu4;
  char *tmp_pc5;
  
  if ((param_1 < 0x34) && ((param_2 != 0 || (*(int *)(BG_Weapons + param_1 * 0x6b0) == 0)))) {
    tmp_pu4 = (uint32_t *)(BG_Weapons + param_1 * 0x6b0);
    for (tmp_i2 = 0x1ac; tmp_i2 != 0; tmp_i2 = tmp_i2 + -1) {
      *tmp_pu4 = 0;
      tmp_pu4 = tmp_pu4 + 1;
    }
    *(uint32_t *)(BG_Weapons + param_1 * 0x6b0) = 1;
    *(uint *)(BG_Weapons + param_1 * 0x6b0 + 0x5f4) = param_1;
    switch(param_1) {
    default:
      goto _L221;
    case 1:
      tmp_pc3 = "knife.weap";
      break;
    case 2:
      tmp_pc3 = "luger.weap";
      break;
    case 3:
      tmp_pc3 = "mp40.weap";
      break;
    case 4:
      tmp_pc3 = "grenade.weap";
      break;
    case 5:
      tmp_pc3 = "panzerfaust.weap";
      break;
    case 6:
      tmp_pc3 = "flamethrower.weap";
      break;
    case 7:
      tmp_pc3 = "colt.weap";
      break;
    case 8:
      tmp_pc3 = "thompson.weap";
      break;
    case 9:
      tmp_pc3 = "pineapple.weap";
      break;
    case 10:
      tmp_pc3 = "sten.weap";
      break;
    case 0xb:
      tmp_pc3 = "syringe.weap";
      break;
    case 0xc:
      tmp_pc3 = "ammopack.weap";
      break;
    case 0xe:
      tmp_pc3 = "silenced_luger.weap";
      break;
    case 0xf:
      tmp_pc3 = "dynamite.weap";
      break;
    case 0x10:
      tmp_pc3 = "smoketrail.weap";
      break;
    case 0x12:
      tmp_pc3 = "medpack.weap";
      break;
    case 0x13:
      tmp_pc3 = "binocs.weap";
      break;
    case 0x14:
      tmp_pc3 = "pliers.weap";
      break;
    case 0x15:
      tmp_pc3 = "smokemarker.weap";
      break;
    case 0x16:
      tmp_pc3 = "kar98.weap";
      break;
    case 0x17:
      tmp_pc3 = "m1_garand.weap";
      break;
    case 0x18:
      tmp_pc3 = "m1_garand_s.weap";
      break;
    case 0x19:
      tmp_pc3 = "landmine.weap";
      break;
    case 0x1a:
      tmp_pc3 = "satchel.weap";
      break;
    case 0x1b:
      tmp_pc3 = "satchel_det.weap";
      break;
    case 0x1c:
      tmp_pc3 = "smokegrenade.weap";
      break;
    case 0x1d:
      tmp_pc3 = "mg42.weap";
      break;
    case 0x1e:
      tmp_pc3 = "k43.weap";
      break;
    case 0x1f:
      tmp_pc3 = "fg42.weap";
      break;
    case 0x21:
      tmp_pc3 = "mortar.weap";
      break;
    case 0x22:
      tmp_pc3 = "akimbo_colt.weap";
      break;
    case 0x23:
      tmp_pc3 = "akimbo_luger.weap";
      break;
    case 0x24:
      tmp_pc3 = "gpg40.weap";
      break;
    case 0x25:
      tmp_pc3 = "m7.weap";
      break;
    case 0x26:
      tmp_pc3 = "silenced_colt.weap";
      break;
    case 0x27:
      tmp_pc3 = "m1_garand_s.weap";
      break;
    case 0x28:
      tmp_pc3 = "k43.weap";
      break;
    case 0x29:
      tmp_pc3 = "fg42.weap";
      break;
    case 0x2a:
      tmp_pc3 = "mortar_set.weap";
      break;
    case 0x2b:
      tmp_pc3 = "adrenaline.weap";
      break;
    case 0x2c:
      tmp_pc3 = "akimbo_silenced_colt.weap";
      break;
    case 0x2d:
      tmp_pc3 = "akimbo_silenced_luger.weap";
      break;
    case 0x2e:
      tmp_pc3 = "mg42.weap";
      break;
    case 0x2f:
      tmp_pc3 = "poison.weap";
      break;
    case 0x30:
      tmp_pc3 = "bomb.weap";
      break;
    case 0x31:
      tmp_pc3 = "tripmine.weap";
      break;
    case 0x32:
      tmp_pc3 = "poisongas.weap";
      break;
    case 0x33:
      tmp_pc3 = "landmine_pgas.weap";
    }
    tmp_pc5 = tmp_pc3;
    tmp_u1 = va("%s/%s",0x3128bb8,tmp_pc3);
    tmp_i2 = trap_PC_LoadSource(tmp_u1);
    if (tmp_i2 == 0) {
      tmp_u1 = va("weapons/%s",tmp_pc3,tmp_pc5);
      trap_PC_LoadSource(tmp_u1);
    }
    BG_RegisterWeaponFromWeaponFile();
    return;
  }
_L221:
  return;
}

uint BG_IsFile(char *param_1)
{
  int tmp_i1;
  stat local_64;
  
  tmp_i1 = __xstat(3,param_1,&local_64);
  if (tmp_i1 != -1) {
    return (local_64.st_mode >> 0xe ^ 1) & 1;
  }
  return 0;
}

uint BG_IsDirectory(char *param_1)
{
  int tmp_i1;
  stat local_64;
  
  tmp_i1 = __xstat(3,param_1,&local_64);
  if (tmp_i1 != -1) {
    return local_64.st_mode >> 0xe & 1;
  }
  return 0;
}

bool BG_DeleteFile(char *param_1)
{
  int tmp_i1;
  
  tmp_i1 = unlink(param_1);
  return tmp_i1 != -1;
}

bool BG_RenameFile(char *param_1,char *param_2)
{
  int tmp_i1;
  
  tmp_i1 = rename(param_1,param_2);
  return tmp_i1 == 0;
}

bool PC_Char_Parse(uint32_t param_1,uint8_t *param_2)
{
  int tmp_i1;
  uint8_t local_424 [16];
  uint8_t local_414;
  
  tmp_i1 = trap_PC_ReadToken(param_1,local_424);
  if (tmp_i1 != 0) {
    *param_2 = local_414;
  }
  return tmp_i1 != 0;
}

uint32_t PC_Script_Parse(uint32_t param_1,uint32_t *param_2)
{
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
    tmp_i1 = Q_stricmp(&local_1424,"{");
    if (tmp_i1 == 0) {
      while (tmp_i1 = trap_PC_ReadToken(param_1,local_1434), tmp_i1 != 0) {
        tmp_i1 = Q_stricmp(&local_1424,&g_unk_0010c012);
        if (tmp_i1 == 0) {
          tmp_u2 = String_Alloc(&local_101c);
          *param_2 = tmp_u2;
          return 1;
        }
        if (local_1423 == '\0') {
          Q_strcat(&local_101c,0x1000,&local_1424);
        }
        else {
          tmp_u2 = va(&g_unk_00120861,&local_1424);
          Q_strcat(&local_101c,0x1000,tmp_u2);
        }
        Q_strcat(&local_101c,0x1000,&g_unk_0011d7f6);
      }
    }
  }
  return 0;
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
  
  local_8 = 0x102546;
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
  uint8_t *tmp_pu7;
  int tmp_i8;
  uint32_t tmp_u9;
  char *tmp_pc10;
  char local_11d [269];
  
  if (*(int *)(param_1 + 0x18) == 0) {
    trap_Cvar_VariableStringBuffer(*(uint32_t *)(param_1 + 4),local_11d,0x101);
    if ((param_1 == bg_focusButton) && ((*(int *)(DC + 0x11c) / 1000 & 1U) != 0)) {
      tmp_i6 = trap_Key_GetOverstrikeMode();
      if (tmp_i6 == 0) {
        tmp_pu7 = &g_unk_00120ae5;
      }
      else {
        tmp_pu7 = &g_unk_00120add;
      }
    }
    else {
      tmp_pu7 = &g_unk_0011d7f6;
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
    tmp_u9 = va("^7%s",tmp_pc10);
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    (*tmp_pc2)(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14),
              *tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u9,0,0,tmp_u4,tmp_u3);
    return;
  }
  if ((param_1 == bg_focusButton) && ((*(int *)(DC + 0x11c) / 1000 & 1U) != 0)) {
    tmp_i6 = (**(void **)(DC + 0x84))();
    if (tmp_i6 == 0) {
      tmp_pc5 = (char *)va(&g_unk_00120ae1,*(uint32_t *)(param_1 + 4));
    }
    else {
      tmp_pc5 = (char *)va(&g_unk_00120ad9,*(uint32_t *)(param_1 + 4));
    }
  }
  else {
    tmp_pc5 = (char *)va(&g_unk_00120ae9,*(uint32_t *)(param_1 + 4));
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

