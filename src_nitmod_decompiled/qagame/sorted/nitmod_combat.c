/* Damage, death, kill logging — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_combat.h"

void G_LogDeath(int param_1,uint32_t param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  
  tmp_i2 = BG_DuplicateWeapon(param_2);
  if (*(int *)(param_1 + 400) != 0) {
    tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0x6dc + tmp_i2 * 0xc);
    *tmp_pi1 = *tmp_pi1 + 1;
    tmp_u3 = va("%d %d %d",*(uint32_t *)(*(int *)(param_1 + 400) + 3000),
               *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc8),tmp_i2);
    trap_PbStat((param_1 + -0x93e4a0 >> 9) * -0x55555555,"death",tmp_u3);
  }
  return;
}

void G_LogKill(int param_1,uint32_t param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  
  tmp_i2 = BG_DuplicateWeapon(param_2);
  if (*(int *)(param_1 + 400) != 0) {
    tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0x6d4 + tmp_i2 * 0xc);
    *tmp_pi1 = *tmp_pi1 + 1;
    tmp_u3 = va("%d %d %d",*(uint32_t *)(*(int *)(param_1 + 400) + 3000),
               *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc8),tmp_i2);
    trap_PbStat((param_1 + -0x93e4a0 >> 9) * -0x55555555,"kill",tmp_u3);
  }
  return;
}

void G_KillEnts(uint32_t param_1,int param_2,int param_3,uint32_t param_4)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = BG_StringHashValue(param_1);
  tmp_i2 = 0;
  do {
    while( true ) {
      do {
        tmp_i2 = G_FindByTargetnameFast(tmp_i2,param_1,tmp_u1);
        if (tmp_i2 == 0) {
          return;
        }
        *(uint32_t *)(tmp_i2 + 0x29c) = 0;
      } while (tmp_i2 == param_2);
      if (*(int *)(tmp_i2 + 4) == 4) break;
      if (*(int *)(tmp_i2 + 4) == 0x20) {
        if (param_3 != 0) {
          G_AddKillSkillPointsForDestruction(param_3,param_4,tmp_i2 + 0x4e4);
        }
        (**(void **)(tmp_i2 + 700))(tmp_i2,param_3,param_3,*(uint32_t *)(tmp_i2 + 0x2c8),param_4);
      }
      else {
LAB_000e946c:
        trap_UnlinkEntity(tmp_i2);
        *(int *)(tmp_i2 + 0x29c) = g_unk_00abe908 + 100;
        *(uint32_t *)(tmp_i2 + 0x2b4) = 0;
        *(uint32_t *)(tmp_i2 + 0x2b0) = 0;
        *(void **)(tmp_i2 + 0x2a4) = G_FreeEntity;
      }
    }
    if ((*(int *)(tmp_i2 + 0x5c0) != 0x27cac) || (*(int *)(tmp_i2 + 700) == 0)) goto LAB_000e946c;
    G_Damage(tmp_i2,param_3,param_3,0,0,0,0x28,0x1e);
  } while( true );
}

void G_KillBox(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  float local_1034;
  float local_1030;
  float local_102c;
  float local_1028;
  float local_1024;
  float local_1020;
  int local_101c [1027];
  
  tmp_i1 = *(int *)(param_1 + 400);
  local_1034 = *(float *)(param_1 + 0x134) + *(float *)(tmp_i1 + 0x14);
  local_1030 = *(float *)(param_1 + 0x138) + *(float *)(tmp_i1 + 0x18);
  local_102c = *(float *)(param_1 + 0x13c) + *(float *)(tmp_i1 + 0x1c);
  local_1028 = *(float *)(tmp_i1 + 0x14) + *(float *)(param_1 + 0x140);
  local_1024 = *(float *)(tmp_i1 + 0x18) + *(float *)(param_1 + 0x144);
  local_1020 = *(float *)(tmp_i1 + 0x1c) + *(float *)(param_1 + 0x148);
  tmp_i1 = trap_EntitiesInBox(&local_1034,&local_1028,local_101c,0x400);
  if (0 < tmp_i1) {
    tmp_i3 = 0;
    do {
      while ((tmp_i2 = local_101c[tmp_i3] * 0x600, *(int *)(g_entities + tmp_i2 + 400) != 0 &&
             (*(int *)(g_entities + tmp_i2 + 0x120) != 0))) {
        tmp_i3 = tmp_i3 + 1;
        G_Damage(g_entities + tmp_i2,param_1,param_1,0,0,100000,8,0x1e);
        if (tmp_i3 == tmp_i1) {
          return;
        }
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != tmp_i1);
  }
  return;
}

