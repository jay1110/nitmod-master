/* Unclassified recovered functions — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_unknown.h"

void unk_func_0001a090(void)
{
  (*(void *)(uint8_t *)0x0)();
  return;
}

void __x86_get_pc_thunk_bx(void)
{
  return;
}

void __x86_get_pc_thunk_cx(void)
{
  return;
}

uint32_t SkillForClass(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 5;
  if (param_1 - 1U < 4) {
    tmp_u1 = *(uint32_t *)(CSWTCH_91 + (param_1 - 1U) * 4);
  }
  return tmp_u1;
}

void ConcatArgs(int param_1)
{
  int tmp_i1;
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
  uStack_14 = 0x262eb;
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
      tmp_pu6 = (uint *)(&line_12690 + tmp_i7);
      tmp_pu8 = (uint *)&local_41c;
      if ((uint8_t *)0x7 < tmp_pu4) {
        tmp_pu9 = tmp_pu6;
        if (((uint)tmp_pu6 & 1) != 0) {
          tmp_pu9 = (uint *)(&g_unk_001971a1 + tmp_i7);
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
        (&line_12690)[tmp_i5] = 0x20;
        tmp_i5 = tmp_i5 + 1;
      }
      param_1 = param_1 + 1;
      tmp_i7 = tmp_i5;
    } while (param_1 != tmp_i1);
  }
  else {
    tmp_i7 = 0;
  }
  (&line_12690)[tmp_i7] = 0;
  return;
}

void etpro_FinalizeTracemapClamp(int *param_1,int *param_2)
{
  int tmp_i1;
  
  if (*param_1 < 0) {
    *param_1 = 0;
  }
  else if (0xff < *param_1) {
    *param_1 = 0xff;
    tmp_i1 = *param_2;
    goto joined_r0x000355aa;
  }
  tmp_i1 = *param_2;
joined_r0x000355aa:
  if (-1 < tmp_i1) {
    if (0xff < tmp_i1) {
      *param_2 = 0xff;
    }
    return;
  }
  *param_2 = 0;
  return;
}

uint8_t * in_word_set(byte *param_1,uint param_2)
{
  int tmp_i1;
  uint tmp_u2;
  
  tmp_u2 = param_2 - 1;
  if (0x1d < tmp_u2) {
    return (uint8_t *)0x0;
  }
  if (param_2 != 2) {
    if (param_2 < 3) {
      tmp_i1 = 1;
      if (param_2 == 1) goto LAB_00036f37;
LAB_00036fa3:
      param_2 = param_2 + *(ushort *)(asso_values_2080 + (uint)param_1[5] * 2);
    }
    else if (5 < param_2) goto LAB_00036fa3;
    param_2 = param_2 + *(ushort *)(asso_values_2080 + (param_1[2] + 1) * 2);
  }
  tmp_i1 = param_2 + *(ushort *)(asso_values_2080 + (uint)param_1[1] * 2);
LAB_00036f37:
  tmp_u2 = (uint)*(ushort *)(asso_values_2080 + (uint)*param_1 * 2) +
          (uint)*(ushort *)(asso_values_2080 + (uint)param_1[tmp_u2] * 2) + tmp_i1;
  if ((tmp_u2 < 0x4a3) && (**(byte **)(wordlist_2093 + tmp_u2 * 8) == *param_1)) {
    tmp_i1 = strcmp((char *)(param_1 + 1),(char *)(*(byte **)(wordlist_2093 + tmp_u2 * 8) + 1));
    if (tmp_i1 == 0) {
      return wordlist_2093 + tmp_u2 * 8;
    }
    return (uint8_t *)0x0;
  }
  return (uint8_t *)0x0;
}

void __x86_get_pc_thunk_dx(void)
{
  return;
}

long double lt_random(int param_1,int param_2)
{
  return (long double)
         *(ushort *)
          (randtable +
          ((param_2 + param_1 + (g_unk_010906e0 / 100) * (g_unk_010906e0 / 100)) % 0x101) * 2) /
         (long double)65535.0;
}

long double lt_crandom(int param_1,int param_2)
{
  return (long double)
         (((float)*(ushort *)
                   (randtable +
                   ((param_2 + param_1 + (g_unk_010906e0 / 100) * (g_unk_010906e0 / 100)) % 0x101) * 2)
           / 65535.0 +
          (float)*(ushort *)
                  (randtable +
                  ((param_2 + param_1 + (g_unk_010906e0 / 100) * (g_unk_010906e0 / 100)) % 0x101) * 2) /
          65535.0) - 1.0);
}

void InitSmokeSprites(void)
{
  memset(SmokeSprites,0,0x7800);
  firstfreesmokesprite = (uint8_t *)0x2bb224;
  do {
    *(uint8_t **)(firstfreesmokesprite + -0x3c) = firstfreesmokesprite;
    firstfreesmokesprite = firstfreesmokesprite + -0x3c;
  } while (firstfreesmokesprite != SmokeSprites);
  lastusedsmokesprite = 0;
  SmokeSpriteCount = 0;
  return;
}

void CGRefEntityToTag(int param_1,uint32_t *param_2)
{
  *param_2 = *(uint32_t *)(param_1 + 0x68);
  param_2[1] = *(uint32_t *)(param_1 + 0x6c);
  param_2[2] = *(uint32_t *)(param_1 + 0x70);
  param_2[3] = *(uint32_t *)(param_1 + 0x1c);
  param_2[4] = *(uint32_t *)(param_1 + 0x20);
  param_2[5] = *(uint32_t *)(param_1 + 0x24);
  param_2[6] = *(uint32_t *)(param_1 + 0x28);
  param_2[7] = *(uint32_t *)(param_1 + 0x2c);
  param_2[8] = *(uint32_t *)(param_1 + 0x30);
  param_2[9] = *(uint32_t *)(param_1 + 0x34);
  param_2[10] = *(uint32_t *)(param_1 + 0x38);
  param_2[0xb] = *(uint32_t *)(param_1 + 0x3c);
  return;
}

void CGTagToRefEntity(int param_1,uint32_t *param_2)
{
  *(uint32_t *)(param_1 + 0x68) = *param_2;
  *(uint32_t *)(param_1 + 0x6c) = param_2[1];
  *(uint32_t *)(param_1 + 0x70) = param_2[2];
  *(uint32_t *)(param_1 + 0x1c) = param_2[3];
  *(uint32_t *)(param_1 + 0x20) = param_2[4];
  *(uint32_t *)(param_1 + 0x24) = param_2[5];
  *(uint32_t *)(param_1 + 0x28) = param_2[6];
  *(uint32_t *)(param_1 + 0x2c) = param_2[7];
  *(uint32_t *)(param_1 + 0x30) = param_2[8];
  *(uint32_t *)(param_1 + 0x34) = param_2[9];
  *(uint32_t *)(param_1 + 0x38) = param_2[10];
  *(uint32_t *)(param_1 + 0x3c) = param_2[0xb];
  return;
}

void CG_AttachBitsToTank(int param_1,uint16_t *param_2,uint16_t *param_3,uint16_t *param_4,
                        uint16_t *param_5,uint16_t *param_6,float *param_7,uint32_t param_8,
                        int param_9)

{
  uint16_t *tmp_pu1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint tmp_u5;
  uint32_t *tmp_pu6;
  uint16_t *tmp_pu7;
  uint32_t tmp_u8;
  int tmp_i9;
  int *tmp_pi10;
  bool tmp_b11;
  uint32_t *local_188;
  uint local_184;
  float local_168;
  float local_164;
  float local_160;
  uint8_t local_15c [36];
  float local_138;
  float local_134;
  float local_130;
  uint8_t local_12c [36];
  float local_108 [62];
  
  tmp_b11 = ((uint)param_2 & 1) != 0;
  local_184 = 0xec;
  local_188 = (uint32_t *)param_2;
  if (tmp_b11) {
    *(uint8_t *)param_2 = 0;
    local_188 = (uint32_t *)((int)param_2 + 1);
    local_184 = 0xeb;
  }
  if (((uint)local_188 & 2) != 0) {
    *(uint16_t *)local_188 = 0;
    local_188 = (uint32_t *)((int)local_188 + 2);
    local_184 = local_184 - 2;
  }
  tmp_u5 = 0;
  do {
    *(uint32_t *)((int)local_188 + tmp_u5) = 0;
    *(uint32_t *)((int)local_188 + tmp_u5 + 4) = 0;
    tmp_u5 = tmp_u5 + 8;
  } while (tmp_u5 < (local_184 & 0xfffffff8));
  local_188 = (uint32_t *)((int)local_188 + tmp_u5);
  if ((local_184 & 4) != 0) {
    *local_188 = 0;
    local_188 = local_188 + 1;
  }
  if ((local_184 & 2) != 0) {
    *(uint16_t *)local_188 = 0;
    local_188 = (uint32_t *)((int)local_188 + 2);
  }
  if (tmp_b11) {
    *(uint8_t *)local_188 = 0;
  }
  tmp_b11 = ((uint)param_4 & 1) != 0;
  local_188 = (uint32_t *)param_4;
  local_184 = 0xec;
  if (tmp_b11) {
    local_188 = (uint32_t *)((int)param_4 + 1);
    *(uint8_t *)param_4 = 0;
    local_184 = 0xeb;
  }
  if (((uint)local_188 & 2) != 0) {
    *(uint16_t *)local_188 = 0;
    local_188 = (uint32_t *)((int)local_188 + 2);
    local_184 = local_184 - 2;
  }
  tmp_u5 = 0;
  do {
    *(uint32_t *)((int)local_188 + tmp_u5) = 0;
    *(uint32_t *)((int)local_188 + tmp_u5 + 4) = 0;
    tmp_u5 = tmp_u5 + 8;
  } while (tmp_u5 < (local_184 & 0xfffffff8));
  local_188 = (uint32_t *)((int)local_188 + tmp_u5);
  if ((local_184 & 4) != 0) {
    *local_188 = 0;
    local_188 = local_188 + 1;
  }
  if ((local_184 & 2) != 0) {
    *(uint16_t *)local_188 = 0;
    local_188 = (uint32_t *)((int)local_188 + 2);
  }
  if (tmp_b11) {
    *(uint8_t *)local_188 = 0;
  }
  tmp_b11 = ((uint)param_3 & 1) != 0;
  local_188 = (uint32_t *)0xec;
  tmp_pu7 = param_3;
  if (tmp_b11) {
    *(uint8_t *)param_3 = 0;
    tmp_pu7 = (uint16_t *)((int)param_3 + 1);
    local_188 = (uint32_t *)0xeb;
  }
  if (((uint)tmp_pu7 & 2) != 0) {
    *tmp_pu7 = 0;
    tmp_pu7 = tmp_pu7 + 1;
    local_188 = (uint32_t *)((int)local_188 - 2);
  }
  tmp_u5 = 0;
  do {
    *(uint32_t *)((int)tmp_pu7 + tmp_u5) = 0;
    *(uint32_t *)((int)tmp_pu7 + tmp_u5 + 4) = 0;
    tmp_u5 = tmp_u5 + 8;
  } while (tmp_u5 < ((uint)local_188 & 0xfffffff8));
  tmp_pu6 = (uint32_t *)((int)tmp_pu7 + tmp_u5);
  if (((uint)local_188 & 4) != 0) {
    *tmp_pu6 = 0;
    tmp_pu6 = tmp_pu6 + 1;
  }
  if (((uint)local_188 & 2) != 0) {
    *(uint16_t *)tmp_pu6 = 0;
    tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
  }
  if (tmp_b11) {
    *(uint8_t *)tmp_pu6 = 0;
  }
  local_188 = (uint32_t *)0xec;
  tmp_b11 = ((uint)param_5 & 1) != 0;
  tmp_pu7 = param_5;
  if (tmp_b11) {
    *(uint8_t *)param_5 = 0;
    local_188 = (uint32_t *)0xeb;
    tmp_pu7 = (uint16_t *)((int)param_5 + 1);
  }
  if (((uint)tmp_pu7 & 2) != 0) {
    *tmp_pu7 = 0;
    tmp_pu7 = tmp_pu7 + 1;
    local_188 = (uint32_t *)((int)local_188 - 2);
  }
  local_184 = 0;
  do {
    *(uint32_t *)((int)tmp_pu7 + local_184) = 0;
    *(uint32_t *)((int)tmp_pu7 + local_184 + 4) = 0;
    local_184 = local_184 + 8;
  } while (local_184 < ((uint)local_188 & 0xfffffff8));
  tmp_pu6 = (uint32_t *)((int)tmp_pu7 + local_184);
  if (((uint)local_188 & 4) != 0) {
    *tmp_pu6 = 0;
    tmp_pu6 = tmp_pu6 + 1;
  }
  if (((uint)local_188 & 2) != 0) {
    *(uint16_t *)tmp_pu6 = 0;
    tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
  }
  if (tmp_b11) {
    *(uint8_t *)tmp_pu6 = 0;
  }
  local_188 = (uint32_t *)0xec;
  tmp_b11 = ((uint)param_6 & 1) != 0;
  tmp_pu7 = param_6;
  if (tmp_b11) {
    *(uint8_t *)param_6 = 0;
    local_188 = (uint32_t *)0xeb;
    tmp_pu7 = (uint16_t *)((int)param_6 + 1);
  }
  if (((uint)tmp_pu7 & 2) != 0) {
    *tmp_pu7 = 0;
    tmp_pu7 = tmp_pu7 + 1;
    local_188 = (uint32_t *)((int)local_188 - 2);
  }
  local_184 = 0;
  do {
    *(uint32_t *)((int)tmp_pu7 + local_184) = 0;
    *(uint32_t *)((int)tmp_pu7 + local_184 + 4) = 0;
    local_184 = local_184 + 8;
  } while (local_184 < ((uint)local_188 & 0xfffffff8));
  tmp_pu6 = (uint32_t *)((int)tmp_pu7 + local_184);
  if (((uint)local_188 & 4) != 0) {
    *tmp_pu6 = 0;
    tmp_pu6 = tmp_pu6 + 1;
  }
  if (((uint)local_188 & 2) != 0) {
    *(uint16_t *)tmp_pu6 = 0;
    tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
  }
  if (tmp_b11) {
    *(uint8_t *)tmp_pu6 = 0;
  }
  *(uint32_t *)(param_2 + 4) = GHIDRA_FIELD(cgs, 69836, 4);
  *(uint32_t *)(param_3 + 4) = GHIDRA_FIELD(cgs, 69840, 4);
  tmp_u8 = GHIDRA_FIELD(cgs, 69848, 4);
  if (param_9 == 0) {
    tmp_u8 = GHIDRA_FIELD(cgs, 69844, 4);
  }
  *(uint32_t *)(param_4 + 4) = tmp_u8;
  tmp_i9 = CG_AddCEntity_Filter(param_1);
  if (tmp_i9 != 0) {
    if (*(int *)(param_1 + 0x9b8) == cg) {
      tmp_u8 = *(uint32_t *)(param_1 + 0x9c0);
    }
    else {
      *(int *)(param_1 + 0x9b8) = cg;
      tmp_u5 = 0;
      do {
        *(uint32_t *)((int)local_108 + tmp_u5) = 0;
        *(uint32_t *)((int)local_108 + tmp_u5 + 4) = 0;
        tmp_u5 = tmp_u5 + 8;
      } while (tmp_u5 < 0xe8);
      tmp_i9 = *(int *)(param_1 + 0xb4);
      *(uint32_t *)((int)local_108 + tmp_u5) = 0;
      if (tmp_i9 == 0xffffff) {
        local_108[2] = (float)CG_GetGameModel(*(uint32_t *)(param_1 + 0xa8));
      }
      else {
        local_108[2] = (float)CG_GetGameModel(*(uint32_t *)(param_1 + 0xa4));
      }
      local_108[0x1d] = *(float *)(param_1 + 0x844);
      local_108[0x28] = *(float *)(param_1 + 0x850);
      local_108[0x24] = *(float *)(param_1 + 0x838);
      AnglesToAxis(param_1 + 0x7a0,local_108 + 7);
      tmp_pu7 = param_2 + 0xe;
      local_108[0x1a] = *(float *)(param_1 + 0x794);
      local_108[0x1b] = *(float *)(param_1 + 0x798);
      local_108[0x1c] = *(float *)(param_1 + 0x79c);
      AxisClear(tmp_pu7);
      trap_R_LerpTag(&local_138,local_108,param_8,0);
      *(float *)(param_2 + 0x34) =
           local_134 * local_108[10] + local_138 * local_108[7] + local_108[0x1a] +
           local_108[0xd] * local_130;
      *(float *)(param_2 + 0x36) =
           local_108[0xb] * local_134 + local_108[8] * local_138 + local_108[0x1b] +
           local_108[0xe] * local_130;
      *(float *)(param_2 + 0x38) =
           local_108[0xc] * local_134 + local_108[9] * local_138 + local_108[0x1c] +
           local_108[0xf] * local_130;
      MatrixMultiply(local_12c,local_108 + 7,tmp_pu7);
      local_168 = 0.0;
      local_164 = param_7[1];
      local_160 = param_7[2];
      if (((*(byte *)(g_unk_01047b00 + 0x95) & 0x80) == 0) ||
         (*(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xab4) !=
          (param_1 + -0x3133e40 >> 3) * -0xbab6561)) {
        if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
          tmp_pi10 = (int *)(cg_entities + 0x244);
          tmp_i9 = 0;
          do {
            if (((*tmp_pi10 != 0) && ((*(byte *)((int)tmp_pi10 + -0x23b) & 0x80) != 0)) &&
               (tmp_pi10[0x21c] == (param_1 + -0x3133e40 >> 3) * -0xbab6561)) goto LAB_0006ef9d;
            tmp_i9 = tmp_i9 + 1;
            tmp_pi10 = tmp_pi10 + 0x2be;
          } while (tmp_i9 != GHIDRA_FIELD(cgs, 27400, 4));
        }
      }
      else {
LAB_0006ef9d:
        local_164 = local_164 - *(float *)(param_1 + 0x7a4);
        local_168 = 0.0 - *(float *)(param_1 + 0x7a0);
      }
      tmp_pu1 = param_3 + 0xe;
      AnglesToAxis(&local_168,tmp_pu1);
      trap_R_LerpTag(&local_138,param_2,"tag_mg42nest",0);
      tmp_f2 = *(float *)(param_2 + 0x34);
      *(float *)(param_3 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_2 + 0x36);
      *(float *)(param_3 + 0x36) = tmp_f3;
      tmp_f4 = *(float *)(param_2 + 0x38);
      *(float *)(param_3 + 0x38) = tmp_f4;
      tmp_f2 = *(float *)(param_2 + 0xe) * local_138 + tmp_f2;
      *(float *)(param_3 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_2 + 0x10) * local_138 + tmp_f3;
      *(float *)(param_3 + 0x36) = tmp_f3;
      tmp_f4 = local_138 * *(float *)(param_2 + 0x12) + tmp_f4;
      *(float *)(param_3 + 0x38) = tmp_f4;
      tmp_f2 = *(float *)(param_2 + 0x14) * local_134 + tmp_f2;
      *(float *)(param_3 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_2 + 0x16) * local_134 + tmp_f3;
      *(float *)(param_3 + 0x36) = tmp_f3;
      tmp_f4 = local_134 * *(float *)(param_2 + 0x18) + tmp_f4;
      *(float *)(param_3 + 0x38) = tmp_f4;
      *(float *)(param_3 + 0x34) = *(float *)(param_2 + 0x1a) * local_130 + tmp_f2;
      *(float *)(param_3 + 0x36) = *(float *)(param_2 + 0x1c) * local_130 + tmp_f3;
      *(float *)(param_3 + 0x38) = local_130 * *(float *)(param_2 + 0x1e) + tmp_f4;
      MatrixMultiply(tmp_pu1,local_12c,local_15c);
      MatrixMultiply(local_15c,tmp_pu7,tmp_pu1);
      local_164 = 0.0;
      local_160 = 0.0;
      local_168 = *param_7;
      tmp_pu7 = param_4 + 0xe;
      AnglesToAxis(&local_168,tmp_pu7);
      trap_R_LerpTag(&local_138,param_3,"tag_mg42",0);
      tmp_f2 = *(float *)(param_3 + 0x34);
      *(float *)(param_4 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_3 + 0x36);
      *(float *)(param_4 + 0x36) = tmp_f3;
      tmp_f4 = *(float *)(param_3 + 0x38);
      *(float *)(param_4 + 0x38) = tmp_f4;
      tmp_f2 = *(float *)(param_3 + 0xe) * local_138 + tmp_f2;
      *(float *)(param_4 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_3 + 0x10) * local_138 + tmp_f3;
      *(float *)(param_4 + 0x36) = tmp_f3;
      tmp_f4 = local_138 * *(float *)(param_3 + 0x12) + tmp_f4;
      *(float *)(param_4 + 0x38) = tmp_f4;
      tmp_f2 = *(float *)(param_3 + 0x14) * local_134 + tmp_f2;
      *(float *)(param_4 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_3 + 0x16) * local_134 + tmp_f3;
      *(float *)(param_4 + 0x36) = tmp_f3;
      tmp_f4 = local_134 * *(float *)(param_3 + 0x18) + tmp_f4;
      *(float *)(param_4 + 0x38) = tmp_f4;
      *(float *)(param_4 + 0x34) = *(float *)(param_3 + 0x1a) * local_130 + tmp_f2;
      *(float *)(param_4 + 0x36) = *(float *)(param_3 + 0x1c) * local_130 + tmp_f3;
      *(float *)(param_4 + 0x38) = local_130 * *(float *)(param_3 + 0x1e) + tmp_f4;
      MatrixMultiply(tmp_pu7,local_12c,local_15c);
      MatrixMultiply(local_15c,tmp_pu1,tmp_pu7);
      trap_R_LerpTag(&local_138,param_3,"tag_playerpo",0);
      tmp_f2 = *(float *)(param_3 + 0x34);
      *(float *)(param_5 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_3 + 0x36);
      *(float *)(param_5 + 0x36) = tmp_f3;
      tmp_f4 = *(float *)(param_3 + 0x38);
      *(float *)(param_5 + 0x38) = tmp_f4;
      tmp_f2 = *(float *)(param_3 + 0xe) * local_138 + tmp_f2;
      *(float *)(param_5 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_3 + 0x10) * local_138 + tmp_f3;
      *(float *)(param_5 + 0x36) = tmp_f3;
      tmp_f4 = local_138 * *(float *)(param_3 + 0x12) + tmp_f4;
      *(float *)(param_5 + 0x38) = tmp_f4;
      tmp_f2 = *(float *)(param_3 + 0x14) * local_134 + tmp_f2;
      *(float *)(param_5 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_3 + 0x16) * local_134 + tmp_f3;
      *(float *)(param_5 + 0x36) = tmp_f3;
      tmp_f4 = local_134 * *(float *)(param_3 + 0x18) + tmp_f4;
      *(float *)(param_5 + 0x38) = tmp_f4;
      *(float *)(param_5 + 0x34) = *(float *)(param_3 + 0x1a) * local_130 + tmp_f2;
      *(float *)(param_5 + 0x36) = *(float *)(param_3 + 0x1c) * local_130 + tmp_f3;
      *(float *)(param_5 + 0x38) = local_130 * *(float *)(param_3 + 0x1e) + tmp_f4;
      MatrixMultiply(local_12c,tmp_pu1,param_5 + 0xe);
      trap_R_LerpTag(&local_138,param_4,"tag_flash",0);
      tmp_f2 = *(float *)(param_4 + 0x34);
      *(float *)(param_6 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_4 + 0x36);
      *(float *)(param_6 + 0x36) = tmp_f3;
      tmp_f4 = *(float *)(param_4 + 0x38);
      *(float *)(param_6 + 0x38) = tmp_f4;
      tmp_f2 = *(float *)(param_4 + 0xe) * local_138 + tmp_f2;
      *(float *)(param_6 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_4 + 0x10) * local_138 + tmp_f3;
      *(float *)(param_6 + 0x36) = tmp_f3;
      tmp_f4 = local_138 * *(float *)(param_4 + 0x12) + tmp_f4;
      *(float *)(param_6 + 0x38) = tmp_f4;
      tmp_f2 = *(float *)(param_4 + 0x14) * local_134 + tmp_f2;
      *(float *)(param_6 + 0x34) = tmp_f2;
      tmp_f3 = *(float *)(param_4 + 0x16) * local_134 + tmp_f3;
      *(float *)(param_6 + 0x36) = tmp_f3;
      tmp_f4 = local_134 * *(float *)(param_4 + 0x18) + tmp_f4;
      *(float *)(param_6 + 0x38) = tmp_f4;
      *(float *)(param_6 + 0x34) = *(float *)(param_4 + 0x1a) * local_130 + tmp_f2;
      *(float *)(param_6 + 0x36) = *(float *)(param_4 + 0x1c) * local_130 + tmp_f3;
      *(float *)(param_6 + 0x38) = local_130 * *(float *)(param_4 + 0x1e) + tmp_f4;
      MatrixMultiply(local_12c,tmp_pu7,param_6 + 0xe);
      tmp_u8 = *(uint32_t *)(param_2 + 0x34);
      *(uint32_t *)(param_1 + 0x9c0) = tmp_u8;
      *(uint32_t *)(param_1 + 0x9c4) = *(uint32_t *)(param_2 + 0x36);
      *(uint32_t *)(param_1 + 0x9c8) = *(uint32_t *)(param_2 + 0x38);
      *(uint32_t *)(param_1 + 0x9cc) = *(uint32_t *)(param_2 + 0xe);
      *(uint32_t *)(param_1 + 0x9d0) = *(uint32_t *)(param_2 + 0x10);
      *(uint32_t *)(param_1 + 0x9d4) = *(uint32_t *)(param_2 + 0x12);
      *(uint32_t *)(param_1 + 0x9d8) = *(uint32_t *)(param_2 + 0x14);
      *(uint32_t *)(param_1 + 0x9dc) = *(uint32_t *)(param_2 + 0x16);
      *(uint32_t *)(param_1 + 0x9e0) = *(uint32_t *)(param_2 + 0x18);
      *(uint32_t *)(param_1 + 0x9e4) = *(uint32_t *)(param_2 + 0x1a);
      *(uint32_t *)(param_1 + 0x9e8) = *(uint32_t *)(param_2 + 0x1c);
      *(uint32_t *)(param_1 + 0x9ec) = *(uint32_t *)(param_2 + 0x1e);
      *(uint32_t *)(param_1 + 0x9f0) = *(uint32_t *)(param_3 + 0x34);
      *(uint32_t *)(param_1 + 0x9f4) = *(uint32_t *)(param_3 + 0x36);
      *(uint32_t *)(param_1 + 0x9f8) = *(uint32_t *)(param_3 + 0x38);
      *(uint32_t *)(param_1 + 0x9fc) = *(uint32_t *)(param_3 + 0xe);
      *(uint32_t *)(param_1 + 0xa00) = *(uint32_t *)(param_3 + 0x10);
      *(uint32_t *)(param_1 + 0xa04) = *(uint32_t *)(param_3 + 0x12);
      *(uint32_t *)(param_1 + 0xa08) = *(uint32_t *)(param_3 + 0x14);
      *(uint32_t *)(param_1 + 0xa0c) = *(uint32_t *)(param_3 + 0x16);
      *(uint32_t *)(param_1 + 0xa10) = *(uint32_t *)(param_3 + 0x18);
      *(uint32_t *)(param_1 + 0xa14) = *(uint32_t *)(param_3 + 0x1a);
      *(uint32_t *)(param_1 + 0xa18) = *(uint32_t *)(param_3 + 0x1c);
      *(uint32_t *)(param_1 + 0xa1c) = *(uint32_t *)(param_3 + 0x1e);
      *(uint32_t *)(param_1 + 0xa20) = *(uint32_t *)(param_4 + 0x34);
      *(uint32_t *)(param_1 + 0xa24) = *(uint32_t *)(param_4 + 0x36);
      *(uint32_t *)(param_1 + 0xa28) = *(uint32_t *)(param_4 + 0x38);
      *(uint32_t *)(param_1 + 0xa2c) = *(uint32_t *)(param_4 + 0xe);
      *(uint32_t *)(param_1 + 0xa30) = *(uint32_t *)(param_4 + 0x10);
      *(uint32_t *)(param_1 + 0xa34) = *(uint32_t *)(param_4 + 0x12);
      *(uint32_t *)(param_1 + 0xa38) = *(uint32_t *)(param_4 + 0x14);
      *(uint32_t *)(param_1 + 0xa3c) = *(uint32_t *)(param_4 + 0x16);
      *(uint32_t *)(param_1 + 0xa40) = *(uint32_t *)(param_4 + 0x18);
      *(uint32_t *)(param_1 + 0xa44) = *(uint32_t *)(param_4 + 0x1a);
      *(uint32_t *)(param_1 + 0xa48) = *(uint32_t *)(param_4 + 0x1c);
      *(uint32_t *)(param_1 + 0xa4c) = *(uint32_t *)(param_4 + 0x1e);
      *(uint32_t *)(param_1 + 0xa50) = *(uint32_t *)(param_5 + 0x34);
      *(uint32_t *)(param_1 + 0xa54) = *(uint32_t *)(param_5 + 0x36);
      *(uint32_t *)(param_1 + 0xa58) = *(uint32_t *)(param_5 + 0x38);
      *(uint32_t *)(param_1 + 0xa5c) = *(uint32_t *)(param_5 + 0xe);
      *(uint32_t *)(param_1 + 0xa60) = *(uint32_t *)(param_5 + 0x10);
      *(uint32_t *)(param_1 + 0xa64) = *(uint32_t *)(param_5 + 0x12);
      *(uint32_t *)(param_1 + 0xa68) = *(uint32_t *)(param_5 + 0x14);
      *(uint32_t *)(param_1 + 0xa6c) = *(uint32_t *)(param_5 + 0x16);
      *(uint32_t *)(param_1 + 0xa70) = *(uint32_t *)(param_5 + 0x18);
      *(uint32_t *)(param_1 + 0xa74) = *(uint32_t *)(param_5 + 0x1a);
      *(uint32_t *)(param_1 + 0xa78) = *(uint32_t *)(param_5 + 0x1c);
      *(uint32_t *)(param_1 + 0xa7c) = *(uint32_t *)(param_5 + 0x1e);
      *(uint32_t *)(param_1 + 0xa80) = *(uint32_t *)(param_6 + 0x34);
      *(uint32_t *)(param_1 + 0xa84) = *(uint32_t *)(param_6 + 0x36);
      *(uint32_t *)(param_1 + 0xa88) = *(uint32_t *)(param_6 + 0x38);
      *(uint32_t *)(param_1 + 0xa8c) = *(uint32_t *)(param_6 + 0xe);
      *(uint32_t *)(param_1 + 0xa90) = *(uint32_t *)(param_6 + 0x10);
      *(uint32_t *)(param_1 + 0xa94) = *(uint32_t *)(param_6 + 0x12);
      *(uint32_t *)(param_1 + 0xa98) = *(uint32_t *)(param_6 + 0x14);
      *(uint32_t *)(param_1 + 0xa9c) = *(uint32_t *)(param_6 + 0x16);
      *(uint32_t *)(param_1 + 0xaa0) = *(uint32_t *)(param_6 + 0x18);
      *(uint32_t *)(param_1 + 0xaa4) = *(uint32_t *)(param_6 + 0x1a);
      *(uint32_t *)(param_1 + 0xaa8) = *(uint32_t *)(param_6 + 0x1c);
      *(uint32_t *)(param_1 + 0xaac) = *(uint32_t *)(param_6 + 0x1e);
    }
    *(uint32_t *)(param_2 + 0x34) = tmp_u8;
    *(uint32_t *)(param_2 + 0x36) = *(uint32_t *)(param_1 + 0x9c4);
    *(uint32_t *)(param_2 + 0x38) = *(uint32_t *)(param_1 + 0x9c8);
    *(uint32_t *)(param_2 + 0xe) = *(uint32_t *)(param_1 + 0x9cc);
    *(uint32_t *)(param_2 + 0x10) = *(uint32_t *)(param_1 + 0x9d0);
    *(uint32_t *)(param_2 + 0x12) = *(uint32_t *)(param_1 + 0x9d4);
    *(uint32_t *)(param_2 + 0x14) = *(uint32_t *)(param_1 + 0x9d8);
    *(uint32_t *)(param_2 + 0x16) = *(uint32_t *)(param_1 + 0x9dc);
    *(uint32_t *)(param_2 + 0x18) = *(uint32_t *)(param_1 + 0x9e0);
    *(uint32_t *)(param_2 + 0x1a) = *(uint32_t *)(param_1 + 0x9e4);
    *(uint32_t *)(param_2 + 0x1c) = *(uint32_t *)(param_1 + 0x9e8);
    *(uint32_t *)(param_2 + 0x1e) = *(uint32_t *)(param_1 + 0x9ec);
    *(uint32_t *)(param_3 + 0x34) = *(uint32_t *)(param_1 + 0x9f0);
    *(uint32_t *)(param_3 + 0x36) = *(uint32_t *)(param_1 + 0x9f4);
    *(uint32_t *)(param_3 + 0x38) = *(uint32_t *)(param_1 + 0x9f8);
    *(uint32_t *)(param_3 + 0xe) = *(uint32_t *)(param_1 + 0x9fc);
    *(uint32_t *)(param_3 + 0x10) = *(uint32_t *)(param_1 + 0xa00);
    *(uint32_t *)(param_3 + 0x12) = *(uint32_t *)(param_1 + 0xa04);
    *(uint32_t *)(param_3 + 0x14) = *(uint32_t *)(param_1 + 0xa08);
    *(uint32_t *)(param_3 + 0x16) = *(uint32_t *)(param_1 + 0xa0c);
    *(uint32_t *)(param_3 + 0x18) = *(uint32_t *)(param_1 + 0xa10);
    *(uint32_t *)(param_3 + 0x1a) = *(uint32_t *)(param_1 + 0xa14);
    *(uint32_t *)(param_3 + 0x1c) = *(uint32_t *)(param_1 + 0xa18);
    *(uint32_t *)(param_3 + 0x1e) = *(uint32_t *)(param_1 + 0xa1c);
    *(uint32_t *)(param_4 + 0x34) = *(uint32_t *)(param_1 + 0xa20);
    *(uint32_t *)(param_4 + 0x36) = *(uint32_t *)(param_1 + 0xa24);
    *(uint32_t *)(param_4 + 0x38) = *(uint32_t *)(param_1 + 0xa28);
    *(uint32_t *)(param_4 + 0xe) = *(uint32_t *)(param_1 + 0xa2c);
    *(uint32_t *)(param_4 + 0x10) = *(uint32_t *)(param_1 + 0xa30);
    *(uint32_t *)(param_4 + 0x12) = *(uint32_t *)(param_1 + 0xa34);
    *(uint32_t *)(param_4 + 0x14) = *(uint32_t *)(param_1 + 0xa38);
    *(uint32_t *)(param_4 + 0x16) = *(uint32_t *)(param_1 + 0xa3c);
    *(uint32_t *)(param_4 + 0x18) = *(uint32_t *)(param_1 + 0xa40);
    *(uint32_t *)(param_4 + 0x1a) = *(uint32_t *)(param_1 + 0xa44);
    *(uint32_t *)(param_4 + 0x1c) = *(uint32_t *)(param_1 + 0xa48);
    *(uint32_t *)(param_4 + 0x1e) = *(uint32_t *)(param_1 + 0xa4c);
    *(uint32_t *)(param_5 + 0x34) = *(uint32_t *)(param_1 + 0xa50);
    *(uint32_t *)(param_5 + 0x36) = *(uint32_t *)(param_1 + 0xa54);
    *(uint32_t *)(param_5 + 0x38) = *(uint32_t *)(param_1 + 0xa58);
    *(uint32_t *)(param_5 + 0xe) = *(uint32_t *)(param_1 + 0xa5c);
    *(uint32_t *)(param_5 + 0x10) = *(uint32_t *)(param_1 + 0xa60);
    *(uint32_t *)(param_5 + 0x12) = *(uint32_t *)(param_1 + 0xa64);
    *(uint32_t *)(param_5 + 0x14) = *(uint32_t *)(param_1 + 0xa68);
    *(uint32_t *)(param_5 + 0x16) = *(uint32_t *)(param_1 + 0xa6c);
    *(uint32_t *)(param_5 + 0x18) = *(uint32_t *)(param_1 + 0xa70);
    *(uint32_t *)(param_5 + 0x1a) = *(uint32_t *)(param_1 + 0xa74);
    *(uint32_t *)(param_5 + 0x1c) = *(uint32_t *)(param_1 + 0xa78);
    *(uint32_t *)(param_5 + 0x1e) = *(uint32_t *)(param_1 + 0xa7c);
    *(uint32_t *)(param_6 + 0x34) = *(uint32_t *)(param_1 + 0xa80);
    *(uint32_t *)(param_6 + 0x36) = *(uint32_t *)(param_1 + 0xa84);
    *(uint32_t *)(param_6 + 0x38) = *(uint32_t *)(param_1 + 0xa88);
    *(uint32_t *)(param_6 + 0xe) = *(uint32_t *)(param_1 + 0xa8c);
    *(uint32_t *)(param_6 + 0x10) = *(uint32_t *)(param_1 + 0xa90);
    *(uint32_t *)(param_6 + 0x12) = *(uint32_t *)(param_1 + 0xa94);
    *(uint32_t *)(param_6 + 0x14) = *(uint32_t *)(param_1 + 0xa98);
    *(uint32_t *)(param_6 + 0x16) = *(uint32_t *)(param_1 + 0xa9c);
    *(uint32_t *)(param_6 + 0x18) = *(uint32_t *)(param_1 + 0xaa0);
    *(uint32_t *)(param_6 + 0x1a) = *(uint32_t *)(param_1 + 0xaa4);
    *(uint32_t *)(param_6 + 0x1c) = *(uint32_t *)(param_1 + 0xaa8);
    *(uint32_t *)(param_6 + 0x1e) = *(uint32_t *)(param_1 + 0xaac);
  }
  return;
}

uint32_t SkillNumForClass(uint param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 0;
  if (param_1 < 5) {
    tmp_u1 = *(uint32_t *)(CSWTCH_11 + param_1 * 4);
  }
  return tmp_u1;
}

int weaponIconScale(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(cg_weapons + param_1 * 0x17ac + 0x1798);
  if (tmp_i1 == 0) {
    switch(param_1) {
    case 3:
    case 5:
    case 6:
    case 8:
    case 10:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x21:
    case 0x24:
    case 0x25:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2e:
      tmp_i1 = 2;
      break;
    default:
      return 1;
    }
  }
  return tmp_i1;
}

void GetMacAddress(void)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint8_t local_1a;
  uint8_t local_19;
  uint8_t local_18;
  uint8_t local_17;
  uint8_t local_16;
  uint8_t local_15;
  
  tmp_i1 = socket(2,2,0);
  if (-1 < tmp_i1) {
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    local_2c = 0x30687465;
    tmp_i2 = ioctl(tmp_i1,0x8913,&local_2c);
    if (-1 < tmp_i2) {
      tmp_i1 = ioctl(tmp_i1,0x8927,&local_2c);
      if (-1 < tmp_i1) {
        tmp_u3 = va(&g_unk_0011754f,local_1a,local_19,local_18,local_17,local_16,local_15);
        trap_Cvar_Register(0,&g_unk_00115a05,tmp_u3,0x442);
        trap_Cvar_Set(&g_unk_00115a05,tmp_u3);
      }
    }
  }
  return;
}

uint32_t ValidBloodPool(float *param_1)
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
  int tmp_i11;
  float local_c4;
  int local_b0;
  uint8_t local_9c [12];
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
  float local_58;
  uint8_t local_54 [4];
  int local_50;
  float local_4c;
  int local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x9df99;
  local_60 = 0.0;
  local_5c = 0.0;
  local_58 = 1.0;
  vectoangles(&local_60,local_9c);
  AngleVectors(local_9c,0,&local_90,&local_84);
  local_b0 = 2;
  tmp_f5 = local_60 * 0.5;
  tmp_f1 = *param_1;
  tmp_f7 = local_5c * 0.5;
  tmp_f2 = param_1[1];
  tmp_f6 = local_58 * 0.5;
  tmp_f3 = param_1[2];
  local_c4 = -8.0;
  do {
    tmp_i11 = 2;
    tmp_f8 = local_90 * local_c4;
    tmp_f9 = local_8c * local_c4;
    tmp_f10 = local_88 * local_c4;
    tmp_f4 = -8.0;
    while( true ) {
      local_78 = local_84 * tmp_f4 + tmp_f8 + tmp_f5 + tmp_f1;
      local_74 = tmp_f9 + tmp_f7 + tmp_f2 + local_80 * tmp_f4;
      local_70 = tmp_f4 * local_7c + tmp_f10 + tmp_f6 + tmp_f3;
      local_6c = local_78 - local_60;
      local_68 = local_74 - local_5c;
      local_64 = local_70 - local_58;
      CG_Trace(local_54,&local_78,0,0,&local_6c,0xffffffff,1);
      if ((local_20 < 0x3fe) || (local_50 != 0)) {
        return 0;
      }
      if (1.0 <= local_4c) {
        return 0;
      }
      tmp_f4 = tmp_f4 + 16.0;
      if (tmp_i11 == 1) break;
      tmp_i11 = 1;
    }
    local_c4 = local_c4 + 16.0;
    if (local_b0 == 1) {
      return 1;
    }
    local_b0 = 1;
  } while( true );
}

void InitSkillLevelStructure(int param_1)
{
  char *__nptr;
  long tmp_l1;
  int tmp_i2;
  long local_130 [5];
  char local_11c [268];
  
  switch(param_1) {
  case 0:
    Q_strncpyz(local_11c,0x31289b8,0x100);
    break;
  case 1:
    Q_strncpyz(local_11c,0x31286b8,0x100);
    break;
  case 2:
    Q_strncpyz(local_11c,0x31285b8,0x100);
    break;
  case 3:
    Q_strncpyz(local_11c,0x31287b8,0x100);
    break;
  case 4:
    Q_strncpyz(local_11c,0x3128ab8,0x100);
    break;
  case 5:
    Q_strncpyz(local_11c,0x31284b8,0x100);
    break;
  case 6:
    Q_strncpyz(local_11c,0x31288b8,0x100);
  }
  __nptr = strtok(local_11c," ");
  if (__nptr != (char *)0x0) {
    tmp_i2 = 0;
    do {
      tmp_l1 = strtol(__nptr,(char **)0x0,10);
      local_130[tmp_i2] = tmp_l1;
      tmp_i2 = tmp_i2 + 1;
      __nptr = strtok((char *)0x0," ,");
      if (4 < tmp_i2) break;
    } while (__nptr != (char *)0x0);
  }
  param_1 = param_1 * 0x18;
  *(long *)(skillLevels + param_1 + 4) = local_130[0];
  *(long *)(skillLevels + param_1 + 8) = local_130[1];
  *(long *)(skillLevels + param_1 + 0xc) = local_130[2];
  *(long *)(skillLevels + param_1 + 0x10) = local_130[3];
  *(long *)(skillLevels + param_1 + 0x14) = local_130[4];
  return;
}

void dllEntry(uint32_t param_1)
{
  syscall = param_1;
  return;
}

void testPrintInt(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x9f,param_1,param_2);
  return;
}

void testPrintFloat(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0xa0,param_1,param_2);
  return;
}

bool isET260(void)
{
  char *tmp_pc1;
  bool tmp_b2;
  char local_10c [260];
  
  (*syscall)(6,"version",local_10c,0x100);
  tmp_pc1 = strstr(local_10c,"2.55");
  tmp_b2 = false;
  if (tmp_pc1 == (char *)0x0) {
    tmp_pc1 = strstr(local_10c,"2.56");
    tmp_b2 = tmp_pc1 == (char *)0x0;
  }
  return tmp_b2;
}

void AddLean(uint32_t param_1,float *param_2,float param_3)
{
  uint8_t local_24 [12];
  float local_18;
  float local_14;
  float local_10;
  
  if (param_3 != 0.0) {
    AngleVectors(param_1,local_24,&local_18,0);
    *param_2 = param_3 * local_18 + *param_2;
    param_2[1] = param_3 * local_14 + param_2[1];
    param_2[2] = (param_2[2] + param_3 * local_10) - ABS(param_3 / 3.5);
    return;
  }
  return;
}

bool is_sidearm_smg(void)
{
  bool tmp_b1;
  
  if (((*(uint *)(g_unk_01047b00 + 0x400) != 0) ||
      (tmp_b1 = false, *(uint *)(g_unk_01047b00 + 0x404) != 0)) &&
     (tmp_b1 = false, (*(uint *)(g_unk_01047b00 + 0x400) & 0x84) == 0)) {
    tmp_b1 = (*(uint *)(g_unk_01047b00 + 0x404) & 0x300c) == 0;
  }
  return tmp_b1;
}

void ToWindowCoords(float *param_1,float *param_2,float *param_3)
{
  *param_1 = *param_1 + *param_3;
  *param_2 = *param_2 + param_3[1];
  return;
}

uint32_t ParseColorRange(int param_1,uint32_t param_2,int param_3)
{
  uint16_t tmp_u1;
  int tmp_i2;
  uint16_t *tmp_pu3;
  uint16_t *tmp_pu4;
  uint16_t *tmp_pu5;
  uint tmp_u6;
  uint tmp_u7;
  bool tmp_b8;
  uint8_t local_38;
  uint16_t auStack_37 [9];
  uint8_t local_24 [4];
  uint8_t local_20 [16];
  
  if ((*(int *)(param_1 + 0x128) == 0) || (*(int *)(param_1 + 0x244) == param_3)) {
    *(int *)(param_1 + 0x244) = param_3;
    tmp_pu3 = (uint16_t *)&local_38;
    tmp_i2 = PC_Float_Parse(param_2,local_24);
    if ((tmp_i2 != 0) &&
       ((tmp_i2 = PC_Float_Parse(param_2,local_20), tmp_i2 != 0 &&
        (tmp_i2 = PC_Color_Parse(param_2,tmp_pu3), tmp_i2 != 0)))) {
      if (*(int *)(param_1 + 0x128) < 10) {
        tmp_i2 = param_1 + 0x120 + *(int *)(param_1 + 0x128) * 0x1c;
        tmp_u7 = 0x1c;
        tmp_pu4 = (uint16_t *)(tmp_i2 + 0xc);
        tmp_b8 = ((uint)tmp_pu4 & 1) != 0;
        if (tmp_b8) {
          tmp_pu4 = (uint16_t *)(tmp_i2 + 0xd);
          tmp_u7 = 0x1b;
          *(uint8_t *)(tmp_i2 + 0xc) = local_38;
          tmp_pu3 = auStack_37;
        }
        tmp_pu5 = tmp_pu4;
        if (((uint)tmp_pu4 & 2) != 0) {
          tmp_u1 = *tmp_pu3;
          tmp_pu5 = tmp_pu4 + 1;
          tmp_pu3 = tmp_pu3 + 1;
          tmp_u7 = tmp_u7 - 2;
          *tmp_pu4 = tmp_u1;
        }
        tmp_u6 = 0;
        do {
          *(uint32_t *)((int)tmp_pu5 + tmp_u6) = *(uint32_t *)((int)tmp_pu3 + tmp_u6);
          tmp_u6 = tmp_u6 + 4;
        } while (tmp_u6 < (tmp_u7 & 0xfffffffc));
        tmp_i2 = 0;
        if ((tmp_u7 & 2) != 0) {
          *(uint16_t *)((int)tmp_pu5 + tmp_u6) = *(uint16_t *)((int)tmp_pu3 + tmp_u6);
          tmp_i2 = 2;
        }
        if (tmp_b8) {
          *(uint8_t *)((int)((int)tmp_pu5 + tmp_u6) + tmp_i2) =
               *(uint8_t *)((int)((int)tmp_pu3 + tmp_u6) + tmp_i2);
        }
        *(int *)(param_1 + 0x128) = *(int *)(param_1 + 0x128) + 1;
        return 1;
      }
      return 1;
    }
  }
  else {
    PC_SourceError(param_2,"both addColorRange and addColorRangeRel - set within same itemdef\n");
  }
  return 0;
}

char pingColor(int param_1)
{
  char tmp_c1;
  
  tmp_c1 = '\a';
  if (((GHIDRA_FIELD(cg_pingColors, 12, 4) != 0) && (tmp_c1 = '\x02', 100 < param_1)) &&
     (tmp_c1 = '\x03', 99 < param_1 - 0x65U)) {
    return (-(param_1 - 0xc9U < 0x96) & 7U) + 1;
  }
  return tmp_c1;
}

void CheckETLegacy(void)
{
  char *tmp_pc1;
  char local_10c [260];
  
  trap_Cvar_VariableStringBuffer("version",local_10c,0x100);
  tmp_pc1 = strstr(local_10c,"ET Legacy");
  GHIDRA_FIELD(cgs, 33823104, 4) = (uint)(tmp_pc1 != (char *)0x0);
  return;
}

uint8_t * G_GetDateAndTimeFileName(void)
{
  time_t tVar1;
  tm *__tp;
  uint8_t *tmp_pu2;
  time_t local_10 [2];
  
  tVar1 = time(local_10);
  tmp_pu2 = &g_unk_0011d841;
  if (tVar1 != 0) {
    tmp_pu2 = tstr_11942;
    __tp = localtime(local_10);
    strftime(tstr_11942,0x32,"%m-%d-%y_%H-%M-%S",__tp);
  }
  return tmp_pu2;
}

uint32_t INTHandler(void)
{
  CG_Printf("------------------------------------------------\n");
  CG_Printf("Ctrl-C is not the proper way to kill the server.\n");
  CG_Printf("------------------------------------------------\n");
  return 0;
}

void linux_siginfo(int param_1,int param_2)
{
  char *tmp_pc1;
  
  tmp_pc1 = strsignal(param_1);
  Crash_Printf("Signal: %s (%d)\n",tmp_pc1,param_1);
  Crash_Printf("Siginfo: %p\n",param_2);
  if (param_2 != 0) {
    Crash_Printf("Code: %d\n",*(uint32_t *)(param_2 + 8),param_1);
    Crash_Printf("Faulting Memory Ref/Instruction: %p\n",*(uint32_t *)(param_2 + 0xc));
  }
  return;
}

void linux_backtrace(int param_1)
{
  int tmp_i1;
  void *__ptr;
  int tmp_i2;
  int tmp_i3;
  uint8_t local_101c [4];
  uint32_t local_1018;
  uint32_t uStack_14;
  
  uStack_14 = 0x10878e;
  tmp_i1 = backtrace(local_101c,0x400);
  Crash_Printf("Stack frames: %zd entries\n",tmp_i1 + -1);
  local_1018 = *(uint32_t *)(param_1 + 0x4c);
  Crash_Printf("Backtrace:\n");
  __ptr = (void *)backtrace_symbols(local_101c,tmp_i1);
  if (1 < tmp_i1) {
    tmp_i2 = 1;
    do {
      tmp_i3 = tmp_i2 + 1;
      Crash_Printf(&g_unk_00121ff4,tmp_i2,*(uint32_t *)((int)__ptr + tmp_i2 * 4));
      tmp_i2 = tmp_i3;
    } while (tmp_i3 != tmp_i1);
  }
  free(__ptr);
  return;
}

void CrashHandler(int param_1,int param_2,uint32_t param_3)
{
  char *tmp_pc1;
  int tmp_i2;
  
  sigaction(0xb,(sigaction *)(oldact + 0x604),(sigaction *)0x0);
  if (param_1 == 0xb) {
    segvloop = segvloop + 1;
  }
  if (1 < segvloop) {
    CG_Error("Recursive segfault. Bailing out.");
    OldHandler = GHIDRA_FIELD(oldact, 1540, 4);
    (*(void *)GHIDRA_FIELD(oldact, 1540, 4))(param_1);
    return;
  }
  nitrox_OpenCrashLog();
  Crash_Printf("-8<--- Client Crash Information ---->8-\n");
  Crash_Printf("Please forward to N!tmod dev team. \n");
  Crash_Printf("---------------------------------------\n");
  Crash_Printf("Version: %s %s Linux %s\n",&g_unk_00116f02,"Feb 14 2023","linux-i386");
  Crash_Printf("Map: %s\n",0x10f69ac);
  tmp_pc1 = strsignal(param_1);
  tmp_i2 = param_1;
  Crash_Printf("Signal: %s (%d)\n",tmp_pc1,param_1);
  Crash_Printf("Siginfo: %p\n",param_2);
  if (param_2 != 0) {
    Crash_Printf("Code: %d\n",*(uint32_t *)(param_2 + 8),tmp_i2);
    Crash_Printf("Faulting Memory Ref/Instruction: %p\n",*(uint32_t *)(param_2 + 0xc));
  }
  linux_backtrace(param_3);
  CG_Printf("-8<--------------------------------->8-\n\n");
  CG_Printf("Attempting to clean up.\n");
  nitrox_CloseCrashLog();
  CG_Shutdown();
  if (param_1 == 0xb) {
    OldHandler = GHIDRA_FIELD(oldact, 1540, 4);
    (*(void *)GHIDRA_FIELD(oldact, 1540, 4))(0xb);
    return;
  }
  exit(1);
}

