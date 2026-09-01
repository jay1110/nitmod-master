/* Other functions
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"
#include "et_ui_imports.h"
#include "et_ui_ui_misc.h"

void UI_StartServerRefresh(void)

{
{  int inreg_EAX;
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint8_t *tmp_pu3;
  char *tmp_pc4;
  char *tmp_pc5;
  uint32_t extraout_ECX;
  uint32_t extraout_EDX;
  long double tmp_l6;
  uint8_t local_70 [4];
  int local_6c;
  int local_68;
  uint32_t local_64;
  int local_60;
  int local_5c;
  uint8_t local_4c [60];
  uint32_t uStack_10;
  
  uStack_10 = 0x13e8a;
  trap_RealTime(local_70);
  if (local_6c < 10) {
    tmp_u1 = va(&g_dat_00055a23,local_6c,extraout_ECX,extraout_ECX);
  }
  else {
    tmp_u1 = va("%i",local_6c,extraout_EDX,extraout_EDX);
  }
  if (local_68 < 10) {
    tmp_u2 = va(&g_dat_00055a23,local_68,tmp_u1,tmp_u1);
  }
  else {
    tmp_u2 = va("%i",local_68,tmp_u1,tmp_u1);
  }
  Com_sprintf(local_4c,0x40,"%s-%i, %i at %s:%s",*(uint32_t *)(MonthAbbrev + local_60 * 4),
              local_64,local_5c + 0x76c,tmp_u2,tmp_u1);
  tmp_u1 = va("ui_lastServerRefresh_%i",GHIDRA_FIELD(ui_netSource, 12, 4));
  trap_Cvar_Set(tmp_u1,local_4c);
  if (inreg_EAX == 0) {
    trap_LAN_ResetPings(GHIDRA_FIELD(ui_netSource, 12, 4));
    g_dat_003e13b8 = 1;
    _DAT_003e13ac = g_dat_00397fdc + 1000;
  }
  else {
    g_dat_003e13b8 = 1;
    g_dat_003e53c0 = 0;
    g_dat_003e53d0 = 0;
    tmp_pu3 = (uint8_t *)(g_dat_00397fdc + 1000);
    _DAT_003e53d8 = tmp_pu3;
    trap_LAN_MarkServerVisible(GHIDRA_FIELD(ui_netSource, 12, 4),0xffffffff,1,tmp_pu3);
    trap_LAN_ResetPings(GHIDRA_FIELD(ui_netSource, 12, 4));
    if (GHIDRA_FIELD(ui_netSource, 12, 4) == 0) {
      trap_Cmd_ExecuteText(2,"localservers\n");
      _DAT_003e13ac = g_dat_00397fdc + 1000;
    }
    else {
      _DAT_003e13ac = g_dat_00397fdc + 5000;
      if (GHIDRA_FIELD(ui_netSource, 12, 4) == 1) {
        tmp_pc4 = (char *)UI_Cvar_VariableString("debug_protocol");
        if (*tmp_pc4 == '\0') {
          tmp_l6 = (long double)trap_Cvar_VariableValue("protocol");
          tmp_pc4 = (char *)(int)ROUND(tmp_l6);
          tmp_pc5 = "globalservers %d %d\n";
        }
        else {
          tmp_pc5 = "globalservers %d %s\n";
          tmp_pu3 = local_4c;
        }
        tmp_u1 = va(tmp_pc5,0,tmp_pc4,tmp_pu3);
        trap_Cmd_ExecuteText(2,tmp_u1);
      }
    }
  }
  return;
}

void ConcatArgs(int param_1)

{
{  int tmp_i1;
  uint tmp_u2;
  uint tmp_u3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  uint *tmp_pu6;
  int tmp_i7;
  uint *tmp_pu8;
  uint *tmp_pu9;
  byte tmp_b10;
  uint8_t local_41c;
  uint auStack_41b [257];
  uint32_t uStack_14;
  
  tmp_b10 = 0;
  uStack_14 = 0x1a22b;
  tmp_i1 = trap_Argc();
  if (param_1 < tmp_i1) {
    tmp_i7 = 0;
    do {
      trap_Argv(param_1,&local_41c,0x400);
      tmp_pu8 = (uint *)&local_41c;
      do {
        tmp_pu6 = tmp_pu8;
        tmp_u2 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
        tmp_u3 = tmp_u2 & 0x80808080;
        tmp_pu8 = tmp_pu6 + 1;
      } while (tmp_u3 == 0);
      if ((tmp_u2 & 0x8080) == 0) {
        tmp_pu8 = (uint *)((int)tmp_pu6 + 6);
        tmp_u3 = tmp_u3 >> 0x10;
      }
      tmp_pu4 = (uint8_t *)
               ((int)tmp_pu8 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)&local_41c));
      tmp_i5 = tmp_i7 + (int)tmp_pu4;
      if (0x3fe < tmp_i5) break;
      tmp_pu6 = (uint *)(&line_7641 + tmp_i7);
      tmp_pu8 = (uint *)&local_41c;
      if ((uint8_t *)0x7 < tmp_pu4) {
        tmp_pu9 = tmp_pu6;
        if (((uint)tmp_pu6 & 1) != 0) {
          tmp_pu9 = (uint *)(&g_dat_00069ce1 + tmp_i7);
          tmp_pu4 = tmp_pu4 + -1;
          tmp_pu8 = auStack_41b;
          *(uint8_t *)tmp_pu6 = local_41c;
        }
        tmp_pu6 = tmp_pu9;
        if (((uint)tmp_pu9 & 2) != 0) {
          tmp_u3 = *tmp_pu8;
          tmp_pu6 = (uint *)((int)tmp_pu9 + 2);
          tmp_pu8 = (uint *)((int)tmp_pu8 + 2);
          tmp_pu4 = tmp_pu4 + -2;
          *(short *)tmp_pu9 = (short)tmp_u3;
        }
        if (((uint)tmp_pu6 & 4) != 0) {
          tmp_pu4 = tmp_pu4 + -4;
          *tmp_pu6 = *tmp_pu8;
          tmp_pu8 = tmp_pu8 + 1;
          tmp_pu6 = tmp_pu6 + 1;
        }
      }
      for (; tmp_pu4 != (uint8_t *)0x0; tmp_pu4 = tmp_pu4 + -1) {
        *(char *)tmp_pu6 = (char)*tmp_pu8;
        tmp_pu8 = (uint *)((int)tmp_pu8 + (uint)tmp_b10 * -2 + 1);
        tmp_pu6 = (uint *)((int)tmp_pu6 + (uint)tmp_b10 * -2 + 1);
      }
      if (tmp_i1 + -1 != param_1) {
        (&line_7641)[tmp_i5] = 0x20;
        tmp_i5 = tmp_i5 + 1;
      }
      param_1 = param_1 + 1;
      tmp_i7 = tmp_i5;
    } while (param_1 != tmp_i1);
  }
  else {
    tmp_i7 = 0;
  }
  (&line_7641)[tmp_i7] = 0;
  return;
}

int ClampShort(int param_1)

{
{  int tmp_i1;
  
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
{  float tmp_f1;
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
{  if (param_1 < 0xa2) {
    *param_2 = (&bytedirs)[param_1 * 3];
    param_2[1] = (&g_dat_00066ee4)[param_1 * 3];
    param_2[2] = (&g_dat_00066ee8)[param_1 * 3];
    return;
  }
  *param_2 = vec3_origin;
  param_2[1] = g_dat_0006c114;
  param_2[2] = g_dat_0006c118;
  return;
}

uint32_t PlaneFromPoints(float *param_1,float *param_2,float *param_3,float *param_4)

{
{  float tmp_f1;
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

void vectoangles(float *param_1,float *param_2)

{
{  float tmp_f1;
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
      goto LAB_0001aad0;
    }
LAB_0001aa50:
    tmp_d3 = atan2((double)tmp_f4,(double)tmp_f1);
    tmp_f2 = ((float)tmp_d3 * 180.0) / 3.1415927;
    if (tmp_f2 < 0.0) {
      tmp_f2 = tmp_f2 + 360.0;
    }
    tmp_f1 = *param_1;
    tmp_f4 = param_1[1];
  }
  else {
    if (tmp_f1 != 0.0) goto LAB_0001aa50;
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
LAB_0001aad0:
  *param_2 = tmp_f1;
  param_2[1] = tmp_f2;
  param_2[2] = 0.0;
  return;
}

void AnglesToAxis(float *param_1,float *param_2)

{
{  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  double local_2c;
  double local_24 [2];
  uint32_t uStack_14;
  
  uStack_14 = 0x1aba9;
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
  param_2[4] = g_dat_0006c114 - (tmp_f3 * tmp_f6 * tmp_f1 - tmp_f2 * tmp_f7);
  param_2[5] = g_dat_0006c118 - tmp_f4 * tmp_f6;
  return;
}

void AxisClear(uint32_t *param_1)

{
{  *param_1 = 0x3f800000;
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
{  *param_2 = *param_1;
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
{  float tmp_f1;
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
{  float tmp_f1;
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

long double LerpAngle(float param_1,float param_2,float param_3)

{
{  long double tmp_l1;
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
{  float tmp_f1;
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

void AnglesSubtract(float *param_1,float *param_2,float *param_3)

{
{  float tmp_f1;
  
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

void SetPlaneSignbits(float *param_1)

{
{  byte tmp_b1;
  
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
{  long double tmp_l1;
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

void AddPointToBounds(float *param_1,float *param_2,float *param_3)

{
{  float tmp_f1;
  
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

void VectorNormalize(float *param_1)

{
{  float __x;
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
{  float tmp_f1;
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
{  long double tmp_l1;
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

long double VectorLength(float *param_1)

{
{  long double tmp_l1;
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

long double Distance(float *param_1,float *param_2)

{
{  long double tmp_l1;
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

void MatrixMultiply(float *param_1,float *param_2,float *param_3)

{
{  *param_3 = param_1[2] * param_2[6] + param_1[1] * param_2[3] + *param_1 * *param_2;
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
{  float tmp_f1;
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
{  float tmp_f1;
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
{  float tmp_f1;
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

void GetPerpendicularViewVector(float *param_1,float *param_2,float *param_3,float *param_4)

{
{  float tmp_f1;
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
{  float tmp_f1;
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
{  float tmp_f1;
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
{  long double tmp_l1;
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
{  long double tmp_l1;
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
{  long double tmp_l1;
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
{  float tmp_f1;
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
  RotatePointAroundVector(tmp_pu4,0x67a78,&local_34,-param_2[1],tmp_pu4);
  RotatePointAroundVector(&local_34,0x67a6c,tmp_pu4,-*param_2);
  if (local_30 == 0.0) {
    if (local_34 != 0.0) {
LAB_0001d020:
      atan2((double)local_30,(double)local_34);
      goto LAB_0001d042;
    }
    if (local_2c <= 0.0) {
      tmp_f1 = 90.0;
      if (local_2c * (float)GHIDRA_FIELD(axisDefault, 20, 4) +
          local_34 * (float)GHIDRA_FIELD(axisDefault, 12, 4) + (float)GHIDRA_FIELD(axisDefault, 16, 4) * local_30 < 0.0)
      goto LAB_0001d156;
      goto LAB_0001d11e;
    }
    tmp_f1 = -90.0;
  }
  else {
    if (local_34 != 0.0) goto LAB_0001d020;
LAB_0001d042:
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
LAB_0001d156:
      param_2[2] = -((90.0 - tmp_f1) + 90.0);
      return;
    }
    tmp_f1 = (-90.0 - tmp_f1) - 90.0;
  }
LAB_0001d11e:
  param_2[2] = -tmp_f1;
  return;
}

long double VectorDistance(float *param_1,float *param_2)

{
{  long double tmp_l1;
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

void SkipBracedSection_Depth(int *param_1,int param_2)

{
{  char *tmp_pc1;
  
  do {
    tmp_pc1 = (char *)COM_ParseExt_constprop_2();
    if (tmp_pc1[1] == '\0') {
      if (*tmp_pc1 == '{') {
        param_2 = param_2 + 1;
      }
      else {
        param_2 = param_2 - (uint)(*tmp_pc1 == '}');
      }
    }
  } while ((param_2 != 0) && (*param_1 != 0));
  return;
}

void SkipBracedSection(int *param_1)

{
{  char *tmp_pc1;
  int tmp_i2;
  
  tmp_i2 = 0;
  do {
    tmp_pc1 = (char *)COM_ParseExt_constprop_2();
    if (tmp_pc1[1] == '\0') {
      if (*tmp_pc1 == '{') {
        tmp_i2 = tmp_i2 + 1;
      }
      else {
        tmp_i2 = tmp_i2 - (uint)(*tmp_pc1 == '}');
      }
    }
  } while ((tmp_i2 != 0) && (*param_1 != 0));
  return;
}

void SkipRestOfLine(uint32_t *param_1)

{
{  char tmp_c1;
  char *tmp_pc2;
  char *tmp_pc3;
  
  tmp_pc3 = (char *)*param_1;
  do {
    tmp_pc2 = tmp_pc3 + 1;
    tmp_c1 = *tmp_pc3;
    if (tmp_c1 == '\0') {
      *param_1 = tmp_pc2;
      return;
    }
    tmp_pc3 = tmp_pc2;
  } while (tmp_c1 != '\n');
  *param_1 = tmp_pc2;
  com_lines = com_lines + 1;
  return;
}

void va(char *param_1)

{
{  int tmp_i1;
  uint tmp_u2;
  uint tmp_u3;
  uint8_t *tmp_pu4;
  uint *tmp_pu5;
  uint8_t *tmp_pu6;
  uint *tmp_pu7;
  uint *tmp_pu8;
  uint *tmp_pu9;
  byte tmp_b10;
  int local_20;
  
  tmp_b10 = 0;
  tmp_pu7 = (uint *)&temp_buffer_5371;
  vsnprintf(&temp_buffer_5371,32000,param_1,&stack0x00000008);
  tmp_pu5 = tmp_pu7;
  do {
    tmp_pu8 = tmp_pu5;
    tmp_u2 = *tmp_pu8 + 0xfefefeff & ~*tmp_pu8;
    tmp_u3 = tmp_u2 & 0x80808080;
    tmp_pu5 = tmp_pu8 + 1;
  } while (tmp_u3 == 0);
  if ((tmp_u2 & 0x8080) == 0) {
    tmp_pu5 = (uint *)((int)tmp_pu8 + 6);
    tmp_u3 = tmp_u3 >> 0x10;
  }
  tmp_i1 = -(uint)CARRY1((byte)tmp_u3,(byte)tmp_u3);
  tmp_pu6 = (uint8_t *)((int)tmp_pu5 + tmp_i1 + -0x78323);
  if ((uint8_t *)0x7cff < tmp_pu6) {
    Com_Error(2,"Attempted to overrun string in call to va()\n");
  }
  if (tmp_pu6 + (int)index_5373 < (uint8_t *)0x7cff) {
    local_20 = (int)index_5373 + 1;
  }
  else {
    index_5373 = (uint8_t *)0x0;
    local_20 = 1;
  }
  tmp_pu4 = (uint8_t *)((int)tmp_pu5 + tmp_i1 + -0x78322);
  tmp_pu5 = (uint *)(&string_5372 + (int)index_5373);
  if ((uint8_t *)0x7 < tmp_pu4) {
    tmp_pu8 = tmp_pu5;
    if (((uint)tmp_pu5 & 1) != 0) {
      tmp_pu8 = (uint *)(&g_dat_00070601 + (int)index_5373);
      tmp_pu7 = (uint *)&g_dat_00078321;
      *(uint8_t *)tmp_pu5 = temp_buffer_5371;
      tmp_pu4 = tmp_pu6;
    }
    tmp_pu9 = tmp_pu8;
    if (((uint)tmp_pu8 & 2) != 0) {
      tmp_u3 = *tmp_pu7;
      tmp_pu9 = (uint *)((int)tmp_pu8 + 2);
      tmp_pu7 = (uint *)((int)tmp_pu7 + 2);
      tmp_pu4 = tmp_pu4 + -2;
      *(short *)tmp_pu8 = (short)tmp_u3;
    }
    tmp_pu5 = tmp_pu9;
    if (((uint)tmp_pu9 & 4) != 0) {
      tmp_u3 = *tmp_pu7;
      tmp_pu5 = tmp_pu9 + 1;
      tmp_pu7 = tmp_pu7 + 1;
      tmp_pu4 = tmp_pu4 + -4;
      *tmp_pu9 = tmp_u3;
    }
  }
  for (; tmp_pu4 != (uint8_t *)0x0; tmp_pu4 = tmp_pu4 + -1) {
    *(char *)tmp_pu5 = (char)*tmp_pu7;
    tmp_pu7 = (uint *)((int)tmp_pu7 + (uint)tmp_b10 * -2 + 1);
    tmp_pu5 = (uint *)((int)tmp_pu5 + (uint)tmp_b10 * -2 + 1);
  }
  index_5373 = tmp_pu6 + local_20;
  return;
}

uint32_t encode64(byte *param_1,char *param_2,int param_3)

{
{  byte tmp_b1;
  byte tmp_b2;
  byte tmp_b3;
  char tmp_c4;
  char tmp_c5;
  char *tmp_pc6;
  uint32_t uStack_14;
  
  for (; 2 < param_3; param_3 = param_3 + -3) {
    tmp_b1 = *param_1;
    tmp_b2 = param_1[1];
    tmp_b3 = param_1[2];
    uStack_14 = CONCAT13(tmp_b3,(uint32_t)uStack_14);
    *param_2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[tmp_b1 >> 2];
    param_2[1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
                 [(uint)(tmp_b2 >> 4) | (uint)(tmp_b1 & 3) << 4];
    param_2[2] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
                 [(uint)(tmp_b3 >> 6) | (uint)(tmp_b2 & 0xf) << 2];
    param_2[3] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[tmp_b3 & 0x3f];
    param_1 = param_1 + 3;
    param_2 = param_2 + 4;
  }
  if (param_3 != 0) {
    tmp_b1 = *param_1;
    *param_2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[tmp_b1 >> 2];
    if (param_3 == 1) {
      tmp_c5 = '=';
      tmp_c4 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
              [(uint)(tmp_b1 & 3) * 0x10];
    }
    else {
      tmp_c5 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
              [(uint)(param_1[1] & 0xf) * 4];
      tmp_c4 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
              [(uint)(tmp_b1 & 3) << 4 | (uint)(param_1[1] >> 4)];
    }
    tmp_pc6 = param_2 + 3;
    param_2[2] = tmp_c5;
    param_2[1] = tmp_c4;
    param_2 = param_2 + 4;
    *tmp_pc6 = '=';
  }
  *param_2 = '\0';
  return uStack_14;
}

void decode64(int param_1)

{
{  int tmp_i1;
  char tmp_c2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  int local_18;
  byte local_13;
  byte local_12;
  char local_11;
  byte local_10;
  char local_f;
  byte local_e;
  char local_d;
  
  local_d = '\0';
  local_18 = 0;
  tmp_i5 = 0;
LAB_0001fd00:
  do {
    tmp_c2 = *(char *)(param_1 + tmp_i5);
    tmp_i4 = tmp_i5;
    tmp_i1 = local_18;
    while( true ) {
      if ((tmp_c2 == '=') || (tmp_c2 < '!')) {
        *(uint8_t *)(param_1 + tmp_i1) = 0;
        return;
      }
      tmp_i3 = (int)tmp_c2;
      tmp_i5 = tmp_i4 + 1;
      local_13 = local_11 >> 4;
      if (tmp_i3 - 0x41U < 0x1a) break;
      if (tmp_i3 - 0x61U < 0x1a) {
        local_d = tmp_c2 + -0x47;
        local_12 = local_d * '\x04';
      }
      else if (tmp_i3 - 0x30U < 10) {
        local_d = tmp_c2 + '\x04';
        local_12 = local_d * '\x04';
      }
      else if (tmp_c2 == '+') {
        local_12 = 0xf8;
        local_d = '>';
      }
      else if (tmp_c2 == '/') {
        local_12 = 0xfc;
        local_d = '?';
      }
      else {
        local_12 = local_d << 2;
      }
      tmp_c2 = *(char *)(param_1 + tmp_i5);
      if (tmp_c2 == '=') goto LAB_0001fef8;
LAB_0001fd6d:
      tmp_i3 = (int)tmp_c2;
      tmp_i5 = tmp_i4 + 2;
      if (tmp_i3 - 0x41U < 0x1a) {
        local_11 = tmp_c2 + -0x41;
        local_13 = local_11 >> 4;
        tmp_c2 = *(char *)(param_1 + tmp_i5);
      }
      else {
        if (tmp_i3 - 0x61U < 0x1a) {
          local_11 = tmp_c2 + -0x47;
          local_13 = local_11 >> 4;
        }
        else if (tmp_i3 - 0x30U < 10) {
          local_11 = tmp_c2 + '\x04';
          local_13 = local_11 >> 4;
        }
        else if (tmp_i3 == 0x2b) {
          local_13 = 3;
          local_11 = '>';
        }
        else if (tmp_i3 == 0x2f) {
          local_13 = 3;
          local_11 = '?';
        }
        tmp_c2 = *(char *)(param_1 + tmp_i5);
      }
      if (tmp_c2 == '=') goto LAB_0001fef8;
      tmp_i3 = (int)tmp_c2;
      tmp_i5 = tmp_i4 + 3;
      if (tmp_i3 - 0x41U < 0x1a) {
        local_f = tmp_c2 + -0x41;
        local_10 = local_f >> 2;
        tmp_c2 = *(char *)(param_1 + tmp_i5);
        if (tmp_c2 != '=') goto LAB_0001fe2d;
LAB_0001ff5a:
        tmp_i4 = 3;
      }
      else {
        if (tmp_i3 - 0x61U < 0x1a) {
          local_f = tmp_c2 + -0x47;
          local_10 = local_f >> 2;
        }
        else if (tmp_i3 - 0x30U < 10) {
          local_f = tmp_c2 + '\x04';
          local_10 = local_f >> 2;
        }
        else if (tmp_i3 == 0x2b) {
          local_10 = 0xf;
          local_f = '>';
        }
        else if (tmp_i3 == 0x2f) {
          local_10 = 0xf;
          local_f = '?';
        }
        else {
          local_10 = local_f >> 2;
        }
        tmp_c2 = *(char *)(param_1 + tmp_i5);
        if (tmp_c2 == '=') goto LAB_0001ff5a;
LAB_0001fe2d:
        tmp_i3 = (int)tmp_c2;
        tmp_i5 = tmp_i4 + 4;
        if (tmp_i3 - 0x41U < 0x1a) {
          local_e = tmp_c2 + 0xbf;
          tmp_i4 = 4;
        }
        else if (tmp_i3 - 0x61U < 0x1a) {
          local_e = tmp_c2 + 0xb9;
          tmp_i4 = 4;
        }
        else if (tmp_i3 - 0x30U < 10) {
          local_e = tmp_c2 + 4;
          tmp_i4 = 4;
        }
        else if (tmp_i3 == 0x2b) {
          local_e = 0x3e;
          tmp_i4 = 4;
        }
        else {
          if (tmp_i3 == 0x2f) {
            local_e = 0x3f;
          }
          tmp_i4 = 4;
        }
      }
      local_18 = tmp_i1 + 2;
      *(byte *)(param_1 + tmp_i1) = local_13 | local_12;
      *(byte *)(param_1 + 1 + tmp_i1) = local_11 << 4 | local_10;
      if (tmp_i4 != 4) goto LAB_0001fd00;
      tmp_i1 = tmp_i1 + 3;
      *(byte *)(param_1 + local_18) = local_f << 6 | local_e;
      tmp_c2 = *(char *)(param_1 + tmp_i5);
      tmp_i4 = tmp_i5;
    }
    local_d = tmp_c2 + -0x41;
    local_12 = local_d * '\x04';
    tmp_c2 = *(char *)(param_1 + tmp_i5);
    if (tmp_c2 != '=') goto LAB_0001fd6d;
LAB_0001fef8:
    *(byte *)(param_1 + tmp_i1) = local_13 | local_12;
    local_18 = tmp_i1 + 1;
  } while( true );
}

uint32_t FileExists(uint32_t param_1)

{
{  int tmp_i1;
  uint32_t local_10 [3];
  
  tmp_i1 = trap_FS_FOpenFile(param_1,local_10,0);
  if (-1 < tmp_i1) {
    trap_FS_FCloseFile(local_10[0]);
    return 1;
  }
  trap_FS_FCloseFile(local_10[0]);
  return 0;
}

void nitrox_ClampFloat(float *param_1,float param_2,float param_3)

{
{  float tmp_f1;
  
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
{  float tmp_f1;
  
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

uint32_t need_escape(byte *param_1)

{
{  byte tmp_b1;
  
  tmp_b1 = *param_1;
  while( true ) {
    if (tmp_b1 == 0) {
      return 0;
    }
    if ((tmp_b1 == 0x25 || tmp_b1 == 0x3d) || (0x7e < tmp_b1)) break;
    param_1 = param_1 + 1;
    tmp_b1 = *param_1;
  }
  return 1;
}

void nitrox_stripLeadingSpaces(char *param_1)

{
{  char tmp_c1;
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

uint32_t UI_ConsoleCommand(int param_1)

{
{  int tmp_i1;
  int local_c18 [771];
  uint32_t uStack_c;
  
  tmp_i1 = g_dat_00397fdc;
  uStack_c = 0x20757;
  g_dat_00397fdc = param_1;
  g_dat_00397fe0 = param_1 - tmp_i1;
  trap_Argv(0,buffer_9111,0x400);
  tmp_i1 = Q_stricmp(buffer_9111,"ui_test");
  if (tmp_i1 == 0) {
    UI_ShowPostGame(1);
  }
  tmp_i1 = Q_stricmp(buffer_9111,"ui_report");
  if (tmp_i1 == 0) {
    UI_Report();
    return 1;
  }
  tmp_i1 = Q_stricmp(buffer_9111,"ui_load");
  if (tmp_i1 == 0) {
    UI_Load();
    return 1;
  }
  tmp_i1 = Q_stricmp(buffer_9111,"postgame");
  if (tmp_i1 != 0) {
    tmp_i1 = Q_stricmp(buffer_9111,"ui_cache");
    if (tmp_i1 == 0) {
      Display_CacheAll();
      return 1;
    }
    tmp_i1 = Q_stricmp(buffer_9111,"ui_teamOrders");
    if (tmp_i1 != 0) {
      trap_GetClientState(local_c18);
      if (local_c18[0] == 1) {
        tmp_i1 = Q_stricmp(buffer_9111,"campaign");
        if (tmp_i1 == 0) {
          UI_Campaign_f();
          return 1;
        }
        tmp_i1 = Q_stricmp(buffer_9111,"listcampaigns");
        if (tmp_i1 == 0) {
          UI_ListCampaigns_f();
          return 1;
        }
      }
      return 0;
    }
  }
  return 1;
}

void UI_AdjustFrom640(float *param_1,float *param_2,float *param_3,float *param_4)

{
{  *param_1 = *param_1 * g_dat_00397fd4;
  *param_2 = *param_2 * g_dat_00397fd0;
  *param_3 = *param_3 * g_dat_00397fd4;
  *param_4 = *param_4 * g_dat_00397fd0;
  if (1.3333334 < g_dat_003b7efc) {
    *param_1 = (1.3333334 / g_dat_003b7efc) * *param_1;
    *param_3 = (1.3333334 / g_dat_003b7efc) * *param_3;
  }
  return;
}

void UI_SortArenas(uint32_t *param_1,uint32_t *param_2)

{
{  uint32_t tmp_u1;
  char local_80c [1024];
  char local_40c [1024];
  
  tmp_u1 = *param_2;
  Q_strncpyz(local_80c,*param_1,0x400);
  Q_strncpyz(local_40c,tmp_u1,0x400);
  Q_CleanStr(local_80c);
  Q_CleanStr(local_40c);
  strcmp(local_80c,local_40c);
  return;
}

void UI_SortCampaigns(int param_1,int param_2)

{
{  uint32_t tmp_u1;
  char local_80c [1024];
  char local_40c [1024];
  
  tmp_u1 = *(uint32_t *)(param_2 + 4);
  Q_strncpyz(local_80c,*(uint32_t *)(param_1 + 4),0x400);
  Q_strncpyz(local_40c,tmp_u1,0x400);
  Q_CleanStr(local_80c);
  Q_CleanStr(local_40c);
  strcmp(local_80c,local_40c);
  return;
}

void UI_LoadArenas(void)

{
{  uint tmp_u1;
  int tmp_i2;
  size_t tmp_s3;
  int tmp_i4;
  int tmp_i5;
  uint32_t tmp_u6;
  char *tmp_pc7;
  uint8_t *tmp_pu8;
  uint tmp_u9;
  int tmp_i10;
  char *tmp_pc11;
  byte tmp_b12;
  int local_8d8;
  char *local_8cc;
  uint32_t local_8b4;
  uint32_t local_8b0;
  uint32_t local_8ac;
  char local_8a8 [116];
  char local_834 [1024];
  uint8_t local_434 [16];
  char local_424 [1040];
  uint32_t uStack_14;
  
  tmp_b12 = 0;
  uStack_14 = 0x213db;
  local_8cc = local_834;
  ui_numArenas = 0;
  g_dat_003bab6c = 0;
  tmp_i2 = trap_FS_GetFileList("scripts",".arena",local_8cc,0x400);
  if (0 < tmp_i2) {
    local_8d8 = 0;
    do {
      tmp_s3 = strlen(local_8cc);
      local_8b4 = 0x69726373;
      local_8b0 = 0x2f737470;
      tmp_u1 = tmp_s3 + 1;
      tmp_u9 = tmp_u1;
      tmp_pc7 = local_8cc;
      tmp_pc11 = (char *)&local_8ac;
      if ((7 < tmp_u1) && (((uint)&local_8ac & 4) != 0)) {
        local_8ac = *(uint32_t *)local_8cc;
        tmp_pc7 = local_8cc + 4;
        tmp_u9 = tmp_s3 - 3;
        tmp_pc11 = local_8a8;
      }
      for (; tmp_u9 != 0; tmp_u9 = tmp_u9 - 1) {
        *tmp_pc11 = *tmp_pc7;
        tmp_pc7 = tmp_pc7 + (uint)tmp_b12 * -2 + 1;
        tmp_pc11 = tmp_pc11 + (uint)tmp_b12 * -2 + 1;
      }
      tmp_i4 = trap_PC_LoadSource(&local_8b4);
      if (tmp_i4 == 0) {
        tmp_u6 = va("^1file not found: %s\n",&local_8b4);
        trap_Print(tmp_u6);
      }
      else {
        tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
        if ((tmp_i5 != 0) && (local_424[0] == '{')) {
          tmp_i5 = g_dat_003bab6c + 0x45a;
          tmp_i10 = g_dat_003bab6c * 0x80;
          (&g_dat_003bab80)[g_dat_003bab6c * 0x20] = 0xffffffff;
          (&g_dat_00397ec8)[tmp_i5 * 0x20] = 0xffffffff;
          *(uint32_t *)(&g_dat_003bab7c + tmp_i10) = 0;
LAB_00021510:
          do {
            while( true ) {
              while( true ) {
                tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
                if (tmp_i5 == 0) goto LAB_00021620;
                if (local_424[0] != '}') break;
                if (*(int *)(&g_dat_003bab7c + g_dat_003bab6c * 0x80) == 0) {
                  *(uint32_t *)(&g_dat_003bab7c + g_dat_003bab6c * 0x80) = 4;
                }
                g_dat_003bab6c = g_dat_003bab6c + 1;
                if ((0x1ff < (int)g_dat_003bab6c) ||
                   (tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434), tmp_i5 == 0)) goto LAB_00021620;
                if (local_424[0] != '{') {
                  tmp_u6 = va("^1unexpected token \'%s\' inside: %s\n",local_424,&local_8b4);
                  trap_Print(tmp_u6);
                  trap_PC_FreeSource(tmp_i4);
                  goto LAB_00021628;
                }
              }
              tmp_i5 = Q_stricmp(local_424,"map");
              if (tmp_i5 != 0) break;
              tmp_pu8 = &g_dat_003bab74 + g_dat_003bab6c * 0x80;
LAB_000215eb:
              tmp_i5 = PC_String_Parse(tmp_i4,tmp_pu8);
joined_r0x0002191f:
              if (tmp_i5 == 0) goto LAB_000215ff;
            }
            tmp_i5 = Q_stricmp(local_424,"longname");
            if (tmp_i5 == 0) {
              tmp_pu8 = &g_dat_003bab70 + g_dat_003bab6c * 0x80;
              goto LAB_000215eb;
            }
            tmp_i5 = Q_stricmp(local_424,"briefing");
            if (tmp_i5 == 0) {
              tmp_pu8 = &g_dat_003babe4 + g_dat_003bab6c * 0x80;
              goto LAB_000215eb;
            }
            tmp_i5 = Q_stricmp(local_424,"lmsbriefing");
            if (tmp_i5 == 0) {
              tmp_pu8 = &g_dat_003babe8 + g_dat_003bab6c * 0x80;
              goto LAB_000215eb;
            }
            tmp_i5 = Q_stricmp(local_424,"timelimit");
            if (tmp_i5 != 0) {
              tmp_i5 = Q_stricmp(local_424,"axisrespawntime");
              if (tmp_i5 == 0) {
                tmp_pu8 = &g_dat_003babd4 + g_dat_003bab6c * 0x80;
                goto LAB_0002178a;
              }
              tmp_i5 = Q_stricmp(local_424,"alliedrespawntime");
              if (tmp_i5 == 0) {
                tmp_pu8 = &g_dat_003babd8 + g_dat_003bab6c * 0x80;
                goto LAB_0002178a;
              }
              tmp_i5 = Q_stricmp(local_424,"type");
              if (tmp_i5 != 0) {
                tmp_i5 = Q_stricmp(local_424,"mapposition_x");
                if (tmp_i5 == 0) {
                  tmp_pu8 = &g_dat_003babdc + g_dat_003bab6c * 0x80;
                }
                else {
                  tmp_i5 = Q_stricmp(local_424,"mapposition_y");
                  if (tmp_i5 != 0) goto LAB_00021510;
                  tmp_pu8 = &g_dat_003babe0 + g_dat_003bab6c * 0x80;
                }
                tmp_i5 = PC_Float_Parse(tmp_i4,tmp_pu8);
                goto joined_r0x0002191f;
              }
              tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
              if (tmp_i5 == 0) break;
              tmp_pc7 = strstr(local_424,"wolfsp");
              if (tmp_pc7 != (char *)0x0) {
                *(uint *)(&g_dat_003bab7c + g_dat_003bab6c * 0x80) =
                     *(uint *)(&g_dat_003bab7c + g_dat_003bab6c * 0x80) | 1;
              }
              tmp_pc7 = strstr(local_424,"wolflms");
              if (tmp_pc7 != (char *)0x0) {
                *(uint *)(&g_dat_003bab7c + g_dat_003bab6c * 0x80) =
                     *(uint *)(&g_dat_003bab7c + g_dat_003bab6c * 0x80) | 0x20;
              }
              tmp_pc7 = strstr(local_424,"wolfmp");
              if (tmp_pc7 != (char *)0x0) {
                *(uint *)(&g_dat_003bab7c + g_dat_003bab6c * 0x80) =
                     *(uint *)(&g_dat_003bab7c + g_dat_003bab6c * 0x80) | 4;
              }
              tmp_pc7 = strstr(local_424,"wolfsw");
              if (tmp_pc7 != (char *)0x0) {
                *(uint *)(&g_dat_003bab7c + g_dat_003bab6c * 0x80) =
                     *(uint *)(&g_dat_003bab7c + g_dat_003bab6c * 0x80) | 8;
              }
              goto LAB_00021510;
            }
            tmp_pu8 = &g_dat_003babd0 + g_dat_003bab6c * 0x80;
LAB_0002178a:
            tmp_i5 = PC_Int_Parse(tmp_i4,tmp_pu8);
          } while (tmp_i5 != 0);
LAB_000215ff:
          tmp_u6 = va("^1unexpected end of file inside: %s\n",&local_8b4);
          trap_Print(tmp_u6);
        }
LAB_00021620:
        trap_PC_FreeSource(tmp_i4);
      }
LAB_00021628:
      local_8d8 = local_8d8 + 1;
      local_8cc = local_8cc + tmp_u1;
    } while (local_8d8 != tmp_i2);
  }
  qsort(&g_dat_003bab70,g_dat_003bab6c,0x80,UI_SortArenas);
  return;
}

uint8_t * UI_FindMapInfoByMapname(uint32_t param_1)

{
  int tmp_i1;
  int tmp_i2;
  
  if (g_dat_003bab6c == 0) {
    UI_LoadArenas();
  }
  tmp_i2 = 0;
  if (0 < g_dat_003bab6c) {
    do {
      tmp_i1 = Q_stricmp(*(uint32_t *)(&g_dat_003bab74 + tmp_i2 * 0x80),param_1);
      if (tmp_i1 == 0) {
        return &g_dat_003bab70 + tmp_i2 * 0x80;
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 < g_dat_003bab6c);
  }
  return (uint8_t *)0x0;
}

uint32_t UI_DescriptionForCampaign(void)

{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  int local_420;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x219fe;
  trap_GetConfigString(0,local_41c,0x400);
  tmp_u1 = Info_ValueForKey(local_41c,"mapname");
  if (0 < g_dat_003cab70) {
    tmp_pu4 = &uiInfo;
    tmp_i3 = 0;
    local_420 = 0;
    tmp_i2 = g_dat_003cab70;
    do {
      if (tmp_i3 < (int)tmp_pu4[0xcb32]) {
        do {
          tmp_i2 = Q_stricmp(tmp_u1,*(uint32_t *)tmp_pu4[tmp_i3 + 0xcb33]);
          if (tmp_i2 == 0) {
            return *(uint32_t *)(&g_dat_003cab7c + local_420 * 0x74);
          }
          tmp_i3 = tmp_i3 + 1;
          tmp_i2 = g_dat_003cab70;
        } while (tmp_i3 < (int)tmp_pu4[0xcb32]);
      }
      local_420 = local_420 + 1;
      tmp_pu4 = tmp_pu4 + 0x1d;
    } while (local_420 < tmp_i2);
  }
  return 0;
}

uint32_t UI_NameForCampaign(void)

{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  int local_420;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x21ace;
  trap_GetConfigString(0,local_41c,0x400);
  tmp_u1 = Info_ValueForKey(local_41c,"mapname");
  if (0 < g_dat_003cab70) {
    tmp_pu4 = &uiInfo;
    tmp_i3 = 0;
    local_420 = 0;
    tmp_i2 = g_dat_003cab70;
    do {
      if (tmp_i3 < (int)tmp_pu4[0xcb32]) {
        do {
          tmp_i2 = Q_stricmp(tmp_u1,*(uint32_t *)tmp_pu4[tmp_i3 + 0xcb33]);
          if (tmp_i2 == 0) {
            return (&g_dat_003cab78)[local_420 * 0x1d];
          }
          tmp_i3 = tmp_i3 + 1;
          tmp_i2 = g_dat_003cab70;
        } while (tmp_i3 < (int)tmp_pu4[0xcb32]);
      }
      local_420 = local_420 + 1;
      tmp_pu4 = tmp_pu4 + 0x1d;
    } while (local_420 < tmp_i2);
  }
  return 0;
}

int UI_FindCampaignInCampaignList(int param_1)

{
  int tmp_i1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  
  if ((param_1 != 0) && (0 < g_dat_003cab70)) {
    tmp_pu2 = (uint32_t *)&g_dat_003cab74;
    tmp_i3 = 0;
    do {
      tmp_i1 = Q_stricmp(*tmp_pu2,param_1);
      if (tmp_i1 == 0) {
        return tmp_i3;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu2 = tmp_pu2 + 0x1d;
    } while (tmp_i3 < g_dat_003cab70);
  }
  return -1;
}

void UI_LoadCampaigns(void)

{
  uint tmp_u1;
  int tmp_i2;
  int tmp_i3;
  size_t tmp_s4;
  int tmp_i5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint32_t *tmp_pu8;
  __int32_t **pp_Var9;
  int tmp_i10;
  char *tmp_pc11;
  char *tmp_pc12;
  uint tmp_u13;
  char tmp_c14;
  byte *tmp_pb15;
  int *tmp_pi16;
  char *tmp_pc17;
  byte tmp_b18;
  size_t local_964;
  int local_95c;
  char *local_958;
  uint32_t local_934;
  uint32_t local_930;
  uint32_t local_92c;
  char local_928 [116];
  char local_8b4 [128];
  char local_834 [1024];
  uint8_t local_434 [12];
  uint32_t local_428;
  char local_424;
  char acStack_423 [1039];
  uint32_t uStack_14;
  
  tmp_b18 = 0;
  uStack_14 = 0x21c27;
  g_dat_003cab70 = 0;
  local_958 = local_834;
  memset(&g_dat_003cab74,0,0xe800);
  tmp_i3 = trap_FS_GetFileList("scripts",".campaign",local_958,0x400);
  if ((0 < tmp_i3) && ((int)g_dat_003cab70 < 0x200)) {
    local_95c = 0;
    do {
      tmp_s4 = strlen(local_958);
      local_934 = 0x69726373;
      local_930 = 0x2f737470;
      tmp_u1 = tmp_s4 + 1;
      tmp_u13 = tmp_u1;
      tmp_pc12 = local_958;
      tmp_pc11 = (char *)&local_92c;
      if ((7 < tmp_u1) && (((uint)&local_92c & 4) != 0)) {
        local_92c = *(uint32_t *)local_958;
        tmp_pc12 = local_958 + 4;
        tmp_u13 = tmp_s4 - 3;
        tmp_pc11 = local_928;
      }
      for (; tmp_u13 != 0; tmp_u13 = tmp_u13 - 1) {
        *tmp_pc11 = *tmp_pc12;
        tmp_pc12 = tmp_pc12 + (uint)tmp_b18 * -2 + 1;
        tmp_pc11 = tmp_pc11 + (uint)tmp_b18 * -2 + 1;
      }
      tmp_i5 = trap_PC_LoadSource(&local_934);
      if (tmp_i5 == 0) {
        tmp_u7 = va("^1file not found: %s\n",&local_934);
        trap_Print(tmp_u7);
      }
      else {
        tmp_i6 = trap_PC_ReadToken(tmp_i5,local_434);
        if ((tmp_i6 == 0) || (local_424 != '{')) {
LAB_00021f0e:
          trap_PC_FreeSource(tmp_i5);
        }
        else {
LAB_00021d7c:
          do {
            tmp_i6 = trap_PC_ReadToken(tmp_i5,local_434);
            tmp_s4 = g_dat_003cab70;
            if (tmp_i6 == 0) goto LAB_00021f0e;
            if (local_424 != '}') {
              tmp_pc12 = &local_424;
              tmp_i6 = Q_stricmp(tmp_pc12,"shortname");
              if (tmp_i6 == 0) {
                tmp_pu8 = (uint32_t *)(&g_dat_003cab74 + g_dat_003cab70 * 0x74);
LAB_00021e95:
                tmp_i6 = PC_String_Parse(tmp_i5,tmp_pu8);
                if (tmp_i6 != 0) goto LAB_00021d7c;
              }
              else {
                tmp_i6 = Q_stricmp(tmp_pc12,"name");
                if (tmp_i6 == 0) {
                  tmp_pu8 = &g_dat_003cab78 + g_dat_003cab70 * 0x1d;
                  goto LAB_00021e95;
                }
                tmp_i6 = Q_stricmp(tmp_pc12,"description");
                if (tmp_i6 == 0) {
                  tmp_pu8 = (uint32_t *)(&g_dat_003cab7c + g_dat_003cab70 * 0x74);
                  goto LAB_00021e95;
                }
                tmp_i6 = Q_stricmp(tmp_pc12,"image");
                if (tmp_i6 == 0) {
                  tmp_i6 = PC_String_Parse(tmp_i5,&g_dat_003cabc8 + g_dat_003cab70 * 0x74);
                  if (tmp_i6 != 0) {
                    (&g_dat_003cabd0)[g_dat_003cab70 * 0x1d] = 0xffffffff;
                    goto LAB_00021d7c;
                  }
                }
                else {
                  tmp_i6 = Q_stricmp(tmp_pc12,"initial");
                  if (tmp_i6 == 0) {
                    *(uint32_t *)(&g_dat_003cabdc + g_dat_003cab70 * 0x74) = 1;
                    goto LAB_00021d7c;
                  }
                  tmp_i6 = Q_stricmp(tmp_pc12,"next");
                  if (tmp_i6 == 0) {
                    tmp_pu8 = (uint32_t *)(&g_dat_003cab80 + g_dat_003cab70 * 0x74);
                    goto LAB_00021e95;
                  }
                  tmp_i6 = Q_stricmp(tmp_pc12,"type");
                  if (tmp_i6 == 0) {
                    tmp_i6 = trap_PC_ReadToken(tmp_i5,local_434);
                    if (tmp_i6 != 0) {
                      tmp_pc11 = strstr(tmp_pc12,"wolfsp");
                      if (tmp_pc11 != (char *)0x0) {
                        *(uint *)(&g_dat_003cabe4 + g_dat_003cab70 * 0x74) =
                             *(uint *)(&g_dat_003cabe4 + g_dat_003cab70 * 0x74) | 1;
                      }
                      tmp_pc11 = strstr(tmp_pc12,"wolfmp");
                      if (tmp_pc11 != (char *)0x0) {
                        *(uint *)(&g_dat_003cabe4 + g_dat_003cab70 * 0x74) =
                             *(uint *)(&g_dat_003cabe4 + g_dat_003cab70 * 0x74) | 4;
                      }
                      tmp_pc11 = strstr(tmp_pc12,"wolfsw");
                      if (tmp_pc11 != (char *)0x0) {
                        *(uint *)(&g_dat_003cabe4 + g_dat_003cab70 * 0x74) =
                             *(uint *)(&g_dat_003cabe4 + g_dat_003cab70 * 0x74) | 8;
                      }
                      tmp_pc12 = strstr(tmp_pc12,"wolflms");
                      if (tmp_pc12 != (char *)0x0) {
                        *(uint *)(&g_dat_003cabe4 + g_dat_003cab70 * 0x74) =
                             *(uint *)(&g_dat_003cabe4 + g_dat_003cab70 * 0x74) | 0x20;
                      }
                      goto LAB_00021d7c;
                    }
                  }
                  else {
                    tmp_i6 = Q_stricmp(tmp_pc12,&g_dat_00055663);
                    if (tmp_i6 == 0) {
                      tmp_i6 = trap_PC_ReadToken(tmp_i5,local_434);
                      if (tmp_i6 != 0) {
                        *(uint32_t *)(&g_dat_003cab88 + g_dat_003cab70 * 0x74) = 0;
LAB_00022442:
                        tmp_c14 = *tmp_pc12;
                        if (tmp_c14 != '\0') {
                          tmp_pc11 = local_8b4;
                          tmp_pc17 = local_8b4;
                          if (tmp_c14 == ';') {
LAB_00022474:
                            tmp_pc12 = tmp_pc12 + 1;
                          }
                          else {
                            do {
                              tmp_pc17 = tmp_pc11 + 1;
                              tmp_pc12 = tmp_pc12 + 1;
                              *tmp_pc11 = tmp_c14;
                              tmp_c14 = *tmp_pc12;
                              if (tmp_c14 == ';') break;
                              tmp_pc11 = tmp_pc17;
                            } while (tmp_c14 != '\0');
                            if (tmp_c14 != '\0') goto LAB_00022474;
                          }
                          *tmp_pc17 = '\0';
                          tmp_i6 = 0;
                          if (0 < g_dat_003bab6c) {
                            do {
                              tmp_i10 = Q_stricmp(*(uint32_t *)(&g_dat_003bab74 + tmp_i6 * 0x80),
                                                 local_8b4);
                              tmp_s4 = g_dat_003cab70;
                              if (tmp_i10 == 0) {
                                tmp_i10 = *(int *)(&g_dat_003cab88 + g_dat_003cab70 * 0x74);
                                *(int *)(&g_dat_003cab88 + g_dat_003cab70 * 0x74) = tmp_i10 + 1;
                                (&g_dat_00397ecc)[tmp_i10 + 0xcb30 + tmp_s4 * 0x1d] =
                                     &g_dat_003bab70 + tmp_i6 * 0x80;
                                break;
                              }
                              tmp_i6 = tmp_i6 + 1;
                            } while (tmp_i6 < g_dat_003bab6c);
                          }
                          goto LAB_00022442;
                        }
                        goto LAB_00021d7c;
                      }
                    }
                    else {
                      tmp_i6 = Q_stricmp(tmp_pc12,"maptc");
                      if (tmp_i6 != 0) goto LAB_00021d7c;
                      tmp_i6 = trap_PC_ReadToken(tmp_i5,local_434);
                      if (tmp_i6 != 0) {
                        *(uint32_t *)(&g_dat_003cabb4 + g_dat_003cab70 * 0x74) = local_428;
                        tmp_i6 = trap_PC_ReadToken(tmp_i5,local_434);
                        if (tmp_i6 != 0) {
                          tmp_i6 = g_dat_003cab70 * 0x74;
                          *(uint32_t *)(&g_dat_003cabb8 + tmp_i6) = local_428;
                          *(float *)(&g_dat_003cabbc + tmp_i6) =
                               *(float *)(&g_dat_003cabb4 + tmp_i6) + 650.0;
                          *(float *)(&g_dat_003cabc0 + tmp_i6) =
                               *(float *)(&g_dat_003cabb8 + tmp_i6) + 650.0;
                          goto LAB_00021d7c;
                        }
                      }
                    }
                  }
                }
              }
              tmp_u7 = va("^1unexpected end of file inside: %s\n",&local_934);
              trap_Print(tmp_u7);
              trap_PC_FreeSource(tmp_i5);
              goto LAB_00021cd9;
            }
            if ((*(int *)(&g_dat_003cabdc + g_dat_003cab70 * 0x74) != 0) &&
               (((&g_dat_003cabe4)[g_dat_003cab70 * 0x74] & 1) != 0)) {
              (&g_dat_003cabd4)[g_dat_003cab70 * 0x1d] = 1;
            }
            tmp_i6 = g_dat_003cab70 * 0x1d;
            g_dat_003cab70 = g_dat_003cab70 + 1;
            (&g_dat_003cabcc)[tmp_i6] = 0xffffffff;
            (&g_dat_003cabd0)[tmp_s4 * 0x1d] = 0xffffffff;
            tmp_i6 = trap_PC_ReadToken(tmp_i5,local_434);
            if (tmp_i6 == 0) goto LAB_00021f0e;
          } while (local_424 == '{');
          tmp_u7 = va("^1unexpected token \'%s\' inside: %s\n",&local_424,&local_934);
          trap_Print(tmp_u7);
          trap_PC_FreeSource(tmp_i5);
        }
      }
LAB_00021cd9:
      local_95c = local_95c + 1;
      local_958 = local_958 + tmp_u1;
    } while ((local_95c != tmp_i3) && ((int)g_dat_003cab70 < 0x200));
  }
  tmp_i3 = UI_OutOfMemory();
  if (tmp_i3 != 0) {
    trap_Print("^3WARNING: not anough memory in pool to load all campaigns\n");
  }
  tmp_s4 = g_dat_003cab70;
  if ((int)g_dat_003cab70 < 1) {
    local_964 = 0;
  }
  else {
    tmp_pb15 = &g_dat_003cabe4;
    local_964 = 0;
    do {
      if (((*tmp_pb15 & 1) != 0) && (*(int *)(tmp_pb15 + -8) != 0)) {
        (&g_dat_003cabe0)[local_964 * 0x1d] = 0;
        break;
      }
      local_964 = local_964 + 1;
      tmp_pb15 = tmp_pb15 + 0x74;
    } while (local_964 != g_dat_003cab70);
    if (0x1ff < (int)local_964) goto LAB_0002211c;
  }
  tmp_i3 = *(int *)(&g_dat_003cab80 + local_964 * 0x74);
  if ((tmp_i3 != 0) && (0 < (int)tmp_s4)) {
    while( true ) {
      tmp_s4 = 0;
      tmp_pu8 = (uint32_t *)&g_dat_003cab74;
      while (tmp_i5 = Q_stricmp(*tmp_pu8,tmp_i3), tmp_i5 != 0) {
        tmp_s4 = tmp_s4 + 1;
        tmp_pu8 = tmp_pu8 + 0x1d;
        if ((int)g_dat_003cab70 <= (int)tmp_s4) goto LAB_0002211c;
      }
      if (tmp_s4 == 0xffffffff) break;
      (&g_dat_003cabe0)[tmp_s4 * 0x1d] = (&g_dat_003cabe0)[local_964 * 0x1d] + 1;
      if (((0x1ff < (int)tmp_s4) || (tmp_i3 = *(int *)(&g_dat_003cab80 + tmp_s4 * 0x74), tmp_i3 == 0)) ||
         (local_964 = tmp_s4, (int)g_dat_003cab70 < 1)) break;
    }
  }
LAB_0002211c:
  tmp_u7 = va("profiles/%s/campaign.dat",0x396610);
  BG_LoadCampaignSave(tmp_u7,&g_dat_003d9374,0x396610);
  tmp_i3 = _DAT_003d937c;
  tmp_s4 = g_dat_003cab70;
  if (0 < (int)g_dat_003cab70) {
    tmp_pu8 = (uint32_t *)&g_dat_003cab74;
    tmp_i5 = g_dat_003cab70 * 0x74;
    tmp_i6 = _DAT_003d937c * 0x30;
    do {
      tmp_pc12 = (char *)*tmp_pu8;
      tmp_c14 = *tmp_pc12;
      if (tmp_c14 == '\0') {
        tmp_i10 = 0;
      }
      else {
        pp_Var9 = __ctype_tolower_loc();
        tmp_i10 = 0;
        tmp_pc11 = tmp_pc12;
        do {
          tmp_i10 = tmp_i10 + (int)(tmp_pc11 + (0x77 - (int)tmp_pc12)) * (*pp_Var9)[tmp_c14];
          tmp_c14 = tmp_pc11[1];
          tmp_pc11 = tmp_pc11 + 1;
        } while (tmp_c14 != '\0');
      }
      if (0 < tmp_i3) {
        tmp_pi16 = (int *)&g_dat_003d9384;
        do {
          while (*tmp_pi16 != tmp_i10) {
            tmp_pi16 = tmp_pi16 + 0xc;
            if (tmp_pi16 == (int *)(&g_dat_003d9384 + tmp_i6)) goto LAB_00022242;
          }
          tmp_pu8[0x18] = 1;
          tmp_i2 = tmp_pi16[1];
          tmp_pu8[0x14] = tmp_pi16;
          tmp_pi16 = tmp_pi16 + 0xc;
          tmp_pu8[0x19] = tmp_i2;
        } while (tmp_pi16 != (int *)(&g_dat_003d9384 + tmp_i6));
      }
LAB_00022242:
      tmp_pu8 = tmp_pu8 + 0x1d;
    } while (tmp_pu8 != (uint32_t *)(&g_dat_003cab74 + tmp_i5));
  }
  qsort(&g_dat_003cab74,tmp_s4,0x74,UI_SortCampaigns);
  return;
}

void UI_LoadPanel_RenderHeaderText(int param_1)

{
  char *tmp_pc1;
  char local_1018 [1024];
  uint local_c18 [772];
  
  trap_GetClientState(local_c18);
  trap_Cvar_VariableStringBuffer("cl_downloadName",local_1018,0x400);
  tmp_pc1 = "CONNECTING...";
  if (((local_c18[0] & 0xfffffffb) == 1) && (local_1018[0] != '\0')) {
    tmp_pc1 = "DOWNLOADING...";
  }
  *(char **)(param_1 + 4) = tmp_pc1;
  BG_PanelButtonsRender_Text(param_1);
  return;
}

void UI_LoadPanel_RenderDownloadingBar_part_0(void)

{
  float tmp_f1;
  float tmp_f2;
  long double tmp_l3;
  long double tmp_l4;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_10 = 0x22698;
  tmp_l3 = (long double)trap_Cvar_VariableValue("cl_downloadSize");
  tmp_l4 = (long double)trap_Cvar_VariableValue("cl_downloadCount");
  if ((int)ROUND(tmp_l3) != 0) {
    tmp_f1 = (float)(int)ROUND(tmp_l4) / (float)(int)ROUND(tmp_l3);
    if (tmp_f1 < 0.0) {
      tmp_f1 = 0.0;
    }
    else if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    local_1c = 0x3f800000;
    local_18 = 0x3f800000;
    local_14 = 0x3f800000;
    local_10 = 0x3e800000;
    trap_R_SetColor(&local_1c);
    trap_R_DrawStretchPic
              (((float)g_dat_003b7ef4 / 640.0) * 0.0,g_dat_00397fd0 * 468.0,
               ((float)g_dat_003b7ef4 / 640.0) * 640.0,g_dat_00397fd0 * 12.0,0,0,0,0x3f800000,
               g_dat_003b7f10);
    trap_R_SetColor(0);
    trap_R_SetColor(colorLtGrey);
    trap_R_DrawStretchPic
              (((float)g_dat_003b7ef4 / 640.0) * 0.0,g_dat_00397fd0 * 468.0,
               ((float)g_dat_003b7ef4 / 640.0) * 640.0,g_dat_00397fd0 * 12.0,0,0,0,0x3f800000,
               g_dat_003b7f10);
    trap_R_SetColor(0);
    local_1c = 0x3f800000;
    local_18 = 0x3f800000;
    local_14 = 0x3f800000;
    local_10 = 0x3e800000;
    if (tmp_f1 <= 1.0) {
      tmp_f2 = 0.0;
      if (0.0 <= tmp_f1) {
        tmp_f2 = tmp_f1;
      }
    }
    else {
      tmp_f2 = 1.0;
    }
    trap_R_SetColor(&local_1c);
    tmp_f1 = (float)g_dat_003b7ef4 / 640.0;
    trap_R_DrawStretchPic
              (tmp_f1 + tmp_f1,g_dat_00397fd0 * 469.0,tmp_f1 * 638.0,g_dat_00397fd0 * 10.0,0,0,0,0x3f800000
               ,g_dat_003b7f10);
    trap_R_SetColor(0);
    trap_R_SetColor(colorGreen);
    tmp_f1 = (float)g_dat_003b7ef4 / 640.0;
    trap_R_DrawStretchPic
              (tmp_f1 + tmp_f1,g_dat_00397fd0 * 469.0,tmp_f2 * 638.0 * tmp_f1,g_dat_00397fd0 * 10.0,0,0,0,
               0x3f800000,g_dat_003b7f10);
    trap_R_SetColor(0);
  }
  return;
}

void AdjustFrom640FullScreen(float *param_1,float *param_2,float *param_3,float *param_4)

{
  float tmp_f1;
  
  tmp_f1 = (float)g_dat_003b7ef4;
  *param_1 = *param_1 * (tmp_f1 / 640.0);
  *param_2 = *param_2 * g_dat_00397fd0;
  *param_3 = (tmp_f1 / 640.0) * *param_3;
  *param_4 = *param_4 * g_dat_00397fd0;
  return;
}

void FillRectFullScreen(float param_1,float param_2,float param_3,float param_4,uint32_t param_5)

{
  trap_R_SetColor(param_5);
  trap_R_DrawStretchPic
            (((float)g_dat_003b7ef4 / 640.0) * param_1,g_dat_00397fd0 * param_2,
             param_3 * ((float)g_dat_003b7ef4 / 640.0),param_4 * g_dat_00397fd0,0,0,0,0x3f800000,
             g_dat_003b7f10);
  trap_R_SetColor(0);
  return;
}

void UI_DrawLoadPanel(uint32_t param_1,uint32_t param_2,int param_3)

{
  float tmp_f1;
  uint32_t tmp_u2;
  long double tmp_l3;
  
  if ((float)(int)DC[0x800d] / (float)(int)DC[0x800e] != 1.3333334) {
    tmp_l3 = (long double)Cui_WideXoffset();
    tmp_f1 = (float)(tmp_l3 * (long double)(float)DC[0x45]);
    tmp_u2 = (*(void *)*DC)("gfx/2d/backtile");
    trap_R_DrawStretchPic(0,0,tmp_f1,(float)(int)DC[0x800e],0,0,0x3f800000,0x3f800000,tmp_u2);
    tmp_u2 = (*(void *)*DC)("gfx/2d/backtile");
    trap_R_DrawStretchPic
              ((float)(int)DC[0x800d] - tmp_f1,0,tmp_f1,(float)(int)DC[0x800e],0,0,0x3f800000,
               0x3f800000,tmp_u2);
  }
  if (inside_9118 == 0) {
    connect_ownerdraw = param_2;
    inside_9118 = 1;
    if (bg_loadscreeninited == 0) {
      trap_R_RegisterFont("ariblk",0x1b,bg_loadscreenfont1);
      trap_R_RegisterFont("courbd",0x1e,bg_loadscreenfont2);
      BG_PanelButtonsSetup(loadpanelButtons);
      tmp_l3 = (long double)Cui_WideXoffset();
      C_PanelButtonsSetup(loadpanelButtons,(float)tmp_l3);
      bg_loadscreeninited = 1;
    }
    trap_R_SetColor(colorBlack);
    trap_R_DrawStretchPic
              (((float)g_dat_003b7ef4 / 640.0) * 0.0,g_dat_00397fd0 * 0.0,
               ((float)g_dat_003b7ef4 / 640.0) * 640.0,g_dat_00397fd0 * 480.0,0,0,0,0x3f800000,
               g_dat_003b7f10);
    trap_R_SetColor(0);
    BG_PanelButtonsRender(loadpanelButtons);
    if ((param_3 == 0) &&
       (tmp_l3 = (long double)trap_Cvar_VariableValue("ui_connecting"), tmp_l3 != (long double)0)) {
      trap_Cvar_Set("ui_connecting","0");
    }
    inside_9118 = 0;
    return;
  }
  if ((param_3 == 0) &&
     (tmp_l3 = (long double)trap_Cvar_VariableValue("ui_connecting"), tmp_l3 != (long double)0)) {
    trap_Cvar_Set("ui_connecting","0");
  }
  return;
}

bool Downloading(void)

{
  char local_1018 [1024];
  uint local_c18 [772];
  uint32_t uStack_8;
  
  uStack_8 = 0x22e26;
  trap_GetClientState(local_c18);
  trap_Cvar_VariableStringBuffer("cl_downloadName",local_1018,0x400);
  return (local_c18[0] & 0xfffffffb) == 1 && local_1018[0] != '\0';
}

void CG_FilledBar(float param_1,float param_2,float param_3,float param_4,uint32_t param_5,
                 uint32_t param_6,uint32_t *param_7,float param_8,uint param_9)

{
  float tmp_f1;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  tmp_f1 = 1.0;
  local_1c = 0x3f800000;
  local_18 = 0x3f800000;
  local_14 = 0x3f800000;
  local_10 = 0x3e800000;
  if ((param_8 <= 1.0) && (tmp_f1 = 0.0, 0.0 <= param_8)) {
    tmp_f1 = param_8;
  }
  if ((param_9 & 0x10) != 0) {
    if (param_7 != (uint32_t *)0x0) {
      local_1c = *param_7;
      local_18 = param_7[1];
      local_14 = param_7[2];
      local_10 = param_7[3];
    }
    trap_R_SetColor(&local_1c);
    trap_R_DrawStretchPic
              (((float)g_dat_003b7ef4 / 640.0) * param_1,param_2 * g_dat_00397fd0,
               param_3 * ((float)g_dat_003b7ef4 / 640.0),param_4 * g_dat_00397fd0,0,0,0,0x3f800000,
               g_dat_003b7f10);
    trap_R_SetColor(0);
    if ((param_9 & 0x40) == 0) {
      param_1 = param_1 + 2.0;
      param_2 = param_2 + 2.0;
      param_3 = param_3 - 4.0;
      param_4 = param_4 - 4.0;
    }
  }
  trap_R_SetColor(param_5);
  trap_R_DrawStretchPic
            (((float)g_dat_003b7ef4 / 640.0) * param_1,g_dat_00397fd0 * param_2,
             param_3 * tmp_f1 * ((float)g_dat_003b7ef4 / 640.0),param_4 * g_dat_00397fd0,0,0,0,0x3f800000
             ,g_dat_003b7f10);
  trap_R_SetColor(0);
  return;
}

void UI_LoadPanel_RenderDownloadingBar(void)

{
  int tmp_i1;
  
  tmp_i1 = Downloading();
  if (tmp_i1 == 0) {
    return;
  }
  UI_LoadPanel_RenderDownloadingBar_part_0();
  return;
}

void UI_DownloadInfo(uint32_t param_1)

{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  long double tmp_l6;
  uint32_t local_130;
  uint8_t local_11c [64];
  uint8_t local_dc [64];
  uint8_t local_9c [64];
  uint8_t local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0x230b9;
  tmp_l6 = (long double)trap_Cvar_VariableValue("cl_downloadSize");
  tmp_i4 = (int)ROUND(tmp_l6);
  tmp_l6 = (long double)trap_Cvar_VariableValue("cl_downloadCount");
  tmp_i1 = (int)ROUND(tmp_l6);
  tmp_l6 = (long double)trap_Cvar_VariableValue("cl_downloadTime");
  local_130 = param_1;
  if (0 < tmp_i4) {
    local_130 = va(&g_dat_0005579e,(int)ROUND(((float)tmp_i1 * 100.0) / (float)tmp_i4));
  }
  UI_ReadableSize(local_11c,0x40,tmp_i1);
  UI_ReadableSize(local_dc,0x40,tmp_i4);
  if (((int)ROUND(tmp_l6) == 0) || (tmp_i1 < 0x1000)) {
    va("Estimating download time for \'%s\'...",param_1);
    return;
  }
  tmp_i3 = g_dat_00397fdc - (int)ROUND(tmp_l6);
  if (tmp_i3 + 999U < 1999) {
    UI_ReadableSize(local_9c,0x40,0);
    tmp_i3 = 0;
  }
  else {
    tmp_i3 = tmp_i1 / (tmp_i3 / 1000);
    UI_ReadableSize(local_9c,0x40,tmp_i3);
    if ((tmp_i3 != 0) && (tmp_i4 != 0)) {
      tmp_pi2 = &tleEstimates_9153;
      tmp_i5 = tmp_i4;
      if (tmp_i4 < 0) {
        tmp_i5 = tmp_i4 + 0x3ff;
      }
      (&tleEstimates_9153)[tleIndex_9154] =
           ((tmp_i1 >> 10) * (tmp_i4 / tmp_i3)) / -(tmp_i5 >> 10) + tmp_i4 / tmp_i3;
      tleIndex_9154 = tleIndex_9154 + 1;
      if (0x4f < tleIndex_9154) {
        tleIndex_9154 = 0;
      }
      tmp_i4 = 0;
      do {
        tmp_i1 = *tmp_pi2;
        tmp_pi2 = tmp_pi2 + 1;
        tmp_i4 = tmp_i4 + tmp_i1;
      } while (tmp_pi2 != (int *)loadpanelButtons);
      UI_PrintTime(local_5c,0x40,tmp_i4 / 0x50);
      goto joined_r0x00023362;
    }
  }
  local_5c[0] = 0;
joined_r0x00023362:
  if (tmp_i3 != 0) {
    va("File: \'%s\'\nSpeed: %s/s\n\n^0%s -- %s remaining^7",param_1,local_9c,local_130,local_5c);
    return;
  }
  va("\n\nEstimating download time for \'%s\'...",param_1);
  return;
}

void UI_LoadPanel_RenderLoadingText(int param_1)

{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  char *tmp_pc6;
  char tmp_c7;
  char *tmp_pc8;
  long double tmp_l9;
  float local_2a60;
  char local_2a34 [1024];
  char local_2634 [1024];
  char local_2234;
  char local_2233 [2559];
  uint local_1834;
  uint32_t local_1830;
  uint8_t local_1828 [2048];
  char local_1028 [1024];
  uint local_c28 [773];
  uint32_t uStack_14;
  
  uStack_14 = 0x233b9;
  tmp_pc8 = &local_2234;
  trap_GetClientState(&local_1834);
  Com_sprintf(tmp_pc8,0xa00,"Connecting to: %s",local_1828);
  trap_Cvar_VariableStringBuffer("cl_downloadName",local_2a34,0x400);
  if (connect_ownerdraw != 0) goto LAB_0002343d;
  tmp_l9 = (long double)trap_Cvar_VariableValue("ui_connecting");
  if (tmp_l9 == (long double)0) {
    if (local_1834 == 3) {
      tmp_pc6 = (char *)va("Awaiting connection...%i",local_1830);
    }
    else if (local_1834 < 4) {
      if (local_1834 == 1) goto LAB_0002360a;
LAB_0002384a:
      tmp_pc6 = "";
    }
    else if (local_1834 == 4) {
      tmp_pc6 = (char *)va("Awaiting challenge...%i",local_1830);
    }
    else {
      if (local_1834 != 5) goto LAB_0002384a;
LAB_0002360a:
      if ((local_2a34[0] != '\0') || (tmp_pc6 = "Awaiting gamestate...", local_1834 == 1))
      goto LAB_0002361e;
    }
  }
  else {
    tmp_l9 = (long double)trap_Cvar_VariableValue("ui_dl_running");
    if (tmp_l9 == (long double)0) goto LAB_0002384a;
LAB_0002361e:
    tmp_pc6 = (char *)UI_DownloadInfo(local_2a34);
  }
  tmp_u5 = va(&g_dat_0005580a,tmp_pc6);
  Q_strcat(tmp_pc8,0xa00,tmp_u5);
  if ((local_1834 < 5) && (local_1028[0] != '\0')) {
    tmp_u5 = va(&g_dat_0005580a,local_1028);
    Q_strcat(tmp_pc8,0xa00,tmp_u5);
  }
LAB_0002343d:
  trap_GetClientState(local_c28);
  trap_Cvar_VariableStringBuffer("cl_downloadName",local_2634,0x400);
  if (((local_c28[0] & 0xfffffffb) == 1) && (local_2634[0] != '\0')) {
    tmp_u5 = UI_Cvar_VariableString("com_missingFiles");
    Com_sprintf(tmp_pc8,0xa00,"Connecting to: %s\n\n\n\nMissing paks:\n%s",local_1828,tmp_u5);
  }
  BG_FitTextToWidth_Ext
            (tmp_pc8,**(uint32_t **)(param_1 + 0x38),*(uint32_t *)(param_1 + 0x10),0xa00,
             (*(uint32_t **)(param_1 + 0x38))[8]);
  local_2a60 = *(float *)(param_1 + 0xc) + 12.0;
  tmp_pc6 = tmp_pc8;
  while (tmp_c7 = *tmp_pc6, tmp_pc4 = tmp_pc6, tmp_c7 != '\0') {
    while (tmp_c7 != '\n') {
      tmp_pc4 = tmp_pc4 + 1;
      tmp_c7 = *tmp_pc4;
      if (tmp_c7 == '\0') goto LAB_000234d8;
    }
    *tmp_pc4 = '\0';
    tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
    tmp_u5 = tmp_pu2[1];
    tmp_u3 = tmp_pu2[8];
    tmp_u1 = *tmp_pu2;
    tmp_l9 = (long double)Cui_WideXoffset();
    Text_Paint_Ext((float)tmp_l9,local_2a60,tmp_u1,tmp_u5,&colorWhite,tmp_pc6,0,0,0,tmp_u3);
    local_2a60 = local_2a60 + 8.0;
    tmp_pc6 = tmp_pc4 + 1;
  }
LAB_000234d8:
  trap_GetClientState(local_c28);
  trap_Cvar_VariableStringBuffer("cl_downloadName",local_2634,0x400);
  if (((local_c28[0] & 0xfffffffb) == 1) && (local_2634[0] != '\0')) {
    tmp_u5 = UI_DownloadInfo(local_2a34);
    Q_strncpyz(tmp_pc8,tmp_u5,0xa00);
    BG_FitTextToWidth_Ext(tmp_pc8,0x3e4ccccd,0x44200000,0xa00,bg_loadscreenfont2);
    trap_GetClientState(local_c28);
    trap_Cvar_VariableStringBuffer("cl_downloadName",local_2634,0x400);
    if (((local_c28[0] & 0xfffffffb) == 1) && (local_2634[0] != '\0')) {
      UI_LoadPanel_RenderDownloadingBar_part_0();
    }
    local_2a60 = 454.0;
    while (tmp_c7 = *tmp_pc8, tmp_pc6 = tmp_pc8, tmp_c7 != '\0') {
      while (tmp_c7 != '\n') {
        tmp_pc6 = tmp_pc6 + 1;
        tmp_c7 = *tmp_pc6;
        if (tmp_c7 == '\0') {
          return;
        }
      }
      *tmp_pc6 = '\0';
      tmp_l9 = (long double)Cui_WideXoffset();
      Text_Paint_Ext((float)tmp_l9,local_2a60,0x3e4ccccd,0x3e4ccccd,&colorWhite,tmp_pc8,0,0,0,
                     bg_loadscreenfont2);
      local_2a60 = local_2a60 + 8.0;
      tmp_pc8 = tmp_pc6 + 1;
    }
  }
  return;
}

void Text_SetActiveFont(uint32_t param_1)

{
  g_dat_003e7e2c = param_1;
  return;
}

long double UI_GetValue(void)

{
  return (long double)0;
}

uint UI_ServersQsortCompare_bis(int *param_1,int *param_2)

{
  uint tmp_u1;
  
  if (*(int *)(&g_dat_003e9078 + *param_1 * 4) < *(int *)(&g_dat_003e9078 + *param_2 * 4)) {
    return -(uint)(_DAT_003e13b4 == 0) | 1;
  }
  tmp_u1 = (uint)(*(int *)(&g_dat_003e9078 + *param_2 * 4) < *(int *)(&g_dat_003e9078 + *param_1 * 4));
  if (_DAT_003e13b4 != 0) {
    return -tmp_u1;
  }
  return tmp_u1;
}

void UI_GetTeamColor(void)

{
  return;
}

void UI_FeederAddItem(void)

{
  return;
}

void _UI_DrawSides(float param_1,uint32_t param_2,float param_3,uint32_t param_4,float param_5)

{
  float tmp_f1;
  
  UI_AdjustFrom640(&param_1,&param_2,&param_3,&param_4);
  tmp_f1 = param_5 * g_dat_00397fd4;
  trap_R_DrawStretchPic(param_1,param_2,tmp_f1,param_4,0,0,0,0,g_dat_003b7f10);
  trap_R_DrawStretchPic((param_1 + param_3) - tmp_f1,param_2,tmp_f1,param_4,0,0,0,0,g_dat_003b7f10);
  return;
}

void _UI_DrawTopBottom(uint32_t param_1,float param_2,uint32_t param_3,float param_4,
                      float param_5)

{
  float tmp_f1;
  
  UI_AdjustFrom640(&param_1,&param_2,&param_3,&param_4);
  tmp_f1 = param_5 * g_dat_00397fd0;
  trap_R_DrawStretchPic(param_1,param_2,param_3,tmp_f1,0,0,0,0,g_dat_003b7f10);
  trap_R_DrawStretchPic(param_1,(param_2 + param_4) - tmp_f1,param_3,tmp_f1,0,0,0,0,g_dat_003b7f10);
  return;
}

int Text_Width_Ext(byte *param_1,float param_2,size_t param_3,int param_4)

{
  byte tmp_b1;
  float tmp_f2;
  size_t tmp_s3;
  int tmp_i4;
  
  if (param_1 == (byte *)0x0) {
    tmp_f2 = 0.0;
  }
  else {
    tmp_s3 = strlen((char *)param_1);
    if (((int)tmp_s3 <= (int)param_3) || ((int)param_3 < 1)) {
      param_3 = tmp_s3;
    }
    tmp_f2 = 0.0;
    tmp_i4 = 0;
    do {
      while( true ) {
        tmp_b1 = *param_1;
        if ((tmp_b1 == 0) || ((int)param_3 <= tmp_i4)) goto LAB_00023b60;
        if ((tmp_b1 != 0x5e) || ((param_1[1] == 0 || (param_1[1] == 0x5e)))) break;
        param_1 = param_1 + 2;
        if (param_1 == (byte *)0x0) goto LAB_00023b60;
      }
      param_1 = param_1 + 1;
      tmp_i4 = tmp_i4 + 1;
      tmp_f2 = (float)*(int *)(param_4 + 0x10 + (uint)tmp_b1 * 0x50) + tmp_f2;
    } while (param_1 != (byte *)0x0);
  }
LAB_00023b60:
  return (int)ROUND(tmp_f2 * param_2 * *(float *)(param_4 + 0x5000));
}

int Multiline_Text_Width(byte *param_1,float param_2,size_t param_3)

{
  float tmp_f1;
  byte tmp_b2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  size_t tmp_s7;
  int tmp_i8;
  
  tmp_i6 = g_dat_003e7e2c;
  if (param_1 == (byte *)0x0) {
    tmp_f1 = *(float *)(&g_dat_0039cffc + g_dat_003e7e2c * 0x5044);
    tmp_f5 = 0.0;
  }
  else {
    tmp_s7 = strlen((char *)param_1);
    if (((int)tmp_s7 <= (int)param_3) || ((int)param_3 < 1)) {
      param_3 = tmp_s7;
    }
    tmp_i8 = 0;
    tmp_f1 = *(float *)(&g_dat_0039cffc + tmp_i6 * 0x5044);
    tmp_f5 = 0.0;
    tmp_f4 = tmp_f5;
    do {
      tmp_b2 = *param_1;
      if ((tmp_b2 == 0) || ((int)param_3 <= tmp_i8)) break;
      if (tmp_b2 == 0x5e) {
        if ((param_1[1] == 0) || (param_1[1] == 0x5e)) goto LAB_00023c27;
        param_1 = param_1 + 2;
      }
      else {
        if (tmp_b2 == 10) {
          tmp_f3 = tmp_f5 * param_2 * tmp_f1;
          tmp_f5 = 0.0;
          if (tmp_f4 < tmp_f3) {
            tmp_f4 = tmp_f3;
            tmp_f5 = 0.0;
          }
        }
        else {
LAB_00023c27:
          tmp_f5 = (float)*(int *)(&g_dat_0039800c + (uint)tmp_b2 * 0x50 + tmp_i6 * 0x5044) + tmp_f5;
        }
        param_1 = param_1 + 1;
        tmp_i8 = tmp_i8 + 1;
      }
    } while (param_1 != (byte *)0x0);
    if (0.0 < tmp_f4) {
      tmp_f1 = tmp_f5 * param_2 * tmp_f1;
      if (tmp_f1 <= tmp_f4) {
        tmp_f1 = tmp_f4;
      }
      return (int)ROUND(tmp_f1);
    }
  }
  return (int)ROUND(tmp_f5 * param_2 * tmp_f1);
}

int Text_Height_Ext(byte *param_1,float param_2,size_t param_3,int param_4)

{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  size_t tmp_s4;
  int tmp_i5;
  
  if (param_1 == (byte *)0x0) {
    tmp_f2 = 0.0;
  }
  else {
    tmp_s4 = strlen((char *)param_1);
    if (((int)tmp_s4 <= (int)param_3) || ((int)param_3 < 1)) {
      param_3 = tmp_s4;
    }
    tmp_f2 = 0.0;
    tmp_i5 = 0;
    do {
      while( true ) {
        tmp_b1 = *param_1;
        if ((tmp_b1 == 0) || ((int)param_3 <= tmp_i5)) goto LAB_00023de0;
        if ((tmp_b1 != 0x5e) || ((param_1[1] == 0 || (param_1[1] == 0x5e)))) break;
        param_1 = param_1 + 2;
        if (param_1 == (byte *)0x0) goto LAB_00023de0;
      }
      tmp_f3 = (float)*(int *)(param_4 + (uint)tmp_b1 * 0x50);
      if (tmp_f3 <= tmp_f2) {
        tmp_f3 = tmp_f2;
      }
      tmp_f2 = tmp_f3;
      param_1 = param_1 + 1;
      tmp_i5 = tmp_i5 + 1;
    } while (param_1 != (byte *)0x0);
  }
LAB_00023de0:
  return (int)ROUND(tmp_f2 * param_2 * *(float *)(param_4 + 0x5000));
}

int Multiline_Text_Height(byte *param_1,float param_2,size_t param_3)

{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  size_t tmp_s6;
  int tmp_i7;
  
  tmp_i5 = g_dat_003e7e2c;
  if (param_1 == (byte *)0x0) {
    tmp_f3 = 0.0;
  }
  else {
    tmp_s6 = strlen((char *)param_1);
    if (((int)tmp_s6 <= (int)param_3) || ((int)param_3 < 1)) {
      param_3 = tmp_s6;
    }
    tmp_i7 = 0;
    tmp_f3 = 0.0;
    tmp_f2 = tmp_f3;
    do {
      tmp_b1 = *param_1;
      if ((tmp_b1 == 0) || ((int)param_3 <= tmp_i7)) break;
      if (tmp_b1 == 0x5e) {
        if ((param_1[1] == 0) || (param_1[1] == 0x5e)) goto LAB_00023eab;
        param_1 = param_1 + 2;
      }
      else {
        if (tmp_b1 == 10) {
          if (tmp_f2 == 0.0) {
            tmp_f2 = tmp_f2 + 5.0;
          }
          tmp_f2 = tmp_f2 + tmp_f3;
          tmp_f4 = 0.0;
        }
        else {
LAB_00023eab:
          tmp_f4 = (float)*(int *)(&g_dat_00397ffc + (uint)tmp_b1 * 0x50 + tmp_i5 * 0x5044);
          if ((float)*(int *)(&g_dat_00397ffc + (uint)tmp_b1 * 0x50 + tmp_i5 * 0x5044) <= tmp_f3) {
            tmp_f4 = tmp_f3;
          }
        }
        param_1 = param_1 + 1;
        tmp_i7 = tmp_i7 + 1;
        tmp_f3 = tmp_f4;
      }
    } while (param_1 != (byte *)0x0);
    if (0.0 < tmp_f2) {
      if (tmp_f2 == 0.0) {
        tmp_f2 = tmp_f2 + 5.0;
      }
      tmp_f3 = tmp_f2 + tmp_f3;
    }
  }
  return (int)ROUND(tmp_f3 * param_2 * *(float *)(&g_dat_0039cffc + tmp_i5 * 0x5044));
}

void UI_BuildServerDisplayList(int param_1)

{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  long tmp_l6;
  long tmp_l7;
  int tmp_i8;
  char *tmp_pc9;
  uint32_t tmp_u10;
  uint tmp_u11;
  uint tmp_u12;
  uint *tmp_pu13;
  uint *tmp_pu14;
  char *tmp_pc15;
  bool tmp_b16;
  int tmp_i17;
  uint32_t *tmp_pu18;
  byte tmp_b19;
  uint uStack_241a0;
  uint8_t *puStack_2419c;
  int iStack_24198;
  int iStack_24190;
  uint32_t *puStack_2418c;
  char *pcStack_24188;
  int iStack_24180;
  uint32_t uStack_2415c;
  long alStack_24158 [79];
  uint8_t auStack_2401c [8192];
  char acStack_2201c [8192];
  char acStack_2001c [65536];
  uint8_t auStack_1001c [65548];
  
  tmp_b19 = 0;
  uStack_2415c = 0;
  tmp_u12 = 0;
  do {
    tmp_u11 = tmp_u12;
    *(uint32_t *)((int)alStack_24158 + tmp_u11) = 0;
    *(uint32_t *)((int)alStack_24158 + tmp_u11 + 4) = 0;
    tmp_u12 = tmp_u11 + 8;
  } while (tmp_u11 + 8 < 0x38);
  *(uint32_t *)((int)alStack_24158 + tmp_u11 + 8) = 0;
  if (param_1 == 0) {
    if (g_dat_00397fdc <= _DAT_003e53d8) {
      return;
    }
  }
  else if (param_1 == 2) {
    param_1 = 0;
  }
  trap_Cvar_VariableStringBuffer("cl_motdString",&g_dat_003e53fc,0x400);
  tmp_pu14 = (uint *)&g_dat_003e53fc;
  do {
    tmp_pu13 = tmp_pu14;
    tmp_u11 = *tmp_pu13 + 0xfefefeff & ~*tmp_pu13;
    tmp_u12 = tmp_u11 & 0x80808080;
    tmp_pu14 = tmp_pu13 + 1;
  } while (tmp_u12 == 0);
  if ((tmp_u11 & 0x8080) == 0) {
    tmp_pu14 = (uint *)((int)tmp_pu13 + 6);
    tmp_u12 = tmp_u12 >> 0x10;
  }
  tmp_pc15 = (char *)((int)tmp_pu14 + (-0x3e53ff - (uint)CARRY1((byte)tmp_u12,(byte)tmp_u12)));
  if (tmp_pc15 == (char *)0x0) {
    tmp_pc15 = (char *)va("Enemy Territory - Version: %s","ET 2.60");
    tmp_pc15 = stpcpy(&g_dat_003e53fc,tmp_pc15);
    tmp_pc15 = tmp_pc15 + -0x3e53fc;
  }
  if (g_dat_003e53e4 != tmp_pc15) {
    g_dat_003e53e8 = 0xffffffff;
    g_dat_003e53e4 = tmp_pc15;
  }
  if (param_1 != 0) {
    numinvisible_10443 = 0;
    g_dat_003e53c0 = 0;
    g_dat_003e53d0 = 0;
    g_dat_003e53d4 = 0;
    _DAT_003e53c8 = 0;
    g_dat_003e53cc = 0;
    _DAT_003e53c4 = 0;
    Menu_SetFeederSelection(0,2,0,0);
    trap_LAN_MarkServerVisible(GHIDRA_FIELD(ui_netSource, 12, 4),0xffffffff,1);
    trap_LAN_ServerStatus(0,0,0);
    tmp_pu18 = (uint32_t *)&g_dat_003ec078;
    for (tmp_i3 = 0x400; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
      *tmp_pu18 = 0;
      tmp_pu18 = tmp_pu18 + (uint)tmp_b19 * -2 + 1;
    }
    tmp_pu18 = (uint32_t *)&g_dat_003ed078;
    for (tmp_i3 = 0x400; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
      *tmp_pu18 = 0;
      tmp_pu18 = tmp_pu18 + (uint)tmp_b19 * -2 + 1;
    }
    tmp_pu18 = (uint32_t *)&g_dat_003ef078;
    for (tmp_i3 = 0x400; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
      *tmp_pu18 = 0;
      tmp_pu18 = tmp_pu18 + (uint)tmp_b19 * -2 + 1;
    }
    tmp_pu18 = (uint32_t *)&g_dat_003e8078;
    for (tmp_i3 = 0x400; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
      *tmp_pu18 = 0;
      tmp_pu18 = tmp_pu18 + (uint)tmp_b19 * -2 + 1;
    }
    tmp_pu18 = (uint32_t *)&g_dat_003e9078;
    for (tmp_i3 = 0x400; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
      *tmp_pu18 = 0;
      tmp_pu18 = tmp_pu18 + (uint)tmp_b19 * -2 + 1;
    }
    tmp_pu18 = (uint32_t *)&g_dat_003ea078;
    for (tmp_i3 = 0x400; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
      *tmp_pu18 = 0;
      tmp_pu18 = tmp_pu18 + (uint)tmp_b19 * -2 + 1;
    }
    tmp_pu18 = (uint32_t *)&g_dat_003ee078;
    for (tmp_i3 = 0x400; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
      *tmp_pu18 = 0;
      tmp_pu18 = tmp_pu18 + (uint)tmp_b19 * -2 + 1;
    }
    tmp_pu18 = (uint32_t *)&g_dat_003eb078;
    for (tmp_i3 = 0x400; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
      *tmp_pu18 = 0;
      tmp_pu18 = tmp_pu18 + (uint)tmp_b19 * -2 + 1;
    }
  }
  tmp_i3 = trap_LAN_GetServerCount(GHIDRA_FIELD(ui_netSource, 12, 4));
  if ((tmp_i3 == -1) || (tmp_i3 == 0 && GHIDRA_FIELD(ui_netSource, 12, 4) == 0)) {
    g_dat_003e53dc = 0;
    _DAT_003e53d8 = g_dat_00397fdc + 500;
    g_dat_003e53d0 = 0;
    g_dat_003e53cc = 0;
    _DAT_003e53c8 = 0;
    _DAT_003e53c4 = 0;
    g_dat_003e53c0 = 0;
    return;
  }
  if (g_dat_003e53c0 == 0) {
    g_dat_003e53dc = 0;
  }
  if (0 < tmp_i3) {
    puStack_2418c = &uiInfo;
    iStack_24190 = 0;
    do {
      tmp_i4 = trap_LAN_ServerIsVisible(GHIDRA_FIELD(ui_netSource, 12, 4),iStack_24190);
      if (tmp_i4 != 0) {
        trap_LAN_GetServerAddressString(GHIDRA_FIELD(ui_netSource, 12, 4),iStack_24190,&uStack_2415c,0x40);
        tmp_i4 = trap_LAN_GetServerPing(GHIDRA_FIELD(ui_netSource, 12, 4),iStack_24190);
        if ((0 < tmp_i4) || (GHIDRA_FIELD(ui_netSource, 12, 4) == 2)) {
          tmp_i5 = rand();
          trap_LAN_GetServerInfo(GHIDRA_FIELD(ui_netSource, 12, 4),iStack_24190,auStack_2401c,0x400);
          tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"clients");
          tmp_l6 = strtol(tmp_pc15,(char **)0x0,10);
          tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"sv_maxclients");
          tmp_l7 = strtol(tmp_pc15,(char **)0x0,10);
          if ((tmp_l7 < tmp_l6) || (0x40 < tmp_l7)) {
            tmp_pc15 = "allies_hq_promo_general_brigadier" + (int)(puStack_2418c + 8);
            tmp_pc15[0] = '\x02';
            tmp_pc15[1] = '\0';
            tmp_pc15[2] = '\0';
            tmp_pc15[3] = '\0';
            g_dat_003e53cc = g_dat_003e53cc + 1;
          }
          else {
            if (*(int *)("allies_hq_promo_general_brigadier" + (int)(puStack_2418c + 8)) == 0) {
              tmp_pc15 = "allies_hq_promo_general_brigadier" + (int)(puStack_2418c + 8);
              tmp_pc15[0] = '\x01';
              tmp_pc15[1] = '\0';
              tmp_pc15[2] = '\0';
              tmp_pc15[3] = '\0';
              _DAT_003e53c4 = _DAT_003e53c4 + 1;
              tmp_i5 = *(int *)("s_volume" + (int)puStack_2418c + 5);
            }
            else {
              if ((*(int *)(aReinfSeeds + (int)(puStack_2418c + 6)) == 1) ||
                 ((0 < *(int *)("hostGamePopupError" + (int)puStack_2418c + 10) &&
                  (g_dat_00397fdc - *(int *)("hostGamePopupError" + (int)puStack_2418c + 10) <
                   (tmp_i5 % 100) * 0x14 + 500)))) goto LAB_00024128;
              tmp_i5 = *(int *)("s_volume" + (int)puStack_2418c + 5);
              if (0x14 < tmp_i5) {
                _DAT_003e53c8 = _DAT_003e53c8 + 1;
                g_dat_003e53cc = g_dat_003e53cc + 1;
                goto LAB_00024586;
              }
            }
            tmp_i8 = g_dat_00397fdc;
            tmp_pc15 = acStack_2201c;
            *(int *)("s_volume" + (int)puStack_2418c + 5) = tmp_i5 + 1;
            *(int *)("hostGamePopupError" + (int)puStack_2418c + 10) = tmp_i8;
            tmp_i8 = trap_LAN_ServerStatus(&uStack_2415c,tmp_pc15,0x2000);
            tmp_i5 = g_dat_00397fdc;
            if (tmp_i8 == 0) {
              *(int *)("hostGamePopupError" + (int)puStack_2418c + 10) = g_dat_00397fdc;
              _DAT_003e13ac = tmp_i5 + 0x32;
              goto LAB_00024128;
            }
            *(uint32_t *)(aReinfSeeds + (int)(puStack_2418c + 6)) = 1;
            tmp_pc9 = "allies_hq_promo_general_brigadier" + (int)(puStack_2418c + 8);
            tmp_pc9[0] = '\x02';
            tmp_pc9[1] = '\0';
            tmp_pc9[2] = '\0';
            tmp_pc9[3] = '\0';
            tmp_pc9 = (char *)Info_ValueForKey(tmp_pc15,"sv_NxAC");
            if (*tmp_pc9 != '\0') {
              tmp_l7 = strtol(tmp_pc9,(char **)0x0,10);
              *(long *)(&UNK_000501b8 + (int)puStack_2418c) = tmp_l7;
            }
            tmp_pc9 = (char *)Info_ValueForKey(tmp_pc15,"humans");
            if (*tmp_pc9 == '\0') {
              tmp_pc9 = (char *)Info_ValueForKey(auStack_2401c,"version");
              tmp_pc9 = strstr(tmp_pc9,"ET Legacy");
              if (tmp_pc9 != (char *)0x0) {
                tmp_pc9 = (char *)Info_ValueForKey(auStack_2401c,"humans");
                goto LAB_000245f7;
              }
              tmp_b16 = false;
            }
            else {
LAB_000245f7:
              tmp_b16 = true;
              tmp_l7 = strtol(tmp_pc9,(char **)0x0,10);
              puStack_2418c[0x1446e] = tmp_l7;
            }
            do {
              if (*tmp_pc15 == '\0') goto LAB_0002466f;
              tmp_pc9 = strchr(tmp_pc15,0x5c);
              if (tmp_pc9 == (char *)0x0) break;
              tmp_pc15 = tmp_pc9 + 1;
              *tmp_pc9 = '\0';
              if (tmp_pc9[1] == '\\') goto LAB_0002466f;
              tmp_pc15 = strchr(tmp_pc15,0x5c);
              if (tmp_pc15 == (char *)0x0) break;
              *tmp_pc15 = '\0';
              tmp_pc15 = tmp_pc15 + 1;
            } while (tmp_pc15 != (char *)0x0);
            tmp_pc15 = (char *)0x0;
LAB_0002466f:
            tmp_pc15 = strtok(tmp_pc15,"\\");
            if (tmp_pc15 == (char *)0x0) {
              iStack_24180 = 0;
            }
            else {
              pcStack_24188 = acStack_2001c;
              iStack_24180 = 0;
              tmp_pc9 = pcStack_24188;
              do {
                iStack_24180 = iStack_24180 + 1;
                Q_strncpyz(tmp_pc9,tmp_pc15,0x400);
                tmp_pc15 = strtok((char *)0x0,"\\");
                tmp_pc9 = tmp_pc9 + 0x400;
              } while (tmp_pc15 != (char *)0x0);
              if (!tmp_b16) {
                tmp_i5 = 0;
                puStack_2419c = auStack_1001c;
                do {
                  tmp_pc15 = strtok(pcStack_24188," ");
                  if ((tmp_pc15 == (char *)0x0) || (*tmp_pc15 == '\\')) {
LAB_000247b2:
                    tmp_l7 = alStack_24158[tmp_i5 + 0xf];
                  }
                  else {
                    do {
                      tmp_pc15 = strtok((char *)0x0," ");
                      if (tmp_pc15 == (char *)0x0) goto LAB_000247b2;
                      tmp_l7 = strtol(tmp_pc15,(char **)0x0,10);
                      alStack_24158[tmp_i5 + 0xf] = tmp_l7;
                      tmp_pc15 = strtok((char *)0x0,"\"");
                    } while ((tmp_pc15 != (char *)0x0) &&
                            (Q_strncpyz(puStack_2419c,tmp_pc15,0x400), *tmp_pc15 != '\\'));
                  }
                  if (0 < tmp_l7) {
                    puStack_2418c[0x1446e] = puStack_2418c[0x1446e] + 1;
                  }
                  tmp_i5 = tmp_i5 + 1;
                  pcStack_24188 = pcStack_24188 + 0x400;
                  puStack_2419c = puStack_2419c + 0x400;
                } while (tmp_i5 != iStack_24180);
              }
            }
            puStack_2418c[0x1486e] = iStack_24180;
            if ((iStack_24180 < tmp_l6) && (5 < tmp_l6 - iStack_24180)) {
              _DAT_003e53c4 = _DAT_003e53c4 + -1;
              g_dat_003e53cc = g_dat_003e53cc + 1;
            }
            else {
              g_dat_003e53d0 = g_dat_003e53d0 + iStack_24180;
              g_dat_003e53d4 = g_dat_003e53d4 + puStack_2418c[0x1446e];
              _DAT_003e53c8 = _DAT_003e53c8 + 1;
              trap_Cvar_Update(ui_browserShowEmptyOrFull);
              if (GHIDRA_FIELD(ui_browserShowEmptyOrFull, 12, 4) != 0) {
                tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"sv_maxclients");
                tmp_l7 = strtol(tmp_pc15,(char **)0x0,10);
                if (tmp_l6 == tmp_l7) {
                  if (tmp_l6 != 0) goto LAB_00024e54;
                }
                else if (tmp_l6 == 0) {
LAB_00024e54:
                  if (GHIDRA_FIELD(ui_browserShowEmptyOrFull, 12, 4) == 2) goto LAB_00024586;
                }
                else if (GHIDRA_FIELD(ui_browserShowEmptyOrFull, 12, 4) == 1) goto LAB_00024586;
              }
              trap_Cvar_Update(ui_browserShowPasswordProtected);
              if (GHIDRA_FIELD(ui_browserShowPasswordProtected, 12, 4) == 0) {
LAB_000248a6:
                trap_Cvar_Update(ui_browserShowFriendlyFire);
                if (GHIDRA_FIELD(ui_browserShowFriendlyFire, 12, 4) == 0) {
LAB_00024900:
                  trap_Cvar_Update(ui_browserShowMaxlives);
                  if (GHIDRA_FIELD(ui_browserShowMaxlives, 12, 4) == 0) {
LAB_0002495a:
                    trap_Cvar_Update(ui_browserShowPunkBuster);
                    if (GHIDRA_FIELD(ui_browserShowPunkBuster, 12, 4) == 0) {
LAB_000249b4:
                      trap_Cvar_Update(ui_browserShowAntilag);
                      if (GHIDRA_FIELD(ui_browserShowAntilag, 12, 4) == 0) {
LAB_00024a0e:
                        trap_Cvar_Update(ui_browserShowWeaponsRestricted);
                        if (GHIDRA_FIELD(ui_browserShowWeaponsRestricted, 12, 4) == 0) {
LAB_00024a69:
                          trap_Cvar_Update(ui_browserShowTeamBalanced);
                          if (GHIDRA_FIELD(ui_browserShowTeamBalanced, 12, 4) == 0) {
LAB_00024ac3:
                            trap_Cvar_Update(ui_joinGameType);
                            if (GHIDRA_FIELD(ui_joinGameType, 12, 4) != -1) {
                              tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"gametype");
                              tmp_l6 = strtol(tmp_pc15,(char **)0x0,10);
                              if (GHIDRA_FIELD(ui_joinGameType, 12, 4) != tmp_l6) goto LAB_00024586;
                            }
                            trap_Cvar_Update(ui_browserNitmodonly);
                            tmp_u10 = Info_ValueForKey(auStack_2401c,"game");
                            tmp_i5 = Q_stricmp(tmp_u10,"nitmod");
                            if (((tmp_i5 != 0) || (GHIDRA_FIELD(ui_browserNitmodonly, 12, 4) != 2)) &&
                               ((tmp_i5 = Q_stricmp(tmp_u10,"nitmod"), tmp_i5 == 0 ||
                                (GHIDRA_FIELD(ui_browserNitmodonly, 12, 4) != 1)))) {
                              trap_Cvar_Update(ui_browserNxAConly);
                              if (GHIDRA_FIELD(ui_browserNitmodonly, 12, 4) != 1) {
LAB_00024b96:
                                uStack_241a0 = g_dat_003e53c0;
                                tmp_u12 = g_dat_003e53c0;
                                if ((GHIDRA_FIELD(ui_netSource, 12, 4) == 2) && (0 < (int)g_dat_003e53c0)) {
                                  tmp_u11 = 0;
                                  tmp_i5 = _DAT_003e13c0;
                                  while (iStack_24190 != tmp_i5) {
                                    tmp_u11 = tmp_u11 + 1;
                                    if (tmp_u11 == g_dat_003e53c0) goto LAB_00024bc0;
                                    tmp_i5 = *(int *)(&g_dat_003e13c0 + tmp_u11 * 4);
                                  }
                                  uStack_241a0 = g_dat_003e53c0 - 1;
                                  tmp_u12 = uStack_241a0;
                                  if ((int)tmp_u11 < (int)uStack_241a0) {
                                    tmp_i5 = g_dat_003e53c0 - tmp_u11;
                                    g_dat_003e53c0 = uStack_241a0;
                                    memmove(&g_dat_003e13c0 + tmp_u11 * 4,&g_dat_003e13c4 + tmp_u11 * 4,
                                            tmp_i5 * 4 - 4);
                                    tmp_u12 = g_dat_003e53c0;
                                  }
                                }
                                g_dat_003e53c0 = tmp_u12;
                                if (uStack_241a0 == 0) {
                                  tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"mapname");
                                  if ((tmp_pc15 == (char *)0x0) || (*tmp_pc15 == '\0')) {
                                    tmp_pc15 = "levelshots/unknownmap";
                                  }
                                  else {
                                    tmp_u10 = Info_ValueForKey(auStack_2401c,"mapname");
                                    tmp_pc15 = (char *)va("levelshots/%s",tmp_u10);
                                  }
                                  g_dat_003e53dc = trap_R_RegisterShaderNoMip(tmp_pc15);
                                  uStack_241a0 = g_dat_003e53c0;
                                }
                                if ((int)uStack_241a0 < 1) {
                                  tmp_i5 = 0;
                                  if (g_dat_003e53c0 < 0x80000000) {
                                    tmp_u12 = g_dat_003e53c0 + 1;
LAB_00024f9b:
                                    tmp_i17 = g_dat_003e53c0 * 4;
                                    tmp_i8 = tmp_u12 - tmp_i5;
                                    g_dat_003e53c0 = tmp_u12;
                                    memmove(&g_dat_003e13c8 + tmp_i17 + tmp_i8 * -4,
                                            &g_dat_003e13c4 + tmp_i17 + tmp_i8 * -4,tmp_i8 * 4);
                                    tmp_u12 = g_dat_003e53c0;
                                    goto LAB_00024fcc;
                                  }
                                }
                                else {
LAB_00024bc0:
                                  tmp_i8 = 0;
                                  do {
                                    tmp_i17 = (int)uStack_241a0 >> 1;
                                    tmp_i5 = tmp_i17 + tmp_i8;
                                    if (_DAT_003e13b0 == 2) {
                                      tmp_i1 = *(int *)(&g_dat_003e9078 +
                                                      (&g_dat_00397ed0)[tmp_i5 + 0x1253c] * 4);
                                      tmp_i2 = puStack_2418c[0x1446e];
                                      if (tmp_i1 <= tmp_i2) {
                                        tmp_u12 = (uint)(tmp_i1 < tmp_i2);
                                        if (_DAT_003e13b4 == 0) goto LAB_00024c8d;
                                        if (tmp_i1 < tmp_i2) goto LAB_00024c18;
                                        goto LAB_0002500e;
                                      }
                                      if (_DAT_003e13b4 == 0) {
LAB_00024c18:
                                        tmp_u12 = 0xffffffff;
                                        goto LAB_00024c1d;
                                      }
                                      tmp_u12 = 1;
                                    }
                                    else {
                                      tmp_u12 = trap_LAN_CompareServers
                                                         (GHIDRA_FIELD(ui_netSource, 12, 4),_DAT_003e13b0,
                                                          _DAT_003e13b4,iStack_24190,
                                                          (&g_dat_00397ed0)[tmp_i5 + 0x1253c]);
LAB_00024c8d:
                                      if (tmp_u12 == 0) {
LAB_0002500e:
                                        iStack_24198 = tmp_i5 + 0x1253c;
                                        if ((-1 < tmp_i5) && (tmp_i5 <= (int)g_dat_003e53c0)) {
                                          tmp_u12 = g_dat_003e53c0 + 1;
                                          if (tmp_i5 < (int)tmp_u12) {
                                            tmp_i8 = g_dat_003e53c0 * 4;
                                            tmp_i5 = tmp_u12 - tmp_i5;
                                            g_dat_003e53c0 = tmp_u12;
                                            memmove(&g_dat_003e13c8 + tmp_i8 + tmp_i5 * -4,
                                                    &g_dat_003e13c4 + tmp_i8 + tmp_i5 * -4,tmp_i5 * 4);
                                            tmp_u12 = g_dat_003e53c0;
                                          }
                                          g_dat_003e53c0 = tmp_u12;
                                          (&g_dat_00397ed0)[iStack_24198] = iStack_24190;
                                        }
                                        goto LAB_00024fdb;
                                      }
                                      if (tmp_u12 != 1) {
LAB_00024c1d:
                                        tmp_i5 = tmp_i8;
                                      }
                                    }
                                    uStack_241a0 = uStack_241a0 - tmp_i17;
                                    tmp_i8 = tmp_i5;
                                  } while (0 < tmp_i17);
                                  tmp_i5 = (uint)(tmp_u12 == 1) + tmp_i5;
                                  if ((-1 < tmp_i5) && (tmp_i5 <= (int)g_dat_003e53c0)) {
                                    tmp_u12 = g_dat_003e53c0 + 1;
                                    if (tmp_i5 < (int)tmp_u12) goto LAB_00024f9b;
LAB_00024fcc:
                                    g_dat_003e53c0 = tmp_u12;
                                    *(int *)(&g_dat_003e13c0 + tmp_i5 * 4) = iStack_24190;
                                  }
                                }
LAB_00024fdb:
                                if (0 < tmp_i4) {
                                  trap_LAN_MarkServerVisible(GHIDRA_FIELD(ui_netSource, 12, 4),iStack_24190,0);
                                  numinvisible_10443 = numinvisible_10443 + 1;
                                }
                                goto LAB_00024128;
                              }
                              if (GHIDRA_FIELD(ui_browserNxAConly, 12, 4) == 1) {
                                if (*(int *)(&UNK_000501b8 + (int)puStack_2418c) != 0)
                                goto LAB_00024b96;
                              }
                              else if ((GHIDRA_FIELD(ui_browserNxAConly, 12, 4) != 2) ||
                                      (*(int *)(&UNK_000501b8 + (int)puStack_2418c) != 1))
                              goto LAB_00024b96;
                            }
                          }
                          else {
                            tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"balancedteams");
                            tmp_l6 = strtol(tmp_pc15,(char **)0x0,10);
                            if (tmp_l6 == 0) {
                              if (GHIDRA_FIELD(ui_browserShowTeamBalanced, 12, 4) != 1) goto LAB_00024ac3;
                            }
                            else if (GHIDRA_FIELD(ui_browserShowTeamBalanced, 12, 4) != 2) goto LAB_00024ac3;
                          }
                        }
                        else {
                          tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"weaprestrict");
                          tmp_l6 = strtol(tmp_pc15,(char **)0x0,10);
                          if (tmp_l6 == 100) {
                            if (GHIDRA_FIELD(ui_browserShowWeaponsRestricted, 12, 4) != 1) goto LAB_00024a69;
                          }
                          else if (GHIDRA_FIELD(ui_browserShowWeaponsRestricted, 12, 4) != 2) goto LAB_00024a69;
                        }
                      }
                      else {
                        tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"g_antilag");
                        tmp_l6 = strtol(tmp_pc15,(char **)0x0,10);
                        if (tmp_l6 == 0) {
                          if (GHIDRA_FIELD(ui_browserShowAntilag, 12, 4) != 1) goto LAB_00024a0e;
                        }
                        else if (GHIDRA_FIELD(ui_browserShowAntilag, 12, 4) != 2) goto LAB_00024a0e;
                      }
                    }
                    else {
                      tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"punkbuster");
                      tmp_l6 = strtol(tmp_pc15,(char **)0x0,10);
                      if (tmp_l6 == 0) {
                        if (GHIDRA_FIELD(ui_browserShowPunkBuster, 12, 4) != 1) goto LAB_000249b4;
                      }
                      else if (GHIDRA_FIELD(ui_browserShowPunkBuster, 12, 4) != 2) goto LAB_000249b4;
                    }
                  }
                  else {
                    tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"maxlives");
                    tmp_l6 = strtol(tmp_pc15,(char **)0x0,10);
                    if (tmp_l6 == 0) {
                      if (GHIDRA_FIELD(ui_browserShowMaxlives, 12, 4) != 1) goto LAB_0002495a;
                    }
                    else if (GHIDRA_FIELD(ui_browserShowMaxlives, 12, 4) != 2) goto LAB_0002495a;
                  }
                }
                else {
                  tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"friendlyFire");
                  tmp_u12 = strtol(tmp_pc15,(char **)0x0,10);
                  if ((tmp_u12 & 1) == 0) {
                    if (GHIDRA_FIELD(ui_browserShowFriendlyFire, 12, 4) != 1) goto LAB_00024900;
                  }
                  else if (GHIDRA_FIELD(ui_browserShowFriendlyFire, 12, 4) != 2) goto LAB_00024900;
                }
              }
              else {
                tmp_pc15 = (char *)Info_ValueForKey(auStack_2401c,"needpass");
                tmp_l6 = strtol(tmp_pc15,(char **)0x0,10);
                if (tmp_l6 == 0) {
                  if (GHIDRA_FIELD(ui_browserShowPasswordProtected, 12, 4) != 1) goto LAB_000248a6;
                }
                else if (GHIDRA_FIELD(ui_browserShowPasswordProtected, 12, 4) != 2) goto LAB_000248a6;
              }
            }
          }
LAB_00024586:
          trap_LAN_MarkServerVisible(GHIDRA_FIELD(ui_netSource, 12, 4),iStack_24190,0);
        }
      }
LAB_00024128:
      iStack_24190 = iStack_24190 + 1;
      puStack_2418c = puStack_2418c + 1;
    } while (iStack_24190 != tmp_i3);
  }
  _DAT_003e13ac = g_dat_00397fdc;
  return;
}

void UI_ServersQsortCompare(uint32_t *param_1,uint32_t *param_2)

{
  trap_LAN_CompareServers(GHIDRA_FIELD(ui_netSource, 12, 4),_DAT_003e13b0,_DAT_003e13b4,*param_1,*param_2);
  return;
}

uint32_t UI_GetServerStatusInfo(uint32_t param_1,uint32_t *param_2)

{
  char tmp_c1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  int tmp_i6;
  char *tmp_pc7;
  int tmp_i8;
  size_t tmp_s9;
  uint tmp_u10;
  uint tmp_u11;
  char *tmp_pc12;
  uint8_t **tmp_ppu13;
  char *__s;
  uint32_t *tmp_pu14;
  char *tmp_pc15;
  bool tmp_b16;
  int local_3c;
  int local_34;
  
  if (param_2 == (uint32_t *)0x0) {
    trap_LAN_ServerStatus(param_1,0,0);
    return 0;
  }
  tmp_b16 = ((uint)param_2 & 1) != 0;
  tmp_u11 = 0x1104;
  tmp_pu14 = param_2;
  if (tmp_b16) {
    tmp_u11 = 0x1103;
    *(uint8_t *)param_2 = 0;
    tmp_pu14 = (uint32_t *)((int)param_2 + 1);
  }
  if (((uint)tmp_pu14 & 2) != 0) {
    *(uint16_t *)tmp_pu14 = 0;
    tmp_u11 = tmp_u11 - 2;
    tmp_pu14 = (uint32_t *)((int)tmp_pu14 + 2);
  }
  if (((uint)tmp_pu14 & 4) != 0) {
    *tmp_pu14 = 0;
    tmp_u11 = tmp_u11 - 4;
    tmp_pu14 = tmp_pu14 + 1;
  }
  for (tmp_u10 = tmp_u11 >> 2; tmp_u10 != 0; tmp_u10 = tmp_u10 - 1) {
    *tmp_pu14 = 0;
    tmp_pu14 = tmp_pu14 + 1;
  }
  if ((tmp_u11 & 2) != 0) {
    *(uint16_t *)tmp_pu14 = 0;
    tmp_pu14 = (uint32_t *)((int)tmp_pu14 + 2);
  }
  if (tmp_b16) {
    *(uint8_t *)tmp_pu14 = 0;
  }
  tmp_i5 = trap_LAN_ServerStatus(param_1,param_2 + 0x210,0x800);
  if (tmp_i5 == 0) {
    return 0;
  }
  tmp_i5 = Menus_FindByName("serverinfo_popmenu");
  tmp_i6 = Menus_FindByName("popupError");
  Q_strncpyz(param_2,param_1,0x40);
  param_2[0x10] = "Address";
  param_2[0x440] = 1;
  param_2[0x11] = "";
  param_2[0x12] = "";
  param_2[0x13] = param_2;
  trap_Cvar_Set("ui_URL","");
  trap_Cvar_Set("ui_modURL","");
  tmp_pc12 = (char *)0x0;
  tmp_pc7 = (char *)(param_2 + 0x210);
  tmp_pc15 = (char *)0x0;
  do {
    __s = tmp_pc7;
    if ((*tmp_pc7 == '\0') || (tmp_pc7 = strchr(tmp_pc7,0x5c), __s = tmp_pc7, tmp_pc7 == (char *)0x0)) {
LAB_00025741:
      tmp_i8 = param_2[0x440];
      goto joined_r0x0002574a;
    }
    __s = tmp_pc7 + 1;
    *tmp_pc7 = '\0';
    if (tmp_pc15 != (char *)0x0) {
      tmp_i8 = Q_stricmp(tmp_pc15,&g_dat_000559ed);
      if (tmp_i8 == 0) {
        trap_Cvar_Set("ui_URL",tmp_pc12);
        if (tmp_i5 != 0) {
          Menu_ShowItemByName(tmp_i5,"serverURL",1);
        }
        if (tmp_i6 != 0) {
          Menu_ShowItemByName(tmp_i6,"serverURL",1);
        }
      }
      else {
        tmp_i8 = Q_stricmp(tmp_pc15,&g_dat_000559e9);
        if (tmp_i8 == 0) {
          trap_Cvar_Set("ui_modURL",tmp_pc12);
          if (tmp_i5 != 0) {
            Menu_ShowItemByName(tmp_i5,"modURL",1);
          }
          if (tmp_i6 != 0) {
            Menu_ShowItemByName(tmp_i6,"modURL",1);
          }
        }
      }
    }
    if (tmp_pc7[1] == '\\') goto LAB_00025741;
    tmp_i8 = param_2[0x440];
    param_2[(tmp_i8 + 4) * 4] = __s;
    param_2[tmp_i8 * 4 + 0x11] = "";
    param_2[tmp_i8 * 4 + 0x12] = "";
    tmp_pc12 = strchr(__s,0x5c);
    if (tmp_pc12 == (char *)0x0) break;
    *tmp_pc12 = '\0';
    tmp_pc12 = tmp_pc12 + 1;
    tmp_i8 = param_2[0x440] + 1;
    param_2[param_2[0x440] * 4 + 0x13] = tmp_pc12;
    param_2[0x440] = tmp_i8;
    if (0x7f < tmp_i8) goto LAB_000254bf;
    tmp_pc7 = tmp_pc12;
    tmp_pc15 = __s;
  } while (tmp_pc12 != (char *)0x0);
  __s = (char *)0x0;
joined_r0x0002574a:
  if (tmp_i8 < 0x7d) {
    param_2[tmp_i8 * 4 + 0x10] = "";
    param_2[tmp_i8 * 4 + 0x11] = "";
    param_2[tmp_i8 * 4 + 0x12] = "";
    param_2[tmp_i8 * 4 + 0x13] = "";
    tmp_i5 = tmp_i8 + 1;
    param_2[tmp_i8 * 4 + 0x14] = &g_dat_000559f1;
    param_2[tmp_i5 * 4 + 0x11] = "score";
    param_2[tmp_i5 * 4 + 0x12] = &g_dat_000559fb;
    param_2[tmp_i5 * 4 + 0x13] = "name";
    param_2[0x440] = tmp_i8 + 2;
    if ((__s != (char *)0x0) && (tmp_c1 = *__s, tmp_c1 != '\0')) {
      tmp_i5 = 0;
      local_3c = 0;
      do {
        if (tmp_c1 == '\\') {
          *__s = '\0';
          __s = __s + 1;
          if (__s == (char *)0x0) break;
        }
        tmp_pc12 = strchr(__s,0x20);
        if (tmp_pc12 == (char *)0x0) break;
        *tmp_pc12 = '\0';
        tmp_pc7 = strchr(tmp_pc12 + 1,0x20);
        if (tmp_pc7 == (char *)0x0) break;
        *tmp_pc7 = '\0';
        tmp_pc15 = (char *)((int)param_2 + tmp_i5 + 0x1040);
        Com_sprintf(tmp_pc15,0xc0 - tmp_i5,"%d",local_3c);
        tmp_i6 = param_2[0x440];
        param_2[(tmp_i6 + 4) * 4] = tmp_pc15;
        tmp_s9 = strlen(tmp_pc15);
        tmp_i5 = tmp_i5 + 1 + tmp_s9;
        param_2[tmp_i6 * 4 + 0x11] = __s;
        param_2[tmp_i6 * 4 + 0x12] = tmp_pc12 + 1;
        param_2[tmp_i6 * 4 + 0x13] = tmp_pc7 + 1;
        param_2[0x440] = tmp_i6 + 1;
        if ((0x7f < tmp_i6 + 1) || (tmp_pc12 = strchr(tmp_pc7 + 1,0x5c), tmp_pc12 == (char *)0x0))
        break;
        local_3c = local_3c + 1;
        __s = tmp_pc12 + 1;
        *tmp_pc12 = '\0';
        if ((__s == (char *)0x0) || (tmp_c1 = tmp_pc12[1], tmp_c1 == '\0')) break;
      } while( true );
    }
  }
LAB_000254bf:
  if (serverStatusCvars != (uint8_t *)0x0) {
    tmp_i5 = param_2[0x440];
    local_34 = 0;
    tmp_ppu13 = &g_ptr_s_Address_0005663a_0xe_00068dc8;
    do {
      if (0 < tmp_i5) {
        tmp_i6 = 0;
        tmp_pu14 = param_2 + 0x10;
        do {
          while (((char *)tmp_pu14[1] == (char *)0x0 || (*(char *)tmp_pu14[1] != '\0'))) {
            tmp_i6 = tmp_i6 + 1;
            tmp_pu14 = tmp_pu14 + 4;
            if (tmp_i5 <= tmp_i6) goto LAB_00025595;
          }
          tmp_i5 = Q_stricmp(tmp_ppu13[-2],*tmp_pu14);
          if (tmp_i5 == 0) {
            tmp_u2 = param_2[local_34 * 4 + 0x10];
            tmp_u3 = param_2[local_34 * 4 + 0x13];
            param_2[local_34 * 4 + 0x10] = *tmp_pu14;
            param_2[local_34 * 4 + 0x13] = tmp_pu14[3];
            *tmp_pu14 = tmp_u2;
            tmp_pu14[3] = tmp_u3;
            if (*tmp_ppu13[-1] != '\0') {
              param_2[local_34 * 4 + 0x10] = tmp_ppu13[-1];
            }
            local_34 = local_34 + 1;
          }
          tmp_i6 = tmp_i6 + 1;
          tmp_pu14 = tmp_pu14 + 4;
          tmp_i5 = param_2[0x440];
        } while (tmp_i6 < tmp_i5);
      }
LAB_00025595:
      tmp_pu4 = *tmp_ppu13;
      tmp_ppu13 = tmp_ppu13 + 2;
    } while (tmp_pu4 != (uint8_t *)0x0);
  }
  return 1;
}

void UI_PlayCinematic(uint32_t param_1,float param_2,float param_3,float param_4,float param_5)

{
  trap_CIN_PlayCinematic
            (param_1,(int)ROUND(param_2),(int)ROUND(param_3),(int)ROUND(param_4),(int)ROUND(param_5)
             ,10);
  return;
}

uint8_t * UI_FileText(uint32_t param_1)

{
  int tmp_i1;
  int local_10;
  
  tmp_i1 = trap_FS_FOpenFile(param_1,&local_10,0);
  if (local_10 != 0) {
    trap_FS_Read(buf_10605,tmp_i1,local_10);
    buf_10605[tmp_i1] = 0;
    trap_FS_FCloseFile(local_10);
    return buf_10605;
  }
  return (uint8_t *)0x0;
}

uint32_t UI_OwnerDrawVisible(uint param_1)

{
  uint32_t tmp_u1;
  long double tmp_l2;
  
  tmp_u1 = 1;
  while( true ) {
    if (param_1 == 0) {
      return tmp_u1;
    }
    if ((param_1 & 0x100) != 0) {
      param_1 = param_1 & 0xfffffeff;
    }
    if ((param_1 & 0x200) != 0) {
      param_1 = param_1 & 0xfffffdff;
      tmp_u1 = 0;
    }
    if ((param_1 & 4) != 0) {
      if (GHIDRA_FIELD(ui_netSource, 12, 4) != 2) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xfffffffb;
    }
    if ((param_1 & 0x1000) != 0) {
      if (GHIDRA_FIELD(ui_netSource, 12, 4) == 2) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xffffefff;
    }
    if ((param_1 & 0x10) != 0) {
      param_1 = param_1 & 0xffffffef;
    }
    if ((param_1 & 8) != 0) {
      param_1 = param_1 & 0xfffffff7;
      tmp_u1 = 0;
    }
    if ((param_1 & 0x800) != 0) {
      param_1 = param_1 & 0xfffff7ff;
    }
    if ((param_1 & 0x400) != 0) {
      param_1 = param_1 & 0xfffffbff;
      tmp_u1 = 0;
    }
    if ((param_1 & 0x20) != 0) {
      if (_DAT_003b7f20 < g_dat_00397fdc) {
        tmp_u1 = 0;
      }
      else if ((_DAT_003b7f34 != 0) &&
              (tmp_l2 = (long double)trap_Cvar_VariableValue("sv_killserver"), tmp_l2 == (long double)0)
              ) {
        trap_S_StartLocalSound(_DAT_003e7e1c,7);
        _DAT_003b7f34 = 0;
      }
      param_1 = param_1 & 0xffffffdf;
    }
    if ((param_1 & 0x80) != 0) {
      if (_DAT_003b7f24 < g_dat_00397fdc) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xffffff7f;
    }
    if ((param_1 & 0x2000) != 0) {
      if (*(int *)(&g_dat_003cab88 + GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x74) < 1) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xffffdfff;
    }
    if ((param_1 & 0x4000) != 0) {
      if (*(int *)(&g_dat_003cab88 + GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x74) < 2) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xffffbfff;
    }
    if ((param_1 & 0x8000) != 0) {
      if (*(int *)(&g_dat_003cab88 + GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x74) < 3) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xffff7fff;
    }
    if ((param_1 & 0x10000) != 0) {
      if (*(int *)(&g_dat_003cab88 + GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x74) < 4) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xfffeffff;
    }
    if ((param_1 & 0x20000) != 0) {
      if (*(int *)(&g_dat_003cab88 + GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x74) < 5) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xfffdffff;
    }
    if ((param_1 & 0x40000) != 0) {
      if (*(int *)(&g_dat_003cab88 + GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x74) < 6) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xfffbffff;
    }
    if ((param_1 & 0x80000) != 0) {
      tmp_l2 = (long double)trap_Cvar_VariableValue("ui_campaignmap");
      if ((int)(&g_dat_003cabd8)[GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x1d] < (int)ROUND(tmp_l2)) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xfff7ffff;
    }
    if ((param_1 & 0x100000) != 0) {
      tmp_l2 = (long double)trap_Cvar_VariableValue("ui_campaignmap");
      if ((int)ROUND(tmp_l2) <= (int)(&g_dat_003cabd8)[GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x1d]) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xffefffff;
    }
    if ((param_1 & 0x1000000) != 0) {
      if (*(int *)(&g_dat_003b9f6c + _DAT_003b8d64 * 4) == 0) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xfeffffff;
    }
    if ((param_1 & 0x2000000) != 0) {
      if (*(int *)(&g_dat_003b9f6c + _DAT_003b8d64 * 4) != 0) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xfdffffff;
    }
    if ((param_1 & 0x4000000) != 0) {
      if (*(int *)(&g_dat_003ba06c + _DAT_003b8d64 * 4) != 0) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xfbffffff;
    }
    if ((param_1 & 0x8000000) != 0) {
      if (*(int *)(&g_dat_003ba06c + _DAT_003b8d64 * 4) != 1) {
        tmp_u1 = 0;
      }
      param_1 = param_1 & 0xf7ffffff;
    }
    if ((param_1 & 0x40) == 0) break;
    if (_DAT_003b7f30 == 0) {
      tmp_u1 = 0;
    }
    param_1 = param_1 & 0xffffffbf;
  }
  return tmp_u1;
}

void UI_SortMods(uint32_t *param_1,uint32_t *param_2)

{
  strcmp((char *)*param_1,(char *)*param_2);
  return;
}

void UI_BuildPlayerList(void)

{
  int tmp_i1;
  char *tmp_pc2;
  long tmp_l3;
  long tmp_l4;
  uint32_t tmp_u5;
  long tmp_l6;
  int tmp_i7;
  uint8_t local_1068 [64];
  char local_1028 [1024];
  uint8_t local_c28 [8];
  int local_c20;
  uint32_t uStack_14;
  
  uStack_14 = 0x25cd3;
  trap_GetClientState(local_c28);
  trap_GetConfigString(local_c20 + 0x2b1,local_1028,0x400);
  _DAT_003b8d68 = local_c20;
  tmp_pc2 = (char *)Info_ValueForKey(local_1028,&g_dat_00053088);
  tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
  trap_GetConfigString(0,local_1028,0x400);
  tmp_pc2 = (char *)Info_ValueForKey(local_1028,"sv_maxclients");
  tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
  g_dat_003b8d58 = 0;
  g_dat_003b8d54 = 0;
  if (tmp_l4 < 1) {
    g_dat_003b8d58 = 0;
    g_dat_003b8d54 = 0;
    return;
  }
  tmp_i7 = 0;
  do {
    while (trap_GetConfigString(tmp_i7 + 0x2b1,local_1028,0x400), local_1028[0] == '\0') {
LAB_00025dc0:
      tmp_i7 = tmp_i7 + 1;
      if (tmp_i7 == tmp_l4) {
        return;
      }
    }
    tmp_u5 = Info_ValueForKey(local_1028,&g_dat_000530b0);
    Q_strncpyz(local_1068,tmp_u5,0x40);
    Q_strncpyz(&g_dat_003b8d6c + g_dat_003b8d54 * 0x48,local_1068,0x48);
    tmp_pc2 = (char *)Info_ValueForKey(local_1028,&g_dat_00055a1d);
    tmp_l6 = strtol(tmp_pc2,(char **)0x0,10);
    tmp_i1 = g_dat_003b8d54;
    if (tmp_l6 == 0) {
      *(uint32_t *)(&g_dat_003b9f6c + g_dat_003b8d54 * 4) = 0;
    }
    else {
      *(uint32_t *)(&g_dat_003b9f6c + g_dat_003b8d54 * 4) = 1;
    }
    tmp_pc2 = (char *)Info_ValueForKey(local_1028,&g_dat_00055a20);
    tmp_l6 = strtol(tmp_pc2,(char **)0x0,10);
    g_dat_003b8d54 = g_dat_003b8d54 + 1;
    *(long *)(&g_dat_003ba06c + tmp_i1 * 4) = tmp_l6;
    tmp_pc2 = (char *)Info_ValueForKey(local_1028,&g_dat_00053088);
    tmp_l6 = strtol(tmp_pc2,(char **)0x0,10);
    if (tmp_l3 != tmp_l6) goto LAB_00025dc0;
    tmp_u5 = Info_ValueForKey(local_1028,&g_dat_000530b0);
    Q_strncpyz(local_1068,tmp_u5,0x40);
    Q_strncpyz(&g_dat_003ba16c + g_dat_003b8d58 * 0x24,local_1068,0x24);
    *(int *)(&g_dat_003baa6c + g_dat_003b8d58 * 4) = tmp_i7;
    tmp_i7 = tmp_i7 + 1;
    g_dat_003b8d58 = g_dat_003b8d58 + 1;
    if (tmp_i7 == tmp_l4) {
      return;
    }
  } while( true );
}

void UI_RunCinematicFrame(uint32_t param_1)

{
  trap_CIN_RunCinematic(param_1);
  return;
}

void UI_DrawCinematic(uint32_t param_1,float param_2,float param_3,float param_4,float param_5)

{
  trap_CIN_SetExtents(param_1,(int)ROUND(param_2),(int)ROUND(param_3),(int)ROUND(param_4),
                      (int)ROUND(param_5));
  trap_CIN_DrawCinematic(param_1);
  return;
}

void UI_StopServerRefresh_part_19(void)

{
  int tmp_i1;
  
  g_dat_003e13b8 = 0;
  Com_Printf("^g%d ^9servers listed in browser with %d players (^7%d ^9humans).\n",g_dat_003e53c0,
             g_dat_003e53d0,g_dat_003e53d4);
  tmp_i1 = trap_LAN_GetServerCount(GHIDRA_FIELD(ui_netSource, 12, 4));
  tmp_i1 = tmp_i1 - g_dat_003e53c0;
  if (0 < tmp_i1) {
    Com_Printf("^8%d ^9servers not listed:\n- ^3%d ^9filtered out by game browser settings\n- ^1%d ^9dropped (fake, serverfacades, no or bad statusResponse)\n"
               ,tmp_i1,tmp_i1 - g_dat_003e53cc,g_dat_003e53cc);
  }
  return;
}

void UI_Pause(int param_1)

{
  uint tmp_u1;
  
  if (param_1 == 0) {
    tmp_u1 = trap_Key_GetCatcher();
    trap_Key_SetCatcher(tmp_u1 & 0xfffffffd);
    trap_Key_ClearStates();
    trap_Cvar_Set("cl_paused","0");
    return;
  }
  trap_Cvar_Set("cl_paused","1");
  trap_Key_SetCatcher(2);
  return;
}

char * UI_FeederItemText_part_33
          (int param_1,uint param_2,float param_3,uint32_t *param_4,uint32_t *param_5)

{
  int tmp_i1;
  long tmp_l2;
  uint tmp_u3;
  long tmp_l4;
  long tmp_l5;
  long tmp_l6;
  long tmp_l7;
  long tmp_l8;
  uint32_t tmp_u9;
  uint32_t tmp_u10;
  char *tmp_pc11;
  int *tmp_pi12;
  int tmp_i13;
  uint8_t local_11c [264];
  uint32_t uStack_14;
  
  uStack_14 = 0x26159;
  if ((param_3 == 27.0) || (param_3 == 26.0)) {
    if (0 < g_dat_003cab70) {
      tmp_pi12 = &g_dat_003cabe0;
      tmp_i13 = 0;
      do {
        if ((*tmp_pi12 == param_1) && (tmp_pi12[-3] != 0)) {
          return (char *)(&g_dat_003cab78)[tmp_i13 * 0x1d];
        }
        tmp_i13 = tmp_i13 + 1;
        tmp_pi12 = tmp_pi12 + 0x1d;
      } while (tmp_i13 != g_dat_003cab70);
    }
  }
  else if (param_3 == 29.0) {
    if (param_1 == 0) {
      tmp_pc11 = (char *)va("Vendor: %s",&g_dat_003b66b0);
      return tmp_pc11;
    }
    if (param_1 == 1) {
      tmp_pc11 = (char *)va("Version: %s: %s",&g_dat_003b6ab0,&g_dat_003b62b0);
      return tmp_pc11;
    }
    if (param_1 == 2) {
      tmp_pc11 = (char *)va("Pixelformat: color(%d-bits) Z(%d-bits) stencil(%d-bits)",g_dat_003b7eb8,
                           g_dat_003b7ebc,g_dat_003b7ec0);
      return tmp_pc11;
    }
    if ((3 < param_1) && (param_1 < g_dat_003e8030)) {
      return (char *)(&g_dat_003e7e20)[param_1];
    }
  }
  else if (param_3 == 2.0) {
    if ((-1 < param_1) && (param_1 < g_dat_003e53c0)) {
      if ((lastColumn_10617 != param_2) || (g_dat_00397fdc + 5000 < lastTime_10618)) {
        trap_LAN_GetServerInfo
                  (GHIDRA_FIELD(ui_netSource, 12, 4),*(uint32_t *)(&g_dat_003e13c0 + param_1 * 4),info_10613,0x400
                  );
        lastTime_10618 = g_dat_00397fdc;
        lastColumn_10617 = param_2;
      }
      tmp_pc11 = (char *)Info_ValueForKey(info_10613,&g_dat_000559fb);
      tmp_l2 = strtol(tmp_pc11,(char **)0x0,10);
      switch(param_2) {
      case 0:
        if (tmp_l2 < 1) {
          tmp_pc11 = (char *)Info_ValueForKey(info_10613,&g_dat_00055aca);
          return tmp_pc11;
        }
        if (GHIDRA_FIELD(ui_netSource, 12, 4) == 0) {
          tmp_pc11 = (char *)Info_ValueForKey(info_10613,"nettype");
          tmp_l2 = strtol(tmp_pc11,(char **)0x0,10);
          tmp_u9 = *(uint32_t *)(netnames + tmp_l2 * 4);
          tmp_u10 = Info_ValueForKey(info_10613,"hostname");
          Com_sprintf(hostname_10614,0x400,&g_dat_00055ad7,tmp_u10,tmp_u9);
          return hostname_10614;
        }
        tmp_pc11 = (char *)Info_ValueForKey(info_10613,"hostname");
        return tmp_pc11;
      case 1:
        tmp_pc11 = (char *)Info_ValueForKey(info_10613,"mapname");
        return tmp_pc11;
      case 2:
        tmp_i13 = *(int *)(&g_dat_003ea078 + *(int *)(&g_dat_003e13c0 + param_1 * 4) * 4);
        tmp_i1 = *(int *)(&g_dat_003e9078 + *(int *)(&g_dat_003e13c0 + param_1 * 4) * 4);
        if (tmp_i13 != tmp_i1) {
          tmp_u9 = Info_ValueForKey(info_10613,"sv_maxclients");
          Com_sprintf(clientBuff_10615,0x20,"^7%i^9(+%i)/%s",tmp_i1,tmp_i13 - tmp_i1,tmp_u9);
          return clientBuff_10615;
        }
        tmp_u9 = Info_ValueForKey(info_10613,"sv_maxclients");
        Com_sprintf(clientBuff_10615,0x20,"^7%i^9/%s",tmp_i13,tmp_u9);
        return clientBuff_10615;
      case 3:
        tmp_pc11 = (char *)Info_ValueForKey(info_10613,"gametype");
        tmp_l4 = strtol(tmp_pc11,(char **)0x0,10);
        if (((-1 < tmp_l4) && (0 < tmp_l2)) && (tmp_l4 < g_dat_003b8b48)) {
          if (tmp_l4 == 6) {
            return "Vote";
          }
          if (tmp_l4 < 7) {
            if (tmp_l4 == 5) {
              return "LMS";
            }
          }
          else {
            if (tmp_l4 == 7) {
              return "TDM";
            }
            if (tmp_l4 == 8) {
              return "DM";
            }
          }
          if (g_dat_003b8b48 < 1) {
            tmp_i13 = 0;
          }
          else {
            if (tmp_l4 == g_dat_003b8b54) {
              tmp_i13 = 0;
LAB_00026d28:
              return (char *)(&g_dat_00397ed0)[(tmp_i13 + 0x20c8) * 4];
            }
            if (g_dat_003b8b48 == 1) {
              tmp_i13 = 1;
            }
            else {
              if (tmp_l4 == g_dat_003b8b64) {
                tmp_i13 = 1;
                goto LAB_00026d28;
              }
              if (g_dat_003b8b48 == 2) {
                tmp_i13 = 2;
              }
              else {
                if (tmp_l4 == g_dat_003b8b74) {
                  tmp_i13 = 2;
                  goto LAB_00026d28;
                }
                if (g_dat_003b8b48 == 3) {
                  tmp_i13 = 3;
                }
                else {
                  if (tmp_l4 == g_dat_003b8b84) {
                    tmp_i13 = 3;
                    goto LAB_00026d28;
                  }
                  if (g_dat_003b8b48 == 4) {
                    tmp_i13 = 4;
                  }
                  else {
                    if (tmp_l4 == g_dat_003b8b94) {
                      tmp_i13 = 4;
                      goto LAB_00026d28;
                    }
                    if (g_dat_003b8b48 == 5) {
                      tmp_i13 = 5;
                    }
                    else {
                      if (tmp_l4 == g_dat_003b8ba4) {
                        tmp_i13 = 5;
                        goto LAB_00026d28;
                      }
                      if (g_dat_003b8b48 == 6) {
                        tmp_i13 = 6;
                      }
                      else {
                        if (tmp_l4 == g_dat_003b8bb4) {
                          tmp_i13 = 6;
                          goto LAB_00026d28;
                        }
                        if (g_dat_003b8b48 == 7) {
                          tmp_i13 = 7;
                        }
                        else {
                          if (tmp_l4 == g_dat_003b8bc4) {
                            tmp_i13 = 7;
                            goto LAB_00026d28;
                          }
                          if (g_dat_003b8b48 == 8) {
                            tmp_i13 = 8;
                          }
                          else {
                            if (tmp_l4 == g_dat_003b8bd4) {
                              tmp_i13 = 8;
                              goto LAB_00026d28;
                            }
                            if (g_dat_003b8b48 == 9) {
                              tmp_i13 = 9;
                            }
                            else {
                              if (tmp_l4 == g_dat_003b8be4) {
                                tmp_i13 = 9;
                                goto LAB_00026d28;
                              }
                              if (g_dat_003b8b48 == 10) {
                                tmp_i13 = 10;
                              }
                              else {
                                if (tmp_l4 == g_dat_003b8bf4) {
                                  tmp_i13 = 10;
                                  goto LAB_00026d28;
                                }
                                if (g_dat_003b8b48 == 0xb) {
                                  tmp_i13 = 0xb;
                                }
                                else {
                                  if (tmp_l4 == g_dat_003b8c04) {
                                    tmp_i13 = 0xb;
                                    goto LAB_00026d28;
                                  }
                                  if (g_dat_003b8b48 == 0xc) {
                                    tmp_i13 = 0xc;
                                  }
                                  else {
                                    if (tmp_l4 == g_dat_003b8c14) {
                                      tmp_i13 = 0xc;
                                      goto LAB_00026d28;
                                    }
                                    if (g_dat_003b8b48 == 0xd) {
                                      tmp_i13 = 0xd;
                                    }
                                    else {
                                      if (tmp_l4 == g_dat_003b8c24) {
                                        tmp_i13 = 0xd;
                                        goto LAB_00026d28;
                                      }
                                      if (g_dat_003b8b48 == 0xe) {
                                        tmp_i13 = 0xe;
                                      }
                                      else {
                                        if (tmp_l4 == g_dat_003b8c34) {
                                          tmp_i13 = 0xe;
                                          goto LAB_00026d28;
                                        }
                                        if (g_dat_003b8b48 == 0xf) {
                                          tmp_i13 = 0xf;
                                        }
                                        else {
                                          if (tmp_l4 == g_dat_003b8c44) {
                                            tmp_i13 = 0xf;
                                            goto LAB_00026d28;
                                          }
                                          tmp_i13 = 0x10;
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
          if (g_dat_003b8b48 != tmp_i13) goto LAB_00026410;
        }
        return "???";
      case 4:
        if (tmp_l2 < 1) {
          return "...";
        }
LAB_00026410:
        tmp_pc11 = (char *)Info_ValueForKey(info_10613,"serverload");
        tmp_l4 = strtol(tmp_pc11,(char **)0x0,10);
        if (tmp_l4 == -1) {
          tmp_pc11 = " %3i";
        }
        else if (tmp_l4 < 0x4c) {
          if (tmp_l4 < 0x29) {
            tmp_pc11 = "^2 %3i";
          }
          else {
            tmp_pc11 = "^3 %3i";
          }
        }
        else {
          tmp_pc11 = "^1 %3i";
        }
        Com_sprintf(pingstr_10616,10,tmp_pc11,tmp_l2);
        return pingstr_10616;
      case 5:
        if (tmp_l2 < 1) {
          *param_5 = 0;
          return "";
        }
        *param_5 = 8;
        tmp_pc11 = (char *)Info_ValueForKey(info_10613,"needpass");
        tmp_l2 = strtol(tmp_pc11,(char **)0x0,10);
        tmp_pc11 = (char *)Info_ValueForKey(info_10613,"friendlyFire");
        tmp_u3 = strtol(tmp_pc11,(char **)0x0,10);
        tmp_pc11 = (char *)Info_ValueForKey(info_10613,"maxlives");
        tmp_l4 = strtol(tmp_pc11,(char **)0x0,10);
        tmp_pc11 = (char *)Info_ValueForKey(info_10613,"punkbuster");
        tmp_l5 = strtol(tmp_pc11,(char **)0x0,10);
        tmp_pc11 = (char *)Info_ValueForKey(info_10613,"weaprestrict");
        tmp_l6 = strtol(tmp_pc11,(char **)0x0,10);
        tmp_pc11 = (char *)Info_ValueForKey(info_10613,"g_antilag");
        tmp_l7 = strtol(tmp_pc11,(char **)0x0,10);
        tmp_pc11 = (char *)Info_ValueForKey(info_10613,"balancedteams");
        tmp_l8 = strtol(tmp_pc11,(char **)0x0,10);
        tmp_i13 = *(int *)(&g_dat_003e8078 + *(int *)(&g_dat_003e13c0 + param_1 * 4) * 4);
        tmp_u9 = 0xffffffff;
        if (tmp_l2 != 0) {
          tmp_u9 = g_dat_003e8054;
        }
        *param_4 = tmp_u9;
        tmp_u9 = 0xffffffff;
        if ((tmp_u3 & 1) != 0) {
          tmp_u9 = g_dat_003e8058;
        }
        param_4[1] = tmp_u9;
        tmp_u9 = 0xffffffff;
        if (tmp_l4 != 0) {
          tmp_u9 = g_dat_003e805c;
        }
        param_4[2] = tmp_u9;
        tmp_u9 = 0xffffffff;
        if (tmp_l5 != 0) {
          tmp_u9 = g_dat_003e8060;
        }
        param_4[3] = tmp_u9;
        tmp_u9 = 0xffffffff;
        if (tmp_l6 < 100) {
          tmp_u9 = g_dat_003e8064;
        }
        param_4[4] = tmp_u9;
        tmp_u9 = 0xffffffff;
        if (tmp_l7 != 0) {
          tmp_u9 = g_dat_003e8068;
        }
        param_4[5] = tmp_u9;
        tmp_u9 = 0xffffffff;
        if (tmp_l8 != 0) {
          tmp_u9 = g_dat_003e806c;
        }
        param_4[6] = tmp_u9;
        if (tmp_i13 != 0) {
          param_4[7] = g_dat_003e8070;
          return "";
        }
        param_4[7] = 0xffffffff;
        return "";
      case 6:
        *param_5 = 1;
        tmp_i13 = trap_LAN_ServerIsInFavoriteList
                           (GHIDRA_FIELD(ui_netSource, 12, 4),*(uint32_t *)(&g_dat_003e13c0 + param_1 * 4));
        if (tmp_i13 != 0) {
          *param_4 = g_dat_003b61c8;
          return "";
        }
        *param_4 = g_dat_003b61cc;
        return "";
      }
    }
  }
  else if (param_3 == 13.0) {
    if (((-1 < param_1) && (param_1 < g_dat_003e693c)) && (param_2 < 4)) {
      return (char *)(&g_dat_00397ecc)[param_2 + 0x1366c + param_1 * 4];
    }
  }
  else if (param_3 == 14.0) {
    if ((-1 < param_1) && (param_1 < g_dat_003e7e0c)) {
      return (char *)(&g_dat_00397ec8 + (param_1 + 0x13ed) * 0x10);
    }
  }
  else if (param_3 == 7.0) {
    if ((-1 < param_1) && (param_1 < g_dat_003b8d54)) {
      return &g_dat_003b8d6c + param_1 * 0x48;
    }
  }
  else if (param_3 == 8.0) {
    if ((-1 < param_1) && (param_1 < g_dat_003b8d58)) {
      return &g_dat_003ba16c + param_1 * 0x24;
    }
  }
  else if (param_3 == 9.0) {
    if ((-1 < param_1) && (param_1 < g_dat_003e0790)) {
      tmp_i13 = param_1 * 0x48;
      if ((&g_dat_003df594)[tmp_i13] != '\0') {
        return &g_dat_003df594 + tmp_i13;
      }
      tmp_pc11 = *(char **)(&g_dat_003df5d4 + tmp_i13);
      if ((tmp_pc11 != (char *)0x0) && (*tmp_pc11 != '\0')) {
        return tmp_pc11;
      }
      return *(char **)(&g_dat_003df590 + param_1 * 0x48);
    }
  }
  else if (param_3 == 15.0) {
    if ((-1 < param_1) && (param_1 < g_dat_003e13a0)) {
      return *(char **)(&g_dat_003e0fa0 + param_1 * 4);
    }
  }
  else if (param_3 == 10.0) {
    if ((-1 < param_1) && (param_1 < g_dat_003e0f98)) {
      return *(char **)(&g_dat_003e0798 + param_1 * 4);
    }
  }
  else if ((param_3 == 28.0) && (-1 < param_1)) {
    if (g_dat_003df584 <= param_1) {
      return "";
    }
    param_1 = param_1 + 0x8e98;
    Q_strncpyz(local_11c,(&g_dat_00397ec4)[param_1 * 2],0x100);
    Q_CleanStr(local_11c);
    Q_CleanDirName(local_11c);
    tmp_i13 = Q_stricmp(local_11c,0x396610);
    if (tmp_i13 == 0) {
      tmp_i13 = Q_stricmp(local_11c,0x3951d0);
      if (tmp_i13 == 0) {
        tmp_pc11 = (char *)va("^7(Default) %s",(&g_dat_00397ec4)[param_1 * 2]);
        return tmp_pc11;
      }
      tmp_pc11 = (char *)va(&g_dat_00055b27,(&g_dat_00397ec4)[param_1 * 2]);
      return tmp_pc11;
    }
    tmp_i13 = Q_stricmp(local_11c,0x3951d0);
    if (tmp_i13 != 0) {
      return (char *)(&g_dat_00397ec4)[param_1 * 2];
    }
    tmp_pc11 = (char *)va("(Default) %s",(char *)(&g_dat_00397ec4)[param_1 * 2]);
    return tmp_pc11;
  }
  return "";
}

byte * Text_AutoWrap_Paint_Chunk_constprop_56
          (int param_1,uint32_t *param_2,float param_3,uint32_t param_4,float param_5,
          byte *param_6,float param_7,uint32_t param_8,uint32_t *param_9)

{
  float tmp_f1;
  byte tmp_b2;
  byte tmp_b3;
  float tmp_f4;
  float tmp_f5;
  size_t tmp_s6;
  int tmp_i7;
  byte *tmp_pb8;
  int tmp_i9;
  int tmp_i10;
  byte *local_3c;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  tmp_i9 = g_dat_003e7e2c * 0x5044;
  tmp_f1 = *(float *)(&g_dat_0039cffc + tmp_i9);
  if (param_6 != (byte *)0x0) {
    trap_R_SetColor(param_2);
    tmp_s6 = strlen((char *)param_6);
    local_3c = (byte *)0x0;
    tmp_i10 = 0;
    tmp_pb8 = param_6;
    tmp_f4 = param_3;
    do {
      tmp_b2 = *tmp_pb8;
      if ((tmp_b2 == 0) || ((int)tmp_s6 <= tmp_i10)) break;
      if (((byte)(tmp_b2 - 9) < 2) || (tmp_b2 == 0x20)) {
        local_3c = tmp_pb8;
      }
      if (tmp_b2 < 0x14) {
LAB_00026fc1:
        tmp_pb8 = tmp_pb8 + 1;
        tmp_i10 = tmp_i10 + 1;
      }
      else {
        if (tmp_b2 != 0x5e) {
LAB_00026f86:
          tmp_f5 = (float)*(int *)(&g_dat_0039800c + (uint)tmp_b2 * 0x50 + tmp_i9) * param_5 * tmp_f1;
          if ((float)param_1 + param_3 < tmp_f5 + tmp_f4 + param_7) {
            if (local_3c != (byte *)0x0) {
              return local_3c + 1;
            }
            return tmp_pb8;
          }
          tmp_f4 = tmp_f5 + param_7 + tmp_f4;
          goto LAB_00026fc1;
        }
        tmp_b3 = tmp_pb8[1];
        if ((tmp_b3 == 0) || (tmp_b3 == 0x5e)) goto LAB_00026f86;
        if (tmp_b3 == 0x2a) {
          local_2c = *param_2;
          local_28 = param_2[1];
          local_24 = param_2[2];
          local_20 = param_2[3];
        }
        else {
          tmp_i7 = ((int)(char)tmp_b3 - 0x30U & 0x1f) * 0x10;
          local_2c = *(uint32_t *)(g_color_table + tmp_i7);
          local_28 = *(uint32_t *)(g_color_table + tmp_i7 + 4);
          local_24 = *(uint32_t *)(g_color_table + tmp_i7 + 8);
          local_20 = param_2[3];
        }
        if (param_9 != (uint32_t *)0x0) {
          *param_9 = local_2c;
          param_9[1] = local_28;
          param_9[2] = local_24;
          param_9[3] = local_20;
        }
        tmp_pb8 = tmp_pb8 + 2;
      }
    } while (tmp_pb8 != (byte *)0x0);
  }
  tmp_s6 = strlen((char *)param_6);
  return param_6 + tmp_s6;
}

void _UI_SetActiveMenu_constprop_61(void)

{
  int tmp_i1;
  
  tmp_i1 = Menu_Count();
  if (0 < tmp_i1) {
    menutype = 6;
  }
  return;
}

void Text_Paint_Ext(float param_1,float param_2,float param_3,float param_4,uint32_t *param_5,
                   byte *param_6,float param_7,size_t param_8,int param_9,int param_10)

{
  int *tmp_pi1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  byte tmp_b7;
  byte tmp_b8;
  uint32_t tmp_u9;
  float tmp_f10;
  size_t tmp_s11;
  int tmp_i12;
  int tmp_i13;
  int local_78;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  param_3 = param_3 * *(float *)(param_10 + 0x5000);
  param_4 = param_4 * *(float *)(param_10 + 0x5000);
  if (param_6 != (byte *)0x0) {
    trap_R_SetColor(param_5);
    local_2c = *param_5;
    local_28 = param_5[1];
    local_24 = param_5[2];
    local_20 = param_5[3];
    tmp_s11 = strlen((char *)param_6);
    if (((int)tmp_s11 <= (int)param_8) || ((int)param_8 < 1)) {
      param_8 = tmp_s11;
    }
    local_78 = 0;
    do {
      tmp_b7 = *param_6;
      if ((tmp_b7 == 0) || ((int)param_8 <= local_78)) break;
      if (tmp_b7 < 0x14) {
LAB_000272f3:
        local_78 = local_78 + 1;
        param_6 = param_6 + 1;
      }
      else {
        if (tmp_b7 != 0x5e) {
LAB_00027329:
          tmp_i12 = (uint)tmp_b7 * 0x50;
          tmp_i13 = param_10 + tmp_i12;
          tmp_f10 = (float)*(int *)(tmp_i13 + 4) * param_4;
          if (param_9 == 6 || param_9 == 3) {
            GHIDRA_FIELD(colorBlack, 12, 4) = local_20;
            trap_R_SetColor(colorBlack);
            tmp_pu2 = (uint32_t *)(param_10 + 0x20 + tmp_i12);
            tmp_u3 = tmp_pu2[2];
            tmp_u9 = tmp_pu2[3];
            tmp_u4 = tmp_pu2[1];
            tmp_u5 = *tmp_pu2;
            tmp_i12 = param_10 + 0x10 + tmp_i12;
            tmp_u6 = *(uint32_t *)(tmp_i12 + 0xc);
            local_48 = (float)(int)(~-(uint)(param_9 != 3) + 2);
            local_4c = (float)*(int *)(tmp_i13 + 0xc) * param_3 + param_1 + local_48;
            local_48 = local_48 + (param_2 - tmp_f10);
            local_44 = param_3 * (float)*(int *)(tmp_i12 + 4);
            local_40 = (float)*(int *)(tmp_i12 + 8) * param_4;
            UI_AdjustFrom640(&local_4c,&local_48,&local_44,&local_40);
            trap_R_DrawStretchPic(local_4c,local_48,local_44,local_40,tmp_u6,tmp_u5,tmp_u4,tmp_u3,tmp_u9)
            ;
            trap_R_SetColor(&local_2c);
            GHIDRA_FIELD(colorBlack, 12, 4) = 0x3f800000;
          }
          local_38 = param_2 - tmp_f10;
          tmp_i12 = (uint)tmp_b7 * 0x50;
          tmp_pu2 = (uint32_t *)(param_10 + 0x20 + tmp_i12);
          tmp_u3 = tmp_pu2[2];
          tmp_pi1 = (int *)(param_10 + 0x10 + tmp_i12);
          tmp_u6 = tmp_pu2[3];
          tmp_u4 = tmp_pu2[1];
          tmp_u5 = *tmp_pu2;
          tmp_i12 = tmp_pi1[3];
          local_3c = (float)*(int *)(tmp_i13 + 0xc) * param_3 + param_1;
          local_34 = (float)tmp_pi1[1] * param_3;
          local_30 = (float)tmp_pi1[2] * param_4;
          UI_AdjustFrom640(&local_3c,&local_38,&local_34,&local_30);
          trap_R_DrawStretchPic(local_3c,local_38,local_34,local_30,tmp_i12,tmp_u5,tmp_u4,tmp_u3,tmp_u6);
          param_1 = (float)*tmp_pi1 * param_3 + param_7 + param_1;
          goto LAB_000272f3;
        }
        tmp_b8 = param_6[1];
        if ((tmp_b8 == 0) || (tmp_b8 == 0x5e)) goto LAB_00027329;
        if (tmp_b8 == 0x2a) {
          local_2c = *param_5;
          local_28 = param_5[1];
          local_24 = param_5[2];
          local_20 = param_5[3];
        }
        else {
          tmp_i12 = ((int)(char)tmp_b8 - 0x30U & 0x1f) * 0x10;
          local_2c = *(uint32_t *)(g_color_table + tmp_i12);
          local_28 = *(uint32_t *)(g_color_table + tmp_i12 + 4);
          local_24 = *(uint32_t *)(g_color_table + tmp_i12 + 8);
          local_20 = param_5[3];
        }
        param_6 = param_6 + 2;
        trap_R_SetColor(&local_2c);
      }
    } while (param_6 != (byte *)0x0);
    trap_R_SetColor(0);
  }
  return;
}

void Text_Paint(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8)

{
  Text_Paint_Ext(param_1,param_2,param_3,param_3,param_4,param_5,param_6,param_7,param_8,
                 &g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
  return;
}

char * UI_FeederItemText(float param_1,int param_2,uint32_t param_3,uint32_t param_4,
                        uint32_t *param_5)

{
  char *tmp_pc1;
  byte *tmp_pb2;
  int tmp_i3;
  int tmp_i4;
  
  *param_5 = 0;
  if (param_1 == 0.0) {
    if ((-1 < param_2) && (param_2 < g_dat_003b7f38)) {
      return (char *)(&uiInfo)[(param_2 + 0x2008) * 4];
    }
  }
  else {
    if ((param_1 != 4.0) && (param_1 != 1.0)) {
      param_3 = param_5;
      tmp_pc1 = (char *)UI_FeederItemText_part_33();
      return tmp_pc1;
    }
    if (GHIDRA_FIELD(ui_netGameType, 12, 4) == 4) {
      if (0 < g_dat_003bab6c) {
        tmp_pb2 = &g_dat_003cabe4;
        tmp_i3 = 0;
        tmp_i4 = 0;
        do {
          if ((*tmp_pb2 & 4) != 0) {
            if (param_2 == tmp_i4) {
              return (char *)(&g_dat_003cab78)[tmp_i3 * 0x1d];
            }
            tmp_i4 = tmp_i4 + 1;
          }
          tmp_i3 = tmp_i3 + 1;
          tmp_pb2 = tmp_pb2 + 0x74;
        } while (tmp_i3 != g_dat_003bab6c);
      }
    }
    else {
      tmp_i4 = 0;
      tmp_i3 = 0;
      if (0 < g_dat_003bab6c) {
        do {
          if (*(int *)(&g_dat_003babcc + tmp_i3 * 0x80) != 0) {
            if (param_2 == tmp_i4) {
              return *(char **)(&g_dat_003bab70 + tmp_i3 * 0x80);
            }
            tmp_i4 = tmp_i4 + 1;
          }
          tmp_i3 = tmp_i3 + 1;
        } while (tmp_i3 != g_dat_003bab6c);
      }
    }
  }
  return "";
}

void _UI_DrawRect(float param_1,float param_2,float param_3,float param_4,float param_5,
                 uint32_t param_6)

{
  float tmp_f1;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10 [3];
  
  trap_R_SetColor(param_6);
  local_2c = param_1;
  local_28 = param_2;
  local_24 = param_3;
  local_20 = param_4;
  UI_AdjustFrom640(&local_2c,&local_28,&local_24,&local_20);
  tmp_f1 = param_5 * g_dat_00397fd0;
  trap_R_DrawStretchPic(local_2c,local_28,local_24,tmp_f1,0,0,0,0,g_dat_003b7f10);
  trap_R_DrawStretchPic(local_2c,(local_28 + local_20) - tmp_f1,local_24,tmp_f1,0,0,0,0,g_dat_003b7f10);
  local_1c = param_1;
  local_18 = param_2;
  local_14 = param_3;
  local_10[0] = param_4;
  UI_AdjustFrom640(&local_1c,&local_18,&local_14,local_10);
  param_5 = param_5 * g_dat_00397fd4;
  trap_R_DrawStretchPic(local_1c,local_18,param_5,local_10[0],0,0,0,0,g_dat_003b7f10);
  trap_R_DrawStretchPic
            ((local_1c + local_14) - param_5,local_18,param_5,local_10[0],0,0,0,0,g_dat_003b7f10);
  trap_R_SetColor(0);
  return;
}

int UI_FeederItemImage(float param_1,int param_2)

{
  bool tmp_b1;
  int *tmp_pi2;
  int tmp_i3;
  int tmp_i4;
  byte *tmp_pb5;
  
  if (param_1 == 0.0) {
    if (param_2 < 0) {
      return 0;
    }
    if (g_dat_003b7f38 <= param_2) {
      return 0;
    }
    param_2 = param_2 + 0x2008;
    if ((&g_dat_00397ec8)[param_2 * 4] != -1) {
      return (&g_dat_00397ec8)[param_2 * 4];
    }
    tmp_i3 = trap_R_RegisterShaderNoMip((&g_dat_00397ec4)[param_2 * 4]);
    (&g_dat_00397ec8)[param_2 * 4] = tmp_i3;
    return tmp_i3;
  }
  tmp_b1 = true;
  if ((param_1 != 1.0) && (tmp_b1 = false, param_1 != 4.0)) {
    if ((param_1 != 26.0) && (param_1 != 27.0)) {
      return 0;
    }
    if (g_dat_003cab70 < 1) {
      return 0;
    }
    tmp_pi2 = &g_dat_003cabe0;
    tmp_i3 = 0;
    while ((param_2 != *tmp_pi2 || (tmp_pi2[-3] == 0))) {
      tmp_i3 = tmp_i3 + 1;
      tmp_pi2 = tmp_pi2 + 0x1d;
      if (tmp_i3 == g_dat_003cab70) {
        tmp_i3 = 0;
LAB_00027b22:
        if ((&g_dat_003cabd0)[tmp_i3 * 0x1d] != -1) {
          return (&g_dat_003cabd0)[tmp_i3 * 0x1d];
        }
        tmp_i4 = trap_R_RegisterShaderNoMip(*(uint32_t *)(&g_dat_003cab74 + tmp_i3 * 0x74));
        (&g_dat_003cabd0)[tmp_i3 * 0x1d] = tmp_i4;
        return tmp_i4;
      }
    }
    if (tmp_i3 < 0) {
      return 0;
    }
    goto LAB_00027b22;
  }
  if (GHIDRA_FIELD(ui_netGameType, 12, 4) == 4) {
    if (0 < g_dat_003bab6c) {
      tmp_pb5 = &g_dat_003cabe4;
      tmp_i4 = 0;
      tmp_i3 = 0;
      do {
        if ((*tmp_pb5 & 4) != 0) {
          if (param_2 == tmp_i4) {
            if (!tmp_b1) goto LAB_00027c17;
            goto LAB_00027bec;
          }
          tmp_i4 = tmp_i4 + 1;
        }
        tmp_i3 = tmp_i3 + 1;
        tmp_pb5 = tmp_pb5 + 0x74;
      } while (tmp_i3 != g_dat_003bab6c);
    }
    if (!tmp_b1) {
      tmp_i3 = 0;
      goto LAB_00027ba6;
    }
  }
  else {
    tmp_i4 = 0;
    tmp_i3 = 0;
    if (g_dat_003bab6c < 1) {
      if (!tmp_b1) {
        return 0;
      }
    }
    else {
      do {
        if (*(int *)(&g_dat_003babcc + tmp_i3 * 0x80) != 0) {
          if (param_2 == tmp_i4) {
            if (tmp_b1) goto LAB_00027bec;
            goto LAB_00027c04;
          }
          tmp_i4 = tmp_i4 + 1;
        }
        tmp_i3 = tmp_i3 + 1;
      } while (tmp_i3 != g_dat_003bab6c);
      tmp_i3 = 0;
      if (!tmp_b1) goto LAB_00027a62;
    }
  }
  tmp_i3 = 0;
  if ((&g_dat_00397ed4)[(GHIDRA_FIELD(ui_gameType, 12, 4) + 0x20c8) * 4] == 4) goto LAB_00027ba6;
LAB_00027a58:
  if (g_dat_003bab6c <= tmp_i3) {
    return 0;
  }
LAB_00027a62:
  tmp_i4 = (&g_dat_00397ec8)[(tmp_i3 + 0x45a) * 0x20];
  if (tmp_i4 == -1) {
    tmp_i4 = trap_R_RegisterShaderNoMip(*(uint32_t *)(&g_dat_003bab78 + tmp_i3 * 0x80));
    (&g_dat_00397ec8)[(tmp_i3 + 0x45a) * 0x20] = tmp_i4;
  }
  return tmp_i4;
LAB_00027bec:
  if ((&g_dat_00397ed4)[(GHIDRA_FIELD(ui_gameType, 12, 4) + 0x20c8) * 4] == 4) {
LAB_00027c17:
    if (tmp_i3 < 0) {
      return 0;
    }
LAB_00027ba6:
    if (g_dat_003cab70 <= tmp_i3) {
      return 0;
    }
    if ((&g_dat_003cabd0)[tmp_i3 * 0x1d] != -1) {
      return (&g_dat_003cabd0)[tmp_i3 * 0x1d];
    }
    tmp_i4 = trap_R_RegisterShaderNoMip(*(uint32_t *)(&g_dat_003cab74 + tmp_i3 * 0x74));
    (&g_dat_003cabd0)[tmp_i3 * 0x1d] = tmp_i4;
    return tmp_i4;
  }
LAB_00027c04:
  if (tmp_i3 < 0) {
    return 0;
  }
  goto LAB_00027a58;
}

int Text_Height(byte *param_1,float param_2,size_t param_3)

{
  byte tmp_b1;
  float tmp_f2;
  int tmp_i3;
  float tmp_f4;
  size_t tmp_s5;
  int tmp_i6;
  
  tmp_i3 = g_dat_003e7e2c;
  if (param_1 == (byte *)0x0) {
    tmp_f2 = 0.0;
  }
  else {
    tmp_s5 = strlen((char *)param_1);
    if (((int)tmp_s5 <= (int)param_3) || ((int)param_3 < 1)) {
      param_3 = tmp_s5;
    }
    tmp_i6 = 0;
    tmp_f2 = 0.0;
    do {
      while( true ) {
        tmp_b1 = *param_1;
        if ((tmp_b1 == 0) || ((int)param_3 <= tmp_i6)) goto LAB_00027cf0;
        if ((tmp_b1 != 0x5e) || ((param_1[1] == 0 || (param_1[1] == 0x5e)))) break;
        param_1 = param_1 + 2;
        if (param_1 == (byte *)0x0) goto LAB_00027cf0;
      }
      tmp_f4 = (float)*(int *)(&g_dat_00397ffc + (uint)tmp_b1 * 0x50 + tmp_i3 * 0x5044);
      if ((float)*(int *)(&g_dat_00397ffc + (uint)tmp_b1 * 0x50 + tmp_i3 * 0x5044) <= tmp_f2) {
        tmp_f4 = tmp_f2;
      }
      tmp_f2 = tmp_f4;
      param_1 = param_1 + 1;
      tmp_i6 = tmp_i6 + 1;
    } while (param_1 != (byte *)0x0);
  }
LAB_00027cf0:
  return (int)ROUND(tmp_f2 * param_2 * *(float *)(&g_dat_0039cffc + tmp_i3 * 0x5044));
}

void UI_ParseGameInfo_constprop_57(void)

{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  uint8_t *local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0x27d5b;
  tmp_i1 = trap_FS_FOpenFile("gameinfo.txt",local_20,0);
  if (local_20[0] == (uint8_t *)0x0) {
    tmp_u3 = va("^1menu file not found: %s, using default\n","gameinfo.txt");
    trap_Print(tmp_u3);
  }
  else {
    if (tmp_i1 < 0x8000) {
      trap_FS_Read(buf_9500,tmp_i1,local_20[0]);
      buf_9500[tmp_i1] = 0;
      trap_FS_FCloseFile(local_20[0]);
      local_20[0] = buf_9500;
      goto LAB_00027e0d;
    }
    tmp_u3 = va("^1menu file too large: %s is %i, max allowed is %i","gameinfo.txt",tmp_i1,0x8000);
    trap_Print(tmp_u3);
    trap_FS_FCloseFile(local_20[0]);
  }
  local_20[0] = defaultMenu;
  if (defaultMenu == (uint8_t *)0x0) {
    return;
  }
LAB_00027e0d:
  do {
    do {
      tmp_pc2 = (char *)COM_ParseExt(local_20,1);
      if (tmp_pc2 == (char *)0x0) {
        return;
      }
      if (*tmp_pc2 == '\0') {
        return;
      }
      if (*tmp_pc2 == '}') {
        return;
      }
      tmp_i1 = Q_stricmp(tmp_pc2,&g_dat_00055b39);
      if (tmp_i1 == 0) {
        return;
      }
      tmp_i1 = Q_stricmp(tmp_pc2,"gametypes");
    } while (tmp_i1 != 0);
    tmp_pc2 = (char *)COM_ParseExt(local_20,1);
    if (*tmp_pc2 != '{') {
      return;
    }
    g_dat_003b8b48 = 0;
    while( true ) {
      tmp_pc2 = (char *)COM_ParseExt(local_20,1);
      tmp_i1 = Q_stricmp(tmp_pc2,&g_dat_00055b39);
      if (tmp_i1 == 0) break;
      if (tmp_pc2 == (char *)0x0) {
        return;
      }
      if (*tmp_pc2 == '\0') {
        return;
      }
      if (*tmp_pc2 == '{') {
        tmp_i1 = Int_Parse(local_20,&g_dat_00397ed4 + (g_dat_003b8b48 + 0x20c8) * 4);
        if (tmp_i1 == 0) {
          return;
        }
        tmp_i1 = String_Parse(local_20,&g_dat_00397ecc + (g_dat_003b8b48 + 0x20c8) * 4);
        if (tmp_i1 == 0) {
          return;
        }
        tmp_i1 = String_Parse(local_20,&g_dat_00397ed0 + (g_dat_003b8b48 + 0x20c8) * 4);
        if (tmp_i1 == 0) {
          return;
        }
        tmp_i1 = String_Parse(local_20,&g_dat_00397ed8 + (g_dat_003b8b48 + 0x20c8) * 4);
        if (tmp_i1 == 0) {
          return;
        }
        if (g_dat_003b8b48 < 0x10) {
          g_dat_003b8b48 = g_dat_003b8b48 + 1;
        }
        else {
          Com_Printf("Too many game types, last one replace!\n");
        }
        tmp_pc2 = (char *)COM_ParseExt(local_20,1);
        if (*tmp_pc2 != '}') {
          return;
        }
      }
    }
  } while( true );
}

int Text_Width(byte *param_1,float param_2,size_t param_3)

{
  byte tmp_b1;
  float tmp_f2;
  int tmp_i3;
  size_t tmp_s4;
  int tmp_i5;
  
  tmp_i3 = g_dat_003e7e2c;
  if (param_1 == (byte *)0x0) {
    tmp_f2 = 0.0;
  }
  else {
    tmp_s4 = strlen((char *)param_1);
    if (((int)tmp_s4 <= (int)param_3) || ((int)param_3 < 1)) {
      param_3 = tmp_s4;
    }
    tmp_i5 = 0;
    tmp_f2 = 0.0;
    do {
      while( true ) {
        tmp_b1 = *param_1;
        if ((tmp_b1 == 0) || ((int)param_3 <= tmp_i5)) goto LAB_000280d0;
        if ((tmp_b1 != 0x5e) || ((param_1[1] == 0 || (param_1[1] == 0x5e)))) break;
        param_1 = param_1 + 2;
        if (param_1 == (byte *)0x0) goto LAB_000280d0;
      }
      param_1 = param_1 + 1;
      tmp_i5 = tmp_i5 + 1;
      tmp_f2 = (float)*(int *)(&g_dat_0039800c + (uint)tmp_b1 * 0x50 + tmp_i3 * 0x5044) + tmp_f2;
    } while (param_1 != (byte *)0x0);
  }
LAB_000280d0:
  return (int)ROUND(tmp_f2 * param_2 * *(float *)(&g_dat_0039cffc + tmp_i3 * 0x5044));
}

void Text_Paint_Limit_constprop_55
          (float *param_1,uint32_t *param_2,float param_3,float param_4,float param_5,
          byte *param_6,size_t param_7)

{
  int tmp_i1;
  float tmp_f2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  byte tmp_b7;
  byte tmp_b8;
  uint32_t tmp_u9;
  float tmp_f10;
  int tmp_i11;
  size_t tmp_s12;
  uint tmp_u13;
  size_t tmp_s14;
  int tmp_i15;
  int tmp_i16;
  byte *tmp_pb17;
  int local_6c;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  tmp_i11 = g_dat_003e7e2c;
  if (param_6 != (byte *)0x0) {
    tmp_f2 = *param_1;
    param_5 = param_5 * *(float *)(&g_dat_0039cffc + g_dat_003e7e2c * 0x5044);
    trap_R_SetColor(param_2);
    tmp_s12 = strlen((char *)param_6);
    if (((int)tmp_s12 <= (int)param_7) || ((int)param_7 < 1)) {
      param_7 = tmp_s12;
    }
    local_6c = 0;
    do {
      tmp_i16 = g_dat_003e7e2c;
      tmp_b7 = *param_6;
      if ((tmp_b7 == 0) || ((int)param_7 <= local_6c)) break;
      tmp_u13 = (uint)tmp_b7;
      if (tmp_b7 == 0x5e) {
        tmp_b8 = param_6[1];
        if ((tmp_b8 == 0) || (tmp_b8 == 0x5e)) goto LAB_00028203;
        if (tmp_b8 == 0x2a) {
          local_2c = *param_2;
          local_28 = param_2[1];
          local_24 = param_2[2];
          local_20 = param_2[3];
        }
        else {
          tmp_i16 = ((int)(char)tmp_b8 - 0x30U & 0x1f) * 0x10;
          local_2c = *(uint32_t *)(g_color_table + tmp_i16);
          local_28 = *(uint32_t *)(g_color_table + tmp_i16 + 4);
          local_24 = *(uint32_t *)(g_color_table + tmp_i16 + 8);
          local_20 = param_2[3];
        }
        trap_R_SetColor(&local_2c);
        param_6 = param_6 + 2;
      }
      else {
LAB_00028203:
        tmp_i1 = *(int *)(&g_dat_00398000 + tmp_u13 * 0x50 + tmp_i11 * 0x5044);
        tmp_s14 = strlen((char *)param_6);
        tmp_s12 = 1;
        if ((int)tmp_s14 < 1) {
          tmp_s12 = tmp_s14;
        }
        tmp_i15 = 0;
        tmp_f10 = 0.0;
        tmp_pb17 = param_6;
        while ((tmp_b7 != 0 && (tmp_i15 < (int)tmp_s12))) {
          if ((tmp_b7 == 0x5e) && ((tmp_pb17[1] != 0 && (tmp_pb17[1] != 0x5e)))) {
            tmp_pb17 = tmp_pb17 + 2;
            tmp_i15 = 0;
          }
          else {
            tmp_pb17 = tmp_pb17 + 1;
            tmp_i15 = 1;
            tmp_f10 = (float)*(int *)(&g_dat_0039800c + (uint)tmp_b7 * 0x50 + tmp_i16 * 0x5044) + tmp_f10;
          }
          if (tmp_pb17 == (byte *)0x0) break;
          tmp_b7 = *tmp_pb17;
        }
        if (tmp_f2 < (float)(int)ROUND(tmp_f10 * param_5 * *(float *)(&g_dat_0039cffc + tmp_i16 * 0x5044)
                                     ) + param_3) {
          *param_1 = 0.0;
          break;
        }
        tmp_i16 = tmp_u13 * 0x50 + tmp_i11 * 0x5044;
        tmp_u3 = *(uint32_t *)(&g_dat_00398024 + tmp_i16);
        tmp_u9 = *(uint32_t *)(&g_dat_00398028 + tmp_i16);
        tmp_u4 = *(uint32_t *)(&g_dat_00398020 + tmp_i16);
        tmp_u5 = *(uint32_t *)(&g_dat_0039801c + tmp_i16);
        tmp_u6 = *(uint32_t *)(&g_dat_00398018 + tmp_i16);
        local_3c = (float)*(int *)(&g_dat_00398008 + tmp_i16) * param_5 + param_3;
        local_38 = param_4 - (float)tmp_i1 * param_5;
        local_34 = (float)*(int *)(&g_dat_00398010 + tmp_i16) * param_5;
        local_30 = param_5 * (float)*(int *)(&g_dat_00398014 + tmp_i16);
        UI_AdjustFrom640(&local_3c,&local_38,&local_34,&local_30);
        trap_R_DrawStretchPic(local_3c,local_38,local_34,local_30,tmp_u6,tmp_u5,tmp_u4,tmp_u3,tmp_u9);
        local_6c = local_6c + 1;
        param_6 = param_6 + 1;
        param_3 = (float)*(int *)(&g_dat_0039800c + tmp_i16) * param_5 + 0.0 + param_3;
        *param_1 = param_3;
      }
    } while (param_6 != (byte *)0x0);
    trap_R_SetColor(0);
  }
  return;
}

void UI_DrawCampaignMapDescription_constprop_54
          (float *param_1,uint32_t param_2,float param_3,float param_4,float param_5,
          uint32_t param_6,int param_7,int param_8)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  byte tmp_b5;
  uint tmp_u6;
  uint tmp_u7;
  uint tmp_u8;
  uint *tmp_pu9;
  byte *tmp_pb10;
  size_t tmp_s11;
  int tmp_i12;
  uint *tmp_pu13;
  byte *local_458;
  int local_454;
  int local_450;
  int local_440;
  byte *local_43c;
  uint32_t local_41c;
  uint32_t uStack_14;
  
  uStack_14 = 0x28529;
  if (((int)GHIDRA_FIELD(ui_currentCampaign, 12, 4) < 0) ||
     (tmp_i12 = GHIDRA_FIELD(ui_currentCampaign, 12, 4), g_dat_003cab70 < (int)GHIDRA_FIELD(ui_currentCampaign, 12, 4))) {
    GHIDRA_FIELD(ui_currentCampaign, 12, 4) = 0;
    trap_Cvar_Set("ui_currentCampaign","0");
    tmp_i12 = 0;
  }
  if ((((&g_dat_003cabd4)[tmp_i12 * 0x1d] == 0) || ((int)(&g_dat_003cabd8)[tmp_i12 * 0x1d] < param_8)) ||
     ((&g_dat_00397ecc)[param_8 + 0xcb30 + tmp_i12 * 0x1d] == 0)) {
    local_458 = (byte *)0x57fac;
LAB_0002858f:
    tmp_b5 = *local_458;
    if (tmp_b5 != 0) {
      tmp_s11 = strlen((char *)local_458);
      tmp_u6 = (uint)tmp_b5;
      goto LAB_000285b0;
    }
  }
  else {
    local_458 = *(byte **)((&g_dat_00397ecc)[param_8 + 0xcb30 + tmp_i12 * 0x1d] + 0x74);
    if (local_458 != (byte *)0x0) goto LAB_0002858f;
  }
  local_458 = (byte *)0x55b45;
  tmp_u6 = 0x5e;
  tmp_s11 = 0x12;
LAB_000285b0:
  tmp_i12 = 0;
  tmp_f2 = 0.0;
  tmp_pb10 = local_458;
  while (((char)tmp_u6 != '\0' && (tmp_i12 < (int)tmp_s11))) {
    if (((char)tmp_u6 == '^') && ((tmp_pb10[1] != 0 && (tmp_pb10[1] != 0x5e)))) {
      tmp_pb10 = tmp_pb10 + 2;
    }
    else {
      tmp_f1 = (float)*(int *)(&g_dat_00397ffc + tmp_u6 * 0x50 + g_dat_003e7e2c * 0x5044);
      if ((float)*(int *)(&g_dat_00397ffc + tmp_u6 * 0x50 + g_dat_003e7e2c * 0x5044) <= tmp_f2) {
        tmp_f1 = tmp_f2;
      }
      tmp_pb10 = tmp_pb10 + 1;
      tmp_i12 = tmp_i12 + 1;
      tmp_f2 = tmp_f1;
    }
    if (tmp_pb10 == (byte *)0x0) break;
    tmp_u6 = (uint)*tmp_pb10;
  }
  tmp_u6 = 0;
  local_440 = 0;
  tmp_i12 = 0;
  local_454 = 0;
  tmp_f1 = *(float *)(&g_dat_0039cffc + g_dat_003e7e2c * 0x5044);
  local_43c = (byte *)0x0;
  GHIDRA_FIELD(local_41c, 0, 1) = 0;
  local_450 = 0;
  tmp_f2 = tmp_f2 * param_3 * tmp_f1;
  tmp_f4 = 0.0;
  do {
    tmp_b5 = *local_458;
    if (((byte)(tmp_b5 - 9) < 2) || (tmp_pu13 = &local_41c, (tmp_b5 & 0xdf) == 0)) {
      local_43c = local_458 + 1;
      local_454 = local_450;
      tmp_pu13 = &local_41c;
      local_440 = tmp_i12;
    }
    do {
      tmp_pu9 = tmp_pu13;
      tmp_u7 = *tmp_pu9 + 0xfefefeff & ~*tmp_pu9;
      tmp_u8 = tmp_u7 & 0x80808080;
      tmp_pu13 = tmp_pu9 + 1;
    } while (tmp_u8 == 0);
    if ((tmp_u7 & 0x8080) == 0) {
      tmp_pu13 = (uint *)((int)tmp_pu9 + 6);
      tmp_u8 = tmp_u8 >> 0x10;
    }
    tmp_i12 = 0;
    tmp_f3 = 0.0;
    tmp_pu9 = &local_41c;
    while (((char)tmp_u6 != '\0' &&
           (tmp_i12 < (int)((int)tmp_pu13 +
                          ((-3 - (uint)CARRY1((byte)tmp_u8,(byte)tmp_u8)) - (int)&local_41c))))) {
      if (((char)tmp_u6 == '^') &&
         ((*(byte *)((int)tmp_pu9 + 1) != 0 && (*(byte *)((int)tmp_pu9 + 1) != 0x5e)))) {
        tmp_pu9 = (uint *)((int)tmp_pu9 + 2);
      }
      else {
        tmp_pu9 = (uint *)((int)tmp_pu9 + 1);
        tmp_i12 = tmp_i12 + 1;
        tmp_f3 = (float)*(int *)(&g_dat_0039800c + tmp_u6 * 0x50 + g_dat_003e7e2c * 0x5044) + tmp_f3;
      }
      if (tmp_pu9 == (uint *)0x0) break;
      tmp_u6 = (uint)(byte)*tmp_pu9;
    }
    tmp_i12 = (int)ROUND(tmp_f3 * param_3 * tmp_f1);
    if ((((local_454 != 0) && (param_1[2] < (float)tmp_i12)) || (tmp_b5 == 10)) || (tmp_b5 == 0)) {
      if (local_450 != 0) {
        tmp_f1 = param_4;
        if (param_7 != 0) {
          if (param_7 == 2) {
            tmp_f1 = param_4 - (float)local_440;
          }
          else {
            tmp_f1 = tmp_f4;
            if (param_7 == 1) {
              tmp_f1 = param_4 - (float)local_440 * 0.5;
            }
          }
        }
        tmp_f4 = tmp_f1 + *param_1;
        tmp_f1 = param_1[1];
        *(uint8_t *)((int)&local_41c + local_454) = 0;
        Text_Paint_Ext(tmp_f4,param_5 + tmp_f1,param_3,param_3,param_2,&local_41c,0,0,param_6,
                       &g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
        tmp_b5 = *local_458;
      }
      if (tmp_b5 == 0) {
        return;
      }
      param_5 = (float)((int)ROUND(tmp_f2) + 5) + param_5;
      local_440 = 0;
      local_454 = 0;
      local_450 = 0;
      local_458 = local_43c;
    }
    else {
      local_458 = local_458 + 1;
      if (tmp_b5 == 0xd) {
        *(uint8_t *)((int)&local_41c + local_450) = 0x20;
      }
      else {
        *(byte *)((int)&local_41c + local_450) = tmp_b5;
      }
      *(uint8_t *)((int)&local_41c + local_450 + 1) = 0;
      local_450 = local_450 + 1;
    }
    if (local_458 == (byte *)0x0) {
      return;
    }
    tmp_u6 = (uint)(byte)local_41c;
    tmp_f1 = *(float *)(&g_dat_0039cffc + g_dat_003e7e2c * 0x5044);
  } while( true );
}

void UI_DrawMissionBriefingObjectives
          (float *param_1,uint32_t param_2,float param_3,float param_4,float param_5,
          uint32_t param_6,int param_7)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  byte tmp_b5;
  int tmp_i6;
  size_t tmp_s7;
  uint tmp_u8;
  uint tmp_u9;
  uint *tmp_pu10;
  byte *tmp_pb11;
  uint tmp_u12;
  int tmp_i13;
  uint *tmp_pu14;
  byte *local_498;
  int local_494;
  int local_490;
  int local_484;
  int local_480;
  byte *local_47c;
  uint8_t local_45c [64];
  uint32_t local_41c;
  uint32_t uStack_14;
  
  uStack_14 = 0x28a1e;
  trap_Cvar_VariableStringBuffer("mapname",local_45c,0x40);
  tmp_i6 = UI_FindMapInfoByMapname(local_45c);
  tmp_i13 = g_dat_003e7e2c;
  if (tmp_i6 != 0) {
    local_498 = *(byte **)(tmp_i6 + 0x7c);
    local_484 = g_dat_003e7e2c;
    if (local_498 != (byte *)0x0) {
      tmp_s7 = strlen((char *)local_498);
      tmp_i6 = 0;
      tmp_f2 = 0.0;
      tmp_pb11 = local_498;
      do {
        while( true ) {
          tmp_b5 = *tmp_pb11;
          if ((tmp_b5 == 0) || ((int)tmp_s7 <= tmp_i6)) goto LAB_00028af0;
          if ((tmp_b5 != 0x5e) || ((tmp_pb11[1] == 0 || (tmp_pb11[1] == 0x5e)))) break;
          tmp_pb11 = tmp_pb11 + 2;
          if (tmp_pb11 == (byte *)0x0) goto LAB_00028af0;
        }
        tmp_f1 = (float)*(int *)(&g_dat_00397ffc + (uint)tmp_b5 * 0x50 + tmp_i13 * 0x5044);
        if ((float)*(int *)(&g_dat_00397ffc + (uint)tmp_b5 * 0x50 + tmp_i13 * 0x5044) <= tmp_f2) {
          tmp_f1 = tmp_f2;
        }
        tmp_f2 = tmp_f1;
        tmp_pb11 = tmp_pb11 + 1;
        tmp_i6 = tmp_i6 + 1;
      } while (tmp_pb11 != (byte *)0x0);
LAB_00028af0:
      local_494 = 0;
      tmp_u12 = 0;
      GHIDRA_FIELD(local_41c, 0, 1) = 0;
      tmp_f1 = *(float *)(&g_dat_0039cffc + tmp_i13 * 0x5044);
      local_47c = (byte *)0x0;
      local_480 = 0;
      tmp_i13 = 0;
      local_490 = 0;
      tmp_f2 = tmp_f2 * param_3 * tmp_f1;
      tmp_f4 = 0.0;
      do {
        tmp_b5 = *local_498;
        if (((byte)(tmp_b5 - 9) < 2) || (tmp_pu14 = &local_41c, (tmp_b5 & 0xdf) == 0)) {
          local_47c = local_498 + 1;
          local_494 = local_490;
          tmp_pu14 = &local_41c;
          local_480 = tmp_i13;
        }
        do {
          tmp_pu10 = tmp_pu14;
          tmp_u8 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
          tmp_u9 = tmp_u8 & 0x80808080;
          tmp_pu14 = tmp_pu10 + 1;
        } while (tmp_u9 == 0);
        if ((tmp_u8 & 0x8080) == 0) {
          tmp_pu14 = (uint *)((int)tmp_pu10 + 6);
          tmp_u9 = tmp_u9 >> 0x10;
        }
        tmp_i13 = 0;
        tmp_f3 = 0.0;
        tmp_pu10 = &local_41c;
        while (((char)tmp_u12 != '\0' &&
               (tmp_i13 < (int)((int)tmp_pu14 +
                              ((-3 - (uint)CARRY1((byte)tmp_u9,(byte)tmp_u9)) - (int)&local_41c))))) {
          if (((char)tmp_u12 == '^') &&
             ((*(byte *)((int)tmp_pu10 + 1) != 0 && (*(byte *)((int)tmp_pu10 + 1) != 0x5e)))) {
            tmp_pu10 = (uint *)((int)tmp_pu10 + 2);
          }
          else {
            tmp_pu10 = (uint *)((int)tmp_pu10 + 1);
            tmp_i13 = tmp_i13 + 1;
            tmp_f3 = (float)*(int *)(&g_dat_0039800c + tmp_u12 * 0x50 + local_484 * 0x5044) + tmp_f3;
          }
          if (tmp_pu10 == (uint *)0x0) break;
          tmp_u12 = (uint)(byte)*tmp_pu10;
        }
        tmp_i13 = (int)ROUND(tmp_f3 * param_3 * tmp_f1);
        if ((((local_494 != 0) && (param_1[2] < (float)tmp_i13)) || (tmp_b5 == 10)) || (tmp_b5 == 0)) {
          if (local_490 != 0) {
            tmp_f1 = param_4;
            if (param_7 != 0) {
              if (param_7 == 2) {
                tmp_f1 = param_4 - (float)local_480;
              }
              else {
                tmp_f1 = tmp_f4;
                if (param_7 == 1) {
                  tmp_f1 = param_4 - (float)local_480 * 0.5;
                }
              }
            }
            tmp_f4 = tmp_f1 + *param_1;
            tmp_f1 = param_1[1];
            *(uint8_t *)((int)&local_41c + local_494) = 0;
            Text_Paint_Ext(tmp_f4,param_5 + tmp_f1,param_3,param_3,param_2,&local_41c,0,0,param_6,
                           &g_dat_00397ffc + g_dat_003e7e2c * 0x5044);
            tmp_b5 = *local_498;
          }
          if (tmp_b5 == 0) {
            return;
          }
          local_498 = local_47c;
          param_5 = (float)((int)ROUND(tmp_f2) + 5) + param_5;
          local_480 = 0;
          local_494 = 0;
          local_490 = 0;
        }
        else {
          local_498 = local_498 + 1;
          if (tmp_b5 == 0xd) {
            *(uint8_t *)((int)&local_41c + local_490) = 0x20;
          }
          else {
            *(byte *)((int)&local_41c + local_490) = tmp_b5;
          }
          *(uint8_t *)((int)&local_41c + local_490 + 1) = 0;
          local_490 = local_490 + 1;
        }
        if (local_498 == (byte *)0x0) {
          return;
        }
        tmp_u12 = (uint)(byte)local_41c;
        local_484 = g_dat_003e7e2c;
        tmp_f1 = *(float *)(&g_dat_0039cffc + g_dat_003e7e2c * 0x5044);
      } while( true );
    }
  }
  return;
}

uint64_t UI_FeederCount(float param_1)

{
  int tmp_i1;
  byte tmp_b2;
  uint32_t *tmp_pu3;
  int *tmp_pi4;
  byte *tmp_pb5;
  int tmp_i6;
  uint32_t uStack_c;
  
  if (param_1 == 0.0) {
    return CONCAT44(uStack_c,g_dat_003b7f38);
  }
  tmp_i1 = g_dat_003e13a0;
  if (param_1 == 15.0) goto LAB_00028f28;
  if ((param_1 == 4.0) || (param_1 == 1.0)) {
    if (GHIDRA_FIELD(ui_netGameType, 12, 4) == 4) {
      if (0 < g_dat_003cab70) {
        tmp_pb5 = &g_dat_003cabe4;
        tmp_i1 = 0;
        do {
          if ((*tmp_pb5 & 4) != 0) {
            tmp_i1 = tmp_i1 + 1;
          }
          tmp_pb5 = tmp_pb5 + 0x74;
        } while (tmp_pb5 != &g_dat_003cabe4 + g_dat_003cab70 * 0x74);
        goto LAB_00028f28;
      }
    }
    else if (0 < g_dat_003bab6c) {
      tmp_b2 = (byte)GHIDRA_FIELD(ui_netGameType, 12, 4);
      tmp_pu3 = (uint32_t *)&g_dat_003babcc;
      tmp_i6 = g_dat_003bab6c * 0x80;
      tmp_i1 = 0;
      do {
        *tmp_pu3 = 0;
        if ((tmp_pu3[-0x14] & 1 << (tmp_b2 & 0x1f)) != 0) {
          tmp_i1 = tmp_i1 + 1;
          *tmp_pu3 = 1;
        }
        tmp_pu3 = tmp_pu3 + 0x20;
      } while (tmp_pu3 != (uint32_t *)(&g_dat_003babcc + tmp_i6));
      goto LAB_00028f28;
    }
  }
  else if ((param_1 == 27.0) || (param_1 == 26.0)) {
    if (0 < g_dat_003cab70) {
      tmp_pi4 = &g_dat_003cabd4;
      tmp_i1 = 0;
      do {
        if (*tmp_pi4 != 0) {
          tmp_i1 = tmp_i1 + 1;
        }
        tmp_pi4 = tmp_pi4 + 0x1d;
      } while (tmp_pi4 != &g_dat_003cabd4 + g_dat_003cab70 * 0x1d);
      return CONCAT44(uStack_c,tmp_i1);
    }
  }
  else {
    tmp_i1 = g_dat_003e8030;
    if ((((param_1 == 29.0) || (tmp_i1 = g_dat_003df584, param_1 == 28.0)) ||
        (tmp_i1 = g_dat_003e53c0, param_1 == 2.0)) ||
       ((tmp_i1 = g_dat_003e693c, param_1 == 13.0 || (tmp_i1 = g_dat_003e7e0c, param_1 == 14.0))))
    goto LAB_00028f28;
    if (param_1 == 7.0) {
      tmp_i1 = g_dat_003b8d54;
      if (_DAT_003b8d60 < g_dat_00397fdc) {
        _DAT_003b8d60 = g_dat_00397fdc + 3000;
        UI_BuildPlayerList();
        tmp_i1 = g_dat_003b8d54;
      }
      goto LAB_00028f28;
    }
    if (param_1 == 8.0) {
      tmp_i1 = g_dat_003b8d58;
      if (_DAT_003b8d60 < g_dat_00397fdc) {
        _DAT_003b8d60 = g_dat_00397fdc + 3000;
        UI_BuildPlayerList();
        tmp_i1 = g_dat_003b8d58;
      }
      goto LAB_00028f28;
    }
    tmp_i1 = g_dat_003e0790;
    if ((param_1 == 9.0) || (tmp_i1 = g_dat_003e0f98, param_1 == 10.0)) goto LAB_00028f28;
  }
  tmp_i1 = 0;
LAB_00028f28:
  return CONCAT44(uStack_c,tmp_i1);
}

void UI_BuildServerStatus(int param_1)

{
  int tmp_i1;
  uint local_c18 [772];
  
  trap_GetClientState(local_c18);
  if (_DAT_003e7e10 == 0) {
    if (param_1 == 0) {
      if (_DAT_003e6940 == 0) {
        return;
      }
      if (g_dat_00397fdc < _DAT_003e6940) {
        return;
      }
    }
    else {
      Menu_SetFeederSelection(0,0xd,0,0);
      g_dat_003e693c = 0;
      tmp_i1 = Menus_FindByName("serverinfo_popmenu");
      if (tmp_i1 != 0) {
        Menu_ShowItemByName(tmp_i1,"serverURL",0);
        Menu_ShowItemByName(tmp_i1,"modURL",0);
      }
      tmp_i1 = Menus_FindByName("popupError");
      if (tmp_i1 != 0) {
        Menu_ShowItemByName(tmp_i1,"serverURL",0);
        Menu_ShowItemByName(tmp_i1,"modURL",0);
      }
      trap_LAN_ServerStatus(0,0,0);
    }
    if ((4 < local_c18[0]) ||
       (((-1 < _DAT_003e13bc && (g_dat_003e53c0 != 0)) && (_DAT_003e13bc <= g_dat_003e53c0)))) {
      tmp_i1 = UI_GetServerStatusInfo();
      if (tmp_i1 == 0) {
        _DAT_003e6940 = g_dat_00397fdc + 500;
      }
      else {
        _DAT_003e6940 = 0;
        trap_LAN_ServerStatus(&g_dat_003e57fc,0,0);
      }
    }
  }
  return;
}

void UI_FeederSelection_part_24(int param_1,float param_2)

{
  bool tmp_b1;
  bool tmp_b2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  byte *tmp_pb5;
  uint32_t tmp_u6;
  char *tmp_pc7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  int local_24;
  
  tmp_b1 = param_2 == 1.0;
  tmp_b2 = true;
  if (param_2 == 4.0) {
    if (tmp_b1) goto LAB_000295f9;
    local_24 = GHIDRA_FIELD(ui_netGameType, 12, 4);
    if (GHIDRA_FIELD(ui_netGameType, 12, 4) == 4) goto LAB_00029627;
LAB_0002937e:
    tmp_i8 = 0;
    tmp_i10 = 0;
    if (g_dat_003bab6c < 1) goto LAB_000293ac;
    tmp_i10 = 0;
    do {
      if (*(int *)(&g_dat_003babcc + tmp_i10 * 0x80) != 0) {
        if (param_1 == tmp_i8) goto LAB_000293ac;
        tmp_i8 = tmp_i8 + 1;
      }
      tmp_i10 = tmp_i10 + 1;
    } while (tmp_i10 != g_dat_003bab6c);
  }
  else {
    tmp_b2 = false;
    if (!tmp_b1) {
      tmp_b1 = true;
      tmp_i8 = GHIDRA_FIELD(ui_currentNetCampaign, 12, 4);
      if ((param_2 != 27.0) && (tmp_b1 = false, tmp_i8 = GHIDRA_FIELD(ui_currentCampaign, 12, 4), param_2 != 26.0))
      {
        if (param_2 == 29.0) {
          return;
        }
        if (param_2 == 2.0) {
          _DAT_003e13bc = param_1;
          trap_LAN_GetServerInfo
                    (GHIDRA_FIELD(ui_netSource, 12, 4),*(uint32_t *)(&g_dat_003e13c0 + param_1 * 4),info_10663,
                     0x400);
          tmp_pc7 = (char *)Info_ValueForKey(info_10663,"mapname");
          if ((tmp_pc7 != (char *)0x0) && (*tmp_pc7 != '\0')) {
            tmp_u3 = Info_ValueForKey(info_10663,"mapname");
            tmp_u3 = va("levelshots/%s",tmp_u3);
            g_dat_003e53dc = trap_R_RegisterShaderNoMip(tmp_u3);
            return;
          }
          g_dat_003e53dc = trap_R_RegisterShaderNoMip("levelshots/unknownmap");
          return;
        }
        if (param_2 == 13.0) {
          return;
        }
        if (param_2 == 14.0) {
          if (g_dat_003e7e0c + -1 <= param_1) {
            _DAT_003e7e08 = param_1;
            return;
          }
          _DAT_003e7e08 = param_1;
          Q_strncpyz(&g_dat_003e57fc,&g_dat_00397ec8 + (param_1 + 0x13dd) * 0x10,0x40);
          Menu_SetFeederSelection(0,0xd,0,0);
          UI_BuildServerStatus();
          return;
        }
        if (param_2 == 7.0) {
          _DAT_003b8d64 = param_1;
          return;
        }
        if (param_2 == 8.0) {
          _DAT_003b8d5c = param_1;
          return;
        }
        if (param_2 == 9.0) {
          _DAT_003e0794 = param_1;
          return;
        }
        if (param_2 == 15.0) {
          g_dat_003e13a4 = param_1;
          if (-1 < g_dat_003e13a8) {
            trap_CIN_StopCinematic(g_dat_003e13a8);
          }
          g_dat_003e13a8 = 0xffffffff;
          return;
        }
        if (param_2 == 10.0) {
          _DAT_003e0f9c = param_1;
          return;
        }
        if (param_2 != 28.0) {
          return;
        }
        _DAT_003df588 = param_1;
        trap_Cvar_Set("ui_profile",*(uint32_t *)(&g_dat_003df384 + param_1 * 8));
        return;
      }
      if (g_dat_003cab70 < 1) {
        tmp_i10 = 0;
      }
      else {
        tmp_pi4 = &g_dat_003cabd4;
        tmp_i10 = 0;
        do {
          if (*tmp_pi4 != 0) {
            tmp_i10 = tmp_i10 + 1;
          }
          tmp_pi4 = tmp_pi4 + 0x1d;
        } while (tmp_pi4 != &g_dat_003cabd4 + g_dat_003cab70 * 0x1d);
      }
      if (-1 < (int)(&g_dat_003cabcc)[tmp_i8 * 0x1d]) {
        trap_CIN_StopCinematic((&g_dat_003cabcc)[tmp_i8 * 0x1d]);
        (&g_dat_003cabcc)[tmp_i8 * 0x1d] = 0xffffffff;
      }
      tmp_u3 = va("%d",param_1);
      trap_Cvar_Set("ui_campaignIndex",tmp_u3);
      if (param_1 < 0) {
        tmp_i8 = 0;
      }
      else {
        tmp_i8 = param_1;
        if (tmp_i10 <= param_1) {
          tmp_i8 = tmp_i10 + -1;
        }
      }
      if (0 < g_dat_003cab70) {
        tmp_pi4 = &g_dat_003cabe0;
        tmp_i9 = 0;
        do {
          if ((*tmp_pi4 == tmp_i8) && (tmp_pi4[-3] != 0)) goto LAB_00029556;
          tmp_i9 = tmp_i9 + 1;
          tmp_pi4 = tmp_pi4 + 0x1d;
        } while (tmp_i9 != g_dat_003cab70);
      }
      tmp_i9 = 0;
LAB_00029556:
      GHIDRA_FIELD(ui_campaignIndex, 12, 4) = param_1;
      if (tmp_b1) {
        GHIDRA_FIELD(ui_currentCampaign, 12, 4) = tmp_i9;
        tmp_u3 = va("%d",tmp_i9);
        trap_Cvar_Set("ui_currentCampaign",tmp_u3);
      }
      if (param_2 == 26.0) {
        GHIDRA_FIELD(ui_currentCampaign, 12, 4) = tmp_i9;
        tmp_u3 = va("%d",tmp_i9);
        trap_Cvar_Set("ui_currentCampaign",tmp_u3);
        GHIDRA_FIELD(ui_currentCampaignCompleted, 12, 4) =
             ZEXT14((&g_dat_003cabd8)[GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x1d] ==
                    *(int *)(&g_dat_003cab88 + (tmp_i10 + -1) * 0x74));
        tmp_u3 = va("%i",GHIDRA_FIELD(ui_currentCampaignCompleted, 12, 4));
        trap_Cvar_Set("ui_currentCampaignCompleted",tmp_u3);
        return;
      }
      GHIDRA_FIELD(ui_currentNetCampaign, 12, 4) = tmp_i9;
      tmp_u3 = va("%d",tmp_i9);
      trap_Cvar_Set("ui_currentNetCampaign",tmp_u3);
      tmp_u3 = GHIDRA_FIELD(ui_currentNetCampaign, 12, 4);
      tmp_u6 = va(&g_dat_00055bd9,*(uint32_t *)(&g_dat_003cab74 + GHIDRA_FIELD(ui_currentNetCampaign, 12, 4) * 0x74))
      ;
      tmp_u6 = trap_CIN_PlayCinematic(tmp_u6,0,0,0,0,10);
      (&g_dat_003cabcc)[tmp_u3 * 0x1d] = tmp_u6;
      return;
    }
LAB_000295f9:
    local_24 = (&g_dat_00397ed4)[(GHIDRA_FIELD(ui_gameType, 12, 4) + 0x20c8) * 4];
    if (GHIDRA_FIELD(ui_netGameType, 12, 4) != 4) goto LAB_0002937e;
LAB_00029627:
    if (0 < g_dat_003bab6c) {
      tmp_pb5 = &g_dat_003cabe4;
      tmp_i8 = 0;
      tmp_i10 = 0;
      do {
        if ((*tmp_pb5 & 4) != 0) {
          if (param_1 == tmp_i8) goto LAB_000293ac;
          tmp_i8 = tmp_i8 + 1;
        }
        tmp_i10 = tmp_i10 + 1;
        tmp_pb5 = tmp_pb5 + 0x74;
      } while (tmp_i10 != g_dat_003bab6c);
    }
  }
  tmp_i10 = 0;
LAB_000293ac:
  tmp_u3 = va("%d",param_1);
  trap_Cvar_Set("ui_mapIndex",tmp_u3);
  GHIDRA_FIELD(ui_mapIndex, 12, 4) = param_1;
  if ((local_24 != 4) && (tmp_b2)) {
    GHIDRA_FIELD(ui_currentMap, 12, 4) = tmp_i10;
    tmp_u3 = va("%d",tmp_i10);
    trap_Cvar_Set("ui_currentMap",tmp_u3);
  }
  if (tmp_b1) {
    GHIDRA_FIELD(ui_currentMap, 12, 4) = tmp_i10;
    tmp_u3 = va("%d",tmp_i10);
    trap_Cvar_Set("ui_currentMap",tmp_u3);
    return;
  }
  GHIDRA_FIELD(ui_currentNetMap, 12, 4) = tmp_i10;
  tmp_u3 = va("%d",tmp_i10);
  trap_Cvar_Set("ui_currentNetMap",tmp_u3);
  return;
}

void UI_FeederSelection(float param_1,int param_2)

{
  char *tmp_pc1;
  uint32_t tmp_u2;
  
  if (param_1 != 0.0) {
    UI_FeederSelection_part_24();
    return;
  }
  if ((-1 < param_2) && (param_2 < g_dat_003b7f38)) {
    if ((&g_dat_00397ecc)[(param_2 + 0x2008) * 4] == 0) {
      tmp_pc1 = "james";
    }
    else {
      tmp_pc1 = "janet";
    }
    trap_Cvar_Set("team_model",tmp_pc1);
    tmp_u2 = va(&g_dat_00055c02,(&uiInfo)[(param_2 + 0x2008) * 4]);
    trap_Cvar_Set("team_headmodel",tmp_u2);
    updateModel = 1;
  }
  return;
}

uint32_t UI_FeederSelectionClick(float *param_1)

{
  int *tmp_pi1;
  uint32_t tmp_u2;
  int tmp_i3;
  float local_474;
  float local_470;
  float local_46c;
  float local_468;
  char local_464 [36];
  char local_440 [36];
  uint8_t local_41c [1036];
  
  tmp_pi1 = (int *)param_1[0x94];
  if ((param_1[0x92] == 2.0) && (tmp_i3 = Menus_CaptureFuncActive(), tmp_i3 == 0)) {
    Item_ListBox_MouseEnter(param_1,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128),1);
    local_474 = (float)tmp_pi1[0x1a] + *param_1;
    local_470 = (float)(tmp_pi1[3] - *tmp_pi1) * (float)tmp_pi1[5] + param_1[1];
    local_46c = (float)tmp_pi1[0x1b];
    local_468 = local_46c;
    tmp_i3 = BG_CursorInRect(&local_474);
    tmp_u2 = 0;
    if (tmp_i3 != 0) {
      tmp_i3 = trap_LAN_ServerIsInFavoriteList
                        (GHIDRA_FIELD(ui_netSource, 12, 4),*(uint32_t *)(&g_dat_003e13c0 + tmp_pi1[3] * 4));
      if (tmp_i3 == 0) {
        trap_LAN_GetServerInfo
                  (GHIDRA_FIELD(ui_netSource, 12, 4),*(uint32_t *)(&g_dat_003e13c0 + _DAT_003e13bc * 4),local_41c,
                   0x400);
        local_464[0] = '\0';
        local_440[0] = '\0';
        tmp_u2 = Info_ValueForKey(local_41c,&g_dat_00055aca);
        Q_strncpyz(local_464,tmp_u2,0x24);
        tmp_u2 = Info_ValueForKey(local_41c,"hostname");
        Q_strncpyz(local_440,tmp_u2,0x24);
        if ((local_440[0] != '\0') && (local_464[0] != '\0')) {
          trap_LAN_AddServer(2,local_440,local_464);
        }
      }
      else {
        trap_LAN_GetServerInfo
                  (GHIDRA_FIELD(ui_netSource, 12, 4),*(uint32_t *)(&g_dat_003e13c0 + _DAT_003e13bc * 4),local_41c,
                   0x400);
        local_464[0] = '\0';
        tmp_u2 = Info_ValueForKey(local_41c,&g_dat_00055aca);
        Q_strncpyz(local_464,tmp_u2,0x24);
        if ((local_464[0] != '\0') && (trap_LAN_RemoveServer(2,local_464), GHIDRA_FIELD(ui_netSource, 12, 4) == 2)
           ) {
          UI_BuildServerDisplayList();
          UI_FeederSelection_part_24(0x40000000);
        }
      }
      tmp_u2 = 1;
    }
  }
  else {
    tmp_u2 = 0;
  }
  return tmp_u2;
}

void UI_BuildFindPlayerList(int param_1)

{
  char tmp_c1;
  char tmp_c2;
  char tmp_c3;
  int tmp_i4;
  __int32_t **pp_Var5;
  uint32_t tmp_u6;
  char *tmp_pc7;
  uint32_t *tmp_pu8;
  int local_1574;
  uint8_t *local_156c;
  uint8_t *local_1564;
  char local_1546 [38];
  uint8_t local_1520 [1096];
  uint32_t local_10d8 [1070];
  int local_20;
  
  if (param_1 == 0) {
    if (_DAT_003e7e10 == 0) {
      return;
    }
    if (g_dat_00397fdc < _DAT_003e7e10) {
      return;
    }
  }
  else {
    _DAT_003e6944 = 0;
    tmp_pu8 = (uint32_t *)&g_dat_003e6948;
    for (tmp_i4 = 0x230; tmp_i4 != 0; tmp_i4 = tmp_i4 + -1) {
      *tmp_pu8 = 0;
      tmp_pu8 = tmp_pu8 + 1;
    }
    g_dat_003e7e0c = 0;
    _DAT_003e7e08 = 0;
    trap_Cvar_VariableStringBuffer("ui_findPlayer",&g_dat_003e7208,0x400);
    Q_CleanStr(&g_dat_003e7208);
    if (g_dat_003e7208 == '\0') {
      _DAT_003e7e10 = 0;
      return;
    }
    tmp_i4 = (int)ROUND((float)(int)GHIDRA_FIELD(ui_serverStatusTimeOut, 12, 4) * 0.5 - 10.0);
    if (tmp_i4 < 0x32) {
      tmp_i4 = 0x32;
    }
    tmp_u6 = va("%d",tmp_i4);
    trap_Cvar_Set("cl_serverStatusResendTime",tmp_u6);
    trap_LAN_ServerStatus(0,0,0);
    g_dat_003e7e0c = 1;
    Com_sprintf(&g_dat_003e7a08,0x40,"searching %d...",_DAT_003e6944);
    numFound_10537 = 0;
    numTimeOuts_10538 = numTimeOuts_10538 + 1;
  }
  local_156c = &g_dat_003e6988;
  local_1564 = &g_dat_003e6948;
  do {
    if (*(int *)(local_156c + 0x48) == 0) {
LAB_00029dd0:
      trap_LAN_ServerStatus(local_1564,0,0);
      *(uint32_t *)(local_156c + 0x48) = 0;
      tmp_i4 = _DAT_003e6944;
      if (_DAT_003e6944 < g_dat_003e53c0) {
        *(int *)(local_156c + 0x40) = g_dat_00397fdc;
        trap_LAN_GetServerAddressString
                  (GHIDRA_FIELD(ui_netSource, 12, 4),*(uint32_t *)(&g_dat_003e13c0 + tmp_i4 * 4),local_1564,0x40);
        trap_LAN_GetServerInfo
                  (GHIDRA_FIELD(ui_netSource, 12, 4),*(uint32_t *)(&g_dat_003e13c0 + _DAT_003e6944 * 4),local_1520
                   ,0x400);
        tmp_u6 = Info_ValueForKey(local_1520,"hostname");
        Q_strncpyz(local_156c,tmp_u6,0x40);
        tmp_i4 = numFound_10537;
        *(uint32_t *)(local_156c + 0x48) = 1;
        _DAT_003e6944 = _DAT_003e6944 + 1;
        Com_sprintf(&g_dat_00397ec8 + (g_dat_003e7e0c + 0x13ec) * 0x10,0x40,"searching %d/%d...",
                    _DAT_003e6944,tmp_i4);
      }
    }
    else {
      tmp_i4 = UI_GetServerStatusInfo();
      if (tmp_i4 != 0) {
        numFound_10537 = numFound_10537 + 1;
        if (0 < local_20) {
          tmp_pu8 = local_10d8;
          local_1574 = 0;
          tmp_i4 = local_20;
          do {
            while (((char *)*tmp_pu8 != (char *)0x0 && (*(char *)*tmp_pu8 != '\0'))) {
              Q_strncpyz(local_1546,tmp_pu8[1],0x26);
              Q_CleanStr(local_1546);
              tmp_c3 = g_dat_003e7208;
              tmp_pc7 = local_1546;
              tmp_c1 = local_1546[0];
              while (tmp_c1 != '\0') {
                if (tmp_c3 == '\0') {
LAB_0002a128:
                  if (g_dat_003e7e0c < 0xf) {
                    Q_strncpyz(&g_dat_00397ec8 + (g_dat_003e7e0c + 0x13dc) * 0x10,local_1564,0x40);
                    Q_strncpyz(&g_dat_00397ec8 + (g_dat_003e7e0c + 0x13ec) * 0x10,local_156c,0x40);
                    g_dat_003e7e0c = g_dat_003e7e0c + 1;
                    tmp_i4 = local_20;
                    goto LAB_00029e90;
                  }
                  _DAT_003e6944 = g_dat_003e53c0;
                  break;
                }
                tmp_c1 = *tmp_pc7;
                if (tmp_c1 != '\0') {
                  pp_Var5 = __ctype_toupper_loc();
                  tmp_i4 = 0;
                  tmp_c2 = tmp_c3;
                  do {
                    if ((*pp_Var5)[tmp_c2] != (*pp_Var5)[tmp_c1]) break;
                    tmp_c2 = (&g_dat_003e7209)[tmp_i4];
                    if (tmp_c2 == '\0') goto LAB_0002a128;
                    tmp_c1 = tmp_pc7[tmp_i4 + 1];
                    tmp_i4 = tmp_i4 + 1;
                  } while (tmp_c1 != '\0');
                }
                tmp_pc7 = tmp_pc7 + 1;
                tmp_c1 = *tmp_pc7;
              }
              local_1574 = local_1574 + 1;
              tmp_pu8 = tmp_pu8 + 4;
              tmp_i4 = local_20;
              if (local_20 <= local_1574) goto LAB_00029f69;
            }
LAB_00029e90:
            local_1574 = local_1574 + 1;
            tmp_pu8 = tmp_pu8 + 4;
          } while (local_1574 < tmp_i4);
        }
LAB_00029f69:
        Com_sprintf(&g_dat_00397ec8 + (g_dat_003e7e0c + 0x13ec) * 0x10,0x40,"searching %d/%d...",
                    _DAT_003e6944,numFound_10537);
        *(uint32_t *)(local_156c + 0x48) = 0;
        goto LAB_00029dd0;
      }
      if (*(int *)(local_156c + 0x48) == 0) goto LAB_00029dd0;
      if (*(int *)(local_156c + 0x40) < g_dat_00397fdc - GHIDRA_FIELD(ui_serverStatusTimeOut, 12, 4)) {
        numTimeOuts_10538 = numTimeOuts_10538 + 1;
        goto LAB_00029dd0;
      }
    }
    local_156c = local_156c + 0x8c;
    local_1564 = local_1564 + 0x8c;
    if (local_156c == &g_dat_003e7248) {
      if (((((_DAT_003e69d0 == 0) && (_DAT_003e6a5c == 0)) && (_DAT_003e6ae8 == 0)) &&
          (((_DAT_003e6b74 == 0 && (_DAT_003e6c00 == 0)) &&
           ((_DAT_003e6c8c == 0 && ((_DAT_003e6d18 == 0 && (_DAT_003e6da4 == 0)))))))) &&
         ((_DAT_003e6e30 == 0 &&
          (((((_DAT_003e6ebc == 0 && (_DAT_003e6f48 == 0)) && (_DAT_003e6fd4 == 0)) &&
            ((_DAT_003e7060 == 0 && (_DAT_003e70ec == 0)))) &&
           ((_DAT_003e7178 == 0 && (_DAT_003e7204 == 0)))))))) {
        if (g_dat_003e7e0c == 0) {
          Com_sprintf(&g_dat_003e79c8,0x40,"no servers found");
        }
        else {
          if (g_dat_003e7e0c == 2) {
            tmp_pc7 = "";
          }
          else {
            tmp_pc7 = "s";
          }
          Com_sprintf(&g_dat_00397ec8 + (g_dat_003e7e0c + 0x13ec) * 0x10,0x40,
                      "%d server%s found with player %s",g_dat_003e7e0c + -1,tmp_pc7,&g_dat_003e7208);
        }
        _DAT_003e7e10 = 0;
        UI_FeederSelection_part_24(0x41600000);
        return;
      }
      _DAT_003e7e10 = g_dat_00397fdc + 0x19;
      return;
    }
  } while( true );
}

void UI_StopCinematic(int param_1)

{
  char *tmp_pc1;
  int tmp_i2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  
  if (param_1 < 0) {
    if (param_1 == -0xf4) {
      if (-1 < (int)(&g_dat_003bab80)[GHIDRA_FIELD(ui_currentMap, 12, 4) * 0x20]) {
        trap_CIN_StopCinematic((&g_dat_003bab80)[GHIDRA_FIELD(ui_currentMap, 12, 4) * 0x20]);
        (&g_dat_003bab80)[GHIDRA_FIELD(ui_currentMap, 12, 4) * 0x20] = 0xffffffff;
      }
    }
    else if (param_1 == -0xf6) {
      if (-1 < g_dat_003e53e0) {
        trap_CIN_StopCinematic(g_dat_003e53e0);
        g_dat_003e53e0 = -1;
      }
    }
    else if (param_1 == -0xfb) {
      tmp_pc1 = (char *)UI_Cvar_VariableString("ui_teamName");
      if (((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) && (0 < g_dat_003b8544)) {
        tmp_pu4 = &g_dat_003b8548;
        tmp_i3 = 0;
        do {
          tmp_i2 = Q_stricmp(tmp_pc1,*tmp_pu4);
          if (tmp_i2 == 0) {
            if (tmp_i3 < 0) {
              return;
            }
            goto LAB_0002a591;
          }
          tmp_i3 = tmp_i3 + 1;
          tmp_pu4 = tmp_pu4 + 6;
        } while (tmp_i3 < g_dat_003b8544);
      }
      tmp_i3 = 0;
LAB_0002a591:
      if ((tmp_i3 < g_dat_003b8544) && (-1 < (int)(&g_dat_003b855c)[tmp_i3 * 6])) {
        trap_CIN_StopCinematic((&g_dat_003b855c)[tmp_i3 * 6]);
        (&g_dat_003b855c)[tmp_i3 * 6] = 0xffffffff;
      }
    }
  }
  else {
    trap_CIN_StopCinematic(param_1);
  }
  return;
}

int UI_OwnerDrawWidth(int param_1,float param_2)

{
  byte tmp_b1;
  float tmp_f2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint8_t *tmp_pu5;
  int tmp_i6;
  uint tmp_u7;
  char *tmp_pc8;
  byte *tmp_pb9;
  uint32_t *tmp_pu10;
  byte tmp_b11;
  long double tmp_l12;
  
  tmp_b11 = 0;
  switch(param_1) {
  case 200:
    tmp_l12 = (long double)trap_Cvar_VariableValue("handicap");
    tmp_l12 = (long double)Com_Clamp(0x40a00000,0x42c80000,(float)tmp_l12);
    tmp_pc8 = *(char **)(handicapValues + ((int)ROUND(tmp_l12) / 5) * -4 + 0x50);
    break;
  default:
    goto _L1926;
  case 0xcb:
    tmp_pc8 = (char *)UI_Cvar_VariableString("ui_teamName");
    break;
  case 0xcd:
    tmp_pc8 = (char *)(&g_dat_00397ecc)[(GHIDRA_FIELD(ui_gameType, 12, 4) + 0x20c8) * 4];
    break;
  case 0xd0:
    tmp_pc8 = (char *)UI_Cvar_VariableString("ui_blueTeam");
    if (((tmp_pc8 != (char *)0x0) && (*tmp_pc8 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_pu10 = &g_dat_003b8548;
      tmp_i3 = 0;
      do {
        tmp_i6 = Q_stricmp(tmp_pc8,*tmp_pu10);
        if (tmp_i6 == 0) {
          if (tmp_i3 < 0) {
            return 0;
          }
          goto LAB_0002a901;
        }
        tmp_i3 = tmp_i3 + 1;
        tmp_pu10 = tmp_pu10 + 6;
      } while (tmp_i3 < g_dat_003b8544);
    }
    tmp_i3 = 0;
LAB_0002a901:
    if (g_dat_003b8544 <= tmp_i3) {
      return 0;
    }
    tmp_u4 = (&g_dat_003b8548)[tmp_i3 * 6];
    tmp_pu5 = &g_dat_00055c9f;
    goto LAB_0002aa14;
  case 0xd1:
    tmp_pc8 = (char *)UI_Cvar_VariableString("ui_redTeam");
    if (((tmp_pc8 != (char *)0x0) && (*tmp_pc8 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_pu10 = &g_dat_003b8548;
      tmp_i3 = 0;
      do {
        tmp_i6 = Q_stricmp(tmp_pc8,*tmp_pu10);
        if (tmp_i6 == 0) {
          if (tmp_i3 < 0) {
            return 0;
          }
          goto LAB_0002a665;
        }
        tmp_i3 = tmp_i3 + 1;
        tmp_pu10 = tmp_pu10 + 6;
      } while (tmp_i3 < g_dat_003b8544);
    }
    tmp_i3 = 0;
LAB_0002a665:
    if (g_dat_003b8544 <= tmp_i3) {
      return 0;
    }
    tmp_u4 = (&g_dat_003b8548)[tmp_i3 * 6];
    tmp_pu5 = &g_dat_00055caf;
LAB_0002aa14:
    tmp_pc8 = (char *)va("%s: %s",tmp_pu5,tmp_u4);
    break;
  case 0xd2:
  case 0xd3:
  case 0xd4:
  case 0xd5:
  case 0xd6:
    param_1 = param_1 + -0xd1;
    tmp_pc8 = "ui_blueteam%i";
    goto LAB_0002a7f8;
  case 0xd7:
  case 0xd8:
  case 0xd9:
  case 0xda:
  case 0xdb:
    param_1 = param_1 + -0xd6;
    tmp_pc8 = "ui_redteam%i";
LAB_0002a7f8:
    tmp_u4 = va(tmp_pc8,param_1);
    tmp_l12 = (long double)trap_Cvar_VariableValue(tmp_u4);
    tmp_i3 = (int)ROUND(tmp_l12);
    if (tmp_i3 < 1) {
      tmp_pc8 = "Closed";
    }
    else if (tmp_i3 == 1) {
      tmp_pc8 = "Human";
    }
    else {
      tmp_i3 = tmp_i3 + -2;
      if (g_dat_003b8340 <= tmp_i3) {
        tmp_i3 = 0;
      }
      tmp_pc8 = (char *)(&g_dat_003b8344)[tmp_i3 * 2];
    }
    tmp_pc8 = (char *)va("%i. %s",param_1,tmp_pc8);
    break;
  case 0xde:
    if (1 < (uint)GHIDRA_FIELD(ui_serverFilterType, 12, 4)) {
      GHIDRA_FIELD(ui_serverFilterType, 12, 4) = 0;
    }
    tmp_pc8 = (char *)va("Filter: %s",(&serverFilters)[GHIDRA_FIELD(ui_serverFilterType, 12, 4) * 2]);
    break;
  case 0xf7:
    tmp_u4 = va("ui_lastServerRefresh_%i",GHIDRA_FIELD(ui_netSource, 12, 4));
    tmp_pc8 = (char *)UI_Cvar_VariableString(tmp_u4);
    break;
  case 0xfa:
    tmp_i3 = Display_KeyBindPending();
    if (tmp_i3 == 0) {
      tmp_i3 = 0x38;
      tmp_pc8 = "Press ENTER or CLICK to change, Press BACKSPACE to clear";
    }
    else {
      tmp_i3 = 0x2d;
      tmp_pc8 = "Waiting for new key... Press ESCAPE to cancel";
    }
    goto LAB_0002a6a2;
  }
  if ((byte *)tmp_pc8 != (byte *)0x0) {
    tmp_u7 = 0xffffffff;
    tmp_pb9 = (byte *)tmp_pc8;
    do {
      if (tmp_u7 == 0) break;
      tmp_u7 = tmp_u7 - 1;
      tmp_b1 = *tmp_pb9;
      tmp_pb9 = tmp_pb9 + (uint)tmp_b11 * -2 + 1;
    } while (tmp_b1 != 0);
    tmp_i3 = ~tmp_u7 - 1;
LAB_0002a6a2:
    tmp_i6 = 0;
    tmp_f2 = 0.0;
    do {
      while( true ) {
        tmp_b11 = *tmp_pc8;
        if ((tmp_b11 == 0) || (tmp_i3 <= tmp_i6)) goto LAB_0002a700;
        if ((tmp_b11 != 0x5e) || ((tmp_pc8[1] == 0 || (tmp_pc8[1] == 0x5e)))) break;
        tmp_pc8 = tmp_pc8 + 2;
        if ((byte *)tmp_pc8 == (byte *)0x0) goto LAB_0002a700;
      }
      tmp_pc8 = tmp_pc8 + 1;
      tmp_i6 = tmp_i6 + 1;
      tmp_f2 = (float)*(int *)(&g_dat_0039800c + (uint)tmp_b11 * 0x50 + g_dat_003e7e2c * 0x5044) + tmp_f2;
    } while ((byte *)tmp_pc8 != (byte *)0x0);
LAB_0002a700:
    return (int)ROUND(tmp_f2 * param_2 * *(float *)(&g_dat_0039cffc + g_dat_003e7e2c * 0x5044));
  }
_L1926:
  return 0;
}

uint32_t UI_OwnerDrawHandleKey(int param_1,uint32_t param_2,uint32_t param_3,int param_4)

{
  char *tmp_pc1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  uint32_t *tmp_pu4;
  char *tmp_pc5;
  int tmp_i6;
  uint32_t tmp_u7;
  byte *tmp_pb8;
  byte tmp_b9;
  int tmp_i10;
  int tmp_i11;
  long double tmp_l12;
  char *local_28;
  
  switch(param_1) {
  case 200:
    if ((param_4 - 0xb2U < 2) || (param_4 == 0xd)) {
      tmp_l12 = (long double)trap_Cvar_VariableValue("handicap");
      tmp_l12 = (long double)Com_Clamp(0x40a00000,0x42c80000,(float)tmp_l12);
      tmp_i11 = (int)ROUND(tmp_l12);
      if (param_4 == 0xb3) {
        tmp_i11 = tmp_i11 + -5;
        goto LAB_0002ab87;
      }
    }
    else {
      if (param_4 != 0xa9) {
        return 0;
      }
      tmp_l12 = (long double)trap_Cvar_VariableValue("handicap");
      tmp_l12 = (long double)Com_Clamp(0x40a00000,0x42c80000,(float)tmp_l12);
      tmp_i11 = (int)ROUND(tmp_l12);
    }
    tmp_i11 = tmp_i11 + 5;
LAB_0002ab87:
    if (tmp_i11 < 0x65) {
      if (tmp_i11 < 0) {
        tmp_i11 = 100;
      }
    }
    else {
      tmp_i11 = 5;
    }
    tmp_u2 = va("%i",tmp_i11);
    trap_Cvar_Set("handicap",tmp_u2);
    return 1;
  case 0xc9:
    if ((param_4 - 0xb2U < 2) || (param_4 == 0xd)) {
      if (param_4 == 0xb3) {
        g_dat_003e7e20 = g_dat_003e7e20 + -1;
        goto LAB_0002abf3;
      }
    }
    else if (param_4 != 0xa9) {
      return 0;
    }
    g_dat_003e7e20 = g_dat_003e7e20 + 1;
LAB_0002abf3:
    if (g_dat_003e7e20 < 7) {
      if (g_dat_003e7e20 < 0) {
        g_dat_003e7e20 = 6;
      }
    }
    else {
      g_dat_003e7e20 = 0;
    }
    trap_Cvar_SetValue("color",(float)(int)(&uitogamecode)[g_dat_003e7e20]);
    return 1;
  default:
    return 0;
  case 0xcb:
    if ((param_4 != 0xa9 && param_4 != 0xd) && (1 < param_4 - 0xb2U)) {
      return 0;
    }
    tmp_pc3 = (char *)UI_Cvar_VariableString("ui_teamName");
    if (((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_pu4 = &g_dat_003b8548;
      tmp_i11 = 0;
      do {
        tmp_i6 = Q_stricmp(tmp_pc3,*tmp_pu4);
        if (tmp_i6 == 0) goto LAB_0002ac7d;
        tmp_i11 = tmp_i11 + 1;
        tmp_pu4 = tmp_pu4 + 6;
      } while (tmp_i11 < g_dat_003b8544);
    }
    tmp_i11 = 0;
LAB_0002ac7d:
    if (-1 < (int)(&g_dat_003b855c)[tmp_i11 * 6]) {
      trap_CIN_StopCinematic((&g_dat_003b855c)[tmp_i11 * 6]);
      (&g_dat_003b855c)[tmp_i11 * 6] = 0xffffffff;
    }
    tmp_i6 = tmp_i11 + -1;
    if (param_4 != 0xb3) {
      tmp_i6 = tmp_i11 + 1;
    }
    if (tmp_i6 < g_dat_003b8544) {
      if (tmp_i6 < 0) {
        tmp_i6 = g_dat_003b8544 + -1;
      }
    }
    else {
      tmp_i6 = 0;
    }
    trap_Cvar_Set("ui_teamName",(&g_dat_003b8548)[tmp_i6 * 6]);
    updateModel = 1;
    return 1;
  case 0xcd:
    if ((param_4 != 0xa9 && param_4 != 0xd) && (1 < param_4 - 0xb2U)) {
      return 0;
    }
    if (GHIDRA_FIELD(ui_netGameType, 12, 4) == 4) {
      if (g_dat_003cab70 < 1) goto LAB_0002b3b4;
      tmp_i11 = 0;
      tmp_pb8 = &g_dat_003cabe4;
      do {
        if ((*tmp_pb8 & 4) != 0) {
          tmp_i11 = tmp_i11 + 1;
        }
        tmp_pb8 = tmp_pb8 + 0x74;
      } while (tmp_pb8 != &g_dat_003cabe4 + g_dat_003cab70 * 0x74);
    }
    else if (g_dat_003bab6c < 1) {
LAB_0002b3b4:
      tmp_i11 = 0;
    }
    else {
      tmp_i6 = g_dat_003bab6c * 0x80;
      tmp_pu4 = (uint32_t *)&g_dat_003babcc;
      tmp_b9 = (byte)GHIDRA_FIELD(ui_netGameType, 12, 4);
      tmp_i11 = 0;
      do {
        *tmp_pu4 = 0;
        if ((tmp_pu4[-0x14] & 1 << (tmp_b9 & 0x1f)) != 0) {
          tmp_i11 = tmp_i11 + 1;
          *tmp_pu4 = 1;
        }
        tmp_pu4 = tmp_pu4 + 0x20;
      } while (tmp_pu4 != (uint32_t *)(&g_dat_003babcc + tmp_i6));
    }
    if (param_4 == 0xb3) {
      GHIDRA_FIELD(ui_gameType, 12, 4) = GHIDRA_FIELD(ui_gameType, 12, 4) + -1;
      if (GHIDRA_FIELD(ui_gameType, 12, 4) == 2) goto LAB_0002b2ea;
      if ((int)GHIDRA_FIELD(ui_gameType, 12, 4) < 2) {
        GHIDRA_FIELD(ui_gameType, 12, 4) = g_dat_003b8b48 + -1;
      }
    }
    else {
      GHIDRA_FIELD(ui_gameType, 12, 4) = GHIDRA_FIELD(ui_gameType, 12, 4) + 1;
      if ((int)GHIDRA_FIELD(ui_gameType, 12, 4) < g_dat_003b8b48) {
        if (GHIDRA_FIELD(ui_gameType, 12, 4) == 2) {
          GHIDRA_FIELD(ui_gameType, 12, 4) = 3;
        }
      }
      else {
LAB_0002b2ea:
        GHIDRA_FIELD(ui_gameType, 12, 4) = 1;
      }
    }
    trap_Cvar_Set("ui_Q3Model","0");
    tmp_u2 = va("%d",GHIDRA_FIELD(ui_gameType, 12, 4));
    trap_Cvar_Set("ui_gameType",tmp_u2);
    if (GHIDRA_FIELD(ui_netGameType, 12, 4) == 4) {
      if (0 < g_dat_003cab70) {
        tmp_pb8 = &g_dat_003cabe4;
        tmp_i6 = 0;
        do {
          if ((*tmp_pb8 & 4) != 0) {
            tmp_i6 = tmp_i6 + 1;
          }
          tmp_pb8 = tmp_pb8 + 0x74;
        } while (tmp_pb8 != &g_dat_003cabe4 + g_dat_003cab70 * 0x74);
        goto LAB_0002ae39;
      }
    }
    else if (0 < g_dat_003bab6c) {
      tmp_b9 = (byte)GHIDRA_FIELD(ui_netGameType, 12, 4);
      tmp_i10 = g_dat_003bab6c * 0x80;
      tmp_pu4 = (uint32_t *)&g_dat_003babcc;
      tmp_i6 = 0;
      do {
        *tmp_pu4 = 0;
        if ((tmp_pu4[-0x14] & 1 << (tmp_b9 & 0x1f)) != 0) {
          tmp_i6 = tmp_i6 + 1;
          *tmp_pu4 = 1;
        }
        tmp_pu4 = tmp_pu4 + 0x20;
      } while (tmp_pu4 != (uint32_t *)(&g_dat_003babcc + tmp_i10));
      goto LAB_0002ae39;
    }
    tmp_i6 = 0;
LAB_0002ae39:
    if (tmp_i11 != tmp_i6) {
      trap_Cvar_Set("ui_currentMap","0");
      Menu_SetFeederSelection(0,1,0,0);
      return 1;
    }
    return 1;
  case 0xd0:
    if ((param_4 != 0xa9 && param_4 != 0xd) && (1 < param_4 - 0xb2U)) {
      return 0;
    }
    tmp_pc3 = "ui_blueTeam";
    local_28 = "ui_blueTeam";
    tmp_pc5 = (char *)UI_Cvar_VariableString("ui_blueTeam");
    tmp_pc1 = tmp_pc3;
    if (((tmp_pc5 != (char *)0x0) && (tmp_pc1 = local_28, *tmp_pc5 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_pu4 = &g_dat_003b8548;
      tmp_i11 = 0;
      do {
        tmp_i6 = Q_stricmp(tmp_pc5,*tmp_pu4);
        local_28 = tmp_pc3;
        if (tmp_i6 == 0) goto LAB_0002aee3;
        tmp_i11 = tmp_i11 + 1;
        tmp_pu4 = tmp_pu4 + 6;
      } while (tmp_i11 < g_dat_003b8544);
LAB_0002b2fa:
      tmp_i11 = 0;
      goto LAB_0002aee3;
    }
    break;
  case 0xd1:
    if ((param_4 != 0xa9 && param_4 != 0xd) && (1 < param_4 - 0xb2U)) {
      return 0;
    }
    tmp_pc3 = "ui_redTeam";
    local_28 = "ui_redTeam";
    tmp_pc5 = (char *)UI_Cvar_VariableString("ui_redTeam");
    tmp_pc1 = tmp_pc3;
    if (((tmp_pc5 != (char *)0x0) && (tmp_pc1 = local_28, *tmp_pc5 != '\0')) && (0 < g_dat_003b8544)) {
      tmp_pu4 = &g_dat_003b8548;
      tmp_i11 = 0;
      do {
        tmp_i6 = Q_stricmp(tmp_pc5,*tmp_pu4);
        local_28 = tmp_pc3;
        if (tmp_i6 == 0) goto LAB_0002aee3;
        tmp_i11 = tmp_i11 + 1;
        tmp_pu4 = tmp_pu4 + 6;
      } while (tmp_i11 < g_dat_003b8544);
      goto LAB_0002b2fa;
    }
    break;
  case 0xd2:
  case 0xd3:
  case 0xd4:
  case 0xd5:
  case 0xd6:
    param_1 = param_1 + -0xd1;
    if ((param_4 - 0xb2U < 2) || (param_4 == 0xd)) {
      tmp_pc3 = "ui_blueteam%i";
      goto LAB_0002b0da;
    }
    if (param_4 != 0xa9) {
      return 0;
    }
    tmp_pc3 = "ui_blueteam%i";
LAB_0002b054:
    tmp_u2 = va(tmp_pc3,param_1);
    tmp_l12 = (long double)trap_Cvar_VariableValue(tmp_u2);
    tmp_i11 = (int)ROUND(tmp_l12);
    goto LAB_0002b088;
  case 0xd7:
  case 0xd8:
  case 0xd9:
  case 0xda:
  case 0xdb:
    param_1 = param_1 + -0xd6;
    if ((1 < param_4 - 0xb2U) && (param_4 != 0xd)) {
      if (param_4 != 0xa9) {
        return 0;
      }
      tmp_pc3 = "ui_redteam%i";
      goto LAB_0002b054;
    }
    tmp_pc3 = "ui_redteam%i";
LAB_0002b0da:
    tmp_u2 = va(tmp_pc3,param_1);
    tmp_l12 = (long double)trap_Cvar_VariableValue(tmp_u2);
    tmp_i11 = (int)ROUND(tmp_l12);
    if (param_4 == 0xb3) {
      tmp_i11 = tmp_i11 + -1;
      goto LAB_0002b089;
    }
LAB_0002b088:
    tmp_i11 = tmp_i11 + 1;
LAB_0002b089:
    if (g_dat_003b7f38 + 1 < tmp_i11) {
      tmp_i11 = 0;
    }
    else if (tmp_i11 < 0) {
      tmp_i11 = g_dat_003b7f38 + 1;
    }
    tmp_u7 = va("%i",tmp_i11);
    trap_Cvar_Set(tmp_u2,tmp_u7);
    return 0;
  case 0xde:
    if (((1 < param_4 - 0xb2U) && (param_4 != 0xd)) && (param_4 != 0xa9)) {
      return 0;
    }
    GHIDRA_FIELD(ui_serverFilterType, 12, 4) = 0;
    UI_BuildServerDisplayList();
    return 0;
  case 0xf2:
    if ((param_4 - 0xb2U < 2) || (param_4 == 0xd)) {
      if (param_4 == 0xb3) {
        g_dat_003e7e14 = g_dat_003e7e14 + -1;
        goto LAB_0002aad7;
      }
    }
    else if (param_4 != 0xa9) {
      return 0;
    }
    g_dat_003e7e14 = g_dat_003e7e14 + 1;
LAB_0002aad7:
    if (g_dat_003e7e14 < 0x10) {
      if (g_dat_003e7e14 < 0) {
        g_dat_003e7e14 = 0xf;
      }
    }
    else {
      g_dat_003e7e14 = 0;
    }
    tmp_u2 = va("%d",g_dat_003e7e14);
    trap_Cvar_Set("cg_drawCrosshair",tmp_u2);
    return 0;
  }
  local_28 = tmp_pc1;
  tmp_i11 = 0;
LAB_0002aee3:
  tmp_i6 = tmp_i11 + -1;
  if (param_4 != 0xb3) {
    tmp_i6 = tmp_i11 + 1;
  }
  if (tmp_i6 < g_dat_003b8544) {
    if (tmp_i6 < 0) {
      tmp_i6 = g_dat_003b8544 + -1;
    }
  }
  else {
    tmp_i6 = 0;
  }
  trap_Cvar_Set(local_28,(&g_dat_003b8548)[tmp_i6 * 6]);
  return 1;
}

void AssetCache(void)

{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  
  _DAT_003b6198 = trap_R_RegisterShaderNoMip("ui/assets/gradientbar2.tga");
  g_dat_003b6210 = trap_R_RegisterShaderNoMip("menu/art/fx_base");
  _DAT_003b6214 = trap_R_RegisterShaderNoMip("menu/art/fx_red");
  _DAT_003b6218 = trap_R_RegisterShaderNoMip("menu/art/fx_yel");
  _DAT_003b621c = trap_R_RegisterShaderNoMip("menu/art/fx_grn");
  _DAT_003b6220 = trap_R_RegisterShaderNoMip("menu/art/fx_teal");
  _DAT_003b6224 = trap_R_RegisterShaderNoMip("menu/art/fx_blue");
  _DAT_003b6228 = trap_R_RegisterShaderNoMip("menu/art/fx_cyan");
  _DAT_003b622c = trap_R_RegisterShaderNoMip("menu/art/fx_white");
  _DAT_003b61ac = trap_R_RegisterShaderNoMip("ui/assets/scrollbar.tga");
  _DAT_003b61a0 = trap_R_RegisterShaderNoMip("ui/assets/scrollbar_arrow_dwn_a.tga");
  _DAT_003b619c = trap_R_RegisterShaderNoMip("ui/assets/scrollbar_arrow_up_a.tga");
  _DAT_003b61a4 = trap_R_RegisterShaderNoMip("ui/assets/scrollbar_arrow_left.tga");
  _DAT_003b61a8 = trap_R_RegisterShaderNoMip("ui/assets/scrollbar_arrow_right.tga");
  _DAT_003b61b0 = trap_R_RegisterShaderNoMip("ui/assets/scrollbar_thumb.tga");
  _DAT_003b61c0 = trap_R_RegisterShaderNoMip("ui/assets/slider2.tga");
  _DAT_003b61c4 = trap_R_RegisterShaderNoMip("ui/assets/sliderbutt_1.tga");
  g_dat_003b61c8 = trap_R_RegisterShaderNoMip("ui/assets/check.tga");
  g_dat_003b61cc = trap_R_RegisterShaderNoMip("ui/assets/check_not.tga");
  _DAT_003b61d0 = trap_R_RegisterShaderNoMip("ui/assets/check_no.tga");
  tmp_i2 = 0x61;
  tmp_pu4 = &g_dat_003b6230;
  do {
    tmp_u1 = va("gfx/2d/crosshair%c",tmp_i2);
    tmp_u1 = trap_R_RegisterShaderNoMip(tmp_u1);
    tmp_i3 = tmp_i2 + 1;
    *tmp_pu4 = tmp_u1;
    tmp_u1 = va("gfx/2d/crosshair%c_alt",tmp_i2);
    tmp_u1 = trap_R_RegisterShaderNoMip(tmp_u1);
    tmp_pu4[0x10] = tmp_u1;
    tmp_i2 = tmp_i3;
    tmp_pu4 = tmp_pu4 + 1;
  } while (tmp_i3 != 0x71);
  return;
}

void Text_PaintCharExt(uint32_t param_1,uint32_t param_2,float param_3,float param_4,
                      float param_5,float param_6,uint32_t param_7,uint32_t param_8,
                      uint32_t param_9,uint32_t param_10,uint32_t param_11)

{
  param_3 = param_3 * param_5;
  param_4 = param_4 * param_6;
  UI_AdjustFrom640(&param_1,&param_2,&param_3,&param_4);
  trap_R_DrawStretchPic(param_1,param_2,param_3,param_4,param_7,param_8,param_9,param_10,param_11);
  return;
}

void Text_PaintChar(uint32_t param_1,uint32_t param_2,float param_3,float param_4,float param_5,
                   uint32_t param_6,uint32_t param_7,uint32_t param_8,uint32_t param_9,
                   uint32_t param_10)

{
  param_3 = param_3 * param_5;
  param_4 = param_4 * param_5;
  UI_AdjustFrom640(&param_1,&param_2,&param_3,&param_4);
  trap_R_DrawStretchPic(param_1,param_2,param_3,param_4,param_6,param_7,param_8,param_9,param_10);
  return;
}

void Text_PaintWithCursor
               (float param_1,float param_2,float param_3,uint32_t *param_4,byte *param_5,
               size_t param_6,byte param_7,size_t param_8,int param_9)

{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  size_t tmp_s6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  uint tmp_u11;
  size_t local_94;
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
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  tmp_i8 = g_dat_003e7e2c;
  uStack_14 = 0x2b719;
  param_3 = param_3 * *(float *)(&g_dat_0039cffc + g_dat_003e7e2c * 0x5044);
  if (param_5 != (byte *)0x0) {
    trap_R_SetColor(param_4);
    local_2c = *param_4;
    local_28 = param_4[1];
    local_24 = param_4[2];
    local_20 = param_4[3];
    tmp_s6 = strlen((char *)param_5);
    if (((int)tmp_s6 <= (int)param_8) || ((int)param_8 < 1)) {
      param_8 = tmp_s6;
    }
    local_94 = 0;
    tmp_i7 = tmp_i8 * 0x5044;
    do {
      if ((*param_5 == 0) || ((int)param_8 <= (int)local_94)) break;
      tmp_u11 = (uint)*param_5;
      tmp_i10 = tmp_u11 * 0x50 + tmp_i7;
      tmp_i9 = *(int *)(&g_dat_00398000 + tmp_i10);
      if (param_9 == 6 || param_9 == 3) {
        GHIDRA_FIELD(colorBlack, 12, 4) = local_20;
        trap_R_SetColor(colorBlack);
        tmp_u5 = *(uint32_t *)(&g_dat_00398028 + tmp_i10);
        tmp_u1 = *(uint32_t *)(&g_dat_00398024 + tmp_i10);
        tmp_u2 = *(uint32_t *)(&g_dat_00398020 + tmp_i10);
        tmp_u3 = *(uint32_t *)(&g_dat_0039801c + tmp_i10);
        tmp_u4 = *(uint32_t *)(&g_dat_00398018 + tmp_i10);
        local_58 = (float)(int)(~-(uint)(param_9 != 3) + 2);
        local_5c = (float)*(int *)(&g_dat_00398008 + tmp_i10) * param_3 + param_1 + local_58;
        local_58 = local_58 + (param_2 - (float)tmp_i9 * param_3);
        local_54 = (float)*(int *)(&g_dat_00398010 + tmp_i10) * param_3;
        local_50 = param_3 * (float)*(int *)(&g_dat_00398014 + tmp_i10);
        UI_AdjustFrom640(&local_5c,&local_58,&local_54,&local_50);
        trap_R_DrawStretchPic(local_5c,local_58,local_54,local_50,tmp_u4,tmp_u3,tmp_u2,tmp_u1,tmp_u5);
        GHIDRA_FIELD(colorBlack, 12, 4) = 0x3f800000;
        trap_R_SetColor(&local_2c);
      }
      local_48 = param_2 - (float)tmp_i9 * param_3;
      tmp_i10 = tmp_u11 * 0x50 + tmp_i7;
      tmp_u1 = *(uint32_t *)(&g_dat_00398024 + tmp_i10);
      tmp_u5 = *(uint32_t *)(&g_dat_00398028 + tmp_i10);
      tmp_u2 = *(uint32_t *)(&g_dat_00398020 + tmp_i10);
      tmp_u3 = *(uint32_t *)(&g_dat_0039801c + tmp_i10);
      tmp_u4 = *(uint32_t *)(&g_dat_00398018 + tmp_i10);
      local_4c = (float)*(int *)(&g_dat_00398008 + tmp_i10) * param_3 + param_1;
      local_44 = (float)*(int *)(&g_dat_00398010 + tmp_i10) * param_3;
      local_40 = (float)*(int *)(&g_dat_00398014 + tmp_i10) * param_3;
      UI_AdjustFrom640(&local_4c,&local_48,&local_44,&local_40);
      trap_R_DrawStretchPic(local_4c,local_48,local_44,local_40,tmp_u4,tmp_u3,tmp_u2,tmp_u1,tmp_u5);
      tmp_i9 = (uint)param_7 * 0x50 + tmp_i7;
      if ((local_94 == param_6) && ((g_dat_00397fdc / 200 & 1U) == 0)) {
        Text_PaintChar((float)*(int *)(&g_dat_00398008 + tmp_i10) * param_3 + param_1,
                       param_2 - (float)*(int *)(&g_dat_00398000 + tmp_i9) * param_3,
                       (float)*(int *)(&g_dat_00398010 + tmp_i9),(float)*(int *)(&g_dat_00398014 + tmp_i9)
                       ,param_3,*(uint32_t *)(&g_dat_00398018 + tmp_i9),
                       *(uint32_t *)(&g_dat_0039801c + tmp_i9),*(uint32_t *)(&g_dat_00398020 + tmp_i9)
                       ,*(uint32_t *)(&g_dat_00398024 + tmp_i9),
                       *(uint32_t *)(&g_dat_00398028 + tmp_i9));
      }
      local_94 = local_94 + 1;
      param_5 = param_5 + 1;
      param_1 = (float)*(int *)(&g_dat_0039800c + tmp_u11 * 0x50 + tmp_i7) * param_3 + param_1;
    } while (param_5 != (byte *)0x0);
    if ((param_6 == param_8) && ((g_dat_00397fdc / 200 & 1U) == 0)) {
      tmp_i8 = tmp_i8 * 0x5044 + (uint)param_7 * 0x50;
      tmp_u1 = *(uint32_t *)(&g_dat_00398024 + tmp_i8);
      tmp_u5 = *(uint32_t *)(&g_dat_00398028 + tmp_i8);
      tmp_u2 = *(uint32_t *)(&g_dat_00398020 + tmp_i8);
      tmp_u3 = *(uint32_t *)(&g_dat_0039801c + tmp_i8);
      tmp_u4 = *(uint32_t *)(&g_dat_00398018 + tmp_i8);
      local_38 = param_2 - (float)*(int *)(&g_dat_00398000 + tmp_i8) * param_3;
      local_3c = (float)*(int *)(&g_dat_00398008 + tmp_i8) * param_3 + param_1;
      local_34 = (float)*(int *)(&g_dat_00398010 + tmp_i8) * param_3;
      local_30 = param_3 * (float)*(int *)(&g_dat_00398014 + tmp_i8);
      UI_AdjustFrom640(&local_3c,&local_38,&local_34,&local_30);
      trap_R_DrawStretchPic(local_3c,local_38,local_34,local_30,tmp_u4,tmp_u3,tmp_u2,tmp_u1,tmp_u5);
    }
    trap_R_SetColor(0);
  }
  return;
}

byte * Text_AutoWrap_Paint_Chunk
                 (float param_1,float param_2,int param_3,float param_4,uint32_t *param_5,
                 byte *param_6,float param_7,size_t param_8,int param_9,int param_10,
                 uint32_t *param_11)

{
  float tmp_f1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  byte tmp_b6;
  byte tmp_b7;
  uint32_t tmp_u8;
  float tmp_f9;
  float tmp_f10;
  int tmp_i11;
  size_t tmp_s12;
  int tmp_i13;
  byte *tmp_pb14;
  int tmp_i15;
  int tmp_i16;
  byte *local_60;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  tmp_i11 = g_dat_003e7e2c;
  uStack_14 = 0x2bd49;
  tmp_f1 = *(float *)(&g_dat_0039cffc + g_dat_003e7e2c * 0x5044);
  if (param_6 != (byte *)0x0) {
    trap_R_SetColor(param_5);
    local_2c = *param_5;
    local_28 = param_5[1];
    local_24 = param_5[2];
    local_20 = param_5[3];
    tmp_s12 = strlen((char *)param_6);
    if (((int)tmp_s12 <= (int)param_8) || ((int)param_8 < 1)) {
      param_8 = tmp_s12;
    }
    tmp_f1 = tmp_f1 * param_4;
    local_60 = (byte *)0x0;
    tmp_i15 = 0;
    tmp_pb14 = param_6;
    tmp_f9 = param_1;
    do {
      tmp_b6 = *tmp_pb14;
      if ((tmp_b6 == 0) || ((int)param_8 <= tmp_i15)) break;
      if (((byte)(tmp_b6 - 9) < 2) || (tmp_b6 == 0x20)) {
        local_60 = tmp_pb14;
      }
      if (tmp_b6 < 0x14) {
LAB_0002c037:
        tmp_pb14 = tmp_pb14 + 1;
        tmp_i15 = tmp_i15 + 1;
      }
      else {
        if (tmp_b6 != 0x5e) {
LAB_0002be9a:
          tmp_i13 = (uint)tmp_b6 * 0x50 + tmp_i11 * 0x5044;
          tmp_i16 = *(int *)(&g_dat_00398000 + tmp_i13);
          tmp_f10 = (float)*(int *)(&g_dat_0039800c + tmp_i13) * tmp_f1;
          if ((float)param_3 + param_1 < tmp_f10 + tmp_f9 + param_7) {
            if (local_60 != (byte *)0x0) {
              return local_60 + 1;
            }
            return tmp_pb14;
          }
          if (param_10 == 0) {
            if (param_9 == 6 || param_9 == 3) {
              GHIDRA_FIELD(colorBlack, 12, 4) = local_20;
              trap_R_SetColor(colorBlack);
              tmp_u8 = *(uint32_t *)(&g_dat_00398028 + tmp_i13);
              tmp_u2 = *(uint32_t *)(&g_dat_00398024 + tmp_i13);
              tmp_u3 = *(uint32_t *)(&g_dat_00398020 + tmp_i13);
              tmp_u4 = *(uint32_t *)(&g_dat_0039801c + tmp_i13);
              tmp_u5 = *(uint32_t *)(&g_dat_00398018 + tmp_i13);
              local_48 = (float)(int)(~-(uint)(param_9 != 3) + 2);
              local_4c = tmp_f9 + local_48;
              local_48 = local_48 + (param_2 - (float)tmp_i16 * tmp_f1);
              local_44 = (float)*(int *)(&g_dat_00398010 + tmp_i13) * tmp_f1;
              local_40 = tmp_f1 * (float)*(int *)(&g_dat_00398014 + tmp_i13);
              UI_AdjustFrom640(&local_4c,&local_48,&local_44,&local_40);
              trap_R_DrawStretchPic
                        (local_4c,local_48,local_44,local_40,tmp_u5,tmp_u4,tmp_u3,tmp_u2,tmp_u8);
              trap_R_SetColor(&local_2c);
              GHIDRA_FIELD(colorBlack, 12, 4) = 0x3f800000;
            }
            local_38 = param_2 - (float)tmp_i16 * tmp_f1;
            tmp_i16 = (uint)tmp_b6 * 0x50 + tmp_i11 * 0x5044;
            tmp_u2 = *(uint32_t *)(&g_dat_00398024 + tmp_i16);
            tmp_u8 = *(uint32_t *)(&g_dat_00398028 + tmp_i16);
            tmp_u3 = *(uint32_t *)(&g_dat_00398020 + tmp_i16);
            tmp_u4 = *(uint32_t *)(&g_dat_0039801c + tmp_i16);
            tmp_u5 = *(uint32_t *)(&g_dat_00398018 + tmp_i16);
            local_34 = (float)*(int *)(&g_dat_00398010 + tmp_i16) * tmp_f1;
            local_30 = (float)*(int *)(&g_dat_00398014 + tmp_i16) * tmp_f1;
            local_3c = tmp_f9;
            UI_AdjustFrom640(&local_3c,&local_38,&local_34,&local_30);
            trap_R_DrawStretchPic(local_3c,local_38,local_34,local_30,tmp_u5,tmp_u4,tmp_u3,tmp_u2,tmp_u8)
            ;
            tmp_f10 = (float)*(int *)(&g_dat_0039800c + tmp_i16) * tmp_f1;
          }
          tmp_f9 = tmp_f10 + param_7 + tmp_f9;
          goto LAB_0002c037;
        }
        tmp_b7 = tmp_pb14[1];
        if ((tmp_b7 == 0) || (tmp_b7 == 0x5e)) goto LAB_0002be9a;
        if (tmp_b7 == 0x2a) {
          local_2c = *param_5;
          local_28 = param_5[1];
          local_24 = param_5[2];
          local_20 = param_5[3];
        }
        else {
          tmp_i16 = ((int)(char)tmp_b7 - 0x30U & 0x1f) * 0x10;
          local_2c = *(uint32_t *)(g_color_table + tmp_i16);
          local_28 = *(uint32_t *)(g_color_table + tmp_i16 + 4);
          local_24 = *(uint32_t *)(g_color_table + tmp_i16 + 8);
          local_20 = param_5[3];
        }
        if (param_10 == 0) {
          trap_R_SetColor(&local_2c);
        }
        if (param_11 != (uint32_t *)0x0) {
          *param_11 = local_2c;
          param_11[1] = local_28;
          param_11[2] = local_24;
          param_11[3] = local_20;
        }
        tmp_pb14 = tmp_pb14 + 2;
      }
    } while (tmp_pb14 != (byte *)0x0);
    if (param_10 == 0) {
      trap_R_SetColor(0);
    }
  }
  tmp_s12 = strlen((char *)param_6);
  return param_6 + tmp_s12;
}

int Count_Text_AutoWrap_Paint
              (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
              uint32_t param_5,char *param_6,uint32_t param_7,uint32_t param_8)

{
  char *tmp_pc1;
  size_t tmp_s2;
  int tmp_i3;
  
  tmp_i3 = 0;
  tmp_s2 = strlen(param_6);
  tmp_pc1 = param_6 + tmp_s2;
  do {
    tmp_i3 = tmp_i3 + 1;
    param_6 = (char *)Text_AutoWrap_Paint_Chunk_constprop_56
                                (param_1,param_2,param_4,param_6,param_7,param_8,0);
  } while (param_6 < tmp_pc1);
  return tmp_i3;
}

void Text_AutoWrap_Paint(float param_1,float param_2,uint32_t param_3,int param_4,float param_5,
                        uint32_t *param_6,uint32_t param_7,float param_8,int param_9)

{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  byte tmp_b5;
  byte tmp_b6;
  uint32_t tmp_u7;
  float tmp_f8;
  uint tmp_u9;
  uint tmp_u10;
  uint *tmp_pu11;
  size_t tmp_s12;
  int tmp_i13;
  uint *tmp_pu14;
  uint *tmp_pu15;
  int tmp_i16;
  int tmp_i17;
  int tmp_i18;
  float local_4bc;
  float local_46c;
  float local_468;
  float local_464;
  float local_460;
  float local_45c;
  float local_458;
  float local_454;
  float local_450;
  uint32_t local_44c;
  uint32_t local_448;
  uint32_t local_444;
  uint32_t local_440;
  uint32_t local_43c;
  uint32_t local_438;
  uint32_t local_434;
  uint32_t local_430;
  uint32_t local_42c;
  uint32_t local_428;
  uint32_t local_424;
  uint32_t local_420;
  uint local_41c [259];
  
  Q_strncpyz(local_41c,param_7,0x3ff);
  tmp_pu14 = local_41c;
  do {
    tmp_pu15 = tmp_pu14;
    tmp_u9 = *tmp_pu15 + 0xfefefeff & ~*tmp_pu15;
    tmp_u10 = tmp_u9 & 0x80808080;
    tmp_pu14 = tmp_pu15 + 1;
  } while (tmp_u10 == 0);
  if ((tmp_u9 & 0x8080) == 0) {
    tmp_pu14 = (uint *)((int)tmp_pu15 + 6);
    tmp_u10 = tmp_u10 >> 0x10;
  }
  local_44c = *param_6;
  local_448 = param_6[1];
  local_444 = param_6[2];
  local_440 = param_6[3];
  tmp_pu15 = local_41c;
  do {
    tmp_pu11 = (uint *)Text_AutoWrap_Paint_Chunk_constprop_56
                                (param_1,param_2,param_5,tmp_pu15,param_8,param_9,&local_43c);
    tmp_u9 = *tmp_pu11;
    *(byte *)tmp_pu11 = 0;
    tmp_i16 = g_dat_003e7e2c * 0x5044;
    tmp_f8 = param_5 * *(float *)(&g_dat_0039cffc + tmp_i16);
    if (tmp_pu15 != (uint *)0x0) {
      trap_R_SetColor(&local_44c);
      local_42c = local_44c;
      local_428 = local_448;
      local_424 = local_444;
      local_420 = local_440;
      tmp_s12 = strlen((char *)tmp_pu15);
      tmp_i18 = 0;
      local_4bc = param_1;
      do {
        tmp_b5 = (byte)*tmp_pu15;
        if ((tmp_b5 == 0) || ((int)tmp_s12 <= tmp_i18)) break;
        if (tmp_b5 < 0x14) {
LAB_0002c782:
          tmp_pu15 = (uint *)((int)tmp_pu15 + 1);
          tmp_i18 = tmp_i18 + 1;
        }
        else {
          if (tmp_b5 != 0x5e) {
LAB_0002c626:
            tmp_i17 = (uint)tmp_b5 * 0x50 + tmp_i16;
            tmp_i13 = *(int *)(&g_dat_00398000 + tmp_i17);
            if (param_9 == 6 || param_9 == 3) {
              GHIDRA_FIELD(colorBlack, 12, 4) = local_420;
              trap_R_SetColor(colorBlack);
              tmp_u7 = *(uint32_t *)(&g_dat_00398028 + tmp_i17);
              tmp_u1 = *(uint32_t *)(&g_dat_00398024 + tmp_i17);
              tmp_u2 = *(uint32_t *)(&g_dat_00398020 + tmp_i17);
              tmp_u3 = *(uint32_t *)(&g_dat_0039801c + tmp_i17);
              tmp_u4 = *(uint32_t *)(&g_dat_00398018 + tmp_i17);
              local_468 = (float)(int)(~-(uint)(param_9 != 3) + 2);
              local_46c = (float)*(int *)(&g_dat_00398008 + tmp_i17) * tmp_f8 + local_4bc + local_468;
              local_468 = local_468 + (param_2 - (float)tmp_i13 * tmp_f8);
              local_464 = (float)*(int *)(&g_dat_00398010 + tmp_i17) * tmp_f8;
              local_460 = tmp_f8 * (float)*(int *)(&g_dat_00398014 + tmp_i17);
              UI_AdjustFrom640(&local_46c,&local_468,&local_464,&local_460);
              trap_R_DrawStretchPic
                        (local_46c,local_468,local_464,local_460,tmp_u4,tmp_u3,tmp_u2,tmp_u1,tmp_u7);
              trap_R_SetColor(&local_42c);
              GHIDRA_FIELD(colorBlack, 12, 4) = 0x3f800000;
            }
            local_458 = param_2 - (float)tmp_i13 * tmp_f8;
            tmp_i13 = (uint)tmp_b5 * 0x50 + tmp_i16;
            tmp_u1 = *(uint32_t *)(&g_dat_00398024 + tmp_i13);
            tmp_u7 = *(uint32_t *)(&g_dat_00398028 + tmp_i13);
            tmp_u2 = *(uint32_t *)(&g_dat_00398020 + tmp_i13);
            tmp_u3 = *(uint32_t *)(&g_dat_0039801c + tmp_i13);
            tmp_u4 = *(uint32_t *)(&g_dat_00398018 + tmp_i13);
            local_45c = (float)*(int *)(&g_dat_00398008 + tmp_i13) * tmp_f8 + local_4bc;
            local_454 = (float)*(int *)(&g_dat_00398010 + tmp_i13) * tmp_f8;
            local_450 = (float)*(int *)(&g_dat_00398014 + tmp_i13) * tmp_f8;
            UI_AdjustFrom640(&local_45c,&local_458,&local_454,&local_450);
            trap_R_DrawStretchPic
                      (local_45c,local_458,local_454,local_450,tmp_u4,tmp_u3,tmp_u2,tmp_u1,tmp_u7);
            local_4bc = (float)*(int *)(&g_dat_0039800c + tmp_i13) * tmp_f8 + param_8 + local_4bc;
            goto LAB_0002c782;
          }
          tmp_b6 = *(byte *)((int)tmp_pu15 + 1);
          if ((tmp_b6 == 0) || (tmp_b6 == 0x5e)) goto LAB_0002c626;
          if (tmp_b6 == 0x2a) {
            local_42c = local_44c;
            local_428 = local_448;
            local_424 = local_444;
          }
          else {
            tmp_i13 = ((int)(char)tmp_b6 - 0x30U & 0x1f) * 0x10;
            local_42c = *(uint32_t *)(g_color_table + tmp_i13);
            local_428 = *(uint32_t *)(g_color_table + tmp_i13 + 4);
            local_424 = *(uint32_t *)(g_color_table + tmp_i13 + 8);
          }
          local_420 = local_440;
          tmp_pu15 = (uint *)((int)tmp_pu15 + 2);
          trap_R_SetColor(&local_42c);
        }
      } while (tmp_pu15 != (uint *)0x0);
      trap_R_SetColor(0);
    }
    *(byte *)tmp_pu11 = (byte)tmp_u9;
    param_2 = (float)param_4 + param_2;
    local_44c = local_43c;
    local_448 = local_438;
    local_444 = local_434;
    local_440 = local_430;
    tmp_pu15 = tmp_pu11;
    if ((uint *)((int)tmp_pu14 + (-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10))) <= tmp_pu11) {
      return;
    }
  } while( true );
}

void UI_ShowPostGame(uint32_t param_1)

{
  trap_Cvar_Set("cg_cameraOrbit","0");
  trap_Cvar_Set("cg_thirdPerson","0");
  trap_Cvar_Set("sv_killserver","1");
  _DAT_003b7f34 = param_1;
  _UI_SetActiveMenu_constprop_61();
  return;
}

void UI_DrawCenteredPic(uint32_t param_1,int param_2,int param_3)

{
  UI_DrawHandlePic((float)(int)ROUND((float)(0x280 - param_2) * 0.5),
                   (float)(int)ROUND((float)(0x1e0 - param_3) * 0.5),(float)param_2,(float)param_3,
                   param_1);
  return;
}

void _UI_Refresh(int param_1)

{
  int tmp_i1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  uint8_t **tmp_ppu4;
  long double tmp_l5;
  uint local_c28 [773];
  uint32_t uStack_14;
  
  tmp_i1 = g_dat_00397fdc;
  uStack_14 = 0x2cb49;
  g_dat_00397fdc = param_1;
  g_dat_00397fe0 = param_1 - tmp_i1;
  tmp_i1 = index_9483 + 1;
  (&previousTimes_9484)[index_9483 % 4] = g_dat_00397fe0;
  if (4 < tmp_i1) {
    tmp_i2 = _DAT_0008c110 + previousTimes_9484 + g_dat_0008c114 + g_dat_0008c118;
    if (tmp_i2 == 0) {
      _DAT_003b7f1c = 4000.0;
    }
    else {
      _DAT_003b7f1c = (float)(int)(4000 / (longlong)tmp_i2);
    }
  }
  index_9483 = tmp_i1;
  if (0 < cvarTableSize) {
    tmp_i2 = 0;
    tmp_ppu4 = &cvarTable;
    tmp_i1 = cvarTableSize;
    do {
      if (*tmp_ppu4 != (uint8_t *)0x0) {
        trap_Cvar_Update(*tmp_ppu4);
        tmp_pu3 = *tmp_ppu4;
        tmp_i1 = cvarTableSize;
        if (tmp_ppu4[4] != *(uint8_t **)(tmp_pu3 + 4)) {
          tmp_ppu4[4] = *(uint8_t **)(tmp_pu3 + 4);
          if ((tmp_pu3 == cg_crosshairColor) || (tmp_pu3 == cg_crosshairAlpha)) {
            BG_setCrosshair(0x393490,&g_dat_003e8034,GHIDRA_FIELD(cg_crosshairAlpha, 8, 4),"cg_crosshairColor");
            tmp_pu3 = *tmp_ppu4;
          }
          if ((tmp_pu3 == cg_crosshairColorAlt) ||
             (tmp_i1 = cvarTableSize, tmp_pu3 == cg_crosshairAlphaAlt)) {
            BG_setCrosshair(0x396bb0,&g_dat_003e8044,GHIDRA_FIELD(cg_crosshairAlphaAlt, 8, 4),"cg_crosshairColorAlt"
                           );
            tmp_i1 = cvarTableSize;
          }
        }
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_ppu4 = tmp_ppu4 + 5;
    } while (tmp_i2 < tmp_i1);
  }
  tmp_l5 = (long double)trap_Cvar_VariableValue("ui_connecting");
  if (tmp_l5 != (long double)0) {
    UI_DrawLoadPanel(1,0,1);
    tmp_l5 = (long double)trap_Cvar_VariableValue("ui_connecting");
    if (tmp_l5 != (long double)0) {
      return;
    }
    trap_Cvar_Set("ui_connecting","1");
    return;
  }
  if (0 < (int)GHIDRA_FIELD(ui_blackout, 12, 4)) {
    UI_FillRect(0xc1200000,0xc1200000,0x44228000,0x43f50000,colorBlack);
  }
  tmp_i1 = Menu_Count();
  if (tmp_i1 < 1) goto LAB_0002cd87;
  Menu_PaintAll();
  if (g_dat_003e13b8 != 0) {
    if (GHIDRA_FIELD(ui_netSource, 12, 4) == 2) {
LAB_0002cef3:
      tmp_i1 = trap_LAN_UpdateVisiblePings(GHIDRA_FIELD(ui_netSource, 12, 4));
      if (tmp_i1 == 0) {
        if (_DAT_003e53c8 < _DAT_003e53c4) {
          _DAT_003e13ac = g_dat_00397fdc + 0x32;
        }
        else {
          UI_BuildServerDisplayList();
          if (g_dat_003e13b8 != 0) {
            g_dat_003e13b8 = 0;
            Com_Printf("^g%d ^9servers listed in browser with %d players (^7%d ^9humans).\n",
                       g_dat_003e53c0,g_dat_003e53d0,g_dat_003e53d4);
            tmp_i1 = trap_LAN_GetServerCount(GHIDRA_FIELD(ui_netSource, 12, 4));
            tmp_i1 = tmp_i1 - g_dat_003e53c0;
            if (0 < tmp_i1) {
              Com_Printf("^8%d ^9servers not listed:\n- ^3%d ^9filtered out by game browser settings\n- ^1%d ^9dropped (fake, serverfacades, no or bad statusResponse)\n"
                         ,tmp_i1,tmp_i1 - g_dat_003e53cc,g_dat_003e53cc);
            }
          }
        }
      }
      else {
LAB_0002cf30:
        _DAT_003e13ac = g_dat_00397fdc + 1000;
      }
    }
    else {
      if (GHIDRA_FIELD(ui_netSource, 12, 4) == 0) {
        tmp_i1 = trap_LAN_GetServerCount(0);
        if (tmp_i1 != 0) goto LAB_0002cef3;
      }
      else {
        tmp_i1 = trap_LAN_GetServerCount(GHIDRA_FIELD(ui_netSource, 12, 4));
        if (-1 < tmp_i1) goto LAB_0002cef3;
      }
      if (g_dat_00397fdc < _DAT_003e13ac) goto LAB_0002cd00;
      tmp_i1 = trap_LAN_UpdateVisiblePings(GHIDRA_FIELD(ui_netSource, 12, 4));
      if (tmp_i1 != 0) goto LAB_0002cf30;
    }
    UI_BuildServerDisplayList();
  }
LAB_0002cd00:
  trap_GetClientState(local_c28);
  if ((((_DAT_003e7e10 == 0) && (_DAT_003e6940 != 0)) && (_DAT_003e6940 <= g_dat_00397fdc)) &&
     ((4 < local_c28[0] ||
      (((-1 < _DAT_003e13bc && (_DAT_003e13bc <= g_dat_003e53c0)) && (g_dat_003e53c0 != 0)))))) {
    tmp_i1 = UI_GetServerStatusInfo();
    if (tmp_i1 == 0) {
      _DAT_003e6940 = g_dat_00397fdc + 500;
    }
    else {
      _DAT_003e6940 = 0;
      trap_LAN_ServerStatus(&g_dat_003e57fc,0,0);
    }
  }
  UI_BuildFindPlayerList();
LAB_0002cd87:
  UI_SetColor(0);
  tmp_i1 = Menu_Count();
  if ((0 < tmp_i1) && (trap_GetClientState(local_c28), 5 < local_c28[0] - 2)) {
    UI_DrawHandlePic((float)g_dat_00397fe4,(float)g_dat_00397fe8,0x42000000,0x42000000,_DAT_003b6194);
    return;
  }
  return;
}

void _UI_Shutdown(void)

{
  trap_LAN_SaveCachedServers();
  return;
}

uint8_t * GetMenuBuffer(uint32_t param_1)

{
  int tmp_i1;
  uint32_t tmp_u2;
  int local_10 [2];
  
  tmp_i1 = trap_FS_FOpenFile(param_1,local_10,0);
  if (local_10[0] == 0) {
    tmp_u2 = va("^1menu file not found: %s, using default\n",param_1);
    trap_Print(tmp_u2);
    return defaultMenu;
  }
  if (tmp_i1 < 0x8000) {
    trap_FS_Read(buf_9500,tmp_i1,local_10[0]);
    buf_9500[tmp_i1] = 0;
    trap_FS_FCloseFile(local_10[0]);
    return buf_9500;
  }
  tmp_u2 = va("^1menu file too large: %s is %i, max allowed is %i",param_1,tmp_i1,0x8000);
  trap_Print(tmp_u2);
  trap_FS_FCloseFile(local_10[0]);
  return defaultMenu;
}

uint32_t Asset_Parse(uint32_t param_1)

{
  int tmp_i1;
  uint8_t *tmp_pu2;
  uint tmp_u3;
  uint32_t *tmp_pu4;
  byte tmp_b5;
  uint32_t local_440;
  uint32_t local_43c;
  uint local_438;
  uint32_t local_434;
  uint32_t local_430 [3];
  uint8_t local_424 [1044];
  
  tmp_b5 = 0;
  tmp_i1 = trap_PC_ReadToken(param_1,&local_434);
  if (tmp_i1 == 0) {
    return 0;
  }
  tmp_i1 = Q_stricmp(local_424,&g_dat_00055ec2);
  if (tmp_i1 != 0) {
    return 0;
  }
LAB_0002d194:
  while( true ) {
    while( true ) {
      while( true ) {
        while( true ) {
          while( true ) {
            while( true ) {
              while( true ) {
                tmp_u3 = 0x418;
                tmp_pu4 = &local_434;
                if (((uint)&local_434 & 4) != 0) {
                  local_434 = 0;
                  tmp_pu4 = local_430;
                  tmp_u3 = 0x414;
                }
                for (tmp_u3 = tmp_u3 >> 2; tmp_u3 != 0; tmp_u3 = tmp_u3 - 1) {
                  *tmp_pu4 = 0;
                  tmp_pu4 = tmp_pu4 + (uint)tmp_b5 * -2 + 1;
                }
                tmp_i1 = trap_PC_ReadToken(param_1,&local_434);
                if (tmp_i1 == 0) {
                  return 0;
                }
                tmp_i1 = Q_stricmp(local_424,&g_dat_00055b39);
                if (tmp_i1 == 0) {
                  return 1;
                }
                tmp_i1 = Q_stricmp(local_424,"font");
                if (tmp_i1 != 0) break;
                tmp_i1 = PC_Int_Parse(param_1,&local_438);
                if (tmp_i1 == 0) {
                  return 0;
                }
                tmp_i1 = PC_String_Parse(param_1,&local_440);
                if (tmp_i1 == 0) {
                  return 0;
                }
                tmp_i1 = PC_Int_Parse(param_1,&local_43c);
                if (tmp_i1 == 0) {
                  return 0;
                }
                if (5 < local_438) {
                  return 0;
                }
                trap_R_RegisterFont(local_440,local_43c,&g_dat_00397ffc + local_438 * 0x5044);
                _DAT_003b620c = 1;
              }
              tmp_i1 = Q_stricmp(local_424,"gradientbar");
              if (tmp_i1 != 0) break;
              tmp_i1 = PC_String_Parse(param_1,&local_440);
              if (tmp_i1 == 0) {
                return 0;
              }
              _DAT_003b6198 = trap_R_RegisterShaderNoMip(local_440);
            }
            tmp_i1 = Q_stricmp(local_424,"menuEnterSound");
            if (tmp_i1 != 0) break;
            tmp_i1 = PC_String_Parse(param_1,&local_440);
            if (tmp_i1 == 0) {
              return 0;
            }
            _DAT_003b61d4 = trap_S_RegisterSound(local_440,1);
          }
          tmp_i1 = Q_stricmp(local_424,"menuExitSound");
          if (tmp_i1 != 0) break;
          tmp_i1 = PC_String_Parse(param_1,&local_440);
          if (tmp_i1 == 0) {
            return 0;
          }
          _DAT_003b61d8 = trap_S_RegisterSound(local_440,1);
        }
        tmp_i1 = Q_stricmp(local_424,"itemFocusSound");
        if (tmp_i1 != 0) break;
        tmp_i1 = PC_String_Parse(param_1,&local_440);
        if (tmp_i1 == 0) {
          return 0;
        }
        _DAT_003b61e0 = trap_S_RegisterSound(local_440,1);
      }
      tmp_i1 = Q_stricmp(local_424,"menuBuzzSound");
      if (tmp_i1 != 0) break;
      tmp_i1 = PC_String_Parse(param_1,&local_440);
      if (tmp_i1 == 0) {
        return 0;
      }
      _DAT_003b61dc = trap_S_RegisterSound(local_440,1);
    }
    tmp_i1 = Q_stricmp(local_424,"cursor");
    if (tmp_i1 != 0) break;
    tmp_i1 = PC_String_Parse(param_1,&g_dat_00397ff4);
    if (tmp_i1 == 0) {
      return 0;
    }
    _DAT_003b6194 = trap_R_RegisterShaderNoMip(_DAT_00397ff4);
  }
  tmp_i1 = Q_stricmp(local_424,"fadeClamp");
  if (tmp_i1 == 0) {
    tmp_pu2 = &g_dat_003b61e4;
  }
  else {
    tmp_i1 = Q_stricmp(local_424,"fadeCycle");
    if (tmp_i1 == 0) {
      tmp_i1 = PC_Int_Parse(param_1,&g_dat_003b61e8);
      goto joined_r0x0002d52c;
    }
    tmp_i1 = Q_stricmp(local_424,"fadeAmount");
    if (tmp_i1 == 0) {
      tmp_pu2 = &g_dat_003b61ec;
    }
    else {
      tmp_i1 = Q_stricmp(local_424,"shadowX");
      if (tmp_i1 != 0) {
        tmp_i1 = Q_stricmp(local_424,"shadowY");
        if (tmp_i1 == 0) {
          tmp_pu2 = &g_dat_003b61f4;
          goto LAB_0002d4db;
        }
        tmp_i1 = Q_stricmp(local_424,"shadowColor");
        if (tmp_i1 == 0) {
          tmp_i1 = PC_Color_Parse(param_1,&g_dat_003b61f8);
          if (tmp_i1 == 0) {
            return 0;
          }
          _DAT_003b6208 = _DAT_003b6204;
        }
        goto LAB_0002d194;
      }
      tmp_pu2 = &g_dat_003b61f0;
    }
  }
LAB_0002d4db:
  tmp_i1 = PC_Float_Parse(param_1,tmp_pu2);
joined_r0x0002d52c:
  if (tmp_i1 == 0) {
    return 0;
  }
  goto LAB_0002d194;
}

void UI_Report(void)

{
  String_Report();
  return;
}

uint32_t UI_ParseMenu(uint32_t param_1)

{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint tmp_u4;
  uint32_t *tmp_pu5;
  byte tmp_b6;
  uint32_t local_434;
  uint32_t local_430 [3];
  char local_424 [1040];
  uint32_t uStack_14;
  
  tmp_b6 = 0;
  uStack_14 = 0x2d619;
  Com_DPrintf("Parsing menu file: %s\n",param_1);
  tmp_i1 = trap_PC_LoadSource(param_1);
  tmp_u2 = 0;
  if (tmp_i1 != 0) {
    do {
      while( true ) {
        tmp_u4 = 0x418;
        tmp_pu5 = &local_434;
        if (((uint)&local_434 & 4) != 0) {
          local_434 = 0;
          tmp_pu5 = local_430;
          tmp_u4 = 0x414;
        }
        for (tmp_u4 = tmp_u4 >> 2; tmp_u4 != 0; tmp_u4 = tmp_u4 - 1) {
          *tmp_pu5 = 0;
          tmp_pu5 = tmp_pu5 + (uint)tmp_b6 * -2 + 1;
        }
        tmp_i3 = trap_PC_ReadToken(tmp_i1,&local_434);
        if ((tmp_i3 == 0) || (local_424[0] == '}')) goto LAB_0002d6b1;
        tmp_i3 = Q_stricmp(local_424,"assetGlobalDef");
        if (tmp_i3 == 0) break;
        tmp_i3 = Q_stricmp(local_424,"menudef");
        if (tmp_i3 == 0) {
          Menu_New(tmp_i1);
        }
      }
      tmp_i3 = Asset_Parse(tmp_i1);
    } while (tmp_i3 != 0);
LAB_0002d6b1:
    trap_PC_FreeSource(tmp_i1);
    tmp_u2 = 1;
  }
  return tmp_u2;
}

uint32_t Load_Menu(uint32_t param_1)

{
  int tmp_i1;
  uint8_t local_434 [16];
  char local_424 [1044];
  
  tmp_i1 = trap_PC_ReadToken(param_1,local_434);
  if ((tmp_i1 != 0) && (local_424[0] == '{')) {
    while ((tmp_i1 = trap_PC_ReadToken(param_1,local_434), tmp_i1 != 0 && (local_424[0] != '\0'))) {
      if (local_424[0] == '}') {
        return 1;
      }
      UI_ParseMenu(local_424);
    }
  }
  return 0;
}

void UI_LoadMenus(uint32_t param_1,int param_2)

{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint8_t local_1458 [16];
  char local_1448 [1032];
  uint8_t local_1040 [16];
  char local_1030 [1032];
  uint local_c28 [773];
  uint32_t uStack_14;
  
  uStack_14 = 0x2d7f9;
  tmp_i1 = trap_Milliseconds();
  trap_GetClientState(local_c28);
  if (local_c28[0] < 2) {
    trap_PC_AddGlobalDefine(&g_dat_00055f7a);
  }
  tmp_u2 = va("_WINDOW_WIDTH %f",(double)((g_dat_003b7efc / 1.3333334) * 640.0));
  trap_PC_AddGlobalDefine(tmp_u2);
  trap_PC_AddGlobalDefine("_WINDOW_HEIGHT 480");
  tmp_i3 = trap_PC_LoadSource(param_1);
  if (tmp_i3 == 0) {
    tmp_u2 = va("^3menu file not found: %s, using default\n",param_1);
    trap_Error(tmp_u2);
    tmp_i3 = trap_PC_LoadSource("ui/menus.txt");
    if (tmp_i3 == 0) {
      trap_Error("^1default menu file not found: ui_mp/menus.txt, unable to continue!\n");
    }
  }
  GHIDRA_FIELD(ui_new, 12, 4) = 1;
  if (param_2 != 0) {
    Menu_Reset();
  }
  while( true ) {
    do {
      tmp_i4 = trap_PC_ReadToken(tmp_i3,local_1458);
      if (((tmp_i4 == 0) || (local_1448[0] == '\0')) || (local_1448[0] == '}')) goto LAB_0002d8dd;
      tmp_i4 = Q_stricmp(local_1448,"loadmenu");
    } while (tmp_i4 != 0);
    tmp_i4 = trap_PC_ReadToken(tmp_i3,local_1040);
    if ((tmp_i4 == 0) || (local_1030[0] != '{')) break;
    while( true ) {
      tmp_i4 = trap_PC_ReadToken(tmp_i3,local_1040);
      if ((tmp_i4 == 0) || (local_1030[0] == '\0')) goto LAB_0002d8dd;
      if (local_1030[0] == '}') break;
      UI_ParseMenu(local_1030);
    }
  }
LAB_0002d8dd:
  tmp_i4 = trap_Milliseconds();
  Com_DPrintf("UI menu load time = %d milli seconds\n",tmp_i4 - tmp_i1);
  trap_PC_FreeSource(tmp_i3);
  return;
}

void UI_Load(void)

{
{  int tmp_i1;
  char *tmp_pc2;
  char local_40c [1024];
  
  tmp_i1 = Menu_GetFocused();
  tmp_pc2 = (char *)UI_Cvar_VariableString("ui_menuFiles");
  if ((tmp_i1 != 0) && (*(char **)(tmp_i1 + 0x20) != (char *)0x0)) {
    strcpy(local_40c,*(char **)(tmp_i1 + 0x20));
  }
  if (tmp_pc2 == (char *)0x0) {
    tmp_pc2 = "ui/menus.txt";
  }
  else if (*tmp_pc2 == '\0') {
    tmp_pc2 = "ui/menus.txt";
  }
  String_Init();
  UI_ParseGameInfo_constprop_57();
  UI_LoadArenas();
  UI_LoadCampaigns();
  UI_LoadMenus(tmp_pc2,1);
  Menus_CloseAll();
  Menus_ActivateByName(local_40c,1);
  return;
}

    if ((((tmp_i11 != 0) && (tmp_f3 = (float)(int)tmp_f6, tmp_f6 = param_1[2], tmp_f6 < tmp_f3)) ||
        ((tmp_b7 & 0xdf) == 10)) || (tmp_b7 == 0)) {
{      if (tmp_i9 != 0) {
        if (param_7 == 0) {
          local_430 = param_4;
        }
        else if (param_7 == 2) {
          local_430 = param_4 - (float)(int)local_444;
        }
        else if (param_7 == 1) {
          local_430 = param_4 - (float)(int)local_444 * 0.5;
        }
        local_41c[tmp_i11] = 0;
        local_430 = local_430 + *param_1;
        (**(void **)(DC + 0x10))
                  (local_430,local_43c + param_1[1],param_2,param_3,local_41c,0,0,param_6,tmp_f6);
        tmp_b7 = *__s;
      }
      if (tmp_b7 == 0) {
        return;
      }
      tmp_i11 = 0;
      local_43c = (float)((int)ROUND(tmp_f2 * param_2 * tmp_f1) + 5) + local_43c;
      tmp_i10 = 0;
      local_444 = 0.0;
      __s = (char *)local_438;
    }

    if (((byte)(tmp_b5 - 9) < 2) || ((tmp_b5 & 0xdf) == 0)) {
{      local_43c = (byte *)(__s + 1);
      tmp_i6 = tmp_i8;
      local_440 = tmp_i3;
LAB_0002ebb0:
      if (tmp_i6 == 0) {
LAB_0002ebd2:
        if ((tmp_b5 == 10) || (tmp_b5 == 0)) goto LAB_0002ec30;
        if (tmp_b5 != 0x2a) {
          if (tmp_b5 == 0xd) {
            local_41c[tmp_i8] = 0x20;
          }
          else {
            local_41c[tmp_i8] = tmp_b5;
          }
          goto LAB_0002ebf9;
        }
        if (__s[1] != 0x2a) goto LAB_0002ed16;
        if (tmp_i8 == 0) goto LAB_0002ecd3;
LAB_0002ec38:
        if (param_7 == 0) {
          local_434 = param_4;
        }
        else if (param_7 == 2) {
          local_434 = param_4 - (float)local_440;
        }
        else if (param_7 == 1) {
          local_434 = param_4 - (float)local_440 * 0.5;
        }
        local_41c[tmp_i6] = 0;
        local_434 = local_434 + *param_1;
        (**(void **)(DC + 0x10))
                  (local_434,local_438 + param_1[1],param_2,param_3,local_41c,0,0,param_6);
        tmp_b5 = *__s;
      }
      else {
LAB_0002ebb4:
        if ((float)tmp_i3 <= param_1[2]) goto LAB_0002ebd2;
LAB_0002ec30:
        if (tmp_i8 != 0) goto LAB_0002ec38;
      }
      if (tmp_b5 == 0) {
        return;
      }
LAB_0002ecd3:
      tmp_i6 = 0;
      local_438 = (float)((int)ROUND(tmp_f2 * param_2 * tmp_f1) + 5) + local_438;
      tmp_i3 = 0;
      local_440 = 0;
      __s = (char *)local_43c;
    }

void UI_ServersSort(int param_1,int param_2)

{
{  void *__compar;
  
  if ((param_2 != 0) || (_DAT_003e13b0 != param_1)) {
    _DAT_003e13b0 = param_1;
    if (param_1 == 2) {
      __compar = UI_ServersQsortCompare_bis;
    }
    else {
      __compar = UI_ServersQsortCompare;
    }
    qsort(&g_dat_003e13c0,g_dat_003e53c0,4,__compar);
  }
  return;
}

void WM_setVisibility(uint32_t param_1,int param_2)

{
{  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = Menu_GetFocused();
  tmp_i2 = Menu_FindItemByName(tmp_u1,param_1);
  if (tmp_i2 != 0) {
    if (param_2 != 0) {
      *(uint *)(tmp_i2 + 0x48) = *(uint *)(tmp_i2 + 0x48) | 4;
      return;
    }
    *(uint *)(tmp_i2 + 0x48) = *(uint *)(tmp_i2 + 0x48) & 0xfffffffa;
  }
  return;
}

void UI_Update(uint32_t param_1)

{
{  int tmp_i1;
  int tmp_i2;
  long double tmp_l3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  
  tmp_l3 = (long double)trap_Cvar_VariableValue(param_1);
  tmp_i1 = Q_stricmp(param_1,"ui_SetName");
  if (tmp_i1 == 0) {
    tmp_u4 = UI_Cvar_VariableString("ui_Name");
    trap_Cvar_Set("name",tmp_u4);
  }
  else {
    tmp_i1 = Q_stricmp(param_1,"ui_setRate");
    if (tmp_i1 == 0) {
      tmp_l3 = (long double)trap_Cvar_VariableValue("ui_rate");
      if ((long double)5000.0 <= tmp_l3) {
        tmp_pc5 = "100";
      }
      else {
        tmp_pc5 = "15";
        if ((long double)4000.0 <= tmp_l3) {
          trap_Cvar_Set("ui_cl_maxpackets","15");
          trap_Cvar_Set("ui_cl_packetdup","2");
          return;
        }
      }
      trap_Cvar_Set("ui_cl_maxpackets",tmp_pc5);
      trap_Cvar_Set("ui_cl_packetdup","1");
      return;
    }
    tmp_i1 = Q_stricmp(param_1,"ui_GetName");
    if (tmp_i1 == 0) {
      tmp_u4 = UI_Cvar_VariableString("name");
      trap_Cvar_Set("ui_Name",tmp_u4);
      return;
    }
    tmp_i1 = (int)ROUND((float)tmp_l3);
    tmp_i2 = Q_stricmp(param_1,"r_colorbits");
    if (tmp_i2 == 0) {
      if (tmp_i1 == 0x10) {
        tmp_u4 = 0x41800000;
      }
      else {
        if (tmp_i1 == 0x20) {
          trap_Cvar_SetValue("r_depthbits",0x41c00000);
          return;
        }
        if (tmp_i1 != 0) {
          return;
        }
        tmp_u4 = 0;
      }
      trap_Cvar_SetValue("r_depthbits",tmp_u4);
      trap_Cvar_SetValue("r_stencilbits",0);
    }
    else {
      tmp_i2 = Q_stricmp(param_1,"ui_r_lodbias");
      if (tmp_i2 == 0) {
        if (tmp_i1 == 1) {
          trap_Cvar_SetValue("ui_r_subdivisions",0x41400000);
        }
        else if (tmp_i1 == 2) {
          trap_Cvar_SetValue("ui_r_subdivisions",0x41a00000);
        }
        else if (tmp_i1 == 0) {
          trap_Cvar_SetValue("ui_r_subdivisions",0x40800000);
        }
      }
      else {
        tmp_i2 = Q_stricmp(param_1,"ui_glCustom");
        if (tmp_i2 == 0) {
          if (tmp_i1 == 1) {
            trap_Cmd_ExecuteText(2,"exec preset_normal_ui.cfg\n");
          }
          else if (tmp_i1 < 2) {
            if (tmp_i1 == 0) {
              trap_Cmd_ExecuteText(2,"exec preset_high_ui.cfg\n");
            }
          }
          else if (tmp_i1 == 2) {
            trap_Cmd_ExecuteText(2,"exec preset_fast_ui.cfg\n");
          }
          else if (tmp_i1 == 3) {
            trap_Cmd_ExecuteText(2,"exec preset_fastest_ui.cfg\n");
          }
        }
        else {
          tmp_i2 = Q_stricmp(param_1,"ui_mousePitch");
          if (tmp_i2 == 0) {
            if (tmp_i1 == 0) {
              trap_Cvar_SetValue("m_pitch",0x3cb43958);
            }
            else {
              trap_Cvar_SetValue("m_pitch",0xbcb43958);
            }
          }
        }
      }
    }
  }
  return;
}

void _UI_MouseEvent(int param_1,int param_2)

{
{  int tmp_i1;
  long double tmp_l2;
  
  param_1 = g_dat_00397fe4 + param_1;
  if (param_1 < 0) {
    g_dat_00397fe4 = 0;
  }
  else {
    g_dat_00397fe4 = param_1;
    tmp_l2 = (long double)Cui_WideX(0x44200000);
    if (tmp_l2 < (long double)param_1) {
      tmp_l2 = (long double)Cui_WideX(0x44200000);
      g_dat_00397fe4 = (int)ROUND(tmp_l2);
    }
  }
  g_dat_00397fe8 = param_2 + g_dat_00397fe8;
  if (g_dat_00397fe8 < 0) {
    g_dat_00397fe8 = 0;
  }
  else if (0x1e0 < g_dat_00397fe8) {
    g_dat_00397fe8 = 0x1e0;
  }
  tmp_i1 = Menu_Count();
  if (0 < tmp_i1) {
    Display_MouseMove(0,g_dat_00397fe4,g_dat_00397fe8);
  }
  return;
}

void UI_LoadNonIngame(void)

{
{  char *tmp_pc1;
  
  tmp_pc1 = (char *)UI_Cvar_VariableString("ui_menuFiles");
  if (tmp_pc1 == (char *)0x0) {
    tmp_pc1 = "ui/menus.txt";
  }
  else if (*tmp_pc1 == '\0') {
    tmp_pc1 = "ui/menus.txt";
  }
  UI_LoadMenus(tmp_pc1,0);
  _DAT_003e7e24 = 0;
  return;
}

uint vmMain(uint32_t param_1,int param_2,int param_3)

{
{  uint tmp_u1;
  int tmp_i2;
  long double tmp_l3;
  
  switch(param_1) {
  case 0:
    tmp_u1 = 4;
    break;
  case 1:
    _UI_Init(param_2);
    tmp_u1 = 0;
    break;
  case 2:
    trap_LAN_SaveCachedServers();
    tmp_u1 = 0;
    break;
  case 3:
    tmp_i2 = Menu_Count();
    if (0 < tmp_i2) {
      tmp_i2 = Menu_GetFocused();
      if (tmp_i2 == 0) {
        tmp_u1 = trap_Key_GetCatcher();
        trap_Key_SetCatcher(tmp_u1 & 0xfffffffd);
        if (bypassKeyClear_10730 == 0) {
          trap_Key_ClearStates();
        }
        if ((GHIDRA_FIELD(cl_bypassMouseInput, 12, 4) != 0) && (tmp_i2 = trap_Key_GetCatcher(), tmp_i2 == 0)) {
          trap_Cvar_Set("cl_bypassMouseInput",0);
        }
        bypassKeyClear_10730 = 0;
        trap_Cvar_Set("cl_paused","0");
        return 0;
      }
      tmp_l3 = (long double)trap_Cvar_VariableValue("cl_bypassMouseInput");
      if (tmp_l3 != (long double)0) {
        bypassKeyClear_10730 = 1;
      }
      Menu_HandleKey(tmp_i2,param_2,param_3);
    }
    return 0;
  case 4:
    param_2 = param_2 + g_dat_00397fe4;
    if (param_2 < 0) {
      g_dat_00397fe4 = 0;
    }
    else {
      g_dat_00397fe4 = param_2;
      tmp_l3 = (long double)Cui_WideX(0x44200000);
      if (tmp_l3 < (long double)param_2) {
        tmp_l3 = (long double)Cui_WideX(0x44200000);
        g_dat_00397fe4 = (int)ROUND(tmp_l3);
      }
    }
    g_dat_00397fe8 = param_3 + g_dat_00397fe8;
    if (g_dat_00397fe8 < 0) {
      g_dat_00397fe8 = 0;
    }
    else if (0x1e0 < g_dat_00397fe8) {
      g_dat_00397fe8 = 0x1e0;
    }
    tmp_i2 = Menu_Count();
    if (tmp_i2 < 1) {
      return 0;
    }
    Display_MouseMove(0,g_dat_00397fe4,g_dat_00397fe8);
    tmp_u1 = 0;
    break;
  case 5:
    _UI_Refresh(param_2);
    tmp_u1 = 0;
    break;
  case 6:
    tmp_u1 = Menus_AnyFullScreenVisible();
    break;
  case 7:
    _UI_SetActiveMenu(param_2);
    tmp_u1 = 0;
    break;
  case 8:
    tmp_u1 = menutype;
    break;
  case 9:
    tmp_u1 = UI_ConsoleCommand(param_2);
    break;
  case 10:
    if (param_2 != 0) {
      return 0;
    }
    UI_DrawLoadPanel(0,0,0);
    tmp_u1 = 0;
    break;
  case 0xb:
    tmp_u1 = 1;
    break;
  case 0xc:
    tmp_i2 = Menu_GetFocused();
    tmp_u1 = 1;
    if (g_editingField == 0) {
      if (0x100 < param_2) {
        return 0;
      }
      if (tmp_i2 == 0) {
        if (GHIDRA_FIELD(cl_bypassMouseInput, 12, 4) == 0) {
          return 0;
        }
        tmp_i2 = trap_Key_GetCatcher();
        if (tmp_i2 != 0) {
          return 0;
        }
        trap_Cvar_Set("cl_bypassMouseInput","0");
        tmp_u1 = 0;
      }
      else {
        tmp_u1 = (uint)(*(int *)(tmp_i2 + 0xf4 + param_2 * 4) != 0);
      }
    }
    break;
  case 0xd:
    tmp_u1 = 0;
    if (g_waitingForKey != 0) {
      tmp_u1 = (uint)(g_bindItem != 0);
    }
    break;
  default:
    tmp_u1 = 0xffffffff;
  }
  return tmp_u1;
}

void UI_ReadableSize(char *param_1,int param_2,uint param_3)

{
{  size_t tmp_s1;
  
  if ((int)param_3 < 0x40000001) {
    if ((int)param_3 < 0x100001) {
      if ((int)param_3 < 0x401) {
        Com_sprintf(param_1,param_2,"%d bytes",param_3);
      }
      else {
        Com_sprintf(param_1,param_2,"%d KB",(int)param_3 >> 10);
      }
    }
    else {
      Com_sprintf(param_1,param_2,"%d",(int)param_3 >> 0x14);
      tmp_s1 = strlen(param_1);
      Com_sprintf(param_1 + tmp_s1,param_2 - tmp_s1,".%02d MB",(param_3 & 0xfffff) * 0x19 >> 0x12);
    }
  }
  else {
    Com_sprintf(param_1,param_2,"%d",1);
    tmp_s1 = strlen(param_1);
    Com_sprintf(param_1 + tmp_s1,param_2 - tmp_s1,".%02d GB",
                (int)(((param_3 & 0x3fffffff) + param_3 * 4) * 0x14) >> 0x1e);
  }
  return;
}

void UI_PrintTime(uint32_t param_1,uint32_t param_2,int param_3)

{
{  char *tmp_pc1;
  int tmp_i2;
  
  if (param_3 < 0xe11) {
    if (param_3 < 0x3d) {
      Com_sprintf(param_1,param_2,"%d sec",param_3);
      return;
    }
    tmp_i2 = param_3 % 0x3c;
    tmp_pc1 = "%d min %d sec";
    param_3 = param_3 / 0x3c;
  }
  else {
    tmp_i2 = (param_3 % 0xe10) / 0x3c;
    tmp_pc1 = "%d hr %d min";
    param_3 = param_3 / 0xe10;
  }
  Com_sprintf(param_1,param_2,tmp_pc1,param_3,tmp_i2);
  return;
}

void UI_RegisterCvars(void)

{
{  uint8_t **tmp_ppu1;
  int tmp_i2;
  
  if (0 < cvarTableSize) {
    tmp_ppu1 = &cvarTable;
    tmp_i2 = 0;
    do {
      trap_Cvar_Register(*tmp_ppu1,tmp_ppu1[1],tmp_ppu1[2],tmp_ppu1[3]);
      if (*tmp_ppu1 != (uint8_t *)0x0) {
        tmp_ppu1[4] = *(uint8_t **)(*tmp_ppu1 + 4);
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_ppu1 = tmp_ppu1 + 5;
    } while (tmp_i2 < cvarTableSize);
  }
  trap_Cvar_Set("ui_blackout","0");
  BG_setCrosshair(0x393490,&g_dat_003e8034,GHIDRA_FIELD(cg_crosshairAlpha, 8, 4),"cg_crosshairColor");
  BG_setCrosshair(0x396bb0,&g_dat_003e8044,GHIDRA_FIELD(cg_crosshairAlphaAlt, 8, 4),"cg_crosshairColorAlt");
  return;
}

void UI_UpdateCvars(void)

{
{  uint8_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  uint8_t **tmp_ppu4;
  
  if (0 < cvarTableSize) {
    tmp_ppu4 = &cvarTable;
    tmp_i3 = 0;
    tmp_i2 = cvarTableSize;
    do {
      if (*tmp_ppu4 != (uint8_t *)0x0) {
        trap_Cvar_Update(*tmp_ppu4);
        tmp_pu1 = *tmp_ppu4;
        tmp_i2 = cvarTableSize;
        if (tmp_ppu4[4] != *(uint8_t **)(tmp_pu1 + 4)) {
          tmp_ppu4[4] = *(uint8_t **)(tmp_pu1 + 4);
          if ((tmp_pu1 == cg_crosshairColor) || (tmp_pu1 == cg_crosshairAlpha)) {
            BG_setCrosshair(0x393490,&g_dat_003e8034,GHIDRA_FIELD(cg_crosshairAlpha, 8, 4),"cg_crosshairColor");
            tmp_pu1 = *tmp_ppu4;
          }
          if ((tmp_pu1 == cg_crosshairColorAlt) ||
             (tmp_i2 = cvarTableSize, tmp_pu1 == cg_crosshairAlphaAlt)) {
            BG_setCrosshair(0x396bb0,&g_dat_003e8044,GHIDRA_FIELD(cg_crosshairAlphaAlt, 8, 4),"cg_crosshairColorAlt"
                           );
            tmp_i2 = cvarTableSize;
          }
        }
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_ppu4 = tmp_ppu4 + 5;
    } while (tmp_i3 < tmp_i2);
  }
  return;
}

void UI_Campaign_f(void)

{
{  uint32_t *tmp_pu1;
  int tmp_i2;
  uint32_t tmp_u3;
  byte tmp_b4;
  int tmp_i5;
  uint32_t *local_420;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x38a49;
  UI_LoadArenas();
  if ((GHIDRA_FIELD(ui_netGameType, 12, 4) != 4) && (0 < g_dat_003bab6c)) {
    tmp_pu1 = (uint32_t *)&g_dat_003babcc;
    tmp_i5 = g_dat_003bab6c * 0x80;
    tmp_b4 = (byte)GHIDRA_FIELD(ui_netGameType, 12, 4);
    do {
      *tmp_pu1 = 0;
      if ((tmp_pu1[-0x14] & 1 << (tmp_b4 & 0x1f)) != 0) {
        *tmp_pu1 = 1;
      }
      tmp_pu1 = tmp_pu1 + 0x20;
    } while (tmp_pu1 != (uint32_t *)(&g_dat_003babcc + tmp_i5));
  }
  UI_LoadCampaigns();
  trap_Argv(1,local_41c,0x400);
  if (g_dat_003cab70 < 1) {
    tmp_i5 = 0;
    local_420 = (uint32_t *)0x0;
  }
  else {
    tmp_i5 = 0;
    tmp_pu1 = (uint32_t *)&g_dat_003cab74;
    do {
      local_420 = tmp_pu1;
      tmp_i2 = Q_stricmp(*local_420,local_41c);
      if (tmp_i2 == 0) break;
      tmp_i5 = tmp_i5 + 1;
      tmp_pu1 = local_420 + 0x1d;
    } while (tmp_i5 < g_dat_003cab70);
  }
  if ((tmp_i5 != g_dat_003cab70) && ((*(byte *)(local_420 + 0x1c) & 4) != 0)) {
    if (local_420[6] == 0) {
      Com_Printf("Corrupted campaign \'%s\'\n",local_41c);
      return;
    }
    trap_Cvar_Set("g_oldCampaign","");
    trap_Cvar_Set("g_currentCampaign",*local_420);
    trap_Cvar_Set("g_currentCampaignMap","0");
    tmp_u3 = va("%i",4);
    trap_Cvar_Set("g_gametype",tmp_u3);
    tmp_u3 = va("map %s\n",*(uint32_t *)(local_420[6] + 4));
    trap_Cmd_ExecuteText(2,tmp_u3);
    return;
  }
  Com_Printf("Can\'t find campaign \'%s\'\n",local_41c);
  return;
}

void UI_ListCampaigns_f(void)

{
{  uint32_t *tmp_pu1;
  byte *tmp_pb2;
  byte tmp_b3;
  int tmp_i4;
  byte *tmp_pb5;
  int tmp_i6;
  
  UI_LoadArenas();
  if ((GHIDRA_FIELD(ui_netGameType, 12, 4) != 4) && (0 < g_dat_003bab6c)) {
    tmp_pu1 = (uint32_t *)&g_dat_003babcc;
    tmp_i4 = g_dat_003bab6c * 0x80;
    tmp_b3 = (byte)GHIDRA_FIELD(ui_netGameType, 12, 4);
    do {
      *tmp_pu1 = 0;
      if ((tmp_pu1[-0x14] & 1 << (tmp_b3 & 0x1f)) != 0) {
        *tmp_pu1 = 1;
      }
      tmp_pu1 = tmp_pu1 + 0x20;
    } while (tmp_pu1 != (uint32_t *)(&g_dat_003babcc + tmp_i4));
  }
  UI_LoadCampaigns();
  if (0 < g_dat_003cab70) {
    tmp_i4 = 0;
    tmp_pb5 = &g_dat_003cabe4;
    tmp_pb2 = tmp_pb5;
    do {
      if ((*tmp_pb2 & 4) != 0) {
        tmp_i4 = tmp_i4 + 1;
      }
      tmp_pb2 = tmp_pb2 + 0x74;
    } while (tmp_pb2 != &g_dat_003cabe4 + g_dat_003cab70 * 0x74);
    if (tmp_i4 != 0) {
      Com_Printf("%i campaigns found:\n",tmp_i4);
      if (0 < g_dat_003cab70) {
        tmp_i6 = 0;
        tmp_i4 = g_dat_003cab70;
        do {
          while ((*tmp_pb5 & 4) != 0) {
            tmp_pb2 = tmp_pb5 + -0x70;
            tmp_i6 = tmp_i6 + 1;
            tmp_pb5 = tmp_pb5 + 0x74;
            Com_Printf(" %s\n",*(uint32_t *)tmp_pb2);
            tmp_i4 = g_dat_003cab70;
            if (g_dat_003cab70 <= tmp_i6) {
              return;
            }
          }
          tmp_i6 = tmp_i6 + 1;
          tmp_pb5 = tmp_pb5 + 0x74;
        } while (tmp_i6 < tmp_i4);
      }
      return;
    }
  }
  Com_Printf("No campaigns found.\n");
  return;
}

void Scroll_Slider_ThumbFunc(int param_1)

{
{  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  void *tmp_pc4;
  float tmp_f5;
  uint32_t tmp_u6;
  
  pfVar3 = *(float **)(param_1 + 0x18);
  if (pfVar3[0x3a] == 0.0) {
    tmp_f2 = *pfVar3;
  }
  else {
    tmp_f2 = pfVar3[0x2e] + pfVar3[0x30] + 8.0;
  }
  tmp_f1 = (float)*(int *)(DC + 0x124);
  tmp_f5 = tmp_f2;
  if ((tmp_f2 <= tmp_f1) && (tmp_f5 = tmp_f1, tmp_f2 + 96.0 < tmp_f1)) {
    tmp_f5 = tmp_f2 + 96.0;
  }
  tmp_pc4 = *(void **)(DC + 0x78);
  tmp_f1 = *(float *)pfVar3[0x94];
  tmp_u6 = va("%f",(double)(tmp_f1 + (((float *)pfVar3[0x94])[1] - tmp_f1) * ((tmp_f5 - tmp_f2) / 96.0)))
  ;
  (*tmp_pc4)(*(uint32_t *)(*(int *)(param_1 + 0x18) + 0x114),tmp_u6);
  return;
}

void Script_ExecWolfConfig(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  void *tmp_pc1;
  char *__nptr;
  long tmp_l2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  long tmp_l6;
  uint tmp_u7;
  uint tmp_u8;
  uint *tmp_pu9;
  uint *tmp_pu10;
  uint32_t local_448;
  uint32_t local_444;
  uint32_t local_440;
  int local_43c [8];
  char local_41c [256];
  uint8_t local_31c [256];
  uint8_t local_21c [256];
  uint local_11c [67];
  
  __nptr = (char *)COM_ParseExt(param_3,0);
  if ((__nptr != (char *)0x0) && (*__nptr != '\0')) {
    tmp_l2 = strtol(__nptr,(char **)0x0,10);
    (**(void **)(DC + 0x70))("cl_profile",local_41c,0x100);
    if ((tmp_l2 == 0) || (local_41c[0] == '\0')) {
      tmp_pc1 = *(void **)(DC + 200);
      tmp_u3 = va("exec %s\n","etconfig.cfg");
      (*tmp_pc1)(0,tmp_u3);
    }
    else {
      Com_sprintf(local_31c,0x100,"profiles/%s/%s",local_41c,"etconfig.cfg");
      Com_sprintf(local_21c,0x100,"profiles/%s/%s.bak",local_41c,"etconfig.cfg");
      tmp_i4 = trap_FS_FOpenFile(local_21c,&local_444,0);
      trap_FS_FCloseFile(local_444);
      if ((0 < tmp_i4) && (tmp_i5 = trap_FS_FOpenFile(local_31c,&local_448,1), tmp_i5 == 0)) {
        trap_FS_FOpenFile(local_21c,&local_444,0);
        tmp_i5 = 0;
        do {
          tmp_i5 = tmp_i5 + 1;
          trap_FS_Read(local_11c,1,local_444);
          trap_FS_Write(local_11c,1,local_448);
        } while (tmp_i5 != tmp_i4);
        trap_FS_FCloseFile(local_448);
        trap_FS_FCloseFile(local_444);
        tmp_u3 = trap_FS_Delete(local_21c);
        Com_Printf("Delete %s %d\n",local_21c,tmp_u3);
      }
      tmp_u3 = va("profiles/%s/profile.pid",local_41c);
      tmp_i4 = trap_FS_FOpenFile(tmp_u3,&local_440,0);
      if (-1 < tmp_i4) {
        trap_FS_Read(local_43c,0x1f,local_440);
        (**(void **)(DC + 0x70))("com_pid",local_11c,0x100);
        tmp_l2 = strtol((char *)local_11c,(char **)0x0,10);
        tmp_l6 = strtol((char *)local_43c,(char **)0x0,10);
        if (tmp_l2 != tmp_l6) {
          trap_FS_FCloseFile(local_440);
          Com_Printf("^3WARNING: profile.pid found for profile \'%s\' - not executing %s\n",
                     local_41c,"etconfig.cfg");
          return;
        }
        trap_FS_FCloseFile(local_440);
      }
      (**(void **)(DC + 200))(0,local_31c);
      tmp_u3 = va("profiles/%s/profile.pid",local_41c);
      tmp_i4 = FileExists(tmp_u3);
      if (tmp_i4 != 0) {
        trap_FS_Delete(tmp_u3);
      }
      tmp_i4 = trap_FS_FOpenFile(tmp_u3,local_43c,1);
      if ((tmp_i4 < 0) || (local_43c[0] < 0)) {
        Com_Printf("Script_WriteProfile: Can\'t write %s.\n",tmp_u3);
        Com_Printf("^3WARNING: couldn\'t write profiles/%s/profile.pid\n",local_41c);
      }
      else {
        (**(void **)(DC + 0x70))("com_pid",local_11c,0x100);
        tmp_pu10 = local_11c;
        do {
          tmp_pu9 = tmp_pu10;
          tmp_u7 = *tmp_pu9 + 0xfefefeff & ~*tmp_pu9;
          tmp_u8 = tmp_u7 & 0x80808080;
          tmp_pu10 = tmp_pu9 + 1;
        } while (tmp_u8 == 0);
        if ((tmp_u7 & 0x8080) == 0) {
          tmp_pu10 = (uint *)((int)tmp_pu9 + 6);
          tmp_u8 = tmp_u8 >> 0x10;
        }
        trap_FS_Write(local_11c,
                      (int)tmp_pu10 + ((-3 - (uint)CARRY1((byte)tmp_u8,(byte)tmp_u8)) - (int)local_11c)
                      ,local_43c[0]);
        trap_FS_FCloseFile(local_43c[0]);
      }
    }
  }
  return;
}

void Tooltip_ComputePosition(int param_1)

{
{  uint *tmp_pu1;
  int tmp_i2;
  float tmp_f3;
  int tmp_i4;
  
  tmp_i2 = *(int *)(param_1 + 0x270);
  (**(void **)(DC + 0x30))(*(uint32_t *)(tmp_i2 + 0xe0));
  *(float *)(tmp_i2 + 0x10) = *(float *)(param_1 + 0x18) / 3.0 + *(float *)(param_1 + 0x10);
  *(float *)(tmp_i2 + 0x14) = *(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x1c) + 8.0;
  tmp_i4 = (**(void **)(DC + 0x2c))
                    (*(uint32_t *)(*(int *)(param_1 + 0x270) + 0xe8),
                     *(uint32_t *)(*(int *)(param_1 + 0x270) + 0xdc),0);
  *(float *)(tmp_i2 + 0x1c) = (float)tmp_i4 + 9.0;
  tmp_i4 = (**(void **)(DC + 0x20))
                    (*(uint32_t *)(*(int *)(param_1 + 0x270) + 0xe8),
                     *(uint32_t *)(*(int *)(param_1 + 0x270) + 0xdc),0);
  *(float *)(tmp_i2 + 0x18) = (float)tmp_i4 + 6.0;
  tmp_f3 = (float)tmp_i4 + 6.0 + *(float *)(tmp_i2 + 0x10);
  if (635.0 < tmp_f3) {
    *(float *)(tmp_i2 + 0x10) = *(float *)(tmp_i2 + 0x10) - (tmp_f3 - 635.0);
  }
  *(uint32_t *)(*(int *)(param_1 + 0x270) + 0xec) = *(uint32_t *)(param_1 + 0xec);
  *(uint32_t *)(*(int *)(param_1 + 0x270) + 200) = 0;
  *(uint32_t *)(*(int *)(param_1 + 0x270) + 0x34) = 1;
  tmp_pu1 = (uint *)(*(int *)(param_1 + 0x270) + 0x48);
  *tmp_pu1 = *tmp_pu1 | 4;
  return;
}

uint8_t * UI_Alloc(int param_1)

{
{  int tmp_i1;
  
  tmp_i1 = allocPoint;
  if (allocPoint + param_1 < 0x200001) {
    allocPoint = (param_1 + 0xfU & 0xfffffff0) + allocPoint;
    return memoryPool + tmp_i1;
  }
  outOfMemory = 1;
  if (*(void **)(DC + 0xd0) != (void *)0x0) {
    (**(void **)(DC + 0xd0))("UI_Alloc: Failure. Out of memory!\n");
    return (uint8_t *)0x0;
  }
  return (uint8_t *)0x0;
}

void Script_SetAsset(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    String_Alloc();
    return;
  }
  return;
}

void Script_ClearCvar(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    (**(void **)(DC + 0x78))(tmp_u2,"");
  }
  return;
}

void Script_SetPlayerModel(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    (**(void **)(DC + 0x78))("team_model",tmp_u2);
  }
  return;
}

void Script_SetPlayerHead(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    (**(void **)(DC + 0x78))("team_headmodel",tmp_u2);
  }
  return;
}

void Script_SetBackground(int param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_u2 = (*(void *)*DC)(tmp_u2);
    *(uint32_t *)(param_1 + 0xb4) = tmp_u2;
  }
  return;
}

void Script_Exec(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  void *tmp_pc1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_pc1 = *(void **)(DC + 200);
    tmp_u3 = va("%s ; ",tmp_u3);
    (*tmp_pc1)(2,tmp_u3);
  }
  return;
}

void Script_ExecNOW(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  void *tmp_pc1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_pc1 = *(void **)(DC + 200);
    tmp_u3 = va("%s ; ",tmp_u3);
    (*tmp_pc1)(0,tmp_u3);
  }
  return;
}

void Script_Play(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  void *tmp_pc1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_pc1 = *(void **)(DC + 0x88);
    tmp_u3 = (**(void **)(DC + 0xdc))(tmp_u3,0);
    (*tmp_pc1)(tmp_u3,6);
  }
  return;
}

void Script_playLooped(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    (**(void **)(DC + 0xe4))();
    (**(void **)(DC + 0xe0))(tmp_u2,tmp_u2,0);
  }
  return;
}

void Script_SetCvar(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_pc1 = (char *)COM_ParseExt(param_3,0);
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_u3 = String_Alloc(tmp_pc1);
      (**(void **)(DC + 0x78))(tmp_u2,tmp_u3);
      return;
    }
  }
  return;
}

void Script_CopyCvar(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint8_t local_11c [268];
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_pc1 = (char *)COM_ParseExt(param_3,0);
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_u3 = String_Alloc(tmp_pc1);
      (**(void **)(DC + 0x70))(tmp_u2,local_11c,0x100);
      (**(void **)(DC + 0x78))(tmp_u3,local_11c);
    }
  }
  return;
}

void Script_ToggleCvarBit(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  void *tmp_pc1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  uint tmp_u4;
  uint tmp_u5;
  uint32_t tmp_u6;
  char local_11c [268];
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_pc2 = (char *)COM_ParseExt(param_3,0);
    if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
      tmp_pc2 = (char *)String_Alloc(tmp_pc2);
      (**(void **)(DC + 0x70))(tmp_u3,local_11c,0x100);
      tmp_u4 = strtol(local_11c,(char **)0x0,10);
      tmp_u5 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_pc1 = *(void **)(DC + 0x78);
      tmp_u6 = va("%i",tmp_u4 ^ tmp_u5);
      (*tmp_pc1)(tmp_u3,tmp_u6);
    }
  }
  return;
}

void Script_CloseAll(void)

{
{  int tmp_i1;
  uint tmp_u2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  
  if (0 < menuCount) {
    tmp_pu3 = &Menus;
    tmp_i4 = 0;
    tmp_i1 = menuCount;
    do {
      tmp_u2 = tmp_pu3[0x12];
      if ((tmp_u2 & 4) != 0) {
        Menu_RunCloseScript_part_10();
        tmp_u2 = tmp_pu3[0x12];
        tmp_i1 = menuCount;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu3[0x12] = tmp_u2 & 0xfffffff8;
      tmp_pu3 = tmp_pu3 + 0x346;
    } while (tmp_i4 < tmp_i1);
  }
  return;
}

void Fade(uint *param_1,float *param_2,float param_3,int *param_4,int param_5,int param_6,
         float param_7)

{
{  float tmp_f1;
  
  if ((*param_1 & 0x60) != 0) {
    if (*param_4 < *(int *)(DC + 0x11c)) {
      *param_4 = *(int *)(DC + 0x11c) + param_5;
      if ((*param_1 & 0x20) == 0) {
        if (param_7 + *param_2 < param_3) {
          *param_2 = param_7 + *param_2;
          return;
        }
        *param_2 = param_3;
        if (param_6 != 0) {
          *param_1 = *param_1 & 0xffffffbf;
          return;
        }
      }
      else {
        tmp_f1 = *param_2;
        *param_2 = tmp_f1 - param_7;
        if ((tmp_f1 - param_7 <= 0.0) && (param_6 != 0)) {
          *param_1 = *param_1 & 0xffffffdb;
        }
      }
    }
  }
  return;
}

void Window_Paint(float *param_1,float param_2,float param_3,float param_4)

{
{  float tmp_f1;
  int tmp_i2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float *pfVar8;
  float local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_10 = 0x3e058;
  tmp_f7 = *param_1;
  tmp_f4 = param_1[1];
  tmp_f5 = param_1[2];
  tmp_f6 = param_1[3];
  if (debugMode != 0) {
    local_10 = 0x3f800000;
    local_14 = 0x3f800000;
    local_18 = 0x3f800000;
    local_1c = 1.0;
    (**(void **)(DC + 0x40))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,0x3f800000,&local_1c);
  }
  tmp_i2 = DC;
  tmp_f3 = param_1[0xd];
  if (tmp_f3 == 0.0) {
    if (param_1[0xe] == 0.0) {
      return;
    }
LAB_0003e090:
    tmp_f1 = param_1[0x11];
    tmp_f7 = tmp_f7 + tmp_f1;
    tmp_f4 = tmp_f4 + tmp_f1;
    tmp_f5 = tmp_f5 - (tmp_f1 + tmp_f1);
    tmp_f6 = tmp_f6 - (tmp_f1 + tmp_f1);
    if (tmp_f3 == 1.4013e-45) goto LAB_0003e124;
LAB_0003e0a6:
    if (tmp_f3 != 2.8026e-45) {
      if (tmp_f3 != 4.2039e-45) {
        if (tmp_f3 == 5.60519e-45) {
          if (*(void **)(DC + 0x6c) != (void *)0x0) {
            (**(void **)(DC + 0x6c))(&local_1c);
            (**(void **)(DC + 0x3c))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,&local_1c);
          }
        }
        else if (tmp_f3 == 7.00649e-45) {
          tmp_f3 = param_1[0xc];
          if (tmp_f3 == -NAN) {
            tmp_f3 = (float)(**(void **)(DC + 0xe8))(param_1[0xb],tmp_f7,tmp_f4,tmp_f5,tmp_f6);
            if (tmp_f3 == -NAN) {
              param_1[0xc] = -NAN;
              goto LAB_0003e0d2;
            }
            param_1[0xc] = tmp_f3;
          }
          if (-1 < (int)tmp_f3) {
            (**(void **)(DC + 0xf4))(tmp_f3);
            (**(void **)(DC + 0xf0))(param_1[0xc],tmp_f7,tmp_f4,tmp_f5,tmp_f6);
          }
        }
        goto LAB_0003e0d2;
      }
      if ((*(byte *)((int)param_1 + 0x49) & 2) != 0) {
        (**(void **)(DC + 4))(param_1 + 0x1d);
      }
      tmp_f3 = param_1[0x2d];
      goto LAB_0003e204;
    }
    (**(void **)(DC + 4))(param_1 + 0x21);
    (**(void **)(DC + 8))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,*(uint32_t *)(DC + 0x1e2d8));
    (**(void **)(DC + 4))(0);
  }
  else {
    if (param_1[0xe] != 0.0) goto LAB_0003e090;
    if (tmp_f3 != 1.4013e-45) goto LAB_0003e0a6;
LAB_0003e124:
    if (param_1[0x2d] != 0.0) {
      tmp_f3 = param_1[0x12];
      if ((((uint)tmp_f3 & 0x60) != 0) && ((int)param_1[0x1c] < *(int *)(DC + 0x11c))) {
        param_1[0x1c] = (float)(*(int *)(DC + 0x11c) + (int)ROUND(param_4));
        if (((uint)tmp_f3 & 0x20) == 0) {
          if (param_2 + param_1[0x24] < param_3) {
            param_1[0x24] = param_2 + param_1[0x24];
          }
          else {
            param_1[0x12] = (float)((uint)tmp_f3 & 0xffffffbf);
            param_1[0x24] = param_3;
          }
        }
        else {
          tmp_f1 = param_1[0x24];
          param_1[0x24] = tmp_f1 - param_2;
          if (tmp_f1 - param_2 <= 0.0) {
            param_1[0x12] = (float)((uint)tmp_f3 & 0xffffffdb);
          }
        }
      }
      (**(void **)(tmp_i2 + 4))(param_1 + 0x21);
      tmp_f3 = param_1[0x2d];
LAB_0003e204:
      (**(void **)(DC + 8))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,tmp_f3);
      (**(void **)(DC + 4))(0);
      tmp_f7 = param_1[0xe];
      goto joined_r0x0003e226;
    }
    (**(void **)(DC + 0x3c))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,param_1 + 0x21);
  }
LAB_0003e0d2:
  tmp_f7 = param_1[0xe];
joined_r0x0003e226:
  if (tmp_f7 != 1.4013e-45) {
    if (tmp_f7 == 2.8026e-45) {
      (**(void **)(DC + 4))(param_1 + 0x25);
      (**(void **)(DC + 0x48))(*param_1,param_1[1],param_1[2],param_1[3],param_1[0x11]);
      (**(void **)(DC + 4))(0);
    }
    else if (tmp_f7 == 4.2039e-45) {
      (**(void **)(DC + 4))(param_1 + 0x25);
      (**(void **)(DC + 0x44))(*param_1,param_1[1],param_1[2],param_1[3],param_1[0x11]);
      (**(void **)(DC + 4))(0);
    }
    else if (tmp_f7 == 5.60519e-45) {
      tmp_f7 = *param_1;
      tmp_f4 = param_1[1];
      tmp_f5 = param_1[2];
      tmp_f6 = param_1[0x11];
      (**(void **)(DC + 4))(param_1 + 0x25);
      (**(void **)(DC + 8))(tmp_f7,tmp_f4,tmp_f5,tmp_f6,*(uint32_t *)(DC + 0x1e2d8));
      (**(void **)(DC + 4))(0);
      tmp_f4 = param_1[1];
      tmp_f3 = param_1[3];
      (**(void **)(DC + 4))(param_1 + 0x25);
      (**(void **)(DC + 8))(tmp_f7,(tmp_f4 + tmp_f3) - 1.0,tmp_f5,tmp_f6,*(uint32_t *)(DC + 0x1e2d8));
      (**(void **)(DC + 4))(0);
    }
    return;
  }
  if (param_1[0xd] == 5.60519e-45) {
    if (local_1c <= 0.0) {
      local_14 = 0x3f800000;
      local_1c = 0.5;
    }
    else {
      local_1c = 1.0;
      local_14 = 0x3f000000;
    }
    local_18 = 0x3f000000;
    pfVar8 = &local_1c;
    tmp_f7 = param_1[0x11];
    local_10 = 0x3f800000;
  }
  else {
    pfVar8 = param_1 + 0x25;
    tmp_f7 = param_1[0x11];
  }
  (**(void **)(DC + 0x40))(*param_1,param_1[1],param_1[2],param_1[3],tmp_f7,pfVar8);
  return;
}

void Script_SetFocus(int param_1,uint32_t param_2,uint32_t param_3)

{
{  int tmp_i1;
  char *tmp_pc2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_i3 = String_Alloc(tmp_pc2);
    tmp_i1 = *(int *)(param_1 + 0xec);
    if ((tmp_i3 != 0) && ((tmp_i1 != 0 && (0 < *(int *)(tmp_i1 + 0xc0))))) {
      tmp_i5 = 0;
      do {
        tmp_i4 = Q_stricmp(tmp_i3,*(uint32_t *)(*(int *)(tmp_i1 + 0x514 + tmp_i5 * 4) + 0x20));
        if (tmp_i4 == 0) {
          tmp_i1 = *(int *)(tmp_i1 + 0x514 + tmp_i5 * 4);
          if (tmp_i1 == 0) {
            return;
          }
          if ((*(byte *)(tmp_i1 + 0x48) & 0x12) != 0) {
            return;
          }
          Menu_ClearFocus(*(uint32_t *)(param_1 + 0xec));
          *(uint *)(tmp_i1 + 0x48) = *(uint *)(tmp_i1 + 0x48) | 2;
          if (*(int *)(tmp_i1 + 0x10c) != 0) {
            Item_RunScript_constprop_37();
          }
          if (*(int *)(DC + 0x1e320) == 0) {
            return;
          }
          (**(void **)(DC + 0x88))(*(int *)(DC + 0x1e320),6);
          return;
        }
        tmp_i5 = tmp_i5 + 1;
      } while (tmp_i5 < *(int *)(tmp_i1 + 0xc0));
    }
  }
  return;
}

void Script_SetEditFocus(int param_1,uint32_t param_2,uint32_t param_3)

{
{  int tmp_i1;
  char *tmp_pc2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_i3 = String_Alloc(tmp_pc2);
    tmp_i1 = *(int *)(param_1 + 0xec);
    if ((tmp_i3 != 0) && ((tmp_i1 != 0 && (0 < *(int *)(tmp_i1 + 0xc0))))) {
      tmp_i5 = 0;
      do {
        tmp_i4 = Q_stricmp(tmp_i3,*(uint32_t *)(*(int *)(tmp_i1 + 0x514 + tmp_i5 * 4) + 0x20));
        if (tmp_i4 == 0) {
          tmp_i1 = *(int *)(tmp_i1 + 0x514 + tmp_i5 * 4);
          if (tmp_i1 == 0) {
            return;
          }
          if ((*(int *)(tmp_i1 + 200) != 9) && (*(int *)(tmp_i1 + 200) != 4)) {
            return;
          }
          tmp_i3 = *(int *)(tmp_i1 + 0x250);
          Menu_ClearFocus(*(uint32_t *)(param_1 + 0xec));
          *(uint *)(tmp_i1 + 0x48) = *(uint *)(tmp_i1 + 0x48) | 2;
          if (*(int *)(tmp_i1 + 0x10c) != 0) {
            Item_RunScript_constprop_37();
          }
          if (*(int *)(DC + 0x1e320) != 0) {
            (**(void **)(DC + 0x88))(*(int *)(DC + 0x1e320),6);
          }
          if (tmp_i3 != 0) {
            *(uint32_t *)(tmp_i3 + 0x18) = 0;
          }
          *(uint32_t *)(tmp_i1 + 0x24c) = 0;
          g_editItem = tmp_i1;
          g_editingField = 1;
          return;
        }
        tmp_i5 = tmp_i5 + 1;
      } while (tmp_i5 < *(int *)(tmp_i1 + 0xc0));
    }
  }
  return;
}

void Script_FadeIn(int param_1,uint32_t param_2,uint32_t param_3)

{
{  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_u1 = *(uint32_t *)(param_1 + 0xec);
    tmp_i4 = Menu_ItemsMatchingGroup(tmp_u1,tmp_u3);
    if (0 < tmp_i4) {
      tmp_i6 = 0;
      do {
        tmp_i5 = Menu_GetMatchingItemByNumber(tmp_u1,tmp_i6,tmp_u3);
        if (tmp_i5 != 0) {
          *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) & 0xffffffdf | 0x44;
        }
        tmp_i6 = tmp_i6 + 1;
      } while (tmp_i6 != tmp_i4);
      return;
    }
  }
  return;
}

void Script_FadeOut(int param_1,uint32_t param_2,uint32_t param_3)

{
{  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_u1 = *(uint32_t *)(param_1 + 0xec);
    tmp_i4 = Menu_ItemsMatchingGroup(tmp_u1,tmp_u3);
    if (0 < tmp_i4) {
      tmp_i6 = 0;
      do {
        tmp_i5 = Menu_GetMatchingItemByNumber(tmp_u1,tmp_i6,tmp_u3);
        if (tmp_i5 != 0) {
          *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) & 0xffffffbf | 0x24;
        }
        tmp_i6 = tmp_i6 + 1;
      } while (tmp_i6 != tmp_i4);
      return;
    }
  }
  return;
}

void Script_Show(int param_1,uint32_t param_2,uint32_t param_3)

{
{  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_u1 = *(uint32_t *)(param_1 + 0xec);
    tmp_i4 = Menu_ItemsMatchingGroup(tmp_u1,tmp_u3);
    if (0 < tmp_i4) {
      tmp_i6 = 0;
      do {
        tmp_i5 = Menu_GetMatchingItemByNumber(tmp_u1,tmp_i6,tmp_u3);
        if (tmp_i5 != 0) {
          *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) | 4;
        }
        tmp_i6 = tmp_i6 + 1;
      } while (tmp_i6 != tmp_i4);
    }
  }
  return;
}

void Script_Hide(int param_1,uint32_t param_2,uint32_t param_3)

{
{  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  int tmp_i7;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_u1 = *(uint32_t *)(param_1 + 0xec);
    tmp_i4 = Menu_ItemsMatchingGroup(tmp_u1,tmp_u3);
    if (0 < tmp_i4) {
      tmp_i7 = 0;
      do {
        tmp_i5 = Menu_GetMatchingItemByNumber(tmp_u1,tmp_i7,tmp_u3);
        if (tmp_i5 != 0) {
          tmp_u6 = *(uint *)(tmp_i5 + 0x48);
          if ((tmp_u6 & 1) != 0) {
            if ((tmp_u6 & 0x80) != 0) {
              Item_RunScript_constprop_37();
              *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) & 0xffffff7f;
            }
            Item_RunScript_constprop_37();
            tmp_u6 = *(uint *)(tmp_i5 + 0x48) & 0xffffe7fe;
          }
          *(uint *)(tmp_i5 + 0x48) = tmp_u6 & 0xfffffffb;
          if (-1 < *(int *)(tmp_i5 + 0x30)) {
            (**(void **)(DC + 0xec))(*(int *)(tmp_i5 + 0x30));
            *(uint32_t *)(tmp_i5 + 0x30) = 0xffffffff;
          }
        }
        tmp_i7 = tmp_i7 + 1;
      } while (tmp_i7 != tmp_i4);
    }
  }
  return;
}

void Script_ConditionalHideShow(int param_1,uint32_t param_2,uint32_t param_3)

{
{  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  long double tmp_l7;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
    tmp_u3 = String_Alloc(tmp_pc2);
    tmp_l7 = (long double)(**(void **)(DC + 0x74))(*(uint32_t *)(param_1 + 0x114));
    if (tmp_l7 == (long double)0) {
      Menu_ShowItemByName();
      return;
    }
    tmp_u1 = *(uint32_t *)(param_1 + 0xec);
    tmp_i4 = Menu_ItemsMatchingGroup(tmp_u1,tmp_u3);
    if (0 < tmp_i4) {
      tmp_i6 = 0;
      do {
        tmp_i5 = Menu_GetMatchingItemByNumber(tmp_u1,tmp_i6,tmp_u3);
        if (tmp_i5 != 0) {
          *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) | 4;
        }
        tmp_i6 = tmp_i6 + 1;
      } while (tmp_i6 != tmp_i4);
    }
  }
  return;
}

void Script_Transition(int param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  long tmp_l4;
  double tmp_d5;
  double tmp_d6;
  double tmp_d7;
  uint32_t local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_pc1 = (char *)COM_ParseExt(param_3,0);
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_d5 = strtod(tmp_pc1,(char **)0x0);
      tmp_pc1 = (char *)COM_ParseExt(param_3,0);
      if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
        tmp_d6 = strtod(tmp_pc1,(char **)0x0);
        tmp_i3 = Float_Parse(param_3,&local_34);
        if (tmp_i3 != 0) {
          tmp_pc1 = (char *)COM_ParseExt(param_3,0);
          if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
            tmp_d7 = strtod(tmp_pc1,(char **)0x0);
            local_30 = (float)tmp_d7;
            tmp_i3 = Rect_Parse(param_3,&local_2c);
            if (tmp_i3 != 0) {
              tmp_pc1 = (char *)COM_ParseExt(param_3,0);
              if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
                tmp_l4 = strtol(tmp_pc1,(char **)0x0,10);
                tmp_pc1 = (char *)COM_ParseExt(param_3,0);
                if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
                  tmp_d7 = strtod(tmp_pc1,(char **)0x0);
                  Menu_TransitionItemByName
                            (*(uint32_t *)(param_1 + 0xec),tmp_u2,(float)tmp_d5,(float)tmp_d6,
                             local_34,local_30,local_2c,local_28,local_24,local_20,tmp_l4,
                             (float)tmp_d7);
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}

        if (pfVar3 != (float *)0x0) {
{          tmp_f1 = *pfVar3;
          tmp_f2 = pfVar3[1];
          pfVar3 = (float *)pfVar9[0x9c];
          *pfVar9 = tmp_f1 + param_3;
          pfVar9[1] = tmp_f2 + param_4;
          pfVar9[2] = pfVar9[6];
          pfVar9[3] = pfVar9[7];
          if (pfVar3 != (float *)0x0) {
            pfVar4 = (float *)pfVar3[0x9c];
            *pfVar3 = pfVar3[4] + tmp_f1;
            pfVar3[1] = pfVar3[5] + tmp_f2;
            pfVar3[2] = pfVar3[6];
            pfVar3[3] = pfVar3[7];
            if (pfVar4 != (float *)0x0) {
              pfVar5 = (float *)pfVar4[0x9c];
              *pfVar4 = pfVar4[4] + tmp_f1;
              pfVar4[1] = pfVar4[5] + tmp_f2;
              pfVar4[2] = pfVar4[6];
              pfVar4[3] = pfVar4[7];
              if (pfVar5 != (float *)0x0) {
                pfVar6 = (float *)pfVar5[0x9c];
                *pfVar5 = pfVar5[4] + tmp_f1;
                pfVar5[1] = pfVar5[5] + tmp_f2;
                pfVar5[2] = pfVar5[6];
                pfVar5[3] = pfVar5[7];
                if (pfVar6 != (float *)0x0) {
                  *pfVar6 = pfVar6[4] + tmp_f1;
                  pfVar6[1] = pfVar6[5] + tmp_f2;
                  pfVar6[2] = pfVar6[6];
                  pfVar6[3] = pfVar6[7];
                  if (pfVar6[0x9c] != 0.0) {
                    Item_SetScreenCoords(pfVar6[0x9c],tmp_f1,tmp_f2);
                    pfVar7 = (float *)pfVar6[0x9c];
                    tmp_f1 = (pfVar7[2] + *pfVar7) - 635.0;
                    if (0.0 < tmp_f1) {
                      pfVar7[4] = pfVar7[4] - tmp_f1;
                      *(float *)pfVar6[0x9c] = *(float *)pfVar6[0x9c] - tmp_f1;
                    }
                  }
                  pfVar6[0x30] = 0.0;
                  pfVar6[0x31] = 0.0;
                  pfVar6 = (float *)pfVar5[0x9c];
                  tmp_f1 = (*pfVar6 + pfVar6[2]) - 635.0;
                  if (0.0 < tmp_f1) {
                    pfVar6[4] = pfVar6[4] - tmp_f1;
                    *(float *)pfVar5[0x9c] = *(float *)pfVar5[0x9c] - tmp_f1;
                  }
                }
                pfVar5[0x30] = 0.0;
                pfVar5[0x31] = 0.0;
                pfVar5 = (float *)pfVar4[0x9c];
                tmp_f1 = (*pfVar5 + pfVar5[2]) - 635.0;
                if (0.0 < tmp_f1) {
                  pfVar5[4] = pfVar5[4] - tmp_f1;
                  *(float *)pfVar4[0x9c] = *(float *)pfVar4[0x9c] - tmp_f1;
                }
              }
              pfVar4[0x30] = 0.0;
              pfVar4[0x31] = 0.0;
              pfVar4 = (float *)pfVar3[0x9c];
              tmp_f1 = (*pfVar4 + pfVar4[2]) - 635.0;
              if (0.0 < tmp_f1) {
                pfVar4[4] = pfVar4[4] - tmp_f1;
                *(float *)pfVar3[0x9c] = *(float *)pfVar3[0x9c] - tmp_f1;
              }
            }
            pfVar3[0x30] = 0.0;
            pfVar3[0x31] = 0.0;
            pfVar3 = (float *)pfVar9[0x9c];
            tmp_f1 = (*pfVar3 + pfVar3[2]) - 635.0;
            if (0.0 < tmp_f1) {
              pfVar3[4] = pfVar3[4] - tmp_f1;
              *(float *)pfVar9[0x9c] = *(float *)pfVar9[0x9c] - tmp_f1;
            }
          }
          pfVar9[0x30] = 0.0;
          pfVar9[0x31] = 0.0;
        }

void Script_Orbit(int param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  double tmp_d4;
  double tmp_d5;
  double tmp_d6;
  uint32_t local_14;
  uint32_t local_10;
  
  local_10 = 0;
  local_14 = 0;
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_pc1 = (char *)COM_ParseExt(param_3,0);
    if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
      tmp_d4 = strtod(tmp_pc1,(char **)0x0);
      tmp_pc1 = (char *)COM_ParseExt(param_3,0);
      if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
        tmp_d5 = strtod(tmp_pc1,(char **)0x0);
        tmp_i3 = Float_Parse(param_3,&local_14);
        if ((tmp_i3 != 0) &&
           ((tmp_pc1 = (char *)COM_ParseExt(param_3,0), tmp_pc1 != (char *)0x0 && (*tmp_pc1 != '\0'))))
        {
          tmp_d6 = strtod(tmp_pc1,(char **)0x0);
          tmp_i3 = Int_Parse(param_3,&local_10);
          if (tmp_i3 != 0) {
            Menu_OrbitItemByName
                      (*(uint32_t *)(param_1 + 0xec),tmp_u2,(float)tmp_d4,(float)tmp_d5,local_14,
                       (float)tmp_d6,local_10);
          }
        }
      }
    }
  }
  return;
}

uint32_t Script_CheckProfile(uint32_t param_1)

{
{  int tmp_i1;
  long tmp_l2;
  long tmp_l3;
  uint32_t tmp_u4;
  uint32_t local_130;
  char local_12c [32];
  char local_10c [256];
  
  tmp_i1 = trap_FS_FOpenFile(param_1,&local_130,0);
  if (tmp_i1 < 0) {
    tmp_u4 = 1;
  }
  else {
    trap_FS_Read(local_12c,0x1f,local_130);
    (**(void **)(DC + 0x70))("com_pid",local_10c,0x100);
    tmp_l2 = strtol(local_10c,(char **)0x0,10);
    tmp_l3 = strtol(local_12c,(char **)0x0,10);
    if (tmp_l2 == tmp_l3) {
      trap_FS_FCloseFile(local_130);
      tmp_u4 = 1;
    }
    else {
      trap_FS_FCloseFile(local_130);
      tmp_u4 = 0;
    }
  }
  return tmp_u4;
}

uint32_t Script_WriteProfile(uint32_t param_1)

{
{  int tmp_i1;
  uint tmp_u2;
  uint tmp_u3;
  uint *tmp_pu4;
  uint *tmp_pu5;
  int local_110;
  uint local_10c [65];
  
  tmp_i1 = FileExists(param_1);
  if (tmp_i1 != 0) {
    trap_FS_Delete(param_1);
  }
  tmp_i1 = trap_FS_FOpenFile(param_1,&local_110,1);
  if ((-1 < tmp_i1) && (-1 < local_110)) {
    (**(void **)(DC + 0x70))("com_pid",local_10c,0x100);
    tmp_pu5 = local_10c;
    do {
      tmp_pu4 = tmp_pu5;
      tmp_u2 = *tmp_pu4 + 0xfefefeff & ~*tmp_pu4;
      tmp_u3 = tmp_u2 & 0x80808080;
      tmp_pu5 = tmp_pu4 + 1;
    } while (tmp_u3 == 0);
    if ((tmp_u2 & 0x8080) == 0) {
      tmp_pu5 = (uint *)((int)tmp_pu4 + 6);
      tmp_u3 = tmp_u3 >> 0x10;
    }
    trap_FS_Write(local_10c,
                  (int)tmp_pu5 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_10c),
                  local_110);
    trap_FS_FCloseFile(local_110);
    return 1;
  }
  Com_Printf("Script_WriteProfile: Can\'t write %s.\n",param_1);
  return 0;
}

void Script_ConditionalScript(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  int tmp_i2;
  long tmp_l3;
  int tmp_i4;
  uint32_t tmp_u5;
  long double tmp_l6;
  long double tmp_l7;
  long double tmp_l8;
  long double tmp_l9;
  long double tmp_l10;
  long double tmp_l11;
  long double tmp_l12;
  long double tmp_l13;
  long double tmp_l14;
  long double tmp_l15;
  long double tmp_l16;
  long double tmp_l17;
  long double tmp_l18;
  long double tmp_l19;
  long double tmp_l20;
  long double tmp_l21;
  long double tmp_l22;
  long double tmp_l23;
  long double tmp_l24;
  long double tmp_l25;
  uint32_t local_52c;
  uint32_t local_528;
  char *local_524;
  uint32_t local_520;
  uint32_t local_51c [64];
  int local_41c [259];
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_i2 = String_Alloc(tmp_pc1);
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  local_524 = (char *)String_Alloc(tmp_pc1);
  if (local_524 == (char *)0x0) {
    return;
  }
  if (*local_524 != '(') {
    return;
  }
  tmp_i4 = String_Parse(param_3,&local_52c);
  if (tmp_i4 == 0) {
    return;
  }
  tmp_i4 = String_Parse(param_3,&local_524);
  if (tmp_i4 == 0) {
    return;
  }
  if (local_524 == (char *)0x0) {
    return;
  }
  if (*local_524 != ')') {
    return;
  }
  tmp_i4 = String_Parse(param_3,&local_524);
  if (tmp_i4 == 0) {
    return;
  }
  if (local_524 == (char *)0x0) {
    return;
  }
  if (*local_524 != '(') {
    return;
  }
  tmp_i4 = String_Parse(param_3,&local_528);
  if (tmp_i4 == 0) {
    return;
  }
  tmp_i4 = String_Parse(param_3,&local_524);
  if (tmp_i4 == 0) {
    return;
  }
  if (local_524 == (char *)0x0) {
    return;
  }
  if (*local_524 != ')') {
    return;
  }
  if (tmp_l3 == 2) {
    tmp_i4 = Q_stricmp(tmp_i2,"UIProfileIsActiveProfile");
    if (tmp_i4 == 0) {
      (**(void **)(DC + 0x70))("ui_profile",local_51c,0x100);
      Q_CleanStr(local_51c);
      Q_CleanDirName(local_51c);
      (**(void **)(DC + 0x70))("cl_profile",local_41c,0x100);
      tmp_i2 = Q_stricmp(local_51c,local_41c);
      if (tmp_i2 != 0) goto LAB_000415d2;
    }
    else {
      tmp_i4 = Q_stricmp(tmp_i2,"UIProfileValidName");
      if (tmp_i4 != 0) {
        tmp_i4 = Q_stricmp(tmp_i2,"UIProfileAlreadyExists");
        if (tmp_i4 == 0) {
          tmp_pc1 = "ui_profile";
        }
        else {
          tmp_i4 = Q_stricmp(tmp_i2,"UIProfileAlreadyExists_Rename");
          if (tmp_i4 != 0) {
            tmp_i4 = Q_stricmp(tmp_i2,"ReadyToCreateProfile");
            if (tmp_i4 == 0) {
              (**(void **)(DC + 0x70))("ui_profile",local_51c,0x100);
              Q_strncpyz(local_41c,local_51c,0x100);
              Q_CleanStr(local_41c);
              Q_CleanDirName(local_41c);
              tmp_u5 = va("profiles/%s/profile.dat",local_41c);
              tmp_i2 = trap_FS_FOpenFile(tmp_u5,&local_520,0);
              if (-1 < tmp_i2) {
                trap_FS_FCloseFile(local_520);
                (**(void **)(DC + 0x74))("ui_rate");
                goto LAB_000415d2;
              }
              tmp_l6 = (long double)(**(void **)(DC + 0x74))("ui_rate");
              local_41c[0]._0_1_ = (char)local_51c[0];
              if ((int)ROUND(tmp_l6) < 1) goto LAB_000415d2;
              goto joined_r0x00041e06;
            }
            tmp_i4 = Q_stricmp(tmp_i2,"vidrestartIsRequired");
            if (tmp_i4 == 0) {
              tmp_l6 = (long double)(**(void **)(DC + 0x74))("ui_r_mode");
              tmp_l7 = (long double)(**(void **)(DC + 0x74))("ui_r_colorbits");
              tmp_l8 = (long double)(**(void **)(DC + 0x74))("ui_r_fullscreen");
              tmp_l9 = (long double)(**(void **)(DC + 0x74))("ui_r_texturebits");
              tmp_l10 = (long double)(**(void **)(DC + 0x74))("ui_r_depthbits");
              tmp_l11 = (long double)(**(void **)(DC + 0x74))("ui_r_ext_compressed_textures");
              tmp_l12 = (long double)(**(void **)(DC + 0x74))("ui_r_allowextensions");
              tmp_l13 = (long double)(**(void **)(DC + 0x74))(&g_dat_00056fed);
              tmp_l14 = (long double)(**(void **)(DC + 0x74))("ui_r_detailtextures");
              tmp_l15 = (long double)(**(void **)(DC + 0x74))("ui_r_subdivisions");
              tmp_l16 = (long double)(**(void **)(DC + 0x74))("r_mode");
              tmp_l17 = (long double)(**(void **)(DC + 0x74))("r_colorbits");
              tmp_l18 = (long double)(**(void **)(DC + 0x74))("r_fullscreen");
              tmp_l19 = (long double)(**(void **)(DC + 0x74))("r_texturebits");
              tmp_l20 = (long double)(**(void **)(DC + 0x74))("r_depthbits");
              tmp_l21 = (long double)(**(void **)(DC + 0x74))("r_ext_compressed_textures");
              tmp_l22 = (long double)(**(void **)(DC + 0x74))("r_allowextensions");
              tmp_l23 = (long double)(**(void **)(DC + 0x74))("s_khz");
              tmp_l24 = (long double)(**(void **)(DC + 0x74))("r_detailtextures");
              tmp_l25 = (long double)(**(void **)(DC + 0x74))("r_subdivisions");
              trap_Cvar_VariableStringBuffer("ui_r_texturemode",local_51c,0x100);
              trap_Cvar_VariableStringBuffer("r_texturemode",local_41c,0x100);
              if (((((((int)ROUND((float)tmp_l15) == (int)ROUND((float)tmp_l25)) &&
                     ((int)ROUND((float)tmp_l6) == (int)ROUND((float)tmp_l16))) &&
                    ((int)ROUND(tmp_l7) == (int)ROUND(tmp_l17))) &&
                   (((int)ROUND(tmp_l8) == (int)ROUND(tmp_l18) &&
                    ((int)ROUND(tmp_l9) == (int)ROUND(tmp_l19))))) &&
                  (((int)ROUND(tmp_l10) == (int)ROUND(tmp_l20) &&
                   (((int)ROUND(tmp_l11) == (int)ROUND(tmp_l21) &&
                    ((int)ROUND(tmp_l12) == (int)ROUND(tmp_l22))))))) &&
                 (((int)ROUND(tmp_l13) == (int)ROUND(tmp_l23) &&
                  (((int)ROUND(tmp_l14) == (int)ROUND(tmp_l24) &&
                   (tmp_i2 = Q_stricmp(local_41c,local_51c), tmp_i2 == 0)))))) goto LAB_000415d2;
            }
            else {
              tmp_i4 = Q_stricmpn(tmp_i2,"serversort_",0xb);
              if (tmp_i4 == 0) {
                tmp_l3 = strtol((char *)(tmp_i2 + 0xb),(char **)0x0,10);
                if (_DAT_003e13b0 != tmp_l3) goto LAB_000415d2;
              }
              else {
                tmp_i4 = Q_stricmp(tmp_i2,"ValidReplaySelected");
                if (tmp_i4 != 0) {
                  tmp_i2 = Q_stricmp(tmp_i2,"ROldModeCheck");
                  if (tmp_i2 != 0) {
                    return;
                  }
                  tmp_l6 = (long double)(**(void **)(DC + 0x74))("r_mode");
                  (**(void **)(DC + 0x70))("r_oldMode",local_41c,0x100);
                  tmp_l3 = strtol((char *)local_41c,(char **)0x0,10);
                  if ((char)local_41c[0] == '\0') {
                    if ((int)ROUND(tmp_l6) != tmp_l3) goto LAB_000415d2;
                  }
                  else if ((int)ROUND(tmp_l6) != tmp_l3) goto LAB_00041679;
                  trap_Cvar_Set("r_oldMode","");
                  goto LAB_000415d2;
                }
                if ((_DAT_003e0f9c < 0) || (g_dat_003e0f98 <= _DAT_003e0f9c)) goto LAB_000415d2;
              }
            }
            goto LAB_00041679;
          }
          tmp_pc1 = "ui_profile_renameto";
        }
        (**(void **)(DC + 0x70))(tmp_pc1,local_41c,0x100);
        Q_CleanStr(local_41c);
        Q_CleanDirName(local_41c);
        tmp_u5 = va("profiles/%s/profile.dat",local_41c);
        tmp_i2 = trap_FS_FOpenFile(tmp_u5,local_51c,0);
        if (-1 < tmp_i2) {
          trap_FS_FCloseFile(local_51c[0]);
          local_528 = local_52c;
        }
        goto LAB_000415d2;
      }
      (**(void **)(DC + 0x70))("ui_profile",local_51c,0x100);
      Q_strncpyz(local_41c,local_51c,0x100);
      Q_CleanStr(local_41c);
      Q_CleanDirName(local_41c);
      if ((char)local_51c[0] == '\0') goto LAB_000415d2;
joined_r0x00041e06:
      if ((char)local_41c[0] == '\0') goto LAB_000415d2;
    }
  }
  else if (tmp_l3 == 3) {
    tmp_i4 = Int_Parse(param_3,local_41c);
    if (tmp_i4 == 0) {
      return;
    }
    tmp_l6 = (long double)(**(void **)(DC + 0x74))(tmp_i2);
    if ((long double)local_41c[0] != tmp_l6) goto LAB_000415d2;
  }
  else {
    if (tmp_l3 == 1) {
      (**(void **)(DC + 0x70))(tmp_i2,local_41c,0x400);
      goto joined_r0x00041e06;
    }
    tmp_l6 = (long double)(**(void **)(DC + 0x74))(tmp_i2);
    if (tmp_l6 == (long double)0) goto LAB_000415d2;
  }
LAB_00041679:
  local_528 = local_52c;
LAB_000415d2:
  Item_RunScript(param_1,param_2,local_528);
  return;
}

void Controls_GetConfig(void)

{
{  uint8_t **tmp_ppu1;
  uint8_t **tmp_ppu2;
  
  tmp_ppu1 = (uint8_t **)&g_dat_000693f8;
  do {
    tmp_ppu2 = tmp_ppu1 + 8;
    (**(void **)(DC + 0xbc))(tmp_ppu1[-6],tmp_ppu1,tmp_ppu1 + 1);
    tmp_ppu1 = tmp_ppu2;
  } while (tmp_ppu2 != &g_ptr_DAT_00069b98);
  return;
}

void Controls_SetConfig(int param_1)

{
{  uint8_t **tmp_ppu1;
  
  tmp_ppu1 = &g_bindings;
  do {
    if (tmp_ppu1[6] != (uint8_t *)0xffffffff) {
      (**(void **)(DC + 0xc4))(tmp_ppu1[6],*tmp_ppu1);
      if (tmp_ppu1[7] != (uint8_t *)0xffffffff) {
        (**(void **)(DC + 0xc4))(tmp_ppu1[7],*tmp_ppu1);
      }
    }
    tmp_ppu1 = tmp_ppu1 + 8;
  } while (tmp_ppu1 != &commandList);
  if (param_1 != 0) {
    (**(void **)(DC + 200))(2,"in_restart\n");
  }
  return;
}

void Controls_SetDefaults(int param_1)

{
{  uint8_t **tmp_ppu1;
  uint8_t **tmp_ppu2;
  
  if (param_1 == 0) {
    tmp_ppu2 = (uint8_t **)&g_dat_000693e8;
    do {
      tmp_ppu1 = tmp_ppu2 + 8;
      tmp_ppu2[5] = tmp_ppu2[1];
      tmp_ppu2[4] = *tmp_ppu2;
      tmp_ppu2 = tmp_ppu1;
    } while (tmp_ppu1 != &g_ptr_s_fadeout_00069b88);
    return;
  }
  tmp_ppu2 = (uint8_t **)&g_dat_000693f0;
  do {
    tmp_ppu1 = tmp_ppu2 + 8;
    tmp_ppu2[3] = tmp_ppu2[1];
    tmp_ppu2[2] = *tmp_ppu2;
    tmp_ppu2 = tmp_ppu1;
  } while (tmp_ppu1 != &g_ptr_s_show_00059075_8_00069b90);
  return;
}

int BindingIDFromName(uint32_t param_1)

{
{  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = 0;
  do {
    tmp_i1 = Q_stricmp(param_1,(&g_bindings)[tmp_i2 * 8]);
    if (tmp_i1 == 0) {
      return tmp_i2;
    }
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 0x3d);
  return -1;
}

uint8_t * BindingFromName(uint32_t param_1)

{
{  uint32_t tmp_u1;
  int local_14;
  int local_10;
  
  (**(void **)(DC + 0xbc))(param_1,&local_14,&local_10);
  if (local_14 == -1) {
    tmp_u1 = va(&g_dat_00055ada,param_1);
    Q_strncpyz(g_nameBind1,tmp_u1,0x20);
  }
  else {
    (**(void **)(DC + 0xb4))(local_14,g_nameBind1,0x20);
    Q_strupr(g_nameBind1);
    if (local_10 != -1) {
      (**(void **)(DC + 0xb4))(local_10,g_nameBind2,0x20);
      Q_strupr(g_nameBind2);
      Q_strcat(g_nameBind1,0x20,&g_dat_00058968);
      Q_strcat(g_nameBind1,0x20,g_nameBind2);
    }
  }
  return g_nameBind1;
}

void AdjustFrom640(float *param_1,float *param_2,float *param_3,float *param_4)

{
{  *param_1 = *param_1 * *(float *)(DC + 0x114);
  *param_2 = *param_2 * *(float *)(DC + 0x110);
  *param_3 = *param_3 * *(float *)(DC + 0x114);
  *param_4 = *param_4 * *(float *)(DC + 0x110);
  if (1.3333334 < *(float *)(&g_dat_0002003c + DC)) {
    *param_1 = (1.3333334 / *(float *)(&g_dat_0002003c + DC)) * *param_1;
    *param_3 = (1.3333334 / *(float *)(&g_dat_0002003c + DC)) * *param_3;
  }
  return;
}

void Script_Open(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    String_Alloc(tmp_pc1);
    Menus_ActivateByName();
    return;
  }
  return;
}

void Script_ConditionalOpen(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  long tmp_l3;
  uint32_t tmp_u4;
  int tmp_i5;
  long double tmp_l6;
  uint32_t local_420;
  char local_41c [1036];
  
  local_420 = 0;
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_u2 = String_Alloc(tmp_pc1);
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_u4 = String_Alloc(tmp_pc1);
  tmp_i5 = String_Parse(param_3,&local_420);
  if (tmp_i5 == 0) {
    return;
  }
  if (tmp_l3 == 1) {
    (**(void **)(DC + 0x70))(tmp_u2,local_41c,0x400);
    if (local_41c[0] != '\0') goto LAB_0004af05;
  }
  else {
    tmp_l6 = (long double)(**(void **)(DC + 0x74))(tmp_u2);
    if (tmp_l6 != (long double)0) {
LAB_0004af05:
      Menus_ActivateByName(tmp_u4,1);
      return;
    }
  }
  Menus_ActivateByName(local_420,1);
  return;
}

void Script_Close(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    String_Alloc(tmp_pc1);
    Menus_CloseByName();
    return;
  }
  return;
}

void Scroll_ListBox_ThumbFunc(int *param_1)

{
{  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  int *tmp_pi4;
  float tmp_f5;
  int tmp_i6;
  int tmp_i7;
  
  pfVar3 = (float *)param_1[6];
  tmp_pi4 = (int *)pfVar3[0x94];
  if ((*(byte *)((int)pfVar3 + 0x49) & 4) == 0) {
    tmp_i6 = DC;
    if ((float)*(int *)(DC + 0x128) != (float)param_1[5]) {
      tmp_f1 = pfVar3[1];
      tmp_f2 = pfVar3[3];
      tmp_i6 = (**(void **)(DC + 0x90))(pfVar3[0x92]);
      if ((*(byte *)((int)pfVar3 + 0x49) & 4) == 0) {
        tmp_f5 = pfVar3[3] / (float)tmp_pi4[5];
      }
      else {
        tmp_f5 = pfVar3[2] / (float)tmp_pi4[4];
      }
      tmp_i6 = tmp_i6 - (int)ROUND(tmp_f5);
      if (tmp_i6 < 0) {
        tmp_i6 = 0;
      }
      tmp_i7 = (int)ROUND(((float)tmp_i6 *
                         (((float)*(int *)(DC + 0x128) - (tmp_f1 + 16.0 + 1.0)) - 8.0)) /
                         (((tmp_f2 - 32.0) - 2.0) - 16.0));
      if (tmp_i7 < 0) {
        tmp_i7 = 0;
      }
      else if (tmp_i6 < tmp_i7) {
        tmp_i7 = tmp_i6;
      }
      *tmp_pi4 = tmp_i7;
      tmp_i6 = DC;
      param_1[5] = (int)(float)*(int *)(DC + 0x128);
    }
    tmp_i6 = *(int *)(tmp_i6 + 0x11c);
    if (tmp_i6 <= *param_1) goto LAB_0004b985;
  }
  else {
    if ((float)*(int *)(DC + 0x124) == (float)param_1[4]) {
      return;
    }
    tmp_f1 = *pfVar3;
    tmp_f2 = pfVar3[2];
    tmp_i6 = (**(void **)(DC + 0x90))(pfVar3[0x92]);
    if ((*(byte *)((int)pfVar3 + 0x49) & 4) == 0) {
      tmp_f5 = pfVar3[3] / (float)tmp_pi4[5];
    }
    else {
      tmp_f5 = pfVar3[2] / (float)tmp_pi4[4];
    }
    tmp_i6 = tmp_i6 - (int)ROUND(tmp_f5);
    if (tmp_i6 < 0) {
      tmp_i6 = 0;
    }
    tmp_i7 = (int)ROUND(((float)tmp_i6 * (((float)*(int *)(DC + 0x124) - (tmp_f1 + 16.0 + 1.0)) - 8.0))
                       / (((tmp_f2 - 32.0) - 2.0) - 16.0));
    if (tmp_i7 < 0) {
      tmp_i7 = 0;
    }
    else if (tmp_i6 < tmp_i7) {
      tmp_i7 = tmp_i6;
    }
    *tmp_pi4 = tmp_i7;
    tmp_i6 = DC;
    param_1[4] = (int)(float)*(int *)(DC + 0x124);
    tmp_i6 = *(int *)(tmp_i6 + 0x11c);
    if (tmp_i6 <= *param_1) goto LAB_0004b985;
  }
  lastListBoxClickTime = 0;
  Item_ListBox_HandleKey(param_1[6],param_1[3],1,0);
  *param_1 = param_1[2] + *(int *)(DC + 0x11c);
  tmp_i6 = *(int *)(DC + 0x11c);
LAB_0004b985:
  if (param_1[1] < tmp_i6) {
    param_1[1] = tmp_i6 + 0x96;
    if (0x14 < param_1[2]) {
      param_1[2] = param_1[2] + -0x28;
    }
  }
  return;
}

void Scroll_ListBox_AutoFunc(int *param_1)

{
{  int tmp_i1;
  
  tmp_i1 = *(int *)(DC + 0x11c);
  if (*param_1 < tmp_i1) {
    Item_ListBox_HandleKey(param_1[6],param_1[3],1,0);
    *param_1 = param_1[2] + *(int *)(DC + 0x11c);
    tmp_i1 = *(int *)(DC + 0x11c);
  }
  if (param_1[1] < tmp_i1) {
    param_1[1] = tmp_i1 + 0x96;
    if (0x14 < param_1[2]) {
      param_1[2] = param_1[2] + -0x28;
    }
  }
  return;
}
