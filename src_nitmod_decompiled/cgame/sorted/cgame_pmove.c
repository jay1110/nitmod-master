/* Player movement — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_pmove.h"

void PM_ReloadClip(void)
{
  int *tmp_pi1;
  int inreg_EAX;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  while( true ) {
    tmp_i4 = *pm;
    tmp_i2 = BG_FindAmmoForWeapon(inreg_EAX);
    tmp_i4 = *(int *)(tmp_i4 + (tmp_i2 + 100) * 4);
    tmp_i2 = *pm;
    tmp_i3 = BG_FindClipForWeapon(inreg_EAX);
    tmp_i2 = *(int *)(ammoTableMP + inreg_EAX * 0x48 + 8) - *(int *)(tmp_i2 + (tmp_i3 + 0xa4) * 4);
    if (tmp_i2 <= tmp_i4) {
      tmp_i4 = tmp_i2;
    }
    if (tmp_i4 != 0) {
      tmp_i2 = BG_FindAmmoForWeapon(inreg_EAX);
      tmp_pi1 = (int *)(*pm + 400 + tmp_i2 * 4);
      *tmp_pi1 = *tmp_pi1 - tmp_i4;
      tmp_i2 = BG_FindClipForWeapon(inreg_EAX);
      tmp_pi1 = (int *)(*pm + 0x290 + tmp_i2 * 4);
      *tmp_pi1 = *tmp_pi1 + tmp_i4;
    }
    if ((1 < inreg_EAX - 0x2cU) && (1 < inreg_EAX - 0x22U)) break;
    inreg_EAX = BG_AkimboSidearm(inreg_EAX);
  }
  return;
}

void PM_StartWeaponAnim(uint param_1)
{
  int tmp_i1;
  
  tmp_i1 = *pm;
  if (((*(int *)(tmp_i1 + 4) < 3) && (*(int *)(pm[1] + 8) < 1)) &&
     (*(char *)((int)pm + 0x12) != '\0')) {
    *(uint *)(tmp_i1 + 0x480) = param_1 | ~*(uint *)(tmp_i1 + 0x480) & 0x200;
    return;
  }
  return;
}

void PM_DropTimers(void)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  
  tmp_pi2 = pm;
  tmp_i3 = *pm;
  tmp_i1 = *(int *)(tmp_i3 + 0x10);
  if (tmp_i1 != 0) {
    if (g_unk_00f3e308 < tmp_i1) {
      *(int *)(tmp_i3 + 0x10) = tmp_i1 - g_unk_00f3e308;
      tmp_i3 = *tmp_pi2;
    }
    else {
      *(uint *)(tmp_i3 + 0xc) = *(uint *)(tmp_i3 + 0xc) & 0xffff7e9f;
      *(uint32_t *)(*tmp_pi2 + 0x10) = 0;
      tmp_i3 = *tmp_pi2;
    }
  }
  if (0 < *(int *)(tmp_i3 + 0x54)) {
    *(int *)(tmp_i3 + 0x54) = *(int *)(tmp_i3 + 0x54) - g_unk_00f3e308;
    tmp_i3 = *tmp_pi2;
    if (*(int *)(tmp_i3 + 0x54) < 0) {
      *(uint32_t *)(tmp_i3 + 0x54) = 0;
      tmp_i3 = *tmp_pi2;
    }
  }
  if (0 < *(int *)(tmp_i3 + 0x5c)) {
    *(int *)(tmp_i3 + 0x5c) = *(int *)(tmp_i3 + 0x5c) - g_unk_00f3e308;
    if (*(int *)(*tmp_pi2 + 0x5c) < 0) {
      *(uint32_t *)(*tmp_pi2 + 0x5c) = 0;
    }
  }
  tmp_i1 = *(int *)(tmp_pi2[1] + 8);
  if (0 < tmp_i1) {
    *(int *)(tmp_pi2[1] + 8) = tmp_i1 - g_unk_00f3e308;
    if (*(int *)(tmp_pi2[1] + 8) < 0) {
      *(uint32_t *)(tmp_pi2[1] + 8) = 0;
    }
  }
  return;
}

void PM_Friction(void)
{
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  uint tmp_u4;
  int tmp_i5;
  long double tmp_l6;
  long double tmp_l7;
  long double tmp_l8;
  long double tmp_l9;
  int local_30;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x26669;
  tmp_i2 = *pm;
  local_28 = *(uint32_t *)(tmp_i2 + 0x20);
  local_24 = *(uint32_t *)(tmp_i2 + 0x24);
  local_20 = *(uint32_t *)(tmp_i2 + 0x28);
  if (g_unk_00f3e30c != 0) {
    local_20 = 0;
  }
  tmp_l6 = (long double)VectorLength(&local_28);
  if (tmp_l6 < (long double)1) {
    local_30 = *pm;
    tmp_i5 = *(int *)(local_30 + 4);
    tmp_u4 = tmp_i5 - 1;
    if (1 < tmp_u4) {
      *(uint32_t *)(tmp_i2 + 0x20) = 0;
      *(uint32_t *)(tmp_i2 + 0x24) = 0;
      return;
    }
  }
  else {
    local_30 = *pm;
    tmp_i5 = *(int *)(local_30 + 4);
    tmp_u4 = tmp_i5 - 1;
  }
  if ((pm[3] - *(int *)(pm[1] + 0x2c)) - 0xfbU < 99) {
    tmp_i3 = pm[0x41];
    tmp_l8 = (long double)20.0 * tmp_l6 * (long double)g_unk_00f3e304 + (long double)0.0;
  }
  else {
    tmp_i3 = pm[0x41];
    tmp_l8 = (long double)0;
  }
  if (tmp_i3 < 2) {
    if (((g_unk_00f3e30c != 0) && ((g_unk_00f3e340 & 2) == 0)) &&
       ((*(byte *)(local_30 + 0xc) & 0x40) == 0)) {
      tmp_l9 = (long double)pm_stopspeed;
      if ((long double)pm_stopspeed <= tmp_l6) {
        tmp_l9 = tmp_l6;
      }
      tmp_l8 = tmp_l9 * (long double)pm_friction * (long double)g_unk_00f3e304 + tmp_l8;
    }
    if (tmp_i3 == 0) goto joined_r0x000267fb;
  }
  tmp_f1 = pm_slagfriction;
  if (pm[0x40] != 0x10) {
    tmp_f1 = pm_waterfriction;
  }
  tmp_l8 = (long double)tmp_i3 * tmp_l6 * (long double)tmp_f1 * (long double)g_unk_00f3e304 + tmp_l8;
joined_r0x000267fb:
  if (tmp_i5 == 2) {
    tmp_l8 = (long double)pm_spectatorfriction * tmp_l6 * (long double)g_unk_00f3e304 + tmp_l8;
  }
  if (g_unk_00f3e36c != 0) {
    tmp_l8 = (long double)pm_ladderfriction * tmp_l6 * (long double)g_unk_00f3e304 + tmp_l8;
  }
  tmp_l9 = (long double)0;
  tmp_l7 = tmp_l6 - tmp_l8;
  if (tmp_l6 - tmp_l8 < tmp_l9) {
    tmp_l7 = tmp_l9;
  }
  if ((1 < tmp_u4 || (long double)3.0 <= tmp_l6) || ((long double)1 <= tmp_l8)) {
    tmp_l9 = tmp_l7 / tmp_l6;
  }
  *(float *)(tmp_i2 + 0x20) = (float)((long double)*(float *)(tmp_i2 + 0x20) * tmp_l9);
  *(float *)(tmp_i2 + 0x24) = (float)((long double)*(float *)(tmp_i2 + 0x24) * tmp_l9);
  *(float *)(tmp_i2 + 0x28) = (float)(tmp_l9 * (long double)*(float *)(tmp_i2 + 0x28));
  return;
}

void PM_SetWaterLevel(void)
{
  int tmp_i1;
  int tmp_i2;
  bool tmp_b3;
  uint tmp_u4;
  int *tmp_pi5;
  uint32_t local_18;
  uint32_t local_14;
  float local_10;
  
  tmp_pi5 = pm;
  pm[0x41] = 0;
  tmp_pi5[0x40] = 0;
  local_18 = *(uint32_t *)(*tmp_pi5 + 0x14);
  local_14 = *(uint32_t *)(*tmp_pi5 + 0x18);
  local_10 = *(float *)(*tmp_pi5 + 0x1c) + *(float *)(*tmp_pi5 + 0x3e4) + 1.0;
  tmp_u4 = (*(void *)tmp_pi5[0x47])(&local_18,*(uint32_t *)(*tmp_pi5 + 0xa0));
  tmp_pi5 = pm;
  if ((tmp_u4 & 0x38) != 0) {
    tmp_i2 = *pm;
    tmp_i1 = (int)ROUND((float)*(int *)(tmp_i2 + 0xbc) - *(float *)(tmp_i2 + 0x3e4));
    pm[0x40] = tmp_u4;
    tmp_pi5[0x41] = 1;
    local_10 = (float)(int)ROUND((float)tmp_i1 * 0.5) +
               *(float *)(tmp_i2 + 0x1c) + *(float *)(tmp_i2 + 0x3e4);
    tmp_u4 = (*(void *)tmp_pi5[0x47])(&local_18,*(uint32_t *)(*tmp_pi5 + 0xa0));
    tmp_pi5 = pm;
    if ((tmp_u4 & 0x38) != 0) {
      pm[0x41] = 2;
      local_10 = (float)tmp_i1 + *(float *)(*tmp_pi5 + 0x1c) + *(float *)(*tmp_pi5 + 0x3e4);
      tmp_u4 = (*(void *)tmp_pi5[0x47])(&local_18,*(uint32_t *)(*tmp_pi5 + 0xa0));
      tmp_pi5 = pm;
      if ((tmp_u4 & 0x38) != 0) {
        tmp_b3 = true;
        pm[0x41] = 3;
        goto LAB_000268fd;
      }
    }
  }
  tmp_b3 = 2 < pm[0x41];
  tmp_pi5 = pm;
LAB_000268fd:
  BG_UpdateConditionValue(*(uint32_t *)(*tmp_pi5 + 0xa0),3,tmp_b3,1);
  return;
}

void PM_SetMovementDir(void)
{
  uint tmp_u1;
  int tmp_i2;
  long double tmp_l3;
  float local_24;
  float local_20;
  float local_1c;
  uint8_t local_18 [4];
  uint32_t local_14;
  
  local_24 = *(float *)(*pm + 0x14) - g_unk_00f3e350;
  local_20 = *(float *)(*pm + 0x18) - g_unk_00f3e354;
  local_1c = *(float *)(*pm + 0x1c) - g_unk_00f3e358;
  tmp_i2 = *pm;
  if (((short)pm[8] != 0) && (*(int *)(tmp_i2 + 0x50) != 0x3ff)) {
    tmp_l3 = (long double)VectorLength(&local_24);
    if ((tmp_l3 != (long double)0) && ((long double)5.0 * (long double)g_unk_00f3e304 < tmp_l3)) {
      VectorNormalize2(&local_24,local_18);
      vectoangles(local_18,local_18);
      tmp_l3 = (long double)AngleDelta(local_14,*(uint32_t *)(*pm + 0xb4));
      tmp_u1 = (uint)ROUND(tmp_l3);
      if ((char)pm[8] < '\0') {
        tmp_l3 = (long double)AngleNormalize180((float)(int)(tmp_u1 + 0xb4));
        tmp_u1 = (uint)ROUND(tmp_l3);
      }
      if ((int)(((int)tmp_u1 >> 0x1f ^ tmp_u1) - ((int)tmp_u1 >> 0x1f)) < 0x4c) {
        tmp_i2 = (int)(char)tmp_u1;
      }
      else {
        tmp_i2 = -0x4b;
        if (0 < (int)tmp_u1) {
          tmp_i2 = 0x4b;
        }
      }
      *(int *)(*pm + 100) = tmp_i2;
      return;
    }
    tmp_i2 = *pm;
  }
  *(uint32_t *)(tmp_i2 + 100) = 0;
  return;
}

long double PM_CmdScale_isra_0(char param_1,char param_2,char param_3)
{
  float tmp_f1;
  float tmp_f2;
  uint tmp_u3;
  int tmp_i4;
  uint tmp_u5;
  int tmp_i6;
  uint tmp_u7;
  long double tmp_l8;
  double tmp_d9;
  
  tmp_u3 = (uint)param_1;
  tmp_u5 = (uint)param_2;
  tmp_i4 = ((int)tmp_u3 >> 0x1f ^ tmp_u3) - ((int)tmp_u3 >> 0x1f);
  tmp_i6 = ((int)tmp_u5 >> 0x1f ^ tmp_u5) - ((int)tmp_u5 >> 0x1f);
  tmp_u7 = (uint)param_3;
  if (tmp_i4 < tmp_i6) {
    tmp_i4 = tmp_i6;
  }
  tmp_i6 = ((int)tmp_u7 >> 0x1f ^ tmp_u7) - ((int)tmp_u7 >> 0x1f);
  if ((tmp_i4 < tmp_i6) || (tmp_i6 = tmp_i4, tmp_i4 != 0)) {
    tmp_i4 = tmp_u5 * tmp_u5 + tmp_u3 * tmp_u3 + tmp_u7 * tmp_u7;
    tmp_f2 = SQRT((float)tmp_i4);
    if (NAN(tmp_f2)) {
      tmp_d9 = sqrt((double)tmp_i4);
      tmp_f2 = (float)tmp_d9;
    }
    tmp_i4 = *pm;
    if (((*(byte *)(pm + 4) & 0x20) == 0) || (*(int *)(pm[1] + 0x10) < 0x33)) {
      tmp_f1 = *(float *)(tmp_i4 + 0x404);
    }
    else {
      tmp_f1 = *(float *)(tmp_i4 + 0x408);
    }
    tmp_l8 = (long double)(((float)tmp_i6 * (float)*(int *)(tmp_i4 + 0x40)) / (tmp_f2 * 127.0)) *
            (long double)tmp_f1;
    if (*(int *)(tmp_i4 + 4) == 1) {
      tmp_l8 = tmp_l8 * (long double)3.0;
    }
    if ((long double)*(float *)(BG_Weapons + *(int *)(tmp_i4 + 0xa4) * 0x6b0 + 0x600) != (long double)0
       ) {
      tmp_l8 = (long double)*(float *)(BG_Weapons + *(int *)(tmp_i4 + 0xa4) * 0x6b0 + 0x600) * tmp_l8;
    }
    switch(*(int *)(tmp_i4 + 0xa4)) {
    case 5:
    case 0x1d:
    case 0x21:
    case 0x2e:
      if (GHIDRA_FIELD(cgs, 33787756, 4) != 1) {
        if ((*(byte *)(pm + 0x4e) & 8) != 0) {
          return tmp_l8 * (long double)0.75;
        }
        return tmp_l8 * (long double)0.5;
      }
    default:
      break;
    case 6:
      if (((*(byte *)(pm + 0x4e) & 8) == 0) || ((*(byte *)(pm + 4) & 1) != 0)) {
        tmp_l8 = (long double)(float)((long double)0.7 * tmp_l8);
      }
    }
  }
  else {
    tmp_l8 = (long double)0;
  }
  return tmp_l8;
}

void PM_TraceAllLegs_constprop_8(int param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  uint32_t tmp_u5;
  void *tmp_pc6;
  float tmp_f7;
  uint tmp_u8;
  double local_bc;
  double local_b4 [2];
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  int local_8c [2];
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  int local_54 [2];
  float local_4c;
  uint32_t uStack_14;
  
  uStack_14 = 0x26dbd;
  (*(void *)pm[0x46])(param_1,param_2,pm + 0x3a,pm + 0x3d,param_3,*(uint32_t *)(*pm + 0xa0),
                      pm[0x11]);
  tmp_i4 = *pm;
  if ((*(uint *)(tmp_i4 + 0x68) & 0x880001) != 0) {
    tmp_u5 = *(uint32_t *)(tmp_i4 + 0xa0);
    tmp_pc6 = (void *)pm[0x46];
    tmp_u8 = pm[0x11];
    sincos((double)((*(float *)(tmp_i4 + 0xb4) * 3.1415927) / 180.0),local_b4,&local_bc);
    if ((*(byte *)(tmp_i4 + 0x6a) & 8) == 0) {
      tmp_f1 = 32.0;
      tmp_f2 = 32.0;
      tmp_f7 = 0.0;
    }
    else {
      tmp_f1 = -32.0;
      tmp_f2 = -32.0;
      tmp_f7 = -0.0;
    }
    tmp_f2 = tmp_f2 * (float)local_b4[0];
    tmp_f1 = (float)local_bc * tmp_f1;
    local_a4 = *param_2 + tmp_f1;
    local_a0 = param_2[1] + tmp_f2;
    local_9c = param_2[2] + tmp_f7;
    local_98 = tmp_f1 + *param_3;
    local_94 = tmp_f2 + param_3[1];
    local_90 = tmp_f7 + param_3[2];
    (*tmp_pc6)(local_8c,&local_a4,&playerlegsProneMins,&playerlegsProneMaxs,&local_98,tmp_u5,
              tmp_u8 & 0xf9ffffff);
    if (((param_1 == 0) || (tmp_f3 = *(float *)(param_1 + 8), local_84 < tmp_f3)) ||
       (local_8c[0] != 0)) {
      local_a4 = *param_2 + tmp_f1;
      local_a0 = param_2[1] + tmp_f2;
      local_9c = param_2[2] + tmp_f7 + 18.0;
      local_98 = tmp_f1 + *param_3;
      local_94 = tmp_f2 + param_3[1];
      local_90 = tmp_f7 + 18.0 + param_3[2];
      (*tmp_pc6)(local_54,&local_a4,&playerlegsProneMins,&playerlegsProneMaxs,&local_98,tmp_u5,
                tmp_u8 & 0xf9ffffff);
      if (((local_54[0] == 0) && (local_54[1] == 0)) && (tmp_u8 = 0, local_84 < local_4c)) {
        do {
          *(uint32_t *)((int)local_8c + tmp_u8) = *(uint32_t *)((int)local_54 + tmp_u8);
          tmp_u8 = tmp_u8 + 4;
        } while (tmp_u8 < 0x38);
      }
      tmp_f3 = *(float *)(param_1 + 8);
    }
    if (((local_84 < tmp_f3) || (local_8c[1] != 0)) || (local_8c[0] != 0)) {
      tmp_u8 = 0;
      local_80 = (*param_3 - *param_2) * local_84 + *param_2;
      local_7c = (param_3[1] - param_2[1]) * local_84 + param_2[1];
      local_78 = local_84 * (param_3[2] - param_2[2]) + param_2[2];
      do {
        *(uint32_t *)(param_1 + tmp_u8) = *(uint32_t *)((int)local_8c + tmp_u8);
        tmp_u8 = tmp_u8 + 4;
      } while (tmp_u8 < 0x38);
    }
  }
  return;
}

void PM_CheckDuck(void)
{
  float tmp_f1;
  byte tmp_b2;
  uint tmp_u3;
  int tmp_i4;
  int *tmp_pi5;
  int tmp_i6;
  uint tmp_u7;
  uint tmp_u8;
  uint tmp_u9;
  bool tmp_b10;
  int local_54;
  
  tmp_pi5 = pm;
  tmp_i6 = *pm;
  tmp_b10 = *(int *)(tmp_i6 + 300) == 3;
  tmp_u8 = *(uint *)(tmp_i6 + 0xc) & 1;
  tmp_u9 = *(uint *)(tmp_i6 + 0xc) & 4;
  tmp_u3 = *(uint *)(tmp_i6 + 0x68);
  pm[0x3a] = *(int *)(tmp_i6 + 0x3dc);
  tmp_pi5[0x3b] = *(int *)(tmp_i6 + 0x3e0);
  tmp_u7 = tmp_u3 & 0x8000;
  tmp_pi5[0x3d] = *(int *)(tmp_i6 + 1000);
  tmp_pi5[0x3e] = *(int *)(tmp_i6 + 0x3ec);
  tmp_pi5[0x3c] = *(int *)(tmp_i6 + 0x3e4);
  tmp_i4 = firstTime_12356;
  if (*(int *)(tmp_i6 + 4) == 3) {
    tmp_pi5[0x3f] = *(int *)(tmp_i6 + 0x3f0);
    tmp_f1 = *(float *)(tmp_i6 + 0x400);
    goto LAB_00027230;
  }
  if (tmp_b10) {
    if ((-1 < *(char *)((int)tmp_pi5 + 0x22)) || (tmp_u9 != 0 || tmp_u7 != 0)) goto LAB_00027272;
LAB_00027200:
    *(uint *)(tmp_i6 + 0xc) = *(uint *)(tmp_i6 + 0xc) | 1;
    if ((tmp_i4 != 0) && (tmp_u8 == 0 && !tmp_b10)) {
      firstTime_12356 = 0;
      *(int *)(tmp_pi5[1] + 0x88) = GHIDRA_FIELD(cgs, 33788136, 4) + tmp_pi5[3];
    }
LAB_00027212:
    tmp_i6 = *tmp_pi5;
    tmp_b2 = *(byte *)(tmp_i6 + 0xc);
  }
  else {
    if (((tmp_u9 == 0 && tmp_u7 == 0) &&
        (((wasCrouching_12357 == 0 || (*(int *)(tmp_pi5[1] + 0x8c) < 1)) ||
         (*(int *)(tmp_pi5[1] + 0x8c) <= tmp_pi5[3])))) &&
       ((((0 < (int)GHIDRA_FIELD(cgs, 33788136, 4) && (0 < *(int *)(tmp_pi5[1] + 0x88))) &&
         (tmp_pi5[3] < *(int *)(tmp_pi5[1] + 0x88))) || (*(char *)((int)tmp_pi5 + 0x22) < '\0'))))
    goto LAB_00027200;
LAB_00027272:
    if (*(int *)(tmp_i6 + 0xa4) == 0x2a) goto LAB_00027200;
    tmp_pi5[0x3f] = *(int *)(tmp_i6 + 0x3f0);
    PM_TraceAllLegs_constprop_8(tmp_i6 + 0x14);
    tmp_pi5 = pm;
    if (local_54 != 0) goto LAB_00027212;
    *(uint *)(*pm + 0xc) = *(uint *)(*pm + 0xc) & 0xfffffffe;
    *(uint32_t *)(tmp_pi5[1] + 0x88) = 0;
    firstTime_12356 = 1;
    if (((tmp_u3 & 0x80000) != 0) || (tmp_u8 == 0)) goto LAB_00027212;
    wasCrouching_12357 = 1;
    *(int *)(tmp_pi5[1] + 0x8c) = GHIDRA_FIELD(cgs, 33788140, 4) + tmp_pi5[3];
    tmp_i6 = *tmp_pi5;
    tmp_b2 = *(byte *)(tmp_i6 + 0xc);
  }
  if ((tmp_b2 & 1) == 0) {
    tmp_pi5[0x3f] = *(int *)(tmp_i6 + 0x3f0);
    tmp_f1 = *(float *)(tmp_i6 + 0x3fc);
  }
  else {
    tmp_pi5[0x3f] = *(int *)(tmp_i6 + 0x3f4);
    tmp_f1 = *(float *)(tmp_i6 + 0x3f8);
  }
LAB_00027230:
  *(int *)(tmp_i6 + 0xbc) = (int)ROUND(tmp_f1);
  return;
}

void PM_WaterMove(void)
{
  uint *tmp_pu1;
  float tmp_f2;
  float tmp_f3;
  int *tmp_pi4;
  uint tmp_u5;
  int tmp_i6;
  long double tmp_l7;
  long double tmp_l8;
  long double tmp_l9;
  long double tmp_l10;
  long double tmp_l11;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_10 = 2.2525e-40;
  if ((*(int *)(*pm + 0x10) == 0) && (pm[0x41] == 2)) {
    local_18 = pml;
    local_14 = g_unk_00f3e2e4;
    local_10 = 0.0;
    VectorNormalize(&local_18);
    local_24 = local_18 * 30.0 + *(float *)(*pm + 0x14);
    local_20 = local_14 * 30.0 + *(float *)(*pm + 0x18);
    local_1c = local_10 * 30.0 + *(float *)(*pm + 0x1c) + 4.0;
    tmp_u5 = (*(void *)pm[0x47])(&local_24,*(uint32_t *)(*pm + 0xa0));
    if ((tmp_u5 & 1) != 0) {
      local_1c = local_1c + 16.0;
      tmp_i6 = (*(void *)pm[0x47])(&local_24,*(uint32_t *)(*pm + 0xa0));
      tmp_pi4 = pm;
      if (tmp_i6 == 0) {
        *(float *)(*pm + 0x20) = pml * 200.0;
        *(float *)(*tmp_pi4 + 0x24) = g_unk_00f3e2e4 * 200.0;
        *(float *)(*tmp_pi4 + 0x28) = g_unk_00f3e2e8 * 200.0;
        *(uint32_t *)(*tmp_pi4 + 0x28) = 0x43af0000;
        *(uint *)(*tmp_pi4 + 0xc) = *(uint *)(*tmp_pi4 + 0xc) | 0x100;
        *(uint32_t *)(*tmp_pi4 + 0x10) = 2000;
        PM_StepSlideMove(1);
        tmp_pi4 = pm;
        tmp_i6 = *pm;
        *(float *)(tmp_i6 + 0x28) =
             *(float *)(tmp_i6 + 0x28) - (float)*(int *)(tmp_i6 + 0x38) * g_unk_00f3e304;
        tmp_i6 = *tmp_pi4;
        if (0.0 <= *(float *)(tmp_i6 + 0x28)) {
          return;
        }
        tmp_pu1 = (uint *)(tmp_i6 + 0xc);
        *tmp_pu1 = *tmp_pu1 & 0xffff7e9f;
        *(uint32_t *)(*tmp_pi4 + 0x10) = 0;
        return;
      }
    }
  }
  PM_Friction();
  tmp_l7 = (long double)PM_CmdScale_isra_0(*(uint8_t *)((int)pm + 0x22));
  if (tmp_l7 == (long double)0) {
    tmp_l7 = (long double)-60.0;
    tmp_l10 = (long double)0;
    tmp_l11 = tmp_l10;
  }
  else {
    tmp_l8 = (long double)(short)(char)pm[8];
    tmp_l9 = (long double)(short)*(char *)((int)pm + 0x21);
    tmp_l10 = (long double)g_unk_00f3e2ec * tmp_l7 * tmp_l9 + (long double)pml * tmp_l7 * tmp_l8;
    local_24 = (float)tmp_l10;
    tmp_l11 = (long double)g_unk_00f3e2f0 * tmp_l7 * tmp_l9 + (long double)g_unk_00f3e2e4 * tmp_l7 * tmp_l8;
    local_20 = (float)tmp_l11;
    tmp_l7 = (long double)(short)*(char *)((int)pm + 0x22) * tmp_l7 +
            (long double)g_unk_00f3e2f4 * tmp_l7 * tmp_l9 + (long double)g_unk_00f3e2e8 * tmp_l7 * tmp_l8;
  }
  local_18 = (float)tmp_l10;
  local_14 = (float)tmp_l11;
  local_10 = (float)tmp_l7;
  tmp_l7 = (long double)VectorNormalize(&local_18);
  tmp_pi4 = pm;
  tmp_i6 = *pm;
  if (pm[0x40] == 0x10) {
    tmp_l10 = (long double)*(int *)(tmp_i6 + 0x40) * (long double)pm_slagSwimScale;
    tmp_f2 = pm_slagaccelerate;
    if (tmp_l10 < tmp_l7) {
      tmp_l7 = tmp_l10;
    }
  }
  else {
    tmp_l10 = (long double)*(int *)(tmp_i6 + 0x40) * (long double)pm_waterSwimScale;
    tmp_f2 = pm_wateraccelerate;
    if (tmp_l10 < tmp_l7) {
      tmp_l7 = tmp_l10;
    }
  }
  tmp_l10 = tmp_l7 - ((long double)*(float *)(tmp_i6 + 0x28) * (long double)local_10 +
                   (long double)*(float *)(tmp_i6 + 0x24) * (long double)local_14 +
                   (long double)*(float *)(tmp_i6 + 0x20) * (long double)local_18);
  if (tmp_l10 <= (long double)0) goto LAB_000275c0;
  tmp_l7 = (long double)tmp_f2 * (long double)g_unk_00f3e304 * tmp_l7;
  if (tmp_l7 <= tmp_l10) {
    if (*(int *)(tmp_i6 + 0x50) != 0x3ff) goto LAB_0002754c;
LAB_0002755e:
    if (tmp_l10 < tmp_l7) {
      tmp_l7 = tmp_l10;
    }
  }
  else {
    tmp_l7 = tmp_l10;
    if (*(int *)(tmp_i6 + 0x50) != 0x3ff) {
LAB_0002754c:
      tmp_l7 = (long double)(float)(((long double)1 / (long double)*(float *)(tmp_i6 + 0x418)) * tmp_l7);
      goto LAB_0002755e;
    }
  }
  *(float *)(tmp_i6 + 0x20) =
       (float)((long double)local_18 * tmp_l7 + (long double)*(float *)(tmp_i6 + 0x20));
  *(float *)(*tmp_pi4 + 0x24) =
       (float)((long double)local_14 * tmp_l7 + (long double)*(float *)(*tmp_pi4 + 0x24));
  *(float *)(*tmp_pi4 + 0x28) =
       (float)(tmp_l7 * (long double)local_10 + (long double)*(float *)(*tmp_pi4 + 0x28));
LAB_000275c0:
  if ((g_unk_00f3e310 != 0) &&
     (tmp_i6 = *tmp_pi4,
     *(float *)(tmp_i6 + 0x28) * g_unk_00f3e334 +
     *(float *)(tmp_i6 + 0x24) * g_unk_00f3e330 + *(float *)(tmp_i6 + 0x20) * g_unk_00f3e32c < 0.0)) {
    tmp_l7 = (long double)VectorLength(tmp_i6 + 0x20);
    tmp_pi4 = pm;
    tmp_i6 = *pm;
    tmp_f2 = g_unk_00f3e334 * *(float *)(tmp_i6 + 0x28) +
            g_unk_00f3e330 * *(float *)(tmp_i6 + 0x24) + *(float *)(tmp_i6 + 0x20) * g_unk_00f3e32c;
    if (tmp_f2 < 0.0) {
      tmp_f2 = tmp_f2 * 1.001;
    }
    else {
      tmp_f2 = tmp_f2 / 1.001;
    }
    tmp_f3 = (float)tmp_l7;
    *(float *)(tmp_i6 + 0x20) = *(float *)(tmp_i6 + 0x20) - g_unk_00f3e32c * tmp_f2;
    *(float *)(tmp_i6 + 0x24) = *(float *)(tmp_i6 + 0x24) - g_unk_00f3e330 * tmp_f2;
    *(float *)(tmp_i6 + 0x28) = *(float *)(tmp_i6 + 0x28) - tmp_f2 * g_unk_00f3e334;
    VectorNormalize(*tmp_pi4 + 0x20);
    tmp_pi4 = pm;
    *(float *)(*pm + 0x20) = *(float *)(*pm + 0x20) * tmp_f3;
    tmp_i6 = *tmp_pi4;
    *(float *)(tmp_i6 + 0x24) = *(float *)(tmp_i6 + 0x24) * tmp_f3;
    tmp_i6 = *tmp_pi4;
    *(float *)(tmp_i6 + 0x28) = tmp_f3 * *(float *)(tmp_i6 + 0x28);
  }
  PM_SlideMove(0);
  return;
}

void PM_AirMove(void)
{
  int *tmp_pi1;
  char tmp_c2;
  float tmp_f3;
  int *tmp_pi4;
  int tmp_i5;
  long double tmp_l6;
  long double tmp_l7;
  uint32_t tmp_u8;
  float local_28;
  float local_24;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_pi4 = pm;
  local_10 = 2.26887e-40;
  if ((((GHIDRA_FIELD(cgs, 33785376, 4) != 0) && (tmp_i5 = *pm, (*(byte *)(tmp_i5 + 0x6a) & 8) == 0)) &&
      ((*(uint *)(tmp_i5 + 0xc) & 0x280) == 0)) &&
     (((0.0 < *(float *)(tmp_i5 + 0x28) || (GHIDRA_FIELD(cgs, 33785376, 4) != 2)) &&
      ('\t' < *(char *)((int)pm + 0x22))))) {
    if ((*(uint *)(tmp_i5 + 0xc) & 2) == 0) {
      g_unk_00f3e310 = 0;
      g_unk_00f3e30c = 0;
      *(uint *)(*pm + 0xc) = *(uint *)(*pm + 0xc) | 2;
      *(uint32_t *)(*tmp_pi4 + 0x50) = 0x3ff;
      *(float *)(*tmp_pi4 + 0x28) = (float)GHIDRA_FIELD(cgs, 33785380, 4) * 270.0;
      if ((char)tmp_pi4[8] < '\0') {
        tmp_u8 = 5;
      }
      else {
        tmp_u8 = 4;
      }
      BG_AnimScriptEvent(*tmp_pi4,*(uint32_t *)(tmp_pi4[2] + 0x7f0),tmp_u8,0,1);
      tmp_pi4 = pm;
      *(uint *)(*pm + 0xc) = *(uint *)(*pm + 0xc) | 0x80;
      if (1 < tmp_pi4[0x41]) {
        PM_WaterMove();
        tmp_pi4 = pm;
      }
      tmp_i5 = tmp_pi4[3];
      if (0x351 < tmp_i5 - *(int *)(tmp_pi4[1] + 4)) {
        tmp_pi1 = (int *)(tmp_pi4[1] + 0x10);
        *tmp_pi1 = *tmp_pi1 + -0x9c4;
        tmp_i5 = tmp_pi4[1];
        if (*(int *)(tmp_i5 + 0x10) < 0) {
          *(uint32_t *)(tmp_i5 + 0x10) = 0;
          tmp_i5 = tmp_pi4[1];
        }
        *(int *)(tmp_i5 + 4) = tmp_pi4[3];
        tmp_i5 = tmp_pi4[3];
      }
      *(int *)(*tmp_pi4 + 0x47c) = tmp_i5;
    }
    else {
      *(uint8_t *)((int)pm + 0x22) = 0;
    }
  }
  PM_Friction();
  tmp_c2 = *(char *)((int)pm + 0x21);
  if (pm[3] - *(int *)(pm[1] + 0x2c) < 0x15e) {
    local_24 = 1.0;
    local_28 = 0.0;
  }
  else {
    local_28 = (float)(short)(char)pm[8];
    tmp_l6 = (long double)PM_CmdScale_isra_0(*(uint8_t *)((int)pm + 0x22));
    g_unk_00f3e2f4 = 0;
    local_24 = (float)tmp_l6;
  }
  g_unk_00f3e2e8 = 0;
  VectorNormalize(&pml);
  VectorNormalize(&g_unk_00f3e2ec);
  local_10 = 0.0;
  local_14 = g_unk_00f3e2f0 * (float)(short)tmp_c2 + g_unk_00f3e2e4 * local_28;
  local_18 = local_28 * pml + g_unk_00f3e2ec * (float)(short)tmp_c2;
  tmp_l6 = (long double)VectorNormalize(&local_18);
  tmp_pi4 = pm;
  tmp_i5 = *pm;
  tmp_l7 = tmp_l6 * (long double)local_24 -
          ((long double)*(float *)(tmp_i5 + 0x28) * (long double)local_10 +
          (long double)*(float *)(tmp_i5 + 0x24) * (long double)local_14 +
          (long double)*(float *)(tmp_i5 + 0x20) * (long double)local_18);
  if (tmp_l7 <= (long double)0) goto LAB_00027b10;
  tmp_l6 = (long double)pm_airaccelerate * (long double)g_unk_00f3e304 * tmp_l6 * (long double)local_24;
  if (tmp_l7 < tmp_l6) {
    tmp_l6 = tmp_l7;
    if (*(int *)(tmp_i5 + 0x50) != 0x3ff) goto LAB_00027ab2;
  }
  else {
    if (*(int *)(tmp_i5 + 0x50) != 0x3ff) {
LAB_00027ab2:
      tmp_l6 = (long double)(float)(((long double)1 / (long double)*(float *)(tmp_i5 + 0x418)) * tmp_l6);
    }
    if (tmp_l7 < tmp_l6) {
      tmp_l6 = tmp_l7;
    }
  }
  *(float *)(tmp_i5 + 0x20) =
       (float)((long double)local_18 * tmp_l6 + (long double)*(float *)(tmp_i5 + 0x20));
  *(float *)(*tmp_pi4 + 0x24) =
       (float)((long double)local_14 * tmp_l6 + (long double)*(float *)(*tmp_pi4 + 0x24));
  *(float *)(*tmp_pi4 + 0x28) =
       (float)(tmp_l6 * (long double)local_10 + (long double)*(float *)(*tmp_pi4 + 0x28));
LAB_00027b10:
  if (g_unk_00f3e310 != 0) {
    tmp_i5 = *tmp_pi4;
    tmp_f3 = g_unk_00f3e334 * *(float *)(tmp_i5 + 0x28) +
            g_unk_00f3e330 * *(float *)(tmp_i5 + 0x24) + *(float *)(tmp_i5 + 0x20) * g_unk_00f3e32c;
    if (tmp_f3 < 0.0) {
      tmp_f3 = tmp_f3 * 1.001;
    }
    else {
      tmp_f3 = tmp_f3 / 1.001;
    }
    *(float *)(tmp_i5 + 0x20) = *(float *)(tmp_i5 + 0x20) - g_unk_00f3e32c * tmp_f3;
    *(float *)(tmp_i5 + 0x24) = *(float *)(tmp_i5 + 0x24) - g_unk_00f3e330 * tmp_f3;
    *(float *)(tmp_i5 + 0x28) = *(float *)(tmp_i5 + 0x28) - tmp_f3 * g_unk_00f3e334;
  }
  PM_StepSlideMove(1);
  PM_SetMovementDir();
  return;
}

void PM_BeginWeaponReload(int param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  uint tmp_u4;
  uint tmp_u5;
  uint32_t tmp_u6;
  
  tmp_i3 = *pm;
  if ((1 < *(int *)(tmp_i3 + 0xa8) - 5U) && (*(int *)(tmp_i3 + 0xa8) != 0)) {
    return;
  }
  tmp_i1 = BG_FindAmmoForWeapon(*(uint32_t *)(tmp_i3 + 0xa4));
  if (*(int *)(tmp_i3 + (tmp_i1 + 100) * 4) == 0) {
    *(uint32_t *)(*pm + 0xa8) = 0;
    return;
  }
  if ((param_1 == 0x1d) || (param_1 == 0x2e)) {
    if ((*(int *)(*pm + 0x304) != 0) && ((*(byte *)(pm + 0x4e) & 0x20) == 0)) {
      return;
    }
  }
  else if ((*(int *)(BG_Weapons + param_1 * 0x6b0 + 0x5fc) != 0) &&
          (tmp_i3 = *pm, tmp_i1 = BG_FindClipForWeapon(param_1),
          *(int *)(tmp_i3 + (tmp_i1 + 0xa4) * 4) != 0)) {
    return;
  }
  if ((0x1d < param_1 - 0x16U) && (0xe < param_1 - 1U)) {
    return;
  }
  switch(param_1) {
  case 4:
  case 9:
  case 0xf:
  case 0x1c:
  case 0x30:
  case 0x31:
  case 0x32:
    break;
  default:
    if ((*(byte *)(*pm + 0x6a) & 8) == 0) {
      tmp_u6 = 0xb;
    }
    else {
      tmp_u6 = 0x16;
    }
    BG_AnimScriptEvent(*pm,*(uint32_t *)(pm[2] + 0x7f0),tmp_u6,0,1);
  }
  tmp_pi2 = pm;
  if ((param_1 != 0x2a) && (param_1 != 0x21)) {
    tmp_i1 = *pm;
    tmp_i3 = *(int *)(tmp_i1 + 0xa4);
    if (tmp_i3 < 0x24) {
LAB_00027ed0:
      if ((*(byte *)(pm + 0x4d) & 4) != 0) {
        tmp_i3 = BG_isLightWeaponSupportingFastReload(tmp_i3);
        if (tmp_i3 != 0) goto LAB_00027f28;
        tmp_u5 = 7;
        goto LAB_00027e18;
      }
      if ((*(char *)((int)pm + 0x12) == '\0') ||
         (tmp_u4 = *(uint *)(tmp_i1 + 0x480), (tmp_u4 & 0xfffffdff) == 7)) {
        tmp_i3 = *(int *)(ammoTableMP + param_1 * 0x48 + 0x14);
        goto LAB_00027da4;
      }
      tmp_u5 = 7;
LAB_00027e3a:
      tmp_pi2 = pm;
      if ((*(int *)(pm[1] + 8) < 1) && (*(int *)(tmp_i1 + 4) < 3)) {
        *(uint *)(tmp_i1 + 0x480) = tmp_u5 | ~tmp_u4 & 0x200;
      }
    }
    else {
      if (tmp_i3 < 0x26) {
LAB_00027f28:
        tmp_u5 = 8;
      }
      else {
        tmp_u5 = 9;
        if (tmp_i3 != 0x2e) goto LAB_00027ed0;
      }
LAB_00027e18:
      tmp_pi2 = pm;
      if (*(char *)((int)pm + 0x12) != '\0') {
        tmp_i1 = *pm;
        tmp_u4 = *(uint *)(tmp_i1 + 0x480);
        if (tmp_u5 != (tmp_u4 & 0xfffffdff)) goto LAB_00027e3a;
      }
    }
  }
  tmp_i3 = *(int *)(ammoTableMP + param_1 * 0x48 + 0x14);
  if (((*(byte *)(tmp_pi2 + 0x4d) & 4) != 0) &&
     (tmp_i1 = BG_isLightWeaponSupportingFastReload(param_1), tmp_pi2 = pm, tmp_i1 != 0)) {
    tmp_i3 = (int)ROUND((float)tmp_i3 * 0.65);
  }
LAB_00027da4:
  tmp_i1 = *tmp_pi2;
  if (*(int *)(tmp_i1 + 0xa8) == 0) {
    *(int *)(tmp_i1 + 0x2c) = *(int *)(tmp_i1 + 0x2c) + tmp_i3;
    tmp_i1 = *tmp_pi2;
  }
  else if (*(int *)(tmp_i1 + 0x2c) < tmp_i3) {
    *(int *)(tmp_i1 + 0x2c) = tmp_i3;
    tmp_i1 = *tmp_pi2;
  }
  *(uint32_t *)(tmp_i1 + 0xa8) = 7;
  BG_AddPredictableEventToPlayerstate(0x1c,0,*tmp_pi2);
  return;
}

void PM_AddEvent(uint32_t param_1)
{
  BG_AddPredictableEventToPlayerstate(param_1,0,*pm);
  return;
}

void PM_AddEventExt(uint32_t param_1,uint32_t param_2)
{
  BG_AddPredictableEventToPlayerstate(param_1,param_2,*pm);
  return;
}

bool PM_IdleAnimForWeapon(int param_1)
{
  bool tmp_b1;
  
  tmp_b1 = false;
  if (param_1 - 0x1bU < 0x14) {
    tmp_b1 = (1 << ((byte)(param_1 - 0x1bU) & 0x1f) & 0x98601U) != 0;
  }
  return tmp_b1;
}

uint32_t PM_AltSwitchFromForWeapon(void)
{
  return 10;
}

int PM_AltSwitchToForWeapon(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = 0xb;
  if (param_1 - 0x1dU < 9) {
    tmp_i1 = ~-(uint)((1 << ((byte)(param_1 - 0x1dU) & 0x1f) & 0x191U) == 0) + 0xb;
  }
  return tmp_i1;
}

int PM_AttackAnimForWeapon(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = 2;
  if (param_1 - 0x1bU < 0x14) {
    tmp_i1 = 3 - (uint)((1 << ((byte)(param_1 - 0x1bU) & 0x1f) & 0x90601U) == 0);
  }
  return tmp_i1;
}

uint32_t PM_LastAttackAnimForWeapon(int param_1)
{
  if (param_1 == 0x2a) {
    return 2;
  }
  if (param_1 < 0x2b) {
    if (param_1 - 0x24U < 2) {
      return 3;
    }
  }
  else if (param_1 == 0x2e) {
    return 3;
  }
  return 4;
}

int PM_ReloadAnimForWeapon(int param_1)
{
  int tmp_i1;
  
  if (((param_1 < 0x24) || ((tmp_i1 = 8, 0x25 < param_1 && (tmp_i1 = 9, param_1 != 0x2e)))) &&
     (tmp_i1 = 7, (*(byte *)(pm + 0x134) & 4) != 0)) {
    tmp_i1 = BG_isLightWeaponSupportingFastReload(param_1);
    return 8 - (uint)(tmp_i1 == 0);
  }
  return tmp_i1;
}

uint32_t PM_RaiseAnimForWeapon(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 6;
  if (param_1 - 0x1bU < 0x14) {
    tmp_u1 = *(uint32_t *)(CSWTCH_163 + (param_1 - 0x1bU) * 4);
  }
  return tmp_u1;
}

uint32_t PM_DropAnimForWeapon(int param_1)
{
  if (param_1 == 0x1b) {
    return 7;
  }
  if ((0x1a < param_1) && (param_1 - 0x24U < 2)) {
    return 0xc;
  }
  return 5;
}

void PM_AddTouchEnt(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i2 = pm;
  if (param_1 != 0x3fe) {
    tmp_i1 = *(int *)(pm + 100);
    if (tmp_i1 != 0x20) {
      if (tmp_i1 < 1) {
LAB_00028203:
        *(int *)(pm + 0x68 + tmp_i1 * 4) = param_1;
        *(int *)(tmp_i2 + 100) = tmp_i1 + 1;
      }
      else if (*(int *)(pm + 0x68) != param_1) {
        tmp_i3 = 0;
        do {
          tmp_i3 = tmp_i3 + 1;
          if (tmp_i3 == tmp_i1) goto LAB_00028203;
        } while (*(int *)(pm + 0x68 + tmp_i3 * 4) != param_1);
      }
    }
  }
  return;
}

void PM_ContinueWeaponAnim(uint param_1)
{
  int tmp_i1;
  
  if (*(char *)((int)pm + 0x12) != '\0') {
    tmp_i1 = *pm;
    if ((((*(uint *)(tmp_i1 + 0x480) & 0xfffffdff) != param_1) && (*(int *)(pm[1] + 8) < 1)) &&
       (*(int *)(tmp_i1 + 4) < 3)) {
      *(uint *)(tmp_i1 + 0x480) = ~*(uint *)(tmp_i1 + 0x480) & 0x200 | param_1;
    }
  }
  return;
}

void PM_ClipVelocity(float *param_1,float *param_2,float *param_3,float param_4)
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

void PM_TraceLegs(int *param_1,float *param_2,float *param_3,float *param_4,int param_5,int param_6,
                 void *param_7,uint32_t param_8,uint param_9)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  double local_7c;
  double local_74;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  int local_54 [2];
  float local_4c;
  float local_48;
  uint32_t local_44;
  float local_40;
  
  param_9 = param_9 & 0xf9ffffff;
  if (param_2 != (float *)0x0) {
    *param_2 = 0.0;
  }
  sincos((double)((*(float *)(param_6 + 4) * 3.1415927) / 180.0),&local_74,&local_7c);
  if ((*(byte *)(*pm + 0x6a) & 8) == 0) {
    tmp_f1 = 32.0;
    tmp_f2 = 32.0;
    tmp_f3 = 0.0;
  }
  else {
    tmp_f1 = -32.0;
    tmp_f2 = -32.0;
    tmp_f3 = -0.0;
  }
  tmp_f2 = (float)local_74 * tmp_f2;
  tmp_f1 = (float)local_7c * tmp_f1;
  local_6c = *param_3 + tmp_f1;
  local_68 = param_3[1] + tmp_f2;
  local_64 = param_3[2] + tmp_f3;
  local_60 = tmp_f1 + *param_4;
  local_5c = tmp_f2 + param_4[1];
  local_58 = tmp_f3 + param_4[2];
  (*param_7)(param_1,&local_6c,&playerlegsProneMins,&playerlegsProneMaxs,&local_60,param_8,param_9);
  if (((param_5 == 0) || ((float)param_1[2] < *(float *)(param_5 + 8))) || (*param_1 != 0)) {
    tmp_f3 = tmp_f3 + 18.0;
    local_6c = *param_3 + tmp_f1;
    local_68 = param_3[1] + tmp_f2;
    local_64 = param_3[2] + tmp_f3;
    local_60 = tmp_f1 + *param_4;
    local_5c = tmp_f2 + param_4[1];
    local_58 = param_4[2] + tmp_f3;
    (*param_7)(local_54,&local_6c,&playerlegsProneMins,&playerlegsProneMaxs,&local_60,param_8,
               param_9);
    if (((local_54[0] == 0) && (local_54[1] == 0)) && (tmp_u4 = 0, (float)param_1[2] < local_4c)) {
      do {
        *(uint32_t *)((int)param_1 + tmp_u4) = *(uint32_t *)((int)local_54 + tmp_u4);
        tmp_u4 = tmp_u4 + 4;
      } while (tmp_u4 < 0x38);
      if (param_2 != (float *)0x0) {
        *param_2 = tmp_f3;
        local_6c = local_48;
        local_68 = (float)local_44;
        local_64 = local_40;
        local_60 = local_48;
        local_5c = (float)local_44;
        local_58 = local_40 - 18.0;
        (*param_7)(local_54,&local_6c,&playerlegsProneMins,&playerlegsProneMaxs,&local_60,param_8,
                   param_9);
        if (local_54[0] == 0) {
          *param_2 = tmp_f3 - (local_64 - local_40);
        }
      }
    }
  }
  return;
}

void PM_TraceHead(uint32_t param_1,uint32_t param_2,float *param_3,uint32_t param_4,
                 int param_5,void *param_6,uint32_t param_7,uint param_8)

{
  float tmp_f1;
  float tmp_f2;
  double local_4c;
  double local_44 [2];
  float local_30;
  float local_2c;
  float local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_24 = 0xc1900000;
  local_20 = 0xc1900000;
  local_1c = 0xc0000000;
  local_18 = 0x41900000;
  local_14 = 0x41900000;
  local_10 = 0x41200000;
  sincos((double)((*(float *)(param_5 + 4) * 3.1415927) / 180.0),local_44,&local_4c);
  if ((*(byte *)(*pm + 0x6a) & 8) == 0) {
    tmp_f1 = -36.0;
    tmp_f2 = -36.0;
    local_28 = -0.0;
  }
  else {
    tmp_f1 = 36.0;
    tmp_f2 = 36.0;
    local_28 = 0.0;
  }
  local_30 = (float)local_4c * tmp_f1 + *param_3;
  local_2c = (float)local_44[0] * tmp_f2 + param_3[1];
  local_28 = local_28 + param_3[2];
  (*param_6)(param_1,param_2,&local_24,&local_18,&local_30,param_7,param_8 & 0xf9ffffff);
  return;
}

void PM_TraceAllLegs(int param_1,uint32_t param_2,float *param_3,float *param_4)
{
  int tmp_i1;
  uint tmp_u2;
  int local_54 [2];
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  
  (*(void *)pm[0x46])(param_1,param_3,pm + 0x3a,pm + 0x3d,param_4,*(uint32_t *)(*pm + 0xa0),
                      pm[0x11]);
  tmp_i1 = *pm;
  if (((*(uint *)(tmp_i1 + 0x68) & 0x880001) != 0) &&
     (((PM_TraceLegs(local_54,param_2,param_3,param_4,param_1,tmp_i1 + 0xb0,pm[0x46],
                     *(uint32_t *)(tmp_i1 + 0xa0),pm[0x11]), local_4c < *(float *)(param_1 + 8) ||
       (local_54[1] != 0)) || (local_54[0] != 0)))) {
    tmp_u2 = 0;
    local_48 = (*param_4 - *param_3) * local_4c + *param_3;
    local_44 = (param_4[1] - param_3[1]) * local_4c + param_3[1];
    local_40 = local_4c * (param_4[2] - param_3[2]) + param_3[2];
    do {
      *(uint32_t *)(param_1 + tmp_u2) = *(uint32_t *)((int)local_54 + tmp_u2);
      tmp_u2 = tmp_u2 + 4;
    } while (tmp_u2 < 0x38);
  }
  return;
}

void PM_GroundTrace(void)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint tmp_u6;
  int *tmp_pi7;
  int tmp_i8;
  int tmp_i9;
  double tmp_d10;
  uint32_t tmp_u11;
  int local_c4;
  int local_b4;
  uint32_t local_a4;
  uint32_t local_a0;
  float local_9c;
  uint32_t local_98;
  uint32_t local_94;
  float local_90;
  int local_8c [2];
  float local_84;
  float local_74;
  float local_70;
  float local_6c;
  int local_58;
  float local_54;
  float local_50;
  float local_4c;
  uint32_t uStack_14;
  
  uStack_14 = 0x28919;
  local_a4 = *(uint32_t *)(*pm + 0x14);
  local_a0 = *(uint32_t *)(*pm + 0x18);
  tmp_i8 = *pm;
  if ((*(byte *)(tmp_i8 + 0x68) & 0x20) == 0) {
    local_9c = *(float *)(tmp_i8 + 0x1c) - 0.25;
  }
  else {
    local_9c = *(float *)(tmp_i8 + 0x1c) - 1.0;
  }
  PM_TraceAllLegs(local_8c,pm[1] + 0x38,*pm + 0x14,&local_a4);
  tmp_u6 = 0;
  do {
    *(uint32_t *)((int)&g_unk_00f3e314 + tmp_u6) = *(uint32_t *)((int)local_8c + tmp_u6);
    tmp_u6 = tmp_u6 + 4;
  } while (tmp_u6 < 0x38);
  if (local_8c[0] == 0) {
LAB_000289a5:
    tmp_i8 = *pm;
  }
  else {
    tmp_i8 = *pm;
    if ((*(byte *)(tmp_i8 + 0x69) & 0x80) == 0) {
      if (pm[0x12] != 0) {
        Com_Printf("%i:allsolid\n",c_pmove);
        tmp_i8 = *pm;
      }
      local_b4 = -1;
LAB_00028ac5:
      local_c4 = -1;
      do {
        tmp_i9 = -1;
LAB_00028ae5:
        local_54 = *(float *)(tmp_i8 + 0x14) + (float)local_b4;
        local_50 = *(float *)(*pm + 0x18) + (float)local_c4;
        local_4c = (float)tmp_i9 + *(float *)(*pm + 0x1c);
        PM_TraceAllLegs_constprop_8(&local_54);
        if (local_8c[0] == 0) {
          local_54 = *(float *)(*pm + 0x14);
          local_50 = *(float *)(*pm + 0x18);
          local_4c = *(float *)(*pm + 0x1c) - 0.25;
          PM_TraceAllLegs_constprop_8(&local_54);
          tmp_u6 = 0;
          do {
            *(uint32_t *)((int)&g_unk_00f3e314 + tmp_u6) = *(uint32_t *)((int)local_8c + tmp_u6);
            tmp_u6 = tmp_u6 + 4;
          } while (tmp_u6 < 0x38);
          goto LAB_000289a5;
        }
        tmp_i9 = tmp_i9 + 1;
        if (tmp_i9 != 2) goto code_r0x00028b47;
        local_c4 = local_c4 + 1;
        if (local_c4 == 2) goto LAB_00028d30;
        tmp_i8 = *pm;
      } while( true );
    }
  }
  tmp_pi7 = pm;
  if (local_84 == 1.0) {
    if (*(int *)(tmp_i8 + 0x50) != 0x3ff) {
      if (pm[0x12] != 0) {
        Com_Printf("%i:lift\n",c_pmove);
        tmp_i8 = *pm;
      }
      local_98 = *(uint32_t *)(tmp_i8 + 0x14);
      local_94 = *(uint32_t *)(*pm + 0x18);
      local_90 = *(float *)(*pm + 0x1c) - 64.0;
      PM_TraceAllLegs_constprop_8(&local_98);
      if (local_4c == 1.0) {
        if ((char)pm[8] < '\0') {
          tmp_u11 = 5;
        }
        else {
          tmp_u11 = 4;
        }
        BG_AnimScriptEvent(*pm,*(uint32_t *)(pm[2] + 0x7f0),tmp_u11,0,1);
      }
      tmp_i8 = *pm;
      if (*(int *)(tmp_i8 + 0x50) == -1) {
        g_unk_00f3e30c = 0;
        g_unk_00f3e310 = 0;
        return;
      }
    }
    *(uint32_t *)(tmp_i8 + 0x50) = 0x3ff;
    g_unk_00f3e310 = 0;
    g_unk_00f3e30c = 0;
    return;
  }
  if (((0.0 < *(float *)(tmp_i8 + 0x28)) &&
      (10.0 < *(float *)(tmp_i8 + 0x28) * local_6c +
              *(float *)(tmp_i8 + 0x24) * local_70 + *(float *)(tmp_i8 + 0x20) * local_74)) &&
     ((*(byte *)(tmp_i8 + 0x6a) & 8) == 0)) {
    if (pm[0x12] != 0) {
      Com_Printf("%i:kickoff\n",c_pmove);
      tmp_i8 = *pm;
    }
    if ((char)pm[8] < '\0') {
      tmp_u11 = 5;
    }
    else {
      tmp_u11 = 4;
    }
    BG_AnimScriptEvent(tmp_i8,*(uint32_t *)(pm[2] + 0x7f0),tmp_u11,0,0);
LAB_00028a5a:
    *(uint32_t *)(*pm + 0x50) = 0x3ff;
    g_unk_00f3e30c = 0;
    g_unk_00f3e310 = 0;
    return;
  }
  if (local_6c < 0.7) {
    if (pm[0x12] != 0) {
      Com_Printf("%i:steep\n",c_pmove);
      tmp_i8 = *pm;
    }
    *(uint32_t *)(tmp_i8 + 0x50) = 0x3ff;
    g_unk_00f3e30c = 0;
    g_unk_00f3e310 = 1;
    return;
  }
  g_unk_00f3e310 = 1;
  g_unk_00f3e30c = 1;
  *(uint *)(*pm + 0xc) = *(uint *)(*pm + 0xc) & 0xffffff7f;
  tmp_i8 = *tmp_pi7;
  if ((*(uint *)(tmp_i8 + 0xc) & 0x100) != 0) {
    *(uint *)(tmp_i8 + 0xc) = *(uint *)(tmp_i8 + 0xc) & 0xfffffedf;
    *(uint32_t *)(*tmp_pi7 + 0x10) = 0;
    tmp_i8 = *tmp_pi7;
  }
  if (*(int *)(tmp_i8 + 0x50) != 0x3ff) goto LAB_00028c0d;
  if (tmp_pi7[0x12] != 0) {
    Com_Printf("%i:Land\n",c_pmove);
    tmp_i8 = *pm;
    tmp_pi7 = pm;
  }
  if ((*(int *)(tmp_i8 + 0x54) == 0) && (g_unk_00f3e364 < -220.0)) {
    BG_AnimScriptEvent(tmp_i8,*(uint32_t *)(tmp_pi7[2] + 0x7f0),6,0,1);
    tmp_i8 = *pm;
    tmp_pi7 = pm;
  }
  tmp_f1 = g_unk_00f3e364;
  tmp_i9 = *(int *)(tmp_i8 + 0x38);
  tmp_f2 = (float)-tmp_i9 * 0.5;
  tmp_f4 = g_unk_00f3e364 * g_unk_00f3e364 + tmp_f2 * 4.0 * (*(float *)(tmp_i8 + 0x1c) - g_unk_00f3e358);
  if (0.0 <= tmp_f4) {
    tmp_f3 = SQRT(tmp_f4);
    if (NAN(tmp_f3)) {
      tmp_d10 = sqrt((double)tmp_f4);
      tmp_f3 = (float)tmp_d10;
      tmp_pi7 = pm;
    }
    tmp_f1 = ((-tmp_f1 - tmp_f3) / (tmp_f2 + tmp_f2)) * (float)-tmp_i9 + tmp_f1;
    tmp_f1 = tmp_f1 * tmp_f1 * 0.0001;
    tmp_i8 = tmp_pi7[0x41];
    if (tmp_i8 != 3) {
      if (tmp_i8 == 2) {
        tmp_f1 = tmp_f1 * 0.25;
      }
      else if (tmp_i8 == 1) {
        tmp_f1 = tmp_f1 * 0.5;
      }
      if (tmp_f1 < 1.0) {
        tmp_i8 = *tmp_pi7;
        goto LAB_00028f36;
      }
      if (((_DAT_00f3e340 & 1) == 0) && (tmp_pi7[0x48] == 0)) {
        if (tmp_pi7[0x12] != 0) {
          Com_Printf("delta: %5.2f\n",(double)tmp_f1);
        }
        if (77.0 < tmp_f1) {
          tmp_u11 = BG_FootstepForSurface(_DAT_00f3e340);
          BG_AddPredictableEventToPlayerstate(0xd,tmp_u11,*pm);
          tmp_i8 = *pm;
          tmp_pi7 = pm;
          goto LAB_00028ef0;
        }
        if (67.0 < tmp_f1) {
          tmp_u11 = BG_FootstepForSurface(_DAT_00f3e340);
          BG_AddPredictableEventToPlayerstate(0x11,tmp_u11,*pm);
          nitrox_AddPredictableDamage(0x32,0xff,0xff,*pm);
          tmp_i8 = *pm;
          tmp_pi7 = pm;
          goto LAB_00028ef0;
        }
        tmp_pi7 = pm;
        if (58.0 < tmp_f1) {
          tmp_i8 = *pm;
          if (0 < *(int *)(tmp_i8 + 0xd0)) {
            tmp_u11 = BG_FootstepForSurface(_DAT_00f3e340);
            BG_AddPredictableEventToPlayerstate(0x10,tmp_u11,*pm);
            nitrox_AddPredictableDamage(0x19,0xff,0xff,*pm);
            tmp_i8 = *pm;
            tmp_pi7 = pm;
          }
          goto LAB_00028ef0;
        }
        if (48.0 < tmp_f1) {
          tmp_i8 = *pm;
          if (0 < *(int *)(tmp_i8 + 0xd0)) {
            tmp_u11 = BG_FootstepForSurface(_DAT_00f3e340);
            BG_AddPredictableEventToPlayerstate(0xf,tmp_u11,*pm);
            nitrox_AddPredictableDamage(0xf,0xff,0xff,*pm);
            tmp_i8 = *pm;
            tmp_pi7 = pm;
          }
          goto LAB_00028ef0;
        }
        if (tmp_f1 <= 38.75) {
          if (tmp_f1 <= 7.0) {
            tmp_u11 = BG_FootstepForSurface(_DAT_00f3e340);
            BG_AddPredictableEventToPlayerstate(1,tmp_u11,*pm);
            tmp_i8 = *pm;
            tmp_pi7 = pm;
          }
          else {
            tmp_u11 = BG_FootstepForSurface(_DAT_00f3e340);
            BG_AddPredictableEventToPlayerstate(0xc,tmp_u11,*pm);
            tmp_i8 = *pm;
            tmp_pi7 = pm;
          }
          goto LAB_00028ef0;
        }
        if (0 < *(int *)(*pm + 0xd0)) {
          tmp_u11 = BG_FootstepForSurface(_DAT_00f3e340);
          BG_AddPredictableEventToPlayerstate(0xe,tmp_u11,*pm);
          nitrox_AddPredictableDamage(10,0xff,0xff,*pm);
        }
        tmp_i8 = *pm;
        tmp_pi7 = pm;
LAB_00028efe:
        *(uint32_t *)(tmp_i8 + 0x28) = 0;
        *(uint32_t *)(tmp_i8 + 0x24) = 0;
        *(uint32_t *)(tmp_i8 + 0x20) = 0;
        tmp_i8 = *tmp_pi7;
      }
      else {
        tmp_i8 = *tmp_pi7;
LAB_00028ef0:
        if (38.75 < tmp_f1) goto LAB_00028efe;
      }
      *(uint32_t *)(tmp_i8 + 8) = 0;
    }
    tmp_i8 = *tmp_pi7;
  }
LAB_00028f36:
  if (g_unk_00f3e364 < -200.0) {
    *(uint *)(tmp_i8 + 0xc) = *(uint *)(tmp_i8 + 0xc) | 0x20;
    *(uint32_t *)(*tmp_pi7 + 0x10) = 0xfa;
    tmp_i8 = *tmp_pi7;
  }
LAB_00028c0d:
  *(int *)(tmp_i8 + 0x50) = local_58;
  if (local_58 == 0x3fe) {
    return;
  }
  tmp_i8 = tmp_pi7[0x19];
  if (tmp_i8 != 0x20) {
    if (0 < tmp_i8) {
      if (local_58 == tmp_pi7[0x1a]) {
        return;
      }
      tmp_i9 = 0;
      while (tmp_i9 + 1 != tmp_i8) {
        tmp_i5 = tmp_i9 + 0x1b;
        tmp_i9 = tmp_i9 + 1;
        if (local_58 == tmp_pi7[tmp_i5]) {
          return;
        }
      }
    }
    tmp_pi7[tmp_i8 + 0x1a] = local_58;
    tmp_pi7[0x19] = tmp_i8 + 1;
    return;
  }
  return;
code_r0x00028b47:
  tmp_i8 = *pm;
  goto LAB_00028ae5;
LAB_00028d30:
  local_b4 = local_b4 + 1;
  if (local_b4 == 2) goto LAB_00028a5a;
  tmp_i8 = *pm;
  goto LAB_00028ac5;
}

void PM_TraceAll(int param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  uint32_t tmp_u5;
  void *tmp_pc6;
  float tmp_f7;
  uint tmp_u8;
  double local_bc;
  double local_b4 [2];
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  int local_8c [2];
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  int local_54 [2];
  float local_4c;
  uint32_t uStack_14;
  
  uStack_14 = 0x293c9;
  (*(void *)pm[0x46])(param_1,param_2,pm + 0x3a,pm + 0x3d,param_3,*(uint32_t *)(*pm + 0xa0),
                      pm[0x11]);
  tmp_i4 = *pm;
  if ((*(uint *)(tmp_i4 + 0x68) & 0x880001) != 0) {
    tmp_u5 = *(uint32_t *)(tmp_i4 + 0xa0);
    tmp_pc6 = (void *)pm[0x46];
    tmp_u8 = pm[0x11];
    sincos((double)((*(float *)(tmp_i4 + 0xb4) * 3.1415927) / 180.0),local_b4,&local_bc);
    if ((*(byte *)(tmp_i4 + 0x6a) & 8) == 0) {
      tmp_f1 = 32.0;
      tmp_f2 = 32.0;
      tmp_f7 = 0.0;
    }
    else {
      tmp_f1 = -32.0;
      tmp_f2 = -32.0;
      tmp_f7 = -0.0;
    }
    tmp_f2 = tmp_f2 * (float)local_b4[0];
    tmp_f1 = (float)local_bc * tmp_f1;
    local_a4 = *param_2 + tmp_f1;
    local_a0 = param_2[1] + tmp_f2;
    local_9c = param_2[2] + tmp_f7;
    local_98 = tmp_f1 + *param_3;
    local_94 = tmp_f2 + param_3[1];
    local_90 = tmp_f7 + param_3[2];
    (*tmp_pc6)(local_8c,&local_a4,&playerlegsProneMins,&playerlegsProneMaxs,&local_98,tmp_u5,
              tmp_u8 & 0xf9ffffff);
    if (((param_1 == 0) || (tmp_f3 = *(float *)(param_1 + 8), local_84 < tmp_f3)) ||
       (local_8c[0] != 0)) {
      local_a4 = *param_2 + tmp_f1;
      local_a0 = param_2[1] + tmp_f2;
      local_9c = param_2[2] + tmp_f7 + 18.0;
      local_98 = tmp_f1 + *param_3;
      local_94 = tmp_f2 + param_3[1];
      local_90 = tmp_f7 + 18.0 + param_3[2];
      (*tmp_pc6)(local_54,&local_a4,&playerlegsProneMins,&playerlegsProneMaxs,&local_98,tmp_u5,
                tmp_u8 & 0xf9ffffff);
      if (((local_54[0] == 0) && (local_54[1] == 0)) && (tmp_u8 = 0, local_84 < local_4c)) {
        do {
          *(uint32_t *)((int)local_8c + tmp_u8) = *(uint32_t *)((int)local_54 + tmp_u8);
          tmp_u8 = tmp_u8 + 4;
        } while (tmp_u8 < 0x38);
      }
      tmp_f3 = *(float *)(param_1 + 8);
    }
    if (((local_84 < tmp_f3) || (local_8c[1] != 0)) || (local_8c[0] != 0)) {
      tmp_u8 = 0;
      local_80 = (*param_3 - *param_2) * local_84 + *param_2;
      local_7c = (param_3[1] - param_2[1]) * local_84 + param_2[1];
      local_78 = local_84 * (param_3[2] - param_2[2]) + param_2[2];
      do {
        *(uint32_t *)(param_1 + tmp_u8) = *(uint32_t *)((int)local_8c + tmp_u8);
        tmp_u8 = tmp_u8 + 4;
      } while (tmp_u8 < 0x38);
    }
  }
  return;
}

void PM_BeginWeaponChange(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint tmp_u3;
  int *tmp_pi4;
  uint8_t **tmp_ppu5;
  uint32_t **tmp_ppu6;
  int tmp_i7;
  uint32_t uStack_60;
  uint32_t *local_5c;
  uint32_t *local_58;
  uint8_t *local_54;
  uint32_t local_50;
  uint32_t local_4c;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint8_t local_24 [12];
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  tmp_ppu6 = &local_5c;
  tmp_ppu5 = &_GLOBAL_OFFSET_TABLE_;
  if ((*(byte *)(*pm + 0xd) & 2) != 0) {
    return;
  }
  if (0x32 < param_2 - 1U) {
    return;
  }
  local_5c = (uint32_t *)(*pm + 0x3d4);
  local_58 = (uint32_t *)param_2;
  uStack_60 = 0x29799;
  tmp_i1 = COM_BitCheck();
  tmp_pi4 = pm;
  if (tmp_i1 == 0) {
    return;
  }
  tmp_i1 = *pm;
  tmp_u3 = *(int *)(tmp_i1 + 0xa8) - 3;
  if ((tmp_u3 < 5) && ((1 << ((byte)tmp_u3 & 0x1f) & 0x13U) != 0)) {
    return;
  }
  if (*(int *)(tmp_i1 + 0x30) != 0) {
    return;
  }
  if (0 < *(int *)(tmp_i1 + 0x34)) {
    return;
  }
  *(int *)(tmp_i1 + 0x41c) = param_2;
  switch(param_2) {
  default:
    local_54 = (uint8_t *)*tmp_pi4;
    local_5c = (uint32_t *)(0x20 - (uint)(param_3 == 0));
    local_58 = (uint32_t *)0x0;
    uStack_60 = 0x2995a;
    BG_AddPredictableEventToPlayerstate();
    goto LAB_0002981c;
  case 1:
  case 4:
  case 9:
  case 0xf:
  case 0x1c:
  case 0x30:
  case 0x32:
    *(uint32_t *)(*tmp_pi4 + 0x34) = 0;
    local_54 = (uint8_t *)*tmp_pi4;
    break;
  case 0x16:
  case 0x17:
    if (param_2 != *(int *)(weapAlts + param_1 * 4)) {
      local_54 = (uint8_t *)*tmp_pi4;
      local_58 = (uint32_t *)0x0;
      local_5c = (uint32_t *)0x1f;
      uStack_60 = 0x29937;
      BG_AddPredictableEventToPlayerstate();
      goto LAB_0002981c;
    }
    goto LAB_00029bba;
  case 0x2a:
    local_54 = (uint8_t *)*tmp_pi4;
    if ((local_54[0x6a] & 8) != 0) {
      return;
    }
    if (tmp_pi4[0x41] == 3) {
      return;
    }
  }
  local_58 = (uint32_t *)0x0;
  local_5c = (uint32_t *)0x1f;
  uStack_60 = 0x29816;
  BG_AddPredictableEventToPlayerstate();
LAB_0002981c:
  tmp_pi4 = pm;
  if (param_2 != *(int *)(weapAlts + param_1 * 4)) {
    if (param_1 == 0x1b) {
      tmp_u3 = 7;
      tmp_pu2 = (uint32_t *)*pm;
      if ((int)tmp_pu2[1] < 3) goto LAB_00029861;
    }
    else {
      if ((param_1 < 0x1b) || (tmp_u3 = 0xc, 1 < param_1 - 0x24U)) {
        tmp_u3 = 5;
      }
      tmp_pu2 = (uint32_t *)*pm;
      if ((int)tmp_pu2[1] < 3) {
LAB_00029861:
        if ((*(int *)(pm[1] + 8) < 1) && (*(char *)((int)pm + 0x12) != '\0')) {
          tmp_pu2[0x120] = tmp_u3 | ~tmp_pu2[0x120] & 0x200;
          goto LAB_00029a86;
        }
      }
      switch(param_1) {
      case 0x1d:
        goto _L680;
      case 0x21:
        goto _L682;
      case 0x2a:
        goto _L692;
      }
    }
_L715:
    tmp_i7 = 0xfa;
    tmp_ppu6 = &local_5c;
    goto LAB_000298a5;
  }
LAB_00029bba:
  tmp_i1 = *tmp_pi4;
  if (((*(int *)(tmp_i1 + 4) < 3) && (*(int *)(tmp_pi4[1] + 8) < 1)) &&
     (*(char *)((int)tmp_pi4 + 0x12) != '\0')) {
    *(uint *)(tmp_i1 + 0x480) = ~*(uint *)(tmp_i1 + 0x480) & 0x200 | 10;
  }
LAB_00029a86:
  switch(param_1) {
  default:
    goto _L675;
  case 2:
  case 7:
    tmp_pu2 = (uint32_t *)*tmp_pi4;
    if (param_2 != *(int *)(weapAlts + param_1 * 4)) goto _L715;
LAB_00029a02:
    tmp_i7 = 0;
    tmp_ppu6 = &local_5c;
    break;
  case 0xe:
  case 0x26:
    tmp_pu2 = (uint32_t *)*tmp_pi4;
    if (param_2 == *(int *)(weapAlts + param_1 * 4)) {
      if ((*(byte *)((int)tmp_pu2 + 0x6a) & 8) == 0) {
        local_54 = (uint8_t *)0x10;
      }
      else {
        local_54 = (uint8_t *)0x12;
      }
      local_4c = 0;
      local_50 = 0;
      tmp_i7 = 1000;
      local_58 = *(uint32_t **)(tmp_pi4[2] + 0x7f0);
      uStack_60 = 0x29b98;
      local_5c = tmp_pu2;
      BG_AnimScriptEvent();
      goto LAB_000298cf;
    }
    goto _L715;
  case 0x16:
  case 0x17:
    tmp_pu2 = (uint32_t *)*tmp_pi4;
    if (param_2 != *(int *)(weapAlts + param_1 * 4)) goto _L715;
    tmp_i7 = 0;
    tmp_ppu6 = &local_5c;
    if ((tmp_pu2[param_2 + 0xa4] == 0) && (tmp_ppu6 = &local_5c, tmp_pu2[param_2 + 100] != 0)) {
      uStack_60 = 0x29b3b;
      PM_ReloadClip();
      tmp_pi4 = *(int **)(memoryPool + (int)(tmp_ppu5 + 0x5991f));
      tmp_pu2 = (uint32_t *)*tmp_pi4;
      tmp_ppu6 = (uint32_t **)&uStack_60;
    }
    break;
  case 0x1d:
_L680:
    if (param_2 == GHIDRA_FIELD(weapAlts, 116, 4)) {
      local_30 = pml;
      local_54 = local_24;
      local_2c = g_unk_00f3e2e4;
      local_58 = &local_18;
      local_28 = g_unk_00f3e2e8;
      local_18 = g_unk_00f3e2ec;
      local_14 = g_unk_00f3e2f0;
      local_10 = g_unk_00f3e2f4;
      uStack_60 = 0x29c52;
      local_5c = &local_30;
      CrossProduct();
      local_58 = (uint32_t *)(pm[1] + 0x3c);
      uStack_60 = 0x29c6a;
      local_5c = &local_30;
      AxisToAngles();
      tmp_i7 = 0;
      tmp_pu2 = (uint32_t *)*pm;
      tmp_i1 = *(int *)(weapAlts + param_1 * 4);
      tmp_pi4 = pm;
      goto LAB_00029aad;
    }
    goto _L675;
  case 0x1f:
  case 0x29:
    tmp_pu2 = (uint32_t *)*tmp_pi4;
    tmp_i7 = 0x32;
    tmp_ppu6 = &local_5c;
    if (param_2 != *(int *)(weapAlts + param_1 * 4)) {
      tmp_i7 = 0xfa;
      tmp_ppu6 = &local_5c;
    }
    break;
  case 0x21:
_L682:
    if (param_2 == GHIDRA_FIELD(weapAlts, 132, 4)) {
      local_30 = pml;
      local_54 = local_24;
      local_2c = g_unk_00f3e2e4;
      local_58 = &local_18;
      local_28 = g_unk_00f3e2e8;
      local_18 = g_unk_00f3e2ec;
      local_14 = g_unk_00f3e2f0;
      local_10 = g_unk_00f3e2f4;
      uStack_60 = 0x299e2;
      local_5c = &local_30;
      CrossProduct();
      local_58 = (uint32_t *)(pm[1] + 0x3c);
      uStack_60 = 0x299fa;
      local_5c = &local_30;
      AxisToAngles();
      tmp_pu2 = (uint32_t *)*pm;
      tmp_pi4 = pm;
      goto LAB_00029a02;
    }
_L675:
    tmp_pu2 = (uint32_t *)*tmp_pi4;
    tmp_i7 = 0xfa;
    tmp_ppu6 = &local_5c;
    break;
  case 0x24:
  case 0x25:
    tmp_pu2 = (uint32_t *)*tmp_pi4;
    tmp_i7 = 0;
    tmp_ppu6 = &local_5c;
    if (param_2 != *(int *)(weapAlts + param_1 * 4)) {
      tmp_i7 = 0xfa;
      tmp_ppu6 = &local_5c;
    }
    break;
  case 0x2a:
    tmp_pu2 = (uint32_t *)*tmp_pi4;
_L692:
    tmp_i7 = 0;
    tmp_ppu6 = &local_5c;
    if (param_2 != GHIDRA_FIELD(weapAlts, 168, 4)) {
      tmp_i7 = 0xfa;
      tmp_ppu6 = &local_5c;
    }
    break;
  case 0x2e:
    tmp_pu2 = (uint32_t *)*tmp_pi4;
    tmp_i7 = 0xfa;
    tmp_i1 = GHIDRA_FIELD(weapAlts, 184, 4);
LAB_00029aad:
    tmp_ppu6 = &local_5c;
    if (param_2 == tmp_i1) {
      tmp_i7 = 0;
      tmp_ppu6 = &local_5c;
    }
  }
LAB_000298a5:
  tmp_ppu6[4] = (uint32_t *)0x0;
  tmp_ppu6[3] = (uint32_t *)0x0;
  tmp_ppu6[2] = (uint32_t *)0x7;
  tmp_i1 = *(int *)(tmp_pi4[2] + 0x7f0);
  *tmp_ppu6 = tmp_pu2;
  tmp_ppu6[1] = (uint32_t *)tmp_i1;
  tmp_ppu6[-1] = (uint32_t *)0x298cf;
  BG_AnimScriptEvent();
LAB_000298cf:
  tmp_pi4 = *(int **)(memoryPool + (int)(tmp_ppu5 + 0x5991f));
  tmp_i1 = *tmp_pi4;
  if (*(int *)((int)tmp_ppu6 + 0x68) == 0) {
    *(uint32_t *)(tmp_i1 + 0xa8) = 3;
  }
  else {
    *(uint32_t *)(tmp_i1 + 0xa8) = 4;
  }
  tmp_pi4 = (int *)(*tmp_pi4 + 0x2c);
  *tmp_pi4 = *tmp_pi4 + tmp_i7;
  return;
}

void PM_CheckForReload(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  uint tmp_u6;
  byte tmp_b7;
  bool tmp_b8;
  
  if (1 < param_1 - 0x24U) {
    tmp_b7 = *(byte *)((int)pm + 0x11) & 8;
    if (((*(byte *)((int)pm + 0x11) & 1) != 0) && (*(int *)(pm[1] + 0x80) != 0)) {
      tmp_b7 = 1;
    }
    tmp_u6 = *(int *)(*pm + 0xa8) - 1;
    if ((6 < tmp_u6) || ((1 << ((byte)tmp_u6 & 0x1f) & 0x4fU) == 0)) {
      tmp_b8 = true;
      if (*(int *)pm[1] == 0) {
        tmp_b8 = *(int *)(ammoTableMP + param_1 * 0x48 + 0x38) == 0;
      }
      tmp_i2 = BG_FindClipForWeapon(param_1);
      tmp_i3 = BG_FindAmmoForWeapon(param_1);
      if (param_1 - 0x27U < 3) {
        if (((tmp_b7 != 0) && (*(int *)(*pm + (tmp_i3 + 100) * 4) != 0)) &&
           (*(int *)(*pm + (tmp_i2 + 0xa4) * 4) < *(int *)(ammoTableMP + param_1 * 0x48 + 8))) {
          if (((*(byte *)(pm + 0x4f) & 0x20) != 0) || (GHIDRA_FIELD(cgs, 33787756, 4) == 2)) goto LAB_00029e44;
          PM_BeginWeaponChange(param_1,*(uint32_t *)(weapAlts + param_1 * 4),1);
        }
      }
      else {
        tmp_i1 = *pm;
        if (*(int *)(tmp_i1 + 0x2c) < 1) {
          if (tmp_b7 == 0) {
            if (((tmp_b8) && (*(int *)(tmp_i1 + (tmp_i2 + 0xa4) * 4) == 0)) &&
               (*(int *)(tmp_i1 + (tmp_i3 + 100) * 4) != 0)) {
              if ((param_1 - 0x2cU < 2) || (param_1 - 0x22U < 2)) {
                tmp_u4 = BG_AkimboSidearm(param_1);
                tmp_i2 = BG_FindClipForWeapon(tmp_u4);
                if (*(int *)(tmp_i1 + (tmp_i2 + 0xa4) * 4) != 0) {
                  return;
                }
              }
LAB_00029e44:
              PM_BeginWeaponReload();
              return;
            }
          }
          else if (*(int *)(tmp_i1 + (tmp_i3 + 100) * 4) != 0) {
            tmp_i2 = *(int *)(tmp_i1 + (tmp_i2 + 0xa4) * 4);
            tmp_i3 = *(int *)(ammoTableMP + param_1 * 0x48 + 8);
            if ((param_1 - 0x2cU < 2) || (param_1 - 0x22U < 2)) {
              tmp_u4 = BG_AkimboSidearm(param_1);
              tmp_i5 = BG_FindClipForWeapon(tmp_u4);
              tmp_i1 = *(int *)(tmp_i1 + (tmp_i5 + 0xa4) * 4);
              tmp_u4 = BG_AkimboSidearm(param_1);
              tmp_i5 = BG_FindClipForWeapon(tmp_u4);
              if (tmp_i1 < *(int *)(ammoTableMP + tmp_i5 * 0x48 + 8)) goto LAB_00029e44;
            }
            if (tmp_i2 < tmp_i3) goto LAB_00029e44;
          }
        }
      }
    }
  }
  return;
}

void PM_WeaponUseAmmo(int param_1,int param_2)
{
  int *tmp_pi1;
  int *tmp_pi2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  bool local_21;
  
  local_21 = param_1 == 5 && GHIDRA_FIELD(cgs, 33787756, 4) == 1;
  if (param_1 != 5 || GHIDRA_FIELD(cgs, 33787756, 4) != 1) {
    local_21 = (bool)((byte)GHIDRA_FIELD(cgs, 33787760, 4) & 1);
  }
  tmp_i3 = BG_FindClipForWeapon(param_1);
  if ((param_1 - 0x2cU < 2) || (param_1 - 0x22U < 2)) {
    tmp_i6 = *pm;
    tmp_u4 = BG_AkimboSidearm(param_1);
    tmp_i5 = BG_FindClipForWeapon(tmp_u4);
    tmp_u4 = *(uint32_t *)(tmp_i6 + (tmp_i5 + 0xa4) * 4);
    tmp_i6 = *pm;
    tmp_i5 = BG_FindClipForWeapon(param_1);
    tmp_i6 = BG_AkimboFireSequence(param_1,*(uint32_t *)(tmp_i6 + (tmp_i5 + 0xa4) * 4),tmp_u4);
    if (tmp_i6 == 0) {
      tmp_i3 = BG_AkimboSidearm(param_1);
    }
  }
  tmp_pi2 = pm;
  tmp_pi1 = (int *)(*pm + tmp_i3 * 4 + 0x290);
  *tmp_pi1 = *tmp_pi1 - param_2;
  tmp_i6 = tmp_i3 * 4 + *tmp_pi2;
  if ((*(int *)(tmp_i6 + 0x290) == 0) && (local_21 != false)) {
    *(uint32_t *)(tmp_i6 + 0x290) = *(uint32_t *)(ammoTableMP + tmp_i3 * 0x48 + 0x10);
  }
  return;
}

uint32_t PM_WeaponAmmoAvailable(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i1 = BG_FindClipForWeapon(param_1);
  if ((param_1 - 0x2cU < 2) || (param_1 - 0x22U < 2)) {
    tmp_i4 = *pm;
    tmp_u2 = BG_AkimboSidearm(param_1);
    tmp_i3 = BG_FindClipForWeapon(tmp_u2);
    tmp_u2 = *(uint32_t *)(tmp_i4 + (tmp_i3 + 0xa4) * 4);
    tmp_i4 = *pm;
    tmp_i3 = BG_FindClipForWeapon(param_1);
    tmp_i4 = BG_AkimboFireSequence(param_1,*(uint32_t *)(tmp_i4 + (tmp_i3 + 0xa4) * 4),tmp_u2);
    if (tmp_i4 == 0) {
      tmp_i1 = BG_AkimboSidearm(param_1);
    }
  }
  return *(uint32_t *)(*pm + (tmp_i1 + 0xa4) * 4);
}

bool PM_WeaponClipEmpty(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i1 = *pm;
  tmp_i2 = BG_FindClipForWeapon(param_1);
  return *(int *)(tmp_i1 + (tmp_i2 + 0xa4) * 4) == 0;
}

void PM_CoolWeapons(void)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  int tmp_i4;
  int *tmp_pi5;
  int tmp_i6;
  float tmp_f7;
  
  tmp_i6 = 0;
  tmp_i3 = *pm;
  tmp_pi5 = (int *)(ammoTableMP + 0x24);
  do {
    if (tmp_pi5[-1] != 0) {
      tmp_i3 = COM_BitCheck(tmp_i3 + 0x3d4,tmp_i6);
      tmp_pi2 = pm;
      if (tmp_i3 == 0) {
        tmp_i3 = *pm;
      }
      else {
        tmp_i3 = *pm;
        tmp_i4 = tmp_i3 + tmp_i6 * 4;
        tmp_i1 = *(int *)(tmp_i4 + 0x49c);
        if (tmp_i1 != 0) {
          if (((*(byte *)(pm + 0x4e) & 4) == 0) || (tmp_pi5[4] == 0)) {
            tmp_f7 = (float)*tmp_pi5;
          }
          else {
            tmp_f7 = (float)*tmp_pi5 * 1.5;
          }
          *(int *)(tmp_i4 + 0x49c) = (int)ROUND((float)tmp_i1 - tmp_f7 * g_unk_00f3e304);
          tmp_i3 = *tmp_pi2;
          tmp_i4 = tmp_i6 * 4 + tmp_i3;
          if (*(int *)(tmp_i4 + 0x49c) < 0) {
            *(uint32_t *)(tmp_i4 + 0x49c) = 0;
            tmp_i3 = *tmp_pi2;
          }
        }
      }
    }
    tmp_pi5 = tmp_pi5 + 0x12;
    tmp_i6 = tmp_i6 + 1;
  } while (tmp_i6 != 0x34);
  tmp_i6 = *(int *)(tmp_i3 + 0xa4);
  if (tmp_i6 != 0) {
    if ((*(int *)(tmp_i3 + 0x140) == 0) && ((*(byte *)(tmp_i3 + 0x69) & 0x80) == 0)) {
      if (*(int *)(ammoTableMP + tmp_i6 * 0x48 + 0x20) == 0) {
        *(uint32_t *)(tmp_i3 + 0x59c) = 0;
        return;
      }
      tmp_f7 = (float)*(int *)(tmp_i3 + 0x49c + tmp_i6 * 4) /
              (float)*(int *)(ammoTableMP + tmp_i6 * 0x48 + 0x20);
    }
    else {
      tmp_f7 = (float)*(int *)(tmp_i3 + 0x51c) / 1500.0;
    }
    tmp_f7 = floorf(tmp_f7 * 255.0);
    *(int *)(tmp_i3 + 0x59c) = (int)ROUND(tmp_f7);
    return;
  }
  return;
}

void PM_AdjustAimSpreadScale(void)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int *tmp_pi4;
  uint tmp_u5;
  uint tmp_u6;
  int tmp_i7;
  int tmp_i8;
  long double tmp_l9;
  float local_50;
  float local_44;
  
  tmp_pi4 = pm;
  tmp_i7 = *pm;
  if ((*(byte *)(tmp_i7 + 0x6a) & 4) != 0) {
    *(uint32_t *)(tmp_i7 + 0x48c) = 0xff;
    *(uint32_t *)(*tmp_pi4 + 0x488) = 0x437f0000;
    return;
  }
  tmp_i8 = *(int *)(tmp_i7 + 0xa4);
  switch(tmp_i8) {
  default:
    tmp_f1 = *(float *)(BG_Weapons + tmp_i8 * 0x6b0 + 0x6a0);
    if (tmp_f1 == 0.0) {
      tmp_f1 = -200.0;
      goto LAB_0002a3cf;
    }
    goto LAB_0002a459;
  case 2:
  case 7:
  case 0xe:
  case 0x22:
  case 0x23:
  case 0x26:
  case 0x2c:
  case 0x2d:
    local_50 = 0.4;
    break;
  case 3:
  case 8:
  case 10:
  case 0x1f:
    local_50 = 0.6;
    break;
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x1e:
    local_50 = 0.5;
    break;
  case 0x1d:
  case 0x2e:
    local_50 = 0.9;
    break;
  case 0x27:
  case 0x28:
  case 0x29:
    if ((*(byte *)(pm + 0x4f) & 8) == 0) {
      local_50 = 10.0;
    }
    else {
      local_50 = 5.0;
    }
  }
  tmp_f1 = *(float *)(BG_Weapons + tmp_i8 * 0x6b0 + 0x6a0);
  if (tmp_f1 != 0.0) {
LAB_0002a459:
    local_50 = tmp_f1;
  }
  if ((*(uint *)(tmp_i7 + 0x68) & 0x80010) != 0) {
    local_50 = local_50 * 0.5;
  }
  tmp_i8 = 0;
  tmp_f3 = (float)(pm[3] - pm[10]) / 1000.0;
  tmp_f1 = *(float *)(tmp_i7 + 0x20);
  tmp_f2 = *(float *)(tmp_i7 + 0x24);
  local_44 = 0.0;
  while( true ) {
    tmp_u5 = AngleNormalizeInt(pm[tmp_i8 + 0xc]);
    tmp_u6 = AngleNormalizeInt(pm[tmp_i8 + 5]);
    tmp_l9 = (long double)AngleSubtract((float)tmp_u6 * 0.005493164,(float)tmp_u5 * 0.005493164);
    local_44 = (float)(ABS(tmp_l9) + (long double)local_44);
    if (tmp_i8 == 1) break;
    tmp_i8 = 1;
  }
  tmp_i8 = BG_IsScopedWeapon(*(uint32_t *)(*pm + 0xa4));
  tmp_i7 = *(int *)(*pm + 0xa4);
  if (tmp_i8 == 0) {
    if (*(int *)(BG_Weapons + tmp_i7 * 0x6b0 + 0x6a4) == 1) goto LAB_0002a57a;
LAB_0002a66c:
    tmp_f1 = 0.0;
  }
  else {
    if (*(int *)(BG_Weapons + tmp_i7 * 0x6b0 + 0x6a4) == 2) goto LAB_0002a66c;
LAB_0002a57a:
    tmp_f1 = ABS(tmp_f2) + ABS(tmp_f1) + 0.0 + 0.0;
  }
  tmp_i8 = BG_IsScopedWeapon(tmp_i7);
  tmp_i7 = *pm;
  if (tmp_i8 == 0) {
    if (*(int *)(BG_Weapons + *(int *)(tmp_i7 + 0xa4) * 0x6b0 + 0x6a8) != 2) goto LAB_0002a6e8;
  }
  else if (*(int *)(BG_Weapons + *(int *)(tmp_i7 + 0xa4) * 0x6b0 + 0x6a8) == 1) {
LAB_0002a6e8:
    tmp_f1 = tmp_f1 + local_44;
  }
  tmp_f1 = tmp_f1 / tmp_f3 - 30.0 / local_50;
  tmp_f2 = 120.0 / local_50;
  if (tmp_f1 <= 0.0) {
    tmp_f1 = 0.0;
  }
  else if (tmp_f2 < tmp_f1) {
    tmp_f1 = tmp_f2;
  }
  tmp_f1 = (float)(int)ROUND((tmp_f1 / tmp_f2) * tmp_f3 * 800.0) - (tmp_f3 * 200.0) / local_50;
LAB_0002a3cf:
  tmp_pi4 = pm;
  *(float *)(tmp_i7 + 0x488) = tmp_f1 + *(float *)(tmp_i7 + 0x488);
  nitrox_ClampFloat(*tmp_pi4 + 0x488,0,0x437f0000);
  *(int *)(*pm + 0x48c) = (int)ROUND(*(float *)(*pm + 0x488));
  return;
}

uint PM_AltFire(void)
{
  int tmp_i1;
  int tmp_i2;
  
  if (((((*(byte *)((int)pm + 0x11) & 1) != 0) && (tmp_i1 = *pm, 0 < *(int *)(tmp_i1 + 0xd0))) &&
      (*(int *)(tmp_i1 + 0xa4) == 1)) &&
     (tmp_i2 = BG_FindClipForWeapon(1), *(uint *)(tmp_i1 + (tmp_i2 + 0xa4) * 4) >> 1 != 0)) {
    return (uint)pm[0x4d] >> 5 & 1;
  }
  return 0;
}

void PM_Weapon(void)
{
  int *tmp_pi1;
  float tmp_f2;
  float tmp_f3;
  byte tmp_b4;
  byte tmp_b5;
  int tmp_i6;
  uint tmp_u7;
  void *tmp_pc8;
  bool tmp_b9;
  int *tmp_pi10;
  int tmp_i11;
  int tmp_i12;
  uint32_t tmp_u13;
  int tmp_i14;
  uint tmp_u15;
  uint8_t **tmp_ppu16;
  double *pdVar17;
  int tmp_i18;
  int tmp_i19;
  int tmp_i20;
  uint8_t *tmp_pu21;
  uint16_t inreg_FPUControlWord;
  double tmp_d22;
  double tmp_d23;
  float tmp_f24;
  uint32_t local_f0;
  float local_b4;
  float local_b0;
  float local_a0;
  float local_50;
  
  tmp_pi10 = pm;
  pdVar17 = (double *)&stack0xffffff14;
  tmp_ppu16 = &_GLOBAL_OFFSET_TABLE_;
  tmp_i20 = *pm;
  if ((*(uint *)(tmp_i20 + 0xc) & 0x200) != 0) {
    return;
  }
  if (*(int *)(tmp_i20 + 300) == 3) {
    return;
  }
  if ((*(int *)(tmp_i20 + 0xd0) < 1) || ((*(uint *)(tmp_i20 + 0x68) & 0x800000) != 0)) {
    if ((*(uint *)(tmp_i20 + 0xc) & 0x4000) != 0) {
      return;
    }
    local_f0 = 0x2a82d;
    PM_CoolWeapons();
    return;
  }
  if (*(int *)(tmp_i20 + 0x140) == 1) {
    if (*(int *)(tmp_i20 + 0x51c) != 0) {
      *(int *)(tmp_i20 + 0x51c) = (int)ROUND((float)*(int *)(tmp_i20 + 0x51c) - g_unk_00f3e304 * 300.0);
      tmp_i20 = *tmp_pi10;
      tmp_i12 = *(int *)(tmp_i20 + 0x51c);
      if (tmp_i12 < 0) {
        *(uint32_t *)(tmp_i20 + 0x51c) = 0;
        tmp_i20 = *tmp_pi10;
        tmp_i12 = *(int *)(tmp_i20 + 0x51c);
      }
      local_f0 = 0x2aa78;
      tmp_f24 = floorf(((float)tmp_i12 / 1500.0) * 255.0);
      *(int *)(tmp_i20 + 0x59c) = (int)ROUND(tmp_f24);
      tmp_i20 = *tmp_pi10;
    }
    if (*(int *)(tmp_i20 + 0x2c) < 1) {
      if ((*(byte *)(tmp_pi10 + 4) & 1) == 0) {
        return;
      }
    }
    else {
      *(int *)(tmp_i20 + 0x2c) = *(int *)(tmp_i20 + 0x2c) - g_unk_00f3e308;
      tmp_i20 = *tmp_pi10;
      if (0 < *(int *)(tmp_i20 + 0x2c)) {
        return;
      }
      if ((*(byte *)(tmp_pi10 + 4) & 1) == 0) {
LAB_0002b5f5:
        *(uint32_t *)(tmp_i20 + 0x2c) = 0;
        return;
      }
    }
    *(int *)(tmp_i20 + 0x51c) = *(int *)(tmp_i20 + 0x51c) + 0x42;
    local_f0 = 0x2aaed;
    BG_AddPredictableEventToPlayerstate();
    *(int *)(*pm + 0x2c) = *(int *)(*pm + 0x2c) + 0x42;
    local_f0 = 0x2ab21;
    BG_AnimScriptEvent();
    tmp_pi10 = pm;
    *(uint32_t *)(*pm + 0x410) = 2;
LAB_0002a977:
    if ((float)*(int *)(*tmp_pi10 + 0x51c) < 1500.0) {
      return;
    }
    *(uint32_t *)(*tmp_pi10 + 0x2c) = 0x5dc;
    local_f0 = 0x2a9b0;
    BG_AddPredictableEventToPlayerstate();
    *(uint32_t *)(*pm + 0x2c) = 2000;
    return;
  }
  if (*(int *)(tmp_i20 + 0x140) == 2) {
    if (*(int *)(tmp_i20 + 0x2c) < 1) {
      return;
    }
    *(int *)(tmp_i20 + 0x2c) = *(int *)(tmp_i20 + 0x2c) - g_unk_00f3e308;
    if (0 < *(int *)(*tmp_pi10 + 0x2c)) {
      return;
    }
    if ((*(byte *)(tmp_pi10 + 4) & 1) != 0) {
      return;
    }
    *(uint32_t *)(*tmp_pi10 + 0x2c) = 0;
    return;
  }
  if ((*(uint *)(tmp_i20 + 0x68) & 0x8000) != 0) {
    if (*(int *)(tmp_i20 + 0x51c) != 0) {
      *(int *)(tmp_i20 + 0x51c) = (int)ROUND((float)*(int *)(tmp_i20 + 0x51c) - g_unk_00f3e304 * 300.0);
      tmp_i20 = *tmp_pi10;
      tmp_i12 = *(int *)(tmp_i20 + 0x51c);
      if (tmp_i12 < 0) {
        *(uint32_t *)(tmp_i20 + 0x51c) = 0;
        tmp_i20 = *tmp_pi10;
        tmp_i12 = *(int *)(tmp_i20 + 0x51c);
      }
      local_f0 = 0x2a8c8;
      tmp_f24 = floorf(((float)tmp_i12 / 1500.0) * 255.0);
      *(int *)(tmp_i20 + 0x59c) = (int)ROUND(tmp_f24);
      tmp_i20 = *tmp_pi10;
    }
    if (*(int *)(tmp_i20 + 0x2c) < 1) {
      if ((*(byte *)(tmp_pi10 + 4) & 1) == 0) {
        return;
      }
    }
    else {
      *(int *)(tmp_i20 + 0x2c) = *(int *)(tmp_i20 + 0x2c) - g_unk_00f3e308;
      tmp_i20 = *tmp_pi10;
      if (0 < *(int *)(tmp_i20 + 0x2c)) {
        return;
      }
      if ((*(byte *)(tmp_pi10 + 4) & 1) == 0) goto LAB_0002b5f5;
    }
    *(int *)(tmp_i20 + 0x51c) = *(int *)(tmp_i20 + 0x51c) + 0x42;
    local_f0 = 0x2a93b;
    BG_AddPredictableEventToPlayerstate();
    *(int *)(*pm + 0x2c) = *(int *)(*pm + 0x2c) + 0x42;
    local_f0 = 0x2a971;
    BG_AnimScriptEvent();
    tmp_pi10 = pm;
    goto LAB_0002a977;
  }
  pm[0x40] = 0;
  if ((*(int *)(tmp_i20 + 0xa4) - 0x2cU < 2) || (*(int *)(tmp_i20 + 0xa4) - 0x22U < 2)) {
    local_f0 = 0x2b3c8;
    BG_AkimboSidearm();
    local_f0 = 0x2b3d0;
    BG_FindClipForWeapon();
    local_f0 = 0x2b3ee;
    BG_FindClipForWeapon();
    local_f0 = 0x2b414;
    BG_AkimboFireSequence();
  }
  local_f0 = 0x2ab71;
  PM_CoolWeapons();
  tmp_pi10 = pm;
  tmp_i20 = pm[1];
  if (*(int *)(tmp_i20 + 0x48) != 0) {
    tmp_i12 = pm[3];
    tmp_i14 = tmp_i12 - *(int *)(tmp_i20 + 0x48);
    tmp_i11 = *pm;
    local_b0 = *(float *)(tmp_i11 + 0xb0);
    local_b4 = *(float *)(tmp_i11 + 0xb4);
    tmp_f24 = *(float *)(tmp_i11 + 0xb8);
    tmp_i6 = *(int *)(tmp_i20 + 0x4c);
    tmp_i18 = *(int *)(tmp_i20 + 0x58);
    if (tmp_i6 < tmp_i14) {
      tmp_i14 = tmp_i6;
    }
    local_50 = local_b4;
    if (tmp_i18 < tmp_i14) {
      tmp_f2 = *(float *)(tmp_i20 + 0x54);
      tmp_i19 = tmp_i18 * 3;
      tmp_f3 = *(float *)(tmp_i20 + 0x50);
      local_a0 = local_b4;
      do {
        if (0.0 < tmp_f2) {
          local_f0 = 0x2ac2e;
          tmp_d22 = cos((double)(((float)tmp_i18 * 2.5) / (float)tmp_i6));
          local_f0 = 0x2ac3e;
          tmp_d23 = cos((double)tmp_i12);
          local_b0 = (local_b0 - (float)tmp_d22 * (tmp_f2 + tmp_f2)) -
                     (1.0 - (float)(tmp_i18 / tmp_i6)) * ABS((float)tmp_d23) * 0.25;
        }
        if (0.0 < tmp_f3) {
          local_f0 = 0x2aca4;
          tmp_d22 = cos(1.0 - (double)(tmp_i19 / tmp_i6));
          local_f0 = 0x2acb4;
          tmp_d23 = cos((double)tmp_i12);
          local_b4 = (1.0 - (float)(tmp_i18 / tmp_i6)) * (float)tmp_d23 * 0.5 +
                     tmp_f3 * 0.5 * (float)tmp_d22 + local_b4;
          local_a0 = local_b4;
        }
        tmp_i18 = tmp_i18 + 0xf;
        tmp_i19 = tmp_i19 + 0x2d;
      } while (tmp_i18 < tmp_i14);
      local_50 = local_a0;
    }
    *(uint *)(tmp_i11 + 0x44) = ((int)ROUND((local_b0 * 65536.0) / 360.0) & 0xffffU) - tmp_pi10[5];
    *(uint *)(*tmp_pi10 + 0x48) = ((int)ROUND((local_50 * 65536.0) / 360.0) & 0xffffU) - tmp_pi10[6];
    *(uint *)(*tmp_pi10 + 0x4c) = ((int)ROUND((tmp_f24 * 65536.0) / 360.0) & 0xffffU) - tmp_pi10[7];
    *(float *)(*tmp_pi10 + 0xb0) = local_b0;
    *(float *)(*tmp_pi10 + 0xb4) = local_b4;
    *(float *)(*tmp_pi10 + 0xb8) = tmp_f24;
    tmp_i20 = tmp_pi10[1];
    if (*(int *)(tmp_i20 + 0x4c) == tmp_i14) {
      *(uint32_t *)(tmp_i20 + 0x48) = 0;
      *(uint32_t *)(tmp_pi10[1] + 0x58) = 0;
    }
    else {
      *(int *)(tmp_i20 + 0x58) = tmp_i14;
    }
  }
  local_f0 = 0x2ae24;
  BG_ClearConditionBitFlag();
  tmp_pi10 = pm;
  tmp_i12 = *pm;
  tmp_i20 = *(int *)(tmp_i12 + 0xa4);
  switch(tmp_i20) {
  default:
_L911:
    tmp_i11 = *(int *)(tmp_i12 + 0x30);
    break;
  case 1:
  case 4:
  case 9:
  case 0xf:
  case 0x1c:
  case 0x30:
  case 0x32:
    tmp_i11 = *(int *)(tmp_i12 + 0x34);
    if (tmp_i11 < 1) goto _L911;
    if (tmp_i20 == 1) {
      tmp_b9 = false;
      *(int *)(tmp_i12 + 0x34) = tmp_i11 + g_unk_00f3e308;
      tmp_i12 = *tmp_pi10;
      if (500 < *(int *)(tmp_i12 + 0x34)) {
        *(uint32_t *)(tmp_i12 + 0x34) = 500;
        tmp_i12 = *tmp_pi10;
      }
    }
    else if (tmp_i20 == 0xf) {
      tmp_b9 = false;
      *(int *)(tmp_i12 + 0x34) = tmp_i11 + g_unk_00f3e308;
      tmp_i12 = *tmp_pi10;
      if (*(int *)(tmp_i12 + 0x34) < 5000) {
        *(uint32_t *)(tmp_i12 + 0x34) = 5000;
        tmp_i12 = *tmp_pi10;
      }
    }
    else {
      tmp_b9 = false;
      *(int *)(tmp_i12 + 0x34) = tmp_i11 - g_unk_00f3e308;
      tmp_i12 = *tmp_pi10;
      if (*(int *)(tmp_i12 + 0x34) < 0x65) {
        *(uint32_t *)(tmp_i12 + 0x34) = 100;
        tmp_b9 = true;
        tmp_i12 = *tmp_pi10;
      }
    }
    if (*(int *)(tmp_i12 + 0x394) != 0) {
      *(byte *)(tmp_pi10 + 4) = *(byte *)(tmp_pi10 + 4) & 0xfe;
      *(byte *)((int)tmp_pi10 + 0x11) = *(byte *)((int)tmp_pi10 + 0x11) & 0xfe;
    }
    tmp_i20 = *(int *)(tmp_i12 + 0xa4);
    if (tmp_i20 == 1) {
      if (((*(byte *)((int)tmp_pi10 + 0x11) & 1) != 0) && ((*(byte *)(tmp_i12 + 0x6a) & 0x10) == 0))
      goto LAB_0002aed6;
      tmp_i11 = *(int *)(tmp_i12 + 0x30);
      if (tmp_i11 == GHIDRA_FIELD(ammoTableMP, 96, 4)) {
        local_f0 = 0x2b597;
        PM_StartWeaponAnim();
        local_f0 = 0x2b5d3;
        BG_AnimScriptEvent();
        goto LAB_0002b49a;
      }
    }
    else {
      if (((!tmp_b9) && ((*(byte *)(tmp_pi10 + 4) & 1) != 0)) &&
         ((*(byte *)(tmp_i12 + 0x6a) & 0x10) == 0)) {
        if (tmp_i20 == 0xf) {
          return;
        }
LAB_0002aed6:
        local_f0 = 0x2aef3;
        BG_SetConditionBitFlag();
        return;
      }
      tmp_i11 = *(int *)(tmp_i12 + 0x30);
      if ((tmp_b9) || (tmp_i11 == *(int *)(ammoTableMP + tmp_i20 * 0x48 + 0x18))) {
        if (((tmp_i20 != 0xf) && ((*(int *)(tmp_i12 + 4) < 3 && (*(int *)(tmp_pi10[1] + 8) < 1)))) &&
           (*(char *)((int)tmp_pi10 + 0x12) != '\0')) {
          *(uint *)(tmp_i12 + 0x480) = ~*(uint *)(tmp_i12 + 0x480) & 0x200 | 3;
        }
        local_f0 = 0x2b49a;
        BG_AnimScriptEvent();
LAB_0002b49a:
        tmp_pi10 = pm;
        *(uint32_t *)(*pm + 0x394) = 1;
        tmp_i12 = *tmp_pi10;
        tmp_i11 = *(int *)(tmp_i12 + 0x30);
      }
    }
  }
  if (tmp_i11 < 1) {
LAB_0002af1f:
    if ((*(byte *)(tmp_i12 + 0x6a) & 0x10) != 0) {
      return;
    }
    tmp_i20 = 0;
  }
  else {
    *(int *)(tmp_i12 + 0x30) = tmp_i11 - g_unk_00f3e308;
    tmp_i12 = *tmp_pi10;
    if (0 < *(int *)(tmp_i12 + 0x30)) goto LAB_0002af1f;
    *(uint32_t *)(tmp_i12 + 0x30) = 0;
    tmp_i20 = 1;
    tmp_i12 = *tmp_pi10;
  }
  if (*(int *)(tmp_i12 + 0x2c) < 1) {
LAB_0002b4b7:
    if ((tmp_i20 == 0) && (*(uint *)(tmp_i12 + 0xa4) != (uint)*(byte *)((int)tmp_pi10 + 0x12))) {
LAB_0002afea:
      local_f0 = 0x2affc;
      PM_BeginWeaponChange();
      tmp_i12 = *pm;
      tmp_pi10 = pm;
    }
LAB_0002b010:
    if (0 < *(int *)(tmp_i12 + 0x30)) {
      return;
    }
LAB_0002b01b:
    if (0 < *(int *)(tmp_i12 + 0xd0)) goto LAB_0002b029;
    tmp_i12 = *(int *)(tmp_i12 + 0x2c);
  }
  else {
    *(int *)(tmp_i12 + 0x2c) = *(int *)(tmp_i12 + 0x2c) - g_unk_00f3e308;
    if ((*(byte *)(tmp_pi10 + 4) & 1) == 0) {
      if ((((*(byte *)((int)tmp_pi10 + 0x11) & 1) != 0) &&
          (tmp_i12 = *tmp_pi10, 0 < *(int *)(tmp_i12 + 0xd0))) && (*(int *)(tmp_i12 + 0xa4) == 1)) {
        local_f0 = 0x2b6d6;
        tmp_i11 = BG_FindClipForWeapon();
        tmp_pi10 = pm;
        if ((*(uint *)(tmp_i12 + (tmp_i11 + 0xa4) * 4) >> 1 != 0) &&
           ((*(byte *)(pm + 0x4d) & 0x20) != 0)) goto LAB_0002af55;
      }
      tmp_i12 = *tmp_pi10;
      if (*(int *)(tmp_i12 + 0x2c) < 0) {
        *(uint32_t *)(tmp_i12 + 0x2c) = 0;
        goto LAB_0002af55;
      }
    }
    else {
LAB_0002af55:
      tmp_i12 = *tmp_pi10;
    }
    tmp_i11 = *(int *)(tmp_i12 + 0xa4);
    switch(tmp_i11) {
    case 2:
    case 7:
    case 0xe:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x1e:
    case 0x22:
    case 0x23:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x2c:
    case 0x2d:
      if (*(int *)(tmp_pi10[1] + 0x5c) == 0) {
        if ((*(byte *)(tmp_pi10 + 4) & 1) == 0) {
          *(uint32_t *)(tmp_pi10[1] + 0x5c) = 1;
          tmp_i12 = *tmp_pi10;
        }
      }
      else if ((*(byte *)(tmp_pi10 + 4) & 1) != 0) {
        if ((tmp_i11 - 0x2cU < 2) || (tmp_i11 - 0x22U < 2)) {
          if (*(int *)(tmp_i12 + 0x2c) < 0x33) goto LAB_0002afa2;
        }
        else if (*(int *)(tmp_i12 + 0x2c) < 0x97) {
LAB_0002afa2:
          *(uint32_t *)(tmp_i12 + 0x2c) = 0;
          tmp_i12 = *tmp_pi10;
        }
      }
    }
    if (*(int *)(tmp_i12 + 0x2c) < 1) goto LAB_0002b4b7;
    if (*(int *)(tmp_i12 + 0xa8) - 5U < 2) goto LAB_0002b010;
    if (0 < *(int *)(tmp_i12 + 0x30)) {
      return;
    }
    if (tmp_i20 == 0) {
      if (*(uint *)(tmp_i12 + 0xa4) != (uint)*(byte *)((int)tmp_pi10 + 0x12)) goto LAB_0002afea;
      goto LAB_0002b01b;
    }
    if (*(int *)(tmp_i12 + 0xd0) < 1) {
      return;
    }
LAB_0002b029:
    local_f0 = 0x2b037;
    PM_CheckForReload();
    if (0 < *(int *)(*pm + 0x2c)) {
      return;
    }
    tmp_i12 = *(int *)(*pm + 0x30);
    tmp_pi10 = pm;
  }
  if (0 < tmp_i12) {
    return;
  }
  *(uint32_t *)(tmp_pi10[1] + 0x78) = 0;
  tmp_i12 = *tmp_pi10;
  switch(*(uint32_t *)(tmp_i12 + 0xa8)) {
  case 1:
    *(uint32_t *)(tmp_i12 + 0xa8) = 0;
    goto LAB_0002b26b;
  case 2:
    *(uint32_t *)(tmp_i12 + 0xa8) = 0;
    local_f0 = 0x2b232;
    PM_BeginWeaponReload();
    return;
  case 3:
  case 4:
    tmp_u15 = *(uint *)(tmp_i12 + 0x41c);
    if (0x33 < tmp_u15) {
      tmp_u15 = 0;
    }
    local_f0 = 0x2b297;
    tmp_i12 = COM_BitCheck();
    tmp_pi10 = pm;
    tmp_i20 = *pm;
    tmp_u7 = *(uint *)(tmp_i20 + 0xa4);
    if (tmp_i12 == 0) {
      *(uint32_t *)(tmp_i20 + 0xa4) = 0;
      tmp_i20 = *tmp_pi10;
      if (*(int *)(tmp_i20 + 0xa8) != 4) {
        tmp_u15 = 0;
        goto LAB_0002b2c8;
      }
      *(uint32_t *)(tmp_i20 + 0xa8) = 2;
      if (tmp_u7 == 0) {
        return;
      }
      tmp_i20 = 0xfa;
      goto LAB_0002b322;
    }
    *(uint *)(tmp_i20 + 0xa4) = tmp_u15;
    tmp_i20 = *tmp_pi10;
    if (*(int *)(tmp_i20 + 0xa8) == 4) {
      tmp_u13 = 2;
    }
    else {
LAB_0002b2c8:
      tmp_u13 = 1;
    }
    *(uint32_t *)(tmp_i20 + 0xa8) = tmp_u13;
    if (tmp_u15 == 0x17) {
LAB_0002b2ff:
      *(uint *)(tmp_pi10[1] + 0xc) = *(uint *)(tmp_pi10[1] + 0xc) & 0xfffffffd;
      if (tmp_u7 == tmp_u15) {
        return;
      }
LAB_0002b30e:
      tmp_i20 = 0xfa;
      if (tmp_u15 == *(uint *)(weapAlts + tmp_u7 * 4)) {
        tmp_i20 = *tmp_pi10;
        local_f0 = 0x2bd4b;
        tmp_i12 = BG_FindAmmoForWeapon();
        if (*(int *)(tmp_i20 + (tmp_i12 + 0xa4) * 4) == 0) {
          local_f0 = 0x2bde3;
          BG_UpdateConditionValue();
          return;
        }
        tmp_i20 = 0x543;
        tmp_pi10 = pm;
        goto LAB_0002ba9d;
      }
LAB_0002b322:
      *(int *)(*tmp_pi10 + 0x2c) = *(int *)(*tmp_pi10 + 0x2c) + tmp_i20;
      local_f0 = 0x2b34f;
      BG_UpdateConditionValue();
    }
    else {
      if ((int)tmp_u15 < 0x18) {
        if (tmp_u15 != 7) {
          if ((int)tmp_u15 < 8) {
            if (tmp_u15 == 2) goto LAB_0002ba7d;
          }
          else {
            if (tmp_u15 == 0xe) goto LAB_0002bbc5;
            if (tmp_u15 == 0x16) goto LAB_0002b2ff;
          }
          goto LAB_0002b761;
        }
LAB_0002ba7d:
        *(uint *)(tmp_pi10[1] + 0xc) = *(uint *)(tmp_pi10[1] + 0xc) & 0xfffffffe;
        if (tmp_u7 == tmp_u15) {
          return;
        }
LAB_0002ba8c:
        if (tmp_u15 != *(uint *)(weapAlts + tmp_u7 * 4)) goto LAB_0002b964;
        tmp_i20 = 0;
        goto LAB_0002ba9d;
      }
      if (tmp_u15 == 0x26) {
LAB_0002bbc5:
        *(uint *)(tmp_pi10[1] + 0xc) = *(uint *)(tmp_pi10[1] + 0xc) | 1;
        if (tmp_u7 == tmp_u15) {
          return;
        }
        goto LAB_0002bbd4;
      }
      if ((int)tmp_u15 < 0x27) {
        if ((tmp_u15 != 0x24) && (tmp_u15 != 0x25)) goto LAB_0002b761;
        *(uint *)(tmp_pi10[1] + 0xc) = *(uint *)(tmp_pi10[1] + 0xc) | 2;
        if (tmp_u7 == tmp_u15) {
          return;
        }
LAB_0002b955:
        if (tmp_u15 != *(uint *)(weapAlts + tmp_u7 * 4)) goto LAB_0002b964;
        tmp_i20 = 0x92e;
        goto LAB_0002ba9d;
      }
      if ((int)tmp_u15 < 0x2a) {
        *(uint32_t *)(*tmp_pi10 + 0x48c) = 0xff;
        *(uint32_t *)(*tmp_pi10 + 0x488) = 0x437f0000;
      }
LAB_0002b761:
      if ((tmp_u15 == tmp_u7) && (tmp_u15 = tmp_u7, tmp_u7 != 0x1c)) {
        if ((int)tmp_u7 < 0x1d) {
          if (tmp_u7 != 1) {
            return;
          }
        }
        else if ((tmp_u7 != 0x30) && (tmp_u7 != 0x32)) {
          return;
        }
      }
      if (tmp_u15 == 0x1f) {
LAB_0002bbaa:
        tmp_i20 = 0x32;
        if (tmp_u15 != *(uint *)(weapAlts + tmp_u7 * 4)) {
          tmp_i20 = 0xfa;
        }
        goto LAB_0002b322;
      }
      if ((int)tmp_u15 < 0x20) {
        if (tmp_u15 != 0xe) {
          if ((int)tmp_u15 < 0xf) {
            if ((tmp_u15 == 2) || (tmp_u15 == 7)) goto LAB_0002ba8c;
          }
          else if (0x15 < (int)tmp_u15) {
            if ((int)tmp_u15 < 0x18) goto LAB_0002b30e;
            if (tmp_u15 == 0x1d) {
              tmp_i20 = 0xfa;
              if (*(int *)(weapAlts + tmp_u7 * 4) == 0x1d) {
                tmp_i20 = 0x6ba;
              }
              goto LAB_0002b322;
            }
          }
          goto LAB_0002bb56;
        }
LAB_0002bbd4:
        if (tmp_u15 != *(uint *)(weapAlts + tmp_u7 * 4)) {
LAB_0002b964:
          tmp_i20 = 0xfa;
          goto LAB_0002b322;
        }
        tmp_i20 = 0x4a6;
      }
      else {
        if (tmp_u15 == 0x26) goto LAB_0002bbd4;
        if (0x26 < (int)tmp_u15) {
          if (tmp_u15 != 0x2a) {
            if (tmp_u15 == 0x2e) {
              tmp_i20 = 0xfa;
              if (*(int *)(weapAlts + tmp_u7 * 4) == 0x2e) {
                tmp_i20 = 0x4e2;
              }
              goto LAB_0002b322;
            }
            if (tmp_u15 == 0x29) goto LAB_0002bbaa;
LAB_0002bb56:
            tmp_i20 = 0xfa;
            goto LAB_0002b322;
          }
          if (*(int *)(weapAlts + tmp_u7 * 4) == 0x2a) {
            tmp_i20 = 0x683;
            goto LAB_0002ba9d;
          }
          goto LAB_0002b964;
        }
        if (tmp_u15 != 0x21) {
          if ((0x20 < (int)tmp_u15) && (0x23 < (int)tmp_u15)) goto LAB_0002b955;
          goto LAB_0002bb56;
        }
        if (*(int *)(weapAlts + tmp_u7 * 4) != 0x21) goto LAB_0002b964;
        tmp_i20 = 1000;
      }
LAB_0002ba9d:
      *(int *)(*tmp_pi10 + 0x2c) = *(int *)(*tmp_pi10 + 0x2c) + tmp_i20;
      local_f0 = 0x2baca;
      BG_UpdateConditionValue();
    }
    local_f0 = 0x2b396;
    BG_AnimScriptEvent();
LAB_0002b26b:
    local_f0 = 0x2b270;
    PM_StartWeaponAnim();
    return;
  case 7:
    pdVar17 = (double *)&local_f0;
    local_f0 = 0x2b0c3;
    PM_ReloadClip();
    *(uint32_t *)(**(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f)) + 0xa8) = 0;
    PM_StartWeaponAnim();
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
  }
  if ((*(byte *)(tmp_pi10 + 4) & 1) == 0) {
    tmp_i12 = *tmp_pi10;
    tmp_i11 = *(int *)(tmp_i12 + 0xa4);
    if (tmp_i11 == 0x21) {
      return;
    }
    if (tmp_i11 < 0x22) {
LAB_0002b6ff:
      if (tmp_i11 == 0) {
        return;
      }
      if ((tmp_i11 == 5) && ((*(byte *)(tmp_i12 + 0x6a) & 8) != 0)) {
        return;
      }
      goto LAB_0002b140;
    }
    if (tmp_i11 == 0x2b) {
LAB_0002bb86:
      if (*(uint *)(tmp_i12 + 0xe4) < 5) {
        switch(tmp_ppu16[*(int *)(tmp_i12 + 0xe4) + -0xb87a] + (int)tmp_ppu16) {
        case (uint8_t *)0x2bc1c:
          if (tmp_pi10[3] - *(int *)(tmp_i12 + 0x478) < tmp_pi10[0x14]) {
            return;
          }
          break;
        case (uint8_t *)0x2bc33:
          if (tmp_pi10[3] - *(int *)(tmp_i12 + 0x478) < tmp_pi10[0x16]) {
            return;
          }
          break;
        case (uint8_t *)0x2bc4a:
          if (tmp_pi10[3] - *(int *)(tmp_i12 + 0x478) < tmp_pi10[0x17]) {
            return;
          }
          break;
        case (uint8_t *)0x2bc61:
          if (tmp_pi10[3] - *(int *)(tmp_i12 + 0x478) < tmp_pi10[0x15]) {
            return;
          }
          break;
        case (uint8_t *)0x2bc78:
          if (tmp_pi10[3] - *(int *)(tmp_i12 + 0x478) < tmp_pi10[0x18]) {
            return;
          }
        }
      }
      goto LAB_0002b140;
    }
    if (tmp_i11 != 0x31) {
LAB_0002b137:
      if ((tmp_i11 == 0x2a) && (tmp_i20 == 0)) {
        *(uint32_t *)(tmp_i12 + 0xa8) = 0;
      }
      goto LAB_0002b140;
    }
LAB_0002b850:
    tmp_b4 = cgs[(int)tmp_ppu16 + 0x1efb225];
    *(uint8_t ***)((int)pdVar17 + 0x34) = tmp_ppu16 + 0x3ec887;
    if ((tmp_b4 & 1) != 0) goto LAB_0002b886;
LAB_0002b863:
    *(uint32_t *)((int)pdVar17 + -4) = 0x2b868;
    tmp_i12 = PM_AltFire();
    if ((tmp_i12 == 0) && (*(char *)(pdVar17 + 6) != '\0')) {
LAB_0002b87b:
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      goto LAB_0002b1e4;
    }
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
LAB_0002b8a7:
    tmp_i12 = *tmp_pi10;
    if (((*(float *)(tmp_i12 + 0x3c) != 0.0) &&
        ((*(int *)(tmp_i12 + 0xa8) != 6 ||
         (((*(char *)((int)pdVar17 + 0x2c) == '\0' && (*(int *)(tmp_i12 + 0x30) < 1)) ||
          (*(int *)(tmp_i12 + 0xa4) != 1)))))) &&
       ((tmp_u15 = *(uint *)(tmp_i12 + 0xa4), (tmp_u15 != 9 && tmp_u15 != 4) && tmp_u15 != 0x1c &&
        ((tmp_u15 & 0xfffffffd) != 0x30)))) {
LAB_0002b1e4:
      *(uint32_t *)(*tmp_pi10 + 0x2c) = 0;
      *(uint32_t *)(*tmp_pi10 + 0x30) = 0;
      if (*(int *)(*tmp_pi10 + 0xa8) - 5U < 2) {
        tmp_u15 = *(int *)(*tmp_pi10 + 0xa4) - 0x1b;
        if (tmp_u15 < 0x14) {
          *(uint *)(pdVar17 + 0xc) = (uint)((1 << ((byte)tmp_u15 & 0x1f) & 0x98601U) != 0);
        }
        *(int *)pdVar17 = *(int *)(pdVar17 + 0xc);
        *(uint32_t *)((int)pdVar17 + -4) = 0x2bcbf;
        PM_ContinueWeaponAnim();
        tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      }
      *(uint32_t *)(*tmp_pi10 + 0xa8) = 0;
      return;
    }
  }
  else {
    *(int **)pdVar17 = tmp_pi10;
    *(uint32_t *)((int)pdVar17 + -4) = 0x2b7c3;
    tmp_i12 = BG_CheckCharge();
    if (tmp_i12 == 0) {
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      tmp_i20 = *tmp_pi10;
      tmp_i12 = *(int *)(tmp_i20 + 0xa4);
      if ((tmp_i12 != 0xc) && (tmp_i12 != 0x12)) {
        return;
      }
      *(int *)(pdVar17 + 2) = 0;
      *(int *)((int)pdVar17 + 0xc) = 1;
      *(int *)(pdVar17 + 1) = 0x17;
      tmp_i12 = *(int *)(tmp_pi10[2] + 0x7f0);
      *(int *)pdVar17 = tmp_i20;
      *(int *)((int)pdVar17 + 4) = tmp_i12;
      *(uint32_t *)((int)pdVar17 + -4) = 0x2b810;
      BG_AnimScriptEvent();
      return;
    }
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
    tmp_i12 = *tmp_pi10;
    tmp_i11 = *(int *)(tmp_i12 + 0xa4);
    if (tmp_i11 == 0x21) {
      return;
    }
    if (tmp_i11 < 0x22) goto LAB_0002b6ff;
    if (tmp_i11 == 0x2b) goto LAB_0002bb86;
    if (tmp_i11 != 0x31) goto LAB_0002b137;
    if ((*(byte *)(tmp_pi10 + 4) & 1) == 0) goto LAB_0002b850;
    *(int *)((int)pdVar17 + 0x74) = *(int *)(tmp_i12 + 0x14);
    *(int *)(pdVar17 + 0xf) = *(int *)(*tmp_pi10 + 0x18);
    tmp_f24 = *(float *)(*tmp_pi10 + 0x1c);
    *(float *)((int)pdVar17 + 0x7c) = tmp_f24;
    tmp_i12 = *(int *)(*tmp_pi10 + 0xbc);
    *(int *)((int)pdVar17 + 0xc) = 0;
    *(int *)(pdVar17 + 1) = 0;
    *(int **)((int)pdVar17 + 4) = (int *)((int)pdVar17 + 0x8c);
    *(float *)((int)pdVar17 + 0x7c) = (float)tmp_i12 + tmp_f24;
    *(int *)pdVar17 = *tmp_pi10 + 0xb0;
    *(uint32_t *)((int)pdVar17 + -4) = 0x2be9b;
    AngleVectors();
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
    *(int *)(pdVar17 + 3) = 0x6000001;
    tmp_pu21 = tmp_ppu16[-0xb6d2];
    *(float *)(pdVar17 + 0x10) =
         *(float *)((int)pdVar17 + 0x8c) * (float)tmp_pu21 + *(float *)((int)pdVar17 + 0x74);
    *(float *)((int)pdVar17 + 0x84) =
         *(float *)(pdVar17 + 0x12) * (float)tmp_pu21 + *(float *)(pdVar17 + 0xf);
    *(float *)(pdVar17 + 0x11) =
         (float)tmp_pu21 * *(float *)((int)pdVar17 + 0x94) + *(float *)((int)pdVar17 + 0x7c);
    tmp_i12 = *(int *)(*tmp_pi10 + 0xa0);
    *(double **)(pdVar17 + 2) = pdVar17 + 0x10;
    *(int *)((int)pdVar17 + 0xc) = 0;
    *(int *)(pdVar17 + 1) = 0;
    *(int *)((int)pdVar17 + 0x14) = tmp_i12;
    *(double **)pdVar17 = pdVar17 + 0x13;
    *(int **)((int)pdVar17 + 4) = (int *)((int)pdVar17 + 0x74);
    *(double **)((int)pdVar17 + 0x34) = pdVar17 + 0x13;
    tmp_pc8 = (void *)tmp_pi10[0x46];
    *(uint32_t *)((int)pdVar17 + -4) = 0x2bf21;
    (*tmp_pc8)();
    if (*(float *)(pdVar17 + 0x14) == 1.0) {
      return;
    }
    if ((*(byte *)((int)pdVar17 + 0xc4) & 0x14) != 0) {
      return;
    }
    if (*(int *)((int)pdVar17 + 0xcc) != 0x3fe) {
      return;
    }
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
    *(int *)((int)pdVar17 + 0x74) = *(int *)((int)pdVar17 + 0xa4);
    *(int *)(pdVar17 + 3) = 0x6000001;
    *(float *)(pdVar17 + 0xf) = *(float *)(pdVar17 + 0x15);
    *(float *)((int)pdVar17 + 0x7c) = *(float *)((int)pdVar17 + 0xac);
    tmp_pu21 = tmp_ppu16[-0xb6c1];
    *(float *)(pdVar17 + 0x10) =
         *(float *)(pdVar17 + 0x16) * (float)tmp_pu21 + *(float *)((int)pdVar17 + 0xa4);
    *(float *)((int)pdVar17 + 0x84) =
         *(float *)((int)pdVar17 + 0xb4) * (float)tmp_pu21 + *(float *)(pdVar17 + 0x15);
    *(float *)(pdVar17 + 0x11) =
         (float)tmp_pu21 * *(float *)(pdVar17 + 0x17) + *(float *)((int)pdVar17 + 0xac);
    tmp_i12 = *(int *)(*tmp_pi10 + 0xa0);
    *(double **)(pdVar17 + 2) = pdVar17 + 0x10;
    *(int *)((int)pdVar17 + 0xc) = 0;
    *(int *)(pdVar17 + 1) = 0;
    *(int *)((int)pdVar17 + 0x14) = tmp_i12;
    *(int **)((int)pdVar17 + 4) = (int *)((int)pdVar17 + 0x74);
    *(int *)pdVar17 = *(int *)((int)pdVar17 + 0x34);
    tmp_pc8 = (void *)tmp_pi10[0x46];
    *(uint32_t *)((int)pdVar17 + -4) = 0x2bffa;
    (*tmp_pc8)();
    if (*(float *)(pdVar17 + 0x14) == 1.0) {
      return;
    }
    if ((*(byte *)((int)pdVar17 + 0xc4) & 0x14) != 0) {
      return;
    }
    if (*(int *)((int)pdVar17 + 0xcc) != 0x3fe) {
      return;
    }
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
LAB_0002b140:
    tmp_b4 = cgs[(int)tmp_ppu16 + 0x1efb225];
    *(uint8_t ***)((int)pdVar17 + 0x34) = tmp_ppu16 + 0x3ec887;
    if ((tmp_b4 & 1) == 0) {
      if ((*(byte *)(tmp_pi10 + 4) & 1) == 0) goto LAB_0002b863;
      goto LAB_0002b8a7;
    }
    if ((*(byte *)(tmp_pi10 + 4) & 1) == 0) {
LAB_0002b886:
      *(uint32_t *)((int)pdVar17 + -4) = 0x2b88b;
      tmp_i12 = PM_AltFire();
      if ((tmp_i12 == 0) && (*(char *)(pdVar17 + 6) != '\0')) goto LAB_0002b87b;
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
    }
    tmp_i12 = *tmp_pi10;
    if (((*(float *)(tmp_i12 + 0x3c) != 0.0) &&
        ((*(int *)(tmp_i12 + 0xa8) != 6 ||
         (((*(char *)((int)pdVar17 + 0x2c) == '\0' && (*(int *)(tmp_i12 + 0x30) < 1)) ||
          (*(int *)(tmp_i12 + 0xa4) != 1)))))) &&
       ((((tmp_u15 = *(uint *)(tmp_i12 + 0xa4),
          (tmp_u15 != 0x26 && (1 < tmp_u15 - 0x22 && 3 < tmp_u15 - 7)) && tmp_u15 != 0xe &&
          (1 < tmp_u15 - 0x2c)) && ((tmp_u15 & 0xfffffffd) != 0x30 && 3 < tmp_u15 - 1)) &&
        (tmp_u15 != 0x1c)))) goto LAB_0002b1e4;
  }
  tmp_i12 = *tmp_pi10;
  tmp_u15 = *(uint *)(tmp_i12 + 0x68);
  *(uint *)(pdVar17 + 7) = tmp_u15 & 0x40000;
  if ((tmp_u15 & 0x40000) != 0) {
    if (*(int *)(tmp_i12 + 0xe4) != 3) {
      return;
    }
    *(int *)(tmp_i12 + 0x2c) = *(int *)(tmp_i12 + 0x2c) + 500;
    *(uint32_t *)(tmp_pi10[1] + 0x78) = 1;
    return;
  }
  if ((cgs[*(int *)((int)pdVar17 + 0x34) + 0xf49009] & 0x10) == 0) {
    tmp_u7 = *(uint *)(tmp_i12 + 0xa4);
    tmp_i11 = tmp_pi10[0x41];
    *(uint *)(pdVar17 + 6) = tmp_u7;
    if (tmp_i11 == 3) {
      *(bool *)((int)pdVar17 + 0x3c) = (tmp_u7 & 0xfffffff7) != 1;
      *(byte *)((int)pdVar17 + 0x3c) =
           ((ulonglong)pdVar17[6] & 0xffffffef) != 4 & *(byte *)((int)pdVar17 + 0x3c);
      if (((((ulonglong)pdVar17[6] & 0xfffffffb) != 0xb &
            *(int *)(pdVar17 + 6) != 0x1c & *(byte *)((int)pdVar17 + 0x3c) &
           1 < *(int *)(pdVar17 + 6) - 0x19U) != 0) && (4 < *(int *)(pdVar17 + 6) - 0x2fU))
      goto LAB_0002ba28;
    }
  }
  else {
    tmp_i11 = *(int *)(tmp_i12 + 0xa4);
    tmp_i6 = tmp_pi10[0x41];
    *(int *)(pdVar17 + 6) = tmp_i11;
    if ((tmp_i6 == 3) &&
       ((*(bool *)((int)pdVar17 + 0x3c) = tmp_i11 - 5U < 2,
        *(char *)((int)pdVar17 + 0x3c) != '\0' || *(int *)(pdVar17 + 6) - 0x24U < 2 ||
        (*(int *)(pdVar17 + 6) == 0x1d)))) {
LAB_0002ba28:
      *(int *)(pdVar17 + 1) = tmp_i12;
      *(int *)((int)pdVar17 + 4) = 0;
      *(uint32_t *)pdVar17 = 0x24;
      *(uint32_t *)((int)pdVar17 + -4) = 0x2ba40;
      BG_AddPredictableEventToPlayerstate();
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      *(uint32_t *)(*tmp_pi10 + 0x2c) = 500;
      *(uint32_t *)(*tmp_pi10 + 0x30) = 0;
      return;
    }
  }
  if (*(int *)(pdVar17 + 6) - 1U < 0x33) {
    switch(tmp_ppu16[*(int *)(pdVar17 + 6) + -0xb8ae] + (int)tmp_ppu16) {
    case (uint8_t *)0x2c03b:
      if (*(int *)(tmp_i12 + 0xa8) - 5U < 2) goto LAB_0002c477;
      *(int *)(pdVar17 + 1) = tmp_i12;
      *(int *)((int)pdVar17 + 4) = 0;
      *(uint32_t *)pdVar17 = 0x43;
      *(uint32_t *)((int)pdVar17 + -4) = 0x2c065;
      BG_AddPredictableEventToPlayerstate();
LAB_0002c094:
      *(uint32_t *)((int)pdVar17 + -4) = 0x2c099;
      PM_StartWeaponAnim();
      break;
    case (uint8_t *)0x2c465:
      goto _L1039;
    case (uint8_t *)0x2c7c8:
      if (tmp_i20 == 0) {
        if (((*(byte *)((int)tmp_pi10 + 0x11) & 1) != 0) && ((*(byte *)(tmp_pi10 + 0x4d) & 0x20) != 0)
           ) {
          *(uint32_t *)pdVar17 = 1;
          *(uint32_t *)((int)pdVar17 + -4) = 0x2cefa;
          tmp_i20 = PM_WeaponAmmoAvailable();
          if (tmp_i20 != 0) {
            tmp_i20 = **(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
            *(uint32_t *)pdVar17 = *(uint32_t *)(tmp_i20 + 0xa4);
            *(uint32_t *)((int)pdVar17 + -4) = 0x2cf47;
            tmp_i12 = BG_FindClipForWeapon();
            if (*(uint *)(tmp_i20 + (tmp_i12 + 0xa4) * 4) >> 1 != 0) {
              tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
              tmp_i20 = *tmp_pi10;
              tmp_b4 = *(byte *)(tmp_i20 + 0x6a);
              *(int *)(pdVar17 + 2) = 1;
              *(int *)((int)pdVar17 + 0xc) = 0;
              if ((tmp_b4 & 8) == 0) {
                *(int *)(pdVar17 + 1) = 0x1b;
              }
              else {
                *(int *)(pdVar17 + 1) = 0x1c;
              }
              tmp_i12 = *(int *)(tmp_pi10[2] + 0x7f0);
              *(int *)pdVar17 = tmp_i20;
              *(int *)((int)pdVar17 + 4) = tmp_i12;
              *(uint32_t *)((int)pdVar17 + -4) = 0x2cf92;
              BG_AnimScriptEvent();
              tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
              *(uint32_t *)(*tmp_pi10 + 0x34) = 0x32;
              *(uint32_t *)(*tmp_pi10 + 0x394) = 0;
              goto LAB_0002c094;
            }
          }
          tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
        }
        tmp_i12 = *tmp_pi10;
        tmp_b4 = *(byte *)(tmp_i12 + 0x6a);
        *(int *)(pdVar17 + 2) = 0;
        *(int *)((int)pdVar17 + 0xc) = 0;
        if ((tmp_b4 & 8) != 0) goto LAB_0002c493;
LAB_0002c7ff:
        *(int *)(pdVar17 + 1) = 2;
LAB_0002c49b:
        tmp_i20 = *(int *)(tmp_pi10[2] + 0x7f0);
        *(int *)pdVar17 = tmp_i12;
        *(int *)((int)pdVar17 + 4) = tmp_i20;
        *(uint32_t *)((int)pdVar17 + -4) = 0x2c4b0;
        BG_AnimScriptEvent();
        tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
        goto LAB_0002c0b5;
      }
      if (*(int *)(tmp_i12 + 0xa8) != 6) goto LAB_0002c0c4;
      goto LAB_0002c27a;
    case (uint8_t *)0x2cca7:
      if (*(int *)(tmp_i12 + 0xa8) - 5U < 2) goto LAB_0002c477;
      *(int *)(pdVar17 + 1) = tmp_i12;
      *(int *)((int)pdVar17 + 4) = 0;
      *(uint32_t *)pdVar17 = 0x43;
      *(uint32_t *)((int)pdVar17 + -4) = 0x2ccd1;
      BG_AddPredictableEventToPlayerstate();
      *(uint8_t **)(**(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f)) + 0x30) =
           tmp_ppu16[*(int *)(**(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f)) + 0xa4) * 0x12 +
                    0x835];
      *(uint32_t *)pdVar17 = 3;
      *(uint32_t *)((int)pdVar17 + -4) = 0x2ccf9;
      PM_ContinueWeaponAnim();
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      goto LAB_0002c0b5;
    case (uint8_t *)0x2cd04:
      if (tmp_i20 != 0) goto LAB_0002cd0c;
      *(int *)pdVar17 = *(int *)(pdVar17 + 6);
      *(uint32_t *)((int)pdVar17 + -4) = 0x2ce35;
      tmp_i20 = PM_WeaponAmmoAvailable();
      if (tmp_i20 != 0) goto LAB_0002c094;
      break;
    case (uint8_t *)0x2cd24:
      if (tmp_i20 != 0) goto LAB_0002cd0c;
      *(int *)pdVar17 = *(int *)(pdVar17 + 6);
      *(uint32_t *)((int)pdVar17 + -4) = 0x2cd34;
      tmp_i20 = PM_WeaponAmmoAvailable();
      if (tmp_i20 != 0) {
        tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
        tmp_i20 = *tmp_pi10;
        tmp_b4 = *(byte *)(tmp_i20 + 0x6a);
        *(int *)(pdVar17 + 2) = 1;
        *(int *)((int)pdVar17 + 0xc) = 0;
        if ((tmp_b4 & 8) == 0) {
          *(int *)(pdVar17 + 1) = 2;
        }
        else {
          *(int *)(pdVar17 + 1) = 0x14;
        }
        tmp_i12 = *(int *)(tmp_pi10[2] + 0x7f0);
        *(int *)pdVar17 = tmp_i20;
        *(int *)((int)pdVar17 + 4) = tmp_i12;
        *(uint32_t *)((int)pdVar17 + -4) = 0x2cd7b;
        BG_AnimScriptEvent();
      }
      break;
    case (uint8_t *)0x2cd80:
      if (tmp_i20 == 0) {
        *(int *)pdVar17 = *(int *)(pdVar17 + 6);
        *(uint32_t *)((int)pdVar17 + -4) = 0x2cd90;
        tmp_i20 = PM_WeaponAmmoAvailable();
        if (tmp_i20 != 0) {
          tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
          tmp_i20 = *tmp_pi10;
          if (*(int *)(tmp_i20 + 0xa4) == 0xf) {
            *(uint32_t *)(tmp_i20 + 0x34) = 0x32;
          }
          else {
            *(uint32_t *)(tmp_i20 + 0x34) = 4000;
            tmp_i20 = *tmp_pi10;
            tmp_b4 = *(byte *)(tmp_i20 + 0x6a);
            *(int *)(pdVar17 + 2) = 1;
            *(int *)((int)pdVar17 + 0xc) = 0;
            if ((tmp_b4 & 8) == 0) {
              *(int *)(pdVar17 + 1) = 0x1b;
            }
            else {
              *(int *)(pdVar17 + 1) = 0x1c;
            }
            tmp_i12 = *(int *)(tmp_pi10[2] + 0x7f0);
            *(int *)pdVar17 = tmp_i20;
            *(int *)((int)pdVar17 + 4) = tmp_i12;
            *(uint32_t *)((int)pdVar17 + -4) = 0x2cde5;
            BG_AnimScriptEvent();
            tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
          }
          *(uint32_t *)(*tmp_pi10 + 0x394) = 0;
          goto LAB_0002c094;
        }
        break;
      }
LAB_0002cd0c:
      if (*(int *)(tmp_i12 + 0xa8) != 6) goto LAB_0002c0c4;
      goto LAB_0002c4d2;
    case (uint8_t *)0x2ce42:
      if (1 < *(int *)(tmp_i12 + 0xa8) - 5U) goto LAB_0002ce50;
      *(int *)(pdVar17 + 2) = 1;
      *(int *)((int)pdVar17 + 0xc) = 1;
      goto joined_r0x0002c48d;
    case (uint8_t *)0x2ce67:
      if (*(int *)(tmp_i12 + 0xa8) - 5U < 2) {
        if ((tmp_u15 & 0x80000) == 0) {
          *(int *)(pdVar17 + 2) = 1;
          *(int *)((int)pdVar17 + 0xc) = 0;
          if (*(int *)((int)pdVar17 + 0x5c) == 0) goto LAB_0002c7ff;
          *(int *)(pdVar17 + 1) = 3;
        }
        else {
          *(int *)(pdVar17 + 2) = 1;
          *(int *)((int)pdVar17 + 0xc) = 0;
          if (*(int *)((int)pdVar17 + 0x5c) == 0) goto LAB_0002c493;
          *(int *)(pdVar17 + 1) = 0x14;
        }
        goto LAB_0002c49b;
      }
      if (*(int *)(pdVar17 + 6) == 5) {
        *(int *)(pdVar17 + 1) = tmp_i12;
        *(int *)((int)pdVar17 + 4) = 0;
        *(uint32_t *)pdVar17 = 0x43;
        *(uint32_t *)((int)pdVar17 + -4) = 0x2ce98;
        BG_AddPredictableEventToPlayerstate();
        break;
      }
      goto LAB_0002c09f;
    }
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
LAB_0002c09f:
    *(uint8_t **)(*tmp_pi10 + 0x30) = tmp_ppu16[*(int *)(*tmp_pi10 + 0xa4) * 0x12 + 0x835];
  }
  else {
_L1039:
    if (*(int *)(tmp_i12 + 0xa8) - 5U < 2) {
LAB_0002c477:
      *(int *)(pdVar17 + 2) = 1;
      *(int *)((int)pdVar17 + 0xc) = 0;
joined_r0x0002c48d:
      if ((tmp_u15 & 0x80000) == 0) goto LAB_0002c7ff;
LAB_0002c493:
      *(int *)(pdVar17 + 1) = 0x13;
      goto LAB_0002c49b;
    }
LAB_0002ce50:
    *(uint8_t **)(tmp_i12 + 0x30) = tmp_ppu16[*(int *)(pdVar17 + 6) * 0x12 + 0x835];
  }
LAB_0002c0b5:
  tmp_i12 = *tmp_pi10;
  if ((*(int *)(tmp_i12 + 0xa8) == 6) &&
     ((*(char *)((int)pdVar17 + 0x2c) != '\0' || (0 < *(int *)(tmp_i12 + 0x30))))) {
LAB_0002c4d2:
    if (*(int *)(tmp_i12 + 0xa4) != 1) goto LAB_0002c0c4;
LAB_0002c27a:
    *(uint32_t *)(*tmp_pi10 + 0xa8) = 6;
  }
  else {
LAB_0002c0c4:
    *(uint32_t *)((int)pdVar17 + -4) = 0x2c0c9;
    tmp_i20 = PM_AltFire();
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
    if (tmp_i20 != 0) goto LAB_0002c27a;
    *(uint32_t *)(*tmp_pi10 + 0xa8) = 5;
  }
  tmp_i20 = *(int *)(*tmp_pi10 + 0xa4);
  tmp_pu21 = tmp_ppu16[tmp_i20 * 0x12 + 0x830];
  if (tmp_i20 != 0) {
    *(int *)pdVar17 = tmp_i20;
    *(uint32_t *)((int)pdVar17 + -4) = 0x2c293;
    tmp_i12 = PM_WeaponAmmoAvailable();
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
    tmp_i20 = *tmp_pi10;
    if ((*(int *)(tmp_i20 + 0xa4) == 1) && (*(int *)(tmp_i20 + 0xa8) == 6)) {
      tmp_pu21 = (uint8_t *)0x1;
    }
    if ((tmp_i12 < (int)tmp_pu21) && (tmp_i12 != -1)) {
      *(int *)pdVar17 = *(int *)(tmp_i20 + 0xa4);
      *(int *)((int)pdVar17 + 0x2c) = tmp_i20;
      *(uint32_t *)((int)pdVar17 + -4) = 0x2c2cd;
      tmp_i12 = BG_FindAmmoForWeapon();
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      tmp_i20 = *tmp_pi10;
      tmp_b9 = (int)tmp_pu21 <= *(int *)(*(int *)((int)pdVar17 + 0x2c) + (tmp_i12 + 100) * 4);
      *(uint *)((int)pdVar17 + 0x2c) = (uint)tmp_b9;
      if ((*(int *)tmp_pi10[1] == 0) &&
         ((tmp_i12 = *(int *)(tmp_i20 + 0xa4), tmp_ppu16[tmp_i12 * 0x12 + 0x83d] != (uint8_t *)0x0 &&
          ((*(byte *)((int)tmp_pi10 + 0x11) & 8) == 0)))) {
        if (tmp_i12 == 0xf) goto LAB_0002c350;
        if (tmp_i12 < 0x10) {
          if (((tmp_i12 == 4) || (tmp_i12 == 9)) || (tmp_i12 == 1)) goto LAB_0002c350;
        }
        else {
          if (tmp_i12 == 0x1c) goto LAB_0002c350;
          if (tmp_i12 < 0x1d) {
            if (tmp_i12 == 0x19) goto LAB_0002c350;
          }
          else if (tmp_i12 - 0x30U < 4) goto LAB_0002c350;
        }
LAB_0002c332:
        *(int *)(pdVar17 + 1) = tmp_i20;
        *(int *)((int)pdVar17 + 4) = 0;
        *(uint32_t *)pdVar17 = 0x19;
        *(uint32_t *)((int)pdVar17 + -4) = 0x2c34a;
        BG_AddPredictableEventToPlayerstate();
        tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      }
      else {
        tmp_i12 = *(int *)(tmp_i20 + 0xa4);
        if (tmp_i12 != 0x19) {
          if (0x19 < tmp_i12) {
            if (tmp_i12 < 0x2a) {
              if (0x26 < tmp_i12) goto LAB_0002c332;
              if (tmp_i12 == 0x1c) goto LAB_0002c3e2;
            }
            else if (tmp_i12 - 0x30U < 4) goto LAB_0002c3e2;
            goto LAB_0002c39b;
          }
          if (tmp_i12 != 4) {
            if (tmp_i12 < 5) {
              if (tmp_i12 == 1) goto LAB_0002c3e2;
            }
            else if ((tmp_i12 == 9) || (tmp_i12 == 0xf)) goto LAB_0002c3e2;
LAB_0002c39b:
            if (tmp_b9) {
              *(int *)(pdVar17 + 1) = tmp_i20;
              *(int *)((int)pdVar17 + 4) = 0;
              *(uint32_t *)pdVar17 = 0x1b;
              *(uint32_t *)((int)pdVar17 + -4) = 0x2c3b7;
              BG_AddPredictableEventToPlayerstate();
              tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
              goto LAB_0002c3bd;
            }
            goto LAB_0002c332;
          }
        }
LAB_0002c3e2:
        if (*(int *)((int)pdVar17 + 0x2c) != 0) {
LAB_0002c3bd:
          *(uint32_t *)pdVar17 = *(uint32_t *)(*tmp_pi10 + 0xa4);
          *(uint32_t *)((int)pdVar17 + -4) = 0x2c3cd;
          tmp_u13 = PM_ReloadAnimForWeapon();
          *(uint32_t *)pdVar17 = tmp_u13;
          *(uint32_t *)((int)pdVar17 + -4) = 0x2c3d5;
          PM_ContinueWeaponAnim();
          return;
        }
      }
LAB_0002c350:
      tmp_u15 = *(int *)(*tmp_pi10 + 0xa4) - 0x1b;
      if (tmp_u15 < 0x14) {
        *(uint *)(pdVar17 + 7) = (uint)((1 << ((byte)tmp_u15 & 0x1f) & 0x98601U) != 0);
      }
      *(int *)pdVar17 = *(int *)(pdVar17 + 7);
      *(uint32_t *)((int)pdVar17 + -4) = 0x2c382;
      PM_ContinueWeaponAnim();
      *(int *)(**(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f)) + 0x2c) =
           *(int *)(**(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f)) + 0x2c) + 500;
      return;
    }
  }
  tmp_i20 = *tmp_pi10;
  if (0 < *(int *)(tmp_i20 + 0x30)) {
    return;
  }
  if ((((*(byte *)(tmp_i20 + 0x6a) & 8) == 0) && ((memoryPool[(int)(tmp_ppu16 + 0x5990f)] & 2) != 0))
     && ((*(int *)(tmp_i20 + 0xa4) - 5U < 0x19 &&
         (0.0 < (float)tmp_ppu16[*(int *)(tmp_i20 + 0xa4) + -0xb7fe])))) {
    tmp_f3 = -((float)tmp_ppu16[*(int *)(tmp_i20 + 0xa4) + -0xb7fe] / (float)tmp_ppu16[-0xb6d9]);
    tmp_f24 = *(float *)(memoryPool + (int)(tmp_ppu16 + 0x598f8));
    tmp_f2 = *(float *)(memoryPool + (int)(tmp_ppu16 + 0x598f9));
    *(float *)(tmp_i20 + 0x20) =
         tmp_f3 * *(float *)(memoryPool + (int)(tmp_ppu16 + 0x598f7)) + *(float *)(tmp_i20 + 0x20);
    *(float *)(*tmp_pi10 + 0x24) = tmp_f24 * tmp_f3 + *(float *)(*tmp_pi10 + 0x24);
    *(float *)(*tmp_pi10 + 0x28) = tmp_f2 * tmp_f3 + *(float *)(*tmp_pi10 + 0x28);
    tmp_i20 = *tmp_pi10;
    if (*(int *)(tmp_i20 + 0x10) == 0) {
      *(uint32_t *)(tmp_i20 + 0x10) = 100;
      *(uint *)(*tmp_pi10 + 0xc) = *(uint *)(*tmp_pi10 + 0xc) | 0x40;
      tmp_i20 = *tmp_pi10;
    }
  }
  *(uint32_t *)pdVar17 = *(uint32_t *)(tmp_i20 + 0xa4);
  *(uint32_t *)((int)pdVar17 + -4) = 0x2c193;
  tmp_i20 = PM_WeaponAmmoAvailable();
  tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
  if (((tmp_i20 != -1) && (tmp_i20 = *tmp_pi10, *(int *)(tmp_i20 + 0x140) == 0)) &&
     ((*(byte *)(tmp_i20 + 0x69) & 0x80) == 0)) {
    *(uint8_t **)((int)pdVar17 + 4) = tmp_pu21;
    *(uint32_t *)pdVar17 = *(uint32_t *)(tmp_i20 + 0xa4);
    *(uint32_t *)((int)pdVar17 + -4) = 0x2c1bf;
    PM_WeaponUseAmmo();
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
  }
  tmp_i20 = *tmp_pi10;
  tmp_i12 = *(int *)(tmp_i20 + 0xa4);
  if (tmp_ppu16[tmp_i12 * 0x12 + 0x837] != (uint8_t *)0x0) {
    tmp_pi1 = (int *)(tmp_i20 + 0x49c + tmp_i12 * 4);
    *tmp_pi1 = (int)(tmp_ppu16[tmp_i12 * 0x12 + 0x836] + *tmp_pi1);
    tmp_i20 = *tmp_pi10;
  }
  tmp_i12 = *(int *)(tmp_i20 + 0xa4);
  if ((1 < tmp_i12 - 0x2cU) && (1 < tmp_i12 - 0x22U)) {
    *(int *)pdVar17 = tmp_i12;
    *(uint32_t *)((int)pdVar17 + -4) = 0x2c20a;
    tmp_i12 = BG_FindClipForWeapon();
    if (*(int *)(tmp_i20 + (tmp_i12 + 0xa4) * 4) != 0) {
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      *(int *)((int)pdVar17 + 0x2c) = 2;
      tmp_u15 = *(int *)(*tmp_pi10 + 0xa4) - 0x1b;
      if ((tmp_u15 < 0x14) && ((1 << ((byte)tmp_u15 & 0x1f) & 0x90601U) != 0)) goto LAB_0002cc61;
      goto LAB_0002c24a;
    }
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
    tmp_i20 = *(int *)(*tmp_pi10 + 0xa4);
    if (tmp_i20 != 0x2a) {
      if (tmp_i20 < 0x2b) {
        if (1 < tmp_i20 - 0x24U) {
LAB_0002c242:
          *(int *)((int)pdVar17 + 0x2c) = 4;
          goto LAB_0002c24a;
        }
      }
      else if (tmp_i20 != 0x2e) goto LAB_0002c242;
LAB_0002cc61:
      *(int *)((int)pdVar17 + 0x2c) = 3;
      goto LAB_0002c24a;
    }
    *(int *)((int)pdVar17 + 0x2c) = 2;
    goto _L1111;
  }
  *(int *)((int)pdVar17 + 0x2c) = 2;
  if (*(int *)((int)pdVar17 + 0x5c) == 0) goto LAB_0002cc61;
LAB_0002c24a:
  tmp_i20 = *(int *)(*tmp_pi10 + 0xa4);
  if (0x32 < tmp_i20 - 1U) {
_L1107:
    *(uint32_t *)((int)pdVar17 + -4) = 0x2c540;
    PM_StartWeaponAnim();
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
    goto _L1111;
  }
  switch(tmp_ppu16[tmp_i20 + -0xb876] + (int)tmp_ppu16) {
  case (uint8_t *)0x2c52a:
    if (*(int *)(*tmp_pi10 + 0xa8) != 6) goto _L1107;
    tmp_i12 = *tmp_pi10;
    tmp_i20 = *(int *)(tmp_i12 + 0xa4);
    goto LAB_0002c5b0;
  case (uint8_t *)0x2c537:
    goto _L1107;
  case (uint8_t *)0x2cc16:
    *(int *)pdVar17 = *(int *)((int)pdVar17 + 0x2c);
    *(uint32_t *)((int)pdVar17 + -4) = 0x2cc22;
    PM_ContinueWeaponAnim();
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
  }
_L1111:
  tmp_i12 = *tmp_pi10;
  tmp_i20 = *(int *)(tmp_i12 + 0xa4);
  if (tmp_i20 == 0x1c) {
LAB_0002c65b:
    *(int *)(pdVar17 + 1) = tmp_i12;
    *(int *)((int)pdVar17 + 4) = 0;
    *(uint32_t *)pdVar17 = 0x19;
    *(uint32_t *)((int)pdVar17 + -4) = 0x2c673;
    BG_AddPredictableEventToPlayerstate();
LAB_0002c589:
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
LAB_0002c58f:
    tmp_i12 = *tmp_pi10;
    tmp_i20 = *(int *)(tmp_i12 + 0xa4);
    if ((1 < tmp_i20 - 0x2cU) && (1 < tmp_i20 - 0x22U)) {
      if (tmp_i20 == 1) {
LAB_0002c5b0:
        if (*(int *)(tmp_i12 + 0xa8) == 6) {
          *(int *)(pdVar17 + 1) = tmp_i12;
          *(int *)((int)pdVar17 + 4) = 0;
          *(uint32_t *)pdVar17 = 0x5f;
          *(uint32_t *)((int)pdVar17 + -4) = 0x2c866;
          BG_AddPredictableEventToPlayerstate();
          tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
          goto LAB_0002c5fa;
        }
      }
      goto LAB_0002c5bd;
    }
    *(int *)(pdVar17 + 1) = tmp_i12;
    *(int *)((int)pdVar17 + 4) = 0;
    if (*(int *)((int)pdVar17 + 0x5c) != 0) goto LAB_0002c723;
    *(uint32_t *)pdVar17 = 0x22;
    *(uint32_t *)((int)pdVar17 + -4) = 0x2c647;
    BG_AddPredictableEventToPlayerstate();
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
  }
  else {
    if (tmp_i20 < 0x1d) {
      if (tmp_i20 != 0x15) {
        if (tmp_i20 < 0x16) {
          if ((tmp_i20 == 5) || (tmp_i20 == 0xf)) goto LAB_0002c65b;
        }
        else {
          if (tmp_i20 == 0x19) goto LAB_0002c65b;
          if (tmp_i20 == 0x1a) {
            *(int *)(pdVar17 + 1) = tmp_i12;
            *(int *)((int)pdVar17 + 4) = 0;
            *(uint32_t *)pdVar17 = 0x19;
            *(uint32_t *)((int)pdVar17 + -4) = 0x2c777;
            BG_AddPredictableEventToPlayerstate();
            tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
            *(uint32_t *)(*tmp_pi10 + 0x2fc) = 1;
            *(uint32_t *)(*tmp_pi10 + 0x1f8) = 0;
            *(uint32_t *)(*tmp_pi10 + 0x2f8) = 0;
            *(int *)(pdVar17 + 1) = 0;
            *(int *)((int)pdVar17 + 4) = 0x1b;
            *(uint32_t *)pdVar17 = 0x1a;
            *(uint32_t *)((int)pdVar17 + -4) = 0x2c7bd;
            PM_BeginWeaponChange();
            tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
          }
        }
        goto LAB_0002c58f;
      }
      goto LAB_0002c65b;
    }
    if (tmp_i20 != 0x2a) {
      if (tmp_i20 < 0x2b) {
        if (1 < tmp_i20 - 0x24U) goto LAB_0002c58f;
        *(int *)pdVar17 = tmp_i20;
        *(uint32_t *)((int)pdVar17 + -4) = 0x2c57c;
        tmp_i20 = BG_FindAmmoForWeapon();
        if (*(int *)(tmp_i12 + (tmp_i20 + 100) * 4) == 0) {
          tmp_i20 = **(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
          *(int *)((int)pdVar17 + 4) = 0;
          *(uint32_t *)pdVar17 = 0x19;
          *(int *)(pdVar17 + 1) = tmp_i20;
          *(uint32_t *)((int)pdVar17 + -4) = 0x2c82c;
          BG_AddPredictableEventToPlayerstate();
          tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
          goto LAB_0002c58f;
        }
        goto LAB_0002c589;
      }
      if (tmp_i20 - 0x30U < 4) goto LAB_0002c65b;
      goto LAB_0002c58f;
    }
    tmp_i20 = 0x2a;
    if (*(int *)(tmp_i12 + 0x214) == 0) goto LAB_0002c65b;
LAB_0002c5bd:
    *(int *)pdVar17 = tmp_i20;
    *(uint32_t *)((int)pdVar17 + -4) = 0x2c5c5;
    tmp_i20 = BG_FindClipForWeapon();
    if (*(int *)(tmp_i12 + (tmp_i20 + 0xa4) * 4) == 0) {
      tmp_i20 = **(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      *(int *)((int)pdVar17 + 4) = 0;
      *(uint32_t *)pdVar17 = 0x23;
      *(int *)(pdVar17 + 1) = tmp_i20;
      *(uint32_t *)((int)pdVar17 + -4) = 0x2c5f4;
      BG_AddPredictableEventToPlayerstate();
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
    }
    else {
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      tmp_i20 = *tmp_pi10;
      *(int *)(pdVar17 + 6) = tmp_i20;
      tmp_u15 = *(uint *)(tmp_i20 + 0xa4);
      *(bool *)(pdVar17 + 7) = tmp_u15 == 0x12;
      tmp_b4 = *(byte *)(pdVar17 + 7);
      *(bool *)(pdVar17 + 7) = (tmp_u15 & 0xffffffef) == 5;
      tmp_b5 = *(byte *)(pdVar17 + 7);
      *(bool *)(pdVar17 + 7) = (tmp_u15 & 0xffffffef) == 0xc;
      *(byte *)(pdVar17 + 7) = tmp_u15 == 0xf | tmp_b4 | tmp_b5 | *(byte *)(pdVar17 + 7);
      if (((3 < tmp_u15 - 0x30 && (1 < tmp_u15 - 0x2a && *(char *)(pdVar17 + 7) == '\0')) &&
           1 < tmp_u15 - 0x24) && (1 < tmp_u15 - 0x19)) {
        *(int *)((int)pdVar17 + 4) = 0;
        *(int *)(pdVar17 + 1) = *(int *)(pdVar17 + 6);
LAB_0002c723:
        *(uint32_t *)pdVar17 = 0x21;
        *(uint32_t *)((int)pdVar17 + -4) = 0x2c72f;
        BG_AddPredictableEventToPlayerstate();
        tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      }
    }
  }
LAB_0002c5fa:
  *(uint32_t *)(tmp_pi10[1] + 0x5c) = 0;
  tmp_i20 = *tmp_pi10;
  tmp_i12 = *(int *)(tmp_i20 + 0xa4);
  if (tmp_i12 - 1U < 0x33) {
    switch(tmp_ppu16[tmp_i12 + -0xb843] + (int)tmp_ppu16) {
    case (uint8_t *)0x2c871:
      tmp_pu21 = tmp_ppu16[tmp_i12 * 0x12 + 0x836];
      *(int *)pdVar17 = tmp_i12;
      *(uint8_t **)(pdVar17 + 6) = tmp_pu21;
      *(uint32_t *)((int)pdVar17 + -4) = 0x2c884;
      tmp_i12 = BG_FindClipForWeapon();
      if (*(int *)(tmp_i20 + (tmp_i12 + 0xa4) * 4) == 0) {
        if (*(int *)((int)pdVar17 + 0x5c) != 0) {
LAB_0002d003:
          *(int *)((int)pdVar17 + 0x2c) = 0x14;
          tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
          break;
        }
      }
      else {
        tmp_i20 = **(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
        *(uint32_t *)pdVar17 = *(uint32_t *)(tmp_i20 + 0xa4);
        *(uint32_t *)((int)pdVar17 + -4) = 0x2cfe5;
        tmp_u13 = BG_AkimboSidearm();
        *(uint32_t *)pdVar17 = tmp_u13;
        *(uint32_t *)((int)pdVar17 + -4) = 0x2cfed;
        tmp_i12 = BG_FindClipForWeapon();
        if ((*(int *)(tmp_i20 + (tmp_i12 + 0xa4) * 4) != 0) || (*(int *)((int)pdVar17 + 0x5c) == 0))
        goto LAB_0002d003;
      }
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      tmp_pu21 = tmp_ppu16[*(int *)(*tmp_pi10 + 0xa4) * 0x12 + 0x836];
      *(int *)((int)pdVar17 + 0x2c) = 0x14;
      *(int *)(pdVar17 + 6) = (int)tmp_pu21 * 2;
      break;
    case (uint8_t *)0x2cfb7:
      *(int *)((int)pdVar17 + 0x2c) = 0x32;
      *(uint8_t **)(pdVar17 + 6) = tmp_ppu16[tmp_i12 * 0x12 + 0x836];
      break;
    case (uint8_t *)0x2d016:
      *(int *)((int)pdVar17 + 0x2c) = 100;
      *(uint8_t **)(pdVar17 + 6) = tmp_ppu16[tmp_i12 * 0x12 + 0x836];
      break;
    case (uint8_t *)0x2d02e:
      if (*(int *)((int)pdVar17 + 0x2c) != 4) goto _L1656;
      *(int *)((int)pdVar17 + 0x2c) = 0x14;
      *(int *)(pdVar17 + 6) = 2000;
      break;
    case (uint8_t *)0x2d039:
_L1656:
      *(int *)((int)pdVar17 + 0x2c) = 0x14;
      *(uint8_t **)(pdVar17 + 6) = tmp_ppu16[tmp_i12 * 0x12 + 0x836];
      break;
    case (uint8_t *)0x2d323:
      *(int *)((int)pdVar17 + 0x2c) = 200;
      *(uint8_t **)(pdVar17 + 6) = tmp_ppu16[tmp_i12 * 0x12 + 0x836];
      break;
    case (uint8_t *)0x2d33b:
      *(int *)(pdVar17 + 6) = 0x6e;
      if ((cgs[*(int *)((int)pdVar17 + 0x34) + 0xf49009] & 4) == 0) {
        *(uint8_t **)(pdVar17 + 6) = tmp_ppu16[tmp_i12 * 0x12 + 0x836];
      }
      *(uint32_t *)((int)pdVar17 + -4) = 0x2d360;
      tmp_i20 = rand();
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      *(int *)((int)pdVar17 + 0x2c) = tmp_i20 % 10 + 0xf;
      break;
    case (uint8_t *)0x2d37a:
      *(int *)((int)pdVar17 + 0x2c) = 0;
      *(uint8_t **)(pdVar17 + 6) = tmp_ppu16[tmp_i12 * 0x12 + 0x836];
      break;
    case (uint8_t *)0x2d39f:
      goto _L1241;
    case (uint8_t *)0x2d3b4:
      if (*(int *)(tmp_i20 + 0xa8) == 6) {
        *(int *)((int)pdVar17 + 0x2c) = 0;
        *(int *)(pdVar17 + 6) = 0x2ee;
      }
      else {
        tmp_pu21 = tmp_ppu16[0x848];
        *(int *)((int)pdVar17 + 0x2c) = 0;
        *(uint8_t **)(pdVar17 + 6) = tmp_pu21;
      }
    }
  }
  else {
_L1241:
    *(int *)((int)pdVar17 + 0x2c) = 0;
    *(int *)(pdVar17 + 6) = 0;
  }
  if (tmp_ppu16[*(int *)(*tmp_pi10 + 0xa4) * 0x1ac + 0x35ce1a] != (uint8_t *)0x0) {
    tmp_pu21 = tmp_ppu16[*(int *)(*tmp_pi10 + 0xa4) * 0x1ac + 0x35ce1b];
    *(uint8_t **)((int)pdVar17 + 0x2c) = tmp_ppu16[*(int *)(*tmp_pi10 + 0xa4) * 0x1ac + 0x35ce1a];
    if (tmp_pu21 != (uint8_t *)0x0) {
      *(uint8_t **)(pdVar17 + 7) = tmp_pu21;
      *(uint32_t *)((int)pdVar17 + -4) = 0x2c8f4;
      tmp_i20 = rand();
      tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
      *(int *)((int)pdVar17 + 0x2c) = *(int *)((int)pdVar17 + 0x2c) + tmp_i20 % *(int *)(pdVar17 + 7)
      ;
    }
  }
  *(uint32_t *)(tmp_pi10[1] + 0x58) = 0;
  tmp_i20 = *(int *)(*tmp_pi10 + 0xa4);
  if (tmp_ppu16[tmp_i20 * 0x1ac + 0x35ce16] != (uint8_t *)0x0) {
    *(int *)(tmp_pi10[1] + 0x48) = tmp_pi10[3];
    *(uint8_t **)(tmp_pi10[1] + 0x4c) = tmp_ppu16[*(int *)(*tmp_pi10 + 0xa4) * 0x1ac + 0x35ce17];
    tmp_i20 = tmp_pi10[3];
    *(int *)(pdVar17 + 7) = tmp_pi10[1];
    *pdVar17 = (double)tmp_i20;
    *(uint32_t *)((int)pdVar17 + -4) = 0x2c95f;
    tmp_d22 = cos(*pdVar17);
    *(float *)(*(int *)(pdVar17 + 7) + 0x50) =
         (float)tmp_d22 * (float)tmp_ppu16[*(int *)(*tmp_pi10 + 0xa4) * 0x1ac + 0x35ce18];
    tmp_i20 = tmp_pi10[3];
    *(int *)(pdVar17 + 7) = tmp_pi10[1];
    *pdVar17 = (double)tmp_i20;
    *(uint32_t *)((int)pdVar17 + -4) = 0x2c98b;
    tmp_d22 = cos(*pdVar17);
    *(float *)(*(int *)(pdVar17 + 7) + 0x54) =
         ABS((float)tmp_d22) * (float)tmp_ppu16[*(int *)(*tmp_pi10 + 0xa4) * 0x1ac + 0x35ce19];
    goto LAB_0002c9a7;
  }
  if (tmp_i20 < 0x24) {
    if ((tmp_i20 < 0x22) && (tmp_i20 != 7)) {
      if (tmp_i20 < 8) {
        if (tmp_i20 == 2) goto LAB_0002d099;
      }
      else {
        if (tmp_i20 == 0xe) goto LAB_0002d099;
        if (tmp_i20 == 0x1d) {
          *(int *)(tmp_pi10[1] + 0x48) = tmp_pi10[3];
          *(uint32_t *)(tmp_pi10[1] + 0x4c) = 200;
          if (((*(byte *)(*tmp_pi10 + 0xc) & 1) == 0) && ((*(byte *)(*tmp_pi10 + 0x6a) & 8) == 0)) {
            tmp_i20 = tmp_pi10[1];
            *pdVar17 = (double)tmp_pi10[3];
            *(uint32_t *)((int)pdVar17 + -4) = 0x2d2f6;
            tmp_d22 = cos(*pdVar17);
            *(float *)(tmp_i20 + 0x50) = (float)tmp_d22 * (float)tmp_ppu16[-0xb6d3];
            tmp_i20 = tmp_pi10[1];
            *pdVar17 = (double)tmp_pi10[3];
            *(uint32_t *)((int)pdVar17 + -4) = 0x2d30d;
            tmp_d22 = cos(*pdVar17);
            *(float *)(tmp_i20 + 0x54) =
                 ABS((float)tmp_d22) * (float)tmp_ppu16[-0xb6e0] * (float)tmp_ppu16[-0xb6be];
          }
          else {
            tmp_i20 = tmp_pi10[1];
            *pdVar17 = (double)tmp_pi10[3];
            *(uint32_t *)((int)pdVar17 + -4) = 0x2d278;
            tmp_d22 = cos(*pdVar17);
            *(float *)(tmp_i20 + 0x50) = (float)tmp_d22 * (float)tmp_ppu16[-0xba3f];
            tmp_i20 = tmp_pi10[1];
            *pdVar17 = (double)tmp_pi10[3];
            *(uint32_t *)((int)pdVar17 + -4) = 0x2d28f;
            tmp_d22 = cos(*pdVar17);
            *(float *)(tmp_i20 + 0x54) =
                 ABS((float)tmp_d22) * (float)tmp_ppu16[-0xb6c0] * (float)tmp_ppu16[-0xb6bf];
          }
          goto LAB_0002c9a7;
        }
      }
      goto LAB_0002d072;
    }
LAB_0002d099:
    *(int *)(tmp_pi10[1] + 0x48) = tmp_pi10[3];
    *(uint *)(tmp_pi10[1] + 0x4c) = (-(uint)((tmp_pi10[0x4d] & 8U) == 0) & 0x1e) + 0x46;
    *(uint32_t *)(tmp_pi10[1] + 0x50) = 0;
    tmp_i20 = tmp_pi10[1];
    if ((*(byte *)(tmp_pi10 + 0x4d) & 8) == 0) {
      *(uint32_t *)((int)pdVar17 + -4) = 0x2d15c;
      tmp_u15 = rand();
      *(uint *)(pdVar17 + 7) = tmp_u15 & 0x7fff;
      tmp_f24 = ((float)*(int *)(pdVar17 + 7) / (float)tmp_ppu16[-0xb6bd]) * (float)tmp_ppu16[-0xb6c0]
               * (float)tmp_ppu16[-0xb6bf];
    }
    else {
      *(uint32_t *)((int)pdVar17 + -4) = 0x2d0db;
      tmp_u15 = rand();
      *(uint *)(pdVar17 + 7) = tmp_u15 & 0x7fff;
      tmp_f24 = ((float)*(int *)(pdVar17 + 7) / (float)tmp_ppu16[-0xb6bd]) * (float)tmp_ppu16[-0xb6d3]
               * (float)tmp_ppu16[-0xb6bf];
    }
    tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
    *(float *)(tmp_i20 + 0x54) = tmp_f24;
  }
  else if (tmp_i20 < 0x29) {
    if (tmp_i20 < 0x27) {
      if (tmp_i20 == 0x26) goto LAB_0002d099;
LAB_0002d072:
      *(uint32_t *)(tmp_pi10[1] + 0x48) = 0;
      *(uint32_t *)(tmp_pi10[1] + 0x50) = 0;
    }
    else {
      *(int *)(tmp_pi10[1] + 0x48) = tmp_pi10[3];
      if (*(int *)(cgs + *(int *)((int)pdVar17 + 0x34) + 0xf4910c) == 2) {
        *(uint32_t *)(tmp_pi10[1] + 0x4c) = 0xaa;
        *(uint32_t *)(tmp_pi10[1] + 0x54) = 0x3e800000;
        tmp_i20 = tmp_pi10[1];
        *pdVar17 = (double)tmp_pi10[3];
        *(uint32_t *)((int)pdVar17 + -4) = 0x2d1ab;
        tmp_d22 = cos(*pdVar17);
        *(float *)(tmp_i20 + 0x50) = (float)tmp_d22 * (float)tmp_ppu16[-0xba3f];
      }
      else {
        *(uint32_t *)(tmp_pi10[1] + 0x4c) = 300;
        tmp_i20 = tmp_pi10[1];
        *pdVar17 = (double)tmp_pi10[3];
        *(uint32_t *)((int)pdVar17 + -4) = 0x2d136;
        tmp_d22 = cos(*pdVar17);
        *(float *)(tmp_i20 + 0x50) = (float)tmp_d22 * (float)tmp_ppu16[-0xba3f];
        if ((*(byte *)(tmp_pi10 + 0x4f) & 8) == 0) {
          *(uint32_t *)(tmp_pi10[1] + 0x54) = 0x3f000000;
        }
        else {
          *(uint32_t *)(tmp_pi10[1] + 0x54) = 0x3e800000;
        }
      }
    }
  }
  else {
    if (tmp_i20 != 0x29) {
      if (tmp_i20 - 0x2cU < 2) goto LAB_0002d099;
      goto LAB_0002d072;
    }
    *(int *)(tmp_pi10[1] + 0x48) = tmp_pi10[3];
    *(uint32_t *)(tmp_pi10[1] + 0x4c) = 100;
    *(uint32_t *)(tmp_pi10[1] + 0x50) = 0;
    tmp_i20 = tmp_pi10[1];
    *pdVar17 = (double)tmp_pi10[3];
    *(uint32_t *)((int)pdVar17 + -4) = 0x2d1ed;
    tmp_d22 = cos(*pdVar17);
    *(float *)(tmp_i20 + 0x54) =
         ABS((float)tmp_d22) * (float)tmp_ppu16[-0xb6c0] * (float)tmp_ppu16[-0xb6bf];
    if ((*(byte *)(tmp_pi10 + 0x4f) & 8) != 0) {
      *(float *)(tmp_pi10[1] + 0x54) = (float)tmp_ppu16[-0xba3f] * *(float *)(tmp_pi10[1] + 0x54);
    }
  }
LAB_0002c9a7:
  tmp_i20 = *(int *)(*tmp_pi10 + 0xa4);
  tmp_pu21 = tmp_ppu16[tmp_i20 * 0x12 + 0x837];
  if (tmp_pu21 != (uint8_t *)0x0) {
    tmp_i20 = *tmp_pi10 + tmp_i20 * 4;
    tmp_i12 = *(int *)(tmp_i20 + 0x49c);
    if ((tmp_i12 != 0) && ((int)tmp_pu21 <= tmp_i12)) {
      *(uint8_t **)(tmp_i20 + 0x49c) = tmp_pu21;
      if (((*(uint *)(cgs + *(int *)((int)pdVar17 + 0x34) + 0xf49008) & 0x20) == 0) &&
         (*(int *)(*tmp_pi10 + 0xa4) == 10)) {
        *(int *)(pdVar17 + 1) = *tmp_pi10;
LAB_0002cb49:
        *(int *)((int)pdVar17 + 4) = 0;
        *(uint32_t *)pdVar17 = 0x1e;
        *(uint32_t *)((int)pdVar17 + -4) = 0x2cb5d;
        BG_AddPredictableEventToPlayerstate();
        tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
        if ((*(byte *)(tmp_pi10 + 0x4a) & 0x20) == 0) {
          *(int *)(pdVar17 + 6) = 2000;
        }
        else {
          *(int *)(pdVar17 + 6) = 0x5dc;
        }
      }
      else if ((*(uint *)(cgs + *(int *)((int)pdVar17 + 0x34) + 0xf49008) & 0x40) == 0) {
        tmp_i20 = *(int *)(*tmp_pi10 + 0xa4);
        if ((tmp_i20 == 0x2e) || (tmp_i20 == 0x1d)) {
          *(int *)(pdVar17 + 1) = *tmp_pi10;
          goto LAB_0002cb49;
        }
      }
    }
  }
  *(float *)(*tmp_pi10 + 0x488) =
       (float)*(int *)((int)pdVar17 + 0x2c) * (float)tmp_ppu16[-0xb6e3] +
       *(float *)(*tmp_pi10 + 0x488);
  *(int *)(pdVar17 + 1) = 0x437f0000;
  *(int *)((int)pdVar17 + 4) = 0;
  *(int *)pdVar17 = *tmp_pi10 + 0x488;
  *(uint32_t *)((int)pdVar17 + -4) = 0x2ca43;
  nitrox_ClampFloat();
  tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
  tmp_i20 = *tmp_pi10;
  if (((*(byte *)(tmp_pi10 + 0x4f) & 8) != 0) && (*(int *)(tmp_i20 + 0xe4) == 4)) {
    *(float *)(tmp_i20 + 0x488) = (float)tmp_ppu16[-0xba3f] * *(float *)(tmp_i20 + 0x488);
    tmp_i20 = *tmp_pi10;
  }
  tmp_f24 = *(float *)(tmp_i20 + 0x488);
  *(uint16_t *)((int)pdVar17 + 0x6a) = inreg_FPUControlWord;
  tmp_i12 = *(int *)(pdVar17 + 6);
  *(ushort *)(pdVar17 + 0xd) = *(ushort *)((int)pdVar17 + 0x6a) | 0xc00;
  *(int *)(tmp_i20 + 0x48c) = (int)ROUND(tmp_f24);
  *(int *)(*tmp_pi10 + 0x2c) = *(int *)(*tmp_pi10 + 0x2c) + tmp_i12;
  tmp_i20 = *tmp_pi10;
  tmp_i12 = *(int *)(tmp_i20 + 0xa4);
  if (tmp_i12 == 9) goto LAB_0002cbfc;
  if (tmp_i12 < 10) {
    if (tmp_i12 != 1) {
      if (tmp_i12 != 4) goto LAB_0002cbaa;
LAB_0002cbfc:
      *(uint32_t *)(tmp_i20 + 0xa8) = 3;
      *(uint32_t *)(*tmp_pi10 + 0x394) = 0;
      tmp_i20 = *tmp_pi10;
      goto LAB_0002cbaa;
    }
    tmp_i12 = 1;
    if (*(int *)(tmp_i20 + 0xa8) == 6) goto LAB_0002cbfc;
  }
  else {
    if (((tmp_i12 == 0x30) || (tmp_i12 == 0x32)) || (tmp_i12 == 0x1c)) goto LAB_0002cbfc;
LAB_0002cbaa:
    tmp_i12 = *(int *)(tmp_i20 + 0xa4);
    if (tmp_i12 != 0x19) {
      if (tmp_i12 < 0x1a) {
        if (tmp_i12 != 4) {
          if (tmp_i12 < 5) {
            if (tmp_i12 != 1) {
              return;
            }
          }
          else if ((tmp_i12 != 9) && (tmp_i12 != 0xf)) {
            return;
          }
        }
      }
      else {
        if (tmp_i12 < 0x1b) {
          return;
        }
        if ((0x1c < tmp_i12) && (3 < tmp_i12 - 0x30U)) {
          return;
        }
      }
    }
  }
  *(int *)pdVar17 = tmp_i12;
  *(uint32_t *)((int)pdVar17 + -4) = 0x2cad5;
  tmp_i12 = BG_FindClipForWeapon();
  if (*(int *)(tmp_i20 + (tmp_i12 + 0xa4) * 4) != 0) {
    return;
  }
  tmp_i20 = **(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
  *(uint32_t *)pdVar17 = *(uint32_t *)(tmp_i20 + 0xa4);
  *(uint32_t *)((int)pdVar17 + -4) = 0x2cafa;
  tmp_i12 = BG_FindAmmoForWeapon();
  if (*(int *)(tmp_i20 + (tmp_i12 + 100) * 4) != 0) {
    return;
  }
  tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
  tmp_i20 = *tmp_pi10;
  tmp_i12 = *(int *)(tmp_i20 + 0xa4);
  if (tmp_i12 != 4) {
    if (tmp_i12 < 5) {
      if (tmp_i12 != 1) goto LAB_0002cb26;
    }
    else if ((tmp_i12 != 9) && (tmp_i12 != 0x30)) goto LAB_0002cb26;
  }
  *(int *)((int)pdVar17 + 4) = tmp_i12;
  *(int *)pdVar17 = tmp_i20 + 0x3d4;
  *(uint32_t *)((int)pdVar17 + -4) = 0x2cb90;
  COM_BitClear();
  tmp_pi10 = *(int **)(memoryPool + (int)(tmp_ppu16 + 0x5991f));
LAB_0002cb26:
  tmp_i20 = *tmp_pi10;
  *(int *)((int)pdVar17 + 4) = 0;
  *(uint32_t *)pdVar17 = 0x19;
  *(int *)(pdVar17 + 1) = tmp_i20;
  *(uint32_t *)((int)pdVar17 + -4) = 0x2cb40;
  BG_AddPredictableEventToPlayerstate();
  return;
}

bool PM_AltFiring(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *pm;
  if ((*(int *)(tmp_i1 + 0xa8) == 6) && ((param_1 != 0 || (0 < *(int *)(tmp_i1 + 0x30))))) {
    return *(int *)(tmp_i1 + 0xa4) == 1;
  }
  return false;
}

void PM_UpdateLean(int param_1,int param_2,int param_3)
{
  float tmp_f1;
  byte tmp_b2;
  float tmp_f3;
  uint tmp_u4;
  int tmp_i5;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  uint32_t local_84;
  uint32_t local_80;
  uint32_t local_7c;
  uint32_t local_78;
  uint32_t local_74;
  uint32_t local_70;
  float local_6c;
  float local_68;
  float local_64;
  uint32_t local_60;
  uint32_t local_5c;
  float local_58;
  uint8_t local_54 [8];
  float local_4c;
  
  tmp_i5 = 0;
  tmp_b2 = *(byte *)(param_2 + 5);
  if (((tmp_b2 & 0x30) != 0) &&
     ((*(int *)(param_1 + 4) == 2 ||
      ((*(char *)(param_2 + 0x14) == '\0' && (*(char *)(param_2 + 0x16) < '\x01')))))) {
    tmp_u4 = tmp_b2 >> 4 & 1;
    if ((tmp_b2 & 0x20) == 0) {
      tmp_i5 = -tmp_u4;
    }
    else {
      tmp_i5 = 1 - tmp_u4;
    }
  }
  tmp_u4 = *(uint *)(param_1 + 0x68);
  if ((tmp_u4 & 0x8020) != 0) {
    tmp_i5 = 0;
  }
  if (((tmp_u4 & 0x80) != 0) && ((cgs[0x2038e69] & 1) == 0)) {
    tmp_i5 = 0;
  }
  if ((tmp_u4 & 1) != 0) {
    tmp_i5 = 0;
  }
  if ((tmp_u4 & 0x800000) != 0) {
    tmp_i5 = 0;
  }
  if ((((*(int *)(param_1 + 0xa8) == 5) && (*(int *)(param_1 + 0xa4) == 0xf)) ||
      ((tmp_u4 & 0x80000) != 0)) || (*(int *)(param_1 + 0xa4) == 0x2a)) {
    tmp_f1 = *(float *)(param_1 + 0x3c);
  }
  else {
    tmp_f1 = *(float *)(param_1 + 0x3c);
    if (tmp_i5 != 0) {
      if (tmp_i5 == 1) {
        if (tmp_f1 < 28.0) {
          tmp_f1 = ((float)g_unk_00f3e308 / 200.0) * 28.0 + tmp_f1;
        }
        if (28.0 < tmp_f1) {
          local_58 = 14.0;
          tmp_f1 = 28.0;
        }
        else {
LAB_0002d52c:
          local_58 = tmp_f1 * 0.5;
        }
      }
      else {
        if (-28.0 < tmp_f1) {
          tmp_f1 = tmp_f1 - ((float)g_unk_00f3e308 / 200.0) * 28.0;
        }
        if (-28.0 <= tmp_f1) goto LAB_0002d52c;
        local_58 = -14.0;
        tmp_f1 = -28.0;
      }
      *(float *)(param_1 + 0x3c) = tmp_f1;
      local_9c = *(float *)(param_1 + 0x14);
      local_98 = *(float *)(param_1 + 0x18);
      local_94 = (float)*(int *)(param_1 + 0xbc) + *(float *)(param_1 + 0x1c);
      local_60 = *(uint32_t *)(param_1 + 0xb0);
      local_5c = *(uint32_t *)(param_1 + 0xb4);
      local_58 = local_58 + *(float *)(param_1 + 0xb8);
      AngleVectors(&local_60,0,&local_6c,0);
      local_84 = 0xc1000000;
      local_80 = 0xc1000000;
      local_7c = 0xc0e00000;
      local_78 = 0x41000000;
      local_74 = 0x41000000;
      local_70 = 0x40800000;
      local_90 = local_6c * tmp_f1 + local_9c;
      local_8c = local_68 * tmp_f1 + local_98;
      local_88 = tmp_f1 * local_64 + local_94;
      if (pm == 0) {
        (**(void **)(param_3 + 0x118))
                  (local_54,&local_9c,&local_84,&local_78,&local_90,*(uint32_t *)(param_1 + 0xa0),
                   0x2010001);
      }
      else {
        (**(void **)(pm + 0x118))
                  (local_54,&local_9c,&local_84,&local_78,&local_90,*(uint32_t *)(param_1 + 0xa0),
                   0x2010001);
      }
      tmp_f1 = *(float *)(param_1 + 0x3c) * local_4c;
      *(float *)(param_1 + 0x3c) = tmp_f1;
      goto LAB_0002d6a5;
    }
  }
  if (tmp_f1 <= 0.0) {
    if ((tmp_f1 < 0.0) && (tmp_f1 = ((float)g_unk_00f3e308 / 300.0) * 28.0 + tmp_f1, 0.0 < tmp_f1)) {
      tmp_f1 = 0.0;
    }
  }
  else {
    tmp_f3 = tmp_f1 - ((float)g_unk_00f3e308 / 300.0) * 28.0;
    tmp_f1 = 0.0;
    if (0.0 <= tmp_f3) {
      tmp_f1 = tmp_f3;
    }
  }
  tmp_i5 = 0;
  *(float *)(param_1 + 0x3c) = tmp_f1;
LAB_0002d6a5:
  if ((tmp_f1 != 0.0) && (*(int *)(param_1 + 4) != 2)) {
    *(uint8_t *)(param_2 + 0x15) = 0;
  }
  *(int *)(param_1 + 0x398) = tmp_i5;
  return;
}

void PM_UpdateFlyLean(int param_1,float param_2)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  
  if (param_2 != 0.0) {
    if (param_2 < -70.0) {
      tmp_i3 = 1 - (uint)(70.0 < param_2);
    }
    else {
      tmp_i3 = -(uint)(70.0 < param_2);
    }
    if ((*(uint *)(param_1 + 0x68) & 0x8020) == 0) {
      tmp_f1 = *(float *)(param_1 + 0xb8);
      if (tmp_i3 != 0) {
        if (tmp_i3 == 1) {
          if (tmp_f1 < 20.0) {
            tmp_f1 = ((float)g_unk_00f3e308 / 500.0) * 20.0 + tmp_f1;
          }
          if (20.0 < tmp_f1) {
            tmp_f1 = 20.0;
          }
          *(float *)(param_1 + 0xb8) = tmp_f1;
          return;
        }
        if (-20.0 < tmp_f1) {
          tmp_f1 = tmp_f1 - ((float)g_unk_00f3e308 / 500.0) * 20.0;
        }
        tmp_f2 = -20.0;
        if (-20.0 <= tmp_f1) {
          tmp_f2 = tmp_f1;
        }
        *(float *)(param_1 + 0xb8) = tmp_f2;
        return;
      }
      goto LAB_0002d818;
    }
  }
  tmp_f1 = *(float *)(param_1 + 0xb8);
LAB_0002d818:
  if (tmp_f1 <= 0.0) {
    if ((tmp_f1 < 0.0) && (tmp_f1 = ((float)g_unk_00f3e308 / 200.0) * 20.0 + tmp_f1, 0.0 < tmp_f1)) {
      tmp_f1 = 0.0;
    }
  }
  else {
    tmp_f2 = tmp_f1 - ((float)g_unk_00f3e308 / 200.0) * 20.0;
    tmp_f1 = 0.0;
    if (0.0 <= tmp_f2) {
      tmp_f1 = tmp_f2;
    }
  }
  *(float *)(param_1 + 0xb8) = tmp_f1;
  return;
}

void PM_UpdateViewAngles(int param_1,int param_2,int param_3,uint32_t param_4,uint32_t param_5)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint32_t tmp_u4;
  float tmp_f5;
  float tmp_f6;
  short tmp_s7;
  int tmp_i8;
  int tmp_i9;
  long double tmp_l10;
  long double tmp_l11;
  double tmp_d12;
  uint64_t in_stack_ffffff54;
  double __x;
  uint32_t tmp_u13;
  short local_74;
  uint8_t local_54 [8];
  float local_4c;
  
  tmp_u13 = (uint32_t)((ulonglong)in_stack_ffffff54 >> 0x20);
  if ((*(int *)(param_1 + 4) == 5) || ((*(byte *)(param_1 + 0xd) & 0x80) != 0)) {
    *(uint *)(param_1 + 0x44) =
         ((int)ROUND((*(float *)(param_1 + 0xb0) * 65536.0) / 360.0) & 0xffffU) -
         *(int *)(param_3 + 8);
    *(uint *)(param_1 + 0x48) =
         ((int)ROUND((*(float *)(param_1 + 0xb4) * 65536.0) / 360.0) & 0xffffU) -
         *(int *)(param_3 + 0xc);
    *(uint *)(param_1 + 0x4c) =
         ((int)ROUND((*(float *)(param_1 + 0xb8) * 65536.0) / 360.0) & 0xffffU) -
         *(int *)(param_3 + 0x10);
    return;
  }
  if (*(int *)(param_1 + 4) != 2) {
    if (*(int *)(param_1 + 0xd0) < 1) {
      tmp_i9 = *(int *)(param_3 + 0xc);
      tmp_i8 = (int)(short)((short)*(uint32_t *)(param_1 + 0x48) + (short)tmp_i9);
      if ((*(byte *)(param_1 + 0x6a) & 0x80) == 0) goto LAB_0002dadf;
    }
    else {
      if ((*(byte *)(param_1 + 0x6a) & 0x80) == 0) goto LAB_0002db10;
      tmp_i9 = *(int *)(param_3 + 0xc);
      tmp_i8 = (int)(short)((short)*(uint32_t *)(param_1 + 0x48) + (short)tmp_i9);
    }
    if (tmp_i8 < 0x3e81) {
      if (tmp_i8 < -16000) {
        *(int *)(param_1 + 0x48) = -16000 - tmp_i9;
        tmp_i8 = -16000;
      }
    }
    else {
      *(int *)(param_1 + 0x48) = 16000 - tmp_i9;
      tmp_i8 = 16000;
    }
LAB_0002dadf:
    *(int *)(param_1 + 0xd8) = tmp_i8;
    *(uint32_t *)(param_3 + 0x10) = 0;
    *(uint32_t *)(param_1 + 0xb8) = 0;
    *(uint32_t *)(param_3 + 8) = 0;
    *(uint32_t *)(param_1 + 0xb0) = 0;
    return;
  }
LAB_0002db10:
  tmp_i9 = *(int *)(param_3 + 8);
  tmp_f1 = *(float *)(param_1 + 0xb0);
  tmp_f2 = *(float *)(param_1 + 0xb4);
  tmp_s7 = (short)*(uint32_t *)(param_1 + 0x44) + (short)tmp_i9;
  if (tmp_s7 < 0x3e81) {
    if (tmp_s7 < -16000) {
      *(int *)(param_1 + 0x44) = -16000 - tmp_i9;
      tmp_s7 = -16000;
    }
  }
  else {
    *(int *)(param_1 + 0x44) = 16000 - tmp_i9;
    tmp_s7 = 16000;
  }
  *(float *)(param_1 + 0xb0) = (float)tmp_s7 * 0.005493164;
  tmp_u4 = *(uint32_t *)(param_1 + 0x48);
  local_74 = (short)*(uint32_t *)(param_3 + 0xc) + (short)tmp_u4;
  *(float *)(param_1 + 0xb4) = (float)local_74 * 0.005493164;
  local_74 = (short)*(uint32_t *)(param_3 + 0x10) + (short)*(uint32_t *)(param_1 + 0x4c);
  *(float *)(param_1 + 0xb8) = (float)local_74 * 0.005493164;
  if ((*(uint *)(param_1 + 0x68) & 0x8020) == 0) {
    if (*(int *)(param_1 + 0xa4) == 0x2a) {
      tmp_f3 = *(float *)(param_1 + 0xb4);
      tmp_f5 = tmp_f3 - tmp_f2;
      tmp_f6 = tmp_f3;
      if (180.0 < tmp_f5) {
        tmp_f6 = tmp_f3 - 360.0;
        tmp_f5 = tmp_f6 - tmp_f2;
      }
      if (tmp_f5 < -180.0) {
        tmp_f6 = tmp_f6 + 360.0;
      }
      if (tmp_f6 <= tmp_f2) {
        if ((tmp_f6 < tmp_f2) && (g_unk_00f3e304 * 60.0 < tmp_f2 - tmp_f6)) {
          tmp_f3 = tmp_f2 - g_unk_00f3e304 * 60.0;
          goto LAB_0002dfec;
        }
      }
      else if (g_unk_00f3e304 * 60.0 < tmp_f6 - tmp_f2) {
        tmp_f3 = g_unk_00f3e304 * 60.0 + tmp_f2;
LAB_0002dfec:
        *(float *)(param_1 + 0xb4) = tmp_f3;
        *(uint *)(param_1 + 0x48) =
             ((int)ROUND((tmp_f3 * 65536.0) / 360.0) & 0xffffU) - *(int *)(param_3 + 0xc);
      }
      tmp_f2 = *(float *)(param_1 + 0xb0);
      tmp_f5 = tmp_f2 - tmp_f1;
      if (180.0 < tmp_f5) {
        tmp_f2 = tmp_f2 - 360.0;
        tmp_f5 = tmp_f2 - tmp_f1;
      }
      if (tmp_f5 < -180.0) {
        tmp_f2 = tmp_f2 + 360.0;
      }
      if (tmp_f2 <= tmp_f1) {
        if ((tmp_f2 < tmp_f1) && (g_unk_00f3e304 * 60.0 < tmp_f1 - tmp_f2)) {
          tmp_f1 = tmp_f1 - g_unk_00f3e304 * 60.0;
          goto LAB_0002e083;
        }
      }
      else if (g_unk_00f3e304 * 60.0 < tmp_f2 - tmp_f1) {
        tmp_f1 = g_unk_00f3e304 * 60.0 + tmp_f1;
LAB_0002e083:
        *(float *)(param_1 + 0xb0) = tmp_f1;
        *(uint *)(param_1 + 0x44) =
             ((int)ROUND((tmp_f1 * 65536.0) / 360.0) & 0xffffU) - *(int *)(param_3 + 8);
      }
      tmp_f1 = *(float *)(param_2 + 0x40);
      tmp_f3 = tmp_f3 - tmp_f1;
      if (tmp_f3 <= 180.0) {
        if (tmp_f3 < -180.0) {
          tmp_f3 = tmp_f3 + 360.0;
        }
      }
      else {
        tmp_f3 = tmp_f3 - 360.0;
      }
      if (30.0 < tmp_f3) {
        tmp_f1 = tmp_f1 + 30.0;
      }
      else {
        if (-30.0 <= tmp_f3) goto LAB_0002e12e;
        tmp_f1 = tmp_f1 - 30.0;
      }
      tmp_l10 = (long double)AngleNormalize180(tmp_f1);
      *(float *)(param_1 + 0xb4) = (float)tmp_l10;
      *(uint *)(param_1 + 0x48) =
           ((int)ROUND((tmp_l10 * (long double)65536.0) / (long double)360.0) & 0xffffU) -
           *(int *)(param_3 + 0xc);
LAB_0002e12e:
      tmp_f1 = *(float *)(param_2 + 0x3c);
      tmp_f2 = *(float *)(param_1 + 0xb0) - tmp_f1;
      if (tmp_f2 <= 180.0) {
        if (tmp_f2 < -180.0) {
          tmp_f2 = tmp_f2 + 360.0;
        }
      }
      else {
        tmp_f2 = tmp_f2 - 360.0;
      }
      if (20.0 < tmp_f2) {
        tmp_f1 = tmp_f1 + 20.0;
      }
      else {
        if (-30.0 <= tmp_f2) {
          return;
        }
        tmp_f1 = tmp_f1 - 30.0;
      }
      tmp_l10 = (long double)AngleNormalize180(tmp_f1);
      *(float *)(param_1 + 0xb0) = (float)tmp_l10;
      *(uint *)(param_1 + 0x44) =
           ((int)ROUND((tmp_l10 * (long double)65536.0) / (long double)360.0) & 0xffffU) -
           *(int *)(param_3 + 8);
      return;
    }
    if ((*(uint *)(param_1 + 0x68) & 0x880001) == 0) {
      return;
    }
    if (*(int *)(param_1 + 0xa4) == 0x2e) {
      tmp_f1 = *(float *)(param_2 + 0x40);
      tmp_f3 = *(float *)(param_1 + 0xb4) - tmp_f1;
      if (tmp_f3 <= 180.0) {
        if (tmp_f3 < -180.0) {
          tmp_f3 = tmp_f3 + 360.0;
        }
      }
      else {
        tmp_f3 = tmp_f3 - 360.0;
      }
      if (20.0 < tmp_f3) {
        tmp_f1 = tmp_f1 + 20.0;
      }
      else {
        if (-20.0 <= tmp_f3) {
          tmp_f1 = 20.0;
          goto LAB_0002dd82;
        }
        tmp_f1 = tmp_f1 - 20.0;
      }
      tmp_l10 = (long double)AngleNormalize180(tmp_f1);
      *(float *)(param_1 + 0xb4) = (float)tmp_l10;
      tmp_f1 = 20.0;
      *(uint *)(param_1 + 0x48) =
           ((int)ROUND((tmp_l10 * (long double)65536.0) / (long double)360.0) & 0xffffU) -
           *(int *)(param_3 + 0xc);
    }
    else {
      tmp_f1 = 40.0;
    }
LAB_0002dd82:
    tmp_f3 = *(float *)(param_2 + 0x3c);
    tmp_f5 = *(float *)(param_1 + 0xb0) - tmp_f3;
    if (tmp_f5 <= 180.0) {
      if (tmp_f5 < -180.0) {
        tmp_f5 = tmp_f5 + 360.0;
      }
    }
    else {
      tmp_f5 = tmp_f5 - 360.0;
    }
    if (tmp_f1 < tmp_f5) {
      tmp_f3 = tmp_f1 + tmp_f3;
LAB_0002e2c2:
      tmp_l10 = (long double)AngleNormalize180(tmp_f3);
      *(float *)(param_1 + 0xb0) = (float)tmp_l10;
      *(uint *)(param_1 + 0x44) =
           ((int)ROUND((tmp_l10 * (long double)65536.0) / (long double)360.0) & 0xffffU) -
           *(int *)(param_3 + 8);
    }
    else if (tmp_f5 < -tmp_f1) {
      tmp_f3 = tmp_f3 - tmp_f1;
      goto LAB_0002e2c2;
    }
    if (tmp_f2 == *(float *)(param_1 + 0xb4)) {
      return;
    }
    *(uint32_t *)(param_1 + 0x48) = tmp_u4;
    PM_TraceLegs(local_54,param_2 + 0x38,param_1 + 0x14,param_1 + 0x14,0,param_1 + 0xb0,
                 *(uint32_t *)(pm + 0x118),*(uint32_t *)(param_1 + 0xa0),param_5);
    tmp_l10 = (long double)tmp_f2;
    if (1.0 <= local_4c) {
      return;
    }
    *(float *)(param_1 + 0xb4) = tmp_f2;
    goto LAB_0002dd18;
  }
  tmp_f1 = *(float *)(param_1 + 0xb4);
  tmp_f3 = tmp_f1 - tmp_f2;
  tmp_f5 = tmp_f1;
  if (180.0 < tmp_f3) {
    tmp_f5 = tmp_f1 - 360.0;
    tmp_f3 = tmp_f5 - tmp_f2;
  }
  if (tmp_f3 < -180.0) {
    tmp_f5 = tmp_f5 + 360.0;
  }
  if (tmp_f5 <= tmp_f2) {
    if ((tmp_f5 < tmp_f2) && (g_unk_00f3e304 * 300.0 < tmp_f2 - tmp_f5)) {
      tmp_f1 = tmp_f2 - g_unk_00f3e304 * 300.0;
      goto LAB_0002dc1b;
    }
  }
  else if (g_unk_00f3e304 * 300.0 < tmp_f5 - tmp_f2) {
    tmp_f1 = g_unk_00f3e304 * 300.0 + tmp_f2;
LAB_0002dc1b:
    *(float *)(param_1 + 0xb4) = tmp_f1;
    *(uint *)(param_1 + 0x48) =
         ((int)ROUND((tmp_f1 * 65536.0) / 360.0) & 0xffffU) - *(int *)(param_3 + 0xc);
  }
  tmp_f2 = *(float *)(param_2 + 0x18);
  if ((*(byte *)(param_1 + 0x69) & 0x80) == 0) {
    tmp_f1 = tmp_f2 * 0.5;
    tmp_l10 = (long double)*(float *)(param_2 + 0x20);
  }
  else {
    tmp_l10 = (long double)AngleNormalize180(*(float *)(param_2 + 0x24) - tmp_f1);
    __x = (double)(((long double)3.141592653589793 * tmp_l10) / (long double)180.0);
    tmp_d12 = cos(__x);
    tmp_u13 = (uint32_t)((ulonglong)__x >> 0x20);
    tmp_l10 = (long double)AngleNormalize180(0.0 - *(float *)(param_2 + 0x20));
    tmp_l10 = (long double)AngleNormalize360((float)((long double)(float)tmp_d12 * tmp_l10));
    tmp_l10 = -tmp_l10;
    *(float *)(param_2 + 0x20) = (float)tmp_l10;
    tmp_f2 = 50.0;
    tmp_f1 = 14.0;
  }
  tmp_l10 = (long double)AngleNormalize180((float)((long double)*(float *)(param_1 + 0xb0) - tmp_l10));
  if ((long double)tmp_f1 < tmp_l10) {
    tmp_l10 = (long double)tmp_f1 + (long double)*(float *)(param_2 + 0x20);
LAB_0002dec9:
    tmp_l10 = (long double)AngleNormalize180(CONCAT44(tmp_u13,(float)tmp_l10));
    *(float *)(param_1 + 0xb0) = (float)tmp_l10;
    *(uint *)(param_1 + 0x44) =
         ((int)ROUND((tmp_l10 * (long double)65536.0) / (long double)360.0) & 0xffffU) -
         *(int *)(param_3 + 8);
  }
  else if (tmp_l10 < -(long double)tmp_f2) {
    tmp_l10 = (long double)*(float *)(param_2 + 0x20) - (long double)tmp_f2;
    goto LAB_0002dec9;
  }
  if ((*(byte *)(param_1 + 0x69) & 0x80) != 0) {
    return;
  }
  tmp_f1 = *(float *)(param_2 + 0x1c);
  tmp_l10 = (long double)AngleNormalize180(*(float *)(param_1 + 0xb4) - *(float *)(param_2 + 0x24));
  tmp_l11 = (long double)tmp_f1;
  if (tmp_l11 < tmp_l10) {
    tmp_l10 = (long double)AngleNormalize180((float)(tmp_l11 + (long double)*(float *)(param_2 + 0x24)))
    ;
    *(float *)(param_1 + 0xb4) = (float)tmp_l10;
  }
  else {
    if (-tmp_l11 <= tmp_l10) {
      return;
    }
    tmp_l10 = (long double)AngleNormalize180((float)((long double)*(float *)(param_2 + 0x24) - tmp_l11))
    ;
    *(float *)(param_1 + 0xb4) = (float)tmp_l10;
  }
LAB_0002dd18:
  *(uint *)(param_1 + 0x48) =
       ((int)ROUND((tmp_l10 * (long double)65536.0) / (long double)360.0) & 0xffffU) -
       *(int *)(param_3 + 0xc);
  return;
}

void PM_CheckLadderMove(void)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  uint tmp_u4;
  int *tmp_pi5;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  int local_50;
  int local_4c;
  uint32_t local_48;
  uint8_t local_44 [8];
  float local_3c;
  float local_2c;
  float local_28;
  float local_24;
  byte local_18;
  
  tmp_pi5 = pm;
  if (*(int *)(*pm + 0x10) != 0) {
    return;
  }
  if (g_unk_00f3e30c == 0) {
    tmp_f1 = -48.0;
    tmp_f2 = 48.0;
  }
  else {
    tmp_f1 = -1.0;
    tmp_f2 = 1.0;
  }
  tmp_u4 = *(uint *)(*pm + 0xc);
  g_unk_00f3e36c = 0;
  ladderforward = 0;
  *(uint *)(*pm + 0xc) = *(uint *)(*pm + 0xc) & 0xfffffffb;
  tmp_i3 = *tmp_pi5;
  if (*(int *)(tmp_i3 + 0xd0) < 1) {
    *(uint32_t *)(tmp_i3 + 0x50) = 0x3ff;
    g_unk_00f3e30c = 0;
    g_unk_00f3e310 = 0;
    return;
  }
  if ((*(byte *)(tmp_i3 + 0x6a) & 8) != 0) {
    return;
  }
  local_5c = pml;
  tmp_u4 = tmp_u4 >> 2;
  local_58 = g_unk_00f3e2e4;
  local_54 = 0.0;
  VectorNormalize(&local_5c);
  local_68 = local_5c * tmp_f2 + *(float *)(*pm + 0x14);
  local_64 = local_58 * tmp_f2 + *(float *)(*pm + 0x18);
  local_60 = local_54 * tmp_f2 + *(float *)(*pm + 0x1c);
  (*(void *)pm[0x46])(local_44,*pm + 0x14,pm + 0x3a,pm + 0x3d,&local_68,*(uint32_t *)(*pm + 0xa0),
                      pm[0x11]);
  tmp_pi5 = pm;
  if ((1.0 <= local_3c) || ((local_18 & 8) == 0)) {
    if (g_unk_00f3e36c != 0) goto LAB_0002e6b9;
  }
  else {
    g_unk_00f3e36c = 1;
LAB_0002e6b9:
    laddervec = local_2c;
    g_unk_00f3e378 = local_28;
    g_unk_00f3e37c = local_24;
    if ((g_unk_00f3e30c != 0) || (tmp_f2 * local_3c <= 1.0)) {
      *(uint *)(*pm + 0xc) = *(uint *)(*pm + 0xc) | 4;
LAB_0002e712:
      if (g_unk_00f3e36c == 0) goto LAB_0002e623;
      if ((g_unk_00f3e30c == 0) || ('\0' < (char)tmp_pi5[8])) goto LAB_0002e72e;
    }
    else {
      g_unk_00f3e36c = 0;
      local_48 = 0xbf800000;
      local_50 = pm[0x3a];
      local_4c = pm[0x3b];
      local_68 = local_2c * tmp_f1 + *(float *)(*pm + 0x14);
      local_64 = local_28 * tmp_f1 + *(float *)(*pm + 0x18);
      local_60 = local_24 * tmp_f1 + *(float *)(*pm + 0x1c);
      (*(void *)pm[0x46])(local_44,*pm + 0x14,&local_50,pm + 0x3d,&local_68,
                          *(uint32_t *)(*pm + 0xa0),pm[0x11]);
      tmp_pi5 = pm;
      if ((local_3c < 1.0) && ((local_18 & 8) != 0)) {
        g_unk_00f3e36c = 1;
        ladderforward = 1;
        *(uint *)(*pm + 0xc) = *(uint *)(*pm + 0xc) | 4;
        goto LAB_0002e712;
      }
    }
    g_unk_00f3e36c = 0;
  }
LAB_0002e623:
  if ((tmp_u4 & 1) == 0) {
    return;
  }
  if (*(float *)(*pm + 0x28) <= 0.0) {
    return;
  }
  BG_AnimScriptEvent(*pm,*(uint32_t *)(pm[2] + 0x7f0),10,0,0);
LAB_0002e72e:
  if ((((byte)tmp_u4 & 1) < (g_unk_00f3e36c != 0)) && (*(float *)(*pm + 0x28) < 0.0)) {
    BG_AnimScriptEvent(*pm,*(uint32_t *)(pm[2] + 0x7f0),9,0,0);
  }
  return;
}

void PM_LadderMove(void)
{
  float tmp_f1;
  float tmp_f2;
  int *tmp_pi3;
  int tmp_i4;
  long double tmp_l5;
  long double tmp_l6;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_pi3 = pm;
  local_10 = 2.67087e-40;
  if (ladderforward != 0) {
    local_30 = laddervec * -200.0;
    local_2c = g_unk_00f3e378 * -200.0;
    local_28 = g_unk_00f3e37c * -200.0;
    *(float *)(*pm + 0x20) = local_30;
    *(float *)(*tmp_pi3 + 0x24) = local_2c;
  }
  tmp_f1 = (g_unk_00f3e2e8 + 0.5) * 2.5;
  if (tmp_f1 <= 1.0) {
    tmp_f2 = -1.0;
    if (-1.0 <= tmp_f1) {
      tmp_f2 = tmp_f1;
    }
  }
  else {
    tmp_f2 = 1.0;
  }
  g_unk_00f3e2e8 = 0.0;
  g_unk_00f3e2f4 = 0;
  VectorNormalize(&pml);
  VectorNormalize(&g_unk_00f3e2ec);
  tmp_l5 = (long double)PM_CmdScale_isra_0(*(uint8_t *)((int)pm + 0x22));
  local_28 = 0.0;
  local_2c = 0.0;
  local_30 = 0.0;
  if ((char)pm[8] != '\0') {
    local_28 = (float)((long double)(short)(char)pm[8] * (long double)0.9 * (long double)tmp_f2 * tmp_l5)
    ;
  }
  if (*(char *)((int)pm + 0x21) != '\0') {
    vectoangles(&laddervec,&local_18);
    AngleVectors(&local_18,0,&local_24,0);
    if (g_unk_00f3e37c * g_unk_00f3e2e8 + g_unk_00f3e378 * g_unk_00f3e2e4 + laddervec * pml < 0.0) {
      VectorInverse(&local_24);
    }
    tmp_f1 = (float)(short)*(char *)((int)pm + 0x21) * (float)tmp_l5 * 0.5;
    local_30 = tmp_f1 * local_24 + local_30;
    local_2c = tmp_f1 * local_20 + local_2c;
    local_28 = tmp_f1 * local_1c + local_28;
  }
  PM_Friction();
  tmp_pi3 = pm;
  tmp_i4 = *pm;
  if ((*(float *)(tmp_i4 + 0x20) < 1.0) && (-1.0 < *(float *)(tmp_i4 + 0x20))) {
    *(uint32_t *)(tmp_i4 + 0x20) = 0;
    tmp_i4 = *tmp_pi3;
  }
  if ((*(float *)(tmp_i4 + 0x24) < 1.0) && (-1.0 < *(float *)(tmp_i4 + 0x24))) {
    *(uint32_t *)(tmp_i4 + 0x24) = 0;
  }
  tmp_l5 = (long double)VectorNormalize2(&local_30,&local_18);
  tmp_pi3 = pm;
  tmp_i4 = *pm;
  tmp_l6 = tmp_l5 - ((long double)*(float *)(tmp_i4 + 0x28) * (long double)local_10 +
                  (long double)*(float *)(tmp_i4 + 0x24) * (long double)local_14 +
                  (long double)*(float *)(tmp_i4 + 0x20) * (long double)local_18);
  if ((long double)0 < tmp_l6) {
    tmp_l5 = (long double)pm_accelerate * (long double)g_unk_00f3e304 * tmp_l5;
    if (tmp_l6 < tmp_l5) {
      tmp_l5 = tmp_l6;
      if (*(int *)(tmp_i4 + 0x50) != 0x3ff) goto LAB_0002ea62;
    }
    else {
      if (*(int *)(tmp_i4 + 0x50) != 0x3ff) {
LAB_0002ea62:
        tmp_l5 = (long double)(float)(((long double)1 / (long double)*(float *)(tmp_i4 + 0x418)) * tmp_l5)
        ;
      }
      if (tmp_l6 < tmp_l5) {
        tmp_l5 = tmp_l6;
      }
    }
    *(float *)(tmp_i4 + 0x20) =
         (float)((long double)local_18 * tmp_l5 + (long double)*(float *)(tmp_i4 + 0x20));
    *(float *)(*tmp_pi3 + 0x24) =
         (float)((long double)local_14 * tmp_l5 + (long double)*(float *)(*tmp_pi3 + 0x24));
    *(float *)(*tmp_pi3 + 0x28) =
         (float)(tmp_l5 * (long double)local_10 + (long double)*(float *)(*tmp_pi3 + 0x28));
  }
  if (local_28 == 0.0) {
    tmp_i4 = *tmp_pi3;
    tmp_f1 = *(float *)(tmp_i4 + 0x28);
    tmp_f2 = (float)*(int *)(tmp_i4 + 0x38) * g_unk_00f3e304;
    if (tmp_f1 <= 0.0) {
      *(float *)(tmp_i4 + 0x28) = tmp_f2 + tmp_f1;
      tmp_i4 = *tmp_pi3;
      if (*(float *)(tmp_i4 + 0x28) <= 0.0) goto LAB_0002eb20;
    }
    else {
      *(float *)(tmp_i4 + 0x28) = tmp_f1 - tmp_f2;
      tmp_i4 = *tmp_pi3;
      if (0.0 <= *(float *)(tmp_i4 + 0x28)) goto LAB_0002eb20;
    }
    *(uint32_t *)(tmp_i4 + 0x28) = 0;
  }
LAB_0002eb20:
  PM_StepSlideMove(0);
  *(uint32_t *)(*pm + 100) = 0;
  return;
}

void PM_Sprint(void)
{
  float tmp_f1;
  int *tmp_pi2;
  int tmp_i3;
  int local_c;
  
  tmp_pi2 = pm;
  if ((*(byte *)(pm + 4) & 0x20) == 0) {
    tmp_i3 = *pm;
  }
  else {
    tmp_i3 = *pm;
    if ((((short)pm[8] != 0) && ((*(byte *)(tmp_i3 + 0xc) & 1) == 0)) &&
       ((*(byte *)(tmp_i3 + 0x6a) & 8) == 0)) {
      if (*(int *)(tmp_i3 + 0x17c) == 0) {
        if (*(int *)(tmp_i3 + 0x160) == 0) {
          if ((*(byte *)(pm + 0x49) & 0x20) == 0) {
            tmp_f1 = 5000.0;
          }
          else {
            tmp_f1 = 4000.0;
          }
          *(int *)(pm[1] + 0x10) = (int)ROUND((float)*(int *)(pm[1] + 0x10) - tmp_f1 * g_unk_00f3e304);
        }
        else {
          *(int *)(tmp_i3 + 0x160) = *(int *)(tmp_i3 + 0x160) + -0x32;
          *(int *)(tmp_pi2[1] + 0x10) = *(int *)(tmp_pi2[1] + 0x10) + 10;
          if (20000.0 < (float)*(int *)(tmp_pi2[1] + 0x10)) {
            *(uint32_t *)(tmp_pi2[1] + 0x10) = 20000;
          }
          if (*(int *)(*tmp_pi2 + 0x160) < 0) {
            *(uint32_t *)(*tmp_pi2 + 0x160) = 0;
          }
        }
      }
      else {
        *(uint32_t *)(pm[1] + 0x10) = 20000;
      }
      if (*(int *)(tmp_pi2[1] + 0x10) < 0) {
        *(uint32_t *)(tmp_pi2[1] + 0x10) = 0;
      }
      if (*(int *)(*tmp_pi2 + 0x474) != 0) {
        return;
      }
      *(uint32_t *)(*tmp_pi2 + 0x474) = 1;
      return;
    }
  }
  if (*(int *)(tmp_i3 + 0x17c) == 0) {
    if (*(int *)(tmp_i3 + 0x160) == 0) {
      if ((*(byte *)(pm + 0x49) & 4) == 0) {
        tmp_f1 = 500.0;
      }
      else {
        tmp_f1 = 800.0;
      }
      *(int *)(pm[1] + 0x10) = (int)ROUND(g_unk_00f3e304 * tmp_f1 + (float)*(int *)(pm[1] + 0x10));
      tmp_i3 = tmp_pi2[1];
      local_c = *(int *)(tmp_i3 + 0x10);
      if (5000 < local_c) {
        *(int *)(tmp_i3 + 0x10) = (int)ROUND(tmp_f1 * g_unk_00f3e304 + (float)local_c);
        tmp_i3 = tmp_pi2[1];
        local_c = *(int *)(tmp_i3 + 0x10);
      }
    }
    else {
      *(int *)(pm[1] + 0x10) = *(int *)(pm[1] + 0x10) + 10;
      tmp_i3 = tmp_pi2[1];
      local_c = *(int *)(tmp_i3 + 0x10);
    }
  }
  else {
    *(uint32_t *)(pm[1] + 0x10) = 20000;
    tmp_i3 = tmp_pi2[1];
    local_c = *(int *)(tmp_i3 + 0x10);
  }
  if (20000.0 < (float)local_c) {
    *(uint32_t *)(tmp_i3 + 0x10) = 20000;
  }
  *(uint32_t *)(*tmp_pi2 + 0x474) = 0;
  return;
}

void PM_CheckAttack(void)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  
  tmp_i1 = *pm;
  if (((*(byte *)(tmp_i1 + 0xd) & 2) == 0) && (*(int *)(tmp_i1 + 4) != 5)) {
    tmp_i1 = *(int *)(tmp_i1 + 0xa4);
    tmp_i2 = BG_FindClipForWeapon(tmp_i1);
    if ((tmp_i1 - 0x2cU < 2) || (tmp_i1 - 0x22U < 2)) {
      tmp_i5 = *pm;
      tmp_u3 = BG_AkimboSidearm(tmp_i1);
      tmp_i4 = BG_FindClipForWeapon(tmp_u3);
      tmp_u3 = *(uint32_t *)(tmp_i5 + (tmp_i4 + 0xa4) * 4);
      tmp_i5 = *pm;
      tmp_i4 = BG_FindClipForWeapon(tmp_i1);
      tmp_i5 = BG_AkimboFireSequence(tmp_i1,*(uint32_t *)(tmp_i5 + (tmp_i4 + 0xa4) * 4),tmp_u3);
      if (tmp_i5 == 0) {
        tmp_i2 = BG_AkimboSidearm(tmp_i1);
      }
    }
    tmp_i1 = *pm;
    if ((((*(int *)(tmp_i1 + (tmp_i2 + 0xa4) * 4) != 0) && ((*(uint *)(tmp_i1 + 0x68) & 0x40000) == 0))
        && ((*(int *)(tmp_i1 + 0xa8) == 5 || (*(int *)(tmp_i1 + 0xa8) == 0)))) &&
       ((((*(byte *)(pm + 4) & 1) != 0 && ((*(byte *)(pm + 4) & 2) == 0)) &&
        (*(float *)(tmp_i1 + 0x3c) == 0.0)))) {
      *(uint *)(tmp_i1 + 0x68) = *(uint *)(tmp_i1 + 0x68) | 0x80;
    }
  }
  return;
}

void PmoveSingle(int *param_1)
{
  float tmp_f1;
  char tmp_c2;
  bool tmp_b3;
  float tmp_f4;
  byte tmp_b5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int *tmp_pi9;
  int *tmp_pi10;
  uint tmp_u11;
  int tmp_i12;
  uint tmp_u13;
  long double tmp_l14;
  long double tmp_l15;
  long double tmp_l16;
  long double tmp_l17;
  long double tmp_l18;
  float tmp_f19;
  uint32_t tmp_u20;
  uint32_t tmp_u21;
  float local_84;
  float local_54;
  float local_50;
  float local_4c;
  
  BG_AnimUpdatePlayerStateConditions(param_1);
  c_pmove = c_pmove + 1;
  pm = param_1;
  param_1[0x41] = 0;
  tmp_i12 = *param_1;
  param_1[0x19] = 0;
  param_1[0x40] = 0;
  tmp_pi9 = param_1;
  if (*(int *)(tmp_i12 + 0xd0) < 1) {
    param_1[0x11] = param_1[0x11] & 0xfdffffff;
    *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) & 0xfffbffff;
    tmp_i12 = BG_IsScopedWeapon(*(uint32_t *)(*param_1 + 0xa4));
    tmp_pi9 = pm;
    if (tmp_i12 != 0) {
      *(uint32_t *)(*pm + 0xa4) = *(uint32_t *)(weapAlts + *(int *)(*pm + 0xa4) * 4);
    }
    tmp_i12 = *tmp_pi9;
  }
  tmp_u11 = (int)(char)tmp_pi9[8] >> 0x1f;
  if (((int)(((int)(char)tmp_pi9[8] ^ tmp_u11) - tmp_u11) < 0x41) &&
     (tmp_u11 = (int)*(char *)((int)tmp_pi9 + 0x21) >> 0x1f,
     (int)(((int)*(char *)((int)tmp_pi9 + 0x21) ^ tmp_u11) - tmp_u11) < 0x41)) {
    tmp_b5 = *(byte *)(tmp_pi9 + 4);
  }
  else {
    tmp_b5 = *(byte *)(tmp_pi9 + 4) & 0xef;
    *(byte *)(tmp_pi9 + 4) = tmp_b5;
  }
  if ((tmp_b5 & 2) == 0) {
    *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) & 0xfffffdff;
  }
  else {
    *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) | 0x200;
  }
  *(uint *)(*tmp_pi9 + 0x68) = *(uint *)(*tmp_pi9 + 0x68) & 0xfffbff7f;
  tmp_i12 = *tmp_pi9;
  if ((((*(byte *)((int)tmp_pi9 + 0x11) & 2) != 0) && (-1 < *(int *)(tmp_i12 + 0xd0))) &&
     (*(int *)(tmp_i12 + 0x30) == 0)) {
    if ((*(byte *)(tmp_i12 + 0xd4) & 0x40) != 0) {
      tmp_i6 = BG_IsScopedWeapon(*(uint32_t *)(tmp_i12 + 0xa4));
      tmp_pi9 = pm;
      tmp_i12 = *pm;
      if ((tmp_i6 == 0) && ((*(uint *)(tmp_i12 + 0x68) & 0x8020) == 0)) {
        if ((*(uint *)(tmp_i12 + 0xa4) & 0xfffffffb) == 0x2a) goto LAB_0002f110;
        *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) | 0x40000;
        tmp_i12 = *tmp_pi9;
      }
    }
    tmp_i6 = *(int *)(tmp_i12 + 0xa4);
    if (((tmp_i6 == 9 || tmp_i6 == 4) || (tmp_i6 == 0xf)) && (0 < *(int *)(tmp_i12 + 0x34))) {
      *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) & 0xfffbffff;
      tmp_i12 = *tmp_pi9;
    }
  }
LAB_0002f110:
  if ((*(byte *)(tmp_i12 + 0xd) & 2) == 0) {
    if (*(int *)(tmp_i12 + 4) != 5) {
      tmp_i12 = *(int *)(tmp_i12 + 0xa4);
      tmp_i6 = BG_FindClipForWeapon(tmp_i12);
      if ((tmp_i12 - 0x2cU < 2) || (tmp_i12 - 0x22U < 2)) {
        tmp_i8 = *pm;
        tmp_u21 = BG_AkimboSidearm(tmp_i12);
        tmp_i7 = BG_FindClipForWeapon(tmp_u21);
        tmp_u21 = *(uint32_t *)(tmp_i8 + (tmp_i7 + 0xa4) * 4);
        tmp_i8 = *pm;
        tmp_i7 = BG_FindClipForWeapon(tmp_i12);
        tmp_i8 = BG_AkimboFireSequence(tmp_i12,*(uint32_t *)(tmp_i8 + (tmp_i7 + 0xa4) * 4),tmp_u21);
        if (tmp_i8 == 0) {
          tmp_i6 = BG_AkimboSidearm(tmp_i12);
        }
      }
      tmp_pi9 = pm;
      tmp_i12 = *pm;
      if (((*(int *)(tmp_i12 + (tmp_i6 + 0xa4) * 4) != 0) &&
          ((*(uint *)(tmp_i12 + 0x68) & 0x40000) == 0)) &&
         (((*(int *)(tmp_i12 + 0xa8) == 5 || (*(int *)(tmp_i12 + 0xa8) == 0)) &&
          ((((*(byte *)(pm + 4) & 1) != 0 && ((*(byte *)(pm + 4) & 2) == 0)) &&
           (*(float *)(tmp_i12 + 0x3c) == 0.0)))))) {
        *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) | 0x80;
        tmp_i12 = *tmp_pi9;
      }
      if ((*(byte *)(tmp_i12 + 0xd) & 2) != 0) goto LAB_0002f310;
    }
  }
  else {
LAB_0002f310:
    if (*(int *)(tmp_i12 + 0xe4) == 4) {
      *(uint *)(tmp_pi9[1] + 0xc) = *(uint *)(tmp_pi9[1] + 0xc) | 1;
      tmp_i12 = *tmp_pi9;
    }
  }
  if ((0 < *(int *)(tmp_i12 + 0xd0)) && ((*(byte *)(tmp_pi9 + 4) & 5) == 0)) {
    *(uint *)(tmp_i12 + 0xc) = *(uint *)(tmp_i12 + 0xc) & 0xfffffdff;
  }
  if ((*(byte *)(param_1 + 4) & 2) != 0) {
    *(uint8_t *)(param_1 + 4) = 2;
    *(uint8_t *)((int)param_1 + 0x11) = 0;
    *(uint8_t *)(param_1 + 8) = 0;
    *(uint8_t *)((int)param_1 + 0x21) = 0;
    *(uint8_t *)((int)param_1 + 0x22) = 0;
    *(uint8_t *)((int)param_1 + 0x23) = 0;
  }
  if (*(int *)(*tmp_pi9 + 0x140) != 0) {
    *(uint8_t *)(param_1 + 8) = 0;
    *(uint8_t *)((int)param_1 + 0x21) = 0;
    *(uint8_t *)((int)param_1 + 0x22) = 0;
  }
  tmp_u11 = 0;
  do {
    *(uint32_t *)((int)&pml + tmp_u11) = 0;
    *(uint32_t *)((int)&g_unk_00f3e2e4 + tmp_u11) = 0;
    tmp_u11 = tmp_u11 + 8;
  } while (tmp_u11 < 0x90);
  g_unk_00f3e308 = param_1[3] - *(int *)*tmp_pi9;
  if (g_unk_00f3e308 < 1) {
    g_unk_00f3e308 = 1;
  }
  else if (200 < g_unk_00f3e308) {
    g_unk_00f3e308 = 200;
  }
  *(int *)*tmp_pi9 = param_1[3];
  g_unk_00f3e350 = *(uint32_t *)(*pm + 0x14);
  g_unk_00f3e354 = *(uint32_t *)(*pm + 0x18);
  g_unk_00f3e358 = *(uint32_t *)(*pm + 0x1c);
  g_unk_00f3e35c = *(float *)(*pm + 0x20);
  g_unk_00f3e360 = *(float *)(*pm + 0x24);
  g_unk_00f3e364 = *(float *)(*pm + 0x28);
  g_unk_00f3e304 = (float)g_unk_00f3e308 * 0.001;
  tmp_i12 = *pm;
  if ((*(int *)(tmp_i12 + 4) != 4) && ((*(byte *)(tmp_i12 + 0xd) & 0x40) == 0)) {
    PM_UpdateViewAngles(tmp_i12,pm[1],pm + 3,pm[0x46],pm[0x11]);
    PM_UpdateLean(*pm,pm + 3,pm);
    tmp_i12 = *pm;
  }
  AngleVectors(tmp_i12 + 0xb0,&pml,&g_unk_00f3e2ec,&g_unk_00f3e2f8);
  tmp_pi9 = pm;
  if (*(char *)((int)pm + 0x22) < '\n') {
    *(uint *)(*pm + 0xc) = *(uint *)(*pm + 0xc) & 0xfffffffd;
  }
  if ((char)tmp_pi9[8] < '\0') {
    *(uint *)(*tmp_pi9 + 0xc) = *(uint *)(*tmp_pi9 + 0xc) | 0x10;
  }
  else if (((char)tmp_pi9[8] != '\0') || (*(char *)((int)tmp_pi9 + 0x21) != '\0')) {
    *(uint *)(*tmp_pi9 + 0xc) = *(uint *)(*tmp_pi9 + 0xc) & 0xffffffef;
  }
  tmp_i12 = *tmp_pi9;
  tmp_i6 = *(int *)(tmp_i12 + 4);
  if ((2 < tmp_i6) || ((*(uint *)(tmp_i12 + 0xc) & 0xc000) != 0)) {
    *(uint8_t *)(tmp_pi9 + 8) = 0;
    *(uint8_t *)((int)tmp_pi9 + 0x21) = 0;
    *(uint8_t *)((int)tmp_pi9 + 0x22) = 0;
    tmp_i6 = *(int *)(tmp_i12 + 4);
  }
  switch(tmp_i6) {
  case 0:
    if (*(int *)(tmp_i12 + 0xa4) == 0x2a) {
      *(uint8_t *)(tmp_pi9 + 8) = 0;
      *(uint8_t *)((int)tmp_pi9 + 0x21) = 0;
      *(uint8_t *)((int)tmp_pi9 + 0x22) = 0;
    }
    break;
  case 1:
    *(uint32_t *)(tmp_i12 + 0xbc) = 0x28;
    tmp_l16 = (long double)VectorLength(*tmp_pi9 + 0x20);
    tmp_pi9 = pm;
    if (tmp_l16 < (long double)1) {
      *(uint32_t *)(*pm + 0x20) = vec3_origin;
      *(uint32_t *)(*tmp_pi9 + 0x24) = g_unk_00c22b14;
      *(uint32_t *)(*tmp_pi9 + 0x28) = g_unk_00c22b18;
    }
    else {
      tmp_l17 = (long double)pm_stopspeed;
      if ((long double)pm_stopspeed <= tmp_l16) {
        tmp_l17 = tmp_l16;
      }
      tmp_l18 = (long double)0;
      tmp_l17 = tmp_l16 - (tmp_l17 * (long double)1.5 * (long double)pm_friction *
                         (long double)g_unk_00f3e304 + tmp_l18);
      if (tmp_l18 <= tmp_l17) {
        tmp_l18 = tmp_l17;
      }
      tmp_l18 = tmp_l18 / tmp_l16;
      *(float *)(*pm + 0x20) = (float)((long double)*(float *)(*pm + 0x20) * tmp_l18);
      *(float *)(*tmp_pi9 + 0x24) = (float)((long double)*(float *)(*tmp_pi9 + 0x24) * tmp_l18);
      *(float *)(*tmp_pi9 + 0x28) = (float)(tmp_l18 * (long double)*(float *)(*tmp_pi9 + 0x28));
    }
    tmp_l16 = (long double)PM_CmdScale_isra_0(*(uint8_t *)((int)tmp_pi9 + 0x22));
    tmp_f19 = (float)(short)(char)pm[8];
    tmp_f1 = (float)(short)*(char *)((int)pm + 0x21);
    local_54 = g_unk_00f3e2ec * tmp_f1 + pml * tmp_f19;
    local_50 = g_unk_00f3e2f0 * tmp_f1 + g_unk_00f3e2e4 * tmp_f19;
    local_4c = (float)(short)*(char *)((int)pm + 0x22) +
               tmp_f1 * g_unk_00f3e2f4 + tmp_f19 * g_unk_00f3e2e8;
    tmp_l17 = (long double)VectorNormalize(&local_54);
    tmp_pi9 = pm;
    tmp_i12 = *pm;
    tmp_l14 = (long double)*(float *)(tmp_i12 + 0x20);
    tmp_l18 = tmp_l17 * (long double)(float)tmp_l16 -
             ((long double)*(float *)(tmp_i12 + 0x28) * (long double)local_4c +
             (long double)*(float *)(tmp_i12 + 0x24) * (long double)local_50 +
             tmp_l14 * (long double)local_54);
    if (tmp_l18 <= (long double)0) goto LAB_0002f770;
    tmp_l16 = (long double)pm_accelerate * (long double)g_unk_00f3e304 *
             tmp_l17 * (long double)(float)tmp_l16;
    if (tmp_l16 <= tmp_l18) {
      if (*(int *)(tmp_i12 + 0x50) != 0x3ff) goto LAB_0002f702;
LAB_0002f714:
      if (tmp_l18 < tmp_l16) {
        tmp_l16 = tmp_l18;
      }
    }
    else {
      tmp_l16 = tmp_l18;
      if (*(int *)(tmp_i12 + 0x50) != 0x3ff) {
LAB_0002f702:
        tmp_l16 = (long double)
                 (float)(((long double)1 / (long double)*(float *)(tmp_i12 + 0x418)) * tmp_l16);
        goto LAB_0002f714;
      }
    }
    *(float *)(tmp_i12 + 0x20) = (float)((long double)local_54 * tmp_l16 + tmp_l14);
    *(float *)(*tmp_pi9 + 0x24) =
         (float)((long double)local_50 * tmp_l16 + (long double)*(float *)(*tmp_pi9 + 0x24));
    *(float *)(*tmp_pi9 + 0x28) =
         (float)(tmp_l16 * (long double)local_4c + (long double)*(float *)(*tmp_pi9 + 0x28));
    tmp_i12 = *tmp_pi9;
    tmp_l14 = (long double)*(float *)(tmp_i12 + 0x20);
LAB_0002f770:
    *(float *)(tmp_i12 + 0x14) =
         (float)(tmp_l14 * (long double)g_unk_00f3e304 + (long double)*(float *)(tmp_i12 + 0x14));
    tmp_i12 = *tmp_pi9;
    *(float *)(tmp_i12 + 0x18) = *(float *)(tmp_i12 + 0x24) * g_unk_00f3e304 + *(float *)(tmp_i12 + 0x18)
    ;
    tmp_i12 = *tmp_pi9;
    *(float *)(tmp_i12 + 0x1c) = *(float *)(tmp_i12 + 0x28) * g_unk_00f3e304 + *(float *)(tmp_i12 + 0x1c)
    ;
    PM_DropTimers();
    return;
  case 2:
    PM_CheckDuck();
    PM_Friction();
    tmp_l16 = (long double)PM_CmdScale_isra_0(*(uint8_t *)((int)pm + 0x22));
    if (tmp_l16 == (long double)0) {
      tmp_l17 = (long double)0;
      tmp_l18 = tmp_l17;
      tmp_l16 = tmp_l17;
    }
    else {
      tmp_l14 = (long double)(short)(char)pm[8];
      tmp_l15 = (long double)(short)*(char *)((int)pm + 0x21);
      tmp_l17 = (long double)g_unk_00f3e2ec * tmp_l16 * tmp_l15 + (long double)pml * tmp_l16 * tmp_l14;
      tmp_l18 = (long double)g_unk_00f3e2f0 * tmp_l16 * tmp_l15 +
               (long double)g_unk_00f3e2e4 * tmp_l16 * tmp_l14;
      tmp_l16 = (long double)(short)*(char *)((int)pm + 0x22) * tmp_l16 +
               (long double)g_unk_00f3e2e8 * tmp_l16 * tmp_l14 +
               (long double)g_unk_00f3e2f4 * tmp_l16 * tmp_l15;
    }
    local_54 = (float)tmp_l17;
    local_50 = (float)tmp_l18;
    local_4c = (float)tmp_l16;
    tmp_l16 = (long double)VectorNormalize(&local_54);
    tmp_pi9 = pm;
    tmp_i12 = *pm;
    tmp_l17 = tmp_l16 - ((long double)*(float *)(tmp_i12 + 0x28) * (long double)local_4c +
                      (long double)*(float *)(tmp_i12 + 0x24) * (long double)local_50 +
                      (long double)*(float *)(tmp_i12 + 0x20) * (long double)local_54);
    if ((long double)0 < tmp_l17) {
      tmp_l16 = (long double)pm_flyaccelerate * (long double)g_unk_00f3e304 * tmp_l16;
      if (tmp_l16 <= tmp_l17) {
        if (*(int *)(tmp_i12 + 0x50) != 0x3ff) goto LAB_0002f504;
LAB_0002f516:
        if (tmp_l17 < tmp_l16) {
          tmp_l16 = tmp_l17;
        }
      }
      else {
        tmp_l16 = tmp_l17;
        if (*(int *)(tmp_i12 + 0x50) != 0x3ff) {
LAB_0002f504:
          tmp_l16 = (long double)
                   (float)(((long double)1 / (long double)*(float *)(tmp_i12 + 0x418)) * tmp_l16);
          goto LAB_0002f516;
        }
      }
      *(float *)(tmp_i12 + 0x20) =
           (float)((long double)local_54 * tmp_l16 + (long double)*(float *)(tmp_i12 + 0x20));
      tmp_i12 = *tmp_pi9;
      *(float *)(tmp_i12 + 0x24) =
           (float)((long double)local_50 * tmp_l16 + (long double)*(float *)(tmp_i12 + 0x24));
      tmp_i12 = *tmp_pi9;
      *(float *)(tmp_i12 + 0x28) =
           (float)(tmp_l16 * (long double)local_4c + (long double)*(float *)(tmp_i12 + 0x28));
    }
    PM_StepSlideMove(0);
    PM_DropTimers();
_L2648:
    return;
  case 4:
  case 5:
    goto _L2648;
  }
  PM_SetWaterLevel();
  tmp_pi9 = pm;
  g_unk_00f3e368 = param_1[0x41];
  tmp_i12 = *pm;
  if (*(int *)(tmp_i12 + 4) == 6) {
    tmp_u21 = 0;
    if ((*(uint *)(tmp_i12 + 0x68) & 0x800000) != 0) {
      tmp_u21 = 3;
    }
    *(uint32_t *)(tmp_i12 + 4) = tmp_u21;
    tmp_i12 = *tmp_pi9;
    if ((*(uint *)(tmp_i12 + 0x68) & 0x800000) == 0) {
      if (((((*(byte *)(tmp_i12 + 0xc) & 4) == 0) && (*(int *)(tmp_i12 + 0x140) == 0)) &&
          ((*(uint *)(tmp_i12 + 0x68) & 0x8000) == 0)) &&
         ((tmp_pi9[0x41] < 2 && (0x6d5 < tmp_pi9[3] - *(int *)(tmp_pi9[1] + 0x7c))))) {
        tmp_pi9[0x3a] = *(int *)(tmp_i12 + 0x3dc);
        tmp_pi9[0x3b] = *(int *)(tmp_i12 + 0x3e0);
        tmp_pi9[0x3d] = *(int *)(tmp_i12 + 1000);
        tmp_pi9[0x3e] = *(int *)(tmp_i12 + 0x3ec);
        tmp_i6 = *(int *)(tmp_i12 + 0x3e4);
        tmp_pi9[0x3f] = 0;
        tmp_pi9[0x3c] = tmp_i6;
        *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) | 0x800000;
        PM_TraceAllLegs_constprop_8(*tmp_pi9 + 0x14);
        tmp_pi9 = pm;
        *(uint *)(*pm + 0x68) = *(uint *)(*pm + 0x68) & 0xff7fffff;
        if ((local_50 == 0.0) && (local_54 == 0.0)) {
          *(uint *)(*tmp_pi9 + 0x68) = *(uint *)(*tmp_pi9 + 0x68) | 0x800000;
          *(uint32_t *)(*tmp_pi9 + 4) = 3;
          tmp_i12 = *(int *)(*tmp_pi9 + 0x3f4);
          *(int *)(*tmp_pi9 + 0x3f0) = tmp_i12;
          tmp_pi9[0x3f] = tmp_i12;
          BG_UpdateConditionValue(*(uint32_t *)(*tmp_pi9 + 0xa0),2,0,1);
          BG_UpdateConditionValue(*(uint32_t *)(*pm + 0xa0),1,0,1);
          tmp_i12 = *pm;
          tmp_u21 = BG_AnimScriptEvent(tmp_i12,*(uint32_t *)(pm[2] + 0x7f0),1,0,1);
          *(uint32_t *)(tmp_i12 + 0x10) = tmp_u21;
          tmp_pi9 = pm;
          *(int *)(pm[1] + 0x7c) = -pm[3];
          *(int *)(*tmp_pi9 + 0x48) = -tmp_pi9[6];
          *(uint32_t *)(*tmp_pi9 + 4) = 3;
        }
      }
    }
    else if (0x6d5 < *(int *)(tmp_pi9[1] + 0x7c) + tmp_pi9[3]) {
      tmp_pi9[0x3a] = *(int *)(tmp_i12 + 0x3dc);
      tmp_pi9[0x3b] = *(int *)(tmp_i12 + 0x3e0);
      tmp_pi9[0x3d] = *(int *)(tmp_i12 + 1000);
      tmp_pi9[0x3e] = *(int *)(tmp_i12 + 0x3ec);
      tmp_pi9[0x3c] = *(int *)(tmp_i12 + 0x3e4);
      tmp_pi9[0x3f] = *(int *)(tmp_i12 + 0x3f4);
      *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) & 0xff7fffff;
      PM_TraceAllLegs_constprop_8(*tmp_pi9 + 0x14);
      tmp_pi9 = pm;
      *(uint *)(*pm + 0x68) = *(uint *)(*pm + 0x68) | 0x800000;
      if (local_54 == 0.0) {
        *(uint *)(*tmp_pi9 + 0xc) = *(uint *)(*tmp_pi9 + 0xc) | 1;
        tmp_i12 = *(int *)(*tmp_pi9 + 0x3fc);
        *(int *)(*tmp_pi9 + 0x3f0) = tmp_i12;
        tmp_pi9[0x3f] = tmp_i12;
        *(uint *)(*tmp_pi9 + 0x68) = *(uint *)(*tmp_pi9 + 0x68) & 0xff7fffff;
        *(uint *)(*tmp_pi9 + 0x68) = *(uint *)(*tmp_pi9 + 0x68) & 0xfffffffe;
        *(uint *)(*tmp_pi9 + 0xc) = *(uint *)(*tmp_pi9 + 0xc) | 0x8000;
        tmp_i12 = *tmp_pi9;
        tmp_u21 = BG_AnimScriptEvent(tmp_i12,*(uint32_t *)(tmp_pi9[2] + 0x7f0),0x1a,0,1);
        *(uint32_t *)(tmp_i12 + 0x10) = tmp_u21;
        tmp_pi9 = pm;
        *(int *)(pm[1] + 0x7c) = pm[3];
        *(uint32_t *)(*tmp_pi9 + 4) = 0;
        tmp_i12 = *tmp_pi9;
        *(float *)(tmp_i12 + 0xb4) =
             (float)*(int *)(tmp_i12 + 0xd8) * 0.005493164 + *(float *)(tmp_i12 + 0xb4);
      }
    }
  }
  tmp_i12 = 0x2ee;
  if ((GHIDRA_FIELD(cgs, 33788132, 4) & 0xfffffffd) == 1) {
    tmp_i12 = 0x6d6;
  }
  tmp_i6 = *tmp_pi9;
  tmp_u11 = *(uint *)(tmp_i6 + 0x68);
  if ((tmp_u11 & 0x80000) == 0) {
    if ((((((*(uint *)(tmp_i6 + 0xc) & 4) == 0) && (*(int *)(tmp_i6 + 0x140) == 0)) &&
         (((tmp_u11 & 0x8000) == 0 &&
          (((*(int *)(tmp_i6 + 0x30) == 0 || (*(int *)(tmp_i6 + 0xa4) != 5)) &&
           (*(int *)(tmp_i6 + 0xa4) != 0x2a)))))) && (tmp_pi9[0x41] < 2)) &&
       (((((*(uint *)(tmp_i6 + 0xc) & 1) != 0 && (*(char *)((int)tmp_pi9 + 0x23) == '\x03')) ||
         (*(char *)((int)tmp_pi9 + 0x11) < '\0')) && (0x2ee < *(int *)(tmp_pi9[1] + 0x30) + tmp_pi9[3])
        ))) {
      tmp_pi9[0x3a] = *(int *)(tmp_i6 + 0x3dc);
      tmp_pi9[0x3b] = *(int *)(tmp_i6 + 0x3e0);
      tmp_pi9[0x3d] = *(int *)(tmp_i6 + 1000);
      tmp_pi9[0x3e] = *(int *)(tmp_i6 + 0x3ec);
      tmp_pi9[0x3c] = *(int *)(tmp_i6 + 0x3e4);
      tmp_pi9[0x3f] = *(int *)(tmp_i6 + 0x3f4);
      *(uint *)(tmp_i6 + 0x68) = *(uint *)(tmp_i6 + 0x68) | 0x80000;
      PM_TraceAllLegs_constprop_8(*tmp_pi9 + 0x14);
      tmp_pi9 = pm;
      *(uint *)(*pm + 0x68) = *(uint *)(*pm + 0x68) & 0xfff7ffff;
      if ((local_50 == 0.0) && (local_54 == 0.0)) {
        *(uint *)(*tmp_pi9 + 0xc) = *(uint *)(*tmp_pi9 + 0xc) | 1;
        *(uint *)(*tmp_pi9 + 0x68) = *(uint *)(*tmp_pi9 + 0x68) | 0x80000;
        *(int *)(tmp_pi9[1] + 0x30) = tmp_pi9[3];
        *(int *)(tmp_pi9[1] + 0x34) = tmp_pi9[3];
      }
      tmp_i6 = *tmp_pi9;
      tmp_u11 = *(uint *)(tmp_i6 + 0x68);
      if ((tmp_u11 & 0x80000) != 0) goto LAB_0002f80e;
    }
LAB_0002fa77:
    PM_CheckDuck();
  }
  else {
LAB_0002f80e:
    if ((((1 < tmp_pi9[0x41]) || (*(int *)(tmp_i6 + 4) == 3)) || ((tmp_u11 & 0x8000) != 0)) ||
       ((((*(char *)((int)tmp_pi9 + 0x23) == '\x04' || ('\n' < *(char *)((int)tmp_pi9 + 0x22))) ||
         (*(char *)((int)tmp_pi9 + 0x11) < '\0')) &&
        (tmp_i12 < tmp_pi9[3] - *(int *)(tmp_pi9[1] + 0x30))))) {
      tmp_pi9[0x3a] = *(int *)(tmp_i6 + 0x3dc);
      tmp_pi9[0x3b] = *(int *)(tmp_i6 + 0x3e0);
      tmp_pi9[0x3d] = *(int *)(tmp_i6 + 1000);
      tmp_pi9[0x3e] = *(int *)(tmp_i6 + 0x3ec);
      tmp_pi9[0x3c] = *(int *)(tmp_i6 + 0x3e4);
      tmp_pi9[0x3f] = *(int *)(tmp_i6 + 0x3f4);
      *(uint *)(tmp_i6 + 0x68) = *(uint *)(tmp_i6 + 0x68) & 0xfff7ffff;
      PM_TraceAllLegs_constprop_8(*tmp_pi9 + 0x14);
      tmp_pi9 = pm;
      *(uint *)(*pm + 0x68) = *(uint *)(*pm + 0x68) | 0x80000;
      if (local_54 == 0.0) {
        *(uint *)(*tmp_pi9 + 0xc) = *(uint *)(*tmp_pi9 + 0xc) | 1;
        *(uint *)(*tmp_pi9 + 0x68) = *(uint *)(*tmp_pi9 + 0x68) & 0xfff7ffff;
        *(uint *)(*tmp_pi9 + 0x68) = *(uint *)(*tmp_pi9 + 0x68) & 0xffefffff;
        *(int *)(tmp_pi9[1] + 0x30) = -tmp_pi9[3];
        if (*(int *)(*tmp_pi9 + 0xa4) == 0x2e) {
          PM_BeginWeaponChange(0x2e,0x1d,0);
          tmp_pi9 = pm;
        }
        *(int *)(tmp_pi9[1] + 4) = tmp_pi9[3] + -0x28a;
        *(int *)(*tmp_pi9 + 0x47c) = tmp_pi9[3] + -0x28a;
      }
      tmp_i6 = *tmp_pi9;
      if ((*(byte *)(tmp_i6 + 0x6a) & 8) == 0) goto LAB_0002fa77;
    }
    tmp_l16 = (long double)VectorLength(tmp_i6 + 0x20);
    tmp_pi9 = pm;
    tmp_u11 = (int)(char)pm[8] >> 0x1f;
    tmp_u13 = (int)*(char *)((int)pm + 0x21) >> 0x1f;
    tmp_b3 = 10 < (int)((((int)*(char *)((int)pm + 0x21) ^ tmp_u13) - tmp_u13) +
                      (((int)(char)pm[8] ^ tmp_u11) - tmp_u11));
    if ((tmp_l16 <= (long double)40.0) || (!tmp_b3)) {
      tmp_i12 = *pm;
      if ((tmp_b3 < (tmp_l16 < (long double)20.0)) && ((*(uint *)(tmp_i12 + 0x68) & 0x100000) != 0)) {
        *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) & 0xffefffff;
        tmp_i12 = *tmp_pi9;
      }
    }
    else {
      tmp_i12 = *pm;
      if ((*(uint *)(tmp_i12 + 0x68) & 0x100000) == 0) {
        *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) | 0x100000;
        tmp_i12 = *tmp_pi9;
        tmp_i6 = *(int *)(tmp_i12 + 0xa4);
        if (tmp_i6 == 0x28) {
          PM_BeginWeaponChange(0x28,0x1e,0);
          tmp_i12 = *pm;
          tmp_pi9 = pm;
        }
        else if (tmp_i6 == 0x29) {
          PM_BeginWeaponChange(0x29,0x1f,0);
          tmp_i12 = *pm;
          tmp_pi9 = pm;
        }
        else if (tmp_i6 == 0x27) {
          PM_BeginWeaponChange(0x27,0x18,0);
          tmp_i12 = *pm;
          tmp_pi9 = pm;
        }
      }
    }
    tmp_pi9[0x3a] = *(int *)(tmp_i12 + 0x3dc);
    tmp_pi9[0x3b] = *(int *)(tmp_i12 + 0x3e0);
    tmp_pi9[0x3d] = *(int *)(tmp_i12 + 1000);
    tmp_pi9[0x3e] = *(int *)(tmp_i12 + 0x3ec);
    tmp_pi9[0x3c] = *(int *)(tmp_i12 + 0x3e4);
    tmp_pi9[0x3f] = (int)((*(float *)(tmp_i12 + 0x3f0) - *(float *)(tmp_i12 + 0x3fc)) + 8.0);
    *(uint32_t *)(tmp_i12 + 0xbc) = 0xfffffff8;
  }
  PM_GroundTrace();
  tmp_i12 = *pm;
  if (*(int *)(tmp_i12 + 4) == 3) {
    if (g_unk_00f3e30c != 0) {
      tmp_l17 = (long double)VectorLength(tmp_i12 + 0x20);
      tmp_pi9 = pm;
      tmp_l16 = (long double)0;
      if (tmp_l17 - (long double)20.0 <= tmp_l16) {
        tmp_i12 = *pm;
        *(float *)(tmp_i12 + 0x28) = (float)tmp_l16;
        *(float *)(tmp_i12 + 0x24) = (float)tmp_l16;
        *(float *)(tmp_i12 + 0x20) = (float)tmp_l16;
        tmp_i12 = *tmp_pi9;
      }
      else {
        tmp_f1 = (float)(tmp_l17 - (long double)20.0);
        VectorNormalize(*pm + 0x20);
        tmp_pi9 = pm;
        *(float *)(*pm + 0x20) = *(float *)(*pm + 0x20) * tmp_f1;
        *(float *)(*tmp_pi9 + 0x24) = *(float *)(*tmp_pi9 + 0x24) * tmp_f1;
        *(float *)(*tmp_pi9 + 0x28) = tmp_f1 * *(float *)(*tmp_pi9 + 0x28);
        tmp_i12 = *tmp_pi9;
      }
    }
    if (*(int *)(tmp_i12 + 0xa4) == 0x2a) {
      *(uint32_t *)(tmp_i12 + 0xa4) = 0x21;
    }
  }
  else if ((*(int *)(tmp_i12 + 0xa4) == 0x2e) && ((*(byte *)(tmp_i12 + 0x6a) & 8) == 0)) {
    PM_BeginWeaponChange(0x2e,0x1d,0);
    g_unk_01091814 = 0x1d;
  }
  PM_CheckLadderMove();
  PM_DropTimers();
  tmp_pi9 = pm;
  if (g_unk_00f3e36c == 0) {
    tmp_i12 = *pm;
    tmp_u11 = *(uint *)(tmp_i12 + 0xc);
    if ((tmp_u11 & 0x100) != 0) {
      PM_StepSlideMove(1);
      tmp_pi9 = pm;
      tmp_i12 = *pm;
      *(float *)(tmp_i12 + 0x28) =
           *(float *)(tmp_i12 + 0x28) - (float)*(int *)(tmp_i12 + 0x38) * g_unk_00f3e304;
      tmp_i12 = *tmp_pi9;
      if (*(float *)(tmp_i12 + 0x28) < 0.0) {
        *(uint *)(tmp_i12 + 0xc) = *(uint *)(tmp_i12 + 0xc) & 0xffff7e9f;
        *(uint32_t *)(*tmp_pi9 + 0x10) = 0;
        tmp_i12 = *tmp_pi9;
        tmp_u11 = *(uint *)(tmp_i12 + 0x68) & 0x8000;
        goto LAB_0002faef;
      }
LAB_000305be:
      tmp_u11 = *(uint *)(tmp_i12 + 0x68) & 0x8000;
      goto LAB_0002faef;
    }
    if (1 < pm[0x41]) {
      PM_WaterMove();
      tmp_i12 = *pm;
      tmp_u11 = *(uint *)(tmp_i12 + 0x68) & 0x8000;
      tmp_pi9 = pm;
      goto LAB_0002faef;
    }
    if (g_unk_00f3e30c == 0) {
      if ((*(byte *)(tmp_i12 + 0x69) & 0x80) == 0) {
        PM_AirMove();
        tmp_i12 = *pm;
        tmp_pi9 = pm;
        goto LAB_000305be;
      }
    }
    else if ((*(uint *)(tmp_i12 + 0x68) & 0x8000) == 0) {
      if (((((*(uint *)(tmp_i12 + 0x68) & 0x80000) == 0) && (0x351 < pm[3] - *(int *)(pm[1] + 4))) &&
          ((tmp_u11 & 0x200) == 0)) && ('\t' < *(char *)((int)pm + 0x22))) {
        if ((tmp_u11 & 2) != 0) {
          *(uint8_t *)((int)pm + 0x22) = 0;
          goto LAB_00030c50;
        }
        g_unk_00f3e310 = 0;
        g_unk_00f3e30c = 0;
        *(uint *)(*pm + 0xc) = *(uint *)(*pm + 0xc) | 2;
        *(uint32_t *)(*tmp_pi9 + 0x50) = 0x3ff;
        *(uint32_t *)(*tmp_pi9 + 0x28) = 0x43870000;
        if ((char)tmp_pi9[8] < '\0') {
          tmp_u21 = 5;
        }
        else {
          tmp_u21 = 4;
        }
        BG_AnimScriptEvent(*tmp_pi9,*(uint32_t *)(tmp_pi9[2] + 0x7f0),tmp_u21,0,1);
        if (pm[0x41] < 2) {
          PM_AirMove();
        }
        else {
          PM_WaterMove();
        }
        tmp_pi9 = pm;
        tmp_i12 = pm[3];
        if (0x351 < tmp_i12 - *(int *)(pm[1] + 4)) {
          tmp_pi10 = (int *)(pm[1] + 0x10);
          *tmp_pi10 = *tmp_pi10 + -0x9c4;
          tmp_i12 = tmp_pi9[1];
          if (*(int *)(tmp_i12 + 0x10) < 0) {
            *(uint32_t *)(tmp_i12 + 0x10) = 0;
            tmp_i12 = tmp_pi9[1];
          }
          *(int *)(tmp_i12 + 4) = tmp_pi9[3];
          tmp_i12 = tmp_pi9[3];
        }
        *(int *)(*tmp_pi9 + 0x47c) = tmp_i12;
      }
      else {
LAB_00030c50:
        PM_Friction();
        tmp_i12 = pm[8];
        tmp_c2 = *(char *)((int)pm + 0x21);
        tmp_l16 = (long double)PM_CmdScale_isra_0(*(uint8_t *)((int)pm + 0x22));
        tmp_f1 = g_unk_00f3e2e4 * g_unk_00f3e330 + pml * g_unk_00f3e32c + g_unk_00f3e334 * 0.0;
        if (tmp_f1 < 0.0) {
          tmp_f1 = tmp_f1 * 1.001;
        }
        else {
          tmp_f1 = tmp_f1 / 1.001;
        }
        pml = pml - g_unk_00f3e32c * tmp_f1;
        g_unk_00f3e2e4 = g_unk_00f3e2e4 - g_unk_00f3e330 * tmp_f1;
        g_unk_00f3e2e8 = 0.0 - tmp_f1 * g_unk_00f3e334;
        tmp_f1 = g_unk_00f3e330 * g_unk_00f3e2f0 + g_unk_00f3e32c * g_unk_00f3e2ec + g_unk_00f3e334 * 0.0;
        if (tmp_f1 < 0.0) {
          tmp_f1 = tmp_f1 * 1.001;
        }
        else {
          tmp_f1 = tmp_f1 / 1.001;
        }
        g_unk_00f3e2ec = g_unk_00f3e2ec - g_unk_00f3e32c * tmp_f1;
        g_unk_00f3e2f0 = g_unk_00f3e2f0 - g_unk_00f3e330 * tmp_f1;
        g_unk_00f3e2f4 = 0.0 - tmp_f1 * g_unk_00f3e334;
        VectorNormalize(&pml);
        VectorNormalize(&g_unk_00f3e2ec);
        tmp_f19 = (float)(short)(char)tmp_i12;
        tmp_f1 = (float)(short)tmp_c2;
        local_54 = g_unk_00f3e2ec * tmp_f1 + pml * tmp_f19;
        local_50 = g_unk_00f3e2f0 * tmp_f1 + g_unk_00f3e2e4 * tmp_f19;
        local_4c = tmp_f1 * g_unk_00f3e2f4 + tmp_f19 * g_unk_00f3e2e8;
        tmp_l17 = (long double)VectorNormalize(&local_54);
        tmp_pi9 = pm;
        tmp_i12 = *pm;
        tmp_l17 = tmp_l17 * (long double)(float)tmp_l16;
        if ((*(byte *)(tmp_i12 + 0x6a) & 8) == 0) {
          if (((*(byte *)(tmp_i12 + 0xc) & 1) != 0) &&
             (tmp_l16 = (long double)*(int *)(tmp_i12 + 0x40) * (long double)*(float *)(tmp_i12 + 0x40c),
             tmp_l16 < tmp_l17)) {
            tmp_l17 = tmp_l16;
          }
        }
        else {
          tmp_l16 = (long double)*(int *)(tmp_i12 + 0x40) * (long double)pm_proneSpeedScale;
          if (tmp_l16 < tmp_l17) {
            tmp_l17 = tmp_l16;
          }
        }
        if (pm[0x41] != 0) {
          tmp_f1 = pm_slagSwimScale;
          if (pm[0x40] != 0x10) {
            tmp_f1 = pm_waterSwimScale;
          }
          local_84 = 1.0 - (1.0 - tmp_f1) * ((float)pm[0x41] / 3.0);
          tmp_l16 = (long double)*(int *)(tmp_i12 + 0x40) * (long double)local_84;
          if (tmp_l16 < tmp_l17) {
            tmp_l17 = tmp_l16;
          }
        }
        tmp_f1 = pm_airaccelerate;
        if (((_DAT_00f3e340 & 2) == 0) && ((*(byte *)(tmp_i12 + 0xc) & 0x40) == 0)) {
          tmp_f1 = pm_accelerate;
        }
        tmp_l16 = tmp_l17 - ((long double)*(float *)(tmp_i12 + 0x28) * (long double)local_4c +
                          (long double)*(float *)(tmp_i12 + 0x24) * (long double)local_50 +
                          (long double)*(float *)(tmp_i12 + 0x20) * (long double)local_54);
        if ((long double)0 < tmp_l16) {
          tmp_l17 = (long double)tmp_f1 * (long double)g_unk_00f3e304 * tmp_l17;
          if (tmp_l17 <= tmp_l16) {
            if (*(int *)(tmp_i12 + 0x50) != 0x3ff) goto LAB_00030eaa;
LAB_00030ebc:
            if (tmp_l16 < tmp_l17) {
              tmp_l17 = tmp_l16;
            }
          }
          else {
            tmp_l17 = tmp_l16;
            if (*(int *)(tmp_i12 + 0x50) != 0x3ff) {
LAB_00030eaa:
              tmp_l17 = (long double)
                       (float)(((long double)1 / (long double)*(float *)(tmp_i12 + 0x418)) * tmp_l17);
              goto LAB_00030ebc;
            }
          }
          *(float *)(tmp_i12 + 0x20) =
               (float)((long double)local_54 * tmp_l17 + (long double)*(float *)(tmp_i12 + 0x20));
          *(float *)(*tmp_pi9 + 0x24) =
               (float)((long double)local_50 * tmp_l17 + (long double)*(float *)(*tmp_pi9 + 0x24));
          *(float *)(*tmp_pi9 + 0x28) =
               (float)(tmp_l17 * (long double)local_4c + (long double)*(float *)(*tmp_pi9 + 0x28));
        }
        tmp_i12 = *tmp_pi9;
        if (((_DAT_00f3e340 & 2) != 0) || ((*(byte *)(tmp_i12 + 0xc) & 0x40) != 0)) {
          *(float *)(tmp_i12 + 0x28) =
               *(float *)(tmp_i12 + 0x28) - (float)*(int *)(tmp_i12 + 0x38) * g_unk_00f3e304;
          tmp_i12 = *tmp_pi9;
        }
        if ((_DAT_00f3e340 & 0x400000) == 0) {
          *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) & 0xfffffeff;
        }
        else {
          *(uint *)(tmp_i12 + 0x68) = *(uint *)(tmp_i12 + 0x68) | 0x100;
        }
        tmp_l16 = (long double)VectorLength(*tmp_pi9 + 0x20);
        tmp_pi9 = pm;
        tmp_i12 = *pm;
        tmp_f1 = g_unk_00f3e334 * *(float *)(tmp_i12 + 0x28) +
                g_unk_00f3e330 * *(float *)(tmp_i12 + 0x24) + *(float *)(tmp_i12 + 0x20) * g_unk_00f3e32c;
        if (tmp_f1 < 0.0) {
          tmp_f1 = tmp_f1 * 1.001;
        }
        else {
          tmp_f1 = tmp_f1 / 1.001;
        }
        *(float *)(tmp_i12 + 0x20) = *(float *)(tmp_i12 + 0x20) - g_unk_00f3e32c * tmp_f1;
        *(float *)(tmp_i12 + 0x24) = *(float *)(tmp_i12 + 0x24) - g_unk_00f3e330 * tmp_f1;
        *(float *)(tmp_i12 + 0x28) = *(float *)(tmp_i12 + 0x28) - tmp_f1 * g_unk_00f3e334;
        tmp_i12 = *tmp_pi9;
        if ((*(float *)(tmp_i12 + 0x20) != 0.0) || (*(float *)(tmp_i12 + 0x24) != 0.0)) {
          tmp_f1 = (float)tmp_l16;
          VectorNormalize(tmp_i12 + 0x20);
          tmp_pi9 = pm;
          *(float *)(*pm + 0x20) = *(float *)(*pm + 0x20) * tmp_f1;
          tmp_i12 = *tmp_pi9;
          *(float *)(tmp_i12 + 0x24) = *(float *)(tmp_i12 + 0x24) * tmp_f1;
          tmp_i12 = *tmp_pi9;
          *(float *)(tmp_i12 + 0x28) = tmp_f1 * *(float *)(tmp_i12 + 0x28);
          PM_StepSlideMove(0);
          PM_SetMovementDir();
          tmp_i12 = *pm;
          tmp_u11 = *(uint *)(tmp_i12 + 0x68) & 0x8000;
          tmp_pi9 = pm;
          goto LAB_0002faef;
        }
        if ((*(byte *)(tmp_i12 + 0x6a) & 8) != 0) {
          *(int *)(tmp_pi9[1] + 0x34) = tmp_pi9[3];
          tmp_i12 = *tmp_pi9;
          goto LAB_000305be;
        }
      }
      tmp_i12 = *tmp_pi9;
      goto LAB_000305be;
    }
LAB_00030270:
    *(uint32_t *)(tmp_i12 + 0x28) = 0;
    *(uint32_t *)(tmp_i12 + 0x24) = 0;
    *(uint32_t *)(tmp_i12 + 0x20) = 0;
    *(uint32_t *)(*tmp_pi9 + 0xbc) = 0x28;
    BG_AnimScriptAnimation(*tmp_pi9,*(uint32_t *)(tmp_pi9[2] + 0x7f0),1,1);
  }
  else {
    PM_LadderMove();
    tmp_i12 = *pm;
    tmp_u11 = *(uint *)(tmp_i12 + 0x68) & 0x8000;
    tmp_pi9 = pm;
LAB_0002faef:
    if (tmp_u11 != 0) goto LAB_00030270;
  }
  PM_Sprint();
  PM_GroundTrace();
  PM_SetWaterLevel();
  tmp_i12 = *pm;
  if (((((*(byte *)(tmp_i12 + 0xd) & 2) == 0) && (*(int *)(tmp_i12 + 300) != 3)) &&
      (0 < *(int *)(tmp_i12 + 0xd0))) &&
     (((tmp_u11 = *(uint *)(tmp_i12 + 0x68), (tmp_u11 & 0x800000) == 0 && ((tmp_u11 & 0x8020) == 0)) &&
      (((*(byte *)((int)pm + 0x11) & 1) != 0 && ((*(byte *)((int)pm + 0x2d) & 1) == 0)))))) {
    if (*(int *)(tmp_i12 + 0xa4) == 0x21) {
      if (((g_unk_00f3e310 != 0) && (*(int *)(tmp_i12 + 0x314) != 0)) &&
         (((tmp_u11 & 0x80000) == 0 &&
          ((pm[0x41] != 3 &&
           (tmp_l16 = (long double)VectorLengthSquared(tmp_i12 + 0x20), tmp_l16 == (long double)0)))))) {
        local_54 = *(float *)(*pm + 0x14);
        local_50 = *(float *)(*pm + 0x18);
        local_4c = *(float *)(*pm + 0x1c) + *(float *)(*pm + 0x3f8);
        tmp_u11 = (*(void *)pm[0x47])(&local_54,*(uint32_t *)(*pm + 0xa0));
        if ((tmp_u11 & 0x38) == 0) {
          tmp_i12 = *pm;
          goto LAB_0002fb7a;
        }
      }
    }
    else if ((*(int *)(tmp_i12 + 0xa4) != 0x1d) || ((tmp_u11 & 0x80000) != 0)) {
LAB_0002fb7a:
      local_84 = *(float *)(tmp_i12 + 0xa8);
      if (local_84 != 9.80909e-45) {
        tmp_u11 = *(uint *)(tmp_i12 + 0xa4);
        tmp_u13 = *(uint *)(weapAlts + tmp_u11 * 4);
        if (*(uint *)(weapAlts + tmp_u11 * 4) == 0) {
          tmp_u13 = tmp_u11;
        }
        if (tmp_u11 == 0x13) {
          if ((*(byte *)(tmp_i12 + 0x6a) & 4) == 0) {
            if (g_unk_010b3b24 == 0) {
              g_unk_010b3b24 = g_unk_010906e0;
              tmp_i12 = *pm;
              local_84 = *(float *)(tmp_i12 + 0xa8);
            }
          }
          else {
            trap_SendConsoleCommand("-zoom\n");
            g_unk_010b3b24 = -g_unk_010906e0;
            tmp_i12 = *pm;
            local_84 = *(float *)(tmp_i12 + 0xa8);
          }
        }
        if ((((((uint)local_84 & 0xfffffffd) != 1) ||
             ((((2 < (tmp_u11 & 0xfffffff7) - 0x24 && (2 < (tmp_u13 & 0xfffffff7) - 0x24)) &&
               (tmp_u11 != 0xe)) && (((tmp_u13 != 0xe && (tmp_u11 != 0x2a)) && (tmp_u13 != 0x2a)))))) &&
            ((tmp_u13 == 0 ||
             ((((*(uint *)(tmp_i12 + 0x68) & 0x8020) == 0 &&
               (tmp_i12 = COM_BitCheck(tmp_i12 + 0x3d4,tmp_u13), tmp_i12 != 0)) &&
              ((tmp_u13 == 0x14 ||
               ((tmp_i12 = *pm, tmp_i6 = BG_FindAmmoForWeapon(tmp_u13),
                *(int *)(tmp_i12 + (tmp_i6 + 100) * 4) != 0 ||
                (tmp_i12 = *pm, tmp_i6 = BG_FindClipForWeapon(tmp_u13),
                *(int *)(tmp_i12 + (tmp_i6 + 0xa4) * 4) != 0)))))))))) && (tmp_u11 != tmp_u13)) {
          BG_AddPredictableEventToPlayerstate(0x61,tmp_u13,*pm);
          PM_BeginWeaponChange(tmp_u11,tmp_u13,0);
        }
      }
    }
  }
  PM_Weapon();
  tmp_pi9 = pm;
  tmp_i12 = *pm;
  tmp_pi10 = pm;
  if ((*(uint *)(tmp_i12 + 0x68) & 0x800000) != 0) {
    tmp_u21 = 0x16;
    goto LAB_0003055a;
  }
  if ((*(uint *)(tmp_i12 + 0x68) & 1) == 0) {
    tmp_f1 = *(float *)(tmp_i12 + 0x24) * *(float *)(tmp_i12 + 0x24) +
            *(float *)(tmp_i12 + 0x20) * *(float *)(tmp_i12 + 0x20);
    tmp_f19 = SQRT(tmp_f1);
    if (NAN(tmp_f19)) {
      tmp_f19 = sqrtf(tmp_f1);
    }
    tmp_pi10 = pm;
    tmp_pi9[0x42] = (int)tmp_f19;
    tmp_i12 = *tmp_pi10;
    if (*(int *)(tmp_i12 + 0x140) != 0) {
LAB_00030530:
      tmp_u21 = 1;
LAB_0003055a:
      tmp_u20 = *(uint32_t *)(tmp_pi10[2] + 0x7f0);
      goto LAB_00030567;
    }
    tmp_i6 = tmp_pi10[0x41];
    if (2 < tmp_i6) {
      if ((*(byte *)(tmp_i12 + 0xc) & 0x10) == 0) {
        tmp_u21 = 9;
      }
      else {
        tmp_u21 = 10;
      }
      goto LAB_0003055a;
    }
    if (*(int *)(tmp_i12 + 0x50) == 0x3ff) {
      if ((*(byte *)(tmp_i12 + 0xc) & 4) != 0) {
        if (0.0 <= *(float *)(tmp_i12 + 0x28)) {
          tmp_u21 = 0xf;
        }
        else {
          if (0.0 <= *(float *)(tmp_i12 + 0x28)) goto LAB_000300c8;
          tmp_u21 = 0x10;
        }
        goto LAB_0003055a;
      }
      goto LAB_000300c8;
    }
    if ((short)tmp_pi10[8] == 0) {
      tmp_f1 = (float)tmp_pi10[0x42];
      if (tmp_f1 < 5.0) {
        *(uint32_t *)(tmp_i12 + 8) = 0;
        tmp_i12 = *tmp_pi10;
        tmp_f1 = (float)tmp_pi10[0x42];
      }
      if (120.0 < tmp_f1) {
        tmp_i6 = tmp_pi10[0x41];
        goto LAB_000300c8;
      }
      if ((*(byte *)(tmp_i12 + 0x6a) & 8) == 0) {
        if ((*(byte *)(tmp_i12 + 0xc) & 1) == 0) goto LAB_00030530;
        tmp_u21 = 2;
      }
      else {
        tmp_u21 = 0x14;
      }
      tmp_i12 = BG_AnimScriptAnimation(tmp_i12,*(uint32_t *)(tmp_pi10[2] + 0x7f0),tmp_u21,1);
      if (tmp_i12 < 0) {
        tmp_i12 = *pm;
        tmp_pi10 = pm;
        goto LAB_00030530;
      }
LAB_000312a1:
      tmp_i6 = pm[0x41];
      tmp_i12 = *pm;
      tmp_pi10 = pm;
      goto LAB_000300c8;
    }
    if ((*(byte *)(tmp_i12 + 0x6a) & 8) == 0) {
      tmp_u11 = *(uint *)(tmp_i12 + 0xc);
      if ((tmp_u11 & 1) != 0) {
        if ((tmp_u11 & 0x10) == 0) {
          tmp_u21 = 5;
        }
        else {
          tmp_u21 = 6;
        }
        tmp_b3 = false;
        tmp_i12 = BG_AnimScriptAnimation(tmp_i12,*(uint32_t *)(tmp_pi10[2] + 0x7f0),tmp_u21,1);
        tmp_f1 = 0.5;
        goto LAB_00030753;
      }
      if ((tmp_u11 & 0x10) == 0) {
        tmp_c2 = *(char *)((int)tmp_pi10 + 0x21);
        if ((*(byte *)(tmp_pi10 + 4) & 0x10) != 0) {
          if ((tmp_c2 != '\0') && ((char)tmp_pi10[8] == '\0')) {
            if (tmp_c2 < '\x01') {
              tmp_u21 = 0xc;
            }
            else {
              tmp_u21 = 0xb;
            }
            tmp_i12 = BG_AnimScriptAnimation(tmp_i12,*(uint32_t *)(tmp_pi10[2] + 0x7f0),tmp_u21,1);
            tmp_pi10 = pm;
            if (-1 < tmp_i12) goto LAB_0003153b;
          }
          tmp_u21 = 3;
          goto LAB_00031599;
        }
        if ((tmp_c2 != '\0') && ((char)tmp_pi10[8] == '\0')) {
          if (tmp_c2 < '\x01') {
            tmp_u21 = 0xc;
          }
          else {
            tmp_u21 = 0xb;
          }
          tmp_i12 = BG_AnimScriptAnimation(tmp_i12,*(uint32_t *)(tmp_pi10[2] + 0x7f0),tmp_u21,1);
          tmp_pi10 = pm;
          if (-1 < tmp_i12) goto LAB_000311ab;
        }
        tmp_u21 = 7;
LAB_000313bb:
        tmp_b3 = true;
        tmp_i12 = BG_AnimScriptAnimation(*tmp_pi10,*(uint32_t *)(tmp_pi10[2] + 0x7f0),tmp_u21,1);
        tmp_f1 = 0.4;
        goto LAB_00030753;
      }
      tmp_c2 = *(char *)((int)tmp_pi10 + 0x21);
      if ((*(byte *)(tmp_pi10 + 4) & 0x10) != 0) {
        if ((tmp_c2 != '\0') && ((char)tmp_pi10[8] == '\0')) {
          if (tmp_c2 < '\x01') {
            tmp_u21 = 0xc;
          }
          else {
            tmp_u21 = 0xb;
          }
          tmp_i12 = BG_AnimScriptAnimation(tmp_i12,*(uint32_t *)(tmp_pi10[2] + 0x7f0),tmp_u21,1);
          tmp_pi10 = pm;
          if (-1 < tmp_i12) {
LAB_0003153b:
            tmp_b3 = false;
            tmp_f1 = 0.3;
            goto LAB_0003075b;
          }
        }
        tmp_u21 = 4;
LAB_00031599:
        tmp_b3 = false;
        tmp_i12 = BG_AnimScriptAnimation(*tmp_pi10,*(uint32_t *)(tmp_pi10[2] + 0x7f0),tmp_u21,1);
        tmp_f1 = 0.3;
        goto LAB_00030753;
      }
      if ((tmp_c2 == '\0') || ((char)tmp_pi10[8] != '\0')) {
LAB_00031625:
        tmp_u21 = 8;
        goto LAB_000313bb;
      }
      if (tmp_c2 < '\x01') {
        tmp_u21 = 0xc;
      }
      else {
        tmp_u21 = 0xb;
      }
      tmp_i12 = BG_AnimScriptAnimation(tmp_i12,*(uint32_t *)(tmp_pi10[2] + 0x7f0),tmp_u21,1);
      tmp_pi10 = pm;
      if (tmp_i12 < 0) goto LAB_00031625;
LAB_000311ab:
      tmp_b3 = true;
      tmp_f1 = 0.4;
    }
    else {
      if ((*(byte *)(tmp_i12 + 0xc) & 0x10) == 0) {
        tmp_u21 = 0x12;
      }
      else {
        tmp_u21 = 0x13;
      }
      tmp_b3 = false;
      tmp_i12 = BG_AnimScriptAnimation(tmp_i12,*(uint32_t *)(tmp_pi10[2] + 0x7f0),tmp_u21,1);
      tmp_f1 = 0.2;
LAB_00030753:
      if (tmp_i12 < 0) {
        BG_AnimScriptAnimation(*pm,*(uint32_t *)(pm[2] + 0x7f0),1,1);
      }
    }
LAB_0003075b:
    tmp_pi10 = pm;
    tmp_i8 = *(int *)(*pm + 8);
    *(uint *)(*pm + 8) = (int)ROUND((float)tmp_i8 + (float)g_unk_00f3e308 * tmp_f1) & 0xff;
    tmp_i12 = *tmp_pi10;
    tmp_i6 = tmp_pi10[0x41];
    if (((tmp_i8 + 0x40U ^ *(int *)(tmp_i12 + 8) + 0x40U) & 0x80) == 0) goto LAB_000300c8;
    if (tmp_i6 == 1) {
      BG_AddPredictableEventToPlayerstate(9,0,tmp_i12);
      tmp_i6 = pm[0x41];
      tmp_i12 = *pm;
      tmp_pi10 = pm;
      goto LAB_000300c8;
    }
    if (tmp_i6 == 2) {
      BG_AddPredictableEventToPlayerstate(10,0,tmp_i12);
      goto LAB_000312a1;
    }
    if (tmp_i6 != 0) goto LAB_000300c8;
    if (tmp_b3) {
      tmp_u21 = BG_FootstepForSurface(_DAT_00f3e340);
      BG_AddPredictableEventToPlayerstate(1,tmp_u21,*pm);
      tmp_i6 = pm[0x41];
      tmp_i12 = *pm;
      tmp_pi10 = pm;
      goto LAB_000300c8;
    }
    if (g_unk_00f3e368 == 0) goto LAB_000300da;
LAB_000307f0:
    BG_AddPredictableEventToPlayerstate(0x13,0,tmp_i12);
    tmp_i6 = pm[0x41];
    tmp_i12 = *pm;
    tmp_pi10 = pm;
LAB_00030158:
    if (g_unk_00f3e368 != 3) goto LAB_000301e2;
LAB_00030161:
    if (tmp_i6 == 3) goto LAB_000300da;
    BG_AddPredictableEventToPlayerstate(0x15,*(int *)(tmp_pi10[1] + 0x14) < 6000,tmp_i12);
  }
  else {
    tmp_u11 = *(uint *)(tmp_i12 + 0xc);
    if ((tmp_u11 & 0x800) == 0) {
      if ((*(int *)(tmp_i12 + 0x10) != 0) || ((tmp_u11 & 0x4000) != 0)) goto LAB_000300c2;
      if (*(int *)(tmp_i12 + 0x50) != 0x3ff) {
        tmp_u21 = 0x11;
        goto LAB_0003055a;
      }
      *(uint *)(tmp_i12 + 0xc) = tmp_u11 | 0x800;
      tmp_u21 = 0x15;
      tmp_u20 = *(uint32_t *)(tmp_pi9[2] + 0x7f0);
      tmp_i12 = *tmp_pi9;
LAB_00030567:
      BG_AnimScriptAnimation(tmp_i12,tmp_u20,tmp_u21,1);
      tmp_i6 = pm[0x41];
      tmp_i12 = *pm;
      tmp_pi10 = pm;
    }
    else {
      BG_AnimScriptAnimation(tmp_i12,*(uint32_t *)(pm[2] + 0x7f0),0x15,1);
      tmp_pi10 = pm;
      tmp_i12 = *pm;
      if (*(int *)(tmp_i12 + 0x10) == 0) {
        *(uint *)(tmp_i12 + 0xc) = *(uint *)(tmp_i12 + 0xc) & 0xfffff7ff;
        tmp_i6 = tmp_pi10[0x41];
        tmp_i12 = *tmp_pi10;
        goto LAB_000300c8;
      }
LAB_000300c2:
      tmp_i6 = pm[0x41];
      tmp_pi10 = pm;
    }
LAB_000300c8:
    if (g_unk_00f3e368 != 0) {
LAB_00030150:
      if (tmp_i6 == 0) goto LAB_000307f0;
      goto LAB_00030158;
    }
    if (tmp_i6 == 0) goto LAB_000300da;
    BG_AddPredictableEventToPlayerstate(0x12,0,tmp_i12);
    if (g_unk_00f3e368 != 0) {
      tmp_i6 = pm[0x41];
      tmp_i12 = *pm;
      tmp_pi10 = pm;
      goto LAB_00030150;
    }
    tmp_i6 = pm[0x41];
    tmp_i12 = *pm;
LAB_000301e2:
    if (tmp_i6 != 3) goto LAB_000300da;
    BG_AddPredictableEventToPlayerstate(0x14,0,tmp_i12);
    if (g_unk_00f3e368 == 3) {
      tmp_i6 = pm[0x41];
      tmp_i12 = *pm;
      tmp_pi10 = pm;
      goto LAB_00030161;
    }
  }
  tmp_i12 = *pm;
LAB_000300da:
  if (GHIDRA_FIELD(cgs, 33823116, 4) == 0) {
    trap_SnapVector(tmp_i12 + 0x20);
    tmp_pi9 = pm;
  }
  else {
    tmp_l16 = (long double)VectorLengthSquared();
    tmp_pi9 = pm;
    if ((long double)0.25 <= tmp_l16) {
      if ((int)GHIDRA_FIELD(cgs, 33823120, 4) < 0x14e) {
        if ((int)GHIDRA_FIELD(cgs, 33823120, 4) < 0x3c) {
          tmp_f1 = 16.666666;
        }
        else {
          tmp_f1 = 1000.0 / (float)(int)GHIDRA_FIELD(cgs, 33823120, 4);
        }
      }
      else {
        tmp_f1 = 3.0030031;
      }
      tmp_i12 = *pm;
      tmp_f1 = (float)g_unk_00f3e308 / tmp_f1;
      tmp_f4 = 0.5 / tmp_f1;
      tmp_f19 = *(float *)(tmp_i12 + 0x20);
      if (tmp_f4 < ABS(tmp_f19 - g_unk_00f3e35c)) {
        if (tmp_f19 < 0.0) {
          *(float *)(tmp_i12 + 0x20) = tmp_f19 - tmp_f1 * 0.5;
          tmp_i12 = *tmp_pi9;
        }
        else {
          *(float *)(tmp_i12 + 0x20) = tmp_f1 * 0.5 + tmp_f19;
          tmp_i12 = *tmp_pi9;
        }
      }
      tmp_f19 = *(float *)(tmp_i12 + 0x24);
      if (tmp_f4 < ABS(tmp_f19 - g_unk_00f3e360)) {
        if (tmp_f19 < 0.0) {
          *(float *)(tmp_i12 + 0x24) = tmp_f19 - tmp_f1 * 0.5;
          tmp_i12 = *tmp_pi9;
        }
        else {
          *(float *)(tmp_i12 + 0x24) = tmp_f1 * 0.5 + tmp_f19;
          tmp_i12 = *tmp_pi9;
        }
      }
      tmp_f19 = *(float *)(tmp_i12 + 0x28);
      if (tmp_f4 < ABS(tmp_f19 - g_unk_00f3e364)) {
        if (tmp_f19 < 0.0) {
          *(float *)(tmp_i12 + 0x28) = tmp_f19 - tmp_f1 * 0.5;
          tmp_i12 = *tmp_pi9;
        }
        else {
          *(float *)(tmp_i12 + 0x28) = tmp_f1 * 0.5 + tmp_f19;
          tmp_i12 = *tmp_pi9;
        }
      }
      *(float *)(tmp_i12 + 0x20) = *(float *)(tmp_i12 + 0x20) * 64.0;
      *(float *)(*tmp_pi9 + 0x24) = *(float *)(*tmp_pi9 + 0x24) * 64.0;
      *(float *)(*tmp_pi9 + 0x28) = *(float *)(*tmp_pi9 + 0x28) * 64.0;
      trap_SnapVector(*tmp_pi9 + 0x20);
      tmp_pi9 = pm;
      *(float *)(*pm + 0x20) = *(float *)(*pm + 0x20) * 0.015625;
      *(float *)(*tmp_pi9 + 0x24) = *(float *)(*tmp_pi9 + 0x24) * 0.015625;
      *(float *)(*tmp_pi9 + 0x28) = *(float *)(*tmp_pi9 + 0x28) * 0.015625;
    }
    else {
      tmp_i12 = *pm;
      *(uint32_t *)(tmp_i12 + 0x28) = 0;
      *(uint32_t *)(tmp_i12 + 0x24) = 0;
      *(uint32_t *)(tmp_i12 + 0x20) = 0;
    }
  }
  *(uint32_t *)(*tmp_pi9 + 0xe8) = *(uint32_t *)(tmp_pi9[1] + 0x10);
  return;
}

uint Pmove(int *param_1)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  int *tmp_pi4;
  int tmp_i5;
  int tmp_i6;
  uint tmp_u7;
  
  tmp_pi4 = (int *)*param_1;
  tmp_i6 = param_1[3];
  tmp_i1 = tmp_pi4[0xe];
  if (*tmp_pi4 <= tmp_i6) {
    if (*tmp_pi4 + 1000 < tmp_i6) {
      *tmp_pi4 = tmp_i6 + -1000;
      tmp_pi4 = (int *)*param_1;
    }
    pm = param_1;
    tmp_pi4[0x11b] = tmp_pi4[0x11b] + 1U & 0x3f;
    tmp_pi4 = (int *)*param_1;
    while (tmp_pi3 = pm, tmp_i2 = *tmp_pi4, tmp_i2 != tmp_i6) {
      tmp_i5 = tmp_i6 - tmp_i2;
      if (param_1[0x44] == 0) {
        if (0x32 < tmp_i5) {
          tmp_i5 = 0x32;
        }
      }
      else if (param_1[0x45] < tmp_i5) {
        tmp_i5 = param_1[0x45];
      }
      param_1[3] = tmp_i5 + tmp_i2;
      PM_AdjustAimSpreadScale();
      *(int *)(*param_1 + 0x38) = tmp_i1;
      PmoveSingle(param_1);
      tmp_pi4 = (int *)*param_1;
      if ((*(byte *)(tmp_pi4 + 3) & 2) != 0) {
        *(uint8_t *)((int)param_1 + 0x22) = 0x14;
      }
    }
    if (tmp_pi4[0x167] < 0x100) {
      if (tmp_pi4[0x167] < 0) {
        tmp_pi4[0x167] = 0;
        tmp_i6 = *tmp_pi3;
      }
      else {
        tmp_i6 = *pm;
        if ((((GHIDRA_FIELD(cgs, 33787496, 4) & 0x20) != 0) && (*(int *)(tmp_i6 + 0xa4) == 10)) ||
           (((GHIDRA_FIELD(cgs, 33787496, 4) & 0x40) != 0 &&
            ((*(int *)(tmp_i6 + 0xa4) == 0x2e || (*(int *)(tmp_i6 + 0xa4) == 0x1d)))))) {
          tmp_pi4[0x167] = 0;
          tmp_i6 = *tmp_pi3;
        }
      }
    }
    else {
      tmp_pi4[0x167] = 0xff;
      tmp_i6 = *tmp_pi3;
    }
    if ((*(int *)(tmp_i6 + 0xd0) < 1) || (*(int *)(tmp_i6 + 4) == 3)) {
      tmp_u7 = 0;
      if ((_DAT_00f3e340 & 0x4000000) != 0) {
        tmp_u7 = _DAT_00f3e340;
      }
      return tmp_u7;
    }
  }
  return 0;
}

void PmovePredict(int *param_1,uint32_t param_2)
{
  uint tmp_u1;
  
  pm = param_1;
  tmp_u1 = 0;
  do {
    *(uint32_t *)((int)&pml + tmp_u1) = 0;
    *(uint32_t *)((int)&g_unk_00f3e2e4 + tmp_u1) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x90);
  g_unk_00f3e304 = param_2;
  PM_GroundTrace();
  if ((g_unk_00f3e310 == 0) && ((*(byte *)(*pm + 0xc) & 4) == 0)) {
    PM_StepSlideMove(1);
    return;
  }
  PM_StepSlideMove(0);
  return;
}

bool PM_SlideMove(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  bool tmp_b7;
  int *tmp_pi8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  float *pfVar12;
  int tmp_i13;
  float *pfVar14;
  float local_114;
  int local_110;
  int local_f0;
  float local_d4;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float *local_90;
  uint32_t local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  uint32_t local_5c;
  float local_58 [4];
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
  uint32_t uStack_14;
  
  tmp_pi8 = pm;
  uStack_14 = 0x31cb9;
  tmp_i11 = *pm;
  tmp_f1 = *(float *)(tmp_i11 + 0x20);
  tmp_u2 = *(uint32_t *)(tmp_i11 + 0x24);
  local_d4 = *(float *)(tmp_i11 + 0x28);
  if (param_1 == 0) {
    local_ac = 0.0;
    local_b0 = 0.0;
    local_b4 = 0.0;
LAB_00032685:
    local_114 = g_unk_00f3e304;
    tmp_pi8 = pm;
    if (g_unk_00f3e310 != 0) {
      local_58[0] = g_unk_00f3e32c;
      tmp_i13 = 2;
      tmp_i11 = 1;
      local_58[1] = g_unk_00f3e330;
      local_58[2] = g_unk_00f3e334;
      goto LAB_00031d5d;
    }
  }
  else {
    local_b0 = *(float *)(*pm + 0x24);
    local_114 = g_unk_00f3e304;
    local_d4 = *(float *)(*pm + 0x28) - (float)*(int *)(*pm + 0x38) * g_unk_00f3e304;
    *(float *)(*pm + 0x28) = (*(float *)(*pm + 0x28) + local_d4) * 0.5;
    local_b4 = tmp_f1;
    local_ac = local_d4;
    if (g_unk_00f3e310 != 0) {
      tmp_i11 = *tmp_pi8 + 0x20;
      PM_ClipVelocity(tmp_i11,&g_unk_00f3e32c,tmp_i11,0x3f8020c5);
      goto LAB_00032685;
    }
  }
  tmp_i13 = 1;
  tmp_i11 = 0;
LAB_00031d5d:
  VectorNormalize2(*tmp_pi8 + 0x20,local_58 + tmp_i11 * 3);
  local_f0 = 4;
  local_110 = 0;
  tmp_i11 = *pm;
  tmp_b7 = false;
  tmp_pi8 = pm;
  do {
    local_c0 = *(float *)(tmp_i11 + 0x20) * local_114 + *(float *)(tmp_i11 + 0x14);
    local_bc = *(float *)(*tmp_pi8 + 0x24) * local_114 + *(float *)(*tmp_pi8 + 0x18);
    local_b8 = *(float *)(*tmp_pi8 + 0x28) * local_114 + *(float *)(*tmp_pi8 + 0x1c);
    pfVar14 = &local_c0;
    PM_TraceAll(&local_90,*tmp_pi8 + 0x14,&local_c0);
    if (1 < pm[0x12]) {
      pfVar14 = local_90;
      Com_Printf("%i:%d %d (%f %f %f)\n",c_pmove,local_90,local_8c,(double)local_84,(double)local_80
                 ,(double)local_7c);
    }
    tmp_pi8 = pm;
    if (local_90 != (float *)0x0) {
      *(uint32_t *)(*pm + 0x28) = 0;
      return true;
    }
    if (0.0 < local_88) {
      *(float *)(*pm + 0x14) = local_84;
      *(float *)(*tmp_pi8 + 0x18) = local_80;
      *(float *)(*tmp_pi8 + 0x1c) = local_7c;
    }
    if (local_88 == 1.0) {
      tmp_i11 = *pm;
      tmp_pi8 = pm;
      break;
    }
    PM_AddTouchEnt(local_5c);
    tmp_pi8 = pm;
    local_114 = local_114 - local_88 * local_114;
    if (tmp_i13 == 5) {
LAB_00032450:
      tmp_i11 = *pm;
      *(uint32_t *)(tmp_i11 + 0x28) = 0;
      *(uint32_t *)(tmp_i11 + 0x24) = 0;
      *(uint32_t *)(tmp_i11 + 0x20) = 0;
      return true;
    }
    if (0.99 < local_58[2] * local_70 + local_58[1] * local_74 + local_58[0] * local_78) {
      tmp_i11 = 0;
      goto LAB_00032750;
    }
    if (tmp_i13 == 1) {
LAB_00031fd0:
      local_58[tmp_i13 * 3] = local_78;
      local_58[tmp_i13 * 3 + 1] = local_74;
      local_58[tmp_i13 * 3 + 2] = local_70;
LAB_00031fe8:
      tmp_i10 = tmp_i13 + 1;
      tmp_i11 = *tmp_pi8;
      tmp_f3 = *(float *)(tmp_i11 + 0x20);
      tmp_f4 = *(float *)(tmp_i11 + 0x24);
      tmp_f5 = *(float *)(tmp_i11 + 0x28);
      tmp_f6 = local_58[2] * tmp_f5 + local_58[1] * tmp_f4 + local_58[0] * tmp_f3;
      if (tmp_f6 < 0.1) {
        tmp_i9 = 0;
LAB_0003202e:
        if (g_unk_00f3e34c < -tmp_f6) {
          tmp_i11 = *tmp_pi8;
          g_unk_00f3e34c = -tmp_f6;
        }
        pfVar14 = local_58 + tmp_i9 * 3;
        PM_ClipVelocity(tmp_i11 + 0x20,pfVar14,&local_cc,0x3f8020c5);
        tmp_i13 = 0;
        PM_ClipVelocity(&local_b4,pfVar14,&local_a8,0x3f8020c5);
        pfVar12 = local_58;
        tmp_f3 = local_cc;
        tmp_f5 = local_c8;
        tmp_f4 = local_c4;
        do {
          if ((tmp_i13 != tmp_i9) &&
             (pfVar12[2] * tmp_f4 + pfVar12[1] * tmp_f5 + *pfVar12 * tmp_f3 < 0.1)) {
            PM_ClipVelocity(&local_cc,pfVar12,&local_cc,0x3f8020c5);
            PM_ClipVelocity(&local_a8,pfVar12,&local_a8,0x3f8020c5);
            tmp_f4 = local_c4;
            tmp_f5 = local_c8;
            tmp_f3 = local_cc;
            if (local_58[tmp_i9 * 3 + 2] * local_c4 +
                local_58[tmp_i9 * 3 + 1] * local_c8 + local_58[tmp_i9 * 3] * local_cc < 0.0) {
              CrossProduct(pfVar14,pfVar12,&local_9c);
              VectorNormalize(&local_9c);
              tmp_i11 = *pm;
              local_c4 = local_94 * *(float *)(tmp_i11 + 0x28) +
                         local_98 * *(float *)(tmp_i11 + 0x24) + local_9c * *(float *)(tmp_i11 + 0x20)
              ;
              local_cc = local_9c * local_c4;
              local_c8 = local_98 * local_c4;
              local_c4 = local_c4 * local_94;
              CrossProduct(pfVar14,pfVar12,&local_9c);
              VectorNormalize(&local_9c);
              local_a0 = local_94 * local_ac + local_98 * local_b0 + local_9c * local_b4;
              local_a8 = local_9c * local_a0;
              local_a4 = local_98 * local_a0;
              local_a0 = local_a0 * local_94;
              if (((((tmp_i13 != 0) && (tmp_i9 != 0)) &&
                   (local_58[2] * local_c4 + local_58[1] * local_c8 + local_58[0] * local_cc < 0.1))
                  || (((tmp_i13 != 1 && (tmp_i9 != 1)) &&
                      (local_44 * local_c4 + local_48 * local_c8 + local_58[3] * local_cc < 0.1))))
                 || ((tmp_f4 = local_c4, tmp_f5 = local_c8, tmp_f3 = local_cc, tmp_i10 != 2 &&
                     ((((tmp_i13 != 2 && (tmp_i9 != 2)) &&
                       (local_38 * local_c4 + local_3c * local_c8 + local_40 * local_cc < 0.1)) ||
                      ((tmp_i10 != 3 &&
                       ((((tmp_i13 != 3 && (tmp_i9 != 3)) &&
                         (local_2c * local_c4 + local_30 * local_c8 + local_34 * local_cc < 0.1)) ||
                        (((tmp_i10 == 5 && (tmp_i9 != 4)) &&
                         ((tmp_i13 != 4 &&
                          (local_20 * local_c4 + local_24 * local_c8 + local_28 * local_cc < 0.1))))
                        )))))))))) goto LAB_00032450;
            }
          }
          tmp_pi8 = pm;
          tmp_i13 = tmp_i13 + 1;
          pfVar12 = pfVar12 + 3;
        } while (tmp_i13 != tmp_i10);
        *(float *)(*pm + 0x20) = tmp_f3;
        *(float *)(*tmp_pi8 + 0x24) = tmp_f5;
        *(float *)(*tmp_pi8 + 0x28) = tmp_f4;
        local_b4 = local_a8;
        local_b0 = local_a4;
        local_ac = local_a0;
        goto LAB_0003264d;
      }
      tmp_f6 = local_44 * tmp_f5 + local_48 * tmp_f4 + local_58[3] * tmp_f3;
      if (tmp_f6 < 0.1) {
        tmp_i9 = 1;
        goto LAB_0003202e;
      }
      if (tmp_i10 == 2) {
        tmp_i13 = 2;
      }
      else {
        tmp_f6 = local_38 * tmp_f5 + local_3c * tmp_f4 + local_40 * tmp_f3;
        if (tmp_f6 < 0.1) {
          tmp_i9 = 2;
          goto LAB_0003202e;
        }
        if (tmp_i10 == 3) {
          tmp_i13 = 3;
        }
        else {
          tmp_f6 = local_2c * tmp_f5 + local_30 * tmp_f4 + local_34 * tmp_f3;
          if (tmp_f6 < 0.1) {
            tmp_i9 = 3;
            goto LAB_0003202e;
          }
          if (tmp_i10 == 5) {
            tmp_i9 = 4;
            tmp_f6 = tmp_f5 * local_20 + tmp_f4 * local_24 + tmp_f3 * local_28;
            if (tmp_f6 < 0.1) goto LAB_0003202e;
            tmp_i13 = 5;
          }
          else {
            tmp_i13 = 4;
          }
        }
      }
    }
    else {
      if (0.99 < local_44 * local_70 + local_48 * local_74 + local_58[3] * local_78) {
        tmp_i11 = 1;
        goto LAB_00032750;
      }
      if (tmp_i13 == 2) goto LAB_00031fd0;
      if (0.99 < local_38 * local_70 + local_3c * local_74 + local_40 * local_78) {
        tmp_i11 = 2;
LAB_00032750:
        if (tmp_b7) {
          local_c0 = local_78 + *(float *)(*pm + 0x14);
          local_bc = local_74 + *(float *)(*pm + 0x18);
          local_b8 = local_70 + *(float *)(*pm + 0x1c);
          PM_TraceAll(&local_90,*pm + 0x14,&local_c0);
          tmp_pi8 = pm;
          *(float *)(*pm + 0x14) = local_84;
          *(float *)(*tmp_pi8 + 0x18) = local_80;
          *(float *)(*tmp_pi8 + 0x1c) = local_7c;
          tmp_b7 = true;
          if (tmp_pi8[0x12] != 0) {
            Com_Printf("%i:planeoriginnudge\n",c_pmove);
            tmp_pi8 = pm;
          }
        }
        else {
          local_f0 = local_f0 + 1;
          *(float *)(*pm + 0x20) = local_78 + *(float *)(*pm + 0x20);
          *(float *)(*tmp_pi8 + 0x24) = local_74 + *(float *)(*tmp_pi8 + 0x24);
          *(float *)(*tmp_pi8 + 0x28) = *(float *)(*tmp_pi8 + 0x28) + local_70;
          tmp_b7 = true;
          if (tmp_pi8[0x12] != 0) {
            Com_Printf("%i:planevelocitynudge\n",c_pmove,pfVar14);
            tmp_pi8 = pm;
          }
        }
      }
      else {
        if (tmp_i13 == 4) {
          if (local_2c * local_70 + local_30 * local_74 + local_34 * local_78 <= 0.99)
          goto LAB_00031fd0;
          tmp_i11 = 3;
          goto LAB_00032750;
        }
        tmp_i11 = 3;
      }
      if (tmp_i13 <= tmp_i11) {
        local_58[tmp_i13 * 3] = local_78;
        local_58[tmp_i13 * 3 + 1] = local_74;
        local_58[tmp_i13 * 3 + 2] = local_70;
        goto LAB_00031fe8;
      }
LAB_0003264d:
      tmp_i11 = *tmp_pi8;
    }
    local_110 = local_110 + 1;
  } while (local_110 < local_f0);
  if (param_1 != 0) {
    *(float *)(tmp_i11 + 0x20) = local_b4;
    *(float *)(*tmp_pi8 + 0x24) = local_b0;
    *(float *)(*tmp_pi8 + 0x28) = local_ac;
    tmp_i11 = *tmp_pi8;
  }
  if (*(int *)(tmp_i11 + 0x10) != 0) {
    *(float *)(tmp_i11 + 0x20) = tmp_f1;
    *(uint32_t *)(*tmp_pi8 + 0x24) = tmp_u2;
    *(float *)(*tmp_pi8 + 0x28) = local_d4;
  }
  return local_110 != 0;
}

void PM_StepSlideMove(uint32_t param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  float tmp_f4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  uint32_t tmp_u7;
  uint32_t tmp_u8;
  uint32_t tmp_u9;
  int tmp_i10;
  int tmp_i11;
  int *tmp_pi12;
  uint tmp_u13;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  int local_54 [2];
  float local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  float local_3c;
  float local_38;
  float local_34;
  
  local_78 = *(float *)(*pm + 0x14);
  local_74 = *(float *)(*pm + 0x18);
  local_70 = *(float *)(*pm + 0x1c);
  tmp_i11 = *pm;
  tmp_u1 = *(uint32_t *)(tmp_i11 + 0x20);
  tmp_u2 = *(uint32_t *)(tmp_i11 + 0x24);
  tmp_u3 = *(uint32_t *)(tmp_i11 + 0x28);
  if (pm[0x12] == 0) {
    tmp_i11 = PM_SlideMove(param_1);
  }
  else {
    PM_TraceAll(local_54,tmp_i11 + 0x14,tmp_i11 + 0x14);
    tmp_i10 = local_54[0];
    tmp_i11 = PM_SlideMove(param_1);
    PM_TraceAll(local_54,*pm + 0x14,*pm + 0x14);
    if ((local_54[0] != 0) && (tmp_i10 == 0)) {
      tmp_i10 = *pm;
      Com_Printf("%i:PM_SlideMove solidified! (%f %f %f) -> (%f %f %f)\n",c_pmove,(double)local_78,
                 (double)local_74,(double)local_70,(double)*(float *)(tmp_i10 + 0x14),
                 (double)*(float *)(tmp_i10 + 0x18),(double)*(float *)(tmp_i10 + 0x1c));
    }
  }
  if (tmp_i11 != 0) {
    if (pm[0x12] != 0) {
      Com_Printf("%i:stepping\n",c_pmove);
    }
    local_60 = local_78;
    local_5c = local_74;
    local_58 = local_70 - 18.0;
    PM_TraceAll(local_54,&local_78,&local_60);
    tmp_i11 = *pm;
    tmp_f4 = *(float *)(tmp_i11 + 0x28);
    if ((tmp_f4 <= 0.0) || ((local_4c != 1.0 && (0.7 <= local_38 * 0.0 + local_3c * 0.0 + local_34)))
       ) {
      tmp_u5 = *(uint32_t *)(tmp_i11 + 0x14);
      tmp_u6 = *(uint32_t *)(tmp_i11 + 0x18);
      tmp_u7 = *(uint32_t *)(tmp_i11 + 0x1c);
      tmp_u8 = *(uint32_t *)(tmp_i11 + 0x20);
      tmp_u9 = *(uint32_t *)(tmp_i11 + 0x24);
      local_6c = local_78;
      local_68 = local_74;
      local_64 = local_70 + 18.0;
      PM_TraceAll(local_54,&local_6c,&local_6c);
      tmp_pi12 = pm;
      if (local_54[0] == 0) {
        *(float *)(*pm + 0x14) = local_6c;
        *(float *)(*tmp_pi12 + 0x18) = local_68;
        *(float *)(*tmp_pi12 + 0x1c) = local_64;
        *(uint32_t *)(*tmp_pi12 + 0x20) = tmp_u1;
        *(uint32_t *)(*tmp_pi12 + 0x24) = tmp_u2;
        *(uint32_t *)(*tmp_pi12 + 0x28) = tmp_u3;
        PM_SlideMove(param_1);
        local_60 = *(float *)(*pm + 0x14);
        local_5c = *(float *)(*pm + 0x18);
        local_58 = *(float *)(*pm + 0x1c) - 18.0;
        if ((*(byte *)(*pm + 0x6a) & 8) != 0) {
          tmp_u13 = 0;
          do {
            *(uint32_t *)((int)local_54 + tmp_u13) = 0;
            *(uint32_t *)((int)local_54 + tmp_u13 + 4) = 0;
            tmp_u13 = tmp_u13 + 8;
          } while (tmp_u13 < 0x38);
          tmp_i11 = *pm;
          PM_TraceLegs(local_54,0,tmp_i11 + 0x14,&local_60,0,tmp_i11 + 0xb0,pm[0x46],
                       *(uint32_t *)(tmp_i11 + 0xa0),pm[0x11]);
          tmp_pi12 = pm;
          if (local_4c < 1.0) {
            *(uint32_t *)(*pm + 0x14) = tmp_u5;
            *(uint32_t *)(*tmp_pi12 + 0x18) = tmp_u6;
            *(uint32_t *)(*tmp_pi12 + 0x1c) = tmp_u7;
            *(uint32_t *)(*tmp_pi12 + 0x20) = tmp_u8;
            *(uint32_t *)(*tmp_pi12 + 0x24) = tmp_u9;
            *(float *)(*tmp_pi12 + 0x28) = tmp_f4;
            if (tmp_pi12[0x12] == 0) {
              return;
            }
            Com_Printf("%i:legs unsteppable\n",c_pmove);
            return;
          }
        }
        tmp_u13 = 0;
        do {
          *(uint32_t *)((int)local_54 + tmp_u13) = 0;
          *(uint32_t *)((int)local_54 + tmp_u13 + 4) = 0;
          tmp_u13 = tmp_u13 + 8;
        } while (tmp_u13 < 0x38);
        (*(void *)pm[0x46])(local_54,*pm + 0x14,pm + 0x3a,pm + 0x3d,&local_60,
                            *(uint32_t *)(*pm + 0xa0),pm[0x11]);
        tmp_pi12 = pm;
        if (local_54[0] == 0) {
          *(uint32_t *)(*pm + 0x14) = local_48;
          *(uint32_t *)(*tmp_pi12 + 0x18) = local_44;
          *(uint32_t *)(*tmp_pi12 + 0x1c) = local_40;
        }
        if (local_4c < 1.0) {
          PM_ClipVelocity(*tmp_pi12 + 0x20,&local_3c,*tmp_pi12 + 0x20,0x3f8020c5);
          tmp_pi12 = pm;
        }
        tmp_f4 = *(float *)(*tmp_pi12 + 0x1c) - local_70;
        if (2.0 < tmp_f4) {
          if (tmp_f4 < 7.0) {
            PM_AddEventExt(0xb,4);
            tmp_pi12 = pm;
          }
          else if (tmp_f4 < 11.0) {
            PM_AddEventExt(0xb,8);
            tmp_pi12 = pm;
          }
          else if (15.0 <= tmp_f4) {
            PM_AddEventExt(0xb,0x10);
            tmp_pi12 = pm;
          }
          else {
            PM_AddEventExt(0xb,0xc);
            tmp_pi12 = pm;
          }
        }
        if (tmp_pi12[0x12] != 0) {
          Com_Printf("%i:stepped\n",c_pmove);
        }
      }
      else if (pm[0x12] != 0) {
        Com_Printf("%i:bend can\'t step\n",c_pmove);
      }
    }
  }
  return;
}

