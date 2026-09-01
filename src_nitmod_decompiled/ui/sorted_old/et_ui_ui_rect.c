/* Rectangle operations, geometry calculations
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"
#include "et_ui_imports.h"
#include "et_ui_ui_rect.h"

void RotateAroundDirection(float *param_1,float param_2)

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

void UI_FillRect(float param_1,float param_2,float param_3,float param_4,uint32_t param_5)

{
{  trap_R_SetColor(param_5);
  param_1 = g_dat_00397fd4 * param_1;
  param_3 = g_dat_00397fd4 * param_3;
  if (1.3333334 < g_dat_003b7efc) {
    param_1 = param_1 * (1.3333334 / g_dat_003b7efc);
    param_3 = (1.3333334 / g_dat_003b7efc) * param_3;
  }
  trap_R_DrawStretchPic
            (param_1,g_dat_00397fd0 * param_2,param_3,g_dat_00397fd0 * param_4,0,0,0,0,g_dat_003b7f10);
  trap_R_SetColor(0);
  return;
}

void UI_DrawRect(float param_1,float param_2,float param_3,float param_4,uint32_t param_5)

{
{  trap_R_SetColor(param_5);
  UI_DrawTopBottom(param_1,param_2,param_3,param_4);
  param_1 = param_1 * g_dat_00397fd4;
  param_2 = param_2 * g_dat_00397fd0;
  param_3 = param_3 * g_dat_00397fd4;
  param_4 = param_4 * g_dat_00397fd0;
  if (1.3333334 < g_dat_003b7efc) {
    param_1 = param_1 * (1.3333334 / g_dat_003b7efc);
    param_3 = (1.3333334 / g_dat_003b7efc) * param_3;
  }
  trap_R_DrawStretchPic(param_1,param_2,0x3f800000,param_4,0,0,0,0,g_dat_003b7f10);
  trap_R_DrawStretchPic((param_3 + param_1) - 1.0,param_2,0x3f800000,param_4,0,0,0,0,g_dat_003b7f10);
  trap_R_SetColor(0);
  return;
}

void Cui_WideRect(float *param_1)

{
{  int tmp_i1;
  long double tmp_l2;
  
  *param_1 = *param_1 * *(float *)(DC + 0x114);
  tmp_i1 = DC;
  param_1[1] = param_1[1] * *(float *)(DC + 0x110);
  param_1[2] = param_1[2] * *(float *)(tmp_i1 + 0x114);
  param_1[3] = param_1[3] * *(float *)(tmp_i1 + 0x110);
  if ((1.3333334 < *(float *)(&g_dat_0002003c + tmp_i1)) &&
     (tmp_l2 = (long double)(**(void **)(tmp_i1 + 0x74))("r_mode"), tmp_l2 != (long double)11.0)) {
    *param_1 = (1.3333334 / *(float *)(&g_dat_0002003c + DC)) * *param_1;
    param_1[2] = (1.3333334 / *(float *)(&g_dat_0002003c + DC)) * param_1[2];
    return;
  }
  return;
}

bool Rect_ContainsPoint(float *param_1,float param_2,float param_3)

{
{  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  
  if (param_1 != (float *)0x0) {
    tmp_f1 = *(float *)(&g_dat_0002003c + DC);
    if (tmp_f1 <= 1.3333334) {
      if (param_2 <= *param_1) {
        return false;
      }
      tmp_f3 = *param_1 + param_1[2];
    }
    else {
      tmp_f2 = tmp_f1 * 0.75;
      param_2 = param_2 * tmp_f2;
      if (param_2 <= *param_1 * tmp_f2) {
        return false;
      }
      tmp_f3 = *param_1 + param_1[2];
      if (1.3333334 < tmp_f1) {
        tmp_f3 = tmp_f2 * tmp_f3;
      }
    }
    if ((param_2 < tmp_f3) && (param_1[1] < param_3)) {
      return param_3 < param_1[1] + param_1[3];
    }
  }
  return false;
}
