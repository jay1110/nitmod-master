/* Client-side prediction and collision — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_predict.h"

void CG_InterpolateEntityPosition_part_3(int param_1)
{
  int tmp_i1;
  float tmp_f2;
  long double tmp_l3;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  tmp_f2 = g_unk_010906d0;
  uStack_14 = 0x6672b;
  BG_EvaluateTrajectory
            (param_1 + 0xc,*(uint32_t *)(g_unk_01047b00 + 8),&local_34,0,
             *(uint32_t *)(param_1 + 0x110));
  BG_EvaluateTrajectory
            (param_1 + 300,*(uint32_t *)(g_unk_01047b04 + 8),&local_28,0,
             *(uint32_t *)(param_1 + 0x110));
  tmp_i1 = g_unk_01047b00;
  *(float *)(param_1 + 0x794) = (local_28 - local_34) * tmp_f2 + local_34;
  *(float *)(param_1 + 0x798) = (local_24 - local_30) * tmp_f2 + local_30;
  *(float *)(param_1 + 0x79c) = (local_20 - local_2c) * tmp_f2 + local_2c;
  BG_EvaluateTrajectory
            (param_1 + 0x30,*(uint32_t *)(tmp_i1 + 8),&local_34,1,*(uint32_t *)(param_1 + 0x110))
  ;
  BG_EvaluateTrajectory
            (param_1 + 0x150,*(uint32_t *)(g_unk_01047b04 + 8),&local_28,1,
             *(uint32_t *)(param_1 + 0x110));
  tmp_l3 = (long double)LerpAngle(local_34,local_28,tmp_f2);
  *(float *)(param_1 + 0x7a0) = (float)tmp_l3;
  tmp_l3 = (long double)LerpAngle(local_30,local_24,tmp_f2);
  *(float *)(param_1 + 0x7a4) = (float)tmp_l3;
  tmp_l3 = (long double)LerpAngle(local_2c,local_20,tmp_f2);
  *(float *)(param_1 + 0x7a8) = (float)tmp_l3;
  return;
}

void CG_PredictLean(int param_1,int param_2,int param_3,int param_4)
{
  float tmp_f1;
  uint tmp_u2;
  float tmp_f3;
  int tmp_i4;
  uint tmp_u5;
  int local_a4;
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
  
  tmp_i4 = g_unk_010906e0;
  if (*(int *)(param_1 + 0x98) < 0) {
    tmp_u5 = 0xffffffff;
  }
  else {
    tmp_u5 = (uint)(0 < *(int *)(param_1 + 0x98));
  }
  tmp_u2 = *(uint *)(param_1 + 8);
  if ((tmp_u2 & 0x8020) != 0) {
    tmp_u5 = 0;
  }
  if ((tmp_u2 & 0x80) != 0) {
    tmp_u5 = 0;
  }
  if ((tmp_u2 & 1) != 0) {
    tmp_u5 = 0;
  }
  if ((tmp_u2 & 0x800000) != 0) {
    tmp_u5 = 0;
  }
  if ((tmp_u2 & 0x80000) == 0) {
    tmp_f1 = *(float *)(param_1 + 0x750);
    if (*(int *)(param_1 + 0xe8) == 0x2a) {
      tmp_u5 = 0;
    }
    if (*(uint *)(param_1 + 0x754) != tmp_u5) goto LAB_000a1625;
LAB_000a18c4:
    tmp_i4 = *(int *)(param_1 + 0x74c);
  }
  else {
    tmp_u5 = 0;
    tmp_f1 = *(float *)(param_1 + 0x750);
    if (*(int *)(param_1 + 0x754) == 0) goto LAB_000a18c4;
LAB_000a1625:
    *(uint *)(param_1 + 0x754) = tmp_u5;
    *(int *)(param_1 + 0x74c) = tmp_i4;
  }
  tmp_i4 = g_unk_010906e0 - tmp_i4;
  if (tmp_i4 < 1) {
    *(int *)(param_1 + 0x74c) = g_unk_010906e0;
    local_a4 = 1;
  }
  else {
    local_a4 = 200;
    if (tmp_i4 < 0xc9) {
      local_a4 = tmp_i4;
    }
    *(int *)(param_1 + 0x74c) = g_unk_010906e0;
  }
  if (tmp_u5 == 0) {
    if (tmp_f1 <= 0.0) {
      if ((tmp_f1 < 0.0) && (tmp_f1 = ((float)local_a4 / 300.0) * 28.0 + tmp_f1, 0.0 < tmp_f1)) {
        tmp_f1 = 0.0;
      }
    }
    else {
      tmp_f3 = tmp_f1 - ((float)local_a4 / 300.0) * 28.0;
      tmp_f1 = 0.0;
      if (0.0 <= tmp_f3) {
        tmp_f1 = tmp_f3;
      }
    }
    goto LAB_000a16b0;
  }
  if (tmp_u5 == 1) {
    if (tmp_f1 < 28.0) {
      tmp_f1 = ((float)local_a4 / 200.0) * 28.0 + tmp_f1;
    }
    if (28.0 < tmp_f1) {
      local_58 = 14.0;
      tmp_f1 = 28.0;
    }
    else {
LAB_000a1784:
      local_58 = tmp_f1 * 0.5;
    }
  }
  else {
    if (-28.0 < tmp_f1) {
      tmp_f1 = tmp_f1 - ((float)local_a4 / 200.0) * 28.0;
    }
    if (-28.0 <= tmp_f1) goto LAB_000a1784;
    local_58 = -14.0;
    tmp_f1 = -28.0;
  }
  *(float *)(param_1 + 0x750) = tmp_f1;
  local_9c = *(float *)(param_1 + 0x794);
  local_98 = *(float *)(param_1 + 0x798);
  local_94 = (float)param_4 + *(float *)(param_1 + 0x79c);
  local_60 = *(uint32_t *)(param_1 + 0x7a0);
  local_5c = *(uint32_t *)(param_1 + 0x7a4);
  local_58 = local_58 + *(float *)(param_1 + 0x7a8);
  AngleVectors(&local_60,0,&local_6c,0);
  local_84 = 0xc1000000;
  local_80 = 0xc1000000;
  local_90 = local_6c * tmp_f1 + local_9c;
  local_7c = 0xc0e00000;
  local_78 = 0x41000000;
  local_74 = 0x41000000;
  local_8c = local_68 * tmp_f1 + local_98;
  local_70 = 0x40800000;
  local_88 = tmp_f1 * local_64 + local_94;
  CG_Trace(local_54,&local_9c,&local_84,&local_78,&local_90,*(uint32_t *)(param_1 + 0xac),
           0x2010001);
  tmp_f1 = *(float *)(param_1 + 0x750) * local_4c;
LAB_000a16b0:
  *(float *)(param_1 + 0x750) = tmp_f1;
  if ((cgs[0x2038e69] & 1) == 0) {
    if ((g_unk_010ef1dc & 0x20) != 0) {
      if (param_2 != 0) {
        *(float *)(param_2 + 8) = tmp_f1 * 1.25 + *(float *)(param_2 + 8);
      }
      if (param_3 != 0) {
        *(float *)(param_3 + 8) = *(float *)(param_1 + 0x750) + *(float *)(param_3 + 8);
        return;
      }
    }
  }
  else if (param_2 != 0) {
    if (tmp_u5 == 1) {
      tmp_f1 = tmp_f1 * 1.9 + *(float *)(param_2 + 8);
    }
    else {
      tmp_f1 = tmp_f1 * 2.35 + *(float *)(param_2 + 8);
    }
    *(float *)(param_2 + 8) = tmp_f1;
    *(float *)(param_3 + 8) = *(float *)(param_1 + 0x750) + *(float *)(param_3 + 8);
  }
  return;
}

void CG_TransitionPlayerState(uint32_t *param_1,uint32_t *param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint tmp_u4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  uint32_t *tmp_pu7;
  int tmp_i8;
  int local_38;
  uint local_34;
  
  if (param_1[0x28] != param_2[0x28]) {
    g_unk_010906d4 = 1;
    g_unk_01091638 = 0;
    *(uint32_t *)(cg_entities + param_1[0x28] * 0xaf8 + 0x990) = 0;
    tmp_u4 = 0x5ac;
    tmp_pu6 = param_1;
    tmp_pu7 = param_2;
    if (((uint)param_2 & 4) != 0) {
      tmp_pu6 = param_1 + 1;
      tmp_u4 = 0x5a8;
      *param_2 = *param_1;
      tmp_pu7 = param_2 + 1;
    }
    for (tmp_u4 = tmp_u4 >> 2; tmp_u4 != 0; tmp_u4 = tmp_u4 - 1) {
      *tmp_pu7 = *tmp_pu6;
      tmp_pu6 = tmp_pu6 + 1;
      tmp_pu7 = tmp_pu7 + 1;
    }
    if (param_1[0x28] == g_unk_01047ac4) {
      param_2[0x4c] = param_2[0x4c] + -1;
    }
  }
  if ((*(byte *)(param_1 + 0x1a) & 0x80) == 0) {
    if (500 < g_unk_010aad08) {
      g_unk_010aad00 = g_unk_010906e0;
    }
    g_unk_010aad08 = 0;
  }
  else {
    g_unk_010aad00 = 0;
    g_unk_010aad08 = g_unk_010aad08 + g_unk_010906dc;
  }
  if ((param_1[0x30] != param_2[0x30]) && (param_1[0x33] != 0)) {
    CG_DamageFeedback(param_1[0x31],param_1[0x32],param_1[0x33]);
  }
  if (param_1[0x4c] != param_2[0x4c]) {
    CG_Respawn(param_1[0x4f] != param_2[0x4f]);
  }
  if (g_unk_010906f0 != 0) {
    CG_Respawn(0);
    g_unk_010906f0 = 0;
  }
  if ((*(int *)(g_unk_01047b00 + 0x30) != 5) && (param_1[0x4b] != 3)) {
    CG_CheckLocalSounds(param_1,param_2);
  }
  tmp_i1 = *(int *)(g_unk_01047b00 + 0x400);
  if ((tmp_i1 != 0) || (*(int *)(g_unk_01047b00 + 0x404) != 0)) {
    tmp_i8 = 0;
    tmp_i5 = 0x33;
    do {
      tmp_i2 = g_unk_01047b00;
      if ((tmp_i1 >> ((byte)tmp_i5 & 0x1f) & 1U) != 0) {
        tmp_i3 = BG_FindAmmoForWeapon(tmp_i5);
        tmp_i8 = tmp_i8 + *(int *)(tmp_i2 + 0x1bc + tmp_i3 * 4) * 1000;
        if (4999 < tmp_i8) {
          g_unk_01093554 = 0;
          goto LAB_000a905e;
        }
      }
      tmp_i5 = tmp_i5 + -1;
    } while (tmp_i5 != -1);
    if (g_unk_01093554 == 0) {
      trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69412, 4),6);
    }
    g_unk_01093554 = ~-(uint)(tmp_i8 == 0) + 2;
  }
LAB_000a905e:
  tmp_u4 = param_1[0x1a];
  if ((tmp_u4 & 0x100000) == 0) {
    if ((*(byte *)((int)param_2 + 0x6a) & 0x10) == 0) goto LAB_000a908a;
    g_unk_010b3b2c = -g_unk_010906e0;
  }
  else {
    if ((param_1[0x29] == 0x13) && ((tmp_u4 & 0x40000) != 0)) {
      trap_SendConsoleCommand("-zoom\n");
    }
    if ((*(byte *)((int)param_2 + 0x6a) & 0x10) == 0) {
      g_unk_010b3b2c = g_unk_010906e0;
      tmp_u4 = param_1[0x1a];
      goto LAB_000a908a;
    }
  }
  tmp_u4 = param_1[0x1a];
LAB_000a908a:
  if ((((tmp_u4 & 0x80000) == 0) && ((*(byte *)((int)param_2 + 0x6a) & 8) != 0)) &&
     (g_unk_01091814 == 0x2e)) {
    CG_FinishWeaponChange(0x2e,param_1[0x107]);
  }
  local_38 = param_1[0x1b];
  tmp_u4 = local_38 - 4;
  do {
    if ((int)tmp_u4 < (int)param_2[0x1b]) {
      if (param_2[0x1b] + -3 <= (int)tmp_u4) {
        tmp_i1 = (tmp_u4 & 3) + 0x1c;
        tmp_i5 = param_1[tmp_i1];
        if (tmp_i5 != param_2[tmp_i1]) goto LAB_000a90d9;
      }
    }
    else {
      tmp_i5 = param_1[(tmp_u4 & 3) + 0x1c];
LAB_000a90d9:
      local_34 = tmp_u4 & 3;
      g_unk_01090d64 = param_1[local_34 + 0x20];
      g_unk_01090d60 = tmp_i5;
      CG_EntityEvent(&g_unk_01090ca8,&g_unk_0109143c);
      g_unk_010917b4 = g_unk_010917b4 + 1;
      *(int *)(&g_unk_010917b8 + (tmp_u4 & 0xf) * 4) = tmp_i5;
      local_38 = param_1[0x1b];
    }
    tmp_u4 = tmp_u4 + 1;
    if (local_38 <= (int)tmp_u4) {
      if (param_1[0x2f] != param_2[0x2f]) {
        g_unk_01091800 = (float)(int)(param_1[0x2f] - param_2[0x2f]);
        g_unk_01091804 = g_unk_010906e0;
        if (((*(byte *)((int)param_2 + 0x6a) & 0x80) != 0) &&
           ((*(byte *)((int)param_1 + 0x6a) & 0x80) == 0)) {
          g_unk_01091808 = 1;
          return;
        }
        g_unk_01091808 = 0;
      }
      return;
    }
  } while( true );
}

uint CG_PointContents(uint32_t param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  uint local_20;
  
  local_20 = trap_CM_PointContents(param_1,0);
  if (0 < cg_numSolidEntities) {
    tmp_i4 = 0;
    tmp_i2 = cg_numSolidEntities;
    do {
      while ((tmp_pi1 = (int *)(&cg_solidEntities)[tmp_i4], *tmp_pi1 == param_2 ||
             (tmp_pi1[0x2d] != 0xffffff))) {
        tmp_i4 = tmp_i4 + 1;
        if (tmp_i2 <= tmp_i4) {
          return local_20;
        }
      }
      tmp_i2 = trap_CM_InlineModel(tmp_pi1[0x29]);
      if (tmp_i2 != 0) {
        tmp_u3 = trap_CM_TransformedPointContents(param_1,tmp_i2,tmp_pi1 + 0x1e5,tmp_pi1 + 0x1e8);
        local_20 = local_20 | tmp_u3;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_i2 = cg_numSolidEntities;
    } while (tmp_i4 < cg_numSolidEntities);
  }
  return local_20;
}

void CG_InterpolatePlayerState(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  uint32_t *tmp_pu7;
  float *pfVar8;
  uint32_t *tmp_pu9;
  float *pfVar10;
  long double tmp_l11;
  uint8_t local_38 [40];
  
  tmp_i3 = g_unk_01047b04;
  tmp_i2 = g_unk_01047b00;
  g_unk_010906fc = *(uint32_t *)(g_unk_01047b00 + 0x2c);
  tmp_pu7 = (uint32_t *)(g_unk_01047b00 + 0x30);
  tmp_pu9 = &g_unk_01090700;
  for (tmp_i6 = 0x16a; tmp_i6 != 0; tmp_i6 = tmp_i6 + -1) {
    *tmp_pu9 = *tmp_pu7;
    tmp_pu7 = tmp_pu7 + 1;
    tmp_pu9 = tmp_pu9 + 1;
  }
  if (g_unk_010abd78 == 0) {
    if (param_1 != 0) {
      tmp_u5 = trap_GetCurrentCmdNumber();
      trap_GetUserCmd(tmp_u5,local_38);
      PM_UpdateViewAngles(&g_unk_010906fc,&g_unk_010b1668,local_38,CG_Trace,0x2010001);
    }
    if ((g_unk_010906d8 == 0) && (tmp_i3 != 0)) {
      tmp_i6 = *(int *)(tmp_i2 + 8);
      if (tmp_i6 < *(int *)(tmp_i3 + 8)) {
        tmp_i4 = *(int *)(tmp_i3 + 0x34);
        if (tmp_i4 < *(int *)(tmp_i2 + 0x34)) {
          tmp_i4 = tmp_i4 + 0x100;
        }
        tmp_f1 = (float)(g_unk_010906e0 - tmp_i6) / (float)(*(int *)(tmp_i3 + 8) - tmp_i6);
        g_unk_01090704 = (int)ROUND((float)(tmp_i4 - *(int *)(tmp_i2 + 0x34)) * tmp_f1 +
                                  (float)*(int *)(tmp_i2 + 0x34));
        if (param_1 == 0) {
          tmp_pu7 = &cg;
          pfVar8 = (float *)(tmp_i2 + 0x40);
          pfVar10 = (float *)(tmp_i3 + 0x40);
          do {
            tmp_pu9 = tmp_pu7 + 1;
            tmp_pu7[0x12314] = (*pfVar10 - *pfVar8) * tmp_f1 + *pfVar8;
            tmp_l11 = (long double)LerpAngle(pfVar8[0x27],pfVar10[0x27],tmp_f1);
            tmp_pu7[0x1233b] = (float)tmp_l11;
            tmp_pu7[0x12317] = (pfVar10[3] - pfVar8[3]) * tmp_f1 + pfVar8[3];
            tmp_pu7 = tmp_pu9;
            pfVar8 = pfVar8 + 1;
            pfVar10 = pfVar10 + 1;
          } while (tmp_pu9 != &g_unk_01047acc);
        }
        else {
          g_unk_01090710 = (*(float *)(tmp_i3 + 0x40) - *(float *)(tmp_i2 + 0x40)) * tmp_f1 +
                         *(float *)(tmp_i2 + 0x40);
          g_unk_0109071c = (*(float *)(tmp_i3 + 0x4c) - *(float *)(tmp_i2 + 0x4c)) * tmp_f1 +
                         *(float *)(tmp_i2 + 0x4c);
          g_unk_01090714 = (*(float *)(tmp_i3 + 0x44) - *(float *)(tmp_i2 + 0x44)) * tmp_f1 +
                         *(float *)(tmp_i2 + 0x44);
          g_unk_01090720 = (*(float *)(tmp_i3 + 0x50) - *(float *)(tmp_i2 + 0x50)) * tmp_f1 +
                         *(float *)(tmp_i2 + 0x50);
          g_unk_01090718 = (*(float *)(tmp_i3 + 0x48) - *(float *)(tmp_i2 + 0x48)) * tmp_f1 +
                         *(float *)(tmp_i2 + 0x48);
          g_unk_01090724 = *(float *)(tmp_i2 + 0x54) +
                         (*(float *)(tmp_i3 + 0x54) - *(float *)(tmp_i2 + 0x54)) * tmp_f1;
        }
      }
    }
  }
  return;
}

void CG_Trace(int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
             uint32_t param_5,int param_6,uint32_t param_7)

{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  uint32_t local_98;
  uint32_t local_94;
  uint32_t local_90;
  int local_8c [2];
  float local_84;
  uint32_t local_58;
  int local_54 [2];
  float local_4c;
  int local_20;
  
  trap_CM_BoxTrace(local_8c,param_2,param_5,param_3,param_4,0,param_7);
  if (local_84 == 1.0) {
    local_58 = 0x3ff;
  }
  else {
    local_58 = 0x3fe;
  }
  tmp_i5 = 0;
  tmp_i2 = cg_numSolidEntities;
  if (0 < cg_numSolidEntities) {
    do {
      tmp_pi1 = (int *)(&cg_solidEntities)[tmp_i5];
      if (param_6 != *tmp_pi1) {
        tmp_u4 = tmp_pi1[0x2d];
        if (tmp_u4 == 0xffffff) {
          tmp_u3 = trap_CM_InlineModel(tmp_pi1[0x29]);
          BG_EvaluateTrajectory(tmp_pi1 + 0xc,g_unk_010906e8,&local_98,1,tmp_pi1[0x44]);
          BG_EvaluateTrajectory(tmp_pi1 + 3,g_unk_010906e8,&local_a4,0,tmp_pi1[0x44]);
        }
        else {
          if ((*(byte *)((int)tmp_pi1 + 10) & 1) == 0) {
            local_bc = (float)(int)-(tmp_u4 & 0xff);
            local_b0 = (float)(tmp_u4 & 0xff);
            local_b4 = (float)(int)-(tmp_u4 >> 8 & 0xff);
            local_a8 = (float)(int)(((int)tmp_u4 >> 0x10 & 0xffU) - 0x20);
            local_b8 = local_bc;
            local_ac = local_b0;
          }
          else {
            local_bc = (float)tmp_pi1[0x1a];
            local_b8 = (float)tmp_pi1[0x1b];
            local_b4 = (float)tmp_pi1[0x1c];
            local_b0 = (float)tmp_pi1[0x20];
            local_ac = (float)tmp_pi1[0x21];
            local_a8 = (float)tmp_pi1[0x22];
          }
          tmp_u3 = trap_CM_TempBoxModel(&local_bc,&local_b0);
          local_98 = vec3_origin;
          local_94 = g_unk_00c22b14;
          local_90 = g_unk_00c22b18;
          local_a4 = tmp_pi1[0x1e5];
          local_a0 = tmp_pi1[0x1e6];
          local_9c = tmp_pi1[0x1e7];
        }
        trap_CM_TransformedBoxTrace
                  (local_54,param_2,param_5,param_3,param_4,tmp_u3,param_7,&local_a4,&local_98);
        if ((local_54[0] != 0) || (local_4c < local_84)) {
          local_20 = *tmp_pi1;
          tmp_u4 = 0;
          do {
            *(uint32_t *)((int)local_8c + tmp_u4) = *(uint32_t *)((int)local_54 + tmp_u4);
            tmp_u4 = tmp_u4 + 4;
          } while (tmp_u4 < 0x38);
        }
        else if (local_54[1] != 0) {
          local_8c[1] = 1;
        }
        tmp_i2 = cg_numSolidEntities;
        if (local_8c[0] != 0) break;
      }
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 < tmp_i2);
  }
  tmp_u4 = 0;
  do {
    *(uint32_t *)(param_1 + tmp_u4) = *(uint32_t *)((int)local_8c + tmp_u4);
    tmp_u4 = tmp_u4 + 4;
  } while (tmp_u4 < 0x38);
  return;
}

void CG_TraceCapsule(int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
                    uint32_t param_5,int param_6,uint32_t param_7)

{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  uint32_t local_98;
  uint32_t local_94;
  uint32_t local_90;
  int local_8c [2];
  float local_84;
  uint32_t local_58;
  int local_54 [2];
  float local_4c;
  int local_20;
  
  trap_CM_CapsuleTrace(local_8c,param_2,param_5,param_3,param_4,0,param_7);
  if (local_84 == 1.0) {
    local_58 = 0x3ff;
  }
  else {
    local_58 = 0x3fe;
  }
  tmp_i5 = 0;
  tmp_i2 = cg_numSolidEntities;
  if (0 < cg_numSolidEntities) {
    do {
      tmp_pi1 = (int *)(&cg_solidEntities)[tmp_i5];
      if (param_6 != *tmp_pi1) {
        tmp_u4 = tmp_pi1[0x2d];
        if (tmp_u4 == 0xffffff) {
          tmp_u3 = trap_CM_InlineModel(tmp_pi1[0x29]);
          BG_EvaluateTrajectory(tmp_pi1 + 0xc,g_unk_010906e8,&local_98,1,tmp_pi1[0x44]);
          BG_EvaluateTrajectory(tmp_pi1 + 3,g_unk_010906e8,&local_a4,0,tmp_pi1[0x44]);
        }
        else {
          if ((*(byte *)((int)tmp_pi1 + 10) & 1) == 0) {
            local_bc = (float)(int)-(tmp_u4 & 0xff);
            local_b0 = (float)(tmp_u4 & 0xff);
            local_b4 = (float)(int)-(tmp_u4 >> 8 & 0xff);
            local_a8 = (float)(int)(((int)tmp_u4 >> 0x10 & 0xffU) - 0x20);
            local_b8 = local_bc;
            local_ac = local_b0;
          }
          else {
            local_bc = (float)tmp_pi1[0x1a];
            local_b8 = (float)tmp_pi1[0x1b];
            local_b4 = (float)tmp_pi1[0x1c];
            local_b0 = (float)tmp_pi1[0x20];
            local_ac = (float)tmp_pi1[0x21];
            local_a8 = (float)tmp_pi1[0x22];
          }
          tmp_u3 = trap_CM_TempBoxModel(&local_bc,&local_b0);
          local_98 = vec3_origin;
          local_94 = g_unk_00c22b14;
          local_90 = g_unk_00c22b18;
          local_a4 = tmp_pi1[0x1e5];
          local_a0 = tmp_pi1[0x1e6];
          local_9c = tmp_pi1[0x1e7];
        }
        trap_CM_TransformedCapsuleTrace
                  (local_54,param_2,param_5,param_3,param_4,tmp_u3,param_7,&local_a4,&local_98);
        if ((local_54[0] != 0) || (local_4c < local_84)) {
          local_20 = *tmp_pi1;
          tmp_u4 = 0;
          do {
            *(uint32_t *)((int)local_8c + tmp_u4) = *(uint32_t *)((int)local_54 + tmp_u4);
            tmp_u4 = tmp_u4 + 4;
          } while (tmp_u4 < 0x38);
        }
        else if (local_54[1] != 0) {
          local_8c[1] = 1;
        }
        tmp_i2 = cg_numSolidEntities;
        if (local_8c[0] != 0) break;
      }
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 < tmp_i2);
  }
  tmp_u4 = 0;
  do {
    *(uint32_t *)(param_1 + tmp_u4) = *(uint32_t *)((int)local_8c + tmp_u4);
    tmp_u4 = tmp_u4 + 4;
  } while (tmp_u4 < 0x38);
  return;
}

void CG_BuildSolidList(void)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int *local_28;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  cg_numSolidEntities = 0;
  cg_numTriggerEntities = 0;
  local_14 = g_unk_01047b04;
  if (((g_unk_01047b04 == 0) || (g_unk_010906d8 != 0)) || (g_unk_010906d4 != 0)) {
    local_14 = g_unk_01047b00;
  }
  local_1c = *(int *)(local_14 + 0x5d8);
  if (0 < local_1c) {
    local_18 = 0;
    local_28 = (int *)(local_14 + 0x5dc);
    tmp_i4 = 0;
    local_20 = 0;
    do {
      while( true ) {
        tmp_i2 = *local_28;
        tmp_i3 = tmp_i2 * 0xaf8;
        tmp_pu1 = cg_entities + tmp_i3;
        if ((*(int *)(cg_entities + tmp_i3 + 0xb4) != 0xffffff) ||
           ((cg_entities[tmp_i3 + 8] & 2) == 0)) break;
        tmp_i4 = tmp_i4 + 1;
        local_28 = local_28 + 0x48;
        if (local_1c <= tmp_i4) goto LAB_000abcab;
      }
      tmp_i3 = *(int *)(cg_entities + tmp_i2 * 0xaf8 + 4);
      if ((tmp_i3 - 8U < 2 || tmp_i3 - 0xbU < 2) || (tmp_i3 == 2)) {
        (&cg_triggerEntities)[local_20] = tmp_pu1;
        local_20 = local_20 + 1;
      }
      else {
        if (tmp_i3 == 0x20) {
          (&cg_triggerEntities)[local_20] = tmp_pu1;
          local_20 = local_20 + 1;
        }
        if (*(int *)(cg_entities + tmp_i2 * 0xaf8 + 0x1d4) != 0) {
          (&cg_solidEntities)[local_18] = tmp_pu1;
          local_18 = local_18 + 1;
          local_1c = *(int *)(local_14 + 0x5d8);
        }
      }
      tmp_i4 = tmp_i4 + 1;
      local_28 = local_28 + 0x48;
    } while (tmp_i4 < local_1c);
LAB_000abcab:
    cg_numTriggerEntities = local_20;
    cg_numSolidEntities = local_18;
  }
  return;
}

void CG_Trace_World(int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
                   uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  uint tmp_u1;
  float local_44 [16];
  
  trap_CM_BoxTrace(local_44,param_2,param_5,param_3,param_4,0,param_7);
  if (local_44[2] == 1.0) {
    local_44[0xd] = 1.43353e-42;
  }
  else {
    local_44[0xd] = 1.43213e-42;
  }
  tmp_u1 = 0;
  do {
    *(uint32_t *)(param_1 + tmp_u1) = *(uint32_t *)((int)local_44 + tmp_u1);
    tmp_u1 = tmp_u1 + 4;
  } while (tmp_u1 < 0x38);
  return;
}

uint32_t CG_PredictionOk(int param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint32_t local_20;
  
  if (*(int *)(param_2 + 4) == *(int *)(param_1 + 4)) {
    if (*(int *)(param_2 + 0xc) == *(int *)(param_1 + 0xc)) {
      if (*(int *)(param_2 + 0x10) == *(int *)(param_1 + 0x10)) {
        local_20 = 4;
        tmp_f1 = *(float *)(param_2 + 0x14) - *(float *)(param_1 + 0x14);
        tmp_f3 = *(float *)(param_2 + 0x18) - *(float *)(param_1 + 0x18);
        tmp_f2 = *(float *)(param_2 + 0x1c) - *(float *)(param_1 + 0x1c);
        if ((tmp_f2 * tmp_f2 + tmp_f3 * tmp_f3 + tmp_f1 * tmp_f1 <= 0.010000001) &&
           (local_20 = 5, tmp_f1 = *(float *)(param_2 + 0x20) - *(float *)(param_1 + 0x20),
           tmp_f2 = *(float *)(param_2 + 0x24) - *(float *)(param_1 + 0x24),
           tmp_f3 = *(float *)(param_2 + 0x28) - *(float *)(param_1 + 0x28),
           tmp_f3 * tmp_f3 + tmp_f2 * tmp_f2 + tmp_f1 * tmp_f1 <= 0.010000001)) {
          tmp_i6 = *(int *)(param_2 + 0x68);
          tmp_i4 = *(int *)(param_1 + 0x68);
          if (tmp_i6 == tmp_i4) {
            if (*(int *)(param_2 + 0x2c) == *(int *)(param_1 + 0x2c)) {
              local_20 = 8;
              if (*(int *)(param_2 + 0x50) == *(int *)(param_1 + 0x50)) {
                if (*(int *)(param_2 + 0x40) == *(int *)(param_1 + 0x40)) {
                  if (*(int *)(param_2 + 0x44) == *(int *)(param_1 + 0x44)) {
                    if (*(int *)(param_2 + 0x48) == *(int *)(param_1 + 0x48)) {
                      if (*(int *)(param_2 + 0x4c) == *(int *)(param_1 + 0x4c)) {
                        if (*(int *)(param_2 + 0x54) == *(int *)(param_1 + 0x54)) {
                          if (*(int *)(param_2 + 0x58) == *(int *)(param_1 + 0x58)) {
                            if (*(int *)(param_2 + 0x5c) == *(int *)(param_1 + 0x5c)) {
                              if (*(int *)(param_2 + 0x60) == *(int *)(param_1 + 0x60)) {
                                if (*(int *)(param_2 + 0x6c) == *(int *)(param_1 + 0x6c)) {
                                  tmp_i6 = 0;
                                  do {
                                    tmp_i4 = *(int *)(param_2 + 0x70 + tmp_i6 * 4);
                                    tmp_i5 = *(int *)(param_1 + 0x70 + tmp_i6 * 4);
                                    if (tmp_i4 != tmp_i5) {
                                      if (GHIDRA_FIELD(cg_showmiss, 12, 4) == 0) {
                                        return 0x12;
                                      }
                                      CG_Printf("events[%i] %i %i\n",tmp_i6,tmp_i4,tmp_i5);
                                      tmp_i4 = *(int *)(param_2 + (tmp_i6 + 0x20) * 4);
                                      tmp_i5 = *(int *)(param_1 + (tmp_i6 + 0x20) * 4);
                                      if (tmp_i4 == tmp_i5) {
                                        return 0x12;
                                      }
LAB_000ac261:
                                      if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                        CG_Printf("eventParm[%i] %i %i\n",tmp_i6,tmp_i4,tmp_i5);
                                      }
                                      return 0x12;
                                    }
                                    tmp_i4 = *(int *)(param_2 + 0x80 + tmp_i6 * 4);
                                    tmp_i5 = *(int *)(param_1 + 0x80 + tmp_i6 * 4);
                                    if (tmp_i4 != tmp_i5) goto LAB_000ac261;
                                    tmp_i6 = tmp_i6 + 1;
                                  } while (tmp_i6 != 4);
                                  if (*(int *)(param_2 + 0xa0) == *(int *)(param_1 + 0xa0)) {
                                    if (*(int *)(param_2 + 0xa4) == *(int *)(param_1 + 0xa4)) {
                                      if (*(int *)(param_2 + 0xa8) == *(int *)(param_1 + 0xa8)) {
                                        tmp_i6 = 0;
                                        do {
                                          if (1.0 < ABS(*(float *)(param_2 + 0xb0 + tmp_i6 * 4) -
                                                        *(float *)(param_1 + 0xb0 + tmp_i6 * 4))) {
                                            if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                              CG_Printf("viewangles[%i]\n",tmp_i6);
                                              return 0x16;
                                            }
                                            return 0x16;
                                          }
                                          tmp_i6 = tmp_i6 + 1;
                                        } while (tmp_i6 != 3);
                                        if (*(int *)(param_2 + 0xbc) == *(int *)(param_1 + 0xbc)) {
                                          if (*(int *)(param_2 + 0xc0) == *(int *)(param_1 + 0xc0))
                                          {
                                            if (*(int *)(param_2 + 0xc4) == *(int *)(param_1 + 0xc4)
                                               ) {
                                              if (*(int *)(param_2 + 200) == *(int *)(param_1 + 200)
                                                 ) {
                                                if (*(int *)(param_2 + 0xcc) ==
                                                    *(int *)(param_1 + 0xcc)) {
                                                  tmp_i6 = 0;
                                                  do {
                                                    if (*(int *)(param_2 + 0xd0 + tmp_i6 * 4) !=
                                                        *(int *)(param_1 + 0xd0 + tmp_i6 * 4)) {
                                                      if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                                        CG_Printf("stats[%i]\n",tmp_i6);
                                                        return 0x1c;
                                                      }
                                                      return 0x1c;
                                                    }
                                                    tmp_i6 = tmp_i6 + 1;
                                                  } while (tmp_i6 != 0x10);
                                                  tmp_i6 = 0;
                                                  do {
                                                    if (*(int *)(param_2 + 0x110 + tmp_i6 * 4) !=
                                                        *(int *)(param_1 + 0x110 + tmp_i6 * 4)) {
                                                      if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                                        CG_Printf("perstistant[%i]\n",tmp_i6);
                                                        return 0x1d;
                                                      }
                                                      return 0x1d;
                                                    }
                                                    tmp_i6 = tmp_i6 + 1;
                                                  } while (tmp_i6 != 0x10);
                                                  tmp_i6 = 0;
                                                  do {
                                                    if (*(int *)(param_2 + 0x150 + tmp_i6 * 4) !=
                                                        *(int *)(param_1 + 0x150 + tmp_i6 * 4)) {
                                                      if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                                        CG_Printf("powerups[%i]\n",tmp_i6);
                                                        return 0x1e;
                                                      }
                                                      return 0x1e;
                                                    }
                                                    tmp_i6 = tmp_i6 + 1;
                                                  } while (tmp_i6 != 0x10);
                                                  tmp_i6 = 0;
                                                  do {
                                                    if ((*(int *)(param_2 + 400 + tmp_i6 * 4) !=
                                                         *(int *)(param_1 + 400 + tmp_i6 * 4)) &&
                                                       (tmp_i6 != 1)) {
                                                      if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                                        CG_Printf("ammo[%i]\n",tmp_i6);
                                                      }
                                                      if (*(int *)(param_2 + (tmp_i6 + 0xa4) * 4) ==
                                                          *(int *)(param_1 + (tmp_i6 + 0xa4) * 4)) {
                                                        return 0x1f;
                                                      }
LAB_000ac54a:
                                                      if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                                        CG_Printf("ammoclip[%i]\n",tmp_i6);
                                                      }
                                                      return 0x1f;
                                                    }
                                                    if ((*(int *)(param_2 + 0x290 + tmp_i6 * 4) !=
                                                         *(int *)(param_1 + 0x290 + tmp_i6 * 4)) &&
                                                       (tmp_i6 != 1)) goto LAB_000ac54a;
                                                    tmp_i6 = tmp_i6 + 1;
                                                  } while (tmp_i6 != 0x40);
                                                  local_20 = 0x20;
                                                  if (((*(int *)(param_1 + 0x410) ==
                                                        *(int *)(param_2 + 0x410)) &&
                                                      (*(int *)(param_1 + 0x414) ==
                                                       *(int *)(param_2 + 0x414))) &&
                                                     (local_20 = 0x21,
                                                     *(int *)(param_1 + 0x424) ==
                                                     *(int *)(param_2 + 0x424))) {
                                                    if (*(int *)(param_1 + 0x34) ==
                                                        *(int *)(param_2 + 0x34)) {
                                                      local_20 = 0;
                                                    }
                                                    else {
                                                      local_20 = 0x22;
                                                      if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                                        CG_Printf("Backup: %d Server: %d\n",
                                                                  *(int *)(param_2 + 0x34),
                                                                  *(int *)(param_1 + 0x34));
                                                        local_20 = 0x22;
                                                      }
                                                    }
                                                  }
                                                }
                                                else {
                                                  local_20 = 0x1b;
                                                  if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                                    CG_Printf("damageCount\n");
                                                    local_20 = 0x1b;
                                                  }
                                                }
                                              }
                                              else {
                                                local_20 = 0x1a;
                                                if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                                  CG_Printf("damagePitch\n");
                                                  local_20 = 0x1a;
                                                }
                                              }
                                            }
                                            else {
                                              local_20 = 0x19;
                                              if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                                CG_Printf("damageYaw\n");
                                                local_20 = 0x19;
                                              }
                                            }
                                          }
                                          else {
                                            local_20 = 0x18;
                                            if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                              CG_Printf("damageEvent\n");
                                              local_20 = 0x18;
                                            }
                                          }
                                        }
                                        else {
                                          local_20 = 0x17;
                                          if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                            CG_Printf("viewheight\n");
                                            local_20 = 0x17;
                                          }
                                        }
                                      }
                                      else {
                                        local_20 = 0x15;
                                        if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                          CG_Printf("weaponstate\n");
                                          local_20 = 0x15;
                                        }
                                      }
                                    }
                                    else {
                                      local_20 = 0x14;
                                      if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                        CG_Printf("weapon\n");
                                        local_20 = 0x14;
                                      }
                                    }
                                  }
                                  else {
                                    local_20 = 0x13;
                                    if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                      CG_Printf("clientNum\n");
                                      local_20 = 0x13;
                                    }
                                  }
                                }
                                else {
                                  local_20 = 0x11;
                                  if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                    CG_Printf("eventSequence\n");
                                    local_20 = 0x11;
                                  }
                                }
                              }
                              else {
                                local_20 = 0x10;
                                if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                  CG_Printf("torsoAnim\n");
                                  local_20 = 0x10;
                                }
                              }
                            }
                            else {
                              local_20 = 0xf;
                              if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                                CG_Printf("torsoTimer\n");
                                local_20 = 0xf;
                              }
                            }
                          }
                          else {
                            local_20 = 0xe;
                            if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                              CG_Printf("legsAnim\n");
                              local_20 = 0xe;
                            }
                          }
                        }
                        else {
                          local_20 = 0xd;
                          if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                            CG_Printf("legsTimer\n");
                            local_20 = 0xd;
                          }
                        }
                      }
                      else {
                        local_20 = 0xc;
                        if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                          CG_Printf("delta_angles[2]\n");
                          local_20 = 0xc;
                        }
                      }
                    }
                    else {
                      local_20 = 0xb;
                      if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                        CG_Printf("delta_angles[1]\n");
                        local_20 = 0xb;
                      }
                    }
                  }
                  else {
                    local_20 = 10;
                    if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                      CG_Printf("delta_angles[0]\n");
                      local_20 = 10;
                    }
                  }
                }
                else {
                  local_20 = 9;
                  if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                    CG_Printf("speed\n");
                    local_20 = 9;
                  }
                }
              }
            }
            else {
              local_20 = 7;
              if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                CG_Printf("weaponTime\nBackup: %d Server: %d\n",*(int *)(param_2 + 0x2c),
                          *(int *)(param_1 + 0x2c));
                local_20 = 7;
              }
            }
          }
          else {
            local_20 = 6;
            if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
              CG_Printf("eFlags\nBackup: %x  Server: %x Diff: %x\n",tmp_i6,tmp_i4,tmp_i6 - tmp_i4);
              local_20 = 6;
            }
          }
        }
      }
      else {
        local_20 = 3;
        if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
          CG_Printf("pm_time\n");
          local_20 = 3;
        }
      }
    }
    else {
      local_20 = 2;
      if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
        CG_Printf("pm_flags\n");
        local_20 = 2;
      }
    }
  }
  else {
    local_20 = 1;
    if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
      local_20 = 1;
      CG_Printf("pm_type\n");
    }
  }
  return local_20;
}

void CG_PredictPlayerState(void)
{
  int tmp_i1;
  int tmp_i2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  bool tmp_b6;
  double tmp_d7;
  uint tmp_u8;
  uint tmp_u9;
  uint8_t *tmp_pu10;
  uint32_t tmp_u11;
  char *tmp_pc12;
  int tmp_i13;
  int tmp_i14;
  int *tmp_pi15;
  uint32_t *tmp_pu16;
  uint32_t *tmp_pu17;
  int *tmp_pi18;
  uint32_t *tmp_pu19;
  byte tmp_b20;
  long double tmp_l21;
  double tmp_d22;
  float *pfVar23;
  float *pfVar24;
  uint local_724;
  int local_70c;
  uint local_708;
  int local_6f4;
  uint local_6e8;
  int local_6e4;
  int local_6e0;
  uint8_t local_6cc [4];
  float local_6c8;
  float local_6c0;
  float local_6bc;
  float local_6b8;
  float local_6b4;
  float local_6b0;
  float local_6ac;
  float local_6a8;
  float local_6a4;
  float local_6a0;
  float local_69c;
  float local_698;
  float local_694;
  int local_690 [7];
  int local_674 [7];
  int local_658 [41];
  float local_5b4;
  float local_5b0;
  float local_5ac;
  uint32_t uStack_14;
  
  tmp_b20 = 0;
  uStack_14 = 0xac6db;
  g_unk_010906f8 = 0;
  if (g_unk_010917a0 == 0) {
    g_unk_010917a0 = 1;
    g_unk_010906fc = *(uint32_t *)(g_unk_01047b00 + 0x2c);
    tmp_pu17 = (uint32_t *)(g_unk_01047b00 + 0x30);
    tmp_pu16 = &g_unk_01090700;
    for (tmp_i13 = 0x16a; tmp_i13 != 0; tmp_i13 = tmp_i13 + -1) {
      *tmp_pu16 = *tmp_pu17;
      tmp_pu17 = tmp_pu17 + 1;
      tmp_pu16 = tmp_pu16 + 1;
    }
  }
  if ((g_unk_01047aec != 0) || ((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) != 0)) {
    CG_InterpolatePlayerState();
    return;
  }
  if ((GHIDRA_FIELD(cg_nopredict, 12, 4) != 0) || (g_unk_01090700 == 5)) {
    cg_pmove = &g_unk_010906fc;
    g_unk_00e9a624 = &g_unk_010b1668;
    g_unk_010b167c = g_unk_010b5e40 - g_unk_010906e0;
    if ((g_unk_01090764 & 0x20) != 0) {
      tmp_i13 = g_unk_01090b10 * 0xaf8;
      g_unk_010b1684 = *(uint32_t *)(cg_entities + tmp_i13 + 0x68);
      g_unk_010b1680 = *(uint32_t *)(cg_entities + tmp_i13 + 0x6c);
      g_unk_010b1688 = *(float *)(cg_entities + tmp_i13 + 0x80);
      g_unk_010b168c = *(float *)(cg_entities + tmp_i13 + 0x84);
      g_unk_010b1690 = *(float *)(cg_entities + tmp_i13 + 0x88);
      tmp_l21 = (long double)AngleNormalize180(g_unk_010b1688);
      g_unk_010b1688 = (float)tmp_l21;
      tmp_l21 = (long double)AngleNormalize180(g_unk_010b168c);
      g_unk_010b168c = (float)tmp_l21;
      tmp_l21 = (long double)AngleNormalize180(g_unk_010b1690);
      g_unk_010b1690 = (float)tmp_l21;
    }
    CG_InterpolatePlayerState();
    return;
  }
  if ((cg_pmove != (uint32_t *)0x0) && ((*(byte *)((int)cg_pmove + 0x69) & 0x80) != 0)) {
    g_unk_010b168c = *(float *)(cg_entities +
                             *(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xab4) *
                             0xaf8 + 0x7a4);
    g_unk_010b1688 = *(float *)(cg_entities +
                             *(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xab4) *
                             0xaf8 + 0x7a0);
  }
  cg_pmove = &g_unk_010906fc;
  g_unk_00e9a624 = local_658;
  g_unk_00e9a628 = CG_CharacterForClientinfo
                           (*(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x10f926c,
                            cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8);
  g_unk_010b167c = g_unk_010b5e40 - g_unk_010906e0;
  if ((cg_pmove[0x1a] & 0x20) == 0) {
    if ((cg_pmove[0x1a] & 0x8000) != 0) {
      g_unk_010b1688 = *(float *)(cg_entities +
                               *(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xab4)
                               * 0xaf8 + 0x7a0);
    }
  }
  else {
    g_unk_010b1684 = *(uint32_t *)(cg_entities + cg_pmove[0x105] * 0xaf8 + 0x68);
    g_unk_010b1680 = *(uint32_t *)(cg_entities + cg_pmove[0x105] * 0xaf8 + 0x6c);
    g_unk_010b1688 = *(float *)(cg_entities + cg_pmove[0x105] * 0xaf8 + 0x80);
    g_unk_010b168c = *(float *)(cg_entities + cg_pmove[0x105] * 0xaf8 + 0x84);
    g_unk_010b1690 = *(float *)(cg_entities + cg_pmove[0x105] * 0xaf8 + 0x88);
    tmp_l21 = (long double)AngleNormalize180(g_unk_010b1688);
    g_unk_010b1688 = (float)tmp_l21;
    tmp_l21 = (long double)AngleNormalize180(g_unk_010b168c);
    g_unk_010b168c = (float)tmp_l21;
    tmp_l21 = (long double)AngleNormalize180(g_unk_010b1690);
    g_unk_010b1690 = (float)tmp_l21;
  }
  tmp_i13 = g_unk_01047b00;
  g_unk_00e9a72c = *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x10f9344;
  g_unk_00e9a744 = *(uint32_t *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x958c);
  g_unk_00e9a748 = *(uint32_t *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9590);
  g_unk_00e9a74c = *(uint32_t *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9594);
  g_unk_00e9a750 = *(uint32_t *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9598);
  g_unk_00e9a754 = *(uint32_t *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x959c);
  g_unk_00e9a758 = *(uint32_t *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x95a0);
  g_unk_00e9a75c = *(uint32_t *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x95a4);
  g_unk_00e9a738 = CG_TraceCapsule;
  g_unk_00e9a73c = CG_PointContents;
  if (cg_pmove[1] == 3) {
    g_unk_00e9a664 = 0x10001;
    cg_pmove[0x1a] = cg_pmove[0x1a] | 1;
  }
  else if (cg_pmove[1] == 2) {
    g_unk_00e9a664 = 0x10001;
    g_unk_00e9a738 = CG_TraceCapsule_World;
  }
  else {
    g_unk_00e9a664 = 0x2010001;
  }
  if ((*(int *)(tmp_i13 + 0x158) == 3) || ((*(byte *)(tmp_i13 + 0x39) & 0x40) != 0)) {
    g_unk_00e9a664 = 0x10001;
  }
  tmp_pi15 = &g_unk_010906fc;
  tmp_pi18 = local_658 + 0x24;
  for (tmp_i13 = 0x16b; tmp_i13 != 0; tmp_i13 = tmp_i13 + -1) {
    *tmp_pi18 = *tmp_pi15;
    tmp_pi15 = tmp_pi15 + (uint)tmp_b20 * -2 + 1;
    tmp_pi18 = tmp_pi18 + (uint)tmp_b20 * -2 + 1;
  }
  tmp_u8 = trap_GetCurrentCmdNumber();
  tmp_u9 = 0;
  tmp_i13 = (tmp_u8 & 0x3f) * 0x90;
  do {
    tmp_u11 = *(uint32_t *)((int)&g_unk_010b166c + tmp_u9);
    *(uint32_t *)(oldpmext + tmp_u9 + tmp_i13) = *(uint32_t *)((int)&g_unk_010b1668 + tmp_u9);
    *(uint32_t *)(tmp_i13 + 0x3b81ba4 + tmp_u9) = tmp_u11;
    tmp_u9 = tmp_u9 + 8;
  } while (tmp_u9 < 0x90);
  local_708 = tmp_u8 - 0x3f;
  trap_GetUserCmd(local_708,local_690);
  if (((*(int *)(g_unk_01047b00 + 0x2c) < local_690[0]) && (local_690[0] < (int)g_unk_010906e0)) &&
     (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0)) {
    CG_Printf("exceeded PACKET_BACKUP on commands\n");
  }
  trap_GetUserCmd(tmp_u8,local_674);
  tmp_i13 = g_unk_01047b00;
  g_unk_010906fc = *(int *)(g_unk_01047b00 + 0x2c);
  tmp_pu17 = (uint32_t *)(g_unk_01047b00 + 0x30);
  tmp_pu16 = &g_unk_01090700;
  for (tmp_i14 = 0x16a; tmp_i14 != 0; tmp_i14 = tmp_i14 + -1) {
    *tmp_pu16 = *tmp_pu17;
    tmp_pu17 = tmp_pu17 + (uint)tmp_b20 * -2 + 1;
    tmp_pu16 = tmp_pu16 + (uint)tmp_b20 * -2 + 1;
  }
  g_unk_010906e8 = *(int *)(tmp_i13 + 8);
  if ((int)GHIDRA_FIELD(pmove_msec, 12, 4) < 8) {
    tmp_pc12 = "8";
LAB_000ad56d:
    trap_Cvar_Set("pmove_msec",tmp_pc12);
  }
  else if (0x21 < (int)GHIDRA_FIELD(pmove_msec, 12, 4)) {
    tmp_pc12 = "33";
    goto LAB_000ad56d;
  }
  g_unk_00e9a734 = GHIDRA_FIELD(pmove_msec, 12, 4);
  g_unk_00e9a730 = GHIDRA_FIELD(pmove_fixed, 12, 4);
  if (GHIDRA_FIELD(cg_optimizePrediction, 12, 4) == 0) {
    local_6e8 = 0;
    local_6f4 = 0;
  }
  else {
    local_6f4 = g_unk_010aabc8;
    local_6e8 = local_708;
    if ((g_unk_010906d8 == 0) && (g_unk_010906d4 == 0)) {
      if (g_unk_010906e8 == g_unk_0109356c) {
        local_6e8 = g_unk_01093568 + 1;
        g_unk_0109356c = g_unk_010906e8;
      }
      else {
        local_6f4 = g_unk_010aabcc;
        if (g_unk_010aabc8 != g_unk_010aabcc) {
          tmp_i13 = *(int *)(&g_unk_01093570 + g_unk_010aabc8 * 0x5ac);
          tmp_i14 = g_unk_010aabc8;
          while (tmp_i13 != g_unk_010906fc) {
            tmp_i14 = (tmp_i14 + 1) % 0x42;
            local_6f4 = g_unk_010aabc8;
            if (tmp_i14 == g_unk_010aabcc) goto LAB_000acb0f;
            tmp_i13 = *(int *)(&g_unk_01093570 + tmp_i14 * 0x5ac);
          }
          tmp_pu17 = (uint32_t *)(&g_unk_01093570 + tmp_i14 * 0x5ac);
          tmp_i13 = CG_PredictionOk(&g_unk_010906fc,tmp_pu17);
          if (tmp_i13 == 0) {
            tmp_u9 = 0x5ac;
            tmp_pu16 = cg_pmove;
            if (((uint)cg_pmove & 4) != 0) {
              tmp_u11 = *tmp_pu17;
              tmp_pu16 = cg_pmove + 1;
              tmp_pu17 = (uint32_t *)(&g_unk_01093574 + tmp_i14 * 0x5ac);
              tmp_u9 = 0x5a8;
              *cg_pmove = tmp_u11;
            }
            for (tmp_u9 = tmp_u9 >> 2; tmp_u9 != 0; tmp_u9 = tmp_u9 - 1) {
              *tmp_pu16 = *tmp_pu17;
              tmp_pu17 = tmp_pu17 + (uint)tmp_b20 * -2 + 1;
              tmp_pu16 = tmp_pu16 + (uint)tmp_b20 * -2 + 1;
            }
            local_6f4 = (tmp_i14 + 1) % 0x42;
            local_6e8 = g_unk_01093568 + 1;
            g_unk_0109356c = g_unk_010906e8;
            g_unk_010aabc8 = local_6f4;
            goto LAB_000acb2f;
          }
          local_6f4 = g_unk_010aabc8;
          if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
            CG_Printf("errorcode %d at %d\n",tmp_i13,g_unk_010906e0);
            local_6f4 = g_unk_010aabc8;
          }
        }
LAB_000acb0f:
        g_unk_01093568 = 0;
        g_unk_0109356c = g_unk_010906e8;
        g_unk_010aabcc = local_6f4;
      }
    }
    else {
      g_unk_01093568 = 0;
      g_unk_010aabcc = g_unk_010aabc8;
      g_unk_0109356c = g_unk_010906e8;
    }
  }
LAB_000acb2f:
  tmp_b6 = false;
  local_6e0 = 0;
  local_6e4 = 0;
  do {
    trap_GetUserCmd(local_708,&g_unk_00e9a62c);
    tmp_pu10 = &g_unk_00e9a648;
    trap_GetUserCmd(local_708 - 1,&g_unk_00e9a648);
    tmp_d7 = (double)ZEXT48(tmp_pu10);
    tmp_d22 = (double)ZEXT48(tmp_pu10);
    if ((g_unk_010906fc < (int)g_unk_00e9a62c) && ((int)g_unk_00e9a62c <= local_674[0])) {
      if (g_unk_010906fc == local_658[0x24]) {
        if ((cg_pmove[0x1a] & 0x8020) == 0) {
          if (g_unk_010906d4 == 0) {
            tmp_d22 = tmp_d7;
            if (g_unk_010abd78 == 0) {
              pfVar23 = &local_69c;
              pfVar24 = g_unk_0109074c;
              CG_AdjustPositionForMover
                        (&g_unk_01090710,g_unk_0109074c,g_unk_010906e8,g_unk_010906e4,pfVar23,local_6cc);
              if (((g_unk_01090766 & 8) != 0) || (g_unk_01091814 == 0x2a)) {
                g_unk_01090744 = g_unk_01090744 + ((int)ROUND((local_6c8 * 65536.0) / 360.0) & 0xffffU);
              }
              if ((GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) &&
                 (tmp_i13 = VectorCompare(&local_5b4,pfVar23), pfVar24 = pfVar23, tmp_i13 == 0)) {
                CG_Printf("prediction error\n");
                pfVar24 = pfVar23;
              }
              local_6a8 = local_5b4 - local_69c;
              local_6a4 = local_5b0 - local_698;
              local_6a0 = local_5ac - local_694;
              tmp_l21 = (long double)VectorLength(&local_6a8);
              tmp_d22 = (double)ZEXT48(pfVar24);
              if ((long double)0.1 < tmp_l21) {
                if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
                  tmp_d22 = (double)tmp_l21;
                  CG_Printf("Prediction miss: %f\n",tmp_d22);
                }
                if (GHIDRA_FIELD(cg_errorDecay, 12, 4) == 0) {
                  tmp_f5 = 0.0;
                  tmp_f3 = 0.0;
                  tmp_f4 = tmp_f5;
                }
                else {
                  tmp_f4 = (float)GHIDRA_FIELD(cg_errorDecay, 8, 4);
                  if (500.0 < (float)GHIDRA_FIELD(cg_errorDecay, 8, 4)) {
                    tmp_f4 = 500.0;
                  }
                  tmp_f4 = (tmp_f4 - (float)(int)(g_unk_010906e0 - g_unk_010917a4)) / tmp_f4;
                  if (tmp_f4 < 0.0) {
                    tmp_f4 = 0.0;
                  }
                  else if ((0.0 < tmp_f4) && (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0)) {
                    tmp_d22 = (double)tmp_f4;
                    CG_Printf("Double prediction decay: %f\n",tmp_d22);
                  }
                  tmp_f5 = g_unk_010917a8 * tmp_f4;
                  tmp_f3 = tmp_f4 * g_unk_010917b0;
                  tmp_f4 = g_unk_010917ac * tmp_f4;
                }
                g_unk_010917a4 = g_unk_010906e4;
                g_unk_010917a8 = tmp_f5 + local_6a8;
                g_unk_010917ac = tmp_f4 + local_6a4;
                g_unk_010917b0 = tmp_f3 + local_6a0;
              }
            }
          }
          else {
            g_unk_010917b0 = 0.0;
            g_unk_010917ac = 0.0;
            g_unk_010917a8 = 0.0;
            if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
              CG_Printf("PredictionTeleport\n");
            }
            g_unk_010906d4 = 0;
            tmp_d22 = (double)ZEXT48(tmp_pu10);
          }
        }
        else {
          g_unk_010917b0 = 0.0;
          g_unk_010917ac = 0.0;
          g_unk_010917a8 = 0.0;
          tmp_d22 = (double)ZEXT48(tmp_pu10);
        }
      }
      if (g_unk_00e9a730 != 0) {
        g_unk_00e9a62c = ((int)(g_unk_00e9a62c + GHIDRA_FIELD(pmove_msec, 12, 4) + -1) / (int)GHIDRA_FIELD(pmove_msec, 12, 4)) *
                       GHIDRA_FIELD(pmove_msec, 12, 4);
      }
      if (g_unk_010b4558 != 0) {
        cg_pmove[1] = 4;
      }
      g_unk_00e9a66c = GHIDRA_FIELD(cgs, 27388, 4);
      tmp_i13 = *(int *)(g_unk_01047b00 + 0x158);
      if (tmp_i13 - 1U < 2) {
        g_unk_00e9a670 = *(uint32_t *)(&g_unk_010b3af8 + tmp_i13 * 4);
        g_unk_00e9a674 = (&g_unk_01047ac4)[(int)(&g_unk_0001b00f + tmp_i13)];
        g_unk_00e9a678 = (&g_unk_01047acc)[(int)(&g_unk_0001b00f + tmp_i13)];
        g_unk_00e9a67c = (&g_unk_01047ac4)[tmp_i13 + 0x1b013];
        g_unk_00e9a680 = (&g_unk_01047acc)[tmp_i13 + 0x1b013];
      }
      tmp_u9 = 0;
      tmp_i13 = (local_708 & 0x3f) * 0x90;
      do {
        tmp_u11 = *(uint32_t *)(tmp_i13 + 0x3b81ba4 + tmp_u9);
        *(uint32_t *)((int)local_658 + tmp_u9) = *(uint32_t *)(oldpmext + tmp_u9 + tmp_i13);
        *(uint32_t *)((int)local_658 + tmp_u9 + 4) = tmp_u11;
        tmp_u9 = tmp_u9 + 8;
      } while (tmp_u9 < 0x90);
      fflush(_stdout);
      if (GHIDRA_FIELD(cg_optimizePrediction, 12, 4) == 0) {
        Pmove(&cg_pmove);
        local_6e4 = local_6e4 + 1;
      }
      else if (((int)local_708 < (int)local_6e8) &&
              (tmp_i13 = (local_6f4 + 1) % 0x42, tmp_i13 != g_unk_010aabc8)) {
        local_6e0 = local_6e0 + 1;
        if ((GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) &&
           (*(uint *)(&g_unk_01093570 + local_6f4 * 0x5ac) != g_unk_00e9a62c)) {
          CG_Printf("saved state miss\n");
        }
        local_724 = 0x5ac;
        tmp_pu17 = (uint32_t *)(&g_unk_01093570 + local_6f4 * 0x5ac);
        tmp_pu16 = cg_pmove;
        if (((uint)cg_pmove & 4) != 0) {
          tmp_u11 = *tmp_pu17;
          tmp_pu16 = cg_pmove + 1;
          tmp_pu17 = (uint32_t *)(&g_unk_01093574 + local_6f4 * 0x5ac);
          *cg_pmove = tmp_u11;
          local_724 = 0x5a8;
        }
        for (local_724 = local_724 >> 2; local_6f4 = tmp_i13, local_724 != 0;
            local_724 = local_724 - 1) {
          *tmp_pu16 = *tmp_pu17;
          tmp_pu17 = tmp_pu17 + (uint)tmp_b20 * -2 + 1;
          tmp_pu16 = tmp_pu16 + (uint)tmp_b20 * -2 + 1;
        }
      }
      else {
        tmp_i13 = (local_6f4 + 1) % 0x42;
        Pmove(&cg_pmove);
        local_6e4 = local_6e4 + 1;
        g_unk_01093568 = local_708;
        if (g_unk_010aabc8 != tmp_i13) {
          local_724 = 0x5ac;
          tmp_pu17 = (uint32_t *)(&g_unk_01093570 + local_6f4 * 0x5ac);
          tmp_pu16 = cg_pmove;
          tmp_pu19 = tmp_pu17;
          if (((uint)tmp_pu17 & 4) != 0) {
            tmp_pu19 = (uint32_t *)(&g_unk_01093574 + local_6f4 * 0x5ac);
            tmp_pu16 = cg_pmove + 1;
            *tmp_pu17 = *cg_pmove;
            local_724 = 0x5a8;
          }
          for (local_724 = local_724 >> 2; local_6f4 = tmp_i13, g_unk_010aabcc = tmp_i13, local_724 != 0
              ; local_724 = local_724 - 1) {
            *tmp_pu19 = *tmp_pu16;
            tmp_pu16 = tmp_pu16 + (uint)tmp_b20 * -2 + 1;
            tmp_pu19 = tmp_pu19 + (uint)tmp_b20 * -2 + 1;
          }
        }
      }
      if (0 < g_unk_010907cc) {
        if ((g_unk_01090700 == 2) || ((g_unk_01090709 & 0x40) != 0)) {
          tmp_b6 = false;
        }
        else {
          tmp_b6 = true;
          tmp_d7 = tmp_d22;
          if (g_unk_01090700 != 0) goto LAB_000acfa5;
          tmp_b6 = true;
        }
        if (0 < cg_numTriggerEntities) {
          tmp_i14 = 0;
          local_70c = 0;
          tmp_i13 = cg_numTriggerEntities;
          do {
            while( true ) {
              tmp_i1 = (&cg_triggerEntities)[tmp_i14];
              tmp_i2 = *(int *)(tmp_i1 + 4);
              if (((((tmp_i2 != 2) || (!tmp_b6)) || (g_unk_0109074c != (float *)0x3fe)) &&
                  (((*(byte *)(tmp_i1 + 10) & 1) != 0 ||
                   ((*(int *)(tmp_i1 + 0xb4) == 0xffffff &&
                    (local_70c = *(int *)(cgs + *(int *)(tmp_i1 + 0xa4) * 4 + 0x840c), local_70c != 0
                    )))))) &&
                 ((tmp_i2 == 0xc || ((tmp_i2 == 0x20 && (*(int *)(tmp_i1 + 0x118) == 0)))))) break;
              tmp_i14 = tmp_i14 + 1;
              if (tmp_i13 <= tmp_i14) goto LAB_000acfa0;
            }
            trap_R_ModelBounds(local_70c,&local_6c0,&local_6b4);
            local_6c0 = (*(float *)(tmp_i1 + 0x794) + local_6c0) - 48.0;
            local_6bc = (*(float *)(tmp_i1 + 0x798) + local_6bc) - 48.0;
            local_6b8 = (*(float *)(tmp_i1 + 0x79c) + local_6b8) - 48.0;
            local_6b4 = *(float *)(tmp_i1 + 0x794) + local_6b4 + 48.0;
            local_6b0 = *(float *)(tmp_i1 + 0x798) + local_6b0 + 48.0;
            local_6ac = *(float *)(tmp_i1 + 0x79c) + local_6ac + 48.0;
            local_6a8 = g_unk_01090710 + g_unk_00e9a708;
            local_6a4 = g_unk_01090714 + g_unk_00e9a70c;
            local_6a0 = g_unk_01090718 + g_unk_00e9a710;
            local_69c = g_unk_01090710 + g_unk_00e9a714;
            local_698 = g_unk_01090714 + g_unk_00e9a718;
            local_694 = g_unk_01090718 + g_unk_00e9a71c;
            pfVar23 = &local_69c;
            tmp_i13 = BG_BBoxCollision(&local_6a8,pfVar23,&local_6c0,&local_6b4);
            if (tmp_i13 != 0) {
              if (*(int *)(tmp_i1 + 4) == 0xc) {
                tmp_i13 = *(int *)(tmp_i1 + 0x108);
              }
              else {
                if (*(int *)(tmp_i1 + 4) != 0x20) goto LAB_000acf7e;
                tmp_i13 = *(int *)(tmp_i1 + 0x90);
              }
              tmp_u11 = nitrox_ConfigString(tmp_i13 + 0x261);
              pfVar23 = (float *)&g_unk_0010d2bf;
              tmp_i13 = Info_ValueForKey(tmp_u11,&g_unk_0010d2bf);
              if (tmp_i13 != 0) {
                tmp_u11 = va("You are near the %s\n",tmp_i13);
                pfVar23 = (float *)&g_unk_00000008;
                CG_ObjectivePrint(tmp_u11,8);
              }
            }
LAB_000acf7e:
            tmp_d22 = (double)ZEXT48(pfVar23);
            tmp_i14 = tmp_i14 + 1;
            tmp_i13 = cg_numTriggerEntities;
          } while (tmp_i14 < cg_numTriggerEntities);
        }
      }
LAB_000acfa0:
      tmp_b6 = true;
      tmp_d7 = tmp_d22;
    }
LAB_000acfa5:
    local_708 = local_708 + 1;
    if ((int)tmp_u8 < (int)local_708) {
      if ((GHIDRA_FIELD(cg_showmiss, 12, 4) & 2) != 0) {
        tmp_u8 = g_unk_010906e0;
        CG_Printf("cg.time: %d, numPredicted: %d, numPlayedBack: %d\n",g_unk_010906e0,local_6e4,
                  local_6e0);
        tmp_d7 = (double)(ulonglong)tmp_u8;
      }
      if ((GHIDRA_FIELD(cg_showmiss, 12, 4) & 4) != 0) {
        tmp_u8 = g_unk_00e9a62c;
        CG_Printf("[%i : %i] ",g_unk_00e9a62c,g_unk_010906e0);
        tmp_d7 = (double)(ulonglong)tmp_u8;
      }
      if (tmp_b6) {
        tmp_u8 = 0;
        do {
          tmp_u11 = *(uint32_t *)((int)local_658 + tmp_u8 + 4);
          *(uint32_t *)((int)&g_unk_010b1668 + tmp_u8) = *(uint32_t *)((int)local_658 + tmp_u8);
          *(uint32_t *)((int)&g_unk_010b166c + tmp_u8) = tmp_u11;
          tmp_u8 = tmp_u8 + 8;
        } while (tmp_u8 < 0x90);
        if (g_unk_010abd78 == 0) {
          CG_AdjustPositionForMover
                    (&g_unk_01090710,g_unk_0109074c,g_unk_010906e8,g_unk_010906e0,&g_unk_01090710,local_6cc);
        }
        CG_TransitionPlayerState(&g_unk_010906fc,local_658 + 0x24);
        tmp_f5 = g_unk_010ab338;
        if (g_unk_010ab334 < (int)g_unk_010906e0) {
          g_unk_010ab33c = 0.0;
          g_unk_010ab340 = 0.0;
          g_unk_010ab338 = 0.0;
          g_unk_010ab334 = 0;
        }
        else {
          tmp_i13 = g_unk_010ab334 - g_unk_010906e0;
          tmp_d22 = sin((double)(g_unk_010ab338 + 326.72565));
          tmp_f4 = g_unk_010ab33c;
          tmp_f3 = (float)tmp_i13 / g_unk_010ab340;
          g_unk_01090718 = g_unk_010ab33c * (float)tmp_d22 * tmp_f3 * 6.0 + g_unk_01090718;
          tmp_d22 = sin((double)(tmp_f3 * 53.407074 + tmp_f5));
          g_unk_01090714 = (float)tmp_d22 * tmp_f3 * 6.0 * tmp_f4 + g_unk_01090714;
          tmp_d22 = cos((double)(tmp_f3 * 21.991148 + tmp_f5));
          g_unk_01090710 = (float)tmp_d22 * tmp_f3 * 6.0 * tmp_f4 + g_unk_01090710;
        }
      }
      else if (GHIDRA_FIELD(cg_showmiss, 12, 4) != 0) {
        CG_Printf("not moved\n",SUB84(tmp_d7,0));
      }
      return;
    }
  } while( true );
}

void CG_TransitionEntity(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint tmp_u6;
  long double tmp_l7;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_i5 = CG_EntOnFire(param_1);
  if (tmp_i5 != 0) {
    BG_EvaluateTrajectory
              (param_1 + 300,*(uint32_t *)(g_unk_01047b00 + 8),&local_24,0,
               *(uint32_t *)(param_1 + 0x110));
    BG_EvaluateTrajectory
              (param_1 + 0xc,*(uint32_t *)(g_unk_01047b00 + 8),&local_18,0,
               *(uint32_t *)(param_1 + 0x110));
    local_30 = local_18 - local_24;
    local_2c = local_14 - local_20;
    local_28 = (local_10 - local_1c) + 2.0;
    tmp_l7 = (long double)VectorNormalize(&local_30);
    if (tmp_l7 < (long double)1) {
      tmp_f3 = 0.0;
      local_28 = 1.0;
      local_2c = 0.0;
      local_30 = 0.0;
      tmp_f1 = 0.3;
      tmp_f4 = tmp_f3;
    }
    else {
      tmp_f3 = local_2c * 0.3;
      tmp_f1 = local_28 * 0.3;
      tmp_f4 = local_30 * 0.3;
    }
    *(float *)(param_1 + 2000) = tmp_f4 + *(float *)(param_1 + 2000);
    *(float *)(param_1 + 0x7d4) = tmp_f3 + *(float *)(param_1 + 0x7d4);
    *(float *)(param_1 + 0x7d8) = tmp_f1 + *(float *)(param_1 + 0x7d8);
    tmp_l7 = (long double)VectorNormalize(param_1 + 2000);
    if (tmp_l7 <= (long double)0.1) {
      *(float *)(param_1 + 2000) = local_30;
      *(float *)(param_1 + 0x7d4) = local_2c;
      *(float *)(param_1 + 0x7d8) = local_28;
    }
  }
  tmp_u6 = 0;
  do {
    *(uint32_t *)(param_1 + tmp_u6) = *(uint32_t *)(param_1 + 0x120 + tmp_u6);
    *(uint32_t *)(param_1 + 4 + tmp_u6) = *(uint32_t *)(param_1 + 0x124 + tmp_u6);
    tmp_u6 = tmp_u6 + 8;
  } while (tmp_u6 < 0x120);
  *(uint32_t *)(param_1 + 0x244) = 1;
  if (*(int *)(param_1 + 0x240) == 0) {
    *(uint32_t *)(param_1 + 0x250) = 0;
    *(uint32_t *)(param_1 + 0x254) = *(uint32_t *)(param_1 + 0xc0);
    tmp_u2 = *(uint32_t *)(g_unk_01047b00 + 8);
    *(uint32_t *)(param_1 + 0x794) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x7c4) = 0;
    *(uint32_t *)(param_1 + 0x798) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x25c) = tmp_u2;
    *(uint32_t *)(param_1 + 0x79c) = *(uint32_t *)(param_1 + 100);
    *(uint32_t *)(param_1 + 0x7c8) = 0;
    *(uint32_t *)(param_1 + 0x7a0) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x7a4) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x7a8) = *(uint32_t *)(param_1 + 0x7c);
    if (*(int *)(param_1 + 4) == 1) {
      CG_ResetPlayerEntity(param_1);
    }
    *(uint32_t *)(param_1 + 0x264) = 0;
    *(uint32_t *)(param_1 + 0x7dc) = 0;
    *(uint32_t *)(param_1 + 0x994) = 0;
    *(uint32_t *)(param_1 + 0x998) = 0;
    *(uint32_t *)(param_1 + 0x9b4) = 0;
    *(uint32_t *)(param_1 + 0x248) = 0;
    *(uint32_t *)(param_1 + 0x24c) = 0;
    *(uint32_t *)(param_1 + 0x260) = 0;
    *(uint32_t *)(param_1 + 0x784) = 0;
    *(uint32_t *)(param_1 + 0x780) = 0;
    *(uint32_t *)(param_1 + 0x77c) = 0;
    *(uint32_t *)(param_1 + 0x790) = 0;
    *(uint32_t *)(param_1 + 0x78c) = 0;
    *(uint32_t *)(param_1 + 0x788) = 0;
    *(uint32_t *)(param_1 + 0xab0) = 0;
  }
  *(uint32_t *)(param_1 + 0x240) = 0;
  CG_CheckEvents(param_1);
  return;
}

void CG_Tracer(float *param_1,float *param_2,int param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  long double tmp_l5;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_18 = *param_2 - *param_1;
  local_14 = param_2[1] - param_1[1];
  local_10 = param_2[2] - param_1[2];
  tmp_l5 = (long double)VectorNormalize(&local_18);
  if ((tmp_l5 < (long double)100.0) && (param_3 == 0)) {
    return;
  }
  tmp_f1 = (float)tmp_l5;
  tmp_u4 = rand();
  tmp_f2 = (tmp_f1 - 60.0) * ((float)(tmp_u4 & 0x7fff) / 32767.0) + 50.0;
  tmp_f3 = (float)GHIDRA_FIELD(cg_tracerLength, 8, 4) + tmp_f2;
  if (tmp_f1 < (float)GHIDRA_FIELD(cg_tracerLength, 8, 4) + tmp_f2) {
    tmp_f3 = tmp_f1;
  }
  local_30 = local_18 * tmp_f2 + *param_1;
  local_2c = local_14 * tmp_f2 + param_1[1];
  local_28 = tmp_f2 * local_10 + param_1[2];
  local_24 = local_18 * tmp_f3 + *param_1;
  local_20 = local_14 * tmp_f3 + param_1[1];
  local_1c = tmp_f3 * local_10 + param_1[2];
  CG_DrawTracer(&local_30,&local_24);
  return;
}

