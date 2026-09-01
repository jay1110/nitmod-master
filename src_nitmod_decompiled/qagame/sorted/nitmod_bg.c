/* Shared bg_* animation, items, weapons tables — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_bg.h"

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
        if (param_1[tmp_i1] == '\0') goto LAB_0002bb82;
      }
      tmp_i4 = tmp_i4 + (param_1[tmp_i3 + -0x77] + 0x20) * tmp_i3;
      tmp_i1 = tmp_i3 + -0x76;
      tmp_i2 = (int)param_1[tmp_i1];
      tmp_i3 = tmp_i3 + 1;
    } while (param_1[tmp_i1] != '\0');
LAB_0002bb82:
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
  Com_Error(2,&g_unk_0024e6e9,local_40c);
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
    tmp_i7 = Q_stricmp(tmp_pc6,&g_unk_0023ac32);
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
LAB_0002c188:
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
          if (*tmp_pc14 == '\0') goto LAB_0002bdbe;
        }
        tmp_pc14 = tmp_pc14 + 1;
        tmp_i7 = (tmp_c3 + 0x20) * tmp_i12;
        tmp_i12 = tmp_i12 + 1;
        local_40 = local_40 + tmp_i7;
        tmp_i7 = (int)*tmp_pc14;
      } while (*tmp_pc14 != '\0');
LAB_0002bdbe:
      if (local_40 == (uint8_t *)0xffffffff) goto LAB_0002c188;
    }
    if (animBodyPartsStr == (uint8_t *)0x0) {
LAB_0002c080:
      *(uint16_t *)(local_38 + local_2c * 2) = 0xffff;
LAB_0002c08e:
      tmp_s10 = strlen(tmp_pc6);
      *param_1 = *param_1 - tmp_s10;
LAB_0002c0b0:
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
          if (*(void **)(&g_unk_01fd8900 + globalScriptData) == (void *)0x0) {
            tmp_u5 = 0;
          }
          else {
            tmp_u5 = (**(void **)(&g_unk_01fd8900 + globalScriptData))(tmp_pc6);
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
        if (local_40 == tmp_ppu13[1]) goto LAB_0002be80;
LAB_0002bdfa:
        tmp_ppu13 = tmp_ppu13 + 2;
        tmp_pc14 = *tmp_ppu13;
        tmp_s4 = tmp_s4 + 1;
        if (tmp_pc14 == (char *)0x0) goto LAB_0002c080;
      }
      tmp_i7 = (int)*tmp_pc14;
      if (*tmp_pc14 == '\0') {
LAB_0002c070:
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
            if (*tmp_pc14 == '\0') goto LAB_0002be5e;
          }
          tmp_pc14 = tmp_pc14 + 1;
          tmp_i7 = (tmp_c3 + 0x20) * tmp_i12;
          tmp_i12 = tmp_i12 + 1;
          tmp_pu15 = tmp_pu15 + tmp_i7;
          tmp_i7 = (int)*tmp_pc14;
        } while (*tmp_pc14 != '\0');
LAB_0002be5e:
        if (tmp_pu15 == (uint8_t *)0xffffffff) goto LAB_0002c070;
      }
      tmp_ppu13[1] = tmp_pu15;
      if (local_40 != tmp_pu15) goto LAB_0002bdfa;
LAB_0002be80:
      tmp_i7 = Q_stricmp(tmp_pc6,*tmp_ppu13);
      if (tmp_i7 != 0) goto LAB_0002bdfa;
      psVar2 = (short *)(local_38 + local_2c * 2);
      *psVar2 = tmp_s4;
      if (tmp_s4 < 1) goto LAB_0002c08e;
      tmp_pc6 = (char *)COM_ParseExt(param_1,0);
      if (tmp_pc6 == (char *)0x0) {
        tmp_i7 = -1;
        BG_AnimParseError("BG_ParseCommands: expected animation");
        goto LAB_0002bf47;
      }
      tmp_c3 = *tmp_pc6;
      if (tmp_c3 == '\0') {
        BG_AnimParseError("BG_ParseCommands: expected animation");
        tmp_c3 = *tmp_pc6;
        if (tmp_c3 == '\0') goto LAB_0002c1c6;
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
LAB_0002c1c6:
        tmp_i7 = 0;
      }
LAB_0002bf47:
      tmp_i9 = 0;
      tmp_i12 = *(int *)(param_3 + 0x89c);
      if (tmp_i12 < 1) {
LAB_0002bfa4:
        tmp_i7 = -1;
        BG_AnimParseError("BG_AnimationIndexForString: unknown index \'%s\' for animation group \'%s\'"
                          ,tmp_pc6,param_3);
      }
      else {
        while( true ) {
          while (tmp_i8 = *(int *)(param_3 + 0x9c + tmp_i9 * 4), *(int *)(tmp_i8 + 100) != tmp_i7) {
            tmp_i9 = tmp_i9 + 1;
            if (tmp_i12 <= tmp_i9) goto LAB_0002bfa4;
          }
          tmp_i12 = Q_stricmp(tmp_pc6,tmp_i8 + 4);
          if (tmp_i12 == 0) break;
          tmp_i12 = *(int *)(param_3 + 0x89c);
          tmp_i9 = tmp_i9 + 1;
          if (tmp_i12 <= tmp_i9) goto LAB_0002bfa4;
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
      if ((*psVar2 == 3) || (local_2c != 0)) goto LAB_0002c0b0;
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
          if (*tmp_pc5 == '\0') goto LAB_0002c30e;
        }
        tmp_pc5 = tmp_pc5 + 1;
        tmp_i2 = (tmp_c1 + 0x20) * tmp_i3;
        tmp_i3 = tmp_i3 + 1;
        local_2c = local_2c + tmp_i2;
        tmp_i2 = (int)*tmp_pc5;
      } while (*tmp_pc5 != '\0');
LAB_0002c30e:
      if (local_2c != -1) goto LAB_0002c31f;
    }
    local_2c = 0;
  }
LAB_0002c31f:
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
LAB_0002c3f0:
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
            if (*tmp_pc5 == '\0') goto LAB_0002c3ae;
          }
          tmp_pc5 = tmp_pc5 + 1;
          tmp_i3 = (tmp_c1 + 0x20) * tmp_i4;
          tmp_i4 = tmp_i4 + 1;
          tmp_i2 = tmp_i2 + tmp_i3;
          tmp_i3 = (int)*tmp_pc5;
        } while (*tmp_pc5 != '\0');
LAB_0002c3ae:
        if (tmp_i2 == -1) goto LAB_0002c3f0;
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
          if (*tmp_pc4 == '\0') goto LAB_0002c4bd;
        }
        tmp_pc4 = tmp_pc4 + 1;
        tmp_i3 = (tmp_c1 + 0x20) * tmp_i5;
        tmp_i5 = tmp_i5 + 1;
        local_20 = local_20 + tmp_i3;
        tmp_i3 = (int)*tmp_pc4;
      } while (*tmp_pc4 != '\0');
LAB_0002c4bd:
      if (local_20 != -1) goto LAB_0002c4cc;
    }
    local_20 = 0;
  }
LAB_0002c4cc:
  tmp_i3 = *(int *)(param_2 + 0x89c);
  tmp_i5 = 0;
  if (0 < tmp_i3) {
    do {
      while (tmp_i2 = *(int *)(param_2 + 0x9c + tmp_i5 * 4), *(int *)(tmp_i2 + 100) != local_20) {
        tmp_i5 = tmp_i5 + 1;
        if (tmp_i3 <= tmp_i5) goto LAB_0002c520;
      }
      tmp_i3 = Q_stricmp(param_1,tmp_i2 + 4);
      if (tmp_i3 == 0) {
        return tmp_i2;
      }
      tmp_i3 = *(int *)(param_2 + 0x89c);
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 < tmp_i3);
  }
LAB_0002c520:
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
          if (*tmp_pc5 == '\0') goto LAB_0002c5ee;
        }
        tmp_pc5 = tmp_pc5 + 1;
        tmp_i2 = (tmp_c1 + 0x20) * tmp_i3;
        tmp_i3 = tmp_i3 + 1;
        local_24 = local_24 + tmp_i2;
        tmp_i2 = (int)*tmp_pc5;
      } while (*tmp_pc5 != '\0');
LAB_0002c5ee:
      if (local_24 != -1) goto LAB_0002c5ff;
    }
    local_24 = 0;
  }
LAB_0002c5ff:
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
LAB_0002c6d0:
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
            if (*tmp_pc5 == '\0') goto LAB_0002c68e;
          }
          tmp_pc5 = tmp_pc5 + 1;
          tmp_i3 = (tmp_c1 + 0x20) * tmp_i4;
          tmp_i4 = tmp_i4 + 1;
          tmp_i2 = tmp_i2 + tmp_i3;
          tmp_i3 = (int)*tmp_pc5;
        } while (*tmp_pc5 != '\0');
LAB_0002c68e:
        if (tmp_i2 == -1) goto LAB_0002c6d0;
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
    *(uint32_t *)((int)&g_unk_00882044 + tmp_u2) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x1a0);
  local_2c = &weaponStrings;
  tmp_i4 = 0;
  do {
    tmp_pi5 = (int *)(bg_itemlist + 0x38);
    if (GHIDRA_FIELD(bg_itemlist, 56, 4) != 0) {
LAB_0002c835:
      if ((tmp_pi5[9] != 1) || (tmp_pi5[10] != tmp_i4)) break;
      tmp_pc6 = (char *)tmp_pi5[7];
      *local_2c = tmp_pc6;
      if (tmp_pc6 == (char *)0x0) {
        tmp_i8 = -1;
      }
      else {
        tmp_c1 = *tmp_pc6;
        if (tmp_c1 == '\0') goto LAB_0002c953;
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
LAB_0002c953:
          tmp_i8 = 0;
        }
      }
      tmp_i7 = *tmp_pi5;
      local_2c[1] = tmp_i8;
      if (tmp_i7 == 0) goto LAB_0002c8e4;
      goto LAB_0002c8c6;
    }
LAB_0002c8e4:
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
        tmp_c1 = *(char *)(tmp_i8 + 0x23abbe);
        tmp_i8 = tmp_i8 + 1;
        if (tmp_c1 == '\0') goto LAB_0002c938;
      }
      tmp_i7 = tmp_i7 + (tmp_i9 + 0x20) * tmp_i8;
      tmp_c1 = *(char *)(tmp_i8 + 0x23abbe);
      tmp_i8 = tmp_i8 + 1;
    } while (tmp_c1 != '\0');
LAB_0002c938:
    if (tmp_i7 == -1) {
      tmp_i7 = 0;
    }
    local_2c[1] = tmp_i7;
LAB_0002c8c6:
    tmp_i4 = tmp_i4 + 1;
    local_2c = local_2c + 2;
    if (tmp_i4 == 0x34) {
      return;
    }
  } while( true );
  tmp_pi5 = tmp_pi5 + 0xe;
  if (*tmp_pi5 == 0) goto LAB_0002c8e4;
  goto LAB_0002c835;
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
LAB_0002c9c0:
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
        if (!tmp_b11) goto LAB_0002cbbe;
LAB_0002cad0:
        tmp_b11 = true;
LAB_0002cadf:
        tmp_i4 = Q_stricmp();
      }
      else {
        if (tmp_b11) goto LAB_0002cad0;
LAB_0002cbbe:
        tmp_i4 = Q_stricmp();
        if ((tmp_i4 == 0) || (tmp_i4 = Q_stricmp(), tmp_i4 == 0)) goto LAB_0002cadf;
        tmp_s6 = strlen(tmp_pc3);
        tmp_b12 = tmp_pc3[tmp_s6 - 1] == ',';
        if (tmp_b12) {
          tmp_pc3[tmp_s6 - 1] = '\0';
        }
        tmp_b11 = tmp_b12 || tmp_b11;
        Q_strcat();
        tmp_i4 = Q_stricmp();
      }
      if (((tmp_i4 != 0) && (tmp_i4 = Q_stricmp(), tmp_i4 != 0)) && (!tmp_b11)) goto LAB_0002c9c0;
      if (tmp_b11) {
        BG_AnimParseError();
      }
      else {
        tmp_i4 = Q_stricmp();
        if (tmp_i4 == 0) {
          tmp_b2 = true;
          goto LAB_0002c9c0;
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
LAB_0002ce30:
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
                    if (*tmp_pc3 == '\0') goto LAB_0002cdce;
                  }
                  tmp_pc3 = tmp_pc3 + 1;
                  tmp_i7 = (tmp_c1 + 0x20) * tmp_i10;
                  tmp_i10 = tmp_i10 + 1;
                  tmp_i4 = tmp_i4 + tmp_i7;
                } while (*tmp_pc3 != '\0');
LAB_0002cdce:
                if (tmp_i4 == -1) goto LAB_0002ce30;
              }
              tmp_pu9[1] = tmp_i4;
            }
            if ((tmp_i4 == 0) && (tmp_i4 = Q_stricmp(), tmp_i4 == 0)) {
              local_84 = param_3 * 0x10 + local_84;
              local_64 = (&defineBits)[local_84 * 2];
              local_60 = (&g_unk_002bd4e4)[local_84 * 2];
              goto LAB_0002cb52;
            }
            tmp_pu9 = tmp_pu9 + 2;
            tmp_pc3 = (char *)*tmp_pu9;
            local_84 = local_84 + 1;
          } while (tmp_pc3 != (char *)0x0);
        }
        BG_IndexForString_constprop_4();
        COM_BitSet();
      }
LAB_0002cb52:
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
  
  uStack_14 = 0x2cedd;
  local_20 = 0;
  local_24 = 0;
  do {
    local_3c = (char *)COM_ParseExt(param_1,0);
    if ((local_3c == (char *)0x0) || (*local_3c == '\0')) goto LAB_0002d20e;
    tmp_i2 = Q_stricmp(local_3c,"default");
    if (tmp_i2 == 0) {
      return 1;
    }
    tmp_i2 = Q_stricmp(local_3c,&g_unk_0024806c);
    if ((tmp_i2 == 0) || (tmp_i2 = Q_stricmp(local_3c,"MINUS"), tmp_i2 == 0)) {
      local_3c = (char *)COM_ParseExt(param_1,0);
      if ((local_3c == (char *)0x0) || (tmp_c1 = *local_3c, tmp_c1 == '\0')) {
LAB_0002d20e:
        if (*param_2 == 0) {
          BG_AnimParseError("BG_ParseConditions: no conditions found");
        }
        return 1;
      }
      local_34 = 1;
LAB_0002cf90:
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
          if (*tmp_pc6 == '\0') goto LAB_0002cfce;
        }
        tmp_pc6 = tmp_pc6 + 1;
        tmp_i2 = (tmp_c1 + 0x20) * tmp_i4;
        tmp_i4 = tmp_i4 + 1;
        local_44 = local_44 + tmp_i2;
        tmp_i2 = (int)*tmp_pc6;
      } while (*tmp_pc6 != '\0');
LAB_0002cfce:
      if (local_44 == (uint8_t *)0xffffffff) goto LAB_0002d1f0;
    }
    else {
      local_34 = 0;
      tmp_c1 = *local_3c;
      if (tmp_c1 != '\0') goto LAB_0002cf90;
LAB_0002d1f0:
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
LAB_0002d158:
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
                if (*tmp_pc6 == '\0') goto LAB_0002d06e;
              }
              tmp_pc6 = tmp_pc6 + 1;
              tmp_i2 = (tmp_c1 + 0x20) * tmp_i4;
              tmp_i4 = tmp_i4 + 1;
              tmp_pu7 = tmp_pu7 + tmp_i2;
              tmp_i2 = (int)*tmp_pc6;
            } while (*tmp_pc6 != '\0');
LAB_0002d06e:
            if (tmp_pu7 == (uint8_t *)0xffffffff) goto LAB_0002d158;
          }
          tmp_ppu5[1] = tmp_pu7;
        }
        if ((local_44 == tmp_pu7) && (tmp_i2 = Q_stricmp(local_3c,*tmp_ppu5), tmp_i2 == 0)) {
          tmp_i2 = *(int *)(animConditionsTable + local_40 * 8);
          goto joined_r0x0002d186;
        }
        tmp_ppu5 = tmp_ppu5 + 2;
        tmp_pc6 = *tmp_ppu5;
        local_40 = local_40 + 1;
      } while (tmp_pc6 != (char *)0x0);
    }
    local_40 = -1;
    BG_AnimParseError("BG_IndexForString: unknown token \'%s\'",local_3c);
    tmp_i2 = __JCR_END__;
joined_r0x0002d186:
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
  
  uStack_14 = 0x2d253;
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
    *(uint32_t *)((int)&g_unk_002c1224 + tmp_u4) = 0;
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
LAB_0002d330:
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
        if (*tmp_pc17 == '\0') goto LAB_0002d38e;
      }
      tmp_pc17 = tmp_pc17 + 1;
      tmp_i11 = (tmp_c2 + 0x20) * tmp_i13;
      tmp_i13 = tmp_i13 + 1;
      tmp_pu16 = tmp_pu16 + tmp_i11;
      tmp_i11 = (int)*tmp_pc17;
    } while (*tmp_pc17 != '\0');
LAB_0002d38e:
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
LAB_0002d4a0:
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
                if (*tmp_pc17 == '\0') goto LAB_0002d42e;
              }
              tmp_pc17 = tmp_pc17 + 1;
              tmp_i11 = (tmp_c2 + 0x20) * tmp_i13;
              tmp_i13 = tmp_i13 + 1;
              tmp_pu16 = tmp_pu16 + tmp_i11;
              tmp_i11 = (int)*tmp_pc17;
            } while (*tmp_pc17 != '\0');
LAB_0002d42e:
            if (tmp_pu16 == (uint8_t *)0xffffffff) goto LAB_0002d4a0;
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
            goto LAB_0002d330;
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
                if (*tmp_pc19 == '\0') goto LAB_0002d631;
              }
              tmp_pc19 = tmp_pc19 + 1;
              tmp_i8 = (tmp_c2 + 0x20) * tmp_i15;
              tmp_i15 = tmp_i15 + 1;
              tmp_i13 = tmp_i13 + tmp_i8;
              tmp_i8 = (int)*tmp_pc19;
            } while (*tmp_pc19 != '\0');
LAB_0002d631:
            if (tmp_i13 != -1) goto LAB_0002d642;
          }
          tmp_i13 = 0;
        }
LAB_0002d642:
        (&g_unk_002bdfe4)[(tmp_i11 * 0x10 + local_23c) * 2] = tmp_i13;
        tmp_i13 = COM_ParseExt(&local_204,0);
        if (tmp_i13 == 0) {
          BG_AnimParseError("BG_AnimParseAnimScript: expected \'=\', found end of line");
        }
        tmp_i8 = Q_stricmp(tmp_i13,&g_unk_0026f609);
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
          *(uint32_t *)((int)&g_unk_002be0e0 + tmp_u4) = *(uint32_t *)((int)&defineStr + tmp_u4);
          tmp_u4 = tmp_u4 + 4;
        } while (tmp_u4 < 0x80);
        tmp_u4 = 0;
        do {
          *(uint32_t *)((int)&g_unk_002bd5e0 + tmp_u4) = *(uint32_t *)((int)&defineBits + tmp_u4);
          tmp_u4 = tmp_u4 + 4;
        } while (tmp_u4 < 0x80);
        g_unk_002c1228 = numDefines;
      }
      goto LAB_0002d330;
    }
    tmp_pc19 = tmp_pc1;
    tmp_i11 = Q_stricmp(tmp_pc5);
    if (tmp_i11 == 0) goto LAB_0002d737;
    tmp_pc19 = "}";
    tmp_i11 = Q_stricmp(tmp_pc5);
    if (tmp_i11 == 0) {
      if (local_224 + -1 < 0) goto LAB_0002dcca;
      tmp_pi9 = (int *)0x0;
      if (local_224 + -1 != 1) {
        tmp_pi9 = local_220;
      }
      goto LAB_0002d7c8;
    }
    if (local_224 == 0) {
      if (-1 < local_200[0]) goto LAB_0002d88a;
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
        if (-1 < local_200[1]) goto LAB_0002d88a;
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
        goto LAB_0002d93e;
      }
      if (local_224 != 2) {
        if (local_224 != 3) goto LAB_0002d88a;
        goto LAB_0002da26;
      }
      if (-1 < local_200[2]) goto LAB_0002d88a;
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
      local_220[tmp_i13 + 1] =
           (int)("_ZN11ETInterface11DebugRadiusEPKffRK7obColorf" + tmp_i11 * 0x1d8 + param_1 + 4);
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
LAB_0002d737:
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
      goto LAB_0002d330;
    }
    tmp_pc19 = "}";
    tmp_i11 = Q_stricmp(tmp_pc5);
    if (tmp_i11 == 0) {
      if (local_224 + -1 < 0) {
LAB_0002dcca:
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
LAB_0002d7c8:
      local_220 = tmp_pi9;
      local_224 = local_224 + -1;
      local_200[local_224] = -1;
      goto LAB_0002d330;
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
LAB_0002d93e:
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
        goto LAB_0002d330;
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
        local_220[tmp_i13 + 1] =
             (int)("_ZN11ETInterface11DebugRadiusEPKffRK7obColorf" + tmp_i11 * 0x1d8 + param_1 + 4);
        tmp_i11 = local_220[*local_220 + 1];
        *local_220 = *local_220 + 1;
        tmp_u4 = 0;
        do {
          tmp_u3 = *(uint32_t *)((int)auStack_1f0 + tmp_u4);
          *(uint32_t *)(tmp_i11 + tmp_u4) = *(uint32_t *)((int)auStack_1f0 + (tmp_u4 - 4));
          *(uint32_t *)(tmp_i11 + 4 + tmp_u4) = tmp_u3;
          tmp_u4 = tmp_u4 + 8;
        } while (tmp_u4 < 0x1d8);
        goto LAB_0002d330;
      }
    }
    else if (local_224 == 2) {
LAB_0002da26:
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
      goto LAB_0002d330;
    }
LAB_0002d88a:
    BG_AnimParseError("BG_AnimParseAnimScript: unexpected \'%s\'",tmp_pc5);
    tmp_pc19 = tmp_pc5;
  }
  goto LAB_0002d330;
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
           ((*(uint *)(&g_unk_01fd5d04 + tmp_i1 * 8 + globalScriptData) & tmp_pi3[2]) != 0))
        goto LAB_0002dee0;
LAB_0002de80:
        if (tmp_pi3[3] == 0) {
          return 0;
        }
      }
      else {
        if ((*(int *)(animConditionsTable + tmp_i1 * 8) == 1) &&
           (*(int *)(globalScriptData + (tmp_i1 + 0x3faba0 + param_1 * 0x16) * 8) != tmp_pi3[1]))
        goto LAB_0002de80;
LAB_0002dee0:
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
LAB_0002df50:
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
        if ((*(uint *)(&g_unk_01fd5d04 + tmp_i2 * 8 + globalScriptData) & tmp_pi3[2]) == 0)
        goto LAB_0002df94;
        tmp_i2 = tmp_pi3[3];
      }
      else {
LAB_0002dfb0:
        tmp_i2 = tmp_pi3[3];
      }
      if (tmp_i2 != 0) break;
    }
    else {
      if ((*(int *)(animConditionsTable + tmp_i2 * 8) != 1) ||
         (*(int *)(globalScriptData + (tmp_i2 + 0x3faba0 + param_1 * 0x16) * 8) == tmp_pi3[1]))
      goto LAB_0002dfb0;
LAB_0002df94:
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
  goto LAB_0002df50;
}

int BG_PlayAnim(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7
               ,int param_8)

{
  bool tmp_b1;
  
  if (param_5 == 0) {
    param_5 = *(int *)(*(int *)(param_2 + 0x9c + param_3 * 4) + 0x60) + 0x32;
  }
  if (param_4 == 2) {
joined_r0x0002e0a6:
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
LAB_0002e06e:
      if (param_4 == 1) {
        return -1;
      }
      goto joined_r0x0002e0a6;
    }
    if ((param_7 != 0) && ((*(uint *)(param_1 + 0x58) & 0xfffffdff) == param_3)) {
      if ((param_6 != 0) && (*(int *)(*(int *)(param_2 + 0x9c + param_3 * 4) + 0x4c) != 0)) {
        *(int *)(param_1 + 0x54) = param_5;
      }
      goto LAB_0002e06e;
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
    if (param_6 == 0) goto LAB_0002e0dd;
    param_6 = *(int *)(*(int *)(param_2 + 0x9c + param_3 * 4) + 0x4c);
  }
  if (param_6 != 0) {
    *(int *)(param_1 + 0x5c) = param_5;
  }
LAB_0002e0dd:
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
          if (*tmp_pc4 == '\0') goto LAB_0002e22a;
        }
        tmp_pc4 = tmp_pc4 + 1;
        tmp_i3 = (tmp_c1 + 0x20) * tmp_i5;
        tmp_i5 = tmp_i5 + 1;
        local_20 = local_20 + tmp_i3;
        tmp_i3 = (int)*tmp_pc4;
      } while (*tmp_pc4 != '\0');
LAB_0002e22a:
      if (local_20 != -1) goto LAB_0002e239;
    }
    local_20 = 0;
  }
LAB_0002e239:
  tmp_i3 = *(int *)(param_2 + 0x89c);
  tmp_i5 = 0;
  if (0 < tmp_i3) {
    do {
      while (tmp_i2 = *(int *)(param_2 + 0x9c + tmp_i5 * 4), *(int *)(tmp_i2 + 100) != local_20) {
        tmp_i5 = tmp_i5 + 1;
        if (tmp_i3 <= tmp_i5) goto LAB_0002e290;
      }
      tmp_i3 = Q_stricmp(param_3,tmp_i2 + 4);
      if (tmp_i3 == 0) goto LAB_0002e2af;
      tmp_i3 = *(int *)(param_2 + 0x89c);
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 < tmp_i3);
  }
LAB_0002e290:
  tmp_i5 = -1;
  BG_AnimParseError("BG_AnimationIndexForString: unknown index \'%s\' for animation group \'%s\'",
                    param_3,param_2);
LAB_0002e2af:
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
LAB_0002e3d7:
    tmp_s1 = param_3[1];
  }
  else {
    tmp_u5 = (int)param_3[4] + 0x32;
    if ((tmp_u4 & 0xfffffffd) == 1) {
      tmp_u3 = (uint)param_3[2];
      if (tmp_u5 == 0) {
        local_28 = *(int *)(*(int *)(param_2 + 0x9c + tmp_u3 * 4) + 0x60) + 0x32;
        if (tmp_u4 != 2) goto LAB_0002e4f0;
LAB_0002e371:
        if (param_6 == 0) {
LAB_0002e37d:
          if (0x31 < *(int *)(param_1 + 0x5c)) goto LAB_0002e390;
        }
LAB_0002e520:
        tmp_b6 = false;
LAB_0002e522:
        if ((param_5 == 0) || (tmp_u3 != (*(uint *)(param_1 + 0x60) & 0xfffffdff))) {
          *(uint *)(param_1 + 0x60) = ~*(uint *)(param_1 + 0x60) & 0x200 | tmp_u3;
          tmp_i2 = param_4;
joined_r0x0002e555:
          if (tmp_i2 != 0) {
            *(uint *)(param_1 + 0x5c) = local_28;
          }
        }
        else if (param_4 != 0) {
          tmp_i2 = *(int *)(*(int *)(param_2 + 0x9c + tmp_u3 * 4) + 0x4c);
          goto joined_r0x0002e555;
        }
        if (!tmp_b6) goto LAB_0002e390;
      }
      else {
        local_28 = tmp_u5;
        if (tmp_u4 == 2) goto LAB_0002e371;
LAB_0002e4f0:
        tmp_b6 = param_6 != 0;
        if ((!tmp_b6) && (0x31 < *(int *)(param_1 + 0x54))) {
LAB_0002e50b:
          if (tmp_u4 == 1) goto LAB_0002e390;
          if (!tmp_b6) goto LAB_0002e37d;
          goto LAB_0002e520;
        }
        if ((param_5 != 0) && (tmp_u3 == (*(uint *)(param_1 + 0x58) & 0xfffffdff))) {
          if ((param_4 != 0) && (*(int *)(*(int *)(param_2 + 0x9c + tmp_u3 * 4) + 0x4c) != 0)) {
            *(uint *)(param_1 + 0x54) = local_28;
          }
          goto LAB_0002e50b;
        }
        *(uint *)(param_1 + 0x58) = ~*(uint *)(param_1 + 0x58) & 0x200 | tmp_u3;
        if (param_4 != 0) {
          *(uint *)(param_1 + 0x54) = local_28;
        }
        if ((tmp_u4 != 1) && ((tmp_b6 || (*(int *)(param_1 + 0x5c) < 0x32)))) {
          tmp_b6 = true;
          goto LAB_0002e522;
        }
      }
      tmp_u4 = ~local_28 >> 0x1f;
      goto LAB_0002e3d7;
    }
    BG_PlayAnim(param_1,param_2,(int)param_3[2],tmp_u4,tmp_u5,param_4,param_5,param_6);
LAB_0002e390:
    tmp_u4 = 0;
    tmp_s1 = param_3[1];
  }
  tmp_u3 = (uint)tmp_s1;
  if (tmp_u3 != 0) {
    tmp_u5 = (int)param_3[4] + 0x32;
    if ((tmp_u3 & 0xfffffffd) != 1) {
      BG_PlayAnim(param_1,param_2,(int)param_3[3],tmp_u3,tmp_u5,param_4,param_5,param_6);
      tmp_s1 = param_3[6];
      goto joined_r0x0002e476;
    }
    tmp_u4 = (uint)param_3[3];
    if (tmp_u5 == 0) {
      local_28 = *(int *)(*(int *)(param_2 + 0x9c + tmp_u4 * 4) + 0x60) + 0x32;
      if (tmp_u3 != 2) goto LAB_0002e5c0;
LAB_0002e40b:
      if (param_6 == 0) {
LAB_0002e417:
        if (*(int *)(param_1 + 0x5c) < 0x32) goto LAB_0002e5f0;
      }
      else {
LAB_0002e5f0:
        tmp_b6 = false;
LAB_0002e5f2:
        if ((param_5 == 0) || (tmp_u4 != (*(uint *)(param_1 + 0x60) & 0xfffffdff))) {
          *(uint *)(param_1 + 0x60) = ~*(uint *)(param_1 + 0x60) & 0x200 | tmp_u4;
joined_r0x0002e621:
          if (param_4 != 0) {
            *(uint *)(param_1 + 0x5c) = local_28;
          }
        }
        else if (param_4 != 0) {
          param_4 = *(int *)(*(int *)(param_2 + 0x9c + tmp_u4 * 4) + 0x4c);
          goto joined_r0x0002e621;
        }
        if (tmp_b6) goto LAB_0002e62b;
      }
LAB_0002e421:
      tmp_u4 = 0;
    }
    else {
      local_28 = tmp_u5;
      if (tmp_u3 == 2) goto LAB_0002e40b;
LAB_0002e5c0:
      tmp_b6 = param_6 != 0;
      if ((!tmp_b6) && (0x31 < *(int *)(param_1 + 0x54))) {
LAB_0002e5db:
        if (tmp_u3 == 1) goto LAB_0002e421;
        if (!tmp_b6) goto LAB_0002e417;
        goto LAB_0002e5f0;
      }
      if ((param_5 != 0) && (tmp_u4 == (*(uint *)(param_1 + 0x58) & 0xfffffdff))) {
        if ((param_4 != 0) && (*(int *)(*(int *)(param_2 + 0x9c + tmp_u4 * 4) + 0x4c) != 0)) {
          *(uint *)(param_1 + 0x54) = local_28;
        }
        goto LAB_0002e5db;
      }
      *(uint *)(param_1 + 0x58) = ~*(uint *)(param_1 + 0x58) & 0x200 | tmp_u4;
      if (param_4 != 0) {
        *(uint *)(param_1 + 0x54) = local_28;
      }
      if ((tmp_u3 != 1) && ((tmp_b6 || (*(int *)(param_1 + 0x5c) < 0x32)))) {
        tmp_b6 = true;
        goto LAB_0002e5f2;
      }
LAB_0002e62b:
      tmp_u4 = ~local_28 >> 0x1f;
    }
  }
  tmp_s1 = param_3[6];
joined_r0x0002e476:
  if (tmp_s1 != 0) {
    (**(void **)(&g_unk_01fd8904 + globalScriptData))
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
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int *tmp_pi4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int local_34;
  int *local_30;
  
  tmp_i2 = globalScriptData;
  tmp_i6 = *(int *)(param_1 + 0x5a8);
  if (((param_3 != 0x16) && ((*(uint *)(param_1 + 0x68) & 0x800000) != 0)) ||
     (((*(uint *)(param_1 + 0x68) & 1) != 0 &&
      (((param_3 & 0xfffffffb) != 0x11 && (param_3 != 0x16)))))) {
    return 0xffffffff;
  }
  local_30 = (int *)0x0;
joined_r0x0002e865:
  do {
    if ((3 < tmp_i6) || (local_30 != (int *)0x0)) {
      if (local_30 == (int *)0x0) {
        return 0xffffffff;
      }
      tmp_i5 = *(int *)(param_1 + 0xa0) * 0xb0;
      tmp_i6 = tmp_i5 + globalScriptData;
      *(uint32_t *)(&g_unk_01fd5d28 + tmp_i6) = 0;
      *(uint32_t *)(&g_unk_01fd5d2c + tmp_i5 + tmp_i2) = 0;
      COM_BitSet(&g_unk_01fd5d28 + tmp_i6,param_3);
      tmp_i6 = BG_ExecuteCommand(param_1,param_2,
                                (int)local_30 +
                                (*(int *)(param_1 + 0xa0) % local_30[0x59]) * 0xe + 0x168,0,param_4,
                                0);
      return (uint)(tmp_i6 != -1);
    }
    tmp_i3 = tmp_i6 * 0x2e5c + param_3 * 0x204;
    tmp_i5 = *(int *)(param_2 + 0x8a4 + tmp_i3);
    if (tmp_i5 != 0) {
      if (0 < tmp_i5) {
        local_34 = 0;
LAB_0002e8e0:
        local_30 = *(int **)(param_2 + 0x8a8 + tmp_i3 + local_34 * 4);
        tmp_pi4 = local_30 + 1;
        if (0 < *local_30) {
          tmp_i7 = 0;
          do {
            tmp_i1 = *tmp_pi4;
            if (*(int *)(animConditionsTable + tmp_i1 * 8) == 0) {
              tmp_i1 = tmp_i1 + *(int *)(param_1 + 0xa0) * 0x16;
              if ((tmp_pi4[1] & *(uint *)(globalScriptData + (tmp_i1 + 0x3faba0) * 8)) == 0) {
                if ((*(uint *)(&g_unk_01fd5d04 + tmp_i1 * 8 + globalScriptData) & tmp_pi4[2]) == 0)
                goto LAB_0002e924;
                tmp_i1 = tmp_pi4[3];
              }
              else {
LAB_0002e949:
                tmp_i1 = tmp_pi4[3];
              }
              if (tmp_i1 != 0) goto LAB_0002e950;
            }
            else {
              if ((*(int *)(animConditionsTable + tmp_i1 * 8) != 1) ||
                 (*(int *)(globalScriptData +
                          (tmp_i1 + 0x3faba0 + *(int *)(param_1 + 0xa0) * 0x16) * 8) == tmp_pi4[1]))
              goto LAB_0002e949;
LAB_0002e924:
              if (tmp_pi4[3] == 0) goto LAB_0002e950;
            }
            tmp_i7 = tmp_i7 + 1;
            tmp_pi4 = tmp_pi4 + 4;
            if (tmp_i7 == *local_30) break;
          } while( true );
        }
        goto joined_r0x0002e865;
      }
    }
LAB_0002e960:
    tmp_i6 = tmp_i6 + 1;
    local_30 = (int *)0x0;
  } while( true );
LAB_0002e950:
  local_34 = local_34 + 1;
  if (local_34 == tmp_i5) goto LAB_0002e960;
  goto LAB_0002e8e0;
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
    if (*(int *)(&g_unk_01fd5d28 + tmp_i5 * 0xb0 + globalScriptData) != 0) {
      tmp_i7 = *(int *)(&g_unk_01fd5d28 + tmp_i5 * 0xb0 + globalScriptData) * 0x204 + 0xc210 + param_2;
      tmp_i1 = *(int *)(tmp_i7 + 4);
      if ((tmp_i1 != 0) && (0 < tmp_i1)) {
        local_2c = 0;
LAB_0002eb10:
        tmp_pi2 = *(int **)(tmp_i7 + 8 + local_2c * 4);
        tmp_pi4 = tmp_pi2 + 1;
        if (*tmp_pi2 < 1) {
LAB_0002ebc8:
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
              if ((*(uint *)(&g_unk_01fd5d04 + tmp_i3 * 8 + globalScriptData) & tmp_pi4[2]) == 0)
              goto LAB_0002eb54;
              tmp_i3 = tmp_pi4[3];
            }
            else {
LAB_0002eb71:
              tmp_i3 = tmp_pi4[3];
            }
            if (tmp_i3 != 0) goto LAB_0002eb78;
          }
          else {
            if ((*(int *)(animConditionsTable + tmp_i3 * 8) != 1) ||
               (*(int *)(globalScriptData + (tmp_i3 + 0x3faba0 + tmp_i5 * 0x16) * 8) == tmp_pi4[1]))
            goto LAB_0002eb71;
LAB_0002eb54:
            if (tmp_pi4[3] == 0) goto LAB_0002eb78;
          }
          tmp_i8 = tmp_i8 + 1;
          tmp_pi4 = tmp_pi4 + 4;
          if (tmp_i8 == *tmp_pi2) goto LAB_0002ebc8;
        } while( true );
      }
    }
  }
  return 0xffffffff;
LAB_0002eb78:
  local_2c = local_2c + 1;
  if (local_2c == tmp_i1) {
    return 0xffffffff;
  }
  goto LAB_0002eb10;
}

BG_AnimScriptEvent(int param_1,int param_2,int param_3,uint32_t param_4,uint32_t param_5)
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
LAB_0002ecb0:
      tmp_pi1 = (int *)tmp_pi6[local_2c + 1];
      tmp_pi3 = tmp_pi1 + 1;
      if (*tmp_pi1 < 1) {
LAB_0002ed68:
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
            if ((*(uint *)(&g_unk_01fd5d04 + tmp_i2 * 8 + globalScriptData) & tmp_pi3[2]) == 0)
            goto LAB_0002ecf4;
            tmp_i2 = tmp_pi3[3];
          }
          else {
LAB_0002ed11:
            tmp_i2 = tmp_pi3[3];
          }
          if (tmp_i2 != 0) goto LAB_0002ed18;
        }
        else {
          if ((*(int *)(animConditionsTable + tmp_i2 * 8) != 1) ||
             (*(int *)(globalScriptData + (tmp_i2 + 0x3faba0 + *(int *)(param_1 + 0xa0) * 0x16) * 8)
              == tmp_pi3[1])) goto LAB_0002ed11;
LAB_0002ecf4:
          if (tmp_pi3[3] == 0) goto LAB_0002ed18;
        }
        tmp_i7 = tmp_i7 + 1;
        tmp_pi3 = tmp_pi3 + 4;
        if (tmp_i7 == *tmp_pi1) goto LAB_0002ed68;
      } while( true );
    }
  }
  return 0xffffffff;
LAB_0002ed18:
  local_2c = local_2c + 1;
  if (local_2c == tmp_i4) {
    return 0xffffffff;
  }
  goto LAB_0002ecb0;
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
    *(uint32_t *)(&g_unk_01fd5d04 + param_2 * 8 + tmp_i2) = 0;
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
joined_r0x0002f0d5:
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
LAB_0002f140:
      local_20 = *(int **)(param_2 + 0x8a8 + tmp_i2 + local_24 * 4);
      tmp_pi3 = local_20 + 1;
      if (0 < *local_20) {
        tmp_i5 = 0;
        do {
          tmp_i1 = *tmp_pi3;
          if (*(int *)(animConditionsTable + tmp_i1 * 8) == 0) {
            tmp_i1 = tmp_i1 + param_1 * 0x16;
            if ((tmp_pi3[1] & *(uint *)(globalScriptData + (tmp_i1 + 0x3faba0) * 8)) == 0) {
              if ((*(uint *)(&g_unk_01fd5d04 + tmp_i1 * 8 + globalScriptData) & tmp_pi3[2]) == 0)
              goto LAB_0002f184;
              tmp_i1 = tmp_pi3[3];
            }
            else {
LAB_0002f1a4:
              tmp_i1 = tmp_pi3[3];
            }
            if (tmp_i1 != 0) goto LAB_0002f1ab;
          }
          else {
            if ((*(int *)(animConditionsTable + tmp_i1 * 8) != 1) ||
               (*(int *)(globalScriptData + (tmp_i1 + 0x3faba0 + param_1 * 0x16) * 8) == tmp_pi3[1]))
            goto LAB_0002f1a4;
LAB_0002f184:
            if (tmp_pi3[3] == 0) goto LAB_0002f1ab;
          }
          tmp_i5 = tmp_i5 + 1;
          tmp_pi3 = tmp_pi3 + 4;
          if (tmp_i5 == *local_20) break;
        } while( true );
      }
      goto joined_r0x0002f0d5;
    }
LAB_0002f1bb:
    param_3 = param_3 + 1;
    local_20 = (int *)0x0;
  } while( true );
LAB_0002f1ab:
  local_24 = local_24 + 1;
  if (local_24 == tmp_i4) goto LAB_0002f1bb;
  goto LAB_0002f140;
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
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  
  tmp_i4 = globalScriptData;
  tmp_i1 = *param_1;
  if ((*(byte *)(tmp_i1 + 0x6a) & 4) == 0) {
    tmp_u2 = *(uint32_t *)(tmp_i1 + 0xa4);
    tmp_i5 = *(int *)(tmp_i1 + 0xa0) * 0xb0;
    tmp_i3 = tmp_i5 + globalScriptData;
    *(uint32_t *)(&g_unk_01fd5d00 + tmp_i3) = 0;
    *(uint32_t *)(&g_unk_01fd5d04 + tmp_i5 + tmp_i4) = 0;
    COM_BitSet(&g_unk_01fd5d00 + tmp_i3,tmp_u2);
    COM_BitClear(&g_unk_01fd5d98 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + globalScriptData,0);
  }
  else {
    tmp_i5 = *(int *)(tmp_i1 + 0xa0) * 0xb0;
    tmp_i3 = tmp_i5 + globalScriptData;
    *(uint32_t *)(&g_unk_01fd5d00 + tmp_i3) = 0;
    *(uint32_t *)(&g_unk_01fd5d04 + tmp_i5 + tmp_i4) = 0;
    COM_BitSet(&g_unk_01fd5d00 + tmp_i3,0x13);
    COM_BitSet(&g_unk_01fd5d98 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + globalScriptData,0);
  }
  tmp_i4 = globalScriptData;
  *(uint32_t *)(&g_unk_01fd5d80 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + globalScriptData) =
       *(uint32_t *)(tmp_i1 + 0xe4);
  if (*(int *)(tmp_i1 + 0xd0) < 0x42) {
    if (*(int *)(tmp_i1 + 0xd0) < 0x21) {
      *(uint32_t *)(&g_unk_01fd5d88 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + tmp_i4) = 1;
    }
    else {
      *(uint32_t *)(&g_unk_01fd5d88 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + tmp_i4) = 2;
    }
  }
  else {
    *(uint32_t *)(&g_unk_01fd5d88 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + tmp_i4) = 3;
  }
  if ((*(uint *)(tmp_i1 + 0x68) & 0x8020) == 0) {
    *(uint32_t *)(&g_unk_01fd5d20 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + tmp_i4) = 0;
  }
  else {
    *(uint32_t *)(&g_unk_01fd5d20 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + tmp_i4) = 1;
  }
  *(uint *)(&g_unk_01fd5d30 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + tmp_i4) =
       (uint)(0.0 < *(float *)(tmp_i1 + 0xb0));
  if ((float)*(int *)(tmp_i1 + 0xbc) == *(float *)(tmp_i1 + 0x3f8)) {
    tmp_u6 = *(uint *)(tmp_i1 + 0x68) | 0x10;
  }
  else {
    tmp_u6 = *(uint *)(tmp_i1 + 0x68) & 0xffffffef;
  }
  *(uint *)(tmp_i1 + 0x68) = tmp_u6;
  if ((*(byte *)(param_1 + 4) & 1) == 0) {
    *(uint32_t *)(&g_unk_01fd5d58 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + tmp_i4) = 0;
  }
  else {
    *(uint32_t *)(&g_unk_01fd5d58 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + tmp_i4) = 1;
  }
  if ((*(byte *)(tmp_i1 + 0xd) & 8) != 0) {
    if (*(int *)(tmp_i1 + 0x50) == 0x3ff) {
      *(uint32_t *)(&g_unk_01fd5d90 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + tmp_i4) = 1;
      *(uint32_t *)(tmp_i1 + 0x10) = 0x2ee;
    }
    else if (*(int *)(&g_unk_01fd5d90 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + tmp_i4) != 2) {
      *(int *)(&g_unk_01fd5d90 + *(int *)(tmp_i1 + 0xa0) * 0xb0 + tmp_i4) = 2;
      *(uint32_t *)(tmp_i1 + 0x10) = 0x2ee;
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
      if ((tmp_i2 == 0) || (tmp_i2 = Q_stricmp(local_83c,&g_unk_0023ac61), tmp_i2 != 0)) {
        tmp_u3 = BG_RAG_ParseError(tmp_i1,"expected \'{\'");
        return tmp_u3;
      }
LAB_0002f7e0:
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
            if ((tmp_i4 == 0) || (tmp_i4 = Q_stricmp(local_424,&g_unk_0023ac61), tmp_i4 != 0)) {
              tmp_i2 = BG_RAG_ParseError(tmp_i1,"expected \'{\'");
            }
            else {
              while (tmp_i4 = trap_PC_ReadToken(tmp_i1,local_434), tmp_i4 != 0) {
                if (local_424[0] == '}') goto LAB_0002f7e0;
                tmp_i4 = 0;
                tmp_pu7 = &g_unk_002c2284;
                do {
                  if ((tmp_i2 == *(int *)(tmp_pu7 + -4)) &&
                     (tmp_i5 = Q_stricmp(tmp_pu7,local_424), tmp_i5 == 0)) {
                    tmp_pi8 = &animationPool + tmp_i4 * 0x1c;
                    goto LAB_0002f93e;
                  }
                  tmp_pu7 = tmp_pu7 + 0x70;
                  tmp_i4 = tmp_i4 + 1;
                } while (tmp_pu7 != (uint8_t *)0x308284);
                tmp_pi8 = &animationPool;
                tmp_i4 = 0;
                while (*tmp_pi8 != 0) {
                  tmp_i4 = tmp_i4 + 1;
                  tmp_pi8 = tmp_pi8 + 0x1c;
                  if (tmp_i4 == 0xa00) {
                    tmp_i2 = BG_RAG_ParseError(tmp_i1,"out of animation storage space");
                    goto LAB_0002fbb6;
                  }
                }
                tmp_pi8 = &animationPool + tmp_i4 * 0x1c;
                *tmp_pi8 = tmp_i2;
                Q_strncpyz(&g_unk_002c2284 + tmp_i4 * 0x70,local_424,0x40);
LAB_0002f93e:
                __haystack = tmp_pi8 + 1;
                Q_strncpyz(__haystack,local_424,0x40);
                Q_strlwr(__haystack);
                tmp_pi8[0x1a] = 0;
                tmp_i4 = PC_Int_Parse(tmp_i1,tmp_pi8 + 0x11);
                if (tmp_i4 == 0) {
                  tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected first frame integer");
LAB_0002fb93:
                  if (tmp_i4 == 0) {
                    return 0;
                  }
                }
                else {
                  tmp_i4 = PC_Int_Parse(tmp_i1,tmp_pi8 + 0x12);
                  if (tmp_i4 == 0) {
                    tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected length integer");
                    goto LAB_0002fb93;
                  }
                  tmp_i4 = PC_Int_Parse(tmp_i1,tmp_pi8 + 0x13);
                  if (tmp_i4 == 0) {
                    tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected looping integer");
                    goto LAB_0002fb93;
                  }
                  tmp_i4 = PC_Int_Parse(tmp_i1,&local_850);
                  if (tmp_i4 == 0) {
                    tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected fps integer");
                    goto LAB_0002fb93;
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
                    goto LAB_0002fb93;
                  }
                  tmp_i4 = PC_Int_Parse(tmp_i1,tmp_pi8 + 0x17);
                  if (tmp_i4 == 0) {
                    tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected transition integer");
                    goto LAB_0002fb93;
                  }
                  tmp_i4 = PC_Int_Parse(tmp_i1,&local_850);
                  if (tmp_i4 == 0) {
                    tmp_i4 = BG_RAG_ParseError(tmp_i1,"expected reversed integer");
                    goto LAB_0002fb93;
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
LAB_0002fbb6:
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
        if ((tmp_i3 == 0) || (tmp_i3 = Q_stricmp(local_424,&g_unk_0023ac61), tmp_i3 != 0)) {
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
                  tmp_i3 = Q_stricmp(local_424,&g_unk_0023b84a);
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
    *(uint32_t *)((int)&g_unk_008821e4 + tmp_u1) = 0;
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
  if ((g_unk_008821e4 != 0) && (tmp_i1 = Q_stricmp(param_1,0x8879d4), tmp_i1 == 0)) {
    return (uint8_t *)0x8879d4;
  }
  if ((g_unk_008821e8 != 0) && (tmp_i1 = Q_stricmp(param_1,0x8881c8), tmp_i1 == 0)) {
    return (uint8_t *)0x8881c8;
  }
  if ((g_unk_008821ec != 0) && (tmp_i1 = Q_stricmp(param_1,0x8889bc), tmp_i1 == 0)) {
    return (uint8_t *)0x8889bc;
  }
  if ((g_unk_008821f0 != 0) && (tmp_i1 = Q_stricmp(param_1,0x8891b0), tmp_i1 == 0)) {
    return (uint8_t *)0x8891b0;
  }
  if ((g_unk_008821f4 != 0) && (tmp_i1 = Q_stricmp(param_1,0x8899a4), tmp_i1 == 0)) {
    return (uint8_t *)0x8899a4;
  }
  if ((g_unk_008821f8 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88a198), tmp_i1 == 0)) {
    return (uint8_t *)0x88a198;
  }
  if ((g_unk_008821fc != 0) && (tmp_i1 = Q_stricmp(param_1,0x88a98c), tmp_i1 == 0)) {
    return (uint8_t *)0x88a98c;
  }
  if ((g_unk_00882200 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88b180), tmp_i1 == 0)) {
    return (uint8_t *)0x88b180;
  }
  if ((g_unk_00882204 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88b974), tmp_i1 == 0)) {
    return (uint8_t *)0x88b974;
  }
  if ((g_unk_00882208 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88c168), tmp_i1 == 0)) {
    return (uint8_t *)0x88c168;
  }
  if ((g_unk_0088220c != 0) && (tmp_i1 = Q_stricmp(param_1,0x88c95c), tmp_i1 == 0)) {
    return (uint8_t *)0x88c95c;
  }
  if ((g_unk_00882210 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88d150), tmp_i1 == 0)) {
    return (uint8_t *)0x88d150;
  }
  if ((g_unk_00882214 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88d944), tmp_i1 == 0)) {
    return (uint8_t *)0x88d944;
  }
  if ((g_unk_00882218 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88e138), tmp_i1 == 0)) {
    return (uint8_t *)0x88e138;
  }
  if ((g_unk_0088221c != 0) && (tmp_i1 = Q_stricmp(param_1,0x88e92c), tmp_i1 == 0)) {
    return (uint8_t *)0x88e92c;
  }
  if (bg_characterPoolInuse == 0) {
    tmp_i1 = 0;
  }
  else if (g_unk_008821e4 == 0) {
    tmp_i1 = 1;
  }
  else if (g_unk_008821e8 == 0) {
    tmp_i1 = 2;
  }
  else if (g_unk_008821ec == 0) {
    tmp_i1 = 3;
  }
  else if (g_unk_008821f0 == 0) {
    tmp_i1 = 4;
  }
  else if (g_unk_008821f4 == 0) {
    tmp_i1 = 5;
  }
  else if (g_unk_008821f8 == 0) {
    tmp_i1 = 6;
  }
  else if (g_unk_008821fc == 0) {
    tmp_i1 = 7;
  }
  else if (g_unk_00882200 == 0) {
    tmp_i1 = 8;
  }
  else if (g_unk_00882204 == 0) {
    tmp_i1 = 9;
  }
  else if (g_unk_00882208 == 0) {
    tmp_i1 = 10;
  }
  else if (g_unk_0088220c == 0) {
    tmp_i1 = 0xb;
  }
  else if (g_unk_00882210 == 0) {
    tmp_i1 = 0xc;
  }
  else if (g_unk_00882214 == 0) {
    tmp_i1 = 0xd;
  }
  else if (g_unk_00882218 == 0) {
    tmp_i1 = 0xe;
  }
  else {
    if (g_unk_0088221c != 0) {
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
  if ((g_unk_008821e4 != 0) && (tmp_i1 = Q_stricmp(param_1,0x8879d4), tmp_i1 == 0)) {
    return (uint8_t *)0x8879d4;
  }
  if ((g_unk_008821e8 != 0) && (tmp_i1 = Q_stricmp(param_1,0x8881c8), tmp_i1 == 0)) {
    return (uint8_t *)0x8881c8;
  }
  if ((g_unk_008821ec != 0) && (tmp_i1 = Q_stricmp(param_1,0x8889bc), tmp_i1 == 0)) {
    return (uint8_t *)0x8889bc;
  }
  if ((g_unk_008821f0 != 0) && (tmp_i1 = Q_stricmp(param_1,0x8891b0), tmp_i1 == 0)) {
    return (uint8_t *)0x8891b0;
  }
  if ((g_unk_008821f4 != 0) && (tmp_i1 = Q_stricmp(param_1,0x8899a4), tmp_i1 == 0)) {
    return (uint8_t *)0x8899a4;
  }
  if ((g_unk_008821f8 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88a198), tmp_i1 == 0)) {
    return (uint8_t *)0x88a198;
  }
  if ((g_unk_008821fc != 0) && (tmp_i1 = Q_stricmp(param_1,0x88a98c), tmp_i1 == 0)) {
    return (uint8_t *)0x88a98c;
  }
  if ((g_unk_00882200 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88b180), tmp_i1 == 0)) {
    return (uint8_t *)0x88b180;
  }
  if ((g_unk_00882204 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88b974), tmp_i1 == 0)) {
    return (uint8_t *)0x88b974;
  }
  if ((g_unk_00882208 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88c168), tmp_i1 == 0)) {
    return (uint8_t *)0x88c168;
  }
  if ((g_unk_0088220c != 0) && (tmp_i1 = Q_stricmp(param_1,0x88c95c), tmp_i1 == 0)) {
    return (uint8_t *)0x88c95c;
  }
  if ((g_unk_00882210 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88d150), tmp_i1 == 0)) {
    return (uint8_t *)0x88d150;
  }
  if ((g_unk_00882214 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88d944), tmp_i1 == 0)) {
    return (uint8_t *)0x88d944;
  }
  if ((g_unk_00882218 != 0) && (tmp_i1 = Q_stricmp(param_1,0x88e138), tmp_i1 == 0)) {
    return (uint8_t *)0x88e138;
  }
  if ((g_unk_0088221c != 0) && (tmp_i1 = Q_stricmp(param_1,0x88e92c), tmp_i1 == 0)) {
    return (uint8_t *)0x88e92c;
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
    tmp_pc2 = (char *)(param_1 * 0x6b0 + 0x898ef4);
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
    tmp_u1 = *(uint32_t *)(CSWTCH_82 + (param_1 - 0x22U) * 4);
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
  if (GHIDRA_FIELD(g_war, 12, 4) == 0) {
    tmp_i7 = 5;
    if (param_1 - 1U < 4) {
      tmp_i7 = *(int *)(CSWTCH_87 + (param_1 - 1U) * 4);
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
    goto LAB_00031b4a;
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
    goto LAB_00031b4a;
  default:
    Com_Error(2,"BG_EvaluateTrajectory: unknown trType: %i",*(uint32_t *)(param_2 + 0x10));
    break;
  case 5:
    tmp_d8 = ((double)(param_3 - *(int *)(param_2 + 0x10)) / (double)*(int *)(param_2 + 0x14)) *
            3.141592653589793;
    tmp_d8 = sin(tmp_d8 + tmp_d8);
    tmp_f1 = (float)tmp_d8;
LAB_00031b4a:
    local_40 = *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x28) * tmp_f1 + *(float *)(param_2 + 0x1c);
    local_38 = tmp_f1 * *(float *)(param_2 + 0x2c) + *(float *)(param_2 + 0x20);
    break;
  case 6:
    tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) * 0.001;
    local_40 = *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x28) * tmp_f1 + *(float *)(param_2 + 0x1c);
    tmp_f9 = *(float *)(param_2 + 0x20) + tmp_f1 * *(float *)(param_2 + 0x2c);
    tmp_f2 = (float)(int)GHIDRA_FIELD(g_gravity, 12, 4);
    goto LAB_00031c31;
  case 7:
    tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) * 0.001;
    local_40 = *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x28) * tmp_f1 + *(float *)(param_2 + 0x1c);
    tmp_f9 = *(float *)(param_2 + 0x20) + tmp_f1 * *(float *)(param_2 + 0x2c);
    tmp_f2 = (float)(int)GHIDRA_FIELD(g_gravity, 12, 4) * 0.3;
LAB_00031c31:
    local_38 = tmp_f9 - tmp_f2 * 0.5 * tmp_f1 * tmp_f1;
    break;
  case 8:
    tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) * 0.001;
    local_40 = *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x28) * tmp_f1 + *(float *)(param_2 + 0x1c);
    local_38 = (*(float *)(param_2 + 0x2c) * tmp_f1 + *(float *)(param_2 + 0x20)) -
               (float)(int)GHIDRA_FIELD(g_gravity, 12, 4) * 0.2 * 0.5 * tmp_f1;
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
LAB_0003199f:
      if (tmp_b6) {
        tmp_f1 = 1.0 - tmp_f1;
      }
      tmp_f1 = tmp_f1 * 16.0;
      tmp_f9 = floorf(tmp_f1);
      tmp_i3 = (int)ROUND(tmp_f9);
LAB_000319e1:
      if (0xf < tmp_i3) goto LAB_000319ec;
      tmp_f1 = tmp_f1 - (float)tmp_i3;
LAB_00031fda:
      tmp_f1 = tmp_f1 * *(float *)(splinePaths + tmp_i3 * 0x1c + tmp_i4 * 0x394 + 0x1e0);
    }
    else {
      tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) / (float)*(int *)(param_2 + 0x14);
      if (tmp_f1 < 0.0) {
        if (tmp_b6) {
          tmp_i3 = 0x10;
          tmp_f1 = 16.0;
          goto LAB_000319e1;
        }
        tmp_f1 = 0.0;
        tmp_i3 = 0;
        goto LAB_00031fda;
      }
      if (tmp_f1 <= 1.0) goto LAB_0003199f;
      if (tmp_b6) {
        tmp_i3 = 0;
        tmp_f1 = 0.0;
        goto LAB_000319e1;
      }
LAB_000319ec:
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
LAB_000320e0:
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
          goto LAB_000320e0;
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

BG_RaySphereIntersection(float param_1,float *param_2,float *param_3,float *param_4,float *param_5)
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
LAB_000323bc:
      if (param_1 < 0.0) goto LAB_00032540;
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
          goto LAB_000323ee;
        }
        goto LAB_0003254c;
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
LAB_00032390:
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
        goto LAB_000323bc;
      }
      if (0.0 <= param_1) {
        tmp_b7 = 0.0 <= tmp_f5;
        if (1.0 < tmp_f5 || (tmp_f5 <= tmp_f4 || !tmp_b7)) {
          if (tmp_f4 < tmp_f11) goto LAB_00032354;
          goto LAB_000323bc;
        }
        tmp_b10 = true;
        goto LAB_00032390;
      }
      tmp_b7 = 0.0 <= tmp_f5;
      if (tmp_f5 <= 1.0 && (tmp_f5 < tmp_f4 && tmp_b7)) {
        tmp_b10 = true;
        goto LAB_00032390;
      }
      if (tmp_f11 < tmp_f4) {
LAB_00032354:
        tmp_b10 = tmp_f11 <= 1.0;
        tmp_b7 = 0.0 <= tmp_f11;
        tmp_f5 = tmp_f11;
        goto LAB_00032390;
      }
LAB_00032540:
      tmp_i8 = tmp_i8 + -1;
      if (tmp_i8 < 0) {
        tmp_i8 = 0xf;
LAB_0003254c:
        tmp_i9 = *(int *)(tmp_i9 + 0x90);
        if (tmp_i9 == 0) {
          return;
        }
        *param_2 = tmp_i9;
      }
    }
LAB_000323ee:
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
  double tmp_d10;
  float tmp_f11;
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
    goto LAB_00032a9a;
  case 3:
    tmp_i7 = param_1[2] + param_1[1];
    if (param_2 <= tmp_i7) {
      tmp_i7 = param_2;
    }
    tmp_f11 = (float)(tmp_i7 - param_1[1]) * 0.001;
    tmp_f1 = 0.0;
    if (0.0 <= tmp_f11) {
      tmp_f1 = tmp_f11;
    }
    goto LAB_00032a9a;
  default:
    Com_Error(2,"BG_EvaluateTrajectory: unknown trType: %i",param_1[1]);
    break;
  case 5:
    tmp_d10 = ((double)(param_2 - param_1[1]) / (double)(int)param_1[2]) * 3.141592653589793;
    tmp_d10 = sin(tmp_d10 + tmp_d10);
    tmp_f1 = (float)tmp_d10;
LAB_00032a9a:
    *param_3 = (float)param_1[6] * tmp_f1 + (float)param_1[3];
    param_3[1] = (float)param_1[7] * tmp_f1 + (float)param_1[4];
    param_3[2] = tmp_f1 * (float)param_1[8] + (float)param_1[5];
    break;
  case 6:
    tmp_f1 = (float)(param_2 - param_1[1]) * 0.001;
    *param_3 = (float)param_1[6] * tmp_f1 + (float)param_1[3];
    param_3[1] = (float)param_1[7] * tmp_f1 + (float)param_1[4];
    tmp_f11 = (float)param_1[8] * tmp_f1 + (float)param_1[5];
    param_3[2] = tmp_f11;
    tmp_f2 = (float)(int)GHIDRA_FIELD(g_gravity, 12, 4);
    goto LAB_00032b7b;
  case 7:
    tmp_f1 = (float)(param_2 - param_1[1]) * 0.001;
    *param_3 = (float)param_1[6] * tmp_f1 + (float)param_1[3];
    param_3[1] = (float)param_1[7] * tmp_f1 + (float)param_1[4];
    tmp_f11 = (float)param_1[8] * tmp_f1 + (float)param_1[5];
    param_3[2] = tmp_f11;
    tmp_f2 = (float)(int)GHIDRA_FIELD(g_gravity, 12, 4) * 0.3;
LAB_00032b7b:
    param_3[2] = tmp_f11 - tmp_f2 * 0.5 * tmp_f1 * tmp_f1;
    break;
  case 8:
    tmp_f1 = (float)(param_2 - param_1[1]) * 0.001;
    *param_3 = (float)param_1[6] * tmp_f1 + (float)param_1[3];
    param_3[1] = (float)param_1[7] * tmp_f1 + (float)param_1[4];
    tmp_f11 = (float)param_1[8] * tmp_f1 + (float)param_1[5];
    param_3[2] = tmp_f11;
    param_3[2] = tmp_f11 - (float)(int)GHIDRA_FIELD(g_gravity, 12, 4) * 0.2 * 0.5 * tmp_f1;
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
    tmp_f11 = (float)param_1[4];
    tmp_f2 = (float)param_1[8];
    tmp_f3 = (float)param_1[5];
    tmp_f4 = -(float)(tmp_l9 / ((long double)tmp_i7 * (long double)0.001)) * 0.5 * local_3c * local_3c;
    *param_3 = tmp_f4 * *param_3 + local_3c * (float)param_1[6] + (float)param_1[3];
    param_3[1] = tmp_f4 * param_3[1] + tmp_f1 * local_3c + tmp_f11;
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
LAB_00032ec0:
      *param_3 = local_28 - local_34;
      param_3[1] = local_24 - local_30;
      param_3[2] = local_20 - local_2c;
    }
    else {
      tmp_f11 = *(float *)(local_38 + 0x388);
      tmp_f1 = (float)param_1[3] / tmp_f11 + tmp_f1;
      tmp_pu6 = local_38;
      if (1.0 < tmp_f1) {
        tmp_pu6 = *(uint8_t **)(local_38 + 0x8c);
        tmp_f1 = tmp_f11 * (tmp_f1 - 1.0);
        if (tmp_pu6 != (uint8_t *)0x0) {
          tmp_f11 = *(float *)(tmp_pu6 + 0x388);
          while (tmp_f11 != 0.0) {
            tmp_f1 = tmp_f1 / tmp_f11;
            if (tmp_f1 <= 1.0) goto LAB_00033260;
            tmp_pu6 = *(uint8_t **)(tmp_pu6 + 0x8c);
            tmp_f1 = (tmp_f1 - 1.0) * tmp_f11;
            if (tmp_pu6 == (uint8_t *)0x0) break;
            tmp_f11 = *(float *)(tmp_pu6 + 0x388);
          }
        }
        goto LAB_00032ec0;
      }
LAB_00033260:
      if (tmp_f1 < 0.0) {
        tmp_f1 = tmp_f1 * tmp_f11;
        tmp_pu6 = *(uint8_t **)(tmp_pu6 + 0x90);
        if (tmp_pu6 != (uint8_t *)0x0) {
          tmp_f11 = *(float *)(tmp_pu6 + 0x388);
          while (tmp_f11 != 0.0) {
            tmp_f1 = 1.0 - -tmp_f1 / tmp_f11;
            if (0.0 <= tmp_f1) goto LAB_000332ea;
            tmp_f1 = tmp_f1 * tmp_f11;
            tmp_pu6 = *(uint8_t **)(tmp_pu6 + 0x90);
            if (tmp_pu6 == (uint8_t *)0x0) break;
            tmp_f11 = *(float *)(tmp_pu6 + 0x388);
          }
        }
        goto LAB_00032ec0;
      }
LAB_000332ea:
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
        tmp_d10 = sin((double)(((local_3c + local_3c) - 1.0) * 3.1415927 * 0.5));
        param_3[2] = tmp_f1 + ((float)tmp_d10 + 1.0) * 0.5 * (float)param_1[5];
        return;
      }
      if (!tmp_b8) {
        tmp_d10 = sin((double)((1.0 - local_3c) * 3.1415927 * 0.5));
        param_3[2] = tmp_f1 + (1.0 - (float)tmp_d10) * (float)param_1[5];
        return;
      }
    }
    else if (!tmp_b8) {
      param_3[2] = (float)param_1[5] * local_3c + tmp_f1;
      return;
    }
    tmp_d10 = sin((double)local_3c * 3.141592653589793 * 0.5);
    param_3[2] = tmp_f1 + (float)tmp_d10 * (float)param_1[5];
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
        tmp_f11 = floorf(tmp_f1);
        tmp_i7 = (int)ROUND(tmp_f11);
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
        tmp_f11 = floorf(tmp_f1);
        local_54 = (int)ROUND(tmp_f11);
        if (local_54 < 0x10) {
          tmp_f1 = (tmp_f1 - (float)local_54) *
                  *(float *)(splinePaths + local_54 * 0x1c + param_5 * 0x394 + 0x1e0);
        }
        else {
          tmp_f1 = *(float *)(splinePaths + param_5 * 0x394 + 900);
          local_54 = 0xf;
        }
        if ((float)param_1[3] == 0.0) {
          vectoangles(local_54 * 0x1c + param_5 * 0x394 + 0x8b3714,param_3);
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
LAB_00033646:
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
    param_3[2] = tmp_f1 - (float)(int)GHIDRA_FIELD(g_gravity, 12, 4) * (float)(param_2 - tmp_i2) * 0.001;
    return;
  case 7:
    tmp_i2 = param_1[1];
    *param_3 = (float)param_1[6];
    param_3[1] = (float)param_1[7];
    tmp_f1 = (float)param_1[8];
    param_3[2] = tmp_f1;
    param_3[2] = tmp_f1 - (float)(int)GHIDRA_FIELD(g_gravity, 12, 4) * 0.3 * (float)(param_2 - tmp_i2) * 0.001;
    return;
  case 8:
    tmp_i2 = param_1[1];
    *param_3 = (float)param_1[6];
    param_3[1] = (float)param_1[7];
    tmp_f1 = (float)param_1[8];
    param_3[2] = tmp_f1;
    param_3[2] = tmp_f1 - (float)(int)GHIDRA_FIELD(g_gravity, 12, 4) * 0.2 * (float)(param_2 - tmp_i2) * 0.001;
    return;
  case 10:
    if (param_2 <= (int)(param_1[2] + param_1[1])) {
      tmp_f1 = (float)(param_2 - param_1[1]) * 0.001;
      tmp_f1 = tmp_f1 * tmp_f1;
      goto LAB_00033646;
    }
    break;
  case 0xb:
    if (param_2 <= (int)(param_1[2] + param_1[1])) {
      tmp_f1 = (float)(param_2 - param_1[1]) * 0.001;
      goto LAB_00033646;
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
      if (local_44 <= local_2c * local_20 + local_30 * local_24 + local_34 * local_28) {
        if (tmp_i1 != 10) goto LAB_00033882;
        break;
      }
    } while (tmp_i1 != 10);
    if (GHIDRA_FIELD(g_developer, 12, 4) != 0) {
      Com_Printf("BG_GetMarkDir loops: %i\n",10);
    }
  }
LAB_00033882:
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
      goto LAB_00033cc4;
    }
    if (*(int *)(param_1 + 0x140) == 2) {
      tmp_u6 = tmp_u6 & 0xffffffdf;
      *(uint *)(param_1 + 0x68) = tmp_u6;
      *(uint32_t *)(param_1 + 0x16c) = 0;
      goto LAB_00033cc4;
    }
  }
  tmp_u6 = tmp_u6 & 0xffffffdf;
  *(uint *)(param_1 + 0x68) = tmp_u6;
LAB_00033cc4:
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
LAB_00034068:
            tmp_pi2 = (int *)(bg_itemlist + 0x38);
            tmp_i1 = GHIDRA_FIELD(bg_itemlist, 56, 4);
            while (tmp_i1 != 0) {
              while (tmp_pi2[9] == 1) {
                if (param_1 == tmp_pi2[10]) {
                  return tmp_pi2;
                }
                tmp_pi2 = tmp_pi2 + 0xe;
                if (*tmp_pi2 == 0) goto LAB_0003409d;
              }
              tmp_pi2 = tmp_pi2 + 0xe;
              tmp_i1 = *tmp_pi2;
            }
LAB_0003409d:
            Com_Printf("^1ERROR : ^7BG_FindItemForWeapon() ^9no item for weapon %i (%s^9)\n",param_1
                       ,param_1 * 0x6b0 + 0x898ef4);
            return (int *)0x0;
          }
        }
        else if (1 < param_1 - 0x27) goto LAB_00034068;
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
    *(uint32_t *)(tmp_i3 + 0x8b3544 + tmp_u1) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x390);
  *(uint32_t *)(tmp_pu4 + tmp_u1) = 0;
  tmp_i3 = tmp_i2 * 0x394;
  *(uint32_t *)(splinePaths + tmp_i3 + 0x40) = *param_3;
  *(uint32_t *)(splinePaths + tmp_i3 + 0x44) = param_3[1];
  *(uint32_t *)(splinePaths + tmp_i3 + 0x48) = param_3[2];
  Q_strncpyz(tmp_pu4,param_1,0x40);
  if (param_2 == (uint8_t *)0x0) {
    param_2 = &g_unk_0026ea14;
  }
  tmp_i2 = tmp_i2 * 0x394;
  Q_strncpyz(tmp_i2 + 0x8b358c,param_2,0x40);
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
LAB_00034707:
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
              goto LAB_00034762;
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
                  goto LAB_000346e2;
                }
                tmp_i5 = tmp_i5 + 1;
                tmp_pu3 = tmp_pu3 + 0x4c;
              } while (tmp_i5 < numPathCorners);
            }
            Com_Printf("^1Cant find control point (%s) for spline (%s)\n",tmp_pc4,tmp_pc1);
LAB_000346e2:
            local_34 = local_34 + 1;
            tmp_pc4 = tmp_pc4 + 0x4c;
          } while (local_34 < *(int *)(local_30 + 0x178));
          if (0 < numSplinePaths) goto LAB_00034707;
        }
        Com_Printf("^1Cant find target point (%s) for spline (%s)\n",local_30,tmp_pc1);
        tmp_i5 = numSplinePaths;
      }
LAB_00034762:
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
    goto _L865;
  case 3:
  case 8:
    tmp_b1 = *(byte *)(param_2 + 8);
    goto LAB_000348a4;
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
    goto joined_r0x00034964;
  case 0x18:
  case 0x1e:
  case 0x1f:
  case 0x27:
  case 0x28:
  case 0x29:
    tmp_b1 = *(byte *)(param_2 + 0x18);
LAB_000348a4:
    if ((tmp_b1 & 2) != 0) {
      tmp_u2 = 1;
    }
_L865:
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
joined_r0x00034964:
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
  if (GHIDRA_FIELD(g_war, 12, 4) == 0) {
    tmp_u6 = *(int *)(param_1 + 0xe4) - 1;
    tmp_i13 = 5;
    if (tmp_u6 < 4) {
      tmp_i13 = *(int *)(CSWTCH_87 + tmp_u6 * 4);
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
      goto LAB_00034bac;
    }
LAB_00034bfc:
    tmp_i13 = 0;
LAB_00034bfe:
    tmp_i7 = 1;
    if ((*(byte *)(param_2 + 0x10) & 0x20) != 0) {
      tmp_i7 = GHIDRA_FIELD(ammoTableMP, 72, 4);
    }
    if (tmp_i10 < tmp_i7) {
      if (param_4 == 0) goto LAB_00034bb8;
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
            goto LAB_00034d1c;
          }
          tmp_pi9 = tmp_pi9 + 0xe;
        } while (*tmp_pi9 != 0);
      }
      tmp_i10 = 0;
LAB_00034d1c:
      tmp_i10 = param_1 + tmp_i10 * 4;
      if (*(int *)(tmp_i10 + 0x290) < tmp_i7) {
        if (param_4 == 0) goto LAB_00034bb8;
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
    if ((tmp_i7 != 0) && ((GHIDRA_FIELD(g_adrenaline, 12, 4) & 2) == 0)) {
      tmp_i7 = 1;
      if (((GHIDRA_FIELD(g_adrenaline, 12, 4) & 4) == 0) &&
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
        if (param_4 == 0) goto LAB_00034bb8;
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
            goto LAB_00035170;
          }
          tmp_pi9 = tmp_pi9 + 0xe;
        } while (*tmp_pi9 != 0);
      }
      tmp_i7 = 0;
LAB_00035170:
      tmp_i7 = param_1 + tmp_i7 * 4;
      if (*(int *)(tmp_i7 + 0x290) < (int)GHIDRA_FIELD(ammoTableMP, 3384, 4)) {
        if (param_4 == 0) goto LAB_00034bb8;
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
      tmp_pi9 = &g_unk_002b53e4;
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
                  goto LAB_00034f9f;
                }
                tmp_pi12 = tmp_pi12 + 0xe;
              } while (*tmp_pi12 != 0);
            }
            tmp_i7 = 0;
LAB_00034f9f:
            tmp_i7 = param_1 + tmp_i7 * 4;
            if (*(int *)(tmp_i7 + 0x290) < tmp_i10) {
              if (param_4 == 0) goto LAB_00034bb8;
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
                  goto LAB_00035007;
                }
                tmp_pi12 = tmp_pi12 + 0xe;
              } while (*tmp_pi12 != 0);
            }
            tmp_i7 = 0;
LAB_00035007:
            tmp_i7 = param_1 + tmp_i7 * 4;
            if (*(int *)(tmp_i7 + 0x290) < tmp_i10) {
              if (param_4 == 0) goto LAB_00034bb8;
              tmp_i8 = *(int *)(tmp_i7 + 0x290) + param_4;
              if (tmp_i8 < tmp_i10) {
                *(int *)(tmp_i7 + 0x290) = tmp_i8;
                goto LAB_00034f2d;
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
                goto LAB_00034ed3;
              }
              tmp_pi12 = tmp_pi12 + 0xe;
              tmp_i8 = *tmp_pi12;
            }
            tmp_i8 = 0;
LAB_00034ed3:
            tmp_i8 = param_1 + tmp_i8 * 4;
            if (*(int *)(tmp_i8 + 400) < tmp_i10) {
              if (param_4 == 0) goto LAB_00034bb8;
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
LAB_00034f2d:
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
        goto LAB_00034b9a;
      }
      tmp_pi12 = tmp_pi12 + 0xe;
    } while (*tmp_pi12 != 0);
    tmp_i8 = 0;
LAB_00034b9a:
    tmp_i10 = *(int *)(param_1 + (tmp_i8 + 0xa4) * 4);
    if (tmp_i13 <= tmp_i10) {
LAB_00034be3:
      do {
        while (tmp_pi9[9] == 1) {
          if (tmp_pi9[10] == 1) {
            tmp_i13 = tmp_pi9[0xd];
            tmp_i10 = *(int *)(param_1 + (tmp_i13 + 0xa4) * 4);
            goto LAB_00034bfe;
          }
          tmp_pi9 = tmp_pi9 + 0xe;
          if (*tmp_pi9 == 0) goto LAB_00034bf2;
        }
        tmp_pi9 = tmp_pi9 + 0xe;
      } while (*tmp_pi9 != 0);
LAB_00034bf2:
      tmp_i10 = *(int *)(param_1 + 0x290);
      goto LAB_00034bfc;
    }
LAB_00034bac:
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
        goto LAB_00034be3;
      }
      tmp_b5 = true;
      tmp_i13 = 0;
      tmp_b14 = true;
      tmp_i10 = *(int *)(param_1 + 0x290);
      goto LAB_00034bfe;
    }
LAB_00034bb8:
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
    goto LAB_0003557d;
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
                goto LAB_000354fb;
              }
              tmp_pi4 = tmp_pi4 + 0xe;
            } while (*tmp_pi4 != 0);
          }
          tmp_i3 = 0;
LAB_000354fb:
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
LAB_0003557d:
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
        if (tmp_i1 != 0xc) goto LAB_00035461;
        tmp_i3 = *(int *)(param_2 + 0x180);
      }
      if (tmp_i3 != 0) {
        return 0;
      }
    }
LAB_00035461:
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
  
  vsnprintf(string_7431,0x1000,param_2,&stack0x0000000c);
  local_90 = 0;
  local_8c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_8c,&local_90);
  Com_Printf("^3WARNING: %s, line %d: %s\n",local_8c,local_90,string_7431);
  return;
}

void PC_SourceError(uint32_t param_1,char *param_2)
{
  uint32_t local_90;
  uint8_t local_8c [128];
  
  vsnprintf(string_7439,0x1000,param_2,&stack0x0000000c);
  local_90 = 0;
  local_8c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_8c,&local_90);
  Com_Error(2,"^1ERROR: %s, line %d: %s\n",local_8c,local_90,string_7439);
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

uint8_t * PC_String_Parse(uint32_t param_1)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  uint8_t local_424 [16];
  uint8_t local_414 [1036];
  
  tmp_i1 = trap_PC_ReadToken(param_1,local_424);
  if (tmp_i1 == 0) {
    tmp_pu2 = (uint8_t *)0x0;
  }
  else {
    tmp_pu2 = buf_7473;
    Q_strncpyz(buf_7473,local_414,0x400);
  }
  return tmp_pu2;
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
joined_r0x00035c22:
  do {
    if (tmp_c1 == '\0') {
LAB_00035c50:
      tmp_i2 = (int)tmp_pc3 - (int)param_2;
LAB_00035c54:
      *tmp_pc3 = '\0';
      return tmp_i2;
    }
    tmp_i2 = (int)tmp_pc3 - (int)param_2;
    if (param_3 + -1 <= tmp_i2) goto LAB_00035c54;
    if (tmp_c1 != '^') {
      if (tmp_c1 < ' ') {
        if ((tmp_c1 == '\n') && (param_4 != 0)) {
LAB_00035c65:
          *tmp_pc3 = tmp_c1;
          param_1 = param_1 + 1;
          tmp_pc3 = tmp_pc3 + 1;
          tmp_c1 = *param_1;
          goto joined_r0x00035c22;
        }
      }
      else if (tmp_c1 != '\x7f') goto LAB_00035c65;
      tmp_c1 = param_1[1];
      param_1 = param_1 + 1;
      goto joined_r0x00035c22;
    }
    if (param_1[1] == '\0') goto LAB_00035c50;
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
        *param_2 = *(float *)(&g_ptr_colorWhite_002b78c4)[tmp_i8 * 2];
        param_2[1] = *(float *)((&g_ptr_colorWhite_002b78c4)[tmp_i8 * 2] + 4);
        param_2[2] = *(float *)((&g_ptr_colorWhite_002b78c4)[tmp_i8 * 2] + 8);
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
  
  g_unk_0030baa8 = 1200.0;
  tmp_f2 = *param_2 - *param_1;
  tmp_f1 = tmp_f2 / 1200.0;
  while (tmp_f1 < 7.0) {
    g_unk_0030baa8 = g_unk_0030baa8 - 50.0;
    tmp_f1 = tmp_f2 / g_unk_0030baa8;
  }
  tmp_f2 = param_1[1] - param_2[1];
  g_unk_0030baac = 1200.0;
  tmp_f3 = tmp_f2 / 1200.0;
  while (tmp_f3 < 7.0) {
    g_unk_0030baac = g_unk_0030baac - 50.0;
    tmp_f3 = tmp_f2 / g_unk_0030baac;
  }
  locInfo = (tmp_f1 - (float)(int)ROUND(tmp_f1)) * g_unk_0030baa8 * 0.5 + *param_1;
  g_unk_0030baa4 = param_1[1] - (tmp_f3 - (float)(int)ROUND(tmp_f3)) * g_unk_0030baac * 0.5;
  return;
}

uint8_t * BG_GetLocationString(float *param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  coord_7553 = 0;
  tmp_i1 = (int)ROUND((*param_1 - locInfo) / g_unk_0030baa8);
  tmp_i2 = (int)ROUND((g_unk_0030baa4 - param_1[1]) / g_unk_0030baac);
  if (tmp_i2 < 0) {
    tmp_i2 = 0;
  }
  if (tmp_i1 < 0) {
    tmp_i1 = 0;
  }
  Com_sprintf(&coord_7553,6,"%c,%i",tmp_i1 + 0x41,tmp_i2);
  return &coord_7553;
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
    local_18 = *(int *)(CSWTCH_87 + tmp_u5 * 4);
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
    if ((chargeCost_Panzer != g_unk_002b4f98) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_002b4f98;
    }
    if ((g_unk_002b4f9c != g_unk_002b4f98) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_002b4f9c;
    }
    if ((g_unk_002b4fa0 != g_unk_002b4f9c) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_002b4fa0;
    }
    if ((g_unk_002b4fa4 != g_unk_002b4fa0) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_002b4fa4;
    }
    tmp_b6 = g_unk_002b4fa8 == g_unk_002b4fa4;
    tmp_f3 = g_unk_002b4fa8;
    if (!NAN(g_unk_002b4fa8) && !NAN(g_unk_002b4fa4)) {
LAB_000364b0:
      if (tmp_b6) goto LAB_000364c2;
    }
    break;
  default:
    return true;
  case 0xc:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Ammo;
    if ((chargeCost_Ammo != g_unk_002b4fe0) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_002b4fe0;
    }
    if ((g_unk_002b4fe4 != g_unk_002b4fe0) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_002b4fe4;
    }
    if ((g_unk_002b4fe8 != g_unk_002b4fe4) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_002b4fe8;
    }
    if ((g_unk_002b4fec != g_unk_002b4fe8) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_002b4fec;
    }
    tmp_b6 = g_unk_002b4ff0 == g_unk_002b4fec;
    tmp_f3 = g_unk_002b4ff0;
    if (!NAN(g_unk_002b4ff0) && !NAN(g_unk_002b4fec)) goto LAB_000364b0;
    break;
  case 0xf:
  case 0x30:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Dynamite;
    if ((chargeCost_Dynamite != g_unk_002b5058) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_002b5058;
    }
    if ((g_unk_002b505c != g_unk_002b5058) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_002b505c;
    }
    if ((g_unk_002b5060 != g_unk_002b505c) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_002b5060;
    }
    if ((g_unk_002b5064 != g_unk_002b5060) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_002b5064;
    }
    tmp_b6 = g_unk_002b5068 == g_unk_002b5064;
    tmp_f3 = g_unk_002b5068;
    if (!NAN(g_unk_002b5068) && !NAN(g_unk_002b5064)) goto LAB_000364b0;
    break;
  case 0x12:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Health;
    if ((chargeCost_Health != g_unk_002b4ff8) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_002b4ff8;
    }
    if ((g_unk_002b4ffc != g_unk_002b4ff8) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_002b4ffc;
    }
    if ((g_unk_002b5000 != g_unk_002b4ffc) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_002b5000;
    }
    if ((g_unk_002b5004 != g_unk_002b5000) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_002b5004;
    }
    tmp_b6 = g_unk_002b5008 == g_unk_002b5004;
    tmp_f3 = g_unk_002b5008;
    if (!NAN(g_unk_002b5008) && !NAN(g_unk_002b5004)) goto LAB_000364b0;
    break;
  case 0x15:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Artillery;
    if ((chargeCost_Artillery != g_unk_002b4fb0) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_002b4fb0;
    }
    if ((g_unk_002b4fb4 != g_unk_002b4fb0) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_002b4fb4;
    }
    if ((g_unk_002b4fb8 != g_unk_002b4fb4) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_002b4fb8;
    }
    if ((g_unk_002b4fbc != g_unk_002b4fb8) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_002b4fbc;
    }
    tmp_b6 = g_unk_002b4fc0 == g_unk_002b4fbc;
    tmp_f3 = g_unk_002b4fc0;
    if (!NAN(g_unk_002b4fc0) && !NAN(g_unk_002b4fbc)) goto LAB_000364b0;
    break;
  case 0x19:
  case 0x33:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Landmine;
    if ((chargeCost_Landmine != g_unk_002b5070) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_002b5070;
    }
    if ((g_unk_002b5074 != g_unk_002b5070) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_002b5074;
    }
    if ((g_unk_002b5078 != g_unk_002b5074) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_002b5078;
    }
    if ((g_unk_002b507c != g_unk_002b5078) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_002b507c;
    }
    tmp_b6 = g_unk_002b5080 == g_unk_002b507c;
    tmp_f3 = g_unk_002b5080;
    if (!NAN(g_unk_002b5080) && !NAN(g_unk_002b507c)) goto LAB_000364b0;
    break;
  case 0x1a:
  case 0x1c:
  case 0x32:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Satchel;
    if ((chargeCost_Satchel != g_unk_002b5028) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_002b5028;
    }
    if ((g_unk_002b502c != g_unk_002b5028) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_002b502c;
    }
    if ((g_unk_002b5030 != g_unk_002b502c) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_002b5030;
    }
    if ((g_unk_002b5034 != g_unk_002b5030) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_002b5034;
    }
    tmp_b6 = g_unk_002b5038 == g_unk_002b5034;
    tmp_f3 = g_unk_002b5038;
    if (!NAN(g_unk_002b5038) && !NAN(g_unk_002b5034)) goto LAB_000364b0;
    break;
  case 0x24:
  case 0x25:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Riflenade;
    if ((chargeCost_Riflenade != g_unk_002b5040) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_002b5040;
    }
    if ((g_unk_002b5044 != g_unk_002b5040) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_002b5044;
    }
    if ((g_unk_002b5048 != g_unk_002b5044) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_002b5048;
    }
    if ((g_unk_002b504c != g_unk_002b5048) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_002b504c;
    }
    tmp_b6 = g_unk_002b5050 == g_unk_002b504c;
    tmp_f3 = g_unk_002b5050;
    if (!NAN(g_unk_002b5050) && !NAN(g_unk_002b504c)) goto LAB_000364b0;
    break;
  case 0x2a:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Mortar;
    if ((chargeCost_Mortar != g_unk_002b4f80) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_002b4f80;
    }
    if ((g_unk_002b4f84 != g_unk_002b4f80) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_002b4f84;
    }
    if ((g_unk_002b4f88 != g_unk_002b4f84) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_002b4f88;
    }
    if ((g_unk_002b4f8c != g_unk_002b4f88) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_002b4f8c;
    }
    tmp_b6 = g_unk_002b4f90 == g_unk_002b4f8c;
    tmp_f3 = g_unk_002b4f90;
    if (!NAN(g_unk_002b4f90) && !NAN(g_unk_002b4f8c)) goto LAB_000364b0;
    break;
  case 0x2b:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Adrenaline;
    if ((chargeCost_Adrenaline != g_unk_002b4fc8) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_002b4fc8;
    }
    if ((g_unk_002b4fcc != g_unk_002b4fc8) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_002b4fcc;
    }
    if ((g_unk_002b4fd0 != g_unk_002b4fcc) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_002b4fd0;
    }
    if ((g_unk_002b4fd4 != g_unk_002b4fd0) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_002b4fd4;
    }
    tmp_b6 = g_unk_002b4fd8 == g_unk_002b4fd4;
    tmp_f3 = g_unk_002b4fd8;
    if (!NAN(g_unk_002b4fd8) && !NAN(g_unk_002b4fd4)) goto LAB_000364b0;
    break;
  case 0x31:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Tripmine;
    if ((chargeCost_Tripmine != g_unk_002b4f68) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_unk_002b4f68;
    }
    if ((g_unk_002b4f6c != g_unk_002b4f68) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_unk_002b4f6c;
    }
    if ((g_unk_002b4f70 != g_unk_002b4f6c) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_unk_002b4f70;
    }
    if ((g_unk_002b4f74 != g_unk_002b4f70) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_unk_002b4f74;
    }
    tmp_b6 = g_unk_002b4f78 == g_unk_002b4f74;
    tmp_f3 = g_unk_002b4f78;
    if (!NAN(g_unk_002b4f78) && !NAN(g_unk_002b4f74)) goto LAB_000364b0;
  }
  if ((tmp_u5 & 0x20) != 0) {
    tmp_f2 = tmp_f3;
  }
LAB_000364c2:
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

bool BG_ClassHasWeapon(int param_1,int param_2,int param_3)
{
  bool tmp_b1;
  
  if (((param_3 == 0) || (tmp_b1 = true, GHIDRA_FIELD(g_pickAnyWeapon, 12, 4) == 0)) &&
     (tmp_b1 = false, param_2 != 0)) {
    if (((param_2 == *(int *)(param_1 + 0x10)) || (param_2 == *(int *)(param_1 + 0x14))) ||
       ((param_2 == *(int *)(param_1 + 0x18) ||
        ((param_2 == *(int *)(param_1 + 0x1c) || (param_2 == *(int *)(param_1 + 0x20))))))) {
      return true;
    }
    tmp_b1 = param_2 == *(int *)(param_1 + 0x24);
  }
  return tmp_b1;
}

bool BG_WeaponIsPrimaryForClassAndTeam(int param_1,int param_2,int param_3,int param_4)
{
  bool tmp_b1;
  
  if (param_2 == 2) {
    if (((param_4 == 0) || (tmp_b1 = true, GHIDRA_FIELD(g_pickAnyWeapon, 12, 4) == 0)) &&
       (tmp_b1 = false, param_3 != 0)) {
      param_1 = param_1 * 0x30;
      if (((param_3 != *(int *)(bg_allies_playerclasses + param_1 + 0x10)) &&
          (param_3 != *(int *)(bg_allies_playerclasses + param_1 + 0x14))) &&
         ((param_3 != *(int *)(bg_allies_playerclasses + param_1 + 0x18) &&
          ((param_3 != *(int *)(bg_allies_playerclasses + param_1 + 0x1c) &&
           (param_3 != *(int *)(bg_allies_playerclasses + param_1 + 0x20))))))) {
        return param_3 == *(int *)(bg_allies_playerclasses + param_1 + 0x24);
      }
      return true;
    }
  }
  else {
    tmp_b1 = false;
    if (param_2 == 1) {
      if ((param_4 != 0) && (GHIDRA_FIELD(g_pickAnyWeapon, 12, 4) != 0)) {
        return true;
      }
      tmp_b1 = false;
      if (param_3 != 0) {
        param_1 = param_1 * 0x30;
        if (param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x10)) {
          return true;
        }
        if (param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x14)) {
          return true;
        }
        if (param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x18)) {
          return true;
        }
        if (param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x1c)) {
          return true;
        }
        if (param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x20)) {
          return true;
        }
        return param_3 == *(int *)(bg_axis_playerclasses + param_1 + 0x24);
      }
    }
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
  return (param_1 + -0x30cae0 >> 3) * 0x286bca1b;
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
      *(uint32_t *)(tmp_i1 + 0x30cae4 + tmp_u3) = *(uint32_t *)(param_1 + 4 + tmp_u3);
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
      if ((tmp_i2 == 0) || (tmp_i2 = Q_stricmp(local_83c,&g_unk_0023ac61), tmp_i2 != 0)) {
        tmp_u3 = BG_SS_ParseError(tmp_i1,"expected \'{\'");
        return tmp_u3;
      }
LAB_00043da0:
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
LAB_00044008:
          tmp_i2 = BG_SS_ParseError(tmp_i1,"expected \'{\'");
        }
        else {
          tmp_i2 = Q_stricmp(local_424,&g_unk_0023ac61);
          if (tmp_i2 != 0) goto LAB_00044008;
LAB_00043e70:
          tmp_i2 = trap_PC_ReadToken(tmp_i1,local_434);
          if ((tmp_i2 == 0) || (local_424[0] == '}')) {
            if (0xff < numScriptSpeakers) {
              tmp_i2 = BG_SS_ParseError(tmp_i1,"Failed to store speaker",local_424);
              goto LAB_00043ee0;
            }
            tmp_i2 = numScriptSpeakers * 0x98;
            tmp_u4 = 0;
            numScriptSpeakers = numScriptSpeakers + 1;
            do {
              tmp_u3 = *(uint32_t *)((int)local_8e4 + tmp_u4 + 4);
              *(uint32_t *)(scriptSpeakers + tmp_u4 + tmp_i2) =
                   *(uint32_t *)((int)local_8e4 + tmp_u4);
              *(uint32_t *)(tmp_i2 + 0x30cae4 + tmp_u4) = tmp_u3;
              tmp_u4 = tmp_u4 + 8;
            } while (tmp_u4 < 0x98);
            goto LAB_00043da0;
          }
          tmp_i2 = Q_stricmp(local_424,"noise");
          if (tmp_i2 != 0) {
            tmp_i2 = Q_stricmp(local_424,"origin");
            if (tmp_i2 == 0) {
              tmp_i2 = PC_Vec_Parse(tmp_i1,local_8a0);
              if (tmp_i2 == 0) {
                tmp_i2 = BG_SS_ParseError(tmp_i1,"expected origin vector");
                goto LAB_00043ee0;
              }
            }
            else {
              tmp_i2 = Q_stricmp(local_424,"targetname");
              if (tmp_i2 == 0) {
                tmp_i2 = PC_String_ParseNoAlloc(tmp_i1,local_894,0x20);
                if (tmp_i2 == 0) {
                  tmp_i2 = BG_SS_ParseError(tmp_i1,"expected targetname string");
                  goto LAB_00043ee0;
                }
                local_874 = BG_StringHashValue(local_894);
              }
              else {
                tmp_i2 = Q_stricmp(local_424,"looped");
                if (tmp_i2 == 0) {
                  tmp_i2 = trap_PC_ReadToken(tmp_i1,local_434);
                  if (tmp_i2 == 0) {
                    tmp_i2 = BG_SS_ParseError(tmp_i1,"expected loop value");
                    goto LAB_00043ee0;
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
                        goto LAB_00043ee0;
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
                      goto LAB_00043ee0;
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
                          goto LAB_00043ee0;
                        }
                        local_86c = 2;
                      }
                    }
                  }
                  else {
                    tmp_i2 = Q_stricmp(local_424,&g_unk_0023f11d);
                    if (tmp_i2 == 0) {
                      tmp_i2 = PC_Int_Parse(tmp_i1,&local_868);
                      if (tmp_i2 == 0) {
                        tmp_i2 = BG_SS_ParseError(tmp_i1,"expected wait value");
                        goto LAB_00043ee0;
                      }
                      if (local_868 < 0) {
                        tmp_i2 = BG_SS_ParseError(tmp_i1,"wait value %i is invalid",local_868);
                        goto LAB_00043ee0;
                      }
                    }
                    else {
                      tmp_i2 = Q_stricmp(local_424,"random");
                      if (tmp_i2 == 0) {
                        tmp_i2 = PC_Int_Parse(tmp_i1,&local_864);
                        if (tmp_i2 == 0) {
                          tmp_i2 = BG_SS_ParseError(tmp_i1,"expected random value");
                          goto LAB_00043ee0;
                        }
                        if (local_864 < 0) {
                          tmp_i2 = BG_SS_ParseError(tmp_i1,"random value %i is invalid",local_864);
                          goto LAB_00043ee0;
                        }
                      }
                      else {
                        tmp_i2 = Q_stricmp(local_424,"volume");
                        if (tmp_i2 == 0) {
                          tmp_i2 = PC_Int_Parse(tmp_i1,&local_860);
                          if (tmp_i2 == 0) {
                            tmp_i2 = BG_SS_ParseError(tmp_i1,"expected volume value");
                            goto LAB_00043ee0;
                          }
                          if (0xffff < local_860) {
                            tmp_i2 = BG_SS_ParseError(tmp_i1,"volume value %i is invalid",local_860);
                            goto LAB_00043ee0;
                          }
                        }
                        else {
                          tmp_i2 = Q_stricmp(local_424,"range");
                          if (tmp_i2 != 0) {
                            tmp_i2 = BG_SS_ParseError(tmp_i1,"unknown token \'%s\'",local_424);
                            goto LAB_00043ee0;
                          }
                          tmp_i2 = PC_Int_Parse(tmp_i1,local_85c);
                          if (tmp_i2 == 0) {
                            tmp_i2 = BG_SS_ParseError(tmp_i1,"expected range value");
                            goto LAB_00043ee0;
                          }
                          if (local_85c[0] < 0) {
                            tmp_i2 = BG_SS_ParseError(tmp_i1,"range value %i is invalid",local_85c[0])
                            ;
                            goto LAB_00043ee0;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
            goto LAB_00043e70;
          }
          tmp_i2 = PC_String_ParseNoAlloc(tmp_i1,local_8e4,0x40);
          if (tmp_i2 != 0) goto LAB_00043e70;
          tmp_i2 = BG_SS_ParseError(tmp_i1,"expected sound filename");
        }
LAB_00043ee0:
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
      return (&g_unk_0023f204)[tmp_i1 * 2];
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
    local_43c = (float *)&g_unk_00395f04;
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
      tmp_pu8 = &g_unk_00355f04;
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
    pfVar7 = (float *)&g_unk_00396704;
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
    } while (pfVar7 != (float *)(string_12736 + 0x3e4));
    if (local_444 == local_468) {
      tmp_f1 = 1.0;
    }
    else {
      tmp_f1 = 254.0 / (float)(int)(local_444 - local_468);
    }
    pfVar7 = (float *)&g_unk_00356704;
    do {
      pfVar4 = pfVar7 + -0x100;
      do {
        if (*pfVar4 != 65536.0) {
          *pfVar4 = *pfVar4 / tmp_f1 + (float)(int)local_468;
        }
        pfVar4 = pfVar4 + 1;
      } while (pfVar7 != pfVar4);
      pfVar7 = pfVar7 + 0x100;
    } while (pfVar7 != (float *)&g_unk_00396704);
    if (local_448 == local_46c) {
      tmp_f1 = 1.0;
    }
    else {
      tmp_f1 = 254.0 / (float)(int)(local_448 - local_46c);
    }
    pfVar7 = (float *)&g_unk_00316704;
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
    } while (pfVar7 != (float *)&g_unk_00356704);
    g_unk_003d6304 = *param_2;
    g_unk_003d6308 = param_2[1];
    g_unk_003d630c = *param_3;
    g_unk_003d6310 = param_3[1];
    g_unk_003d6314 = local_470;
    g_unk_003d6318 = local_460;
    tracemap = 1;
    one_over_mapgrid_factor = 1.0 / ((*param_3 - *param_2) * 0.00390625);
    g_unk_003162e4 = 1.0 / ((param_3[1] - param_2[1]) * 0.00390625);
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
    tmp_f2 = g_unk_003d6304;
    if ((g_unk_003d6304 <= tmp_f1) && (tmp_f2 = tmp_f1, g_unk_003d630c < tmp_f1)) {
      tmp_f2 = g_unk_003d630c;
    }
    tmp_f1 = param_1[1];
    tmp_f3 = g_unk_003d6310;
    if ((g_unk_003d6310 <= tmp_f1) && (tmp_f3 = tmp_f1, g_unk_003d6308 < tmp_f1)) {
      tmp_f3 = g_unk_003d6308;
    }
    tmp_i4 = (int)ROUND((tmp_f2 - g_unk_003d6304) * one_over_mapgrid_factor);
    tmp_i6 = (int)ROUND((tmp_f3 - g_unk_003d6308) * g_unk_003162e4);
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
    return (long double)(float)(&g_unk_00316304)[tmp_i5 * 0x100 + tmp_i6];
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
    tmp_f2 = g_unk_003d6304;
    if ((g_unk_003d6304 <= tmp_f1) && (tmp_f2 = tmp_f1, g_unk_003d630c < tmp_f1)) {
      tmp_f2 = g_unk_003d630c;
    }
    tmp_f1 = param_1[1];
    tmp_f3 = g_unk_003d6310;
    if ((g_unk_003d6310 <= tmp_f1) && (tmp_f3 = tmp_f1, g_unk_003d6308 < tmp_f1)) {
      tmp_f3 = g_unk_003d6308;
    }
    tmp_i5 = (int)ROUND((tmp_f2 - g_unk_003d6304) * one_over_mapgrid_factor);
    tmp_i4 = (int)ROUND((tmp_f3 - g_unk_003d6308) * g_unk_003162e4);
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
    return (long double)(float)(&g_unk_00316304)[tmp_i5 + 0x10000 + tmp_i4 * 0x100];
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
    tmp_f2 = g_unk_003d6304;
    if ((g_unk_003d6304 <= tmp_f1) && (tmp_f2 = tmp_f1, g_unk_003d630c < tmp_f1)) {
      tmp_f2 = g_unk_003d630c;
    }
    tmp_f1 = param_1[1];
    tmp_f3 = g_unk_003d6310;
    if ((g_unk_003d6310 <= tmp_f1) && (tmp_f3 = tmp_f1, g_unk_003d6308 < tmp_f1)) {
      tmp_f3 = g_unk_003d6308;
    }
    tmp_i5 = (int)ROUND((tmp_f2 - g_unk_003d6304) * one_over_mapgrid_factor);
    tmp_i4 = (int)ROUND((tmp_f3 - g_unk_003d6308) * g_unk_003162e4);
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
    return (long double)(float)(&g_unk_00316304)[tmp_i5 + 0x20000 + tmp_i4 * 0x100];
  }
  return (long double)-65536.0;
}

uint32_t BG_GetTracemapGroundFloor(void)
{
  if (tracemap != 0) {
    return g_unk_003d6314;
  }
  return 0xffff0000;
}

uint32_t BG_RW_ParseError(uint32_t param_1,char *param_2)
{
  uint32_t local_a0;
  uint8_t local_9c [140];
  
  vsnprintf(string_12736,0x1000,param_2,&stack0x0000000c);
  local_a0 = 0;
  local_9c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_9c,&local_a0);
  Com_Printf("^1ERROR: %s, line %d: %s\n",local_9c,local_a0,string_12736);
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
  uStack_14 = 0x44fad;
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
LAB_00045040:
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
      if (!tmp_b9) goto LAB_000452a8;
      tmp_b1 = true;
      local_4e6c = local_4e44;
      tmp_pc3 = (char *)COM_Parse(&local_4e44);
      tmp_b9 = false;
      if (tmp_pc3 == (char *)0x0) break;
    } while( true );
  }
  goto LAB_0004507e;
LAB_000452a8:
  if (9 < (byte)(*tmp_pc3 - 0x30U)) {
    Com_Printf("unknown token in weapon cfg \'%s\' is %s\n",tmp_pc3,param_1);
    goto LAB_00045040;
  }
  local_4e44 = local_4e6c;
LAB_0004507e:
  tmp_pu7 = (uint *)(param_2 + 0x5c);
  do {
    tmp_pc3 = (char *)COM_Parse(&local_4e44);
    if (tmp_pc3 == (char *)0x0) goto LAB_000452e0;
    tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_pu7[-5] = tmp_u4;
    tmp_pc3 = (char *)COM_Parse(&local_4e44);
    if (tmp_pc3 == (char *)0x0) goto LAB_000452e0;
    tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_pu7[-4] = tmp_u4;
    tmp_pc3 = (char *)COM_Parse(&local_4e44);
    if (tmp_pc3 == (char *)0x0) goto LAB_000452e0;
    tmp_d11 = strtod(tmp_pc3,(char **)0x0);
    tmp_u4 = 1000;
    if ((float)tmp_d11 != 0.0) {
      tmp_u4 = (uint)ROUND(1000.0 / (float)tmp_d11);
    }
    tmp_pu7[-2] = tmp_u4;
    tmp_pu7[-1] = tmp_u4;
    tmp_pc3 = (char *)COM_Parse(&local_4e44);
    if (tmp_pc3 == (char *)0x0) goto LAB_000452e0;
    tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_pu7[-3] = tmp_u4;
    if ((int)tmp_pu7[-4] < (int)tmp_u4) {
      tmp_pu7[-3] = tmp_pu7[-4];
LAB_0004509b:
      *tmp_pu7 = 0;
    }
    else {
      if (-1 < (int)tmp_u4) goto LAB_0004509b;
      tmp_pu7[-3] = 0;
      *tmp_pu7 = 0;
    }
    if (tmp_b1) {
      tmp_pc3 = (char *)COM_Parse(&local_4e44);
      if (tmp_pc3 == (char *)0x0) {
LAB_000452e0:
        Com_Printf("Error parsing weapon animation file: %s",param_1);
        return 0;
      }
      tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
      *tmp_pu7 = tmp_u4;
      tmp_pc3 = (char *)COM_Parse(&local_4e44);
      if (tmp_pc3 == (char *)0x0) goto LAB_000452e0;
      tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
      if (tmp_l5 != 0) {
        *tmp_pu7 = *tmp_pu7 | 0x10000;
      }
      tmp_pc3 = (char *)COM_Parse(&local_4e44);
      if (tmp_pc3 == (char *)0x0) goto LAB_000452e0;
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
  uStack_14 = 0x4532b;
  tmp_i1 = trap_PC_ReadToken(param_1,local_434);
  if (((tmp_i1 == 0) || (local_424 != '{')) || (local_423 != '\0')) {
    return 0;
  }
LAB_00045380:
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
      goto LAB_00045380;
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
                                                goto LAB_00045380;
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
                                                    goto LAB_00045380;
                                                  }
                                                }
                                                else if (((local_474 == 'n') && (local_473 == 'o'))
                                                        && (local_472 == '\0')) {
                                                  *(uint32_t *)(param_2 + 0x684) = 2;
                                                  goto LAB_00045380;
                                                }
                                                Com_Printf("expected yes/no \n");
                                                *(uint32_t *)(param_2 + 0x684) = 0;
                                                goto LAB_00045380;
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
                                                    goto LAB_00045380;
                                                  }
                                                }
                                                else if (((local_474 == 'n') && (local_473 == 'o'))
                                                        && (local_472 == '\0')) {
                                                  *(uint32_t *)(param_2 + 0x68c) = 2;
                                                  goto LAB_00045380;
                                                }
                                                Com_Printf("expected yes/no \n");
                                                *(uint32_t *)(param_2 + 0x68c) = 0;
                                                goto LAB_00045380;
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
                                                    goto LAB_00045380;
                                                  }
                                                }
                                                else if (((local_474 == 'n') && (local_473 == 'o'))
                                                        && (local_472 == '\0')) {
                                                  *(uint32_t *)(param_2 + 0x688) = 2;
                                                  goto LAB_00045380;
                                                }
                                                Com_Printf("expected yes/no \n");
                                                *(uint32_t *)(param_2 + 0x688) = 0;
                                                goto LAB_00045380;
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
                                                  goto LAB_00045380;
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
                                                      goto LAB_00045380;
                                                    }
                                                  }
                                                  else if (((local_474 == 'n') && (local_473 == 'o')
                                                           ) && (local_472 == '\0')) {
                                                    *(uint32_t *)(param_2 + 0x6a4) = 2;
                                                    goto LAB_00045380;
                                                  }
                                                  Com_Printf("expected yes/no \n");
                                                  *(uint32_t *)(param_2 + 0x6a4) = 0;
                                                  goto LAB_00045380;
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
                                                      goto LAB_00045380;
                                                    }
                                                  }
                                                  else if (((local_474 == 'n') && (local_473 == 'o')
                                                           ) && (local_472 == '\0')) {
                                                    *(uint32_t *)(param_2 + 0x6a8) = 2;
                                                    goto LAB_00045380;
                                                  }
                                                  Com_Printf("expected yes/no \n");
                                                  *(uint32_t *)(param_2 + 0x6a8) = 0;
                                                  goto LAB_00045380;
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
      goto LAB_00045380;
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
  uStack_14 = 0x4607b;
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
LAB_00046120:
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
                  if ((tmp_i1 == 0) || (tmp_u6 = 1, local_424 == '}')) goto LAB_0004615d;
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
                  goto LAB_0004615d;
                }
                tmp_i1 = BG_ParseWeaponConfig();
                tmp_u6 = tmp_i1 == 0;
              } while (!(bool)tmp_u6);
              BG_RW_ParseError(param_1,"error in weaponConfig!!!");
            }
          }
LAB_0004615d:
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
          goto LAB_00046120;
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
    tmp_u1 = va("%s/%s",&g_unk_02ad55a4,tmp_pc3);
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

uint32_t BG_PCF_ParseError(uint32_t param_1,char *param_2)
{
  uint32_t local_a0;
  uint8_t local_9c [140];
  
  vsnprintf(string_13804,0x1000,param_2,&stack0x0000000c);
  local_a0 = 0;
  local_9c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_9c,&local_a0);
  Com_Printf("^1ERROR: %s, line %d: %s\n",local_9c,local_a0,string_13804);
  trap_PC_FreeSource(param_1);
  return 0;
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

