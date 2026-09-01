/* Particle systems — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_particles.h"

void CG_ParticleSnowFlurry(int param_1,int param_2)
{
  uint32_t tmp_u1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  uint32_t *tmp_pu6;
  int tmp_i7;
  uint tmp_u8;
  uint local_2c;
  
  if (param_1 == 0) {
    CG_Printf("CG_ParticleSnowFlurry pshader == ZERO!\n");
  }
  tmp_pu5 = free_particles;
  if (free_particles != (uint32_t *)0x0) {
    tmp_pu6 = (uint32_t *)*free_particles;
    *free_particles = active_particles;
    free_particles = tmp_pu6;
    active_particles = tmp_pu5;
    tmp_f2 = (float)g_unk_010906e0;
    tmp_pu5[0xc] = 0;
    tmp_pu5[0xe] = 0x3f666666;
    tmp_pu5[0xf] = 0;
    tmp_pu5[1] = tmp_f2;
    tmp_pu5[0x16] = *(uint32_t *)(param_2 + 0x68);
    tmp_pu5[0x17] = *(uint32_t *)(param_2 + 0x6c);
    tmp_pu5[2] = (float)(*(int *)(param_2 + 0x54) + g_unk_010906e0);
    tmp_i4 = g_unk_010906e0;
    tmp_i7 = *(int *)(param_2 + 0x58);
    tmp_pu5[0x11] = param_1;
    tmp_pu5[0x18] = (float)(tmp_i7 + tmp_i4);
    tmp_i7 = rand();
    if (tmp_i7 % 100 < 0x5b) {
      tmp_u1 = 0x3f800000;
    }
    else {
      tmp_pu5[0xe] = 0x3dcccccd;
      tmp_u1 = 0x42000000;
    }
    tmp_pu5[0x13] = tmp_u1;
    tmp_pu5[0x12] = tmp_u1;
    tmp_pu5[0x10] = 0xb;
    tmp_pu5[8] = 0xc1200000;
    tmp_pu5[3] = *(uint32_t *)(param_2 + 0x5c);
    tmp_pu5[4] = *(uint32_t *)(param_2 + 0x60);
    tmp_u1 = *(uint32_t *)(param_2 + 100);
    tmp_pu5[7] = 0;
    tmp_pu5[5] = tmp_u1;
    tmp_pu5[6] = 0;
    tmp_pu5[0xb] = 0;
    tmp_pu5[10] = 0;
    tmp_pu5[9] = 0;
    tmp_f2 = *(float *)(param_2 + 0x74);
    tmp_u8 = rand();
    tmp_f3 = (float)(tmp_u8 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu5[6] = (tmp_f3 + tmp_f3) * 16.0 + tmp_f2 * 32.0 + (float)tmp_pu5[6];
    tmp_f2 = *(float *)(param_2 + 0x78);
    tmp_u8 = rand();
    tmp_f3 = (float)(tmp_u8 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu5[7] = (tmp_f3 + tmp_f3) * 16.0 + tmp_f2 * 32.0 + (float)tmp_pu5[7];
    tmp_pu5[8] = (float)tmp_pu5[8] + *(float *)(param_2 + 0x7c);
    local_2c = rand();
    local_2c = local_2c & 0x7fff;
    tmp_f2 = (float)local_2c / 32767.0 - 0.5;
    tmp_pu5[9] = (tmp_f2 + tmp_f2) * 16.0;
    tmp_u8 = rand();
    tmp_f2 = (float)(tmp_u8 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu5[10] = (tmp_f2 + tmp_f2) * 16.0;
  }
  return;
}

void CG_ParticleSnow(int param_1,float *param_2,int param_3,int param_4,float param_5,
                    uint32_t param_6)

{
  float tmp_f1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint32_t tmp_u5;
  uint tmp_u6;
  uint local_3c;
  
  if (param_1 == 0) {
    CG_Printf("CG_ParticleSnow pshader == ZERO!\n");
  }
  tmp_pu3 = free_particles;
  if (free_particles != (uint32_t *)0x0) {
    tmp_pu4 = (uint32_t *)*free_particles;
    *free_particles = active_particles;
    free_particles = tmp_pu4;
    active_particles = tmp_pu3;
    tmp_f1 = (float)g_unk_010906e0;
    tmp_pu3[0xc] = 0;
    tmp_pu3[0xe] = 0x3ecccccd;
    tmp_pu3[0xf] = 0;
    tmp_pu3[1] = tmp_f1;
    tmp_pu3[0x16] = param_2[2];
    tmp_u5 = *(uint32_t *)(param_3 + 8);
    tmp_pu3[0x11] = param_1;
    tmp_pu3[0x17] = tmp_u5;
    tmp_pu3[0x12] = 0x3f800000;
    tmp_pu3[0x13] = 0x3f800000;
    if (param_4 == 0) {
      tmp_pu3[8] = 0xc2480000;
      tmp_u5 = 1;
    }
    else {
      tmp_pu3[8] = 0xc2820000;
      tmp_u5 = 5;
    }
    tmp_pu3[0x10] = tmp_u5;
    tmp_f1 = *param_2;
    tmp_pu3[3] = tmp_f1;
    tmp_pu3[4] = param_2[1];
    tmp_pu3[5] = param_2[2];
    tmp_u6 = rand();
    tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu3[3] = tmp_f1 + (tmp_f2 + tmp_f2) * param_5;
    tmp_f1 = (float)tmp_pu3[4];
    tmp_u6 = rand();
    tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu3[4] = param_5 * (tmp_f2 + tmp_f2) + tmp_f1;
    tmp_f1 = (float)tmp_pu3[5];
    tmp_u6 = rand();
    tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu3[5] = ((float)tmp_pu3[0x16] - (float)tmp_pu3[0x17]) * (tmp_f2 + tmp_f2) + tmp_f1;
    tmp_pu3[7] = 0;
    tmp_pu3[6] = 0;
    tmp_pu3[0xb] = 0;
    tmp_pu3[10] = 0;
    tmp_pu3[9] = 0;
    if (param_4 != 0) {
      local_3c = rand();
      local_3c = local_3c & 0x7fff;
      tmp_f1 = (float)local_3c / 32767.0 - 0.5;
      tmp_pu3[6] = (tmp_f1 + tmp_f1) * 16.0;
      tmp_u6 = rand();
      tmp_f1 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
      tmp_pu3[7] = (tmp_f1 + tmp_f1) * 16.0;
    }
    tmp_pu3[0x1b] = 1;
    tmp_pu3[0x1a] = param_6;
  }
  return;
}

uint32_t CG_ParticleBubble(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  uint32_t tmp_u1;
  
  if (GHIDRA_FIELD(cg_trailparticles, 12, 4) != 0) {
    param_2 = param_4;
    tmp_u1 = CG_ParticleBubble_part_0();
    return tmp_u1;
  }
  return param_1;
}

void CG_ParticleSmoke(int param_1,int param_2)
{
  uint32_t tmp_u1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  uint tmp_u7;
  int tmp_i8;
  uint local_24;
  
  if (GHIDRA_FIELD(cg_smokeparticles, 12, 4) == 0) {
    return;
  }
  tmp_pu5 = free_particles;
  if (param_1 == 0) {
    CG_Printf("CG_ParticleSmoke == ZERO!\n");
    tmp_pu5 = free_particles;
  }
  if (tmp_pu5 == (uint32_t *)0x0) {
    free_particles = tmp_pu5;
    return;
  }
  free_particles = (uint32_t *)*tmp_pu5;
  *tmp_pu5 = active_particles;
  active_particles = tmp_pu5;
  tmp_pu5[1] = (float)g_unk_010906e0;
  tmp_pu5[2] = (float)(*(int *)(param_2 + 0x54) + g_unk_010906e0);
  tmp_i6 = g_unk_010906e0;
  tmp_i8 = *(int *)(param_2 + 0x58);
  tmp_pu5[0xc] = 0;
  tmp_pu5[0xe] = 0x3f800000;
  tmp_pu5[0xf] = 0;
  tmp_pu5[0x18] = (float)(tmp_i8 + tmp_i6);
  tmp_pu5[0x16] = *(uint32_t *)(param_2 + 100);
  tmp_u1 = *(uint32_t *)(param_2 + 0x70);
  tmp_pu5[0x11] = param_1;
  tmp_pu5[0x17] = tmp_u1;
  tmp_i8 = *(int *)(param_2 + 0xf4);
  if ((tmp_i8 == 1) || (*(int *)(param_2 + 0xa8) != 0)) {
    tmp_pu5[0x19] = 0;
    tmp_pu5[0x12] = 0x41000000;
    tmp_pu5[0x13] = 0x41000000;
    tmp_pu5[0x14] = 0x42000000;
    tmp_pu5[0x15] = 0x42000000;
  }
  else if (tmp_i8 == 2) {
    tmp_pu5[0x19] = 1;
    tmp_pu5[0x12] = 0x40800000;
    tmp_pu5[0x13] = 0x40800000;
    tmp_pu5[0x14] = 0x41000000;
    tmp_pu5[0x15] = 0x41000000;
  }
  else if (tmp_i8 == 3) {
    tmp_pu5[0x19] = 0;
    tmp_u7 = rand();
    tmp_f2 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
    tmp_f2 = (tmp_f2 + tmp_f2) * 8.0 + 16.0;
    tmp_f3 = tmp_f2 + 24.0;
    tmp_pu5[0x12] = tmp_f3;
    tmp_pu5[0x13] = tmp_f3;
    tmp_f2 = tmp_f2 + 64.0;
    tmp_pu5[0x14] = tmp_f2;
    tmp_pu5[0x15] = tmp_f2;
  }
  else {
    tmp_pu5[0x19] = 1;
    if (tmp_i8 == 4) {
      tmp_pu5[0x12] = *(uint32_t *)(param_2 + 0x80);
      tmp_pu5[0x13] = *(uint32_t *)(param_2 + 0x80);
      tmp_pu5[0x14] = *(uint32_t *)(param_2 + 0x84);
      tmp_u1 = *(uint32_t *)(param_2 + 0x84);
      tmp_pu5[0xc] = 4;
      tmp_pu5[0x15] = tmp_u1;
    }
    else if (tmp_i8 == 5) {
      tmp_pu5[0x12] = *(uint32_t *)(param_2 + 0x80);
      tmp_pu5[0x13] = *(uint32_t *)(param_2 + 0x80);
      tmp_pu5[0x14] = *(uint32_t *)(param_2 + 0x84);
      tmp_u1 = *(uint32_t *)(param_2 + 0x84);
      tmp_pu5[0xc] = 1;
      tmp_pu5[0x15] = tmp_u1;
      tmp_pu5[0xe] = 0x3f400000;
    }
    else {
      tmp_pu5[0x12] = *(uint32_t *)(param_2 + 0x80);
      tmp_pu5[0x13] = *(uint32_t *)(param_2 + 0x80);
      tmp_pu5[0x14] = *(uint32_t *)(param_2 + 0x84);
      tmp_pu5[0x15] = *(uint32_t *)(param_2 + 0x84);
      tmp_i8 = rand();
      tmp_i8 = tmp_i8 % 6;
      if (tmp_i8 == 1) {
        tmp_pu5[0x11] = GHIDRA_FIELD(cgs, 68528, 4);
      }
      else if (tmp_i8 == 2) {
        tmp_pu5[0x11] = GHIDRA_FIELD(cgs, 68532, 4);
      }
      else if (tmp_i8 == 3) {
        tmp_pu5[0x11] = GHIDRA_FIELD(cgs, 68536, 4);
      }
      else if (tmp_i8 == 4) {
        tmp_pu5[0x11] = GHIDRA_FIELD(cgs, 68540, 4);
      }
      else {
        tmp_pu5[0x11] = GHIDRA_FIELD(cgs, 68544, 4);
      }
    }
  }
  tmp_pu5[0x10] = 3;
  tmp_pu5[3] = *(uint32_t *)(param_2 + 0x794);
  tmp_pu5[4] = *(uint32_t *)(param_2 + 0x798);
  tmp_u1 = *(uint32_t *)(param_2 + 0x79c);
  tmp_pu5[7] = 0;
  tmp_pu5[5] = tmp_u1;
  tmp_pu5[6] = 0;
  tmp_pu5[0xb] = 0;
  tmp_pu5[10] = 0;
  tmp_pu5[9] = 0;
  tmp_i8 = *(int *)(param_2 + 0xf4);
  if ((tmp_i8 == 1) || (tmp_i8 == 2)) {
    tmp_pu5[8] = 0x40a00000;
    tmp_f2 = 5.0;
  }
  else if (tmp_i8 == 3) {
    tmp_f2 = *(float *)(param_2 + 0x6c);
    tmp_f3 = *(float *)(param_2 + 0x68);
    tmp_u7 = rand();
    tmp_f4 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu5[6] = (tmp_f4 + tmp_f4) * 64.0 + tmp_f3 * 128.0;
    tmp_u7 = rand();
    tmp_f3 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu5[7] = (tmp_f3 + tmp_f3) * 64.0 + tmp_f2 * 128.0;
    tmp_u7 = rand();
    tmp_f2 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
    tmp_f2 = (tmp_f2 + tmp_f2) * 16.0 + 15.0;
    tmp_pu5[8] = tmp_f2;
  }
  else {
    if (tmp_i8 != 5) {
      tmp_f2 = *(float *)(param_2 + 0x6c);
      tmp_f3 = *(float *)(param_2 + 0x68);
      tmp_u7 = rand();
      tmp_f4 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
      tmp_pu5[6] = (tmp_f4 + tmp_f4) * (float)tmp_pu5[0x12] + tmp_f3;
      local_24 = rand();
      local_24 = local_24 & 0x7fff;
      tmp_f3 = (float)local_24 / 32767.0 - 0.5;
      tmp_pu5[7] = (tmp_f3 + tmp_f3) * (float)tmp_pu5[0x12] + tmp_f2;
      tmp_f2 = *(float *)(param_2 + 0x88);
      tmp_pu5[8] = tmp_f2;
      tmp_i8 = *(int *)(param_2 + 0xb0);
      goto joined_r0x0009c824;
    }
    tmp_f2 = *(float *)(param_2 + 0x6c);
    tmp_f3 = *(float *)(param_2 + 0x68);
    tmp_u7 = rand();
    tmp_f4 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu5[6] = (tmp_f4 + tmp_f4) * 16.0 + tmp_f3 * 32.0;
    tmp_u7 = rand();
    tmp_f3 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu5[7] = (tmp_f3 + tmp_f3) * 16.0 + tmp_f2 * 32.0;
    tmp_u7 = rand();
    tmp_f2 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
    tmp_f2 = tmp_f2 + tmp_f2;
    tmp_f2 = tmp_f2 + tmp_f2 + 4.0;
    tmp_pu5[8] = tmp_f2;
  }
  tmp_i8 = *(int *)(param_2 + 0xb0);
joined_r0x0009c824:
  if (tmp_i8 == 1) {
    tmp_pu5[8] = -tmp_f2;
  }
  tmp_u7 = rand();
  tmp_f2 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
  tmp_pu5[0x1d] = (int)ROUND((tmp_f2 + tmp_f2) * 4.0 + 8.0);
  return;
}

void CG_ParticleBulletDebris(uint32_t *param_1,uint32_t *param_2,int param_3)
{
  float tmp_f1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t *tmp_pu4;
  uint32_t *tmp_pu5;
  
  tmp_pu4 = free_particles;
  if (free_particles != (uint32_t *)0x0) {
    tmp_pu5 = (uint32_t *)*free_particles;
    *free_particles = active_particles;
    free_particles = tmp_pu5;
    active_particles = tmp_pu4;
    tmp_pu4[1] = (float)g_unk_010906e0;
    tmp_pu4[2] = (float)(g_unk_010906e0 + param_3);
    tmp_i2 = g_unk_010906e0;
    tmp_pu4[0xc] = 3;
    tmp_pu4[0xe] = 0x3f800000;
    tmp_pu4[0xf] = 0;
    tmp_pu4[0x12] = 0x3f000000;
    tmp_pu4[0x13] = 0x3f000000;
    tmp_pu4[0x14] = 0x3f000000;
    tmp_pu4[0x15] = 0x3f000000;
    tmp_pu4[0x18] = (float)(param_3 / 2 + tmp_i2);
    tmp_u3 = GHIDRA_FIELD(cgs, 68004, 4);
    tmp_pu4[0x10] = 3;
    tmp_pu4[0x11] = tmp_u3;
    tmp_pu4[3] = *param_1;
    tmp_pu4[4] = param_1[1];
    tmp_pu4[5] = param_1[2];
    tmp_pu4[6] = *param_2;
    tmp_pu4[7] = param_2[1];
    tmp_f1 = (float)param_2[2];
    tmp_pu4[10] = 0;
    tmp_pu4[9] = 0;
    tmp_pu4[0xb] = 0xc2700000;
    tmp_pu4[8] = tmp_f1 - 20.0;
  }
  return;
}

void CG_ParticleDirtBulletDebris(uint32_t *param_1,uint32_t *param_2,int param_3)
{
  float tmp_f1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  
  tmp_i5 = rand();
  tmp_pu3 = free_particles;
  if (free_particles != (uint32_t *)0x0) {
    tmp_pu4 = (uint32_t *)*free_particles;
    *free_particles = active_particles;
    free_particles = tmp_pu4;
    active_particles = tmp_pu3;
    tmp_pu3[1] = (float)g_unk_010906e0;
    tmp_pu3[2] = (float)(g_unk_010906e0 + param_3);
    tmp_i2 = g_unk_010906e0;
    tmp_pu3[0xc] = 3;
    tmp_pu3[0xe] = 0x3f800000;
    tmp_pu3[0xf] = 0;
    tmp_pu3[0x12] = 0x3f99999a;
    tmp_pu3[0x13] = 0x3f99999a;
    tmp_pu3[0x14] = 0x40900000;
    tmp_pu3[0x15] = 0x40900000;
    tmp_pu3[0x18] = (float)(param_3 / 2 + tmp_i2);
    if (tmp_i5 % 3 == 0) {
      tmp_pu3[0x11] = GHIDRA_FIELD(cgs, 68880, 4);
    }
    else if (tmp_i5 % 3 == 1) {
      tmp_pu3[0x11] = GHIDRA_FIELD(cgs, 68884, 4);
    }
    else {
      tmp_pu3[0x11] = GHIDRA_FIELD(cgs, 68888, 4);
    }
    tmp_pu3[0x10] = 3;
    tmp_pu3[3] = *param_1;
    tmp_pu3[4] = param_1[1];
    tmp_pu3[5] = param_1[2];
    tmp_pu3[6] = *param_2;
    tmp_pu3[7] = param_2[1];
    tmp_f1 = (float)param_2[2];
    tmp_pu3[10] = 0;
    tmp_pu3[9] = 0;
    tmp_pu3[0xb] = 0xc3a50000;
    tmp_pu3[8] = tmp_f1 - 20.0;
  }
  return;
}

void CG_ParticleDirtBulletDebris_Core
               (uint32_t *param_1,uint32_t *param_2,int param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  uint32_t *tmp_pu3;
  
  tmp_pu2 = free_particles;
  if (free_particles != (uint32_t *)0x0) {
    tmp_pu3 = (uint32_t *)*free_particles;
    *free_particles = active_particles;
    free_particles = tmp_pu3;
    active_particles = tmp_pu2;
    tmp_pu2[1] = (float)g_unk_010906e0;
    tmp_pu2[2] = (float)(param_3 + g_unk_010906e0);
    tmp_pu2[0x18] = (float)param_3 * 0.5 + (float)g_unk_010906e0;
    tmp_pu2[0xc] = 3;
    tmp_pu2[0xe] = param_6;
    tmp_pu2[0xf] = 0;
    tmp_pu2[0x12] = param_4;
    tmp_pu2[0x19] = 0;
    tmp_pu2[0x13] = param_5;
    tmp_pu2[0x14] = param_4;
    tmp_pu2[0x15] = param_5;
    tmp_pu2[0x10] = 3;
    tmp_pu2[0x11] = param_7;
    tmp_pu2[3] = *param_1;
    tmp_pu2[4] = param_1[1];
    tmp_pu2[5] = param_1[2];
    tmp_pu2[6] = *param_2;
    tmp_pu2[7] = param_2[1];
    tmp_u1 = param_2[2];
    tmp_pu2[9] = 0;
    tmp_pu2[8] = tmp_u1;
    tmp_pu2[10] = 0;
    tmp_pu2[0xb] = 0xc3a50000;
  }
  return;
}

void CG_ParticleExplosion
               (uint32_t param_1,uint32_t *param_2,uint32_t *param_3,int param_4,int param_5,
               int param_6,int param_7)

{
  float tmp_f1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  char *tmp_pc5;
  int tmp_i6;
  uint tmp_u7;
  int tmp_i8;
  
  if (GHIDRA_FIELD(cg_wolfparticles, 12, 4) != 0) {
    tmp_pc5 = "explode1";
    tmp_i8 = 0;
    while( true ) {
      tmp_i6 = Q_stricmp(param_1,tmp_pc5);
      tmp_pu3 = free_particles;
      if (tmp_i6 == 0) break;
      tmp_i8 = tmp_i8 + 1;
      tmp_pc5 = *(char **)(shaderAnimNames + tmp_i8 * 4);
      if (tmp_pc5 == (char *)0x0) {
        CG_Error("CG_ParticleExplosion: unknown animation string: %s\n",param_1);
        return;
      }
    }
    if (free_particles != (uint32_t *)0x0) {
      tmp_pu4 = (uint32_t *)*free_particles;
      *free_particles = active_particles;
      free_particles = tmp_pu4;
      tmp_f1 = (float)g_unk_010906e0;
      active_particles = tmp_pu3;
      tmp_pu3[0xe] = 0x3f800000;
      tmp_pu3[0xf] = 0;
      tmp_pu3[1] = tmp_f1;
      if (param_4 < 0) {
        param_4 = -param_4;
        tmp_pu3[0x1d] = 0;
      }
      else {
        tmp_u7 = rand();
        tmp_f1 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
        tmp_pu3[0x1d] = (int)ROUND((tmp_f1 + tmp_f1) * 179.0);
      }
      tmp_pu3[0x1c] = tmp_i8;
      tmp_pu3[0x13] = (float)param_5;
      tmp_f1 = (float)(&shaderAnimSTRatio)[tmp_i8];
      tmp_pu3[0x12] = (float)param_5 * tmp_f1;
      tmp_pu3[0x14] = (float)param_6;
      tmp_pu3[0x15] = (float)param_6 * tmp_f1;
      param_4 = param_4 + g_unk_010906e0;
      tmp_pu3[0x10] = 7 - (uint)(param_7 == 0);
      tmp_pu3[2] = (float)param_4;
      tmp_pu3[3] = *param_2;
      tmp_pu3[4] = param_2[1];
      tmp_pu3[5] = param_2[2];
      tmp_pu3[6] = *param_3;
      tmp_pu3[7] = param_3[1];
      tmp_u2 = param_3[2];
      tmp_pu3[0xb] = 0;
      tmp_pu3[8] = tmp_u2;
      tmp_pu3[10] = 0;
      tmp_pu3[9] = 0;
    }
  }
  return;
}

void CG_ParticleExplosionTrail
               (uint32_t param_1,uint32_t *param_2,uint32_t *param_3,int param_4,int param_5,
               int param_6,int param_7)

{
  float tmp_f1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  char *tmp_pc5;
  int tmp_i6;
  uint tmp_u7;
  int tmp_i8;
  
  if (GHIDRA_FIELD(cg_trailparticles, 12, 4) != 0) {
    tmp_pc5 = "explode1";
    tmp_i8 = 0;
    while( true ) {
      tmp_i6 = Q_stricmp(param_1,tmp_pc5);
      tmp_pu3 = free_particles;
      if (tmp_i6 == 0) break;
      tmp_i8 = tmp_i8 + 1;
      tmp_pc5 = *(char **)(shaderAnimNames + tmp_i8 * 4);
      if (tmp_pc5 == (char *)0x0) {
        CG_Error("CG_ParticleExplosion: unknown animation string: %s\n",param_1);
        return;
      }
    }
    if (free_particles != (uint32_t *)0x0) {
      tmp_pu4 = (uint32_t *)*free_particles;
      *free_particles = active_particles;
      free_particles = tmp_pu4;
      tmp_f1 = (float)g_unk_010906e0;
      active_particles = tmp_pu3;
      tmp_pu3[0xe] = 0x3f800000;
      tmp_pu3[0xf] = 0;
      tmp_pu3[1] = tmp_f1;
      if (param_4 < 0) {
        param_4 = -param_4;
        tmp_pu3[0x1d] = 0;
      }
      else {
        tmp_u7 = rand();
        tmp_f1 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
        tmp_pu3[0x1d] = (int)ROUND((tmp_f1 + tmp_f1) * 179.0);
      }
      tmp_pu3[0x1c] = tmp_i8;
      tmp_pu3[0x13] = (float)param_5;
      tmp_f1 = (float)(&shaderAnimSTRatio)[tmp_i8];
      tmp_pu3[0x12] = (float)param_5 * tmp_f1;
      tmp_pu3[0x14] = (float)param_6;
      tmp_pu3[0x15] = (float)param_6 * tmp_f1;
      param_4 = param_4 + g_unk_010906e0;
      tmp_pu3[0x10] = 7 - (uint)(param_7 == 0);
      tmp_pu3[2] = (float)param_4;
      tmp_pu3[3] = *param_2;
      tmp_pu3[4] = param_2[1];
      tmp_pu3[5] = param_2[2];
      tmp_pu3[6] = *param_3;
      tmp_pu3[7] = param_3[1];
      tmp_u2 = param_3[2];
      tmp_pu3[0xb] = 0;
      tmp_pu3[8] = tmp_u2;
      tmp_pu3[10] = 0;
      tmp_pu3[9] = 0;
    }
  }
  return;
}

void CG_ParticleImpactSmokePuff(int param_1,uint32_t *param_2)
{
  uint32_t tmp_u1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  uint tmp_u6;
  
  if (GHIDRA_FIELD(cg_smokeparticles, 12, 4) != 0) {
    if (param_1 == 0) {
      CG_Printf("CG_ParticleImpactSmokePuff pshader == ZERO!\n");
    }
    tmp_pu3 = free_particles;
    if (free_particles != (uint32_t *)0x0) {
      tmp_pu4 = (uint32_t *)*free_particles;
      *free_particles = active_particles;
      free_particles = tmp_pu4;
      tmp_f2 = (float)g_unk_010906e0;
      tmp_pu3[0xe] = 0x3e800000;
      tmp_pu3[0xf] = 0;
      active_particles = tmp_pu3;
      tmp_pu3[1] = tmp_f2;
      tmp_i5 = rand();
      tmp_pu3[0x1d] = tmp_i5 % 0x3c + -0x1e;
      tmp_pu3[0x11] = param_1;
      tmp_pu3[2] = (float)(g_unk_010906e0 + 500);
      tmp_pu3[0x18] = (float)(g_unk_010906e0 + 100);
      tmp_u6 = rand();
      tmp_pu3[0x13] = (((float)(tmp_u6 & 0x7fff) / 32767.0) * 0.5 + 1.0) * 8.0;
      tmp_u6 = rand();
      tmp_f2 = (((float)(tmp_u6 & 0x7fff) / 32767.0) * 0.5 + 1.0) * 8.0;
      tmp_pu3[0x10] = 0xc;
      tmp_pu3[0x12] = tmp_f2;
      tmp_pu3[0x14] = tmp_f2 + tmp_f2;
      tmp_pu3[0x15] = (float)tmp_pu3[0x13] + (float)tmp_pu3[0x13];
      tmp_pu3[3] = *param_2;
      tmp_pu3[4] = param_2[1];
      tmp_u1 = param_2[2];
      tmp_pu3[6] = 0;
      tmp_pu3[5] = tmp_u1;
      tmp_pu3[7] = 0;
      tmp_pu3[8] = 0x41a00000;
      tmp_pu3[9] = 0;
      tmp_pu3[10] = 0;
      tmp_pu3[0xb] = 0x41a00000;
      tmp_pu3[0x19] = 1;
    }
  }
  return;
}

void CG_Particle_Bleed(int param_1,uint32_t *param_2,uint32_t param_3,int param_4,int param_5)
{
  uint32_t tmp_u1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  
  if (param_1 == 0) {
    CG_Printf("CG_Particle_Bleed pshader == ZERO!\n");
  }
  tmp_pu3 = free_particles;
  if (free_particles != (uint32_t *)0x0) {
    tmp_pu4 = (uint32_t *)*free_particles;
    *free_particles = active_particles;
    free_particles = tmp_pu4;
    active_particles = tmp_pu3;
    tmp_f2 = (float)g_unk_010906e0;
    tmp_pu3[0x11] = param_1;
    tmp_pu3[0xe] = 0x3f800000;
    tmp_pu3[0xf] = 0;
    tmp_pu3[0x1d] = 0;
    tmp_pu3[1] = tmp_f2;
    tmp_pu3[2] = (float)(param_5 + g_unk_010906e0);
    tmp_i5 = g_unk_010906e0;
    if (param_4 == 0) {
      tmp_i5 = g_unk_010906e0 + 100;
    }
    tmp_pu3[0x18] = (float)tmp_i5;
    tmp_pu3[0x13] = 0x40800000;
    tmp_pu3[0x12] = 0x40800000;
    tmp_i5 = rand();
    tmp_pu3[0x10] = 3;
    tmp_f2 = (float)(tmp_i5 % 3 + 4);
    tmp_pu3[0x14] = tmp_f2;
    tmp_pu3[0x15] = tmp_f2;
    tmp_pu3[3] = *param_2;
    tmp_pu3[4] = param_2[1];
    tmp_u1 = param_2[2];
    tmp_pu3[6] = 0;
    tmp_pu3[5] = tmp_u1;
    tmp_pu3[7] = 0;
    tmp_pu3[8] = 0xc1a00000;
    tmp_pu3[0xb] = 0;
    tmp_pu3[10] = 0;
    tmp_pu3[9] = 0;
    tmp_pu3[0x19] = 0;
    tmp_i5 = rand();
    tmp_pu3[0xe] = 0x3f400000;
    tmp_pu3[0x1d] = tmp_i5 % 0xb3;
    tmp_pu3[0xc] = ~-(uint)(param_4 == 0) + 2;
  }
  return;
}

void CG_Particle_OilParticle
               (int param_1,uint32_t *param_2,float *param_3,int param_4,uint32_t param_5)

{
  float tmp_f1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  
  tmp_f1 = (float)g_unk_010906e0;
  param_4 = g_unk_010906e0 + param_4;
  if (param_1 == 0) {
    CG_Printf("CG_Particle_OilParticle == ZERO!\n");
  }
  tmp_pu3 = free_particles;
  if (free_particles != (uint32_t *)0x0) {
    tmp_pu4 = (uint32_t *)*free_particles;
    *free_particles = active_particles;
    free_particles = tmp_pu4;
    tmp_f2 = (float)g_unk_010906e0;
    tmp_pu3[0x11] = param_1;
    tmp_pu3[0xf] = 0;
    tmp_pu3[0x1d] = 0;
    active_particles = tmp_pu3;
    tmp_pu3[1] = tmp_f2;
    tmp_f2 = (float)g_unk_010906e0;
    tmp_pu3[0x13] = 0x40000000;
    tmp_pu3[0x12] = 0x40000000;
    tmp_pu3[0x15] = 0x3f800000;
    tmp_pu3[0x14] = 0x3f800000;
    tmp_pu3[0x10] = 3;
    tmp_pu3[2] = tmp_f2 + 2000.0;
    tmp_pu3[0x18] = tmp_f2 + 2000.0;
    tmp_pu3[3] = *param_2;
    tmp_pu3[4] = param_2[1];
    tmp_pu3[5] = param_2[2];
    tmp_f1 = (1.0 - tmp_f1 / (float)param_4) * 16.0;
    tmp_pu3[6] = *param_3 * tmp_f1;
    tmp_pu3[7] = param_3[1] * tmp_f1;
    tmp_pu3[8] = tmp_f1 * param_3[2];
    tmp_pu3[0x1a] = param_5;
    tmp_pu3[10] = 0;
    tmp_pu3[9] = 0;
    tmp_pu3[0xb] = 0xc1a00000;
    tmp_pu3[0x19] = 0;
    tmp_i5 = rand();
    tmp_pu3[0xe] = 0x3f000000;
    tmp_pu3[0xc] = 2;
    tmp_pu3[0x1d] = tmp_i5 % 0xb3;
  }
  return;
}

void CG_Particle_OilSlick(int param_1,int param_2)
{
  float tmp_f1;
  uint32_t *tmp_pu2;
  uint32_t *tmp_pu3;
  uint tmp_u4;
  int tmp_i5;
  
  if (param_1 == 0) {
    CG_Printf("CG_Particle_OilSlick == ZERO!\n");
  }
  tmp_pu2 = free_particles;
  if (free_particles != (uint32_t *)0x0) {
    tmp_pu3 = (uint32_t *)*free_particles;
    *free_particles = active_particles;
    free_particles = tmp_pu3;
    active_particles = tmp_pu2;
    tmp_pu2[1] = (float)g_unk_010906e0;
    if (*(float *)(param_2 + 0x88) == 0.0) {
      tmp_f1 = (float)(g_unk_010906e0 + 60000);
    }
    else {
      tmp_f1 = (float)g_unk_010906e0 + *(float *)(param_2 + 0x88);
    }
    tmp_pu2[2] = tmp_f1;
    tmp_pu2[0x18] = tmp_f1;
    tmp_pu2[0xe] = 0x3f800000;
    tmp_pu2[0xf] = 0;
    tmp_pu2[0x1d] = 0;
    tmp_pu2[0x11] = param_1;
    if ((*(float *)(param_2 + 0x80) == 0.0) && (*(float *)(param_2 + 0x84) == 0.0)) {
      tmp_pu2[0x13] = 0x41000000;
      tmp_pu2[0x12] = 0x41000000;
      tmp_pu2[0x14] = 0x41800000;
      tmp_pu2[0x15] = 0x41800000;
    }
    else {
      tmp_pu2[0x13] = *(float *)(param_2 + 0x80);
      tmp_pu2[0x12] = *(uint32_t *)(param_2 + 0x80);
      tmp_pu2[0x14] = *(uint32_t *)(param_2 + 0x84);
      tmp_pu2[0x15] = *(uint32_t *)(param_2 + 0x84);
    }
    tmp_pu2[0x10] = 9;
    tmp_pu2[0x1a] = *(uint32_t *)(param_2 + 0xf4);
    tmp_pu2[3] = *(uint32_t *)(param_2 + 0x5c);
    tmp_pu2[4] = *(uint32_t *)(param_2 + 0x60);
    tmp_pu2[5] = *(uint32_t *)(param_2 + 100);
    tmp_u4 = rand();
    tmp_f1 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu2[5] = (tmp_f1 + tmp_f1) * 0.5 + 0.55 + (float)tmp_pu2[5];
    tmp_pu2[6] = 0;
    tmp_pu2[7] = 0;
    tmp_pu2[8] = 0;
    tmp_pu2[0xb] = 0;
    tmp_pu2[10] = 0;
    tmp_pu2[9] = 0;
    tmp_pu2[0x19] = 0;
    tmp_i5 = rand();
    tmp_pu2[0xe] = 0x3f400000;
    tmp_pu2[0x1d] = tmp_i5 % 0xb3;
  }
  return;
}

void CG_ParticleBloodCloud(int param_1,uint32_t *param_2,uint32_t param_3)
{
  float tmp_f1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  uint tmp_u5;
  long double tmp_l6;
  int local_58;
  uint8_t local_34 [12];
  uint8_t local_28 [24];
  
  tmp_l6 = (long double)VectorLength(param_3);
  vectoangles(param_3,local_34);
  AngleVectors(local_34,local_28,0,0);
  if (*(int *)(param_1 + 0xf4) == 0) {
    tmp_f1 = 16.0;
  }
  else {
    tmp_f1 = 32.0;
  }
  tmp_pu3 = free_particles;
  if (((float)tmp_l6 == 0.0) || (tmp_f1 = (float)tmp_l6 / tmp_f1, tmp_f1 < 1.0)) {
    local_58 = 0;
  }
  else {
    tmp_i4 = (int)ROUND(tmp_f1);
    local_58 = tmp_i4 + -1;
    if (tmp_i4 == 0) {
      return;
    }
  }
  do {
    if (tmp_pu3 == (uint32_t *)0x0) {
      free_particles = tmp_pu3;
      return;
    }
    local_58 = local_58 + -1;
    free_particles = (uint32_t *)*tmp_pu3;
    *tmp_pu3 = active_particles;
    tmp_f1 = (float)g_unk_010906e0;
    tmp_pu3[0xe] = 0x3f800000;
    tmp_pu3[0xf] = 0;
    tmp_pu3[0x1d] = 0;
    active_particles = tmp_pu3;
    tmp_pu3[1] = tmp_f1;
    tmp_pu3[0x11] = GHIDRA_FIELD(cgs, 68088, 4);
    tmp_i4 = g_unk_010906e0 + 0x15e;
    tmp_u5 = rand();
    tmp_f1 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu3[2] = (tmp_f1 + tmp_f1) * 100.0 + (float)tmp_i4;
    tmp_pu3[0x18] = (float)g_unk_010906e0;
    if (*(int *)(param_1 + 0xf4) == 0) {
      tmp_pu3[0x13] = 0x41800000;
      tmp_pu3[0x12] = 0x41800000;
      tmp_pu3[0x14] = 0x41800000;
      tmp_pu3[0x15] = 0x41800000;
    }
    else {
      tmp_pu3[0x13] = 0x42000000;
      tmp_pu3[0x12] = 0x42000000;
      tmp_pu3[0x14] = 0x42000000;
      tmp_pu3[0x15] = 0x42000000;
    }
    tmp_pu3[0x10] = 3;
    tmp_pu3[3] = *param_2;
    tmp_pu3[4] = param_2[1];
    tmp_u2 = param_2[2];
    tmp_pu3[6] = 0;
    tmp_pu3[5] = tmp_u2;
    tmp_pu3[7] = 0;
    tmp_pu3[8] = 0xbf800000;
    tmp_pu3[0xb] = 0;
    tmp_pu3[10] = 0;
    tmp_pu3[9] = 0;
    tmp_pu3[0x19] = 0;
    tmp_i4 = rand();
    tmp_pu3[0xc] = 2;
    tmp_pu3[0xe] = 0x3f400000;
    tmp_pu3[0x1d] = tmp_i4 % 0xb3;
    tmp_pu3 = free_particles;
  } while (local_58 != -1);
  return;
}

void CG_ParticleBloodCloudZombie(int param_1,uint32_t *param_2,uint32_t param_3)
{
  float tmp_f1;
  float tmp_f2;
  uint32_t tmp_u3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  uint tmp_u6;
  long double tmp_l7;
  int local_58;
  uint local_54;
  uint8_t local_34 [12];
  uint8_t local_28 [24];
  
  tmp_l7 = (long double)VectorLength(param_3);
  tmp_f1 = (float)tmp_l7;
  vectoangles(param_3,local_34);
  AngleVectors(local_34,local_28,0,0);
  if (*(int *)(param_1 + 0xf4) == 0) {
    tmp_f2 = 4.0;
  }
  else {
    tmp_f2 = 10.0;
  }
  tmp_pu4 = free_particles;
  if ((tmp_f1 == 0.0) || (tmp_f1 / tmp_f2 < 1.0)) {
    local_58 = 0;
  }
  else {
    tmp_i5 = (int)ROUND(tmp_f1 / tmp_f2);
    local_58 = tmp_i5 + -1;
    if (tmp_i5 == 0) {
      return;
    }
  }
  do {
    if (tmp_pu4 == (uint32_t *)0x0) {
      free_particles = tmp_pu4;
      return;
    }
    local_58 = local_58 + -1;
    free_particles = (uint32_t *)*tmp_pu4;
    *tmp_pu4 = active_particles;
    tmp_f2 = (float)g_unk_010906e0;
    tmp_pu4[0xe] = 0x3e4ccccd;
    tmp_pu4[0x1d] = 0;
    active_particles = tmp_pu4;
    tmp_pu4[1] = tmp_f2;
    tmp_pu4[0xf] = 0;
    tmp_pu4[0x11] = GHIDRA_FIELD(cgs, 68836, 4);
    if (tmp_f1 == 0.0) {
      tmp_i5 = g_unk_010906e0 + 0x2ee;
      tmp_u6 = rand();
      tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
      tmp_pu4[2] = (tmp_f2 + tmp_f2) * 500.0 + (float)tmp_i5;
    }
    else {
      tmp_i5 = g_unk_010906e0 + 0xdac;
      tmp_u6 = rand();
      tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
      tmp_pu4[2] = (tmp_f2 + tmp_f2) * 2000.0 + (float)tmp_i5;
    }
    tmp_pu4[0x18] = (float)g_unk_010906e0;
    if (*(int *)(param_1 + 0xf4) == 0) {
      tmp_pu4[0x13] = 0x41800000;
      tmp_u3 = 0x404ccccd;
      tmp_pu4[0x12] = 0x41800000;
      tmp_pu4[0x14] = 0x42800000;
      tmp_pu4[0x15] = 0x42800000;
    }
    else {
      tmp_pu4[0x13] = 0x42000000;
      tmp_u3 = 0x40cccccd;
      tmp_pu4[0x12] = 0x42000000;
      tmp_pu4[0x14] = 0x42c00000;
      tmp_pu4[0x15] = 0x42c00000;
    }
    if (tmp_f1 == 0.0) {
      tmp_pu4[0x13] = tmp_u3;
      tmp_pu4[0x12] = tmp_u3;
      tmp_pu4[0x14] = 0x41800000;
      tmp_pu4[0x15] = 0x41800000;
    }
    tmp_pu4[0x10] = 3;
    tmp_pu4[3] = *param_2;
    tmp_pu4[4] = param_2[1];
    tmp_pu4[5] = param_2[2];
    local_54 = rand();
    local_54 = local_54 & 0x7fff;
    tmp_f2 = (float)local_54 / 32767.0 - 0.5;
    tmp_pu4[6] = (tmp_f2 + tmp_f2) * 6.0;
    local_54 = rand();
    local_54 = local_54 & 0x7fff;
    tmp_f2 = (float)local_54 / 32767.0 - 0.5;
    tmp_pu4[7] = (tmp_f2 + tmp_f2) * 6.0;
    local_54 = rand();
    local_54 = local_54 & 0x7fff;
    tmp_pu4[8] = ((float)local_54 / 32767.0) * 6.0;
    local_54 = rand();
    local_54 = local_54 & 0x7fff;
    tmp_f2 = (float)local_54 / 32767.0 - 0.5;
    tmp_pu4[9] = (tmp_f2 + tmp_f2) * 3.0;
    rand();
    tmp_pu4[0xb] = 0;
    tmp_pu4[10] = 0;
    tmp_pu4[9] = 0;
    tmp_pu4[0x19] = 0;
    tmp_i5 = rand();
    tmp_pu4[0xc] = 5;
    tmp_pu4[0x1d] = tmp_i5 % 0xb3;
    tmp_pu4 = free_particles;
  } while (local_58 != -1);
  return;
}

void CG_ParticleSparks(uint32_t *param_1,uint32_t *param_2,int param_3,float param_4,
                      float param_5,float param_6)

{
  uint32_t tmp_u1;
  float tmp_f2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  uint32_t *tmp_pu5;
  uint tmp_u6;
  
  tmp_pu4 = free_particles;
  if ((GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0) && (free_particles != (uint32_t *)0x0)) {
    tmp_pu5 = (uint32_t *)*free_particles;
    *free_particles = active_particles;
    free_particles = tmp_pu5;
    active_particles = tmp_pu4;
    tmp_pu4[1] = (float)g_unk_010906e0;
    tmp_pu4[2] = (float)(g_unk_010906e0 + param_3);
    tmp_i3 = g_unk_010906e0;
    tmp_pu4[0xc] = 3;
    tmp_pu4[0xe] = 0x3ecccccd;
    tmp_pu4[0xf] = 0;
    tmp_pu4[0x12] = 0x3f000000;
    tmp_pu4[0x13] = 0x3f000000;
    tmp_pu4[0x14] = 0x3f000000;
    tmp_pu4[0x15] = 0x3f000000;
    tmp_pu4[0x18] = (float)(param_3 / 2 + tmp_i3);
    tmp_u1 = GHIDRA_FIELD(cgs, 68004, 4);
    tmp_pu4[0x10] = 3;
    tmp_pu4[0x11] = tmp_u1;
    tmp_pu4[3] = *param_1;
    tmp_pu4[4] = param_1[1];
    tmp_pu4[5] = param_1[2];
    tmp_u6 = rand();
    tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu4[3] = (tmp_f2 + tmp_f2) * param_4 + (float)tmp_pu4[3];
    tmp_u6 = rand();
    tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu4[4] = (tmp_f2 + tmp_f2) * param_5 + (float)tmp_pu4[4];
    tmp_pu4[6] = *param_2;
    tmp_pu4[7] = param_2[1];
    tmp_u1 = param_2[2];
    tmp_pu4[0xb] = 0;
    tmp_pu4[8] = tmp_u1;
    tmp_pu4[10] = 0;
    tmp_pu4[9] = 0;
    tmp_u6 = rand();
    tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu4[6] = (tmp_f2 + tmp_f2) * 4.0 + (float)tmp_pu4[6];
    tmp_u6 = rand();
    tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu4[7] = (tmp_f2 + tmp_f2) * 4.0 + (float)tmp_pu4[7];
    tmp_u6 = rand();
    tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu4[8] = ((tmp_f2 + tmp_f2) * 10.0 + 20.0) * param_6 + (float)tmp_pu4[8];
    tmp_u6 = rand();
    tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu4[9] = (tmp_f2 + tmp_f2) * 4.0;
    tmp_u6 = rand();
    tmp_f2 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu4[10] = (tmp_f2 + tmp_f2) * 4.0;
  }
  return;
}

void CG_ParticleDust(int param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint32_t tmp_u5;
  float tmp_f6;
  uint32_t *tmp_pu7;
  int tmp_i8;
  long double tmp_l9;
  int local_60;
  uint local_5c;
  uint local_54;
  float local_4c;
  uint8_t local_34 [12];
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x9eaa9;
  if (GHIDRA_FIELD(cg_smokeparticles, 12, 4) != 0) {
    *param_3 = -*param_3;
    param_3[1] = -param_3[1];
    param_3[2] = -param_3[2];
    tmp_l9 = (long double)VectorLength(param_3);
    tmp_f1 = (float)tmp_l9;
    vectoangles(param_3,local_34);
    AngleVectors(local_34,&local_28,0,0);
    if (*(int *)(param_1 + 0xf4) == 0) {
      local_4c = 16.0;
    }
    else {
      local_4c = 32.0;
    }
    if ((tmp_f1 == 0.0) || (tmp_f1 / local_4c < 1.0)) {
      tmp_f2 = *param_2;
      tmp_f3 = param_2[1];
      tmp_f4 = param_2[2];
      local_60 = 0;
    }
    else {
      tmp_i8 = (int)ROUND(tmp_f1 / local_4c);
      tmp_f2 = *param_2;
      tmp_f3 = param_2[1];
      tmp_f4 = param_2[2];
      local_60 = tmp_i8 + -1;
      if (tmp_i8 == 0) {
        return;
      }
    }
    tmp_f2 = local_28 * local_4c + tmp_f2;
    tmp_f3 = local_24 * local_4c + tmp_f3;
    tmp_f4 = tmp_f4 + local_20 * local_4c;
    tmp_pu7 = free_particles;
    while (free_particles = tmp_pu7, tmp_pu7 != (uint32_t *)0x0) {
      local_60 = local_60 + -1;
      free_particles = (uint32_t *)*tmp_pu7;
      *tmp_pu7 = active_particles;
      tmp_f6 = (float)g_unk_010906e0;
      tmp_pu7[0xe] = 0x40a00000;
      tmp_pu7[0x1d] = 0;
      active_particles = tmp_pu7;
      tmp_pu7[1] = tmp_f6;
      tmp_pu7[0xf] = 0;
      tmp_pu7[0x11] = GHIDRA_FIELD(cgs, 68836, 4);
      if (tmp_f1 == 0.0) {
        tmp_i8 = g_unk_010906e0 + 0x2ee;
        local_54 = rand();
        local_54 = local_54 & 0x7fff;
        tmp_f6 = (float)local_54 / 32767.0 - 0.5;
        tmp_pu7[2] = (tmp_f6 + tmp_f6) * 500.0 + (float)tmp_i8;
      }
      else {
        tmp_i8 = g_unk_010906e0 + 0x1194;
        local_54 = rand();
        local_54 = local_54 & 0x7fff;
        tmp_f6 = (float)local_54 / 32767.0 - 0.5;
        tmp_pu7[2] = (tmp_f6 + tmp_f6) * 3500.0 + (float)tmp_i8;
      }
      tmp_pu7[0x18] = (float)g_unk_010906e0;
      if (*(int *)(param_1 + 0xf4) == 0) {
        tmp_pu7[0x13] = 0x41800000;
        tmp_u5 = 0x404ccccd;
        tmp_pu7[0x12] = 0x41800000;
        tmp_pu7[0x14] = 0x42800000;
        tmp_pu7[0x15] = 0x42800000;
      }
      else {
        tmp_pu7[0x13] = 0x42000000;
        tmp_u5 = 0x40cccccd;
        tmp_pu7[0x12] = 0x42000000;
        tmp_pu7[0x14] = 0x42c00000;
        tmp_pu7[0x15] = 0x42c00000;
      }
      if (tmp_f1 == 0.0) {
        tmp_pu7[0x13] = tmp_u5;
        tmp_pu7[0x12] = tmp_u5;
        tmp_pu7[0x14] = 0x41800000;
        tmp_pu7[0x15] = 0x41800000;
      }
      tmp_pu7[0x10] = 3;
      tmp_pu7[3] = tmp_f2;
      tmp_pu7[4] = tmp_f3;
      tmp_pu7[5] = tmp_f4;
      local_5c = rand();
      local_5c = local_5c & 0x7fff;
      tmp_f6 = (float)local_5c / 32767.0 - 0.5;
      tmp_pu7[6] = (tmp_f6 + tmp_f6) * 6.0;
      local_5c = rand();
      local_5c = local_5c & 0x7fff;
      tmp_f6 = (float)local_5c / 32767.0 - 0.5;
      tmp_pu7[7] = (tmp_f6 + tmp_f6) * 6.0;
      local_5c = rand();
      local_5c = local_5c & 0x7fff;
      tmp_pu7[8] = ((float)local_5c / 32767.0) * 20.0;
      local_5c = rand();
      local_5c = local_5c & 0x7fff;
      tmp_f6 = (float)local_5c / 32767.0 - 0.5;
      tmp_pu7[9] = (tmp_f6 + tmp_f6) * 3.0;
      rand();
      tmp_pu7[0xb] = 0;
      tmp_pu7[10] = 0;
      tmp_pu7[9] = 0;
      tmp_pu7[0x19] = 0;
      tmp_i8 = rand();
      tmp_pu7[0x1d] = tmp_i8 % 0xb3;
      tmp_i8 = *(int *)(param_1 + 0xf4);
      tmp_pu7[0xe] = 0x3f400000;
      tmp_pu7[0xc] = (-(uint)(tmp_i8 == 0) & 0xfffffffd) + 4;
      if (local_60 == -1) {
        return;
      }
      tmp_f2 = local_28 * local_4c + tmp_f2;
      tmp_f3 = local_24 * local_4c + tmp_f3;
      tmp_f4 = local_20 * local_4c + tmp_f4;
      tmp_pu7 = free_particles;
    }
  }
  return;
}

void CG_ParticleMisc(int param_1,uint32_t *param_2,int param_3,int param_4)
{
  uint32_t tmp_u1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  
  if (param_1 == 0) {
    CG_Printf("CG_ParticleImpactSmokePuff pshader == ZERO!\n");
  }
  tmp_pu3 = free_particles;
  if (free_particles != (uint32_t *)0x0) {
    tmp_pu4 = (uint32_t *)*free_particles;
    *free_particles = active_particles;
    free_particles = tmp_pu4;
    tmp_f2 = (float)g_unk_010906e0;
    tmp_pu3[0xe] = 0x3f800000;
    tmp_pu3[0xf] = 0;
    active_particles = tmp_pu3;
    tmp_pu3[1] = tmp_f2;
    tmp_i5 = rand();
    tmp_pu3[0x1d] = tmp_i5 % 0xb3;
    tmp_pu3[0x11] = param_1;
    if (0 < param_4) {
      param_4 = param_4 + g_unk_010906e0;
    }
    tmp_pu3[2] = (float)param_4;
    tmp_f2 = (float)g_unk_010906e0;
    tmp_pu3[0x10] = 0xf;
    tmp_pu3[0x18] = tmp_f2;
    tmp_f2 = (float)param_3;
    tmp_pu3[0x13] = tmp_f2;
    tmp_pu3[0x12] = tmp_f2;
    tmp_pu3[0x14] = tmp_f2;
    tmp_pu3[0x15] = tmp_f2;
    tmp_pu3[3] = *param_2;
    tmp_pu3[4] = param_2[1];
    tmp_u1 = param_2[2];
    tmp_pu3[0x19] = 0;
    tmp_pu3[5] = tmp_u1;
  }
  return;
}

