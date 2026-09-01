/* Vector, angle and geometry helpers — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_math.h"

void SnapVectorTowards(float *param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  
  tmp_f1 = *param_1;
  tmp_f2 = floorf(tmp_f1);
  tmp_f3 = ceilf(tmp_f1);
  if (tmp_f1 < *param_2) {
    tmp_f2 = tmp_f3;
  }
  *param_1 = tmp_f2;
  tmp_f1 = param_1[1];
  tmp_f2 = floorf(tmp_f1);
  tmp_f3 = ceilf(tmp_f1);
  if (tmp_f1 < param_2[1]) {
    tmp_f2 = tmp_f3;
  }
  param_1[1] = tmp_f2;
  tmp_f1 = param_1[2];
  tmp_f2 = floorf(tmp_f1);
  tmp_f3 = ceilf(tmp_f1);
  if (tmp_f1 < param_2[2]) {
    tmp_f2 = tmp_f3;
  }
  param_1[2] = tmp_f2;
  return;
}

void CG_Bullet(float *param_1,int param_2,uint32_t param_3,int param_4,int param_5,int param_6,
              float param_7)

{
  bool tmp_b1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint tmp_u4;
  uint tmp_u5;
  int tmp_i6;
  long double tmp_l7;
  long double tmp_l8;
  long double tmp_l9;
  float tmp_f10;
  float tmp_f11;
  float tmp_f12;
  float tmp_f13;
  double tmp_d14;
  uint local_f4;
  float *local_e4;
  int local_d8;
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
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  uint32_t local_58;
  uint8_t local_54 [8];
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  uint8_t local_3c [20];
  uint32_t local_28;
  uint32_t uStack_14;
  
  uStack_14 = 0xe26d9;
  if ((cg_entities[param_2 * 0xaf8 + 10] & 4) != 0) {
    return;
  }
  if (((GHIDRA_FIELD(cgs, 27392, 4) != 0) && (tmp_i3 = *(int *)(g_unk_01047b00 + 0xcc), tmp_i3 == param_6)) &&
     ((cg_entities[tmp_i3 * 0xaf8 + 8] & 0x20) != 0)) {
    AngleVectors(&g_unk_010907ac,&local_80,&local_74,&local_64);
    tmp_i6 = *(int *)(g_unk_01047b00 + 0x440) * 0xaf8;
    local_8c = *(float *)(cg_entities + tmp_i6 + 0x18);
    local_88 = *(float *)(cg_entities + tmp_i6 + 0x1c);
    local_84 = *(float *)(cg_entities + tmp_i6 + 0x20);
    if (*(int *)(cg_entities + tmp_i6 + 0xfc) != 0) {
      local_8c = local_64 * 16.0 + local_8c;
      local_88 = local_60 * 16.0 + local_88;
      local_84 = local_5c * 16.0 + local_84;
    }
    tmp_l7 = (long double)Q_crandom(&stack0x00000020);
    tmp_l8 = (long double)Q_crandom(&stack0x00000020);
    tmp_l8 = tmp_l8 * (long double)100.0;
    tmp_l9 = (long double)8192.0;
    tmp_l7 = (long double)(float)((long double)100.0 * tmp_l7);
    *param_1 = (float)((long double)local_64 * tmp_l8 +
                      tmp_l7 * (long double)local_74 +
                      tmp_l9 * (long double)local_80 + (long double)local_8c);
    param_1[1] = (float)((long double)local_60 * tmp_l8 +
                        (long double)local_70 * tmp_l7 +
                        (long double)local_88 + (long double)local_7c * tmp_l9);
    param_1[2] = (float)(tmp_l8 * (long double)local_5c +
                        (long double)local_6c * tmp_l7 +
                        (long double)local_78 * tmp_l9 + (long double)local_84);
    CG_Trace(local_54,&local_8c,0,0,param_1,tmp_i3,0x6000001);
    tmp_f10 = floorf(local_48);
    tmp_f11 = ceilf(local_48);
    if (local_48 < local_8c) {
      tmp_f10 = tmp_f11;
    }
    local_48 = tmp_f10;
    tmp_f11 = floorf(local_44);
    tmp_f12 = ceilf(local_44);
    if (local_44 < local_88) {
      tmp_f11 = tmp_f12;
    }
    local_44 = tmp_f11;
    tmp_f12 = floorf(local_40);
    tmp_f13 = ceilf(local_40);
    tmp_b1 = local_40 < local_84;
    local_40 = tmp_f12;
    if (tmp_b1) {
      local_40 = tmp_f13;
    }
    *param_1 = tmp_f10;
    param_1[1] = tmp_f11;
    param_1[2] = local_40;
  }
  if ((param_2 < 0) || ((float)GHIDRA_FIELD(cg_tracerChance, 8, 4) <= 0.0)) {
LAB_000e2810:
    if (param_4 == 0) {
LAB_000e3650:
      tmp_i3 = CG_CalcMuzzlePoint(param_2,&local_bc);
      if ((tmp_i3 == 0) && (*(int *)(g_unk_01047b00 + 0x16c) == 0)) {
        return;
      }
      if (param_7 == 0.0) {
        local_c8 = *param_1 - local_bc;
        local_c4 = param_1[1] - local_b8;
        local_c0 = param_1[2] - local_b4;
        VectorNormalizeFast(&local_c8);
        *param_1 = local_c8 * 4.0 + *param_1;
        param_1[1] = local_c4 * 4.0 + param_1[1];
        param_1[2] = local_c0 * 4.0 + param_1[2];
        CG_Trace(local_54,&local_bc,0,0,param_1,0,0x4000001);
        local_c8 = vec3_origin - local_c8;
        local_c4 = g_unk_00c22b14 - local_c4;
        local_c0 = g_unk_00c22b18 - local_c0;
        CG_MissileHitWall(3,1,&local_48,&local_c8,local_28);
        return;
      }
      local_64 = 0.0;
      local_60 = 0.0;
      local_5c = 1.0;
      local_74 = (*param_1 - local_bc) * param_7 + local_bc;
      local_70 = (param_1[1] - local_b8) * param_7 + local_b8;
      local_6c = (param_1[2] - local_b4) * param_7 + local_b4;
      tmp_i3 = rand();
      trap_S_StartSound(param_1,0xffffffff,0,*(uint32_t *)(cgs + (tmp_i3 % 5) * 4 + 0x10ef4));
      CG_MissileHitWall(3,2,&local_74,&local_64,0);
      CG_MissileHitWall(3,1,param_1,local_3c,0);
      return;
    }
  }
  else {
    tmp_i3 = CG_CalcMuzzlePoint(param_2,&local_bc);
    if (tmp_i3 == 0) goto LAB_000e2810;
    tmp_u4 = CG_PointContents(&local_bc,0);
    tmp_u5 = CG_PointContents(param_1,0);
    if (tmp_u4 == tmp_u5) {
      if ((tmp_u4 & 0x20) != 0) {
        CG_BubbleTrail(&local_bc,param_1,0x3f000000,0x41000000);
      }
    }
    else if ((tmp_u4 & 0x20) == 0) {
      if (((tmp_u5 & 0x20) != 0) &&
         (tmp_l7 = (long double)Distance(g_unk_01047b00 + 0x40,param_1), tmp_l7 < (long double)1024.0)) {
        trap_CM_BoxTrace(local_54,&local_bc,param_1,0,0,0,0x20);
        CG_BubbleTrail(param_1,&local_48,0x3f000000,0x41000000);
      }
    }
    else {
      trap_CM_BoxTrace(local_54,param_1,&local_bc,0,0,0,0x20);
      CG_BubbleTrail(&local_bc,&local_48,0x3f000000,0x41000000);
    }
    if (param_4 == 0) {
      if (GHIDRA_FIELD(cg_tracers, 12, 4) == 2) {
        if (*(int *)(g_unk_01047b00 + 0xcc) == param_2) goto LAB_000e3650;
      }
      else if (GHIDRA_FIELD(cg_tracers, 12, 4) != 1) goto LAB_000e3650;
      if ((param_6 == 0x3ff) || (param_6 < 0)) {
        CG_SpawnTracer(param_2,&local_bc,param_1);
      }
      else {
        CG_SpawnTracer(param_6,&local_bc,param_1);
      }
      goto LAB_000e3650;
    }
    if (GHIDRA_FIELD(cg_tracers, 12, 4) != 0) {
      local_f4 = rand();
      local_f4 = local_f4 & 0x7fff;
      if ((float)local_f4 / 32767.0 < (float)GHIDRA_FIELD(cg_tracerChance, 8, 4)) {
        CG_Tracer(&local_bc,param_1,0);
      }
    }
  }
  if (param_5 < 0x40) {
    CG_Bleed(param_1,param_5);
  }
  local_98 = *param_1 - local_bc;
  local_94 = param_1[1] - local_b8;
  local_90 = param_1[2] - local_b4;
  VectorNormalize(&local_98);
  tmp_i3 = param_5 * 0xaf8;
  local_84 = 0.0;
  local_8c = *(float *)(cg_entities + tmp_i3 + 0x18) - *param_1;
  local_88 = *(float *)(cg_entities + tmp_i3 + 0x1c) - param_1[1];
  tmp_l7 = (long double)VectorLength(&local_8c);
  local_8c = (float)((long double)local_98 * tmp_l7);
  local_88 = (float)((long double)local_94 * tmp_l7);
  local_84 = (float)(tmp_l7 * (long double)local_90);
  local_a4 = (float)((long double)local_98 * tmp_l7 + (long double)*param_1);
  local_a0 = (float)((long double)local_94 * tmp_l7 + (long double)param_1[1]);
  local_9c = (float)(tmp_l7 * (long double)local_90 + (long double)param_1[2]);
  CG_GetOriginForTag(cg_entities + tmp_i3,tmp_i3 + 0x31343a4,"tag_mouth",0,&local_8c,0);
  local_84 = local_84 + 5.0;
  local_80 = local_8c - local_a4;
  local_7c = local_88 - local_a0;
  local_78 = local_84 - local_9c;
  tmp_l7 = (long double)VectorLength(&local_80);
  if ((long double)10.0 <= tmp_l7) {
    local_d8 = 10;
  }
  else {
    if (GHIDRA_FIELD(cg_gibs, 12, 4) != 0) {
      local_d8 = 5;
      do {
        tmp_u4 = rand();
        tmp_f11 = local_98;
        tmp_f10 = (float)(tmp_u4 & 0x7fff) / 32767.0;
        tmp_u4 = rand();
        tmp_f12 = local_94;
        local_8c = (((float)(tmp_u4 & 0x7fff) / 32767.0) * 25.0 + 25.0) * tmp_f11;
        tmp_u4 = rand();
        tmp_f11 = local_90;
        local_88 = (((float)(tmp_u4 & 0x7fff) / 32767.0) * 25.0 + 25.0) * tmp_f12;
        tmp_u4 = rand();
        local_84 = (((float)(tmp_u4 & 0x7fff) / 32767.0) * 25.0 + 25.0) * tmp_f11;
        local_f4 = rand();
        local_f4 = local_f4 & 0x7fff;
        tmp_f11 = (float)local_f4 / 32767.0 - 0.5;
        local_8c = (tmp_f11 + tmp_f11) * 25.0 + local_8c;
        local_f4 = rand();
        local_f4 = local_f4 & 0x7fff;
        tmp_f11 = (float)local_f4 / 32767.0 - 0.5;
        local_88 = (tmp_f11 + tmp_f11) * 25.0 + local_88;
        local_f4 = rand();
        local_f4 = local_f4 & 0x7fff;
        tmp_f11 = (float)local_f4 / 32767.0 - 0.5;
        local_84 = (tmp_f11 + tmp_f11) * 25.0 + local_84;
        local_f4 = rand();
        local_f4 = local_f4 & 0x7fff;
        local_80 = ((float)local_f4 / 32767.0) * 0.25;
        tmp_d14 = sin((double)g_unk_010906e0 * 1e-05);
        local_7c = (float)tmp_d14;
        local_f4 = rand();
        local_f4 = local_f4 & 0x7fff;
        local_78 = (float)local_f4 / 32767.0;
        VectorNormalize();
        tmp_u2 = GHIDRA_FIELD(cgs, 68084, 4);
        tmp_i3 = g_unk_010906e0;
        local_80 = local_80 * 35.0;
        local_7c = local_7c * 35.0;
        local_78 = 0.0;
        local_8c = local_80 + local_8c;
        local_88 = local_7c + local_88;
        local_84 = local_84 + 0.0;
        tmp_i6 = rand();
        tmp_f11 = tmp_f10 * 0.8;
        CG_SmokePuff(&local_a4,&local_8c,tmp_f10 * 10.0 + 5.0,0x3f800000,tmp_f11,tmp_f11,0x3f000000,
                     (float)(tmp_i6 % 800 + 500),tmp_i3,0,0,tmp_u2);
        local_d8 = local_d8 + -1;
      } while (local_d8 != 0);
      goto LAB_000e2d03;
    }
    local_d8 = 10;
  }
  do {
    local_e4 = &local_a4;
    tmp_u4 = rand();
    tmp_f11 = local_98;
    tmp_f10 = (float)(tmp_u4 & 0x7fff) / 32767.0;
    tmp_u4 = rand();
    tmp_f12 = local_94;
    local_8c = (((float)(tmp_u4 & 0x7fff) / 32767.0) * 25.0 - 35.0) * tmp_f11;
    tmp_u4 = rand();
    tmp_f11 = local_90;
    local_88 = (((float)(tmp_u4 & 0x7fff) / 32767.0) * 25.0 - 35.0) * tmp_f12;
    tmp_u4 = rand();
    local_84 = (((float)(tmp_u4 & 0x7fff) / 32767.0) * 25.0 - 35.0) * tmp_f11;
    tmp_u4 = rand();
    tmp_f11 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
    local_8c = (tmp_f11 + tmp_f11) * 25.0 + local_8c;
    tmp_u4 = rand();
    tmp_f11 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
    local_88 = (tmp_f11 + tmp_f11) * 25.0 + local_88;
    tmp_u4 = rand();
    tmp_f11 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
    local_84 = (tmp_f11 + tmp_f11) * 25.0 + local_84;
    local_f4 = rand();
    local_f4 = local_f4 & 0x7fff;
    local_80 = ((float)local_f4 / 32767.0) * 0.25;
    tmp_d14 = sin((double)g_unk_010906e0 * 1e-05);
    local_7c = (float)tmp_d14;
    local_f4 = rand();
    local_f4 = local_f4 & 0x7fff;
    local_78 = (float)local_f4 / 32767.0;
    VectorNormalize(&local_80);
    tmp_u2 = GHIDRA_FIELD(cgs, 68088, 4);
    tmp_i3 = g_unk_010906e0;
    local_80 = local_80 * 35.0;
    local_7c = local_7c * 35.0;
    local_78 = 0.0;
    local_8c = local_80 + local_8c;
    local_88 = local_7c + local_88;
    local_84 = local_84 + 0.0;
    tmp_i6 = rand();
    tmp_f11 = tmp_f10 * 0.3 + 0.5;
    CG_SmokePuff(local_e4,&local_8c,tmp_f10 * 10.0 + 5.0,tmp_f11,tmp_f11,tmp_f11,0x3e000000,
                 (float)(tmp_i6 % 300 + 500),tmp_i3,0,0,tmp_u2);
    local_d8 = local_d8 + -1;
  } while (local_d8 != 0);
LAB_000e2d03:
  local_e4 = &local_a4;
  if (*(int *)(g_unk_01047b00 + 0xcc) == param_5) {
    tmp_i3 = rand();
    trap_S_StartSound(0,param_5,5,*(uint32_t *)(cgs + (tmp_i3 % 5) * 4 + 0x10ee0));
  }
  else {
    tmp_i3 = rand();
    trap_S_StartSound(param_5 * 0xaf8 + 0x3133e9c,0x3fe,5,
                      *(uint32_t *)(cgs + (tmp_i3 % 5) * 4 + 0x10ee0));
  }
  if (GHIDRA_FIELD(cg_gibs, 12, 4) == 0) {
    return;
  }
  if ((lastBloodSpat_13036 <= g_unk_010906e0) && (g_unk_010906e0 + -500 <= lastBloodSpat_13036)) {
    return;
  }
  tmp_i3 = CG_CalcMuzzlePoint(param_2,&local_bc);
  if (tmp_i3 == 0) {
    return;
  }
  local_c8 = *param_1 - local_bc;
  local_c4 = param_1[1] - local_b8;
  local_c0 = param_1[2] - local_b4;
  VectorNormalize(&local_c8);
  local_b0 = local_c8 * 128.0 + *param_1;
  local_ac = local_c4 * 128.0 + param_1[1];
  local_a8 = local_c0 * 128.0 + param_1[2];
  trap_CM_BoxTrace(local_54,param_1,&local_b0,0,0,0,0x4000001);
  if (1.0 <= local_4c) {
    if (g_unk_010906e0 + -1000 <= lastBloodSpat_13036) {
      return;
    }
    local_b0 = *param_1;
    local_ac = param_1[1];
    local_a8 = param_1[2] - 64.0;
    trap_CM_BoxTrace(local_54,param_1,&local_b0,0,0,0,0x4000001);
    if (1.0 <= local_4c) {
      return;
    }
  }
  local_74 = 0.0;
  local_70 = 0.0;
  local_6c = -1.0;
  tmp_u4 = rand();
  local_64 = 1.0;
  local_60 = 1.0;
  local_5c = 1.0;
  local_58 = 0x3f800000;
  tmp_i6 = GHIDRA_FIELD(cg_bloodTime, 12, 4) * 1000;
  local_68 = ((float)(tmp_u4 & 0x7fff) / 32767.0) * 20.0 + 15.0;
  tmp_i3 = rand();
  trap_R_ProjectDecal(*(uint32_t *)(cgs + (tmp_i3 % 5) * 4 + 0x10ca4),1,local_e4,&local_74,
                      &local_64,tmp_i6,tmp_i6 >> 4);
  lastBloodSpat_13036 = g_unk_010906e0;
  return;
}

uint8_t ClampChar(int param_1)
{
  if (param_1 < -0x80) {
    return 0x80;
  }
  if (0x7f < param_1) {
    return 0x7f;
  }
  return (char)param_1;
}

int ClampShort(int param_1)
{
  int tmp_i1;
  
  if (-0x8001 < param_1) {
    tmp_i1 = (int)(short)param_1;
    if (0x7fff < param_1) {
      tmp_i1 = 0x7fff;
    }
    return tmp_i1;
  }
  return -0x8000;
}

int DirToByte(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  float *pfVar6;
  
  if (param_1 != (float *)0x0) {
    pfVar6 = (float *)&bytedirs;
    tmp_i5 = 0;
    tmp_i4 = 0;
    tmp_f2 = 0.0;
    do {
      tmp_f1 = pfVar6[2] * param_1[2] + pfVar6[1] * param_1[1] + *pfVar6 * *param_1;
      tmp_i3 = tmp_i5;
      if (tmp_f1 <= tmp_f2) {
        tmp_f1 = tmp_f2;
        tmp_i3 = tmp_i4;
      }
      tmp_i4 = tmp_i3;
      tmp_i5 = tmp_i5 + 1;
      pfVar6 = pfVar6 + 3;
      tmp_f2 = tmp_f1;
    } while (tmp_i5 != 0xa2);
    return tmp_i4;
  }
  return 0;
}

void ByteToDir(uint param_1,uint32_t *param_2)
{
  if (param_1 < 0xa2) {
    *param_2 = (&bytedirs)[param_1 * 3];
    param_2[1] = (&g_unk_00149844)[param_1 * 3];
    param_2[2] = (&g_unk_00149848)[param_1 * 3];
    return;
  }
  *param_2 = vec3_origin;
  param_2[1] = g_unk_00c22b14;
  param_2[2] = g_unk_00c22b18;
  return;
}

uint32_t ColorBytes3(float param_1,float param_2,float param_3)
{
  uint8_t local_4 [2];
  uint8_t uStack_2;
  
  _local_4 = CONCAT12((char)(short)ROUND(param_3 * 255.0),
                      CONCAT11((char)(short)ROUND(param_2 * 255.0),
                               (char)(short)ROUND(param_1 * 255.0)));
  return _local_4;
}

uint32_t ColorBytes4(float param_1,float param_2,float param_3,float param_4)
{
  uint32_t local_4;
  
  local_4 = CONCAT13((char)(short)ROUND(param_4 * 255.0),
                     CONCAT12((char)(short)ROUND(param_3 * 255.0),
                              CONCAT11((char)(short)ROUND(param_2 * 255.0),
                                       (char)(short)ROUND(param_1 * 255.0))));
  return local_4;
}

void NormalizeColor(float *param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  
  tmp_f1 = *param_1;
  tmp_f3 = param_1[1];
  if (param_1[1] <= tmp_f1) {
    tmp_f3 = tmp_f1;
  }
  tmp_f2 = param_1[2];
  if (param_1[2] <= tmp_f3) {
    tmp_f2 = tmp_f3;
  }
  if (tmp_f2 != 0.0) {
    *param_2 = tmp_f1 / tmp_f2;
    param_2[1] = param_1[1] / tmp_f2;
    param_2[2] = param_1[2] / tmp_f2;
    return;
  }
  param_2[2] = 0.0;
  param_2[1] = 0.0;
  *param_2 = 0.0;
  return;
}

uint32_t PlaneFromPoints(float *param_1,float *param_2,float *param_3,float *param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  float tmp_f9;
  float tmp_f10;
  float tmp_f11;
  float tmp_f12;
  float tmp_f13;
  
  tmp_f1 = *param_3;
  tmp_f13 = *param_2;
  tmp_f2 = param_3[1];
  tmp_f3 = param_2[1];
  tmp_f4 = param_3[2];
  tmp_f5 = param_2[2];
  tmp_f6 = *param_4;
  tmp_f7 = *param_2;
  tmp_f8 = param_4[1];
  tmp_f9 = param_2[1];
  tmp_f10 = param_4[2];
  tmp_f11 = param_2[2];
  tmp_f12 = (tmp_f4 - tmp_f5) * (tmp_f8 - tmp_f9) - (tmp_f2 - tmp_f3) * (tmp_f10 - tmp_f11);
  *param_1 = tmp_f12;
  tmp_f4 = (tmp_f10 - tmp_f11) * (tmp_f1 - tmp_f13) - (tmp_f4 - tmp_f5) * (tmp_f6 - tmp_f7);
  param_1[1] = tmp_f4;
  tmp_f1 = (tmp_f6 - tmp_f7) * (tmp_f2 - tmp_f3) - (tmp_f8 - tmp_f9) * (tmp_f1 - tmp_f13);
  param_1[2] = tmp_f1;
  tmp_f1 = tmp_f1 * tmp_f1 + tmp_f4 * tmp_f4 + tmp_f12 * tmp_f12;
  tmp_f13 = SQRT(tmp_f1);
  if (NAN(tmp_f13)) {
    tmp_f13 = sqrtf(tmp_f1);
  }
  if (tmp_f13 == 0.0) {
    return 0;
  }
  tmp_f13 = 1.0 / tmp_f13;
  tmp_f1 = *param_1;
  *param_1 = tmp_f1 * tmp_f13;
  tmp_f2 = param_1[1];
  param_1[1] = tmp_f2 * tmp_f13;
  tmp_f3 = param_1[2];
  param_1[2] = tmp_f13 * tmp_f3;
  param_1[3] = tmp_f13 * tmp_f3 * param_2[2] + tmp_f2 * tmp_f13 * param_2[1] + tmp_f1 * tmp_f13 * *param_2
  ;
  return 1;
}

void RotatePointAroundVertex
               (float *param_1,float param_2,float param_3,float param_4,float *param_5)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  float tmp_f9;
  double local_2c;
  double local_24 [2];
  
  tmp_f1 = *param_1 - *param_5;
  *param_1 = tmp_f1;
  tmp_f2 = param_1[1] - param_5[1];
  param_1[1] = tmp_f2;
  sincos((double)param_2,local_24,&local_2c);
  tmp_f3 = (float)local_24[0];
  tmp_f4 = (float)local_2c;
  sincos((double)param_3,local_24,&local_2c);
  tmp_f5 = (float)local_24[0];
  tmp_f6 = (float)local_2c;
  sincos((double)param_4,local_24,&local_2c);
  tmp_f9 = tmp_f1 * (float)local_2c;
  tmp_f7 = tmp_f2 * (float)local_24[0];
  tmp_f8 = (param_1[2] - param_5[2]) * tmp_f6;
  tmp_f6 = (tmp_f9 - tmp_f7) * tmp_f6 + tmp_f5 * tmp_f6;
  *param_1 = tmp_f6;
  tmp_f7 = tmp_f7 * tmp_f5;
  tmp_f1 = (float)local_24[0] * tmp_f1 + tmp_f2 * (float)local_2c;
  tmp_f2 = tmp_f4 * tmp_f1 + ((tmp_f5 * tmp_f9 - tmp_f7) - tmp_f8) * tmp_f3;
  param_1[1] = tmp_f2;
  tmp_f1 = tmp_f1 * tmp_f3 + ((tmp_f7 - tmp_f9 * tmp_f5) + tmp_f8) * tmp_f4;
  param_1[2] = tmp_f1;
  *param_1 = tmp_f6 + *param_5;
  param_1[1] = tmp_f2 + param_5[1];
  param_1[2] = tmp_f1 + param_5[2];
  return;
}

void vectoangles(float *param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  double tmp_d3;
  float tmp_f4;
  
  tmp_f4 = param_1[1];
  tmp_f1 = *param_1;
  if (tmp_f4 == 0.0) {
    if (tmp_f1 == 0.0) {
      if (param_1[2] <= 0.0) {
        tmp_f1 = -270.0;
        tmp_f2 = 0.0;
      }
      else {
        tmp_f1 = -90.0;
        tmp_f2 = 0.0;
      }
      goto LAB_000e5e10;
    }
LAB_000e5d90:
    tmp_d3 = atan2((double)tmp_f4,(double)tmp_f1);
    tmp_f2 = ((float)tmp_d3 * 180.0) / 3.1415927;
    if (tmp_f2 < 0.0) {
      tmp_f2 = tmp_f2 + 360.0;
    }
    tmp_f1 = *param_1;
    tmp_f4 = param_1[1];
  }
  else {
    if (tmp_f1 != 0.0) goto LAB_000e5d90;
    if (tmp_f4 <= 0.0) {
      tmp_f2 = 270.0;
    }
    else {
      tmp_f2 = 90.0;
    }
  }
  tmp_f1 = tmp_f4 * tmp_f4 + tmp_f1 * tmp_f1;
  tmp_f4 = SQRT(tmp_f1);
  if (NAN(tmp_f4)) {
    tmp_f4 = sqrtf(tmp_f1);
  }
  tmp_d3 = atan2((double)param_1[2],(double)tmp_f4);
  tmp_f1 = ((float)tmp_d3 * 180.0) / 3.1415927;
  if (tmp_f1 < 0.0) {
    tmp_f1 = tmp_f1 + 360.0;
  }
  tmp_f1 = -tmp_f1;
LAB_000e5e10:
  *param_2 = tmp_f1;
  param_2[1] = tmp_f2;
  param_2[2] = 0.0;
  return;
}

void AnglesToAxis(float *param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  double local_2c;
  double local_24 [2];
  uint32_t uStack_14;
  
  uStack_14 = 0xe5ee9;
  sincos((double)(param_1[1] * 0.017453292),local_24,&local_2c);
  tmp_f1 = (float)local_24[0];
  tmp_f2 = (float)local_2c;
  cy_5405 = tmp_f2;
  sy_5402 = tmp_f1;
  sincos((double)(*param_1 * 0.017453292),local_24,&local_2c);
  tmp_f3 = (float)local_24[0];
  tmp_f4 = (float)local_2c;
  cp_5404 = tmp_f4;
  sp_5401 = tmp_f3;
  sincos((double)(param_1[2] * 0.017453292),local_24,&local_2c);
  tmp_f5 = (float)local_24[0];
  tmp_f7 = (float)local_2c;
  cr_5403 = tmp_f7;
  sr_5400 = tmp_f5;
  if (param_2 != (float *)0x0) {
    *param_2 = tmp_f2 * tmp_f4;
    param_2[1] = tmp_f1 * tmp_f4;
    param_2[2] = -tmp_f3;
  }
  tmp_f6 = -tmp_f5;
  if (param_2 != (float *)0xffffffe8) {
    param_2[6] = tmp_f5 * tmp_f1 + tmp_f2 * tmp_f3 * tmp_f7;
    param_2[7] = tmp_f6 * tmp_f2 + tmp_f3 * tmp_f7 * tmp_f1;
    param_2[8] = tmp_f7 * tmp_f4;
  }
  param_2[3] = vec3_origin - (tmp_f1 * tmp_f7 + tmp_f2 * tmp_f3 * tmp_f6);
  param_2[4] = g_unk_00c22b14 - (tmp_f3 * tmp_f6 * tmp_f1 - tmp_f2 * tmp_f7);
  param_2[5] = g_unk_00c22b18 - tmp_f4 * tmp_f6;
  return;
}

void AxisClear(uint32_t *param_1)
{
  *param_1 = 0x3f800000;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0x3f800000;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0x3f800000;
  return;
}

void AxisCopy(uint32_t *param_1,uint32_t *param_2)
{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  param_2[2] = param_1[2];
  param_2[3] = param_1[3];
  param_2[4] = param_1[4];
  param_2[5] = param_1[5];
  param_2[6] = param_1[6];
  param_2[7] = param_1[7];
  param_2[8] = param_1[8];
  return;
}

void ProjectPointOnPlane(float *param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  
  tmp_f1 = *param_3;
  tmp_f2 = param_3[1];
  tmp_f3 = param_3[2];
  tmp_f5 = 1.0 / (tmp_f3 * tmp_f3 + tmp_f2 * tmp_f2 + tmp_f1 * tmp_f1);
  tmp_f4 = (param_2[2] * tmp_f3 + param_2[1] * tmp_f2 + *param_2 * tmp_f1) * tmp_f5;
  *param_1 = *param_2 - tmp_f1 * tmp_f5 * tmp_f4;
  param_1[1] = param_2[1] - tmp_f2 * tmp_f5 * tmp_f4;
  param_1[2] = param_2[2] - tmp_f3 * tmp_f5 * tmp_f4;
  return;
}

void MakeNormalVectors(float *param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  
  tmp_f4 = *param_1;
  tmp_f3 = -tmp_f4;
  param_2[1] = tmp_f3;
  tmp_f1 = param_1[1];
  param_2[2] = tmp_f1;
  tmp_f2 = param_1[2];
  *param_2 = tmp_f2;
  tmp_f3 = -(param_1[2] * tmp_f1 + tmp_f3 * param_1[1] + *param_1 * tmp_f2);
  tmp_f2 = *param_1 * tmp_f3 + tmp_f2;
  *param_2 = tmp_f2;
  tmp_f4 = param_1[1] * tmp_f3 - tmp_f4;
  param_2[1] = tmp_f4;
  tmp_f1 = tmp_f3 * param_1[2] + tmp_f1;
  param_2[2] = tmp_f1;
  tmp_f1 = tmp_f1 * tmp_f1 + tmp_f4 * tmp_f4 + tmp_f2 * tmp_f2;
  tmp_f4 = SQRT(tmp_f1);
  if (NAN(tmp_f4)) {
    tmp_f4 = sqrtf(tmp_f1);
  }
  if (tmp_f4 == 0.0) {
    tmp_f1 = param_2[1];
    tmp_f4 = param_2[2];
  }
  else {
    tmp_f4 = 1.0 / tmp_f4;
    *param_2 = *param_2 * tmp_f4;
    tmp_f1 = param_2[1] * tmp_f4;
    param_2[1] = tmp_f1;
    tmp_f4 = tmp_f4 * param_2[2];
    param_2[2] = tmp_f4;
  }
  *param_3 = tmp_f1 * param_1[2] - tmp_f4 * param_1[1];
  param_3[1] = param_2[2] * *param_1 - *param_2 * param_1[2];
  param_3[2] = *param_2 * param_1[1] - param_2[1] * *param_1;
  return;
}

void VectorRotate(float *param_1,float *param_2,float *param_3)
{
  *param_3 = param_1[2] * param_2[2] + param_1[1] * param_2[1] + *param_1 * *param_2;
  param_3[1] = param_1[2] * param_2[5] + param_1[1] * param_2[4] + *param_1 * param_2[3];
  param_3[2] = param_1[2] * param_2[8] + param_1[1] * param_2[7] + *param_1 * param_2[6];
  return;
}

long double LerpAngle(float param_1,float param_2,float param_3)
{
  long double tmp_l1;
  long double tmp_l2;
  
  tmp_l1 = (long double)param_2;
  tmp_l2 = tmp_l1 - (long double)param_1;
  if ((long double)180.0 < tmp_l2) {
    tmp_l1 = tmp_l1 - (long double)360.0;
    tmp_l2 = tmp_l1 - (long double)param_1;
  }
  if (tmp_l2 < (long double)-180.0) {
    tmp_l2 = (tmp_l1 + (long double)360.0) - (long double)param_1;
  }
  return tmp_l2 * (long double)param_3 + (long double)param_1;
}

void LerpPosition(float *param_1,float *param_2,float param_3,float *param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  
  tmp_f1 = param_2[1];
  tmp_f2 = param_1[1];
  tmp_f3 = param_2[2];
  tmp_f4 = param_1[2];
  *param_4 = (*param_2 - *param_1) * param_3 + *param_1;
  param_4[1] = (tmp_f1 - tmp_f2) * param_3 + param_1[1];
  param_4[2] = (tmp_f3 - tmp_f4) * param_3 + param_1[2];
  return;
}

void AngleSubtract(float param_1,float param_2)
{
  for (param_1 = param_1 - param_2; 180.0 < param_1; param_1 = param_1 - 360.0) {
  }
  for (; param_1 < -180.0; param_1 = param_1 + 360.0) {
  }
  return;
}

void AnglesSubtract(float *param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  
  for (tmp_f1 = *param_1 - *param_2; 180.0 < tmp_f1; tmp_f1 = tmp_f1 - 360.0) {
  }
  for (; tmp_f1 < -180.0; tmp_f1 = tmp_f1 + 360.0) {
  }
  *param_3 = tmp_f1;
  for (tmp_f1 = param_1[1] - param_2[1]; 180.0 < tmp_f1; tmp_f1 = tmp_f1 - 360.0) {
  }
  for (; tmp_f1 < -180.0; tmp_f1 = tmp_f1 + 360.0) {
  }
  param_3[1] = tmp_f1;
  for (tmp_f1 = param_1[2] - param_2[2]; 180.0 < tmp_f1; tmp_f1 = tmp_f1 - 360.0) {
  }
  for (; tmp_f1 < -180.0; tmp_f1 = tmp_f1 + 360.0) {
  }
  param_3[2] = tmp_f1;
  return;
}

long double AngleMod(float param_1)
{
  return (long double)((float)((int)ROUND(param_1 * 182.04445) & 0xffff) * 0.005493164);
}

long double AngleNormalize2Pi(float param_1)
{
  return (long double)
         (((float)((int)ROUND(((param_1 * 180.0) / 3.1415927) * 182.04445) & 0xffff) * 0.005493164 *
          3.1415927) / 180.0);
}

long double AngleNormalize360(float param_1)
{
  return (long double)((float)((int)ROUND(param_1 * 182.04445) & 0xffff) * 0.005493164);
}

uint AngleNormalizeInt(uint param_1)
{
  if ((int)param_1 < 0) {
    param_1 = (int)param_1 % 0x10000 + 0x10000;
  }
  return param_1 & 0xffff;
}

long double AngleNormalize180(float param_1)
{
  long double tmp_l1;
  
  tmp_l1 = (long double)((float)((int)ROUND(param_1 * 182.04445) & 0xffff) * 0.005493164);
  if ((long double)180.0 < tmp_l1) {
    tmp_l1 = tmp_l1 - (long double)360.0;
  }
  return tmp_l1;
}

long double AngleDelta(float param_1,float param_2)
{
  long double tmp_l1;
  
  tmp_l1 = (long double)((float)((int)ROUND((param_1 - param_2) * 182.04445) & 0xffff) * 0.005493164);
  if ((long double)180.0 < tmp_l1) {
    tmp_l1 = tmp_l1 - (long double)360.0;
  }
  return tmp_l1;
}

void SetPlaneSignbits(float *param_1)
{
  byte tmp_b1;
  
  tmp_b1 = *param_1 < 0.0;
  if (param_1[1] < 0.0) {
    tmp_b1 = *param_1 < 0.0 | 2;
  }
  if (param_1[2] < 0.0) {
    tmp_b1 = tmp_b1 | 4;
  }
  *(byte *)((int)param_1 + 0x11) = tmp_b1;
  return;
}

long double RadiusFromBounds(float *param_1,float *param_2)
{
  long double tmp_l1;
  long double tmp_l2;
  long double tmp_l3;
  float tmp_f4;
  
  tmp_l2 = (long double)ABS(*param_1);
  if ((long double)ABS(*param_1) <= (long double)ABS(*param_2)) {
    tmp_l2 = (long double)ABS(*param_2);
  }
  tmp_l3 = (long double)ABS(param_1[1]);
  if ((long double)ABS(param_1[1]) <= (long double)ABS(param_2[1])) {
    tmp_l3 = (long double)ABS(param_2[1]);
  }
  tmp_l1 = (long double)ABS(param_1[2]);
  if ((long double)ABS(param_1[2]) <= (long double)ABS(param_2[2])) {
    tmp_l1 = (long double)ABS(param_2[2]);
  }
  tmp_l3 = tmp_l1 * tmp_l1 + tmp_l3 * tmp_l3 + tmp_l2 * tmp_l2;
  tmp_l2 = SQRT(tmp_l3);
  if (NAN(tmp_l2)) {
    tmp_f4 = sqrtf((float)tmp_l3);
    tmp_l2 = (long double)tmp_f4;
  }
  return tmp_l2;
}

void ClearBounds(uint32_t *param_1,uint32_t *param_2)
{
  param_1[2] = 0x47c34f80;
  param_1[1] = 0x47c34f80;
  *param_1 = 0x47c34f80;
  param_2[2] = 0xc7c34f80;
  param_2[1] = 0xc7c34f80;
  *param_2 = 0xc7c34f80;
  return;
}

void AddPointToBounds(float *param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  
  tmp_f1 = *param_1;
  if (tmp_f1 < *param_2) {
    *param_2 = tmp_f1;
    tmp_f1 = *param_1;
  }
  if (*param_3 < tmp_f1) {
    *param_3 = tmp_f1;
  }
  tmp_f1 = param_1[1];
  if (tmp_f1 < param_2[1]) {
    param_2[1] = tmp_f1;
    tmp_f1 = param_1[1];
  }
  if (param_3[1] < tmp_f1) {
    param_3[1] = tmp_f1;
  }
  tmp_f1 = param_1[2];
  if (tmp_f1 < param_2[2]) {
    param_2[2] = tmp_f1;
    tmp_f1 = param_1[2];
  }
  if (param_3[2] < tmp_f1) {
    param_3[2] = tmp_f1;
  }
  return;
}

bool PointInBounds(float *param_1,float *param_2,float *param_3)
{
  bool tmp_b1;
  
  tmp_b1 = false;
  if ((((*param_2 <= *param_1) && (*param_1 <= *param_3)) && (param_2[1] <= param_1[1])) &&
     ((param_1[1] <= param_3[1] && (param_2[2] <= param_1[2])))) {
    tmp_b1 = param_1[2] <= param_3[2];
  }
  return tmp_b1;
}

bool VectorCompare(float *param_1,float *param_2)
{
  if ((*param_1 == *param_2) && (param_1[1] == param_2[1])) {
    return param_2[2] == param_1[2];
  }
  return false;
}

void VectorNormalize(float *param_1)
{
  float __x;
  float tmp_f1;
  
  __x = param_1[2] * param_1[2] + param_1[1] * param_1[1] + *param_1 * *param_1;
  tmp_f1 = SQRT(__x);
  if (NAN(tmp_f1)) {
    tmp_f1 = sqrtf(__x);
  }
  if (tmp_f1 != 0.0) {
    tmp_f1 = 1.0 / tmp_f1;
    *param_1 = *param_1 * tmp_f1;
    param_1[1] = param_1[1] * tmp_f1;
    param_1[2] = tmp_f1 * param_1[2];
  }
  return;
}

void VectorNormalizeFast(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  
  tmp_f1 = *param_1;
  tmp_f2 = param_1[1];
  tmp_f3 = param_1[2] * param_1[2] + tmp_f2 * tmp_f2 + tmp_f1 * tmp_f1;
  tmp_f4 = (float)(0x5f3759df - ((int)tmp_f3 >> 1));
  tmp_f4 = (1.5 - tmp_f3 * 0.5 * tmp_f4 * tmp_f4) * tmp_f4;
  *param_1 = tmp_f1 * tmp_f4;
  param_1[1] = tmp_f2 * tmp_f4;
  param_1[2] = tmp_f4 * param_1[2];
  return;
}

long double VectorNormalize2(float *param_1,float *param_2)
{
  long double tmp_l1;
  long double tmp_l2;
  float tmp_f3;
  
  tmp_l2 = (long double)param_1[2] * (long double)param_1[2] +
          (long double)param_1[1] * (long double)param_1[1] +
          (long double)*param_1 * (long double)*param_1;
  tmp_l1 = SQRT(tmp_l2);
  if (NAN(tmp_l1)) {
    tmp_f3 = sqrtf((float)tmp_l2);
    tmp_l1 = (long double)tmp_f3;
  }
  tmp_l2 = (long double)0;
  if (tmp_l1 != tmp_l2) {
    tmp_l2 = (long double)1.0 / tmp_l1;
    *param_2 = (float)((long double)*param_1 * tmp_l2);
    param_2[1] = (float)((long double)param_1[1] * tmp_l2);
    param_2[2] = (float)(tmp_l2 * (long double)param_1[2]);
    return tmp_l1;
  }
  param_2[2] = (float)tmp_l2;
  param_2[1] = (float)tmp_l2;
  *param_2 = (float)tmp_l2;
  return tmp_l1;
}

void _VectorMA(float *param_1,float param_2,float *param_3,float *param_4)
{
  *param_4 = *param_3 * param_2 + *param_1;
  param_4[1] = param_3[1] * param_2 + param_1[1];
  param_4[2] = param_2 * param_3[2] + param_1[2];
  return;
}

long double _DotProduct(float *param_1,float *param_2)
{
  return (long double)param_1[2] * (long double)param_2[2] +
         (long double)param_1[1] * (long double)param_2[1] +
         (long double)*param_1 * (long double)*param_2;
}

void _VectorSubtract(float *param_1,float *param_2,float *param_3)
{
  *param_3 = *param_1 - *param_2;
  param_3[1] = param_1[1] - param_2[1];
  param_3[2] = param_1[2] - param_2[2];
  return;
}

void _VectorAdd(float *param_1,float *param_2,float *param_3)
{
  *param_3 = *param_1 + *param_2;
  param_3[1] = param_1[1] + param_2[1];
  param_3[2] = param_1[2] + param_2[2];
  return;
}

void _VectorCopy(uint32_t *param_1,uint32_t *param_2)
{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  param_2[2] = param_1[2];
  return;
}

void _VectorScale(float *param_1,float param_2,float *param_3)
{
  *param_3 = *param_1 * param_2;
  param_3[1] = param_1[1] * param_2;
  param_3[2] = param_2 * param_1[2];
  return;
}

void CrossProduct(float *param_1,float *param_2,float *param_3)
{
  *param_3 = param_1[1] * param_2[2] - param_1[2] * param_2[1];
  param_3[1] = param_1[2] * *param_2 - *param_1 * param_2[2];
  param_3[2] = *param_1 * param_2[1] - param_1[1] * *param_2;
  return;
}

long double VectorLength(float *param_1)
{
  long double tmp_l1;
  long double tmp_l2;
  float tmp_f3;
  
  tmp_l2 = (long double)param_1[2] * (long double)param_1[2] +
          (long double)param_1[1] * (long double)param_1[1] +
          (long double)*param_1 * (long double)*param_1;
  tmp_l1 = SQRT(tmp_l2);
  if (NAN(tmp_l1)) {
    tmp_f3 = sqrtf((float)tmp_l2);
    tmp_l1 = (long double)tmp_f3;
  }
  return tmp_l1;
}

long double VectorLengthSquared(float *param_1)
{
  return (long double)param_1[2] * (long double)param_1[2] +
         (long double)param_1[1] * (long double)param_1[1] +
         (long double)*param_1 * (long double)*param_1;
}

long double Distance(float *param_1,float *param_2)
{
  long double tmp_l1;
  long double tmp_l2;
  float tmp_f3;
  
  tmp_l2 = ((long double)param_2[1] - (long double)param_1[1]) *
          ((long double)param_2[1] - (long double)param_1[1]) +
          ((long double)*param_2 - (long double)*param_1) *
          ((long double)*param_2 - (long double)*param_1) +
          ((long double)param_2[2] - (long double)param_1[2]) *
          ((long double)param_2[2] - (long double)param_1[2]);
  tmp_l1 = SQRT(tmp_l2);
  if (NAN(tmp_l1)) {
    tmp_f3 = sqrtf((float)tmp_l2);
    tmp_l1 = (long double)tmp_f3;
  }
  return tmp_l1;
}

long double DistanceSquared(float *param_1,float *param_2)
{
  return ((long double)param_2[1] - (long double)param_1[1]) *
         ((long double)param_2[1] - (long double)param_1[1]) +
         ((long double)*param_2 - (long double)*param_1) *
         ((long double)*param_2 - (long double)*param_1) +
         ((long double)param_2[2] - (long double)param_1[2]) *
         ((long double)param_2[2] - (long double)param_1[2]);
}

void VectorInverse(float *param_1)
{
  *param_1 = -*param_1;
  param_1[1] = -param_1[1];
  param_1[2] = -param_1[2];
  return;
}

void Vector4Scale(float *param_1,float param_2,float *param_3)
{
  *param_3 = *param_1 * param_2;
  param_3[1] = param_1[1] * param_2;
  param_3[2] = param_1[2] * param_2;
  param_3[3] = param_2 * param_1[3];
  return;
}

void MatrixMultiply(float *param_1,float *param_2,float *param_3)
{
  *param_3 = param_1[2] * param_2[6] + param_1[1] * param_2[3] + *param_1 * *param_2;
  param_3[1] = param_1[2] * param_2[7] + param_1[1] * param_2[4] + *param_1 * param_2[1];
  param_3[2] = param_1[2] * param_2[8] + param_1[1] * param_2[5] + *param_1 * param_2[2];
  param_3[3] = param_1[5] * param_2[6] + param_1[4] * param_2[3] + param_1[3] * *param_2;
  param_3[4] = param_1[5] * param_2[7] + param_1[4] * param_2[4] + param_1[3] * param_2[1];
  param_3[5] = param_1[5] * param_2[8] + param_1[4] * param_2[5] + param_1[3] * param_2[2];
  param_3[6] = param_1[8] * param_2[6] + param_1[7] * param_2[3] + param_1[6] * *param_2;
  param_3[7] = param_1[8] * param_2[7] + param_1[7] * param_2[4] + param_1[6] * param_2[1];
  param_3[8] = param_1[8] * param_2[8] + param_1[7] * param_2[5] + param_1[6] * param_2[2];
  return;
}

void AngleVectors(float *param_1,float *param_2,float *param_3,float *param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  double local_2c;
  double local_24 [2];
  
  sincos((double)(param_1[1] * 0.017453292),local_24,&local_2c);
  tmp_f1 = (float)local_24[0];
  tmp_f2 = (float)local_2c;
  cy_5405 = tmp_f2;
  sy_5402 = tmp_f1;
  sincos((double)(*param_1 * 0.017453292),local_24,&local_2c);
  tmp_f3 = (float)local_24[0];
  tmp_f4 = (float)local_2c;
  cp_5404 = tmp_f4;
  sp_5401 = tmp_f3;
  sincos((double)(param_1[2] * 0.017453292),local_24,&local_2c);
  tmp_f5 = (float)local_24[0];
  tmp_f7 = (float)local_2c;
  cr_5403 = tmp_f7;
  sr_5400 = tmp_f5;
  if (param_2 != (float *)0x0) {
    *param_2 = tmp_f2 * tmp_f4;
    param_2[1] = tmp_f4 * tmp_f1;
    param_2[2] = -tmp_f3;
  }
  if (param_3 != (float *)0x0) {
    tmp_f6 = tmp_f3 * -tmp_f5;
    *param_3 = tmp_f1 * tmp_f7 + tmp_f2 * tmp_f6;
    param_3[1] = tmp_f6 * tmp_f1 - tmp_f2 * tmp_f7;
    param_3[2] = -tmp_f5 * tmp_f4;
  }
  if (param_4 != (float *)0x0) {
    *param_4 = tmp_f1 * tmp_f5 + tmp_f2 * tmp_f3 * tmp_f7;
    param_4[1] = tmp_f3 * tmp_f7 * tmp_f1 - tmp_f2 * tmp_f5;
    param_4[2] = tmp_f7 * tmp_f4;
  }
  return;
}

void PerpendicularVector(float *param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint tmp_u6;
  float tmp_f7;
  float local_18 [4];
  
  local_18[2] = 0.0;
  local_18[1] = 0.0;
  local_18[0] = 0.0;
  tmp_f4 = ABS(*param_2);
  if (1.0 <= tmp_f4) {
    tmp_f4 = 1.0;
  }
  tmp_f5 = ABS(param_2[1]);
  tmp_f7 = tmp_f4;
  if (tmp_f5 < tmp_f4) {
    tmp_f7 = tmp_f5;
  }
  tmp_u6 = 2;
  if (tmp_f7 <= ABS(param_2[2])) {
    tmp_u6 = (uint)(tmp_f5 < tmp_f4);
  }
  local_18[tmp_u6] = 1.0;
  tmp_f4 = *param_2;
  tmp_f7 = param_2[1];
  tmp_f5 = param_2[2];
  tmp_f1 = 1.0 / (tmp_f5 * tmp_f5 + tmp_f7 * tmp_f7 + tmp_f4 * tmp_f4);
  tmp_f2 = (local_18[2] * tmp_f5 + local_18[1] * tmp_f7 + local_18[0] * tmp_f4) * tmp_f1;
  tmp_f3 = local_18[0] - tmp_f4 * tmp_f1 * tmp_f2;
  *param_1 = tmp_f3;
  tmp_f7 = local_18[1] - tmp_f7 * tmp_f1 * tmp_f2;
  param_1[1] = tmp_f7;
  tmp_f4 = local_18[2] - tmp_f1 * tmp_f5 * tmp_f2;
  param_1[2] = tmp_f4;
  tmp_f4 = tmp_f4 * tmp_f4 + tmp_f7 * tmp_f7 + tmp_f3 * tmp_f3;
  tmp_f7 = SQRT(tmp_f4);
  if (NAN(tmp_f7)) {
    tmp_f7 = sqrtf(tmp_f4);
  }
  if (tmp_f7 != 0.0) {
    tmp_f7 = 1.0 / tmp_f7;
    *param_1 = *param_1 * tmp_f7;
    param_1[1] = param_1[1] * tmp_f7;
    param_1[2] = tmp_f7 * param_1[2];
  }
  return;
}

void RotatePointAroundVector(float *param_1,float *param_2,float *param_3,float param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  float tmp_f9;
  float tmp_f10;
  float tmp_f11;
  float tmp_f12;
  float tmp_f13;
  float tmp_f14;
  float tmp_f15;
  float tmp_f16;
  uint tmp_u17;
  uint tmp_u18;
  double local_7c;
  double local_74 [2];
  float local_60;
  float local_5c;
  float local_58;
  uint32_t local_54 [19];
  
  tmp_f1 = *param_2;
  tmp_f2 = param_2[1];
  tmp_f3 = param_2[2];
  PerpendicularVector(&local_60,param_2);
  tmp_f6 = tmp_f3 * local_5c - tmp_f2 * local_58;
  tmp_f5 = tmp_f1 * local_58 - tmp_f3 * local_60;
  tmp_f4 = tmp_f2 * local_60 - tmp_f1 * local_5c;
  tmp_u17 = 0;
  do {
    tmp_u18 = tmp_u17;
    *(uint32_t *)((int)local_54 + tmp_u18) = 0;
    *(uint32_t *)((int)local_54 + tmp_u18 + 4) = 0;
    tmp_u17 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x20);
  *(uint32_t *)((int)local_54 + tmp_u18 + 8) = 0;
  sincos((double)((param_4 * 3.1415927) / 180.0),local_74,&local_7c);
  tmp_f7 = (float)local_7c;
  tmp_f16 = (float)local_74[0];
  tmp_f10 = -tmp_f16;
  tmp_f8 = tmp_f6 * tmp_f10 + tmp_f7 * local_60 + tmp_f1 * 0.0;
  tmp_f9 = tmp_f7 * tmp_f6 + tmp_f16 * local_60 + tmp_f1 * 0.0;
  tmp_f15 = local_60 * 0.0 + tmp_f6 * 0.0 + tmp_f1;
  tmp_f12 = tmp_f5 * tmp_f10 + tmp_f7 * local_5c + tmp_f2 * 0.0;
  tmp_f13 = tmp_f7 * tmp_f5 + tmp_f16 * local_5c + tmp_f2 * 0.0;
  tmp_f14 = tmp_f2 + local_5c * 0.0 + tmp_f5 * 0.0;
  tmp_f11 = tmp_f10 * tmp_f4 + tmp_f7 * local_58 + tmp_f3 * 0.0;
  tmp_f10 = tmp_f7 * tmp_f4 + tmp_f16 * local_58 + tmp_f3 * 0.0;
  tmp_f7 = local_58 * 0.0 + tmp_f4 * 0.0 + tmp_f3;
  *param_1 = (tmp_f9 * tmp_f4 + tmp_f8 * local_58 + tmp_f3 * tmp_f15) * param_3[2] +
             (tmp_f2 * tmp_f15 + tmp_f5 * tmp_f9 + tmp_f8 * local_5c) * param_3[1] +
             (tmp_f1 * tmp_f15 + tmp_f6 * tmp_f9 + tmp_f8 * local_60) * *param_3;
  param_1[1] = (tmp_f14 * tmp_f3 + tmp_f13 * tmp_f4 + tmp_f12 * local_58) * param_3[2] +
               (tmp_f2 * tmp_f14 + tmp_f5 * tmp_f13 + tmp_f12 * local_5c) * param_3[1] +
               (tmp_f1 * tmp_f14 + tmp_f6 * tmp_f13 + tmp_f12 * local_60) * *param_3;
  param_1[2] = (tmp_f3 * tmp_f7 + tmp_f4 * tmp_f10 + tmp_f11 * local_58) * param_3[2] +
               (tmp_f2 * tmp_f7 + tmp_f5 * tmp_f10 + local_5c * tmp_f11) * param_3[1] +
               (tmp_f1 * tmp_f7 + tmp_f6 * tmp_f10 + local_60 * tmp_f11) * *param_3;
  return;
}

void RotateAroundDirection(float *param_1,float param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint tmp_u6;
  float tmp_f7;
  float local_18 [4];
  
  local_18[2] = 0.0;
  local_18[1] = 0.0;
  local_18[0] = 0.0;
  tmp_f4 = ABS(*param_1);
  if (1.0 <= tmp_f4) {
    tmp_f4 = 1.0;
  }
  tmp_f5 = ABS(param_1[1]);
  tmp_f7 = tmp_f4;
  if (tmp_f5 < tmp_f4) {
    tmp_f7 = tmp_f5;
  }
  tmp_u6 = 2;
  if (tmp_f7 <= ABS(param_1[2])) {
    tmp_u6 = (uint)(tmp_f5 < tmp_f4);
  }
  local_18[tmp_u6] = 1.0;
  tmp_f4 = *param_1;
  tmp_f7 = param_1[1];
  tmp_f5 = param_1[2];
  tmp_f1 = 1.0 / (tmp_f5 * tmp_f5 + tmp_f7 * tmp_f7 + tmp_f4 * tmp_f4);
  tmp_f2 = (local_18[2] * tmp_f5 + local_18[1] * tmp_f7 + local_18[0] * tmp_f4) * tmp_f1;
  tmp_f3 = local_18[0] - tmp_f4 * tmp_f1 * tmp_f2;
  param_1[3] = tmp_f3;
  tmp_f7 = local_18[1] - tmp_f7 * tmp_f1 * tmp_f2;
  param_1[4] = tmp_f7;
  tmp_f4 = local_18[2] - tmp_f1 * tmp_f5 * tmp_f2;
  param_1[5] = tmp_f4;
  tmp_f4 = tmp_f4 * tmp_f4 + tmp_f7 * tmp_f7 + tmp_f3 * tmp_f3;
  tmp_f7 = SQRT(tmp_f4);
  if (NAN(tmp_f7)) {
    tmp_f7 = sqrtf(tmp_f4);
  }
  if (tmp_f7 == 0.0) {
    local_18[0] = param_1[3];
    local_18[1] = param_1[4];
    local_18[2] = param_1[5];
  }
  else {
    tmp_f7 = 1.0 / tmp_f7;
    local_18[0] = param_1[3] * tmp_f7;
    param_1[3] = local_18[0];
    local_18[1] = param_1[4] * tmp_f7;
    param_1[4] = local_18[1];
    local_18[2] = tmp_f7 * param_1[5];
    param_1[5] = local_18[2];
  }
  if (param_2 != 0.0) {
    RotatePointAroundVector(param_1 + 3,param_1,local_18,param_2);
    local_18[2] = param_1[5];
    local_18[1] = param_1[4];
    local_18[0] = param_1[3];
  }
  param_1[6] = param_1[1] * local_18[2] - param_1[2] * local_18[1];
  param_1[7] = param_1[2] * local_18[0] - local_18[2] * *param_1;
  param_1[8] = local_18[1] * *param_1 - local_18[0] * param_1[1];
  return;
}

void GetPerpendicularViewVector(float *param_1,float *param_2,float *param_3,float *param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  
  tmp_f1 = *param_1;
  tmp_f3 = tmp_f1 - *param_2;
  tmp_f7 = param_1[1];
  tmp_f5 = tmp_f7 - param_2[1];
  tmp_f2 = param_1[2];
  tmp_f4 = tmp_f2 - param_2[2];
  tmp_f8 = tmp_f4 * tmp_f4 + tmp_f5 * tmp_f5 + tmp_f3 * tmp_f3;
  tmp_f6 = SQRT(tmp_f8);
  if (NAN(tmp_f6)) {
    tmp_f6 = sqrtf(tmp_f8);
    tmp_f1 = *param_1;
    tmp_f7 = param_1[1];
    tmp_f2 = param_1[2];
  }
  if (tmp_f6 != 0.0) {
    tmp_f6 = 1.0 / tmp_f6;
    tmp_f3 = tmp_f3 * tmp_f6;
    tmp_f5 = tmp_f5 * tmp_f6;
    tmp_f4 = tmp_f6 * tmp_f4;
  }
  tmp_f1 = tmp_f1 - *param_3;
  tmp_f7 = tmp_f7 - param_3[1];
  tmp_f2 = tmp_f2 - param_3[2];
  tmp_f6 = tmp_f2 * tmp_f2 + tmp_f7 * tmp_f7 + tmp_f1 * tmp_f1;
  tmp_f8 = SQRT(tmp_f6);
  if (NAN(tmp_f8)) {
    tmp_f8 = sqrtf(tmp_f6);
  }
  if (tmp_f8 != 0.0) {
    tmp_f8 = 1.0 / tmp_f8;
    tmp_f1 = tmp_f1 * tmp_f8;
    tmp_f7 = tmp_f7 * tmp_f8;
    tmp_f2 = tmp_f8 * tmp_f2;
  }
  tmp_f6 = tmp_f2 * tmp_f5 - tmp_f7 * tmp_f4;
  *param_4 = tmp_f6;
  tmp_f2 = tmp_f4 * tmp_f1 - tmp_f2 * tmp_f3;
  param_4[1] = tmp_f2;
  tmp_f1 = tmp_f7 * tmp_f3 - tmp_f1 * tmp_f5;
  param_4[2] = tmp_f1;
  tmp_f1 = tmp_f1 * tmp_f1 + tmp_f2 * tmp_f2 + tmp_f6 * tmp_f6;
  tmp_f7 = SQRT(tmp_f1);
  if (NAN(tmp_f7)) {
    tmp_f7 = sqrtf(tmp_f1);
  }
  if (tmp_f7 != 0.0) {
    tmp_f7 = 1.0 / tmp_f7;
    *param_4 = *param_4 * tmp_f7;
    param_4[1] = param_4[1] * tmp_f7;
    param_4[2] = tmp_f7 * param_4[2];
  }
  return;
}

void ProjectPointOntoVector(float *param_1,float *param_2,float *param_3,float *param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  float __x;
  float tmp_f9;
  float tmp_f10;
  
  tmp_f1 = *param_2;
  tmp_f9 = *param_1 - tmp_f1;
  tmp_f2 = param_1[1];
  tmp_f3 = param_2[1];
  tmp_f4 = param_1[2];
  tmp_f5 = param_2[2];
  tmp_f7 = *param_3 - tmp_f1;
  tmp_f8 = param_3[1] - param_2[1];
  tmp_f6 = param_3[2] - param_2[2];
  __x = tmp_f6 * tmp_f6 + tmp_f8 * tmp_f8 + tmp_f7 * tmp_f7;
  tmp_f10 = SQRT(__x);
  if (NAN(tmp_f10)) {
    tmp_f10 = sqrtf(__x);
    tmp_f1 = *param_2;
  }
  if (tmp_f10 != 0.0) {
    tmp_f10 = 1.0 / tmp_f10;
    tmp_f7 = tmp_f7 * tmp_f10;
    tmp_f8 = tmp_f8 * tmp_f10;
    tmp_f6 = tmp_f10 * tmp_f6;
  }
  tmp_f2 = (tmp_f4 - tmp_f5) * tmp_f6 + (tmp_f2 - tmp_f3) * tmp_f8 + tmp_f9 * tmp_f7;
  *param_4 = tmp_f7 * tmp_f2 + tmp_f1;
  param_4[1] = tmp_f8 * tmp_f2 + param_2[1];
  param_4[2] = tmp_f6 * tmp_f2 + param_2[2];
  return;
}

void ProjectPointOntoVectorBounded(float *param_1,float *param_2,float *param_3,float *param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  float __x;
  float tmp_f9;
  float tmp_f10;
  
  tmp_f1 = *param_2;
  tmp_f9 = *param_1 - tmp_f1;
  tmp_f2 = param_1[1];
  tmp_f3 = param_2[1];
  tmp_f4 = param_1[2];
  tmp_f5 = param_2[2];
  tmp_f7 = *param_3 - tmp_f1;
  tmp_f8 = param_3[1] - param_2[1];
  tmp_f6 = param_3[2] - param_2[2];
  __x = tmp_f6 * tmp_f6 + tmp_f8 * tmp_f8 + tmp_f7 * tmp_f7;
  tmp_f10 = SQRT(__x);
  if (NAN(tmp_f10)) {
    tmp_f10 = sqrtf(__x);
    tmp_f1 = *param_2;
  }
  if (tmp_f10 != 0.0) {
    tmp_f10 = 1.0 / tmp_f10;
    tmp_f7 = tmp_f7 * tmp_f10;
    tmp_f8 = tmp_f8 * tmp_f10;
    tmp_f6 = tmp_f10 * tmp_f6;
  }
  tmp_f2 = (tmp_f4 - tmp_f5) * tmp_f6 + (tmp_f2 - tmp_f3) * tmp_f8 + tmp_f9 * tmp_f7;
  tmp_f1 = tmp_f7 * tmp_f2 + tmp_f1;
  *param_4 = tmp_f1;
  param_4[1] = tmp_f8 * tmp_f2 + param_2[1];
  param_4[2] = tmp_f2 * tmp_f6 + param_2[2];
  tmp_f2 = *param_2;
  tmp_f3 = tmp_f2;
  if (((tmp_f1 <= tmp_f2) || (tmp_f4 = *param_3, tmp_f1 <= tmp_f4)) &&
     ((tmp_f2 <= tmp_f1 || (tmp_f4 = *param_3, tmp_f4 <= tmp_f1)))) {
    tmp_f1 = param_4[1];
    tmp_f3 = param_2[1];
    if (((tmp_f1 <= tmp_f3) || (tmp_f4 = param_3[1], tmp_f1 <= tmp_f4)) &&
       ((tmp_f3 <= tmp_f1 || (tmp_f4 = param_3[1], tmp_f4 <= tmp_f1)))) {
      tmp_f1 = param_4[2];
      tmp_f3 = param_2[2];
      if (((tmp_f1 <= tmp_f3) || (tmp_f4 = param_3[2], tmp_f1 <= tmp_f4)) &&
         ((tmp_f3 <= tmp_f1 || (tmp_f4 = param_3[2], tmp_f4 <= tmp_f1)))) {
        return;
      }
    }
  }
  if (ABS(tmp_f1 - tmp_f4) <= ABS(tmp_f1 - tmp_f3)) {
    *param_4 = *param_3;
    param_4[1] = param_3[1];
    param_4[2] = param_3[2];
    return;
  }
  *param_4 = tmp_f2;
  param_4[1] = param_2[1];
  param_4[2] = param_2[2];
  return;
}

long double DistanceFromLineSquared(float *param_1,float *param_2,float *param_3)
{
  long double tmp_l1;
  long double tmp_l2;
  long double tmp_l3;
  long double tmp_l4;
  long double tmp_l5;
  long double tmp_l6;
  long double tmp_l7;
  long double tmp_l8;
  long double tmp_l9;
  long double tmp_l10;
  float tmp_f11;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  
  tmp_l1 = (long double)*param_2;
  local_50 = *param_1;
  tmp_l2 = (long double)local_50 - tmp_l1;
  local_58 = param_2[1];
  tmp_l3 = (long double)local_58;
  local_4c = param_1[1];
  tmp_l4 = (long double)local_4c;
  local_54 = param_2[2];
  local_48 = param_1[2];
  tmp_l5 = (long double)local_48 - (long double)local_54;
  tmp_l6 = (long double)*param_3 - tmp_l1;
  tmp_l7 = (long double)param_3[1] - tmp_l3;
  tmp_l8 = (long double)param_3[2] - (long double)local_54;
  tmp_l10 = tmp_l8 * tmp_l8 + tmp_l7 * tmp_l7 + tmp_l6 * tmp_l6;
  tmp_l9 = SQRT(tmp_l10);
  if (NAN(tmp_l9)) {
    tmp_f11 = sqrtf((float)tmp_l10);
    tmp_l9 = (long double)tmp_f11;
    tmp_l1 = (long double)*param_2;
    local_50 = *param_1;
    local_58 = param_2[1];
    local_4c = param_1[1];
    local_54 = param_2[2];
    local_48 = param_1[2];
    tmp_l8 = (long double)(float)tmp_l8;
    tmp_l7 = (long double)(float)tmp_l7;
    tmp_l6 = (long double)(float)tmp_l6;
    tmp_l5 = (long double)(float)tmp_l5;
    tmp_l2 = (long double)(float)tmp_l2;
  }
  if (tmp_l9 != (long double)0) {
    tmp_l9 = (long double)1.0 / tmp_l9;
    tmp_l6 = tmp_l6 * tmp_l9;
    tmp_l7 = tmp_l7 * tmp_l9;
    tmp_l8 = tmp_l9 * tmp_l8;
  }
  tmp_l3 = tmp_l5 * tmp_l8 + (long double)(float)(tmp_l4 - tmp_l3) * tmp_l7 + tmp_l2 * tmp_l6;
  tmp_l9 = tmp_l6 * tmp_l3 + tmp_l1;
  tmp_l7 = tmp_l7 * tmp_l3 + (long double)local_58;
  tmp_l8 = tmp_l8 * tmp_l3 + (long double)local_54;
  tmp_l3 = tmp_l1;
  tmp_l4 = tmp_l9;
  if (((tmp_l9 <= tmp_l1) || (tmp_l6 = (long double)*param_3, tmp_l9 <= tmp_l6)) &&
     ((tmp_l1 <= tmp_l9 || (tmp_l6 = (long double)*param_3, tmp_l6 <= tmp_l9)))) {
    tmp_l4 = (long double)(float)tmp_l7;
    tmp_l3 = (long double)local_58;
    if (((tmp_l4 <= tmp_l3) || (tmp_l6 = (long double)param_3[1], tmp_l4 <= tmp_l6)) &&
       (((long double)local_58 <= tmp_l4 || (tmp_l6 = (long double)param_3[1], tmp_l6 <= tmp_l4)))) {
      tmp_l4 = (long double)(float)tmp_l8;
      tmp_l3 = (long double)local_54;
      if (((tmp_l4 <= tmp_l3) || (tmp_l6 = (long double)param_3[2], tmp_l4 <= tmp_l6)) &&
         (((long double)local_54 <= tmp_l4 || (tmp_l6 = (long double)param_3[2], tmp_l6 <= tmp_l4)))) {
        tmp_l7 = (long double)local_4c - tmp_l7;
        tmp_l8 = (long double)local_48 - tmp_l8;
        return tmp_l8 * tmp_l8 +
               tmp_l7 * tmp_l7 + ((long double)local_50 - tmp_l9) * ((long double)local_50 - tmp_l9);
      }
    }
  }
  if (ABS((float)(tmp_l4 - tmp_l3)) < ABS((float)(tmp_l4 - tmp_l6))) {
    tmp_l1 = (long double)local_50 - tmp_l1;
    tmp_l3 = (long double)local_4c - (long double)local_58;
    tmp_l4 = (long double)local_48 - (long double)local_54;
  }
  else {
    tmp_l1 = (long double)local_50 - (long double)*param_3;
    tmp_l3 = (long double)local_4c - (long double)param_3[1];
    tmp_l4 = (long double)local_48 - (long double)param_3[2];
  }
  return tmp_l4 * tmp_l4 + tmp_l3 * tmp_l3 + tmp_l1 * tmp_l1;
}

long double DistanceFromVectorSquared(float *param_1,float *param_2,float *param_3)
{
  long double tmp_l1;
  long double tmp_l2;
  long double tmp_l3;
  long double tmp_l4;
  long double tmp_l5;
  long double tmp_l6;
  long double tmp_l7;
  long double tmp_l8;
  long double tmp_l9;
  float tmp_f10;
  float local_2c;
  float local_28;
  
  local_28 = *param_1;
  tmp_l7 = (long double)local_28 - (long double)*param_2;
  local_2c = param_1[1];
  tmp_l8 = (long double)local_2c - (long double)param_2[1];
  tmp_l1 = (long double)param_1[2];
  tmp_l2 = tmp_l1 - (long double)param_2[2];
  tmp_l3 = (long double)*param_3 - (long double)*param_2;
  tmp_l4 = (long double)param_3[1] - (long double)param_2[1];
  tmp_l5 = (long double)param_3[2] - (long double)param_2[2];
  tmp_l9 = tmp_l5 * tmp_l5 + tmp_l4 * tmp_l4 + tmp_l3 * tmp_l3;
  tmp_l6 = SQRT(tmp_l9);
  if (NAN(tmp_l6)) {
    tmp_f10 = sqrtf((float)tmp_l9);
    tmp_l6 = (long double)tmp_f10;
    local_28 = *param_1;
    local_2c = param_1[1];
    tmp_l1 = (long double)param_1[2];
    tmp_l5 = (long double)(float)tmp_l5;
    tmp_l4 = (long double)(float)tmp_l4;
    tmp_l3 = (long double)(float)tmp_l3;
    tmp_l8 = (long double)(float)tmp_l8;
    tmp_l7 = (long double)(float)tmp_l7;
  }
  if (tmp_l6 != (long double)0) {
    tmp_l6 = (long double)1.0 / tmp_l6;
    tmp_l3 = tmp_l3 * tmp_l6;
    tmp_l4 = tmp_l4 * tmp_l6;
    tmp_l5 = tmp_l6 * tmp_l5;
  }
  tmp_l8 = (long double)(float)tmp_l2 * tmp_l5 + tmp_l8 * tmp_l4 + tmp_l7 * tmp_l3;
  tmp_l2 = (long double)local_28 - (tmp_l3 * tmp_l8 + (long double)*param_2);
  tmp_l6 = (long double)local_2c - (tmp_l4 * tmp_l8 + (long double)param_2[1]);
  tmp_l1 = tmp_l1 - (tmp_l8 * tmp_l5 + (long double)param_2[2]);
  return tmp_l1 * tmp_l1 + tmp_l6 * tmp_l6 + tmp_l2 * tmp_l2;
}

long double vectoyaw(float *param_1)
{
  long double tmp_l1;
  long double tmp_l2;
  double tmp_d3;
  
  tmp_l1 = (long double)param_1[1];
  tmp_l2 = (long double)*param_1;
  if (tmp_l1 == (long double)0) {
    if ((long double)0 == tmp_l2) {
      return (long double)0;
    }
  }
  else if (tmp_l2 == (long double)0) {
    if (tmp_l1 <= (long double)0) {
      return (long double)270.0;
    }
    return (long double)90.0;
  }
  tmp_d3 = atan2((double)param_1[1],(double)*param_1);
  tmp_l1 = (long double)(((float)tmp_d3 * 180.0) / 3.1415927);
  if (tmp_l1 < (long double)0) {
    tmp_l1 = tmp_l1 + (long double)360.0;
  }
  return tmp_l1;
}

void AxisToAngles(int param_1,float *param_2)
{
  float tmp_f1;
  double tmp_d2;
  float tmp_f3;
  uint8_t *tmp_pu4;
  float local_34;
  float local_30;
  float local_2c;
  uint8_t local_28 [24];
  
  vectoangles(param_1);
  tmp_pu4 = local_28;
  local_34 = *(float *)(param_1 + 0xc);
  local_30 = *(float *)(param_1 + 0x10);
  local_2c = *(float *)(param_1 + 0x14);
  RotatePointAroundVector(tmp_pu4,0x14a3d8,&local_34,-param_2[1],tmp_pu4);
  RotatePointAroundVector(&local_34,0x14a3cc,tmp_pu4,-*param_2);
  if (local_30 == 0.0) {
    if (local_34 != 0.0) {
LAB_000e8360:
      atan2((double)local_30,(double)local_34);
      goto LAB_000e8382;
    }
    if (local_2c <= 0.0) {
      tmp_f1 = 90.0;
      if (local_2c * (float)GHIDRA_FIELD(axisDefault, 20, 4) +
          local_34 * (float)GHIDRA_FIELD(axisDefault, 12, 4) + (float)GHIDRA_FIELD(axisDefault, 16, 4) * local_30 < 0.0)
      goto LAB_000e8496;
      goto LAB_000e845e;
    }
    tmp_f1 = -90.0;
  }
  else {
    if (local_34 != 0.0) goto LAB_000e8360;
LAB_000e8382:
    tmp_f1 = local_30 * local_30 + local_34 * local_34;
    tmp_f3 = SQRT(tmp_f1);
    if (NAN(tmp_f3)) {
      tmp_f3 = sqrtf(tmp_f1);
    }
    tmp_d2 = atan2((double)local_2c,(double)tmp_f3);
    tmp_f1 = ((float)tmp_d2 * 180.0) / 3.1415927;
    if (tmp_f1 < 0.0) {
      tmp_f1 = tmp_f1 + 360.0;
    }
    tmp_f1 = (float)((int)ROUND(-tmp_f1 * 182.04445) & 0xffff) * 0.005493164;
    if (180.0 < tmp_f1) {
      tmp_f1 = tmp_f1 - 360.0;
    }
  }
  if (local_2c * (float)GHIDRA_FIELD(axisDefault, 20, 4) +
      local_30 * (float)GHIDRA_FIELD(axisDefault, 16, 4) + local_34 * (float)GHIDRA_FIELD(axisDefault, 12, 4) < 0.0) {
    if (0.0 <= tmp_f1) {
LAB_000e8496:
      param_2[2] = -((90.0 - tmp_f1) + 90.0);
      return;
    }
    tmp_f1 = (-90.0 - tmp_f1) - 90.0;
  }
LAB_000e845e:
  param_2[2] = -tmp_f1;
  return;
}

long double VectorDistance(float *param_1,float *param_2)
{
  long double tmp_l1;
  long double tmp_l2;
  float tmp_f3;
  
  tmp_l2 = ((long double)param_2[1] - (long double)param_1[1]) *
          ((long double)param_2[1] - (long double)param_1[1]) +
          ((long double)*param_2 - (long double)*param_1) *
          ((long double)*param_2 - (long double)*param_1) +
          ((long double)param_2[2] - (long double)param_1[2]) *
          ((long double)param_2[2] - (long double)param_1[2]);
  tmp_l1 = SQRT(tmp_l2);
  if (NAN(tmp_l1)) {
    tmp_f3 = sqrtf((float)tmp_l2);
    tmp_l1 = (long double)tmp_f3;
  }
  return tmp_l1;
}

long double VectorDistanceSquared(float *param_1,float *param_2)
{
  return ((long double)param_2[1] - (long double)param_1[1]) *
         ((long double)param_2[1] - (long double)param_1[1]) +
         ((long double)*param_2 - (long double)*param_1) *
         ((long double)*param_2 - (long double)*param_1) +
         ((long double)param_2[2] - (long double)param_1[2]) *
         ((long double)param_2[2] - (long double)param_1[2]);
}

void LerpColor(float *param_1,float *param_2,float *param_3,float param_4)
{
  float tmp_f1;
  
  tmp_f1 = (*param_2 - *param_1) * param_4 + *param_1;
  if (tmp_f1 < 0.0) {
    *param_3 = 0.0;
  }
  else {
    if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    *param_3 = tmp_f1;
  }
  tmp_f1 = (param_2[1] - param_1[1]) * param_4 + param_1[1];
  if (tmp_f1 < 0.0) {
    param_3[1] = 0.0;
  }
  else {
    if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    param_3[1] = tmp_f1;
  }
  tmp_f1 = (param_2[2] - param_1[2]) * param_4 + param_1[2];
  if (tmp_f1 < 0.0) {
    param_3[2] = 0.0;
  }
  else {
    if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    param_3[2] = tmp_f1;
  }
  tmp_f1 = param_1[3] + (param_2[3] - param_1[3]) * param_4;
  if (0.0 <= tmp_f1) {
    if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    param_3[3] = tmp_f1;
    return;
  }
  param_3[3] = 0.0;
  return;
}

