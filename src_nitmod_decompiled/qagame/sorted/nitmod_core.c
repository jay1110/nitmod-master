/* Nitmod / nitrox helpers not in admin/weapons — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_core.h"

uint32_t Nit_RemoveWordInString(char *param_1,char *param_2)
{
  size_t tmp_s1;
  int tmp_i2;
  size_t tmp_s3;
  char tmp_c4;
  char *__src;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  tmp_s1 = strlen(param_2);
  tmp_c4 = *param_1;
  if (tmp_c4 != '\0') {
    tmp_s3 = 0;
    tmp_i2 = 0;
    __src = param_1 + 1;
    do {
      while (tmp_c4 == param_2[tmp_i2]) {
        tmp_s3 = tmp_s3 + 1;
        tmp_i2 = tmp_i2 + 1;
        if (tmp_s3 == tmp_s1) goto LAB_00036f58;
LAB_00036f44:
        tmp_c4 = *__src;
        __src = __src + 1;
        if (tmp_c4 == '\0') {
          return 1;
        }
      }
      if (tmp_s3 != tmp_s1) goto LAB_00036f44;
LAB_00036f58:
      strcpy(__src + -tmp_s3,__src);
      tmp_c4 = *__src;
      tmp_s3 = 0;
      tmp_i2 = 0;
      __src = __src + 1;
    } while (tmp_c4 != '\0');
  }
  return 1;
}

void nitrox_AddPredictableDamage
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,int param_4)

{
  *(int *)(param_4 + 0xc0) = *(int *)(param_4 + 0xc0) + 1;
  *(uint32_t *)(param_4 + 0xcc) = param_1;
  *(uint32_t *)(param_4 + 200) = param_2;
  *(uint32_t *)(param_4 + 0xc4) = param_3;
  return;
}

bool nitmod_NCSvar(uint8_t *param_1)
{
  return ((((((((((((((((((param_1 == team_maxPanzers || param_1 == team_panzerRestriction) ||
                         param_1 == team_maxMG42s) || param_1 == team_maxFlamers) ||
                       param_1 == team_maxMortars) || param_1 == team_maxriflegrenades) ||
                     param_1 == g_adrenaline) || param_1 == team_maxSoldiers) ||
                   param_1 == team_maxMedics) || param_1 == team_maxEngineers) ||
                 param_1 == team_maxFieldops) || param_1 == team_maxCovertops) ||
               param_1 == g_weapons) || param_1 == jp_keepAwards) || param_1 == g_DJHeight) ||
            param_1 == g_missileCams) || param_1 == g_TDMOptions) || param_1 == g_DMOptions) ||
         param_1 == g_gravity) || param_1 == g_resetXPMapCount;
}

bool nitrox_PreciseBBoxCollision(float *param_1,float *param_2,float *param_3,float *param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  bool tmp_b7;
  
  tmp_f1 = *param_1;
  tmp_f2 = *param_2;
  *param_1 = tmp_f1 - tmp_f2;
  tmp_f3 = param_1[1];
  tmp_f4 = param_2[1];
  param_1[1] = tmp_f3 - tmp_f4;
  tmp_f5 = param_1[2];
  tmp_f6 = param_2[2];
  param_1[2] = tmp_f5 - tmp_f6;
  tmp_f1 = (tmp_f1 - tmp_f2) - *param_3;
  *param_1 = tmp_f1;
  tmp_f2 = (tmp_f3 - tmp_f4) - param_3[1];
  param_1[1] = tmp_f2;
  tmp_f3 = (tmp_f5 - tmp_f6) - param_3[2];
  param_1[2] = tmp_f3;
  tmp_b7 = false;
  if (((int)ROUND(tmp_f2 - param_4[1]) + 0x17U < 0x2f) &&
     ((int)ROUND(tmp_f1 - *param_4) + 0x17U < 0x2f)) {
    tmp_b7 = ABS(tmp_f3 - param_4[2]) < 45.0;
  }
  return tmp_b7;
}

bool nitrox_CreateDirectory(uint32_t param_1)
{
  uint tmp_u1;
  uint tmp_u2;
  int tmp_i3;
  bool tmp_b4;
  stat local_364;
  char local_30c [4];
  uint32_t local_308 [191];
  
  local_30c[0] = '\0';
  local_30c[1] = '\0';
  local_30c[2] = '\0';
  local_30c[3] = '\0';
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_308 + tmp_u2) = 0;
    *(uint32_t *)((int)local_308 + tmp_u2 + 4) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xf8);
  *(uint32_t *)((int)local_308 + tmp_u2 + 8) = 0;
  local_308[0x3f] = 0;
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x100) = 0;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x104) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xf8);
  *(uint32_t *)((int)local_308 + tmp_u2 + 0x108) = 0;
  local_308[0x7f] = 0;
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x200) = 0;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x204) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xf8);
  *(uint32_t *)((int)local_308 + tmp_u2 + 0x208) = 0;
  trap_Cvar_VariableStringBuffer("fs_homepath",local_308 + 0x7f,0x100);
  trap_Cvar_VariableStringBuffer("fs_game",local_308 + 0x3f,0x100);
  Com_sprintf(local_30c,0x100,"%s/%s/%s",local_308 + 0x7f,local_308 + 0x3f,param_1);
  tmp_i3 = __xstat(3,local_30c,&local_364);
  if ((tmp_i3 == -1) || (tmp_b4 = true, (local_364.GHIDRA_FIELD(st_mode, 1, 1) & 0x40) == 0)) {
    tmp_i3 = mkdir(local_30c,0x1c0);
    tmp_b4 = tmp_i3 == 0;
  }
  return tmp_b4;
}

uint8_t *
BG_BuildFilePath(char *param_1,uint32_t param_2,uint32_t param_3,uint8_t *param_4,
                uint32_t param_5)

{
  size_t tmp_s1;
  
  tmp_s1 = strlen(param_1);
  *param_4 = 0;
  Q_strcat(param_4,param_5,param_1);
  if (((tmp_s1 != 0) && (param_1[tmp_s1 - 1] != '/')) && (param_1[tmp_s1 - 1] != '\\')) {
    Q_strcat(param_4,param_5,&g_unk_0024ed91);
  }
  Q_strcat(param_4,param_5,param_2);
  Q_strcat(param_4,param_5,param_3);
  return param_4;
}

uint32_t nitrox_CrazyGravityCmd(int param_1,int param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  char local_e;
  char local_d;
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    Q_SayArgv(param_2 + 1,&local_e,2);
    if (local_e == '1') {
      if (local_d != '\0') goto LAB_000c9937;
      trap_Cvar_Set("n_crazyGravity",&g_unk_00258b23);
      tmp_pc2 = "cpm \"^xcrazygravity: ^2Enabled !\"";
    }
    else {
      if ((local_e != '0') || (local_d != '\0')) goto LAB_000c9937;
      trap_Cvar_Set("n_crazyGravity",&g_unk_0024bfa6);
      tmp_pc2 = "cpm \"^xcrazygravity: ^1Disabled!\"";
    }
    tmp_u3 = va(tmp_pc2);
    trap_SendServerCommand(0xffffffff,tmp_u3);
    return 1;
  }
LAB_000c9937:
  if (param_1 != 0) {
    tmp_u3 = va("print \"%s\"","^9usage : ^g!crazygravity [0|1]^7\n");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
    return 0;
  }
  G_shrubbot_print_part_8();
  return 0;
}

void Nit_GibAll(void)
{
  int *tmp_pi1;
  int tmp_i2;
  
  if (0 < g_unk_00abe93c) {
    tmp_i2 = 0;
    do {
      tmp_pi1 = &g_unk_00abe944 + tmp_i2;
      tmp_i2 = tmp_i2 + 1;
      G_Damage(g_entities + *tmp_pi1 * 0x600,0,0,0,0,0,0x28,0);
    } while (tmp_i2 < g_unk_00abe93c);
  }
  return;
}

void nitrox_bigBufferPrint(int param_1)
{
  size_t tmp_s1;
  uint tmp_u2;
  size_t tmp_s3;
  uint32_t tmp_u4;
  uint tmp_u5;
  uint16_t *tmp_pu6;
  char *__s;
  int tmp_i7;
  bool tmp_b8;
  uint32_t local_41a;
  uint16_t local_416;
  uint16_t auStack_414 [512];
  uint32_t uStack_14;
  
  uStack_14 = 0xd7929;
  tmp_s1 = strlen(&bigTextBuffer);
  if (0 < (int)tmp_s1) {
    tmp_i7 = 0;
    do {
      tmp_u5 = 0x3fa;
      local_41a = 0;
      tmp_b8 = ((uint)&local_416 & 2) != 0;
      tmp_pu6 = &local_416;
      if (tmp_b8) {
        local_416 = 0;
        tmp_u5 = 0x3f8;
        tmp_pu6 = auStack_414;
      }
      tmp_u2 = 0;
      do {
        *(uint32_t *)((int)tmp_pu6 + tmp_u2) = 0;
        *(uint32_t *)((int)tmp_pu6 + tmp_u2 + 4) = 0;
        tmp_u2 = tmp_u2 + 8;
      } while (tmp_u2 < (tmp_u5 & 0xfffffff8));
      if (!tmp_b8) {
        *(uint16_t *)((int)tmp_pu6 + tmp_u2) = 0;
      }
      __s = &bigTextBuffer + tmp_i7;
      tmp_s3 = strlen(__s);
      if (tmp_s3 < 1000) {
        tmp_u4 = va("print \"%s\"",__s);
        Q_strncpyz(&local_41a,tmp_u4,0x3fe);
        tmp_s3 = strlen(__s);
        tmp_i7 = tmp_i7 + tmp_s3;
      }
      else {
        tmp_u4 = va("print \"%s\"",__s);
        Q_strncpyz(&local_41a,tmp_u4,0x3fe);
        tmp_s3 = strnlen(&bigTextBuffer,1000);
        tmp_i7 = tmp_i7 + -2 + tmp_s3;
      }
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,&local_41a);
    } while (tmp_i7 < (int)tmp_s1);
  }
  return;
}

void nitrox_QueryScreenshot(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  long local_548;
  char local_544 [4];
  char local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1036];
  
  local_548 = 100;
  if (g_unk_02b9a334 == 0) {
    G_Printf("/!\\ NxAC: Can\'t query screenshots during this game session!\n");
  }
  else if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
    tmp_i1 = trap_Argc();
    if (tmp_i1 < 2) {
      G_Printf("usage: getss [name|slot#] (JPEG Quality)\n");
    }
    else {
      trap_Argv(1,local_540,0x24);
      tmp_i1 = trap_Argc();
      if (tmp_i1 < 3) {
        local_548 = 0x46;
      }
      else {
        trap_Argv(2,local_544,4);
        local_548 = strtol(local_544,(char **)0x0,10);
        nitrox_ClampInt(&local_548,0x41200000,0x42c80000);
      }
      if (local_540[0] != '\0') {
        tmp_i1 = ClientNumbersFromString(local_540,local_51c);
        if (tmp_i1 == 1) {
          tmp_i3 = local_51c[0] * 0x600 + g_unk_00abe8a4;
          tmp_i1 = NxAC_ClientActiveFileTransfer(local_51c[0]);
          if ((0 < tmp_i1) || (0 < *(int *)(*(int *)(tmp_i3 + 400) + 0xb3c))) {
            NxAC_ClearClientFileHandle(local_51c[0]);
            *(uint32_t *)(*(int *)(tmp_i3 + 400) + 0xb3c) = 0;
            *(uint32_t *)(*(int *)(tmp_i3 + 400) + 0xb44) = 0;
            *(uint32_t *)(*(int *)(tmp_i3 + 400) + 0xb40) = 0;
          }
          tmp_u2 = va("getss %d",local_548);
          trap_SendServerCommand((tmp_i3 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
          NxAC_Log(tmp_i3,1,0,"[SCREENSHOT] Requested by admin");
        }
        else {
          G_MatchOnePlayer(local_51c,local_41c,0x400);
          G_Printf("^1getss: %s\n",local_41c);
        }
      }
    }
  }
  else {
    G_Printf("/!\\ NxAC: Can\'t query screenshots during Warmup/Intermission\n");
  }
  return;
}

uint nitrox_SortByKDRatio(int *param_1,int *param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  long double tmp_l4;
  long double tmp_l5;
  
  tmp_i2 = *param_1 * 0x54dc + level;
  tmp_i1 = level + *param_2 * 0x54dc;
  if (*(int *)(tmp_i2 + 0xbc4) < 0) {
    return 1;
  }
  if (*(int *)(tmp_i1 + 0xbc4) < 0) {
    return 0xffffffff;
  }
  if (*(int *)(tmp_i2 + 0x5ac) == 1) {
    return 1;
  }
  if (*(int *)(tmp_i1 + 0x5ac) == 1) {
    return 0xffffffff;
  }
  if (*(int *)(tmp_i2 + 3000) == 3) {
    if (*(int *)(tmp_i1 + 3000) != 3) {
      return 1;
    }
    if (*(int *)(tmp_i2 + 0xbbc) < *(int *)(tmp_i1 + 0xbbc)) {
      return 0xffffffff;
    }
    return (uint)(*(int *)(tmp_i1 + 0xbbc) < *(int *)(tmp_i2 + 0xbbc));
  }
  if (*(int *)(tmp_i1 + 3000) == 3) {
    return 0xffffffff;
  }
  if (*(int *)(tmp_i2 + 0xb8c) == 0) {
    if (*(int *)(tmp_i2 + 0xc74) < 1) goto LAB_000ea030;
    tmp_l4 = (long double)*(int *)(tmp_i2 + 0xc7c) / (long double)*(int *)(tmp_i2 + 0xc74);
    if (*(int *)(tmp_i1 + 0xb8c) != 0) goto LAB_000e9f3b;
LAB_000e9fde:
    if (0 < *(int *)(tmp_i1 + 0xc74)) {
      tmp_l5 = (long double)*(int *)(tmp_i1 + 0xc7c) / (long double)*(int *)(tmp_i1 + 0xc74);
      goto LAB_000e9f80;
    }
  }
  else {
    tmp_i3 = (&g_unk_02b99230)[*(int *)(tmp_i2 + 0xa0) * 0x10] + *(int *)(tmp_i2 + 0xb4c);
    if (tmp_i3 < 1) {
LAB_000ea030:
      tmp_l4 = (long double)0;
    }
    else {
      tmp_l4 = (long double)
              ((&g_unk_00abe8ac)[(*(int *)(tmp_i2 + 0xa0) + 0x836a6) * 0x10] + *(int *)(tmp_i2 + 0xb48))
              / (long double)tmp_i3;
    }
    if (*(int *)(tmp_i1 + 0xb8c) == 0) goto LAB_000e9fde;
LAB_000e9f3b:
    tmp_i2 = (&g_unk_02b99230)[*(int *)(tmp_i1 + 0xa0) * 0x10] + *(int *)(tmp_i1 + 0xb4c);
    if (0 < tmp_i2) {
      tmp_l5 = (long double)
              ((&g_unk_00abe8ac)[(*(int *)(tmp_i1 + 0xa0) + 0x836a6) * 0x10] + *(int *)(tmp_i1 + 0xb48))
              / (long double)tmp_i2;
      goto LAB_000e9f80;
    }
  }
  tmp_l5 = (long double)0;
LAB_000e9f80:
  if (tmp_l5 < tmp_l4) {
    return 0xffffffff;
  }
  return (uint)(tmp_l4 < tmp_l5);
}

void nitrox_ResetNumObjectives(void)
{
  numobjectives = 0;
  g_unk_00abfa98 = 0;
  return;
}

uint32_t nitrox_CustomVoteDescription(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  char *tmp_pc2;
  uint8_t local_41c [1036];
  
  if (param_2 == 0) {
    tmp_pc2 = "\\callvote";
  }
  else {
    tmp_pc2 = "\\ref";
  }
  if (param_1 != 0) {
    trap_Argv(2,local_41c,0x400);
    tmp_i1 = Q_stricmp(local_41c,&g_unk_0026f751);
    if (tmp_i1 == 0) {
      trap_Argv(1,local_41c,0x400);
      G_refPrintf(param_1,"\nUsage: ^3%s %s^7\n  %s\n",tmp_pc2,local_41c,
                  (&CustomVotes)[param_3] + 0x114);
      return 1;
    }
  }
  return 0;
}

int nitmod_customVoteCmd
              (int param_1,uint32_t param_2,int param_3,uint32_t param_4,uint32_t param_5)

{
  bool tmp_b1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  int *tmp_pi6;
  
  tmp_i2 = nitrox_GetAdminLevel(param_1,0);
  if (((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) && (CustomVotes != 0)) {
    tmp_b1 = false;
    tmp_i5 = 0;
    tmp_i3 = CustomVotes;
    tmp_pi6 = &g_unk_02db0d44;
    do {
      tmp_i3 = Q_stricmp(param_3,tmp_i3);
      if (tmp_i3 == 0) {
        tmp_i5 = 0;
        tmp_i3 = *(int *)(tmp_pi6[-1] + 0x714);
        while (tmp_i3 != -1) {
          if (tmp_i2 == tmp_i3) {
            tmp_b1 = true;
            break;
          }
          tmp_i5 = tmp_i5 + 1;
          tmp_i3 = *(int *)(tmp_pi6[-1] + 0x714 + tmp_i5 * 4);
        }
      }
      tmp_i3 = *tmp_pi6;
      tmp_pi6 = tmp_pi6 + 1;
    } while (tmp_i3 != 0);
    if ((tmp_i5 != 0) && (!tmp_b1)) {
      G_refPrintf(param_1,"^1callvote error: ^3Your admin level is not allowed to call this vote.");
      return -1;
    }
  }
  if (param_3 == 0) {
    tmp_u4 = va(&g_unk_0026fe3c,(&CustomVotes)[g_unk_00abef70] + 0x314);
    trap_SendConsoleCommand(2,tmp_u4);
    tmp_i2 = 0;
    if (*(char *)((&CustomVotes)[g_unk_00abef70] + 0x214) != '\0') {
      tmp_u4 = va(&g_unk_0025a5ea,(&CustomVotes)[g_unk_00abef70] + 0x214);
      trap_SendServerCommand(0xffffffff,tmp_u4);
    }
  }
  else {
    tmp_i2 = nitrox_CustomVoteDescription(param_1,param_5,param_2);
    tmp_i2 = -(uint)(tmp_i2 != 0);
  }
  return tmp_i2;
}

void nitrox_SpawnArtyHint(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i3 = G_Spawn();
  tmp_i2 = g_unk_00abe908;
  *(uint32_t *)(tmp_i3 + 4) = 0x3a;
  *(int *)(tmp_i3 + 0x29c) = tmp_i2 + 1;
  *(void **)(tmp_i3 + 0x2a4) = artilleryHintThink;
  *(uint32_t *)(tmp_i3 + 0x128) = 0x20;
  *(char **)(tmp_i3 + 0x1a4) = "arty_hint";
  *(uint32_t *)(tmp_i3 + 0x180) = **(uint32_t **)(param_1 + 0x218);
  *(uint32_t *)(tmp_i3 + 0xac) = **(uint32_t **)(param_1 + 0x218);
  *(uint32_t *)(tmp_i3 + 0x218) = *(uint32_t *)(param_1 + 0x218);
  tmp_u1 = *(uint32_t *)(*(int *)(*(int *)(param_1 + 0x218) + 400) + 3000);
  *(uint32_t *)(tmp_i3 + 0x1d4) = 0x6000081;
  *(uint32_t *)(tmp_i3 + 0xc) = 0;
  *(uint32_t *)(tmp_i3 + 0x108) = tmp_u1;
  *(uint32_t *)(tmp_i3 + 0x10) = *(uint32_t *)(param_1 + 0x10);
  *(uint32_t *)(tmp_i3 + 0x18) = *(uint32_t *)(param_1 + 0x18);
  *(uint32_t *)(tmp_i3 + 0x1c) = *(uint32_t *)(param_1 + 0x1c);
  *(uint32_t *)(tmp_i3 + 0x20) = *(uint32_t *)(param_1 + 0x20);
  *(uint32_t *)(tmp_i3 + 0x168) = *(uint32_t *)(param_1 + 0x18);
  *(uint32_t *)(tmp_i3 + 0x16c) = *(uint32_t *)(param_1 + 0x1c);
  *(uint32_t *)(tmp_i3 + 0x170) = *(uint32_t *)(param_1 + 0x20);
  trap_LinkEntity(tmp_i3);
  return;
}

void nitrox_DrawHitboxesOnShoot(uint8_t *param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  long double tmp_l5;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x1092a9;
  if (0 < g_unk_00abe938) {
    tmp_i4 = 0;
    tmp_i2 = g_unk_00abe938;
    do {
      while( true ) {
        tmp_i3 = (&g_unk_00abe944)[tmp_i4] * 0x600;
        if ((((*(int *)(g_entities + tmp_i3 + 0x194) != 0) &&
             (tmp_i1 = *(int *)(g_entities + tmp_i3 + 400), g_entities + tmp_i3 != param_1)) &&
            (*(int *)(tmp_i1 + 3000) != 3)) &&
           (((*(int *)(g_entities + tmp_i3 + 0x120) != 0 && ((*(byte *)(tmp_i1 + 0xd) & 0x40) == 0))
            && ((*(int *)(tmp_i1 + 4) == 3 || (*(int *)(tmp_i1 + 4) == 0)))))) break;
        tmp_i4 = tmp_i4 + 1;
        if (tmp_i2 <= tmp_i4) {
          return;
        }
      }
      local_28 = *(float *)(g_entities + tmp_i3 + 0x134);
      local_24 = *(float *)(g_entities + tmp_i3 + 0x138);
      local_20 = *(uint32_t *)(g_entities + tmp_i3 + 0x13c);
      local_34 = *(float *)(g_entities + tmp_i3 + 0x140);
      local_30 = *(float *)(g_entities + tmp_i3 + 0x144);
      local_2c = *(float *)(g_entities + tmp_i3 + 0x148);
      if ((int)GHIDRA_FIELD(g_hitboxes, 12, 4) < 1) {
        if ((g_realBody[0xc] & 1) != 0) {
          local_34 = local_34 - 3.0;
          local_28 = local_28 + 3.0;
          local_30 = local_30 - 3.0;
          local_24 = local_24 + 3.0;
        }
        tmp_l5 = (long double)nitrox_HitboxHeight(g_entities + tmp_i3,param_1);
        local_2c = (float)tmp_l5;
      }
      tmp_i4 = tmp_i4 + 1;
      G_RailBox(tmp_i3 + 0x93e608,&local_28,&local_34,&colorWhite,0xffffffff);
      tmp_i2 = g_unk_00abe938;
    } while (tmp_i4 < g_unk_00abe938);
  }
  return;
}

uint32_t
Bullet_Fire_Extended
          (uint32_t *param_1,int *param_2,float *param_3,uint32_t param_4,uint32_t param_5,
          int param_6,int param_7,int param_8)

{
  float tmp_f1;
  bool tmp_b2;
  bool tmp_b3;
  int tmp_i4;
  uint32_t tmp_u5;
  bool tmp_b6;
  bool tmp_b7;
  long double tmp_l8;
  long double tmp_l9;
  float tmp_f10;
  float tmp_f11;
  float tmp_f12;
  float tmp_f13;
  float tmp_f14;
  float local_98;
  float local_94;
  float local_90;
  uint8_t local_8c [8];
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  int local_58;
  uint8_t local_54 [8];
  float local_4c;
  
  if (*(int *)(g_entities + *param_2 * 0x600 + 400) == 0) {
    tmp_b7 = false;
  }
  else {
    tmp_b7 = false;
    if (*(int *)(g_entities + *param_2 * 0x600 + 0x120) == 1) {
      *(int *)(g_entities + *param_2 * 0x600 + 0x120) = 0;
      tmp_b7 = true;
    }
  }
  if (GHIDRA_FIELD(g_hitboxes, 12, 4) == 0) {
    tmp_i4 = G_WeaponCanGib(*(uint32_t *)(ammoTableMP + param_2[0x3a] * 0x48 + 0x3c));
    G_Trace(param_1,local_8c,param_3,0,0,param_4,*param_1,0x6000001,tmp_i4 == 0,1);
    tmp_i4 = G_WeaponCanGib(*(uint32_t *)(ammoTableMP + param_2[0x3a] * 0x48 + 0x3c));
    G_Trace(param_1,local_54,param_3,0,0,param_4,*param_1,0x6000039,tmp_i4 == 0,0);
    tmp_b2 = local_84 != local_4c;
  }
  else {
    G_TraceNew(param_1,local_8c,local_54,param_3,0,0,param_4,*param_1,0x6000001);
    tmp_b2 = local_84 != local_4c;
  }
  tmp_b6 = local_4c != 1.0;
  if (tmp_b7) {
    *(uint32_t *)(g_entities + *param_2 * 0x600 + 0x120) = 1;
  }
  if ((GHIDRA_FIELD(g_debugBullets, 12, 4) & 1) != 0) {
    tmp_u5 = tv(0x3f800000,0,0);
    G_RailTrail(param_3,&local_80,tmp_u5);
  }
  tmp_b7 = false;
  if (*(int *)(g_entities + local_58 * 0x600 + 0x2cc) != 0) {
    tmp_b7 = *(int *)(g_entities + local_58 * 0x600 + 400) != 0;
  }
  local_98 = local_80;
  local_94 = local_7c;
  local_90 = local_78;
  tmp_f10 = floorf(local_80);
  tmp_f11 = ceilf(local_80);
  tmp_b3 = local_80 < (float)param_2[0x17];
  local_80 = tmp_f10;
  if (tmp_b3) {
    local_80 = tmp_f11;
  }
  tmp_f10 = floorf(local_7c);
  tmp_f11 = ceilf(local_7c);
  tmp_b3 = local_7c < (float)param_2[0x18];
  local_7c = tmp_f10;
  if (tmp_b3) {
    local_7c = tmp_f11;
  }
  tmp_f10 = floorf(local_78);
  tmp_f11 = ceilf(local_78);
  tmp_b3 = local_78 < (float)param_2[0x19];
  local_78 = tmp_f10;
  if (tmp_b3) {
    local_78 = tmp_f11;
  }
  tmp_i4 = Q_stricmp(*(uint32_t *)(g_entities + local_58 * 0x600 + 0x1a4),"func_leaky");
  if (tmp_i4 == 0) {
    tmp_i4 = nitrox_TempEventFromQueue(&local_98,0x4b);
    *(float *)(tmp_i4 + 0x5c) = local_98;
    *(float *)(tmp_i4 + 0x60) = local_94;
    *(uint32_t *)(tmp_i4 + 0x54) = 0x4d2;
    *(float *)(tmp_i4 + 100) = local_90;
    *(uint32_t *)(tmp_i4 + 0xf4) = 0x2694;
    *(float *)(tmp_i4 + 0x68) = local_74;
    *(float *)(tmp_i4 + 0x6c) = local_70;
    *(float *)(tmp_i4 + 0x70) = local_6c;
  }
  tmp_f11 = local_80;
  tmp_f10 = floorf(local_80);
  tmp_f12 = ceilf(tmp_f11);
  tmp_f14 = local_7c;
  if (tmp_f11 < *param_3) {
    tmp_f10 = tmp_f12;
  }
  local_80 = tmp_f10;
  tmp_f11 = floorf(local_7c);
  tmp_f13 = ceilf(tmp_f14);
  tmp_f12 = local_78;
  if (tmp_f14 < param_3[1]) {
    tmp_f11 = tmp_f13;
  }
  local_7c = tmp_f11;
  tmp_f14 = floorf(local_78);
  tmp_f13 = ceilf(tmp_f12);
  local_78 = tmp_f14;
  if (tmp_f12 < param_3[2]) {
    local_78 = tmp_f13;
  }
  if (param_7 != 0) {
    local_98 = tmp_f10 - muzzleTrace;
    local_94 = tmp_f11 - g_unk_02e432e4;
    local_90 = local_78 - g_unk_02e432e8;
    tmp_l9 = (long double)VectorLength(&local_98);
    tmp_l9 = (long double)1 - ((tmp_l9 - (long double)1500.0) / (long double)1000.0) * (long double)0.5;
    if (tmp_l9 < (long double)1) {
      tmp_l8 = (long double)0.5;
      if ((long double)0.5 <= tmp_l9) {
        tmp_l8 = tmp_l9;
      }
    }
    else {
      tmp_l8 = (long double)1;
    }
    param_6 = (int)ROUND((long double)param_6 * tmp_l8);
  }
  if (param_8 != 0) {
    if (tmp_b7) {
      tmp_i4 = nitrox_TempEventFromQueue(&local_80,0x2e);
      *(uint32_t *)(tmp_i4 + 0xbc) = *(uint32_t *)(g_entities + local_58 * 0x600);
    }
    else {
      tmp_i4 = nitrox_TempEventFromQueue(&local_80,0x2f);
      if ((bool)(tmp_b6 & tmp_b2)) {
        local_98 = local_80 - *param_3;
        local_94 = local_7c - param_3[1];
        local_90 = local_78 - param_3[2];
        tmp_l9 = (long double)VectorLength(&local_98);
        *(float *)(tmp_i4 + 0x68) = (float)((long double)(local_4c * 8192.0) / tmp_l9);
      }
      else {
        *(uint32_t *)(tmp_i4 + 0x68) = 0;
      }
      tmp_f10 = (g_unk_02e432f4 * local_6c + g_unk_02e432f0 * local_70 + forward * local_74) * -2.0;
      local_98 = local_74 * tmp_f10 + forward;
      local_94 = local_70 * tmp_f10 + g_unk_02e432f0;
      local_90 = tmp_f10 * local_6c + g_unk_02e432f4;
      VectorNormalize(&local_98);
      tmp_u5 = DirToByte(&local_98);
      *(uint32_t *)(tmp_i4 + 0xbc) = tmp_u5;
      *(uint32_t *)(tmp_i4 + 0x90) = 0x3ff;
    }
    *(int *)(tmp_i4 + 0x8c) = *param_2;
    *(int *)(tmp_i4 + 0xac) = param_2[0x2b];
  }
  if (tmp_b7) {
    if ((int)GHIDRA_FIELD(g_debugBullets, 12, 4) < 2) goto LAB_001098bf;
  }
  else if (-2 < (int)GHIDRA_FIELD(g_debugBullets, 12, 4)) goto LAB_001098bf;
  tmp_i4 = local_58 * 0x600;
  local_98 = *(float *)(g_entities + tmp_i4 + 0x168) + *(float *)(g_entities + tmp_i4 + 0x134);
  local_94 = *(float *)(g_entities + tmp_i4 + 0x16c) + *(float *)(g_entities + tmp_i4 + 0x138);
  local_90 = *(float *)(g_entities + tmp_i4 + 0x170) + *(float *)(g_entities + tmp_i4 + 0x13c);
  tmp_f10 = *(float *)(g_entities + tmp_i4 + 0x168);
  tmp_f11 = *(float *)(g_entities + tmp_i4 + 0x140);
  tmp_f14 = *(float *)(g_entities + tmp_i4 + 0x16c);
  tmp_f12 = *(float *)(g_entities + tmp_i4 + 0x144);
  tmp_f13 = *(float *)(g_entities + tmp_i4 + 0x170);
  tmp_f1 = *(float *)(g_entities + tmp_i4 + 0x148);
  tmp_i4 = nitrox_TempEventFromQueue(&local_98,0x32);
  *(float *)(tmp_i4 + 0x68) = tmp_f10 + tmp_f11;
  *(float *)(tmp_i4 + 0x6c) = tmp_f14 + tmp_f12;
  *(uint32_t *)(tmp_i4 + 0xf8) = 1;
  *(float *)(tmp_i4 + 0x70) = tmp_f13 + tmp_f1;
LAB_001098bf:
  tmp_i4 = local_58 * 0x600;
  if (*(int *)(g_entities + tmp_i4 + 0x2cc) != 0) {
    G_Damage(g_entities + tmp_i4,param_2,param_2,&forward,&local_80,param_6,~-(param_7 == 0) & 0x10,
             *(uint32_t *)(ammoTableMP + param_2[0x3a] * 0x48 + 0x3c));
    if ((*(int *)(g_entities + tmp_i4 + 4) == 0xe) &&
       (*(int *)(g_entities + tmp_i4 + 0x2c8) <= param_6)) {
      tmp_u5 = Bullet_Fire_Extended(g_entities + tmp_i4,param_2,&local_80,param_4,0,param_6,param_7,0)
      ;
      return tmp_u5;
    }
  }
  return 1;
}

void nitrox_ClampFloat(float *param_1,float param_2,float param_3)
{
  float tmp_f1;
  
  tmp_f1 = *param_1;
  if (tmp_f1 < param_2) {
    *param_1 = param_2;
    tmp_f1 = param_2;
  }
  if (param_3 < tmp_f1) {
    *param_1 = param_3;
  }
  return;
}

void nitrox_ClampInt(int *param_1,float param_2,float param_3)
{
  float tmp_f1;
  
  tmp_f1 = (float)*param_1;
  if (tmp_f1 < param_2) {
    *param_1 = (int)ROUND(param_2);
    tmp_f1 = (float)(int)ROUND(param_2);
  }
  if (param_3 < tmp_f1) {
    *param_1 = (int)ROUND(param_3);
  }
  return;
}

void nitrox_stripLeadingSpaces(char *param_1)
{
  char tmp_c1;
  char *tmp_pc2;
  
  tmp_c1 = *param_1;
  tmp_pc2 = param_1;
  while (tmp_c1 == ' ') {
    tmp_pc2 = tmp_pc2 + 1;
    tmp_c1 = *tmp_pc2;
  }
  while (tmp_c1 != '\0') {
    tmp_pc2 = tmp_pc2 + 1;
    *param_1 = tmp_c1;
    param_1 = param_1 + 1;
    tmp_c1 = *tmp_pc2;
  }
  *param_1 = '\0';
  return;
}

uint32_t nitrox_XPSave_LoadXP(int param_1)
{
  uint32_t *tmp_pu1;
  uint tmp_u2;
  uint tmp_u3;
  uint32_t tmp_u4;
  size_t tmp_s5;
  int tmp_i6;
  int tmp_i7;
  char *tmp_pc8;
  int tmp_i9;
  int tmp_i10;
  double tmp_d11;
  uint32_t local_81c;
  uint32_t local_818 [514];
  
  local_81c = 0;
  tmp_u2 = 0;
  do {
    tmp_u3 = tmp_u2;
    *(uint32_t *)((int)local_818 + tmp_u3) = 0;
    *(uint32_t *)((int)local_818 + tmp_u3 + 4) = 0;
    tmp_u2 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0x3f8);
  *(uint32_t *)((int)local_818 + tmp_u3 + 8) = 0;
  local_818[0xff] = 0;
  tmp_u2 = 0;
  do {
    tmp_u3 = tmp_u2;
    *(uint32_t *)((int)local_818 + tmp_u3 + 0x400) = 0;
    *(uint32_t *)((int)local_818 + tmp_u3 + 0x404) = 0;
    tmp_u2 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0x3f8);
  *(uint32_t *)((int)local_818 + tmp_u3 + 0x408) = 0;
  tmp_u4 = 1;
  if ((g_unk_02af58b8 != 0) && ((g_XPSave[0xc] & 1) != 0)) {
    if ((param_1 == 0) || (tmp_i10 = *(int *)(param_1 + 400), tmp_i10 == 0)) {
      tmp_u4 = 0;
    }
    else if (*(int *)(tmp_i10 + 0x54d8) == 0) {
      tmp_s5 = strlen((char *)(tmp_i10 + 0x61c));
      tmp_u4 = 0;
      if (tmp_s5 == 0x20) {
        if (Users != 0) {
          tmp_i9 = 0;
          tmp_i7 = Users;
          do {
            tmp_i6 = strcmp((char *)(tmp_i10 + 0x61c),(char *)(tmp_i7 + 4));
            if (tmp_i6 == 0) {
              Q_strncpyz(&local_81c,tmp_i7 + 0xc78,0x400);
              tmp_i10 = *(int *)((&Users)[tmp_i9] + 0xc74);
              if (tmp_i10 != 0) {
                decode64(&local_81c);
                tmp_i7 = G_GetCurrentTime();
                tmp_i7 = tmp_i7 - tmp_i10;
                if (((g_XPSave[0xc] & 4) == 0) && ((int)GHIDRA_FIELD(g_XPSaveMaxAge, 12, 4) < tmp_i7)) {
                  trap_SendServerCommand
                            ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                             "print \"^7N^1!^7tmod^g: ^8Your saved XP has expired...\n");
                  return 1;
                }
                tmp_i10 = 0;
                do {
                  tmp_u4 = va(&g_unk_0025cd0d,tmp_i10);
                  tmp_pc8 = (char *)Info_ValueForKey(&local_81c,tmp_u4);
                  tmp_d11 = strtod(tmp_pc8,(char **)0x0);
                  *(float *)(*(int *)(param_1 + 400) + 0xbf4 + tmp_i10 * 4) =
                       (float)(int)ROUND(tmp_d11);
                  tmp_i10 = tmp_i10 + 1;
                  *(float *)(*(int *)(param_1 + 400) + 0xc2c) =
                       (float)(int)ROUND(tmp_d11) + *(float *)(*(int *)(param_1 + 400) + 0xc2c);
                } while (tmp_i10 != 7);
                *(int *)(*(int *)(param_1 + 400) + 0xf0) =
                     (int)ROUND(*(float *)(*(int *)(param_1 + 400) + 0xc2c));
                if ((GHIDRA_FIELD(g_XPDecay, 12, 4) & 3) == 1) {
                  G_XPDecay(param_1,tmp_i7,1);
                }
                tmp_pu1 = local_818 + 0xff;
                G_CalcRank(*(uint32_t *)(param_1 + 400));
                BG_PlayerStateToEntityState(*(uint32_t *)(param_1 + 400),param_1,g_unk_00abe908,1);
                G_shrubbot_duration(tmp_i7,tmp_pu1,0x400);
                tmp_i10 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
                G_LogPrintf("| [XPSave::LoadXP] Client %d (%s) Restored XP from %s ago\n",tmp_i10,
                            *(int *)(param_1 + 400) + 0x5f8,tmp_pu1);
                tmp_u4 = va("print \"^7N^1!^7tmod^g: ^5Restored XP from ^g%s ^5ago\n\"",tmp_pu1);
                trap_SendServerCommand(tmp_i10,tmp_u4);
                return 1;
              }
              tmp_pc8 = "print \"^7N^1!^7tmod^g: ^8No XP found in database for your NGUID.\n";
              goto LAB_0011392e;
            }
            tmp_i9 = tmp_i9 + 1;
            tmp_i7 = (&Users)[tmp_i9];
          } while (tmp_i7 != 0);
        }
        tmp_pc8 = "print \"^7N^1!^7tmod^g: ^8User not found in database.\n";
LAB_0011392e:
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc8);
        tmp_u4 = 1;
      }
    }
  }
  return tmp_u4;
}

uint nitrox_XPSave_WriteXP(int param_1)
{
  uint tmp_u1;
  size_t tmp_s2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint tmp_u7;
  int tmp_i8;
  uint local_45c;
  uint8_t local_440 [36];
  uint32_t local_41c;
  uint32_t local_418 [257];
  uint32_t uStack_14;
  
  uStack_14 = 0x1139dd;
  local_41c = 0;
  tmp_u7 = 0;
  do {
    tmp_u1 = tmp_u7;
    *(uint32_t *)((int)local_418 + tmp_u1) = 0;
    *(uint32_t *)((int)local_418 + tmp_u1 + 4) = 0;
    tmp_u7 = tmp_u1 + 8;
  } while (tmp_u1 + 8 < 0x3f8);
  *(uint32_t *)((int)local_418 + tmp_u1 + 8) = 0;
  if ((param_1 == 0) || (g_unk_02af58b8 == 0)) {
    return 0;
  }
  tmp_i6 = *(int *)(param_1 + 400);
  tmp_u7 = 0;
  if ((tmp_i6 != 0) && (*(int *)(tmp_i6 + 0x54d8) == 0)) {
    tmp_s2 = strlen((char *)(tmp_i6 + 0x61c));
    if (tmp_s2 != 0x20) {
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,"getnguid");
      return 0;
    }
    local_45c = GHIDRA_FIELD(g_XPSave, 12, 4) & 1;
    if (((g_OmniBotFlags[0xc] & 1) != 0) &&
       (local_45c = tmp_u7, (*(byte *)(param_1 + 0x128) & 8) == 0)) {
      local_45c = GHIDRA_FIELD(g_XPSave, 12, 4) & 1;
    }
    tmp_u3 = G_GetCurrentTime();
    tmp_u4 = nitrox_XPSave_encode64(param_1,&local_41c);
    tmp_i8 = 0;
    Q_strncpyz(&local_41c,tmp_u4,0x400);
    Q_strncpyz(local_440,*(int *)(param_1 + 400) + 0x5f8,0x24);
    tmp_i6 = Users;
    while (tmp_i6 != 0) {
      if ((*(char *)(tmp_i6 + 4) != '\0') &&
         (tmp_i5 = strcmp((char *)(tmp_i6 + 4),(char *)(*(int *)(param_1 + 400) + 0x61c)), tmp_i5 == 0)
         ) {
        Q_strncpyz(tmp_i6 + 0x25,local_440,0x24);
        Q_strncpyz((&Users)[tmp_i8] + 0xc62,*(int *)(param_1 + 400) + 0x653,0x12);
        Q_strncpyz((&Users)[tmp_i8] + 0xc50,*(int *)(param_1 + 400) + 0xaf4,0x12);
        if (local_45c != 0) {
          G_LogPrintf("| [XPSave::WriteXP] Client %d (%s) XP Saved.\n",
                      (param_1 + -0x93e4a0 >> 9) * -0x55555555,*(int *)(param_1 + 400) + 0x5f8);
          Q_strncpyz((&Users)[tmp_i8] + 0xc78,&local_41c,0x400);
        }
        *(uint32_t *)((&Users)[tmp_i8] + 0xc74) = tmp_u3;
        tmp_u3 = 2;
        tmp_i6 = (&Users)[tmp_i8];
        goto LAB_00113c0a;
      }
      tmp_i8 = tmp_i8 + 1;
      tmp_i6 = (&Users)[tmp_i8];
    }
    tmp_i6 = AllocUser();
    tmp_u4 = nitrox_LevelPointer(0);
    *(uint32_t *)(tmp_i6 + 0x4c) = tmp_u4;
    Q_strncpyz(tmp_i6 + 0x25,local_440,0x24);
    Q_strncpyz(tmp_i6 + 4,*(int *)(param_1 + 400) + 0x61c,0x21);
    Q_strncpyz(tmp_i6 + 0xc62,*(int *)(param_1 + 400) + 0x653,0x12);
    Q_strncpyz(tmp_i6 + 0xc50,*(int *)(param_1 + 400) + 0xaf4,0x12);
    if (local_45c != 0) {
      Q_strncpyz(tmp_i6 + 0xc78,&local_41c,0x400);
    }
    *(uint32_t *)(tmp_i6 + 0xc74) = tmp_u3;
    (&Users)[tmp_i8] = tmp_i6;
    tmp_u3 = 1;
LAB_00113c0a:
    nitrox_SaveSingleUser(tmp_i6,tmp_u3);
    tmp_u7 = 1;
    nitrox_SetAdminPointers(param_1,(&Users)[tmp_i8]);
  }
  return tmp_u7;
}

void nitrox_XPSave_WriteAllXP(void)
{
  int tmp_i1;
  int tmp_i2;
  
  if (0 < g_unk_00abe938) {
    tmp_i2 = 0;
    do {
      while( true ) {
        tmp_i1 = (&g_unk_00abe944)[tmp_i2];
        if (g_unk_02af58b8 == 0) break;
        nitrox_XPSave_WriteXP(g_entities + tmp_i1 * 0x600);
        if ((g_entities[tmp_i1 * 0x600 + 0x128] & 8) != 0) goto LAB_00113e00;
LAB_00113e4a:
        tmp_i2 = tmp_i2 + 1;
        nitrox_SendStatsToMaster(g_entities + tmp_i1 * 0x600);
        if (g_unk_00abe938 <= tmp_i2) {
          return;
        }
      }
      if ((g_entities[tmp_i1 * 0x600 + 0x128] & 8) == 0) goto LAB_00113e4a;
LAB_00113e00:
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 < g_unk_00abe938);
  }
  return;
}

void nitrox_XPSave_ClearXP(void)
{
  int tmp_i1;
  int *tmp_pi2;
  
  if (Users != 0) {
    tmp_i1 = Users;
    tmp_pi2 = &g_unk_02db1044;
    do {
      Q_strncpyz(tmp_i1 + 0xc78,"UzBcMFxTMVwwXFMyXDBcUzNcMFxTNFwwXFM1XDBcUzZcMFw=",0x400);
      tmp_i1 = *tmp_pi2;
      tmp_pi2 = tmp_pi2 + 1;
    } while (tmp_i1 != 0);
  }
  return;
}

void nitrox_OpenCrashLog(void)
{
  time_t *ptVar1;
  uint tmp_u2;
  time_t tVar3;
  tm *__tp;
  uint8_t *tmp_pu4;
  time_t local_74 [26];
  
  tmp_u2 = 0;
  local_74[1] = 0;
  do {
    *(uint32_t *)((int)local_74 + tmp_u2 + 8) = 0;
    *(uint32_t *)((int)local_74 + tmp_u2 + 0xc) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x60);
  tVar3 = time(local_74);
  tmp_pu4 = &g_unk_0026ea14;
  if (tVar3 != 0) {
    __tp = localtime(local_74);
    tmp_pu4 = tstr_12663;
    strftime(tstr_12663,0x32,"%m-%d-%y_%H-%M-%S",__tp);
  }
  ptVar1 = local_74 + 1;
  Com_sprintf(ptVar1,100,"crash_%s_%s.log",&g_unk_00abe8c0,tmp_pu4);
  trap_FS_FOpenFile(ptVar1,&g_unk_00abe8b8,3);
  if (g_unk_00abe8b8 == 0) {
    G_Printf("^3WARNING: Couldn\'t open crashlog: %s\n",ptVar1);
  }
  return;
}

void Nit_SecShrubLogin(int param_1)
{
  char *tmp_pc1;
  int tmp_i2;
  char *tmp_pc3;
  bool tmp_b4;
  byte tmp_b5;
  char local_41c [1036];
  
  tmp_b5 = 0;
  if (((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) &&
     (*(int *)(*(int *)(param_1 + 400) + 0x54d8) == 0)) {
    trap_Argv(1,local_41c,0x400);
    tmp_b4 = *(int *)(*(int *)(param_1 + 400) + 0xf2c) == 0;
    if (tmp_b4) {
      tmp_i2 = 5;
      tmp_pc1 = g_secureShrubPassword + 0x10;
      tmp_pc3 = "none";
      do {
        if (tmp_i2 == 0) break;
        tmp_i2 = tmp_i2 + -1;
        tmp_b4 = *tmp_pc1 == *tmp_pc3;
        tmp_pc1 = tmp_pc1 + (uint)tmp_b5 * -2 + 1;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b5 * -2 + 1;
      } while (tmp_b4);
      if ((tmp_b4) || (g_secureShrubPassword[0x10] == '\0')) {
        trap_SendServerCommand
                  ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                   "print \"^1SecureShrubLogin: ^gSecure Shrubbot Login is disabled on this server.\n\""
                  );
        return;
      }
      tmp_i2 = trap_Argc();
      if (tmp_i2 < 2) {
        tmp_pc1 = "print \"^xusage: ^gsslogin [password]\n\"";
      }
      else {
        tmp_i2 = strcmp(local_41c,g_secureShrubPassword + 0x10);
        if (tmp_i2 == 0) {
          tmp_i2 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xf2c) = 1;
          trap_SendServerCommand(tmp_i2,"print \"^xSecureShrubLogin: ^gLogin successful.\n\"");
          ClientUserinfoChanged(tmp_i2);
          return;
        }
        tmp_pc1 = "print \"^1SecureShrubLogin error: ^9Invalid Password.\n\"";
      }
    }
    else {
      tmp_pc1 = "print \"^1SecureShrubLogin: ^gYou are already logged in.\n\"";
    }
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc1);
  }
  return;
}

void Nit_SecShrubLogout(int param_1)
{
  int tmp_i1;
  
  if (((param_1 != 0) && (tmp_i1 = *(int *)(param_1 + 400), tmp_i1 != 0)) &&
     (*(int *)(tmp_i1 + 0x54d8) == 0)) {
    if (*(int *)(tmp_i1 + 0xf2c) == 0) {
      trap_SendServerCommand
                ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                 "print \"^1SecureShrubLogin: ^gYou are not logged in.\n\"");
      return;
    }
    *(uint32_t *)(tmp_i1 + 0xf2c) = 0;
    tmp_i1 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand(tmp_i1,"print \"^xSecureShrubLogin: ^gLogged out.\n\"");
    ClientUserinfoChanged(tmp_i1);
  }
  return;
}

bool Nit_SecureShrubEnabled(void)
{
  int tmp_i1;
  byte *tmp_pb2;
  byte *tmp_pb3;
  bool tmp_b4;
  bool tmp_b5;
  
  tmp_i1 = 5;
  tmp_b4 = false;
  tmp_b5 = false;
  tmp_pb2 = g_secureShrubPassword + 0x10;
  tmp_pb3 = (byte *)0x261da9;
  do {
    if (tmp_i1 == 0) break;
    tmp_i1 = tmp_i1 + -1;
    tmp_b4 = *tmp_pb2 < *tmp_pb3;
    tmp_b5 = *tmp_pb2 == *tmp_pb3;
    tmp_pb2 = tmp_pb2 + 1;
    tmp_pb3 = tmp_pb3 + 1;
  } while (tmp_b5);
  return (!tmp_b4 && !tmp_b5) != tmp_b4 && g_secureShrubPassword[0x10] != '\0';
}

void Nit_SecureShrubError(uint32_t param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  
  tmp_u1 = va("^1%s error: ^9Secure Shrubbot Login is enabled on this server. \n ^9Log in using ^g/sslogin ^9and try again.^7\n"
             ,param_2);
  G_shrubbot_print(param_1,tmp_u1);
  return;
}

void nitmod_cp(int param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  
  if (param_1 != 0) {
    tmp_u1 = va("ncp %i",param_2);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
    return;
  }
  tmp_u1 = va("ncp %i",param_2);
  trap_SendServerCommand(0xffffffff,tmp_u1);
  return;
}

void nitmod_SendChargeTimes(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = va("ct %i %i %i %i %i %i %i %i %i %i",g_unk_02a983e4,g_unk_02a983e8,g_unk_02a983ec,g_unk_02a983f0,
             g_unk_02a983f4,g_unk_02a983f8,g_unk_02a983fc,g_unk_02a98400,g_unk_02a98404,g_unk_02a98408);
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
    return;
  }
  trap_SendServerCommand(0xffffffff,tmp_u1);
  return;
}

void nitmod_Sound_Global(uint32_t param_1)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  
  tmp_pu1 = &g_unk_0080dc08 + g_unk_02af58bc;
  if (g_unk_00abe908 - *(int *)((&level)[(int)tmp_pu1] + 0x1c0) < 300) {
    tmp_i2 = G_TempEntity(0,0x67);
  }
  else {
    *(uint32_t *)((&level)[(int)tmp_pu1] + 4) = 0xa2;
    tmp_i2 = g_unk_00abe908;
    *(int *)((&level)[(int)tmp_pu1] + 0x1c0) = g_unk_00abe908;
    *(int *)((&level)[(int)tmp_pu1] + 0x184) = tmp_i2;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x1c4) = 0;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x1c8) = 1;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x128) = 0;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x5e4) = 0;
    g_unk_02af58bc = (g_unk_02af58bc + 1) % 0x20;
    trap_LinkEntity((&level)[(int)tmp_pu1]);
    tmp_i2 = (&level)[(int)tmp_pu1];
  }
  *(uint32_t *)(tmp_i2 + 0xbc) = param_1;
  *(uint32_t *)(tmp_i2 + 0x128) = 0x20;
  return;
}

void Nit_SCLogin(int param_1)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  int tmp_i3;
  char *tmp_pc4;
  bool tmp_b5;
  byte tmp_b6;
  char local_41c [1036];
  
  tmp_b6 = 0;
  if (((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) &&
     (*(int *)(*(int *)(param_1 + 400) + 0x54d8) == 0)) {
    trap_Argv(1,local_41c,0x400);
    tmp_b5 = *(int *)(*(int *)(param_1 + 400) + 0xf30) == 0;
    if (tmp_b5) {
      tmp_i3 = 5;
      tmp_pc2 = shoutcastPassword + 0x10;
      tmp_pc4 = "none";
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_b5 = *tmp_pc2 == *tmp_pc4;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b6 * -2 + 1;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
      } while (tmp_b5);
      if ((tmp_b5) || (shoutcastPassword[0x10] == '\0')) {
        trap_SendServerCommand
                  ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                   "print \"^1Shoutcaster status is disabled on this server.\n\"");
        return;
      }
      tmp_i3 = trap_Argc();
      if (tmp_i3 < 2) {
        tmp_pc2 = "print \"^xusage: ^gsclogin [password]\n\"";
      }
      else {
        tmp_i3 = strcmp(local_41c,shoutcastPassword + 0x10);
        if (tmp_i3 == 0) {
          tmp_i3 = *(int *)(param_1 + 400);
          if (*(int *)(tmp_i3 + 3000) != 3) {
            SetTeam(param_1,"spectator",1,0xffffffff,0xffffffff,0);
            tmp_i3 = *(int *)(param_1 + 400);
          }
          *(uint32_t *)(tmp_i3 + 0xf30) = 1;
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xc88) = 3;
          tmp_u1 = va("cp \"%s\n^3has become a shoutcaster\n\"",*(int *)(param_1 + 400) + 0x5f8);
          trap_SendServerCommand(0xffffffff,tmp_u1);
          ClientUserinfoChanged((param_1 + -0x93e4a0 >> 9) * -0x55555555);
          return;
        }
        tmp_pc2 = "print \"^1Shoutcaster error: ^9Invalid Password.\n\"";
      }
    }
    else {
      tmp_pc2 = "print \"^1You are already shoutcaster.\n\"";
    }
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc2);
  }
  return;
}

void Nit_SCLogout(int param_1)
{
  int tmp_i1;
  
  if (((param_1 != 0) && (tmp_i1 = *(int *)(param_1 + 400), tmp_i1 != 0)) &&
     (*(int *)(tmp_i1 + 0x54d8) == 0)) {
    if (*(int *)(tmp_i1 + 0xf30) == 0) {
      trap_SendServerCommand
                ((param_1 + -0x93e4a0 >> 9) * -0x55555555,"print \"^1You are not a Shoutcaster.\n\""
                );
      return;
    }
    *(uint32_t *)(tmp_i1 + 0xf30) = 0;
    if (*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0) {
      *(uint32_t *)(*(int *)(param_1 + 400) + 0xc88) = 0;
    }
    ClientUserinfoChanged((param_1 + -0x93e4a0 >> 9) * -0x55555555);
  }
  return;
}

bool Nit_SCEnabled(void)
{
  int tmp_i1;
  byte *tmp_pb2;
  byte *tmp_pb3;
  bool tmp_b4;
  bool tmp_b5;
  
  tmp_i1 = 5;
  tmp_b4 = false;
  tmp_b5 = false;
  tmp_pb2 = shoutcastPassword + 0x10;
  tmp_pb3 = (byte *)0x261da9;
  do {
    if (tmp_i1 == 0) break;
    tmp_i1 = tmp_i1 + -1;
    tmp_b4 = *tmp_pb2 < *tmp_pb3;
    tmp_b5 = *tmp_pb2 == *tmp_pb3;
    tmp_pb2 = tmp_pb2 + 1;
    tmp_pb3 = tmp_pb3 + 1;
  } while (tmp_b5);
  return (!tmp_b4 && !tmp_b5) != tmp_b4 && shoutcastPassword[0x10] != '\0';
}

void nitmod_objective(uint param_1,int param_2,int param_3,int param_4,int param_5)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  if (param_3 == 0) {
    return;
  }
  if (param_4 == 0) {
    return;
  }
  tmp_i2 = *(int *)(param_4 + 400);
  if (tmp_i2 == 0) {
    return;
  }
  if (((param_1 & 0xfffffffb) != 0) || (param_2 < 0)) goto LAB_0011c400;
  if (2 < param_2) {
    if (4 < param_2) goto LAB_0011c400;
    if (param_5 != 0x15) {
      if ((param_5 == 0x16) || (param_5 == 0x19)) {
        *(int *)(tmp_i2 + 0xba4) = *(int *)(tmp_i2 + 0xba4) + 1;
        tmp_i2 = *(int *)(param_4 + 400);
      }
      goto LAB_0011c400;
    }
  }
  *(int *)(tmp_i2 + 0xb9c) = *(int *)(tmp_i2 + 0xb9c) + 1;
  tmp_i2 = *(int *)(param_4 + 400);
LAB_0011c400:
  tmp_u1 = va("ob %i %i %i %i %i",param_1,param_2,*(uint32_t *)(param_3 + 0x108),
             (param_4 + -0x93e4a0 >> 9) * -0x55555555,*(uint32_t *)(tmp_i2 + 3000));
  trap_SendServerCommand(0xffffffff,tmp_u1);
  return;
}

void Nit_HitSound(int param_1,uint32_t param_2)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  float local_28;
  float local_24;
  float local_20;
  
  if ((param_1 != 0) && (tmp_i3 = *(int *)(param_1 + 400), tmp_i3 != 0)) {
    tmp_pu1 = &g_unk_0080dc08 + g_unk_02af58bc;
    if (g_unk_00abe908 - *(int *)((&level)[(int)tmp_pu1] + 0x1c0) < 300) {
      tmp_i3 = G_TempEntity(tmp_i3 + 0x14,99);
    }
    else {
      *(uint32_t *)((&level)[(int)tmp_pu1] + 4) = 0x9e;
      tmp_i2 = g_unk_00abe908;
      *(int *)((&level)[(int)tmp_pu1] + 0x1c0) = g_unk_00abe908;
      *(int *)((&level)[(int)tmp_pu1] + 0x184) = tmp_i2;
      *(uint32_t *)((&level)[(int)tmp_pu1] + 0x1c4) = 0;
      *(uint32_t *)((&level)[(int)tmp_pu1] + 0x1c8) = 1;
      *(uint32_t *)((&level)[(int)tmp_pu1] + 0x128) = 0;
      *(uint32_t *)((&level)[(int)tmp_pu1] + 0x5e4) = 0;
      g_unk_02af58bc = (g_unk_02af58bc + 1) % 0x20;
      local_28 = (float)(int)ROUND(*(float *)(tmp_i3 + 0x14));
      local_24 = (float)(int)ROUND(*(float *)(tmp_i3 + 0x18));
      local_20 = (float)(int)ROUND(*(float *)(tmp_i3 + 0x1c));
      G_SetOrigin((&level)[(int)tmp_pu1],&local_28);
      trap_LinkEntity((&level)[(int)tmp_pu1]);
      tmp_i3 = (&level)[(int)tmp_pu1];
    }
    *(uint *)(tmp_i3 + 0x128) = *(uint *)(tmp_i3 + 0x128) | 0x800;
    *(uint32_t *)(tmp_i3 + 0xbc) = param_2;
    *(int *)(tmp_i3 + 300) = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  }
  return;
}

void nitmod_SendMapEndStats(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = *(int *)(param_1 + 400);
  tmp_u2 = va("mes %d %d %d %d %d",*(uint32_t *)(tmp_i1 + 0xf38),*(uint32_t *)(tmp_i1 + 0xf3c),
             *(uint32_t *)(tmp_i1 + 0xc7c),*(uint32_t *)(tmp_i1 + 0xc74),
             *(uint32_t *)(tmp_i1 + 0xdd0));
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  return;
}

bool nitmod_IsSimpleCSVar(uint8_t *param_1)
{
  return (((((((((param_1 == g_missileCams || param_1 == g_doubleJump) || param_1 == g_war) ||
               param_1 == g_noReload) || param_1 == g_filtercams) || param_1 == g_spectatorNames) ||
            param_1 == g_misc) || param_1 == n_proneDelay) || param_1 == n_dynamiteTimer) ||
         param_1 == n_crouchStandDelay) || param_1 == n_standCrouchDelay;
}

void nitmod_SimpleCS(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = va("scs %i %i %i %i %i %i %i %i %i %i %i",GHIDRA_FIELD(g_doubleJump, 12, 4),GHIDRA_FIELD(g_missileCams, 12, 4),
             GHIDRA_FIELD(g_war, 12, 4),GHIDRA_FIELD(g_noReload, 12, 4),GHIDRA_FIELD(g_filtercams, 12, 4),GHIDRA_FIELD(g_spectatorNames, 12, 4),
             GHIDRA_FIELD(g_misc, 12, 4),GHIDRA_FIELD(n_proneDelay, 12, 4),GHIDRA_FIELD(n_dynamiteTimer, 12, 4),GHIDRA_FIELD(n_crouchStandDelay, 12, 4),
             GHIDRA_FIELD(n_standCrouchDelay, 12, 4));
  if (param_1 == 0) {
    tmp_i2 = -1;
  }
  else {
    tmp_i2 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  }
  trap_SendServerCommand(tmp_i2,tmp_u1);
  return;
}

void nitmod_makeSC(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  char *tmp_pc3;
  int tmp_i4;
  char *tmp_pc5;
  bool tmp_b6;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1036];
  
  tmp_i2 = 5;
  tmp_b6 = false;
  tmp_pc3 = shoutcastPassword + 0x10;
  tmp_pc5 = "none";
  do {
    if (tmp_i2 == 0) break;
    tmp_i2 = tmp_i2 + -1;
    tmp_b6 = *tmp_pc3 == *tmp_pc5;
    tmp_pc3 = tmp_pc3 + 1;
    tmp_pc5 = tmp_pc5 + 1;
  } while (tmp_b6);
  if ((tmp_b6) || (shoutcastPassword[0x10] == '\0')) {
    G_Printf("^1Shoutcaster status is disabled on this server.\n");
  }
  else {
    tmp_i2 = Q_SayArgc();
    if (tmp_i2 < 2) {
      G_Printf("^9usage: ^gmakeshoutcaster ^7[name|slot#]^7\n");
    }
    else {
      Q_SayArgv(1,local_540,0x24);
      tmp_i2 = ClientNumbersFromString(local_540,local_51c);
      if (tmp_i2 == 1) {
        tmp_i4 = local_51c[0] * 0x600;
        tmp_i2 = *(int *)(g_entities + tmp_i4 + 400);
        if ((tmp_i2 != 0) && (*(int *)(tmp_i2 + 0x54d8) == 0)) {
          if (*(int *)(tmp_i2 + 0xf30) == 0) {
            if (*(int *)(tmp_i2 + 3000) != 3) {
              SetTeam(g_entities + tmp_i4,"spectator",1,0xffffffff,0xffffffff,0);
              tmp_i2 = *(int *)(g_entities + tmp_i4 + 400);
            }
            *(uint32_t *)(tmp_i2 + 0xf30) = 1;
            *(uint32_t *)(*(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0xc88) = 3;
            tmp_u1 = va("cp \"%s\n^3has become a shoutcaster\n\"",
                       *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8);
            trap_SendServerCommand(0xffffffff,tmp_u1);
            ClientUserinfoChanged((tmp_i4 >> 9) * -0x55555555);
          }
          else {
            G_Printf("%s ^1is already a shoutcaster.\n",tmp_i2 + 0x5f8);
          }
        }
      }
      else {
        G_MatchOnePlayer(local_51c,local_41c,0x400);
        G_Printf("^1makeshoutcaster %s\n",local_41c);
      }
    }
  }
  return;
}

void nitmod_removeSC(void)
{
  int *tmp_pi1;
  uint32_t tmp_u2;
  int tmp_i3;
  char *tmp_pc4;
  char *tmp_pc5;
  bool tmp_b6;
  uint8_t local_530 [36];
  int local_50c [64];
  uint8_t local_40c [1024];
  
  tmp_i3 = 5;
  tmp_b6 = false;
  tmp_pc4 = shoutcastPassword + 0x10;
  tmp_pc5 = "none";
  do {
    if (tmp_i3 == 0) break;
    tmp_i3 = tmp_i3 + -1;
    tmp_b6 = *tmp_pc4 == *tmp_pc5;
    tmp_pc4 = tmp_pc4 + 1;
    tmp_pc5 = tmp_pc5 + 1;
  } while (tmp_b6);
  if ((tmp_b6) || (shoutcastPassword[0x10] == '\0')) {
    G_Printf("^1Shoutcaster status is disabled on this server.\n");
  }
  else {
    tmp_i3 = Q_SayArgc();
    if (tmp_i3 < 2) {
      G_Printf("^9usage: ^gremoveshoutcaster ^7[name|slot#]^7\n");
    }
    else {
      Q_SayArgv(1,local_530,0x24);
      tmp_i3 = ClientNumbersFromString(local_530,local_50c);
      if (tmp_i3 == 1) {
        tmp_pi1 = (int *)(g_entities + local_50c[0] * 0x600 + 400);
        tmp_i3 = *tmp_pi1;
        if ((tmp_i3 != 0) && (*(int *)(tmp_i3 + 0x54d8) == 0)) {
          if (*(int *)(tmp_i3 + 0xf30) == 0) {
            G_Printf("%s ^1is not a shoutcaster.\n",tmp_i3 + 0x5f8);
          }
          else {
            *(uint32_t *)(tmp_i3 + 0xf30) = 0;
            tmp_i3 = *tmp_pi1;
            if (*(int *)(tmp_i3 + 0xc80) == 0) {
              *(uint32_t *)(tmp_i3 + 0xc88) = 0;
              tmp_i3 = *tmp_pi1;
            }
            tmp_u2 = va("cp \"%s\n^3has been stripped of his shoutcaster status\n\"",tmp_i3 + 0x5f8);
            trap_SendServerCommand(0xffffffff,tmp_u2);
            ClientUserinfoChanged((local_50c[0] * 0x600 >> 9) * -0x55555555);
          }
        }
      }
      else {
        G_MatchOnePlayer(local_50c,local_40c,0x400);
        G_Printf("^1removeshoutcaster %s\n",local_40c);
      }
    }
  }
  return;
}

void nitmod_SendNCS(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = g_unk_02aa029c;
  if ((int)GHIDRA_FIELD(g_resetXPMapCount, 12, 4) <= g_unk_02aa029c) {
    tmp_i1 = 0;
  }
  tmp_u2 = GHIDRA_FIELD(g_resetXPMapCount, 12, 4);
  if ((g_XPSave[0xc] & 4) != 0) {
    tmp_u2 = 0;
  }
  tmp_u2 = va("# %i %i %i %i %i %i %i %i %i %i %i %i %i %i %.3f %i %i %i %d %d",
             GHIDRA_FIELD(team_panzerRestriction, 12, 4),GHIDRA_FIELD(team_maxPanzers, 12, 4),GHIDRA_FIELD(team_maxMG42s, 12, 4),
             GHIDRA_FIELD(team_maxFlamers, 12, 4),GHIDRA_FIELD(team_maxMortars, 12, 4),GHIDRA_FIELD(team_maxriflegrenades, 12, 4),
             GHIDRA_FIELD(g_adrenaline, 12, 4),GHIDRA_FIELD(jp_keepAwards, 12, 4),GHIDRA_FIELD(team_maxSoldiers, 12, 4),GHIDRA_FIELD(team_maxMedics, 12, 4),
             GHIDRA_FIELD(team_maxEngineers, 12, 4),GHIDRA_FIELD(team_maxFieldops, 12, 4),GHIDRA_FIELD(team_maxCovertops, 12, 4),
             GHIDRA_FIELD(g_weapons, 12, 4),(double)(float)GHIDRA_FIELD(g_DJHeight, 8, 4),GHIDRA_FIELD(g_TDMOptions, 12, 4),GHIDRA_FIELD(g_DMOptions, 12, 4)
             ,GHIDRA_FIELD(g_gravity, 12, 4),tmp_i1,tmp_u2);
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
    return;
  }
  trap_SendServerCommand(0xffffffff,tmp_u2);
  return;
}

void nitmod_SoundEvent(int param_1,uint32_t param_2)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_pu1 = &g_unk_0080dc08 + g_unk_02af58bc;
  if (g_unk_00abe908 - *(int *)((&level)[(int)tmp_pu1] + 0x1c0) < 300) {
    tmp_i2 = G_TempEntity(param_1 + 0x168,100);
  }
  else {
    *(uint32_t *)((&level)[(int)tmp_pu1] + 4) = 0x9f;
    tmp_i2 = g_unk_00abe908;
    *(int *)((&level)[(int)tmp_pu1] + 0x1c0) = g_unk_00abe908;
    *(int *)((&level)[(int)tmp_pu1] + 0x184) = tmp_i2;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x1c4) = 0;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x1c8) = 1;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x128) = 0;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x5e4) = 0;
    g_unk_02af58bc = (g_unk_02af58bc + 1) % 0x20;
    if (param_1 + 0x168 != 0) {
      local_28 = (float)(int)ROUND(*(float *)(param_1 + 0x168));
      local_24 = (float)(int)ROUND(*(float *)(param_1 + 0x16c));
      local_20 = (float)(int)ROUND(*(float *)(param_1 + 0x170));
      G_SetOrigin((&level)[(int)tmp_pu1],&local_28);
    }
    trap_LinkEntity((&level)[(int)tmp_pu1]);
    tmp_i2 = (&level)[(int)tmp_pu1];
  }
  *(uint32_t *)(tmp_i2 + 0xbc) = param_2;
  return;
}

void nitmod_Announce(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  float local_18;
  float local_14;
  float local_10;
  
  local_10 = 1.636548e-39;
  tmp_pu1 = &g_unk_0080dc08 + g_unk_02af58bc;
  if (g_unk_00abe908 - *(int *)((&level)[(int)tmp_pu1] + 0x1c0) < 300) {
    tmp_i2 = G_TempEntity(&g_unk_00abf998,0x65);
  }
  else {
    *(uint32_t *)((&level)[(int)tmp_pu1] + 4) = 0xa0;
    tmp_i2 = g_unk_00abe908;
    *(int *)((&level)[(int)tmp_pu1] + 0x1c0) = g_unk_00abe908;
    *(int *)((&level)[(int)tmp_pu1] + 0x184) = tmp_i2;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x1c4) = 0;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x1c8) = 1;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x128) = 0;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x5e4) = 0;
    g_unk_02af58bc = (g_unk_02af58bc + 1) % 0x20;
    local_18 = (float)(int)ROUND(g_unk_00abf998);
    local_14 = (float)(int)ROUND(g_unk_00abf99c);
    local_10 = (float)(int)ROUND(g_unk_00abf9a0);
    G_SetOrigin((&level)[(int)tmp_pu1],&local_18);
    trap_LinkEntity((&level)[(int)tmp_pu1]);
    tmp_i2 = (&level)[(int)tmp_pu1];
  }
  *(uint *)(tmp_i2 + 0x128) = *(uint *)(tmp_i2 + 0x128) | 0x20;
  *(uint32_t *)(tmp_i2 + 0x10c) = param_1;
  *(uint32_t *)(tmp_i2 + 0x110) = param_2;
  *(uint32_t *)(tmp_i2 + 0x114) = param_3;
  return;
}

void nitmod_TeamScores(void)
{
  uint32_t tmp_u1;
  
  tmp_u1 = va("tsc %i %i",g_unk_00abe920,g_unk_00abe924);
  trap_SendServerCommand(0xffffffff,tmp_u1);
  return;
}

uint8_t * nitrox_XPSave_encode64(int param_1,uint8_t *param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint tmp_u3;
  uint tmp_u4;
  uint *tmp_pu5;
  uint *tmp_pu6;
  int tmp_i7;
  uint local_41c [259];
  
  if ((param_1 != 0) && (tmp_i1 = *(int *)(param_1 + 400), tmp_i1 != 0)) {
    local_41c[0]._0_1_ = 0;
    tmp_i7 = 0;
    while( true ) {
      tmp_u2 = va("S%i\\%d\\",tmp_i7,(int)ROUND(*(float *)(tmp_i1 + 0xbf4 + tmp_i7 * 4)));
      Q_strcat(local_41c,0x400,tmp_u2);
      tmp_pu6 = local_41c;
      if (tmp_i7 + 1 == 7) break;
      tmp_i1 = *(int *)(param_1 + 400);
      tmp_i7 = tmp_i7 + 1;
    }
    do {
      tmp_pu5 = tmp_pu6;
      tmp_u3 = *tmp_pu5 + 0xfefefeff & ~*tmp_pu5;
      tmp_u4 = tmp_u3 & 0x80808080;
      tmp_pu6 = tmp_pu5 + 1;
    } while (tmp_u4 == 0);
    if ((tmp_u3 & 0x8080) == 0) {
      tmp_pu6 = (uint *)((int)tmp_pu5 + 6);
      tmp_u4 = tmp_u4 >> 0x10;
    }
    encode64(local_41c,param_2,
             (int)tmp_pu6 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_41c));
    return param_2;
  }
  return &g_unk_0026ea14;
}

bool nitrox_CheckNGUIDSum(char *param_1)
{
  char *tmp_pc1;
  char tmp_c2;
  int tmp_i3;
  
  tmp_i3 = 0;
  tmp_pc1 = param_1 + 0x21;
  do {
    tmp_c2 = *param_1;
    param_1 = param_1 + 1;
    tmp_i3 = tmp_i3 + tmp_c2;
  } while (param_1 != tmp_pc1);
  return tmp_i3 == (tmp_i3 / 100) * 100;
}

uint32_t nitrox_GUIDCheckValid(char *param_1,uint32_t param_2)
{
  char tmp_c1;
  char *tmp_pc2;
  size_t tmp_s3;
  int tmp_i4;
  
  tmp_i4 = 0;
  tmp_pc2 = param_1;
  do {
    tmp_c1 = *tmp_pc2;
    tmp_pc2 = tmp_pc2 + 1;
    tmp_i4 = tmp_i4 + tmp_c1;
  } while (tmp_pc2 != param_1 + 0x21);
  if (tmp_i4 == (tmp_i4 / 100) * 100) {
    tmp_s3 = strlen(param_1);
    tmp_pc2 = param_1 + tmp_s3;
    do {
      if (param_1 == tmp_pc2) {
        return 1;
      }
      tmp_c1 = *param_1;
    } while (((6 < (byte)(tmp_c1 - 0x3aU)) && ((byte)(tmp_c1 - 0x30U) < 0x4b)) &&
            (param_1 = param_1 + 1, 5 < (byte)(tmp_c1 + 0xa5U)));
    tmp_pc2 = "NGUID contains invalid characters";
  }
  else {
    tmp_pc2 = "Corrupted NGUID";
  }
  Com_sprintf(param_2,0x400,tmp_pc2);
  return 0;
}

uint32_t nitrox_AlphaNumValid(char *param_1)
{
  char *tmp_pc1;
  char tmp_c2;
  size_t tmp_s3;
  
  tmp_s3 = strlen(param_1);
  tmp_pc1 = param_1 + tmp_s3;
  do {
    if (param_1 == tmp_pc1) {
      return 1;
    }
    tmp_c2 = *param_1;
  } while (((6 < (byte)(tmp_c2 - 0x3aU)) && ((byte)(tmp_c2 - 0x30U) < 0x4b)) &&
          (param_1 = param_1 + 1, 5 < (byte)(tmp_c2 + 0xa5U)));
  return 0;
}

void nitrox_user_register(int param_1)
{
  char tmp_c1;
  size_t tmp_s2;
  int tmp_i3;
  uint32_t tmp_u4;
  size_t tmp_s5;
  int tmp_i6;
  char local_5e [33];
  char local_3d [45];
  
  if ((((param_1 != 0) && (GHIDRA_FIELD(n_userMail, 12, 4) != 0)) && (tmp_i3 = *(int *)(param_1 + 400), tmp_i3 != 0)
      ) && ((g_unk_02af58b8 != 0 && (*(int *)(tmp_i3 + 0x54d8) == 0)))) {
    tmp_s2 = strlen((char *)(tmp_i3 + 0x61c));
    if (tmp_s2 == 0x20) {
      tmp_i3 = Q_SayArgc();
      if (tmp_i3 < 3) {
        G_shrubbot_print(param_1,
                         "^9usage: ^gregister [username(32 char max)] [password(32 char max)]\n");
      }
      else {
        Q_SayArgv(1,local_5e,0x21);
        Q_SayArgv(2,local_3d,0x21);
        tmp_s2 = strlen(local_5e);
        for (tmp_s5 = 0; tmp_s5 != tmp_s2; tmp_s5 = tmp_s5 + 1) {
          tmp_c1 = local_5e[tmp_s5];
          if (((0x4a < (byte)(tmp_c1 - 0x30U)) || ((byte)(tmp_c1 - 0x3aU) < 7)) ||
             ((byte)(tmp_c1 + 0xa5U) < 6)) {
            G_shrubbot_print(param_1,
                             "^1Register: ^gUsername can only contain letters and numbers.\n");
            return;
          }
        }
        tmp_s2 = strlen(local_3d);
        for (tmp_s5 = 0; tmp_s5 != tmp_s2; tmp_s5 = tmp_s5 + 1) {
          tmp_c1 = local_3d[tmp_s5];
          if (((0x4a < (byte)(tmp_c1 - 0x30U)) || ((byte)(tmp_c1 - 0x3aU) < 7)) ||
             ((byte)(tmp_c1 + 0xa5U) < 6)) {
            G_shrubbot_print(param_1,
                             "^1Register: ^gPassword can only contain letters and numbers.\n");
            return;
          }
        }
        tmp_i6 = 0;
        tmp_u4 = G_SHA1(local_3d);
        tmp_i3 = Users;
        while (tmp_i3 != 0) {
          tmp_i3 = Q_stricmp(*(int *)(param_1 + 400) + 0x61c,tmp_i3 + 4);
          if (tmp_i3 == 0) {
            tmp_i3 = (&Users)[tmp_i6];
            if (*(char *)(tmp_i3 + 0x1078) != '\0') {
              tmp_u4 = va("^1Register: ^gYou are already registered as \'^7%s^g\' on this server.\n",
                         tmp_i3 + 0x1078);
              G_shrubbot_print(param_1,tmp_u4);
              return;
            }
            Q_strncpyz(tmp_i3 + 0x1078,local_5e,0x21);
            Q_strncpyz((&Users)[tmp_i6] + 0x1099,tmp_u4,0x40);
            if (g_unk_02af58b8 != 0) {
              nitrox_SQLite_SaveUser((&Users)[tmp_i6],2);
            }
            tmp_u4 = va("^xRegister: ^gYou are now registered on this server.\n^gYour username is: ^7%s\n^gYour password is: ^7%s\n"
                       ,(&Users)[tmp_i6] + 0x1078,local_3d);
            G_shrubbot_print(param_1,tmp_u4);
            nitrox_SetAdminPointers(param_1,(&Users)[tmp_i6]);
            return;
          }
          tmp_i6 = tmp_i6 + 1;
          tmp_i3 = (&Users)[tmp_i6];
        }
      }
    }
    else {
      G_shrubbot_print(param_1,"^1Register: ^gYou have an invalid NGUID.\n");
    }
  }
  return;
}

void nitrox_user_login(int param_1)
{
  size_t tmp_s1;
  int tmp_i2;
  char *__s1;
  int tmp_i3;
  int tmp_i4;
  char local_5e [33];
  uint8_t local_3d [45];
  
  if ((((param_1 != 0) && (GHIDRA_FIELD(n_userMail, 12, 4) != 0)) && (*(int *)(param_1 + 400) != 0)) &&
     (g_unk_02af58b8 != 0)) {
    tmp_s1 = strlen((char *)(*(int *)(param_1 + 400) + 0x61c));
    if (tmp_s1 == 0x20) {
      tmp_i2 = Q_SayArgc();
      if (tmp_i2 < 3) {
        G_shrubbot_print(param_1,"^9usage: ^glogin [username] [password]\n");
      }
      else {
        Q_SayArgv(1,local_5e,0x21);
        Q_SayArgv(2,local_3d,0x21);
        __s1 = (char *)G_SHA1(local_3d);
        if (Users != 0) {
          tmp_i4 = 0;
          tmp_i2 = Users;
          do {
            tmp_i2 = Q_stricmp(*(int *)(param_1 + 400) + 0x61c,tmp_i2 + 4);
            if (tmp_i2 == 0) {
              tmp_i2 = (&Users)[tmp_i4];
              tmp_i3 = strcmp(local_5e,(char *)(tmp_i2 + 0x1078));
              if (tmp_i3 != 0) {
                G_shrubbot_print(param_1,"^1Login: ^gUsername doesn\'t match your NGUID\n");
                return;
              }
              tmp_i2 = strcmp(__s1,(char *)(tmp_i2 + 0x1099));
              if (tmp_i2 != 0) {
                G_shrubbot_print(param_1,"^1Login: ^gInvalid password\n");
                return;
              }
              *(uint32_t *)(*(int *)(param_1 + 400) + 0xf40) = 1;
              Q_strncpyz(*(int *)(param_1 + 400) + 0xf48,(&Users)[tmp_i4] + 0x1078,0x21);
              G_shrubbot_print(param_1,
                               "^xLogin: ^gYou have successfully logged in to your account\n");
              return;
            }
            tmp_i4 = tmp_i4 + 1;
            tmp_i2 = (&Users)[tmp_i4];
          } while (tmp_i2 != 0);
        }
      }
    }
    else {
      G_shrubbot_print(param_1,"^1Login: ^gYou have an invalid NGUID.\n");
    }
  }
  return;
}

void nitrox_DBConnect(void)
{
  nitrox_SQLite_init();
  return;
}

void nitrox_InitUsersTable(void)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_InitUsersTable();
    nitrox_SQLite_InitRecordsTable();
  }
  return;
}

void nitrox_InitMailsTable(void)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_InitMailsTable();
  }
  return;
}

void nitrox_LoadUsers(void)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_LoadUsers();
  }
  return;
}

void nitrox_SaveUsers(uint32_t param_1,uint32_t param_2)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_SaveUsers(param_1,param_2);
  }
  return;
}

void nitrox_MailTo(uint32_t param_1)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_MailTo(param_1);
  }
  return;
}

void nitrox_CheckMails(uint32_t param_1)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_FindMails(param_1);
  }
  return;
}

void nitrox_DeleteMail(uint32_t param_1,uint32_t param_2)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_DeleteMail(param_1,param_2);
  }
  return;
}

void nitrox_SaveSingleUser(uint32_t param_1,uint32_t param_2)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_SaveUser(param_1,param_2);
  }
  return;
}

uint32_t nitrox_SaveDB(uint32_t param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 0;
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_SaveBans(param_1,param_2);
    tmp_u1 = 1;
    if (g_unk_02af58b8 != 0) {
      nitrox_SQLite_SaveMutes(param_1,param_2);
      return 1;
    }
  }
  return tmp_u1;
}

void nitrox_SaveDB_console(void)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_SaveUsers(0,0xffffffff);
    if (g_unk_02af58b8 != 0) {
      nitrox_SQLite_SaveBans(0,0xffffffff);
      if (g_unk_02af58b8 != 0) {
        nitrox_SQLite_SaveMutes(0,0xffffffff);
        return;
      }
    }
  }
  return;
}

void nitrox_InitEventsQueue(void)
{
  int tmp_i1;
  int *tmp_pi2;
  int *tmp_pi3;
  
  g_unk_02af58bc = 0;
  tmp_pi2 = &g_unk_02af58c0;
  do {
    tmp_i1 = G_Spawn();
    tmp_pi3 = tmp_pi2 + 1;
    *(uint32_t *)(tmp_i1 + 0x2a0) = 0;
    *(uint32_t *)(tmp_i1 + 0x1ac) = 1;
    *(uint32_t *)(tmp_i1 + 0x1c4) = 0;
    *(uint32_t *)(tmp_i1 + 0x1c8) = 0;
    *(char **)(tmp_i1 + 0x1a4) = "eventQueue";
    *(uint32_t *)(tmp_i1 + 4) = 10;
    *(uint32_t *)(tmp_i1 + 0x128) = 1;
    *(uint32_t *)(tmp_i1 + 0x5e4) = 1;
    *tmp_pi2 = tmp_i1;
    tmp_pi2 = tmp_pi3;
  } while (tmp_pi3 != &g_unk_02af5940);
  return;
}

uint32_t nitrox_TempEventFromQueue(float *param_1,int param_2)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint32_t tmp_u3;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_pu1 = &g_unk_0080dc08 + g_unk_02af58bc;
  if (g_unk_00abe908 - *(int *)((&level)[(int)tmp_pu1] + 0x1c0) < 300) {
    tmp_u3 = G_TempEntity(param_1,param_2);
  }
  else {
    *(int *)((&level)[(int)tmp_pu1] + 4) = param_2 + 0x3b;
    tmp_i2 = g_unk_00abe908;
    *(int *)((&level)[(int)tmp_pu1] + 0x1c0) = g_unk_00abe908;
    *(int *)((&level)[(int)tmp_pu1] + 0x184) = tmp_i2;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x1c4) = 0;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x1c8) = 1;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x128) = 0;
    *(uint32_t *)((&level)[(int)tmp_pu1] + 0x5e4) = 0;
    if ((param_2 - 0x68U < 3) || (param_2 == 0x32)) {
      tmp_i2 = tmp_i2 + 200;
      *(int *)((&level)[(int)tmp_pu1] + 0x1c0) = tmp_i2;
      *(int *)((&level)[(int)tmp_pu1] + 0x184) = tmp_i2;
    }
    g_unk_02af58bc = (g_unk_02af58bc + 1) % 0x20;
    if (param_1 != (float *)0x0) {
      local_28 = (float)(int)ROUND(*param_1);
      local_24 = (float)(int)ROUND(param_1[1]);
      local_20 = (float)(int)ROUND(param_1[2]);
      G_SetOrigin((&level)[(int)tmp_pu1],&local_28);
    }
    trap_LinkEntity((&level)[(int)tmp_pu1]);
    tmp_u3 = (&level)[(int)tmp_pu1];
  }
  return tmp_u3;
}

void nitrox_InitTempHeadQueue(void)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = 0;
  g_unk_02af5940 = 0;
  do {
    tmp_i1 = G_Spawn();
    *(uint32_t *)(tmp_i1 + 0x2a0) = 0;
    *(uint32_t *)(tmp_i1 + 0x1ac) = 1;
    *(uint32_t *)(tmp_i1 + 0x1c4) = 0;
    *(uint32_t *)(tmp_i1 + 0x1c8) = 0;
    *(int *)(tmp_i1 + 0x5dc) = tmp_i2;
    *(char **)(tmp_i1 + 0x1a4) = "tempHeadQueue";
    *(uint32_t *)(tmp_i1 + 4) = 10;
    *(uint32_t *)(tmp_i1 + 0x128) = 1;
    *(uint32_t *)(tmp_i1 + 0x5e4) = 1;
    (&g_unk_02af5944)[tmp_i2] = tmp_i1;
    tmp_i2 = tmp_i2 + 1;
    trap_LinkEntity(tmp_i1);
  } while (tmp_i2 != 0x40);
  return;
}

uint32_t nitrox_TempHeadFromQueue(void)
{
  uint8_t *tmp_pu1;
  
  tmp_pu1 = &g_unk_0080dc28 + g_unk_02af5940;
  g_unk_02af5940 = (g_unk_02af5940 + 1) % 0x40;
  *(uint32_t *)((&g_unk_00abe8a4)[(int)tmp_pu1] + 4) = 0x28;
  *(uint32_t *)((&g_unk_00abe8a4)[(int)tmp_pu1] + 0x5e4) = 0;
  return (&g_unk_00abe8a4)[(int)tmp_pu1];
}

void nitrox_FreeTempHead(int param_1)
{
  *(uint32_t *)(param_1 + 4) = 10;
  *(char **)(param_1 + 0x1a4) = "tempHeadQueue";
  *(uint32_t *)(param_1 + 0x14c) = 0;
  *(uint32_t *)(param_1 + 0x1d4) = 0;
  *(uint32_t *)(param_1 + 0x184) = 0;
  *(uint32_t *)(param_1 + 0x1c0) = 0;
  *(uint32_t *)(param_1 + 0x5e4) = 1;
  *(uint32_t *)(param_1 + 0x218) = 0;
  return;
}

void nitrox_InitTempLegQueue(void)
{
  return;
}

void nitrox_TempLegFromQueue(void)
{
  G_Spawn();
  return;
}

void nitrox_FreeTempLeg(uint32_t param_1)
{
  G_FreeEntity(param_1);
  return;
}

void nitrox_TempMissileCam(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  
  if (GHIDRA_FIELD(g_missileCams, 12, 4) != 0) {
    tmp_i1 = G_Spawn();
    *(char **)(tmp_i1 + 0x1a4) = "missileCam";
    *(uint32_t *)(tmp_i1 + 4) = 0x39;
    tmp_i2 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    *(uint32_t *)(tmp_i1 + 0x128) = 0x840;
    *(int *)(tmp_i1 + 0x180) = tmp_i2;
    *(int *)(tmp_i1 + 300) = tmp_i2;
    *(uint32_t *)(tmp_i1 + 0x2f0) = param_2;
    trap_LinkEntity(tmp_i1);
  }
  return;
}

void nitrox_Uptime(void)
{
  int tmp_i1;
  
  tmp_i1 = (g_unk_00abe908 / 1000) % 0x15180;
  va("%d D %d H %d M",(g_unk_00abe908 / 1000) / 0x15180,tmp_i1 / 0xe10,(tmp_i1 % 0xe10) / 0x3c);
  return;
}

uint8_t * nitrox_FindByClassNameHash(int param_1,int param_2)
{
  uint8_t *tmp_pu1;
  
  tmp_pu1 = (uint8_t *)(param_1 + 0x600);
  if (param_1 == 0) {
    tmp_pu1 = g_entities;
  }
  while( true ) {
    if (g_entities + g_unk_00abe8a8 * 0x600 <= tmp_pu1) {
      return (uint8_t *)0x0;
    }
    if ((*(int *)(tmp_pu1 + 0x194) != 0) && (*(int *)(tmp_pu1 + 0x5c0) == param_2)) break;
    tmp_pu1 = tmp_pu1 + 0x600;
  }
  return tmp_pu1;
}

uint8_t * nitrox_FindByScriptNameHash(int param_1,int param_2)
{
  uint8_t *tmp_pu1;
  
  tmp_pu1 = (uint8_t *)(param_1 + 0x600);
  if (param_1 == 0) {
    tmp_pu1 = g_entities;
  }
  while( true ) {
    if (g_entities + g_unk_00abe8a8 * 0x600 <= tmp_pu1) {
      return (uint8_t *)0x0;
    }
    if ((*(int *)(tmp_pu1 + 0x194) != 0) && (*(int *)(tmp_pu1 + 0x5b0) == param_2)) break;
    tmp_pu1 = tmp_pu1 + 0x600;
  }
  return tmp_pu1;
}

uint8_t * nitrox_FindByInteger(int param_1,int param_2,int param_3)
{
  uint8_t *tmp_pu1;
  
  tmp_pu1 = (uint8_t *)(param_1 + 0x600);
  if (param_1 == 0) {
    tmp_pu1 = g_entities;
  }
  while( true ) {
    if (g_entities + g_unk_00abe8a8 * 0x600 <= tmp_pu1) {
      return (uint8_t *)0x0;
    }
    if ((*(int *)(tmp_pu1 + 0x194) != 0) && (*(int *)(tmp_pu1 + param_2) == param_3)) break;
    tmp_pu1 = tmp_pu1 + 0x600;
  }
  return tmp_pu1;
}

uint8_t * nitrox_FindByFloat(int param_1,int param_2,float param_3)
{
  uint8_t *tmp_pu1;
  
  tmp_pu1 = (uint8_t *)(param_1 + 0x600);
  if (param_1 == 0) {
    tmp_pu1 = g_entities;
  }
  while( true ) {
    if (g_entities + g_unk_00abe8a8 * 0x600 <= tmp_pu1) {
      return (uint8_t *)0x0;
    }
    if ((*(int *)(tmp_pu1 + 0x194) != 0) && (*(float *)(tmp_pu1 + param_2) == param_3)) break;
    tmp_pu1 = tmp_pu1 + 0x600;
  }
  return tmp_pu1;
}

uint8_t * nitrox_FindByVector(int param_1,int param_2,uint32_t param_3)
{
  int tmp_i1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x11e9f9;
  tmp_i2 = g_unk_00abe8a8 * 0x600;
  tmp_pu3 = (uint8_t *)(param_1 + 0x600);
  if (param_1 == 0) {
    tmp_pu3 = g_entities;
  }
  tmp_pu4 = (uint32_t *)(tmp_pu3 + param_2);
  do {
    if (g_entities + tmp_i2 <= tmp_pu3) {
      return (uint8_t *)0x0;
    }
    if (*(int *)(tmp_pu3 + 0x194) != 0) {
      local_28 = *tmp_pu4;
      local_24 = tmp_pu4[1];
      local_20 = tmp_pu4[2];
      tmp_i1 = VectorCompare(&local_28,param_3);
      if (tmp_i1 != 0) {
        return tmp_pu3;
      }
    }
    tmp_pu3 = tmp_pu3 + 0x600;
    tmp_pu4 = tmp_pu4 + 0x180;
  } while( true );
}

void nitrox_InitEntityArray(uint32_t *param_1)
{
  *param_1 = 0;
  return;
}

void nitrox_AddEntityToEntityArray(int *param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  
  tmp_i1 = *param_1;
  if (tmp_i1 < 0x400) {
    if (tmp_i1 < 1) {
LAB_0011eb0c:
      *param_1 = tmp_i1 + 1;
      param_1[tmp_i1 + 1] = param_2;
    }
    else if (param_1[1] != param_2) {
      tmp_pi3 = param_1 + 2;
      do {
        if (tmp_pi3 == param_1 + tmp_i1 + 1) goto LAB_0011eb0c;
        tmp_i2 = *tmp_pi3;
        tmp_pi3 = tmp_pi3 + 1;
      } while (tmp_i2 != param_2);
    }
  }
  else {
    G_Error("Entity Array Overflow");
  }
  return;
}

void nitrox_RemoveEntityFromEntityArray(int *param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i1 = *param_1;
  if (0 < tmp_i1) {
    tmp_i2 = param_1[1];
    tmp_i3 = 0;
    while( true ) {
      if (tmp_i2 == param_2) {
        if (tmp_i3 < tmp_i1 + -1) {
          memmove(param_1 + tmp_i3 + 1,param_1 + tmp_i3 + 2,((tmp_i1 + 0x3fffffff) - tmp_i3) * 4);
        }
        *param_1 = tmp_i1 + -1;
        return;
      }
      if (tmp_i3 + 1 == tmp_i1) break;
      tmp_i2 = param_1[tmp_i3 + 2];
      tmp_i3 = tmp_i3 + 1;
    }
  }
  return;
}

bool nitrox_NextKey(uint32_t *param_1,char *param_2)
{
  char tmp_c1;
  char *tmp_pc2;
  char *tmp_pc3;
  
  tmp_pc3 = (char *)*param_1;
  tmp_c1 = *tmp_pc3;
  *param_2 = '\0';
  tmp_pc3 = tmp_pc3 + (tmp_c1 == '\\');
  tmp_c1 = *tmp_pc3;
  tmp_pc2 = param_2;
  while ((tmp_c1 != '\0' && (tmp_c1 != '\\'))) {
    tmp_pc3 = tmp_pc3 + 1;
    *tmp_pc2 = tmp_c1;
    tmp_pc2 = tmp_pc2 + 1;
    tmp_c1 = *tmp_pc3;
  }
  *tmp_pc2 = '\0';
  tmp_c1 = *param_2;
  if (tmp_c1 != '\0') {
    *param_1 = tmp_pc3 + 1;
  }
  return tmp_c1 != '\0';
}

void nitrox_CacheClientIP(int param_1,char *param_2)
{
  char tmp_c1;
  char tmp_c2;
  int tmp_i3;
  long tmp_l4;
  char local_2c [28];
  
  if ((param_1 != 0) && (tmp_i3 = *(int *)(param_1 + 400), tmp_i3 != 0)) {
    if (*param_2 == '\0') {
      *(uint8_t *)(tmp_i3 + 0x63d) = 0;
      *(uint8_t *)(*(int *)(param_1 + 400) + 0x653) = 0;
    }
    else {
      Q_strncpyz(tmp_i3 + 0x63d,param_2,0x16);
      tmp_c1 = *param_2;
      if ((tmp_c1 == '\0') || (tmp_c1 == ':')) {
        tmp_i3 = 0;
      }
      else {
        tmp_c2 = param_2[1];
        local_2c[0] = tmp_c1;
        if ((tmp_c2 == '\0') || (tmp_c2 == ':')) {
          tmp_i3 = 1;
          param_2 = param_2 + 1;
        }
        else {
          tmp_c1 = param_2[2];
          local_2c[1] = tmp_c2;
          if ((tmp_c1 == '\0') || (tmp_c1 == ':')) {
            tmp_i3 = 2;
            param_2 = param_2 + 2;
          }
          else {
            tmp_c2 = param_2[3];
            local_2c[2] = tmp_c1;
            if ((tmp_c2 == '\0') || (tmp_c2 == ':')) {
              tmp_i3 = 3;
              param_2 = param_2 + 3;
            }
            else {
              tmp_c1 = param_2[4];
              local_2c[3] = tmp_c2;
              if ((tmp_c1 == '\0') || (tmp_c1 == ':')) {
                tmp_i3 = 4;
                param_2 = param_2 + 4;
              }
              else {
                tmp_c2 = param_2[5];
                local_2c[4] = tmp_c1;
                if ((tmp_c2 == '\0') || (tmp_c2 == ':')) {
                  tmp_i3 = 5;
                  param_2 = param_2 + 5;
                }
                else {
                  tmp_c1 = param_2[6];
                  local_2c[5] = tmp_c2;
                  if ((tmp_c1 == '\0') || (tmp_c1 == ':')) {
                    tmp_i3 = 6;
                    param_2 = param_2 + 6;
                  }
                  else {
                    tmp_c2 = param_2[7];
                    local_2c[6] = tmp_c1;
                    if ((tmp_c2 == '\0') || (tmp_c2 == ':')) {
                      tmp_i3 = 7;
                      param_2 = param_2 + 7;
                    }
                    else {
                      tmp_c1 = param_2[8];
                      local_2c[7] = tmp_c2;
                      if ((tmp_c1 == '\0') || (tmp_c1 == ':')) {
                        tmp_i3 = 8;
                        param_2 = param_2 + 8;
                      }
                      else {
                        tmp_c2 = param_2[9];
                        local_2c[8] = tmp_c1;
                        if ((tmp_c2 == '\0') || (tmp_c2 == ':')) {
                          tmp_i3 = 9;
                          param_2 = param_2 + 9;
                        }
                        else {
                          tmp_c1 = param_2[10];
                          local_2c[9] = tmp_c2;
                          if ((tmp_c1 == '\0') || (tmp_c1 == ':')) {
                            tmp_i3 = 10;
                            param_2 = param_2 + 10;
                          }
                          else {
                            tmp_c2 = param_2[0xb];
                            local_2c[10] = tmp_c1;
                            if ((tmp_c2 == '\0') || (tmp_c2 == ':')) {
                              tmp_i3 = 0xb;
                              param_2 = param_2 + 0xb;
                            }
                            else {
                              tmp_c1 = param_2[0xc];
                              local_2c[0xb] = tmp_c2;
                              if ((tmp_c1 == '\0') || (tmp_c1 == ':')) {
                                tmp_i3 = 0xc;
                                param_2 = param_2 + 0xc;
                              }
                              else {
                                tmp_c2 = param_2[0xd];
                                local_2c[0xc] = tmp_c1;
                                if ((tmp_c2 == '\0') || (tmp_c2 == ':')) {
                                  tmp_i3 = 0xd;
                                  param_2 = param_2 + 0xd;
                                }
                                else {
                                  tmp_c1 = param_2[0xe];
                                  local_2c[0xd] = tmp_c2;
                                  if ((tmp_c1 == '\0') || (tmp_c1 == ':')) {
                                    tmp_i3 = 0xe;
                                    param_2 = param_2 + 0xe;
                                  }
                                  else {
                                    tmp_c2 = param_2[0xf];
                                    local_2c[0xe] = tmp_c1;
                                    if ((tmp_c2 == '\0') || (tmp_c2 == ':')) {
                                      tmp_i3 = 0xf;
                                      param_2 = param_2 + 0xf;
                                    }
                                    else {
                                      tmp_i3 = 0x10;
                                      param_2 = param_2 + 0x10;
                                      local_2c[0xf] = tmp_c2;
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
      local_2c[tmp_i3] = '\0';
      Q_strncpyz(*(int *)(param_1 + 400) + 0x653,local_2c,0x10);
      tmp_i3 = *(int *)(param_1 + 400);
      tmp_l4 = strtol(param_2 + 1,(char **)0x0,10);
      *(long *)(tmp_i3 + 0x664) = tmp_l4;
    }
  }
  return;
}

long double nitrox_HitboxHeight(int param_1,int param_2)
{
  uint tmp_u1;
  int tmp_i2;
  
  if (param_1 == 0) {
    return (long double)0;
  }
  if (*(int *)(param_1 + 400) == 0) {
    return (long double)*(float *)(param_1 + 0x148);
  }
  tmp_u1 = *(uint *)(*(int *)(param_1 + 400) + 0x68);
  if ((tmp_u1 & 0x880001) == 0) {
    if ((tmp_u1 & 0x10) == 0) {
      if ((g_realBody[0xc] & 2) == 0) {
        return (long double)48.0;
      }
      return (long double)36.0;
    }
    if ((g_realBody[0xc] & 8) != 0) {
      return (long double)18.0;
    }
  }
  else {
    if (((param_2 != 0) && (*(int *)(param_2 + 400) != 0)) &&
       ((tmp_i2 = *(int *)(param_2 + 0xe8), tmp_i2 == 0x2f || tmp_i2 == 0xb || (tmp_i2 == 1)))) {
      return (long double)32.0;
    }
    if (((g_realBody[0xc] & 4) != 0) || (GHIDRA_FIELD(g_hitboxes, 12, 4) != 0)) {
      return (long double)4.0;
    }
  }
  return (long double)24.0;
}

void nitrox_ParseMaxHP(void)
{
  char *__nptr;
  long tmp_l1;
  int tmp_i2;
  char local_11c [264];
  uint32_t uStack_14;
  
  uStack_14 = 0x11f562;
  Q_strncpyz(local_11c,0x2e47190,0x100);
  g_unk_02b9a438 = 0;
  g_unk_02b9a440 = 0;
  g_unk_02b9a444 = 0;
  g_unk_02b9a43c = 0;
  g_unk_02b9a448 = 0;
  tmp_i2 = 0;
  __nptr = strtok(local_11c," ");
  if (__nptr != (char *)0x0) {
    do {
      tmp_l1 = strtol(__nptr,(char **)0x0,10);
      if (0 < tmp_l1) {
        tmp_l1 = strtol(__nptr,(char **)0x0,10);
        (&g_unk_02b9a438)[tmp_i2] = tmp_l1;
      }
      tmp_i2 = tmp_i2 + 1;
      __nptr = strtok((char *)0x0," ");
    } while ((__nptr != (char *)0x0) && (tmp_i2 < 5));
  }
  return;
}

void nitrox_SendSkillLevels(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint8_t local_41c [1036];
  
  if (param_1 == 0) {
    tmp_i2 = -1;
  }
  else {
    tmp_i2 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  }
  local_41c[0] = 0;
  tmp_u1 = va(&g_unk_0024e6e9,0x2e55a70);
  Info_SetValueForKey(local_41c,"S",tmp_u1);
  tmp_u1 = va(&g_unk_0024e6e9,0x2e5a390);
  Info_SetValueForKey(local_41c,"M",tmp_u1);
  tmp_u1 = va(&g_unk_0024e6e9,0x2e53d30);
  Info_SetValueForKey(local_41c,&g_unk_00261b5c,tmp_u1);
  tmp_u1 = va(&g_unk_0024e6e9,0x2e56eb0);
  Info_SetValueForKey(local_41c,"F",tmp_u1);
  tmp_u1 = va(&g_unk_0024e6e9,0x2e579f0);
  Info_SetValueForKey(local_41c,&g_unk_0024ae19,tmp_u1);
  tmp_u1 = va(&g_unk_0024e6e9,0x2e516f0);
  Info_SetValueForKey(local_41c,&g_unk_002603db,tmp_u1);
  tmp_u1 = va(&g_unk_0024e6e9,0x2e48b70);
  Info_SetValueForKey(local_41c,"L",tmp_u1);
  tmp_u1 = va("sl %s",local_41c);
  trap_SendServerCommand(tmp_i2,tmp_u1);
  return;
}

void nitrox_SetConfigstring(uint param_1,char *param_2)
{
  char *__s2;
  int tmp_i1;
  uint32_t tmp_u2;
  
  if (0x28e < param_1) {
    G_Error("nitrox_SetConfigstring: bad index %i\n",param_1);
  }
  if (param_2 == (char *)0x0) {
    param_2 = "";
  }
  __s2 = (char *)((int)&g_unk_02af5a44 + param_1 * 0x3fa);
  tmp_i1 = strcmp(param_2,__s2);
  if (tmp_i1 != 0) {
    tmp_i1 = 0;
    Q_strncpyz(__s2,param_2,0x3fa);
    (&g_unk_02b986ec)[param_1] = 1;
    do {
      if ((&g_unk_02b99128)[tmp_i1] != 0) {
        tmp_u2 = va("ncs %i \"%s\"\n",param_1,__s2);
        trap_SendServerCommand(tmp_i1,tmp_u2);
      }
      tmp_i1 = tmp_i1 + 1;
    } while (tmp_i1 != 0x40);
  }
  return;
}

void nitrox_GetConfigstring(uint param_1,uint32_t param_2,int param_3)
{
  if (param_3 < 1) {
    G_Error("nitrox_GetConfigstring: buffSize == %i",param_3);
  }
  if (0x28e < param_1) {
    G_Error("nitrox_GetConfigstring: bad index %i\n",param_1);
  }
  Q_strncpyz(param_2,(int)&g_unk_02af5a44 + param_1 * 0x3fa,param_3);
  return;
}

void nitrox_UpdateConfigstrings(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *local_24;
  
  tmp_i2 = 0;
  local_24 = &g_unk_02af5a44;
  do {
    if ((&g_unk_02b986ec)[tmp_i2] != 0) {
      (&g_unk_02b986ec)[tmp_i2] = 0;
      tmp_i3 = 0;
      do {
        while ((&g_unk_02b99128)[tmp_i3] == 0) {
          tmp_i3 = tmp_i3 + 1;
          if (tmp_i3 == 0x40) goto LAB_0011fa10;
        }
        tmp_u1 = va("ncs %i \"%s\"\n",tmp_i2,local_24);
        tmp_i4 = tmp_i3 + 1;
        trap_SendServerCommand(tmp_i3,tmp_u1);
        tmp_i3 = tmp_i4;
      } while (tmp_i4 != 0x40);
    }
LAB_0011fa10:
    tmp_i2 = tmp_i2 + 1;
    local_24 = (uint32_t *)((int)local_24 + 0x3fa);
    if (tmp_i2 == 0x28f) {
      return;
    }
  } while( true );
}

int nitrox_CSIndex(char *param_1,int param_2,int param_3,int param_4)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int local_430;
  char *local_42c;
  uint local_428;
  char local_41c [1036];
  
  if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
    return 0;
  }
  if (param_3 < 2) {
    if (param_4 == 0) {
      return 0;
    }
    if (param_3 != 1) {
      local_428 = param_2 + 1;
      local_42c = (char *)((int)&g_unk_02af5a44 + local_428 * 0x3fa);
      local_430 = 1;
      goto LAB_0011fb9a;
    }
  }
  else {
    local_428 = param_2 + 1;
    local_42c = (char *)((int)&g_unk_02af5a44 + local_428 * 0x3fa);
    local_430 = 1;
    do {
      if (0x28e < local_428) {
        G_Error("nitrox_GetConfigstring: bad index %i\n",local_428);
      }
      Q_strncpyz(local_41c,local_42c,0x400);
      if (local_41c[0] == '\0') {
        if (param_4 == 0) {
          return 0;
        }
        goto LAB_0011fb9a;
      }
      tmp_i1 = strcmp(local_41c,param_1);
      if (tmp_i1 == 0) {
        return local_430;
      }
      local_430 = local_430 + 1;
      local_428 = local_428 + 1;
      local_42c = local_42c + 0x3fa;
    } while (local_430 != param_3);
    if (param_4 == 0) {
      return 0;
    }
  }
  G_Error("nitrox_CSIndex: overflow : %s %i %i %i",param_1,param_2,param_3,param_4);
  local_428 = param_2 + param_3;
  local_42c = (char *)((int)&g_unk_02af5a44 + local_428 * 0x3fa);
  local_430 = param_3;
LAB_0011fb9a:
  if (0x28e < local_428) {
    G_Error("nitrox_SetConfigstring: bad index %i\n",local_428);
  }
  tmp_i1 = strcmp(param_1,local_42c);
  if (tmp_i1 != 0) {
    Q_strncpyz(local_42c,param_1,0x3fa);
    (&g_unk_02b986ec)[local_428] = 1;
    tmp_i1 = 0;
    do {
      if ((&g_unk_02b99128)[tmp_i1] != 0) {
        tmp_u2 = va("ncs %i \"%s\"\n",local_428,local_42c);
        trap_SendServerCommand(tmp_i1,tmp_u2);
      }
      tmp_i1 = tmp_i1 + 1;
    } while (tmp_i1 != 0x40);
  }
  return local_430;
}

void nitrox_SendNewGameState(int param_1)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  
  tmp_i5 = param_1 + -0x93e4a0 >> 9;
  if ((&g_unk_02b99128)[tmp_i5 * -0x15555555] != 0) {
    tmp_pc2 = (char *)&g_unk_02af5a44;
    tmp_i3 = 0;
    do {
      while (*tmp_pc2 == '\0') {
        tmp_i3 = tmp_i3 + 1;
        tmp_pc2 = tmp_pc2 + 0x3fa;
        if (tmp_i3 == 0x28f) {
          return;
        }
      }
      tmp_i4 = tmp_i3 + 1;
      tmp_u1 = va("ncs %i \"%s\"\n",tmp_i3,tmp_pc2);
      trap_SendServerCommand(tmp_i5 * -0x55555555,tmp_u1);
      tmp_pc2 = tmp_pc2 + 0x3fa;
      tmp_i3 = tmp_i4;
    } while (tmp_i4 != 0x28f);
  }
  return;
}

void nitrox_SendConfigString(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i2 = 0;
  do {
    while ((&g_unk_02b99128)[tmp_i2] != 0) {
      tmp_u1 = va("ncs %i \"%s\"\n",param_1,(int)&g_unk_02af5a44 + param_1 * 0x3fa);
      tmp_i3 = tmp_i2 + 1;
      trap_SendServerCommand(tmp_i2,tmp_u1);
      tmp_i2 = tmp_i3;
      if (tmp_i3 == 0x40) {
        return;
      }
    }
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 0x40);
  return;
}

void nitrox_SendClassesMaxHP(void)
{
  uint32_t tmp_u1;
  uint8_t local_41c [1036];
  
  local_41c[0] = 0;
  tmp_u1 = va(&g_unk_00245ee9,g_unk_02b9a438);
  Info_SetValueForKey(local_41c,"S",tmp_u1);
  tmp_u1 = va(&g_unk_00245ee9,g_unk_02b9a43c);
  Info_SetValueForKey(local_41c,"M",tmp_u1);
  tmp_u1 = va(&g_unk_00245ee9,g_unk_02b9a440);
  Info_SetValueForKey(local_41c,&g_unk_00261b5c,tmp_u1);
  tmp_u1 = va(&g_unk_00245ee9,g_unk_02b9a444);
  Info_SetValueForKey(local_41c,"F",tmp_u1);
  tmp_u1 = va(&g_unk_00245ee9,g_unk_02b9a448);
  Info_SetValueForKey(local_41c,&g_unk_0024ae19,tmp_u1);
  trap_SetConfigstring(0x27,local_41c);
  return;
}

void nitrox_DumpNCSFull(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  uint tmp_u4;
  char *tmp_pc5;
  uint *tmp_pu6;
  uint *tmp_pu7;
  uint tmp_u8;
  uint32_t *local_840;
  int local_838;
  int local_834;
  uint32_t local_820;
  uint local_81c [256];
  uint local_41c [258];
  uint32_t uStack_14;
  
  uStack_14 = 0x11ff89;
  tmp_u1 = va("DevLogs/DumpNCS_%s.log",&g_unk_00abe8c0);
  tmp_i2 = trap_FS_FOpenFile(tmp_u1,&local_820,1);
  if ((tmp_i2 < 0) && (G_Printf("Couldn\'t open file\n"), param_1 == 0)) {
    return;
  }
  local_840 = &g_unk_02af5a44;
  local_838 = 0;
  local_834 = 0;
  tmp_u8 = 0;
  do {
    Q_strncpyz(local_81c,local_840,0x400);
    tmp_pu7 = local_81c;
    do {
      tmp_pu6 = tmp_pu7;
      tmp_u3 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
      tmp_u4 = tmp_u3 & 0x80808080;
      tmp_pu7 = tmp_pu6 + 1;
    } while (tmp_u4 == 0);
    if ((tmp_u3 & 0x8080) == 0) {
      tmp_pu7 = (uint *)((int)tmp_pu6 + 6);
      tmp_u4 = tmp_u4 >> 0x10;
    }
    tmp_i2 = (int)tmp_pu7 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_81c);
    local_838 = local_838 + (uint)(0 < tmp_i2);
    local_834 = local_834 + tmp_i2;
    if (tmp_u8 < 0x100) {
      tmp_pc5 = "NCS_MODELS";
LAB_001200d5:
      tmp_u1 = va("%-3d(%s) [%d] %s\n",tmp_u8,tmp_pc5,tmp_i2,local_81c);
      Q_strncpyz(local_41c,tmp_u1,0x400);
      tmp_pu7 = local_41c;
      if (param_1 != 0) {
LAB_00120170:
        G_Printf(local_41c);
        tmp_pu7 = local_41c;
      }
      do {
        tmp_pu6 = tmp_pu7;
        tmp_u3 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
        tmp_u4 = tmp_u3 & 0x80808080;
        tmp_pu7 = tmp_pu6 + 1;
      } while (tmp_u4 == 0);
      if ((tmp_u3 & 0x8080) == 0) {
        tmp_pu7 = (uint *)((int)tmp_pu6 + 6);
        tmp_u4 = tmp_u4 >> 0x10;
      }
      trap_FS_Write(local_41c,
                    (int)tmp_pu7 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_41c),
                    local_820);
      if (tmp_u8 == 0x28e) {
        tmp_u1 = va("***********************************************\nMap: %s\nN!tmod Version: %s\nTotal NGS Size: %d\nUsed NCS: %d/%d\n***********************************************\n"
                   ,&g_unk_00abe8c0,&g_unk_00249e9e,local_834,local_838,0x28f);
        Q_strncpyz(local_41c,tmp_u1,0x400);
        tmp_pu7 = local_41c;
        if (param_1 != 0) {
          G_Printf(local_41c);
        }
        do {
          tmp_pu6 = tmp_pu7;
          tmp_u4 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
          tmp_u8 = tmp_u4 & 0x80808080;
          tmp_pu7 = tmp_pu6 + 1;
        } while (tmp_u8 == 0);
        if ((tmp_u4 & 0x8080) == 0) {
          tmp_pu7 = (uint *)((int)tmp_pu6 + 6);
          tmp_u8 = tmp_u8 >> 0x10;
        }
        trap_FS_Write(local_41c,
                      (int)tmp_pu7 + ((-3 - (uint)CARRY1((byte)tmp_u8,(byte)tmp_u8)) - (int)local_41c),
                      local_820);
        trap_FS_FCloseFile(local_820);
        return;
      }
    }
    else {
      if (tmp_u8 - 0x100 < 0x100) {
        tmp_pc5 = "NCS_SOUNDS";
        goto LAB_001200d5;
      }
      if (tmp_u8 - 0x200 < 0x20) {
        tmp_pc5 = "NCS_SHADERS";
        goto LAB_001200d5;
      }
      if (tmp_u8 - 0x221 < 0x40) {
        tmp_pc5 = "NCS_SKINS";
        goto LAB_001200d5;
      }
      if (tmp_u8 - 0x261 < 0x12) {
        tmp_pc5 = "NCS_TRIGGERS";
        goto LAB_001200d5;
      }
      if (tmp_u8 - 0x273 < 0x10) {
        tmp_pc5 = "NCS_MULTI_SPAWNTARGETS";
        goto LAB_001200d5;
      }
      if (tmp_u8 != 0x220) {
        tmp_pc5 = "";
        goto LAB_001200d5;
      }
      tmp_u1 = va("%-3d(%s) [%d] %s\n",0x220,"NCS_SHADERSTATE",tmp_i2,local_81c);
      Q_strncpyz(local_41c,tmp_u1,0x400);
      tmp_pu7 = local_41c;
      if (param_1 != 0) goto LAB_00120170;
      do {
        tmp_pu6 = tmp_pu7;
        tmp_u3 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
        tmp_u4 = tmp_u3 & 0x80808080;
        tmp_pu7 = tmp_pu6 + 1;
      } while (tmp_u4 == 0);
      if ((tmp_u3 & 0x8080) == 0) {
        tmp_pu7 = (uint *)((int)tmp_pu6 + 6);
        tmp_u4 = tmp_u4 >> 0x10;
      }
      trap_FS_Write(local_41c,
                    (int)tmp_pu7 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_41c),
                    local_820);
    }
    tmp_u8 = tmp_u8 + 1;
    local_840 = (uint32_t *)((int)local_840 + 0x3fa);
  } while( true );
}

uint nitrox_LoadDBFile_commands(void)
{
  char *tmp_pc1;
  uint tmp_u2;
  int tmp_i3;
  void *__ptr;
  byte *tmp_pb4;
  uint tmp_u5;
  uint32_t tmp_u6;
  long tmp_l7;
  char tmp_c8;
  uint8_t *tmp_pu9;
  int *tmp_pi10;
  byte *tmp_pb11;
  char *tmp_pc12;
  byte *tmp_pb13;
  bool tmp_b14;
  bool tmp_b15;
  uint8_t tmp_u16;
  bool tmp_b17;
  uint8_t tmp_u18;
  byte tmp_b19;
  uint local_45c;
  int local_44c;
  uint32_t local_430;
  void *local_42c;
  uint local_428 [3];
  char local_41c [4];
  uint32_t local_418 [257];
  uint32_t uStack_14;
  
  tmp_b19 = 0;
  uStack_14 = 0x12034d;
  local_41c[0] = '\0';
  local_41c[1] = '\0';
  local_41c[2] = '\0';
  local_41c[3] = '\0';
  tmp_u2 = 0;
  do {
    tmp_u5 = tmp_u2;
    *(uint32_t *)((int)local_418 + tmp_u5) = 0;
    *(uint32_t *)((int)local_418 + tmp_u5 + 4) = 0;
    tmp_u2 = tmp_u5 + 8;
  } while (tmp_u5 + 8 < 0x3f8);
  *(uint32_t *)((int)local_418 + tmp_u5 + 8) = 0;
  tmp_i3 = trap_FS_FOpenFile("commands.db",&local_430,0);
  if (tmp_i3 < 0) {
    G_LogPrintf(
               "! [Admin::LoadCommands] WARNING: Couldn\'t open \'commands.db\' file, creating default one...\n"
               );
    tmp_i3 = trap_FS_FOpenFile("commands.db",&local_430,1);
    if (tmp_i3 < 0) {
      G_LogPrintf("! [Admin::LoadCommands] ERROR: Can not create default \'commands.db\' file\n");
      return 0;
    }
    trap_FS_Write("**********\n\n",0xc,local_430);
    trap_FS_Write("name = minbots\n",0xf,local_430);
    trap_FS_Write("exec = bot minbots [1]\n",0x17,local_430);
    trap_FS_Write("desc = Sets the minimum number of bots on the server\n",0x35,local_430);
    trap_FS_Write("levels = 1 2\n\n",0xe,local_430);
    trap_FS_Write("**********\n\n",0xc,local_430);
    trap_FS_Write("name = maxbots\n",0xf,local_430);
    trap_FS_Write("exec = bot maxbots [1]\n",0x17,local_430);
    trap_FS_Write("desc = Sets the maximum number of bots on the server\n",0x35,local_430);
    trap_FS_Write("levels = 1 2\n\n",0xe,local_430);
    trap_FS_FCloseFile(local_430);
    G_LogPrintf("| [Admin::LoadCommands] Default \'commands.db\' file created\n");
    tmp_i3 = trap_FS_FOpenFile("commands.db",&local_430,0);
  }
  if (CustomCommands != (void *)0x0) {
    __ptr = CustomCommands;
    tmp_pi10 = (int *)&CustomCommands;
    do {
      free(__ptr);
      *tmp_pi10 = 0;
      __ptr = (void *)tmp_pi10[1];
      tmp_pi10 = tmp_pi10 + 1;
    } while (__ptr != (void *)0x0);
  }
  local_42c = malloc(tmp_i3 + 1);
  trap_FS_Read(local_42c,tmp_i3,local_430);
  *(uint8_t *)((int)local_42c + tmp_i3) = 0;
  tmp_pb4 = (byte *)COM_Parse(&local_42c);
  if (*tmp_pb4 == 0) {
    local_45c = 0;
  }
  else {
    tmp_b15 = false;
    tmp_pc1 = "**********";
    tmp_pu9 = (uint8_t *)0x0;
    tmp_b17 = true;
    local_45c = 0;
    do {
      tmp_b14 = false;
      tmp_i3 = 0xb;
      tmp_pb11 = tmp_pb4;
      tmp_pb13 = (byte *)tmp_pc1;
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_b14 = *tmp_pb11 < *tmp_pb13;
        tmp_b17 = *tmp_pb11 == *tmp_pb13;
        tmp_pb11 = tmp_pb11 + (uint)tmp_b19 * -2 + 1;
        tmp_pb13 = tmp_pb13 + (uint)tmp_b19 * -2 + 1;
      } while (tmp_b17);
      if ((!tmp_b14 && !tmp_b17) == tmp_b14) {
        tmp_c8 = '\0';
        if (tmp_b15) {
          tmp_b15 = local_45c < 0x7f;
          tmp_b17 = local_45c == 0x7f;
          if (0x7f < (int)local_45c) {
            G_Error("! [Admin::LoadCommands] ERROR: MAX_COMMANDS EXCEEDED");
            return 0;
          }
          tmp_i3 = 0xb;
          (&CustomCommands)[local_45c] = tmp_pu9;
          tmp_pb11 = (byte *)tmp_pc1;
          do {
            if (tmp_i3 == 0) break;
            tmp_i3 = tmp_i3 + -1;
            tmp_b15 = *tmp_pb4 < *tmp_pb11;
            tmp_b17 = *tmp_pb4 == *tmp_pb11;
            tmp_pb4 = tmp_pb4 + (uint)tmp_b19 * -2 + 1;
            tmp_pb11 = tmp_pb11 + (uint)tmp_b19 * -2 + 1;
          } while (tmp_b17);
          tmp_c8 = (!tmp_b15 && !tmp_b17) - tmp_b15;
          local_45c = local_45c + 1;
        }
        tmp_b15 = false;
LAB_001204a7:
        if (tmp_c8 == '\0') {
          if (0x7f < (int)local_45c) {
            G_Error("| [Admin::LoadCommands] ERRROR: MAX_COMMANDS EXCEEDED");
            return 0;
          }
          tmp_pu9 = malloc(0x944);
          *tmp_pu9 = 0;
          tmp_pu9[0x40] = 0;
          tmp_pu9[0x440] = 0;
          tmp_u2 = 0;
          do {
            tmp_u5 = tmp_u2;
            *(uint32_t *)(tmp_pu9 + tmp_u5 + 0x840) = 0xffffffff;
            *(uint32_t *)(tmp_pu9 + tmp_u5 + 0x844) = 0xffffffff;
            tmp_u2 = tmp_u5 + 8;
          } while (tmp_u5 + 8 < 0x100);
          *(uint32_t *)(tmp_pu9 + tmp_u5 + 0x848) = 0xffffffff;
          tmp_b15 = true;
        }
      }
      else if (tmp_b15) {
        tmp_i3 = Q_stricmp(tmp_pb4,"command");
        if (tmp_i3 == 0) {
LAB_001206c0:
          tmp_i3 = Q_stricmp(tmp_pb4,"command");
          tmp_u16 = 0;
          tmp_u18 = tmp_i3 == 0;
          if ((bool)tmp_u18) {
            tmp_u6 = COM_GetCurrentParseLine();
            G_LogPrintf("! [Admin::LoadCommands] \'command\' is deprecated (line %d), use \'name\' instead.\n"
                        ,tmp_u6);
          }
          G_shrubbot_readconfig_string(&local_42c,tmp_pu9,0x40);
        }
        else {
          tmp_i3 = Q_stricmp(tmp_pb4,"name");
          tmp_u16 = false;
          if (tmp_i3 == 0) goto LAB_001206c0;
          tmp_i3 = 5;
          tmp_u18 = false;
          tmp_pb11 = tmp_pb4;
          tmp_pb13 = &g_unk_0025a6c1;
          do {
            if (tmp_i3 == 0) break;
            tmp_i3 = tmp_i3 + -1;
            tmp_u16 = *tmp_pb11 < *tmp_pb13;
            tmp_u18 = *tmp_pb11 == *tmp_pb13;
            tmp_pb11 = tmp_pb11 + (uint)tmp_b19 * -2 + 1;
            tmp_pb13 = tmp_pb13 + (uint)tmp_b19 * -2 + 1;
          } while ((bool)tmp_u18);
          if ((bool)tmp_u18) {
            G_shrubbot_readconfig_string(&local_42c,tmp_pu9 + 0x40,0x400);
          }
          else {
            tmp_i3 = 5;
            tmp_pb11 = tmp_pb4;
            tmp_pb13 = &g_unk_0025ef86;
            do {
              if (tmp_i3 == 0) break;
              tmp_i3 = tmp_i3 + -1;
              tmp_u16 = *tmp_pb11 < *tmp_pb13;
              tmp_u18 = *tmp_pb11 == *tmp_pb13;
              tmp_pb11 = tmp_pb11 + (uint)tmp_b19 * -2 + 1;
              tmp_pb13 = tmp_pb13 + (uint)tmp_b19 * -2 + 1;
            } while ((bool)tmp_u18);
            if ((bool)tmp_u18) {
              G_shrubbot_readconfig_string(&local_42c,tmp_pu9 + 0x440,0x400);
            }
            else {
              tmp_i3 = 7;
              tmp_pb11 = tmp_pb4;
              tmp_pb13 = (byte *)0x252d6e;
              do {
                if (tmp_i3 == 0) break;
                tmp_i3 = tmp_i3 + -1;
                tmp_u16 = *tmp_pb11 < *tmp_pb13;
                tmp_u18 = *tmp_pb11 == *tmp_pb13;
                tmp_pb11 = tmp_pb11 + (uint)tmp_b19 * -2 + 1;
                tmp_pb13 = tmp_pb13 + (uint)tmp_b19 * -2 + 1;
              } while ((bool)tmp_u18);
              if ((bool)tmp_u18) {
                local_428[0] = 0;
                tmp_pc12 = local_41c;
                local_428[1] = 0;
                local_428[2] = 0;
                G_shrubbot_readconfig_string(&local_42c,tmp_pc12,0x400);
                local_44c = 0;
                for (; tmp_c8 = *tmp_pc12, tmp_c8 != '\0'; tmp_pc12 = tmp_pc12 + 1) {
                  while (tmp_c8 != ' ') {
                    tmp_pc12 = tmp_pc12 + 1;
                    tmp_u6 = va("%c",(int)tmp_c8);
                    Q_strcat(local_428,0xc,tmp_u6);
                    tmp_c8 = *tmp_pc12;
                    if (tmp_c8 == '\0') goto LAB_0012067c;
                  }
                  tmp_l7 = strtol((char *)local_428,(char **)0x0,10);
                  local_428[0] = local_428[0] & 0xffffff00;
                  *(long *)(tmp_pu9 + local_44c * 4 + 0x840) = tmp_l7;
                  local_44c = local_44c + 1;
                }
LAB_0012067c:
                tmp_u16 = 0;
                tmp_u18 = (char)local_428[0] == '\0';
                if (!(bool)tmp_u18) {
                  tmp_u16 = 0;
                  tmp_u18 = 1;
                  tmp_l7 = strtol((char *)local_428,(char **)0x0,10);
                  *(long *)(tmp_pu9 + local_44c * 4 + 0x840) = tmp_l7;
                }
                *(uint32_t *)(tmp_pu9 + 0x940) = 0xffffffff;
              }
              else {
                tmp_u6 = COM_GetCurrentParseLine();
                G_LogPrintf("! [Admin::LoadCommands] Parse error near \'%s\' (line %d)\n",tmp_pb4,
                            tmp_u6);
              }
            }
          }
        }
        tmp_i3 = 0xb;
        tmp_pb11 = (byte *)tmp_pc1;
        do {
          if (tmp_i3 == 0) break;
          tmp_i3 = tmp_i3 + -1;
          tmp_u16 = *tmp_pb4 < *tmp_pb11;
          tmp_u18 = *tmp_pb4 == *tmp_pb11;
          tmp_pb4 = tmp_pb4 + (uint)tmp_b19 * -2 + 1;
          tmp_pb11 = tmp_pb11 + (uint)tmp_b19 * -2 + 1;
        } while ((bool)tmp_u18);
        tmp_c8 = (!(bool)tmp_u16 && !(bool)tmp_u18) - tmp_u16;
        goto LAB_001204a7;
      }
      tmp_pb4 = (byte *)COM_Parse(&local_42c);
      tmp_b17 = *tmp_pb4 == 0;
    } while (!tmp_b17);
    if (tmp_b15) {
      (&CustomCommands)[local_45c] = tmp_pu9;
      local_45c = local_45c + 1;
    }
  }
  free(local_42c);
  trap_FS_FCloseFile(local_430);
  return local_45c;
}

uint nitrox_LoadDBFile_levels(void)
{
  char *tmp_pc1;
  char tmp_c2;
  int tmp_i3;
  void *__ptr;
  byte *tmp_pb4;
  uint32_t tmp_u5;
  int *tmp_pi6;
  byte *tmp_pb7;
  byte *tmp_pb8;
  bool tmp_b9;
  bool tmp_b10;
  uint8_t tmp_u11;
  bool tmp_b12;
  uint8_t tmp_u13;
  byte tmp_b14;
  uint local_40;
  uint local_34;
  uint32_t local_24;
  void *local_20 [3];
  uint32_t uStack_14;
  
  tmp_b14 = 0;
  uStack_14 = 0x120a1b;
  tmp_i3 = trap_FS_FOpenFile("levels.db",&local_24,0);
  if (tmp_i3 < 0) {
    G_LogPrintf(
               "! [Admin::LoadLevels] WARNING: Couldn\'t open \'levels.db\' file, creating default one...\n"
               );
    tmp_i3 = trap_FS_FOpenFile("levels.db",&local_24,1);
    if (tmp_i3 < 0) {
      G_LogPrintf("! [Admin::LoadLevels] ERROR: Can not create default \'levels.db\' file\n");
      return 0;
    }
    trap_FS_Write("**********\n\n",0xc,local_24);
    trap_FS_Write("level = 0\n",10,local_24);
    trap_FS_Write("name = Guest\n",0xd,local_24);
    trap_FS_Write("flags =  time listplayers records help gibme admintest news uptime about\n",0x49,
                  local_24);
    trap_FS_Write(&g_unk_0025f3ec,0x23,local_24);
    trap_FS_Write("gsound = \n\n",0xb,local_24);
    trap_FS_Write("**********\n\n",0xc,local_24);
    trap_FS_Write("level = 1\n",10,local_24);
    trap_FS_Write("name = Server Moderator\n",0x18,local_24);
    trap_FS_Write("flags =  time listplayers records help gibme admintest spec999",0x3e,local_24);
    trap_FS_Write(" news pip pop pants uptime about stats put ban banguid\n",0x37,local_24);
    trap_FS_Write("gtext = Welcome to the administrator [n] !\n",0x2b,local_24);
    trap_FS_Write("gsound = \n\n",0xb,local_24);
    trap_FS_Write("**********\n\n",0xc,local_24);
    trap_FS_Write("level = 2\n",10,local_24);
    trap_FS_Write("name = Server Master\n",0x15,local_24);
    trap_FS_Write("flags =  all\n",0xd,local_24);
    trap_FS_Write(&g_unk_0025f4b4,0x27,local_24);
    trap_FS_Write("gsound = \n\n",0xb,local_24);
    G_LogPrintf("| [Admin::LoadLevels] Default \'levels.db\' file created\n");
    trap_FS_FCloseFile(local_24);
    tmp_i3 = trap_FS_FOpenFile("levels.db",&local_24,0);
    if (tmp_i3 < 0) {
      g_unk_02af58b8 = 0;
      return 0;
    }
  }
  if (Levels != (void *)0x0) {
    __ptr = Levels;
    tmp_pi6 = (int *)&Levels;
    do {
      free(__ptr);
      *tmp_pi6 = 0;
      __ptr = (void *)tmp_pi6[1];
      tmp_pi6 = tmp_pi6 + 1;
    } while (__ptr != (void *)0x0);
  }
  local_20[0] = malloc(tmp_i3 + 1);
  trap_FS_Read(local_20[0],tmp_i3,local_24);
  *(uint8_t *)((int)local_20[0] + tmp_i3) = 0;
  tmp_pb4 = (byte *)COM_Parse(local_20);
  if (*tmp_pb4 == 0) {
    local_40 = 0;
  }
  else {
    tmp_pc1 = "**********";
    tmp_b12 = true;
    tmp_b9 = false;
    local_40 = 0;
    local_34 = 0;
    do {
      tmp_b10 = false;
      tmp_i3 = 0xb;
      tmp_pb7 = tmp_pb4;
      tmp_pb8 = (byte *)tmp_pc1;
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_b10 = *tmp_pb7 < *tmp_pb8;
        tmp_b12 = *tmp_pb7 == *tmp_pb8;
        tmp_pb7 = tmp_pb7 + (uint)tmp_b14 * -2 + 1;
        tmp_pb8 = tmp_pb8 + (uint)tmp_b14 * -2 + 1;
      } while (tmp_b12);
      if ((!tmp_b10 && !tmp_b12) == tmp_b10) {
        tmp_c2 = '\0';
        if (tmp_b9) {
          tmp_b9 = local_40 < 0x3f;
          tmp_b12 = local_40 == 0x3f;
          if (0x3f < (int)local_40) goto LAB_00120d64;
          (&Levels)[local_40] = (void *)local_34;
          tmp_i3 = 0xb;
          tmp_pb7 = (byte *)tmp_pc1;
          do {
            if (tmp_i3 == 0) break;
            tmp_i3 = tmp_i3 + -1;
            tmp_b9 = *tmp_pb4 < *tmp_pb7;
            tmp_b12 = *tmp_pb4 == *tmp_pb7;
            tmp_pb4 = tmp_pb4 + (uint)tmp_b14 * -2 + 1;
            tmp_pb7 = tmp_pb7 + (uint)tmp_b14 * -2 + 1;
          } while (tmp_b12);
          tmp_c2 = (!tmp_b9 && !tmp_b12) - tmp_b9;
          local_40 = local_40 + 1;
        }
        tmp_b9 = false;
LAB_00120b3b:
        if (tmp_c2 == '\0') {
          if (0x3f < (int)local_40) {
LAB_00120d64:
            G_Error("! [Admin::LoadLevels] ERROR: MAX_LEVELS EXCEEDED");
            trap_FS_FCloseFile(local_24);
            return 0;
          }
          local_34 = AllocLevel();
          tmp_b9 = true;
        }
      }
      else {
        tmp_u11 = false;
        tmp_u13 = !tmp_b9;
        if (!(bool)tmp_u13) {
          tmp_i3 = 6;
          tmp_pb7 = tmp_pb4;
          tmp_pb8 = (byte *)0x252df8;
          do {
            if (tmp_i3 == 0) break;
            tmp_i3 = tmp_i3 + -1;
            tmp_u11 = *tmp_pb7 < *tmp_pb8;
            tmp_u13 = *tmp_pb7 == *tmp_pb8;
            tmp_pb7 = tmp_pb7 + (uint)tmp_b14 * -2 + 1;
            tmp_pb8 = tmp_pb8 + (uint)tmp_b14 * -2 + 1;
          } while ((bool)tmp_u13);
          if ((bool)tmp_u13) {
            G_shrubbot_readconfig_int(local_20,local_34);
          }
          else {
            tmp_i3 = 5;
            tmp_b12 = false;
            tmp_pb7 = tmp_pb4;
            tmp_pb8 = (byte *)0x249a02;
            do {
              if (tmp_i3 == 0) break;
              tmp_i3 = tmp_i3 + -1;
              tmp_b12 = *tmp_pb7 == *tmp_pb8;
              tmp_pb7 = tmp_pb7 + (uint)tmp_b14 * -2 + 1;
              tmp_pb8 = tmp_pb8 + (uint)tmp_b14 * -2 + 1;
            } while (tmp_b12);
            if (tmp_b12) {
              tmp_u11 = 0xfffffffb < local_34;
              tmp_u13 = local_34 + 4 == 0;
              G_shrubbot_readconfig_string(local_20,local_34 + 4,0x24);
            }
            else {
              tmp_i3 = 6;
              tmp_b12 = false;
              tmp_pb7 = tmp_pb4;
              tmp_pb8 = (byte *)0x24ab9a;
              do {
                if (tmp_i3 == 0) break;
                tmp_i3 = tmp_i3 + -1;
                tmp_b12 = *tmp_pb7 == *tmp_pb8;
                tmp_pb7 = tmp_pb7 + (uint)tmp_b14 * -2 + 1;
                tmp_pb8 = tmp_pb8 + (uint)tmp_b14 * -2 + 1;
              } while (tmp_b12);
              if (tmp_b12) {
                tmp_u11 = 0xffffffd7 < local_34;
                tmp_u13 = local_34 + 0x28 == 0;
                G_shrubbot_readconfig_string(local_20,local_34 + 0x28,0x400);
                nitrox_SetLevelPermissions(local_34);
                nitrox_SetLevelCommandPermissions(local_34);
              }
              else {
                tmp_i3 = 6;
                tmp_b12 = false;
                tmp_pb7 = tmp_pb4;
                tmp_pb8 = &g_unk_00252693;
                do {
                  if (tmp_i3 == 0) break;
                  tmp_i3 = tmp_i3 + -1;
                  tmp_b12 = *tmp_pb7 == *tmp_pb8;
                  tmp_pb7 = tmp_pb7 + (uint)tmp_b14 * -2 + 1;
                  tmp_pb8 = tmp_pb8 + (uint)tmp_b14 * -2 + 1;
                } while (tmp_b12);
                if (tmp_b12) {
                  tmp_u11 = 0xfffffbd7 < local_34;
                  tmp_u13 = local_34 + 0x428 == 0;
                  G_shrubbot_readconfig_string(local_20,local_34 + 0x428,0x400);
                }
                else {
                  tmp_i3 = Q_stricmp(tmp_pb4,"gsound");
                  tmp_u11 = 0;
                  tmp_u13 = tmp_i3 == 0;
                  if ((bool)tmp_u13) {
                    tmp_u11 = 0xfffff7d7 < local_34;
                    tmp_u13 = local_34 + 0x828 == 0;
                    G_shrubbot_readconfig_string(local_20,local_34 + 0x828,0x400);
                  }
                  else {
                    tmp_u5 = COM_GetCurrentParseLine();
                    G_LogPrintf("! [Admin::LoadLevels] Parse error near \'%s\' (line %d)\n",tmp_pb4,
                                tmp_u5);
                  }
                }
              }
            }
          }
          tmp_i3 = 0xb;
          tmp_pb7 = (byte *)tmp_pc1;
          do {
            if (tmp_i3 == 0) break;
            tmp_i3 = tmp_i3 + -1;
            tmp_u11 = *tmp_pb4 < *tmp_pb7;
            tmp_u13 = *tmp_pb4 == *tmp_pb7;
            tmp_pb4 = tmp_pb4 + (uint)tmp_b14 * -2 + 1;
            tmp_pb7 = tmp_pb7 + (uint)tmp_b14 * -2 + 1;
          } while ((bool)tmp_u13);
          tmp_c2 = (!(bool)tmp_u11 && !(bool)tmp_u13) - tmp_u11;
          goto LAB_00120b3b;
        }
      }
      tmp_pb4 = (byte *)COM_Parse(local_20);
      tmp_b12 = *tmp_pb4 == 0;
    } while (!tmp_b12);
    if (tmp_b9) {
      (&Levels)[local_40] = (void *)local_34;
      local_40 = local_40 + 1;
    }
  }
  free(local_20[0]);
  trap_FS_FCloseFile(local_24);
  return local_40;
}

void nitrox_SaveDBFile_levels(void)
{
  int tmp_i1;
  int *tmp_pi2;
  uint32_t local_10;
  
  local_10 = 0x12107d;
  tmp_i1 = trap_FS_FOpenFile("levels.db",&local_10,1);
  if (tmp_i1 < 0) {
    G_LogPrintf("| [Admin::SaveLevels] Couldn\'t open \'levels.db\' file\n");
  }
  else {
    tmp_pi2 = &Levels;
    tmp_i1 = Levels;
    while (tmp_i1 != 0) {
      while (*(int *)(tmp_i1 + 0xc28) != 0) {
        tmp_pi2 = tmp_pi2 + 1;
        tmp_i1 = *tmp_pi2;
        if (tmp_i1 == 0) goto LAB_00121228;
      }
      trap_FS_Write("**********\n\n",0xc,local_10);
      trap_FS_Write("level = ",8,local_10);
      G_shrubbot_writeconfig_int(*(uint32_t *)*tmp_pi2,local_10);
      trap_FS_Write("name = ",7,local_10);
      G_shrubbot_writeconfig_string(*tmp_pi2 + 4,local_10);
      trap_FS_Write("flags = ",8,local_10);
      G_shrubbot_writeconfig_string(*tmp_pi2 + 0x28,local_10);
      trap_FS_Write("gtext = ",8,local_10);
      G_shrubbot_writeconfig_string(*tmp_pi2 + 0x428,local_10);
      trap_FS_Write("gsound = ",9,local_10);
      G_shrubbot_writeconfig_string(*tmp_pi2 + 0x828,local_10);
      trap_FS_Write("\n",1,local_10);
      tmp_i1 = tmp_pi2[1];
      tmp_pi2 = tmp_pi2 + 1;
    }
LAB_00121228:
    trap_FS_FCloseFile(local_10);
  }
  return;
}

void nitrox_CreateLevelZero(void)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  
  tmp_i3 = 0;
  tmp_i1 = Levels;
  do {
    if (tmp_i1 == 0) {
      tmp_i3 = 0;
      break;
    }
    tmp_i3 = tmp_i3 + 1;
    tmp_i1 = (&Levels)[tmp_i3];
  } while (tmp_i1 != 0);
  tmp_pu2 = (uint32_t *)AllocLevel();
  *tmp_pu2 = 0;
  Q_strncpyz(tmp_pu2 + 10,"help listplayers admintest time records gibme about stats spec",0x400);
  (&Levels)[tmp_i3] = (int)tmp_pu2;
  nitrox_SetLevelPermissions(tmp_pu2);
  nitrox_SetLevelCommandPermissions(tmp_pu2);
  return;
}

uint32_t nitrox_LoadDBFiles(uint32_t param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t *tmp_pu4;
  uint8_t *tmp_pu5;
  uint8_t *tmp_pu6;
  int tmp_i7;
  
  if (g_unk_02af58b8 != 0) {
    tmp_i1 = nitrox_LoadDBFile_levels();
    tmp_i2 = nitrox_LevelExists(0);
    if ((tmp_i2 == 0) || (tmp_i1 == 0)) {
      tmp_i7 = 0;
      G_LogPrintf(
                 "! [Admin::LoadLevels] WARNING! Level \'0\' not found. Automaticly generating...\n"
                 );
      tmp_i2 = Levels;
      do {
        if (tmp_i2 == 0) {
          tmp_i7 = 0;
          break;
        }
        tmp_i7 = tmp_i7 + 1;
        tmp_i2 = (&Levels)[tmp_i7];
      } while (tmp_i2 != 0);
      tmp_pu4 = (uint32_t *)AllocLevel();
      *tmp_pu4 = 0;
      Q_strncpyz(tmp_pu4 + 10,"help listplayers admintest time records gibme about stats spec",0x400)
      ;
      (&Levels)[tmp_i7] = (int)tmp_pu4;
      nitrox_SetLevelPermissions(tmp_pu4);
      nitrox_SetLevelCommandPermissions(tmp_pu4);
      nitrox_SaveDBFile_levels();
      tmp_i2 = nitrox_LoadDBFile_commands();
    }
    else {
      tmp_i2 = nitrox_LoadDBFile_commands();
    }
    if (g_unk_02af58b8 != 0) {
      tmp_pu5 = &g_unk_0024e6ea;
      if (tmp_i2 < 2) {
        tmp_pu5 = &g_unk_0026ea14;
      }
      tmp_pu6 = &g_unk_0024e6ea;
      if (tmp_i1 < 2) {
        tmp_pu6 = &g_unk_0026ea14;
      }
      if (param_2 == -1) {
        G_LogPrintf("| [Admin::LoadCommands] Loaded %d level%s, %d command%s\n",tmp_i1,tmp_pu6,tmp_i2,
                    tmp_pu5);
      }
      else {
        tmp_u3 = va("^xreadconfig: ^9Loaded ^g%d ^9level%s, ^g%d ^9command%s\n");
        G_shrubbot_print(param_1,tmp_u3);
      }
      if (g_unk_02af58b8 != 0) {
        G_customVoteLoad();
        return 1;
      }
    }
    G_shrubbot_cleanup();
  }
  return 0;
}

bool nitrox_CreateScreenshotsFolder(void)
{
  uint tmp_u1;
  uint tmp_u2;
  int tmp_i3;
  bool tmp_b4;
  char local_30c [4];
  uint32_t local_308 [191];
  
  local_30c[0] = '\0';
  local_30c[1] = '\0';
  local_30c[2] = '\0';
  local_30c[3] = '\0';
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_308 + tmp_u2) = 0;
    *(uint32_t *)((int)local_308 + tmp_u2 + 4) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xf8);
  *(uint32_t *)((int)local_308 + tmp_u2 + 8) = 0;
  local_308[0x3f] = 0;
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x100) = 0;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x104) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xf8);
  *(uint32_t *)((int)local_308 + tmp_u2 + 0x108) = 0;
  local_308[0x7f] = 0;
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x200) = 0;
    *(uint32_t *)((int)local_308 + tmp_u2 + 0x204) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xf8);
  *(uint32_t *)((int)local_308 + tmp_u2 + 0x208) = 0;
  trap_Cvar_VariableStringBuffer("fs_homepath",local_308 + 0x7f,0x100);
  trap_Cvar_VariableStringBuffer("fs_game",local_308 + 0x3f,0x100);
  Com_sprintf(local_30c,0x100,"%s%s%s%sNxAC%sscreenshots",local_308 + 0x7f,&g_unk_0024ed91,
              local_308 + 0x3f,&g_unk_0024ed91,&g_unk_0024ed91);
  Q_strncpyz(&g_unk_02b9a338,local_30c,0x100);
  tmp_i3 = BG_IsDirectory(local_30c);
  tmp_b4 = true;
  if (tmp_i3 == 0) {
    tmp_i3 = mkdir(local_30c,0x1c0);
    tmp_b4 = tmp_i3 == 0;
  }
  return tmp_b4;
}

uint32_t nitrox_GetTokenForString(char *param_1)
{
  size_t tmp_s1;
  int tmp_i2;
  
  tmp_s1 = strlen(param_1);
  tmp_i2 = in_word_set(param_1,tmp_s1);
  if (tmp_i2 != 0) {
    return *(uint32_t *)(tmp_i2 + 4);
  }
  return 0x117;
}

void nitrox_ClearInvalidUsers_part_0(void)
{
  char *tmp_pc1;
  size_t tmp_s2;
  uint8_t *tmp_pu3;
  int *tmp_pi4;
  int tmp_i5;
  int tmp_i6;
  
  G_LogPrintf("| [Admin::ClearInvalidUsers] Looking for invalid users...\n");
  tmp_pi4 = &Users;
  if (Users != 0) {
    tmp_i6 = 0;
    tmp_i5 = Users;
    do {
      if (*(char *)(tmp_i5 + 4) == '\0') {
LAB_001fd120:
        tmp_i5 = tmp_i5 + 0x25;
        tmp_pc1 = "| [Admin::ClearInvalidUsers] User \'%s\': Invalid NGUID\n";
LAB_001fd12b:
        tmp_i6 = tmp_i6 + 1;
        G_LogPrintf(tmp_pc1,tmp_i5);
        *(uint32_t *)(*tmp_pi4 + 0x10e0) = 1;
      }
      else {
        tmp_s2 = strlen((char *)(tmp_i5 + 4));
        if (tmp_s2 != 0x20) goto LAB_001fd120;
        if (*(char *)(tmp_i5 + 0xc50) == '\0') {
LAB_001fd182:
          tmp_i5 = tmp_i5 + 0x25;
          tmp_pc1 = "| [Admin::ClearInvalidUsers] User \'%s\': Invalid MAC Address\n";
          goto LAB_001fd12b;
        }
        tmp_s2 = strlen((char *)(tmp_i5 + 0xc50));
        if (tmp_s2 != 0x11) goto LAB_001fd182;
        if (*(char *)(tmp_i5 + 0x1078) != '\0') {
          tmp_i5 = nitrox_AlphaNumValid(tmp_i5 + 0x1078);
          if (tmp_i5 != 0) goto LAB_001fd1a1;
          tmp_i5 = *tmp_pi4 + 0x25;
          tmp_pc1 = 
          "| [Admin::ClearInvalidUsers] User \'%s\': Login field contains invalid characters\n";
          goto LAB_001fd12b;
        }
LAB_001fd1a1:
        if (*(char *)(*tmp_pi4 + 0x1099) != '\0') {
          tmp_i5 = nitrox_AlphaNumValid(*tmp_pi4 + 0x1099);
          if (tmp_i5 == 0) {
            tmp_i5 = *tmp_pi4 + 0x25;
            tmp_pc1 = 
            "| [Admin::ClearInvalidUsers] User \'%s\': Password field contains invalid characters\n"
            ;
            goto LAB_001fd12b;
          }
        }
      }
      tmp_pi4 = tmp_pi4 + 1;
      tmp_i5 = *tmp_pi4;
    } while (tmp_i5 != 0);
    if (tmp_i6 != 0) {
      nitrox_SaveUsers(0,0xffffffff);
      tmp_pu3 = &g_unk_0024e6ea;
      if (tmp_i6 == 1) {
        tmp_pu3 = &g_unk_0026ea14;
      }
      G_LogPrintf("| [Admin::ClearInvalidUsers] Cleared %d invalid user%s.\nReloading...",tmp_i6,
                  tmp_pu3);
      nitrox_LoadUsers();
    }
  }
  return;
}

void nitrox_ClearInvalidUsers(void)
{
  if (g_unk_02af58b8 == 0) {
    return;
  }
  nitrox_ClearInvalidUsers_part_0();
  return;
}

uint32_t nitrox_LevelExists(int param_1)
{
  int *tmp_pi1;
  uint32_t *tmp_pu2;
  
  if (Levels == (int *)0x0) {
    return 0;
  }
  if (*Levels != param_1) {
    tmp_pu2 = &g_unk_02db0c44;
    do {
      tmp_pi1 = (int *)*tmp_pu2;
      if (tmp_pi1 == (int *)0x0) {
        return 0;
      }
      tmp_pu2 = tmp_pu2 + 1;
    } while (*tmp_pi1 != param_1);
  }
  return 1;
}

int * nitrox_LevelPointer(int param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  int *tmp_pi3;
  uint32_t *tmp_pu4;
  uint32_t *tmp_pu5;
  
  if (Levels == (int *)0x0) {
    tmp_pi3 = (int *)0x0;
  }
  else {
    tmp_i1 = *Levels;
    tmp_pi3 = Levels;
    if (tmp_i1 != param_1) {
      tmp_pu4 = &g_unk_02db0c44;
      tmp_pu5 = tmp_pu4;
      do {
        tmp_pi3 = (int *)*tmp_pu5;
        tmp_pi2 = Levels;
        if (tmp_pi3 == (int *)0x0) {
          while( true ) {
            if (tmp_i1 == 0) {
              return tmp_pi2;
            }
            tmp_pi2 = (int *)*tmp_pu4;
            if (tmp_pi2 == (int *)0x0) break;
            tmp_i1 = *tmp_pi2;
            tmp_pu4 = tmp_pu4 + 1;
          }
          return (int *)0x0;
        }
        tmp_pu5 = tmp_pu5 + 1;
      } while (*tmp_pi3 != param_1);
    }
  }
  return tmp_pi3;
}

void nitrox_OpenNxACListenSocket(void)
{
  uint tmp_u1;
  ushort tmp_u2;
  uint tmp_u3;
  long tmp_l4;
  int tmp_i5;
  uint32_t tmp_u6;
  uint32_t *__s;
  uint32_t *tmp_pu7;
  socklen_t local_124;
  uint32_t local_120;
  sockaddr local_11c;
  uint32_t local_10c;
  uint32_t local_108 [63];
  
  local_108[0x3e] = 0x1fe3cf;
  local_10c = 0;
  local_124 = 0x10;
  tmp_u1 = 0;
  do {
    tmp_u3 = tmp_u1;
    *(uint32_t *)((int)local_108 + tmp_u3) = 0;
    *(uint32_t *)((int)local_108 + tmp_u3 + 4) = 0;
    tmp_u1 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0xf8);
  *(uint32_t *)((int)local_108 + tmp_u3 + 8) = 0;
  local_120 = 1;
  __s = &NxACClients;
  do {
    tmp_pu7 = __s + 0x1058;
    memset(__s,0,0x4160);
    __s = tmp_pu7;
  } while (tmp_pu7 != &NxAC_svPort);
  NxAC_svSocket = socket(2,1,0);
  if (NxAC_svSocket != -1) {
    ioctl(NxAC_svSocket,0x5421,&local_120);
    local_11c.sa_data[6] = '\0';
    local_11c.sa_data[7] = '\0';
    local_11c.sa_data[8] = '\0';
    local_11c.sa_data[9] = '\0';
    local_11c.sa_data[10] = '\0';
    local_11c.sa_data[0xb] = '\0';
    local_11c.sa_data[0xc] = '\0';
    local_11c.sa_data[0xd] = '\0';
    local_11c.sa_data[2] = '\0';
    local_11c.sa_data[3] = '\0';
    local_11c.sa_data[4] = '\0';
    local_11c.sa_data[5] = '\0';
    local_11c.sa_family = 2;
    local_11c.sa_data[0] = '\0';
    local_11c.sa_data[1] = '\0';
    trap_Cvar_VariableStringBuffer("net_port",&local_10c,0x100);
    tmp_l4 = strtol((char *)&local_10c,(char **)0x0,10);
    tmp_u2 = (ushort)tmp_l4 >> 8 | (ushort)tmp_l4 << 8;
    local_11c.sa_data[0] = (char)tmp_u2;
    local_11c.sa_data[1] = (char)(tmp_u2 >> 8);
    trap_Cvar_VariableStringBuffer("net_ip",&local_10c,0x100);
    tmp_i5 = Q_stricmp(&local_10c,"localhost");
    if ((tmp_i5 == 0) || (tmp_i5 = Q_stricmp(&local_10c,"127.0.0.1"), tmp_i5 == 0)) {
      local_11c.sa_data[2] = '\0';
      local_11c.sa_data[3] = '\0';
      local_11c.sa_data[4] = '\0';
      local_11c.sa_data[5] = '\0';
    }
    else {
      local_11c.GHIDRA_FIELD(sa_data, 2, 4) = inet_addr((char *)&local_10c);
    }
    tmp_i5 = setsockopt(NxAC_svSocket,1,2,&local_120,4);
    if (tmp_i5 < 0) {
      close(NxAC_svSocket);
      NxAC_svSocket = 0;
      tmp_i5 = bind(0,&local_11c,local_124);
    }
    else {
      tmp_i5 = bind(NxAC_svSocket,&local_11c,local_124);
    }
    if (tmp_i5 < 0) {
      close(NxAC_svSocket);
      NxAC_svSocket = 0;
      return;
    }
    getsockname(NxAC_svSocket,&local_11c,&local_124);
    NxAC_svPort = (uint)(ushort)((ushort)local_11c.GHIDRA_FIELD(sa_data, 0, 2) >> 8 | local_11c.GHIDRA_FIELD(sa_data, 0, 2) << 8
                                );
    tmp_u6 = va("%i",NxAC_svPort);
    trap_Cvar_Register(0,"nport",tmp_u6,0x44);
    tmp_u6 = va("%i",NxAC_svPort);
    trap_Cvar_Set("nport",tmp_u6);
    listen(NxAC_svSocket,0x40);
  }
  return;
}

void nitrox_OpenMasterSocket(void)
{
  uint tmp_u1;
  uint tmp_u2;
  int tmp_i3;
  int tmp_i4;
  hostent *phVar5;
  char *__cp;
  uint32_t local_110;
  char local_10c [4];
  uint32_t local_108 [63];
  
  local_108[0x3e] = 0x1fe6aa;
  local_10c[0] = '\0';
  local_10c[1] = '\0';
  local_10c[2] = '\0';
  local_10c[3] = '\0';
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)local_108 + tmp_u2) = 0;
    *(uint32_t *)((int)local_108 + tmp_u2 + 4) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xf8);
  *(uint32_t *)((int)local_108 + tmp_u2 + 8) = 0;
  local_110 = 1;
  g_unk_02b99228 = 0;
  sock = socket(2,2,0x11);
  if (sock == -1) {
    close(-1);
    sock = 0;
    return;
  }
  ioctl(sock,0x5421,&local_110);
  _DAT_0083d384 = 0;
  _DAT_0083d388 = 0;
  g_unk_0083d380 = 0;
  _sv_sin = 0;
  trap_Cvar_VariableStringBuffer("net_ip",local_10c,0x100);
  tmp_i3 = Q_stricmp(local_10c,"localhost");
  if (tmp_i3 != 0) {
    tmp_i3 = Q_stricmp(local_10c,"127.0.0.1");
    if (tmp_i3 != 0) {
      g_unk_0083d380 = inet_addr(local_10c);
      goto LAB_001fe79b;
    }
  }
  g_unk_0083d380 = 0;
LAB_001fe79b:
  tmp_i3 = sock;
  _sv_sin = CONCAT22(sv_sin_2,2);
  tmp_i4 = bind(sock,(sockaddr *)&sv_sin,0x10);
  if (tmp_i4 == -1) {
    close(tmp_i3);
    sock = 0;
    return;
  }
  phVar5 = gethostbyname("master.etmods.net");
  if (phVar5 != (hostent *)0x0) {
    __cp = inet_ntoa((in_addr)*(in_addr_t *)*phVar5->h_addr_list);
    _DAT_0083d390 = inet_addr(__cp);
    g_unk_02b99228 = 1;
    _DAT_0083d38e = 0x1b21;
    cl_sin = 2;
    return;
  }
  close(sock);
  sock = 0;
  return;
}

void nitrox_CloseMasterSocket(void)
{
  if (sock != 0) {
    close(sock);
    sock = 0;
  }
  if (NxAC_svSocket != 0) {
    close(NxAC_svSocket);
    NxAC_svSocket = 0;
  }
  g_unk_02b99228 = 0;
  return;
}

void nitrox_SendStatsToMaster(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  size_t tmp_s3;
  uint32_t tmp_u4;
  uint tmp_u5;
  uint tmp_u6;
  uint *tmp_pu7;
  uint *tmp_pu8;
  int tmp_i9;
  uint local_11c;
  uint32_t local_118 [66];
  
  local_11c = 0;
  tmp_u6 = 0;
  do {
    tmp_u5 = tmp_u6;
    *(uint32_t *)((int)local_118 + tmp_u5) = 0;
    *(uint32_t *)((int)local_118 + tmp_u5 + 4) = 0;
    tmp_u6 = tmp_u5 + 8;
  } while (tmp_u5 + 8 < 0xf8);
  *(uint32_t *)((int)local_118 + tmp_u5 + 8) = 0;
  if ((((param_1 != 0) && (g_unk_02b99228 != 0)) && (tmp_i1 = *(int *)(param_1 + 400), tmp_i1 != 0)) &&
     (1 < GHIDRA_FIELD(g_gamestate, 12, 4) - 1)) {
    tmp_i9 = param_1 + -0x93e4a0 >> 9;
    if ((((&g_unk_00abe8ac)[(int)(&g_unk_00836e60 + tmp_i9 * -0x55555555)] != 1) &&
        ((*(byte *)(param_1 + 0x128) & 8) == 0)) &&
       (tmp_s3 = strlen((char *)(tmp_i1 + 0x61c)), 0x1f < tmp_s3)) {
      tmp_i2 = (g_unk_00abe908 - *(int *)(tmp_i1 + 0x674)) / 60000;
      tmp_i1 = tmp_i9 * -0x55555555 + 0x836a6;
      (&g_unk_02b99238)[tmp_i9 * -0x15555550] = tmp_i2;
      if ((((0 < (int)(&g_unk_00abe8ac)[tmp_i1 * 0x10]) ||
           (0 < (int)(&g_unk_02b99230)[tmp_i9 * -0x15555550])) ||
          ((((0 < (int)(&g_unk_02b99234)[tmp_i9 * -0x15555550] ||
             (((0 < (int)(&g_unk_02b9923c)[tmp_i9 * -0x15555550] ||
               (0 < (int)(&g_unk_02b99240)[tmp_i9 * -0x15555550])) ||
              (0 < (int)(&g_unk_02b99244)[tmp_i9 * -0x15555550])))) ||
            ((0 < (int)(&g_unk_02b99248)[tmp_i9 * -0x15555550] ||
             (0 < (int)(&g_unk_02b9924c)[tmp_i9 * -0x15555550])))) ||
           (0 < (int)(&g_unk_02b99250)[tmp_i9 * -0x15555550])))) ||
         (((0 < (int)(&g_unk_02b99254)[tmp_i9 * -0x15555550] ||
           (0 < (int)(&g_unk_02b9925c)[tmp_i9 * -0x15555550])) ||
          ((0 < (int)(&g_unk_02b99260)[tmp_i9 * -0x15555550] ||
           ((0 < (int)(&g_unk_02b99264)[tmp_i9 * -0x15555550] ||
            (0 < (int)(&g_unk_02b99268)[tmp_i9 * -0x15555550])))))))) {
        local_11c = CONCAT31(GHIDRA_FIELD(local_11c, 1, 3),0xb0);
        tmp_u4 = va("ps %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %s",
                   *(int *)(param_1 + 400) + 0x61c,(&g_unk_00abe8ac)[tmp_i1 * 0x10],
                   (&g_unk_02b99230)[tmp_i9 * -0x15555550],(&g_unk_02b99234)[tmp_i9 * -0x15555550],tmp_i2,
                   (&g_unk_02b9923c)[tmp_i9 * -0x15555550],(&g_unk_02b99240)[tmp_i9 * -0x15555550],
                   (&g_unk_02b99244)[tmp_i9 * -0x15555550],(&g_unk_02b99248)[tmp_i9 * -0x15555550],
                   (&g_unk_02b9924c)[tmp_i9 * -0x15555550],(&g_unk_02b99250)[tmp_i9 * -0x15555550],
                   (&g_unk_02b99254)[tmp_i9 * -0x15555550],(&g_unk_02b99258)[tmp_i9 * -0x15555550],
                   (&g_unk_02b9925c)[tmp_i9 * -0x15555550],(&g_unk_02b99260)[tmp_i9 * -0x15555550],
                   (&g_unk_02b99264)[tmp_i9 * -0x15555550],(&g_unk_02b99268)[tmp_i9 * -0x15555550],
                   *(int *)(param_1 + 400) + 0x5f8);
        Q_strcat(&local_11c,0x100,tmp_u4);
        tmp_pu8 = &local_11c;
        do {
          tmp_pu7 = tmp_pu8;
          tmp_u5 = *tmp_pu7 + 0xfefefeff & ~*tmp_pu7;
          tmp_u6 = tmp_u5 & 0x80808080;
          tmp_pu8 = tmp_pu7 + 1;
        } while (tmp_u6 == 0);
        if ((tmp_u5 & 0x8080) == 0) {
          tmp_pu8 = (uint *)((int)tmp_pu7 + 6);
          tmp_u6 = tmp_u6 >> 0x10;
        }
        sendto(sock,&local_11c,
               (int)tmp_pu8 + (-(int)&local_11c - (uint)CARRY1((byte)tmp_u6,(byte)tmp_u6)) + -2,0,
               (sockaddr *)&cl_sin,0x10);
        tmp_u6 = 0;
        do {
          *(uint32_t *)((int)&g_unk_02b9922c + tmp_u6 + tmp_i9 * -0x55555540) = 0;
          *(uint32_t *)((int)&g_unk_02b99230 + tmp_u6 + tmp_i9 * -0x55555540) = 0;
          tmp_u6 = tmp_u6 + 8;
        } while (tmp_u6 < 0x40);
        (&g_unk_00abe8ac)[(int)(&g_unk_00836e60 + tmp_i9 * -0x55555555)] = 1;
      }
    }
  }
  return;
}

void nitrox_QueryGlobalStats(char *param_1)
{
  size_t tmp_s1;
  uint32_t tmp_u2;
  uint tmp_u3;
  uint tmp_u4;
  uint *tmp_pu5;
  uint *tmp_pu6;
  uint local_10c [65];
  
  local_10c[0] = 0;
  tmp_u4 = 0;
  do {
    tmp_u3 = tmp_u4;
    *(uint32_t *)((int)local_10c + tmp_u3 + 4) = 0;
    *(uint32_t *)((int)local_10c + tmp_u3 + 8) = 0;
    tmp_u4 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0xf8);
  *(uint32_t *)((int)local_10c + tmp_u3 + 0xc) = 0;
  if ((g_unk_02b99228 != 0) && (tmp_s1 = strlen(param_1), 0x1f < tmp_s1)) {
    local_10c[0] = CONCAT31(local_10c[0]._1_3_,0xb0);
    tmp_u2 = va("gsg %s",param_1);
    Q_strcat(local_10c,0x100,tmp_u2);
    tmp_pu6 = local_10c;
    do {
      tmp_pu5 = tmp_pu6;
      tmp_u3 = *tmp_pu5 + 0xfefefeff & ~*tmp_pu5;
      tmp_u4 = tmp_u3 & 0x80808080;
      tmp_pu6 = tmp_pu5 + 1;
    } while (tmp_u4 == 0);
    if ((tmp_u3 & 0x8080) == 0) {
      tmp_pu6 = (uint *)((int)tmp_pu5 + 6);
      tmp_u4 = tmp_u4 >> 0x10;
    }
    sendto(sock,local_10c,
           (int)tmp_pu6 + (-(int)local_10c - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) + -2,0,
           (sockaddr *)&cl_sin,0x10);
  }
  return;
}

void nitrox_PlayerStatsReceivedFromMaster(int param_1)
{
  uint tmp_u1;
  uint tmp_u2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint32_t local_7d;
  uint8_t local_79;
  uint32_t local_78 [7];
  uint32_t local_5c [19];
  
  local_7d = 0;
  local_79 = 0;
  tmp_u2 = 0;
  do {
    tmp_u1 = tmp_u2;
    *(uint32_t *)((int)local_78 + tmp_u1) = 0;
    *(uint32_t *)((int)local_78 + tmp_u1 + 4) = 0;
    tmp_u2 = tmp_u1 + 8;
  } while (tmp_u1 + 8 < 0x18);
  *(uint32_t *)((int)local_78 + tmp_u1 + 8) = 0;
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)local_5c + tmp_u2) = 0;
    *(uint32_t *)((int)local_5c + tmp_u2 + 4) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x40);
  __isoc99_sscanf(param_1,"%s %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i",&local_7d,local_5c,
                  local_5c + 1,local_5c + 2,local_5c + 3,local_5c + 4,local_5c + 5,local_5c + 6,
                  local_5c + 7,local_5c + 8,local_5c + 9,local_5c + 10,local_5c + 0xb,local_5c + 0xc
                  ,local_5c + 0xd,local_5c + 0xe);
  if (0 < g_unk_00abe938) {
    tmp_i6 = 0;
    tmp_i5 = g_unk_00abe938;
    do {
      tmp_i3 = (&g_unk_00abe944)[tmp_i6] * 0x600;
      if ((((tmp_i3 != -0x93e4a0) && (*(int *)(g_entities + tmp_i3 + 400) != 0)) &&
          (tmp_i4 = Q_stricmp(*(int *)(g_entities + tmp_i3 + 400) + 0xeec,&local_7d),
          tmp_i5 = g_unk_00abe938, tmp_i4 == 0)) &&
         (*(int *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb8c) == 0)) {
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb48) = local_5c[0];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb4c) = local_5c[1];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb50) = local_5c[2];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb54) = local_5c[3];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb58) = local_5c[4];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb5c) = local_5c[5];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb60) = local_5c[6];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb64) = local_5c[7];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb68) = local_5c[8];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb6c) = local_5c[9];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb70) = local_5c[10];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb74) = local_5c[0xb];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb78) = local_5c[0xc];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb7c) = local_5c[0xd];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb80) = local_5c[0xe];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb84) = local_5c[0xf];
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb8c) = 1;
        *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb90) = 0;
        G_LuaHook_ReceivedGlobalStats((tmp_i3 >> 9) * -0x55555555,param_1 + 0x21);
        return;
      }
      tmp_i6 = tmp_i6 + 1;
    } while (tmp_i6 < tmp_i5);
  }
  return;
}

int nitrox_FindPacketEntity
              (uint32_t param_1,in_addr param_2,uint32_t param_3,uint32_t param_4,uint param_5
              )

{
  uint tmp_u1;
  char *tmp_pc2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint8_t *tmp_pu6;
  uint32_t local_41c;
  uint32_t local_418 [257];
  uint32_t uStack_14;
  
  tmp_i5 = 0;
  uStack_14 = 0x1ff20b;
  tmp_pu6 = g_entities;
  do {
    if (*(int *)(tmp_pu6 + 0x194) != 0) {
      local_41c = 0;
      tmp_u3 = 0;
      do {
        tmp_u1 = tmp_u3;
        *(uint32_t *)((int)local_418 + tmp_u1) = 0;
        *(uint32_t *)((int)local_418 + tmp_u1 + 4) = 0;
        tmp_u3 = tmp_u1 + 8;
      } while (tmp_u1 + 8 < 0x3f8);
      *(uint32_t *)((int)local_418 + tmp_u1 + 8) = 0;
      trap_GetUserinfo(tmp_i5,&local_41c,0x400);
      tmp_pc2 = (char *)Info_ValueForKey(&local_41c,"cnport");
      tmp_u3 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_i4 = *(int *)(tmp_pu6 + 400);
      tmp_pc2 = inet_ntoa(param_2);
      tmp_i4 = Q_stricmp(tmp_pc2,tmp_i4 + 0x653);
      if ((tmp_i4 == 0) &&
         (((ushort)(GHIDRA_FIELD(param_1, 2, 2) >> 8 | GHIDRA_FIELD(param_1, 2, 2) << 8) == tmp_u3 ||
          ((param_5 == tmp_u3 && (0 < (int)param_5)))))) {
        return tmp_i5;
      }
    }
    tmp_i5 = tmp_i5 + 1;
    tmp_pu6 = tmp_pu6 + 0x600;
    if (tmp_i5 == 0x40) {
      return -1;
    }
  } while( true );
}

void nitrox_ClearSocketInfos(int param_1)
{
  memset(&NxACClients + param_1 * 0x1058,0,0x4160);
  return;
}

void nitrox_ReadSocketData(void)
{
  int *__s;
  ushort tmp_u1;
  ushort tmp_u2;
  in_addr __in;
  ssize_t tmp_s3;
  int *tmp_pi4;
  char *tmp_pc5;
  uint tmp_u6;
  size_t tmp_s7;
  long tmp_l8;
  uint32_t tmp_u9;
  void *pvVar10;
  int *tmp_pi11;
  int tmp_i12;
  FILE *pFVar13;
  uint32_t tmp_u14;
  uint32_t tmp_u15;
  int tmp_i16;
  uint tmp_u17;
  sockaddr *psVar18;
  sockaddr *psVar19;
  int tmp_i20;
  int *tmp_pi21;
  uint8_t *tmp_pu22;
  int *tmp_pi23;
  uint32_t *tmp_pu24;
  char *tmp_pc25;
  int *tmp_pi26;
  uint8_t tmp_u27;
  byte tmp_b28;
  uint8_t *local_1554;
  int local_1550;
  int local_1544;
  uint local_1540;
  char *local_153c;
  socklen_t local_150c;
  uint32_t local_1508 [63];
  char local_140c [4];
  uint32_t local_1408 [63];
  uint8_t local_130c [4];
  in_addr local_1308;
  char local_1304 [4];
  char local_1300 [1012];
  uint32_t local_f0c;
  uint32_t local_f08 [255];
  uint32_t local_b0c;
  uint8_t uStack_b09;
  uint32_t local_b08;
  uint32_t local_b04 [348];
  char local_594 [8];
  uint32_t local_58c [350];
  uint32_t uStack_14;
  
  tmp_b28 = 0;
  uStack_14 = 0x1ff570;
  local_b0c = 0;
  local_b08 = 0;
  tmp_pu24 = local_b04;
  for (tmp_i16 = 0x15c; tmp_i16 != 0; tmp_i16 = tmp_i16 + -1) {
    *tmp_pu24 = 0;
    tmp_pu24 = tmp_pu24 + 1;
  }
  tmp_s3 = recv(sock,&stack0xfffff4f4,0x578,0);
  if ((0 < tmp_s3) && (tmp_i16 = Q_stricmpn(&stack0xfffff4f4,"ps",2), tmp_i16 == 0)) {
    nitrox_PlayerStatsReceivedFromMaster(&uStack_b09);
  }
  tmp_pu24 = &stack0xfffff4f4;
  for (tmp_i16 = 0x15e; tmp_i16 != 0; tmp_i16 = tmp_i16 + -1) {
    *tmp_pu24 = 0;
    tmp_pu24 = tmp_pu24 + (uint)tmp_b28 * -2 + 1;
  }
  tmp_pi4 = __errno_location();
  while( true ) {
    local_594[0] = '\0';
    local_594[1] = '\0';
    local_594[2] = '\0';
    local_594[3] = '\0';
    local_140c[0] = '\x01';
    local_140c[1] = '\0';
    local_140c[2] = '\0';
    local_140c[3] = '\0';
    local_594[4] = '\0';
    local_594[5] = '\0';
    local_594[6] = '\0';
    local_594[7] = '\0';
    tmp_pu24 = local_58c;
    for (tmp_i16 = 0x15c; tmp_i16 != 0; tmp_i16 = tmp_i16 + -1) {
      *tmp_pu24 = 0;
      tmp_pu24 = tmp_pu24 + (uint)tmp_b28 * -2 + 1;
    }
    local_150c = 0x10;
    local_1550 = accept(NxAC_svSocket,(sockaddr *)local_130c,&local_150c);
    if (((local_1550 == -1) && (*tmp_pi4 == 0xb)) ||
       (tmp_i16 = ioctl(local_1550,0x5421,local_140c), tmp_i16 == -1)) break;
    tmp_i20 = -1;
    tmp_pc5 = local_594;
    for (tmp_i16 = 0x15e; tmp_i16 != 0; tmp_i16 = tmp_i16 + -1) {
      tmp_pc5[0] = '\0';
      tmp_pc5[1] = '\0';
      tmp_pc5[2] = '\0';
      tmp_pc5[3] = '\0';
      tmp_pc5 = tmp_pc5 + (uint)tmp_b28 * -8 + 4;
    }
    local_1540 = 0;
LAB_001ff6f0:
    tmp_s3 = recvfrom(local_1550,local_594,0x578,0,(sockaddr *)local_130c,&local_150c);
    tmp_u27 = tmp_s3 == 0;
    if (0 < tmp_s3) {
      tmp_pc5 = strtok(local_594," ");
      tmp_i16 = 2;
      tmp_pc25 = "hb";
      do {
        if (tmp_i16 == 0) break;
        tmp_i16 = tmp_i16 + -1;
        tmp_u27 = *tmp_pc5 == *tmp_pc25;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b28 * -2 + 1;
        tmp_pc25 = tmp_pc25 + (uint)tmp_b28 * -2 + 1;
      } while ((bool)tmp_u27);
      if ((bool)tmp_u27) goto LAB_001ff780;
      if (tmp_i20 == -1) goto LAB_001ff760;
      goto LAB_001ff6f0;
    }
    if ((tmp_i20 == -1) || (local_1540 == 0xffffffff)) {
      close(local_1550);
    }
    else {
      tmp_i16 = tmp_i20 * 0x4160;
      (&NxACClients)[tmp_i20 * 0x1058] = local_1550;
      *(uint *)(tmp_i16 + 0x2e5e604) = local_1540;
      *(uint *)(tmp_i16 + 0x2e5e608) =
           (uint)(ushort)((ushort)GHIDRA_FIELD(local_130c, 2, 2) >> 8 | GHIDRA_FIELD(local_130c, 2, 2) << 8);
      *(uint8_t (*) [4])(&g_unk_02e5e60c + tmp_i16) = local_130c;
      *(in_addr_t *)(tmp_i16 + 0x2e5e610) = local_1308.s_addr;
      *(char (*) [4])(tmp_i16 + 0x2e5e614) = local_1304;
      *(uint32_t *)(tmp_i16 + 0x2e5e618) = GHIDRA_FIELD(local_1300, 0, 4);
      *(uint32_t *)(&g_unk_02e5e61c + tmp_i16) = 0x10;
      (&g_unk_02e5e620)[tmp_i20 * 0x1058] = 1;
      tmp_pc5 = local_594;
      for (tmp_i16 = 0x15e; tmp_i16 != 0; tmp_i16 = tmp_i16 + -1) {
        tmp_pc5[0] = '\0';
        tmp_pc5[1] = '\0';
        tmp_pc5[2] = '\0';
        tmp_pc5[3] = '\0';
        tmp_pc5 = tmp_pc5 + (uint)tmp_b28 * -8 + 4;
      }
    }
  }
  local_1554 = g_entities;
  tmp_pi21 = (int *)&g_unk_02e62624;
  local_1544 = 0;
  do {
    if (tmp_pi21[-0x1001] != 0) {
      __s = tmp_pi21 + -0x1000;
      memset(__s,0,0x4000);
      tmp_u6 = recvfrom(tmp_pi21[-0x1009],__s,0x4000,0,(sockaddr *)(tmp_pi21 + -0x1006),
                       (socklen_t *)(tmp_pi21 + -0x1002));
      if ((int)tmp_u6 < 1) {
        if ((*tmp_pi4 != 0xb) && ((tmp_u6 == 0 || (tmp_u6 == 0xffffffff)))) {
          close(tmp_pi21[-0x1009]);
          memset(tmp_pi21 + -0x1009,0,0x4160);
        }
      }
      else {
        if (*(int *)(local_1554 + 400) == 0) goto LAB_001ffabf;
        tmp_i16 = Q_strncmp(__s,&g_unk_0026dc8e,2);
        if (tmp_i16 == 0) {
          tmp_pi21[-0x1001] = 1;
LAB_001ffaa4:
          memset(__s,0,0x4000);
        }
        else {
          tmp_i16 = Q_strncmp(__s,&g_unk_0026dc91,2);
          if (tmp_i16 == 0) {
            if (0 < tmp_pi21[2]) {
              tmp_u6 = 0;
              do {
                *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
                *(uint32_t *)((int)tmp_pi21 + tmp_u6 + 4) = 0;
                tmp_u6 = tmp_u6 + 8;
              } while (tmp_u6 < 0x138);
              *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
              *(uint8_t *)(tmp_pi21 + 5) = 0;
              *(uint8_t *)((int)tmp_pi21 + 0x39) = 0;
              if ((void *)*tmp_pi21 != (void *)0x0) {
                free((void *)*tmp_pi21);
              }
              *tmp_pi21 = 0;
              *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb44) = 0;
              *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb40) = 0;
              *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb3c) = 0;
            }
            goto LAB_001ffaa4;
          }
          tmp_i16 = Q_strncmp(__s,&g_unk_0026dc94,3);
          if (tmp_i16 == 0) {
            if (g_unk_02b9a334 != 0) {
              tmp_u6 = 0;
              do {
                *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
                *(uint32_t *)((int)tmp_pi21 + tmp_u6 + 4) = 0;
                tmp_u6 = tmp_u6 + 8;
              } while (tmp_u6 < 0x138);
              *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
              *(uint8_t *)(tmp_pi21 + 5) = 0;
              *(uint8_t *)((int)tmp_pi21 + 0x39) = 0;
              if ((void *)*tmp_pi21 != (void *)0x0) {
                free((void *)*tmp_pi21);
              }
              tmp_pi11 = tmp_pi21 + -0xfff;
              *tmp_pi21 = 0;
              tmp_s7 = strlen((char *)tmp_pi11);
              if (0x20 < tmp_s7) {
                tmp_pc5 = (char *)Info_ValueForKey(tmp_pi11,&g_unk_002609cd);
                tmp_l8 = strtol(tmp_pc5,(char **)0x0,10);
                *(uint8_t *)((int)tmp_pi21 + 0x39) = 0;
                tmp_pi21[3] = tmp_l8;
                tmp_u9 = Info_ValueForKey(tmp_pi11,&g_unk_0026dc98);
                Q_strncpyz(tmp_pi21 + 5,tmp_u9,0x21);
                tmp_u9 = Info_ValueForKey(tmp_pi11,&g_unk_00261798);
                Q_strncpyz((int)tmp_pi21 + 0x35,tmp_u9,4);
                trap_SendServerCommand
                          (((int)(local_1554 + -0x93e4a0) >> 9) * -0x55555555,&g_unk_0026dc9c);
              }
              goto LAB_001ffaa4;
            }
          }
          else if (g_unk_02b9a334 == 0) {
            tmp_u6 = 0;
            do {
              *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
              *(uint32_t *)((int)tmp_pi21 + tmp_u6 + 4) = 0;
              tmp_u6 = tmp_u6 + 8;
            } while (tmp_u6 < 0x138);
            *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
            *(uint8_t *)(tmp_pi21 + 5) = 0;
            *(uint8_t *)((int)tmp_pi21 + 0x39) = 0;
            if ((void *)*tmp_pi21 != (void *)0x0) {
              free((void *)*tmp_pi21);
            }
            *tmp_pi21 = 0;
          }
          else {
            if (tmp_pi21[3] == 0) {
              tmp_i16 = local_1544 * 0x4160;
              tmp_u6 = 0;
              do {
                *(uint32_t *)(&g_unk_02e62624 + tmp_u6 + tmp_i16) = 0;
                *(uint32_t *)(tmp_i16 + 0x2e62628 + tmp_u6) = 0;
                tmp_u6 = tmp_u6 + 8;
              } while (tmp_u6 < 0x138);
              *(uint32_t *)(&g_unk_02e62624 + tmp_u6 + tmp_i16) = 0;
              *(uint8_t *)(&g_unk_02e62638 + local_1544 * 0x20b0) = 0;
              (&g_unk_02e6265d)[local_1544 * 0x4160] = 0;
              if (*(void **)(&g_unk_02e62624 + local_1544 * 0x4160) != (void *)0x0) {
                free(*(void **)(&g_unk_02e62624 + local_1544 * 0x4160));
              }
              *(uint32_t *)(&g_unk_02e62624 + local_1544 * 0x4160) = 0;
              memset(__s,0,0x4000);
              return;
            }
            if (tmp_pi21[2] == 0) {
              NxAC_Log(local_1554,1,0,"[SCREENSHOT] Transfering... (%.2fKb)",
                       (double)((float)tmp_pi21[3] / 1000.0));
            }
            if (*(int *)(*(int *)(local_1554 + 400) + 0xb40) == 1) {
              *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb3c) = 2;
            }
            pvVar10 = realloc((void *)*tmp_pi21,tmp_u6 + 1 + tmp_pi21[1]);
            *tmp_pi21 = (int)pvVar10;
            if (pvVar10 != (void *)0x0) {
              tmp_pi11 = (int *)((int)pvVar10 + tmp_pi21[1]);
              tmp_u17 = tmp_u6;
              tmp_pi23 = __s;
              if (7 < tmp_u6) {
                if (((uint)tmp_pi11 & 1) != 0) {
                  *(char *)tmp_pi11 = (char)*__s;
                  tmp_pi11 = (int *)((int)tmp_pi11 + 1);
                  tmp_pi23 = (int *)((int)tmp_pi21 + -0x3fff);
                  tmp_u17 = tmp_u6 - 1;
                }
                tmp_pi26 = tmp_pi11;
                if (((uint)tmp_pi11 & 2) != 0) {
                  tmp_i16 = *tmp_pi23;
                  tmp_pi26 = (int *)((int)tmp_pi11 + 2);
                  tmp_pi23 = (int *)((int)tmp_pi23 + 2);
                  tmp_u17 = tmp_u17 - 2;
                  *(short *)tmp_pi11 = (short)tmp_i16;
                }
                tmp_pi11 = tmp_pi26;
                if (((uint)tmp_pi26 & 4) != 0) {
                  tmp_i16 = *tmp_pi23;
                  tmp_pi11 = tmp_pi26 + 1;
                  tmp_pi23 = tmp_pi23 + 1;
                  tmp_u17 = tmp_u17 - 4;
                  *tmp_pi26 = tmp_i16;
                }
              }
              for (; tmp_u17 != 0; tmp_u17 = tmp_u17 - 1) {
                *(char *)tmp_pi11 = (char)*tmp_pi23;
                tmp_pi23 = (int *)((int)tmp_pi23 + (uint)tmp_b28 * -2 + 1);
                tmp_pi11 = (int *)((int)tmp_pi11 + (uint)tmp_b28 * -2 + 1);
              }
              tmp_i16 = tmp_pi21[1];
              tmp_pi21[1] = tmp_i16 + tmp_u6;
              *(uint8_t *)(*tmp_pi21 + tmp_i16 + tmp_u6) = 0;
            }
            tmp_i16 = tmp_pi21[4];
            tmp_pi21[2] = tmp_pi21[2] + 1;
            tmp_pi21[4] = tmp_i16 + tmp_u6;
            if (tmp_pi21[3] <= (int)(tmp_i16 + tmp_u6)) {
              local_150c = 0;
              tmp_u6 = 0;
              do {
                tmp_u17 = tmp_u6;
                *(uint32_t *)((int)local_1508 + tmp_u17) = 0;
                *(uint32_t *)((int)local_1508 + tmp_u17 + 4) = 0;
                tmp_u6 = tmp_u17 + 8;
              } while (tmp_u17 + 8 < 0xf8);
              *(uint32_t *)((int)local_1508 + tmp_u17 + 8) = 0;
              GHIDRA_FIELD(local_130c, 0, 2) = 0;
              local_130c[2] = '\0';
              local_130c[3] = '\0';
              tmp_u6 = 0;
              do {
                tmp_u17 = tmp_u6;
                *(uint32_t *)((int)&local_1308.s_addr + tmp_u17) = 0;
                tmp_pc5 = local_1300 + (tmp_u17 - 4);
                tmp_pc5[0] = '\0';
                tmp_pc5[1] = '\0';
                tmp_pc5[2] = '\0';
                tmp_pc5[3] = '\0';
                tmp_u6 = tmp_u17 + 8;
              } while (tmp_u17 + 8 < 0x3f8);
              tmp_pc5 = local_1300 + tmp_u17;
              tmp_pc5[0] = '\0';
              tmp_pc5[1] = '\0';
              tmp_pc5[2] = '\0';
              tmp_pc5[3] = '\0';
              local_140c[0] = '\0';
              local_140c[1] = '\0';
              local_140c[2] = '\0';
              local_140c[3] = '\0';
              tmp_u6 = 0;
              do {
                tmp_u17 = tmp_u6;
                *(uint32_t *)((int)local_1408 + tmp_u17) = 0;
                *(uint32_t *)((int)local_1408 + tmp_u17 + 4) = 0;
                tmp_u6 = tmp_u17 + 8;
              } while (tmp_u17 + 8 < 0xf8);
              *(uint32_t *)((int)local_1408 + tmp_u17 + 8) = 0;
              tmp_pi11 = tmp_pi21 + 5;
              tmp_i12 = ((int)(local_1554 + -0x93e4a0) >> 9) * -0x55555555;
              trap_SendServerCommand(tmp_i12,&g_unk_0026dcec);
              tmp_i16 = (int)tmp_pi21 + 0x35;
              tmp_i20 = tmp_i16;
              Com_sprintf(local_140c,0x100,"%s%s%s.%s",&g_unk_02b9a338,&g_unk_0024ed91,tmp_pi11,tmp_i16);
              pFVar13 = fopen(local_140c,"a+b");
              if (pFVar13 == (FILE *)0x0) {
                NxAC_Log(0,1,0,"[SCREENSHOT] Can\'t write file (%s).",local_140c);
                tmp_u6 = 0;
                do {
                  *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
                  *(uint32_t *)((int)tmp_pi21 + tmp_u6 + 4) = 0;
                  tmp_u6 = tmp_u6 + 8;
                } while (tmp_u6 < 0x138);
                *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
                *(uint8_t *)(tmp_pi21 + 5) = 0;
                *(uint8_t *)((int)tmp_pi21 + 0x39) = 0;
                if ((void *)*tmp_pi21 != (void *)0x0) {
                  free((void *)*tmp_pi21);
                }
                *tmp_pi21 = 0;
                *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb44) = 0;
                *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb40) = 0;
              }
              else {
                fwrite((void *)*tmp_pi21,1,tmp_pi21[1],pFVar13);
                fclose(pFVar13);
                Com_sprintf(&local_150c,0x100,"%s%s%s.txt",&g_unk_02b9a338,&g_unk_0024ed91,tmp_pi11,
                            tmp_i20);
                pFVar13 = fopen((char *)&local_150c,"w");
                if (pFVar13 != (FILE *)0x0) {
                  local_f0c = 0;
                  tmp_u6 = 0;
                  do {
                    tmp_u17 = tmp_u6;
                    *(uint32_t *)((int)local_f08 + tmp_u17) = 0;
                    *(uint32_t *)((int)local_f08 + tmp_u17 + 4) = 0;
                    tmp_u6 = tmp_u17 + 8;
                  } while (tmp_u17 + 8 < 0x3f8);
                  *(uint32_t *)((int)local_f08 + tmp_u17 + 8) = 0;
                  trap_GetUserinfo(tmp_i12,local_594,0x400);
                  DecolorString(*(int *)(local_1554 + 400) + 0x5f8,&local_f0c);
                  if (*(int *)(*(int *)(local_1554 + 400) + 0xb40) < 1) {
                    local_153c = "\n";
                    tmp_pc5 = "Requested by admin";
                  }
                  else {
                    local_153c = (char *)va("Code 0x%04X\n",
                                            *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb44));
                    if (*(int *)(*(int *)(local_1554 + 400) + 0xb40) < 1) {
                      tmp_pc5 = "Requested by admin";
                    }
                    else {
                      tmp_u9 = NxAC_ViolationStringForIndex
                                        (*(int *)(*(int *)(local_1554 + 400) + 0xb40));
                      tmp_pc5 = (char *)va("NXAC_AUTOSCREENSHOT [%s]",tmp_u9);
                    }
                  }
                  tmp_u9 = Info_ValueForKey(local_594,"build");
                  tmp_u14 = Info_ValueForKey(local_594,"etVersion");
                  tmp_i20 = *(int *)(local_1554 + 400);
                  tmp_u15 = G_GetDateAndTime();
                  Com_sprintf((sockaddr *)local_130c,0x400,
                              "Date: %s\nFile: %s.%s\nPlayer: %s (%s)\nIP: %s\nNGUID: %s\nMAC: %s\nClient: %s\nBuild: %s\nReason %s\n%s"
                              ,tmp_u15,tmp_pi11,tmp_i16,&local_f0c,tmp_i20 + 0x5f8,tmp_i20 + 0x653,
                              tmp_i20 + 0x61c,tmp_i20 + 0xaf4,tmp_u14,tmp_u9,tmp_pc5,local_153c);
                  psVar19 = (sockaddr *)local_130c;
                  do {
                    psVar18 = psVar19;
                    tmp_u17 = *(uint *)psVar18 + 0xfefefeff & ~*(uint *)psVar18;
                    tmp_u6 = tmp_u17 & 0x80808080;
                    psVar19 = (sockaddr *)(psVar18->sa_data + 2);
                  } while (tmp_u6 == 0);
                  if ((tmp_u17 & 0x8080) == 0) {
                    psVar19 = (sockaddr *)(psVar18->sa_data + 4);
                    tmp_u6 = tmp_u6 >> 0x10;
                  }
                  fwrite((sockaddr *)local_130c,1,
                         (size_t)((int)psVar19 +
                                 ((-3 - (uint)CARRY1((byte)tmp_u6,(byte)tmp_u6)) - (int)local_130c)),
                         pFVar13);
                  fclose(pFVar13);
                  NxAC_Log(local_1554,1,0,"[SCREENSHOT] Saved (%s.%s)",tmp_pi11);
                  if (GHIDRA_FIELD(n_NxAC, 12, 4) == 2) {
                    tmp_i16 = *(int *)(local_1554 + 400);
                    if (0 < *(int *)(tmp_i16 + 0xb40)) {
                      *(uint32_t *)(tmp_i16 + 0xf44) = 0;
                      *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb44) = 0;
                      *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb40) = 0;
                      *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb3c) = 0;
                      NxAC_BanClient(local_1554);
                      goto LAB_00200307;
                    }
                  }
                  else {
LAB_00200307:
                    tmp_i16 = *(int *)(local_1554 + 400);
                  }
                  *(uint32_t *)(tmp_i16 + 0xb44) = 0;
                  *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb40) = 0;
                  *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb3c) = 0;
                  tmp_u6 = 0;
                  do {
                    *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
                    *(uint32_t *)((int)tmp_pi21 + tmp_u6 + 4) = 0;
                    tmp_u6 = tmp_u6 + 8;
                  } while (tmp_u6 < 0x138);
                  *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
                  *(uint8_t *)(tmp_pi21 + 5) = 0;
                  *(uint8_t *)((int)tmp_pi21 + 0x39) = 0;
                  if ((void *)*tmp_pi21 != (void *)0x0) {
                    free((void *)*tmp_pi21);
                  }
                  *tmp_pi21 = 0;
                  goto LAB_001ffaa4;
                }
                NxAC_Log(0,1,0,"[SCREENSHOT] Can\'t write info file (%s).",local_140c);
                tmp_u6 = 0;
                do {
                  *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
                  *(uint32_t *)((int)tmp_pi21 + tmp_u6 + 4) = 0;
                  tmp_u6 = tmp_u6 + 8;
                } while (tmp_u6 < 0x138);
                *(uint32_t *)((int)tmp_pi21 + tmp_u6) = 0;
                *(uint8_t *)(tmp_pi21 + 5) = 0;
                *(uint8_t *)((int)tmp_pi21 + 0x39) = 0;
                if ((void *)*tmp_pi21 != (void *)0x0) {
                  free((void *)*tmp_pi21);
                }
                *tmp_pi21 = 0;
                *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb44) = 0;
                *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb40) = 0;
              }
              *(uint32_t *)(*(int *)(local_1554 + 400) + 0xb3c) = 0;
            }
          }
        }
LAB_001ffabf:
        memset(__s,0,0x4000);
      }
    }
    tmp_pi21 = tmp_pi21 + 0x1058;
    local_1544 = local_1544 + 1;
    local_1554 = local_1554 + 0x600;
    if (tmp_pi21 == (int *)0x2f67e24) {
      return;
    }
  } while( true );
LAB_001ff780:
  tmp_pc5 = strtok((char *)0x0,"");
  tmp_i20 = 0;
  local_1540 = strtol(tmp_pc5,(char **)0x0,10);
  __in.s_addr = local_1308.s_addr;
  tmp_pu22 = g_entities;
  tmp_u1 = (ushort)GHIDRA_FIELD(local_130c, 2, 2) >> 8;
  tmp_u2 = GHIDRA_FIELD(local_130c, 2, 2) << 8;
  do {
    if (*(int *)(tmp_pu22 + 0x194) != 0) {
      local_f0c = 0;
      tmp_u6 = 0;
      do {
        tmp_u17 = tmp_u6;
        *(uint32_t *)((int)local_f08 + tmp_u17) = 0;
        *(uint32_t *)((int)local_f08 + tmp_u17 + 4) = 0;
        tmp_u6 = tmp_u17 + 8;
      } while (tmp_u17 + 8 < 0x3f8);
      *(uint32_t *)((int)local_f08 + tmp_u17 + 8) = 0;
      trap_GetUserinfo(tmp_i20,&local_f0c,0x400);
      tmp_pc5 = (char *)Info_ValueForKey(&local_f0c,"cnport");
      tmp_u6 = strtol(tmp_pc5,(char **)0x0,10);
      tmp_i16 = *(int *)(tmp_pu22 + 400);
      tmp_pc5 = inet_ntoa(__in);
      tmp_i16 = Q_stricmp(tmp_pc5,tmp_i16 + 0x653);
      if ((tmp_i16 == 0) &&
         ((tmp_u6 == (tmp_u1 | tmp_u2) || ((local_1540 == tmp_u6 && (0 < (int)local_1540))))))
      goto LAB_001ff6f0;
    }
    tmp_i20 = tmp_i20 + 1;
    tmp_pu22 = tmp_pu22 + 0x600;
  } while (tmp_i20 != 0x40);
LAB_001ff760:
  tmp_i20 = -1;
  close(local_1550);
  local_1550 = 0;
  goto LAB_001ff6f0;
}

void nitrox_CheckGlobalAwards(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int local_30;
  int local_2c;
  uint local_28;
  
  if ((((param_1 != 0) && (g_unk_02b99228 != 0)) &&
      (local_30 = *(int *)(param_1 + 400), local_30 != 0)) &&
     ((*(byte *)(param_1 + 0x128) & 8) == 0)) {
    if (((param_3 != 0) && (param_2 != -1)) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
      (&g_unk_00abe8ac)[(int)(&g_unk_00836a60 + (param_1 + -0x93e4a0 >> 9) * -0x55555550 + param_2)] =
           (&g_unk_00abe8ac)
           [(int)(&g_unk_00836a60 + (param_1 + -0x93e4a0 >> 9) * -0x55555550 + param_2)] + 1;
      local_30 = *(int *)(param_1 + 400);
    }
    tmp_i1 = totalGlobalAwards;
    if (totalGlobalAwards < 1) {
      local_28 = 0;
    }
    else {
      tmp_pi3 = &globalAwards;
      local_2c = 0;
      local_28 = 0;
      do {
        tmp_i5 = *tmp_pi3;
        tmp_i2 = 0;
        do {
          while ((tmp_i5 == tmp_i2 &&
                 (tmp_pi3[1] <=
                  (&g_unk_02b9922c)[(param_1 + -0x93e4a0 >> 9) * -0x55555550 + tmp_i5] +
                  *(int *)(local_30 + 0xb48 + tmp_i5 * 4)))) {
            tmp_i2 = tmp_i2 + 1;
            local_28 = local_28 | tmp_pi3[2];
            if (tmp_i2 == 0x10) goto LAB_002008b0;
          }
          tmp_i2 = tmp_i2 + 1;
        } while (tmp_i2 != 0x10);
LAB_002008b0:
        local_2c = local_2c + 1;
        tmp_pi3 = tmp_pi3 + 5;
      } while (local_2c != totalGlobalAwards);
    }
    *(uint *)(local_30 + 0xb88) = local_28;
    if ((param_2 != -1) && (*(int *)(*(int *)(param_1 + 400) + 0xb8c) != 0)) {
      tmp_i5 = param_1 + -0x93e4a0 >> 9;
      tmp_i2 = (&g_unk_00abe8ac)[(int)(&g_unk_00836a60 + tmp_i5 * -0x55555550 + param_2)] +
              *(int *)(*(int *)(param_1 + 400) + 0xb48 + param_2 * 4);
      if ((0 < tmp_i2) && (0 < tmp_i1)) {
        tmp_pi3 = &globalAwards;
        tmp_i6 = 0;
        do {
          if ((*tmp_pi3 == param_2) && (tmp_pi3[1] == tmp_i2)) {
            tmp_u4 = va("popaw %i %i",tmp_i5 * -0x55555555,tmp_i6);
            trap_SendServerCommand(0xffffffff,tmp_u4);
            return;
          }
          tmp_i6 = tmp_i6 + 1;
          tmp_pi3 = tmp_pi3 + 5;
        } while (tmp_i6 != tmp_i1);
      }
    }
  }
  return;
}

void nitrox_NxAC_ReportCvarViolationToMaster(int param_1,int param_2,uint32_t param_3)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint tmp_u4;
  uint tmp_u5;
  char *tmp_pc6;
  uint *tmp_pu7;
  uint *tmp_pu8;
  char *tmp_pc9;
  uint32_t local_422;
  uint16_t local_41e;
  uint local_41c [259];
  
  tmp_u5 = 0;
  do {
    tmp_u4 = tmp_u5;
    *(uint32_t *)((int)local_41c + tmp_u4 + 4) = 0;
    *(uint32_t *)((int)local_41c + tmp_u4 + 8) = 0;
    tmp_u5 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0x3f8);
  *(uint32_t *)((int)local_41c + tmp_u4 + 0xc) = 0;
  local_422 = 0;
  local_41e = 0;
  if (((g_unk_02b99228 != 0) && (local_41c[0] = 0xb0, param_1 != 0)) && (*(int *)(param_1 + 400) != 0)
     ) {
    trap_Cvar_VariableStringBuffer("net_port",&local_422,6);
    tmp_i1 = (&CvarChecks)[param_2];
    tmp_pc6 = (char *)(tmp_i1 + 100);
    if (*(char *)(tmp_i1 + 100) == '\0') {
      tmp_pc6 = "NULL";
    }
    tmp_pc9 = (char *)(tmp_i1 + 0x44);
    if (*(char *)(tmp_i1 + 0x44) == '\0') {
      tmp_pc9 = "NULL";
    }
    tmp_i2 = *(int *)(param_1 + 400);
    tmp_u3 = va("cv \\%s\\%s\\%s\\%s\\%s\\%s\\%s\\%s\\%s\\%s\\\n",&local_422,tmp_i2 + 0x61c,
               tmp_i2 + 0x5f8,tmp_i2 + 0x653,tmp_i2 + 0xaf4,tmp_i1,
               *(uint32_t *)(NxAC_CvarRulesStr + *(int *)(tmp_i1 + 0x40) * 4),tmp_pc9,tmp_pc6,param_3
              );
    Q_strcat(local_41c,0x400,tmp_u3);
    tmp_pu8 = local_41c;
    do {
      tmp_pu7 = tmp_pu8;
      tmp_u4 = *tmp_pu7 + 0xfefefeff & ~*tmp_pu7;
      tmp_u5 = tmp_u4 & 0x80808080;
      tmp_pu8 = tmp_pu7 + 1;
    } while (tmp_u5 == 0);
    if ((tmp_u4 & 0x8080) == 0) {
      tmp_pu8 = (uint *)((int)tmp_pu7 + 6);
      tmp_u5 = tmp_u5 >> 0x10;
    }
    sendto(sock,local_41c,
           (int)tmp_pu8 + (-(int)local_41c - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5)) + -2,0,
           (sockaddr *)&cl_sin,0x10);
  }
  return;
}

