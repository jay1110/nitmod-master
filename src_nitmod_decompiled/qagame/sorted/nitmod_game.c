/* Remaining G_* game logic — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_game.h"

bool G_DoAntiwarp(int param_1)
{
  int tmp_i1;
  bool tmp_b2;
  
  tmp_b2 = false;
  if ((GHIDRA_FIELD(g_antiwarp, 12, 4) != 0) && (GHIDRA_FIELD(g_gamestate, 12, 4) != 3)) {
    if ((param_1 == 0) || (tmp_i1 = *(int *)(param_1 + 400), tmp_i1 == 0)) {
      return true;
    }
    if (((*(int *)(tmp_i1 + 3000) != 3) && ((*(byte *)(tmp_i1 + 0xd) & 0x40) == 0)) &&
       (*(int *)(tmp_i1 + 0x5e8) == 0)) {
      tmp_b2 = 4999 < g_unk_00abe908 - *(int *)(tmp_i1 + 0x678);
    }
  }
  return tmp_b2;
}

void G_SetClientSound(int param_1)
{
  *(uint32_t *)(param_1 + 0xa0) = 0;
  return;
}

void G_TouchTriggers(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint8_t *tmp_pu6;
  float local_106c;
  float local_1068;
  float local_1064;
  float local_1060;
  float local_105c;
  float local_1058;
  int local_1054 [1041];
  
  if (*(int *)(param_1 + 400) != 0) {
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x103c) = 0;
    tmp_i4 = *(int *)(param_1 + 400);
    if ((0 < *(int *)(tmp_i4 + 0xd0)) && ((*(byte *)(tmp_i4 + 0x6a) & 0x80) == 0)) {
      local_106c = *(float *)(tmp_i4 + 0x14) - 40.0;
      local_1068 = *(float *)(tmp_i4 + 0x18) - 40.0;
      local_1064 = *(float *)(tmp_i4 + 0x1c) - 52.0;
      local_1060 = *(float *)(tmp_i4 + 0x14) + 40.0;
      local_105c = *(float *)(tmp_i4 + 0x18) + 40.0;
      local_1058 = *(float *)(tmp_i4 + 0x1c) + 52.0;
      tmp_i2 = trap_EntitiesInBox(&local_106c,&local_1060,local_1054 + 0xe,0x400);
      tmp_i4 = *(int *)(param_1 + 400);
      local_106c = *(float *)(param_1 + 0x134) + *(float *)(tmp_i4 + 0x14);
      local_1068 = *(float *)(param_1 + 0x138) + *(float *)(tmp_i4 + 0x18);
      local_1064 = *(float *)(param_1 + 0x13c) + *(float *)(tmp_i4 + 0x1c);
      local_1060 = *(float *)(tmp_i4 + 0x14) + *(float *)(param_1 + 0x140);
      local_105c = *(float *)(tmp_i4 + 0x18) + *(float *)(param_1 + 0x144);
      local_1058 = *(float *)(tmp_i4 + 0x1c) + *(float *)(param_1 + 0x148);
      if (0 < tmp_i2) {
        tmp_i4 = 0;
        do {
          tmp_i1 = (local_1054 + 0xe)[tmp_i4];
          if ((((*(int *)(g_entities + tmp_i1 * 0x600 + 0x2b0) != 0) ||
               (*(int *)(param_1 + 0x2b0) != 0)) &&
              (tmp_i5 = tmp_i1 * 0x600, (g_entities[tmp_i5 + 0x14f] & 0x40) != 0)) &&
             (1 < *(int *)(g_entities + tmp_i5 + 0x458) - 1U)) {
            tmp_pu6 = g_entities + tmp_i5;
            if (*(int *)(*(int *)(param_1 + 400) + 3000) == 3) {
              if (*(int *)(g_entities + tmp_i5 + 4) == 9) goto LAB_0004d6a7;
            }
            else {
              if (*(int *)(g_entities + tmp_i5 + 4) == 2) {
                tmp_i5 = BG_PlayerTouchesItem(*(int *)(param_1 + 400),tmp_pu6,g_unk_00abe908);
              }
              else {
LAB_0004d6a7:
                tmp_i5 = trap_EntityContactCapsule(&local_106c,&local_1060,tmp_pu6);
              }
              if (tmp_i5 != 0) {
                tmp_u3 = 0;
                do {
                  *(uint32_t *)((int)local_1054 + tmp_u3) = 0;
                  *(uint32_t *)((int)local_1054 + tmp_u3 + 4) = 0;
                  tmp_u3 = tmp_u3 + 8;
                } while (tmp_u3 < 0x38);
                if (*(void **)(g_entities + tmp_i1 * 0x600 + 0x2b0) != (void *)0x0) {
                  (**(void **)(g_entities + tmp_i1 * 0x600 + 0x2b0))(tmp_pu6,param_1,local_1054);
                }
              }
            }
          }
          tmp_i4 = tmp_i4 + 1;
        } while (tmp_i4 != tmp_i2);
      }
    }
  }
  return;
}

uint32_t G_SpectatorAttackFollow(uint32_t *param_1)
{
  int tmp_i1;
  float local_80;
  float local_7c;
  float local_78;
  uint8_t local_74 [12];
  uint8_t local_68 [12];
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  uint8_t local_44 [52];
  int local_10;
  
  if (param_1[100] != 0) {
    AngleVectors(param_1[100] + 0xb0,&local_80,local_74,local_68);
    tmp_i1 = param_1[100];
    local_5c = *(float *)(tmp_i1 + 0x14);
    local_58 = *(float *)(tmp_i1 + 0x18);
    local_54 = *(float *)(tmp_i1 + 0x1c);
    local_50 = local_80 * 8192.0 + local_5c;
    local_4c = local_7c * 8192.0 + local_58;
    local_48 = local_78 * 8192.0 + local_54;
    G_HistoricalTrace(param_1,local_44,&local_5c,0,0,&local_50,*param_1,0x6000001,0);
    if (*(int *)(g_entities + local_10 * 0x600 + 400) != 0) {
      *(uint32_t *)(param_1[100] + 0xbc0) = 2;
      *(int *)(param_1[100] + 0xbc4) = local_10;
      return 1;
    }
  }
  return 0;
}

void G_SetIdentifyClient(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i1 = *(int *)(param_1 + 400);
  tmp_i2 = *(int *)(tmp_i1 + 0x5a0) * 0x600;
  if (((*(int *)(g_entities + tmp_i2 + 0x194) == 0) || (*(int *)(g_entities + tmp_i2 + 400) == 0)) ||
     ((*(int *)(g_entities + tmp_i2 + 0x260) != *(int *)(param_1 + 0x260) &&
      ((*(int *)(*(int *)(g_entities + tmp_i2 + 400) + 0x16c) == 0 &&
       ((*(byte *)(tmp_i1 + 0xd) & 0x10) == 0)))))) {
    *(uint32_t *)(tmp_i1 + 0x5a0) = 0xffffffff;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x5a4) = 0;
  }
  else {
    *(uint32_t *)(tmp_i1 + 0x5a4) =
         *(uint32_t *)(g_entities + *(int *)(tmp_i1 + 0x5a0) * 0x600 + 0x2c8);
  }
  return;
}

void G_FallDamage(uint32_t *param_1,uint32_t param_2)
{
  uint *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  uint32_t tmp_u5;
  int local_78;
  int local_74;
  uint32_t local_6c;
  uint32_t local_68;
  float local_64;
  uint32_t local_60;
  uint32_t local_5c;
  float local_58;
  uint8_t local_54 [52];
  int local_20;
  
  if (param_1[1] != 1) {
    return;
  }
  tmp_i4 = param_1[0x25] * 0x600 + g_unk_00abe8a4;
  if (*(int *)(tmp_i4 + 400) == 0) {
    local_6c = param_1[0x5a];
    local_68 = param_1[0x5b];
    local_64 = (float)param_1[0x5c];
    local_58 = local_64 - 4.0;
    local_60 = local_6c;
    local_5c = local_68;
    trap_Trace(local_54,&local_6c,0,0,&local_60,*param_1,0x6000001);
    tmp_i4 = local_20 * 0x600 + g_unk_00abe8a4;
  }
  switch(param_2) {
  case 0xc:
    if ((GHIDRA_FIELD(g_goombaFlags, 12, 4) & 2) != 0) {
      return;
    }
    if (tmp_i4 == 0) {
      return;
    }
    local_74 = *(int *)(tmp_i4 + 400);
    if (local_74 == 0) {
      return;
    }
    if ((*(int *)(local_74 + 3000) == *(int *)(param_1[100] + 3000)) &&
       ((GHIDRA_FIELD(g_goombaFlags, 12, 4) & 4) != 0)) {
      return;
    }
    if (GHIDRA_FIELD(g_goomba, 12, 4) == 0) {
      return;
    }
    tmp_u3 = 0;
    local_78 = 0;
    if (*(int *)(tmp_i4 + 0x2cc) == 0) {
      return;
    }
    goto LAB_0004e67c;
  case 0xd:
    if ((GHIDRA_FIELD(g_goomba, 12, 4) != 0) && (tmp_i4 != 0)) {
      local_78 = 0;
      tmp_u3 = 500;
      goto LAB_0004e52c;
    }
    tmp_u3 = 500;
    goto LAB_0004e55d;
  case 0xe:
    local_78 = 0xfa;
    tmp_u3 = 10;
    break;
  case 0xf:
    tmp_u3 = 0xf;
    local_78 = 0xfa;
    break;
  case 0x10:
    tmp_u3 = 0x19;
    local_78 = 500;
    break;
  case 0x11:
    local_78 = 1000;
    tmp_u3 = 0x32;
    break;
  default:
    goto switchD_0004e50d_default;
  }
  if (GHIDRA_FIELD(g_goomba, 12, 4) == 0) {
LAB_0004e5cf:
    *(int *)(param_1[100] + 0x10) = local_78;
    *(uint *)(param_1[100] + 0xc) = *(uint *)(param_1[100] + 0xc) | 0x40;
LAB_0004e55d:
    param_1[0xb0] = g_unk_00abe908 + 200;
  }
  else {
    if (tmp_i4 == 0) {
LAB_0004e548:
      if (local_78 != 0) goto LAB_0004e5cf;
      goto LAB_0004e55d;
    }
LAB_0004e52c:
    local_74 = *(int *)(tmp_i4 + 400);
    if ((local_74 == 0) || (*(int *)(tmp_i4 + 0x2cc) == 0)) goto LAB_0004e548;
LAB_0004e67c:
    if (((GHIDRA_FIELD(g_gametype, 12, 4) != 8) && ((GHIDRA_FIELD(g_goombaFlags, 12, 4) & 1) != 0)) &&
       (*(int *)(local_74 + 3000) == *(int *)(param_1[100] + 3000))) {
      return;
    }
    if (tmp_u3 == 0) {
      tmp_u3 = 5;
    }
    if (local_78 != 0) {
      *(int *)(local_74 + 0x10) = local_78;
      tmp_pu1 = (uint *)(*(int *)(tmp_i4 + 400) + 0xc);
      *tmp_pu1 = *tmp_pu1 | 0x40;
    }
    *(int *)(tmp_i4 + 0x2c0) = g_unk_00abe908 + 200;
    if (0 < (int)param_1[0xb2]) {
      if ((GHIDRA_FIELD(g_goombaFlags, 12, 4) & 0x10) == 0) {
        tmp_u5 = 0;
        tmp_i2 = GHIDRA_FIELD(g_goomba, 12, 4) * tmp_u3;
      }
      else {
        tmp_u5 = 0x20;
        tmp_i2 = *(int *)(tmp_i4 + 0x2c8);
      }
      G_Damage(tmp_i4,param_1,param_1,0,0,tmp_i2,tmp_u5,0x3a);
    }
    if (tmp_u3 < 6) {
      nitmod_SoundEvent(tmp_i4,5);
      return;
    }
    if ((GHIDRA_FIELD(g_goombaFlags, 12, 4) & 8) != 0) {
      return;
    }
    tmp_u3 = (uint)ROUND((float)tmp_u3 * 0.2);
  }
  G_Damage(param_1,0,0,0,0,tmp_u3,0,0x1f);
switchD_0004e50d_default:
  return;
}

void G_RunClient(int param_1)
{
  int tmp_i1;
  
  if ((*(byte *)(*(int *)(param_1 + 400) + 0x5b4) & 0x40) == 0) {
    tmp_i1 = *(int *)(param_1 + 0x2c8);
  }
  else {
    Cmd_Activate2_f(param_1);
    tmp_i1 = *(int *)(param_1 + 0x2c8);
  }
  if (((tmp_i1 < 1) && ((*(byte *)(*(int *)(param_1 + 400) + 0xd) & 0x40) != 0)) &&
     (*(int *)(param_1 + 0x120) != 0)) {
    trap_UnlinkEntity(param_1);
  }
  tmp_i1 = G_DoAntiwarp(param_1);
  if (tmp_i1 != 0) {
    DoClientThinks(param_1);
  }
  return;
}

void G_AdjustSingleClientPosition_constprop_6(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  long double tmp_l10;
  int local_3c;
  
  tmp_i1 = g_unk_00abe908;
  if (((((param_1 != 0) && (*(int *)(param_1 + 0x194) != 0)) && (*(int *)(param_1 + 0x120) != 0)) &&
      ((tmp_i8 = *(int *)(param_1 + 400), tmp_i8 != 0 && (*(int *)(tmp_i8 + 3000) - 1U < 2)))) &&
     ((*(byte *)(tmp_i8 + 0xd) & 0x40) == 0)) {
    if ((g_unk_00abe908 == *(int *)(tmp_i8 + 0x1a28)) && (*(int *)(tmp_i8 + 4) == 3)) {
      if (GHIDRA_FIELD(g_realHead, 12, 4) == 0) {
        return;
      }
    }
    else {
      if (*(int *)(param_1 + 0x2c8) < 1) {
        return;
      }
      if (*(int *)(tmp_i8 + 4) != 0) {
        return;
      }
      if ((*(byte *)(tmp_i8 + 0x69) & 0x80) != 0) {
        return;
      }
    }
    if (g_unk_00abe908 < param_2) {
      param_2 = g_unk_00abe908;
    }
    tmp_i9 = *(int *)(tmp_i8 + 0x1058);
    tmp_i4 = tmp_i9;
    local_3c = tmp_i9;
    do {
      tmp_i7 = tmp_i4;
      tmp_i5 = tmp_i7;
      if (*(int *)(tmp_i8 + 0x1098 + tmp_i7 * 0x90) <= param_2) break;
      tmp_i4 = tmp_i7 + -1;
      if (tmp_i4 < 0) {
        tmp_i4 = 0x10;
      }
      tmp_i5 = tmp_i9;
      local_3c = tmp_i7;
    } while (tmp_i9 != tmp_i4);
    if (tmp_i5 != local_3c) {
      if (g_unk_00abe908 != *(int *)(tmp_i8 + 0x1a28)) {
        *(uint32_t *)(tmp_i8 + 0x1a04) = *(uint32_t *)(param_1 + 0x168);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a08) = *(uint32_t *)(param_1 + 0x16c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a0c) = *(uint32_t *)(param_1 + 0x170);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x19ec) = *(uint32_t *)(param_1 + 0x134);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x19f0) = *(uint32_t *)(param_1 + 0x138);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x19f4) = *(uint32_t *)(param_1 + 0x13c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x19f8) = *(uint32_t *)(param_1 + 0x140);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x19fc) = *(uint32_t *)(param_1 + 0x144);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a00) = *(uint32_t *)(param_1 + 0x148);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a1c) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xb0);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a20) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xb4);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a24) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xb8);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a10) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x68);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a18) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xc);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a14) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc);
        *(int *)(*(int *)(param_1 + 400) + 0x1a28) = tmp_i1;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a2c) = *(uint32_t *)(param_1 + 0x558);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a30) = *(uint32_t *)(param_1 + 0x55c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a34) = *(uint32_t *)(param_1 + 0x560);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a38) = *(uint32_t *)(param_1 + 0x578);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a3c) = *(uint32_t *)(param_1 + 0x564);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a40) = *(uint32_t *)(param_1 + 0x57c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a44) = *(uint32_t *)(param_1 + 0x580);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a48) = *(uint32_t *)(param_1 + 0x588);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a4c) = *(uint32_t *)(param_1 + 0x584);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a50) = *(uint32_t *)(param_1 + 0x58c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a54) = *(uint32_t *)(param_1 + 0x508);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a58) = *(uint32_t *)(param_1 + 0x50c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a5c) = *(uint32_t *)(param_1 + 0x510);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a60) = *(uint32_t *)(param_1 + 0x528);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a64) = *(uint32_t *)(param_1 + 0x514);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a68) = *(uint32_t *)(param_1 + 0x52c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a6c) = *(uint32_t *)(param_1 + 0x530);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a70) = *(uint32_t *)(param_1 + 0x538);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a74) = *(uint32_t *)(param_1 + 0x534);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a78) = *(uint32_t *)(param_1 + 0x53c);
        tmp_i8 = *(int *)(param_1 + 400);
        tmp_i9 = *(int *)(tmp_i8 + 0x1058);
      }
      if (tmp_i5 == tmp_i9) {
        local_3c = local_3c * 0x90;
        tmp_i1 = tmp_i8 + 0x1050 + local_3c;
        tmp_i9 = tmp_i8 + 0x1054 + local_3c;
        *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(tmp_i8 + 0x1074 + local_3c);
        tmp_i4 = tmp_i8 + 0x1058 + local_3c;
        *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(tmp_i8 + 0x1078 + local_3c);
        *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(tmp_i8 + 0x107c + local_3c);
        *(uint32_t *)(param_1 + 0x134) = *(uint32_t *)(tmp_i1 + 0xc);
        *(uint32_t *)(param_1 + 0x138) = *(uint32_t *)(tmp_i9 + 0xc);
        *(uint32_t *)(param_1 + 0x13c) = *(uint32_t *)(tmp_i4 + 0xc);
        *(uint32_t *)(param_1 + 0x140) = *(uint32_t *)(tmp_i1 + 0x18);
        *(uint32_t *)(param_1 + 0x144) = *(uint32_t *)(tmp_i9 + 0x18);
        *(uint32_t *)(param_1 + 0x148) = *(uint32_t *)(tmp_i4 + 0x18);
        *(uint32_t *)(tmp_i8 + 0xb0) = *(uint32_t *)(tmp_i8 + 0x108c + local_3c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xb4) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1090 + local_3c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xb8) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1094 + local_3c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x68) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1080 + local_3c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xc) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1088 + local_3c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1084 + local_3c);
        tmp_i9 = *(int *)(param_1 + 400);
        tmp_i1 = tmp_i9 + 0x1090 + local_3c;
        *(uint32_t *)(param_1 + 0x558) = *(uint32_t *)(tmp_i1 + 0xc);
        *(uint32_t *)(param_1 + 0x55c) = *(uint32_t *)(tmp_i1 + 0x10);
        *(uint32_t *)(param_1 + 0x560) = *(uint32_t *)(tmp_i1 + 0x14);
        *(uint32_t *)(param_1 + 0x578) = *(uint32_t *)(tmp_i1 + 0x18);
        tmp_i1 = tmp_i9 + 0x10a0 + local_3c;
        *(uint32_t *)(param_1 + 0x564) = *(uint32_t *)(tmp_i1 + 0xc);
        *(uint32_t *)(param_1 + 0x57c) = *(uint32_t *)(tmp_i1 + 0x10);
        *(uint32_t *)(param_1 + 0x580) = *(uint32_t *)(tmp_i1 + 0x14);
        tmp_i8 = tmp_i9 + 0x10b0 + local_3c;
        *(uint32_t *)(param_1 + 0x588) = *(uint32_t *)(tmp_i1 + 0x18);
        *(uint32_t *)(param_1 + 0x584) = *(uint32_t *)(tmp_i8 + 0xc);
        *(uint32_t *)(param_1 + 0x58c) = *(uint32_t *)(tmp_i8 + 0x10);
        *(uint32_t *)(param_1 + 0x508) = *(uint32_t *)(tmp_i8 + 0x14);
        *(uint32_t *)(param_1 + 0x50c) = *(uint32_t *)(tmp_i8 + 0x18);
        tmp_i1 = tmp_i9 + 0x10c0 + local_3c;
        tmp_i8 = tmp_i9 + 0x10d0 + local_3c;
        *(uint32_t *)(param_1 + 0x510) = *(uint32_t *)(tmp_i1 + 0xc);
        *(uint32_t *)(param_1 + 0x528) = *(uint32_t *)(tmp_i1 + 0x10);
        *(uint32_t *)(param_1 + 0x514) = *(uint32_t *)(tmp_i1 + 0x14);
        *(uint32_t *)(param_1 + 0x52c) = *(uint32_t *)(tmp_i1 + 0x18);
        *(uint32_t *)(param_1 + 0x530) = *(uint32_t *)(tmp_i8 + 0xc);
        *(uint32_t *)(param_1 + 0x538) = *(uint32_t *)(tmp_i8 + 0x10);
        *(uint32_t *)(param_1 + 0x534) = *(uint32_t *)(tmp_i8 + 0x14);
        *(uint32_t *)(param_1 + 0x53c) = *(uint32_t *)(tmp_i8 + 0x18);
        *(uint32_t *)(param_1 + 0x5a8) = *(uint32_t *)(tmp_i9 + local_3c + 0x1098);
      }
      else {
        tmp_i5 = tmp_i5 * 0x90;
        tmp_i6 = tmp_i5 + 0x1080;
        tmp_i7 = *(int *)(tmp_i8 + tmp_i6 + 0x18);
        local_3c = local_3c * 0x90;
        tmp_i1 = local_3c + 0x1080;
        tmp_i9 = tmp_i8 + 0x1060 + local_3c;
        tmp_i4 = tmp_i8 + 0x1060 + tmp_i5;
        tmp_f3 = (float)(param_2 - tmp_i7) / (float)(*(int *)(tmp_i1 + tmp_i8 + 0x18) - tmp_i7);
        *(float *)(param_1 + 0x168) =
             (*(float *)(tmp_i9 + 0x14) - *(float *)(tmp_i4 + 0x14)) * tmp_f3 +
             *(float *)(tmp_i4 + 0x14);
        *(float *)(param_1 + 0x16c) =
             (*(float *)(tmp_i9 + 0x18) - *(float *)(tmp_i4 + 0x18)) * tmp_f3 +
             *(float *)(tmp_i4 + 0x18);
        tmp_i7 = tmp_i8 + 0x1050 + local_3c;
        tmp_i2 = tmp_i8 + 0x1050 + tmp_i5;
        *(float *)(param_1 + 0x170) =
             (*(float *)(tmp_i9 + 0x1c) - *(float *)(tmp_i4 + 0x1c)) * tmp_f3 +
             *(float *)(tmp_i4 + 0x1c);
        *(float *)(param_1 + 0x134) =
             (*(float *)(tmp_i7 + 0xc) - *(float *)(tmp_i2 + 0xc)) * tmp_f3 + *(float *)(tmp_i2 + 0xc);
        *(float *)(param_1 + 0x138) =
             (*(float *)(tmp_i7 + 0x10) - *(float *)(tmp_i2 + 0x10)) * tmp_f3 +
             *(float *)(tmp_i2 + 0x10);
        *(float *)(param_1 + 0x13c) =
             (*(float *)(tmp_i7 + 0x14) - *(float *)(tmp_i2 + 0x14)) * tmp_f3 +
             *(float *)(tmp_i2 + 0x14);
        *(float *)(param_1 + 0x140) =
             (*(float *)(tmp_i7 + 0x18) - *(float *)(tmp_i2 + 0x18)) * tmp_f3 +
             *(float *)(tmp_i2 + 0x18);
        *(float *)(param_1 + 0x144) =
             (*(float *)(tmp_i7 + 0x1c) - *(float *)(tmp_i2 + 0x1c)) * tmp_f3 +
             *(float *)(tmp_i2 + 0x1c);
        *(float *)(param_1 + 0x148) =
             (*(float *)(tmp_i7 + 0x20) - *(float *)(tmp_i2 + 0x20)) * tmp_f3 +
             *(float *)(tmp_i2 + 0x20);
        tmp_l10 = (long double)
                 LerpAngle(*(uint32_t *)(tmp_i8 + tmp_i6 + 0xc),*(uint32_t *)(tmp_i1 + tmp_i8 + 0xc)
                           ,tmp_f3);
        *(float *)(tmp_i8 + 0xb0) = (float)tmp_l10;
        tmp_i8 = *(int *)(param_1 + 400);
        tmp_l10 = (long double)
                 LerpAngle(*(uint32_t *)(tmp_i8 + 0x1090 + tmp_i5),
                           *(uint32_t *)(tmp_i8 + 0x1090 + local_3c),tmp_f3);
        *(float *)(tmp_i8 + 0xb4) = (float)tmp_l10;
        tmp_i8 = *(int *)(param_1 + 400);
        tmp_l10 = (long double)
                 LerpAngle(*(uint32_t *)(tmp_i8 + 0x1094 + tmp_i5),
                           *(uint32_t *)(tmp_i8 + 0x1094 + local_3c),tmp_f3);
        *(float *)(tmp_i8 + 0xb8) = (float)tmp_l10;
        tmp_i8 = *(int *)(param_1 + 400);
        if (*(int *)(tmp_i8 + 0x18 + tmp_i1) - param_2 < param_2 - *(int *)(tmp_i8 + 0x18 + tmp_i6)) {
          *(uint32_t *)(tmp_i8 + 0x68) = *(uint32_t *)(tmp_i8 + 0x1080 + local_3c);
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xc) =
               *(uint32_t *)(*(int *)(param_1 + 400) + 0x1088 + local_3c);
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc) =
               *(uint32_t *)(*(int *)(param_1 + 400) + 0x1084 + local_3c);
          tmp_i4 = *(int *)(param_1 + 400);
          tmp_i8 = tmp_i4 + 0x1090 + local_3c;
          *(uint32_t *)(param_1 + 0x558) = *(uint32_t *)(tmp_i8 + 0xc);
          *(uint32_t *)(param_1 + 0x55c) = *(uint32_t *)(tmp_i8 + 0x10);
          *(uint32_t *)(param_1 + 0x560) = *(uint32_t *)(tmp_i8 + 0x14);
          *(uint32_t *)(param_1 + 0x578) = *(uint32_t *)(tmp_i8 + 0x18);
          tmp_i8 = tmp_i4 + 0x10a0 + local_3c;
          *(uint32_t *)(param_1 + 0x564) = *(uint32_t *)(tmp_i8 + 0xc);
          *(uint32_t *)(param_1 + 0x57c) = *(uint32_t *)(tmp_i8 + 0x10);
          *(uint32_t *)(param_1 + 0x580) = *(uint32_t *)(tmp_i8 + 0x14);
          tmp_i9 = tmp_i4 + 0x10b0 + local_3c;
          *(uint32_t *)(param_1 + 0x588) = *(uint32_t *)(tmp_i8 + 0x18);
          *(uint32_t *)(param_1 + 0x584) = *(uint32_t *)(tmp_i9 + 0xc);
          *(uint32_t *)(param_1 + 0x58c) = *(uint32_t *)(tmp_i9 + 0x10);
          *(uint32_t *)(param_1 + 0x508) = *(uint32_t *)(tmp_i9 + 0x14);
          *(uint32_t *)(param_1 + 0x50c) = *(uint32_t *)(tmp_i9 + 0x18);
          tmp_i8 = tmp_i4 + 0x10c0 + local_3c;
          *(uint32_t *)(param_1 + 0x510) = *(uint32_t *)(tmp_i8 + 0xc);
          *(uint32_t *)(param_1 + 0x528) = *(uint32_t *)(tmp_i8 + 0x10);
          *(uint32_t *)(param_1 + 0x514) = *(uint32_t *)(tmp_i8 + 0x14);
          *(uint32_t *)(param_1 + 0x52c) = *(uint32_t *)(tmp_i8 + 0x18);
          local_3c = tmp_i4 + 0x10d0 + local_3c;
          *(uint32_t *)(param_1 + 0x530) = *(uint32_t *)(local_3c + 0xc);
          *(uint32_t *)(param_1 + 0x538) = *(uint32_t *)(local_3c + 0x10);
          *(uint32_t *)(param_1 + 0x534) = *(uint32_t *)(local_3c + 0x14);
          *(uint32_t *)(param_1 + 0x53c) = *(uint32_t *)(local_3c + 0x18);
          *(uint32_t *)(param_1 + 0x5a8) = *(uint32_t *)(tmp_i4 + 0x18 + tmp_i1);
        }
        else {
          *(uint32_t *)(tmp_i8 + 0x68) = *(uint32_t *)(tmp_i8 + 0x1080 + tmp_i5);
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xc) =
               *(uint32_t *)(*(int *)(param_1 + 400) + 0x1088 + tmp_i5);
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc) =
               *(uint32_t *)(*(int *)(param_1 + 400) + 0x1084 + tmp_i5);
          tmp_i9 = *(int *)(param_1 + 400);
          tmp_i1 = tmp_i9 + 0x1090 + tmp_i5;
          *(uint32_t *)(param_1 + 0x558) = *(uint32_t *)(tmp_i1 + 0xc);
          *(uint32_t *)(param_1 + 0x55c) = *(uint32_t *)(tmp_i1 + 0x10);
          *(uint32_t *)(param_1 + 0x560) = *(uint32_t *)(tmp_i1 + 0x14);
          *(uint32_t *)(param_1 + 0x578) = *(uint32_t *)(tmp_i1 + 0x18);
          tmp_i1 = tmp_i9 + 0x10a0 + tmp_i5;
          *(uint32_t *)(param_1 + 0x564) = *(uint32_t *)(tmp_i1 + 0xc);
          *(uint32_t *)(param_1 + 0x57c) = *(uint32_t *)(tmp_i1 + 0x10);
          *(uint32_t *)(param_1 + 0x580) = *(uint32_t *)(tmp_i1 + 0x14);
          tmp_i8 = tmp_i9 + 0x10b0 + tmp_i5;
          *(uint32_t *)(param_1 + 0x588) = *(uint32_t *)(tmp_i1 + 0x18);
          *(uint32_t *)(param_1 + 0x584) = *(uint32_t *)(tmp_i8 + 0xc);
          *(uint32_t *)(param_1 + 0x58c) = *(uint32_t *)(tmp_i8 + 0x10);
          *(uint32_t *)(param_1 + 0x508) = *(uint32_t *)(tmp_i8 + 0x14);
          *(uint32_t *)(param_1 + 0x50c) = *(uint32_t *)(tmp_i8 + 0x18);
          tmp_i1 = tmp_i9 + 0x10c0 + tmp_i5;
          *(uint32_t *)(param_1 + 0x510) = *(uint32_t *)(tmp_i1 + 0xc);
          *(uint32_t *)(param_1 + 0x528) = *(uint32_t *)(tmp_i1 + 0x10);
          *(uint32_t *)(param_1 + 0x514) = *(uint32_t *)(tmp_i1 + 0x14);
          *(uint32_t *)(param_1 + 0x52c) = *(uint32_t *)(tmp_i1 + 0x18);
          tmp_i5 = tmp_i9 + 0x10d0 + tmp_i5;
          *(uint32_t *)(param_1 + 0x530) = *(uint32_t *)(tmp_i5 + 0xc);
          *(uint32_t *)(param_1 + 0x538) = *(uint32_t *)(tmp_i5 + 0x10);
          *(uint32_t *)(param_1 + 0x534) = *(uint32_t *)(tmp_i5 + 0x14);
          *(uint32_t *)(param_1 + 0x53c) = *(uint32_t *)(tmp_i5 + 0x18);
          *(uint32_t *)(param_1 + 0x5a8) = *(uint32_t *)(tmp_i9 + 0x18 + tmp_i6);
        }
      }
      trap_LinkEntity(param_1);
      return;
    }
  }
  return;
}

void DetectHitZone(int param_1,uint32_t *param_2,int param_3,uint32_t param_4,uint32_t param_5
                  )

{
  uint32_t *tmp_pu1;
  uint8_t local_44 [52];
  int local_10;
  
  *(uint32_t *)(param_1 + 0x5ec) = 0xffffffff;
  if (param_2[100] != 0) {
    *(uint32_t *)(param_1 + 0x5ec) = 2;
    if ((*(uint *)(param_3 + 4) & 0xfffffffd) == 0x28) {
      *(uint *)(param_1 + 0x5ec) = (uint)(*(uint *)(param_3 + 4) != 0x28) * 3;
    }
    else {
      trap_Trace(local_44,param_4,0,0,param_5,*param_2,0x6000001);
      tmp_pu1 = *(uint32_t **)(g_entities + local_10 * 0x600 + 0x218);
      if (((tmp_pu1 != (uint32_t *)0x0) && (param_2 == tmp_pu1)) && (tmp_pu1[100] != 0)) {
        if (*(int *)(g_entities + local_10 * 0x600 + 4) == 0x28) {
          *(uint32_t *)(param_1 + 0x5ec) = 0;
        }
        else if (*(int *)(g_entities + local_10 * 0x600 + 4) == 0x2a) {
          *(uint32_t *)(param_1 + 0x5ec) = 3;
        }
      }
    }
  }
  return;
}

int Trace_HitsPlayer(uint32_t param_1,int param_2,uint32_t param_3,uint32_t param_4,
                    uint32_t param_5,uint32_t *param_6)

{
  int tmp_i1;
  uint32_t local_c4;
  uint8_t local_c0 [4];
  uint8_t local_bc [172];
  uint32_t uStack_10;
  
  uStack_10 = 0x54008;
  if ((g_hitboxes[0xc] & 0x10) == 0) {
    if (param_2 == 0) {
      return -1;
    }
    if (*(int *)(param_2 + 400) == 0) {
      return -1;
    }
  }
  else {
    if (param_2 == 0) {
      return -1;
    }
    if (*(int *)(param_2 + 400) == 0) {
      return -1;
    }
    if (*(int *)(*(int *)(param_2 + 400) + 0x154) != 0) {
      *param_6 = 2;
      return (param_2 + -0x93e4a0 >> 9) * -0x55555555;
    }
  }
  tmp_i1 = *(int *)(param_2 + 0x5a8);
  if (*(int *)(param_2 + 0x5a8) == 0) {
    tmp_i1 = g_unk_00abe908;
  }
  mdx_gentity_to_grefEntity(param_2,local_bc,tmp_i1);
  tmp_i1 = mdx_shot_test(param_1,param_3,param_4,param_2,local_bc,&local_c4,param_5,local_c0);
  if (tmp_i1 != 0) {
    switch(local_c4) {
    default:
      goto _L57;
    case 1:
    case 2:
      *param_6 = 2;
      break;
    case 3:
    case 4:
      *param_6 = 1;
      break;
    case 5:
    case 6:
      *param_6 = 3;
      break;
    case 7:
      *param_6 = 0;
    }
    return (param_2 + -0x93e4a0 >> 9) * -0x55555555;
  }
_L57:
  return -1;
}

bool G_AntilagSafe(int param_1)
{
  int tmp_i1;
  bool tmp_b2;
  
  if (param_1 == 0) {
    return false;
  }
  tmp_b2 = false;
  if ((*(int *)(param_1 + 0x194) != 0) && (tmp_b2 = false, *(int *)(param_1 + 0x120) != 0)) {
    tmp_i1 = *(int *)(param_1 + 400);
    if (tmp_i1 == 0) {
      return false;
    }
    tmp_b2 = false;
    if ((*(int *)(tmp_i1 + 3000) - 1U < 2) && ((*(byte *)(tmp_i1 + 0xd) & 0x40) == 0)) {
      if ((*(int *)(tmp_i1 + 0x1a28) == g_unk_00abe908) && (*(int *)(tmp_i1 + 4) == 3)) {
        tmp_b2 = GHIDRA_FIELD(g_realHead, 12, 4) != 0;
      }
      else {
        tmp_b2 = false;
        if ((0 < *(int *)(param_1 + 0x2c8)) && (*(int *)(tmp_i1 + 4) == 0)) {
          tmp_b2 = (*(byte *)(tmp_i1 + 0x69) & 0x80) == 0;
        }
      }
    }
  }
  return tmp_b2;
}

int G_StoreClientPosition(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int local_14;
  
  tmp_i1 = g_unk_00abe908;
  if (((((param_1 != 0) && (*(int *)(param_1 + 0x194) != 0)) && (*(int *)(param_1 + 0x120) != 0)) &&
      ((tmp_i2 = *(int *)(param_1 + 400), tmp_i2 != 0 && (*(int *)(tmp_i2 + 3000) - 1U < 2)))) &&
     ((*(byte *)(tmp_i2 + 0xd) & 0x40) == 0)) {
    local_14 = g_unk_00abe908;
    if ((*(int *)(tmp_i2 + 0x1a28) == g_unk_00abe908) && (*(int *)(tmp_i2 + 4) == 3)) {
      if (GHIDRA_FIELD(g_realHead, 12, 4) != 0) {
LAB_000542e5:
        *(int *)(tmp_i2 + 0x1058) = *(int *)(tmp_i2 + 0x1058) + 1;
        tmp_i2 = *(int *)(param_1 + 400);
        tmp_i3 = *(int *)(tmp_i2 + 0x1058);
        if (0x10 < tmp_i3) {
          *(uint32_t *)(tmp_i2 + 0x1058) = 0;
          tmp_i2 = *(int *)(param_1 + 400);
          tmp_i3 = *(int *)(tmp_i2 + 0x1058);
        }
        tmp_i3 = tmp_i3 * 0x90;
        *(uint32_t *)(tmp_i2 + 0x105c + tmp_i3) = *(uint32_t *)(param_1 + 0x134);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i3 + 0x1054 + 0xc) =
             *(uint32_t *)(param_1 + 0x138);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i3 + 0x1058 + 0xc) =
             *(uint32_t *)(param_1 + 0x13c);
        *(uint32_t *)(tmp_i3 + *(int *)(param_1 + 400) + 0x1068) = *(uint32_t *)(param_1 + 0x140)
        ;
        *(uint32_t *)(tmp_i3 + 0x1054 + *(int *)(param_1 + 400) + 0x18) =
             *(uint32_t *)(param_1 + 0x144);
        *(uint32_t *)(tmp_i3 + 0x1058 + *(int *)(param_1 + 400) + 0x18) =
             *(uint32_t *)(param_1 + 0x148);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i3 + 0x1074) = *(uint32_t *)(param_1 + 0x18);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i3 + 0x1078) = *(uint32_t *)(param_1 + 0x1c);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i3 + 0x107c) = *(uint32_t *)(param_1 + 0x20);
        *(int *)(*(int *)(param_1 + 400) + tmp_i3 + 0x1080 + 0x18) = tmp_i1;
        *(uint32_t *)(tmp_i3 + 0x1080 + *(int *)(param_1 + 400) + 0xc) =
             *(uint32_t *)(param_1 + 0x3c);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i3 + 0x1090) = *(uint32_t *)(param_1 + 0x40);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i3 + 0x1094) = *(uint32_t *)(param_1 + 0x44);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i3 + 0x1080) = *(uint32_t *)(param_1 + 8);
        tmp_i2 = tmp_i3 + 0x1090;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1088 + tmp_i3) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xc);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1084 + tmp_i3) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0xc) = *(uint32_t *)(param_1 + 0x558);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0x10) = *(uint32_t *)(param_1 + 0x55c);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0x14) = *(uint32_t *)(param_1 + 0x560);
        *(uint32_t *)(tmp_i2 + *(int *)(param_1 + 400) + 0x18) = *(uint32_t *)(param_1 + 0x578);
        tmp_i2 = tmp_i3 + 0x10a0;
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0xc) = *(uint32_t *)(param_1 + 0x564);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0x10) = *(uint32_t *)(param_1 + 0x57c);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0x14) = *(uint32_t *)(param_1 + 0x580);
        *(uint32_t *)(tmp_i2 + *(int *)(param_1 + 400) + 0x18) = *(uint32_t *)(param_1 + 0x588);
        tmp_i2 = tmp_i3 + 0x10b0;
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0xc) = *(uint32_t *)(param_1 + 0x584);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0x10) = *(uint32_t *)(param_1 + 0x58c);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0x14) = *(uint32_t *)(param_1 + 0x508);
        *(uint32_t *)(tmp_i2 + *(int *)(param_1 + 400) + 0x18) = *(uint32_t *)(param_1 + 0x50c);
        tmp_i2 = tmp_i3 + 0x10c0;
        tmp_i3 = tmp_i3 + 0x10d0;
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0xc) = *(uint32_t *)(param_1 + 0x510);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0x10) = *(uint32_t *)(param_1 + 0x528);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i2 + 0x14) = *(uint32_t *)(param_1 + 0x514);
        *(uint32_t *)(tmp_i2 + *(int *)(param_1 + 400) + 0x18) = *(uint32_t *)(param_1 + 0x52c);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i3 + 0xc) = *(uint32_t *)(param_1 + 0x530);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i3 + 0x10) = *(uint32_t *)(param_1 + 0x538);
        *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i3 + 0x14) = *(uint32_t *)(param_1 + 0x534);
        *(uint32_t *)(tmp_i3 + *(int *)(param_1 + 400) + 0x18) = *(uint32_t *)(param_1 + 0x53c);
        return tmp_i1;
      }
    }
    else if ((0 < *(int *)(param_1 + 0x2c8)) &&
            ((*(int *)(tmp_i2 + 4) == 0 && ((*(byte *)(tmp_i2 + 0x69) & 0x80) == 0))))
    goto LAB_000542e5;
  }
  return local_14;
}

void G_AdjustSingleClientPosition(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  float tmp_f4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  long double tmp_l12;
  int local_844;
  int local_840;
  uint8_t local_81c [2056];
  uint32_t uStack_14;
  
  tmp_i11 = g_unk_00abe908;
  uStack_14 = 0x545d9;
  if (((((param_1 != 0) && (*(int *)(param_1 + 0x194) != 0)) && (*(int *)(param_1 + 0x120) != 0)) &&
      ((tmp_i10 = *(int *)(param_1 + 400), tmp_i10 != 0 && (*(int *)(tmp_i10 + 3000) - 1U < 2)))) &&
     ((*(byte *)(tmp_i10 + 0xd) & 0x40) == 0)) {
    if ((g_unk_00abe908 == *(int *)(tmp_i10 + 0x1a28)) && (*(int *)(tmp_i10 + 4) == 3)) {
      if (GHIDRA_FIELD(g_realHead, 12, 4) == 0) {
        return;
      }
    }
    else {
      if (*(int *)(param_1 + 0x2c8) < 1) {
        return;
      }
      if (*(int *)(tmp_i10 + 4) != 0) {
        return;
      }
      if ((*(byte *)(tmp_i10 + 0x69) & 0x80) != 0) {
        return;
      }
    }
    tmp_i9 = *(int *)(tmp_i10 + 0x1058);
    tmp_i5 = tmp_i9;
    local_844 = tmp_i9;
    tmp_i6 = g_unk_00abe908;
    if (param_2 <= g_unk_00abe908) {
      tmp_i6 = param_2;
    }
    do {
      local_840 = tmp_i5;
      if (*(int *)(tmp_i10 + 0x1098 + local_840 * 0x90) <= tmp_i6) break;
      tmp_i5 = local_840 + -1;
      if (tmp_i5 < 0) {
        tmp_i5 = 0x10;
      }
      local_844 = local_840;
      local_840 = tmp_i9;
    } while (tmp_i5 != tmp_i9);
    if (local_840 != local_844) {
      if (g_unk_00abe908 != *(int *)(tmp_i10 + 0x1a28)) {
        *(uint32_t *)(tmp_i10 + 0x1a04) = *(uint32_t *)(param_1 + 0x168);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a08) = *(uint32_t *)(param_1 + 0x16c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a0c) = *(uint32_t *)(param_1 + 0x170);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x19ec) = *(uint32_t *)(param_1 + 0x134);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x19f0) = *(uint32_t *)(param_1 + 0x138);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x19f4) = *(uint32_t *)(param_1 + 0x13c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x19f8) = *(uint32_t *)(param_1 + 0x140);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x19fc) = *(uint32_t *)(param_1 + 0x144);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a00) = *(uint32_t *)(param_1 + 0x148);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a1c) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xb0);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a20) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xb4);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a24) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xb8);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a10) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x68);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a18) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xc);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a14) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc);
        *(int *)(*(int *)(param_1 + 400) + 0x1a28) = tmp_i11;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a2c) = *(uint32_t *)(param_1 + 0x558);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a30) = *(uint32_t *)(param_1 + 0x55c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a34) = *(uint32_t *)(param_1 + 0x560);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a38) = *(uint32_t *)(param_1 + 0x578);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a3c) = *(uint32_t *)(param_1 + 0x564);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a40) = *(uint32_t *)(param_1 + 0x57c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a44) = *(uint32_t *)(param_1 + 0x580);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a48) = *(uint32_t *)(param_1 + 0x588);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a4c) = *(uint32_t *)(param_1 + 0x584);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a50) = *(uint32_t *)(param_1 + 0x58c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a54) = *(uint32_t *)(param_1 + 0x508);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a58) = *(uint32_t *)(param_1 + 0x50c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a5c) = *(uint32_t *)(param_1 + 0x510);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a60) = *(uint32_t *)(param_1 + 0x528);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a64) = *(uint32_t *)(param_1 + 0x514);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a68) = *(uint32_t *)(param_1 + 0x52c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a6c) = *(uint32_t *)(param_1 + 0x530);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a70) = *(uint32_t *)(param_1 + 0x538);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a74) = *(uint32_t *)(param_1 + 0x534);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a78) = *(uint32_t *)(param_1 + 0x53c);
        tmp_i10 = *(int *)(param_1 + 400);
        tmp_i9 = *(int *)(tmp_i10 + 0x1058);
      }
      if (local_840 == tmp_i9) {
        local_844 = local_844 * 0x90;
        tmp_i11 = tmp_i10 + 0x1050 + local_844;
        tmp_i9 = tmp_i10 + 0x1054 + local_844;
        *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(tmp_i10 + 0x1074 + local_844);
        tmp_i5 = tmp_i10 + 0x1058 + local_844;
        *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(tmp_i10 + 0x1078 + local_844);
        *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(tmp_i10 + 0x107c + local_844);
        *(uint32_t *)(param_1 + 0x134) = *(uint32_t *)(tmp_i11 + 0xc);
        *(uint32_t *)(param_1 + 0x138) = *(uint32_t *)(tmp_i9 + 0xc);
        *(uint32_t *)(param_1 + 0x13c) = *(uint32_t *)(tmp_i5 + 0xc);
        *(uint32_t *)(param_1 + 0x140) = *(uint32_t *)(tmp_i11 + 0x18);
        *(uint32_t *)(param_1 + 0x144) = *(uint32_t *)(tmp_i9 + 0x18);
        *(uint32_t *)(param_1 + 0x148) = *(uint32_t *)(tmp_i5 + 0x18);
        *(uint32_t *)(tmp_i10 + 0xb0) = *(uint32_t *)(tmp_i10 + 0x108c + local_844);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xb4) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1090 + local_844);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xb8) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1094 + local_844);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x68) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1080 + local_844);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xc) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1088 + local_844);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1084 + local_844);
        tmp_i9 = *(int *)(param_1 + 400);
        tmp_i11 = tmp_i9 + 0x1090 + local_844;
        *(uint32_t *)(param_1 + 0x558) = *(uint32_t *)(tmp_i11 + 0xc);
        *(uint32_t *)(param_1 + 0x55c) = *(uint32_t *)(tmp_i11 + 0x10);
        *(uint32_t *)(param_1 + 0x560) = *(uint32_t *)(tmp_i11 + 0x14);
        *(uint32_t *)(param_1 + 0x578) = *(uint32_t *)(tmp_i11 + 0x18);
        tmp_i11 = tmp_i9 + 0x10a0 + local_844;
        *(uint32_t *)(param_1 + 0x564) = *(uint32_t *)(tmp_i11 + 0xc);
        *(uint32_t *)(param_1 + 0x57c) = *(uint32_t *)(tmp_i11 + 0x10);
        *(uint32_t *)(param_1 + 0x580) = *(uint32_t *)(tmp_i11 + 0x14);
        tmp_i10 = tmp_i9 + 0x10b0 + local_844;
        *(uint32_t *)(param_1 + 0x588) = *(uint32_t *)(tmp_i11 + 0x18);
        *(uint32_t *)(param_1 + 0x584) = *(uint32_t *)(tmp_i10 + 0xc);
        *(uint32_t *)(param_1 + 0x58c) = *(uint32_t *)(tmp_i10 + 0x10);
        *(uint32_t *)(param_1 + 0x508) = *(uint32_t *)(tmp_i10 + 0x14);
        *(uint32_t *)(param_1 + 0x50c) = *(uint32_t *)(tmp_i10 + 0x18);
        tmp_i11 = tmp_i9 + 0x10c0 + local_844;
        tmp_i10 = tmp_i9 + 0x10d0 + local_844;
        *(uint32_t *)(param_1 + 0x510) = *(uint32_t *)(tmp_i11 + 0xc);
        *(uint32_t *)(param_1 + 0x528) = *(uint32_t *)(tmp_i11 + 0x10);
        *(uint32_t *)(param_1 + 0x514) = *(uint32_t *)(tmp_i11 + 0x14);
        *(uint32_t *)(param_1 + 0x52c) = *(uint32_t *)(tmp_i11 + 0x18);
        *(uint32_t *)(param_1 + 0x530) = *(uint32_t *)(tmp_i10 + 0xc);
        *(uint32_t *)(param_1 + 0x538) = *(uint32_t *)(tmp_i10 + 0x10);
        *(uint32_t *)(param_1 + 0x534) = *(uint32_t *)(tmp_i10 + 0x14);
        *(uint32_t *)(param_1 + 0x53c) = *(uint32_t *)(tmp_i10 + 0x18);
        *(uint32_t *)(param_1 + 0x5a8) = *(uint32_t *)(tmp_i9 + local_844 + 0x1098);
      }
      else {
        tmp_i7 = local_840 * 0x90;
        tmp_i11 = tmp_i7 + 0x1080;
        tmp_i3 = *(int *)(tmp_i10 + tmp_i11 + 0x18);
        tmp_i8 = local_844 * 0x90;
        tmp_i9 = tmp_i8 + 0x1080;
        tmp_i5 = tmp_i10 + 0x1060 + tmp_i8;
        tmp_i1 = tmp_i10 + 0x1060 + tmp_i7;
        tmp_i2 = tmp_i10 + 0x1050 + tmp_i7;
        tmp_f4 = (float)(tmp_i6 - tmp_i3) / (float)(*(int *)(tmp_i10 + tmp_i9 + 0x18) - tmp_i3);
        *(float *)(param_1 + 0x168) =
             (*(float *)(tmp_i5 + 0x14) - *(float *)(tmp_i1 + 0x14)) * tmp_f4 +
             *(float *)(tmp_i1 + 0x14);
        *(float *)(param_1 + 0x16c) =
             (*(float *)(tmp_i5 + 0x18) - *(float *)(tmp_i1 + 0x18)) * tmp_f4 +
             *(float *)(tmp_i1 + 0x18);
        tmp_i3 = tmp_i10 + 0x1050 + tmp_i8;
        *(float *)(param_1 + 0x170) =
             (*(float *)(tmp_i5 + 0x1c) - *(float *)(tmp_i1 + 0x1c)) * tmp_f4 +
             *(float *)(tmp_i1 + 0x1c);
        *(float *)(param_1 + 0x134) =
             (*(float *)(tmp_i3 + 0xc) - *(float *)(tmp_i2 + 0xc)) * tmp_f4 + *(float *)(tmp_i2 + 0xc);
        *(float *)(param_1 + 0x138) =
             (*(float *)(tmp_i3 + 0x10) - *(float *)(tmp_i2 + 0x10)) * tmp_f4 +
             *(float *)(tmp_i2 + 0x10);
        *(float *)(param_1 + 0x13c) =
             (*(float *)(tmp_i3 + 0x14) - *(float *)(tmp_i2 + 0x14)) * tmp_f4 +
             *(float *)(tmp_i2 + 0x14);
        *(float *)(param_1 + 0x140) =
             (*(float *)(tmp_i3 + 0x18) - *(float *)(tmp_i2 + 0x18)) * tmp_f4 +
             *(float *)(tmp_i2 + 0x18);
        *(float *)(param_1 + 0x144) =
             (*(float *)(tmp_i3 + 0x1c) - *(float *)(tmp_i2 + 0x1c)) * tmp_f4 +
             *(float *)(tmp_i2 + 0x1c);
        *(float *)(param_1 + 0x148) =
             (*(float *)(tmp_i3 + 0x20) - *(float *)(tmp_i2 + 0x20)) * tmp_f4 +
             *(float *)(tmp_i2 + 0x20);
        tmp_l12 = (long double)
                 LerpAngle(*(uint32_t *)(tmp_i10 + tmp_i11 + 0xc),
                           *(uint32_t *)(tmp_i10 + tmp_i9 + 0xc),tmp_f4);
        *(float *)(tmp_i10 + 0xb0) = (float)tmp_l12;
        tmp_i10 = *(int *)(param_1 + 400);
        tmp_l12 = (long double)
                 LerpAngle(*(uint32_t *)(tmp_i10 + 0x1090 + tmp_i7),
                           *(uint32_t *)(tmp_i10 + 0x1090 + tmp_i8),tmp_f4);
        *(float *)(tmp_i10 + 0xb4) = (float)tmp_l12;
        tmp_i10 = *(int *)(param_1 + 400);
        tmp_l12 = (long double)
                 LerpAngle(*(uint32_t *)(tmp_i10 + 0x1094 + tmp_i7),
                           *(uint32_t *)(tmp_i10 + 0x1094 + tmp_i8),tmp_f4);
        *(float *)(tmp_i10 + 0xb8) = (float)tmp_l12;
        tmp_i10 = *(int *)(param_1 + 400);
        if (*(int *)(tmp_i10 + 0x18 + tmp_i9) - tmp_i6 < tmp_i6 - *(int *)(tmp_i10 + 0x18 + tmp_i11)) {
          *(uint32_t *)(tmp_i10 + 0x68) = *(uint32_t *)(tmp_i10 + 0x1080 + tmp_i8);
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xc) =
               *(uint32_t *)(*(int *)(param_1 + 400) + 0x1088 + tmp_i8);
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc) =
               *(uint32_t *)(*(int *)(param_1 + 400) + 0x1084 + tmp_i8);
          tmp_i5 = *(int *)(param_1 + 400);
          tmp_i11 = tmp_i5 + 0x1090 + tmp_i8;
          *(uint32_t *)(param_1 + 0x558) = *(uint32_t *)(tmp_i11 + 0xc);
          *(uint32_t *)(param_1 + 0x55c) = *(uint32_t *)(tmp_i11 + 0x10);
          *(uint32_t *)(param_1 + 0x560) = *(uint32_t *)(tmp_i11 + 0x14);
          *(uint32_t *)(param_1 + 0x578) = *(uint32_t *)(tmp_i11 + 0x18);
          tmp_i11 = tmp_i5 + 0x10a0 + tmp_i8;
          *(uint32_t *)(param_1 + 0x564) = *(uint32_t *)(tmp_i11 + 0xc);
          *(uint32_t *)(param_1 + 0x57c) = *(uint32_t *)(tmp_i11 + 0x10);
          *(uint32_t *)(param_1 + 0x580) = *(uint32_t *)(tmp_i11 + 0x14);
          tmp_i10 = tmp_i5 + 0x10b0 + tmp_i8;
          *(uint32_t *)(param_1 + 0x588) = *(uint32_t *)(tmp_i11 + 0x18);
          *(uint32_t *)(param_1 + 0x584) = *(uint32_t *)(tmp_i10 + 0xc);
          *(uint32_t *)(param_1 + 0x58c) = *(uint32_t *)(tmp_i10 + 0x10);
          *(uint32_t *)(param_1 + 0x508) = *(uint32_t *)(tmp_i10 + 0x14);
          *(uint32_t *)(param_1 + 0x50c) = *(uint32_t *)(tmp_i10 + 0x18);
          tmp_i11 = tmp_i5 + 0x10c0 + tmp_i8;
          *(uint32_t *)(param_1 + 0x510) = *(uint32_t *)(tmp_i11 + 0xc);
          *(uint32_t *)(param_1 + 0x528) = *(uint32_t *)(tmp_i11 + 0x10);
          *(uint32_t *)(param_1 + 0x514) = *(uint32_t *)(tmp_i11 + 0x14);
          *(uint32_t *)(param_1 + 0x52c) = *(uint32_t *)(tmp_i11 + 0x18);
          tmp_i8 = tmp_i5 + 0x10d0 + tmp_i8;
          *(uint32_t *)(param_1 + 0x530) = *(uint32_t *)(tmp_i8 + 0xc);
          *(uint32_t *)(param_1 + 0x538) = *(uint32_t *)(tmp_i8 + 0x10);
          *(uint32_t *)(param_1 + 0x534) = *(uint32_t *)(tmp_i8 + 0x14);
          *(uint32_t *)(param_1 + 0x53c) = *(uint32_t *)(tmp_i8 + 0x18);
          *(uint32_t *)(param_1 + 0x5a8) = *(uint32_t *)(tmp_i5 + 0x18 + tmp_i9);
        }
        else {
          *(uint32_t *)(tmp_i10 + 0x68) = *(uint32_t *)(tmp_i10 + 0x1080 + tmp_i7);
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xc) =
               *(uint32_t *)(*(int *)(param_1 + 400) + 0x1088 + tmp_i7);
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc) =
               *(uint32_t *)(*(int *)(param_1 + 400) + 0x1084 + tmp_i7);
          tmp_i5 = *(int *)(param_1 + 400);
          tmp_i10 = tmp_i5 + 0x1090 + tmp_i7;
          *(uint32_t *)(param_1 + 0x558) = *(uint32_t *)(tmp_i10 + 0xc);
          *(uint32_t *)(param_1 + 0x55c) = *(uint32_t *)(tmp_i10 + 0x10);
          *(uint32_t *)(param_1 + 0x560) = *(uint32_t *)(tmp_i10 + 0x14);
          *(uint32_t *)(param_1 + 0x578) = *(uint32_t *)(tmp_i10 + 0x18);
          tmp_i10 = tmp_i5 + 0x10a0 + tmp_i7;
          *(uint32_t *)(param_1 + 0x564) = *(uint32_t *)(tmp_i10 + 0xc);
          *(uint32_t *)(param_1 + 0x57c) = *(uint32_t *)(tmp_i10 + 0x10);
          *(uint32_t *)(param_1 + 0x580) = *(uint32_t *)(tmp_i10 + 0x14);
          tmp_i9 = tmp_i5 + 0x10b0 + tmp_i7;
          *(uint32_t *)(param_1 + 0x588) = *(uint32_t *)(tmp_i10 + 0x18);
          *(uint32_t *)(param_1 + 0x584) = *(uint32_t *)(tmp_i9 + 0xc);
          *(uint32_t *)(param_1 + 0x58c) = *(uint32_t *)(tmp_i9 + 0x10);
          *(uint32_t *)(param_1 + 0x508) = *(uint32_t *)(tmp_i9 + 0x14);
          *(uint32_t *)(param_1 + 0x50c) = *(uint32_t *)(tmp_i9 + 0x18);
          tmp_i10 = tmp_i5 + 0x10c0 + tmp_i7;
          *(uint32_t *)(param_1 + 0x510) = *(uint32_t *)(tmp_i10 + 0xc);
          *(uint32_t *)(param_1 + 0x528) = *(uint32_t *)(tmp_i10 + 0x10);
          *(uint32_t *)(param_1 + 0x514) = *(uint32_t *)(tmp_i10 + 0x14);
          *(uint32_t *)(param_1 + 0x52c) = *(uint32_t *)(tmp_i10 + 0x18);
          tmp_i7 = tmp_i5 + 0x10d0 + tmp_i7;
          *(uint32_t *)(param_1 + 0x530) = *(uint32_t *)(tmp_i7 + 0xc);
          *(uint32_t *)(param_1 + 0x538) = *(uint32_t *)(tmp_i7 + 0x10);
          *(uint32_t *)(param_1 + 0x534) = *(uint32_t *)(tmp_i7 + 0x14);
          *(uint32_t *)(param_1 + 0x53c) = *(uint32_t *)(tmp_i7 + 0x18);
          *(uint32_t *)(param_1 + 0x5a8) = *(uint32_t *)(tmp_i5 + 0x18 + tmp_i11);
        }
        if ((param_3 != 0) && (*(int *)(param_3 + 400) != 0)) {
          tmp_i11 = *(int *)(*(int *)(param_3 + 400) + 0x5388) + g_unk_00abe908;
          local_844 = local_844 * 0x90;
          local_840 = local_840 * 0x90;
          Com_sprintf(local_81c,0x800,
                      "print \"^1Rec: time: %d, j: %d, k: %d, origin: %0.2f %0.2f %0.2f\n^2frac: %0.4f, origin1: %0.2f %0.2f %0.2f, origin2: %0.2f %0.2f %0.2f\n^7level.time: %d, est time: %d, level.time delta: %d, est real ping: %d\n\""
                      ,tmp_i6,*(uint32_t *)(tmp_i5 + 0x1098 + local_840),
                      *(uint32_t *)(tmp_i5 + 0x1098 + local_844),
                      (double)*(float *)(param_1 + 0x168),(double)*(float *)(param_1 + 0x16c),
                      (double)*(float *)(param_1 + 0x170),(double)tmp_f4,
                      (double)*(float *)(tmp_i5 + 0x1074 + local_840),
                      (double)*(float *)(tmp_i5 + 0x1078 + local_840),
                      (double)*(float *)(tmp_i5 + 0x107c + local_840),
                      (double)*(float *)(tmp_i5 + 0x1074 + local_844),
                      (double)*(float *)(tmp_i5 + 0x1078 + local_844),
                      (double)*(float *)(tmp_i5 + 0x107c + local_844),g_unk_00abe908,tmp_i11,
                      g_unk_00abe908 - tmp_i6,tmp_i11 - tmp_i6);
          trap_SendServerCommand((param_3 + -0x93e4a0 >> 9) * -0x55555555,local_81c);
        }
      }
      trap_LinkEntity(param_1);
      return;
    }
  }
  return;
}

void G_ReAdjustSingleClientPosition(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  if ((((param_1 != 0) && (*(int *)(param_1 + 0x194) != 0)) && (*(int *)(param_1 + 0x120) != 0)) &&
     (((tmp_i2 = *(int *)(param_1 + 400), tmp_i2 != 0 && (*(int *)(tmp_i2 + 3000) - 1U < 2)) &&
      ((*(byte *)(tmp_i2 + 0xd) & 0x40) == 0)))) {
    if ((*(int *)(tmp_i2 + 0x1a28) == g_unk_00abe908) && (*(int *)(tmp_i2 + 4) == 3)) {
      if (GHIDRA_FIELD(g_realHead, 12, 4) != 0) {
LAB_00055246:
        *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(tmp_i2 + 0x1a04);
        *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(tmp_i2 + 0x1a08);
        *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(tmp_i2 + 0x1a0c);
        *(uint32_t *)(param_1 + 0x134) = *(uint32_t *)(tmp_i2 + 0x19ec);
        *(uint32_t *)(param_1 + 0x138) = *(uint32_t *)(tmp_i2 + 0x19f0);
        *(uint32_t *)(param_1 + 0x13c) = *(uint32_t *)(tmp_i2 + 0x19f4);
        *(uint32_t *)(param_1 + 0x140) = *(uint32_t *)(tmp_i2 + 0x19f8);
        *(uint32_t *)(param_1 + 0x144) = *(uint32_t *)(tmp_i2 + 0x19fc);
        *(uint32_t *)(param_1 + 0x148) = *(uint32_t *)(tmp_i2 + 0x1a00);
        *(uint32_t *)(tmp_i2 + 0xb0) = *(uint32_t *)(tmp_i2 + 0x1a1c);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xb4) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a20);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xb8) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a24);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x68) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a10);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xc) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a18);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc) =
             *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a14);
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x1a28) = 0;
        tmp_i2 = *(int *)(param_1 + 400);
        *(uint32_t *)(param_1 + 0x558) = *(uint32_t *)(tmp_i2 + 0x1a2c);
        *(uint32_t *)(param_1 + 0x55c) = *(uint32_t *)(tmp_i2 + 0x1a30);
        *(uint32_t *)(param_1 + 0x560) = *(uint32_t *)(tmp_i2 + 0x1a34);
        *(uint32_t *)(param_1 + 0x578) = *(uint32_t *)(tmp_i2 + 0x1a38);
        *(uint32_t *)(param_1 + 0x564) = *(uint32_t *)(tmp_i2 + 0x1a3c);
        *(uint32_t *)(param_1 + 0x57c) = *(uint32_t *)(tmp_i2 + 0x1a40);
        *(uint32_t *)(param_1 + 0x580) = *(uint32_t *)(tmp_i2 + 0x1a44);
        *(uint32_t *)(param_1 + 0x588) = *(uint32_t *)(tmp_i2 + 0x1a48);
        *(uint32_t *)(param_1 + 0x584) = *(uint32_t *)(tmp_i2 + 0x1a4c);
        *(uint32_t *)(param_1 + 0x58c) = *(uint32_t *)(tmp_i2 + 0x1a50);
        *(uint32_t *)(param_1 + 0x508) = *(uint32_t *)(tmp_i2 + 0x1a54);
        *(uint32_t *)(param_1 + 0x50c) = *(uint32_t *)(tmp_i2 + 0x1a58);
        *(uint32_t *)(param_1 + 0x510) = *(uint32_t *)(tmp_i2 + 0x1a5c);
        *(uint32_t *)(param_1 + 0x528) = *(uint32_t *)(tmp_i2 + 0x1a60);
        *(uint32_t *)(param_1 + 0x514) = *(uint32_t *)(tmp_i2 + 0x1a64);
        *(uint32_t *)(param_1 + 0x52c) = *(uint32_t *)(tmp_i2 + 0x1a68);
        *(uint32_t *)(param_1 + 0x530) = *(uint32_t *)(tmp_i2 + 0x1a6c);
        tmp_u1 = *(uint32_t *)(tmp_i2 + 0x1a70);
        *(uint32_t *)(param_1 + 0x5a8) = 0;
        *(uint32_t *)(param_1 + 0x538) = tmp_u1;
        trap_LinkEntity(param_1);
        return;
      }
    }
    else if ((0 < *(int *)(param_1 + 0x2c8)) &&
            (((*(int *)(tmp_i2 + 4) == 0 && ((*(byte *)(tmp_i2 + 0x69) & 0x80) == 0)) &&
             (*(int *)(tmp_i2 + 0x1a28) == g_unk_00abe908)))) goto LAB_00055246;
  }
  return;
}

void G_AdjustClientPositions(uint8_t *param_1,uint32_t param_2,int param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  int tmp_i6;
  
  if (0 < g_unk_00abe938) {
    tmp_i6 = 0;
    tmp_i5 = g_unk_00abe938;
    do {
      while( true ) {
        tmp_i3 = (&g_unk_00abe944)[tmp_i6] * 0x600;
        tmp_pu4 = g_entities + tmp_i3;
        if (tmp_pu4 != param_1) break;
LAB_0005547f:
        tmp_i6 = tmp_i6 + 1;
        if (tmp_i5 <= tmp_i6) {
          return;
        }
      }
      if (param_3 != 0) {
        G_AdjustSingleClientPosition_constprop_6();
        tmp_i5 = g_unk_00abe938;
        goto LAB_0005547f;
      }
      if ((((tmp_pu4 == (uint8_t *)0x0) || (*(int *)(g_entities + tmp_i3 + 0x194) == 0)) ||
          (*(int *)(g_entities + tmp_i3 + 0x120) == 0)) ||
         (((tmp_i2 = *(int *)(g_entities + tmp_i3 + 400), tmp_i2 == 0 ||
           (1 < *(int *)(tmp_i2 + 3000) - 1U)) || ((*(byte *)(tmp_i2 + 0xd) & 0x40) != 0))))
      goto LAB_0005547f;
      if ((*(int *)(tmp_i2 + 0x1a28) != g_unk_00abe908) || (*(int *)(tmp_i2 + 4) != 3)) {
        if ((0 < *(int *)(g_entities + tmp_i3 + 0x2c8)) &&
           (((*(int *)(tmp_i2 + 4) == 0 && ((*(byte *)(tmp_i2 + 0x69) & 0x80) == 0)) &&
            (*(int *)(tmp_i2 + 0x1a28) == g_unk_00abe908)))) goto LAB_00055533;
        goto LAB_0005547f;
      }
      if (GHIDRA_FIELD(g_realHead, 12, 4) == 0) goto LAB_0005547f;
LAB_00055533:
      tmp_i6 = tmp_i6 + 1;
      *(uint32_t *)(g_entities + tmp_i3 + 0x168) = *(uint32_t *)(tmp_i2 + 0x1a04);
      *(uint32_t *)(g_entities + tmp_i3 + 0x16c) = *(uint32_t *)(tmp_i2 + 0x1a08);
      *(uint32_t *)(g_entities + tmp_i3 + 0x170) = *(uint32_t *)(tmp_i2 + 0x1a0c);
      *(uint32_t *)(g_entities + tmp_i3 + 0x134) = *(uint32_t *)(tmp_i2 + 0x19ec);
      *(uint32_t *)(g_entities + tmp_i3 + 0x138) = *(uint32_t *)(tmp_i2 + 0x19f0);
      *(uint32_t *)(g_entities + tmp_i3 + 0x13c) = *(uint32_t *)(tmp_i2 + 0x19f4);
      *(uint32_t *)(g_entities + tmp_i3 + 0x140) = *(uint32_t *)(tmp_i2 + 0x19f8);
      *(uint32_t *)(g_entities + tmp_i3 + 0x144) = *(uint32_t *)(tmp_i2 + 0x19fc);
      *(uint32_t *)(g_entities + tmp_i3 + 0x148) = *(uint32_t *)(tmp_i2 + 0x1a00);
      *(uint32_t *)(tmp_i2 + 0xb0) = *(uint32_t *)(tmp_i2 + 0x1a1c);
      *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb4) =
           *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a20);
      *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb8) =
           *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a24);
      *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x68) =
           *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a10);
      *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xc) =
           *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a18);
      *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xbc) =
           *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a14);
      *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a28) = 0;
      tmp_i5 = *(int *)(g_entities + tmp_i3 + 400);
      *(uint32_t *)(g_entities + tmp_i3 + 0x558) = *(uint32_t *)(tmp_i5 + 0x1a2c);
      *(uint32_t *)(g_entities + tmp_i3 + 0x55c) = *(uint32_t *)(tmp_i5 + 0x1a30);
      *(uint32_t *)(g_entities + tmp_i3 + 0x560) = *(uint32_t *)(tmp_i5 + 0x1a34);
      *(uint32_t *)(g_entities + tmp_i3 + 0x578) = *(uint32_t *)(tmp_i5 + 0x1a38);
      *(uint32_t *)(g_entities + tmp_i3 + 0x564) = *(uint32_t *)(tmp_i5 + 0x1a3c);
      *(uint32_t *)(g_entities + tmp_i3 + 0x57c) = *(uint32_t *)(tmp_i5 + 0x1a40);
      *(uint32_t *)(g_entities + tmp_i3 + 0x580) = *(uint32_t *)(tmp_i5 + 0x1a44);
      *(uint32_t *)(g_entities + tmp_i3 + 0x588) = *(uint32_t *)(tmp_i5 + 0x1a48);
      *(uint32_t *)(g_entities + tmp_i3 + 0x584) = *(uint32_t *)(tmp_i5 + 0x1a4c);
      *(uint32_t *)(g_entities + tmp_i3 + 0x58c) = *(uint32_t *)(tmp_i5 + 0x1a50);
      *(uint32_t *)(g_entities + tmp_i3 + 0x508) = *(uint32_t *)(tmp_i5 + 0x1a54);
      *(uint32_t *)(g_entities + tmp_i3 + 0x50c) = *(uint32_t *)(tmp_i5 + 0x1a58);
      *(uint32_t *)(g_entities + tmp_i3 + 0x510) = *(uint32_t *)(tmp_i5 + 0x1a5c);
      *(uint32_t *)(g_entities + tmp_i3 + 0x528) = *(uint32_t *)(tmp_i5 + 0x1a60);
      *(uint32_t *)(g_entities + tmp_i3 + 0x514) = *(uint32_t *)(tmp_i5 + 0x1a64);
      *(uint32_t *)(g_entities + tmp_i3 + 0x52c) = *(uint32_t *)(tmp_i5 + 0x1a68);
      *(uint32_t *)(g_entities + tmp_i3 + 0x530) = *(uint32_t *)(tmp_i5 + 0x1a6c);
      tmp_u1 = *(uint32_t *)(tmp_i5 + 0x1a70);
      *(uint32_t *)(g_entities + tmp_i3 + 0x5a8) = 0;
      *(uint32_t *)(g_entities + tmp_i3 + 0x538) = tmp_u1;
      trap_LinkEntity(tmp_pu4);
      tmp_i5 = g_unk_00abe938;
    } while (tmp_i6 < g_unk_00abe938);
  }
  return;
}

void G_ResetMarkers(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint32_t local_14;
  
  tmp_u2 = *(uint *)(*(int *)(param_1 + 400) + 0x68);
  *(uint32_t *)(*(int *)(param_1 + 400) + 0x1058) = 0x10;
  local_14 = 0x10;
  tmp_u3 = tmp_u2 & 0xffff7fff;
  if ((tmp_u2 & 0x8000) == 0) {
    tmp_u3 = tmp_u2;
  }
  do {
    tmp_i4 = local_14 * 0x90;
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i4 + 0x1050 + 0xc) =
         *(uint32_t *)(param_1 + 0x134);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i4 + 0x1054 + 0xc) =
         *(uint32_t *)(param_1 + 0x138);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i4 + 0x1058 + 0xc) =
         *(uint32_t *)(param_1 + 0x13c);
    *(uint32_t *)(tmp_i4 + 0x1050 + *(int *)(param_1 + 400) + 0x18) =
         *(uint32_t *)(param_1 + 0x140);
    *(uint32_t *)(tmp_i4 + 0x1054 + *(int *)(param_1 + 400) + 0x18) =
         *(uint32_t *)(param_1 + 0x144);
    *(uint32_t *)(tmp_i4 + 0x1058 + *(int *)(param_1 + 400) + 0x18) =
         *(uint32_t *)(param_1 + 0x148);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i4 + 0x1074) = *(uint32_t *)(param_1 + 0x168);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i4 + 0x1078) = *(uint32_t *)(param_1 + 0x16c);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i4 + 0x107c) = *(uint32_t *)(param_1 + 0x170);
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x108c + tmp_i4) =
         *(uint32_t *)(*(int *)(param_1 + 400) + 0xb0);
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x1090 + tmp_i4) =
         *(uint32_t *)(*(int *)(param_1 + 400) + 0xb4);
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x1094 + tmp_i4) =
         *(uint32_t *)(*(int *)(param_1 + 400) + 0xb8);
    *(uint *)(*(int *)(param_1 + 400) + tmp_i4 + 0x1080) = tmp_u3;
    tmp_i1 = tmp_i4 + 0x1090;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x1088 + tmp_i4) =
         *(uint32_t *)(*(int *)(param_1 + 400) + 0xc);
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x1084 + tmp_i4) =
         *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0xc) = *(uint32_t *)(param_1 + 0x558);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0x10) = *(uint32_t *)(param_1 + 0x55c);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0x14) = *(uint32_t *)(param_1 + 0x560);
    *(uint32_t *)(tmp_i1 + *(int *)(param_1 + 400) + 0x18) = *(uint32_t *)(param_1 + 0x578);
    tmp_i1 = tmp_i4 + 0x10a0;
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0xc) = *(uint32_t *)(param_1 + 0x564);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0x10) = *(uint32_t *)(param_1 + 0x57c);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0x14) = *(uint32_t *)(param_1 + 0x580);
    *(uint32_t *)(tmp_i1 + *(int *)(param_1 + 400) + 0x18) = *(uint32_t *)(param_1 + 0x588);
    tmp_i1 = tmp_i4 + 0x10b0;
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0xc) = *(uint32_t *)(param_1 + 0x584);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0x10) = *(uint32_t *)(param_1 + 0x58c);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0x14) = *(uint32_t *)(param_1 + 0x508);
    *(uint32_t *)(tmp_i1 + *(int *)(param_1 + 400) + 0x18) = *(uint32_t *)(param_1 + 0x50c);
    tmp_i1 = tmp_i4 + 0x10c0;
    tmp_i5 = tmp_i4 + 0x10d0;
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0xc) = *(uint32_t *)(param_1 + 0x510);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0x10) = *(uint32_t *)(param_1 + 0x528);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i1 + 0x14) = *(uint32_t *)(param_1 + 0x514);
    *(uint32_t *)(tmp_i1 + *(int *)(param_1 + 400) + 0x18) = *(uint32_t *)(param_1 + 0x52c);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i5 + 0xc) = *(uint32_t *)(param_1 + 0x530);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i5 + 0x10) = *(uint32_t *)(param_1 + 0x538);
    *(uint32_t *)(*(int *)(param_1 + 400) + tmp_i5 + 0x14) = *(uint32_t *)(param_1 + 0x534);
    *(uint32_t *)(tmp_i5 + *(int *)(param_1 + 400) + 0x18) = *(uint32_t *)(param_1 + 0x53c);
    local_14 = local_14 + -1;
    *(uint32_t *)(tmp_i4 + *(int *)(param_1 + 400) + 0x1098) = 0;
  } while (local_14 != -1);
  *(uint32_t *)(param_1 + 0x5a8) = 0;
  return;
}

void G_AttachBodyParts(uint *param_1)
{
  byte tmp_b1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint *tmp_pu5;
  int tmp_i6;
  long double tmp_l7;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t uStack_14;
  
  uStack_14 = 0x55a59;
  if (0 < g_unk_00abe938) {
    tmp_i6 = 0;
    do {
      tmp_i4 = (&g_unk_00abe944)[tmp_i6] * 0x600;
      tmp_pu5 = (uint *)(g_entities + tmp_i4);
      tmp_i3 = *(int *)(g_entities + tmp_i4 + 400);
      if (((((*(int *)(g_entities + tmp_i4 + 0x194) == 0) || (tmp_pu5 == param_1)) ||
           (*(int *)(tmp_i3 + 3000) == 3)) ||
          ((*(int *)(g_entities + tmp_i4 + 0x120) == 0 || ((*(byte *)(tmp_i3 + 0xd) & 0x40) != 0))))
         || ((*(int *)(tmp_i3 + 4) != 3 && (*(int *)(tmp_i3 + 4) != 0)))) {
        *(uint32_t *)(tmp_i3 + 0x528c) = 0;
        *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x5290) = 0;
      }
      else {
        tmp_u2 = G_BuildHead(tmp_pu5,0);
        *(uint32_t *)(tmp_i3 + 0x528c) = tmp_u2;
        tmp_i3 = *(int *)(g_entities + tmp_i4 + 400);
        tmp_u2 = G_BuildLeg(tmp_pu5,0);
        *(uint32_t *)(tmp_i3 + 0x5290) = tmp_u2;
        *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x54bc) =
             *(uint32_t *)(g_entities + tmp_i4 + 0x140);
        *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x54c0) =
             *(uint32_t *)(g_entities + tmp_i4 + 0x144);
        *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x54c4) =
             *(uint32_t *)(g_entities + tmp_i4 + 0x148);
        *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x54c8) =
             *(uint32_t *)(g_entities + tmp_i4 + 0x134);
        *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x54cc) =
             *(uint32_t *)(g_entities + tmp_i4 + 0x138);
        *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x54d0) =
             *(uint32_t *)(g_entities + tmp_i4 + 0x13c);
        if ((g_realBody[0xc] & 1) != 0) {
          *(float *)(g_entities + tmp_i4 + 0x140) = *(float *)(g_entities + tmp_i4 + 0x140) - 3.0;
          *(float *)(g_entities + tmp_i4 + 0x134) = *(float *)(g_entities + tmp_i4 + 0x134) + 3.0;
          *(float *)(g_entities + tmp_i4 + 0x144) = *(float *)(g_entities + tmp_i4 + 0x144) - 3.0;
          *(float *)(g_entities + tmp_i4 + 0x138) = *(float *)(g_entities + tmp_i4 + 0x138) + 3.0;
        }
        tmp_l7 = (long double)nitrox_HitboxHeight(tmp_pu5,param_1);
        tmp_b1 = g_antilag[0xc] & 2;
        *(float *)(g_entities + tmp_i4 + 0x148) = (float)tmp_l7;
        if (tmp_b1 != 0) {
          tmp_i3 = *(int *)(*(int *)(g_entities + tmp_i4 + 400) + 0xa0);
          if ((0x1f < tmp_i3) && (tmp_i3 = tmp_i3 >> 1, tmp_i3 == 0x20)) {
            tmp_i3 = 0x1f;
          }
          tmp_i3 = tmp_i3 * 0x10;
          local_2c = *(uint32_t *)(g_color_table + tmp_i3);
          local_28 = *(uint32_t *)(g_color_table + tmp_i3 + 4);
          local_24 = *(uint32_t *)(g_color_table + tmp_i3 + 8);
          G_RailBox(tmp_i4 + 0x93e608,tmp_i4 + 0x93e5d4,tmp_i4 + 0x93e5e0,&local_2c,*tmp_pu5 | 0x1000);
          tmp_i3 = *(int *)(g_entities + tmp_i4 + 400);
          tmp_pu5 = *(uint **)(tmp_i3 + 0x528c);
          if (tmp_pu5 != (uint *)0x0) {
            G_RailBox(tmp_pu5 + 0x5a,tmp_pu5 + 0x4d,tmp_pu5 + 0x50,&local_2c,*tmp_pu5 | 0x400);
            tmp_i3 = *(int *)(g_entities + tmp_i4 + 400);
          }
          tmp_pu5 = *(uint **)(tmp_i3 + 0x5290);
          if (tmp_pu5 != (uint *)0x0) {
            G_RailBox(tmp_pu5 + 0x5a,tmp_pu5 + 0x4d,tmp_pu5 + 0x50,&local_2c,*tmp_pu5 | 0x800);
          }
        }
      }
      tmp_i6 = tmp_i6 + 1;
    } while (tmp_i6 < g_unk_00abe938);
  }
  return;
}

void G_DettachBodyParts(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (0 < g_unk_00abe938) {
    tmp_i2 = 0;
    do {
      tmp_i3 = (&g_unk_00abe944)[tmp_i2] * 0x600;
      tmp_i1 = *(int *)(g_entities + tmp_i3 + 400);
      *(uint32_t *)(g_entities + tmp_i3 + 0x140) = *(uint32_t *)(tmp_i1 + 0x54bc);
      *(uint32_t *)(g_entities + tmp_i3 + 0x144) = *(uint32_t *)(tmp_i1 + 0x54c0);
      *(uint32_t *)(g_entities + tmp_i3 + 0x148) = *(uint32_t *)(tmp_i1 + 0x54c4);
      *(uint32_t *)(g_entities + tmp_i3 + 0x134) = *(uint32_t *)(tmp_i1 + 0x54c8);
      *(uint32_t *)(g_entities + tmp_i3 + 0x138) = *(uint32_t *)(tmp_i1 + 0x54cc);
      *(uint32_t *)(g_entities + tmp_i3 + 0x13c) = *(uint32_t *)(tmp_i1 + 0x54d0);
      if (*(int *)(tmp_i1 + 0x528c) != 0) {
        nitrox_FreeTempHead(*(int *)(tmp_i1 + 0x528c));
        tmp_i1 = *(int *)(g_entities + tmp_i3 + 400);
      }
      if (*(int *)(tmp_i1 + 0x5290) != 0) {
        nitrox_FreeTempLeg(*(int *)(tmp_i1 + 0x5290));
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 < g_unk_00abe938);
  }
  return;
}

int G_SwitchBodyPartEntity(uint32_t param_1,int param_2)
{
  if ((*(uint *)(param_2 + 4) & 0xfffffffd) != 0x28) {
    return (param_2 + -0x93e4a0 >> 9) * -0x55555555;
  }
  return (*(int *)(param_2 + 0x218) + -0x93e4a0 >> 9) * -0x55555555;
}

void G_HistoricalTraceBegin(uint8_t *param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  if (GHIDRA_FIELD(g_antilag, 12, 4) != 0) {
    if (0 < g_unk_00abe938) {
      tmp_i2 = 0;
      tmp_i1 = g_unk_00abe938;
      do {
        if (param_1 != g_entities + (&g_unk_00abe944)[tmp_i2] * 0x600) {
          G_AdjustSingleClientPosition_constprop_6();
          tmp_i1 = g_unk_00abe938;
        }
        tmp_i2 = tmp_i2 + 1;
      } while (tmp_i2 < tmp_i1);
      return;
    }
  }
  return;
}

void G_HistoricalTraceEnd(uint8_t *param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  int local_24;
  
  if ((GHIDRA_FIELD(g_antilag, 12, 4) != 0) && (local_24 = g_unk_00abe938, 0 < g_unk_00abe938)) {
    tmp_i5 = 0;
    do {
      tmp_i3 = (&g_unk_00abe944)[tmp_i5] * 0x600;
      tmp_pu4 = g_entities + tmp_i3;
      if ((((param_1 != tmp_pu4) && (tmp_pu4 != (uint8_t *)0x0)) &&
          (*(int *)(g_entities + tmp_i3 + 0x194) != 0)) &&
         (((*(int *)(g_entities + tmp_i3 + 0x120) != 0 &&
           (tmp_i2 = *(int *)(g_entities + tmp_i3 + 400), tmp_i2 != 0)) &&
          ((*(int *)(tmp_i2 + 3000) - 1U < 2 && ((*(byte *)(tmp_i2 + 0xd) & 0x40) == 0)))))) {
        if ((*(int *)(tmp_i2 + 0x1a28) == g_unk_00abe908) && (*(int *)(tmp_i2 + 4) == 3)) {
          if (GHIDRA_FIELD(g_realHead, 12, 4) != 0) {
LAB_00056004:
            *(uint32_t *)(g_entities + tmp_i3 + 0x168) = *(uint32_t *)(tmp_i2 + 0x1a04);
            *(uint32_t *)(g_entities + tmp_i3 + 0x16c) = *(uint32_t *)(tmp_i2 + 0x1a08);
            *(uint32_t *)(g_entities + tmp_i3 + 0x170) = *(uint32_t *)(tmp_i2 + 0x1a0c);
            *(uint32_t *)(g_entities + tmp_i3 + 0x134) = *(uint32_t *)(tmp_i2 + 0x19ec);
            *(uint32_t *)(g_entities + tmp_i3 + 0x138) = *(uint32_t *)(tmp_i2 + 0x19f0);
            *(uint32_t *)(g_entities + tmp_i3 + 0x13c) = *(uint32_t *)(tmp_i2 + 0x19f4);
            *(uint32_t *)(g_entities + tmp_i3 + 0x140) = *(uint32_t *)(tmp_i2 + 0x19f8);
            *(uint32_t *)(g_entities + tmp_i3 + 0x144) = *(uint32_t *)(tmp_i2 + 0x19fc);
            *(uint32_t *)(g_entities + tmp_i3 + 0x148) = *(uint32_t *)(tmp_i2 + 0x1a00);
            *(uint32_t *)(tmp_i2 + 0xb0) = *(uint32_t *)(tmp_i2 + 0x1a1c);
            *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb4) =
                 *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a20);
            *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb8) =
                 *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a24);
            *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x68) =
                 *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a10);
            *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xc) =
                 *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a18);
            *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0xbc) =
                 *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a14);
            *(uint32_t *)(*(int *)(g_entities + tmp_i3 + 400) + 0x1a28) = 0;
            tmp_i2 = *(int *)(g_entities + tmp_i3 + 400);
            *(uint32_t *)(g_entities + tmp_i3 + 0x558) = *(uint32_t *)(tmp_i2 + 0x1a2c);
            *(uint32_t *)(g_entities + tmp_i3 + 0x55c) = *(uint32_t *)(tmp_i2 + 0x1a30);
            *(uint32_t *)(g_entities + tmp_i3 + 0x560) = *(uint32_t *)(tmp_i2 + 0x1a34);
            *(uint32_t *)(g_entities + tmp_i3 + 0x578) = *(uint32_t *)(tmp_i2 + 0x1a38);
            *(uint32_t *)(g_entities + tmp_i3 + 0x564) = *(uint32_t *)(tmp_i2 + 0x1a3c);
            *(uint32_t *)(g_entities + tmp_i3 + 0x57c) = *(uint32_t *)(tmp_i2 + 0x1a40);
            *(uint32_t *)(g_entities + tmp_i3 + 0x580) = *(uint32_t *)(tmp_i2 + 0x1a44);
            *(uint32_t *)(g_entities + tmp_i3 + 0x588) = *(uint32_t *)(tmp_i2 + 0x1a48);
            *(uint32_t *)(g_entities + tmp_i3 + 0x584) = *(uint32_t *)(tmp_i2 + 0x1a4c);
            *(uint32_t *)(g_entities + tmp_i3 + 0x58c) = *(uint32_t *)(tmp_i2 + 0x1a50);
            *(uint32_t *)(g_entities + tmp_i3 + 0x508) = *(uint32_t *)(tmp_i2 + 0x1a54);
            *(uint32_t *)(g_entities + tmp_i3 + 0x50c) = *(uint32_t *)(tmp_i2 + 0x1a58);
            *(uint32_t *)(g_entities + tmp_i3 + 0x510) = *(uint32_t *)(tmp_i2 + 0x1a5c);
            *(uint32_t *)(g_entities + tmp_i3 + 0x528) = *(uint32_t *)(tmp_i2 + 0x1a60);
            *(uint32_t *)(g_entities + tmp_i3 + 0x514) = *(uint32_t *)(tmp_i2 + 0x1a64);
            *(uint32_t *)(g_entities + tmp_i3 + 0x52c) = *(uint32_t *)(tmp_i2 + 0x1a68);
            *(uint32_t *)(g_entities + tmp_i3 + 0x530) = *(uint32_t *)(tmp_i2 + 0x1a6c);
            tmp_u1 = *(uint32_t *)(tmp_i2 + 0x1a70);
            *(uint32_t *)(g_entities + tmp_i3 + 0x5a8) = 0;
            *(uint32_t *)(g_entities + tmp_i3 + 0x538) = tmp_u1;
            trap_LinkEntity(tmp_pu4);
            local_24 = g_unk_00abe938;
          }
        }
        else if ((0 < *(int *)(g_entities + tmp_i3 + 0x2c8)) &&
                (((*(int *)(tmp_i2 + 4) == 0 && ((*(byte *)(tmp_i2 + 0x69) & 0x80) == 0)) &&
                 (*(int *)(tmp_i2 + 0x1a28) == g_unk_00abe908)))) goto LAB_00056004;
      }
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 < local_24);
  }
  return;
}

void G_TempTraceIgnoreBodies(void)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  
  tmp_pu2 = &g_unk_00abf9b8;
  do {
    tmp_u1 = *tmp_pu2;
    tmp_pu2 = tmp_pu2 + 1;
    G_TempTraceIgnoreEntity(tmp_u1);
  } while (tmp_pu2 != &g_unk_00abf9d8);
  return;
}

void G_TraceNew(int param_1,int param_2,uint32_t param_3,float *param_4,uint32_t param_5,
               uint32_t param_6,float *param_7,uint32_t param_8,uint param_9)

{
  int tmp_i1;
  uint8_t local_3c [4];
  int local_38;
  uint8_t local_34 [12];
  float local_28;
  float local_24;
  float local_20;
  
  local_38 = -1;
  *(uint32_t *)(param_1 + 0x5ec) = 0xfffffffe;
  trap_EngineerTrace(param_2,param_4,param_5,param_6,param_7,0x3ff,param_9);
  trap_EngineerTrace(param_3,param_4,param_5,param_6,param_7,0x3ff,param_9 | 0x38);
  TracePlayers(param_1,param_4,param_2 + 0xc,local_34,local_3c,&local_38,param_1 + 0x5ec);
  tmp_i1 = local_38;
  if ((local_38 != -1) && (local_38 != *(int *)(param_2 + 0x34))) {
    local_28 = *param_7 - *param_4;
    local_24 = param_7[1] - param_4[1];
    local_20 = param_7[2] - param_4[2];
    VectorNormalizeFast(&local_28);
    *(int *)(param_2 + 0x34) = tmp_i1;
    *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) - local_28;
    *(float *)(param_2 + 0x10) = *(float *)(param_2 + 0x10) - local_24;
    *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) - local_20;
  }
  return;
}

void G_Trace(int param_1,int param_2,float *param_3,uint32_t param_4,uint32_t param_5,
            float *param_6,uint32_t param_7,uint32_t param_8,int param_9,int param_10)

{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  float local_54;
  float local_50;
  float local_4c;
  int local_20;
  
  G_AttachBodyParts(param_1);
  if (param_9 != 0) {
    tmp_pu4 = &g_unk_00abf9b8;
    do {
      tmp_u1 = *tmp_pu4;
      tmp_pu4 = tmp_pu4 + 1;
      G_TempTraceIgnoreEntity(tmp_u1);
    } while (tmp_pu4 != &g_unk_00abf9d8);
  }
  trap_Trace(param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  tmp_i5 = *(int *)(param_2 + 0x34);
  tmp_i2 = tmp_i5 * 0x600;
  if ((*(int *)(g_entities + tmp_i2 + 4) == 0x28) || (*(int *)(g_entities + tmp_i2 + 4) == 0x2a)) {
    tmp_i2 = *(int *)(g_entities + tmp_i2 + 0x218) + -0x93e4a0;
  }
  tmp_i3 = (tmp_i2 >> 9) * -0x55555555;
  if (param_10 != 0) {
    *(uint32_t *)(param_1 + 0x5ec) = 0xffffffff;
    tmp_i2 = (tmp_i2 >> 9) * 0x200;
    if (*(int *)(g_entities + tmp_i2 + 400) != 0) {
      *(uint32_t *)(param_1 + 0x5ec) = 2;
      if ((*(uint *)(g_entities + tmp_i5 * 0x600 + 4) & 0xfffffffd) == 0x28) {
        *(uint *)(param_1 + 0x5ec) = (uint)(*(uint *)(g_entities + tmp_i5 * 0x600 + 4) != 0x28) * 3;
        tmp_i5 = *(int *)(param_2 + 0x34);
        goto LAB_000564b5;
      }
      trap_Trace(&local_54,param_3,0,0,param_6,*(uint32_t *)(g_entities + tmp_i2),0x6000001);
      tmp_pu4 = *(uint32_t **)(g_entities + local_20 * 0x600 + 0x218);
      if (((tmp_pu4 != (uint32_t *)0x0) && (tmp_pu4[100] != 0)) &&
         (tmp_pu4 == (uint32_t *)(g_entities + tmp_i2))) {
        if (*(int *)(g_entities + local_20 * 0x600 + 4) == 0x28) {
          *(uint32_t *)(param_1 + 0x5ec) = 0;
        }
        else if (*(int *)(g_entities + local_20 * 0x600 + 4) == 0x2a) {
          *(uint32_t *)(param_1 + 0x5ec) = 3;
        }
      }
    }
    tmp_i5 = *(int *)(param_2 + 0x34);
  }
LAB_000564b5:
  if (tmp_i3 != tmp_i5) {
    local_54 = *param_6 - *param_3;
    local_50 = param_6[1] - param_3[1];
    local_4c = param_6[2] - param_3[2];
    VectorNormalizeFast(&local_54);
    *(int *)(param_2 + 0x34) = tmp_i3;
    *(float *)(param_2 + 0xc) = *(float *)(param_2 + 0xc) - local_54;
    *(float *)(param_2 + 0x10) = *(float *)(param_2 + 0x10) - local_50;
    *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) - local_4c;
  }
  if (0 < g_unk_00abe938) {
    tmp_i5 = 0;
    do {
      tmp_i3 = (&g_unk_00abe944)[tmp_i5] * 0x600;
      tmp_i2 = *(int *)(g_entities + tmp_i3 + 400);
      *(uint32_t *)(g_entities + tmp_i3 + 0x140) = *(uint32_t *)(tmp_i2 + 0x54bc);
      *(uint32_t *)(g_entities + tmp_i3 + 0x144) = *(uint32_t *)(tmp_i2 + 0x54c0);
      *(uint32_t *)(g_entities + tmp_i3 + 0x148) = *(uint32_t *)(tmp_i2 + 0x54c4);
      *(uint32_t *)(g_entities + tmp_i3 + 0x134) = *(uint32_t *)(tmp_i2 + 0x54c8);
      *(uint32_t *)(g_entities + tmp_i3 + 0x138) = *(uint32_t *)(tmp_i2 + 0x54cc);
      *(uint32_t *)(g_entities + tmp_i3 + 0x13c) = *(uint32_t *)(tmp_i2 + 0x54d0);
      if (*(int *)(tmp_i2 + 0x528c) != 0) {
        nitrox_FreeTempHead(*(int *)(tmp_i2 + 0x528c));
        tmp_i2 = *(int *)(g_entities + tmp_i3 + 400);
      }
      if (*(int *)(tmp_i2 + 0x5290) != 0) {
        nitrox_FreeTempLeg(*(int *)(tmp_i2 + 0x5290));
      }
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 < g_unk_00abe938);
  }
  if (param_9 != 0) {
    G_ResetTempTraceIgnoreEnts();
  }
  return;
}

void G_HistoricalTrace(uint8_t *param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
                      uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8,
                      uint32_t param_9)

{
  uint32_t tmp_u1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  int local_28;
  
  *(uint32_t *)(param_1 + 0x5ec) = 0xffffffff;
  if ((((g_antilag[0xc] & 1) != 0) && (*(int *)(param_1 + 400) != 0)) && (0 < g_unk_00abe938)) {
    tmp_i4 = 0;
    tmp_i5 = g_unk_00abe938;
    do {
      if (param_1 != g_entities + (&g_unk_00abe944)[tmp_i4] * 0x600) {
        G_AdjustSingleClientPosition_constprop_6();
        tmp_i5 = g_unk_00abe938;
      }
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_i4 < tmp_i5);
  }
  G_Trace(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,param_9);
  if ((((g_antilag[0xc] & 1) != 0) && (*(int *)(param_1 + 400) != 0)) &&
     (local_28 = g_unk_00abe938, 0 < g_unk_00abe938)) {
    tmp_i5 = 0;
    do {
      while( true ) {
        tmp_i4 = (&g_unk_00abe944)[tmp_i5] * 0x600;
        tmp_pu3 = g_entities + tmp_i4;
        if (((param_1 != tmp_pu3) && (tmp_pu3 != (uint8_t *)0x0)) &&
           ((*(int *)(g_entities + tmp_i4 + 0x194) != 0 &&
            ((((*(int *)(g_entities + tmp_i4 + 0x120) != 0 &&
               (tmp_i2 = *(int *)(g_entities + tmp_i4 + 400), tmp_i2 != 0)) &&
              (*(int *)(tmp_i2 + 3000) - 1U < 2)) && ((*(byte *)(tmp_i2 + 0xd) & 0x40) == 0))))))
        break;
LAB_000568a8:
        tmp_i5 = tmp_i5 + 1;
        if (local_28 <= tmp_i5) {
          return;
        }
      }
      if ((*(int *)(tmp_i2 + 0x1a28) != g_unk_00abe908) || (*(int *)(tmp_i2 + 4) != 3)) {
        if ((0 < *(int *)(g_entities + tmp_i4 + 0x2c8)) &&
           (((*(int *)(tmp_i2 + 4) == 0 && ((*(byte *)(tmp_i2 + 0x69) & 0x80) == 0)) &&
            (*(int *)(tmp_i2 + 0x1a28) == g_unk_00abe908)))) goto LAB_0005694c;
        goto LAB_000568a8;
      }
      if (GHIDRA_FIELD(g_realHead, 12, 4) == 0) goto LAB_000568a8;
LAB_0005694c:
      tmp_i5 = tmp_i5 + 1;
      *(uint32_t *)(g_entities + tmp_i4 + 0x168) = *(uint32_t *)(tmp_i2 + 0x1a04);
      *(uint32_t *)(g_entities + tmp_i4 + 0x16c) = *(uint32_t *)(tmp_i2 + 0x1a08);
      *(uint32_t *)(g_entities + tmp_i4 + 0x170) = *(uint32_t *)(tmp_i2 + 0x1a0c);
      *(uint32_t *)(g_entities + tmp_i4 + 0x134) = *(uint32_t *)(tmp_i2 + 0x19ec);
      *(uint32_t *)(g_entities + tmp_i4 + 0x138) = *(uint32_t *)(tmp_i2 + 0x19f0);
      *(uint32_t *)(g_entities + tmp_i4 + 0x13c) = *(uint32_t *)(tmp_i2 + 0x19f4);
      *(uint32_t *)(g_entities + tmp_i4 + 0x140) = *(uint32_t *)(tmp_i2 + 0x19f8);
      *(uint32_t *)(g_entities + tmp_i4 + 0x144) = *(uint32_t *)(tmp_i2 + 0x19fc);
      *(uint32_t *)(g_entities + tmp_i4 + 0x148) = *(uint32_t *)(tmp_i2 + 0x1a00);
      *(uint32_t *)(tmp_i2 + 0xb0) = *(uint32_t *)(tmp_i2 + 0x1a1c);
      *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0xb4) =
           *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x1a20);
      *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0xb8) =
           *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x1a24);
      *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x68) =
           *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x1a10);
      *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0xc) =
           *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x1a18);
      *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0xbc) =
           *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x1a14);
      *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0x1a28) = 0;
      tmp_i2 = *(int *)(g_entities + tmp_i4 + 400);
      *(uint32_t *)(g_entities + tmp_i4 + 0x558) = *(uint32_t *)(tmp_i2 + 0x1a2c);
      *(uint32_t *)(g_entities + tmp_i4 + 0x55c) = *(uint32_t *)(tmp_i2 + 0x1a30);
      *(uint32_t *)(g_entities + tmp_i4 + 0x560) = *(uint32_t *)(tmp_i2 + 0x1a34);
      *(uint32_t *)(g_entities + tmp_i4 + 0x578) = *(uint32_t *)(tmp_i2 + 0x1a38);
      *(uint32_t *)(g_entities + tmp_i4 + 0x564) = *(uint32_t *)(tmp_i2 + 0x1a3c);
      *(uint32_t *)(g_entities + tmp_i4 + 0x57c) = *(uint32_t *)(tmp_i2 + 0x1a40);
      *(uint32_t *)(g_entities + tmp_i4 + 0x580) = *(uint32_t *)(tmp_i2 + 0x1a44);
      *(uint32_t *)(g_entities + tmp_i4 + 0x588) = *(uint32_t *)(tmp_i2 + 0x1a48);
      *(uint32_t *)(g_entities + tmp_i4 + 0x584) = *(uint32_t *)(tmp_i2 + 0x1a4c);
      *(uint32_t *)(g_entities + tmp_i4 + 0x58c) = *(uint32_t *)(tmp_i2 + 0x1a50);
      *(uint32_t *)(g_entities + tmp_i4 + 0x508) = *(uint32_t *)(tmp_i2 + 0x1a54);
      *(uint32_t *)(g_entities + tmp_i4 + 0x50c) = *(uint32_t *)(tmp_i2 + 0x1a58);
      *(uint32_t *)(g_entities + tmp_i4 + 0x510) = *(uint32_t *)(tmp_i2 + 0x1a5c);
      *(uint32_t *)(g_entities + tmp_i4 + 0x528) = *(uint32_t *)(tmp_i2 + 0x1a60);
      *(uint32_t *)(g_entities + tmp_i4 + 0x514) = *(uint32_t *)(tmp_i2 + 0x1a64);
      *(uint32_t *)(g_entities + tmp_i4 + 0x52c) = *(uint32_t *)(tmp_i2 + 0x1a68);
      *(uint32_t *)(g_entities + tmp_i4 + 0x530) = *(uint32_t *)(tmp_i2 + 0x1a6c);
      tmp_u1 = *(uint32_t *)(tmp_i2 + 0x1a70);
      *(uint32_t *)(g_entities + tmp_i4 + 0x5a8) = 0;
      *(uint32_t *)(g_entities + tmp_i4 + 0x538) = tmp_u1;
      trap_LinkEntity(tmp_pu3);
      local_28 = g_unk_00abe938;
    } while (tmp_i5 < g_unk_00abe938);
  }
  return;
}

bool G_SkipCorrectionSafe(int param_1)
{
  int tmp_i1;
  bool tmp_b2;
  
  if (param_1 == 0) {
    return false;
  }
  tmp_b2 = false;
  if ((*(int *)(param_1 + 0x194) != 0) && (tmp_b2 = false, *(int *)(param_1 + 0x120) != 0)) {
    tmp_i1 = *(int *)(param_1 + 400);
    if (tmp_i1 == 0) {
      return false;
    }
    tmp_b2 = false;
    if ((((*(int *)(tmp_i1 + 3000) - 1U < 2) && ((*(uint *)(tmp_i1 + 0xc) & 0xc000) == 0)) &&
        (0 < *(int *)(param_1 + 0x2c8))) &&
       (((*(int *)(tmp_i1 + 4) == 0 && ((*(uint *)(tmp_i1 + 0x68) & 0x88000) == 0)) &&
        (*(int *)(param_1 + 0x304) < 2)))) {
      if (*(float *)(tmp_i1 + 0x20) == 0.0) {
        tmp_b2 = NAN(*(float *)(tmp_i1 + 0x24));
        if (*(float *)(tmp_i1 + 0x24) != 0.0) {
          tmp_b2 = true;
        }
      }
      else {
        tmp_b2 = true;
      }
    }
  }
  return tmp_b2;
}

void G_PredictPmove(int param_1,uint32_t param_2)
{
  float tmp_f1;
  float tmp_f2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  uint32_t tmp_u7;
  int tmp_i8;
  uint tmp_u9;
  uint32_t tmp_u10;
  uint32_t tmp_u11;
  uint32_t tmp_u12;
  uint tmp_u13;
  int local_160 [17];
  uint8_t *local_11c;
  uint32_t local_78;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  void *local_48;
  void *local_44;
  uint32_t local_40;
  
  if ((((((param_1 != 0) && (*(int *)(param_1 + 0x194) != 0)) && (*(int *)(param_1 + 0x120) != 0))
       && ((tmp_i8 = *(int *)(param_1 + 400), tmp_i8 != 0 && (*(int *)(tmp_i8 + 3000) - 1U < 2)))) &&
      (((*(uint *)(tmp_i8 + 0xc) & 0xc000) == 0 &&
       ((0 < *(int *)(param_1 + 0x2c8) && (*(int *)(tmp_i8 + 4) == 0)))))) &&
     ((tmp_u9 = *(uint *)(tmp_i8 + 0x68), (tmp_u9 & 0x88000) == 0 && (*(int *)(param_1 + 0x304) < 2))))
  {
    tmp_f1 = *(float *)(tmp_i8 + 0x20);
    tmp_f2 = *(float *)(tmp_i8 + 0x24);
    if ((tmp_f1 != 0.0) || (tmp_f2 != 0.0)) {
      tmp_u10 = *(uint32_t *)(tmp_i8 + 0xc);
      tmp_u3 = *(uint32_t *)(tmp_i8 + 0x14);
      tmp_u11 = *(uint32_t *)(tmp_i8 + 0x50);
      tmp_u4 = *(uint32_t *)(tmp_i8 + 0x18);
      tmp_u12 = *(uint32_t *)(tmp_i8 + 0x10);
      tmp_u5 = *(uint32_t *)(tmp_i8 + 0x1c);
      tmp_u6 = *(uint32_t *)(tmp_i8 + 0x28);
      tmp_u13 = 0;
      do {
        *(uint32_t *)((int)local_160 + tmp_u13) = 0;
        *(uint32_t *)((int)local_160 + tmp_u13 + 4) = 0;
        tmp_u13 = tmp_u13 + 8;
      } while (tmp_u13 < 0x140);
      tmp_u7 = *(uint32_t *)(param_1 + 0x134);
      *(uint32_t *)((int)local_160 + tmp_u13) = 0;
      local_160[1] = tmp_i8 + 0x52a0;
      local_74 = *(uint32_t *)(param_1 + 0x138);
      local_160[2] = *(uint32_t *)(tmp_i8 + 0x99c);
      local_70 = *(uint32_t *)(param_1 + 0x13c);
      local_6c = *(uint32_t *)(param_1 + 0x140);
      local_48 = trap_TraceCapsuleNoEnts;
      local_68 = *(uint32_t *)(param_1 + 0x144);
      local_64 = *(uint32_t *)(param_1 + 0x148);
      local_44 = trap_PointContents;
      local_11c = &g_unk_02010001;
      local_40 = 1;
      local_160[0] = tmp_i8;
      local_78 = tmp_u7;
      PmovePredict(local_160,param_2);
      *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(tmp_i8 + 0x14);
      *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(tmp_i8 + 0x18);
      *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(tmp_i8 + 0x1c);
      *(uint32_t *)(param_1 + 0x24) = *(uint32_t *)(tmp_i8 + 0x20);
      *(uint32_t *)(param_1 + 0x28) = *(uint32_t *)(tmp_i8 + 0x24);
      *(uint32_t *)(param_1 + 0x2c) = *(uint32_t *)(tmp_i8 + 0x28);
      *(uint32_t *)(param_1 + 0x94) = *(uint32_t *)(tmp_i8 + 0x50);
      *(uint32_t *)(param_1 + 8) = *(uint32_t *)(tmp_i8 + 0x68);
      *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(tmp_i8 + 0x14);
      *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(tmp_i8 + 0x18);
      *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(tmp_i8 + 0x1c);
      trap_LinkEntity(param_1);
      *(uint *)(tmp_i8 + 0x68) = tmp_u9;
      *(uint32_t *)(tmp_i8 + 0xc) = tmp_u10;
      *(uint32_t *)(tmp_i8 + 0x50) = tmp_u11;
      *(uint32_t *)(tmp_i8 + 0x14) = tmp_u3;
      *(uint32_t *)(tmp_i8 + 0x10) = tmp_u12;
      *(uint32_t *)(tmp_i8 + 0x18) = tmp_u4;
      *(uint32_t *)(tmp_i8 + 0x1c) = tmp_u5;
      *(float *)(tmp_i8 + 0x20) = tmp_f1;
      *(float *)(tmp_i8 + 0x24) = tmp_f2;
      *(uint32_t *)(tmp_i8 + 0x28) = tmp_u6;
    }
  }
  return;
}

void G_RemoveFromAllIgnoreLists(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
    tmp_i2 = 0;
    tmp_i3 = 0;
    do {
      tmp_i3 = tmp_i3 + 1;
      tmp_i1 = level + tmp_i2;
      tmp_i2 = tmp_i2 + 0x54dc;
      COM_BitClear(tmp_i1 + 0xbe8,param_1);
    } while (tmp_i3 < (int)GHIDRA_FIELD(g_maxclients, 12, 4));
  }
  return;
}

uint32_t G_RegisterCharacter(uint32_t param_1,int param_2)
{
  uint32_t *tmp_pu1;
  float tmp_f2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  long tmp_l6;
  char *__s;
  char *tmp_pc7;
  char **ppcVar8;
  int local_3b4;
  float local_3b0;
  int local_3a0;
  char **local_39c;
  char *local_38c [2];
  char *local_384 [2];
  char *local_37c;
  float local_378;
  uint32_t local_374;
  float local_370;
  char *local_36c [12];
  float local_33c;
  uint32_t local_338;
  float local_334;
  int local_30c [76];
  uint8_t local_1dc [64];
  uint8_t local_19c [64];
  uint8_t local_15c [328];
  uint32_t uStack_14;
  
  tmp_u3 = 0;
  uStack_14 = 0x56f6b;
  do {
    *(uint32_t *)((int)local_30c + tmp_u3 + 0xb0) = 0;
    *(uint32_t *)((int)local_30c + tmp_u3 + 0xb4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0x240);
  tmp_i4 = BG_ParseCharacterFile(param_1);
  if (tmp_i4 != 0) {
    tmp_i4 = trap_R_RegisterModel(local_15c);
    *(int *)(param_2 + 0x40) = tmp_i4;
    if (tmp_i4 == 0) {
      G_Printf("^3WARNING: failed to register mesh \'%s\' referenced from \'%s\'\n",local_15c,
               param_1);
    }
    __s = (char *)0x0;
    tmp_pc7 = &g_unk_00abfaa0;
    do {
      if ((*tmp_pc7 == '\0') || (tmp_pc7[0x40] == '\0')) {
        if (__s == (char *)0x0) {
          __s = tmp_pc7;
        }
      }
      else {
        tmp_i4 = Q_stricmp(tmp_pc7);
        if ((tmp_i4 == 0) && (tmp_i4 = Q_stricmp(tmp_pc7 + 0x40), tmp_i4 == 0)) {
          *(char **)(param_2 + 0x7f0) = tmp_pc7;
          return 1;
        }
      }
      tmp_pc7 = tmp_pc7 + 0xfeae8;
    } while (tmp_pc7 != &g_unk_02a957a0);
    if (__s == (char *)0x0) {
      G_Error("unable to find a free modelinfo slot, cannot continue\n");
    }
    else {
      *(char **)(param_2 + 0x7f0) = __s;
      memset(__s,0,0xfeae8);
    }
    Q_strncpyz(*(uint32_t *)(param_2 + 0x7f0),local_1dc,0x40);
    Q_strncpyz(*(int *)(param_2 + 0x7f0) + 0x40,local_19c,0x40);
    BG_R_RegisterAnimationGroup(local_1dc,*(uint32_t *)(param_2 + 0x7f0));
    local_38c[0] = "tag_footleft";
    local_38c[1] = "tag_footright";
    tmp_u3 = 0;
    local_384[0] = (char *)0x0;
    local_384[1] = (char *)0x0;
    local_37c = (char *)0x0;
    local_378 = 0.0;
    local_374 = 0;
    local_370 = 0.0;
    do {
      *(uint32_t *)((int)local_30c + tmp_u3) = 0;
      *(uint32_t *)((int)local_30c + tmp_u3 + 4) = 0;
      tmp_u3 = tmp_u3 + 8;
    } while (tmp_u3 < 0xb0);
    local_30c[0] = *(int *)(param_2 + 0x40);
    tmp_i4 = *(int *)(param_2 + 0x7f0);
    tmp_i5 = *(int *)(tmp_i4 + 0x89c);
    if (0 < tmp_i5) {
      local_3a0 = 0;
      do {
        while (tmp_pu1 = *(uint32_t **)(tmp_i4 + 0x9c + local_3a0 * 4), (int)tmp_pu1[0x16] < 0) {
          if ((int)tmp_pu1[0x12] < 1) {
            tmp_f2 = 0.0;
            local_3b0 = 0.0;
          }
          else {
            local_3b4 = 0;
            local_3b0 = 0.0;
            do {
              tmp_i4 = 0;
              local_30c[0x1f] = local_3b4 + tmp_pu1[0x11];
              local_30c[0x20] = *tmp_pu1;
              ppcVar8 = local_38c + 8;
              local_30c[0x22] = local_30c[0x20];
              local_30c[0x26] = local_30c[0x1f];
              local_30c[0x27] = local_30c[0x20];
              local_30c[0x29] = local_30c[0x20];
              while( true ) {
                tmp_i5 = trap_R_LerpTag(ppcVar8,local_30c,local_38c[tmp_i4],0);
                if (tmp_i5 < 0) {
                  G_Error("G_CalcMoveSpeeds: unable to find tag %s, cannot calculate movespeed");
                }
                ppcVar8 = ppcVar8 + 0xc;
                if (tmp_i4 == 1) break;
                tmp_i4 = 1;
              }
              if ((*(byte *)(tmp_pu1 + 0x1a) & 1) == 0) {
                tmp_f2 = (float)local_38c[(uint)(local_334 <= (float)local_36c[2]) * 3 + 2] -
                        (float)local_38c[(uint)(local_334 <= (float)local_36c[2]) * 0xc + 8];
              }
              else {
                tmp_f2 = (float)local_38c[(uint)((float)local_36c[0] <= local_33c) * 3 + 4] -
                        (float)local_38c[(uint)((float)local_36c[0] <= local_33c) * 0xc + 10];
              }
              local_3b0 = ABS(tmp_f2) + local_3b0;
              local_384[0] = local_36c[0];
              local_3b4 = local_3b4 + 1;
              local_384[1] = local_36c[1];
              local_37c = local_36c[2];
              local_378 = local_33c;
              local_374 = local_338;
              local_370 = local_334;
            } while (local_3b4 < (int)tmp_pu1[0x12]);
            tmp_f2 = (float)local_3b4;
          }
          tmp_l6 = lrint((double)(((local_3b0 / tmp_f2) * 1000.0) / (float)(int)tmp_pu1[0x14]));
          local_3a0 = local_3a0 + 1;
          tmp_pu1[0x16] = tmp_l6;
          tmp_i4 = *(int *)(param_2 + 0x7f0);
          tmp_i5 = *(int *)(tmp_i4 + 0x89c);
          if (tmp_i5 <= local_3a0) goto LAB_000573a9;
        }
        local_3a0 = local_3a0 + 1;
      } while (local_3a0 < tmp_i5);
    }
LAB_000573a9:
    local_39c = local_38c + 8;
    tmp_i4 = trap_FS_FOpenFile(local_19c,local_39c,0);
    if (0 < tmp_i4) {
      if (tmp_i4 < 99999) {
        trap_FS_Read(&bigTextBuffer,tmp_i4,local_36c[0]);
        (&bigTextBuffer)[tmp_i4] = 0;
        trap_FS_FCloseFile(local_36c[0]);
        BG_AnimParseAnimScript
                  (*(uint32_t *)(param_2 + 0x7f0),&g_unk_00abfaa0,local_19c,&bigTextBuffer);
        Init_Hit_ETKill();
        return 1;
      }
      G_Printf("File %s is too long\n",local_30c);
    }
    G_Printf("^3WARNING: failed to load animation files referenced from \'%s\'\n",param_1);
  }
  return 0;
}

void G_RegisterPlayerClasses(void)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  
  tmp_i5 = 0;
  do {
    tmp_pu1 = (uint32_t *)BG_GetPlayerClassInfo(1,tmp_i5);
    tmp_u2 = BG_GetCharacter(1,tmp_i5);
    Q_strncpyz(tmp_u2,tmp_pu1[1],0x40);
    tmp_i3 = G_RegisterCharacter(tmp_u2,tmp_u2);
    if (tmp_i3 == 0) {
      tmp_u4 = BG_ClassnameForNumber(*tmp_pu1);
      G_Error("ERROR: G_RegisterPlayerClasses: failed to load character file \'%s\' for the %s %s\n"
              ,tmp_u2,"Axis",tmp_u4);
    }
    tmp_i5 = tmp_i5 + 1;
  } while (tmp_i5 != 5);
  tmp_i5 = 0;
  do {
    tmp_pu1 = (uint32_t *)BG_GetPlayerClassInfo(2,tmp_i5);
    tmp_u2 = BG_GetCharacter(2,tmp_i5);
    Q_strncpyz(tmp_u2,tmp_pu1[1],0x40);
    tmp_i3 = G_RegisterCharacter(tmp_u2,tmp_u2);
    if (tmp_i3 == 0) {
      tmp_u4 = BG_ClassnameForNumber(*tmp_pu1);
      G_Error("ERROR: G_RegisterPlayerClasses: failed to load character file \'%s\' for the %s %s\n"
              ,tmp_u2,"Allied",tmp_u4);
    }
    tmp_i5 = tmp_i5 + 1;
  } while (tmp_i5 != 5);
  return;
}

void G_UpdateCharacter(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = BG_GetCharacter(*(uint32_t *)(param_1 + 3000),*(uint32_t *)(param_1 + 0xbc8));
  if (*(int *)(param_1 + 0x99c) != tmp_i1) {
    *(uint32_t *)(param_1 + 0x9a0) = 0xffffffff;
    *(int *)(param_1 + 0x99c) = tmp_i1;
    *(uint32_t *)(param_1 + 0x58) = 0;
    *(uint32_t *)(param_1 + 0x60) = 0;
    *(uint32_t *)(param_1 + 0x54) = 0;
    *(uint32_t *)(param_1 + 0x5c) = 0;
  }
  return;
}

void G_SetDefaultLevel_part_4(int param_1,int param_2)
{
  int tmp_i1;
  bool tmp_b2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint32_t tmp_u6;
  int *tmp_pi7;
  int local_38;
  uint32_t local_24;
  
  tmp_i1 = *(int *)(param_1 + 400);
  if ((tmp_i1 != 0) && (*(int *)(tmp_i1 + 0x54d8) == 0)) {
    tmp_pi7 = &Users;
    if (Users == 0) {
      local_38 = 0;
    }
    else {
      local_24 = 0;
      tmp_b2 = false;
      local_38 = 0;
      tmp_i5 = Users;
      do {
        if ((*(char *)(tmp_i5 + 4) != '\0') &&
           (tmp_i3 = strcmp((char *)(tmp_i5 + 4),(char *)(tmp_i1 + 0x61c)), tmp_i3 == 0)) {
          tmp_i3 = *(int *)(param_1 + 400);
          tmp_i4 = strcmp((char *)(tmp_i5 + 0x25),(char *)(tmp_i3 + 0x5f8));
          if (tmp_i4 != 0) {
            Q_strncpyz((char *)(tmp_i5 + 0x25),(char *)(tmp_i3 + 0x5f8),0x24);
            local_24 = 1;
            tmp_i3 = *(int *)(param_1 + 400);
          }
          tmp_i5 = *tmp_pi7;
          tmp_i4 = strcmp((char *)(tmp_i5 + 0xc62),(char *)(tmp_i3 + 0x653));
          if (tmp_i4 != 0) {
            Q_strncpyz((char *)(tmp_i5 + 0xc62),(char *)(tmp_i3 + 0x653),0x12);
            tmp_i5 = *tmp_pi7;
            local_24 = 1;
            tmp_i3 = *(int *)(param_1 + 400);
          }
          tmp_i4 = strcmp((char *)(tmp_i5 + 0xc50),(char *)(tmp_i3 + 0xaf4));
          if (tmp_i4 != 0) {
            Q_strncpyz((char *)(tmp_i5 + 0xc50),(char *)(tmp_i3 + 0xaf4),0x12);
            tmp_i5 = *tmp_pi7;
            local_24 = 1;
          }
          tmp_b2 = true;
          *(uint32_t *)(tmp_i5 + 0x10dc) = local_24;
          nitrox_SetAdminPointers(param_1,*tmp_pi7);
        }
        tmp_pi7 = tmp_pi7 + 1;
        tmp_i5 = *tmp_pi7;
        local_38 = local_38 + 1;
      } while (tmp_i5 != 0);
      if (tmp_b2) {
        return;
      }
    }
    tmp_i5 = AllocUser();
    tmp_u6 = nitrox_LevelPointer(0);
    *(uint32_t *)(tmp_i5 + 0x4c) = tmp_u6;
    Q_strncpyz(tmp_i5 + 0x25,*(int *)(param_1 + 400) + 0x5f8,0x24);
    Q_strncpyz(tmp_i5 + 4,(char *)(tmp_i1 + 0x61c),0x21);
    Q_strncpyz(tmp_i5 + 0xc62,*(int *)(param_1 + 400) + 0x653,0x12);
    Q_strncpyz(tmp_i5 + 0xc50,*(int *)(param_1 + 400) + 0xaf4,0x12);
    (&Users)[local_38] = tmp_i5;
    if (param_2 == 0) {
      nitrox_SaveSingleUser(tmp_i5,1);
      tmp_i5 = (&Users)[local_38];
    }
    nitrox_SetAdminPointers(param_1,tmp_i5);
  }
  return;
}

void G_AddClassSpecificTools_part_3(int param_1)
{
  int *tmp_pi1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  byte tmp_b4;
  byte tmp_b5;
  uint tmp_u6;
  int tmp_i7;
  uint32_t tmp_u8;
  int tmp_i9;
  uint32_t tmp_u10;
  
  tmp_u6 = *(uint *)(param_1 + 0xed0) >> 1;
  tmp_b5 = (byte)tmp_u6 & 1;
  tmp_i7 = ClientHasAdren(param_1);
  tmp_u8 = GHIDRA_FIELD(ammoTableMP, 3108, 4);
  if (tmp_i7 == 0) {
    tmp_i7 = *(int *)(param_1 + 0xbc8);
    tmp_i9 = tmp_i7 + -2;
    if (tmp_i7 == 2) goto LAB_00058161;
LAB_00057dfe:
    tmp_u3 = GHIDRA_FIELD(ammoTableMP, 2032, 4);
    tmp_u2 = GHIDRA_FIELD(ammoTableMP, 2028, 4);
    tmp_u10 = GHIDRA_FIELD(ammoTableMP, 808, 4);
    tmp_u8 = GHIDRA_FIELD(ammoTableMP, 804, 4);
    if (SBORROW4(tmp_i7,2) == tmp_i9 < 0) {
      if (tmp_i7 == 3) {
        if ((g_fieldOps[0xc] & 1) == 0) {
          tmp_b4 = 1;
        }
        else {
          tmp_b4 = 1;
          if ((*(byte *)(param_1 + 0xedc) & 2) == 0) {
            tmp_b4 = tmp_b5;
          }
        }
        tmp_b5 = tmp_b4;
        if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
          COM_BitSet(param_1 + 0x3d4,0xc);
          tmp_i7 = BG_FindClipForWeapon(0xc);
          *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = 1;
          tmp_i7 = BG_FindAmmoForWeapon(0xc);
          *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = 0;
          tmp_u8 = Bot_WeaponGameToBot(0xc);
          Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
          tmp_u10 = GHIDRA_FIELD(ammoTableMP, 1528, 4);
          tmp_u8 = GHIDRA_FIELD(ammoTableMP, 1524, 4);
          COM_BitSet(param_1 + 0x3d4,0x15);
          tmp_i7 = BG_FindClipForWeapon(0x15);
          *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = tmp_u10;
          tmp_i7 = BG_FindAmmoForWeapon(0x15);
          tmp_u10 = 0x15;
          *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = tmp_u8;
          goto LAB_0005849f;
        }
        goto LAB_00058330;
      }
      if (tmp_i7 != 4) goto LAB_00058330;
      if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
        COM_BitSet(param_1 + 0x3d4,0x1c);
        tmp_i7 = BG_FindClipForWeapon(0x1c);
        *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = tmp_u3;
        tmp_i7 = BG_FindAmmoForWeapon(0x1c);
        *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = tmp_u2;
        tmp_u8 = Bot_WeaponGameToBot(0x1c);
        Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
      }
      tmp_i7 = param_1 + 0x3d4;
      nitmod_AddNewWeapon(param_1,0x32);
      if ((GHIDRA_FIELD(g_gametype, 12, 4) != 8) || ((GHIDRA_FIELD(g_DMOptions, 12, 4) & 0x1000) != 0)) {
        tmp_i9 = G_FindSatchel(g_entities + *(int *)(param_1 + 0xa0) * 0x600);
        if (tmp_i9 == 0) {
          COM_BitSet(tmp_i7,0x1a);
          tmp_i9 = BG_FindClipForWeapon(0x1a);
          *(uint32_t *)(param_1 + 0x290 + tmp_i9 * 4) = 1;
          tmp_i9 = BG_FindAmmoForWeapon(0x1a);
          *(uint32_t *)(param_1 + 400 + tmp_i9 * 4) = 0;
          tmp_u8 = Bot_WeaponGameToBot(0x1a);
          Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
          COM_BitSet(tmp_i7,0x1b);
          tmp_i7 = BG_FindClipForWeapon(0x1b);
          *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = 0;
        }
        else {
          COM_BitSet(tmp_i7,0x1a);
          tmp_i9 = BG_FindClipForWeapon(0x1a);
          *(uint32_t *)(param_1 + 0x290 + tmp_i9 * 4) = 0;
          tmp_i9 = BG_FindAmmoForWeapon(0x1a);
          *(uint32_t *)(param_1 + 400 + tmp_i9 * 4) = 0;
          tmp_u8 = Bot_WeaponGameToBot(0x1a);
          Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
          COM_BitSet(tmp_i7,0x1b);
          tmp_i7 = BG_FindClipForWeapon(0x1b);
          *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = 1;
        }
        tmp_i7 = BG_FindAmmoForWeapon(0x1b);
        *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = 0;
        tmp_u8 = Bot_WeaponGameToBot(0x1b);
        Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
      }
      goto LAB_00057fad;
    }
    if ((tmp_i7 == 1) && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) {
      COM_BitSet(param_1 + 0x3d4,0xb);
      tmp_i7 = BG_FindClipForWeapon(0xb);
      *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = tmp_u10;
      tmp_i7 = BG_FindAmmoForWeapon(0xb);
      *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = tmp_u8;
      if ((3 < GHIDRA_FIELD(g_war, 12, 4) - 1) && ((*(byte *)(param_1 + 0xed8) & 4) != 0)) {
        tmp_i7 = BG_FindAmmoForWeapon(0xb);
        tmp_pi1 = (int *)(param_1 + 0x290 + tmp_i7 * 4);
        *tmp_pi1 = *tmp_pi1 + 2;
      }
      tmp_u8 = Bot_WeaponGameToBot(0xb);
      Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
      tmp_u10 = GHIDRA_FIELD(ammoTableMP, 1312, 4);
      tmp_u8 = GHIDRA_FIELD(ammoTableMP, 1308, 4);
      COM_BitSet(param_1 + 0x3d4,0x12);
      tmp_i7 = BG_FindClipForWeapon(0x12);
      *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = tmp_u10;
      tmp_i7 = BG_FindAmmoForWeapon(0x12);
      tmp_u10 = 0x12;
      *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = tmp_u8;
LAB_0005849f:
      tmp_u8 = Bot_WeaponGameToBot(tmp_u10);
      Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
    }
LAB_00058330:
    tmp_i7 = GHIDRA_FIELD(g_war, 12, 4);
    if (tmp_b5 != 0) {
LAB_00057fad:
      COM_BitSet(param_1 + 0x3d4,0x13);
      tmp_i7 = BG_FindClipForWeapon(0x13);
      *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = 0;
      tmp_i7 = BG_FindAmmoForWeapon(0x13);
      *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = 1;
      tmp_u8 = Bot_WeaponGameToBot(0x13);
      Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
      tmp_i7 = GHIDRA_FIELD(g_war, 12, 4);
      *(uint *)(param_1 + 0xd4) = *(uint *)(param_1 + 0xd4) | 0x40;
    }
    if (tmp_i7 - 1U < 4) goto LAB_00058020;
  }
  else {
    if ((GHIDRA_FIELD(g_adrenaline, 12, 4) & 4) == 0) {
      tmp_u10 = GHIDRA_FIELD(ammoTableMP, 3112, 4);
      if ((GHIDRA_FIELD(g_adrenaline, 12, 4) & 1) != 0) {
        tmp_u10 = 0;
      }
    }
    else {
      tmp_u10 = 1;
    }
    COM_BitSet(param_1 + 0x3d4,0x2b);
    tmp_i7 = BG_FindClipForWeapon(0x2b);
    *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = tmp_u10;
    tmp_i7 = BG_FindAmmoForWeapon(0x2b);
    *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = tmp_u8;
    if ((3 < GHIDRA_FIELD(g_war, 12, 4) - 1) && ((*(byte *)(param_1 + 0xed8) & 4) != 0)) {
      tmp_i7 = BG_FindAmmoForWeapon(0x2b);
      tmp_pi1 = (int *)(param_1 + 0x290 + tmp_i7 * 4);
      *tmp_pi1 = *tmp_pi1 + 2;
    }
    tmp_u8 = Bot_WeaponGameToBot(0x2b);
    Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
    tmp_i7 = *(int *)(param_1 + 0xbc8);
    tmp_i9 = tmp_i7 + -2;
    if (tmp_i9 != 0) goto LAB_00057dfe;
LAB_00058161:
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
LAB_000585f0:
      if ((GHIDRA_FIELD(g_DMOptions, 12, 4) & 0xb00) != 0) {
        COM_BitSet(param_1 + 0x3d4,0x14);
        tmp_i7 = BG_FindClipForWeapon(0x14);
        *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = 1;
        tmp_i7 = BG_FindAmmoForWeapon(0x14);
        *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = 0;
        tmp_u8 = Bot_WeaponGameToBot(0x14);
        Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
      }
      tmp_u10 = GHIDRA_FIELD(ammoTableMP, 1816, 4);
      tmp_u8 = GHIDRA_FIELD(ammoTableMP, 1812, 4);
      if ((GHIDRA_FIELD(g_DMOptions, 12, 4) & 0x100) != 0) {
        COM_BitSet(param_1 + 0x3d4,0x19);
        tmp_i7 = BG_FindClipForWeapon(0x19);
        *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = tmp_u10;
        tmp_i7 = BG_FindAmmoForWeapon(0x19);
        *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = tmp_u8;
        tmp_u8 = Bot_WeaponGameToBot(0x19);
        Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
      }
      tmp_u10 = GHIDRA_FIELD(ammoTableMP, 3472, 4);
      tmp_u8 = GHIDRA_FIELD(ammoTableMP, 3468, 4);
      if ((((GHIDRA_FIELD(g_DMOptions, 12, 4) & 0x2000) != 0) && ((*(byte *)(param_1 + 0xed4) & 0x20) != 0)) &&
         ((g_weapons[0xc] & 4) != 0)) {
        COM_BitSet(param_1 + 0x3d4,0x30);
        tmp_i7 = BG_FindClipForWeapon(0x30);
        *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = tmp_u10;
        tmp_i7 = BG_FindAmmoForWeapon(0x30);
        *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = tmp_u8;
        tmp_u8 = Bot_WeaponGameToBot(0x30);
        Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
      }
    }
    else {
      tmp_i7 = param_1 + 0x3d4;
      COM_BitSet(tmp_i7,0xf);
      tmp_i9 = BG_FindClipForWeapon(0xf);
      *(uint32_t *)(param_1 + 0x290 + tmp_i9 * 4) = 1;
      tmp_i9 = BG_FindAmmoForWeapon(0xf);
      *(uint32_t *)(param_1 + 400 + tmp_i9 * 4) = 0;
      tmp_u8 = Bot_WeaponGameToBot(0xf);
      Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
      COM_BitSet(tmp_i7,0x14);
      tmp_i9 = BG_FindClipForWeapon(0x14);
      *(uint32_t *)(param_1 + 0x290 + tmp_i9 * 4) = 1;
      tmp_i9 = BG_FindAmmoForWeapon(0x14);
      *(uint32_t *)(param_1 + 400 + tmp_i9 * 4) = 0;
      tmp_u8 = Bot_WeaponGameToBot(0x14);
      Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
      tmp_u10 = GHIDRA_FIELD(ammoTableMP, 1816, 4);
      tmp_u8 = GHIDRA_FIELD(ammoTableMP, 1812, 4);
      COM_BitSet(tmp_i7,0x19);
      tmp_i9 = BG_FindClipForWeapon(0x19);
      *(uint32_t *)(param_1 + 0x290 + tmp_i9 * 4) = tmp_u10;
      tmp_i9 = BG_FindAmmoForWeapon(0x19);
      *(uint32_t *)(param_1 + 400 + tmp_i9 * 4) = tmp_u8;
      tmp_u8 = Bot_WeaponGameToBot(0x19);
      Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
      tmp_u10 = GHIDRA_FIELD(ammoTableMP, 3472, 4);
      tmp_u8 = GHIDRA_FIELD(ammoTableMP, 3468, 4);
      if (((*(byte *)(param_1 + 0xed4) & 0x20) != 0) && ((g_weapons[0xc] & 4) != 0)) {
        COM_BitSet(tmp_i7,0x30);
        tmp_i7 = BG_FindClipForWeapon(0x30);
        *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = tmp_u10;
        tmp_i7 = BG_FindAmmoForWeapon(0x30);
        *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = tmp_u8;
        tmp_u8 = Bot_WeaponGameToBot(0x30);
        Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
      }
      if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) goto LAB_000585f0;
    }
    nitmod_AddNewWeapon(param_1,0x31);
    nitmod_AddNewWeapon(param_1,0x33);
    if ((*(byte *)(param_1 + 0xed4) & 0x10) == 0) goto LAB_00058330;
    if (GHIDRA_FIELD(g_war, 12, 4) - 1 < 4) {
      if ((tmp_u6 & 1) == 0) goto LAB_00058020;
      goto LAB_00057fad;
    }
    if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
      *(uint32_t *)(param_1 + 0x158) = 0x7fffffff;
      goto LAB_00058330;
    }
    if ((tmp_u6 & 1) != 0) goto LAB_00057fad;
  }
  if (((GHIDRA_FIELD(g_gametype, 12, 4) != 8) && (*(int *)(param_1 + 0xbc8) != 2)) &&
     (((jp_keepAwards[0xc] & 1) != 0 && ((*(byte *)(param_1 + 0xed4) & 0x10) != 0)))) {
    *(uint32_t *)(param_1 + 0x158) = 0x7fffffff;
  }
LAB_00058020:
  tmp_u10 = GHIDRA_FIELD(ammoTableMP, 3400, 4);
  tmp_u8 = GHIDRA_FIELD(ammoTableMP, 3396, 4);
  if ((GHIDRA_FIELD(g_poison, 12, 4) != 0) && ((*(byte *)(param_1 + 0xee0) & 0x10) != 0)) {
    COM_BitSet(param_1 + 0x3d4,0x2f);
    tmp_i7 = BG_FindClipForWeapon(0x2f);
    *(uint32_t *)(param_1 + 0x290 + tmp_i7 * 4) = tmp_u10;
    tmp_i7 = BG_FindAmmoForWeapon(0x2f);
    *(uint32_t *)(param_1 + 400 + tmp_i7 * 4) = tmp_u8;
    tmp_u8 = Bot_WeaponGameToBot(0x2f);
    Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u8);
  }
  return;
}

void G_BodyDP(uint32_t *param_1)
{
  int tmp_i1;
  
  tmp_i1 = nitrox_TempEventFromQueue(param_1 + 0x5a,0x5e);
  *(uint32_t *)(tmp_i1 + 0x90) = *param_1;
  *(uint32_t *)(tmp_i1 + 0x128) = 0x20;
  G_FreeEntity(param_1);
  return;
}

void G_DropLimboHealth(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  uint tmp_u3;
  int local_48;
  float local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  if ((((GHIDRA_FIELD(g_dropHealth, 12, 4) != 0) && (3 < GHIDRA_FIELD(g_war, 12, 4) - 1)) && (*(int *)(param_1 + 400) != 0)) &&
     ((tmp_i2 = IsClass(param_1,1), tmp_i2 != 0 && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)))) {
    local_48 = GHIDRA_FIELD(g_dropHealth, 12, 4);
    if ((int)GHIDRA_FIELD(g_dropHealth, 12, 4) < 10) {
      if ((int)GHIDRA_FIELD(g_dropHealth, 12, 4) < 1) {
        return;
      }
    }
    else {
      local_48 = 10;
    }
    tmp_i2 = 0;
    do {
      tmp_u3 = rand();
      tmp_i2 = tmp_i2 + 1;
      local_34 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
      local_34 = local_34 + local_34;
      tmp_u3 = rand();
      local_2c = 0x41c80000;
      local_34 = local_34 * 100.0;
      tmp_f1 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
      local_30 = (tmp_f1 + tmp_f1) * 100.0;
      local_28 = *(uint32_t *)(param_1 + 0x168);
      local_24 = *(uint32_t *)(param_1 + 0x16c);
      local_20 = *(uint32_t *)(param_1 + 0x170);
      Weapon_Medic_Ext(param_1,&local_28,&local_28,&local_34);
    } while (tmp_i2 < local_48);
  }
  return;
}

uint32_t G_AddClassSpecificTools(uint32_t param_1)
{
  uint32_t tmp_u1;
  
  if (3 < GHIDRA_FIELD(g_war, 12, 4) - 1) {
    tmp_u1 = G_AddClassSpecificTools_part_3();
    return tmp_u1;
  }
  return param_1;
}

int G_CountTeamMedics(int param_1,int param_2)
{
  int tmp_i1;
  int *tmp_pi2;
  int *tmp_pi3;
  int tmp_i4;
  int local_14;
  
  if (g_unk_00abe93c < 1) {
    local_14 = 0;
  }
  else {
    tmp_pi2 = &g_unk_00abe944 + g_unk_00abe93c;
    tmp_pi3 = &g_unk_00abe944;
    if (param_2 == 0) {
      tmp_i4 = 0;
      do {
        while (tmp_i1 = *tmp_pi3 * 0x54dc + level, *(int *)(tmp_i1 + 3000) != param_1) {
          tmp_pi3 = tmp_pi3 + 1;
          if (tmp_pi3 == tmp_pi2) {
            return tmp_i4;
          }
        }
        tmp_pi3 = tmp_pi3 + 1;
        tmp_i4 = tmp_i4 + (uint)(*(int *)(tmp_i1 + 0xbc8) == 1);
      } while (tmp_pi3 != tmp_pi2);
      return tmp_i4;
    }
    local_14 = 0;
    do {
      while( true ) {
        tmp_i4 = *tmp_pi3 * 0x54dc + level;
        if ((((*(int *)(tmp_i4 + 3000) != param_1) || (*(int *)(tmp_i4 + 0xbc8) != 1)) ||
            (*(int *)(g_entities + *tmp_pi3 * 0x600 + 0x2c8) < 1)) || (*(int *)(tmp_i4 + 4) == 3))
        break;
        local_14 = local_14 + (uint)((*(uint *)(tmp_i4 + 0xc) & 0x4000) == 0);
        tmp_pi3 = tmp_pi3 + 1;
        if (tmp_pi3 == tmp_pi2) {
          return local_14;
        }
      }
      tmp_pi3 = tmp_pi3 + 1;
    } while (tmp_pi3 != tmp_pi2);
  }
  return local_14;
}

void G_SetDefaultLevel(int param_1)
{
  if ((param_1 != 0) && (g_unk_02af58b8 != 0)) {
    G_SetDefaultLevel_part_4();
    return;
  }
  return;
}

int G_ComputeMaxLives(int param_1,int param_2)
{
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i2 = param_2 + -1;
  if ((float)GHIDRA_FIELD(g_timelimit, 8, 4) != 0.0) {
    if ((float)GHIDRA_FIELD(g_timelimit, 8, 4) * 60000.0 <= (float)(g_unk_00abe908 - g_unk_00abe918)) {
      tmp_i2 = -1;
    }
    else {
      tmp_f1 = (1.0 - (float)(g_unk_00abe908 - g_unk_00abe918) / ((float)GHIDRA_FIELD(g_timelimit, 8, 4) * 60000.0)) *
              (float)(param_2 + -1);
      tmp_i3 = (int)ROUND(tmp_f1);
      tmp_i3 = (uint)(0.5 <= tmp_f1 - (float)tmp_i3) + tmp_i3;
      tmp_i2 = tmp_i3;
      if (((g_XPSave[0xc] & 1) != 0) &&
         ((tmp_i2 = *(int *)(param_1 + 0x537c), tmp_i3 <= tmp_i2 || (tmp_i2 == -999)))) {
        return tmp_i3;
      }
    }
  }
  return tmp_i2;
}

void G_ShortcutSanitize_part_7(uint32_t param_1)
{
  uint32_t tmp_u1;
  
  Q_strncpyz(n_14038,param_1,0x96);
  tmp_u1 = Q_StrReplace(n_14038,&g_unk_002457e4,&g_unk_002457e0);
  Q_strncpyz(n_14038,tmp_u1,0x96);
  tmp_u1 = Q_StrReplace(n_14038,&g_unk_002457ec,&g_unk_002457e8);
  Q_strncpyz(n_14038,tmp_u1,0x96);
  tmp_u1 = Q_StrReplace(n_14038,&g_unk_002457f4,&g_unk_002457f0);
  Q_strncpyz(n_14038,tmp_u1,0x96);
  tmp_u1 = Q_StrReplace(n_14038,&g_unk_002457fc,&g_unk_002457f8);
  Q_strncpyz(n_14038,tmp_u1,0x96);
  tmp_u1 = Q_StrReplace(n_14038,&g_unk_00245804,&g_unk_00245800);
  Q_strncpyz(n_14038,tmp_u1,0x96);
  tmp_u1 = Q_StrReplace(n_14038,&g_unk_0024580c,&g_unk_00245808);
  Q_strncpyz(n_14038,tmp_u1,0x96);
  tmp_u1 = Q_StrReplace(n_14038,&g_unk_00245814,&g_unk_00245810);
  Q_strncpyz(n_14038,tmp_u1,0x96);
  tmp_u1 = Q_StrReplace(n_14038,&g_unk_0024581c,&g_unk_00245818);
  Q_strncpyz(n_14038,tmp_u1,0x96);
  tmp_u1 = Q_StrReplace(n_14038,&g_unk_00245820,"(s)");
  Q_strncpyz(n_14038,tmp_u1,0x96);
  tmp_u1 = Q_StrReplace(n_14038,&g_unk_00245828,&g_unk_00245824);
  Q_strncpyz(n_14038,tmp_u1,0x96);
  return;
}

uint32_t G_CensorText(char *param_1,char *param_2)
{
  char tmp_c1;
  bool tmp_b2;
  bool tmp_b3;
  size_t tmp_s4;
  int tmp_i5;
  char *tmp_pc6;
  char *__s;
  uint32_t tmp_u7;
  int local_28;
  
  tmp_u7 = 0;
LAB_00061580:
  tmp_c1 = *param_1;
  do {
    if (tmp_c1 == '\0') {
      return tmp_u7;
    }
    if (0 < *(int *)(param_2 + 1000)) {
      local_28 = 0;
      tmp_b2 = false;
      tmp_pc6 = param_1;
      __s = param_2;
      do {
        tmp_s4 = strlen(__s);
        tmp_i5 = Q_stricmpn(tmp_pc6,__s,tmp_s4);
        param_1 = tmp_pc6;
        if (tmp_i5 == 0) {
          tmp_b3 = true;
          if (*(int *)(param_2 + 1000) + -1 != local_28) {
            tmp_b3 = tmp_b2;
          }
          for (; tmp_b2 = tmp_b3, tmp_s4 = strlen(__s), (uint)((int)param_1 - (int)tmp_pc6) < tmp_s4;
              param_1 = param_1 + 1) {
            *param_1 = '*';
            tmp_b3 = tmp_b2;
          }
          tmp_u7 = 1;
        }
        local_28 = local_28 + 1;
      } while ((local_28 < *(int *)(param_2 + 1000)) &&
              (__s = __s + 0x14, tmp_pc6 = param_1, *param_1 != '\0'));
      if (tmp_b2) goto LAB_00061580;
    }
    param_1 = param_1 + 1;
    tmp_c1 = *param_1;
  } while( true );
}

void G_CensorPenalize(uint32_t *param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_i2 = param_1[100];
  if (tmp_i2 == 0) {
    return;
  }
  if ((GHIDRA_FIELD(g_censorPenalty, 12, 4) & 0x40) == 0) {
LAB_00061780:
    if ((GHIDRA_FIELD(g_censorPenalty, 12, 4) & 0x20) != 0) {
      if (*(int *)(param_1[100] + 3000) == 3) goto joined_r0x000616f2;
      if ((*(byte *)(param_1[100] + 0xd) & 0x40) == 0) {
LAB_000616ca:
        if ((-1 < (int)param_1[0xb2]) && (g_unk_02a99a78 == 0)) {
          G_BurnMeGood(param_1,param_1,0);
          tmp_u1 = va("pop \"^8CENSOR WARNING: ^7%s ^7burned his tongue.\"",param_1[100] + 0x5f8);
          trap_SendServerCommand(0xffffffff,tmp_u1);
          goto LAB_00061800;
        }
      }
      goto joined_r0x000617a3;
    }
LAB_00061800:
    if (((GHIDRA_FIELD(g_censorPenalty, 12, 4) & 0x10) == 0) || (*(int *)(param_1[100] + 3000) == 3))
    goto joined_r0x000616f2;
  }
  else {
    if (*(int *)(tmp_i2 + 3000) == 3) goto joined_r0x000616f2;
    if ((*(byte *)(tmp_i2 + 0xd) & 0x40) == 0) {
      if ((-1 < (int)param_1[0xb2]) && (g_unk_02a99a78 == 0)) {
        *(uint32_t *)(tmp_i2 + 0x5300) = *param_1;
        *(uint *)(param_1[100] + 0x68) = *(uint *)(param_1[100] + 0x68) | 0x200000;
        *(uint32_t *)(param_1[100] + 0x5304) = 1;
        tmp_u1 = va("pop \"^8CENSOR WARNING: ^7%s ^7poisoned his dirty mouth.\"",param_1[100] + 0x5f8
                  );
        trap_SendServerCommand(0xffffffff,tmp_u1);
        goto LAB_00061780;
      }
      if ((GHIDRA_FIELD(g_censorPenalty, 12, 4) & 0x20) != 0) goto LAB_000616ca;
    }
joined_r0x000617a3:
    if ((GHIDRA_FIELD(g_censorPenalty, 12, 4) & 0x10) == 0) goto joined_r0x000616f2;
  }
  trap_SendServerCommand
            (((int)(param_1 + -0x24f928) >> 9) * -0x55555555,
             "pop \"^8CENSOR WARNING: ^7Watch your mouth! You have lost 10 XP.\"");
  tmp_u1 = BG_ClassSkillForClass(*(uint32_t *)(param_1[100] + 0xbc8));
  G_LoseSkillPoints(param_1,tmp_u1,0x41200000);
joined_r0x000616f2:
  if ((GHIDRA_FIELD(g_censorPenalty, 12, 4) & 8) != 0) {
    tmp_i2 = ((int)(param_1 + -0x24f928) >> 9) * -0x55555555;
    tmp_u1 = va("!mute %i %d CensorPenalty\n",tmp_i2,GHIDRA_FIELD(g_censorMuteTime, 12, 4));
    trap_SendConsoleCommand(2,tmp_u1);
    *(uint32_t *)(param_1[100] + 0xbf0) = 1;
    *(uint32_t *)(param_1[100] + 0xca4) = g_unk_00abe908;
    tmp_u1 = va("print \"^9You\'ve been auto-muted for %d seconds for language.\n\"",
               GHIDRA_FIELD(g_censorMuteTime, 12, 4));
    trap_SendServerCommand(tmp_i2,tmp_u1);
    tmp_u1 = va("pop \"^8CENSOR WARNING: ^7%s^9 has been auto-muted for %d seconds.\"",
               param_1[100] + 0x5f8,GHIDRA_FIELD(g_censorMuteTime, 12, 4));
    trap_SendServerCommand(0xffffffff,tmp_u1);
  }
  if ((GHIDRA_FIELD(g_censorPenalty, 12, 4) & 1) == 0) {
    if ((GHIDRA_FIELD(g_censorPenalty, 12, 4) & 4) != 0) {
      param_1[0xb2] = 0;
      param_1[0x6c] = param_1[0x6c] & 0xffffffef;
      *(uint32_t *)(param_1[100] + 0xd0) = 0;
      *(uint32_t *)(param_1[100] + 0x140) = 0;
      G_Damage(param_1,param_1,param_1,0,0,param_1[0xb2],0,0x3d);
    }
  }
  else {
    tmp_i2 = param_1[100];
    if ((((*(int *)(tmp_i2 + 3000) != 3) && ((*(byte *)(tmp_i2 + 0xd) & 0x40) == 0)) &&
        (0 < (int)param_1[0xb2])) && (g_unk_02a99a78 == 0)) {
      param_1[0x6c] = param_1[0x6c] & 0xffffffef;
      param_1[0xb2] = 0xfffffe0c;
      *(uint32_t *)(tmp_i2 + 0xd0) = 0xfffffe0c;
      *(uint32_t *)(param_1[100] + 0x140) = 0;
      player_die(param_1,param_1,param_1,(-(uint)(GHIDRA_FIELD(g_gamestate, 12, 4) == 0) & 0x18619) + 0x87,0x3d);
    }
  }
  return;
}

void G_PlayDead(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 400);
  if ((((tmp_i1 != 0) && (-1 < *(int *)(param_1 + 0x2c8))) &&
      ((*(uint *)(tmp_i1 + 0x68) & 0x200000) == 0)) && (*(int *)(tmp_i1 + 0x30) == 0)) {
    if ((*(uint *)(tmp_i1 + 0x68) & 0x800000) == 0) {
      if (GHIDRA_FIELD(g_playDead, 12, 4) == 0) {
        return;
      }
      if (*(int *)(tmp_i1 + 4) != 0) {
        return;
      }
    }
    else if (*(int *)(tmp_i1 + 4) != 3) {
      return;
    }
    if ((*(byte *)(tmp_i1 + 0xd) & 0x80) == 0) {
      *(uint32_t *)(tmp_i1 + 4) = 6;
      *(uint32_t *)(param_1 + 0x14c) = 0x4000000;
    }
  }
  return;
}

void G_TeamDamageStats(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  float tmp_f3;
  uint32_t tmp_u4;
  
  tmp_i2 = *(int *)(param_1 + 400);
  if (tmp_i2 != 0) {
    tmp_f1 = *(float *)(tmp_i2 + 0xca0);
    tmp_f3 = 0.0;
    if (tmp_f1 != 0.0) {
      tmp_f3 = (*(float *)(tmp_i2 + 0xc9c) / tmp_f1) * 100.0;
    }
    tmp_u4 = va("print \"Team Hits: %.2f Total Hits: %.2f Pct: %.2f Limit: %d\n\"",
               (double)*(float *)(tmp_i2 + 0xc9c),(double)tmp_f1,(double)tmp_f3,
               GHIDRA_FIELD(g_teamDamageRestriction, 12, 4));
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
  }
  return;
}

uint32_t G_SendScore_Add(uint32_t param_1,int param_2,char *param_3,uint param_4)
{
  uint tmp_u1;
  size_t tmp_s2;
  int tmp_i3;
  int tmp_i4;
  uint *tmp_pu5;
  uint *tmp_pu6;
  int tmp_i7;
  uint tmp_u8;
  int tmp_i9;
  int local_b0;
  uint32_t local_ac;
  uint local_9c [34];
  uint32_t uStack_14;
  
  uStack_14 = 0x61b89;
  local_9c[0]._0_1_ = 0;
  tmp_i4 = (&g_unk_00abe8a4)[param_2 + 0x28];
  tmp_i9 = tmp_i4 * 0x54dc + level;
  tmp_i7 = *(int *)(tmp_i9 + 0x134);
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
    if (*(int *)(g_entities + tmp_i4 * 0x600 + 0x2c8) < 1) {
      tmp_i7 = -2;
    }
    if (*(int *)(tmp_i9 + 0x5ac) == 1) {
      local_ac = 0xffffffff;
    }
    else {
      local_ac = 999;
      if (*(int *)(tmp_i9 + 0x9e8) < 1000) {
        local_ac = *(uint32_t *)(tmp_i9 + 0x9e8);
      }
    }
    local_b0 = *(int *)(tmp_i9 + 0x110);
  }
  else {
    if (tmp_i7 == 0) {
      if ((*(byte *)(tmp_i9 + 0xd) & 0x40) == 0) {
        if ((g_unk_00abf994 != 0) && (*(int *)(g_entities + tmp_i4 * 0x600 + 0x2c8) < 1)) {
          tmp_i7 = -2;
        }
      }
      else {
        tmp_i7 = -2;
      }
    }
    if (*(int *)(tmp_i9 + 0x5ac) == 1) {
      local_ac = 0xffffffff;
    }
    else {
      local_ac = 999;
      if (*(int *)(tmp_i9 + 0x9e8) < 1000) {
        local_ac = *(uint32_t *)(tmp_i9 + 0x9e8);
      }
    }
    local_b0 = (int)ROUND((float)(int)ROUND((float)(int)ROUND((float)(int)ROUND((float)(int)ROUND((
                                                  float)(int)ROUND((float)(int)ROUND(*(float *)(
                                                  tmp_i9 + 0xbf4) + 0.0) + *(float *)(tmp_i9 + 0xbf8))
                                                  + *(float *)(tmp_i9 + 0xbfc)) +
                                                  *(float *)(tmp_i9 + 0xc00)) +
                                                  *(float *)(tmp_i9 + 0xc04)) +
                                            *(float *)(tmp_i9 + 0xc08)) + *(float *)(tmp_i9 + 0xc0c));
  }
  tmp_u1 = *(uint *)(tmp_i9 + 0x68) >> 3 & 1;
  tmp_u8 = tmp_u1 | 2;
  if ((g_entities[tmp_i4 * 0x600 + 0x128] & 8) == 0) {
    tmp_u8 = tmp_u1;
  }
  if (*(int *)(tmp_i9 + 0xbf0) == 0) {
    tmp_i3 = G_shrubbot_mute_check(tmp_i9 + 0x61c,tmp_i9 + 0xaf4);
    tmp_i4 = (&g_unk_00abe8a4)[param_2 + 0x28];
    if (tmp_i3 == 0) goto LAB_00061ceb;
  }
  tmp_u8 = tmp_u8 | 4;
LAB_00061ceb:
  Com_sprintf(local_9c,0x80," %i %i %i %i %i %i %i",tmp_i4,local_b0,local_ac,
              (g_unk_00abe908 - *(int *)(tmp_i9 + 0x674)) / 60000,
              *(uint32_t *)(g_entities + tmp_i4 * 0x600 + 0xe4),tmp_u8,tmp_i7);
  tmp_s2 = strlen(param_3);
  tmp_pu6 = local_9c;
  do {
    tmp_pu5 = tmp_pu6;
    tmp_u1 = *tmp_pu5 + 0xfefefeff & ~*tmp_pu5;
    tmp_u8 = tmp_u1 & 0x80808080;
    tmp_pu6 = tmp_pu5 + 1;
  } while (tmp_u8 == 0);
  if ((tmp_u1 & 0x8080) == 0) {
    tmp_pu6 = (uint *)((int)tmp_pu5 + 6);
    tmp_u8 = tmp_u8 >> 0x10;
  }
  if (param_4 < (int)tmp_pu6 + tmp_s2 + (-(int)local_9c - (uint)CARRY1((byte)tmp_u8,(byte)tmp_u8)) + -2)
  {
    return 0;
  }
  Q_strcat(param_3,param_4,local_9c);
  return 1;
}

void G_SendScore(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  int local_42c;
  uint8_t local_417 [32];
  uint8_t local_3f7 [995];
  uint32_t uStack_14;
  
  tmp_i5 = g_unk_00abe938;
  uStack_14 = 0x61efb;
  local_3f7[0] = 0;
  local_417[0] = 0;
  Q_strncpyz(local_417,&g_unk_00245859,0x20);
  tmp_i3 = 0;
  if (tmp_i5 < 1) {
    tmp_u2 = va("%s %i%s",local_417,0,local_3f7);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
    if (tmp_i5 != 0) {
      local_3f7[0] = 0;
      local_417[0] = 0;
      Q_strncpyz(local_417,&g_unk_00245865,0x20);
    }
  }
  else {
    do {
      tmp_i1 = G_SendScore_Add(param_1,tmp_i3,local_3f7,0x3db);
      tmp_i4 = tmp_i3;
      if (tmp_i1 == 0) goto LAB_00061f95;
      tmp_i4 = tmp_i3 + 1;
      if (tmp_i4 == tmp_i5) {
        tmp_u2 = va("%s %i%s",local_417,tmp_i4,local_3f7);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
        return;
      }
      tmp_i3 = tmp_i4;
    } while (tmp_i4 != 0x21);
    tmp_i3 = 0x21;
LAB_00061f95:
    tmp_u2 = va("%s %i%s",local_417,tmp_i3,local_3f7);
    tmp_i3 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand(tmp_i3,tmp_u2);
    local_3f7[0] = 0;
    local_417[0] = 0;
    Q_strncpyz(local_417,&g_unk_00245865,0x20);
    local_42c = tmp_i5 - tmp_i4;
    if (tmp_i4 < tmp_i5) {
      tmp_i5 = 0;
      do {
        tmp_i1 = G_SendScore_Add(param_1,tmp_i5 + tmp_i4,local_3f7,0x3db);
        if (tmp_i1 == 0) {
          G_Printf("ERROR: G_SendScore() buffer overflow\n");
          local_42c = tmp_i5;
          break;
        }
        tmp_i5 = tmp_i5 + 1;
      } while (tmp_i5 != local_42c);
      if (local_42c != 0) {
        tmp_u2 = va("%s %i%s",local_417,local_42c,local_3f7);
        trap_SendServerCommand(tmp_i3,tmp_u2);
        return;
      }
    }
  }
  return;
}

bool G_SendKD_Add(uint32_t param_1,int param_2,char *param_3,uint param_4)
{
  bool tmp_b1;
  int tmp_i2;
  size_t tmp_s3;
  uint *tmp_pu4;
  uint *tmp_pu5;
  uint tmp_u6;
  uint tmp_u7;
  uint local_9c [35];
  
  local_9c[0]._0_1_ = 0;
  tmp_i2 = (&g_unk_00abe944)[param_2] * 0x54dc + level;
  Com_sprintf(local_9c,0x80," %i %i %i",(&g_unk_00abe944)[param_2],*(uint32_t *)(tmp_i2 + 0xc7c),
              *(uint32_t *)(tmp_i2 + 0xc74));
  tmp_s3 = strlen(param_3);
  tmp_pu5 = local_9c;
  do {
    tmp_pu4 = tmp_pu5;
    tmp_u6 = *tmp_pu4 + 0xfefefeff & ~*tmp_pu4;
    tmp_u7 = tmp_u6 & 0x80808080;
    tmp_pu5 = tmp_pu4 + 1;
  } while (tmp_u7 == 0);
  if ((tmp_u6 & 0x8080) == 0) {
    tmp_pu5 = (uint *)((int)tmp_pu4 + 6);
    tmp_u7 = tmp_u7 >> 0x10;
  }
  tmp_b1 = (int)tmp_pu5 + tmp_s3 + (-(int)local_9c - (uint)CARRY1((byte)tmp_u7,(byte)tmp_u7)) + -2 <=
          param_4;
  if (tmp_b1) {
    Q_strcat(param_3,param_4,local_9c);
  }
  return tmp_b1;
}

void G_SendKD(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  size_t tmp_s3;
  size_t tmp_s4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  char *local_4bc;
  int local_4b8;
  int local_4a4;
  uint8_t local_497 [32];
  char local_477 [128];
  char local_3f7 [995];
  uint32_t uStack_14;
  
  tmp_i1 = g_unk_00abe938;
  uStack_14 = 0x622ab;
  local_497[0] = 0;
  local_3f7[0] = '\0';
  Q_strncpyz(local_497,&g_unk_00245869,0x20);
  if (tmp_i1 < 1) {
    tmp_i7 = 0;
LAB_00062395:
    tmp_u5 = va("%s %i%s",local_497,tmp_i7,local_3f7);
    local_4a4 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand(local_4a4,tmp_u5);
    if (tmp_i7 != tmp_i1) {
      local_3f7[0] = '\0';
      local_497[0] = 0;
      Q_strncpyz(local_497,&g_unk_0024586d,0x20);
      if (tmp_i7 < tmp_i1) goto LAB_000624b1;
    }
    return;
  }
  tmp_i7 = 0;
  do {
    local_477[0] = '\0';
    tmp_i2 = (&g_unk_00abe944)[tmp_i7] * 0x54dc + level;
    Com_sprintf(local_477,0x80," %i %i %i",(&g_unk_00abe944)[tmp_i7],*(uint32_t *)(tmp_i2 + 0xc7c),
                *(uint32_t *)(tmp_i2 + 0xc74));
    tmp_s3 = strlen(local_3f7);
    tmp_s4 = strlen(local_477);
    if (0x3db < tmp_s3 + 1 + tmp_s4) goto LAB_00062395;
    tmp_i7 = tmp_i7 + 1;
    Q_strcat(local_3f7,0x3db,local_477);
    if (tmp_i7 == tmp_i1) {
      tmp_u5 = va("%s %i%s",local_497,tmp_i7,local_3f7);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
      return;
    }
  } while (tmp_i7 != 0x21);
  tmp_u5 = va("%s %i%s",local_497,0x21,local_3f7);
  local_4a4 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  trap_SendServerCommand(local_4a4,tmp_u5);
  local_3f7[0] = '\0';
  local_497[0] = 0;
  Q_strncpyz(local_497,&g_unk_0024586d,0x20);
LAB_000624b1:
  local_4bc = local_3f7;
  local_4b8 = 0;
  tmp_i2 = tmp_i7;
  do {
    local_477[0] = '\0';
    tmp_i6 = (&g_unk_00abe944)[tmp_i2] * 0x54dc + level;
    Com_sprintf(local_477,0x80," %i %i %i",(&g_unk_00abe944)[tmp_i2],*(uint32_t *)(tmp_i6 + 0xc7c),
                *(uint32_t *)(tmp_i6 + 0xc74));
    tmp_s3 = strlen(local_4bc);
    tmp_s4 = strlen(local_477);
    if (0x3db < tmp_s3 + 1 + tmp_s4) {
      G_Printf("ERROR: G_SendScore() buffer overflow\n");
      if (local_4b8 == 0) {
        return;
      }
      break;
    }
    Q_strcat(local_4bc,0x3db,local_477);
    local_4b8 = local_4b8 + 1;
    tmp_i2 = local_4b8 + tmp_i7;
  } while (tmp_i2 < tmp_i1);
  tmp_u5 = va("%s %i%s",local_497,local_4b8,local_4bc);
  trap_SendServerCommand(local_4a4,tmp_u5);
  return;
}

uint32_t G_MatchOnePlayer(int *param_1,char *param_2,uint param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  size_t tmp_s3;
  size_t tmp_s4;
  int tmp_i5;
  char local_4a [58];
  
  local_4a[0] = '\0';
  *param_2 = '\0';
  if (*param_1 == -1) {
    Q_strcat(param_2,param_3,"^1error: ^9Player not found.^7");
    tmp_u1 = 0;
  }
  else {
    tmp_u1 = 1;
    if (param_1[1] != -1) {
      Q_strcat(param_2,param_3,
               "^1error: ^9more than one player name matches. be more specific or use the slot #:");
      tmp_i5 = *param_1;
      while (tmp_i5 != -1) {
        while (tmp_i2 = tmp_i5 * 0x54dc + level, *(int *)(tmp_i2 + 0x5ac) != 2) {
          param_1 = param_1 + 1;
          tmp_i5 = *param_1;
          if (tmp_i5 == -1) goto LAB_00062970;
        }
        Com_sprintf(local_4a,0x2e,"^9%2i ^7- %s^7",tmp_i5,tmp_i2 + 0x5f8);
        tmp_s3 = strlen(param_2);
        tmp_s4 = strlen(local_4a);
        if (param_3 < tmp_s4 + tmp_s3) break;
        param_1 = param_1 + 1;
        Q_strcat(param_2,param_3,local_4a);
        tmp_i5 = *param_1;
      }
LAB_00062970:
      tmp_u1 = 0;
    }
  }
  return tmp_u1;
}

void G_PlaySound_Cmd(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char local_570 [36];
  uint8_t local_54c [64];
  int local_50c [64];
  uint8_t local_40c [1024];
  
  tmp_i1 = trap_Argc();
  if (tmp_i1 < 2) {
    G_Printf("usage: playsound [name|slot#] sound\n");
  }
  else {
    tmp_i1 = trap_Argc();
    if (tmp_i1 < 3) {
      trap_Argv(1,local_54c,0x40);
      local_570[0] = '\0';
    }
    else {
      trap_Argv(1,local_570,0x24);
      trap_Argv(2,local_54c,0x40);
    }
    tmp_u2 = G_SoundIndex(local_54c);
    if (local_570[0] == '\0') {
      G_globalSound(local_54c);
    }
    else {
      tmp_i1 = ClientNumbersFromString(local_570,local_50c);
      if (tmp_i1 == 1) {
        G_ClientSound(local_50c[0] * 0x600 + g_unk_00abe8a4,tmp_u2);
      }
      else {
        G_MatchOnePlayer(local_50c,local_40c,0x400);
        G_Printf("playsound: %s\n",local_40c);
      }
    }
  }
  return;
}

void G_PrivateMessage(uint8_t *param_1)
{
  uint8_t *tmp_pu1;
  char tmp_c2;
  bool tmp_b3;
  bool tmp_b4;
  bool tmp_b5;
  bool tmp_b6;
  int tmp_i7;
  char *tmp_pc8;
  char *tmp_pc9;
  int tmp_i10;
  uint32_t tmp_u11;
  int tmp_i12;
  char tmp_c13;
  int tmp_i14;
  uint8_t *local_1a0;
  char *local_190;
  char local_170 [12];
  char local_164 [36];
  uint8_t local_140 [36];
  int local_11c [67];
  
  if (param_1 == (uint8_t *)0x0) {
    tmp_b5 = false;
  }
  else {
    tmp_i7 = *(int *)(param_1 + 400);
    if ((*(int *)(tmp_i7 + 0xbf0) != 0) ||
       (tmp_i7 = G_shrubbot_mute_check(tmp_i7 + 0x61c,tmp_i7 + 0xaf4), tmp_i7 != 0)) {
      tmp_pc8 = "chat \"^1PM Error^9: You are muted\" -2";
      goto LAB_00062e51;
    }
    if (GHIDRA_FIELD(g_privateMessages, 12, 4) == 0) {
      tmp_pc8 = "chat \"^1PM Error^9: Private messages disabled on this server\" -2";
      goto LAB_00062e51;
    }
    tmp_b5 = true;
  }
  tmp_i7 = nitrox_CheckPermission(param_1,0xe);
  if (tmp_i7 != 0) {
    nitmod_cp(param_1,0x38);
    return;
  }
  local_170[0] = '\0';
  tmp_pc8 = (char *)ConcatArgs(0);
  tmp_c13 = *tmp_pc8;
  if (tmp_c13 != '\0') {
    if (tmp_c13 == ' ') {
      tmp_pc8 = local_170;
    }
    else {
      tmp_c2 = tmp_pc8[1];
      local_170[0] = tmp_c13;
      if ((tmp_c2 == '\0') || (tmp_c2 == ' ')) {
        tmp_pc8 = local_170 + 1;
      }
      else {
        tmp_c13 = tmp_pc8[2];
        local_170[1] = tmp_c2;
        if ((tmp_c13 == '\0') || (tmp_c13 == ' ')) {
          tmp_pc8 = local_170 + 2;
        }
        else {
          tmp_c2 = tmp_pc8[3];
          local_170[2] = tmp_c13;
          if ((tmp_c2 == '\0') || (tmp_c2 == ' ')) {
            tmp_pc8 = local_170 + 3;
          }
          else {
            tmp_c13 = tmp_pc8[4];
            local_170[3] = tmp_c2;
            if ((tmp_c13 == '\0') || (tmp_c13 == ' ')) {
              tmp_pc8 = local_170 + 4;
            }
            else {
              tmp_c2 = tmp_pc8[5];
              local_170[4] = tmp_c13;
              if ((tmp_c2 == '\0') || (tmp_c2 == ' ')) {
                tmp_pc8 = local_170 + 5;
              }
              else {
                tmp_c13 = tmp_pc8[6];
                local_170[5] = tmp_c2;
                if ((tmp_c13 == '\0') || (tmp_c13 == ' ')) {
                  tmp_pc8 = local_170 + 6;
                }
                else {
                  tmp_c2 = tmp_pc8[7];
                  local_170[6] = tmp_c13;
                  if ((tmp_c2 == '\0') || (tmp_c2 == ' ')) {
                    tmp_pc8 = local_170 + 7;
                  }
                  else {
                    tmp_c13 = tmp_pc8[8];
                    local_170[7] = tmp_c2;
                    if ((tmp_c13 == '\0') || (tmp_c13 == ' ')) {
                      tmp_pc8 = local_170 + 8;
                    }
                    else {
                      tmp_c2 = tmp_pc8[9];
                      local_170[8] = tmp_c13;
                      if ((tmp_c2 == '\0') || (tmp_c2 == ' ')) {
                        tmp_pc8 = local_170 + 9;
                      }
                      else {
                        tmp_c13 = tmp_pc8[10];
                        local_170[9] = tmp_c2;
                        if ((tmp_c13 == '\0') || (tmp_c13 == ' ')) {
                          tmp_pc8 = local_170 + 10;
                        }
                        else {
                          tmp_pc8 = local_170 + 0xb;
                          local_170[10] = tmp_c13;
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
    *tmp_pc8 = '\0';
  }
  if ((((local_170[0] == 's') && (local_170[1] == 'a')) && (local_170[2] == 'y')) &&
     (local_170[3] == '\0')) {
    local_170[0] = '\0';
    tmp_pc8 = (char *)ConcatArgs(0);
    tmp_b3 = false;
    tmp_c13 = *tmp_pc8;
LAB_0006305b:
    if (tmp_c13 != '\0') {
      do {
        if (tmp_b3) {
          if (tmp_c13 == ' ') {
            tmp_pc8 = local_170;
          }
          else {
            tmp_c2 = tmp_pc8[1];
            local_170[0] = tmp_c13;
            if ((tmp_c2 == '\0') || (tmp_c2 == ' ')) {
              tmp_pc8 = local_170 + 1;
            }
            else {
              tmp_c13 = tmp_pc8[2];
              local_170[1] = tmp_c2;
              if ((tmp_c13 == '\0') || (tmp_c13 == ' ')) {
                tmp_pc8 = local_170 + 2;
              }
              else {
                tmp_c2 = tmp_pc8[3];
                local_170[2] = tmp_c13;
                if ((tmp_c2 == '\0') || (tmp_c2 == ' ')) {
                  tmp_pc8 = local_170 + 3;
                }
                else {
                  tmp_c13 = tmp_pc8[4];
                  local_170[3] = tmp_c2;
                  if ((tmp_c13 == '\0') || (tmp_c13 == ' ')) {
                    tmp_pc8 = local_170 + 4;
                  }
                  else {
                    tmp_c2 = tmp_pc8[5];
                    local_170[4] = tmp_c13;
                    if ((tmp_c2 == '\0') || (tmp_c2 == ' ')) {
                      tmp_pc8 = local_170 + 5;
                    }
                    else {
                      tmp_c13 = tmp_pc8[6];
                      local_170[5] = tmp_c2;
                      if ((tmp_c13 == '\0') || (tmp_c13 == ' ')) {
                        tmp_pc8 = local_170 + 6;
                      }
                      else {
                        tmp_c2 = tmp_pc8[7];
                        local_170[6] = tmp_c13;
                        if ((tmp_c2 == '\0') || (tmp_c2 == ' ')) {
                          tmp_pc8 = local_170 + 7;
                        }
                        else {
                          tmp_c13 = tmp_pc8[8];
                          local_170[7] = tmp_c2;
                          if ((tmp_c13 == '\0') || (tmp_c13 == ' ')) {
                            tmp_pc8 = local_170 + 8;
                          }
                          else {
                            tmp_c2 = tmp_pc8[9];
                            local_170[8] = tmp_c13;
                            if ((tmp_c2 == '\0') || (tmp_c2 == ' ')) {
                              tmp_pc8 = local_170 + 9;
                            }
                            else {
                              tmp_c13 = tmp_pc8[10];
                              local_170[9] = tmp_c2;
                              if ((tmp_c13 == '\0') || (tmp_c13 == ' ')) {
                                tmp_pc8 = local_170 + 10;
                              }
                              else {
                                tmp_pc8 = local_170 + 0xb;
                                local_170[10] = tmp_c13;
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
          *tmp_pc8 = '\0';
          tmp_i7 = 2;
          tmp_i14 = 3;
          goto LAB_0006309a;
        }
        tmp_b3 = false;
        if (tmp_c13 == ' ') {
          tmp_c13 = tmp_pc8[1];
          tmp_pc8 = tmp_pc8 + 1;
          tmp_b3 = true;
          if (tmp_c13 != ' ') goto LAB_0006305b;
          do {
            tmp_pc8 = tmp_pc8 + 1;
          } while (*tmp_pc8 == ' ');
          tmp_b3 = true;
        }
        tmp_c13 = tmp_pc8[1];
        tmp_pc8 = tmp_pc8 + 1;
        if (tmp_c13 == '\0') break;
      } while( true );
    }
    tmp_i7 = 2;
    tmp_i14 = 3;
  }
  else {
    tmp_i7 = 1;
    tmp_i14 = 2;
  }
LAB_0006309a:
  tmp_pc8 = (char *)ConcatArgs(0);
  tmp_c13 = *tmp_pc8;
  if (tmp_c13 != '\0') {
    tmp_i12 = 1;
    do {
      if (tmp_c13 == ' ') {
        tmp_c13 = tmp_pc8[1];
        tmp_pc8 = tmp_pc8 + 1;
        if (tmp_c13 == ' ') {
          do {
            tmp_pc8 = tmp_pc8 + 1;
          } while (*tmp_pc8 == ' ');
          tmp_i12 = tmp_i12 + 1;
          goto LAB_000630c0;
        }
        tmp_i12 = tmp_i12 + 1;
      }
      else {
LAB_000630c0:
        tmp_c13 = tmp_pc8[1];
        tmp_pc8 = tmp_pc8 + 1;
      }
    } while (tmp_c13 != '\0');
    if (tmp_i14 < tmp_i12) {
      local_164[0] = '\0';
      tmp_pc8 = (char *)ConcatArgs(0);
      tmp_i12 = 0;
      tmp_c13 = *tmp_pc8;
LAB_00063110:
      if (tmp_c13 != '\0') {
        do {
          if (tmp_i7 == tmp_i12) {
            if (tmp_c13 != ' ') {
              tmp_pc9 = local_164;
              tmp_i7 = 1;
              goto LAB_000635b0;
            }
            tmp_pc9 = local_164;
            goto LAB_000635c7;
          }
          if (tmp_c13 == ' ') {
            tmp_c13 = tmp_pc8[1];
            tmp_pc8 = tmp_pc8 + 1;
            if (tmp_c13 != ' ') goto code_r0x00063330;
            do {
              tmp_pc8 = tmp_pc8 + 1;
            } while (*tmp_pc8 == ' ');
            tmp_i12 = tmp_i12 + 1;
          }
          tmp_c13 = tmp_pc8[1];
          tmp_pc8 = tmp_pc8 + 1;
          if (tmp_c13 == '\0') break;
        } while( true );
      }
      goto LAB_00063136;
    }
  }
  tmp_pc8 = (char *)va("chat \"^9usage: ^g%s [name|slot#] [message]\" -2",local_170);
LAB_00062e51:
  trap_SendServerCommand(((int)(param_1 + -0x93e4a0) >> 9) * -0x55555555,tmp_pc8);
  return;
code_r0x00063330:
  tmp_i12 = tmp_i12 + 1;
  goto LAB_00063110;
code_r0x00063358:
  tmp_i7 = tmp_i7 + 1;
  goto LAB_00063149;
  while (tmp_i7 = tmp_i7 + 1, tmp_c13 != ' ') {
LAB_000635b0:
    *tmp_pc9 = tmp_c13;
    tmp_pc9 = tmp_pc9 + 1;
    tmp_c13 = tmp_pc8[tmp_i7];
    if ((tmp_c13 == '\0') || (tmp_i7 + 1 == 0x24)) break;
  }
LAB_000635c7:
  *tmp_pc9 = '\0';
LAB_00063136:
  local_190 = local_164;
  tmp_i7 = 0;
  tmp_pc8 = (char *)ConcatArgs(0);
  tmp_c13 = *tmp_pc8;
LAB_00063149:
  tmp_b3 = tmp_i14 == tmp_i7 || tmp_c13 == '\0';
  if (tmp_i14 != tmp_i7 && tmp_c13 != '\0') {
    do {
      if (tmp_c13 == ' ') {
        tmp_c13 = tmp_pc8[1];
        tmp_pc8 = tmp_pc8 + 1;
        if (tmp_c13 != ' ') goto code_r0x00063358;
        do {
          tmp_pc8 = tmp_pc8 + 1;
        } while (*tmp_pc8 == ' ');
        tmp_i7 = tmp_i7 + 1;
      }
      tmp_c13 = tmp_pc8[1];
      tmp_pc8 = tmp_pc8 + 1;
      tmp_b3 = tmp_i14 == tmp_i7 || tmp_c13 == '\0';
      if (tmp_i14 == tmp_i7 || tmp_c13 == '\0') break;
    } while( true );
  }
  tmp_i7 = ClientNumbersFromString(local_190,local_11c);
  if (tmp_b5) {
    tmp_pc9 = (char *)(*(int *)(param_1 + 400) + 0x5f8);
  }
  else {
    tmp_pc9 = "console";
  }
  Q_strncpyz(local_140,tmp_pc9,0x24);
  if (tmp_i7 < 1) {
    if (0 < g_unk_00abe938) {
      local_1a0 = (uint8_t *)0x0;
      tmp_b6 = false;
      tmp_b5 = false;
      tmp_b3 = false;
      tmp_b4 = false;
      goto LAB_000633b1;
    }
LAB_00063538:
    trap_SendServerCommand
              (((int)(param_1 + -0x93e4a0) >> 9) * -0x55555555,
               "chat \"^1PM Error ^9: Player not found\" -2");
  }
  else {
    tmp_i14 = ((int)(param_1 + -0x93e4a0) >> 9) * -0x55555555;
    tmp_i12 = 0;
    tmp_b4 = false;
    do {
      tmp_i10 = local_11c[tmp_i12];
      tmp_b6 = true;
      if (tmp_i10 != tmp_i14) {
        tmp_b6 = tmp_b4;
      }
      tmp_i10 = tmp_i10 * 0x600;
      local_1a0 = g_entities + tmp_i10;
      tmp_i10 = COM_BitCheck(*(int *)(g_entities + tmp_i10 + 400) + 0xbe8,tmp_i14);
      if (tmp_i10 == 0) {
        tmp_u11 = va("pop \"^xPrivate message from ^7%s\"",local_140);
        trap_SendServerCommand(local_11c[tmp_i12],tmp_u11);
        tmp_u11 = va("chat \"^7%s ^0-> ^7%s ^0(^f%d^0):^7\" -2",local_140,local_190,tmp_i7);
        trap_SendServerCommand(local_11c[tmp_i12],tmp_u11);
        tmp_u11 = Q_CleanStr(tmp_pc8);
        tmp_u11 = va("lc \"%s\"",tmp_u11);
        trap_SendServerCommand(local_11c[tmp_i12],tmp_u11);
        G_AddEvent(local_1a0,0x62,0);
      }
      else {
        trap_SendServerCommand(tmp_i14,"chat \"^1PM Error^9: ^7%s ^9is ignoring you\" -2");
      }
      tmp_i12 = tmp_i12 + 1;
      tmp_b4 = tmp_b6;
    } while (tmp_i12 != tmp_i7);
    if (g_unk_00abe938 < 1) {
      if (!tmp_b5) goto LAB_000634bf;
    }
    else {
      tmp_b4 = true;
LAB_000633b1:
      tmp_i14 = 0;
      do {
        tmp_i10 = (&g_unk_00abe944)[tmp_i14] * 0x600;
        tmp_pu1 = g_entities + tmp_i10;
        tmp_i12 = nitrox_CheckPermission(tmp_pu1,0xc);
        if ((((tmp_i12 != 0) && (*(int *)(*(int *)(g_entities + tmp_i10 + 400) + 3000) == 3)) &&
            ((bool)(tmp_b3 & tmp_pu1 != param_1))) && (tmp_pu1 != local_1a0)) {
          tmp_u11 = va("chat \"^xPMSpec : ^7%s ^9-> ^7%s^9 (^f%d^9): ^7\" -2",local_140,local_190,
                      tmp_i7);
          tmp_i12 = (tmp_i10 >> 9) * -0x55555555;
          trap_SendServerCommand(tmp_i12,tmp_u11);
          tmp_u11 = Q_CleanStr(tmp_pc8);
          tmp_u11 = va("lc \"%s\"",tmp_u11);
          trap_SendServerCommand(tmp_i12,tmp_u11);
        }
        tmp_i14 = tmp_i14 + 1;
      } while (tmp_i14 < g_unk_00abe938);
      if (!tmp_b5) {
        if (tmp_b4) goto LAB_000634bf;
        goto LAB_00063538;
      }
    }
    if (!tmp_b6) {
      tmp_u11 = va("chat \"^7%s^7 ^9-> ^7%s^9: (^f%d^9):^7\" -2",local_140,local_190,tmp_i7);
      tmp_i7 = ((int)(param_1 + -0x93e4a0) >> 9) * -0x55555555;
      trap_SendServerCommand(tmp_i7,tmp_u11);
      tmp_u11 = Q_CleanStr(tmp_pc8);
      tmp_u11 = va("lc \"%s\"",tmp_u11);
      trap_SendServerCommand(tmp_i7,tmp_u11);
    }
  }
LAB_000634bf:
  unescape_string(tmp_pc8);
  G_LogPrintf("privmsg: %s: %s: %s\n",local_140,local_190,tmp_pc8);
  return;
}

void G_DropItems(uint32_t *param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
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
  uint32_t local_14;
  uint32_t local_10;
  
  if (*(int *)(param_1[100] + 0x164) == 0) {
    if (*(int *)(param_1[100] + 0x168) == 0) {
      return;
    }
LAB_000652e0:
    tmp_i2 = BG_FindItem("Blue Flag");
    if (tmp_i2 == 0) {
      tmp_i2 = BG_FindItem("Objective");
    }
    *(uint32_t *)(param_1[100] + 0x168) = 0;
  }
  else {
    tmp_i2 = BG_FindItem("Red Flag");
    if (tmp_i2 != 0) {
      *(uint32_t *)(param_1[100] + 0x164) = 0;
      tmp_i3 = param_1[100];
      if (*(int *)(tmp_i3 + 0x168) == 0) goto LAB_00065130;
      goto LAB_000652e0;
    }
    tmp_i2 = BG_FindItem("Objective");
    *(uint32_t *)(param_1[100] + 0x164) = 0;
    if (*(int *)(param_1[100] + 0x168) != 0) goto LAB_000652e0;
  }
  if (tmp_i2 == 0) {
    return;
  }
  tmp_i3 = param_1[100];
LAB_00065130:
  local_3c = 0.0;
  local_38 = 0.0;
  local_34 = 0.0;
  local_24 = *(float *)(tmp_i3 + 0x14);
  local_20 = *(float *)(tmp_i3 + 0x18);
  local_1c = *(float *)(tmp_i3 + 0x1c);
  if (0 < (int)param_1[0xb2]) {
    local_18 = *(float *)(tmp_i3 + 0xb0);
    local_14 = *(uint32_t *)(tmp_i3 + 0xb4);
    local_10 = *(uint32_t *)(tmp_i3 + 0xb8);
    if (0.0 < local_18) {
      local_18 = 0.0;
    }
    AngleVectors(&local_18,&local_30,0,0);
    tmp_i3 = param_1[100];
    local_3c = local_30 * 96.0 + *(float *)(tmp_i3 + 0x20);
    local_38 = local_2c * 96.0 + *(float *)(tmp_i3 + 0x24);
    local_34 = local_28 * 96.0 + *(float *)(tmp_i3 + 0x28);
    local_24 = local_30 * 36.0 + local_24;
    local_20 = local_2c * 36.0 + local_20;
    local_1c = (float)*(int *)(tmp_i3 + 0xbc) + local_28 * 36.0 + local_1c;
  }
  tmp_i2 = LaunchItem(tmp_i2,&local_24,&local_3c,*param_1,0x1000);
  *(uint32_t *)(tmp_i2 + 0xa8) = param_1[0x24];
  tmp_u1 = param_1[0x92];
  *(uint32_t *)(tmp_i2 + 0x248) = tmp_u1;
  tmp_u1 = va("%s dropped.",tmp_u1);
  Bot_Util_SendTrigger(tmp_i2,0,tmp_u1,"dropped");
  param_1[0x24] = 0;
  param_1[0x92] = 0;
  return;
}

uint G_ClassCount(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  int *tmp_pi4;
  uint local_14;
  
  local_14 = (uint)(param_2 == -1);
  if (0 < g_unk_00abe93c) {
    tmp_i2 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    tmp_pi3 = &g_unk_00abe944;
    tmp_pi4 = &g_unk_00abe944 + g_unk_00abe93c;
    if (param_2 == -1) {
      local_14 = 1;
      do {
        if (tmp_i2 - *tmp_pi3 != 0) {
          local_14 = local_14 +
                     (*(int *)(level + 3000 + *tmp_pi3 * 0x54dc) ==
                     *(int *)(*(int *)(param_1 + 400) + 3000));
        }
        tmp_pi3 = tmp_pi3 + 1;
      } while (tmp_pi3 != tmp_pi4);
      return local_14;
    }
    do {
      while (((tmp_i2 - *tmp_pi3 == 0 ||
              (tmp_i1 = *tmp_pi3 * 0x54dc + level,
              *(int *)(tmp_i1 + 3000) != *(int *)(*(int *)(param_1 + 400) + 3000))) ||
             ((*(int *)(tmp_i1 + 0xbc8) != param_2 && (*(int *)(tmp_i1 + 0xbd8) != param_2))))) {
        tmp_pi3 = tmp_pi3 + 1;
        if (tmp_pi3 == tmp_pi4) {
          return local_14;
        }
      }
      tmp_pi3 = tmp_pi3 + 1;
      local_14 = local_14 + 1;
    } while (tmp_pi3 != tmp_pi4);
  }
  return local_14;
}

uint32_t G_IsClassDisabled(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  int *tmp_pi4;
  uint local_20;
  
  tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 3000);
  if (tmp_i1 != 3) {
    local_20 = (uint)(param_2 == -1);
    if (0 < g_unk_00abe93c) {
      tmp_pi3 = &g_unk_00abe944;
      tmp_pi4 = &g_unk_00abe944 + g_unk_00abe93c;
      if (param_2 == -1) {
        do {
          tmp_pi3 = tmp_pi3 + 1;
        } while (tmp_pi3 != tmp_pi4);
        return 0;
      }
      do {
        while (((*tmp_pi3 == (param_1 + -0x93e4a0 >> 9) * -0x55555555 ||
                (tmp_i2 = *tmp_pi3 * 0x54dc + level, tmp_i1 != *(int *)(tmp_i2 + 3000))) ||
               ((param_2 != *(int *)(tmp_i2 + 0xbc8) && (param_2 != *(int *)(tmp_i2 + 0xbd8)))))) {
          tmp_pi3 = tmp_pi3 + 1;
          if (tmp_pi3 == tmp_pi4) goto LAB_00065520;
        }
        tmp_pi3 = tmp_pi3 + 1;
        local_20 = local_20 + 1;
      } while (tmp_pi3 != tmp_pi4);
    }
LAB_00065520:
    switch(param_2) {
    case 0:
      if (((GHIDRA_FIELD(g_war, 12, 4) != 1) && ((int)GHIDRA_FIELD(team_maxSoldiers, 12, 4) <= (int)local_20)) &&
         (GHIDRA_FIELD(team_maxSoldiers, 12, 4) != -1)) {
        if (param_3 == 0) {
          nitmod_cp(param_1,0xe);
          return 1;
        }
        return 1;
      }
      break;
    case 1:
      if (((int)GHIDRA_FIELD(team_maxMedics, 12, 4) <= (int)local_20) && (GHIDRA_FIELD(team_maxMedics, 12, 4) != -1)) {
        if (param_3 == 0) {
          nitmod_cp(param_1,0xf);
          return 1;
        }
        return 1;
      }
      break;
    case 2:
      if (((GHIDRA_FIELD(g_war, 12, 4) != 3) && ((int)GHIDRA_FIELD(team_maxEngineers, 12, 4) <= (int)local_20)) &&
         (GHIDRA_FIELD(team_maxEngineers, 12, 4) != -1)) {
        if (param_3 == 0) {
          nitmod_cp(param_1,0x10);
          return 1;
        }
        return 1;
      }
      break;
    case 3:
      if (((int)GHIDRA_FIELD(team_maxFieldops, 12, 4) <= (int)local_20) && (GHIDRA_FIELD(team_maxFieldops, 12, 4) != -1)) {
        if (param_3 == 0) {
          nitmod_cp(param_1,0x11);
          return 1;
        }
        return 1;
      }
      break;
    case 4:
      if (((GHIDRA_FIELD(g_war, 12, 4) != 2) && (GHIDRA_FIELD(team_maxCovertops, 12, 4) != -1)) &&
         ((int)GHIDRA_FIELD(team_maxCovertops, 12, 4) <= (int)local_20)) {
        if (param_3 == 0) {
          nitmod_cp(param_1,0x12);
          return 1;
        }
        return 1;
      }
    }
  }
  return 0;
}

void G_TeamCountPlayers(void)
{
  int tmp_i1;
  int *tmp_pi2;
  
  if (g_unk_00abe938 < 1) {
    g_unk_02b9a450 = 0;
    g_unk_02b9a44c = 0;
  }
  else {
    tmp_pi2 = &g_unk_00abe944;
    g_unk_02b9a450 = 0;
    g_unk_02b9a44c = 0;
    do {
      while (tmp_i1 = *(int *)(level + 3000 + *tmp_pi2 * 0x54dc), tmp_i1 == 1) {
        tmp_pi2 = tmp_pi2 + 1;
        g_unk_02b9a44c = g_unk_02b9a44c + 1;
        if (tmp_pi2 == &g_unk_00abe944 + g_unk_00abe938) {
          return;
        }
      }
      tmp_pi2 = tmp_pi2 + 1;
      g_unk_02b9a450 = g_unk_02b9a450 + (uint)(tmp_i1 == 2);
    } while (tmp_pi2 != &g_unk_00abe944 + g_unk_00abe938);
  }
  return;
}

uint G_TeamCount(int param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  uint local_1c;
  
  local_1c = (uint)(param_2 == -1);
  if (0 < g_unk_00abe93c) {
    tmp_i2 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    if (param_2 - 0x24U < 2) {
      tmp_pi1 = &g_unk_00abe944;
      do {
        if ((((tmp_i2 - *tmp_pi1 != 0) &&
             (tmp_i3 = *tmp_pi1 * 0x54dc + level,
             *(int *)(tmp_i3 + 3000) == *(int *)(*(int *)(param_1 + 400) + 3000))) &&
            (*(int *)(tmp_i3 + 0xbe4) != 0)) &&
           ((*(int *)(tmp_i3 + 0xbcc) == *(int *)(weapAlts + param_2 * 4) ||
            (*(int *)(weapAlts + param_2 * 4) == *(int *)(tmp_i3 + 0xbdc))))) {
          local_1c = local_1c + 1;
        }
        tmp_pi1 = tmp_pi1 + 1;
      } while (tmp_pi1 != &g_unk_00abe944 + g_unk_00abe93c);
    }
    else {
      if (param_2 == -1) {
        tmp_pi1 = &g_unk_00abe944;
        local_1c = 1;
        do {
          if (tmp_i2 - *tmp_pi1 != 0) {
            local_1c = local_1c +
                       (*(int *)(level + 3000 + *tmp_pi1 * 0x54dc) ==
                       *(int *)(*(int *)(param_1 + 400) + 3000));
          }
          tmp_pi1 = tmp_pi1 + 1;
        } while (tmp_pi1 != &g_unk_00abe944 + g_unk_00abe93c);
        return local_1c;
      }
      tmp_pi1 = &g_unk_00abe944;
      do {
        while (((tmp_i2 == *tmp_pi1 ||
                (tmp_i3 = *tmp_pi1 * 0x54dc + level,
                *(int *)(tmp_i3 + 3000) != *(int *)(*(int *)(param_1 + 400) + 3000))) ||
               ((*(int *)(tmp_i3 + 0xbcc) != param_2 &&
                (((*(int *)(tmp_i3 + 0xbdc) != param_2 &&
                  (*(int *)(tmp_i3 + 0xbcc) != *(int *)(weapTeamConversion + param_2 * 4))) &&
                 (*(int *)(tmp_i3 + 0xbdc) != *(int *)(weapTeamConversion + param_2 * 4)))))))) {
          tmp_pi1 = tmp_pi1 + 1;
          if (tmp_pi1 == &g_unk_00abe944 + g_unk_00abe93c) {
            return local_1c;
          }
        }
        tmp_pi1 = tmp_pi1 + 1;
        local_1c = local_1c + 1;
      } while (tmp_pi1 != &g_unk_00abe944 + g_unk_00abe93c);
    }
  }
  return local_1c;
}

void G_EntitySound(uint32_t *param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t tmp_u1;
  
  tmp_u1 = va("entitySound %d %s %d %i %i %i normal",*param_1,param_2,param_3,
             (int)ROUND((float)param_1[6]),(int)ROUND((float)param_1[7]),
             (int)ROUND((float)param_1[8]));
  trap_SendServerCommand(0xffffffff,tmp_u1);
  return;
}

void G_EntitySoundNoCut(uint32_t *param_1,uint32_t param_2,uint32_t param_3)
{
  uint32_t tmp_u1;
  
  tmp_u1 = va("entitySound %d %s %d %i %i %i noCut",*param_1,param_2,param_3,
             (int)ROUND((float)param_1[6]),(int)ROUND((float)param_1[7]),
             (int)ROUND((float)param_1[8]));
  trap_SendServerCommand(0xffffffff,tmp_u1);
  return;
}

uint8_t * G_ShortcutSanitize(char *param_1)
{
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    G_ShortcutSanitize_part_7();
  }
  return n_14038;
}

uint8_t * G_Shortcuts(int param_1,uint32_t param_2)
{
  uint tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint32_t *local_1c4;
  uint32_t *local_1c0;
  uint32_t *local_1bc;
  uint32_t *local_1b8;
  uint32_t *local_1b4;
  uint32_t *local_1b0;
  uint32_t *local_1ac;
  uint32_t *local_1a8;
  uint32_t *local_1a4;
  uint32_t local_198;
  uint32_t local_194;
  uint32_t local_190;
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
  uint32_t local_160;
  uint32_t local_15c;
  uint32_t local_158;
  uint32_t local_154;
  uint32_t auStack_150 [79];
  uint32_t uStack_14;
  
  uStack_14 = 0x66538;
  auStack_150[0x10] = 0x2a;
  tmp_u1 = 0;
  auStack_150[0xe] = 0x6b6e752a;
  auStack_150[0xf] = 0x6e776f6e;
  do {
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0x44) = 0;
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0x48) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x18);
  auStack_150[0x19] = 0x2a;
  tmp_u1 = 0;
  auStack_150[0x17] = 0x6b6e752a;
  auStack_150[0x18] = 0x6e776f6e;
  do {
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0x68) = 0;
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0x6c) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x18);
  auStack_150[0x22] = 0x2a;
  tmp_u1 = 0;
  auStack_150[0x20] = 0x6b6e752a;
  auStack_150[0x21] = 0x6e776f6e;
  do {
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0x8c) = 0;
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0x90) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x18);
  tmp_u1 = 0;
  auStack_150[0x29] = 0x6b6e752a;
  auStack_150[0x2a] = 0x6e776f6e;
  auStack_150[0x2b] = 0x2a;
  do {
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0xb0) = 0;
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0xb4) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x18);
  local_190 = 0x2a;
  local_18c = 0;
  local_188 = 0;
  local_184 = 0;
  local_198 = 0x6b6e752a;
  local_180 = 0;
  local_17c = 0;
  tmp_u1 = 0;
  local_194 = 0x6e776f6e;
  auStack_150[0x32] = 0x6b6e752a;
  auStack_150[0x33] = 0x6e776f6e;
  auStack_150[0x34] = 0x2a;
  do {
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0xd4) = 0;
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0xd8) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x18);
  auStack_150[0x3d] = 0x2a;
  tmp_u1 = 0;
  auStack_150[0x3b] = 0x6b6e752a;
  auStack_150[0x3c] = 0x6e776f6e;
  do {
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0xf8) = 0;
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0xfc) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x18);
  auStack_150[0x46] = 0x2a;
  tmp_u1 = 0;
  auStack_150[0x44] = 0x6b6e752a;
  auStack_150[0x45] = 0x6e776f6e;
  do {
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0x11c) = 0;
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 0x120) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x18);
  local_178 = 0x6b6e752a;
  tmp_u1 = 0;
  local_174 = 0x6e776f6e;
  local_170 = 0x2a;
  local_16c = 0;
  local_168 = 0;
  local_164 = 0;
  local_160 = 0;
  local_15c = 0;
  local_158 = 0x68746f4e;
  local_154 = 0x676e69;
  do {
    *(uint32_t *)((int)auStack_150 + tmp_u1) = 0;
    *(uint32_t *)((int)auStack_150 + tmp_u1 + 4) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x18);
  auStack_150[6] = 0x6b6e752a;
  auStack_150[7] = 0x6e776f6e;
  auStack_150[8] = 0x2a;
  auStack_150[9] = 0;
  auStack_150[10] = 0;
  auStack_150[0xb] = 0;
  auStack_150[0xc] = 0;
  auStack_150[0xd] = 0;
  out_14043 = 0;
  if (param_1 == 0) goto LAB_00066996;
  tmp_i3 = *(int *)(param_1 + 400);
  if (*(int *)(tmp_i3 + 0x9dc) == -1) {
LAB_00066ce1:
    tmp_i4 = *(int *)(tmp_i3 + 0x9d8);
    if (tmp_i4 != -1) {
      if (1 < *(int *)(tmp_i3 + 3000) - 1U) goto LAB_00066879;
LAB_00066d08:
      tmp_i4 = tmp_i4 * 0x54dc + level;
      if (tmp_i4 == 0) {
        tmp_i4 = *(int *)(tmp_i3 + 0x9e0);
        goto joined_r0x0006705c;
      }
      if (*(char *)(tmp_i4 + 0x5f8) != '\0') {
        G_ShortcutSanitize_part_7();
      }
      Q_strncpyz(auStack_150 + 0x17,n_14038,0x24);
      tmp_i3 = *(int *)(param_1 + 400);
    }
    tmp_i4 = *(int *)(tmp_i3 + 0x9e0);
    if (tmp_i4 == -1) goto LAB_00066db1;
    if (*(int *)(tmp_i3 + 3000) - 1U < 2) goto LAB_00066d70;
  }
  else {
    if (*(int *)(tmp_i3 + 3000) - 1U < 2) {
      tmp_i4 = *(int *)(tmp_i3 + 0x9dc) * 0x54dc + level;
      if (tmp_i4 != 0) {
        if (*(char *)(tmp_i4 + 0x5f8) != '\0') {
          G_ShortcutSanitize_part_7();
        }
        Q_strncpyz(auStack_150 + 0xe,n_14038,0x24);
        tmp_i3 = *(int *)(param_1 + 400);
        goto LAB_00066ce1;
      }
      tmp_i4 = *(int *)(tmp_i3 + 0x9d8);
      if (tmp_i4 != -1) goto LAB_00066d08;
      tmp_i4 = *(int *)(tmp_i3 + 0x9e0);
joined_r0x0006705c:
      if (tmp_i4 == -1) goto LAB_00066db1;
LAB_00066d70:
      tmp_i4 = tmp_i4 * 0x54dc + level;
      if (tmp_i4 != 0) {
        if (*(char *)(tmp_i4 + 0x5f8) != '\0') {
          G_ShortcutSanitize_part_7();
        }
        Q_strncpyz(auStack_150 + 0x20,n_14038,0x24);
        tmp_i3 = *(int *)(param_1 + 400);
        goto LAB_00066db1;
      }
      tmp_i4 = *(int *)(tmp_i3 + 0x9d0);
      if (tmp_i4 == -1) goto LAB_00066879;
    }
    else {
      if (*(int *)(tmp_i3 + 0x9e0) != -1) goto LAB_00066879;
LAB_00066db1:
      tmp_i4 = *(int *)(tmp_i3 + 0x9d0);
      if ((tmp_i4 == -1) || (1 < *(int *)(tmp_i3 + 3000) - 1U)) goto LAB_00066879;
    }
    tmp_i4 = tmp_i4 * 0x54dc + level;
    if (tmp_i4 != 0) {
      if (*(char *)(tmp_i4 + 0x5f8) != '\0') {
        G_ShortcutSanitize_part_7();
      }
      Q_strncpyz(auStack_150 + 0x29,n_14038,0x24);
      tmp_i3 = *(int *)(param_1 + 400);
    }
  }
LAB_00066879:
  tmp_u2 = BG_GetLocationString(tmp_i3 + 0x14);
  Q_strncpyz(&local_198,tmp_u2,0x20);
  if ((*(int *)(param_1 + 400) != -0x5f8) && (*(char *)(*(int *)(param_1 + 400) + 0x5f8) != '\0')) {
    G_ShortcutSanitize_part_7();
  }
  Q_strncpyz(auStack_150 + 0x32,n_14038,0x24);
  tmp_i3 = *(int *)(param_1 + 400);
  if (*(int *)(tmp_i3 + 0x9d4) == -1) {
LAB_00066b4b:
    tmp_i5 = *(int *)(tmp_i3 + 0x5a0) * 0x600;
    tmp_i4 = *(int *)(g_entities + tmp_i5 + 400);
    if ((tmp_i4 != 0) && (*(int *)(g_entities + tmp_i5 + 0x194) != 0)) {
      tmp_i5 = *(int *)(tmp_i3 + 3000);
      if (tmp_i5 != *(int *)(tmp_i4 + 3000)) goto LAB_0006694e;
      goto LAB_00066b97;
    }
LAB_00066970:
    tmp_i3 = *(int *)(tmp_i3 + 3000);
joined_r0x00066bd4:
    if (1 < tmp_i3 - 1U) goto LAB_00066996;
  }
  else {
    if (1 < *(int *)(tmp_i3 + 3000) - 1U) {
      tmp_i5 = *(int *)(tmp_i3 + 0x5a0) * 0x600;
      tmp_i4 = *(int *)(g_entities + tmp_i5 + 400);
      if ((tmp_i4 == 0) || (*(int *)(g_entities + tmp_i5 + 0x194) == 0)) goto LAB_00066996;
LAB_00066931:
      tmp_i5 = *(int *)(tmp_i3 + 3000);
      if (tmp_i5 == *(int *)(tmp_i4 + 3000)) {
LAB_00066b97:
        if (*(char *)(tmp_i4 + 0x5f8) != '\0') {
          G_ShortcutSanitize_part_7();
        }
      }
      else {
LAB_0006694e:
        if (*(int *)(tmp_i4 + 0x16c) == 0) {
          if (tmp_i5 != 3) goto LAB_00066970;
          goto LAB_00066b97;
        }
        if (*(char *)(tmp_i4 + 0x533c) != '\0') {
          G_ShortcutSanitize_part_7();
        }
      }
      Q_strncpyz(auStack_150 + 0x44,n_14038,0x24);
      tmp_i3 = *(int *)(*(int *)(param_1 + 400) + 3000);
      goto joined_r0x00066bd4;
    }
    tmp_i4 = *(int *)(tmp_i3 + 0x9d4) * 0x54dc + level;
    if (tmp_i4 != 0) {
      if (*(char *)(tmp_i4 + 0x5f8) != '\0') {
        G_ShortcutSanitize_part_7();
      }
      Q_strncpyz(auStack_150 + 0x3b,n_14038,0x24);
      tmp_i3 = *(int *)(param_1 + 400);
      goto LAB_00066b4b;
    }
    tmp_i5 = *(int *)(tmp_i3 + 0x5a0) * 0x600;
    tmp_i4 = *(int *)(g_entities + tmp_i5 + 400);
    if ((tmp_i4 != 0) && (*(int *)(g_entities + tmp_i5 + 0x194) != 0)) goto LAB_00066931;
  }
  tmp_u2 = 0;
  if (-1 < *(int *)(param_1 + 0x2c8)) {
    tmp_u2 = *(uint32_t *)(param_1 + 0x2c8);
  }
  Com_sprintf(&local_178,0x20,"%i",tmp_u2);
  tmp_i3 = BG_FindItemForWeapon(*(uint32_t *)(*(int *)(param_1 + 400) + 0xa4));
  if (tmp_i3 != 0) {
    Q_strncpyz(&local_158,*(uint32_t *)(tmp_i3 + 0x1c),0x20);
    tmp_i4 = BG_FindClipForWeapon(*(uint32_t *)(*(int *)(param_1 + 400) + 0xa4));
    tmp_i5 = BG_FindAmmoForWeapon(*(uint32_t *)(*(int *)(param_1 + 400) + 0xa4));
    tmp_i3 = *(int *)(param_1 + 400);
    if (*(int *)(tmp_i3 + 0xa4) == 1) {
      tmp_i5 = 0;
    }
    else {
      tmp_i5 = *(int *)(tmp_i3 + (tmp_i5 + 100) * 4);
    }
    Com_sprintf(auStack_150 + 6,0x20,"%i",tmp_i5 + *(int *)(tmp_i3 + (tmp_i4 + 0xa4) * 4));
  }
LAB_00066996:
  local_1ac = auStack_150 + 0x32;
  local_1b0 = &local_198;
  local_1c4 = auStack_150 + 0x29;
  local_1a4 = auStack_150 + 0x3b;
  local_1a8 = auStack_150 + 0xe;
  local_1b4 = &local_158;
  local_1b8 = auStack_150 + 0x17;
  local_1bc = auStack_150 + 0x44;
  local_1c0 = auStack_150 + 0x20;
  tmp_u2 = Q_StrReplace(param_2,&g_unk_002457e4,local_1a8);
  tmp_u2 = Q_StrReplace(tmp_u2,&g_unk_002457ec,local_1b8);
  tmp_u2 = Q_StrReplace(tmp_u2,&g_unk_002457f4,local_1c0);
  tmp_u2 = Q_StrReplace(tmp_u2,&g_unk_002457fc,local_1c4);
  tmp_u2 = Q_StrReplace(tmp_u2,&g_unk_00245804,local_1b0);
  tmp_u2 = Q_StrReplace(tmp_u2,&g_unk_0024580c,local_1ac);
  tmp_u2 = Q_StrReplace(tmp_u2,&g_unk_00245814,local_1a4);
  tmp_u2 = Q_StrReplace(tmp_u2,&g_unk_0024581c,local_1bc);
  tmp_u2 = Q_StrReplace(tmp_u2,&g_unk_00245820,&local_178);
  tmp_u2 = Q_StrReplace(tmp_u2,&g_unk_00245828,local_1b4);
  tmp_u2 = Q_StrReplace(tmp_u2,&g_unk_00245a1d,auStack_150 + 6);
  Q_strncpyz(&out_14043,tmp_u2,0x96);
  return &out_14043;
}

void G_SayTo(int param_1,int param_2,uint param_3,uint32_t param_4,uint32_t param_5,
            uint32_t param_6,uint32_t param_7)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  uint32_t tmp_u5;
  int *tmp_pi6;
  char *tmp_pc7;
  uint8_t tmp_u8;
  bool tmp_b9;
  byte tmp_b10;
  ushort inreg_FPUControlWord;
  int local_48;
  int local_44;
  int local_28;
  int local_24 [5];
  
  tmp_b10 = 0;
  if (param_2 == 0) {
    return;
  }
  if (*(int *)(param_2 + 0x194) == 0) {
    return;
  }
  if (*(int *)(param_2 + 400) == 0) {
    return;
  }
  if ((param_3 & 0xfffffffd) == 1) {
    tmp_i4 = OnSameTeam(param_1,param_2);
    if ((tmp_i4 == 0) && (tmp_i4 = nitrox_CheckPermission(param_2,3), tmp_i4 == 0)) {
      return;
    }
    tmp_i4 = nitrox_CheckPermission(param_2,3);
    if (((tmp_i4 != 0) && (*(int *)(*(int *)(param_2 + 400) + 3000) != 3)) &&
       (tmp_i4 = OnSameTeam(param_1,param_2), tmp_i4 == 0)) {
      return;
    }
  }
  if ((0 < (int)GHIDRA_FIELD(match_mutespecs, 12, 4)) && (*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0)) {
    tmp_i4 = *(int *)(*(int *)(param_1 + 400) + 3000);
    if (tmp_i4 == 0) {
      if (*(int *)(*(int *)(param_2 + 400) + 3000) != 0) {
        return;
      }
    }
    else if ((tmp_i4 == 3) && (*(int *)(*(int *)(param_2 + 400) + 3000) != 3)) {
      return;
    }
  }
  if (param_3 == 2) {
    if (*(int *)(param_1 + 0xac) == *(int *)(param_2 + 0xac)) {
      local_48 = (param_2 + -0x93e4a0 >> 9) * -0x55555555;
      local_44 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    }
    else {
      tmp_i4 = nitrox_CheckPermission(param_2,3);
      if ((tmp_i4 != 0) && (*(int *)(*(int *)(param_2 + 400) + 3000) == 3)) {
        local_44 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        local_48 = (param_2 + -0x93e4a0 >> 9) * -0x55555555;
        goto LAB_00067469;
      }
      local_48 = (param_2 + -0x93e4a0 >> 9) * -0x55555555;
      tmp_i4 = G_IsOnFireteam(local_48,&local_28);
      if (tmp_i4 == 0) {
        return;
      }
      local_44 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
      tmp_i4 = G_IsOnFireteam(local_44,local_24);
      if (tmp_i4 == 0) {
        return;
      }
      if (local_28 != local_24[0]) {
        return;
      }
    }
    tmp_i4 = COM_BitCheck(*(int *)(param_2 + 400) + 0xbe8,local_44);
    if (tmp_i4 != 0) goto LAB_00067391;
  }
  else {
    local_44 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    tmp_i4 = COM_BitCheck(*(int *)(param_2 + 400) + 0xbe8,local_44);
    if (tmp_i4 != 0) {
      local_48 = (param_2 + -0x93e4a0 >> 9) * -0x55555555;
LAB_00067391:
      Q_strncpyz(local_24,"print",6);
      goto LAB_000673ac;
    }
    tmp_u8 = param_3 - 1 == 1;
    if (1 < param_3 - 1) {
      Q_strncpyz(local_24,"chat",6);
      tmp_i4 = 6;
      tmp_pi6 = local_24;
      tmp_pc7 = "print";
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_u8 = (char)*tmp_pi6 == *tmp_pc7;
        tmp_pi6 = (int *)((int)tmp_pi6 + (uint)tmp_b10 * -2 + 1);
        tmp_pc7 = tmp_pc7 + (uint)tmp_b10 * -2 + 1;
      } while ((bool)tmp_u8);
      if ((bool)tmp_u8) {
        tmp_pc7 = "\n";
      }
      else {
        tmp_pc7 = "";
      }
      tmp_u5 = escape_string(param_6);
      tmp_u5 = va("%s \"%s%c%c%s%s\" %i %i",local_24,param_5,0x5e,param_4,tmp_u5,tmp_pc7,local_44,
                 param_7);
      local_48 = (param_2 + -0x93e4a0 >> 9) * -0x55555555;
      trap_SendServerCommand(local_48,tmp_u5);
      goto LAB_000673ac;
    }
    local_48 = (param_2 + -0x93e4a0 >> 9) * -0x55555555;
  }
LAB_00067469:
  Q_strncpyz(local_24,"tchat",6);
  tmp_i4 = 6;
  tmp_f1 = *(float *)(param_1 + 0x20);
  tmp_b9 = (inreg_FPUControlWord | 0xc00) == 0;
  tmp_f2 = *(float *)(param_1 + 0x1c);
  tmp_f3 = *(float *)(param_1 + 0x18);
  tmp_pi6 = local_24;
  tmp_pc7 = "print";
  do {
    if (tmp_i4 == 0) break;
    tmp_i4 = tmp_i4 + -1;
    tmp_b9 = (char)*tmp_pi6 == *tmp_pc7;
    tmp_pi6 = (int *)((int)tmp_pi6 + (uint)tmp_b10 * -2 + 1);
    tmp_pc7 = tmp_pc7 + (uint)tmp_b10 * -2 + 1;
  } while (tmp_b9);
  if (tmp_b9) {
    tmp_pc7 = "\n";
  }
  else {
    tmp_pc7 = "";
  }
  tmp_u5 = escape_string(param_6);
  tmp_u5 = va("%s \"%c%c%s%s\" %i %i %i %i %i",local_24,0x5e,param_4,tmp_u5,tmp_pc7,local_44,param_7,
             (int)ROUND(tmp_f3),(int)ROUND(tmp_f2),(int)ROUND(tmp_f1));
  trap_SendServerCommand(local_48,tmp_u5);
LAB_000673ac:
  Bot_Event_ChatMessage(local_48,param_1,param_3,param_6);
  return;
}

void G_HQSay(int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  uint32_t tmp_u1;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 0x194) != 0)) && (*(int *)(param_1 + 400) != 0)) {
    tmp_u1 = va("gamechat \"%s%c%c%s\" 1",param_3,0x5e,param_2,param_4);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
  }
  return;
}

void G_Say(int param_1,int param_2,uint param_3,uint32_t param_4)
{
  char *tmp_pc1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  char tmp_c5;
  int tmp_i6;
  bool tmp_b7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  uint8_t *tmp_pu12;
  uint32_t tmp_u13;
  size_t tmp_s14;
  __int32_t **pp_Var15;
  int tmp_i16;
  char *tmp_pc17;
  char *tmp_pc18;
  int *tmp_pi19;
  uint8_t tmp_u20;
  bool tmp_b21;
  byte tmp_b22;
  ushort inreg_FPUControlWord;
  int local_1d4;
  uint32_t local_1c4;
  uint32_t local_1c0;
  uint8_t *local_1a8;
  int local_194;
  int local_190 [2];
  uint8_t local_188 [64];
  char local_148 [150];
  char local_b2 [162];
  
  tmp_b22 = 0;
  unescape_string(param_4);
  Q_strncpyz(local_148,param_4,0x96);
  if ((g_censor[0x10] != '\0') && (tmp_i8 = nitrox_CheckPermission(param_1,1), tmp_i8 == 0)) {
    tmp_pc18 = local_148;
    tmp_c5 = local_148[0];
    tmp_pc17 = local_b2;
    while (tmp_c5 != '\0') {
      if ((tmp_c5 == '^') || (tmp_c5 == '\x1b')) {
        if (tmp_pc18[1] == '\0') break;
        tmp_c5 = tmp_pc18[2];
        tmp_pc18 = tmp_pc18 + 2;
      }
      else if (tmp_c5 < ' ') {
        tmp_pc1 = tmp_pc18 + 1;
        tmp_pc18 = tmp_pc18 + 1;
        tmp_c5 = *tmp_pc1;
      }
      else {
        tmp_pc18 = tmp_pc18 + 1;
        pp_Var15 = __ctype_tolower_loc();
        tmp_i8 = (int)tmp_c5;
        tmp_c5 = *tmp_pc18;
        *tmp_pc17 = (char)(*pp_Var15)[tmp_i8];
        tmp_pc17 = tmp_pc17 + 1;
      }
    }
    *tmp_pc17 = '\0';
    tmp_b21 = false;
    tmp_pc18 = local_b2;
LAB_000680a0:
    if (*tmp_pc18 != '\0') {
      tmp_pu12 = censorDictionary;
      if (0 < (int)GHIDRA_FIELD(censorDictionary, 1000, 4)) goto code_r0x000680be;
      goto LAB_00068157;
    }
    if (tmp_b21) {
      Q_strncpyz(local_148,local_b2,0x96);
      G_CensorPenalize(param_1);
    }
  }
  if (GHIDRA_FIELD(g_shortcuts, 12, 4) != 0) {
    tmp_u13 = G_Shortcuts(param_1,local_148);
    Q_strncpyz(local_148,tmp_u13,0x96);
  }
  if (param_3 == 2) {
    G_LogPrintf("saybuddy: %s: %s\n",*(int *)(param_1 + 400) + 0x5f8,local_148);
    tmp_u13 = BG_GetLocationString(*(int *)(param_1 + 400) + 0x14);
    Com_sprintf(local_188,0x40,"[lof](%s%c%c) (%s): ",*(int *)(param_1 + 400) + 0x5f8,0x5e,0x37,
                tmp_u13);
    local_1c0 = 1;
    local_1c4 = 0x33;
  }
  else if (param_3 == 3) {
    G_LogPrintf("sayteamnl: %s: %s\n",*(int *)(param_1 + 400) + 0x5f8,local_148);
    Com_sprintf(local_188,0x40,"(%s^7): ",*(int *)(param_1 + 400) + 0x5f8);
    local_1c0 = 0;
    local_1c4 = 0x35;
  }
  else if (param_3 == 1) {
    G_LogPrintf("sayteam: %s: %s\n",*(int *)(param_1 + 400) + 0x5f8,local_148);
    tmp_u13 = BG_GetLocationString(*(int *)(param_1 + 400) + 0x14);
    Com_sprintf(local_188,0x40,"[lof](%s%c%c) (%s): ",*(int *)(param_1 + 400) + 0x5f8,0x5e,0x37,
                tmp_u13);
    local_1c0 = 1;
    local_1c4 = 0x35;
  }
  else {
    G_LogPrintf("say: %s: %s\n",*(int *)(param_1 + 400) + 0x5f8,local_148);
    Com_sprintf(local_188,0x40,"%s%c%c: ",*(int *)(param_1 + 400) + 0x5f8,0x5e,0x37);
    local_1c0 = 0;
    local_1c4 = 0x32;
  }
  if (param_2 != 0) {
    local_1a8 = local_188;
    tmp_i8 = COM_BitCheck(*(int *)(param_2 + 400) + 0xbe8,(param_1 + -0x93e4a0 >> 9) * -0x55555555);
    if (tmp_i8 != 0) {
      return;
    }
    G_SayTo(param_1,param_2,param_3,local_1c4,local_1a8,local_148,local_1c0);
    return;
  }
  local_1a8 = local_188;
  if (GHIDRA_FIELD(g_dedicated, 12, 4) != 0) {
    G_Printf("%s%s\n",local_1a8,local_148);
  }
  if (0 < g_unk_00abe938) {
    tmp_i16 = 0;
    tmp_i9 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    tmp_i8 = g_unk_00abe938;
    do {
      tmp_i6 = (&g_unk_00abe944)[tmp_i16];
      tmp_i11 = tmp_i6 * 0x600;
      if (((*(int *)(g_entities + tmp_i11 + 0x194) == 0) ||
          (*(int *)(g_entities + tmp_i11 + 400) == 0)) ||
         ((tmp_pu12 = g_entities + tmp_i11, (param_3 & 0xfffffffd) == 1 &&
          (((tmp_i8 = OnSameTeam(param_1,tmp_pu12), tmp_i8 == 0 &&
            (tmp_i10 = nitrox_CheckPermission(tmp_pu12,3), tmp_i8 = g_unk_00abe938, tmp_i10 == 0)) ||
           ((tmp_i8 = nitrox_CheckPermission(tmp_pu12,3), tmp_i8 != 0 &&
            ((*(int *)(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 3000) != 3 &&
             (tmp_i10 = OnSameTeam(param_1,tmp_pu12), tmp_i8 = g_unk_00abe938, tmp_i10 == 0))))))))))
      goto LAB_00067a3c;
      if (((int)GHIDRA_FIELD(match_mutespecs, 12, 4) < 1) || (*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0)) {
LAB_00067ae0:
        tmp_i11 = tmp_i11 >> 9;
        if (param_3 == 2) {
          if (*(int *)(param_1 + 0xac) != *(int *)(g_entities + tmp_i6 * 0x600 + 0xac)) {
            tmp_i8 = nitrox_CheckPermission(tmp_pu12,3);
            if ((tmp_i8 != 0) && (*(int *)(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 3000) == 3))
            goto LAB_00067cbd;
            tmp_i10 = G_IsOnFireteam(tmp_i11 * -0x55555555,&local_194);
            tmp_i8 = g_unk_00abe938;
            if ((tmp_i10 == 0) ||
               ((tmp_i10 = G_IsOnFireteam(tmp_i9,local_190), tmp_i8 = g_unk_00abe938, tmp_i10 == 0 ||
                (local_194 != local_190[0])))) goto LAB_00067a3c;
          }
          tmp_i8 = COM_BitCheck(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 0xbe8,tmp_i9);
          if (tmp_i8 != 0) goto LAB_00067e1d;
LAB_00067cbd:
          local_1d4 = tmp_i11 * -0x55555555;
          Q_strncpyz(local_190,"tchat",6);
          tmp_i8 = 6;
          tmp_f2 = *(float *)(param_1 + 0x20);
          tmp_b21 = (inreg_FPUControlWord | 0xc00) == 0;
          tmp_f3 = *(float *)(param_1 + 0x1c);
          tmp_f4 = *(float *)(param_1 + 0x18);
          tmp_pi19 = local_190;
          tmp_pc18 = "print";
          do {
            if (tmp_i8 == 0) break;
            tmp_i8 = tmp_i8 + -1;
            tmp_b21 = (char)*tmp_pi19 == *tmp_pc18;
            tmp_pi19 = (int *)((int)tmp_pi19 + (uint)tmp_b22 * -2 + 1);
            tmp_pc18 = tmp_pc18 + (uint)tmp_b22 * -2 + 1;
          } while (tmp_b21);
          if (tmp_b21) {
            tmp_pc18 = "\n";
          }
          else {
            tmp_pc18 = "";
          }
          tmp_u13 = escape_string(local_148);
          tmp_u13 = va("%s \"%c%c%s%s\" %i %i %i %i %i",local_190,0x5e,local_1c4,tmp_u13,tmp_pc18,tmp_i9
                      ,local_1c0,(int)ROUND(tmp_f4),(int)ROUND(tmp_f3),(int)ROUND(tmp_f2));
          trap_SendServerCommand(local_1d4,tmp_u13);
        }
        else {
          tmp_i8 = COM_BitCheck(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 0xbe8,tmp_i9);
          if (tmp_i8 == 0) {
            tmp_u20 = param_3 - 1 == 1;
            if (param_3 - 1 < 2) goto LAB_00067cbd;
            Q_strncpyz(local_190,"chat",6);
            tmp_i8 = 6;
            tmp_pi19 = local_190;
            tmp_pc18 = "print";
            do {
              if (tmp_i8 == 0) break;
              tmp_i8 = tmp_i8 + -1;
              tmp_u20 = (char)*tmp_pi19 == *tmp_pc18;
              tmp_pi19 = (int *)((int)tmp_pi19 + (uint)tmp_b22 * -2 + 1);
              tmp_pc18 = tmp_pc18 + (uint)tmp_b22 * -2 + 1;
            } while ((bool)tmp_u20);
            if ((bool)tmp_u20) {
              tmp_pc18 = "\n";
            }
            else {
              tmp_pc18 = "";
            }
            tmp_u13 = escape_string(local_148);
            tmp_u13 = va("%s \"%s%c%c%s%s\" %i %i",local_190,local_1a8,0x5e,local_1c4,tmp_u13,tmp_pc18,
                        tmp_i9,local_1c0);
            trap_SendServerCommand(tmp_i11 * -0x55555555,tmp_u13);
          }
          else {
LAB_00067e1d:
            Q_strncpyz(local_190,"print",6);
          }
        }
        local_1d4 = tmp_i11 * -0x55555555;
        Bot_Event_ChatMessage(local_1d4,param_1,param_3,local_148);
        tmp_i8 = g_unk_00abe938;
      }
      else {
        tmp_i10 = *(int *)(*(int *)(param_1 + 400) + 3000);
        tmp_i8 = g_unk_00abe938;
        if (tmp_i10 == 0) {
          if (*(int *)(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 3000) == 0) goto LAB_00067ae0;
        }
        else if ((tmp_i10 != 3) || (*(int *)(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 3000) == 3)
                ) goto LAB_00067ae0;
      }
LAB_00067a3c:
      tmp_i16 = tmp_i16 + 1;
    } while (tmp_i16 < tmp_i8);
  }
  G_shrubbot_cmd_check(param_1);
  return;
code_r0x000680be:
  tmp_b7 = false;
  local_1d4 = 0;
  tmp_pc17 = tmp_pc18;
  do {
    tmp_s14 = strlen(tmp_pu12);
    tmp_i8 = Q_stricmpn(tmp_pc17,tmp_pu12,tmp_s14);
    tmp_u13 = GHIDRA_FIELD(censorDictionary, 1000, 4);
    tmp_pc18 = tmp_pc17;
    if (tmp_i8 == 0) {
      tmp_b21 = true;
      if (local_1d4 != GHIDRA_FIELD(censorDictionary, 1000, 4) + -1) {
        tmp_b21 = tmp_b7;
      }
      for (; tmp_b7 = tmp_b21, tmp_s14 = strlen(tmp_pu12), (uint)((int)tmp_pc18 - (int)tmp_pc17) < tmp_s14;
          tmp_pc18 = tmp_pc18 + 1) {
        *tmp_pc18 = '*';
        tmp_b21 = tmp_b7;
      }
      tmp_b21 = true;
    }
    local_1d4 = local_1d4 + 1;
  } while ((local_1d4 < (int)tmp_u13) &&
          (tmp_pu12 = tmp_pu12 + 0x14, tmp_pc17 = tmp_pc18, *tmp_pc18 != '\0'));
  if (!tmp_b7) {
LAB_00068157:
    tmp_pc18 = tmp_pc18 + 1;
  }
  goto LAB_000680a0;
}

void G_VoiceTo(int param_1,int param_2,int param_3,uint32_t param_4,int param_5,float param_6)
{
  uint tmp_u1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  int local_24;
  int local_20 [4];
  
  if (param_2 == 0) {
    return;
  }
  if (*(int *)(param_2 + 0x194) == 0) {
    return;
  }
  if (*(int *)(param_2 + 400) == 0) {
    return;
  }
  if (param_3 == 1) {
    tmp_i2 = OnSameTeam(param_1,param_2);
    if (tmp_i2 == 0) {
      return;
    }
    if ((0 < (int)GHIDRA_FIELD(match_mutespecs, 12, 4)) &&
       (tmp_i2 = *(int *)(param_1 + 400), *(int *)(tmp_i2 + 0xc80) == 0)) {
LAB_00068660:
      if ((*(int *)(tmp_i2 + 3000) == 3) && (*(int *)(*(int *)(param_2 + 400) + 3000) != 3)) {
        return;
      }
      goto LAB_0006854c;
    }
LAB_00068720:
    tmp_u1 = *(uint *)(param_2 + 0x128);
    tmp_pc3 = "vtchat";
    tmp_u4 = 0x35;
    goto joined_r0x0006873a;
  }
  if ((int)GHIDRA_FIELD(match_mutespecs, 12, 4) < 1) {
    if (param_3 != 2) goto LAB_0006855e;
LAB_00068691:
    if (*(int *)(param_1 + 0xac) != *(int *)(param_2 + 0xac)) {
      tmp_i2 = G_IsOnFireteam((param_2 + -0x93e4a0 >> 9) * -0x55555555,&local_24);
      if (tmp_i2 == 0) {
        return;
      }
      tmp_i2 = G_IsOnFireteam((param_1 + -0x93e4a0 >> 9) * -0x55555555,local_20);
      if (tmp_i2 == 0) {
        return;
      }
      if (local_24 != local_20[0]) {
        return;
      }
    }
    tmp_pc3 = "vbchat";
    tmp_u4 = 0x33;
  }
  else {
    tmp_i2 = *(int *)(param_1 + 400);
    if (*(int *)(tmp_i2 + 0xc80) == 0) goto LAB_00068660;
LAB_0006854c:
    if (param_3 == 2) goto LAB_00068691;
    if (param_3 == 1) goto LAB_00068720;
LAB_0006855e:
    tmp_pc3 = "vchat";
    tmp_u4 = 0x32;
  }
  tmp_u1 = *(uint *)(param_2 + 0x128);
joined_r0x0006873a:
  if ((tmp_u1 & 8) == 0) {
    tmp_i2 = 0;
    if (param_5 != 2) {
      tmp_i2 = param_5;
    }
  }
  else {
    Bot_Event_VoiceMacro((param_2 + -0x93e4a0 >> 9) * -0x55555555,param_1,param_3,param_4);
    if (param_5 == 2) {
      param_5 = 0;
    }
    tmp_i2 = param_5;
    if ((*(uint *)(param_2 + 0x128) & 8) != 0) {
      return;
    }
  }
  param_5 = tmp_i2;
  if (param_3 - 1U < 2) {
    tmp_u4 = va("%s %d %d %d %s %i %i %i %f",tmp_pc3,param_5,(param_1 + -0x93e4a0 >> 9) * -0x55555555,
               tmp_u4,param_4,(int)ROUND(*(float *)(param_1 + 0x18)),
               (int)ROUND(*(float *)(param_1 + 0x1c)),(int)ROUND(*(float *)(param_1 + 0x20)),
               (double)param_6);
    trap_SendServerCommand((param_2 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
  }
  else {
    tmp_u4 = va("%s %d %d %d %s %f",tmp_pc3,param_5,(param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4,
               param_4,(double)param_6);
    trap_SendServerCommand((param_2 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
  }
  return;
}

void G_Voice(int param_1,int param_2,uint param_3,uint32_t param_4,char *param_5,int param_6)
{
  float tmp_f1;
  uint tmp_u2;
  size_t tmp_s3;
  int tmp_i4;
  long tmp_l5;
  long tmp_l6;
  int tmp_i7;
  char *tmp_pc8;
  int tmp_i9;
  int tmp_i10;
  uint32_t tmp_u11;
  int tmp_i12;
  char local_13c [32];
  int local_11c [66];
  uint32_t uStack_14;
  
  uStack_14 = 0x68869;
  tmp_u2 = rand();
  tmp_i9 = *(int *)(param_1 + 0x450) - g_unk_00abe908;
  *(int *)(param_1 + 0x450) = g_unk_00abe908;
  tmp_i9 = tmp_i9 + *(int *)(param_1 + 0x44c);
  *(int *)(param_1 + 0x44c) = tmp_i9;
  if (tmp_i9 < 0) {
    *(uint32_t *)(param_1 + 0x44c) = 0;
  }
  else if ((29999 < tmp_i9) && (tmp_i9 = nitrox_CheckPermission(param_1,1), tmp_i9 == 0)) {
    nitmod_cp(param_1,0x1a);
    return;
  }
  if (GHIDRA_FIELD(g_voiceChatsAllowed, 12, 4) == 0) {
    return;
  }
  tmp_f1 = (float)(tmp_u2 & 0x7fff) / 32767.0;
  *(int *)(param_1 + 0x44c) =
       *(int *)(param_1 + 0x44c) + (int)(34000 / (longlong)(int)GHIDRA_FIELD(g_voiceChatsAllowed, 12, 4));
  if (param_2 != 0) {
    tmp_s3 = strlen(param_5);
    if (1 < tmp_s3) {
      G_Say(param_1,param_2,param_3,param_5);
      param_6 = 1;
    }
    G_VoiceTo(param_1,param_2,param_3,param_4,param_6,tmp_f1);
    return;
  }
  if (GHIDRA_FIELD(g_dedicated, 12, 4) == 0) {
    if (param_3 == 2) {
LAB_00068c94:
      tmp_u2 = 0;
      do {
        *(uint32_t *)((int)local_11c + tmp_u2) = 0;
        *(uint32_t *)((int)local_11c + tmp_u2 + 4) = 0;
        tmp_u2 = tmp_u2 + 8;
      } while (tmp_u2 < 0x100);
      trap_Argv(1,local_13c,0x20);
      tmp_l5 = strtol(local_13c,(char **)0x0,10);
      trap_Argv(2,local_13c,0x20);
      tmp_l6 = strtol(local_13c,(char **)0x0,10);
      tmp_i9 = 0x40;
      if (tmp_l6 < 0x41) {
        tmp_i9 = tmp_l6;
      }
      if (0 < tmp_i9) {
        tmp_i12 = 3;
        do {
          trap_Argv(tmp_i12,local_13c,0x20);
          tmp_u2 = strtol(local_13c,(char **)0x0,10);
          if (tmp_u2 < 0x40) {
            local_11c[tmp_u2] = 1;
          }
          tmp_i12 = tmp_i12 + 1;
        } while (tmp_i12 != tmp_i9 + 3);
      }
      tmp_s3 = strlen(param_5);
      if (1 < tmp_s3) {
        G_Say(param_1,0,2,param_5);
        param_6 = 1;
      }
      if (g_unk_00abe938 < 1) {
        return;
      }
      tmp_i4 = 0;
      tmp_i7 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
      tmp_i12 = g_unk_00abe938;
      if (tmp_i9 != 0) {
        do {
          tmp_i9 = (&g_unk_00abe944)[tmp_i4];
          if ((((tmp_i9 == *(int *)(param_1 + 0xac)) || (tmp_l5 == -1)) ||
              (*(int *)(tmp_i9 * 0x54dc + level + 0xbc8) == tmp_l5)) &&
             ((local_11c[tmp_i9] != 0 &&
              (tmp_i9 = COM_BitCheck(*(int *)(g_entities + tmp_i9 * 0x600 + 400) + 0xbe8,tmp_i7),
              tmp_i12 = g_unk_00abe938, tmp_i9 == 0)))) {
            G_VoiceTo(param_1,g_entities + (&g_unk_00abe944)[tmp_i4] * 0x600,2,param_4,param_6,tmp_f1);
            tmp_i12 = g_unk_00abe938;
          }
          tmp_i4 = tmp_i4 + 1;
        } while (tmp_i4 < tmp_i12);
        return;
      }
      tmp_i12 = 0;
      tmp_i9 = g_unk_00abe938;
      do {
        tmp_i4 = (&g_unk_00abe944)[tmp_i12];
        if ((((tmp_i4 == *(int *)(param_1 + 0xac)) || (tmp_l5 == -1)) ||
            (*(int *)(tmp_i4 * 0x54dc + level + 0xbc8) == tmp_l5)) &&
           (tmp_i4 = COM_BitCheck(*(int *)(g_entities + tmp_i4 * 0x600 + 400) + 0xbe8,tmp_i7),
           tmp_i9 = g_unk_00abe938, tmp_i4 == 0)) {
          G_VoiceTo(param_1,g_entities + (&g_unk_00abe944)[tmp_i12] * 0x600,2,param_4,param_6,tmp_f1);
          tmp_i9 = g_unk_00abe938;
        }
        tmp_i12 = tmp_i12 + 1;
      } while (tmp_i12 < tmp_i9);
      return;
    }
  }
  else {
    if ((param_3 & 0xfffffffd) == 1) {
      G_LogPrintf("(team)voice: %s %s %s\n",*(int *)(param_1 + 400) + 0x5f8,param_4,param_5);
    }
    else if (param_3 == 0) {
      G_Printf("voice: %s %s %s\n",*(int *)(param_1 + 400) + 0x5f8,param_4,param_5);
      goto LAB_00068a0f;
    }
    if (param_3 == 2) {
      G_Printf("(fteam)voice: %s %s %s\n",*(int *)(param_1 + 400) + 0x5f8,param_4,param_5);
      goto LAB_00068c94;
    }
  }
LAB_00068a0f:
  tmp_s3 = strlen(param_5);
  if (1 < tmp_s3) {
    G_Say(param_1,0,param_3,param_5);
    param_6 = 1;
  }
  if (0 < g_unk_00abe938) {
    tmp_i12 = 0;
    tmp_i9 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    do {
      tmp_i7 = (&g_unk_00abe944)[tmp_i12];
      tmp_i10 = tmp_i7 * 0x600;
      tmp_i4 = COM_BitCheck(*(int *)(g_entities + tmp_i10 + 400) + 0xbe8,tmp_i9);
      if (((tmp_i4 == 0) && (*(int *)(g_entities + tmp_i10 + 0x194) != 0)) &&
         (*(int *)(g_entities + tmp_i10 + 400) != 0)) {
        if (param_3 == 1) {
          tmp_i4 = OnSameTeam(param_1,g_entities + tmp_i10);
          if (tmp_i4 == 0) goto LAB_00068ab0;
          if ((0 < (int)GHIDRA_FIELD(match_mutespecs, 12, 4)) &&
             (tmp_i4 = *(int *)(param_1 + 400), *(int *)(tmp_i4 + 0xc80) == 0)) goto LAB_00068b48;
LAB_00068f00:
          tmp_pc8 = "vtchat";
          tmp_u11 = 0x35;
        }
        else {
          if ((0 < (int)GHIDRA_FIELD(match_mutespecs, 12, 4)) &&
             (tmp_i4 = *(int *)(param_1 + 400), *(int *)(tmp_i4 + 0xc80) == 0)) {
LAB_00068b48:
            if ((*(int *)(tmp_i4 + 3000) == 3) &&
               (*(int *)(*(int *)(g_entities + tmp_i7 * 0x600 + 400) + 3000) != 3))
            goto LAB_00068ab0;
            if (param_3 == 1) goto LAB_00068f00;
          }
          tmp_pc8 = "vchat";
          tmp_u11 = 0x32;
        }
        if ((*(uint *)(g_entities + tmp_i7 * 0x600 + 0x128) & 8) == 0) {
          tmp_u2 = 0;
          if (param_6 != 2) {
LAB_00068b9a:
            tmp_i4 = param_6;
            goto LAB_00068ba1;
          }
          tmp_i4 = 0;
        }
        else {
          Bot_Event_VoiceMacro((tmp_i10 >> 9) * -0x55555555,param_1,param_3,param_4);
          tmp_i4 = 0;
          tmp_u2 = *(uint *)(g_entities + tmp_i7 * 0x600 + 0x128) & 8;
          if (param_6 != 2) goto LAB_00068b9a;
LAB_00068ba1:
          if (tmp_u2 != 0) goto LAB_00068ab0;
        }
        if (param_3 - 1 < 2) {
          tmp_u11 = va("%s %d %d %d %s %i %i %i %f",tmp_pc8,tmp_i4,tmp_i9,tmp_u11,param_4,
                      (int)ROUND(*(float *)(param_1 + 0x18)),(int)ROUND(*(float *)(param_1 + 0x1c)),
                      (int)ROUND(*(float *)(param_1 + 0x20)),(double)tmp_f1);
        }
        else {
          tmp_u11 = va("%s %d %d %d %s %f",tmp_pc8,tmp_i4,tmp_i9,tmp_u11,param_4);
        }
        trap_SendServerCommand((tmp_i10 >> 9) * -0x55555555,tmp_u11);
      }
LAB_00068ab0:
      tmp_i12 = tmp_i12 + 1;
    } while (tmp_i12 < g_unk_00abe938);
  }
  return;
}

void G_SendVoiceChat(int param_1,uint32_t param_2)
{
  G_Voice(g_entities + param_1 * 0x600,0,1,param_2,&g_unk_0026ea14,0);
  return;
}

bool G_FindFreeComplainIP(int param_1,uint *param_2)
{
  bool tmp_b1;
  uint tmp_u2;
  int tmp_i3;
  
  if (GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) == 0) {
    return true;
  }
  if ((int)GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) < 1) {
LAB_00069cd0:
    tmp_b1 = false;
  }
  else {
    if ((*(uint *)(param_1 + 0x9a8) == 0) && (*(uint *)(param_1 + 0x9a4) == 0)) {
      tmp_i3 = 0;
    }
    else {
      tmp_u2 = param_2[1] & *param_2;
      if ((*(uint *)(param_1 + 0x9a8) & *(uint *)(param_1 + 0x9a4)) == tmp_u2) {
        return true;
      }
      if (GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) == 1) goto LAB_00069cd0;
      if ((*(uint *)(param_1 + 0x9b0) == 0) && (*(uint *)(param_1 + 0x9ac) == 0)) {
        tmp_i3 = 1;
      }
      else {
        if (tmp_u2 == (*(uint *)(param_1 + 0x9b0) & *(uint *)(param_1 + 0x9ac))) {
          return true;
        }
        if (GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) == 2) goto LAB_00069cd0;
        if ((*(uint *)(param_1 + 0x9b8) == 0) && (*(uint *)(param_1 + 0x9b4) == 0)) {
          tmp_i3 = 2;
        }
        else {
          if (tmp_u2 == (*(uint *)(param_1 + 0x9b8) & *(uint *)(param_1 + 0x9b4))) {
            return true;
          }
          if (GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) == 3) goto LAB_00069cd0;
          if ((*(uint *)(param_1 + 0x9c0) == 0) && (*(uint *)(param_1 + 0x9bc) == 0)) {
            tmp_i3 = 3;
          }
          else {
            if (tmp_u2 == (*(uint *)(param_1 + 0x9c0) & *(uint *)(param_1 + 0x9bc))) {
              return true;
            }
            if (GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) == 4) goto LAB_00069cd0;
            if ((*(uint *)(param_1 + 0x9c8) != 0) || (*(uint *)(param_1 + 0x9c4) != 0)) {
              return (*(uint *)(param_1 + 0x9c8) & *(uint *)(param_1 + 0x9c4)) == tmp_u2;
            }
            tmp_i3 = 4;
          }
        }
      }
    }
    param_1 = param_1 + tmp_i3 * 8;
    *(uint *)(param_1 + 0x9a8) = param_2[1];
    *(uint *)(param_1 + 0x9a4) = *param_2;
    tmp_b1 = true;
  }
  return tmp_b1;
}

bool G_TankIsOccupied(int param_1)
{
  return *(int *)(param_1 + 0x444) != 0;
}

uint32_t G_TankIsMountable(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  if ((((((*(byte *)(param_1 + 0x1a8) & 0x80) != 0) && (g_unk_02aa29a4 == 0)) &&
       (tmp_i1 = BG_IsScopedWeapon(*(uint32_t *)(*(int *)(param_2 + 400) + 0xa4)), tmp_i1 == 0)) &&
      ((*(int *)(param_1 + 0x444) == 0 && (0 < *(int *)(param_1 + 0x2c8))))) &&
     ((0 < *(int *)(*(int *)(param_2 + 400) + 0xd0) &&
      (*(int *)(*(int *)(param_2 + 400) + 0x30) == 0)))) {
    if ((((int)GHIDRA_FIELD(n_tankMountDelay, 12, 4) < 1) || (*(int *)(param_2 + 0x5f4) < 1)) ||
       (*(int *)(param_2 + 0x5f4) <= g_unk_00abe908)) {
      return 1;
    }
    if (param_3 == 0) {
      tmp_u2 = va("cp \"You must wait %d seconds before you can mount a tank again.^7\" 1",
                 GHIDRA_FIELD(n_tankMountDelay, 12, 4));
      trap_SendServerCommand((param_2 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
      return 0;
    }
  }
  return 0;
}

uint32_t G_UniformSteal_2(int param_1,int param_2)
{
  uint *tmp_pu1;
  int *tmp_pi2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint32_t local_20;
  
  if ((GHIDRA_FIELD(g_gametype, 12, 4) == 8) || (*(int *)(param_1 + 0x2c8) < 1)) {
    local_20 = 0;
  }
  else {
    tmp_i3 = *(int *)(param_1 + 400);
    local_20 = 0;
    if (((*(int *)(tmp_i3 + 0x16c) == 0) && (*(int *)(tmp_i3 + 0x168) == 0)) &&
       (*(int *)(tmp_i3 + 0x164) == 0)) {
      *(uint32_t *)(tmp_i3 + 0x16c) = 1;
      *(uint *)(*(int *)(param_1 + 400) + 0x170) = *(uint *)(*(int *)(param_2 + 400) + 0xbc8) & 1;
      *(uint *)(*(int *)(param_1 + 400) + 0x174) = *(uint *)(*(int *)(param_2 + 400) + 0xbc8) & 2;
      *(uint *)(*(int *)(param_1 + 400) + 0x178) = *(uint *)(*(int *)(param_2 + 400) + 0xbc8) & 4;
      tmp_pu1 = (uint *)(*(int *)(param_2 + 400) + 0x68);
      *tmp_pu1 = *tmp_pu1 | 0x10000;
      G_AddEvent(param_1,0x57,0);
      G_AddSkillPoints(param_1,6,0x40a00000);
      if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
        G_DebugAddSkillPoints(param_1,6,0x40a00000,"back stealing uniform");
      }
      Q_strncpyz(*(int *)(param_1 + 400) + 0x533c,
                 *(int *)(g_entities + *(int *)(param_2 + 0xac) * 0x600 + 400) + 0x5f8,0x24);
      tmp_u4 = 0;
      if (*(int *)(g_entities + *(int *)(param_2 + 0xac) * 0x600 + 400) != 0) {
        tmp_u4 = *(uint32_t *)
                 (*(int *)(g_entities + *(int *)(param_2 + 0xac) * 0x600 + 400) + 0xc4c);
      }
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x5360) = tmp_u4;
      ClientUserinfoChanged(*(uint32_t *)(param_1 + 0xac));
      tmp_pi2 = (int *)(*(int *)(param_1 + 400) + 0xba0);
      *tmp_pi2 = *tmp_pi2 + 1;
      local_20 = 1;
      if ((g_entities[*(int *)(param_2 + 0xac) * 0x600 + 0x128] & 8) == 0) {
        local_20 = 1;
        nitrox_CheckGlobalAwards(param_1,0xe,1);
      }
    }
  }
  return local_20;
}

uint32_t G_UniformSteal(int param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  
  tmp_u3 = 0;
  if (((((GHIDRA_FIELD(g_gametype, 12, 4) != 8) && (*(int *)(param_2 + 0x2f0) == 0)) &&
       (tmp_i2 = *(int *)(param_1 + 400), *(int *)(tmp_i2 + 0xbc8) == 4)) &&
      ((0 < *(int *)(param_1 + 0x2c8) && (*(int *)(tmp_i2 + 0x16c) == 0)))) &&
     ((*(int *)(tmp_i2 + 0x168) == 0 &&
      ((*(int *)(tmp_i2 + 0x164) == 0 && (*(int *)(param_2 + 0xa4) != *(int *)(tmp_i2 + 3000))))))) {
    if (*(int *)(param_2 + 0x300) < 0xfa) {
      *(int *)(param_2 + 0x300) =
           (int)(100 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4)) + *(int *)(param_2 + 0x300);
    }
    else {
      *(int *)(param_2 + 0x29c) = *(int *)(param_2 + 0x24c) + 20000;
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x16c) = 1;
      *(uint *)(*(int *)(param_1 + 400) + 0x170) = *(uint *)(param_2 + 0xa8) & 1;
      *(uint *)(*(int *)(param_1 + 400) + 0x174) = *(uint *)(param_2 + 0xa8) & 2;
      *(uint *)(*(int *)(param_1 + 400) + 0x178) = *(uint *)(param_2 + 0xa8) & 4;
      *(int *)(param_2 + 0xa4) = *(int *)(param_2 + 0xa4) + 4;
      *(int *)(param_2 + 0x2f0) = param_1;
      *(uint32_t *)(param_2 + 0x58) = 1;
      G_AddEvent(param_1,0x57,0);
      G_AddSkillPoints(param_1,6,0x40a00000);
      if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
        G_DebugAddSkillPoints(param_1,6,0x40a00000,"stealing uniform");
      }
      Q_strncpyz(*(int *)(param_1 + 400) + 0x533c,
                 *(int *)(g_entities + *(int *)(param_2 + 0xac) * 0x600 + 400) + 0x5f8,0x24);
      tmp_u4 = 0;
      if (*(int *)(g_entities + *(int *)(param_2 + 0xac) * 0x600 + 400) != 0) {
        tmp_u4 = *(uint32_t *)
                 (*(int *)(g_entities + *(int *)(param_2 + 0xac) * 0x600 + 400) + 0xc4c);
      }
      tmp_u3 = 1;
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x5360) = tmp_u4;
      ClientUserinfoChanged(*(uint32_t *)(param_1 + 0xac));
      tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0xba0);
      *tmp_pi1 = *tmp_pi1 + 1;
      if ((g_entities[*(int *)(param_2 + 0xac) * 0x600 + 0x128] & 8) == 0) {
        nitrox_CheckGlobalAwards(param_1,0xe,1);
      }
    }
  }
  return tmp_u3;
}

void G_ClassSteal_RemoveTools(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i1 = param_1 + 0x3d4;
  COM_BitClear(tmp_i1,0xf);
  COM_BitClear(tmp_i1,0x14);
  COM_BitClear(tmp_i1,0x19);
  COM_BitClear(tmp_i1,0x1c);
  COM_BitClear(tmp_i1,0x30);
  COM_BitClear(tmp_i1,0x1a);
  COM_BitClear(tmp_i1,0x1b);
  COM_BitClear(tmp_i1,0x15);
  COM_BitClear(tmp_i1,0xc);
  COM_BitClear(tmp_i1,0x12);
  COM_BitClear(tmp_i1,0xb);
  COM_BitClear(tmp_i1,0x2f);
  COM_BitClear(tmp_i1,0x2b);
  COM_BitClear(tmp_i1,0x32);
  COM_BitClear(tmp_i1,0x31);
  COM_BitClear(tmp_i1,0x33);
  if (*(int *)(param_1 + 0xbc8) == 4) {
    *(uint32_t *)(param_1 + 0x52ac) = 1;
    COM_BitSet(tmp_i1,0xe);
    COM_BitSet(tmp_i1,0x26);
    tmp_i2 = COM_BitCheck(tmp_i1,0x23);
    if (tmp_i2 != 0) {
      COM_BitClear(tmp_i1,0x23);
      COM_BitSet(tmp_i1,0x2d);
    }
    tmp_i2 = COM_BitCheck(tmp_i1,0x22);
    if (tmp_i2 != 0) {
      COM_BitClear(tmp_i1,0x22);
      COM_BitSet(tmp_i1,0x2c);
    }
  }
  else {
    *(uint32_t *)(param_1 + 0x52ac) = 0;
    COM_BitClear(tmp_i1,0xe);
    COM_BitClear(tmp_i1,0x26);
    tmp_i2 = COM_BitCheck(tmp_i1,0x2d);
    if (tmp_i2 != 0) {
      COM_BitClear(tmp_i1,0x2d);
      COM_BitSet(tmp_i1,0x23);
    }
    tmp_i2 = COM_BitCheck(tmp_i1,0x2c);
    if (tmp_i2 != 0) {
      COM_BitClear(tmp_i1,0x2c);
      COM_BitSet(tmp_i1,0x22);
      G_AddClassSpecificTools(param_1);
      return;
    }
  }
  G_AddClassSpecificTools(param_1);
  return;
}

uint32_t G_ClassSteal(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_u1 = 0;
  if ((((3 < GHIDRA_FIELD(g_war, 12, 4) - 1) && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) && (GHIDRA_FIELD(g_classChange, 12, 4) != 0)) &&
     ((*(int *)(param_2 + 0xa8) != *(int *)(*(int *)(param_1 + 400) + 0xbc8) &&
      (*(int *)(param_2 + 0x2f0) == 0)))) {
    tmp_i2 = *(int *)(param_2 + 0x300);
    if (tmp_i2 < 0xfa) {
      if (tmp_i2 == 0) {
        nitmod_cp(param_1,0x23);
        tmp_i2 = *(int *)(param_2 + 0x300);
      }
      *(int *)(param_2 + 0x300) = (int)(100 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4)) + tmp_i2;
      tmp_u1 = 1;
    }
    else {
      *(int *)(param_2 + 0x29c) = *(int *)(param_2 + 0x24c) + 20000;
      *(uint32_t *)(param_2 + 0x58) = 1;
      *(int *)(param_2 + 0x2f0) = param_1;
      G_AddEvent(param_1,0x57,0);
      *(int *)(param_2 + 0xa4) = *(int *)(param_2 + 0xa4) + 4;
      tmp_i2 = G_GetPrimaryWeaponForClient(*(uint32_t *)(param_1 + 400));
      *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc8) = *(uint32_t *)(param_2 + 0xa8);
      G_ClassSteal_RemoveTools(*(uint32_t *)(param_1 + 400));
      if (tmp_i2 - 1U < 0x33) {
        tmp_i3 = G_CanPickupWeapon(tmp_i2,param_1);
        if (tmp_i3 == 0) {
          G_DropWeapon(param_1,tmp_i2);
        }
        tmp_i2 = G_GetPrimaryWeaponForClient(*(uint32_t *)(param_1 + 400));
        if ((tmp_i2 != 0) && (tmp_i3 = G_CanPickupWeapon(tmp_i2,param_1), tmp_i3 == 0)) {
          G_DropWeapon(param_1,tmp_i2);
        }
      }
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x16c) = 0;
      ClientUserinfoChanged(*(uint32_t *)(param_1 + 0xac));
      tmp_u1 = 1;
    }
  }
  return tmp_u1;
}

uint32_t G_PushPlayer(int param_1,int param_2)
{
  uint *tmp_pu1;
  float tmp_f2;
  int tmp_i3;
  uint32_t tmp_u4;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_u4 = 0;
  if ((((GHIDRA_FIELD(g_shove, 12, 4) != 0) && (0 < *(int *)(param_1 + 0x2c8))) &&
      (tmp_i3 = *(int *)(param_1 + 400), 499 < g_unk_00abe908 - *(int *)(tmp_i3 + 0x5308))) &&
     (*(int *)(tmp_i3 + 0x154) == 0)) {
    *(int *)(tmp_i3 + 0x5308) = g_unk_00abe908;
    AngleVectors(*(int *)(param_1 + 400) + 0xb0,&local_28,0,0);
    VectorNormalizeFast(&local_28);
    tmp_f2 = (float)(GHIDRA_FIELD(g_shove, 12, 4) * 5);
    local_28 = local_28 * tmp_f2;
    local_24 = local_24 * tmp_f2;
    if (((tmp_f2 * local_20 <= ABS(local_28)) || (tmp_f2 * local_20 <= ABS(local_24))) ||
       (GHIDRA_FIELD(g_shoveNoZ, 12, 4) != 0)) {
      tmp_f2 = 64.0;
    }
    else {
      tmp_f2 = (float)(int)GHIDRA_FIELD(g_shove, 12, 4) * local_20 * 4.0;
    }
    *(float *)(param_2 + 0x24) = *(float *)(param_2 + 0x24) + local_28;
    *(float *)(param_2 + 0x28) = *(float *)(param_2 + 0x28) + local_24;
    *(float *)(param_2 + 0x2c) = *(float *)(param_2 + 0x2c) + tmp_f2;
    *(float *)(*(int *)(param_2 + 400) + 0x20) =
         local_28 + *(float *)(*(int *)(param_2 + 400) + 0x20);
    *(float *)(*(int *)(param_2 + 400) + 0x24) =
         local_24 + *(float *)(*(int *)(param_2 + 400) + 0x24);
    *(float *)(*(int *)(param_2 + 400) + 0x28) = tmp_f2 + *(float *)(*(int *)(param_2 + 400) + 0x28);
    *(uint32_t *)(*(int *)(param_2 + 400) + 0x5318) = 1;
    *(int *)(*(int *)(param_2 + 400) + 0x531c) = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    G_AddEvent(param_2,0x60,0);
    *(uint32_t *)(*(int *)(param_2 + 400) + 0x10) = 100;
    tmp_pu1 = (uint *)(*(int *)(param_2 + 400) + 0xc);
    *tmp_pu1 = *tmp_pu1 | 0x40;
    tmp_u4 = 1;
  }
  return tmp_u4;
}

uint32_t G_DragCorpse(int param_1,int param_2)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  long double tmp_l4;
  float local_18;
  float local_14;
  uint32_t local_10;
  
  if (GHIDRA_FIELD(g_dragCorpse, 12, 4) != 0) {
    local_18 = *(float *)(param_1 + 0x168) - *(float *)(param_2 + 0x168);
    local_10 = 0;
    local_14 = *(float *)(param_1 + 0x16c) - *(float *)(param_2 + 0x16c);
    tmp_l4 = (long double)VectorNormalize(&local_18);
    if ((tmp_l4 <= (long double)85.0) && ((long double)40.0 <= tmp_l4)) {
      tmp_i1 = *(int *)(param_2 + 400);
      tmp_f2 = local_18 * 110.0 - *(float *)(tmp_i1 + 0x20);
      tmp_f3 = local_14 * 110.0 - *(float *)(tmp_i1 + 0x24);
      *(float *)(param_2 + 0x24) = *(float *)(param_2 + 0x24) + tmp_f2;
      *(float *)(param_2 + 0x28) = *(float *)(param_2 + 0x28) + tmp_f3;
      *(float *)(param_2 + 0x2c) = *(float *)(param_2 + 0x2c) + 0.0;
      *(float *)(tmp_i1 + 0x20) = tmp_f2 + *(float *)(tmp_i1 + 0x20);
      *(float *)(*(int *)(param_2 + 400) + 0x24) =
           tmp_f3 + *(float *)(*(int *)(param_2 + 400) + 0x24);
      *(float *)(*(int *)(param_2 + 400) + 0x28) = *(float *)(*(int *)(param_2 + 400) + 0x28) + 0.0;
      return 1;
    }
  }
  return 0;
}

void G_LeaveTank(uint32_t *param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  uint8_t local_54 [4];
  int local_50;
  
  tmp_i1 = param_1[0x111];
  if (tmp_i1 != 0) {
    if (param_2 != 0) {
      AnglesToAxis(tmp_i1 + 0x74,&local_78);
      tmp_i2 = param_1[100];
      local_84 = local_6c * 128.0 + *(float *)(tmp_i2 + 0x14);
      local_80 = local_68 * 128.0 + *(float *)(tmp_i2 + 0x18);
      local_7c = local_64 * 128.0 + *(float *)(tmp_i2 + 0x1c);
      trap_Trace(local_54,&local_84,&playerMins,&playerMaxs,&local_84,0xffffffff,1);
      if (local_50 != 0) {
        tmp_i2 = param_1[100];
        local_84 = local_6c * -128.0 + *(float *)(tmp_i2 + 0x14);
        local_80 = local_68 * -128.0 + *(float *)(tmp_i2 + 0x18);
        local_7c = local_64 * -128.0 + *(float *)(tmp_i2 + 0x1c);
        trap_Trace(local_54,&local_84,&playerMins,&playerMaxs,&local_84,0xffffffff,1);
        if (local_50 != 0) {
          tmp_i2 = param_1[100];
          local_84 = local_78 * -224.0 + *(float *)(tmp_i2 + 0x14);
          local_80 = local_74 * -224.0 + *(float *)(tmp_i2 + 0x18);
          local_7c = local_70 * -224.0 + *(float *)(tmp_i2 + 0x1c);
          trap_Trace(local_54,&local_84,&playerMins,&playerMaxs,&local_84,0xffffffff,1);
          if (local_50 != 0) {
            tmp_i2 = param_1[100];
            local_84 = local_78 * 224.0 + *(float *)(tmp_i2 + 0x14);
            local_80 = local_74 * 224.0 + *(float *)(tmp_i2 + 0x18);
            local_7c = local_70 * 224.0 + *(float *)(tmp_i2 + 0x1c);
            trap_Trace(local_54,&local_84,&playerMins,&playerMaxs,&local_84,0xffffffff,1);
            if (local_50 != 0) {
              return;
            }
          }
        }
      }
      tmp_i2 = param_1[100];
      *(uint32_t *)(tmp_i2 + 0x28) = 0;
      *(uint32_t *)(tmp_i2 + 0x24) = 0;
      *(uint32_t *)(tmp_i2 + 0x20) = 0;
      TeleportPlayer(param_1,&local_84,param_1[100] + 0xb0);
    }
    *(uint32_t *)(tmp_i1 + 0x4d4) = *(uint32_t *)(param_1[100] + 0x51c);
    *(uint32_t *)(tmp_i1 + 0x4d0) = *(uint32_t *)(param_1[100] + 0x2c);
    *(uint32_t *)(param_1[100] + 0x2c) = param_1[0x134];
    tmp_u3 = va("%i %i %s",*param_1,*(uint32_t *)param_1[0x110],param_1 + 0x100);
    G_RemoveConfigstringIndex(tmp_u3,0x309,0x40);
    G_Script_ScriptEvent(tmp_i1,&g_unk_0024c710,"unmount");
    param_1[2] = param_1[2] & 0xffff7fff;
    param_1[0x110] = 0;
    *(uint8_t *)(param_1 + 0x100) = 0;
    *(uint *)(param_1[100] + 0x68) = *(uint *)(param_1[100] + 0x68) & 0xffff7fff;
    *(uint32_t *)(tmp_i1 + 0x444) = 0;
    *(uint32_t *)(tmp_i1 + 0xe4) = 0xffffffff;
    param_1[0x111] = 0;
    if ((param_3 != 0) && (GHIDRA_FIELD(n_tankMountDelay, 12, 4) != 0)) {
      param_1[0x17d] = GHIDRA_FIELD(n_tankMountDelay, 12, 4) * 1000 + g_unk_00abe908;
    }
  }
  return;
}

void G_UpdateSpawnCounts(void)
{
  uint tmp_u1;
  bool tmp_b2;
  char *tmp_pc3;
  long tmp_l4;
  uint tmp_u5;
  int tmp_i6;
  uint32_t tmp_u7;
  int *tmp_pi8;
  int local_440;
  int local_43c;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x6d3f9;
  if (0 < g_unk_00abfa98) {
    local_43c = 1;
    do {
      tmp_i6 = local_43c + -1;
      nitrox_GetConfigstring(local_43c + 0x272,local_41c,0x400);
      tmp_pc3 = (char *)Info_ValueForKey(local_41c,"c");
      tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pc3 = (char *)Info_ValueForKey(local_41c,&g_unk_0026176c);
      tmp_u5 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_u5 = tmp_u5 & 0xfffffeff;
      if (g_unk_00abe938 < 1) {
        local_440 = 0;
      }
      else if (g_unk_02aa29b8 == tmp_i6) {
        tmp_pi8 = &g_unk_00abe944;
        if (g_unk_02aa29bc == tmp_i6) {
          local_440 = 0;
          do {
            tmp_i6 = *tmp_pi8 * 0x54dc + level;
            tmp_u1 = *(uint *)(tmp_i6 + 3000);
            if (tmp_u1 - 1 < 2) {
              tmp_i6 = *(int *)(tmp_i6 + 0xbd4);
              if ((tmp_u1 == tmp_u5) && (tmp_i6 == local_43c)) {
                local_440 = local_440 + 1;
              }
              else {
                local_440 = local_440 + (uint)(tmp_i6 == 0);
              }
            }
            tmp_pi8 = tmp_pi8 + 1;
          } while (tmp_pi8 != &g_unk_00abe944 + g_unk_00abe938);
        }
        else {
          local_440 = 0;
          do {
            tmp_i6 = *tmp_pi8 * 0x54dc + level;
            tmp_u1 = *(uint *)(tmp_i6 + 3000);
            if (tmp_u1 - 1 < 2) {
              if (tmp_u1 == tmp_u5) {
                tmp_i6 = *(int *)(tmp_i6 + 0xbd4);
                if (tmp_i6 == local_43c) {
                  local_440 = local_440 + 1;
                  goto LAB_0006d618;
                }
              }
              else {
                tmp_i6 = *(int *)(tmp_i6 + 0xbd4);
              }
              if (tmp_i6 == 0) {
                local_440 = local_440 + (uint)(tmp_u1 == 1);
              }
            }
LAB_0006d618:
            tmp_pi8 = tmp_pi8 + 1;
          } while (tmp_pi8 != &g_unk_00abe944 + g_unk_00abe938);
        }
      }
      else if (g_unk_02aa29bc == tmp_i6) {
        tmp_pi8 = &g_unk_00abe944;
        local_440 = 0;
        do {
          tmp_i6 = *tmp_pi8 * 0x54dc + level;
          tmp_u1 = *(uint *)(tmp_i6 + 3000);
          if (tmp_u1 - 1 < 2) {
            if (tmp_u1 == tmp_u5) {
              tmp_i6 = *(int *)(tmp_i6 + 0xbd4);
              if (tmp_i6 == local_43c) {
                local_440 = local_440 + 1;
                goto LAB_0006d690;
              }
            }
            else {
              tmp_i6 = *(int *)(tmp_i6 + 0xbd4);
            }
            if (tmp_i6 == 0) {
              local_440 = local_440 + (uint)(tmp_u1 != 1);
            }
          }
LAB_0006d690:
          tmp_pi8 = tmp_pi8 + 1;
        } while (tmp_pi8 != &g_unk_00abe944 + g_unk_00abe938);
      }
      else {
        tmp_pi8 = &g_unk_00abe944;
        local_440 = 0;
        do {
          while( true ) {
            tmp_i6 = *tmp_pi8 * 0x54dc + level;
            tmp_u1 = *(uint *)(tmp_i6 + 3000);
            if ((1 < tmp_u1 - 1) || (tmp_u1 != tmp_u5)) break;
            tmp_pi8 = tmp_pi8 + 1;
            local_440 = local_440 + (uint)(*(int *)(tmp_i6 + 0xbd4) == local_43c);
            if (tmp_pi8 == &g_unk_00abe944 + g_unk_00abe938) goto LAB_0006d580;
          }
          tmp_pi8 = tmp_pi8 + 1;
        } while (tmp_pi8 != &g_unk_00abe944 + g_unk_00abe938);
      }
LAB_0006d580:
      if (local_440 != tmp_l4) {
        tmp_u7 = va("%i",local_440);
        Info_SetValueForKey(local_41c,"c",tmp_u7);
        nitrox_SetConfigstring(local_43c + 0x272,local_41c);
      }
      tmp_b2 = local_43c < g_unk_00abfa98;
      local_43c = local_43c + 1;
    } while (tmp_b2);
  }
  return;
}

void G_MakeReady(int param_1)
{
  uint *tmp_pu1;
  
  tmp_pu1 = (uint *)(*(int *)(param_1 + 400) + 0x68);
  *tmp_pu1 = *tmp_pu1 | 8;
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 8;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0x998) = 1;
  return;
}

void G_MakeUnready(int param_1)
{
  uint *tmp_pu1;
  
  tmp_pu1 = (uint *)(*(int *)(param_1 + 400) + 0x68);
  *tmp_pu1 = *tmp_pu1 & 0xfffffff7;
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xfffffff7;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0x998) = 0;
  return;
}

void G_CalcClientAccuracies(void)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int *tmp_pi3;
  int *tmp_pi4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int local_24;
  int *local_20;
  uint8_t *local_1c;
  
  tmp_u2 = GHIDRA_FIELD(g_maxclients, 12, 4);
  if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
    local_1c = g_entities;
    local_24 = 0;
    local_20 = (int *)(level + 0xcac);
    do {
      if (*(int *)(local_1c + 0x194) == 0) {
        local_20[0x11af] = 0;
        local_20[0x11b0] = 0;
      }
      else {
        tmp_i5 = 0;
        tmp_i6 = 0;
        tmp_i7 = 0;
        tmp_pi3 = local_20;
        do {
          tmp_pi4 = tmp_pi3 + 5;
          tmp_i6 = tmp_i6 + *tmp_pi3;
          tmp_i5 = tmp_i5 + tmp_pi3[3];
          tmp_i7 = tmp_pi3[2] + tmp_i7;
          tmp_pi3 = tmp_pi4;
        } while (tmp_pi4 != local_20 + 0x82);
        tmp_f1 = 0.0;
        if (tmp_i6 != 0) {
          tmp_f1 = (float)(tmp_i5 * 100) / (float)tmp_i6;
        }
        local_20[0x11af] = (int)tmp_f1;
        local_20[0x11b0] = tmp_i7;
      }
      local_24 = local_24 + 1;
      local_1c = local_1c + 0x600;
      local_20 = local_20 + 0x1537;
    } while (local_24 < (int)tmp_u2);
  }
  return;
}

void G_commands_cmd(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint8_t **tmp_ppu3;
  int tmp_i4;
  
  tmp_i2 = 0;
  tmp_i4 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  trap_SendServerCommand
            (tmp_i4,"print \"^5\nAvailable OSP Game-Commands:\n----------------------------\n\"");
  tmp_ppu3 = &aCommandInfo;
  do {
    while (6 < tmp_i2) {
      tmp_i2 = tmp_i2 + 1;
      tmp_u1 = va("print \"^3%-17s%-17s%-17s\n\"",*tmp_ppu3,tmp_ppu3[0x32],tmp_ppu3[100]);
      trap_SendServerCommand(tmp_i4,tmp_u1);
      tmp_ppu3 = tmp_ppu3 + 5;
      if (tmp_i2 == 10) goto LAB_000734c9;
    }
    tmp_i2 = tmp_i2 + 1;
    tmp_u1 = va("print \"^3%-17s%-17s%-17s%-17s\n\"",*tmp_ppu3,tmp_ppu3[0x32],tmp_ppu3[100],
               tmp_ppu3[0x96]);
    trap_SendServerCommand(tmp_i4,tmp_u1);
    tmp_ppu3 = tmp_ppu3 + 5;
  } while (tmp_i2 != 10);
LAB_000734c9:
  trap_SendServerCommand(tmp_i4,"print \"\nType: ^3\\command_name ?^7 for more information\n\"");
  return;
}

void G_players_cmd(int param_1)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  long tmp_l3;
  char *tmp_pc4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  char *tmp_pc8;
  uint8_t *tmp_pu9;
  char *local_580;
  char *local_578;
  char local_560 [16];
  char local_550 [16];
  uint8_t local_540 [26];
  uint8_t local_526;
  char local_51c [256];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x734f9;
  if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
    if (param_1 == 0) {
      G_Printf(" ID : Player                    Nudge  Rate  MaxPkts  Snaps\n");
      G_Printf("-----------------------------------------------------------\n");
      goto LAB_00073b67;
    }
    tmp_i7 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand
              (tmp_i7,
               "print \"\n^3 ID^1 : ^3Player                    Nudge  Rate  MaxPkts  Snaps\n\"");
    trap_SendServerCommand
              (tmp_i7,"print \"^1-----------------------------------------------------------^7\n\"");
LAB_000735b2:
    local_580 = (char *)trap_Cvar_VariableIntegerValue("sv_maxrate");
    if (0 < g_unk_00abe938) goto LAB_000735dc;
    tmp_i6 = 0;
LAB_00073a15:
    tmp_u1 = va("print \"\n^3%2d^7 total players\n\n\"",tmp_i6);
    trap_SendServerCommand(tmp_i7,tmp_u1);
  }
  else {
    if (param_1 != 0) {
      tmp_i7 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
      trap_SendServerCommand
                (tmp_i7,
                 "print \"\n^3Status^1   : ^3ID^1 : ^3Player                    Nudge  Rate  MaxPkts  Snaps\n\""
                );
      trap_SendServerCommand
                (tmp_i7,
                 "print \"^1---------------------------------------------------------------------^7\n\""
                );
      goto LAB_000735b2;
    }
    G_Printf("Status   : ID : Player                    Nudge  Rate  MaxPkts  Snaps\n");
    G_Printf("---------------------------------------------------------------------\n");
LAB_00073b67:
    local_580 = (char *)trap_Cvar_VariableIntegerValue("sv_maxrate");
    if (g_unk_00abe938 < 1) {
      tmp_i6 = 0;
    }
    else {
LAB_000735dc:
      tmp_i7 = 0;
LAB_000736b1:
      do {
        tmp_i6 = tmp_i7;
        tmp_i7 = (&g_unk_00abe944)[tmp_i6];
        tmp_i5 = tmp_i7 * 0x54dc + level;
        SanitizeString(tmp_i5 + 0x5f8,local_540,1);
        local_526 = 0;
        local_550[0] = '\0';
        local_560[0] = '\0';
        if ((g_entities[tmp_i7 * 0x600 + 0x128] & 8) == 0) {
          if (*(int *)(tmp_i5 + 0x5ac) != 1) {
            trap_GetUserinfo(tmp_i7,local_41c,0x400);
            tmp_pc2 = (char *)Info_ValueForKey(local_41c,"rate");
            if (((int)local_580 < 1) ||
               (tmp_l3 = strtol(tmp_pc2,(char **)0x0,10), tmp_l3 <= (int)local_580)) {
              local_578 = (char *)strtol(tmp_pc2,(char **)0x0,10);
            }
            else {
              local_578 = local_580;
            }
            tmp_pc2 = (char *)Info_ValueForKey(local_41c,"snaps");
            tmp_pc4 = (char *)strtol(tmp_pc2,(char **)0x0,10);
            tmp_pu9 = *(uint8_t **)(tmp_i5 + 0x980);
            tmp_pc8 = *(char **)(tmp_i5 + 0x984);
            tmp_pc2 = "%5d%6d%9d%7d";
            goto LAB_000737e5;
          }
          tmp_pc2 = (char *)va(&g_unk_0024e6e9,"^3>>> CONNECTING <<<");
          strcpy(local_51c,tmp_pc2);
        }
        else {
          tmp_pc4 = "     --";
          tmp_pu9 = &g_unk_00247f7f;
          local_578 = " -----";
          tmp_pc8 = "[BOT]";
          tmp_pc2 = "%s%s%s%s";
LAB_000737e5:
          tmp_pc2 = (char *)va(tmp_pc2,tmp_pc8,local_578,tmp_pu9,tmp_pc4);
          strcpy(local_51c,tmp_pc2);
        }
        if (GHIDRA_FIELD(g_gamestate, 12, 4) != 0) {
          if ((*(int *)(tmp_i5 + 3000) == 3) || (*(int *)(tmp_i5 + 0x5ac) == 1)) {
            tmp_pc2 = "^5--------^1 :";
            tmp_pc4 = "-------- :";
          }
          else if ((*(int *)(tmp_i5 + 0x998) == 0) && ((g_entities[tmp_i7 * 0x600 + 0x128] & 8) == 0))
          {
            tmp_pc2 = "NOTREADY^1 :";
            tmp_pc4 = "NOTREADY :";
          }
          else {
            tmp_pc2 = "^3(READY)^1  :";
            tmp_pc4 = "(READY)  :";
          }
          if (param_1 == 0) {
            tmp_pc2 = tmp_pc4;
          }
          strcpy(local_560,tmp_pc2);
        }
        if (*(int *)(tmp_i5 + 0xc80) != 0) {
          local_550[0] = 'R';
        }
        tmp_i5 = *(int *)(tmp_i5 + 3000);
        if (param_1 == 0) {
          tmp_pc2 = " ";
          if (1 < (int)GHIDRA_FIELD(g_gametype, 12, 4)) {
            if (tmp_i5 == 1) {
              tmp_pc2 = "X";
            }
            else {
LAB_000738b5:
              if (tmp_i5 != 2) goto LAB_000738be;
              tmp_pc2 = "^4L^7";
              if (param_1 != 0) goto LAB_000738cd;
              tmp_pc2 = "L";
            }
          }
LAB_0007399b:
          G_Printf("%s%s%2d%s: %-26s%s  %s\n",local_560,tmp_pc2,tmp_i7,&g_unk_002612df,local_540,
                   local_51c,local_550);
          tmp_i7 = tmp_i6 + 1;
          if (g_unk_00abe938 <= tmp_i6 + 1) break;
          goto LAB_000736b1;
        }
        tmp_pc2 = "^7 ";
        if (1 < (int)GHIDRA_FIELD(g_gametype, 12, 4)) {
          if (tmp_i5 != 1) {
            tmp_pc2 = "^7 ";
            goto LAB_000738b5;
          }
          tmp_pc2 = "^1X^7";
LAB_000738be:
          if (param_1 == 0) goto LAB_0007399b;
        }
LAB_000738cd:
        if (local_550[0] == '\0') {
          tmp_pc4 = "^7";
        }
        else {
          tmp_pc4 = "^3";
        }
        tmp_u1 = va("print \"%s%s%2d%s^1:%s %-26s^7%s  ^3%s\n\"",local_560,tmp_pc2,tmp_i7,&g_unk_002612df
                   ,tmp_pc4,local_540,local_51c,local_550);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
        tmp_i7 = tmp_i6 + 1;
      } while (tmp_i6 + 1 < g_unk_00abe938);
      tmp_i6 = tmp_i6 + 1;
      if (param_1 != 0) {
        tmp_i7 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        goto LAB_00073a15;
      }
    }
    G_Printf("\n%2d total players\n\n",tmp_i6);
  }
  if (1 < (int)GHIDRA_FIELD(g_gametype, 12, 4)) {
    tmp_i7 = 0;
    do {
      if (*(int *)(teamInfo + tmp_i7 * 4 + 0x10) != 0) {
        if (param_1 == 0) {
          G_Printf("** %s team is speclocked.\n",*(uint32_t *)(aTeams + tmp_i7 + 4));
        }
        else {
          tmp_u1 = va("print \"** %s team is speclocked.\n\"");
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
        }
      }
      tmp_i7 = tmp_i7 + 4;
    } while (tmp_i7 != 8);
  }
  return;
}

void G_scores_cmd(uint32_t param_1)
{
  G_printMatchInfo(param_1);
  return;
}

void G_statsall_cmd(int param_1)
{
  int *tmp_pi1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  if (0 < g_unk_00abe93c) {
    tmp_i3 = 0;
    do {
      tmp_pi1 = &g_unk_00abe944 + tmp_i3;
      tmp_i3 = tmp_i3 + 1;
      tmp_u2 = G_createStats(g_entities + *tmp_pi1 * 0x600);
      tmp_u2 = va("ws %s\n",tmp_u2);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
    } while (tmp_i3 < g_unk_00abe93c);
  }
  return;
}

void G_cheaters_cmd(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  uint tmp_u4;
  size_t tmp_s5;
  uint tmp_u6;
  char *tmp_pc7;
  uint *tmp_pu8;
  uint *tmp_pu9;
  int tmp_i10;
  int tmp_i11;
  int tmp_i12;
  int tmp_i13;
  int tmp_i14;
  uint8_t *tmp_pu15;
  int local_870;
  uint *local_868;
  int local_85c;
  uint local_840 [9];
  uint8_t local_81c [1024];
  uint local_41c [258];
  uint32_t uStack_14;
  
  uStack_14 = 0x73d09;
  if (0 < g_unk_00abe938) {
    tmp_i11 = 0;
    local_85c = 1;
    tmp_i13 = 0;
    do {
      while( true ) {
        local_41c[0] = 0;
        tmp_u4 = 0;
        do {
          tmp_u3 = tmp_u4;
          *(uint32_t *)((int)local_41c + tmp_u3 + 4) = 0;
          *(uint32_t *)((int)local_41c + tmp_u3 + 8) = 0;
          tmp_u4 = tmp_u3 + 8;
        } while (tmp_u3 + 8 < 0x3f8);
        *(uint32_t *)((int)local_41c + tmp_u3 + 0xc) = 0;
        if (*(int *)(*(int *)(g_entities + (&g_unk_00abe944)[tmp_i13] * 0x600 + 400) + 0xf44) != 0)
        break;
        tmp_i13 = tmp_i13 + 1;
        if (g_unk_00abe938 <= tmp_i13) goto LAB_00073dbf;
      }
      tmp_i11 = tmp_i11 + 1;
      DecolorString(*(int *)(g_entities + (&g_unk_00abe944)[tmp_i13] * 0x600 + 400) + 0x5f8,local_41c);
      tmp_pu9 = local_41c;
      do {
        tmp_pu8 = tmp_pu9;
        tmp_u3 = *tmp_pu8 + 0xfefefeff & ~*tmp_pu8;
        tmp_u4 = tmp_u3 & 0x80808080;
        tmp_pu9 = tmp_pu8 + 1;
      } while (tmp_u4 == 0);
      if ((tmp_u3 & 0x8080) == 0) {
        tmp_pu9 = (uint *)((int)tmp_pu8 + 6);
        tmp_u4 = tmp_u4 >> 0x10;
      }
      tmp_i10 = (int)tmp_pu9 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_41c);
      if (tmp_i10 <= local_85c) {
        tmp_i10 = local_85c;
      }
      tmp_i13 = tmp_i13 + 1;
      local_85c = tmp_i10;
    } while (tmp_i13 < g_unk_00abe938);
LAB_00073dbf:
    if (tmp_i11 != 0) {
      G_shrubbot_buffer_begin();
      Com_sprintf(local_81c,0x400,"^9%%s | %%-%ds | %%-32s | %%s\n",local_85c);
      tmp_u1 = va(local_81c,&g_unk_0024802e,"Name","NGUID","Violation(s)");
      G_shrubbot_buffer_print(param_1,tmp_u1);
      if (0 < g_unk_00abe938) {
        local_870 = 0;
        tmp_i11 = g_unk_00abe938;
        do {
          tmp_i13 = (&g_unk_00abe944)[local_870];
          tmp_i2 = tmp_i13 * 0x600;
          tmp_i10 = *(int *)(g_entities + tmp_i2 + 400);
          tmp_u4 = *(uint *)(tmp_i10 + 0xf44);
          if (0 < (int)tmp_u4) {
            local_41c[0] = 0;
            tmp_u3 = 0;
            do {
              tmp_u6 = tmp_u3;
              *(uint32_t *)((int)local_41c + tmp_u6 + 4) = 0;
              *(uint32_t *)((int)local_41c + tmp_u6 + 8) = 0;
              tmp_u3 = tmp_u6 + 8;
            } while (tmp_u6 + 8 < 0x3f8);
            *(uint32_t *)((int)local_41c + tmp_u6 + 0xc) = 0;
            if (1 < NxAC_ViolationsCount) {
              tmp_pu15 = NxAC_Violations;
              tmp_i14 = 1;
              tmp_i12 = 0;
              tmp_i11 = NxAC_ViolationsCount;
              do {
                if ((*(uint *)(tmp_pu15 + 0xc) & tmp_u4) == 0) {
                  if (tmp_i11 <= tmp_i14 + 1) break;
                }
                else {
                  tmp_u1 = NxAC_ViolationStringForIndex(tmp_i14);
                  if (tmp_i12 == 0) {
                    tmp_pc7 = "";
                  }
                  else {
                    tmp_pc7 = ", ";
                  }
                  tmp_i12 = tmp_i12 + 1;
                  tmp_u1 = va("%s%s",tmp_pc7,tmp_u1);
                  Q_strcat(local_41c,0x400,tmp_u1);
                  tmp_i10 = *(int *)(g_entities + tmp_i2 + 400);
                  tmp_i11 = NxAC_ViolationsCount;
                  if (NxAC_ViolationsCount <= tmp_i14 + 1) break;
                }
                tmp_pu15 = tmp_pu15 + 0xc;
                tmp_i14 = tmp_i14 + 1;
                tmp_u4 = *(uint *)(tmp_i10 + 0xf44);
              } while( true );
            }
            local_868 = local_41c;
            DecolorString(tmp_i10 + 0x5f8,local_840);
            tmp_pu9 = local_840;
            do {
              tmp_pu8 = tmp_pu9;
              tmp_u3 = *tmp_pu8 + 0xfefefeff & ~*tmp_pu8;
              tmp_u4 = tmp_u3 & 0x80808080;
              tmp_pu9 = tmp_pu8 + 1;
            } while (tmp_u4 == 0);
            if ((tmp_u3 & 0x8080) == 0) {
              tmp_pu9 = (uint *)((int)tmp_pu8 + 6);
              tmp_u4 = tmp_u4 >> 0x10;
            }
            tmp_s5 = strlen((char *)(*(int *)(g_entities + tmp_i2 + 400) + 0x5f8));
            Com_sprintf(local_81c,0x400,"^g%%i ^9| ^7%%-%ds ^9| ^g%%-32s ^9| ^g%%s\n",
                        (tmp_s5 + local_85c) -
                        ((int)tmp_pu9 +
                        ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_840)));
            tmp_u1 = va(local_81c,tmp_i13,*(int *)(g_entities + tmp_i2 + 400) + 0x5f8,
                       *(int *)(g_entities + tmp_i2 + 400) + 0x61c,local_868);
            G_shrubbot_buffer_print(param_1,tmp_u1);
            tmp_i11 = g_unk_00abe938;
          }
          local_870 = local_870 + 1;
        } while (local_870 < tmp_i11);
      }
      G_shrubbot_buffer_end(param_1);
      return;
    }
  }
  G_shrubbot_print(param_1,"^xcheaters: ^gNo cheaters detected.\n");
  return;
}

void G_say_teamnl_cmd(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = G_shrubbot_mute_check(*(int *)(param_1 + 400) + 0x61c,*(int *)(param_1 + 400) + 0xaf4);
  if ((tmp_i1 != 0) || (*(int *)(*(int *)(param_1 + 400) + 0xbf0) != 0)) {
    return;
  }
  tmp_i1 = ClientIsFlooding(param_1,0);
  if ((tmp_i1 != 0) && (tmp_i1 = nitrox_CheckPermission(param_1,1), tmp_i1 == 0)) {
    trap_SendServerCommand
              ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
               "print \"^1Flood Protection: ^7dropping teamchat\n\"");
    return;
  }
  Cmd_Say_f(param_1,3,0);
  return;
}

void G_specinvite_cmd(int param_1,int param_2)
{
  uint tmp_u1;
  int tmp_i2;
  char *tmp_pc3;
  int tmp_i4;
  uint32_t tmp_u5;
  uint8_t local_41c [1036];
  
  if (GHIDRA_FIELD(team_nocontrols, 12, 4) == 0) {
    tmp_i4 = *(int *)(*(int *)(param_1 + 400) + 0x988);
    if (g_unk_00abe908 < tmp_i4) {
      tmp_pc3 = (char *)va("print \"Wait another %.1fs to issue ^3%s\n\"",
                          (double)((float)(tmp_i4 - g_unk_00abe908) / 1000.0),
                          (&aCommandInfo)[param_2 * 5]);
    }
    else {
      *(int *)(*(int *)(param_1 + 400) + 0x988) = g_unk_00abe908 + 5000;
      tmp_u1 = *(uint *)(*(int *)(param_1 + 400) + 3000);
      if (tmp_u1 - 1 < 2) {
        if (*(int *)(teamInfo + tmp_u1 * 0x10) == 0) {
          trap_SendServerCommand
                    ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                     "cpm \"Your team isn\'t locked from spectators!\n\"");
          return;
        }
        trap_Argv(1,local_41c,0x400);
        tmp_i4 = ClientNumberFromString(param_1,local_41c);
        if (tmp_i4 == -1) {
          return;
        }
        tmp_i4 = tmp_i4 * 0x600;
        tmp_i2 = *(int *)(g_entities + tmp_i4 + 400);
        if (tmp_i2 == *(int *)(param_1 + 400)) {
          trap_SendServerCommand
                    ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                     "cpm \"You can\'t specinvite yourself!\n\"");
          return;
        }
        if (*(int *)(tmp_i2 + 3000) != 3) {
          trap_SendServerCommand
                    ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                     "cpm \"You can\'t specinvite a non-spectator!\n\"");
          return;
        }
        *(uint *)(tmp_i2 + 0xc88) = *(uint *)(tmp_i2 + 0xc88) | tmp_u1;
        tmp_u5 = va("print \"%s^7 has been sent a spectator invitation.\n\"",
                   *(int *)(g_entities + tmp_i4 + 400) + 0x5f8);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
        tmp_u5 = va("*** You\'ve been invited to spectate the %s team!",
                   *(uint32_t *)(aTeams + tmp_u1 * 4));
        G_printFull(tmp_u5,g_entities + tmp_i4);
        return;
      }
      tmp_pc3 = "cpm \"Spectators can\'t specinvite players!\n\"";
    }
  }
  else {
    tmp_pc3 = "cpm \"Team commands not enabled on this server.\n\"";
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc3);
  return;
}

void G_speclock_cmd(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  if (GHIDRA_FIELD(team_nocontrols, 12, 4) == 0) {
    tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 0x988);
    if (g_unk_00abe908 < tmp_i1) {
      tmp_pc2 = (char *)va("print \"Wait another %.1fs to issue ^3%s\n\"",
                          (double)((float)(tmp_i1 - g_unk_00abe908) / 1000.0),
                          (&aCommandInfo)[param_2 * 5]);
    }
    else {
      *(int *)(*(int *)(param_1 + 400) + 0x988) = g_unk_00abe908 + 5000;
      tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 3000);
      if (tmp_i1 - 1U < 2) {
        if (param_3 == *(int *)(teamInfo + tmp_i1 * 0x10)) {
          tmp_pc2 = (char *)va("print \"\n^3Your team is already %sed from spectators!\n\n\"",
                              (&lock_status)[param_3]);
        }
        else {
          tmp_u3 = va("The %s team is now %sed from spectators",*(uint32_t *)(aTeams + tmp_i1 * 4),
                     (&lock_status)[param_3]);
          G_printFull(tmp_u3,0);
          G_updateSpecLock(tmp_i1,param_3);
          if (param_3 == 0) {
            return;
          }
          tmp_pc2 = "cpm \"Use ^3specinvite^7 to invite people to spectate.\n\"";
        }
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc2);
        return;
      }
      tmp_pc2 = (char *)va("print \"Spectators can\'t %s a team from spectators!\n\"",
                          (&lock_status)[param_3]);
    }
  }
  else {
    tmp_pc2 = "cpm \"Team commands not enabled on this server.\n\"";
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc2);
  return;
}

void G_lock_cmd(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  
  if (GHIDRA_FIELD(team_nocontrols, 12, 4) == 0) {
    tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 0x988);
    if (g_unk_00abe908 < tmp_i1) {
      tmp_pc2 = (char *)va("print \"Wait another %.1fs to issue ^3%s\n\"",
                          (double)((float)(tmp_i1 - g_unk_00abe908) / 1000.0),
                          (&aCommandInfo)[param_2 * 5]);
    }
    else {
      *(int *)(*(int *)(param_1 + 400) + 0x988) = g_unk_00abe908 + 5000;
      tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 3000);
      if (tmp_i1 - 1U < 2) {
        if (param_3 != *(int *)(teamInfo + tmp_i1 * 0x10 + 4)) {
          tmp_u3 = va("\"The %s team is now %sed!\n\"",*(uint32_t *)(aTeams + tmp_i1 * 4),
                     (&lock_status)[param_3]);
          *(int *)(teamInfo + tmp_i1 * 0x10 + 4) = param_3;
          tmp_u4 = va("print %s",tmp_u3);
          trap_SendServerCommand(0xffffffff,tmp_u4);
          tmp_u3 = va("cp %s",tmp_u3);
          trap_SendServerCommand(0xffffffff,tmp_u3);
          return;
        }
        tmp_u3 = va("print \"^3Your team is already %sed!\n\"",(&lock_status)[param_3]);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
        return;
      }
      tmp_pc2 = (char *)va("print \"Spectators can\'t %s a team!\n\"",(&lock_status)[param_3]);
    }
  }
  else {
    tmp_pc2 = "cpm \"Team commands not enabled on this server.\n\"";
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc2);
  return;
}

void G_pause_cmd(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  uint8_t *local_24 [5];
  
  local_24[0] = &g_unk_0024805b;
  local_24[1] = &g_unk_00248060;
  if (GHIDRA_FIELD(team_nocontrols, 12, 4) == 0) {
    tmp_i2 = param_3;
    if (((1 < g_unk_02a99a78) || (tmp_i2 = g_unk_02a99a78, param_3 != 0)) && (tmp_i2 == 0)) {
      tmp_i2 = *(int *)(param_1 + 400);
      if (*(int *)(tmp_i2 + 0xc80) != 0) {
        G_refPause_cmd(param_1,param_3);
        return;
      }
      tmp_i1 = *(int *)(tmp_i2 + 3000);
      if (g_unk_00abe908 < *(int *)(tmp_i2 + 0x988)) {
        tmp_pc3 = (char *)va("print \"Wait another %.1fs to issue ^3%s\n\"",
                            (double)((float)(*(int *)(tmp_i2 + 0x988) - g_unk_00abe908) / 1000.0),
                            (&aCommandInfo)[param_2 * 5]);
      }
      else {
        *(int *)(tmp_i2 + 0x988) = g_unk_00abe908 + 5000;
        if (param_3 == 0) {
          if (tmp_i1 + 0x80 == g_unk_02a99a78) {
            trap_SendServerCommand
                      (0xffffffff,
                       "print \"\n^3Match is ^5UNPAUSED^3 ... resuming in 10 seconds!\n\n\"");
            g_unk_02a99a78 = 1;
            trap_SendServerCommand(0xffffffff,"an -1 0");
            G_spawnPrintf(1,g_unk_00abe908 + 10,0);
            return;
          }
          tmp_pc3 = "cpm \"^3Your team didn\'t call the timeout!\n\"";
        }
        else {
          tmp_i2 = tmp_i1 * 0x10;
          if (*(int *)(teamInfo + tmp_i2 + 0xc) != 0) {
            *(int *)(teamInfo + tmp_i2 + 0xc) = *(int *)(teamInfo + tmp_i2 + 0xc) + -1;
            g_unk_02a99a78 = tmp_i1 + 0x80;
            nitmod_Sound_Global(0xc);
            G_spawnPrintf(0,g_unk_00abe908 + 15000,0);
            tmp_u4 = va("print \"^3Match is ^1PAUSED^3!\n^7[%s^7: - %d Timeouts Remaining]\n\"",
                       *(uint32_t *)(aTeams + tmp_i1 * 4),*(uint32_t *)(teamInfo + tmp_i2 + 0xc));
            trap_SendServerCommand(0xffffffff,tmp_u4);
            tmp_u4 = va("cp \"^3Match is ^1PAUSED^3! (%s^3)\n\"",*(uint32_t *)(aTeams + tmp_i1 * 4))
            ;
            trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
            g_unk_02a99a80 = g_unk_02a99a80 | 0x10;
            tmp_u4 = va(&g_unk_00245ee9,g_unk_02a99a80);
            trap_SetConfigstring(0x1d,tmp_u4);
            return;
          }
          tmp_pc3 = "cpm \"^3Your team has no more timeouts remaining!\n\"";
        }
      }
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc3);
      return;
    }
    tmp_pc3 = (char *)va("print \"The match is already %sPAUSED^7!\n\"",local_24[param_3]);
  }
  else {
    tmp_pc3 = "cpm \"Team commands not enabled on this server.\n\"";
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc3);
  return;
}

void G_ready_cmd(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  uint8_t *local_24 [5];
  
  local_24[0] = &g_unk_0024806b;
  local_24[1] = &g_unk_0026ea14;
  if ((GHIDRA_FIELD(g_gamestate, 12, 4) == 3) || (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
    tmp_pc4 = "cpm \"Match is already in progress!\n\"";
  }
  else {
    if ((param_3 == 0) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 1)) {
      tmp_pc4 = "cpm \"Countdown started.... ^3notready^7 ignored!\n\"";
LAB_00074cee:
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc4);
      return;
    }
    tmp_i1 = *(int *)(param_1 + 400);
    if (*(int *)(tmp_i1 + 3000) == 3) {
      tmp_pc4 = "cpm \"You must be in the game to be ^3ready^7!\n\"";
    }
    else {
      if ((int)GHIDRA_FIELD(match_minplayers, 12, 4) <= g_unk_00abe940) {
        if (*(int *)(tmp_i1 + 0x988) <= g_unk_00abe908) {
          *(int *)(tmp_i1 + 0x988) = g_unk_00abe908 + 5000;
          if (*(int *)(*(int *)(param_1 + 400) + 0x998) == param_3) {
            tmp_u3 = va("print \"You are already%s ready!\n\"",local_24[param_3]);
            trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
          }
          else {
            *(int *)(*(int *)(param_1 + 400) + 0x998) = param_3;
            if (g_unk_00abf994 == 0) {
              if (param_3 == 0) {
                G_MakeUnready();
              }
              else {
                G_MakeReady(param_1);
              }
              tmp_pu2 = local_24[param_3];
              tmp_u3 = va("print \"%s^7 is%s ready!\n\"",*(int *)(param_1 + 400) + 0x5f8,tmp_pu2);
              trap_SendServerCommand(0xffffffff,tmp_u3);
              tmp_u3 = va("cp \"\n%s\n^3is%s ready!\n\"",*(int *)(param_1 + 400) + 0x5f8,tmp_pu2);
              trap_SendServerCommand(0xffffffff,tmp_u3);
            }
          }
          G_readyMatchState();
          return;
        }
        tmp_pc4 = (char *)va("print \"Wait another %.1fs to issue ^3%s\n\"",
                            (double)((float)(*(int *)(tmp_i1 + 0x988) - g_unk_00abe908) / 1000.0),
                            (&aCommandInfo)[param_2 * 5]);
        goto LAB_00074cee;
      }
      tmp_pc4 = "cpm \"Not enough players to start match!\n\"";
    }
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc4);
  return;
}

void G_teamready_cmd(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_i2 = g_unk_00abe940;
  tmp_i6 = *(int *)(param_1 + 400);
  tmp_i1 = *(int *)(tmp_i6 + 3000);
  if ((GHIDRA_FIELD(g_gamestate, 12, 4) == 3) || (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
    tmp_pc4 = "cpm \"Match is already in progress!\n\"";
  }
  else {
    tmp_pc4 = "cpm \"Spectators can\'t ready a team!\n\"";
    if (tmp_i1 != 3) {
      if (g_unk_00abe940 < (int)GHIDRA_FIELD(match_minplayers, 12, 4)) {
        tmp_pc4 = "cpm \"Not enough players to start match!\n\"";
      }
      else {
        if (*(int *)(tmp_i6 + 0x988) <= g_unk_00abe908) {
          *(int *)(tmp_i6 + 0x988) = g_unk_00abe908 + 5000;
          if (0 < tmp_i2) {
            tmp_i6 = 0;
            do {
              while (tmp_i5 = (&g_unk_00abe944)[tmp_i6] * 0x54dc + level,
                    tmp_i1 != *(int *)(tmp_i5 + 3000)) {
                tmp_i6 = tmp_i6 + 1;
                if (tmp_i2 <= tmp_i6) goto LAB_00074e62;
              }
              tmp_i6 = tmp_i6 + 1;
              *(uint32_t *)(tmp_i5 + 0x998) = 1;
              G_MakeReady(param_1);
              tmp_i2 = g_unk_00abe940;
            } while (tmp_i6 < g_unk_00abe940);
          }
LAB_00074e62:
          tmp_u3 = va("The %s team is ready!",*(uint32_t *)(aTeams + tmp_i1 * 4));
          G_printFull(tmp_u3,0);
          G_readyMatchState();
          return;
        }
        tmp_pc4 = (char *)va("print \"Wait another %.1fs to issue ^3%s\n\"",
                            (double)((float)(*(int *)(tmp_i6 + 0x988) - g_unk_00abe908) / 1000.0),
                            (&aCommandInfo)[param_2 * 5]);
      }
    }
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc4);
  return;
}

uint32_t G_commandHelp(int param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t local_40c [1024];
  
  if (param_1 != 0) {
    trap_Argv(1,local_40c,0x400);
    tmp_i1 = Q_stricmp(local_40c,&g_unk_0026f751);
    if (tmp_i1 == 0) {
      tmp_u2 = va(&g_unk_002480b8,param_2,
                 (&g_ptr_s_7_HUD_overlay_showing_current_w_002b37b0)[param_3 * 5]);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
      return 1;
    }
  }
  return 0;
}

uint32_t G_commandCheck(uint32_t param_1,uint32_t param_2,int param_3)
{
  void *tmp_pc1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  
  tmp_i4 = 0;
  tmp_pu3 = &g_unk_002b37ac;
  while (((tmp_pc1 = (void *)*tmp_pu3, tmp_pc1 == (void *)0x0 || (tmp_pu3[-2] != param_3)) ||
         (tmp_i2 = Q_stricmp(param_2,tmp_pu3[-3]), tmp_i2 != 0))) {
    tmp_pu3 = tmp_pu3 + 5;
    tmp_i4 = tmp_i4 + 1;
    if (tmp_pu3 == &g_unk_002b3aa4) {
      return 0;
    }
  }
  tmp_i2 = G_commandHelp(param_1,param_2,tmp_i4);
  if (tmp_i2 != 0) {
    return 1;
  }
  (*tmp_pc1)(param_1,tmp_i4,(&g_unk_002b37a8)[tmp_i4 * 5]);
  return 1;
}

uint32_t G_cmdDebounce(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 0x988);
  if (tmp_i1 <= g_unk_00abe908) {
    *(int *)(*(int *)(param_1 + 400) + 0x988) = g_unk_00abe908 + 5000;
    return 1;
  }
  tmp_u2 = va("print \"Wait another %.1fs to issue ^3%s\n\"",
             (double)((float)(tmp_i1 - g_unk_00abe908) / 1000.0),param_2);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  return 0;
}

void G_noTeamControls(int param_1)
{
  trap_SendServerCommand
            ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
             "cpm \"Team commands not enabled on this server.\n\"");
  return;
}

void G_UpdateKillingSpree(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  bool tmp_b7;
  int tmp_i8;
  bool tmp_b9;
  
  tmp_i1 = BG_GetKillSpree(*(uint32_t *)(param_1 + 400));
  if (param_3 == 0) {
    tmp_i8 = tmp_i1 + 1;
    if (tmp_i1 < 0) {
      tmp_i8 = 1;
    }
    tmp_i6 = *(int *)(param_1 + 400);
    if (*(int *)(tmp_i6 + 0xb98) < *(int *)(tmp_i6 + 0xb94)) {
      *(int *)(tmp_i6 + 0xb98) = *(int *)(tmp_i6 + 0xb94);
    }
    tmp_b7 = false;
LAB_0007606c:
    tmp_b9 = tmp_b7;
    if (((-10 < tmp_i1) || (param_3 != 0)) || ((g_announcer[0xc] & 0x40) == 0)) goto LAB_00075fc0;
    tmp_i2 = -tmp_i1;
    tmp_i6 = *(int *)(param_1 + 400);
    tmp_pc3 = "chat \"%s^g\'s death spree ended after ^1%d ^gdeaths!\" -2";
LAB_000760ae:
    tmp_u4 = va(tmp_pc3,tmp_i6 + 0x5f8,tmp_i2);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    if (4 < tmp_i8) goto LAB_00075fc9;
LAB_000760d0:
    if (((0x14 < tmp_i8 + 0x1eU) || ((-tmp_i8 / 10) * -10 != tmp_i8)) || ((g_announcer[0xc] & 2) == 0))
    goto LAB_00076000;
    tmp_u4 = 2;
    tmp_i6 = -(tmp_i8 / 10);
  }
  else {
    tmp_i8 = tmp_i1 + -1;
    if (0 < tmp_i1) {
      tmp_i8 = 0;
    }
    tmp_i6 = *(int *)(param_1 + 400);
    if (*(int *)(tmp_i6 + 0xb98) < *(int *)(tmp_i6 + 0xb94)) {
      *(int *)(tmp_i6 + 0xb98) = *(int *)(tmp_i6 + 0xb94);
    }
    if ((n_reviveSpreeOptions[0xc] & 8) != 0) {
      tmp_i6 = *(int *)(*(int *)(param_1 + 400) + 0xb94);
      if (4 < tmp_i6) {
        if ((param_1 == param_2) || (tmp_i2 = *(int *)(param_2 + 400), tmp_i2 == 0)) {
          tmp_u4 = va("chat \"%s ^gended his own revive spree after ^2%d ^grevives!\" -2",
                     *(int *)(param_1 + 400) + 0x5f8,tmp_i6);
          trap_SendServerCommand(0xffffffff,tmp_u4);
        }
        else {
          tmp_i5 = OnSameTeam(param_1,param_2);
          if (tmp_i5 == 0) {
            tmp_pc3 = "^7";
          }
          else {
            tmp_pc3 = "^1TEAMMATE ^7";
          }
          tmp_u4 = va("chat \"%s^g\'s revive spree ended by %s%s ^gafter ^2%d ^grevives!\" -2",
                     *(int *)(param_1 + 400) + 0x5f8,tmp_pc3,tmp_i2 + 0x5f8,tmp_i6);
          trap_SendServerCommand(0xffffffff,tmp_u4);
        }
      }
    }
    tmp_b9 = param_3 != 0;
    tmp_b7 = 4 < tmp_i1 && tmp_b9;
    if (4 < tmp_i1 && tmp_b9) {
      if ((g_announcer[0xc] & 0x20) == 0) goto LAB_0007606c;
      if ((param_1 != param_2) && (tmp_i6 = *(int *)(param_2 + 400), tmp_i6 != 0)) {
        tmp_i2 = OnSameTeam(param_1,param_2);
        if (tmp_i2 == 0) {
          tmp_pc3 = "^7";
        }
        else {
          tmp_pc3 = "^1TEAMMATE ^7";
        }
        tmp_u4 = va("chat \"%s^g\'s killing spree ended by %s%s ^gafter ^2%d ^gkills!\" -2",
                   *(int *)(param_1 + 400) + 0x5f8,tmp_pc3,tmp_i6 + 0x5f8,tmp_i1);
        trap_SendServerCommand(0xffffffff,tmp_u4);
        tmp_b9 = tmp_b7;
        goto LAB_00075fc0;
      }
      tmp_i6 = *(int *)(param_1 + 400);
      tmp_pc3 = "chat \"%s ^gended his own killing spree after ^2%d ^gkills!\" -2";
      tmp_i2 = tmp_i1;
      goto LAB_000760ae;
    }
LAB_00075fc0:
    tmp_b7 = tmp_b9;
    if (tmp_i8 < 5) goto LAB_000760d0;
LAB_00075fc9:
    if (((0x1e < tmp_i8) || (tmp_i6 = tmp_i8 / 5, tmp_i8 != tmp_i6 * 5)) || ((g_announcer[0xc] & 1) == 0)
       ) goto LAB_00076000;
    tmp_u4 = 1;
  }
  nitmod_Announce((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_i6 + -1,tmp_u4);
LAB_00076000:
  BG_SetKillSpree(*(uint32_t *)(param_1 + 400),tmp_i8);
  if (tmp_b7) {
    if ((0 < tmp_i1) && (tmp_i8 = BG_GetStatBestSpree(*(uint32_t *)(param_1 + 400)), tmp_i8 < tmp_i1))
    {
      BG_SetStatBestSpree(*(uint32_t *)(param_1 + 400),tmp_i1);
    }
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xb94) = 0;
  }
  return;
}

void G_UpdateKillingSpreeForMapEnd(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i1 = BG_GetKillSpree(*(uint32_t *)(param_1 + 400));
  tmp_i2 = BG_GetStatBestSpree(*(uint32_t *)(param_1 + 400));
  if (tmp_i2 < tmp_i1) {
    BG_SetStatBestSpree(*(uint32_t *)(param_1 + 400),tmp_i1);
  }
  BG_SetKillSpree(*(uint32_t *)(param_1 + 400),0);
  return;
}

int G_BuildHead(uint32_t *param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  byte tmp_b7;
  float tmp_f8;
  float tmp_f9;
  int tmp_i10;
  int tmp_i11;
  uint tmp_u12;
  float local_130;
  float local_120;
  uint32_t local_11c;
  uint32_t local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  uint8_t local_fc [48];
  float local_cc;
  float local_c8;
  float local_c4;
  
  if (param_2 == 0) {
    tmp_i10 = nitrox_TempHeadFromQueue(((int)(param_1 + -0x24f928) >> 9) * -0x55555555);
  }
  else {
    tmp_i10 = G_Spawn();
  }
  *(char **)(tmp_i10 + 0x1a4) = "head";
  *(uint32_t *)(tmp_i10 + 0x134) = 0xc0c00000;
  *(uint32_t *)(tmp_i10 + 0x138) = 0xc0c00000;
  *(uint32_t *)(tmp_i10 + 0x13c) = 0xc0000000;
  tmp_b7 = g_realHead[0xc] & 1;
  *(uint32_t *)(tmp_i10 + 0x140) = 0x40c00000;
  *(uint32_t *)(tmp_i10 + 0x144) = 0x40c00000;
  *(uint32_t *)(tmp_i10 + 0x148) = 0x41200000;
  if ((tmp_b7 != 0) && ((*(byte *)(param_1[100] + 0x6a) & 8) == 0)) {
    tmp_i11 = param_1[0x16a];
    if (param_1[0x16a] == 0) {
      tmp_i11 = g_unk_00abe908;
    }
    mdx_gentity_to_grefEntity(param_1,&local_cc,tmp_i11);
    mdx_head_position(param_1,&local_cc,local_fc);
    G_SetOrigin(tmp_i10,local_fc);
    *(uint32_t *)(tmp_i10 + 0x134) = 0xc0c00000;
    *(uint32_t *)(tmp_i10 + 0x138) = 0xc0c00000;
    *(uint32_t *)(tmp_i10 + 0x13c) = 0xc0c00000;
    *(uint32_t *)(tmp_i10 + 0x140) = 0x40c00000;
    tmp_f1 = *(float *)(tmp_i10 + 0x168);
    tmp_f2 = *(float *)(tmp_i10 + 0x16c);
    *(uint32_t *)(tmp_i10 + 0x144) = 0x40c00000;
    tmp_f3 = *(float *)(tmp_i10 + 0x170);
    *(uint32_t *)(tmp_i10 + 0x148) = 0x40c00000;
    goto LAB_00078a7c;
  }
  tmp_i11 = trap_GetTag(*param_1,0,"tag_head",local_fc);
  if (tmp_i11 != 0) {
    G_SetOrigin(tmp_i10,local_fc);
    tmp_f1 = *(float *)(tmp_i10 + 0x168);
    tmp_f2 = *(float *)(tmp_i10 + 0x16c);
    tmp_f3 = *(float *)(tmp_i10 + 0x170);
    goto LAB_00078a7c;
  }
  G_SetOrigin(tmp_i10,param_1 + 0x5a);
  tmp_i11 = param_1[100];
  tmp_u12 = *(uint *)(tmp_i11 + 0x68) & 0x80000;
  if (tmp_u12 == 0) {
    if ((*(uint *)(tmp_i11 + 0x68) & 0x800001) == 0) {
      if ((*(byte *)(tmp_i11 + 0xc) & 1) == 0) {
        local_130 = (float)*(int *)(tmp_i11 + 0xbc);
      }
      else {
        local_130 = *(float *)(tmp_i11 + 0x3f8) - 12.0;
      }
    }
    else {
      local_130 = (float)(*(int *)(tmp_i11 + 0xbc) + -0x40);
    }
  }
  else {
    local_130 = (float)(*(int *)(tmp_i11 + 0xbc) + -0x3c);
  }
  tmp_f1 = *(float *)(tmp_i11 + 0xb0);
  local_11c = *(uint32_t *)(tmp_i11 + 0xb4);
  local_118 = *(uint32_t *)(tmp_i11 + 0xb8);
  if (180.0 < tmp_f1) {
    tmp_f1 = tmp_f1 - 360.0;
  }
  local_120 = -10.0;
  if (tmp_u12 == 0) {
    local_120 = tmp_f1 * 0.75;
  }
  AngleVectors(&local_120,&local_114,&local_cc,&local_108);
  if ((*(uint *)(param_1[100] + 0x68) & 0x80000) == 0) {
    if ((*(uint *)(param_1[100] + 0x68) & 0x800001) != 0) {
      tmp_f1 = -26.0;
      tmp_f2 = 5.0;
      goto LAB_00078c01;
    }
    tmp_f3 = local_cc * 5.0 + local_114 * 5.0;
    tmp_f9 = local_c8 * 5.0 + local_110 * 5.0;
    tmp_f8 = local_c4 * 5.0 + local_10c * 5.0;
  }
  else {
    tmp_f1 = 28.0;
    tmp_f2 = 7.0;
LAB_00078c01:
    tmp_f3 = local_cc * tmp_f2 + local_114 * tmp_f1;
    tmp_f9 = local_c8 * tmp_f2 + local_110 * tmp_f1;
    tmp_f8 = tmp_f2 * local_c4 + tmp_f1 * local_10c;
  }
  tmp_f1 = local_108 * 18.0 + tmp_f3 + *(float *)(tmp_i10 + 0x168);
  *(float *)(tmp_i10 + 0x168) = tmp_f1;
  tmp_f2 = local_104 * 18.0 + tmp_f9 + *(float *)(tmp_i10 + 0x16c);
  *(float *)(tmp_i10 + 0x16c) = tmp_f2;
  tmp_f3 = local_130 * 0.5 + local_100 * 18.0 + tmp_f8 + *(float *)(tmp_i10 + 0x170);
  *(float *)(tmp_i10 + 0x170) = tmp_f3;
LAB_00078a7c:
  *(float *)(tmp_i10 + 0x5c) = tmp_f1;
  *(float *)(tmp_i10 + 0x60) = tmp_f2;
  *(float *)(tmp_i10 + 100) = tmp_f3;
  tmp_u4 = param_1[0x5d];
  *(uint32_t *)(tmp_i10 + 0x74) = tmp_u4;
  tmp_u5 = param_1[0x5e];
  *(uint32_t *)(tmp_i10 + 0x78) = tmp_u5;
  tmp_u6 = param_1[0x5f];
  *(uint32_t *)(tmp_i10 + 0x1d4) = 0x2000000;
  *(uint32_t *)(tmp_i10 + 0x7c) = tmp_u6;
  *(uint32_t *)(tmp_i10 + 0x3c) = tmp_u4;
  *(uint32_t *)(tmp_i10 + 0x40) = tmp_u5;
  *(uint32_t *)(tmp_i10 + 0x44) = tmp_u6;
  *(uint32_t *)(tmp_i10 + 0x48) = tmp_u4;
  *(uint32_t *)(tmp_i10 + 0x4c) = tmp_u5;
  *(uint32_t **)(tmp_i10 + 0x218) = param_1;
  *(uint32_t *)(tmp_i10 + 0x50) = tmp_u6;
  *(uint32_t *)(tmp_i10 + 0x14c) = 0x2000000;
  *(uint32_t *)(tmp_i10 + 4) = 0x28;
  trap_LinkEntity(tmp_i10);
  return tmp_i10;
}

int G_BuildLeg(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  uint8_t local_d8 [8];
  float local_d0;
  uint8_t local_cc [188];
  
  if ((*(uint *)(*(int *)(param_1 + 400) + 0x68) & 0x880001) == 0) {
    tmp_i2 = 0;
  }
  else {
    tmp_i2 = G_Spawn();
    *(uint8_t **)(tmp_i2 + 0x1a4) = &g_unk_002483f3;
    tmp_i3 = *(int *)(param_1 + 0x5a8);
    if (*(int *)(param_1 + 0x5a8) == 0) {
      tmp_i3 = g_unk_00abe908;
    }
    mdx_gentity_to_grefEntity(param_1,local_cc,tmp_i3);
    mdx_legs_position(param_1,local_cc,local_d8);
    local_d0 = (local_d0 + *(float *)(*(int *)(param_1 + 400) + 0x52d8)) -
               (g_unk_002b5634 + g_unk_002b5628) * 0.5;
    G_SetOrigin(tmp_i2,local_d8);
    *(uint32_t *)(tmp_i2 + 0x14c) = 0x2000000;
    *(int *)(tmp_i2 + 0x218) = param_1;
    *(uint32_t *)(tmp_i2 + 0x5c) = *(uint32_t *)(tmp_i2 + 0x168);
    *(uint32_t *)(tmp_i2 + 0x60) = *(uint32_t *)(tmp_i2 + 0x16c);
    *(uint32_t *)(tmp_i2 + 100) = *(uint32_t *)(tmp_i2 + 0x170);
    *(uint32_t *)(tmp_i2 + 0x134) = playerlegsProneMins;
    *(uint32_t *)(tmp_i2 + 0x138) = g_unk_002b5630;
    tmp_f1 = g_unk_002b5634;
    *(uint32_t *)(tmp_i2 + 0x1d4) = 0x2000000;
    *(float *)(tmp_i2 + 0x13c) = tmp_f1;
    *(uint32_t *)(tmp_i2 + 0x140) = playerlegsProneMaxs;
    *(uint32_t *)(tmp_i2 + 0x144) = g_unk_002b5624;
    tmp_f1 = g_unk_002b5628;
    *(uint32_t *)(tmp_i2 + 4) = 0x2a;
    *(float *)(tmp_i2 + 0x148) = tmp_f1;
    trap_LinkEntity(tmp_i2);
  }
  return tmp_i2;
}

void G_RailTrail(uint32_t param_1,uint32_t *param_2,float *param_3)
{
  uint32_t tmp_u1;
  float tmp_f2;
  int tmp_i3;
  
  tmp_i3 = nitrox_TempEventFromQueue(param_1,0x32);
  *(uint32_t *)(tmp_i3 + 0x68) = *param_2;
  *(uint32_t *)(tmp_i3 + 0x6c) = param_2[1];
  tmp_u1 = param_2[2];
  *(uint32_t *)(tmp_i3 + 0xf8) = 0;
  *(uint32_t *)(tmp_i3 + 0x70) = tmp_u1;
  *(float *)(tmp_i3 + 0x74) = (float)(int)ROUND(*param_3 * 255.0);
  *(float *)(tmp_i3 + 0x78) = (float)(int)ROUND(param_3[1] * 255.0);
  tmp_f2 = param_3[2];
  *(uint32_t *)(tmp_i3 + 0xf4) = 0xffffffff;
  *(float *)(tmp_i3 + 0x7c) = (float)(int)ROUND(tmp_f2 * 255.0);
  return;
}

void G_RailBox(float *param_1,float *param_2,float *param_3,float *param_4,int param_5)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  int tmp_i7;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_f1 = *param_1;
  tmp_f2 = param_1[1];
  tmp_f3 = param_1[2];
  local_18 = *param_2 + tmp_f1;
  local_14 = param_2[1] + tmp_f2;
  local_10 = param_2[2] + tmp_f3;
  tmp_f4 = *param_3;
  tmp_f5 = param_3[1];
  tmp_f6 = param_3[2];
  tmp_i7 = nitrox_TempEventFromQueue(&local_18,0x32);
  *(float *)(tmp_i7 + 0x68) = tmp_f1 + tmp_f4;
  *(float *)(tmp_i7 + 0x6c) = tmp_f2 + tmp_f5;
  *(float *)(tmp_i7 + 0x70) = tmp_f3 + tmp_f6;
  *(float *)(tmp_i7 + 0x74) = *param_4;
  *(float *)(tmp_i7 + 0x78) = param_4[1];
  tmp_f1 = param_4[2];
  *(uint32_t *)(tmp_i7 + 0xf8) = 1;
  *(float *)(tmp_i7 + 0x7c) = tmp_f1;
  *(float *)(tmp_i7 + 0x74) = (float)(int)ROUND(*param_4 * 255.0);
  *(float *)(tmp_i7 + 0x78) = (float)(int)ROUND(param_4[1] * 255.0);
  tmp_f1 = param_4[2];
  *(int *)(tmp_i7 + 0x10c) = param_5 + 1;
  *(float *)(tmp_i7 + 0x7c) = (float)(int)ROUND(tmp_f1 * 255.0);
  return;
}

void G_AdjustedDamageVec(int param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  
  if (*(int *)(param_1 + 0x130) == 0) {
    *param_3 = *(float *)(param_1 + 0x168) - *param_2;
    param_3[1] = *(float *)(param_1 + 0x16c) - param_2[1];
    param_3[2] = *(float *)(param_1 + 0x170) - param_2[2];
    return;
  }
  tmp_f1 = *param_2;
  if (*(float *)(param_1 + 0x150) <= tmp_f1) {
    if (tmp_f1 <= *(float *)(param_1 + 0x15c)) {
      *param_3 = 0.0;
      goto LAB_0007baaa;
    }
    *param_3 = tmp_f1 - *(float *)(param_1 + 0x15c);
    tmp_f1 = param_2[1];
    tmp_f2 = *(float *)(param_1 + 0x154);
    if (tmp_f2 <= tmp_f1) goto LAB_0007bac2;
LAB_0007bb27:
    param_3[1] = tmp_f2 - tmp_f1;
  }
  else {
    *param_3 = *(float *)(param_1 + 0x150) - tmp_f1;
LAB_0007baaa:
    tmp_f1 = param_2[1];
    tmp_f2 = *(float *)(param_1 + 0x154);
    if (tmp_f1 < tmp_f2) goto LAB_0007bb27;
LAB_0007bac2:
    if (*(float *)(param_1 + 0x160) < tmp_f1) {
      param_3[1] = tmp_f1 - *(float *)(param_1 + 0x160);
      tmp_f1 = param_2[2];
      tmp_f2 = *(float *)(param_1 + 0x158);
      if (tmp_f1 < tmp_f2) goto LAB_0007bb39;
      goto LAB_0007baf2;
    }
    param_3[1] = 0.0;
  }
  tmp_f1 = param_2[2];
  tmp_f2 = *(float *)(param_1 + 0x158);
  if (tmp_f1 < tmp_f2) {
LAB_0007bb39:
    param_3[2] = tmp_f2 - tmp_f1;
    return;
  }
LAB_0007baf2:
  if (tmp_f1 <= *(float *)(param_1 + 0x164)) {
    param_3[2] = 0.0;
    return;
  }
  param_3[2] = tmp_f1 - *(float *)(param_1 + 0x164);
  return;
}

uint32_t
G_RadiusDamage(float *param_1,uint32_t param_2,uint32_t param_3,float param_4,float param_5,
              uint8_t *param_6,int param_7)

{
  float tmp_f1;
  char tmp_c2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint8_t *tmp_pu6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  long double tmp_l9;
  float local_1090;
  float local_108c;
  float local_1088;
  float local_1084;
  float local_1080;
  float local_107c;
  float local_1078;
  float local_1074;
  float local_1070;
  float local_106c;
  float local_1068;
  float local_1064;
  float local_1060;
  float local_105c;
  float local_1058;
  uint8_t local_1054 [8];
  float local_104c;
  int local_101c [1027];
  
  tmp_c2 = (-(param_7 - 0x28U < 2) & 2U) + 1;
  if (param_5 < 1.0) {
    local_107c = 1.4142135;
    param_5 = 1.0;
  }
  else {
    local_107c = param_5 * 1.4142135;
  }
  local_1090 = *param_1 - local_107c;
  local_1084 = *param_1 + local_107c;
  local_108c = param_1[1] - local_107c;
  local_1080 = param_1[1] + local_107c;
  local_1088 = param_1[2] - local_107c;
  local_107c = local_107c + param_1[2];
  tmp_i3 = trap_EntitiesInBox(&local_1090,&local_1084,local_101c,0x400);
  tmp_i8 = g_unk_00abe8a8;
  if (0 < g_unk_00abe8a8) {
    tmp_pu7 = g_entities;
    tmp_i4 = 0;
    do {
      tmp_i4 = tmp_i4 + 1;
      *(uint32_t *)(tmp_pu7 + 0x494) = 0;
      tmp_pu7 = tmp_pu7 + 0x600;
    } while (tmp_i4 != tmp_i8);
  }
  if (0 < tmp_i3) {
    tmp_i8 = 0;
    do {
      while( true ) {
        tmp_i4 = local_101c[tmp_i8];
        tmp_i5 = tmp_i4 * 0x600;
        tmp_pu7 = g_entities + tmp_i5;
        if ((tmp_pu7 != param_6) &&
           ((*(int *)(g_entities + tmp_i5 + 0x2cc) != 0 ||
            ((*(int *)(g_entities + tmp_i5 + 0x490) != 0 &&
             (*(int *)(*(int *)(g_entities + tmp_i5 + 0x490) + 0x2cc) != 0)))))) break;
LAB_0007bda1:
        tmp_i8 = tmp_i8 + 1;
        if (tmp_i8 == tmp_i3) {
          return 1;
        }
      }
      if ((1 < param_7 - 0x43U) || (*(int *)(g_entities + tmp_i4 * 0x600) < 0x40)) {
        tmp_i5 = tmp_i4 * 0x600;
        if (*(int *)(g_entities + tmp_i5 + 0x130) == 0) {
          local_1078 = *(float *)(g_entities + tmp_i5 + 0x168) - *param_1;
          local_1074 = *(float *)(g_entities + tmp_i5 + 0x16c) - param_1[1];
          local_1070 = *(float *)(g_entities + tmp_i5 + 0x170) - param_1[2];
        }
        else {
          local_1078 = *param_1;
          if (local_1078 < *(float *)(g_entities + tmp_i5 + 0x150)) {
            local_1078 = *(float *)(g_entities + tmp_i5 + 0x150) - local_1078;
          }
          else if (*(float *)(g_entities + tmp_i5 + 0x15c) < local_1078) {
            local_1078 = local_1078 - *(float *)(g_entities + tmp_i5 + 0x15c);
          }
          else {
            local_1078 = 0.0;
          }
          local_1074 = param_1[1];
          if (local_1074 < *(float *)(g_entities + tmp_i4 * 0x600 + 0x154)) {
            local_1074 = *(float *)(g_entities + tmp_i4 * 0x600 + 0x154) - local_1074;
          }
          else if (*(float *)(g_entities + tmp_i4 * 0x600 + 0x160) < local_1074) {
            local_1074 = local_1074 - *(float *)(g_entities + tmp_i4 * 0x600 + 0x160);
          }
          else {
            local_1074 = 0.0;
          }
          local_1070 = param_1[2];
          if (local_1070 < *(float *)(g_entities + tmp_i4 * 0x600 + 0x158)) {
            local_1070 = *(float *)(g_entities + tmp_i4 * 0x600 + 0x158) - local_1070;
          }
          else if (*(float *)(g_entities + tmp_i4 * 0x600 + 0x164) < local_1070) {
            local_1070 = local_1070 - *(float *)(g_entities + tmp_i4 * 0x600 + 0x164);
          }
          else {
            local_1070 = 0.0;
          }
        }
        tmp_l9 = (long double)VectorLength(&local_1078);
        if (tmp_l9 < (long double)param_5) {
          tmp_f1 = (float)(((long double)1 - tmp_l9 / (long double)param_5) * (long double)param_4);
          tmp_i5 = CanDamage(tmp_pu7,param_1);
          if (tmp_i5 == 0) {
            tmp_i4 = tmp_i4 * 0x600;
            local_105c = (*(float *)(g_entities + tmp_i4 + 0x154) +
                         *(float *)(g_entities + tmp_i4 + 0x160)) * 0.5;
            local_1058 = (*(float *)(g_entities + tmp_i4 + 0x158) +
                         *(float *)(g_entities + tmp_i4 + 0x164)) * 0.5;
            local_1060 = (*(float *)(g_entities + tmp_i4 + 0x150) +
                         *(float *)(g_entities + tmp_i4 + 0x15c)) * 0.5;
            trap_Trace(local_1054,param_1,&vec3_origin,&vec3_origin,&local_1060,0x3ff,1);
            if (local_104c < 1.0) {
              local_1060 = local_1060 - *param_1;
              local_105c = local_105c - param_1[1];
              local_1058 = local_1058 - param_1[2];
              tmp_l9 = (long double)VectorLength(&local_1060);
              if (tmp_l9 < (long double)param_5 * (long double)0.2) {
                tmp_pu6 = *(uint8_t **)(g_entities + tmp_i4 + 0x490);
                if (*(uint8_t **)(g_entities + tmp_i4 + 0x490) == (uint8_t *)0x0) {
                  tmp_pu6 = tmp_pu7;
                }
                if (*(int *)(tmp_pu6 + 0x494) == 0) {
                  local_106c = *(float *)(tmp_pu6 + 0x168) - *param_1;
                  local_1068 = *(float *)(tmp_pu6 + 0x16c) - param_1[1];
                  local_1064 = (*(float *)(tmp_pu6 + 0x170) - param_1[2]) + 24.0;
                  G_Damage(tmp_pu6,param_2,param_3,&local_106c,param_1,(int)ROUND(tmp_f1 * 0.1),tmp_c2,
                           param_7);
                }
              }
            }
          }
          else {
            tmp_pu6 = *(uint8_t **)(g_entities + tmp_i4 * 0x600 + 0x490);
            if (*(uint8_t **)(g_entities + tmp_i4 * 0x600 + 0x490) == (uint8_t *)0x0) {
              tmp_pu6 = tmp_pu7;
            }
            if (*(int *)(tmp_pu6 + 0x494) == 0) {
              local_106c = *(float *)(tmp_pu6 + 0x168) - *param_1;
              local_1068 = *(float *)(tmp_pu6 + 0x16c) - param_1[1];
              local_1064 = (*(float *)(tmp_pu6 + 0x170) - param_1[2]) + 24.0;
              G_Damage(tmp_pu6,param_2,param_3,&local_106c,param_1,(int)ROUND(tmp_f1),tmp_c2,param_7);
            }
          }
        }
        goto LAB_0007bda1;
      }
      tmp_i8 = tmp_i8 + 1;
    } while (tmp_i8 != tmp_i3);
  }
  return 1;
}

uint32_t
etpro_RadiusDamage(float *param_1,uint32_t param_2,uint32_t param_3,float param_4,float param_5,
                  uint8_t *param_6,int param_7,int param_8)

{
  float tmp_f1;
  char tmp_c2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint8_t *tmp_pu6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  long double tmp_l9;
  float local_1090;
  float local_108c;
  float local_1088;
  float local_1084;
  float local_1080;
  float local_107c;
  float local_1078;
  float local_1074;
  float local_1070;
  float local_106c;
  float local_1068;
  float local_1064;
  float local_1060;
  float local_105c;
  float local_1058;
  uint8_t local_1054 [8];
  float local_104c;
  int local_101c [1027];
  
  tmp_c2 = (-(param_7 - 0x28U < 2) & 2U) + 1;
  if (param_5 < 1.0) {
    local_107c = 1.4142135;
    param_5 = 1.0;
  }
  else {
    local_107c = param_5 * 1.4142135;
  }
  local_1090 = *param_1 - local_107c;
  local_1084 = *param_1 + local_107c;
  local_108c = param_1[1] - local_107c;
  local_1080 = param_1[1] + local_107c;
  local_1088 = param_1[2] - local_107c;
  local_107c = param_1[2] + local_107c;
  tmp_i3 = trap_EntitiesInBox(&local_1090,&local_1084,local_101c,0x400);
  tmp_i8 = g_unk_00abe8a8;
  if (0 < g_unk_00abe8a8) {
    tmp_pu7 = g_entities;
    tmp_i4 = 0;
    do {
      tmp_i4 = tmp_i4 + 1;
      *(uint32_t *)(tmp_pu7 + 0x494) = 0;
      tmp_pu7 = tmp_pu7 + 0x600;
    } while (tmp_i4 != tmp_i8);
  }
  if (0 < tmp_i3) {
    tmp_i8 = 0;
    do {
      while( true ) {
        tmp_i4 = local_101c[tmp_i8];
        tmp_i5 = tmp_i4 * 0x600;
        tmp_pu7 = g_entities + tmp_i5;
        if ((tmp_pu7 != param_6) &&
           ((*(int *)(g_entities + tmp_i5 + 0x2cc) != 0 ||
            ((*(int *)(g_entities + tmp_i5 + 0x490) != 0 &&
             (*(int *)(*(int *)(g_entities + tmp_i5 + 0x490) + 0x2cc) != 0)))))) break;
LAB_0007c3b9:
        tmp_i8 = tmp_i8 + 1;
        if (tmp_i8 == tmp_i3) {
          return 1;
        }
      }
      tmp_i5 = tmp_i4 * 0x600;
      if (param_8 != 0) {
        if ((*(int *)(g_entities + tmp_i5 + 400) != 0) || (*(int *)(g_entities + tmp_i5 + 4) == 0x26))
        goto LAB_0007c2bf;
        goto LAB_0007c3b9;
      }
      if (*(int *)(g_entities + tmp_i5 + 400) == 0) {
LAB_0007c2bf:
        tmp_i5 = tmp_i4 * 0x600;
        if (*(int *)(g_entities + tmp_i5 + 0x130) == 0) {
          local_1078 = *(float *)(g_entities + tmp_i5 + 0x168) - *param_1;
          local_1074 = *(float *)(g_entities + tmp_i5 + 0x16c) - param_1[1];
          local_1070 = *(float *)(g_entities + tmp_i5 + 0x170) - param_1[2];
        }
        else {
          local_1078 = *param_1;
          if (local_1078 < *(float *)(g_entities + tmp_i5 + 0x150)) {
            local_1078 = *(float *)(g_entities + tmp_i5 + 0x150) - local_1078;
          }
          else if (*(float *)(g_entities + tmp_i5 + 0x15c) < local_1078) {
            local_1078 = local_1078 - *(float *)(g_entities + tmp_i5 + 0x15c);
          }
          else {
            local_1078 = 0.0;
          }
          local_1074 = param_1[1];
          if (local_1074 < *(float *)(g_entities + tmp_i4 * 0x600 + 0x154)) {
            local_1074 = *(float *)(g_entities + tmp_i4 * 0x600 + 0x154) - local_1074;
          }
          else if (*(float *)(g_entities + tmp_i4 * 0x600 + 0x160) < local_1074) {
            local_1074 = local_1074 - *(float *)(g_entities + tmp_i4 * 0x600 + 0x160);
          }
          else {
            local_1074 = 0.0;
          }
          local_1070 = param_1[2];
          if (local_1070 < *(float *)(g_entities + tmp_i4 * 0x600 + 0x158)) {
            local_1070 = *(float *)(g_entities + tmp_i4 * 0x600 + 0x158) - local_1070;
          }
          else if (*(float *)(g_entities + tmp_i4 * 0x600 + 0x164) < local_1070) {
            local_1070 = local_1070 - *(float *)(g_entities + tmp_i4 * 0x600 + 0x164);
          }
          else {
            local_1070 = 0.0;
          }
        }
        tmp_l9 = (long double)VectorLength(&local_1078);
        if (tmp_l9 < (long double)param_5) {
          tmp_f1 = (float)(((long double)1 - tmp_l9 / (long double)param_5) * (long double)param_4);
          tmp_i5 = CanDamage(tmp_pu7,param_1);
          if (tmp_i5 == 0) {
            tmp_i4 = tmp_i4 * 0x600;
            local_105c = (*(float *)(g_entities + tmp_i4 + 0x154) +
                         *(float *)(g_entities + tmp_i4 + 0x160)) * 0.5;
            local_1058 = (*(float *)(g_entities + tmp_i4 + 0x158) +
                         *(float *)(g_entities + tmp_i4 + 0x164)) * 0.5;
            local_1060 = (*(float *)(g_entities + tmp_i4 + 0x150) +
                         *(float *)(g_entities + tmp_i4 + 0x15c)) * 0.5;
            trap_Trace(local_1054,param_1,&vec3_origin,&vec3_origin,&local_1060,0x3ff,1);
            if (local_104c < 1.0) {
              local_1060 = local_1060 - *param_1;
              local_105c = local_105c - param_1[1];
              local_1058 = local_1058 - param_1[2];
              tmp_l9 = (long double)VectorLength(&local_1060);
              if (tmp_l9 < (long double)param_5 * (long double)0.2) {
                tmp_pu6 = *(uint8_t **)(g_entities + tmp_i4 + 0x490);
                if (*(uint8_t **)(g_entities + tmp_i4 + 0x490) == (uint8_t *)0x0) {
                  tmp_pu6 = tmp_pu7;
                }
                if (*(int *)(tmp_pu6 + 0x494) == 0) {
                  local_106c = *(float *)(tmp_pu6 + 0x168) - *param_1;
                  local_1068 = *(float *)(tmp_pu6 + 0x16c) - param_1[1];
                  local_1064 = (*(float *)(tmp_pu6 + 0x170) - param_1[2]) + 24.0;
                  G_Damage(tmp_pu6,param_2,param_3,&local_106c,param_1,(int)ROUND(tmp_f1 * 0.1),tmp_c2,
                           param_7);
                }
              }
            }
          }
          else {
            tmp_pu6 = *(uint8_t **)(g_entities + tmp_i4 * 0x600 + 0x490);
            if (*(uint8_t **)(g_entities + tmp_i4 * 0x600 + 0x490) == (uint8_t *)0x0) {
              tmp_pu6 = tmp_pu7;
            }
            if (*(int *)(tmp_pu6 + 0x494) == 0) {
              local_106c = *(float *)(tmp_pu6 + 0x168) - *param_1;
              local_1068 = *(float *)(tmp_pu6 + 0x16c) - param_1[1];
              local_1064 = (*(float *)(tmp_pu6 + 0x170) - param_1[2]) + 24.0;
              G_Damage(tmp_pu6,param_2,param_3,&local_106c,param_1,(int)ROUND(tmp_f1),tmp_c2,param_7);
            }
          }
        }
        goto LAB_0007c3b9;
      }
      tmp_i8 = tmp_i8 + 1;
    } while (tmp_i8 != tmp_i3);
  }
  return 1;
}

void G_configSet(uint param_1,int param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  uint8_t *tmp_pu3;
  
  if (param_1 < 9) {
    G_wipeCvars();
    if (param_2 == 0) {
      tmp_pu3 = (uint8_t *)&aPubSettings;
    }
    else {
      tmp_pu3 = aCompSettings;
    }
    tmp_pc1 = "g_altStopwatchMode";
    do {
      while ((*(uint *)tmp_pu3 & 1 << ((byte)param_1 & 0x1f)) != 0) {
        trap_Cvar_Set(tmp_pc1,*(uint *)((int)tmp_pu3 + 8));
        G_Printf("set %s %s\n",*(uint *)((int)tmp_pu3 + 4),*(uint *)((int)tmp_pu3 + 8));
        tmp_pc1 = *(char **)((int)tmp_pu3 + 0x10);
        tmp_pu3 = (uint8_t *)((int)tmp_pu3 + 0xc);
        if (tmp_pc1 == (char *)0x0) goto LAB_0007c86d;
      }
      tmp_pc1 = *(char **)((int)tmp_pu3 + 0x10);
      tmp_pu3 = (uint8_t *)((int)tmp_pu3 + 0xc);
    } while (tmp_pc1 != (char *)0x0);
LAB_0007c86d:
    G_UpdateCvars();
    if (param_2 == 0) {
      G_Printf(">> %s settings loaded!\n","Public");
    }
    else {
      G_Printf(">> %s settings loaded!\n","Competition");
      if (GHIDRA_FIELD(g_gamestate, 12, 4) == 1) {
        g_unk_02a983a8 = g_unk_00abe908;
      }
    }
    tmp_u2 = va("map_restart 0 %i\n",2);
    trap_SendConsoleCommand(2,tmp_u2);
  }
  return;
}

uint32_t * G_FindFreeFireteam(void)
{
  int tmp_i1;
  
  if (g_unk_02a996ec == 0) {
    tmp_i1 = 0;
  }
  else if (g_unk_02a9973c == 0) {
    tmp_i1 = 1;
  }
  else if (g_unk_02a9978c == 0) {
    tmp_i1 = 2;
  }
  else if (g_unk_02a997dc == 0) {
    tmp_i1 = 3;
  }
  else if (g_unk_02a9982c == 0) {
    tmp_i1 = 4;
  }
  else if (g_unk_02a9987c == 0) {
    tmp_i1 = 5;
  }
  else if (g_unk_02a998cc == 0) {
    tmp_i1 = 6;
  }
  else if (g_unk_02a9991c == 0) {
    tmp_i1 = 7;
  }
  else if (g_unk_02a9996c == 0) {
    tmp_i1 = 8;
  }
  else if (g_unk_02a999bc == 0) {
    tmp_i1 = 9;
  }
  else if (g_unk_02a99a0c == 0) {
    tmp_i1 = 10;
  }
  else {
    if (g_unk_02a99a5c != 0) {
      return (uint32_t *)0x0;
    }
    tmp_i1 = 0xb;
  }
  return &g_unk_02a996a4 + tmp_i1 * 0x14;
}

uint32_t G_GetFireteamTeam(int param_1)
{
  int tmp_i1;
  
  if (*(int *)(param_1 + 0x48) == 0) {
    return 0xffffffff;
  }
  if ((*(char *)(param_1 + 4) == -1) ||
     (tmp_i1 = *(int *)(g_entities + *(char *)(param_1 + 4) * 0x600 + 400), tmp_i1 == 0)) {
    G_Error("G_GetFireteamTeam: Fireteam leader is invalid\n");
    tmp_i1 = *(int *)(g_entities + *(char *)(param_1 + 4) * 0x600 + 400);
  }
  return *(uint32_t *)(tmp_i1 + 3000);
}

int G_CountTeamFireteams(int param_1)
{
  int tmp_i1;
  char *tmp_pc2;
  int tmp_i3;
  
  tmp_i3 = 0;
  tmp_pc2 = &g_unk_02a996a8;
  do {
    tmp_i1 = -1;
    if (*(int *)(tmp_pc2 + 0x44) != 0) {
      if ((*tmp_pc2 == -1) || (tmp_i1 = *(int *)(g_entities + *tmp_pc2 * 0x600 + 400), tmp_i1 == 0)) {
        G_Error("G_GetFireteamTeam: Fireteam leader is invalid\n");
        tmp_i1 = *(int *)(g_entities + *tmp_pc2 * 0x600 + 400);
      }
      tmp_i1 = *(int *)(tmp_i1 + 3000);
    }
    tmp_pc2 = tmp_pc2 + 0x50;
    tmp_i3 = tmp_i3 + (uint)(param_1 == tmp_i1);
  } while (tmp_pc2 != (char *)&g_unk_02a99a68);
  return tmp_i3;
}

void G_UpdateFireteamConfigString(int *param_1)
{
  char tmp_c1;
  int tmp_i2;
  int tmp_i3;
  uint32_t local_a4;
  uint32_t local_a0;
  uint8_t local_9c [136];
  uint32_t uStack_14;
  
  uStack_14 = 0x7cc0d;
  local_a0 = 0;
  local_a4 = 0;
  if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
    if (param_1[0x12] == 0) {
      Com_sprintf(local_9c,0x80,"\\n\\-1");
    }
    else {
      if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
        tmp_i3 = 0;
        tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
        do {
          tmp_c1 = *(char *)((int)param_1 + tmp_i3 + 4);
          if (tmp_c1 != -1) {
            COM_BitSet(&local_a4,(int)tmp_c1);
            tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
          }
          tmp_i3 = tmp_i3 + 1;
        } while (tmp_i3 < tmp_i2);
      }
      Com_sprintf(local_9c,0x80,"\\n\\%i\\l\\%i\\c\\%.8x%.8x",*param_1 + -1,(int)(char)param_1[1],
                  local_a0,local_a4);
    }
    nitrox_SetConfigstring(((int)(param_1 + -0xaa65a9) >> 4) * -0x33333333 + 0x283,local_9c);
  }
  return;
}

uint32_t G_IsOnFireteam(int param_1,uint32_t *param_2)
{
  char tmp_c1;
  char *tmp_pc2;
  char *tmp_pc3;
  int tmp_i4;
  
  if (((param_1 < 0) || ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= param_1)) ||
     (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
    G_Error("G_IsOnFireteam: invalid client");
  }
  tmp_pc2 = &g_unk_02a996a9;
  tmp_i4 = 0;
  do {
    if (((*(int *)(tmp_pc2 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && (tmp_pc2[-1] != -1)) {
      if (tmp_pc2[-1] == param_1) {
LAB_0007cdf0:
        if (param_2 != (uint32_t *)0x0) {
          *param_2 = &g_unk_02a996a4 + tmp_i4 * 0x14;
        }
        return 1;
      }
      tmp_pc3 = tmp_pc2;
      while ((tmp_pc3 != tmp_pc2 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 && (tmp_c1 = *tmp_pc3, tmp_c1 != -1))) {
        tmp_pc3 = tmp_pc3 + 1;
        if (tmp_c1 == param_1) goto LAB_0007cdf0;
      }
    }
    tmp_pc2 = tmp_pc2 + 0x50;
    tmp_i4 = tmp_i4 + 1;
    if (tmp_pc2 == (char *)((int)&g_unk_02a99a68 + 1)) {
      if (param_2 == (uint32_t *)0x0) {
        return 0;
      }
      *param_2 = 0;
      return 0;
    }
  } while( true );
}

uint32_t G_IsFireteamLeader(uint param_1,uint32_t *param_2)
{
  int tmp_i1;
  
  if ((0x3f < param_1) || (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
    G_Error("G_IsFireteamLeader: invalid client");
  }
  if ((g_unk_02a996ec == 0) || ((int)g_unk_02a996a8 != param_1)) {
    if ((g_unk_02a9973c == 0) || ((int)g_unk_02a996f8 != param_1)) {
      if ((g_unk_02a9978c == 0) || ((int)g_unk_02a99748 != param_1)) {
        if ((g_unk_02a997dc == 0) || ((int)g_unk_02a99798 != param_1)) {
          if ((g_unk_02a9982c == 0) || ((int)g_unk_02a997e8 != param_1)) {
            if ((g_unk_02a9987c == 0) || ((int)g_unk_02a99838 != param_1)) {
              if ((g_unk_02a998cc == 0) || ((int)g_unk_02a99888 != param_1)) {
                if ((g_unk_02a9991c == 0) || ((int)g_unk_02a998d8 != param_1)) {
                  if ((g_unk_02a9996c == 0) || ((int)g_unk_02a99928 != param_1)) {
                    if ((g_unk_02a999bc == 0) || ((int)g_unk_02a99978 != param_1)) {
                      if ((g_unk_02a99a0c == 0) || ((int)g_unk_02a999c8 != param_1)) {
                        if ((g_unk_02a99a5c == 0) || ((int)g_unk_02a99a18 != param_1)) {
                          if (param_2 != (uint32_t *)0x0) {
                            *param_2 = 0;
                            return 0;
                          }
                          return 0;
                        }
                        tmp_i1 = 0xb;
                      }
                      else {
                        tmp_i1 = 10;
                      }
                    }
                    else {
                      tmp_i1 = 9;
                    }
                  }
                  else {
                    tmp_i1 = 8;
                  }
                }
                else {
                  tmp_i1 = 7;
                }
              }
              else {
                tmp_i1 = 6;
              }
            }
            else {
              tmp_i1 = 5;
            }
          }
          else {
            tmp_i1 = 4;
          }
        }
        else {
          tmp_i1 = 3;
        }
      }
      else {
        tmp_i1 = 2;
      }
    }
    else {
      tmp_i1 = 1;
    }
  }
  else {
    tmp_i1 = 0;
  }
  if (param_2 == (uint32_t *)0x0) {
    return 1;
  }
  *param_2 = &g_unk_02a996a4 + tmp_i1 * 0x14;
  return 1;
}

uint32_t G_FindFreeFireteamIdent(int param_1)
{
  uint tmp_u1;
  uint32_t tmp_u2;
  int aiStack_20 [7];
  
  tmp_u1 = 0;
  aiStack_20[6] = 0x7d128;
  do {
    *(uint8_t **)((int)aiStack_20 + tmp_u1 + 4) = &g_unk_01010101;
    *(uint8_t **)((int)aiStack_20 + tmp_u1 + 8) = &g_unk_01010101;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x18);
  if ((g_unk_02a996ec != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a996a8 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a996a4] = 0;
  }
  if ((g_unk_02a9973c != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a996f8 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a996f4] = 0;
  }
  if ((g_unk_02a9978c != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a99748 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a99744] = 0;
  }
  if ((g_unk_02a997dc != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a99798 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a99794] = 0;
  }
  if ((g_unk_02a9982c != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a997e8 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a997e4] = 0;
  }
  if ((g_unk_02a9987c != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a99838 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a99834] = 0;
  }
  if ((g_unk_02a998cc != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a99888 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a99884] = 0;
  }
  if ((g_unk_02a9991c != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a998d8 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a998d4] = 0;
  }
  if ((g_unk_02a9996c != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a99928 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a99924] = 0;
  }
  if ((g_unk_02a999bc != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a99978 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a99974] = 0;
  }
  if ((g_unk_02a99a0c != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a999c8 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a999c4] = 0;
  }
  if ((g_unk_02a99a5c != 0) &&
     (*(int *)(*(int *)(g_entities + g_unk_02a99a18 * 0x600 + 400) + 3000) == param_1)) {
    aiStack_20[g_unk_02a99a14] = 0;
  }
  if (aiStack_20[1] == 0) {
    if (aiStack_20[2] == 0) {
      if (aiStack_20[3] == 0) {
        if (aiStack_20[4] == 0) {
          if (aiStack_20[5] == 0) {
            tmp_u2 = 0xffffffff;
            if (aiStack_20[6] != 0) {
              tmp_u2 = 5;
            }
          }
          else {
            tmp_u2 = 4;
          }
        }
        else {
          tmp_u2 = 3;
        }
      }
      else {
        tmp_u2 = 2;
      }
    }
    else {
      tmp_u2 = 1;
    }
  }
  else {
    tmp_u2 = 0;
  }
  return tmp_u2;
}

void G_RegisterFireteam(uint param_1)
{
  char tmp_c1;
  int *tmp_pi2;
  int tmp_i3;
  char *tmp_pc4;
  char *tmp_pc5;
  uint tmp_u6;
  int tmp_i7;
  int tmp_i8;
  int local_c0;
  uint32_t local_a4;
  int local_a0 [36];
  
  if (0x3f < param_1) {
    G_Error("G_RegisterFireteam: invalid client");
  }
  if (*(int *)(g_entities + param_1 * 0x600 + 400) == 0) {
    G_Error("G_RegisterFireteam: attempting to register a Fireteam to an entity with no client\n");
  }
  if ((((int)param_1 < 0) || ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= (int)param_1)) ||
     (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
    G_Error("G_IsOnFireteam: invalid client");
  }
  tmp_pc4 = &g_unk_02a996a9;
  do {
    if (((*(int *)(tmp_pc4 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && (tmp_pc4[-1] != -1)) {
      if (param_1 == (int)tmp_pc4[-1]) {
LAB_0007d728:
        trap_SendServerCommand(param_1,"cpm \"You are already on a fireteam, leave it first\"\n");
        return;
      }
      tmp_pc5 = tmp_pc4;
      while ((tmp_pc5 != tmp_pc4 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 && (tmp_c1 = *tmp_pc5, tmp_c1 != -1))) {
        tmp_pc5 = tmp_pc5 + 1;
        if (param_1 == (int)tmp_c1) goto LAB_0007d728;
      }
    }
    tmp_pc4 = tmp_pc4 + 0x50;
  } while (tmp_pc4 != (char *)((int)&g_unk_02a99a68 + 1));
  if (g_unk_02a996ec == 0) {
    local_c0 = 0;
  }
  else if (g_unk_02a9973c == 0) {
    local_c0 = 1;
  }
  else if (g_unk_02a9978c == 0) {
    local_c0 = 2;
  }
  else if (g_unk_02a997dc == 0) {
    local_c0 = 3;
  }
  else if (g_unk_02a9982c == 0) {
    local_c0 = 4;
  }
  else if (g_unk_02a9987c == 0) {
    local_c0 = 5;
  }
  else if (g_unk_02a998cc == 0) {
    local_c0 = 6;
  }
  else if (g_unk_02a9991c == 0) {
    local_c0 = 7;
  }
  else if (g_unk_02a9996c == 0) {
    local_c0 = 8;
  }
  else if (g_unk_02a999bc == 0) {
    local_c0 = 9;
  }
  else if (g_unk_02a99a0c == 0) {
    local_c0 = 10;
  }
  else {
    if (g_unk_02a99a5c != 0) {
      trap_SendServerCommand(param_1,"cpm \"No free fireteams available\"\n");
      return;
    }
    local_c0 = 0xb;
  }
  tmp_i8 = *(int *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 3000);
  if (1 < tmp_i8 - 1U) {
    trap_SendServerCommand(param_1,"cpm \"Only players on a team can create a fireteam\"\n");
    return;
  }
  tmp_pc4 = &g_unk_02a996a8;
  tmp_i7 = 0;
  do {
    while (*(int *)(tmp_pc4 + 0x44) != 0) {
      if ((*tmp_pc4 == -1) || (tmp_i3 = *(int *)(g_entities + *tmp_pc4 * 0x600 + 400), tmp_i3 == 0)) {
        G_Error("G_GetFireteamTeam: Fireteam leader is invalid\n");
        tmp_i3 = *(int *)(g_entities + *tmp_pc4 * 0x600 + 400);
      }
      tmp_pc4 = tmp_pc4 + 0x50;
      tmp_i7 = tmp_i7 + (uint)(tmp_i8 == *(int *)(tmp_i3 + 3000));
      if (tmp_pc4 == (char *)&g_unk_02a99a68) goto LAB_0007d859;
    }
    tmp_pc4 = tmp_pc4 + 0x50;
  } while (tmp_pc4 != (char *)&g_unk_02a99a68);
LAB_0007d859:
  if (6.0 <= (float)tmp_i7) {
    trap_SendServerCommand
              (param_1,"cpm \"Your team already has the maximum number of fireteams allowed\"\n");
    return;
  }
  tmp_u6 = 0;
  tmp_pi2 = local_a0 + 1;
  tmp_i8 = *(int *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 3000);
  do {
    *(uint8_t **)((int)tmp_pi2 + tmp_u6) = &g_unk_01010101;
    *(uint8_t **)((int)local_a0 + tmp_u6 + 8) = &g_unk_01010101;
    tmp_u6 = tmp_u6 + 8;
  } while (tmp_u6 < 0x18);
  if ((g_unk_02a996ec != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a996a8 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a996a4] = 0;
  }
  if ((g_unk_02a9973c != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a996f8 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a996f4] = 0;
  }
  if ((g_unk_02a9978c != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a99748 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a99744] = 0;
  }
  if ((g_unk_02a997dc != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a99798 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a99794] = 0;
  }
  if ((g_unk_02a9982c != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a997e8 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a997e4] = 0;
  }
  if ((g_unk_02a9987c != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a99838 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a99834] = 0;
  }
  if ((g_unk_02a998cc != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a99888 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a99884] = 0;
  }
  if ((g_unk_02a9991c != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a998d8 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a998d4] = 0;
  }
  if ((g_unk_02a9996c != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a99928 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a99924] = 0;
  }
  if ((g_unk_02a999bc != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a99978 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a99974] = 0;
  }
  if ((g_unk_02a99a0c != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a999c8 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a999c4] = 0;
  }
  if ((g_unk_02a99a5c != 0) &&
     (tmp_i8 == *(int *)(*(int *)(g_entities + g_unk_02a99a18 * 0x600 + 400) + 3000))) {
    local_a0[g_unk_02a99a14] = 0;
  }
  if (local_a0[1] == 0) {
    if (local_a0[2] == 0) {
      if (local_a0[3] == 0) {
        if (local_a0[4] == 0) {
          if (local_a0[5] == 0) {
            if (local_a0[6] == 0) {
              trap_SendServerCommand(param_1,"cpm \"Um, something is broken, spoink Gordon\"\n");
              return;
            }
            tmp_i8 = 5;
          }
          else {
            tmp_i8 = 4;
          }
        }
        else {
          tmp_i8 = 3;
        }
      }
      else {
        tmp_i8 = 2;
      }
    }
    else {
      tmp_i8 = 1;
    }
  }
  else {
    tmp_i8 = 0;
  }
  (&g_unk_02a996ec)[local_c0 * 0x14] = 1;
  tmp_u6 = 0;
  do {
    *(uint32_t *)(&g_unk_02a996a8 + tmp_u6 + local_c0 * 0x50) = 0xffffffff;
    *(uint32_t *)((int)&g_unk_02a996ac + tmp_u6 + local_c0 * 0x50) = 0xffffffff;
    tmp_u6 = tmp_u6 + 8;
  } while (tmp_u6 < 0x40);
  tmp_i7 = ((int)(param_1 * 0x600) >> 9) * -0x55555555;
  (&g_unk_02a996a8)[local_c0 * 0x50] = (char)tmp_i7;
  (&g_unk_02a996a4)[local_c0 * 0x14] = tmp_i8 + 1;
  if (GHIDRA_FIELD(g_autoFireteams, 12, 4) == 0) {
    (&g_unk_02a996f0)[local_c0 * 0x14] = 0;
  }
  else {
    (&g_unk_02a996f0)[local_c0 * 0x14] = 0;
    trap_SendServerCommand(param_1,"aft -1");
    *(int *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 0x6c8) = g_unk_00abe908 + 0x5014;
  }
  Bot_Event_FireTeamCreated(param_1,(&g_unk_02a996a4)[local_c0 * 0x14]);
  Bot_Event_JoinedFireTeam(tmp_i7,g_entities + param_1 * 0x600);
  local_a4 = 0;
  local_a0[0] = 0;
  if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
    if ((&g_unk_02a996ec)[local_c0 * 0x14] == 0) {
      Com_sprintf(tmp_pi2,0x80,"\\n\\-1");
    }
    else {
      if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
        tmp_i7 = 0;
        tmp_i8 = GHIDRA_FIELD(g_maxclients, 12, 4);
        do {
          if ((&g_unk_02a996a8)[tmp_i7 + local_c0 * 0x50] != -1) {
            COM_BitSet(&local_a4,(int)(&g_unk_02a996a8)[tmp_i7 + local_c0 * 0x50]);
            tmp_i8 = GHIDRA_FIELD(g_maxclients, 12, 4);
          }
          tmp_i7 = tmp_i7 + 1;
        } while (tmp_i7 < tmp_i8);
      }
      Com_sprintf(tmp_pi2,0x80,"\\n\\%i\\l\\%i\\c\\%.8x%.8x",(&g_unk_02a996a4)[local_c0 * 0x14] + -1,
                  (int)(&g_unk_02a996a8)[local_c0 * 0x50],local_a0[0],local_a4);
    }
    nitrox_SetConfigstring(local_c0 + 0x283,tmp_pi2);
  }
  return;
}

void G_AddClientToFireteam(uint param_1,uint param_2)
{
  char tmp_c1;
  int tmp_i2;
  char *tmp_pc3;
  char *tmp_pc4;
  int tmp_i5;
  int local_b0;
  uint32_t local_a4;
  uint32_t local_a0;
  uint8_t local_9c [140];
  
  if ((0x3f < param_1) || (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
    G_Error("G_AddClientToFireteam: invalid client");
  }
  if (param_2 < 0x40) {
    tmp_i2 = *(int *)(g_entities + param_2 * 0x600 + 400);
    if (tmp_i2 == 0) {
      G_Error("G_AddClientToFireteam: invalid client");
      tmp_i2 = *(int *)(g_entities + param_2 * 0x600 + 400);
    }
    if (*(int *)(tmp_i2 + 3000) == *(int *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 3000)) {
LAB_0007e0f3:
      if ((g_unk_02a996ec == 0) || (param_2 != (int)g_unk_02a996a8)) {
        if ((g_unk_02a9973c == 0) || (param_2 != (int)g_unk_02a996f8)) {
          if ((g_unk_02a9978c == 0) || (param_2 != (int)g_unk_02a99748)) {
            if ((g_unk_02a997dc == 0) || (param_2 != (int)g_unk_02a99798)) {
              if ((g_unk_02a9982c == 0) || (param_2 != (int)g_unk_02a997e8)) {
                if ((g_unk_02a9987c == 0) || (param_2 != (int)g_unk_02a99838)) {
                  if ((g_unk_02a998cc == 0) || (param_2 != (int)g_unk_02a99888)) {
                    if ((g_unk_02a9991c == 0) || (param_2 != (int)g_unk_02a998d8)) {
                      if ((g_unk_02a9996c == 0) || (param_2 != (int)g_unk_02a99928)) {
                        if ((g_unk_02a999bc == 0) || (param_2 != (int)g_unk_02a99978)) {
                          if ((g_unk_02a99a0c == 0) || (param_2 != (int)g_unk_02a999c8)) {
                            if ((g_unk_02a99a5c == 0) || (param_2 != (int)g_unk_02a99a18)) {
                              trap_SendServerCommand
                                        (param_1,
                                         "cpm \"The leader has now left the Fireteam you applied to\"\n"
                                        );
                              return;
                            }
                            local_b0 = 0xb;
                          }
                          else {
                            local_b0 = 10;
                          }
                        }
                        else {
                          local_b0 = 9;
                        }
                      }
                      else {
                        local_b0 = 8;
                      }
                    }
                    else {
                      local_b0 = 7;
                    }
                  }
                  else {
                    local_b0 = 6;
                  }
                }
                else {
                  local_b0 = 5;
                }
              }
              else {
                local_b0 = 4;
              }
            }
            else {
              local_b0 = 3;
            }
          }
          else {
            local_b0 = 2;
          }
        }
        else {
          local_b0 = 1;
        }
      }
      else {
        local_b0 = 0;
      }
      if ((((int)param_1 < 0) || ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= (int)param_1)) ||
         (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
        G_Error("G_IsOnFireteam: invalid client");
      }
      tmp_pc4 = &g_unk_02a996a9;
      do {
        if (((*(int *)(tmp_pc4 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && (tmp_pc4[-1] != -1)
           ) {
          if (param_1 == (int)tmp_pc4[-1]) {
LAB_0007e520:
            trap_SendServerCommand(param_1,"cpm \"You are already on a fireteam\"\n");
            return;
          }
          tmp_pc3 = tmp_pc4;
          while ((tmp_pc4 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 != tmp_pc3 && (tmp_c1 = *tmp_pc3, tmp_c1 != -1))) {
            tmp_pc3 = tmp_pc3 + 1;
            if (param_1 == (int)tmp_c1) goto LAB_0007e520;
          }
        }
        tmp_pc4 = tmp_pc4 + 0x50;
        if (tmp_pc4 == (char *)((int)&g_unk_02a99a68 + 1)) {
          if ((int)GHIDRA_FIELD(g_maxclients, 12, 4) < 1) {
            return;
          }
          tmp_i2 = local_b0 * 0x50;
          if ((&g_unk_02a996a8)[tmp_i2] == -1) {
            tmp_i2 = 0;
          }
          else {
            if (GHIDRA_FIELD(g_maxclients, 12, 4) == 1) {
              return;
            }
            if ((&g_unk_02a996a9)[tmp_i2] == -1) {
              tmp_i2 = 1;
            }
            else {
              if (GHIDRA_FIELD(g_maxclients, 12, 4) == 2) {
                return;
              }
              if ((&g_unk_02a996aa)[tmp_i2] == -1) {
                tmp_i2 = 2;
              }
              else {
                if (GHIDRA_FIELD(g_maxclients, 12, 4) == 3) {
                  return;
                }
                if ((&g_unk_02a996ab)[tmp_i2] == -1) {
                  tmp_i2 = 3;
                }
                else {
                  if (GHIDRA_FIELD(g_maxclients, 12, 4) == 4) {
                    return;
                  }
                  if (*(char *)(&g_unk_02a996ac + local_b0 * 0x28) == -1) {
                    tmp_i2 = 4;
                  }
                  else {
                    if (GHIDRA_FIELD(g_maxclients, 12, 4) == 5) {
                      return;
                    }
                    if (*(char *)((int)&g_unk_02a996ac + local_b0 * 0x50 + 1) != -1) {
                      if (GHIDRA_FIELD(g_maxclients, 12, 4) == 6) {
                        return;
                      }
                      trap_SendServerCommand
                                (param_1,"cpm \"Too many players already on this Fireteam\"\n");
                      return;
                    }
                    tmp_i2 = 5;
                  }
                }
              }
            }
          }
          (&g_unk_02a996a8)[tmp_i2 + local_b0 * 0x50] = (char)param_1;
          Bot_Event_JoinedFireTeam(param_1,g_entities + param_2 * 0x600);
          local_a4 = 0;
          local_a0 = 0;
          if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
            return;
          }
          if ((&g_unk_02a996ec)[local_b0 * 0x14] == 0) {
            Com_sprintf(local_9c,0x80,"\\n\\-1");
          }
          else {
            if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
              tmp_i5 = 0;
              tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
              do {
                if ((&g_unk_02a996a8)[tmp_i5 + local_b0 * 0x50] != -1) {
                  COM_BitSet(&local_a4,(int)(&g_unk_02a996a8)[tmp_i5 + local_b0 * 0x50]);
                  tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
                }
                tmp_i5 = tmp_i5 + 1;
              } while (tmp_i5 < tmp_i2);
            }
            Com_sprintf(local_9c,0x80,"\\n\\%i\\l\\%i\\c\\%.8x%.8x",
                        (&g_unk_02a996a4)[local_b0 * 0x14] + -1,(int)(&g_unk_02a996a8)[local_b0 * 0x50],
                        local_a0,local_a4);
          }
          nitrox_SetConfigstring(local_b0 + 0x283,local_9c);
          return;
        }
      } while( true );
    }
  }
  else {
    G_Error("G_AddClientToFireteam: invalid client");
    if (*(int *)(*(int *)(g_entities + param_2 * 0x600 + 400) + 3000) ==
        *(int *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 3000)) {
      G_Error("G_IsFireteamLeader: invalid client");
      goto LAB_0007e0f3;
    }
  }
  trap_SendServerCommand(param_1,"cpm \"You are not on the same team as that fireteam\"\n");
  return;
}

void G_RemoveClientFromFireteams(int param_1,int param_2,int param_3)
{
  char tmp_c1;
  int tmp_i2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  char *tmp_pc5;
  int tmp_i6;
  int local_bc;
  int local_b0;
  uint32_t local_a4;
  uint32_t local_a0;
  uint8_t local_9c [140];
  
  if (param_1 < 0) {
    G_Error("G_RemoveClientFromFireteams: invalid client");
  }
  else if (((param_1 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) &&
           (*(int *)(g_entities + param_1 * 0x600 + 400) != 0)) ||
          ((G_Error("G_RemoveClientFromFireteams: invalid client"),
           param_1 < (int)GHIDRA_FIELD(g_maxclients, 12, 4) && (*(int *)(g_entities + param_1 * 0x600 + 400) != 0)
           ))) goto LAB_0007e740;
  G_Error("G_IsOnFireteam: invalid client");
LAB_0007e740:
  tmp_u3 = GHIDRA_FIELD(g_maxclients, 12, 4);
  tmp_pc4 = &g_unk_02a996a9;
  local_bc = 0;
  do {
    if (((*(int *)(tmp_pc4 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && (tmp_pc4[-1] != -1)) {
      if (param_1 == tmp_pc4[-1]) {
        if ((&g_unk_02a996a9)[local_bc * 0x50] == -1) {
          (&g_unk_02a996ec)[local_bc * 0x14] = 0;
          (&g_unk_02a996a4)[local_bc * 0x14] = 0xffffffff;
        }
        tmp_i2 = 0;
        goto LAB_0007ea2a;
      }
      tmp_pc5 = tmp_pc4;
      while ((tmp_pc5 != tmp_pc4 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 && (tmp_c1 = *tmp_pc5, tmp_c1 != -1))) {
        tmp_pc5 = tmp_pc5 + 1;
        if (param_1 == tmp_c1) {
          tmp_i2 = 0;
          goto LAB_0007e800;
        }
      }
    }
    tmp_pc4 = tmp_pc4 + 0x50;
    local_bc = local_bc + 1;
    if (tmp_pc4 == (char *)((int)&g_unk_02a99a68 + 1)) {
      return;
    }
  } while( true );
  while ((char)(&g_unk_02a996a8)[tmp_i2 + local_bc * 0x50] != param_1) {
LAB_0007e800:
    tmp_i2 = tmp_i2 + 1;
    if ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= tmp_i2) goto LAB_0007e805;
  }
LAB_0007ea2a:
  local_b0 = tmp_u3 + -1;
  if (tmp_i2 < local_b0) {
    tmp_i6 = local_bc * 0x50 + tmp_i2;
    memmove(&g_unk_02a996a8 + tmp_i6,&g_unk_02a996a9 + tmp_i6,(tmp_u3 - tmp_i2) - 1);
  }
  (&g_unk_02a996a8)[local_b0 + local_bc * 0x50] = 0xff;
LAB_0007e805:
  Bot_Event_LeftFireTeam(param_1);
  if (((param_3 != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && ((&g_unk_02a996a8)[local_bc * 0x50] != -1)
     ) {
    tmp_i2 = 0;
    tmp_pc4 = &g_unk_02a996a8 + local_bc * 0x50;
    do {
      tmp_i2 = tmp_i2 + 1;
      tmp_u3 = va("cpm \"%s has left the Fireteam\"\n",param_1 * 0x54dc + level + 0x5f8);
      trap_SendServerCommand((int)*tmp_pc4,tmp_u3);
      if ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= tmp_i2) break;
      tmp_pc4 = tmp_pc4 + 1;
    } while (*tmp_pc4 != -1);
  }
  if (param_2 == 0) {
    return;
  }
  local_a4 = 0;
  local_a0 = 0;
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    return;
  }
  if ((&g_unk_02a996ec)[local_bc * 0x14] == 0) {
    Com_sprintf(local_9c,0x80,"\\n\\-1");
  }
  else {
    if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
      tmp_i6 = 0;
      tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
      do {
        if ((&g_unk_02a996a8)[tmp_i6 + local_bc * 0x50] != -1) {
          COM_BitSet(&local_a4,(int)(char)(&g_unk_02a996a8)[tmp_i6 + local_bc * 0x50]);
          tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
        }
        tmp_i6 = tmp_i6 + 1;
      } while (tmp_i6 < tmp_i2);
    }
    Com_sprintf(local_9c,0x80,"\\n\\%i\\l\\%i\\c\\%.8x%.8x",(&g_unk_02a996a4)[local_bc * 0x14] + -1,
                (int)(char)(&g_unk_02a996a8)[local_bc * 0x50],local_a0,local_a4);
  }
  nitrox_SetConfigstring((local_bc * 0x50 >> 4) * -0x33333333 + 0x283,local_9c);
  return;
}

void G_InviteToFireTeam(uint param_1,uint param_2)
{
  char tmp_c1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  char *tmp_pc4;
  
  if ((((int)param_1 < 0) || ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= (int)param_1)) ||
     (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
    G_Error("G_InviteToFireTeam: invalid client");
  }
  if ((0x3f < param_2) || (*(int *)(g_entities + param_2 * 0x600 + 400) == 0)) {
    G_Error("G_InviteToFireTeam: invalid client");
  }
  if ((0x3f < param_1) || (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
    G_Error("G_IsFireteamLeader: invalid client");
  }
  if (((((g_unk_02a996ec == 0) || (param_1 != (int)g_unk_02a996a8)) &&
       ((g_unk_02a9973c == 0 || (param_1 != (int)g_unk_02a996f8)))) &&
      ((g_unk_02a9978c == 0 || (param_1 != (int)g_unk_02a99748)))) &&
     (((((g_unk_02a997dc == 0 || (param_1 != (int)g_unk_02a99798)) &&
        ((((g_unk_02a9982c == 0 || (param_1 != (int)g_unk_02a997e8)) &&
          ((g_unk_02a9987c == 0 || (param_1 != (int)g_unk_02a99838)))) &&
         ((g_unk_02a998cc == 0 || (param_1 != (int)g_unk_02a99888)))))) &&
       ((g_unk_02a9991c == 0 || (param_1 != (int)g_unk_02a998d8)))) &&
      ((((g_unk_02a9996c == 0 || (param_1 != (int)g_unk_02a99928)) &&
        ((g_unk_02a999bc == 0 || (param_1 != (int)g_unk_02a99978)))) &&
       (((g_unk_02a99a0c == 0 || (param_1 != (int)g_unk_02a999c8)) &&
        ((g_unk_02a99a5c == 0 || (param_1 != (int)g_unk_02a99a18)))))))))) {
    trap_SendServerCommand(param_1,"cpm \"You are not the leader of a fireteam\"\n");
  }
  else {
    if (*(int *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 3000) !=
        *(int *)(*(int *)(g_entities + param_2 * 0x600 + 400) + 3000)) {
      trap_SendServerCommand(param_1,"cpm \"You are not on the same team as the other player\"\n");
      return;
    }
    if (((int)param_2 < 0) || ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= (int)param_2)) {
      G_Error("G_IsOnFireteam: invalid client");
    }
    tmp_pc4 = &g_unk_02a996a9;
    do {
      if (((*(int *)(tmp_pc4 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && (tmp_pc4[-1] != -1))
      {
        if (param_2 == (int)tmp_pc4[-1]) {
LAB_0007ef50:
          trap_SendServerCommand(param_1,"cpm \"The other player is already on a fireteam\"\n");
          return;
        }
        tmp_pc3 = tmp_pc4;
        while ((tmp_pc4 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 != tmp_pc3 && (tmp_c1 = *tmp_pc3, tmp_c1 != -1))) {
          tmp_pc3 = tmp_pc3 + 1;
          if (param_2 == (int)tmp_c1) goto LAB_0007ef50;
        }
      }
      tmp_pc4 = tmp_pc4 + 0x50;
    } while (tmp_pc4 != (char *)((int)&g_unk_02a99a68 + 1));
    trap_SendServerCommand(param_1,"invitation -1");
    tmp_u2 = va("invitation %i",param_1);
    trap_SendServerCommand(param_2,tmp_u2);
    *(uint *)(*(int *)(g_entities + param_2 * 0x600 + 400) + 0x6b4) = param_1;
    *(int *)(*(int *)(g_entities + param_2 * 0x600 + 400) + 0x6b8) = g_unk_00abe908 + 0x5014;
    Bot_Event_InviteFireTeam(param_1,param_2);
  }
  return;
}

void G_DestroyFireteam(uint param_1)
{
  uint32_t tmp_u1;
  char tmp_c2;
  uint tmp_u3;
  int tmp_i4;
  char *tmp_pc5;
  uint tmp_u6;
  char *tmp_pc7;
  int tmp_i8;
  int local_c4;
  int local_b8;
  int local_b4;
  uint32_t local_a4;
  uint32_t local_a0;
  uint8_t local_9c [140];
  
  if (param_1 < 0x40) {
    if ((*(int *)(g_entities + param_1 * 0x600 + 400) != 0) ||
       (G_Error("G_DestroyFireteam: invalid client"),
       *(int *)(g_entities + param_1 * 0x600 + 400) != 0)) goto LAB_0007efb8;
  }
  else {
    G_Error("G_DestroyFireteam: invalid client");
  }
  G_Error("G_IsFireteamLeader: invalid client");
LAB_0007efb8:
  if ((g_unk_02a996ec == 0) || (tmp_u6 = (uint)g_unk_02a996a8, param_1 != tmp_u6)) {
    if ((g_unk_02a9973c == 0) || (tmp_u6 = (uint)g_unk_02a996f8, param_1 != tmp_u6)) {
      if ((g_unk_02a9978c == 0) || (tmp_u6 = (uint)g_unk_02a99748, param_1 != tmp_u6)) {
        if ((g_unk_02a997dc == 0) || (tmp_u6 = (uint)g_unk_02a99798, param_1 != tmp_u6)) {
          if ((g_unk_02a9982c == 0) || (tmp_u6 = (uint)g_unk_02a997e8, param_1 != tmp_u6)) {
            if ((g_unk_02a9987c == 0) || (tmp_u6 = (uint)g_unk_02a99838, param_1 != tmp_u6)) {
              if ((g_unk_02a998cc == 0) || (tmp_u6 = (uint)g_unk_02a99888, param_1 != tmp_u6)) {
                if ((g_unk_02a9991c == 0) || (tmp_u6 = (uint)g_unk_02a998d8, param_1 != tmp_u6)) {
                  if ((g_unk_02a9996c == 0) || (tmp_u6 = (uint)g_unk_02a99928, param_1 != tmp_u6)) {
                    if ((g_unk_02a999bc == 0) || (tmp_u6 = (uint)g_unk_02a99978, param_1 != tmp_u6)) {
                      if ((g_unk_02a99a0c == 0) || (tmp_u6 = (uint)g_unk_02a999c8, param_1 != tmp_u6)) {
                        if ((g_unk_02a99a5c == 0) || (tmp_u6 = (uint)g_unk_02a99a18, param_1 != tmp_u6)) {
                          trap_SendServerCommand
                                    (param_1,"cpm \"You are not the leader of a fireteam\"\n");
                          return;
                        }
                        local_b4 = 0xb;
                      }
                      else {
                        local_b4 = 10;
                      }
                    }
                    else {
                      local_b4 = 9;
                    }
                  }
                  else {
                    local_b4 = 8;
                  }
                }
                else {
                  local_b4 = 7;
                }
              }
              else {
                local_b4 = 6;
              }
            }
            else {
              local_b4 = 5;
            }
          }
          else {
            local_b4 = 4;
          }
        }
        else {
          local_b4 = 3;
        }
      }
      else {
        local_b4 = 2;
      }
    }
    else {
      local_b4 = 1;
    }
  }
  else {
    local_b4 = 0;
  }
  tmp_c2 = (char)tmp_u6;
  tmp_i4 = GHIDRA_FIELD(g_maxclients, 12, 4);
joined_r0x0007f284:
  GHIDRA_FIELD(g_maxclients, 12, 4) = tmp_i4;
  if (tmp_c2 == -1) {
    local_a4 = 0;
    local_a0 = 0;
    if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
      if ((&g_unk_02a996ec)[local_b4 * 0x14] == 0) {
        Com_sprintf(local_9c,0x80,"\\n\\-1");
      }
      else {
        if (0 < tmp_i4) {
          tmp_i8 = 0;
          do {
            if ((&g_unk_02a996a8)[tmp_i8 + local_b4 * 0x50] != -1) {
              COM_BitSet(&local_a4,(int)(&g_unk_02a996a8)[tmp_i8 + local_b4 * 0x50]);
              tmp_i4 = GHIDRA_FIELD(g_maxclients, 12, 4);
            }
            tmp_i8 = tmp_i8 + 1;
          } while (tmp_i8 < tmp_i4);
          tmp_u6 = (uint)(&g_unk_02a996a8)[local_b4 * 0x50];
        }
        Com_sprintf(local_9c,0x80,"\\n\\%i\\l\\%i\\c\\%.8x%.8x",
                    (&g_unk_02a996a4)[local_b4 * 0x14] + -1,tmp_u6,local_a0,local_a4);
      }
      nitrox_SetConfigstring((local_b4 * 0x50 >> 4) * -0x33333333 + 0x283,local_9c);
      return;
    }
    return;
  }
  tmp_u6 = (uint)(char)tmp_u6;
  if (tmp_u6 != param_1) {
    Bot_Event_FireTeamDestroyed(tmp_u6);
    trap_SendServerCommand
              ((int)(&g_unk_02a996a8)[local_b4 * 0x50],
               "cpm \"The Fireteam you are on has been disbanded\"\n");
    tmp_u6 = (uint)(&g_unk_02a996a8)[local_b4 * 0x50];
  }
  if ((int)tmp_u6 < 0) {
    G_Error("G_RemoveClientFromFireteams: invalid client");
LAB_0007f597:
    G_Error("G_IsOnFireteam: invalid client");
  }
  else if ((((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= (int)tmp_u6) ||
           (*(int *)(g_entities + tmp_u6 * 0x600 + 400) == 0)) &&
          ((G_Error("G_RemoveClientFromFireteams: invalid client"),
           (int)GHIDRA_FIELD(g_maxclients, 12, 4) <= (int)tmp_u6 ||
           (*(int *)(g_entities + tmp_u6 * 0x600 + 400) == 0)))) goto LAB_0007f597;
  tmp_u1 = GHIDRA_FIELD(g_maxclients, 12, 4);
  local_c4 = 0;
  tmp_pc5 = &g_unk_02a996a9;
  do {
    if (((*(int *)(tmp_pc5 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) &&
       (tmp_u3 = (uint)tmp_pc5[-1], tmp_pc5[-1] != -1)) {
      if (tmp_u6 == tmp_u3) {
        if ((&g_unk_02a996a9)[local_c4 * 0x50] == -1) {
          (&g_unk_02a996ec)[local_c4 * 0x14] = 0;
          (&g_unk_02a996a4)[local_c4 * 0x14] = 0xffffffff;
        }
        tmp_i4 = 0;
        goto LAB_0007f5e6;
      }
      tmp_pc7 = tmp_pc5;
      while ((tmp_pc7 != tmp_pc5 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 && (tmp_u3 = (uint)*tmp_pc7, *tmp_pc7 != -1))
            ) {
        tmp_pc7 = tmp_pc7 + 1;
        if (tmp_u6 == tmp_u3) {
          tmp_i4 = 0;
          goto LAB_0007f56c;
        }
      }
    }
    tmp_pc5 = tmp_pc5 + 0x50;
    local_c4 = local_c4 + 1;
  } while (tmp_pc5 != (char *)((int)&g_unk_02a99a68 + 1));
  goto LAB_0007f38d;
  while (tmp_u3 != (int)(&g_unk_02a996a8)[tmp_i4 + local_c4 * 0x50]) {
LAB_0007f56c:
    tmp_i4 = tmp_i4 + 1;
    if ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= tmp_i4) {
      Bot_Event_LeftFireTeam(tmp_u3);
      goto LAB_0007f38d;
    }
  }
LAB_0007f5e6:
  local_b8 = tmp_u1 + -1;
  if (tmp_i4 < local_b8) {
    tmp_i8 = local_c4 * 0x50 + tmp_i4;
    memmove(&g_unk_02a996a8 + tmp_i8,&g_unk_02a996a9 + tmp_i8,(tmp_u1 - tmp_i4) - 1);
  }
  (&g_unk_02a996a8)[local_b8 + local_c4 * 0x50] = 0xff;
  Bot_Event_LeftFireTeam(tmp_u3);
LAB_0007f38d:
  tmp_c2 = (&g_unk_02a996a8)[local_b4 * 0x50];
  tmp_u6 = (uint)tmp_c2;
  tmp_i4 = GHIDRA_FIELD(g_maxclients, 12, 4);
  goto joined_r0x0007f284;
}

void G_ApplyToFireTeam(uint param_1,int param_2)
{
  char tmp_c1;
  byte tmp_b2;
  int tmp_i3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  char *tmp_pc6;
  
  if (param_1 < 0x40) {
    if (*(int *)(g_entities + param_1 * 0x600 + 400) == 0) {
      G_Error("G_AddClientToFireteam: invalid client");
LAB_000804f0:
      if (((int)param_1 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) &&
         (*(int *)(g_entities + param_1 * 0x600 + 400) != 0)) goto LAB_00080360;
    }
    else if ((int)param_1 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) goto LAB_00080360;
  }
  else {
    G_Error("G_AddClientToFireteam: invalid client");
    if (-1 < (int)param_1) goto LAB_000804f0;
  }
  G_Error("G_IsOnFireteam: invalid client");
LAB_00080360:
  tmp_pc5 = &g_unk_02a996a9;
  do {
    if (((*(int *)(tmp_pc5 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && (tmp_pc5[-1] != -1)) {
      if (param_1 == (int)tmp_pc5[-1]) {
LAB_000804c8:
        trap_SendServerCommand(param_1,"cpm \"You are already on a fireteam\"\n");
        return;
      }
      tmp_pc6 = tmp_pc5;
      while ((tmp_pc5 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 != tmp_pc6 && (tmp_c1 = *tmp_pc6, tmp_c1 != -1))) {
        tmp_pc6 = tmp_pc6 + 1;
        if (param_1 == (int)tmp_c1) goto LAB_000804c8;
      }
    }
    tmp_pc5 = tmp_pc5 + 0x50;
    if (tmp_pc5 == (char *)((int)&g_unk_02a99a68 + 1)) {
      if ((&g_unk_02a996ec)[param_2 * 0x14] == 0) {
        trap_SendServerCommand(param_1,"cpm \"The Fireteam you requested does not exist\"\n");
        return;
      }
      tmp_b2 = (&g_unk_02a996a8)[param_2 * 0x50];
      if (0x3f < tmp_b2) {
        G_Error("G_ApplyToFireTeam: Fireteam leader is invalid\n");
        tmp_b2 = (&g_unk_02a996a8)[param_2 * 0x50];
      }
      tmp_i3 = (char)tmp_b2 * 0x600;
      if (*(int *)(g_entities + tmp_i3 + 400) == 0) {
        G_Error("G_ApplyToFireTeam: Fireteam leader client is NULL\n");
      }
      trap_SendServerCommand(param_1,"application -1");
      tmp_u4 = va("application %i",param_1);
      trap_SendServerCommand((tmp_i3 >> 9) * -0x55555555,tmp_u4);
      *(uint *)(*(int *)(g_entities + (char)tmp_b2 * 0x600 + 400) + 0x6ac) = param_1;
      *(int *)(*(int *)(g_entities + (char)tmp_b2 * 0x600 + 400) + 0x6b0) = g_unk_00abe908 + 20000;
      return;
    }
  } while( true );
}

void G_ProposeFireTeamPlayer(uint param_1,uint param_2)
{
  int *tmp_pi1;
  char tmp_c2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  char *tmp_pc5;
  char *tmp_pc6;
  int tmp_i7;
  uint tmp_u8;
  
  if (param_1 == param_2) {
    return;
  }
  if ((param_1 < 0x40) && (*(int *)(g_entities + param_1 * 0x600 + 400) != 0)) {
    if (param_2 < 0x40) goto LAB_000805c1;
LAB_0008073f:
    G_Error("G_ProposeFireTeamPlayer: invalid client");
    if (-1 < (int)param_2) goto LAB_00080755;
  }
  else {
    G_Error("G_ProposeFireTeamPlayer: invalid client");
    if (0x3f < param_2) goto LAB_0008073f;
LAB_000805c1:
    if (*(int *)(g_entities + param_2 * 0x600 + 400) == 0) {
      G_Error("G_ProposeFireTeamPlayer: invalid client");
LAB_00080755:
      if (((int)param_2 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) &&
         (*(int *)(g_entities + param_2 * 0x600 + 400) != 0)) goto LAB_000805fb;
    }
    else if ((int)param_2 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) goto LAB_000805fb;
  }
  G_Error("G_IsOnFireteam: invalid client");
LAB_000805fb:
  tmp_pc4 = &g_unk_02a996a9;
  tmp_pc5 = tmp_pc4;
  do {
    if (((*(int *)(tmp_pc5 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && (tmp_pc5[-1] != -1)) {
      if (param_2 == (int)tmp_pc5[-1]) {
LAB_00080790:
        trap_SendServerCommand(param_1,"cpm \"The other player is already on a fireteam\"\n");
        return;
      }
      tmp_pc6 = tmp_pc5;
      while ((tmp_pc6 != tmp_pc5 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 && (tmp_c2 = *tmp_pc6, tmp_c2 != -1))) {
        tmp_pc6 = tmp_pc6 + 1;
        if (param_2 == (int)tmp_c2) goto LAB_00080790;
      }
    }
    tmp_pc5 = tmp_pc5 + 0x50;
    if (tmp_pc5 == (char *)((int)&g_unk_02a99a68 + 1)) {
      if ((((int)param_1 < 0) || ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= (int)param_1)) ||
         (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
        G_Error("G_IsOnFireteam: invalid client");
      }
      do {
        if (((*(int *)(tmp_pc4 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && (tmp_pc4[-1] != -1)
           ) {
          tmp_u8 = (uint)tmp_pc4[-1];
          if (param_1 == tmp_u8) {
            G_InviteToFireTeam();
            return;
          }
          tmp_pc5 = tmp_pc4;
          while ((tmp_pc5 != tmp_pc4 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 && (tmp_c2 = *tmp_pc5, tmp_c2 != -1))) {
            tmp_pc5 = tmp_pc5 + 1;
            if (param_1 == (int)tmp_c2) {
              if (*(int *)(g_entities + tmp_u8 * 0x600 + 400) == 0) {
                G_Error("G_ProposeFireTeamPlayer: invalid client");
              }
              trap_SendServerCommand(param_1,"proposition -1");
              tmp_u3 = va("proposition %i %i",param_2,param_1);
              tmp_i7 = ((int)(tmp_u8 * 0x600) >> 9) * -0x55555555;
              trap_SendServerCommand(tmp_i7,tmp_u3);
              tmp_pi1 = (int *)(g_entities + tmp_u8 * 0x600 + 400);
              *(uint *)(*tmp_pi1 + 0x6bc) = param_2;
              *(uint *)(*tmp_pi1 + 0x6c0) = param_1;
              *(int *)(*tmp_pi1 + 0x6c4) = g_unk_00abe908 + 20000;
              Bot_Event_FireTeam_Proposal(tmp_i7,param_2);
              return;
            }
          }
        }
        tmp_pc4 = tmp_pc4 + 0x50;
      } while (tmp_pc4 != (char *)((int)&g_unk_02a99a68 + 1));
      trap_SendServerCommand(param_1,"cpm \"You are not on a fireteam\"\n");
      return;
    }
  } while( true );
}

void G_FireteamNumberForString(char *param_1,int param_2)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  int local_28;
  
  tmp_i3 = 1;
  tmp_pi2 = &g_unk_02a996ec;
  local_28 = 0;
  do {
    if (((*tmp_pi2 != 0) &&
        (*(int *)(*(int *)(g_entities + (char)tmp_pi2[-0x11] * 0x600 + 400) + 3000) == param_2)) &&
       (tmp_i1 = Q_stricmp(*(uint32_t *)(bg_fireteamNames + (tmp_pi2[-0x12] + -1) * 4),param_1),
       tmp_i1 == 0)) {
      local_28 = tmp_i3;
    }
    tmp_pi2 = tmp_pi2 + 0x14;
    tmp_i3 = tmp_i3 + 1;
  } while (tmp_pi2 != (int *)&g_unk_02a99aac);
  if (local_28 == 0) {
    strtol(param_1,(char **)0x0,10);
    return;
  }
  return;
}

uint32_t * G_FindFreePublicFireteam(int param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  
  tmp_i2 = 0;
  tmp_pi1 = &g_unk_02a996ec;
  while ((((*tmp_pi1 == 0 ||
           (*(int *)(*(int *)(g_entities + (char)tmp_pi1[-0x11] * 0x600 + 400) + 3000) != param_1))
          || (tmp_pi1[1] != 0)) ||
         ((((((char)tmp_pi1[-0x11] == -1 || (int)GHIDRA_FIELD(g_maxclients, 12, 4) < 1) <
             (GHIDRA_FIELD(g_maxclients, 12, 4) != 1) && (*(char *)((int)tmp_pi1 + -0x43) != -1)) &&
           ((GHIDRA_FIELD(g_maxclients, 12, 4) != 2 &&
            ((*(char *)((int)tmp_pi1 + -0x42) != -1 && (GHIDRA_FIELD(g_maxclients, 12, 4) != 3)))))) &&
          ((*(char *)((int)tmp_pi1 + -0x41) != -1 &&
           ((((GHIDRA_FIELD(g_maxclients, 12, 4) != 4 && ((char)tmp_pi1[-0x10] != -1)) &&
             (GHIDRA_FIELD(g_maxclients, 12, 4) != 5)) && (*(char *)((int)tmp_pi1 + -0x3f) != -1))))))))) {
    tmp_i2 = tmp_i2 + 1;
    tmp_pi1 = tmp_pi1 + 0x14;
    if (tmp_i2 == 0xc) {
      return (uint32_t *)0x0;
    }
  }
  return &g_unk_02a996a4 + tmp_i2 * 0x14;
}

void G_SpawnItem(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t local_20 [4];
  
  G_SpawnFloatExt("random",&g_unk_0024bfa6,param_1 + 0x310,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_items.c",0x4fe);
  G_SpawnFloatExt(&g_unk_0023f11d,&g_unk_0024bfa6,param_1 + 0x30c,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_items.c",0x4ff);
  *(int *)(param_1 + 0x33c) = param_2;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 200;
  *(void **)(param_1 + 0x2a4) = FinishSpawningItem;
  tmp_i1 = G_SpawnStringExt("noise",0,local_20,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_items.c",0x507);
  if (tmp_i1 != 0) {
    tmp_u2 = G_SoundIndex(local_20[0]);
    *(uint32_t *)(param_1 + 0x308) = tmp_u2;
  }
  *(uint32_t *)(param_1 + 0x5c8) = 1;
  *(uint32_t *)(param_1 + 0x1d0) = 0x3f000000;
  *(uint32_t *)(param_1 + 0x5c4) = 1;
  if (*(int *)(param_1 + 0x1b4) != 0) {
    tmp_u2 = G_ModelIndex(*(int *)(param_1 + 0x1b4));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u2;
  }
  if (*(int *)(param_2 + 0x24) == 5) {
    G_SpawnIntExt("count",&g_unk_00258b23,param_1 + 0xf4,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_items.c",0x513);
    G_SpawnIntExt("speedscale",&g_unk_002496df,param_1 + 0x2d4,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_items.c",0x514);
    if (*(int *)(param_1 + 0x2d4) == 0) {
      *(uint32_t *)(param_1 + 0x2d4) = 100;
    }
  }
  return;
}

void G_FlushItem(uint32_t *param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  long double tmp_l7;
  uint8_t local_9c [12];
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  uint8_t local_78 [12];
  float local_6c;
  float local_68;
  float local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint8_t local_54 [4];
  int local_50;
  float local_4c;
  
  if ((((GHIDRA_FIELD(g_flushItems, 12, 4) == 0) || (param_1[0x172] == 0)) || (*(float *)(param_2 + 0x20) <= 0.7))
     || (((*(float *)(param_2 + 0x18) == 0.0 && (*(float *)(param_2 + 0x1c) == 0.0)) &&
         (*(float *)(param_2 + 0x20) == 1.0)))) {
    *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + 1.0;
    if (param_1[0x172] != 0) {
      param_1[0x5f] = 0;
      param_1[0x5d] = 0;
    }
  }
  else {
    AngleVectors(param_1 + 0x5d,local_9c,0,0);
    local_60 = *(uint32_t *)(param_2 + 0x18);
    local_5c = *(uint32_t *)(param_2 + 0x1c);
    local_58 = *(uint32_t *)(param_2 + 0x20);
    ProjectPointOnPlane(local_78,local_9c,&local_60);
    tmp_l7 = (long double)VectorNormalize(local_78);
    if (tmp_l7 == (long double)0) {
      AngleVectors(param_1 + 0x5d,0,0,local_9c);
      ProjectPointOnPlane(local_78,local_9c,&local_60);
      VectorNormalize(local_78);
    }
    CrossProduct(local_78,&local_60,&local_6c);
    local_6c = -local_6c;
    local_68 = -local_68;
    local_64 = -local_64;
    AxisToAngles(local_78,param_1 + 0x5d);
    local_84 = *(float *)(param_2 + 0x18) * -64.0 + *(float *)(param_2 + 0xc);
    local_80 = *(float *)(param_2 + 0x1c) * -64.0 + *(float *)(param_2 + 0x10);
    local_7c = *(float *)(param_2 + 0x20) * -64.0 + *(float *)(param_2 + 0x14);
    local_90 = *(float *)(param_2 + 0xc) + *(float *)(param_2 + 0x18);
    local_8c = *(float *)(param_2 + 0x10) + *(float *)(param_2 + 0x1c);
    local_88 = *(float *)(param_2 + 0x14) + *(float *)(param_2 + 0x20);
    trap_Trace(local_54,&local_90,0,0,&local_84,*param_1,1);
    if (local_50 == 0) {
      local_4c = local_4c * -64.0;
      tmp_f3 = *(float *)(param_2 + 0x18) * local_4c + *(float *)(param_2 + 0xc);
      tmp_f1 = *(float *)(param_2 + 0x1c);
      tmp_f4 = local_4c * tmp_f1 + *(float *)(param_2 + 0x10);
      tmp_f2 = *(float *)(param_2 + 0x20);
      tmp_f5 = local_4c * tmp_f2 + *(float *)(param_2 + 0x14);
    }
    else {
      tmp_f1 = *(float *)(param_2 + 0x1c);
      tmp_f2 = *(float *)(param_2 + 0x20);
      tmp_f3 = *(float *)(param_2 + 0xc);
      tmp_f4 = *(float *)(param_2 + 0x10);
      tmp_f5 = *(float *)(param_2 + 0x14);
    }
    *(float *)(param_2 + 0xc) = tmp_f3 + *(float *)(param_2 + 0x18);
    *(float *)(param_2 + 0x10) = tmp_f1 + tmp_f4;
    *(float *)(param_2 + 0x14) = tmp_f5 + tmp_f2;
  }
  G_SetAngle(param_1,param_1 + 0x5d);
  *(float *)(param_2 + 0xc) = (float)(int)ROUND(*(float *)(param_2 + 0xc));
  *(float *)(param_2 + 0x10) = (float)(int)ROUND(*(float *)(param_2 + 0x10));
  *(float *)(param_2 + 0x14) = (float)(int)ROUND(*(float *)(param_2 + 0x14));
  G_SetOrigin(param_1,param_2 + 0xc);
  tmp_i6 = *(int *)(param_2 + 0x34);
  param_1[0x25] = tmp_i6;
  if (tmp_i6 != 0x3fe) {
    param_1[3] = 9;
  }
  return;
}

uint32_t G_ItemStick(int param_1,int param_2,float *param_3)
{
  if ((*(int *)(param_1 + 0x2d0) != 0) && (*(int *)(param_1 + 0xe8) == 1)) {
    *(uint32_t *)(param_1 + 0x5c8) = 1;
    VectorNormalize(param_3);
    if ((*(float *)(param_2 + 0x20) * param_3[2] +
         *(float *)(param_2 + 0x1c) * param_3[1] + *(float *)(param_2 + 0x18) * *param_3 <= -0.75)
       && ((*(uint *)(param_2 + 0x2c) & 0x5c0000) != 0)) {
      vectoangles(param_3,param_1 + 0x174);
      *(uint32_t *)(param_1 + 0x5c8) = 0;
      return 1;
    }
  }
  return 0;
}

void G_BounceItem(int param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  uint32_t tmp_u6;
  long double tmp_l7;
  float local_28;
  float local_24;
  float local_20;
  
  BG_EvaluateTrajectoryDelta
            (param_1 + 0xc,
             (int)ROUND((float)(g_unk_00abe908 - g_unk_00abe910) * *(float *)(param_2 + 8) +
                        (float)g_unk_00abe910),&local_28,0,*(uint32_t *)(param_1 + 0x110));
  tmp_f2 = (local_20 * *(float *)(param_2 + 0x20) +
          local_24 * *(float *)(param_2 + 0x1c) + local_28 * *(float *)(param_2 + 0x18)) * -2.0;
  tmp_f3 = *(float *)(param_2 + 0x18) * tmp_f2 + local_28;
  *(float *)(param_1 + 0x24) = tmp_f3;
  tmp_f1 = *(float *)(param_2 + 0x1c) * tmp_f2 + local_24;
  *(float *)(param_1 + 0x28) = tmp_f1;
  tmp_f2 = tmp_f2 * *(float *)(param_2 + 0x20) + local_20;
  *(float *)(param_1 + 0x2c) = tmp_f2;
  if (*(float *)(param_2 + 0x20) < 0.7) {
    tmp_i4 = param_1 + 0x24;
    tmp_l7 = (long double)VectorLength(tmp_i4);
    if (((long double)16.0 <= tmp_l7) && (*(int *)(param_1 + 0x5c4) != 0)) {
      BG_ClipVelocity(tmp_i4,param_2 + 0x18,tmp_i4,0x3f8020c5);
      goto LAB_0008518b;
    }
    tmp_f3 = *(float *)(param_1 + 0x24);
    tmp_f1 = *(float *)(param_1 + 0x28);
    tmp_f2 = *(float *)(param_1 + 0x2c);
  }
  tmp_i4 = *(int *)(param_1 + 0x33c);
  *(float *)(param_1 + 0x24) = tmp_f3 * *(float *)(param_1 + 0x1d0);
  *(float *)(param_1 + 0x28) = tmp_f1 * *(float *)(param_1 + 0x1d0);
  *(float *)(param_1 + 0x2c) = tmp_f2 * *(float *)(param_1 + 0x1d0);
  if (tmp_i4 != 0) {
    tmp_i5 = *(int *)(tmp_i4 + 0x28);
    if (tmp_i5 == 1) {
      tmp_u6 = BG_FootstepForSurface(*(uint32_t *)(param_2 + 0x2c));
      G_AddEvent(param_1,0x27,tmp_u6);
    }
    else if ((*(int *)(tmp_i4 + 0x24) - 1U < 2) && (tmp_i5 - 1U < 0x33)) {
      *(int *)(param_1 + 0xe8) = tmp_i5;
    }
  }
  if ((*(int *)(param_1 + 0x2d0) != 0) && (*(int *)(param_1 + 0xe8) == 1)) {
    *(uint32_t *)(param_1 + 0x5c8) = 1;
    VectorNormalize(&local_28);
    if ((local_20 * *(float *)(param_2 + 0x20) +
         local_24 * *(float *)(param_2 + 0x1c) + local_28 * *(float *)(param_2 + 0x18) <= -0.75) &&
       ((*(uint *)(param_2 + 0x2c) & 0x5c0000) != 0)) {
      vectoangles(&local_28,param_1 + 0x174);
      *(uint32_t *)(param_1 + 0x5c8) = 0;
      goto LAB_00085162;
    }
  }
  tmp_l7 = (long double)VectorLength(param_1 + 0x24);
  if (((long double)40.0 <= tmp_l7) || (*(float *)(param_2 + 0x20) <= 0.0)) {
    if (*(int *)(param_1 + 0x30) != 0) {
      tmp_f3 = *(float *)(param_1 + 0x1d0);
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * tmp_f3;
      *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * tmp_f3;
      *(float *)(param_1 + 0x50) = tmp_f3 * *(float *)(param_1 + 0x50);
      *(int *)(param_1 + 0x34) = g_unk_00abe908;
    }
LAB_0008518b:
    *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x168);
    *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x16c);
    *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x170);
    *(int *)(param_1 + 0x10) = g_unk_00abe908;
    *(float *)(param_1 + 0x168) = *(float *)(param_1 + 0x168) + *(float *)(param_2 + 0x18);
    *(float *)(param_1 + 0x16c) = *(float *)(param_1 + 0x16c) + *(float *)(param_2 + 0x1c);
    *(float *)(param_1 + 0x170) = *(float *)(param_1 + 0x170) + *(float *)(param_2 + 0x20);
    return;
  }
LAB_00085162:
  G_FlushItem(param_1,param_2);
  return;
}

void G_RunItemProp(uint8_t *param_1,uint32_t *param_2)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint32_t local_60;
  uint32_t local_5c;
  float local_58;
  uint8_t local_54 [4];
  int local_50;
  byte local_28;
  int local_20;
  
  local_60 = *param_2;
  tmp_i2 = *(int *)(param_1 + 0x180);
  local_5c = param_2[1];
  local_58 = (float)param_2[2] + 1.0;
  trap_Trace(local_54,param_1 + 0x168,param_1 + 0x134,param_1 + 0x140,&local_60,tmp_i2,0x6000001);
  tmp_pu1 = g_entities + local_20 * 0x600;
  if ((param_1 != tmp_pu1) && (*(int *)(g_entities + local_20 * 0x600 + 0x2cc) != 0)) {
    *(uint8_t **)(param_1 + 0x2ec) = tmp_pu1;
  }
  tmp_i2 = tmp_i2 * 0x600;
  if ((((*(int *)(g_entities + tmp_i2 + 400) == 0) || (local_50 == 0)) ||
      (tmp_pu1 == g_entities + tmp_i2)) || (param_1 == tmp_pu1)) {
    if ((local_28 & 0x10) != 0) {
      *(uint32_t *)(param_1 + 0x2cc) = 0;
      Props_Chair_Skyboxtouch(param_1);
    }
  }
  else {
    *(uint32_t *)(param_1 + 0x2cc) = 0;
    (**(void **)(param_1 + 700))(param_1,param_1,0,10,0);
    Prop_Break_Sound(param_1);
  }
  return;
}

void G_TestWater(int param_1,uint32_t *param_2)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  uint8_t local_54 [4];
  int local_50;
  float local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  
  trap_Trace(local_54,param_1 + 0x168,param_1 + 0x134,param_1 + 0x140,param_2,
             *(uint32_t *)(param_1 + 0x180),0x38);
  if (((local_4c == 1.0) && (local_50 == 0)) &&
     (tmp_u2 = trap_PointContents(param_1 + 0x168,0xffffffff), tmp_u1 = g_unk_00abe908,
     (tmp_u2 & 0x38) == 0)) {
    if (*(int *)(param_1 + 0xc) != 6) {
      *(uint32_t *)(param_1 + 0xc) = 6;
      *(uint32_t *)(param_1 + 0x10) = tmp_u1;
      *(uint32_t *)(param_1 + 0x18) = *param_2;
      *(uint32_t *)(param_1 + 0x1c) = param_2[1];
      *(uint32_t *)(param_1 + 0x20) = param_2[2];
    }
  }
  else {
    tmp_u1 = g_unk_00abe908;
    if (*(int *)(param_1 + 0xc) != 8) {
      *(uint32_t *)(param_1 + 0x18) = local_48;
      *(uint32_t *)(param_1 + 0xc) = 8;
      *(uint32_t *)(param_1 + 0x1c) = local_44;
      *(uint32_t *)(param_1 + 0x10) = tmp_u1;
      *(uint32_t *)(param_1 + 0x20) = local_40;
      *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) * 0.125;
      *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) * 0.125;
      *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) * 0.125;
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * 0.125;
      *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * 0.125;
      *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) * 0.125;
    }
  }
  return;
}

uint32_t G_CheckForCabinetResupply(int param_1,int *param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  int local_24;
  
  if ((((param_2 != (int *)0x0) && (tmp_i1 = *(int *)(param_1 + 0x33c), tmp_i1 != 0)) &&
      (*(int *)(param_1 + 0x218) != 0)) && (*(int *)(*(int *)(param_1 + 0x218) + 400) != 0)) {
    if (*(int *)(tmp_i1 + 0x24) == 3) {
      if (param_2[1] != 0x2f) {
        return 0;
      }
      local_24 = 1;
    }
    else {
      if (*(int *)(tmp_i1 + 0x28) != 0xc) {
        return 0;
      }
      if (param_2[1] != 0x30) {
        return 0;
      }
      local_24 = 2;
    }
    if (0 < g_unk_00abe8a8) {
      tmp_pu3 = g_entities;
      tmp_i2 = 0;
      do {
        if ((*(int **)(tmp_pu3 + 0x264) != (int *)0x0) && (**(int **)(tmp_pu3 + 0x264) == *param_2)) {
          tmp_i2 = tmp_i2 * 0x600;
          tmp_i5 = *(int *)(g_entities + tmp_i2 + 0x2e4);
          if (tmp_i5 == -9999) {
            return 0;
          }
          tmp_i4 = *(int *)(g_entities + tmp_i2 + 0x2c8);
          if (tmp_i4 < tmp_i5) {
            if (local_24 == 1) {
              tmp_i4 = tmp_i4 + *(int *)(tmp_i1 + 0x20);
              if (tmp_i5 < tmp_i4) {
                tmp_i4 = tmp_i5;
              }
              *(int *)(g_entities + tmp_i2 + 0x2c8) = tmp_i4;
            }
            else {
              tmp_i4 = tmp_i4 + *(int *)(param_1 + 0x2e4);
              if (tmp_i4 <= tmp_i5) {
                tmp_i5 = tmp_i4;
              }
              *(int *)(g_entities + tmp_i2 + 0x2c8) = tmp_i5;
            }
            G_FreeEntity(param_1);
            return 1;
          }
          return 0;
        }
        tmp_i2 = tmp_i2 + 1;
        tmp_pu3 = tmp_pu3 + 0x600;
      } while (tmp_i2 != g_unk_00abe8a8);
    }
  }
  return 0;
}

void G_RunItem(uint32_t *param_1)
{
  uint32_t *tmp_pu1;
  uint32_t *tmp_pu2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  int tmp_i7;
  long double tmp_l8;
  uint32_t local_78;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_68;
  float local_64;
  uint32_t local_60;
  uint32_t local_5c;
  float local_58;
  uint8_t local_54 [4];
  int local_50;
  float local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  int local_20;
  
  tmp_i5 = param_1[0x75];
  tmp_i7 = 1;
  if (tmp_i5 != 0) {
    tmp_i7 = tmp_i5;
  }
  if (param_1[0x25] == -1) {
    if (param_1[3] != 6) {
      param_1[3] = 6;
      param_1[4] = g_unk_00abe908;
    }
  }
  else {
    tmp_i4 = param_1[3];
    if (tmp_i4 == 2) {
      if (tmp_i5 != 0) goto LAB_00085790;
      tmp_i4 = param_1[0x53];
    }
    else if (tmp_i4 == 9) {
      local_60 = param_1[0x5a];
      local_5c = param_1[0x5b];
      local_58 = (float)param_1[0x5c] - 8.0;
      trap_Trace(local_54,param_1 + 0x5a,param_1 + 0x4d,param_1 + 0x50,&local_60,*param_1,tmp_i7);
      if ((0.5 < local_4c) && (local_50 == 0)) {
        param_1[0xb] = 0;
        param_1[10] = 0;
        param_1[9] = 0;
        param_1[3] = 6;
        param_1[4] = g_unk_00abe908;
      }
      goto LAB_0008598e;
    }
    if (tmp_i4 == 0) {
LAB_0008598e:
      G_RunThink(param_1);
      return;
    }
  }
LAB_00085790:
  BG_EvaluateTrajectory(param_1 + 3,g_unk_00abe908,&local_78,0,param_1[0x44]);
  tmp_pu1 = param_1 + 0x5a;
  tmp_pu2 = param_1 + 0x50;
  tmp_pu3 = param_1 + 0x4d;
  trap_Trace(local_54,tmp_pu1,tmp_pu3,tmp_pu2,&local_78,param_1[0x60],0x38);
  if (((local_4c == 1.0) && (local_50 == 0)) &&
     (tmp_u6 = trap_PointContents(tmp_pu1,0xffffffff), tmp_i5 = g_unk_00abe908, (tmp_u6 & 0x38) == 0)) {
    if (param_1[3] != 6) {
      param_1[6] = local_78;
      param_1[3] = 6;
      param_1[7] = local_74;
      param_1[4] = tmp_i5;
      param_1[8] = local_70;
    }
  }
  else {
    tmp_i5 = g_unk_00abe908;
    if (param_1[3] != 8) {
      param_1[6] = local_48;
      param_1[3] = 8;
      param_1[7] = local_44;
      param_1[4] = tmp_i5;
      param_1[8] = local_40;
      param_1[9] = (float)param_1[9] * 0.125;
      param_1[10] = (float)param_1[10] * 0.125;
      param_1[0xb] = (float)param_1[0xb] * 0.125;
      param_1[0x12] = (float)param_1[0x12] * 0.125;
      param_1[0x13] = (float)param_1[0x13] * 0.125;
      param_1[0x14] = (float)param_1[0x14] * 0.125;
    }
  }
  if ((param_1[0xb4] == 0) || (param_1[0x86] == 0)) {
    trap_Trace(local_54,tmp_pu1,tmp_pu3,tmp_pu2,&local_78,param_1[0x60],tmp_i7);
  }
  else {
    *(uint32_t *)(param_1[0x86] + 0x120) = 0;
    trap_Trace(local_54,tmp_pu1,tmp_pu3,tmp_pu2,&local_78,*param_1,tmp_i7);
    *(uint32_t *)(param_1[0x86] + 0x120) = 1;
  }
  if ((param_1[0xe1] != 0) && (param_1[0xb3] != 0)) {
    G_RunItemProp(param_1,&local_78);
  }
  param_1[0x5a] = local_48;
  param_1[0x5b] = local_44;
  param_1[0x5c] = local_40;
  if (local_50 != 0) {
    local_4c = 0.0;
  }
  trap_LinkEntity(param_1);
  G_RunThink(param_1);
  if (local_4c == 1.0) {
    return;
  }
  tmp_i5 = G_CheckForCabinetResupply(param_1,g_entities + local_20 * 0x600);
  if (tmp_i5 != 0) {
    return;
  }
  tmp_i5 = trap_PointContents(tmp_pu1,0xffffffff);
  if (tmp_i5 < 0) {
    if ((param_1[0xcf] != 0) && (*(int *)(param_1[0xcf] + 0x24) == 5)) {
      Team_ReturnFlag(param_1,0);
      return;
    }
    G_FreeEntity(param_1);
    return;
  }
  if ((param_1[0xb4] == 0) || (local_20 == 0x3ff)) goto LAB_00085c10;
  BG_EvaluateTrajectoryDelta
            (param_1 + 3,
             (int)ROUND((float)(g_unk_00abe908 - g_unk_00abe910) * local_4c + (float)g_unk_00abe910),
             &local_6c,0,param_1[0x44]);
  local_60 = local_6c;
  local_5c = local_68;
  local_58 = local_64;
  VectorNormalize(&local_60);
  tmp_l8 = (long double)VectorLength(&local_6c);
  if ((tmp_l8 <= (long double)300.0) || (*(int *)(g_entities + local_20 * 0x600 + 0x2cc) == 0))
  goto LAB_00085c10;
  if (((g_friendlyFire[0xc] & 1) == 0) && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) {
    tmp_i5 = OnSameTeam(param_1[0x86],g_entities + local_20 * 0x600);
    tmp_l8 = (long double)(float)tmp_l8;
    if (tmp_i5 == 0) goto LAB_00085b71;
  }
  else {
LAB_00085b71:
    G_Damage(g_entities + local_20 * 0x600,param_1,param_1[0x86],&local_60,&local_48,
             (int)ROUND((tmp_l8 - (long double)300.0) / (long double)20.0 +
                        (long double)(int)param_1[0xb4]),0,param_1[0xb7]);
  }
  tmp_i5 = local_20 * 0x600;
  if ((*(int *)(g_entities + tmp_i5 + 400) != 0) && (*(int *)(g_entities + tmp_i5 + 0x2cc) != 0)) {
    tmp_i7 = nitrox_TempEventFromQueue(&local_48,0x30);
    *(uint32_t *)(tmp_i7 + 0x8c) = *(uint32_t *)(g_entities + tmp_i5);
    *(uint32_t *)(tmp_i7 + 0xe8) = param_1[0x3a];
    *(uint32_t *)(tmp_i7 + 0xac) = param_1[0x60];
  }
LAB_00085c10:
  G_BounceItem(param_1,local_54);
  return;
}

uint G_SortMapsByzOrder(int *param_1,int *param_2)
{
  int tmp_i1;
  uint tmp_u2;
  
  tmp_i1 = *param_2;
  if (*param_1 == -1) {
    tmp_u2 = (uint)(tmp_i1 != -1);
  }
  else {
    if (tmp_i1 != -1) {
      if ((g_mapVoteFlags[0xc] & 8) != 0) {
        return 0;
      }
      if ((int)(&g_unk_02aa0434)[*param_1 * 0x26] <= (int)(&g_unk_02aa0434)[tmp_i1 * 0x26]) {
        return (uint)((int)(&g_unk_02aa0434)[*param_1 * 0x26] < (int)(&g_unk_02aa0434)[tmp_i1 * 0x26]);
      }
    }
    tmp_u2 = 0xffffffff;
  }
  return tmp_u2;
}

uint32_t G_SnapshotCallback(int param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  
  if ((*(int *)(g_entities + param_1 * 0x600 + 4) == 3) &&
     ((*(int *)(g_entities + param_1 * 0x600 + 0xe8) == 0x33 ||
      (*(int *)(g_entities + param_1 * 0x600 + 0xe8) == 0x19)))) {
    tmp_u1 = G_LandmineSnapshotCallback(param_1,param_2);
    return tmp_u1;
  }
  return 1;
}

void G_Printf(char *param_1)
{
  char local_40c [1028];
  
  vsnprintf(local_40c,0x400,param_1,&stack0x00000008);
  G_LuaHook_Print(local_40c);
  trap_Printf(local_40c);
  return;
}

void G_DPrintf(char *param_1)
{
  char local_40c [1028];
  
  if (GHIDRA_FIELD(g_developer, 12, 4) != 0) {
    vsnprintf(local_40c,0x400,param_1,&stack0x00000008);
    trap_Printf(local_40c);
  }
  return;
}

void G_Error(char *param_1)
{
  char local_40c [1028];
  
  vsnprintf(local_40c,0x400,param_1,&stack0x00000008);
  trap_Error(local_40c);
  return;
}

void G_CheckForCursorHints(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  float tmp_f3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint32_t *tmp_pu8;
  uint32_t *tmp_pu9;
  int tmp_i10;
  char *tmp_pc11;
  char *tmp_pc12;
  char *tmp_pc13;
  bool tmp_b14;
  byte tmp_b15;
  long double tmp_l16;
  float local_8c;
  int local_88;
  int local_80;
  int local_7c;
  float *local_78;
  int local_74;
  float local_68;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  uint8_t local_40 [12];
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_b15 = 0;
  tmp_i2 = *(int *)(param_1 + 400);
  if (tmp_i2 == 0) {
    return;
  }
  tmp_u4 = *(uint *)(tmp_i2 + 0x68) & 0x40000;
  AngleVectors(tmp_i2 + 0xb0,&local_58,&local_4c,local_40);
  local_34 = *(float *)(tmp_i2 + 0x14);
  local_30 = *(float *)(tmp_i2 + 0x18);
  local_2c = 30.0;
  if ((*(float *)(tmp_i2 + 0xb0) <= 30.0) || ((*(byte *)(tmp_i2 + 0x68) & 0x10) == 0)) {
    local_2c = (float)*(int *)(tmp_i2 + 0xbc);
  }
  local_2c = local_2c + *(float *)(tmp_i2 + 0x1c);
  tmp_f1 = *(float *)(tmp_i2 + 0x3c);
  if (tmp_f1 != 0.0) {
    local_34 = local_4c * tmp_f1 + local_34;
    local_30 = local_48 * tmp_f1 + local_30;
    local_2c = tmp_f1 * local_44 + local_2c;
  }
  if (tmp_u4 == 0) {
    local_28 = local_58 * 1024.0 + local_34;
    local_24 = local_54 * 1024.0 + local_30;
    local_20 = local_50 * 1024.0 + local_2c;
    trap_Trace(tmp_i2 + 0x430,&local_34,0,0,&local_28,*(uint32_t *)(tmp_i2 + 0xa0),0x46000081);
    *(uint32_t *)(tmp_i2 + 0x428) = 0;
    *(uint32_t *)(tmp_i2 + 0x42c) = 0;
    tmp_l16 = (long double)VectorDistanceSquared(&local_34,tmp_i2 + 0x43c);
    local_68 = 1048576.0;
  }
  else {
    local_28 = local_58 * 8192.0 + local_34;
    local_24 = local_54 * 8192.0 + local_30;
    local_20 = local_50 * 8192.0 + local_2c;
    trap_Trace(tmp_i2 + 0x430,&local_34,0,0,&local_28,*(uint32_t *)(tmp_i2 + 0xa0),0x46000081);
    *(uint32_t *)(tmp_i2 + 0x428) = 0;
    *(uint32_t *)(tmp_i2 + 0x42c) = 0;
    tmp_l16 = (long double)VectorDistanceSquared(&local_34,tmp_i2 + 0x43c);
    local_68 = 67108864.0;
  }
  local_78 = &local_28;
  local_7c = tmp_i2 + 0x43c;
  local_80 = tmp_i2 + 0x430;
  tmp_i5 = *(int *)(tmp_i2 + 0xe4);
  tmp_i10 = *(int *)(*(int *)(param_1 + 400) + 0x103c);
  if ((tmp_i10 != 0) && (tmp_i5 == 2)) {
    tmp_i5 = G_IsConstructible(*(uint32_t *)(*(int *)(param_1 + 400) + 3000),tmp_i10);
    tmp_l16 = (long double)(float)tmp_l16;
    if (tmp_i5 != 0) {
      *(uint32_t *)(tmp_i2 + 0x428) = 0x21;
      *(int *)(tmp_i2 + 0x42c) = (int)ROUND(*(float *)(tmp_i5 + 0x80));
      return;
    }
    tmp_i5 = *(int *)(tmp_i2 + 0xe4);
  }
  if (tmp_i5 == 4) {
    tmp_i5 = *(int *)(param_1 + 400);
LAB_000868dd:
    if ((*(int *)(tmp_i5 + 0x1048) != 0) && (g_unk_00abe908 - *(int *)(tmp_i5 + 0x1048) < 500)) {
      *(uint32_t *)(tmp_i2 + 0x428) = 0x23;
      tmp_i5 = *(int *)(*(int *)(param_1 + 400) + 0x104c);
      if (tmp_i5 == 0) {
        tmp_u7 = 0;
      }
      else {
        tmp_u7 = *(uint32_t *)(tmp_i5 + 0x39c);
      }
      *(uint32_t *)(tmp_i2 + 0x42c) = tmp_u7;
      return;
    }
  }
  else if (((jp_keepAwards[0xc] & 8) != 0) &&
          (tmp_i5 = *(int *)(param_1 + 400), (*(byte *)(tmp_i5 + 0xed0) & 0x10) != 0))
  goto LAB_000868dd;
  if (*(float *)(tmp_i2 + 0x438) == 1.0) {
    return;
  }
  tmp_i5 = *(int *)(tmp_i2 + 0x464);
  tmp_pu9 = (uint32_t *)(g_entities + tmp_i5 * 0x600);
  local_74 = *(int *)(g_entities + tmp_i5 * 0x600 + 4);
  if ((local_74 == 0x2b) || (local_74 == 0xc)) {
    local_88 = 0;
    local_8c = (float)tmp_l16;
    do {
      local_88 = local_88 + 1;
      local_34 = local_58 * 0.1 + *(float *)(tmp_i2 + 0x43c);
      local_30 = local_54 * 0.1 + *(float *)(tmp_i2 + 0x440);
      local_2c = local_50 * 0.1 + *(float *)(tmp_i2 + 0x444);
      trap_Trace(local_80,&local_34,0,0,local_78,*tmp_pu9,0x46000081);
      tmp_l16 = (long double)VectorDistanceSquared(&local_34,local_7c);
      local_8c = (float)(tmp_l16 + (long double)local_8c);
      if (*(float *)(tmp_i2 + 0x438) == 1.0) {
        return;
      }
      tmp_i5 = *(int *)(tmp_i2 + 0x464);
      tmp_pu9 = (uint32_t *)(g_entities + tmp_i5 * 0x600);
      local_74 = *(int *)(g_entities + tmp_i5 * 0x600 + 4);
    } while ((local_74 == 0xc || local_74 == 0x2b) && (local_88 != 10));
    tmp_l16 = (long double)local_8c;
  }
  if (tmp_i5 == 0x3fe) {
    if ((*(byte *)(tmp_i2 + 0x460) & 0x20) == 0) {
      if (((*(byte *)(tmp_i2 + 0x45c) & 8) == 0) || ((*(byte *)(tmp_i2 + 0xc) & 4) != 0))
      goto LAB_0008678f;
      local_68 = 10000.0;
      tmp_i10 = 0;
      tmp_i5 = 0xf;
    }
    else {
      local_68 = 10000.0;
      tmp_i10 = 0;
      tmp_i5 = 0x11;
    }
    goto LAB_00086793;
  }
  if (tmp_i5 < 0x40) {
    tmp_i5 = tmp_pu9[100];
    if ((((tmp_i5 == 0) || (*(int *)(tmp_i5 + 3000) != *(int *)(*(int *)(param_1 + 400) + 3000))) ||
        (*(int *)(tmp_i5 + 4) != 3)) ||
       ((((*(byte *)(tmp_i5 + 0xd) & 0x40) != 0 || ((*(byte *)(tmp_i5 + 0x6a) & 0x80) != 0)) ||
        (*(int *)(*(int *)(param_1 + 400) + 0xbc8) != 1)))) {
LAB_0008678f:
      tmp_i10 = 0;
      tmp_i5 = 0;
    }
    else {
      local_68 = 4096.0;
      tmp_i10 = 0;
      tmp_i5 = 0x1f;
    }
    goto LAB_00086793;
  }
  if (tmp_pu9[0x116] - 1 < 2) {
    return;
  }
  tmp_pu8 = tmp_pu9;
  if (local_74 == 0) {
    tmp_i5 = 0xf;
    tmp_b14 = true;
    tmp_pc11 = (char *)tmp_pu9[0x69];
    tmp_pc12 = "trigger_aidoor";
    do {
      if (tmp_i5 == 0) break;
      tmp_i5 = tmp_i5 + -1;
      tmp_b14 = *tmp_pc11 == *tmp_pc12;
      tmp_pc11 = tmp_pc11 + (uint)tmp_b15 * -2 + 1;
      tmp_pc12 = tmp_pc12 + (uint)tmp_b15 * -2 + 1;
    } while (tmp_b14);
    if (tmp_b14) {
      return;
    }
    if (tmp_pu9[0x170] != 0x3f73d) goto _L97;
    tmp_i5 = tmp_pu9[0x3e];
    if (tmp_i5 == 0) {
      tmp_pu8 = (uint32_t *)G_FindByTargetnameFast(0,tmp_pu9[0x95],tmp_pu9[0x16f]);
      tmp_l16 = (long double)(float)tmp_l16;
      if (tmp_pu8 != (uint32_t *)0x0) {
        local_74 = tmp_pu8[1];
        goto LAB_00086aa6;
      }
      local_68 = 67108864.0;
      tmp_i5 = 0x27;
      tmp_i10 = 0;
    }
    else {
      local_68 = 9216.0;
      tmp_i10 = 0;
    }
    goto LAB_00086793;
  }
LAB_00086aa6:
  switch(local_74) {
  case 0:
  case 0x29:
_L97:
    if ((tmp_pu9[0x170] == 0x1908e) && (*(int *)(param_1 + 400) != 0)) {
      tmp_f1 = (float)tmp_l16;
      tmp_i5 = BG_IsScopedWeapon(*(uint32_t *)(*(int *)(param_1 + 400) + 0xa4));
      tmp_l16 = (long double)tmp_f1;
      if ((((tmp_i5 == 0) &&
           (((tmp_i5 = *(int *)(param_1 + 400), (*(byte *)(tmp_i5 + 0xc) & 1) == 0 &&
             (*(int *)(tmp_i5 + 0x140) == 0)) &&
            (tmp_f3 = (float)tmp_pu9[0x5c] - *(float *)(param_1 + 0x170), tmp_f3 < 40.0)))) &&
          (((0.0 <= tmp_f3 && (tmp_pu9[0x2c] == 0)) && (tmp_pu9[0xda] == 0)))) &&
         (*(int *)(tmp_i5 + 0x34) == 0)) {
        tmp_i5 = infront(tmp_pu9,param_1);
        tmp_l16 = (long double)tmp_f1;
        if (tmp_i5 == 0) {
          if (tmp_u4 != 0) {
            return;
          }
          local_68 = 9216.0;
          tmp_i10 = 0;
          tmp_i5 = 8;
          goto LAB_00086793;
        }
      }
    }
    if (*(int *)(tmp_i2 + 0xe4) == 2) {
      tmp_i5 = G_EmplacedGunIsRepairable(tmp_pu9,param_1);
      tmp_l16 = (long double)(float)tmp_l16;
      if (tmp_i5 != 0) {
        local_68 = 4096.0;
        tmp_i10 = 0xff;
        if ((int)tmp_pu9[0xb2] < 0x100) {
          tmp_i10 = tmp_pu9[0xb2];
        }
        tmp_i5 = 0x1d;
        break;
      }
    }
    goto LAB_000869a6;
  default:
    goto _L205;
  case 2:
    tmp_i5 = tmp_pu8[0xcf] + -0x2b59a0 >> 3;
    switch(*(uint32_t *)(bg_itemlist + tmp_i5 * 8 + 0x24)) {
    default:
      local_68 = 9216.0;
      tmp_i10 = 0;
      tmp_i5 = 0;
      break;
    case 1:
      tmp_i6 = G_CanPickupWeapon(*(uint32_t *)(bg_itemlist + tmp_i5 * 8 + 0x28),param_1);
      tmp_i10 = *(int *)(bg_itemlist + tmp_i5 * 8 + 0x28);
      tmp_l16 = (long double)(float)tmp_l16;
      if (tmp_i10 == 0xc) {
        local_68 = 9216.0;
        tmp_i10 = 0;
        tmp_i5 = 0x13;
      }
      else {
        if (tmp_i10 == 0x12) goto _L191;
        if (tmp_i6 == 0) goto LAB_00086db8;
        local_68 = 9216.0;
        tmp_i5 = 0x12;
        *(int *)(tmp_i2 + 0x42c) = tmp_i10;
      }
      break;
    case 2:
      if (tmp_u4 != 0) {
        return;
      }
      local_68 = 9216.0;
      tmp_i10 = 0;
      tmp_i5 = 0x13;
      goto LAB_00086793;
    case 3:
_L191:
      local_68 = 9216.0;
      tmp_i10 = 0;
      tmp_i5 = 0xd;
      break;
    case 4:
      local_68 = 9216.0;
      tmp_i10 = 0;
      tmp_i5 = 0x15;
      break;
    case 5:
      if (tmp_pu9[0x170] == 0x3317f) {
        if (*(int *)(*(int *)(param_1 + 400) + 3000) != 2) goto LAB_00086db8;
        local_68 = 9216.0;
        tmp_i10 = 0;
        tmp_i5 = 0x14;
      }
      else {
        if ((tmp_pu9[0x170] != 0x36af1) || (*(int *)(*(int *)(param_1 + 400) + 3000) != 1)) {
LAB_00086db8:
          local_68 = 9216.0;
          tmp_i5 = 0;
          goto LAB_00086dc4;
        }
        local_68 = 9216.0;
        tmp_i10 = 0;
        tmp_i5 = 0x14;
      }
      break;
    case 6:
      if (*(int *)(bg_itemlist + tmp_i5 * 8 + 0x2c) == 7) {
        tmp_i10 = *(int *)(param_1 + 400);
        if ((((*(int *)(bg_itemlist + tmp_i5 * 8 + 0x30) == *(int *)(tmp_i10 + 3000)) ||
             (*(int *)(tmp_i10 + 0xbc8) != 4)) || (*(int *)(tmp_i10 + 0x168) != 0)) ||
           ((*(int *)(tmp_i10 + 0x164) != 0 || (*(int *)(tmp_i10 + 0x16c) != 0)))) goto LAB_00086db8;
        local_68 = 9216.0;
        tmp_i10 = 0;
        tmp_i5 = 0x22;
      }
      else {
        local_68 = 9216.0;
        tmp_i10 = 0;
        tmp_i5 = 0x15;
      }
    }
    break;
  case 3:
  case 0x22:
    if (*(int *)(tmp_i2 + 0xe4) == 2) {
      if (tmp_pu8[0x3a] == 0x33) {
        tmp_i5 = G_LandmineTriggered(tmp_pu8);
        tmp_l16 = (long double)(float)tmp_l16;
        if (tmp_i5 != 0) goto LAB_00086ccd;
      }
      if (0xff < (int)tmp_pu8[0x17c]) {
        tmp_pu8[0x17c] = 0xff;
      }
      tmp_i10 = tmp_pu8[0x17c];
      tmp_i6 = tmp_pu8[0x3e];
      tmp_i5 = tmp_pu9[0x3e];
      if (tmp_i6 == 0) {
        tmp_i6 = tmp_i5;
        if (tmp_i5 == 0) {
          local_68 = 4096.0;
          tmp_i5 = 0x1e;
          break;
        }
      }
      else if (tmp_i5 != 0) {
        local_68 = 4096.0;
        goto LAB_00086f16;
      }
      local_68 = 4096.0;
      tmp_i5 = tmp_i6;
      goto LAB_00086f16;
    }
LAB_00086ccd:
    if (tmp_pu8[0x3e] == 0) {
      tmp_i10 = 0;
      tmp_i5 = 0;
      break;
    }
    tmp_i5 = 0;
    if (tmp_pu9[0x3e] == 0) goto LAB_00086dc4;
    goto _L205;
  case 4:
    tmp_i5 = tmp_pu8[0x170];
    if (tmp_i5 == 0x27cac) {
      tmp_i10 = G_TankIsMountable(tmp_pu8,param_1,1);
      tmp_l16 = (long double)(float)tmp_l16;
      tmp_i5 = 0;
      if (tmp_i10 != 0) {
        local_68 = 9216.0;
        goto LAB_00086bf1;
      }
LAB_00086dc4:
      if (tmp_u4 != 0) {
        return;
      }
      tmp_i10 = 0;
      goto LAB_00086793;
    }
    if (tmp_i5 == 0x3bf8a) {
      tmp_i5 = 0;
      if (tmp_pu8[0x79] != 7) goto LAB_00086dc4;
      if (tmp_pu8[0xd9] != -1) {
        tmp_i10 = 0;
        tmp_i5 = G_AllowTeamsAllowed(tmp_pu8,param_1);
        local_68 = 9216.0;
        tmp_l16 = (long double)(float)tmp_l16;
        if (tmp_i5 != 0) {
          tmp_i5 = 5;
          break;
        }
      }
      local_68 = 9216.0;
      tmp_i10 = 0;
      tmp_i5 = 7;
    }
    else if (tmp_i5 == 0x1cce6) {
      if (tmp_pu8[0x79] != 0) goto LAB_00086ea2;
      if (tmp_pu8[0xd9] != -1) {
        tmp_i5 = G_AllowTeamsAllowed(tmp_pu8,param_1);
        tmp_l16 = (long double)(float)tmp_l16;
        if (tmp_i5 != 0) {
          local_68 = 9216.0;
          tmp_i10 = 0;
          tmp_i5 = 4;
          break;
        }
      }
      local_68 = 9216.0;
      tmp_i10 = 0;
      tmp_i5 = 6;
    }
    else {
      tmp_pc11 = (char *)tmp_pu8[0x69];
      tmp_i5 = 0xc;
      tmp_b14 = false;
      tmp_pc12 = tmp_pc11;
      tmp_pc13 = "func_button";
      do {
        if (tmp_i5 == 0) break;
        tmp_i5 = tmp_i5 + -1;
        tmp_b14 = *tmp_pc12 == *tmp_pc13;
        tmp_pc12 = tmp_pc12 + (uint)tmp_b15 * -2 + 1;
        tmp_pc13 = tmp_pc13 + (uint)tmp_b15 * -2 + 1;
      } while (tmp_b14);
      if (tmp_b14) {
        local_68 = 9216.0;
        tmp_i10 = 0;
        tmp_i5 = 0x10;
      }
      else {
        tmp_i5 = 0x12;
        tmp_b14 = false;
        tmp_pc12 = tmp_pc11;
        tmp_pc13 = "props_flamebarrel";
        do {
          if (tmp_i5 == 0) break;
          tmp_i5 = tmp_i5 + -1;
          tmp_b14 = *tmp_pc12 == *tmp_pc13;
          tmp_pc12 = tmp_pc12 + (uint)tmp_b15 * -2 + 1;
          tmp_pc13 = tmp_pc13 + (uint)tmp_b15 * -2 + 1;
        } while (tmp_b14);
        if (tmp_b14) {
          local_68 = 16384.0;
          tmp_i10 = 0;
          tmp_i5 = 9;
        }
        else {
          tmp_i5 = strcmp(tmp_pc11,"props_statue");
          tmp_l16 = (long double)(float)tmp_l16;
          if (tmp_i5 != 0) goto LAB_00086ea2;
          local_68 = 16384.0;
          tmp_i10 = 0;
          tmp_i5 = 9;
        }
      }
    }
    break;
  case 0xe:
    if ((*(byte *)(tmp_pu8 + 0x6a) & 0x20) != 0) {
      local_68 = 16384.0;
      tmp_i10 = 0;
      *(uint32_t *)(tmp_i2 + 0x42c) = 0;
      tmp_i5 = 0x24;
      break;
    }
    tmp_i10 = tmp_pu8[0x13d];
    if (tmp_i10 == 1) {
LAB_000871f3:
      local_68 = 16384.0;
      tmp_i10 = 0;
      tmp_i5 = 0x25;
      *(uint32_t *)(tmp_i2 + 0x42c) = 0;
      break;
    }
    if (tmp_i10 != 2) {
      tmp_i5 = tmp_pu8[0xb2];
      if ((tmp_i10 != 0) && (tmp_i5 < 1)) goto LAB_000869a6;
LAB_00086bb2:
      if (hintValMax_13536 < tmp_i5) {
        hintValMax_13536 = tmp_i5;
      }
      local_68 = 4096.0;
      tmp_i10 = (tmp_i5 * 0xff) / hintValMax_13536;
      tmp_i5 = 9;
      break;
    }
    *(uint32_t *)(tmp_i2 + 0x428) = 1;
    *(uint32_t *)(tmp_i2 + 0x42c) = 0;
    tmp_i5 = tmp_pu8[0x86];
    if (tmp_i5 == 0) {
LAB_000872a9:
      tmp_i10 = 0;
      tmp_i5 = 1;
      local_68 = 0.0;
      break;
    }
    if (*(int *)(tmp_i5 + 4) == 0xc) {
      tmp_i10 = *(int *)(*(int *)(param_1 + 400) + 3000);
      if (tmp_i10 == 1) {
        if ((*(byte *)(tmp_i5 + 0x1a8) & 2) == 0) {
          tmp_i5 = 1;
          local_68 = 0.0;
          goto LAB_00086dc4;
        }
        local_68 = 16384.0;
        tmp_i10 = 0;
        tmp_i5 = 10;
      }
      else {
        if (tmp_i10 != 2) goto LAB_000872a9;
        if ((*(byte *)(tmp_i5 + 0x1a8) & 1) == 0) goto LAB_000869b9;
        local_68 = 16384.0;
        tmp_i10 = 0;
        tmp_i5 = 10;
      }
      break;
    }
    goto LAB_000869b9;
  case 0xf:
    if ((int)tmp_pu8[0xb2] < 1) {
LAB_00086ea2:
      tmp_i5 = 0;
      goto LAB_00086dc4;
    }
LAB_00086bf1:
    tmp_i10 = 0;
    tmp_i5 = 3;
    break;
  case 0x20:
    tmp_i5 = G_ConstructionIsPartlyBuilt(tmp_pu8);
    tmp_l16 = (long double)(float)tmp_l16;
    if ((tmp_i5 == 0) || ((*(byte *)(tmp_pu8 + 0x6a) & 2) != 0)) goto LAB_00086ea2;
    if (tmp_pu8[0x42] == *(int *)(*(int *)(param_1 + 400) + 3000)) {
      *(uint32_t *)(tmp_i2 + 0x428) = 1;
      *(uint32_t *)(tmp_i2 + 0x42c) = 0;
      return;
    }
    tmp_i5 = tmp_pu8[0x13d];
    if (tmp_i5 == 1) goto LAB_000871f3;
    if (tmp_i5 == 2) {
      local_68 = 16384.0;
      tmp_i10 = 0;
      tmp_i5 = 10;
      *(uint32_t *)(tmp_i2 + 0x42c) = 0;
      break;
    }
    if (tmp_i5 == 0) {
      tmp_i5 = tmp_pu8[0xb2];
      goto LAB_00086bb2;
    }
LAB_000869a6:
    *(uint32_t *)(tmp_i2 + 0x428) = 1;
    *(uint32_t *)(tmp_i2 + 0x42c) = 0;
LAB_000869b9:
    tmp_i5 = 1;
    local_68 = 0.0;
    tmp_i10 = 0;
    break;
  case 0x26:
    tmp_i10 = *(int *)(param_1 + 400);
    if (((*(int *)(tmp_i10 + 0x168) == 0) && (*(int *)(tmp_i10 + 0x164) == 0)) &&
       (*(int *)(tmp_i10 + 0x16c) == 0)) {
      if (tmp_pu9[0x16] == 0) {
        if (tmp_pu9[0x29] == *(int *)(tmp_i10 + 3000)) {
          if (GHIDRA_FIELD(g_classChange, 12, 4) != 0) goto LAB_00086ed5;
        }
        else {
          if ((tmp_pu9[0xa7] == tmp_pu9[0x93] + 20000) && (*(int *)(tmp_i10 + 0xe4) == 4)) {
            local_68 = 2304.0;
            tmp_i10 = 0xff;
            if ((int)tmp_pu9[0xc0] < 0x100) {
              tmp_i10 = tmp_pu9[0xc0];
            }
            tmp_i5 = 0x22;
            break;
          }
          if (GHIDRA_FIELD(g_classChange, 12, 4) != 0) goto LAB_00086ea2;
        }
      }
      if (tmp_u4 != 0) {
        return;
      }
      goto LAB_0008678f;
    }
    if (GHIDRA_FIELD(g_classChange, 12, 4) == 0) goto LAB_00086ea2;
    tmp_i5 = 0;
    if ((tmp_pu9[0x16] != 0) || (tmp_pu9[0x29] != *(int *)(tmp_i10 + 3000))) goto LAB_00086dc4;
LAB_00086ed5:
    if (*(int *)(tmp_i10 + 0xbc8) == tmp_pu9[0x2a]) goto LAB_00086ea2;
    local_68 = 2304.0;
    tmp_i5 = (-(uint)(GHIDRA_FIELD(g_war, 12, 4) - 1 < 4) & 4) + 0x22;
    tmp_i10 = 0xff;
    if ((int)tmp_pu9[0xc0] < 0x100) {
      tmp_i10 = tmp_pu9[0xc0];
    }
LAB_00086f16:
    if (tmp_u4 != 0) {
      if (0x1a < tmp_i5 - 2U) {
        return;
      }
      if ((1 << ((byte)(tmp_i5 - 2U) & 0x1f) & 0x7e02001U) == 0) {
        return;
      }
      local_68 = 67108864.0;
    }
    goto LAB_00086793;
  }
LAB_000869d0:
  if (tmp_u4 == 0) {
LAB_00086793:
    if (tmp_l16 <= (long double)local_68) {
      *(int *)(tmp_i2 + 0x428) = tmp_i5;
      *(int *)(tmp_i2 + 0x42c) = tmp_i10;
    }
  }
  return;
_L205:
  tmp_i10 = 0;
  tmp_i5 = 0;
  goto LAB_000869d0;
}

void G_SetTargetName(int param_1,char *param_2)
{
  uint32_t tmp_u1;
  
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    *(char **)(param_1 + 600) = param_2;
    tmp_u1 = BG_StringHashValue(param_2);
    *(uint32_t *)(param_1 + 0x25c) = tmp_u1;
    return;
  }
  *(uint32_t *)(param_1 + 0x25c) = 0xffffffff;
  return;
}

void G_FindTeams(void)
{
  char *tmp_pc1;
  bool tmp_b2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  int local_2c;
  int local_28;
  
  if (g_unk_00abe8a8 < 2) {
    local_2c = 0;
    local_28 = 0;
  }
  else {
    local_2c = 0;
    local_28 = 0;
    tmp_i8 = 0x93eaa0;
    tmp_i6 = g_unk_00abe8a8;
    tmp_i7 = 2;
    do {
      if (((*(int *)(tmp_i8 + 0x194) != 0) && (*(int *)(tmp_i8 + 0x260) != 0)) &&
         ((*(byte *)(tmp_i8 + 0x1b1) & 4) == 0)) {
        if (*(int *)(tmp_i8 + 0x5c0) == 0x26903) {
          if ((*(byte *)(tmp_i8 + 0x1a8) & 8) == 0) goto LAB_00087750;
          *(int *)(tmp_i8 + 0x2f8) = tmp_i8;
        }
        local_28 = local_28 + 1;
        local_2c = local_2c + 1;
        tmp_i10 = tmp_i7;
        tmp_i3 = tmp_i8;
        if (tmp_i6 <= tmp_i7) break;
        do {
          tmp_i9 = tmp_i3 + 0x600;
          if (((*(int *)(tmp_i3 + 0x794) != 0) && (*(char **)(tmp_i3 + 0x860) != (char *)0x0)) &&
             (((*(byte *)(tmp_i3 + 0x7b1) & 4) == 0 &&
              (tmp_i4 = strcmp(*(char **)(tmp_i8 + 0x260),*(char **)(tmp_i3 + 0x860)), tmp_i4 == 0)))) {
            local_2c = local_2c + 1;
            *(uint32_t *)(tmp_i3 + 0x8f4) = *(uint32_t *)(tmp_i8 + 0x2f4);
            *(int *)(tmp_i8 + 0x2f4) = tmp_i9;
            *(uint *)(tmp_i3 + 0x7b0) = *(uint *)(tmp_i3 + 0x7b0) | 0x400;
            *(int *)(tmp_i3 + 0x8f8) = tmp_i8;
            if (*(int *)(tmp_i3 + 0xbc0) == 0x26903) {
              trap_UnlinkEntity(tmp_i9);
            }
            tmp_pc1 = *(char **)(tmp_i3 + 0x858);
            tmp_i6 = g_unk_00abe8a8;
            if (tmp_pc1 != (char *)0x0) {
              if (*tmp_pc1 == '\0') {
                *(uint32_t *)(tmp_i8 + 0x25c) = 0xffffffff;
              }
              else {
                *(char **)(tmp_i8 + 600) = tmp_pc1;
                tmp_u5 = BG_StringHashValue(tmp_pc1);
                *(uint32_t *)(tmp_i8 + 0x25c) = tmp_u5;
              }
              tmp_i6 = g_unk_00abe8a8;
              if (*(int *)(tmp_i3 + 0xbc0) != 0x3bf8a) {
                *(uint32_t *)(tmp_i3 + 0x858) = 0;
                tmp_i6 = g_unk_00abe8a8;
              }
            }
          }
          tmp_i10 = tmp_i10 + 1;
          tmp_i3 = tmp_i9;
        } while (tmp_i10 < tmp_i6);
      }
LAB_00087750:
      tmp_i8 = tmp_i8 + 0x600;
      tmp_b2 = tmp_i7 < tmp_i6;
      tmp_i7 = tmp_i7 + 1;
    } while (tmp_b2);
  }
  G_Printf("%i teams with %i entities\n",local_28,local_2c);
  return;
}

void G_RegisterCvars(void)
{
  uint8_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  char *tmp_pc4;
  uint8_t **tmp_ppu5;
  char *tmp_pc6;
  char *tmp_pc7;
  bool tmp_b8;
  byte tmp_b9;
  
  tmp_b9 = 0;
  g_unk_02a99a80 = 0;
  tmp_ppu5 = &gameCvarTable;
  G_Printf("%d cvars in use.\n",0x153);
  trap_Cvar_Register(g_serverInfo,"g_serverInfo",&g_unk_00258b23,0x40);
  do {
    if ((GHIDRA_FIELD(g_serverInfo, 12, 4) & 0x10) == 0) {
      tmp_pu1 = tmp_ppu5[3];
      tmp_pc4 = tmp_ppu5[1];
    }
    else {
      tmp_pc4 = tmp_ppu5[1];
      tmp_i3 = 0x12;
      tmp_b8 = false;
      tmp_pc6 = tmp_pc4;
      tmp_pc7 = "g_medicChargeTime";
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_b8 = *tmp_pc6 == *tmp_pc7;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
        tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
      } while (tmp_b8);
      if (!tmp_b8) {
        tmp_i3 = 0xf;
        tmp_pc6 = tmp_pc4;
        tmp_pc7 = "g_LTChargeTime";
        do {
          if (tmp_i3 == 0) break;
          tmp_i3 = tmp_i3 + -1;
          tmp_b8 = *tmp_pc6 == *tmp_pc7;
          tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
          tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
        } while (tmp_b8);
        if (!tmp_b8) {
          tmp_i3 = 0x15;
          tmp_pc6 = tmp_pc4;
          tmp_pc7 = "g_engineerChargeTime";
          do {
            if (tmp_i3 == 0) break;
            tmp_i3 = tmp_i3 + -1;
            tmp_b8 = *tmp_pc6 == *tmp_pc7;
            tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
            tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
          } while (tmp_b8);
          if (!tmp_b8) {
            tmp_i3 = 0x14;
            tmp_pc6 = tmp_pc4;
            tmp_pc7 = "g_soldierChargeTime";
            do {
              if (tmp_i3 == 0) break;
              tmp_i3 = tmp_i3 + -1;
              tmp_b8 = *tmp_pc6 == *tmp_pc7;
              tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
              tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
            } while (tmp_b8);
            if (!tmp_b8) {
              tmp_i3 = 0x16;
              tmp_pc6 = tmp_pc4;
              tmp_pc7 = "g_covertopsChargeTime";
              do {
                if (tmp_i3 == 0) break;
                tmp_i3 = tmp_i3 + -1;
                tmp_b8 = *tmp_pc6 == *tmp_pc7;
                tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
                tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
              } while (tmp_b8);
              if (!tmp_b8) {
                tmp_pu1 = tmp_ppu5[3];
                goto LAB_0008787e;
              }
            }
          }
        }
      }
      tmp_pu1 = (uint8_t *)((uint)tmp_ppu5[3] | 4);
      tmp_ppu5[3] = tmp_pu1;
    }
LAB_0008787e:
    trap_Cvar_Register(*tmp_ppu5,tmp_pc4,tmp_ppu5[2],tmp_pu1);
    tmp_pu1 = *tmp_ppu5;
    if (tmp_pu1 != (uint8_t *)0x0) {
      tmp_ppu5[4] = *(uint8_t **)(tmp_pu1 + 4);
      G_checkServerToggle(tmp_pu1);
    }
    tmp_ppu5 = tmp_ppu5 + 7;
    if (tmp_ppu5 == (uint8_t **)&g_unk_002ba334) {
      if ((GHIDRA_FIELD(g_serverInfo, 12, 4) & 2) != 0) {
        trap_Cvar_Register(0,"Players_Axis",&g_unk_0026ea14,0x2000);
        trap_Cvar_Set("Players_Axis",
                      "................................................................................................................................................................................"
                     );
        trap_Cvar_Register(0,"Players_Allies",&g_unk_0026ea14,0x2000);
        trap_Cvar_Set("Players_Allies","(none)");
      }
      if ((GHIDRA_FIELD(g_serverInfo, 12, 4) & 1) != 0) {
        trap_Cvar_Register(0,"P",&g_unk_0026ea14,0x2000);
        trap_Cvar_Set("P","..............................................................");
      }
      if (6 < GHIDRA_FIELD(g_gametype, 12, 4) - 2) {
        G_Printf("g_gametype %i is out of range, defaulting to GT_WOLF(%i)\n",GHIDRA_FIELD(g_gametype, 12, 4),2);
        tmp_u2 = va("%i",2);
        trap_Cvar_Set("g_gametype",tmp_u2);
        trap_Cvar_Update(g_gametype);
      }
      tmp_u2 = va(&g_unk_00245ee9,g_unk_02a99a80);
      trap_SetConfigstring(0x1d,tmp_u2);
      if ((int)GHIDRA_FIELD(match_readypercent, 12, 4) < 1) {
        trap_Cvar_Set("match_readypercent",&g_unk_00258b23);
      }
      if ((int)GHIDRA_FIELD(pmove_msec, 12, 4) < 8) {
        trap_Cvar_Set("pmove_msec",&g_unk_00261bbb);
      }
      else if (0x21 < (int)GHIDRA_FIELD(pmove_msec, 12, 4)) {
        trap_Cvar_Set("pmove_msec",&g_unk_0024992b);
      }
      if ((int)GHIDRA_FIELD(g_fixedphysicsfps, 12, 4) < 0x3c) {
        trap_Cvar_Set("g_fixedphysicsfps",&g_unk_00248d19);
        return;
      }
      if ((int)GHIDRA_FIELD(g_fixedphysicsfps, 12, 4) < 0x14e) {
        return;
      }
      trap_Cvar_Set("g_fixedphysicsfps",&g_unk_0024992a);
      return;
    }
  } while( true );
}

void G_UpdateInfo(void)
{
  uint8_t local_40c [1024];
  
  local_40c[0] = 0;
  Info_SetValueForKey(local_40c,&g_unk_002612d7,&g_unk_02ad55a4);
  Info_SetValueForKey(local_40c,&g_unk_00260a4c,&g_unk_02ad56a4);
  trap_SetConfigstring(0x24,local_40c);
  return;
}

uint32_t G_ConfigParse_constprop_11(uint32_t param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  char *tmp_pc4;
  bool tmp_b5;
  byte tmp_b6;
  uint8_t local_634 [256];
  char local_534 [256];
  uint8_t local_434 [16];
  char local_424;
  char local_423;
  char local_422;
  char local_421;
  uint32_t uStack_14;
  
  tmp_b6 = 0;
  uStack_14 = 0x88489;
  tmp_i1 = trap_PC_ReadToken(param_1,local_434);
  if (((tmp_i1 == 0) || (local_424 != '{')) || (local_423 != '\0')) {
    tmp_u2 = BG_PCF_ParseError(param_1,"expected \'{\'");
    return tmp_u2;
  }
  do {
    while( true ) {
      tmp_i1 = trap_PC_ReadToken(param_1,local_434);
      if ((tmp_i1 == 0) || (local_424 == '}')) {
        return 1;
      }
      if (((local_424 == 's') && (local_423 == 'e')) && ((local_422 == 't' && (local_421 == '\0'))))
      break;
      tmp_b5 = false;
      tmp_i1 = 8;
      tmp_pc3 = &local_424;
      tmp_pc4 = "command";
      do {
        if (tmp_i1 == 0) break;
        tmp_i1 = tmp_i1 + -1;
        tmp_b5 = *tmp_pc3 == *tmp_pc4;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
      } while (tmp_b5);
      if (tmp_b5) {
        tmp_i1 = PC_String_ParseNoAlloc(param_1,local_634,0x100);
        if (tmp_i1 == 0) {
          tmp_u2 = BG_PCF_ParseError(param_1,"expected command to execute");
          return tmp_u2;
        }
        tmp_u2 = va(&g_unk_0026fe3c,local_634);
        trap_SendConsoleCommand(2,tmp_u2);
      }
      else {
        tmp_i1 = 5;
        tmp_b5 = false;
        tmp_pc3 = &local_424;
        tmp_pc4 = "setl";
        do {
          if (tmp_i1 == 0) break;
          tmp_i1 = tmp_i1 + -1;
          tmp_b5 = *tmp_pc3 == *tmp_pc4;
          tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
          tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
        } while (tmp_b5);
        if (!tmp_b5) {
          tmp_u2 = BG_PCF_ParseError(param_1,"unknown token \'%s\'",&local_424);
          return tmp_u2;
        }
        tmp_i1 = PC_String_ParseNoAlloc(param_1,&g_unk_02ad56a4 + (g_unk_02af58a4 + 1) * 0x200,0x100);
        if (tmp_i1 == 0) {
          tmp_u2 = BG_PCF_ParseError(param_1,"expected name of cvar to set and lock");
          return tmp_u2;
        }
        tmp_i1 = PC_String_ParseNoAlloc(param_1,&g_unk_02ad59a4 + g_unk_02af58a4 * 0x200,0x100);
        if (tmp_i1 == 0) {
          tmp_u2 = BG_PCF_ParseError(param_1,"expected value of cvar to set and lock");
          return tmp_u2;
        }
        if ((&g_unk_02ad59a4)[g_unk_02af58a4 * 0x200] == '-') {
          tmp_i1 = PC_String_ParseNoAlloc(param_1,local_634,0x100);
          if (tmp_i1 == 0) goto LAB_0008889b;
          tmp_u2 = va(&g_unk_00260b9d,local_634);
          Q_strncpyz(&g_unk_02ad59a4 + g_unk_02af58a4 * 0x200,tmp_u2,0x100);
        }
        Q_strncpyz(&g_unk_02ac4198 + g_unk_02af58a4 * 0x200,&g_unk_02ad56a4 + (g_unk_02af58a4 + 1) * 0x200,
                   0x100);
        Q_strncpyz(&g_unk_02ac4298 + g_unk_02af58a4 * 0x200,&g_unk_02ad59a4 + g_unk_02af58a4 * 0x200,0x100);
        g_unk_02af58a4 = g_unk_02af58a4 + 1;
        g_unk_02ad4198 = g_unk_02ad4198 + 1;
      }
    }
    tmp_i1 = PC_String_ParseNoAlloc(param_1,local_634,0x100);
    if (tmp_i1 == 0) {
      tmp_u2 = BG_PCF_ParseError(param_1,"expected cvar to set");
      return tmp_u2;
    }
    tmp_i1 = PC_String_ParseNoAlloc(param_1,local_534,0x100);
    if (tmp_i1 == 0) {
      tmp_u2 = BG_PCF_ParseError(param_1,"expected cvar value");
      return tmp_u2;
    }
    if (local_534[0] == '-') {
      tmp_i1 = PC_String_ParseNoAlloc(param_1,local_634,0x100);
      if (tmp_i1 == 0) {
LAB_0008889b:
        tmp_u2 = BG_PCF_ParseError(param_1,"expected value after \'-\'");
        return tmp_u2;
      }
      tmp_u2 = va(&g_unk_00260b9d,local_634);
      Q_strncpyz(local_534,tmp_u2,0x100);
    }
    trap_Cvar_Set(local_634,local_534);
  } while( true );
}

uint32_t G_LoadConfig(char *param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  char *tmp_pc5;
  bool tmp_b6;
  byte tmp_b7;
  uint8_t local_874 [64];
  uint8_t local_834 [1024];
  uint8_t local_434 [16];
  char local_424 [1044];
  
  tmp_b7 = 0;
  if (*param_1 == '\0') {
    if (g_customConfig[0x10] == '\0') {
      if (g_mapConfigs[0x10] == '\0') {
        return 0;
      }
      Q_strncpyz(local_874,0x2e5a150,0x40);
      Q_strcat(local_874,0x40,&g_unk_0024ed91);
      Q_strcat(local_874,0x40,&g_unk_00abe8c0);
      Q_strcat(local_874,0x40,".config");
      goto LAB_00088958;
    }
    Q_strncpyz(local_874,0x2e50070,0x40);
    if (g_unk_02af58a8 != 0) goto LAB_00088949;
  }
  else {
    Q_strncpyz(local_874,param_1,0x40);
LAB_00088949:
    if (param_2 == 0) goto LAB_00088958;
  }
  memset(&g_unk_02ad56a4,0,0x20208);
LAB_00088958:
  tmp_i1 = trap_PC_LoadSource(local_874);
  if (tmp_i1 == 0) {
    G_Printf("^3Warning: No config with filename \'%s\' found\n",local_874);
    return 0;
  }
LAB_00088980:
  do {
    tmp_i2 = trap_PC_ReadToken(tmp_i1,local_434);
    if (tmp_i2 == 0) {
      g_unk_02af58a8 = 1;
      trap_PC_FreeSource(tmp_i1);
      local_834[0] = 0;
      Info_SetValueForKey(local_834,&g_unk_002612d7,&g_unk_02ad55a4);
      Info_SetValueForKey(local_834,&g_unk_00260a4c,&g_unk_02ad56a4);
      trap_SetConfigstring(0x24,local_834);
      return 1;
    }
    tmp_i2 = 0xb;
    tmp_b6 = false;
    tmp_pc4 = local_424;
    tmp_pc5 = "configname";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_b6 = *tmp_pc4 == *tmp_pc5;
      tmp_pc4 = tmp_pc4 + (uint)tmp_b7 * -2 + 1;
      tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
    } while (tmp_b6);
    if (tmp_b6) {
      tmp_i2 = PC_String_ParseNoAlloc(tmp_i1,&g_unk_02ad56a4,0x100);
      if (tmp_i2 == 0) {
        tmp_u3 = BG_PCF_ParseError(tmp_i1,"expected config name");
        return tmp_u3;
      }
      goto LAB_00088980;
    }
    tmp_i2 = 8;
    tmp_b6 = false;
    tmp_pc4 = local_424;
    tmp_pc5 = "version";
    do {
      if (tmp_i2 == 0) break;
      tmp_i2 = tmp_i2 + -1;
      tmp_b6 = *tmp_pc4 == *tmp_pc5;
      tmp_pc4 = tmp_pc4 + (uint)tmp_b7 * -2 + 1;
      tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
    } while (tmp_b6);
    if (tmp_b6) {
      tmp_i2 = PC_String_ParseNoAlloc(tmp_i1,&g_unk_02ad57a4,0x100);
      if (tmp_i2 == 0) {
        tmp_u3 = BG_PCF_ParseError(tmp_i1,"expected config version");
        return tmp_u3;
      }
    }
    else {
      tmp_i2 = 5;
      tmp_b6 = false;
      tmp_pc4 = local_424;
      tmp_pc5 = "init";
      do {
        if (tmp_i2 == 0) break;
        tmp_i2 = tmp_i2 + -1;
        tmp_b6 = *tmp_pc4 == *tmp_pc5;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b7 * -2 + 1;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
      } while (tmp_b6);
      if (tmp_b6) {
        tmp_i2 = G_ConfigParse_constprop_11();
        if (tmp_i2 == 0) {
          tmp_u3 = BG_PCF_ParseError(tmp_i1,"failed to load init struct");
          return tmp_u3;
        }
        if (g_unk_02ad56a4 != '\0') {
          tmp_u3 = va("cp \"\'%s^7\' config loaded\n\"",&g_unk_02ad56a4);
          trap_SendServerCommand(0xffffffff,tmp_u3);
        }
      }
      else {
        tmp_i2 = 8;
        tmp_b6 = false;
        tmp_pc4 = local_424;
        tmp_pc5 = "default";
        do {
          if (tmp_i2 == 0) break;
          tmp_i2 = tmp_i2 + -1;
          tmp_b6 = *tmp_pc4 == *tmp_pc5;
          tmp_pc4 = tmp_pc4 + (uint)tmp_b7 * -2 + 1;
          tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
        } while (tmp_b6);
        if (tmp_b6) {
          tmp_i2 = G_ConfigParse_constprop_11();
          if (tmp_i2 == 0) {
            tmp_u3 = BG_PCF_ParseError(tmp_i1,"failed to load default struct");
            return tmp_u3;
          }
        }
        else {
          tmp_i2 = strcmp(local_424,&g_unk_00abe8c0);
          if ((tmp_i2 == 0) && (tmp_i2 = G_ConfigParse_constprop_11(), tmp_i2 == 0)) {
            tmp_u3 = BG_PCF_ParseError(tmp_i1,"failed to load %s struct",&g_unk_00abe8c0);
            return tmp_u3;
          }
        }
      }
    }
  } while( true );
}

void G_mapvoteinfo_write(void)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  char *tmp_pc4;
  uint32_t local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0x891de;
  trap_FS_FOpenFile("mapvoteinfo.cfg",local_20,1);
  tmp_pc3 = &g_unk_02aa03a0;
  do {
    while (*tmp_pc3 != '\0') {
      trap_FS_Write("[mapvoteinfo]\n",0xe,local_20[0]);
      trap_FS_Write("name             = ",0x13,local_20[0]);
      tmp_pc4 = tmp_pc3 + 0x98;
      G_shrubbot_writeconfig_string(tmp_pc3,local_20[0]);
      trap_FS_Write("times_played     = ",0x13,local_20[0]);
      tmp_u1 = local_20[0];
      tmp_u2 = va(&g_unk_00245ee9,*(uint32_t *)(tmp_pc3 + 0x84));
      G_shrubbot_writeconfig_string(tmp_u2,tmp_u1);
      trap_FS_Write("last_played      = ",0x13,local_20[0]);
      tmp_u1 = local_20[0];
      tmp_u2 = va(&g_unk_00245ee9,*(uint32_t *)(tmp_pc3 + 0x88));
      G_shrubbot_writeconfig_string(tmp_u2,tmp_u1);
      trap_FS_Write("total_votes      = ",0x13,local_20[0]);
      tmp_u1 = local_20[0];
      tmp_u2 = va(&g_unk_00245ee9,*(uint32_t *)(tmp_pc3 + 0x8c));
      G_shrubbot_writeconfig_string(tmp_u2,tmp_u1);
      trap_FS_Write("vote_eligible    = ",0x13,local_20[0]);
      tmp_u1 = local_20[0];
      tmp_u2 = va(&g_unk_00245ee9,*(uint32_t *)(tmp_pc3 + 0x90));
      G_shrubbot_writeconfig_string(tmp_u2,tmp_u1);
      trap_FS_Write("\n",1,local_20[0]);
      tmp_pc3 = tmp_pc4;
      if (tmp_pc4 == (char *)&g_unk_02aa29a0) goto LAB_000893ca;
    }
    tmp_pc3 = tmp_pc3 + 0x98;
  } while (tmp_pc3 != (char *)&g_unk_02aa29a0);
LAB_000893ca:
  G_Printf("mapvoteinfo: wrote %d map vote stats\n",0x40);
  trap_FS_FCloseFile(local_20[0]);
  return;
}

void G_mapvoteinfo_read(void)
{
  int tmp_i1;
  void *__ptr;
  char *tmp_pc2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  char *tmp_pc6;
  char *tmp_pc7;
  bool tmp_b8;
  byte tmp_b9;
  uint32_t local_a4;
  void *local_a0;
  char local_9c [136];
  uint32_t uStack_14;
  
  tmp_b9 = 0;
  uStack_14 = 0x8940b;
  tmp_i1 = trap_FS_FOpenFile("mapvoteinfo.cfg",&local_a4,0);
  if (tmp_i1 < 0) {
    G_Printf("readconfig: could not open mapvoteinfo file\n");
    return;
  }
  __ptr = malloc(tmp_i1 + 1);
  local_a0 = __ptr;
  trap_FS_Read(__ptr,tmp_i1,local_a4);
  *(uint8_t *)((int)local_a0 + tmp_i1) = 0;
  trap_FS_FCloseFile(local_a4);
  tmp_pc2 = (char *)COM_Parse(&local_a0);
  tmp_b8 = *tmp_pc2 == '\0';
  if (!tmp_b8) {
    tmp_i1 = -1;
    do {
      tmp_i5 = 5;
      tmp_pc6 = tmp_pc2;
      tmp_pc7 = "name";
      do {
        if (tmp_i5 == 0) break;
        tmp_i5 = tmp_i5 + -1;
        tmp_b8 = *tmp_pc6 == *tmp_pc7;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
        tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
      } while (tmp_b8);
      if (tmp_b8) {
        G_shrubbot_readconfig_string(&local_a0,local_9c,0x80);
        tmp_i5 = g_unk_02aa0298;
        if (0 < g_unk_02aa0298) {
          tmp_pc2 = &g_unk_02aa03a0;
          tmp_i1 = 0;
          do {
            tmp_i3 = strcmp(local_9c,tmp_pc2);
            if (tmp_i3 == 0) goto LAB_00089530;
            tmp_i1 = tmp_i1 + 1;
            tmp_pc2 = tmp_pc2 + 0x98;
          } while (tmp_i1 != tmp_i5);
        }
        tmp_i1 = -1;
      }
      else {
        tmp_i5 = 0xd;
        tmp_pc6 = tmp_pc2;
        tmp_pc7 = "times_played";
        do {
          if (tmp_i5 == 0) break;
          tmp_i5 = tmp_i5 + -1;
          tmp_b8 = *tmp_pc6 == *tmp_pc7;
          tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
          tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
        } while (tmp_b8);
        if (tmp_b8) {
          G_shrubbot_readconfig_int(&local_a0,&g_unk_02aa0424 + tmp_i1 * 0x26);
        }
        else {
          tmp_i5 = 0xc;
          tmp_b8 = false;
          tmp_pc6 = tmp_pc2;
          tmp_pc7 = "last_played";
          do {
            if (tmp_i5 == 0) break;
            tmp_i5 = tmp_i5 + -1;
            tmp_b8 = *tmp_pc6 == *tmp_pc7;
            tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
            tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
          } while (tmp_b8);
          if (tmp_b8) {
            G_shrubbot_readconfig_int(&local_a0,&g_unk_02aa0428 + tmp_i1 * 0x26);
          }
          else {
            tmp_i5 = 0xc;
            tmp_b8 = false;
            tmp_pc6 = tmp_pc2;
            tmp_pc7 = "total_votes";
            do {
              if (tmp_i5 == 0) break;
              tmp_i5 = tmp_i5 + -1;
              tmp_b8 = *tmp_pc6 == *tmp_pc7;
              tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
              tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
            } while (tmp_b8);
            if (tmp_b8) {
              G_shrubbot_readconfig_int(&local_a0,&g_unk_02aa042c + tmp_i1 * 0x26);
            }
            else {
              tmp_i5 = 0xe;
              tmp_b8 = false;
              tmp_pc6 = tmp_pc2;
              tmp_pc7 = "vote_eligible";
              do {
                if (tmp_i5 == 0) break;
                tmp_i5 = tmp_i5 + -1;
                tmp_b8 = *tmp_pc6 == *tmp_pc7;
                tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
                tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
              } while (tmp_b8);
              if (tmp_b8) {
                G_shrubbot_readconfig_int(&local_a0,&g_unk_02aa0430 + tmp_i1 * 0x26);
              }
              else {
                tmp_i5 = 0xe;
                tmp_b8 = false;
                tmp_pc6 = tmp_pc2;
                tmp_pc7 = "[mapvoteinfo]";
                do {
                  if (tmp_i5 == 0) break;
                  tmp_i5 = tmp_i5 + -1;
                  tmp_b8 = *tmp_pc6 == *tmp_pc7;
                  tmp_pc6 = tmp_pc6 + (uint)tmp_b9 * -2 + 1;
                  tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
                } while (tmp_b8);
                if (!tmp_b8) {
                  tmp_u4 = COM_GetCurrentParseLine();
                  G_Printf("mapvoteinfo: [mapvoteinfo] parse error near %s on line %d\n",tmp_pc2,
                           tmp_u4);
                }
              }
            }
          }
        }
      }
LAB_00089530:
      tmp_pc2 = (char *)COM_Parse(&local_a0);
      tmp_b8 = *tmp_pc2 == '\0';
    } while (!tmp_b8);
  }
  free(__ptr);
  return;
}

void G_GetRealTime(void)
{
  uint8_t *tmp_pu1;
  uint8_t *tmp_pu2;
  int local_30;
  int local_2c;
  uint32_t local_28;
  uint32_t uStack_c;
  
  uStack_c = 0x89b57;
  trap_RealTime(&local_30);
  if (local_30 < 10) {
    tmp_pu1 = &g_unk_0024bfa6;
  }
  else {
    tmp_pu1 = &g_unk_0026ea14;
  }
  if (local_2c < 10) {
    tmp_pu2 = &g_unk_0024bfa6;
  }
  else {
    tmp_pu2 = &g_unk_0026ea14;
  }
  va(&g_unk_00249b64,local_28,tmp_pu2,local_2c,tmp_pu1,local_30);
  return;
}

void G_LogPrintf(char *param_1)
{
  char *__s;
  uint32_t tmp_u1;
  uint tmp_u2;
  uint tmp_u3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  uint *tmp_pu6;
  uint *tmp_pu7;
  uint8_t *tmp_pu8;
  int tmp_i9;
  uint32_t local_420;
  uint local_41c [259];
  
  if ((((*param_1 != 's') || (param_1[1] != 'a')) || (param_1[2] != 'y')) ||
     (local_420 = 1, tmp_i9 = g_unk_00abe8b0, g_unk_00abe8b0 == 0)) {
    local_420 = 0;
    tmp_i9 = g_unk_00abe8b4;
  }
  if (GHIDRA_FIELD(n_LogCurrentTime, 12, 4) == 0) {
    tmp_i5 = (g_unk_00abe908 / 1000) % 0x3c;
    Com_sprintf(local_41c,0x400,"%i:%i%i ",(g_unk_00abe908 / 1000) / 0x3c,tmp_i5 / 10,tmp_i5 % 10);
    goto LAB_00089c99;
  }
  trap_RealTime(local_41c);
  if ((int)local_41c[0] < 10) {
    tmp_pu8 = &g_unk_0024bfa6;
    if (9 < (int)local_41c[1]) goto LAB_00089ea3;
LAB_00089c4e:
    tmp_pu4 = &g_unk_0024bfa6;
  }
  else {
    tmp_pu8 = &g_unk_0026ea14;
    if ((int)local_41c[1] < 10) goto LAB_00089c4e;
LAB_00089ea3:
    tmp_pu4 = &g_unk_0026ea14;
  }
  tmp_u1 = va(&g_unk_00249b64,local_41c[2],tmp_pu4,local_41c[1],tmp_pu8,local_41c[0]);
  Com_sprintf(local_41c,0x400,&g_unk_00249b72,tmp_u1);
LAB_00089c99:
  tmp_pu7 = local_41c;
  do {
    tmp_pu6 = tmp_pu7;
    tmp_u2 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
    tmp_u3 = tmp_u2 & 0x80808080;
    tmp_pu7 = tmp_pu6 + 1;
  } while (tmp_u3 == 0);
  if ((tmp_u2 & 0x8080) == 0) {
    tmp_pu7 = (uint *)((int)tmp_pu6 + 6);
    tmp_u3 = tmp_u3 >> 0x10;
  }
  tmp_i5 = (int)tmp_pu7 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_41c);
  __s = (char *)((int)local_41c + tmp_i5);
  vsnprintf(__s,0x400 - tmp_i5,param_1,&stack0x00000008);
  tmp_pu7 = local_41c;
  if (local_420 != 0) {
    do {
      tmp_pu6 = tmp_pu7;
      tmp_u2 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
      tmp_u3 = tmp_u2 & 0x80808080;
      tmp_pu7 = tmp_pu6 + 1;
    } while (tmp_u3 == 0);
    if ((tmp_u2 & 0x8080) == 0) {
      tmp_pu7 = (uint *)((int)tmp_pu6 + 6);
      tmp_u3 = tmp_u3 >> 0x10;
    }
    if (*(char *)((int)tmp_pu7 +
                 (int)local_41c + (-(int)local_41c - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) + -4) !=
        '\n') {
      Q_strcat(local_41c,0x400,"\n");
    }
  }
  if (GHIDRA_FIELD(g_dedicated, 12, 4) != 0) {
    G_Printf(&g_unk_0024e6e9,__s);
  }
  tmp_pu7 = local_41c;
  if (tmp_i9 != 0) {
    do {
      tmp_pu6 = tmp_pu7;
      tmp_u2 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
      tmp_u3 = tmp_u2 & 0x80808080;
      tmp_pu7 = tmp_pu6 + 1;
    } while (tmp_u3 == 0);
    if ((tmp_u2 & 0x8080) == 0) {
      tmp_pu7 = (uint *)((int)tmp_pu6 + 6);
      tmp_u3 = tmp_u3 >> 0x10;
    }
    trap_FS_Write(local_41c,
                  (int)tmp_pu7 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_41c),
                  tmp_i9);
    return;
  }
  return;
}

void G_ShutdownGame(uint32_t param_1)
{
  uint tmp_u1;
  int tmp_i2;
  int *tmp_pi3;
  int tmp_i4;
  int tmp_i5;
  uint32_t tmp_u6;
  
  NxAC_ClearCvarList();
  NxAC_ClearChecksumList();
  nitrox_XPSave_WriteAllXP();
  nitrox_SaveDB_console();
  if (0 < g_unk_00abe900) {
    tmp_pi3 = (int *)(g_entities + 0x194);
    tmp_i2 = g_unk_00abe900;
    tmp_i4 = 0;
    do {
      while ((*tmp_pi3 != 0 && ((*(byte *)(tmp_pi3 + -0x1b) & 8) == 0))) {
        tmp_i5 = tmp_i4 + 1;
        tmp_pi3 = tmp_pi3 + 0x180;
        nitrox_ClearSocketInfos(tmp_i4);
        tmp_i2 = g_unk_00abe900;
        tmp_i4 = tmp_i5;
        if (g_unk_00abe900 <= tmp_i5) goto LAB_00089f50;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pi3 = tmp_pi3 + 0x180;
    } while (tmp_i4 < tmp_i2);
  }
LAB_00089f50:
  nitrox_SQLite_close();
  G_LuaHook_ShutdownGame(param_1);
  G_LuaShutdown();
  nitrox_CloseMasterSocket();
  if ((((GHIDRA_FIELD(g_gametype, 12, 4) & 0xfffffffb) == 2) || (GHIDRA_FIELD(g_gametype, 12, 4) == 4)) &&
     ((GHIDRA_FIELD(g_entities, 1570184, 4) & 1) != 0)) {
LAB_0008a01a:
    tmp_u6 = 5;
  }
  else {
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 3) {
      tmp_u1 = GHIDRA_FIELD(g_entities, 1570184, 4) & 2;
    }
    else {
      if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) goto LAB_00089f99;
      tmp_u1 = GHIDRA_FIELD(g_entities, 1570184, 4) & 8;
    }
    if (tmp_u1 == 0) goto LAB_00089f99;
    if ((GHIDRA_FIELD(g_entities, 1570184, 4) & 1) != 0) goto LAB_0008a01a;
    tmp_u6 = 2;
  }
  tmp_u6 = va("%i",tmp_u6);
  trap_Cvar_Set("g_gametype",tmp_u6);
  trap_Cvar_Update(g_gametype);
LAB_00089f99:
  G_Printf("==== ShutdownGame ====\n");
  G_DebugCloseSkillLog();
  if (g_unk_00abe8b0 != 0) {
    trap_FS_Write("~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+\n",0x41,
                  g_unk_00abe8b0);
    trap_FS_FCloseFile(g_unk_00abe8b0);
    g_unk_00abe8b0 = 0;
  }
  if (g_unk_00abe8b8 != 0) {
    trap_FS_FCloseFile(g_unk_00abe8b8);
    g_unk_00abe8b8 = 0;
  }
  if (g_unk_00abe8b4 != 0) {
    G_LogPrintf("ShutdownGame:\n");
    G_LogPrintf("------------------------------------------------------------\n");
    trap_FS_FCloseFile(g_unk_00abe8b4);
    g_unk_00abe8b4 = 0;
  }
  if (g_unk_00abe8bc != 0) {
    trap_FS_FCloseFile(g_unk_00abe8bc);
    g_unk_00abe8bc = 0;
  }
  G_WriteSessionData(param_1);
  GeoIP_close();
  mdx_cleanup();
  G_shrubbot_cleanup();
  return;
}

void G_UpdateCvars(void)
{
  char *tmp_pc1;
  bool tmp_b2;
  bool tmp_b3;
  bool tmp_b4;
  int tmp_i5;
  uint tmp_u6;
  int tmp_i7;
  uint8_t *tmp_pu8;
  uint32_t tmp_u9;
  long tmp_l10;
  uint8_t *tmp_pu11;
  uint8_t **tmp_ppu12;
  char local_9c [4];
  uint32_t auStack_98 [33];
  uint32_t uStack_14;
  
  uStack_14 = 0x8a11b;
  tmp_b3 = false;
  tmp_b2 = false;
  tmp_b4 = false;
  tmp_ppu12 = &gameCvarTable;
  do {
    while (*tmp_ppu12 == (uint8_t *)0x0) {
LAB_0008a470:
      tmp_ppu12 = tmp_ppu12 + 7;
      if (tmp_ppu12 == (uint8_t **)&g_unk_002ba334) goto LAB_0008a47b;
    }
    trap_Cvar_Update(*tmp_ppu12);
    tmp_pu11 = *tmp_ppu12;
    if (tmp_ppu12[4] == *(uint8_t **)(tmp_pu11 + 4)) goto LAB_0008a470;
    tmp_ppu12[4] = *(uint8_t **)(tmp_pu11 + 4);
    if ((tmp_ppu12[5] != (uint8_t *)0x0) && (((uint)tmp_ppu12[3] & 0x20) == 0)) {
      tmp_u9 = va("print \"Server:[lof] %s [lon]changed to[lof] %s\n\"",tmp_ppu12[1],tmp_pu11 + 0x10);
      trap_SendServerCommand(0xffffffff,tmp_u9);
      tmp_pu11 = *tmp_ppu12;
    }
    if (tmp_pu11 != sv_NxAC) goto LAB_0008a190;
    if ((uint)GHIDRA_FIELD(sv_NxAC, 12, 4) < 2) {
      if (GHIDRA_FIELD(sv_NxAC, 12, 4) == 1) {
        if (GHIDRA_FIELD(n_NxAC, 12, 4) != 0) goto LAB_0008a190;
        tmp_pu8 = &g_unk_0024bfa6;
        goto LAB_0008a5da;
      }
      tmp_pu8 = &g_unk_00258b23;
      if (0 < (int)GHIDRA_FIELD(n_NxAC, 12, 4)) goto LAB_0008a5da;
LAB_0008a190:
      if (tmp_pu11 != g_TDMScore) goto LAB_0008a19c;
LAB_0008a600:
      tmp_u9 = va(&g_unk_00245ee6,*(uint32_t *)(tmp_pu11 + 0xc));
      trap_SendServerCommand(0xffffffff,tmp_u9);
      tmp_pu11 = *tmp_ppu12;
      if (tmp_pu11 == mod_version) goto LAB_0008a640;
LAB_0008a1a8:
      if (tmp_pu11 != mod_build) goto LAB_0008a1b4;
LAB_0008a670:
      G_Printf("N!tmod: mod_build modification attempted\nServer stopped!\n\n");
      G_ShutdownGame(0);
      tmp_pu11 = *tmp_ppu12;
      if (tmp_pu11 == mod_url) {
LAB_0008a6a0:
        G_Printf("N!tmod: mod_url modification attempted\nServer stopped!\n\n");
        G_ShutdownGame(0);
        tmp_pu11 = *tmp_ppu12;
      }
    }
    else {
      tmp_pu8 = &g_unk_00258b23;
      if ((int)GHIDRA_FIELD(n_NxAC, 12, 4) < 1) {
        tmp_pu8 = &g_unk_0024bfa6;
      }
LAB_0008a5da:
      trap_Cvar_Set("sv_NxAC",tmp_pu8);
      tmp_pu11 = *tmp_ppu12;
      if (tmp_pu11 == g_TDMScore) {
        tmp_pu11 = g_TDMScore;
        goto LAB_0008a600;
      }
LAB_0008a19c:
      if (tmp_pu11 != mod_version) goto LAB_0008a1a8;
LAB_0008a640:
      G_Printf("N!tmod: mod_version modification attempted\nServer stopped!\n\n");
      G_ShutdownGame(0);
      tmp_pu11 = *tmp_ppu12;
      if (tmp_pu11 == mod_build) goto LAB_0008a670;
LAB_0008a1b4:
      if (tmp_pu11 == mod_url) goto LAB_0008a6a0;
    }
    tmp_u9 = GHIDRA_FIELD(g_entities, 1570216, 4);
    if (tmp_pu11 == g_soldierChargeTime) {
      g_unk_02a983e4 = (int)ROUND(g_unk_02a98458 * (float)(int)GHIDRA_FIELD(g_soldierChargeTime, 12, 4));
      tmp_b3 = true;
      g_unk_02a983e8 = (int)ROUND((float)(int)GHIDRA_FIELD(g_soldierChargeTime, 12, 4) * g_unk_02a9845c);
    }
    else if (tmp_pu11 == g_medicChargeTime) {
      g_unk_02a983ec = (int)ROUND(g_unk_02a98460 * (float)(int)GHIDRA_FIELD(g_medicChargeTime, 12, 4));
      tmp_b3 = true;
      g_unk_02a983f0 = (int)ROUND((float)(int)GHIDRA_FIELD(g_medicChargeTime, 12, 4) * g_unk_02a98464);
    }
    else if (tmp_pu11 == g_engineerChargeTime) {
      g_unk_02a983f4 = (int)ROUND(g_unk_02a98468 * (float)(int)GHIDRA_FIELD(g_engineerChargeTime, 12, 4));
      tmp_b3 = true;
      g_unk_02a983f8 = (int)ROUND((float)(int)GHIDRA_FIELD(g_engineerChargeTime, 12, 4) * g_unk_02a9846c);
    }
    else if (tmp_pu11 == g_LTChargeTime) {
      g_unk_02a983fc = (int)ROUND(g_unk_02a98470 * (float)(int)GHIDRA_FIELD(g_LTChargeTime, 12, 4));
      tmp_b3 = true;
      g_unk_02a98400 = (int)ROUND((float)(int)GHIDRA_FIELD(g_LTChargeTime, 12, 4) * g_unk_02a98474);
    }
    else if (tmp_pu11 == g_covertopsChargeTime) {
      g_unk_02a98404 = (int)ROUND(g_unk_02a98478 * (float)(int)GHIDRA_FIELD(g_covertopsChargeTime, 12, 4));
      tmp_b3 = true;
      g_unk_02a98408 = (int)ROUND((float)(int)GHIDRA_FIELD(g_covertopsChargeTime, 12, 4) * g_unk_02a9847c);
    }
    else {
      if (tmp_pu11 == match_readypercent) {
        if ((int)GHIDRA_FIELD(match_readypercent, 12, 4) < 1) {
          tmp_pu8 = &g_unk_00258b23;
        }
        else {
          if ((int)GHIDRA_FIELD(match_readypercent, 12, 4) < 0x65) goto LAB_0008a340;
          tmp_pu8 = &g_unk_002496df;
        }
        goto LAB_0008a7ec;
      }
      if ((tmp_pu11 == g_warmup) && (GHIDRA_FIELD(g_gamestate, 12, 4) != 0)) {
        tmp_i5 = 11000;
        if (9 < (int)GHIDRA_FIELD(g_warmup, 12, 4)) {
          tmp_i5 = (GHIDRA_FIELD(g_warmup, 12, 4) + 1) * 1000;
        }
        g_unk_00abe8ac = tmp_i5 + g_unk_00abe908;
        tmp_u9 = va("%i",g_unk_00abe8ac);
        trap_SetConfigstring(5,tmp_u9);
        tmp_pu11 = *tmp_ppu12;
      }
      else if (tmp_pu11 == g_gametype) {
        trap_Cvar_LatchedVariableStringBuffer("g_gametype",local_9c,0x20);
        tmp_l10 = strtol(local_9c,(char **)0x0,10);
        if ((tmp_l10 == 4) && (GHIDRA_FIELD(g_gametype, 12, 4) != 4)) {
          tmp_i5 = G_MapIsValidCampaignStartMap();
          if (tmp_i5 == 0) {
            tmp_i5 = GHIDRA_FIELD(g_gametype, 12, 4);
            if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) {
              tmp_i5 = (-(uint)((tmp_u9 & 1) == 0) & 0xfffffffd) + 5;
            }
            G_Printf("Map \'%s\' isn\'t a valid campaign start map, resetting game type to \'%i\'\n"
                     ,&g_unk_00abe8c0,tmp_i5);
            tmp_u9 = va("%i",tmp_i5);
            trap_Cvar_Set("g_gametype",tmp_u9);
          }
          goto LAB_0008a470;
        }
        if ((g_unk_02a983b8 == 0) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
          if ((((GHIDRA_FIELD(g_gametype, 12, 4) & 0xfffffffb) == 2) || (GHIDRA_FIELD(g_gametype, 12, 4) == 4)) &&
             ((tmp_u9 & 1) != 0)) {
            tmp_i5 = 5;
          }
          else {
            if (GHIDRA_FIELD(g_gametype, 12, 4) == 3) {
              if ((tmp_u9 & 2) == 0) {
                tmp_pu11 = *tmp_ppu12;
                goto LAB_0008a340;
              }
            }
            else if ((GHIDRA_FIELD(g_gametype, 12, 4) != 5) || ((tmp_u9 & 8) == 0)) goto LAB_0008a9df;
            tmp_i5 = (-(uint)((tmp_u9 & 1) == 0) & 0xfffffffd) + 5;
          }
          g_unk_02a983b8 = 1;
          trap_SendServerCommand
                    (0xffffffff,"print \"Invalid gametype was specified, Restarting\n\"");
          tmp_u9 = va("wait 2 ; g_gametype %i ; map_restart 10 0\n",tmp_i5);
          trap_SendConsoleCommand(2,tmp_u9);
          tmp_pu11 = *tmp_ppu12;
        }
        else {
LAB_0008a9df:
          tmp_pu11 = *tmp_ppu12;
        }
      }
      else if (tmp_pu11 == pmove_msec) {
        if ((int)GHIDRA_FIELD(pmove_msec, 12, 4) < 8) {
          tmp_pu8 = &g_unk_00261bbb;
        }
        else {
          if ((int)GHIDRA_FIELD(pmove_msec, 12, 4) < 0x22) goto LAB_0008a340;
          tmp_pu8 = &g_unk_0024992b;
        }
LAB_0008a7ec:
        trap_Cvar_Set(tmp_ppu12[1],tmp_pu8);
        tmp_pu11 = *tmp_ppu12;
      }
      else {
        tmp_i5 = nitmod_IsSimpleCSVar(tmp_pu11);
        if (tmp_i5 == 0) {
          tmp_pu11 = *tmp_ppu12;
          if (((((((((((((((((((tmp_pu11 == team_panzerRestriction || tmp_pu11 == team_maxPanzers) ||
                              tmp_pu11 == team_maxMG42s) || tmp_pu11 == team_maxFlamers) ||
                            tmp_pu11 == team_maxMortars) || tmp_pu11 == team_maxriflegrenades) ||
                          tmp_pu11 == g_adrenaline) || tmp_pu11 == team_maxSoldiers) ||
                        tmp_pu11 == team_maxMedics) || tmp_pu11 == team_maxEngineers) ||
                      tmp_pu11 == team_maxFieldops) || tmp_pu11 == team_maxCovertops) ||
                    tmp_pu11 == g_weapons) || tmp_pu11 == jp_keepAwards) || tmp_pu11 == g_DJHeight) ||
                 tmp_pu11 == g_missileCams) || tmp_pu11 == g_TDMOptions) || tmp_pu11 == g_DMOptions) ||
               tmp_pu11 == g_gravity) || (tmp_pu11 == g_resetXPMapCount)) {
            nitmod_SendNCS(0);
            tmp_pu11 = *tmp_ppu12;
          }
          else if ((tmp_pu11 == lua_modules) || (tmp_pu11 == lua_allowedModules)) {
            G_LuaShutdown();
            goto LAB_0008a9df;
          }
        }
        else {
          nitmod_SimpleCS(0);
          tmp_pu11 = *tmp_ppu12;
        }
      }
    }
LAB_0008a340:
    if (((((((((((((((((((((((tmp_pu11 != vote_allow_comp && tmp_pu11 != vote_allow_gametype) &&
                            tmp_pu11 != vote_allow_kick) && tmp_pu11 != vote_allow_map) &&
                          tmp_pu11 != vote_allow_matchreset) && tmp_pu11 != vote_allow_mutespecs) &&
                        tmp_pu11 != vote_allow_nextmap) && tmp_pu11 != vote_allow_pub) &&
                      tmp_pu11 != vote_allow_referee) && tmp_pu11 != vote_allow_shuffleteams) &&
                    tmp_pu11 != vote_allow_shuffleteams_norestart) && tmp_pu11 != vote_allow_swapteams
                   ) && tmp_pu11 != vote_allow_swapteamsrestart) &&
                 tmp_pu11 != vote_allow_friendlyfire) && tmp_pu11 != vote_allow_timelimit) &&
               tmp_pu11 != vote_allow_warmupdamage) && tmp_pu11 != vote_allow_antilag) &&
             tmp_pu11 != vote_allow_balancedteams) && tmp_pu11 != vote_allow_muting) &&
           tmp_pu11 != vote_allow_surrender) && tmp_pu11 != vote_allow_restartcampaign) &&
         tmp_pu11 != vote_allow_nextcampaign) && tmp_pu11 != vote_allow_poll) &&
       (tmp_pu11 != vote_allow_maprestart)) {
      tmp_i5 = G_checkServerToggle(tmp_pu11);
      tmp_b4 = tmp_b4 || tmp_i5 != 0;
      goto LAB_0008a470;
    }
    tmp_ppu12 = tmp_ppu12 + 7;
    tmp_b2 = true;
  } while (tmp_ppu12 != (uint8_t **)&g_unk_002ba334);
LAB_0008a47b:
  if (tmp_b2) {
    G_voteFlags();
  }
  if (tmp_b4) {
    tmp_u9 = va(&g_unk_00245ee9,g_unk_02a99a80);
    trap_SetConfigstring(0x1d,tmp_u9);
  }
  if (tmp_b3) {
    nitmod_SendChargeTimes(0);
  }
  if (0 < g_unk_02ad4198) {
    tmp_i5 = 0;
    tmp_pu8 = &g_unk_02ac4198;
    do {
      while( true ) {
        tmp_u6 = 0;
        do {
          tmp_pc1 = local_9c + tmp_u6;
          tmp_pc1[0] = '\0';
          tmp_pc1[1] = '\0';
          tmp_pc1[2] = '\0';
          tmp_pc1[3] = '\0';
          *(uint32_t *)((int)auStack_98 + tmp_u6) = 0;
          tmp_u6 = tmp_u6 + 8;
        } while (tmp_u6 < 0x80);
        trap_Cvar_VariableStringBuffer(tmp_pu8,local_9c,0x80);
        tmp_i7 = strcmp(tmp_pu8 + 0x100,local_9c);
        if (tmp_i7 != 0) break;
        tmp_i5 = tmp_i5 + 1;
        tmp_pu8 = tmp_pu8 + 0x200;
        if (g_unk_02ad4198 <= tmp_i5) {
          return;
        }
      }
      tmp_i5 = tmp_i5 + 1;
      trap_Cvar_Set(tmp_pu8,tmp_pu8 + 0x100);
      tmp_pu8 = tmp_pu8 + 0x200;
    } while (tmp_i5 < g_unk_02ad4198);
  }
  return;
}

void G_wipeCvars(void)
{
  uint8_t **tmp_ppu1;
  uint8_t **tmp_ppu2;
  
  tmp_ppu1 = &gameCvarTable;
  do {
    while ((*tmp_ppu1 != (uint8_t *)0x0 && (tmp_ppu1[6] != (uint8_t *)0x0))) {
      tmp_ppu2 = tmp_ppu1 + 7;
      G_Printf("set %s %s\n",tmp_ppu1[1],tmp_ppu1[2]);
      trap_Cvar_Set(tmp_ppu1[1],tmp_ppu1[2]);
      tmp_ppu1 = tmp_ppu2;
      if (tmp_ppu2 == (uint8_t **)&g_unk_002ba334) goto LAB_0008ac23;
    }
    tmp_ppu1 = tmp_ppu1 + 7;
  } while (tmp_ppu1 != (uint8_t **)&g_unk_002ba334);
LAB_0008ac23:
  G_UpdateCvars();
  return;
}

void G_CrashLogPrintf(char *param_1)
{
  char *__s;
  uint tmp_u1;
  uint tmp_u2;
  uint *tmp_pu3;
  uint *tmp_pu4;
  int tmp_i5;
  char acStack_40f [3];
  uint local_40c [255];
  uint32_t uStack_10;
  
  uStack_10 = 0x8baed;
  tmp_i5 = (g_unk_00abe908 / 1000) % 0x3c;
  Com_sprintf(local_40c,0x400,"%i:%i%i ",(g_unk_00abe908 / 1000) / 0x3c,tmp_i5 / 10,tmp_i5 % 10);
  tmp_pu4 = local_40c;
  do {
    tmp_pu3 = tmp_pu4;
    tmp_u1 = *tmp_pu3 + 0xfefefeff & ~*tmp_pu3;
    tmp_u2 = tmp_u1 & 0x80808080;
    tmp_pu4 = tmp_pu3 + 1;
  } while (tmp_u2 == 0);
  if ((tmp_u1 & 0x8080) == 0) {
    tmp_pu4 = (uint *)((int)tmp_pu3 + 6);
    tmp_u2 = tmp_u2 >> 0x10;
  }
  tmp_i5 = (int)tmp_pu4 + ((-3 - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) - (int)local_40c);
  __s = (char *)((int)local_40c + tmp_i5);
  vsnprintf(__s,0x400 - tmp_i5,param_1,&stack0x00000008);
  if (GHIDRA_FIELD(g_dedicated, 12, 4) != 0) {
    G_Printf(&g_unk_0024e6e9,__s);
  }
  tmp_pu4 = local_40c;
  if (g_unk_00abe8b8 != 0) {
    do {
      tmp_pu3 = tmp_pu4;
      tmp_u1 = *tmp_pu3 + 0xfefefeff & ~*tmp_pu3;
      tmp_u2 = tmp_u1 & 0x80808080;
      tmp_pu4 = tmp_pu3 + 1;
    } while (tmp_u2 == 0);
    if ((tmp_u1 & 0x8080) == 0) {
      tmp_pu4 = (uint *)((int)tmp_pu3 + 6);
      tmp_u2 = tmp_u2 >> 0x10;
    }
    trap_FS_Write(local_40c,
                  (int)tmp_pu4 + ((-3 - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) - (int)local_40c),
                  g_unk_00abe8b8);
    return;
  }
  return;
}

void G_RunThink(int *param_1)
{
  int tmp_i1;
  int tmp_i2;
  void *tmp_pc3;
  char *tmp_pc4;
  
  tmp_i2 = g_unk_00abe908;
  if ((g_unk_02a99a78 != 0) &&
     ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= ((int)(param_1 + -0x24f928) >> 9) * -0x55555555)) {
    tmp_i1 = param_1[0xa7];
    if (g_unk_00abe908 < tmp_i1) {
      tmp_pc4 = strstr((char *)param_1[0x69],"DPRINTF_");
      if (tmp_pc4 == (char *)0x0) {
        param_1[0xa7] = (tmp_i2 - g_unk_00abe910) + tmp_i1;
      }
    }
  }
  if (0x3f < *param_1) {
    G_Script_ScriptRun(param_1);
  }
  if ((0 < param_1[0xa7]) && (param_1[0xa7] <= g_unk_00abe908)) {
    param_1[0xa7] = 0;
    tmp_pc3 = (void *)param_1[0xa9];
    if (tmp_pc3 == (void *)0x0) {
      G_Error("NULL ent->think");
      tmp_pc3 = (void *)param_1[0xa9];
    }
    (*tmp_pc3)(param_1);
  }
  return;
}

uint32_t G_PositionEntityOnTag(int param_1,int param_2,uint32_t param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  uint32_t tmp_u5;
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
  
  AnglesToAxis(param_2 + 0x174,&local_60);
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_2 + 0x168);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_2 + 0x16c);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_2 + 0x170);
  tmp_i4 = trap_GetTag(0xffffffff,*(uint32_t *)(param_2 + 0x498),param_3,&local_3c);
  tmp_u5 = 0;
  if (tmp_i4 != 0) {
    tmp_f3 = local_54 * local_38 + local_60 * local_3c + *(float *)(param_1 + 0x168) +
            local_48 * local_34;
    tmp_f2 = local_50 * local_38 + local_5c * local_3c + *(float *)(param_1 + 0x16c) +
            local_44 * local_34;
    tmp_f1 = local_38 * local_4c + local_3c * local_58 + *(float *)(param_1 + 0x170) +
            local_34 * local_40;
    *(float *)(param_1 + 0x168) = tmp_f3;
    *(float *)(param_1 + 0x16c) = tmp_f2;
    *(float *)(param_1 + 0x170) = tmp_f1;
    if ((*(int *)(param_1 + 400) != 0) && ((*(byte *)(param_1 + 9) & 0x80) != 0)) {
      *(float *)(param_1 + 0x168) = tmp_f3 + 3.296875;
      *(float *)(param_1 + 0x16c) = tmp_f2 - 2.53125;
      *(float *)(param_1 + 0x170) = tmp_f1 + 30.953125;
    }
    G_SetOrigin(param_1,param_1 + 0x168);
    if (((*(int *)(param_1 + 0x120) != 0) && (*(int *)(param_1 + 400) == 0)) &&
       (tmp_i4 = VectorCompare(param_1 + 0x4d8,param_1 + 0x168), tmp_i4 == 0)) {
      trap_LinkEntity(param_1);
    }
    tmp_u5 = 1;
  }
  return tmp_u5;
}

uint32_t G_missileCamera(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  
  if (GHIDRA_FIELD(g_missileCams, 12, 4) == 0) {
    return 0;
  }
  if (*(int *)(g_entities + *(int *)(param_1 + 0x180) * 0x600 + 400) == 0) {
    return 0;
  }
  if (*(int *)(*(int *)(g_entities + *(int *)(param_1 + 0x180) * 0x600 + 400) + 0x5ac) != 2) {
    return 0;
  }
  if (*(int *)(param_1 + 0x2f0) == 0) {
    return 0;
  }
  switch(*(uint32_t *)(*(int *)(param_1 + 0x2f0) + 0xe8)) {
  case 5:
    if ((GHIDRA_FIELD(g_missileCams, 12, 4) & 1) == 0) {
      return 0;
    }
    goto LAB_0008d7a7;
  default:
    return 0;
  case 0x16:
  case 0x17:
  case 0x24:
  case 0x25:
    tmp_u2 = GHIDRA_FIELD(g_missileCams, 12, 4) & 4;
    break;
  case 0x2a:
    tmp_u2 = GHIDRA_FIELD(g_missileCams, 12, 4) & 2;
  }
  tmp_u4 = 0;
  if (tmp_u2 != 0) {
LAB_0008d7a7:
    tmp_i3 = *(int *)(param_1 + 0x180) * 0x600;
    *(uint32_t *)(param_1 + 0x5c) = *(uint32_t *)(g_entities + tmp_i3 + 0x168);
    *(uint32_t *)(param_1 + 0x60) = *(uint32_t *)(g_entities + tmp_i3 + 0x16c);
    *(uint32_t *)(param_1 + 100) = *(uint32_t *)(g_entities + tmp_i3 + 0x170);
    *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(g_entities + tmp_i3 + 0x168);
    *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(g_entities + tmp_i3 + 0x16c);
    *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(g_entities + tmp_i3 + 0x170);
    G_SetOrigin(param_1,tmp_i3 + 0x93e608);
    tmp_i1 = *(int *)(param_1 + 0x2f0);
    *(uint32_t *)(param_1 + 0x68) = *(uint32_t *)(tmp_i1 + 0x168);
    *(uint32_t *)(param_1 + 0x6c) = *(uint32_t *)(tmp_i1 + 0x16c);
    *(uint32_t *)(param_1 + 0x70) = *(uint32_t *)(tmp_i1 + 0x170);
    *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(g_entities + tmp_i3 + 0x168);
    *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(g_entities + tmp_i3 + 0x16c);
    *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(g_entities + tmp_i3 + 0x170);
    trap_LinkEntity(param_1);
    tmp_u4 = 1;
  }
  return tmp_u4;
}

void G_DrawEntBBox(uint32_t *param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  tmp_i2 = G_EntitiesFree();
  if (0x3f < tmp_i2) {
    if ((g_debugHitboxes[0x10] == '\0') ||
       (tmp_i2 = Q_isalpha((int)g_debugHitboxes[0x10]), tmp_i2 == 0)) {
      switch(param_1[1]) {
      case 0:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 0xe) {
          return;
        }
        break;
      case 1:
      case 0x26:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 3) {
          return;
        }
        break;
      case 2:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 6) {
          return;
        }
        break;
      case 3:
      case 0x22:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 4) {
          return;
        }
        break;
      case 4:
      case 0x1e:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 7) {
          return;
        }
        break;
      default:
        goto _L1487;
      case 8:
      case 9:
      case 0xb:
      case 0xc:
      case 0x2b:
      case 0x2c:
      case 0x2d:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 10) {
          return;
        }
        break;
      case 0xe:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 5) {
          return;
        }
        break;
      case 0xf:
      case 0x11:
      case 0x13:
      case 0x1b:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 0xc) {
          return;
        }
        break;
      case 0x12:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 0xd) {
          return;
        }
        break;
      case 0x1f:
      case 0x20:
      case 0x21:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 9) {
          return;
        }
        break;
      case 0x29:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 8) {
          return;
        }
        break;
      case 0x2f:
      case 0x30:
      case 0x31:
      case 0x32:
        if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) != 0xb) {
          return;
        }
      }
      local_24 = param_1[0x50];
      tmp_u1 = *param_1;
      local_20 = param_1[0x51];
      local_1c = param_1[0x52];
      local_18 = param_1[0x4d];
      local_14 = param_1[0x4e];
      local_10 = param_1[0x4f];
      tmp_u3 = tv(0,0x3f800000,0);
      G_RailBox(param_1 + 0x5a,&local_18,&local_24,tmp_u3,tmp_u1);
    }
    else if (((char *)param_1[0x69] != (char *)0x0) &&
            (tmp_i2 = strcmp((char *)param_1[0x69],g_debugHitboxes + 0x10), tmp_i2 == 0)) {
      tmp_u1 = *param_1;
      tmp_u3 = tv(0x3f000000,0,0x3f000000);
      G_RailBox(param_1 + 0x5a,param_1 + 0x4d,param_1 + 0x50,tmp_u3,tmp_u1);
    }
  }
_L1487:
  return;
}

void G_RunEntity_part_9(int *param_1,int param_2)
{
  int tmp_i1;
  float tmp_f2;
  uint tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  char *tmp_pc6;
  void *tmp_pc7;
  int tmp_i8;
  uint *tmp_pu9;
  uint *tmp_pu10;
  
  if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) == 0) {
    tmp_pu10 = (uint *)(g_debugHitboxes + 0x10);
    do {
      tmp_pu9 = tmp_pu10;
      tmp_u3 = *tmp_pu9 + 0xfefefeff & ~*tmp_pu9;
      tmp_u4 = tmp_u3 & 0x80808080;
      tmp_pu10 = tmp_pu9 + 1;
    } while (tmp_u4 == 0);
    if ((tmp_u3 & 0x8080) == 0) {
      tmp_pu10 = (uint *)((int)tmp_pu9 + 6);
      tmp_u4 = tmp_u4 >> 0x10;
    }
    if (2 < (int)tmp_pu10 + (-0x2e580b3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4))) goto LAB_0008db6f;
  }
  else {
LAB_0008db6f:
    G_DrawEntBBox(param_1);
  }
  tmp_i5 = param_1[0x110];
  if (tmp_i5 == 0) {
    if ((*(byte *)((int)param_1 + 10) & 2) != 0) {
      G_TagLinkEntity(param_1,param_2);
    }
  }
  else {
    if ((*(int *)(tmp_i5 + 0x5e4) == 0) && (*(int *)(tmp_i5 + 0x194) != 0)) {
      G_RunEntity_part_9();
      tmp_i5 = param_1[0x110];
      if (tmp_i5 == 0) goto LAB_0008dbb8;
    }
    tmp_i5 = G_PositionEntityOnTag(param_1,tmp_i5,param_1 + 0x100);
    if ((tmp_i5 != 0) && (param_1[100] == 0)) {
      if (param_1[0x3d] == 0) {
        BG_EvaluateTrajectory(param_1 + 0xc,g_unk_00abe908,param_1 + 0x5d,1,param_1[0x44]);
        tmp_i5 = param_1[0x110];
        param_1[0x5d] = (int)((float)param_1[0x5d] + *(float *)(tmp_i5 + 0x174));
        param_1[0x5e] = (int)((float)param_1[0x5e] + *(float *)(tmp_i5 + 0x178));
        param_1[0x5f] = (int)((float)param_1[0x5f] + *(float *)(tmp_i5 + 0x17c));
      }
      else {
        BG_EvaluateTrajectory(param_1 + 0xc,g_unk_00abe908,param_1 + 0x5d,1,param_1[0x44]);
      }
    }
  }
LAB_0008dbb8:
  param_1[0x136] = param_1[0x5a];
  tmp_i8 = ((int)(param_1 + -0x24f928) >> 9) * -0x55555555;
  param_1[0x137] = param_1[0x5b];
  tmp_i1 = g_unk_00abe900;
  tmp_i5 = tmp_i8 - g_unk_00abe900;
  param_1[0x138] = param_1[0x5c];
  if (tmp_i5 == 0 || tmp_i8 < tmp_i1) {
LAB_0008dc0e:
    tmp_i5 = param_1[1];
  }
  else {
    if ((*(byte *)((int)param_1 + 0x1b3) & 1) != 0) {
      param_1[2] = param_1[2] | 0x40;
      goto LAB_0008dc0e;
    }
    tmp_i5 = param_1[1];
    param_1[2] = param_1[2] & 0xffffffbf;
  }
  tmp_i1 = g_unk_00abe908;
  if (tmp_i5 == 0x39) {
    tmp_i5 = G_missileCamera(param_1);
    if (tmp_i5 != 0) {
      return;
    }
LAB_0008dec8:
    G_FreeEntity(param_1);
    return;
  }
  if (g_unk_00abe908 - param_1[0x70] < 0x12d) {
    if (param_1[0x71] != 0) {
      return;
    }
  }
  else {
    if (param_1[0x2e] != 0) {
      param_1[0x2e] = 0;
    }
    if (param_1[0x71] != 0) goto LAB_0008dec8;
    if (param_1[0x72] != 0) {
      param_1[0x72] = 0;
      trap_UnlinkEntity(param_1);
      param_1[1] = 10;
      param_1[0x4a] = 1;
      param_1[0x179] = 1;
      return;
    }
  }
  if (tmp_i5 == 0x20) {
    if (param_1[0x48] == 0) goto LAB_0008dee0;
LAB_0008df12:
    if (param_1[0x73] == 0) {
      if ((tmp_i5 == 0x1b) || (tmp_i5 == 4)) {
        G_RunMover(param_1);
      }
      else if ((int)(param_1 + -0x24f928) < 0x18000) {
        G_RunClient(param_1);
      }
      else {
        if ((tmp_i5 - 0x31U < 2) && (param_1[0x99] != 0)) {
          *(int *)(param_1[0x99] + 0xfc) = param_1[0xb2];
          *(int *)(param_1[0x99] + 0x100) = param_1[0xb9];
        }
        if ((((g_unk_02a99a78 != 0) && ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= tmp_i8)) &&
            (tmp_i5 = param_1[0xa7], tmp_i1 < tmp_i5)) &&
           (tmp_pc6 = strstr((char *)param_1[0x69],"DPRINTF_"), tmp_pc6 == (char *)0x0)) {
          param_1[0xa7] = tmp_i5 + (tmp_i1 - g_unk_00abe910);
        }
        if (0x3f < *param_1) {
          G_Script_ScriptRun(param_1);
        }
        if ((0 < param_1[0xa7]) && (param_1[0xa7] <= g_unk_00abe908)) {
          tmp_pc7 = (void *)param_1[0xa9];
          param_1[0xa7] = 0;
          if (tmp_pc7 == (void *)0x0) {
            G_Error("NULL ent->think");
            tmp_pc7 = (void *)param_1[0xa9];
          }
          (*tmp_pc7)(param_1);
        }
      }
      goto LAB_0008dccb;
    }
  }
  else {
    if (param_1[0x116] - 1U < 2) {
      if (*param_1 < 0x40) {
        return;
      }
      G_Script_ScriptRun(param_1);
      return;
    }
    if (param_1[0x48] == 0) {
LAB_0008dee0:
      if (param_1[0x6b] != 0) {
        return;
      }
    }
    if ((tmp_i5 == 0x1a || tmp_i5 == 3) || (tmp_i5 - 0x14U < 5)) {
      if (g_unk_02a99a78 == 0) {
        G_RunMissile(param_1);
        return;
      }
      param_1[4] = param_1[4] + (tmp_i1 - g_unk_00abe910);
      if (param_1[0xb7] == 0x15) {
        param_1[0x43] = param_1[0x43] + (g_unk_00abe908 - g_unk_00abe910);
      }
      tmp_i5 = g_unk_00abe908;
      if ((((g_unk_02a99a78 != 0) && ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= tmp_i8)) &&
          (tmp_i1 = param_1[0xa7], g_unk_00abe908 < tmp_i1)) &&
         (tmp_pc6 = strstr((char *)param_1[0x69],"DPRINTF_"), tmp_pc6 == (char *)0x0)) {
        param_1[0xa7] = tmp_i1 + (tmp_i5 - g_unk_00abe910);
      }
      if (0x3f < *param_1) {
        G_Script_ScriptRun(param_1);
      }
      if (param_1[0xa7] < 1) {
        return;
      }
      if (g_unk_00abe908 < param_1[0xa7]) {
        return;
      }
      param_1[0xa7] = 0;
      tmp_pc7 = (void *)param_1[0xa9];
      if (tmp_pc7 == (void *)0x0) {
        G_Error("NULL ent->think");
        tmp_pc7 = (void *)param_1[0xa9];
      }
      (*tmp_pc7)(param_1);
      return;
    }
    if (tmp_i5 == 0x19) {
      G_RunFlamechunk(param_1);
      goto LAB_0008dccb;
    }
    if (tmp_i5 != 2) goto LAB_0008df12;
  }
  G_RunItem(param_1);
LAB_0008dccb:
  tmp_f2 = 1000.0 / (float)param_2;
  param_1[0x66] = (int)(((float)param_1[0x5a] - (float)param_1[0x136]) * tmp_f2);
  param_1[0x67] = (int)(((float)param_1[0x5b] - (float)param_1[0x137]) * tmp_f2);
  param_1[0x68] = (int)(((float)param_1[0x5c] - (float)param_1[0x138]) * tmp_f2);
  return;
}

void G_TagLinkEntity(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  uint16_t *tmp_pu5;
  int tmp_i6;
  uint32_t tmp_u7;
  int tmp_i8;
  uint tmp_u9;
  uint tmp_u10;
  bool tmp_b11;
  float tmp_f12;
  float tmp_f13;
  int local_74;
  uint32_t local_5c;
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
  float local_28;
  float local_24;
  float local_20;
  
  local_3c = 0.0;
  local_38 = 0.0;
  tmp_i6 = *(int *)(param_1 + 0xf0);
  local_40 = 0.0;
  if (g_unk_00abe908 <= *(int *)(param_1 + 0x49c)) {
    return;
  }
  if ((*(int *)(g_entities + tmp_i6 * 0x600 + 0x5e4) == 0) &&
     (*(int *)(g_entities + tmp_i6 * 0x600 + 0x194) != 0)) {
    G_RunEntity_part_9();
  }
  tmp_i3 = tmp_i6 * 0x600;
  if ((g_entities[tmp_i3 + 10] & 2) == 0) {
    if (*(int *)(g_entities + tmp_i3 + 0xc) != 0xd) {
LAB_0008e1d6:
      tmp_u9 = 0x24;
      *(uint32_t *)(param_1 + 0x4b8) = 0;
      tmp_pu5 = (uint16_t *)(param_1 + 0xc);
      tmp_b11 = ((uint)tmp_pu5 & 1) != 0;
      if (tmp_b11) {
        *(uint8_t *)(param_1 + 0xc) = 0;
        tmp_pu5 = (uint16_t *)(param_1 + 0xd);
        tmp_u9 = 0x23;
      }
      if (((uint)tmp_pu5 & 2) != 0) {
        *tmp_pu5 = 0;
        tmp_u9 = tmp_u9 - 2;
        tmp_pu5 = tmp_pu5 + 1;
      }
      tmp_u10 = 0;
      do {
        *(uint32_t *)((int)tmp_pu5 + tmp_u10) = 0;
        *(uint32_t *)((int)tmp_pu5 + tmp_u10 + 4) = 0;
        tmp_u10 = tmp_u10 + 8;
      } while (tmp_u10 < (tmp_u9 & 0xfffffff8));
      tmp_pu4 = (uint32_t *)((int)tmp_pu5 + tmp_u10);
      if ((tmp_u9 & 4) != 0) {
        *tmp_pu4 = 0;
        tmp_pu4 = tmp_pu4 + 1;
      }
      if ((tmp_u9 & 2) != 0) {
        *(uint16_t *)tmp_pu4 = 0;
        tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
      }
      if (tmp_b11) {
        *(uint8_t *)tmp_pu4 = 0;
      }
      tmp_pu5 = (uint16_t *)(param_1 + 0x30);
      tmp_u9 = 0x24;
      tmp_b11 = ((uint)tmp_pu5 & 1) != 0;
      if (tmp_b11) {
        *(uint8_t *)(param_1 + 0x30) = 0;
        tmp_pu5 = (uint16_t *)(param_1 + 0x31);
        tmp_u9 = 0x23;
      }
      if (((uint)tmp_pu5 & 2) != 0) {
        *tmp_pu5 = 0;
        tmp_u9 = tmp_u9 - 2;
        tmp_pu5 = tmp_pu5 + 1;
      }
      tmp_u10 = 0;
      do {
        *(uint32_t *)((int)tmp_pu5 + tmp_u10) = 0;
        *(uint32_t *)((int)tmp_pu5 + tmp_u10 + 4) = 0;
        tmp_u10 = tmp_u10 + 8;
      } while (tmp_u10 < (tmp_u9 & 0xfffffff8));
      tmp_pu4 = (uint32_t *)((int)tmp_pu5 + tmp_u10);
      if ((tmp_u9 & 4) != 0) {
        *tmp_pu4 = 0;
        tmp_pu4 = tmp_pu4 + 1;
      }
      if ((tmp_u9 & 2) != 0) {
        *(uint16_t *)tmp_pu4 = 0;
        tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
      }
      if (tmp_b11) {
        *(uint8_t *)tmp_pu4 = 0;
      }
      *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x168);
      *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x16c);
      *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 0x170);
      *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x174);
      *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x178);
      *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x17c);
      goto LAB_0008e4ab;
    }
    tmp_i8 = BG_GetSplineData(*(uint32_t *)(g_entities + tmp_i3 + 0x110),param_1 + 0x4b4);
    *(int *)(param_1 + 0x4a0) = tmp_i8;
    if (tmp_i8 == 0) {
      return;
    }
    if (*(int *)(g_entities + tmp_i3 + 0x14) == 0) {
      *(uint32_t *)(param_1 + 0x4b0) = 0;
      tmp_f1 = 0.0;
LAB_0008e7ec:
      local_74 = *(int *)(param_1 + 0x4b4);
      if (local_74 == 0) {
        tmp_f1 = tmp_f1 * 16.0;
        tmp_f12 = floorf(tmp_f1);
        tmp_i3 = (int)ROUND(tmp_f12);
      }
      else {
        tmp_f12 = 1.0 - tmp_f1;
        tmp_f1 = tmp_f12 * 16.0;
        tmp_f13 = floorf(tmp_f1);
        tmp_i3 = (int)ROUND(tmp_f13);
LAB_0008e65d:
        *(float *)(param_1 + 0x4b0) = tmp_f12;
      }
      if (0xf < tmp_i3) goto LAB_0008e66e;
LAB_0008e7af:
      tmp_f1 = (tmp_f1 - (float)tmp_i3) * *(float *)(tmp_i8 + 0x1e0 + tmp_i3 * 0x1c);
    }
    else {
      tmp_f1 = (float)(g_unk_00abe908 - *(int *)(g_entities + tmp_i3 + 0x10)) /
              (float)*(int *)(g_entities + tmp_i3 + 0x14);
      if (tmp_f1 < 0.0) {
        local_74 = *(int *)(param_1 + 0x4b4);
        *(uint32_t *)(param_1 + 0x4b0) = 0;
        if (local_74 != 0) {
          tmp_f1 = 16.0;
          tmp_i3 = 0x10;
          tmp_f12 = 1.0;
          goto LAB_0008e65d;
        }
        tmp_i3 = 0;
        tmp_f1 = 0.0;
        goto LAB_0008e7af;
      }
      if (tmp_f1 <= 1.0) {
        *(float *)(param_1 + 0x4b0) = tmp_f1;
        goto LAB_0008e7ec;
      }
      local_74 = *(int *)(param_1 + 0x4b4);
      *(uint32_t *)(param_1 + 0x4b0) = 0x3f800000;
      if (local_74 != 0) {
        tmp_f1 = 0.0;
        tmp_i3 = 0;
        tmp_f12 = tmp_f1;
        goto LAB_0008e65d;
      }
LAB_0008e66e:
      tmp_f1 = *(float *)(tmp_i8 + 900);
      tmp_i3 = 0xf;
    }
    tmp_i3 = tmp_i3 * 0x1c;
    local_28 = *(float *)(tmp_i8 + 0x1d4 + tmp_i3) * tmp_f1 + *(float *)(tmp_i8 + 0x1c8 + tmp_i3);
    local_24 = *(float *)(tmp_i8 + 0x1d8 + tmp_i3) * tmp_f1 + *(float *)(tmp_i8 + 0x1cc + tmp_i3);
    local_20 = tmp_f1 * *(float *)(tmp_i8 + 0x1dc + tmp_i3) + *(float *)(tmp_i8 + 0x1d0 + tmp_i3);
    if (*(float *)(g_entities + tmp_i6 * 0x600 + 0x3c) != 0.0) {
      BG_LinearPathOrigin2
                (*(float *)(g_entities + tmp_i6 * 0x600 + 0x3c),param_1 + 0x4a0,param_1 + 0x4b0,
                 &local_28,local_74);
    }
    tmp_f1 = *(float *)(param_1 + 0x80);
    tmp_f12 = local_28;
    tmp_f13 = local_20;
    tmp_f2 = local_24;
    local_40 = local_28;
    local_3c = local_24;
    local_38 = local_20;
    if (tmp_f1 != 0.0) {
      tmp_u7 = *(uint32_t *)(param_1 + 0x4b4);
LAB_0008e578:
      tmp_f13 = local_20;
      tmp_f2 = local_24;
      tmp_f12 = local_28;
      local_40 = local_28;
      local_3c = local_24;
      local_38 = local_20;
      BG_LinearPathOrigin2(tmp_f1,param_1 + 0x4a0,param_1 + 0x4b0,&local_28,tmp_u7);
      tmp_f1 = *(float *)(param_1 + 0x80);
    }
  }
  else {
    if (*(int *)(g_entities + tmp_i3 + 0x4b8) == 0) goto LAB_0008e1d6;
    local_40 = *(float *)(g_entities + tmp_i3 + 0x4a4);
    local_3c = *(float *)(g_entities + tmp_i3 + 0x4a8);
    local_38 = *(float *)(g_entities + tmp_i3 + 0x4ac);
    tmp_u7 = *(uint32_t *)(g_entities + tmp_i3 + 0x4b4);
    *(uint32_t *)(param_1 + 0x4b4) = tmp_u7;
    *(uint32_t *)(param_1 + 0x4b0) = *(uint32_t *)(g_entities + tmp_i3 + 0x4b0);
    tmp_f1 = *(float *)(param_1 + 0x80);
    *(uint32_t *)(param_1 + 0x4a0) = *(uint32_t *)(g_entities + tmp_i3 + 0x4a0);
    tmp_f12 = local_40;
    tmp_f13 = local_38;
    tmp_f2 = local_3c;
    local_28 = local_40;
    local_24 = local_3c;
    local_20 = local_38;
    if (tmp_f1 != 0.0) goto LAB_0008e578;
  }
  *(float *)(param_1 + 0x4a4) = local_28;
  *(float *)(param_1 + 0x4a8) = local_24;
  *(float *)(param_1 + 0x4ac) = local_20;
  if (tmp_f1 < 0.0) {
    local_28 = local_28 - tmp_f12;
    local_24 = local_24 - tmp_f2;
    local_20 = local_20 - tmp_f13;
LAB_0008e3a6:
    vectoangles(&local_28,&local_34);
  }
  else {
    if (0.0 < tmp_f1) {
      local_28 = tmp_f12 - local_28;
      local_24 = tmp_f2 - local_24;
      local_20 = tmp_f13 - local_20;
      goto LAB_0008e3a6;
    }
    local_40 = vec3_origin;
    local_3c = g_unk_008277c4;
    local_38 = g_unk_008277c8;
    tmp_f13 = g_unk_008277c8;
    tmp_f2 = g_unk_008277c4;
    tmp_f12 = vec3_origin;
  }
  local_58 = tmp_f12 - *(float *)(param_1 + 0x168);
  *(uint32_t *)(param_1 + 0x4b8) = 1;
  local_54 = tmp_f2 - *(float *)(param_1 + 0x16c);
  local_50 = tmp_f13 - *(float *)(param_1 + 0x170);
  local_4c = local_34 - *(float *)(param_1 + 0x174);
  local_48 = local_30 - *(float *)(param_1 + 0x178);
  local_44 = local_2c - *(float *)(param_1 + 0x17c);
  tmp_i6 = G_MoverPush(param_1,&local_58,&local_4c,&local_5c);
  if (tmp_i6 == 0) {
    script_mover_blocked(param_1,local_5c);
  }
  *(float *)(param_1 + 0x18) = tmp_f12;
  *(float *)(param_1 + 0x1c) = tmp_f2;
  *(float *)(param_1 + 0x20) = tmp_f13;
  *(float *)(param_1 + 0x3c) = local_34;
  *(float *)(param_1 + 0x40) = local_30;
  *(float *)(param_1 + 0x44) = local_2c;
LAB_0008e4ab:
  *(int *)(param_1 + 0x49c) = g_unk_00abe908;
  return;
}

void G_RunEntity(int *param_1,int param_2)
{
  int tmp_i1;
  float tmp_f2;
  uint tmp_u3;
  uint tmp_u4;
  char *tmp_pc5;
  void *tmp_pc6;
  int tmp_i7;
  int tmp_i8;
  uint *tmp_pu9;
  uint *tmp_pu10;
  
  if (param_1[0x179] != 0) {
    return;
  }
  if (param_1[0x65] == 0) {
    return;
  }
  if (GHIDRA_FIELD(g_debugHitboxes, 12, 4) == 0) {
    tmp_pu10 = (uint *)(g_debugHitboxes + 0x10);
    do {
      tmp_pu9 = tmp_pu10;
      tmp_u3 = *tmp_pu9 + 0xfefefeff & ~*tmp_pu9;
      tmp_u4 = tmp_u3 & 0x80808080;
      tmp_pu10 = tmp_pu9 + 1;
    } while (tmp_u4 == 0);
    if ((tmp_u3 & 0x8080) == 0) {
      tmp_pu10 = (uint *)((int)tmp_pu9 + 6);
      tmp_u4 = tmp_u4 >> 0x10;
    }
    if (2 < (int)tmp_pu10 + (-0x2e580b3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4))) goto LAB_0008e9b5;
  }
  else {
LAB_0008e9b5:
    G_DrawEntBBox(param_1);
  }
  tmp_i7 = param_1[0x110];
  if (tmp_i7 == 0) {
    if ((*(byte *)((int)param_1 + 10) & 2) != 0) {
      G_TagLinkEntity(param_1,param_2);
    }
  }
  else {
    if ((*(int *)(tmp_i7 + 0x5e4) == 0) && (*(int *)(tmp_i7 + 0x194) != 0)) {
      G_RunEntity_part_9();
      tmp_i7 = param_1[0x110];
      if (tmp_i7 == 0) goto LAB_0008e9fe;
    }
    tmp_i7 = G_PositionEntityOnTag(param_1,tmp_i7,param_1 + 0x100);
    if ((tmp_i7 != 0) && (param_1[100] == 0)) {
      if (param_1[0x3d] == 0) {
        BG_EvaluateTrajectory(param_1 + 0xc,g_unk_00abe908,param_1 + 0x5d,1,param_1[0x44]);
        tmp_i7 = param_1[0x110];
        param_1[0x5d] = (int)((float)param_1[0x5d] + *(float *)(tmp_i7 + 0x174));
        param_1[0x5e] = (int)((float)param_1[0x5e] + *(float *)(tmp_i7 + 0x178));
        param_1[0x5f] = (int)((float)param_1[0x5f] + *(float *)(tmp_i7 + 0x17c));
      }
      else {
        BG_EvaluateTrajectory(param_1 + 0xc,g_unk_00abe908,param_1 + 0x5d,1,param_1[0x44]);
      }
    }
  }
LAB_0008e9fe:
  param_1[0x136] = param_1[0x5a];
  tmp_i8 = ((int)(param_1 + -0x24f928) >> 9) * -0x55555555;
  param_1[0x137] = param_1[0x5b];
  tmp_i1 = g_unk_00abe900;
  tmp_i7 = tmp_i8 - g_unk_00abe900;
  param_1[0x138] = param_1[0x5c];
  if (tmp_i7 != 0 && tmp_i1 <= tmp_i8) {
    if ((*(byte *)((int)param_1 + 0x1b3) & 1) == 0) {
      param_1[2] = param_1[2] & 0xffffffbf;
    }
    else {
      param_1[2] = param_1[2] | 0x40;
    }
  }
  tmp_i1 = g_unk_00abe908;
  tmp_i7 = param_1[1];
  if (tmp_i7 == 0x39) {
    tmp_i7 = G_missileCamera(param_1);
    if (tmp_i7 != 0) {
      return;
    }
LAB_0008edf8:
    G_FreeEntity(param_1);
    return;
  }
  if (g_unk_00abe908 - param_1[0x70] < 0x12d) {
    if (param_1[0x71] != 0) {
      return;
    }
  }
  else {
    if (param_1[0x2e] != 0) {
      param_1[0x2e] = 0;
    }
    if (param_1[0x71] != 0) goto LAB_0008edf8;
    if (param_1[0x72] != 0) {
      param_1[0x72] = 0;
      trap_UnlinkEntity(param_1);
      param_1[1] = 10;
      param_1[0x4a] = 1;
      param_1[0x179] = 1;
      return;
    }
  }
  if (tmp_i7 == 0x20) {
    if (param_1[0x48] == 0) goto LAB_0008eacc;
LAB_0008eb13:
    if (param_1[0x73] == 0) {
      if ((tmp_i7 == 0x1b) || (tmp_i7 == 4)) {
        G_RunMover(param_1);
      }
      else if ((int)(param_1 + -0x24f928) < 0x18000) {
        G_RunClient(param_1);
      }
      else {
        if ((tmp_i7 - 0x31U < 2) && (param_1[0x99] != 0)) {
          *(int *)(param_1[0x99] + 0xfc) = param_1[0xb2];
          *(int *)(param_1[0x99] + 0x100) = param_1[0xb9];
        }
        if ((((g_unk_02a99a78 != 0) && ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= tmp_i8)) &&
            (tmp_i7 = param_1[0xa7], tmp_i1 < tmp_i7)) &&
           (tmp_pc5 = strstr((char *)param_1[0x69],"DPRINTF_"), tmp_pc5 == (char *)0x0)) {
          param_1[0xa7] = tmp_i7 + (tmp_i1 - g_unk_00abe910);
        }
        if (0x3f < *param_1) {
          G_Script_ScriptRun(param_1);
        }
        if ((0 < param_1[0xa7]) && (param_1[0xa7] <= g_unk_00abe908)) {
          tmp_pc6 = (void *)param_1[0xa9];
          param_1[0xa7] = 0;
          if (tmp_pc6 == (void *)0x0) {
            G_Error("NULL ent->think");
            tmp_pc6 = (void *)param_1[0xa9];
          }
          (*tmp_pc6)(param_1);
        }
      }
      goto LAB_0008ebc2;
    }
  }
  else {
    if (param_1[0x116] - 1U < 2) {
      if (*param_1 < 0x40) {
        return;
      }
      G_Script_ScriptRun(param_1);
      return;
    }
    if (param_1[0x48] == 0) {
LAB_0008eacc:
      if (param_1[0x6b] != 0) {
        return;
      }
    }
    if ((tmp_i7 == 0x1a || tmp_i7 == 3) || (tmp_i7 - 0x14U < 5)) {
      if (g_unk_02a99a78 == 0) {
        G_RunMissile(param_1);
        return;
      }
      param_1[4] = param_1[4] + (tmp_i1 - g_unk_00abe910);
      if (param_1[0xb7] == 0x15) {
        param_1[0x43] = param_1[0x43] + (g_unk_00abe908 - g_unk_00abe910);
      }
      tmp_i7 = g_unk_00abe908;
      if ((((g_unk_02a99a78 != 0) && ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= tmp_i8)) &&
          (tmp_i1 = param_1[0xa7], g_unk_00abe908 < tmp_i1)) &&
         (tmp_pc5 = strstr((char *)param_1[0x69],"DPRINTF_"), tmp_pc5 == (char *)0x0)) {
        param_1[0xa7] = tmp_i1 + (tmp_i7 - g_unk_00abe910);
      }
      if (0x3f < *param_1) {
        G_Script_ScriptRun(param_1);
      }
      if (param_1[0xa7] < 1) {
        return;
      }
      if (g_unk_00abe908 < param_1[0xa7]) {
        return;
      }
      param_1[0xa7] = 0;
      tmp_pc6 = (void *)param_1[0xa9];
      if (tmp_pc6 == (void *)0x0) {
        G_Error("NULL ent->think");
        tmp_pc6 = (void *)param_1[0xa9];
      }
      (*tmp_pc6)(param_1);
      return;
    }
    if (tmp_i7 == 0x19) {
      G_RunFlamechunk(param_1);
      goto LAB_0008ebc2;
    }
    if (tmp_i7 != 2) goto LAB_0008eb13;
  }
  G_RunItem(param_1);
LAB_0008ebc2:
  tmp_f2 = 1000.0 / (float)param_2;
  param_1[0x66] = (int)(((float)param_1[0x5a] - (float)param_1[0x136]) * tmp_f2);
  param_1[0x67] = (int)(((float)param_1[0x5b] - (float)param_1[0x137]) * tmp_f2);
  param_1[0x68] = (int)(((float)param_1[0x5c] - (float)param_1[0x138]) * tmp_f2);
  return;
}

void G_InitGame(uint32_t param_1,uint param_2,uint32_t param_3)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  uint tmp_u4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  int *tmp_pi7;
  uint32_t tmp_u8;
  uint8_t *tmp_pu9;
  uint8_t *tmp_pu10;
  uint *tmp_pu11;
  uint *tmp_pu12;
  uint32_t *tmp_pu13;
  uint tmp_u14;
  uint32_t *tmp_pu15;
  byte *tmp_pb16;
  byte *__s1;
  byte *tmp_pb17;
  uint8_t tmp_u18;
  uint8_t tmp_u19;
  bool tmp_b20;
  byte tmp_b21;
  int iStack_20780;
  uint8_t *puStack_2077c;
  int iStack_2076c;
  char acStack_20767 [27];
  uint32_t uStack_2074c;
  uint32_t auStack_20748 [328];
  uint8_t auStack_20228 [4];
  uint uStack_20224;
  uint auStack_20220 [32900];
  
  tmp_b21 = 0;
  acStack_20767[7] = '\0';
  acStack_20767[8] = '\0';
  acStack_20767[9] = '\0';
  acStack_20767[10] = '\0';
  acStack_20767[0xb] = '\0';
  acStack_20767[0xc] = '\0';
  acStack_20767[0xd] = '\0';
  acStack_20767[0xe] = '\0';
  acStack_20767[0x17] = '\0';
  acStack_20767[0x18] = '\0';
  acStack_20767[0x19] = '\0';
  acStack_20767[0x1a] = '\0';
  __s1 = (byte *)(acStack_20767 + 7);
  acStack_20767[0x13] = '\0';
  acStack_20767[0x14] = '\0';
  acStack_20767[0x15] = '\0';
  acStack_20767[0x16] = '\0';
  acStack_20767[0xf] = '\0';
  acStack_20767[0x10] = '\0';
  acStack_20767[0x11] = '\0';
  acStack_20767[0x12] = '\0';
  acStack_20767[0] = '\0';
  acStack_20767[1] = '\0';
  acStack_20767[2] = '\0';
  acStack_20767[3] = '\0';
  acStack_20767[4] = '\0';
  acStack_20767[5] = '\0';
  acStack_20767[6] = 0;
  Q_strcat(acStack_20767,7,&g_unk_0023bf57);
  Q_strcat(acStack_20767,7,"i");
  Q_strcat(acStack_20767,7,&g_unk_0026176c);
  Q_strcat(acStack_20767,7,"m");
  Q_strcat(acStack_20767,7,&g_unk_0024d8f6);
  Q_strcat(acStack_20767,7,&g_unk_00245eea);
  G_Printf("------- Game Initialization -------\n");
  G_Printf("gamename: %s\n",acStack_20767);
  G_Printf("gamebuild: %s\n","linux-i386");
  G_Printf("gamedate: %s\n","Feb 14 2023");
  G_Printf("gametime: %s\n","16:23:19");
  srand(param_2);
  trap_FS_FOpenFile("pak2.dat",&iStack_2076c,0);
  trap_FS_FCloseFile(iStack_2076c);
  G_RegisterCvars();
  trap_Cvar_Set("gamename",acStack_20767);
  trap_Cvar_VariableStringBuffer("gamename",__s1,0x14);
  tmp_i3 = strcmp((char *)__s1,acStack_20767);
  if (tmp_i3 != 0) {
LAB_0008f4f0:
    G_LogPrintf(
               "\nN!tmod: Unofficial server binaries detected!\nServer stopped!\nVisit www.etmods.net to download an official N!tmod package!\n\n"
               );
    G_ShutdownGame(0);
    return;
  }
  trap_Cvar_VariableStringBuffer("fs_game",__s1,0x14);
  tmp_i3 = strcmp((char *)__s1,acStack_20767);
  tmp_u18 = 0;
  tmp_u19 = tmp_i3 == 0;
  if (!(bool)tmp_u19) {
    G_LogPrintf("N!tmod: Invalid fs_game. Should be \'nitmod\'.\nServer stopped!\n\n");
    G_ShutdownGame(0);
    return;
  }
  trap_Cvar_VariableStringBuffer("mod_version",__s1,0x14);
  tmp_i3 = 6;
  tmp_pb16 = __s1;
  tmp_pb17 = &g_unk_00249e9e;
  do {
    if (tmp_i3 == 0) break;
    tmp_i3 = tmp_i3 + -1;
    tmp_u18 = *tmp_pb16 < *tmp_pb17;
    tmp_u19 = *tmp_pb16 == *tmp_pb17;
    tmp_pb16 = tmp_pb16 + (uint)tmp_b21 * -2 + 1;
    tmp_pb17 = tmp_pb17 + (uint)tmp_b21 * -2 + 1;
  } while ((bool)tmp_u19);
  if (!(bool)tmp_u19) goto LAB_0008f4f0;
  trap_Cvar_VariableStringBuffer("mod_url",__s1,0x14);
  tmp_i3 = 0xb;
  tmp_pb16 = (byte *)0x26dc62;
  do {
    if (tmp_i3 == 0) break;
    tmp_i3 = tmp_i3 + -1;
    tmp_u18 = *__s1 < *tmp_pb16;
    tmp_u19 = *__s1 == *tmp_pb16;
    __s1 = __s1 + (uint)tmp_b21 * -2 + 1;
    tmp_pb16 = tmp_pb16 + (uint)tmp_b21 * -2 + 1;
  } while ((bool)tmp_u19);
  if ((!(bool)tmp_u18 && !(bool)tmp_u19) != (bool)tmp_u18) goto LAB_0008f4f0;
  ClearMaxLivesBans();
  if (((GHIDRA_FIELD(g_gametype, 12, 4) != 5) && (GHIDRA_FIELD(g_enforcemaxlives, 12, 4) != 0)) &&
     ((0 < (int)GHIDRA_FIELD(g_maxlives, 12, 4) ||
      ((0 < (int)GHIDRA_FIELD(g_axismaxlives, 12, 4) || (0 < (int)GHIDRA_FIELD(g_alliedmaxlives, 12, 4))))))) {
    G_Printf("EnforceMaxLives-Cleared GUID List\n");
  }
  G_ProcessIPBans();
  G_InitMemory();
  if (GHIDRA_FIELD(g_gamestate, 12, 4) == -1) {
    tmp_u8 = va("%i",2);
    trap_Cvar_Set("gamestate",tmp_u8);
  }
  tmp_u8 = g_unk_00abef84;
  tmp_pu9 = &g_unk_02ad56a4;
  tmp_i3 = 0x20208;
  tmp_pu12 = &uStack_20224;
  if (((uint)&uStack_20224 & 4) != 0) {
    uStack_20224 = _DAT_02ad56a4;
    tmp_pu12 = auStack_20220;
    tmp_i3 = 0x20204;
    tmp_pu9 = &g_unk_02ad56a8;
  }
  tmp_pu13 = &g_unk_00abea4c;
  for (; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
    *(uint8_t *)tmp_pu12 = *tmp_pu9;
    tmp_pu9 = tmp_pu9 + (uint)tmp_b21 * -2 + 1;
    tmp_pu12 = (uint *)((int)tmp_pu12 + (uint)tmp_b21 * -2 + 1);
  }
  tmp_u14 = 0x528;
  tmp_pu15 = &uStack_2074c;
  if (((uint)&uStack_2074c & 4) != 0) {
    uStack_2074c = g_unk_00abea4c;
    tmp_pu15 = auStack_20748;
    tmp_u14 = 0x524;
    tmp_pu13 = &g_unk_00abea50;
  }
  for (tmp_u14 = tmp_u14 >> 2; tmp_u14 != 0; tmp_u14 = tmp_u14 - 1) {
    *tmp_pu15 = *tmp_pu13;
    tmp_pu13 = tmp_pu13 + (uint)tmp_b21 * -2 + 1;
    tmp_pu15 = tmp_pu15 + (uint)tmp_b21 * -2 + 1;
  }
  memset(&level,0,0x20dbdc0);
  g_unk_00abea4c = uStack_2074c;
  tmp_pu13 = auStack_20748;
  tmp_pu15 = &g_unk_00abea50;
  for (tmp_i3 = 0x149; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
    *tmp_pu15 = *tmp_pu13;
    tmp_pu13 = tmp_pu13 + (uint)tmp_b21 * -2 + 1;
    tmp_pu15 = tmp_pu15 + (uint)tmp_b21 * -2 + 1;
  }
  tmp_pu9 = &g_unk_02ad56a8;
  tmp_pu12 = auStack_20220;
  _DAT_02ad56a4 = uStack_20224;
  for (tmp_i3 = 0x20204; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
    *tmp_pu9 = (char)*tmp_pu12;
    tmp_pu12 = (uint *)((int)tmp_pu12 + (uint)tmp_b21 * -2 + 1);
    tmp_pu9 = tmp_pu9 + (uint)tmp_b21 * -2 + 1;
  }
  tmp_pu13 = &g_unk_02af5a44;
  iStack_20780 = 0;
  g_unk_00abef84 = tmp_u8;
  do {
    tmp_u14 = 0x3fa;
    tmp_b20 = ((uint)tmp_pu13 & 2) != 0;
    tmp_pu15 = tmp_pu13;
    if (tmp_b20) {
      *(uint16_t *)tmp_pu13 = 0;
      tmp_u14 = 0x3f8;
      tmp_pu15 = (uint32_t *)((int)tmp_pu13 + 2);
    }
    tmp_u4 = 0;
    do {
      *(uint32_t *)((int)tmp_pu15 + tmp_u4) = 0;
      *(uint32_t *)((int)tmp_pu15 + tmp_u4 + 4) = 0;
      tmp_u4 = tmp_u4 + 8;
    } while (tmp_u4 < (tmp_u14 & 0xfffffff8));
    if (!tmp_b20) {
      *(uint16_t *)((int)tmp_pu15 + tmp_u4) = 0;
    }
    tmp_pu13 = (uint32_t *)((int)tmp_pu13 + 0x3fa);
    (&g_unk_02b986ec)[iStack_20780] = 0;
    iStack_20780 = iStack_20780 + 1;
  } while (iStack_20780 != 0x28f);
  tmp_pu13 = &g_unk_02b9922c;
  tmp_pu15 = &g_unk_02b99128;
  do {
    tmp_pu5 = tmp_pu13 + 0x10;
    *tmp_pu15 = 0;
    tmp_pu15[0x441] = 0;
    *tmp_pu13 = 0;
    tmp_pu13[1] = 0;
    tmp_pu13[2] = 0;
    tmp_pu13[3] = 0;
    tmp_pu13[4] = 0;
    tmp_pu13[5] = 0;
    tmp_pu13[6] = 0;
    tmp_pu13[7] = 0;
    tmp_pu13[8] = 0;
    tmp_pu13[9] = 0;
    tmp_pu13[10] = 0;
    tmp_pu13[0xb] = 0;
    tmp_pu13[0xc] = 0;
    tmp_pu13[0xd] = 0;
    tmp_pu13[0xe] = 0;
    tmp_pu13[0xf] = 0;
    tmp_pu13 = tmp_pu5;
    tmp_pu15 = tmp_pu15 + 1;
  } while (tmp_pu5 != &g_unk_02b9a22c);
  g_unk_02b9a65c = 0;
  iStack_2076c = 0x40;
  Q_strncpyz(&g_unk_02ad55a4,0x2e55ef0,0x100);
  uStack_20224 = uStack_20224 & 0xffffff00;
  Info_SetValueForKey(&uStack_20224,&g_unk_002612d7,&g_unk_02ad55a4);
  Info_SetValueForKey(&uStack_20224,&g_unk_00260a4c,&g_unk_02ad56a4);
  trap_SetConfigstring(0x24,&uStack_20224);
  iStack_2076c = 0;
  do {
    tmp_i3 = BG_WeaponInWolfMP(iStack_2076c);
    if ((tmp_i3 != 0) || (iStack_2076c == 0)) {
      BG_RegisterWeapon(iStack_2076c,1);
    }
    tmp_i3 = (int)level;
    tmp_i6 = iStack_2076c + 1;
    iStack_2076c = tmp_i6;
  } while (tmp_i6 < 0x34);
  tmp_i2 = g_unk_00abe938;
  iStack_2076c = 0;
  g_unk_00abe908 = param_1;
  g_unk_00abe918 = param_1;
  g_unk_02a99a80 = tmp_i6;
  if (0 < g_unk_00abe938) {
    tmp_pi7 = &g_unk_00abe944;
    tmp_pi1 = &g_unk_00abe944 + g_unk_00abe938;
    do {
      tmp_i6 = *tmp_pi7;
      tmp_pi7 = tmp_pi7 + 1;
      *(uint32_t *)(tmp_i3 + tmp_i6 * 0x54dc + 0xbd4) = 0;
      iStack_2076c = tmp_i2;
    } while (tmp_pi7 != tmp_pi1);
  }
  g_unk_02a9845c = 0x3f800000;
  g_unk_02a98458 = 0x3f800000;
  g_unk_02a98464 = 0x3f800000;
  g_unk_02a983a0 = G_SoundIndex;
  g_unk_02a98460 = 0x3f800000;
  g_unk_02a9846c = 0x3f800000;
  g_unk_02a98468 = 0x3f800000;
  g_unk_02a983a4 = G_AnimScriptSound;
  g_unk_02a98474 = 0x3f800000;
  g_unk_02a98470 = 0x3f800000;
  g_unk_02a9847c = 0x3f800000;
  g_unk_02a983e8 = GHIDRA_FIELD(g_soldierChargeTime, 12, 4);
  g_unk_02a983e4 = GHIDRA_FIELD(g_soldierChargeTime, 12, 4);
  g_unk_02a983f0 = GHIDRA_FIELD(g_medicChargeTime, 12, 4);
  g_unk_02a983ec = GHIDRA_FIELD(g_medicChargeTime, 12, 4);
  g_unk_02a983f8 = GHIDRA_FIELD(g_engineerChargeTime, 12, 4);
  g_unk_02a983f4 = GHIDRA_FIELD(g_engineerChargeTime, 12, 4);
  g_unk_02a98400 = GHIDRA_FIELD(g_LTChargeTime, 12, 4);
  g_unk_02a983fc = GHIDRA_FIELD(g_LTChargeTime, 12, 4);
  g_unk_02a98408 = GHIDRA_FIELD(g_covertopsChargeTime, 12, 4);
  g_unk_02a98404 = GHIDRA_FIELD(g_covertopsChargeTime, 12, 4);
  g_unk_02a98478 = 0x3f800000;
  nitmod_SendChargeTimes(0);
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
    trap_GetConfigstring(0xe,&uStack_2074c,0x400);
    Info_SetValueForKey(&uStack_2074c,"w",&g_unk_0025a5f5);
    trap_SetConfigstring(0xe,&uStack_2074c);
    g_unk_02a98480 = 0xffffffff;
    if (GHIDRA_FIELD(g_currentRound, 12, 4) == 0) {
      trap_Cvar_Set("g_axiswins",&g_unk_0024bfa6);
      trap_Cvar_Set("g_alliedwins",&g_unk_0024bfa6);
      trap_Cvar_Update(g_axiswins);
      trap_Cvar_Update(g_alliedwins);
    }
    tmp_u8 = va("%i",GHIDRA_FIELD(g_axiswins, 12, 4));
    trap_SetConfigstring(0x17,tmp_u8);
    tmp_u8 = va("%i",GHIDRA_FIELD(g_alliedwins, 12, 4));
    trap_SetConfigstring(0x18,tmp_u8);
  }
  puStack_2077c = &g_unk_0024bfa6;
  if ((GHIDRA_FIELD(g_gametype, 12, 4) - 6 < 3) || (GHIDRA_FIELD(g_gametype, 12, 4) - 2 < 2)) {
    trap_SetConfigstring(0x1f,&g_unk_0026ea14);
    trap_SetConfigstring(0x20,&g_unk_0026ea14);
    trap_Cvar_Set("nitmod_axismapxp0",&g_unk_0026ea14);
    trap_Cvar_Set("nitmod_alliedmapxp0",&g_unk_0026ea14);
  }
  trap_GetServerinfo(&uStack_2074c,0x400);
  tmp_u8 = Info_ValueForKey(&uStack_2074c,"mapname");
  Q_strncpyz(&g_unk_00abe8c0,tmp_u8,0x40);
  G_ParseCampaigns();
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 4) {
    if ((*(int *)(g_campaigns + g_unk_02a98490 * 0x494 + 0x284) == 0) || (g_unk_02a98494 != 0)) {
      trap_Cvar_Set("g_axiswins",&g_unk_0024bfa6);
      trap_Cvar_Set("g_alliedwins",&g_unk_0024bfa6);
      trap_SetConfigstring(0x1f,&g_unk_0026ea14);
      trap_SetConfigstring(0x20,&g_unk_0026ea14);
      trap_Cvar_Set("nitmod_axismapxp0",&g_unk_0026ea14);
      trap_Cvar_Set("nitmod_alliedmapxp0",&g_unk_0026ea14);
      trap_Cvar_Update(g_axiswins);
      trap_Cvar_Update(g_alliedwins);
    }
    else {
      bani_getmapxp();
    }
    uStack_20224 = uStack_20224 & 0xffffff00;
    iStack_2076c = 0;
    do {
      if (g_campaigns[g_unk_02a98490 * 0x494 + iStack_2076c * 0x40] != '\0') {
        Q_strcat(&uStack_20224,0x28a,g_campaigns + g_unk_02a98490 * 0x494 + iStack_2076c * 0x40);
        Q_strcat(&uStack_20224,0x28a,&g_unk_00249e1d);
      }
      iStack_2076c = iStack_2076c + 1;
    } while (iStack_2076c < 10);
    tmp_pu12 = &uStack_20224;
    if ((char)uStack_20224 != '\0') {
      do {
        tmp_pu11 = tmp_pu12;
        tmp_u4 = *tmp_pu11 + 0xfefefeff & ~*tmp_pu11;
        tmp_u14 = tmp_u4 & 0x80808080;
        tmp_pu12 = tmp_pu11 + 1;
      } while (tmp_u14 == 0);
      if ((tmp_u4 & 0x8080) == 0) {
        tmp_pu12 = (uint *)((int)tmp_pu11 + 6);
        tmp_u14 = tmp_u14 >> 0x10;
      }
      *(uint8_t *)
       ((int)tmp_pu12 +
       (int)(auStack_20228 + (-(int)&uStack_20224 - (uint)CARRY1((byte)tmp_u14,(byte)tmp_u14)))) = 0;
    }
    trap_Cvar_Set("campaign_maps",&uStack_20224);
    tmp_u8 = va("%d,%d",*(int *)(g_campaigns + g_unk_02a98490 * 0x494 + 0x284) + 1,
               *(uint32_t *)(g_campaigns + g_unk_02a98490 * 0x494 + 0x280));
    trap_Cvar_Set(&g_unk_0024ae19,tmp_u8);
  }
  trap_SetConfigstring(0x1a,&g_unk_0026ea14);
  G_DebugOpenSkillLog();
  if (g_log[0x10] == '\0') {
    G_Printf("Not logging to disk.\n");
  }
  else {
    if (GHIDRA_FIELD(g_logSync, 12, 4) == 0) {
      tmp_u8 = 2;
    }
    else {
      tmp_u8 = 3;
    }
    trap_FS_FOpenFile(0x2e5d1b0,&g_unk_00abe8b4,tmp_u8);
    if (g_unk_00abe8b4 == 0) {
      G_Printf("WARNING: Couldn\'t open logfile: %s\n",0x2e5d1b0);
    }
    else {
      G_LogPrintf("------------------------------------------------------------\n");
      tmp_pu13 = &uStack_2074c;
      G_LogPrintf("InitGame: %s\n",&uStack_2074c);
      if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
        G_LogPrintf("Start of round. \n",tmp_pu13);
      }
      else {
        G_LogPrintf("Start of warmup. \n",tmp_pu13);
      }
    }
  }
  NxAC_Init();
  nitrox_InitAdminSystem();
  iStack_2076c = trap_Cvar_VariableIntegerValue("sv_floodprotect");
  if (iStack_2076c != 0) {
    G_Printf("WARNING: \'sv_floodprotect\' is set to %d, N!tmod requires it to be set to 0.\n",
             iStack_2076c);
    G_Printf("N!tmod: forcing \'sv_floodprotect\' to 0\n");
    trap_Cvar_Set("sv_floodprotect",&g_unk_0024bfa6);
  }
  if (g_mapConfigs[0x10] != '\0') {
    Q_strncpyz(&uStack_20224,"exec ",0x400);
    Q_strcat(&uStack_20224,0x400,0x2e5a150);
    Q_strcat(&uStack_20224,0x400,"/default.cfg\n");
    trap_SendConsoleCommand(2,&uStack_20224);
    Q_strncpyz(&uStack_20224,"exec ",0x400);
    Q_strcat(&uStack_20224,0x400,0x2e5a150);
    Q_strcat(&uStack_20224,0x400,&g_unk_0024ed91);
    Q_strcat(&uStack_20224,0x400,&g_unk_00abe8c0);
    Q_strcat(&uStack_20224,0x400,".cfg\n");
    trap_SendConsoleCommand(2,&uStack_20224);
  }
  G_InitRemappedShaders();
  G_InitWorldSession();
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 6) {
LAB_00090028:
    tmp_i3 = g_unk_02aa029c + 1;
    if ((int)GHIDRA_FIELD(g_resetXPMapCount, 12, 4) <= g_unk_02aa029c) {
      tmp_i3 = 1;
    }
    tmp_u8 = va("%d,%d",tmp_i3,GHIDRA_FIELD(g_resetXPMapCount, 12, 4));
    trap_Cvar_Set(&g_unk_0024ae19,tmp_u8);
    if ((g_mapConfigs[0x10] != '\0') && (GHIDRA_FIELD(g_resetXPMapCount, 12, 4) != 0)) {
      Q_strncpyz(&uStack_20224,"exec ",0x400);
      Q_strcat(&uStack_20224,0x400,0x2e5a150);
      if ((g_unk_02aa029c == 0) || (g_unk_02aa029c == GHIDRA_FIELD(g_resetXPMapCount, 12, 4))) {
        iStack_2076c = 2;
      }
      else if (g_unk_02aa029c + 1 < (int)GHIDRA_FIELD(g_resetXPMapCount, 12, 4)) {
        iStack_2076c = g_unk_02aa029c + 2;
      }
      else {
        iStack_2076c = 1;
      }
      tmp_u8 = va("/vote_%d.cfg",iStack_2076c);
      Q_strcat(&uStack_20224,0x400,tmp_u8);
      trap_SendConsoleCommand(2,&uStack_20224);
    }
  }
  else if (GHIDRA_FIELD(g_gametype, 12, 4) == 7) {
    tmp_b21 = g_TDMOptions[0xc] & 8;
joined_r0x00090022:
    if (tmp_b21 != 0) goto LAB_00090028;
  }
  else if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    tmp_b21 = g_DMOptions[0xd] & 0x40;
    goto joined_r0x00090022;
  }
  nitrox_ResetNumObjectives();
  trap_GetConfigstring(0xd,&uStack_2074c,0x400);
  Info_SetValueForKey(&uStack_2074c,&g_unk_0023bf57,&g_unk_0024bfa6);
  tmp_pu9 = g_clients;
  trap_SetConfigstring(0xd,&uStack_2074c);
  G_ResetTeamMapData();
  memset(g_entities,0,0x180000);
  g_unk_00abe8a4 = g_entities;
  nitrox_InitEntityArray(&SpawnEntities);
  nitrox_InitEntityArray(&TriggerEntities);
  nitrox_InitEntityArray(&TripmineEntities);
  nitrox_InitEntityArray(&LandmineEntities);
  nitrox_InitEntityArray(&IndicatorEntities);
  nitrox_InitEntityArray(&MG42Entities);
  nitrox_InitEntityArray(&SatchelEntities);
  nitrox_InitEntityArray(&AirstrikeEntities);
  tmp_u8 = GHIDRA_FIELD(g_maxclients, 12, 4);
  tmp_i3 = GHIDRA_FIELD(g_maxclients, 12, 4);
  g_unk_00abe900 = GHIDRA_FIELD(g_maxclients, 12, 4);
  memset(g_clients,0,0x153700);
  iStack_2076c = 0;
  level = g_clients;
  if (0 < (int)tmp_u8) {
    tmp_pu13 = (uint32_t *)(g_entities + 400);
    do {
      *tmp_pu13 = tmp_pu9;
      tmp_pu9 = tmp_pu9 + 0x54dc;
      tmp_pu13 = tmp_pu13 + 0x180;
      iStack_2076c = tmp_i3;
    } while (tmp_pu9 != g_clients + tmp_u8 * 0x54dc);
  }
  g_unk_00abe8a8 = 0x40;
  trap_LocateGameData(g_unk_00abe8a4,0x40,0x600,g_clients,0x54dc);
  G_LoadConfig(&g_unk_0026ea14,0);
  G_Script_ScriptLoad();
  nitrox_InitEventsQueue();
  nitrox_InitTempHeadQueue();
  nitrox_InitTempLegQueue();
  InitBodyQue();
  numSplinePaths = 0;
  numPathCorners = 0;
  if ((g_XPSave[0xc] & 4) != 0) goto LAB_0008fd60;
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 4) {
    if ((*(int *)(g_campaigns + g_unk_02a98490 * 0x494 + 0x284) != 0) && (g_unk_02a98494 == 0))
    goto LAB_0008fd60;
  }
  else if ((int)GHIDRA_FIELD(g_gametype, 12, 4) < 5) {
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 3) goto LAB_00090681;
  }
  else if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
LAB_00090681:
    if (GHIDRA_FIELD(g_currentRound, 12, 4) != 0) goto LAB_0008fd60;
  }
  else if (GHIDRA_FIELD(g_gametype, 12, 4) == 6) {
    if ((GHIDRA_FIELD(g_resetXPMapCount, 12, 4) == 0) ||
       ((g_unk_02aa029c < (int)GHIDRA_FIELD(g_resetXPMapCount, 12, 4) && (g_unk_02aa029c != 0)))) goto LAB_0008fd60;
    if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
      g_unk_02aa029c = 0;
    }
  }
  nitrox_XPSave_ClearXP();
LAB_0008fd60:
  InitServerEntities();
  G_SpawnEntitiesFromString();
  InitialServerEntitySetup();
  G_LinkDebris();
  G_LinkDamageParents();
  BG_ClearScriptSpeakerPool();
  tmp_u8 = va("sound/maps/%s.sps",&g_unk_00abe8c0);
  BG_LoadSpeakerScript(tmp_u8);
  if (g_unk_02a9969c == 0) {
    G_Printf("^1ERROR No \'script_multiplayer\' found in map\n");
  }
  g_unk_02a99b90 = 0;
  tmp_i3 = BG_LoadTraceMap(&g_unk_00abe8c0,&g_unk_02a99b94,&g_unk_02a99b9c);
  if (tmp_i3 == 0) {
    G_Printf("^1ERROR No tracemap found for map\n");
  }
  else {
    g_unk_02a99b90 = 1;
  }
  BG_BuildSplinePaths();
  G_FindTeams();
  G_Printf("-----------------------------------\n");
  trap_PbStat(0xffffffff,&g_unk_00249f51,&g_unk_00249f4c);
  BG_ClearAnimationPool();
  BG_ClearCharacterPool();
  BG_InitWeaponStrings();
  G_RegisterPlayerClasses();
  G_loadMatchGame();
  iStack_2076c = 0;
  do {
    InitSkillLevelStructure(iStack_2076c);
    G_ReassignSkillLevel(iStack_2076c);
    iStack_2076c = iStack_2076c + 1;
  } while (iStack_2076c < 7);
  nitrox_SendSkillLevels(0);
  nitrox_ParseMaxHP();
  nitrox_SendClassesMaxHP();
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    tmp_pu13 = &DMSpawnTime;
    do {
      *tmp_pu13 = 0xffffd8f0;
      tmp_pu13 = tmp_pu13 + 1;
    } while (tmp_pu13 != (uint32_t *)g_clients);
    iStack_2076c = 0x40;
  }
  GeoIP_open();
  tmp_u8 = va(&g_unk_00245ee6,GHIDRA_FIELD(g_TDMScore, 12, 4));
  trap_SendServerCommand(0xffffffff,tmp_u8);
  nitmod_SimpleCS(0);
  nitmod_SendNCS(0);
  nitmod_SendChargeTimes(0);
  g_unk_02b9a32c = 0xffffffff;
  G_LuaInit();
  G_LuaHook_InitGame(param_1,param_2,param_3);
  nitrox_OpenMasterSocket();
  nitrox_OpenNxACListenSocket();
  tmp_pu10 = &g_unk_00258b23;
  if ((int)GHIDRA_FIELD(n_NxAC, 12, 4) < 1) {
    tmp_pu10 = puStack_2077c;
  }
  trap_Cvar_Set("sv_NxAC",tmp_pu10);
  iStack_2076c = 0;
  tmp_i3 = g_unk_00abe900;
  if (g_unk_00abe900 < 1) {
    return;
  }
  do {
    if ((*(int *)(g_entities + iStack_2076c * 0x600 + 0x194) != 0) &&
       ((g_entities[iStack_2076c * 0x600 + 0x128] & 8) == 0)) {
      nitrox_ClearSocketInfos(iStack_2076c);
      tmp_i3 = g_unk_00abe900;
    }
    iStack_2076c = iStack_2076c + 1;
  } while (iStack_2076c < tmp_i3);
  return;
}

void G_RunFrame_part_10(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int *tmp_pi4;
  uint8_t *tmp_pu5;
  int tmp_i6;
  int local_24;
  
  if (g_unk_02b99228 != 0) {
    nitrox_ReadSocketData();
  }
  tmp_i6 = g_unk_00abe910;
  if (g_unk_00abe910 <= g_unk_00abe908) {
    tmp_i6 = g_unk_00abe90c;
  }
  g_unk_00abe90c = tmp_i6;
  param_1 = param_1 + g_unk_00abe90c;
  if (g_unk_02a99a78 == 0) {
    g_unk_02a99b84 = param_1 - g_unk_02a99b88;
  }
  else {
    g_unk_02a99b88 = param_1 - g_unk_02a99b84;
    if (g_unk_00abe908 == (g_unk_00abe908 / 500) * 500) {
      tmp_u1 = va("%i",g_unk_02a99b88 + g_unk_00abe918);
      trap_SetConfigstring(0xb,tmp_u1);
    }
  }
  nitrox_UpdateConfigstrings();
  g_unk_00abe914 = trap_Milliseconds();
  g_unk_00abe904 = g_unk_00abe904 + 1;
  tmp_i6 = param_1 - g_unk_00abe908;
  g_unk_00abe910 = g_unk_00abe908;
  g_unk_02aa29a8 = g_unk_02aa29a8 - tmp_i6;
  g_unk_02aa29ac = g_unk_02aa29ac - tmp_i6;
  g_unk_02aa29b0 = g_unk_02aa29b0 - tmp_i6;
  g_unk_02aa29b4 = g_unk_02aa29b4 - tmp_i6;
  if (g_unk_02aa29a8 < 0) {
    g_unk_02aa29a8 = 0;
  }
  if (g_unk_02aa29ac < 0) {
    g_unk_02aa29ac = 0;
  }
  if (g_unk_02aa29b0 < 0) {
    g_unk_02aa29b0 = 0;
  }
  if (g_unk_02aa29b4 < 0) {
    g_unk_02aa29b4 = 0;
  }
  g_unk_00abe908 = param_1;
  G_UpdateCvars();
  if (0 < g_unk_00abe8a8) {
    tmp_pu5 = g_entities;
    tmp_i3 = 0;
    tmp_i6 = g_unk_00abe8a8;
    do {
      while ((*(int *)(tmp_pu5 + 0x5e4) == 0 && (*(int *)(tmp_pu5 + 0x194) != 0))) {
        G_RunEntity_part_9();
        tmp_i3 = tmp_i3 + 1;
        tmp_pu5 = tmp_pu5 + 0x600;
        tmp_i6 = g_unk_00abe8a8;
        if (g_unk_00abe8a8 <= tmp_i3) goto LAB_00090d80;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu5 = tmp_pu5 + 0x600;
    } while (tmp_i3 < tmp_i6);
  }
LAB_00090d80:
  if (((GHIDRA_FIELD(g_msgs, 12, 4) != 0) && (g_unk_00abe908 == (g_unk_00abe908 / 1000) * 1000)) &&
     ((g_unk_00abe908 / 1000) % (int)GHIDRA_FIELD(g_msgs, 12, 4) == 0)) {
    G_PrintBanners();
  }
  if (g_unk_00abe938 < 1) {
    local_24 = 0;
  }
  else {
    tmp_i6 = 0;
    tmp_pi4 = &g_unk_00abe944;
    local_24 = 0;
    do {
      ClientEndFrame(g_entities + *tmp_pi4 * 0x600);
      tmp_i3 = *tmp_pi4;
      if (*(int *)(*(int *)(g_entities + tmp_i3 * 0x600 + 400) + 3000) - 1U < 2) {
        ClientThink_checkWeapons(g_entities + tmp_i3 * 0x600);
        tmp_i3 = *tmp_pi4;
      }
      if ((g_entities[tmp_i3 * 0x600 + 0x128] & 8) == 0) {
        if (0 < (int)GHIDRA_FIELD(n_NxAC, 12, 4)) {
          NxAC_CheckClient(g_entities + tmp_i3 * 0x600);
        }
        local_24 = local_24 + 1;
      }
      tmp_i6 = tmp_i6 + 1;
      tmp_pi4 = tmp_pi4 + 1;
    } while (tmp_i6 < g_unk_00abe938);
  }
  if (local_24 != g_unk_02b9a65c) {
    tmp_u1 = va("%i",local_24);
    trap_Cvar_Set("humans",tmp_u1);
  }
  g_unk_02b9a65c = local_24;
  CheckWolfMP();
  CheckExitRules();
  CheckTeamStatus();
  CheckVote();
  CheckCvars();
  G_UpdateTeamMapData();
  tmp_u1 = GHIDRA_FIELD(team_maxLandmines, 12, 4);
  tmp_i6 = g_unk_02a9969c;
  if (g_unk_02a9969c != 0) {
    tmp_i3 = G_CountTeamLandmines(1);
    *(int *)(tmp_i6 + 0x8c) = tmp_u1 - tmp_i3;
    tmp_u1 = GHIDRA_FIELD(team_maxLandmines, 12, 4);
    tmp_i6 = g_unk_02a9969c;
    tmp_i3 = G_CountTeamLandmines(2);
    *(int *)(tmp_i6 + 0x90) = tmp_u1 - tmp_i3;
    tmp_u1 = GHIDRA_FIELD(team_maxTripmines, 12, 4);
    tmp_i6 = g_unk_02a9969c;
    tmp_i3 = nitmod_CountTeamTripmines(1);
    *(int *)(tmp_i6 + 0x54) = tmp_u1 - tmp_i3;
    tmp_u1 = GHIDRA_FIELD(team_maxTripmines, 12, 4);
    tmp_i6 = g_unk_02a9969c;
    tmp_i3 = nitmod_CountTeamTripmines(2);
    *(int *)(tmp_i6 + 0x58) = tmp_u1 - tmp_i3;
  }
  if (((0 < (int)GHIDRA_FIELD(g_autoQuitDelay, 12, 4)) &&
      ((int)GHIDRA_FIELD(g_autoQuitDelay, 12, 4) <= (((g_unk_00abe908 / 1000) % 0x15180) % 0xe10) / 0x3c)) &&
     (g_unk_00abe938 == 0)) {
    trap_SendConsoleCommand(0,"quit\n");
  }
  if (GHIDRA_FIELD(n_crazyGravity, 12, 4) == 1) {
    if ((g_unk_02b9a32c == -1) || (g_unk_02b9a32c < g_unk_00abe908)) {
      tmp_i6 = 0;
      if (-1 < (int)GHIDRA_FIELD(n_crazyGravityMin, 12, 4)) {
        tmp_i6 = GHIDRA_FIELD(n_crazyGravityMin, 12, 4);
      }
      tmp_i3 = GHIDRA_FIELD(n_crazyGravityMax, 12, 4);
      if ((int)GHIDRA_FIELD(n_crazyGravityMax, 12, 4) <= tmp_i6) {
        tmp_i3 = tmp_i6 + 1;
      }
      tmp_i2 = rand();
      tmp_i6 = tmp_i6 + tmp_i2 % (tmp_i3 - tmp_i6);
      tmp_u1 = va(&g_unk_00245ee9,tmp_i6);
      trap_Cvar_Set("g_gravity",tmp_u1);
      g_unk_02b9a32c = GHIDRA_FIELD(n_crazyGravityInterval, 12, 4) + g_unk_00abe908;
      tmp_u1 = va("cpm \"^8crazygravity: ^9gravity changed to ^g%d\"",tmp_i6);
      trap_SendServerCommand(0xffffffff,tmp_u1);
    }
  }
  else if (g_unk_02b9a32c != -1) {
    g_unk_02b9a32c = -1;
    trap_Cvar_Set("g_gravity",&g_unk_0024a8b7);
    trap_SendServerCommand(0xffffffff,"cpm \"^8crazygravity: ^9gravity changed to ^g800\"");
  }
  G_LuaHook_RunFrame(param_1);
  return;
}

uint32_t G_RunFrame(uint32_t param_1)
{
  uint32_t tmp_u1;
  
  if (g_unk_00abe934 == 0) {
    tmp_u1 = G_RunFrame_part_10();
    return tmp_u1;
  }
  return param_1;
}

uint8_t * G_GetDateAndTime(void)
{
  time_t tVar1;
  tm *__tp;
  uint8_t *tmp_pu2;
  time_t local_10 [2];
  
  tVar1 = time(local_10);
  tmp_pu2 = &g_unk_0026ea14;
  if (tVar1 != 0) {
    tmp_pu2 = tstr_14553;
    __tp = localtime(local_10);
    strftime(tstr_14553,0x32,"%m-%d-%y %H:%M:%S",__tp);
  }
  return tmp_pu2;
}

void G_delayPrint(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  
  if (*(int *)(param_1 + 0x1a8) == 0) {
    if (1 < g_unk_02a99a78) {
      tmp_i4 = (GHIDRA_FIELD(match_timeoutlength, 12, 4) * 1000 + *(int *)(param_1 + 0x24c)) - g_unk_00abe908;
      if (GHIDRA_FIELD(match_timeoutlength, 12, 4) == -1) {
        return;
      }
      if (1000 < tmp_i4) {
        tmp_u2 = va("cp \"^3Match resuming in ^1%d^3 seconds!\n\"",tmp_i4 / 1000);
        trap_SendServerCommand(0xffffffff,tmp_u2);
        tmp_i4 = g_unk_00abe908 + 15000;
        goto LAB_00091c99;
      }
      g_unk_02a99a78 = 1;
      trap_SendServerCommand(0xffffffff,"print \"^3Match resuming in 10 seconds!\n\"");
      trap_SendServerCommand(0xffffffff,"an -1 0");
      tmp_i4 = g_unk_00abe908 + 10;
      tmp_i3 = G_Spawn();
      *(uint *)(tmp_i3 + 8) = *(uint *)(tmp_i3 + 8) | 0x40;
      *(uint *)(tmp_i3 + 0x128) = *(uint *)(tmp_i3 + 0x128) | 1;
      *(char **)(tmp_i3 + 0x1a4) = "DPRINTF_UNPAUSING";
      *(uint32_t *)(tmp_i3 + 0x1d4) = 0;
      *(uint32_t *)(tmp_i3 + 4) = 2;
      *(uint32_t *)(tmp_i3 + 0x1a8) = 1;
      tmp_i1 = g_unk_00abe908;
      *(uint32_t *)(tmp_i3 + 0x218) = 0;
      *(int *)(tmp_i3 + 0x29c) = tmp_i4;
      *(int *)(tmp_i3 + 0x24c) = tmp_i1;
      *(void **)(tmp_i3 + 0x2a4) = G_delayPrint;
    }
  }
  else if ((*(int *)(param_1 + 0x1a8) == 1) && (g_unk_02a99a78 == 1)) {
    tmp_i4 = (*(int *)(param_1 + 0x24c) - g_unk_00abe908) + 11000;
    if (1000 < tmp_i4) {
      tmp_u2 = va("cp \"^3Match resuming in ^1%d^3 seconds!\n\"",tmp_i4 / 1000);
      trap_SendServerCommand(0xffffffff,tmp_u2);
      tmp_i4 = g_unk_00abe908 + 1000;
LAB_00091c99:
      *(int *)(param_1 + 0x29c) = tmp_i4;
      return;
    }
    g_unk_02a99a78 = 0;
    trap_SendServerCommand(0xffffffff,"an 0 0");
    tmp_u2 = va("print \"%s\n\"","^1FIGHT!");
    trap_SendServerCommand(0xffffffff,tmp_u2);
    tmp_u2 = va("cp \"%s\n\"","^1FIGHT!");
    trap_SendServerCommand(0xffffffff,tmp_u2);
    tmp_u2 = va("%i",g_unk_02a99b88 + g_unk_00abe918);
    trap_SetConfigstring(0xb,tmp_u2);
    g_unk_02a99a80 = g_unk_02a99a80 & 0xffffffef;
    tmp_u2 = va(&g_unk_00245ee9,g_unk_02a99a80);
    trap_SetConfigstring(0x1d,tmp_u2);
  }
  *(uint32_t *)(param_1 + 0x29c) = 0;
  *(uint32_t *)(param_1 + 0x2a4) = 0;
  G_FreeEntity(param_1);
  return;
}

void G_initMatch(void)
{
  G_teamReset(1,0);
  G_teamReset(2,0);
  return;
}

void G_loadMatchGame(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  char *tmp_pc5;
  uint32_t tmp_u6;
  int tmp_i7;
  int local_43c [8];
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x91e69;
  if ((0 < (int)GHIDRA_FIELD(server_autoconfig, 12, 4)) &&
     (((GHIDRA_FIELD(z_serverflags, 12, 4) & 1) == 0 || (g_unk_00abe930 != 0)))) {
    G_configSet(GHIDRA_FIELD(g_gametype, 12, 4),GHIDRA_FIELD(server_autoconfig, 12, 4) == 1);
    tmp_u6 = va(&g_unk_00245ee9,GHIDRA_FIELD(z_serverflags, 12, 4) | 1);
    trap_Cvar_Set("z_serverflags",tmp_u6);
  }
  G_Printf("Setting MOTD...\n");
  trap_SetConfigstring(0x349,0x2e538b0);
  trap_SetConfigstring(0x34a,0x2e4e0f0);
  trap_SetConfigstring(0x34b,0x2e47f10);
  trap_SetConfigstring(0x34c,&g_unk_02e5a4b0);
  trap_SetConfigstring(0x34d,0x2e52470);
  trap_SetConfigstring(0x34e,0x2e4cb90);
  trap_SetConfigstring(0x34f,0x2e46f50);
  G_voteFlags();
  tmp_i1 = rand();
  tmp_i1 = tmp_i1 % 8;
  tmp_i2 = rand();
  tmp_i2 = tmp_i2 % 8;
  tmp_i3 = rand();
  tmp_i7 = 0;
  tmp_i3 = tmp_i3 % 4 + tmp_i2 * 4;
  tmp_i4 = rand();
  tmp_pc5 = (char *)va("%d %d",tmp_i4 % 8 + tmp_i1 * 8,tmp_i3);
  strcpy(local_41c,tmp_pc5);
  do {
    tmp_i4 = rand();
    tmp_i4 = (tmp_i4 % 0x10) * *(int *)((int)&aReinfSeeds + tmp_i7);
    *(int *)((int)local_43c + tmp_i7) = tmp_i4;
    tmp_i7 = tmp_i7 + 4;
    tmp_pc5 = (char *)va(&g_unk_00245ee8,tmp_i4,tmp_i3);
    strcat(local_41c,tmp_pc5);
  } while (tmp_i7 != 0x20);
  g_unk_02a99a68 = (uint)(local_43c[tmp_i1] * 1000) / (uint)(&aReinfSeeds)[tmp_i1];
  g_unk_02a99a6c = (uint)(local_43c[tmp_i2] * 1000) / (uint)(&aReinfSeeds)[tmp_i2];
  trap_SetConfigstring(0x1c,local_41c);
  return;
}

void G_printFull(uint32_t param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  if (param_2 != 0) {
    tmp_u1 = va("print \"%s\n\"",param_1);
    tmp_i2 = (param_2 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand(tmp_i2,tmp_u1);
    tmp_u1 = va("cp \"%s\n\"",param_1);
    trap_SendServerCommand(tmp_i2,tmp_u1);
    return;
  }
  tmp_u1 = va("print \"%s\n\"",param_1);
  trap_SendServerCommand(0xffffffff,tmp_u1);
  tmp_u1 = va("cp \"%s\n\"",param_1);
  trap_SendServerCommand(0xffffffff,tmp_u1);
  return;
}

void G_globalSound(uint32_t param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = nitrox_TempEventFromQueue(0,0x2a);
  tmp_u2 = G_SoundIndex(param_1);
  *(uint *)(tmp_i1 + 0x128) = *(uint *)(tmp_i1 + 0x128) | 0x20;
  *(uint32_t *)(tmp_i1 + 0xbc) = tmp_u2;
  return;
}

void G_spawnPrintf(int param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  
  tmp_i1 = G_Spawn();
  *(uint32_t *)(tmp_i1 + 0x1a4) = *(uint32_t *)(pszDPInfo + param_1 * 4);
  *(uint32_t *)(tmp_i1 + 0x1d4) = 0;
  *(uint *)(tmp_i1 + 8) = *(uint *)(tmp_i1 + 8) | 0x40;
  *(uint *)(tmp_i1 + 0x128) = *(uint *)(tmp_i1 + 0x128) | 1;
  *(uint32_t *)(tmp_i1 + 0x218) = param_3;
  *(uint32_t *)(tmp_i1 + 4) = 2;
  *(int *)(tmp_i1 + 0x1a8) = param_1;
  *(uint32_t *)(tmp_i1 + 0x24c) = g_unk_00abe908;
  *(uint32_t *)(tmp_i1 + 0x29c) = param_2;
  *(void **)(tmp_i1 + 0x2a4) = G_delayPrint;
  return;
}

void G_addStats(int param_1,int param_2,int param_3,int param_4)
{
  int *tmp_pi1;
  float tmp_f2;
  int tmp_i3;
  float tmp_f4;
  int tmp_i5;
  uint32_t tmp_u6;
  int tmp_i7;
  float *pfVar8;
  int tmp_i9;
  uint32_t tmp_u10;
  
  tmp_i5 = OnSameTeam(param_1,param_2);
  if (param_1 == 0) {
    return;
  }
  tmp_i7 = *(int *)(param_1 + 400);
  if (tmp_i7 == 0) {
    return;
  }
  tmp_i9 = *(int *)(param_1 + 0x2c8);
  if ((tmp_i9 < 1) && (*(int *)(tmp_i7 + 4) == 3)) {
    if (param_2 == 0) {
      return;
    }
    if (*(int *)(param_2 + 400) == 0) {
      return;
    }
    tmp_i5 = 0;
    do {
      if (param_4 == (&aWeapMOD)[tmp_i5 * 2]) {
        tmp_i5 = (&g_unk_0024c044)[tmp_i5 * 2];
        goto LAB_000925e2;
      }
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 != 0x45);
    tmp_i5 = 0x1a;
LAB_000925e2:
    tmp_i7 = tmp_i5 * 0x14 + 0xca0 + *(int *)(param_2 + 400);
    tmp_i5 = *(int *)(tmp_i7 + 0xc);
    *(int *)(tmp_i7 + 0xc) = tmp_i5 + -1;
    if (0 < tmp_i5) {
      return;
    }
    tmp_i5 = 0;
    do {
      if (param_4 == (&aWeapMOD)[tmp_i5 * 2]) {
        tmp_i5 = (&g_unk_0024c044)[tmp_i5 * 2];
        goto LAB_00092622;
      }
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 != 0x45);
    tmp_i5 = 0x1a;
LAB_00092622:
    *(uint32_t *)(*(int *)(param_2 + 400) + 0xcac + tmp_i5 * 0x14) = 1;
    return;
  }
  if (param_4 == 0x39) {
    return;
  }
  if (GHIDRA_FIELD(g_gamestate, 12, 4) != 0) {
    return;
  }
  if ((*(byte *)(tmp_i7 + 0xd) & 0x40) != 0) {
    return;
  }
  if ((*(uint *)(tmp_i7 + 0x68) & 0x800001) == 1) {
    if (*(int *)(param_2 + 400) != 0) {
      tmp_i5 = 0;
      do {
        if (param_4 == (&aWeapMOD)[tmp_i5 * 2]) {
          tmp_i5 = (&g_unk_0024c044)[tmp_i5 * 2];
          goto LAB_0009266a;
        }
        tmp_i5 = tmp_i5 + 1;
      } while (tmp_i5 != 0x45);
      tmp_i5 = 0x1a;
LAB_0009266a:
      tmp_pi1 = (int *)(*(int *)(param_2 + 400) + 0xcb8 + tmp_i5 * 0x14);
      *tmp_pi1 = *tmp_pi1 + 1;
      return;
    }
LAB_00092680:
    if (tmp_i9 < 1) {
      *(int *)(tmp_i7 + 0xc90) = *(int *)(tmp_i7 + 0xc90) + 1;
    }
    return;
  }
  if ((((param_1 == param_2) || (param_2 == 0)) ||
      (tmp_i3 = *(int *)(param_2 + 400), param_4 == 0x20)) || (tmp_i3 == 0)) goto LAB_00092680;
  tmp_i7 = 100;
  if (param_4 != 0x1e) {
    tmp_i7 = param_3;
  }
  if ((int)GHIDRA_FIELD(g_gametype, 12, 4) < 2) {
    return;
  }
  if (tmp_i5 == 0) {
    *(int *)(tmp_i3 + 0xc6c) = *(int *)(tmp_i3 + 0xc6c) + tmp_i7;
    if (param_4 == 0x11) {
      *(float *)(*(int *)(param_2 + 400) + 0xca0) =
           *(float *)(*(int *)(param_2 + 400) + 0xca0) + 0.1;
      tmp_i9 = *(int *)(param_1 + 400);
    }
    else if ((param_4 != 0x3b) ||
            (tmp_i9 = *(int *)(param_1 + 400), (*(byte *)(tmp_i9 + 0x6a) & 0x20) == 0)) {
      *(float *)(*(int *)(param_2 + 400) + 0xca0) =
           *(float *)(*(int *)(param_2 + 400) + 0xca0) + 1.0;
      tmp_i9 = *(int *)(param_1 + 400);
    }
    *(int *)(tmp_i9 + 0xc70) = *(int *)(tmp_i9 + 0xc70) + tmp_i7;
    goto LAB_00092435;
  }
  if ((((byte)GHIDRA_FIELD(g_friendlyFire, 12, 4) & 1) != 1) && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) {
    return;
  }
  if (param_4 != 0x17) {
    *(int *)(tmp_i3 + 0xc94) = *(int *)(tmp_i3 + 0xc94) + tmp_i7;
    tmp_i9 = *(int *)(param_2 + 400);
    if (param_4 == 0x28) {
      pfVar8 = (float *)&g_unk_0023e008;
      tmp_f2 = 0.5;
    }
    else {
      if (param_4 != 0x11) {
        *(float *)(tmp_i9 + 0xc9c) = *(float *)(tmp_i9 + 0xc9c) + 1.0;
        *(float *)(*(int *)(param_2 + 400) + 0xca0) =
             *(float *)(*(int *)(param_2 + 400) + 0xca0) + 1.0;
        tmp_i9 = *(int *)(param_1 + 0x2c8);
        goto LAB_0009242d;
      }
      pfVar8 = (float *)&g_unk_00244300;
      tmp_f2 = 0.1;
    }
    *(float *)(tmp_i9 + 0xc9c) = tmp_f2 + *(float *)(tmp_i9 + 0xc9c);
    *(float *)(*(int *)(param_2 + 400) + 0xca0) =
         *pfVar8 + *(float *)(*(int *)(param_2 + 400) + 0xca0);
    tmp_i9 = *(int *)(param_1 + 0x2c8);
  }
LAB_0009242d:
  if ((tmp_i9 < 1) &&
     (tmp_pi1 = (int *)(*(int *)(param_2 + 400) + 0xc98), *tmp_pi1 = *tmp_pi1 + 1,
     (*(byte *)(param_1 + 0x128) & 8) == 0)) {
    nitrox_CheckGlobalAwards(param_2,2,1);
  }
LAB_00092435:
  tmp_i9 = 0;
  do {
    if (param_4 == (&aWeapMOD)[tmp_i9 * 2]) {
      tmp_i9 = (&g_unk_0024c044)[tmp_i9 * 2];
      goto LAB_0009245e;
    }
    tmp_i9 = tmp_i9 + 1;
  } while (tmp_i9 != 0x45);
  tmp_i9 = 0x1a;
LAB_0009245e:
  if (0 < tmp_i7) {
    tmp_pi1 = (int *)(tmp_i9 * 0x14 + *(int *)(param_2 + 400) + 0xcb8);
    *tmp_pi1 = *tmp_pi1 + 1;
  }
  if ((tmp_i5 == 0) && (*(int *)(param_1 + 0x2c8) < 1)) {
    tmp_pi1 = (int *)(tmp_i9 * 0x14 + *(int *)(param_2 + 400) + 0xcbc);
    *tmp_pi1 = *tmp_pi1 + 1;
    tmp_pi1 = (int *)(tmp_i9 * 0x14 + *(int *)(param_1 + 400) + 0xcb0);
    *tmp_pi1 = *tmp_pi1 + 1;
  }
  if ((*(byte *)(param_2 + 0x128) & 8) != 0) {
    return;
  }
  if ((int)GHIDRA_FIELD(g_teamDamageRestriction, 12, 4) < 1) {
    return;
  }
  tmp_i5 = nitrox_CheckPermission(param_2,0);
  if (tmp_i5 != 0) {
    return;
  }
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    return;
  }
  tmp_f2 = *(float *)(*(int *)(param_2 + 400) + 0xca0);
  if (tmp_f2 <= 0.0) {
    tmp_f4 = 0.0;
  }
  else {
    tmp_f4 = (*(float *)(*(int *)(param_2 + 400) + 0xc9c) / tmp_f2) * 100.0;
  }
  if (tmp_f2 < (float)(int)GHIDRA_FIELD(g_minHits, 12, 4)) {
    return;
  }
  if (tmp_f4 <= (float)(int)GHIDRA_FIELD(g_teamDamageRestriction, 12, 4)) {
    return;
  }
  tmp_u10 = 0;
  if (GHIDRA_FIELD(g_autoTempBan, 12, 4) != 0) {
    tmp_u10 = GHIDRA_FIELD(g_autoTempBanTime, 12, 4);
  }
  tmp_u6 = va("Kicked for %d seconds for excessive team damage",tmp_u10);
  trap_DropClient((param_2 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6,tmp_u10);
  return;
}

void G_addStatsHeadShot(int param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  
  if (((param_1 != 0) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) && (*(int *)(param_1 + 400) != 0)) {
    tmp_i2 = 0;
    do {
      if (param_2 == (&aWeapMOD)[tmp_i2 * 2]) {
        tmp_i2 = (&g_unk_0024c044)[tmp_i2 * 2];
        goto LAB_0009280e;
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 != 0x45);
    tmp_i2 = 0x1a;
LAB_0009280e:
    tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0xcb4 + tmp_i2 * 0x14);
    *tmp_pi1 = *tmp_pi1 + 1;
  }
  return;
}

uint32_t G_createStats(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  uint32_t *tmp_pu8;
  byte tmp_b9;
  int local_834;
  uint local_82c;
  uint32_t local_81c [514];
  uint32_t uStack_14;
  
  tmp_u2 = 0;
  uStack_14 = 0x9287b;
  do {
    *(uint32_t *)((int)local_81c + tmp_u2) = 0;
    *(uint32_t *)((int)local_81c + tmp_u2 + 4) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x400);
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)local_81c + tmp_u2 + 0x400) = 0;
    *(uint32_t *)((int)local_81c + tmp_u2 + 0x404) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x400);
  if (param_1 == 0) {
    tmp_u3 = 0;
  }
  else {
    tmp_i5 = 0;
    local_82c = 0;
    tmp_i4 = *(int *)(param_1 + 400);
    do {
      tmp_i7 = tmp_i5 * 0x14;
      tmp_i1 = tmp_i4 + 0xca0 + tmp_i7;
      if (*(int *)(tmp_i1 + 0xc) == 0) {
        tmp_i6 = *(int *)(tmp_i1 + 0x18);
        local_834 = *(int *)(tmp_i1 + 0x10);
        tmp_i7 = *(int *)(tmp_i4 + 0xcbc + tmp_i7);
        if ((tmp_i6 != 0) || (local_834 != 0)) goto LAB_00092930;
        if (tmp_i7 != 0) {
          tmp_i6 = 0;
          goto LAB_00092930;
        }
      }
      else {
        local_834 = *(int *)(tmp_i1 + 0x10);
        tmp_i7 = *(int *)(tmp_i4 + 0xcbc + tmp_i7);
        tmp_i6 = *(int *)(tmp_i1 + 0x18);
LAB_00092930:
        local_82c = local_82c | 1 << ((byte)tmp_i5 & 0x1f);
        tmp_u3 = va(" %d %d %d %d %d",tmp_i6,*(int *)(tmp_i1 + 0xc),tmp_i7,local_834,
                   *(uint32_t *)(tmp_i4 + 0xcb4 + tmp_i5 * 0x14));
        Q_strcat(local_81c,0x400,tmp_u3);
        tmp_i4 = *(int *)(param_1 + 400);
      }
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 != 0x1a);
    if (local_82c != 0) {
      tmp_u3 = va(" %d %d %d",*(uint32_t *)(tmp_i4 + 0xc6c),*(uint32_t *)(tmp_i4 + 0xc70),
                 *(uint32_t *)(tmp_i4 + 0xc94));
      Q_strcat(local_81c,0x400,tmp_u3);
      tmp_i4 = *(int *)(param_1 + 400);
    }
    tmp_b9 = *(float *)(tmp_i4 + 0xbf4) != 0.0;
    if ((bool)tmp_b9) {
      tmp_u3 = va(&g_unk_00245ee8,(int)ROUND(*(float *)(tmp_i4 + 0xbf4)));
      Q_strcat(local_81c + 0x100,0x400,tmp_u3);
      tmp_i4 = *(int *)(param_1 + 400);
    }
    tmp_pu8 = local_81c + 0x100;
    if (*(float *)(tmp_i4 + 0xbf8) != 0.0) {
      tmp_b9 = tmp_b9 | 2;
      tmp_u3 = va(&g_unk_00245ee8,(int)ROUND(*(float *)(tmp_i4 + 0xbf8)));
      Q_strcat(tmp_pu8,0x400,tmp_u3);
      tmp_i4 = *(int *)(param_1 + 400);
    }
    if (*(float *)(tmp_i4 + 0xbfc) != 0.0) {
      tmp_b9 = tmp_b9 | 4;
      tmp_u3 = va(&g_unk_00245ee8,(int)ROUND(*(float *)(tmp_i4 + 0xbfc)));
      Q_strcat(tmp_pu8,0x400,tmp_u3);
      tmp_i4 = *(int *)(param_1 + 400);
    }
    if (*(float *)(tmp_i4 + 0xc00) != 0.0) {
      tmp_b9 = tmp_b9 | 8;
      tmp_u3 = va(&g_unk_00245ee8,(int)ROUND(*(float *)(tmp_i4 + 0xc00)));
      Q_strcat(tmp_pu8,0x400,tmp_u3);
      tmp_i4 = *(int *)(param_1 + 400);
    }
    if (*(float *)(tmp_i4 + 0xc04) != 0.0) {
      tmp_b9 = tmp_b9 | 0x10;
      tmp_u3 = va(&g_unk_00245ee8,(int)ROUND(*(float *)(tmp_i4 + 0xc04)));
      Q_strcat(tmp_pu8,0x400,tmp_u3);
      tmp_i4 = *(int *)(param_1 + 400);
    }
    if (*(float *)(tmp_i4 + 0xc08) != 0.0) {
      tmp_b9 = tmp_b9 | 0x20;
      tmp_u3 = va(&g_unk_00245ee8,(int)ROUND(*(float *)(tmp_i4 + 0xc08)));
      Q_strcat(tmp_pu8,0x400,tmp_u3);
      tmp_i4 = *(int *)(param_1 + 400);
    }
    if (*(float *)(tmp_i4 + 0xc0c) != 0.0) {
      tmp_b9 = tmp_b9 | 0x40;
      tmp_u3 = va(&g_unk_00245ee8,(int)ROUND(*(float *)(tmp_i4 + 0xc0c)));
      Q_strcat(tmp_pu8,0x400,tmp_u3);
      tmp_i4 = *(int *)(param_1 + 400);
    }
    tmp_u3 = va("%d %d %d%s %d%s",(param_1 + -0x93e4a0 >> 9) * -0x55555555,
               *(uint32_t *)(tmp_i4 + 0xc84),local_82c,local_81c,tmp_b9,tmp_pu8);
  }
  return tmp_u3;
}

void G_deleteStats(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint tmp_u5;
  uint16_t *tmp_pu6;
  uint32_t *tmp_pu7;
  bool tmp_b8;
  
  tmp_i1 = param_1 * 0x54dc + level;
  *(uint32_t *)(tmp_i1 + 0xc70) = 0;
  *(uint32_t *)(tmp_i1 + 0xc84) = 0;
  *(uint32_t *)(tmp_i1 + 0xc6c) = 0;
  *(uint32_t *)(tmp_i1 + 0xc94) = 0;
  *(uint32_t *)(tmp_i1 + 0xc74) = 0;
  *(uint32_t *)(tmp_i1 + 0xc78) = 0;
  *(uint32_t *)(tmp_i1 + 0xca8) = 0;
  *(uint32_t *)(tmp_i1 + 0xc7c) = 0;
  *(uint32_t *)(tmp_i1 + 0xc90) = 0;
  *(uint32_t *)(tmp_i1 + 0xf3c) = 0;
  tmp_pu6 = (uint16_t *)(tmp_i1 + 0xcac);
  *(uint32_t *)(tmp_i1 + 0xc98) = 0;
  *(uint32_t *)(tmp_i1 + 0xec8) = 0;
  tmp_b8 = ((uint)tmp_pu6 & 1) != 0;
  *(uint32_t *)(tmp_i1 + 0xecc) = 0;
  tmp_u5 = 0x21c;
  *(uint32_t *)(tmp_i1 + 0xc9c) = 0;
  *(uint32_t *)(tmp_i1 + 0xca0) = 0;
  *(uint32_t *)(tmp_i1 + 0xf38) = 0;
  if (tmp_b8) {
    tmp_pu6 = (uint16_t *)(tmp_i1 + 0xcad);
    tmp_u5 = 0x21b;
    *(uint8_t *)(tmp_i1 + 0xcac) = 0;
  }
  if (((uint)tmp_pu6 & 2) != 0) {
    *tmp_pu6 = 0;
    tmp_u5 = tmp_u5 - 2;
    tmp_pu6 = tmp_pu6 + 1;
  }
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)tmp_pu6 + tmp_u2) = 0;
    *(uint32_t *)((int)tmp_pu6 + tmp_u2 + 4) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < (tmp_u5 & 0xfffffff8));
  tmp_pu7 = (uint32_t *)((int)tmp_pu6 + tmp_u2);
  if ((tmp_u5 & 4) != 0) {
    *tmp_pu7 = 0;
    tmp_pu7 = tmp_pu7 + 1;
  }
  if ((tmp_u5 & 2) != 0) {
    *(uint16_t *)tmp_pu7 = 0;
    tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
  }
  if (tmp_b8) {
    *(uint8_t *)tmp_pu7 = 0;
  }
  tmp_u3 = va(&g_unk_00245ee9,param_1);
  tmp_u4 = va("wstats%i",param_1);
  trap_Cvar_Set(tmp_u4,tmp_u3);
  return;
}

void G_parseStats(char *param_1)
{
  uint tmp_u1;
  int tmp_i2;
  char *tmp_pc3;
  long tmp_l4;
  long *plVar5;
  int local_24;
  
  tmp_u1 = strtol(param_1,(char **)0x0,10);
  if (tmp_u1 < 0x41) {
    tmp_i2 = tmp_u1 * 0x54dc + level;
    tmp_pc3 = strchr(param_1,0x20);
    if (tmp_pc3 != (char *)0x0) {
      tmp_l4 = strtol(tmp_pc3 + 1,(char **)0x0,10);
      *(long *)(tmp_i2 + 0xc84) = tmp_l4;
      tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
      if (tmp_pc3 != (char *)0x0) {
        tmp_pc3 = tmp_pc3 + 1;
        tmp_u1 = strtol(tmp_pc3,(char **)0x0,10);
        local_24 = 0;
        plVar5 = (long *)(tmp_i2 + 0xcb4);
        do {
          if ((1 << ((byte)local_24 & 0x1f) & tmp_u1) != 0) {
            tmp_pc3 = strchr(tmp_pc3,0x20);
            if (tmp_pc3 == (char *)0x0) {
              return;
            }
            tmp_l4 = strtol(tmp_pc3 + 1,(char **)0x0,10);
            plVar5[1] = tmp_l4;
            tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
            if (tmp_pc3 == (char *)0x0) {
              return;
            }
            tmp_l4 = strtol(tmp_pc3 + 1,(char **)0x0,10);
            plVar5[-2] = tmp_l4;
            tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
            if (tmp_pc3 == (char *)0x0) {
              return;
            }
            tmp_l4 = strtol(tmp_pc3 + 1,(char **)0x0,10);
            plVar5[2] = tmp_l4;
            tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
            if (tmp_pc3 == (char *)0x0) {
              return;
            }
            tmp_l4 = strtol(tmp_pc3 + 1,(char **)0x0,10);
            plVar5[-1] = tmp_l4;
            tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
            if (tmp_pc3 == (char *)0x0) {
              return;
            }
            tmp_pc3 = tmp_pc3 + 1;
            tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
            *plVar5 = tmp_l4;
          }
          local_24 = local_24 + 1;
          plVar5 = plVar5 + 5;
        } while (local_24 != 0x1a);
        if ((tmp_u1 != 0) && (tmp_pc3 = strchr(tmp_pc3,0x20), tmp_pc3 != (char *)0x0)) {
          tmp_l4 = strtol(tmp_pc3 + 1,(char **)0x0,10);
          *(long *)(tmp_i2 + 0xc6c) = tmp_l4;
          tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
          if (tmp_pc3 != (char *)0x0) {
            tmp_l4 = strtol(tmp_pc3 + 1,(char **)0x0,10);
            *(long *)(tmp_i2 + 0xc70) = tmp_l4;
            tmp_pc3 = strchr(tmp_pc3 + 1,0x20);
            if (tmp_pc3 != (char *)0x0) {
              tmp_l4 = strtol(tmp_pc3 + 1,(char **)0x0,10);
              *(long *)(tmp_i2 + 0xc94) = tmp_l4;
            }
          }
        }
      }
    }
  }
  return;
}

void G_printMatchInfo(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  char *tmp_pc5;
  uint32_t tmp_u6;
  int tmp_i7;
  int tmp_i8;
  int local_480;
  int local_478;
  int local_474;
  int local_46c;
  int local_468;
  int local_464;
  int local_43c;
  int local_438;
  int local_434;
  int local_430;
  int local_42c;
  uint8_t local_41c [15];
  uint8_t local_40d;
  uint32_t uStack_14;
  
  uStack_14 = 0x9326b;
  local_46c = 0;
  tmp_i3 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  local_480 = 1;
  do {
    tmp_i4 = TeamCount(0xffffffff,local_480);
    if (tmp_i4 != 0) {
      trap_SendServerCommand
                (tmp_i3,
                 "sc \"\n^7TEAM   Player          Kll Dth Sui TK Eff  ^3GP^7    ^2DG    ^1DR   ^6TD  ^3Score\n^7---------------------------------------------------------------------\n\""
                );
      if (g_unk_00abe940 < 1) {
        local_42c = 0;
        local_43c = 0;
        local_464 = 0;
        tmp_i7 = 0;
        local_468 = 0;
        local_474 = 0;
        local_430 = 0;
        local_434 = 0;
        local_438 = 0;
        tmp_i4 = 0;
      }
      else {
        local_42c = 0;
        local_434 = 0;
        local_430 = 0;
        local_464 = 0;
        local_438 = 0;
        local_468 = 0;
        tmp_i7 = 0;
        local_43c = 0;
        local_474 = 0;
        tmp_i4 = g_unk_00abe940;
        do {
          while( true ) {
            tmp_i8 = (&g_unk_00abe944)[tmp_i7] * 0x54dc + level;
            if ((*(int *)(tmp_i8 + 0x5ac) != 2) || (*(int *)(tmp_i8 + 3000) != local_480)) break;
            SanitizeString(tmp_i8 + 0x5f8,local_41c,0);
            tmp_i4 = *(int *)(tmp_i8 + 0xc74);
            local_468 = local_468 + tmp_i4;
            tmp_i1 = *(int *)(tmp_i8 + 0xc7c);
            local_40d = 0;
            local_43c = local_43c + *(int *)(tmp_i8 + 0xc90);
            local_474 = local_474 + tmp_i1;
            local_438 = local_438 + *(int *)(tmp_i8 + 0xc98);
            local_434 = local_434 + *(int *)(tmp_i8 + 0xc6c);
            local_430 = local_430 + *(int *)(tmp_i8 + 0xc70);
            local_42c = local_42c + *(int *)(tmp_i8 + 0xc94);
            local_464 = local_464 + *(int *)(tmp_i8 + 0xc78);
            local_478 = 0;
            if (tmp_i1 + tmp_i4 != 0) {
              local_478 = (tmp_i1 * 100) / (tmp_i1 + tmp_i4);
              if (local_478 < 0) {
                local_478 = 0;
              }
            }
            tmp_i2 = *(int *)(param_1 + 400);
            if (tmp_i2 == tmp_i8) {
              tmp_pc5 = "^3";
            }
            else {
              tmp_pc5 = "^7";
              if (((*(int *)(tmp_i2 + 3000) == 3) && (*(int *)(tmp_i2 + 0xbc0) == 2)) &&
                 (*(int *)(tmp_i2 + 0xbc4) == (&g_unk_00abe944)[tmp_i7])) {
                tmp_pc5 = "^3";
              }
            }
            tmp_i7 = tmp_i7 + 1;
            local_46c = local_46c + 1;
            tmp_u6 = va("sc \"%-10s %s%-15s^3%4d%4d%4d%3d%s%4d^3%4d^2%6d^1%6d^6%5d^3%7d\n\"",
                       *(uint32_t *)(aTeams + local_480 * 4),tmp_pc5,local_41c,tmp_i1,tmp_i4,
                       *(int *)(tmp_i8 + 0xc90),*(int *)(tmp_i8 + 0xc98),tmp_pc5,local_478,
                       *(int *)(tmp_i8 + 0xc78) - tmp_i1,*(int *)(tmp_i8 + 0xc6c),
                       *(int *)(tmp_i8 + 0xc70),*(int *)(tmp_i8 + 0xc94),
                       *(uint32_t *)(tmp_i8 + 0x110));
            trap_SendServerCommand(tmp_i3,tmp_u6);
            tmp_i4 = g_unk_00abe940;
            if (g_unk_00abe940 <= tmp_i7) goto LAB_000935d0;
          }
          tmp_i7 = tmp_i7 + 1;
        } while (tmp_i7 < tmp_i4);
LAB_000935d0:
        if (local_468 + local_474 == 0) {
          tmp_i7 = local_464 - local_474;
          tmp_i4 = 0;
        }
        else {
          tmp_i4 = (local_474 * 100) / (local_468 + local_474);
          tmp_i7 = local_464 - local_474;
          if (tmp_i4 < 0) {
            tmp_i4 = 0;
          }
        }
      }
      tmp_u6 = va("sc \"^7---------------------------------------------------------------------\n%-10s ^5%-15s%4d%4d%4d%3d^5%4d^3%4d^2%6d^1%6d^6%5d^3%7d\n\""
                 ,*(uint32_t *)(aTeams + local_480 * 4),"Totals",local_474,local_468,local_43c,
                 local_438,tmp_i4,tmp_i7,local_434,local_430,local_42c,local_464);
      trap_SendServerCommand(tmp_i3,tmp_u6);
    }
    if (local_480 == 2) {
      if (local_46c == 0) {
        tmp_pc5 = "^3\nNo scores to report.";
      }
      else {
        tmp_pc5 = "";
      }
      tmp_u6 = va(&g_unk_0024bf9d,tmp_pc5);
      trap_SendServerCommand(tmp_i3,tmp_u6);
      return;
    }
    local_480 = 2;
  } while( true );
}

void G_matchInfoDump(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  char *tmp_pc6;
  uint32_t tmp_u7;
  uint8_t *tmp_pu8;
  int tmp_i9;
  uint8_t *tmp_pu10;
  int tmp_i11;
  
  if (0 < g_unk_00abe938) {
    tmp_i11 = 0;
    tmp_i4 = g_unk_00abe938;
    do {
      while( true ) {
        tmp_i9 = (&g_unk_00abe944)[tmp_i11] * 0x600;
        tmp_i1 = *(int *)(g_entities + tmp_i9 + 400);
        if (*(int *)(tmp_i1 + 0x5ac) == 2) break;
LAB_00093780:
        tmp_i11 = tmp_i11 + 1;
        if (tmp_i4 <= tmp_i11) {
          return;
        }
      }
      tmp_pu10 = g_entities + tmp_i9;
      tmp_i9 = tmp_i9 >> 9;
      if (param_1 == 1) {
        if ((*(byte *)(tmp_i1 + 0x97c) & 2) == 0) {
          tmp_u2 = *(uint *)(tmp_i1 + 0x978);
          if ((tmp_u2 & 1) == 0) {
            tmp_i5 = *(int *)(tmp_i1 + 3000);
            if (tmp_i5 == 3) {
              if (*(int *)(tmp_i1 + 0xbc0) == 1) goto LAB_00093780;
              if ((tmp_u2 & 2) == 0) {
                tmp_pu8 = g_entities + *(int *)(tmp_i1 + 0xbc4) * 0x600;
                goto LAB_000939b4;
              }
              tmp_i5 = *(int *)(*(int *)(tmp_i1 + 0xbc4) * 0x54dc + level + 3000);
            }
            else {
              tmp_pu8 = tmp_pu10;
              if ((tmp_u2 & 2) == 0) {
LAB_000939b4:
                tmp_u7 = G_createStats(tmp_pu8);
                tmp_u7 = va("ws %s\n",tmp_u7);
                trap_SendServerCommand(tmp_i9 * -0x55555555,tmp_u7);
                goto LAB_00093860;
              }
            }
            G_statsall_cmd(tmp_pu10,tmp_i5,0);
          }
          else {
            G_statsall_cmd(tmp_pu10,0,0);
          }
        }
LAB_00093860:
        if (*(int *)(tmp_i1 + 3000) == 3) goto LAB_000937d9;
        tmp_u7 = G_createStats(tmp_pu10);
        G_LogPrintf("WeaponStats: %s\n",tmp_u7);
        tmp_i4 = g_unk_00abe938;
        goto LAB_00093780;
      }
      if (param_1 != 2) goto LAB_00093780;
      if ((*(byte *)(tmp_i1 + 0x97c) & 2) == 0) {
        G_printMatchInfo(tmp_pu10);
      }
      if (GHIDRA_FIELD(g_gametype, 12, 4) == 3) {
        if (GHIDRA_FIELD(g_currentRound, 12, 4) == 1) {
          tmp_f3 = (float)GHIDRA_FIELD(g_nextTimeLimit, 8, 4) - (float)(int)GHIDRA_FIELD(g_nextTimeLimit, 12, 4);
          tmp_pc6 = "print \">>> ^3Clock set to: %d:%02d\n\n\n\"";
          tmp_u7 = GHIDRA_FIELD(g_nextTimeLimit, 12, 4);
        }
        else {
          tmp_f3 = (float)(g_unk_02a99b84 + (g_unk_00abf994 - (g_unk_00abe908 + g_unk_00abe918))) / 60000.0;
          if (tmp_f3 < (float)GHIDRA_FIELD(g_timelimit, 8, 4)) {
            tmp_u7 = va("print \">>> ^3Objective reached at %d:%02d (original: %d:%02d)\n\n\n\"",
                       (int)ROUND(tmp_f3),(int)ROUND((tmp_f3 - (float)(int)ROUND(tmp_f3)) * 60.0),
                       GHIDRA_FIELD(g_timelimit, 12, 4),
                       (int)ROUND(((float)GHIDRA_FIELD(g_timelimit, 8, 4) - (float)(int)GHIDRA_FIELD(g_timelimit, 12, 4)) * 60.0
                                 ));
            trap_SendServerCommand(tmp_i9 * -0x55555555,tmp_u7);
            tmp_i4 = g_unk_00abe938;
            goto LAB_00093780;
          }
          tmp_f3 = (float)GHIDRA_FIELD(g_timelimit, 8, 4) - (float)(int)GHIDRA_FIELD(g_timelimit, 12, 4);
          tmp_pc6 = "print \">>> ^3Objective NOT reached in time (%d:%02d)\n\n\n\"";
          tmp_u7 = GHIDRA_FIELD(g_timelimit, 12, 4);
        }
        tmp_u7 = va(tmp_pc6,tmp_u7,(int)ROUND(tmp_f3 * 60.0));
        trap_SendServerCommand(tmp_i9 * -0x55555555,tmp_u7);
      }
LAB_000937d9:
      tmp_i11 = tmp_i11 + 1;
      tmp_i4 = g_unk_00abe938;
    } while (tmp_i11 < g_unk_00abe938);
  }
  return;
}

uint32_t G_checkServerToggle(uint8_t *param_1)
{
  char tmp_c1;
  uint tmp_u2;
  int tmp_i3;
  
  if (param_1 == match_mutespecs) {
    tmp_u2 = 1;
  }
  else {
    if (param_1 == g_friendlyFire) {
      if ((g_friendlyFire[0xc] & 1) != 0) {
        g_unk_02a99a80 = g_unk_02a99a80 | 2;
        return 1;
      }
      g_unk_02a99a80 = g_unk_02a99a80 & 0xfffffffd;
      return 1;
    }
    if (param_1 == g_antilag) {
      tmp_u2 = 0x80;
    }
    else if (param_1 == g_balancedteams) {
      tmp_u2 = 0x100;
    }
    else {
      if (param_1 != match_warmupDamage) {
        if (param_1 == g_nextmap) {
          tmp_c1 = g_nextmap[0x10];
          if (GHIDRA_FIELD(g_gametype, 12, 4) == 4) {
            return 0;
          }
        }
        else {
          if (param_1 != g_nextcampaign) {
            return 0;
          }
          tmp_c1 = g_nextcampaign[0x10];
          if (GHIDRA_FIELD(g_gametype, 12, 4) != 4) {
            return 0;
          }
        }
        if (tmp_c1 == '\0') {
          g_unk_02a99a80 = g_unk_02a99a80 & 0xfffffdff;
        }
        else {
          g_unk_02a99a80 = g_unk_02a99a80 | 0x200;
        }
        return 1;
      }
      tmp_u2 = 0xc;
      if (0 < (int)GHIDRA_FIELD(match_warmupDamage, 12, 4)) {
        g_unk_02a99a80 = g_unk_02a99a80 & 0xfffffff3;
        tmp_i3 = 2;
        if ((int)GHIDRA_FIELD(match_warmupDamage, 12, 4) < 3) {
          tmp_i3 = GHIDRA_FIELD(match_warmupDamage, 12, 4);
        }
        tmp_u2 = tmp_i3 << 2;
      }
    }
  }
  if (0 < *(int *)(param_1 + 0xc)) {
    g_unk_02a99a80 = tmp_u2 | g_unk_02a99a80;
    return 1;
  }
  g_unk_02a99a80 = ~tmp_u2 & g_unk_02a99a80;
  return 1;
}

void G_statsPrint(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  uint8_t local_41c [1036];
  
  if (param_2 == 0) {
    tmp_pc3 = "ws";
  }
  else if (param_2 == 1) {
    tmp_pc3 = "wws";
  }
  else {
    tmp_pc3 = "gstats";
  }
  if ((param_1 != 0) && ((*(byte *)(param_1 + 0x128) & 8) == 0)) {
    tmp_i1 = trap_Argc();
    if (tmp_i1 < 2) {
      tmp_i1 = *(int *)(param_1 + 400);
      if (*(int *)(tmp_i1 + 3000) == 3) {
        if (*(int *)(tmp_i1 + 0xbc0) == 2) {
          tmp_u2 = G_createStats(g_entities + *(int *)(tmp_i1 + 0xbc4) * 0x600);
          tmp_u2 = va("%s %s\n",tmp_pc3,tmp_u2);
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
          return;
        }
        tmp_pc3 = "cpm \"Type ^3\\stats <player_id>^7 to see stats on an active player.\n\"";
      }
      else {
        tmp_u2 = G_createStats(param_1);
        tmp_pc3 = (char *)va("%s %s\n",tmp_pc3,tmp_u2);
      }
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc3);
    }
    else {
      trap_Argv(1,local_41c,0x400);
      tmp_i1 = ClientNumberFromString(param_1,local_41c);
      if (tmp_i1 != -1) {
        tmp_u2 = G_createStats(g_entities + tmp_i1 * 0x600);
        tmp_u2 = va("%s %s\n",tmp_pc3,tmp_u2);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
      }
    }
  }
  return;
}

void G_resetRoundState(void)
{
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 3) {
    trap_Cvar_Set("g_currentRound",&g_unk_0024bfa6);
  }
  else if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
    trap_Cvar_Set("g_currentRound",&g_unk_0024bfa6);
    trap_Cvar_Set("g_lms_currentMatch",&g_unk_0024bfa6);
    return;
  }
  return;
}

void G_resetModeState(void)
{
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 3) {
    trap_Cvar_Set("g_nextTimeLimit",&g_unk_0024bfa6);
  }
  else if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
    trap_Cvar_Set("g_axiswins",&g_unk_0024bfa6);
    trap_Cvar_Set("g_alliedwins",&g_unk_0024bfa6);
    return;
  }
  return;
}

uint8_t * G_Alloc(int param_1)
{
  uint8_t *tmp_pu1;
  
  if (GHIDRA_FIELD(g_debugAlloc, 12, 4) != 0) {
    G_Printf("G_Alloc of %i bytes (%i left)\n",param_1,
             (0x400000 - allocPoint) - (param_1 + 0x1fU & 0xffffffe0));
  }
  if (allocPoint + param_1 < 0x400001) {
    tmp_pu1 = memoryPool + allocPoint;
    allocPoint = (param_1 + 0x1fU & 0xffffffe0) + allocPoint;
  }
  else {
    G_Error("G_Alloc: failed on allocation of %u bytes\n",param_1);
    tmp_pu1 = (uint8_t *)0x0;
  }
  return tmp_pu1;
}

void G_InitMemory(void)
{
  allocPoint = 0;
  return;
}

void G_InitTempTraceIgnoreEnts(void)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  
  g_unk_02aa2f8c = 0;
  tmp_pu2 = &g_unk_02aa2f90;
  for (tmp_i1 = 0x3ff; tmp_i1 != 0; tmp_i1 = tmp_i1 + -1) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + 1;
  }
  return;
}

void G_ResetTempTraceIgnoreEnts(void)
{
  uint32_t *tmp_pu1;
  int *tmp_pi2;
  
  tmp_pi2 = &g_unk_02aa2f8c;
  tmp_pu1 = (uint32_t *)(g_entities + 0x120);
  do {
    if (*tmp_pi2 != 0) {
      *tmp_pu1 = 1;
      *tmp_pi2 = 0;
    }
    tmp_pu1 = tmp_pu1 + 0x180;
    tmp_pi2 = tmp_pi2 + 1;
  } while (tmp_pu1 != (uint32_t *)(censorDictionary + 0x120));
  return;
}

void G_TempTraceIgnoreEntity(int param_1)
{
  if (*(int *)(param_1 + 0x120) != 0) {
    (&g_unk_02aa2f8c)[(param_1 + -0x93e4a0 >> 9) * -0x15555555] = 1;
    *(uint32_t *)(param_1 + 0x120) = 0;
  }
  return;
}

uint8_t * G_TempTraceIgnorePlayersAndBodies(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  uint8_t *local_14;
  
  tmp_u2 = GHIDRA_FIELD(g_maxclients, 12, 4);
  local_14 = (uint8_t *)0x98579;
  if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
    if (GHIDRA_FIELD(g_hitboxes, 12, 4) == 0) {
      tmp_i4 = 0;
      tmp_pu3 = g_entities;
      do {
        while (*(int *)(tmp_pu3 + 0x120) == 0) {
          tmp_i4 = tmp_i4 + 1;
          tmp_pu3 = tmp_pu3 + 0x600;
          if (tmp_i4 == tmp_u2) goto LAB_00098690;
        }
        tmp_i4 = tmp_i4 + 1;
        (&g_unk_02aa2f8c)[((int)(tmp_pu3 + -0x93e4a0) >> 9) * -0x15555555] = 1;
        *(uint32_t *)(tmp_pu3 + 0x120) = 0;
        tmp_pu3 = tmp_pu3 + 0x600;
      } while (tmp_i4 != tmp_u2);
    }
    else {
      tmp_i4 = 0;
      tmp_pu3 = g_entities;
      do {
        if (*(int *)(tmp_pu3 + 0x120) != 0) {
          (&g_unk_02aa2f8c)[((int)(tmp_pu3 + -0x93e4a0) >> 9) * -0x15555555] = 1;
          *(uint32_t *)(tmp_pu3 + 0x120) = 0;
        }
        tmp_i5 = *(int *)(tmp_pu3 + 400);
        if (tmp_i5 != 0) {
          tmp_i1 = *(int *)(tmp_i5 + 0x528c);
          if ((tmp_i1 != 0) && (*(int *)(tmp_i1 + 0x120) != 0)) {
            (&g_unk_02aa2f8c)[(tmp_i1 + -0x93e4a0 >> 9) * -0x15555555] = 1;
            *(uint32_t *)(tmp_i1 + 0x120) = 0;
            tmp_i5 = *(int *)(tmp_pu3 + 400);
          }
          tmp_i5 = *(int *)(tmp_i5 + 0x5290);
          if ((tmp_i5 != 0) && (*(int *)(tmp_i5 + 0x120) != 0)) {
            (&g_unk_02aa2f8c)[(tmp_i5 + -0x93e4a0 >> 9) * -0x15555555] = 1;
            *(uint32_t *)(tmp_i5 + 0x120) = 0;
          }
        }
        tmp_i4 = tmp_i4 + 1;
        tmp_pu3 = tmp_pu3 + 0x600;
        local_14 = g_entities;
      } while (tmp_i4 != tmp_u2);
    }
  }
LAB_00098690:
  tmp_i4 = g_unk_00abf9b8;
  if (*(int *)(g_unk_00abf9b8 + 0x120) != 0) {
    (&g_unk_02aa2f8c)[(g_unk_00abf9b8 + -0x93e4a0 >> 9) * -0x15555555] = 1;
    *(uint32_t *)(tmp_i4 + 0x120) = 0;
  }
  tmp_i4 = g_unk_00abf9bc;
  if (*(int *)(g_unk_00abf9bc + 0x120) != 0) {
    (&g_unk_02aa2f8c)[(g_unk_00abf9bc + -0x93e4a0 >> 9) * -0x15555555] = 1;
    *(uint32_t *)(tmp_i4 + 0x120) = 0;
  }
  tmp_i4 = g_unk_00abf9c0;
  if (*(int *)(g_unk_00abf9c0 + 0x120) != 0) {
    (&g_unk_02aa2f8c)[(g_unk_00abf9c0 + -0x93e4a0 >> 9) * -0x15555555] = 1;
    *(uint32_t *)(tmp_i4 + 0x120) = 0;
  }
  tmp_i4 = g_unk_00abf9c4;
  if (*(int *)(g_unk_00abf9c4 + 0x120) != 0) {
    (&g_unk_02aa2f8c)[(g_unk_00abf9c4 + -0x93e4a0 >> 9) * -0x15555555] = 1;
    *(uint32_t *)(tmp_i4 + 0x120) = 0;
  }
  tmp_i4 = g_unk_00abf9c8;
  if (*(int *)(g_unk_00abf9c8 + 0x120) != 0) {
    (&g_unk_02aa2f8c)[(g_unk_00abf9c8 + -0x93e4a0 >> 9) * -0x15555555] = 1;
    *(uint32_t *)(tmp_i4 + 0x120) = 0;
  }
  tmp_i4 = g_unk_00abf9cc;
  if (*(int *)(g_unk_00abf9cc + 0x120) != 0) {
    (&g_unk_02aa2f8c)[(g_unk_00abf9cc + -0x93e4a0 >> 9) * -0x15555555] = 1;
    *(uint32_t *)(tmp_i4 + 0x120) = 0;
  }
  tmp_i4 = g_unk_00abf9d0;
  if (*(int *)(g_unk_00abf9d0 + 0x120) != 0) {
    (&g_unk_02aa2f8c)[(g_unk_00abf9d0 + -0x93e4a0 >> 9) * -0x15555555] = 1;
    *(uint32_t *)(tmp_i4 + 0x120) = 0;
  }
  tmp_i4 = g_unk_00abf9d4;
  if (*(int *)(g_unk_00abf9d4 + 0x120) != 0) {
    (&g_unk_02aa2f8c)[(g_unk_00abf9d4 + -0x93e4a0 >> 9) * -0x15555555] = 1;
    *(uint32_t *)(tmp_i4 + 0x120) = 0;
    return local_14;
  }
  return local_14;
}

void G_MakePip(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  tmp_i3 = nitrox_TempEventFromQueue(param_1 + 0x168,0x3d);
  *(uint32_t *)(tmp_i3 + 0x5c) = *(uint32_t *)(param_1 + 0x168);
  *(uint32_t *)(tmp_i3 + 0x60) = *(uint32_t *)(param_1 + 0x16c);
  tmp_f1 = *(float *)(param_1 + 0x170);
  *(float *)(tmp_i3 + 100) = tmp_f1;
  *(uint32_t *)(tmp_i3 + 0x74) = *(uint32_t *)(param_1 + 0x174);
  *(uint32_t *)(tmp_i3 + 0x78) = *(uint32_t *)(param_1 + 0x178);
  tmp_u2 = *(uint32_t *)(param_1 + 0x17c);
  *(uint32_t *)(tmp_i3 + 0xf4) = 5000;
  *(uint32_t *)(tmp_i3 + 0x7c) = tmp_u2;
  *(uint32_t *)(tmp_i3 + 0xb0) = 6000;
  *(uint32_t *)(tmp_i3 + 0x88) = 0x3f000000;
  *(float *)(tmp_i3 + 100) = tmp_f1 - 6.0;
  *(uint32_t *)(tmp_i3 + 0x80) = 0x41900000;
  *(uint32_t *)(tmp_i3 + 0x84) = 0x41900000;
  return;
}

uint32_t G_FlingClient(int param_1,int param_2)
{
  float tmp_f1;
  uint tmp_u2;
  float local_18;
  float local_14;
  float local_10;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) && (0 < *(int *)(param_1 + 0x2c8))) {
    if (param_2 == 0) {
      tmp_u2 = rand();
      tmp_f1 = (float)(tmp_u2 & 0x7fff) / 32767.0 - 0.5;
      local_18 = (tmp_f1 + tmp_f1) * 50.0;
      tmp_u2 = rand();
      local_10 = 10.0;
      tmp_f1 = (float)(tmp_u2 & 0x7fff) / 32767.0 - 0.5;
      local_14 = (tmp_f1 + tmp_f1) * 50.0;
    }
    else if (param_2 == 1) {
      AngleVectors(*(int *)(param_1 + 400) + 0xb0,&local_18,0,0);
      local_10 = 0.25;
    }
    else {
      local_18 = 0.0;
      local_14 = 0.0;
      local_10 = 10.0;
    }
    VectorNormalize(&local_18);
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + local_18 * 1500.0;
    *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) + local_14 * 1500.0;
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + local_10 * 1500.0;
    *(float *)(*(int *)(param_1 + 400) + 0x20) =
         local_18 * 1500.0 + *(float *)(*(int *)(param_1 + 400) + 0x20);
    *(float *)(*(int *)(param_1 + 400) + 0x24) =
         local_14 * 1500.0 + *(float *)(*(int *)(param_1 + 400) + 0x24);
    *(float *)(*(int *)(param_1 + 400) + 0x28) =
         local_10 * 1500.0 + *(float *)(*(int *)(param_1 + 400) + 0x28);
    return 1;
  }
  return 0;
}

char G_GetEnemyPosition(int param_1,int param_2)
{
  float tmp_f1;
  char tmp_c2;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  AngleVectors(*(int *)(param_1 + 400) + 0xb0,&local_24,0,0);
  AngleVectors(*(int *)(param_2 + 400) + 0xb0,&local_18,0,0);
  tmp_c2 = '\x01';
  tmp_f1 = local_10 * local_1c + local_14 * local_20 + local_18 * local_24;
  if (tmp_f1 <= 0.6) {
    tmp_c2 = (tmp_f1 < -0.6) * '\x02';
  }
  return tmp_c2;
}

bool G_ConstructionBegun(int param_1)
{
  if (*(float *)(param_1 + 0x84) == 1.0) {
    return true;
  }
  if ((*(int *)(param_1 + 0x39c) != 0) && (*(int *)(param_1 + 0x3a4) != 0)) {
    return true;
  }
  return *(float *)(param_1 + 0x80) != 0.0;
}

bool G_ConstructionIsFullyBuilt(int param_1)
{
  return *(float *)(param_1 + 0x84) == 1.0;
}

bool G_ConstructionIsPartlyBuilt(int param_1)
{
  if (*(float *)(param_1 + 0x84) == 1.0) {
    return true;
  }
  if (*(int *)(param_1 + 0x39c) == 0) {
    return false;
  }
  return *(int *)(param_1 + 0x3a4) != 0;
}

bool G_ConstructionIsDestroyable(int param_1)
{
  if ((*(float *)(param_1 + 0x84) != 1.0) &&
     ((*(int *)(param_1 + 0x39c) == 0 || (*(int *)(param_1 + 0x3a4) == 0)))) {
    return false;
  }
  return *(float *)(param_1 + 0x80) == 0.0;
}

int G_ConstructionForTeam(int param_1,int param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x264);
  if ((tmp_i1 == 0) || (*(int *)(tmp_i1 + 4) != 0x20)) {
    return 0;
  }
  if ((*(uint *)(tmp_i1 + 0x1a8) & 4) == 0) {
    if ((param_2 != 1) || ((*(uint *)(tmp_i1 + 0x1a8) & 8) == 0)) {
      return tmp_i1;
    }
  }
  else if (param_2 != 2) {
    return tmp_i1;
  }
  return *(int *)(tmp_i1 + 0x2e8);
}

int G_IsConstructible(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  
  if (param_2 == 0) {
    return 0;
  }
  if (*(int *)(param_2 + 4) != 0xc) {
    return 0;
  }
  tmp_i2 = *(int *)(param_2 + 0x264);
  if (tmp_i2 == 0) {
    return 0;
  }
  if (*(int *)(tmp_i2 + 4) != 0x20) {
    return 0;
  }
  if ((*(uint *)(tmp_i2 + 0x1a8) & 4) == 0) {
    if ((param_1 != 1) || ((*(uint *)(tmp_i2 + 0x1a8) & 8) == 0)) goto LAB_00098f41;
  }
  else if (param_1 != 2) goto LAB_00098f41;
  tmp_i2 = *(int *)(tmp_i2 + 0x2e8);
  if (tmp_i2 == 0) {
    return 0;
  }
LAB_00098f41:
  if (*(float *)(tmp_i2 + 0x84) != 1.0) {
    tmp_i1 = *(int *)(tmp_i2 + 0x2e8);
    if (tmp_i1 == 0) {
      return tmp_i2;
    }
    if ((*(float *)(tmp_i1 + 0x84) != 1.0) &&
       (((*(int *)(tmp_i1 + 0x39c) == 0 || (*(int *)(tmp_i1 + 0x3a4) == 0)) &&
        (*(float *)(tmp_i1 + 0x80) == 0.0)))) {
      return tmp_i2;
    }
  }
  return 0;
}

void G_BounceMissile(int param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  long double tmp_l6;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  if ((*(int *)(param_1 + 0xe8) - 0x24U < 2) &&
     (*(uint32_t *)(param_1 + 0x10c) = 1, *(int *)(param_1 + 0x29c) - g_unk_00abe908 < 0xcb2)) {
    G_ExplodeMissile(param_1);
    return;
  }
  BG_EvaluateTrajectoryDelta
            (param_1 + 0xc,
             (int)ROUND((float)(g_unk_00abe908 - g_unk_00abe910) * *(float *)(param_2 + 8) +
                        (float)g_unk_00abe910),&local_34,0,*(uint32_t *)(param_1 + 0x110));
  tmp_f1 = (local_2c * *(float *)(param_2 + 0x20) +
          local_30 * *(float *)(param_2 + 0x1c) + local_34 * *(float *)(param_2 + 0x18)) * -2.0;
  local_28 = *(float *)(param_2 + 0x18) * tmp_f1 + local_34;
  *(float *)(param_1 + 0x24) = local_28;
  local_24 = *(float *)(param_2 + 0x1c) * tmp_f1 + local_30;
  *(float *)(param_1 + 0x28) = local_24;
  local_20 = tmp_f1 * *(float *)(param_2 + 0x20) + local_2c;
  *(float *)(param_1 + 0x2c) = local_20;
  if (0.2 < *(float *)(param_2 + 0x20)) {
    tmp_i4 = *(int *)(param_2 + 0x34);
    *(int *)(param_1 + 0x94) = tmp_i4;
  }
  else {
    tmp_i4 = *(int *)(param_1 + 0x94);
  }
  if ((tmp_i4 != -1) && (tmp_i4 != 0x3fe)) {
    tmp_i5 = tmp_i4 * 0x600;
    local_28 = *(float *)(g_entities + tmp_i5 + 0x198) * 0.85 + local_28;
    *(float *)(param_1 + 0x24) = local_28;
    local_24 = *(float *)(g_entities + tmp_i5 + 0x19c) * 0.85 + local_24;
    *(float *)(param_1 + 0x28) = local_24;
    local_20 = *(float *)(g_entities + tmp_i5 + 0x1a0) * 0.85 + local_20;
    *(float *)(param_1 + 0x2c) = local_20;
  }
  if ((*(uint *)(param_1 + 8) & 0x8000000) != 0) {
    if ((*(uint *)(param_1 + 8) & 0x4000000) == 0) {
      local_28 = local_28 * 0.65;
      *(float *)(param_1 + 0x24) = local_28;
      local_24 = local_24 * 0.65;
      *(float *)(param_1 + 0x28) = local_24;
      local_20 = local_20 * 0.65;
      *(float *)(param_1 + 0x2c) = local_20;
    }
    else {
      local_28 = local_28 * 0.35;
      *(float *)(param_1 + 0x24) = local_28;
      local_24 = local_24 * 0.35;
      *(float *)(param_1 + 0x28) = local_24;
      local_20 = local_20 * 0.35;
      *(float *)(param_1 + 0x2c) = local_20;
    }
    if (tmp_i4 != 0x3fe) {
      local_28 = local_28 * 0.5;
      *(float *)(param_1 + 0x24) = local_28;
      local_24 = local_24 * 0.5;
      *(float *)(param_1 + 0x28) = local_24;
      local_20 = local_20 * 0.5;
      *(float *)(param_1 + 0x2c) = local_20;
    }
    if (0.2 < *(float *)(param_2 + 0x20)) {
      tmp_l6 = (long double)VectorLengthSquared(&local_28);
      if (tmp_l6 < (long double)1600.0) {
        *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + 1.0;
        switch(*(uint32_t *)(param_1 + 0xe8)) {
        case 4:
        case 9:
        case 0xf:
        case 0x15:
        case 0x19:
        case 0x1a:
        case 0x1c:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
          *(uint32_t *)(param_1 + 0x180) = 0x3fe;
        }
        G_SetOrigin(param_1,param_2 + 0xc);
        *(int *)(param_1 + 0x54) = g_unk_00abe908;
        if (1 < *(int *)(param_1 + 0xe8) - 0x24U) {
          return;
        }
        *(int *)(param_1 + 0x29c) = *(int *)(param_1 + 0x29c) + -0xcb2;
        return;
      }
      local_28 = *(float *)(param_1 + 0x24);
      local_24 = *(float *)(param_1 + 0x28);
      local_20 = *(float *)(param_1 + 0x2c);
    }
  }
  *(float *)(param_1 + 0x24) = (float)(int)ROUND(local_28);
  *(float *)(param_1 + 0x28) = (float)(int)ROUND(local_24);
  *(float *)(param_1 + 0x2c) = (float)(int)ROUND(local_20);
  tmp_f1 = *(float *)(param_1 + 0x168) + *(float *)(param_2 + 0x18);
  *(float *)(param_1 + 0x168) = tmp_f1;
  tmp_f2 = *(float *)(param_1 + 0x16c) + *(float *)(param_2 + 0x1c);
  *(float *)(param_1 + 0x16c) = tmp_f2;
  tmp_f3 = *(float *)(param_1 + 0x170) + *(float *)(param_2 + 0x20);
  *(float *)(param_1 + 0x170) = tmp_f3;
  *(float *)(param_1 + 0x18) = (float)(int)ROUND(tmp_f1);
  *(float *)(param_1 + 0x1c) = (float)(int)ROUND(tmp_f2);
  *(float *)(param_1 + 0x20) = (float)(int)ROUND(tmp_f3);
  *(int *)(param_1 + 0x10) = g_unk_00abe908;
  return;
}

void G_BurnTarget(int param_1,int *param_2,int param_3)
{
  float tmp_f1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  long double tmp_l5;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  uint8_t local_44 [8];
  float local_3c;
  
  if (param_2[0xb3] == 0) {
    return;
  }
  if (param_2[100] != 0) {
    if (g_unk_00abe908 <= *(int *)(param_2[100] + 0x154)) {
      tmp_i2 = g_unk_00abe908 + -1;
      param_2[0xe4] = 0;
      param_2[0x40] = tmp_i2;
      return;
    }
    if ((((g_friendlyFire[0xc] & 1) == 0) && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) &&
       (tmp_i2 = OnSameTeam(param_2,*(uint32_t *)(param_1 + 0x218)), tmp_i2 != 0)) {
      return;
    }
  }
  if (param_2[0xc1] < 3) {
    if (param_2[0x4c] == 0) {
      local_5c = (float)param_2[0x5a];
      local_58 = (float)param_2[0x5b];
      local_54 = (float)param_2[0x5c];
      if (param_2[100] != 0) {
        local_54 = (float)*(int *)(param_2[100] + 0xbc) + local_54;
      }
      local_50 = local_5c - *(float *)(param_1 + 0x168);
      local_4c = local_58 - *(float *)(param_1 + 0x16c);
      local_48 = local_54 - *(float *)(param_1 + 0x170);
    }
    else {
      if (*(float *)(param_1 + 0x5c) < (float)param_2[0x54]) {
        local_50 = (float)param_2[0x54] - *(float *)(param_1 + 0x168);
      }
      else if ((float)param_2[0x57] < *(float *)(param_1 + 0x168)) {
        local_50 = *(float *)(param_1 + 0x168) - (float)param_2[0x57];
      }
      else {
        local_50 = 0.0;
      }
      if (*(float *)(param_1 + 0x60) < (float)param_2[0x55]) {
        local_4c = (float)param_2[0x55] - *(float *)(param_1 + 0x16c);
      }
      else if ((float)param_2[0x58] < *(float *)(param_1 + 0x16c)) {
        local_4c = *(float *)(param_1 + 0x16c) - (float)param_2[0x58];
      }
      else {
        local_4c = 0.0;
      }
      if ((float)param_2[0x56] <= *(float *)(param_1 + 100)) {
        if (*(float *)(param_1 + 0x170) <= (float)param_2[0x59]) {
          local_48 = 0.0;
        }
        else {
          local_48 = *(float *)(param_1 + 0x170) - (float)param_2[0x59];
        }
      }
      else {
        local_48 = (float)param_2[0x56] - *(float *)(param_1 + 0x170);
      }
    }
    tmp_f1 = *(float *)(param_1 + 0x268);
    tmp_l5 = (long double)VectorLength(&local_50);
    if (((*param_2 != *(int *)(param_1 + 0x180)) || (tmp_l5 < (long double)tmp_f1 * (long double)0.5))
       && ((tmp_l5 < (long double)tmp_f1 || (param_3 != 0)))) {
      if (param_2[100] == 0) {
        if (0 < param_2[0xb2]) {
          tmp_u3 = G_GetWeaponDamage(6);
          G_Damage(param_2,*(uint32_t *)(param_1 + 0x218),*(uint32_t *)(param_1 + 0x218),
                   &vec3_origin,param_1 + 0x168,tmp_u3,0,0x11);
        }
      }
      else {
        trap_Trace(local_44,param_1 + 0x168,0,0,&local_5c,*param_2,0x6000001);
        if (1.0 <= local_3c) {
          if ((param_2[0xe5] != 0) && (0 < param_2[0xe4])) {
            tmp_i4 = param_2[0xe4] -
                    (int)ROUND(((float)(g_unk_00abe908 - param_2[0xe5]) / 1000.0) * 2.5);
            tmp_i2 = 0;
            if (-1 < tmp_i4) {
              tmp_i2 = tmp_i4;
            }
            param_2[0xe4] = tmp_i2;
          }
          G_BurnMeGood(*(uint32_t *)(param_1 + 0x218),param_2,param_1);
          if (((*(int *)(param_1 + 0x2e4) != 0) && (*(int *)(param_1 + 0x218) != 0)) &&
             (*(int *)(*(int *)(param_1 + 0x218) + 400) != 0)) {
            tmp_u3 = G_GetWeaponDamage(6);
            G_addStats(param_2,*(uint32_t *)(param_1 + 0x218),tmp_u3,0x11);
            *(uint32_t *)(param_1 + 0x2e4) = 0;
          }
        }
      }
    }
  }
  else {
    param_2[0xe4] = 0;
    param_2[0x40] = g_unk_00abe908 + -1;
  }
  return;
}

void G_FadeItems(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (0x40 < g_unk_00abe8a8) {
    tmp_i3 = 0x40;
    tmp_i2 = 0x9564a0;
    tmp_i1 = g_unk_00abe8a8;
    do {
      if ((((*(int *)(tmp_i2 + 0x194) != 0) && (*(int *)(tmp_i2 + 4) == 3)) &&
          (*(int *)(tmp_i2 + 0x2dc) == param_2)) && (*(int *)(tmp_i2 + 0x218) == param_1)) {
        *(uint32_t *)(tmp_i2 + 0x218) = 0;
        *(uint32_t *)(tmp_i2 + 0x180) = 0x3ff;
        G_FreeEntity(tmp_i2);
        tmp_i1 = g_unk_00abe8a8;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_i2 = tmp_i2 + 0x600;
    } while (tmp_i3 < tmp_i1);
  }
  return;
}

uint8_t * G_FindMissileBis(int param_1,int param_2)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  
  if (param_1 == 0) {
    tmp_i2 = 0;
  }
  else {
    tmp_i2 = (param_1 + -0x93e4a0 >> 9) * -0x55555555 + 1;
  }
  tmp_pu1 = g_entities + tmp_i2 * 0x600;
  if (tmp_i2 < g_unk_00abe8a8) {
    do {
      if ((((tmp_pu1 != (uint8_t *)0x0) && (*(int *)(tmp_pu1 + 0x194) != 0)) &&
          (*(int *)(tmp_pu1 + 4) == 3)) && (*(int *)(tmp_pu1 + 0xe8) == param_2)) {
        return tmp_pu1;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pu1 = tmp_pu1 + 0x600;
    } while (tmp_i2 != g_unk_00abe8a8);
  }
  return (uint8_t *)0x0;
}

void G_BlockThink(int param_1)
{
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

uint8_t * G_TestEntityPosition(uint32_t *param_1)
{
  int tmp_i1;
  float *pfVar2;
  int tmp_i3;
  uint32_t tmp_u4;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  uint32_t local_64;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [4];
  int local_50;
  float local_48;
  uint32_t local_44;
  float local_40;
  int local_20;
  
  tmp_i3 = param_1[0x75];
  if (tmp_i3 == 0) {
    tmp_i3 = 1;
  }
  if (param_1[100] == 0) {
    if (param_1[1] == 0x26) {
      local_60 = (float)param_1[6];
      local_5c = (float)param_1[7];
      local_58 = (float)param_1[8] + 4.0;
      tmp_u4 = *param_1;
      pfVar2 = &local_60;
    }
    else {
      pfVar2 = (float *)(param_1 + 6);
      if (param_1[1] == 3) {
        tmp_u4 = param_1[0x60];
      }
      else {
        tmp_u4 = *param_1;
      }
    }
    trap_Trace(local_54,pfVar2,param_1 + 0x4d,param_1 + 0x50,pfVar2,tmp_u4,tmp_i3);
  }
  else {
    tmp_i1 = param_1[100] + 0x14;
    trap_TraceCapsule(local_54,tmp_i1,param_1 + 0x4d,param_1 + 0x50,tmp_i1,*param_1,tmp_i3);
    if (local_50 != 0) goto LAB_000a52ef;
    if ((*(byte *)(param_1[100] + 0x6a) & 8) == 0) {
      return (uint8_t *)0x0;
    }
    AngleVectors(param_1[100] + 0xb0,&local_6c,0,0);
    local_64 = 0;
    VectorNormalizeFast(&local_6c);
    tmp_i1 = param_1[100];
    local_78 = local_6c * -32.0 + *(float *)(tmp_i1 + 0x14);
    local_74 = local_68 * -32.0 + *(float *)(tmp_i1 + 0x18);
    local_70 = *(float *)(tmp_i1 + 0x1c) + 24.0;
    local_58 = (local_70 - 21.6) - 24.0;
    local_60 = local_78;
    local_5c = local_74;
    trap_TraceCapsule(local_54,&local_78,&playerlegsProneMins,&playerlegsProneMaxs,&local_60,
                      *param_1,tmp_i3);
    if ((local_50 == 0) || (local_20 < 0x40)) {
      local_78 = local_48;
      local_74 = (float)local_44;
      local_70 = local_40;
      local_60 = local_48;
      local_5c = (float)local_44;
      local_58 = local_40 + 21.6;
      trap_TraceCapsule(local_54,&local_78,&playerlegsProneMins,&playerlegsProneMaxs,&local_60,
                        *param_1,tmp_i3);
      if (local_50 == 0) {
        return (uint8_t *)0x0;
      }
      if (local_20 < 0x40) {
        return (uint8_t *)0x0;
      }
    }
  }
  if (local_50 == 0) {
    return (uint8_t *)0x0;
  }
LAB_000a52ef:
  return g_entities + local_20 * 0x600;
}

void G_TestEntityDropToFloor(uint32_t *param_1,float param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t local_50;
  uint32_t local_4c;
  float local_48;
  uint8_t local_44 [12];
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  
  tmp_i2 = param_1[0x75];
  if (tmp_i2 == 0) {
    tmp_i2 = 1;
  }
  tmp_i1 = param_1[100];
  if (tmp_i1 == 0) {
    local_50 = param_1[6];
    local_4c = param_1[7];
    local_48 = (float)param_1[8] - param_2;
    trap_Trace(local_44,param_1 + 6,param_1 + 0x4d,param_1 + 0x50,&local_50,*param_1,tmp_i2);
  }
  else {
    local_50 = *(uint32_t *)(tmp_i1 + 0x14);
    local_4c = *(uint32_t *)(tmp_i1 + 0x18);
    local_48 = *(float *)(tmp_i1 + 0x1c) - param_2;
    trap_TraceCapsule(local_44,tmp_i1 + 0x14,param_1 + 0x4d,param_1 + 0x50,&local_50,*param_1,tmp_i2);
  }
  param_1[6] = local_38;
  param_1[7] = local_34;
  param_1[8] = local_30;
  if (param_1[100] != 0) {
    *(uint32_t *)(param_1[100] + 0x14) = local_38;
    *(uint32_t *)(param_1[100] + 0x18) = local_34;
    *(uint32_t *)(param_1[100] + 0x1c) = local_30;
  }
  return;
}

void G_TestEntityMoveTowardsPos(uint32_t *param_1,uint32_t param_2)
{
  int tmp_i1;
  uint8_t local_44 [12];
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  
  tmp_i1 = param_1[0x75];
  if (tmp_i1 == 0) {
    tmp_i1 = 1;
  }
  if (param_1[100] == 0) {
    trap_Trace(local_44,param_1 + 6,param_1 + 0x4d,param_1 + 0x50,param_2,*param_1,tmp_i1);
  }
  else {
    trap_TraceCapsule(local_44,param_1[100] + 0x14);
  }
  param_1[6] = local_38;
  param_1[7] = local_34;
  param_1[8] = local_30;
  if (param_1[100] != 0) {
    *(uint32_t *)(param_1[100] + 0x14) = local_38;
    *(uint32_t *)(param_1[100] + 0x18) = local_34;
    *(uint32_t *)(param_1[100] + 0x1c) = local_30;
  }
  return;
}

bool G_TryPushingEntity(uint32_t *param_1,int *param_2,float *param_3,int param_4)
{
  uint32_t *tmp_pu1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  float *pfVar7;
  int tmp_i8;
  uint32_t tmp_u9;
  float local_110;
  float local_10c;
  float local_f8;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  uint32_t local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  uint8_t local_9c [36];
  uint8_t local_78 [36];
  uint8_t local_54 [4];
  int local_50;
  float local_48;
  float local_44;
  float local_40;
  int local_20;
  
  if (((*(byte *)((int)param_2 + 0xb) & 0x10) != 0) && (param_1[0x25] != *param_2)) {
    return false;
  }
  if (pushed + 0x8000 < pushed_p) {
    G_Error("pushed_p > &pushed[MAX_GENTITIES]");
  }
  *pushed_p = param_1;
  pushed_p[1] = param_1[6];
  pushed_p[2] = param_1[7];
  pushed_p[3] = param_1[8];
  pushed_p[4] = param_1[0xf];
  pushed_p[5] = param_1[0x10];
  pushed_p[6] = param_1[0x11];
  tmp_i5 = 0;
  if (param_1[100] != 0) {
    pushed_p[7] = (float)*(int *)(param_1[100] + 0x48);
    pushed_p[1] = *(uint32_t *)(param_1[100] + 0x14);
    pushed_p[2] = *(uint32_t *)(param_1[100] + 0x18);
    pushed_p[3] = *(uint32_t *)(param_1[100] + 0x1c);
    tmp_i5 = param_1[100];
  }
  pushed_p = pushed_p + 8;
  param_1[6] = (float)param_1[6] + *param_3;
  param_1[7] = (float)param_1[7] + param_3[1];
  param_1[8] = (float)param_1[8] + param_3[2];
  if ((tmp_i5 != 0) && (((*(byte *)(tmp_i5 + 0x6a) & 8) != 0 || (param_1[0x3a] == 0x2a)))) {
    *(int *)(tmp_i5 + 0x48) =
         *(int *)(tmp_i5 + 0x48) +
         ((int)ROUND((*(float *)(param_4 + 4) * 65536.0) / 360.0) & 0xffffU);
  }
  BG_CreateRotationMatrix(param_4,local_78);
  BG_TransposeMatrix(local_78,local_9c);
  tmp_i5 = param_1[100];
  if (tmp_i5 == 0) {
    tmp_f2 = (float)param_1[6] - (float)param_2[0x5a];
    tmp_f3 = (float)param_1[7] - (float)param_2[0x5b];
    tmp_f4 = (float)param_1[8] - (float)param_2[0x5c];
  }
  else {
    tmp_f2 = *(float *)(tmp_i5 + 0x14) - (float)param_2[0x5a];
    tmp_f3 = *(float *)(tmp_i5 + 0x18) - (float)param_2[0x5b];
    tmp_f4 = *(float *)(tmp_i5 + 0x1c) - (float)param_2[0x5c];
  }
  local_cc = tmp_f2;
  local_c8 = tmp_f3;
  local_c4 = tmp_f4;
  BG_RotatePoint(&local_cc,local_9c);
  tmp_i5 = param_1[100];
  param_1[6] = (float)param_1[6] + (local_cc - tmp_f2);
  param_1[7] = (float)param_1[7] + (local_c8 - tmp_f3);
  param_1[8] = (float)param_1[8] + (local_c4 - tmp_f4);
  if (tmp_i5 != 0) {
    *(float *)(tmp_i5 + 0x14) = *(float *)(tmp_i5 + 0x14) + *param_3;
    *(float *)(param_1[100] + 0x18) = *(float *)(param_1[100] + 0x18) + param_3[1];
    *(float *)(param_1[100] + 0x1c) = *(float *)(param_1[100] + 0x1c) + param_3[2];
    *(float *)(param_1[100] + 0x14) = (local_cc - tmp_f2) + *(float *)(param_1[100] + 0x14);
    *(float *)(param_1[100] + 0x18) = (local_c8 - tmp_f3) + *(float *)(param_1[100] + 0x18);
    *(float *)(param_1[100] + 0x1c) = (local_c4 - tmp_f4) + *(float *)(param_1[100] + 0x1c);
  }
  if (param_1[0x25] != *param_2) {
    param_1[0x25] = 0xffffffff;
  }
  tmp_i5 = G_TestEntityPosition(param_1);
  if (tmp_i5 == 0) {
    tmp_i5 = param_1[100];
    if (tmp_i5 != 0) {
      param_1[0x5a] = *(uint32_t *)(tmp_i5 + 0x14);
      param_1[0x5b] = *(uint32_t *)(tmp_i5 + 0x18);
      param_1[0x5c] = *(uint32_t *)(tmp_i5 + 0x1c);
      return true;
    }
    param_1[0x5a] = param_1[6];
    param_1[0x5b] = param_1[7];
    param_1[0x5c] = param_1[8];
    return true;
  }
  if (*(int *)(tmp_i5 + 400) != 0) {
    pushedStackDepth = pushedStackDepth + 1;
    if ((pushedStackDepth < 3) &&
       (tmp_i5 = G_TryPushingEntity(tmp_i5,param_2,param_3,param_4), tmp_i5 != 0)) {
      tmp_i5 = param_1[100];
      if (tmp_i5 != 0) {
        param_1[0x5a] = *(uint32_t *)(tmp_i5 + 0x14);
        param_1[0x5b] = *(uint32_t *)(tmp_i5 + 0x18);
        param_1[0x5c] = *(uint32_t *)(tmp_i5 + 0x1c);
        return true;
      }
      param_1[0x5a] = param_1[6];
      param_1[0x5b] = param_1[7];
      param_1[0x5c] = param_1[8];
      return true;
    }
    pushedStackDepth = pushedStackDepth + -1;
  }
  tmp_f2 = (float)param_1[0x50];
  tmp_f3 = tmp_f2 * 0.5;
  if (4.0 < tmp_f3) {
    local_ec = (float)param_1[6];
    tmp_i5 = param_1[100];
    local_10c = (float)param_1[7];
    local_e8 = (float)param_1[8];
    if (tmp_i5 == 0) {
      if (0.0 < tmp_f3) {
LAB_000a5a94:
        local_d8 = 0.0;
        do {
          local_e0 = -local_d8;
          if (local_e0 <= local_d8) {
            do {
              tmp_f3 = tmp_f2 * 0.5;
              local_dc = 4.0;
              if (4.0 < tmp_f3) {
                do {
                  local_e4 = -local_dc;
                  if (local_e4 <= local_dc) {
                    do {
                      tmp_f3 = tmp_f2 * 0.5;
                      local_f8 = 4.0;
                      if (4.0 < tmp_f3) {
                        do {
                          local_110 = -local_f8;
                          if (local_110 <= local_f8) {
                            tmp_pu6 = param_1 + 0x50;
                            tmp_f2 = local_ec + local_e4;
                            tmp_pu1 = param_1 + 0x4d;
                            tmp_f3 = local_e8 + local_e0;
                            do {
                              local_c8 = local_110 + local_10c;
                              param_1[6] = tmp_f2;
                              param_1[7] = local_c8;
                              param_1[8] = tmp_f3;
                              local_cc = tmp_f2;
                              local_c4 = tmp_f3;
                              if (tmp_i5 == 0) {
                                tmp_i8 = param_1[0x75];
                                tmp_i5 = 0;
                                if (tmp_i8 == 0) {
LAB_000a5bec:
                                  tmp_i8 = 1;
                                  goto LAB_000a5bf1;
                                }
LAB_000a5cb0:
                                if (param_1[1] == 0x26) {
                                  local_a8 = (float)param_1[6];
                                  local_a4 = (float)param_1[7];
                                  local_a0 = (float)param_1[8] + 4.0;
                                  tmp_u9 = *param_1;
                                  pfVar7 = &local_a8;
LAB_000a607a:
                                  trap_Trace(local_54,pfVar7,tmp_pu1,tmp_pu6,pfVar7,tmp_u9,tmp_i8);
                                }
                                else {
                                  pfVar7 = (float *)(param_1 + 6);
                                  if (param_1[1] == 3) {
                                    tmp_u9 = param_1[0x60];
                                    goto LAB_000a607a;
                                  }
                                  trap_Trace(local_54,pfVar7,tmp_pu1,tmp_pu6,pfVar7,*param_1,tmp_i8);
                                }
LAB_000a5cf9:
                                if (local_50 == 0) {
LAB_000a6132:
                                  tmp_i5 = param_1[100];
                                  if (tmp_i5 == 0) {
                                    param_1[0x5a] = param_1[6];
                                    param_1[0x5b] = param_1[7];
                                    param_1[0x5c] = param_1[8];
                                    return true;
                                  }
LAB_000a5c47:
                                  param_1[0x5a] = *(uint32_t *)(tmp_i5 + 0x14);
                                  param_1[0x5b] = *(uint32_t *)(tmp_i5 + 0x18);
                                  param_1[0x5c] = *(uint32_t *)(tmp_i5 + 0x1c);
                                  return true;
                                }
                              }
                              else {
                                *(float *)(tmp_i5 + 0x14) = tmp_f2;
                                *(float *)(param_1[100] + 0x18) = local_c8;
                                *(float *)(param_1[100] + 0x1c) = tmp_f3;
                                tmp_i8 = param_1[0x75];
                                tmp_i5 = param_1[100];
                                if (tmp_i8 == 0) goto LAB_000a5bec;
LAB_000a5bf1:
                                if (tmp_i5 == 0) goto LAB_000a5cb0;
                                trap_TraceCapsule(local_54,tmp_i5 + 0x14,tmp_pu1,tmp_pu6,tmp_i5 + 0x14,
                                                  *param_1,tmp_i8);
                                if (local_50 == 0) {
                                  tmp_i5 = param_1[100];
                                  if ((*(byte *)(tmp_i5 + 0x6a) & 8) == 0) goto LAB_000a5c47;
                                  AngleVectors(tmp_i5 + 0xb0,&local_b4,0,0);
                                  local_ac = 0;
                                  VectorNormalizeFast(&local_b4);
                                  tmp_i5 = param_1[100];
                                  local_c0 = local_b4 * -32.0 + *(float *)(tmp_i5 + 0x14);
                                  local_bc = local_b0 * -32.0 + *(float *)(tmp_i5 + 0x18);
                                  local_b8 = *(float *)(tmp_i5 + 0x1c) + 24.0;
                                  local_a0 = (local_b8 - 21.6) - 24.0;
                                  local_a8 = local_c0;
                                  local_a4 = local_bc;
                                  trap_TraceCapsule(local_54,&local_c0,&playerlegsProneMins,
                                                    &playerlegsProneMaxs,&local_a8,*param_1,tmp_i8);
                                  if ((local_50 != 0) && (0x3f < local_20)) goto LAB_000a5cf9;
                                  local_c0 = local_48;
                                  local_bc = local_44;
                                  local_b8 = local_40;
                                  local_a8 = local_48;
                                  local_a4 = local_44;
                                  local_a0 = local_40 + 21.6;
                                  trap_TraceCapsule(local_54,&local_c0,&playerlegsProneMins,
                                                    &playerlegsProneMaxs,&local_a8,*param_1,tmp_i8);
                                  if ((local_50 != 0) && (0x3f < local_20)) goto LAB_000a5cf9;
                                  goto LAB_000a6132;
                                }
                              }
                              tmp_i5 = param_1[100];
                              local_110 = local_f8 + local_f8 + local_110;
                            } while (local_110 <= local_f8);
                            tmp_f2 = (float)param_1[0x50];
                          }
                          local_f8 = local_f8 + 4.0;
                          tmp_f3 = tmp_f2 * 0.5;
                        } while (local_f8 < tmp_f3);
                      }
                      local_e4 = local_dc + local_dc + local_e4;
                    } while (local_e4 <= local_dc);
                  }
                  else {
                    tmp_f3 = tmp_f2 * 0.5;
                  }
                  local_dc = local_dc + 4.0;
                } while (local_dc < tmp_f3);
              }
            } while ((local_e0 != 0.0) &&
                    (local_e0 = local_d8 + local_d8 + local_e0, local_e0 <= local_d8));
          }
          else {
            tmp_f3 = tmp_f2 * 0.5;
          }
          local_d8 = local_d8 + 4.0;
        } while (local_d8 < tmp_f3);
        param_1[6] = local_ec;
        param_1[7] = local_10c;
        param_1[8] = local_e8;
        if (tmp_i5 != 0) goto LAB_000a5de8;
      }
      else {
        param_1[6] = local_ec;
        param_1[7] = local_10c;
        param_1[8] = local_e8;
      }
      tmp_pu6 = pushed_p;
      param_1[6] = pushed_p[-7];
      param_1[7] = tmp_pu6[-6];
      param_1[8] = tmp_pu6[-5];
      goto LAB_000a5e54;
    }
    local_ec = *(float *)(tmp_i5 + 0x14);
    local_10c = *(float *)(tmp_i5 + 0x18);
    local_e8 = *(float *)(tmp_i5 + 0x1c);
    if (0.0 < tmp_f3) goto LAB_000a5a94;
    param_1[6] = local_ec;
    param_1[7] = local_10c;
    param_1[8] = local_e8;
LAB_000a5de8:
    *(float *)(tmp_i5 + 0x14) = local_ec;
    *(float *)(param_1[100] + 0x18) = local_10c;
    *(float *)(param_1[100] + 0x1c) = local_e8;
  }
  tmp_pu6 = pushed_p;
  param_1[6] = pushed_p[-7];
  param_1[7] = tmp_pu6[-6];
  param_1[8] = tmp_pu6[-5];
  if (param_1[100] != 0) {
    *(uint32_t *)(param_1[100] + 0x14) = tmp_pu6[-7];
    *(uint32_t *)(param_1[100] + 0x18) = tmp_pu6[-6];
    *(uint32_t *)(param_1[100] + 0x1c) = tmp_pu6[-5];
  }
LAB_000a5e54:
  param_1[0xf] = tmp_pu6[-4];
  param_1[0x10] = tmp_pu6[-3];
  param_1[0x11] = tmp_pu6[-2];
  tmp_i5 = G_TestEntityPosition(param_1);
  if (tmp_i5 == 0) {
    param_1[0x25] = 0xffffffff;
    pushed_p = pushed_p + -8;
  }
  return tmp_i5 == 0;
}

uint32_t G_MoverPush(int *param_1,float *param_2,float *param_3,uint32_t *param_4)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint8_t *tmp_pu7;
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
  int local_2060;
  float local_204c;
  float local_2048;
  float local_2044;
  float local_2040;
  float local_203c;
  float local_2038;
  float local_2034;
  float local_2030;
  float local_202c;
  float local_2028;
  float local_2024;
  float local_2020;
  int local_201c [1024];
  int local_101c [1027];
  
  *param_4 = 0;
  if ((((((float)param_1[0x5d] == 0.0) && ((float)param_1[0x5e] == 0.0)) &&
       ((float)param_1[0x5f] == 0.0)) && ((*param_3 == 0.0 && (param_3[1] == 0.0)))) &&
     (param_3[2] == 0.0)) {
    tmp_l10 = (long double)*param_2;
    local_2034 = (float)param_1[0x54];
    tmp_l11 = (long double)local_2034 + tmp_l10;
    tmp_l13 = (long double)(float)param_1[0x57] + tmp_l10;
    tmp_l14 = (long double)param_2[1];
    local_2030 = (float)param_1[0x55];
    tmp_l15 = (long double)local_2030 + tmp_l14;
    tmp_l16 = (long double)(float)param_1[0x58] + tmp_l14;
    tmp_l12 = (long double)param_2[2];
    local_202c = (float)param_1[0x56];
    tmp_l17 = (long double)local_202c + tmp_l12;
    tmp_l18 = (long double)(float)param_1[0x59] + tmp_l12;
    local_2028 = (float)param_1[0x57];
    local_2024 = (float)param_1[0x58];
    local_2020 = (float)param_1[0x59];
  }
  else {
    tmp_l8 = (long double)RadiusFromBounds(param_1 + 0x4d,param_1 + 0x50);
    tmp_l9 = (long double)(float)param_1[0x5a] - tmp_l8;
    tmp_l10 = (long double)*param_2;
    tmp_l11 = tmp_l9 + tmp_l10;
    tmp_l12 = (long double)(float)param_1[0x5a] + tmp_l8;
    tmp_l13 = tmp_l10 + tmp_l12;
    local_2034 = (float)tmp_l9;
    local_2028 = (float)tmp_l12;
    tmp_l9 = (long double)(float)param_1[0x5b] - tmp_l8;
    tmp_l14 = (long double)param_2[1];
    tmp_l15 = tmp_l9 + tmp_l14;
    tmp_l12 = (long double)(float)param_1[0x5b] + tmp_l8;
    tmp_l16 = tmp_l14 + tmp_l12;
    local_2030 = (float)tmp_l9;
    local_2024 = (float)tmp_l12;
    tmp_l9 = (long double)(float)param_1[0x5c] - tmp_l8;
    tmp_l12 = (long double)param_2[2];
    tmp_l17 = tmp_l9 + tmp_l12;
    tmp_l8 = (long double)(float)param_1[0x5c] + tmp_l8;
    tmp_l18 = tmp_l12 + tmp_l8;
    local_202c = (float)tmp_l9;
    local_2020 = (float)tmp_l8;
  }
  local_2038 = (float)tmp_l18;
  local_203c = (float)tmp_l16;
  local_2040 = (float)tmp_l13;
  local_2044 = (float)tmp_l17;
  local_2048 = (float)tmp_l15;
  local_204c = (float)tmp_l11;
  if (tmp_l10 <= (long double)0) {
    local_2034 = (float)(tmp_l10 + (long double)local_2034);
  }
  else {
    local_2028 = (float)(tmp_l10 + (long double)local_2028);
  }
  if (tmp_l14 <= (long double)0) {
    local_2030 = (float)(tmp_l14 + (long double)local_2030);
  }
  else {
    local_2024 = (float)(tmp_l14 + (long double)local_2024);
  }
  if (tmp_l12 <= (long double)0) {
    local_202c = (float)(tmp_l12 + (long double)local_202c);
  }
  else {
    local_2020 = (float)(tmp_l12 + (long double)local_2020);
  }
  trap_UnlinkEntity(param_1);
  tmp_i1 = trap_EntitiesInBox(&local_2034,&local_2028,local_201c,0x400);
  param_1[0x5a] = (int)(*param_2 + (float)param_1[0x5a]);
  param_1[0x5b] = (int)(param_2[1] + (float)param_1[0x5b]);
  param_1[0x5c] = (int)(param_2[2] + (float)param_1[0x5c]);
  param_1[0x5d] = (int)(*param_3 + (float)param_1[0x5d]);
  param_1[0x5e] = (int)(param_3[1] + (float)param_1[0x5e]);
  param_1[0x5f] = (int)(param_3[2] + (float)param_1[0x5f]);
  trap_LinkEntity(param_1);
  if (0 < tmp_i1) {
    tmp_i6 = 0;
    local_2060 = 0;
    do {
      while( true ) {
        tmp_i3 = local_201c[tmp_i6];
        tmp_i5 = *(int *)(g_entities + tmp_i3 * 0x600 + 4);
        if ((tmp_i5 != 0xf) && ((*(int *)(g_entities + tmp_i3 * 0x600 + 900) == 0 || (tmp_i5 != 0x1b)))
           ) break;
LAB_000a6630:
        tmp_i6 = tmp_i6 + 1;
        if (tmp_i6 == tmp_i1) goto LAB_000a6706;
      }
      tmp_i4 = tmp_i3 * 0x600;
      if (2 < tmp_i5 - 1U) {
        if (*(int *)(g_entities + tmp_i4 + 0x1cc) != 0) {
LAB_000a659f:
          tmp_i5 = tmp_i3 * 0x600;
          if (*(int *)(g_entities + tmp_i5 + 0x94) != *param_1) {
            if ((((local_2040 <= *(float *)(g_entities + tmp_i5 + 0x150)) ||
                 (local_203c <= *(float *)(g_entities + tmp_i5 + 0x154))) ||
                (local_2038 <= *(float *)(g_entities + tmp_i5 + 0x158))) ||
               (((*(float *)(g_entities + tmp_i5 + 0x15c) <= local_204c ||
                 (*(float *)(g_entities + tmp_i5 + 0x160) <= local_2048)) ||
                ((*(float *)(g_entities + tmp_i5 + 0x164) <= local_2044 ||
                 (tmp_pi2 = (int *)G_TestEntityPosition(g_entities + tmp_i4), tmp_pi2 != param_1))))))
            goto LAB_000a6630;
            tmp_i3 = local_201c[tmp_i6];
          }
LAB_000a68d0:
          local_101c[local_2060] = tmp_i3;
          local_2060 = local_2060 + 1;
        }
        goto LAB_000a6630;
      }
      if (tmp_i5 != 3) {
        if (((tmp_i5 != 1) || (tmp_i5 = *(int *)(g_entities + tmp_i4 + 400), tmp_i5 == 0)) ||
           (((*(byte *)(tmp_i5 + 0x69) & 0x80) == 0 && (*(int *)(tmp_i5 + 4) != 1))))
        goto LAB_000a659f;
        goto LAB_000a6630;
      }
      if (*(int *)(g_entities + tmp_i4 + 0x94) == *param_1) goto LAB_000a68d0;
      if (((*(int *)(g_entities + tmp_i4 + 0x2dc) != 0x44) &&
          (*(int *)(g_entities + tmp_i4 + 0x2dc) != 0x28)) ||
         (3 < *(uint *)(g_entities + tmp_i3 * 0x600 + 0x108))) goto LAB_000a6630;
      tmp_i6 = tmp_i6 + 1;
      LandMineTrigger(g_entities + tmp_i4);
    } while (tmp_i6 != tmp_i1);
LAB_000a6706:
    if (local_2060 != 0) {
      tmp_i1 = 0;
      do {
        tmp_pi2 = local_101c + tmp_i1;
        tmp_i1 = tmp_i1 + 1;
        trap_UnlinkEntity(g_entities + *tmp_pi2 * 0x600);
      } while (tmp_i1 != local_2060);
      tmp_i1 = 0;
      do {
        pushedStackDepth = 0;
        tmp_pu7 = g_entities + local_101c[tmp_i1] * 0x600;
        tmp_i6 = G_TryPushingEntity(tmp_pu7,param_1,param_2,param_3);
        if (tmp_i6 == 0) {
          if ((param_1[3] != 5) && (param_1[0xc] != 5)) {
            *param_4 = tmp_pu7;
            for (tmp_pu7 = pushed_p; pushed < tmp_pu7; tmp_pu7 = tmp_pu7 + -0x20) {
              *(uint32_t *)(*(int *)(tmp_pu7 + -0x20) + 0x18) = *(uint32_t *)(tmp_pu7 + -0x1c);
              *(uint32_t *)(*(int *)(tmp_pu7 + -0x20) + 0x1c) = *(uint32_t *)(tmp_pu7 + -0x18);
              *(uint32_t *)(*(int *)(tmp_pu7 + -0x20) + 0x20) = *(uint32_t *)(tmp_pu7 + -0x14);
              *(uint32_t *)(*(int *)(tmp_pu7 + -0x20) + 0x3c) = *(uint32_t *)(tmp_pu7 + -0x10);
              *(uint32_t *)(*(int *)(tmp_pu7 + -0x20) + 0x40) = *(uint32_t *)(tmp_pu7 + -0xc);
              *(uint32_t *)(*(int *)(tmp_pu7 + -0x20) + 0x44) = *(uint32_t *)(tmp_pu7 + -8);
              if (*(int *)(*(int *)(tmp_pu7 + -0x20) + 400) != 0) {
                *(int *)(*(int *)(*(int *)(tmp_pu7 + -0x20) + 400) + 0x48) =
                     (int)ROUND(*(float *)(tmp_pu7 + -4));
                *(uint32_t *)(*(int *)(*(int *)(tmp_pu7 + -0x20) + 400) + 0x14) =
                     *(uint32_t *)(tmp_pu7 + -0x1c);
                *(uint32_t *)(*(int *)(*(int *)(tmp_pu7 + -0x20) + 400) + 0x18) =
                     *(uint32_t *)(tmp_pu7 + -0x18);
                *(uint32_t *)(*(int *)(*(int *)(tmp_pu7 + -0x20) + 400) + 0x1c) =
                     *(uint32_t *)(tmp_pu7 + -0x14);
              }
            }
            tmp_i1 = 0;
            do {
              tmp_pi2 = local_101c + tmp_i1;
              tmp_i1 = tmp_i1 + 1;
              trap_LinkEntity(g_entities + *tmp_pi2 * 0x600);
            } while (tmp_i1 != local_2060);
            return 0;
          }
          G_Damage(tmp_pu7,param_1,param_1,0,0,0,0x20,0x1d);
        }
        else {
          trap_LinkEntity(tmp_pu7);
        }
        tmp_i1 = tmp_i1 + 1;
      } while (tmp_i1 != local_2060);
      tmp_i1 = 0;
      do {
        tmp_pi2 = local_101c + tmp_i1;
        tmp_i1 = tmp_i1 + 1;
        trap_LinkEntity(g_entities + *tmp_pi2 * 0x600);
      } while (tmp_i1 < local_2060);
    }
  }
  return 1;
}

void G_MoverTeam(int param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
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
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0xa6aeb;
  local_50 = 0;
  pushed_p = pushed;
  if (param_1 != 0) {
    tmp_i3 = param_1;
    do {
      BG_EvaluateTrajectory(tmp_i3 + 0xc,g_unk_00abe908,&local_34,0,*(uint32_t *)(param_1 + 0x110));
      BG_EvaluateTrajectory(tmp_i3 + 0x30,g_unk_00abe908,&local_28,1,*(uint32_t *)(param_1 + 0x110));
      local_4c = local_34 - *(float *)(tmp_i3 + 0x168);
      local_48 = local_30 - *(float *)(tmp_i3 + 0x16c);
      local_44 = local_2c - *(float *)(tmp_i3 + 0x170);
      local_40 = local_28 - *(float *)(tmp_i3 + 0x174);
      local_3c = local_24 - *(float *)(tmp_i3 + 0x178);
      local_38 = local_20 - *(float *)(tmp_i3 + 0x17c);
      tmp_i2 = G_MoverPush(tmp_i3,&local_4c,&local_40,&local_50);
      tmp_i4 = param_1;
      if (tmp_i2 == 0) {
        do {
          *(int *)(tmp_i4 + 0x10) = *(int *)(tmp_i4 + 0x10) + (g_unk_00abe908 - g_unk_00abe910);
          *(int *)(tmp_i4 + 0x34) = *(int *)(tmp_i4 + 0x34) + (g_unk_00abe908 - g_unk_00abe910);
          BG_EvaluateTrajectory
                    (tmp_i4 + 0xc,g_unk_00abe908,tmp_i4 + 0x168,0,*(uint32_t *)(param_1 + 0x110));
          BG_EvaluateTrajectory
                    (tmp_i4 + 0x30,g_unk_00abe908,tmp_i4 + 0x174,1,*(uint32_t *)(param_1 + 0x110));
          trap_LinkEntity(tmp_i4);
          tmp_pi1 = (int *)(tmp_i4 + 0x2f4);
          tmp_i4 = *tmp_pi1;
        } while (*tmp_pi1 != 0);
        if (*(void **)(param_1 + 0x2ac) == (void *)0x0) {
          return;
        }
        (**(void **)(param_1 + 0x2ac))(param_1,local_50);
        return;
      }
      tmp_i3 = *(int *)(tmp_i3 + 0x2f4);
    } while (tmp_i3 != 0);
    do {
      if (*(int *)(param_1 + 0xc) == 3) {
        tmp_i3 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x10);
joined_r0x000a6d33:
        if ((tmp_i3 <= g_unk_00abe908) && (*(void **)(param_1 + 0x2a8) != (void *)0x0)) {
          (**(void **)(param_1 + 0x2a8))(param_1);
        }
      }
      else if (*(int *)(param_1 + 0x30) == 3) {
        tmp_i3 = *(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x34);
        goto joined_r0x000a6d33;
      }
      param_1 = *(int *)(param_1 + 0x2f4);
    } while (param_1 != 0);
  }
  return;
}

void G_RunMover(int param_1)
{
  if ((*(byte *)(param_1 + 0x1b1) & 4) == 0) {
    if ((*(int *)(param_1 + 0xc) != 0) || (*(int *)(param_1 + 0x30) != 0)) {
      if (g_unk_02a99a78 == 0) {
        G_MoverTeam(param_1);
      }
      else {
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + (g_unk_00abe908 - g_unk_00abe910);
      }
    }
    G_RunThink(param_1);
    return;
  }
  if ((*(int *)(param_1 + 0x120) != 0) &&
     ((*(int *)(param_1 + 0x5c0) == 0x26903 || (*(int *)(param_1 + 0x5c0) == 0x2a92f)))) {
    trap_UnlinkEntity(param_1);
  }
  return;
}

void G_TryDoor(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  
  tmp_u3 = *(uint *)(param_1 + 0x1b0);
  if (((*(int *)(param_1 + 0x30) != 0) || (*(int *)(param_1 + 0xc) != 0)) ||
     (*(int *)(param_1 + 0x368) != 0)) {
    return;
  }
  if ((*(int *)(param_1 + 0x364) < 0) || (tmp_i2 = G_AllowTeamsAllowed(param_1,param_3), tmp_i2 == 0))
  {
    G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x204));
    return;
  }
  tmp_i2 = *(int *)(param_1 + 0x2f8);
  tmp_u3 = tmp_u3 & 0x40;
  if ((tmp_i2 != 0) && ((param_1 != tmp_i2 && (*(int *)(param_1 + 0x260) != 0)))) {
    *(uint32_t *)(tmp_i2 + 0x368) = 1;
    if (tmp_u3 != 0) {
      tmp_pu1 = (uint *)(*(int *)(param_1 + 0x2f8) + 0x1b0);
      *tmp_pu1 = *tmp_pu1 | 0x40;
    }
    Use_BinaryMover(*(uint32_t *)(param_1 + 0x2f8),param_3,param_3);
    G_UseTargets(*(uint32_t *)(param_1 + 0x2f8),param_3);
    return;
  }
  *(uint32_t *)(param_1 + 0x368) = 1;
  if (tmp_u3 != 0) {
    *(uint *)(param_1 + 0x1b0) = *(uint *)(param_1 + 0x1b0) | 0x40;
  }
  Use_BinaryMover(param_1,param_3,param_3);
  G_UseTargets(param_1,param_3);
  return;
}

void G_Activate(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  if ((((*(int *)(param_1 + 0x30) == 0) && (*(int *)(param_1 + 0xc) == 0)) &&
      (*(int *)(param_1 + 0x368) == 0)) &&
     ((-1 < *(int *)(param_1 + 0x364) && (*(int *)(param_1 + 0x5c0) != 0x27cac)))) {
    tmp_i1 = *(int *)(param_1 + 0x2f8);
    if ((tmp_i1 == 0) || ((param_1 == tmp_i1 || (*(int *)(param_1 + 0x260) == 0)))) {
      *(uint32_t *)(param_1 + 0x368) = 1;
      tmp_i1 = param_1;
    }
    else {
      *(uint32_t *)(tmp_i1 + 0x368) = 1;
      tmp_i1 = *(int *)(param_1 + 0x2f8);
    }
    Use_BinaryMover(tmp_i1,param_2,param_2);
    G_UseTargets(*(uint32_t *)(param_1 + 0x2f8),param_2);
  }
  return;
}

uint32_t * G_AllocDebrisChunk(void)
{
  uint32_t *tmp_pu1;
  
  if (g_unk_02a9a694 < 0x100) {
    tmp_pu1 = &g_unk_02a9a698 + g_unk_02a9a694 * 0x17;
    g_unk_02a9a694 = g_unk_02a9a694 + 1;
  }
  else {
    G_Error("ERROR: MAX_DEBRISCHUNKS(%i) hit.",0x100);
    tmp_pu1 = (uint32_t *)0x0;
  }
  return tmp_pu1;
}

void G_LinkDamageParents(void)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  
  if (0 < g_unk_00abe8a8) {
    tmp_pu5 = g_entities;
    tmp_i4 = 0;
    tmp_i3 = g_unk_00abe8a8;
    do {
      while ((tmp_pc1 = *(char **)(tmp_pu5 + 0x464), tmp_pc1 != (char *)0x0 && (*tmp_pc1 != '\0'))) {
        tmp_u2 = BG_StringHashValue(tmp_pc1);
        tmp_i3 = G_FindByTargetnameFast(0,*(uint32_t *)(tmp_pu5 + 0x464),tmp_u2);
        *(int *)(tmp_pu5 + 0x490) = tmp_i3;
        if (tmp_i3 == 0) {
          G_Error("Error: Failed to find damageparent: %s\n",*(uint32_t *)(tmp_pu5 + 0x464));
        }
        tmp_i4 = tmp_i4 + 1;
        tmp_pu5 = tmp_pu5 + 0x600;
        tmp_i3 = g_unk_00abe8a8;
        if (g_unk_00abe8a8 <= tmp_i4) {
          return;
        }
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu5 = tmp_pu5 + 0x600;
    } while (tmp_i4 < tmp_i3);
  }
  return;
}

void G_LinkDebris(void)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  float *pfVar4;
  int tmp_i5;
  
  if (0 < g_unk_02a9a694) {
    tmp_i5 = 0;
    pfVar4 = (float *)&g_unk_02a9a6a8;
    do {
      tmp_u2 = BG_StringHashValue(pfVar4 + 3);
      tmp_i3 = G_FindByTargetnameFast(0,pfVar4 + 3,tmp_u2);
      if (tmp_i3 == 0) {
        G_Error("ERROR: func_debris with no target");
      }
      tmp_f1 = *pfVar4;
      tmp_i5 = tmp_i5 + 1;
      *pfVar4 = *(float *)(tmp_i3 + 0x5c) - pfVar4[-4];
      pfVar4[1] = *(float *)(tmp_i3 + 0x60) - pfVar4[-3];
      pfVar4[2] = *(float *)(tmp_i3 + 100) - pfVar4[-2];
      VectorNormalize(pfVar4);
      *pfVar4 = *pfVar4 * tmp_f1;
      pfVar4[1] = pfVar4[1] * tmp_f1;
      pfVar4[2] = tmp_f1 * pfVar4[2];
      trap_SnapVector(pfVar4);
      pfVar4 = pfVar4 + 0x17;
    } while (tmp_i5 < g_unk_02a9a694);
  }
  return;
}

void G_refPrintf_constprop_4(uint32_t param_1,char *param_2)
{
  uint32_t tmp_u1;
  char local_40c [1028];
  
  vsnprintf(local_40c,0x400,param_2,&stack0x0000000c);
  tmp_u1 = va(&g_unk_0026fe3c,local_40c);
  trap_Printf(tmp_u1);
  return;
}

void G_refHelp_cmd(int param_1)
{
  int tmp_i1;
  
  if (param_1 != 0) {
    tmp_i1 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand(tmp_i1,"print \"\n^3Referee commands:^7\n\"");
    trap_SendServerCommand(tmp_i1,"print \"------------------------------------------\n\"");
    G_voteHelp(param_1,0);
    trap_SendServerCommand
              (tmp_i1,
               "print \"\n^5allready         putallies^7 <pid>  ^5speclock          warmup\n\"");
    trap_SendServerCommand
              (tmp_i1,
               "print \"^5lock             putaxis^7 <pid>    ^5specunlock        warn ^7<pid>\n\"")
    ;
    trap_SendServerCommand
              (tmp_i1,
               "print \"^5help             remove^7 <pid>     ^5unlock            mute ^7<pid>\n\"")
    ;
    trap_SendServerCommand(tmp_i1,"print \"^5pause            unpause           unmute ^7<pid>\n\"");
    trap_SendServerCommand(tmp_i1,"print \"Usage: ^3\\ref <cmd> [params]\n\n\"");
    return;
  }
  G_Printf("\nAdditional console commands:\n");
  G_Printf("----------------------------------------------\n");
  G_Printf("allready    putallies <pid>     unlock\n");
  G_Printf("lock        putaxis <pid>       unpause\n");
  G_Printf("help        warmup [value]\n");
  G_Printf("pause       speclock            warn <pid>\n");
  G_Printf("specunlock  remove <pid>\n\n");
  G_Printf("Usage: <cmd> [params]\n\n");
  return;
}

void G_refSpeclockTeams_cmd(uint32_t param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  
  tmp_i1 = TeamCount(0xffffffff,1);
  tmp_i2 = 0;
  if (tmp_i1 != 0) {
    tmp_i2 = param_2;
  }
  G_updateSpecLock(1,tmp_i2);
  tmp_i1 = TeamCount(0xffffffff,2);
  tmp_i2 = 0;
  if (tmp_i1 != 0) {
    tmp_i2 = param_2;
  }
  G_updateSpecLock(2,tmp_i2);
  if (param_2 == 0) {
    tmp_u3 = va("Referee has ^3SPECTATOR %sLOCKED^7 teams",&g_unk_0024805d);
    G_printFull(tmp_u3,param_1);
    g_unk_02a99a80 = g_unk_02a99a80 & 0xffffffbf;
  }
  else {
    tmp_u3 = va("Referee has ^3SPECTATOR %sLOCKED^7 teams",&g_unk_0026ea14);
    G_printFull(tmp_u3,param_1);
    g_unk_02a99a80 = g_unk_02a99a80 | 0x40;
  }
  tmp_u3 = va(&g_unk_00245ee9,g_unk_02a99a80);
  trap_SetConfigstring(0x1d,tmp_u3);
  return;
}

void G_refPrintf(int param_1,char *param_2)
{
  uint32_t tmp_u1;
  char local_40c [1024];
  
  vsnprintf(local_40c,0x400,param_2,&stack0x0000000c);
  if (param_1 == 0) {
    tmp_u1 = va(&g_unk_0026fe3c,local_40c);
    trap_Printf(tmp_u1);
  }
  else {
    tmp_u1 = va("print \"%s\n\"",local_40c);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
  }
  return;
}

void G_refAllReady_cmd(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  int *tmp_pi4;
  
  tmp_i2 = level;
  if (GHIDRA_FIELD(g_gamestate, 12, 4) != 0) {
    if (0 < g_unk_00abe93c) {
      tmp_pi3 = &g_unk_00abe944;
      tmp_pi4 = &g_unk_00abe944 + g_unk_00abe93c;
      do {
        tmp_i1 = *tmp_pi3;
        tmp_pi3 = tmp_pi3 + 1;
        *(uint32_t *)(tmp_i2 + 0x998 + tmp_i1 * 0x54dc) = 1;
      } while (tmp_pi3 != tmp_pi4);
    }
    g_unk_02a99a7c = 1;
    G_readyMatchState();
    return;
  }
  G_refPrintf(param_1,"Match already in progress!");
  return;
}

void G_refLockTeams_cmd(uint32_t param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = TeamCount(0xffffffff,1);
  GHIDRA_FIELD(teamInfo, 20, 4) = 0;
  if (tmp_i1 != 0) {
    GHIDRA_FIELD(teamInfo, 20, 4) = param_2;
  }
  tmp_i1 = TeamCount(0xffffffff,2);
  GHIDRA_FIELD(teamInfo, 36, 4) = 0;
  if (tmp_i1 != 0) {
    GHIDRA_FIELD(teamInfo, 36, 4) = param_2;
  }
  if (param_2 == 0) {
    tmp_u2 = va("Referee has ^3%sLOCKED^7 teams",&g_unk_0024805d);
    G_printFull(tmp_u2,param_1);
    G_refPrintf(param_1,"You have %sLOCKED teams\n",&g_unk_0024805d);
    g_unk_02a99a80 = g_unk_02a99a80 & 0xffffffdf;
  }
  else {
    tmp_u2 = va("Referee has ^3%sLOCKED^7 teams",&g_unk_0026ea14);
    G_printFull(tmp_u2,param_1);
    G_refPrintf(param_1,"You have %sLOCKED teams\n",&g_unk_0026ea14);
    g_unk_02a99a80 = g_unk_02a99a80 | 0x20;
  }
  tmp_u2 = va(&g_unk_00245ee9,g_unk_02a99a80);
  trap_SetConfigstring(0x1d,tmp_u2);
  return;
}

void G_refPause_cmd(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  uint8_t *local_24 [5];
  
  local_24[0] = &g_unk_0024805b;
  local_24[1] = &g_unk_00248060;
  tmp_pc3 = "Referee";
  if (param_1 == 0) {
    tmp_pc3 = "ref";
  }
  if (g_unk_02a99a78 < 2) {
    if ((param_2 != 0) && (g_unk_02a99a78 == 0)) {
      if (param_1 == 0) {
        g_unk_02a99a78 = 100;
      }
      else {
        tmp_i1 = G_cmdDebounce(param_1,"pause");
        if (tmp_i1 == 0) {
          return;
        }
        g_unk_02a99a78 = (param_1 + -0x93dea0 >> 9) * -0x55555555 + 100;
      }
      nitmod_Sound_Global(0xc);
      G_spawnPrintf(0,g_unk_00abe908 + 15000,0);
      tmp_u2 = va("print \"^3%s ^1PAUSED^3 the match^3!\n",tmp_pc3);
      trap_SendServerCommand(0xffffffff,tmp_u2);
      tmp_u2 = va("cp \"^3Match is ^1PAUSED^3! (^7%s^3)",tmp_pc3);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
      g_unk_02a99a80 = g_unk_02a99a80 | 0x10;
      tmp_u2 = va(&g_unk_00245ee9,g_unk_02a99a80);
      trap_SetConfigstring(0x1d,tmp_u2);
      return;
    }
  }
  else if (param_2 == 0) {
    if ((param_1 != 0) && (tmp_i1 = G_cmdDebounce(param_1,"unpause"), tmp_i1 == 0)) {
      return;
    }
    tmp_u2 = va("print \"\n^3%s ^5UNPAUSES^3 the match ... resuming in 10 seconds!\n\n\"",tmp_pc3);
    trap_SendServerCommand(0xffffffff,tmp_u2);
    g_unk_02a99a78 = 1;
    trap_SendServerCommand(0xffffffff,"an -1 0");
    G_spawnPrintf(1,g_unk_00abe908 + 10,0);
    return;
  }
  G_refPrintf(param_1,"The match is already %sPAUSED!",local_24[param_2]);
  return;
}

void G_refPlayerPut_cmd(uint32_t param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  uint8_t local_41c [1036];
  
  if ((int)GHIDRA_FIELD(g_gametype, 12, 4) < 2) {
    G_refPrintf(param_1,"\"put[allies|axis]\" only for team-based games!");
  }
  else {
    trap_Argv(2,local_41c,0x400);
    tmp_i1 = ClientNumberFromString(param_1,local_41c);
    if (tmp_i1 != -1) {
      tmp_i1 = tmp_i1 * 0x600;
      tmp_i2 = *(int *)(g_entities + tmp_i1 + 400);
      if (*(int *)(tmp_i2 + 3000) == param_2) {
        G_refPrintf(param_1,"\"%s\" is already on team %s!",tmp_i2 + 0x5f8,
                    *(uint32_t *)(aTeams + param_2 * 4));
      }
      else {
        if (GHIDRA_FIELD(team_maxplayers, 12, 4) != 0) {
          tmp_u3 = TeamCount(0xffffffff,param_2);
          if ((uint)GHIDRA_FIELD(team_maxplayers, 12, 4) <= tmp_u3) {
            G_refPrintf(param_1,"Sorry, the %s team is already full!",
                        *(uint32_t *)(aTeams + param_2 * 4));
            return;
          }
          tmp_i2 = *(int *)(g_entities + tmp_i1 + 400);
        }
        *(int *)(tmp_i2 + 0x98c) = param_2;
        *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 0x998) = 0;
        if (param_2 == 1) {
          SetTeam(g_entities + tmp_i1,"red",1,0xffffffff,0xffffffff,0);
        }
        else {
          SetTeam(g_entities + tmp_i1,&g_unk_0023bbe7,1,0xffffffff,0xffffffff,0);
        }
        if (GHIDRA_FIELD(g_gamestate, 12, 4) - 1 < 2) {
          G_readyMatchState();
        }
      }
    }
  }
  return;
}

void G_refRemove_cmd(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint8_t local_41c [1036];
  
  if ((int)GHIDRA_FIELD(g_gametype, 12, 4) < 2) {
    G_refPrintf(param_1,"\"remove\" only for team-based games!");
  }
  else {
    trap_Argv(2,local_41c,0x400);
    tmp_i2 = ClientNumberFromString(param_1,local_41c);
    if (tmp_i2 != -1) {
      tmp_i4 = tmp_i2 * 0x600;
      tmp_i1 = *(int *)(*(int *)(g_entities + tmp_i4 + 400) + 3000);
      if (tmp_i1 == 3) {
        G_refPrintf(param_1,"You can only remove people in the game!");
      }
      else {
        tmp_u3 = va("cp \"%s\n^7removed from team %s\n\"",*(int *)(g_entities + tmp_i4 + 400) + 0x5f8,
                   *(uint32_t *)(aTeams + tmp_i1 * 4));
        trap_SendServerCommand(0xffffffff,tmp_u3);
        tmp_u3 = va("print \"^5You\'ve been removed from the %s team\n\"",
                   *(uint32_t *)(aTeams + *(int *)(*(int *)(g_entities + tmp_i4 + 400) + 3000) * 4)
                  );
        trap_SendServerCommand(tmp_i2,tmp_u3);
        SetTeam(g_entities + tmp_i4,&g_unk_0024e6ea,1,0xffffffff,0xffffffff,0);
        if (GHIDRA_FIELD(g_gamestate, 12, 4) - 1 < 2) {
          G_readyMatchState();
        }
      }
    }
  }
  return;
}

void G_refWarmup_cmd(uint32_t param_1)
{
  long tmp_l1;
  uint32_t tmp_u2;
  char local_40c [1024];
  uint32_t uStack_c;
  
  uStack_c = 0xb95cc;
  trap_Argv(2,local_40c,0x400);
  if (local_40c[0] != '\0') {
    tmp_l1 = strtol(local_40c,(char **)0x0,10);
    if (-1 < tmp_l1) {
      tmp_l1 = strtol(local_40c,(char **)0x0,10);
      tmp_u2 = va(&g_unk_00245ee9,tmp_l1);
      trap_Cvar_Set("g_warmup",tmp_u2);
      return;
    }
  }
  trap_Cvar_VariableStringBuffer("g_warmup",local_40c,0x400);
  tmp_l1 = strtol(local_40c,(char **)0x0,10);
  G_refPrintf(param_1,"Warmup Time: %d",tmp_l1);
  return;
}

uint32_t G_refClientnumForName_part_1(uint32_t param_1,char *param_2)
{
  int tmp_i1;
  int tmp_i2;
  char local_41c [1032];
  uint32_t uStack_14;
  
  tmp_i2 = 0;
  uStack_14 = 0xb98ab;
  if (0 < g_unk_00abe938) {
    do {
      Q_strncpyz(local_41c,(&g_unk_00abe944)[tmp_i2] * 0x54dc + level + 0x5f8,0x400);
      Q_CleanStr(local_41c);
      tmp_i1 = strcmp(local_41c,param_2);
      if (tmp_i1 == 0) {
        return (&g_unk_00abe944)[tmp_i2];
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 < g_unk_00abe938);
  }
  G_refPrintf(param_1,"Client not on server.");
  return 0x40;
}

uint32_t G_refClientnumForName(uint32_t param_1,char *param_2)
{
  uint32_t tmp_u1;
  
  if (*param_2 == '\0') {
    return 0x40;
  }
  tmp_u1 = G_refClientnumForName_part_1();
  return tmp_u1;
}

uint32_t G_refCommandCheck(int param_1,byte *param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  int *tmp_pi4;
  byte *tmp_pb5;
  byte *tmp_pb6;
  bool tmp_b7;
  bool tmp_b8;
  bool tmp_b9;
  
  tmp_i3 = level;
  tmp_i2 = 9;
  tmp_b7 = &stack0xfffffff4 < &g_unk_00000020;
  tmp_b9 = &stack0x00000000 == &g_unk_0000002c;
  tmp_pb5 = param_2;
  tmp_pb6 = (byte *)"allready";
  do {
    if (tmp_i2 == 0) break;
    tmp_i2 = tmp_i2 + -1;
    tmp_b7 = *tmp_pb5 < *tmp_pb6;
    tmp_b9 = *tmp_pb5 == *tmp_pb6;
    tmp_pb5 = tmp_pb5 + 1;
    tmp_pb6 = tmp_pb6 + 1;
  } while (tmp_b9);
  if (tmp_b9) {
    if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
      G_refPrintf();
      return 1;
    }
    if (0 < g_unk_00abe93c) {
      tmp_pi1 = &g_unk_00abe944;
      tmp_pi4 = &g_unk_00abe944 + g_unk_00abe93c;
      do {
        tmp_i2 = *tmp_pi1;
        tmp_pi1 = tmp_pi1 + 1;
        *(uint32_t *)(tmp_i3 + 0x998 + tmp_i2 * 0x54dc) = 1;
      } while (tmp_pi1 != tmp_pi4);
    }
    g_unk_02a99a7c = 1;
    G_readyMatchState();
    return 1;
  }
  tmp_i3 = 5;
  tmp_b9 = false;
  tmp_pb5 = param_2;
  tmp_pb6 = (byte *)0x2606e0;
  do {
    if (tmp_i3 == 0) break;
    tmp_i3 = tmp_i3 + -1;
    tmp_b7 = *tmp_pb5 < *tmp_pb6;
    tmp_b9 = *tmp_pb5 == *tmp_pb6;
    tmp_pb5 = tmp_pb5 + 1;
    tmp_pb6 = tmp_pb6 + 1;
  } while (tmp_b9);
  if (tmp_b9) {
    tmp_i3 = TeamCount();
    GHIDRA_FIELD(teamInfo, 20, 4) = ZEXT14(tmp_i3 != 0);
    tmp_i3 = TeamCount();
    GHIDRA_FIELD(teamInfo, 36, 4) = ZEXT14(tmp_i3 != 0);
    va();
    G_printFull();
    G_refPrintf();
    g_unk_02a99a80 = g_unk_02a99a80 | 0x20;
  }
  else {
    tmp_i3 = 5;
    tmp_b9 = false;
    tmp_pb5 = param_2;
    tmp_pb6 = &g_unk_0024e755;
    do {
      if (tmp_i3 == 0) break;
      tmp_i3 = tmp_i3 + -1;
      tmp_b7 = *tmp_pb5 < *tmp_pb6;
      tmp_b9 = *tmp_pb5 == *tmp_pb6;
      tmp_pb5 = tmp_pb5 + 1;
      tmp_pb6 = tmp_pb6 + 1;
    } while (tmp_b9);
    if (tmp_b9) {
      G_refHelp_cmd();
      return 1;
    }
    tmp_i3 = 6;
    tmp_b9 = false;
    tmp_pb5 = param_2;
    tmp_pb6 = (byte *)0x248203;
    do {
      if (tmp_i3 == 0) break;
      tmp_i3 = tmp_i3 + -1;
      tmp_b7 = *tmp_pb5 < *tmp_pb6;
      tmp_b9 = *tmp_pb5 == *tmp_pb6;
      tmp_pb5 = tmp_pb5 + 1;
      tmp_pb6 = tmp_pb6 + 1;
    } while (tmp_b9);
    if (tmp_b9) {
      G_refPause_cmd();
      return 1;
    }
    tmp_i3 = 10;
    tmp_b9 = false;
    tmp_pb5 = param_2;
    tmp_pb6 = (byte *)"putallies";
    do {
      if (tmp_i3 == 0) break;
      tmp_i3 = tmp_i3 + -1;
      tmp_b7 = *tmp_pb5 < *tmp_pb6;
      tmp_b9 = *tmp_pb5 == *tmp_pb6;
      tmp_pb5 = tmp_pb5 + 1;
      tmp_pb6 = tmp_pb6 + 1;
    } while (tmp_b9);
    if (tmp_b9) {
      G_refPlayerPut_cmd();
      return 1;
    }
    tmp_i3 = 8;
    tmp_b9 = false;
    tmp_pb5 = param_2;
    tmp_pb6 = (byte *)"putaxis";
    do {
      if (tmp_i3 == 0) break;
      tmp_i3 = tmp_i3 + -1;
      tmp_b7 = *tmp_pb5 < *tmp_pb6;
      tmp_b9 = *tmp_pb5 == *tmp_pb6;
      tmp_pb5 = tmp_pb5 + 1;
      tmp_pb6 = tmp_pb6 + 1;
    } while (tmp_b9);
    if (tmp_b9) {
      G_refPlayerPut_cmd();
      return 1;
    }
    tmp_i3 = 7;
    tmp_b9 = false;
    tmp_pb5 = param_2;
    tmp_pb6 = (byte *)"remove";
    do {
      if (tmp_i3 == 0) break;
      tmp_i3 = tmp_i3 + -1;
      tmp_b7 = *tmp_pb5 < *tmp_pb6;
      tmp_b9 = *tmp_pb5 == *tmp_pb6;
      tmp_pb5 = tmp_pb5 + 1;
      tmp_pb6 = tmp_pb6 + 1;
    } while (tmp_b9);
    if (tmp_b9) {
      G_refRemove_cmd();
      return 1;
    }
    tmp_i3 = 9;
    tmp_b9 = false;
    tmp_pb5 = param_2;
    tmp_pb6 = (byte *)"speclock";
    do {
      if (tmp_i3 == 0) break;
      tmp_i3 = tmp_i3 + -1;
      tmp_b7 = *tmp_pb5 < *tmp_pb6;
      tmp_b9 = *tmp_pb5 == *tmp_pb6;
      tmp_pb5 = tmp_pb5 + 1;
      tmp_pb6 = tmp_pb6 + 1;
    } while (tmp_b9);
    if (tmp_b9) {
      TeamCount();
      G_updateSpecLock();
      TeamCount();
      G_updateSpecLock();
      va();
      G_printFull();
      g_unk_02a99a80 = g_unk_02a99a80 | 0x40;
    }
    else {
      tmp_i3 = 0xb;
      tmp_b9 = false;
      tmp_pb5 = param_2;
      tmp_pb6 = (byte *)"specunlock";
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_b7 = *tmp_pb5 < *tmp_pb6;
        tmp_b9 = *tmp_pb5 == *tmp_pb6;
        tmp_pb5 = tmp_pb5 + 1;
        tmp_pb6 = tmp_pb6 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        TeamCount();
        G_updateSpecLock();
        TeamCount();
        G_updateSpecLock();
        va();
        G_printFull();
        g_unk_02a99a80 = g_unk_02a99a80 & 0xffffffbf;
      }
      else {
        tmp_i3 = 7;
        tmp_b9 = false;
        tmp_pb5 = param_2;
        tmp_pb6 = (byte *)0x2481d3;
        do {
          if (tmp_i3 == 0) break;
          tmp_i3 = tmp_i3 + -1;
          tmp_b7 = *tmp_pb5 < *tmp_pb6;
          tmp_b9 = *tmp_pb5 == *tmp_pb6;
          tmp_pb5 = tmp_pb5 + 1;
          tmp_pb6 = tmp_pb6 + 1;
        } while (tmp_b9);
        if (!tmp_b9) {
          tmp_i3 = 8;
          tmp_b9 = false;
          tmp_pb5 = param_2;
          tmp_pb6 = (byte *)"unpause";
          do {
            if (tmp_i3 == 0) break;
            tmp_i3 = tmp_i3 + -1;
            tmp_b7 = *tmp_pb5 < *tmp_pb6;
            tmp_b9 = *tmp_pb5 == *tmp_pb6;
            tmp_pb5 = tmp_pb5 + 1;
            tmp_pb6 = tmp_pb6 + 1;
          } while (tmp_b9);
          tmp_b8 = (!tmp_b7 && !tmp_b9) < tmp_b7;
          if ((!tmp_b7 && !tmp_b9) != tmp_b7) {
            tmp_i3 = 7;
            tmp_b7 = false;
            tmp_pb5 = param_2;
            tmp_pb6 = (byte *)0x248d12;
            do {
              if (tmp_i3 == 0) break;
              tmp_i3 = tmp_i3 + -1;
              tmp_b8 = *tmp_pb5 < *tmp_pb6;
              tmp_b7 = *tmp_pb5 == *tmp_pb6;
              tmp_pb5 = tmp_pb5 + 1;
              tmp_pb6 = tmp_pb6 + 1;
            } while (tmp_b7);
            if (tmp_b7) {
              G_refWarmup_cmd();
              return 1;
            }
            tmp_i3 = 5;
            tmp_b7 = false;
            tmp_pb5 = param_2;
            tmp_pb6 = &g_unk_0024962a;
            do {
              if (tmp_i3 == 0) break;
              tmp_i3 = tmp_i3 + -1;
              tmp_b8 = *tmp_pb5 < *tmp_pb6;
              tmp_b7 = *tmp_pb5 == *tmp_pb6;
              tmp_pb5 = tmp_pb5 + 1;
              tmp_pb6 = tmp_pb6 + 1;
            } while (tmp_b7);
            if (tmp_b7) {
              G_refWarning_cmd();
              return 1;
            }
            tmp_i3 = 5;
            tmp_b7 = false;
            tmp_pb5 = param_2;
            tmp_pb6 = (byte *)0x24e775;
            do {
              if (tmp_i3 == 0) break;
              tmp_i3 = tmp_i3 + -1;
              tmp_b8 = *tmp_pb5 < *tmp_pb6;
              tmp_b7 = *tmp_pb5 == *tmp_pb6;
              tmp_pb5 = tmp_pb5 + 1;
              tmp_pb6 = tmp_pb6 + 1;
            } while (tmp_b7);
            if (tmp_b7) {
              G_refMute_cmd();
              return 1;
            }
            tmp_i3 = 7;
            tmp_b7 = false;
            tmp_pb5 = (byte *)"unmute";
            do {
              if (tmp_i3 == 0) break;
              tmp_i3 = tmp_i3 + -1;
              tmp_b8 = *param_2 < *tmp_pb5;
              tmp_b7 = *param_2 == *tmp_pb5;
              param_2 = param_2 + 1;
              tmp_pb5 = tmp_pb5 + 1;
            } while (tmp_b7);
            if ((!tmp_b8 && !tmp_b7) == tmp_b8) {
              G_refMute_cmd();
              return 1;
            }
            return 0;
          }
          if (param_1 == 0) {
            if (g_unk_02a99a78 < 2) goto LAB_000ba1c2;
          }
          else {
            if (g_unk_02a99a78 < 2) {
LAB_000ba1c2:
              G_refPrintf();
              return 1;
            }
            tmp_i3 = G_cmdDebounce();
            if (tmp_i3 == 0) {
              return 1;
            }
          }
          va();
          trap_SendServerCommand();
          g_unk_02a99a78 = 1;
          trap_SendServerCommand();
          G_spawnPrintf();
          return 1;
        }
        TeamCount();
        GHIDRA_FIELD(teamInfo, 20, 4) = 0;
        TeamCount();
        GHIDRA_FIELD(teamInfo, 36, 4) = 0;
        va();
        G_printFull();
        G_refPrintf();
        g_unk_02a99a80 = g_unk_02a99a80 & 0xffffffdf;
      }
    }
  }
  va();
  trap_SetConfigstring();
  return 1;
}

void G_ref_cmd(int param_1)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint tmp_u4;
  uint32_t *tmp_pu5;
  char *tmp_pc6;
  uint32_t *tmp_pu7;
  bool tmp_b8;
  byte tmp_b9;
  char local_944 [1024];
  uint32_t local_544;
  uint32_t local_540 [332];
  
  tmp_b9 = 0;
  if ((param_1 == 0) || (tmp_b8 = *(int *)(*(int *)(param_1 + 400) + 0xc80) == 0, !tmp_b8)) {
    trap_Argv(1,local_944,0x400);
    tmp_pu7 = &local_544;
    tmp_u4 = 0x528;
    tmp_pu5 = &g_unk_00abea4c;
    if (((uint)tmp_pu7 & 4) != 0) {
      local_544 = g_unk_00abea4c;
      tmp_pu7 = local_540;
      tmp_u4 = 0x524;
      tmp_pu5 = &g_unk_00abea50;
    }
    for (tmp_u4 = tmp_u4 >> 2; tmp_u4 != 0; tmp_u4 = tmp_u4 - 1) {
      *tmp_pu7 = *tmp_pu5;
      tmp_pu5 = tmp_pu5 + (uint)tmp_b9 * -2 + 1;
      tmp_pu7 = tmp_pu7 + (uint)tmp_b9 * -2 + 1;
    }
    tmp_i3 = Cmd_CallVote_f(param_1,0,1);
    if (tmp_i3 == 0) {
      g_unk_00abea4c = local_544;
      tmp_pu5 = local_540;
      tmp_pu7 = &g_unk_00abea50;
      for (tmp_i3 = 0x149; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
        *tmp_pu7 = *tmp_pu5;
        tmp_pu5 = tmp_pu5 + (uint)tmp_b9 * -2 + 1;
        tmp_pu7 = tmp_pu7 + (uint)tmp_b9 * -2 + 1;
      }
      tmp_i3 = G_refCommandCheck(param_1,local_944);
      if (tmp_i3 == 0) {
        G_refHelp_cmd(param_1);
      }
    }
    else {
      g_unk_00abea4c = local_544;
      tmp_pu5 = local_540;
      tmp_pu7 = &g_unk_00abea50;
      for (tmp_i3 = 0x149; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
        *tmp_pu7 = *tmp_pu5;
        tmp_pu5 = tmp_pu5 + (uint)tmp_b9 * -2 + 1;
        tmp_pu7 = tmp_pu7 + (uint)tmp_b9 * -2 + 1;
      }
    }
  }
  else {
    tmp_i3 = 5;
    tmp_pc1 = refereePassword + 0x10;
    tmp_pc6 = "none";
    do {
      if (tmp_i3 == 0) break;
      tmp_i3 = tmp_i3 + -1;
      tmp_b8 = *tmp_pc1 == *tmp_pc6;
      tmp_pc1 = tmp_pc1 + 1;
      tmp_pc6 = tmp_pc6 + 1;
    } while (tmp_b8);
    if ((tmp_b8) || (refereePassword[0x10] == '\0')) {
      tmp_pc1 = "print \"Sorry, referee status disabled on this server.\n\"";
    }
    else {
      tmp_i3 = trap_Argc();
      if (tmp_i3 < 2) {
        tmp_pc1 = "print \"Usage: ref [password]\n\"";
      }
      else {
        trap_Argv(1,local_944,0x400);
        tmp_i3 = strcmp(local_944,refereePassword + 0x10);
        if (tmp_i3 == 0) {
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xc80) = 1;
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xc88) = 3;
          tmp_u2 = va("cp \"%s\n^3has become a referee\n\"",*(int *)(param_1 + 400) + 0x5f8);
          trap_SendServerCommand(0xffffffff,tmp_u2);
          ClientUserinfoChanged((param_1 + -0x93e4a0 >> 9) * -0x55555555);
          return;
        }
        tmp_pc1 = "print \"Invalid referee password!\n\"";
      }
    }
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc1);
  }
  return;
}

void G_ModifyTOI(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  uint tmp_u5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint8_t *tmp_pu8;
  double tmp_d9;
  int local_844;
  int local_840;
  uint8_t *local_83c;
  char *local_828;
  uint32_t local_824;
  uint32_t local_820;
  uint32_t local_81c;
  uint32_t local_818 [255];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xc5b7d;
  local_81c = 0;
  tmp_u4 = 0;
  do {
    tmp_u5 = tmp_u4;
    *(uint32_t *)((int)local_818 + tmp_u5) = 0;
    *(uint32_t *)((int)local_818 + tmp_u5 + 4) = 0;
    tmp_u4 = tmp_u5 + 8;
  } while (tmp_u5 + 8 < 0x3f8);
  *(uint32_t *)((int)local_818 + tmp_u5 + 8) = 0;
  nitrox_GetConfigstring(*(int *)(param_1 + 0x108) + 0x261,local_41c,0x400);
  tmp_i6 = G_SpawnStringExt("customimage",&g_unk_0026ea14,&local_824,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script_actions.c",
                           0xf63);
  if (tmp_i6 == 0) {
    tmp_i6 = G_SpawnStringExt("customaxisimage",&g_unk_0026ea14,&local_824,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script_actions.c",
                             0xf66);
    local_844 = 0;
    if (tmp_i6 != 0) {
      local_844 = G_ShaderIndex(local_824);
    }
    tmp_i6 = G_SpawnStringExt("customalliesimage",&g_unk_0026ea14,&local_824,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script_actions.c",
                             0xf6c);
    if (tmp_i6 == 0) {
      tmp_i6 = G_SpawnStringExt("customalliedimage",&g_unk_0026ea14,&local_824,
                               "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script_actions.c"
                               ,0xf6e);
      local_840 = 0;
      if (tmp_i6 == 0) goto LAB_000c5c33;
    }
    local_840 = G_ShaderIndex(local_824);
  }
  else {
    local_844 = G_ShaderIndex(local_824);
    local_840 = local_844;
  }
LAB_000c5c33:
  local_83c = &g_unk_0026ea14;
  tmp_u7 = va("%i",(param_1 + -0x93e4a0 >> 9) * -0x55555555);
  Info_SetValueForKey(local_41c,&g_unk_0025feb2,tmp_u7);
  tmp_i6 = G_SpawnIntExt("objflags",&g_unk_0024bfa6,&local_820,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script_actions.c",0xf77)
  ;
  if (tmp_i6 != 0) {
    tmp_u7 = va("%i",local_820);
    Info_SetValueForKey(local_41c,&g_unk_0024d8f6,tmp_u7);
  }
  if (local_844 != 0) {
    tmp_u7 = va("%i",local_844);
    Info_SetValueForKey(local_41c,"r",tmp_u7);
  }
  if (local_840 != 0) {
    tmp_u7 = va("%i",local_840);
    Info_SetValueForKey(local_41c,&g_unk_0026dcfc,tmp_u7);
  }
  tmp_u7 = va("%i",*(uint32_t *)(param_1 + 0x1a8));
  Info_SetValueForKey(local_41c,&g_unk_0024e6ea,tmp_u7);
  tmp_pu8 = *(uint8_t **)(param_1 + 0x248);
  if (*(uint8_t **)(param_1 + 0x248) == (uint8_t *)0x0) {
    tmp_pu8 = local_83c;
  }
  Info_SetValueForKey(local_41c,&g_unk_0023bf57,tmp_pu8);
  tmp_i6 = G_SpawnStringExt("score",&g_unk_0024bfa6,&local_828,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script_actions.c",
                           0xf81);
  if (tmp_i6 != 0) {
    tmp_d9 = strtod(local_828,(char **)0x0);
    *(float *)(param_1 + 0x3fc) = (float)tmp_d9;
  }
  Q_strncpyz(&local_81c,*(uint32_t *)(param_1 + 0x3a8),4);
  Nit_RemoveWordInString(&local_81c,&g_unk_00251d18);
  if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
    Info_SetValueForKey(local_41c,&g_unk_0026176c,&local_81c);
  }
  if (((*(float *)(param_1 + 0x5c) == 0.0) && (*(float *)(param_1 + 0x60) == 0.0)) &&
     (*(float *)(param_1 + 100) == 0.0)) {
    tmp_f2 = *(float *)(param_1 + 0x154);
    tmp_f3 = *(float *)(param_1 + 0x160);
    tmp_f1 = (*(float *)(param_1 + 0x158) + *(float *)(param_1 + 0x164)) * 0.5;
    tmp_u7 = va("%i",(int)ROUND((*(float *)(param_1 + 0x150) + *(float *)(param_1 + 0x15c)) * 0.5));
    Info_SetValueForKey(local_41c,&g_unk_0026019a,tmp_u7);
    tmp_u7 = va("%i",(int)ROUND((tmp_f2 + tmp_f3) * 0.5));
    Info_SetValueForKey(local_41c,&g_unk_0025d431,tmp_u7);
  }
  else {
    tmp_u7 = va("%i",(int)ROUND(*(float *)(param_1 + 0x5c)));
    Info_SetValueForKey(local_41c,&g_unk_0026019a,tmp_u7);
    tmp_u7 = va("%i",(int)ROUND(*(float *)(param_1 + 0x60)));
    Info_SetValueForKey(local_41c,&g_unk_0025d431,tmp_u7);
    tmp_f1 = *(float *)(param_1 + 100);
  }
  tmp_u7 = va("%i",(int)ROUND(tmp_f1));
  Info_SetValueForKey(local_41c,&g_unk_0026047e,tmp_u7);
  if (*(int *)(param_1 + 0x254) == 0) {
    trap_LinkEntity(param_1);
  }
  else {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 300;
    *(void **)(param_1 + 0x2a4) = Think_SetupObjectiveInfo;
  }
  tmp_u7 = va("%i",*(uint32_t *)(param_1 + 0x108));
  Info_SetValueForKey(local_41c,"i",tmp_u7);
  nitrox_SetConfigstring(*(int *)(param_1 + 0x108) + 0x261,local_41c);
  return;
}

void G_WriteClientSessionData(int param_1,int param_2)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  uint32_t tmp_u7;
  uint32_t tmp_u8;
  uint32_t tmp_u9;
  uint32_t tmp_u10;
  uint32_t tmp_u11;
  uint32_t tmp_u12;
  uint32_t tmp_u13;
  uint32_t tmp_u14;
  uint32_t tmp_u15;
  uint32_t tmp_u16;
  uint32_t tmp_u17;
  int tmp_i18;
  
  tmp_i18 = param_1 + 0xf48;
  G_deleteStats((param_1 - level >> 2) * -0x66e64f79);
  tmp_u4 = *(uint32_t *)(param_1 + 0xf40);
  tmp_u5 = *(uint32_t *)(param_1 + 0xf44);
  tmp_u9 = *(uint32_t *)(param_1 + 0xbe4);
  tmp_u17 = *(uint32_t *)(param_1 + 0xf3c);
  tmp_u16 = *(uint32_t *)(param_1 + 0xf38);
  tmp_u15 = *(uint32_t *)(param_1 + 0xf34);
  tmp_u14 = *(uint32_t *)(param_1 + 0xf30);
  tmp_u13 = *(uint32_t *)(param_1 + 0xf2c);
  tmp_u12 = *(uint32_t *)(param_1 + 0xecc);
  tmp_u11 = *(uint32_t *)(param_1 + 0xf14);
  tmp_u10 = *(uint32_t *)(param_1 + 0xca8);
  tmp_u1 = 0;
  if (param_2 != 0) {
    tmp_u1 = *(uint32_t *)(param_1 + 0xbd4);
  }
  tmp_u8 = *(uint32_t *)(param_1 + 0x674);
  tmp_u7 = *(uint32_t *)(param_1 + 0xbec);
  tmp_u6 = *(uint32_t *)(param_1 + 0xbe8);
  tmp_u2 = va("%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %s"
             ,*(uint32_t *)(param_1 + 3000),*(uint32_t *)(param_1 + 0xbbc),
             *(uint32_t *)(param_1 + 0xbc0),*(uint32_t *)(param_1 + 0xbc4),
             *(uint32_t *)(param_1 + 0xbc8),*(uint32_t *)(param_1 + 0xbcc),
             *(uint32_t *)(param_1 + 0xbd0),*(uint32_t *)(param_1 + 0xbd8),
             *(uint32_t *)(param_1 + 0xbdc),*(uint32_t *)(param_1 + 0xbe0),
             *(uint32_t *)(param_1 + 0xc74),*(uint32_t *)(param_1 + 0xc78),
             *(uint32_t *)(param_1 + 0xc7c),*(uint32_t *)(param_1 + 0xc80),
             *(uint32_t *)(param_1 + 0xc88),*(uint32_t *)(param_1 + 0xc8c),
             *(uint32_t *)(param_1 + 0xc90),*(uint32_t *)(param_1 + 0xc98),
             *(uint32_t *)(param_1 + 0xec8),*(uint32_t *)(param_1 + 0xbf0),
             *(uint32_t *)(param_1 + 0xca4),tmp_u6,tmp_u7,tmp_u8,tmp_u1,tmp_u9,tmp_u10,tmp_u11,tmp_u12,
             tmp_u13,tmp_u14,tmp_u15,tmp_u16,tmp_u17,tmp_u4,tmp_u5,tmp_i18);
  tmp_u3 = va("session%i",(param_1 - level >> 2) * -0x66e64f79);
  trap_Cvar_Set(tmp_u3,tmp_u2);
  if (((param_2 != 0) && (g_unk_00abe8ac == 0)) && ((g_XPSave[0xc] & 2) == 0)) {
    return;
  }
  tmp_u4 = va("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %i %i %i %i %i %i %i",
             (double)*(float *)(param_1 + 0xbf4),(double)*(float *)(param_1 + 0xbf8),
             (double)*(float *)(param_1 + 0xbfc),(double)*(float *)(param_1 + 0xc00),
             (double)*(float *)(param_1 + 0xc04),(double)*(float *)(param_1 + 0xc08),
             (double)*(float *)(param_1 + 0xc0c),*(uint32_t *)(param_1 + 0xc50),
             *(uint32_t *)(param_1 + 0xc54),*(uint32_t *)(param_1 + 0xc58),
             *(uint32_t *)(param_1 + 0xc5c),*(uint32_t *)(param_1 + 0xc60),
             *(uint32_t *)(param_1 + 0xc64),*(uint32_t *)(param_1 + 0xc68),tmp_u6,tmp_u7,tmp_u8,
             tmp_u1,tmp_u9,tmp_u10,tmp_u11,tmp_u12,tmp_u13,tmp_u14,tmp_u15,tmp_u16,tmp_u17,tmp_u4,tmp_u5,tmp_i18)
  ;
  tmp_u5 = va("sessionstats%i",(param_1 - level >> 2) * -0x66e64f79);
  trap_Cvar_Set(tmp_u5,tmp_u4);
  return;
}

void G_ClientSwap(int param_1)
{
  uint tmp_u1;
  uint tmp_u2;
  
  if (*(int *)(param_1 + 3000) == 1) {
    *(uint32_t *)(param_1 + 3000) = 2;
  }
  else if (*(int *)(param_1 + 3000) == 2) {
    *(uint32_t *)(param_1 + 3000) = 1;
  }
  tmp_u2 = *(uint *)(param_1 + 0xc88) & 1;
  tmp_u1 = (-(uint)(tmp_u2 == 0) & 0xfffffffe) + 3;
  if ((*(uint *)(param_1 + 0xc88) & 2) == 0) {
    tmp_u1 = -tmp_u2 & 2;
  }
  *(uint *)(param_1 + 0xc88) = tmp_u1;
  tmp_u2 = *(uint *)(param_1 + 0xc8c) & 1;
  tmp_u1 = (-(uint)(tmp_u2 == 0) & 0xfffffffe) + 3;
  if ((*(uint *)(param_1 + 0xc8c) & 2) == 0) {
    tmp_u1 = -tmp_u2 & 2;
  }
  *(uint *)(param_1 + 0xc8c) = tmp_u1;
  return;
}

void G_CalcRank(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  
  tmp_i2 = 0;
  *(uint32_t *)(param_1 + 0xc4c) = 0;
  tmp_i3 = 0;
  do {
    G_SetPlayerSkill(param_1,tmp_i3);
    tmp_i1 = tmp_i3 * 4;
    tmp_i3 = tmp_i3 + 1;
    tmp_i2 = *(int *)(param_1 + 0xc30 + tmp_i1) + tmp_i2;
  } while (tmp_i3 != 7);
  if (tmp_i2 < g_unk_002bb384) {
    if (tmp_i2 < g_unk_002bb380) goto LAB_000c7075;
    if (*(int *)(param_1 + 0xc4c) < 10) {
      tmp_u4 = 9;
      goto LAB_000c7120;
    }
LAB_000c70d6:
    if (tmp_i2 < g_unk_002bb378) goto LAB_000c7087;
    tmp_u4 = 7;
    if (*(int *)(param_1 + 0xc4c) < 10) goto LAB_000c7120;
LAB_000c70e4:
    if (tmp_i2 < g_unk_002bb370) goto LAB_000c7099;
    if (*(int *)(param_1 + 0xc4c) < 10) {
      tmp_u4 = 5;
      goto LAB_000c7120;
    }
LAB_000c70f2:
    if (tmp_i2 < g_unk_002bb368) goto LAB_000c70ab;
    if (*(int *)(param_1 + 0xc4c) < 10) {
      tmp_u4 = 3;
      goto LAB_000c7120;
    }
  }
  else {
    if (*(int *)(param_1 + 0xc4c) < 10) {
      tmp_u4 = 10;
      goto LAB_000c7120;
    }
LAB_000c7075:
    if (tmp_i2 < g_unk_002bb37c) goto LAB_000c70d6;
    if (*(int *)(param_1 + 0xc4c) < 10) {
      tmp_u4 = 8;
      goto LAB_000c7120;
    }
LAB_000c7087:
    if (tmp_i2 < g_unk_002bb374) goto LAB_000c70e4;
    if (*(int *)(param_1 + 0xc4c) < 10) {
      tmp_u4 = 6;
      goto LAB_000c7120;
    }
LAB_000c7099:
    if (tmp_i2 < g_unk_002bb36c) goto LAB_000c70f2;
    if (*(int *)(param_1 + 0xc4c) < 10) {
      tmp_u4 = 4;
      goto LAB_000c7120;
    }
LAB_000c70ab:
    if (g_unk_002bb364 <= tmp_i2) {
      if (9 < *(int *)(param_1 + 0xc4c)) {
        return;
      }
      tmp_u4 = 2;
      goto LAB_000c7120;
    }
  }
  if ((tmp_i2 < rankTable) || (9 < *(int *)(param_1 + 0xc4c))) {
    return;
  }
  tmp_u4 = 1;
LAB_000c7120:
  *(uint32_t *)(param_1 + 0xc4c) = tmp_u4;
  return;
}

void G_ReadSessionData(int param_1)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  bool tmp_b6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  int tmp_i12;
  int tmp_i13;
  int tmp_i14;
  int tmp_i15;
  int tmp_i16;
  int tmp_i17;
  int tmp_i18;
  int tmp_i19;
  int tmp_i20;
  int tmp_i21;
  int tmp_i22;
  int tmp_i23;
  int tmp_i24;
  int tmp_i25;
  int tmp_i26;
  int tmp_i27;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xc717e;
  tmp_u1 = va("session%i",(param_1 - level >> 2) * -0x66e64f79);
  trap_Cvar_VariableStringBuffer(tmp_u1,local_41c,0x400);
  tmp_i4 = param_1 + 0xf48;
  tmp_i5 = param_1 + 0xf44;
  tmp_i27 = param_1 + 0xf40;
  tmp_i26 = param_1 + 0xf3c;
  tmp_i25 = param_1 + 0xf38;
  tmp_i24 = param_1 + 0xf34;
  tmp_i23 = param_1 + 0xf30;
  tmp_i22 = param_1 + 0xf2c;
  tmp_i21 = param_1 + 0xecc;
  tmp_i20 = param_1 + 0xf14;
  tmp_i19 = param_1 + 0xca8;
  tmp_i18 = param_1 + 0xbe4;
  tmp_i17 = param_1 + 0xbd4;
  tmp_i16 = param_1 + 0x674;
  tmp_i15 = param_1 + 0xbec;
  tmp_i14 = param_1 + 0xbe8;
  tmp_i13 = param_1 + 0xca4;
  tmp_i12 = param_1 + 0xbf0;
  tmp_i11 = param_1 + 0xec8;
  tmp_i10 = param_1 + 0xc98;
  tmp_i9 = param_1 + 0xc90;
  tmp_i8 = param_1 + 0xc8c;
  tmp_i7 = param_1 + 0xc88;
  __isoc99_sscanf(local_41c,
                  "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %s"
                  ,param_1 + 3000,param_1 + 0xbbc,param_1 + 0xbc0,param_1 + 0xbc4,param_1 + 0xbc8,
                  param_1 + 0xbcc,param_1 + 0xbd0,param_1 + 0xbd8,param_1 + 0xbdc,param_1 + 0xbe0,
                  param_1 + 0xc74,param_1 + 0xc78,param_1 + 0xc7c,param_1 + 0xc80,tmp_i7,tmp_i8,tmp_i9,
                  tmp_i10,tmp_i11,tmp_i12,tmp_i13,tmp_i14,tmp_i15,tmp_i16,tmp_i17,tmp_i18,tmp_i19,tmp_i20,
                  tmp_i21,tmp_i22,tmp_i23,tmp_i24,tmp_i25,tmp_i26,tmp_i27,tmp_i5,tmp_i4);
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 4) {
    tmp_b6 = false;
    if (*(int *)(g_campaigns + g_unk_02a98490 * 0x494 + 0x284) != 0) {
      tmp_b6 = g_unk_02a98494 == 0;
    }
LAB_000c7508:
    if ((GHIDRA_FIELD(g_XPSave, 12, 4) & 4) == 0) {
      if ((GHIDRA_FIELD(g_XPSave, 12, 4) & 2) != 0) goto joined_r0x000c76b0;
LAB_000c76c0:
      if (!tmp_b6) goto LAB_000c7390;
    }
    else if ((GHIDRA_FIELD(g_XPSave, 12, 4) & 2) != 0) {
      tmp_b6 = true;
joined_r0x000c76b0:
      if (GHIDRA_FIELD(g_reset, 12, 4) == 0) goto LAB_000c76c0;
    }
    tmp_u1 = va("sessionstats%i",(param_1 - level >> 2) * -0x66e64f79);
    trap_Cvar_VariableStringBuffer(tmp_u1,local_41c,0x400);
    __isoc99_sscanf(local_41c,"%f %f %f %f %f %f %f %i %i %i %i %i %i %i",param_1 + 0xbf4,
                    param_1 + 0xbf8,param_1 + 0xbfc,param_1 + 0xc00,param_1 + 0xc04,param_1 + 0xc08,
                    param_1 + 0xc0c,param_1 + 0xc50,param_1 + 0xc54,param_1 + 0xc58,param_1 + 0xc5c,
                    param_1 + 0xc60,param_1 + 0xc64,param_1 + 0xc68,tmp_i7,tmp_i8,tmp_i9,tmp_i10,tmp_i11,
                    tmp_i12,tmp_i13,tmp_i14,tmp_i15,tmp_i16,tmp_i17,tmp_i18,tmp_i19,tmp_i20,tmp_i21,tmp_i22,
                    tmp_i23,tmp_i24,tmp_i25,tmp_i26,tmp_i27,tmp_i5,tmp_i4);
  }
  else {
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
      tmp_b6 = GHIDRA_FIELD(g_currentRound, 12, 4) != 0;
      goto LAB_000c7508;
    }
    if (GHIDRA_FIELD(g_gametype, 12, 4) - 2 < 6) {
      tmp_b6 = false;
      goto LAB_000c7508;
    }
  }
LAB_000c7390:
  tmp_i4 = 0;
  *(uint32_t *)(param_1 + 0xc4c) = 0;
  tmp_i5 = 0;
  do {
    G_SetPlayerSkill(param_1,tmp_i5);
    tmp_i27 = tmp_i5 * 4;
    tmp_i5 = tmp_i5 + 1;
    tmp_i4 = *(int *)(param_1 + 0xc30 + tmp_i27) + tmp_i4;
  } while (tmp_i5 != 7);
  if (tmp_i4 < g_unk_002bb384) {
    if (tmp_i4 < g_unk_002bb380) goto LAB_000c73d9;
    if (*(int *)(param_1 + 0xc4c) < 10) {
      tmp_u1 = 9;
      goto LAB_000c7690;
    }
LAB_000c7636:
    if (tmp_i4 < g_unk_002bb378) {
LAB_000c73ef:
      if (tmp_i4 < g_unk_002bb374) goto LAB_000c7648;
      if (*(int *)(param_1 + 0xc4c) < 10) {
        tmp_u1 = 6;
        goto LAB_000c7690;
      }
LAB_000c7405:
      if (tmp_i4 < g_unk_002bb36c) goto LAB_000c765e;
      if (*(int *)(param_1 + 0xc4c) < 10) {
        tmp_u1 = 4;
        goto LAB_000c7690;
      }
LAB_000c741b:
      if (g_unk_002bb364 <= tmp_i4) {
        if (9 < *(int *)(param_1 + 0xc4c)) goto LAB_000c7431;
        tmp_u1 = 2;
        goto LAB_000c7690;
      }
    }
    else {
      tmp_u1 = 7;
      if (*(int *)(param_1 + 0xc4c) < 10) goto LAB_000c7690;
LAB_000c7648:
      if (tmp_i4 < g_unk_002bb370) goto LAB_000c7405;
      if (*(int *)(param_1 + 0xc4c) < 10) {
        tmp_u1 = 5;
        goto LAB_000c7690;
      }
LAB_000c765e:
      if (tmp_i4 < g_unk_002bb368) goto LAB_000c741b;
      if (*(int *)(param_1 + 0xc4c) < 10) {
        tmp_u1 = 3;
        goto LAB_000c7690;
      }
    }
    if ((tmp_i4 < rankTable) || (tmp_u1 = 1, 9 < *(int *)(param_1 + 0xc4c))) goto LAB_000c7431;
  }
  else {
    if (9 < *(int *)(param_1 + 0xc4c)) {
LAB_000c73d9:
      if (tmp_i4 < g_unk_002bb37c) goto LAB_000c7636;
      if (*(int *)(param_1 + 0xc4c) < 10) {
        tmp_u1 = 8;
        goto LAB_000c7690;
      }
      goto LAB_000c73ef;
    }
    tmp_u1 = 10;
  }
LAB_000c7690:
  *(uint32_t *)(param_1 + 0xc4c) = tmp_u1;
LAB_000c7431:
  if (((GHIDRA_FIELD(g_gametype, 12, 4) == 3) && (GHIDRA_FIELD(g_gamestate, 12, 4) != 0)) &&
     (GHIDRA_FIELD(g_altStopwatchMode, 12, 4) != 0 || GHIDRA_FIELD(g_currentRound, 12, 4) == 1)) {
    if (*(int *)(param_1 + 3000) == 1) {
      *(uint32_t *)(param_1 + 3000) = 2;
    }
    else if (*(int *)(param_1 + 3000) == 2) {
      *(uint32_t *)(param_1 + 3000) = 1;
    }
    tmp_u3 = *(uint *)(param_1 + 0xc88) & 1;
    tmp_u2 = (-(uint)(tmp_u3 == 0) & 0xfffffffe) + 3;
    if ((*(uint *)(param_1 + 0xc88) & 2) == 0) {
      tmp_u2 = -tmp_u3 & 2;
    }
    *(uint *)(param_1 + 0xc88) = tmp_u2;
    tmp_u3 = *(uint *)(param_1 + 0xc8c) & 1;
    tmp_u2 = (-(uint)(tmp_u3 == 0) & 0xfffffffe) + 3;
    if ((*(uint *)(param_1 + 0xc8c) & 2) == 0) {
      tmp_u2 = -tmp_u3 & 2;
    }
    *(uint *)(param_1 + 0xc8c) = tmp_u2;
  }
  if (GHIDRA_FIELD(g_swapteams, 12, 4) != 0) {
    trap_Cvar_Set("g_swapteams",&g_unk_0024bfa6);
    if (*(int *)(param_1 + 3000) == 1) {
      *(uint32_t *)(param_1 + 3000) = 2;
    }
    else if (*(int *)(param_1 + 3000) == 2) {
      *(uint32_t *)(param_1 + 3000) = 1;
    }
    tmp_u3 = *(uint *)(param_1 + 0xc88) & 1;
    tmp_u2 = (-(uint)(tmp_u3 == 0) & 0xfffffffe) + 3;
    if ((*(uint *)(param_1 + 0xc88) & 2) == 0) {
      tmp_u2 = -tmp_u3 & 2;
    }
    *(uint *)(param_1 + 0xc88) = tmp_u2;
    tmp_u3 = *(uint *)(param_1 + 0xc8c) & 1;
    tmp_u2 = (-(uint)(tmp_u3 == 0) & 0xfffffffe) + 3;
    if ((*(uint *)(param_1 + 0xc8c) & 2) == 0) {
      tmp_u2 = -tmp_u3 & 2;
    }
    *(uint *)(param_1 + 0xc8c) = tmp_u2;
  }
  *(float *)(param_1 + 0xc10) = *(float *)(param_1 + 0xbf4);
  *(float *)(param_1 + 0xc14) = *(float *)(param_1 + 0xbf8);
  *(float *)(param_1 + 0xc18) = *(float *)(param_1 + 0xbfc);
  *(float *)(param_1 + 0xc1c) = *(float *)(param_1 + 0xc00);
  *(float *)(param_1 + 0xc20) = *(float *)(param_1 + 0xc04);
  *(float *)(param_1 + 0xc24) = *(float *)(param_1 + 0xc08);
  *(float *)(param_1 + 0xc28) = *(float *)(param_1 + 0xc0c);
  *(float *)(param_1 + 0xc2c) =
       *(float *)(param_1 + 0xbf4) + 0.0 + *(float *)(param_1 + 0xbf8) + *(float *)(param_1 + 0xbfc)
       + *(float *)(param_1 + 0xc00) + *(float *)(param_1 + 0xc04) + *(float *)(param_1 + 0xc08) +
       *(float *)(param_1 + 0xc0c);
  return;
}

void G_InitSessionData(int param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint16_t *tmp_pu3;
  char *__nptr;
  long tmp_l4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  uint tmp_u7;
  uint tmp_u8;
  bool tmp_b9;
  
  *(uint32_t *)(param_1 + 3000) = 3;
  *(uint32_t *)(param_1 + 0xbc0) = 1;
  *(uint32_t *)(param_1 + 0xbc8) = 0;
  *(uint32_t *)(param_1 + 0xbd8) = 0;
  tmp_u5 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0xbec) = 0;
  tmp_u7 = 0x1c;
  *(uint32_t *)(param_1 + 0xbe8) = 0;
  *(uint32_t *)(param_1 + 0xbf0) = 0;
  *(uint32_t *)(param_1 + 0xbbc) = tmp_u5;
  *(uint32_t *)(param_1 + 0xbcc) = 0;
  *(uint32_t *)(param_1 + 0xbdc) = 0;
  *(uint32_t *)(param_1 + 0xbd0) = 0;
  *(uint32_t *)(param_1 + 0xbe0) = 0;
  *(uint32_t *)(param_1 + 0xbe4) = 0;
  *(uint32_t *)(param_1 + 0xbd4) = 0;
  *(uint32_t *)(param_1 + 0xca4) = 0xffffffff;
  tmp_pu3 = (uint16_t *)(param_1 + 0xc30);
  tmp_b9 = ((uint)tmp_pu3 & 1) != 0;
  if (tmp_b9) {
    tmp_pu3 = (uint16_t *)(param_1 + 0xc31);
    tmp_u7 = 0x1b;
    *(uint8_t *)(param_1 + 0xc30) = 0;
  }
  if (((uint)tmp_pu3 & 2) != 0) {
    *tmp_pu3 = 0;
    tmp_u7 = tmp_u7 - 2;
    tmp_pu3 = tmp_pu3 + 1;
  }
  tmp_u8 = 0;
  do {
    *(uint32_t *)((int)tmp_pu3 + tmp_u8) = 0;
    *(uint32_t *)((int)tmp_pu3 + tmp_u8 + 4) = 0;
    tmp_u8 = tmp_u8 + 8;
  } while (tmp_u8 < (tmp_u7 & 0xfffffff8));
  tmp_pu2 = (uint32_t *)((int)tmp_pu3 + tmp_u8);
  if ((tmp_u7 & 4) != 0) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + 1;
  }
  if ((tmp_u7 & 2) != 0) {
    *(uint16_t *)tmp_pu2 = 0;
    tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
  }
  if (tmp_b9) {
    *(uint8_t *)tmp_pu2 = 0;
  }
  tmp_pu3 = (uint16_t *)(param_1 + 0xbf4);
  tmp_u7 = 0x1c;
  tmp_b9 = ((uint)tmp_pu3 & 1) != 0;
  if (tmp_b9) {
    *(uint8_t *)(param_1 + 0xbf4) = 0;
    tmp_pu3 = (uint16_t *)(param_1 + 0xbf5);
    tmp_u7 = 0x1b;
  }
  if (((uint)tmp_pu3 & 2) != 0) {
    *tmp_pu3 = 0;
    tmp_u7 = tmp_u7 - 2;
    tmp_pu3 = tmp_pu3 + 1;
  }
  tmp_u8 = 0;
  do {
    *(uint32_t *)((int)tmp_pu3 + tmp_u8) = 0;
    *(uint32_t *)((int)tmp_pu3 + tmp_u8 + 4) = 0;
    tmp_u8 = tmp_u8 + 8;
  } while (tmp_u8 < (tmp_u7 & 0xfffffff8));
  tmp_pu2 = (uint32_t *)((int)tmp_pu3 + tmp_u8);
  if ((tmp_u7 & 4) != 0) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + 1;
  }
  if ((tmp_u7 & 2) != 0) {
    *(uint16_t *)tmp_pu2 = 0;
    tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
  }
  if (tmp_b9) {
    *(uint8_t *)tmp_pu2 = 0;
  }
  tmp_pu3 = (uint16_t *)(param_1 + 0xc10);
  tmp_u7 = 0x1c;
  tmp_b9 = ((uint)tmp_pu3 & 1) != 0;
  if (tmp_b9) {
    *(uint8_t *)(param_1 + 0xc10) = 0;
    tmp_pu3 = (uint16_t *)(param_1 + 0xc11);
    tmp_u7 = 0x1b;
  }
  if (((uint)tmp_pu3 & 2) != 0) {
    *tmp_pu3 = 0;
    tmp_u7 = tmp_u7 - 2;
    tmp_pu3 = tmp_pu3 + 1;
  }
  tmp_u8 = 0;
  do {
    *(uint32_t *)((int)tmp_pu3 + tmp_u8) = 0;
    *(uint32_t *)((int)tmp_pu3 + tmp_u8 + 4) = 0;
    tmp_u8 = tmp_u8 + 8;
  } while (tmp_u8 < (tmp_u7 & 0xfffffff8));
  tmp_pu2 = (uint32_t *)((int)tmp_pu3 + tmp_u8);
  if ((tmp_u7 & 4) != 0) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + 1;
  }
  if ((tmp_u7 & 2) != 0) {
    *(uint16_t *)tmp_pu2 = 0;
    tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
  }
  if (tmp_b9) {
    *(uint8_t *)tmp_pu2 = 0;
  }
  tmp_pu3 = (uint16_t *)(param_1 + 0xc50);
  tmp_u7 = 0x1c;
  tmp_b9 = ((uint)tmp_pu3 & 1) != 0;
  if (tmp_b9) {
    *(uint8_t *)(param_1 + 0xc50) = 0;
    tmp_pu3 = (uint16_t *)(param_1 + 0xc51);
    tmp_u7 = 0x1b;
  }
  if (((uint)tmp_pu3 & 2) != 0) {
    *tmp_pu3 = 0;
    tmp_u7 = tmp_u7 - 2;
    tmp_pu3 = tmp_pu3 + 1;
  }
  tmp_u8 = 0;
  do {
    *(uint32_t *)((int)tmp_pu3 + tmp_u8) = 0;
    *(uint32_t *)((int)tmp_pu3 + tmp_u8 + 4) = 0;
    tmp_u8 = tmp_u8 + 8;
  } while (tmp_u8 < (tmp_u7 & 0xfffffff8));
  tmp_pu2 = (uint32_t *)((int)tmp_pu3 + tmp_u8);
  if ((tmp_u7 & 4) != 0) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + 1;
  }
  if ((tmp_u7 & 2) != 0) {
    *(uint16_t *)tmp_pu2 = 0;
    tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
  }
  if (tmp_b9) {
    *(uint8_t *)tmp_pu2 = 0;
  }
  *(uint32_t *)(param_1 + 0xc4c) = 0;
  *(uint32_t *)(param_1 + 0xc2c) = 0;
  tmp_i1 = level;
  *(uint *)(param_1 + 0xc80) = (uint)(*(int *)(param_1 + 0x5e8) != 0);
  *(uint32_t *)(param_1 + 0xc88) = 0;
  *(uint32_t *)(param_1 + 0xc8c) = 0;
  G_deleteStats((param_1 - tmp_i1 >> 2) * -0x66e64f79);
  *(uint32_t *)(param_1 + 0xca8) = 0;
  *(uint32_t *)(param_1 + 0xf14) = 0;
  __nptr = (char *)Info_ValueForKey(param_2,"protocol");
  tmp_l4 = strtol(__nptr,(char **)0x0,10);
  *(uint *)(param_1 + 0xf34) = (uint)(tmp_l4 == 0x11c);
  tmp_u7 = 0;
  if (tmp_l4 == 0x11c) {
    tmp_u7 = (uint)GHIDRA_FIELD(g_ettvFlags, 12, 4) >> 1 & 1;
  }
  *(uint *)(param_1 + 0xf30) = tmp_u7;
  G_deleteStats((param_1 - level >> 2) * -0x66e64f79);
  tmp_u5 = va("%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %s"
             ,*(uint32_t *)(param_1 + 3000),*(uint32_t *)(param_1 + 0xbbc),
             *(uint32_t *)(param_1 + 0xbc0),*(uint32_t *)(param_1 + 0xbc4),
             *(uint32_t *)(param_1 + 0xbc8),*(uint32_t *)(param_1 + 0xbcc),
             *(uint32_t *)(param_1 + 0xbd0),*(uint32_t *)(param_1 + 0xbd8),
             *(uint32_t *)(param_1 + 0xbdc),*(uint32_t *)(param_1 + 0xbe0),
             *(uint32_t *)(param_1 + 0xc74),*(uint32_t *)(param_1 + 0xc78),
             *(uint32_t *)(param_1 + 0xc7c),*(uint32_t *)(param_1 + 0xc80),
             *(uint32_t *)(param_1 + 0xc88),*(uint32_t *)(param_1 + 0xc8c),
             *(uint32_t *)(param_1 + 0xc90),*(uint32_t *)(param_1 + 0xc98),
             *(uint32_t *)(param_1 + 0xec8),*(uint32_t *)(param_1 + 0xbf0),
             *(uint32_t *)(param_1 + 0xca4),*(uint32_t *)(param_1 + 0xbe8),
             *(uint32_t *)(param_1 + 0xbec),*(uint32_t *)(param_1 + 0x674),0,
             *(uint32_t *)(param_1 + 0xbe4),*(uint32_t *)(param_1 + 0xca8),
             *(uint32_t *)(param_1 + 0xf14),*(uint32_t *)(param_1 + 0xecc),
             *(uint32_t *)(param_1 + 0xf2c),*(uint32_t *)(param_1 + 0xf30),
             *(uint32_t *)(param_1 + 0xf34),*(uint32_t *)(param_1 + 0xf38),
             *(uint32_t *)(param_1 + 0xf3c),*(uint32_t *)(param_1 + 0xf40),
             *(uint32_t *)(param_1 + 0xf44),param_1 + 0xf48);
  tmp_u6 = va("session%i",(param_1 - level >> 2) * -0x66e64f79);
  trap_Cvar_Set(tmp_u6,tmp_u5);
  tmp_u5 = va("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %i %i %i %i %i %i %i",
             (double)*(float *)(param_1 + 0xbf4),(double)*(float *)(param_1 + 0xbf8),
             (double)*(float *)(param_1 + 0xbfc),(double)*(float *)(param_1 + 0xc00),
             (double)*(float *)(param_1 + 0xc04),(double)*(float *)(param_1 + 0xc08),
             (double)*(float *)(param_1 + 0xc0c),*(uint32_t *)(param_1 + 0xc50),
             *(uint32_t *)(param_1 + 0xc54),*(uint32_t *)(param_1 + 0xc58),
             *(uint32_t *)(param_1 + 0xc5c),*(uint32_t *)(param_1 + 0xc60),
             *(uint32_t *)(param_1 + 0xc64),*(uint32_t *)(param_1 + 0xc68));
  tmp_u6 = va("sessionstats%i",(param_1 - level >> 2) * -0x66e64f79);
  trap_Cvar_Set(tmp_u6,tmp_u5);
  return;
}

void G_InitWorldSession(void)
{
  uint8_t *tmp_pu1;
  long tmp_l2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  uint tmp_u5;
  char *__s;
  uint tmp_u6;
  uint32_t *tmp_pu7;
  int tmp_i8;
  int tmp_i9;
  uint32_t *tmp_pu10;
  bool tmp_b11;
  bool tmp_b12;
  byte tmp_b13;
  int local_448;
  char local_424 [8];
  char local_41c [1032];
  uint32_t uStack_14;
  
  tmp_b13 = 0;
  uStack_14 = 0xc7f2e;
  trap_Cvar_VariableStringBuffer("session",local_41c,0x400);
  tmp_l2 = strtol(local_41c,(char **)0x0,10);
  if (GHIDRA_FIELD(g_gametype, 12, 4) == tmp_l2) {
    tmp_b11 = GHIDRA_FIELD(g_altStopwatchMode, 12, 4) != 0;
    tmp_b12 = GHIDRA_FIELD(g_currentRound, 12, 4) == 1;
    tmp_pc4 = strchr(local_41c,0x20);
    if (tmp_pc4 == (char *)0x0) {
      return;
    }
    tmp_u6 = strtol(tmp_pc4 + 1,(char **)0x0,10);
    GHIDRA_FIELD(teamInfo, 16, 4) = tmp_u6 & 1;
    GHIDRA_FIELD(teamInfo, 32, 4) = tmp_u6 >> 1 & 1;
    tmp_pc4 = strchr(tmp_pc4 + 1,0x20);
    if (tmp_pc4 == (char *)0x0) {
      return;
    }
    g_unk_02aa3f8c = strtol(tmp_pc4 + 1,(char **)0x0,10);
    tmp_pc4 = strchr(tmp_pc4 + 1,0x20);
    if (tmp_pc4 == (char *)0x0) {
      return;
    }
    g_unk_02aa029c = strtol(tmp_pc4 + 1,(char **)0x0,10);
    if (GHIDRA_FIELD(g_gametype, 12, 4) != 4) {
      tmp_pc4 = (char *)va(&g_unk_0024e6e9,tmp_pc4 + 1);
      tmp_pc4 = strchr(tmp_pc4,0x20);
      if (tmp_pc4 != (char *)0x0) {
        trap_GetServerinfo(local_41c,0x400);
        tmp_u3 = Info_ValueForKey(local_41c,"mapname");
        tmp_i9 = Q_stricmp(tmp_pc4 + 1,tmp_u3);
        if (tmp_i9 != 0) {
          g_unk_02a99a74 = 1;
          G_Printf("Map changed, clearing player stats.\n");
        }
      }
      if (((GHIDRA_FIELD(g_gametype, 12, 4) == 3) && (tmp_b11 || tmp_b12)) && (GHIDRA_FIELD(g_gamestate, 12, 4) != 0)) {
        G_swapTeamLocks();
      }
    }
    if (GHIDRA_FIELD(g_swapteams, 12, 4) != 0) {
      G_swapTeamLocks();
    }
  }
  else {
    g_unk_00abe930 = 1;
    g_unk_02a99a74 = 1;
    G_Printf("Gametype changed, clearing session data.\n");
  }
  tmp_pu7 = &level;
  local_448 = 0;
  do {
    tmp_u3 = va("fireteam%i",local_448);
    trap_Cvar_VariableStringBuffer(tmp_u3,local_41c,0x400);
    tmp_pc4 = (char *)Info_ValueForKey(local_41c,&g_unk_0023bf57);
    tmp_l2 = strtol(tmp_pc4,(char **)0x0,10);
    *(uint *)(&g_unk_01fdae4c + (int)tmp_pu7) = (uint)(tmp_l2 != -1 && *tmp_pc4 != '\0');
    *(long *)(&g_unk_01fdae04 + (int)tmp_pu7) = tmp_l2 + 1;
    tmp_pc4 = (char *)Info_ValueForKey(local_41c,"p");
    tmp_l2 = strtol(tmp_pc4,(char **)0x0,10);
    tmp_pu7[0x7f6b94] = (uint)(tmp_l2 != 0);
    tmp_i8 = 0;
    tmp_pc4 = (char *)Info_ValueForKey(local_41c,"i");
    tmp_i9 = tmp_i8;
    if ((tmp_pc4 != (char *)0x0) && (*tmp_pc4 != '\0')) {
      tmp_pc4 = strchr(tmp_pc4,0x20);
      __s = tmp_pc4 + 1;
      if ((__s != (char *)0x0) && (tmp_pc4[1] != '\0')) {
        while (tmp_pc4 = strchr(__s,0x20), tmp_i9 = tmp_i8, tmp_pc4 != (char *)0x0) {
          tmp_i9 = tmp_i8 + 1;
          Q_strncpyz(local_424,__s,tmp_pc4 + (1 - (int)__s));
          tmp_pc4[(int)(local_424 + -(int)__s)] = '\0';
          tmp_l2 = strtol(local_424,(char **)0x0,10);
          __s = tmp_pc4 + 1;
          *(char *)((int)tmp_pu7 + (int)(&g_unk_01fdae08 + tmp_i8)) = (char)tmp_l2;
          if ((__s == (char *)0x0) || (tmp_i8 = tmp_i9, tmp_pc4[1] == '\0')) break;
        }
      }
    }
    if (tmp_i9 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
      tmp_u6 = GHIDRA_FIELD(g_maxclients, 12, 4) - tmp_i9;
      tmp_pu10 = (uint32_t *)(&g_unk_01fdae08 + (int)tmp_pu7 + tmp_i9);
      if (7 < tmp_u6) {
        tmp_u5 = tmp_u6;
        if (((uint)tmp_pu10 & 1) != 0) {
          *(uint8_t *)tmp_pu10 = 0xff;
          tmp_pu10 = (uint32_t *)((int)tmp_pu10 + 1);
          tmp_u5 = tmp_u6 - 1;
        }
        if (((uint)tmp_pu10 & 2) != 0) {
          *(uint16_t *)tmp_pu10 = 0xffff;
          tmp_u5 = tmp_u5 - 2;
          tmp_pu10 = (uint32_t *)((int)tmp_pu10 + 2);
        }
        if (((uint)tmp_pu10 & 4) != 0) {
          *tmp_pu10 = 0xffffffff;
          tmp_u5 = tmp_u5 - 4;
          tmp_pu10 = tmp_pu10 + 1;
        }
        tmp_u6 = tmp_u5 & 3;
        for (tmp_u5 = tmp_u5 >> 2; tmp_u5 != 0; tmp_u5 = tmp_u5 - 1) {
          *tmp_pu10 = 0xffffffff;
          tmp_pu10 = tmp_pu10 + (uint)tmp_b13 * -2 + 1;
        }
      }
      if ((tmp_u6 & 4) != 0) {
        *tmp_pu10 = 0xffffffff;
        tmp_pu10 = tmp_pu10 + 1;
      }
      if ((tmp_u6 & 2) != 0) {
        *(uint16_t *)tmp_pu10 = 0xffff;
        tmp_pu10 = (uint32_t *)((int)tmp_pu10 + 2);
      }
      if ((tmp_u6 & 1) != 0) {
        *(uint8_t *)tmp_pu10 = 0xff;
      }
    }
    tmp_pu1 = &g_unk_01fdae04 + (int)tmp_pu7;
    tmp_pu7 = tmp_pu7 + 0x14;
    G_UpdateFireteamConfigString(tmp_pu1);
    local_448 = local_448 + 1;
    if (local_448 == 0xc) {
      return;
    }
  } while( true );
}

void G_WriteSessionData(uint32_t param_1)
{
  int *tmp_pi1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  int tmp_i6;
  uint8_t *local_c2c;
  int local_c24;
  uint8_t local_c1c [1024];
  uint8_t local_81c [1024];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xc842e;
  trap_GetServerinfo(local_c1c,0x400);
  tmp_u2 = Info_ValueForKey(local_c1c,"mapname");
  tmp_pu4 = &level;
  tmp_u2 = va("%i %i %d %d %s",GHIDRA_FIELD(g_gametype, 12, 4),GHIDRA_FIELD(teamInfo, 32, 4) * 2 | GHIDRA_FIELD(teamInfo, 16, 4),g_unk_02aa3f8c,
             g_unk_02aa029c,tmp_u2);
  trap_Cvar_Set("session",tmp_u2);
  if (g_unk_02a99a74 == 0) {
    if (g_unk_00abe938 < 1) goto LAB_000c8537;
    if (GHIDRA_FIELD(g_gamestate, 12, 4) == 1) {
      tmp_i6 = 0;
      if (GHIDRA_FIELD(g_gametype, 12, 4) == 3) {
        do {
          if (1 < *(int *)(level + 0xc84 + (&g_unk_00abe944)[tmp_i6] * 0x54dc)) goto LAB_000c86b4;
          tmp_i6 = tmp_i6 + 1;
        } while (tmp_i6 != g_unk_00abe938);
      }
      else {
        do {
          if (0 < *(int *)(level + 0xc84 + (&g_unk_00abe944)[tmp_i6] * 0x54dc)) goto LAB_000c86b4;
          tmp_i6 = tmp_i6 + 1;
        } while (tmp_i6 != g_unk_00abe938);
      }
    }
  }
  else if (g_unk_00abe938 < 1) goto LAB_000c8537;
  goto LAB_000c84f0;
LAB_000c86b4:
  g_unk_02a99a74 = 1;
LAB_000c84f0:
  tmp_i5 = 0;
  tmp_i6 = g_unk_00abe938;
  do {
    while( true ) {
      tmp_pi1 = &g_unk_00abe944 + tmp_i5;
      tmp_i3 = *tmp_pi1 * 0x54dc + level;
      if (*(int *)(tmp_i3 + 0x5ac) != 2) break;
      G_WriteClientSessionData(tmp_i3,param_1);
      tmp_i6 = g_unk_00abe938;
LAB_000c84f8:
      tmp_i5 = tmp_i5 + 1;
      if (tmp_i6 <= tmp_i5) goto LAB_000c8537;
    }
    if (g_unk_02a99a74 == 0) goto LAB_000c84f8;
    tmp_i5 = tmp_i5 + 1;
    G_deleteStats(*tmp_pi1);
    tmp_i6 = g_unk_00abe938;
  } while (tmp_i5 < g_unk_00abe938);
LAB_000c8537:
  local_c24 = 0;
  do {
    if (*(int *)(&g_unk_01fdae4c + (int)tmp_pu4) == 0) {
      Com_sprintf(local_81c,0x400,"\\n\\-1");
    }
    else {
      local_41c[0] = 0;
      if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
        tmp_i6 = 0;
        do {
          tmp_i5 = tmp_i6 + (int)tmp_pu4;
          tmp_i6 = tmp_i6 + 1;
          Com_sprintf(local_81c,8," %i",(int)(char)(&g_unk_01fdae08)[tmp_i5]);
          Q_strcat(local_41c,0x400,local_81c);
        } while (tmp_i6 < (int)GHIDRA_FIELD(g_maxclients, 12, 4));
      }
      local_c2c = local_41c;
      Com_sprintf(local_81c,0x400,"\\n\\%i\\i\\%s\\p\\%i",*(int *)(&g_unk_01fdae04 + (int)tmp_pu4) + -1
                  ,local_c2c,tmp_pu4[0x7f6b94] != 0);
    }
    tmp_pu4 = tmp_pu4 + 0x14;
    tmp_u2 = va("fireteam%i",local_c24);
    trap_Cvar_Set(tmp_u2,local_81c);
    local_c24 = local_c24 + 1;
  } while (local_c24 != 0xc);
  return;
}

int G_SpawnIntExt(char *param_1,char *param_2,long *param_3,uint32_t param_4,uint32_t param_5)
{
  int tmp_i1;
  int tmp_i2;
  long tmp_l3;
  int tmp_i4;
  
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",param_4,param_5);
  }
  tmp_i1 = g_unk_00abef88;
  tmp_i4 = 0;
  if (0 < g_unk_00abef88) {
    do {
      tmp_i2 = strcmp(param_1,(char *)(&g_unk_00abef8c)[tmp_i4 * 2]);
      if (tmp_i2 == 0) {
        param_2 = (char *)(&g_unk_00abef90)[tmp_i4 * 2];
        tmp_i4 = 1;
        goto LAB_000dc89e;
      }
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_i4 != tmp_i1);
    tmp_i4 = 0;
  }
LAB_000dc89e:
  tmp_l3 = strtol(param_2,(char **)0x0,10);
  *param_3 = tmp_l3;
  return tmp_i4;
}

int G_SpawnVectorExt(char *param_1,uint32_t param_2,int param_3,uint32_t param_4,
                    uint32_t param_5)

{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",param_4,param_5);
  }
  tmp_i1 = g_unk_00abef88;
  tmp_i3 = 0;
  if (0 < g_unk_00abef88) {
    do {
      tmp_i2 = strcmp(param_1,(char *)(&g_unk_00abef8c)[tmp_i3 * 2]);
      if (tmp_i2 == 0) {
        param_2 = (&g_unk_00abef90)[tmp_i3 * 2];
        tmp_i3 = 1;
        goto LAB_000dc96e;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != tmp_i1);
    tmp_i3 = 0;
  }
LAB_000dc96e:
  __isoc99_sscanf(param_2,"%f %f %f",param_3,param_3 + 4,param_3 + 8);
  return tmp_i3;
}

int G_SpawnVector2DExt(char *param_1,uint32_t param_2,int param_3,uint32_t param_4,
                      uint32_t param_5)

{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",param_4,param_5);
  }
  tmp_i1 = g_unk_00abef88;
  tmp_i3 = 0;
  if (0 < g_unk_00abef88) {
    do {
      tmp_i2 = strcmp(param_1,(char *)(&g_unk_00abef8c)[tmp_i3 * 2]);
      if (tmp_i2 == 0) {
        param_2 = (&g_unk_00abef90)[tmp_i3 * 2];
        tmp_i3 = 1;
        goto LAB_000dca4e;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != tmp_i1);
    tmp_i3 = 0;
  }
LAB_000dca4e:
  __isoc99_sscanf(param_2,"%f %f",param_3,param_3 + 4);
  return tmp_i3;
}

uint32_t G_CallSpawn(int param_1)
{
  char *__s2;
  char *__s1;
  char *__s1_00;
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint8_t **tmp_ppu3;
  
  __s2 = *(char **)(param_1 + 0x1a4);
  if (__s2 == (char *)0x0) {
    G_Printf("G_CallSpawn: NULL classname\n");
    return 0;
  }
  tmp_pu2 = (uint32_t *)(bg_itemlist + 0x38);
  __s1 = (char *)GHIDRA_FIELD(bg_itemlist, 56, 4);
  __s1_00 = spawns;
  while (spawns = __s1_00, __s1 != (char *)0x0) {
    tmp_i1 = strcmp(__s1,__s2);
    if (tmp_i1 == 0) {
      if (tmp_pu2[9] == 5) {
        if (tmp_pu2[0xb] == 6) {
          *(uint32_t *)(param_1 + 0x5c0) = 0x36af1;
        }
        else if (tmp_pu2[0xb] == 5) {
          *(uint32_t *)(param_1 + 0x5c0) = 0x3317f;
        }
      }
      if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
        return 0;
      }
      G_SpawnItem(param_1,tmp_pu2);
      goto LAB_000dcb3e;
    }
    tmp_pu2 = tmp_pu2 + 0xe;
    __s1_00 = spawns;
    __s1 = (char *)*tmp_pu2;
  }
  if (__s1_00 != (char *)0x0) {
    tmp_ppu3 = &spawns;
    do {
      tmp_i1 = strcmp(__s1_00,__s2);
      if (tmp_i1 == 0) {
        (*(void *)tmp_ppu3[1])(param_1);
        if (*(int *)(param_1 + 0x3ac) == 0) {
          return 1;
        }
LAB_000dcb3e:
        G_Script_ScriptParse(param_1);
        G_Script_ScriptEvent(param_1,"spawn",&g_unk_0026ea14);
        return 1;
      }
      tmp_ppu3 = tmp_ppu3 + 2;
      __s1_00 = *tmp_ppu3;
    } while (__s1_00 != (char *)0x0);
  }
  G_Printf("%s doesn\'t have a spawn function\n",__s2);
  return 0;
}

int G_NewString(char *param_1)
{
  int tmp_i1;
  size_t tmp_s2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  
  tmp_s2 = strlen(param_1);
  tmp_i1 = tmp_s2 + 1;
  tmp_i3 = G_Alloc(tmp_i1);
  tmp_i5 = 0;
  tmp_i4 = tmp_i3 + 1;
  if (tmp_i1 < 1) {
    return tmp_i3;
  }
  do {
    while ((param_1[tmp_i5] != '\\' || ((int)tmp_s2 <= tmp_i5))) {
      *(char *)(tmp_i4 + -1) = param_1[tmp_i5];
LAB_000dcc73:
      tmp_i5 = tmp_i5 + 1;
      tmp_i4 = tmp_i4 + 1;
      if (tmp_i1 <= tmp_i5) {
        return tmp_i3;
      }
    }
    if (param_1[tmp_i5 + 1] == 'n') {
      *(uint8_t *)(tmp_i4 + -1) = 10;
      tmp_i5 = tmp_i5 + 1;
      goto LAB_000dcc73;
    }
    tmp_i5 = tmp_i5 + 2;
    *(uint8_t *)(tmp_i4 + -1) = 0x5c;
    tmp_i4 = tmp_i4 + 1;
    if (tmp_i1 <= tmp_i5) {
      return tmp_i3;
    }
  } while( true );
}

void G_ParseField(uint32_t param_1,char *param_2,int param_3)
{
  uint8_t *tmp_pu1;
  char *tmp_pc2;
  int tmp_i3;
  long tmp_l4;
  size_t tmp_s5;
  char *tmp_pc6;
  int tmp_i7;
  uint8_t **tmp_ppu8;
  double tmp_d9;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0xdccc9;
  tmp_ppu8 = &fields;
  tmp_pu1 = fields;
  while( true ) {
    if (tmp_pu1 == (uint8_t *)0x0) {
      return;
    }
    tmp_i3 = Q_stricmp(tmp_pu1,param_1);
    if (tmp_i3 == 0) break;
    tmp_ppu8 = tmp_ppu8 + 4;
    tmp_pu1 = *tmp_ppu8;
  }
  switch(tmp_ppu8[2]) {
  case (uint8_t *)0x0:
    tmp_pu1 = tmp_ppu8[1];
    tmp_l4 = strtol(param_2,(char **)0x0,10);
    *(long *)(tmp_pu1 + param_3) = tmp_l4;
    return;
  case (uint8_t *)0x1:
    tmp_pu1 = tmp_ppu8[1];
    tmp_d9 = strtod(param_2,(char **)0x0);
    *(float *)(tmp_pu1 + param_3) = (float)tmp_d9;
    return;
  case (uint8_t *)0x2:
    break;
  default:
    return;
  case (uint8_t *)0x4:
    __isoc99_sscanf(param_2,"%f %f %f",&local_28,&local_24,local_20);
    *(uint32_t *)(tmp_ppu8[1] + param_3) = local_28;
    *(uint32_t *)(tmp_ppu8[1] + param_3 + 4) = local_24;
    *(uint32_t *)(tmp_ppu8[1] + param_3 + 8) = local_20[0];
    return;
  case (uint8_t *)0x5:
    tmp_d9 = strtod(param_2,(char **)0x0);
    *(uint32_t *)(tmp_ppu8[1] + param_3) = 0;
    *(float *)(tmp_ppu8[1] + param_3 + 4) = (float)tmp_d9;
    *(uint32_t *)(tmp_ppu8[1] + param_3 + 8) = 0;
    return;
  }
  tmp_pu1 = tmp_ppu8[1];
  tmp_s5 = strlen(param_2);
  tmp_i3 = tmp_s5 + 1;
  tmp_pc6 = (char *)G_Alloc(tmp_i3);
  tmp_i7 = 0;
  tmp_pc2 = tmp_pc6;
  if (0 < tmp_i3) {
    do {
      if ((param_2[tmp_i7] == '\\') && (tmp_i7 < (int)tmp_s5)) {
        tmp_i7 = tmp_i7 + 1;
        if (param_2[tmp_i7] == 'n') {
          *tmp_pc2 = '\n';
        }
        else {
          *tmp_pc2 = '\\';
        }
      }
      else {
        *tmp_pc2 = param_2[tmp_i7];
      }
      tmp_i7 = tmp_i7 + 1;
      tmp_pc2 = tmp_pc2 + 1;
    } while (tmp_i7 < tmp_i3);
  }
  *(char **)(tmp_pu1 + param_3) = tmp_pc6;
  return;
}

int G_SpawnGEntityFromSpawnVars(void)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  char *tmp_pc5;
  uint8_t *tmp_pu6;
  int tmp_i7;
  uint32_t *tmp_pu8;
  int tmp_i9;
  bool tmp_b10;
  byte tmp_b11;
  
  tmp_b11 = 0;
  tmp_i1 = G_Spawn();
  if (g_unk_00abef88 < 1) {
    if (g_unk_00abef84 != 0) goto LAB_000dcf40;
LAB_000dd158:
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x318);
  }
  else {
    tmp_i9 = 0;
    tmp_pu8 = &g_unk_00abef90;
    do {
      tmp_i9 = tmp_i9 + 1;
      G_ParseField(tmp_pu8[-1],*tmp_pu8,tmp_i1);
      tmp_pu8 = tmp_pu8 + 2;
    } while (tmp_i9 < g_unk_00abef88);
    if (g_unk_00abef84 == 0) goto LAB_000dd158;
  }
  if (0 < g_unk_00abef88) {
    tmp_i9 = 0;
    tmp_b10 = true;
    do {
      tmp_i7 = 8;
      tmp_pc4 = "notteam";
      tmp_pc5 = (char *)(&g_unk_00abef8c)[tmp_i9 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b10 = *tmp_pc4 == *tmp_pc5;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b11 * -2 + 1;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b11 * -2 + 1;
      } while (tmp_b10);
      if (tmp_b10) {
        tmp_pc4 = (char *)(&g_unk_00abef90)[tmp_i9 * 2];
        goto LAB_000dcf46;
      }
      tmp_i9 = tmp_i9 + 1;
      tmp_b10 = tmp_i9 == g_unk_00abef88;
    } while (!tmp_b10);
  }
LAB_000dcf40:
  tmp_pc4 = "0";
LAB_000dcf46:
  tmp_l2 = strtol(tmp_pc4,(char **)0x0,10);
  if (tmp_l2 != 0) {
    G_FreeEntity(tmp_i1);
    return 0;
  }
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",799);
  }
  if (0 < g_unk_00abef88) {
    tmp_i9 = 0;
    tmp_b10 = true;
    do {
      tmp_i7 = 0xb;
      tmp_pc4 = "allowteams";
      tmp_pc5 = (char *)(&g_unk_00abef8c)[tmp_i9 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b10 = *tmp_pc4 == *tmp_pc5;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b11 * -2 + 1;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b11 * -2 + 1;
      } while (tmp_b10);
      if (tmp_b10) {
        if (*(char *)(&g_unk_00abef90)[tmp_i9 * 2] != '\0') {
          tmp_pc4 = (char *)Q_strlwr((char *)(&g_unk_00abef90)[tmp_i9 * 2]);
          tmp_pc5 = strstr(tmp_pc4,"axis");
          if (tmp_pc5 != (char *)0x0) {
            *(uint *)(tmp_i1 + 0x488) = *(uint *)(tmp_i1 + 0x488) | 1;
          }
          tmp_pc5 = strstr(tmp_pc4,"allies");
          if (tmp_pc5 != (char *)0x0) {
            *(uint *)(tmp_i1 + 0x488) = *(uint *)(tmp_i1 + 0x488) | 2;
          }
          tmp_pc4 = strstr(tmp_pc4,"cvops");
          if (tmp_pc4 != (char *)0x0) {
            *(uint *)(tmp_i1 + 0x488) = *(uint *)(tmp_i1 + 0x488) | 4;
          }
        }
        break;
      }
      tmp_i9 = tmp_i9 + 1;
      tmp_b10 = tmp_i9 == g_unk_00abef88;
    } while (!tmp_b10);
  }
  tmp_pc4 = *(char **)(tmp_i1 + 600);
  if ((tmp_pc4 == (char *)0x0) || (*tmp_pc4 == '\0')) {
    *(uint32_t *)(tmp_i1 + 0x25c) = 0xffffffff;
  }
  else {
    tmp_u3 = BG_StringHashValue(tmp_pc4);
    *(uint32_t *)(tmp_i1 + 0x25c) = tmp_u3;
  }
  tmp_pc4 = *(char **)(tmp_i1 + 0x254);
  if ((tmp_pc4 == (char *)0x0) || (*tmp_pc4 == '\0')) {
    *(uint32_t *)(tmp_i1 + 0x5bc) = 0xffffffff;
  }
  else {
    tmp_u3 = BG_StringHashValue(tmp_pc4);
    *(uint32_t *)(tmp_i1 + 0x5bc) = tmp_u3;
  }
  tmp_pc4 = *(char **)(tmp_i1 + 0x3ac);
  if ((tmp_pc4 == (char *)0x0) || (*tmp_pc4 == '\0')) {
    *(uint32_t *)(tmp_i1 + 0x5b0) = 0xffffffff;
  }
  else {
    tmp_pc5 = *(char **)(tmp_i1 + 0x1a4);
    if ((tmp_pc5 != (char *)0x0) && (*tmp_pc5 != '\0')) {
      tmp_i9 = Q_stricmp(tmp_pc5,"script_multiplayer");
      if (tmp_i9 == 0) {
        tmp_pc4 = "game_manager";
      }
      else {
        tmp_pc4 = *(char **)(tmp_i1 + 0x3ac);
      }
    }
    tmp_u3 = BG_StringHashValue(tmp_pc4);
    *(uint32_t *)(tmp_i1 + 0x5b0) = tmp_u3;
  }
  *(uint32_t *)(tmp_i1 + 0x18) = *(uint32_t *)(tmp_i1 + 0x5c);
  *(uint32_t *)(tmp_i1 + 0x1c) = *(uint32_t *)(tmp_i1 + 0x60);
  *(uint32_t *)(tmp_i1 + 0x20) = *(uint32_t *)(tmp_i1 + 100);
  *(uint32_t *)(tmp_i1 + 0x168) = *(uint32_t *)(tmp_i1 + 0x5c);
  *(uint32_t *)(tmp_i1 + 0x16c) = *(uint32_t *)(tmp_i1 + 0x60);
  *(uint32_t *)(tmp_i1 + 0x170) = *(uint32_t *)(tmp_i1 + 100);
  tmp_i9 = G_CallSpawn(tmp_i1);
  if (tmp_i9 == 0) {
    G_FreeEntity(tmp_i1);
  }
  tmp_pc4 = *(char **)(tmp_i1 + 0x1a4);
  if ((tmp_pc4 != (char *)0x0) && (*tmp_pc4 != '\0')) {
    tmp_pu6 = (uint8_t *)BG_StringHashValue(tmp_pc4);
    *(uint8_t **)(tmp_i1 + 0x5c0) = tmp_pu6;
    if (tmp_pu6 != (uint8_t *)0x3eee0) {
      if ((int)tmp_pu6 < 0x3eee1) {
        if (((tmp_pu6 != (uint8_t *)0x3b699) && (tmp_pu6 != (uint8_t *)0x3ec15)) &&
           (tmp_pu6 != (uint8_t *)0x37c98)) {
          return tmp_i1;
        }
      }
      else if (((tmp_pu6 != (uint8_t *)0x49240) && (tmp_pu6 != (uint8_t *)0x527df)) &&
              (tmp_pu6 != &g_unk_00042729)) {
        return tmp_i1;
      }
    }
    nitrox_AddEntityToEntityArray(&SpawnEntities,tmp_i1);
    return tmp_i1;
  }
  *(uint32_t *)(tmp_i1 + 0x5c0) = 0xffffffff;
  return tmp_i1;
}

void G_AddSpawnVarToken(char *param_1)
{
  uint tmp_u1;
  char tmp_c2;
  uint16_t tmp_u3;
  uint32_t tmp_u4;
  size_t tmp_s5;
  char *tmp_pc6;
  char *tmp_pc7;
  char *tmp_pc8;
  byte tmp_b9;
  uint local_24;
  
  tmp_b9 = 0;
  tmp_s5 = strlen(param_1);
  if (0x7ff < (int)(g_unk_00abf18c + tmp_s5)) {
    G_Error("G_AddSpawnVarToken: MAX_SPAWN_VARS");
  }
  tmp_pc7 = &g_unk_00abf190 + g_unk_00abf18c;
  tmp_u1 = tmp_s5 + 1;
  local_24 = tmp_u1;
  if (7 < tmp_u1) {
    tmp_pc6 = tmp_pc7;
    if (((uint)tmp_pc7 & 1) != 0) {
      tmp_c2 = *param_1;
      tmp_pc6 = &g_unk_00abf191 + g_unk_00abf18c;
      param_1 = param_1 + 1;
      *tmp_pc7 = tmp_c2;
      local_24 = tmp_s5;
    }
    tmp_pc8 = tmp_pc6;
    if (((uint)tmp_pc6 & 2) != 0) {
      tmp_u3 = *(uint16_t *)param_1;
      tmp_pc8 = tmp_pc6 + 2;
      param_1 = param_1 + 2;
      *(uint16_t *)tmp_pc6 = tmp_u3;
      local_24 = local_24 - 2;
    }
    tmp_pc7 = tmp_pc8;
    if (((uint)tmp_pc8 & 4) != 0) {
      tmp_u4 = *(uint32_t *)param_1;
      tmp_pc7 = tmp_pc8 + 4;
      param_1 = param_1 + 4;
      *(uint32_t *)tmp_pc8 = tmp_u4;
      local_24 = local_24 - 4;
    }
  }
  for (; local_24 != 0; local_24 = local_24 - 1) {
    *tmp_pc7 = *param_1;
    param_1 = param_1 + (uint)tmp_b9 * -2 + 1;
    tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
  }
  g_unk_00abf18c = g_unk_00abf18c + tmp_u1;
  return;
}

uint32_t G_ParseSpawnVars(void)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  uint tmp_u4;
  uint32_t tmp_u5;
  uint8_t *tmp_pu6;
  uint8_t *tmp_pu7;
  uint *tmp_pu8;
  uint *tmp_pu9;
  uint *tmp_pu10;
  uint *tmp_pu11;
  byte tmp_b12;
  char local_81c;
  uint auStack_81b [255];
  char local_41c;
  uint auStack_41b [257];
  uint32_t uStack_14;
  
  tmp_b12 = 0;
  uStack_14 = 0xdd3db;
  g_unk_00abef88 = 0;
  g_unk_00abf18c = (uint8_t *)0x0;
  tmp_i2 = trap_GetEntityToken(&local_41c,0x400);
  tmp_u5 = 0;
  if (tmp_i2 != 0) {
    if (local_41c != '{') {
      G_Error("G_ParseSpawnVars: found %s when expecting {",&local_41c);
    }
    while( true ) {
      tmp_i2 = trap_GetEntityToken(&local_81c,0x400);
      if (tmp_i2 == 0) {
        G_Error("G_ParseSpawnVars: EOF without closing brace");
      }
      if (local_81c == '}') break;
      tmp_i2 = trap_GetEntityToken(&local_41c,0x400);
      if (tmp_i2 == 0) {
        G_Error("G_ParseSpawnVars: EOF without closing brace");
      }
      if (local_41c == '}') {
        G_Error("G_ParseSpawnVars: closing brace without data");
      }
      tmp_pu9 = (uint *)&local_81c;
      if (g_unk_00abef88 == 0x40) {
        G_Error("G_ParseSpawnVars: MAX_SPAWN_VARS");
      }
      do {
        tmp_pu8 = tmp_pu9;
        tmp_i2 = g_unk_00abef88;
        tmp_u3 = *tmp_pu8 + 0xfefefeff & ~*tmp_pu8;
        tmp_u4 = tmp_u3 & 0x80808080;
        tmp_pu9 = tmp_pu8 + 1;
      } while (tmp_u4 == 0);
      if ((tmp_u3 & 0x8080) == 0) {
        tmp_pu9 = (uint *)((int)tmp_pu8 + 6);
        tmp_u4 = tmp_u4 >> 0x10;
      }
      tmp_pu7 = (uint8_t *)
               ((int)tmp_pu9 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)&local_81c));
      if (0x7ff < (int)(g_unk_00abf18c + (int)tmp_pu7)) {
        G_Error("G_AddSpawnVarToken: MAX_SPAWN_VARS");
      }
      tmp_pu8 = (uint *)(g_unk_00abf18c + 0xabf190);
      tmp_pu1 = tmp_pu7 + 1;
      tmp_pu6 = tmp_pu1;
      tmp_pu9 = (uint *)&local_81c;
      tmp_pu11 = tmp_pu8;
      if ((uint8_t *)0x7 < tmp_pu1) {
        tmp_pu10 = tmp_pu8;
        if (((uint)tmp_pu8 & 1) != 0) {
          tmp_pu10 = (uint *)(g_unk_00abf18c + 0xabf191);
          tmp_pu9 = auStack_81b;
          *(char *)tmp_pu8 = local_81c;
          tmp_pu6 = tmp_pu7;
        }
        tmp_pu11 = tmp_pu10;
        if (((uint)tmp_pu10 & 2) != 0) {
          tmp_u4 = *tmp_pu9;
          tmp_pu11 = (uint *)((int)tmp_pu10 + 2);
          tmp_pu9 = (uint *)((int)tmp_pu9 + 2);
          tmp_pu6 = tmp_pu6 + -2;
          *(short *)tmp_pu10 = (short)tmp_u4;
        }
        if (((uint)tmp_pu11 & 4) != 0) {
          tmp_pu6 = tmp_pu6 + -4;
          *tmp_pu11 = *tmp_pu9;
          tmp_pu9 = tmp_pu9 + 1;
          tmp_pu11 = tmp_pu11 + 1;
        }
      }
      for (; tmp_pu6 != (uint8_t *)0x0; tmp_pu6 = tmp_pu6 + -1) {
        *(char *)tmp_pu11 = (char)*tmp_pu9;
        tmp_pu9 = (uint *)((int)tmp_pu9 + (uint)tmp_b12 * -2 + 1);
        tmp_pu11 = (uint *)((int)tmp_pu11 + (uint)tmp_b12 * -2 + 1);
      }
      (&g_unk_00abef8c)[tmp_i2 * 2] = tmp_pu8;
      tmp_i2 = g_unk_00abef88;
      g_unk_00abf18c = g_unk_00abf18c + (int)tmp_pu1;
      tmp_pu9 = (uint *)&local_41c;
      do {
        tmp_pu8 = tmp_pu9;
        tmp_u3 = *tmp_pu8 + 0xfefefeff & ~*tmp_pu8;
        tmp_u4 = tmp_u3 & 0x80808080;
        tmp_pu9 = tmp_pu8 + 1;
      } while (tmp_u4 == 0);
      if ((tmp_u3 & 0x8080) == 0) {
        tmp_pu9 = (uint *)((int)tmp_pu8 + 6);
        tmp_u4 = tmp_u4 >> 0x10;
      }
      tmp_pu7 = (uint8_t *)
               ((int)tmp_pu9 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)&local_41c));
      if (0x7ff < (int)(g_unk_00abf18c + (int)tmp_pu7)) {
        G_Error("G_AddSpawnVarToken: MAX_SPAWN_VARS");
      }
      tmp_pu9 = (uint *)(g_unk_00abf18c + 0xabf190);
      tmp_pu1 = tmp_pu7 + 1;
      tmp_pu6 = tmp_pu1;
      tmp_pu8 = (uint *)&local_41c;
      tmp_pu11 = tmp_pu9;
      if ((uint8_t *)0x7 < tmp_pu1) {
        if (((uint)tmp_pu9 & 1) != 0) {
          *(char *)tmp_pu9 = local_41c;
          tmp_pu11 = (uint *)(g_unk_00abf18c + 0xabf191);
          tmp_pu8 = auStack_41b;
          tmp_pu6 = tmp_pu7;
        }
        tmp_pu10 = tmp_pu11;
        if (((uint)tmp_pu11 & 2) != 0) {
          tmp_u4 = *tmp_pu8;
          tmp_pu10 = (uint *)((int)tmp_pu11 + 2);
          tmp_pu8 = (uint *)((int)tmp_pu8 + 2);
          tmp_pu6 = tmp_pu6 + -2;
          *(short *)tmp_pu11 = (short)tmp_u4;
        }
        tmp_pu11 = tmp_pu10;
        if (((uint)tmp_pu10 & 4) != 0) {
          tmp_u4 = *tmp_pu8;
          tmp_pu11 = tmp_pu10 + 1;
          tmp_pu8 = tmp_pu8 + 1;
          tmp_pu6 = tmp_pu6 + -4;
          *tmp_pu10 = tmp_u4;
        }
      }
      for (; tmp_pu6 != (uint8_t *)0x0; tmp_pu6 = tmp_pu6 + -1) {
        *(char *)tmp_pu11 = (char)*tmp_pu8;
        tmp_pu8 = (uint *)((int)tmp_pu8 + (uint)tmp_b12 * -2 + 1);
        tmp_pu11 = (uint *)((int)tmp_pu11 + (uint)tmp_b12 * -2 + 1);
      }
      g_unk_00abf18c = g_unk_00abf18c + (int)tmp_pu1;
      g_unk_00abef88 = g_unk_00abef88 + 1;
      (&g_unk_00abef90)[tmp_i2 * 2] = tmp_pu9;
    }
    tmp_u5 = 1;
  }
  return tmp_u5;
}

void G_SpawnEntitiesFromString(void)
{
  int tmp_i1;
  
  G_Printf("Enable spawning!\n");
  g_unk_00abef84 = 1;
  g_unk_00abef88 = 0;
  tmp_i1 = G_ParseSpawnVars();
  if (tmp_i1 == 0) {
    G_Error("SpawnEntities: no entities");
  }
  SP_worldspawn();
  while( true ) {
    tmp_i1 = G_ParseSpawnVars();
    if (tmp_i1 == 0) break;
    G_SpawnGEntityFromSpawnVars();
  }
  G_Printf("Disable spawning!\n");
  g_unk_00abef84 = 0;
  return;
}

void G_ResetXP_part_1(int param_1)
{
  uint16_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint tmp_u5;
  int tmp_i6;
  uint tmp_u7;
  uint32_t *tmp_pu8;
  uint16_t *tmp_pu9;
  uint16_t *tmp_pu10;
  bool tmp_b11;
  uint8_t local_21c [4];
  uint32_t auStack_218 [63];
  uint8_t local_11c [4];
  uint32_t auStack_118 [66];
  
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xbf4) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xc30) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xbf8) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xc34) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xbfc) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xc38) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xc00) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xc3c) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xc04) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xc40) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xc08) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xc44) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xc0c) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xc48) = 0;
  G_CalcRank(*(uint32_t *)(param_1 + 400));
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xf0) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0x110) = 0;
  if (3 < GHIDRA_FIELD(g_war, 12, 4) - 1) {
    tmp_pu3 = (uint32_t *)local_21c;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x3d4) = 0;
    tmp_u7 = 0;
    tmp_i6 = *(int *)(param_1 + 400);
    do {
      *(uint32_t *)((int)tmp_pu3 + tmp_u7) = *(uint32_t *)(tmp_i6 + 400 + tmp_u7);
      *(uint32_t *)((int)auStack_218 + tmp_u7) = *(uint32_t *)(tmp_i6 + 0x194 + tmp_u7);
      tmp_u7 = tmp_u7 + 8;
    } while (tmp_u7 < 0x100);
    tmp_pu4 = (uint32_t *)local_11c;
    tmp_u7 = 0;
    do {
      *(uint32_t *)((int)tmp_pu4 + tmp_u7) = *(uint32_t *)(tmp_i6 + 0x290 + tmp_u7);
      *(uint32_t *)((int)auStack_118 + tmp_u7) = *(uint32_t *)(tmp_i6 + 0x294 + tmp_u7);
      tmp_u7 = tmp_u7 + 8;
    } while (tmp_u7 < 0x100);
    SetWolfSpawnWeapons(tmp_i6,1);
    tmp_i6 = *(int *)(param_1 + 400);
    tmp_u7 = 0x100;
    tmp_pu9 = (uint16_t *)(tmp_i6 + 400);
    tmp_b11 = ((uint)tmp_pu9 & 1) != 0;
    if (tmp_b11) {
      tmp_pu9 = (uint16_t *)(tmp_i6 + 0x191);
      tmp_u7 = 0xff;
      *(uint8_t *)(tmp_i6 + 400) = local_21c[0];
      tmp_pu3 = (uint32_t *)((int)local_21c + 1);
    }
    tmp_pu10 = tmp_pu9;
    if (((uint)tmp_pu9 & 2) != 0) {
      tmp_u1 = *(uint16_t *)tmp_pu3;
      tmp_pu10 = tmp_pu9 + 1;
      tmp_pu3 = (uint32_t *)((int)tmp_pu3 + 2);
      tmp_u7 = tmp_u7 - 2;
      *tmp_pu9 = tmp_u1;
    }
    tmp_u5 = 0;
    do {
      tmp_u2 = *(uint32_t *)((int)tmp_pu3 + tmp_u5);
      *(uint32_t *)((int)tmp_pu10 + tmp_u5 + 4) = *(uint32_t *)((int)tmp_pu3 + tmp_u5 + 4);
      *(uint32_t *)((int)tmp_pu10 + tmp_u5) = tmp_u2;
      tmp_u5 = tmp_u5 + 8;
    } while (tmp_u5 < (tmp_u7 & 0xfffffff8));
    tmp_pu8 = (uint32_t *)((int)tmp_pu10 + tmp_u5);
    tmp_pu3 = (uint32_t *)((int)tmp_pu3 + tmp_u5);
    tmp_i6 = 0;
    if ((tmp_u7 & 4) != 0) {
      *tmp_pu8 = *tmp_pu3;
      tmp_i6 = 4;
    }
    if ((tmp_u7 & 2) != 0) {
      *(uint16_t *)((int)tmp_pu8 + tmp_i6) = *(uint16_t *)((int)tmp_pu3 + tmp_i6);
      tmp_i6 = tmp_i6 + 2;
    }
    if (tmp_b11) {
      *(uint8_t *)((int)tmp_pu8 + tmp_i6) = *(uint8_t *)((int)tmp_pu3 + tmp_i6);
    }
    tmp_i6 = *(int *)(param_1 + 400);
    tmp_u7 = 0x100;
    tmp_pu9 = (uint16_t *)(tmp_i6 + 0x290);
    tmp_b11 = ((uint)tmp_pu9 & 1) != 0;
    if (tmp_b11) {
      tmp_pu9 = (uint16_t *)(tmp_i6 + 0x291);
      tmp_u7 = 0xff;
      *(uint8_t *)(tmp_i6 + 0x290) = local_11c[0];
      tmp_pu4 = (uint32_t *)((int)local_11c + 1);
    }
    tmp_pu10 = tmp_pu9;
    if (((uint)tmp_pu9 & 2) != 0) {
      tmp_u1 = *(uint16_t *)tmp_pu4;
      tmp_pu10 = tmp_pu9 + 1;
      tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
      tmp_u7 = tmp_u7 - 2;
      *tmp_pu9 = tmp_u1;
    }
    tmp_u5 = 0;
    do {
      tmp_u2 = *(uint32_t *)((int)tmp_pu4 + tmp_u5);
      *(uint32_t *)((int)tmp_pu10 + tmp_u5 + 4) = *(uint32_t *)((int)tmp_pu4 + tmp_u5 + 4);
      *(uint32_t *)((int)tmp_pu10 + tmp_u5) = tmp_u2;
      tmp_u5 = tmp_u5 + 8;
    } while (tmp_u5 < (tmp_u7 & 0xfffffff8));
    tmp_pu3 = (uint32_t *)((int)tmp_pu10 + tmp_u5);
    tmp_pu4 = (uint32_t *)((int)tmp_pu4 + tmp_u5);
    tmp_i6 = 0;
    if ((tmp_u7 & 4) != 0) {
      *tmp_pu3 = *tmp_pu4;
      tmp_i6 = 4;
    }
    if ((tmp_u7 & 2) != 0) {
      *(uint16_t *)((int)tmp_pu3 + tmp_i6) = *(uint16_t *)((int)tmp_pu4 + tmp_i6);
      tmp_i6 = tmp_i6 + 2;
    }
    if (tmp_b11) {
      *(uint8_t *)((int)tmp_pu3 + tmp_i6) = *(uint8_t *)((int)tmp_pu4 + tmp_i6);
    }
  }
  ClientUserinfoChanged((param_1 + -0x93e4a0 >> 9) * -0x55555555);
  return;
}

void G_UpgradeSkill(int param_1,int param_2)
{
  uint *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  char *__s;
  size_t tmp_s6;
  uint32_t tmp_u7;
  byte tmp_b8;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t uStack_14;
  
  uStack_14 = 0xde31d;
  tmp_i3 = G_LuaHook_UpgradeSkill(((int)g_entities - param_1 >> 9) * -0x55555555,param_2);
  if (tmp_i3 != 0) {
    return;
  }
  if (GHIDRA_FIELD(g_debugSkills, 12, 4) == 0) {
    tmp_i3 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  }
  else {
    tmp_i3 = param_2 * 4 + *(int *)(param_1 + 400);
    tmp_u7 = *(uint32_t *)(tmp_i3 + 0xc30);
    tmp_u7 = va("sdbg \"^%c(SK: %2i XP: %.0f) %s: You raised your skill level to %i.\"\n",
               param_2 + 0x31,tmp_u7,(double)*(float *)(tmp_i3 + 0xbf4),
               *(uint32_t *)(skillNames + param_2 * 4),tmp_u7);
    tmp_i3 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand(tmp_i3,tmp_u7);
    trap_RealTime(&local_40);
    if ((1 < (int)GHIDRA_FIELD(g_debugSkills, 12, 4)) && (skillDebugLog != -1)) {
      tmp_i5 = *(int *)(param_1 + 400) + param_2 * 4;
      tmp_u7 = *(uint32_t *)(tmp_i5 + 0xc30);
      __s = (char *)va("%02d:%02d:%02d : ^%c(SK: %2i XP: %.0f) %s: %s raised in skill level to %i.\n"
                       ,local_38,local_3c,local_40,param_2 + 0x31,tmp_u7,
                       (double)*(float *)(tmp_i5 + 0xbf4),*(uint32_t *)(skillNames + param_2 * 4),
                       *(int *)(param_1 + 400) + 0x5f8,tmp_u7);
      tmp_s6 = strlen(__s);
      trap_FS_Write(__s,tmp_s6,skillDebugLog);
    }
  }
  tmp_i2 = g_unk_002bb384;
  tmp_i5 = *(int *)(param_1 + 400);
  tmp_i4 = *(int *)(tmp_i5 + 0xc34) + *(int *)(tmp_i5 + 0xc30) + *(int *)(tmp_i5 + 0xc38) +
          *(int *)(tmp_i5 + 0xc3c) + *(int *)(tmp_i5 + 0xc40) + *(int *)(tmp_i5 + 0xc44) +
          *(int *)(tmp_i5 + 0xc48);
  *(uint32_t *)(tmp_i5 + 0xc4c) = 0;
  if (tmp_i4 < tmp_i2) {
    if (tmp_i4 < g_unk_002bb380) goto LAB_000de3d0;
    tmp_i5 = *(int *)(param_1 + 400);
    if (*(int *)(tmp_i5 + 0xc4c) < 10) {
      tmp_u7 = 9;
      goto LAB_000de570;
    }
LAB_000de4ef:
    if (tmp_i4 < g_unk_002bb378) {
LAB_000de3ef:
      if (tmp_i4 < g_unk_002bb374) goto LAB_000de50e;
      tmp_i5 = *(int *)(param_1 + 400);
      if (*(int *)(tmp_i5 + 0xc4c) < 10) {
        tmp_u7 = 6;
        goto LAB_000de570;
      }
LAB_000de40e:
      if (tmp_i4 < g_unk_002bb36c) goto LAB_000de52d;
      tmp_i5 = *(int *)(param_1 + 400);
      if (*(int *)(tmp_i5 + 0xc4c) < 10) {
        tmp_u7 = 4;
        goto LAB_000de570;
      }
LAB_000de42d:
      if (tmp_i4 < g_unk_002bb364) goto LAB_000de54c;
      tmp_i5 = *(int *)(param_1 + 400);
      if (*(int *)(tmp_i5 + 0xc4c) < 10) {
        tmp_u7 = 2;
        goto LAB_000de570;
      }
    }
    else {
      tmp_i5 = *(int *)(param_1 + 400);
      if (*(int *)(tmp_i5 + 0xc4c) < 10) {
        tmp_u7 = 7;
        goto LAB_000de570;
      }
LAB_000de50e:
      if (tmp_i4 < g_unk_002bb370) goto LAB_000de40e;
      tmp_i5 = *(int *)(param_1 + 400);
      if (*(int *)(tmp_i5 + 0xc4c) < 10) {
        tmp_u7 = 5;
        goto LAB_000de570;
      }
LAB_000de52d:
      if (tmp_i4 < g_unk_002bb368) goto LAB_000de42d;
      tmp_i5 = *(int *)(param_1 + 400);
      if (*(int *)(tmp_i5 + 0xc4c) < 10) {
        tmp_u7 = 3;
        goto LAB_000de570;
      }
LAB_000de54c:
      if (rankTable <= tmp_i4) {
        tmp_i5 = *(int *)(param_1 + 400);
        tmp_u7 = 1;
        if (*(int *)(tmp_i5 + 0xc4c) < 10) goto LAB_000de570;
      }
    }
    ClientUserinfoChanged(tmp_i3);
  }
  else {
    tmp_i5 = *(int *)(param_1 + 400);
    if (9 < *(int *)(tmp_i5 + 0xc4c)) {
LAB_000de3d0:
      if (tmp_i4 < g_unk_002bb37c) goto LAB_000de4ef;
      tmp_i5 = *(int *)(param_1 + 400);
      if (*(int *)(tmp_i5 + 0xc4c) < 10) {
        tmp_u7 = 8;
        goto LAB_000de570;
      }
      goto LAB_000de3ef;
    }
    tmp_u7 = 10;
LAB_000de570:
    *(uint32_t *)(tmp_i5 + 0xc4c) = tmp_u7;
    ClientUserinfoChanged(tmp_i3);
  }
  if (param_2 == 0) {
    if ((*(byte *)(*(int *)(param_1 + 400) + 0xed0) & 2) != 0) {
      tmp_i3 = AddWeaponToPlayer(*(int *)(param_1 + 400),0x13,1,0,0);
      if (tmp_i3 != 0) {
        tmp_pu1 = (uint *)(*(int *)(param_1 + 400) + 0xd4);
        *tmp_pu1 = *tmp_pu1 | 0x40;
        return;
      }
      return;
    }
    tmp_i3 = EntHasAdren(param_1);
    if (tmp_i3 == 0) {
      return;
    }
  }
  else {
    tmp_i3 = EntHasAdren(param_1);
    if (tmp_i3 == 0) {
      if (param_2 != 1) {
        return;
      }
      tmp_i3 = *(int *)(param_1 + 400);
      if (*(int *)(tmp_i3 + 0xbc8) == 2) {
        if ((*(byte *)(tmp_i3 + 0xed4) & 0x10) != 0) {
          *(uint32_t *)(tmp_i3 + 0x158) = 0x7fffffff;
          return;
        }
        return;
      }
      return;
    }
  }
  tmp_b8 = 1;
  if ((GHIDRA_FIELD(g_adrenaline, 12, 4) & 4) == 0) {
    tmp_b8 = -((GHIDRA_FIELD(g_adrenaline, 12, 4) & 1) == 0) & 0xc;
  }
  AddWeaponToPlayer(*(uint32_t *)(param_1 + 400),0x2b,0,tmp_b8,0);
  return;
}

void G_LogTeamKill(int param_1,uint32_t param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  
  tmp_i2 = BG_DuplicateWeapon(param_2);
  if (*(int *)(param_1 + 400) != 0) {
    tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0x6d8 + tmp_i2 * 0xc);
    *tmp_pi1 = *tmp_pi1 + 1;
    tmp_u3 = va("%d %d %d",*(uint32_t *)(*(int *)(param_1 + 400) + 3000),
               *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc8),tmp_i2);
    trap_PbStat((param_1 + -0x93e4a0 >> 9) * -0x55555555,&g_unk_00257f15,tmp_u3);
  }
  return;
}

void G_LogRegionHit(int param_1,int param_2)
{
  int *tmp_pi1;
  uint32_t tmp_u2;
  
  if (*(int *)(param_1 + 400) != 0) {
    tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0xba8 + param_2 * 4);
    *tmp_pi1 = *tmp_pi1 + 1;
    tmp_u2 = va("%d %d %d",*(uint32_t *)(*(int *)(param_1 + 400) + 3000),
               *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc8),param_2);
    trap_PbStat((param_1 + -0x93e4a0 >> 9) * -0x55555555,"hr",tmp_u2);
  }
  return;
}

void G_PrintAccuracyLog(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t *local_820;
  uint8_t local_81c [2056];
  uint32_t uStack_14;
  
  tmp_i3 = 0;
  uStack_14 = 0xdea40;
  Q_strncpyz(local_81c,"WeaponStats",0x800);
  do {
    tmp_i1 = BG_ValidStatWeapon(tmp_i3);
    if (tmp_i1 != 0) {
      tmp_i1 = tmp_i3 * 0xc + 0x6c0 + *(int *)(param_1 + 400);
      tmp_u2 = va(" %i %i %i",*(uint32_t *)(tmp_i1 + 0x14),*(uint32_t *)(tmp_i1 + 0x1c),
                 *(uint32_t *)(tmp_i1 + 0x18));
      Q_strcat(local_81c,0x800,tmp_u2);
    }
    tmp_i3 = tmp_i3 + 1;
  } while (tmp_i3 != 0x34);
  tmp_u2 = va(" %i",*(uint32_t *)(*(int *)(param_1 + 400) + 0x944));
  Q_strcat(local_81c,0x800,tmp_u2);
  tmp_i3 = 0;
  tmp_u2 = va(" %i",6);
  Q_strcat(local_81c,0x800,tmp_u2);
  local_820 = &level;
  do {
    tmp_u2 = va(" %i",*(uint32_t *)(*(int *)(param_1 + 400) + 0x948 + tmp_i3 * 4));
    Q_strcat(local_81c,0x800,tmp_u2);
    if (*(int *)(*(int *)(param_1 + 400) + 3000) == 1) {
      tmp_u2 = local_820[0x7f66e4];
    }
    else {
      tmp_u2 = local_820[0x7f66dc];
    }
    tmp_i3 = tmp_i3 + 1;
    tmp_u2 = va(" %i",tmp_u2);
    Q_strcat(local_81c,0x800,tmp_u2);
    local_820 = local_820 + 1;
  } while (tmp_i3 != 6);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,local_81c);
  return;
}

void G_SetPlayerScore(int param_1)
{
  *(int *)(param_1 + 0x110) =
       (int)ROUND((float)(int)ROUND((float)(int)ROUND((float)(int)ROUND((float)(int)ROUND((float)(
                                                  int)ROUND((float)(int)ROUND(*(float *)(param_1 +
                                                                                        0xbf4) + 0.0
                                                                             ) +
                                                            *(float *)(param_1 + 0xbf8)) +
                                                  *(float *)(param_1 + 0xbfc)) +
                                                  *(float *)(param_1 + 0xc00)) +
                                                  *(float *)(param_1 + 0xc04)) +
                                    *(float *)(param_1 + 0xc08)) + *(float *)(param_1 + 0xc0c));
  return;
}

void G_SetPlayerSkill(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i2 = G_LuaHook_SetPlayerSkill((param_1 - level >> 2) * -0x66e64f79,param_2);
  if (tmp_i2 != 0) {
    return;
  }
  switch(param_2) {
  case 0:
    tmp_i2 = GHIDRA_FIELD(jp_maxLevelBattleSense, 12, 4);
    break;
  case 1:
    tmp_i2 = GHIDRA_FIELD(jp_maxLevelEngineer, 12, 4);
    break;
  case 2:
    tmp_i2 = GHIDRA_FIELD(jp_maxLevelMedic, 12, 4);
    break;
  case 3:
    tmp_i2 = GHIDRA_FIELD(jp_maxLevelFieldOp, 12, 4);
    break;
  case 4:
    tmp_i2 = GHIDRA_FIELD(jp_maxLevelLightWeapons, 12, 4);
    break;
  case 5:
    tmp_i2 = GHIDRA_FIELD(jp_maxLevelSoldier, 12, 4);
    break;
  case 6:
    tmp_i2 = GHIDRA_FIELD(jp_maxLevelCovertOp, 12, 4);
    break;
  default:
    tmp_i2 = 6;
    goto LAB_000defe0;
  }
  if (tmp_i2 < 7) {
LAB_000defe0:
    if (GHIDRA_FIELD(n_noSkillUpgrades, 12, 4) != 0) goto LAB_000defc0;
    tmp_i3 = param_1 + param_2 * 4;
    *(uint32_t *)(tmp_i3 + 0xed0) = 0;
    *(uint32_t *)(tmp_i3 + 0xc30) = 0;
    if (tmp_i2 < 2) goto LAB_000deea0;
    tmp_i3 = *(int *)(skillLevels + param_2 * 0x18 + 4);
    if (-1 < tmp_i3) goto LAB_000ded70;
LAB_000ded99:
    if (tmp_i2 == 2) goto LAB_000deea0;
    tmp_i3 = *(int *)(skillLevels + param_2 * 0x18 + 8);
    if (-1 < tmp_i3) goto LAB_000dedb3;
LAB_000deddc:
    if (tmp_i2 == 3) goto LAB_000deea0;
  }
  else {
    if (GHIDRA_FIELD(n_noSkillUpgrades, 12, 4) != 0) {
LAB_000defc0:
      tmp_i2 = param_1 + param_2 * 4;
      *(uint32_t *)(tmp_i2 + 0xed0) = 0;
      *(uint32_t *)(tmp_i2 + 0xc30) = 0;
      goto LAB_000deea0;
    }
    tmp_i2 = param_1 + param_2 * 4;
    *(uint32_t *)(tmp_i2 + 0xed0) = 0;
    *(uint32_t *)(tmp_i2 + 0xc30) = 0;
    tmp_i2 = 6;
    tmp_i3 = *(int *)(skillLevels + param_2 * 0x18 + 4);
    if (-1 < tmp_i3) {
LAB_000ded70:
      tmp_i1 = param_1 + param_2 * 4;
      if ((float)tmp_i3 <= *(float *)(tmp_i1 + 0xbf4)) {
        *(uint *)(tmp_i1 + 0xed0) = *(uint *)(tmp_i1 + 0xed0) | 2;
        *(uint32_t *)(tmp_i1 + 0xc30) = 1;
      }
      goto LAB_000ded99;
    }
    tmp_i3 = *(int *)(skillLevels + param_2 * 0x18 + 8);
    if (-1 < tmp_i3) {
LAB_000dedb3:
      tmp_i1 = param_1 + param_2 * 4;
      if ((float)tmp_i3 <= *(float *)(tmp_i1 + 0xbf4)) {
        *(uint *)(tmp_i1 + 0xed0) = *(uint *)(tmp_i1 + 0xed0) | 4;
        *(uint32_t *)(tmp_i1 + 0xc30) = 2;
      }
      goto LAB_000deddc;
    }
  }
  if ((-1 < *(int *)(skillLevels + param_2 * 0x18 + 0xc)) &&
     (tmp_i3 = param_1 + param_2 * 4,
     (float)*(int *)(skillLevels + param_2 * 0x18 + 0xc) <= *(float *)(tmp_i3 + 0xbf4))) {
    *(uint *)(tmp_i3 + 0xed0) = *(uint *)(tmp_i3 + 0xed0) | 8;
    *(uint32_t *)(tmp_i3 + 0xc30) = 3;
  }
  if (tmp_i2 != 4) {
    if ((-1 < *(int *)(skillLevels + param_2 * 0x18 + 0x10)) &&
       (tmp_i3 = param_1 + param_2 * 4,
       (float)*(int *)(skillLevels + param_2 * 0x18 + 0x10) <= *(float *)(tmp_i3 + 0xbf4))) {
      *(uint *)(tmp_i3 + 0xed0) = *(uint *)(tmp_i3 + 0xed0) | 0x10;
      *(uint32_t *)(tmp_i3 + 0xc30) = 4;
    }
    if (((tmp_i2 == 6) && (-1 < *(int *)(skillLevels + param_2 * 0x18 + 0x14))) &&
       (tmp_i2 = param_1 + param_2 * 4,
       (float)*(int *)(skillLevels + param_2 * 0x18 + 0x14) <= *(float *)(tmp_i2 + 0xbf4))) {
      *(uint *)(tmp_i2 + 0xed0) = *(uint *)(tmp_i2 + 0xed0) | 0x20;
      *(uint32_t *)(tmp_i2 + 0xc30) = 5;
    }
  }
LAB_000deea0:
  *(int *)(param_1 + 0x110) =
       (int)ROUND((float)(int)ROUND((float)(int)ROUND((float)(int)ROUND((float)(int)ROUND((float)(
                                                  int)ROUND((float)(int)ROUND(*(float *)(param_1 +
                                                                                        0xbf4) + 0.0
                                                                             ) +
                                                            *(float *)(param_1 + 0xbf8)) +
                                                  *(float *)(param_1 + 0xbfc)) +
                                                  *(float *)(param_1 + 0xc00)) +
                                                  *(float *)(param_1 + 0xc04)) +
                                    *(float *)(param_1 + 0xc08)) + *(float *)(param_1 + 0xc0c));
  return;
}

uint32_t G_LoseSkillPointsExt(int param_1,int param_2,float param_3)
{
  int tmp_i1;
  float tmp_f2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  
  if (param_1 == 0) {
    tmp_u3 = 0;
  }
  else {
    tmp_u3 = 0;
    if ((*(int *)(param_1 + 400) != 0) && (GHIDRA_FIELD(g_gametype, 12, 4) != 5)) {
      tmp_i1 = *(int *)(param_1 + 400) + param_2 * 4;
      tmp_f2 = *(float *)(tmp_i1 + 0xbf4);
      *(float *)(tmp_i1 + 0xbf4) = tmp_f2 - param_3;
      tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 0x10 + (param_2 + 0x308) * 4);
      G_SetPlayerSkill(*(int *)(param_1 + 400),param_2);
      tmp_i4 = *(int *)(param_1 + 400);
      if ((*(int *)(tmp_i4 + 0x10 + (param_2 + 0x308) * 4) != tmp_i1) &&
         (*(int *)(tmp_i4 + 0x5ac) == 2)) {
        G_UpgradeSkill();
        tmp_i4 = *(int *)(param_1 + 400);
      }
      tmp_f2 = tmp_f2 - *(float *)(tmp_i4 + 0xbf4 + param_2 * 4);
      tmp_i5 = *(int *)(tmp_i4 + 300) + 0x1c;
      tmp_i1 = *(int *)(tmp_i4 + 3000);
      (&g_unk_00abe8ac)[tmp_i5] = (int)ROUND((float)(int)(&g_unk_00abe8ac)[tmp_i5] - tmp_f2);
      (&g_unk_00abe8a4)[(int)(&g_unk_007f918b + param_2 * 2 + tmp_i1)] =
           (float)(&g_unk_00abe8a4)[(int)(&g_unk_007f918b + param_2 * 2 + tmp_i1)] - tmp_f2;
      tmp_u3 = 1;
    }
  }
  return tmp_u3;
}

void G_LoseSkillPoints(int param_1,int param_2,float param_3)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  
  if ((((param_1 != 0) && (tmp_i5 = *(int *)(param_1 + 400), tmp_i5 != 0)) &&
      (*(int *)(tmp_i5 + 3000) - 1U < 2)) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
    tmp_i5 = tmp_i5 + param_2 * 4;
    tmp_f1 = *(float *)(tmp_i5 + 0xbf4);
    if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) {
      *(float *)(tmp_i5 + 0xbf4) = tmp_f1 - param_3;
      tmp_i5 = *(int *)(*(int *)(param_1 + 400) + 0x10 + (param_2 + 0x308) * 4);
      G_SetPlayerSkill(*(int *)(param_1 + 400),param_2);
      tmp_i3 = *(int *)(param_1 + 400);
      if ((tmp_i5 != *(int *)(tmp_i3 + 0x10 + (param_2 + 0x308) * 4)) &&
         (*(int *)(tmp_i3 + 0x5ac) == 2)) {
        G_UpgradeSkill();
        tmp_i3 = *(int *)(param_1 + 400);
      }
      tmp_i5 = *(int *)(tmp_i3 + 300) + 0x1c;
      tmp_f2 = tmp_f1 - *(float *)(tmp_i3 + 0x14 + (param_2 + 0x2f8) * 4);
      (&g_unk_00abe8ac)[tmp_i5] = (int)ROUND((float)(int)(&g_unk_00abe8ac)[tmp_i5] - tmp_f2);
      (&g_unk_00abe8a4)[(int)(&g_unk_007f918b + param_2 * 2 + *(int *)(tmp_i3 + 3000))] =
           (float)(&g_unk_00abe8a4)[(int)(&g_unk_007f918b + param_2 * 2 + *(int *)(tmp_i3 + 3000))] -
           tmp_f2;
      tmp_i5 = *(int *)(param_1 + 400);
      tmp_u4 = va("%d %d %d %f",*(uint32_t *)(tmp_i5 + 3000),*(uint32_t *)(tmp_i5 + 0xbc8),param_2,
                 (double)(tmp_f1 - *(float *)(tmp_i5 + 0x14 + (param_2 + 0x2f8) * 4)));
      trap_PbStat((param_1 + -0x93e4a0 >> 9) * -0x55555555,"loseskill",tmp_u4);
    }
  }
  return;
}

void G_XPDecay(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  int local_58;
  int local_30 [8];
  
  local_30[2] = 1;
  local_30[3] = 3;
  local_30[4] = 6;
  local_30[0] = 5;
  local_30[1] = 2;
  if ((GHIDRA_FIELD(g_XPDecay, 12, 4) & 1) == 0) {
    return;
  }
  if ((float)GHIDRA_FIELD(g_XPDecayRate, 8, 4) == 0.0) {
    return;
  }
  if (param_3 == 0) {
    if (((GHIDRA_FIELD(g_XPDecay, 12, 4) & 8) != 0) && (*(int *)(*(int *)(param_1 + 400) + 3000) == 3)) {
      return;
    }
    if ((GHIDRA_FIELD(g_XPDecay, 12, 4) & 0x10) == 0) {
      if (((GHIDRA_FIELD(g_XPDecay, 12, 4) & 0x20) == 0) || (GHIDRA_FIELD(g_gamestate, 12, 4) != 0)) goto LAB_000df3b5;
    }
    else {
      if (GHIDRA_FIELD(g_gamestate, 12, 4) != 0) {
        return;
      }
      if ((GHIDRA_FIELD(g_XPDecay, 12, 4) & 0x20) == 0) goto LAB_000df3b5;
    }
    if (*(int *)(*(int *)(param_1 + 400) + 3000) - 1U < 2) {
      return;
    }
  }
LAB_000df3b5:
  tmp_i5 = 0;
  tmp_f3 = (float)param_2 * (float)GHIDRA_FIELD(g_XPDecayRate, 8, 4);
  do {
    while (((param_3 == 0 &&
            (((((GHIDRA_FIELD(g_XPDecay, 12, 4) & 4) != 0 &&
               (local_30[*(int *)(*(int *)(param_1 + 400) + 0xbc8)] == tmp_i5)) ||
              ((tmp_i5 == 0 && ((GHIDRA_FIELD(g_XPDecay, 12, 4) & 0x40) != 0)))) ||
             ((tmp_i5 == 4 && ((GHIDRA_FIELD(g_XPDecay, 12, 4) & 0x80) != 0)))))) ||
           ((float)GHIDRA_FIELD(g_XPDecayFloor, 8, 4) < 0.0))) {
LAB_000df430:
      tmp_i5 = tmp_i5 + 1;
      if (tmp_i5 == 7) {
        return;
      }
    }
    tmp_i1 = *(int *)(param_1 + 400) + tmp_i5 * 4;
    tmp_f2 = *(float *)(tmp_i1 + 0xbf4);
    if (tmp_f2 < (float)GHIDRA_FIELD(g_XPDecayFloor, 8, 4)) goto LAB_000df430;
    tmp_f4 = tmp_f3;
    if (tmp_f2 - tmp_f3 < (float)GHIDRA_FIELD(g_XPDecayFloor, 8, 4)) {
      tmp_f4 = tmp_f2 - (float)GHIDRA_FIELD(g_XPDecayFloor, 8, 4);
    }
    if (tmp_f2 < tmp_f4) {
      tmp_f4 = tmp_f2;
    }
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) goto LAB_000df430;
    *(float *)(tmp_i1 + 0xbf4) = tmp_f2 - tmp_f4;
    tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 0x10 + (tmp_i5 + 0x308) * 4);
    G_SetPlayerSkill(*(int *)(param_1 + 400),tmp_i5);
    local_58 = *(int *)(param_1 + 400);
    if ((tmp_i1 != *(int *)(local_58 + 0x10 + (tmp_i5 + 0x308) * 4)) &&
       (*(int *)(local_58 + 0x5ac) == 2)) {
      G_UpgradeSkill();
      local_58 = *(int *)(param_1 + 400);
    }
    tmp_f2 = tmp_f2 - *(float *)(local_58 + 0xbf4 + tmp_i5 * 4);
    tmp_i1 = *(int *)(local_58 + 300) + 0x1c;
    (&g_unk_00abe8ac)[tmp_i1] = (int)ROUND((float)(int)(&g_unk_00abe8ac)[tmp_i1] - tmp_f2);
    tmp_i1 = tmp_i5 * 2;
    tmp_i5 = tmp_i5 + 1;
    (&g_unk_00abe8a4)[(int)(&g_unk_007f918b + tmp_i1 + *(int *)(local_58 + 3000))] =
         (float)(&g_unk_00abe8a4)[(int)(&g_unk_007f918b + tmp_i1 + *(int *)(local_58 + 3000))] - tmp_f2;
    if (tmp_i5 == 7) {
      return;
    }
  } while( true );
}

void G_ResetXP(int param_1)
{
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xc4c) = 0;
    G_ResetXP_part_1();
    return;
  }
  return;
}

void G_AddSkillPoints(int param_1,int param_2,float param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  tmp_u2 = GHIDRA_FIELD(g_gametype, 12, 4);
  if ((((*(int *)(param_1 + 400) != 0) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) &&
      (tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 3000), tmp_i1 - 1U < 2)) &&
     (GHIDRA_FIELD(g_gametype, 12, 4) != 5)) {
    (&g_unk_00abe8a4)[(int)(&g_unk_007f918b + param_2 * 2 + tmp_i1)] =
         (float)(&g_unk_00abe8a4)[(int)(&g_unk_007f918b + param_2 * 2 + tmp_i1)] + param_3;
    tmp_i1 = *(int *)(param_1 + 400) + param_2 * 4;
    *(float *)(tmp_i1 + 0xbf4) = *(float *)(tmp_i1 + 0xbf4) + param_3;
    tmp_i1 = *(int *)(param_1 + 400);
    if (((int)GHIDRA_FIELD(g_maxXP, 12, 4) < 0) ||
       ((float)*(int *)(tmp_i1 + 0x110) + param_3 < (float)(int)GHIDRA_FIELD(g_maxXP, 12, 4))) {
      if ((tmp_u2 != 7) || ((g_TDMOptions[0xc] & 1) == 0)) {
        tmp_i3 = *(int *)(tmp_i1 + 300) + 0x1c;
        (&g_unk_00abe8ac)[tmp_i3] = (int)ROUND((float)(int)(&g_unk_00abe8ac)[tmp_i3] + param_3);
      }
      tmp_u2 = va("%d %d %d %f",*(uint32_t *)(tmp_i1 + 3000),*(uint32_t *)(tmp_i1 + 0xbc8),param_2,
                 (double)param_3);
      trap_PbStat((param_1 + -0x93e4a0 >> 9) * -0x55555555,"addskill",tmp_u2);
      tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 0x10 + (param_2 + 0x308) * 4);
      G_SetPlayerSkill(*(int *)(param_1 + 400),param_2);
      if (*(int *)(*(int *)(param_1 + 400) + 0x10 + (param_2 + 0x308) * 4) != tmp_i1) {
        G_UpgradeSkill();
        return;
      }
    }
    else {
      *(uint32_t *)(tmp_i1 + 0xc4c) = 0;
      G_ResetXP_part_1();
      if (GHIDRA_FIELD(g_maxXP, 12, 4) != 0) {
        trap_SendServerCommand
                  ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                   "cp \"You\'ve reached the max XP allowed on this server. Your XP has been reset =(\" 1"
                  );
      }
    }
  }
  return;
}

void G_LoseKillSkillPoints(int param_1,uint32_t param_2)
{
  uint32_t uStack0000000c;
  
  if (*(int *)(param_1 + 400) != 0) {
    switch(param_2) {
    case 1:
    case 2:
    case 3:
    case 0xf:
    case 0x11:
    case 0x2b:
    case 0x33:
    case 0x41:
      uStack0000000c = 0x40800000;
      G_LoseSkillPoints();
      return;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0x10:
    case 0x12:
    case 0x24:
    case 0x25:
    case 0x2c:
    case 0x31:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x3b:
    case 0x3f:
    case 0x43:
    case 0x44:
      uStack0000000c = 0x40a00000;
      G_LoseSkillPoints();
      return;
    case 0xe:
    case 0x29:
    case 0x2d:
    case 0x32:
      uStack0000000c = 0x40400000;
      G_LoseSkillPoints();
      return;
    case 0x15:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x42:
      uStack0000000c = 0x40400000;
      G_LoseSkillPoints();
      return;
    case 0x16:
    case 0x19:
    case 0x38:
      uStack0000000c = 0x40a00000;
      G_LoseSkillPoints();
      return;
    case 0x3a:
    case 0x3e:
      uStack0000000c = 0x40a00000;
      G_LoseSkillPoints();
      return;
    }
  }
  return;
}

void G_DebugOpenSkillLog(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  char *__s;
  size_t tmp_s3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  uint8_t *tmp_pu7;
  uint32_t local_140;
  uint32_t local_13c;
  uint32_t local_138;
  uint32_t local_134;
  int local_130;
  int local_12c;
  uint8_t local_11c [16];
  uint8_t local_10c [256];
  uint32_t uStack_c;
  
  uStack_c = 0xdf9e7;
  if (1 < (int)GHIDRA_FIELD(g_debugSkills, 12, 4)) {
    trap_Cvar_Register(local_11c,"mapname",&g_unk_0026ea14,0x44);
    trap_RealTime(&local_140);
    tmp_pu7 = local_10c;
    tmp_u4 = local_138;
    tmp_u5 = local_13c;
    tmp_u6 = local_140;
    tmp_u1 = va("skills-%d-%02d-%02d-%02d%02d%02d-%s.log",local_12c + 0x76c,local_130 + 1,local_134,
               local_138,local_13c,local_140,tmp_pu7);
    tmp_i2 = trap_FS_FOpenFile(tmp_u1,&skillDebugLog,3);
    if (-1 < tmp_i2) {
      __s = (char *)va("%02d:%02d:%02d : Logfile opened.\n",local_138,local_13c,local_140,tmp_u4,
                       tmp_u5,tmp_u6,tmp_pu7);
      tmp_s3 = strlen(__s);
      trap_FS_Write(__s,tmp_s3,skillDebugLog);
      return;
    }
  }
  return;
}

void G_DebugCloseSkillLog(void)
{
  char *__s;
  size_t tmp_s1;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  
  if (skillDebugLog != -1) {
    trap_RealTime(&local_30);
    __s = (char *)va("%02d:%02d:%02d : Logfile closed.\n",local_28,local_2c,local_30);
    tmp_s1 = strlen(__s);
    trap_FS_Write(__s,tmp_s1,skillDebugLog);
    trap_FS_FCloseFile(skillDebugLog);
  }
  return;
}

void G_DebugAddSkillLevel(int param_1,int param_2)
{
  uint32_t tmp_u1;
  char *__s;
  size_t tmp_s2;
  int tmp_i3;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  
  if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
    tmp_i3 = *(int *)(param_1 + 400) + param_2 * 4;
    tmp_u1 = *(uint32_t *)(tmp_i3 + 0xc30);
    tmp_u1 = va("sdbg \"^%c(SK: %2i XP: %.0f) %s: You raised your skill level to %i.\"\n",
               param_2 + 0x31,tmp_u1,(double)*(float *)(tmp_i3 + 0xbf4),
               *(uint32_t *)(skillNames + param_2 * 4),tmp_u1);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
    trap_RealTime(&local_40);
    if ((1 < (int)GHIDRA_FIELD(g_debugSkills, 12, 4)) && (skillDebugLog != -1)) {
      tmp_i3 = param_2 * 4 + *(int *)(param_1 + 400);
      tmp_u1 = *(uint32_t *)(tmp_i3 + 0xc30);
      __s = (char *)va("%02d:%02d:%02d : ^%c(SK: %2i XP: %.0f) %s: %s raised in skill level to %i.\n"
                       ,local_38,local_3c,local_40,param_2 + 0x31,tmp_u1,
                       (double)*(float *)(tmp_i3 + 0xbf4),*(uint32_t *)(skillNames + param_2 * 4),
                       *(int *)(param_1 + 400) + 0x5f8,tmp_u1);
      tmp_s2 = strlen(__s);
      trap_FS_Write(__s,tmp_s2,skillDebugLog);
    }
  }
  return;
}

void G_DebugAddSkillPoints(int param_1,int param_2,float param_3,uint32_t param_4)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *__s;
  size_t tmp_s3;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  
  tmp_i1 = *(int *)(param_1 + 400) + param_2 * 4;
  tmp_u2 = va("sdbg \"^%c(SK: %2i XP: %.0f) %s: You gained %.0fXP, reason: %s.\"\n",param_2 + 0x31,
             *(uint32_t *)(tmp_i1 + 0xc30),(double)*(float *)(tmp_i1 + 0xbf4),
             *(uint32_t *)(skillNames + param_2 * 4),(double)param_3,param_4);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  trap_RealTime(&local_40);
  if ((1 < (int)GHIDRA_FIELD(g_debugSkills, 12, 4)) && (skillDebugLog != -1)) {
    tmp_i1 = param_2 * 4 + *(int *)(param_1 + 400);
    __s = (char *)va("%02d:%02d:%02d : ^%c(SK: %2i XP: %.0f) %s: %s gained %.0fXP, reason: %s.\n",
                     local_38,local_3c,local_40,param_2 + 0x31,*(uint32_t *)(tmp_i1 + 0xc30),
                     (double)*(float *)(tmp_i1 + 0xbf4),*(uint32_t *)(skillNames + param_2 * 4),
                     *(int *)(param_1 + 400) + 0x5f8,(double)param_3,param_4);
    tmp_s3 = strlen(__s);
    trap_FS_Write(__s,tmp_s3,skillDebugLog);
  }
  return;
}

void G_AddKillSkillPoints(int param_1,int param_2,uint32_t param_3,int param_4,int param_5)
{
  int *tmp_pi1;
  
  if (*(int *)(param_1 + 400) == 0) {
    return;
  }
  if (((g_TDMOptions[0xc] & 1) != 0) && (GHIDRA_FIELD(g_gametype, 12, 4) == 7)) {
    *(int *)(&g_unk_00abe91c + *(int *)(*(int *)(param_1 + 400) + 300) * 4) =
         *(int *)(&g_unk_00abe91c + *(int *)(*(int *)(param_1 + 400) + 300) * 4) + 1;
  }
  switch(param_3) {
  default:
    goto _L349;
  case 1:
  case 2:
  case 3:
    G_AddSkillPoints(param_1,5,0x40400000);
    break;
  case 5:
  case 0x3f:
    G_AddSkillPoints(param_1,4,0x40400000);
    goto joined_r0x000e05b0;
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0x24:
  case 0x25:
  case 0x2c:
  case 0x31:
  case 0x34:
  case 0x35:
  case 0x36:
  case 0x37:
    if (param_4 == 1) {
      G_AddSkillPoints(param_1,4,0x40400000);
    }
    else if (param_4 == 0) {
      G_AddSkillPoints(param_1,4,0x40a00000);
    }
    else {
      if (param_4 != 2) {
        if (param_4 == 3) {
          G_AddSkillPoints(param_1,4,0x40400000);
        }
        else {
          G_AddSkillPoints(param_1,4,0x40400000);
        }
        goto joined_r0x000e05b0;
      }
      G_AddSkillPoints(param_1,4,0x40400000);
    }
    break;
  case 0xe:
  case 0x2d:
  case 0x32:
    if (param_4 == 1) {
      G_AddSkillPoints(param_1,6,0x40400000);
      goto joined_r0x000e05b0;
    }
    if (param_4 == 0) {
      G_AddSkillPoints(param_1,6,0x40a00000);
    }
    else if (param_4 == 2) {
      G_AddSkillPoints(param_1,6,0x40400000);
    }
    else if (param_4 == 3) {
      G_AddSkillPoints(param_1,6,0x40400000);
    }
    else {
      G_AddSkillPoints(param_1,6,0x40400000);
    }
    break;
  case 0xf:
    if (param_5 != 0) {
      G_AddSkillPoints(param_1,5,0x40400000);
      goto joined_r0x000e05b0;
    }
    G_AddSkillPoints(param_1,5,0x40400000);
    break;
  case 0x10:
  case 0x12:
  case 0x38:
  case 0x41:
    G_AddSkillPoints(param_1,4,0x40400000);
    break;
  case 0x11:
    G_AddSkillPoints(param_1,5,0x40400000);
    if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
      G_DebugAddSkillPoints(param_1,5,0x40400000,"flamethrower kill");
    }
    if ((*(byte *)(param_2 + 0x128) & 8) != 0) {
      return;
    }
    nitrox_CheckGlobalAwards(param_1,8,1);
    return;
  case 0x15:
  case 0x28:
    G_AddSkillPoints(param_1,1,0x40800000);
    break;
  case 0x16:
    G_AddSkillPoints(param_1,3,0x40400000);
    break;
  case 0x19:
    G_AddSkillPoints(param_1,3,0x40800000);
    break;
  case 0x26:
  case 0x27:
    G_AddSkillPoints(param_1,1,0x40400000);
    break;
  case 0x29:
    G_AddSkillPoints(param_1,6,0x40a00000);
    if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
      G_DebugAddSkillPoints(param_1,6,0x40a00000,"satchel charge kill");
    }
    if ((param_2 != 0) && (*(int *)(param_2 + 400) != 0)) {
      tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0xba0);
      *tmp_pi1 = *tmp_pi1 + 1;
    }
    if ((*(byte *)(param_2 + 0x128) & 8) != 0) {
      return;
    }
    nitrox_CheckGlobalAwards(param_1,0xc,1);
    return;
  case 0x2b:
    G_AddSkillPoints(param_1,5,0x40400000);
    break;
  case 0x33:
    if (param_5 == 0) {
      G_AddSkillPoints(param_1,5,0x40400000);
    }
    else {
      G_AddSkillPoints(param_1,5,0x40400000);
    }
joined_r0x000e05b0:
    if (GHIDRA_FIELD(g_debugSkills, 12, 4) == 0) {
      return;
    }
    goto LAB_000e0040;
  case 0x3a:
    if ((*(byte *)(param_2 + 0x128) & 8) == 0) {
      nitrox_CheckGlobalAwards(param_1,6,1);
    }
    G_AddSkillPoints(param_1,0,0x40a00000);
    if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
      G_DebugAddSkillPoints(param_1,0,0x40a00000,"goomba kill");
    }
    BG_AdjustGoombas(*(uint32_t *)(param_1 + 400),1);
    return;
  case 0x3b:
  case 0x43:
  case 0x44:
    G_AddSkillPoints();
    return;
  case 0x3e:
    G_AddSkillPoints(param_1,0,0x40a00000);
    break;
  case 0x42:
    if ((*(byte *)(param_2 + 0x128) & 8) == 0) {
      nitrox_CheckGlobalAwards(param_1,5,1);
    }
    G_AddSkillPoints(param_1,1,0x40800000);
  }
  if (GHIDRA_FIELD(g_debugSkills, 12, 4) == 0) {
_L349:
    return;
  }
LAB_000e0040:
  G_DebugAddSkillPoints();
  return;
}

void G_AddKillSkillPointsForDestruction(int param_1,uint32_t param_2,int param_3)
{
  int *tmp_pi1;
  
  switch(param_2) {
  case 0xf:
  case 0x33:
    G_AddSkillPoints(param_1,5,*(uint32_t *)(param_3 + 8));
    if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
      G_DebugAddSkillPoints
                (param_1,5,*(uint32_t *)(param_3 + 8),"destroying a constructible/explosive");
    }
    break;
  case 0x10:
  case 0x12:
    G_AddSkillPoints(param_1,4,*(uint32_t *)(param_3 + 8));
    if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
      G_DebugAddSkillPoints
                (param_1,4,*(uint32_t *)(param_3 + 8),"destroying a constructible/explosive");
    }
    break;
  default:
    goto _L412;
  case 0x15:
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x42:
    G_AddSkillPoints(param_1,1,*(uint32_t *)(param_3 + 8));
    if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
      G_DebugAddSkillPoints
                (param_1,1,*(uint32_t *)(param_3 + 8),"destroying a constructible/explosive");
    }
    break;
  case 0x16:
  case 0x19:
    G_AddSkillPoints(param_1,3,*(uint32_t *)(param_3 + 8));
    if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
      G_DebugAddSkillPoints
                (param_1,3,*(uint32_t *)(param_3 + 8),"destroying a constructible/explosive");
    }
    break;
  case 0x29:
    G_AddSkillPoints(param_1,6,*(uint32_t *)(param_3 + 8));
    if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
      G_DebugAddSkillPoints
                (param_1,6,*(uint32_t *)(param_3 + 8),"destroying a constructible/explosive");
    }
    nitrox_CheckGlobalAwards(param_1,10,1);
    tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0xba0);
    *tmp_pi1 = *tmp_pi1 + 1;
    return;
  }
  nitrox_CheckGlobalAwards(param_1,10,1);
_L412:
  return;
}

void G_ReassignSkillLevel(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
    tmp_i3 = 0;
    tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
    do {
      while ((tmp_i1 = *(int *)(g_unk_00abe8a4 + 400 + tmp_i3 * 0x600), tmp_i1 != 0 &&
             (*(int *)(tmp_i1 + 0x5ac) == 2))) {
        tmp_i3 = tmp_i3 + 1;
        G_SetPlayerSkill(tmp_i1,param_1);
        G_UpgradeSkill();
        tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
        if ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= tmp_i3) {
          return;
        }
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 < tmp_i2);
  }
  return;
}

bool G_HasFlakJacket(int param_1)
{
  return *(int *)(*(int *)(param_1 + 400) + 0x158) != 0;
}

void G_Is_SV_Running(void)
{
  char local_40c [1028];
  
  trap_Cvar_VariableStringBuffer("sv_running",local_40c,0x400);
  strtol(local_40c,(char **)0x0,10);
  return;
}

bool G_FilterPacket(uint *param_1,char *param_2)
{
  uint *tmp_pu1;
  uint *tmp_pu2;
  char tmp_c3;
  uint *tmp_pu4;
  char tmp_c5;
  uint tmp_u6;
  int tmp_i7;
  char local_21;
  uint local_14;
  
  tmp_c5 = *param_2;
  if (tmp_c5 != '\0') {
    tmp_i7 = 0;
    while( true ) {
      *(uint8_t *)((int)&local_14 + tmp_i7) = 0;
      if ((byte)(tmp_c5 - 0x30U) < 10) {
        tmp_c3 = '\0';
        local_21 = tmp_c5;
        do {
          param_2 = param_2 + 1;
          tmp_c5 = *param_2;
          tmp_c3 = tmp_c3 * '\n' + -0x30 + local_21;
          local_21 = tmp_c5;
        } while ((byte)(tmp_c5 - 0x30U) < 10);
        *(char *)((int)&local_14 + tmp_i7) = tmp_c3;
      }
      if ((tmp_c5 == ':') || (tmp_c5 == '\0')) break;
      tmp_c5 = param_2[1];
      tmp_i7 = tmp_i7 + 1;
      param_2 = param_2 + 1;
      if ((tmp_c5 == '\0') || (tmp_i7 == 4)) break;
    }
  }
  if (0 < (int)param_1[0x800]) {
    if ((*param_1 & local_14) != param_1[1]) {
      tmp_u6 = 0;
      tmp_pu2 = param_1;
      do {
        tmp_pu4 = tmp_pu2 + 2;
        tmp_u6 = tmp_u6 + 1;
        if (tmp_u6 == param_1[0x800]) goto LAB_000e2379;
        tmp_pu1 = tmp_pu2 + 3;
        tmp_pu2 = tmp_pu4;
      } while ((*tmp_pu4 & local_14) != *tmp_pu1);
    }
    return GHIDRA_FIELD(g_filterBan, 12, 4) != 0;
  }
LAB_000e2379:
  return GHIDRA_FIELD(g_filterBan, 12, 4) == 0;
}

bool G_FilterMaxLivesIPPacket(char *param_1)
{
  uint *tmp_pu1;
  uint tmp_u2;
  char tmp_c3;
  uint *tmp_pu4;
  char tmp_c5;
  int tmp_i6;
  char local_21;
  uint local_14;
  
  tmp_c5 = *param_1;
  if (tmp_c5 != '\0') {
    tmp_i6 = 0;
    while( true ) {
      *(uint8_t *)((int)&local_14 + tmp_i6) = 0;
      if ((byte)(tmp_c5 - 0x30U) < 10) {
        tmp_c3 = '\0';
        local_21 = tmp_c5;
        do {
          param_1 = param_1 + 1;
          tmp_c5 = *param_1;
          tmp_c3 = tmp_c3 * '\n' + -0x30 + local_21;
          local_21 = tmp_c5;
        } while ((byte)(tmp_c5 - 0x30U) < 10);
        *(char *)((int)&local_14 + tmp_i6) = tmp_c3;
      }
      if ((tmp_c5 == ':') || (tmp_c5 == '\0')) break;
      tmp_c5 = param_1[1];
      tmp_i6 = tmp_i6 + 1;
      param_1 = param_1 + 1;
      if ((tmp_c5 == '\0') || (tmp_i6 == 4)) break;
    }
  }
  if (0 < g_unk_008233a0) {
    if ((ipMaxLivesFilters & local_14) != g_unk_008213a4) {
      tmp_i6 = 0;
      tmp_pu4 = &g_unk_008213a8;
      do {
        tmp_i6 = tmp_i6 + 1;
        if (tmp_i6 == g_unk_008233a0) goto LAB_000e2571;
        tmp_u2 = *tmp_pu4;
        tmp_pu1 = tmp_pu4 + 1;
        tmp_pu4 = tmp_pu4 + 2;
      } while ((tmp_u2 & local_14) != *tmp_pu1);
    }
    return GHIDRA_FIELD(g_filterBan, 12, 4) != 0;
  }
LAB_000e2571:
  return GHIDRA_FIELD(g_filterBan, 12, 4) == 0;
}

uint32_t G_FilterMaxLivesPacket(uint32_t param_1)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  
  if (0 < numMaxLivesFilters) {
    tmp_pu2 = &guidMaxLivesFilters;
    tmp_i3 = 0;
    do {
      tmp_i1 = Q_stricmp(tmp_pu2,param_1);
      if (tmp_i1 == 0) {
        return 1;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu2 = tmp_pu2 + 0x21;
    } while (tmp_i3 < numMaxLivesFilters);
  }
  return 0;
}

int G_GetPlayerByNum(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = G_Is_SV_Running();
  if (tmp_i1 != 0) {
    tmp_i1 = trap_Argc();
    if (tmp_i1 < 2) {
      G_Printf("No player specified.\n");
      tmp_i1 = 0;
    }
    else if ((param_1 < 0) || (g_unk_00abe900 <= param_1)) {
      Com_Printf("Bad client slot: %i\n",param_1);
      tmp_i1 = 0;
    }
    else {
      tmp_i1 = param_1 * 0x54dc + level;
      if (*(int *)(tmp_i1 + 0x5ac) == 0) {
        G_Printf("Client %i is not connected\n",param_1);
        tmp_i1 = 0;
      }
    }
    return tmp_i1;
  }
  return 0;
}

int G_GetPlayerByName(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint8_t local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0xe35d9;
  tmp_i1 = G_Is_SV_Running();
  if (tmp_i1 == 0) {
    return 0;
  }
  tmp_i1 = trap_Argc();
  if (tmp_i1 < 2) {
    G_Printf("No player specified.\n");
    return 0;
  }
  tmp_i1 = 0;
  if (0 < g_unk_00abe938) {
    do {
      tmp_i2 = (&g_unk_00abe944)[tmp_i1] * 0x54dc + level;
      tmp_i3 = Q_stricmp(tmp_i2 + 0x5f8,param_1);
      if (tmp_i3 == 0) {
        return tmp_i2;
      }
      Q_strncpyz(local_5c,tmp_i2 + 0x5f8,0x40);
      Q_CleanStr(local_5c);
      tmp_i3 = Q_stricmp(local_5c,param_1);
      if (tmp_i3 == 0) {
        return tmp_i2;
      }
      tmp_i1 = tmp_i1 + 1;
    } while (tmp_i1 < g_unk_00abe938);
  }
  G_Printf("Player %s is not on the server\n",param_1);
  return 0;
}

void G_ClearXP(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  
  nitrox_XPSave_ClearXP();
  if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
    tmp_pu3 = g_entities;
    tmp_i2 = 0;
    do {
      tmp_u1 = va("sessionstats%i",tmp_i2);
      trap_Cvar_Set(tmp_u1,&g_unk_0026ea14);
      tmp_u1 = va("wstats%i",tmp_i2);
      trap_Cvar_Set(tmp_u1,&g_unk_0026ea14);
      if ((*(int *)(tmp_pu3 + 0x194) != 0) && (*(int *)(tmp_pu3 + 400) != 0)) {
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xbf4) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xc50) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xbf8) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xc54) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xbfc) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xc58) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xc00) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xc5c) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xc04) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xc60) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xc08) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xc64) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xc0c) = 0;
        *(uint32_t *)(*(int *)(tmp_pu3 + 400) + 0xc68) = 0;
        G_deleteStats(tmp_i2);
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pu3 = tmp_pu3 + 0x600;
    } while (tmp_i2 < (int)GHIDRA_FIELD(g_maxclients, 12, 4));
  }
  return;
}

void G_UpdateSvCvars(void)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  uint8_t *local_428;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xe4179;
  local_41c[0] = 0;
  if (0 < g_unk_02ac4194) {
    tmp_i3 = 0;
    tmp_pu5 = &g_unk_02aabf94;
    do {
      tmp_u1 = va("%i %s %s %s",*(uint32_t *)(tmp_pu5 + 0x100),tmp_pu5,tmp_pu5 + 0x104,tmp_pu5 + 0x204)
      ;
      tmp_i4 = tmp_i3 + 1;
      tmp_u2 = va(&g_unk_0025874f,tmp_i3);
      Info_SetValueForKey(local_41c,tmp_u2,tmp_u1);
      tmp_i3 = tmp_i4;
      tmp_pu5 = tmp_pu5 + 0x304;
    } while (tmp_i4 < g_unk_02ac4194);
  }
  local_428 = local_41c;
  tmp_u1 = va("%i",g_unk_02ac4194);
  Info_SetValueForKey(local_428,0x25fe2b,tmp_u1);
  trap_SetConfigstring(0x26,local_428);
  return;
}

uint32_t G_CvarUpdateSafe(int param_1,int param_2)
{
  uint *tmp_pu1;
  uint32_t tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  uint tmp_u5;
  int tmp_i6;
  int *tmp_pi7;
  uint *tmp_pu8;
  uint *tmp_pu9;
  int local_4d4 [304];
  uint32_t uStack_14;
  
  tmp_u3 = 0;
  uStack_14 = 0xe63ab;
  do {
    tmp_u2 = *(uint32_t *)((int)&g_ptr_s_mod_version_002bb3a4 + tmp_u3);
    *(uint32_t *)((int)local_4d4 + tmp_u3) = *(uint32_t *)((int)&g_ptr_s_mod_url_002bb3a0 + tmp_u3);
    *(uint32_t *)((int)local_4d4 + tmp_u3 + 4) = tmp_u2;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0xb8);
  local_4d4[0x2e] = 0;
  tmp_u3 = 0;
  do {
    tmp_u5 = tmp_u3;
    *(uint32_t *)((int)local_4d4 + tmp_u5 + 0xbc) = 0;
    *(uint32_t *)((int)local_4d4 + tmp_u5 + 0xc0) = 0;
    tmp_u3 = tmp_u5 + 8;
  } while (tmp_u5 + 8 < 0x3f8);
  *(uint32_t *)((int)local_4d4 + tmp_u5 + 0xc4) = 0;
  if (((param_1 != 0) && (param_2 != 0)) && (local_4d4[0] != 0)) {
    tmp_pi7 = local_4d4;
    do {
      tmp_pi7 = tmp_pi7 + 1;
      tmp_i4 = Q_stricmp(local_4d4[0],param_1);
      if (tmp_i4 == 0) {
        tmp_pu1 = (uint *)(local_4d4 + 0x2e);
        (*syscall)(0x18,tmp_pu1,0x400,0xfffffac7);
        tmp_pu9 = tmp_pu1;
        do {
          tmp_pu8 = tmp_pu9;
          tmp_u5 = *tmp_pu8 + 0xfefefeff & ~*tmp_pu8;
          tmp_u3 = tmp_u5 & 0x80808080;
          tmp_pu9 = tmp_pu8 + 1;
        } while (tmp_u3 == 0);
        if ((tmp_u5 & 0x8080) == 0) {
          tmp_pu9 = (uint *)((int)tmp_pu8 + 6);
          tmp_u3 = tmp_u3 >> 0x10;
        }
        tmp_i4 = (int)tmp_pu9 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)tmp_pu1);
        Info_SetValueForKey(tmp_pu1,param_1,param_2);
        if (tmp_i4 < 0x3ff) {
          if ((tmp_i4 + 1 + g_unk_02ad55a0) - g_unk_02ad45a0 < 15999) {
            tmp_i6 = tmp_i4 - g_unk_02ad45a0;
            g_unk_02ad45a0 = tmp_i4 + 1;
            g_unk_02ad55a0 = g_unk_02ad55a0 + 1 + tmp_i6;
            return 1;
          }
          G_Printf("WARNING: skipping SERVERINFO cvar set for %s (MAX_GAMESTATE_CHARS protection)\n"
                   ,param_1);
          return 0;
        }
        G_Printf("WARNING: skipping SERVERINFO cvar set for %s (MAX_INFO_STRING protection)\n",
                 param_1);
        return 0;
      }
      local_4d4[0] = *tmp_pi7;
    } while (local_4d4[0] != 0);
  }
  return 1;
}

void trap_Cvar_Register(uint32_t param_1,uint32_t param_2,uint8_t *param_3,uint32_t param_4
                       )

{
  int tmp_i1;
  
  tmp_i1 = G_CvarUpdateSafe(param_2,param_3);
  if (tmp_i1 == 0) {
    param_3 = &g_unk_0026ea14;
  }
  (*syscall)(3,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void G_teamReset(int param_1,int param_2)
{
  uint tmp_u1;
  
  tmp_u1 = 0;
  if (GHIDRA_FIELD(match_latejoin, 12, 4) == 0) {
    tmp_u1 = (uint)(GHIDRA_FIELD(g_gamestate, 12, 4) == 0);
  }
  param_1 = param_1 * 0x10;
  *(uint *)(teamInfo + param_1 + 4) = tmp_u1;
  *(uint32_t *)(teamInfo + param_1 + 8) = 0;
  *(uint32_t *)(teamInfo + param_1 + 0xc) = GHIDRA_FIELD(match_timeoutcount, 12, 4);
  if (param_2 != 0) {
    *(uint32_t *)(teamInfo + param_1) = 0;
  }
  return;
}

void G_swapTeams(void)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  
  if ((GHIDRA_FIELD(match_latejoin, 12, 4) == 0) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
    GHIDRA_FIELD(teamInfo, 20, 4) = 1;
    GHIDRA_FIELD(teamInfo, 36, 4) = 1;
  }
  else {
    GHIDRA_FIELD(teamInfo, 36, 4) = 0;
    GHIDRA_FIELD(teamInfo, 20, 4) = 0;
  }
  GHIDRA_FIELD(teamInfo, 24, 4) = 0;
  GHIDRA_FIELD(teamInfo, 16, 4) = 0;
  GHIDRA_FIELD(teamInfo, 32, 4) = 0;
  GHIDRA_FIELD(teamInfo, 44, 4) = GHIDRA_FIELD(match_timeoutcount, 12, 4);
  GHIDRA_FIELD(teamInfo, 40, 4) = 0;
  GHIDRA_FIELD(teamInfo, 28, 4) = GHIDRA_FIELD(teamInfo, 44, 4);
  if (0 < g_unk_00abe93c) {
    tmp_i3 = 0;
    tmp_pi2 = &g_unk_00abe944;
    do {
      tmp_i1 = *tmp_pi2 * 0x54dc + level;
      tmp_i3 = tmp_i3 + 1;
      *(uint *)(tmp_i1 + 3000) = (*(int *)(tmp_i1 + 3000) == 1) + 1;
      G_UpdateCharacter(tmp_i1);
      ClientUserinfoChanged(*tmp_pi2);
      ClientBegin(*tmp_pi2);
      tmp_pi2 = tmp_pi2 + 1;
    } while (tmp_i3 < g_unk_00abe93c);
  }
  nitmod_cp(0,0x24);
  return;
}

void G_shuffleTeams(void)
{
  int *tmp_pi1;
  size_t __nmemb;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint local_124;
  int local_11c [66];
  uint32_t uStack_14;
  
  uStack_14 = 0xed019;
  if ((GHIDRA_FIELD(match_latejoin, 12, 4) == 0) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
    GHIDRA_FIELD(teamInfo, 36, 4) = 1;
    GHIDRA_FIELD(teamInfo, 20, 4) = 1;
  }
  else {
    GHIDRA_FIELD(teamInfo, 36, 4) = 0;
    GHIDRA_FIELD(teamInfo, 20, 4) = 0;
  }
  GHIDRA_FIELD(teamInfo, 24, 4) = 0;
  GHIDRA_FIELD(teamInfo, 16, 4) = 0;
  GHIDRA_FIELD(teamInfo, 28, 4) = GHIDRA_FIELD(match_timeoutcount, 12, 4);
  GHIDRA_FIELD(teamInfo, 40, 4) = 0;
  GHIDRA_FIELD(teamInfo, 32, 4) = 0;
  GHIDRA_FIELD(teamInfo, 44, 4) = GHIDRA_FIELD(teamInfo, 28, 4);
  if (g_unk_00abe938 < 1) {
    qsort(local_11c,0,4,nitrox_SortByKDRatio);
  }
  else {
    tmp_pi1 = &g_unk_00abe944;
    __nmemb = 0;
    do {
      if (*(int *)(level + 3000 + *tmp_pi1 * 0x54dc) != 3) {
        local_11c[__nmemb] = *tmp_pi1;
        __nmemb = __nmemb + 1;
      }
      tmp_pi1 = tmp_pi1 + 1;
    } while (tmp_pi1 != &g_unk_00abe944 + g_unk_00abe938);
    qsort(local_11c,__nmemb,4,nitrox_SortByKDRatio);
    if (__nmemb != 0) {
      local_124 = 0;
      tmp_pi1 = local_11c;
      do {
        tmp_i2 = *tmp_pi1;
        tmp_i3 = tmp_i2 * 0x54dc + level;
        tmp_i4 = (local_124 & 1) + 1;
        if (*(int *)(tmp_i3 + 3000) != tmp_i4) {
          G_LeaveTank(g_entities + tmp_i2 * 0x600,0,0);
          G_RemoveClientFromFireteams(*tmp_pi1,1,0);
          if (GHIDRA_FIELD(g_landminetimeout, 12, 4) != 0) {
            nitrox_FadeLandmines(g_entities + *tmp_pi1 * 0x600);
          }
          if (GHIDRA_FIELD(n_tripmineTimeout, 12, 4) != 0) {
            nitrox_RemoveTripmines(g_entities + *tmp_pi1 * 0x600);
          }
          nitrox_FadeSatchels(g_entities + *tmp_pi1 * 0x600);
          tmp_i2 = *tmp_pi1;
        }
        G_DropItems(g_entities + tmp_i2 * 0x600);
        *(int *)(tmp_i3 + 3000) = tmp_i4;
        G_UpdateCharacter(tmp_i3);
        ClientUserinfoChanged(*tmp_pi1);
        ClientBegin(*tmp_pi1);
        local_124 = local_124 + 1;
        tmp_pi1 = tmp_pi1 + 1;
      } while (local_124 != __nmemb);
    }
  }
  nitmod_cp(0,0x25);
  return;
}

bool G_checkReady(void)
{
  bool tmp_b1;
  uint32_t tmp_u2;
  int tmp_i3;
  int *tmp_pi4;
  int tmp_i5;
  int local_24;
  int local_20;
  
  local_24 = GHIDRA_FIELD(match_minplayers, 12, 4);
  if (GHIDRA_FIELD(g_doWarmup, 12, 4) == 0) {
    return true;
  }
  if ((g_unk_00abe93c < (int)GHIDRA_FIELD(match_minplayers, 12, 4)) || (g_unk_00abee58 < 1)) {
    tmp_i5 = 0;
    tmp_b1 = true;
    local_20 = GHIDRA_FIELD(match_minplayers, 12, 4);
  }
  else {
    if (g_unk_00abe93c < 1) {
      tmp_i5 = 0;
      goto LAB_000ed34b;
    }
    tmp_pi4 = &g_unk_00abe944;
    local_20 = 0;
    tmp_i5 = 0;
    do {
      while( true ) {
        tmp_i3 = *tmp_pi4 * 0x54dc + level;
        if (*(int *)(tmp_i3 + 0x5ac) == 2) break;
LAB_000ed400:
        tmp_pi4 = tmp_pi4 + 1;
        if (tmp_pi4 == &g_unk_00abe944 + g_unk_00abe93c) goto LAB_000ed450;
      }
      if ((*(int *)(tmp_i3 + 0x998) != 0) || ((g_entities[*tmp_pi4 * 0x600 + 0x128] & 8) != 0)) {
        tmp_i5 = tmp_i5 + 1;
        goto LAB_000ed400;
      }
      tmp_pi4 = tmp_pi4 + 1;
      local_20 = local_20 + 1;
    } while (tmp_pi4 != &g_unk_00abe944 + g_unk_00abe93c);
LAB_000ed450:
    tmp_b1 = tmp_i5 < 1;
  }
  if ((0 < local_20) || (!tmp_b1)) {
    local_24 = local_20;
  }
LAB_000ed34b:
  if (local_24 != GHIDRA_FIELD(g_minGameClients, 12, 4)) {
    tmp_u2 = va(&g_unk_00245ee9,local_24);
    trap_Cvar_Set("g_minGameClients",tmp_u2);
  }
  if (g_unk_02a99a7c == 0) {
    return 0 < local_24 + tmp_i5 &&
           (int)GHIDRA_FIELD(match_readypercent, 12, 4) <= (tmp_i5 * 100) / (local_24 + tmp_i5);
  }
  return true;
}

uint32_t G_readyMatchState(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  if (((GHIDRA_FIELD(g_doWarmup, 12, 4) == 0) &&
      (((GHIDRA_FIELD(g_gametype, 12, 4) != 5 || (GHIDRA_FIELD(g_lms_lockTeams, 12, 4) == 0)) &&
       (g_unk_00abe8ac <= g_unk_00abe908 + 10000)))) ||
     ((GHIDRA_FIELD(g_gamestate, 12, 4) != 2 || (tmp_i1 = G_checkReady(), tmp_i1 == 0)))) {
    tmp_i1 = G_checkReady();
    if (tmp_i1 != 0) {
      return 0;
    }
    if (GHIDRA_FIELD(g_gamestate, 12, 4) == 1) {
      trap_SendServerCommand(0xffffffff,"cp \"^1COUNTDOWN STOPPED!^7  Back to warmup...\n\"");
    }
    g_unk_02a983a8 = g_unk_00abe908;
    tmp_u2 = va("map_restart 0 %i\n",2);
    trap_SendConsoleCommand(2,tmp_u2);
    tmp_u2 = 0;
  }
  else {
    tmp_u2 = 1;
    g_unk_02a99a7c = 0;
    if ((GHIDRA_FIELD(g_gametype, 12, 4) == 5) && (GHIDRA_FIELD(g_lms_lockTeams, 12, 4) != 0)) {
      GHIDRA_FIELD(teamInfo, 20, 4) = 1;
      GHIDRA_FIELD(teamInfo, 36, 4) = 1;
    }
  }
  return tmp_u2;
}

void G_verifyMatchState(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint tmp_u3;
  
  if (((g_unk_02a983a8 + 1000 < g_unk_00abe908) && (param_1 - 1U < 2)) &&
     (((uint)GHIDRA_FIELD(g_gamestate, 12, 4) < 2 || (GHIDRA_FIELD(g_gamestate, 12, 4) == 3)))) {
    tmp_i1 = TeamCount(0xffffffff,param_1);
    if (tmp_i1 == 0) {
      if (0 < (int)GHIDRA_FIELD(g_doWarmup, 12, 4)) {
        g_unk_02a983a8 = g_unk_00abe908;
        if (GHIDRA_FIELD(g_gametype, 12, 4) == 3) {
          trap_Cvar_Set("g_currentRound",&g_unk_0024bfa6);
          trap_Cvar_Set("g_nextTimeLimit",&g_unk_0024bfa6);
        }
        tmp_u2 = va("map_restart 0 %i\n",2);
        trap_SendConsoleCommand(2,tmp_u2);
      }
      tmp_u3 = 0;
      if (GHIDRA_FIELD(match_latejoin, 12, 4) == 0) {
        tmp_u3 = (uint)(GHIDRA_FIELD(g_gamestate, 12, 4) == 0);
      }
      param_1 = param_1 * 0x10;
      *(uint *)(teamInfo + param_1 + 4) = tmp_u3;
      *(uint32_t *)(teamInfo + param_1 + 8) = 0;
      *(uint32_t *)(teamInfo + param_1) = 0;
      *(uint32_t *)(teamInfo + param_1 + 0xc) = GHIDRA_FIELD(match_timeoutcount, 12, 4);
    }
  }
  G_checkReady();
  return;
}

uint32_t G_teamJoinCheck(uint param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  int tmp_i5;
  
  tmp_i1 = TeamCount(0xffffffff,param_1);
  if (tmp_i1 == 0) {
    tmp_i2 = param_1 * 0x10;
    *(uint32_t *)(teamInfo + tmp_i2 + 8) = 0;
    *(uint32_t *)(teamInfo + tmp_i2) = 0;
    *(uint32_t *)(teamInfo + tmp_i2 + 4) = 0;
    *(uint32_t *)(teamInfo + tmp_i2 + 0xc) = GHIDRA_FIELD(match_timeoutcount, 12, 4);
  }
  if (1 < param_1 - 1) {
    return 1;
  }
  tmp_i2 = *(int *)(param_2 + 400);
  if (param_1 == *(uint *)(tmp_i2 + 3000)) {
    return 1;
  }
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
    tmp_i2 = G_IsClassDisabled(param_2,*(uint32_t *)(tmp_i2 + 0xbc8),1);
    if (tmp_i2 != 0) {
      tmp_i2 = 0;
      do {
        tmp_i5 = G_IsClassDisabled(param_2,tmp_i2,1);
        if (tmp_i5 == 0) {
          tmp_i5 = *(int *)(param_2 + 400);
          *(int *)(tmp_i5 + 0xbc8) = tmp_i2;
          *(int *)(tmp_i5 + 0xbd8) = tmp_i2;
          goto LAB_000ed8f0;
        }
        tmp_i2 = tmp_i2 + 1;
      } while (tmp_i2 != 5);
      tmp_u4 = *(uint32_t *)(aTeams + param_1 * 4);
      tmp_pc3 = "The %s has no classes left!";
      goto LAB_000ed818;
    }
LAB_000ed8f0:
    if (((int)GHIDRA_FIELD(team_maxplayers, 12, 4) <= tmp_i1) && (0 < (int)GHIDRA_FIELD(team_maxplayers, 12, 4)))
    goto LAB_000ed807;
    if (GHIDRA_FIELD(g_gamestate, 12, 4) != 0) {
      return 1;
    }
    if (GHIDRA_FIELD(g_lms_lockTeams, 12, 4) == 0) {
      return 1;
    }
    tmp_i2 = *(int *)(param_2 + 400);
  }
  else {
    if (((int)GHIDRA_FIELD(team_maxplayers, 12, 4) <= tmp_i1) && (0 < (int)GHIDRA_FIELD(team_maxplayers, 12, 4))) {
LAB_000ed807:
      tmp_u4 = *(uint32_t *)(aTeams + param_1 * 4);
      tmp_pc3 = "The %s team is full!";
      goto LAB_000ed818;
    }
    if (*(int *)(teamInfo + param_1 * 0x10 + 4) == 0) {
      return 1;
    }
  }
  if ((*(uint *)(tmp_i2 + 0x98c) & param_1) != 0) {
    return 1;
  }
  tmp_u4 = *(uint32_t *)(aTeams + param_1 * 4);
  tmp_pc3 = "The %s team is LOCKED!";
LAB_000ed818:
  tmp_u4 = va(tmp_pc3,tmp_u4);
  G_printFull(tmp_u4,param_2);
  return 0;
}

void G_updateSpecLock(uint param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  *(int *)(teamInfo + param_1 * 0x10) = param_2;
  if (0 < g_unk_00abe938) {
    tmp_i4 = 0;
    tmp_i2 = g_unk_00abe938;
    do {
      while( true ) {
        tmp_i3 = (&g_unk_00abe944)[tmp_i4] * 0x600;
        tmp_i1 = *(int *)(g_entities + tmp_i3 + 400);
        if ((*(int *)(tmp_i1 + 0xc80) == 0) && (*(int *)(tmp_i1 + 0xf30) == 0)) break;
LAB_000ed9f0:
        tmp_i4 = tmp_i4 + 1;
        if (tmp_i2 <= tmp_i4) {
          return;
        }
      }
      *(uint *)(tmp_i1 + 0xc88) = *(uint *)(tmp_i1 + 0xc88) & ~param_1;
      if ((param_2 != 0) && (*(int *)(*(int *)(g_entities + tmp_i3 + 400) + 3000) == 3)) {
        if (*(int *)(*(int *)(g_entities + tmp_i3 + 400) + 0xbc0) == 2) {
          StopFollowing(g_entities + tmp_i3);
          *(uint *)(*(int *)(g_entities + tmp_i3 + 400) + 0xc8c) =
               *(uint *)(*(int *)(g_entities + tmp_i3 + 400) + 0xc8c) & ~param_1;
        }
        SetTeam(g_entities + tmp_i3,&g_unk_0024e6ea,1,0xffffffff,0xffffffff,0);
        tmp_i2 = g_unk_00abe938;
        goto LAB_000ed9f0;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_i2 = g_unk_00abe938;
    } while (tmp_i4 < g_unk_00abe938);
  }
  return;
}

void G_swapTeamLocks(void)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  
  tmp_u2 = GHIDRA_FIELD(teamInfo, 36, 4);
  tmp_u1 = GHIDRA_FIELD(teamInfo, 32, 4);
  GHIDRA_FIELD(teamInfo, 32, 4) = GHIDRA_FIELD(teamInfo, 16, 4);
  GHIDRA_FIELD(teamInfo, 16, 4) = tmp_u1;
  GHIDRA_FIELD(teamInfo, 36, 4) = GHIDRA_FIELD(teamInfo, 20, 4);
  GHIDRA_FIELD(teamInfo, 20, 4) = tmp_u2;
  return;
}

void G_removeSpecInvite(uint param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  int *tmp_pi3;
  
  if (0 < g_unk_00abe938) {
    tmp_pi3 = &g_unk_00abe944;
    tmp_pi2 = &g_unk_00abe944 + g_unk_00abe938;
    do {
      if (((*(int *)(g_entities + *tmp_pi3 * 0x600 + 0x194) != 0) &&
          (tmp_i1 = *(int *)(g_entities + *tmp_pi3 * 0x600 + 400), *(int *)(tmp_i1 + 0xc80) == 0)) &&
         (*(int *)(tmp_i1 + 0xf30) == 0)) {
        *(uint *)(tmp_i1 + 0xc88) = *(uint *)(tmp_i1 + 0xc88) & ~param_1;
      }
      tmp_pi3 = tmp_pi3 + 1;
    } while (tmp_pi3 != tmp_pi2);
  }
  return;
}

bool G_blockoutTeam(int param_1,uint param_2)
{
  uint tmp_u1;
  int tmp_i2;
  
  if ((GHIDRA_FIELD(g_gametype, 12, 4) == 5) && (GHIDRA_FIELD(g_lms_followTeamOnly, 12, 4) != 0)) {
    if (param_2 == (*(uint *)(*(int *)(param_1 + 400) + 0xc88) & param_2)) {
      return false;
    }
    tmp_u1 = *(uint *)(*(int *)(param_1 + 400) + 3000);
    if ((tmp_u1 != 3) && (tmp_u1 != param_2)) {
      return true;
    }
  }
  if (0x9c4 < g_unk_00abe908 - g_unk_00abe918) {
    tmp_i2 = TeamCount(0xffffffff,1);
    if (tmp_i2 == 0) {
      GHIDRA_FIELD(teamInfo, 16, 4) = 0;
    }
    tmp_i2 = TeamCount(0xffffffff,2);
    if (tmp_i2 == 0) {
      GHIDRA_FIELD(teamInfo, 32, 4) = 0;
    }
  }
  if ((*(int *)(teamInfo + param_2 * 0x10) != 0) && (*(int *)(*(int *)(param_1 + 400) + 3000) == 3))
  {
    return param_2 != (*(uint *)(*(int *)(param_1 + 400) + 0xc88) & param_2);
  }
  return false;
}

bool G_allowFollow(int param_1,uint param_2)
{
  uint tmp_u1;
  int tmp_i2;
  
  if ((GHIDRA_FIELD(g_gametype, 12, 4) == 5) && (GHIDRA_FIELD(g_lms_followTeamOnly, 12, 4) != 0)) {
    if ((*(uint *)(*(int *)(param_1 + 400) + 0xc88) & param_2) == param_2) {
      return true;
    }
    tmp_u1 = *(uint *)(*(int *)(param_1 + 400) + 3000);
    if ((tmp_u1 != 3) && (tmp_u1 != param_2)) {
      return false;
    }
  }
  if (0x9c4 < g_unk_00abe908 - g_unk_00abe918) {
    tmp_i2 = TeamCount(0xffffffff,1);
    if (tmp_i2 == 0) {
      GHIDRA_FIELD(teamInfo, 16, 4) = 0;
    }
    tmp_i2 = TeamCount(0xffffffff,2);
    if (tmp_i2 == 0) {
      GHIDRA_FIELD(teamInfo, 32, 4) = 0;
    }
  }
  if ((*(int *)(teamInfo + param_2 * 0x10) != 0) && (*(int *)(*(int *)(param_1 + 400) + 3000) == 3))
  {
    return param_2 == (*(uint *)(*(int *)(param_1 + 400) + 0xc88) & param_2);
  }
  return true;
}

uint32_t G_desiredFollow(int param_1,uint param_2)
{
  int tmp_i1;
  
  if ((GHIDRA_FIELD(g_gametype, 12, 4) == 5) && (GHIDRA_FIELD(g_lms_followTeamOnly, 12, 4) != 0)) {
    tmp_i1 = *(int *)(param_1 + 400);
    if (param_2 == (*(uint *)(tmp_i1 + 0xc88) & param_2)) goto LAB_000ede1d;
    if ((*(uint *)(tmp_i1 + 3000) != 3) && (*(uint *)(tmp_i1 + 3000) != param_2)) {
      return 0;
    }
  }
  if (0x9c4 < g_unk_00abe908 - g_unk_00abe918) {
    tmp_i1 = TeamCount(0xffffffff,1);
    if (tmp_i1 == 0) {
      GHIDRA_FIELD(teamInfo, 16, 4) = 0;
    }
    tmp_i1 = TeamCount(0xffffffff,2);
    if (tmp_i1 == 0) {
      GHIDRA_FIELD(teamInfo, 32, 4) = 0;
    }
  }
  tmp_i1 = *(int *)(param_1 + 400);
  if (((*(int *)(teamInfo + param_2 * 0x10) != 0) && (*(int *)(tmp_i1 + 3000) == 3)) &&
     (param_2 != (*(uint *)(tmp_i1 + 0xc88) & param_2))) {
    return 0;
  }
LAB_000ede1d:
  if ((param_2 != *(uint *)(tmp_i1 + 0xc8c)) && (*(uint *)(tmp_i1 + 0xc8c) != 0)) {
    return 0;
  }
  return 1;
}

void G_PushMapEntityToBuffer(uint32_t param_1,uint32_t param_2,float *param_3)
{
  int tmp_i1;
  char tmp_c2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint8_t local_2c [28];
  uint32_t uStack_10;
  
  uStack_10 = 0xedf08;
  if (g_unk_02a99a64 == 0) {
    tmp_i1 = (int)ROUND(param_3[1]);
    tmp_i5 = tmp_i1 + 0x7f;
    if (-1 < tmp_i1) {
      tmp_i5 = tmp_i1;
    }
    tmp_i1 = (int)ROUND(*param_3);
    tmp_i6 = tmp_i1 + 0x7f;
    if (-1 < tmp_i1) {
      tmp_i6 = tmp_i1;
    }
    Com_sprintf(local_2c,0x20,"%i %i",tmp_i6 >> 7,tmp_i5 >> 7);
  }
  else {
    tmp_i1 = (int)ROUND(param_3[2]);
    tmp_i5 = tmp_i1 + 0x7f;
    if (-1 < tmp_i1) {
      tmp_i5 = tmp_i1;
    }
    tmp_i1 = (int)ROUND(param_3[1]);
    tmp_i6 = tmp_i1 + 0x7f;
    if (-1 < tmp_i1) {
      tmp_i6 = tmp_i1;
    }
    tmp_i1 = (int)ROUND(*param_3);
    tmp_i3 = tmp_i1 + 0x7f;
    if (-1 < tmp_i1) {
      tmp_i3 = tmp_i1;
    }
    Com_sprintf(local_2c,0x20,"%i %i %i",tmp_i3 >> 7,tmp_i6 >> 7,tmp_i5 >> 7);
  }
  tmp_c2 = *(char *)(param_3 + 5);
  if (((byte)(tmp_c2 - 3U) < 7) && ((1 << (tmp_c2 - 3U & 0x1f) & 0x77U) != 0)) {
    tmp_u4 = va(" %i %s %i",(int)tmp_c2,local_2c,param_3[4]);
  }
  else {
    tmp_u4 = va(" %i %s %i %i",(int)tmp_c2,local_2c,param_3[3],param_3[4]);
  }
  Q_strcat(param_1,param_2,tmp_u4);
  return;
}

void G_InitMapEntityData(void *param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  
  memset(param_1,0,0xc034);
  *(int *)((int)param_1 + 0xc02c) = (int)param_1 + 0xc004;
  tmp_pi2 = (int *)((int)param_1 + 0x28);
  *(int *)((int)param_1 + 0xc030) = (int)param_1 + 0xc004;
  *(void **)((int)param_1 + 0xc000) = param_1;
  tmp_i1 = (int)param_1 + 0x30;
  do {
    *tmp_pi2 = tmp_i1;
    tmp_i1 = tmp_i1 + 0x30;
    tmp_pi2 = tmp_pi2 + 0xc;
  } while (tmp_i1 != (int)param_1 + 0xc000);
  return;
}

uint32_t G_FreeMapEntityData(int param_1,int param_2)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  tmp_i3 = *(int *)(param_2 + 0x2c);
  tmp_u1 = *(uint32_t *)(param_2 + 0x28);
  tmp_u2 = tmp_u1;
  if (tmp_i3 == 0) {
    G_Error("G_FreeMapEntityData: not active");
    tmp_i3 = *(int *)(param_2 + 0x2c);
    tmp_u2 = *(uint32_t *)(param_2 + 0x28);
  }
  *(uint32_t *)(tmp_i3 + 0x28) = tmp_u2;
  *(uint32_t *)(*(int *)(param_2 + 0x28) + 0x2c) = *(uint32_t *)(param_2 + 0x2c);
  *(uint32_t *)(param_2 + 0x28) = *(uint32_t *)(param_1 + 0xc000);
  *(int *)(param_1 + 0xc000) = param_2;
  return tmp_u1;
}

void G_AllocMapEntityData(int param_1)
{
  uint16_t *tmp_pu1;
  uint16_t *tmp_pu2;
  uint32_t *tmp_pu3;
  uint tmp_u4;
  uint tmp_u5;
  bool tmp_b6;
  
  tmp_pu1 = *(uint16_t **)(param_1 + 0xc000);
  if (tmp_pu1 == (uint16_t *)0x0) {
    G_Error("G_AllocMapEntityData: out of entities");
    tmp_pu1 = *(uint16_t **)(param_1 + 0xc000);
  }
  tmp_b6 = ((uint)tmp_pu1 & 1) != 0;
  tmp_u5 = 0x30;
  *(uint32_t *)(param_1 + 0xc000) = *(uint32_t *)(tmp_pu1 + 0x14);
  tmp_pu2 = tmp_pu1;
  if (tmp_b6) {
    tmp_u5 = 0x2f;
    *(uint8_t *)tmp_pu1 = 0;
    tmp_pu2 = (uint16_t *)((int)tmp_pu1 + 1);
  }
  if (((uint)tmp_pu2 & 2) != 0) {
    *tmp_pu2 = 0;
    tmp_u5 = tmp_u5 - 2;
    tmp_pu2 = tmp_pu2 + 1;
  }
  tmp_u4 = 0;
  do {
    *(uint32_t *)((int)tmp_pu2 + tmp_u4) = 0;
    *(uint32_t *)((int)tmp_pu2 + tmp_u4 + 4) = 0;
    tmp_u4 = tmp_u4 + 8;
  } while (tmp_u4 < (tmp_u5 & 0xfffffff8));
  tmp_pu3 = (uint32_t *)((int)tmp_pu2 + tmp_u4);
  if ((tmp_u5 & 4) != 0) {
    *tmp_pu3 = 0;
    tmp_pu3 = tmp_pu3 + 1;
  }
  if ((tmp_u5 & 2) != 0) {
    *(uint16_t *)tmp_pu3 = 0;
    tmp_pu3 = (uint32_t *)((int)tmp_pu3 + 2);
  }
  if (tmp_b6) {
    *(uint8_t *)tmp_pu3 = 0;
  }
  *(uint32_t *)(tmp_pu1 + 0xe) = 0xffffffff;
  *(uint32_t *)(tmp_pu1 + 0x14) = *(uint32_t *)(param_1 + 0xc02c);
  *(int *)(tmp_pu1 + 0x16) = param_1 + 0xc004;
  *(uint16_t **)(*(int *)(param_1 + 0xc02c) + 0x2c) = tmp_pu1;
  *(uint16_t **)(param_1 + 0xc02c) = tmp_pu1;
  return;
}

int G_FindMapEntityData(int param_1,int param_2)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0xc02c);
  if (tmp_i1 != 0) {
    do {
      if (tmp_i1 == param_1 + 0xc004) {
        return 0;
      }
      if ((*(int *)(tmp_i1 + 0x1c) < 0) && (*(int *)(tmp_i1 + 0x24) == param_2)) {
        return tmp_i1;
      }
      tmp_i1 = *(int *)(tmp_i1 + 0x28);
    } while (tmp_i1 != 0);
  }
  return 0;
}

int G_FindMapEntityDataSingleClient(int param_1,int param_2,int param_3,int param_4)
{
  int tmp_i1;
  
  if (param_2 == 0) {
    tmp_i1 = *(int *)(param_1 + 0xc02c);
  }
  else {
    tmp_i1 = *(int *)(param_2 + 0x28);
  }
  if ((tmp_i1 != 0) && (param_1 = param_1 + 0xc004, tmp_i1 != param_1)) {
    if (param_4 == -1) {
      do {
        if ((-1 < *(int *)(tmp_i1 + 0x1c)) && (*(int *)(tmp_i1 + 0x24) == param_3)) {
          return tmp_i1;
        }
        tmp_i1 = *(int *)(tmp_i1 + 0x28);
      } while ((tmp_i1 != 0) && (tmp_i1 != param_1));
    }
    else {
      do {
        if (((param_4 == *(int *)(tmp_i1 + 0x1c)) || (*(int *)(tmp_i1 + 0x1c) < 0)) &&
           (*(int *)(tmp_i1 + 0x24) == param_3)) {
          return tmp_i1;
        }
        tmp_i1 = *(int *)(tmp_i1 + 0x28);
      } while ((tmp_i1 != 0) && (tmp_i1 != param_1));
    }
  }
  return 0;
}

void G_SetupFrustum(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  float tmp_f4;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  AnglesToAxis(*(int *)(param_1 + 400) + 0xb0,&local_30);
  local_30 = local_30 * 0.70710677;
  local_2c = local_2c * 0.70710677;
  local_28 = local_28 * 0.70710677;
  frustum = local_24 * 0.70710677 + local_30;
  g_unk_00826424 = local_20 * 0.70710677 + local_2c;
  g_unk_00826428 = local_1c * 0.70710677 + local_28;
  g_unk_00826430 = local_24 * -0.70710677 + local_30;
  g_unk_00826434 = local_20 * -0.70710677 + local_2c;
  g_unk_00826438 = local_1c * -0.70710677 + local_28;
  g_unk_00826440 = local_18 * 0.70710677 + local_30;
  g_unk_00826444 = local_14 * 0.70710677 + local_2c;
  g_unk_00826448 = local_10 * 0.70710677 + local_28;
  g_unk_00826450 = local_18 * -0.70710677 + local_30;
  g_unk_00826454 = local_14 * -0.70710677 + local_2c;
  tmp_i3 = *(int *)(param_1 + 400);
  g_unk_00826458 = local_10 * -0.70710677 + local_28;
  tmp_f1 = *(float *)(tmp_i3 + 0x14);
  tmp_f2 = *(float *)(tmp_i3 + 0x18);
  tmp_f4 = (float)*(int *)(tmp_i3 + 0xbc) + *(float *)(tmp_i3 + 0x1c);
  g_unk_0082642c = g_unk_00826428 * tmp_f4 + g_unk_00826424 * tmp_f2 + frustum * tmp_f1;
  g_unk_0082643c = g_unk_00826438 * tmp_f4 + g_unk_00826434 * tmp_f2 + g_unk_00826430 * tmp_f1;
  g_unk_0082644c = g_unk_00826448 * tmp_f4 + g_unk_00826444 * tmp_f2 + g_unk_00826440 * tmp_f1;
  g_unk_0082645c = tmp_f1 * g_unk_00826450 + g_unk_00826454 * tmp_f2 + g_unk_00826458 * tmp_f4;
  return;
}

void G_SetupFrustum_ForBinoculars(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  if ((*(byte *)(param_1 + 0x128) & 8) == 0) {
    tmp_f1 = -0.9961947;
    tmp_f2 = 0.9961947;
    tmp_f3 = 0.08715574;
  }
  else {
    tmp_f1 = -0.8660254;
    tmp_f2 = 0.8660254;
    tmp_f3 = 0.5;
  }
  AnglesToAxis(*(int *)(param_1 + 400) + 0xb0,&local_30);
  local_30 = local_30 * tmp_f3;
  local_2c = local_2c * tmp_f3;
  tmp_f3 = tmp_f3 * local_28;
  frustum = local_24 * tmp_f2 + local_30;
  g_unk_00826424 = local_20 * tmp_f2 + local_2c;
  g_unk_00826428 = local_1c * tmp_f2 + tmp_f3;
  g_unk_00826430 = local_24 * tmp_f1 + local_30;
  g_unk_00826434 = local_20 * tmp_f1 + local_2c;
  g_unk_00826438 = local_1c * tmp_f1 + tmp_f3;
  g_unk_00826440 = local_18 * tmp_f2 + local_30;
  g_unk_00826444 = local_14 * tmp_f2 + local_2c;
  g_unk_00826448 = tmp_f2 * local_10 + tmp_f3;
  g_unk_00826450 = local_18 * tmp_f1 + local_30;
  tmp_i4 = *(int *)(param_1 + 400);
  g_unk_00826454 = local_14 * tmp_f1 + local_2c;
  g_unk_00826458 = tmp_f1 * local_10 + tmp_f3;
  tmp_f1 = *(float *)(tmp_i4 + 0x14);
  tmp_f2 = *(float *)(tmp_i4 + 0x18);
  tmp_f3 = (float)*(int *)(tmp_i4 + 0xbc) + *(float *)(tmp_i4 + 0x1c);
  g_unk_0082642c = g_unk_00826428 * tmp_f3 + g_unk_00826424 * tmp_f2 + frustum * tmp_f1;
  g_unk_0082643c = g_unk_00826438 * tmp_f3 + g_unk_00826434 * tmp_f2 + g_unk_00826430 * tmp_f1;
  g_unk_0082644c = g_unk_00826448 * tmp_f3 + g_unk_00826444 * tmp_f2 + g_unk_00826440 * tmp_f1;
  g_unk_0082645c = tmp_f3 * g_unk_00826458 + tmp_f1 * g_unk_00826450 + g_unk_00826454 * tmp_f2;
  return;
}

bool G_VisibleFromBinoculars(uint32_t *param_1,int *param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint32_t local_60;
  uint32_t local_5c;
  float local_58;
  uint8_t local_54 [8];
  float local_4c;
  int local_20;
  
  tmp_i5 = param_1[100];
  local_60 = *(uint32_t *)(tmp_i5 + 0x14);
  local_5c = *(uint32_t *)(tmp_i5 + 0x18);
  local_58 = (float)*(int *)(tmp_i5 + 0xbc) + *(float *)(tmp_i5 + 0x1c);
  tmp_f1 = *param_3;
  tmp_f2 = param_3[1];
  tmp_f3 = param_3[2];
  tmp_f4 = (g_unk_00826428 * tmp_f3 + g_unk_00826424 * tmp_f2 + frustum * tmp_f1) - g_unk_0082642c;
  if (((((0.0 <= tmp_f4) && (0.0 < tmp_f4)) &&
       (tmp_f4 = (g_unk_00826438 * tmp_f3 + g_unk_00826434 * tmp_f2 + g_unk_00826430 * tmp_f1) - g_unk_0082643c,
       0.0 <= tmp_f4)) &&
      ((0.0 < tmp_f4 &&
       (tmp_f4 = (g_unk_00826448 * tmp_f3 + g_unk_00826444 * tmp_f2 + g_unk_00826440 * tmp_f1) - g_unk_0082644c,
       0.0 <= tmp_f4)))) &&
     ((0.0 < tmp_f4 &&
      ((tmp_f1 = (tmp_f3 * g_unk_00826458 + tmp_f2 * g_unk_00826454 + tmp_f1 * g_unk_00826450) - g_unk_0082645c,
       0.0 <= tmp_f1 && (0.0 < tmp_f1)))))) {
    tmp_i5 = trap_InPVS(&local_60,param_3);
    if (tmp_i5 != 0) {
      trap_Trace(local_54,&local_60,0,0,param_3,*param_1,0x6000001);
      if (local_4c == 1.0) {
        return true;
      }
      if (param_2 != (int *)0x0) {
        return local_20 == *param_2;
      }
    }
  }
  return false;
}

void G_ResetTeamMapData(void)
{
  int tmp_i1;
  
  memset(mapEntityData,0,0xc034);
  GHIDRA_FIELD(mapEntityData, 49196, 4) = 0x2d8ca64;
  tmp_i1 = 0x2d80a90;
  GHIDRA_FIELD(mapEntityData, 49200, 4) = 0x2d8ca64;
  GHIDRA_FIELD(mapEntityData, 49152, 4) = mapEntityData;
  do {
    *(int *)(tmp_i1 + -8) = tmp_i1;
    tmp_i1 = tmp_i1 + 0x30;
  } while (tmp_i1 != 0x2d8ca60);
  memset(mapEntityData + 0xc034,0,0xc034);
  GHIDRA_FIELD(mapEntityData, 98400, 4) = 0x2d98a98;
  tmp_i1 = 0x2d8cac4;
  GHIDRA_FIELD(mapEntityData, 98404, 4) = 0x2d98a98;
  GHIDRA_FIELD(mapEntityData, 98356, 4) = 0x2d8ca94;
  do {
    *(int *)(tmp_i1 + -8) = tmp_i1;
    tmp_i1 = tmp_i1 + 0x30;
  } while (tmp_i1 != 0x2d98a94);
  return;
}

void G_UpdateTeamMapData_Construct(int param_1)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  uint tmp_u4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  bool tmp_b7;
  uint local_24;
  
  tmp_i3 = *(int *)(param_1 + 0x108);
  tmp_i6 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98400, 4);
  if (tmp_i3 == 2) {
    for (; (tmp_pu2 != (uint32_t *)0x0 && (tmp_pu2 != (uint32_t *)(mapEntityData + 0x18038)));
        tmp_pu2 = (uint32_t *)tmp_pu2[10]) {
      if (((int)tmp_pu2[7] < 0) && (tmp_i3 = tmp_pu2[9], tmp_i6 - tmp_pu2[9] == 0)) goto LAB_000eec19;
    }
    tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
    if (GHIDRA_FIELD(mapEntityData, 98356, 4) == 0) {
      G_Error("G_AllocMapEntityData: out of entities");
      tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
    }
    GHIDRA_FIELD(mapEntityData, 98356, 4) = tmp_pu2[10];
    tmp_b7 = ((uint)tmp_pu2 & 1) != 0;
    local_24 = 0x30;
    tmp_pu5 = tmp_pu2;
    if (tmp_b7) {
      *(uint8_t *)tmp_pu2 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu2 + 1);
      local_24 = 0x2f;
    }
    if (((uint)tmp_pu5 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
      local_24 = local_24 - 2;
    }
    tmp_u4 = 0;
    do {
      *(uint32_t *)((int)tmp_pu5 + tmp_u4) = 0;
      *(uint32_t *)((int)tmp_pu5 + tmp_u4 + 4) = 0;
      tmp_u4 = tmp_u4 + 8;
    } while (tmp_u4 < (local_24 & 0xfffffff8));
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + tmp_u4);
    if ((local_24 & 4) != 0) {
      *tmp_pu5 = 0;
      tmp_pu5 = tmp_pu5 + 1;
    }
    if ((local_24 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
    }
    if (tmp_b7) {
      *(uint8_t *)tmp_pu5 = 0;
    }
    tmp_pu2[7] = 0xffffffff;
    tmp_pu2[10] = GHIDRA_FIELD(mapEntityData, 98400, 4);
    tmp_pu2[0xb] = 0x2d98a98;
    *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 98400, 4) + 0x2c) = tmp_pu2;
    GHIDRA_FIELD(mapEntityData, 98400, 4) = tmp_pu2;
    tmp_pu2[9] = tmp_i6;
    tmp_i3 = tmp_i6;
LAB_000eec19:
    *tmp_pu2 = *(uint32_t *)(param_1 + 0x18);
    tmp_pu2[1] = *(uint32_t *)(param_1 + 0x1c);
    tmp_pu2[2] = *(uint32_t *)(param_1 + 0x20);
  }
  else {
    tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49196, 4);
    if (tmp_i3 == 3) {
      for (; (tmp_pu2 != (uint32_t *)0x0 && (tmp_pu2 != (uint32_t *)(mapEntityData + 0xc004)));
          tmp_pu2 = (uint32_t *)tmp_pu2[10]) {
        if (((int)tmp_pu2[7] < 0) && (tmp_i3 = tmp_pu2[9], tmp_i6 - tmp_pu2[9] == 0)) goto LAB_000eeb49;
      }
      tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
      if (GHIDRA_FIELD(mapEntityData, 49152, 4) == 0) {
        G_Error("G_AllocMapEntityData: out of entities");
        tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
      }
      GHIDRA_FIELD(mapEntityData, 49152, 4) = tmp_pu2[10];
      tmp_b7 = ((uint)tmp_pu2 & 1) != 0;
      local_24 = 0x30;
      tmp_pu5 = tmp_pu2;
      if (tmp_b7) {
        *(uint8_t *)tmp_pu2 = 0;
        tmp_pu5 = (uint32_t *)((int)tmp_pu2 + 1);
        local_24 = 0x2f;
      }
      if (((uint)tmp_pu5 & 2) != 0) {
        *(uint16_t *)tmp_pu5 = 0;
        tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
        local_24 = local_24 - 2;
      }
      tmp_u4 = 0;
      do {
        *(uint32_t *)((int)tmp_pu5 + tmp_u4) = 0;
        *(uint32_t *)((int)tmp_pu5 + tmp_u4 + 4) = 0;
        tmp_u4 = tmp_u4 + 8;
      } while (tmp_u4 < (local_24 & 0xfffffff8));
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + tmp_u4);
      if ((local_24 & 4) != 0) {
        *tmp_pu5 = 0;
        tmp_pu5 = tmp_pu5 + 1;
      }
      if ((local_24 & 2) != 0) {
        *(uint16_t *)tmp_pu5 = 0;
        tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
      }
      if (tmp_b7) {
        *(uint8_t *)tmp_pu5 = 0;
      }
      tmp_pu2[7] = 0xffffffff;
      tmp_pu2[10] = GHIDRA_FIELD(mapEntityData, 49196, 4);
      tmp_pu2[0xb] = 0x2d8ca64;
      *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 49196, 4) + 0x2c) = tmp_pu2;
      GHIDRA_FIELD(mapEntityData, 49196, 4) = tmp_pu2;
      tmp_pu2[9] = tmp_i6;
      tmp_i3 = tmp_i6;
LAB_000eeb49:
      *tmp_pu2 = *(uint32_t *)(param_1 + 0x18);
      tmp_pu2[1] = *(uint32_t *)(param_1 + 0x1c);
      tmp_u1 = *(uint32_t *)(param_1 + 0x20);
      tmp_pu2[4] = tmp_i3;
      tmp_pu2[2] = tmp_u1;
      *(uint8_t *)(tmp_pu2 + 5) = 3;
      tmp_u1 = g_unk_00abe908;
      tmp_pu2[3] = 0;
      tmp_pu2[6] = tmp_u1;
      for (tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98400, 4);
          (tmp_pu2 != (uint32_t *)0x0 && (tmp_pu2 != (uint32_t *)(mapEntityData + 0x18038)));
          tmp_pu2 = (uint32_t *)tmp_pu2[10]) {
        if (((int)tmp_pu2[7] < 0) && (tmp_i3 = tmp_pu2[9], tmp_i6 - tmp_pu2[9] == 0)) goto LAB_000eebb1;
      }
      tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
      if (GHIDRA_FIELD(mapEntityData, 98356, 4) == 0) {
        G_Error("G_AllocMapEntityData: out of entities");
        tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
      }
      GHIDRA_FIELD(mapEntityData, 98356, 4) = tmp_pu2[10];
      tmp_b7 = ((uint)tmp_pu2 & 1) != 0;
      local_24 = 0x30;
      tmp_pu5 = tmp_pu2;
      if (tmp_b7) {
        *(uint8_t *)tmp_pu2 = 0;
        tmp_pu5 = (uint32_t *)((int)tmp_pu2 + 1);
        local_24 = 0x2f;
      }
      if (((uint)tmp_pu5 & 2) != 0) {
        *(uint16_t *)tmp_pu5 = 0;
        tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
        local_24 = local_24 - 2;
      }
      tmp_u4 = 0;
      do {
        *(uint32_t *)((int)tmp_pu5 + tmp_u4) = 0;
        *(uint32_t *)((int)tmp_pu5 + tmp_u4 + 4) = 0;
        tmp_u4 = tmp_u4 + 8;
      } while (tmp_u4 < (local_24 & 0xfffffff8));
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + tmp_u4);
      if ((local_24 & 4) != 0) {
        *tmp_pu5 = 0;
        tmp_pu5 = tmp_pu5 + 1;
      }
      if ((local_24 & 2) != 0) {
        *(uint16_t *)tmp_pu5 = 0;
        tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
      }
      if (tmp_b7) {
        *(uint8_t *)tmp_pu5 = 0;
      }
      tmp_pu2[7] = 0xffffffff;
      tmp_pu2[10] = GHIDRA_FIELD(mapEntityData, 98400, 4);
      tmp_pu2[0xb] = 0x2d98a98;
      *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 98400, 4) + 0x2c) = tmp_pu2;
      GHIDRA_FIELD(mapEntityData, 98400, 4) = tmp_pu2;
      tmp_pu2[9] = tmp_i6;
      tmp_i3 = tmp_i6;
LAB_000eebb1:
      *tmp_pu2 = *(uint32_t *)(param_1 + 0x18);
      tmp_pu2[1] = *(uint32_t *)(param_1 + 0x1c);
      tmp_pu2[2] = *(uint32_t *)(param_1 + 0x20);
      tmp_pu2[4] = tmp_i3;
      *(uint8_t *)(tmp_pu2 + 5) = 3;
      tmp_u1 = g_unk_00abe908;
      tmp_pu2[3] = 0;
      tmp_pu2[6] = tmp_u1;
      return;
    }
    if (tmp_i3 != 1) {
      return;
    }
    for (; (tmp_pu2 != (uint32_t *)0x0 && (tmp_pu2 != (uint32_t *)(mapEntityData + 0xc004)));
        tmp_pu2 = (uint32_t *)tmp_pu2[10]) {
      if (((int)tmp_pu2[7] < 0) && (tmp_i3 = tmp_pu2[9], tmp_i6 - tmp_pu2[9] == 0)) goto LAB_000eead1;
    }
    tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
    if (GHIDRA_FIELD(mapEntityData, 49152, 4) == 0) {
      G_Error("G_AllocMapEntityData: out of entities");
      tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
    }
    GHIDRA_FIELD(mapEntityData, 49152, 4) = tmp_pu2[10];
    tmp_b7 = ((uint)tmp_pu2 & 1) != 0;
    local_24 = 0x30;
    tmp_pu5 = tmp_pu2;
    if (tmp_b7) {
      *(uint8_t *)tmp_pu2 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu2 + 1);
      local_24 = 0x2f;
    }
    if (((uint)tmp_pu5 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
      local_24 = local_24 - 2;
    }
    tmp_u4 = 0;
    do {
      *(uint32_t *)((int)tmp_pu5 + tmp_u4) = 0;
      *(uint32_t *)((int)tmp_pu5 + tmp_u4 + 4) = 0;
      tmp_u4 = tmp_u4 + 8;
    } while (tmp_u4 < (local_24 & 0xfffffff8));
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + tmp_u4);
    if ((local_24 & 4) != 0) {
      *tmp_pu5 = 0;
      tmp_pu5 = tmp_pu5 + 1;
    }
    if ((local_24 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
    }
    if (tmp_b7) {
      *(uint8_t *)tmp_pu5 = 0;
    }
    tmp_pu2[7] = 0xffffffff;
    tmp_pu2[10] = GHIDRA_FIELD(mapEntityData, 49196, 4);
    tmp_pu2[0xb] = 0x2d8ca64;
    *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 49196, 4) + 0x2c) = tmp_pu2;
    GHIDRA_FIELD(mapEntityData, 49196, 4) = tmp_pu2;
    tmp_pu2[9] = tmp_i6;
    tmp_i3 = tmp_i6;
LAB_000eead1:
    *tmp_pu2 = *(uint32_t *)(param_1 + 0x18);
    tmp_pu2[1] = *(uint32_t *)(param_1 + 0x1c);
    tmp_pu2[2] = *(uint32_t *)(param_1 + 0x20);
  }
  tmp_pu2[4] = tmp_i3;
  *(uint8_t *)(tmp_pu2 + 5) = 3;
  tmp_u1 = g_unk_00abe908;
  tmp_pu2[3] = 0;
  tmp_pu2[6] = tmp_u1;
  return;
}

void G_UpdateTeamMapData_Tank(int param_1)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint tmp_u3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  bool tmp_b6;
  uint32_t *local_30;
  uint local_2c;
  
  tmp_i5 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  for (tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49196, 4);
      (tmp_pu2 != (uint32_t *)0x0 && (tmp_pu2 != (uint32_t *)(mapEntityData + 0xc004)));
      tmp_pu2 = (uint32_t *)tmp_pu2[10]) {
    if (((int)tmp_pu2[7] < 0) && (tmp_i5 - tmp_pu2[9] == 0)) goto LAB_000ef077;
  }
  tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
  if (GHIDRA_FIELD(mapEntityData, 49152, 4) == 0) {
    G_Error("G_AllocMapEntityData: out of entities");
    tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
  }
  GHIDRA_FIELD(mapEntityData, 49152, 4) = tmp_pu2[10];
  tmp_b6 = ((uint)tmp_pu2 & 1) != 0;
  local_30 = (uint32_t *)0x30;
  tmp_pu4 = tmp_pu2;
  if (tmp_b6) {
    *(uint8_t *)tmp_pu2 = 0;
    tmp_pu4 = (uint32_t *)((int)tmp_pu2 + 1);
    local_30 = (uint32_t *)0x2f;
  }
  if (((uint)tmp_pu4 & 2) != 0) {
    *(uint16_t *)tmp_pu4 = 0;
    tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
    local_30 = (uint32_t *)((int)local_30 - 2);
  }
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)tmp_pu4 + tmp_u3) = 0;
    *(uint32_t *)((int)tmp_pu4 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < ((uint)local_30 & 0xfffffff8));
  tmp_pu4 = (uint32_t *)((int)tmp_pu4 + tmp_u3);
  if (((uint)local_30 & 4) != 0) {
    *tmp_pu4 = 0;
    tmp_pu4 = tmp_pu4 + 1;
  }
  if (((uint)local_30 & 2) != 0) {
    *(uint16_t *)tmp_pu4 = 0;
    tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
  }
  if (tmp_b6) {
    *(uint8_t *)tmp_pu4 = 0;
  }
  tmp_pu2[7] = 0xffffffff;
  tmp_pu2[10] = GHIDRA_FIELD(mapEntityData, 49196, 4);
  tmp_pu2[0xb] = 0x2d8ca64;
  *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 49196, 4) + 0x2c) = tmp_pu2;
  GHIDRA_FIELD(mapEntityData, 49196, 4) = tmp_pu2;
  tmp_pu2[9] = tmp_i5;
LAB_000ef077:
  *tmp_pu2 = *(uint32_t *)(param_1 + 0x18);
  tmp_pu2[1] = *(uint32_t *)(param_1 + 0x1c);
  tmp_pu2[2] = *(uint32_t *)(param_1 + 0x20);
  tmp_pu2[4] = *(uint32_t *)(param_1 + 0xa8);
  tmp_pu2[6] = g_unk_00abe908;
  tmp_i1 = *(int *)(param_1 + 4);
  tmp_pu2[3] = 0;
  *(char *)(tmp_pu2 + 5) = (tmp_i1 == 0x25) + '\a';
  for (tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98400, 4);
      (tmp_pu2 != (uint32_t *)0x0 && (tmp_pu2 != (uint32_t *)(mapEntityData + 0x18038)));
      tmp_pu2 = (uint32_t *)tmp_pu2[10]) {
    if (((int)tmp_pu2[7] < 0) && (tmp_i5 - tmp_pu2[9] == 0)) goto LAB_000ef0de;
  }
  tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
  if (GHIDRA_FIELD(mapEntityData, 98356, 4) == 0) {
    G_Error("G_AllocMapEntityData: out of entities");
    tmp_pu2 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
  }
  GHIDRA_FIELD(mapEntityData, 98356, 4) = tmp_pu2[10];
  tmp_b6 = ((uint)tmp_pu2 & 1) != 0;
  local_2c = 0x30;
  local_30 = tmp_pu2;
  if (tmp_b6) {
    local_30 = (uint32_t *)((int)tmp_pu2 + 1);
    *(uint8_t *)tmp_pu2 = 0;
    local_2c = 0x2f;
  }
  if (((uint)local_30 & 2) != 0) {
    *(uint16_t *)local_30 = 0;
    local_30 = (uint32_t *)((int)local_30 + 2);
    local_2c = local_2c - 2;
  }
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)local_30 + tmp_u3) = 0;
    *(uint32_t *)((int)local_30 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < (local_2c & 0xfffffff8));
  local_30 = (uint32_t *)((int)local_30 + tmp_u3);
  if ((local_2c & 4) != 0) {
    *local_30 = 0;
    local_30 = local_30 + 1;
  }
  if ((local_2c & 2) != 0) {
    *(uint16_t *)local_30 = 0;
    local_30 = (uint32_t *)((int)local_30 + 2);
  }
  if (tmp_b6) {
    *(uint8_t *)local_30 = 0;
  }
  tmp_pu2[7] = 0xffffffff;
  tmp_pu2[10] = GHIDRA_FIELD(mapEntityData, 98400, 4);
  tmp_pu2[0xb] = 0x2d98a98;
  *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 98400, 4) + 0x2c) = tmp_pu2;
  GHIDRA_FIELD(mapEntityData, 98400, 4) = tmp_pu2;
  tmp_pu2[9] = tmp_i5;
LAB_000ef0de:
  *tmp_pu2 = *(uint32_t *)(param_1 + 0x18);
  tmp_pu2[1] = *(uint32_t *)(param_1 + 0x1c);
  tmp_pu2[2] = *(uint32_t *)(param_1 + 0x20);
  tmp_pu2[4] = *(uint32_t *)(param_1 + 0xa8);
  tmp_pu2[6] = g_unk_00abe908;
  tmp_i5 = *(int *)(param_1 + 4);
  tmp_pu2[3] = 0;
  *(char *)(tmp_pu2 + 5) = (tmp_i5 == 0x25) + '\a';
  return;
}

void G_UpdateTeamMapData_Destruct(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  uint tmp_u6;
  uint32_t *tmp_pu7;
  int tmp_i8;
  bool tmp_b9;
  uint local_28;
  uint local_24;
  
  tmp_i4 = *(int *)(param_1 + 0x108);
  tmp_i8 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  tmp_pu7 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98400, 4);
  if (tmp_i4 == 1) {
    for (; (tmp_pu7 != (uint32_t *)0x0 && (tmp_pu7 != (uint32_t *)(mapEntityData + 0x18038)));
        tmp_pu7 = (uint32_t *)tmp_pu7[10]) {
      if (((int)tmp_pu7[7] < 0) && (tmp_i4 = tmp_pu7[9], tmp_i8 - tmp_pu7[9] == 0)) goto LAB_000ef509;
    }
    tmp_pu7 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
    if (GHIDRA_FIELD(mapEntityData, 98356, 4) == 0) {
      G_Error("G_AllocMapEntityData: out of entities");
      tmp_pu7 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
    }
    GHIDRA_FIELD(mapEntityData, 98356, 4) = tmp_pu7[10];
    tmp_b9 = ((uint)tmp_pu7 & 1) != 0;
    local_28 = 0x30;
    tmp_pu5 = tmp_pu7;
    if (tmp_b9) {
      *(uint8_t *)tmp_pu7 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu7 + 1);
      local_28 = 0x2f;
    }
    if (((uint)tmp_pu5 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
      local_28 = local_28 - 2;
    }
    tmp_u6 = 0;
    do {
      *(uint32_t *)((int)tmp_pu5 + tmp_u6) = 0;
      *(uint32_t *)((int)tmp_pu5 + tmp_u6 + 4) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < (local_28 & 0xfffffff8));
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + tmp_u6);
    if ((local_28 & 4) != 0) {
      *tmp_pu5 = 0;
      tmp_pu5 = tmp_pu5 + 1;
    }
    if ((local_28 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
    }
    if (tmp_b9) {
      *(uint8_t *)tmp_pu5 = 0;
    }
    tmp_pu7[7] = 0xffffffff;
    tmp_pu7[10] = GHIDRA_FIELD(mapEntityData, 98400, 4);
    tmp_pu7[0xb] = 0x2d98a98;
    *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 98400, 4) + 0x2c) = tmp_pu7;
    GHIDRA_FIELD(mapEntityData, 98400, 4) = tmp_pu7;
    tmp_pu7[9] = tmp_i8;
    tmp_i4 = tmp_i8;
LAB_000ef509:
    *tmp_pu7 = *(uint32_t *)(param_1 + 0x18);
    tmp_pu7[1] = *(uint32_t *)(param_1 + 0x1c);
    tmp_u1 = *(uint32_t *)(param_1 + 0x20);
    tmp_pu7[4] = tmp_i4;
    tmp_pu7[2] = tmp_u1;
    tmp_u1 = g_unk_00abe908;
    *(uint8_t *)(tmp_pu7 + 5) = 4;
    tmp_pu7[3] = 0;
    tmp_pu7[6] = tmp_u1;
    tmp_i4 = *(int *)(param_1 + 0x108);
  }
  else {
    tmp_i3 = *(int *)(param_1 + 0x218);
    tmp_pu7 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49196, 4);
    if ((*(int *)(tmp_i3 + 0x264) == 0) ||
       ((tmp_i2 = *(int *)(*(int *)(tmp_i3 + 0x264) + 4), tmp_i2 != 0xe && (tmp_i2 != 0x20)))) {
      if (tmp_i4 != 2) {
        return;
      }
      goto joined_r0x000ef458;
    }
    tmp_pu5 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98400, 4);
    if ((*(byte *)(tmp_i3 + 0x1a8) & 0x50) == 0) {
      if (tmp_i4 == 2) goto joined_r0x000ef458;
      goto LAB_000ef56a;
    }
    for (; (tmp_pu5 != (uint32_t *)0x0 && (tmp_pu5 != (uint32_t *)(mapEntityData + 0x18038)));
        tmp_pu5 = (uint32_t *)tmp_pu5[10]) {
      if (((int)tmp_pu5[7] < 0) && (tmp_i4 = tmp_pu5[9], tmp_i8 - tmp_pu5[9] == 0)) goto LAB_000ef411;
    }
    tmp_pu5 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
    if (GHIDRA_FIELD(mapEntityData, 98356, 4) == 0) {
      G_Error("G_AllocMapEntityData: out of entities");
      tmp_pu5 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
    }
    GHIDRA_FIELD(mapEntityData, 98356, 4) = tmp_pu5[10];
    tmp_b9 = ((uint)tmp_pu5 & 1) != 0;
    local_28 = 0x30;
    tmp_pu7 = tmp_pu5;
    if (tmp_b9) {
      *(uint8_t *)tmp_pu5 = 0;
      tmp_pu7 = (uint32_t *)((int)tmp_pu5 + 1);
      local_28 = 0x2f;
    }
    if (((uint)tmp_pu7 & 2) != 0) {
      *(uint16_t *)tmp_pu7 = 0;
      tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
      local_28 = local_28 - 2;
    }
    tmp_u6 = 0;
    do {
      *(uint32_t *)((int)tmp_pu7 + tmp_u6) = 0;
      *(uint32_t *)((int)tmp_pu7 + tmp_u6 + 4) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < (local_28 & 0xfffffff8));
    tmp_pu7 = (uint32_t *)((int)tmp_pu7 + tmp_u6);
    if ((local_28 & 4) != 0) {
      *tmp_pu7 = 0;
      tmp_pu7 = tmp_pu7 + 1;
    }
    if ((local_28 & 2) != 0) {
      *(uint16_t *)tmp_pu7 = 0;
      tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
    }
    if (tmp_b9) {
      *(uint8_t *)tmp_pu7 = 0;
    }
    tmp_pu5[7] = 0xffffffff;
    tmp_pu5[10] = GHIDRA_FIELD(mapEntityData, 98400, 4);
    tmp_pu5[0xb] = 0x2d98a98;
    *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 98400, 4) + 0x2c) = tmp_pu5;
    GHIDRA_FIELD(mapEntityData, 98400, 4) = tmp_pu5;
    tmp_pu5[9] = tmp_i8;
    tmp_i4 = tmp_i8;
LAB_000ef411:
    *tmp_pu5 = *(uint32_t *)(param_1 + 0x18);
    tmp_pu5[1] = *(uint32_t *)(param_1 + 0x1c);
    tmp_u1 = *(uint32_t *)(param_1 + 0x20);
    tmp_pu5[4] = tmp_i4;
    tmp_pu5[2] = tmp_u1;
    tmp_u1 = g_unk_00abe908;
    *(uint8_t *)(tmp_pu5 + 5) = 5;
    tmp_pu5[3] = 0;
    tmp_pu5[6] = tmp_u1;
    tmp_i4 = *(int *)(param_1 + 0x108);
  }
  tmp_pu7 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49196, 4);
  if (tmp_i4 != 2) {
    tmp_i3 = *(int *)(param_1 + 0x218);
    if (*(int *)(tmp_i3 + 0x264) == 0) {
      return;
    }
    tmp_i4 = *(int *)(*(int *)(tmp_i3 + 0x264) + 4);
    if ((tmp_i4 != 0xe) && (tmp_i4 != 0x20)) {
      return;
    }
LAB_000ef56a:
    tmp_pu7 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49196, 4);
    if ((*(byte *)(tmp_i3 + 0x1a8) & 0x50) == 0) {
      return;
    }
    for (; (tmp_pu7 != (uint32_t *)0x0 && (tmp_pu7 != (uint32_t *)(mapEntityData + 0xc004)));
        tmp_pu7 = (uint32_t *)tmp_pu7[10]) {
      if (((int)tmp_pu7[7] < 0) && (tmp_i4 = tmp_pu7[9], tmp_i8 - tmp_pu7[9] == 0)) goto LAB_000ef5b9;
    }
    tmp_pu7 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
    if (GHIDRA_FIELD(mapEntityData, 49152, 4) == 0) {
      G_Error("G_AllocMapEntityData: out of entities");
      tmp_pu7 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
    }
    GHIDRA_FIELD(mapEntityData, 49152, 4) = tmp_pu7[10];
    tmp_b9 = ((uint)tmp_pu7 & 1) != 0;
    local_28 = 0x30;
    tmp_pu5 = tmp_pu7;
    if (tmp_b9) {
      *(uint8_t *)tmp_pu7 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu7 + 1);
      local_28 = 0x2f;
    }
    if (((uint)tmp_pu5 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
      local_28 = local_28 - 2;
    }
    tmp_u6 = 0;
    do {
      *(uint32_t *)((int)tmp_pu5 + tmp_u6) = 0;
      *(uint32_t *)((int)tmp_pu5 + tmp_u6 + 4) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < (local_28 & 0xfffffff8));
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + tmp_u6);
    if ((local_28 & 4) != 0) {
      *tmp_pu5 = 0;
      tmp_pu5 = tmp_pu5 + 1;
    }
    if ((local_28 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
    }
    if (tmp_b9) {
      *(uint8_t *)tmp_pu5 = 0;
    }
    tmp_pu7[7] = 0xffffffff;
    tmp_pu7[10] = GHIDRA_FIELD(mapEntityData, 49196, 4);
    tmp_pu7[0xb] = 0x2d8ca64;
    *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 49196, 4) + 0x2c) = tmp_pu7;
    GHIDRA_FIELD(mapEntityData, 49196, 4) = tmp_pu7;
    tmp_pu7[9] = tmp_i8;
    tmp_i4 = tmp_i8;
LAB_000ef5b9:
    *tmp_pu7 = *(uint32_t *)(param_1 + 0x18);
    tmp_pu7[1] = *(uint32_t *)(param_1 + 0x1c);
    tmp_u1 = *(uint32_t *)(param_1 + 0x20);
    tmp_pu7[4] = tmp_i4;
    tmp_pu7[2] = tmp_u1;
    tmp_u1 = g_unk_00abe908;
    *(uint8_t *)(tmp_pu7 + 5) = 5;
    tmp_pu7[3] = 0;
    tmp_pu7[6] = tmp_u1;
    return;
  }
joined_r0x000ef458:
  for (; (tmp_pu7 != (uint32_t *)0x0 && (tmp_pu7 != (uint32_t *)(mapEntityData + 0xc004)));
      tmp_pu7 = (uint32_t *)tmp_pu7[10]) {
    if (((int)tmp_pu7[7] < 0) && (tmp_i4 = tmp_pu7[9], tmp_i8 == tmp_pu7[9])) goto LAB_000ef491;
  }
  tmp_pu7 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
  if (GHIDRA_FIELD(mapEntityData, 49152, 4) == 0) {
    G_Error("G_AllocMapEntityData: out of entities");
    tmp_pu7 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
  }
  GHIDRA_FIELD(mapEntityData, 49152, 4) = tmp_pu7[10];
  tmp_b9 = ((uint)tmp_pu7 & 1) != 0;
  local_24 = 0x30;
  tmp_pu5 = tmp_pu7;
  if (tmp_b9) {
    *(uint8_t *)tmp_pu7 = 0;
    tmp_pu5 = (uint32_t *)((int)tmp_pu7 + 1);
    local_24 = 0x2f;
  }
  if (((uint)tmp_pu5 & 2) != 0) {
    *(uint16_t *)tmp_pu5 = 0;
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
    local_24 = local_24 - 2;
  }
  tmp_u6 = 0;
  do {
    *(uint32_t *)((int)tmp_pu5 + tmp_u6) = 0;
    *(uint32_t *)((int)tmp_pu5 + tmp_u6 + 4) = 0;
    tmp_u6 = tmp_u6 + 8;
  } while (tmp_u6 < (local_24 & 0xfffffff8));
  tmp_pu5 = (uint32_t *)((int)tmp_pu5 + tmp_u6);
  if ((local_24 & 4) != 0) {
    *tmp_pu5 = 0;
    tmp_pu5 = tmp_pu5 + 1;
  }
  if ((local_24 & 2) != 0) {
    *(uint16_t *)tmp_pu5 = 0;
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
  }
  if (tmp_b9) {
    *(uint8_t *)tmp_pu5 = 0;
  }
  tmp_pu7[7] = 0xffffffff;
  tmp_pu7[10] = GHIDRA_FIELD(mapEntityData, 49196, 4);
  tmp_pu7[0xb] = 0x2d8ca64;
  *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 49196, 4) + 0x2c) = tmp_pu7;
  GHIDRA_FIELD(mapEntityData, 49196, 4) = tmp_pu7;
  tmp_pu7[9] = tmp_i8;
  tmp_i4 = tmp_i8;
LAB_000ef491:
  *tmp_pu7 = *(uint32_t *)(param_1 + 0x18);
  tmp_pu7[1] = *(uint32_t *)(param_1 + 0x1c);
  tmp_pu7[2] = *(uint32_t *)(param_1 + 0x20);
  tmp_pu7[4] = tmp_i4;
  tmp_u1 = g_unk_00abe908;
  *(uint8_t *)(tmp_pu7 + 5) = 4;
  tmp_pu7[3] = 0;
  tmp_pu7[6] = tmp_u1;
  return;
}

void G_UpdateTeamMapData_Player(int param_1,int param_2,int param_3)
{
  uint32_t *tmp_pu1;
  uint tmp_u2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  bool tmp_b6;
  uint local_28;
  
  tmp_i3 = *(int *)(param_1 + 400);
  tmp_i5 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  if (tmp_i3 == 0) {
LAB_000efb10:
    if (param_3 != 0) {
      if (tmp_i3 == 0) {
        return;
      }
      goto LAB_000efb39;
    }
  }
  else {
    if (*(int *)(tmp_i3 + 3000) != 1) {
      if (*(int *)(tmp_i3 + 3000) != 2) goto LAB_000efb10;
      if (param_3 == 0) goto LAB_000efa5b;
      param_2 = 1;
    }
LAB_000efb39:
    tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49196, 4);
    if ((*(byte *)(tmp_i3 + 0xd) & 0x40) != 0) {
      return;
    }
    for (; (tmp_pu1 != (uint32_t *)0x0 && (tmp_pu1 != (uint32_t *)(mapEntityData + 0xc004)));
        tmp_pu1 = (uint32_t *)tmp_pu1[10]) {
      if (((int)tmp_pu1[7] < 0) && (tmp_i5 - tmp_pu1[9] == 0)) goto LAB_000efb7e;
    }
    tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
    if (GHIDRA_FIELD(mapEntityData, 49152, 4) == 0) {
      G_Error("G_AllocMapEntityData: out of entities");
      tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
    }
    GHIDRA_FIELD(mapEntityData, 49152, 4) = tmp_pu1[10];
    tmp_b6 = ((uint)tmp_pu1 & 1) != 0;
    local_28 = 0x30;
    tmp_pu4 = tmp_pu1;
    if (tmp_b6) {
      *(uint8_t *)tmp_pu1 = 0;
      tmp_pu4 = (uint32_t *)((int)tmp_pu1 + 1);
      local_28 = 0x2f;
    }
    if (((uint)tmp_pu4 & 2) != 0) {
      *(uint16_t *)tmp_pu4 = 0;
      tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
      local_28 = local_28 - 2;
    }
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)tmp_pu4 + tmp_u2) = 0;
      *(uint32_t *)((int)tmp_pu4 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < (local_28 & 0xfffffff8));
    tmp_pu4 = (uint32_t *)((int)tmp_pu4 + tmp_u2);
    if ((local_28 & 4) != 0) {
      *tmp_pu4 = 0;
      tmp_pu4 = tmp_pu4 + 1;
    }
    if ((local_28 & 2) != 0) {
      *(uint16_t *)tmp_pu4 = 0;
      tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
    }
    if (tmp_b6) {
      *(uint8_t *)tmp_pu4 = 0;
    }
    tmp_pu1[7] = 0xffffffff;
    tmp_pu1[10] = GHIDRA_FIELD(mapEntityData, 49196, 4);
    tmp_pu1[0xb] = 0x2d8ca64;
    *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 49196, 4) + 0x2c) = tmp_pu1;
    GHIDRA_FIELD(mapEntityData, 49196, 4) = tmp_pu1;
    tmp_pu1[9] = tmp_i5;
    tmp_i3 = *(int *)(param_1 + 400);
LAB_000efb7e:
    *tmp_pu1 = *(uint32_t *)(tmp_i3 + 0x14);
    tmp_pu1[1] = *(uint32_t *)(*(int *)(param_1 + 400) + 0x18);
    tmp_pu1[2] = *(uint32_t *)(*(int *)(param_1 + 400) + 0x1c);
    tmp_pu1[3] = (int)ROUND(*(float *)(*(int *)(param_1 + 400) + 0xb4));
    tmp_pu1[4] = tmp_i5;
    tmp_pu1[6] = g_unk_00abe908;
    *(bool *)(tmp_pu1 + 5) = *(int *)(param_1 + 0x2c8) < 1;
  }
  if (param_2 == 0) {
    return;
  }
  tmp_i3 = *(int *)(param_1 + 400);
  if (tmp_i3 == 0) {
    return;
  }
LAB_000efa5b:
  tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98400, 4);
  if ((*(byte *)(tmp_i3 + 0xd) & 0x40) == 0) {
    for (; (tmp_pu1 != (uint32_t *)0x0 && (tmp_pu1 != (uint32_t *)(mapEntityData + 0x18038)));
        tmp_pu1 = (uint32_t *)tmp_pu1[10]) {
      if (((int)tmp_pu1[7] < 0) && (tmp_i5 - tmp_pu1[9] == 0)) goto LAB_000efaa6;
    }
    tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
    if (GHIDRA_FIELD(mapEntityData, 98356, 4) == 0) {
      G_Error("G_AllocMapEntityData: out of entities");
      tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
    }
    GHIDRA_FIELD(mapEntityData, 98356, 4) = tmp_pu1[10];
    tmp_b6 = ((uint)tmp_pu1 & 1) != 0;
    local_28 = 0x30;
    tmp_pu4 = tmp_pu1;
    if (tmp_b6) {
      *(uint8_t *)tmp_pu1 = 0;
      tmp_pu4 = (uint32_t *)((int)tmp_pu1 + 1);
      local_28 = 0x2f;
    }
    if (((uint)tmp_pu4 & 2) != 0) {
      *(uint16_t *)tmp_pu4 = 0;
      tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
      local_28 = local_28 - 2;
    }
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)tmp_pu4 + tmp_u2) = 0;
      *(uint32_t *)((int)tmp_pu4 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < (local_28 & 0xfffffff8));
    tmp_pu4 = (uint32_t *)((int)tmp_pu4 + tmp_u2);
    if ((local_28 & 4) != 0) {
      *tmp_pu4 = 0;
      tmp_pu4 = tmp_pu4 + 1;
    }
    if ((local_28 & 2) != 0) {
      *(uint16_t *)tmp_pu4 = 0;
      tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
    }
    if (tmp_b6) {
      *(uint8_t *)tmp_pu4 = 0;
    }
    tmp_pu1[7] = 0xffffffff;
    tmp_pu1[10] = GHIDRA_FIELD(mapEntityData, 98400, 4);
    tmp_pu1[0xb] = 0x2d98a98;
    *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 98400, 4) + 0x2c) = tmp_pu1;
    GHIDRA_FIELD(mapEntityData, 98400, 4) = tmp_pu1;
    tmp_pu1[9] = tmp_i5;
    tmp_i3 = *(int *)(param_1 + 400);
LAB_000efaa6:
    *tmp_pu1 = *(uint32_t *)(tmp_i3 + 0x14);
    tmp_pu1[1] = *(uint32_t *)(*(int *)(param_1 + 400) + 0x18);
    tmp_pu1[2] = *(uint32_t *)(*(int *)(param_1 + 400) + 0x1c);
    tmp_pu1[3] = (int)ROUND(*(float *)(*(int *)(param_1 + 400) + 0xb4));
    tmp_pu1[4] = tmp_i5;
    tmp_pu1[6] = g_unk_00abe908;
    *(bool *)(tmp_pu1 + 5) = *(int *)(param_1 + 0x2c8) < 1;
  }
  return;
}

void G_UpdateTeamMapData_CommandmapMarker(int param_1)
{
  uint32_t *tmp_pu1;
  uint tmp_u2;
  uint32_t *tmp_pu3;
  uint32_t tmp_u4;
  int tmp_i5;
  bool tmp_b6;
  uint local_24;
  
  if ((*(int *)(param_1 + 0x218) != 0) && (*(int *)(param_1 + 0x458) == 0)) {
    tmp_u2 = *(uint *)(*(int *)(param_1 + 0x218) + 0x1a8);
    tmp_i5 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49196, 4);
    if ((tmp_u2 & 2) != 0) {
      for (; (tmp_pu1 != (uint32_t *)0x0 && (tmp_pu1 != (uint32_t *)(mapEntityData + 0xc004)));
          tmp_pu1 = (uint32_t *)tmp_pu1[10]) {
        if (((int)tmp_pu1[7] < 0) && (tmp_i5 - tmp_pu1[9] == 0)) goto LAB_000f024f;
      }
      tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
      if (GHIDRA_FIELD(mapEntityData, 49152, 4) == 0) {
        G_Error("G_AllocMapEntityData: out of entities");
        tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
      }
      GHIDRA_FIELD(mapEntityData, 49152, 4) = tmp_pu1[10];
      tmp_b6 = ((uint)tmp_pu1 & 1) != 0;
      local_24 = 0x30;
      tmp_pu3 = tmp_pu1;
      if (tmp_b6) {
        *(uint8_t *)tmp_pu1 = 0;
        tmp_pu3 = (uint32_t *)((int)tmp_pu1 + 1);
        local_24 = 0x2f;
      }
      if (((uint)tmp_pu3 & 2) != 0) {
        *(uint16_t *)tmp_pu3 = 0;
        tmp_pu3 = (uint32_t *)((int)tmp_pu3 + 2);
        local_24 = local_24 - 2;
      }
      tmp_u2 = 0;
      do {
        *(uint32_t *)((int)tmp_pu3 + tmp_u2) = 0;
        *(uint32_t *)((int)tmp_pu3 + tmp_u2 + 4) = 0;
        tmp_u2 = tmp_u2 + 8;
      } while (tmp_u2 < (local_24 & 0xfffffff8));
      tmp_pu3 = (uint32_t *)((int)tmp_pu3 + tmp_u2);
      if ((local_24 & 4) != 0) {
        *tmp_pu3 = 0;
        tmp_pu3 = tmp_pu3 + 1;
      }
      if ((local_24 & 2) != 0) {
        *(uint16_t *)tmp_pu3 = 0;
        tmp_pu3 = (uint32_t *)((int)tmp_pu3 + 2);
      }
      if (tmp_b6) {
        *(uint8_t *)tmp_pu3 = 0;
      }
      tmp_pu1[7] = 0xffffffff;
      tmp_pu1[10] = GHIDRA_FIELD(mapEntityData, 49196, 4);
      tmp_pu1[0xb] = 0x2d8ca64;
      *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 49196, 4) + 0x2c) = tmp_pu1;
      GHIDRA_FIELD(mapEntityData, 49196, 4) = tmp_pu1;
      tmp_pu1[9] = tmp_i5;
LAB_000f024f:
      *tmp_pu1 = *(uint32_t *)(param_1 + 0x5c);
      tmp_pu1[1] = *(uint32_t *)(param_1 + 0x60);
      tmp_pu1[2] = *(uint32_t *)(param_1 + 100);
      tmp_pu1[4] = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x108);
      tmp_u4 = g_unk_00abe908;
      *(uint8_t *)(tmp_pu1 + 5) = 9;
      tmp_pu1[3] = 0;
      tmp_pu1[6] = tmp_u4;
      tmp_u2 = *(uint *)(*(int *)(param_1 + 0x218) + 0x1a8);
    }
    tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98400, 4);
    if ((tmp_u2 & 1) != 0) {
      for (; (tmp_pu1 != (uint32_t *)0x0 && (tmp_pu1 != (uint32_t *)(mapEntityData + 0x18038)));
          tmp_pu1 = (uint32_t *)tmp_pu1[10]) {
        if (((int)tmp_pu1[7] < 0) && (tmp_i5 - tmp_pu1[9] == 0)) goto LAB_000f02c7;
      }
      tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
      if (GHIDRA_FIELD(mapEntityData, 98356, 4) == 0) {
        G_Error("G_AllocMapEntityData: out of entities");
        tmp_pu1 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
      }
      GHIDRA_FIELD(mapEntityData, 98356, 4) = tmp_pu1[10];
      tmp_b6 = ((uint)tmp_pu1 & 1) != 0;
      local_24 = 0x30;
      tmp_pu3 = tmp_pu1;
      if (tmp_b6) {
        *(uint8_t *)tmp_pu1 = 0;
        tmp_pu3 = (uint32_t *)((int)tmp_pu1 + 1);
        local_24 = 0x2f;
      }
      if (((uint)tmp_pu3 & 2) != 0) {
        *(uint16_t *)tmp_pu3 = 0;
        tmp_pu3 = (uint32_t *)((int)tmp_pu3 + 2);
        local_24 = local_24 - 2;
      }
      tmp_u2 = 0;
      do {
        *(uint32_t *)((int)tmp_pu3 + tmp_u2) = 0;
        *(uint32_t *)((int)tmp_pu3 + tmp_u2 + 4) = 0;
        tmp_u2 = tmp_u2 + 8;
      } while (tmp_u2 < (local_24 & 0xfffffff8));
      tmp_pu3 = (uint32_t *)((int)tmp_pu3 + tmp_u2);
      if ((local_24 & 4) != 0) {
        *tmp_pu3 = 0;
        tmp_pu3 = tmp_pu3 + 1;
      }
      if ((local_24 & 2) != 0) {
        *(uint16_t *)tmp_pu3 = 0;
        tmp_pu3 = (uint32_t *)((int)tmp_pu3 + 2);
      }
      if (tmp_b6) {
        *(uint8_t *)tmp_pu3 = 0;
      }
      tmp_pu1[7] = 0xffffffff;
      tmp_pu1[10] = GHIDRA_FIELD(mapEntityData, 98400, 4);
      tmp_pu1[0xb] = 0x2d98a98;
      *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 98400, 4) + 0x2c) = tmp_pu1;
      GHIDRA_FIELD(mapEntityData, 98400, 4) = tmp_pu1;
      tmp_pu1[9] = tmp_i5;
LAB_000f02c7:
      *tmp_pu1 = *(uint32_t *)(param_1 + 0x5c);
      tmp_pu1[1] = *(uint32_t *)(param_1 + 0x60);
      tmp_pu1[2] = *(uint32_t *)(param_1 + 100);
      if (*(int *)(param_1 + 0x218) == 0) {
        tmp_u4 = 0xffffffff;
      }
      else {
        tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x108);
      }
      tmp_pu1[4] = tmp_u4;
      tmp_u4 = g_unk_00abe908;
      *(uint8_t *)(tmp_pu1 + 5) = 9;
      tmp_pu1[3] = 0;
      tmp_pu1[6] = tmp_u4;
    }
  }
  return;
}

void G_SendSpectatorMapEntityInfo(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint8_t local_81c [2056];
  uint32_t uStack_14;
  
  tmp_i2 = 0;
  uStack_14 = 0xf051b;
  for (tmp_i1 = GHIDRA_FIELD(mapEntityData, 49196, 4); tmp_i1 != 0; tmp_i1 = *(int *)(tmp_i1 + 0x28)) {
    while( true ) {
      if (tmp_i1 == 0x2d8ca64) goto LAB_000f0580;
      if ((1 < (*(char *)(tmp_i1 + 0x14) - 3U & 0xfb)) ||
         ((-1 < *(int *)(tmp_i1 + 0x1c) && (*(int *)(tmp_i1 + 0x1c) != *(int *)(param_1 + 0xac)))))
      break;
      tmp_i1 = *(int *)(tmp_i1 + 0x28);
      tmp_i2 = tmp_i2 + 1;
      if (tmp_i1 == 0) goto LAB_000f0580;
    }
  }
LAB_000f0580:
  tmp_i3 = 0;
  for (tmp_i1 = GHIDRA_FIELD(mapEntityData, 98400, 4); tmp_i1 != 0; tmp_i1 = *(int *)(tmp_i1 + 0x28)) {
    while( true ) {
      if (tmp_i1 == 0x2d98a98) goto LAB_000f05d0;
      if ((1 < (*(char *)(tmp_i1 + 0x14) - 3U & 0xfb)) ||
         ((-1 < *(int *)(tmp_i1 + 0x1c) && (*(int *)(tmp_i1 + 0x1c) != *(int *)(param_1 + 0xac)))))
      break;
      tmp_i1 = *(int *)(tmp_i1 + 0x28);
      tmp_i3 = tmp_i3 + 1;
      if (tmp_i1 == 0) goto LAB_000f05d0;
    }
  }
LAB_000f05d0:
  Com_sprintf(local_81c,0x800,"entnfo %i %i",tmp_i2,tmp_i3);
  tmp_i1 = GHIDRA_FIELD(mapEntityData, 49196, 4);
  while ((tmp_i2 = GHIDRA_FIELD(mapEntityData, 98400, 4), tmp_i1 != 0 && (tmp_i1 != 0x2d8ca64))) {
    if ((((byte)(*(char *)(tmp_i1 + 0x14) - 7U) < 2) || ((byte)(*(char *)(tmp_i1 + 0x14) - 3U) < 3))
       && ((*(int *)(tmp_i1 + 0x1c) < 0 || (*(int *)(tmp_i1 + 0x1c) == *(int *)(param_1 + 0xac))))) {
      G_PushMapEntityToBuffer(local_81c,0x800,tmp_i1);
      tmp_i1 = *(int *)(tmp_i1 + 0x28);
    }
    else {
      tmp_i1 = *(int *)(tmp_i1 + 0x28);
    }
  }
  while ((tmp_i2 != 0 && (tmp_i2 != 0x2d98a98))) {
    if ((((byte)(*(char *)(tmp_i2 + 0x14) - 7U) < 2) || ((byte)(*(char *)(tmp_i2 + 0x14) - 3U) < 3))
       && ((*(int *)(tmp_i2 + 0x1c) < 0 || (*(int *)(tmp_i2 + 0x1c) == *(int *)(param_1 + 0xac))))) {
      G_PushMapEntityToBuffer(local_81c,0x800,tmp_i2);
      tmp_i2 = *(int *)(tmp_i2 + 0x28);
    }
    else {
      tmp_i2 = *(int *)(tmp_i2 + 0x28);
    }
  }
  tmp_i1 = Q_stricmp(local_81c,oldBuffer_12828);
  if (tmp_i1 == 0) {
    return;
  }
  Q_strncpyz(oldBuffer_12828,local_81c,0x800);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,local_81c);
  return;
}

void G_SendMapEntityInfo(int param_1)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  char *tmp_pc3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  uint8_t *local_830;
  uint8_t local_81c [2060];
  
  tmp_i5 = *(int *)(*(int *)(param_1 + 400) + 3000);
  if (tmp_i5 == 3) {
    G_SendSpectatorMapEntityInfo(param_1);
    return;
  }
  if (1 < tmp_i5 - 1U) {
    return;
  }
  if (tmp_i5 == 1) {
    local_830 = mapEntityData;
    if (GHIDRA_FIELD(mapEntityData, 49196, 4) == 0) {
      tmp_i5 = 0;
    }
    else {
      tmp_i6 = 0x2d8ca64;
      tmp_i5 = 0;
      tmp_i8 = GHIDRA_FIELD(mapEntityData, 49196, 4);
      if (GHIDRA_FIELD(mapEntityData, 49196, 4) != 0x2d8ca64) goto LAB_000f07fc;
    }
LAB_000f08a0:
    tmp_pc3 = "entnfo %i 0";
  }
  else {
    if (GHIDRA_FIELD(mapEntityData, 98400, 4) == 0) {
      local_830 = (uint8_t *)0x2d8ca94;
      tmp_i5 = 0;
    }
    else {
      tmp_i6 = 0x2d98a98;
      tmp_i5 = 0;
      local_830 = (uint8_t *)0x2d8ca94;
      tmp_i8 = GHIDRA_FIELD(mapEntityData, 98400, 4);
      if (GHIDRA_FIELD(mapEntityData, 98400, 4) != 0x2d98a98) {
LAB_000f07fc:
        tmp_i5 = 0;
        do {
          if (g_unk_00abe908 - *(int *)(tmp_i8 + 0x18) < 0x1389) {
            *(uint32_t *)(tmp_i8 + 0x20) = 2;
LAB_000f0843:
            tmp_i8 = *(int *)(tmp_i8 + 0x28);
            tmp_i5 = tmp_i5 + 1;
          }
          else {
            *(uint32_t *)(tmp_i8 + 0x20) = 1;
            if (*(char *)(tmp_i8 + 0x14) == '\0') {
              tmp_i2 = *(int *)(tmp_i8 + 0x28);
              tmp_i4 = *(int *)(tmp_i8 + 0x2c);
            }
            else {
              if ((*(char *)(tmp_i8 + 0x14) != '\x02') ||
                 (*(int *)(tmp_i8 + 0x1c) != *(int *)(param_1 + 0xac))) goto LAB_000f0843;
              tmp_i2 = *(int *)(tmp_i8 + 0x28);
              tmp_i4 = *(int *)(tmp_i8 + 0x2c);
            }
            tmp_i7 = tmp_i2;
            if (tmp_i4 == 0) {
              G_Error("G_FreeMapEntityData: not active");
              tmp_i7 = *(int *)(tmp_i8 + 0x28);
              tmp_i4 = *(int *)(tmp_i8 + 0x2c);
            }
            *(int *)(tmp_i4 + 0x28) = tmp_i7;
            *(uint32_t *)(*(int *)(tmp_i8 + 0x28) + 0x2c) = *(uint32_t *)(tmp_i8 + 0x2c);
            *(uint32_t *)(tmp_i8 + 0x28) = *(uint32_t *)(local_830 + 0xc000);
            *(int *)(local_830 + 0xc000) = tmp_i8;
            tmp_i8 = tmp_i2;
          }
        } while ((tmp_i8 != 0) && (tmp_i8 != tmp_i6));
        if (*(int *)(*(int *)(param_1 + 400) + 3000) == 1) goto LAB_000f08a0;
      }
    }
    tmp_pc3 = "entnfo 0 %i";
  }
  Com_sprintf(local_81c,0x800,tmp_pc3,tmp_i5);
  tmp_pu1 = *(uint8_t **)(local_830 + 0xc02c);
  if (tmp_pu1 != (uint8_t *)0x0) {
    do {
      if (tmp_pu1 == local_830 + 0xc004) break;
      if ((*(int *)(tmp_pu1 + 0x1c) < 0) || (*(int *)(tmp_pu1 + 0x1c) == *(int *)(param_1 + 0xac))) {
        G_PushMapEntityToBuffer(local_81c,0x800,tmp_pu1);
        tmp_pu1 = *(uint8_t **)(tmp_pu1 + 0x28);
      }
      else {
        tmp_pu1 = *(uint8_t **)(tmp_pu1 + 0x28);
      }
    } while (tmp_pu1 != (uint8_t *)0x0);
  }
  tmp_i5 = Q_stricmp(local_81c,oldBuffer_12853);
  if (tmp_i5 != 0) {
    Q_strncpyz(oldBuffer_12853,local_81c,0x800);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,local_81c);
  }
  return;
}

void G_UpdateTeamMapData(void)
{
  uint8_t *tmp_pu1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint tmp_u7;
  uint32_t *tmp_pu8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  int *tmp_pi12;
  uint8_t *tmp_pu13;
  int tmp_i14;
  bool tmp_b15;
  bool tmp_b16;
  bool tmp_b17;
  bool tmp_b18;
  uint32_t *local_7c;
  uint local_78;
  uint local_6c;
  uint local_68;
  uint32_t local_40;
  uint32_t local_3c;
  float local_38;
  uint32_t local_34;
  uint32_t local_30;
  float local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0xf0a99;
  if (g_unk_00abe908 - g_unk_02a9840c < 500) {
    return;
  }
  g_unk_02a9840c = g_unk_00abe908;
  local_7c = (uint32_t *)LandmineEntities;
  if (0 < LandmineEntities) {
    tmp_i9 = 0;
    do {
      tmp_i14 = (&g_unk_0087ca04)[tmp_i9];
      tmp_i11 = *(int *)(tmp_i14 + 0x108);
      tmp_i10 = (tmp_i14 + -0x93e4a0 >> 9) * -0x55555555;
      if (tmp_i11 % 4 == 1) {
        tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49196, 4);
        if (3 < tmp_i11 - 4U) {
          for (; (tmp_pu3 != (uint32_t *)0x0 && (tmp_pu3 != (uint32_t *)(mapEntityData + 0xc004)))
              ; tmp_pu3 = (uint32_t *)tmp_pu3[10]) {
            if (((int)tmp_pu3[7] < 0) && (tmp_i10 - tmp_pu3[9] == 0)) goto LAB_000f0d3f;
          }
          tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
          if (GHIDRA_FIELD(mapEntityData, 49152, 4) == 0) {
            G_Error("G_AllocMapEntityData: out of entities");
            tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
          }
          GHIDRA_FIELD(mapEntityData, 49152, 4) = tmp_pu3[10];
          tmp_b16 = ((uint)tmp_pu3 & 1) != 0;
          local_7c = (uint32_t *)0x30;
          tmp_pu8 = tmp_pu3;
          if (tmp_b16) {
            *(uint8_t *)tmp_pu3 = 0;
            local_7c = (uint32_t *)0x2f;
            tmp_pu8 = (uint32_t *)((int)tmp_pu3 + 1);
          }
          if (((uint)tmp_pu8 & 2) != 0) {
            *(uint16_t *)tmp_pu8 = 0;
            tmp_pu8 = (uint32_t *)((int)tmp_pu8 + 2);
            local_7c = (uint32_t *)((int)local_7c - 2);
          }
          tmp_u7 = 0;
          do {
            *(uint32_t *)((int)tmp_pu8 + tmp_u7) = 0;
            *(uint32_t *)((int)tmp_pu8 + tmp_u7 + 4) = 0;
            tmp_u7 = tmp_u7 + 8;
          } while (tmp_u7 < ((uint)local_7c & 0xfffffff8));
          tmp_pu8 = (uint32_t *)((int)tmp_pu8 + tmp_u7);
          if (((uint)local_7c & 4) != 0) {
            *tmp_pu8 = 0;
            tmp_pu8 = tmp_pu8 + 1;
          }
          if (((uint)local_7c & 2) != 0) {
            *(uint16_t *)tmp_pu8 = 0;
            tmp_pu8 = (uint32_t *)((int)tmp_pu8 + 2);
          }
          if (tmp_b16) {
            *(uint8_t *)tmp_pu8 = 0;
          }
          tmp_pu3[7] = 0xffffffff;
          tmp_pu3[10] = GHIDRA_FIELD(mapEntityData, 49196, 4);
          tmp_pu3[0xb] = 0x2d8ca64;
          *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 49196, 4) + 0x2c) = tmp_pu3;
          GHIDRA_FIELD(mapEntityData, 49196, 4) = tmp_pu3;
          tmp_pu3[9] = tmp_i10;
LAB_000f0d3f:
          *tmp_pu3 = *(uint32_t *)(tmp_i14 + 0x168);
          tmp_pu3[1] = *(uint32_t *)(tmp_i14 + 0x16c);
          tmp_pu3[2] = *(uint32_t *)(tmp_i14 + 0x170);
          goto LAB_000f0b98;
        }
      }
      else if ((tmp_i11 % 4 == 2) &&
              (tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98400, 4), 3 < tmp_i11 - 4U)) {
        for (; (tmp_pu3 != (uint32_t *)0x0 && (tmp_pu3 != (uint32_t *)(mapEntityData + 0x18038)));
            tmp_pu3 = (uint32_t *)tmp_pu3[10]) {
          if (((int)tmp_pu3[7] < 0) && (tmp_i10 - tmp_pu3[9] == 0)) goto LAB_000f0b7e;
        }
        tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
        if (GHIDRA_FIELD(mapEntityData, 98356, 4) == 0) {
          G_Error("G_AllocMapEntityData: out of entities");
          tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
        }
        GHIDRA_FIELD(mapEntityData, 98356, 4) = tmp_pu3[10];
        tmp_b16 = ((uint)tmp_pu3 & 1) != 0;
        local_78 = 0x30;
        local_7c = tmp_pu3;
        if (tmp_b16) {
          *(uint8_t *)tmp_pu3 = 0;
          local_78 = 0x2f;
          local_7c = (uint32_t *)((int)tmp_pu3 + 1);
        }
        if (((uint)local_7c & 2) != 0) {
          *(uint16_t *)local_7c = 0;
          local_7c = (uint32_t *)((int)local_7c + 2);
          local_78 = local_78 - 2;
        }
        tmp_u7 = 0;
        do {
          *(uint32_t *)((int)local_7c + tmp_u7) = 0;
          *(uint32_t *)((int)local_7c + tmp_u7 + 4) = 0;
          tmp_u7 = tmp_u7 + 8;
        } while (tmp_u7 < (local_78 & 0xfffffff8));
        local_7c = (uint32_t *)((int)local_7c + tmp_u7);
        if ((local_78 & 4) != 0) {
          *local_7c = 0;
          local_7c = local_7c + 1;
        }
        if ((local_78 & 2) != 0) {
          *(uint16_t *)local_7c = 0;
          local_7c = (uint32_t *)((int)local_7c + 2);
        }
        if (tmp_b16) {
          *(uint8_t *)local_7c = 0;
        }
        tmp_pu3[7] = 0xffffffff;
        tmp_pu3[10] = GHIDRA_FIELD(mapEntityData, 98400, 4);
        tmp_pu3[0xb] = 0x2d98a98;
        *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 98400, 4) + 0x2c) = tmp_pu3;
        GHIDRA_FIELD(mapEntityData, 98400, 4) = tmp_pu3;
        tmp_pu3[9] = tmp_i10;
LAB_000f0b7e:
        *tmp_pu3 = *(uint32_t *)(tmp_i14 + 0x168);
        tmp_pu3[1] = *(uint32_t *)(tmp_i14 + 0x16c);
        tmp_pu3[2] = *(uint32_t *)(tmp_i14 + 0x170);
LAB_000f0b98:
        tmp_pu3[4] = *(int *)(tmp_i14 + 0x108) % 4;
        tmp_i14 = g_unk_00abe908;
        *(uint8_t *)(tmp_pu3 + 5) = 6;
        tmp_pu3[6] = tmp_i14;
        local_7c = (uint32_t *)LandmineEntities;
      }
      tmp_i9 = tmp_i9 + 1;
    } while (tmp_i9 < (int)local_7c);
  }
  if (g_unk_00abe93c < 1) {
    if (IndicatorEntities < 1) {
      return;
    }
  }
  else {
    tmp_i14 = 0;
    tmp_i9 = g_unk_00abe93c;
    do {
      while( true ) {
        tmp_i11 = (&g_unk_00abe944)[tmp_i14] * 0x600;
        tmp_pi12 = (int *)(g_entities + tmp_i11);
        if ((*(int *)(g_entities + tmp_i11 + 0x194) != 0) && (*(int *)(g_entities + tmp_i11 + 4) == 1)
           ) break;
        tmp_i14 = tmp_i14 + 1;
        if (tmp_i9 <= tmp_i14) goto LAB_000f0ca1;
      }
      G_UpdateTeamMapData_Player(tmp_pi12,0,0);
      tmp_i9 = *tmp_pi12;
      tmp_pu3 = (uint32_t *)(mapEntityData + 0xc004);
      do {
        for (tmp_pu8 = (uint32_t *)tmp_pu3[10]; (tmp_pu8 != (uint32_t *)0x0 && (tmp_pu8 != tmp_pu3));
            tmp_pu8 = (uint32_t *)tmp_pu8[10]) {
          if ((-1 < (int)tmp_pu8[7]) && (tmp_pu8[9] == tmp_i9)) {
            do {
              *tmp_pu8 = *(uint32_t *)(*(int *)(g_entities + tmp_i11 + 400) + 0x14);
              tmp_pu8[1] = *(uint32_t *)(*(int *)(g_entities + tmp_i11 + 400) + 0x18);
              tmp_pu8[2] = *(uint32_t *)(*(int *)(g_entities + tmp_i11 + 400) + 0x1c);
              tmp_pu8[3] = (int)ROUND(*(float *)(*(int *)(g_entities + tmp_i11 + 400) + 0xb4));
              tmp_i9 = *tmp_pi12;
              do {
                tmp_pu8 = (uint32_t *)tmp_pu8[10];
                if ((tmp_pu8 == (uint32_t *)0x0) || (tmp_pu8 == tmp_pu3)) goto LAB_000f0c80;
              } while (((int)tmp_pu8[7] < 0) || (tmp_i9 != tmp_pu8[9]));
            } while( true );
          }
        }
LAB_000f0c80:
        tmp_pu3 = tmp_pu3 + 0x300d;
      } while (tmp_pu3 != (uint32_t *)(pushed + 0xbfcc));
      tmp_i14 = tmp_i14 + 1;
      tmp_i9 = g_unk_00abe93c;
    } while (tmp_i14 < g_unk_00abe93c);
LAB_000f0ca1:
    if (IndicatorEntities < 1) goto LAB_000f0fa6;
  }
  tmp_i14 = 0;
  do {
    tmp_i9 = (&g_unk_0087b9e4)[tmp_i14];
    if (*(int *)(tmp_i9 + 0x194) != 0) {
      switch(*(uint32_t *)(tmp_i9 + 4)) {
      case 0xd:
        if ((*(int *)(tmp_i9 + 0x218) != 0) && (*(int *)(*(int *)(tmp_i9 + 0x218) + 0x458) == 0)) {
          G_UpdateTeamMapData_Destruct(tmp_i9);
        }
        break;
      case 0x1f:
        if ((*(int *)(tmp_i9 + 0x218) != 0) && (*(int *)(*(int *)(tmp_i9 + 0x218) + 0x458) == 0)) {
          G_UpdateTeamMapData_Construct(tmp_i9);
        }
        break;
      case 0x24:
      case 0x25:
        G_UpdateTeamMapData_Tank(tmp_i9);
        break;
      case 0x37:
        G_UpdateTeamMapData_CommandmapMarker(tmp_i9);
      }
    }
    tmp_i14 = tmp_i14 + 1;
    tmp_i9 = g_unk_00abe93c;
  } while (tmp_i14 < IndicatorEntities);
LAB_000f0fa6:
  if (0 < tmp_i9) {
    local_7c = (uint32_t *)0x0;
    do {
      tmp_i14 = (&g_unk_00abe944)[(int)local_7c] * 0x600;
      tmp_pu1 = g_entities + tmp_i14;
      if ((*(int *)(g_entities + tmp_i14 + 0x194) != 0) &&
         (tmp_i11 = *(int *)(g_entities + tmp_i14 + 400), tmp_i11 != 0)) {
        if (*(int *)(tmp_i11 + 0xbc8) == 3) {
          if (((*(byte *)(tmp_i11 + 0xedc) & 0x10) == 0) ||
             (*(int *)(g_entities + tmp_i14 + 0x2c8) < 1)) {
LAB_000f0fc9:
            tmp_b16 = false;
            tmp_b15 = false;
LAB_000f0fd5:
            tmp_i9 = g_unk_00abe93c;
            if (((jp_keepAwards[0xc] & 8) == 0) || ((*(byte *)(tmp_i11 + 0xed0) & 0x10) == 0))
            goto LAB_000f100a;
          }
          else {
            tmp_b15 = *(int *)(tmp_i11 + 3000) == 2;
            tmp_b16 = *(int *)(tmp_i11 + 3000) == 1;
            G_SetupFrustum(tmp_pu1);
            local_78 = g_unk_00abe93c;
            tmp_i11 = *(int *)(g_entities + tmp_i14 + 400);
            if (0 < g_unk_00abe93c) {
              tmp_i9 = 0;
              do {
                while( true ) {
                  tmp_i10 = (&g_unk_00abe944)[tmp_i9] * 0x600;
                  tmp_pu13 = g_entities + tmp_i10;
                  if ((((tmp_pu1 != tmp_pu13) && (*(int *)(g_entities + tmp_i10 + 0x194) != 0)) &&
                      (0 < *(int *)(g_entities + tmp_i10 + 0x2c8))) &&
                     ((tmp_i4 = *(int *)(g_entities + tmp_i10 + 400),
                      *(int *)(tmp_i4 + 3000) != *(int *)(tmp_i11 + 3000) &&
                      (*(int *)(tmp_i4 + 0x16c) != 0)))) break;
                  tmp_i9 = tmp_i9 + 1;
                  if ((int)local_78 <= tmp_i9) goto LAB_000f1219;
                }
                local_40 = *(uint32_t *)(tmp_i4 + 0x14);
                local_3c = *(uint32_t *)(tmp_i4 + 0x18);
                local_2c = *(float *)(tmp_i4 + 0x1c);
                local_38 = *(float *)(tmp_i4 + 0x3e4) + local_2c;
                local_28 = *(uint32_t *)(tmp_i4 + 0x14);
                local_24 = *(uint32_t *)(tmp_i4 + 0x18);
                local_20 = *(float *)(tmp_i4 + 0x1c) + *(float *)(tmp_i4 + 0x3f0);
                local_34 = local_40;
                local_30 = local_3c;
                tmp_i11 = G_VisibleFromBinoculars(tmp_pu1,tmp_pu13,&local_40);
                if ((tmp_i11 != 0) ||
                   ((tmp_i11 = G_VisibleFromBinoculars(tmp_pu1,tmp_pu13,&local_34), tmp_i11 != 0 ||
                    (tmp_i11 = G_VisibleFromBinoculars(tmp_pu1,tmp_pu13,&local_28), tmp_i11 != 0)))) {
                  tmp_i11 = *(int *)(g_entities + tmp_i10 + 400);
                  tmp_i4 = (tmp_i10 >> 9) * -0x55555555;
                  if (tmp_i11 != 0) {
                    if (*(int *)(tmp_i11 + 3000) == 1) {
                      tmp_b17 = tmp_b15;
                      if ((*(byte *)(tmp_i11 + 0xd) & 0x40) == 0) {
LAB_000f1702:
                        tmp_i6 = *(int *)(g_entities + tmp_i14 + 0xac);
                        if ((GHIDRA_FIELD(mapEntityData, 49196, 4) != 0) && (GHIDRA_FIELD(mapEntityData, 49196, 4) != 0x2d8ca64)
                           ) {
                          tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49196, 4);
                          if (tmp_i6 != -1) {
                            tmp_i5 = *(int *)(GHIDRA_FIELD(mapEntityData, 49196, 4) + 0x1c);
                            if (tmp_i6 == tmp_i5) goto LAB_000f177c;
                            do {
                              if (tmp_i5 < 0) goto LAB_000f177c;
                              while( true ) {
                                tmp_pu3 = (uint32_t *)tmp_pu3[10];
                                if ((tmp_pu3 == (uint32_t *)0x0) ||
                                   (tmp_pu3 == (uint32_t *)(mapEntityData + 0xc004)))
                                goto LAB_000f1af0;
                                tmp_i5 = tmp_pu3[7];
                                if (tmp_i6 != tmp_i5) break;
LAB_000f177c:
                                if (tmp_i4 == tmp_pu3[9]) goto LAB_000f178d;
                              }
                            } while( true );
                          }
                          do {
                            if ((-1 < (int)tmp_pu3[7]) && (tmp_i4 == tmp_pu3[9])) goto LAB_000f178d;
                            tmp_pu3 = (uint32_t *)tmp_pu3[10];
                          } while ((tmp_pu3 != (uint32_t *)0x0) &&
                                  (tmp_pu3 != (uint32_t *)(mapEntityData + 0xc004)));
                        }
LAB_000f1af0:
                        tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
                        if (GHIDRA_FIELD(mapEntityData, 49152, 4) == 0) {
                          G_Error("G_AllocMapEntityData: out of entities");
                          tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
                        }
                        GHIDRA_FIELD(mapEntityData, 49152, 4) = tmp_pu3[10];
                        tmp_b18 = ((uint)tmp_pu3 & 1) != 0;
                        local_68 = 0x30;
                        tmp_pu8 = tmp_pu3;
                        if (tmp_b18) {
                          *(uint8_t *)tmp_pu3 = 0;
                          tmp_pu8 = (uint32_t *)((int)tmp_pu3 + 1);
                          local_68 = 0x2f;
                        }
                        if (((uint)tmp_pu8 & 2) != 0) {
                          *(uint16_t *)tmp_pu8 = 0;
                          tmp_pu8 = (uint32_t *)((int)tmp_pu8 + 2);
                          local_68 = local_68 - 2;
                        }
                        tmp_u7 = 0;
                        do {
                          *(uint32_t *)((int)tmp_pu8 + tmp_u7) = 0;
                          *(uint32_t *)((int)tmp_pu8 + tmp_u7 + 4) = 0;
                          tmp_u7 = tmp_u7 + 8;
                        } while (tmp_u7 < (local_68 & 0xfffffff8));
                        tmp_pu8 = (uint32_t *)((int)tmp_pu8 + tmp_u7);
                        if ((local_68 & 4) != 0) {
                          *tmp_pu8 = 0;
                          tmp_pu8 = tmp_pu8 + 1;
                        }
                        if ((local_68 & 2) != 0) {
                          *(uint16_t *)tmp_pu8 = 0;
                          tmp_pu8 = (uint32_t *)((int)tmp_pu8 + 2);
                        }
                        if (tmp_b18) {
                          *(uint8_t *)tmp_pu8 = 0;
                        }
                        tmp_pu3[7] = 0xffffffff;
                        tmp_pu3[10] = GHIDRA_FIELD(mapEntityData, 49196, 4);
                        tmp_pu3[0xb] = 0x2d8ca64;
                        *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 49196, 4) + 0x2c) = tmp_pu3;
                        GHIDRA_FIELD(mapEntityData, 49196, 4) = tmp_pu3;
                        tmp_pu3[9] = tmp_i4;
                        tmp_pu3[7] = *(uint32_t *)(g_entities + tmp_i14 + 0xac);
                        tmp_i11 = *(int *)(g_entities + tmp_i10 + 400);
LAB_000f178d:
                        *tmp_pu3 = *(uint32_t *)(tmp_i11 + 0x14);
                        tmp_pu3[1] = *(uint32_t *)(*(int *)(g_entities + tmp_i10 + 400) + 0x18);
                        tmp_pu3[2] = *(uint32_t *)(*(int *)(g_entities + tmp_i10 + 400) + 0x1c);
                        tmp_pu3[3] = (int)ROUND(*(float *)(*(int *)(g_entities + tmp_i10 + 400) + 0xb4
                                                         ));
                        tmp_pu3[4] = tmp_i4;
                        tmp_i11 = g_unk_00abe908;
                        *(uint8_t *)(tmp_pu3 + 5) = 2;
                        tmp_pu3[6] = tmp_i11;
                        goto joined_r0x000f17f0;
                      }
                    }
                    else {
                      tmp_b17 = *(int *)(tmp_i11 + 3000) == 2 || tmp_b15;
                      if ((*(byte *)(tmp_i11 + 0xd) & 0x40) == 0) {
                        if (tmp_b16) goto LAB_000f1702;
joined_r0x000f17f0:
                        if (tmp_b17) {
                          tmp_i11 = *(int *)(g_entities + tmp_i14 + 0xac);
                          if ((GHIDRA_FIELD(mapEntityData, 98400, 4) != 0) &&
                             (GHIDRA_FIELD(mapEntityData, 98400, 4) != 0x2d98a98)) {
                            tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98400, 4);
                            if (tmp_i11 != -1) {
                              tmp_i6 = *(int *)(GHIDRA_FIELD(mapEntityData, 98400, 4) + 0x1c);
                              if (tmp_i11 == tmp_i6) goto LAB_000f185f;
                              do {
                                if (tmp_i6 < 0) goto LAB_000f185f;
                                while( true ) {
                                  tmp_pu3 = (uint32_t *)tmp_pu3[10];
                                  if ((tmp_pu3 == (uint32_t *)0x0) ||
                                     (tmp_pu3 == (uint32_t *)(mapEntityData + 0x18038)))
                                  goto LAB_000f18dc;
                                  tmp_i6 = tmp_pu3[7];
                                  if (tmp_i11 != tmp_i6) break;
LAB_000f185f:
                                  if (tmp_i4 == tmp_pu3[9]) goto LAB_000f186c;
                                }
                              } while( true );
                            }
                            do {
                              if ((-1 < (int)tmp_pu3[7]) && (tmp_i4 == tmp_pu3[9])) goto LAB_000f186c;
                              tmp_pu3 = (uint32_t *)tmp_pu3[10];
                            } while ((tmp_pu3 != (uint32_t *)0x0) &&
                                    (tmp_pu3 != (uint32_t *)(mapEntityData + 0x18038)));
                          }
LAB_000f18dc:
                          tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
                          if (GHIDRA_FIELD(mapEntityData, 98356, 4) == 0) {
                            G_Error("G_AllocMapEntityData: out of entities");
                            tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
                          }
                          GHIDRA_FIELD(mapEntityData, 98356, 4) = tmp_pu3[10];
                          tmp_b17 = ((uint)tmp_pu3 & 1) != 0;
                          local_6c = 0x30;
                          tmp_pu8 = tmp_pu3;
                          if (tmp_b17) {
                            *(uint8_t *)tmp_pu3 = 0;
                            tmp_pu8 = (uint32_t *)((int)tmp_pu3 + 1);
                            local_6c = 0x2f;
                          }
                          if (((uint)tmp_pu8 & 2) != 0) {
                            *(uint16_t *)tmp_pu8 = 0;
                            tmp_pu8 = (uint32_t *)((int)tmp_pu8 + 2);
                            local_6c = local_6c - 2;
                          }
                          tmp_u7 = 0;
                          do {
                            *(uint32_t *)((int)tmp_pu8 + tmp_u7) = 0;
                            *(uint32_t *)((int)tmp_pu8 + tmp_u7 + 4) = 0;
                            tmp_u7 = tmp_u7 + 8;
                          } while (tmp_u7 < (local_6c & 0xfffffff8));
                          tmp_pu8 = (uint32_t *)((int)tmp_pu8 + tmp_u7);
                          if ((local_6c & 4) != 0) {
                            *tmp_pu8 = 0;
                            tmp_pu8 = tmp_pu8 + 1;
                          }
                          if ((local_6c & 2) != 0) {
                            *(uint16_t *)tmp_pu8 = 0;
                            tmp_pu8 = (uint32_t *)((int)tmp_pu8 + 2);
                          }
                          if (tmp_b17) {
                            *(uint8_t *)tmp_pu8 = 0;
                          }
                          tmp_pu3[7] = 0xffffffff;
                          tmp_pu3[10] = GHIDRA_FIELD(mapEntityData, 98400, 4);
                          tmp_pu3[0xb] = 0x2d98a98;
                          *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 98400, 4) + 0x2c) = tmp_pu3;
                          GHIDRA_FIELD(mapEntityData, 98400, 4) = tmp_pu3;
                          tmp_pu3[9] = tmp_i4;
                          tmp_pu3[7] = *(uint32_t *)(g_entities + tmp_i14 + 0xac);
LAB_000f186c:
                          *tmp_pu3 = *(uint32_t *)(*(int *)(g_entities + tmp_i10 + 400) + 0x14);
                          tmp_pu3[1] = *(uint32_t *)(*(int *)(g_entities + tmp_i10 + 400) + 0x18);
                          tmp_pu3[2] = *(uint32_t *)(*(int *)(g_entities + tmp_i10 + 400) + 0x1c);
                          tmp_pu3[3] = (int)ROUND(*(float *)(*(int *)(g_entities + tmp_i10 + 400) +
                                                           0xb4));
                          tmp_pu3[4] = tmp_i4;
                          tmp_i11 = g_unk_00abe908;
                          *(uint8_t *)(tmp_pu3 + 5) = 2;
                          tmp_pu3[6] = tmp_i11;
                        }
                      }
                    }
                  }
                }
                tmp_i9 = tmp_i9 + 1;
                tmp_i11 = *(int *)(g_entities + tmp_i14 + 400);
                local_78 = g_unk_00abe93c;
              } while (tmp_i9 < g_unk_00abe93c);
            }
LAB_000f1219:
            tmp_i9 = *(int *)(tmp_i11 + 0xbc8);
joined_r0x000f1436:
            if (tmp_i9 != 4) goto LAB_000f0fd5;
          }
          tmp_i9 = g_unk_00abe93c;
          if ((0 < *(int *)(g_entities + tmp_i14 + 0x2c8)) &&
             (((*(byte *)(tmp_i11 + 0x6a) & 4) != 0 &&
              (G_SetupFrustum_ForBinoculars(tmp_pu1), tmp_i9 = g_unk_00abe93c, 0 < LandmineEntities))))
          {
            tmp_i10 = 0;
            tmp_i4 = (tmp_i14 >> 9) * -0x55555555;
            tmp_i11 = LandmineEntities;
            do {
              tmp_pu13 = (uint8_t *)(&g_unk_0087ca04)[tmp_i10];
              if ((tmp_pu1 != tmp_pu13) && (*(int *)(tmp_pu13 + 0x194) != 0)) {
                tmp_i9 = *(int *)(*(int *)(g_entities + tmp_i14 + 400) + 3000);
                if ((tmp_i9 != 3) &&
                   ((((*(byte *)(*(int *)(g_entities + tmp_i14 + 400) + 0xd) & 0x40) == 0 &&
                     (3 < *(int *)(tmp_pu13 + 0x108) - 4U)) &&
                    (tmp_i9 != *(int *)(tmp_pu13 + 0x108) % 4)))) {
                  tmp_i9 = G_VisibleFromBinoculars(tmp_pu1,tmp_pu13,tmp_pu13 + 0x168);
                  if (tmp_i9 == 0) {
                    *(uint32_t *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) = 0;
                    tmp_i11 = LandmineEntities;
                  }
                  else {
                    G_UpdateTeamMapData_LandMine(tmp_pu13,tmp_b15,tmp_b16);
                    tmp_i9 = g_unk_00abe908;
                    tmp_i11 = LandmineEntities;
                    if (*(int *)(tmp_pu13 + 0x108) % 4 == 1) {
                      if (*(int *)(tmp_pu13 + 0xa8) == 0) {
                        *(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x1048) = g_unk_00abe908;
                        *(uint8_t **)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) = tmp_pu13;
                        *(int *)(tmp_pu13 + 0xf4) = tmp_i4 + 1;
                        *(int *)(tmp_pu13 + 0x378) = tmp_i9;
                        tmp_pi12 = (int *)(*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) +
                                         0x39c);
                        *tmp_pi12 = *tmp_pi12 + 0x32;
                        tmp_i11 = LandmineEntities;
                        if (0xf9 < *(int *)(*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) +
                                           0x39c)) {
                          *(uint32_t *)
                           (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0x39c) = 0xfa;
                          *(uint32_t *)
                           (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0xa8) = 1;
                          tmp_i9 = G_LandmineTriggered(*(uint32_t *)
                                                       (*(int *)(g_entities + tmp_i14 + 400) + 0x104c
                                                       ));
                          if (tmp_i9 == 0) {
                            tmp_i9 = *(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c);
                            tmp_i11 = rand();
                            *(int *)(tmp_i9 + 0xb0) = tmp_i11 % 0x14;
                            *(uint32_t *)
                             (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0x14c) =
                                 0x20000000;
                            trap_LinkEntity(*(uint32_t *)
                                             (*(int *)(g_entities + tmp_i14 + 400) + 0x104c));
                          }
                          tmp_i9 = G_PopupMessage(2);
                          *(uint32_t *)(tmp_i9 + 0x5c) =
                               *(uint32_t *)
                                (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0x168);
                          *(uint32_t *)(tmp_i9 + 0x60) =
                               *(uint32_t *)
                                (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0x16c);
                          tmp_u2 = *(uint32_t *)
                                   (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0x170);
                          *(uint32_t *)(tmp_i9 + 0x110) = 1;
                          *(uint32_t *)(tmp_i9 + 100) = tmp_u2;
                          goto LAB_000f1657;
                        }
                      }
                    }
                    else if ((*(int *)(tmp_pu13 + 0x108) % 4 == 2) && (*(int *)(tmp_pu13 + 0xa8) == 0)
                            ) {
                      *(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x1048) = g_unk_00abe908;
                      *(uint8_t **)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) = tmp_pu13;
                      *(int *)(tmp_pu13 + 0xf4) = tmp_i4 + 1;
                      *(int *)(tmp_pu13 + 0x378) = tmp_i9;
                      tmp_pi12 = (int *)(*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) +
                                       0x39c);
                      *tmp_pi12 = *tmp_pi12 + 0x32;
                      tmp_i11 = LandmineEntities;
                      if (0xf9 < *(int *)(*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) +
                                         0x39c)) {
                        *(uint32_t *)
                         (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0x39c) = 0xfa;
                        *(uint32_t *)
                         (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0xa8) = 1;
                        tmp_i9 = G_LandmineTriggered(*(uint32_t *)
                                                     (*(int *)(g_entities + tmp_i14 + 400) + 0x104c))
                        ;
                        if (tmp_i9 == 0) {
                          tmp_i9 = *(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c);
                          tmp_i11 = rand();
                          *(int *)(tmp_i9 + 0xb0) = tmp_i11 % 0x14;
                          *(uint32_t *)
                           (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0x14c) =
                               0x20000000;
                          trap_LinkEntity(*(uint32_t *)
                                           (*(int *)(g_entities + tmp_i14 + 400) + 0x104c));
                        }
                        tmp_i9 = G_PopupMessage(2);
                        *(uint32_t *)(tmp_i9 + 0x5c) =
                             *(uint32_t *)
                              (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0x168);
                        *(uint32_t *)(tmp_i9 + 0x60) =
                             *(uint32_t *)
                              (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0x16c);
                        tmp_u2 = *(uint32_t *)
                                 (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0x104c) + 0x170);
                        *(uint32_t *)(tmp_i9 + 0x110) = 2;
                        *(uint32_t *)(tmp_i9 + 100) = tmp_u2;
LAB_000f1657:
                        *(int *)(tmp_i9 + 0x114) = tmp_i4;
                        trap_SendServerCommand(tmp_i4,"cp \"Landmine Revealed\n\"");
                        if (*(int *)(*(int *)(g_entities + tmp_i14 + 400) + 0xbc8) == 4) {
                          tmp_pi12 = (int *)(*(int *)(g_entities + tmp_i14 + 400) + 0xba0);
                          *tmp_pi12 = *tmp_pi12 + 1;
                        }
                        AddScore(tmp_pu1,1);
                        G_AddSkillPoints(tmp_pu1,6,0x40400000);
                        tmp_i11 = LandmineEntities;
                        if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
                          G_DebugAddSkillPoints(tmp_pu1,6,0x40400000,"spotting a landmine");
                          tmp_i11 = LandmineEntities;
                        }
                      }
                    }
                  }
                }
              }
              tmp_i10 = tmp_i10 + 1;
              tmp_i9 = g_unk_00abe93c;
            } while (tmp_i10 < tmp_i11);
          }
        }
        else {
          if (*(int *)(tmp_i11 + 0xbc8) != 4) goto LAB_000f0fc9;
          tmp_i9 = g_unk_00abe93c;
          if (0 < *(int *)(g_entities + tmp_i14 + 0x2c8)) {
            tmp_b15 = *(int *)(tmp_i11 + 3000) == 2;
            tmp_b16 = *(int *)(tmp_i11 + 3000) == 1;
            G_SetupFrustum(tmp_pu1);
            if (0 < g_unk_00abe93c) {
              tmp_i11 = 0;
              tmp_i9 = g_unk_00abe93c;
              do {
                while( true ) {
                  tmp_i10 = (&g_unk_00abe944)[tmp_i11] * 0x600;
                  tmp_pu13 = g_entities + tmp_i10;
                  if (((tmp_pu1 != tmp_pu13) && (*(int *)(g_entities + tmp_i10 + 0x194) != 0)) &&
                     (*(int *)(g_entities + tmp_i10 + 4) == 1)) break;
LAB_000f1320:
                  tmp_i11 = tmp_i11 + 1;
                  if (tmp_i9 <= tmp_i11) goto LAB_000f1429;
                }
                tmp_i4 = *(int *)(g_entities + tmp_i10 + 400);
                local_40 = *(uint32_t *)(tmp_i4 + 0x14);
                local_3c = *(uint32_t *)(tmp_i4 + 0x18);
                local_2c = *(float *)(tmp_i4 + 0x1c);
                local_38 = *(float *)(tmp_i4 + 0x3e4) + local_2c;
                local_28 = *(uint32_t *)(tmp_i4 + 0x14);
                local_24 = *(uint32_t *)(tmp_i4 + 0x18);
                local_20 = *(float *)(tmp_i4 + 0x1c) + *(float *)(tmp_i4 + 0x3f0);
                local_34 = local_40;
                local_30 = local_3c;
                if (*(int *)(g_entities + tmp_i10 + 0x2c8) < 1) goto LAB_000f1320;
                tmp_i9 = G_VisibleFromBinoculars(tmp_pu1,tmp_pu13,&local_40);
                if (((tmp_i9 != 0) ||
                    (tmp_i9 = G_VisibleFromBinoculars(tmp_pu1,tmp_pu13,&local_34), tmp_i9 != 0)) ||
                   (tmp_i9 = G_VisibleFromBinoculars(tmp_pu1,tmp_pu13,&local_28), tmp_i9 != 0)) {
                  G_UpdateTeamMapData_Player(tmp_pu13,tmp_b15,tmp_b16);
                  tmp_i9 = g_unk_00abe93c;
                  goto LAB_000f1320;
                }
                tmp_i11 = tmp_i11 + 1;
                tmp_i9 = g_unk_00abe93c;
              } while (tmp_i11 < g_unk_00abe93c);
            }
LAB_000f1429:
            tmp_i11 = *(int *)(g_entities + tmp_i14 + 400);
            tmp_i9 = *(int *)(tmp_i11 + 0xbc8);
            goto joined_r0x000f1436;
          }
        }
      }
LAB_000f100a:
      local_7c = (uint32_t *)((int)local_7c + 1);
    } while ((int)local_7c < tmp_i9);
  }
  return;
}

void G_ConvertQtime(int *param_1)
{
  tm local_38;
  
  local_38.tm_sec = *param_1;
  local_38.tm_min = param_1[1];
  local_38.tm_hour = param_1[2];
  local_38.tm_mday = param_1[3];
  local_38.tm_mon = param_1[4];
  local_38.tm_year = param_1[5];
  local_38.tm_wday = param_1[6];
  local_38.tm_yday = param_1[7];
  local_38.tm_isdst = param_1[8];
  mktime(&local_38);
  return;
}

void G_GetCurrentTime(void)
{
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  tm local_38;
  uint32_t uStack_8;
  
  uStack_8 = 0xf1f26;
  trap_RealTime(&local_5c);
  local_38.tm_sec = local_5c;
  local_38.tm_min = local_58;
  local_38.tm_hour = local_54;
  local_38.tm_mday = local_50;
  local_38.tm_mon = local_4c;
  local_38.tm_year = local_48;
  local_38.tm_wday = local_44;
  local_38.tm_yday = local_40;
  local_38.tm_isdst = local_3c;
  mktime(&local_38);
  return;
}

bool G_IsAllowedHeal(int param_1)
{
  if (((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) && (0 < *(int *)(param_1 + 0x2c8))) {
    return *(int *)(param_1 + 0x2c8) < *(int *)(*(int *)(param_1 + 400) + 0xe0);
  }
  return false;
}

void G_SetConfigStringValue(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  uint8_t local_40c [1024];
  
  trap_GetConfigstring(param_1,local_40c,0x400);
  Info_SetValueForKey(local_40c,param_2,param_3);
  trap_SetConfigstring(param_1,local_40c);
  return;
}

bool G_LoadCampaignsFromFile(uint32_t param_1)
{
  char tmp_c1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  char *tmp_pc6;
  uint32_t *tmp_pu7;
  int tmp_i8;
  uint tmp_u9;
  char *tmp_pc10;
  bool tmp_b11;
  byte tmp_b12;
  char local_4b4 [128];
  uint8_t local_434 [16];
  char local_424;
  char local_423 [1039];
  uint32_t uStack_14;
  
  tmp_b12 = 0;
  uStack_14 = 0xf5839;
  tmp_i2 = trap_PC_LoadSource(param_1);
  if (tmp_i2 == 0) {
    tmp_u4 = va("^1file not found: %s\n",param_1);
    G_Printf(tmp_u4);
    return false;
  }
  tmp_i3 = trap_PC_ReadToken(tmp_i2,local_434);
  if ((tmp_i3 != 0) && (tmp_b11 = false, local_424 == '{')) {
LAB_000f5890:
    do {
      tmp_i3 = trap_PC_ReadToken(tmp_i2,local_434);
      if (tmp_i3 == 0) {
        return tmp_b11;
      }
      if (local_424 != '}') {
        tmp_pc6 = &local_424;
        tmp_i3 = Q_stricmp(tmp_pc6,"name");
        if (((tmp_i3 == 0) || (tmp_i3 = Q_stricmp(tmp_pc6,"description"), tmp_i3 == 0)) ||
           (tmp_i3 = Q_stricmp(tmp_pc6,"image"), tmp_i3 == 0)) {
          tmp_i3 = PC_String_Parse(tmp_i2);
          if (tmp_i3 != 0) goto LAB_000f5890;
        }
        else {
          tmp_i3 = Q_stricmp(tmp_pc6,"shortname");
          if ((tmp_i3 == 0) || (tmp_i3 = Q_stricmp(tmp_pc6,"next"), tmp_i3 == 0)) {
            tmp_i3 = PC_String_Parse(tmp_i2);
            if (tmp_i3 != 0) {
              Q_strncpyz(g_unk_02a9848c * 0x494 + 0x2cee4e8,tmp_i3,0x100);
              goto LAB_000f5890;
            }
          }
          else {
            tmp_i3 = Q_stricmp(tmp_pc6,"type");
            if (tmp_i3 != 0) {
              tmp_i3 = Q_stricmp(tmp_pc6,"maps");
              if (tmp_i3 == 0) {
                tmp_i3 = trap_PC_ReadToken(tmp_i2,local_434);
                if (tmp_i3 == 0) {
                  G_Printf("^1unexpected end of file inside: %s\n",param_1);
                  goto LAB_000f5971;
                }
                if (local_424 != '\0') {
                  tmp_i3 = g_unk_02a9848c;
                  tmp_c1 = local_424;
LAB_000f5c26:
                  tmp_pc5 = local_4b4;
                  tmp_pc10 = local_4b4;
                  if (tmp_c1 == ';') {
LAB_000f5cd0:
                    tmp_pc6 = tmp_pc6 + 1;
                  }
                  else {
                    do {
                      tmp_pc10 = tmp_pc5 + 1;
                      tmp_pc6 = tmp_pc6 + 1;
                      *tmp_pc5 = tmp_c1;
                      tmp_c1 = *tmp_pc6;
                      if (tmp_c1 == ';') break;
                      tmp_pc5 = tmp_pc10;
                    } while (tmp_c1 != '\0');
                    if (tmp_c1 != '\0') goto LAB_000f5cd0;
                  }
                  *tmp_pc10 = '\0';
                  if ((tmp_b11 == false) && (GHIDRA_FIELD(g_gametype, 12, 4) == 4)) {
                    tmp_i3 = Q_stricmp(tmp_i3 * 0x494 + 0x2cee4e8,0x2e515d0);
                    if ((tmp_i3 == 0) &&
                       (tmp_i8 = Q_stricmp(local_4b4,&g_unk_00abe8c0), tmp_i3 = g_unk_02a9848c, tmp_i8 == 0
                       )) {
                      g_unk_02a98494 = (uint)(GHIDRA_FIELD(g_currentCampaignMap, 12, 4) == 0);
                      g_unk_02a98490 = g_unk_02a9848c;
                      tmp_b11 = GHIDRA_FIELD(g_currentCampaignMap, 12, 4) ==
                               *(int *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x280);
                      if (tmp_b11) {
                        *(uint32_t *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x284) =
                             GHIDRA_FIELD(g_currentCampaignMap, 12, 4);
                      }
                    }
                    else {
                      tmp_b11 = false;
                      tmp_i3 = g_unk_02a9848c;
                    }
                  }
                  tmp_i3 = tmp_i3 * 0x494;
                  if (*(int *)(g_campaigns + tmp_i3 + 0x280) < 10) {
                    Q_strncpyz(g_campaigns + *(int *)(g_campaigns + tmp_i3 + 0x280) * 0x40 + tmp_i3,
                               local_4b4,0x40);
                    tmp_i3 = g_unk_02a9848c;
                    *(int *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x280) =
                         *(int *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x280) + 1;
                    tmp_c1 = *tmp_pc6;
                    if (tmp_c1 == '\0') goto LAB_000f5890;
                    goto LAB_000f5c26;
                  }
                  G_Printf("^1Error: Campaign %s (%s) has too many maps\n",tmp_i3 + 0x2cee4e8,param_1
                          );
                  tmp_pu7 = (uint32_t *)(g_campaigns + g_unk_02a9848c * 0x494);
                  tmp_u9 = 0x494;
                  if (((uint)tmp_pu7 & 4) != 0) {
                    *tmp_pu7 = 0;
                    tmp_pu7 = (uint32_t *)(g_campaigns + g_unk_02a9848c * 0x494 + 4);
                    tmp_u9 = 0x490;
                  }
                  g_unk_02a9848c = g_unk_02a9848c + -1;
                  for (tmp_u9 = tmp_u9 >> 2; tmp_u9 != 0; tmp_u9 = tmp_u9 - 1) {
                    *tmp_pu7 = 0;
                    tmp_pu7 = tmp_pu7 + (uint)tmp_b12 * -2 + 1;
                  }
                }
              }
              goto LAB_000f5890;
            }
            tmp_i3 = trap_PC_ReadToken(tmp_i2,local_434);
            if (tmp_i3 != 0) {
              tmp_pc5 = strstr(tmp_pc6,"wolfsp");
              if (tmp_pc5 != (char *)0x0) {
                *(uint *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x488) =
                     *(uint *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x488) | 1;
              }
              tmp_pc5 = strstr(tmp_pc6,"wolfcoop");
              if (tmp_pc5 != (char *)0x0) {
                *(uint *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x488) =
                     *(uint *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x488) | 2;
              }
              tmp_pc5 = strstr(tmp_pc6,"wolfmp");
              if (tmp_pc5 != (char *)0x0) {
                *(uint *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x488) =
                     *(uint *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x488) | 4;
              }
              tmp_pc5 = strstr(tmp_pc6,"wolfsw");
              if (tmp_pc5 != (char *)0x0) {
                *(uint *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x488) =
                     *(uint *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x488) | 8;
              }
              tmp_pc6 = strstr(tmp_pc6,"wolflms");
              if (tmp_pc6 != (char *)0x0) {
                *(uint *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x488) =
                     *(uint *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x488) | 0x20;
              }
              goto LAB_000f5890;
            }
          }
        }
        tmp_u4 = va("^1unexpected end of file inside: %s\n",param_1);
        goto LAB_000f5969;
      }
      g_unk_02a9848c = g_unk_02a9848c + 1;
      if (0x1ff < g_unk_02a9848c) {
        return tmp_b11;
      }
      tmp_i3 = trap_PC_ReadToken(tmp_i2,local_434);
      if (tmp_i3 == 0) {
        trap_PC_FreeSource(tmp_i2);
        return tmp_b11;
      }
    } while (local_424 == '{');
    tmp_u4 = va("^1unexpected token \'%s\' inside: %s\n",&local_424,param_1);
LAB_000f5969:
    G_Printf(tmp_u4);
  }
LAB_000f5971:
  trap_PC_FreeSource(tmp_i2);
  return false;
}

int G_FindConfigstringIndex_part_0(char *param_1,int param_2,int param_3,int param_4)
{
  int tmp_i1;
  int tmp_i2;
  char local_41c [1036];
  
  if (param_3 < 2) {
    if (param_4 == 0) {
      return 0;
    }
    if (param_3 != 1) {
      param_3 = 1;
      tmp_i1 = param_2 + 1;
      goto LAB_000f5ee8;
    }
  }
  else {
    tmp_i2 = 1;
    do {
      tmp_i1 = tmp_i2 + param_2;
      trap_GetConfigstring(tmp_i1,local_41c,0x400);
      if (local_41c[0] == '\0') {
        param_3 = tmp_i2;
        if (param_4 == 0) {
          return 0;
        }
        goto LAB_000f5ee8;
      }
      tmp_i1 = strcmp(local_41c,param_1);
      if (tmp_i1 == 0) {
        return tmp_i2;
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 != param_3);
    if (param_4 == 0) {
      return 0;
    }
  }
  G_Error("G_FindConfigstringIndex: overflow");
  tmp_i1 = param_2 + param_3;
LAB_000f5ee8:
  trap_SetConfigstring(tmp_i1,param_1);
  return param_3;
}

int G_FindConfigstringIndex_part_0_constprop_4(char *param_1)
{
  int tmp_i1;
  int tmp_i2;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xf5f5e;
  tmp_i2 = 1;
  do {
    tmp_i1 = tmp_i2 + 0x309;
    trap_GetConfigstring(tmp_i1,local_41c,0x400);
    if (local_41c[0] == '\0') goto LAB_000f5fcf;
    tmp_i1 = strcmp(local_41c,param_1);
    if (tmp_i1 == 0) {
      return tmp_i2;
    }
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 0x40);
  tmp_i1 = 0x349;
  G_Error("G_FindConfigstringIndex: overflow");
LAB_000f5fcf:
  trap_SetConfigstring(tmp_i1,param_1);
  return tmp_i2;
}

int G_FindConfigstringIndex_part_0_constprop_5(char *param_1)
{
  int tmp_i1;
  int tmp_i2;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xf5ffe;
  tmp_i2 = 1;
  do {
    tmp_i1 = tmp_i2 + 0x350;
    trap_GetConfigstring(tmp_i1,local_41c,0x400);
    if (local_41c[0] == '\0') goto LAB_000f606f;
    tmp_i1 = strcmp(local_41c,param_1);
    if (tmp_i1 == 0) {
      return tmp_i2;
    }
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 0x20);
  tmp_i1 = 0x370;
  G_Error("G_FindConfigstringIndex: overflow");
LAB_000f606f:
  trap_SetConfigstring(tmp_i1,param_1);
  return tmp_i2;
}

void G_InitRemappedShaders(void)
{
  uint32_t *tmp_pu1;
  uint32_t *tmp_pu2;
  
  tmp_pu1 = (uint32_t *)0x2e3f120;
  do {
    Q_strncpyz(tmp_pu1,&g_unk_0026ea14,0x40);
    tmp_pu2 = tmp_pu1 + 0x21;
    Q_strncpyz(tmp_pu1 + -0x10,&g_unk_0026ea14,0x40);
    tmp_pu1[0x10] = 0;
    tmp_pu1 = tmp_pu2;
  } while (tmp_pu2 != &OldHandler);
  remapCount = 0;
  return;
}

G_FindConfigstringIndex(char *param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  uint32_t tmp_u1;
  
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    param_2 = param_4;
    tmp_u1 = G_FindConfigstringIndex_part_0();
    return tmp_u1;
  }
  return 0;
}

void G_RemoveConfigstringIndex(char *param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  char local_41c [1036];
  
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    tmp_i3 = 1;
    if (1 < param_3) {
      do {
        tmp_i2 = param_2 + tmp_i3;
        trap_GetConfigstring(tmp_i2,local_41c,0x400);
        if (local_41c[0] == '\0') {
          return;
        }
        tmp_i1 = strcmp(local_41c,param_1);
        if (tmp_i1 == 0) {
          trap_SetConfigstring(tmp_i2,&g_unk_0026ea14);
          if (param_3 + -1 <= tmp_i3 + 1) {
            return;
          }
          tmp_i3 = tmp_i3 + 1 + param_2;
          do {
            trap_GetConfigstring(tmp_i3,local_41c,0x400);
            tmp_i1 = tmp_i3 + 1;
            trap_SetConfigstring(tmp_i3,&g_unk_0026ea14);
            trap_SetConfigstring(tmp_i2,local_41c);
            tmp_i3 = tmp_i1;
          } while (tmp_i1 != param_2 + -1 + param_3);
          return;
        }
        tmp_i3 = tmp_i3 + 1;
      } while (tmp_i3 != param_3);
    }
  }
  return;
}

void G_ModelIndex(uint32_t param_1)
{
  nitrox_CSIndex(param_1,0,0x100,1);
  return;
}

int G_SoundIndex(uint32_t param_1)
{
  int tmp_i1;
  
  tmp_i1 = nitrox_CSIndex(param_1,0x100,0x100,1);
  return tmp_i1 + 0x54;
}

void G_SkinIndex(uint32_t param_1)
{
  nitrox_CSIndex(param_1,0x221,0x40,1);
  return;
}

void G_ShaderIndex(uint32_t param_1)
{
  nitrox_CSIndex(param_1,0x200,0x20,1);
  return;
}

uint32_t G_StringIndex(char *param_1)
{
  uint32_t tmp_u1;
  
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    tmp_u1 = G_FindConfigstringIndex_part_0_constprop_5();
    return tmp_u1;
  }
  return 0;
}

void G_TeamCommand(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i4 = 0;
  tmp_i1 = g_unk_00abe900;
  tmp_i2 = 0;
  if (0 < g_unk_00abe900) {
    do {
      while ((*(int *)(level + tmp_i4 + 0x5ac) != 2 || (*(int *)(level + tmp_i4 + 3000) != param_1)))
      {
        tmp_i2 = tmp_i2 + 1;
        tmp_i4 = tmp_i4 + 0x54dc;
        if (tmp_i1 <= tmp_i2) {
          return;
        }
      }
      tmp_i4 = tmp_i4 + 0x54dc;
      tmp_i3 = tmp_i2 + 1;
      trap_SendServerCommand(tmp_i2,param_2);
      tmp_i1 = g_unk_00abe900;
      tmp_i2 = tmp_i3;
    } while (tmp_i3 < g_unk_00abe900);
  }
  return;
}

uint8_t * G_Find(int param_1,int param_2,uint32_t param_3)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i3 = g_unk_00abe8a8 * 0x600;
  tmp_pu1 = (uint8_t *)(param_1 + 0x600);
  if (param_1 == 0) {
    tmp_pu1 = g_entities;
  }
  while( true ) {
    if (g_entities + tmp_i3 <= tmp_pu1) {
      return (uint8_t *)0x0;
    }
    if (((*(int *)(tmp_pu1 + 0x194) != 0) && (*(int *)(tmp_pu1 + param_2) != 0)) &&
       (tmp_i2 = Q_stricmp(*(int *)(tmp_pu1 + param_2),param_3), tmp_i2 == 0)) break;
    tmp_pu1 = tmp_pu1 + 0x600;
  }
  return tmp_pu1;
}

uint8_t * G_FindByTargetnameFast(int param_1,uint32_t param_2,int param_3)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i3 = g_unk_00abe8a8 * 0x600;
  tmp_pu1 = (uint8_t *)(param_1 + 0x600);
  if (param_1 == 0) {
    tmp_pu1 = g_entities;
  }
  while( true ) {
    if (g_entities + tmp_i3 <= tmp_pu1) {
      return (uint8_t *)0x0;
    }
    if ((((*(int *)(tmp_pu1 + 0x194) != 0) && (*(int *)(tmp_pu1 + 600) != 0)) &&
        (*(int *)(tmp_pu1 + 0x25c) == param_3)) &&
       (tmp_i2 = Q_stricmp(*(int *)(tmp_pu1 + 600),param_2), tmp_i2 == 0)) break;
    tmp_pu1 = tmp_pu1 + 0x600;
  }
  return tmp_pu1;
}

int G_PickTarget(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  uint8_t *tmp_pu4;
  bool tmp_b5;
  int local_a0 [36];
  
  if (param_1 == 0) {
    tmp_i1 = 0;
  }
  else {
    tmp_i1 = BG_StringHashValue(param_1);
    local_a0[0] = 0;
    tmp_pu4 = g_entities + g_unk_00abe8a8 * 0x600;
    for (tmp_pu3 = g_entities; tmp_pu3 < tmp_pu4; tmp_pu3 = tmp_pu3 + 0x600) {
      if (((*(int *)(tmp_pu3 + 0x194) != 0) && (*(int *)(tmp_pu3 + 600) != 0)) &&
         (tmp_i1 == *(int *)(tmp_pu3 + 0x25c))) {
        tmp_i2 = Q_stricmp(*(int *)(tmp_pu3 + 600),param_1);
        if (tmp_i2 == 0) {
          local_a0[0] = local_a0[0] + 1;
          tmp_b5 = local_a0[0] == 0x20;
          local_a0[local_a0[0]] = (int)tmp_pu3;
          if (tmp_b5) {
            tmp_i1 = 0x20;
            goto LAB_000f689a;
          }
          tmp_pu4 = g_entities + g_unk_00abe8a8 * 0x600;
        }
      }
    }
    tmp_i1 = local_a0[0];
    if (local_a0[0] == 0) {
      G_Printf("G_PickTarget: target %s not found\n",param_1);
      return 0;
    }
LAB_000f689a:
    tmp_i2 = rand();
    tmp_i1 = local_a0[tmp_i2 % tmp_i1 + 1];
  }
  return tmp_i1;
}

bool G_AllowTeamsAllowed(int param_1,int param_2)
{
  uint tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  bool tmp_b4;
  
  tmp_u1 = *(uint *)(param_1 + 0x488);
  if (((param_2 != 0) && (tmp_u1 != 0)) && (tmp_i2 = *(int *)(param_2 + 400), tmp_i2 != 0)) {
    tmp_u3 = *(uint *)(tmp_i2 + 3000);
    tmp_b4 = true;
    if (((tmp_u3 != 3) && ((tmp_u3 & tmp_u1) == 0)) &&
       ((tmp_b4 = false, (tmp_u1 & 4) != 0 && (tmp_b4 = false, *(int *)(tmp_i2 + 0x16c) != 0)))) {
      if (tmp_u3 == 1) {
        tmp_u3 = 2;
      }
      else {
        if (tmp_u3 != 2) {
          return false;
        }
        tmp_u3 = 1;
      }
      tmp_b4 = (tmp_u3 & tmp_u1) != 0;
    }
    return tmp_b4;
  }
  return true;
}

void G_UseEntity(int param_1,uint32_t param_2,int param_3)
{
  uint tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  uint tmp_u4;
  
  tmp_u1 = *(uint *)(param_1 + 0x488);
  if ((((param_3 != 0) && (tmp_u1 != 0)) && (tmp_i2 = *(int *)(param_3 + 400), tmp_i2 != 0)) &&
     ((tmp_u3 = *(uint *)(tmp_i2 + 3000), tmp_u3 != 3 && ((tmp_u3 & tmp_u1) == 0)))) {
    if ((tmp_u1 & 4) == 0) {
      return;
    }
    if (*(int *)(tmp_i2 + 0x16c) == 0) {
      return;
    }
    if (tmp_u3 == 1) {
      tmp_u4 = 2;
    }
    else {
      tmp_u4 = 1;
      if (tmp_u3 != 2) {
        return;
      }
    }
    if ((tmp_u4 & tmp_u1) == 0) {
      return;
    }
  }
  (**(void **)(param_1 + 0x2b4))(param_1,param_2,param_3);
  return;
}

void G_UseTargets(uint8_t *param_1,int param_2)
{
  uint tmp_u1;
  uint tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint tmp_u5;
  uint8_t *tmp_pu6;
  uint8_t *tmp_pu7;
  uint32_t local_24;
  
  if ((param_1 != (uint8_t *)0x0) && (*(int *)(param_1 + 0x254) != 0)) {
    tmp_i3 = BG_StringHashValue(*(int *)(param_1 + 0x254));
    local_24 = *(uint32_t *)(param_1 + 0x254);
    tmp_pu6 = g_entities + g_unk_00abe8a8 * 0x600;
    for (tmp_pu7 = g_entities; tmp_pu7 < tmp_pu6; tmp_pu7 = tmp_pu7 + 0x600) {
      if ((((*(int *)(tmp_pu7 + 0x194) != 0) && (*(int *)(tmp_pu7 + 600) != 0)) &&
          (tmp_i3 == *(int *)(tmp_pu7 + 0x25c))) &&
         (tmp_i4 = Q_stricmp(*(int *)(tmp_pu7 + 600),local_24), tmp_i4 == 0)) {
        if (param_1 == tmp_pu7) {
          G_Printf("WARNING: Entity used itself.\n");
          tmp_i4 = *(int *)(param_1 + 0x194);
        }
        else {
          if (*(void **)(tmp_pu7 + 0x2b4) != (void *)0x0) {
            *(uint *)(tmp_pu7 + 0x1b0) =
                 *(uint *)(tmp_pu7 + 0x1b0) | *(uint *)(param_1 + 0x1b0) & 0x40;
            if (param_2 == 0) {
LAB_000f6b80:
              (**(void **)(tmp_pu7 + 0x2b4))(tmp_pu7,param_1,param_2);
            }
            else if ((*(int *)(tmp_pu7 + 0x5c0) == 0x3bf8a) || (*(int *)(tmp_pu7 + 0x5c0) == 0x1cce6))
            {
              G_TryDoor(tmp_pu7,param_1,param_2);
            }
            else {
              tmp_u1 = *(uint *)(tmp_pu7 + 0x488);
              if (((tmp_u1 == 0) || (tmp_i4 = *(int *)(param_2 + 400), tmp_i4 == 0)) ||
                 ((tmp_u2 = *(uint *)(tmp_i4 + 3000), tmp_u2 == 3 || ((tmp_u2 & tmp_u1) != 0))))
              goto LAB_000f6b80;
              if (((tmp_u1 & 4) != 0) && (*(int *)(tmp_i4 + 0x16c) != 0)) {
                if (tmp_u2 == 1) {
                  tmp_u5 = 2;
                }
                else {
                  tmp_u5 = 1;
                  if (tmp_u2 != 2) goto LAB_000f6b95;
                }
                if ((tmp_u5 & tmp_u1) != 0) goto LAB_000f6b80;
              }
            }
          }
LAB_000f6b95:
          tmp_i4 = *(int *)(param_1 + 0x194);
        }
        if (tmp_i4 == 0) {
          G_Printf("entity was removed while using targets\n");
          return;
        }
        local_24 = *(uint32_t *)(param_1 + 0x254);
        tmp_pu6 = g_entities + g_unk_00abe8a8 * 0x600;
      }
    }
  }
  return;
}

void G_SetMovedir(uint32_t *param_1,uint32_t *param_2)
{
  int tmp_i1;
  
  tmp_i1 = VectorCompare(param_1,VEC_UP_12953);
  if (tmp_i1 == 0) {
    tmp_i1 = VectorCompare(param_1,VEC_DOWN_12955);
    if (tmp_i1 == 0) {
      AngleVectors(param_1,param_2,0,0);
    }
    else {
      *param_2 = 0;
      param_2[1] = 0;
      param_2[2] = 0xbf800000;
    }
  }
  else {
    *param_2 = 0;
    param_2[1] = 0;
    param_2[2] = 0x3f800000;
  }
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  return;
}

void G_InitGentity(int *param_1)
{
  param_1[0x65] = 1;
  param_1[0x69] = (int)"noclass";
  param_1[0x16b] = param_1[0x16b] + 1;
  param_1[0xa7] = 0;
  param_1[0x179] = 0;
  *param_1 = ((int)(param_1 + -0x24f928) >> 9) * -0x55555555;
  param_1[0x60] = 0x3ff;
  param_1[0xa8] = 0;
  param_1[0xf0] = -1;
  param_1[0x123] = g_unk_00abe908;
  Bot_Queue_EntityCreated(param_1);
  return;
}

int G_GentitiesAvailable(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i1 = 0x400 - g_unk_00abe8a8;
  if (0x40 < g_unk_00abe8a8) {
    tmp_i2 = 0x9564a0;
    tmp_i3 = 0x40;
    do {
      if (*(int *)(tmp_i2 + 0x194) == 0) {
        tmp_i1 = tmp_i1 + 1;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_i2 = tmp_i2 + 0x600;
    } while (tmp_i3 != g_unk_00abe8a8);
  }
  return tmp_i1;
}

int * G_Spawn(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  int *tmp_pi5;
  
  tmp_i3 = g_unk_00abe908;
  if (g_unk_00abe8a8 < 0x41) {
    tmp_pi5 = (int *)(g_entities + 0x18000);
  }
  else {
    tmp_i2 = 0x40;
    tmp_pi5 = (int *)(g_entities + 0x18000);
    do {
      if ((tmp_pi5[0x65] == 0) &&
         ((tmp_pi5[0x6f] <= g_unk_00abe918 + 2000 || (999 < g_unk_00abe908 - tmp_pi5[0x6f]))))
      goto LAB_000f70d0;
      tmp_i2 = tmp_i2 + 1;
      tmp_pi5 = tmp_pi5 + 0x180;
    } while (tmp_i2 != g_unk_00abe8a8);
    if (g_unk_00abe8a8 == 0x3fe) {
      tmp_i2 = 0x40;
      tmp_pi5 = (int *)(g_entities + 0x18000);
      do {
        if (tmp_pi5[0x65] == 0) {
LAB_000f70d0:
          tmp_pi5[0x69] = (int)"noclass";
          tmp_pi5[0x16b] = tmp_pi5[0x16b] + 1;
          tmp_pi5[0x65] = 1;
          tmp_pi5[0x60] = 0x3ff;
          tmp_pi5[0xa7] = 0;
          *tmp_pi5 = ((int)(tmp_pi5 + -0x24f928) >> 9) * -0x55555555;
          tmp_pi5[0xa8] = 0;
          tmp_pi5[0x179] = 0;
          tmp_pi5[0xf0] = -1;
          tmp_pi5[0x123] = tmp_i3;
          Bot_Queue_EntityCreated(tmp_pi5);
          return tmp_pi5;
        }
        tmp_i2 = tmp_i2 + 1;
        tmp_pi5 = tmp_pi5 + 0x180;
      } while (tmp_i2 != 0x3fe);
      tmp_pu4 = (uint32_t *)(g_entities + 0x1a4);
      tmp_i3 = 0;
      do {
        tmp_u1 = *tmp_pu4;
        tmp_pu4 = tmp_pu4 + 0x180;
        tmp_i2 = tmp_i3 + 1;
        G_Printf("%4i: %s\n",tmp_i3,tmp_u1);
        tmp_i3 = tmp_i2;
      } while (tmp_i2 != 0x400);
      G_Error("G_Spawn: no free entities");
    }
  }
  g_unk_00abe8a8 = g_unk_00abe8a8 + 1;
  trap_LocateGameData(g_unk_00abe8a4,g_unk_00abe8a8,0x600,level,0x54dc);
  tmp_pi5[0x69] = (int)"noclass";
  tmp_pi5[0x16b] = tmp_pi5[0x16b] + 1;
  tmp_pi5[0x65] = 1;
  tmp_pi5[0xa7] = 0;
  tmp_pi5[0xa8] = 0;
  *tmp_pi5 = ((int)(tmp_pi5 + -0x24f928) >> 9) * -0x55555555;
  tmp_pi5[0x179] = 0;
  tmp_pi5[0xf0] = -1;
  tmp_pi5[0x60] = 0x3ff;
  tmp_pi5[0x123] = g_unk_00abe908;
  Bot_Queue_EntityCreated(tmp_pi5);
  return tmp_pi5;
}

int G_EntitiesFree(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (g_unk_00abe8a8 < 0x41) {
    tmp_i3 = 0x3c0;
  }
  else {
    tmp_i3 = 0x40;
    tmp_i2 = 0x9564a0;
    tmp_i1 = 0x40;
    do {
      if (*(int *)(tmp_i2 + 0x194) != 0) {
        tmp_i3 = tmp_i3 + 1;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_i2 = tmp_i2 + 0x600;
    } while (tmp_i1 != g_unk_00abe8a8);
    tmp_i3 = 0x400 - tmp_i3;
  }
  return tmp_i3;
}

void G_FreeEntity(uint32_t *param_1)
{
  uint8_t *tmp_pu1;
  uint32_t tmp_u2;
  uint tmp_u3;
  uint tmp_u4;
  uint32_t *tmp_pu5;
  bool tmp_b6;
  byte tmp_b7;
  
  tmp_b7 = 0;
  Bot_Event_EntityDeleted(param_1);
  tmp_pu1 = (uint8_t *)param_1[0x170];
  if (tmp_pu1 != (uint8_t *)0x3eee0) {
    if ((int)tmp_pu1 < 0x3eee1) {
      if (((tmp_pu1 != (uint8_t *)0x3b699) && (tmp_pu1 != (uint8_t *)0x3ec15)) &&
         (tmp_pu1 != (uint8_t *)0x37c98)) goto LAB_000f721e;
    }
    else if (((tmp_pu1 != (uint8_t *)0x49240) && (tmp_pu1 != (uint8_t *)0x527df)) &&
            (tmp_pu1 != &g_unk_00042729)) goto LAB_000f721e;
  }
  nitrox_RemoveEntityFromEntityArray(&SpawnEntities,param_1);
LAB_000f721e:
  switch(param_1[1]) {
  case 3:
    switch(param_1[0xb7]) {
    case 0x16:
    case 0x38:
      nitrox_RemoveEntityFromEntityArray(&AirstrikeEntities,param_1);
      break;
    case 0x28:
    case 0x44:
      nitrox_RemoveEntityFromEntityArray(&LandmineEntities,param_1);
      break;
    case 0x29:
      nitrox_RemoveEntityFromEntityArray(&SatchelEntities,param_1);
    }
    break;
  case 0xc:
    nitrox_RemoveEntityFromEntityArray(&TriggerEntities,param_1);
    break;
  case 0xd:
  case 0x1f:
  case 0x24:
  case 0x25:
  case 0x37:
    nitrox_RemoveEntityFromEntityArray(&IndicatorEntities,param_1);
    break;
  case 0x22:
    nitrox_RemoveEntityFromEntityArray(&TripmineEntities,param_1);
    break;
  case 0x29:
    nitrox_RemoveEntityFromEntityArray(&MG42Entities,param_1);
  }
  if ((void *)param_1[0xa8] != (void *)0x0) {
    (*(void *)param_1[0xa8])(param_1);
  }
  trap_UnlinkEntity(param_1);
  if (param_1[0x6b] == 0) {
    tmp_b6 = ((uint)param_1 & 1) != 0;
    tmp_u2 = param_1[0x16b];
    tmp_u4 = 0x600;
    tmp_pu5 = param_1;
    if (tmp_b6) {
      *(uint8_t *)param_1 = 0;
      tmp_pu5 = (uint32_t *)((int)param_1 + 1);
      tmp_u4 = 0x5ff;
    }
    if (((uint)tmp_pu5 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_u4 = tmp_u4 - 2;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
    }
    if (((uint)tmp_pu5 & 4) != 0) {
      *tmp_pu5 = 0;
      tmp_u4 = tmp_u4 - 4;
      tmp_pu5 = tmp_pu5 + 1;
    }
    for (tmp_u3 = tmp_u4 >> 2; tmp_u3 != 0; tmp_u3 = tmp_u3 - 1) {
      *tmp_pu5 = 0;
      tmp_pu5 = tmp_pu5 + (uint)tmp_b7 * -2 + 1;
    }
    if ((tmp_u4 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
    }
    if (tmp_b6) {
      *(uint8_t *)tmp_pu5 = 0;
    }
    param_1[0x69] = "freed";
    param_1[0x16b] = tmp_u2;
    param_1[0x6f] = g_unk_00abe908;
    param_1[0x65] = 0;
  }
  return;
}

int G_TempEntity(float *param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint32_t tmp_u4;
  int tmp_i5;
  
  tmp_i5 = G_Spawn();
  *(int *)(tmp_i5 + 4) = param_2 + 0x3b;
  *(char **)(tmp_i5 + 0x1a4) = "tempEntity";
  tmp_u4 = g_unk_00abe908;
  *(uint32_t *)(tmp_i5 + 0x1c0) = g_unk_00abe908;
  *(uint32_t *)(tmp_i5 + 0x184) = tmp_u4;
  *(uint32_t *)(tmp_i5 + 0x1c4) = 1;
  if (param_1 != (float *)0x0) {
    tmp_f2 = (float)(int)ROUND(*param_1);
    tmp_f3 = (float)(int)ROUND(param_1[1]);
    tmp_f1 = param_1[2];
    *(uint32_t *)(tmp_i5 + 0xc) = 0;
    *(uint32_t *)(tmp_i5 + 0x10) = 0;
    tmp_f1 = (float)(int)ROUND(tmp_f1);
    *(uint32_t *)(tmp_i5 + 0x14) = 0;
    *(uint32_t *)(tmp_i5 + 0x2c) = 0;
    *(uint32_t *)(tmp_i5 + 0x28) = 0;
    *(uint32_t *)(tmp_i5 + 0x24) = 0;
    *(float *)(tmp_i5 + 0x18) = tmp_f2;
    *(float *)(tmp_i5 + 0x1c) = tmp_f3;
    *(float *)(tmp_i5 + 0x20) = tmp_f1;
    *(float *)(tmp_i5 + 0x5c) = tmp_f2;
    *(float *)(tmp_i5 + 0x60) = tmp_f3;
    *(float *)(tmp_i5 + 100) = tmp_f1;
    *(float *)(tmp_i5 + 0x168) = tmp_f2;
    *(float *)(tmp_i5 + 0x16c) = tmp_f3;
    *(float *)(tmp_i5 + 0x170) = tmp_f1;
    if (*(int *)(tmp_i5 + 400) != 0) {
      *(float *)(*(int *)(tmp_i5 + 400) + 0x14) = tmp_f2;
      *(float *)(*(int *)(tmp_i5 + 400) + 0x18) = tmp_f3;
      *(float *)(*(int *)(tmp_i5 + 400) + 0x1c) = tmp_f1;
    }
  }
  trap_LinkEntity(tmp_i5);
  return tmp_i5;
}

int G_PopupMessage(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_i2 = G_Spawn();
  *(char **)(tmp_i2 + 0x1a4) = "messageent";
  *(uint32_t *)(tmp_i2 + 4) = 0x95;
  *(uint32_t *)(tmp_i2 + 0x128) = 0x20;
  tmp_u1 = g_unk_00abe908;
  *(uint32_t *)(tmp_i2 + 0x1c0) = g_unk_00abe908;
  *(uint32_t *)(tmp_i2 + 0x184) = tmp_u1;
  *(uint32_t *)(tmp_i2 + 0x1c4) = 1;
  *(uint32_t *)(tmp_i2 + 0x10c) = param_1;
  trap_LinkEntity(tmp_i2);
  return tmp_i2;
}

void G_AddPredictableEvent(int param_1,uint32_t param_2,uint32_t param_3)
{
  if (*(int *)(param_1 + 400) != 0) {
    BG_AddPredictableEventToPlayerstate(param_2,param_3,*(int *)(param_1 + 400));
  }
  return;
}

void G_AddEvent(uint32_t *param_1,int param_2,uint32_t param_3)
{
  int tmp_i1;
  uint tmp_u2;
  uint32_t tmp_u3;
  uint tmp_u4;
  
  if (param_2 != 0) {
    tmp_i1 = param_1[100];
    if (tmp_i1 == 0) {
      tmp_u2 = param_1[0x30];
      tmp_u4 = tmp_u2 & 3;
      param_1[tmp_u4 + 0x31] = param_2;
      param_1[tmp_u4 + 0x35] = param_3;
      param_1[0x30] = tmp_u2 + 1;
    }
    else {
      *(int *)(tmp_i1 + 0x70 + (*(uint *)(tmp_i1 + 0x6c) & 3) * 4) = param_2;
      *(uint32_t *)(param_1[100] + 0x80 + (*(uint *)(param_1[100] + 0x6c) & 3) * 4) = param_3;
      *(int *)(param_1[100] + 0x6c) = *(int *)(param_1[100] + 0x6c) + 1;
    }
    tmp_u3 = g_unk_00abe908;
    param_1[0x70] = g_unk_00abe908;
    param_1[0x61] = tmp_u3;
    return;
  }
  G_Printf("G_AddEvent: zero event added for entity %i\n",*param_1);
  return;
}

void G_Sound(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  tmp_i1 = nitrox_TempEventFromQueue(param_1 + 0x168,0x28);
  *(uint32_t *)(tmp_i1 + 0xbc) = param_2;
  return;
}

void G_ClientSound(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    tmp_i1 = nitrox_TempEventFromQueue(0,0x2b);
    tmp_i2 = *(int *)(param_1 + 400) - level;
    *(uint32_t *)(tmp_i1 + 0x128) = 0x800;
    *(int *)(tmp_i1 + 0x108) = (tmp_i2 >> 2) * -0x66e64f79;
    *(uint32_t *)(tmp_i1 + 0xbc) = param_2;
    *(int *)(tmp_i1 + 300) = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  }
  return;
}

void G_AnimScriptSound(uint32_t param_1,uint32_t param_2,int param_3)
{
  int *tmp_pi1;
  uint tmp_u2;
  uint32_t tmp_u3;
  int tmp_i4;
  
  tmp_pi1 = (int *)(g_entities + param_3 * 0x600 + 400);
  tmp_i4 = *tmp_pi1;
  if (tmp_i4 == 0) {
    tmp_u2 = *(uint *)(g_entities + param_3 * 0x600 + 0xc0);
    tmp_i4 = param_3 * 0x180 + (tmp_u2 & 3);
    *(uint32_t *)(g_entities + tmp_i4 * 4 + 0xc4) = 0x28;
    *(uint32_t *)(g_entities + tmp_i4 * 4 + 0xd4) = param_1;
    *(uint *)(g_entities + param_3 * 0x600 + 0xc0) = tmp_u2 + 1;
  }
  else {
    *(uint32_t *)(tmp_i4 + 0x70 + (*(uint *)(tmp_i4 + 0x6c) & 3) * 4) = 0x28;
    *(uint32_t *)(*tmp_pi1 + 0x80 + (*(uint *)(*tmp_pi1 + 0x6c) & 3) * 4) = param_1;
    *(int *)(*tmp_pi1 + 0x6c) = *(int *)(*tmp_pi1 + 0x6c) + 1;
  }
  tmp_u3 = g_unk_00abe908;
  *(uint32_t *)(g_entities + param_3 * 0x600 + 0x1c0) = g_unk_00abe908;
  *(uint32_t *)(g_entities + param_3 * 0x600 + 0x184) = tmp_u3;
  return;
}

void G_SetOrigin(int param_1,uint32_t *param_2)
{
  uint32_t tmp_u1;
  
  *(uint32_t *)(param_1 + 0x18) = *param_2;
  *(uint32_t *)(param_1 + 0x1c) = param_2[1];
  tmp_u1 = param_2[2];
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(uint32_t *)(param_1 + 0x20) = tmp_u1;
  *(uint32_t *)(param_1 + 0x10) = 0;
  *(uint32_t *)(param_1 + 0x14) = 0;
  *(uint32_t *)(param_1 + 0x2c) = 0;
  *(uint32_t *)(param_1 + 0x28) = 0;
  *(uint32_t *)(param_1 + 0x24) = 0;
  *(uint32_t *)(param_1 + 0x5c) = *param_2;
  *(uint32_t *)(param_1 + 0x60) = param_2[1];
  *(uint32_t *)(param_1 + 100) = param_2[2];
  *(uint32_t *)(param_1 + 0x168) = *param_2;
  *(uint32_t *)(param_1 + 0x16c) = param_2[1];
  *(uint32_t *)(param_1 + 0x170) = param_2[2];
  if (*(int *)(param_1 + 400) != 0) {
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x14) = *param_2;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x18) = param_2[1];
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x1c) = param_2[2];
  }
  return;
}

void G_SetAngle(int param_1,uint32_t *param_2)
{
  uint32_t tmp_u1;
  
  *(uint32_t *)(param_1 + 0x3c) = *param_2;
  *(uint32_t *)(param_1 + 0x40) = param_2[1];
  tmp_u1 = param_2[2];
  *(uint32_t *)(param_1 + 0x30) = 0;
  *(uint32_t *)(param_1 + 0x44) = tmp_u1;
  *(uint32_t *)(param_1 + 0x34) = 0;
  *(uint32_t *)(param_1 + 0x50) = 0;
  *(uint32_t *)(param_1 + 0x4c) = 0;
  *(uint32_t *)(param_1 + 0x38) = 0;
  *(uint32_t *)(param_1 + 0x48) = 0;
  *(uint32_t *)(param_1 + 0x174) = *param_2;
  *(uint32_t *)(param_1 + 0x178) = param_2[1];
  *(uint32_t *)(param_1 + 0x17c) = param_2[2];
  return;
}

void G_ProcessTagConnect(uint32_t *param_1,int param_2)
{
  uint *tmp_pu1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  char *tmp_pc4;
  
  if (*(char *)(param_1 + 0x100) == '\0') {
    G_Error("G_ProcessTagConnect: NULL ent->tagName\n");
  }
  tmp_pu3 = (uint32_t *)param_1[0x110];
  if (tmp_pu3 == (uint32_t *)0x0) {
    G_Error("G_ProcessTagConnect: NULL ent->tagParent\n");
    tmp_pu3 = (uint32_t *)param_1[0x110];
  }
  tmp_pc4 = (char *)va("%i %i %s",*param_1,*tmp_pu3,param_1 + 0x100);
  if ((tmp_pc4 != (char *)0x0) && (*tmp_pc4 != '\0')) {
    G_FindConfigstringIndex_part_0_constprop_4();
  }
  param_1[2] = param_1[2] | 0x8000;
  if (param_1[100] != 0) {
    tmp_pu1 = (uint *)(param_1[100] + 0x68);
    *tmp_pu1 = *tmp_pu1 | 0x8000;
    *(uint *)(param_1[100] + 0x68) = *(uint *)(param_1[100] + 0x68) & 0xffefffff;
    *(uint *)(param_1[100] + 0x68) = *(uint *)(param_1[100] + 0x68) & 0xfff7ffff;
    param_1[2] = param_1[2] & 0xffe7ffff;
  }
  if (param_2 != 0) {
    param_1[0xf] = 0;
    param_1[0x10] = 0;
    param_1[0x11] = 0;
    tmp_u2 = g_unk_00abe908;
    param_1[0x1f] = 0;
    param_1[0x1e] = 0;
    param_1[0x1d] = 0;
    param_1[0xd] = tmp_u2;
    param_1[0xe] = 0;
    param_1[0xc] = 0;
    param_1[0x14] = 0;
    param_1[0x13] = 0;
    param_1[0x12] = 0;
    param_1[0x5f] = 0;
    param_1[0x5e] = 0;
    param_1[0x5d] = 0;
  }
  return;
}

void G_SetEntState(uint32_t *param_1,int param_2)
{
  uint tmp_u1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  int local_101c [1027];
  
  tmp_i5 = param_1[0x116];
  if (tmp_i5 == param_2) {
    G_DPrintf("entity %i already in desired state [%i]\n",*param_1,tmp_i5);
    return;
  }
  if (param_2 == 1) {
    if (tmp_i5 == 2) {
      param_1[0x75] = param_1[0x76];
      param_1[0x53] = param_1[0x77];
      if (param_1[0x78] == 0) {
        param_1[2] = param_1[2] & 0xfffffffd;
      }
    }
    param_1[0x116] = 1;
    param_1[0x39] = 1;
    if (param_1[0x170] == 0x1908e) {
      mg42_stopusing(param_1);
      tmp_i5 = param_1[1];
    }
    else {
      tmp_i5 = param_1[1];
      if (tmp_i5 == 0x38) {
        nitrox_GetConfigstring(param_1[0xb9],local_101c,0x400);
        tmp_u1 = param_1[0xe7];
        param_1[0xe7] = tmp_u1 | 0x100;
        tmp_u4 = va("%i",tmp_u1 | 0x100);
        Info_SetValueForKey(local_101c,&g_unk_0026176c,tmp_u4);
        nitrox_SetConfigstring(param_1[0xb9],local_101c);
        tmp_i5 = param_1[1];
      }
    }
    if (tmp_i5 == 0x37) {
      tmp_i8 = ((int)(param_1 + -0x24f928) >> 9) * -0x55555555;
      tmp_i5 = G_FindMapEntityData(mapEntityData,tmp_i8);
      if (tmp_i5 != 0) {
        G_FreeMapEntityData(mapEntityData,tmp_i5);
      }
      tmp_i5 = G_FindMapEntityData(0x2d8ca94,tmp_i8);
      if (tmp_i5 != 0) {
        G_FreeMapEntityData(0x2d8ca94,tmp_i5);
      }
    }
    trap_UnlinkEntity(param_1);
    return;
  }
  if (param_2 == 0) {
    if (tmp_i5 == 2) {
      param_1[0x75] = param_1[0x76];
      param_1[0x53] = param_1[0x77];
      if (param_1[0x78] == 0) {
        param_1[2] = param_1[2] & 0xfffffffd;
      }
    }
    param_1[0x116] = 0;
    param_1[0x39] = 0;
    tmp_i5 = param_1[1];
    if (tmp_i5 == 0x38) {
      nitrox_GetConfigstring(param_1[0xb9],local_101c,0x400);
      tmp_u1 = param_1[0xe7];
      param_1[0xe7] = tmp_u1 & 0xfffffeff;
      tmp_u4 = va("%i",tmp_u1 & 0xfffffeff);
      Info_SetValueForKey(local_101c,&g_unk_0026176c,tmp_u4);
      nitrox_SetConfigstring(param_1[0xb9],local_101c);
      tmp_i5 = param_1[1];
    }
    if (tmp_i5 != 0x37) {
      trap_LinkEntity(param_1);
    }
    tmp_i5 = trap_EntitiesInBox(param_1 + 0x54,param_1 + 0x57,local_101c,0x400);
    if (tmp_i5 < 1) {
      return;
    }
    tmp_i8 = 0;
    do {
      tmp_i6 = local_101c[tmp_i8];
      tmp_i2 = tmp_i6 * 0x600;
      if ((*(int *)(g_entities + tmp_i2 + 4) - 1U < 3) || (*(int *)(g_entities + tmp_i2 + 0x1cc) != 0)
         ) {
        tmp_i6 = tmp_i6 * 0x600;
        tmp_pu7 = g_entities + tmp_i6;
        tmp_pu3 = (uint32_t *)G_TestEntityPosition(tmp_pu7);
        if ((tmp_pu3 != (uint32_t *)0x0) && (param_1 == tmp_pu3)) {
          if ((*(int *)(g_entities + tmp_i6 + 400) == 0) &&
             (tmp_i2 = *(int *)(g_entities + tmp_i6 + 4), tmp_i2 != 0x26)) {
            if (tmp_i2 == 2) {
              if (*(int *)(*(int *)(g_entities + tmp_i6 + 0x33c) + 0x24) == 5) {
                Team_DroppedFlagThink(tmp_pu7);
                goto LAB_000f80e8;
              }
            }
            else if ((tmp_i2 == 3) &&
                    ((*(int *)(g_entities + tmp_i6 + 0x2dc) == 0x44 ||
                     (*(int *)(g_entities + tmp_i6 + 0x2dc) == 0x28)))) {
              tmp_i6 = (tmp_i6 >> 9) * -0x55555555;
              tmp_i2 = G_FindMapEntityData(mapEntityData,tmp_i6);
              if (tmp_i2 != 0) {
                G_FreeMapEntityData(mapEntityData,tmp_i2);
              }
              tmp_i6 = G_FindMapEntityData(0x2d8ca94,tmp_i6);
              if (tmp_i6 != 0) {
                G_FreeMapEntityData(0x2d8ca94,tmp_i6);
              }
            }
            G_FreeEntity(tmp_pu7);
          }
          else {
            G_Damage(tmp_pu7,param_1,param_1,0,0,0,0x28,0x30);
          }
        }
      }
LAB_000f80e8:
      tmp_i8 = tmp_i8 + 1;
      if (tmp_i8 == tmp_i5) {
        return;
      }
    } while( true );
  }
  if (param_2 != 2) {
    return;
  }
  param_1[0x116] = 2;
  param_1[0x39] = 2;
  param_1[0x76] = param_1[0x75];
  if (param_1[1] == 0x20) {
    param_1[0x77] = param_1[0x53];
    if ((*(byte *)(param_1 + 2) & 2) == 0) goto LAB_000f8019;
  }
  else {
    tmp_u4 = param_1[0x53];
    param_1[0x75] = 0;
    param_1[0x53] = 0;
    param_1[0x77] = tmp_u4;
    if ((param_1[2] & 2) == 0) {
      param_1[2] = param_1[2] | 2;
      goto LAB_000f8019;
    }
  }
  param_1[0x78] = 1;
LAB_000f8019:
  if (param_1[0x170] == 0x1908e) {
    mg42_stopusing(param_1);
  }
  if (param_1[1] == 0x37) {
    tmp_i8 = ((int)(param_1 + -0x24f928) >> 9) * -0x55555555;
    tmp_i5 = G_FindMapEntityData(mapEntityData,tmp_i8);
    if (tmp_i5 != 0) {
      G_FreeMapEntityData(mapEntityData,tmp_i5);
    }
    tmp_i5 = G_FindMapEntityData(0x2d8ca94,tmp_i8);
    if (tmp_i5 != 0) {
      G_FreeMapEntityData(0x2d8ca94,tmp_i5);
    }
  }
  trap_LinkEntity(param_1);
  return;
}

uint32_t G_MapIsValidCampaignStartMap(void)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  
  if (0 < g_unk_02a9848c) {
    tmp_pu2 = g_campaigns;
    tmp_i3 = 0;
    do {
      tmp_i1 = Q_stricmp(tmp_pu2,&g_unk_00abe8c0);
      if (tmp_i1 == 0) {
        return 1;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu2 = tmp_pu2 + 0x494;
    } while (tmp_i3 < g_unk_02a9848c);
  }
  return 0;
}

void G_ParseCampaigns(void)
{
  uint tmp_u1;
  bool tmp_b2;
  bool tmp_b3;
  int tmp_i4;
  size_t tmp_s5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint tmp_u8;
  char *__s;
  uint8_t *tmp_pu9;
  char *tmp_pc10;
  char *tmp_pc11;
  byte tmp_b12;
  int local_4b8;
  uint32_t local_494;
  char local_490 [116];
  char local_41c [1032];
  uint32_t uStack_14;
  
  tmp_b12 = 0;
  uStack_14 = 0xf8667;
  g_unk_02a9848c = 0;
  g_unk_02a98490 = -1;
  memset(g_campaigns,0,0x92800);
  if ((g_campaignFile[0x10] == '\0') || (tmp_i4 = G_LoadCampaignsFromFile(), tmp_i4 == 0)) {
    __s = &bigTextBuffer;
    tmp_i4 = trap_FS_GetFileList("scripts",".campaign",&bigTextBuffer,100000);
    if (tmp_i4 < 1) {
      if (GHIDRA_FIELD(g_gametype, 12, 4) != 4) goto LAB_000f88fc;
    }
    else {
      tmp_b2 = false;
      if (g_unk_02a9848c < 0x200) {
        local_4b8 = 0;
        do {
          tmp_s5 = strlen(__s);
          tmp_u1 = tmp_s5 + 1;
          tmp_u8 = tmp_u1;
          tmp_pc10 = __s;
          tmp_pc11 = (char *)&local_494;
          if ((7 < tmp_u1) && (((uint)&local_494 & 4) != 0)) {
            local_494 = *(uint32_t *)__s;
            tmp_pc10 = __s + 4;
            tmp_pc11 = local_490;
            tmp_u8 = tmp_s5 - 3;
          }
          for (; tmp_u8 != 0; tmp_u8 = tmp_u8 - 1) {
            *tmp_pc11 = *tmp_pc10;
            tmp_pc10 = tmp_pc10 + (uint)tmp_b12 * -2 + 1;
            tmp_pc11 = tmp_pc11 + (uint)tmp_b12 * -2 + 1;
          }
          tmp_i6 = G_LoadCampaignsFromFile();
          tmp_b3 = true;
          if (tmp_i6 == 0) {
            tmp_b3 = tmp_b2;
          }
          tmp_b2 = tmp_b3;
          __s = __s + tmp_u1;
          local_4b8 = local_4b8 + 1;
          if (local_4b8 == tmp_i4) goto LAB_000f87a0;
        } while (g_unk_02a9848c < 0x200);
      }
      G_LogPrintf("Warning: number of campaigns larger then MAX_CAMPAIGNS\n");
LAB_000f87a0:
      if (GHIDRA_FIELD(g_gametype, 12, 4) != 4) {
LAB_000f88fc:
        trap_Cvar_Set("g_oldCampaign",&g_unk_0026ea14);
        trap_Cvar_Set("g_currentCampaign",&g_unk_0026ea14);
        trap_Cvar_Set("g_currentCampaignMap",&g_unk_0024bfa6);
        return;
      }
      if (tmp_b2) {
        return;
      }
    }
    if (g_unk_02a9848c < 1) {
      tmp_i6 = 0;
      tmp_i4 = g_unk_02a9848c;
    }
    else {
      tmp_i6 = 0;
      tmp_pu9 = g_campaigns;
      do {
        tmp_i4 = Q_stricmp(tmp_pu9,&g_unk_00abe8c0);
        if (tmp_i4 == 0) {
          trap_Cvar_Set("g_oldCampaign",0x2e515d0);
          trap_Cvar_Set("g_currentCampaign",tmp_i6 * 0x494 + 0x2cee4e8);
          trap_Cvar_Set("g_currentCampaignMap",&g_unk_0024bfa6);
          tmp_i4 = g_unk_02a9848c;
          g_unk_02a98494 = 1;
          *(uint32_t *)(g_campaigns + g_unk_02a9848c * 0x494 + 0x284) = 0;
          g_unk_02a98490 = tmp_i6;
          break;
        }
        tmp_i6 = tmp_i6 + 1;
        tmp_pu9 = tmp_pu9 + 0x494;
        tmp_i4 = g_unk_02a9848c;
      } while (tmp_i6 < g_unk_02a9848c);
    }
    if (tmp_i4 == tmp_i6) {
      tmp_i4 = trap_Argc();
      if (tmp_i4 < 1) {
        G_Error("Usage \'map <mapname>\n\'");
      }
      trap_Argv(0,local_41c,0x400);
      if (local_41c[0] == '\0') {
        G_Error("Usage \'map <mapname>\n\'");
      }
      trap_Cvar_Set("g_gametype","2");
      tmp_u7 = va("%s %s",local_41c,&g_unk_00abe8c0);
      trap_SendConsoleCommand(2,tmp_u7);
    }
  }
  else if (GHIDRA_FIELD(g_gametype, 12, 4) != 4) goto LAB_000f88fc;
  return;
}

int G_GetTeamFromEntity(uint8_t *param_1)
{
  int *tmp_pi1;
  uint tmp_u2;
  
  tmp_u2 = *(uint *)(param_1 + 4);
joined_r0x000f8a33:
  if (tmp_u2 < 0x2a) {
    switch((int)&_GLOBAL_OFFSET_TABLE_ +
           (&switchD_000f8a41::switchdataD_0025a308)[*(int *)(param_1 + 4)]) {
    case 0xf8a48:
      if (*(int *)(param_1 + 0x5c0) != 0x27cac) {
        return 0;
      }
    case 0xf8a60:
_L725:
      return *(int *)(param_1 + 0x108);
    case 0xf8a70:
      if (*(int *)(param_1 + 400) != 0) {
        return *(int *)(*(int *)(param_1 + 400) + 3000);
      }
      break;
    case 0xf8a88:
      goto _L726;
    case 0xf8ab0:
      break;
    case 0xf8ab8:
      switch(*(uint32_t *)(param_1 + 0x2dc)) {
      case 0xf:
      case 0x10:
      case 0x12:
      case 0x16:
      case 0x19:
      case 0x26:
      case 0x27:
      case 0x33:
      case 0x38:
      case 0x3f:
      case 0x41:
        goto _L725;
      default:
        break;
      case 0x15:
      case 0x28:
      case 0x29:
      case 0x42:
      case 0x44:
        return *(int *)(param_1 + 0x108) % 4;
      }
    }
  }
  return 0;
_L726:
  tmp_pi1 = (int *)(param_1 + 0x180);
  param_1 = g_entities + *tmp_pi1 * 0x600;
  tmp_u2 = *(uint *)(g_entities + *tmp_pi1 * 0x600 + 4);
  goto joined_r0x000f8a33;
}

uint32_t G_Nextmap_v(int param_1,int param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  char local_41c [1036];
  
  if (param_3 == 0) {
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 4) {
      tmp_i1 = g_unk_02a98490 * 0x494;
      if (*(int *)(g_campaigns + tmp_i1 + 0x280) <= *(int *)(g_campaigns + tmp_i1 + 0x284) + 1) {
        trap_SendConsoleCommand(2,"vstr nextcampaign\n");
        trap_SendServerCommand(0xffffffff,"cp \"^3*** Loading nextcampaign! ***\n\"");
        return 0;
      }
      tmp_u2 = va("%i",*(int *)(g_campaigns + tmp_i1 + 0x284) + 1);
      trap_Cvar_Set("g_currentCampaignMap",tmp_u2);
      tmp_u2 = va("map %s\n",g_campaigns + tmp_i1 + (*(int *)(g_campaigns + tmp_i1 + 0x284) + 1) * 0x40
                );
      trap_SendConsoleCommand(2,tmp_u2);
      trap_SendServerCommand(0xffffffff,"cp \"^3*** Loading next map in campaign! ***\n\"");
      return 0;
    }
    if ((GHIDRA_FIELD(g_gametype, 12, 4) == 6) && ((g_mapVoteFlags[0xc] & 0x10) != 0)) {
      LogExit("Nextmap vote passed!");
      trap_SendServerCommand
                (0xffffffff,"chat \"^3*** Nextmap vote passed! Choose a new map! ***\" -2");
      return 0;
    }
    trap_SendConsoleCommand(2,"vstr nextmap\n");
    trap_SendServerCommand(0xffffffff,"cp \"^3*** Loading nextmap! ***\n\"");
  }
  else {
    tmp_i1 = trap_Argc();
    if (2 < tmp_i1) {
      if (param_5 == 0) {
        tmp_pc3 = "\\callvote";
      }
      else {
        tmp_pc3 = "\\ref";
      }
      G_refPrintf(param_1,"Usage: ^3%s %s%s\n",tmp_pc3,param_3,
                  (&g_ptr_s_7_Loads_standard_competition_se_002ae8f0)[param_2 * 5]);
      return 0xffffffff;
    }
    if (((param_1 != 0) && (GHIDRA_FIELD(vote_allow_nextmap, 12, 4) == 0)) &&
       ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
        (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 == 0)))) {
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
      return 0xffffffff;
    }
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 4) {
      trap_Cvar_VariableStringBuffer("nextcampaign",local_41c,0x400);
      if (local_41c[0] == '\0') {
        G_refPrintf(param_1,"\'nextcampaign\' is not set.");
        return 0xffffffff;
      }
    }
    else {
      trap_Cvar_VariableStringBuffer("nextmap",local_41c,0x400);
      if (local_41c[0] == '\0') {
        G_refPrintf(param_1,"\'nextmap\' is not set.");
        return 0xffffffff;
      }
    }
  }
  return 0;
}

uint32_t G_StartMatch_v(uint32_t param_1,int param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  char *tmp_pc2;
  
  if (param_3 == 0) {
    G_refAllReady_cmd(0);
    return 0;
  }
  tmp_i1 = trap_Argc();
  if ((2 < tmp_i1) && (tmp_i1 = Q_stricmp(param_4,&g_unk_0026f751), tmp_i1 == 0)) {
    if (param_5 == 0) {
      tmp_pc2 = "\\callvote";
    }
    else {
      tmp_pc2 = "\\ref";
    }
    G_refPrintf(param_1,"Usage: ^3%s %s%s\n",tmp_pc2,param_3,
                (&g_ptr_s_7_Loads_standard_competition_se_002ae8f0)[param_2 * 5]);
    return 0xffffffff;
  }
  if ((GHIDRA_FIELD(g_gamestate, 12, 4) == 3) || (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
    tmp_pc2 = "^3Match is already in progress!";
  }
  else if (GHIDRA_FIELD(g_gamestate, 12, 4) == 1) {
    tmp_pc2 = "^3Countdown already started!";
  }
  else {
    if ((int)GHIDRA_FIELD(match_minplayers, 12, 4) <= g_unk_00abe940) {
      return 0;
    }
    tmp_pc2 = "^3Not enough players to start match!";
  }
  G_refPrintf(param_1,tmp_pc2);
  return 0xffffffff;
}

uint32_t G_Poll_v(int param_1,uint32_t param_2,int param_3,uint32_t param_4)
{
  int tmp_i1;
  char *__s;
  size_t tmp_s2;
  uint32_t tmp_u3;
  
  if (param_3 == 0) {
    return 0;
  }
  if ((param_1 == 0) || (GHIDRA_FIELD(vote_allow_poll, 12, 4) != 0)) {
LAB_000f8f94:
    __s = (char *)ConcatArgs(2);
    tmp_s2 = strlen(__s);
    if (tmp_s2 < 2) {
      tmp_u3 = 0xffffffff;
    }
    else {
      tmp_u3 = ConcatArgs(2);
      Com_sprintf(param_4,0x100,&g_unk_0024e6e9,tmp_u3);
      tmp_u3 = 0;
    }
  }
  else {
    if (*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0) {
      tmp_i1 = nitrox_CheckPermission(param_1,6);
      if (tmp_i1 != 0) goto LAB_000f8f94;
    }
    G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
    tmp_u3 = 0xffffffff;
  }
  return tmp_u3;
}

uint32_t G_NextCampaign_v_part_0(void)
{
  char local_40c [1028];
  uint32_t uStack_8;
  
  uStack_8 = 0xf903b;
  trap_Cvar_VariableStringBuffer("nextcampaign",local_40c,0x400);
  if (local_40c[0] == '\0') {
    return 0;
  }
  trap_SendConsoleCommand(2,"vstr nextcampaign\n");
  return 0;
}

int G_NextCampaign_v(int param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  
  if (param_3 == 0) {
    tmp_i1 = G_NextCampaign_v_part_0();
    return tmp_i1;
  }
  if ((param_1 == 0) || (GHIDRA_FIELD(vote_allow_nextcampaign, 12, 4) != 0)) {
LAB_000f90f1:
    tmp_i1 = -(uint)(GHIDRA_FIELD(g_gametype, 12, 4) != 4);
  }
  else {
    if (*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0) {
      tmp_i1 = nitrox_CheckPermission(param_1,6);
      if (tmp_i1 != 0) goto LAB_000f90f1;
    }
    tmp_i1 = -1;
  }
  return tmp_i1;
}

uint32_t G_RestartCampaign_v_part_1(void)
{
  uint32_t tmp_u1;
  uint8_t *tmp_pu2;
  char local_40c [1024];
  uint32_t uStack_c;
  
  uStack_c = 0xf913c;
  trap_Cvar_VariableStringBuffer("nextcampaign",local_40c,0x400);
  tmp_pu2 = &g_unk_0026ea14;
  if (local_40c[0] != '\0') {
    tmp_pu2 = (uint8_t *)va("; set nextcampaign \"%s\"",local_40c);
  }
  tmp_u1 = va("campaign %s%s\n",g_unk_02a98490 * 0x494 + 0x2cee4e8,tmp_pu2);
  trap_SendConsoleCommand(2,tmp_u1);
  return 0;
}

int G_RestartCampaign_v(int param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  
  if (param_3 == 0) {
    tmp_i1 = G_RestartCampaign_v_part_1();
    return tmp_i1;
  }
  if ((param_1 == 0) || (GHIDRA_FIELD(vote_allow_restartcampaign, 12, 4) != 0)) {
LAB_000f9231:
    tmp_i1 = -(uint)(GHIDRA_FIELD(g_gametype, 12, 4) != 4);
  }
  else {
    if (*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0) {
      tmp_i1 = nitrox_CheckPermission(param_1,6);
      if (tmp_i1 != 0) goto LAB_000f9231;
    }
    tmp_i1 = -1;
  }
  return tmp_i1;
}

uint32_t G_Surrender_v_part_2(void)
{
  uint8_t *tmp_pu1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  uint8_t local_40c [1020];
  uint32_t uStack_10;
  
  uStack_10 = 0xf927d;
  trap_GetConfigstring(0xe,local_40c,0x400);
  if (g_unk_00abef6c == 1) {
    tmp_pu1 = &g_unk_00258b23;
  }
  else {
    tmp_pu1 = &g_unk_0024bfa6;
  }
  Info_SetValueForKey(local_40c,"w",tmp_pu1);
  trap_SetConfigstring(0xe,local_40c);
  if (g_unk_00abef6c == 1) {
    tmp_pc3 = "Players_Axis";
  }
  else {
    tmp_pc3 = "Players_Allies";
  }
  tmp_u2 = va("%s Surrender\n",tmp_pc3 + 8);
  LogExit(tmp_u2);
  if (g_unk_00abef6c == 1) {
    tmp_pc3 = "^1AXIS^7";
  }
  else {
    tmp_pc3 = "^4ALLIES^7";
  }
  tmp_u2 = va("chat \"%s have surrendered!\" -2",tmp_pc3);
  trap_SendServerCommand(0xffffffff,tmp_u2);
  return 0;
}

uint32_t G_Surrender_v(int param_1,uint32_t param_2,int param_3,uint32_t param_4)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  if (param_3 == 0) {
    if (GHIDRA_FIELD(g_gamestate, 12, 4) != 0) {
      return 0;
    }
    tmp_u3 = G_Surrender_v_part_2();
    return tmp_u3;
  }
  if ((((param_1 == 0) || (GHIDRA_FIELD(vote_allow_surrender, 12, 4) != 0)) ||
      ((*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0 &&
       (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 != 0)))) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
    if (*(int *)(*(int *)(param_1 + 400) + 3000) == 1) {
      tmp_pc2 = "[AXIS]";
    }
    else {
      tmp_pc2 = "[ALLIES]";
    }
    Q_strncpyz(param_4,tmp_pc2,0x100);
    return 0;
  }
  return 0xffffffff;
}

uint32_t G_Comp_v(int param_1,int param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  char *tmp_pc2;
  
  if (param_3 == 0) {
    trap_SendConsoleCommand(2,"exec default_comp.cfg\n");
    trap_SendServerCommand(0xffffffff,"cpm \"Competition Settings Loaded!\n\"");
  }
  else {
    tmp_i1 = trap_Argc();
    if (2 < tmp_i1) {
      if (param_5 == 0) {
        tmp_pc2 = "\\callvote";
      }
      else {
        tmp_pc2 = "\\ref";
      }
      G_refPrintf(param_1,"Usage: ^3%s %s%s\n",tmp_pc2,param_3,
                  (&g_ptr_s_7_Loads_standard_competition_se_002ae8f0)[param_2 * 5]);
      return 0xffffffff;
    }
    if (((param_1 != 0) && (GHIDRA_FIELD(vote_allow_comp, 12, 4) == 0)) &&
       ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
        (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 == 0)))) {
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
      return 0xffffffff;
    }
  }
  return 0;
}

uint32_t G_Pub_v(int param_1,int param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  char *tmp_pc2;
  
  if (param_3 == 0) {
    trap_SendConsoleCommand(2,"exec default_pub.cfg\n");
    trap_SendServerCommand(0xffffffff,"cpm \"Public Settings Loaded!\n\"");
  }
  else {
    tmp_i1 = trap_Argc();
    if (2 < tmp_i1) {
      if (param_5 == 0) {
        tmp_pc2 = "\\callvote";
      }
      else {
        tmp_pc2 = "\\ref";
      }
      G_refPrintf(param_1,"Usage: ^3%s %s%s\n",tmp_pc2,param_3,
                  (&g_ptr_s_7_Loads_standard_competition_se_002ae8f0)[param_2 * 5]);
      return 0xffffffff;
    }
    if (((param_1 != 0) && ((int)GHIDRA_FIELD(vote_allow_pub, 12, 4) < 1)) &&
       ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
        (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 == 0)))) {
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
      return 0xffffffff;
    }
  }
  return 0;
}

uint32_t G_ShuffleTeams_v(int param_1,int param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  char *tmp_pc2;
  
  if (param_3 == 0) {
    Svcmd_ShuffleTeams_f(1);
  }
  else {
    tmp_i1 = trap_Argc();
    if (2 < tmp_i1) {
      if (param_5 == 0) {
        tmp_pc2 = "\\callvote";
      }
      else {
        tmp_pc2 = "\\ref";
      }
      G_refPrintf(param_1,"Usage: ^3%s %s%s\n",tmp_pc2,param_3,
                  (&g_ptr_s_7_Loads_standard_competition_se_002ae8f0)[param_2 * 5]);
      return 0xffffffff;
    }
    if (((param_1 != 0) && (GHIDRA_FIELD(vote_allow_shuffleteams, 12, 4) == 0)) &&
       ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
        (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 == 0)))) {
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
      return 0xffffffff;
    }
  }
  return 0;
}

G_ShuffleTeams_NoRestart_v(int param_1,int param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  char *tmp_pc2;
  
  if (param_3 == 0) {
    Svcmd_ShuffleTeams_f(0);
  }
  else {
    tmp_i1 = trap_Argc();
    if (2 < tmp_i1) {
      if (param_5 == 0) {
        tmp_pc2 = "\\callvote";
      }
      else {
        tmp_pc2 = "\\ref";
      }
      G_refPrintf(param_1,"Usage: ^3%s %s%s\n",tmp_pc2,param_3,
                  (&g_ptr_s_7_Loads_standard_competition_se_002ae8f0)[param_2 * 5]);
      return 0xffffffff;
    }
    if (((param_1 != 0) && (GHIDRA_FIELD(vote_allow_shuffleteams_norestart, 12, 4) == 0)) &&
       ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
        (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 == 0)))) {
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
      return 0xffffffff;
    }
  }
  return 0;
}

uint32_t G_SwapTeams_v(int param_1,int param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  char *tmp_pc2;
  
  if (param_3 == 0) {
    G_swapTeams();
  }
  else {
    tmp_i1 = trap_Argc();
    if (2 < tmp_i1) {
      if (param_5 == 0) {
        tmp_pc2 = "\\callvote";
      }
      else {
        tmp_pc2 = "\\ref";
      }
      G_refPrintf(param_1,"Usage: ^3%s %s%s\n",tmp_pc2,param_3,
                  (&g_ptr_s_7_Loads_standard_competition_se_002ae8f0)[param_2 * 5]);
      return 0xffffffff;
    }
    if (((param_1 != 0) && (GHIDRA_FIELD(vote_allow_swapteams, 12, 4) == 0)) &&
       ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
        (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 == 0)))) {
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
      return 0xffffffff;
    }
  }
  return 0;
}

uint32_t G_SwapTeamsRestart_v(int param_1,int param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  char *tmp_pc2;
  
  if (param_3 == 0) {
    Svcmd_SwapTeams_f();
  }
  else {
    tmp_i1 = trap_Argc();
    if (2 < tmp_i1) {
      if (param_5 == 0) {
        tmp_pc2 = "\\callvote";
      }
      else {
        tmp_pc2 = "\\ref";
      }
      G_refPrintf(param_1,"Usage: ^3%s %s%s\n",tmp_pc2,param_3,
                  (&g_ptr_s_7_Loads_standard_competition_se_002ae8f0)[param_2 * 5]);
      return 0xffffffff;
    }
    if (((param_1 != 0) && (GHIDRA_FIELD(vote_allow_swapteamsrestart, 12, 4) == 0)) &&
       ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
        (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 == 0)))) {
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
      return 0xffffffff;
    }
  }
  return 0;
}

uint32_t G_Campaign_v(int param_1,int param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t *tmp_pu3;
  char *tmp_pc4;
  uint8_t local_81c [1024];
  char local_41c [1036];
  
  if (param_3 == 0) {
    trap_Cvar_VariableStringBuffer("nextcampaign",local_41c,0x400);
    tmp_pu3 = &g_unk_0026ea14;
    if (local_41c[0] != '\0') {
      tmp_pu3 = (uint8_t *)va("; set nextcampaign \"%s\"",local_41c);
    }
    tmp_u2 = va("campaign %s%s\n",&g_unk_00abee68,tmp_pu3);
    trap_SendConsoleCommand(2,tmp_u2);
    return 0;
  }
  trap_GetServerinfo(local_81c,0x400);
  if (((param_1 == 0) || (GHIDRA_FIELD(vote_allow_map, 12, 4) != 0)) ||
     ((*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0 &&
      (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 != 0)))) {
    if (param_5 == 0) {
      tmp_pc4 = "\\callvote";
    }
    else {
      tmp_pc4 = "\\ref";
    }
    if (param_1 != 0) {
      trap_Argv(2,local_41c,0x400);
      tmp_i1 = Q_stricmp(local_41c,&g_unk_0026f751);
      if ((tmp_i1 == 0) || (tmp_i1 = trap_Argc(), tmp_i1 == 2)) {
        trap_Argv(1,local_41c,0x400);
        G_refPrintf(param_1,"\nUsage: ^3%s %s%s\n",tmp_pc4,local_41c,
                    (&g_ptr_s_7_Loads_standard_competition_se_002ae8f0)[param_2 * 5]);
        goto joined_r0x000f9c72;
      }
    }
    Com_sprintf(&g_unk_00abee68,0x100,&g_unk_0024e6e9,param_4);
    tmp_u2 = 0;
  }
  else {
    G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
joined_r0x000f9c72:
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 4) {
      G_refPrintf(param_1,"^2%s^7 is currently ^3%s\n",param_3,g_unk_02a98490 * 0x494 + 0x2cee4e8);
    }
    tmp_u2 = 0xffffffff;
  }
  return tmp_u2;
}

uint32_t G_Map_v(int param_1,int param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  uint8_t *tmp_pu4;
  char *local_820;
  uint8_t local_81c [1024];
  char local_41c [1036];
  
  if (param_3 == 0) {
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 4) {
      trap_Cvar_VariableStringBuffer("nextcampaign",local_41c,0x400);
      tmp_pu4 = &g_unk_0026ea14;
      if (local_41c[0] != '\0') {
        tmp_pu4 = (uint8_t *)va("; set nextcampaign \"%s\"",local_41c);
      }
      tmp_pc3 = "campaign %s%s\n";
    }
    else {
      Svcmd_ResetMatch_f(1,0);
      trap_Cvar_VariableStringBuffer("nextmap",local_41c,0x400);
      tmp_pu4 = &g_unk_0026ea14;
      if (local_41c[0] != '\0') {
        tmp_pu4 = (uint8_t *)va("; set nextmap \"%s\"",local_41c);
      }
      tmp_pc3 = "map %s%s\n";
    }
    tmp_u2 = va(tmp_pc3,&g_unk_00abee68,tmp_pu4);
    trap_SendConsoleCommand(2,tmp_u2);
LAB_000f9e9b:
    tmp_u2 = 0;
  }
  else {
    trap_GetServerinfo(local_81c,0x400);
    if (((param_1 == 0) || (GHIDRA_FIELD(vote_allow_map, 12, 4) != 0)) ||
       (*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0)) {
LAB_000f9e0d:
      if (param_5 == 0) {
        local_820 = "\\callvote";
      }
      else {
        local_820 = "\\ref";
      }
      if (param_1 == 0) {
LAB_000f9e6a:
        Com_sprintf(&g_unk_00abee68,0x100,&g_unk_0024e6e9,param_4);
        goto LAB_000f9e9b;
      }
      trap_Argv(2,local_41c,0x400);
      tmp_i1 = Q_stricmp(local_41c,&g_unk_0026f751);
      if (tmp_i1 != 0) {
        tmp_i1 = trap_Argc();
        if (tmp_i1 != 2) goto LAB_000f9e6a;
      }
      trap_Argv(1,local_41c,0x400);
      G_refPrintf(param_1,"\nUsage: ^3%s %s%s\n",local_820,local_41c,
                  (&g_ptr_s_7_Loads_standard_competition_se_002ae8f0)[param_2 * 5]);
    }
    else {
      tmp_i1 = nitrox_CheckPermission(param_1,6);
      if (tmp_i1 != 0) goto LAB_000f9e0d;
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
    }
    tmp_u2 = Info_ValueForKey(local_81c,"mapname");
    G_refPrintf(param_1,"^2%s^7 is currently ^3%s\n",param_3,tmp_u2);
    tmp_u2 = 0xffffffff;
  }
  return tmp_u2;
}

int G_voteCmdCheck(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  void *tmp_pc1;
  int tmp_i2;
  int tmp_i3;
  uint8_t **tmp_ppu4;
  int tmp_i5;
  
  tmp_i3 = 0;
  tmp_ppu4 = &g_ptr_s_comp_0023bd0f_0xb_002ae8e4;
  do {
    tmp_i2 = Q_stricmp(param_2,*tmp_ppu4);
    if (tmp_i2 == 0) {
      tmp_pc1 = (void *)(&g_ptr_G_Comp_v_002ae8e8)[tmp_i3 * 5];
      tmp_i2 = (*tmp_pc1)(param_1,tmp_i3,param_2,param_3,param_4);
      if (tmp_i2 == 0) {
        Com_sprintf(param_2,0x100,(&g_ptr_s_Load_Competition_Settings_002ae8ec)[tmp_i3 * 5]);
        g_unk_00abee64 = tmp_pc1;
        return 0;
      }
      goto LAB_000fa3f1;
    }
    tmp_i3 = tmp_i3 + 1;
    tmp_ppu4 = tmp_ppu4 + 5;
  } while (tmp_i3 != 0x1d);
  tmp_i5 = 0;
  tmp_i3 = CustomVotes;
  while( true ) {
    if (tmp_i3 == 0) {
      return -2;
    }
    tmp_i3 = Q_stricmp(param_2,tmp_i3);
    if (tmp_i3 == 0) break;
    tmp_i5 = tmp_i5 + 1;
    tmp_i3 = (&CustomVotes)[tmp_i5];
  }
  tmp_i2 = nitmod_customVoteCmd(param_1,tmp_i5,param_2,param_3,param_4);
  if (tmp_i2 == 0) {
    Com_sprintf(param_2,0x100,(&CustomVotes)[tmp_i5] + 0x14);
    g_unk_00abee64 = nitmod_customVoteCmd;
    tmp_i2 = 0;
    g_unk_00abef70 = tmp_i5;
  }
  else {
LAB_000fa3f1:
    g_unk_00abee64 = (void *)0x0;
  }
  return tmp_i2;
}

void G_customVoteLoad(void)
{
  char tmp_c1;
  uint tmp_u2;
  int tmp_i3;
  void *pvVar4;
  char *tmp_pc5;
  uint tmp_u6;
  uint8_t *tmp_pu7;
  long tmp_l8;
  uint8_t *tmp_pu9;
  int *tmp_pi10;
  char *tmp_pc11;
  char *tmp_pc12;
  bool tmp_b13;
  byte tmp_b14;
  uint8_t *tmp_pu15;
  uint32_t tmp_u16;
  int local_454;
  uint32_t local_430;
  void *local_42c;
  uint local_428 [3];
  char local_41c [4];
  uint32_t local_418 [257];
  uint32_t uStack_14;
  
  tmp_b14 = 0;
  uStack_14 = 0xfa50d;
  local_41c[0] = '\0';
  local_41c[1] = '\0';
  local_41c[2] = '\0';
  local_41c[3] = '\0';
  tmp_u2 = 0;
  do {
    tmp_u6 = tmp_u2;
    *(uint32_t *)((int)local_418 + tmp_u6) = 0;
    *(uint32_t *)((int)local_418 + tmp_u6 + 4) = 0;
    tmp_u2 = tmp_u6 + 8;
  } while (tmp_u6 + 8 < 0x3f8);
  *(uint32_t *)((int)local_418 + tmp_u6 + 8) = 0;
  if (CustomVotes != (void *)0x0) {
    pvVar4 = CustomVotes;
    tmp_pi10 = (int *)&CustomVotes;
    do {
      free(pvVar4);
      *tmp_pi10 = 0;
      pvVar4 = (void *)tmp_pi10[1];
      tmp_pi10 = tmp_pi10 + 1;
    } while (pvVar4 != (void *)0x0);
  }
  tmp_i3 = trap_FS_FOpenFile("votes.db",&local_430,0);
  if (tmp_i3 < 0) {
    G_LogPrintf(
               "! [Admin::LoadVotes] WARNING: Unable to load custom votes. Couldn\'t open \'votes.db\', creating default one...\n"
               );
    tmp_i3 = trap_FS_FOpenFile("votes.db",&local_430,1);
    if (tmp_i3 < 0) {
      G_LogPrintf("! [Admin::LoadVotes] ERROR: Can not create default \'votes.db\' file\n");
      return;
    }
    trap_FS_Write("**********\n\n",0xc,local_430);
    trap_FS_Write("name = panzerwaron\n",0x13,local_430);
    trap_FS_Write("message = ^1Enable Panzerwar?\n",0x1e,local_430);
    trap_FS_Write("help = Enable Panzerwar\n",0x18,local_430);
    trap_FS_Write("exec = !panzerwar 1\n\n",0x14,local_430);
    trap_FS_Write("**********\n\n",0xc,local_430);
    trap_FS_Write("name = panzerwaroff\n",0x14,local_430);
    trap_FS_Write("message = ^1Disable Panzerwar?\n",0x1f,local_430);
    trap_FS_Write("help = Disable Panzerwar\n",0x19,local_430);
    trap_FS_Write("exec = !panzerwar 0\n\n",0x14,local_430);
    trap_FS_Write("**********\n\n",0xc,local_430);
    trap_FS_Write("name = splata\n",0xe,local_430);
    trap_FS_Write("message = Splat (instagib) all players?\n",0x28,local_430);
    trap_FS_Write("help = Splat (instagib) all players.\n",0x25,local_430);
    trap_FS_Write("exec = !splata\n\n",0xf,local_430);
    trap_FS_FCloseFile(local_430);
    G_LogPrintf("| [Admin::LoadVotes] Default \'votes.db\' file created\n");
    tmp_i3 = trap_FS_FOpenFile("votes.db",&local_430,0);
  }
  pvVar4 = malloc(tmp_i3 + 1);
  tmp_u16 = local_430;
  local_42c = pvVar4;
  trap_FS_Read(pvVar4,tmp_i3,local_430);
  *(uint8_t *)((int)local_42c + tmp_i3) = 0;
  tmp_pc5 = (char *)COM_Parse(&local_42c);
  if (*tmp_pc5 == '\0') {
    free(local_42c);
    free(pvVar4);
    trap_FS_FCloseFile(local_430);
    local_454 = 0;
    tmp_pu7 = &g_unk_0026ea14;
  }
  else {
    local_454 = 0;
    tmp_pu9 = (uint8_t *)0x0;
    tmp_b13 = false;
    do {
      tmp_i3 = Q_stricmp(tmp_pc5,"**********");
      if (tmp_i3 == 0) {
        if (tmp_b13) {
          (&CustomVotes)[local_454] = tmp_pu9;
          local_454 = local_454 + 1;
        }
        tmp_b13 = false;
      }
      else if (tmp_b13) {
        tmp_i3 = Q_stricmp(tmp_pc5,&g_unk_0025a6c1);
        if ((tmp_i3 == 0) || (tmp_i3 = Q_stricmp(tmp_pc5,&g_unk_0025a6c6), tmp_i3 == 0)) {
          tmp_i3 = Q_stricmp(tmp_pc5,&g_unk_0025a6c6);
          if (tmp_i3 == 0) {
            tmp_u16 = COM_GetCurrentParseLine();
            G_LogPrintf("! [Admin::LoadVotes] \'cmd\' is deprecated (line %d), use \'exec\' instead.\n"
                        ,tmp_u16);
          }
          tmp_u16 = 0x3ff;
          tmp_pu15 = tmp_pu9 + 0x314;
        }
        else {
          tmp_i3 = Q_stricmp(tmp_pc5,&g_unk_0024e755);
          if (tmp_i3 == 0) {
            tmp_u16 = 0x100;
            tmp_pu15 = tmp_pu9 + 0x114;
          }
          else {
            tmp_i3 = Q_stricmp(tmp_pc5,"message");
            if (tmp_i3 == 0) {
              tmp_u16 = 0x100;
              tmp_pu15 = tmp_pu9 + 0x14;
            }
            else {
              tmp_i3 = Q_stricmp(tmp_pc5,"name");
              if (tmp_i3 == 0) {
                tmp_u16 = 0x14;
                tmp_pu15 = tmp_pu9;
              }
              else {
                tmp_i3 = Q_stricmp(tmp_pc5,"passtext");
                tmp_b13 = tmp_i3 == 0;
                if (!tmp_b13) {
                  tmp_i3 = 7;
                  tmp_pc12 = tmp_pc5;
                  tmp_pc11 = "levels";
                  do {
                    if (tmp_i3 == 0) break;
                    tmp_i3 = tmp_i3 + -1;
                    tmp_b13 = *tmp_pc12 == *tmp_pc11;
                    tmp_pc12 = tmp_pc12 + (uint)tmp_b14 * -2 + 1;
                    tmp_pc11 = tmp_pc11 + (uint)tmp_b14 * -2 + 1;
                  } while (tmp_b13);
                  if (tmp_b13) {
                    local_428[0] = 0;
                    tmp_pc12 = local_41c;
                    tmp_u16 = 0x400;
                    local_428[1] = 0;
                    local_428[2] = 0;
                    G_shrubbot_readconfig_string(&local_42c,tmp_pc12,0x400);
                    tmp_i3 = 0;
                    for (; tmp_c1 = *tmp_pc12, tmp_c1 != '\0'; tmp_pc12 = tmp_pc12 + 1) {
                      while (tmp_c1 != ' ') {
                        tmp_pc12 = tmp_pc12 + 1;
                        tmp_u16 = va("%c",(int)tmp_c1);
                        Q_strcat(local_428,0xc,tmp_u16);
                        tmp_c1 = *tmp_pc12;
                        if (tmp_c1 == '\0') goto LAB_000fab95;
                      }
                      tmp_u16 = 10;
                      tmp_l8 = strtol((char *)local_428,(char **)0x0,10);
                      local_428[0] = local_428[0] & 0xffffff00;
                      *(long *)(tmp_pu9 + tmp_i3 * 4 + 0x714) = tmp_l8;
                      tmp_i3 = tmp_i3 + 1;
                    }
LAB_000fab95:
                    if ((char)local_428[0] != '\0') {
                      tmp_u16 = 10;
                      tmp_l8 = strtol((char *)local_428,(char **)0x0,10);
                      *(long *)(tmp_pu9 + tmp_i3 * 4 + 0x714) = tmp_l8;
                    }
                    tmp_b13 = true;
                    *(uint32_t *)(tmp_pu9 + 0x814) = 0xffffffff;
                  }
                  else {
                    tmp_b13 = true;
                    tmp_u16 = COM_GetCurrentParseLine();
                    G_LogPrintf("! [Admin::LoadVotes] Parse error near \'%s\' (line %d)\n",tmp_pc5,
                                tmp_u16);
                  }
                  goto LAB_000fa638;
                }
                tmp_u16 = 0x100;
                tmp_pu15 = tmp_pu9 + 0x214;
              }
            }
          }
        }
        tmp_b13 = true;
        G_shrubbot_readconfig_string(&local_42c,tmp_pu15,tmp_u16);
      }
LAB_000fa638:
      tmp_i3 = Q_stricmp(tmp_pc5,"**********");
      if (tmp_i3 == 0) {
        if (0x3f < local_454) {
          G_LogPrintf("! [Admin::LoadVotes] WARNING: MAX_CUSTOM_VOTES(%i) EXCEEDED.\n",0x40,tmp_u16);
          return;
        }
        tmp_pu9 = malloc(0x818);
        tmp_pu9[0x314] = 0;
        tmp_pu9[0x114] = 0;
        tmp_pu9[0x14] = 0;
        *tmp_pu9 = 0;
        tmp_pu9[0x214] = 0;
        tmp_u2 = 0;
        do {
          tmp_u6 = tmp_u2;
          *(uint32_t *)(tmp_pu9 + tmp_u6 + 0x714) = 0xffffffff;
          *(uint32_t *)(tmp_pu9 + tmp_u6 + 0x718) = 0xffffffff;
          tmp_u2 = tmp_u6 + 8;
        } while (tmp_u6 + 8 < 0x100);
        *(uint32_t *)(tmp_pu9 + tmp_u6 + 0x71c) = 0xffffffff;
        tmp_b13 = true;
      }
      tmp_pc5 = (char *)COM_Parse(&local_42c);
    } while (*tmp_pc5 != '\0');
    if (tmp_b13) {
      (&CustomVotes)[local_454] = tmp_pu9;
      local_454 = local_454 + 1;
    }
    free(local_42c);
    free(pvVar4);
    trap_FS_FCloseFile(local_430);
    tmp_pu7 = &g_unk_0024e6ea;
    if (local_454 < 2) {
      tmp_pu7 = &g_unk_0026ea14;
    }
  }
  G_LogPrintf("| [Admin::LoadVote] Loaded %d vote%s\n",local_454,tmp_pu7);
  return;
}

void G_voteHelp(int param_1,int param_2)
{
  int *tmp_pi1;
  uint32_t *tmp_pu2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  int tmp_i7;
  uint tmp_u8;
  int tmp_i9;
  int tmp_i10;
  int local_1d0;
  int local_1cc;
  int local_1ac [102];
  uint32_t uStack_14;
  
  tmp_u8 = 0;
  uStack_14 = 0xfacab;
  if (CustomVotes != 0) {
    tmp_u8 = 0;
    do {
      tmp_u8 = tmp_u8 + 1;
    } while ((&CustomVotes)[tmp_u8] != 0);
  }
  if (param_2 != 0) {
    trap_SendServerCommand
              ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
               "print \"\nN!tmod ^3callvote^7 commands are:\n^3----------------------------\n\"");
  }
  tmp_u6 = 0;
  tmp_i4 = 0;
  do {
    if (((&aVoteInfo)[tmp_i4 * 5] & 1 << ((byte)GHIDRA_FIELD(g_gametype, 12, 4) & 0x1f)) != 0) {
      local_1ac[tmp_u6] = tmp_i4;
      tmp_u6 = tmp_u6 + 1;
    }
    tmp_i4 = tmp_i4 + 1;
  } while (tmp_i4 != 0x1c);
  tmp_i4 = (((int)tmp_u6 >> 2) + 1) - (uint)((tmp_u6 & 3) == 0);
  if (-1 < tmp_i4) {
    if (tmp_i4 != 0) {
      local_1cc = tmp_i4 * 2;
      tmp_i9 = 0;
      local_1d0 = tmp_i4;
      do {
        while ((int)tmp_u6 <= tmp_i4 * 3 + tmp_i9) {
          if (local_1cc < (int)tmp_u6) {
            G_refPrintf(param_1,"^5%-17s%-17s%-17s",
                        (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[local_1ac[tmp_i9] * 5],
                        (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[local_1ac[local_1d0] * 5],
                        (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[local_1ac[local_1cc] * 5]);
          }
          else if (local_1d0 < (int)tmp_u6) {
            G_refPrintf(param_1,"^5%-17s%-17s",
                        (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[local_1ac[tmp_i9] * 5],
                        (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[local_1ac[local_1d0] * 5]);
          }
          else {
            G_refPrintf(param_1,"^5%-17s",(&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[local_1ac[tmp_i9] * 5])
            ;
          }
          tmp_i9 = tmp_i9 + 1;
          local_1d0 = local_1d0 + 1;
          local_1cc = local_1cc + 1;
          if (tmp_i9 == tmp_i4) goto LAB_000fae8e;
        }
        tmp_i10 = tmp_i4 * 3 + tmp_i9;
        tmp_pi1 = local_1ac + tmp_i9;
        tmp_i9 = tmp_i9 + 1;
        G_refPrintf(param_1,"^5%-17s%-17s%-17s%-17s",
                    (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[*tmp_pi1 * 5],
                    (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[local_1ac[local_1d0] * 5],
                    (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[local_1ac[local_1cc] * 5],
                    (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[local_1ac[tmp_i10] * 5]);
        local_1d0 = local_1d0 + 1;
        local_1cc = local_1cc + 1;
      } while (tmp_i9 != tmp_i4);
    }
LAB_000fae8e:
    tmp_i4 = (((int)tmp_u8 >> 2) + 1) - (uint)((tmp_u8 & 3) == 0);
    if ((0 < (int)tmp_u8) && (param_2 != 0)) {
      trap_SendServerCommand
                ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                 "print \"\nCustom ^3callvotes^7 commands are:\n^3----------------------------\n\"")
      ;
    }
    if (0 < tmp_i4) {
      tmp_i7 = 0;
      tmp_i9 = tmp_i4 * 2;
      tmp_i10 = tmp_i4;
      do {
        while (tmp_i5 = tmp_i4 * 3 + tmp_i7, (int)tmp_u8 <= tmp_i5) {
          if (tmp_i9 < (int)tmp_u8) {
            G_refPrintf(param_1,"^5%-17s%-17s%-17s",(&CustomVotes)[tmp_i7],(&CustomVotes)[tmp_i10],
                        (&CustomVotes)[tmp_i9]);
          }
          else if (tmp_i10 < (int)tmp_u8) {
            G_refPrintf(param_1,"^5%-17s%-17s",(&CustomVotes)[tmp_i7],(&CustomVotes)[tmp_i10]);
          }
          else {
            G_refPrintf(param_1,"^5%-17s",(&CustomVotes)[tmp_i7]);
          }
          tmp_i7 = tmp_i7 + 1;
          tmp_i10 = tmp_i10 + 1;
          tmp_i9 = tmp_i9 + 1;
          if (tmp_i7 == tmp_i4) goto LAB_000faf98;
        }
        tmp_pu2 = &CustomVotes + tmp_i10;
        tmp_i10 = tmp_i10 + 1;
        tmp_pu3 = &CustomVotes + tmp_i7;
        tmp_i7 = tmp_i7 + 1;
        G_refPrintf(param_1,"^5%-17s%-17s%-17s%-17s",*tmp_pu3,*tmp_pu2,(&CustomVotes)[tmp_i9],
                    (&CustomVotes)[tmp_i5]);
        tmp_i9 = tmp_i9 + 1;
      } while (tmp_i7 != tmp_i4);
    }
LAB_000faf98:
    if (param_2 != 0) {
      trap_SendServerCommand
                ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                 "print \"\nUsage: ^3\\callvote <command> <params>\n^7For current settings/help, use: ^3\\callvote <command> ?\n\n\""
                );
      return;
    }
  }
  return;
}

void G_voteFlags(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint local_20;
  
  local_20 = 0;
  if (0 < numVotesAvailable) {
    tmp_i3 = 0;
    do {
      tmp_i1 = trap_Cvar_VariableIntegerValue((&voteToggles)[tmp_i3 * 2]);
      if (tmp_i1 == 0) {
        local_20 = local_20 | (&g_unk_002ae5e4)[tmp_i3 * 2];
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 < numVotesAvailable);
  }
  if (GHIDRA_FIELD(voteFlags, 12, 4) != local_20) {
    tmp_u2 = va(&g_unk_00245ee9,local_20);
    trap_Cvar_Set("voteFlags",tmp_u2);
  }
  return;
}

uint32_t G_voteDescription(int param_1,int param_2,int param_3)
{
  char *tmp_pc1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint8_t local_41c [1036];
  
  if (param_2 == 0) {
    tmp_pc1 = "\\callvote";
  }
  else {
    tmp_pc1 = "\\ref";
  }
  if (param_1 == 0) {
    tmp_u3 = 0;
  }
  else {
    trap_Argv(2,local_41c,0x400);
    tmp_i2 = Q_stricmp(local_41c,&g_unk_0026f751);
    if ((tmp_i2 == 0) || (tmp_i2 = trap_Argc(), tmp_i2 == 2)) {
      trap_Argv(1,local_41c,0x400);
      G_refPrintf(param_1,"\nUsage: ^3%s %s%s\n",tmp_pc1,local_41c,
                  (&g_ptr_s_7_Loads_standard_competition_se_002ae8f0)[param_3 * 5]);
      tmp_u3 = 1;
    }
    else {
      tmp_u3 = 0;
    }
  }
  return tmp_u3;
}

int G_MapRestart_v(int param_1,uint32_t param_2,int param_3,uint32_t param_4,uint32_t param_5)
{
  int tmp_i1;
  int tmp_i2;
  
  if (param_3 != 0) {
    if (((param_1 == 0) || (GHIDRA_FIELD(vote_allow_maprestart, 12, 4) != 0)) ||
       ((*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0 &&
        (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 != 0)))) {
      tmp_i1 = trap_Argc();
      tmp_i2 = 0;
      if (tmp_i1 != 2) {
        tmp_i1 = G_voteDescription(param_1,param_5,param_2);
        tmp_i2 = -(uint)(tmp_i1 != 0);
      }
    }
    else {
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
      tmp_i2 = -1;
    }
    return tmp_i2;
  }
  Svcmd_ResetMatch_f(0,1);
  trap_SendServerCommand(0xffffffff,"cp \"^1*** Level Restarted! ***\n\"");
  return 0;
}

int G_MatchReset_v(int param_1,uint32_t param_2,int param_3,uint32_t param_4,uint32_t param_5)
{
  int tmp_i1;
  int tmp_i2;
  
  if (param_3 != 0) {
    if (((param_1 == 0) || (GHIDRA_FIELD(vote_allow_matchreset, 12, 4) != 0)) ||
       ((*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0 &&
        (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 != 0)))) {
      tmp_i1 = trap_Argc();
      tmp_i2 = 0;
      if (tmp_i1 != 2) {
        tmp_i1 = G_voteDescription(param_1,param_5,param_2);
        tmp_i2 = -(uint)(tmp_i1 != 0);
      }
    }
    else {
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
      tmp_i2 = -1;
    }
    return tmp_i2;
  }
  Svcmd_ResetMatch_f(1,1);
  trap_SendServerCommand(0xffffffff,"cp \"^1*** Match Reset! ***\n\"");
  return 0;
}

G_Timelimit_v(int param_1,uint32_t param_2,int param_3,char *param_4,uint32_t param_5)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t tmp_u3;
  
  if (param_3 == 0) {
    tmp_u3 = va("print \"^3%s set to: ^5%s\n\"","Timelimit",&g_unk_00abee68);
    trap_SendServerCommand(0xffffffff,tmp_u3);
    tmp_u3 = va(&g_unk_0026fe3c,&g_unk_00abea4c);
    trap_SendConsoleCommand(2,tmp_u3);
    return 0;
  }
  if (((param_1 == 0) || (GHIDRA_FIELD(vote_allow_timelimit, 12, 4) != 0)) ||
     ((*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0 &&
      (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 != 0)))) {
    tmp_i1 = G_voteDescription(param_1,param_5,param_2);
    if (tmp_i1 == 0) {
      tmp_l2 = strtol(param_4,(char **)0x0,10);
      if (-1 < tmp_l2) {
        Com_sprintf(&g_unk_00abee68,0x100,&g_unk_0024e6e9,param_4);
        return 0;
      }
      G_refPrintf(param_1,"Sorry, can\'t specify a timelimit < 0!");
      return 0xffffffff;
    }
  }
  else {
    G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
  }
  G_refPrintf(param_1,"^2%s^7 is currently ^3%s\n",param_3,0x2e4d370);
  return 0xffffffff;
}

uint32_t G_Gametype_v(int param_1,uint32_t param_2,int param_3,char *param_4,uint32_t param_5)
{
  long tmp_l1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  
  if (param_3 == 0) {
    tmp_u3 = va("cpm \"^3%s set to: ^5%s\n\"","Gametype",&g_unk_00abee68);
    trap_SendServerCommand(0xffffffff,tmp_u3);
    trap_Cvar_Set("g_gametype",&g_unk_00abee68);
    Svcmd_ResetMatch_f(1,1);
    return 0;
  }
  tmp_l1 = strtol(param_4,(char **)0x0,10);
  if (((param_1 != 0) && (GHIDRA_FIELD(vote_allow_gametype, 12, 4) == 0)) &&
     ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
      (tmp_i2 = nitrox_CheckPermission(param_1,6), tmp_i2 == 0)))) {
    tmp_i2 = 3;
    G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
    G_refPrintf(param_1,"\nAvailable gametypes:\n--------------------");
    do {
      tmp_i4 = tmp_i2 + -1;
      if (tmp_i4 != 4) {
        tmp_u3 = *(uint32_t *)(tmp_i2 * 4 + 0x2aeb3c);
        G_refPrintf(param_1,"  %d ^3(%s)",tmp_i4,tmp_u3);
        if (tmp_i2 == 9) goto LAB_000fc76c;
      }
      tmp_i2 = tmp_i2 + 1;
    } while( true );
  }
  tmp_i2 = G_voteDescription(param_1,param_5,param_2);
  if (tmp_i2 == 0) {
    if ((tmp_l1 - 2U < 7) && (tmp_l1 != 4)) {
      if (GHIDRA_FIELD(g_gametype, 12, 4) != tmp_l1) {
        Com_sprintf(&g_unk_00abee68,0x100,&g_unk_0024e6e9,param_4);
        Com_sprintf(param_4,0x100,&g_unk_0024e6e9,*(uint32_t *)(gameNames + tmp_l1 * 4));
        return 0;
      }
      G_refPrintf(param_1,"\n^3Gametype^5 is already set to %s!",
                  *(uint32_t *)(gameNames + tmp_l1 * 4));
      return 0xffffffff;
    }
    tmp_i2 = 3;
    G_refPrintf(param_1,"\n^3Invalid gametype: ^7%d",tmp_l1);
    G_refPrintf(param_1,"\nAvailable gametypes:\n--------------------");
    do {
      tmp_i4 = tmp_i2 + -1;
      if (tmp_i4 != 4) {
        tmp_u3 = *(uint32_t *)(tmp_i2 * 4 + 0x2aeb3c);
        G_refPrintf(param_1,"  %d ^3(%s)",tmp_i4,tmp_u3);
        if (tmp_i2 == 9) {
          G_refPrintf(param_1,"\n",tmp_i4,tmp_u3);
          return 0xffffffff;
        }
      }
      tmp_i2 = tmp_i2 + 1;
    } while( true );
  }
  tmp_i2 = 3;
  G_refPrintf(param_1,"\nAvailable gametypes:\n--------------------");
  do {
    tmp_i4 = tmp_i2 + -1;
    if (tmp_i4 != 4) {
      tmp_u3 = *(uint32_t *)(tmp_i2 * 4 + 0x2aeb3c);
      G_refPrintf(param_1,"  %d ^3(%s)",tmp_i4,tmp_u3);
      if (tmp_i2 == 9) {
LAB_000fc76c:
        G_refPrintf(param_1,"\n",tmp_i4,tmp_u3);
        tmp_u3 = va("%d (%s)",GHIDRA_FIELD(g_gametype, 12, 4),*(uint32_t *)(gameNames + GHIDRA_FIELD(g_gametype, 12, 4) * 4));
        G_refPrintf(param_1,"^2%s^7 is currently ^3%s\n",param_3,tmp_u3);
        return 0xffffffff;
      }
    }
    tmp_i2 = tmp_i2 + 1;
  } while( true );
}

G_Warmupfire_v(int param_1,uint32_t param_2,int param_3,char *param_4,uint32_t param_5)
{
  uint tmp_u1;
  int tmp_i2;
  long tmp_l3;
  uint32_t tmp_u4;
  uint tmp_u5;
  uint tmp_u6;
  int tmp_i7;
  int tmp_i8;
  uint8_t *tmp_pu9;
  
  if (param_3 == 0) {
    tmp_l3 = strtol(&g_unk_00abee68,(char **)0x0,10);
    tmp_u4 = va("cpm \"^3Warmup Damage set to: ^5%s\n\"",(&warmupType)[tmp_l3]);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    tmp_u4 = va("match_warmupDamage %s\n",&g_unk_00abee68);
    trap_SendConsoleCommand(2,tmp_u4);
    tmp_u4 = 0;
  }
  else {
    tmp_u1 = strtol(param_4,(char **)0x0,10);
    tmp_u5 = 2;
    if ((int)GHIDRA_FIELD(match_warmupDamage, 12, 4) < 3) {
      tmp_u5 = GHIDRA_FIELD(match_warmupDamage, 12, 4);
    }
    tmp_u6 = 0;
    if (-1 < (int)tmp_u5) {
      tmp_u6 = tmp_u5;
    }
    if (((param_1 == 0) || (GHIDRA_FIELD(vote_allow_warmupdamage, 12, 4) != 0)) ||
       ((*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0 &&
        (tmp_i2 = nitrox_CheckPermission(param_1,6), tmp_i2 != 0)))) {
      tmp_i2 = G_voteDescription(param_1,param_5,param_2);
      if (tmp_i2 == 0) {
        if (2 < tmp_u1) {
          G_refPrintf(param_1,"\n^3Invalid Warmup Damage type: ^7%d",tmp_u1);
          G_refPrintf(param_1,"\nAvailable Warmup Damage types:\n------------------------------");
          tmp_i2 = 0;
          do {
            tmp_pu9 = (&warmupType)[tmp_i2];
            tmp_i7 = tmp_i2 + 1;
            tmp_i8 = tmp_i2;
            G_refPrintf(param_1,"  %d ^3(%s)",tmp_i2,tmp_pu9);
            tmp_i2 = tmp_i7;
          } while (tmp_i7 != 3);
          G_refPrintf(param_1,"\n",tmp_i8,tmp_pu9);
          return 0xffffffff;
        }
        if (tmp_u1 != tmp_u6) {
          Com_sprintf(&g_unk_00abee68,0x100,&g_unk_0024e6e9,param_4);
          Com_sprintf(param_4,0x100,&g_unk_0024e6e9,(&warmupType)[tmp_u1]);
          return 0;
        }
        G_refPrintf(param_1,"\n^3Warmup Damage^5 is already set to %s!",(&warmupType)[tmp_u1]);
        return 0xffffffff;
      }
      G_refPrintf(param_1,"\nAvailable Warmup Damage types:\n------------------------------");
      tmp_i2 = 0;
      do {
        tmp_pu9 = (&warmupType)[tmp_i2];
        tmp_i8 = tmp_i2;
        G_refPrintf(param_1,"  %d ^3(%s)",tmp_i2,tmp_pu9);
        tmp_i2 = tmp_i2 + 1;
      } while (tmp_i2 != 3);
    }
    else {
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
      G_refPrintf(param_1,"\nAvailable Warmup Damage types:\n------------------------------");
      tmp_i2 = 0;
      do {
        tmp_pu9 = (&warmupType)[tmp_i2];
        tmp_i8 = tmp_i2;
        G_refPrintf(param_1,"  %d ^3(%s)",tmp_i2,tmp_pu9);
        tmp_i2 = tmp_i2 + 1;
      } while (tmp_i2 != 3);
    }
    G_refPrintf(param_1,"\n",tmp_i8,tmp_pu9);
    tmp_u4 = va("%d (%s)",tmp_u6,(&warmupType)[tmp_u6]);
    G_refPrintf(param_1,"^2%s^7 is currently ^3%s\n",param_3,tmp_u4);
    tmp_u4 = 0xffffffff;
  }
  return tmp_u4;
}

uint32_t G_AntiLag_v(int param_1,int param_2,int param_3,char *param_4,uint32_t param_5)
{
  int tmp_i1;
  long tmp_l2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  bool tmp_b5;
  uint8_t *tmp_pu6;
  
  if (param_3 == 0) {
    tmp_l2 = strtol(&g_unk_00abee68,(char **)0x0,10);
    if (tmp_l2 == 0) {
      tmp_pc3 = "DISABLED";
    }
    else {
      tmp_pc3 = "ENABLED";
    }
    tmp_u4 = va("cpm \"^3%s is: ^5%s\n\"","Anti-Lag",tmp_pc3);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    trap_Cvar_Set("g_antilag",&g_unk_00abee68);
    tmp_u4 = 0;
  }
  else {
    tmp_b5 = GHIDRA_FIELD(g_antilag, 12, 4) != 0;
    if (((param_1 == 0) || (GHIDRA_FIELD(vote_allow_antilag, 12, 4) != 0)) ||
       (*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0)) {
      tmp_i1 = G_voteDescription(param_1,param_5,param_2);
      if (tmp_i1 == 0) {
        tmp_l2 = strtol(param_4,(char **)0x0,10);
        if ((tmp_l2 == 0) || (!tmp_b5)) {
          tmp_l2 = strtol(param_4,(char **)0x0,10);
          if (tmp_l2 != 0 || tmp_b5) {
            Com_sprintf(&g_unk_00abee68,0x100,&g_unk_0024e6e9,param_4);
            tmp_l2 = strtol(param_4,(char **)0x0,10);
            if (tmp_l2 == 0) {
              tmp_pc3 = "DEACTIVATED";
            }
            else {
              tmp_pc3 = "ACTIVATED";
            }
            Com_sprintf(param_4,0x100,&g_unk_0024e6e9,tmp_pc3);
            return 0;
          }
          tmp_pc3 = "DISABLED";
        }
        else {
          tmp_pc3 = "ENABLED";
        }
        G_refPrintf(param_1,"^3%s^5 is already %s!",(&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_2 * 5]
                    ,tmp_pc3);
        return 0xffffffff;
      }
      if (tmp_b5) {
        tmp_pc3 = "ENABLED";
      }
      else {
        tmp_pc3 = "DISABLED";
      }
      tmp_pu6 = (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_2 * 5];
    }
    else {
      tmp_pu6 = (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_2 * 5];
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",tmp_pu6);
      if (tmp_b5) {
        tmp_pc3 = "ENABLED";
      }
      else {
        tmp_pc3 = "DISABLED";
      }
    }
    G_refPrintf(param_1,"^2%s^7 is currently ^3%s\n",tmp_pu6,tmp_pc3);
    tmp_u4 = 0xffffffff;
  }
  return tmp_u4;
}

uint32_t G_FriendlyFire_v(int param_1,int param_2,int param_3,char *param_4,uint32_t param_5)
{
  int tmp_i1;
  long tmp_l2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  uint tmp_u5;
  uint8_t *tmp_pu6;
  
  if (param_3 == 0) {
    tmp_l2 = strtol(&g_unk_00abee68,(char **)0x0,10);
    tmp_u4 = va("%i",GHIDRA_FIELD(g_friendlyFire, 12, 4) ^ 1);
    trap_Cvar_Set("g_friendlyFire",tmp_u4);
    if (tmp_l2 == 0) {
      tmp_pc3 = "DISABLED";
    }
    else {
      tmp_pc3 = "ENABLED";
    }
    tmp_u4 = va("cpm \"^3%s is: ^5%s\n\"","Friendly Fire",tmp_pc3);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    tmp_u4 = 0;
  }
  else {
    tmp_u5 = GHIDRA_FIELD(g_friendlyFire, 12, 4) & 1;
    if (((param_1 == 0) || (GHIDRA_FIELD(vote_allow_friendlyfire, 12, 4) != 0)) ||
       (*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0)) {
      tmp_i1 = G_voteDescription(param_1,param_5,param_2);
      if (tmp_i1 == 0) {
        tmp_l2 = strtol(param_4,(char **)0x0,10);
        if ((tmp_l2 == 0) || ((char)tmp_u5 == '\0')) {
          tmp_l2 = strtol(param_4,(char **)0x0,10);
          if (tmp_l2 != 0 || tmp_u5 != 0) {
            Com_sprintf(&g_unk_00abee68,0x100,&g_unk_0024e6e9,param_4);
            tmp_l2 = strtol(param_4,(char **)0x0,10);
            if (tmp_l2 == 0) {
              tmp_pc3 = "DEACTIVATED";
            }
            else {
              tmp_pc3 = "ACTIVATED";
            }
            Com_sprintf(param_4,0x100,&g_unk_0024e6e9,tmp_pc3);
            return 0;
          }
          tmp_pc3 = "DISABLED";
        }
        else {
          tmp_pc3 = "ENABLED";
        }
        G_refPrintf(param_1,"^3%s^5 is already %s!",(&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_2 * 5]
                    ,tmp_pc3);
        return 0xffffffff;
      }
      if (tmp_u5 == 0) {
        tmp_pc3 = "DISABLED";
      }
      else {
        tmp_pc3 = "ENABLED";
      }
      tmp_pu6 = (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_2 * 5];
    }
    else {
      tmp_pu6 = (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_2 * 5];
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",tmp_pu6);
      if (tmp_u5 == 0) {
        tmp_pc3 = "DISABLED";
      }
      else {
        tmp_pc3 = "ENABLED";
      }
    }
    G_refPrintf(param_1,"^2%s^7 is currently ^3%s\n",tmp_pu6,tmp_pc3);
    tmp_u4 = 0xffffffff;
  }
  return tmp_u4;
}

uint32_t G_BalancedTeams_v(int param_1,int param_2,int param_3,char *param_4,uint32_t param_5)
{
  int tmp_i1;
  long tmp_l2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  bool tmp_b5;
  uint8_t *tmp_pu6;
  
  if (param_3 == 0) {
    tmp_l2 = strtol(&g_unk_00abee68,(char **)0x0,10);
    if (tmp_l2 == 0) {
      tmp_pc3 = "DISABLED";
    }
    else {
      tmp_pc3 = "ENABLED";
    }
    tmp_u4 = va("cpm \"^3%s is: ^5%s\n\"","Balanced Teams",tmp_pc3);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    trap_Cvar_Set("g_balancedteams",&g_unk_00abee68);
    trap_Cvar_Set("g_teamForceBalance",&g_unk_00abee68);
    trap_Cvar_Set("g_lms_teamForceBalance",&g_unk_00abee68);
    tmp_u4 = 0;
  }
  else {
    tmp_b5 = GHIDRA_FIELD(g_balancedteams, 12, 4) != 0;
    if (((param_1 == 0) || (GHIDRA_FIELD(vote_allow_balancedteams, 12, 4) != 0)) ||
       (*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0)) {
      tmp_i1 = G_voteDescription(param_1,param_5,param_2);
      if (tmp_i1 == 0) {
        tmp_l2 = strtol(param_4,(char **)0x0,10);
        if ((tmp_l2 == 0) || (!tmp_b5)) {
          tmp_l2 = strtol(param_4,(char **)0x0,10);
          if (tmp_l2 != 0 || tmp_b5) {
            Com_sprintf(&g_unk_00abee68,0x100,&g_unk_0024e6e9,param_4);
            tmp_l2 = strtol(param_4,(char **)0x0,10);
            if (tmp_l2 == 0) {
              tmp_pc3 = "DEACTIVATED";
            }
            else {
              tmp_pc3 = "ACTIVATED";
            }
            Com_sprintf(param_4,0x100,&g_unk_0024e6e9,tmp_pc3);
            return 0;
          }
          tmp_pc3 = "DISABLED";
        }
        else {
          tmp_pc3 = "ENABLED";
        }
        G_refPrintf(param_1,"^3%s^5 is already %s!",(&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_2 * 5]
                    ,tmp_pc3);
        return 0xffffffff;
      }
      if (tmp_b5) {
        tmp_pc3 = "ENABLED";
      }
      else {
        tmp_pc3 = "DISABLED";
      }
      tmp_pu6 = (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_2 * 5];
    }
    else {
      tmp_pu6 = (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_2 * 5];
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",tmp_pu6);
      if (tmp_b5) {
        tmp_pc3 = "ENABLED";
      }
      else {
        tmp_pc3 = "DISABLED";
      }
    }
    G_refPrintf(param_1,"^2%s^7 is currently ^3%s\n",tmp_pu6,tmp_pc3);
    tmp_u4 = 0xffffffff;
  }
  return tmp_u4;
}

void G_voteDisableMessage(uint32_t param_1,uint32_t param_2)
{
  G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_2);
  return;
}

void G_playersMessage(uint32_t param_1)
{
  G_refPrintf(param_1,"Use the ^3players^7 command to find a valid player ID.");
  return;
}

void G_voteCurrentSetting(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  G_refPrintf(param_1,"^2%s^7 is currently ^3%s\n",param_2,param_3);
  return;
}

uint32_t
G_voteProcessOnOff(int param_1,uint32_t param_2,char *param_3,uint32_t param_4,int param_5,
                  int param_6,int param_7)

{
  int tmp_i1;
  long tmp_l2;
  char *tmp_pc3;
  uint8_t *tmp_pu4;
  
  if (((param_6 == 0) && (param_1 != 0)) && (*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0)) {
    tmp_pu4 = (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_7 * 5];
    G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",tmp_pu4);
    if (param_5 == 0) {
      tmp_pc3 = "DISABLED";
    }
    else {
      tmp_pc3 = "ENABLED";
    }
  }
  else {
    tmp_i1 = G_voteDescription(param_1,param_4,param_7);
    if (tmp_i1 == 0) {
      tmp_l2 = strtol(param_3,(char **)0x0,10);
      if ((tmp_l2 == 0) || (param_5 == 0)) {
        tmp_l2 = strtol(param_3,(char **)0x0,10);
        if (tmp_l2 != 0 || param_5 != 0) {
          Com_sprintf(&g_unk_00abee68,0x100,&g_unk_0024e6e9,param_3);
          tmp_l2 = strtol(param_3,(char **)0x0,10);
          if (tmp_l2 == 0) {
            tmp_pc3 = "DEACTIVATED";
          }
          else {
            tmp_pc3 = "ACTIVATED";
          }
          Com_sprintf(param_3,0x100,&g_unk_0024e6e9,tmp_pc3);
          return 0;
        }
        tmp_pc3 = "DISABLED";
      }
      else {
        tmp_pc3 = "ENABLED";
      }
      G_refPrintf(param_1,"^3%s^5 is already %s!",(&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_7 * 5],
                  tmp_pc3);
      return 0xffffffff;
    }
    if (param_5 == 0) {
      tmp_pc3 = "DISABLED";
    }
    else {
      tmp_pc3 = "ENABLED";
    }
    tmp_pu4 = (&g_ptr_s_comp_0023bd0f_0xb_002ae8e4)[param_7 * 5];
  }
  G_refPrintf(param_1,"^2%s^7 is currently ^3%s\n",tmp_pu4,tmp_pc3);
  return 0xffffffff;
}

void G_voteSetOnOff(uint32_t param_1,uint32_t param_2)
{
  long tmp_l1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  tmp_l1 = strtol(&g_unk_00abee68,(char **)0x0,10);
  if (tmp_l1 == 0) {
    tmp_pc2 = "DISABLED";
  }
  else {
    tmp_pc2 = "ENABLED";
  }
  tmp_u3 = va("cpm \"^3%s is: ^5%s\n\"",param_1,tmp_pc2);
  trap_SendServerCommand(0xffffffff,tmp_u3);
  trap_Cvar_Set(param_2,&g_unk_00abee68);
  return;
}

void G_voteSetValue(uint32_t param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  
  tmp_u1 = va("cpm \"^3%s set to: ^5%s\n\"",param_1,&g_unk_00abee68);
  trap_SendServerCommand(0xffffffff,tmp_u1);
  trap_Cvar_Set(param_2,&g_unk_00abee68);
  return;
}

void G_voteSetVoteString(uint32_t param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = va("print \"^3%s set to: ^5%s\n\"",param_1,&g_unk_00abee68);
  trap_SendServerCommand(0xffffffff,tmp_u1);
  tmp_u1 = va(&g_unk_0026fe3c,&g_unk_00abea4c);
  trap_SendConsoleCommand(2,tmp_u1);
  return;
}

void G_GametypeList(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  
  G_refPrintf(param_1,"\nAvailable gametypes:\n--------------------");
  tmp_i1 = 3;
  do {
    tmp_i2 = tmp_i1 + -1;
    if (tmp_i2 != 4) {
      tmp_u3 = *(uint32_t *)(tmp_i1 * 4 + 0x2aeb3c);
      G_refPrintf(param_1,"  %d ^3(%s)",tmp_i2,tmp_u3);
      if (tmp_i1 == 9) {
        G_refPrintf(param_1,"\n",tmp_i2,tmp_u3);
        return;
      }
    }
    tmp_i1 = tmp_i1 + 1;
  } while( true );
}

void G_voteSetBitFlag(uint32_t param_1,int param_2,uint32_t param_3,uint param_4)
{
  long tmp_l1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  
  tmp_l1 = strtol(&g_unk_00abee68,(char **)0x0,10);
  tmp_u2 = va("%i",param_4 ^ *(uint *)(param_2 + 0xc));
  trap_Cvar_Set(param_3,tmp_u2);
  if (tmp_l1 == 0) {
    tmp_pc3 = "DISABLED";
  }
  else {
    tmp_pc3 = "ENABLED";
  }
  tmp_u2 = va("cpm \"^3%s is: ^5%s\n\"",param_1,tmp_pc3);
  trap_SendServerCommand(0xffffffff,tmp_u2);
  return;
}

void G_WarmupDamageTypeList(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  
  G_refPrintf(param_1,"\nAvailable Warmup Damage types:\n------------------------------");
  tmp_i1 = 0;
  do {
    tmp_pu4 = (&warmupType)[tmp_i1];
    tmp_i2 = tmp_i1 + 1;
    tmp_i3 = tmp_i1;
    G_refPrintf(param_1,"  %d ^3(%s)",tmp_i1,tmp_pu4);
    tmp_i1 = tmp_i2;
  } while (tmp_i2 != 3);
  G_refPrintf(param_1,"\n",tmp_i3,tmp_pu4);
  return;
}

void G_IntermissionMapVote(int param_1)
{
  uint *tmp_pu1;
  int tmp_i2;
  byte tmp_b3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  int tmp_i6;
  long tmp_l7;
  long tmp_l8;
  long tmp_l9;
  uint tmp_u10;
  char local_81c [1024];
  char local_41c [1036];
  
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 7) {
    tmp_b3 = g_TDMOptions[0xc] & 8;
joined_r0x000fdf5a:
    if (tmp_b3 == 0) {
      tmp_pc4 = "print \"^3Map voting not enabled!\n\"";
      goto LAB_000fde02;
    }
  }
  else {
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
      tmp_b3 = g_DMOptions[0xd] & 0x40;
      goto joined_r0x000fdf5a;
    }
    if (GHIDRA_FIELD(g_gametype, 12, 4) != 6) {
      return;
    }
  }
  if (GHIDRA_FIELD(g_gamestate, 12, 4) == 3) {
    if (g_unk_00abf994 == 0) {
      tmp_pc4 = "print \"^3You can only vote during intermission\n\"";
    }
    else {
      trap_Argv(1,local_81c,0x400);
      tmp_i6 = trap_Argc();
      if (tmp_i6 == 2) {
        tmp_i6 = *(int *)(param_1 + 400);
        tmp_u10 = *(uint *)(tmp_i6 + 0x68);
        if ((tmp_u10 & 0x4000) != 0) {
          *(int *)(&g_unk_02aa0420 + *(int *)(tmp_i6 + 0xf18) * 0x98) =
               *(int *)(&g_unk_02aa0420 + *(int *)(tmp_i6 + 0xf18) * 0x98) + -1;
          (&g_unk_02aa042c)[*(int *)(*(int *)(param_1 + 400) + 0xf18) * 0x26] =
               (&g_unk_02aa042c)[*(int *)(*(int *)(param_1 + 400) + 0xf18) * 0x26] + -1;
          tmp_i6 = *(int *)(param_1 + 400);
          tmp_u10 = *(uint *)(tmp_i6 + 0x68);
        }
        *(uint *)(tmp_i6 + 0x68) = tmp_u10 | 0x4000;
        tmp_l7 = strtol(local_81c,(char **)0x0,10);
        *(int *)(&g_unk_02aa0420 + tmp_l7 * 0x98) = *(int *)(&g_unk_02aa0420 + tmp_l7 * 0x98) + 1;
        tmp_l7 = strtol(local_81c,(char **)0x0,10);
        (&g_unk_02aa042c)[tmp_l7 * 0x26] = (&g_unk_02aa042c)[tmp_l7 * 0x26] + 1;
        tmp_i6 = *(int *)(param_1 + 400);
        tmp_l7 = strtol(local_81c,(char **)0x0,10);
        *(long *)(tmp_i6 + 0xf18) = tmp_l7;
        return;
      }
      tmp_i6 = trap_Argc();
      if (tmp_i6 != 3) {
        return;
      }
      trap_Argv(2,local_41c,0x400);
      tmp_l7 = strtol(local_41c,(char **)0x0,10);
      if (2 < tmp_l7 - 1U) {
        return;
      }
      tmp_u10 = 0;
      while ((tmp_l7 - 1U == tmp_u10 ||
             (tmp_i6 = *(int *)(*(int *)(param_1 + 400) + 0xf18 + tmp_u10 * 4),
             tmp_l8 = strtol(local_81c,(char **)0x0,10), tmp_i6 != tmp_l8))) {
        tmp_u10 = tmp_u10 + 1;
        if (tmp_u10 == 3) {
          tmp_i6 = tmp_l7 + 0x3c3;
          tmp_i2 = *(int *)(*(int *)(param_1 + 400) + 8 + tmp_i6 * 4);
          if (tmp_i2 != -1) {
            *(int *)(&g_unk_02aa0420 + tmp_i2 * 0x98) = *(int *)(&g_unk_02aa0420 + tmp_i2 * 0x98) - tmp_l7;
            (&g_unk_02aa042c)[*(int *)(*(int *)(param_1 + 400) + 8 + tmp_i6 * 4) * 0x26] =
                 (&g_unk_02aa042c)[*(int *)(*(int *)(param_1 + 400) + 8 + tmp_i6 * 4) * 0x26] - tmp_l7;
          }
          tmp_l8 = strtol(local_81c,(char **)0x0,10);
          tmp_l9 = strtol(local_81c,(char **)0x0,10);
          *(long *)(&g_unk_02aa0420 + tmp_l8 * 0x98) = tmp_l7 + *(int *)(&g_unk_02aa0420 + tmp_l9 * 0x98);
          tmp_l8 = strtol(local_81c,(char **)0x0,10);
          tmp_l9 = strtol(local_81c,(char **)0x0,10);
          (&g_unk_02aa042c)[tmp_l8 * 0x26] = tmp_l7 + (&g_unk_02aa042c)[tmp_l9 * 0x26];
          tmp_i2 = *(int *)(param_1 + 400);
          tmp_l7 = strtol(local_81c,(char **)0x0,10);
          *(long *)(tmp_i2 + 8 + tmp_i6 * 4) = tmp_l7;
          tmp_pu1 = (uint *)(*(int *)(param_1 + 400) + 0x68);
          *tmp_pu1 = *tmp_pu1 | 0x4000;
          return;
        }
      }
      tmp_pc4 = "print \"^3Can\'t vote for the same map twice\n\"";
    }
  }
  else {
    tmp_pc4 = "print \"^3Can\'t vote until intermission\n\"";
  }
LAB_000fde02:
  tmp_u5 = va(tmp_pc4);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
  return;
}

void G_IntermissionMapList(int param_1)
{
  int tmp_i1;
  byte tmp_b2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xfe189;
  if (g_unk_00abf994 != 0) {
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 7) {
      tmp_b2 = g_TDMOptions[0xc] & 8;
    }
    else {
      if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
        if (GHIDRA_FIELD(g_gametype, 12, 4) != 6) {
          return;
        }
        goto LAB_000fe1d8;
      }
      tmp_b2 = g_DMOptions[0xd] & 0x40;
    }
    if (tmp_b2 != 0) {
LAB_000fe1d8:
      tmp_i3 = GHIDRA_FIELD(g_maxMapsVotedFor, 12, 4);
      if (g_unk_02aa0298 <= (int)GHIDRA_FIELD(g_maxMapsVotedFor, 12, 4)) {
        tmp_i3 = g_unk_02aa0298;
      }
      tmp_u4 = va("immaplist %d ",GHIDRA_FIELD(g_mapVoteFlags, 12, 4) & 4);
      Q_strncpyz(local_41c,tmp_u4,0x400);
      if (0 < tmp_i3) {
        tmp_i5 = 0;
        do {
          tmp_i1 = (&g_unk_02aa02a0)[tmp_i5];
          tmp_i5 = tmp_i5 + 1;
          tmp_u4 = va("%s %d %d %d ",&g_unk_02aa03a0 + tmp_i1 * 0x98,tmp_i1,(&g_unk_02aa0428)[tmp_i1 * 0x26]
                     ,(&g_unk_02aa042c)[tmp_i1 * 0x26]);
          Q_strcat(local_41c,0x400,tmp_u4);
        } while (tmp_i5 != tmp_i3);
      }
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,local_41c);
      return;
    }
  }
  return;
}

void G_IntermissionVoteTally(int param_1)
{
  int *tmp_pi1;
  byte tmp_b2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xfe2f9;
  if (g_unk_00abf994 != 0) {
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 7) {
      tmp_b2 = g_TDMOptions[0xc] & 8;
    }
    else {
      if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
        if (GHIDRA_FIELD(g_gametype, 12, 4) != 6) {
          return;
        }
        goto LAB_000fe348;
      }
      tmp_b2 = g_DMOptions[0xd] & 0x40;
    }
    if (tmp_b2 != 0) {
LAB_000fe348:
      tmp_i3 = GHIDRA_FIELD(g_maxMapsVotedFor, 12, 4);
      if (g_unk_02aa0298 <= (int)GHIDRA_FIELD(g_maxMapsVotedFor, 12, 4)) {
        tmp_i3 = g_unk_02aa0298;
      }
      Q_strncpyz(local_41c,"imvotetally ",0x400);
      if (0 < tmp_i3) {
        tmp_i5 = 0;
        do {
          tmp_pi1 = &g_unk_02aa02a0 + tmp_i5;
          tmp_i5 = tmp_i5 + 1;
          tmp_u4 = va("%d ",*(uint32_t *)(&g_unk_02aa0420 + *tmp_pi1 * 0x98));
          Q_strcat(local_41c,0x400,tmp_u4);
        } while (tmp_i5 != tmp_i3);
      }
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,local_41c);
      return;
    }
  }
  return;
}

bool G_AvailableArty(int param_1)
{
  if (*(int *)(*(int *)(param_1 + 400) + 3000) != 1) {
    return g_unk_02aa29b4 < 1;
  }
  return g_unk_02aa29b0 < 1;
}

void G_AddArtyToCounters(int param_1)
{
  if (*(int *)(*(int *)(param_1 + 400) + 3000) != 1) {
    g_unk_02aa29b4 = g_unk_02aa29b4 + GHIDRA_FIELD(team_artyTime, 12, 4) * 1000;
    return;
  }
  g_unk_02aa29b0 = g_unk_02aa29b0 + GHIDRA_FIELD(team_artyTime, 12, 4) * 1000;
  return;
}

void G_GlobalClientEvent(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  
  tmp_i1 = nitrox_TempEventFromQueue(&vec3_origin,param_1);
  *(uint32_t *)(tmp_i1 + 0xf4) = param_2;
  *(uint32_t *)(tmp_i1 + 0x10c) = 1;
  *(uint32_t *)(tmp_i1 + 300) = param_3;
  *(uint32_t *)(tmp_i1 + 0x128) = 0x820;
  return;
}

void G_BurnMeGood(uint32_t *param_1,int param_2,int param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  if (param_3 == 0) {
    tmp_u3 = *param_1;
    *(int *)(param_2 + 0x390) = *(int *)(param_2 + 0x390) + 5;
    *(int *)(param_2 + 0x394) = g_unk_00abe908;
    local_28 = param_1[0x5a];
    local_24 = param_1[0x5b];
    local_20 = param_1[0x5c];
  }
  else {
    tmp_u3 = *(uint32_t *)(param_3 + 0x180);
    *(int *)(param_2 + 0x390) = *(int *)(param_2 + 0x390) + 5;
    *(int *)(param_2 + 0x394) = g_unk_00abe908;
    local_28 = *(uint32_t *)(param_3 + 0x168);
    local_24 = *(uint32_t *)(param_3 + 0x16c);
    local_20 = *(uint32_t *)(param_3 + 0x170);
  }
  if (*(int *)(param_2 + 0x454) != g_unk_00abe904) {
    tmp_u2 = GHIDRA_FIELD(BG_Weapons, 11764, 4);
    if (GHIDRA_FIELD(BG_Weapons, 11764, 4) == 0) {
      tmp_u2 = GHIDRA_FIELD(ammoTableMP, 472, 4);
    }
    G_Damage(param_2,param_1,param_1,&vec3_origin,&local_28,tmp_u2,0,0x11);
    *(int *)(param_2 + 0x454) = g_unk_00abe904;
  }
  tmp_i1 = g_unk_00abe908;
  if ((*(int *)(param_2 + 400) != 0) &&
     ((*(int *)(param_2 + 0x2c8) < 1 || (0 < *(int *)(param_2 + 0x390))))) {
    if (*(int *)(param_2 + 0x100) < g_unk_00abe908) {
      *(int *)(param_2 + 0xfc) = g_unk_00abe908;
    }
    *(int *)(param_2 + 0x100) = tmp_i1 + 2000;
    *(uint32_t *)(param_2 + 0x398) = tmp_u3;
    *(int *)(*(int *)(param_2 + 400) + 0x424) = tmp_i1;
  }
  return;
}

uint32_t G_PlayerCanBeSeenByOthers(uint8_t *param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  uint32_t local_40;
  uint32_t local_3c;
  float local_38;
  uint32_t local_34;
  uint32_t local_30;
  float local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  
  tmp_i1 = *(int *)(param_1 + 400);
  local_40 = *(uint32_t *)(tmp_i1 + 0x14);
  local_3c = *(uint32_t *)(tmp_i1 + 0x18);
  local_2c = *(float *)(tmp_i1 + 0x1c);
  local_38 = *(float *)(tmp_i1 + 0x3e4) + local_2c;
  local_28 = *(uint32_t *)(tmp_i1 + 0x14);
  local_24 = *(uint32_t *)(tmp_i1 + 0x18);
  local_20 = *(float *)(tmp_i1 + 0x1c) + *(float *)(tmp_i1 + 0x3f0);
  if (0 < g_unk_00abe900) {
    tmp_pu3 = g_entities;
    tmp_i4 = 0;
    tmp_i1 = g_unk_00abe900;
    local_34 = local_40;
    local_30 = local_3c;
    do {
      if ((*(int *)(tmp_pu3 + 0x194) != 0) && (tmp_pu3 != param_1)) {
        tmp_i2 = *(int *)(*(int *)(tmp_pu3 + 400) + 3000);
        if ((tmp_i2 != 3) &&
           ((0 < *(int *)(tmp_pu3 + 0x2c8) && (tmp_i2 != *(int *)(*(int *)(param_1 + 400) + 3000)))))
        {
          if ((*(byte *)(*(int *)(tmp_pu3 + 400) + 0x6a) & 4) == 0) {
            G_SetupFrustum();
          }
          else {
            G_SetupFrustum_ForBinoculars(tmp_pu3);
          }
          tmp_i1 = G_VisibleFromBinoculars(tmp_pu3,param_1,&local_40);
          if (((tmp_i1 != 0) ||
              (tmp_i1 = G_VisibleFromBinoculars(tmp_pu3,param_1,&local_34), tmp_i1 != 0)) ||
             (tmp_i2 = G_VisibleFromBinoculars(tmp_pu3,param_1,&local_28), tmp_i1 = g_unk_00abe900,
             tmp_i2 != 0)) {
            return 1;
          }
        }
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu3 = tmp_pu3 + 0x600;
    } while (tmp_i4 < tmp_i1);
  }
  return 0;
}

void G_createClusterNade(int param_1,int param_2,int param_3)
{
  char tmp_c1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int local_54;
  int local_50;
  int local_4c;
  double local_44;
  double local_3c;
  float local_30;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i3 = *(int *)(param_1 + 400);
  tmp_c1 = (*(int *)(tmp_i3 + 3000) != 1) * '\x05' + '\x04';
  if (param_2 < 1) {
    local_50 = 0x168;
    local_54 = 1;
  }
  else {
    local_54 = 0x20;
    if (param_2 < 0x21) {
      local_54 = param_2;
    }
    local_50 = (int)(0x168 / (longlong)local_54);
  }
  tmp_i4 = 0;
  tmp_f2 = 1.0;
  local_30 = 0.0;
  local_4c = local_50;
  if (param_3 == 0) {
    while( true ) {
      tmp_i4 = tmp_i4 + 1;
      local_28 = *(float *)(tmp_i3 + 0x20) - tmp_f2 * 200.0;
      local_30 = local_30 * 200.0;
      local_24 = *(float *)(tmp_i3 + 0x24) - local_30;
      local_20 = *(float *)(tmp_i3 + 0x28) - 30.0;
      tmp_i3 = fire_grenade(param_1,param_1 + 0x168,&local_28,tmp_c1);
      *(int *)(tmp_i3 + 0x29c) = g_unk_00abe908 + 0x9c4;
      if (tmp_i4 == local_54) break;
      sincos(((double)local_4c * 3.141592653589793) / 180.0,&local_3c,&local_44);
      tmp_i3 = *(int *)(param_1 + 400);
      local_4c = local_4c + local_50;
      tmp_f2 = (float)local_44;
      local_30 = (float)local_3c;
    }
    return;
  }
  while( true ) {
    tmp_i4 = tmp_i4 + 1;
    local_28 = *(float *)(tmp_i3 + 0x20) - tmp_f2 * 200.0;
    local_30 = local_30 * 200.0;
    local_24 = *(float *)(tmp_i3 + 0x24) - local_30;
    local_20 = *(float *)(tmp_i3 + 0x28) - 30.0;
    tmp_i3 = fire_grenade(param_1,param_1 + 0x168,&local_28,tmp_c1);
    *(int *)(tmp_i3 + 0x29c) = g_unk_00abe908 + 0x28a;
    if (tmp_i4 == local_54) break;
    sincos(((double)local_4c * 3.141592653589793) / 180.0,&local_44,&local_3c);
    tmp_i3 = *(int *)(param_1 + 400);
    local_4c = local_4c + local_50;
    tmp_f2 = (float)local_3c;
    local_30 = (float)local_44;
  }
  return;
}

uint8_t * G_GetDateAndTimeFileName(void)
{
  time_t tVar1;
  tm *__tp;
  uint8_t *tmp_pu2;
  time_t local_10 [2];
  
  tVar1 = time(local_10);
  tmp_pu2 = &g_unk_0026ea14;
  if (tVar1 != 0) {
    tmp_pu2 = tstr_12663;
    __tp = localtime(local_10);
    strftime(tstr_12663,0x32,"%m-%d-%y_%H-%M-%S",__tp);
  }
  return tmp_pu2;
}

uint8_t * G_SHA1(char *param_1)
{
  size_t tmp_s1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  
  SHA1Reset(&local_74);
  tmp_s1 = strlen(param_1);
  SHA1Input(&local_74,param_1,tmp_s1);
  tmp_i2 = SHA1Result(&local_74);
  tmp_pu3 = &g_unk_0026ea14;
  if (tmp_i2 != 0) {
    tmp_pu3 = (uint8_t *)va("%08X%08X%08X%08X%08X",local_74,local_70,local_6c,local_68,local_64);
  }
  return tmp_pu3;
}

