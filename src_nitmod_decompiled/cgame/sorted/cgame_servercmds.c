/* Server-command and config-string processing — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_servercmds.h"

void CG_ParseMapEntity(int *param_1,int *param_2,uint32_t param_3)
{
  int tmp_i1;
  int tmp_i2;
  float tmp_f3;
  long tmp_l4;
  byte tmp_b5;
  char local_2c [28];
  
  tmp_i1 = *param_1;
  tmp_i2 = *param_2;
  *param_2 = tmp_i2 + 1;
  trap_Argv(tmp_i2,local_2c,0x10);
  tmp_l4 = strtol(local_2c,(char **)0x0,10);
  tmp_b5 = (char)tmp_l4 - 3;
  (&g_unk_002a75b4)[tmp_i1 * 0x2c] = (char)tmp_l4;
  if ((tmp_b5 < 7) && ((1 << (tmp_b5 & 0x1f) & 0x77U) != 0)) {
    tmp_i2 = *param_2;
    *param_2 = tmp_i2 + 1;
    trap_Argv(tmp_i2,local_2c,0x10);
    tmp_l4 = strtol(local_2c,(char **)0x0,10);
    (&mapEntities)[tmp_i1 * 0xb] = tmp_l4 << 7;
    tmp_i2 = *param_2;
    *param_2 = tmp_i2 + 1;
    trap_Argv(tmp_i2,local_2c,0x10);
    tmp_l4 = strtol(local_2c,(char **)0x0,10);
    (&g_unk_002a75a4)[tmp_i1 * 0xb] = tmp_l4 << 7;
    if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
      tmp_i2 = *param_2;
      *param_2 = tmp_i2 + 1;
      trap_Argv(tmp_i2,local_2c,0x10);
      tmp_l4 = strtol(local_2c,(char **)0x0,10);
      *(long *)(&g_unk_002a75a8 + tmp_i1 * 0x2c) = tmp_l4 << 7;
    }
  }
  else {
    tmp_i2 = *param_2;
    *param_2 = tmp_i2 + 1;
    trap_Argv(tmp_i2,local_2c,0x10);
    tmp_l4 = strtol(local_2c,(char **)0x0,10);
    (&mapEntities)[tmp_i1 * 0xb] = tmp_l4 << 7;
    tmp_i2 = *param_2;
    *param_2 = tmp_i2 + 1;
    trap_Argv(tmp_i2,local_2c,0x10);
    tmp_l4 = strtol(local_2c,(char **)0x0,10);
    (&g_unk_002a75a4)[tmp_i1 * 0xb] = tmp_l4 << 7;
    if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
      tmp_i2 = *param_2;
      *param_2 = tmp_i2 + 1;
      trap_Argv(tmp_i2,local_2c,0x10);
      tmp_l4 = strtol(local_2c,(char **)0x0,10);
      *(long *)(&g_unk_002a75a8 + tmp_i1 * 0x2c) = tmp_l4 << 7;
    }
    tmp_i2 = *param_2;
    *param_2 = tmp_i2 + 1;
    trap_Argv(tmp_i2,local_2c,0x10);
    tmp_l4 = strtol(local_2c,(char **)0x0,10);
    *(long *)(&g_unk_002a75ac + tmp_i1 * 0x2c) = tmp_l4;
  }
  tmp_i2 = *param_2;
  *param_2 = tmp_i2 + 1;
  trap_Argv(tmp_i2,local_2c,0x10);
  tmp_l4 = strtol(local_2c,(char **)0x0,10);
  (&g_unk_002a75b0)[tmp_i1 * 0xb] = tmp_l4;
  (&g_unk_002a75b8)[tmp_i1 * 0xb] =
       ((float)(int)(&mapEntities)[tmp_i1 * 0xb] - g_unk_010abd54) * g_unk_010abd64 * 352.0;
  tmp_f3 = ((float)(int)(&g_unk_002a75a4)[tmp_i1 * 0xb] - g_unk_010abd58) * g_unk_010abd68;
  (&g_unk_002a75c8)[tmp_i1 * 0xb] = param_3;
  (&g_unk_002a75bc)[tmp_i1 * 0xb] = tmp_f3 * 352.0;
  *param_1 = *param_1 + 1;
  return;
}

void CG_ParseMapEntityInfo(int param_1,int param_2)
{
  uint32_t tmp_u1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int *tmp_pi6;
  int tmp_i7;
  int tmp_i8;
  uint32_t local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0x3be10;
  local_20[0] = 3;
  mapEntityCount = 0;
  mapEntityTime = g_unk_010906e0;
  if (0 < param_1) {
    tmp_i8 = 0;
    do {
      tmp_i8 = tmp_i8 + 1;
      CG_ParseMapEntity(&mapEntityCount,local_20,1);
    } while (tmp_i8 != param_1);
  }
  if (0 < param_2) {
    tmp_i8 = 0;
    do {
      tmp_i8 = tmp_i8 + 1;
      CG_ParseMapEntity(&mapEntityCount,local_20,2);
    } while (tmp_i8 != param_2);
  }
  tmp_f5 = g_unk_010abd68;
  tmp_f4 = g_unk_010abd64;
  tmp_f3 = g_unk_010abd58;
  tmp_f2 = g_unk_010abd54;
  tmp_u1 = GHIDRA_FIELD(cg_automapZoom, 8, 4);
  tmp_i8 = mapEntityCount;
  if (0 < mapEntityCount) {
    tmp_i7 = 0;
    tmp_pi6 = &mapEntities;
    do {
      tmp_i7 = tmp_i7 + 1;
      tmp_pi6[8] = (int)(((float)*tmp_pi6 - tmp_f2) * tmp_f4 * 100.0 * (float)tmp_u1);
      tmp_pi6[9] = (int)(((float)tmp_pi6[1] - tmp_f3) * tmp_f5 * 100.0 * (float)tmp_u1);
      tmp_pi6 = tmp_pi6 + 0xb;
    } while (tmp_i7 != tmp_i8);
  }
  return;
}

void CG_ParseFireteams(void)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  long tmp_l4;
  int tmp_i5;
  int tmp_i6;
  long *plVar7;
  int local_50;
  uint8_t local_30 [4];
  uint8_t local_2c [5];
  uint32_t local_27;
  uint32_t local_23;
  uint16_t local_1f;
  uint8_t local_1d;
  uint32_t uStack_14;
  
  uStack_14 = 0x764c9;
  if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
    tmp_i6 = GHIDRA_FIELD(cgs, 27400, 4) * 0x1a4;
    tmp_pu1 = (uint32_t *)(cgs + 0x9578);
    do {
      *tmp_pu1 = 0;
      tmp_pu1 = tmp_pu1 + 0x69;
    } while (tmp_pu1 != (uint32_t *)(cgs + tmp_i6 + 0x9578));
  }
  plVar7 = &g_unk_010b3b30;
  local_50 = 0x283;
  do {
    local_27 = 0x30307830;
    local_23 = 0x30303030;
    local_1f = 0x3030;
    local_1d = 0;
    tmp_u2 = nitrox_ConfigString(local_50);
    tmp_pc3 = (char *)Info_ValueForKey(tmp_u2,&g_unk_0010d2e7);
    tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
    if (tmp_l4 == -1) {
      plVar7[0x12] = 0;
    }
    else {
      *plVar7 = tmp_l4;
      plVar7[0x12] = 1;
      tmp_pc3 = (char *)Info_ValueForKey(tmp_u2,"l");
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      plVar7[0x11] = tmp_l4;
      tmp_i6 = Info_ValueForKey(tmp_u2,"c");
      Q_strncpyz((int)&local_27 + 2,tmp_i6,9);
      __isoc99_sscanf(&local_27,&g_unk_00115a04,local_2c);
      Q_strncpyz((int)&local_27 + 2,tmp_i6 + 8,9);
      __isoc99_sscanf(&local_27,&g_unk_00115a04,local_30);
      if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
        tmp_pu1 = (uint32_t *)(cgs + 0x9578);
        tmp_i6 = 0;
        do {
          tmp_i5 = COM_BitCheck(local_30,tmp_i6);
          if (tmp_i5 != 0) {
            *tmp_pu1 = plVar7;
          }
          tmp_pu1 = tmp_pu1 + 0x69;
          *(bool *)((int)plVar7 + tmp_i6 + 4) = tmp_i5 != 0;
          tmp_i6 = tmp_i6 + 1;
        } while (tmp_i6 < (int)GHIDRA_FIELD(cgs, 27400, 4));
      }
    }
    tmp_u2 = GHIDRA_FIELD(cgs, 27400, 4);
    local_50 = local_50 + 1;
    plVar7 = plVar7 + 0x14;
  } while (plVar7 != (long *)&g_unk_010b3ef0);
  if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
    tmp_i6 = 0;
    do {
      (&sortedFireTeamClients)[tmp_i6] = tmp_i6;
      tmp_i6 = tmp_i6 + 1;
    } while (tmp_i6 != tmp_u2);
  }
  qsort(&sortedFireTeamClients,tmp_u2,4,CG_SortFireTeam);
  return;
}

void CG_ParseTeamXPs(int param_1)
{
  char *tmp_pc1;
  long tmp_l2;
  uint8_t *tmp_pu3;
  uint8_t *tmp_pu4;
  uint8_t *tmp_pu5;
  uint32_t local_20 [4];
  
  local_20[0] = CG_ConfigString(param_1 + 0x1f);
  tmp_pu3 = cgs;
  do {
    while (tmp_pu5 = tmp_pu3, param_1 != 0) {
      do {
        tmp_pc1 = (char *)COM_ParseExt(local_20,0);
        if (tmp_pc1 == (char *)0x0) {
          return;
        }
        if (*tmp_pc1 == '\0') {
          return;
        }
        tmp_pu4 = tmp_pu5 + 0x28;
        tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
        *(long *)(cgs + (int)(tmp_pu5 + 0xf33f9c)) = tmp_l2;
        tmp_pu5 = tmp_pu4;
      } while (tmp_pu4 != tmp_pu3 + 0x118);
      tmp_pu3 = tmp_pu3 + 4;
      if (tmp_pu3 == (uint8_t *)0x10efe88) {
        return;
      }
    }
    do {
      tmp_pc1 = (char *)COM_ParseExt(local_20,0);
      if (tmp_pc1 == (char *)0x0) {
        return;
      }
      if (*tmp_pc1 == '\0') {
        return;
      }
      tmp_pu4 = tmp_pu5 + 0x28;
      tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
      *(long *)(cgs + (int)(tmp_pu5 + 0xf33e84)) = tmp_l2;
      tmp_pu5 = tmp_pu4;
    } while (tmp_pu4 != tmp_pu3 + 0x118);
    tmp_pu3 = tmp_pu3 + 4;
    if (tmp_pu3 == (uint8_t *)0x10efe88) {
      return;
    }
  } while( true );
}

uint32_t CG_ParseVoiceChats_constprop_4(uint32_t param_1,int param_2)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  byte *tmp_pb7;
  int tmp_i8;
  char *tmp_pc9;
  char *tmp_pc10;
  bool tmp_b11;
  byte tmp_b12;
  int local_8024;
  uint8_t *local_8020;
  uint8_t local_801c [32776];
  uint32_t uStack_14;
  
  tmp_u5 = GHIDRA_FIELD(cg_buildScript, 12, 4);
  tmp_b12 = 0;
  uStack_14 = 0xb187f;
  tmp_i2 = trap_FS_FOpenFile(param_1,&local_8024,0);
  if (local_8024 == 0) {
    tmp_u5 = va("^1voice chat file not found: %s\n",param_1);
    trap_Print(tmp_u5);
    return 0;
  }
  if (0x7fff < tmp_i2) {
    tmp_u5 = va("^1voice chat file too large: %s is %i, max allowed is %i",param_1,tmp_i2,0x8000);
    trap_Print(tmp_u5);
    trap_FS_FCloseFile(local_8024);
    return 0;
  }
  trap_FS_Read(local_801c,tmp_i2,local_8024);
  local_801c[tmp_i2] = 0;
  trap_FS_FCloseFile(local_8024);
  local_8020 = local_801c;
  Com_sprintf(param_2,0x40,"%s",param_1);
  tmp_pu1 = (uint8_t *)(param_2 + 0x48);
  tmp_pu3 = tmp_pu1;
  do {
    *tmp_pu3 = 0;
    tmp_pu3 = tmp_pu3 + 0x944;
  } while (tmp_pu3 != (uint8_t *)(param_2 + 0x9d888));
  tmp_pc4 = (char *)COM_ParseExt(&local_8020,1);
  if ((tmp_pc4 != (char *)0x0) && (tmp_b11 = *tmp_pc4 == '\0', !tmp_b11)) {
    tmp_i2 = 7;
    tmp_pc9 = tmp_pc4;
    tmp_pc10 = "female";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_b11 = *tmp_pc9 == *tmp_pc10;
      tmp_pc9 = tmp_pc9 + (uint)tmp_b12 * -2 + 1;
      tmp_pc10 = tmp_pc10 + (uint)tmp_b12 * -2 + 1;
    } while (tmp_b11);
    if (tmp_b11) {
      *(uint32_t *)(param_2 + 0x40) = 1;
    }
    else {
      tmp_i2 = 5;
      tmp_b11 = false;
      tmp_pc9 = tmp_pc4;
      tmp_pc10 = "male";
      do {
        if (tmp_i2 == 0) break;
        tmp_i2 = tmp_i2 + -1;
        tmp_b11 = *tmp_pc9 == *tmp_pc10;
        tmp_pc9 = tmp_pc9 + (uint)tmp_b12 * -2 + 1;
        tmp_pc10 = tmp_pc10 + (uint)tmp_b12 * -2 + 1;
      } while (tmp_b11);
      if (tmp_b11) {
        *(uint32_t *)(param_2 + 0x40) = 0;
      }
      else {
        tmp_i2 = 7;
        tmp_pc9 = "neuter";
        do {
          if (tmp_i2 == 0) break;
          tmp_i2 = tmp_i2 + -1;
          tmp_b11 = *tmp_pc4 == *tmp_pc9;
          tmp_pc4 = tmp_pc4 + (uint)tmp_b12 * -2 + 1;
          tmp_pc9 = tmp_pc9 + (uint)tmp_b12 * -2 + 1;
        } while (tmp_b11);
        if (!tmp_b11) {
          tmp_u5 = va("^1expected gender not found in voice chat file: %s\n",param_1);
          trap_Print(tmp_u5);
          return 0;
        }
        *(uint32_t *)(param_2 + 0x40) = 2;
      }
    }
    *(uint32_t *)(param_2 + 0x44) = 0;
    while ((tmp_pc4 = (char *)COM_ParseExt(&local_8020,1), tmp_pc4 != (char *)0x0 && (*tmp_pc4 != '\0')
           )) {
      Com_sprintf(tmp_pu1 + *(int *)(param_2 + 0x44) * 0x944,0x40,"%s",tmp_pc4);
      tmp_pc4 = (char *)COM_ParseExt(&local_8020,1);
      if ((*tmp_pc4 != '{') || (tmp_pc4[1] != '\0')) {
        tmp_u5 = va("^1Expected { found %s in voice chat file: %s\n",tmp_pc4,param_1);
        trap_Print(tmp_u5);
        return 0;
      }
      *(uint32_t *)(param_2 + 0x88 + *(int *)(param_2 + 0x44) * 0x944) = 0;
      tmp_i2 = *(int *)(param_2 + 0x88 + *(int *)(param_2 + 0x44) * 0x944);
      do {
        tmp_pc4 = (char *)COM_ParseExt(&local_8020,1);
        if (tmp_pc4 == (char *)0x0) {
          return 1;
        }
        if (*tmp_pc4 == '\0') {
          return 1;
        }
        if ((*tmp_pc4 == '}') && (tmp_pc4[1] == '\0')) {
          tmp_i8 = *(int *)(param_2 + 0x44);
          break;
        }
        tmp_i8 = *(int *)(param_2 + 0x44);
        tmp_u6 = trap_S_RegisterSound(tmp_pc4,tmp_u5 == 0);
        *(uint32_t *)(tmp_pu1 + tmp_i2 * 4 + tmp_i8 * 0x944 + 0x44) = tmp_u6;
        tmp_pc4 = (char *)COM_ParseExt(&local_8020,1);
        if (tmp_pc4 == (char *)0x0) {
          return 1;
        }
        if (*tmp_pc4 == '\0') {
          return 1;
        }
        Com_sprintf(tmp_pu1 + (tmp_i2 + 3) * 0x40 + *(int *)(param_2 + 0x44) * 0x944 + 4,0x40,"%s",
                    tmp_pc4);
        tmp_pb7 = (byte *)COM_ParseExt(&local_8020,0);
        tmp_i8 = 0x7d - (uint)*tmp_pb7;
        if (tmp_i8 == 0) {
          tmp_i8 = -(uint)tmp_pb7[1];
        }
        if ((tmp_i8 == 0) || (*tmp_pb7 == 0)) {
          tmp_i8 = *(int *)(param_2 + 0x44);
          tmp_u6 = trap_R_RegisterShader("sprites/voiceChat");
          *(uint32_t *)(tmp_pu1 + tmp_i2 * 4 + tmp_i8 * 0x944 + 0x8c4) = tmp_u6;
          COM_RestoreParseSession(&local_8020);
          tmp_pu3 = tmp_pu1 + *(int *)(param_2 + 0x44) * 0x944;
        }
        else {
          tmp_i8 = *(int *)(param_2 + 0x44);
          tmp_u6 = trap_R_RegisterShader(tmp_pb7);
          *(uint32_t *)(tmp_pu1 + tmp_i2 * 4 + tmp_i8 * 0x944 + 0x8c4) = tmp_u6;
          tmp_pu3 = tmp_pu1 + *(int *)(param_2 + 0x44) * 0x944;
          if (*(int *)(tmp_pu3 + tmp_i2 * 4 + 0x8c4) == 0) {
            tmp_u6 = trap_R_RegisterShader("sprites/voiceChat");
            *(uint32_t *)(tmp_pu3 + tmp_i2 * 4 + 0x8c4) = tmp_u6;
            tmp_pu3 = tmp_pu1 + *(int *)(param_2 + 0x44) * 0x944;
          }
        }
        *(int *)(tmp_pu3 + 0x40) = *(int *)(tmp_pu3 + 0x40) + 1;
        tmp_i8 = *(int *)(param_2 + 0x44);
        tmp_i2 = *(int *)(param_2 + 0x88 + tmp_i8 * 0x944);
      } while (tmp_i2 < 0x20);
      *(int *)(param_2 + 0x44) = tmp_i8 + 1;
      if (0x10f < tmp_i8 + 1) {
        return 1;
      }
    }
  }
  return 1;
}

void CG_ParseServerinfo(char *param_1)
{
  uint tmp_u1;
  uint tmp_u2;
  char *tmp_pc3;
  long tmp_l4;
  uint32_t tmp_u5;
  int tmp_i6;
  char *tmp_pc7;
  uint8_t tmp_u8;
  byte tmp_b9;
  double tmp_d10;
  uint32_t local_43c;
  uint32_t local_438 [7];
  char local_41c [4];
  uint32_t local_418 [257];
  uint32_t uStack_14;
  
  tmp_b9 = 0;
  uStack_14 = 0xb314d;
  local_43c = 0;
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_438 + tmp_u2) = 0;
    *(uint32_t *)((int)local_438 + tmp_u2 + 4) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0x18);
  *(uint32_t *)((int)local_438 + tmp_u2 + 8) = 0;
  local_41c[0] = '\0';
  local_41c[1] = '\0';
  local_41c[2] = '\0';
  local_41c[3] = '\0';
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_418 + tmp_u2) = 0;
    *(uint32_t *)((int)local_418 + tmp_u2 + 4) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0x3f8);
  *(uint32_t *)((int)local_418 + tmp_u2 + 8) = 0;
  tmp_u8 = *param_1 == '\0';
  if ((bool)tmp_u8) {
    param_1 = (char *)CG_ConfigString(0);
    CachedServerInfo = param_1;
  }
  tmp_pc3 = (char *)Info_ValueForKey(param_1,"mod_version");
  tmp_i6 = 6;
  tmp_pc7 = "2.3.5";
  do {
    if (tmp_i6 == 0) break;
    tmp_i6 = tmp_i6 + -1;
    tmp_u8 = *tmp_pc3 == *tmp_pc7;
    tmp_pc3 = tmp_pc3 + (uint)tmp_b9 * -2 + 1;
    tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
  } while ((bool)tmp_u8);
  if ((!(bool)tmp_u8) && (g_unk_01047aec == 0)) {
    tmp_u5 = Info_ValueForKey(param_1,"mod_version");
    tmp_u5 = va("^7N^1!^7tmod:\n^7Server/Client mod version mismatch.\n^7(Client: ^3%s^7, Server: ^3%s^7)\n"
               ,&g_unk_00116f02,tmp_u5);
    CG_Error(tmp_u5);
  }
  tmp_u5 = GHIDRA_FIELD(cgs, 33822772, 4);
  if (0 < (int)GHIDRA_FIELD(cgs, 33822772, 4)) {
    tmp_pc3 = (char *)Info_ValueForKey(param_1,"nport");
    tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
    if (tmp_u5 != tmp_l4) {
      tmp_pc3 = (char *)Info_ValueForKey(param_1,"nport");
      GHIDRA_FIELD(cgs, 33822772, 4) = strtol(tmp_pc3,(char **)0x0,10);
    }
  }
  tmp_pc3 = (char *)Info_ValueForKey(param_1,"sv_maxClients");
  GHIDRA_FIELD(cgs, 27400, 4) = strtol(tmp_pc3,(char **)0x0,10);
  while( true ) {
    Info_NextPair(&param_1,&local_43c,local_41c);
    if ((char)local_43c == '\0') break;
    tmp_u5 = nitrox_GetTokenForString(&local_43c);
    switch(tmp_u5) {
    case 0x4e:
      GHIDRA_FIELD(cg_gameType, 12, 4) = strtol(local_41c,(char **)0x0,10);
      GHIDRA_FIELD(cgs, 27388, 4) = GHIDRA_FIELD(cg_gameType, 12, 4);
      break;
    case 0x53:
      tmp_l4 = strtol(local_41c,(char **)0x0,10);
      GHIDRA_FIELD(cgs, 27660, 4) = (float)tmp_l4 * 0.01;
      break;
    case 0x54:
      GHIDRA_FIELD(cg_antilag, 12, 4) = strtol(local_41c,(char **)0x0,10);
      GHIDRA_FIELD(cgs, 27392, 4) = GHIDRA_FIELD(cg_antilag, 12, 4);
      break;
    case 0x56:
      Q_strncpyz(0x10f69ac,local_41c,0x40);
      Com_sprintf(0x10f696c,0x40,"maps/%s.bsp",local_41c);
      break;
    case 0x5d:
      tmp_pc3 = "0";
      if (GHIDRA_FIELD(authLevel, 12, 4) == 0) {
        tmp_pc3 = local_41c;
      }
      trap_Cvar_Set("cg_ui_voteFlags",tmp_pc3);
      break;
    case 0x5e:
      tmp_d10 = strtod(local_41c,(char **)0x0);
      GHIDRA_FIELD(cgs, 27396, 4) = (uint32_t)tmp_d10;
      break;
    case 0x60:
      trap_Cvar_Set("g_redlimbotime",local_41c);
      GHIDRA_FIELD(cg_redlimbotime, 12, 4) = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x61:
      trap_Cvar_Set("g_bluelimbotime",local_41c);
      GHIDRA_FIELD(cg_bluelimbotime, 12, 4) = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x62:
      GHIDRA_FIELD(cgs, 33823116, 4) = strtol(local_41c,(char **)0x0,10);
      break;
    case 99:
      GHIDRA_FIELD(cgs, 33823120, 4) = strtol(local_41c,(char **)0x0,10);
      break;
    case 100:
      GHIDRA_FIELD(cgs, 33525352, 4) = strtol(local_41c,(char **)0x0,10);
    }
  }
  if (GHIDRA_FIELD(cgs, 27384, 4) == 0) {
    tmp_u5 = va("%i",GHIDRA_FIELD(cgs, 27388, 4));
    trap_Cvar_Set("g_gametype",tmp_u5);
    tmp_u5 = va("%i",GHIDRA_FIELD(cgs, 27392, 4));
    trap_Cvar_Set("g_antilag",tmp_u5);
    trap_Cvar_Update(cg_antilag);
    trap_Cvar_Update(cg_gameType);
  }
  return;
}

void CG_ParseOIDInfo(int param_1)
{
  char *tmp_pc1;
  uint tmp_u2;
  char *tmp_pc3;
  long tmp_l4;
  
  tmp_pc1 = (char *)nitrox_ConfigString(param_1 + 0x261);
  tmp_u2 = 0;
  do {
    *(uint32_t *)(param_1 * 0x60 + 0x3113db4 + tmp_u2) = 0;
    *(uint32_t *)(param_1 * 0x60 + 0x3113db8 + tmp_u2) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x60);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,"s");
    if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      *(long *)(cgs + param_1 * 0x60 + 0x2023f54) = tmp_l4;
    }
    tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,"b");
    if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      *(uint32_t *)(cgs + param_1 * 0x60 + 0x2023f58) = *(uint32_t *)(cgs + tmp_l4 * 4 + 0x7b48);
    }
    tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,"r");
    if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      *(uint32_t *)(cgs + param_1 * 0x60 + 0x2023f5c) = *(uint32_t *)(cgs + tmp_l4 * 4 + 0x7b48);
    }
    tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,&g_unk_00120a20);
    if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      *(long *)(cgs + param_1 * 0x60 + 0x2023f64) = tmp_l4;
    }
    tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,"e");
    if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      *(long *)(cgs + param_1 * 0x60 + 0x2023f60) = tmp_l4;
    }
    tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,&g_unk_0010d2e7);
    if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
      Q_strncpyz(param_1 * 0x60 + 0x3113dc8,tmp_pc3,0x40);
    }
    tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,&g_unk_00115a05);
    if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      *(float *)(cgs + param_1 * 0x60 + 0x2023fa8) = (float)tmp_l4;
    }
    tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,"y");
    if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      *(float *)(cgs + param_1 * 0x60 + 0x2023fac) = (float)tmp_l4;
    }
    tmp_pc1 = (char *)Info_ValueForKey(tmp_pc1,"z");
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_l4 = strtol(tmp_pc1,(char **)0x0,10);
      *(float *)(cgs + param_1 * 0x60 + 0x2023fb0) = (float)tmp_l4;
    }
  }
  return;
}

void CG_ParseOIDInfos(void)
{
  char *tmp_pc1;
  uint tmp_u2;
  char *tmp_pc3;
  long tmp_l4;
  int tmp_i5;
  long *plVar6;
  
  tmp_i5 = 0x261;
  plVar6 = (long *)(cgs + 0x2023f54);
  do {
    tmp_pc1 = (char *)nitrox_ConfigString(tmp_i5);
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)plVar6 + tmp_u2) = 0;
      *(uint32_t *)((int)plVar6 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < 0x60);
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,"s");
      if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
        tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
        *plVar6 = tmp_l4;
      }
      tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,"b");
      if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
        tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
        plVar6[1] = *(long *)(cgs + tmp_l4 * 4 + 0x7b48);
      }
      tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,"r");
      if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
        tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
        plVar6[2] = *(long *)(cgs + tmp_l4 * 4 + 0x7b48);
      }
      tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,&g_unk_00120a20);
      if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
        tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
        plVar6[4] = tmp_l4;
      }
      tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,"e");
      if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
        tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
        plVar6[3] = tmp_l4;
      }
      tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,&g_unk_0010d2e7);
      if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
        Q_strncpyz(plVar6 + 5,tmp_pc3,0x40);
      }
      tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,&g_unk_00115a05);
      if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
        tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
        plVar6[0x15] = (long)(float)tmp_l4;
      }
      tmp_pc3 = (char *)Info_ValueForKey(tmp_pc1,"y");
      if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
        tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
        plVar6[0x16] = (long)(float)tmp_l4;
      }
      tmp_pc1 = (char *)Info_ValueForKey(tmp_pc1,"z");
      if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
        tmp_l4 = strtol(tmp_pc1,(char **)0x0,10);
        plVar6[0x17] = (long)(float)tmp_l4;
      }
    }
    plVar6 = plVar6 + 0x18;
    tmp_i5 = tmp_i5 + 1;
  } while (plVar6 != (long *)(cgs + 0x2024614));
  return;
}

void CG_ParseSpawns(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  long tmp_l5;
  int *tmp_pi6;
  float *pfVar7;
  double tmp_d8;
  int local_2c;
  uint8_t *local_28;
  
  tmp_u3 = CG_ConfigString(0xd);
  tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,&g_unk_0010d2e7);
  if ((tmp_pc4 != (char *)0x0) && (*tmp_pc4 != '\0')) {
    Q_strncpyz(&g_unk_010abd80,"Auto Pick",0x80);
    tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
    g_unk_010ad280 = tmp_l5 + 1;
    if (1 < g_unk_010ad280) {
      local_28 = &g_unk_010abe00;
      local_2c = 1;
      pfVar7 = (float *)&g_unk_010acf0c;
      tmp_pi6 = &g_unk_010ad084;
      while( true ) {
        tmp_u3 = nitrox_ConfigString(local_2c + 0x272);
        tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,"s");
        if ((tmp_pc4 == (char *)0x0) || (*tmp_pc4 == '\0')) break;
        Q_strncpyz(local_28,tmp_pc4,0x80);
        tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,&g_unk_00115a05);
        if (tmp_pc4 == (char *)0x0) {
          return;
        }
        if (*tmp_pc4 == '\0') {
          return;
        }
        tmp_d8 = strtod(tmp_pc4,(char **)0x0);
        *pfVar7 = (float)tmp_d8;
        pfVar7[-0x60] = (float)tmp_d8;
        tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,"y");
        if (tmp_pc4 == (char *)0x0) {
          return;
        }
        if (*tmp_pc4 == '\0') {
          return;
        }
        tmp_d8 = strtod(tmp_pc4,(char **)0x0);
        tmp_u2 = GHIDRA_FIELD(cgs, 33575848, 4);
        pfVar7[1] = (float)tmp_d8;
        pfVar7[-0x5f] = (float)tmp_d8;
        if (tmp_u2 != 0) {
          tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,"z");
          if (tmp_pc4 == (char *)0x0) {
            return;
          }
          if (*tmp_pc4 == '\0') {
            return;
          }
          tmp_d8 = strtod(tmp_pc4,(char **)0x0);
          pfVar7[2] = (float)tmp_d8;
          pfVar7[-0x5e] = (float)tmp_d8;
        }
        CG_TransformToCommandMapCoord(pfVar7,pfVar7 + 1);
        tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,&g_unk_0010d2bf);
        tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
        if (*tmp_pi6 != tmp_l5) {
          tmp_pi6[0x20] = *tmp_pi6;
          tmp_i1 = g_unk_010906e0;
          *tmp_pi6 = tmp_l5;
          tmp_pi6[0x40] = tmp_i1;
        }
        pfVar7 = pfVar7 + 3;
        tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,"c");
        tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
        local_2c = local_2c + 1;
        local_28 = local_28 + 0x80;
        tmp_pi6[0x60] = tmp_l5;
        tmp_pi6 = tmp_pi6 + 1;
        if (g_unk_010ad280 <= local_2c) {
          return;
        }
      }
    }
  }
  return;
}

void CG_ParseReinforcementTimes(char *param_1)
{
  long tmp_l1;
  char *tmp_pc2;
  char *tmp_pc3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int local_28 [6];
  
  tmp_l1 = strtol(param_1,(char **)0x0,10);
  local_28[1] = tmp_l1 >> 3;
  tmp_pc2 = strchr(param_1,0x20);
  if (tmp_pc2 != (char *)0x0) {
    tmp_pc2 = tmp_pc2 + 1;
    tmp_l1 = strtol(tmp_pc2,(char **)0x0,10);
    if (tmp_l1 < 0) {
      tmp_l1 = tmp_l1 + 3;
    }
    tmp_i5 = 0;
    local_28[0] = tmp_l1 >> 2;
    do {
      tmp_i6 = *(int *)((int)local_28 + tmp_i5);
      if (tmp_i6 == 0) {
        tmp_i6 = 0;
        tmp_pc3 = tmp_pc2;
LAB_000b4470:
        tmp_pc3 = strchr(tmp_pc3,0x20);
        if (tmp_pc3 == (char *)0x0) {
          return;
        }
        tmp_u4 = strtol(tmp_pc3 + 1,(char **)0x0,10);
        *(uint *)(cgs + tmp_i5 + 0x2005438) = (tmp_u4 / (uint)(&aReinfSeeds)[tmp_i6]) * 1000;
      }
      else {
        tmp_pc3 = strchr(tmp_pc2,0x20);
        if (tmp_pc3 == (char *)0x0) {
          return;
        }
        if (tmp_i6 == 1) {
          tmp_i6 = 1;
          tmp_pc3 = tmp_pc3 + 1;
          goto LAB_000b4470;
        }
        tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
        if (tmp_pc3 == (char *)0x0) {
          return;
        }
        if (tmp_i6 == 2) {
          tmp_i6 = 2;
          tmp_pc3 = tmp_pc3 + 1;
          goto LAB_000b4470;
        }
        tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
        if (tmp_pc3 == (char *)0x0) {
          return;
        }
        if (tmp_i6 == 3) {
          tmp_i6 = 3;
          tmp_pc3 = tmp_pc3 + 1;
          goto LAB_000b4470;
        }
        tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
        if (tmp_pc3 == (char *)0x0) {
          return;
        }
        if (tmp_i6 == 4) {
          tmp_i6 = 4;
          tmp_pc3 = tmp_pc3 + 1;
          goto LAB_000b4470;
        }
        tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
        if (tmp_pc3 == (char *)0x0) {
          return;
        }
        if (tmp_i6 == 5) {
          tmp_i6 = 5;
          tmp_pc3 = tmp_pc3 + 1;
          goto LAB_000b4470;
        }
        tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
        if (tmp_pc3 == (char *)0x0) {
          return;
        }
        if (tmp_i6 == 6) {
          tmp_i6 = 6;
          tmp_pc3 = tmp_pc3 + 1;
          goto LAB_000b4470;
        }
        tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
        if (tmp_pc3 == (char *)0x0) {
          return;
        }
        if (tmp_i6 == 7) {
          tmp_i6 = 7;
          tmp_pc3 = tmp_pc3 + 1;
          goto LAB_000b4470;
        }
        tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
        if (tmp_pc3 == (char *)0x0) {
          return;
        }
      }
      tmp_i5 = tmp_i5 + 4;
    } while (tmp_i5 != 8);
  }
  return;
}

uint32_t CG_ParseVoiceChats(uint32_t param_1,int param_2,int param_3)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  byte *tmp_pb7;
  int tmp_i8;
  char *tmp_pc9;
  char *tmp_pc10;
  bool tmp_b11;
  byte tmp_b12;
  int local_8024;
  uint8_t *local_8020;
  uint8_t local_801c [32776];
  uint32_t uStack_14;
  
  tmp_u5 = GHIDRA_FIELD(cg_buildScript, 12, 4);
  tmp_b12 = 0;
  uStack_14 = 0xb4fab;
  tmp_i2 = trap_FS_FOpenFile(param_1,&local_8024,0);
  if (local_8024 == 0) {
    tmp_u5 = va("^1voice chat file not found: %s\n",param_1);
    trap_Print(tmp_u5);
    return 0;
  }
  if (0x7fff < tmp_i2) {
    tmp_u5 = va("^1voice chat file too large: %s is %i, max allowed is %i",param_1,tmp_i2,0x8000);
    trap_Print(tmp_u5);
    trap_FS_FCloseFile(local_8024);
    return 0;
  }
  trap_FS_Read(local_801c,tmp_i2,local_8024);
  local_801c[tmp_i2] = 0;
  trap_FS_FCloseFile(local_8024);
  local_8020 = local_801c;
  Com_sprintf(param_2,0x40,"%s",param_1);
  tmp_pu1 = (uint8_t *)(param_2 + 0x48);
  if (0 < param_3) {
    tmp_pu3 = tmp_pu1;
    do {
      *tmp_pu3 = 0;
      tmp_pu3 = tmp_pu3 + 0x944;
    } while (tmp_pu3 != tmp_pu1 + param_3 * 0x944);
  }
  tmp_pc4 = (char *)COM_ParseExt(&local_8020,1);
  if ((tmp_pc4 != (char *)0x0) && (tmp_b11 = *tmp_pc4 == '\0', !tmp_b11)) {
    tmp_i2 = 7;
    tmp_pc9 = tmp_pc4;
    tmp_pc10 = "female";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_b11 = *tmp_pc9 == *tmp_pc10;
      tmp_pc9 = tmp_pc9 + (uint)tmp_b12 * -2 + 1;
      tmp_pc10 = tmp_pc10 + (uint)tmp_b12 * -2 + 1;
    } while (tmp_b11);
    if (tmp_b11) {
      *(uint32_t *)(param_2 + 0x40) = 1;
    }
    else {
      tmp_i2 = 5;
      tmp_b11 = false;
      tmp_pc9 = tmp_pc4;
      tmp_pc10 = "male";
      do {
        if (tmp_i2 == 0) break;
        tmp_i2 = tmp_i2 + -1;
        tmp_b11 = *tmp_pc9 == *tmp_pc10;
        tmp_pc9 = tmp_pc9 + (uint)tmp_b12 * -2 + 1;
        tmp_pc10 = tmp_pc10 + (uint)tmp_b12 * -2 + 1;
      } while (tmp_b11);
      if (tmp_b11) {
        *(uint32_t *)(param_2 + 0x40) = 0;
      }
      else {
        tmp_i2 = 7;
        tmp_pc9 = "neuter";
        do {
          if (tmp_i2 == 0) break;
          tmp_i2 = tmp_i2 + -1;
          tmp_b11 = *tmp_pc4 == *tmp_pc9;
          tmp_pc4 = tmp_pc4 + (uint)tmp_b12 * -2 + 1;
          tmp_pc9 = tmp_pc9 + (uint)tmp_b12 * -2 + 1;
        } while (tmp_b11);
        if (!tmp_b11) {
          tmp_u5 = va("^1expected gender not found in voice chat file: %s\n",param_1);
          trap_Print(tmp_u5);
          return 0;
        }
        *(uint32_t *)(param_2 + 0x40) = 2;
      }
    }
    *(uint32_t *)(param_2 + 0x44) = 0;
    while ((tmp_pc4 = (char *)COM_ParseExt(&local_8020,1), tmp_pc4 != (char *)0x0 && (*tmp_pc4 != '\0')
           )) {
      Com_sprintf(tmp_pu1 + *(int *)(param_2 + 0x44) * 0x944,0x40,"%s",tmp_pc4);
      tmp_pc4 = (char *)COM_ParseExt(&local_8020,1);
      if ((*tmp_pc4 != '{') || (tmp_pc4[1] != '\0')) {
        tmp_u5 = va("^1Expected { found %s in voice chat file: %s\n",tmp_pc4,param_1);
        trap_Print(tmp_u5);
        return 0;
      }
      *(uint32_t *)(param_2 + 0x88 + *(int *)(param_2 + 0x44) * 0x944) = 0;
      tmp_i2 = *(int *)(param_2 + 0x88 + *(int *)(param_2 + 0x44) * 0x944);
      do {
        tmp_pc4 = (char *)COM_ParseExt(&local_8020,1);
        if (tmp_pc4 == (char *)0x0) {
          return 1;
        }
        if (*tmp_pc4 == '\0') {
          return 1;
        }
        if ((*tmp_pc4 == '}') && (tmp_pc4[1] == '\0')) {
          tmp_i8 = *(int *)(param_2 + 0x44);
          break;
        }
        tmp_i8 = *(int *)(param_2 + 0x44);
        tmp_u6 = trap_S_RegisterSound(tmp_pc4,tmp_u5 == 0);
        *(uint32_t *)(tmp_pu1 + tmp_i2 * 4 + tmp_i8 * 0x944 + 0x44) = tmp_u6;
        tmp_pc4 = (char *)COM_ParseExt(&local_8020,1);
        if (tmp_pc4 == (char *)0x0) {
          return 1;
        }
        if (*tmp_pc4 == '\0') {
          return 1;
        }
        Com_sprintf(tmp_pu1 + (tmp_i2 + 3) * 0x40 + *(int *)(param_2 + 0x44) * 0x944 + 4,0x40,"%s",
                    tmp_pc4);
        tmp_pb7 = (byte *)COM_ParseExt(&local_8020,0);
        tmp_i8 = 0x7d - (uint)*tmp_pb7;
        if (tmp_i8 == 0) {
          tmp_i8 = -(uint)tmp_pb7[1];
        }
        if ((tmp_i8 == 0) || (*tmp_pb7 == 0)) {
          tmp_i8 = *(int *)(param_2 + 0x44);
          tmp_u6 = trap_R_RegisterShader("sprites/voiceChat");
          *(uint32_t *)(tmp_pu1 + tmp_i2 * 4 + tmp_i8 * 0x944 + 0x8c4) = tmp_u6;
          COM_RestoreParseSession(&local_8020);
          tmp_pu3 = tmp_pu1 + *(int *)(param_2 + 0x44) * 0x944;
        }
        else {
          tmp_i8 = *(int *)(param_2 + 0x44);
          tmp_u6 = trap_R_RegisterShader(tmp_pb7);
          *(uint32_t *)(tmp_pu1 + tmp_i2 * 4 + tmp_i8 * 0x944 + 0x8c4) = tmp_u6;
          tmp_pu3 = tmp_pu1 + *(int *)(param_2 + 0x44) * 0x944;
          if (*(int *)(tmp_pu3 + tmp_i2 * 4 + 0x8c4) == 0) {
            tmp_u6 = trap_R_RegisterShader("sprites/voiceChat");
            *(uint32_t *)(tmp_pu3 + tmp_i2 * 4 + 0x8c4) = tmp_u6;
            tmp_pu3 = tmp_pu1 + *(int *)(param_2 + 0x44) * 0x944;
          }
        }
        *(int *)(tmp_pu3 + 0x40) = *(int *)(tmp_pu3 + 0x40) + 1;
        tmp_i8 = *(int *)(param_2 + 0x44);
        tmp_i2 = *(int *)(param_2 + 0x88 + tmp_i8 * 0x944);
      } while (tmp_i2 < 0x20);
      *(int *)(param_2 + 0x44) = tmp_i8 + 1;
      if (param_3 <= tmp_i8 + 1) {
        return 1;
      }
    }
  }
  return 1;
}

void CG_ParseWarmup(void)
{
  char *__nptr;
  long tmp_l1;
  uint32_t tmp_u2;
  
  __nptr = (char *)CG_ConfigString(5);
  tmp_l1 = strtol(__nptr,(char **)0x0,10);
  if (tmp_l1 < 1) {
LAB_000b664a:
    if ((GHIDRA_FIELD(cgs, 33525356, 4) == 2) && (g_unk_010aac20 < 1)) goto LAB_000b65a7;
  }
  else if (g_unk_010aac20 < 1) {
    if (GHIDRA_FIELD(cgs, 33525356, 4) == 2) goto LAB_000b65a7;
    if ((g_unk_01047aec == 0) && ((cg_autoAction[0xc] & 1) != 0)) {
      CG_autoRecord_f();
      if (g_unk_010aac24 < 0) goto LAB_000b664a;
    }
    else if (g_unk_010aac24 < 0) goto LAB_000b65a1;
    tmp_u2 = CG_LocalizeServerCommand("^3All players ready!^7\nMatch starting...\n");
    CG_Printf("[cgnotify]%s",tmp_u2);
    tmp_u2 = CG_LocalizeServerCommand("^3All players ready!^7\nMatch starting...");
    CG_CenterPrint(tmp_u2,0x180,8);
    goto LAB_000b664a;
  }
LAB_000b65a1:
  g_unk_010aac20 = tmp_l1;
LAB_000b65a7:
  g_unk_010aac24 = g_unk_010aac24 + 1;
  return;
}

void CG_ParseWolfinfo(void)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  uint tmp_u3;
  uint32_t tmp_u4;
  double tmp_d5;
  uint32_t local_820;
  uint32_t local_81c;
  uint32_t local_818 [255];
  char local_41c [4];
  uint32_t local_418 [257];
  uint32_t uStack_14;
  
  tmp_u1 = GHIDRA_FIELD(cgs, 33525356, 4);
  uStack_14 = 0xb66bb;
  local_81c = 0;
  tmp_u2 = 0;
  do {
    tmp_u3 = tmp_u2;
    *(uint32_t *)((int)local_818 + tmp_u3) = 0;
    *(uint32_t *)((int)local_818 + tmp_u3 + 4) = 0;
    tmp_u2 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0x3f8);
  *(uint32_t *)((int)local_818 + tmp_u3 + 8) = 0;
  local_41c[0] = '\0';
  local_41c[1] = '\0';
  local_41c[2] = '\0';
  local_41c[3] = '\0';
  tmp_u2 = 0;
  do {
    tmp_u3 = tmp_u2;
    *(uint32_t *)((int)local_418 + tmp_u3) = 0;
    *(uint32_t *)((int)local_418 + tmp_u3 + 4) = 0;
    tmp_u2 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0x3f8);
  *(uint32_t *)((int)local_418 + tmp_u3 + 8) = 0;
  local_820 = CG_ConfigString(0x15);
  while( true ) {
    Info_NextPair(&local_820,&local_81c,local_41c);
    if ((char)local_81c == '\0') break;
    tmp_u4 = nitrox_GetTokenForString(&local_81c);
    switch(tmp_u4) {
    case 0x7e:
      GHIDRA_FIELD(cgs, 33525344, 4) = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x7f:
      tmp_d5 = strtod(local_41c,(char **)0x0);
      GHIDRA_FIELD(cgs, 33525348, 4) = (uint32_t)tmp_d5;
      break;
    case 0x80:
      GHIDRA_FIELD(cgs, 33525356, 4) = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x81:
      Q_strncpyz(0x30e8cd0,local_41c,0x100);
      break;
    case 0x82:
      GHIDRA_FIELD(cgs, 33525616, 4) = strtol(local_41c,(char **)0x0,10);
    }
  }
  if (tmp_u1 == 0) {
    if (GHIDRA_FIELD(cgs, 27384, 4) != 0) goto LAB_000b68b3;
LAB_000b68e0:
    tmp_u4 = va("%i",GHIDRA_FIELD(cgs, 33525356, 4));
    trap_Cvar_Set("gamestate",tmp_u4);
  }
  else {
    if (((GHIDRA_FIELD(cgs, 33525356, 4) == 0) &&
        (CG_AddAnnouncer("FIGHT!",GHIDRA_FIELD(cgs, 68912, 4),0x3f8ccccd,1000,0x3f800000,0,0,1,0),
        (cg_autoAction[0xc] & 1) != 0)) && (g_unk_01047aec == 0)) {
      CG_autoRecord_f();
    }
    if (GHIDRA_FIELD(cgs, 27384, 4) == 0) goto LAB_000b68e0;
  }
  if (tmp_u1 == 1) {
    return;
  }
LAB_000b68b3:
  if (GHIDRA_FIELD(cgs, 33525356, 4) != 1) {
    return;
  }
  CG_ParseWarmup();
  return;
}

void CG_ParseWeaponStats(void)
{
  char *tmp_pc1;
  
  tmp_pc1 = (char *)CG_Argv(1);
  GHIDRA_FIELD(cgs, 33685928, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(2);
  GHIDRA_FIELD(cgs, 33685932, 4) = strtol(tmp_pc1,(char **)0x0,10);
  return;
}

void CG_ParsePortalPos(void)
{
  char *tmp_pc1;
  long tmp_l2;
  int tmp_i3;
  
  tmp_pc1 = (char *)CG_Argv(1);
  tmp_i3 = 2;
  GHIDRA_FIELD(cgs, 33685968, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(8);
  GHIDRA_FIELD(cgs, 33685960, 4) = strtol(tmp_pc1,(char **)0x0,10);
  do {
    tmp_pc1 = (char *)CG_Argv(tmp_i3);
    tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
    *(float *)(cgs + tmp_i3 * 4 + 0x20201a8) = (float)tmp_l2;
    tmp_i3 = tmp_i3 + 1;
  } while (tmp_i3 != 5);
  do {
    tmp_pc1 = (char *)CG_Argv(tmp_i3);
    tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
    *(float *)(cgs + tmp_i3 * 4 + 0x20201a8) = (float)tmp_l2;
    tmp_i3 = tmp_i3 + 1;
  } while (tmp_i3 != 8);
  return;
}

void CG_ServerCommand(void)
{
  int tmp_i1;
  char tmp_c2;
  uint tmp_u3;
  char *tmp_pc4;
  int tmp_i5;
  long tmp_l6;
  uint tmp_u7;
  uint32_t tmp_u8;
  long tmp_l9;
  char *tmp_pc10;
  uint32_t tmp_u11;
  uint32_t tmp_u12;
  int tmp_i13;
  long *plVar14;
  int tmp_i15;
  char *tmp_pc16;
  uint32_t *tmp_pu17;
  bool tmp_b18;
  byte tmp_b19;
  double tmp_d20;
  double tmp_d21;
  double tmp_d22;
  double tmp_d23;
  double tmp_d24;
  double tmp_d25;
  int local_55c;
  float local_524;
  float local_520;
  float local_51c;
  float local_518;
  float local_514;
  uint32_t local_41c;
  uint32_t local_418 [258];
  
  tmp_b19 = 0;
  tmp_pc4 = (char *)CG_Argv(0);
  if (*tmp_pc4 == '\0') {
    return;
  }
  tmp_c2 = *tmp_pc4;
  if ((((tmp_c2 == 'c') && (tmp_pc4[1] == 'v')) && (tmp_pc4[2] == 's')) && (tmp_pc4[3] == '\0')) {
    local_41c = 0;
    tmp_u3 = 0;
    do {
      tmp_u7 = tmp_u3;
      *(uint32_t *)((int)local_418 + tmp_u7) = 0;
      *(uint32_t *)((int)local_418 + tmp_u7 + 4) = 0;
      tmp_u3 = tmp_u7 + 8;
    } while (tmp_u7 + 8 < 0xf8);
    *(uint32_t *)((int)local_418 + tmp_u7 + 8) = 0;
    tmp_pc4 = (char *)CG_Argv(1);
    tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
    tmp_u8 = CG_Argv(2);
    trap_Cvar_VariableStringBuffer(tmp_u8,&local_41c,0x100);
    tmp_u8 = va("cvs %i %s \"%s\"\n",tmp_l6,tmp_u8,&local_41c);
    trap_SendClientCommand(tmp_u8);
    return;
  }
  tmp_b18 = false;
  tmp_i13 = 10;
  tmp_pc10 = tmp_pc4;
  tmp_pc16 = "handshake";
  do {
    if (tmp_i13 == 0) break;
    tmp_i13 = tmp_i13 + -1;
    tmp_b18 = *tmp_pc10 == *tmp_pc16;
    tmp_pc10 = tmp_pc10 + (uint)tmp_b19 * -2 + 1;
    tmp_pc16 = tmp_pc16 + (uint)tmp_b19 * -2 + 1;
  } while (tmp_b18);
  if (tmp_b18) {
    trap_SendClientCommand(&g_unk_0011dad8);
    trap_SendClientCommand("handshake");
    trap_SendClientCommand("getdata");
    return;
  }
  tmp_i13 = 6;
  tmp_b18 = false;
  tmp_pc10 = tmp_pc4;
  tmp_pc16 = "getss";
  do {
    if (tmp_i13 == 0) break;
    tmp_i13 = tmp_i13 + -1;
    tmp_b18 = *tmp_pc10 == *tmp_pc16;
    tmp_pc10 = tmp_pc10 + (uint)tmp_b19 * -2 + 1;
    tmp_pc16 = tmp_pc16 + (uint)tmp_b19 * -2 + 1;
  } while (tmp_b18);
  if (tmp_b18) {
    tmp_pc4 = (char *)CG_Argv(1);
    GHIDRA_FIELD(cgs, 33823056, 4) = strtol(tmp_pc4,(char **)0x0,10);
    nitrox_FreeScreenshot();
    GHIDRA_FIELD(cgs, 33822776, 4) = 1;
    GHIDRA_FIELD(cgs, 33822780, 4) = g_unk_010906e0 + 100;
    return;
  }
  if ((tmp_c2 == 'f') && (tmp_pc4[1] == 't')) {
    if ((tmp_pc4[2] == 'a') && (tmp_pc4[3] == '\0')) {
      GHIDRA_FIELD(cgs, 33822776, 4) = 5;
      GHIDRA_FIELD(cgs, 33822780, 4) = g_unk_010906e0 + 100;
      return;
    }
    if ((tmp_pc4[2] == 'c') && (tmp_pc4[3] == '\0')) {
      GHIDRA_FIELD(cgs, 33822776, 4) = 7;
      GHIDRA_FIELD(cgs, 33822780, 4) = g_unk_010906e0 + 100;
      return;
    }
  }
  tmp_b18 = false;
  tmp_i13 = 6;
  tmp_pc10 = tmp_pc4;
  tmp_pc16 = "tinfo";
  do {
    if (tmp_i13 == 0) break;
    tmp_i13 = tmp_i13 + -1;
    tmp_b18 = *tmp_pc10 == *tmp_pc16;
    tmp_pc10 = tmp_pc10 + (uint)tmp_b19 * -2 + 1;
    tmp_pc16 = tmp_pc16 + (uint)tmp_b19 * -2 + 1;
  } while (tmp_b18);
  if (tmp_b18) {
    tmp_pc4 = (char *)CG_Argv(1);
    tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
    if (tmp_l6 < 1) {
      return;
    }
    tmp_i13 = 2;
    do {
      tmp_pc4 = (char *)CG_Argv(tmp_i13);
      tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
      tmp_i5 = tmp_l9 * 0x1a4;
      tmp_pc4 = (char *)CG_Argv(tmp_i13 + 1);
      tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
      *(long *)(cgs + tmp_i5 + 0x949c) = tmp_l9;
      tmp_pc4 = (char *)CG_Argv(tmp_i13 + 2);
      tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
      *(long *)(cgs + tmp_i5 + 0x94a0) = tmp_l9;
      tmp_pc4 = (char *)CG_Argv(tmp_i13 + 3);
      tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
      *(long *)(cgs + tmp_i5 + 0x94a4) = tmp_l9;
      tmp_pc4 = (char *)CG_Argv(tmp_i13 + 4);
      tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
      *(long *)(cgs + tmp_i5 + 0x94a8) = tmp_l9;
      tmp_i15 = tmp_i13 + 5;
      tmp_i13 = tmp_i13 + 6;
      tmp_pc4 = (char *)CG_Argv(tmp_i15);
      tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
      *(long *)(cgs + tmp_i5 + 0x94b0) = tmp_l9;
    } while (tmp_i13 != tmp_l6 * 6 + 2);
    return;
  }
  if (tmp_c2 == 's') {
    if (tmp_pc4[1] == 'c') {
      if ((tmp_pc4[2] == '0') && (tmp_pc4[3] == '\0')) {
        CG_ParseScore(1);
        return;
      }
      if ((tmp_pc4[2] == '1') && (tmp_pc4[3] == '\0')) {
        CG_ParseScore(2);
        return;
      }
    }
  }
  else if (tmp_c2 == 'k') {
    if (tmp_pc4[1] == 'd') {
      if ((tmp_pc4[2] == '0') && (tmp_pc4[3] == '\0')) {
        CG_ParseKD(1);
        return;
      }
      if ((tmp_pc4[2] == '1') && (tmp_pc4[3] == '\0')) {
        CG_ParseKD(2);
        return;
      }
    }
  }
  else if (tmp_c2 == 'z') {
    if ((tmp_pc4[1] == '1') && (tmp_pc4[2] == '\0')) {
      tmp_pc4 = (char *)CG_Argv(1);
      GHIDRA_FIELD(cgs, 33787492, 4) = strtol(tmp_pc4,(char **)0x0,10);
      return;
    }
  }
  else if (((tmp_c2 == 'D') && (tmp_pc4[1] == 'M')) && (tmp_pc4[2] == '\0')) {
    tmp_pc4 = (char *)CG_Argv(1);
    GHIDRA_FIELD(cgs, 33787764, 4) = strtol(tmp_pc4,(char **)0x0,10);
    return;
  }
  tmp_i13 = Q_stricmp(tmp_pc4,"WeaponStats");
  if (tmp_i13 == 0) {
    tmp_i13 = 1;
    plVar14 = (long *)(cgs + 0x1ff8f7c);
    tmp_i15 = 0;
    do {
      tmp_i5 = BG_ValidStatWeapon(tmp_i15);
      if (tmp_i5 != 0) {
        tmp_pc4 = (char *)CG_Argv(tmp_i13);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        tmp_i5 = tmp_i13 + 2;
        *plVar14 = tmp_l6;
        tmp_i1 = tmp_i13 + 1;
        tmp_i13 = tmp_i13 + 3;
        tmp_pc4 = (char *)CG_Argv(tmp_i1);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        plVar14[2] = tmp_l6;
        tmp_pc4 = (char *)CG_Argv(tmp_i5);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        plVar14[1] = tmp_l6;
      }
      tmp_i15 = tmp_i15 + 1;
      plVar14 = plVar14 + 3;
    } while (tmp_i15 != 0x34);
    tmp_pc4 = (char *)CG_Argv(tmp_i13);
    GHIDRA_FIELD(cgs, 33526252, 4) = strtol(tmp_pc4,(char **)0x0,10);
    tmp_pc4 = (char *)CG_Argv(tmp_i13 + 1);
    GHIDRA_FIELD(cgs, 33526288, 4) = strtol(tmp_pc4,(char **)0x0,10);
    if ((int)GHIDRA_FIELD(cgs, 33526288, 4) < 1) {
      return;
    }
    tmp_i15 = 0;
    plVar14 = (long *)(cgs + 0x1ff91f0);
    do {
      tmp_i15 = tmp_i15 + 1;
      tmp_pc4 = (char *)CG_Argv(tmp_i13 + 2);
      tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
      *plVar14 = tmp_l6;
      tmp_pc4 = (char *)CG_Argv(tmp_i13 + 3);
      tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
      plVar14[9] = tmp_l6;
      plVar14 = plVar14 + 1;
      tmp_i13 = tmp_i13 + 2;
    } while (tmp_i15 < (int)GHIDRA_FIELD(cgs, 33526288, 4));
    return;
  }
  tmp_c2 = *tmp_pc4;
  if ((((tmp_c2 == 'c') && (tmp_pc4[1] == 'p')) && (tmp_pc4[2] == 'm')) && (tmp_pc4[3] == '\0')) {
LAB_000b9594:
    tmp_u8 = CG_Argv(1);
    tmp_u8 = CG_LocalizeServerCommand(tmp_u8);
    CG_AddPMItem(4,tmp_u8,GHIDRA_FIELD(cgs, 67984, 4),0);
    return;
  }
  tmp_b18 = false;
  tmp_i13 = 8;
  tmp_pc10 = tmp_pc4;
  tmp_pc16 = "cpm_map";
  do {
    if (tmp_i13 == 0) break;
    tmp_i13 = tmp_i13 + -1;
    tmp_b18 = *tmp_pc10 == *tmp_pc16;
    tmp_pc10 = tmp_pc10 + (uint)tmp_b19 * -2 + 1;
    tmp_pc16 = tmp_pc16 + (uint)tmp_b19 * -2 + 1;
  } while (tmp_b18);
  if (tmp_b18) goto LAB_000b9594;
  tmp_i13 = strcmp(tmp_pc4,"announce");
  if (tmp_i13 == 0) {
    tmp_i13 = trap_Argc();
    if (tmp_i13 < 3) {
      tmp_u8 = CG_Argv(1);
      tmp_u8 = CG_LocalizeServerCommand(tmp_u8);
      CG_CenterPrint(tmp_u8,0x180,8);
      return;
    }
    tmp_u8 = CG_Argv(1);
    tmp_u8 = va("%s",tmp_u8);
    if (tmp_i13 == 4) {
      tmp_u11 = CG_Argv(3);
      tmp_u8 = va("%s%s",tmp_u11,tmp_u8);
      if ((int)GHIDRA_FIELD(cg_printObjectiveInfo, 12, 4) < 1) goto LAB_000b984c;
    }
    else {
      if ((int)GHIDRA_FIELD(cg_printObjectiveInfo, 12, 4) < 1) goto LAB_000b984c;
      tmp_pc4 = (char *)CG_Argv(2);
      tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
      if (tmp_l6 < 2) goto LAB_000b984c;
    }
    tmp_u11 = CG_Argv(1);
    tmp_u11 = CG_LocalizeServerCommand(tmp_u11);
    CG_Printf("[cgnotify]*** ^3ANNOUNCEMENT: ^5%s\n",tmp_u11);
LAB_000b984c:
    tmp_pc4 = (char *)CG_Argv(2);
    tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
    CG_PrintAnnouncement(tmp_u8,200,8,tmp_l6);
    return;
  }
  if ((tmp_c2 == 'a') && (tmp_pc4[1] == 'n')) {
    if (tmp_pc4[2] == '\0') {
      tmp_pc4 = (char *)CG_Argv(1);
      tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
      switch(tmp_l6) {
      case 0:
        CG_AddAnnouncer("FIGHT!",GHIDRA_FIELD(cgs, 68912, 4),0x3f8ccccd,1000,0x3f800000,0,0,1,0);
        return;
      case 1:
        tmp_pc4 = (char *)CG_Argv(2);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        nitrox_AddSpecialPrint("KILL ASSISTANCE!",0x3f800000,0x3f800000,0x3f800000,0x5a,tmp_l6);
        return;
      case 2:
        tmp_pc4 = (char *)CG_Argv(2);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        nitrox_AddSpecialPrint("SUICIDE HELPER!",0x3f800000,0x3f800000,0x3f800000,0x5a,tmp_l6);
        return;
      case 3:
        tmp_pc4 = (char *)CG_Argv(2);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        nitrox_AddSpecialPrint("TEAMKILL ASSISTANCE!",0x3f800000,0,0,0x5a,tmp_l6);
        return;
      case 4:
        tmp_pc4 = (char *)CG_Argv(2);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        nitrox_AddSpecialPrint("FIRST BLOOD!",0x3f800000,0,0,0x5a,tmp_l6);
        return;
      case 5:
        tmp_pc4 = (char *)CG_Argv(2);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        nitrox_AddSpecialPrint("FIRST HEADSHOT!",0x3f800000,0,0,0x5a,tmp_l6);
        return;
      case -2:
        tmp_pc4 = (char *)CG_Argv(2);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        nitrox_AddSpecialPrint("REVENGE!",0x3f800000,0,0,0x5a,tmp_l6);
        return;
      case -1:
        CG_AddAnnouncer("PREPARE TO FIGHT!",GHIDRA_FIELD(cgs, 68908, 4),0x3f59999a,1000,0x3f800000,0x3f800000,0,1,
                        0);
        return;
      default:
        return;
      }
    }
LAB_000b9724:
    if (((tmp_c2 == 'b') && (tmp_pc4[1] == 'p')) && (tmp_pc4[2] == '\0')) {
      if (GHIDRA_FIELD(cg_drawBanners, 12, 4) == 0) {
        return;
      }
      tmp_pc4 = (char *)CG_Argv(1);
      tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
      if (tmp_l6 == 1) {
        tmp_u8 = CG_Argv(2);
        tmp_u8 = CG_LocalizeServerCommand(tmp_u8);
        CG_Printf(&g_unk_00121ff9,tmp_u8);
        return;
      }
      if (tmp_l6 == 2) {
        tmp_u8 = CG_Argv(2);
        tmp_u8 = CG_LocalizeServerCommand(tmp_u8);
        CG_BannerPrint(tmp_u8);
        return;
      }
      if (tmp_l6 != 0) {
        return;
      }
      tmp_u8 = CG_Argv(2);
      tmp_u8 = CG_LocalizeServerCommand(tmp_u8);
      CG_AddToTeamChat(tmp_u8,0xffffffff);
      return;
    }
  }
  else {
    if (tmp_c2 != 'c') goto LAB_000b9724;
    if ((tmp_pc4[1] == 'p') && (tmp_pc4[2] == '\0')) {
      tmp_i13 = trap_Argc();
      if (tmp_i13 < 3) {
        tmp_u8 = CG_Argv(1);
        tmp_u8 = CG_LocalizeServerCommand(tmp_u8);
        CG_CenterPrint(tmp_u8,0x180,8);
        return;
      }
      tmp_u8 = CG_Argv(1);
      tmp_u8 = va("%s",tmp_u8);
      if (tmp_i13 == 4) {
        tmp_u11 = CG_Argv(3);
        tmp_u8 = va("%s%s",tmp_u11,tmp_u8);
        if ((int)GHIDRA_FIELD(cg_printObjectiveInfo, 12, 4) < 1) goto LAB_000b9707;
      }
      else {
        if ((int)GHIDRA_FIELD(cg_printObjectiveInfo, 12, 4) < 1) goto LAB_000b9707;
        tmp_pc4 = (char *)CG_Argv(2);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        if (tmp_l6 < 2) goto LAB_000b9707;
      }
      tmp_u11 = CG_Argv(1);
      tmp_u11 = CG_LocalizeServerCommand(tmp_u11);
      CG_Printf("[cgnotify]*** ^3INFO: ^5%s\n",tmp_u11);
LAB_000b9707:
      CG_CenterPrint(tmp_u8,0x180,8);
      return;
    }
  }
  tmp_i13 = strcmp(tmp_pc4,"reqforcespawn");
  if (tmp_i13 == 0) {
    if (GHIDRA_FIELD(cg_instanttapout, 12, 4) != 0) {
      CG_ForceTapOut_f();
      return;
    }
    if (GHIDRA_FIELD(cgs, 27388, 4) != 5) {
      trap_UI_Popup(0xc);
      return;
    }
    trap_UI_Popup(0xd);
    return;
  }
  tmp_i13 = strcmp(tmp_pc4,"sdbg");
  if (tmp_i13 == 0) {
    tmp_u8 = CG_Argv(1);
    CG_StatsDebugAddText(tmp_u8);
    return;
  }
  if ((tmp_c2 == 'c') && (tmp_pc4[1] == 's')) {
    if (tmp_pc4[2] == '\0') {
      tmp_pc4 = (char *)CG_Argv(1);
      tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
      trap_GetGameState(cgs);
      tmp_pc4 = (char *)CG_ConfigString(tmp_l6);
      switch(tmp_l6) {
      case 0:
        CG_ParseServerinfo(tmp_pc4);
        return;
      case 2:
        CG_StartMusic();
        return;
      case 5:
        CG_ParseWarmup();
        return;
      case 6:
        GHIDRA_FIELD(cgs, 27664, 4) = strtol(tmp_pc4,(char **)0x0,10);
        GHIDRA_FIELD(cgs, 27676, 4) = 1;
        return;
      case 7:
        Q_strncpyz(0x10f6a80,tmp_pc4,0x100);
        return;
      case 8:
        GHIDRA_FIELD(cgs, 27668, 4) = strtol(tmp_pc4,(char **)0x0,10);
        GHIDRA_FIELD(cgs, 27676, 4) = 1;
        return;
      case 9:
        GHIDRA_FIELD(cgs, 27672, 4) = strtol(tmp_pc4,(char **)0x0,10);
        GHIDRA_FIELD(cgs, 27676, 4) = 1;
        return;
      case 0xb:
        GHIDRA_FIELD(cgs, 28480, 4) = strtol(tmp_pc4,(char **)0x0,10);
        return;
      case 0xc:
        g_unk_01047af4 = strtol(tmp_pc4,(char **)0x0,10);
        return;
      case 0xf:
      case 0x23:
        return;
      case 0x12:
        local_41c = CG_ConfigString(0x12);
        tmp_pc4 = (char *)COM_Parse(&local_41c);
        tmp_d20 = strtod(tmp_pc4,(char **)0x0);
        tmp_pc4 = (char *)COM_Parse(&local_41c);
        tmp_d21 = strtod(tmp_pc4,(char **)0x0);
        tmp_pc4 = (char *)COM_Parse(&local_41c);
        tmp_d22 = strtod(tmp_pc4,(char **)0x0);
        tmp_pc4 = (char *)COM_Parse(&local_41c);
        tmp_d23 = strtod(tmp_pc4,(char **)0x0);
        tmp_pc4 = (char *)COM_Parse(&local_41c);
        tmp_d24 = strtod(tmp_pc4,(char **)0x0);
        tmp_pc4 = (char *)COM_Parse(&local_41c);
        tmp_d25 = strtod(tmp_pc4,(char **)0x0);
        tmp_pc4 = (char *)COM_Parse(&local_41c);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        if ((float)tmp_d21 == 0.0) {
          trap_R_SetFog(10,4,tmp_l6,0,0,0,0);
          return;
        }
        trap_R_SetFog(6,(int)ROUND((float)tmp_d20),(int)ROUND((float)tmp_d21),(float)tmp_d23,
                      (float)tmp_d24,(float)tmp_d25,(float)tmp_d22 + 0.1);
        trap_R_SetFog(10,6,tmp_l6,0,0,0,0);
        return;
      case 0x13:
        CG_ParseSkyBox();
        return;
      case 0x15:
        CG_ParseWolfinfo();
        return;
      case 0x16:
        g_unk_010aabec = strtol(tmp_pc4,(char **)0x0,10);
        return;
      case 0x17:
        g_unk_010aabf4 = strtol(tmp_pc4,(char **)0x0,10);
        return;
      case 0x18:
        g_unk_010aabf0 = strtol(tmp_pc4,(char **)0x0,10);
        return;
      case 0x19:
        CG_QueueMusic();
        return;
      case 0x1c:
        CG_ParseReinforcementTimes(tmp_pc4);
        return;
      case 0x1e:
        local_41c = CG_ConfigString(0x1e);
        tmp_pc4 = (char *)COM_Parse(&local_41c);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        tmp_pc4 = (char *)COM_Parse(&local_41c);
        tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
        if (tmp_l6 == 0) {
          tmp_pc4 = (char *)COM_Parse(&local_41c);
          tmp_d20 = strtod(tmp_pc4,(char **)0x0);
          tmp_pc4 = (char *)COM_Parse(&local_41c);
          tmp_d21 = strtod(tmp_pc4,(char **)0x0);
          tmp_pc4 = (char *)COM_Parse(&local_41c);
          tmp_d22 = strtod(tmp_pc4,(char **)0x0);
          tmp_pc4 = (char *)COM_Parse(&local_41c);
          tmp_d23 = strtod(tmp_pc4,(char **)0x0);
          trap_R_SetGlobalFog(0,tmp_l9,(float)tmp_d20,(float)tmp_d21,(float)tmp_d22,(float)tmp_d23);
          return;
        }
        trap_R_SetGlobalFog(1,tmp_l9,0,0,0,0);
        return;
      case 0x1f:
      case 0x20:
        CG_ParseTeamXPs(tmp_l6 + -0x1f);
        return;
      case 0x21:
        GHIDRA_FIELD(cgs, 28484, 4) = strtol(tmp_pc4,(char **)0x0,10);
        return;
      case 0x24:
        CG_ParseInfo();
        return;
      case 0x26:
        CG_UpdateSvCvars();
        return;
      case 0x27:
        CG_UpdateClassesMaxHP();
        return;
      }
      if (0x3f < tmp_l6 - 0x2b1U) {
        if (0x3f < tmp_l6 - 0x309U) {
          return;
        }
        CG_ParseTagConnect(tmp_l6);
        return;
      }
      CG_NewClientInfo(tmp_l6 - 0x2b1U,tmp_pc4);
      return;
    }
LAB_000b9973:
    tmp_i13 = strcmp(tmp_pc4,"popaw");
    if (tmp_i13 == 0) {
LAB_000bb029:
      g_unk_010ef260 = 1;
      g_unk_010ef25c = g_unk_010906e0;
      tmp_pc4 = (char *)CG_Argv(1);
      g_unk_010ef24c = strtol(tmp_pc4,(char **)0x0,10);
      tmp_pc4 = (char *)CG_Argv(2);
      g_unk_010ef250 = strtol(tmp_pc4,(char **)0x0,10);
      g_unk_010ef254 = 0;
      g_unk_010ef258 = 2;
      return;
    }
    if ((((tmp_c2 == 'p') && (tmp_pc4[1] == 'o')) && (tmp_pc4[2] == 'p')) && (tmp_pc4[3] == '\0')) {
      if (g_unk_010ef258 != 2) {
        g_unk_010ef260 = 1;
        g_unk_010ef258 = 1;
        g_unk_010ef25c = g_unk_010906e0;
      }
      tmp_u8 = CG_Argv(1);
      tmp_u8 = CG_LocalizeServerCommand(tmp_u8);
      Q_strncpyz(&g_unk_010ef264,tmp_u8,0x400);
      CG_Printf("%s^7\n",&g_unk_010ef264);
      return;
    }
  }
  else {
    if (tmp_c2 != 'n') goto LAB_000b9973;
    if (((tmp_pc4[1] == 'c') && (tmp_pc4[2] == 's')) && (tmp_pc4[3] == '\0')) {
      tmp_pc4 = (char *)CG_Argv(1);
      tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
      nitrox_ConfigStringModified();
      nitrox_ProcessNewCS(tmp_l6);
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"popaw");
    if (tmp_i13 == 0) goto LAB_000bb029;
  }
  tmp_i13 = strcmp(tmp_pc4,"glstats");
  if (tmp_i13 == 0) {
    tmp_pu17 = &g_unk_010ef204;
    for (tmp_i13 = 0x10; tmp_i13 != 0; tmp_i13 = tmp_i13 + -1) {
      *tmp_pu17 = 0;
      tmp_pu17 = tmp_pu17 + (uint)tmp_b19 * -2 + 1;
    }
    g_unk_010ef200 = 0;
    tmp_u8 = CG_Argv(2);
    tmp_i13 = Q_stricmp(tmp_u8,&g_unk_0011db92);
    if (tmp_i13 == 0) {
      g_unk_010ef1f8 = g_unk_010906e0 + 5000;
      g_unk_010ef200 = 1;
      g_unk_010ef204 = 0xffffffff;
      return;
    }
    tmp_i13 = 1;
    do {
      tmp_i13 = tmp_i13 + 1;
      tmp_pc4 = (char *)CG_Argv(tmp_i13);
      tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
      (&g_unk_010ef1fc)[tmp_i13] = tmp_l6;
    } while (tmp_i13 != 0x10);
    g_unk_010ef200 = 1;
    return;
  }
  tmp_i13 = strcmp(tmp_pc4,"print");
  if (tmp_i13 == 0) {
    tmp_u8 = CG_Argv(1);
    tmp_u8 = CG_LocalizeServerCommand(tmp_u8);
    Q_strncpyz(&local_41c,tmp_u8,0x400);
    unescape_string(&local_41c);
    CG_Printf("%s",&local_41c);
    return;
  }
  tmp_i13 = strcmp(tmp_pc4,"entnfo");
  if (tmp_i13 == 0) {
    trap_Argv(1,&local_41c,0x10);
    tmp_l6 = strtol((char *)&local_41c,(char **)0x0,10);
    trap_Argv(2,&local_41c,0x10);
    tmp_l9 = strtol((char *)&local_41c,(char **)0x0,10);
    CG_ParseMapEntityInfo(tmp_l6,tmp_l9);
    return;
  }
  tmp_i13 = strcmp(tmp_pc4,"chat");
  if (tmp_i13 == 0) {
    if (GHIDRA_FIELD(cg_teamChatsOnly, 12, 4) != 0) {
      return;
    }
    tmp_pc4 = (char *)CG_Argv(3);
    tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
    if (tmp_l6 == 0) {
      tmp_u8 = CG_Argv(1);
    }
    else {
      tmp_u8 = CG_Argv(1);
      tmp_u8 = CG_LocalizeServerCommand(tmp_u8);
    }
    unescape_string(tmp_u8);
    Q_strncpyz(&local_41c,tmp_u8,0x96);
    tmp_i13 = 0;
    for (tmp_pc4 = (char *)&local_41c; tmp_c2 = *tmp_pc4, tmp_c2 != '\0'; tmp_pc4 = tmp_pc4 + 1) {
      if (tmp_c2 != '\x19') {
        *(char *)((int)&local_41c + tmp_i13) = tmp_c2;
        tmp_i13 = tmp_i13 + 1;
      }
    }
    *(uint8_t *)((int)&local_41c + tmp_i13) = 0;
    tmp_pc4 = (char *)CG_Argv(2);
    tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
    CG_AddToTeamChat(&local_41c,tmp_l6);
    CG_Printf(&g_unk_00121ff9,&local_41c);
    if (GHIDRA_FIELD(cg_clientLog, 12, 4) == 0) {
      return;
    }
    CG_WriteToLog(&g_unk_00121ff9,&local_41c);
    return;
  }
  if (((tmp_c2 == 'l') && (tmp_pc4[1] == 'c')) && (tmp_pc4[2] == '\0')) {
    tmp_u8 = CG_Argv(1);
    tmp_i13 = -1;
    tmp_pc4 = cg_pmColor + 0x10;
    do {
      if (tmp_i13 == 0) break;
      tmp_i13 = tmp_i13 + -1;
      tmp_c2 = *tmp_pc4;
      tmp_pc4 = tmp_pc4 + (uint)tmp_b19 * -2 + 1;
    } while (tmp_c2 != '\0');
    if (tmp_i13 == -3) {
      tmp_u11 = va(&g_unk_0011db9c,0xfbcd70);
      Q_strncpyz(&local_41c,tmp_u11,0x100);
    }
    else {
      Q_strncpyz(&local_41c,"^7",0x100);
    }
    Q_strcat(&local_41c,0x100,tmp_u8);
    tmp_i13 = 0;
    for (tmp_pc4 = (char *)&local_41c; tmp_c2 = *tmp_pc4, tmp_c2 != '\0'; tmp_pc4 = tmp_pc4 + 1) {
      if (tmp_c2 != '\x19') {
        *(char *)((int)&local_41c + tmp_i13) = tmp_c2;
        tmp_i13 = tmp_i13 + 1;
      }
    }
    *(uint8_t *)((int)&local_41c + tmp_i13) = 0;
    CG_AddToTeamChat(&local_41c,0xfffffffe);
    CG_Printf("^7%s\n",&local_41c);
    if (GHIDRA_FIELD(cg_clientLog, 12, 4) == 0) {
      return;
    }
    CG_WriteToLog(&g_unk_00121ff9,&local_41c);
    return;
  }
  tmp_i13 = strcmp(tmp_pc4,"tchat");
  if (tmp_i13 == 0) {
    tmp_pc4 = (char *)CG_Argv(3);
    tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
    if (tmp_l6 == 0) {
      tmp_u8 = CG_Argv(1);
    }
    else {
      tmp_u8 = CG_Argv(1);
      tmp_u8 = CG_LocalizeServerCommand(tmp_u8);
    }
    unescape_string(tmp_u8);
    tmp_pc4 = (char *)CG_Argv(2);
    tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
    tmp_pc4 = (char *)CG_Argv(4);
    tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
    local_524 = (float)tmp_l9;
    local_51c = local_524;
    tmp_pc4 = (char *)CG_Argv(5);
    tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
    local_520 = (float)tmp_l9;
    local_518 = local_520;
    tmp_pc4 = (char *)CG_Argv(6);
    tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
    local_514 = (float)tmp_l9;
    if (((cg_locations[0xc] & 2) == 0) ||
       ((tmp_pc4 = (char *)CG_GetLocationMsg(&local_51c), (cg_locations[0xc] & 8) == 0 &&
        (tmp_i13 = Q_stricmp(tmp_pc4,"Unknown"), tmp_i13 == 0)))) {
      tmp_pc4 = (char *)BG_GetLocationString(&local_524);
    }
    else if ((cg_locations[0xc] & 0x10) != 0) {
      tmp_u11 = BG_GetLocationString(&local_524);
      tmp_pc4 = (char *)va(&g_unk_0011d97b,tmp_pc4,tmp_u11);
    }
    if (tmp_pc4 == (char *)0x0) {
      tmp_pc4 = " ";
    }
    else if (*tmp_pc4 == '\0') {
      tmp_pc4 = " ";
    }
    Com_sprintf(&local_41c,0x96,"(%s^7)^3(%s):%s",tmp_l6 * 0x1a4 + 0x10f9274,tmp_pc4,tmp_u8);
    tmp_i13 = 0;
    for (tmp_pc4 = (char *)&local_41c; tmp_c2 = *tmp_pc4, tmp_c2 != '\0'; tmp_pc4 = tmp_pc4 + 1) {
      if (tmp_c2 != '\x19') {
        *(char *)((int)&local_41c + tmp_i13) = tmp_c2;
        tmp_i13 = tmp_i13 + 1;
      }
    }
    *(uint8_t *)((int)&local_41c + tmp_i13) = 0;
    CG_AddToTeamChat(&local_41c,tmp_l6);
    CG_Printf(&g_unk_00121ff9,&local_41c);
    if (GHIDRA_FIELD(cg_clientLog, 12, 4) == 0) {
      return;
    }
    CG_WriteToLog(&g_unk_00121ff9,&local_41c);
    return;
  }
  tmp_i13 = strcmp(tmp_pc4,"gamechat");
  if (tmp_i13 == 0) {
    tmp_u8 = CG_Argv(1);
    tmp_u8 = CG_LocalizeServerCommand(tmp_u8);
    Q_strncpyz(&local_41c,tmp_u8,0x96);
    tmp_i13 = 0;
    for (tmp_pc4 = (char *)&local_41c; tmp_c2 = *tmp_pc4, tmp_c2 != '\0'; tmp_pc4 = tmp_pc4 + 1) {
      if (tmp_c2 != '\x19') {
        *(char *)((int)&local_41c + tmp_i13) = tmp_c2;
        tmp_i13 = tmp_i13 + 1;
      }
    }
    *(uint8_t *)((int)&local_41c + tmp_i13) = 0;
    CG_AddToTeamChat(&local_41c,*(uint32_t *)(g_unk_01047b00 + 0xcc));
    CG_Printf(&g_unk_00121ff9,&local_41c);
    return;
  }
  tmp_i13 = strcmp(tmp_pc4,"vchat");
  if (tmp_i13 == 0) {
    CG_VoiceChat(0);
    return;
  }
  tmp_i13 = strcmp(tmp_pc4,"vtchat");
  if (tmp_i13 == 0) {
    CG_VoiceChat(1);
    return;
  }
  tmp_i13 = strcmp(tmp_pc4,"vbchat");
  if (tmp_i13 == 0) {
    CG_VoiceChat(2);
    return;
  }
  tmp_i13 = strcmp(tmp_pc4,"complaint");
  if ((tmp_i13 == 0) && (GHIDRA_FIELD(cgs, 33525356, 4) == 0)) {
    if (GHIDRA_FIELD(cg_complaintPopUp, 12, 4) == 0) {
      trap_SendClientCommand("vote no");
    }
    GHIDRA_FIELD(cgs, 33525624, 4) = g_unk_010906e0 + 20000;
    tmp_pc4 = (char *)CG_Argv(1);
    GHIDRA_FIELD(cgs, 33525620, 4) = strtol(tmp_pc4,(char **)0x0,10);
    if (-1 < (int)GHIDRA_FIELD(cgs, 33525620, 4)) {
      return;
    }
    GHIDRA_FIELD(cgs, 33525624, 4) = g_unk_010906e0 + 10000;
    return;
  }
  tmp_i13 = strcmp(tmp_pc4,"map_restart");
  if (tmp_i13 == 0) {
    if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
      CG_Printf("CG_MapRestart\n");
    }
    tmp_pu17 = &g_unk_010aad18;
    for (tmp_i13 = 10; tmp_i13 != 0; tmp_i13 = tmp_i13 + -1) {
      *tmp_pu17 = 0;
      tmp_pu17 = tmp_pu17 + (uint)tmp_b19 * -2 + 1;
    }
    g_unk_010b49bc = 0;
    g_unk_01092d00 = 0;
    g_unk_010aac2c = 0;
    g_unk_010aac10 = 0;
    GHIDRA_FIELD(cgs, 33525620, 4) = 0xffffffff;
    GHIDRA_FIELD(cgs, 33525624, 4) = 0;
    CG_LimboPanel_RequestObjective();
    g_unk_01091a64 = 0;
    g_unk_01091a68 = 0;
    g_unk_01091a6c = 0;
    g_unk_01091a74 = 0;
    g_unk_01091a78 = 0;
    g_unk_010aad14 = 0;
    g_unk_010aad0c = 0;
    g_unk_010aad04 = 0;
    GHIDRA_FIELD(cgs, 33525624, 4) = 0;
    GHIDRA_FIELD(cgs, 33575924, 4) = 0;
    GHIDRA_FIELD(cgs, 33575932, 4) = 0;
    GHIDRA_FIELD(cgs, 33575944, 4) = 0;
    GHIDRA_FIELD(cgs, 33575948, 4) = 0;
    GHIDRA_FIELD(cgs, 33575956, 4) = 0;
    trap_R_SetFog(10,4,0x14,0,0,0,0);
    g_unk_010b16f8 = 0;
    GHIDRA_FIELD(cgs, 67808, 4) = 0;
    GHIDRA_FIELD(cgs, 67800, 4) = 0;
    tmp_pu17 = &g_unk_010b1668;
    for (tmp_i13 = 0x24; tmp_i13 != 0; tmp_i13 = tmp_i13 + -1) {
      *tmp_pu17 = 0;
      tmp_pu17 = tmp_pu17 + (uint)tmp_b19 * -2 + 1;
    }
    GHIDRA_FIELD(cgs, 33525356, 4) = 0xffffffff;
    g_unk_010b1668 = (uint)(0 < (int)GHIDRA_FIELD(cg_autoReload, 12, 4));
    g_unk_010b16e8 = (uint)(0 < (int)GHIDRA_FIELD(cg_weapAltReloads, 12, 4));
    numSplinePaths = 0;
    numPathCorners = 0;
    CG_ParseWolfinfo();
    CG_ParseEntitiesFromString();
    CG_LoadObjectiveData();
    CG_InitLocalEntities();
    CG_InitMarkPolys();
    g_unk_010b4554 = 0;
    BG_BuildSplinePaths();
    InitSmokeSprites();
    CG_ClearParticles();
    CG_ClearFlameChunks();
    CG_SoundInit();
    g_unk_01047af4 = 0;
    g_unk_01092cfc = 0;
    g_unk_010906f0 = 1;
    g_unk_010906ec = 0;
    GHIDRA_FIELD(cgs, 27664, 4) = 0;
    GHIDRA_FIELD(cgs, 33576016, 4) = 0;
    CG_StartMusic();
    trap_S_ClearLoopingSounds();
    trap_S_ClearSounds(0);
    trap_R_ClearDecals();
    g_unk_010ab344 = 0;
    g_unk_010aad40 = 0;
    CG_ParseFireteams();
    tmp_i13 = 0;
    do {
      tmp_i15 = tmp_i13 + 1;
      CG_ParseOIDInfo(tmp_i13);
      tmp_i13 = tmp_i15;
    } while (tmp_i15 != 0x12);
    CG_InitPM();
    CG_ParseSpawns();
    CG_ParseTagConnects();
    trap_Cvar_Set("cg_thirdPerson",&g_unk_0011e957);
    if (0 < g_unk_010bde48) {
      g_unk_010b5e44 = 1;
    }
    trap_Cvar_Set("cg_spawnTimer_set",&g_unk_0011e957);
    trap_Cvar_Set("cg_spawnTimer_period",&g_unk_0011e957);
    nitmod_ClientCheck();
    return;
  }
  if (tmp_c2 == 's') {
    if ((tmp_pc4[1] == 'c') && (tmp_pc4[2] == '\0')) {
      CG_scores_cmd();
      return;
    }
LAB_000b9d4b:
    tmp_i13 = strcmp(tmp_pc4,"gstats");
    if (tmp_i13 == 0) {
      CG_parseWeaponStatsGS_cmd();
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"astats");
    if (tmp_i13 == 0) {
      CG_parseTopShotsStats_cmd(1,CG_printConsoleString);
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"astatsb");
    if (tmp_i13 == 0) {
      CG_parseTopShotsStats_cmd(0,CG_printConsoleString);
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"bstats");
    if (tmp_i13 == 0) {
      CG_parseBestShotsStats_cmd(1,CG_printConsoleString);
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"bstatsb");
    if (tmp_i13 == 0) {
      CG_parseBestShotsStats_cmd(0,CG_printConsoleString);
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"immaplist");
    if (tmp_i13 == 0) {
      CG_parseMapVoteListInfo();
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"imvotetally");
    if (tmp_i13 == 0) {
      CG_parseMapVoteTally();
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"wbstats");
    if (tmp_i13 == 0) {
      CG_topshotsParse_cmd(1);
      return;
    }
    if (tmp_c2 == 'r') {
      if (((tmp_pc4[1] == 'w') && (tmp_pc4[2] == 's')) && (tmp_pc4[3] == '\0')) {
        CG_ParseWeaponStats();
        return;
      }
    }
    else if (((tmp_c2 == 'z') && (tmp_pc4[1] == '5')) && (tmp_pc4[2] == '\0')) {
      CG_ParsePortalPos();
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"setspawnpt");
    if (tmp_i13 == 0) {
      tmp_pc4 = (char *)CG_Argv(1);
      tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
      g_unk_010ad284 = tmp_l6 + 1;
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"application");
    if (tmp_i13 == 0) {
      GHIDRA_FIELD(cgs, 33575932, 4) = g_unk_010906e0 + 20000;
      tmp_pc4 = (char *)CG_Argv(1);
      GHIDRA_FIELD(cgs, 33575928, 4) = strtol(tmp_pc4,(char **)0x0,10);
      if (-1 < (int)GHIDRA_FIELD(cgs, 33575928, 4)) {
        return;
      }
      GHIDRA_FIELD(cgs, 33575932, 4) = g_unk_010906e0 + 10000;
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"invitation");
    if (tmp_i13 == 0) {
      GHIDRA_FIELD(cgs, 33575924, 4) = g_unk_010906e0 + 20000;
      tmp_pc4 = (char *)CG_Argv(1);
      GHIDRA_FIELD(cgs, 33575920, 4) = strtol(tmp_pc4,(char **)0x0,10);
      if (-1 < (int)GHIDRA_FIELD(cgs, 33575920, 4)) {
        return;
      }
      GHIDRA_FIELD(cgs, 33575924, 4) = g_unk_010906e0 + 10000;
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"proposition");
    if (tmp_i13 == 0) {
      GHIDRA_FIELD(cgs, 33575944, 4) = g_unk_010906e0 + 20000;
      tmp_pc4 = (char *)CG_Argv(1);
      GHIDRA_FIELD(cgs, 33575936, 4) = strtol(tmp_pc4,(char **)0x0,10);
      tmp_pc4 = (char *)CG_Argv(2);
      GHIDRA_FIELD(cgs, 33575940, 4) = strtol(tmp_pc4,(char **)0x0,10);
      if (-1 < (int)GHIDRA_FIELD(cgs, 33575936, 4)) {
        return;
      }
      GHIDRA_FIELD(cgs, 33575944, 4) = g_unk_010906e0 + 10000;
      return;
    }
    if (((tmp_c2 == 'a') && (tmp_pc4[1] == 'f')) && ((tmp_pc4[2] == 't' && (tmp_pc4[3] == '\0')))) {
      GHIDRA_FIELD(cgs, 33575948, 4) = g_unk_010906e0 + 20000;
      tmp_pc4 = (char *)CG_Argv(1);
      GHIDRA_FIELD(cgs, 33575952, 4) = strtol(tmp_pc4,(char **)0x0,10);
      if (-2 < (int)GHIDRA_FIELD(cgs, 33575952, 4)) {
        return;
      }
      GHIDRA_FIELD(cgs, 33575948, 4) = g_unk_010906e0 + 10000;
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"aftc");
    if (tmp_i13 == 0) {
      GHIDRA_FIELD(cgs, 33575956, 4) = g_unk_010906e0 + 20000;
      tmp_pc4 = (char *)CG_Argv(1);
      GHIDRA_FIELD(cgs, 33575960, 4) = strtol(tmp_pc4,(char **)0x0,10);
      if (-2 < (int)GHIDRA_FIELD(cgs, 33575960, 4)) {
        return;
      }
      GHIDRA_FIELD(cgs, 33575956, 4) = g_unk_010906e0 + 10000;
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"aftj");
    if (tmp_i13 == 0) {
      GHIDRA_FIELD(cgs, 33575964, 4) = g_unk_010906e0 + 20000;
      tmp_pc4 = (char *)CG_Argv(1);
      GHIDRA_FIELD(cgs, 33575968, 4) = strtol(tmp_pc4,(char **)0x0,10);
      if (-2 < (int)GHIDRA_FIELD(cgs, 33575968, 4)) {
        return;
      }
      GHIDRA_FIELD(cgs, 33575964, 4) = g_unk_010906e0 + 10000;
      return;
    }
    tmp_i13 = Q_stricmp(tmp_pc4,"remapShader");
    if ((tmp_i13 == 0) && (tmp_i13 = trap_Argc(), tmp_i13 == 4)) {
      tmp_u8 = CG_Argv(3);
      tmp_u11 = CG_Argv(2);
      tmp_u12 = CG_Argv(1);
      trap_R_RemapShader(tmp_u12,tmp_u11,tmp_u8);
    }
    tmp_i13 = strcmp(tmp_pc4,"mu_start");
    if (tmp_i13 == 0) {
      tmp_l6 = 0;
      tmp_u8 = CG_Argv(2);
      Q_strncpyz(&local_41c,tmp_u8,0x96);
      if ((char)local_41c != '\0') {
        tmp_l6 = strtol((char *)&local_41c,(char **)0x0,10);
      }
      tmp_u8 = CG_Argv(1);
      tmp_u11 = CG_Argv(1);
      trap_S_StartBackgroundTrack(tmp_u11,tmp_u8,tmp_l6);
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"mu_play");
    if (tmp_i13 == 0) {
      tmp_l6 = 0;
      tmp_u8 = CG_Argv(2);
      Q_strncpyz(&local_41c,tmp_u8,0x96);
      if ((char)local_41c != '\0') {
        tmp_l6 = strtol((char *)&local_41c,(char **)0x0,10);
      }
      tmp_u8 = CG_Argv(1);
      trap_S_StartBackgroundTrack(tmp_u8,"onetimeonly",tmp_l6);
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"mu_stop");
    if (tmp_i13 == 0) {
      tmp_u8 = CG_Argv(1);
      Q_strncpyz(&local_41c,tmp_u8,0x96);
      tmp_l6 = 0;
      if ((char)local_41c != '\0') {
        tmp_l6 = strtol((char *)&local_41c,(char **)0x0,10);
      }
      trap_S_FadeBackgroundTrack(0,tmp_l6,0);
      trap_S_StartBackgroundTrack(&g_unk_0011d841,&g_unk_0011d841,0xfffffffe);
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"mu_fade");
    if (tmp_i13 == 0) {
      tmp_pc4 = (char *)CG_Argv(2);
      tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
      tmp_pc4 = (char *)CG_Argv(1);
      tmp_d20 = strtod(tmp_pc4,(char **)0x0);
      trap_S_FadeBackgroundTrack((float)tmp_d20,tmp_l6,0);
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"snd_fade");
    if (tmp_i13 == 0) {
      tmp_pc4 = (char *)CG_Argv(3);
      tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
      tmp_pc4 = (char *)CG_Argv(2);
      tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
      tmp_pc4 = (char *)CG_Argv(1);
      tmp_d20 = strtod(tmp_pc4,(char **)0x0);
      trap_S_FadeAllSound((float)tmp_d20,tmp_l9,tmp_l6);
      return;
    }
    tmp_i13 = Q_stricmp(tmp_pc4,"addToBuild");
    if (tmp_i13 == 0) {
      if (GHIDRA_FIELD(cg_buildScript, 12, 4) == 0) {
        return;
      }
      tmp_u8 = CG_Argv(1);
      trap_FS_FOpenFile(tmp_u8,&local_41c,0);
      trap_FS_FCloseFile(local_41c);
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"spawnserver");
    if (tmp_i13 == 0) {
      CG_CenterPrint("^3Server Restarting",0x168,8);
      g_unk_010b4558 = 1;
      return;
    }
    if (((*tmp_pc4 == 'f') && (tmp_pc4[1] == 'c')) && (tmp_pc4[2] == '\0')) {
      tmp_u8 = CG_Argv(1);
      Q_strncpyz(&local_51c,tmp_u8,0x100);
      tmp_u8 = CG_Argv(2);
      Q_strncpyz(&local_41c,tmp_u8,0x100);
      if (g_unk_01047aec != 0) {
        return;
      }
      tmp_i13 = Q_stricmp("cl_profile",&local_51c);
      if (tmp_i13 == 0) {
        return;
      }
      tmp_i13 = Q_stricmp(&g_unk_00115a05,&local_51c);
      if (tmp_i13 == 0) {
        return;
      }
      tmp_i13 = Q_stricmp("name",&local_51c);
      if (tmp_i13 == 0) {
        return;
      }
      tmp_i13 = Q_stricmp("sensitivity",&local_51c);
      if (tmp_i13 == 0) {
        return;
      }
      tmp_i13 = Q_stricmp("n_guid",&local_51c);
      if (tmp_i13 == 0) {
        return;
      }
      if (0x3f < g_unk_010bde48) {
        return;
      }
      local_55c = 0;
      while( true ) {
        if (g_unk_010bde48 <= local_55c) {
          Q_strncpyz(&g_unk_010b5e48 + g_unk_010bde48 * 0x200,&local_51c,0x100);
          Q_strncpyz(&g_unk_010b5f48 + g_unk_010bde48 * 0x200,&local_41c,0x100);
          g_unk_010b5e44 = 1;
          g_unk_010bde48 = g_unk_010bde48 + 1;
          return;
        }
        tmp_pc4 = (char *)Q_strlwr(&local_51c);
        tmp_pc10 = (char *)Q_strlwr(&g_unk_010b5e48 + local_55c * 0x200);
        tmp_i13 = strcmp(tmp_pc10,tmp_pc4);
        if (tmp_i13 == 0) break;
        local_55c = local_55c + 1;
      }
      Q_strncpyz(&g_unk_010b5f48 + local_55c * 0x200,&local_41c,0x100);
      return;
    }
    tmp_i13 = Q_stricmp(tmp_pc4,&g_unk_0011dc91);
    if (tmp_i13 == 0) {
      trap_Args(&local_41c,0x100);
      CG_UpdateSkills(&local_41c);
      return;
    }
    tmp_c2 = *tmp_pc4;
    if (tmp_c2 == 'o') {
      if ((tmp_pc4[1] == 'b') && (tmp_pc4[2] == '\0')) {
        nitmod_ObjectiveEvent();
        return;
      }
    }
    else if (tmp_c2 == 'n') {
      if (((tmp_pc4[1] == 'c') && (tmp_pc4[2] == 'p')) && (tmp_pc4[3] == '\0')) {
        tmp_pc4 = (char *)CG_Argv(1);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        if ((tmp_l6 == 7) && (GHIDRA_FIELD(cgs, 33788144, 4) != 30000)) {
          tmp_u8 = va("Dynamite is now armed with a %i second timer!",(int)GHIDRA_FIELD(cgs, 33788144, 4) / 1000);
          CG_CenterPrint(tmp_u8,0x180,8);
          return;
        }
        CG_CenterPrint(*(uint32_t *)(SrvMsgs + tmp_l6 * 4),0x180,8);
        return;
      }
    }
    else if (tmp_c2 == 'z') {
      if ((tmp_pc4[1] == '2') && (tmp_pc4[2] == '\0')) {
        tmp_pc4 = (char *)CG_Argv(1);
        g_unk_010ef120 = strtol(tmp_pc4,(char **)0x0,10);
        tmp_pc4 = (char *)CG_Argv(2);
        GHIDRA_FIELD(cgs, 33787768, 4) = strtol(tmp_pc4,(char **)0x0,10);
        g_unk_010ef124 = 3;
        nitmod_AddSpreePrint();
        return;
      }
    }
    else if (tmp_c2 == 'h') {
      if (((tmp_pc4[1] == 'p') && (tmp_pc4[2] == 'b')) && (tmp_pc4[3] == '\0')) {
        tmp_pc4 = (char *)CG_Argv(1);
        tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
        tmp_u8 = va("+%i HP",tmp_l6);
        nitrox_AddSpecialPrint(tmp_u8,0,0x3f800000,0,0x5a,0);
        return;
      }
    }
    else {
      if (tmp_c2 == '#') {
        nitmod_ParseNCS();
        return;
      }
      if (tmp_c2 == 'c') {
        if ((tmp_pc4[1] == 't') && (tmp_pc4[2] == '\0')) {
          nitrox_ParseChargeTimes();
          return;
        }
      }
      else if (tmp_c2 == 's') {
        if (((tmp_pc4[1] == 'c') && (tmp_pc4[2] == 's')) && (tmp_pc4[3] == '\0')) {
          nitmod_GetSimpleCS();
          return;
        }
      }
      else if (tmp_c2 == 't') {
        if (((tmp_pc4[1] == 's') && (tmp_pc4[2] == 'c')) && (tmp_pc4[3] == '\0')) {
          tmp_pc4 = (char *)CG_Argv(1);
          tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
          tmp_pc4 = (char *)CG_Argv(2);
          tmp_l9 = strtol(tmp_pc4,(char **)0x0,10);
          if (g_unk_01091e8c != tmp_l6) {
            g_unk_010ef1e0 = g_unk_010906e0;
            g_unk_010ef1e8 = (uint)(g_unk_01091e8c < tmp_l6);
          }
          if (g_unk_01091e90 == tmp_l9) {
            g_unk_01091e8c = tmp_l6;
            g_unk_01091e90 = tmp_l9;
            return;
          }
          tmp_b18 = g_unk_01091e90 < tmp_l9;
          g_unk_01091e8c = tmp_l6;
          g_unk_01091e90 = tmp_l9;
          g_unk_010ef1e4 = g_unk_010906e0;
          g_unk_010ef1ec = (uint)tmp_b18;
          return;
        }
      }
      else if (((tmp_c2 == 'm') && (tmp_pc4[1] == 'e')) && ((tmp_pc4[2] == 's' && (tmp_pc4[3] == '\0')))
              ) {
        nitmod_GetMapEndStats();
        return;
      }
    }
    tmp_i13 = CG_Debriefing_ServerCommand(tmp_pc4);
    if (tmp_i13 != 0) {
      return;
    }
    tmp_i13 = strcmp(tmp_pc4,"getnguid");
    if (tmp_i13 != 0) {
      tmp_i13 = strcmp(tmp_pc4,"gsnd");
      if (tmp_i13 != 0) {
        if (*tmp_pc4 == '*') {
          return;
        }
        CG_Printf("Unknown client game command: %s\n",tmp_pc4);
        return;
      }
      if (GHIDRA_FIELD(cg_noGreetingSounds, 12, 4) != 0) {
        return;
      }
      tmp_u8 = CG_Argv(1);
      tmp_u8 = trap_S_RegisterSound(tmp_u8,0);
      trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),3,tmp_u8);
      return;
    }
    trap_Cvar_Set("n_guid",&g_unk_0011d841);
    g_unk_010ef664 = 1;
    return;
  }
  if (tmp_c2 != 'w') goto LAB_000b9d4b;
  if (tmp_pc4[1] == 's') {
    if (tmp_pc4[2] == '\0') {
      if (g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33576016, 4)) {
        CG_dumpStats();
        return;
      }
      CG_parseWeaponStats_cmd(CG_printConsoleString);
      GHIDRA_FIELD(cgs, 33576016, 4) = 0;
      return;
    }
    goto LAB_000b9d4b;
  }
  if (((tmp_pc4[1] != 'w') || (tmp_pc4[2] != 's')) || (tmp_pc4[3] != '\0')) goto LAB_000b9d4b;
  if (g_unk_010afbd0 == 0) {
    return;
  }
  if (((g_unk_010afbdc == 0) || (*(int *)(g_unk_010afbdc + 0x54) != 1)) ||
     (*(int *)(g_unk_010afbdc + 0x58) == 0)) {
    CG_createStatsWindow();
  }
  else {
    if (*(int *)(g_unk_010afbdc + 0x264) != 2) goto LAB_000bba75;
    *(uint32_t *)(g_unk_010afbdc + 0x264) = 1;
    tmp_i13 = g_unk_010afbdc;
    tmp_u8 = trap_Milliseconds();
    *(uint32_t *)(tmp_i13 + 0x268) = tmp_u8;
  }
  if (g_unk_010afbdc == 0) {
    g_unk_010afbd0 = 0;
    return;
  }
LAB_000bba75:
  *(uint *)(g_unk_010afbdc + 0x34) = *(uint *)(g_unk_010afbdc + 0x34) | 1;
  *(uint32_t *)(g_unk_010afbdc + 0x5c) = 0;
  g_unk_010afbe8 = g_unk_010afbdc;
  CG_parseWeaponStats_cmd(CG_printWindow);
  return;
}

void CG_ParseEntityFromSpawnVars(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  char *tmp_pc3;
  long tmp_l4;
  int tmp_i5;
  char *tmp_pc6;
  bool tmp_b7;
  byte tmp_b8;
  
  tmp_b8 = 0;
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i2 = 0;
    tmp_b7 = true;
    do {
      tmp_i5 = 8;
      tmp_pc3 = "notteam";
      tmp_pc6 = (char *)(&g_unk_010ab350)[tmp_i2 * 2];
      do {
        if (tmp_i5 == 0) break;
        tmp_i5 = tmp_i5 + -1;
        tmp_b7 = *tmp_pc3 == *tmp_pc6;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) {
        tmp_pc3 = (char *)(&g_unk_010ab354)[tmp_i2 * 2];
        goto LAB_000c3f8e;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_b7 = tmp_i2 == g_unk_010ab34c;
    } while (!tmp_b7);
  }
  tmp_pc3 = "0";
LAB_000c3f8e:
  tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
  if (tmp_l4 != 0) {
    return;
  }
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (g_unk_010ab34c < 1) {
    return;
  }
  tmp_i2 = 0;
  tmp_b7 = true;
  do {
    tmp_i5 = 10;
    tmp_pc3 = "classname";
    tmp_pc6 = (char *)(&g_unk_010ab350)[tmp_i2 * 2];
    do {
      if (tmp_i5 == 0) break;
      tmp_i5 = tmp_i5 + -1;
      tmp_b7 = *tmp_pc3 == *tmp_pc6;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
      tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
    } while (tmp_b7);
    if (tmp_b7) {
      tmp_u1 = (&g_unk_010ab354)[tmp_i2 * 2];
      tmp_i2 = 0;
      do {
        tmp_i5 = Q_stricmp(*(uint32_t *)(spawns + tmp_i2 * 8),tmp_u1);
        if (tmp_i5 == 0) {
          (**(void **)(spawns + tmp_i2 * 8 + 4))();
          return;
        }
        tmp_i2 = tmp_i2 + 1;
      } while (tmp_i2 != 7);
      return;
    }
    tmp_i2 = tmp_i2 + 1;
    tmp_b7 = false;
    if (tmp_i2 == g_unk_010ab34c) {
      return;
    }
  } while( true );
}

uint32_t CG_ParseSpawnVars(void)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  uint tmp_u4;
  uint tmp_u5;
  uint *tmp_pu6;
  uint32_t tmp_u7;
  uint8_t *tmp_pu8;
  uint8_t *tmp_pu9;
  uint *tmp_pu10;
  uint *tmp_pu11;
  uint *tmp_pu12;
  byte tmp_b13;
  char local_81c;
  uint auStack_81b [255];
  char local_41c;
  uint auStack_41b [257];
  uint32_t uStack_14;
  
  tmp_b13 = 0;
  uStack_14 = 0xc419b;
  g_unk_010ab34c = 0;
  g_unk_010ab550 = (uint8_t *)0x0;
  tmp_i2 = trap_GetEntityToken(&local_41c,0x400);
  tmp_u7 = 0;
  if (tmp_i2 != 0) {
    if (local_41c != '{') {
      CG_Error("CG_ParseSpawnVars: found %s when expecting {",&local_41c);
    }
    while( true ) {
      tmp_i2 = trap_GetEntityToken(&local_81c,0x400);
      if (tmp_i2 == 0) {
        CG_Error("CG_ParseSpawnVars: EOF without closing brace");
      }
      if (local_81c == '}') break;
      tmp_i2 = trap_GetEntityToken(&local_41c,0x400);
      if (tmp_i2 == 0) {
        CG_Error("CG_ParseSpawnVars: EOF without closing brace");
      }
      if (local_41c == '}') {
        CG_Error("CG_ParseSpawnVars: closing brace without data");
      }
      tmp_pu10 = (uint *)&local_81c;
      if (g_unk_010ab34c == 0x40) {
        CG_Error("CG_ParseSpawnVars: MAX_SPAWN_VARS");
      }
      do {
        tmp_pu12 = tmp_pu10;
        tmp_i2 = g_unk_010ab34c;
        tmp_u4 = *tmp_pu12 + 0xfefefeff & ~*tmp_pu12;
        tmp_u5 = tmp_u4 & 0x80808080;
        tmp_pu10 = tmp_pu12 + 1;
      } while (tmp_u5 == 0);
      if ((tmp_u4 & 0x8080) == 0) {
        tmp_pu10 = (uint *)((int)tmp_pu12 + 6);
        tmp_u5 = tmp_u5 >> 0x10;
      }
      tmp_pu9 = (uint8_t *)
               ((int)tmp_pu10 + ((-3 - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5)) - (int)&local_81c));
      if (0x7ff < (int)(g_unk_010ab550 + (int)tmp_pu9)) {
        CG_Error("CG_AddSpawnVarToken: MAX_SPAWN_VARS");
      }
      tmp_pu1 = g_unk_010ab550;
      tmp_pu6 = (uint *)(g_unk_010ab550 + 0x10ab554);
      tmp_pu3 = tmp_pu9 + 1;
      tmp_pu8 = tmp_pu3;
      tmp_pu10 = (uint *)&local_81c;
      tmp_pu12 = tmp_pu6;
      if ((uint8_t *)0x7 < tmp_pu3) {
        tmp_pu11 = tmp_pu6;
        if (((uint)tmp_pu6 & 1) != 0) {
          tmp_pu10 = auStack_81b;
          g_unk_010ab550[0x10ab554] = local_81c;
          tmp_pu11 = (uint *)(tmp_pu1 + 0x10ab555);
          tmp_pu8 = tmp_pu9;
        }
        tmp_pu12 = tmp_pu11;
        if (((uint)tmp_pu11 & 2) != 0) {
          tmp_u5 = *tmp_pu10;
          tmp_pu12 = (uint *)((int)tmp_pu11 + 2);
          tmp_pu10 = (uint *)((int)tmp_pu10 + 2);
          tmp_pu8 = tmp_pu8 + -2;
          *(short *)tmp_pu11 = (short)tmp_u5;
        }
        if (((uint)tmp_pu12 & 4) != 0) {
          tmp_pu8 = tmp_pu8 + -4;
          *tmp_pu12 = *tmp_pu10;
          tmp_pu10 = tmp_pu10 + 1;
          tmp_pu12 = tmp_pu12 + 1;
        }
      }
      for (; tmp_pu8 != (uint8_t *)0x0; tmp_pu8 = tmp_pu8 + -1) {
        *(char *)tmp_pu12 = (char)*tmp_pu10;
        tmp_pu10 = (uint *)((int)tmp_pu10 + (uint)tmp_b13 * -2 + 1);
        tmp_pu12 = (uint *)((int)tmp_pu12 + (uint)tmp_b13 * -2 + 1);
      }
      tmp_pu3 = g_unk_010ab550 + (int)tmp_pu3;
      g_unk_010ab550 = tmp_pu3;
      (&g_unk_010ab350)[tmp_i2 * 2] = tmp_pu6;
      tmp_i2 = g_unk_010ab34c;
      tmp_pu10 = (uint *)&local_41c;
      do {
        tmp_pu12 = tmp_pu10;
        tmp_u4 = *tmp_pu12 + 0xfefefeff & ~*tmp_pu12;
        tmp_u5 = tmp_u4 & 0x80808080;
        tmp_pu10 = tmp_pu12 + 1;
      } while (tmp_u5 == 0);
      if ((tmp_u4 & 0x8080) == 0) {
        tmp_pu10 = (uint *)((int)tmp_pu12 + 6);
        tmp_u5 = tmp_u5 >> 0x10;
      }
      tmp_pu9 = (uint8_t *)
               ((int)tmp_pu10 + ((-3 - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5)) - (int)&local_41c));
      if (0x7ff < (int)(tmp_pu3 + (int)tmp_pu9)) {
        CG_Error("CG_AddSpawnVarToken: MAX_SPAWN_VARS");
        tmp_pu3 = g_unk_010ab550;
      }
      tmp_pu6 = (uint *)(tmp_pu3 + 0x10ab554);
      tmp_pu1 = tmp_pu9 + 1;
      tmp_pu8 = tmp_pu1;
      tmp_pu10 = (uint *)&local_41c;
      tmp_pu12 = tmp_pu6;
      if ((uint8_t *)0x7 < tmp_pu1) {
        if (((uint)tmp_pu6 & 1) != 0) {
          tmp_pu10 = auStack_41b;
          tmp_pu3[0x10ab554] = local_41c;
          tmp_pu12 = (uint *)(tmp_pu3 + 0x10ab555);
          tmp_pu8 = tmp_pu9;
        }
        tmp_pu11 = tmp_pu12;
        if (((uint)tmp_pu12 & 2) != 0) {
          tmp_u5 = *tmp_pu10;
          tmp_pu11 = (uint *)((int)tmp_pu12 + 2);
          tmp_pu10 = (uint *)((int)tmp_pu10 + 2);
          tmp_pu8 = tmp_pu8 + -2;
          *(short *)tmp_pu12 = (short)tmp_u5;
        }
        tmp_pu12 = tmp_pu11;
        if (((uint)tmp_pu11 & 4) != 0) {
          tmp_u5 = *tmp_pu10;
          tmp_pu12 = tmp_pu11 + 1;
          tmp_pu10 = tmp_pu10 + 1;
          tmp_pu8 = tmp_pu8 + -4;
          *tmp_pu11 = tmp_u5;
        }
      }
      for (; tmp_pu8 != (uint8_t *)0x0; tmp_pu8 = tmp_pu8 + -1) {
        *(char *)tmp_pu12 = (char)*tmp_pu10;
        tmp_pu10 = (uint *)((int)tmp_pu10 + (uint)tmp_b13 * -2 + 1);
        tmp_pu12 = (uint *)((int)tmp_pu12 + (uint)tmp_b13 * -2 + 1);
      }
      g_unk_010ab550 = g_unk_010ab550 + (int)tmp_pu1;
      g_unk_010ab34c = g_unk_010ab34c + 1;
      (&g_unk_010ab354)[tmp_i2 * 2] = tmp_pu6;
    }
    tmp_u7 = 1;
  }
  return tmp_u7;
}

void CG_ParseEntitiesFromString(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  char *tmp_pc3;
  long tmp_l4;
  int tmp_i5;
  char *tmp_pc6;
  bool tmp_b7;
  byte tmp_b8;
  
  tmp_b8 = 0;
  g_unk_010ab348 = 1;
  g_unk_010ab34c = 0;
  g_unk_010abd70 = 0;
  g_unk_010abd74 = 0;
  tmp_i2 = CG_ParseSpawnVars();
  if (tmp_i2 == 0) {
    CG_Error("ParseEntities: no entities");
  }
  SP_worldspawn();
LAB_000c50c0:
  tmp_i2 = CG_ParseSpawnVars();
joined_r0x000c50c7:
  if (tmp_i2 == 0) {
    g_unk_010ab348 = 0;
    return;
  }
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i2 = 0;
    tmp_b7 = true;
    do {
      tmp_i5 = 8;
      tmp_pc3 = "notteam";
      tmp_pc6 = (char *)(&g_unk_010ab350)[tmp_i2 * 2];
      do {
        if (tmp_i5 == 0) break;
        tmp_i5 = tmp_i5 + -1;
        tmp_b7 = *tmp_pc3 == *tmp_pc6;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) {
        tmp_pc3 = (char *)(&g_unk_010ab354)[tmp_i2 * 2];
        goto LAB_000c5126;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_b7 = tmp_i2 == g_unk_010ab34c;
    } while (!tmp_b7);
  }
  tmp_pc3 = "0";
LAB_000c5126:
  tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
  if (tmp_l4 == 0) {
    if (g_unk_010ab348 == 0) {
      CG_Error("CG_SpawnString() called while not spawning");
    }
    if (0 < g_unk_010ab34c) {
      tmp_i2 = 0;
      tmp_b7 = true;
      do {
        tmp_i5 = 10;
        tmp_pc3 = "classname";
        tmp_pc6 = (char *)(&g_unk_010ab350)[tmp_i2 * 2];
        do {
          if (tmp_i5 == 0) break;
          tmp_i5 = tmp_i5 + -1;
          tmp_b7 = *tmp_pc3 == *tmp_pc6;
          tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
          tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
        } while (tmp_b7);
        if (tmp_b7) goto code_r0x000c519f;
        tmp_i2 = tmp_i2 + 1;
        tmp_b7 = false;
        if (tmp_i2 == g_unk_010ab34c) break;
      } while( true );
    }
  }
  goto LAB_000c50c0;
code_r0x000c519f:
  tmp_u1 = (&g_unk_010ab354)[tmp_i2 * 2];
  tmp_i2 = 0;
  while (tmp_i5 = Q_stricmp(*(uint32_t *)(spawns + tmp_i2 * 8),tmp_u1), tmp_i5 != 0) {
    tmp_i2 = tmp_i2 + 1;
    if (tmp_i2 == 7) goto LAB_000c50c0;
  }
  (**(void **)(spawns + tmp_i2 * 8 + 4))();
  tmp_i2 = CG_ParseSpawnVars();
  goto joined_r0x000c50c7;
}

void CG_ParseSkyBox(void)
{
  char *tmp_pc1;
  long tmp_l2;
  long tmp_l3;
  double tmp_d4;
  double tmp_d5;
  double tmp_d6;
  char *local_20 [4];
  
  local_20[0] = (char *)CG_ConfigString(0x13);
  if (*local_20[0] == '\0') {
    g_unk_010b4534 = 0;
  }
  else {
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      CG_Error("CG_ParseSkyBox: error parsing skybox configstring\n");
    }
    tmp_d4 = strtod(tmp_pc1,(char **)0x0);
    g_unk_010b4538 = (float)tmp_d4;
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      CG_Error("CG_ParseSkyBox: error parsing skybox configstring\n");
    }
    tmp_d4 = strtod(tmp_pc1,(char **)0x0);
    g_unk_010b453c = (float)tmp_d4;
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      CG_Error("CG_ParseSkyBox: error parsing skybox configstring\n");
    }
    tmp_d4 = strtod(tmp_pc1,(char **)0x0);
    g_unk_010b4540 = (float)tmp_d4;
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      CG_Error("CG_ParseSkyBox: error parsing skybox configstring\n");
    }
    tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
    g_unk_010b4544 = (float)tmp_l2;
    if (g_unk_010b4544 == 0.0) {
      g_unk_010b4544 = 90.0;
    }
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      CG_Error("CG_ParseSkyBox: error parsing skybox configstring.  No fog state\n");
    }
    tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
    if (tmp_l2 == 0) {
      trap_R_SetFog(2,0,0,0,0,0,0);
    }
    else {
      tmp_pc1 = (char *)COM_Parse(local_20);
      if (*tmp_pc1 == '\0') {
        CG_Error("CG_DrawSkyBoxPortal: error parsing skybox configstring.  No fog[0]\n");
      }
      tmp_d4 = strtod(tmp_pc1,(char **)0x0);
      tmp_pc1 = (char *)COM_Parse(local_20);
      if (*tmp_pc1 == '\0') {
        CG_Error("CG_DrawSkyBoxPortal: error parsing skybox configstring.  No fog[1]\n");
      }
      tmp_d5 = strtod(tmp_pc1,(char **)0x0);
      tmp_pc1 = (char *)COM_Parse(local_20);
      if (*tmp_pc1 == '\0') {
        CG_Error("CG_DrawSkyBoxPortal: error parsing skybox configstring.  No fog[2]\n");
      }
      tmp_d6 = strtod(tmp_pc1,(char **)0x0);
      tmp_pc1 = (char *)COM_ParseExt(local_20,0);
      tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
      tmp_pc1 = (char *)COM_ParseExt(local_20,0);
      tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
      trap_R_SetFog(2,tmp_l2,tmp_l3,(float)tmp_d4,(float)tmp_d5,(float)tmp_d6,0x3f8ccccd);
    }
    g_unk_010b4534 = 1;
  }
  return;
}

void CG_ParseTagConnects(void)
{
  char *tmp_pc1;
  uint tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  char *local_20 [4];
  
  tmp_i4 = 0x309;
  do {
    while (local_20[0] = (char *)CG_ConfigString(tmp_i4), *local_20[0] == '\0') {
      tmp_i4 = tmp_i4 + 1;
      if (tmp_i4 == 0x349) {
        return;
      }
    }
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      CG_Error("Invalid TAGCONNECT configstring\n");
    }
    tmp_u2 = strtol(tmp_pc1,(char **)0x0,10);
    if (0x3ff < tmp_u2) {
      CG_Error("Invalid TAGCONNECT entitynum\n");
    }
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      CG_Error("Invalid TAGCONNECT configstring\n");
    }
    tmp_u3 = strtol(tmp_pc1,(char **)0x0,10);
    *(uint *)(cg_entities + tmp_u2 * 0xaf8 + 0xab4) = tmp_u3;
    if (0x3ff < tmp_u3) {
      CG_Error("Invalid TAGCONNECT tagparent\n");
    }
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      CG_Error("Invalid TAGCONNECT configstring\n");
    }
    tmp_i4 = tmp_i4 + 1;
    Q_strncpyz(tmp_u2 * 0xaf8 + 0x31348f8,tmp_pc1,0x40);
  } while (tmp_i4 != 0x349);
  return;
}

void CG_ParseTagConnect(uint32_t param_1)
{
  char tmp_c1;
  char *tmp_pc2;
  uint tmp_u3;
  uint tmp_u4;
  char *local_20 [4];
  
  local_20[0] = (char *)CG_ConfigString(param_1);
  if (*local_20[0] != '\0') {
    tmp_pc2 = (char *)COM_Parse(local_20);
    if (*tmp_pc2 == '\0') {
      CG_Error("Invalid TAGCONNECT configstring\n");
    }
    tmp_u3 = strtol(tmp_pc2,(char **)0x0,10);
    if (0x3ff < tmp_u3) {
      CG_Error("Invalid TAGCONNECT entitynum\n");
    }
    tmp_pc2 = (char *)COM_Parse(local_20);
    if (*tmp_pc2 == '\0') {
      CG_Error("Invalid TAGCONNECT configstring\n");
    }
    tmp_u4 = strtol(tmp_pc2,(char **)0x0,10);
    *(uint *)(cg_entities + tmp_u3 * 0xaf8 + 0xab4) = tmp_u4;
    if (tmp_u4 < 0x400) {
      tmp_pc2 = (char *)COM_Parse(local_20);
      tmp_c1 = *tmp_pc2;
    }
    else {
      CG_Error("Invalid TAGCONNECT tagparent\n");
      tmp_pc2 = (char *)COM_Parse(local_20);
      tmp_c1 = *tmp_pc2;
    }
    if (tmp_c1 == '\0') {
      CG_Error("Invalid TAGCONNECT configstring\n");
    }
    Q_strncpyz(tmp_u3 * 0xaf8 + 0x31348f8,tmp_pc2,0x40);
  }
  return;
}

uint32_t CG_ParseWeaponConfig(uint32_t param_1,int param_2)
{
  bool tmp_b1;
  int tmp_i2;
  char *tmp_pc3;
  uint tmp_u4;
  long tmp_l5;
  uint *tmp_pu6;
  double tmp_d7;
  uint8_t *local_4e68;
  uint8_t *local_4e44;
  uint32_t local_4e40;
  uint8_t local_4e3c [20008];
  uint32_t uStack_14;
  
  uStack_14 = 0xd050d;
  tmp_i2 = trap_FS_FOpenFile(param_1,&local_4e40,0);
  if (0 < tmp_i2) {
    if (0x4e1e < tmp_i2) {
      CG_Printf("File %s too long\n",param_1);
      return 0;
    }
    trap_FS_Read(local_4e3c,tmp_i2,local_4e40);
    local_4e3c[tmp_i2] = 0;
    trap_FS_FCloseFile(local_4e40);
    tmp_b1 = false;
    local_4e44 = local_4e3c;
    while (local_4e68 = local_4e44, tmp_pc3 = (char *)COM_Parse(&local_4e44), tmp_pc3 != (char *)0x0)
    {
      while (tmp_i2 = Q_stricmp(tmp_pc3,&g_unk_00110812), tmp_i2 == 0) {
        tmp_b1 = true;
        local_4e68 = local_4e44;
        tmp_pc3 = (char *)COM_Parse(&local_4e44);
        if (tmp_pc3 == (char *)0x0) goto LAB_000d05e1;
      }
      if ((byte)(*tmp_pc3 - 0x30U) < 10) {
        local_4e44 = local_4e68;
        break;
      }
      Com_Printf("unknown token in weapon cfg \'%s\' is %s\n",tmp_pc3,param_1);
    }
LAB_000d05e1:
    tmp_pu6 = (uint *)(param_2 + 0x5c);
    while (tmp_pc3 = (char *)COM_Parse(&local_4e44), tmp_pc3 != (char *)0x0) {
      tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pu6[-5] = tmp_u4;
      tmp_pc3 = (char *)COM_Parse(&local_4e44);
      if (tmp_pc3 == (char *)0x0) break;
      tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pu6[-4] = tmp_u4;
      tmp_pc3 = (char *)COM_Parse(&local_4e44);
      if (tmp_pc3 == (char *)0x0) break;
      tmp_d7 = strtod(tmp_pc3,(char **)0x0);
      tmp_u4 = 1000;
      if ((float)tmp_d7 != 0.0) {
        tmp_u4 = (uint)ROUND(1000.0 / (float)tmp_d7);
      }
      tmp_pu6[-2] = tmp_u4;
      tmp_pu6[-1] = tmp_u4;
      tmp_pc3 = (char *)COM_Parse(&local_4e44);
      if (tmp_pc3 == (char *)0x0) break;
      tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pu6[-3] = tmp_u4;
      if ((int)tmp_pu6[-4] < (int)tmp_u4) {
        tmp_pu6[-3] = tmp_pu6[-4];
LAB_000d05f3:
        *tmp_pu6 = 0;
      }
      else {
        if (-1 < (int)tmp_u4) goto LAB_000d05f3;
        tmp_pu6[-3] = 0;
        *tmp_pu6 = 0;
      }
      if (tmp_b1) {
        tmp_pc3 = (char *)COM_Parse(&local_4e44);
        if (tmp_pc3 != (char *)0x0) {
          tmp_u4 = strtol(tmp_pc3,(char **)0x0,10);
          *tmp_pu6 = tmp_u4;
          tmp_pc3 = (char *)COM_Parse(&local_4e44);
          if (tmp_pc3 != (char *)0x0) {
            tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
            if (tmp_l5 != 0) {
              *tmp_pu6 = *tmp_pu6 | 0x10000;
            }
            tmp_pc3 = (char *)COM_Parse(&local_4e44);
            if (tmp_pc3 != (char *)0x0) {
              tmp_u4 = *tmp_pu6;
              tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
              *tmp_pu6 = tmp_l5 << 8 | tmp_u4;
              goto joined_r0x000d060a;
            }
          }
        }
        break;
      }
joined_r0x000d060a:
      tmp_pu6 = tmp_pu6 + 0x1c;
      if (tmp_pu6 == (uint *)(param_2 + 0x60c)) {
        return 1;
      }
    }
    CG_Printf("Error parsing weapon animation file: %s",param_1);
  }
  return 0;
}

void CG_ParseScore(int param_1)
{
  int tmp_i1;
  char *tmp_pc2;
  long tmp_l3;
  long tmp_l4;
  long tmp_l5;
  uint tmp_u6;
  int tmp_i7;
  int tmp_i8;
  
  if (param_1 == 1) {
    g_unk_01091e84 = 0;
  }
  tmp_pc2 = (char *)CG_Argv(1);
  tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
  if (0 < tmp_l3) {
    tmp_i8 = 2;
    do {
      tmp_i1 = g_unk_01091e84;
      tmp_pc2 = (char *)CG_Argv(tmp_i8);
      tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_i7 = tmp_i1 * 0x28;
      (&g_unk_01091ea4)[tmp_i1 * 10] = tmp_l4;
      tmp_pc2 = (char *)CG_Argv(tmp_i8 + 1);
      tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
      *(long *)(&g_unk_01091ea8 + tmp_i7) = tmp_l4;
      tmp_pc2 = (char *)CG_Argv(tmp_i8 + 2);
      tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
      *(long *)(&g_unk_01091eac + tmp_i7) = tmp_l4;
      tmp_pc2 = (char *)CG_Argv(tmp_i8 + 3);
      tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
      (&g_unk_01091eb0)[tmp_i1 * 10] = tmp_l4;
      tmp_pc2 = (char *)CG_Argv(tmp_i8 + 4);
      tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_pc2 = (char *)CG_Argv(tmp_i8 + 5);
      tmp_l5 = strtol(tmp_pc2,(char **)0x0,10);
      *(long *)(&g_unk_01091ebc + tmp_i7) = tmp_l5;
      tmp_pc2 = (char *)CG_Argv(tmp_i8 + 6);
      tmp_l5 = strtol(tmp_pc2,(char **)0x0,10);
      *(long *)(&g_unk_01091ec0 + tmp_i7) = tmp_l5;
      tmp_u6 = (&g_unk_01091ea4)[tmp_i1 * 10];
      if (0x3f < tmp_u6) {
        (&g_unk_01091ea4)[tmp_i1 * 10] = 0;
        tmp_u6 = 0;
      }
      tmp_i7 = tmp_u6 * 0x1a4;
      tmp_i8 = tmp_i8 + 7;
      *(uint32_t *)(cgs + tmp_i7 + 0x9498) = *(uint32_t *)(&g_unk_01091ea8 + tmp_i1 * 0x28);
      *(long *)(cgs + tmp_i7 + 0x94b0) = tmp_l4;
      (&g_unk_01091eb8)[tmp_i1 * 10] = *(uint32_t *)(cgs + tmp_i7 + 0x9494);
      g_unk_01091e84 = g_unk_01091e84 + 1;
    } while (tmp_i8 != tmp_l3 * 7 + 2);
  }
  return;
}

void CG_ParseKD(int param_1)
{
  int tmp_i1;
  char *tmp_pc2;
  long tmp_l3;
  long tmp_l4;
  int tmp_i5;
  
  if (param_1 == 1) {
    g_unk_01091e84 = 0;
  }
  tmp_pc2 = (char *)CG_Argv(1);
  tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
  if (0 < tmp_l3) {
    tmp_i5 = 3;
    do {
      tmp_i1 = g_unk_01091e84;
      tmp_pc2 = (char *)CG_Argv(tmp_i5);
      tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
      *(long *)(&g_unk_01091ec4 + tmp_i1 * 0x28) = tmp_l4;
      tmp_pc2 = (char *)CG_Argv(tmp_i5 + 1);
      tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
      *(long *)(&g_unk_01091ec8 + tmp_i1 * 0x28) = tmp_l4;
      if (0x3f < (uint)(&g_unk_01091ea4)[tmp_i1 * 10]) {
        (&g_unk_01091ea4)[tmp_i1 * 10] = 0;
      }
      tmp_i5 = tmp_i5 + 3;
      g_unk_01091e84 = g_unk_01091e84 + 1;
    } while (tmp_i5 != tmp_l3 * 3 + 3);
  }
  return;
}

void CG_ParseInfo(void)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint8_t local_11c [264];
  uint32_t uStack_14;
  
  uStack_14 = 0x105fee;
  tmp_u1 = CG_ConfigString(0x24);
  tmp_u2 = Info_ValueForKey(tmp_u1,&g_unk_0011756b);
  Q_strncpyz(0x3128ccc,tmp_u2,0x100);
  Q_strncpyz(local_11c,0x3128bb8,0x100);
  tmp_u1 = Info_ValueForKey(tmp_u1,"W");
  Q_strncpyz(0x3128bb8,tmp_u1,0x100);
  tmp_i3 = Q_stricmp(0x3128bb8,local_11c);
  if (tmp_i3 != 0) {
    tmp_i3 = 0;
    do {
      tmp_i4 = BG_WeaponInWolfMP(tmp_i3);
      if ((tmp_i4 != 0) || (tmp_i3 == 0)) {
        CG_RegisterWeapon(tmp_i3,1);
        BG_RegisterWeapon(tmp_i3,1);
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != 0x34);
  }
  return;
}

