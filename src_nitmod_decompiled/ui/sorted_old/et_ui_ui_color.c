/* Color tables, color ranges, color parsing
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"
#include "et_ui_imports.h"
#include "et_ui_ui_color.h"

uint32_t ColorBytes3(float param_1,float param_2,float param_3)

{
{  uint8_t local_4 [2];
  uint8_t uStack_2;
  
  _local_4 = CONCAT12((char)(short)ROUND(param_3 * 255.0),
                      CONCAT11((char)(short)ROUND(param_2 * 255.0),
                               (char)(short)ROUND(param_1 * 255.0)));
  return _local_4;
}

uint32_t ColorBytes4(float param_1,float param_2,float param_3,float param_4)

{
{  uint32_t local_4;
  
  local_4 = CONCAT13((char)(short)ROUND(param_4 * 255.0),
                     CONCAT12((char)(short)ROUND(param_3 * 255.0),
                              CONCAT11((char)(short)ROUND(param_2 * 255.0),
                                       (char)(short)ROUND(param_1 * 255.0))));
  return local_4;
}

void NormalizeColor(float *param_1,float *param_2)

{
{  float tmp_f1;
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

void Script_SetTeamColor(int param_1)

{
{  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  if (*(void **)(DC + 0x6c) != (void *)0x0) {
    (**(void **)(DC + 0x6c))(&local_1c);
    *(uint32_t *)(param_1 + 0x84) = local_1c;
    *(uint32_t *)(param_1 + 0x88) = local_18;
    *(uint32_t *)(param_1 + 0x8c) = local_14;
    *(uint32_t *)(param_1 + 0x90) = local_10;
  }
  return;
}

void Script_SetColor(int param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  double tmp_d5;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    tmp_u2 = String_Alloc(tmp_pc1);
    tmp_i3 = Q_stricmp(tmp_u2,"backcolor");
    if (tmp_i3 == 0) {
      *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x400000;
      tmp_i3 = param_1 + 0x84;
    }
    else {
      tmp_i3 = Q_stricmp(tmp_u2,"forecolor");
      if (tmp_i3 == 0) {
        tmp_i3 = param_1 + 0x74;
        *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x200;
      }
      else {
        tmp_i3 = Q_stricmp(tmp_u2,"bordercolor");
        if (tmp_i3 != 0) {
          return;
        }
        tmp_i3 = param_1 + 0x94;
      }
    }
    if (tmp_i3 != 0) {
      tmp_i4 = 0;
      do {
        tmp_pc1 = (char *)COM_ParseExt(param_3,0);
        if (tmp_pc1 == (char *)0x0) {
          return;
        }
        if (*tmp_pc1 == '\0') {
          return;
        }
        tmp_d5 = strtod(tmp_pc1,(char **)0x0);
        *(float *)(tmp_i3 + tmp_i4 * 4) = (float)tmp_d5;
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 != 4);
    }
  }
  return;
}

void LerpColor(float *param_1,float *param_2,float *param_3,float param_4)

{
{  float tmp_f1;
  
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
