/* Omni-bot interface — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_omnibot.h"

uint IsBot(gentity_s *param_1)
{
  return *(uint *)(param_1 + 0x128) >> 3 & 0xffffff01;
}

uint8_t * INDEXENT(int param_1)
{
  uint8_t *tmp_pu1;
  
  if (0x3ff < (uint)param_1) {
    return (uint8_t *)0x0;
  }
  if (param_1 != 0x3fe) {
    tmp_pu1 = g_entities + param_1 * 0x600;
    if (*(int *)(g_entities + param_1 * 0x600 + 0x194) == 0) {
      tmp_pu1 = (uint8_t *)0x0;
    }
    return tmp_pu1;
  }
  return (uint8_t *)0xabd8a0;
}

int ENTINDEX(gentity_s *param_1)
{
  return ((int)(param_1 + -0x93e4a0) >> 9) * -0x55555555;
}

uint8_t * EntityFromHandle(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = (int)(short)param_1;
  if (((int)(short)(&m_EntityHandles)[tmp_i1 * 2] == param_1 >> 0x10) &&
     (*(int *)(g_entities + tmp_i1 * 0x600 + 0x194) != 0)) {
    return g_entities + tmp_i1 * 0x600;
  }
  if (tmp_i1 == 0x3fe) {
    return (uint8_t *)0xabd8a0;
  }
  return (uint8_t *)0x0;
}

void HandleFromEntity(gentity_s *param_1)
{
  uint16_t tmp_u1;
  int tmp_i2;
  int in_stack_00000008;
  
  if (in_stack_00000008 != 0) {
    tmp_i2 = in_stack_00000008 + -0x93e4a0 >> 9;
    tmp_u1 = (&m_EntityHandles)[tmp_i2 * -0x2aaaaaaa];
    *(short *)param_1 = (short)tmp_i2 * -0x5555;
    *(uint16_t *)(param_1 + 2) = tmp_u1;
    return;
  }
  *(uint16_t *)(param_1 + 2) = 0;
  *(uint16_t *)param_1 = 0xffff;
  return;
}

// Bot_Util_AddGoal(char const*, gentity_s*, int, char const*, char const*, obUserData_t*) [clone
// .part_23]

void Bot_Util_AddGoal(char *param_1,gentity_s *param_2,int param_3,char *param_4,char *param_5,
                obUserData_t *param_6)

{
  uint32_t local_e20;
  KeyVals local_e1c [3596];
  
  KeyVals::KeyVals(local_e1c);
  KeyVals::Reset(local_e1c);
  KeyVals::SetString(local_e1c,"Type",param_1);
  HandleFromEntity((gentity_s *)&local_e20);
  KeyVals::SetEntity(local_e1c,"Entity",local_e20);
  KeyVals::SetInt(local_e1c,"Team",(int)param_2);
  KeyVals::SetString(local_e1c,"TagName",(char *)param_3);
  KeyVals::SetInt(local_e1c,"InterfaceGoal",1);
  if ((param_4 != (char *)0x0) && (param_5 != (char *)0x0)) {
    KeyVals::Set(local_e1c,param_4,(obUserData_t *)param_5);
  }
  (*g_unk_00881200)(local_e1c);
  return;
}

void SendDeferredGoals(void)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  
  if (g_GoalSubmitReady != '\0') {
    if (0 < g_NumDeferredGoals) {
      tmp_i2 = 0;
      tmp_pu1 = g_DeferredGoals;
      do {
        tmp_i2 = tmp_i2 + 1;
        (*g_unk_00881200)(tmp_pu1);
        tmp_pu1 = tmp_pu1 + 0xe00;
      } while (tmp_i2 < g_NumDeferredGoals);
    }
    g_NumDeferredGoals = 0;
  }
  return;
}

void GetEntityCenter(int param_1,float *param_2)
{
  *param_2 = (*(float *)(param_1 + 0x140) + *(float *)(param_1 + 0x134)) * 0.5 +
             *(float *)(param_1 + 0x168);
  param_2[1] = (*(float *)(param_1 + 0x144) + *(float *)(param_1 + 0x138)) * 0.5 +
               *(float *)(param_1 + 0x16c);
  param_2[2] = (*(float *)(param_1 + 0x148) + *(float *)(param_1 + 0x13c)) * 0.5 +
               *(float *)(param_1 + 0x170);
  return;
}

void UpdateMG42(gentity_s *param_1)
{
  int tmp_i1;
  float *pfVar2;
  float local_18;
  float local_14;
  
  GetEntityCenter(param_1,&local_18);
  if (0 < numofmg42s) {
    pfVar2 = (float *)&g_unk_0083d3e4;
    tmp_i1 = numofmg42s * 0x25;
    do {
      if ((local_18 == *pfVar2) && (pfVar2[1] == local_14)) {
        pfVar2[-1] = (float)param_1;
      }
      pfVar2 = pfVar2 + 0x25;
    } while (pfVar2 != (float *)(&g_unk_0083d3e4 + tmp_i1));
  }
  return;
}

void CheckForMG42(gentity_s *param_1,char *param_2)
{
  int tmp_i1;
  char *__dest;
  int tmp_i2;
  float local_28;
  float local_24;
  uint32_t uStack_14;
  
  uStack_14 = 0x22e919;
  if ((numofmg42s != 0) && (GetEntityCenter(param_1,&local_28), tmp_i1 = numofmg42s, 0 < numofmg42s))
  {
    tmp_i2 = 0;
    __dest = &g_unk_0083d430;
    do {
      if ((ABS(*(float *)(__dest + -0x4c) - local_28) < 100.0) &&
         (ABS(*(float *)(__dest + -0x48) - local_24) < 100.0)) {
        __dest[0x40] = '\x01';
        strcpy(__dest,param_2);
      }
      tmp_i2 = tmp_i2 + 1;
      __dest = __dest + 0x94;
    } while (tmp_i2 != tmp_i1);
  }
  return;
}

uint32_t Bot_TeamGameToBot(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 0;
  if (param_1 - 1U < 3) {
    tmp_u1 = *(uint32_t *)(CSWTCH_594 + (param_1 - 1U) * 4);
  }
  return tmp_u1;
}

uint32_t Bot_PlayerClassGameToBot(uint param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 0;
  if (param_1 < 5) {
    tmp_u1 = *(uint32_t *)(CSWTCH_598 + param_1 * 4);
  }
  return tmp_u1;
}

int Bot_WeaponGameToBot(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = 0;
  if (param_1 - 1U < 0x33) {
    tmp_i1 = (int)(char)(&UNK_00270aff)[param_1];
  }
  return tmp_i1;
}

bool Simple_EmplacedGunIsRepairable(gentity_s *param_1)
{
  if (*(int *)(param_1 + 0x5c0) != 0x1908e) {
    return false;
  }
  return *(int *)(param_1 + 0xb0) != 0;
}

int Bot_EntInvisibleBySmokeBomb(float *param_1,float *param_2)
{
  int tmp_i1;
  float tmp_f2;
  int *tmp_pi3;
  long double tmp_l4;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  
  tmp_l4 = (long double)DistanceSquared(param_1,param_2);
  if ((long double)10000.0 <= tmp_l4) {
    tmp_pi3 = &g_SmokeGrenadeCache;
    do {
      tmp_i1 = *tmp_pi3;
      if ((tmp_i1 != 0) && (*(int *)(tmp_i1 + 0x10c) != 0x10)) {
        local_28 = *(uint32_t *)(tmp_i1 + 0x18);
        local_24 = *(uint32_t *)(tmp_i1 + 0x1c);
        local_20 = *(float *)(tmp_i1 + 0x20) + 32.0;
        tmp_f2 = ((float)(g_unk_00abe908 - *(int *)(tmp_i1 + 0x3a0)) / 10000.0) * 320.0;
        if (320.0 < tmp_f2) {
          tmp_f2 = 320.0;
        }
        tmp_l4 = (long double)DistanceFromLineSquared(&local_28,param_1,param_2);
        if (tmp_l4 < (long double)tmp_f2 * (long double)tmp_f2) {
          return tmp_i1;
        }
      }
      tmp_pi3 = tmp_pi3 + 1;
    } while (tmp_pi3 != &AirstrikeEntities);
  }
  return 0;
}

// Bot_Util_AddGoal(char const*, gentity_s*, int, char const*, char const*, obUserData_t*)

void Bot_Util_AddGoal(char *param_1,gentity_s *param_2,int param_3,char *param_4,char *param_5,
                     obUserData_t *param_6)

{
  char tmp_c1;
  
  tmp_c1 = IsOmnibotLoaded();
  if ((tmp_c1 != '\0') && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) {
    Bot_Util_AddGoal(param_1,(gentity_s *)param_3,(int)param_4,param_5,(char *)param_6,
                     (obUserData_t *)param_5);
    return;
  }
  return;
}

bool _TankIsMountable(gentity_s *param_1)
{
  bool tmp_b1;
  
  tmp_b1 = false;
  if (((byte)param_1[0x1a8] & 0x80) != 0) {
    if (g_unk_02aa29a4 != 0) {
      return false;
    }
    tmp_b1 = false;
    if ((g_OmniBotFlags[0xc] & 2) == 0) {
      tmp_b1 = 0 < *(int *)(param_1 + 0x2c8);
    }
  }
  return tmp_b1;
}

bool _EmplacedGunIsMountable(gentity_s *param_1)
{
  return (g_OmniBotFlags[0xc] & 4) == 0;
}

void Omnibot_Load_PrintMsg(char *param_1)
{
  G_Printf("Omni-bot: %s%s\n",&g_unk_00270b9f,param_1);
  return;
}

void Omnibot_Load_PrintErr(char *param_1)
{
  G_Printf("Omni-bot: %s%s\n",&g_unk_00248060,param_1);
  return;
}

uint obUtilBotContentsFromGameContents(int param_1)
{
  uint tmp_u1;
  
  tmp_u1 = param_1 & 1U;
  if ((param_1 & 0x20U) != 0) {
    tmp_u1 = param_1 & 1U | 2;
  }
  if ((param_1 & 0x10U) != 0) {
    tmp_u1 = tmp_u1 | 4;
  }
  if ((param_1 & 0x40U) != 0) {
    tmp_u1 = tmp_u1 | 8;
  }
  if ((param_1 & 0x40000U) != 0) {
    tmp_u1 = tmp_u1 | 0x100;
  }
  if ((param_1 & 0x4000U) != 0) {
    tmp_u1 = tmp_u1 | 0x10;
  }
  if ((param_1 & 0x40000000U) != 0) {
    tmp_u1 = tmp_u1 | 0x20;
  }
  if ((param_1 & 8U) != 0) {
    tmp_u1 = tmp_u1 | 0x40;
  }
  if ((param_1 & 0x10000U) != 0) {
    tmp_u1 = tmp_u1 | 0x400;
  }
  return tmp_u1;
}

uint obUtilBotSurfaceFromGameSurface(int param_1)
{
  uint tmp_u1;
  
  tmp_u1 = (uint)param_1 >> 1 & 1;
  if ((param_1 & 8U) != 0) {
    tmp_u1 = tmp_u1 | 2;
  }
  return tmp_u1;
}

void Bot_Interface_InitHandles(void)
{
  byte tmp_b1;
  int tmp_i2;
  
  tmp_i2 = 0;
  do {
    tmp_b1 = (&g_unk_00877902)[tmp_i2 * 4];
    (&m_EntityHandles)[tmp_i2 * 2] = 1;
    (&g_unk_00877902)[tmp_i2 * 4] = tmp_b1 & 0xfc;
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 0x400);
  return;
}

bool Bot_Interface_Init(void)
{
  char *tmp_pc1;
  int tmp_i2;
  
  if (GHIDRA_FIELD(g_OmniBotEnable, 12, 4) != 0) {
    g_GoalSubmitReady = 0;
    g_InterfaceFunctions = operator_new(4);
    *g_InterfaceFunctions = &g_ptr_AddBot_002b4248;
    tmp_pc1 = (char *)Omnibot_FixPath(g_OmniBotPath + 0x10);
    tmp_i2 = Omnibot_LoadLibrary(0x11,"omnibot_et",tmp_pc1);
    return tmp_i2 == 0;
  }
  G_Printf("%s%s\n",&g_unk_00270b9f,"Omni-bot is currently disabled with \"omnibot_enable 0\"");
  return true;
}

uint32_t Bot_Interface_Shutdown(void)
{
  char tmp_c1;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    (*g_unk_008811e8)();
  }
  Omnibot_FreeLibrary();
  return 1;
}

void Bot_Interface_ConsoleCommand(void)
{
  int *tmp_pi1;
  char tmp_c2;
  uint tmp_u3;
  int tmp_i4;
  int *tmp_pi5;
  int tmp_i6;
  int local_2030 [2056];
  int local_10;
  
  tmp_u3 = 0;
  local_10 = 0x22f51a;
  do {
    *(uint32_t *)((int)local_2030 + tmp_u3) = 0;
    *(uint32_t *)((int)local_2030 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0x20);
  trap_Argv(1,local_2030,0x20);
  tmp_c2 = IsOmnibotLoaded();
  if (tmp_c2 == '\0') {
    tmp_i4 = Q_stricmp(local_2030,"load");
    if (tmp_i4 != 0) {
      G_Printf("%s%s\n",&g_unk_00248060,"Omni-bot not loaded.");
      return;
    }
    Bot_Interface_InitHandles();
    Bot_Interface_Init();
  }
  else {
    tmp_i4 = Q_stricmp(local_2030,"unload");
    if (tmp_i4 == 0) {
      Bot_Interface_Shutdown();
      return;
    }
    tmp_i4 = Q_stricmp(local_2030,"reload");
    if (tmp_i4 != 0) {
      tmp_pi1 = local_2030 + 8;
      local_10 = 0;
      tmp_pi5 = tmp_pi1;
      do {
        *(uint8_t *)tmp_pi5 = 0;
        tmp_pi5 = tmp_pi5 + 0x20;
      } while (tmp_pi5 != &local_10);
      tmp_i4 = 0;
      while( true ) {
        tmp_i6 = trap_Argc();
        if (tmp_i6 <= tmp_i4) break;
        tmp_i6 = local_10 * 0x20;
        local_10 = local_10 + 1;
        trap_Argv(tmp_i4,tmp_pi1 + tmp_i6,0x80);
        tmp_i4 = tmp_i4 + 1;
      }
      (*g_unk_008811ec)(tmp_pi1);
      return;
    }
    Bot_Interface_Shutdown();
    Bot_Interface_InitHandles();
    Bot_Interface_Init();
  }
  return;
}

uint32_t Bot_Util_AllowPush(int param_1)
{
  if ((param_1 != 0x2a) && (param_1 != 0x2e)) {
    return 1;
  }
  return 0;
}

char * _GetEntityName(int param_1)
{
  uint16_t tmp_u1;
  char tmp_c2;
  char *tmp_pc3;
  uint tmp_u4;
  int tmp_i5;
  char *tmp_pc6;
  uint32_t *tmp_pu7;
  char tmp_c8;
  char *tmp_pc9;
  uint tmp_u10;
  char *tmp_pc11;
  char *tmp_pc12;
  bool tmp_b13;
  char local_33 [35];
  
  _GetEntityName::newentname = '\0';
  if (param_1 == 0) {
    tmp_pc3 = (char *)0x0;
  }
  else {
    if ((*(int *)(param_1 + 0x194) == 0) || (tmp_i5 = *(int *)(param_1 + 400), tmp_i5 == 0)) {
      tmp_pc3 = *(char **)(param_1 + 0x3a8);
      if ((tmp_pc3 != (char *)0x0) ||
         (((tmp_pc3 = *(char **)(param_1 + 0x3ac), tmp_pc3 != (char *)0x0 ||
           (tmp_pc3 = *(char **)(param_1 + 600), tmp_pc3 != (char *)0x0)) ||
          (tmp_pc3 = *(char **)(param_1 + 0x248), tmp_pc3 != (char *)0x0)))) {
        strcpy(&_GetEntityName::newentname,tmp_pc3);
      }
      tmp_u10 = 0x15;
      Q_CleanStr(&_GetEntityName::newentname);
      tmp_pc3 = local_33 + 2;
      tmp_b13 = ((uint)tmp_pc3 & 1) != 0;
      local_33[0] = '-';
      tmp_pu7 = (uint32_t *)&g_unk_00270858;
      local_33[1] = 0;
      tmp_pc9 = tmp_pc3;
      if (tmp_b13) {
        tmp_pc9 = local_33 + 3;
        tmp_pu7 = &g_unk_00270859;
        tmp_u10 = 0x14;
        local_33[2] = '[';
      }
      tmp_pc12 = tmp_pc9;
      if (((uint)tmp_pc9 & 2) != 0) {
        tmp_u1 = *(uint16_t *)tmp_pu7;
        tmp_pc12 = tmp_pc9 + 2;
        tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
        tmp_u10 = tmp_u10 - 2;
        *(uint16_t *)tmp_pc9 = tmp_u1;
      }
      tmp_u4 = 0;
      do {
        *(uint32_t *)(tmp_pc12 + tmp_u4) = *(uint32_t *)((int)tmp_pu7 + tmp_u4);
        tmp_u4 = tmp_u4 + 4;
      } while (tmp_u4 < (tmp_u10 & 0xfffffffc));
      tmp_i5 = 0;
      if ((tmp_u10 & 2) != 0) {
        *(uint16_t *)(tmp_pc12 + tmp_u4) = *(uint16_t *)((int)tmp_pu7 + tmp_u4);
        tmp_i5 = 2;
      }
      tmp_pc9 = &_GetEntityName::newentname;
      tmp_pc6 = &_GetEntityName::newentname;
      tmp_c8 = _GetEntityName::newentname;
      if (!tmp_b13) {
        (tmp_pc12 + tmp_u4)[tmp_i5] = *(char *)((int)((int)tmp_pu7 + tmp_u4) + tmp_i5);
      }
joined_r0x0022f7a5:
      if (tmp_c8 == '\0') {
        *tmp_pc9 = '\0';
        tmp_i5 = Q_stricmpn(&g_unk_00251d18,&_GetEntityName::newentname,4);
        tmp_pc3 = &_GetEntityName::newentname;
        if (tmp_i5 == 0) {
          tmp_pc3 = &g_unk_00880e84;
        }
        return tmp_pc3;
      }
      tmp_pc12 = tmp_pc3;
      tmp_c2 = local_33[2];
      if (tmp_c8 != '-') {
        tmp_pc11 = local_33;
        do {
          tmp_pc11 = tmp_pc11 + 1;
          if (*tmp_pc11 == '\0') goto joined_r0x0022f7e2;
        } while (tmp_c8 != *tmp_pc11);
      }
      *tmp_pc6 = '_';
      tmp_c8 = '_';
joined_r0x0022f7e2:
      do {
        if (tmp_c2 == '\0') goto LAB_0022f80a;
        if (tmp_c2 == tmp_c8) {
          tmp_c8 = tmp_pc6[1];
          tmp_pc6 = tmp_pc6 + 1;
          goto LAB_0022f80a;
        }
        tmp_pc12 = tmp_pc12 + 1;
        tmp_c2 = *tmp_pc12;
      } while( true );
    }
    if (*(char *)(tmp_i5 + 0x5f8) == '\0') {
      trap_GetUserinfo((param_1 + -0x93e4a0 >> 9) * -0x55555555,_GetEntityName::userinfo,0x400);
      tmp_pc3 = (char *)Info_ValueForKey(_GetEntityName::userinfo,"name");
      return tmp_pc3;
    }
    tmp_pc3 = (char *)(tmp_i5 + 0x5f8);
  }
  return tmp_pc3;
LAB_0022f80a:
  *tmp_pc9 = tmp_c8;
  tmp_pc12 = tmp_pc6 + 1;
  tmp_pc9 = tmp_pc9 + 1;
  tmp_pc6 = tmp_pc6 + 1;
  tmp_c8 = *tmp_pc12;
  goto joined_r0x0022f7a5;
}

void GetMG42s(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  char *__src;
  int tmp_i3;
  
  if (numofmg42s == 0) {
    if ((havemg42s != '\0') && (0 < MG42Entities)) {
      tmp_i3 = 0;
      do {
        tmp_u1 = (&g_unk_0087a9c4)[tmp_i3];
        __src = (char *)_GetEntityName(tmp_u1);
        tmp_i2 = numofmg42s;
        (&mg42s)[numofmg42s * 0x25] = tmp_u1;
        GetEntityCenter(tmp_u1,&g_unk_0083d3e4 + tmp_i2 * 0x25);
        tmp_i2 = numofmg42s;
        if (__src == (char *)0x0) {
          (&g_unk_0083d3f0)[numofmg42s * 0x94] = 0;
        }
        else {
          strcpy(&g_unk_0083d3f0 + numofmg42s * 0x94,__src);
        }
        tmp_i3 = tmp_i3 + 1;
        (&g_unk_0083d470)[tmp_i2 * 0x94] = 0;
        numofmg42s = tmp_i2 + 1;
      } while (tmp_i3 < MG42Entities);
      if (numofmg42s != 0) {
        return;
      }
    }
    havemg42s = '\0';
  }
  return;
}

void Bot_Util_CheckForGoalEntity(uint32_t param_1)
{
  char tmp_c1;
  gentity_s *pgVar2;
  uint tmp_u3;
  char *tmp_pc4;
  char local_10c [4];
  uint32_t auStack_108 [63];
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    pgVar2 = (gentity_s *)EntityFromHandle(param_1);
    if ((*(int *)(pgVar2 + 0x194) != 0) && (*(int *)(pgVar2 + 4) == 2)) {
      tmp_u3 = 0;
      do {
        *(uint32_t *)((int)auStack_108 + (tmp_u3 - 4)) = 0;
        *(uint32_t *)((int)auStack_108 + tmp_u3) = 0;
        tmp_u3 = tmp_u3 + 8;
      } while (tmp_u3 < 0x100);
      tmp_pc4 = (char *)_GetEntityName(pgVar2);
      if (*(int *)(pgVar2 + 0x5c0) == 0x3317f) {
        if (*(int *)(pgVar2 + 0x8c) != -1) {
          tmp_pc4 = (char *)_GetEntityName(g_entities + *(int *)(pgVar2 + 0x8c) * 0x600);
        }
        if (tmp_pc4 == (char *)0x0) {
          tmp_pc4 = "allies_flag";
        }
        Com_sprintf(local_10c,0x100,"%s_dropped",tmp_pc4);
        Bot_Util_AddGoal("flag",pgVar2,4,local_10c,(char *)0x0,(obUserData_t *)0x0);
        Bot_Util_AddGoal("flagreturn",pgVar2,2,local_10c,(char *)0x0,(obUserData_t *)0x0);
      }
      else if (*(int *)(pgVar2 + 0x5c0) == 0x36af1) {
        if (*(int *)(pgVar2 + 0x8c) != -1) {
          tmp_pc4 = (char *)_GetEntityName(g_entities + *(int *)(pgVar2 + 0x8c) * 0x600);
        }
        if (tmp_pc4 == (char *)0x0) {
          tmp_pc4 = "axis_flag";
        }
        Com_sprintf(local_10c,0x100,"%s_dropped",tmp_pc4);
        Bot_Util_AddGoal("flag",pgVar2,2,local_10c,(char *)0x0,(obUserData_t *)0x0);
        Bot_Util_AddGoal("flagreturn",pgVar2,4,local_10c,(char *)0x0,(obUserData_t *)0x0);
      }
    }
  }
  return;
}

uint32_t Bot_Util_CheckForSuicide(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  
  if ((((param_1 == 0) || (tmp_i1 = *(int *)(param_1 + 400), tmp_i1 == 0)) ||
      (*(int *)(tmp_i1 + 0xf24) != 1)) ||
     (((tmp_i3 = GHIDRA_FIELD(g_redlimbotime, 12, 4), tmp_i2 = g_unk_02a99a6c, *(int *)(tmp_i1 + 3000) != 1 &&
       (tmp_i3 = GHIDRA_FIELD(g_bluelimbotime, 12, 4), tmp_i2 = g_unk_02a99a68, *(int *)(tmp_i1 + 3000) != 2)) ||
      (1999 < tmp_i3 - ((g_unk_02a99b84 + tmp_i2) - g_unk_00abe918) % tmp_i3)))) {
    tmp_u4 = 0;
  }
  else {
    Cmd_Kill_f(param_1);
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xf24) = 0;
    tmp_u4 = 1;
  }
  return tmp_u4;
}

void Bot_Event_ClientConnected(uint32_t param_1,int param_2)
{
  char tmp_c1;
  uint32_t local_28;
  uint32_t *local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint local_18;
  uint32_t local_14;
  uint32_t local_10;
  uint32_t uStack_8;
  
  uStack_8 = 0x22fd16;
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    local_14 = 0xfffffffe;
    local_10 = 0xfffffffe;
    local_24 = &local_1c;
    local_20 = 0x10;
    local_1c = param_1;
    local_28 = 10;
    local_18 = (uint)(param_2 == 1);
    (*g_unk_008811fc)(&local_28);
  }
  return;
}

void Bot_Event_ClientDisConnected(uint32_t param_1)
{
  char tmp_c1;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t *local_14;
  uint32_t local_10;
  uint32_t uStack_8;
  
  uStack_8 = 0x22fd96;
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    local_18 = 0xb;
    local_14 = &local_1c;
    local_10 = 4;
    local_1c = param_1;
    (*g_unk_008811fc)(&local_18);
  }
  return;
}

void Bot_Event_ResetWeapons(int param_1)
{
  char tmp_c1;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  uint32_t uStack_8;
  
  uStack_8 = 0x22fdf6;
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      local_14 = 0;
      local_18 = 0x2e;
      local_10 = 0;
      (*g_unk_008811f8)(param_1,&local_18);
      return;
    }
  }
  return;
}

void Bot_Event_AddWeapon(int param_1,uint32_t param_2)
{
  char tmp_c1;
  int tmp_i2;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t *local_24;
  uint32_t local_20;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 == '\0') {
    return;
  }
  tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
  if (tmp_c1 == '\0') {
    return;
  }
  switch(param_2) {
  case 0x15:
    tmp_i2 = COM_BitCheck(*(int *)(g_entities + param_1 * 0x600 + 400) + 0x3d4,0x29);
    if (tmp_i2 != 0) {
      local_2c = 0x15;
      local_24 = &local_2c;
      local_20 = 4;
      local_28 = 0x2d;
      (*g_unk_008811f8)(param_1,&local_28);
      param_2 = 0x16;
      goto LAB_0022fef6;
    }
    break;
  case 0x16:
    local_2c = 0x15;
    goto LAB_0022ff31;
  case 0x1c:
    tmp_i2 = COM_BitCheck(*(int *)(g_entities + param_1 * 0x600 + 400) + 0x3d4,0x28);
    if (tmp_i2 != 0) {
      local_2c = 0x1c;
      local_24 = &local_2c;
      local_28 = 0x2d;
      local_20 = 4;
      (*g_unk_008811f8)(param_1,&local_28);
      param_2 = 0x1d;
      goto LAB_0022fef6;
    }
    break;
  case 0x1d:
    local_2c = 0x1c;
    goto LAB_0022ff31;
  case 0x20:
    tmp_i2 = COM_BitCheck(*(int *)(g_entities + param_1 * 0x600 + 400) + 0x3d4,0x27);
    if (tmp_i2 != 0) {
      local_28 = 0x2d;
      local_24 = &local_2c;
      local_2c = 0x20;
      local_20 = 4;
      (*g_unk_008811f8)(param_1,&local_28);
      param_2 = 0x21;
      goto LAB_0022fef6;
    }
    break;
  case 0x21:
    local_2c = 0x20;
LAB_0022ff31:
    local_24 = &local_2c;
    local_28 = 0x2d;
    local_20 = 4;
    (*g_unk_008811f8)(param_1,&local_28);
    goto LAB_0022fef6;
  }
LAB_0022fef6:
  local_24 = &local_2c;
  local_28 = 0x2c;
  local_2c = param_2;
  local_20 = 4;
  (*g_unk_008811f8)(param_1,&local_28);
  return;
}

void Bot_Event_RemoveWeapon(int param_1,uint32_t param_2)
{
  char tmp_c1;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t *local_14;
  uint32_t local_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    if (*(int *)(g_entities + param_1 * 0x600 + 400) != 0) {
      tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
      if ((tmp_c1 != '\0') && (*(int *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 4) != 3)) {
        local_18 = 0x2d;
        local_14 = &local_1c;
        local_10 = 4;
        local_1c = param_2;
        (*g_unk_008811f8)(param_1,&local_18);
      }
    }
  }
  return;
}

void Bot_Event_TakeDamage(int param_1)
{
  char tmp_c1;
  gentity_s local_1c [4];
  uint32_t local_18;
  gentity_s *local_14;
  uint32_t uStack_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      HandleFromEntity(local_1c);
      uStack_10 = 4;
      local_18 = 0x3d;
      local_14 = local_1c;
      (*g_unk_008811f8)(param_1,&local_18);
      return;
    }
  }
  return;
}

void Bot_Event_Death(int param_1,uint32_t param_2,char *param_3)
{
  char tmp_c1;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t *local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint8_t auStack_2c [36];
  
  tmp_c1 = IsOmnibotLoaded();
  if ((tmp_c1 != '\0') && (tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600)), tmp_c1 != '\0')
     ) {
    local_30 = 0xffff;
    HandleFromEntity((gentity_s *)&local_40);
    local_30 = local_40;
    if (param_3 == (char *)0x0) {
      param_3 = "<unknown>";
    }
    Q_strncpyz(auStack_2c,param_3,0x20);
    local_3c = 0x28;
    local_34 = 0x24;
    local_38 = &local_30;
    (*g_unk_008811f8)(param_1,&local_3c);
    return;
  }
  return;
}

void Bot_Event_Healed(int param_1)
{
  char tmp_c1;
  gentity_s local_1c [4];
  uint32_t local_18;
  gentity_s *local_14;
  uint32_t uStack_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      HandleFromEntity(local_1c);
      uStack_10 = 4;
      local_18 = 0x29;
      local_14 = local_1c;
      (*g_unk_008811f8)(param_1,&local_18);
      return;
    }
  }
  return;
}

void Bot_Event_RecievedAmmo(int param_1)
{
  char tmp_c1;
  gentity_s local_1c [4];
  uint32_t local_18;
  gentity_s *local_14;
  uint32_t uStack_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      HandleFromEntity(local_1c);
      uStack_10 = 4;
      local_18 = 0x55;
      local_14 = local_1c;
      (*g_unk_008811f8)(param_1,&local_18);
      return;
    }
  }
  return;
}

void Bot_Event_Revived(int param_1)
{
  char tmp_c1;
  gentity_s local_1c [4];
  uint32_t local_18;
  gentity_s *local_14;
  uint32_t uStack_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      HandleFromEntity(local_1c);
      uStack_10 = 4;
      local_18 = 0x2a;
      local_14 = local_1c;
      (*g_unk_008811f8)(param_1,&local_18);
      return;
    }
  }
  return;
}

void Bot_Event_KilledSomeone(int param_1,uint32_t param_2,char *param_3)
{
  char tmp_c1;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t *local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint8_t auStack_2c [36];
  
  tmp_c1 = IsOmnibotLoaded();
  if ((tmp_c1 != '\0') && (tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600)), tmp_c1 != '\0')
     ) {
    local_30 = 0xffff;
    HandleFromEntity((gentity_s *)&local_40);
    local_30 = local_40;
    if (param_3 == (char *)0x0) {
      param_3 = "<unknown>";
    }
    Q_strncpyz(auStack_2c,param_3,0x20);
    local_3c = 0x2b;
    local_34 = 0x24;
    local_38 = &local_30;
    (*g_unk_008811f8)(param_1,&local_3c);
    return;
  }
  return;
}

void Bot_Event_FireWeapon(int param_1,uint32_t param_2)
{
  char tmp_c1;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t *local_14;
  uint32_t uStack_10;
  uint32_t uStack_8;
  
  uStack_8 = 0x230656;
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      local_20 = 0;
      local_1c = 0;
      local_24 = param_2;
      HandleFromEntity((gentity_s *)&local_1c);
      local_18 = 0x17;
      local_14 = &local_24;
      uStack_10 = 0xc;
      (*g_unk_008811f8)(param_1,&local_18);
      return;
    }
  }
  return;
}

void Bot_Event_PreTriggerMine(int param_1)
{
  char tmp_c1;
  gentity_s local_1c [4];
  uint32_t local_18;
  gentity_s *local_14;
  uint32_t uStack_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      HandleFromEntity(local_1c);
      uStack_10 = 4;
      local_18 = 0x4b;
      local_14 = local_1c;
      (*g_unk_008811f8)(param_1,&local_18);
      return;
    }
  }
  return;
}

void Bot_Event_PostTriggerMine(int param_1)
{
  char tmp_c1;
  gentity_s local_1c [4];
  uint32_t local_18;
  gentity_s *local_14;
  uint32_t uStack_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      HandleFromEntity(local_1c);
      uStack_10 = 4;
      local_18 = 0x4c;
      local_14 = local_1c;
      (*g_unk_008811f8)(param_1,&local_18);
      return;
    }
  }
  return;
}

void Bot_Event_MortarImpact(int param_1,uint32_t *param_2)
{
  char tmp_c1;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t *local_14;
  uint32_t local_10;
  uint32_t uStack_8;
  
  uStack_8 = 0x230866;
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      local_10 = 0xc;
      local_18 = 0x4d;
      local_14 = &local_24;
      local_24 = *param_2;
      local_20 = param_2[1];
      local_1c = param_2[2];
      (*g_unk_008811f8)(param_1,&local_18);
      return;
    }
  }
  return;
}

void Bot_Event_Spectated(int param_1,uint32_t param_2)
{
  char tmp_c1;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t *local_14;
  uint32_t local_10;
  uint32_t uStack_8;
  
  uStack_8 = 0x230906;
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      local_10 = 4;
      local_18 = 0x31;
      local_14 = &local_1c;
      local_1c = param_2;
      (*g_unk_008811f8)(param_1,&local_18);
      return;
    }
  }
  return;
}

void Bot_Event_ChatMessage(int param_1,uint32_t param_2,int param_3,char *param_4)
{
  char tmp_c1;
  uint32_t tmp_u2;
  uint32_t local_230;
  uint32_t local_22c;
  uint32_t *local_228;
  uint32_t local_224;
  uint32_t local_220;
  uint8_t auStack_21c [524];
  
  tmp_c1 = IsOmnibotLoaded();
  if ((tmp_c1 != '\0') && (tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600)), tmp_c1 != '\0')
     ) {
    if (param_3 == 2) {
      tmp_u2 = 0x44;
    }
    else if ((param_3 == 3) || (tmp_u2 = 0x42, param_3 == 1)) {
      tmp_u2 = 0x43;
    }
    local_220 = 0xffff;
    HandleFromEntity((gentity_s *)&local_230);
    local_220 = local_230;
    if (param_4 == (char *)0x0) {
      param_4 = "<unknown>";
    }
    Q_strncpyz(auStack_21c,param_4,0x200);
    local_224 = 0x204;
    local_22c = tmp_u2;
    local_228 = &local_220;
    (*g_unk_008811f8)(param_1,&local_22c);
  }
  return;
}

void Bot_Event_VoiceMacro(int param_1,uint32_t param_2,int param_3,char *param_4)
{
  char tmp_c1;
  int tmp_i2;
  uint32_t local_70;
  int local_6c;
  uint32_t *local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint8_t auStack_5c [76];
  
  tmp_c1 = IsOmnibotLoaded();
  if ((tmp_c1 != '\0') && (tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600)), tmp_c1 != '\0')
     ) {
    if (param_3 == 1) {
      tmp_i2 = 0x40;
    }
    else {
      tmp_i2 = (uint)(param_3 == 2) * 2 + 0x3f;
    }
    local_60 = 0xffff;
    HandleFromEntity((gentity_s *)&local_70);
    local_60 = local_70;
    if (param_4 == (char *)0x0) {
      param_4 = "<unknown>";
    }
    Q_strncpyz(auStack_5c,param_4,0x40);
    local_64 = 0x44;
    local_6c = tmp_i2;
    local_68 = &local_60;
    (*g_unk_008811f8)(param_1,&local_6c);
  }
  return;
}

void Bot_Event_Sound(uint32_t param_1,uint32_t param_2,char *param_3)
{
  float tmp_f1;
  char tmp_c2;
  uint tmp_u3;
  int tmp_i4;
  uint32_t local_a0 [4];
  float local_90;
  float fStack_8c;
  float local_84;
  float *local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float fStack_64;
  float local_60 [19];
  uint32_t local_14;
  uint32_t uStack_10;
  
  tmp_c2 = IsOmnibotLoaded();
  if (tmp_c2 != '\0') {
    tmp_u3 = 0;
    do {
      *(uint32_t *)((int)local_60 + tmp_u3) = 0;
      *(uint32_t *)((int)local_60 + tmp_u3 + 4) = 0;
      tmp_u3 = tmp_u3 + 8;
    } while (tmp_u3 < 0x50);
    *(uint32_t *)((int)local_60 + tmp_u3) = 0;
    local_14 = CONCAT22(GHIDRA_FIELD(local_14, 2, 2),0xffff);
    HandleFromEntity((gentity_s *)local_a0);
    uStack_10 = param_2;
    local_14 = local_a0[0];
    if (*(void **)(*g_InterfaceFunctions + 0x4c) == ETInterface::GetEntityPosition) {
      tmp_i4 = EntityFromHandle(local_a0[0],param_1);
      if ((tmp_i4 != 0) && (*(int *)(tmp_i4 + 0x194) != 0)) {
        if (*(int *)(tmp_i4 + 400) == 0) {
          AnglesToAxis(tmp_i4 + 0x174,&local_84);
          local_90 = (*(float *)(tmp_i4 + 0x140) + *(float *)(tmp_i4 + 0x134)) * 0.5;
          fStack_8c = (*(float *)(tmp_i4 + 0x144) + *(float *)(tmp_i4 + 0x138)) * 0.5;
          tmp_f1 = (*(float *)(tmp_i4 + 0x148) + *(float *)(tmp_i4 + 0x13c)) * 0.5;
          local_60[0x11] =
               local_68 * tmp_f1 +
               local_74 * fStack_8c + (float)local_80 * local_90 + *(float *)(tmp_i4 + 0x16c);
          local_60[0x12] =
               fStack_64 * tmp_f1 +
               fStack_8c * local_70 + local_90 * local_7c + *(float *)(tmp_i4 + 0x170);
          local_60[0x10] =
               tmp_f1 * local_6c +
               local_78 * fStack_8c + local_84 * local_90 + *(float *)(tmp_i4 + 0x168);
        }
        else {
          local_60[0x10] = *(float *)(tmp_i4 + 0x168);
          local_60[0x11] = *(float *)(tmp_i4 + 0x16c);
          local_60[0x12] = *(float *)(tmp_i4 + 0x170);
        }
      }
    }
    else {
      (**(void **)(*g_InterfaceFunctions + 0x4c))(g_InterfaceFunctions,local_a0[0],local_60 + 0x10);
    }
    if (param_3 == (char *)0x0) {
      param_3 = "<unknown>";
    }
    Q_strncpyz(local_60,param_3,0x40);
    local_84 = 2.52234e-44;
    local_7c = 1.17709e-43;
    local_80 = local_60;
    (*g_unk_008811fc)(&local_84);
  }
  return;
}

void Bot_Event_FireTeamCreated(int param_1,uint32_t param_2)
{
  char tmp_c1;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t *local_14;
  uint32_t local_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
      if (tmp_c1 != '\0') {
        local_10 = 4;
        local_18 = 0x4e;
        local_14 = &local_1c;
        local_1c = param_2;
        (*g_unk_008811f8)(param_1,&local_18);
        return;
      }
    }
  }
  return;
}

void Bot_Event_FireTeamDestroyed(int param_1)
{
  char tmp_c1;
  uint8_t local_19;
  uint32_t local_18;
  uint8_t *local_14;
  uint32_t local_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
      if (tmp_c1 != '\0') {
        local_10 = 1;
        local_18 = 0x4f;
        local_14 = &local_19;
        (*g_unk_008811f8)(param_1,&local_18);
        return;
      }
    }
  }
  return;
}

void Bot_Event_JoinedFireTeam(int param_1)
{
  char tmp_c1;
  gentity_s local_1c [4];
  uint32_t local_18;
  gentity_s *local_14;
  uint32_t uStack_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
      if (tmp_c1 != '\0') {
        HandleFromEntity(local_1c);
        uStack_10 = 4;
        local_18 = 0x50;
        local_14 = local_1c;
        (*g_unk_008811f8)(param_1,&local_18);
        return;
      }
    }
  }
  return;
}

void Bot_Event_LeftFireTeam(int param_1)
{
  char tmp_c1;
  uint8_t local_19;
  uint32_t local_18;
  uint8_t *local_14;
  uint32_t local_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
      if (tmp_c1 != '\0') {
        local_10 = 1;
        local_18 = 0x51;
        local_14 = &local_19;
        (*g_unk_008811f8)(param_1,&local_18);
        return;
      }
    }
  }
  return;
}

void Bot_Event_InviteFireTeam(uint32_t param_1,int param_2)
{
  char tmp_c1;
  gentity_s local_1c [4];
  uint32_t local_18;
  gentity_s *local_14;
  uint32_t local_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_2 * 0x600));
    if (tmp_c1 != '\0') {
      tmp_c1 = IsBot((gentity_s *)(g_entities + param_2 * 0x600));
      if (tmp_c1 != '\0') {
        HandleFromEntity(local_1c);
        local_10 = 4;
        local_18 = 0x52;
        local_14 = local_1c;
        (*g_unk_008811f8)(param_2,&local_18);
        return;
      }
    }
  }
  return;
}

void Bot_Event_FireTeam_Proposal(int param_1)
{
  char tmp_c1;
  gentity_s local_1c [4];
  uint32_t local_18;
  gentity_s *local_14;
  uint32_t local_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
      if (tmp_c1 != '\0') {
        HandleFromEntity(local_1c);
        local_10 = 4;
        local_18 = 0x53;
        local_14 = local_1c;
        (*g_unk_008811f8)(param_1,&local_18);
        return;
      }
    }
  }
  return;
}

void Bot_Event_FireTeam_Warn(int param_1,uint32_t param_2)
{
  char tmp_c1;
  gentity_s local_1c [4];
  uint32_t local_18;
  gentity_s *local_14;
  uint32_t local_10;
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
    if (tmp_c1 != '\0') {
      tmp_c1 = IsBot((gentity_s *)(g_entities + param_1 * 0x600));
      if (tmp_c1 != '\0') {
        HandleFromEntity(local_1c);
        local_18 = 0x54;
        local_10 = 4;
        local_14 = local_1c;
        (*g_unk_008811f8)(param_2,&local_18);
        return;
      }
    }
  }
  return;
}

void Bot_Event_EntityCreated(gentity_s *param_1)
{
  char tmp_c1;
  gentity_s *pgVar2;
  int tmp_i3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  gentity_s *pgVar7;
  gentity_s *local_40 [3];
  short local_34;
  uint16_t uStack_32;
  uint local_30;
  int local_2c;
  uint32_t local_28;
  short *local_24;
  uint32_t uStack_20;
  
  if ((param_1 == (gentity_s *)0x0) || (tmp_c1 = IsOmnibotLoaded(), tmp_c1 == '\0'))
  goto LAB_0023140e;
  pgVar7 = param_1;
  HandleFromEntity((gentity_s *)local_40);
  if (*(void **)(*g_InterfaceFunctions + 0x2c) == ETInterface::GetEntityClass) {
    pgVar2 = (gentity_s *)EntityFromHandle(local_40[0],pgVar7);
    if ((pgVar2 != (gentity_s *)0x0) && (*(int *)(pgVar2 + 0x194) != 0)) {
      tmp_i3 = _GetEntityClass(pgVar2);
      goto LAB_00231465;
    }
  }
  else {
    pgVar7 = local_40[0];
    tmp_i3 = (**(void **)(*g_InterfaceFunctions + 0x2c))(g_InterfaceFunctions,local_40[0]);
LAB_00231465:
    if (tmp_i3 != 0) {
      tmp_i6 = (int)(param_1 + -0x93e4a0) >> 9;
      local_34 = (short)tmp_i6 * -0x5555;
      local_30 = 0;
      uStack_32 = (&m_EntityHandles)[tmp_i6 * -0x2aaaaaaa];
      local_2c = tmp_i3;
      if (*(void **)(*g_InterfaceFunctions + 0x30) == ETInterface::GetEntityCategory) {
        tmp_i3 = EntityFromHandle(local_40[0],pgVar7);
        if (tmp_i3 != 0) {
          tmp_i5 = *(int *)(tmp_i3 + 400);
          if (tmp_i5 == 0) {
            switch(*(uint32_t *)(tmp_i3 + 4)) {
            case 0:
_L2984:
              if (*(int *)(tmp_i3 + 0x5c0) == 0x3f73d) {
                if (*(int *)(tmp_i3 + 0xf8) == 0x10) {
LAB_0023175e:
                  local_30 = local_30 | 0x8400;
                }
              }
              else {
                tmp_i5 = Q_stricmp(*(uint32_t *)(tmp_i3 + 0x1a4),"func_button");
                if (tmp_i5 == 0) goto LAB_0023175e;
                if (*(int *)(tmp_i3 + 0x5c0) == 0x1908e) goto _L3009;
              }
              break;
            case 2:
_L2991:
              if ((*(byte *)(tmp_i3 + 0x14d) & 1) != 0) {
                tmp_i5 = Q_strncmp(*(uint32_t *)(tmp_i3 + 0x1a4),"item_health",0xb);
                if (tmp_i5 == 0) {
                  local_30 = local_30 | 0x90;
                }
                else {
                  tmp_i5 = Q_strncmp(*(uint32_t *)(tmp_i3 + 0x1a4),"weapon_magicammo",0x10);
                  if (tmp_i5 == 0) {
                    local_30 = local_30 | 0x30;
                  }
                  else {
                    tmp_i5 = Q_stricmp(*(uint32_t *)(tmp_i3 + 0x1a4),"item_treasure");
                    if (tmp_i5 == 0) {
                      local_30 = local_30 | 0x10;
                    }
                    else if ((*(int *)(tmp_i3 + 0x33c) != 0) &&
                            (*(int *)(*(int *)(tmp_i3 + 0x33c) + 0x24) == 1)) {
                      local_30 = local_30 | 0x50;
                    }
                  }
                }
              }
              break;
            case 3:
_L2996:
              switch(*(uint32_t *)(tmp_i3 + 0xe8)) {
              case 4:
              case 5:
              case 9:
              case 0xd:
              case 0xf:
              case 0x15:
              case 0x1a:
              case 0x24:
              case 0x25:
              case 0x2a:
                goto _L3002;
              default:
                tmp_i3 = Q_strncmp(*(uint32_t *)(tmp_i3 + 0x1a4),"air strike",0xb);
                if (tmp_i3 == 0) goto _L3002;
                break;
              case 0x19:
              case 0x33:
                local_30 = local_30 | 0x141000;
                break;
              case 0x1c:
                local_30 = local_30 | 4;
              }
              break;
            case 4:
_L3003:
              if (*(int *)(tmp_i3 + 0x5c0) == 0x27cac) {
                tmp_u4 = local_30 | 0x40800;
                if (*(int *)(tmp_i3 + 0x1b8) != 0) {
                  tmp_u4 = local_30 | 0x40002;
                }
                local_30 = tmp_u4 | 0x8000;
                if (0 < *(int *)(tmp_i3 + 0x2c8)) {
                  local_30 = tmp_u4 | 0x8008;
                }
              }
              else {
                tmp_i5 = Q_stricmp(*(uint32_t *)(tmp_i3 + 0x1a4),"props_chair_hiback");
                if ((((tmp_i5 == 0) ||
                     (tmp_i5 = Q_stricmp(*(uint32_t *)(tmp_i3 + 0x1a4),"props_chair"), tmp_i5 == 0))
                    || (tmp_i5 = Q_stricmp(*(uint32_t *)(tmp_i3 + 0x1a4),"props_chair_side"),
                       tmp_i5 == 0)) &&
                   ((0 < *(int *)(tmp_i3 + 0x2c8) && (*(int *)(tmp_i3 + 0x2cc) == 1)))) {
                  local_30 = local_30 | 8;
                }
              }
              break;
            case 0xe:
_L3010:
              if (((*(byte *)(tmp_i3 + 0x1a8) & 0x20) == 0) && (1 < *(int *)(tmp_i3 + 0x4f4) - 1U)) {
                local_30 = local_30 | 0x40008;
              }
              break;
            case 0x19:
_L3002:
              local_30 = local_30 | 0x1004;
              break;
            case 0x26:
_L2995:
              local_30 = local_30 | 0x4000;
              break;
            case 0x29:
_L3009:
              if ((0 < *(int *)(tmp_i3 + 0x2c8)) && (1 < *(int *)(tmp_i3 + 0x458) - 1U)) {
                local_30 = local_30 | 0x2008;
              }
              break;
            case 0x31:
            case 0x32:
_L3012:
              local_30 = local_30 | 0x40010;
            }
          }
          else {
            if (0x17fff < tmp_i3 + -0x93e4a0) {
              switch(*(uint32_t *)(tmp_i3 + 4)) {
              case 0:
                goto _L2984;
              case 1:
                break;
              case 2:
                goto _L2991;
              case 3:
                goto _L2996;
              case 4:
                goto _L3003;
              default:
                goto _L2980;
              case 0xe:
                goto _L3010;
              case 0x19:
                goto _L3002;
              case 0x26:
                goto _L2995;
              case 0x29:
                goto _L3009;
              case 0x31:
              case 0x32:
                goto _L3012;
              }
            }
            if (((*(int *)(tmp_i3 + 0x458) != 1) && (*(int *)(tmp_i5 + 4) != 2)) &&
               (*(int *)(tmp_i5 + 3000) - 1U < 2)) {
              if (*(int *)(tmp_i3 + 0x2c8) < -0xae) goto _L2995;
              if (*(int *)(tmp_i5 + 0x154) == 0) {
                local_30 = local_30 | 8;
              }
              local_30 = local_30 | 1;
            }
          }
        }
      }
      else {
        (**(void **)(*g_InterfaceFunctions + 0x30))(g_InterfaceFunctions,local_40[0],&local_30);
      }
_L2980:
      local_24 = &local_34;
      uStack_20 = 0xc;
      local_28 = 0xc;
      (*g_unk_008811fc)(&local_28);
      (&g_unk_00877902)[tmp_i6 * -0x55555554] = (&g_unk_00877902)[tmp_i6 * -0x55555554] | 2;
    }
  }
  Bot_Util_CheckForGoalEntity(local_40[0]);
LAB_0023140e:
  if ((*(int *)(param_1 + 4) == 3) && (*(int *)(param_1 + 0xe8) == 0x1c)) {
    tmp_i3 = 0;
    do {
      if ((&g_SmokeGrenadeCache)[tmp_i3] == 0) {
        (&g_SmokeGrenadeCache)[tmp_i3] = param_1;
        return;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != 0x20);
  }
  return;
}

void Bot_Queue_EntityCreated(int param_1)
{
  if (param_1 != 0) {
    (&g_unk_00877902)[(param_1 + -0x93e4a0 >> 9) * -0x55555554] =
         (&g_unk_00877902)[(param_1 + -0x93e4a0 >> 9) * -0x55555554] | 1;
  }
  return;
}

void Bot_Event_EntityDeleted(int param_1)
{
  char tmp_c1;
  short tmp_s2;
  int *tmp_pi3;
  int tmp_i4;
  short local_2c;
  uint16_t local_2a;
  uint32_t local_28;
  short *local_24;
  uint32_t local_20;
  
  if (param_1 != 0) {
    tmp_c1 = IsOmnibotLoaded();
    tmp_i4 = param_1 + -0x93e4a0 >> 9;
    local_2c = (short)tmp_i4 * -0x5555;
    if (tmp_c1 != '\0') {
      local_2a = (&m_EntityHandles)[tmp_i4 * -0x2aaaaaaa];
      local_28 = 0xd;
      local_24 = &local_2c;
      local_20 = 4;
      (*g_unk_008811fc)(&local_28);
    }
    tmp_s2 = (&m_EntityHandles)[tmp_i4 * -0x2aaaaaaa];
    (&g_unk_00877902)[tmp_i4 * -0x55555554] = (&g_unk_00877902)[tmp_i4 * -0x55555554] & 0xfc;
    tmp_s2 = tmp_s2 + 1;
    if (tmp_s2 == 0) {
      tmp_s2 = 1;
    }
    (&m_EntityHandles)[tmp_i4 * -0x2aaaaaaa] = tmp_s2;
  }
  tmp_pi3 = &g_SmokeGrenadeCache;
  do {
    while (*tmp_pi3 == param_1) {
      *tmp_pi3 = 0;
      tmp_pi3 = tmp_pi3 + 1;
      if (tmp_pi3 == &AirstrikeEntities) {
        return;
      }
    }
    tmp_pi3 = tmp_pi3 + 1;
  } while (tmp_pi3 != &AirstrikeEntities);
  return;
}

void Bot_Util_SendTrigger
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  char tmp_c1;
  uint tmp_u2;
  uint32_t local_b0 [3];
  uint32_t local_a4 [38];
  
  tmp_c1 = IsOmnibotLoaded();
  if (tmp_c1 != '\0') {
    local_a4[0x24] = 0xffff;
    local_a4[0x25] = 0xffff;
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)(local_a4 + 0x12) + tmp_u2) = 0;
      *(uint32_t *)((int)local_a4 + tmp_u2 + 0x4c) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < 0x48);
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)local_a4 + tmp_u2) = 0;
      *(uint32_t *)((int)local_a4 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < 0x48);
    HandleFromEntity((gentity_s *)local_b0);
    local_a4[0x24] = local_b0[0];
    Q_strncpyz(local_a4,param_3,0x48);
    Q_strncpyz(local_a4 + 0x12,param_4,0x48);
    (*g_unk_008811f0)(local_a4);
  }
  return;
}

void Bot_Interface_Update(void)
{
  int tmp_i1;
  char tmp_c2;
  uint tmp_u3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  uint8_t *tmp_pu8;
  uint8_t *local_434;
  int local_430;
  float local_42c [2];
  float *local_424;
  uint32_t local_420;
  uint32_t local_41c [258];
  uint32_t uStack_14;
  
  uStack_14 = 0x231af9;
  tmp_c2 = IsOmnibotLoaded();
  if (tmp_c2 != '\0') {
    tmp_u3 = 0;
    do {
      *(uint32_t *)((int)local_41c + tmp_u3) = 0;
      *(uint32_t *)((int)local_41c + tmp_u3 + 4) = 0;
      tmp_u3 = tmp_u3 + 8;
    } while (tmp_u3 < 0x400);
    if (g_unk_00abe904 % (int)GHIDRA_FIELD(sv_fps, 12, 4) == 0) {
      if ((g_unk_02af58b0 == 0) &&
         ((float)GHIDRA_FIELD(g_timelimit, 8, 4) * 60000.0 - (float)(g_unk_00abe908 - g_unk_00abe918) < 120000.0)) {
        g_unk_02af58b0 = 1;
        Bot_Util_SendTrigger(0,0,"two minute warning.","twominute");
      }
      if ((g_unk_02af58b4 == 0) &&
         ((float)GHIDRA_FIELD(g_timelimit, 8, 4) * 60000.0 - (float)(g_unk_00abe908 - g_unk_00abe918) < 30000.0)) {
        g_unk_02af58b4 = 1;
        Bot_Util_SendTrigger(0,0,"thirty second warning.","thirtysecond");
      }
    }
    if ((float)GHIDRA_FIELD(g_gravity, 8, 4) != Bot_Interface_Update::serverGravity) {
      local_424 = local_42c;
      local_42c[0] = -(float)GHIDRA_FIELD(g_gravity, 8, 4);
      local_42c[1] = 2.10195e-44;
      local_420 = 4;
      (*g_unk_008811fc)(local_42c + 1);
      Bot_Interface_Update::serverGravity = (float)GHIDRA_FIELD(g_gravity, 8, 4);
    }
    if (GHIDRA_FIELD(g_cheats, 12, 4) != Bot_Interface_Update::cheatsEnabled) {
      local_42c[0] = (float)(uint)(GHIDRA_FIELD(g_cheats, 12, 4) != 0);
      local_42c[1] = 2.24208e-44;
      local_424 = local_42c;
      local_420 = 4;
      (*g_unk_008811fc)(local_42c + 1);
      Bot_Interface_Update::cheatsEnabled = GHIDRA_FIELD(g_cheats, 12, 4);
    }
    if ((int)GHIDRA_FIELD(g_maxclients, 12, 4) < 1) {
      local_430 = 0;
    }
    else {
      tmp_pu8 = g_entities;
      tmp_i6 = 0;
      local_430 = 0;
      tmp_i7 = GHIDRA_FIELD(g_maxclients, 12, 4);
      do {
        while (((tmp_i4 = *(int *)(tmp_pu8 + 0x194), tmp_i4 != 0 &&
                (tmp_i1 = *(int *)(tmp_pu8 + 400), tmp_i1 != 0)) && (*(int *)(tmp_i1 + 0x5ac) == 2))) {
          if ((*(int *)(tmp_i1 + 3000) == 3) && (*(int *)(tmp_i1 + 0xbc0) == 2)) {
            Bot_Event_Spectated(*(uint32_t *)(tmp_i1 + 0xbc4),tmp_i6);
            tmp_i4 = *(int *)(tmp_pu8 + 0x194);
          }
          if ((tmp_i4 == 1) && (tmp_c2 = IsBot((gentity_s *)tmp_pu8), tmp_c2 != '\0')) {
            local_430 = local_430 + 1;
            do {
              tmp_i7 = trap_BotGetServerCommand(tmp_i6,local_41c,0x400);
            } while (tmp_i7 != 0);
          }
          tmp_i6 = tmp_i6 + 1;
          tmp_pu8 = tmp_pu8 + 0x600;
          tmp_i7 = GHIDRA_FIELD(g_maxclients, 12, 4);
          if ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= tmp_i6) goto LAB_00231cb0;
        }
        tmp_i6 = tmp_i6 + 1;
        tmp_pu8 = tmp_pu8 + 0x600;
      } while (tmp_i6 < tmp_i7);
    }
LAB_00231cb0:
    local_434 = g_entities;
    if ((g_OmniBotFlags[0xc] & 8) == 0) {
      if (GHIDRA_FIELD(g_OmniBotPlaying, 12, 4) != local_430) {
        GHIDRA_FIELD(g_OmniBotPlaying, 12, 4) = local_430;
        tmp_u5 = va("%i",local_430);
        trap_Cvar_Set("omnibot_playing",tmp_u5);
      }
    }
    else if (GHIDRA_FIELD(g_OmniBotPlaying, 12, 4) != -1) {
      GHIDRA_FIELD(g_OmniBotPlaying, 12, 4) = 0xffffffff;
      trap_Cvar_Set("omnibot_playing",&g_unk_0025a5f5);
    }
    tmp_i7 = 0;
    do {
      if (((((&g_unk_00877902)[tmp_i7 * 4] & 1) != 0) && (*(int *)(local_434 + 0x194) != 0)) &&
         (*(void **)(local_434 + 0x2a4) != script_mover_spawn)) {
        (&g_unk_00877902)[tmp_i7 * 4] = (&g_unk_00877902)[tmp_i7 * 4] & 0xfe;
        Bot_Event_EntityCreated((gentity_s *)local_434);
      }
      tmp_i7 = tmp_i7 + 1;
      local_434 = local_434 + 0x600;
    } while (tmp_i7 != 0x400);
    SendDeferredGoals();
    (*g_unk_008811e4)();
  }
  return;
}

void Bot_AddDynamiteGoal(gentity_s *param_1,int param_2,char *param_3)
{
  int tmp_i1;
  
  if (param_2 == 1) {
    tmp_i1 = 4;
  }
  else {
    tmp_i1 = 2;
  }
  Bot_Util_AddGoal("defuse",param_1,tmp_i1,param_3,(char *)0x0,(obUserData_t *)0x0);
  return;
}

void Bot_AddFallenTeammateGoals(gentity_s *param_1,int param_2)
{
  char *tmp_pc1;
  int tmp_i2;
  
  if (param_2 == 1) {
    tmp_pc1 = (char *)_GetEntityName(param_1);
    tmp_i2 = 2;
  }
  else {
    if (param_2 != 2) {
      return;
    }
    tmp_pc1 = (char *)_GetEntityName(param_1);
    tmp_i2 = 4;
  }
  Bot_Util_AddGoal("revive",param_1,tmp_i2,tmp_pc1,(char *)0x0,(obUserData_t *)0x0);
  return;
}

uint8_t IsOmnibotLoaded(void)
{
  return g_IsOmnibotLoaded;
}

uint32_t Omnibot_GetLibraryPath(void)
{
  return g_OmnibotLibPath;
}

void Omnibot_strncpy(char *param_1,char *param_2,int param_3)
{
  char tmp_c1;
  uint tmp_u2;
  uint tmp_u3;
  
  if (param_3 != 0) {
    tmp_c1 = *param_2;
    *param_1 = tmp_c1;
    while (param_1 = param_1 + 1, tmp_c1 != '\0') {
      param_2 = param_2 + 1;
      param_3 = param_3 + -1;
      if (param_3 == 0) {
        return;
      }
      tmp_c1 = *param_2;
      *param_1 = tmp_c1;
    }
    if (param_3 != 1) {
      tmp_u3 = param_3 - 1;
      if (7 < tmp_u3) {
        tmp_u2 = tmp_u3;
        if (((uint)param_1 & 1) != 0) {
          *param_1 = '\0';
          param_1 = param_1 + 1;
          tmp_u2 = param_3 - 2;
        }
        if (((uint)param_1 & 2) != 0) {
          param_1[0] = '\0';
          param_1[1] = '\0';
          tmp_u2 = tmp_u2 - 2;
          param_1 = param_1 + 2;
        }
        if (((uint)param_1 & 4) != 0) {
          param_1[0] = '\0';
          param_1[1] = '\0';
          param_1[2] = '\0';
          param_1[3] = '\0';
          tmp_u2 = tmp_u2 - 4;
          param_1 = param_1 + 4;
        }
        tmp_u3 = tmp_u2 & 3;
        for (tmp_u2 = tmp_u2 >> 2; tmp_u2 != 0; tmp_u2 = tmp_u2 - 1) {
          param_1[0] = '\0';
          param_1[1] = '\0';
          param_1[2] = '\0';
          param_1[3] = '\0';
          param_1 = param_1 + 4;
        }
      }
      if ((tmp_u3 & 4) != 0) {
        param_1[0] = '\0';
        param_1[1] = '\0';
        param_1[2] = '\0';
        param_1[3] = '\0';
        param_1 = param_1 + 4;
      }
      if ((tmp_u3 & 2) != 0) {
        param_1[0] = '\0';
        param_1[1] = '\0';
        param_1 = param_1 + 2;
      }
      if ((tmp_u3 & 1) != 0) {
        *param_1 = '\0';
        return;
      }
    }
  }
  return;
}

uint8_t * Omnibot_ErrorString(uint param_1)
{
  if (param_1 < 7) {
    return *(uint8_t **)(BOTERRORS + param_1 * 4);
  }
  return &g_unk_0026ea14;
}

uint8_t * Omnibot_FixPath(char *param_1)
{
  char tmp_c1;
  char *tmp_pc2;
  
  tmp_pc2 = &Omnibot_FixPath(char_const*)::pathstr;
  Omnibot_strncpy(&Omnibot_FixPath(char_const*)::pathstr,param_1,0x200);
  g_unk_0088203f = 0;
  tmp_c1 = Omnibot_FixPath(char_const*)::pathstr;
  while (tmp_c1 != '\0') {
    while (tmp_c1 != '\\') {
      tmp_pc2 = tmp_pc2 + 1;
      tmp_c1 = *tmp_pc2;
      if (tmp_c1 == '\0') goto LAB_00239ed0;
    }
    *tmp_pc2 = '/';
    tmp_pc2 = tmp_pc2 + 1;
    tmp_c1 = *tmp_pc2;
  }
LAB_00239ed0:
  return &Omnibot_FixPath(char_const*)::pathstr;
}

char * OB_VA(char *param_1)
{
  int tmp_i1;
  
  tmp_i1 = OB_VA::iCurrentBuffer * 0x400;
  vsnprintf(OB_VA::buffers + tmp_i1,0x400,param_1,&stack0x00000008);
  OB_VA::iCurrentBuffer = (OB_VA::iCurrentBuffer + 1) % 3;
  return OB_VA::buffers + tmp_i1;
}

void OB_VA_OWNBUFFER(char *param_1,int param_2,char *param_3,...)
{
  vsnprintf(param_1,param_2,param_3,&stack0x00000010);
  return;
}

uint32_t OB_ShowLastError(char *param_1,char *param_2)
{
  char *tmp_pc1;
  
  if (param_2 == (char *)0x0) {
    param_2 = "<unknown error>";
  }
  tmp_pc1 = (char *)OB_VA("%s Failed with Error: %s",param_1,param_2);
  Omnibot_Load_PrintErr(tmp_pc1);
  return 1;
}

int Omnibot_LL(char *param_1)
{
  size_t tmp_s1;
  int tmp_i2;
  char *tmp_pc3;
  
  tmp_s1 = strlen(param_1);
  std::string::assign((char *)&g_OmnibotLibPath,(uint)param_1);
  tmp_i2 = dlopen(g_OmnibotLibPath,2,tmp_s1);
  tmp_pc3 = "found.";
  if (tmp_i2 == 0) {
    tmp_pc3 = (char *)dlerror();
    OB_ShowLastError("LoadLibrary",tmp_pc3);
    tmp_pc3 = "not found";
  }
  tmp_pc3 = (char *)OB_VA("Looking for %s, ",g_OmnibotLibPath,tmp_pc3);
  Omnibot_Load_PrintMsg(tmp_pc3);
  return tmp_i2;
}

int Omnibot_LoadLibrary(int param_1,char *param_2,char *param_3)
{
  uint tmp_u1;
  char *tmp_pc2;
  char *tmp_pc3;
  uint tmp_u4;
  void *tmp_pc5;
  int tmp_i6;
  uint32_t tmp_u7;
  
  if (param_3 == (char *)0x0) {
    param_3 = ".";
  }
  tmp_pc3 = param_2;
  tmp_pc2 = (char *)OB_VA("%s/%s.so",param_3,param_2);
  g_BotLibrary = Omnibot_LL(tmp_pc2);
  if (g_BotLibrary == 0) {
    tmp_pc2 = (char *)OB_VA(&g_unk_002718f6,param_2,tmp_pc3);
    g_BotLibrary = Omnibot_LL(tmp_pc2);
    if (g_BotLibrary == 0) {
      tmp_pc2 = getenv("HOME");
      if (tmp_pc2 != (char *)0x0) {
        tmp_pc3 = param_2;
        tmp_pc2 = (char *)OB_VA("%s/omni-bot/%s.so",tmp_pc2,param_2);
        g_BotLibrary = Omnibot_LL(tmp_pc2);
      }
      if (g_BotLibrary == 0) {
        tmp_pc2 = getenv("HOME");
        if (tmp_pc2 != (char *)0x0) {
          tmp_pc2 = (char *)OB_VA(&g_unk_002718f8,param_2,tmp_pc3);
          g_BotLibrary = Omnibot_LL(tmp_pc2);
        }
        if (g_BotLibrary == 0) {
          std::string::_M_mutate((uint)&g_OmnibotLibPath,0,*(uint *)(g_OmnibotLibPath + -0xc));
          return 1;
        }
      }
    }
  }
  tmp_pc3 = (char *)OB_VA("Found Omni-bot: %s, Attempting to Initialize",g_OmnibotLibPath,tmp_pc3);
  Omnibot_Load_PrintMsg(tmp_pc3);
  tmp_u1 = 0;
  do {
    tmp_u4 = tmp_u1;
    *(uint32_t *)((int)&g_BotFunctions + tmp_u4) = 0;
    *(uint32_t *)((int)&g_unk_008811e4 + tmp_u4) = 0;
    tmp_u1 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0x28);
  *(uint32_t *)((int)&g_unk_008811e8 + tmp_u4) = 0;
  tmp_pc5 = (void *)dlsym(g_BotLibrary,"ExportBotFunctionsFromDLL");
  if (tmp_pc5 == (void *)0x0) {
    tmp_u7 = Omnibot_ErrorString(2);
    tmp_pc3 = (char *)OB_VA("Omni-bot Failed with Error: %s",tmp_u7);
    Omnibot_Load_PrintErr(tmp_pc3);
    tmp_pc3 = (char *)dlerror();
    OB_ShowLastError("GetProcAddress",tmp_pc3);
    tmp_i6 = 2;
  }
  else {
    tmp_i6 = (*tmp_pc5)(&g_BotFunctions,0x2c);
    if (tmp_i6 == 0) {
      Omnibot_Load_PrintMsg("Omni-bot Loaded Successfully");
      tmp_i6 = (*g_BotFunctions)(g_InterfaceFunctions,param_1);
      g_IsOmnibotLoaded = tmp_i6 == 0;
    }
  }
  return tmp_i6;
}

void Omnibot_FreeLibrary(void)
{
  uint tmp_u1;
  uint tmp_u2;
  
  if (g_BotLibrary != 0) {
    dlclose(g_BotLibrary);
    g_BotLibrary = 0;
  }
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)&g_BotFunctions + tmp_u2) = 0;
    *(uint32_t *)((int)&g_unk_008811e4 + tmp_u2) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0x28);
  *(uint32_t *)((int)&g_unk_008811e8 + tmp_u2) = 0;
  g_InterfaceFunctions = 0;
  g_IsOmnibotLoaded = 0;
  return;
}

