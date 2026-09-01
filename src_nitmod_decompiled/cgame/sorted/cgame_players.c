/* Client/player model and character information — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_players.h"

uint32_t CG_PlayerSelected(void)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  
  if (((g_unk_01047b04 == 0) || (g_unk_010906d8 != 0)) || (tmp_i2 = g_unk_01047b04, g_unk_010906d4 != 0)) {
    tmp_i2 = g_unk_01047b00;
  }
  if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
    tmp_pi1 = (int *)(cgs + 0x9494);
    tmp_i3 = 0;
    do {
      if ((*tmp_pi1 == *(int *)(tmp_i2 + 0x158)) && (tmp_pi1[0xc] != 0)) {
        return 1;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pi1 = tmp_pi1 + 0x69;
    } while (tmp_i3 != GHIDRA_FIELD(cgs, 27400, 4));
  }
  return 0;
}

bool CG_PlayerSeesItem(int param_1,int param_2,uint32_t param_3)
{
  bool tmp_b1;
  long double tmp_l2;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  BG_EvaluateTrajectory(param_2 + 0xc,param_3,&local_30,0,*(uint32_t *)(param_2 + 0x110));
  local_18 = *(float *)(param_1 + 0x14) - local_30;
  local_14 = *(float *)(param_1 + 0x18) - local_2c;
  local_10 = ((float)*(int *)(param_1 + 0xbc) + *(float *)(param_1 + 0x1c)) - local_28;
  tmp_l2 = (long double)VectorNormalize(&local_18);
  tmp_b1 = false;
  if (tmp_l2 <= (long double)255.0) {
    AngleVectors(param_1 + 0xb0,&local_24,0,0);
    tmp_b1 = local_1c * local_10 + local_20 * local_14 + local_24 * local_18 <=
            -0.94 - (float)tmp_l2 * 0.003921569 * 0.057;
  }
  return tmp_b1;
}

uint32_t CG_CustomSound(int param_1)
{
  uint32_t tmp_u1;
  
  if (param_1 != 0) {
    tmp_u1 = trap_S_RegisterSound(param_1,0);
    return tmp_u1;
  }
  return 0;
}

int CG_PlayerSFFromPos(int param_1,int *param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  uint8_t *tmp_pu6;
  int local_28;
  int local_20;
  
  tmp_i1 = CG_IsOnFireteam(g_unk_01047ac4);
  if (tmp_i1 == 0) {
    *param_2 = 0;
    return -1;
  }
  tmp_pu6 = cgs;
  if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
    if (*param_2 < 1) {
      return -1;
    }
  }
  else {
    local_28 = 0;
    tmp_i5 = 0;
    tmp_i1 = GHIDRA_FIELD(cgs, 27400, 4);
    tmp_pu4 = tmp_pu6;
    do {
      if (((g_unk_01047ac4 != tmp_i5) && (*(int *)(tmp_pu4 + 0x940c) != 0)) &&
         (*(int *)(tmp_pu4 + 0x9494) == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) {
        tmp_i2 = CG_IsOnFireteam(tmp_i5);
        tmp_i3 = CG_IsOnFireteam(g_unk_01047ac4);
        tmp_i1 = GHIDRA_FIELD(cgs, 27400, 4);
        if (tmp_i2 == tmp_i3) {
          local_28 = local_28 + 1;
        }
      }
      tmp_i5 = tmp_i5 + 1;
      tmp_pu4 = tmp_pu4 + 0x1a4;
    } while (tmp_i5 < tmp_i1);
    if (*param_2 * 8 - local_28 == 0 || *param_2 * 8 < local_28) goto LAB_000789ef;
  }
  *param_2 = 0;
  tmp_i1 = GHIDRA_FIELD(cgs, 27400, 4);
LAB_000789ef:
  if (0 < tmp_i1) {
    tmp_i5 = 0;
    local_20 = 0;
    do {
      while (((g_unk_01047ac4 != tmp_i5 && (*(int *)(tmp_pu6 + 0x940c) != 0)) &&
             (*(int *)(tmp_pu6 + 0x9494) == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494)))) {
        tmp_i1 = CG_IsOnFireteam(tmp_i5);
        tmp_i2 = CG_IsOnFireteam(g_unk_01047ac4);
        if (tmp_i1 == tmp_i2) {
          tmp_i1 = *param_2 * 8;
          if (((tmp_i1 - local_20 == 0 || tmp_i1 < local_20) && (local_20 < tmp_i1 + 8)) &&
             (param_1 == local_20 + *param_2 * -8)) {
            return tmp_i5;
          }
          local_20 = local_20 + 1;
        }
        tmp_i5 = tmp_i5 + 1;
        tmp_pu6 = tmp_pu6 + 0x1a4;
        tmp_i1 = GHIDRA_FIELD(cgs, 27400, 4);
        if ((int)GHIDRA_FIELD(cgs, 27400, 4) <= tmp_i5) {
          return -1;
        }
      }
      tmp_i5 = tmp_i5 + 1;
      tmp_pu6 = tmp_pu6 + 0x1a4;
    } while (tmp_i5 < tmp_i1);
  }
  return -1;
}

int CG_PlayerNFFromPos(int param_1,int *param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  uint8_t *tmp_pu4;
  int local_24;
  int local_20;
  
  tmp_i1 = CG_IsOnFireteam(g_unk_01047ac4);
  if (tmp_i1 == 0) {
    *param_2 = 0;
    return -1;
  }
  tmp_pu4 = cgs;
  local_24 = GHIDRA_FIELD(cgs, 27400, 4);
  if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
    if (*param_2 < 1) {
      return -1;
    }
  }
  else {
    local_20 = 0;
    tmp_i1 = 0;
    tmp_pu3 = tmp_pu4;
    do {
      if (((g_unk_01047ac4 != tmp_i1) && (*(int *)(tmp_pu3 + 0x940c) != 0)) &&
         (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu3 + 0x9494))) {
        tmp_i2 = CG_IsOnFireteam(tmp_i1);
        if (tmp_i2 == 0) {
          local_20 = local_20 + 1;
        }
        local_24 = GHIDRA_FIELD(cgs, 27400, 4);
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_pu3 = tmp_pu3 + 0x1a4;
    } while (tmp_i1 < local_24);
    if (*param_2 * 8 - local_20 == 0 || *param_2 * 8 < local_20) goto LAB_00078bf6;
  }
  *param_2 = 0;
  local_24 = GHIDRA_FIELD(cgs, 27400, 4);
LAB_00078bf6:
  if (0 < local_24) {
    tmp_i1 = 0;
    local_20 = 0;
    do {
      while (((g_unk_01047ac4 != tmp_i1 && (*(int *)(tmp_pu4 + 0x940c) != 0)) &&
             (*(int *)(tmp_pu4 + 0x9494) == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494)))) {
        tmp_i2 = CG_IsOnFireteam(tmp_i1);
        if (tmp_i2 == 0) {
          tmp_i2 = *param_2 * 8;
          if (((tmp_i2 - local_20 == 0 || tmp_i2 < local_20) && (local_20 < tmp_i2 + 8)) &&
             (param_1 == local_20 + *param_2 * -8)) {
            return tmp_i1;
          }
          local_20 = local_20 + 1;
        }
        tmp_i1 = tmp_i1 + 1;
        tmp_pu4 = tmp_pu4 + 0x1a4;
        local_24 = GHIDRA_FIELD(cgs, 27400, 4);
        if ((int)GHIDRA_FIELD(cgs, 27400, 4) <= tmp_i1) {
          return -1;
        }
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_pu4 = tmp_pu4 + 0x1a4;
    } while (tmp_i1 < local_24);
  }
  return -1;
}

void CG_PlayerFloatSprite(int *param_1,uint32_t param_2,int param_3,int param_4)
{
  float tmp_f1;
  uint tmp_u2;
  uint tmp_u3;
  float local_15c;
  float local_158;
  float local_154;
  int aiStack_150 [9];
  int aiStack_12c [9];
  uint local_108 [26];
  float local_a0;
  float local_9c;
  float local_98;
  uint32_t local_58;
  uint8_t local_54;
  uint8_t local_53;
  uint8_t local_52;
  uint8_t local_51;
  uint32_t local_44;
  
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)aiStack_150 + tmp_u2) = *(uint32_t *)((int)&g_unk_0011bf00 + tmp_u2);
    tmp_u2 = tmp_u2 + 4;
  } while (tmp_u2 < 0x24);
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)aiStack_12c + tmp_u2) = *(uint32_t *)((int)&g_unk_0011bf40 + tmp_u2);
    tmp_u2 = tmp_u2 + 4;
  } while (tmp_u2 < 0x24);
  tmp_u2 = 0;
  if (*param_1 == *(int *)(g_unk_01047b00 + 0xcc)) {
    tmp_u2 = -(uint)(g_unk_010906f4 == 0) & 2;
  }
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)local_108 + tmp_u3) = 0;
    *(uint32_t *)((int)local_108 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0xe8);
  tmp_f1 = (float)param_1[0x1e5];
  *(uint32_t *)((int)local_108 + tmp_u3) = 0;
  local_9c = (float)param_1[0x1e6];
  local_98 = (float)param_3 + (float)param_1[0x1e7];
  local_a0 = tmp_f1;
  AngleVectors(&g_unk_01091a54,0,&local_15c,0);
  if (8 < param_4) {
    return;
  }
  tmp_f1 = (float)aiStack_150[param_4];
  local_a0 = local_15c * tmp_f1 + local_a0;
  local_9c = local_158 * tmp_f1 + local_9c;
  local_98 = tmp_f1 * local_154 + local_98 + (float)aiStack_12c[param_4];
  if (param_1[0x2b] == *(int *)(g_unk_01047b00 + 0xcc)) {
    if ((*(byte *)(g_unk_01047b00 + 0x38) & 1) == 0) goto LAB_0009f1d2;
  }
  else if (param_1[0x47] == 0) goto LAB_0009f1d2;
  local_98 = local_98 - 18.0;
LAB_0009f1d2:
  local_108[0] = 2;
  local_52 = 0xff;
  local_44 = 0x40d51eb8;
  local_54 = 0xff;
  local_53 = 0xff;
  local_51 = 0xff;
  local_108[1] = tmp_u2;
  local_58 = param_2;
  trap_R_AddRefEntityToScene(local_108);
  return;
}

void CG_PlayerClassForClientinfo(int param_1,int param_2)
{
  if (param_2 != 0) {
    if (*(int *)(param_2 + 4) == 0x26) {
      BG_GetPlayerClassInfo(*(uint32_t *)(param_2 + 0xa4),*(uint32_t *)(param_2 + 0xa8));
      return;
    }
    if ((*(uint *)(param_2 + 0xe4) & 0x80) != 0) {
      BG_GetPlayerClassInfo
                ((*(int *)(param_1 + 0x88) == 1) + '\x01',(int)*(uint *)(param_2 + 0xe4) >> 8 & 7);
      return;
    }
  }
  BG_GetPlayerClassInfo(*(uint32_t *)(param_1 + 0x88),*(uint32_t *)(param_1 + 0xac));
  return;
}

void CG_PlayerAngles(uint8_t *param_1,uint32_t *param_2,uint32_t *param_3,uint32_t param_4)
{
  uint32_t tmp_u1;
  float tmp_f2;
  byte tmp_b3;
  uint tmp_u4;
  uint tmp_u5;
  int tmp_i6;
  int tmp_i7;
  char *tmp_pc8;
  int tmp_i9;
  long double tmp_l10;
  float *local_94;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  uint32_t local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  uint32_t uStack_14;
  
  uStack_14 = 0xa1a1b;
  tmp_i9 = *(int *)(param_1 + 0xac);
  tmp_i6 = CG_CharacterForClientinfo(tmp_i9 * 0x1a4 + 0x10f926c,param_1);
  if (tmp_i6 == 0) {
    return;
  }
  local_58 = *(float *)(param_1 + 0x7a0);
  tmp_u4 = *(uint *)(param_1 + 0xec);
  local_54 = *(float *)(param_1 + 0x7a4);
  local_50 = *(uint32_t *)(param_1 + 0x7a8);
  tmp_l10 = (long double)AngleMod(local_54);
  local_54 = (float)tmp_l10;
  if (*(int *)(param_1 + 4) == 0x26) {
    local_50 = 0;
    local_58 = 0.0;
  }
  local_68 = 0.0;
  local_6c = 0.0;
  local_70 = 0.0;
  local_5c = 0.0;
  local_60 = 0.0;
  local_64 = 0.0;
  tmp_i7 = BG_GetConditionBitFlag(*(uint32_t *)(param_1 + 0xac),5,1);
  if ((tmp_i7 == 0) &&
     (tmp_i7 = BG_GetConditionBitFlag(*(uint32_t *)(param_1 + 0xac),5,2), tmp_i7 == 0)) {
    *(uint32_t *)(param_1 + 0x2e4) = 1;
    *(uint32_t *)(param_1 + 0x2dc) = 1;
    *(uint32_t *)(param_1 + 0x288) = 1;
  }
  else {
    tmp_i7 = BG_GetConditionValue(*(uint32_t *)(param_1 + 0xac),0xb,1);
    if (tmp_i7 != 0) {
      *(uint32_t *)(param_1 + 0x2dc) = 1;
      *(uint32_t *)(param_1 + 0x2e4) = 1;
      tmp_u5 = *(uint *)(param_1 + 8);
      goto joined_r0x000a1dca;
    }
  }
  tmp_u5 = *(uint *)(param_1 + 8);
joined_r0x000a1dca:
  local_60 = local_54;
  local_6c = local_54;
  if ((tmp_u5 & 0x808001) == 0) {
    local_6c = local_54 + *(float *)(param_1 + 0x84);
    if ((tmp_u5 & 0x80) == 0) {
      local_60 = *(float *)(param_1 + 0x84) * 0.35 + local_54;
      tmp_u1 = 0x42b40000;
    }
    else {
      tmp_u1 = 0x42700000;
    }
    CG_SwingAngles(local_60,0x41c80000,tmp_u1,GHIDRA_FIELD(cg_swingSpeed, 8, 4));
    tmp_i9 = BG_GetConditionBitFlag(*(uint32_t *)(cgs + tmp_i9 * 0x1a4 + 0x9410),5,1);
    if (tmp_i9 == 0) {
      tmp_pc8 = (char *)BG_GetAnimString(*(uint32_t *)(tmp_i6 + 0x7f0),tmp_u4 & 0xfffffdff);
      tmp_pc8 = strstr(tmp_pc8,"strafe");
      if (tmp_pc8 == (char *)0x0) {
        if (*(int *)(param_1 + 0x288) == 0) {
          CG_SwingAngles(local_6c,0x42200000,0x43160000,GHIDRA_FIELD(cg_swingSpeed, 8, 4));
        }
        else {
          CG_SwingAngles(local_6c,0,0x43160000,GHIDRA_FIELD(cg_swingSpeed, 8, 4));
        }
      }
      else {
        *(uint32_t *)(param_1 + 0x288) = 0;
        local_6c = local_54;
        CG_SwingAngles(local_54,0,0x43160000,GHIDRA_FIELD(cg_swingSpeed, 8, 4));
      }
    }
    else {
      tmp_f2 = (float)GHIDRA_FIELD(cg_swingSpeed, 8, 4) * 0.5;
      *(uint32_t *)(param_1 + 0x288) = 0;
      CG_SwingAngles(local_6c,0x41a00000,0x43160000,tmp_f2);
    }
    local_60 = *(float *)(param_1 + 0x2d8);
    local_6c = *(float *)(param_1 + 0x284);
  }
  if (local_58 <= 180.0) {
    tmp_b3 = param_1[10];
    tmp_f2 = local_58;
  }
  else {
    tmp_f2 = local_58 - 360.0;
    tmp_b3 = param_1[10];
  }
  if ((tmp_b3 & 8) == 0) {
    CG_SwingAngles(tmp_f2 * 0.75,0x41700000,0x41f00000,0x3dcccccd);
    local_64 = *(float *)(param_1 + 0x2e0);
  }
  else {
    local_64 = local_70 - 3.0;
  }
  local_4c = *(float *)(param_1 + 0x24);
  local_48 = *(float *)(param_1 + 0x28);
  local_44 = *(float *)(param_1 + 0x2c);
  tmp_l10 = (long double)VectorNormalize(&local_4c);
  if (tmp_l10 != (long double)0) {
    AnglesToAxis(&local_70,&local_40);
    local_68 = local_68 -
               (local_44 * local_2c + local_48 * local_30 + local_4c * local_34) *
               (float)((long double)0.05 * tmp_l10);
    local_70 = (local_44 * local_38 + local_48 * local_3c + local_4c * local_40) *
               (float)((long double)0.05 * tmp_l10) + local_70;
  }
  local_94 = &local_70;
  if ((param_1[10] & 0x80) != 0) {
    local_50 = 0;
    local_58 = 0.0;
  }
  if (*(int *)(g_unk_01047b00 + 0xcc) == *(int *)(param_1 + 0xac)) {
    tmp_i9 = (int)ROUND((long double)*(int *)(g_unk_01047b00 + 0xe8));
  }
  else {
    tmp_i9 = (int)ROUND(*(float *)(param_1 + 0x5d4));
  }
  CG_PredictLean(param_1,&local_64,&local_58,tmp_i9);
  if (*(float *)(param_1 + 0x740) == 0.0) {
    *(uint32_t *)(param_1 + 0x470) = 0xffffffff;
    *(uint32_t *)(param_1 + 0x46c) = 0xffffffff;
    *(uint32_t *)(param_1 + 0x740) = 0x3f800000;
  }
  if ((*(uint *)(param_1 + 8) & 0x800001) == 0) {
    tmp_i9 = *(int *)(param_1 + 0x464);
    if (tmp_i9 == 0) {
      tmp_f2 = 200.0;
      tmp_i9 = 200;
    }
    else {
      tmp_f2 = (float)tmp_i9;
    }
    if (g_unk_010906e0 - *(int *)(param_1 + 0x460) < tmp_i9) {
      tmp_f2 = (1.0 - (float)(g_unk_010906e0 - *(int *)(param_1 + 0x460)) / tmp_f2) * 20.0;
      if (*(int *)(param_1 + 0x468) == 0) {
        local_5c = local_5c - tmp_f2;
      }
      else {
        local_5c = tmp_f2 + local_5c;
      }
    }
  }
  else {
    *(uint32_t *)(param_1 + 0x470) = 0xffffffff;
    *(uint32_t *)(param_1 + 0x46c) = 0xffffffff;
    *(uint32_t *)(param_1 + 0x740) = 0x3f800000;
  }
  AnglesSubtract(&local_58,&local_64,&local_58);
  AnglesSubtract(&local_64,local_94,&local_64);
  AnglesToAxis(local_94,param_2);
  AnglesToAxis(&local_64,param_3);
  AnglesToAxis(&local_58,param_4);
  if ((param_1 == cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8) &&
     ((*(byte *)(g_unk_01047b00 + 0x38) & 4) != 0)) {
    *param_3 = *param_2;
    param_3[1] = param_2[1];
    param_3[2] = param_2[2];
  }
  return;
}

void CG_PlayerFloatText(int param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  long double tmp_l7;
  long double tmp_l8;
  float local_20;
  float local_1c;
  uint32_t local_18;
  uint32_t local_14;
  float local_10;
  
  local_18 = *(uint32_t *)(param_1 + 0x794);
  local_14 = *(uint32_t *)(param_1 + 0x798);
  local_10 = (float)param_3 + *(float *)(param_1 + 0x79c);
  if (*(int *)(param_1 + 0xac) == *(int *)(g_unk_01047b00 + 0xcc)) {
    if ((*(byte *)(g_unk_01047b00 + 0x38) & 1) == 0) goto joined_r0x000a261f;
  }
  else if (*(int *)(param_1 + 0x11c) == 0) goto joined_r0x000a261f;
  local_10 = local_10 - 18.0;
joined_r0x000a261f:
  if (g_unk_010ee740 < 0x10) {
    tmp_i2 = CG_WorldCoordToScreenCoordFloat(&local_18,&local_20,&local_1c);
    if (tmp_i2 != 0) {
      tmp_l7 = (long double)VectorDistance(&local_18,g_unk_010afbcc + 0x18);
      if (tmp_l7 <= (long double)1500.0) {
        tmp_l8 = (long double)0.5 - tmp_l7 / (long double)3000.0;
        tmp_l7 = (long double)0.125;
        if ((long double)0.125 <= tmp_l8) {
          tmp_l7 = tmp_l8;
        }
      }
      else {
        tmp_l7 = (long double)0.125;
      }
      tmp_i3 = CG_Text_Width_Ext(param_2,(float)tmp_l7,0,0x1100f64);
      tmp_i4 = CG_Text_Height_Ext(param_2,(float)tmp_l7,0,0x1100f64);
      tmp_i1 = g_unk_010ee740;
      tmp_i5 = g_unk_010ee740 * 0x2c;
      (&g_unk_010ee4a8)[g_unk_010ee740 * 0xb] = 1;
      tmp_i2 = g_unk_010ee740 * 0xb;
      g_unk_010ee740 = g_unk_010ee740 + 1;
      (&g_unk_010ee480)[tmp_i2] = local_20 - (float)tmp_i3 * 0.5;
      (&g_unk_010ee484)[tmp_i1 * 0xb] = local_1c - (float)tmp_i4 * 0.5;
      (&g_unk_010ee488)[tmp_i1 * 0xb] = (float)tmp_l7;
      (&g_unk_010ee490)[tmp_i1 * 0xb] = param_2;
      *(uint32_t *)(&g_unk_010ee494 + tmp_i5) = local_18;
      *(uint32_t *)(&g_unk_010ee498 + tmp_i5) = local_14;
      *(float *)(&g_unk_010ee49c + tmp_i5) = local_10;
      return;
    }
    tmp_i2 = g_unk_010ee740 * 0x2c;
    tmp_u6 = 0;
    do {
      *(uint32_t *)((int)&g_unk_010ee480 + tmp_u6 + tmp_i2) = 0;
      *(uint32_t *)((int)&g_unk_010ee484 + tmp_u6 + tmp_i2) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < 0x28);
    *(uint32_t *)((int)&g_unk_010ee480 + tmp_u6 + tmp_i2) = 0;
  }
  return;
}

void CG_NewClientInfo(int param_1,char *param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  long tmp_l3;
  char *tmp_pc4;
  uint tmp_u5;
  uint tmp_u6;
  uint32_t tmp_u7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  uint8_t *tmp_pu11;
  uint8_t *tmp_pu12;
  int tmp_i13;
  int *tmp_pi14;
  uint local_9e4;
  char local_9c6 [2];
  char *local_9c4;
  int local_9c0 [18];
  uint8_t local_978 [64];
  long local_938;
  uint32_t local_930;
  uint32_t local_92c;
  uint32_t local_928;
  uint32_t local_924;
  long local_914;
  long local_910;
  long local_90c;
  long alStack_904 [7];
  int local_8e8 [14];
  uint8_t local_8b0 [64];
  long local_870;
  long local_86c;
  long local_868;
  long local_864;
  long local_860;
  long local_85c;
  uint32_t local_854;
  uint32_t local_850;
  uint32_t local_84c;
  uint local_840 [5];
  byte local_82c;
  long local_824;
  long local_820;
  uint32_t local_81c;
  uint32_t local_818 [255];
  char local_41c [4];
  uint32_t local_418 [257];
  uint32_t uStack_14;
  
  uStack_14 = 0xa37db;
  local_81c = 0;
  tmp_u6 = 0;
  do {
    tmp_u5 = tmp_u6;
    *(uint32_t *)((int)local_818 + tmp_u5) = 0;
    *(uint32_t *)((int)local_818 + tmp_u5 + 4) = 0;
    tmp_u6 = tmp_u5 + 8;
  } while (tmp_u5 + 8 < 0x3f8);
  *(uint32_t *)((int)local_818 + tmp_u5 + 8) = 0;
  local_41c[0] = '\0';
  local_41c[1] = '\0';
  local_41c[2] = '\0';
  local_41c[3] = '\0';
  tmp_u6 = 0;
  do {
    tmp_u5 = tmp_u6;
    *(uint32_t *)((int)local_418 + tmp_u5) = 0;
    *(uint32_t *)((int)local_418 + tmp_u5 + 4) = 0;
    tmp_u6 = tmp_u5 + 8;
  } while (tmp_u5 + 8 < 0x3f8);
  *(uint32_t *)((int)local_418 + tmp_u5 + 8) = 0;
  if (*param_2 == '\0') {
    tmp_i1 = param_1 * 0x1a4 + 0x10f926c;
    tmp_u6 = 0;
    do {
      *(uint32_t *)(tmp_i1 + tmp_u6) = 0;
      *(uint32_t *)(param_1 * 0x1a4 + 0x10f9270 + tmp_u6) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < 0x1a0);
    *(uint32_t *)(tmp_i1 + tmp_u6) = 0;
    return;
  }
  tmp_u6 = 0;
  do {
    tmp_u5 = tmp_u6;
    *(uint32_t *)((int)local_9c0 + tmp_u5) = 0;
    *(uint32_t *)((int)local_9c0 + tmp_u5 + 4) = 0;
    tmp_u6 = tmp_u5 + 8;
  } while (tmp_u5 + 8 < 0x1a0);
  local_9c0[1] = param_1;
  *(uint32_t *)((int)local_9c0 + tmp_u5 + 8) = 0;
  tmp_i1 = param_1 * 0x1a4;
  local_930 = *(uint32_t *)(cgs + tmp_i1 + 0x949c);
  local_924 = *(uint32_t *)(cgs + tmp_i1 + 0x94a8);
  local_92c = *(uint32_t *)(cgs + tmp_i1 + 0x94a0);
  local_854 = *(uint32_t *)(cgs + tmp_i1 + 0x9578);
  local_928 = *(uint32_t *)(cgs + tmp_i1 + 0x94a4);
  local_850 = *(uint32_t *)(cgs + tmp_i1 + 0x957c);
  local_84c = *(uint32_t *)(cgs + tmp_i1 + 0x9580);
  local_9c4 = param_2;
_L861:
  Info_NextPair(&local_9c4,&local_81c,local_41c);
  tmp_i1 = g_unk_01047ac4;
  if ((char)local_81c != '\0') {
    tmp_u2 = nitrox_GetTokenForString(&local_81c);
    switch(tmp_u2) {
    case 0x49:
      local_86c = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x4a:
      Q_strncpyz(local_9c0 + 2,local_41c,0x40);
      Q_strncpyz(local_978,local_41c,0x40);
      Q_CleanStr(local_978);
      break;
    case 0x58:
      tmp_l3 = strtol(local_41c,(char **)0x0,10);
      *(long *)(ClientFlags + param_1 * 4) = tmp_l3;
      break;
    case 0x59:
      local_824 = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x5a:
      local_820 = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x5b:
      local_85c = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x6c:
      if (local_41c[0] != '\0') {
        tmp_i1 = 0;
        do {
          local_9c6[0] = local_41c[tmp_i1];
          local_9c6[1] = 0;
          tmp_l3 = strtol(local_9c6,(char **)0x0,10);
          local_8e8[tmp_i1] = tmp_l3;
          tmp_i1 = tmp_i1 + 1;
        } while (tmp_i1 != 7);
      }
      break;
    case 0x6e:
      local_90c = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x70:
      if ((local_41c[0] != '\0') && (tmp_pc4 = strtok(local_41c," "), tmp_pc4 != (char *)0x0)) {
        tmp_i1 = 0;
        do {
          tmp_u6 = strtol(tmp_pc4,(char **)0x0,10);
          local_840[tmp_i1] = tmp_u6;
          tmp_i1 = tmp_i1 + 1;
          tmp_pc4 = strtok((char *)0x0," ");
          if (6 < tmp_i1) break;
        } while (tmp_pc4 != (char *)0x0);
      }
      break;
    case 0x73:
      local_938 = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x74:
      local_914 = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x83:
      if (local_41c[0] != '\0') {
        local_9c6[1] = 0;
        tmp_i1 = 0;
        do {
          local_9c6[0] = local_41c[tmp_i1];
          tmp_l3 = strtol(local_9c6,(char **)0x0,10);
          alStack_904[tmp_i1] = tmp_l3;
          tmp_i1 = tmp_i1 + 1;
        } while (tmp_i1 != 7);
      }
      break;
    case 0x84:
      Q_strncpyz(local_8b0,local_41c,0x40);
      break;
    case 0x85:
      local_870 = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x86:
      local_864 = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x87:
      local_910 = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x88:
      local_868 = strtol(local_41c,(char **)0x0,10);
      break;
    case 0x89:
      local_860 = strtol(local_41c,(char **)0x0,10);
    }
    goto _L861;
  }
  if (g_unk_01047ac4 == param_1) {
    if (local_938 != *(int *)(cgs + param_1 * 0x1a4 + 0x9494)) {
      if (GHIDRA_FIELD(cgs, 33575956, 4) != g_unk_010906e0 + 20000) {
        GHIDRA_FIELD(cgs, 33575956, 4) = 0;
      }
      if (g_unk_010906e0 + 20000 != GHIDRA_FIELD(cgs, 33575964, 4)) {
        GHIDRA_FIELD(cgs, 33575964, 4) = 0;
      }
    }
    if ((0x1e < cg) && (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94c0) < local_90c)) {
      if (*(int *)(cgs + param_1 * 0x1a4 + 0x9494) == 2) {
        tmp_u2 = *(uint32_t *)(rankSoundNames_Allies + local_90c * 4);
      }
      else {
        tmp_u2 = *(uint32_t *)(rankSoundNames_Axis + local_90c * 4);
      }
      CG_SoundPlaySoundScript(tmp_u2,0,0xffffffff,1);
      tmp_u2 = *(uint32_t *)
               (rankicons +
               ((uint)(*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 1) + local_90c * 2) * 0x20);
      if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 1) {
        tmp_u7 = *(uint32_t *)(rankNames_Axis + local_90c * 4);
      }
      else {
        tmp_u7 = *(uint32_t *)(rankNames_Allies + local_90c * 4);
      }
      tmp_u7 = va("Promoted to rank %s!",tmp_u7);
      CG_AddPMItemBig(1,tmp_u7,tmp_u2,0);
    }
    CG_LimboPanel_Setup();
    tmp_pi14 = local_8e8;
    tmp_i13 = 0;
    tmp_i9 = g_unk_01047ac4;
    do {
      tmp_i8 = *tmp_pi14;
      tmp_i10 = tmp_i9 * 0x69 + tmp_i13;
      if (*(int *)(cgs + tmp_i10 * 4 + 0x94e4) < tmp_i8) {
        tmp_u6 = *(uint *)(cgs + tmp_i10 * 4 + 0x958c);
        if (cg < 0x65) {
          local_9e4 = tmp_pi14[0x2a];
        }
        else {
          local_9e4 = tmp_pi14[0x2a];
          tmp_i9 = 0;
          do {
            if ((((int)tmp_u6 >> ((byte)tmp_i9 & 0x1f) & 1U) == 0) &&
               (((int)local_9e4 >> ((byte)tmp_i9 & 0x1f) & 1U) != 0)) {
              tmp_u2 = *(uint32_t *)(cgs + tmp_i13 * 4 + 0x11084);
              tmp_u7 = va("Reached %s skill level %i!",(&skillNames)[tmp_i13],tmp_i9);
              CG_AddPMItemBig(0,tmp_u7,tmp_u2,0);
              tmp_u2 = va("You have been rewarded with %s",
                         *(uint32_t *)(cg_skillRewards + (tmp_i13 * 5 + -1 + *tmp_pi14) * 4));
              CG_CenterPrint(tmp_u2,0x180,8);
              local_9e4 = tmp_pi14[0x2a];
            }
            tmp_i9 = tmp_i9 + 1;
          } while (tmp_i9 != 6);
          tmp_i8 = *tmp_pi14;
          tmp_i9 = g_unk_01047ac4;
        }
        tmp_i10 = tmp_i9 * 0x69 + tmp_i13;
        *(int *)(cgs + tmp_i10 * 4 + 0x94e4) = tmp_i8;
        *(uint *)(cgs + tmp_i10 * 4 + 0x958c) = local_9e4;
        if (tmp_i13 == 4) {
          if ((((tmp_u6 & 0x10) == 0) && ((local_9e4 & 0x10) != 0)) && (GHIDRA_FIELD(cgs, 33685924, 4) == 0)) {
            tmp_u2 = 1;
LAB_000a429d:
            CG_LimboPanel_SetSelectedWeaponNumForSlot(1,tmp_u2);
            CG_LimboPanel_SendSetupMsg(0);
            tmp_i9 = g_unk_01047ac4;
          }
        }
        else {
          if (tmp_i13 != 5) goto LAB_000a3fd4;
          if (((local_914 == 0) && ((tmp_u6 & 0x10) == 0)) && ((local_82c & 0x10) != 0)) {
            tmp_u2 = 2;
            goto LAB_000a429d;
          }
        }
      }
      else {
LAB_000a3fd4:
        if (tmp_i13 == 6) goto LAB_000a4102;
      }
      tmp_i13 = tmp_i13 + 1;
      tmp_pi14 = tmp_pi14 + 1;
    } while( true );
  }
LAB_000a3d2c:
  tmp_pu11 = cg_entities;
  do {
    while ((param_1 != *(int *)(tmp_pu11 + 0xac) || (*(int *)(tmp_pu11 + 4) != 1))) {
      tmp_pu11 = tmp_pu11 + 0xaf8;
      if (tmp_pu11 == int_cl_timenudge) goto LAB_000a3d70;
    }
    tmp_pu12 = tmp_pu11 + 0xaf8;
    CG_ResetPlayerEntity(tmp_pu11);
    tmp_pu11 = tmp_pu12;
  } while (tmp_pu12 != int_cl_timenudge);
LAB_000a3d70:
  tmp_i1 = param_1 * 0x1a4;
  local_9c0[0] = 1;
  tmp_u6 = 0;
  do {
    tmp_u5 = tmp_u6;
    tmp_u2 = *(uint32_t *)((int)local_9c0 + tmp_u5 + 4);
    *(uint32_t *)(tmp_i1 + 0x10f926c + tmp_u5) = *(uint32_t *)((int)local_9c0 + tmp_u5);
    *(uint32_t *)(tmp_i1 + 0x10f9270 + tmp_u5) = tmp_u2;
    tmp_u6 = tmp_u5 + 8;
  } while (tmp_u6 < 0x1a0);
  param_1 = param_1 * 0x1a4;
  *(uint32_t *)(tmp_i1 + 0x10f926c + tmp_u6) = *(uint32_t *)((int)local_9c0 + tmp_u5 + 8);
  if (*(int *)(cgs + param_1 + 0x9574) == 0) {
    tmp_u2 = BG_GetCharacter(*(uint32_t *)(cgs + param_1 + 0x9494),
                            *(uint32_t *)(cgs + param_1 + 0x94b8));
    *(uint32_t *)(cgs + param_1 + 0x9574) = tmp_u2;
  }
  CG_SortClientFireteam();
  return;
LAB_000a4102:
  if (local_938 != *(int *)(cgs + tmp_i9 * 0x1a4 + 0x9494)) {
    tmp_u6 = 0;
    do {
      *(uint32_t *)((int)&g_unk_010b4578 + tmp_u6) = 0;
      *(uint32_t *)((int)&g_unk_010b457c + tmp_u6) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < 0x300);
    tmp_u6 = 0;
    do {
      *(uint32_t *)((int)&g_unk_010b4878 + tmp_u6) = 0;
      *(uint32_t *)((int)&g_unk_010b487c + tmp_u6) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < 0x100);
  }
  tmp_u2 = va("%i",local_85c);
  trap_Cvar_Set("authLevel",tmp_u2);
  if (local_85c != *(int *)(cgs + tmp_i1 * 0x1a4 + 0x9570)) {
    if (local_85c < 1) {
      tmp_u2 = Info_ValueForKey(CachedServerInfo,"voteFlags");
      trap_Cvar_Set("cg_ui_voteFlags",tmp_u2);
      CG_Printf("[cgnotify]^3*** You have been stripped of your referee status! ***\n");
    }
    else {
      trap_Cvar_Set("cg_ui_voteFlags",&g_unk_0011e957);
      if (local_85c == 2) {
        tmp_pc4 = "rcon";
      }
      else {
        tmp_pc4 = "referee";
      }
      CG_Printf("[cgnotify]^2*** You have been authorized \"%s\" status ***\n",tmp_pc4);
      CG_Printf("Type: ^3ref^7 (by itself) for a list of referee commands.\n");
    }
  }
  goto LAB_000a3d2c;
}

void CG_Player(uint *param_1)
{
  uint *tmp_pu1;
  float tmp_f2;
  uint8_t tmp_u3;
  uint8_t tmp_u4;
  uint8_t tmp_u5;
  uint8_t tmp_u6;
  uint8_t tmp_u7;
  uint8_t tmp_u8;
  uint8_t tmp_u9;
  uint8_t tmp_u10;
  uint8_t tmp_u11;
  uint8_t tmp_u12;
  uint8_t tmp_u13;
  uint8_t tmp_u14;
  char tmp_c15;
  int tmp_i16;
  int tmp_i17;
  int *tmp_pi18;
  uint tmp_u19;
  int tmp_i20;
  long tmp_l21;
  uint32_t tmp_u22;
  char *tmp_pc23;
  uint tmp_u24;
  uint tmp_u25;
  int tmp_i26;
  uint tmp_u27;
  float *pfVar28;
  float *pfVar29;
  char tmp_c30;
  int tmp_i31;
  int tmp_i32;
  uint tmp_u33;
  float tmp_f34;
  char **ppcVar35;
  int tmp_i36;
  float *pfVar37;
  uint8_t tmp_u38;
  bool tmp_b39;
  long double tmp_l40;
  float local_434;
  uint32_t local_430;
  float *local_42c;
  char *local_428;
  int local_424;
  char **local_420;
  uint *local_414;
  byte local_40c;
  uint *local_408;
  uint local_404;
  uint local_3e8;
  float local_3dc;
  float local_3d8;
  float local_3d4;
  uint local_3d0;
  uint local_3cc;
  float local_3c8;
  uint local_3c4;
  uint local_3c0;
  float local_3bc;
  float local_3b8;
  float local_3b4;
  float local_3b0;
  float local_3ac;
  float local_3a8;
  float local_3a4;
  uint32_t local_3a0;
  float local_39c;
  float local_398;
  float local_394;
  float local_378;
  float local_374;
  float local_370;
  float local_36c;
  float local_368;
  float local_364;
  char *local_340;
  float local_33c [2];
  char *local_334;
  uint32_t local_330;
  char *local_32c;
  char *local_328;
  float local_324;
  float local_320;
  uint32_t local_31c;
  char *local_318;
  uint32_t local_314;
  float local_310;
  float local_30c;
  float local_308;
  uint32_t local_304;
  uint32_t local_300;
  uint8_t local_2fc;
  uint8_t local_2fb;
  uint8_t local_2fa;
  uint8_t local_2f9;
  float local_2f8;
  float local_2f4;
  float local_2f0;
  uint32_t local_2ec;
  uint32_t local_2e8;
  uint8_t local_2e4;
  uint8_t local_2e3;
  uint8_t local_2e2;
  uint8_t local_2e1;
  float local_2e0 [2];
  int local_2d8;
  float local_2d4;
  float local_2d0;
  float local_2cc;
  float local_2c8;
  float local_2c4;
  float local_2c0;
  float local_2bc;
  float local_2b8;
  float local_2b4;
  float local_2b0;
  float local_2ac;
  float local_2a8;
  float local_2a4;
  uint8_t local_2a0 [40];
  float local_278;
  float local_274;
  float local_270;
  uint local_26c;
  uint local_268;
  uint local_264;
  uint local_260;
  uint local_250;
  uint local_24c;
  uint local_248;
  uint local_244;
  uint local_240;
  uint local_23c;
  uint32_t local_234;
  uint32_t local_230;
  float local_200;
  uint local_1f4 [3];
  float local_1e8;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  uint8_t local_1d8 [76];
  uint8_t local_18c [12];
  uint local_180;
  uint local_164;
  uint local_154;
  uint32_t local_148;
  uint32_t local_144;
  float local_114;
  uint local_108 [3];
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  uint8_t local_ec [144];
  int local_5c;
  uint32_t local_58;
  float local_28;
  
  local_3dc = 0.0;
  local_3d8 = 0.0;
  local_3d4 = 0.0;
  tmp_u24 = param_1[0x2b];
  if (0x3f < tmp_u24) {
    CG_Error("Bad clientNum on player entity");
  }
  tmp_i31 = tmp_u24 * 0x1a4;
  if (*(int *)(cgs + tmp_i31 + 0x940c) == 0) {
    return;
  }
  tmp_i16 = CG_CharacterForClientinfo(tmp_i31 + 0x10f926c,param_1);
  tmp_i17 = BG_GetCharacter(*(uint32_t *)(cgs + tmp_i31 + 0x9494),
                           *(uint32_t *)(cgs + tmp_i31 + 0x94b8));
  tmp_i36 = *(int *)(cgs + tmp_i31 + 0x9494);
  if ((param_1[2] & 0x8000) == 0) {
    if ((param_1[2] & 0x20) == 0) {
      local_3dc = (float)param_1[0x1e5];
      local_3d8 = (float)param_1[0x1e6];
      local_3d4 = (float)param_1[0x1e7];
    }
    else {
      tmp_i20 = *(int *)(g_unk_01047b00 + 0x5d8);
      if (tmp_i20 < 1) {
        tmp_i32 = 0;
LAB_000a52a0:
        if (tmp_i32 != tmp_i20) goto LAB_000a5320;
      }
      else {
        tmp_pi18 = (int *)(g_unk_01047b00 + 0x5dc);
        tmp_i32 = 0;
        do {
          tmp_i26 = *tmp_pi18 * 0xaf8;
          if ((*(int *)(cg_entities + tmp_i26 + 4) == 0x29) &&
             (*(uint *)(cg_entities + tmp_i26 + 0x8c) == *param_1)) {
            AngleVectors(param_1 + 0x1e8,local_2e0,local_1f4,local_108);
            local_3dc = local_2e0[0] * -36.0 + *(float *)(cg_entities + tmp_i26 + 0x18);
            local_3d8 = local_2e0[1] * -36.0 + *(float *)(cg_entities + tmp_i26 + 0x1c);
            tmp_i20 = *(int *)(g_unk_01047b00 + 0x5d8);
            local_3d4 = (float)param_1[0x1e7];
            goto LAB_000a52a0;
          }
          tmp_i32 = tmp_i32 + 1;
          tmp_pi18 = tmp_pi18 + 0x48;
        } while (tmp_i32 != tmp_i20);
      }
      local_3dc = (float)param_1[0x1e5];
      local_3d8 = (float)param_1[0x1e6];
      local_3d4 = (float)param_1[0x1e7];
    }
  }
  else {
    tmp_i20 = *(int *)(cg_entities + param_1[0x2b] * 0xaf8 + 0xab4) * 0xaf8;
    local_3dc = *(float *)(cg_entities + tmp_i20 + 0xa50);
    local_3d8 = *(float *)(cg_entities + tmp_i20 + 0xa54);
    local_3d4 = *(float *)(cg_entities + tmp_i20 + 0xa58);
  }
LAB_000a5320:
  local_408 = local_1f4;
  local_414 = local_108;
  local_42c = local_2e0;
  tmp_u19 = 0;
  do {
    *(uint32_t *)((int)local_42c + tmp_u19) = 0;
    *(uint32_t *)((int)local_2e0 + tmp_u19 + 4) = 0;
    tmp_u19 = tmp_u19 + 8;
  } while (tmp_u19 < 0xe8);
  *(uint32_t *)((int)local_42c + tmp_u19) = 0;
  tmp_u19 = 0;
  do {
    *(uint32_t *)((int)local_408 + tmp_u19) = 0;
    *(uint32_t *)((int)local_1f4 + tmp_u19 + 4) = 0;
    tmp_u19 = tmp_u19 + 8;
  } while (tmp_u19 < 0xe8);
  *(uint32_t *)((int)local_408 + tmp_u19) = 0;
  tmp_u19 = 0;
  do {
    *(uint32_t *)((int)local_414 + tmp_u19) = 0;
    *(uint32_t *)((int)local_108 + tmp_u19 + 4) = 0;
    tmp_u19 = tmp_u19 + 8;
  } while (tmp_u19 < 0xe8);
  *(uint32_t *)((int)local_414 + tmp_u19) = 0;
  CG_PlayerAngles(local_2a0,local_1d8);
  AxisCopy(local_2a0,local_ec);
  CG_AnimPlayerConditions(tmp_i16,param_1);
  tmp_u19 = param_1[0x2b];
  tmp_i20 = tmp_u19 * 0x1a4 + 0x10f926c;
  tmp_i32 = CG_CharacterForClientinfo(tmp_i20,param_1);
  if (tmp_i32 == 0) {
LAB_000a61ee:
    tmp_u19 = param_1[1];
  }
  else {
    if (GHIDRA_FIELD(cg_noPlayerAnims, 12, 4) != 0) {
      local_248 = 0;
      local_264 = 0;
      local_250 = 0;
      local_26c = 0;
      local_268 = **(uint **)(*(int *)(tmp_i32 + 0x7f0) + 0x9c);
      local_260 = local_268;
      local_24c = local_268;
      local_244 = local_268;
      goto LAB_000a61ee;
    }
    tmp_u33 = param_1[0x3b];
    if ((*(byte *)((int)param_1 + 10) & 0x80) == 0) {
      tmp_u25 = param_1[0x1de];
    }
    else {
      tmp_u25 = g_unk_010906e0 + 0x6d6;
      param_1[0x1de] = tmp_u25;
    }
    if (((((int)tmp_u25 < (int)g_unk_010906e0) && ((param_1[2] & 0x808001) == 0)) &&
        (param_1[0xa2] != 0)) &&
       (tmp_u19 = BG_GetAnimScriptAnimation
                           (tmp_u19,*(uint32_t *)(tmp_i32 + 0x7f0),param_1[0x46],
                            (param_1[0xa2] != 1) + '\r'), -1 < (int)tmp_u19)) {
      tmp_u33 = tmp_u19;
    }
    tmp_u19 = param_1[1];
    if (tmp_u19 == 0x26) {
      CG_RunLerpFrameRateCorpse(tmp_i20,param_1 + 0x9a,tmp_u33,param_1,0);
      local_250 = param_1[0x9a];
      local_26c = param_1[0x9d];
      tmp_u19 = param_1[1];
      local_240 = param_1[0xa0];
LAB_000a68ef:
      local_268 = param_1[0x9f];
      local_24c = param_1[0x9c];
      if (tmp_u19 != 0x26) goto LAB_000a550e;
      CG_RunLerpFrameRateCorpse(tmp_i20,param_1 + 0xaf,param_1[0x3c],param_1,0);
      local_248 = param_1[0xaf];
      local_264 = param_1[0xb2];
      tmp_u19 = param_1[1];
      local_23c = param_1[0xb5];
    }
    else {
      if (GHIDRA_FIELD(cg_animSpeed, 12, 4) != 0) {
        CG_RunLerpFrameRate_part_2(tmp_u33,param_1,0);
        local_250 = param_1[0x9a];
        local_26c = param_1[0x9d];
        tmp_u19 = param_1[1];
        local_240 = param_1[0xa0];
        goto LAB_000a68ef;
      }
      param_1[0x9d] = 0;
      local_250 = 0;
      local_268 = param_1[0x9f];
      param_1[0x9a] = 0;
      param_1[0xa0] = 0;
      local_26c = 0;
      local_24c = param_1[0x9c];
      local_240 = 0;
LAB_000a550e:
      if (GHIDRA_FIELD(cg_animSpeed, 12, 4) == 0) {
        param_1[0xaf] = 0;
        local_23c = 0;
        local_264 = 0;
        param_1[0xb5] = 0;
        param_1[0xb2] = 0;
        local_248 = 0;
      }
      else {
        CG_RunLerpFrameRate_part_2(param_1[0x3c],param_1,0);
        local_248 = param_1[0xaf];
        local_264 = param_1[0xb2];
        tmp_u19 = param_1[1];
        local_23c = param_1[0xb5];
      }
    }
    local_260 = param_1[0xb4];
    local_244 = param_1[0xb1];
  }
  tmp_u33 = param_1[2];
  if (tmp_u19 != 0x26) {
    tmp_u19 = param_1[0x2b];
    tmp_u38 = (param_1[0x39] & 0x60) != 0;
    if ((bool)tmp_u38) {
      CG_PlayerFloatSprite(0x38,0);
      tmp_u11 = 6;
      tmp_u6 = 5;
      tmp_u5 = 4;
      tmp_u4 = 3;
      tmp_u3 = 2;
      tmp_u7 = 8;
      tmp_u9 = 7;
    }
    else {
      tmp_u11 = 5;
      tmp_u6 = 4;
      tmp_u5 = 3;
      tmp_u4 = 2;
      tmp_u3 = 1;
      tmp_u7 = 7;
      tmp_u9 = 6;
    }
    tmp_c30 = (-((param_1[2] & 0x800001) == 0) & 0x28U) + 0x10;
    tmp_c15 = (-((param_1[2] & 0x800001) == 0) & 0x28U) + 8;
    tmp_i20 = *(int *)(g_unk_01047b00 + 0x158);
    if (tmp_i20 == 3) {
      if ((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95a8) == 0) && (GHIDRA_FIELD(cgs, 33787772, 4) == 0)) {
        if (*(int *)(g_unk_01047b00 + 0xfc) < 1) {
          local_3e8 = param_1[0x2b];
          if ((*(int *)(cgs + local_3e8 * 0x1a4 + 0x9494) == 3) &&
             (*(int *)(cgs + local_3e8 * 0x1a4 + 0x94b8) == 1)) {
LAB_000a6aaa:
            if (0 < *(int *)(cgs + local_3e8 * 0x1a4 + 0x94a8)) {
              CG_WoundedPlayerFloatName(param_1,local_3e8 * 0x1a4 + 0x10f9274,1);
              tmp_i20 = *(int *)(g_unk_01047b00 + 0x158);
            }
            goto LAB_000a6af0;
          }
          goto LAB_000a6830;
        }
      }
      else {
        CG_PlayerFloatText(param_1,tmp_u19 * 0x1a4 + 0x10f9274,tmp_c15);
        tmp_i20 = *(int *)(g_unk_01047b00 + 0x158);
        if (*(int *)(g_unk_01047b00 + 0xfc) < 1) {
          local_3e8 = param_1[0x2b];
          if ((tmp_i20 == *(int *)(cgs + local_3e8 * 0x1a4 + 0x9494)) &&
             (*(int *)(cgs + local_3e8 * 0x1a4 + 0x94b8) == 1)) goto LAB_000a6aaa;
        }
LAB_000a6af0:
        if (tmp_i20 == 3) {
LAB_000a6830:
          if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95a8) != 0) {
            if (((((param_1[2] & 1) != 0) && (*param_1 == param_1[0x2b])) &&
                (0 < *(int *)(g_unk_01047b00 + 0xfc))) &&
               ((*(int *)(g_unk_01047b00 + 0x110) == 1 ||
                (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3)))) {
              CG_PlayerFloatSprite(tmp_c15,tmp_u38);
            }
            goto LAB_000a56e5;
          }
          tmp_i20 = 3;
        }
      }
    }
    else if (*(int *)(g_unk_01047b00 + 0xfc) < 1) {
      local_3e8 = param_1[0x2b];
      if ((tmp_i20 == *(int *)(cgs + local_3e8 * 0x1a4 + 0x9494)) &&
         (*(int *)(cgs + local_3e8 * 0x1a4 + 0x94b8) == 1)) goto LAB_000a6aaa;
    }
    tmp_u8 = tmp_u9;
    tmp_u10 = tmp_u11;
    tmp_u12 = tmp_u6;
    tmp_u13 = tmp_u5;
    tmp_u14 = tmp_u4;
    if ((param_1[0x39] & 2) != 0) {
      CG_PlayerFloatSprite(tmp_c30,tmp_u38);
      tmp_i20 = *(int *)(g_unk_01047b00 + 0x158);
      tmp_u38 = tmp_u3;
      tmp_u8 = tmp_u7;
      tmp_u10 = tmp_u9;
      tmp_u12 = tmp_u11;
      tmp_u13 = tmp_u6;
      tmp_u14 = tmp_u5;
      tmp_u3 = tmp_u4;
    }
    tmp_i32 = *(int *)(cgs + tmp_u19 * 0x1a4 + 0x9494);
    tmp_b39 = tmp_i32 == tmp_i20;
    tmp_u19 = param_1[2];
    tmp_u7 = tmp_u10;
    tmp_u9 = tmp_u13;
    tmp_u11 = tmp_u14;
    if ((((tmp_u19 & 1) != 0) && (*param_1 == param_1[0x2b])) &&
       ((tmp_b39 &&
        (((0 < *(int *)(g_unk_01047b00 + 0xfc) && (*(int *)(g_unk_01047b00 + 0x110) == 1)) &&
         (GHIDRA_FIELD(cgs, 27388, 4) != 8)))))) {
      CG_PlayerFloatSprite(tmp_c15,tmp_u38);
      CG_WoundedPlayerFloatName(param_1,param_1[0x2b] * 0x1a4 + 0x10f9274,0);
      tmp_u19 = param_1[2];
      tmp_u38 = tmp_u3;
      tmp_u7 = tmp_u8;
      tmp_u9 = tmp_u12;
      tmp_u11 = tmp_u13;
      tmp_u3 = tmp_u14;
      tmp_u12 = tmp_u10;
    }
    tmp_u6 = tmp_u12;
    tmp_u5 = tmp_u9;
    tmp_u4 = tmp_u11;
    if (((tmp_u19 & 0x400) != 0) && (tmp_b39)) {
      CG_PlayerFloatSprite(tmp_c15,tmp_u38);
      tmp_u19 = param_1[2];
      tmp_u38 = tmp_u3;
      tmp_u6 = tmp_u7;
      tmp_u5 = tmp_u12;
      tmp_u4 = tmp_u9;
      tmp_u3 = tmp_u11;
    }
    if ((tmp_u19 & 0x200000) != 0) {
      CG_PlayerFloatSprite(tmp_c30,tmp_u38);
      tmp_u38 = tmp_u3;
      tmp_u3 = tmp_u4;
      tmp_u4 = tmp_u5;
      tmp_u5 = tmp_u6;
    }
    if (tmp_b39) {
      if ((int)g_unk_010906e0 < (int)param_1[0x264]) {
        CG_PlayerFloatSprite(tmp_c30,tmp_u38);
        tmp_u38 = tmp_u3;
        tmp_u3 = tmp_u4;
        tmp_u4 = tmp_u5;
      }
      if ((*(byte *)((int)param_1 + 9) & 2) != 0) {
        CG_PlayerFloatSprite(tmp_c15,tmp_u38);
        tmp_u38 = tmp_u3;
        tmp_u3 = tmp_u4;
      }
    }
    if (((param_1[0x39] & 0x80) != 0) && (tmp_i32 == *(int *)(g_unk_01047b00 + 0x158))) {
      CG_PlayerFloatSprite(tmp_c30,tmp_u38);
      tmp_u38 = tmp_u3;
    }
    tmp_i20 = CG_IsOnFireteam(*param_1);
    if ((((tmp_i20 != 0) && (tmp_i32 = CG_IsOnFireteam(g_unk_01047ac4), tmp_i20 == tmp_i32)) &&
        (*(int *)(cgs + *param_1 * 0x1a4 + 0x957c) != 0)) && (GHIDRA_FIELD(cgs, 27388, 4) != 8)) {
      CG_PlayerFloatSprite(0x38,tmp_u38);
    }
  }
LAB_000a56e5:
  local_3ac = 0.0;
  tmp_u19 = 0;
  local_3a8 = 0.0;
  local_3a4 = -1.0;
  local_3a0 = 0x42800000;
  do {
    *(uint32_t *)((int)&local_340 + tmp_u19) = 0;
    *(uint32_t *)((int)local_33c + tmp_u19) = 0;
    tmp_u19 = tmp_u19 + 8;
  } while (tmp_u19 < 0x50);
  local_32c = "tag_footright";
  local_318 = "tag_torso";
  local_428 = "tag_footleft";
  local_33c[0] = 10.0;
  local_328 = (char *)0x41200000;
  local_330 = GHIDRA_FIELD(cgs, 68736, 4);
  local_314 = 0x41900000;
  local_308 = (float)GHIDRA_FIELD(cgs, 68740, 4);
  local_31c = local_330;
  if (GHIDRA_FIELD(cg_shadows, 12, 4) == 0) {
    local_434 = 0.0;
LAB_000a57b9:
    local_40c = 0;
    tmp_i20 = 0;
  }
  else {
    local_3d0 = param_1[0x1e5];
    local_3cc = param_1[0x1e6];
    local_3c8 = (float)param_1[0x1e7] - 64.0;
    local_340 = local_428;
    trap_CM_BoxTrace(&local_378,param_1 + 0x1e5,&local_3d0,0,0,0,0x2010001);
    local_434 = local_364 + 1.0;
    if (GHIDRA_FIELD(cg_shadows, 12, 4) == 0) goto LAB_000a57b9;
    if (GHIDRA_FIELD(cg_shadows, 12, 4) == 1) {
      if ((param_1[2] & 1) != 0) {
        local_40c = 0;
        goto LAB_000a629b;
      }
      tmp_l40 = (long double)VectorDistance(param_1 + 0x1e5,g_unk_010afbcc + 0x18);
      local_40c = (long double)250.0 < tmp_l40 & ((byte)(param_1[2] >> 0x12) ^ 1);
      if (local_40c == 0) {
        if ((long double)512.0 <= tmp_l40) {
          local_40c = 1;
        }
        else {
          ppcVar35 = &local_340;
          do {
            tmp_i20 = 0;
            while (tmp_i20 = CG_GetOriginForTag(param_1,param_1 + 0x11e,local_428,tmp_i20,&local_3c4,
                                               &local_39c), -1 < tmp_i20) {
              tmp_f34 = local_434;
              if (local_434 <= local_3bc) {
                tmp_f34 = local_3bc;
              }
              local_3bc = tmp_f34 + 5.0;
              AxisToAngles(&local_39c,&local_3b8);
              CG_ImpactMark(ppcVar35[4],&local_3c4,&local_3ac,ppcVar35[1],local_3b4,0x3f800000,
                            0x3f800000,0x3f800000,0x3f800000,0xffffffff);
              tmp_i20 = tmp_i20 + 1;
            }
            ppcVar35 = ppcVar35 + 5;
            local_428 = *ppcVar35;
          } while (local_428 != (char *)0x0);
          local_40c = 1;
        }
      }
      else {
        if (tmp_l40 <= (long double)512.0) {
LAB_000a74c5:
          tmp_l40 = (long double)1;
        }
        else {
          if ((long double)1024.0 < tmp_l40) {
            local_40c = 0;
            goto LAB_000a7567;
          }
          tmp_l40 = (long double)
                   (float)((long double)1 - (tmp_l40 - (long double)512.0) * (long double)0.001953125);
          if ((long double)1 < tmp_l40) goto LAB_000a74c5;
          if (tmp_l40 < (long double)0) {
            tmp_l40 = (long double)0;
          }
        }
        local_3c4 = param_1[0x1e5];
        local_3c0 = param_1[0x1e6];
        local_3bc = local_434;
        if (local_434 <= (float)param_1[0x1e7]) {
          local_3bc = (float)param_1[0x1e7];
        }
        local_3bc = local_3bc + 18.0;
        CG_ImpactMark(GHIDRA_FIELD(cgs, 68740, 4),&local_3c4,&local_3ac,0x41900000,param_1[0x1e9],(float)tmp_l40,
                      (float)tmp_l40,(float)tmp_l40,(float)tmp_l40,0xffffffff);
      }
LAB_000a7567:
      if (GHIDRA_FIELD(cg_shadows, 12, 4) != 0) goto LAB_000a629b;
      tmp_i20 = 0;
    }
    else {
      local_40c = 1;
LAB_000a629b:
      local_420 = &local_340;
      local_39c = (float)param_1[0x1e5];
      local_398 = (float)param_1[0x1e6];
      local_394 = (float)param_1[0x1e7] - 24.0;
      tmp_u19 = CG_PointContents(&local_39c,0);
      tmp_i20 = GHIDRA_FIELD(cg_shadows, 12, 4);
      if ((tmp_u19 & 0x38) != 0) {
        local_3ac = (float)param_1[0x1e5];
        local_3a8 = (float)param_1[0x1e6];
        local_3a4 = (float)param_1[0x1e7] + 32.0;
        tmp_u19 = CG_PointContents(&local_3ac,0);
        tmp_i20 = GHIDRA_FIELD(cg_shadows, 12, 4);
        if (((tmp_u19 & 0x39) == 0) &&
           (trap_CM_BoxTrace(&local_378,&local_3ac,&local_39c,0,0,0,0x38),
           tmp_i20 = GHIDRA_FIELD(cg_shadows, 12, 4), local_370 != 1.0)) {
          local_33c[1] = local_364;
          local_340 = (char *)(local_36c - 32.0);
          local_32c = (char *)0xffffffff;
          local_33c[0] = local_368 - 32.0;
          local_2fc = 0xff;
          local_2fb = 0xff;
          local_2fa = 0xff;
          local_2f9 = 0xff;
          local_320 = local_364;
          local_324 = local_368 + 32.0;
          local_314 = 0xffffffff;
          local_334 = (char *)0x0;
          local_330 = 0;
          local_308 = local_364;
          local_310 = local_36c + 32.0;
          local_31c = 0;
          local_318 = (char *)0x3f800000;
          local_304 = 0x3f800000;
          local_300 = 0x3f800000;
          local_2f0 = local_364;
          local_2e4 = 0xff;
          local_2e3 = 0xff;
          local_2ec = 0x3f800000;
          local_2e8 = 0;
          local_2e2 = 0xff;
          local_2e1 = 0xff;
          local_328 = local_340;
          local_30c = local_324;
          local_2f8 = local_310;
          local_2f4 = local_33c[0];
          trap_R_AddPolyToScene(GHIDRA_FIELD(cgs, 68744, 4),4,local_420);
          tmp_i20 = GHIDRA_FIELD(cg_shadows, 12, 4);
        }
      }
    }
  }
  local_420 = &local_340;
  tmp_u19 = 0;
  if (*param_1 == *(uint *)(g_unk_01047b00 + 0xcc)) {
    tmp_u19 = -(uint)(g_unk_010906f4 == 0) & 2;
  }
  if (g_unk_010aaecc == 0) {
    if (g_unk_010ee058 != 0) {
      tmp_u19 = 0;
    }
  }
  else {
    tmp_u19 = 0;
  }
  if ((tmp_i20 == 3) && (local_40c != 0)) {
    tmp_u19 = tmp_u19 | 0x40;
  }
  if (((g_unk_01047aec != 0) && (GHIDRA_FIELD(demo_wallHack, 12, 4) != 0)) &&
     (tmp_u19 = tmp_u19 | 8, local_230 = GHIDRA_FIELD(cgs, 131916, 4), local_144 = GHIDRA_FIELD(cgs, 131916, 4),
     local_58 = GHIDRA_FIELD(cgs, 131916, 4), *(int *)(cgs + tmp_u24 * 0x1a4 + 0x9494) != 1)) {
    local_230 = GHIDRA_FIELD(cgs, 131924, 4);
    local_144 = GHIDRA_FIELD(cgs, 131924, 4);
    local_58 = GHIDRA_FIELD(cgs, 131924, 4);
  }
  local_404 = tmp_u19 | 0x20;
  tmp_f34 = local_3d4 + 31.0;
  local_340 = (char *)(local_3dc - *(float *)(g_unk_010afbcc + 0x18));
  local_33c[0] = local_3d8 - *(float *)(g_unk_010afbcc + 0x1c);
  local_33c[1] = tmp_f34 - *(float *)(g_unk_010afbcc + 0x20);
  local_2e0[1] = (float)local_404;
  local_1f4[1] = local_404;
  local_108[1] = local_404;
  tmp_l40 = (long double)VectorLengthSquared(local_420);
  if (tmp_l40 <= (long double)147456.0) {
    tmp_l40 = (long double)0;
  }
  else {
    tmp_l40 = tmp_l40 - (long double)147456.0;
    local_404 = tmp_u19 | 0x21;
    if ((long double)589824.0 < tmp_l40) {
      tmp_l40 = (long double)1;
    }
    else {
      tmp_l40 = tmp_l40 / (long double)589824.0;
    }
  }
  local_200 = (float)tmp_l40;
  local_114 = (float)tmp_l40;
  local_28 = (float)tmp_l40;
  local_2d4 = local_3dc;
  local_2d0 = local_3d8;
  local_1e8 = local_3dc;
  local_1e4 = local_3d8;
  local_fc = local_3dc;
  local_f8 = local_3d8;
  local_2c8 = local_434;
  local_1dc = local_434;
  local_f0 = local_434;
  if ((param_1[1] == 0x26) && (param_1[0x16] == 1)) {
    tmp_u19 = param_1[2];
LAB_000a6170:
    local_2d8 = *(int *)(tmp_i16 + 0x7e8);
    local_234 = *(uint32_t *)(tmp_i16 + 0x7ec);
  }
  else {
    tmp_u19 = param_1[2];
    if ((tmp_u19 & 0x10000) != 0) goto LAB_000a6170;
    local_2d8 = *(int *)(tmp_i16 + 0x40);
    local_234 = *(uint32_t *)(tmp_i16 + 0x44);
  }
  local_2cc = tmp_f34;
  local_1e0 = tmp_f34;
  local_f4 = tmp_f34;
  if ((tmp_u19 & 0x40) != 0) {
    if ((param_1[0x39] & 0x80) == 0) {
      if (tmp_i36 == 1) {
        local_430 = 0;
        local_434 = 1.0;
      }
      else {
        local_430 = 0x3f800000;
        local_434 = 0.0;
      }
    }
    else if (*(int *)(cgs + tmp_u24 * 0x1a4 + 0x9494) == 1) {
      local_430 = 0x3f800000;
      local_434 = 0.0;
    }
    else {
      local_430 = 0;
      local_434 = 1.0;
    }
    trap_Cvar_VariableStringBuffer("r_dynamicLight",local_420,8);
    tmp_l21 = strtol((char *)local_420,(char **)0x0,10);
    tmp_i36 = 0;
    do {
      tmp_i36 = tmp_i36 + 1;
      trap_R_AddLightToScene(&local_2d4,0x42c80000,0x3f800000,local_434,0,local_430,0,0);
    } while (tmp_i36 != (uint)(tmp_l21 == 2) * 3 + 1);
  }
  local_278 = local_3dc;
  local_274 = local_3d8;
  local_270 = local_3d4;
  if (local_2d8 == 0) {
    return;
  }
  if ((GHIDRA_FIELD(cg_drawHitbox, 12, 4) & 4) != 0) {
    tmp_u19 = param_1[0x2d];
    tmp_u25 = *param_1;
    local_374 = (float)(int)-(tmp_u19 & 0xff);
    local_33c[0] = (float)(tmp_u19 & 0xff);
    local_378 = (float)param_1[0x1e5] + local_374;
    local_374 = local_374 + (float)param_1[0x1e6];
    local_370 = (float)(int)-(tmp_u19 >> 8 & 0xff) + (float)param_1[0x1e7];
    local_340 = (char *)((float)param_1[0x1e5] + local_33c[0]);
    local_33c[0] = local_33c[0] + (float)param_1[0x1e6];
    local_33c[1] = (float)(int)(((int)tmp_u19 >> 0x10 & 0xffU) - 0x20) + (float)param_1[0x1e7];
    tmp_u22 = tv(0x3e800000,0x3f000000,0x3f800000);
    CG_RailTrail(tmp_u22,&local_378,local_420,1,tmp_u25 | 0x1000);
  }
  if ((GHIDRA_FIELD(cg_drawHitbox, 12, 4) & 2) != 0) {
    trap_R_LerpTag(local_420,local_42c,"tag_head",0);
    local_3a8 = local_2c0 * (float)local_340 + local_274 + local_2b4 * local_33c[0] +
                local_2a8 * local_33c[1];
    local_3a4 = local_2bc * (float)local_340 + local_270 + local_2b0 * local_33c[0] +
                local_2a4 * local_33c[1];
    local_3ac = (float)local_340 * local_2c4 + local_278 + local_2b8 * local_33c[0] +
                local_33c[1] * local_2ac;
    MatrixMultiply(&local_334,&local_2c4,&local_378);
    pfVar28 = &local_39c;
    pfVar37 = &local_378;
    do {
      *pfVar28 = *pfVar37 * 32.0 + local_3ac;
      pfVar28[1] = pfVar37[1] * 32.0 + local_3a8;
      pfVar28[2] = pfVar37[2] * 32.0 + local_3a4;
      tmp_u22 = tv(0x3e800000,0x3f000000,0x3f800000);
      pfVar29 = pfVar28 + 3;
      CG_RailTrail2(tmp_u22,&local_3ac,pfVar28,0xffffffff,0xffffffff);
      pfVar28 = pfVar29;
      pfVar37 = pfVar37 + 3;
    } while (pfVar29 != &local_378);
  }
  if ((GHIDRA_FIELD(cg_drawHitbox, 12, 4) & 1) != 0) {
    if ((g_unk_01090766 & 8) == 0) {
      local_370 = g_unk_01090aec;
      if ((g_unk_01090708 & 1) != 0) {
        local_370 = g_unk_01090af0;
      }
    }
    else {
      local_370 = g_unk_01090aec - (g_unk_01090af8 + 8.0 + 8.0);
    }
    local_39c = g_unk_01090ad8 + (float)param_1[0x1e5];
    tmp_u19 = *param_1;
    local_398 = g_unk_01090adc + (float)param_1[0x1e6];
    local_394 = g_unk_01090ae0 + (float)param_1[0x1e7];
    local_378 = g_unk_01090ae4 + (float)param_1[0x1e5];
    local_374 = g_unk_01090ae8 + (float)param_1[0x1e6];
    local_370 = local_370 + (float)param_1[0x1e7];
    tmp_u22 = tv(0x3e800000,0x3f000000,0x3f800000);
    CG_RailTrail(tmp_u22,&local_39c,&local_378,1,tmp_u19 | 0x1000);
    if ((g_unk_01090766 & 8) != 0) {
      local_39c = playerlegsProneMins;
      local_398 = g_unk_0013e990;
      local_394 = g_unk_0013e994;
      local_378 = playerlegsProneMaxs;
      local_374 = g_unk_0013e984;
      local_370 = g_unk_0013e988;
      AngleVectors(param_1 + 0x1e8,local_420,0,0);
      local_33c[1] = 0.0;
      VectorNormalizeFast(local_420);
      tmp_f34 = (float)local_340 * -32.0 + (float)param_1[0x1e5];
      tmp_f2 = local_33c[0] * -32.0 + (float)param_1[0x1e6];
      tmp_u19 = *param_1;
      local_39c = local_39c + tmp_f34;
      local_398 = local_398 + tmp_f2;
      local_394 = local_394 + (float)param_1[0x1e7] + g_unk_010b16a0;
      local_378 = tmp_f34 + local_378;
      local_374 = tmp_f2 + local_374;
      local_370 = (float)param_1[0x1e7] + g_unk_010b16a0 + local_370;
      tmp_u22 = tv(0x3e800000,0x3f000000,0x3f800000);
      CG_RailTrail(tmp_u22,&local_39c,&local_378,1,tmp_u19 | 0x1800);
      local_378 = (float)local_340 * 12.0 + (float)param_1[0x1e5];
      tmp_u19 = *param_1;
      local_374 = local_33c[0] * 12.0 + (float)param_1[0x1e6];
      local_39c = local_378 - 6.0;
      local_398 = local_374 - 6.0;
      local_394 = (float)param_1[0x1e7] - 22.0;
      local_378 = local_378 + 6.0;
      local_374 = local_374 + 6.0;
      local_370 = (float)param_1[0x1e7] - 10.0;
      tmp_u22 = tv(0x3e800000,0x3f000000,0x3f800000);
      CG_RailTrail(tmp_u22,&local_39c,&local_378,1,tmp_u19 | 0x1400);
    }
  }
  if (param_1[1] == 0x26) {
    tmp_i17 = tmp_i16;
  }
  local_1f4[2] = *(int *)(tmp_i17 + 0xa0);
  if (local_1f4[2] == 0) {
    return;
  }
  local_148 = *(uint32_t *)(tmp_i17 + 0xa4);
  CG_PositionRotatedEntityOnTag(local_408,local_42c,"tag_head");
  tmp_u19 = param_1[2];
  if ((tmp_u19 & 0x80) == 0) {
    if (500 < (int)param_1[0x1d2]) {
      param_1[0x1d1] = g_unk_010906e0;
    }
    param_1[0x1d2] = 0;
  }
  else {
    param_1[0x1d1] = 0;
    param_1[0x1d2] = param_1[0x1d2] + g_unk_010906dc;
  }
  if (((int)param_1[0x1da] < (int)g_unk_010906e0) ||
     (((int)(g_unk_010906e0 - param_1[0x1dd]) < 0x96 && ((tmp_u19 & 1) != 0)))) {
    param_1[0x1db] = (uint)((int)param_1[0x27] < 0x28) << 3;
  }
  tmp_u25 = g_unk_010906e0;
  if ((param_1[1] == 0x26) || ((tmp_u19 & 0x800000) != 0)) {
    local_180 = 0;
    local_164 = 0;
    local_154 = 0;
  }
  else {
    tmp_u27 = param_1[0x1db];
    if ((int)param_1[0x1d2] < 0x1f5) {
      if ((499 < (int)(g_unk_010906e0 - param_1[0x1d1])) || ((tmp_u19 & 1) != 0)) goto LAB_000a75a4;
      tmp_u27 = 0xe;
LAB_000a5d06:
      local_1f4[1] = local_1f4[1] | 0x400;
      tmp_u19 = tmp_u27;
    }
    else {
      if ((tmp_u19 & 1) == 0) {
        tmp_u27 = 0xd;
        goto LAB_000a5d06;
      }
LAB_000a75a4:
      if ((int)(g_unk_010906e0 - param_1[0x118]) < *(int *)(tmp_i17 + 0x780) * *(int *)(tmp_i17 + 0x788)
         ) {
        tmp_u27 = 0xf;
        goto LAB_000a5d06;
      }
      if ((int)param_1[0x1d9] < (int)g_unk_010906e0) {
        tmp_i36 = rand();
        param_1[0x1d9] = tmp_u25 + 7000 + tmp_i36 % 1000;
        if (((int)param_1[0x27] < 0x28) || ((param_1[2] & 1) != 0)) {
          tmp_i36 = rand();
          tmp_u19 = tmp_i36 % 2 + 9;
          param_1[0x1db] = tmp_u19;
        }
        else {
          tmp_i36 = rand();
          tmp_u19 = tmp_i36 % 7 + 1;
          param_1[0x1db] = tmp_u19;
        }
        param_1[0x1da] =
             *(int *)(tmp_i17 + 0xf0 + tmp_u19 * 0x70) * *(int *)(tmp_i17 + 0xf8 + tmp_u19 * 0x70) +
             g_unk_010906e0;
      }
      tmp_u19 = 0;
      if (tmp_u27 != 0) goto LAB_000a5d06;
    }
    CG_RunHudHeadLerpFrame(tmp_i17,param_1 + 0xc4,tmp_u19,0x3f800000,tmp_i31 + 0x10f926c);
    local_164 = param_1[0xc4];
    local_180 = param_1[199];
    local_154 = param_1[0xca];
  }
  tmp_pu1 = param_1 + 500;
  CG_AddRefEntityWithPowerups
            (local_408,param_1[0x39],*(uint32_t *)(cgs + tmp_u24 * 0x1a4 + 0x9494),param_1,tmp_pu1);
  tmp_u19 = param_1[0x27];
  if ((((int)tmp_u19 < 5) || (param_1[1] == 0x26)) || ((param_1[2] & 1) != 0)) {
    local_148 = GHIDRA_FIELD(cgs, 131840, 4);
  }
  else if ((int)tmp_u19 < 0x14) {
    local_148 = GHIDRA_FIELD(cgs, 131836, 4);
  }
  else if ((int)tmp_u19 < 0x28) {
    local_148 = GHIDRA_FIELD(cgs, 131832, 4);
  }
  else {
    if (0x3b < (int)tmp_u19) goto LAB_000a5e2b;
    local_148 = GHIDRA_FIELD(cgs, 131828, 4);
  }
  CG_AddRefEntityWithPowerups
            (local_408,param_1[0x39],*(uint32_t *)(cgs + tmp_u24 * 0x1a4 + 0x9494),param_1,tmp_pu1);
LAB_000a5e2b:
  tmp_u19 = 0;
  do {
    tmp_u25 = tmp_u19;
    tmp_u22 = *(uint32_t *)((int)local_1f4 + tmp_u25 + 4);
    *(uint32_t *)((int)param_1 + tmp_u25 + 0x564) = *(uint32_t *)((int)local_1f4 + tmp_u25);
    *(uint32_t *)((int)param_1 + tmp_u25 + 0x568) = tmp_u22;
    tmp_u19 = tmp_u25 + 8;
  } while (tmp_u19 < 0xe8);
  *(uint32_t *)((int)param_1 + tmp_u25 + 0x56c) = *(uint32_t *)((int)local_408 + tmp_u19);
  tmp_u19 = *param_1;
  if (((tmp_u19 != *(uint *)(g_unk_01047b00 + 0xcc)) || (g_unk_010906f4 != 0)) &&
     (((param_1[2] & 0x101) == 0x101 &&
      ((tmp_u25 = CG_PointContents(local_18c,0), (tmp_u25 & 0x38) == 0 &&
       (tmp_i31 = tmp_u19 * 0x1a4, *(int *)(cgs + tmp_i31 + 0x94b4) <= (int)g_unk_010906e0)))))) {
    CG_GetOriginForTag(param_1,local_408,"tag_mouth",0,&local_378,local_420);
    AxisToAngles(local_420,&local_39c);
    AngleVectors(&local_39c,&local_3ac,0,&local_3b8);
    local_378 = local_3ac * 4.0 + local_378;
    local_374 = local_3a8 * 4.0 + local_374;
    local_370 = local_3a4 * 4.0 + local_370;
    local_3ac = local_3ac * 5.0 + local_3b8 * 8.0;
    local_3a8 = local_3a8 * 5.0 + local_3b4 * 8.0;
    local_3a4 = local_3a4 * 5.0 + local_3b0 * 8.0;
    tmp_i36 = g_unk_010906e0 + 3000;
    tmp_u19 = rand();
    *(int *)(cgs + tmp_i31 + 0x94b4) =
         (int)ROUND(((float)(tmp_u19 & 0x7fff) / 32767.0) * 1000.0 + (float)tmp_i36);
  }
  if ((param_1[2] & 0x800001) == 0) {
    CG_AddPlayerWeapon(local_42c,0,param_1);
  }
  if ((tmp_u33 & 0x40000) != 0) {
    local_108[2] = GHIDRA_FIELD(cgs, 68828, 4);
    CG_PositionEntityOnTag(local_414,local_42c,"tag_weapon",0,0);
    CG_AddRefEntityWithPowerups
              (local_414,param_1[0x39],*(uint32_t *)(cgs + tmp_u24 * 0x1a4 + 0x9494),param_1,tmp_pu1
              );
  }
  tmp_i31 = tmp_u24 * 0x1a4;
  if ((param_1[0x39] & 0x80) == 0) {
    local_428 = *(char **)(cgs + tmp_i31 + 0x94c0);
    local_424 = *(int *)(cgs + tmp_i31 + 0x9494);
  }
  else {
    local_428 = *(char **)(cgs + tmp_i31 + 0x955c);
    local_424 = (*(int *)(cgs + tmp_i31 + 0x9494) == 1) + 1;
  }
  tmp_pi18 = (int *)(tmp_i16 + 0x48);
  tmp_i31 = 0;
  do {
    tmp_i36 = *tmp_pi18;
    if ((tmp_i36 != 0) &&
       ((local_5c = tmp_pi18[0xb], local_108[2] = tmp_i36, param_1[1] != 0x26 || (param_1[0x16] != 1))
       )) {
      switch(tmp_i31) {
      default:
        tmp_pc23 = "tag_bright";
        break;
      case 1:
        tmp_pc23 = "tag_bleft";
        break;
      case 2:
        tmp_pc23 = "tag_ubelt";
        break;
      case 3:
        tmp_pc23 = "tag_back";
        break;
      case 4:
        tmp_pc23 = "tag_weapon";
        break;
      case 5:
        tmp_pc23 = "tag_weapon2";
        break;
      case 6:
      case 7:
      case 9:
      case 10:
        if ((*(byte *)((int)param_1 + 9) & 0x10) != 0) goto LAB_000a6087;
        if (tmp_i31 != 10) {
          if (tmp_i31 == 6) {
            if (9 < (int)local_428) goto LAB_000a7a67;
            goto LAB_000a6026;
          }
          if (tmp_i31 != 9) goto LAB_000a6026;
LAB_000a7a67:
          if ((*(byte *)((int)param_1 + 0xe5) & 0x10) != 0) goto LAB_000a6026;
          goto LAB_000a6090;
        }
        tmp_u19 = param_1[0x39];
        if (((int)local_428 - 1U < 9) && ((tmp_u19 & 0x1000) == 0)) {
          local_58 = *(uint32_t *)
                      (rankicons + ((uint)(local_424 == 1) + (int)local_428 * 2) * 0x20 + 0x10);
LAB_000a6026:
          CG_PositionEntityOnTag(local_414,local_408,"tag_mouth",0,0);
          goto _L1278;
        }
        goto LAB_000a6686;
      case 8:
        goto _L1278;
      }
      CG_PositionEntityOnTag(local_414,local_42c,tmp_pc23,0,0);
_L1278:
      CG_AddRefEntityWithPowerups
                (local_414,param_1[0x39],*(uint32_t *)(cgs + tmp_u24 * 0x1a4 + 0x9494),param_1,
                 tmp_pu1);
    }
LAB_000a6087:
    if (tmp_i31 == 10) {
      tmp_u19 = param_1[0x39];
LAB_000a6686:
      tmp_f34 = 0.0;
      if (((GHIDRA_FIELD(cgs, 33823068, 4) == 0) && (g_unk_01047aec == 0)) && (GHIDRA_FIELD(demo_wallHack, 12, 4) == 0)) {
        tmp_f34 = local_2e0[1];
      }
      CG_AddRefEntityWithPowerups
                (local_42c,tmp_u19,*(uint32_t *)(cgs + tmp_u24 * 0x1a4 + 0x9494),param_1,tmp_pu1);
      if (((GHIDRA_FIELD(cgs, 33823068, 4) == 0) && (g_unk_01047aec == 0)) &&
         ((GHIDRA_FIELD(demo_wallHack, 12, 4) == 0 && ((local_2e0[1] != tmp_f34 || (((uint)tmp_f34 & 8) != 0)))))) {
        GHIDRA_FIELD(cgs, 33823112, 4) = GHIDRA_FIELD(cgs, 33823112, 4) | 0x20;
        GHIDRA_FIELD(cgs, 33823068, 4) = 1;
      }
      tmp_u24 = 0;
      do {
        tmp_u19 = tmp_u24;
        tmp_u22 = *(uint32_t *)((int)local_2e0 + tmp_u19 + 4);
        *(uint32_t *)((int)param_1 + tmp_u19 + 0x478) = *(uint32_t *)((int)local_2e0 + tmp_u19);
        *(uint32_t *)((int)param_1 + tmp_u19 + 0x47c) = tmp_u22;
        tmp_u24 = tmp_u19 + 8;
      } while (tmp_u24 < 0xe8);
      *(uint32_t *)((int)param_1 + tmp_u19 + 0x480) = *(uint32_t *)((int)local_42c + tmp_u24);
      param_1[0x11f] = local_404;
      if (local_40c == 0) {
        return;
      }
      if (GHIDRA_FIELD(cg_shadows, 12, 4) != 3) {
        return;
      }
      local_2e0[1] = (float)((uint)local_2e0[1] & 0xfffffffd);
      local_230 = GHIDRA_FIELD(cgs, 67840, 4);
      trap_R_AddRefEntityToScene(local_42c);
      return;
    }
LAB_000a6090:
    tmp_i31 = tmp_i31 + 1;
    tmp_pi18 = tmp_pi18 + 1;
  } while( true );
}

void CG_HudHeadAnimation(int param_1,uint32_t *param_2,uint32_t *param_3,uint32_t *param_4,
                        uint32_t *param_5,uint param_6)

{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  int local_30;
  int local_2c;
  
  tmp_i6 = g_unk_010906e0;
  tmp_pu5 = (uint32_t *)param_2[0xd];
  if (tmp_pu5 == (uint32_t *)0x0) {
    param_2[0xb] = param_6;
    param_6 = param_6 & 0xfffffdff;
    param_2[1] = tmp_i6;
    param_2[4] = tmp_i6;
    if (0xf < param_6) {
      CG_Error("Bad animation number (CG_SetHudHeadLerpFrameAnimation): %i",param_6);
      tmp_i6 = param_2[4];
    }
    tmp_i1 = param_6 * 0x70;
    tmp_i4 = param_1 + 0xa0 + tmp_i1;
    tmp_pu5 = (uint32_t *)(tmp_i4 + 8);
    param_2[0xd] = tmp_pu5;
    param_2[0xe] = *(int *)(param_1 + 0xfc + tmp_i1) + tmp_i6;
    tmp_u3 = *(uint32_t *)(param_1 + 0xec + tmp_i1);
    param_2[3] = tmp_u3;
    *param_2 = tmp_u3;
    tmp_u3 = *(uint32_t *)(tmp_i4 + 8);
    param_2[5] = tmp_u3;
    param_2[2] = tmp_u3;
  }
  else if (param_6 == param_2[0xb]) {
    tmp_i6 = param_2[4];
  }
  else {
    param_2[0xb] = param_6;
    param_6 = param_6 & 0xfffffdff;
    if (0xf < param_6) {
      CG_Error("Bad animation number (CG_SetHudHeadLerpFrameAnimation): %i",param_6);
    }
    tmp_i6 = param_2[4];
    tmp_pu5 = (uint32_t *)(param_1 + 0xa8 + param_6 * 0x70);
    param_2[0xd] = tmp_pu5;
    param_2[0xe] = *(int *)(param_1 + 0xfc + param_6 * 0x70) + tmp_i6;
  }
  if (g_unk_010906e0 < tmp_i6) {
    local_30 = tmp_i6;
    tmp_i6 = param_2[1];
  }
  else {
    tmp_u3 = param_2[3];
    param_2[1] = tmp_i6;
    param_2[2] = param_2[5];
    *param_2 = tmp_u3;
    if (tmp_pu5[0x14] == 0) goto LAB_000a7ba9;
    tmp_i4 = param_2[0xe];
    local_2c = 0;
    local_30 = tmp_i4;
    if (tmp_i4 <= g_unk_010906e0) {
      local_30 = tmp_pu5[0x14] + tmp_i6;
      local_2c = local_30 - tmp_i4;
    }
    param_2[4] = local_30;
    tmp_i4 = (int)ROUND((long double)(local_2c / (int)tmp_pu5[0x14]));
    tmp_i1 = tmp_pu5[0x12];
    if (tmp_i1 <= tmp_i4) {
      tmp_i2 = tmp_pu5[0x13];
      if (tmp_i2 == 0) {
        local_30 = g_unk_010906e0;
        tmp_i4 = tmp_i1 + -1;
        param_2[4] = g_unk_010906e0;
      }
      else {
        tmp_i4 = (tmp_i1 - tmp_i2) + (tmp_i4 - tmp_i1) % tmp_i2;
      }
    }
    param_2[3] = tmp_i4 + tmp_pu5[0x11];
    param_2[5] = *tmp_pu5;
    tmp_i4 = g_unk_010906e0;
    if (local_30 < g_unk_010906e0) {
      param_2[4] = g_unk_010906e0;
      local_30 = tmp_i4;
    }
  }
  tmp_i4 = g_unk_010906e0;
  if (g_unk_010906e0 + 200 < local_30) {
    param_2[4] = g_unk_010906e0;
    local_30 = tmp_i4;
  }
  tmp_i4 = g_unk_010906e0;
  if (g_unk_010906e0 < tmp_i6) {
    param_2[1] = g_unk_010906e0;
    tmp_i6 = tmp_i4;
  }
  if (local_30 == tmp_i6) {
    param_2[6] = 0;
    tmp_u3 = *param_2;
  }
  else {
    tmp_u3 = *param_2;
    param_2[6] = 1.0 - (float)(g_unk_010906e0 - tmp_i6) / (float)(local_30 - tmp_i6);
  }
LAB_000a7ba9:
  *param_3 = tmp_u3;
  *param_4 = param_2[3];
  *param_5 = param_2[6];
  return;
}

