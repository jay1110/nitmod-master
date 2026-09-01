/* Missiles, impacts and visual effects — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_effects.h"

void CG_Bleed(float *param_1,int param_2)
{
  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  float *pfVar4;
  float *pfVar5;
  long double tmp_l6;
  long double tmp_l7;
  long double tmp_l8;
  int local_94;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28 [3];
  float local_1c [2];
  uint32_t uStack_14;
  
  uStack_14 = 0x62859;
  if ((GHIDRA_FIELD(cg_gibs, 12, 4) != 0) && (*(int *)(g_unk_01047b00 + 0xcc) != param_2)) {
    CG_GetBleedOrigin(&local_64,&local_58,param_2);
    ProjectPointOntoVector(param_1,&local_58,&local_64,&local_4c);
    local_34 = local_64 - local_58;
    local_30 = local_60 - local_54;
    local_2c = local_5c - local_50;
    if ((local_44 - local_50) * local_2c +
        (local_48 - local_54) * local_30 + (local_4c - local_58) * local_34 < 0.0) {
      local_4c = local_58;
      local_48 = local_54;
      local_44 = local_50;
    }
    else if (0.0 < local_34 * (local_4c - local_64) + (local_48 - local_60) * local_30 +
                   (local_44 - local_5c) * local_2c) {
      local_4c = local_64;
      local_48 = local_60;
      local_44 = local_5c;
    }
    local_40 = *param_1 - local_4c;
    local_3c = param_1[1] - local_48;
    local_38 = param_1[2] - local_44;
    VectorNormalize(&local_40);
    local_34 = local_4c - local_64;
    local_30 = local_48 - local_60;
    local_2c = local_44 - local_5c;
    tmp_l6 = (long double)VectorLength(&local_34);
    tmp_l7 = (long double)8.0;
    tmp_l8 = (long double)local_40;
    if (tmp_l7 < tmp_l6) {
      local_4c = (float)(tmp_l8 * tmp_l7 + (long double)local_4c);
      local_48 = (float)((long double)local_3c * tmp_l7 + (long double)local_48);
      local_44 = (float)(tmp_l7 * (long double)local_38 + (long double)local_44);
    }
    local_94 = 4;
    while( true ) {
      local_28[0] = (float)tmp_l8;
      local_28[1] = local_3c;
      local_28[2] = local_38;
      pfVar4 = local_28;
      do {
        tmp_u2 = rand();
        pfVar5 = pfVar4 + 1;
        tmp_f1 = (float)(tmp_u2 & 0x7fff) / 32767.0 - 0.5;
        *pfVar4 = (tmp_f1 + tmp_f1) * 0.3 + *pfVar4;
        pfVar4 = pfVar5;
      } while (pfVar5 != local_1c);
      VectorNormalize(local_28);
      tmp_i3 = rand();
      tmp_u2 = rand();
      tmp_f1 = (float)(tmp_u2 & 0x7fff) / 32767.0 - 0.5;
      CG_AddBloodTrails(&local_4c,local_28,100,(int)ROUND((tmp_f1 + tmp_f1) * 50.0) + 0x1c2,
                        tmp_i3 % 2 + 2,0x3dcccccd);
      local_94 = local_94 + -1;
      if (local_94 == 0) break;
      tmp_l8 = (long double)local_40;
    }
  }
  return;
}

void CG_LaunchGib(uint32_t *param_1,uint32_t *param_2,uint32_t *param_3,uint32_t *param_4,
                 int param_5,float param_6,uint32_t param_7)

{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  uint tmp_u4;
  int tmp_i5;
  long double tmp_l6;
  uint8_t local_34 [12];
  uint8_t local_28 [24];
  
  if (GHIDRA_FIELD(cg_gibs, 12, 4) != 0) {
    tmp_i3 = CG_AllocLocalEntity();
    *(uint32_t *)(tmp_i3 + 8) = 3;
    tmp_i5 = g_unk_010906e0;
    *(int *)(tmp_i3 + 0x10) = g_unk_010906e0;
    tmp_u4 = rand();
    tmp_f1 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
    *(int *)(tmp_i3 + 0x14) = (int)ROUND((tmp_f1 + tmp_f1) * 5000.0 + (float)(tmp_i5 + 40000));
    *(uint32_t *)(tmp_i3 + 0x1ac) = param_7;
    *(float *)(tmp_i3 + 0x1b0) = param_6;
    *(uint32_t *)(tmp_i3 + 0x50) = *param_3;
    *(uint32_t *)(tmp_i3 + 0x54) = param_3[1];
    *(uint32_t *)(tmp_i3 + 0x58) = param_3[2];
    *(uint32_t *)(tmp_i3 + 0x100) = *param_2;
    *(uint32_t *)(tmp_i3 + 0x104) = param_2[1];
    *(uint32_t *)(tmp_i3 + 0x108) = param_2[2];
    AnglesToAxis(param_3,tmp_i3 + 0xb4);
    if (param_6 != 1.0) {
      *(float *)(tmp_i3 + 0xcc) = *(float *)(tmp_i3 + 0xcc) * param_6;
      *(float *)(tmp_i3 + 0xd0) = *(float *)(tmp_i3 + 0xd0) * param_6;
      *(float *)(tmp_i3 + 0xd4) = *(float *)(tmp_i3 + 0xd4) * param_6;
      *(float *)(tmp_i3 + 0xc0) = *(float *)(tmp_i3 + 0xc0) * param_6;
      *(float *)(tmp_i3 + 0xc4) = *(float *)(tmp_i3 + 0xc4) * param_6;
      *(float *)(tmp_i3 + 200) = *(float *)(tmp_i3 + 200) * param_6;
      *(float *)(tmp_i3 + 0xb4) = *(float *)(tmp_i3 + 0xb4) * param_6;
      *(float *)(tmp_i3 + 0xb8) = *(float *)(tmp_i3 + 0xb8) * param_6;
      *(float *)(tmp_i3 + 0xbc) = *(float *)(tmp_i3 + 0xbc) * param_6;
    }
    *(int *)(tmp_i3 + 0xa0) = param_5;
    if (param_5 != 0) {
      trap_R_ModelBounds(param_5,local_28,local_34);
      tmp_l6 = (long double)RadiusFromBounds(local_28,local_34);
      tmp_l6 = tmp_l6 / (long double)10.0;
      if ((long double)0 < tmp_l6) {
        if (tmp_l6 < (long double)0.2) {
          tmp_l6 = (long double)0.2;
        }
        else if ((long double)5.0 < tmp_l6) {
          tmp_l6 = (long double)5.0;
        }
        *(uint32_t *)(tmp_i3 + 0x20) = 6;
        tmp_f1 = (float)tmp_l6;
        *(int *)(tmp_i3 + 0x170) = *(int *)(tmp_i3 + 0x14) + -1000;
        *(int *)(tmp_i3 + 0x174) = *(int *)(tmp_i3 + 0x14);
        *(uint32_t *)(tmp_i3 + 0x90) = 1;
        *(uint32_t *)(tmp_i3 + 0x94) = 1;
        tmp_u4 = rand();
        *(float *)(tmp_i3 + 0x5c) = (float)(int)((tmp_u4 & 0x32) - 0x14) / tmp_f1;
        tmp_u4 = rand();
        *(float *)(tmp_i3 + 0x60) = (float)(int)((tmp_u4 & 500) - 200) / tmp_f1;
        tmp_u4 = rand();
        *(float *)(tmp_i3 + 100) = (float)(int)((tmp_u4 & 0x32) - 0x14) / tmp_f1;
        tmp_f1 = 0.5 - tmp_f1 / 10.0;
        tmp_f2 = 0.0;
        if (0.0 <= tmp_f1) {
          tmp_f2 = tmp_f1;
        }
        *(float *)(tmp_i3 + 0x68) = tmp_f2;
        *(uint32_t *)(tmp_i3 + 0x2c) = *param_2;
        *(uint32_t *)(tmp_i3 + 0x30) = param_2[1];
        *(uint32_t *)(tmp_i3 + 0x34) = param_2[2];
        *(uint32_t *)(tmp_i3 + 0x38) = *param_4;
        *(uint32_t *)(tmp_i3 + 0x3c) = param_4[1];
        *(uint32_t *)(tmp_i3 + 0x40) = param_4[2];
        tmp_i5 = g_unk_010906e0;
        *(uint32_t *)(tmp_i3 + 0x44) = 2;
        *(int *)(tmp_i3 + 0x24) = tmp_i5;
        *(int *)(tmp_i3 + 0x48) = g_unk_010906e0;
        *(uint32_t *)(tmp_i3 + 0x1a4) = *param_1;
        tmp_i5 = CG_EntOnFire(param_1);
        if (tmp_i5 == 0) {
          return;
        }
        *(uint32_t *)(tmp_i3 + 0x19c) = param_1[0x3f];
        *(int *)(tmp_i3 + 0x1a0) = *(int *)(tmp_i3 + 0x174) + 1000;
        return;
      }
    }
    CG_FreeLocalEntity(tmp_i3);
  }
  return;
}

void CG_GibPlayer(uint32_t *param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  bool tmp_b5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  float tmp_f9;
  uint tmp_u10;
  uint tmp_u11;
  int tmp_i12;
  uint tmp_u13;
  int tmp_i14;
  uint32_t tmp_u15;
  int tmp_i16;
  uint tmp_u17;
  float *pfVar18;
  int tmp_i19;
  long double tmp_l20;
  int local_218;
  float *local_210;
  int local_208;
  float *local_204;
  int local_1f4;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  float local_190;
  uint32_t local_18c;
  uint32_t local_188;
  uint32_t local_184;
  uint32_t local_180;
  uint32_t local_17c;
  uint32_t local_178;
  uint32_t local_174;
  uint32_t local_170;
  uint32_t local_16c;
  uint32_t local_168;
  uint32_t local_164;
  int local_160 [16];
  uint32_t auStack_120 [8];
  uint8_t local_100 [36];
  int local_dc [10];
  float local_b4;
  float local_b0;
  float local_ac;
  uint8_t local_a8 [44];
  float local_7c [21];
  float local_28 [5];
  uint32_t uStack_14;
  
  tmp_u10 = 0;
  uStack_14 = 0x6355b;
  do {
    *(uint32_t *)((int)local_160 + tmp_u10 + 0x20) =
         *(uint32_t *)((int)&g_ptr_s_tag_footright_00143f80 + tmp_u10);
    tmp_u10 = tmp_u10 + 4;
  } while (tmp_u10 < 0x20);
  tmp_u10 = 0;
  do {
    *(uint32_t *)((int)auStack_120 + tmp_u10) =
         *(uint32_t *)((int)&g_ptr_s_tag_legright_00143fa0 + tmp_u10);
    tmp_u10 = tmp_u10 + 4;
  } while (tmp_u10 < 0x20);
  tmp_u10 = 0;
  do {
    *(uint32_t *)((int)local_dc + tmp_u10) =
         *(uint32_t *)((int)&g_ptr_s_tag_footright_00143fc0 + tmp_u10);
    tmp_u10 = tmp_u10 + 4;
  } while (tmp_u10 < 0x28);
  tmp_u10 = param_1[0x2b];
  if (0x3f < tmp_u10) {
    CG_Error("Bad clientNum on player entity");
  }
  if (GHIDRA_FIELD(cg_gibs, 12, 4) == 0) {
LAB_00063b38:
    if (((*(byte *)((int)param_1 + 9) & 0x10) == 0) &&
       ((*(byte *)((int)param_1 + 0xe5) & 0x10) != 0)) {
      tmp_u15 = tv(0,0,0x3f800000);
      CG_LoseACC(param_1,tmp_u15,6,"tag_mouth",1);
    }
    return;
  }
  tmp_u11 = 0;
  do {
    *(uint32_t *)((int)local_160 + tmp_u11) = 0;
    *(uint32_t *)((int)local_160 + tmp_u11 + 4) = 0;
    tmp_u11 = tmp_u11 + 8;
  } while (tmp_u11 < 0x20);
  tmp_i12 = CG_CharacterForClientinfo(tmp_u10 * 0x1a4 + 0x10f926c,param_1);
  local_218 = local_dc[0];
  if (local_dc[0] == 0) {
    local_1f4 = 0;
  }
  else {
    local_208 = 0;
    local_1f4 = 0;
    do {
      if (*(int *)(tmp_i12 + 0x7a8 + local_208 * 4) == 0) break;
      local_210 = (float *)trap_R_LerpTag(&local_b4,param_1 + 0x11e,local_218,0);
      if ((int)local_210 < 0) break;
      do {
        local_1a4 = (float)param_1[299] * local_ac +
                    local_b0 * (float)param_1[0x128] +
                    local_b4 * (float)param_1[0x125] + (float)param_1[0x138];
        local_1a0 = (float)param_1[300] * local_ac +
                    (float)param_1[0x129] * local_b0 +
                    (float)param_1[0x126] * local_b4 + (float)param_1[0x139];
        local_19c = local_ac * (float)param_1[0x12d] +
                    (float)param_1[0x12a] * local_b0 +
                    (float)param_1[0x127] * local_b4 + (float)param_1[0x13a];
        MatrixMultiply(local_a8,param_1 + 0x125,local_100);
        local_198 = local_1a4 - (float)param_1[0x138];
        local_194 = local_1a0 - (float)param_1[0x139];
        local_190 = local_19c - (float)param_1[0x13a];
        VectorNormalize(&local_198);
        tmp_f7 = local_198;
        tmp_u10 = rand();
        tmp_f8 = local_194;
        tmp_u11 = rand();
        tmp_f9 = local_190;
        tmp_u13 = rand();
        tmp_f1 = *param_3;
        tmp_f2 = param_3[1];
        tmp_f3 = param_3[2];
        AxisToAngles(local_100,&local_18c);
        tmp_i19 = *(int *)(tmp_i12 + 0x7a8 + local_208 * 4);
        if (GHIDRA_FIELD(cg_gibs, 12, 4) != 0) {
          tmp_i16 = CG_AllocLocalEntity();
          *(uint32_t *)(tmp_i16 + 8) = 3;
          tmp_i14 = g_unk_010906e0;
          *(int *)(tmp_i16 + 0x10) = g_unk_010906e0;
          tmp_u17 = rand();
          tmp_f4 = (float)(tmp_u17 & 0x7fff) / 32767.0 - 0.5;
          *(int *)(tmp_i16 + 0x14) = (int)ROUND((tmp_f4 + tmp_f4) * 5000.0 + (float)(tmp_i14 + 40000));
          *(uint32_t *)(tmp_i16 + 0x1ac) = 0;
          *(uint32_t *)(tmp_i16 + 0x1b0) = 0x3f800000;
          *(uint32_t *)(tmp_i16 + 0x50) = local_18c;
          *(uint32_t *)(tmp_i16 + 0x54) = local_188;
          *(uint32_t *)(tmp_i16 + 0x58) = local_184;
          *(float *)(tmp_i16 + 0x100) = local_1a4;
          *(float *)(tmp_i16 + 0x104) = local_1a0;
          *(float *)(tmp_i16 + 0x108) = local_19c;
          AnglesToAxis(&local_18c,tmp_i16 + 0xb4);
          *(int *)(tmp_i16 + 0xa0) = tmp_i19;
          if (tmp_i19 != 0) {
            trap_R_ModelBounds(tmp_i19,&local_b4,&local_170);
            tmp_l20 = (long double)RadiusFromBounds(&local_b4,&local_170);
            tmp_l20 = tmp_l20 / (long double)10.0;
            if ((long double)0 < tmp_l20) {
              if (tmp_l20 < (long double)0.2) {
                tmp_l20 = (long double)0.2;
              }
              else if ((long double)5.0 < tmp_l20) {
                tmp_l20 = (long double)5.0;
              }
              *(uint32_t *)(tmp_i16 + 0x94) = 1;
              tmp_f4 = (float)tmp_l20;
              *(uint32_t *)(tmp_i16 + 0x20) = 6;
              *(int *)(tmp_i16 + 0x174) = *(int *)(tmp_i16 + 0x14);
              *(int *)(tmp_i16 + 0x170) = *(int *)(tmp_i16 + 0x14) + -1000;
              *(uint32_t *)(tmp_i16 + 0x90) = 1;
              tmp_u17 = rand();
              *(float *)(tmp_i16 + 0x5c) = (float)(int)((tmp_u17 & 0x32) - 0x14) / tmp_f4;
              tmp_u17 = rand();
              *(float *)(tmp_i16 + 0x60) = (float)(int)((tmp_u17 & 500) - 200) / tmp_f4;
              tmp_u17 = rand();
              *(float *)(tmp_i16 + 100) = (float)(int)((tmp_u17 & 0x32) - 0x14) / tmp_f4;
              tmp_f4 = 0.5 - tmp_f4 / 10.0;
              tmp_f6 = 0.0;
              if (0.0 <= tmp_f4) {
                tmp_f6 = tmp_f4;
              }
              *(float *)(tmp_i16 + 0x68) = tmp_f6;
              *(float *)(tmp_i16 + 0x2c) = local_1a4;
              *(float *)(tmp_i16 + 0x30) = local_1a0;
              *(float *)(tmp_i16 + 0x34) = local_19c;
              *(float *)(tmp_i16 + 0x38) =
                   tmp_f1 * 75.0 + ((float)(tmp_u10 & 0x7fff) / 32767.0 + 0.5) * tmp_f7 * 75.0 * 0.3;
              *(float *)(tmp_i16 + 0x3c) =
                   tmp_f2 * 75.0 + ((float)(tmp_u11 & 0x7fff) / 32767.0 + 0.5) * tmp_f8 * 75.0 * 0.3;
              *(float *)(tmp_i16 + 0x40) =
                   tmp_f3 * 75.0 +
                   ((float)(tmp_u13 & 0x7fff) / 32767.0 + 0.5) * tmp_f9 * 75.0 * 0.3 + 165.0;
              tmp_i19 = g_unk_010906e0;
              *(uint32_t *)(tmp_i16 + 0x44) = 2;
              *(int *)(tmp_i16 + 0x24) = tmp_i19;
              *(int *)(tmp_i16 + 0x48) = g_unk_010906e0;
              *(uint32_t *)(tmp_i16 + 0x1a4) = *param_1;
              tmp_i19 = CG_EntOnFire(param_1);
              if (tmp_i19 != 0) {
                *(uint32_t *)(tmp_i16 + 0x19c) = param_1[0x3f];
                *(int *)(tmp_i16 + 0x1a0) = *(int *)(tmp_i16 + 0x174) + 1000;
              }
              goto LAB_0006388f;
            }
          }
          CG_FreeLocalEntity(tmp_i16);
        }
LAB_0006388f:
        tmp_i19 = 0;
        pfVar18 = local_7c;
        do {
          tmp_i14 = Q_stricmp(local_218,local_160[tmp_i19 + 8]);
          if (tmp_i14 == 0) {
            *pfVar18 = local_1a4;
            pfVar18[1] = local_1a0;
            local_160[tmp_i19] = 1;
            pfVar18[2] = local_19c;
          }
          tmp_i19 = tmp_i19 + 1;
          pfVar18 = pfVar18 + 3;
        } while (tmp_i19 != 8);
        local_1f4 = local_1f4 + 1;
        local_210 = (float *)trap_R_LerpTag(&local_b4,param_1 + 0x11e,local_218,(int)local_210 + 1);
      } while (-1 < (int)local_210);
      local_208 = local_208 + 1;
      local_218 = local_dc[local_208];
    } while (local_218 != 0);
  }
  local_204 = &local_b4;
  tmp_i12 = 7;
  local_210 = local_28;
  do {
    while (local_160[tmp_i12] != 1) {
      tmp_i12 = tmp_i12 + -1;
      local_210 = local_210 + -3;
      if (tmp_i12 == -1) goto LAB_000639ee;
    }
    tmp_u15 = auStack_120[tmp_i12];
    tmp_i19 = 7;
    pfVar18 = local_28;
    do {
      tmp_i14 = Q_stricmp(local_160[tmp_i19 + 8],tmp_u15);
      if ((tmp_i14 == 0) && (local_160[tmp_i19] == 1)) {
        local_198 = *local_210 - *pfVar18;
        local_194 = local_210[1] - pfVar18[1];
        local_190 = local_210[2] - pfVar18[2];
        CG_ParticleBloodCloud(param_1,local_210,&local_198);
      }
      tmp_i19 = tmp_i19 + -1;
      pfVar18 = pfVar18 + -3;
    } while (tmp_i19 != -1);
    local_210 = local_210 + -3;
    tmp_i12 = tmp_i12 + -1;
  } while (tmp_i12 != -1);
LAB_000639ee:
  tmp_u10 = 5;
  do {
    tmp_u11 = rand();
    tmp_f2 = (((float)(tmp_u11 & 0x7fff) / 32767.0) * 40.0 + 40.0) *
            (float)(int)((tmp_u10 & 1) * 2 + -1);
    tmp_u11 = rand();
    local_1a0 = (((float)(tmp_u11 & 0x7fff) / 32767.0) * 40.0 + 40.0) *
                (float)(int)((tmp_u10 & 2) - 1);
    tmp_f1 = 40.0;
    if (2 < (int)tmp_u10) {
      tmp_f1 = -40.0;
    }
    while( true ) {
      local_1a4 = tmp_f2 + *param_2;
      local_1a0 = local_1a0 + param_2[1];
      local_19c = tmp_f1 + param_2[2];
      CG_Trace(local_204,param_2,0,0,&local_1a4,0xffffffff,1);
      if (local_ac < 1.0) {
        local_180 = 0;
        local_17c = 0;
        local_178 = 0xbf800000;
        tmp_i19 = GHIDRA_FIELD(cg_bloodTime, 12, 4) * 1000;
        local_174 = 0x41f00000;
        local_170 = 0x3f800000;
        local_16c = 0x3f800000;
        local_168 = 0x3f800000;
        local_164 = 0x3f800000;
        tmp_i12 = rand();
        trap_R_ProjectDecal(*(uint32_t *)(cgs + (tmp_i12 % 5) * 4 + 0x10ca4),1,local_a8,&local_180,
                            &local_170,tmp_i19,tmp_i19 >> 4);
        tmp_b5 = 3 < local_1f4;
        local_1f4 = local_1f4 + 1;
        if (tmp_b5) goto LAB_00063b38;
      }
      tmp_u10 = tmp_u10 - 1;
      if (tmp_u10 == 0xffffffff) goto LAB_00063b38;
      tmp_f1 = -64.0;
      if (tmp_u10 != 0) break;
      tmp_f2 = 0.0;
      local_1a0 = 0.0;
    }
  } while( true );
}

void CG_Missile(int param_1)
{
  uint tmp_u1;
  float *pfVar2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  bool tmp_b8;
  bool tmp_b9;
  long double tmp_l10;
  uint *local_138;
  uint8_t *local_134;
  int local_128;
  float local_114;
  float local_110;
  float local_10c;
  uint local_108 [5];
  float local_f4;
  uint8_t local_ec [8];
  uint32_t local_e4;
  uint32_t local_a0;
  uint32_t local_9c;
  float local_98;
  uint32_t local_84;
  uint32_t local_80;
  float local_7c;
  uint local_60;
  uint32_t local_5c;
  uint32_t local_58;
  
  tmp_i7 = *(int *)(param_1 + 0xe8);
  if (tmp_i7 < 0x35) {
    *(uint32_t *)(param_1 + 0x7a0) = *(uint32_t *)(param_1 + 0x74);
    local_134 = cg_weapons + tmp_i7 * 0x17ac;
    *(uint32_t *)(param_1 + 0x7a4) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x7a8) = *(uint32_t *)(param_1 + 0x7c);
    if ((tmp_i7 - 0x32U < 2) || (tmp_i7 == 0x1c)) {
      CG_RenderSmokeGrenadeSmoke(param_1,local_134);
      goto LAB_00065a7f;
    }
    if (tmp_i7 == 0x1a) {
      if (*(int *)(param_1 + 0xac) == *(int *)(g_unk_01047b00 + 0xcc)) {
        g_unk_010b4530 = param_1;
      }
      goto LAB_00065a7f;
    }
    if (tmp_i7 == 0xd) {
      if ((*(int *)(param_1 + 0x90) != 0) &&
         (*(int *)(param_1 + 0x108) == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) {
        (&g_unk_010b4578)[*(int *)(param_1 + 0xac) * 3] = *(uint32_t *)(param_1 + 0x794);
        tmp_i6 = g_unk_010906e0;
        (&g_unk_010b457c)[*(int *)(param_1 + 0xac) * 3] = *(uint32_t *)(param_1 + 0x798);
        (&g_unk_010b4580)[*(int *)(param_1 + 0xac) * 3] = *(uint32_t *)(param_1 + 0x79c);
        (&g_unk_010b4878)[*(int *)(param_1 + 0xac)] = tmp_i6;
      }
      goto LAB_00065a7f;
    }
    if (*(int *)(param_1 + 4) - 0x15U < 4) goto LAB_00065d8d;
LAB_00065a8e:
    if (*(void **)(cg_weapons + tmp_i7 * 0x17ac + 0x1734) != (void *)0x0) {
      (**(void **)(cg_weapons + tmp_i7 * 0x17ac + 0x1734))(param_1,local_134);
    }
  }
  else {
    *(uint32_t *)(param_1 + 0xe8) = 0;
    local_134 = cg_weapons;
    tmp_i7 = 0;
    *(uint32_t *)(param_1 + 0x7a0) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x7a4) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x7a8) = *(uint32_t *)(param_1 + 0x7c);
LAB_00065a7f:
    if (3 < *(int *)(param_1 + 4) - 0x15U) goto LAB_00065a8e;
LAB_00065d8d:
    CG_RocketTrail(param_1,0);
  }
  if (*(float *)(cg_weapons + tmp_i7 * 0x17ac + 0x1738) != 0.0) {
    tmp_i6 = tmp_i7 * 0x17ac;
    trap_R_AddLightToScene
              (param_1 + 0x794,*(float *)(cg_weapons + tmp_i7 * 0x17ac + 0x1738),0x3f800000,
               *(uint32_t *)(cg_weapons + tmp_i6 + 0x173c),
               *(uint32_t *)(cg_weapons + tmp_i6 + 0x1740),
               *(uint32_t *)(cg_weapons + tmp_i6 + 0x1744),0,0);
  }
  if (*(int *)(cg_weapons + tmp_i7 * 0x17ac + 0x1730) == 0) {
    tmp_i6 = *(int *)(param_1 + 0xe8);
joined_r0x00065e22:
    if (tmp_i6 == 0xf) {
      local_138 = local_108;
      tmp_u1 = *(uint *)(param_1 + 0x108);
      if ((int)tmp_u1 < 4) {
        BG_EvaluateTrajectoryDelta(param_1 + 0xc,g_unk_010906e0,local_138,0,0xffffffff);
        trap_S_AddLoopingSound
                  (param_1 + 0x794,local_138,*(uint32_t *)(cg_weapons + tmp_i7 * 0x17ac + 0x1768),
                   0xff,0);
        tmp_u1 = *(uint *)(param_1 + 0x108);
        if (((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3) && ((tmp_u1 & 3) != 0)) &&
           (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95a8) != 0)) {
          tmp_u3 = va(&g_unk_0011cbd7,0x1e - (g_unk_010906e0 - *(int *)(param_1 + 0x10c)) / 1000);
          CG_PlayerFloatText(param_1,tmp_u3,0x14);
          tmp_u1 = *(uint *)(param_1 + 0x108);
        }
      }
      tmp_i6 = *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4;
      if (((int)tmp_u1 % 4 == *(int *)(cgs + tmp_i6 + 0x9494)) ||
         (((cgs[tmp_i6 + 0x9590] & 0x20) != 0 && (*(int *)(cgs + tmp_i6 + 0x94b8) == 2)))) {
        CG_ScanForCrosshairDynamite(param_1);
      }
    }
  }
  else {
    if (1 < *(int *)(param_1 + 0xe8) - 0x24U) {
      BG_EvaluateTrajectoryDelta(param_1 + 0xc,g_unk_010906e0,local_108,0,0xffffffff);
      tmp_i6 = 0xff;
      tmp_i4 = *(int *)(cg_weapons + tmp_i7 * 0x17ac + 0x1730);
LAB_00065dff:
      local_138 = local_108;
      trap_S_AddLoopingSound(param_1 + 0x794,local_138,tmp_i4,tmp_i6,0);
      tmp_i6 = *(int *)(param_1 + 0xe8);
      goto joined_r0x00065e22;
    }
    if ((*(int *)(param_1 + 0x10c) == 0) &&
       (tmp_i4 = g_unk_010906e0 - *(int *)(param_1 + 0x10), 300 < tmp_i4)) {
      tmp_i6 = 0xff;
      if (tmp_i4 < 0x178) {
        tmp_i6 = (int)ROUND((75.0 / ((float)tmp_i4 - 300.0)) * 255.0);
      }
      BG_EvaluateTrajectoryDelta(param_1 + 0xc,g_unk_010906e0,local_108,0,0xffffffff);
      tmp_i4 = *(int *)(cg_weapons + tmp_i7 * 0x17ac + 0x1730);
      goto LAB_00065dff;
    }
  }
  local_138 = local_108;
  tmp_u1 = 0;
  do {
    *(uint32_t *)((int)local_138 + tmp_u1) = 0;
    *(uint32_t *)((int)local_108 + tmp_u1 + 4) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0xe8);
  tmp_u3 = *(uint32_t *)(param_1 + 0x794);
  *(uint32_t *)((int)local_138 + tmp_u1) = 0;
  local_9c = *(uint32_t *)(param_1 + 0x798);
  local_98 = *(float *)(param_1 + 0x79c);
  local_60 = cg & 1;
  tmp_i6 = *(int *)(param_1 + 4);
  local_a0 = tmp_u3;
  local_84 = tmp_u3;
  local_80 = local_9c;
  local_7c = local_98;
  if ((tmp_i6 == 0x15) || (tmp_i6 == 0x1a)) {
    tmp_i4 = CG_GetGameModel(*(uint32_t *)(param_1 + 0xa4));
LAB_0006622e:
    tmp_i5 = *(int *)(param_1 + 0xe8);
    tmp_b8 = tmp_i5 == 0x19;
    local_108[2] = tmp_i4;
LAB_00066240:
    tmp_b9 = tmp_i5 == 0x33;
  }
  else {
    tmp_i4 = GHIDRA_FIELD(cgs, 68812, 4);
    if (tmp_i6 == 0x14) goto LAB_0006622e;
    tmp_i5 = *(int *)(param_1 + 0xe8);
    tmp_b8 = tmp_i5 == 0x19;
    if (tmp_i6 - 0x16U < 3) goto LAB_00066240;
    tmp_b9 = tmp_i5 == 0x33;
    local_128 = *(int *)(param_1 + 0x108);
    if ((tmp_i5 == 0xf || tmp_b8) || (tmp_b9)) {
      local_128 = local_128 % 4;
    }
    tmp_i6 = tmp_i7 * 0x17ac;
    local_108[2] = *(uint *)(cg_weapons + tmp_i6 + 0x171c);
    if (local_128 == 2) {
      local_5c = *(uint32_t *)(cg_weapons + tmp_i6 + 0x1728);
      if (*(int *)(cg_weapons + tmp_i6 + 0x1790) != 0) {
        local_108[2] = *(uint *)(cg_weapons + tmp_i6 + 0x1724);
      }
    }
    else if ((local_128 == 1) &&
            (local_5c = *(uint32_t *)(cg_weapons + tmp_i6 + 0x172c),
            *(int *)(cg_weapons + tmp_i6 + 0x1794) != 0)) {
      local_108[2] = *(uint *)(cg_weapons + tmp_i6 + 0x1720);
    }
  }
  local_108[1] = *(uint *)(cg_weapons + tmp_i7 * 0x17ac + 0x1748) | 0x10;
  if ((!tmp_b9) && (!tmp_b8)) goto LAB_00065c3c;
  tmp_i6 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
  if ((tmp_i6 == 3) && (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95a8) == 0)) {
    return;
  }
  local_108[3] = local_a0;
  local_108[1] = *(uint *)(cg_weapons + tmp_i7 * 0x17ac + 0x1748) | 0x30;
  tmp_i7 = *(int *)(param_1 + 0x108);
  local_108[4] = local_9c;
  local_f4 = local_98;
  if (tmp_i7 < 4) {
    local_98 = local_98 - 8.0;
    local_7c = local_7c - 8.0;
    if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) ==
        ~-(uint)(*(int *)(param_1 + 0x90) == 0) + 2) {
      if ((tmp_i6 != 3) || (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95a8) == 0)) {
        CG_ScanForCrosshairMine(param_1);
        goto LAB_00066408;
      }
LAB_000666b8:
      Nit_SpecMines(param_1,local_138);
      tmp_i7 = *(int *)(param_1 + 0x108);
      tmp_i5 = *(int *)(param_1 + 0xe8);
      goto LAB_00066442;
    }
    if (*(int *)(g_unk_01047b00 + 0xcc) == *(int *)(param_1 + 0xf4) + -1) {
      local_58 = GHIDRA_FIELD(cgs, 68892, 4);
      goto LAB_00065c3c;
    }
    if (tmp_i6 == 3) {
      if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95a8) != 0) goto LAB_000666b8;
      if (*(int *)(param_1 + 0xa8) == 0) {
        return;
      }
LAB_00066408:
      CG_DrawMineMarkerFlag_isra_0(*(uint32_t *)(local_134 + 0x1694),local_134 + 0x1698);
      tmp_i7 = *(int *)(param_1 + 0x108);
LAB_00066431:
      tmp_i5 = *(int *)(param_1 + 0xe8);
      goto LAB_00066442;
    }
    if (*(int *)(param_1 + 0xa8) != 0) goto LAB_00066408;
    if ((cgs[g_unk_01047ac4 * 0x1a4 + 0x958c] & 0x10) == 0) {
      return;
    }
    tmp_l10 = (long double)DistanceSquared(param_1 + 0x794,&g_unk_0109143c);
    if ((long double)65536.0 < tmp_l10) {
      return;
    }
    if ((g_unk_010ef1dc & 0x10) == 0) {
      tmp_i5 = *(int *)(param_1 + 0xe8);
      local_58 = GHIDRA_FIELD(cgs, 68892, 4);
      tmp_i7 = *(int *)(param_1 + 0x108);
      goto LAB_00066442;
    }
    tmp_i7 = *(int *)(param_1 + 0x108);
    if (tmp_i7 != 1) {
      if (tmp_i7 == 2) {
        tmp_i5 = *(int *)(param_1 + 0xe8);
        local_58 = GHIDRA_FIELD(cgs, 131924, 4);
        goto LAB_00065c3c;
      }
      goto LAB_00066431;
    }
    tmp_i5 = *(int *)(param_1 + 0xe8);
    local_58 = GHIDRA_FIELD(cgs, 131916, 4);
  }
  else {
LAB_00066442:
    if (7 < tmp_i7) {
      local_98 = local_98 - 8.0;
      local_7c = local_7c - 8.0;
    }
  }
LAB_00065c3c:
  if ((tmp_i5 == 5 || tmp_i5 == 0x2a) || (tmp_i5 - 0x24U < 2)) {
    tmp_i7 = VectorCompare(param_1 + 0x77c,&vec3_origin);
    if (tmp_i7 == 0) {
      local_114 = *(float *)(param_1 + 0x794) - *(float *)(param_1 + 0x77c);
      local_110 = *(float *)(param_1 + 0x798) - *(float *)(param_1 + 0x780);
      local_10c = *(float *)(param_1 + 0x79c) - *(float *)(param_1 + 0x784);
      tmp_i7 = VectorCompare(param_1 + 0x794,param_1 + 0x77c);
      if (tmp_i7 == 0) {
        *(uint32_t *)(param_1 + 0x77c) = *(uint32_t *)(param_1 + 0x794);
        *(uint32_t *)(param_1 + 0x780) = *(uint32_t *)(param_1 + 0x798);
        *(uint32_t *)(param_1 + 0x784) = *(uint32_t *)(param_1 + 0x79c);
      }
    }
    else {
      local_114 = *(float *)(param_1 + 0x794) - *(float *)(param_1 + 0x18);
      local_110 = *(float *)(param_1 + 0x798) - *(float *)(param_1 + 0x1c);
      local_10c = *(float *)(param_1 + 0x79c) - *(float *)(param_1 + 0x20);
      *(uint32_t *)(param_1 + 0x77c) = *(uint32_t *)(param_1 + 0x794);
      *(uint32_t *)(param_1 + 0x780) = *(uint32_t *)(param_1 + 0x798);
      *(uint32_t *)(param_1 + 0x784) = *(uint32_t *)(param_1 + 0x79c);
    }
    pfVar2 = &local_114;
  }
  else {
    pfVar2 = (float *)(param_1 + 0x24);
  }
  tmp_l10 = (long double)VectorNormalize2(pfVar2,local_ec);
  if (tmp_l10 == (long double)0) {
    local_e4 = 0x3f800000;
  }
  if (*(int *)(param_1 + 0xac) == g_unk_0109079c) {
    tmp_i7 = *(int *)(param_1 + 0xe8);
    if (tmp_i7 == 5) {
      if ((((cgs[0x20390d4] & 1) == 0) || (*(int *)(param_1 + 4) == 0x14)) ||
         (g_unk_010ee054 = param_1, g_unk_0109079c != *(int *)(param_1 + 0xac))) goto LAB_00065c99;
      tmp_i7 = *(int *)(param_1 + 0xe8);
    }
    if (((tmp_i7 - 0x16U < 2) || (tmp_i7 - 0x24U < 2)) && ((cgs[0x20390d4] & 4) != 0)) {
      g_unk_010ee054 = param_1;
      if (g_unk_0109079c != *(int *)(param_1 + 0xac)) goto LAB_00065c99;
      tmp_i7 = *(int *)(param_1 + 0xe8);
    }
    if (((tmp_i7 == 0x2a) || (tmp_i7 == 0x21)) && ((cgs[0x20390d4] & 2) != 0)) {
      g_unk_010ee054 = param_1;
    }
  }
LAB_00065c99:
  AxisToAngles(local_ec,param_1 + 0x7a0);
  if (*(int *)(param_1 + 0xc) == 0) {
    RotateAroundDirection(local_ec,(float)*(int *)(param_1 + 0x54));
  }
  else {
    tmp_i7 = g_unk_010906e0 + 3;
    if (-1 < g_unk_010906e0) {
      tmp_i7 = g_unk_010906e0;
    }
    RotateAroundDirection(local_ec,(float)(tmp_i7 >> 2));
  }
  if (local_108[2] != 0) {
    CG_AddRefEntityWithPowerups(local_138,*(uint32_t *)(param_1 + 0xe4),0,param_1,&vec3_origin);
  }
  return;
}

void CG_FlameLerpVec(float *param_1,float *param_2,float param_3,float *param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  
  tmp_f4 = 1.0 - param_3;
  tmp_f1 = *param_2;
  *param_4 = tmp_f4 * tmp_f1;
  tmp_f2 = param_2[1];
  param_4[1] = tmp_f4 * tmp_f2;
  tmp_f3 = param_2[2];
  param_4[2] = tmp_f4 * tmp_f3;
  *param_4 = *param_1 * param_3 + tmp_f4 * tmp_f1;
  param_4[1] = param_1[1] * param_3 + tmp_f4 * tmp_f2;
  param_4[2] = param_3 * param_1[2] + tmp_f4 * tmp_f3;
  return;
}

void CG_FlameAdjustSpeed(int param_1,float param_2)
{
  float tmp_f1;
  
  if ((param_2 == 0.0) && (*(float *)(param_1 + 0x50) == 0.0)) {
    return;
  }
  param_2 = *(float *)(param_1 + 0x50) + param_2;
  tmp_f1 = 60.0;
  if (60.0 <= param_2) {
    tmp_f1 = param_2;
  }
  *(float *)(param_1 + 0x50) = tmp_f1;
  return;
}

int CG_FlameCalcOrg(int param_1,int param_2,float *param_3)
{
  *param_3 = ((float)(param_2 - *(int *)(param_1 + 0x40)) / 1000.0) * *(float *)(param_1 + 0x50) *
             *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x34);
  param_3[1] = ((float)(param_2 - *(int *)(param_1 + 0x40)) / 1000.0) * *(float *)(param_1 + 0x50) *
               *(float *)(param_1 + 0x48) + *(float *)(param_1 + 0x38);
  param_2 = param_2 - *(int *)(param_1 + 0x40);
  param_3[2] = ((float)param_2 / 1000.0) * *(float *)(param_1 + 0x50) * *(float *)(param_1 + 0x4c) +
               *(float *)(param_1 + 0x3c);
  return param_2;
}

void CG_FlameDamage(void)
{
  return;
}

void CG_RailTrail_part_5(uint32_t param_1,float *param_2,float *param_3,uint32_t param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float local_54;
  float local_50;
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
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_48 = *param_2;
  tmp_f1 = local_48 - *param_3;
  local_50 = param_2[1];
  tmp_f2 = local_50 - param_3[1];
  local_4c = param_2[2];
  tmp_f3 = local_4c - param_3[2];
  local_54 = local_48 - tmp_f1;
  local_44 = local_50 - tmp_f2;
  local_34 = local_4c - tmp_f3;
  local_40 = local_4c;
  local_3c = local_48;
  local_38 = local_50;
  CG_RailTrail2(param_1,param_2,&local_54,param_4,1);
  CG_RailTrail2(param_1,param_2,&local_48,param_4,2);
  CG_RailTrail2(param_1,param_2,&local_3c,param_4,3);
  local_24 = *param_3;
  local_2c = param_3[1];
  local_28 = param_3[2];
  local_30 = tmp_f1 + local_24;
  local_20 = tmp_f2 + local_2c;
  local_10 = tmp_f3 + local_28;
  local_1c = local_28;
  local_18 = local_24;
  local_14 = local_2c;
  CG_RailTrail2(param_1,param_3,&local_30,param_4,4);
  CG_RailTrail2(param_1,param_3,&local_24,param_4,5);
  CG_RailTrail2(param_1,param_3,&local_18,param_4,6);
  CG_RailTrail2(param_1,&local_48,&local_18,param_4,7);
  CG_RailTrail2(param_1,&local_18,&local_54,param_4,8);
  CG_RailTrail2(param_1,&local_54,&local_24,param_4,9);
  CG_RailTrail2(param_1,&local_48,&local_30,param_4,10);
  CG_RailTrail2(param_1,&local_30,&local_3c,param_4,0xb);
  CG_RailTrail2(param_1,&local_3c,&local_24,param_4,0xc);
  return;
}

void CG_MissileHitWall(int param_1,int param_2,float *param_3,float *param_4,uint param_5)
{
  float *pfVar1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint tmp_u6;
  int tmp_i7;
  uint32_t tmp_u8;
  int tmp_i9;
  int tmp_i10;
  long double tmp_l11;
  uint32_t tmp_u12;
  uint32_t tmp_u13;
  int local_f8;
  uint local_f4;
  uint local_e4;
  int local_dc;
  int local_d8;
  int local_cc;
  int local_c8;
  int local_c0;
  int local_bc;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c [10];
  float local_64;
  float local_60;
  float local_5c;
  uint32_t local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  uint local_28;
  
  if ((param_5 & 4) != 0) {
    return;
  }
  switch(param_1) {
  default:
    goto _L3445;
  case 1:
    tmp_i9 = rand();
    if (param_5 == 0) {
      local_dc = GHIDRA_FIELD(cgs, 69408, 4);
      local_f8 = GHIDRA_FIELD(cgs, 68792, 4);
      tmp_i9 = rand();
      tmp_f3 = (float)(tmp_i9 % 2 + 1);
      tmp_i9 = rand();
      if (GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0) {
        CG_AddBulletParticles_part_13(0x14,tmp_i9 % 6 + 3,0x3f800000);
      }
    }
    else {
      local_dc = *(int *)(cgs + (tmp_i9 % 4) * 4 + 0x10f10);
      tmp_f3 = 32.0;
      local_f8 = 0;
    }
    tmp_u8 = 0x7f;
LAB_000dec9e:
    local_cc = GHIDRA_FIELD(cg_markTime, 12, 4);
    if (local_dc != 0) {
      local_d8 = 0;
      tmp_f4 = 0.0;
      goto LAB_000e01cc;
    }
    goto LAB_000decc0;
  case 2:
  case 3:
  case 7:
  case 8:
  case 10:
  case 0xe:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x22:
  case 0x23:
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2c:
  case 0x2d:
  case 0x2e:
    if (param_2 == 0) {
      tmp_i9 = rand();
      if (GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0) {
        CG_AddSparks_part_12(0x15e,200,tmp_i9 % 7 + 0xf,0x3e4ccccd);
      }
      if (2 < param_1 - 0x27U) {
        Distance(g_unk_010afbcc + 0x18,param_3);
      }
    }
    else {
      if (param_2 == 1) {
        local_54 = *param_4 * 12.0 + *param_3;
        local_50 = param_4[1] * 12.0 + param_3[1];
        local_4c = param_4[2] * 12.0 + param_3[2];
        if ((param_5 & 0x580000) == 0) {
          if (GHIDRA_FIELD(cg_smokeparticles, 12, 4) != 0) {
            CG_ParticleImpactSmokePuff(GHIDRA_FIELD(cgs, 68876, 4),&local_54);
          }
          tmp_i9 = rand();
          if (GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0) {
            CG_AddBulletParticles_part_13(0x14,tmp_i9 % 6 + 3,0x3f800000);
          }
        }
        else if ((param_5 & 0x400000) == 0) {
          if (GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0) {
            tmp_u13 = 0x41800000;
            tmp_u12 = 0x3f000000;
            tmp_u8 = GHIDRA_FIELD(cgs, 68880, 4);
            goto LAB_000e0166;
          }
        }
        else if (GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0) {
          tmp_u13 = 0x42000000;
          tmp_u12 = 0x3e800000;
          tmp_u8 = GHIDRA_FIELD(cgs, 68884, 4);
LAB_000e0166:
          CG_AddDirtBulletParticles_part_14(0xbe,900,5,tmp_u12,0x42a00000,tmp_u13,0x3f000000,tmp_u8);
        }
      }
      else if (param_2 == 2) {
        tv(0,0,0x3f800000);
        tmp_u8 = GHIDRA_FIELD(cgs, 68748, 4);
        tmp_i7 = CG_AllocLocalEntity();
        *(uint32_t *)(tmp_i7 + 0xc) = 1;
        *(uint32_t *)(tmp_i7 + 8) = 8;
        tmp_i9 = g_unk_010906e0;
        *(int *)(tmp_i7 + 0x10) = g_unk_010906e0;
        tmp_i10 = g_unk_010906e0 + 1000;
        *(int *)(tmp_i7 + 0x14) = tmp_i10;
        *(float *)(tmp_i7 + 0x1c) = 1.0 / (float)(tmp_i10 - tmp_i9);
        *(float *)(tmp_i7 + 0x100) = *param_3;
        *(float *)(tmp_i7 + 0x104) = param_3[1];
        *(float *)(tmp_i7 + 0x108) = param_3[2];
        tmp_f3 = (float)g_unk_010906e0;
        *(uint32_t *)(tmp_i7 + 0x98) = 3;
        *(uint32_t *)(tmp_i7 + 0x15c) = 0x42000000;
        *(uint32_t *)(tmp_i7 + 0x148) = tmp_u8;
        *(uint8_t *)(tmp_i7 + 0x14c) = 0xff;
        *(uint8_t *)(tmp_i7 + 0x14d) = 0xff;
        *(uint8_t *)(tmp_i7 + 0x14e) = 0xff;
        *(uint8_t *)(tmp_i7 + 0x14f) = 0xff;
        *(uint32_t *)(tmp_i7 + 0x78) = 0x3f800000;
        *(float *)(tmp_i7 + 0x158) = tmp_f3 / 1000.0;
        if (GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0) {
          CG_AddDirtBulletParticles_part_14
                    (0xbe,900,5,0x3f000000,0x42a00000,0x41800000,0x3e000000,GHIDRA_FIELD(cgs, 68884, 4));
        }
        goto LAB_000dfb4f;
      }
      if ((param_1 - 0x27U < 3) ||
         (tmp_l11 = (long double)Distance(g_unk_010afbcc + 0x18,param_3),
         tmp_l11 < (long double)(int)GHIDRA_FIELD(cg_markDistance, 12, 4))) {
        tmp_i9 = rand();
        tmp_f3 = (float)(tmp_i9 % 2) * 0.5 + 1.0;
        if ((param_5 & 0x801000) == 0) {
          if ((param_5 & 0x40000) == 0) {
            if ((param_5 & 0x200000) == 0) {
              tmp_i9 = rand();
              local_dc = *(int *)(cgs + (tmp_i9 % 5) * 4 + 0x10ee0);
              local_f8 = GHIDRA_FIELD(cgs, 68792, 4);
            }
            else {
              tmp_i9 = rand();
              local_dc = *(int *)(cgs + (tmp_i9 % 5) * 4 + 0x10ecc);
              local_f8 = GHIDRA_FIELD(cgs, 68804, 4);
            }
          }
          else {
            tmp_i9 = rand();
            tmp_f3 = tmp_f3 + 0.4;
            local_dc = *(int *)(cgs + (tmp_i9 % 5) * 4 + 0x10eb8);
            local_f8 = GHIDRA_FIELD(cgs, 68800, 4);
          }
        }
        else {
          tmp_i9 = rand();
          local_dc = *(int *)(cgs + (tmp_i9 % 5) * 4 + 0x10ea4);
          local_f8 = GHIDRA_FIELD(cgs, 68796, 4);
        }
        tmp_u8 = 0x40;
        goto LAB_000dec9e;
      }
    }
LAB_000dfb4f:
    if (GHIDRA_FIELD(cgs, 68808, 4) != 0) {
      return;
    }
    local_cc = -1;
    local_8c[9] = 32.0;
    tmp_u8 = 0;
    goto LAB_000dfb80;
  case 4:
  case 9:
  case 0x19:
  case 0x1a:
  case 0x24:
  case 0x25:
  case 0x2a:
  case 0x31:
    if (param_1 == 0x1a) {
      local_dc = GHIDRA_FIELD(cgs, 69112, 4);
      local_d8 = GHIDRA_FIELD(cgs, 69116, 4);
    }
    else if ((param_1 == 0x31) || (param_1 == 0x19)) {
      local_dc = GHIDRA_FIELD(cgs, 69120, 4);
      local_d8 = GHIDRA_FIELD(cgs, 69124, 4);
    }
    else if (param_1 == 0x2a) {
      local_d8 = 0;
      local_dc = 0;
    }
    else if (((param_1 == 4) || (param_1 == 9)) || (param_1 - 0x24U < 2)) {
      local_dc = GHIDRA_FIELD(cgs, 69148, 4);
      local_d8 = GHIDRA_FIELD(cgs, 69152, 4);
    }
    else {
      local_dc = GHIDRA_FIELD(cgs, 69100, 4);
      local_d8 = GHIDRA_FIELD(cgs, 69104, 4);
    }
    local_f8 = GHIDRA_FIELD(cgs, 68808, 4);
    local_cc = GHIDRA_FIELD(cg_markTime, 12, 4) * 3;
    local_8c[0] = *param_4 * 16.0 + *param_3;
    local_8c[1] = param_4[1] * 16.0 + param_3[1];
    local_8c[2] = param_4[2] * 16.0 + param_3[2];
    local_8c[3] = *param_4 * 100.0;
    local_8c[4] = param_4[1] * 100.0;
    local_8c[5] = param_4[2] * 100.0;
    tmp_u6 = CG_PointContents(param_3,0);
    if ((tmp_u6 & 0x20) == 0) {
      local_a4 = *param_3;
      local_a0 = param_3[1];
      local_9c = param_3[2] + 20.0;
      local_90 = param_3[2] - 20.0;
      local_98 = local_a4;
      local_94 = local_a0;
      trap_CM_BoxTrace(&local_54,&local_a4,&local_98,0,0,0,0x6000001);
      tmp_u8 = GHIDRA_FIELD(cgs, 68880, 4);
      if (((local_28 & 0x180000) != 0) && (GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0)) {
        local_64 = *param_3;
        local_60 = param_3[1];
        local_8c[6] = 0.0;
        local_5c = param_3[2];
        local_8c[7] = 0.0;
        local_8c[8] = 400.0;
        CG_ParticleDirtBulletDebris_Core
                  (&local_64,local_8c + 6,2000,0x43480000,0x42960000,0x3e800000,GHIDRA_FIELD(cgs, 68880, 4));
        local_c8 = 10;
        do {
          tmp_f3 = *param_4;
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[6] = (tmp_f4 + tmp_f4) * tmp_f3 * 400.0 * 0.5;
          tmp_f3 = param_4[1];
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[7] = (tmp_f4 + tmp_f4) * tmp_f3 * 400.0 * 0.5;
          tmp_f3 = param_4[2];
          tmp_u6 = rand();
          local_8c[8] = ((float)(tmp_u6 & 0x7fff) / 32767.0) * tmp_f3 * 400.0;
          tmp_i9 = rand();
          CG_ParticleDirtBulletDebris_Core
                    (&local_64,local_8c + 6,tmp_i9 % 1000 + 2000,0x43480000,0x42960000,0x3e800000,
                     tmp_u8);
          local_c8 = local_c8 + -1;
        } while (local_c8 != 0);
      }
      CG_ParticleExplosion("explode1",local_8c,local_8c + 3,700,0x3c,0xf0,1);
      tmp_i9 = rand();
      CG_AddDebris(param_3,param_4,0x118,0x578,tmp_i9 % 2 + 7);
      tmp_f4 = 400.0;
      tmp_f3 = 64.0;
    }
    else {
      local_a4 = *param_3;
      local_a0 = param_3[1];
      local_dc = GHIDRA_FIELD(cgs, 69108, 4);
      local_9c = param_3[2] + 10000.0;
      trap_CM_BoxTrace(&local_54,&local_a4,param_3,0,0,0,0x38);
      tmp_u8 = GHIDRA_FIELD(cgs, 68748, 4);
      tmp_i7 = CG_AllocLocalEntity();
      *(uint32_t *)(tmp_i7 + 0xc) = 1;
      *(uint32_t *)(tmp_i7 + 8) = 8;
      tmp_i9 = g_unk_010906e0;
      *(int *)(tmp_i7 + 0x10) = g_unk_010906e0;
      tmp_i10 = g_unk_010906e0 + 1000;
      *(int *)(tmp_i7 + 0x14) = tmp_i10;
      *(float *)(tmp_i7 + 0x1c) = 1.0 / (float)(tmp_i10 - tmp_i9);
      *(float *)(tmp_i7 + 0x100) = local_48;
      *(float *)(tmp_i7 + 0x104) = local_44;
      *(float *)(tmp_i7 + 0x108) = local_40;
      tmp_f3 = (float)g_unk_010906e0;
      *(uint32_t *)(tmp_i7 + 0x98) = 3;
      *(uint32_t *)(tmp_i7 + 0x15c) = 0x43160000;
      *(uint32_t *)(tmp_i7 + 0x148) = tmp_u8;
      *(uint8_t *)(tmp_i7 + 0x14c) = 0xff;
      *(uint8_t *)(tmp_i7 + 0x14d) = 0xff;
      *(uint8_t *)(tmp_i7 + 0x14e) = 0xff;
      *(uint8_t *)(tmp_i7 + 0x14f) = 0xff;
      *(uint32_t *)(tmp_i7 + 0x78) = 0x3f800000;
      *(float *)(tmp_i7 + 0x158) = tmp_f3 / 1000.0;
      tmp_u8 = GHIDRA_FIELD(cgs, 68884, 4);
      if (GHIDRA_FIELD(cg_impactparticles, 12, 4) == 0) {
        tmp_f4 = 400.0;
        tmp_f3 = 64.0;
      }
      else {
        local_64 = local_48;
        local_60 = local_44;
        local_5c = local_40;
        local_8c[6] = 0.0;
        local_8c[7] = 0.0;
        local_8c[8] = 400.0;
        CG_ParticleDirtBulletDebris_Core
                  (&local_64,local_8c + 6,900,0x43800000,0x43000000,0x3e000000,GHIDRA_FIELD(cgs, 68884, 4));
        local_c8 = 0xf;
        do {
          tmp_f3 = *param_4;
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[6] = (tmp_f4 + tmp_f4) * tmp_f3 * 400.0 * 0.5;
          tmp_f3 = param_4[1];
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[7] = (tmp_f4 + tmp_f4) * tmp_f3 * 400.0 * 0.5;
          tmp_f3 = param_4[2];
          tmp_u6 = rand();
          local_8c[8] = ((float)(tmp_u6 & 0x7fff) / 32767.0) * tmp_f3 * 400.0;
          tmp_i9 = rand();
          CG_ParticleDirtBulletDebris_Core
                    (&local_64,local_8c + 6,tmp_i9 % 0x1c2 + 900,0x43800000,0x43000000,0x3e000000,
                     tmp_u8);
          local_c8 = local_c8 + -1;
        } while (local_c8 != 0);
        tmp_f3 = 64.0;
        tmp_f4 = 400.0;
      }
    }
    break;
  case 5:
  case 0xd:
  case 0x11:
  case 0x15:
    local_dc = GHIDRA_FIELD(cgs, 69100, 4);
    local_d8 = GHIDRA_FIELD(cgs, 69104, 4);
    if ((param_1 - 0xdU & 0xfffffffb) == 0) {
      tmp_i9 = rand();
      local_dc = *(int *)(cgs + (tmp_i9 % 3) * 4 + 0x10d34);
      local_d8 = GHIDRA_FIELD(cgs, 68928, 4);
    }
    else if (param_1 == 0x15) {
      tmp_i9 = rand();
      local_dc = *(int *)(cgs + (tmp_i9 % 3) * 4 + 0x10d44);
      local_d8 = GHIDRA_FIELD(cgs, 68944, 4);
    }
    local_f8 = GHIDRA_FIELD(cgs, 68808, 4);
    local_cc = GHIDRA_FIELD(cg_markTime, 12, 4) * 3;
    local_8c[0] = *param_4 * 24.0 + *param_3;
    local_8c[1] = param_4[1] * 24.0 + param_3[1];
    local_8c[2] = param_4[2] * 24.0 + param_3[2];
    local_8c[3] = *param_4 * 64.0;
    local_8c[4] = param_4[1] * 64.0;
    local_8c[5] = param_4[2] * 64.0;
    tmp_u6 = CG_PointContents(param_3,0);
    if ((tmp_u6 & 0x20) == 0) {
      local_a4 = *param_3;
      local_a0 = param_3[1];
      local_9c = param_3[2] + 20.0;
      local_90 = param_3[2] - 20.0;
      local_98 = local_a4;
      local_94 = local_a0;
      trap_CM_BoxTrace(&local_54,&local_a4,&local_98,0,0,0,0x6000001);
      tmp_u8 = GHIDRA_FIELD(cgs, 68880, 4);
      if (((local_28 & 0x180000) != 0) && (tmp_u6 = rand(), GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0)) {
        local_8c[6] = 0.0;
        local_8c[7] = 0.0;
        tmp_i9 = (int)ROUND(((float)(tmp_u6 & 0x7fff) / 32767.0) * 200.0 + 400.0);
        local_64 = *param_3;
        local_60 = param_3[1];
        local_5c = param_3[2];
        local_8c[8] = (float)tmp_i9;
        CG_ParticleDirtBulletDebris_Core
                  (&local_64,local_8c + 6,3000,0x43c80000,0x43800000,0x3e800000,tmp_u8);
        local_c0 = 10;
        do {
          tmp_f3 = *param_4;
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[6] = (tmp_f4 + tmp_f4) * tmp_f3 * (float)tmp_i9 * 0.5;
          tmp_f3 = param_4[1];
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[7] = (tmp_f4 + tmp_f4) * tmp_f3 * (float)tmp_i9 * 0.5;
          tmp_f3 = param_4[2];
          local_e4 = rand();
          local_e4 = local_e4 & 0x7fff;
          local_8c[8] = ((float)local_e4 / 32767.0) * tmp_f3 * (float)tmp_i9;
          tmp_i7 = rand();
          CG_ParticleDirtBulletDebris_Core
                    (&local_64,local_8c + 6,tmp_i7 % 0x5dc + 3000,0x43c80000,0x43800000,0x3e800000,
                     tmp_u8);
          local_c0 = local_c0 + -1;
        } while (local_c0 != 0);
      }
      local_f4 = rand();
      local_f4 = local_f4 & 0x7fff;
      pfVar1 = local_8c + 3;
      CG_ParticleExplosion
                ("explode1",local_8c,pfVar1,0x640,0x14,
                 (int)ROUND(((float)local_f4 / 32767.0) * 400.0 + 200.0),1);
      local_e4 = 4;
      do {
        tmp_i9 = 0;
        do {
          tmp_f3 = param_3[tmp_i9];
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[tmp_i9] = (tmp_f4 + tmp_f4) * 50.0 + tmp_f3;
          tmp_u6 = rand();
          tmp_f3 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          pfVar1[tmp_i9] = (tmp_f3 + tmp_f3) * 0.35;
          tmp_i9 = tmp_i9 + 1;
        } while (tmp_i9 != 3);
        local_8c[3] = (local_8c[3] + local_3c) * 300.0;
        local_8c[4] = (local_8c[4] + local_38) * 300.0;
        local_8c[5] = (local_8c[5] + local_34) * 300.0;
        tmp_i9 = rand();
        CG_ParticleExplosion("explode1",local_8c,pfVar1,0x640,0x28,tmp_i9 % 0x78 + 0x104,0);
        local_e4 = local_e4 + -1;
      } while (local_e4 != 0);
      tmp_i9 = rand();
      tmp_i7 = rand();
      tmp_u6 = rand();
      CG_AddDebris(param_3,param_4,(int)ROUND(((float)(tmp_u6 & 0x7fff) / 32767.0) * 200.0 + 400.0),
                   tmp_i7 % 2000 + 1000,tmp_i9 % 5 + 5);
      tmp_f4 = 800.0;
      tmp_f3 = 128.0;
    }
    else {
      local_a4 = *param_3;
      local_a0 = param_3[1];
      local_9c = param_3[2] + 10000.0;
      trap_CM_BoxTrace(&local_54,&local_a4,param_3,0,0,0,0x38);
      tmp_u8 = GHIDRA_FIELD(cgs, 68748, 4);
      tmp_i7 = CG_AllocLocalEntity();
      *(uint32_t *)(tmp_i7 + 8) = 8;
      *(uint32_t *)(tmp_i7 + 0xc) = 1;
      tmp_i9 = g_unk_010906e0;
      *(int *)(tmp_i7 + 0x10) = g_unk_010906e0;
      tmp_i10 = g_unk_010906e0 + 2000;
      *(int *)(tmp_i7 + 0x14) = tmp_i10;
      *(float *)(tmp_i7 + 0x1c) = 1.0 / (float)(tmp_i10 - tmp_i9);
      *(float *)(tmp_i7 + 0x100) = local_48;
      *(float *)(tmp_i7 + 0x104) = local_44;
      *(float *)(tmp_i7 + 0x108) = local_40;
      tmp_f3 = (float)g_unk_010906e0;
      *(uint32_t *)(tmp_i7 + 0x98) = 3;
      *(uint32_t *)(tmp_i7 + 0x15c) = 0x43960000;
      *(uint32_t *)(tmp_i7 + 0x148) = tmp_u8;
      *(uint8_t *)(tmp_i7 + 0x14c) = 0xff;
      *(uint8_t *)(tmp_i7 + 0x14d) = 0xff;
      *(uint8_t *)(tmp_i7 + 0x14e) = 0xff;
      *(uint8_t *)(tmp_i7 + 0x14f) = 0xff;
      *(uint32_t *)(tmp_i7 + 0x78) = 0x3f800000;
      *(float *)(tmp_i7 + 0x158) = tmp_f3 / 1000.0;
      tmp_u8 = GHIDRA_FIELD(cgs, 68884, 4);
      tmp_u6 = rand();
      if (GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0) {
        local_8c[6] = 0.0;
        local_8c[7] = 0.0;
        tmp_i9 = (int)ROUND(((float)(tmp_u6 & 0x7fff) / 32767.0) * 200.0 + 400.0);
        local_64 = local_48;
        local_60 = local_44;
        local_5c = local_40;
        local_8c[8] = (float)tmp_i9;
        CG_ParticleDirtBulletDebris_Core
                  (&local_64,local_8c + 6,900,0x44000000,0x43000000,0x3e000000,tmp_u8);
        local_bc = 0xf;
        do {
          tmp_f3 = *param_4;
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[6] = (tmp_f4 + tmp_f4) * tmp_f3 * (float)tmp_i9 * 0.5;
          tmp_f3 = param_4[1];
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[7] = (tmp_f4 + tmp_f4) * tmp_f3 * (float)tmp_i9 * 0.5;
          tmp_f3 = param_4[2];
          local_e4 = rand();
          local_e4 = local_e4 & 0x7fff;
          local_8c[8] = ((float)local_e4 / 32767.0) * tmp_f3 * (float)tmp_i9;
          tmp_i7 = rand();
          CG_ParticleDirtBulletDebris_Core
                    (&local_64,local_8c + 6,tmp_i7 % 0x1c2 + 900,0x44000000,0x43000000,0x3e000000,
                     tmp_u8);
          local_bc = local_bc + -1;
        } while (local_bc != 0);
      }
      tmp_u8 = GHIDRA_FIELD(cgs, 68884, 4);
      local_f4 = rand();
      if (GHIDRA_FIELD(cg_impactparticles, 12, 4) == 0) {
        tmp_f4 = 800.0;
        tmp_f3 = 128.0;
      }
      else {
        local_f4 = local_f4 & 0x7fff;
        local_8c[6] = 0.0;
        local_8c[7] = 0.0;
        tmp_i9 = (int)ROUND(((float)local_f4 / 32767.0) * 600.0 + 400.0);
        local_64 = local_48;
        local_60 = local_44;
        local_5c = local_40;
        local_8c[8] = (float)tmp_i9;
        CG_ParticleDirtBulletDebris_Core
                  (&local_64,local_8c + 6,0x578,0x43000000,0x44000000,0x3e000000,tmp_u8);
        local_c0 = 0xf;
        do {
          tmp_f3 = *param_4;
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[6] = (tmp_f4 + tmp_f4) * tmp_f3 * (float)tmp_i9 * 0.5;
          tmp_f3 = param_4[1];
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[7] = (tmp_f4 + tmp_f4) * tmp_f3 * (float)tmp_i9 * 0.5;
          tmp_f3 = param_4[2];
          local_e4 = rand();
          local_e4 = local_e4 & 0x7fff;
          local_8c[8] = ((float)local_e4 / 32767.0) * tmp_f3 * (float)tmp_i9;
          tmp_i7 = rand();
          CG_ParticleDirtBulletDebris_Core
                    (&local_64,local_8c + 6,tmp_i7 % 700 + 0x578,0x43000000,0x44000000,0x3e000000,
                     tmp_u8);
          local_c0 = local_c0 + -1;
        } while (local_c0 != 0);
        tmp_f4 = 800.0;
        tmp_f3 = 128.0;
      }
    }
    break;
  case 0xf:
  case 0x30:
    local_dc = GHIDRA_FIELD(cgs, 69384, 4);
    local_d8 = GHIDRA_FIELD(cgs, 69388, 4);
    local_f8 = GHIDRA_FIELD(cgs, 68808, 4);
    local_cc = GHIDRA_FIELD(cg_markTime, 12, 4) * 3;
    tmp_u6 = CG_PointContents(param_3,0);
    if ((tmp_u6 & 0x20) == 0) {
      local_a4 = *param_3;
      local_a0 = param_3[1];
      local_9c = param_3[2] + 20.0;
      local_90 = param_3[2] - 20.0;
      local_98 = local_a4;
      local_94 = local_a0;
      trap_CM_BoxTrace(&local_54,&local_a4,&local_98,0,0,0,0x6000001);
      tmp_u8 = GHIDRA_FIELD(cgs, 68880, 4);
      if (((local_28 & 0x180000) != 0) && (local_f4 = rand(), GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0)) {
        local_f4 = local_f4 & 0x7fff;
        local_8c[6] = 0.0;
        local_8c[7] = 0.0;
        tmp_i9 = (int)ROUND(((float)local_f4 / 32767.0) * 200.0 + 400.0);
        tmp_f3 = (float)tmp_i9;
        local_64 = *param_3;
        local_60 = param_3[1];
        local_5c = param_3[2];
        local_8c[8] = tmp_f3;
        CG_ParticleDirtBulletDebris_Core
                  (&local_64,local_8c + 6,3000,0x43c80000,0x43800000,0x3e800000,tmp_u8);
        local_c0 = 10;
        tmp_f4 = (float)tmp_i9;
        do {
          tmp_f2 = *param_4;
          tmp_u6 = rand();
          tmp_f5 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[6] = (tmp_f5 + tmp_f5) * tmp_f2 * tmp_f4 * 0.5;
          tmp_f2 = param_4[1];
          tmp_u6 = rand();
          tmp_f5 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[7] = (tmp_f5 + tmp_f5) * tmp_f2 * tmp_f4 * 0.5;
          tmp_f2 = param_4[2];
          tmp_u6 = rand();
          local_8c[8] = ((float)(tmp_u6 & 0x7fff) / 32767.0) * tmp_f2 * tmp_f3;
          tmp_i9 = rand();
          CG_ParticleDirtBulletDebris_Core
                    (&local_64,local_8c + 6,tmp_i9 % 0x5dc + 3000,0x43c80000,0x43800000,0x3e800000,
                     tmp_u8);
          local_c0 = local_c0 + -1;
        } while (local_c0 != 0);
      }
      pfVar1 = local_8c + 3;
      local_e4 = 3;
      do {
        tmp_i9 = 0;
        do {
          tmp_f3 = param_3[tmp_i9];
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[tmp_i9] = (tmp_f4 + tmp_f4) * 150.0 + tmp_f3;
          local_f4 = rand();
          local_f4 = local_f4 & 0x7fff;
          tmp_f3 = (float)local_f4 / 32767.0 - 0.5;
          pfVar1[tmp_i9] = (tmp_f3 + tmp_f3) * 0.35;
          tmp_i9 = tmp_i9 + 1;
        } while (tmp_i9 != 3);
        local_8c[3] = (local_8c[3] + local_3c) * 130.0;
        local_8c[4] = (local_8c[4] + local_38) * 130.0;
        local_8c[5] = (local_8c[5] + local_34) * 130.0;
        local_f4 = rand();
        tmp_u6 = rand();
        local_f4 = local_f4 & 0x7fff;
        tmp_f3 = (float)local_f4;
        local_f4 = tmp_u6 & 0x7fff;
        CG_ParticleExplosion
                  ("blacksmokeanim",local_8c,pfVar1,
                   (int)ROUND(((float)local_f4 / 32767.0) * 2000.0 + 6000.0),0x28,
                   (int)ROUND((tmp_f3 / 32767.0) * 200.0 + 400.0),0);
        local_e4 = local_e4 + -1;
      } while (local_e4 != 0);
      local_e4 = 3;
      do {
        tmp_i9 = 0;
        do {
          tmp_f3 = param_3[tmp_i9];
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[tmp_i9] = (tmp_f4 + tmp_f4) * 100.0 + tmp_f3;
          tmp_u6 = rand();
          tmp_f3 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          pfVar1[tmp_i9] = (tmp_f3 + tmp_f3) * 0.65;
          tmp_i9 = tmp_i9 + 1;
        } while (tmp_i9 != 3);
        tmp_f3 = local_8c[3] + local_3c;
        local_8c[4] = local_8c[4] + local_38;
        local_8c[5] = local_8c[5] + local_34;
        local_8c[3] = tmp_f3;
        tmp_u6 = rand();
        tmp_f4 = local_8c[4];
        local_8c[3] = tmp_f3 * (((float)(tmp_u6 & 0x7fff) / 32767.0) * 100.0 + 300.0);
        tmp_u6 = rand();
        tmp_f3 = local_8c[5];
        local_8c[4] = (((float)(tmp_u6 & 0x7fff) / 32767.0) * 100.0 + 300.0) * tmp_f4;
        tmp_u6 = rand();
        local_8c[5] = (((float)(tmp_u6 & 0x7fff) / 32767.0) * 100.0 + 300.0) * tmp_f3;
        tmp_u6 = rand();
        tmp_i9 = rand();
        CG_ParticleExplosion
                  ("explode1",local_8c,pfVar1,tmp_i9 % 0x5aa + 1000,0x28,
                   (int)ROUND(((float)(tmp_u6 & 0x7fff) / 32767.0) * 200.0 + 400.0),local_e4 == 0);
        local_e4 = local_e4 + -1;
      } while (local_e4 != -1);
      tmp_i9 = rand();
      tmp_i7 = rand();
      tmp_u6 = rand();
      CG_AddDebris(param_3,param_4,(int)ROUND(((float)(tmp_u6 & 0x7fff) / 32767.0) * 200.0 + 400.0),
                   tmp_i7 % 2000 + 0x578,tmp_i9 % 0xc + 0xc);
      tmp_f4 = 600.0;
      tmp_f3 = 150.0;
    }
    else {
      local_a4 = *param_3;
      local_a0 = param_3[1];
      local_9c = param_3[2] + 10000.0;
      trap_CM_BoxTrace(&local_54,&local_a4,param_3,0,0,0,0x38);
      tmp_u8 = GHIDRA_FIELD(cgs, 68748, 4);
      tmp_i7 = CG_AllocLocalEntity();
      *(uint32_t *)(tmp_i7 + 8) = 8;
      *(uint32_t *)(tmp_i7 + 0xc) = 1;
      tmp_i9 = g_unk_010906e0;
      *(int *)(tmp_i7 + 0x10) = g_unk_010906e0;
      tmp_i10 = g_unk_010906e0 + 2000;
      *(int *)(tmp_i7 + 0x14) = tmp_i10;
      *(float *)(tmp_i7 + 0x1c) = 1.0 / (float)(tmp_i10 - tmp_i9);
      *(float *)(tmp_i7 + 0x100) = local_48;
      *(float *)(tmp_i7 + 0x104) = local_44;
      *(float *)(tmp_i7 + 0x108) = local_40;
      tmp_f3 = (float)g_unk_010906e0;
      *(uint32_t *)(tmp_i7 + 0x98) = 3;
      *(uint32_t *)(tmp_i7 + 0x15c) = 0x43960000;
      *(uint32_t *)(tmp_i7 + 0x148) = tmp_u8;
      *(uint8_t *)(tmp_i7 + 0x14c) = 0xff;
      *(uint8_t *)(tmp_i7 + 0x14d) = 0xff;
      *(uint8_t *)(tmp_i7 + 0x14e) = 0xff;
      *(uint8_t *)(tmp_i7 + 0x14f) = 0xff;
      *(uint32_t *)(tmp_i7 + 0x78) = 0x3f800000;
      *(float *)(tmp_i7 + 0x158) = tmp_f3 / 1000.0;
      tmp_u8 = GHIDRA_FIELD(cgs, 68884, 4);
      tmp_u6 = rand();
      if (GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0) {
        local_8c[6] = 0.0;
        local_8c[7] = 0.0;
        tmp_i9 = (int)ROUND(((float)(tmp_u6 & 0x7fff) / 32767.0) * 200.0 + 400.0);
        local_64 = local_48;
        local_60 = local_44;
        local_5c = local_40;
        local_8c[8] = (float)tmp_i9;
        CG_ParticleDirtBulletDebris_Core
                  (&local_64,local_8c + 6,900,0x44000000,0x43000000,0x3e000000,tmp_u8);
        local_bc = 0xf;
        do {
          tmp_f3 = *param_4;
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[6] = (tmp_f4 + tmp_f4) * tmp_f3 * (float)tmp_i9 * 0.5;
          tmp_f3 = param_4[1];
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[7] = (tmp_f4 + tmp_f4) * tmp_f3 * (float)tmp_i9 * 0.5;
          tmp_f3 = param_4[2];
          tmp_u6 = rand();
          local_8c[8] = ((float)(tmp_u6 & 0x7fff) / 32767.0) * tmp_f3 * (float)tmp_i9;
          tmp_i7 = rand();
          CG_ParticleDirtBulletDebris_Core
                    (&local_64,local_8c + 6,tmp_i7 % 0x1c2 + 900,0x44000000,0x43000000,0x3e000000,
                     tmp_u8);
          local_bc = local_bc + -1;
        } while (local_bc != 0);
      }
      tmp_u8 = GHIDRA_FIELD(cgs, 68884, 4);
      local_f4 = rand();
      if (GHIDRA_FIELD(cg_impactparticles, 12, 4) == 0) {
        tmp_f4 = 600.0;
        tmp_f3 = 150.0;
      }
      else {
        local_f4 = local_f4 & 0x7fff;
        local_8c[6] = 0.0;
        local_8c[7] = 0.0;
        tmp_i9 = (int)ROUND(((float)local_f4 / 32767.0) * 600.0 + 400.0);
        local_64 = local_48;
        local_60 = local_44;
        local_5c = local_40;
        local_8c[8] = (float)tmp_i9;
        CG_ParticleDirtBulletDebris_Core
                  (&local_64,local_8c + 6,0x578,0x43000000,0x44000000,0x3e000000,tmp_u8);
        local_c0 = 0xf;
        do {
          tmp_f3 = *param_4;
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[6] = (tmp_f4 + tmp_f4) * tmp_f3 * (float)tmp_i9 * 0.5;
          tmp_f3 = param_4[1];
          tmp_u6 = rand();
          tmp_f4 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          local_8c[7] = (tmp_f4 + tmp_f4) * tmp_f3 * (float)tmp_i9 * 0.5;
          tmp_f3 = param_4[2];
          tmp_u6 = rand();
          local_8c[8] = ((float)(tmp_u6 & 0x7fff) / 32767.0) * tmp_f3 * (float)tmp_i9;
          tmp_i7 = rand();
          CG_ParticleDirtBulletDebris_Core
                    (&local_64,local_8c + 6,tmp_i7 % 700 + 0x578,0x43000000,0x44000000,0x3e000000,
                     tmp_u8);
          local_c0 = local_c0 + -1;
        } while (local_c0 != 0);
        tmp_f4 = 600.0;
        tmp_f3 = 150.0;
      }
    }
  }
  tmp_u8 = 0x7f;
  if (local_dc != 0) {
LAB_000e01cc:
    trap_S_StartSoundVControl(param_3,0xffffffff,0,local_dc,tmp_u8);
  }
  if (local_d8 != 0) {
    local_8c[6] = *param_3;
    local_8c[7] = param_3[1];
    local_8c[8] = param_3[2];
    local_64 = local_8c[6] - *(float *)(g_unk_010afbcc + 0x18);
    local_60 = local_8c[7] - *(float *)(g_unk_010afbcc + 0x1c);
    local_5c = local_8c[8] - *(float *)(g_unk_010afbcc + 0x20);
    tmp_l11 = (long double)VectorNormalize(&local_64);
    if (((long double)1200.0 < tmp_l11) && (tmp_l11 < (long double)8000.0)) {
      local_8c[6] = local_64 * tmp_f4 + *(float *)(g_unk_010afbcc + 0x18);
      local_8c[7] = local_60 * tmp_f4 + *(float *)(g_unk_010afbcc + 0x1c);
      local_8c[8] = local_5c * tmp_f4 + *(float *)(g_unk_010afbcc + 0x20);
      trap_S_StartSoundEx(local_8c + 6,0xffffffff,2,local_d8,0x10);
    }
  }
LAB_000decc0:
  tmp_u8 = GHIDRA_FIELD(cgs, 68808, 4);
  local_8c[9] = tmp_f3;
  if (GHIDRA_FIELD(cgs, 68808, 4) == local_f8) {
LAB_000dfb80:
    local_8c[6] = 0.0;
    local_8c[7] = 0.0;
    local_8c[8] = -1.0;
    local_64 = 1.0;
    local_60 = 1.0;
    local_5c = 1.0;
    local_58 = 0x3f800000;
    trap_R_ProjectDecal(tmp_u8,1,param_3,local_8c + 6,&local_64,local_cc,local_cc >> 4);
  }
  else if (local_f8 != 0) {
    local_8c[6] = vec3_origin - *param_4;
    local_8c[7] = g_unk_00c22b14 - param_4[1];
    local_8c[8] = g_unk_00c22b18 - param_4[2];
    local_8c[9] = tmp_f3 * 32.0;
    local_64 = local_8c[6] * -16.0 + *param_3;
    local_60 = local_8c[7] * -16.0 + param_3[1];
    local_5c = local_8c[8] * -16.0 + param_3[2];
    tmp_u6 = rand();
    local_64 = ((float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5) + local_64;
    tmp_u6 = rand();
    local_60 = ((float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5) + local_60;
    tmp_u6 = rand();
    local_5c = ((float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5) + local_5c;
    tmp_u6 = rand();
    CG_ImpactMark(local_f8,&local_64,local_8c + 6,tmp_f3,((float)(tmp_u6 & 0x7fff) / 32767.0) * 360.0,
                  0x3f800000,0x3f800000,0x3f800000,0x3f800000,local_cc);
  }
_L3445:
  return;
}

void CG_MissileHitWallSmall(uint32_t param_1,uint32_t param_2,float *param_3,float *param_4)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  tmp_u2 = GHIDRA_FIELD(cgs, 69100, 4);
  tmp_u1 = GHIDRA_FIELD(cgs, 68808, 4);
  uStack_14 = 0xe1879;
  local_54 = *param_4 * 16.0 + *param_3;
  local_50 = param_4[1] * 16.0 + param_3[1];
  local_4c = param_4[2] * 16.0 + param_3[2];
  local_48 = *param_4 * 64.0;
  local_44 = param_4[1] * 64.0;
  local_40 = param_4[2] * 64.0;
  CG_ParticleExplosion("explode1",&local_54,&local_48,600,6,0x32,1);
  tmp_i3 = rand();
  CG_AddDebris(param_3,param_4,0x118,0x578,tmp_i3 % 2 + 7);
  if (tmp_u2 != 0) {
    trap_S_StartSound(param_3,0xffffffff,0,tmp_u2);
  }
  local_3c = 0;
  local_38 = 0;
  local_34 = 0xbf800000;
  local_30 = 0x42a00000;
  local_2c = 0x3f800000;
  local_28 = 0x3f800000;
  local_24 = 0x3f800000;
  local_20 = 0x3f800000;
  trap_R_ProjectDecal(tmp_u1,1,param_3,&local_3c,&local_2c,GHIDRA_FIELD(cg_markTime, 12, 4),
                      (int)GHIDRA_FIELD(cg_markTime, 12, 4) >> 4);
  return;
}

void CG_MissileHitPlayer(uint32_t param_1,int param_2,uint32_t param_3,uint32_t param_4,
                        uint32_t param_5)

{
  CG_Bleed(param_3,param_5);
  if ((param_2 != 1) && ((param_2 < 1 || (1 < param_2 - 4U)))) {
    return;
  }
  CG_MissileHitWall();
  return;
}

