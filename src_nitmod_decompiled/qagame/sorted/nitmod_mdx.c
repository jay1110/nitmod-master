/* MDX hit detection / antilag helpers — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_mdx.h"

void etpro_FinalizeTracemapClamp(int *param_1,int *param_2)
{
  int tmp_i1;
  
  if (*param_1 < 0) {
    *param_1 = 0;
  }
  else if (0xff < *param_1) {
    *param_1 = 0xff;
    tmp_i1 = *param_2;
    goto joined_r0x00044eba;
  }
  tmp_i1 = *param_2;
joined_r0x00044eba:
  if (-1 < tmp_i1) {
    if (0xff < tmp_i1) {
      *param_2 = 0xff;
    }
    return;
  }
  *param_2 = 0;
  return;
}

mdx_SwingAngles(float *param_1,int *param_2,float param_3,float param_4,float param_5,float param_6)
{
  int tmp_i1;
  long double tmp_l2;
  long double tmp_l3;
  
  if (*param_2 == 0) {
    tmp_l2 = (long double)AngleSubtract(param_3,*param_1);
    if (((long double)param_4 <= tmp_l2) || (tmp_l2 < -(long double)param_4)) {
      *param_2 = 1;
    }
    else if (*param_2 == 0) {
      return;
    }
  }
  tmp_l2 = (long double)AngleSubtract(param_3,*param_1);
  tmp_l3 = (long double)0.5;
  if ((long double)0.5 <= (long double)(float)((long double)0.05 * ABS(tmp_l2))) {
    tmp_l3 = (long double)(float)((long double)0.05 * ABS(tmp_l2));
  }
  if (tmp_l2 < (long double)0) {
    if ((long double)0 <= tmp_l2) {
      tmp_l2 = (long double)*param_1;
      goto LAB_0004687e;
    }
    tmp_i1 = 0;
    tmp_l3 = -(long double)param_6 * tmp_l3 * (long double)50.0;
    if (tmp_l2 < tmp_l3) {
      tmp_i1 = 1;
      tmp_l2 = tmp_l3;
    }
  }
  else {
    tmp_i1 = 0;
    tmp_l3 = tmp_l3 * (long double)50.0 * (long double)param_6;
    if (tmp_l3 < tmp_l2) {
      tmp_i1 = 2;
      tmp_l2 = tmp_l3;
    }
  }
  *param_2 = tmp_i1;
  tmp_l2 = (long double)AngleMod((float)(tmp_l2 + (long double)*param_1));
  *param_1 = (float)tmp_l2;
LAB_0004687e:
  tmp_l2 = (long double)AngleSubtract(param_3,(float)tmp_l2);
  if ((long double)param_5 < tmp_l2) {
    tmp_l2 = (long double)
            AngleMod((float)((long double)param_3 - ((long double)param_5 - (long double)1)));
    *param_1 = (float)tmp_l2;
  }
  else if (tmp_l2 < -(long double)param_5) {
    tmp_l2 = (long double)AngleMod((param_5 - 1.0) + param_3);
    *param_1 = (float)tmp_l2;
    return;
  }
  return;
}

void mdx_calculate_bone_lerp_constprop_6
          (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  float *pfVar1;
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
  int tmp_i12;
  float tmp_f13;
  float tmp_f14;
  int tmp_i15;
  float *pfVar16;
  int tmp_i17;
  int tmp_i18;
  int tmp_i19;
  int tmp_i20;
  
  pfVar16 = mdx_bones;
  tmp_i18 = param_6 * 0x4c;
  tmp_i20 = *(int *)(param_2 + 0x44) + tmp_i18;
  if (*(float *)(tmp_i20 + 0x48) == 0.0) {
    tmp_i17 = *(int *)(param_1 + 0x98);
    tmp_f2 = *(float *)(param_1 + 0xa8);
    tmp_i19 = *(int *)(param_1 + 0x7c);
    tmp_i12 = *(int *)(param_3 + 0x44);
    tmp_i15 = param_3;
  }
  else {
    tmp_i17 = *(int *)(param_1 + 0xa0);
    tmp_f2 = *(float *)(param_1 + 0xac);
    tmp_i19 = *(int *)(param_1 + 0x84);
    tmp_i20 = tmp_i18 + *(int *)(param_4 + 0x44);
    tmp_i12 = *(int *)(param_5 + 0x44);
    param_2 = param_4;
    tmp_i15 = param_5;
  }
  if (param_6 != 0) {
    mdx_calculate_bone_lerp_constprop_6(param_3,param_4,param_5,*(uint32_t *)(tmp_i20 + 0x40));
    pfVar16 = mdx_bones;
    tmp_i19 = *(int *)(tmp_i19 * 0x14 + *(int *)(param_2 + 0x4c) + 0x10) + param_6 * 10;
    tmp_i17 = param_6 * 10 + *(int *)(*(int *)(tmp_i15 + 0x4c) + tmp_i17 * 0x14 + 0x10);
    tmp_f3 = *(float *)(tmp_i12 + 0x44 + tmp_i18);
    tmp_i18 = (int)*(short *)(tmp_i17 + 6) >> 4;
    if (tmp_i18 < 0) {
      tmp_i18 = tmp_i18 + 0x1000;
    }
    tmp_f4 = *(float *)(sintable + tmp_i18 * 4);
    tmp_f5 = *(float *)(sintable + ((tmp_i18 + 0x400) % 0x1000) * 4);
    tmp_i18 = (int)*(short *)(tmp_i17 + 8) >> 4;
    if (tmp_i18 < 0) {
      tmp_i18 = tmp_i18 + 0x1000;
    }
    tmp_f6 = *(float *)(sintable + tmp_i18 * 4);
    tmp_f7 = *(float *)(sintable + ((tmp_i18 + 0x400) % 0x1000) * 4);
    tmp_i18 = (int)*(short *)(tmp_i19 + 6) >> 4;
    if (tmp_i18 < 0) {
      tmp_i18 = tmp_i18 + 0x1000;
    }
    tmp_f8 = *(float *)(sintable + tmp_i18 * 4);
    tmp_f9 = *(float *)(sintable + ((tmp_i18 + 0x400) % 0x1000) * 4);
    tmp_i18 = (int)*(short *)(tmp_i19 + 8) >> 4;
    if (tmp_i18 < 0) {
      tmp_i18 = tmp_i18 + 0x1000;
    }
    tmp_f10 = *(float *)(sintable + tmp_i18 * 4);
    tmp_f11 = *(float *)(sintable + ((tmp_i18 + 0x400) % 0x1000) * 4);
    pfVar1 = mdx_bones + param_6 * 3;
    tmp_f13 = tmp_f8 * tmp_f11 * 0.0 + (tmp_f9 * tmp_f11 * *(float *)(tmp_i20 + 0x44) - tmp_f10 * 0.0);
    tmp_f10 = tmp_f10 * tmp_f8 * 0.0 + tmp_f11 * 0.0 + tmp_f9 * tmp_f10 * *(float *)(tmp_i20 + 0x44);
    tmp_f11 = tmp_f9 * 0.0 + (0.0 - tmp_f8 * *(float *)(tmp_i20 + 0x44));
    tmp_f14 = mdx_bones[*(int *)(tmp_i20 + 0x40) * 3] + tmp_f13;
    *pfVar1 = tmp_f14;
    tmp_f9 = pfVar16[*(int *)(tmp_i20 + 0x40) * 3 + 1] + tmp_f10;
    pfVar1[1] = tmp_f9;
    tmp_f8 = pfVar16[*(int *)(tmp_i20 + 0x40) * 3 + 2];
    *pfVar1 = ((tmp_f4 * tmp_f7 * 0.0 + (tmp_f5 * tmp_f7 * tmp_f3 - tmp_f6 * 0.0)) - tmp_f13) * tmp_f2 +
              tmp_f14;
    pfVar1[1] = tmp_f9 + ((tmp_f6 * tmp_f4 * 0.0 + tmp_f7 * 0.0 + tmp_f5 * tmp_f6 * tmp_f3) - tmp_f10) *
                        tmp_f2;
    pfVar1[2] = tmp_f8 + tmp_f11 + (((0.0 - tmp_f3 * tmp_f4) + tmp_f5 * 0.0) - tmp_f11) * tmp_f2;
    return;
  }
  tmp_f3 = 1.0 - tmp_f2;
  tmp_i19 = tmp_i19 * 0x14;
  tmp_f5 = tmp_f3 * *(float *)(*(int *)(param_2 + 0x4c) + 4 + tmp_i19) + vec3_origin;
  *mdx_bones = tmp_f5;
  tmp_f4 = tmp_f3 * *(float *)(*(int *)(param_2 + 0x4c) + 8 + tmp_i19) + g_unk_008277c4;
  pfVar16[1] = tmp_f4;
  tmp_f3 = tmp_f3 * *(float *)(*(int *)(param_2 + 0x4c) + 0xc + tmp_i19) + g_unk_008277c8;
  tmp_i17 = tmp_i17 * 0x14;
  pfVar16[2] = tmp_f3;
  *pfVar16 = *(float *)(*(int *)(tmp_i15 + 0x4c) + 4 + tmp_i17) * tmp_f2 + tmp_f5;
  pfVar16[1] = *(float *)(*(int *)(tmp_i15 + 0x4c) + 8 + tmp_i17) * tmp_f2 + tmp_f4;
  pfVar16[2] = tmp_f2 * *(float *)(*(int *)(tmp_i15 + 0x4c) + 0xc + tmp_i17) + tmp_f3;
  return;
}

void Init_Hit_ETKill(void)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  uint8_t *tmp_pu3;
  uint32_t *tmp_pu4;
  
  tmp_pu4 = &HitBoxList;
  for (tmp_i1 = 0x286; tmp_i1 != 0; tmp_i1 = tmp_i1 + -1) {
    *tmp_pu4 = 0;
    tmp_pu4 = tmp_pu4 + 1;
  }
  tmp_pu2 = &g_unk_003d7394;
  do {
    *(uint32_t *)(tmp_pu2 + -0x54) = 0;
    *(uint32_t *)(tmp_pu2 + -0x4c) = 0xb;
    tmp_pu3 = tmp_pu2 + 0x98;
    AxisCopy(axisDefault,tmp_pu2);
    *(uint32_t *)(tmp_pu2 + -0x40) = 0x3f800000;
    *(uint32_t *)(tmp_pu2 + -0x3c) = 0x3f800000;
    *(uint32_t *)(tmp_pu2 + -0x38) = 0x3f800000;
    *(uint32_t *)(tmp_pu2 + -0x34) = 0x3f800000;
    *(uint32_t *)(tmp_pu2 + -0x30) = 0x3f800000;
    *(uint32_t *)(tmp_pu2 + -0x2c) = 0x3f800000;
    *(uint32_t *)(tmp_pu2 + -0x48) = 0xffffffff;
    *(uint32_t *)(tmp_pu2 + -0x28) = 0x3f800000;
    *(uint32_t *)(tmp_pu2 + -0x24) = 0x3f800000;
    *(uint32_t *)(tmp_pu2 + -0x20) = 0x3f800000;
    *(uint32_t *)(tmp_pu2 + -0x44) = 0xffffffff;
    *(uint32_t *)(tmp_pu2 + -0x1c) = 0x3f800000;
    *(uint32_t *)(tmp_pu2 + -0x18) = 0x3f800000;
    *(uint32_t *)(tmp_pu2 + -0x14) = 0x3f800000;
    tmp_pu2 = tmp_pu3;
  } while (tmp_pu3 != &g_unk_003d7dac);
  HitBoxList = 7;
  g_unk_003d7350 = 0xffffffff;
  g_unk_003d7344 = 0;
  g_unk_003d734c = 0;
  g_unk_003d7354 = 0xc0a00000;
  g_unk_003d7358 = 0xc0880000;
  g_unk_003d735c = 0xc0a00000;
  g_unk_003d7360 = 0x40a00000;
  g_unk_003d7364 = 0x40880000;
  g_unk_003d7368 = 0x40a00000;
  g_unk_003d736c = 0x41200000;
  g_unk_003d7370 = 0x41080000;
  g_unk_003d7374 = 0x41200000;
  g_unk_003d7388 = 0x3f000000;
  g_unk_003d738c = 0xbf000000;
  g_unk_003d7390 = 0x40b00000;
  Q_strncpyz(&g_unk_003d73b8,&g_unk_0023ae0a,0x20);
  g_unk_003d73dc = 1;
  g_unk_003d73e4 = 0;
  g_unk_003d73e8 = 4;
  g_unk_003d73d8 = 7;
  g_unk_003d73ec = 0xc0400000;
  g_unk_003d73f0 = 0xc0400000;
  g_unk_003d73f4 = 0xc0400000;
  g_unk_003d73f8 = 0x40800000;
  g_unk_003d73fc = 0x40800000;
  g_unk_003d7400 = 0x40400000;
  g_unk_003d7404 = 0x40e00000;
  g_unk_003d7408 = 0x40e00000;
  g_unk_003d740c = 0x40c00000;
  g_unk_003d7410 = 0;
  g_unk_003d7414 = 0;
  g_unk_003d7418 = 0x41700000;
  Q_strncpyz(&g_unk_003d7450,&g_unk_00240054,0x20);
  g_unk_003d7768 = 4;
  g_unk_003d7774 = 7;
  g_unk_003d7778 = 6;
  g_unk_003d777c = 0xc0400000;
  g_unk_003d7780 = 0xc0400000;
  g_unk_003d7784 = 0xc1080000;
  g_unk_003d7788 = 0x40400000;
  g_unk_003d778c = 0x40400000;
  g_unk_003d7790 = 0x41080000;
  g_unk_003d7794 = 0x40c00000;
  g_unk_003d7798 = 0x40c00000;
  g_unk_003d779c = 0x41880000;
  Q_strncpyz(&g_unk_003d77e0,"RIGHT FOREARM",0x20);
  g_unk_003d7940 = 9;
  g_unk_003d7930 = 3;
  g_unk_003d793c = 10;
  g_unk_003d7944 = 0xc0400000;
  g_unk_003d7948 = 0xc0400000;
  g_unk_003d794c = 0xc1080000;
  g_unk_003d7950 = 0x40400000;
  g_unk_003d7954 = 0x40400000;
  g_unk_003d7958 = 0x41080000;
  g_unk_003d795c = 0x40c00000;
  g_unk_003d7960 = 0x40c00000;
  g_unk_003d7964 = 0x41880000;
  g_unk_003d797c = 0x40000000;
  g_unk_003d7980 = 0;
  Q_strncpyz(&g_unk_003d79a8,"LEFT FOREARM",0x20);
  g_unk_003d79c8 = 2;
  g_unk_003d79d4 = 0xffffffff;
  g_unk_003d79dc = 0xc0800000;
  g_unk_003d79e0 = 0xc0800000;
  g_unk_003d79e4 = 0xc0800000;
  g_unk_003d79e8 = 0x40800000;
  g_unk_003d79ec = 0x40800000;
  g_unk_003d79f0 = 0x40800000;
  g_unk_003d79f4 = 0x41000000;
  g_unk_003d79f8 = 0x41000000;
  g_unk_003d79fc = 0x41000000;
  Q_strncpyz(&g_unk_003d7a40,"TORSO2",0x20);
  g_unk_003d76d0 = 4;
  g_unk_003d76dc = 6;
  g_unk_003d76e0 = 4;
  g_unk_003d76e4 = 0xc0800000;
  g_unk_003d76e8 = 0xc0400000;
  g_unk_003d76ec = 0xc0f00000;
  g_unk_003d76f0 = 0x40800000;
  g_unk_003d76f4 = 0x40400000;
  g_unk_003d76f8 = 0x40f00000;
  g_unk_003d76fc = 0x41000000;
  g_unk_003d7700 = 0x40c00000;
  g_unk_003d7704 = 0x41700000;
  g_unk_003d7708 = 0;
  g_unk_003d770c = 0xc1100000;
  g_unk_003d7710 = 0x41000000;
  Q_strncpyz(&g_unk_003d7748,"RIGHTARM",0x20);
  g_unk_003d78a4 = 9;
  g_unk_003d78a8 = 4;
  g_unk_003d7898 = 3;
  g_unk_003d78ac = 0xc0800000;
  g_unk_003d78b0 = 0xc0400000;
  g_unk_003d78b4 = 0xc0f00000;
  g_unk_003d78b8 = 0x40800000;
  g_unk_003d78bc = 0x40400000;
  g_unk_003d78c0 = 0x40f00000;
  g_unk_003d78c4 = 0x41000000;
  g_unk_003d78c8 = 0x40c00000;
  g_unk_003d78cc = 0x41700000;
  g_unk_003d78d0 = 0;
  g_unk_003d78d4 = 0x41100000;
  g_unk_003d78d8 = 0x41000000;
  Q_strncpyz(&g_unk_003d7910,"LEFTARM",0x20);
  g_unk_003d7a60 = 2;
  g_unk_003d7a6c = 0xc;
  g_unk_003d7a74 = 0xc0e00000;
  g_unk_003d7a78 = 0xc1080000;
  g_unk_003d7a7c = 0xc0c00000;
  g_unk_003d7a80 = 0x40e00000;
  g_unk_003d7a84 = 0x41080000;
  g_unk_003d7a88 = 0x40c00000;
  g_unk_003d7a8c = 0x41600000;
  g_unk_003d7a90 = 0x41880000;
  g_unk_003d7a94 = 0x41400000;
  g_unk_003d7aac = 0;
  g_unk_003d7ab0 = 0xc0000000;
  Q_strncpyz(&g_unk_003d7ad8,&g_unk_0024008c,0x20);
  g_unk_003d75a0 = 2;
  g_unk_003d75ac = 4;
  g_unk_003d75b4 = 0xc0c00000;
  g_unk_003d75b8 = 0xc1080000;
  g_unk_003d75bc = 0xc0933333;
  g_unk_003d75c0 = 0x40c00000;
  g_unk_003d75c4 = 0x41080000;
  g_unk_003d75c8 = 0x40933333;
  g_unk_003d75cc = 0x41400000;
  g_unk_003d75d0 = 0x41880000;
  g_unk_003d75d4 = 0x41133333;
  g_unk_003d75ec = 0;
  g_unk_003d75f0 = 0x40c00000;
  Q_strncpyz(&g_unk_003d7618,"CHEST",0x20);
  g_unk_003d7514 = 0xffffffff;
  g_unk_003d7508 = 2;
  g_unk_003d751c = 0xc0700000;
  g_unk_003d7520 = 0xc0f00000;
  g_unk_003d7524 = 0xc0e00000;
  g_unk_003d7528 = 0x40700000;
  g_unk_003d752c = 0x40f00000;
  g_unk_003d7530 = 0x40e00000;
  g_unk_003d7554 = 0;
  g_unk_003d7558 = 0xbf800000;
  Q_strncpyz(&g_unk_003d7580,"BACKPACK",0x20);
  g_unk_003d7470 = 2;
  g_unk_003d747c = 2;
  g_unk_003d7484 = 0xc0c00000;
  g_unk_003d7488 = 0xc1080000;
  g_unk_003d748c = 0xc0800000;
  g_unk_003d7490 = 0x40c00000;
  g_unk_003d7494 = 0x41080000;
  g_unk_003d7498 = 0x40800000;
  g_unk_003d74bc = 0;
  g_unk_003d74c0 = 0x40c00000;
  Q_strncpyz(&g_unk_003d74e8,"TORSO",0x20);
  g_unk_003d7638 = 6;
  g_unk_003d7648 = 0xd;
  g_unk_003d7644 = 5;
  g_unk_003d764c = 0xc0a00000;
  g_unk_003d7650 = 0xc0a00000;
  g_unk_003d7654 = 0xc1100000;
  g_unk_003d7658 = 0x40a00000;
  g_unk_003d765c = 0x40a00000;
  g_unk_003d7660 = 0x41100000;
  g_unk_003d7664 = 0x41200000;
  g_unk_003d7668 = 0x41200000;
  g_unk_003d766c = 0x41900000;
  g_unk_003d7684 = 0xbf800000;
  g_unk_003d7688 = 0x40000000;
  Q_strncpyz(&g_unk_003d76b0,"RIGHT THIGH",0x20);
  g_unk_003d780c = 8;
  g_unk_003d7810 = 0xf;
  g_unk_003d7800 = 5;
  g_unk_003d7814 = 0xc0a00000;
  g_unk_003d7818 = 0xc0a00000;
  g_unk_003d781c = 0xc1100000;
  g_unk_003d7820 = 0x40a00000;
  g_unk_003d7824 = 0x40a00000;
  g_unk_003d7828 = 0x41100000;
  g_unk_003d782c = 0x41200000;
  g_unk_003d7830 = 0x41200000;
  g_unk_003d7834 = 0x41900000;
  g_unk_003d784c = 0;
  g_unk_003d7850 = 0x40000000;
  Q_strncpyz(&g_unk_003d7878,"LEFT THIGH",0x20);
  g_unk_003d7af8 = 6;
  g_unk_003d7b04 = 0xd;
  g_unk_003d7b08 = 0xe;
  g_unk_003d7b0c = 0xc0b00000;
  g_unk_003d7b10 = 0xc0a00000;
  g_unk_003d7b14 = 0xc1000000;
  g_unk_003d7b18 = 0x40b00000;
  g_unk_003d7b1c = 0x40a00000;
  g_unk_003d7b20 = 0x41000000;
  g_unk_003d7b24 = 0x41300000;
  g_unk_003d7b28 = 0x41200000;
  g_unk_003d7b2c = 0x41800000;
  Q_strncpyz(&g_unk_003d7b70,"RIGHT LEG",0x20);
  g_unk_003d7c28 = 5;
  g_unk_003d7c34 = 0xf;
  g_unk_003d7c38 = 0x10;
  g_unk_003d7c3c = 0xc0b00000;
  g_unk_003d7c40 = 0xc0a00000;
  g_unk_003d7c44 = 0xc1000000;
  g_unk_003d7c48 = 0x40b00000;
  g_unk_003d7c4c = 0x40a00000;
  g_unk_003d7c50 = 0x41000000;
  g_unk_003d7c54 = 0x41300000;
  g_unk_003d7c58 = 0x41200000;
  g_unk_003d7c5c = 0x41800000;
  Q_strncpyz(&g_unk_003d7ca0,"LEFT LEG",0x20);
  g_unk_003d7b90 = 6;
  g_unk_003d7b9c = 0xe;
  g_unk_003d7ba4 = 0xc0f00000;
  g_unk_003d7ba8 = 0xc0200000;
  g_unk_003d7bac = 0xc0400000;
  g_unk_003d7bb0 = 0x40f00000;
  g_unk_003d7bb4 = 0x40200000;
  g_unk_003d7bb8 = 0x40400000;
  g_unk_003d7bbc = 0x41700000;
  g_unk_003d7bc0 = 0x40a00000;
  g_unk_003d7bc4 = 0x40c00000;
  g_unk_003d7bdc = 0x3fa66666;
  g_unk_003d7be0 = 0xc0000000;
  Q_strncpyz(&g_unk_003d7c08,"RIGHT FOOT",0x20);
  g_unk_003d7cc0 = 5;
  g_unk_003d7ccc = 0x10;
  g_unk_003d7cd4 = 0xc0f00000;
  g_unk_003d7cd8 = 0xc0200000;
  g_unk_003d7cdc = 0xc0400000;
  g_unk_003d7ce0 = 0x40f00000;
  g_unk_003d7ce4 = 0x40200000;
  g_unk_003d7ce8 = 0x40400000;
  g_unk_003d7cec = 0x41700000;
  g_unk_003d7cf0 = 0x40a00000;
  g_unk_003d7cf4 = 0x40c00000;
  g_unk_003d7d0c = 0x3fa66666;
  g_unk_003d7d10 = 0xc0000000;
  Q_strncpyz(&g_unk_003d7d38,"LEFT FOOT",0x20);
  return;
}

void mdx_cleanup(void)
{
  void *pvVar1;
  void *pvVar2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  
  mdx_bones_max = 0;
  free(mdx_bones);
  tmp_i3 = mdm_model_count;
  pvVar2 = mdm_models;
  mdx_bones = (void *)0x0;
  tmp_pu4 = (uint32_t *)((int)mdm_models + 0x44);
  if (0 < mdm_model_count) {
    tmp_i5 = 0;
    do {
      pvVar1 = (void *)*tmp_pu4;
      tmp_i5 = tmp_i5 + 1;
      tmp_pu4 = tmp_pu4 + 0x2f;
      free(pvVar1);
    } while (tmp_i5 != tmp_i3);
  }
  mdm_model_count = 0;
  free(pvVar2);
  tmp_i3 = mdx_model_count;
  pvVar2 = mdx_models;
  mdm_models = (void *)0x0;
  tmp_i5 = 0;
  tmp_pu4 = (uint32_t *)((int)mdx_models + 0x44);
  if (0 < mdx_model_count) {
    do {
      tmp_i5 = tmp_i5 + 1;
      free((void *)*tmp_pu4);
      free((void *)tmp_pu4[2]);
      tmp_pu4 = tmp_pu4 + 0x15;
    } while (tmp_i5 != tmp_i3);
  }
  mdx_model_count = 0;
  free(pvVar2);
  tmp_i3 = hit_count;
  pvVar2 = hits;
  mdx_models = (void *)0x0;
  tmp_pu4 = (uint32_t *)((int)hits + 8);
  if (0 < hit_count) {
    tmp_i5 = 0;
    do {
      pvVar1 = (void *)*tmp_pu4;
      tmp_i5 = tmp_i5 + 1;
      tmp_pu4 = tmp_pu4 + 3;
      free(pvVar1);
    } while (tmp_i5 != tmp_i3);
  }
  hit_count = 0;
  free(pvVar2);
  hits = (void *)0x0;
  return;
}

void mdx_gentity_to_grefEntity(int param_1,uint32_t *param_2,int param_3)
{
  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  uint tmp_u6;
  bool tmp_b7;
  long double tmp_l8;
  int local_8c;
  float local_88;
  float local_70;
  float local_6c;
  float local_68;
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
  float local_30;
  float local_2c;
  
  tmp_u6 = 0xb0;
  tmp_b7 = ((uint)param_2 & 1) != 0;
  tmp_pu5 = param_2;
  if (tmp_b7) {
    tmp_u6 = 0xaf;
    *(uint8_t *)param_2 = 0;
    tmp_pu5 = (uint32_t *)((int)param_2 + 1);
  }
  if (((uint)tmp_pu5 & 2) != 0) {
    *(uint16_t *)tmp_pu5 = 0;
    tmp_u6 = tmp_u6 - 2;
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
  }
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)tmp_pu5 + tmp_u2) = 0;
    *(uint32_t *)((int)tmp_pu5 + tmp_u2 + 4) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < (tmp_u6 & 0xfffffff8));
  tmp_pu5 = (uint32_t *)((int)tmp_pu5 + tmp_u2);
  if ((tmp_u6 & 4) != 0) {
    *tmp_pu5 = 0;
    tmp_pu5 = tmp_pu5 + 1;
  }
  if ((tmp_u6 & 2) != 0) {
    *(uint16_t *)tmp_pu5 = 0;
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
  }
  if (tmp_b7) {
    *(uint8_t *)tmp_pu5 = 0;
  }
  if (*(int *)(param_1 + 4) == 1) {
    tmp_i3 = BG_GetCharacter(*(uint32_t *)(*(int *)(param_1 + 400) + 3000),
                            *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc8));
  }
  else {
    tmp_i3 = BG_GetCharacter(*(uint32_t *)(param_1 + 0xa4),*(uint32_t *)(param_1 + 0xa8));
  }
  *param_2 = *(uint32_t *)(tmp_i3 + 0x40);
  param_2[0x1c] = *(uint32_t *)(param_1 + 0x168);
  param_2[0x1d] = *(uint32_t *)(param_1 + 0x16c);
  param_2[0x1e] = *(uint32_t *)(param_1 + 0x170);
  param_2[0x1f] = *(uint32_t *)(param_1 + 0x528);
  param_2[0x20] = *(uint32_t *)(param_1 + 0x50c);
  param_2[0x26] = *(uint32_t *)(param_1 + 0x510);
  param_2[0x27] = *(uint32_t *)(param_1 + 0x508);
  tmp_i3 = *(int *)(param_1 + 0x514);
  if (*(int *)(param_1 + 0x52c) == tmp_i3) {
    tmp_f1 = 0.0;
  }
  else {
    tmp_f1 = 1.0 - (float)(param_3 - tmp_i3) / (float)(*(int *)(param_1 + 0x52c) - tmp_i3);
  }
  param_2[0x2a] = tmp_f1;
  param_2[0x21] = *(uint32_t *)(param_1 + 0x578);
  param_2[0x22] = *(uint32_t *)(param_1 + 0x55c);
  param_2[0x28] = *(uint32_t *)(param_1 + 0x560);
  param_2[0x29] = *(uint32_t *)(param_1 + 0x558);
  tmp_i3 = *(int *)(param_1 + 0x564);
  if (*(int *)(param_1 + 0x57c) == tmp_i3) {
    tmp_f1 = 0.0;
  }
  else {
    tmp_f1 = 1.0 - (float)(param_3 - tmp_i3) / (float)(*(int *)(param_1 + 0x57c) - tmp_i3);
  }
  param_2[0x2b] = tmp_f1;
  tmp_i3 = *(int *)(param_1 + 400);
  if (*(int *)(param_1 + 4) == 1) {
    local_8c = BG_GetCharacterForPlayerstate(tmp_i3);
  }
  else {
    local_8c = BG_GetCharacter(*(uint32_t *)(param_1 + 0xa4),*(uint32_t *)(param_1 + 0xa8));
  }
  if (local_8c == 0) goto LAB_00047e1c;
  if (*(int *)(param_1 + 4) == 0x26) {
    local_6c = *(float *)(param_1 + 0x78);
    local_68 = 0.0;
    local_70 = 0.0;
    local_5c = 0.0;
    local_64 = 0.0;
    local_50 = 0.0;
    local_58 = 0;
    local_60 = local_6c;
    local_54 = local_6c;
    goto LAB_00047e1c;
  }
  tmp_u6 = *(uint *)(tmp_i3 + 0x58);
  tmp_i4 = *(int *)(tmp_i3 + 100);
  if (tmp_i4 < 0x81) {
    local_88 = (float)tmp_i4;
  }
  else {
    local_88 = (float)tmp_i4 - 256.0;
  }
  local_58 = *(uint32_t *)(tmp_i3 + 0xb0);
  local_54 = *(float *)(tmp_i3 + 0xb4);
  local_50 = *(float *)(tmp_i3 + 0xb8);
  tmp_l8 = (long double)AngleMod(local_54);
  local_68 = 0.0;
  local_6c = 0.0;
  local_70 = 0.0;
  local_54 = (float)tmp_l8;
  local_5c = 0.0;
  local_60 = 0.0;
  local_64 = 0.0;
  tmp_i4 = BG_GetConditionBitFlag(*(uint32_t *)(param_1 + 0xac),5,1);
  if ((tmp_i4 == 0) &&
     (tmp_i4 = BG_GetConditionBitFlag(*(uint32_t *)(param_1 + 0xac),5,2), tmp_i4 == 0)) {
    *(uint32_t *)(param_1 + 0x584) = 1;
    *(uint32_t *)(param_1 + 0x58c) = 1;
    *(uint32_t *)(param_1 + 0x534) = 1;
LAB_00047d3c:
    tmp_u2 = *(uint *)(tmp_i3 + 0x68);
    if ((tmp_u2 & 0x8001) != 0) goto LAB_00047d4e;
LAB_00047ed0:
    local_6c = local_88 + local_54;
    local_60 = local_54;
    if ((tmp_u2 & 0x80) == 0) {
      local_60 = local_88 * 0.35 + local_54;
    }
    tmp_i4 = BG_GetConditionBitFlag(*(uint32_t *)(param_1 + 0xac),5,1);
    if (tmp_i4 == 0) {
      BG_GetAnimString(*(uint32_t *)(local_8c + 0x7f0),tmp_u6 & 0xfffffdff);
    }
    local_60 = *(float *)(param_1 + 0x580);
    tmp_u6 = *(uint *)(tmp_i3 + 0x68);
    local_6c = *(float *)(param_1 + 0x530);
    if ((tmp_u6 & 1) == 0) goto LAB_00047f3d;
LAB_00047d61:
    local_58 = 0;
    if ((tmp_u6 & 0x80000) == 0) {
      local_64 = 0.0;
    }
    else {
LAB_00048000:
      local_64 = local_70 - 3.0;
    }
  }
  else {
    tmp_i4 = BG_GetConditionValue(*(uint32_t *)(param_1 + 0xac),0xb,1);
    if (tmp_i4 == 0) goto LAB_00047d3c;
    *(uint32_t *)(param_1 + 0x584) = 1;
    *(uint32_t *)(param_1 + 0x58c) = 1;
    tmp_u2 = *(uint *)(tmp_i3 + 0x68);
    if ((tmp_u2 & 0x8001) == 0) goto LAB_00047ed0;
LAB_00047d4e:
    tmp_u6 = *(uint *)(tmp_i3 + 0x68);
    local_6c = local_54;
    local_60 = local_54;
    if ((tmp_u6 & 1) != 0) goto LAB_00047d61;
LAB_00047f3d:
    if ((tmp_u6 & 0x80000) != 0) goto LAB_00048000;
    local_64 = *(float *)(param_1 + 0x588);
  }
  local_4c = *(float *)(tmp_i3 + 0x20);
  local_48 = *(float *)(tmp_i3 + 0x24);
  local_44 = *(float *)(tmp_i3 + 0x28);
  tmp_l8 = (long double)VectorNormalize(&local_4c);
  if (tmp_l8 != (long double)0) {
    AnglesToAxis(&local_70,&local_40);
    local_68 = local_68 -
               (local_44 * local_2c + local_48 * local_30 + local_4c * local_34) *
               (float)((long double)0.05 * tmp_l8);
    local_70 = (local_44 * local_38 + local_48 * local_3c + local_4c * local_40) *
               (float)((long double)0.05 * tmp_l8) + local_70;
  }
  if ((g_weapons[0xd] & 1) == 0) {
    if ((g_misc[0xc] & 0x20) != 0) {
      tmp_f1 = *(float *)(*(int *)(param_1 + 400) + 0x3c);
      local_5c = tmp_f1 * 1.25 + local_5c;
      local_50 = tmp_f1 + local_50;
    }
  }
  else {
    tmp_f1 = *(float *)(*(int *)(param_1 + 400) + 0x3c);
    local_5c = tmp_f1 * 2.2 + local_5c;
    local_50 = tmp_f1 + local_50;
  }
  AnglesSubtract(&local_58,&local_64,&local_58);
  AnglesSubtract(&local_64,&local_70,&local_64);
LAB_00047e1c:
  AnglesToAxis(&local_70,param_2 + 10);
  AnglesToAxis(&local_64,param_2 + 0x13);
  AnglesToAxis(&local_58,param_2 + 1);
  return;
}

void mdx_calculate_bones_single(int param_1,int param_2)
{
  float *pfVar1;
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
  int tmp_i12;
  int tmp_i13;
  float tmp_f14;
  float tmp_f15;
  int tmp_i16;
  float *pfVar17;
  int tmp_i18;
  int tmp_i19;
  int tmp_i20;
  int tmp_i21;
  int tmp_i22;
  int local_38;
  int local_34;
  
  pfVar17 = mdx_bones;
  if (*(int *)(param_1 + 0x80) < 1) {
    tmp_i18 = *(int *)(param_1 + 0x9c);
    tmp_i19 = mdx_models;
  }
  else {
    tmp_i18 = *(int *)(param_1 + 0x9c);
    tmp_i19 = mdx_models + (*(int *)(param_1 + 0x80) + -1) * 0x54;
  }
  local_38 = tmp_i19;
  if (0 < tmp_i18) {
    local_38 = mdx_models + (tmp_i18 + -1) * 0x54;
  }
  if (*(int *)(param_1 + 0x88) < 1) {
    tmp_i12 = *(int *)(param_1 + 0xa4);
    tmp_i18 = mdx_models;
  }
  else {
    tmp_i18 = mdx_models + (*(int *)(param_1 + 0x88) + -1) * 0x54;
    tmp_i12 = *(int *)(param_1 + 0xa4);
  }
  local_34 = tmp_i18;
  if (0 < tmp_i12) {
    local_34 = mdx_models + (tmp_i12 + -1) * 0x54;
  }
  tmp_i12 = param_2 * 0x4c;
  tmp_i22 = *(int *)(tmp_i19 + 0x44) + tmp_i12;
  if (*(float *)(tmp_i22 + 0x48) == 0.0) {
    tmp_i20 = *(int *)(param_1 + 0x7c);
    tmp_f2 = *(float *)(param_1 + 0xa8);
    tmp_i21 = *(int *)(param_1 + 0x98);
    tmp_i13 = *(int *)(local_38 + 0x44);
    tmp_i16 = local_38;
  }
  else {
    tmp_i20 = *(int *)(param_1 + 0x84);
    tmp_f2 = *(float *)(param_1 + 0xac);
    tmp_i21 = *(int *)(param_1 + 0xa0);
    tmp_i22 = tmp_i12 + *(int *)(tmp_i18 + 0x44);
    tmp_i13 = *(int *)(local_34 + 0x44);
    tmp_i19 = tmp_i18;
    tmp_i16 = local_34;
  }
  if (param_2 == 0) {
    tmp_f3 = 1.0 - tmp_f2;
    tmp_i20 = tmp_i20 * 0x14;
    tmp_f5 = tmp_f3 * *(float *)(*(int *)(tmp_i19 + 0x4c) + 4 + tmp_i20) + vec3_origin;
    *mdx_bones = tmp_f5;
    tmp_f4 = tmp_f3 * *(float *)(*(int *)(tmp_i19 + 0x4c) + 8 + tmp_i20) + g_unk_008277c4;
    pfVar17[1] = tmp_f4;
    tmp_f3 = tmp_f3 * *(float *)(*(int *)(tmp_i19 + 0x4c) + 0xc + tmp_i20) + g_unk_008277c8;
    tmp_i21 = tmp_i21 * 0x14;
    pfVar17[2] = tmp_f3;
    *pfVar17 = *(float *)(*(int *)(tmp_i16 + 0x4c) + 4 + tmp_i21) * tmp_f2 + tmp_f5;
    pfVar17[1] = *(float *)(*(int *)(tmp_i16 + 0x4c) + 8 + tmp_i21) * tmp_f2 + tmp_f4;
    pfVar17[2] = tmp_f2 * *(float *)(*(int *)(tmp_i16 + 0x4c) + 0xc + tmp_i21) + tmp_f3;
    return;
  }
  mdx_calculate_bone_lerp_constprop_6(local_38,tmp_i18,local_34,*(uint32_t *)(tmp_i22 + 0x40));
  pfVar17 = mdx_bones;
  tmp_i20 = *(int *)(tmp_i20 * 0x14 + *(int *)(tmp_i19 + 0x4c) + 0x10) + param_2 * 10;
  tmp_i18 = param_2 * 10 + *(int *)(*(int *)(tmp_i16 + 0x4c) + tmp_i21 * 0x14 + 0x10);
  tmp_f3 = *(float *)(tmp_i13 + 0x44 + tmp_i12);
  tmp_i19 = (int)*(short *)(tmp_i18 + 6) >> 4;
  if (tmp_i19 < 0) {
    tmp_i19 = tmp_i19 + 0x1000;
  }
  tmp_f4 = *(float *)(sintable + tmp_i19 * 4);
  tmp_f5 = *(float *)(sintable + ((tmp_i19 + 0x400) % 0x1000) * 4);
  tmp_i19 = (int)*(short *)(tmp_i18 + 8) >> 4;
  if (tmp_i19 < 0) {
    tmp_i19 = tmp_i19 + 0x1000;
  }
  tmp_f6 = *(float *)(sintable + tmp_i19 * 4);
  tmp_f7 = *(float *)(sintable + ((tmp_i19 + 0x400) % 0x1000) * 4);
  tmp_i19 = (int)*(short *)(tmp_i20 + 6) >> 4;
  if (tmp_i19 < 0) {
    tmp_i19 = tmp_i19 + 0x1000;
  }
  tmp_f8 = *(float *)(sintable + tmp_i19 * 4);
  tmp_f9 = *(float *)(sintable + ((tmp_i19 + 0x400) % 0x1000) * 4);
  tmp_i19 = (int)*(short *)(tmp_i20 + 8) >> 4;
  if (tmp_i19 < 0) {
    tmp_i19 = tmp_i19 + 0x1000;
  }
  tmp_f10 = *(float *)(sintable + tmp_i19 * 4);
  tmp_f11 = *(float *)(sintable + ((tmp_i19 + 0x400) % 0x1000) * 4);
  pfVar1 = mdx_bones + param_2 * 3;
  tmp_f14 = tmp_f8 * tmp_f11 * 0.0 + (tmp_f9 * tmp_f11 * *(float *)(tmp_i22 + 0x44) - tmp_f10 * 0.0);
  tmp_f10 = tmp_f10 * tmp_f8 * 0.0 + tmp_f11 * 0.0 + tmp_f9 * tmp_f10 * *(float *)(tmp_i22 + 0x44);
  tmp_f11 = tmp_f9 * 0.0 + (0.0 - tmp_f8 * *(float *)(tmp_i22 + 0x44));
  tmp_f15 = mdx_bones[*(int *)(tmp_i22 + 0x40) * 3] + tmp_f14;
  *pfVar1 = tmp_f15;
  tmp_f9 = pfVar17[*(int *)(tmp_i22 + 0x40) * 3 + 1] + tmp_f10;
  pfVar1[1] = tmp_f9;
  tmp_f8 = pfVar17[*(int *)(tmp_i22 + 0x40) * 3 + 2];
  *pfVar1 = ((tmp_f4 * tmp_f7 * 0.0 + (tmp_f5 * tmp_f7 * tmp_f3 - tmp_f6 * 0.0)) - tmp_f14) * tmp_f2 +
            tmp_f15;
  pfVar1[1] = tmp_f9 + ((tmp_f6 * tmp_f4 * 0.0 + tmp_f7 * 0.0 + tmp_f5 * tmp_f6 * tmp_f3) - tmp_f10) * tmp_f2
  ;
  pfVar1[2] = tmp_f8 + tmp_f11 + (((0.0 - tmp_f3 * tmp_f4) + tmp_f5 * 0.0) - tmp_f11) * tmp_f2;
  return;
}

void mdx_PlayerAngles(int param_1,float *param_2,float *param_3,float *param_4,int param_5)
{
  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  int tmp_i4;
  char *tmp_pc5;
  long double tmp_l6;
  uint32_t tmp_u7;
  uint32_t tmp_u8;
  int local_60;
  float local_58;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  
  tmp_i4 = *(int *)(param_1 + 400);
  if (*(int *)(param_1 + 4) == 1) {
    local_60 = BG_GetCharacterForPlayerstate(tmp_i4);
  }
  else {
    local_60 = BG_GetCharacter(*(uint32_t *)(param_1 + 0xa4),*(uint32_t *)(param_1 + 0xa8));
  }
  if (local_60 == 0) {
    return;
  }
  if (*(int *)(param_1 + 4) == 0x26) {
    param_2[1] = 0.0;
    param_2[2] = 0.0;
    *param_2 = 0.0;
    param_3[1] = 0.0;
    param_3[2] = 0.0;
    *param_3 = 0.0;
    param_4[1] = 0.0;
    param_4[2] = 0.0;
    *param_4 = 0.0;
    tmp_f1 = *(float *)(param_1 + 0x78);
    param_4[1] = tmp_f1;
    param_3[1] = tmp_f1;
    param_2[1] = tmp_f1;
    return;
  }
  tmp_u2 = *(uint *)(tmp_i4 + 0x58);
  tmp_i3 = *(int *)(tmp_i4 + 100);
  if (tmp_i3 < 0x81) {
    local_58 = (float)tmp_i3;
  }
  else {
    local_58 = (float)tmp_i3 - 256.0;
  }
  *param_4 = *(float *)(tmp_i4 + 0xb0);
  tmp_f1 = *(float *)(tmp_i4 + 0xb4);
  param_4[1] = tmp_f1;
  param_4[2] = *(float *)(tmp_i4 + 0xb8);
  tmp_l6 = (long double)AngleMod(tmp_f1);
  param_4[1] = (float)tmp_l6;
  param_2[2] = 0.0;
  param_2[1] = 0.0;
  *param_2 = 0.0;
  param_3[2] = 0.0;
  param_3[1] = 0.0;
  *param_3 = 0.0;
  tmp_i3 = BG_GetConditionBitFlag(*(uint32_t *)(param_1 + 0xac),5,1);
  if ((tmp_i3 == 0) &&
     (tmp_i3 = BG_GetConditionBitFlag(*(uint32_t *)(param_1 + 0xac),5,2), tmp_i3 == 0)) {
    *(uint32_t *)(param_1 + 0x584) = 1;
    *(uint32_t *)(param_1 + 0x58c) = 1;
    *(uint32_t *)(param_1 + 0x534) = 1;
  }
  else {
    tmp_i3 = BG_GetConditionValue(*(uint32_t *)(param_1 + 0xac),0xb,1);
    if (tmp_i3 != 0) {
      *(uint32_t *)(param_1 + 0x584) = 1;
      *(uint32_t *)(param_1 + 0x58c) = 1;
    }
  }
  if ((*(uint *)(tmp_i4 + 0x68) & 0x8001) == 0) {
    param_2[1] = local_58 + param_4[1];
    if ((*(byte *)(tmp_i4 + 0x68) & 0x80) == 0) {
      tmp_f1 = local_58 * 0.35 + param_4[1];
      tmp_u7 = 0x42b40000;
    }
    else {
      tmp_f1 = param_4[1];
      tmp_u7 = 0x42700000;
    }
    param_3[1] = tmp_f1;
    if (param_5 == 0) {
      tmp_i3 = BG_GetConditionBitFlag(*(uint32_t *)(param_1 + 0xac),5,1);
      if (tmp_i3 == 0) {
        tmp_pc5 = (char *)BG_GetAnimString(*(uint32_t *)(local_60 + 0x7f0),tmp_u2 & 0xfffffdff);
        tmp_pc5 = strstr(tmp_pc5,"strafe");
        if (tmp_pc5 == (char *)0x0) {
LAB_00049f51:
          if (*(int *)(param_1 + 0x534) == 0) {
            if (param_5 != 0) {
              tmp_u8 = 0x3dcccccd;
              tmp_u7 = 0x42200000;
              goto LAB_00049eea;
            }
          }
          else if (param_5 != 0) {
            tmp_u8 = 0x3dcccccd;
            tmp_u7 = 0;
LAB_00049eea:
            mdx_SwingAngles(param_2[1],tmp_u7,0x43160000,tmp_u8);
          }
        }
      }
    }
    else {
      mdx_SwingAngles(tmp_f1,0x41c80000,tmp_u7,0x3dcccccd);
      tmp_i3 = BG_GetConditionBitFlag(*(uint32_t *)(param_1 + 0xac),5,1);
      if (tmp_i3 != 0) {
        *(uint32_t *)(param_1 + 0x534) = 0;
        tmp_u8 = 0x3d4ccccd;
        tmp_u7 = 0x41a00000;
        goto LAB_00049eea;
      }
      tmp_pc5 = (char *)BG_GetAnimString(*(uint32_t *)(local_60 + 0x7f0),tmp_u2 & 0xfffffdff);
      tmp_pc5 = strstr(tmp_pc5,"strafe");
      if (tmp_pc5 == (char *)0x0) goto LAB_00049f51;
      *(uint32_t *)(param_1 + 0x534) = 0;
      tmp_f1 = param_4[1];
      param_2[1] = tmp_f1;
      mdx_SwingAngles(tmp_f1,0,0x43160000,0x3dcccccd);
    }
    param_3[1] = *(float *)(param_1 + 0x580);
    param_2[1] = *(float *)(param_1 + 0x530);
  }
  else {
    param_2[1] = param_4[1];
    param_3[1] = param_4[1];
  }
  tmp_f1 = *param_4;
  if (180.0 < tmp_f1) {
    tmp_f1 = tmp_f1 - 360.0;
  }
  if ((*(uint *)(tmp_i4 + 0x68) & 1) == 0) {
    if ((*(uint *)(tmp_i4 + 0x68) & 0x80000) != 0) goto LAB_00049b3a;
LAB_00049c10:
    if (param_5 != 0) {
      mdx_SwingAngles(tmp_f1 * 0.75,0x41700000,0x41f00000,0x3dcccccd);
    }
    *param_3 = *(float *)(param_1 + 0x588);
  }
  else {
    *param_4 = 0.0;
    if ((*(uint *)(tmp_i4 + 0x68) & 0x80000) == 0) {
      if ((*(uint *)(tmp_i4 + 0x68) & 1) == 0) goto LAB_00049c10;
      *param_3 = 0.0;
    }
    else {
LAB_00049b3a:
      *param_3 = *param_2 - 3.0;
    }
  }
  local_4c = *(float *)(tmp_i4 + 0x20);
  local_48 = *(float *)(tmp_i4 + 0x24);
  local_44 = *(float *)(tmp_i4 + 0x28);
  tmp_l6 = (long double)VectorNormalize(&local_4c);
  if (tmp_l6 != (long double)0) {
    AnglesToAxis(param_2,&local_40);
    param_2[2] = param_2[2] -
                 (local_44 * local_2c + local_48 * local_30 + local_4c * local_34) *
                 (float)((long double)0.05 * tmp_l6);
    *param_2 = (local_44 * local_38 + local_48 * local_3c + local_4c * local_40) *
               (float)((long double)0.05 * tmp_l6) + *param_2;
  }
  if ((g_weapons[0xd] & 1) == 0) {
    if ((g_misc[0xc] & 0x20) == 0) goto LAB_00049bb7;
    tmp_i4 = *(int *)(param_1 + 400);
    tmp_f1 = 1.25;
  }
  else {
    tmp_i4 = *(int *)(param_1 + 400);
    tmp_f1 = 2.2;
  }
  param_3[2] = tmp_f1 * *(float *)(tmp_i4 + 0x3c) + param_3[2];
  param_4[2] = param_4[2] + *(float *)(*(int *)(param_1 + 400) + 0x3c);
LAB_00049bb7:
  AnglesSubtract(param_4,param_3,param_4);
  AnglesSubtract(param_3,param_2,param_3);
  return;
}

void mdx_PlayerAnimation(uint32_t *param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  float tmp_f3;
  byte tmp_b4;
  bool tmp_b5;
  bool tmp_b6;
  uint tmp_u7;
  uint32_t *tmp_pu8;
  int tmp_i9;
  int tmp_i10;
  uint tmp_u11;
  uint32_t *tmp_pu12;
  int tmp_i13;
  bool tmp_b14;
  long double tmp_l15;
  int local_7c;
  int local_74;
  uint32_t *local_70;
  uint local_6c;
  int local_68;
  uint32_t *local_64;
  int local_5c;
  uint8_t local_40 [12];
  uint8_t local_34 [12];
  uint8_t local_28 [24];
  
  if (param_1[1] == 1) {
    local_5c = BG_GetCharacter(*(uint32_t *)(param_1[100] + 3000),
                               *(uint32_t *)(param_1[100] + 0xbc8));
  }
  else {
    local_5c = BG_GetCharacter(param_1[0x29],param_1[0x2a]);
  }
  tmp_i9 = g_unk_00abe908;
  tmp_u11 = param_1[0x3b];
  if ((*(byte *)((int)param_1 + 10) & 0x80) == 0) {
    tmp_i13 = param_1[0x175];
  }
  else {
    tmp_i13 = g_unk_00abe908 + 0x6d6;
    param_1[0x175] = tmp_i13;
  }
  if ((((tmp_i13 < tmp_i9) && ((param_1[2] & 0x808001) == 0)) && (param_1[0x14d] != 0)) &&
     (tmp_u7 = BG_GetAnimScriptAnimation
                        (*param_1,*(uint32_t *)(local_5c + 0x7f0),param_1[0x46],
                         (param_1[0x14d] != 1) + '\r'), -1 < (int)tmp_u7)) {
    tmp_u11 = tmp_u7;
  }
  local_70 = (uint32_t *)param_1[0x153];
  if (local_70 == (uint32_t *)0x0) {
    param_1[0x151] = tmp_u11;
    tmp_pu8 = (uint32_t *)
             BG_GetAnimationForIndex(*(uint32_t *)(local_5c + 0x7f0),tmp_u11 & 0xfffffdff);
    tmp_i9 = param_1[0x14b];
    tmp_b5 = false;
    tmp_b14 = true;
    param_1[0x153] = tmp_pu8;
    tmp_i13 = tmp_pu8[0x15] + tmp_i9;
    param_1[0x154] = tmp_i13;
LAB_0004a1dd:
    tmp_b6 = false;
LAB_0004ada1:
    tmp_pu12 = tmp_pu8;
    if (((tmp_pu8[0x1b] & 100) != 0) == tmp_b6) {
      if (tmp_pu8[0x16] == 0) {
        local_74 = tmp_i9 + 0xaa;
LAB_0004aec2:
        if (local_70 != (uint32_t *)0x0) {
          tmp_i10 = local_70[0x17];
          goto joined_r0x0004aecf;
        }
        goto LAB_0004adf1;
      }
      local_74 = tmp_i9 + 0x78;
      if (local_70 == (uint32_t *)0x0) goto LAB_0004af20;
LAB_0004add9:
      tmp_i10 = local_70[0x17];
joined_r0x0004aecf:
      if (tmp_i10 == 0) {
        if (tmp_pu8[0x16] != 0) goto LAB_0004af20;
        goto LAB_0004adf1;
      }
      tmp_pu12 = (uint32_t *)param_1[0x153];
      param_1[0x154] = tmp_i9 + tmp_i10;
    }
    else {
      if (tmp_pu8[0x16] == 0) {
        if ((tmp_pu8[0x1b] & 0x6000) == 0) {
          local_74 = tmp_i9 + 0x15e;
        }
        else {
          local_74 = tmp_i9 + 200;
        }
        goto LAB_0004aec2;
      }
      local_74 = tmp_i9 + 200;
      if (local_70 != (uint32_t *)0x0) goto LAB_0004add9;
LAB_0004af20:
      if ((float)param_1[0x155] < 1.0) {
        tmp_i13 = tmp_i13 + tmp_pu8[0x15];
        param_1[0x154] = tmp_i13;
        tmp_pu12 = (uint32_t *)param_1[0x153];
      }
LAB_0004adf1:
      if (tmp_i13 < local_74) {
        param_1[0x154] = local_74;
      }
    }
    tmp_b6 = tmp_b5;
    if (!tmp_b14) goto LAB_0004a212;
    tmp_i13 = param_1[1];
    tmp_i9 = g_unk_00abe908 + -1;
    param_1[0x14b] = tmp_i9;
    param_1[0x154] = tmp_i9;
    param_1[0x14a] = tmp_pu8[0x11];
    tmp_u2 = *tmp_pu8;
    param_1[0x147] = param_1[6];
    param_1[0x148] = param_1[7];
    param_1[0x143] = tmp_u2;
    param_1[0x149] = param_1[8];
  }
  else {
    tmp_b14 = (local_70[0x1a] & 1) == 0;
    if (tmp_b14) {
      tmp_u7 = param_1[0x151];
    }
    else {
      tmp_u7 = param_1[0x151];
    }
    tmp_b5 = !tmp_b14;
    tmp_pu12 = local_70;
    tmp_b6 = !tmp_b14;
    if (tmp_u11 != tmp_u7) {
      param_1[0x151] = tmp_u11;
      tmp_pu8 = (uint32_t *)
               BG_GetAnimationForIndex(*(uint32_t *)(local_5c + 0x7f0),tmp_u11 & 0xfffffdff);
      tmp_i9 = param_1[0x14b];
      tmp_b14 = false;
      param_1[0x153] = tmp_pu8;
      tmp_i13 = tmp_pu8[0x15] + tmp_i9;
      param_1[0x154] = tmp_i13;
      if ((*(byte *)(local_70 + 0x1b) & 100) == 0) goto LAB_0004a1dd;
      tmp_b6 = true;
      goto LAB_0004ada1;
    }
LAB_0004a212:
    tmp_b5 = tmp_b6;
    tmp_i13 = param_1[1];
  }
  if (tmp_i13 == 0x26) {
    local_70 = (uint32_t *)param_1[0x167];
    tmp_u11 = param_1[0x3c];
    tmp_i9 = tmp_pu12[0x12] + tmp_pu12[0x11] + -1;
    param_1[0x14a] = tmp_i9;
    param_1[0x144] = tmp_i9;
    tmp_u2 = *tmp_pu12;
    param_1[0x143] = tmp_u2;
    param_1[0x142] = tmp_u2;
    if (local_70 == (uint32_t *)0x0) goto LAB_0004ae90;
LAB_0004a6fb:
    tmp_b14 = (local_70[0x1a] & 1) == 0;
    if (tmp_b14) {
      tmp_u7 = param_1[0x165];
    }
    else {
      tmp_u7 = param_1[0x165];
    }
    local_64 = (uint32_t *)(uint)!tmp_b14;
    tmp_pu8 = local_70;
    tmp_pu12 = (uint32_t *)(uint)!tmp_b14;
    if (tmp_u11 != tmp_u7) goto LAB_0004a720;
  }
  else {
    local_74 = param_1[0x14b];
    tmp_i9 = g_unk_00abe908;
    if (local_74 < g_unk_00abe908) {
      local_7c = param_1[4];
      do {
        tmp_i9 = param_1[0x146];
        if (tmp_i9 < local_7c) {
          if (tmp_b5) {
            param_1[0x147] = param_1[6];
            param_1[0x148] = param_1[7];
          }
          tmp_l15 = (long double)Distance(param_1 + 6,param_1 + 0x147);
          tmp_i9 = local_7c - tmp_i9;
          local_7c = param_1[4];
          param_1[0x150] = (int)ROUND(tmp_l15 / ((long double)tmp_i9 / (long double)1000.0));
          param_1[0x146] = local_7c;
          param_1[0x147] = param_1[6];
          param_1[0x148] = param_1[7];
          param_1[0x149] = param_1[8];
        }
        if (tmp_pu12[0x16] == 0) {
          param_1[0x155] = 0x3f800000;
          tmp_f3 = 1.0;
LAB_0004a410:
          tmp_i13 = param_1[0x14a];
          local_74 = param_1[0x14b];
          param_1[0x142] = param_1[0x143];
          tmp_i9 = param_1[0x167];
          param_1[0x144] = tmp_i13;
          param_1[0x145] = local_74;
          if (tmp_f3 != 0.0) goto LAB_0004a450;
LAB_0004a2c2:
          tmp_i9 = tmp_pu12[0x11];
          tmp_b4 = 1;
          local_74 = local_74 + tmp_pu12[0x14];
          local_6c = param_1[0x151];
          param_1[0x14b] = local_74;
          tmp_i13 = tmp_i13 - tmp_i9;
          tmp_i10 = tmp_pu12[0x12];
LAB_0004a2e8:
          if (tmp_i13 < tmp_i10) {
            tmp_b14 = (bool)(local_74 < g_unk_00abe908 & tmp_b4);
            tmp_i9 = g_unk_00abe908;
          }
          else {
LAB_0004a560:
            tmp_i9 = g_unk_00abe908;
            tmp_i1 = tmp_pu12[0x13];
            if (tmp_i1 == 0) {
              tmp_i13 = tmp_i10 + -1;
              tmp_b14 = false;
              local_74 = g_unk_00abe908;
              param_1[0x14b] = g_unk_00abe908;
            }
            else {
              tmp_i13 = (tmp_i13 - tmp_i10) % tmp_i1 + (tmp_i10 - tmp_i1);
              tmp_b14 = (bool)(local_74 < g_unk_00abe908 & tmp_b4);
            }
          }
          local_68 = tmp_pu12[0x11];
          if ((*(byte *)(tmp_pu12 + 0x1a) & 4) == 0) goto LAB_0004a530;
          tmp_i10 = tmp_pu12[0x12];
LAB_0004a31a:
          param_1[0x14a] = (tmp_i10 + -1 + local_68) - tmp_i13;
          param_1[0x143] = *tmp_pu12;
        }
        else {
          tmp_f3 = (float)(int)param_1[0x150] / (float)(int)tmp_pu12[0x16];
          if (tmp_f3 < 0.25) {
            if ((!tmp_b5) || (0.01 <= tmp_f3)) {
              param_1[0x155] = 0x3e800000;
              tmp_f3 = 0.25;
              goto LAB_0004a612;
            }
            tmp_i13 = param_1[0x14a];
            local_74 = param_1[0x14b];
            param_1[0x155] = 0;
            param_1[0x144] = tmp_i13;
            param_1[0x145] = local_74;
            param_1[0x142] = param_1[0x143];
            goto LAB_0004a2c2;
          }
          param_1[0x155] = tmp_f3;
          if (tmp_f3 <= 1.1) goto LAB_0004a410;
          if ((*(byte *)(tmp_pu12 + 0x1a) & 1) == 0) {
            tmp_i9 = tmp_pu12[0x16];
            if (tmp_i9 < 0x65) {
              if (tmp_i9 < 0x14) {
                if (1.6 < tmp_f3) {
                  param_1[0x155] = 0x3fcccccd;
                  tmp_f3 = 1.6;
                  goto LAB_0004a612;
                }
              }
              else {
                tmp_f3 = 1.6 - ((float)(tmp_i9 + -0x14) * 0.5) / 80.0;
                param_1[0x155] = tmp_f3;
              }
              goto LAB_0004a410;
            }
            param_1[0x155] = 0x3f8ccccd;
            tmp_f3 = 1.1;
          }
          else {
            if (tmp_f3 <= 4.0) goto LAB_0004a410;
            param_1[0x155] = 0x40800000;
            tmp_f3 = 4.0;
          }
LAB_0004a612:
          tmp_i13 = param_1[0x14a];
          local_74 = param_1[0x14b];
          param_1[0x142] = param_1[0x143];
          tmp_i9 = param_1[0x167];
          param_1[0x144] = tmp_i13;
          param_1[0x145] = local_74;
LAB_0004a450:
          local_6c = param_1[0x151];
          if ((param_1[0x152] != local_6c) &&
             (((tmp_pu12[0x16] == 0 || (tmp_i13 < (int)tmp_pu12[0x11])) ||
              ((int)(tmp_pu12[0x11] + tmp_pu12[0x12]) <= tmp_i13)))) {
            local_74 = param_1[0x154];
            param_1[0x14b] = local_74;
            if ((local_70 == (uint32_t *)0x0) || (tmp_pu12[0x16] == 0)) {
              tmp_i10 = tmp_pu12[0x12];
              tmp_i13 = 0;
              tmp_b4 = 1;
            }
            else {
              tmp_i10 = tmp_pu12[0x12];
              for (tmp_i13 = (tmp_i13 - local_70[0x11]) + 1; tmp_i13 < 0; tmp_i13 = tmp_i13 + tmp_i10) {
              }
              tmp_b4 = 1;
            }
            goto LAB_0004a2e8;
          }
          if ((((tmp_i9 != 0) && ((*(byte *)(tmp_pu12 + 0x1a) & 2) == 0)) &&
              (((local_6c ^ param_1[0x165]) & 0xfffffdff) == 0)) && (tmp_pu12[0x16] == 0)) {
            tmp_i13 = param_1[0x15e] - *(int *)(tmp_i9 + 0x44);
            if (((int)tmp_pu12[0x12] <= tmp_i13) || (tmp_i13 < 0)) {
              tmp_i13 = 0;
            }
            local_74 = param_1[0x15f];
            tmp_b4 = 0;
            param_1[0x14b] = local_74;
            tmp_i10 = tmp_pu12[0x12];
            goto LAB_0004a2e8;
          }
          local_74 = local_74 + (int)ROUND((float)(int)tmp_pu12[0x14] * (1.0 / tmp_f3));
          param_1[0x14b] = local_74;
          tmp_i9 = g_unk_00abe908;
          if ((*(byte *)(tmp_pu12 + 0x1a) & 4) != 0) {
            local_68 = tmp_pu12[0x11];
            tmp_i10 = tmp_pu12[0x12];
            tmp_i13 = (local_68 - tmp_i13) + tmp_i10;
            if (tmp_i10 <= tmp_i13) goto LAB_0004a550;
            tmp_b14 = local_74 < g_unk_00abe908;
            goto LAB_0004a31a;
          }
          local_68 = tmp_pu12[0x11];
          tmp_i10 = tmp_pu12[0x12];
          tmp_i13 = (tmp_i13 - local_68) + 1;
          if (tmp_i10 <= tmp_i13) {
LAB_0004a550:
            tmp_b4 = 1;
            goto LAB_0004a560;
          }
          tmp_b14 = local_74 < g_unk_00abe908;
LAB_0004a530:
          param_1[0x14a] = tmp_i13 + local_68;
          param_1[0x143] = *tmp_pu12;
        }
        param_1[0x152] = local_6c;
        local_70 = tmp_pu12;
      } while (tmp_b14);
    }
    if (tmp_i9 + 5000 < local_74) {
      param_1[0x14b] = tmp_i9;
    }
    local_70 = (uint32_t *)param_1[0x167];
    tmp_u11 = param_1[0x3c];
    if (local_70 != (uint32_t *)0x0) goto LAB_0004a6fb;
LAB_0004ae90:
    local_64 = (uint32_t *)0x0;
    tmp_pu12 = local_64;
    if (tmp_u11 == param_1[0x165]) {
      tmp_b14 = true;
      local_64 = local_70;
    }
    else {
LAB_0004a720:
      local_64 = tmp_pu12;
      tmp_b14 = local_70 == (uint32_t *)0x0;
    }
    param_1[0x165] = tmp_u11;
    tmp_pu8 = (uint32_t *)
             BG_GetAnimationForIndex(*(uint32_t *)(local_5c + 0x7f0),tmp_u11 & 0xfffffdff);
    tmp_i9 = param_1[0x15f];
    param_1[0x167] = tmp_pu8;
    tmp_i13 = tmp_pu8[0x15] + tmp_i9;
    param_1[0x168] = tmp_i13;
    if ((*(byte *)(tmp_pu8 + 0x1a) & 2) == 0) {
      if (tmp_pu8[0x16] == 0) {
        local_74 = tmp_i9 + 0xaa;
        if ((local_70 == (uint32_t *)0x0) || (tmp_i10 = local_70[0x17], tmp_i10 == 0))
        goto LAB_0004ad79;
      }
      else {
        local_74 = tmp_i9 + 0x78;
        if ((local_70 == (uint32_t *)0x0) || (tmp_i10 = local_70[0x17], tmp_i10 == 0)) {
          if ((float)param_1[0x169] < 1.0) {
            tmp_i13 = tmp_i13 + tmp_pu8[0x15];
            param_1[0x168] = tmp_i13;
          }
LAB_0004ad79:
          if (tmp_i13 < local_74) {
            param_1[0x168] = local_74;
          }
          goto LAB_0004a797;
        }
      }
      param_1[0x168] = tmp_i9 + tmp_i10;
    }
LAB_0004a797:
    if (tmp_b14) {
      tmp_i9 = g_unk_00abe908 + -1;
      param_1[0x15f] = tmp_i9;
      param_1[0x168] = tmp_i9;
      tmp_i9 = param_1[1];
      param_1[0x15e] = tmp_pu8[0x11];
      tmp_u2 = *tmp_pu8;
      param_1[0x15b] = param_1[6];
      param_1[0x15c] = param_1[7];
      param_1[0x157] = tmp_u2;
      param_1[0x15d] = param_1[8];
      goto joined_r0x0004a7ed;
    }
  }
  tmp_i9 = param_1[1];
joined_r0x0004a7ed:
  if (tmp_i9 == 0x26) {
    tmp_i9 = tmp_pu8[0x12] + tmp_pu8[0x11] + -1;
    param_1[0x15e] = tmp_i9;
    param_1[0x158] = tmp_i9;
    tmp_u2 = *tmp_pu8;
    param_1[0x157] = tmp_u2;
    param_1[0x156] = tmp_u2;
  }
  else {
    local_74 = param_1[0x15f];
    tmp_i9 = g_unk_00abe908;
    if (local_74 < g_unk_00abe908) {
      local_7c = param_1[4];
      do {
        tmp_i9 = param_1[0x15a];
        if (tmp_i9 < local_7c) {
          if (local_64 != (uint32_t *)0x0) {
            param_1[0x15b] = param_1[6];
            param_1[0x15c] = param_1[7];
          }
          tmp_l15 = (long double)Distance(param_1 + 6,param_1 + 0x15b);
          tmp_i9 = local_7c - tmp_i9;
          local_7c = param_1[4];
          param_1[0x164] = (int)ROUND(tmp_l15 / ((long double)tmp_i9 / (long double)1000.0));
          param_1[0x15a] = local_7c;
          param_1[0x15b] = param_1[6];
          param_1[0x15c] = param_1[7];
          param_1[0x15d] = param_1[8];
        }
        if (tmp_pu8[0x16] == 0) {
          param_1[0x169] = 0x3f800000;
          tmp_f3 = 1.0;
LAB_0004aa30:
          tmp_i13 = param_1[0x15e];
          local_74 = param_1[0x15f];
          param_1[0x156] = param_1[0x157];
          tmp_i9 = param_1[0x153];
          param_1[0x158] = tmp_i13;
          param_1[0x159] = local_74;
          if (tmp_f3 != 0.0) goto LAB_0004aa70;
LAB_0004a8da:
          tmp_i9 = tmp_pu8[0x11];
          tmp_b4 = 1;
          local_74 = local_74 + tmp_pu8[0x14];
          local_6c = param_1[0x165];
          param_1[0x15f] = local_74;
          tmp_i13 = tmp_i13 - tmp_i9;
          tmp_i10 = tmp_pu8[0x12];
LAB_0004a900:
          if (tmp_i13 < tmp_i10) {
            tmp_b14 = (bool)(local_74 < g_unk_00abe908 & tmp_b4);
            tmp_i9 = g_unk_00abe908;
          }
          else {
LAB_0004abe0:
            tmp_i9 = g_unk_00abe908;
            tmp_i1 = tmp_pu8[0x13];
            if (tmp_i1 == 0) {
              tmp_i13 = tmp_i10 + -1;
              tmp_b14 = false;
              local_74 = g_unk_00abe908;
              param_1[0x15f] = g_unk_00abe908;
            }
            else {
              tmp_i13 = (tmp_i13 - tmp_i10) % tmp_i1 + (tmp_i10 - tmp_i1);
              tmp_b14 = (bool)(local_74 < g_unk_00abe908 & tmp_b4);
            }
          }
          local_68 = tmp_pu8[0x11];
          if ((*(byte *)(tmp_pu8 + 0x1a) & 4) == 0) goto LAB_0004abb0;
          tmp_i10 = tmp_pu8[0x12];
LAB_0004a932:
          param_1[0x15e] = (tmp_i10 + -1 + local_68) - tmp_i13;
          param_1[0x157] = *tmp_pu8;
        }
        else {
          tmp_f3 = (float)(int)param_1[0x164] / (float)(int)tmp_pu8[0x16];
          if (tmp_f3 < 0.25) {
            if ((((uint)local_64 & 1) == 0) || (0.01 <= tmp_f3)) {
              param_1[0x169] = 0x3e800000;
              tmp_f3 = 0.25;
              goto LAB_0004ac22;
            }
            tmp_i13 = param_1[0x15e];
            local_74 = param_1[0x15f];
            param_1[0x169] = 0;
            param_1[0x158] = tmp_i13;
            param_1[0x159] = local_74;
            param_1[0x156] = param_1[0x157];
            goto LAB_0004a8da;
          }
          param_1[0x169] = tmp_f3;
          if (tmp_f3 <= 1.1) goto LAB_0004aa30;
          if ((*(byte *)(tmp_pu8 + 0x1a) & 1) == 0) {
            tmp_i9 = tmp_pu8[0x16];
            if (tmp_i9 < 0x65) {
              if (tmp_i9 < 0x14) {
                if (1.6 < tmp_f3) {
                  param_1[0x169] = 0x3fcccccd;
                  tmp_f3 = 1.6;
                  goto LAB_0004ac22;
                }
              }
              else {
                tmp_f3 = 1.6 - ((float)(tmp_i9 + -0x14) * 0.5) / 80.0;
                param_1[0x169] = tmp_f3;
              }
              goto LAB_0004aa30;
            }
            param_1[0x169] = 0x3f8ccccd;
            tmp_f3 = 1.1;
          }
          else {
            if (tmp_f3 <= 4.0) goto LAB_0004aa30;
            param_1[0x169] = 0x40800000;
            tmp_f3 = 4.0;
          }
LAB_0004ac22:
          tmp_i13 = param_1[0x15e];
          local_74 = param_1[0x15f];
          param_1[0x156] = param_1[0x157];
          tmp_i9 = param_1[0x153];
          param_1[0x158] = tmp_i13;
          param_1[0x159] = local_74;
LAB_0004aa70:
          local_6c = param_1[0x165];
          if ((param_1[0x166] != local_6c) &&
             (((tmp_pu8[0x16] == 0 || (tmp_i13 < (int)tmp_pu8[0x11])) ||
              ((int)(tmp_pu8[0x11] + tmp_pu8[0x12]) <= tmp_i13)))) {
            local_74 = param_1[0x168];
            param_1[0x15f] = local_74;
            if ((local_70 == (uint32_t *)0x0) || (tmp_pu8[0x16] == 0)) {
              tmp_i10 = tmp_pu8[0x12];
              tmp_i13 = 0;
              tmp_b4 = 1;
            }
            else {
              tmp_i10 = tmp_pu8[0x12];
              for (tmp_i13 = (tmp_i13 - local_70[0x11]) + 1; tmp_i13 < 0; tmp_i13 = tmp_i13 + tmp_i10) {
              }
              tmp_b4 = 1;
            }
            goto LAB_0004a900;
          }
          if (((tmp_i9 != 0) && ((*(byte *)(tmp_pu8 + 0x1a) & 2) == 0)) &&
             ((((local_6c ^ param_1[0x151]) & 0xfffffdff) == 0 && (*(int *)(tmp_i9 + 0x58) != 0)))) {
            tmp_i13 = param_1[0x14a] - *(int *)(tmp_i9 + 0x44);
            if (((int)tmp_pu8[0x12] <= tmp_i13) || (tmp_i13 < 0)) {
              tmp_i13 = 0;
            }
            local_74 = param_1[0x14b];
            tmp_b4 = 0;
            param_1[0x15f] = local_74;
            tmp_i10 = tmp_pu8[0x12];
            goto LAB_0004a900;
          }
          local_74 = local_74 + (int)ROUND((float)(int)tmp_pu8[0x14] * (1.0 / tmp_f3));
          param_1[0x15f] = local_74;
          tmp_i9 = g_unk_00abe908;
          if ((*(byte *)(tmp_pu8 + 0x1a) & 4) != 0) {
            local_68 = tmp_pu8[0x11];
            tmp_i10 = tmp_pu8[0x12];
            tmp_i13 = (local_68 - tmp_i13) + tmp_i10;
            if (tmp_i10 <= tmp_i13) goto LAB_0004abd0;
            tmp_b14 = local_74 < g_unk_00abe908;
            goto LAB_0004a932;
          }
          local_68 = tmp_pu8[0x11];
          tmp_i10 = tmp_pu8[0x12];
          tmp_i13 = (tmp_i13 - local_68) + 1;
          if (tmp_i10 <= tmp_i13) {
LAB_0004abd0:
            tmp_b4 = 1;
            goto LAB_0004abe0;
          }
          tmp_b14 = local_74 < g_unk_00abe908;
LAB_0004abb0:
          param_1[0x15e] = tmp_i13 + local_68;
          param_1[0x157] = *tmp_pu8;
        }
        param_1[0x166] = local_6c;
        local_70 = tmp_pu8;
      } while (tmp_b14);
    }
    if (tmp_i9 + 5000 < local_74) {
      param_1[0x15f] = tmp_i9;
    }
  }
  mdx_PlayerAngles(param_1,local_40,local_34,local_28,1);
  return;
}

void mdx_head_position(uint32_t param_1,int *param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  uint8_t local_70 [36];
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_28;
  float local_24;
  float local_20;
  
  if (*param_2 < 1) {
    tmp_i4 = 0;
  }
  else {
    tmp_i4 = (*param_2 + -1) * 0xbc;
  }
  trap_R_LerpTagNumber(&local_4c,param_2,*(uint32_t *)(mdm_models + 0x48 + tmp_i4));
  tmp_f1 = (float)param_2[0x1c];
  *param_3 = tmp_f1;
  tmp_f2 = (float)param_2[0x1d];
  param_3[1] = tmp_f2;
  tmp_f3 = (float)param_2[0x1e];
  param_3[2] = tmp_f3;
  tmp_f1 = (float)param_2[10] * local_4c + tmp_f1;
  *param_3 = tmp_f1;
  tmp_f2 = (float)param_2[0xb] * local_4c + tmp_f2;
  param_3[1] = tmp_f2;
  tmp_f3 = local_4c * (float)param_2[0xc] + tmp_f3;
  param_3[2] = tmp_f3;
  tmp_f1 = (float)param_2[0xd] * local_48 + tmp_f1;
  *param_3 = tmp_f1;
  tmp_f2 = (float)param_2[0xe] * local_48 + tmp_f2;
  param_3[1] = tmp_f2;
  tmp_f3 = local_48 * (float)param_2[0xf] + tmp_f3;
  param_3[2] = tmp_f3;
  *param_3 = (float)param_2[0x10] * local_44 + tmp_f1;
  param_3[1] = (float)param_2[0x11] * local_44 + tmp_f2;
  param_3[2] = local_44 * (float)param_2[0x12] + tmp_f3;
  MatrixMultiply(param_2 + 1,&local_40,local_70);
  MatrixMultiply(local_70,param_2 + 10,&local_40);
  *param_3 = local_40 * 0.5 + local_28 * 6.5 + *param_3;
  param_3[1] = local_3c * 0.5 + local_24 * 6.5 + param_3[1];
  param_3[2] = local_38 * 0.5 + local_20 * 6.5 + param_3[2];
  return;
}

void mdx_tag_position(uint32_t param_1,int *param_2,float *param_3,uint32_t param_4,
                     float param_5,float param_6)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_28;
  float local_24;
  float local_20;
  
  if (*param_2 < 1) {
    tmp_i5 = 0;
  }
  else {
    tmp_i5 = (*param_2 + -1) * 0xbc;
  }
  tmp_i5 = mdm_models + tmp_i5;
  tmp_i7 = 0;
  if (0 < *(int *)(tmp_i5 + 0x40)) {
    do {
      tmp_i6 = Q_stricmp(tmp_i7 * 0x74 + *(int *)(tmp_i5 + 0x44),param_4);
      if (tmp_i6 == 0) goto LAB_0004b3b5;
      tmp_i7 = tmp_i7 + 1;
    } while (tmp_i7 < *(int *)(tmp_i5 + 0x40));
  }
  tmp_i7 = -1;
LAB_0004b3b5:
  trap_R_LerpTagNumber(&local_4c,param_2,tmp_i7);
  tmp_f1 = (float)param_2[0x1c];
  *param_3 = tmp_f1;
  tmp_f2 = (float)param_2[0x1d];
  param_3[1] = tmp_f2;
  tmp_f3 = (float)param_2[0x1e];
  param_3[2] = tmp_f3;
  tmp_f1 = (float)param_2[10] * local_4c + tmp_f1;
  *param_3 = tmp_f1;
  tmp_f2 = (float)param_2[0xb] * local_4c + tmp_f2;
  param_3[1] = tmp_f2;
  tmp_f3 = local_4c * (float)param_2[0xc] + tmp_f3;
  param_3[2] = tmp_f3;
  tmp_f1 = (float)param_2[0xd] * local_48 + tmp_f1;
  *param_3 = tmp_f1;
  tmp_f2 = (float)param_2[0xe] * local_48 + tmp_f2;
  param_3[1] = tmp_f2;
  tmp_f3 = local_48 * (float)param_2[0xf] + tmp_f3;
  param_3[2] = tmp_f3;
  tmp_f1 = (float)param_2[0x10] * local_44 + tmp_f1;
  *param_3 = tmp_f1;
  tmp_f2 = (float)param_2[0x11] * local_44 + tmp_f2;
  param_3[1] = tmp_f2;
  tmp_f4 = (float)param_2[0x12];
  *param_3 = param_6 * local_40 + param_5 * local_28 + tmp_f1;
  param_3[1] = param_6 * local_3c + param_5 * local_24 + tmp_f2;
  param_3[2] = param_6 * local_38 + param_5 * local_20 + local_44 * tmp_f4 + tmp_f3;
  return;
}

void mdx_legs_position(uint32_t param_1,int *param_2,float *param_3)
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
  float tmp_f17;
  float tmp_f18;
  float tmp_f19;
  float tmp_f20;
  int tmp_i21;
  float local_4c;
  float local_48;
  float local_44;
  
  if (*param_2 < 1) {
    tmp_i21 = 0;
  }
  else {
    tmp_i21 = (*param_2 + -1) * 0xbc;
  }
  tmp_i21 = mdm_models + tmp_i21;
  trap_R_LerpTagNumber(&local_4c,param_2,*(uint32_t *)(tmp_i21 + 0x6c));
  tmp_f12 = (float)param_2[10] * local_4c;
  tmp_f1 = (float)param_2[0x1c];
  tmp_f13 = (float)param_2[0xb] * local_4c;
  tmp_f2 = (float)param_2[0x1d];
  tmp_f14 = local_4c * (float)param_2[0xc];
  tmp_f3 = (float)param_2[0x1e];
  tmp_f18 = (float)param_2[0xd] * local_48;
  tmp_f17 = (float)param_2[0xe] * local_48;
  tmp_f20 = local_48 * (float)param_2[0xf];
  tmp_f19 = (float)param_2[0x10] * local_44;
  tmp_f16 = (float)param_2[0x11] * local_44;
  tmp_f15 = local_44 * (float)param_2[0x12];
  trap_R_LerpTagNumber(&local_4c,param_2,*(uint32_t *)(tmp_i21 + 0x70));
  tmp_f4 = (float)param_2[0xb];
  tmp_f5 = (float)param_2[0x1d];
  tmp_f6 = (float)param_2[0xc];
  tmp_f7 = (float)param_2[0x1e];
  tmp_f8 = (float)param_2[0xe];
  tmp_f9 = (float)param_2[0xf];
  tmp_f10 = (float)param_2[0x11];
  tmp_f11 = (float)param_2[0x12];
  *param_3 = (tmp_f19 + tmp_f18 + tmp_f12 + tmp_f1 +
             (float)param_2[0x10] * local_44 +
             (float)param_2[0xd] * local_48 + (float)param_2[10] * local_4c + (float)param_2[0x1c])
             * 0.5;
  param_3[1] = (tmp_f10 * local_44 + tmp_f8 * local_48 + tmp_f4 * local_4c + tmp_f5 +
               tmp_f16 + tmp_f17 + tmp_f13 + tmp_f2) * 0.5;
  param_3[2] = (tmp_f11 * local_44 + local_48 * tmp_f9 + local_4c * tmp_f6 + tmp_f7 +
               tmp_f15 + tmp_f20 + tmp_f3 + tmp_f14) * 0.5;
  return;
}

void etseb_AddDebugAxis(uint32_t *param_1,uint32_t *param_2)
{
  int tmp_i1;
  
  tmp_i1 = nitrox_TempEventFromQueue(param_1,0x69);
  *(uint32_t *)(tmp_i1 + 0x18) = *param_1;
  *(uint32_t *)(tmp_i1 + 0x1c) = param_1[1];
  *(uint32_t *)(tmp_i1 + 0x20) = param_1[2];
  *(uint32_t *)(tmp_i1 + 0x68) = *param_2;
  *(uint32_t *)(tmp_i1 + 0x6c) = param_2[1];
  *(uint32_t *)(tmp_i1 + 0x70) = param_2[2];
  *(uint32_t *)(tmp_i1 + 0x74) = param_2[3];
  *(uint32_t *)(tmp_i1 + 0x78) = param_2[4];
  *(uint32_t *)(tmp_i1 + 0x7c) = param_2[5];
  *(uint32_t *)(tmp_i1 + 0x80) = param_2[6];
  *(uint32_t *)(tmp_i1 + 0x84) = param_2[7];
  *(uint32_t *)(tmp_i1 + 0x88) = param_2[8];
  return;
}

void etseb_AddDebugBox(uint32_t *param_1,uint32_t *param_2,float *param_3,uint32_t param_4)
{
  int tmp_i1;
  
  tmp_i1 = nitrox_TempEventFromQueue(param_1,0x6a);
  *(uint32_t *)(tmp_i1 + 0x18) = *param_1;
  *(uint32_t *)(tmp_i1 + 0x1c) = param_1[1];
  *(uint32_t *)(tmp_i1 + 0x20) = param_1[2];
  *(uint32_t *)(tmp_i1 + 0x68) = *param_2;
  *(uint32_t *)(tmp_i1 + 0x6c) = param_2[1];
  *(uint32_t *)(tmp_i1 + 0x70) = param_2[2];
  *(uint32_t *)(tmp_i1 + 0x74) = param_2[3];
  *(uint32_t *)(tmp_i1 + 0x78) = param_2[4];
  *(uint32_t *)(tmp_i1 + 0x7c) = param_2[5];
  *(uint32_t *)(tmp_i1 + 0x80) = param_2[6];
  *(uint32_t *)(tmp_i1 + 0x84) = param_2[7];
  *(uint32_t *)(tmp_i1 + 0x88) = param_2[8];
  *(int *)(tmp_i1 + 0x10c) = (int)ROUND(*param_3);
  *(int *)(tmp_i1 + 0x110) = (int)ROUND(param_3[1]);
  *(int *)(tmp_i1 + 0x114) = (int)ROUND(param_3[2]);
  *(uint32_t *)(tmp_i1 + 0x8c) = param_4;
  return;
}

void etpro_AddDebugLine(uint32_t *param_1,uint32_t *param_2,int param_3)
{
  int tmp_i1;
  
  tmp_i1 = nitrox_TempEventFromQueue(param_1,0x68);
  *(uint32_t *)(tmp_i1 + 0x68) = *param_1;
  *(uint32_t *)(tmp_i1 + 0x6c) = param_1[1];
  *(uint32_t *)(tmp_i1 + 0x70) = param_1[2];
  *(uint32_t *)(tmp_i1 + 0x18) = *param_2;
  *(uint32_t *)(tmp_i1 + 0x1c) = param_2[1];
  *(uint32_t *)(tmp_i1 + 0x20) = param_2[2];
  if (param_3 == 0) {
    *(uint32_t *)(tmp_i1 + 0x80) = 0x3f800000;
    *(uint32_t *)(tmp_i1 + 0x84) = 0x3f800000;
    *(uint32_t *)(tmp_i1 + 0x88) = 0x3f800000;
  }
  else if (param_3 == 1) {
    *(uint32_t *)(tmp_i1 + 0x80) = 0;
    *(uint32_t *)(tmp_i1 + 0x84) = 0x3f800000;
    *(uint32_t *)(tmp_i1 + 0x88) = 0;
  }
  else {
    *(uint32_t *)(tmp_i1 + 0x80) = 0x3f800000;
    *(uint32_t *)(tmp_i1 + 0x84) = 0;
    *(uint32_t *)(tmp_i1 + 0x88) = 0;
  }
  return;
}

void etpro_AddUsercmd(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint tmp_u4;
  
  tmp_i1 = *(int *)(g_entities + param_1 * 0x600 + 400);
  tmp_i2 = *(int *)(tmp_i1 + 0x1a80);
  tmp_i3 = *(int *)(tmp_i1 + 0x1a84);
  tmp_u4 = 0;
  do {
    *(uint32_t *)(tmp_i1 + ((tmp_i3 + tmp_i2) % 0x200) * 0x1c + 0x1a8c + tmp_u4) =
         *(uint32_t *)(param_2 + tmp_u4);
    tmp_u4 = tmp_u4 + 4;
  } while (tmp_u4 < 0x1c);
  tmp_i1 = *(int *)(g_entities + param_1 * 0x600 + 400);
  if (0x1ff < *(int *)(tmp_i1 + 0x1a84)) {
    *(int *)(tmp_i1 + 0x1a80) = (*(int *)(tmp_i1 + 0x1a80) + 1) % 0x200;
    return;
  }
  *(int *)(tmp_i1 + 0x1a84) = *(int *)(tmp_i1 + 0x1a84) + 1;
  return;
}

void etpro_PlayerInfo(void)
{
  char *tmp_pc1;
  bool tmp_b2;
  bool tmp_b3;
  bool tmp_b4;
  uint tmp_u5;
  int tmp_i6;
  char tmp_c7;
  uint tmp_u8;
  int tmp_i9;
  int tmp_i10;
  char *tmp_pc11;
  uint8_t *tmp_pu12;
  char local_5d [77];
  
  tmp_u8 = 0x41;
  tmp_b4 = false;
  tmp_b3 = false;
  tmp_b2 = true;
  if (((uint)local_5d & 1) == 0) {
    tmp_pc11 = local_5d;
    if (((uint)local_5d & 2) != 0) {
      local_5d[0] = '\0';
      tmp_u8 = 0x3f;
      tmp_b4 = true;
      tmp_b3 = true;
      tmp_b2 = true;
      tmp_pc11 = local_5d + 2;
    }
  }
  else {
    tmp_pc11 = local_5d + 1;
    tmp_u8 = 0x40;
    tmp_b4 = false;
    tmp_b3 = false;
    tmp_b2 = false;
    local_5d[0] = '\0';
  }
  tmp_u5 = 0;
  do {
    tmp_pc1 = tmp_pc11 + tmp_u5;
    tmp_pc1[0] = '\0';
    tmp_pc1[1] = '\0';
    tmp_pc1[2] = '\0';
    tmp_pc1[3] = '\0';
    tmp_pc1 = tmp_pc11 + tmp_u5 + 4;
    tmp_pc1[0] = '\0';
    tmp_pc1[1] = '\0';
    tmp_pc1[2] = '\0';
    tmp_pc1[3] = '\0';
    tmp_u5 = tmp_u5 + 8;
  } while (tmp_u5 < (tmp_u8 & 0xfffffff8));
  tmp_pc11 = tmp_pc11 + tmp_u5;
  if (tmp_b3) {
    tmp_pc11[0] = '\0';
    tmp_pc11[1] = '\0';
    tmp_pc11[2] = '\0';
    tmp_pc11[3] = '\0';
    tmp_pc11 = tmp_pc11 + 4;
  }
  if (tmp_b4) {
    tmp_pc11[0] = '\0';
    tmp_pc11[1] = '\0';
    tmp_pc11 = tmp_pc11 + 2;
  }
  if (tmp_b2) {
    *tmp_pc11 = '\0';
  }
  if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
    tmp_pu12 = g_entities;
    tmp_i6 = 0;
    tmp_i9 = -1;
    do {
      while ((tmp_i10 = tmp_i6, tmp_i6 = *(int *)(tmp_pu12 + 400), tmp_i6 != 0 &&
             (*(int *)(tmp_i6 + 0x5ac) != 0))) {
        tmp_c7 = '0';
        if (*(int *)(tmp_pu12 + 0x194) != 0) {
          tmp_c7 = (char)*(uint32_t *)(tmp_i6 + 3000) + '0';
        }
        local_5d[tmp_i10] = tmp_c7;
        tmp_pu12 = tmp_pu12 + 0x600;
        tmp_i6 = tmp_i10 + 1;
        tmp_i9 = tmp_i10;
        if (tmp_i10 + 1 == GHIDRA_FIELD(g_maxclients, 12, 4)) goto LAB_00088d8e;
      }
      local_5d[tmp_i10] = '-';
      tmp_i6 = tmp_i10 + 1;
      tmp_pu12 = tmp_pu12 + 0x600;
      tmp_i10 = tmp_i9;
    } while (tmp_i6 != GHIDRA_FIELD(g_maxclients, 12, 4));
LAB_00088d8e:
    if (tmp_i10 != -1) {
      local_5d[tmp_i10 + 1] = '\0';
      goto LAB_00088d98;
    }
  }
  local_5d[0] = '\0';
LAB_00088d98:
  trap_Cvar_Set("P",local_5d);
  return;
}

uint32_t etpro_ScriptAction_SetValues(int param_1,uint32_t param_2)
{
  bool tmp_b1;
  bool tmp_b2;
  bool tmp_b3;
  char *tmp_pc4;
  int tmp_i5;
  uint32_t tmp_u6;
  uint32_t local_820;
  char local_81c [1024];
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xc61ad;
  local_820 = param_2;
  tmp_b2 = false;
  tmp_b1 = false;
  g_unk_00abef88 = 0;
  g_unk_00abf18c = 0;
  while (tmp_pc4 = (char *)COM_ParseExt(&local_820,0), *tmp_pc4 != '\0') {
    strcpy(local_81c,tmp_pc4);
    tmp_pc4 = (char *)COM_ParseExt(&local_820,0);
    if (*tmp_pc4 == '\0') {
      G_Error("key \"%s\" has no value",local_81c);
      break;
    }
    strcpy(local_41c,tmp_pc4);
    if (GHIDRA_FIELD(g_scriptDebug, 12, 4) != 0) {
      G_Printf("%d : (%s) nitmod: set [%s] [%s] [%s]\n",g_unk_00abe908,
               *(uint32_t *)(param_1 + 0x3ac),*(uint32_t *)(param_1 + 0x3ac),local_81c,local_41c
              );
    }
    tmp_i5 = Q_stricmp(local_81c,"classname_nospawn");
    if (tmp_i5 == 0) {
      Q_strncpyz(local_81c,"classname",0x400);
      tmp_b2 = true;
    }
    tmp_i5 = Q_stricmp(local_81c,"classname");
    tmp_b3 = tmp_b1;
    if (tmp_i5 == 0) {
      tmp_i5 = Q_stricmp(local_41c,*(uint32_t *)(param_1 + 0x1a4));
      tmp_b3 = true;
      if (tmp_i5 == 0) {
        tmp_b3 = tmp_b1;
      }
    }
    tmp_b1 = tmp_b3;
    if (g_unk_00abef88 == 0x40) {
      G_Error("G_ParseSpawnVars: MAX_SPAWN_VARS");
    }
    tmp_i5 = g_unk_00abef88;
    tmp_u6 = G_AddSpawnVarToken(local_81c);
    (&g_unk_00abef8c)[tmp_i5 * 2] = tmp_u6;
    tmp_i5 = g_unk_00abef88;
    tmp_u6 = G_AddSpawnVarToken(local_41c);
    g_unk_00abef88 = g_unk_00abef88 + 1;
    (&g_unk_00abef90)[tmp_i5 * 2] = tmp_u6;
    G_ParseField(local_81c,local_41c,param_1);
    tmp_i5 = Q_stricmp(local_81c,"targetname");
    if (tmp_i5 == 0) {
      tmp_u6 = BG_StringHashValue(*(uint32_t *)(param_1 + 600));
      *(uint32_t *)(param_1 + 0x25c) = tmp_u6;
    }
    tmp_i5 = Q_stricmp(local_81c,"target");
    if (tmp_i5 == 0) {
      tmp_u6 = BG_StringHashValue(*(uint32_t *)(param_1 + 0x254));
      *(uint32_t *)(param_1 + 0x5bc) = tmp_u6;
    }
    tmp_i5 = Q_stricmp(local_81c,"scriptname");
    if (tmp_i5 == 0) {
      tmp_u6 = BG_StringHashValue(*(uint32_t *)(param_1 + 0x3ac));
      *(uint32_t *)(param_1 + 0x5b0) = tmp_u6;
    }
    if (*(int *)(param_1 + 0x5c0) == 0x499c5) {
      if (tmp_b1) {
        tmp_b1 = true;
      }
      else {
        G_ModifyTOI(param_1);
      }
    }
  }
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
  if (!tmp_b1) goto LAB_000c6502;
  if (tmp_b2) {
    tmp_pc4 = *(char **)(param_1 + 0x1a4);
    if (tmp_pc4 == (char *)0x0) goto LAB_000c64ef;
LAB_000c64ea:
    if (*tmp_pc4 == '\0') goto LAB_000c64ef;
    tmp_u6 = BG_StringHashValue(tmp_pc4);
    *(uint32_t *)(param_1 + 0x5c0) = tmp_u6;
  }
  else {
    G_CallSpawn(param_1);
    tmp_pc4 = *(char **)(param_1 + 0x1a4);
    if (tmp_pc4 != (char *)0x0) goto LAB_000c64ea;
LAB_000c64ef:
    *(uint32_t *)(param_1 + 0x5c0) = 0xffffffff;
  }
  trap_LinkEntity(param_1);
LAB_000c6502:
  if (*(int *)(param_1 + 0x120) != 0) {
    trap_LinkEntity(param_1);
  }
  return 1;
}

uint32_t etpro_ScriptAction_DeleteEntity(int param_1,uint32_t param_2)
{
  uint32_t *tmp_pu1;
  uint tmp_u2;
  char *tmp_pc3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  long tmp_l6;
  int tmp_i7;
  int tmp_i8;
  double tmp_d9;
  uint32_t local_8ac;
  uint32_t local_8a8;
  float local_8a4;
  uint32_t local_8a0;
  int local_89c [32];
  char local_81c [1024];
  char local_41c [1036];
  
  local_8ac = param_2;
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)local_89c + tmp_u2) = 0;
    *(uint32_t *)((int)local_89c + tmp_u2 + 4) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x80);
  if ((float)GHIDRA_FIELD(g_scriptDebug, 8, 4) != 0.0) {
    G_Printf("%d : (%s) Beginning entity deletion (from %s)\n",g_unk_00abe908,
             *(uint32_t *)(param_1 + 0x3ac),*(uint32_t *)(param_1 + 0x3ac));
  }
  tmp_i7 = 0;
  do {
    tmp_pc3 = (char *)COM_ParseExt(&local_8ac,0);
    if (*tmp_pc3 == '\0') {
joined_r0x000c6b99:
      if (tmp_i7 != 0) {
        tmp_i8 = 0;
        do {
          tmp_pu1 = (uint32_t *)local_89c[tmp_i8];
          if (tmp_pu1 != (uint32_t *)0x0) {
            if (GHIDRA_FIELD(g_scriptDebug, 12, 4) != 0) {
              G_Printf("%d : (%s) Freeing entity #%d\n",g_unk_00abe908,
                       *(uint32_t *)(param_1 + 0x3ac),*tmp_pu1);
            }
            G_FreeEntity(tmp_pu1);
          }
          tmp_i8 = tmp_i8 + 1;
        } while (tmp_i8 < tmp_i7);
        return 1;
      }
      G_Printf("G_ScriptAction_Delete(): No matches while deleting entity\n");
      return 0;
    }
    strcpy(local_81c,tmp_pc3);
    tmp_pc3 = (char *)COM_ParseExt(&local_8ac,0);
    if (*tmp_pc3 == '\0') {
      G_Error("G_ScriptAction_Delete(): key \"%s\" has no value",local_81c);
      goto joined_r0x000c6b99;
    }
    strcpy(local_41c,tmp_pc3);
    if (fields == (uint8_t *)0x0) {
LAB_000c6a74:
      G_Error("G_ScriptAction_Delete(): Unknown key \"%s\"",local_81c);
      goto joined_r0x000c6b99;
    }
    tmp_i8 = 0;
    tmp_pu4 = fields;
    while (tmp_i5 = Q_stricmp(tmp_pu4,local_81c), tmp_i5 != 0) {
      tmp_i8 = tmp_i8 + 1;
      tmp_pu4 = (&fields)[tmp_i8 * 4];
      if (tmp_pu4 == (uint8_t *)0x0) goto LAB_000c6a74;
    }
    if ((&fields)[tmp_i8 * 4] == (uint8_t *)0x0) goto LAB_000c6a74;
    if (GHIDRA_FIELD(g_scriptDebug, 12, 4) != 0) {
      G_Printf("%d : (%s) Searching for entity to delete where \"%s\" = \"%s\"\n",g_unk_00abe908,
               *(uint32_t *)(param_1 + 0x3ac),local_81c,local_41c);
    }
    switch((&g_unk_002baf08)[tmp_i8 * 4]) {
    case 0:
      tmp_l6 = strtol(local_41c,(char **)0x0,10);
      tmp_i5 = 0;
      while( true ) {
        tmp_i5 = nitrox_FindByInteger(tmp_i5,(&g_unk_002baf04)[tmp_i8 * 4],tmp_l6);
        local_89c[tmp_i7] = tmp_i5;
        if (tmp_i5 == 0) break;
        tmp_i7 = tmp_i7 + 1;
      }
      break;
    case 1:
      tmp_d9 = strtod(local_41c,(char **)0x0);
      tmp_i5 = 0;
      while( true ) {
        tmp_i5 = nitrox_FindByFloat(tmp_i5,(&g_unk_002baf04)[tmp_i8 * 4],(float)tmp_d9);
        local_89c[tmp_i7] = tmp_i5;
        if (tmp_i5 == 0) break;
        tmp_i7 = tmp_i7 + 1;
      }
      break;
    case 2:
    case 3:
      tmp_i5 = 0;
      while( true ) {
        tmp_i5 = G_Find(tmp_i5,(&g_unk_002baf04)[tmp_i8 * 4],local_41c);
        local_89c[tmp_i7] = tmp_i5;
        if (tmp_i5 == 0) break;
        tmp_i7 = tmp_i7 + 1;
      }
      break;
    case 4:
      __isoc99_sscanf(local_41c,"%f %f %f",&local_8a8,&local_8a4,&local_8a0);
      tmp_i5 = 0;
      while( true ) {
        tmp_i5 = nitrox_FindByVector(tmp_i5,(&g_unk_002baf04)[tmp_i8 * 4],&local_8a8);
        local_89c[tmp_i7] = tmp_i5;
        if (tmp_i5 == 0) break;
        tmp_i7 = tmp_i7 + 1;
      }
      break;
    case 5:
      local_8a8 = 0;
      tmp_d9 = strtod(local_41c,(char **)0x0);
      local_8a4 = (float)tmp_d9;
      tmp_i5 = 0;
      local_8a0 = 0;
      while( true ) {
        tmp_i5 = nitrox_FindByVector(tmp_i5,(&g_unk_002baf04)[tmp_i8 * 4],&local_8a8);
        local_89c[tmp_i7] = tmp_i5;
        if (tmp_i5 == 0) break;
        tmp_i7 = tmp_i7 + 1;
      }
      break;
    default:
      G_Error("G_ScriptAction_Delete(): Invalid key \"%s\"",local_81c);
    }
  } while( true );
}

