/* Map entity spawn (SP_*), triggers, props — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_spawn.h"

void alarmbox_updateparts(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i2 = *(int *)(param_1 + 0xb0);
  if (param_2 != 0) {
    tmp_i3 = *(int *)(param_1 + 0x2f8);
joined_r0x00052ec4:
    if (tmp_i3 != 0) {
      do {
        if ((tmp_i3 != param_1) && (*(int *)(tmp_i3 + 0x368) != 0)) {
          if (*(int *)(param_1 + 0x368) == 0) {
            *(uint32_t *)(tmp_i3 + 0xb0) = 0;
            tmp_i1 = *(int *)(tmp_i3 + 0x254);
            if (tmp_i1 == 0) goto code_r0x0005318e;
LAB_00052f25:
            tmp_i4 = 0;
            while (tmp_i4 = G_FindByTargetnameFast(tmp_i4,tmp_i1,*(uint32_t *)(tmp_i3 + 0x5bc)),
                  tmp_i4 != 0) {
              if (tmp_i3 == tmp_i4) {
                G_Printf("WARNING: Entity used itself.\n");
                tmp_i4 = tmp_i3;
              }
              else {
                tmp_i1 = Q_stricmp(*(uint32_t *)(tmp_i4 + 0x1a4),"dlight");
                if (tmp_i1 == 0) {
                  *(uint32_t *)(tmp_i4 + 0x1f8) = *(uint32_t *)(tmp_i3 + 0x1f8);
                  tmp_i1 = *(int *)(tmp_i4 + 0x120);
                }
                else {
                  if (*(int *)(tmp_i4 + 0x5c0) != 0x46fcc) goto LAB_00052f40;
                  tmp_i1 = *(int *)(tmp_i3 + 0x368);
                }
                if (tmp_i1 != 0) {
                  G_UseEntity(tmp_i4,tmp_i3,0);
                }
              }
LAB_00052f40:
              tmp_i1 = *(int *)(tmp_i3 + 0x254);
            }
          }
          else {
            tmp_i1 = *(int *)(tmp_i3 + 0x254);
            tmp_i4 = *(int *)(param_1 + 0xb0);
            *(int *)(tmp_i3 + 0xb0) = tmp_i4;
            if (tmp_i1 != 0) {
              if (tmp_i4 != 1) goto LAB_00052f25;
              tmp_i4 = 0;
              while (tmp_i4 = G_FindByTargetnameFast(tmp_i4,tmp_i1,*(uint32_t *)(tmp_i3 + 0x5bc)),
                    tmp_i4 != 0) {
                if (tmp_i3 == tmp_i4) {
                  G_Printf("WARNING: Entity used itself.\n");
                  tmp_i4 = tmp_i3;
                }
                else {
                  tmp_i1 = Q_stricmp(*(uint32_t *)(tmp_i4 + 0x1a4),"dlight");
                  if (tmp_i1 == 0) {
                    *(uint32_t *)(tmp_i4 + 0x1f8) = *(uint32_t *)(tmp_i3 + 0x1f8);
                    if (*(int *)(tmp_i4 + 0x120) == 0) goto LAB_00053130;
                  }
                  else if ((*(int *)(tmp_i4 + 0x5c0) == 0x46fcc) && (*(int *)(tmp_i3 + 0x368) != 0)) {
LAB_00053130:
                    G_UseEntity(tmp_i4,tmp_i3,0);
                  }
                }
                tmp_i1 = *(int *)(tmp_i3 + 0x254);
              }
            }
          }
        }
        tmp_i3 = *(int *)(tmp_i3 + 0x2f4);
        if (tmp_i3 == 0) break;
      } while( true );
    }
  }
  tmp_i3 = *(int *)(param_1 + 0x254);
  if (tmp_i3 != 0) {
    tmp_i4 = 0;
    if (tmp_i2 == 1) {
      while (tmp_i4 = G_FindByTargetnameFast(tmp_i4,tmp_i3,*(uint32_t *)(param_1 + 0x5bc)),
            tmp_i4 != 0) {
        if (tmp_i4 == param_1) {
          G_Printf("WARNING: Entity used itself.\n");
        }
        else {
          tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i4 + 0x1a4),"dlight");
          if (tmp_i2 == 0) {
            *(uint32_t *)(tmp_i4 + 0x1f8) = *(uint32_t *)(param_1 + 0x1f8);
            if (*(int *)(tmp_i4 + 0x120) == 0) goto LAB_0005323c;
          }
          else if ((*(int *)(tmp_i4 + 0x5c0) == 0x46fcc) && (*(int *)(param_1 + 0x368) != 0)) {
LAB_0005323c:
            G_UseEntity(tmp_i4,param_1,0);
          }
        }
        tmp_i3 = *(int *)(param_1 + 0x254);
      }
    }
    else {
      while (tmp_i4 = G_FindByTargetnameFast(tmp_i4,tmp_i3,*(uint32_t *)(param_1 + 0x5bc)),
            tmp_i4 != 0) {
        if (tmp_i4 == param_1) {
          G_Printf("WARNING: Entity used itself.\n");
        }
        else {
          tmp_i2 = Q_stricmp(*(uint32_t *)(tmp_i4 + 0x1a4),"dlight");
          if (tmp_i2 == 0) {
            *(uint32_t *)(tmp_i4 + 0x1f8) = *(uint32_t *)(param_1 + 0x1f8);
            tmp_i2 = *(int *)(tmp_i4 + 0x120);
          }
          else {
            if (*(int *)(tmp_i4 + 0x5c0) != 0x46fcc) goto LAB_00053000;
            tmp_i2 = *(int *)(param_1 + 0x368);
          }
          if (tmp_i2 != 0) {
            G_UseEntity(tmp_i4,param_1,0);
          }
        }
LAB_00053000:
        tmp_i3 = *(int *)(param_1 + 0x254);
      }
    }
  }
  return;
code_r0x0005318e:
  tmp_i3 = *(int *)(tmp_i3 + 0x2f4);
  goto joined_r0x00052ec4;
}

void alarmbox_use(int param_1,int param_2)
{
  if (*(int *)(param_1 + 0x368) != 0) {
    *(uint *)(param_1 + 0xb0) = (uint)(*(int *)(param_1 + 0xb0) == 0);
    alarmbox_updateparts(param_1,1);
    if (*(int *)(param_2 + 400) != 0) {
      G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x204));
    }
  }
  return;
}

void alarmbox_die(int param_1)
{
  propExplosion(param_1);
  *(uint32_t *)(param_1 + 0xb0) = 2;
  *(uint32_t *)(param_1 + 0x368) = 0;
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  alarmbox_updateparts();
  return;
}

void alarmbox_finishspawning(int param_1)
{
  int tmp_i1;
  
  for (tmp_i1 = param_1; tmp_i1 != 0; tmp_i1 = *(int *)(tmp_i1 + 0x2f4)) {
    *(uint32_t *)(tmp_i1 + 0x2f8) = *(uint32_t *)(param_1 + 0x2f8);
  }
  alarmbox_updateparts(param_1,1);
  return;
}

void SP_alarm_box(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint32_t local_10 [2];
  
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
    tmp_u1 = G_ModelIndex("models/mapobjects/electronics/alarmbox.md3");
    *(uint32_t *)(param_1 + 0xa8) = tmp_u1;
    tmp_i2 = G_SpawnStringExt("noise",&g_unk_0024bfa6,local_10,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_alarm.c",0xa4);
    if (tmp_i2 != 0) {
      tmp_u1 = G_SoundIndex(local_10[0]);
      *(uint32_t *)(param_1 + 0x1f8) = tmp_u1;
    }
    tmp_u1 = G_SoundIndex("sound/world/alarmswitch");
    *(uint32_t *)(param_1 + 0x204) = tmp_u1;
    G_SetOrigin(param_1,param_1 + 0x5c);
    G_SetAngle(param_1,param_1 + 0x74);
    if (*(int *)(param_1 + 0x2c8) == 0) {
      *(uint32_t *)(param_1 + 0x2c8) = 10;
    }
    *(uint32_t *)(param_1 + 4) = 0xf;
    *(uint32_t *)(param_1 + 0x2cc) = 1;
    *(uint *)(param_1 + 0xb0) = *(uint *)(param_1 + 0x1a8) & 1;
    *(uint32_t *)(param_1 + 0x368) = 1;
    *(void **)(param_1 + 700) = alarmbox_die;
    *(void **)(param_1 + 0x2b4) = alarmbox_use;
    *(void **)(param_1 + 0x2a4) = alarmbox_finishspawning;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
    trap_LinkEntity(param_1);
    return;
  }
  G_Printf("^1alarm_box with NULL model\n");
  return;
}

void SP_info_player_deathmatch(int param_1)
{
  int tmp_i1;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_i1 = G_PickTarget(*(uint32_t *)(param_1 + 0x254));
  *(int *)(param_1 + 0x2ec) = tmp_i1;
  if (tmp_i1 != 0) {
    local_18 = *(float *)(tmp_i1 + 0x5c) - *(float *)(param_1 + 0x5c);
    local_14 = *(float *)(tmp_i1 + 0x60) - *(float *)(param_1 + 0x60);
    local_10 = *(float *)(tmp_i1 + 100) - *(float *)(param_1 + 100);
    vectoangles(&local_18,param_1 + 0x74);
  }
  return;
}

void SP_info_player_checkpoint(int param_1)
{
  int tmp_i1;
  float local_18;
  float local_14;
  float local_10;
  uint32_t uStack_c;
  
  uStack_c = 0x589d7;
  *(char **)(param_1 + 0x1a4) = "info_player_checkpoint";
  tmp_i1 = G_PickTarget(*(uint32_t *)(param_1 + 0x254));
  *(int *)(param_1 + 0x2ec) = tmp_i1;
  if (tmp_i1 != 0) {
    local_18 = *(float *)(tmp_i1 + 0x5c) - *(float *)(param_1 + 0x5c);
    local_14 = *(float *)(tmp_i1 + 0x60) - *(float *)(param_1 + 0x60);
    local_10 = *(float *)(tmp_i1 + 100) - *(float *)(param_1 + 100);
    vectoangles(&local_18,param_1 + 0x74);
  }
  return;
}

void SP_info_player_start(int param_1)
{
  int tmp_i1;
  float local_18;
  float local_14;
  float local_10;
  uint32_t uStack_c;
  
  uStack_c = 0x58a47;
  *(char **)(param_1 + 0x1a4) = "info_player_deathmatch";
  tmp_i1 = G_PickTarget(*(uint32_t *)(param_1 + 0x254));
  *(int *)(param_1 + 0x2ec) = tmp_i1;
  if (tmp_i1 != 0) {
    local_18 = *(float *)(tmp_i1 + 0x5c) - *(float *)(param_1 + 0x5c);
    local_14 = *(float *)(tmp_i1 + 0x60) - *(float *)(param_1 + 0x60);
    local_10 = *(float *)(tmp_i1 + 100) - *(float *)(param_1 + 100);
    vectoangles(&local_18,param_1 + 0x74);
  }
  return;
}

void SP_info_player_intermission(void)
{
  return;
}

void Use_Item(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (*(int *)(param_1 + 0x260) == 0) goto LAB_000817eb;
  tmp_i1 = *(int *)(param_1 + 0x2f8);
  if (tmp_i1 == 0) {
    G_Error("RespawnItem: bad teammaster");
    tmp_i1 = *(int *)(param_1 + 0x2f8);
    if (tmp_i1 != 0) goto LAB_000817b9;
    tmp_i3 = 0;
    param_1 = tmp_i1;
  }
  else {
LAB_000817b9:
    tmp_i3 = 0;
    tmp_i2 = tmp_i1;
    do {
      tmp_i2 = *(int *)(tmp_i2 + 0x2f4);
      tmp_i3 = tmp_i3 + 1;
      param_1 = tmp_i1;
    } while (tmp_i2 != 0);
  }
  tmp_i1 = rand();
  if (0 < tmp_i1 % tmp_i3) {
    tmp_i2 = 0;
    do {
      tmp_i2 = tmp_i2 + 1;
      param_1 = *(int *)(param_1 + 0x2f4);
    } while (tmp_i2 != tmp_i1 % tmp_i3);
  }
LAB_000817eb:
  *(uint *)(param_1 + 0x1b0) = *(uint *)(param_1 + 0x1b0) & 0xfeffffff;
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0xfffffffe;
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0x29c) = 0;
  return;
}

void Touch_Item_Auto(int param_1,uint32_t *param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint tmp_u4;
  void *tmp_pc5;
  int tmp_i6;
  int tmp_i7;
  int local_20;
  
  if (*(int *)(param_2[100] + 0x66c) == 0) {
    return;
  }
  if ((((*(int *)(param_1 + 0x368) == 0) && (*(int *)(*(int *)(param_1 + 0x33c) + 0x24) == 1)) &&
      (tmp_i2 = *(int *)(*(int *)(param_1 + 0x33c) + 0x28), tmp_i2 != 0xc)) &&
     (tmp_i2 = COM_BitCheck(param_2[100] + 0x3d4,tmp_i2), tmp_i2 == 0)) {
    return;
  }
  *(uint32_t *)(param_1 + 0x368) = 0;
  tmp_i2 = param_2[100];
  if ((((tmp_i2 == 0) || ((int)param_2[0xb2] < 1)) || ((*(uint *)(tmp_i2 + 0x68) & 0x800000) != 0)) ||
     ((((*(int *)(*(int *)(param_1 + 0x33c) + 0x24) == 3 &&
        (((g_medics[0xc] & 1) != 0 || ((*(uint *)(tmp_i2 + 0x68) & 0x200000) != 0)))) &&
       (tmp_i6 = *(int *)(param_1 + 0x218), tmp_i6 != 0)) &&
      ((*(int *)(tmp_i6 + 400) != 0 && (param_2[0x2b] == *(int *)(tmp_i6 + 0xac)))))))
  goto LAB_00083b56;
  tmp_i2 = BG_CanItemBeGrabbed(param_1,tmp_i2,tmp_i2 + 0xed0,*(uint32_t *)(tmp_i2 + 3000));
  if ((tmp_i2 != 0) &&
     ((*(int *)(param_1 + 0x2d0) == 0 ||
      ((*(uint *)(param_1 + 0xc) < 10 &&
       ((1 << ((byte)*(uint *)(param_1 + 0xc) & 0x1f) & 0x301U) != 0)))))) {
    tmp_i6 = *(int *)(param_1 + 0x33c);
    tmp_i2 = *(int *)(tmp_i6 + 0x24);
    if ((GHIDRA_FIELD(g_gamestate, 12, 4) != 0) && ((2 < tmp_i2 - 1U && (tmp_i2 != 6)))) goto _L505;
    switch(tmp_i2) {
    default:
      goto _L505;
    case 1:
      tmp_i2 = Pickup_Weapon(param_1,param_2);
      break;
    case 2:
      tmp_i2 = param_2[100];
      if (g_unk_00abe908 - *(int *)(tmp_i2 + 0xfe8) < 1000) goto LAB_00083b56;
      tmp_i7 = *(int *)(param_1 + 0xf4);
      if (tmp_i7 == 0) {
        tmp_i7 = 1;
      }
      if (*(int *)(tmp_i6 + 0x28) == 0xc) {
        BG_AddMagicAmmo(tmp_i2,tmp_i2 + 0xed0,*(uint32_t *)(tmp_i2 + 3000),
                        *(int *)(param_1 + 0x2e4) * tmp_i7);
        if (*(int *)(param_1 + 0xf4) == 2) goto LAB_00083dca;
LAB_00083ee7:
        tmp_i2 = -1;
      }
      else {
        tmp_i2 = *(int *)(param_1 + 0x2e4);
        if (tmp_i2 == 0) {
          tmp_i2 = *(int *)(tmp_i6 + 0x20) * tmp_i7;
        }
        Add_Ammo(param_2,*(int *)(tmp_i6 + 0x28),tmp_i2,0);
        if (*(int *)(param_1 + 0xf4) != 2) goto LAB_00083ee7;
LAB_00083dca:
        tmp_i2 = 0x3e6;
      }
      goto LAB_00083c5e;
    case 3:
      tmp_i2 = Pickup_Health(param_1,param_2);
      break;
    case 5:
      tmp_i2 = Pickup_Team(param_1,param_2);
      break;
    case 6:
      tmp_i2 = Pickup_Powerup(param_1,param_2);
    }
    if (tmp_i2 != 0) {
LAB_00083c5e:
      G_LogPrintf("Item: %i %s\n",*param_2,**(uint32_t **)(param_1 + 0x33c));
      tmp_u3 = 0x16;
      if (*(int *)(param_1 + 0x308) != 0) {
        G_AddEvent(param_2,0x28,*(int *)(param_1 + 0x308));
        tmp_u3 = 0x17;
      }
      G_AddEvent(param_2,tmp_u3,*(uint32_t *)(param_1 + 0xa4));
      if (*(int *)(*(int *)(param_1 + 0x33c) + 0x24) == 5) {
        tmp_i6 = nitrox_TempEventFromQueue(param_1 + 0x18,0x18);
        tmp_u3 = *(uint32_t *)(param_1 + 0xa4);
        *(uint *)(tmp_i6 + 0x128) = *(uint *)(tmp_i6 + 0x128) | 0x20;
        *(uint32_t *)(tmp_i6 + 0xbc) = tmp_u3;
      }
      G_UseTargets(param_1,param_2);
      if (tmp_i2 == 0x3e6) {
        tmp_pi1 = (int *)(param_1 + 0xf4);
        *tmp_pi1 = *tmp_pi1 + -1;
        if (*tmp_pi1 != 0) {
          *(uint32_t *)(param_1 + 0x368) = 1;
          trap_LinkEntity(param_1);
          tmp_i2 = param_2[100];
          goto LAB_00083b56;
        }
        tmp_u4 = *(uint *)(param_1 + 0x1b0);
        if ((tmp_u4 & 0x1000) != 0) goto LAB_00083cda;
        *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 1;
        *(uint *)(param_1 + 0x1b0) = tmp_u4 | 0x1000000;
        *(uint32_t *)(param_1 + 0x14c) = 0;
LAB_00083d07:
        tmp_pc5 = RespawnItem;
        local_20 = tmp_i2 * 1000 + g_unk_00abe908;
      }
      else {
        tmp_u4 = *(uint *)(param_1 + 0x1b0);
        if ((tmp_u4 & 0x1000) != 0) {
LAB_00083cda:
          *(uint32_t *)(param_1 + 0x1c4) = 1;
        }
        *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 1;
        *(uint *)(param_1 + 0x1b0) = tmp_u4 | 0x1000000;
        *(uint32_t *)(param_1 + 0x14c) = 0;
        if (0 < tmp_i2) goto LAB_00083d07;
        tmp_pc5 = (void *)0x0;
        local_20 = 0;
      }
      *(void **)(param_1 + 0x2a4) = tmp_pc5;
      *(int *)(param_1 + 0x29c) = local_20;
      trap_LinkEntity(param_1);
    }
  }
_L505:
  tmp_i2 = param_2[100];
LAB_00083b56:
  if (*(int *)(tmp_i2 + 0x66c) == 2) {
    *(uint32_t *)(tmp_i2 + 0x66c) = 0;
  }
  return;
}

void Touch_Item(int param_1,uint32_t *param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint tmp_u4;
  void *tmp_pc5;
  int tmp_i6;
  int tmp_i7;
  int local_20;
  
  if (*(int *)(param_1 + 0x368) == 0) {
    return;
  }
  *(uint32_t *)(param_1 + 0x368) = 0;
  tmp_i2 = param_2[100];
  if (tmp_i2 == 0) {
    return;
  }
  if ((int)param_2[0xb2] < 1) {
    return;
  }
  if ((*(uint *)(tmp_i2 + 0x68) & 0x800000) != 0) {
    return;
  }
  if ((*(int *)(*(int *)(param_1 + 0x33c) + 0x24) == 3) &&
     (((((g_medics[0xc] & 1) != 0 || ((*(uint *)(tmp_i2 + 0x68) & 0x200000) != 0)) &&
       (tmp_i6 = *(int *)(param_1 + 0x218), tmp_i6 != 0)) &&
      ((*(int *)(tmp_i6 + 400) != 0 && (param_2[0x2b] == *(int *)(tmp_i6 + 0xac))))))) {
    return;
  }
  tmp_i2 = BG_CanItemBeGrabbed(param_1,tmp_i2,tmp_i2 + 0xed0,*(uint32_t *)(tmp_i2 + 3000));
  if (tmp_i2 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0x2d0) != 0) {
    if (9 < *(uint *)(param_1 + 0xc)) {
      return;
    }
    if ((1 << ((byte)*(uint *)(param_1 + 0xc) & 0x1f) & 0x301U) == 0) {
      return;
    }
  }
  tmp_i2 = *(int *)(param_1 + 0x33c);
  tmp_i6 = *(int *)(tmp_i2 + 0x24);
  if (((GHIDRA_FIELD(g_gamestate, 12, 4) != 0) && (2 < tmp_i6 - 1U)) && (tmp_i6 != 6)) {
    return;
  }
  switch(tmp_i6) {
  default:
    return;
  case 1:
    tmp_i2 = Pickup_Weapon(param_1,param_2);
    break;
  case 2:
    tmp_i6 = param_2[100];
    if (g_unk_00abe908 - *(int *)(tmp_i6 + 0xfe8) < 1000) {
      return;
    }
    tmp_i7 = *(int *)(param_1 + 0xf4);
    if (tmp_i7 == 0) {
      tmp_i7 = 1;
    }
    if (*(int *)(tmp_i2 + 0x28) == 0xc) {
      BG_AddMagicAmmo(tmp_i6,tmp_i6 + 0xed0,*(uint32_t *)(tmp_i6 + 3000),
                      *(int *)(param_1 + 0x2e4) * tmp_i7);
      if (*(int *)(param_1 + 0xf4) == 2) goto LAB_000841e2;
LAB_000842e1:
      tmp_i2 = -1;
    }
    else {
      tmp_i6 = *(int *)(param_1 + 0x2e4);
      if (tmp_i6 == 0) {
        tmp_i6 = *(int *)(tmp_i2 + 0x20) * tmp_i7;
      }
      Add_Ammo(param_2,*(int *)(tmp_i2 + 0x28),tmp_i6,0);
      if (*(int *)(param_1 + 0xf4) != 2) goto LAB_000842e1;
LAB_000841e2:
      tmp_i2 = 0x3e6;
    }
    goto LAB_0008405e;
  case 3:
    tmp_i2 = Pickup_Health(param_1,param_2);
    break;
  case 5:
    tmp_i2 = Pickup_Team(param_1,param_2);
    break;
  case 6:
    tmp_i2 = Pickup_Powerup(param_1,param_2);
  }
  if (tmp_i2 == 0) {
    return;
  }
LAB_0008405e:
  G_LogPrintf("Item: %i %s\n",*param_2,**(uint32_t **)(param_1 + 0x33c));
  tmp_u3 = 0x16;
  if (*(int *)(param_1 + 0x308) != 0) {
    G_AddEvent(param_2,0x28,*(int *)(param_1 + 0x308));
    tmp_u3 = 0x17;
  }
  G_AddEvent(param_2,tmp_u3,*(uint32_t *)(param_1 + 0xa4));
  if (*(int *)(*(int *)(param_1 + 0x33c) + 0x24) == 5) {
    tmp_i6 = nitrox_TempEventFromQueue(param_1 + 0x18,0x18);
    tmp_u3 = *(uint32_t *)(param_1 + 0xa4);
    *(uint *)(tmp_i6 + 0x128) = *(uint *)(tmp_i6 + 0x128) | 0x20;
    *(uint32_t *)(tmp_i6 + 0xbc) = tmp_u3;
  }
  G_UseTargets(param_1,param_2);
  if (tmp_i2 == 0x3e6) {
    tmp_pi1 = (int *)(param_1 + 0xf4);
    *tmp_pi1 = *tmp_pi1 + -1;
    if (*tmp_pi1 != 0) {
      *(uint32_t *)(param_1 + 0x368) = 1;
      trap_LinkEntity(param_1);
      return;
    }
    tmp_u4 = *(uint *)(param_1 + 0x1b0);
    if ((tmp_u4 & 0x1000) != 0) goto LAB_000840da;
    *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 1;
    *(uint *)(param_1 + 0x1b0) = tmp_u4 | 0x1000000;
    *(uint32_t *)(param_1 + 0x14c) = 0;
  }
  else {
    tmp_u4 = *(uint *)(param_1 + 0x1b0);
    if ((tmp_u4 & 0x1000) != 0) {
LAB_000840da:
      *(uint32_t *)(param_1 + 0x1c4) = 1;
    }
    *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 1;
    *(uint *)(param_1 + 0x1b0) = tmp_u4 | 0x1000000;
    *(uint32_t *)(param_1 + 0x14c) = 0;
    if (tmp_i2 < 1) {
      tmp_pc5 = (void *)0x0;
      local_20 = 0;
      goto LAB_00084122;
    }
  }
  tmp_pc5 = RespawnItem;
  local_20 = tmp_i2 * 1000 + g_unk_00abe908;
LAB_00084122:
  *(void **)(param_1 + 0x2a4) = tmp_pc5;
  *(int *)(param_1 + 0x29c) = local_20;
  trap_LinkEntity(param_1);
  return;
}

void mg42_use(uint32_t *param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  
  tmp_i2 = param_1[0x60] * 0x600;
  tmp_pi1 = (int *)(g_entities + tmp_i2 + 400);
  if (*tmp_pi1 != 0) {
    *(uint32_t *)(*tmp_pi1 + 0x140) = 0;
    param_1[0x60] = *param_1;
    param_1[0x23] = *param_1;
    *(uint32_t *)(*tmp_pi1 + 0x410) = 0;
    *(uint32_t *)(g_entities + tmp_i2 + 0x368) = 0;
    *(uint32_t *)(*(int *)(param_2 + 400) + 0x51c) = param_1[0x135];
    param_1[0x134] = *(uint32_t *)(*tmp_pi1 + 0x2c);
    *(uint32_t *)(g_entities + tmp_i2 + 0x4d0) = *(uint32_t *)(*tmp_pi1 + 0x2c);
  }
  trap_LinkEntity(param_1);
  return;
}

void misc_spawner_use(int param_1)
{
  *(void **)(param_1 + 0x2a4) = misc_spawner_think;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  trap_LinkEntity(param_1);
  return;
}

void Use_Shooter(int param_1)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  long double tmp_l5;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i1 = *(int *)(param_1 + 0x2ec);
  if (tmp_i1 == 0) {
    local_40 = *(float *)(param_1 + 0x270);
    tmp_i1 = *(int *)(param_1 + 0xe8);
    local_3c = *(float *)(param_1 + 0x274);
    local_38 = *(float *)(param_1 + 0x278);
  }
  else {
    local_40 = *(float *)(tmp_i1 + 0x168) - *(float *)(param_1 + 0x5c);
    local_3c = *(float *)(tmp_i1 + 0x16c) - *(float *)(param_1 + 0x60);
    local_38 = *(float *)(tmp_i1 + 0x170) - *(float *)(param_1 + 100);
    VectorNormalize(&local_40);
    tmp_i1 = *(int *)(param_1 + 0xe8);
  }
  if (tmp_i1 == 0x2a) {
    AimAtTarget(param_1);
    local_40 = *(float *)(param_1 + 0x68);
    local_3c = *(float *)(param_1 + 0x6c);
    local_38 = *(float *)(param_1 + 0x70);
  }
  PerpendicularVector(&local_34,&local_40);
  CrossProduct(&local_34,&local_40,&local_28);
  tmp_u4 = rand();
  tmp_f2 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
  tmp_f2 = (tmp_f2 + tmp_f2) * *(float *)(param_1 + 0x310);
  local_40 = local_34 * tmp_f2 + local_40;
  local_3c = local_30 * tmp_f2 + local_3c;
  local_38 = tmp_f2 * local_2c + local_38;
  tmp_u4 = rand();
  tmp_f2 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
  tmp_f2 = (tmp_f2 + tmp_f2) * *(float *)(param_1 + 0x310);
  local_40 = local_28 * tmp_f2 + local_40;
  local_3c = local_24 * tmp_f2 + local_3c;
  local_38 = tmp_f2 * local_20 + local_38;
  VectorNormalize(&local_40);
  tmp_i1 = *(int *)(param_1 + 0xe8);
  if (tmp_i1 == 5) {
    fire_rocket(param_1,param_1 + 0x5c,&local_40,5);
    *(float *)(param_1 + 0x24) =
         (float)(int)ROUND(*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x24));
    *(float *)(param_1 + 0x28) =
         (float)(int)ROUND(*(float *)(param_1 + 0x28) + *(float *)(param_1 + 0x28));
    *(float *)(param_1 + 0x2c) =
         (float)(int)ROUND(*(float *)(param_1 + 0x2c) + *(float *)(param_1 + 0x2c));
  }
  else if (tmp_i1 == 0x2a) {
    tmp_i1 = param_1 + 0x68;
    AimAtTarget(param_1);
    tmp_f2 = local_40;
    tmp_l5 = (long double)VectorLength(tmp_i1);
    tmp_f3 = local_3c;
    local_40 = (float)(tmp_l5 * (long double)tmp_f2);
    tmp_l5 = (long double)VectorLength(tmp_i1);
    tmp_f2 = local_38;
    local_3c = (float)(tmp_l5 * (long double)tmp_f3);
    tmp_l5 = (long double)VectorLength(tmp_i1);
    local_38 = (float)(tmp_l5 * (long double)tmp_f2);
    fire_mortar(param_1,param_1 + 0x5c,&local_40);
  }
  else if (tmp_i1 == 4) {
    local_40 = local_40 * 700.0;
    local_3c = local_3c * 700.0;
    local_38 = local_38 * 700.0;
    fire_grenade(param_1,param_1 + 0x5c,&local_40,4);
  }
  G_AddEvent(param_1,0x21,0);
  return;
}

void mg42_die(uint32_t *param_1,uint32_t param_2,int param_3)
{
  int *tmp_pi1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  int local_78;
  uint8_t local_54 [4];
  int local_50;
  
  tmp_pu2 = (uint32_t *)param_1[0xba];
  if ((uint32_t *)param_1[0xba] == (uint32_t *)0x0) {
    tmp_pu2 = param_1;
  }
  if (*(int *)(param_3 + 400) == 0) {
    local_78 = tmp_pu2[0x60];
    tmp_pu2[0x80] = 0xffffffff;
  }
  else {
    local_78 = tmp_pu2[0x60];
    tmp_pu2[0x80] = *(uint32_t *)(*(int *)(param_3 + 400) + 3000);
  }
  if ((int)param_1[0xb2] < 1) {
    tmp_pu2[0x2c] = 2;
    tmp_pu2[0xb3] = 0;
    tmp_pu2[0xb2] = 0;
    tmp_pu2[2] = 0x2000;
    param_1[0xb2] = 0;
  }
  param_1[0xb3] = 0;
  tmp_i3 = local_78 * 0x600;
  tmp_pi1 = (int *)(g_entities + tmp_i3 + 400);
  if (*tmp_pi1 != 0) {
    trap_Trace(local_54,tmp_i3 + 0x93e608,tmp_i3 + 0x93e5d4,tmp_i3 + 0x93e5e0,tmp_i3 + 0x93e608,
               *(uint32_t *)(g_entities + tmp_i3),&g_unk_02010001);
    if (local_50 != 0) {
      *(uint32_t *)(*tmp_pi1 + 0x14) = *(uint32_t *)(g_entities + tmp_i3 + 0x330);
      *(uint32_t *)(*tmp_pi1 + 0x18) = *(uint32_t *)(g_entities + tmp_i3 + 0x334);
      *(uint32_t *)(*tmp_pi1 + 0x1c) = *(uint32_t *)(g_entities + tmp_i3 + 0x338);
      *(uint32_t *)(g_entities + tmp_i3 + 0x168) = *(uint32_t *)(g_entities + tmp_i3 + 0x330);
      *(uint32_t *)(g_entities + tmp_i3 + 0x16c) = *(uint32_t *)(g_entities + tmp_i3 + 0x334);
      *(uint32_t *)(g_entities + tmp_i3 + 0x170) = *(uint32_t *)(g_entities + tmp_i3 + 0x338);
      *(uint32_t *)(g_entities + tmp_i3 + 0x14c) = 0x4000000;
    }
    local_78 = local_78 * 0x600;
    tmp_pi1 = (int *)(g_entities + local_78 + 400);
    *(uint *)(*tmp_pi1 + 0x68) = *(uint *)(*tmp_pi1 + 0x68) & 0xffffffdf;
    *(uint32_t *)(*tmp_pi1 + 0x140) = 0;
    *(uint32_t *)(g_entities + local_78 + 0x368) = 0;
    param_1[0x60] = *param_1;
    param_1[0x23] = *param_1;
    *(uint32_t *)(*tmp_pi1 + 0x410) = 0;
    tmp_pu2[0x135] = 0;
    tmp_pu2[0x134] = 0;
    *(uint32_t *)(*tmp_pi1 + 0x2c) = *(uint32_t *)(g_entities + local_78 + 0x4d0);
    param_1[0xda] = 0;
    tmp_pu2[0xda] = 0;
  }
  trap_LinkEntity(param_1);
  return;
}

void mg42_spawn(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  char *tmp_pc3;
  int *tmp_pi4;
  int *tmp_pi5;
  int tmp_i6;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x94b19;
  if ((GHIDRA_FIELD(g_war, 12, 4) != 4) && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) {
    tmp_pi4 = (int *)G_Spawn();
    tmp_pi4[0x69] = (int)"misc_mg42base";
    if ((*(byte *)(param_1 + 0x1a8) & 2) == 0) {
      tmp_pi4[0x75] = 1;
      tmp_pi4[0x53] = 1;
      tmp_pi4[0x4a] = 0;
      tmp_pi4[0xb3] = 1;
      tmp_pi4[1] = 0;
      tmp_pi4[0xaf] = (int)mg42_die;
      tmp_pi4[0xea] = *(int *)(param_1 + 0x3a8);
      G_SetTargetName(tmp_pi4,*(uint32_t *)(param_1 + 600));
      tmp_i6 = G_ModelIndex("models/mapobjects/weapons/mg42b.md3");
      tmp_pi4[0x29] = tmp_i6;
    }
    else {
      tmp_pi4[0xb3] = 0;
    }
    tmp_pi4[0x4d] = -0x3f000000;
    tmp_pi4[0x4e] = -0x3f000000;
    tmp_pi4[0x4f] = -0x3f000000;
    tmp_pi4[0x50] = 0x41000000;
    tmp_pi4[0x51] = 0x41000000;
    tmp_pi4[0x52] = 0x42400000;
    local_28 = *(uint32_t *)(param_1 + 0x5c);
    local_24 = *(uint32_t *)(param_1 + 0x60);
    local_20 = *(float *)(param_1 + 100) - 24.0;
    G_SetOrigin(tmp_pi4,&local_28);
    tmp_pi4[0xc] = 0;
    tmp_pi4[0xd] = 0;
    tmp_pi4[0xe] = 0;
    tmp_pi4[0x3e] = 8;
    tmp_i6 = *(int *)(param_1 + 0x74);
    tmp_pi4[0x1d] = tmp_i6;
    tmp_i1 = *(int *)(param_1 + 0x78);
    tmp_pi4[0x1e] = tmp_i1;
    tmp_i2 = *(int *)(param_1 + 0x7c);
    tmp_pi4[0x1f] = tmp_i2;
    tmp_pi4[0xf] = tmp_i6;
    tmp_pi4[0x10] = tmp_i1;
    tmp_pi4[0x11] = tmp_i2;
    tmp_pi4[0x12] = tmp_i6;
    tmp_pi4[0x13] = tmp_i1;
    tmp_pi4[0x14] = tmp_i2;
    tmp_pi4[0xb2] = *(int *)(param_1 + 0x2c8);
    tmp_pc3 = *(char **)(param_1 + 0x254);
    tmp_pi4[0x95] = (int)tmp_pc3;
    if ((tmp_pc3 == (char *)0x0) || (*tmp_pc3 == '\0')) {
      tmp_pi4[0x16f] = -1;
    }
    else {
      tmp_i6 = BG_StringHashValue(tmp_pc3);
      tmp_pi4[0x16f] = tmp_i6;
    }
    tmp_pi4[0x80] = -1;
    trap_LinkEntity(tmp_pi4);
    G_SetEntState(tmp_pi4,*(uint32_t *)(param_1 + 0x458));
    tmp_pi5 = (int *)G_Spawn();
    tmp_pi5[0x69] = (int)&g_unk_0024c70b;
    tmp_pi5[0x170] = 0x1908e;
    tmp_pi5[0x75] = 1;
    tmp_pi5[0x53] = 0x40000000;
    tmp_pi5[0x4a] = 0;
    tmp_pi5[1] = 0x29;
    tmp_pi5[0xb2] = tmp_pi4[0xb2];
    tmp_i6 = G_ModelIndex("models/multiplayer/mg42/mg42.md3");
    tmp_pi5[0x80] = -1;
    tmp_pi5[0x29] = tmp_i6;
    local_28 = *(uint32_t *)(param_1 + 0x5c);
    local_24 = *(uint32_t *)(param_1 + 0x60);
    local_20 = *(float *)(param_1 + 100) + 24.0;
    G_SetOrigin(tmp_pi5,&local_28);
    tmp_pi5[0x4d] = -0x3e400000;
    tmp_pi5[0x4e] = -0x3e400000;
    tmp_pi5[0x4f] = -0x3f000000;
    tmp_pi5[0x50] = 0x41c00000;
    tmp_pi5[0x51] = 0x41c00000;
    tmp_pi5[0x52] = 0x42400000;
    tmp_pi5[0xd] = 0;
    tmp_pi5[0xe] = 0;
    tmp_pi5[0xc] = 3;
    tmp_i6 = *(int *)(param_1 + 0x74);
    tmp_pi5[0x1d] = tmp_i6;
    tmp_i1 = *(int *)(param_1 + 0x78);
    tmp_pi5[0x1e] = tmp_i1;
    tmp_i2 = *(int *)(param_1 + 0x7c);
    tmp_pi5[0x1f] = tmp_i2;
    tmp_pi5[0xf] = tmp_i6;
    tmp_pi5[0x10] = tmp_i1;
    tmp_pi5[0x11] = tmp_i2;
    tmp_pi5[0x12] = tmp_i6;
    tmp_pi5[0x13] = tmp_i1;
    tmp_pi5[0x14] = tmp_i2;
    tmp_pi5[0x20] = *(int *)(param_1 + 0x74);
    tmp_pi5[0x21] = *(int *)(param_1 + 0x78);
    tmp_i6 = *(int *)(param_1 + 0x7c);
    tmp_pi5[0xac] = (int)mg42_touch;
    tmp_pi5[0xa9] = (int)mg42_think;
    tmp_pi5[0xad] = (int)mg42_use;
    tmp_pi5[0x22] = tmp_i6;
    tmp_pi5[0xaf] = (int)mg42_die;
    tmp_i6 = g_unk_00abe908 + 100;
    tmp_pi5[0x93] = g_unk_00abe908 + 1000;
    tmp_pi5[0xa7] = tmp_i6;
    *tmp_pi5 = ((int)(tmp_pi5 + -0x24f928) >> 9) * -0x55555555;
    tmp_pi5[0xdb] = *(int *)(param_1 + 0x36c);
    tmp_pi5[0xdc] = *(int *)(param_1 + 0x370);
    tmp_pi5[0x1a] = *(int *)(param_1 + 0x36c);
    tmp_i6 = *(int *)(param_1 + 0x370);
    tmp_pi5[0xb3] = 1;
    tmp_pi5[0x1b] = tmp_i6;
    G_SetTargetName(tmp_pi5,*(uint32_t *)(param_1 + 600));
    tmp_pi5[0xb4] = *(int *)(param_1 + 0x2d0);
    tmp_pi5[0xff] = *(int *)(param_1 + 0x3fc);
    tmp_pc3 = *(char **)(param_1 + 0x254);
    tmp_pi5[0x95] = (int)tmp_pc3;
    if ((tmp_pc3 == (char *)0x0) || (*tmp_pc3 == '\0')) {
      tmp_pi5[0x16f] = -1;
    }
    else {
      tmp_i6 = BG_StringHashValue(tmp_pc3);
      tmp_pi5[0x16f] = tmp_i6;
    }
    tmp_i6 = *(int *)(param_1 + 0x1a8);
    tmp_pi5[0x135] = 0;
    tmp_pi5[0x6a] = tmp_i6;
    tmp_pi5[0xea] = *(int *)(param_1 + 0x3a8);
    G_SetEntState(tmp_pi5,*(uint32_t *)(param_1 + 0x458));
    if ((*(byte *)(param_1 + 0x1a8) & 2) == 0) {
      tmp_pi5[0xe2] = *tmp_pi4;
      tmp_pi4[0xba] = (int)tmp_pi5;
    }
    else {
      tmp_pi5[0xe2] = -1;
    }
    if ((*(byte *)(tmp_pi5 + 0x6a) & 1) != 0) {
      tmp_pi5[0x3f] = 1;
    }
    trap_LinkEntity(tmp_pi5);
    nitrox_AddEntityToEntityArray(&MG42Entities,tmp_pi5);
    UpdateGoalEntity(param_1,tmp_pi5);
  }
  G_FreeEntity(param_1);
  return;
}

void misc_firetrails_think(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  
  tmp_i1 = G_FindByTargetnameFast
                    (0,*(uint32_t *)(param_1 + 0x254),*(uint32_t *)(param_1 + 0x5bc));
  if (tmp_i1 == 0) {
    G_Error("can\'t find airplane with targetname \"%s\" for firetrails",
            *(uint32_t *)(param_1 + 0x254));
  }
  tmp_i2 = G_Spawn();
  *(char **)(tmp_i2 + 0x1a4) = "left_firetrail";
  *(uint32_t *)(tmp_i2 + 0x14c) = 0;
  *(uint32_t *)(tmp_i2 + 4) = 0x18;
  tmp_u3 = G_ModelIndex("models/ammo/rocket/rocket.md3");
  *(int *)(tmp_i2 + 0x440) = tmp_i1;
  *(uint32_t *)(tmp_i2 + 0xa4) = tmp_u3;
  Q_strncpyz(tmp_i2 + 0x400,"tag_engine1",0x40);
  *(void **)(tmp_i2 + 0x2b4) = firetrail_use;
  *(void **)(tmp_i2 + 0x344) = G_FreeEntity;
  G_SetTargetName(tmp_i2,*(uint32_t *)(param_1 + 600));
  G_ProcessTagConnect(tmp_i2,1);
  trap_LinkEntity(tmp_i2);
  tmp_i2 = G_Spawn();
  *(char **)(tmp_i2 + 0x1a4) = "right_firetrail";
  *(uint32_t *)(tmp_i2 + 0x14c) = 0;
  *(uint32_t *)(tmp_i2 + 4) = 0x18;
  tmp_u3 = G_ModelIndex("models/ammo/rocket/rocket.md3");
  *(int *)(tmp_i2 + 0x440) = tmp_i1;
  *(uint32_t *)(tmp_i2 + 0xa4) = tmp_u3;
  Q_strncpyz(tmp_i2 + 0x400,"tag_engine2",0x40);
  *(void **)(tmp_i2 + 0x2b4) = firetrail_use;
  *(void **)(tmp_i2 + 0x344) = G_FreeEntity;
  G_SetTargetName(tmp_i2,*(uint32_t *)(param_1 + 600));
  G_ProcessTagConnect(tmp_i2,1);
  trap_LinkEntity(tmp_i2);
  return;
}

void misc_spawner_think(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = BG_FindItem(*(uint32_t *)(param_1 + 0x38c));
  tmp_i2 = Drop_Item(param_1,tmp_u1,0,0);
  if (tmp_i2 != 0) {
    return;
  }
  G_Printf("-----> WARNING <-------\n");
  tmp_u1 = vtos(param_1 + 0x168);
  G_Printf("misc_spawner used at %s failed to drop!\n",tmp_u1);
  return;
}

void mg42_touch(uint32_t *param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  float local_30;
  float local_2c;
  uint8_t local_24 [12];
  uint8_t local_18 [12];
  
  if ((param_1[0xda] != 0) && (*(int *)(param_2 + 0x368) != 0)) {
    *(uint32_t *)(*(int *)(param_2 + 400) + 0x410) = 3;
    *(uint32_t *)(*(int *)(param_2 + 400) + 0x414) = *param_1;
    AngleVectors(param_1 + 0xf,&local_30,local_24,local_18);
    tmp_f1 = (float)param_1[0x5a];
    tmp_f2 = (float)param_1[0x5b];
    tmp_f3 = *(float *)(param_2 + 0x170);
    trap_UnlinkEntity(param_2);
    *(float *)(*(int *)(param_2 + 400) + 0x14) = (float)(int)ROUND(local_30 * -36.0 + tmp_f1);
    *(float *)(*(int *)(param_2 + 400) + 0x18) = (float)(int)ROUND(local_2c * -36.0 + tmp_f2);
    *(float *)(*(int *)(param_2 + 400) + 0x1c) = (float)(int)ROUND(tmp_f3);
    BG_PlayerStateToEntityState(*(uint32_t *)(param_2 + 400),param_2,g_unk_00abe908,0);
    tmp_i4 = *(int *)(param_2 + 400);
    *(uint32_t *)(param_2 + 0x168) = *(uint32_t *)(tmp_i4 + 0x14);
    *(uint32_t *)(param_2 + 0x16c) = *(uint32_t *)(tmp_i4 + 0x18);
    *(uint32_t *)(param_2 + 0x170) = *(uint32_t *)(tmp_i4 + 0x1c);
    *(uint32_t *)(tmp_i4 + 0x24) = 0;
    *(uint32_t *)(tmp_i4 + 0x20) = 0;
    *(uint32_t *)(param_2 + 0x28) = 0;
    *(uint32_t *)(param_2 + 0x24) = 0;
    trap_LinkEntity(param_2);
  }
  return;
}

void mg42_think(uint32_t *param_1)
{
  uint8_t *tmp_pu1;
  int *tmp_pi2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  int tmp_i7;
  float *pfVar8;
  float *pfVar9;
  long double tmp_l10;
  long double tmp_l11;
  long double tmp_l12;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  uint8_t local_34 [12];
  uint8_t local_28 [20];
  uint32_t uStack_14;
  
  uStack_14 = 0x95999;
  if (GHIDRA_FIELD(g_gamestate, 12, 4) != 3) {
    local_44 = 0.0;
    tmp_i7 = param_1[0x60];
    local_48 = 0.0;
    local_4c = 0.0;
    if (g_unk_00abe908 < (int)param_1[0x93]) {
      BG_EvaluateTrajectory(param_1 + 0xc,g_unk_00abe908,param_1 + 0xf,0,0);
    }
    if (*(int *)(g_entities + tmp_i7 * 0x600 + 400) == 0) {
      tmp_i6 = param_1[0x135];
    }
    else {
      tmp_i6 = *(int *)(*(int *)(g_entities + tmp_i7 * 0x600 + 400) + 0x51c);
      param_1[0x135] = tmp_i6;
    }
    if ((float)tmp_i6 < 1500.0) {
      if (((int)param_1[0xe5] < g_unk_00abe908) && ((param_1[2] & 0x2800) == 0x2800)) {
        param_1[2] = param_1[2] & 0xffffd7ff;
        param_1[0xe5] = 0;
      }
    }
    else {
      param_1[2] = param_1[2] | 0x2800;
      if ((int)param_1[0xe5] < g_unk_00abe908) {
        if (*(int *)(g_entities + tmp_i7 * 0x600 + 400) == 0) {
          param_1[0xe5] = g_unk_00abe908 + 2000;
        }
        else {
          param_1[0xe5] = g_unk_00abe908 + *(int *)(*(int *)(g_entities + tmp_i7 * 0x600 + 400) + 0x2c)
          ;
        }
      }
    }
    tmp_i6 = tmp_i7 * 0x600;
    tmp_pi2 = (int *)(g_entities + tmp_i6 + 400);
    if (*tmp_pi2 != 0) {
      local_4c = (float)param_1[0x5a] - *(float *)(g_entities + tmp_i6 + 0x168);
      local_48 = (float)param_1[0x5b] - *(float *)(g_entities + tmp_i6 + 0x16c);
      local_44 = (float)param_1[0x5c] - *(float *)(g_entities + tmp_i6 + 0x170);
      tmp_l10 = (long double)VectorLength(&local_4c);
      if (((tmp_l10 < (long double)128.0) && (*(int *)(g_entities + tmp_i6 + 0x368) != 0)) &&
         (0 < *(int *)(g_entities + tmp_i6 + 0x2c8))) {
        *(uint *)(*tmp_pi2 + 0xc) = *(uint *)(*tmp_pi2 + 0xc) & 0xfffffffe;
        param_1[0xda] = 1;
        *(uint32_t *)(*tmp_pi2 + 0x140) = 1;
        if ((param_1[0xda] != 0) && (*(int *)(g_entities + tmp_i6 + 0x368) != 0)) {
          param_1[0x12] = *(float *)(*tmp_pi2 + 0xb0) - (float)param_1[0xf];
          param_1[0x13] = *(float *)(*tmp_pi2 + 0xb4) - (float)param_1[0x10];
          param_1[0x14] = *(float *)(*tmp_pi2 + 0xb8) - (float)param_1[0x11];
          pfVar8 = (float *)(param_1 + 0x12);
          do {
            pfVar9 = pfVar8 + 1;
            tmp_l10 = (long double)AngleNormalize180(*pfVar8);
            *pfVar8 = (float)tmp_l10;
            pfVar8 = pfVar9;
          } while (pfVar9 != (float *)(param_1 + 0x15));
          tmp_f3 = (float)param_1[0x12];
          param_1[0x12] = tmp_f3 * 20.0;
          tmp_f4 = (float)param_1[0x13];
          param_1[0x13] = tmp_f4 * 20.0;
          tmp_f5 = (float)param_1[0x14];
          param_1[0x14] = tmp_f5 * 20.0;
          tmp_i6 = g_unk_00abe908;
          param_1[0xe] = 0x32;
          param_1[0xd] = tmp_i6;
          param_1[0x12] = (float)(int)ROUND(tmp_f3 * 20.0);
          param_1[0x13] = (float)(int)ROUND(tmp_f4 * 20.0);
          param_1[0x14] = (float)(int)ROUND(tmp_f5 * 20.0);
        }
        tmp_i7 = tmp_i7 * 0x600;
        tmp_pu1 = g_entities + tmp_i7;
        tmp_i6 = g_unk_00abe908 + 0x32;
        param_1[0x93] = g_unk_00abe908 + 1000;
        param_1[0xa7] = tmp_i6;
        AngleVectors(param_1 + 0xf,&local_40,local_34,local_28);
        tmp_f3 = (float)param_1[0x5a];
        tmp_f4 = (float)param_1[0x5b];
        tmp_pi2 = (int *)(g_entities + tmp_i7 + 400);
        tmp_f5 = *(float *)(g_entities + tmp_i7 + 0x170);
        trap_UnlinkEntity(tmp_pu1);
        *(float *)(*tmp_pi2 + 0x14) = (float)(int)ROUND(local_40 * -36.0 + tmp_f3);
        *(float *)(*tmp_pi2 + 0x18) = (float)(int)ROUND(local_3c * -36.0 + tmp_f4);
        *(float *)(*tmp_pi2 + 0x1c) = (float)(int)ROUND(tmp_f5);
        BG_PlayerStateToEntityState(*tmp_pi2,tmp_pu1,g_unk_00abe908,0);
        tmp_i6 = *tmp_pi2;
        *(uint32_t *)(g_entities + tmp_i7 + 0x168) = *(uint32_t *)(tmp_i6 + 0x14);
        *(uint32_t *)(g_entities + tmp_i7 + 0x16c) = *(uint32_t *)(tmp_i6 + 0x18);
        *(uint32_t *)(g_entities + tmp_i7 + 0x170) = *(uint32_t *)(tmp_i6 + 0x1c);
        *(uint32_t *)(tmp_i6 + 0x24) = 0;
        *(uint32_t *)(tmp_i6 + 0x20) = 0;
        *(uint32_t *)(g_entities + tmp_i7 + 0x28) = 0;
        *(uint32_t *)(g_entities + tmp_i7 + 0x24) = 0;
        trap_LinkEntity(tmp_pu1);
        return;
      }
    }
    param_1[0xda] = 0;
    tmp_pi2 = (int *)(g_entities + tmp_i7 * 0x600 + 400);
    if (*tmp_pi2 == 0) {
      tmp_i7 = param_1[0x134];
    }
    else {
      *(uint32_t *)(*tmp_pi2 + 0x140) = 0;
      *(uint32_t *)(*tmp_pi2 + 0x410) = 0;
      *(uint32_t *)(g_entities + tmp_i7 * 0x600 + 0x368) = 0;
      tmp_i7 = *(int *)(*tmp_pi2 + 0x2c);
      param_1[0x134] = tmp_i7;
    }
    if (param_1[0x135] != 0) {
      tmp_i6 = (int)ROUND((float)(int)param_1[0x135] - 30.0);
      if (tmp_i6 < 0) {
        tmp_i6 = 0;
      }
      param_1[0x135] = tmp_i6;
    }
    if (tmp_i7 != 0) {
      tmp_i7 = tmp_i7 + -0x32;
      if (tmp_i7 < 0) {
        tmp_i7 = 0;
      }
      param_1[0x134] = tmp_i7;
    }
    param_1[0x60] = *param_1;
    param_1[0x23] = *param_1;
    if (g_unk_00abe908 < (int)param_1[0x93]) {
      local_4c = (float)param_1[0x1d];
      local_48 = (float)param_1[0x1e];
      tmp_l10 = (long double)local_48;
      local_44 = (float)param_1[0x1f];
      if ((local_4c < 0.0) && (local_4c < -(float)param_1[0xdc])) {
        local_4c = -(float)param_1[0xdc];
      }
      if ((0.0 < local_4c) && ((float)param_1[0xdc] * 0.5 < local_4c)) {
        local_4c = (float)param_1[0xdc] * 0.5;
      }
      tmp_l11 = tmp_l10 - tmp_l10;
      if (tmp_l11 < (long double)-180.0) {
        tmp_l11 = tmp_l11 + (long double)360.0;
      }
      tmp_l12 = (long double)(float)param_1[0xdb];
      if (tmp_l12 < ABS(tmp_l11)) {
        if (tmp_l11 <= (long double)0) {
          tmp_l10 = tmp_l12 + tmp_l10;
        }
        else {
          tmp_l10 = tmp_l10 - tmp_l12;
        }
        tmp_l10 = (long double)AngleMod((float)tmp_l10);
        local_48 = (float)tmp_l10;
      }
      param_1[0x12] = local_4c - (float)param_1[0xf];
      param_1[0x13] = (float)(tmp_l10 - (long double)(float)param_1[0x10]);
      param_1[0x14] = local_44 - (float)param_1[0x11];
      pfVar8 = (float *)(param_1 + 0x12);
      do {
        pfVar9 = pfVar8 + 1;
        tmp_l10 = (long double)AngleNormalize180(*pfVar8);
        *pfVar8 = (float)tmp_l10;
        pfVar8 = pfVar9;
      } while (pfVar9 != (float *)(param_1 + 0x15));
      tmp_f3 = (float)param_1[0x12] * 20.0;
      param_1[0x12] = tmp_f3;
      tmp_f4 = (float)param_1[0x13] * 20.0;
      param_1[0x13] = tmp_f4;
      tmp_f5 = (float)param_1[0x14] * 20.0;
      param_1[0x14] = tmp_f5;
      tmp_i7 = g_unk_00abe908;
      param_1[0xe] = 0x32;
      param_1[0xd] = tmp_i7;
    }
    else {
      tmp_f3 = (float)param_1[0x12];
      tmp_f4 = (float)param_1[0x13];
      tmp_f5 = (float)param_1[0x14];
    }
    param_1[0xa7] = g_unk_00abe908 + 0x32;
    param_1[0x12] = (float)(int)ROUND(tmp_f3);
    param_1[0x13] = (float)(int)ROUND(tmp_f4);
    param_1[0x14] = (float)(int)ROUND(tmp_f5);
  }
  return;
}

void SP_info_camp(int param_1)
{
  G_SetOrigin(param_1,param_1 + 0x5c);
  return;
}

void SP_info_null(int param_1)
{
  if ((*(char **)(param_1 + 600) == (char *)0x0) || (**(char **)(param_1 + 600) == '\0')) {
    G_FreeEntity(param_1);
  }
  *(void **)(param_1 + 0x2a4) = G_FreeEntity;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 200;
  return;
}

void SP_info_notnull(int param_1)
{
  G_SetOrigin(param_1,param_1 + 0x5c);
  return;
}

void SP_misc_teleporter_dest(void)
{
  return;
}

void SP_misc_gamemodel(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t local_84;
  int local_80;
  int local_7c;
  uint8_t local_78 [4];
  int local_74;
  int local_70;
  int local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint8_t local_5c [76];
  
  if (((*(int *)(param_1 + 0x3ac) == 0) && (*(int *)(param_1 + 600) == 0)) &&
     (*(int *)(param_1 + 0x1a8) == 0)) {
    G_FreeEntity(param_1);
  }
  else {
    *(uint32_t *)(param_1 + 4) = 0x12;
    tmp_u2 = G_ModelIndex(*(uint32_t *)(param_1 + 0x1b4));
    *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
    tmp_u2 = G_SkinIndex(*(uint32_t *)(param_1 + 0x348));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u2;
    if ((*(byte *)(param_1 + 0x1a8) & 2) != 0) {
      G_SpawnIntExt("frames",&g_unk_0024bfa6,&local_74,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x9c);
      G_SpawnIntExt("start",&g_unk_0024bfa6,&local_70,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x9d);
      G_SpawnIntExt(&g_unk_00248da5,&g_unk_0024a16e,&local_6c,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x9e);
      G_SpawnStringExt("reverse",&g_unk_0026ea14,local_78,
                       "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x9f);
      if (local_74 == 0) {
        G_Error("\'misc_model\' with ANIMATE spawnflag set has \'frames\' set to 0\n");
      }
      *(int *)(param_1 + 0xf0) = local_74;
      tmp_i3 = rand();
      *(uint32_t *)(param_1 + 0xa0) = 0;
      *(int *)(param_1 + 0xec) = local_70 + 1;
      *(int *)(param_1 + 0xb0) = tmp_i3 % *(int *)(param_1 + 0xf0);
      *(int *)(param_1 + 0xe8) = (int)ROUND(1000.0 / (float)local_6c);
      *(uint32_t *)(param_1 + 0x108) = 0;
    }
    if (*(int *)(param_1 + 0x1b4) != 0) {
      COM_StripExtension(*(int *)(param_1 + 0x1b4),local_5c);
      Q_strcat(local_5c,0x40,&g_unk_0024c792);
      tmp_u2 = trap_LoadTag(local_5c);
      *(uint32_t *)(param_1 + 0x498) = tmp_u2;
    }
    tmp_i3 = G_SpawnVectorExt("modelscale_vec","1 1 1",&local_68,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0xb8);
    if ((tmp_i3 == 0) &&
       (tmp_i3 = G_SpawnFloatExt("modelscale",&g_unk_00258b23,&local_84,
                                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0xb9),
       tmp_i3 != 0)) {
      local_68 = local_84;
      local_64 = local_68;
      local_60 = local_68;
    }
    G_SpawnIntExt("trunk",&g_unk_0024bfa6,&local_80,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0xbe);
    tmp_i3 = G_SpawnIntExt("trunkhight",&g_unk_0024bfa6,&local_7c,
                          "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0xbf);
    if (tmp_i3 == 0) {
      local_7c = 0x100;
    }
    if (local_80 != 0) {
      tmp_f1 = (float)local_80 * 0.5;
      *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 0x200;
      *(uint32_t *)(param_1 + 0x1d4) = 1;
      *(uint32_t *)(param_1 + 0x14c) = 1;
      *(uint32_t *)(param_1 + 0x13c) = 0;
      *(float *)(param_1 + 0x134) = -tmp_f1;
      *(float *)(param_1 + 0x138) = -tmp_f1;
      *(float *)(param_1 + 0x140) = tmp_f1;
      *(float *)(param_1 + 0x144) = tmp_f1;
      *(float *)(param_1 + 0x148) = (float)local_7c;
    }
    *(uint32_t *)(param_1 + 0x80) = local_68;
    *(uint32_t *)(param_1 + 0x84) = local_64;
    *(uint32_t *)(param_1 + 0x88) = local_60;
    G_SetOrigin(param_1,param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
    if ((*(byte *)(param_1 + 0x1a8) & 1) != 0) {
      *(uint32_t *)(param_1 + 0x30) = 1;
    }
    trap_LinkEntity(param_1);
  }
  return;
}

void SP_misc_vis_dummy(int param_1)
{
  uint32_t tmp_u1;
  
  if (*(int *)(param_1 + 0x254) != 0) {
    *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 4;
    G_SetOrigin(param_1,param_1 + 0x5c);
    trap_LinkEntity(param_1);
    *(void **)(param_1 + 0x2a4) = locateMaster;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 1000;
    return;
  }
  tmp_u1 = vtos(param_1 + 0x168);
  G_Printf("No target specified for misc_vis_dummy at %s\n",tmp_u1);
  G_FreeEntity(param_1);
  return;
}

void SP_misc_vis_dummy_multiple(int param_1)
{
  uint32_t tmp_u1;
  
  if (*(int *)(param_1 + 600) != 0) {
    *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 0x400;
    G_SetOrigin(param_1,param_1 + 0x5c);
    trap_LinkEntity(param_1);
    return;
  }
  tmp_u1 = vtos(param_1 + 0x168);
  G_Printf("misc_vis_dummy_multiple needs a targetname at %s\n",tmp_u1);
  G_FreeEntity(param_1);
  return;
}

void SP_misc_portal_surface(int param_1)
{
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x138) = 0;
  *(uint32_t *)(param_1 + 0x134) = 0;
  *(uint32_t *)(param_1 + 0x148) = 0;
  *(uint32_t *)(param_1 + 0x144) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0;
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0x128) = 0x40;
  *(uint32_t *)(param_1 + 4) = 6;
  if (*(int *)(param_1 + 0x254) != 0) {
    *(void **)(param_1 + 0x2a4) = locateCamera;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
    return;
  }
  *(uint32_t *)(param_1 + 0x68) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x6c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x70) = *(uint32_t *)(param_1 + 100);
  return;
}

void SP_misc_portal_camera(int param_1)
{
  float local_10 [2];
  
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x138) = 0;
  *(uint32_t *)(param_1 + 0x134) = 0;
  *(uint32_t *)(param_1 + 0x148) = 0;
  *(uint32_t *)(param_1 + 0x144) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0;
  trap_LinkEntity(param_1);
  G_SpawnFloatExt(&g_unk_0024c7c8,&g_unk_0024bfa6,local_10,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x15a);
  *(int *)(param_1 + 0xac) = (int)ROUND((local_10[0] / 360.0) * 256.0);
  return;
}

void SP_shooter_mortar(int param_1)
{
  float tmp_f1;
  double tmp_d2;
  
  *(uint32_t *)(param_1 + 0xe8) = 0x2a;
  *(void **)(param_1 + 0x2b4) = Use_Shooter;
  G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  if (*(float *)(param_1 + 0x310) == 0.0) {
    tmp_f1 = 0.017452406;
  }
  else {
    tmp_d2 = sin((double)((*(float *)(param_1 + 0x310) * 3.1415927) / 180.0));
    tmp_f1 = (float)tmp_d2;
  }
  *(float *)(param_1 + 0x310) = tmp_f1;
  if (*(int *)(param_1 + 0x254) != 0) {
    *(void **)(param_1 + 0x2a4) = InitShooter_Finish;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 500;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_shooter_rocket(int param_1)
{
  float tmp_f1;
  double tmp_d2;
  
  *(uint32_t *)(param_1 + 0xe8) = 5;
  *(void **)(param_1 + 0x2b4) = Use_Shooter;
  G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  if (*(float *)(param_1 + 0x310) == 0.0) {
    tmp_f1 = 0.017452406;
  }
  else {
    tmp_d2 = sin((double)((*(float *)(param_1 + 0x310) * 3.1415927) / 180.0));
    tmp_f1 = (float)tmp_d2;
  }
  *(float *)(param_1 + 0x310) = tmp_f1;
  if (*(int *)(param_1 + 0x254) != 0) {
    *(void **)(param_1 + 0x2a4) = InitShooter_Finish;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 500;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_shooter_grenade(int param_1)
{
  float tmp_f1;
  double tmp_d2;
  
  *(uint32_t *)(param_1 + 0xe8) = 4;
  *(void **)(param_1 + 0x2b4) = Use_Shooter;
  G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  if (*(float *)(param_1 + 0x310) == 0.0) {
    tmp_f1 = 0.017452406;
  }
  else {
    tmp_d2 = sin((double)((*(float *)(param_1 + 0x310) * 3.1415927) / 180.0));
    tmp_f1 = (float)tmp_d2;
  }
  *(float *)(param_1 + 0x310) = tmp_f1;
  if (*(int *)(param_1 + 0x254) != 0) {
    *(void **)(param_1 + 0x2a4) = InitShooter_Finish;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 500;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_corona(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  float local_10 [2];
  
  if (((*(int *)(param_1 + 0x3ac) == 0) && (*(int *)(param_1 + 600) == 0)) &&
     (*(int *)(param_1 + 0x1a8) == 0)) {
    G_FreeEntity(param_1);
    return;
  }
  *(uint32_t *)(param_1 + 4) = 0x10;
  if (*(float *)(param_1 + 0x34c) <= 0.0) {
    tmp_f1 = *(float *)(param_1 + 0x350);
    if (0.0 < tmp_f1) {
      tmp_f1 = tmp_f1 * 255.0;
      tmp_f3 = *(float *)(param_1 + 0x354) * 255.0;
    }
    else {
      if (*(float *)(param_1 + 0x354) <= 0.0) {
        tmp_f2 = 255.0;
        tmp_u4 = 0xffffff;
        tmp_f3 = tmp_f2;
        tmp_f1 = tmp_f2;
        goto LAB_00096d35;
      }
      tmp_f1 = tmp_f1 * 255.0;
      tmp_f3 = *(float *)(param_1 + 0x354) * 255.0;
    }
  }
  else {
    tmp_f1 = *(float *)(param_1 + 0x350) * 255.0;
    tmp_f3 = *(float *)(param_1 + 0x354) * 255.0;
  }
  tmp_f2 = *(float *)(param_1 + 0x34c) * 255.0;
  tmp_u4 = (int)ROUND(tmp_f3) << 0x10 | (int)ROUND(tmp_f1) << 8 | (int)ROUND(tmp_f2);
LAB_00096d35:
  *(float *)(param_1 + 0x34c) = tmp_f2;
  *(float *)(param_1 + 0x350) = tmp_f1;
  *(uint *)(param_1 + 0x9c) = tmp_u4;
  *(float *)(param_1 + 0x354) = tmp_f3;
  G_SpawnFloatExt("scale",&g_unk_00258b23,local_10,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x211);
  *(int *)(param_1 + 0xf4) = (int)ROUND(local_10[0] * 255.0);
  *(void **)(param_1 + 0x2b4) = use_corona;
  if ((*(byte *)(param_1 + 0x1a8) & 1) != 0) {
    return;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_dlight(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  size_t tmp_s5;
  uint tmp_u6;
  uint32_t tmp_u7;
  int tmp_i8;
  char *__s;
  bool tmp_b9;
  uint32_t local_30;
  uint8_t local_2c [4];
  int local_28;
  int local_24;
  uint32_t local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0x96e9e;
  G_SpawnIntExt("offset",&g_unk_0024bfa6,&local_28,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x29f);
  G_SpawnIntExt("style",&g_unk_0024bfa6,&local_24,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x2a0);
  G_SpawnStringExt("sound",&g_unk_0026ea14,&local_30,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x2a1);
  G_SpawnIntExt("atten",&g_unk_0024bfa6,local_20,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x2a2);
  G_SpawnStringExt("shader",&g_unk_0026ea14,local_2c,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x2a3);
  tmp_i4 = G_SpawnStringExt("sound",&g_unk_0024bfa6,&local_30,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x2a5);
  if (tmp_i4 != 0) {
    tmp_u7 = G_SoundIndex(local_30);
    *(uint32_t *)(param_1 + 0x1f8) = tmp_u7;
  }
  __s = *(char **)(param_1 + 0x358);
  if ((__s == (char *)0x0) || (*__s == '\0')) {
    if (local_24 != 0) {
      if (local_24 < 1) {
        local_24 = 1;
      }
      if (0x13 < local_24) {
        local_24 = 0x13;
      }
      __s = *(char **)(local_24 * 4 + 0x2ba33c);
      *(char **)(param_1 + 0x358) = __s;
      goto LAB_00096fd2;
    }
    __s = "mmmaaa";
    tmp_s5 = 6;
    *(char **)(param_1 + 0x358) = "mmmaaa";
  }
  else {
LAB_00096fd2:
    tmp_s5 = strlen(__s);
  }
  *(size_t *)(param_1 + 0x2e4) = tmp_s5;
  *(uint32_t *)(param_1 + 0x360) = local_20[0];
  tmp_i4 = dlightstarttime;
  local_28 = local_28 % (int)tmp_s5;
  tmp_b9 = dlightstarttime == 0;
  *(void **)(param_1 + 0x2a4) = dlight_finish_spawning;
  *(int *)(param_1 + 0x2c8) = local_28;
  if (tmp_b9) {
    tmp_i4 = g_unk_00abe908 + 100;
    dlightstarttime = tmp_i4;
  }
  tmp_f1 = *(float *)(param_1 + 0x34c);
  *(int *)(param_1 + 0x29c) = tmp_i4;
  if (tmp_f1 <= 0.0) {
    tmp_f2 = *(float *)(param_1 + 0x350);
    if (tmp_f2 <= 0.0) {
      if (*(float *)(param_1 + 0x354) <= 0.0) {
        tmp_f1 = 255.0;
        tmp_u6 = 0xffffff;
        tmp_f3 = tmp_f1;
        tmp_f2 = tmp_f1;
      }
      else {
        tmp_f3 = *(float *)(param_1 + 0x354) * 255.0;
        tmp_f1 = tmp_f1 * 255.0;
        tmp_u6 = (int)ROUND(tmp_f2 * 255.0) << 8 | (int)ROUND(tmp_f3) << 0x10 | (int)ROUND(tmp_f1);
        tmp_f2 = tmp_f2 * 255.0;
      }
      goto LAB_000970a7;
    }
  }
  else {
    tmp_f2 = *(float *)(param_1 + 0x350);
  }
  tmp_f1 = tmp_f1 * 255.0;
  tmp_f3 = *(float *)(param_1 + 0x354) * 255.0;
  tmp_u6 = (int)ROUND(tmp_f3) << 0x10 | (int)ROUND(tmp_f2 * 255.0) << 8 | (int)ROUND(tmp_f1);
  tmp_f2 = tmp_f2 * 255.0;
LAB_000970a7:
  *(float *)(param_1 + 0x34c) = tmp_f1;
  *(float *)(param_1 + 0x350) = tmp_f2;
  *(float *)(param_1 + 0x354) = tmp_f3;
  tmp_i4 = (int)ROUND((float)(__s[local_28] + -0x61) * 41.666668);
  tmp_i8 = tmp_i4 + 3;
  if (-1 < tmp_i4) {
    tmp_i8 = tmp_i4;
  }
  *(uint *)(param_1 + 0x98) = tmp_u6 | (tmp_i8 >> 2) << 0x18;
  *(void **)(param_1 + 0x2b4) = use_dlight;
  if ((*(byte *)(param_1 + 0x1a8) & 2) == 0) {
    trap_LinkEntity(param_1);
  }
  return;
}

void Fire_Lead_Ext(uint32_t *param_1,uint32_t *param_2,float param_3,uint32_t param_4,
                  float *param_5,float *param_6,float *param_7,float *param_8,uint32_t param_9)

{
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  long double tmp_l6;
  long double tmp_l7;
  long double tmp_l8;
  uint local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [12];
  uint8_t local_48 [12];
  float local_3c;
  float local_38;
  float local_34;
  byte local_28;
  int local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x97269;
  local_70 = rand();
  local_70 = local_70 & 0xff;
  tmp_l6 = (long double)Q_crandom(&local_70);
  tmp_l7 = (long double)Q_crandom(&local_70);
  param_1[2] = param_1[2] | 0x20;
  param_2[2] = param_2[2] | 0x20;
  tmp_l7 = (long double)param_3 * tmp_l7;
  tmp_l8 = (long double)8192.0;
  tmp_l6 = (long double)(float)((long double)param_3 * tmp_l6);
  local_6c = (float)(tmp_l7 * (long double)*param_8 +
                    tmp_l6 * (long double)*param_7 +
                    tmp_l8 * (long double)*param_6 + (long double)*param_5);
  local_68 = (float)((long double)param_8[1] * tmp_l7 +
                    tmp_l6 * (long double)param_7[1] +
                    (long double)param_6[1] * tmp_l8 + (long double)param_5[1]);
  local_64 = (float)(tmp_l7 * (long double)param_8[2] +
                    (long double)param_7[2] * tmp_l6 +
                    (long double)param_6[2] * tmp_l8 + (long double)param_5[2]);
  G_HistoricalTrace(param_2,local_54,param_5,0,0,&local_6c,*param_1,0x6000001,1);
  tmp_i2 = local_20;
  if ((g_debugBullets[0xc] & 1) != 0) {
    tmp_u4 = tv(0x3f800000,0,0);
    G_RailTrail(param_5,local_48,tmp_u4);
    tmp_i2 = local_20;
  }
  if ((local_28 & 0x10) == 0) {
    SnapVectorTowards(local_48,param_5);
    tmp_i5 = tmp_i2 * 0x600;
    if ((*(int *)(g_entities + tmp_i5 + 0x2cc) == 0) || (*(int *)(g_entities + tmp_i5 + 400) == 0)) {
      tmp_i5 = nitrox_TempEventFromQueue(local_48,0x55);
      tmp_f1 = (param_6[2] * local_34 + param_6[1] * local_38 + *param_6 * local_3c) * -2.0;
      local_60 = local_3c * tmp_f1 + *param_6;
      local_5c = local_38 * tmp_f1 + param_6[1];
      local_58 = tmp_f1 * local_34 + param_6[2];
      VectorNormalize(&local_60);
      tmp_u4 = DirToByte(&local_60);
      *(uint32_t *)(tmp_i5 + 0xbc) = tmp_u4;
      *(uint32_t *)(tmp_i5 + 0x8c) = *param_1;
      *(uint32_t *)(tmp_i5 + 0x90) = *param_2;
      *(uint *)(tmp_i5 + 0x10c) = local_70;
    }
    else {
      tmp_i3 = nitrox_TempEventFromQueue(local_48,0x54);
      *(uint32_t *)(tmp_i3 + 0xbc) = *(uint32_t *)(g_entities + tmp_i5);
      *(uint32_t *)(tmp_i3 + 0x8c) = *param_1;
      *(uint32_t *)(tmp_i3 + 0x90) = *param_2;
      *(uint *)(tmp_i3 + 0x10c) = local_70;
    }
    if (*(int *)(g_entities + tmp_i2 * 0x600 + 0x2cc) != 0) {
      G_Damage(g_entities + tmp_i2 * 0x600,param_1,param_2,param_6,local_48,param_4,0,param_9);
      return;
    }
  }
  return;
}

void mg42_fire(uint32_t *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint32_t tmp_u7;
  int tmp_i8;
  long double tmp_l9;
  long double tmp_l10;
  long double tmp_l11;
  uint local_a0;
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
  float local_58;
  uint8_t local_54 [12];
  uint8_t local_48 [12];
  float local_3c;
  float local_38;
  float local_34;
  byte local_28;
  int local_20;
  
  tmp_i4 = *(int *)(param_1[100] + 0x414);
  AngleVectors(param_1[100] + 0xb0,&local_9c,&local_90,&local_84);
  tmp_i5 = tmp_i4 * 0x600;
  tmp_f1 = *(float *)(g_entities + tmp_i5 + 0x18);
  tmp_f2 = *(float *)(g_entities + tmp_i5 + 0x1c);
  tmp_f3 = *(float *)(g_entities + tmp_i5 + 0x20);
  if ((g_entities[tmp_i5 + 0x1a8] & 1) != 0) {
    tmp_f1 = local_84 * 16.0 + tmp_f1;
    tmp_f2 = local_80 * 16.0 + tmp_f2;
    tmp_f3 = local_7c * 16.0 + tmp_f3;
  }
  tmp_i5 = tmp_i4 * 0x600;
  *(uint *)(g_entities + tmp_i5 + 8) = *(uint *)(g_entities + tmp_i5 + 8) | 0x20;
  param_1[2] = param_1[2] | 0x20;
  local_78 = (float)(int)ROUND(tmp_f1);
  local_74 = (float)(int)ROUND(tmp_f2);
  local_70 = (float)(int)ROUND(tmp_f3);
  local_a0 = rand();
  local_a0 = local_a0 & 0xff;
  tmp_l9 = (long double)Q_crandom(&local_a0);
  tmp_l10 = (long double)Q_crandom(&local_a0);
  *(uint *)(g_entities + tmp_i5 + 8) = *(uint *)(g_entities + tmp_i5 + 8) | 0x20;
  param_1[2] = param_1[2] | 0x20;
  tmp_l10 = (long double)100.0 * tmp_l10;
  tmp_l11 = (long double)8192.0;
  tmp_l9 = (long double)(float)((long double)100.0 * tmp_l9);
  local_6c = (float)((long double)local_84 * tmp_l10 +
                    tmp_l9 * (long double)local_90 +
                    tmp_l11 * (long double)local_9c + (long double)local_78);
  local_68 = (float)((long double)local_80 * tmp_l10 +
                    (long double)local_8c * tmp_l9 +
                    (long double)local_98 * tmp_l11 + (long double)local_74);
  local_64 = (float)(tmp_l10 * (long double)local_7c +
                    (long double)local_88 * tmp_l9 +
                    (long double)local_94 * tmp_l11 + (long double)local_70);
  G_HistoricalTrace(param_1,local_54,&local_78,0,0,&local_6c,*(uint32_t *)(g_entities + tmp_i5),
                    0x6000001,1);
  tmp_i5 = local_20;
  if ((g_debugBullets[0xc] & 1) != 0) {
    tmp_u7 = tv(0x3f800000,0,0);
    G_RailTrail(&local_78,local_48,tmp_u7);
    tmp_i5 = local_20;
  }
  if ((local_28 & 0x10) == 0) {
    SnapVectorTowards(local_48,&local_78);
    tmp_i8 = tmp_i5 * 0x600;
    if ((*(int *)(g_entities + tmp_i8 + 0x2cc) == 0) || (*(int *)(g_entities + tmp_i8 + 400) == 0)) {
      tmp_i8 = nitrox_TempEventFromQueue(local_48,0x55);
      tmp_f1 = (local_94 * local_34 + local_98 * local_38 + local_9c * local_3c) * -2.0;
      local_60 = local_3c * tmp_f1 + local_9c;
      local_5c = local_38 * tmp_f1 + local_98;
      local_58 = tmp_f1 * local_34 + local_94;
      VectorNormalize(&local_60);
      tmp_u7 = DirToByte(&local_60);
      *(uint32_t *)(tmp_i8 + 0xbc) = tmp_u7;
      *(uint32_t *)(tmp_i8 + 0x8c) = *(uint32_t *)(g_entities + tmp_i4 * 0x600);
      *(uint32_t *)(tmp_i8 + 0x90) = *param_1;
      *(uint *)(tmp_i8 + 0x10c) = local_a0;
    }
    else {
      tmp_i6 = nitrox_TempEventFromQueue(local_48,0x54);
      *(uint32_t *)(tmp_i6 + 0xbc) = *(uint32_t *)(g_entities + tmp_i8);
      *(uint32_t *)(tmp_i6 + 0x8c) = *(uint32_t *)(g_entities + tmp_i4 * 0x600);
      *(uint32_t *)(tmp_i6 + 0x90) = *param_1;
      *(uint *)(tmp_i6 + 0x10c) = local_a0;
    }
    if (*(int *)(g_entities + tmp_i5 * 0x600 + 0x2cc) != 0) {
      G_Damage(g_entities + tmp_i5 * 0x600,g_entities + tmp_i4 * 0x600,param_1,&local_9c,local_48,0x14
               ,0,1);
      return;
    }
  }
  return;
}

void mg42_track(int param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint32_t tmp_u4;
  float *pfVar5;
  float *pfVar6;
  long double tmp_l7;
  
  if ((*(int *)(param_1 + 0x368) != 0) && (*(int *)(param_2 + 0x368) != 0)) {
    *(float *)(param_1 + 0x48) =
         *(float *)(*(int *)(param_2 + 400) + 0xb0) - *(float *)(param_1 + 0x3c);
    *(float *)(param_1 + 0x4c) =
         *(float *)(*(int *)(param_2 + 400) + 0xb4) - *(float *)(param_1 + 0x40);
    *(float *)(param_1 + 0x50) =
         *(float *)(*(int *)(param_2 + 400) + 0xb8) - *(float *)(param_1 + 0x44);
    pfVar5 = (float *)(param_1 + 0x48);
    do {
      pfVar6 = pfVar5 + 1;
      tmp_l7 = (long double)AngleNormalize180(*pfVar5);
      *pfVar5 = (float)tmp_l7;
      pfVar5 = pfVar6;
    } while (pfVar6 != (float *)(param_1 + 0x54));
    tmp_f1 = *(float *)(param_1 + 0x48) * 20.0;
    *(float *)(param_1 + 0x48) = tmp_f1;
    tmp_f2 = *(float *)(param_1 + 0x4c) * 20.0;
    *(float *)(param_1 + 0x4c) = tmp_f2;
    tmp_f3 = *(float *)(param_1 + 0x50) * 20.0;
    *(float *)(param_1 + 0x50) = tmp_f3;
    tmp_u4 = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x38) = 0x32;
    *(uint32_t *)(param_1 + 0x34) = tmp_u4;
    *(float *)(param_1 + 0x48) = (float)(int)ROUND(tmp_f1);
    *(float *)(param_1 + 0x4c) = (float)(int)ROUND(tmp_f2);
    *(float *)(param_1 + 0x50) = (float)(int)ROUND(tmp_f3);
  }
  return;
}

void mg42_stopusing(uint32_t *param_1)
{
  uint *tmp_pu1;
  int *tmp_pi2;
  int tmp_i3;
  
  tmp_i3 = param_1[0x60] * 0x600;
  tmp_pi2 = (int *)(g_entities + tmp_i3 + 400);
  if (*tmp_pi2 != 0) {
    tmp_pu1 = (uint *)(*tmp_pi2 + 0x68);
    *tmp_pu1 = *tmp_pu1 & 0xffffffdf;
    *(uint32_t *)(*tmp_pi2 + 0x140) = 0;
    param_1[0x60] = *param_1;
    *(uint32_t *)(*tmp_pi2 + 0x410) = 0;
    *(uint32_t *)(g_entities + tmp_i3 + 0x368) = 0;
    param_1[0x135] = *(uint32_t *)(*tmp_pi2 + 0x51c);
    param_1[0x134] = *(uint32_t *)(*tmp_pi2 + 0x2c);
    *(uint32_t *)(*tmp_pi2 + 0x2c) = *(uint32_t *)(g_entities + tmp_i3 + 0x4d0);
    param_1[0xda] = 0;
    param_1[0x60] = *param_1;
  }
  return;
}

void SP_mg42(int param_1)
{
  int tmp_i1;
  long tmp_l2;
  double tmp_d3;
  char *local_14;
  char *local_10;
  
  if (*(float *)(param_1 + 0x36c) == 0.0) {
    *(uint32_t *)(param_1 + 0x36c) = 0x42660000;
  }
  else if (*(float *)(param_1 + 0x36c) < 45.0) {
    *(uint32_t *)(param_1 + 0x36c) = 0x42340000;
  }
  if (*(float *)(param_1 + 0x370) == 0.0) {
    *(uint32_t *)(param_1 + 0x370) = 0x42340000;
  }
  if (*(int *)(param_1 + 0x2c8) == 0) {
    *(uint32_t *)(param_1 + 0x2c8) = 0x15e;
  }
  *(void **)(param_1 + 0x2a4) = mg42_spawn;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  tmp_i1 = G_SpawnStringExt("damage",&g_unk_0024bfa6,&local_14,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x52f);
  if (tmp_i1 != 0) {
    tmp_l2 = strtol(local_14,(char **)0x0,10);
    *(long *)(param_1 + 0x2d0) = tmp_l2;
  }
  G_SpawnStringExt("accuracy",&g_unk_0024a6b1,&local_10,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x532);
  tmp_d3 = strtod(local_10,(char **)0x0);
  if ((float)tmp_d3 == 0.0) {
    *(uint32_t *)(param_1 + 0x3fc) = 0x3f800000;
  }
  else {
    *(float *)(param_1 + 0x3fc) = (float)tmp_d3;
  }
  if (*(int *)(param_1 + 0x2d0) == 0) {
    *(uint32_t *)(param_1 + 0x2d0) = 0x19;
  }
  return;
}

void SP_misc_spawner(int param_1)
{
  uint32_t tmp_u1;
  
  if (*(int *)(param_1 + 0x38c) != 0) {
    *(void **)(param_1 + 0x2b4) = misc_spawner_use;
    trap_LinkEntity(param_1);
    return;
  }
  G_Printf("-----> WARNING <-------\n");
  tmp_u1 = vtos(param_1 + 0x5c);
  G_Printf("misc_spawner at loc %s has no spawnitem!\n",tmp_u1);
  return;
}

void SP_misc_firetrails(int param_1)
{
  *(void **)(param_1 + 0x2a4) = misc_firetrails_think;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

void SP_misc_constructiblemarker(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint32_t local_420;
  uint8_t local_41c [1036];
  
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    G_FreeEntity(param_1);
  }
  else {
    *(uint32_t *)(param_1 + 4) = 0x21;
    if (*(int *)(param_1 + 0x1b8) != 0) {
      tmp_u1 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
      *(uint32_t *)(param_1 + 0xa8) = tmp_u1;
    }
    if (*(int *)(param_1 + 0x348) != 0) {
      tmp_u1 = G_SkinIndex(*(int *)(param_1 + 0x348));
      *(uint32_t *)(param_1 + 0x10c) = tmp_u1;
    }
    tmp_i2 = G_SpawnStringExt("description",&g_unk_0026ea14,&local_420,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_misc.c",0x60e);
    if (tmp_i2 != 0) {
      trap_GetConfigstring(0x1b,local_41c,0x400);
      tmp_u1 = va("%i",(param_1 + -0x93e4a0 >> 9) * -0x55555555);
      Info_SetValueForKey(local_41c,tmp_u1,local_420);
      trap_SetConfigstring(0x1b,local_41c);
    }
    trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
    *(void **)(param_1 + 0x2a4) = constructiblemarker_setup;
    *(uint32_t *)(param_1 + 0xc) = 0;
    *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
    tmp_i2 = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
    *(int *)(param_1 + 0x29c) = tmp_i2 + 100;
  }
  return;
}

void SP_misc_landmine(int param_1)
{
  if ((*(uint *)(param_1 + 0x1a8) & 1) == 0) {
    if ((*(uint *)(param_1 + 0x1a8) & 2) == 0) {
      G_Error("ERROR: misc_landmine without a team\n");
    }
    else {
      *(uint32_t *)(param_1 + 0x108) = 2;
    }
  }
  else {
    *(uint32_t *)(param_1 + 0x108) = 1;
  }
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 500;
  *(void **)(param_1 + 0x2a4) = landmine_setup;
  return;
}

void SP_misc_commandmap_marker(int param_1)
{
  *(uint32_t *)(param_1 + 0x218) = 0;
  *(uint32_t *)(param_1 + 4) = 0x37;
  G_SetOrigin(param_1,param_1 + 0x5c);
  nitrox_AddEntityToEntityArray(&IndicatorEntities,param_1);
  return;
}

void Touch_Plat(int param_1,int param_2)
{
  if (((*(int *)(param_2 + 400) != 0) && (0 < *(int *)(param_2 + 0x2c8))) &&
     (*(int *)(param_1 + 0x1e4) == 1)) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 1000;
    return;
  }
  return;
}

void Think_BeginMoving(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0xc) = 3;
  *(uint32_t *)(param_1 + 0x10) = tmp_u1;
  return;
}

void Think_BeginMoving_rotating(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0xc) = 3;
  *(uint32_t *)(param_1 + 0x10) = tmp_u1;
  return;
}

void Use_Static(int param_1)
{
  if (*(int *)(param_1 + 0x120) == 0) {
    trap_LinkEntity();
    return;
  }
  trap_UnlinkEntity(param_1);
  return;
}

void Use_Func_Rotate(int param_1)
{
  uint tmp_u1;
  
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u1 & 4) == 0) {
    if ((tmp_u1 & 8) == 0) {
      *(uint32_t *)(param_1 + 0x4c) = *(uint32_t *)(param_1 + 0x268);
    }
    else {
      *(uint32_t *)(param_1 + 0x48) = *(uint32_t *)(param_1 + 0x268);
    }
  }
  else {
    *(uint32_t *)(param_1 + 0x50) = *(uint32_t *)(param_1 + 0x268);
  }
  if ((tmp_u1 & 2) != 0) {
    *(uint *)(param_1 + 0x1b0) = *(uint *)(param_1 + 0x1b0) & 0xfffffbff;
  }
  trap_LinkEntity(param_1);
  return;
}

void func_explosive_spawn(int param_1)
{
  trap_LinkEntity(param_1);
  *(void **)(param_1 + 0x2b4) = func_explosive_use;
  return;
}

void func_constructible_spawn(int param_1)
{
  trap_LinkEntity(param_1);
  *(void **)(param_1 + 0x2b4) = func_constructible_use;
  return;
}

void func_brushmodel_delete(uint32_t param_1)
{
  G_FreeEntity(param_1);
  return;
}

void target_effect(int param_1,uint32_t param_2)
{
  float tmp_f1;
  int tmp_i2;
  
  tmp_i2 = nitrox_TempEventFromQueue(param_1 + 0x168,0x41);
  *(uint32_t *)(tmp_i2 + 0x5c) = *(uint32_t *)(param_1 + 0x168);
  *(uint32_t *)(tmp_i2 + 0x60) = *(uint32_t *)(param_1 + 0x16c);
  *(uint32_t *)(tmp_i2 + 100) = *(uint32_t *)(param_1 + 0x170);
  *(uint *)(tmp_i2 + 0x9c) = *(uint *)(param_1 + 0x1a8) >> 5 & 1;
  trap_SetConfigstring(0x14,*(uint32_t *)(param_1 + 0x35c));
  *(uint32_t *)(tmp_i2 + 0xb0) = *(uint32_t *)(param_1 + 0x364);
  *(uint32_t *)(tmp_i2 + 0xbc) = *(uint32_t *)(param_1 + 0x1a8);
  *(uint32_t *)(tmp_i2 + 0xf4) = *(uint32_t *)(param_1 + 0x2c8);
  if (*(int *)(param_1 + 0x2d0) != 0) {
    tmp_f1 = (float)*(int *)(param_1 + 0x2d0);
    G_RadiusDamage(param_1 + 0x18,0,param_1,tmp_f1,tmp_f1,param_1,0x23);
  }
  G_UseTargets(param_1,param_2);
  return;
}

void target_explosion_use(int param_1,uint32_t param_2,uint32_t param_3)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_18 = 0;
  local_14 = 0;
  local_10 = 0x3f800000;
  tmp_i2 = nitrox_TempEventFromQueue(param_1 + 0x168,0x40);
  G_UseTargets(param_1,param_3);
  *(uint32_t *)(tmp_i2 + 0xf4) = *(uint32_t *)(param_1 + 0x2e4);
  *(int *)(tmp_i2 + 0xe8) = (int)ROUND(*(float *)(param_1 + 800));
  *(uint32_t *)(tmp_i2 + 0xb0) = *(uint32_t *)(param_1 + 0x364);
  *(uint32_t *)(tmp_i2 + 0x80) = *(uint32_t *)(param_1 + 0x80);
  *(uint32_t *)(tmp_i2 + 0x84) = *(uint32_t *)(param_1 + 0x84);
  tmp_i1 = *(int *)(param_1 + 0x2d0);
  if (tmp_i1 != 0) {
    G_RadiusDamage(param_1 + 0x18,0,param_1,(float)tmp_i1,(float)(tmp_i1 + 0x28),param_1,0x23);
  }
  tmp_u3 = DirToByte(&local_18);
  *(uint32_t *)(tmp_i2 + 0xbc) = tmp_u3;
  return;
}

void func_explosive_explode
               (int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5)

{
  float tmp_f1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  float local_28;
  float local_24;
  float local_20;
  
  local_28 = 0.0;
  local_24 = 0.0;
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  *(void **)(param_1 + 0x2a4) = BecomeExplosion;
  local_20 = 1.0;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(float *)(param_1 + 0x18) =
       (*(float *)(param_1 + 0x15c) - *(float *)(param_1 + 0x150)) * 0.5 +
       *(float *)(param_1 + 0x150);
  *(float *)(param_1 + 0x1c) =
       (*(float *)(param_1 + 0x160) - *(float *)(param_1 + 0x154)) * 0.5 +
       *(float *)(param_1 + 0x154);
  *(float *)(param_1 + 0x20) =
       (*(float *)(param_1 + 0x164) - *(float *)(param_1 + 0x158)) * 0.5 +
       *(float *)(param_1 + 0x158);
  G_UseTargets(param_1,param_3);
  *(uint32_t *)(param_1 + 0xf4) = *(uint32_t *)(param_1 + 0x2e4);
  *(int *)(param_1 + 0xe8) = (int)ROUND(*(float *)(param_1 + 800));
  *(uint32_t *)(param_1 + 0xb0) = *(uint32_t *)(param_1 + 0x364);
  tmp_i4 = *(int *)(param_1 + 0x2d0);
  if (tmp_i4 != 0) {
    G_RadiusDamage(param_1 + 0x18,0,param_1,(float)tmp_i4,(float)(tmp_i4 + 0x28),param_1,0x23);
  }
  tmp_i4 = *(int *)(param_1 + 0x254);
  if (tmp_i4 != 0) {
    tmp_i2 = 0;
    while (tmp_i2 = G_FindByTargetnameFast(tmp_i2,tmp_i4,*(uint32_t *)(param_1 + 0x5bc)), tmp_i2 != 0)
    {
      if (*(int *)(tmp_i2 + 0x5c0) == 0x27a09) {
        local_28 = *(float *)(tmp_i2 + 0x18) - *(float *)(param_1 + 0x18);
        local_24 = *(float *)(tmp_i2 + 0x1c) - *(float *)(param_1 + 0x1c);
        local_20 = *(float *)(tmp_i2 + 0x20) - *(float *)(param_1 + 0x20);
        VectorNormalize(&local_28);
        goto LAB_000a03a2;
      }
      tmp_i4 = *(int *)(param_1 + 0x254);
    }
  }
  tmp_f1 = *(float *)(param_1 + 0x78);
  if ((tmp_f1 != 0.0) && (tmp_f1 != -1.0)) {
    if (tmp_f1 == -2.0) {
      local_20 = -1.0;
    }
    else {
      tmp_u3 = tv(0x3f800000,0,0);
      RotatePointAroundVector(&local_28,&local_28,tmp_u3,tmp_f1);
    }
  }
LAB_000a03a2:
  tmp_u3 = DirToByte(&local_28);
  G_AddEvent(param_1,0x3f,tmp_u3);
  if (*(float *)(param_1 + 0x4e8) == 5.0) {
    G_Script_ScriptEvent(param_1,"exploded",&g_unk_0026ea14);
  }
  tmp_i4 = G_GetWeaponClassForMOD(param_5);
  if (*(int *)(param_1 + 0x4f4) <= tmp_i4) {
    G_AddKillSkillPointsForDestruction(param_3,param_5,param_1 + 0x4e4);
  }
  return;
}

void func_explosive_use(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  G_Script_ScriptEvent(param_1,"death",&g_unk_0026ea14);
  if (*(int *)(param_1 + 0x218) != 0) {
    tmp_i1 = Q_stricmp(*(uint32_t *)(param_1 + 0x3ac),
                      *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x3ac));
    if (tmp_i1 != 0) {
      G_Script_ScriptEvent(*(uint32_t *)(param_1 + 0x218),"death",&g_unk_0026ea14);
    }
  }
  func_explosive_explode(param_1,param_1,param_2,*(uint32_t *)(param_1 + 0x2d0),0);
  return;
}

void func_constructible_use(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  long tmp_l7;
  
  *(uint32_t *)(param_1 + 0x3a4) = 0;
  *(uint32_t *)(param_1 + 0xa4) = 0;
  *(uint32_t *)(param_1 + 0x80) = 0;
  if (*(int *)(param_1 + 0x39c) == 0) {
    tmp_l7 = strtol((char *)(*(int *)(param_1 + 0x1b4) + 1),(char **)0x0,10);
    *(long *)(param_1 + 0xa8) = tmp_l7;
  }
  else {
    *(uint32_t *)(param_1 + 0xa8) = *(uint32_t *)(param_1 + 0x468);
  }
  if ((*(byte *)(param_1 + 0x1a8) & 0x10) == 0) {
    tmp_u1 = *(uint32_t *)(param_1 + 0x1d4);
    tmp_u6 = *(uint32_t *)(param_1 + 0xa4);
    tmp_u2 = *(uint32_t *)(param_1 + 0x14c);
    tmp_u3 = *(uint *)(param_1 + 8);
    if (*(int *)(param_1 + 0x39c) == 0) {
      trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
    }
    else {
      tmp_u5 = va(&g_unk_0024d859,*(uint32_t *)(param_1 + 0x464 + *(int *)(param_1 + 0x39c) * 4));
      trap_SetBrushModel(param_1,tmp_u5);
    }
    trap_LinkEntity(param_1);
    tmp_u6 = va(&g_unk_0024d859,tmp_u6);
    trap_SetBrushModel(param_1,tmp_u6);
    *(uint32_t *)(param_1 + 0x1d4) = tmp_u1;
    *(uint32_t *)(param_1 + 0x14c) = tmp_u2;
    if ((tmp_u3 & 2) == 0) {
      *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xfffffffd;
    }
    trap_UnlinkEntity(param_1);
  }
  *(void **)(param_1 + 0x2b4) = func_constructible_spawn;
  trap_UnlinkEntity(param_1);
  if (*(int *)(param_1 + 0x218) == 0) {
    *(uint32_t *)(param_1 + 0x84) = 0;
  }
  else {
    trap_LinkEntity(*(int *)(param_1 + 0x218));
    if (*(float *)(param_1 + 0x84) == 0.0) {
      if ((*(int *)(*(int *)(param_1 + 0x218) + 0x2e8) != 0) &&
         (tmp_i4 = *(int *)(*(int *)(param_1 + 0x218) + 0x39c), tmp_i4 != 0)) {
        *(uint32_t *)(g_entities + tmp_i4 * 0x600 + 0x108) = 3;
      }
    }
    else {
      *(uint32_t *)(param_1 + 0x84) = 0;
      Think_SetupObjectiveInfo(*(uint32_t *)(param_1 + 0x218));
    }
  }
  if ((*(byte *)(param_1 + 0x1a8) & 2) == 0) {
    *(uint32_t *)(param_1 + 0x2cc) = 0;
  }
  return;
}

void func_constructiblespawn(uint32_t *param_1)
{
  char *tmp_pc1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  char tmp_c6;
  uint32_t tmp_u7;
  int tmp_i8;
  int tmp_i9;
  long tmp_l10;
  int tmp_i11;
  char *tmp_pc12;
  char *tmp_pc13;
  int local_ac;
  char acStack_9d [141];
  
  tmp_pc12 = (char *)param_1[0x117];
  if (tmp_pc12 != (char *)0x0) {
    param_1[0xe7] = 0;
    param_1[0xe9] = 0;
    tmp_c6 = *tmp_pc12;
    if (tmp_c6 == '\0') {
      tmp_i8 = 1;
      tmp_i9 = 0;
    }
    else {
      tmp_pc13 = tmp_pc12 + 1;
      do {
        while (tmp_c6 != ';') {
          tmp_c6 = *tmp_pc13;
          tmp_pc13 = tmp_pc13 + 1;
          if (tmp_c6 == '\0') goto LAB_000a0940;
        }
        tmp_pc1 = acStack_9d + 1;
        Q_strncpyz(tmp_pc1,tmp_pc12,tmp_pc13 + -(int)tmp_pc12);
        tmp_i8 = param_1[0xe7];
        tmp_pc13[(int)(acStack_9d + -(int)tmp_pc12)] = '\0';
        if (tmp_i8 == 3) {
          G_Error("\'func_constructible\' has more than %i targets in the constages key\n",2);
          tmp_i9 = param_1[0xe7];
          tmp_i8 = tmp_i9 + 1;
          goto LAB_000a0949;
        }
        tmp_u7 = BG_StringHashValue(tmp_pc1);
        tmp_i8 = G_FindByTargetnameFast(0,tmp_pc1,tmp_u7);
        if (tmp_i8 != 0) {
          tmp_i9 = Q_stricmp(*(uint32_t *)(tmp_i8 + 0x1a4),"func_brushmodel");
          if (tmp_i9 != 0) {
            G_Error("constages entry doesn\'t target a \'func_brushmodel\'\n");
          }
          tmp_i8 = *(int *)(tmp_i8 + 0x1b4);
          tmp_i9 = param_1[0xe7];
          param_1[0xe7] = tmp_i9 + 1;
          tmp_l10 = strtol((char *)(tmp_i8 + 1),(char **)0x0,10);
          param_1[tmp_i9 + 0x11a] = tmp_l10;
        }
        tmp_c6 = *tmp_pc13;
        tmp_pc12 = tmp_pc13;
        tmp_pc13 = tmp_pc13 + 1;
      } while (tmp_c6 != '\0');
LAB_000a0940:
      tmp_i9 = param_1[0xe7];
      tmp_i8 = tmp_i9 + 1;
    }
LAB_000a0949:
    param_1[0xe7] = tmp_i8;
    tmp_l10 = strtol((char *)(param_1[0x6d] + 1),(char **)0x0,10);
    param_1[tmp_i9 + 0x11a] = tmp_l10;
    tmp_i8 = param_1[0xe7];
    if ((tmp_i8 != 0) && (tmp_pc12 = (char *)param_1[0x118], tmp_pc12 != (char *)0x0)) {
      tmp_c6 = *tmp_pc12;
      if (tmp_c6 == '\0') {
        local_ac = 0;
      }
      else {
        local_ac = 0;
        tmp_pc13 = tmp_pc12 + 1;
        do {
          while (tmp_c6 != ';') {
            tmp_c6 = *tmp_pc13;
            tmp_pc13 = tmp_pc13 + 1;
            if (tmp_c6 == '\0') goto LAB_000a0a90;
          }
          tmp_pc1 = acStack_9d + 1;
          Q_strncpyz(tmp_pc1,tmp_pc12,tmp_pc13 + -(int)tmp_pc12);
          tmp_pc13[(int)(acStack_9d + -(int)tmp_pc12)] = '\0';
          if (local_ac == 2) {
            G_Error("\'func_constructible\' has more than %i targets in the desstages key\n",1);
            tmp_i8 = param_1[0xe7];
            goto LAB_000a0a9d;
          }
          tmp_u7 = BG_StringHashValue(tmp_pc1);
          tmp_i8 = G_FindByTargetnameFast(0,tmp_pc1,tmp_u7);
          if (tmp_i8 != 0) {
            tmp_i9 = Q_stricmp(*(uint32_t *)(tmp_i8 + 0x1a4),"func_brushmodel");
            if (tmp_i9 != 0) {
              G_Error("desstages entry doesn\'t target a \'func_brushmodel\'\n");
            }
            tmp_l10 = strtol((char *)(*(int *)(tmp_i8 + 0x1b4) + 1),(char **)0x0,10);
            param_1[local_ac + 0x11e] = tmp_l10;
            local_ac = local_ac + 1;
          }
          tmp_c6 = *tmp_pc13;
          tmp_pc12 = tmp_pc13;
          tmp_pc13 = tmp_pc13 + 1;
        } while (tmp_c6 != '\0');
LAB_000a0a90:
        tmp_i8 = param_1[0xe7];
      }
LAB_000a0a9d:
      if (tmp_i8 + -1 != local_ac) {
        G_Error("\'func_constructible\' has %i entries in the desstages and %i targets in the constages key\n"
                ,local_ac,tmp_i8 + -1);
      }
    }
  }
  param_1[0x20] = 0;
  param_1[1] = 0x20;
  trap_LinkEntity(param_1);
  if ((*(byte *)(param_1 + 0x6a) & 1) == 0) {
    param_1[0xad] = func_constructible_spawn;
    if (param_1[0xe7] == 0) {
      trap_SetBrushModel(param_1,param_1[0x6d]);
    }
    else {
      tmp_u7 = va(&g_unk_0024d859,param_1[param_1[0xe7] + 0x119]);
      trap_SetBrushModel(param_1,tmp_u7);
    }
    trap_LinkEntity(param_1);
    trap_UnlinkEntity(param_1);
    if (param_1[0xe7] == 0) {
      trap_SetBrushModel(param_1,param_1[0x6d]);
      param_1[0x29] = 0;
      trap_LinkEntity(param_1);
      tmp_l10 = strtol((char *)(param_1[0x6d] + 1),(char **)0x0,10);
      param_1[0x2a] = tmp_l10;
    }
    else {
      tmp_u7 = va(&g_unk_0024d859,param_1[0x11a]);
      trap_SetBrushModel(param_1,tmp_u7);
      param_1[0x29] = 0;
      trap_LinkEntity(param_1);
      param_1[0x2a] = param_1[0x11a];
    }
    trap_UnlinkEntity(param_1);
  }
  else {
    param_1[0xad] = func_constructible_use;
    if (param_1[0xe7] == 0) {
      trap_SetBrushModel(param_1,param_1[0x6d]);
    }
    else {
      tmp_u7 = va(&g_unk_0024d859,param_1[param_1[0xe7] + 0x119]);
      trap_SetBrushModel(param_1,tmp_u7);
      param_1[0xe9] = param_1[0xe7];
    }
    param_1[0x21] = 0x3f800000;
    if ((*(byte *)(param_1 + 0x6a) & 2) == 0) {
      param_1[0xb3] = 1;
      tmp_i9 = G_Spawn();
      nitrox_AddEntityToEntityArray(&IndicatorEntities,tmp_i9);
      tmp_i8 = TriggerEntities;
      *(uint32_t *)(tmp_i9 + 0x128) = 0x20;
      *(char **)(tmp_i9 + 0x1a4) = "explosive_indicator";
      *(uint32_t *)(tmp_i9 + 4) = 0xd;
      if (0 < tmp_i8) {
        tmp_i8 = 0;
        do {
          while( true ) {
            tmp_i5 = (&g_unk_0087ea44)[tmp_i8];
            tmp_i11 = Q_stricmp(*(uint32_t *)(tmp_i5 + 0x254),param_1[0x96]);
            if ((tmp_i11 == 0) && (*(int *)(tmp_i5 + 4) == 0xc)) break;
LAB_000a0d08:
            tmp_i8 = tmp_i8 + 1;
            if (TriggerEntities <= tmp_i8) goto LAB_000a0d80;
          }
          if ((*(byte *)(tmp_i5 + 0x1a8) & 8) != 0) {
            *(uint32_t *)(tmp_i9 + 4) = 0x24;
          }
          if (param_1[0x86] != 0) goto LAB_000a0d08;
          tmp_i8 = tmp_i8 + 1;
          param_1[0x86] = tmp_i5;
          *(int *)(tmp_i9 + 0x218) = tmp_i5;
        } while (tmp_i8 < TriggerEntities);
      }
LAB_000a0d80:
      if (param_1[0x86] == 0) {
        G_Error("\'func_constructible\' has a missing parent trigger_objective_info \'%s\'\n",
                param_1[0x96]);
      }
      *(uint32_t *)(tmp_i9 + 0xc) = 0;
      if ((param_1[0x6a] & 4) == 0) {
        if ((param_1[0x6a] & 8) != 0) {
          *(uint32_t *)(tmp_i9 + 0x108) = 2;
        }
      }
      else {
        *(uint32_t *)(tmp_i9 + 0x108) = 1;
      }
      *(uint32_t *)(tmp_i9 + 0xa8) = *(uint32_t *)(param_1[0x86] + 0x108);
      *(uint32_t *)(tmp_i9 + 0x180) = *param_1;
      *(void **)(tmp_i9 + 0x2a4) = explosive_indicator_think;
      *(int *)(tmp_i9 + 0x29c) = g_unk_00abe908 + 100;
      *(uint32_t *)(tmp_i9 + 0x10c) = param_1[0x13d];
      if (*(int *)(param_1[0x86] + 0x440) == 0) {
        tmp_f2 = (float)param_1[0x54];
        *(float *)(tmp_i9 + 0x18) = tmp_f2;
        tmp_f3 = (float)param_1[0x55];
        *(float *)(tmp_i9 + 0x1c) = tmp_f3;
        tmp_f4 = (float)param_1[0x56];
        *(float *)(tmp_i9 + 0x20) = tmp_f4;
        tmp_f2 = tmp_f2 + (float)param_1[0x57];
        *(float *)(tmp_i9 + 0x18) = tmp_f2;
        tmp_f3 = tmp_f3 + (float)param_1[0x58];
        *(float *)(tmp_i9 + 0x1c) = tmp_f3;
        tmp_f2 = tmp_f2 * 0.5;
        tmp_f3 = tmp_f3 * 0.5;
        tmp_f4 = (tmp_f4 + (float)param_1[0x59]) * 0.5;
      }
      else {
        *(int *)(tmp_i9 + 0x440) = *(int *)(param_1[0x86] + 0x440);
        Q_strncpyz(tmp_i9 + 0x400,param_1[0x86] + 0x400,0x40);
        tmp_f2 = *(float *)(tmp_i9 + 0x18);
        tmp_f3 = *(float *)(tmp_i9 + 0x1c);
        tmp_f4 = *(float *)(tmp_i9 + 0x20);
      }
      *(float *)(tmp_i9 + 0x18) = (float)(int)ROUND(tmp_f2);
      *(float *)(tmp_i9 + 0x1c) = (float)(int)ROUND(tmp_f3);
      *(float *)(tmp_i9 + 0x20) = (float)(int)ROUND(tmp_f4);
      trap_LinkEntity(tmp_i9);
    }
  }
  param_1[0xaf] = func_constructible_explode;
  return;
}

void Think_SetupTrainTargets(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  
  tmp_i1 = G_FindByTargetnameFast
                    (0,*(uint32_t *)(param_1 + 0x254),*(uint32_t *)(param_1 + 0x5bc));
  *(int *)(param_1 + 0x21c) = tmp_i1;
  if (tmp_i1 == 0) {
    tmp_u3 = vtos(param_1 + 0x150);
    G_Printf("func_train at %s with an unfound target\n",tmp_u3);
  }
  else if (*(int *)(tmp_i1 + 0x21c) == 0) {
    tmp_i2 = *(int *)(tmp_i1 + 0x254);
    while (tmp_i2 != 0) {
      tmp_i4 = 0;
      while( true ) {
        tmp_i4 = G_FindByTargetnameFast(tmp_i4,tmp_i2,*(uint32_t *)(tmp_i1 + 0x5bc));
        if (tmp_i4 == 0) {
          tmp_u3 = vtos(tmp_i1 + 0x5c);
          G_Printf("Train corner at %s without a target path_corner\n",tmp_u3);
          return;
        }
        if (*(int *)(tmp_i4 + 0x5c0) == 0x23858) break;
        tmp_i2 = *(int *)(tmp_i1 + 0x254);
      }
      *(int *)(tmp_i1 + 0x21c) = tmp_i4;
      if (*(int *)(tmp_i4 + 0x21c) != 0) goto LAB_000a1e9b;
      tmp_i1 = tmp_i4;
      tmp_i2 = *(int *)(tmp_i4 + 0x254);
    }
    tmp_u3 = vtos(tmp_i1 + 0x5c);
    G_Printf("Train corner at %s without a target\n",tmp_u3);
  }
  else {
LAB_000a1e9b:
    tmp_i1 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"func_train");
    if ((tmp_i1 != 0) || ((*(byte *)(param_1 + 0x1a8) & 2) == 0)) {
      Reached_Train();
      return;
    }
    tmp_i1 = *(int *)(param_1 + 0x21c);
    *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(tmp_i1 + 0x5c);
    *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(tmp_i1 + 0x60);
    *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(tmp_i1 + 100);
    *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(tmp_i1 + 0x5c);
    *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(tmp_i1 + 0x60);
    *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(tmp_i1 + 100);
    trap_LinkEntity(param_1);
  }
  return;
}

void Think_SetupTrainTargets_rotating(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  
  tmp_i1 = G_FindByTargetnameFast
                    (0,*(uint32_t *)(param_1 + 0x254),*(uint32_t *)(param_1 + 0x5bc));
  *(int *)(param_1 + 0x21c) = tmp_i1;
  if (tmp_i1 == 0) {
    tmp_u3 = vtos(param_1 + 0x150);
    G_Printf("func_train at %s with an unfound target\n",tmp_u3);
  }
  else {
    *(uint32_t *)(param_1 + 0x31c) = 1;
    *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
    *(uint32_t *)(param_1 + 0x330) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x334) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x338) = *(uint32_t *)(param_1 + 0x7c);
    tmp_i5 = tmp_i1;
    while (tmp_i2 = *(int *)(tmp_i5 + 0x254), tmp_i2 != 0) {
      tmp_i4 = 0;
      while( true ) {
        tmp_i4 = G_FindByTargetnameFast(tmp_i4,tmp_i2,*(uint32_t *)(tmp_i5 + 0x5bc));
        if (tmp_i4 == 0) {
          tmp_u3 = vtos(tmp_i5 + 0x5c);
          G_Printf("Train corner at %s without a target path_corner\n",tmp_u3);
          return;
        }
        if (*(int *)(tmp_i4 + 0x5c0) == 0x23858) break;
        tmp_i2 = *(int *)(tmp_i5 + 0x254);
      }
      *(int *)(tmp_i5 + 0x21c) = tmp_i4;
      tmp_i5 = tmp_i4;
      if (tmp_i1 == tmp_i4) {
        Reached_Train_rotating();
        return;
      }
    }
    tmp_u3 = vtos(tmp_i5 + 0x5c);
    G_Printf("Train corner at %s without a target\n",tmp_u3);
  }
  return;
}

void func_explosive_touch(int param_1,uint32_t param_2)
{
  float tmp_f1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  float local_28;
  float local_24;
  float local_20;
  
  local_28 = 0.0;
  local_24 = 0.0;
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  *(void **)(param_1 + 0x2a4) = BecomeExplosion;
  local_20 = 1.0;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(float *)(param_1 + 0x18) =
       (*(float *)(param_1 + 0x15c) - *(float *)(param_1 + 0x150)) * 0.5 +
       *(float *)(param_1 + 0x150);
  *(float *)(param_1 + 0x1c) =
       (*(float *)(param_1 + 0x160) - *(float *)(param_1 + 0x154)) * 0.5 +
       *(float *)(param_1 + 0x154);
  *(float *)(param_1 + 0x20) =
       (*(float *)(param_1 + 0x164) - *(float *)(param_1 + 0x158)) * 0.5 +
       *(float *)(param_1 + 0x158);
  G_UseTargets(param_1,param_2);
  *(uint32_t *)(param_1 + 0xf4) = *(uint32_t *)(param_1 + 0x2e4);
  *(int *)(param_1 + 0xe8) = (int)ROUND(*(float *)(param_1 + 800));
  *(uint32_t *)(param_1 + 0xb0) = *(uint32_t *)(param_1 + 0x364);
  tmp_i4 = *(int *)(param_1 + 0x2d0);
  if (tmp_i4 != 0) {
    G_RadiusDamage(param_1 + 0x18,0,param_1,(float)tmp_i4,(float)(tmp_i4 + 0x28),param_1,0x23);
  }
  tmp_i4 = *(int *)(param_1 + 0x254);
  if (tmp_i4 != 0) {
    tmp_i2 = 0;
    while (tmp_i2 = G_FindByTargetnameFast(tmp_i2,tmp_i4,*(uint32_t *)(param_1 + 0x5bc)), tmp_i2 != 0)
    {
      if (*(int *)(tmp_i2 + 0x5c0) == 0x27a09) {
        local_28 = *(float *)(tmp_i2 + 0x18) - *(float *)(param_1 + 0x18);
        local_24 = *(float *)(tmp_i2 + 0x1c) - *(float *)(param_1 + 0x1c);
        local_20 = *(float *)(tmp_i2 + 0x20) - *(float *)(param_1 + 0x20);
        VectorNormalize(&local_28);
        goto LAB_000a2a32;
      }
      tmp_i4 = *(int *)(param_1 + 0x254);
    }
  }
  tmp_f1 = *(float *)(param_1 + 0x78);
  if ((tmp_f1 != 0.0) && (tmp_f1 != -1.0)) {
    if (tmp_f1 == -2.0) {
      local_20 = -1.0;
    }
    else {
      tmp_u3 = tv(0x3f800000,0,0);
      RotatePointAroundVector(&local_28,&local_28,tmp_u3,tmp_f1);
    }
  }
LAB_000a2a32:
  tmp_u3 = DirToByte(&local_28);
  G_AddEvent(param_1,0x3f,tmp_u3);
  if (*(float *)(param_1 + 0x4e8) == 5.0) {
    G_Script_ScriptEvent(param_1,"exploded",&g_unk_0026ea14);
  }
  tmp_i4 = G_GetWeaponClassForMOD(0);
  if (*(int *)(param_1 + 0x4f4) <= tmp_i4) {
    G_AddKillSkillPointsForDestruction(param_2,0,param_1 + 0x4e4);
  }
  return;
}

void func_explosive_alert(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  float local_18;
  float local_14;
  float local_10;
  
  local_18 = 0.0;
  local_14 = 0.0;
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  *(void **)(param_1 + 0x2a4) = BecomeExplosion;
  local_10 = 1.0;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(float *)(param_1 + 0x18) =
       (*(float *)(param_1 + 0x15c) - *(float *)(param_1 + 0x150)) * 0.5 +
       *(float *)(param_1 + 0x150);
  *(float *)(param_1 + 0x1c) =
       (*(float *)(param_1 + 0x160) - *(float *)(param_1 + 0x154)) * 0.5 +
       *(float *)(param_1 + 0x154);
  *(float *)(param_1 + 0x20) =
       (*(float *)(param_1 + 0x164) - *(float *)(param_1 + 0x158)) * 0.5 +
       *(float *)(param_1 + 0x158);
  G_UseTargets(param_1,param_1);
  *(uint32_t *)(param_1 + 0xf4) = *(uint32_t *)(param_1 + 0x2e4);
  *(int *)(param_1 + 0xe8) = (int)ROUND(*(float *)(param_1 + 800));
  *(uint32_t *)(param_1 + 0xb0) = *(uint32_t *)(param_1 + 0x364);
  tmp_i4 = *(int *)(param_1 + 0x2d0);
  if (tmp_i4 != 0) {
    G_RadiusDamage(param_1 + 0x18,0,param_1,(float)tmp_i4,(float)(tmp_i4 + 0x28),param_1,0x23);
  }
  tmp_i4 = *(int *)(param_1 + 0x254);
  if (tmp_i4 != 0) {
    tmp_i2 = 0;
    while (tmp_i2 = G_FindByTargetnameFast(tmp_i2,tmp_i4,*(uint32_t *)(param_1 + 0x5bc)), tmp_i2 != 0)
    {
      if (*(int *)(tmp_i2 + 0x5c0) == 0x27a09) {
        local_18 = *(float *)(tmp_i2 + 0x18) - *(float *)(param_1 + 0x18);
        local_14 = *(float *)(tmp_i2 + 0x1c) - *(float *)(param_1 + 0x1c);
        local_10 = *(float *)(tmp_i2 + 0x20) - *(float *)(param_1 + 0x20);
        VectorNormalize(&local_18);
        goto LAB_000a2d32;
      }
      tmp_i4 = *(int *)(param_1 + 0x254);
    }
  }
  tmp_f1 = *(float *)(param_1 + 0x78);
  if ((tmp_f1 != 0.0) && (tmp_f1 != -1.0)) {
    if (tmp_f1 == -2.0) {
      local_10 = -1.0;
    }
    else {
      tmp_u3 = tv(0x3f800000,0,0);
      RotatePointAroundVector(&local_18,&local_18,tmp_u3,tmp_f1);
    }
  }
LAB_000a2d32:
  tmp_u3 = DirToByte(&local_18);
  G_AddEvent(param_1,0x3f,tmp_u3);
  if (*(float *)(param_1 + 0x4e8) == 5.0) {
    G_Script_ScriptEvent(param_1,"exploded",&g_unk_0026ea14);
  }
  tmp_i4 = G_GetWeaponClassForMOD(0);
  if (*(int *)(param_1 + 0x4f4) <= tmp_i4) {
    G_AddKillSkillPointsForDestruction(param_1,0,param_1 + 0x4e4);
  }
  return;
}

void Think_MatchTeam(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint32_t tmp_u6;
  uint tmp_u7;
  uint32_t tmp_u8;
  int tmp_i9;
  char *tmp_pc10;
  int tmp_i11;
  float local_20;
  
  tmp_u6 = g_unk_00abe908;
  tmp_u2 = *(uint32_t *)(param_1 + 0x1e4);
  tmp_i11 = param_1;
  do {
    tmp_u7 = *(uint *)(tmp_i11 + 0x1b0);
    if ((*(byte *)(param_1 + 0x1b0) & 0x40) != 0) {
      tmp_u7 = tmp_u7 | 0x40;
      *(uint *)(tmp_i11 + 0x1b0) = tmp_u7;
    }
    *(uint32_t *)(tmp_i11 + 0x1e4) = tmp_u2;
    *(uint32_t *)(tmp_i11 + 0x10) = tmp_u6;
    *(uint32_t *)(tmp_i11 + 0x34) = tmp_u6;
    switch(tmp_u2) {
    case 0:
      *(uint32_t *)(tmp_i11 + 0xc) = 0;
      *(uint32_t *)(tmp_i11 + 0x18) = *(uint32_t *)(tmp_i11 + 0x224);
      *(uint32_t *)(tmp_i11 + 0x368) = 0;
      *(uint32_t *)(tmp_i11 + 0x1c) = *(uint32_t *)(tmp_i11 + 0x228);
      *(uint32_t *)(tmp_i11 + 0x20) = *(uint32_t *)(tmp_i11 + 0x22c);
      break;
    case 1:
      *(uint32_t *)(tmp_i11 + 0xc) = 0;
      *(uint32_t *)(tmp_i11 + 0x18) = *(uint32_t *)(tmp_i11 + 0x230);
      *(uint32_t *)(tmp_i11 + 0x1c) = *(uint32_t *)(tmp_i11 + 0x234);
      *(uint32_t *)(tmp_i11 + 0x20) = *(uint32_t *)(tmp_i11 + 0x238);
      break;
    case 2:
      *(uint32_t *)(tmp_i11 + 0xc) = 0;
      *(uint32_t *)(tmp_i11 + 0x18) = *(uint32_t *)(tmp_i11 + 0x23c);
      *(uint32_t *)(tmp_i11 + 0x1c) = *(uint32_t *)(tmp_i11 + 0x240);
      *(uint32_t *)(tmp_i11 + 0x20) = *(uint32_t *)(tmp_i11 + 0x244);
      break;
    case 3:
      *(float *)(tmp_i11 + 0x18) = *(float *)(tmp_i11 + 0x224);
      *(float *)(tmp_i11 + 0x1c) = *(float *)(tmp_i11 + 0x228);
      *(uint32_t *)(tmp_i11 + 0x14) = *(uint32_t *)(tmp_i11 + 0x27c);
      *(float *)(tmp_i11 + 0x20) = *(float *)(tmp_i11 + 0x22c);
      tmp_f1 = 1000.0 / (float)*(int *)(tmp_i11 + 0x27c);
      *(uint32_t *)(tmp_i11 + 0xc) = 3;
      *(float *)(tmp_i11 + 0x24) = (*(float *)(tmp_i11 + 0x230) - *(float *)(tmp_i11 + 0x224)) * tmp_f1;
      *(float *)(tmp_i11 + 0x28) = (*(float *)(tmp_i11 + 0x234) - *(float *)(tmp_i11 + 0x228)) * tmp_f1;
      *(float *)(tmp_i11 + 0x2c) = tmp_f1 * (*(float *)(tmp_i11 + 0x238) - *(float *)(tmp_i11 + 0x22c));
      tmp_u8 = _GetEntityName(tmp_i11);
      tmp_i9 = Q_stricmp(tmp_u8,&g_unk_0026ea14);
      if (tmp_i9 != 0) {
        tmp_u8 = va("%s_Moving",tmp_u8);
        tmp_pc10 = "opening";
LAB_000a4278:
        Bot_Util_SendTrigger(tmp_i11,0,tmp_u8,tmp_pc10);
      }
      break;
    case 4:
      *(float *)(tmp_i11 + 0x18) = *(float *)(tmp_i11 + 0x230);
      *(float *)(tmp_i11 + 0x1c) = *(float *)(tmp_i11 + 0x234);
      *(float *)(tmp_i11 + 0x20) = *(float *)(tmp_i11 + 0x238);
      if (*(float *)(tmp_i11 + 0x26c) == 0.0) {
        tmp_i9 = *(int *)(tmp_i11 + 0x27c);
      }
      else {
        tmp_i9 = *(int *)(tmp_i11 + 0x280);
      }
      tmp_f1 = 1000.0 / (float)tmp_i9;
      *(int *)(tmp_i11 + 0x14) = tmp_i9;
      *(uint32_t *)(tmp_i11 + 0xc) = 3;
      *(float *)(tmp_i11 + 0x24) = (*(float *)(tmp_i11 + 0x224) - *(float *)(tmp_i11 + 0x230)) * tmp_f1;
      *(float *)(tmp_i11 + 0x28) = (*(float *)(tmp_i11 + 0x228) - *(float *)(tmp_i11 + 0x234)) * tmp_f1;
      *(float *)(tmp_i11 + 0x2c) = tmp_f1 * (*(float *)(tmp_i11 + 0x22c) - *(float *)(tmp_i11 + 0x238));
      tmp_u8 = _GetEntityName(tmp_i11);
      tmp_i9 = Q_stricmp(tmp_u8,&g_unk_0026ea14);
      if (tmp_i9 != 0) {
        tmp_u8 = va("%s_Moving",tmp_u8);
        tmp_pc10 = "closing";
        goto LAB_000a4278;
      }
      break;
    case 5:
      *(float *)(tmp_i11 + 0x18) = *(float *)(tmp_i11 + 0x230);
      *(float *)(tmp_i11 + 0x1c) = *(float *)(tmp_i11 + 0x234);
      *(float *)(tmp_i11 + 0x20) = *(float *)(tmp_i11 + 0x238);
      tmp_f4 = *(float *)(tmp_i11 + 0x240) - *(float *)(tmp_i11 + 0x234);
      tmp_f3 = *(float *)(tmp_i11 + 0x244) - *(float *)(tmp_i11 + 0x238);
      tmp_i9 = *(int *)(tmp_i11 + 0x14);
      tmp_f1 = *(float *)(tmp_i11 + 0x23c) - *(float *)(tmp_i11 + 0x230);
      goto LAB_000a413c;
    case 6:
      *(float *)(tmp_i11 + 0x18) = *(float *)(tmp_i11 + 0x23c);
      *(float *)(tmp_i11 + 0x1c) = *(float *)(tmp_i11 + 0x240);
      *(float *)(tmp_i11 + 0x20) = *(float *)(tmp_i11 + 0x244);
      tmp_f4 = *(float *)(tmp_i11 + 0x234) - *(float *)(tmp_i11 + 0x240);
      tmp_f3 = *(float *)(tmp_i11 + 0x238) - *(float *)(tmp_i11 + 0x244);
      tmp_i9 = *(int *)(tmp_i11 + 0x14);
      tmp_f1 = *(float *)(tmp_i11 + 0x230) - *(float *)(tmp_i11 + 0x23c);
LAB_000a413c:
      local_20 = 1000.0 / (float)tmp_i9;
      *(uint32_t *)(tmp_i11 + 0xc) = 3;
      *(float *)(tmp_i11 + 0x24) = tmp_f1 * local_20;
      *(float *)(tmp_i11 + 0x28) = tmp_f4 * local_20;
      *(float *)(tmp_i11 + 0x2c) = tmp_f3 * local_20;
      break;
    case 7:
      *(uint32_t *)(tmp_i11 + 0x30) = 0;
      *(uint32_t *)(tmp_i11 + 0x3c) = *(uint32_t *)(tmp_i11 + 0x174);
      *(uint32_t *)(tmp_i11 + 0x40) = *(uint32_t *)(tmp_i11 + 0x178);
      *(uint32_t *)(tmp_i11 + 0x44) = *(uint32_t *)(tmp_i11 + 0x17c);
      tmp_u8 = _GetEntityName(tmp_i11);
      tmp_i9 = Q_stricmp(tmp_u8,&g_unk_0026ea14);
      if (tmp_i9 != 0) {
        tmp_u8 = va("%s_Moving",tmp_u8);
        tmp_pc10 = "closed";
        goto LAB_000a4278;
      }
      break;
    case 8:
      *(uint32_t *)(tmp_i11 + 0x30) = 0;
      *(uint32_t *)(tmp_i11 + 0x3c) = *(uint32_t *)(tmp_i11 + 0x174);
      *(uint32_t *)(tmp_i11 + 0x40) = *(uint32_t *)(tmp_i11 + 0x178);
      *(uint32_t *)(tmp_i11 + 0x44) = *(uint32_t *)(tmp_i11 + 0x17c);
      tmp_u8 = _GetEntityName(tmp_i11);
      tmp_i9 = Q_stricmp(tmp_u8,&g_unk_0026ea14);
      if (tmp_i9 != 0) {
        tmp_u8 = va("%s_Moving",tmp_u8);
        tmp_pc10 = "opened";
        goto LAB_000a4278;
      }
      break;
    case 9:
      tmp_i9 = *(int *)(tmp_i11 + 0x27c);
      *(uint32_t *)(tmp_i11 + 0x44) = 0;
      *(uint32_t *)(tmp_i11 + 0x40) = 0;
      *(uint32_t *)(tmp_i11 + 0x3c) = 0;
      tmp_f1 = (float)tmp_i9;
      if ((tmp_u7 & 0x40) == 0) {
        local_20 = 1000.0;
      }
      else {
        local_20 = 500.0;
        tmp_i9 = tmp_i9 * 2;
      }
      local_20 = local_20 / tmp_f1;
      local_20 = local_20 * *(float *)(tmp_i11 + 0x250);
      *(int *)(tmp_i11 + 0x38) = tmp_i9;
      *(uint32_t *)(tmp_i11 + 0x30) = 3;
      *(float *)(tmp_i11 + 0x48) = *(float *)(tmp_i11 + 0x324) * local_20;
      *(float *)(tmp_i11 + 0x4c) = *(float *)(tmp_i11 + 0x328) * local_20;
      *(float *)(tmp_i11 + 0x50) = local_20 * *(float *)(tmp_i11 + 0x32c);
      break;
    case 10:
      tmp_f1 = *(float *)(tmp_i11 + 0x250);
      tmp_f3 = *(float *)(tmp_i11 + 0x324) * tmp_f1;
      tmp_i9 = *(int *)(tmp_i11 + 0x27c);
      *(float *)(tmp_i11 + 0x3c) = tmp_f3;
      tmp_f4 = *(float *)(tmp_i11 + 0x328) * tmp_f1;
      *(float *)(tmp_i11 + 0x40) = tmp_f4;
      tmp_f1 = tmp_f1 * *(float *)(tmp_i11 + 0x32c);
      *(float *)(tmp_i11 + 0x44) = tmp_f1;
      tmp_f5 = 1000.0 / (float)tmp_i9;
      if ((tmp_u7 & 0x40) == 0) {
        *(int *)(tmp_i11 + 0x38) = tmp_i9;
      }
      else {
        *(int *)(tmp_i11 + 0x38) = tmp_i9 * 2;
        tmp_f5 = tmp_f5 * 0.5;
      }
      tmp_f5 = -tmp_f5;
      *(uint32_t *)(tmp_i11 + 0x30) = 3;
      *(uint32_t *)(tmp_i11 + 0x368) = 0;
      *(float *)(tmp_i11 + 0x48) = tmp_f3 * tmp_f5;
      *(float *)(tmp_i11 + 0x4c) = tmp_f4 * tmp_f5;
      *(float *)(tmp_i11 + 0x50) = tmp_f5 * tmp_f1;
    }
    BG_EvaluateTrajectory
              (tmp_i11 + 0xc,g_unk_00abe908,tmp_i11 + 0x168,0,*(uint32_t *)(tmp_i11 + 0x110));
    if (((*(byte *)(tmp_i11 + 0x128) & 1) == 0) || (*(int *)(tmp_i11 + 0x14c) != 0)) {
      trap_LinkEntity(tmp_i11);
    }
    tmp_i11 = *(int *)(tmp_i11 + 0x2f4);
    if (tmp_i11 == 0) {
      return;
    }
  } while( true );
}

void Think_SpawnNewDoorTrigger(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint32_t tmp_u6;
  int tmp_i7;
  uint tmp_u8;
  uint32_t tmp_u9;
  int tmp_i10;
  char *tmp_pc11;
  float local_40;
  float local_34 [9];
  
  for (tmp_i7 = param_1; tmp_i7 != 0; tmp_i7 = *(int *)(tmp_i7 + 0x2f4)) {
    *(uint32_t *)(tmp_i7 + 0x2cc) = 1;
  }
  local_34[0] = *(float *)(param_1 + 0x150);
  local_34[1] = *(float *)(param_1 + 0x154);
  local_34[2] = *(float *)(param_1 + 0x158);
  local_34[3] = *(float *)(param_1 + 0x15c);
  local_34[4] = *(float *)(param_1 + 0x160);
  local_34[5] = *(float *)(param_1 + 0x164);
  for (tmp_i7 = *(int *)(param_1 + 0x2f4); tmp_i7 != 0; tmp_i7 = *(int *)(tmp_i7 + 0x2f4)) {
    AddPointToBounds(tmp_i7 + 0x150,local_34,local_34 + 3);
    AddPointToBounds(tmp_i7 + 0x15c,local_34,local_34 + 3);
  }
  tmp_f1 = local_34[1];
  tmp_f5 = local_34[4];
  if (local_34[3] - local_34[0] <= local_34[4] - local_34[1]) {
    tmp_f1 = local_34[0];
    tmp_f5 = local_34[3];
  }
  tmp_f4 = local_34[5] - local_34[2];
  tmp_f3 = local_34[5];
  tmp_u8 = 2;
  if (tmp_f5 - tmp_f1 <= tmp_f4) {
    tmp_f3 = tmp_f5;
    tmp_u8 = (uint)(local_34[4] - local_34[1] < local_34[3] - local_34[0]);
  }
  local_34[tmp_u8 + 3] = tmp_f3 + 120.0;
  tmp_f3 = local_34[2];
  if (tmp_f5 - tmp_f1 <= tmp_f4) {
    tmp_f3 = tmp_f1;
  }
  local_34[tmp_u8] = tmp_f3 - 120.0;
  tmp_i7 = G_Spawn();
  *(uint32_t *)(tmp_i7 + 0x14c) = 0x40000000;
  *(float *)(tmp_i7 + 0x134) = local_34[0];
  *(int *)(tmp_i7 + 0x218) = param_1;
  *(float *)(tmp_i7 + 0x138) = local_34[1];
  *(void **)(tmp_i7 + 0x2b0) = Touch_DoorTrigger;
  *(float *)(tmp_i7 + 0x13c) = local_34[2];
  *(float *)(tmp_i7 + 0x140) = local_34[3];
  *(float *)(tmp_i7 + 0x144) = local_34[4];
  *(float *)(tmp_i7 + 0x148) = local_34[5];
  trap_LinkEntity(tmp_i7);
  tmp_u6 = g_unk_00abe908;
  tmp_u2 = *(uint32_t *)(param_1 + 0x1e4);
  tmp_i7 = param_1;
  do {
    tmp_u8 = *(uint *)(tmp_i7 + 0x1b0);
    if ((*(byte *)(param_1 + 0x1b0) & 0x40) != 0) {
      tmp_u8 = tmp_u8 | 0x40;
      *(uint *)(tmp_i7 + 0x1b0) = tmp_u8;
    }
    *(uint32_t *)(tmp_i7 + 0x1e4) = tmp_u2;
    *(uint32_t *)(tmp_i7 + 0x10) = tmp_u6;
    *(uint32_t *)(tmp_i7 + 0x34) = tmp_u6;
    switch(tmp_u2) {
    case 0:
      *(uint32_t *)(tmp_i7 + 0xc) = 0;
      *(uint32_t *)(tmp_i7 + 0x18) = *(uint32_t *)(tmp_i7 + 0x224);
      *(uint32_t *)(tmp_i7 + 0x368) = 0;
      *(uint32_t *)(tmp_i7 + 0x1c) = *(uint32_t *)(tmp_i7 + 0x228);
      *(uint32_t *)(tmp_i7 + 0x20) = *(uint32_t *)(tmp_i7 + 0x22c);
      break;
    case 1:
      *(uint32_t *)(tmp_i7 + 0xc) = 0;
      *(uint32_t *)(tmp_i7 + 0x18) = *(uint32_t *)(tmp_i7 + 0x230);
      *(uint32_t *)(tmp_i7 + 0x1c) = *(uint32_t *)(tmp_i7 + 0x234);
      *(uint32_t *)(tmp_i7 + 0x20) = *(uint32_t *)(tmp_i7 + 0x238);
      break;
    case 2:
      *(uint32_t *)(tmp_i7 + 0xc) = 0;
      *(uint32_t *)(tmp_i7 + 0x18) = *(uint32_t *)(tmp_i7 + 0x23c);
      *(uint32_t *)(tmp_i7 + 0x1c) = *(uint32_t *)(tmp_i7 + 0x240);
      *(uint32_t *)(tmp_i7 + 0x20) = *(uint32_t *)(tmp_i7 + 0x244);
      break;
    case 3:
      *(float *)(tmp_i7 + 0x18) = *(float *)(tmp_i7 + 0x224);
      *(float *)(tmp_i7 + 0x1c) = *(float *)(tmp_i7 + 0x228);
      *(uint32_t *)(tmp_i7 + 0x14) = *(uint32_t *)(tmp_i7 + 0x27c);
      *(float *)(tmp_i7 + 0x20) = *(float *)(tmp_i7 + 0x22c);
      tmp_f1 = 1000.0 / (float)*(int *)(tmp_i7 + 0x27c);
      *(uint32_t *)(tmp_i7 + 0xc) = 3;
      *(float *)(tmp_i7 + 0x24) = (*(float *)(tmp_i7 + 0x230) - *(float *)(tmp_i7 + 0x224)) * tmp_f1;
      *(float *)(tmp_i7 + 0x28) = (*(float *)(tmp_i7 + 0x234) - *(float *)(tmp_i7 + 0x228)) * tmp_f1;
      *(float *)(tmp_i7 + 0x2c) = tmp_f1 * (*(float *)(tmp_i7 + 0x238) - *(float *)(tmp_i7 + 0x22c));
      tmp_u9 = _GetEntityName(tmp_i7);
      tmp_i10 = Q_stricmp(tmp_u9,&g_unk_0026ea14);
      if (tmp_i10 != 0) {
        tmp_u9 = va("%s_Moving",tmp_u9);
        tmp_pc11 = "opening";
LAB_000a5018:
        Bot_Util_SendTrigger(tmp_i7,0,tmp_u9,tmp_pc11);
      }
      break;
    case 4:
      *(float *)(tmp_i7 + 0x18) = *(float *)(tmp_i7 + 0x230);
      *(float *)(tmp_i7 + 0x1c) = *(float *)(tmp_i7 + 0x234);
      *(float *)(tmp_i7 + 0x20) = *(float *)(tmp_i7 + 0x238);
      if (*(float *)(tmp_i7 + 0x26c) == 0.0) {
        tmp_i10 = *(int *)(tmp_i7 + 0x27c);
      }
      else {
        tmp_i10 = *(int *)(tmp_i7 + 0x280);
      }
      tmp_f1 = 1000.0 / (float)tmp_i10;
      *(int *)(tmp_i7 + 0x14) = tmp_i10;
      *(uint32_t *)(tmp_i7 + 0xc) = 3;
      *(float *)(tmp_i7 + 0x24) = (*(float *)(tmp_i7 + 0x224) - *(float *)(tmp_i7 + 0x230)) * tmp_f1;
      *(float *)(tmp_i7 + 0x28) = (*(float *)(tmp_i7 + 0x228) - *(float *)(tmp_i7 + 0x234)) * tmp_f1;
      *(float *)(tmp_i7 + 0x2c) = tmp_f1 * (*(float *)(tmp_i7 + 0x22c) - *(float *)(tmp_i7 + 0x238));
      tmp_u9 = _GetEntityName(tmp_i7);
      tmp_i10 = Q_stricmp(tmp_u9,&g_unk_0026ea14);
      if (tmp_i10 != 0) {
        tmp_u9 = va("%s_Moving",tmp_u9);
        tmp_pc11 = "closing";
        goto LAB_000a5018;
      }
      break;
    case 5:
      *(float *)(tmp_i7 + 0x18) = *(float *)(tmp_i7 + 0x230);
      *(float *)(tmp_i7 + 0x1c) = *(float *)(tmp_i7 + 0x234);
      *(float *)(tmp_i7 + 0x20) = *(float *)(tmp_i7 + 0x238);
      tmp_f4 = *(float *)(tmp_i7 + 0x240) - *(float *)(tmp_i7 + 0x234);
      tmp_f5 = *(float *)(tmp_i7 + 0x244) - *(float *)(tmp_i7 + 0x238);
      tmp_i10 = *(int *)(tmp_i7 + 0x14);
      tmp_f1 = *(float *)(tmp_i7 + 0x23c) - *(float *)(tmp_i7 + 0x230);
      goto LAB_000a4edc;
    case 6:
      *(float *)(tmp_i7 + 0x18) = *(float *)(tmp_i7 + 0x23c);
      *(float *)(tmp_i7 + 0x1c) = *(float *)(tmp_i7 + 0x240);
      *(float *)(tmp_i7 + 0x20) = *(float *)(tmp_i7 + 0x244);
      tmp_f4 = *(float *)(tmp_i7 + 0x234) - *(float *)(tmp_i7 + 0x240);
      tmp_f5 = *(float *)(tmp_i7 + 0x238) - *(float *)(tmp_i7 + 0x244);
      tmp_i10 = *(int *)(tmp_i7 + 0x14);
      tmp_f1 = *(float *)(tmp_i7 + 0x230) - *(float *)(tmp_i7 + 0x23c);
LAB_000a4edc:
      local_40 = 1000.0 / (float)tmp_i10;
      *(uint32_t *)(tmp_i7 + 0xc) = 3;
      *(float *)(tmp_i7 + 0x24) = tmp_f1 * local_40;
      *(float *)(tmp_i7 + 0x28) = tmp_f4 * local_40;
      *(float *)(tmp_i7 + 0x2c) = tmp_f5 * local_40;
      break;
    case 7:
      *(uint32_t *)(tmp_i7 + 0x30) = 0;
      *(uint32_t *)(tmp_i7 + 0x3c) = *(uint32_t *)(tmp_i7 + 0x174);
      *(uint32_t *)(tmp_i7 + 0x40) = *(uint32_t *)(tmp_i7 + 0x178);
      *(uint32_t *)(tmp_i7 + 0x44) = *(uint32_t *)(tmp_i7 + 0x17c);
      tmp_u9 = _GetEntityName(tmp_i7);
      tmp_i10 = Q_stricmp(tmp_u9,&g_unk_0026ea14);
      if (tmp_i10 != 0) {
        tmp_u9 = va("%s_Moving",tmp_u9);
        tmp_pc11 = "closed";
        goto LAB_000a5018;
      }
      break;
    case 8:
      *(uint32_t *)(tmp_i7 + 0x30) = 0;
      *(uint32_t *)(tmp_i7 + 0x3c) = *(uint32_t *)(tmp_i7 + 0x174);
      *(uint32_t *)(tmp_i7 + 0x40) = *(uint32_t *)(tmp_i7 + 0x178);
      *(uint32_t *)(tmp_i7 + 0x44) = *(uint32_t *)(tmp_i7 + 0x17c);
      tmp_u9 = _GetEntityName(tmp_i7);
      tmp_i10 = Q_stricmp(tmp_u9,&g_unk_0026ea14);
      if (tmp_i10 != 0) {
        tmp_u9 = va("%s_Moving",tmp_u9);
        tmp_pc11 = "opened";
        goto LAB_000a5018;
      }
      break;
    case 9:
      tmp_i10 = *(int *)(tmp_i7 + 0x27c);
      *(uint32_t *)(tmp_i7 + 0x44) = 0;
      *(uint32_t *)(tmp_i7 + 0x40) = 0;
      *(uint32_t *)(tmp_i7 + 0x3c) = 0;
      tmp_f1 = (float)tmp_i10;
      if ((tmp_u8 & 0x40) == 0) {
        local_40 = 1000.0;
      }
      else {
        local_40 = 500.0;
        tmp_i10 = tmp_i10 * 2;
      }
      local_40 = local_40 / tmp_f1;
      local_40 = local_40 * *(float *)(tmp_i7 + 0x250);
      *(int *)(tmp_i7 + 0x38) = tmp_i10;
      *(uint32_t *)(tmp_i7 + 0x30) = 3;
      *(float *)(tmp_i7 + 0x48) = *(float *)(tmp_i7 + 0x324) * local_40;
      *(float *)(tmp_i7 + 0x4c) = *(float *)(tmp_i7 + 0x328) * local_40;
      *(float *)(tmp_i7 + 0x50) = local_40 * *(float *)(tmp_i7 + 0x32c);
      break;
    case 10:
      tmp_f1 = *(float *)(tmp_i7 + 0x250);
      tmp_f5 = *(float *)(tmp_i7 + 0x324) * tmp_f1;
      tmp_i10 = *(int *)(tmp_i7 + 0x27c);
      *(float *)(tmp_i7 + 0x3c) = tmp_f5;
      tmp_f4 = *(float *)(tmp_i7 + 0x328) * tmp_f1;
      *(float *)(tmp_i7 + 0x40) = tmp_f4;
      tmp_f1 = tmp_f1 * *(float *)(tmp_i7 + 0x32c);
      *(float *)(tmp_i7 + 0x44) = tmp_f1;
      tmp_f3 = 1000.0 / (float)tmp_i10;
      if ((tmp_u8 & 0x40) == 0) {
        *(int *)(tmp_i7 + 0x38) = tmp_i10;
      }
      else {
        *(int *)(tmp_i7 + 0x38) = tmp_i10 * 2;
        tmp_f3 = tmp_f3 * 0.5;
      }
      tmp_f3 = -tmp_f3;
      *(uint32_t *)(tmp_i7 + 0x30) = 3;
      *(uint32_t *)(tmp_i7 + 0x368) = 0;
      *(float *)(tmp_i7 + 0x48) = tmp_f5 * tmp_f3;
      *(float *)(tmp_i7 + 0x4c) = tmp_f4 * tmp_f3;
      *(float *)(tmp_i7 + 0x50) = tmp_f3 * tmp_f1;
    }
    BG_EvaluateTrajectory(tmp_i7 + 0xc,g_unk_00abe908,tmp_i7 + 0x168,0,*(uint32_t *)(tmp_i7 + 0x110));
    if (((*(byte *)(tmp_i7 + 0x128) & 1) == 0) || (*(int *)(tmp_i7 + 0x14c) != 0)) {
      trap_LinkEntity(tmp_i7);
    }
    tmp_i7 = *(int *)(tmp_i7 + 0x2f4);
    if (tmp_i7 == 0) {
      return;
    }
  } while( true );
}

void Use_TrinaryMover(int param_1,int param_2,int param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
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
  
  uStack_14 = 0xa73a9;
  do {
    if ((*(int *)(param_1 + 0x5c0) == 0x3bf8a) && ((*(byte *)(param_1 + 0x1a8) & 0x20) == 0)) {
      if (param_3 != 0) {
LAB_000a740a:
        tmp_f2 = (*(float *)(param_1 + 0x150) + *(float *)(param_1 + 0x15c)) * 0.5;
        tmp_f1 = (*(float *)(param_1 + 0x154) + *(float *)(param_1 + 0x160)) * 0.5;
        tmp_f3 = (*(float *)(param_1 + 0x158) + *(float *)(param_1 + 0x164)) * 0.5;
        local_4c = tmp_f2 - *(float *)(param_1 + 0x5c);
        local_48 = tmp_f1 - *(float *)(param_1 + 0x60);
        local_44 = tmp_f3 - *(float *)(param_1 + 100);
        vectoangles(&local_4c,&local_40);
        if (*(float *)(param_1 + 0x328) == 0.0) {
          if (*(float *)(param_1 + 0x324) == 0.0) {
            if (*(float *)(param_1 + 0x32c) != 0.0) {
              local_38 = local_38 + *(float *)(param_1 + 0x250);
            }
          }
          else {
            local_40 = local_40 + *(float *)(param_1 + 0x250);
          }
        }
        else {
          local_3c = local_3c + *(float *)(param_1 + 0x250);
        }
        AngleVectors(&local_40,&local_28,0,0);
        if (param_3 == 0) {
          local_34 = *(float *)(param_2 + 0x168);
          local_30 = *(float *)(param_2 + 0x16c);
          local_2c = *(float *)(param_2 + 0x170);
        }
        else {
          local_34 = *(float *)(param_3 + 0x168);
          local_30 = *(float *)(param_3 + 0x16c);
          local_2c = *(float *)(param_3 + 0x170);
        }
        local_2c = local_2c - tmp_f3;
        local_30 = local_30 - tmp_f1;
        local_34 = local_34 - tmp_f2;
        VectorNormalize(&local_34);
        if (0.0 <= local_2c * local_20 + local_30 * local_24 + local_34 * local_28) {
          tmp_i6 = g_unk_00abe908 + 0x32;
          tmp_i7 = param_1;
          do {
            tmp_u4 = *(uint *)(tmp_i7 + 0x1b0);
            *(float *)(tmp_i7 + 0x250) = -*(float *)(tmp_i7 + 0x250);
            if ((*(byte *)(param_1 + 0x1b0) & 0x40) != 0) {
              tmp_u4 = tmp_u4 | 0x40;
              *(uint *)(tmp_i7 + 0x1b0) = tmp_u4;
            }
            tmp_i5 = *(int *)(tmp_i7 + 0x27c);
            *(uint32_t *)(tmp_i7 + 0x1e4) = 9;
            *(int *)(tmp_i7 + 0x10) = tmp_i6;
            *(int *)(tmp_i7 + 0x34) = tmp_i6;
            *(uint32_t *)(tmp_i7 + 0x44) = 0;
            tmp_f2 = (float)tmp_i5;
            *(uint32_t *)(tmp_i7 + 0x40) = 0;
            *(uint32_t *)(tmp_i7 + 0x3c) = 0;
            if ((tmp_u4 & 0x40) == 0) {
              tmp_f1 = 1000.0;
            }
            else {
              tmp_f1 = 500.0;
              tmp_i5 = tmp_i5 * 2;
            }
            tmp_f2 = (tmp_f1 / tmp_f2) * *(float *)(tmp_i7 + 0x250);
            *(int *)(tmp_i7 + 0x38) = tmp_i5;
            *(uint32_t *)(tmp_i7 + 0x30) = 3;
            *(float *)(tmp_i7 + 0x48) = *(float *)(tmp_i7 + 0x324) * tmp_f2;
            *(float *)(tmp_i7 + 0x4c) = *(float *)(tmp_i7 + 0x328) * tmp_f2;
            *(float *)(tmp_i7 + 0x50) = tmp_f2 * *(float *)(tmp_i7 + 0x32c);
            BG_EvaluateTrajectory
                      (tmp_i7 + 0xc,g_unk_00abe908,tmp_i7 + 0x168,0,*(uint32_t *)(tmp_i7 + 0x110));
            if (((*(byte *)(tmp_i7 + 0x128) & 1) == 0) || (*(int *)(tmp_i7 + 0x14c) != 0)) {
              trap_LinkEntity(tmp_i7);
            }
            tmp_i7 = *(int *)(tmp_i7 + 0x2f4);
          } while (tmp_i7 != 0);
          G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x1ec));
          *(uint32_t *)(param_1 + 0xa0) = *(uint32_t *)(param_1 + 0x1f8);
          if ((*(int *)(param_1 + 0x2f8) != param_1) && (*(int *)(param_1 + 0x2f8) != 0)) {
            return;
          }
          trap_AdjustAreaPortalState(param_1,1);
          return;
        }
        goto LAB_000a73d8;
      }
      if (param_2 == 0) goto LAB_000a73d8;
      tmp_i6 = Q_stricmp(*(uint32_t *)(param_2 + 0x1a4),"target_relay");
      if (tmp_i6 == 0) goto LAB_000a740a;
      tmp_u4 = *(uint *)(param_1 + 0x1b0);
    }
    else {
LAB_000a73d8:
      tmp_u4 = *(uint *)(param_1 + 0x1b0);
    }
    if ((tmp_u4 & 0x400) == 0) {
      tmp_i6 = *(int *)(param_1 + 0x1e4);
      *(int *)(param_1 + 0x2f0) = param_3;
      if (tmp_i6 == 0) {
        tmp_i7 = g_unk_00abe908 + 0x32;
        tmp_i6 = param_1;
        while( true ) {
          if ((tmp_u4 & 0x40) != 0) {
            *(uint *)(tmp_i6 + 0x1b0) = *(uint *)(tmp_i6 + 0x1b0) | 0x40;
          }
          SetMoverState(tmp_i6,3,tmp_i7);
          tmp_i6 = *(int *)(tmp_i6 + 0x2f4);
          if (tmp_i6 == 0) break;
          tmp_u4 = *(uint *)(param_1 + 0x1b0);
        }
        G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x1ec));
        *(uint32_t *)(param_1 + 0xa0) = *(uint32_t *)(param_1 + 0x1f8);
        if ((*(int *)(param_1 + 0x2f8) == param_1) || (*(int *)(param_1 + 0x2f8) == 0)) {
          trap_AdjustAreaPortalState(param_1,1);
        }
      }
      else if (tmp_i6 == 1) {
        tmp_i7 = g_unk_00abe908 + 0x32;
        tmp_i6 = param_1;
        while( true ) {
          if ((tmp_u4 & 0x40) != 0) {
            *(uint *)(tmp_i6 + 0x1b0) = *(uint *)(tmp_i6 + 0x1b0) | 0x40;
          }
          SetMoverState(tmp_i6,5,tmp_i7);
          tmp_i6 = *(int *)(tmp_i6 + 0x2f4);
          if (tmp_i6 == 0) break;
          tmp_u4 = *(uint *)(param_1 + 0x1b0);
        }
        G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x1fc));
        *(uint32_t *)(param_1 + 0xa0) = *(uint32_t *)(param_1 + 0x1f8);
      }
      else if (tmp_i6 == 2) {
        if (*(float *)(param_1 + 0x30c) != -1000.0) {
          *(int *)(param_1 + 0x29c) = (int)ROUND((float)g_unk_00abe908 + *(float *)(param_1 + 0x30c));
        }
      }
      else if (tmp_i6 == 4) {
        tmp_i6 = *(int *)(param_1 + 0x14);
        tmp_i7 = g_unk_00abe908 - *(int *)(param_1 + 0x54);
        if (tmp_i6 < tmp_i7) {
          tmp_i7 = tmp_i6;
        }
        tmp_i6 = g_unk_00abe908 + (tmp_i7 - tmp_i6);
        tmp_i7 = param_1;
        while( true ) {
          if ((tmp_u4 & 0x40) != 0) {
            *(uint *)(tmp_i7 + 0x1b0) = *(uint *)(tmp_i7 + 0x1b0) | 0x40;
          }
          SetMoverState(tmp_i7,3,tmp_i6);
          tmp_i7 = *(int *)(tmp_i7 + 0x2f4);
          if (tmp_i7 == 0) break;
          tmp_u4 = *(uint *)(param_1 + 0x1b0);
        }
        G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x1ec));
      }
      else if (tmp_i6 == 6) {
        tmp_i6 = *(int *)(param_1 + 0x14);
        tmp_i7 = g_unk_00abe908 - *(int *)(param_1 + 0x54);
        if (tmp_i6 < tmp_i7) {
          tmp_i7 = tmp_i6;
        }
        tmp_i6 = g_unk_00abe908 + (tmp_i7 - tmp_i6);
        tmp_i7 = param_1;
        while( true ) {
          if ((tmp_u4 & 0x40) != 0) {
            *(uint *)(tmp_i7 + 0x1b0) = *(uint *)(tmp_i7 + 0x1b0) | 0x40;
          }
          SetMoverState(tmp_i7,5,tmp_i6);
          tmp_i7 = *(int *)(tmp_i7 + 0x2f4);
          if (tmp_i7 == 0) break;
          tmp_u4 = *(uint *)(param_1 + 0x1b0);
        }
        G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x1fc));
      }
      else if (tmp_i6 == 3) {
        tmp_i6 = *(int *)(param_1 + 0x14);
        tmp_i7 = g_unk_00abe908 - *(int *)(param_1 + 0x54);
        if (tmp_i6 < tmp_i7) {
          tmp_i7 = tmp_i6;
        }
        tmp_i6 = g_unk_00abe908 + (tmp_i7 - tmp_i6);
        tmp_i7 = param_1;
        while( true ) {
          if ((tmp_u4 & 0x40) != 0) {
            *(uint *)(tmp_i7 + 0x1b0) = *(uint *)(tmp_i7 + 0x1b0) | 0x40;
          }
          SetMoverState(tmp_i7,4,tmp_i6);
          tmp_i7 = *(int *)(tmp_i7 + 0x2f4);
          if (tmp_i7 == 0) break;
          tmp_u4 = *(uint *)(param_1 + 0x1b0);
        }
        if ((*(byte *)(param_1 + 0x1b0) & 0x40) == 0) {
          G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x1f0));
        }
        else {
          G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x210));
        }
      }
      else if (tmp_i6 == 5) {
        tmp_i6 = *(int *)(param_1 + 0x14);
        tmp_i7 = g_unk_00abe908 - *(int *)(param_1 + 0x54);
        if (tmp_i6 < tmp_i7) {
          tmp_i7 = tmp_i6;
        }
        tmp_i6 = g_unk_00abe908 + (tmp_i7 - tmp_i6);
        tmp_i7 = param_1;
        while( true ) {
          if ((tmp_u4 & 0x40) != 0) {
            *(uint *)(tmp_i7 + 0x1b0) = *(uint *)(tmp_i7 + 0x1b0) | 0x40;
          }
          SetMoverState(tmp_i7,6,tmp_i6);
          tmp_i7 = *(int *)(tmp_i7 + 0x2f4);
          if (tmp_i7 == 0) break;
          tmp_u4 = *(uint *)(param_1 + 0x1b0);
        }
        G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x200));
      }
      return;
    }
    param_1 = *(int *)(param_1 + 0x2f8);
  } while( true );
}

void Use_BinaryMover(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint *tmp_pu1;
  float tmp_f2;
  bool tmp_b3;
  float tmp_f4;
  uint32_t tmp_u5;
  int tmp_i6;
  uint tmp_u7;
  int tmp_i8;
  int tmp_i9;
  
  tmp_b3 = g_unk_00abe908 < 0xfa1;
  tmp_u7 = *(uint *)(param_1 + 0x1b0);
  while ((tmp_u7 & 0x400) != 0) {
    if ((tmp_u7 & 0x40) != 0) {
      tmp_pu1 = (uint *)(*(int *)(param_1 + 0x2f8) + 0x1b0);
      *tmp_pu1 = *tmp_pu1 | 0x40;
    }
    param_1 = *(int *)(param_1 + 0x2f8);
    tmp_u7 = *(uint *)(param_1 + 0x1b0);
  }
  if (*(int *)(param_1 + 0x254) != 0) {
    tmp_u5 = va("%s activated",*(int *)(param_1 + 0x254));
    Bot_Util_SendTrigger(param_1,0,tmp_u5,"pushed");
  }
  if (((*(int *)(param_1 + 0x1e4) == 7) || (*(int *)(param_1 + 0x1e4) == 0)) &&
     (tmp_i6 = IsBinaryMoverBlocked(param_1,param_2,param_3), tmp_i6 != 0)) {
    tmp_i6 = g_unk_00abe908 + 0x32;
    tmp_i9 = param_1;
    do {
      tmp_u7 = *(uint *)(tmp_i9 + 0x1b0);
      *(float *)(tmp_i9 + 0x250) = -*(float *)(tmp_i9 + 0x250);
      if ((*(byte *)(param_1 + 0x1b0) & 0x40) != 0) {
        tmp_u7 = tmp_u7 | 0x40;
        *(uint *)(tmp_i9 + 0x1b0) = tmp_u7;
      }
      tmp_i8 = *(int *)(tmp_i9 + 0x27c);
      *(uint32_t *)(tmp_i9 + 0x1e4) = 9;
      *(int *)(tmp_i9 + 0x10) = tmp_i6;
      *(int *)(tmp_i9 + 0x34) = tmp_i6;
      *(uint32_t *)(tmp_i9 + 0x44) = 0;
      tmp_f4 = (float)tmp_i8;
      *(uint32_t *)(tmp_i9 + 0x40) = 0;
      *(uint32_t *)(tmp_i9 + 0x3c) = 0;
      if ((tmp_u7 & 0x40) == 0) {
        tmp_f2 = 1000.0;
      }
      else {
        tmp_f2 = 500.0;
        tmp_i8 = tmp_i8 * 2;
      }
      tmp_f4 = (tmp_f2 / tmp_f4) * *(float *)(tmp_i9 + 0x250);
      *(int *)(tmp_i9 + 0x38) = tmp_i8;
      *(uint32_t *)(tmp_i9 + 0x30) = 3;
      *(float *)(tmp_i9 + 0x48) = *(float *)(tmp_i9 + 0x324) * tmp_f4;
      *(float *)(tmp_i9 + 0x4c) = *(float *)(tmp_i9 + 0x328) * tmp_f4;
      *(float *)(tmp_i9 + 0x50) = tmp_f4 * *(float *)(tmp_i9 + 0x32c);
      BG_EvaluateTrajectory(tmp_i9 + 0xc,g_unk_00abe908,tmp_i9 + 0x168,0,*(uint32_t *)(tmp_i9 + 0x110))
      ;
      if (((*(byte *)(tmp_i9 + 0x128) & 1) == 0) || (*(int *)(tmp_i9 + 0x14c) != 0)) {
        trap_LinkEntity(tmp_i9);
      }
      tmp_i9 = *(int *)(tmp_i9 + 0x2f4);
    } while (tmp_i9 != 0);
LAB_000a8c0c:
    if (!tmp_b3) {
      if ((*(byte *)(param_1 + 0x1b0) & 0x40) == 0) {
        G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x1ec));
      }
      else {
        G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x208));
      }
      *(uint32_t *)(param_1 + 0xa0) = *(uint32_t *)(param_1 + 0x1fc);
      goto LAB_000a8c1f;
    }
  }
  else {
    *(uint32_t *)(param_1 + 0x2f0) = param_3;
    tmp_i6 = *(int *)(param_1 + 0x21c);
    if (((tmp_i6 != 0) && (*(float *)(tmp_i6 + 0x30c) == -1.0)) && (*(int *)(tmp_i6 + 0x2e4) == 1)) {
      *(uint32_t *)(tmp_i6 + 0x2e4) = 0;
      return;
    }
    tmp_i6 = *(int *)(param_1 + 0x1e4);
    if (tmp_i6 != 0) {
      if (tmp_i6 != 7) {
        if (tmp_i6 == 1) {
          if ((*(byte *)(param_1 + 0x1b2) & 2) != 0) {
            *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
            return;
          }
          if (*(float *)(param_1 + 0x30c) == -1000.0) {
            return;
          }
          tmp_f4 = (float)g_unk_00abe908 + *(float *)(param_1 + 0x30c);
        }
        else {
          if (tmp_i6 != 8) {
            if (tmp_i6 == 4) {
              if ((*(byte *)(param_1 + 0x1a8) & 4) == 0) {
                tmp_i9 = 4;
                tmp_i6 = param_1;
                while( true ) {
                  tmp_i8 = (g_unk_00abe908 * 2 - *(int *)(tmp_i6 + 0x10)) - *(int *)(tmp_i6 + 0x14);
                  if (tmp_i9 == 3) {
                    SetMoverState(tmp_i6,4,tmp_i8);
                  }
                  else {
                    SetMoverState(tmp_i6,3,tmp_i8);
                  }
                  trap_LinkEntity(tmp_i6);
                  tmp_i6 = *(int *)(tmp_i6 + 0x2f4);
                  if (tmp_i6 == 0) break;
                  tmp_i9 = *(int *)(tmp_i6 + 0x1e4);
                }
              }
LAB_000a8eb2:
              if (tmp_b3) {
                return;
              }
              G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x1ec));
              return;
            }
            if (tmp_i6 == 3) {
              Blocked_Door(param_1,0);
              if (tmp_b3) {
                return;
              }
            }
            else {
              if (tmp_i6 == 10) {
                Blocked_DoorRotate(param_1,0);
                goto LAB_000a8eb2;
              }
              if (tmp_i6 != 9) {
                return;
              }
              Blocked_DoorRotate(param_1,0);
              if (tmp_b3) {
                return;
              }
              if ((*(byte *)(param_1 + 0x1b0) & 0x40) != 0) {
                G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x210));
                return;
              }
            }
            G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x1f0));
            return;
          }
          if ((*(byte *)(param_1 + 0x1b2) & 2) != 0) {
            *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
            return;
          }
          tmp_f4 = (float)g_unk_00abe908 + *(float *)(param_1 + 0x30c);
        }
        *(int *)(param_1 + 0x29c) = (int)ROUND(tmp_f4);
        return;
      }
      tmp_i9 = g_unk_00abe908 + 0x32;
      tmp_i6 = param_1;
      do {
        if ((*(byte *)(param_1 + 0x1b0) & 0x40) != 0) {
          *(uint *)(tmp_i6 + 0x1b0) = *(uint *)(tmp_i6 + 0x1b0) | 0x40;
        }
        SetMoverState(tmp_i6,9,tmp_i9);
        tmp_i6 = *(int *)(tmp_i6 + 0x2f4);
      } while (tmp_i6 != 0);
      goto LAB_000a8c0c;
    }
    tmp_i9 = g_unk_00abe908 + 0x32;
    tmp_i6 = param_1;
    do {
      if ((*(byte *)(param_1 + 0x1b0) & 0x40) != 0) {
        *(uint *)(tmp_i6 + 0x1b0) = *(uint *)(tmp_i6 + 0x1b0) | 0x40;
      }
      SetMoverState(tmp_i6,3,tmp_i9);
      tmp_i6 = *(int *)(tmp_i6 + 0x2f4);
    } while (tmp_i6 != 0);
    if (!tmp_b3) {
      G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x1ec));
      *(uint32_t *)(param_1 + 0xa0) = *(uint32_t *)(param_1 + 0x1fc);
      goto LAB_000a8c1f;
    }
  }
  *(uint32_t *)(param_1 + 0xa0) = 0;
LAB_000a8c1f:
  if ((*(int *)(param_1 + 0x2f8) != param_1) && (*(int *)(param_1 + 0x2f8) != 0)) {
    return;
  }
  trap_AdjustAreaPortalState(param_1,1);
  return;
}

void Touch_DoorTrigger(int param_1,int param_2)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  float local_30 [6];
  uint8_t local_18 [12];
  
  if ((*(int *)(param_2 + 400) == 0) || (*(int *)(*(int *)(param_2 + 400) + 3000) != 3)) {
    if (*(int *)(*(int *)(param_1 + 0x218) + 0x1e4) == 3) {
      return;
    }
    Use_BinaryMover(*(int *)(param_1 + 0x218),param_1,param_2);
    return;
  }
  if ((*(uint *)(*(int *)(param_1 + 0x218) + 0x1e4) & 0xfffffffd) == 1) {
    return;
  }
  tmp_i4 = *(int *)(param_1 + 0x2e4);
  local_30[5] = 0.0;
  local_30[4] = 0.0;
  local_30[3] = 0.0;
  tmp_i1 = param_1 + tmp_i4 * 4;
  tmp_f2 = *(float *)(tmp_i1 + 0x15c);
  tmp_f3 = *(float *)(tmp_i1 + 0x150);
  if (ABS(*(float *)(param_2 + 0x5c + tmp_i4 * 4) - tmp_f2) <
      ABS(*(float *)(param_2 + 0x5c + tmp_i4 * 4) - tmp_f3)) {
    tmp_f2 = tmp_f3 - 10.0;
    tmp_f3 = -1.0;
  }
  else {
    tmp_f2 = tmp_f2 + 10.0;
    tmp_f3 = 1.0;
  }
  local_30[tmp_i4 + 3] = tmp_f3;
  local_30[tmp_i4] = tmp_f2;
  if (tmp_i4 == 0) {
    local_30[1] = (*(float *)(param_1 + 0x154) + *(float *)(param_1 + 0x160)) * 0.5;
  }
  else {
    local_30[0] = (*(float *)(param_1 + 0x150) + *(float *)(param_1 + 0x15c)) * 0.5;
    if ((tmp_i4 != 1) &&
       (local_30[1] = (*(float *)(param_1 + 0x154) + *(float *)(param_1 + 0x160)) * 0.5, tmp_i4 == 2)
       ) goto LAB_000a9053;
  }
  local_30[2] = (*(float *)(param_1 + 0x158) + *(float *)(param_1 + 0x164)) * 0.5;
LAB_000a9053:
  vectoangles(local_30 + 3,local_18);
  TeleportPlayer(param_2,local_30,local_18);
  return;
}

void Touch_PlatCenterTrigger(int param_1,int param_2)
{
  int iStack0000000c;
  
  if ((*(int *)(param_2 + 400) != 0) && (*(int *)(*(int *)(param_1 + 0x218) + 0x1e4) == 0)) {
    iStack0000000c = param_2;
    Use_BinaryMover();
    return;
  }
  return;
}

void Touch_Button(int param_1,int param_2)
{
  int iStack0000000c;
  
  if ((*(int *)(param_2 + 400) != 0) && (*(int *)(param_1 + 0x1e4) == 0)) {
    iStack0000000c = param_2;
    Use_BinaryMover();
    return;
  }
  return;
}

void SP_func_door(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  float local_2c;
  int local_28;
  int local_24;
  int local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0xa9de9;
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    G_FreeEntity(param_1);
    return;
  }
  G_SpawnIntExt("type",&g_unk_0024bfa6,&local_24,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x890);
  if (local_24 != 0) {
    DoorSetSounds(param_1,local_24,0);
  }
  *(void **)(param_1 + 0x2ac) = Blocked_Door;
  if (*(float *)(param_1 + 0x268) == 0.0) {
    *(uint32_t *)(param_1 + 0x268) = 0x43c80000;
  }
  if (*(float *)(param_1 + 0x30c) == 0.0) {
    tmp_f1 = 2000.0;
  }
  else {
    tmp_f1 = *(float *)(param_1 + 0x30c) * 1000.0;
  }
  *(float *)(param_1 + 0x30c) = tmp_f1;
  tmp_i5 = G_SpawnIntExt("key",&g_unk_0026ea14,&local_28,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x8a3);
  if (tmp_i5 != 0) {
    *(int *)(param_1 + 0x364) = local_28;
    if (local_28 + 2U < 0x14) goto LAB_000a9ee9;
    G_Error("invalid key number: %d in func_door_rotating\n",local_28);
  }
  *(uint32_t *)(param_1 + 0x364) = 0xfffffffe;
LAB_000a9ee9:
  G_SpawnFloatExt("lip",&g_unk_00261bbb,&local_2c,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x8b1);
  G_SpawnIntExt(&g_unk_0024d95c,"2",param_1 + 0x2d0,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x8b4);
  *(uint32_t *)(param_1 + 0x224) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x228) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x22c) = *(uint32_t *)(param_1 + 100);
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  local_2c = ((*(float *)(param_1 + 0x148) - *(float *)(param_1 + 0x13c)) *
              ABS(*(float *)(param_1 + 0x278)) +
             (*(float *)(param_1 + 0x144) - *(float *)(param_1 + 0x138)) *
             ABS(*(float *)(param_1 + 0x274)) +
             (*(float *)(param_1 + 0x140) - *(float *)(param_1 + 0x134)) *
             ABS(*(float *)(param_1 + 0x270))) - local_2c;
  tmp_f1 = *(float *)(param_1 + 0x270) * local_2c + *(float *)(param_1 + 0x224);
  *(float *)(param_1 + 0x230) = tmp_f1;
  tmp_f4 = *(float *)(param_1 + 0x274) * local_2c + *(float *)(param_1 + 0x228);
  *(float *)(param_1 + 0x234) = tmp_f4;
  tmp_f3 = local_2c * *(float *)(param_1 + 0x278) + *(float *)(param_1 + 0x22c);
  *(float *)(param_1 + 0x238) = tmp_f3;
  if ((*(uint *)(param_1 + 0x1a8) & 1) != 0) {
    *(uint32_t *)(param_1 + 0x230) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x234) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x238) = *(uint32_t *)(param_1 + 100);
    *(float *)(param_1 + 0x224) = tmp_f1;
    *(float *)(param_1 + 0x228) = tmp_f4;
    *(float *)(param_1 + 0x22c) = tmp_f3;
    if (*(float *)(param_1 + 0x26c) != 0.0) {
      tmp_f1 = *(float *)(param_1 + 0x268);
      *(float *)(param_1 + 0x268) = *(float *)(param_1 + 0x26c);
      *(float *)(param_1 + 0x26c) = (float)(int)ROUND(tmp_f1);
    }
    tmp_u2 = *(uint32_t *)(param_1 + 0x1f0);
    *(uint32_t *)(param_1 + 0x1f0) = *(uint32_t *)(param_1 + 0x1ec);
    *(uint32_t *)(param_1 + 0x1ec) = tmp_u2;
    tmp_u2 = *(uint32_t *)(param_1 + 500);
    *(uint32_t *)(param_1 + 500) = *(uint32_t *)(param_1 + 0x1e8);
    *(uint32_t *)(param_1 + 0x1e8) = tmp_u2;
    tmp_u2 = *(uint32_t *)(param_1 + 0x200);
    *(uint32_t *)(param_1 + 0x200) = *(uint32_t *)(param_1 + 0x1fc);
    *(uint32_t *)(param_1 + 0x1fc) = tmp_u2;
    tmp_u2 = *(uint32_t *)(param_1 + 0x210);
    *(uint32_t *)(param_1 + 0x210) = *(uint32_t *)(param_1 + 0x208);
    *(uint32_t *)(param_1 + 0x208) = tmp_u2;
    tmp_u2 = *(uint32_t *)(param_1 + 0x214);
    *(uint32_t *)(param_1 + 0x214) = *(uint32_t *)(param_1 + 0x20c);
    *(uint32_t *)(param_1 + 0x20c) = tmp_u2;
  }
  if ((*(uint *)(param_1 + 0x1a8) & 2) != 0) {
    *(uint *)(param_1 + 0x1b0) = *(uint *)(param_1 + 0x1b0) | 0x20000;
  }
  InitMover(param_1);
  *(uint32_t *)(param_1 + 8) = 4;
  if (*(int *)(param_1 + 0x488) == 0) {
    *(uint32_t *)(param_1 + 0xf8) = 4;
  }
  if (((*(byte *)(param_1 + 0x1b1) & 4) == 0) &&
     (G_SpawnIntExt("health",&g_unk_0024bfa6,local_20,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x8e5),
     local_20[0] != 0)) {
    *(uint32_t *)(param_1 + 0x2cc) = 1;
  }
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2a4) = finishSpawningKeyedMover;
  return;
}

void SP_func_plat(int param_1)
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
  uint32_t tmp_u11;
  int tmp_i12;
  long double tmp_l13;
  long double tmp_l14;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_10 = 9.77019e-40;
  tmp_u11 = G_SoundIndex("sound/movers/plats/pt1_strt");
  *(uint32_t *)(param_1 + 0x1f0) = tmp_u11;
  *(uint32_t *)(param_1 + 0x1ec) = tmp_u11;
  tmp_u11 = G_SoundIndex("sound/movers/plats/pt1_end");
  *(uint32_t *)(param_1 + 0x7c) = 0;
  *(uint32_t *)(param_1 + 0x78) = 0;
  *(uint32_t *)(param_1 + 0x74) = 0;
  *(uint32_t *)(param_1 + 500) = tmp_u11;
  *(uint32_t *)(param_1 + 0x1e8) = tmp_u11;
  G_SpawnFloatExt("speed",&g_unk_0024a7e3,param_1 + 0x268,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x95b);
  G_SpawnIntExt(&g_unk_0024d95c,"2",param_1 + 0x2d0,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x95c);
  G_SpawnFloatExt(&g_unk_0023f11d,&g_unk_00258b23,param_1 + 0x30c,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x95d);
  G_SpawnFloatExt("lip",&g_unk_00261bbb,&local_20,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x95e);
  *(uint32_t *)(param_1 + 0x30c) = 0x447a0000;
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  tmp_i12 = G_SpawnFloatExt("height",&g_unk_0024bfa6,&local_1c,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x965);
  if (tmp_i12 == 0) {
    local_1c = (*(float *)(param_1 + 0x148) - *(float *)(param_1 + 0x13c)) - local_20;
  }
  *(uint32_t *)(param_1 + 0x230) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x234) = *(uint32_t *)(param_1 + 0x60);
  *(float *)(param_1 + 0x238) = *(float *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x224) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x228) = *(uint32_t *)(param_1 + 0x60);
  *(float *)(param_1 + 0x22c) = *(float *)(param_1 + 100) - local_1c;
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u11 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u11;
  }
  if (*(int *)(param_1 + 0x5c0) == 0x23654) {
    *(void **)(param_1 + 0x2b4) = Use_TrinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_TrinaryMover;
  }
  else if (*(int *)(param_1 + 0x5c0) == 0x2a92f) {
    *(void **)(param_1 + 0x2b4) = Use_Func_Rotate;
    *(uint32_t *)(param_1 + 0x2a8) = 0;
  }
  else {
    *(void **)(param_1 + 0x2b4) = Use_BinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_BinaryMover;
  }
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0x4000;
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x224);
  *(uint32_t *)(param_1 + 0x1e4) = 0;
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x228);
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 0x22c);
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x224);
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x228);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x22c);
  local_18 = *(float *)(param_1 + 0x230) - *(float *)(param_1 + 0x224);
  local_14 = *(float *)(param_1 + 0x234) - *(float *)(param_1 + 0x228);
  local_10 = *(float *)(param_1 + 0x238) - *(float *)(param_1 + 0x22c);
  tmp_l13 = (long double)VectorLength(&local_18);
  tmp_l14 = (long double)*(float *)(param_1 + 0x268);
  if (tmp_l14 == (long double)0) {
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
    tmp_l14 = (long double)100.0;
  }
  *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l14);
  *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l14);
  *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l14);
  tmp_i12 = (int)ROUND((tmp_l13 * (long double)1000.0) / tmp_l14);
  if (tmp_i12 < 1) {
    *(uint32_t *)(param_1 + 0x14) = 1;
    tmp_i12 = 1;
  }
  else {
    *(int *)(param_1 + 0x14) = tmp_i12;
  }
  tmp_l14 = (long double)*(float *)(param_1 + 0x26c);
  *(int *)(param_1 + 0x27c) = tmp_i12;
  *(int *)(param_1 + 0x280) = tmp_i12;
  if (tmp_l14 != (long double)0) {
    *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l14);
    *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l14);
    *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l14);
    tmp_i12 = (int)ROUND((tmp_l13 * (long double)1000.0) / tmp_l14);
    if (tmp_i12 < 1) {
      tmp_i12 = 1;
    }
    *(int *)(param_1 + 0x280) = tmp_i12;
  }
  *(void **)(param_1 + 0x2b0) = Touch_Plat;
  *(void **)(param_1 + 0x2ac) = Blocked_Door;
  *(int *)(param_1 + 0x218) = param_1;
  if (*(int *)(param_1 + 600) != 0) {
    return;
  }
  tmp_i12 = G_Spawn();
  *(void **)(tmp_i12 + 0x2b0) = Touch_PlatCenterTrigger;
  *(uint32_t *)(tmp_i12 + 0x14c) = 0x40000000;
  *(int *)(tmp_i12 + 0x218) = param_1;
  tmp_f1 = *(float *)(param_1 + 0x224);
  tmp_f7 = *(float *)(param_1 + 0x134) + tmp_f1 + 33.0;
  tmp_f2 = *(float *)(param_1 + 0x228);
  tmp_f9 = *(float *)(param_1 + 0x138) + tmp_f2 + 33.0;
  tmp_f3 = *(float *)(param_1 + 0x22c);
  tmp_f4 = *(float *)(param_1 + 0x13c);
  tmp_f8 = (tmp_f1 + *(float *)(param_1 + 0x140)) - 33.0;
  tmp_f10 = (*(float *)(param_1 + 0x144) + tmp_f2) - 33.0;
  tmp_f5 = *(float *)(param_1 + 0x22c);
  tmp_f6 = *(float *)(param_1 + 0x148);
  if (tmp_f8 <= tmp_f7) {
    tmp_f7 = (*(float *)(param_1 + 0x140) + *(float *)(param_1 + 0x134)) * 0.5 + tmp_f1;
    tmp_f8 = tmp_f7 + 1.0;
  }
  if (tmp_f10 <= tmp_f9) {
    tmp_f9 = (*(float *)(param_1 + 0x138) + *(float *)(param_1 + 0x144)) * 0.5 + tmp_f2;
    tmp_f10 = tmp_f9 + 1.0;
  }
  *(float *)(tmp_i12 + 0x134) = tmp_f7;
  *(float *)(tmp_i12 + 0x138) = tmp_f9;
  *(float *)(tmp_i12 + 0x13c) = tmp_f3 + tmp_f4;
  *(float *)(tmp_i12 + 0x140) = tmp_f8;
  *(float *)(tmp_i12 + 0x144) = tmp_f10;
  *(float *)(tmp_i12 + 0x148) = tmp_f5 + tmp_f6 + 8.0;
  trap_LinkEntity(tmp_i12);
  return;
}

void SP_func_button(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint32_t tmp_u4;
  int tmp_i5;
  long double tmp_l6;
  long double tmp_l7;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  uint32_t uStack_c;
  
  uStack_c = 0xaa907;
  tmp_u4 = G_SoundIndex("sound/movers/switches/butn2");
  *(uint32_t *)(param_1 + 0x1ec) = tmp_u4;
  if (*(float *)(param_1 + 0x268) == 0.0) {
    *(uint32_t *)(param_1 + 0x268) = 0x42200000;
  }
  if (*(float *)(param_1 + 0x30c) == 0.0) {
    tmp_f1 = 1000.0;
  }
  else {
    tmp_f1 = *(float *)(param_1 + 0x30c) * 1000.0;
  }
  *(float *)(param_1 + 0x30c) = tmp_f1;
  *(uint32_t *)(param_1 + 0x224) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x228) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x22c) = *(uint32_t *)(param_1 + 100);
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  G_SpawnFloatExt("lip","4",&local_1c,"/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",
                  0x9bc);
  G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  local_1c = ((*(float *)(param_1 + 0x148) - *(float *)(param_1 + 0x13c)) *
              ABS(*(float *)(param_1 + 0x278)) +
             (*(float *)(param_1 + 0x144) - *(float *)(param_1 + 0x138)) *
             ABS(*(float *)(param_1 + 0x274)) +
             (*(float *)(param_1 + 0x140) - *(float *)(param_1 + 0x134)) *
             ABS(*(float *)(param_1 + 0x270))) - local_1c;
  tmp_f1 = *(float *)(param_1 + 0x224);
  *(float *)(param_1 + 0x230) = *(float *)(param_1 + 0x270) * local_1c + tmp_f1;
  tmp_f2 = *(float *)(param_1 + 0x228);
  *(float *)(param_1 + 0x234) = *(float *)(param_1 + 0x274) * local_1c + tmp_f2;
  tmp_f3 = *(float *)(param_1 + 0x22c);
  *(float *)(param_1 + 0x238) = local_1c * *(float *)(param_1 + 0x278) + tmp_f3;
  if (*(int *)(param_1 + 0x2c8) == 0) {
    if ((*(byte *)(param_1 + 0x1a8) & 8) != 0) {
      *(void **)(param_1 + 0x2b0) = Touch_Button;
    }
  }
  else {
    *(uint32_t *)(param_1 + 0x2cc) = 1;
  }
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u4 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    tmp_f1 = *(float *)(param_1 + 0x224);
    tmp_f2 = *(float *)(param_1 + 0x228);
    *(uint32_t *)(param_1 + 0xa8) = tmp_u4;
    tmp_f3 = *(float *)(param_1 + 0x22c);
  }
  if (*(int *)(param_1 + 0x5c0) == 0x23654) {
    *(void **)(param_1 + 0x2b4) = Use_TrinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_TrinaryMover;
  }
  else if (*(int *)(param_1 + 0x5c0) == 0x2a92f) {
    *(void **)(param_1 + 0x2b4) = Use_Func_Rotate;
    *(uint32_t *)(param_1 + 0x2a8) = 0;
  }
  else {
    *(void **)(param_1 + 0x2b4) = Use_BinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_BinaryMover;
  }
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0x4000;
  *(float *)(param_1 + 0x168) = tmp_f1;
  *(float *)(param_1 + 0x16c) = tmp_f2;
  *(uint32_t *)(param_1 + 0x1e4) = 0;
  *(float *)(param_1 + 0x170) = tmp_f3;
  *(uint32_t *)(param_1 + 4) = 4;
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x224);
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x228);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x22c);
  local_18 = *(float *)(param_1 + 0x230) - *(float *)(param_1 + 0x224);
  local_14 = *(float *)(param_1 + 0x234) - *(float *)(param_1 + 0x228);
  local_10 = *(float *)(param_1 + 0x238) - *(float *)(param_1 + 0x22c);
  tmp_l6 = (long double)VectorLength(&local_18);
  tmp_l7 = (long double)*(float *)(param_1 + 0x268);
  if (tmp_l7 == (long double)0) {
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
    tmp_l7 = (long double)100.0;
  }
  *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l7);
  *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l7);
  *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l7);
  tmp_i5 = (int)ROUND((tmp_l6 * (long double)1000.0) / tmp_l7);
  if (tmp_i5 < 1) {
    *(uint32_t *)(param_1 + 0x14) = 1;
    tmp_i5 = 1;
  }
  else {
    *(int *)(param_1 + 0x14) = tmp_i5;
  }
  tmp_l7 = (long double)*(float *)(param_1 + 0x26c);
  *(int *)(param_1 + 0x27c) = tmp_i5;
  *(int *)(param_1 + 0x280) = tmp_i5;
  if (tmp_l7 != (long double)0) {
    *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l7);
    *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l7);
    *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l7);
    tmp_i5 = (int)ROUND((tmp_l6 * (long double)1000.0) / tmp_l7);
    if (tmp_i5 < 1) {
      tmp_i5 = 1;
    }
    *(int *)(param_1 + 0x280) = tmp_i5;
  }
  return;
}

void SP_path_corner(int param_1)
{
  uint32_t tmp_u1;
  
  if (*(int *)(param_1 + 600) == 0) {
    tmp_u1 = vtos(param_1 + 0x5c);
    G_Printf("path_corner with no targetname at %s\n",tmp_u1);
    G_FreeEntity(param_1);
  }
  else if (*(float *)(param_1 + 0x30c) == -1.0) {
    *(uint32_t *)(param_1 + 0x2e4) = 1;
  }
  return;
}

void SP_path_corner_2(int param_1)
{
  uint32_t tmp_u1;
  
  if (*(int *)(param_1 + 600) == 0) {
    tmp_u1 = vtos(param_1 + 0x5c);
    G_Printf("path_corner_2 with no targetname at %s\n",tmp_u1);
    G_FreeEntity(param_1);
  }
  else {
    if (0x1ff < numPathCorners) {
      G_Printf("Maximum path_corners hit\n");
      G_FreeEntity(param_1);
      return;
    }
    BG_AddPathCorner(*(int *)(param_1 + 600),param_1 + 0x5c);
    G_FreeEntity(param_1);
  }
  return;
}

void SP_info_train_spline_main(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint8_t local_24 [4];
  uint32_t local_20 [4];
  
  if (*(int *)(param_1 + 600) != 0) {
    tmp_i1 = BG_AddSplinePath(*(int *)(param_1 + 600),*(uint32_t *)(param_1 + 0x254),param_1 + 0x5c
                            );
    tmp_i2 = G_SpawnStringExt("end",&g_unk_0026ea14,local_24,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xaa7);
    if (tmp_i2 == 0) {
      tmp_i2 = G_SpawnStringExt("start",&g_unk_0026ea14,local_24,
                               "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xaa9);
      if (tmp_i2 != 0) {
        *(uint32_t *)(tmp_i1 + 0x38c) = 1;
      }
    }
    else {
      *(uint32_t *)(tmp_i1 + 0x390) = 1;
    }
    tmp_i2 = 1;
    while( true ) {
      if (tmp_i2 == 1) {
        tmp_u3 = va("control");
      }
      else {
        tmp_u3 = va("control%i",tmp_i2);
      }
      tmp_i4 = G_SpawnStringExt(tmp_u3,&g_unk_0026ea14,local_20,
                               "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xab0);
      if (tmp_i4 == 0) break;
      tmp_i2 = tmp_i2 + 1;
      BG_AddSplineControl(tmp_i1,local_20[0]);
    }
    G_FreeEntity(param_1);
    return;
  }
  tmp_u3 = vtos(param_1 + 0x5c);
  G_Printf("info_train_spline_main with no targetname at %s\n",tmp_u3);
  G_FreeEntity(param_1);
  return;
}

void SP_info_limbo_camera(int param_1)
{
  uint tmp_u1;
  
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u1 & 2) == 0) {
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
      if ((tmp_u1 & 1) == 0) goto LAB_000ab065;
    }
    else if ((tmp_u1 & 1) != 0) {
LAB_000ab065:
      G_FreeEntity(param_1);
      return;
    }
  }
  *(void **)(param_1 + 0x2a4) = info_limbo_camera_setup;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  G_SpawnIntExt("objective",&g_unk_0025a5f5,param_1 + 0x2e4,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xb0a);
  return;
}

void SP_func_train(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  long double tmp_l3;
  long double tmp_l4;
  float local_18;
  float local_14;
  float local_10;
  
  *(uint32_t *)(param_1 + 0x7c) = 0;
  *(uint32_t *)(param_1 + 0x78) = 0;
  *(uint32_t *)(param_1 + 0x74) = 0;
  if ((*(byte *)(param_1 + 0x1a8) & 4) == 0) {
    if (*(int *)(param_1 + 0x2d0) == 0) {
      *(uint32_t *)(param_1 + 0x2d0) = 2;
    }
  }
  else {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x10000000;
    *(uint32_t *)(param_1 + 0x2d0) = 0;
  }
  if (*(float *)(param_1 + 0x268) == 0.0) {
    tmp_i2 = *(int *)(param_1 + 0x254);
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
  }
  else {
    tmp_i2 = *(int *)(param_1 + 0x254);
  }
  if (tmp_i2 == 0) {
    tmp_u1 = vtos(param_1 + 0x150);
    G_Printf("func_train without a target at %s\n",tmp_u1);
    G_FreeEntity(param_1);
    return;
  }
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u1 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u1;
  }
  if (*(int *)(param_1 + 0x5c0) == 0x23654) {
    *(void **)(param_1 + 0x2b4) = Use_TrinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_TrinaryMover;
  }
  else if (*(int *)(param_1 + 0x5c0) == 0x2a92f) {
    *(void **)(param_1 + 0x2b4) = Use_Func_Rotate;
    *(uint32_t *)(param_1 + 0x2a8) = 0;
  }
  else {
    *(void **)(param_1 + 0x2b4) = Use_BinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_BinaryMover;
  }
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0x4000;
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x224);
  *(uint32_t *)(param_1 + 0x1e4) = 0;
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x228);
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 0x22c);
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x224);
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x228);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x22c);
  local_18 = *(float *)(param_1 + 0x230) - *(float *)(param_1 + 0x224);
  local_14 = *(float *)(param_1 + 0x234) - *(float *)(param_1 + 0x228);
  local_10 = *(float *)(param_1 + 0x238) - *(float *)(param_1 + 0x22c);
  tmp_l3 = (long double)VectorLength(&local_18);
  tmp_l4 = (long double)*(float *)(param_1 + 0x268);
  if (tmp_l4 == (long double)0) {
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
    tmp_l4 = (long double)100.0;
  }
  *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l4);
  *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l4);
  *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l4);
  tmp_i2 = (int)ROUND((tmp_l3 * (long double)1000.0) / tmp_l4);
  if (tmp_i2 < 1) {
    *(uint32_t *)(param_1 + 0x14) = 1;
    tmp_i2 = 1;
  }
  else {
    *(int *)(param_1 + 0x14) = tmp_i2;
  }
  tmp_l4 = (long double)*(float *)(param_1 + 0x26c);
  *(int *)(param_1 + 0x27c) = tmp_i2;
  *(int *)(param_1 + 0x280) = tmp_i2;
  if (tmp_l4 != (long double)0) {
    *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l4);
    *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l4);
    *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l4);
    tmp_i2 = (int)ROUND((tmp_l3 * (long double)1000.0) / tmp_l4);
    if (tmp_i2 < 1) {
      tmp_i2 = 1;
    }
    *(int *)(param_1 + 0x280) = tmp_i2;
  }
  *(void **)(param_1 + 0x2a8) = Reached_Train;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2a4) = Think_SetupTrainTargets;
  *(void **)(param_1 + 0x2ac) = Blocked_Door;
  return;
}

void SP_func_train_rotating(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  long double tmp_l3;
  long double tmp_l4;
  float local_18;
  float local_14;
  float local_10;
  
  *(uint32_t *)(param_1 + 0x7c) = 0;
  *(uint32_t *)(param_1 + 0x78) = 0;
  *(uint32_t *)(param_1 + 0x74) = 0;
  if ((*(byte *)(param_1 + 0x1a8) & 4) == 0) {
    if (*(int *)(param_1 + 0x2d0) == 0) {
      *(uint32_t *)(param_1 + 0x2d0) = 2;
    }
  }
  else {
    *(uint32_t *)(param_1 + 0x2d0) = 0;
  }
  if (*(float *)(param_1 + 0x268) == 0.0) {
    tmp_i2 = *(int *)(param_1 + 0x254);
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
  }
  else {
    tmp_i2 = *(int *)(param_1 + 0x254);
  }
  if (tmp_i2 == 0) {
    tmp_u1 = vtos(param_1 + 0x150);
    G_Printf("func_train without a target at %s\n",tmp_u1);
    G_FreeEntity(param_1);
    return;
  }
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u1 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u1;
  }
  if (*(int *)(param_1 + 0x5c0) == 0x23654) {
    *(void **)(param_1 + 0x2b4) = Use_TrinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_TrinaryMover;
  }
  else if (*(int *)(param_1 + 0x5c0) == 0x2a92f) {
    *(void **)(param_1 + 0x2b4) = Use_Func_Rotate;
    *(uint32_t *)(param_1 + 0x2a8) = 0;
  }
  else {
    *(void **)(param_1 + 0x2b4) = Use_BinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_BinaryMover;
  }
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0x4000;
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x224);
  *(uint32_t *)(param_1 + 0x1e4) = 0;
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x228);
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 0x22c);
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x224);
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x228);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x22c);
  local_18 = *(float *)(param_1 + 0x230) - *(float *)(param_1 + 0x224);
  local_14 = *(float *)(param_1 + 0x234) - *(float *)(param_1 + 0x228);
  local_10 = *(float *)(param_1 + 0x238) - *(float *)(param_1 + 0x22c);
  tmp_l3 = (long double)VectorLength(&local_18);
  tmp_l4 = (long double)*(float *)(param_1 + 0x268);
  if (tmp_l4 == (long double)0) {
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
    tmp_l4 = (long double)100.0;
  }
  *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l4);
  *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l4);
  *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l4);
  tmp_i2 = (int)ROUND((tmp_l3 * (long double)1000.0) / tmp_l4);
  if (tmp_i2 < 1) {
    *(uint32_t *)(param_1 + 0x14) = 1;
    tmp_i2 = 1;
  }
  else {
    *(int *)(param_1 + 0x14) = tmp_i2;
  }
  tmp_l4 = (long double)*(float *)(param_1 + 0x26c);
  *(int *)(param_1 + 0x27c) = tmp_i2;
  *(int *)(param_1 + 0x280) = tmp_i2;
  if (tmp_l4 != (long double)0) {
    *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l4);
    *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l4);
    *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l4);
    tmp_i2 = (int)ROUND((tmp_l3 * (long double)1000.0) / tmp_l4);
    if (tmp_i2 < 1) {
      tmp_i2 = 1;
    }
    *(int *)(param_1 + 0x280) = tmp_i2;
  }
  *(void **)(param_1 + 0x2a8) = Reached_Train_rotating;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2a4) = Think_SetupTrainTargets_rotating;
  return;
}

void SP_func_leaky(int param_1)
{
  uint32_t tmp_u1;
  
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u1 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u1;
  }
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
  return;
}

void SP_func_static(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  long double tmp_l4;
  long double tmp_l5;
  float local_18;
  float local_14;
  float local_10;
  
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u2 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u2;
  }
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u2 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u2;
  }
  if (*(int *)(param_1 + 0x5c0) == 0x23654) {
    *(void **)(param_1 + 0x2b4) = Use_TrinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_TrinaryMover;
  }
  else if (*(int *)(param_1 + 0x5c0) == 0x2a92f) {
    *(void **)(param_1 + 0x2b4) = Use_Func_Rotate;
    *(uint32_t *)(param_1 + 0x2a8) = 0;
  }
  else {
    *(void **)(param_1 + 0x2b4) = Use_BinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_BinaryMover;
  }
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0x4000;
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x224);
  *(uint32_t *)(param_1 + 0x1e4) = 0;
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x228);
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 0x22c);
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x224);
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x228);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x22c);
  local_18 = *(float *)(param_1 + 0x230) - *(float *)(param_1 + 0x224);
  local_14 = *(float *)(param_1 + 0x234) - *(float *)(param_1 + 0x228);
  local_10 = *(float *)(param_1 + 0x238) - *(float *)(param_1 + 0x22c);
  tmp_l4 = (long double)VectorLength(&local_18);
  tmp_l5 = (long double)*(float *)(param_1 + 0x268);
  if (tmp_l5 == (long double)0) {
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
    tmp_l5 = (long double)100.0;
  }
  *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l5);
  *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l5);
  *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l5);
  tmp_i3 = (int)ROUND((tmp_l4 * (long double)1000.0) / tmp_l5);
  if (tmp_i3 < 1) {
    *(uint32_t *)(param_1 + 0x14) = 1;
    tmp_i3 = 1;
  }
  else {
    *(int *)(param_1 + 0x14) = tmp_i3;
  }
  tmp_l5 = (long double)*(float *)(param_1 + 0x26c);
  *(int *)(param_1 + 0x27c) = tmp_i3;
  *(int *)(param_1 + 0x280) = tmp_i3;
  if (tmp_l5 != (long double)0) {
    *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l5);
    *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l5);
    *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l5);
    tmp_i3 = (int)ROUND((tmp_l4 * (long double)1000.0) / tmp_l5);
    if (tmp_i3 < 1) {
      tmp_i3 = 1;
    }
    *(int *)(param_1 + 0x280) = tmp_i3;
  }
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(void **)(param_1 + 0x2b4) = Use_Static;
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
  if ((*(byte *)(param_1 + 0x1a8) & 1) != 0) {
    trap_UnlinkEntity(param_1);
  }
  if (((*(byte *)(param_1 + 0x1b1) & 4) == 0) &&
     (G_SpawnIntExt("health",&g_unk_0024bfa6,&local_18,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xca6),
     local_18 != 0.0)) {
    *(uint32_t *)(param_1 + 0x2cc) = 1;
  }
  if ((*(byte *)(param_1 + 0x1a8) & 6) != 0) {
    *(void **)(param_1 + 0x2b8) = Static_Pain;
    if (*(float *)(param_1 + 0x318) == 0.0) {
      tmp_f1 = 1000.0;
    }
    else {
      tmp_f1 = *(float *)(param_1 + 0x318) * 1000.0;
    }
    *(float *)(param_1 + 0x318) = tmp_f1;
    *(uint32_t *)(param_1 + 0x2cc) = 1;
    *(uint32_t *)(param_1 + 900) = 1;
    *(uint32_t *)(param_1 + 0x2c8) = 9999;
    if (*(int *)(param_1 + 0x2e4) == 0) {
      *(uint32_t *)(param_1 + 0x2e4) = 4;
    }
  }
  return;
}

void SP_func_rotating(int param_1)
{
  float tmp_f1;
  uint tmp_u2;
  uint32_t tmp_u3;
  int tmp_i4;
  long double tmp_l5;
  long double tmp_l6;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_f1 = *(float *)(param_1 + 0x268);
  if (tmp_f1 == 0.0) {
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
    tmp_f1 = 100.0;
  }
  tmp_u2 = *(uint *)(param_1 + 0x1a8);
  *(uint32_t *)(param_1 + 0x30) = 2;
  if ((tmp_u2 & 1) != 0) {
    if ((tmp_u2 & 4) == 0) {
      if ((tmp_u2 & 8) == 0) {
        *(float *)(param_1 + 0x4c) = tmp_f1;
      }
      else {
        *(float *)(param_1 + 0x48) = tmp_f1;
      }
    }
    else {
      *(float *)(param_1 + 0x50) = tmp_f1;
    }
  }
  if (*(int *)(param_1 + 0x2d0) == 0) {
    *(uint32_t *)(param_1 + 0x2d0) = 2;
  }
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u3 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u3;
  }
  if (*(int *)(param_1 + 0x5c0) == 0x23654) {
    *(void **)(param_1 + 0x2b4) = Use_TrinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_TrinaryMover;
  }
  else if (*(int *)(param_1 + 0x5c0) == 0x2a92f) {
    *(void **)(param_1 + 0x2b4) = Use_Func_Rotate;
    *(uint32_t *)(param_1 + 0x2a8) = 0;
  }
  else {
    *(void **)(param_1 + 0x2b4) = Use_BinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_BinaryMover;
  }
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0x4000;
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x224);
  *(uint32_t *)(param_1 + 0x1e4) = 0;
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x228);
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 0x22c);
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x224);
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x228);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x22c);
  local_18 = *(float *)(param_1 + 0x230) - *(float *)(param_1 + 0x224);
  local_14 = *(float *)(param_1 + 0x234) - *(float *)(param_1 + 0x228);
  local_10 = *(float *)(param_1 + 0x238) - *(float *)(param_1 + 0x22c);
  tmp_l5 = (long double)VectorLength(&local_18);
  tmp_l6 = (long double)*(float *)(param_1 + 0x268);
  if (tmp_l6 == (long double)0) {
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
    tmp_l6 = (long double)100.0;
  }
  *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l6);
  *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l6);
  *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l6);
  tmp_i4 = (int)ROUND((tmp_l5 * (long double)1000.0) / tmp_l6);
  if (tmp_i4 < 1) {
    *(uint32_t *)(param_1 + 0x14) = 1;
    tmp_i4 = 1;
  }
  else {
    *(int *)(param_1 + 0x14) = tmp_i4;
  }
  tmp_l6 = (long double)*(float *)(param_1 + 0x26c);
  *(int *)(param_1 + 0x27c) = tmp_i4;
  *(int *)(param_1 + 0x280) = tmp_i4;
  if (tmp_l6 != (long double)0) {
    *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l6);
    *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l6);
    *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l6);
    tmp_i4 = (int)ROUND((tmp_l5 * (long double)1000.0) / tmp_l6);
    if (tmp_i4 < 1) {
      tmp_i4 = 1;
    }
    *(int *)(param_1 + 0x280) = tmp_i4;
  }
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x174) = *(uint32_t *)(param_1 + 0x3c);
  *(uint32_t *)(param_1 + 0x178) = *(uint32_t *)(param_1 + 0x40);
  *(uint32_t *)(param_1 + 0x17c) = *(uint32_t *)(param_1 + 0x44);
  if ((*(byte *)(param_1 + 0x1a8) & 2) == 0) {
    trap_LinkEntity(param_1);
    return;
  }
  *(uint *)(param_1 + 0x1b0) = *(uint *)(param_1 + 0x1b0) | 0x400;
  trap_UnlinkEntity(param_1);
  return;
}

void SP_func_bobbing(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  long double tmp_l5;
  long double tmp_l6;
  uint32_t local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  G_SpawnFloatExt("speed","4",param_1 + 0x268,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xd28);
  G_SpawnFloatExt("height","32",&local_20,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xd29);
  G_SpawnIntExt(&g_unk_0024d95c,"2",param_1 + 0x2d0,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xd2a);
  G_SpawnFloatExt("phase",&g_unk_0024bfa6,&local_1c,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xd2b);
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u2 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u2;
  }
  if (*(int *)(param_1 + 0x5c0) == 0x23654) {
    *(void **)(param_1 + 0x2b4) = Use_TrinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_TrinaryMover;
  }
  else if (*(int *)(param_1 + 0x5c0) == 0x2a92f) {
    *(void **)(param_1 + 0x2b4) = Use_Func_Rotate;
    *(uint32_t *)(param_1 + 0x2a8) = 0;
  }
  else {
    *(void **)(param_1 + 0x2b4) = Use_BinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_BinaryMover;
  }
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0x4000;
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x224);
  *(uint32_t *)(param_1 + 0x1e4) = 0;
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x228);
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 0x22c);
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x224);
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x228);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x22c);
  local_18 = *(float *)(param_1 + 0x230) - *(float *)(param_1 + 0x224);
  local_14 = *(float *)(param_1 + 0x234) - *(float *)(param_1 + 0x228);
  local_10 = *(float *)(param_1 + 0x238) - *(float *)(param_1 + 0x22c);
  tmp_l5 = (long double)VectorLength(&local_18);
  tmp_l6 = (long double)*(float *)(param_1 + 0x268);
  if (tmp_l6 == (long double)0) {
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
    tmp_l6 = (long double)100.0;
    tmp_i4 = 100000;
    tmp_f1 = 100000.0;
  }
  else {
    tmp_i4 = (int)ROUND((long double)1000.0 * tmp_l6);
    tmp_f1 = (float)tmp_i4;
  }
  *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l6);
  *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l6);
  *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l6);
  tmp_i3 = (int)ROUND((tmp_l5 * (long double)1000.0) / tmp_l6);
  if (tmp_i3 < 1) {
    *(uint32_t *)(param_1 + 0x14) = 1;
    tmp_i3 = 1;
  }
  else {
    *(int *)(param_1 + 0x14) = tmp_i3;
  }
  tmp_l6 = (long double)*(float *)(param_1 + 0x26c);
  *(int *)(param_1 + 0x27c) = tmp_i3;
  *(int *)(param_1 + 0x280) = tmp_i3;
  if (tmp_l6 != (long double)0) {
    *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l6);
    *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l6);
    *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l6);
    tmp_i3 = (int)ROUND((tmp_l5 * (long double)1000.0) / tmp_l6);
    if (tmp_i3 < 1) {
      tmp_i3 = 1;
    }
    *(int *)(param_1 + 0x280) = tmp_i3;
  }
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(int *)(param_1 + 0x14) = tmp_i4;
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
  *(int *)(param_1 + 0x10) = (int)ROUND(tmp_f1 * local_1c);
  *(uint32_t *)(param_1 + 0xc) = 5;
  if ((*(uint *)(param_1 + 0x1a8) & 1) == 0) {
    if ((*(uint *)(param_1 + 0x1a8) & 2) == 0) {
      *(uint32_t *)(param_1 + 0x2c) = local_20;
      return;
    }
    *(uint32_t *)(param_1 + 0x28) = local_20;
    return;
  }
  *(uint32_t *)(param_1 + 0x24) = local_20;
  return;
}

void SP_func_pendulum(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  long double tmp_l4;
  long double tmp_l5;
  double tmp_d6;
  float local_20;
  uint32_t local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_10 = 9.88191e-40;
  G_SpawnFloatExt("speed",&g_unk_0024d9e4,&local_1c,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xd5b);
  G_SpawnIntExt(&g_unk_0024d95c,"2",param_1 + 0x2d0,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xd5c);
  G_SpawnFloatExt("phase",&g_unk_0024bfa6,&local_20,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xd5d);
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  if ((long double)8.0 <= ABS((long double)*(float *)(param_1 + 0x13c))) {
    tmp_l4 = ABS((long double)*(float *)(param_1 + 0x13c)) * (long double)3.0;
  }
  else {
    tmp_l4 = (long double)24.0;
  }
  tmp_l5 = SQRT((long double)(float)GHIDRA_FIELD(g_gravity, 8, 4) / tmp_l4);
  if (NAN(tmp_l5)) {
    tmp_d6 = sqrt((double)((long double)(float)GHIDRA_FIELD(g_gravity, 8, 4) / tmp_l4));
    tmp_l5 = (long double)tmp_d6;
  }
  tmp_i1 = (int)ROUND(1000.0 / (float)(tmp_l5 * (long double)0.15915494309189535));
  *(int *)(param_1 + 0x14) = tmp_i1;
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u2 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u2;
  }
  if (*(int *)(param_1 + 0x5c0) == 0x23654) {
    *(void **)(param_1 + 0x2b4) = Use_TrinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_TrinaryMover;
  }
  else if (*(int *)(param_1 + 0x5c0) == 0x2a92f) {
    *(void **)(param_1 + 0x2b4) = Use_Func_Rotate;
    *(uint32_t *)(param_1 + 0x2a8) = 0;
  }
  else {
    *(void **)(param_1 + 0x2b4) = Use_BinaryMover;
    *(void **)(param_1 + 0x2a8) = Reached_BinaryMover;
  }
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0x4000;
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x224);
  *(uint32_t *)(param_1 + 0x1e4) = 0;
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x228);
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 0x22c);
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x224);
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x228);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x22c);
  local_18 = *(float *)(param_1 + 0x230) - *(float *)(param_1 + 0x224);
  local_14 = *(float *)(param_1 + 0x234) - *(float *)(param_1 + 0x228);
  local_10 = *(float *)(param_1 + 0x238) - *(float *)(param_1 + 0x22c);
  tmp_l4 = (long double)VectorLength(&local_18);
  tmp_l5 = (long double)*(float *)(param_1 + 0x268);
  if (tmp_l5 == (long double)0) {
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
    tmp_l5 = (long double)100.0;
  }
  *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l5);
  *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l5);
  *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l5);
  tmp_i3 = (int)ROUND((tmp_l4 * (long double)1000.0) / tmp_l5);
  if (tmp_i3 < 1) {
    *(uint32_t *)(param_1 + 0x14) = 1;
    tmp_i3 = 1;
  }
  else {
    *(int *)(param_1 + 0x14) = tmp_i3;
  }
  tmp_l5 = (long double)*(float *)(param_1 + 0x26c);
  *(int *)(param_1 + 0x27c) = tmp_i3;
  *(int *)(param_1 + 0x280) = tmp_i3;
  if (tmp_l5 != (long double)0) {
    *(float *)(param_1 + 0x284) = (float)((long double)local_18 * tmp_l5);
    *(float *)(param_1 + 0x288) = (float)((long double)local_14 * tmp_l5);
    *(float *)(param_1 + 0x28c) = (float)((long double)local_10 * tmp_l5);
    tmp_i3 = (int)ROUND((tmp_l4 * (long double)1000.0) / tmp_l5);
    if (tmp_i3 < 1) {
      tmp_i3 = 1;
    }
    *(int *)(param_1 + 0x280) = tmp_i3;
  }
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(int *)(param_1 + 0x38) = tmp_i1;
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
  *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
  *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
  *(int *)(param_1 + 0x34) = (int)ROUND((float)tmp_i1 * local_20);
  *(uint32_t *)(param_1 + 0x30) = 5;
  *(uint32_t *)(param_1 + 0x50) = local_1c;
  return;
}

void SP_func_door_rotating(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint32_t tmp_u6;
  int tmp_i7;
  uint tmp_u8;
  int tmp_i9;
  long double tmp_l10;
  int local_34;
  int local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0xac689;
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    G_FreeEntity(param_1);
    return;
  }
  G_SpawnIntExt("type",&g_unk_0024bfa6,&local_30,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xda6);
  if (local_30 != 0) {
    DoorSetSounds(param_1,local_30,1);
  }
  if (*(float *)(param_1 + 0x268) == 0.0) {
    *(uint32_t *)(param_1 + 0x268) = 0x447a0000;
  }
  tmp_f1 = *(float *)(param_1 + 0x250);
  if (tmp_f1 == 0.0) {
    *(uint32_t *)(param_1 + 0x250) = 0x42b40000;
    tmp_f1 = 90.0;
  }
  if ((*(uint *)(param_1 + 0x1a8) & 0x10) != 0) {
    *(float *)(param_1 + 0x250) = -tmp_f1;
  }
  if ((*(uint *)(param_1 + 0x1a8) & 2) != 0) {
    *(uint *)(param_1 + 0x1b0) = *(uint *)(param_1 + 0x1b0) | 0x20000;
  }
  tmp_i5 = G_SpawnIntExt("key",&g_unk_0026ea14,&local_34,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xdbf);
  if (tmp_i5 != 0) {
    *(int *)(param_1 + 0x364) = local_34;
    if (local_34 + 2U < 0x14) goto LAB_000ac7b0;
    G_Error("invalid key number: %d in func_door_rotating\n",local_34);
  }
  *(uint32_t *)(param_1 + 0x364) = 0xfffffffe;
LAB_000ac7b0:
  *(uint32_t *)(param_1 + 0x32c) = 0;
  *(uint32_t *)(param_1 + 0x328) = 0;
  *(uint32_t *)(param_1 + 0x324) = 0;
  if ((*(uint *)(param_1 + 0x1a8) & 4) == 0) {
    if ((*(uint *)(param_1 + 0x1a8) & 8) == 0) {
      *(uint32_t *)(param_1 + 0x328) = 0x3f800000;
    }
    else {
      *(uint32_t *)(param_1 + 0x324) = 0x3f800000;
    }
  }
  else {
    *(uint32_t *)(param_1 + 0x32c) = 0x3f800000;
  }
  tmp_l10 = (long double)VectorLengthSquared(param_1 + 0x324);
  if ((long double)1 < tmp_l10) {
    G_Error(
           "Too many axis marked in func_door_rotating entity.  Only choose one axis of rotation. (defaulting to standard door rotation)"
           );
    *(uint32_t *)(param_1 + 0x32c) = 0;
    *(uint32_t *)(param_1 + 0x324) = 0;
    *(uint32_t *)(param_1 + 0x328) = 0x3f800000;
  }
  if (*(float *)(param_1 + 0x30c) == 0.0) {
    tmp_f1 = 2000.0;
  }
  else {
    tmp_f1 = *(float *)(param_1 + 0x30c) * 1000.0;
  }
  *(float *)(param_1 + 0x30c) = tmp_f1;
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u6 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u6;
  }
  tmp_i5 = G_SpawnFloatExt("light",&g_unk_002496df,&local_2c,
                          "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x631);
  tmp_i7 = G_SpawnVectorExt("color","1 1 1",&local_28,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x632);
  if (tmp_i7 != 0 || tmp_i5 != 0) {
    tmp_u8 = (uint)ROUND(local_28 * 255.0);
    tmp_i5 = (int)ROUND(local_24 * 255.0);
    tmp_i7 = (int)ROUND(local_20 * 255.0);
    if (0xff < tmp_i5) {
      tmp_i5 = 0xff;
    }
    tmp_i9 = (int)ROUND(local_2c * 0.25);
    if (0xff < tmp_i7) {
      tmp_i7 = 0xff;
    }
    if (0xff < (int)tmp_u8) {
      tmp_u8 = 0xff;
    }
    if (0xff < tmp_i9) {
      tmp_i9 = 0xff;
    }
    *(uint *)(param_1 + 0x98) = tmp_i7 << 0x10 | tmp_i5 << 8 | tmp_u8 | tmp_i9 << 0x18;
  }
  *(void **)(param_1 + 0x2b4) = Use_BinaryMover;
  if ((*(byte *)(param_1 + 0x1a8) & 0x40) == 0) {
    *(void **)(param_1 + 0x2a8) = Reached_BinaryMover;
  }
  *(uint32_t *)(param_1 + 0x1e4) = 7;
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x224);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x228);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 0x22c);
  trap_LinkEntity(param_1);
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x224);
  *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x228);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x22c);
  tmp_f2 = *(float *)(param_1 + 0x230) - *(float *)(param_1 + 0x224);
  tmp_f3 = *(float *)(param_1 + 0x234) - *(float *)(param_1 + 0x228);
  tmp_f4 = *(float *)(param_1 + 0x238) - *(float *)(param_1 + 0x22c);
  tmp_f1 = *(float *)(param_1 + 0x268);
  if (tmp_f1 == 0.0) {
    tmp_i5 = 100;
    *(uint32_t *)(param_1 + 0x38) = 100;
    *(uint32_t *)(param_1 + 0x268) = 0x42c80000;
    *(float *)(param_1 + 0x24) = tmp_f2 * 100.0;
    *(float *)(param_1 + 0x28) = tmp_f3 * 100.0;
    *(float *)(param_1 + 0x2c) = tmp_f4 * 100.0;
  }
  else {
    *(float *)(param_1 + 0x24) = tmp_f2 * tmp_f1;
    *(float *)(param_1 + 0x28) = tmp_f3 * tmp_f1;
    *(float *)(param_1 + 0x2c) = tmp_f4 * tmp_f1;
    tmp_i5 = (int)ROUND(tmp_f1);
    if (tmp_i5 < 1) {
      *(uint32_t *)(param_1 + 0x38) = 1;
      tmp_i5 = 1;
    }
    else {
      *(int *)(param_1 + 0x38) = tmp_i5;
    }
  }
  *(int *)(param_1 + 0x280) = tmp_i5;
  *(int *)(param_1 + 0x27c) = tmp_i5;
  if (*(int *)(param_1 + 0x488) == 0) {
    *(uint32_t *)(param_1 + 0xf8) = 5;
  }
  if (((*(byte *)(param_1 + 0x1b1) & 4) == 0) &&
     (G_SpawnIntExt("health",&g_unk_0024bfa6,&local_28,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xdec),
     local_28 != 0.0)) {
    *(uint32_t *)(param_1 + 0x2cc) = 1;
  }
  tmp_i5 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(int *)(param_1 + 0x29c) = tmp_i5 + 100;
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
  *(void **)(param_1 + 0x2a4) = finishSpawningKeyedMover;
  *(uint32_t *)(param_1 + 0x174) = *(uint32_t *)(param_1 + 0x3c);
  *(void **)(param_1 + 0x2ac) = Blocked_DoorRotate;
  *(uint32_t *)(param_1 + 0x178) = *(uint32_t *)(param_1 + 0x40);
  *(uint32_t *)(param_1 + 0x17c) = *(uint32_t *)(param_1 + 0x44);
  trap_LinkEntity(param_1);
  return;
}

void SP_target_effect(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t local_14;
  uint32_t local_10;
  
  *(void **)(param_1 + 0x2b4) = target_effect;
  tmp_i1 = G_SpawnIntExt(&g_unk_0024d9e7,&g_unk_0024a598,&local_14,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xe36);
  tmp_u2 = 0xf;
  if (tmp_i1 != 0) {
    tmp_u2 = local_14;
  }
  *(uint32_t *)(param_1 + 0x2c8) = tmp_u2;
  tmp_i1 = G_SpawnStringExt("type",&g_unk_0024d9ec,&local_10,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xe3c);
  if (tmp_i1 == 0) {
LAB_000acd00:
    *(uint32_t *)(param_1 + 0x364) = 5;
  }
  else {
    tmp_i1 = Q_stricmp(local_10,&g_unk_0024d9ec);
    if (tmp_i1 != 0) {
      tmp_i1 = Q_stricmp(local_10,"glass");
      if (tmp_i1 == 0) {
        *(uint32_t *)(param_1 + 0x364) = 1;
        goto LAB_000acd0b;
      }
      tmp_i1 = Q_stricmp(local_10,"metal");
      if (tmp_i1 == 0) {
        *(uint32_t *)(param_1 + 0x364) = 2;
        goto LAB_000acd0b;
      }
      tmp_i1 = Q_stricmp(local_10,&g_unk_0024d9fd);
      if (tmp_i1 == 0) {
        *(uint32_t *)(param_1 + 0x364) = 3;
        goto LAB_000acd0b;
      }
      tmp_i1 = Q_stricmp(local_10,"brick");
      if (tmp_i1 == 0) {
        *(uint32_t *)(param_1 + 0x364) = 4;
        goto LAB_000acd0b;
      }
      tmp_i1 = Q_stricmp(local_10,&g_unk_0024da08);
      if (tmp_i1 == 0) goto LAB_000acd00;
      tmp_i1 = Q_stricmp(local_10,"fabric");
      if (tmp_i1 != 0) goto LAB_000acd0b;
    }
    *(uint32_t *)(param_1 + 0x364) = 0;
  }
LAB_000acd0b:
  if (*(int *)(param_1 + 0x35c) != 0) {
    G_Printf(
            "^1Warning: This feature needs to be cleaned up from original wolf since you are using it, go poke Gordon about it\n"
            );
  }
  return;
}

void SP_target_explosion(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t local_64;
  uint32_t local_60;
  uint8_t local_5c [76];
  
  if ((*(byte *)(param_1 + 0x1a8) & 1) == 0) {
    tmp_u2 = 0;
  }
  else {
    tmp_u2 = 0x3f800000;
  }
  *(uint32_t *)(param_1 + 800) = tmp_u2;
  G_SpawnIntExt(&g_unk_0024d95c,&g_unk_0024bfa6,param_1 + 0x2d0,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xf40);
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  tmp_i1 = G_SpawnIntExt(&g_unk_0024d9e7,&g_unk_0024a57a,param_1 + 0x2e4,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xf44);
  if (tmp_i1 == 0) {
    *(uint32_t *)(param_1 + 0x2e4) = 0x4b;
  }
  G_SpawnFloatExt("speed",&g_unk_00258b23,param_1 + 0x80,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xf48);
  G_SpawnFloatExt("size",&g_unk_00258b23,param_1 + 0x84,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xf49);
  tmp_i1 = G_SpawnStringExt("type",&g_unk_0024d9ec,&local_64,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xf4b);
  if ((tmp_i1 != 0) && (tmp_i1 = Q_stricmp(local_64,&g_unk_0024d9ec), tmp_i1 != 0)) {
    tmp_i1 = Q_stricmp(local_64,"glass");
    if (tmp_i1 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 1;
      goto LAB_000ad05e;
    }
    tmp_i1 = Q_stricmp(local_64,"metal");
    if (tmp_i1 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 2;
      goto LAB_000ad05e;
    }
    tmp_i1 = Q_stricmp(local_64,&g_unk_0024d9fd);
    if (tmp_i1 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 3;
      goto LAB_000ad05e;
    }
    tmp_i1 = Q_stricmp(local_64,"brick");
    if (tmp_i1 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 4;
      goto LAB_000ad05e;
    }
    tmp_i1 = Q_stricmp(local_64,&g_unk_0024da08);
    if (tmp_i1 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 5;
      goto LAB_000ad05e;
    }
    tmp_i1 = Q_stricmp(local_64,"fabric");
    if (tmp_i1 != 0) goto LAB_000ad05e;
  }
  *(uint32_t *)(param_1 + 0x364) = 0;
LAB_000ad05e:
  *(uint32_t *)(param_1 + 0x9c) = 0;
  tmp_i1 = G_SpawnStringExt("noise","NOSOUND",&local_60,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xf58);
  if (tmp_i1 != 0) {
    tmp_i1 = Q_stricmp(local_60,"nosound");
    if (tmp_i1 == 0) {
      *(uint32_t *)(param_1 + 0x9c) = 0xffffffff;
    }
    else {
      Q_strncpyz(local_5c,local_60,0x40);
      tmp_u2 = G_SoundIndex(local_5c);
      *(uint32_t *)(param_1 + 0x9c) = tmp_u2;
    }
  }
  *(void **)(param_1 + 0x2b4) = target_explosion_use;
  return;
}

void SP_func_explosive(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  long tmp_l3;
  uint16_t *tmp_pu4;
  uint32_t *tmp_pu5;
  uint tmp_u6;
  void *tmp_pc7;
  uint tmp_u8;
  bool tmp_b9;
  uint32_t local_78;
  uint32_t local_74;
  uint32_t local_70;
  int local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  char *local_5c [19];
  
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
  }
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u1 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u1;
  }
  tmp_i2 = G_SpawnStringExt("damage",&g_unk_0024bfa6,local_5c,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xf11);
  if (tmp_i2 != 0) {
    tmp_l3 = strtol(local_5c[0],(char **)0x0,10);
    *(long *)(param_1 + 0x2d0) = tmp_l3;
  }
  *(uint32_t *)(param_1 + 0x218) = 0;
  *(uint32_t *)(param_1 + 4) = 0xe;
  trap_LinkEntity(param_1);
  *(void **)(param_1 + 0x2a4) = G_BlockThink;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  tmp_u6 = *(uint *)(param_1 + 0x1a8);
  if (((tmp_u6 & 1) == 0) || ((*(byte *)(param_1 + 10) & 1) != 0)) {
    if ((*(int *)(param_1 + 600) != 0) && (*(int *)(param_1 + 0x5cc) == 0)) {
      *(void **)(param_1 + 0x2b4) = func_explosive_use;
      *(void **)(param_1 + 0x344) = func_explosive_alert;
    }
  }
  else {
    *(void **)(param_1 + 0x2b4) = func_explosive_spawn;
    trap_UnlinkEntity(param_1);
    tmp_u6 = *(uint *)(param_1 + 0x1a8);
  }
  tmp_pc7 = (void *)0x0;
  if ((tmp_u6 & 2) != 0) {
    tmp_pc7 = func_explosive_touch;
  }
  *(void **)(param_1 + 0x2b0) = tmp_pc7;
  if ((((tmp_u6 & 4) != 0) && (*(char **)(param_1 + 0x1b4) != (char *)0x0)) &&
     (**(char **)(param_1 + 0x1b4) != '\0')) {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x80;
  }
  if ((tmp_u6 & 8) != 0) {
    *(uint32_t *)(param_1 + 800) = 0x3f800000;
  }
  tmp_pu4 = (uint16_t *)(param_1 + 0x4e4);
  tmp_u6 = 0x18;
  tmp_b9 = ((uint)tmp_pu4 & 1) != 0;
  if (tmp_b9) {
    tmp_pu4 = (uint16_t *)(param_1 + 0x4e5);
    tmp_u6 = 0x17;
    *(uint8_t *)(param_1 + 0x4e4) = 0;
  }
  if (((uint)tmp_pu4 & 2) != 0) {
    *tmp_pu4 = 0;
    tmp_u6 = tmp_u6 - 2;
    tmp_pu4 = tmp_pu4 + 1;
  }
  tmp_u8 = 0;
  do {
    *(uint32_t *)((int)tmp_pu4 + tmp_u8) = 0;
    *(uint32_t *)((int)tmp_pu4 + tmp_u8 + 4) = 0;
    tmp_u8 = tmp_u8 + 8;
  } while (tmp_u8 < (tmp_u6 & 0xfffffff8));
  tmp_pu5 = (uint32_t *)((int)tmp_pu4 + tmp_u8);
  if ((tmp_u6 & 4) != 0) {
    *tmp_pu5 = 0;
    tmp_pu5 = tmp_pu5 + 1;
  }
  if ((tmp_u6 & 2) != 0) {
    *(uint16_t *)tmp_pu5 = 0;
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
  }
  if (tmp_b9) {
    *(uint8_t *)tmp_pu5 = 0;
  }
  G_SpawnIntExt("constructible_class",&g_unk_0024bfa6,&local_6c,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfa1);
  tmp_i2 = local_6c + -1;
  if (local_6c - 2U < 3) {
    tmp_u6 = 0;
    do {
      *(uint32_t *)(param_1 + 0x4e4 + tmp_u6) =
           *(uint32_t *)(g_constructible_classes + tmp_u6 + tmp_i2 * 0x18);
      tmp_u6 = tmp_u6 + 4;
    } while (tmp_u6 < 0x18);
    local_6c = tmp_i2;
    tmp_u1 = va("%f",(double)*(float *)(param_1 + 0x4ec));
    G_SpawnFloatExt("constructible_destructxpbonus",tmp_u1,param_1 + 0x4ec,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfa6);
    tmp_u1 = va("%i",*(uint32_t *)(param_1 + 0x4f0));
    G_SpawnIntExt("constructible_health",tmp_u1,param_1 + 0x4f0,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfa7);
    tmp_u1 = va("%i",*(uint32_t *)(param_1 + 0x4f4));
    G_SpawnIntExt("constructible_weaponclass",tmp_u1,param_1 + 0x4f4,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfa8);
  }
  else {
    local_6c = tmp_i2;
    G_SpawnFloatExt("constructible_destructxpbonus",&g_unk_0024bfa6,param_1 + 0x4ec,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfaa);
    G_SpawnIntExt("constructible_health",&g_unk_0025a5f5,param_1 + 0x4f0,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfab);
    G_SpawnIntExt("constructible_weaponclass",&g_unk_0024bfa6,param_1 + 0x4f4,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfac);
  }
  *(int *)(param_1 + 0x4f4) = *(int *)(param_1 + 0x4f4) + -1;
  *(uint32_t *)(param_1 + 0x2c8) = *(uint32_t *)(param_1 + 0x4f0);
  G_SpawnIntExt("health",&g_unk_002496df,&local_78,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfb1);
  *(uint32_t *)(param_1 + 0x2c8) = local_78;
  G_SpawnIntExt(&g_unk_0024d95c,&g_unk_0024bfa6,&local_70,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfb4);
  *(uint32_t *)(param_1 + 0x2d0) = local_70;
  if (*(int *)(param_1 + 0x2c8) != 0) {
    *(uint32_t *)(param_1 + 0x2cc) = 1;
  }
  tmp_i2 = G_SpawnIntExt(&g_unk_0024d9e7,&g_unk_0024a57a,&local_74,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfba);
  tmp_u1 = 0x4b;
  if (tmp_i2 != 0) {
    tmp_u1 = local_74;
  }
  *(uint32_t *)(param_1 + 0x2e4) = tmp_u1;
  tmp_i2 = G_SpawnStringExt("type",&g_unk_0024d9ec,&local_64,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfbf);
  if ((tmp_i2 != 0) && (tmp_i2 = Q_stricmp(local_64,&g_unk_0024d9ec), tmp_i2 != 0)) {
    tmp_i2 = Q_stricmp(local_64,"glass");
    if (tmp_i2 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 1;
      goto LAB_000ad5af;
    }
    tmp_i2 = Q_stricmp(local_64,"metal");
    if (tmp_i2 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 2;
      goto LAB_000ad5af;
    }
    tmp_i2 = Q_stricmp(local_64,&g_unk_0024d9fd);
    if (tmp_i2 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 3;
      goto LAB_000ad5af;
    }
    tmp_i2 = Q_stricmp(local_64,"brick");
    if (tmp_i2 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 4;
      goto LAB_000ad5af;
    }
    tmp_i2 = Q_stricmp(local_64,&g_unk_0024da08);
    if (tmp_i2 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 5;
      goto LAB_000ad5af;
    }
    tmp_i2 = Q_stricmp(local_64,"fabric");
    if (tmp_i2 != 0) goto LAB_000ad5af;
  }
  *(uint32_t *)(param_1 + 0x364) = 0;
LAB_000ad5af:
  tmp_i2 = G_SpawnStringExt("noise","NOSOUND",&local_68,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfcb);
  if (tmp_i2 != 0) {
    tmp_i2 = Q_stricmp(local_68,"nosound");
    if (tmp_i2 == 0) {
      *(uint32_t *)(param_1 + 0x9c) = 0xffffffff;
    }
    else {
      Q_strncpyz(local_5c,local_68,0x40);
      tmp_u1 = G_SoundIndex(local_5c);
      *(uint32_t *)(param_1 + 0x9c) = tmp_u1;
    }
  }
  *(uint32_t *)(param_1 + 0xf8) = 0;
  tmp_i2 = G_SpawnStringExt("cursorhint",&g_unk_0024bfa6,&local_60,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0xfd9);
  if (tmp_i2 != 0) {
    local_6c = 0;
    do {
      tmp_i2 = Q_stricmp(local_60,(&hintStrings)[local_6c]);
      if (tmp_i2 == 0) {
        *(int *)(param_1 + 0xf8) = local_6c;
      }
      local_6c = local_6c + 1;
    } while (local_6c < 0x28);
  }
  *(void **)(param_1 + 700) = func_explosive_explode;
  return;
}

void SP_func_invisible_user(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t local_24;
  uint32_t local_20 [4];
  
  *(uint32_t *)(param_1 + 0x224) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x228) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x22c) = *(uint32_t *)(param_1 + 100);
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x224);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x228);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 0x22c);
  trap_LinkEntity(param_1);
  *(void **)(param_1 + 0x2b4) = use_invisible_user;
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(uint32_t *)(param_1 + 0x128) = 1;
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x224);
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x228);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 0x22c);
  *(float *)(param_1 + 0x318) = *(float *)(param_1 + 0x318) * 1000.0;
  tmp_i1 = G_SpawnStringExt("cursorhint",&g_unk_0024bfa6,local_20,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x102f);
  if (tmp_i1 != 0) {
    tmp_i1 = 0;
    do {
      tmp_i2 = Q_stricmp(local_20[0],(&hintStrings)[tmp_i1]);
      if (tmp_i2 == 0) {
        *(int *)(param_1 + 0xf8) = tmp_i1;
      }
      tmp_i1 = tmp_i1 + 1;
    } while (tmp_i1 != 0x28);
  }
  if ((*(byte *)(param_1 + 0x1a8) & 4) == 0) {
    tmp_i1 = G_SpawnStringExt("offnoise",&g_unk_0024bfa6,&local_24,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x103b);
    if (tmp_i1 == 0) {
      *(uint32_t *)(param_1 + 0x1e8) = 0x11;
      return;
    }
    tmp_u3 = G_SoundIndex(local_24);
    *(uint32_t *)(param_1 + 0x1e8) = tmp_u3;
  }
  return;
}

void func_constructible_underconstructionthink(int param_1)
{
  byte tmp_b1;
  int tmp_i2;
  char *tmp_pc3;
  
  if (g_unk_00abe908 - *(int *)(param_1 + 0x448) < 30000) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
    return;
  }
  *(uint32_t *)(param_1 + 0x80) = 0;
  if (*(int *)(param_1 + 0x39c) == 0) {
    G_Script_ScriptEvent(param_1,"decayed","final");
    tmp_i2 = *(int *)(param_1 + 0x218);
    tmp_b1 = *(byte *)(tmp_i2 + 0x1a8);
    goto joined_r0x000addb1;
  }
  tmp_i2 = *(int *)(param_1 + 0x3a4);
  if (*(int *)(param_1 + 0x39c) == tmp_i2) {
    tmp_pc3 = "final";
LAB_000addce:
    G_Script_ScriptEvent(param_1,"decayed",tmp_pc3);
    tmp_i2 = *(int *)(param_1 + 0x3a4);
  }
  else {
    if (tmp_i2 == 2) {
      tmp_pc3 = "stage2";
      goto LAB_000addce;
    }
    if (tmp_i2 == 3) {
      tmp_pc3 = "stage3";
      goto LAB_000addce;
    }
    if (tmp_i2 == 1) {
      tmp_pc3 = "stage1";
      goto LAB_000addce;
    }
  }
  *(int *)(param_1 + 0x3a4) = tmp_i2 + -1;
  tmp_i2 = *(int *)(param_1 + 0x218);
  *(uint32_t *)(param_1 + 0xa8) = 0;
  tmp_b1 = *(byte *)(tmp_i2 + 0x1a8);
joined_r0x000addb1:
  if ((tmp_b1 & 8) == 0) {
    *(uint32_t *)(param_1 + 0xa0) = 0;
  }
  else {
    *(uint32_t *)(tmp_i2 + 0xa0) = 0;
  }
  G_Script_ScriptEvent(param_1,"failed",&g_unk_0026ea14);
  G_SetEntState(param_1,0);
  if (*(int *)(param_1 + 0x3a4) == 0) {
    G_UseEntity(param_1,param_1,param_1);
    if ((*(int *)(*(int *)(param_1 + 0x218) + 0x2e8) != 0) &&
       (tmp_i2 = *(int *)(*(int *)(param_1 + 0x218) + 0x39c), tmp_i2 != 0)) {
      *(uint32_t *)(g_entities + tmp_i2 * 0x600 + 0x108) = 3;
    }
  }
  *(uint32_t *)(param_1 + 0x2a4) = 0;
  tmp_i2 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0x29c) = 0;
  *(uint32_t *)(param_1 + 0x80) = 0;
  *(int *)(param_1 + 0x448) = tmp_i2;
  return;
}

void SP_func_constructible(int param_1)
{
  int tmp_i1;
  uint16_t *tmp_pu2;
  uint tmp_u3;
  uint32_t tmp_u4;
  uint16_t *tmp_pu5;
  uint32_t *tmp_pu6;
  uint tmp_u7;
  bool tmp_b8;
  int local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0xade79;
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    G_FreeEntity(param_1);
  }
  else {
    if ((*(uint *)(param_1 + 0x1a8) & 4) == 0) {
      if ((*(uint *)(param_1 + 0x1a8) & 8) == 0) {
        G_Error("\'func_constructible\' does not have a team that can build it\n");
      }
      else {
        *(uint32_t *)(param_1 + 0x108) = 2;
      }
    }
    else {
      *(uint32_t *)(param_1 + 0x108) = 1;
    }
    tmp_pu2 = (uint16_t *)(param_1 + 0x4e4);
    tmp_u7 = 0x18;
    tmp_b8 = ((uint)tmp_pu2 & 1) != 0;
    tmp_pu5 = tmp_pu2;
    if (tmp_b8) {
      *(uint8_t *)(param_1 + 0x4e4) = 0;
      tmp_pu5 = (uint16_t *)(param_1 + 0x4e5);
      tmp_u7 = 0x17;
    }
    if (((uint)tmp_pu5 & 2) != 0) {
      *tmp_pu5 = 0;
      tmp_u7 = tmp_u7 - 2;
      tmp_pu5 = tmp_pu5 + 1;
    }
    tmp_u3 = 0;
    do {
      *(uint32_t *)((int)tmp_pu5 + tmp_u3) = 0;
      *(uint32_t *)((int)tmp_pu5 + tmp_u3 + 4) = 0;
      tmp_u3 = tmp_u3 + 8;
    } while (tmp_u3 < (tmp_u7 & 0xfffffff8));
    tmp_pu6 = (uint32_t *)((int)tmp_pu5 + tmp_u3);
    if ((tmp_u7 & 4) != 0) {
      *tmp_pu6 = 0;
      tmp_pu6 = tmp_pu6 + 1;
    }
    if ((tmp_u7 & 2) != 0) {
      *(uint16_t *)tmp_pu6 = 0;
      tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
    }
    if (tmp_b8) {
      *(uint8_t *)tmp_pu6 = 0;
    }
    G_SpawnIntExt("constructible_class",&g_unk_0024bfa6,local_20,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12bd);
    tmp_i1 = local_20[0] + -1;
    if (local_20[0] - 2U < 3) {
      tmp_u7 = 0;
      do {
        *(uint32_t *)(param_1 + 0x4e4 + tmp_u7) =
             *(uint32_t *)(g_constructible_classes + tmp_u7 + tmp_i1 * 0x18);
        tmp_u7 = tmp_u7 + 4;
      } while (tmp_u7 < 0x18);
      local_20[0] = tmp_i1;
      tmp_u4 = va("%f",(double)*(float *)(param_1 + 0x4e4));
      G_SpawnFloatExt("constructible_chargebarreq",tmp_u4,tmp_pu2,
                      "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12c2);
      tmp_u4 = va("%f",(double)*(float *)(param_1 + 0x4e8));
      G_SpawnFloatExt("constructible_constructxpbonus",tmp_u4,param_1 + 0x4e8,
                      "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12c3);
      tmp_u4 = va("%f",(double)*(float *)(param_1 + 0x4ec));
      G_SpawnFloatExt("constructible_destructxpbonus",tmp_u4,param_1 + 0x4ec,
                      "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12c4);
      tmp_u4 = va("%i",*(uint32_t *)(param_1 + 0x4f0));
      G_SpawnIntExt("constructible_health",tmp_u4,param_1 + 0x4f0,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12c5);
      tmp_u4 = va("%i",*(uint32_t *)(param_1 + 0x4f4));
      G_SpawnIntExt("constructible_weaponclass",tmp_u4,param_1 + 0x4f4,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12c6);
      tmp_u4 = va("%i",*(uint32_t *)(param_1 + 0x4f8));
      G_SpawnIntExt("constructible_duration",tmp_u4,param_1 + 0x4f8,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12c7);
    }
    else {
      local_20[0] = tmp_i1;
      G_SpawnFloatExt("constructible_chargebarreq",&g_unk_00258b23,tmp_pu2,
                      "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12c9);
      G_SpawnFloatExt("constructible_constructxpbonus",&g_unk_0024bfa6,param_1 + 0x4e8,
                      "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12ca);
      G_SpawnFloatExt("constructible_destructxpbonus",&g_unk_0024bfa6,param_1 + 0x4ec,
                      "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12cb);
      G_SpawnIntExt("constructible_health",&g_unk_002496df,param_1 + 0x4f0,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12cc);
      G_SpawnIntExt("constructible_weaponclass",&g_unk_0024bfa6,param_1 + 0x4f4,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12cd);
      G_SpawnIntExt("constructible_duration",&g_unk_00270bcc,param_1 + 0x4f8,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x12ce);
    }
    *(int *)(param_1 + 0x4f4) = *(int *)(param_1 + 0x4f4) + -1;
    *(uint32_t *)(param_1 + 0x2c8) = *(uint32_t *)(param_1 + 0x4f0);
    *(uint32_t *)(param_1 + 0xf8) = 0;
    *(void **)(param_1 + 0x2a4) = func_constructiblespawn;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 200;
  }
  return;
}

void SP_func_brushmodel(int param_1)
{
  int tmp_i1;
  long tmp_l2;
  
  if (*(int *)(param_1 + 0x1b4) == 0) {
    G_Error("\'func_brushmodel\' does not have a model\n");
  }
  tmp_i1 = g_unk_02a99698;
  if (((*(int *)(param_1 + 600) != 0) && (*(int *)(param_1 + 0x5cc) == 0)) && (g_unk_02a99698 < 0x80))
  {
    tmp_l2 = strtol((char *)(*(int *)(param_1 + 0x1b4) + 1),(char **)0x0,10);
    (&g_unk_02a984b8)[tmp_i1 * 9] = tmp_l2;
    Q_strncpyz(&g_unk_02a98498 + g_unk_02a99698 * 0x24,*(uint32_t *)(param_1 + 600),0x20);
    g_unk_02a99698 = g_unk_02a99698 + 1;
  }
  *(void **)(param_1 + 0x2a4) = func_brushmodel_delete;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 300;
  return;
}

void SP_func_debris(int param_1)
{
  void *tmp_pc1;
  int tmp_i2;
  long tmp_l3;
  int tmp_i4;
  
  if ((*(char **)(param_1 + 0x1b4) == (char *)0x0) || (**(char **)(param_1 + 0x1b4) == '\0')) {
    G_FreeEntity(param_1);
    G_Printf("^3WARNING: \'func_debris\' without a valid model\n");
  }
  else {
    if ((*(char **)(param_1 + 0x254) == (char *)0x0) || (**(char **)(param_1 + 0x254) == '\0')) {
      G_Error("ERROR: func_debris with no target");
    }
    if ((*(char **)(param_1 + 600) == (char *)0x0) || (**(char **)(param_1 + 600) == '\0')) {
      G_Error("ERROR: func_debris with no targetname");
    }
    tmp_i2 = g_unk_02a9a694;
    if (0xff < g_unk_02a9a694) {
      G_Error("ERROR: MAX_DEBRISCHUNKS(%i) hit.",0x100);
      strtol((char *)(*(int *)(param_1 + 0x1b4) + 1),(char **)0x0,10);
      _DAT_0000000c = 0;
      tmp_pc1 = (void *)invalidInstructionException();
      (*tmp_pc1)();
    }
    tmp_i4 = g_unk_02a9a694 * 0x5c;
    g_unk_02a9a694 = g_unk_02a9a694 + 1;
    tmp_l3 = strtol((char *)(*(int *)(param_1 + 0x1b4) + 1),(char **)0x0,10);
    (&g_unk_02a9a6a4)[tmp_i2 * 0x17] = tmp_l3;
    Q_strncpyz(&g_unk_02a9a6b4 + tmp_i4,*(uint32_t *)(param_1 + 0x254),0x20);
    Q_strncpyz(&g_unk_02a9a6d4 + tmp_i4,*(uint32_t *)(param_1 + 600),0x20);
    (&g_unk_02a9a698)[tmp_i2 * 0x17] = *(uint32_t *)(param_1 + 0x5c);
    (&g_unk_02a9a69c)[tmp_i2 * 0x17] = *(uint32_t *)(param_1 + 0x60);
    (&g_unk_02a9a6a0)[tmp_i2 * 0x17] = *(uint32_t *)(param_1 + 100);
    G_SpawnFloatExt("speed",&g_unk_0024a8b7,&g_unk_02a9a6a8 + tmp_i2 * 0x17,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_mover.c",0x131c);
    G_FreeEntity(param_1);
  }
  return;
}

void props_bench_die(int param_1)
{
  *(void **)(param_1 + 0x2a4) = props_bench_think;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

void Props_Barrel_Touch(void)
{
  return;
}

void props_crate32x64_die(int param_1)
{
  *(void **)(param_1 + 0x2a4) = props_crate32x64_think;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

void props_58x112tablew_die(int param_1)
{
  *(void **)(param_1 + 0x2a4) = props_58x112tablew_think;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  return;
}

void props_snowGenerator_use(int param_1)
{
  uint tmp_u1;
  float tmp_f2;
  uint tmp_u3;
  
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  tmp_u3 = tmp_u1 & 0xfffffffe;
  if ((tmp_u1 & 1) == 0) {
    tmp_u3 = tmp_u1 | 1;
    *(void **)(param_1 + 0x2a4) = props_snowGenerator_think;
    tmp_f2 = (float)g_unk_00abe908;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
    *(float *)(param_1 + 0x30c) = tmp_f2 + *(float *)(param_1 + 800);
  }
  *(uint *)(param_1 + 0x1a8) = tmp_u3;
  return;
}

void props_decoration_animate(int param_1)
{
  int tmp_i1;
  
  *(uint32_t *)(param_1 + 4) = 0;
  tmp_i1 = *(int *)(param_1 + 0xb0) + 1;
  *(int *)(param_1 + 0xb0) = tmp_i1;
  if (*(int *)(param_1 + 0x39c) < tmp_i1) {
    if ((*(uint *)(param_1 + 0x1a8) & 0x60) == 0) {
      *(int *)(param_1 + 0xb0) = *(int *)(param_1 + 0x39c);
      *(uint32_t *)(param_1 + 0x2cc) = 0;
      return;
    }
    *(uint32_t *)(param_1 + 0xb0) = *(uint32_t *)(param_1 + 0x374);
    if ((*(uint *)(param_1 + 0x1a8) & 0x40) == 0) {
      *(uint32_t *)(param_1 + 0x2cc) = 0;
    }
  }
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
  return;
}

void props_locker_endrattle(int param_1)
{
  *(uint32_t *)(param_1 + 0xb0) = 0;
  *(uint32_t *)(param_1 + 0x2a4) = 0;
  *(uint32_t *)(param_1 + 0x29c) = 0;
  *(uint32_t *)(param_1 + 0x318) = 0;
  return;
}

void props_locker_use(int param_1)
{
  if (*(float *)(param_1 + 0x318) == 0.0) {
    *(uint32_t *)(param_1 + 0xb0) = 1;
  }
  *(void **)(param_1 + 0x2a4) = props_locker_endrattle;
  *(uint32_t *)(param_1 + 0x318) = 0x3f800000;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 1000;
  return;
}

void props_locker_pain(int param_1)
{
  if (*(float *)(param_1 + 0x318) == 0.0) {
    *(uint32_t *)(param_1 + 0xb0) = 1;
  }
  *(void **)(param_1 + 0x2a4) = props_locker_endrattle;
  *(uint32_t *)(param_1 + 0x318) = 0x3f800000;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 1000;
  return;
}

void props_locker_tall_die(int param_1)
{
  *(void **)(param_1 + 0x2a4) = locker_tall_think;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  G_UseTargets(param_1,0);
  return;
}

void Use_DamageInflictor(void)
{
  void *tmp_pc1;
  
  tmp_pc1 = (void *)invalidInstructionException();
  (*tmp_pc1)();
}

void props_flippy_blocked(int param_1,int param_2)
{
  float tmp_f1;
  uint32_t tmp_u2;
  uint tmp_u3;
  float local_24;
  float local_20;
  float local_1c;
  uint32_t local_18;
  float local_14;
  uint32_t local_10;
  
  if (*(int *)(param_2 + 400) != 0) {
    local_10 = *(uint32_t *)(param_1 + 0x44);
    local_14 = *(float *)(param_1 + 0x40) + *(float *)(param_1 + 0x178);
    local_18 = 0;
    AngleVectors(&local_18,&local_24,0,0);
    local_24 = local_24 * 24.0;
    local_20 = local_20 * 24.0;
    local_1c = local_1c * 24.0;
    tmp_u3 = rand();
    tmp_f1 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
    *(float *)(*(int *)(param_2 + 400) + 0x20) =
         local_24 * 32.0 + *(float *)(*(int *)(param_2 + 400) + 0x20);
    *(float *)(*(int *)(param_2 + 400) + 0x24) =
         local_20 * 32.0 + *(float *)(*(int *)(param_2 + 400) + 0x24);
    *(float *)(*(int *)(param_2 + 400) + 0x28) =
         ((tmp_f1 + tmp_f1) * 50.0 + 100.0 + local_1c) * 32.0 +
         *(float *)(*(int *)(param_2 + 400) + 0x28);
    return;
  }
  if (*(int *)(param_2 + 4) != 2) {
    G_FreeEntity(param_2);
    return;
  }
  local_10 = *(uint32_t *)(param_1 + 0x44);
  local_14 = *(float *)(param_1 + 0x40) + *(float *)(param_1 + 0x178);
  local_18 = 0;
  AngleVectors(&local_18,&local_24,0,0);
  local_24 = local_24 * 150.0;
  local_20 = local_20 * 150.0;
  local_1c = local_1c * 150.0;
  tmp_u3 = rand();
  tmp_f1 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
  *(uint32_t *)(param_2 + 0xc) = 6;
  tmp_u2 = g_unk_00abe908;
  *(uint *)(param_2 + 8) = *(uint *)(param_2 + 8) | 0x4000000;
  *(float *)(param_2 + 0x24) = local_24 * 8.0;
  *(float *)(param_2 + 0x28) = local_20 * 8.0;
  *(uint32_t *)(param_2 + 0x10) = tmp_u2;
  *(float *)(param_2 + 0x2c) = ((tmp_f1 + tmp_f1) * 50.0 + 300.0 + local_1c) * 8.0;
  return;
}

void props_flamethrower_use(int param_1)
{
  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_u2 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u2 & 2) != 0) {
    *(uint *)(param_1 + 0x1a8) = tmp_u2 & 0xfffffffd;
    *(uint32_t *)(param_1 + 0x2a4) = 0;
    *(uint32_t *)(param_1 + 0x29c) = 0;
    return;
  }
  tmp_f1 = *(float *)(param_1 + 0x310);
  *(uint *)(param_1 + 0x1a8) = tmp_u2 | 2;
  if (tmp_f1 == 0.0) {
    tmp_i4 = 0;
  }
  else {
    tmp_i4 = rand();
    tmp_i4 = tmp_i4 % (int)ROUND(tmp_f1 * 1000.0);
  }
  tmp_i3 = g_unk_00abe908;
  *(void **)(param_1 + 0x2a4) = props_flamethrower_think;
  *(int *)(param_1 + 0x24c) = tmp_i4 + tmp_i3;
  *(int *)(param_1 + 0x29c) = tmp_i3 + 0x32;
  return;
}

void props_flamethrower_init(int param_1)
{
  int tmp_i1;
  float local_24;
  float local_20;
  float local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  if (*(int *)(param_1 + 0x254) != 0) {
    tmp_i1 = G_FindByTargetnameFast(0,*(int *)(param_1 + 0x254),*(uint32_t *)(param_1 + 0x5bc));
    if (tmp_i1 != 0) {
      local_24 = *(float *)(tmp_i1 + 0x5c) - *(float *)(param_1 + 0x5c);
      local_20 = *(float *)(tmp_i1 + 0x60) - *(float *)(param_1 + 0x60);
      local_1c = *(float *)(tmp_i1 + 100) - *(float *)(param_1 + 100);
      VectorNormalize(&local_24);
      vectoangles(&local_24,&local_18);
      *(uint32_t *)(param_1 + 0x3c) = local_18;
      *(uint32_t *)(param_1 + 0x40) = local_14;
      *(uint32_t *)(param_1 + 0x44) = local_10;
      *(uint32_t *)(param_1 + 0x74) = local_18;
      *(uint32_t *)(param_1 + 0x78) = local_14;
      *(uint32_t *)(param_1 + 0x7c) = local_10;
      goto LAB_000af746;
    }
  }
  *(uint32_t *)(param_1 + 0x3c) = 0;
  *(uint32_t *)(param_1 + 0x40) = 0;
  *(uint32_t *)(param_1 + 0x44) = 0x3f800000;
LAB_000af746:
  trap_LinkEntity(param_1);
  return;
}

void props_flamethrower_think(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  float local_40;
  float local_3c;
  float local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i2 = *(int *)(param_1 + 0x254);
  if ((*(byte *)(param_1 + 0x1a8) & 1) == 0) {
    if ((tmp_i2 == 0) ||
       (tmp_i2 = G_FindByTargetnameFast(0,tmp_i2,*(uint32_t *)(param_1 + 0x5bc)), tmp_i2 == 0)) {
      local_28 = 0.0;
      local_24 = 0.0;
      local_20 = 1.0;
    }
    else {
      local_28 = *(float *)(param_1 + 0x5c) - *(float *)(tmp_i2 + 0x5c);
      local_24 = *(float *)(param_1 + 0x60) - *(float *)(tmp_i2 + 0x60);
      local_20 = *(float *)(param_1 + 100) - *(float *)(tmp_i2 + 100);
    }
  }
  else if ((tmp_i2 == 0) ||
          (tmp_i2 = G_FindByTargetnameFast(0,tmp_i2,*(uint32_t *)(param_1 + 0x5bc)), tmp_i2 == 0)) {
    *(uint32_t *)(param_1 + 0x3c) = 0;
    *(uint32_t *)(param_1 + 0x40) = 0;
    *(uint32_t *)(param_1 + 0x44) = 0x3f800000;
    local_28 = 0.0;
    local_24 = 0.0;
    local_20 = 1.0;
  }
  else {
    local_40 = *(float *)(tmp_i2 + 0x5c) - *(float *)(param_1 + 0x5c);
    local_3c = *(float *)(tmp_i2 + 0x60) - *(float *)(param_1 + 0x60);
    local_38 = *(float *)(tmp_i2 + 100) - *(float *)(param_1 + 100);
    VectorNormalize(&local_40);
    vectoangles(&local_40,&local_34);
    *(uint32_t *)(param_1 + 0x3c) = local_34;
    *(uint32_t *)(param_1 + 0x40) = local_30;
    *(uint32_t *)(param_1 + 0x44) = local_2c;
    local_28 = *(float *)(param_1 + 0x5c) - *(float *)(tmp_i2 + 0x5c);
    local_24 = *(float *)(param_1 + 0x60) - *(float *)(tmp_i2 + 0x60);
    local_20 = *(float *)(param_1 + 100) - *(float *)(tmp_i2 + 100);
  }
  if ((float)g_unk_00abe908 < (float)*(int *)(param_1 + 0x24c) + *(float *)(param_1 + 800)) {
    G_AddEvent(param_1,0x53,0);
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
    fire_flamechunk(param_1,param_1 + 0x168,&local_28);
    tmp_f1 = *(float *)(param_1 + 0x310);
    if (tmp_f1 == 0.0) {
      tmp_i2 = 0;
    }
    else {
      tmp_i2 = rand();
      tmp_i2 = tmp_i2 % (int)ROUND(tmp_f1 * 1000.0);
    }
    tmp_i2 = tmp_i2 + g_unk_00abe908;
    *(int *)(param_1 + 0x24c) = tmp_i2;
    *(int *)(param_1 + 0x29c) = tmp_i2 + 0x32;
  }
  return;
}

void props_bench_think(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0xb0) + 1;
  *(int *)(param_1 + 0xb0) = tmp_i1;
  if (tmp_i1 < 0x1c) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
    return;
  }
  *(uint32_t *)(param_1 + 0x1d4) = 0;
  *(uint32_t *)(param_1 + 0x14c) = 0;
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  G_UseTargets(param_1,0);
  return;
}

void props_crate32x64_think(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0xb0) + 1;
  *(int *)(param_1 + 0xb0) = tmp_i1;
  if (tmp_i1 < 0x11) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
    return;
  }
  *(uint32_t *)(param_1 + 0x1d4) = 0;
  *(uint32_t *)(param_1 + 0x14c) = 0;
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  G_UseTargets(param_1,0);
  return;
}

void props_58x112tablew_think(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0xb0) + 1;
  *(int *)(param_1 + 0xb0) = tmp_i1;
  if (tmp_i1 < 0x10) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
    return;
  }
  *(uint32_t *)(param_1 + 0x1d4) = 0;
  *(uint32_t *)(param_1 + 0x14c) = 0;
  G_UseTargets(param_1,0);
  return;
}

void props_castlebed_animate(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0xb0) + 1;
  *(int *)(param_1 + 0xb0) = tmp_i1;
  if (tmp_i1 < 8) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
    return;
  }
  *(uint32_t *)(param_1 + 0x1d4) = 0;
  *(uint32_t *)(param_1 + 0x14c) = 0;
  G_UseTargets(param_1,0);
  return;
}

void props_castlebed_touch(int *param_1,int param_2)
{
  uint *tmp_pu1;
  int tmp_i2;
  
  tmp_i2 = *(int *)(param_2 + 400);
  if ((((tmp_i2 != 0) && ((*(byte *)(tmp_i2 + 0xc) & 2) != 0)) &&
      (*(int *)(param_2 + 0x94) == *param_1)) && (*(int *)(tmp_i2 + 0x10) == 0)) {
    G_Damage(param_1,param_2,param_2,0,0,1,0,0x1d);
    G_Printf("SOUND sqweeky\n");
    *(float *)(*(int *)(param_2 + 400) + 0x28) = *(float *)(*(int *)(param_2 + 400) + 0x28) + 250.0;
    *(uint32_t *)(*(int *)(param_2 + 400) + 0x10) = 0xfa;
    tmp_pu1 = (uint *)(*(int *)(param_2 + 400) + 0xc);
    *tmp_pu1 = *tmp_pu1 | 0x40;
  }
  return;
}

void props_snowGenerator_think(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  uint32_t tmp_u7;
  float tmp_f8;
  uint tmp_u9;
  int tmp_i10;
  int tmp_i11;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_u9 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u9 & 1) != 0) {
    tmp_f1 = *(float *)(param_1 + 0x148);
    tmp_f2 = *(float *)(param_1 + 0x13c);
    tmp_f3 = *(float *)(param_1 + 0x144);
    tmp_f4 = *(float *)(param_1 + 0x138);
    tmp_f5 = *(float *)(param_1 + 0x140);
    tmp_f6 = *(float *)(param_1 + 0x134);
    if (0 < *(int *)(param_1 + 0x2e4)) {
      tmp_i11 = 0;
      do {
        local_28 = *(float *)(param_1 + 0x224);
        tmp_i11 = tmp_i11 + 1;
        local_24 = *(float *)(param_1 + 0x228);
        local_20 = *(float *)(param_1 + 0x22c);
        tmp_u9 = rand();
        tmp_f8 = (float)(tmp_u9 & 0x7fff) / 32767.0 - 0.5;
        local_28 = (tmp_f8 + tmp_f8) * (tmp_f5 - tmp_f6) * 0.5 + local_28;
        tmp_u9 = rand();
        tmp_f8 = (float)(tmp_u9 & 0x7fff) / 32767.0 - 0.5;
        local_24 = (tmp_f8 + tmp_f8) * (tmp_f3 - tmp_f4) * 0.5 + local_24;
        tmp_u9 = rand();
        tmp_f8 = (float)(tmp_u9 & 0x7fff) / 32767.0 - 0.5;
        local_20 = (tmp_f1 - tmp_f2) * 0.5 * (tmp_f8 + tmp_f8) + local_20;
        tmp_i10 = nitrox_TempEventFromQueue(&local_28,0x4f);
        *(float *)(tmp_i10 + 0x5c) = local_28;
        *(float *)(tmp_i10 + 0x60) = local_24;
        *(float *)(tmp_i10 + 100) = local_20;
        *(uint32_t *)(tmp_i10 + 0x74) = *(uint32_t *)(param_1 + 0x270);
        *(uint32_t *)(tmp_i10 + 0x78) = *(uint32_t *)(param_1 + 0x274);
        tmp_u7 = *(uint32_t *)(param_1 + 0x278);
        *(uint32_t *)(tmp_i10 + 0x54) = 2000;
        *(uint32_t *)(tmp_i10 + 0x7c) = tmp_u7;
        *(uint32_t *)(tmp_i10 + 0x58) = 1000;
      } while (tmp_i11 < *(int *)(param_1 + 0x2e4));
      tmp_u9 = *(uint *)(param_1 + 0x1a8);
    }
    if ((tmp_u9 & 2) == 0) {
      if (*(float *)(param_1 + 0x30c) < (float)g_unk_00abe908) {
        *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
      }
    }
    else {
      *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
    }
  }
  return;
}

void Use_props_decoration(int param_1)
{
  if ((*(uint *)(param_1 + 0x1a8) & 1) != 0) {
    trap_LinkEntity(param_1);
    *(uint *)(param_1 + 0x1a8) = *(uint *)(param_1 + 0x1a8) & 0xfffffffe;
    return;
  }
  if ((*(uint *)(param_1 + 0x1a8) & 4) != 0) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
    *(void **)(param_1 + 0x2a4) = props_decoration_animate;
    return;
  }
  trap_UnlinkEntity(param_1);
  *(uint *)(param_1 + 0x1a8) = *(uint *)(param_1 + 0x1a8) | 1;
  return;
}

void Props_Barrel_Pain(uint32_t *param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  if (0 < (int)param_1[0xb2]) {
    if ((*(byte *)(param_1 + 0x6a) & 8) == 0) {
      tmp_i2 = nitrox_TempEventFromQueue(param_1 + 0x5a,0x4d);
      *(uint32_t *)(tmp_i2 + 0x5c) = param_1[0x5a];
      *(uint32_t *)(tmp_i2 + 0x60) = param_1[0x5b];
      tmp_u1 = param_1[0x5c];
      *(uint32_t *)(tmp_i2 + 0x80) = 0x41800000;
      *(uint32_t *)(tmp_i2 + 100) = tmp_u1;
      *(uint32_t *)(tmp_i2 + 0x84) = 0x42400000;
      *(uint32_t *)(tmp_i2 + 0x88) = 0x461c4000;
      *(uint32_t *)(tmp_i2 + 0xf4) = *param_1;
      param_1[0x6a] = param_1[0x6a] | 8;
    }
    param_1[0xe7] = param_1[0xe7] + 1;
  }
  return;
}

void props_locker_death(uint32_t *param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  
  param_1[0xb3] = 0;
  param_1[0x2c] = 2;
  param_1[0xa7] = 0;
  param_1[0xa9] = 0;
  trap_UnlinkEntity(param_1);
  param_1[0x52] = 0x41300000;
  tmp_i1 = BG_FindItem(param_1[0xe3]);
  if (tmp_i1 != 0) {
    tmp_u3 = *param_1;
    tmp_u2 = tv(0,0,0x41a00000);
    tmp_i1 = LaunchItem(tmp_i1,param_1 + 0x5a,tmp_u2,tmp_u3,0x1000);
    if (tmp_i1 == 0) {
      G_Printf("-----> WARNING <-------\n");
      tmp_u3 = vtos(param_1 + 0x5a);
      G_Printf("props_locker_spawn_item at %s failed!\n",tmp_u3);
    }
  }
  trap_LinkEntity(param_1);
  return;
}

void props_castlebed_die(int param_1)
{
  int tmp_i1;
  
  *(void **)(param_1 + 0x2a4) = props_castlebed_animate;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(uint32_t *)(param_1 + 0x2b0) = 0;
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  *(uint32_t *)(param_1 + 0x2e4) = 0;
  G_AddEvent(param_1,0x2d,0);
  tmp_i1 = *(int *)(param_1 + 0x2e4);
  if (tmp_i1 == 1) {
    G_AddEvent(param_1,0x2d,1);
    return;
  }
  if (tmp_i1 != 2) {
    if (tmp_i1 != 0) {
      return;
    }
    G_AddEvent(param_1,0x2d,0);
    return;
  }
  G_AddEvent(param_1,0x2d,2);
  return;
}

void props_radio_die(uint32_t *param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i3 = G_Spawn();
  *(char **)(tmp_i3 + 0x1a4) = "props_explosion";
  *(uint32_t *)(tmp_i3 + 0xe8) = 0;
  *(uint32_t *)(tmp_i3 + 0x3fc) = 0x3f800000;
  tmp_i2 = g_unk_00abe908;
  *(uint32_t *)(tmp_i3 + 4) = 3;
  *(uint32_t *)(tmp_i3 + 8) = 0x8000000;
  *(int *)(tmp_i3 + 0x29c) = tmp_i2 + 100;
  *(void **)(tmp_i3 + 0x2a4) = G_ExplodeMissile;
  *(uint32_t *)(tmp_i3 + 0x128) = 0;
  tmp_u1 = *param_1;
  *(uint32_t **)(tmp_i3 + 0x218) = param_1;
  *(uint32_t *)(tmp_i3 + 0x180) = tmp_u1;
  *(uint32_t *)(tmp_i3 + 0x2d0) = param_1[0xb2];
  *(uint32_t *)(tmp_i3 + 0x2d4) = param_1[0xb2];
  *(int *)(tmp_i3 + 0x2d8) = (int)ROUND((float)(int)param_1[0xb2] * 1.5);
  *(uint32_t *)(tmp_i3 + 0x2dc) = 4;
  *(uint32_t *)(tmp_i3 + 0x1d4) = 0x6000001;
  *(uint32_t *)(tmp_i3 + 0x2e0) = 4;
  *(uint32_t *)(tmp_i3 + 0x18) = param_1[0x5a];
  *(uint32_t *)(tmp_i3 + 0x1c) = param_1[0x5b];
  *(uint32_t *)(tmp_i3 + 0x20) = param_1[0x5c];
  *(uint32_t *)(tmp_i3 + 0x168) = param_1[0x5a];
  *(uint32_t *)(tmp_i3 + 0x16c) = param_1[0x5b];
  *(uint32_t *)(tmp_i3 + 0x170) = param_1[0x5c];
  param_1[0xb3] = 0;
  G_UseTargets(param_1,0);
  G_FreeEntity(param_1);
  return;
}

void Props_Barrel_Think(uint32_t *param_1)
{
  int tmp_i1;
  uint32_t local_bc;
  uint32_t local_b8;
  uint32_t local_b4;
  uint32_t local_b0;
  uint32_t local_ac;
  uint32_t local_a8;
  uint32_t local_a4;
  uint32_t local_a0;
  float local_9c;
  uint32_t local_98;
  uint32_t local_94;
  float local_90;
  uint8_t local_8c [8];
  float local_84;
  uint32_t local_54;
  uint32_t local_50;
  float local_4c;
  
  param_1[0xda] = 0;
  BG_EvaluateTrajectory(param_1 + 3,g_unk_00abe908,param_1 + 6,0,param_1[0x44]);
  if ((int)param_1[5] < g_unk_00abe908) {
    param_1[0xb] = 0;
    param_1[10] = 0;
    param_1[9] = 0;
    param_1[5] = 0;
    param_1[3] = 0;
  }
  else {
    local_98 = param_1[0x4d];
    local_94 = param_1[0x4e];
    local_54 = param_1[0x50];
    local_50 = param_1[0x51];
    local_4c = (float)param_1[0x52];
    local_90 = (float)param_1[0x4f] + 1.0;
    trap_Trace(local_8c,param_1 + 0x5a,&local_98,&local_54,param_1 + 6,*param_1,0x6000001);
    if (local_84 == 1.0) {
      param_1[0x5a] = param_1[6];
      param_1[0x5b] = param_1[7];
      param_1[0x5c] = param_1[8];
    }
    else {
      param_1[0xb] = 0;
      param_1[6] = param_1[0x5a];
      param_1[10] = 0;
      param_1[7] = param_1[0x5b];
      param_1[9] = 0;
      param_1[8] = param_1[0x5c];
      param_1[5] = 0;
      param_1[3] = 0;
    }
  }
  if (param_1[0x25] == -1) {
    param_1[3] = 6;
    param_1[0x172] = 0;
    param_1[0x73] = 1;
    param_1[0x74] = 0x3e4ccccd;
    param_1[0x171] = 0;
    param_1[0xb] = (float)param_1[0xb] - 200.0;
    param_1[4] = g_unk_00abe908;
    param_1[0xda] = 0;
    param_1[0xa9] = Just_Got_Thrown;
  }
  param_1[0xa7] = g_unk_00abe908 + 0x32;
  tmp_i1 = VectorCompare(param_1 + 0x5a,param_1 + 0xa1);
  if (tmp_i1 == 0) {
    local_a4 = param_1[0x5a];
    local_a0 = param_1[0x5b];
    local_9c = (float)param_1[0x5c];
    local_90 = local_9c - 4.0;
    local_bc = param_1[0x4d];
    local_b8 = param_1[0x4e];
    local_b4 = param_1[0x4f];
    local_b0 = param_1[0x50];
    local_ac = param_1[0x51];
    local_a8 = param_1[0x52];
    local_98 = local_a4;
    local_94 = local_a0;
    trap_Trace(&local_54,&local_a4,&local_bc,&local_b0,&local_98,*param_1,0x6000001);
    if (local_4c == 1.0) {
      param_1[0x25] = 0xffffffff;
    }
    trap_LinkEntity(param_1);
    param_1[0xa1] = param_1[0x5a];
    param_1[0xa2] = param_1[0x5b];
    param_1[0xa3] = param_1[0x5c];
  }
  return;
}

void Props_Barrel_Animate(uint32_t *param_1)
{
  int tmp_i1;
  float tmp_f2;
  long double tmp_l3;
  double local_a4;
  double local_9c;
  float local_90;
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
  uint8_t local_54 [12];
  float local_48;
  float local_44;
  uint32_t local_40;
  
  if (param_1[0x2c] == 0xe) {
    param_1[0xa7] = g_unk_00abe908 + 25000;
    param_1[0xa9] = G_FreeEntity;
  }
  else {
    param_1[0x2c] = param_1[0x2c] + 1;
    param_1[0xa7] = g_unk_00abe908 + 0x32;
    if ((*(byte *)(param_1 + 0x6a) & 1) == 0) {
      tmp_i1 = param_1[0xbb];
      local_84 = (float)param_1[0x5a] - *(float *)(tmp_i1 + 0x168);
      local_80 = (float)param_1[0x5b] - *(float *)(tmp_i1 + 0x16c);
      local_7c = (float)param_1[0x5c] - *(float *)(tmp_i1 + 0x170);
      tmp_f2 = (float)param_1[0xc6] * 2.5 * 100.0 * 0.001;
      tmp_l3 = (long double)vectoyaw(&local_84);
      local_90 = (float)(((long double)3.141592653589793 * tmp_l3 +
                         (long double)3.141592653589793 * tmp_l3) / (long double)360.0);
      sincos((double)local_90,&local_9c,&local_a4);
      local_78 = (float)local_a4 * tmp_f2 + (float)param_1[0x5a];
      local_90 = tmp_f2 * (float)local_9c;
      local_74 = local_90 + (float)param_1[0x5b];
      local_70 = (float)param_1[0x5c] + 0.0;
      local_6c = (float)param_1[0x4d];
      local_68 = (float)param_1[0x4e];
      local_64 = (float)param_1[0x4f] + 0.01;
      local_60 = (float)param_1[0x50];
      local_5c = (float)param_1[0x51];
      local_58 = (float)param_1[0x52] - 0.01;
      trap_Trace(local_54,param_1 + 0x5a,&local_6c,&local_60,&local_78,*param_1,0x6000001);
      if ((local_48 != local_78) || (local_44 != local_74)) {
        local_6c = (float)param_1[0x4d] - 2.0;
        local_68 = (float)param_1[0x4e] - 2.0;
        local_60 = (float)param_1[0x50] + 2.0;
        local_5c = (float)param_1[0x51] + 2.0;
        trap_Trace(local_54,param_1 + 0x5a,&local_6c,&local_60,&local_78,*param_1,0x6000001);
      }
      param_1[0x5a] = local_48;
      param_1[0x5b] = local_44;
      param_1[0x5c] = local_40;
      param_1[6] = local_48;
      param_1[7] = local_44;
      param_1[8] = local_40;
      trap_LinkEntity(param_1);
    }
  }
  return;
}

void props_radio_dieSEVEN(uint32_t *param_1,int param_2)
{
  int tmp_i1;
  float tmp_f2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint tmp_u5;
  int local_68;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0xb17eb;
  tmp_i3 = G_Spawn();
  tmp_i1 = g_unk_00abe908;
  *(char **)(tmp_i3 + 0x1a4) = "props_explosion";
  *(uint32_t *)(tmp_i3 + 0x128) = 0;
  *(int *)(tmp_i3 + 0x29c) = tmp_i1 + 100;
  *(uint32_t *)(tmp_i3 + 4) = 3;
  *(uint32_t *)(tmp_i3 + 0x3fc) = 0x3f800000;
  *(uint32_t *)(tmp_i3 + 8) = 0x8000000;
  *(void **)(tmp_i3 + 0x2a4) = G_ExplodeMissile;
  *(uint32_t *)(tmp_i3 + 0xe8) = 0;
  tmp_u4 = *param_1;
  *(uint32_t **)(tmp_i3 + 0x218) = param_1;
  *(uint32_t *)(tmp_i3 + 0x180) = tmp_u4;
  *(uint32_t *)(tmp_i3 + 0x2d0) = param_1[0xb2];
  *(uint32_t *)(tmp_i3 + 0x2d4) = param_1[0xb2];
  *(int *)(tmp_i3 + 0x2d8) = (int)ROUND((float)(int)param_1[0xb2] * 1.5);
  *(uint32_t *)(tmp_i3 + 0x2dc) = 4;
  *(uint32_t *)(tmp_i3 + 0x2e0) = 4;
  *(uint32_t *)(tmp_i3 + 0x1d4) = 0x6000001;
  *(uint32_t *)(tmp_i3 + 0x18) = param_1[0x5a];
  *(uint32_t *)(tmp_i3 + 0x1c) = param_1[0x5b];
  local_68 = 0x14;
  *(uint32_t *)(tmp_i3 + 0x20) = param_1[0x5c];
  *(uint32_t *)(tmp_i3 + 0x168) = param_1[0x5a];
  *(uint32_t *)(tmp_i3 + 0x16c) = param_1[0x5b];
  *(uint32_t *)(tmp_i3 + 0x170) = param_1[0x5c];
  do {
    tmp_i1 = param_1[0xb9];
    local_28 = (float)param_1[0x5a];
    local_24 = (float)param_1[0x5b];
    local_20 = (float)param_1[0x5c];
    tmp_i3 = Q_stricmp(param_1[0x69],"props_radioSEVEN");
    if (tmp_i3 == 0) {
      tmp_u5 = rand();
      tmp_f2 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
      local_28 = (tmp_f2 + tmp_f2) * 32.0 + local_28;
      tmp_u5 = rand();
      tmp_f2 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
      local_24 = (tmp_f2 + tmp_f2) * 32.0 + local_24;
      local_34 = *(float *)(param_2 + 0x168) - (float)param_1[0x5a];
      local_30 = *(float *)(param_2 + 0x16c) - (float)param_1[0x5b];
      local_2c = *(float *)(param_2 + 0x170) - (float)param_1[0x5c];
      VectorNormalize(&local_34);
    }
    else if (param_2 == 0) {
      local_34 = 0.0;
      local_30 = 0.0;
      local_2c = 1.0;
    }
    else {
      local_34 = *(float *)(param_2 + 0x168) - (float)param_1[0x5a];
      local_30 = *(float *)(param_2 + 0x16c) - (float)param_1[0x5b];
      local_2c = *(float *)(param_2 + 0x170) - (float)param_1[0x5c];
      VectorNormalize(&local_34);
      local_34 = -local_34;
      local_30 = -local_30;
      local_2c = -local_2c;
    }
    tmp_i3 = G_Spawn();
    *(int *)(tmp_i3 + 0xf4) = tmp_i1;
    if (tmp_i1 < 4) {
      local_20 = local_20 + 32.0;
    }
    G_SetOrigin(tmp_i3,&local_28);
    G_SetAngle(tmp_i3,param_1 + 0x5d);
    tmp_u4 = DirToByte(&local_34);
    G_AddEvent(tmp_i3,0x4a,tmp_u4);
    *(uint32_t *)(tmp_i3 + 0xb0) = 1;
    *(void **)(tmp_i3 + 0x2a4) = G_FreeEntity;
    *(int *)(tmp_i3 + 0x29c) = g_unk_00abe908 + 1000;
    trap_LinkEntity(tmp_i3);
    local_68 = local_68 + -1;
  } while (local_68 != 0);
  G_AddEvent(param_1,0x2d,0);
  tmp_i1 = param_1[0xb9];
  if (tmp_i1 == 1) {
    G_AddEvent(param_1,0x2d,1);
  }
  else if (tmp_i1 == 2) {
    G_AddEvent(param_1,0x2d,2);
  }
  else if (tmp_i1 == 0) {
    G_AddEvent(param_1,0x2d,0);
  }
  param_1[0xb3] = 0;
  param_1[0xaf] = 0;
  trap_LinkEntity(param_1);
  G_UseTargets(param_1,0);
  G_FreeEntity(param_1);
  return;
}

void Props_Chair_Animate(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  long double tmp_l4;
  float local_18;
  float local_14;
  float local_10;
  uint32_t uStack_c;
  
  uStack_c = 0xb1e79;
  *(uint32_t *)(param_1 + 0x2b0) = 0;
  tmp_i2 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_chair");
  if (tmp_i2 == 0) {
    tmp_i2 = *(int *)(param_1 + 0xb0);
    if (0x1a < tmp_i2) {
      *(uint32_t *)(param_1 + 0xb0) = 0x1b;
LAB_000b1f8e:
      G_UseTargets(param_1,0);
LAB_000b1f9c:
      *(void **)(param_1 + 0x2a4) = G_FreeEntity;
      tmp_i2 = g_unk_00abe908;
      *(int *)(param_1 + 0x54) = g_unk_00abe908;
      tmp_i3 = g_unk_00abe908;
      *(int *)(param_1 + 0x29c) = tmp_i2 + 2000;
      *(int *)(param_1 + 0x58) = tmp_i3 + 2000;
      return;
    }
  }
  else {
    tmp_i2 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_chair_side");
    if ((((tmp_i2 == 0) ||
         (tmp_i2 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_chair_chat"), tmp_i2 == 0)) ||
        (tmp_i2 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_chair_chatarm"), tmp_i2 == 0)) ||
       (tmp_i2 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_chair_hiback"), tmp_i2 == 0)) {
      tmp_i2 = *(int *)(param_1 + 0xb0);
      if (0x13 < tmp_i2) {
        *(uint32_t *)(param_1 + 0xb0) = 0x14;
        goto LAB_000b1f8e;
      }
    }
    else {
      tmp_i3 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_desklamp");
      tmp_i2 = *(int *)(param_1 + 0xb0);
      if (tmp_i3 != 0) goto LAB_000b1ecd;
      if (10 < tmp_i2) {
        if (*(int *)(param_1 + 0x254) == 0) goto LAB_000b1f9c;
        goto LAB_000b1f8e;
      }
    }
  }
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
LAB_000b1ecd:
  *(int *)(param_1 + 0xb0) = tmp_i2 + 1;
  tmp_i2 = *(int *)(param_1 + 0x2ec);
  if (tmp_i2 != 0) {
    local_18 = *(float *)(param_1 + 0x168) - *(float *)(tmp_i2 + 0x168);
    local_14 = *(float *)(param_1 + 0x16c) - *(float *)(tmp_i2 + 0x16c);
    local_10 = *(float *)(param_1 + 0x170) - *(float *)(tmp_i2 + 0x170);
    tmp_f1 = *(float *)(param_1 + 0x318);
    tmp_l4 = (long double)vectoyaw(&local_18);
    moveit(param_1,(float)tmp_l4,tmp_f1 * 2.5 * 100.0 * 0.001);
  }
  return;
}

void SP_props_box_32(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = G_ModelIndex("models/mapobjects/boxes/box32.md3");
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u1;
  *(uint32_t *)(param_1 + 0x134) = 0xc1800000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1800000;
  *(uint32_t *)(param_1 + 0x13c) = 0xc1800000;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x140) = 0x41800000;
  *(uint32_t *)(param_1 + 0x144) = 0x41800000;
  *(void **)(param_1 + 0x2b0) = touch_props_box_32;
  *(uint32_t *)(param_1 + 0x148) = 0x41800000;
  trap_LinkEntity(param_1);
  *(void **)(param_1 + 0x2a4) = DropToFloor;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

void SP_props_box_48(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = G_ModelIndex("models/mapobjects/boxes/box48.md3");
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u1;
  *(uint32_t *)(param_1 + 0x134) = 0xc1c00000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1c00000;
  *(uint32_t *)(param_1 + 0x13c) = 0xc1c00000;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x140) = 0x41c00000;
  *(uint32_t *)(param_1 + 0x144) = 0x41c00000;
  *(void **)(param_1 + 0x2b0) = touch_props_box_48;
  *(uint32_t *)(param_1 + 0x148) = 0x41c00000;
  trap_LinkEntity(param_1);
  *(void **)(param_1 + 0x2a4) = DropToFloor;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

void SP_props_box_64(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = G_ModelIndex("models/mapobjects/boxes/box64.md3");
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u1;
  *(uint32_t *)(param_1 + 0x134) = 0xc2000000;
  *(uint32_t *)(param_1 + 0x138) = 0xc2000000;
  *(uint32_t *)(param_1 + 0x13c) = 0xc2000000;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x140) = 0x42000000;
  *(uint32_t *)(param_1 + 0x144) = 0x42000000;
  *(void **)(param_1 + 0x2b0) = touch_props_box_64;
  *(uint32_t *)(param_1 + 0x148) = 0x42000000;
  trap_LinkEntity(param_1);
  *(void **)(param_1 + 0x2a4) = DropToFloor;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

void SP_props_sparks(int param_1)
{
  *(void **)(param_1 + 0x2a4) = G_FreeEntity;
  return;
}

void SP_props_gunsparks(int param_1)
{
  G_SetOrigin(param_1,param_1 + 0x5c);
  *(void **)(param_1 + 0x2a4) = sparks_angles_think;
  *(uint32_t *)(param_1 + 4) = 0;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  if (*(float *)(param_1 + 0x268) == 0.0) {
    *(uint32_t *)(param_1 + 0x268) = 0x41a00000;
  }
  if (*(int *)(param_1 + 0x2c8) == 0) {
    *(uint32_t *)(param_1 + 0x2c8) = 4;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_SmokeDust(int param_1)
{
  *(void **)(param_1 + 0x2b4) = smokedust_use;
  G_SetOrigin(param_1,param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 4) = 0;
  if (*(int *)(param_1 + 0x2c8) == 0) {
    *(uint32_t *)(param_1 + 0x2c8) = 0x10;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_Dust(int param_1)
{
  *(void **)(param_1 + 0x2b4) = dust_use;
  G_SetOrigin(param_1,param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 4) = 0;
  if (*(int *)(param_1 + 0x254) != 0) {
    *(void **)(param_1 + 0x2a4) = dust_angles_think;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_Props_Bench(int param_1)
{
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  InitProp(param_1);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    *(uint32_t *)(param_1 + 0x2c8) = 10;
  }
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(void **)(param_1 + 700) = props_bench_die;
  trap_LinkEntity(param_1);
  return;
}

void SP_Props_Radio(int param_1)
{
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
    InitProp(param_1);
    if (*(int *)(param_1 + 0x2c8) == 0) {
      *(uint32_t *)(param_1 + 0x2c8) = 100;
    }
    *(uint32_t *)(param_1 + 0x2cc) = 1;
    *(void **)(param_1 + 700) = props_radio_die;
    trap_LinkEntity(param_1);
    return;
  }
  G_Printf("^1props_radio with NULL model\n");
  return;
}

void SP_Props_RadioSEVEN(int param_1)
{
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
    InitProp(param_1);
    if (*(int *)(param_1 + 0x2c8) == 0) {
      *(uint32_t *)(param_1 + 0x2c8) = 100;
    }
    *(uint32_t *)(param_1 + 0x2cc) = 1;
    *(void **)(param_1 + 700) = props_radio_dieSEVEN;
    *(uint32_t *)(param_1 + 0x2e4) = 2;
    trap_LinkEntity(param_1);
    return;
  }
  G_Printf("^1props_radio with NULL model\n");
  return;
}

void SP_Props_Locker_Tall(int param_1)
{
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
    InitProp(param_1);
    if (*(int *)(param_1 + 0x2c8) == 0) {
      *(uint32_t *)(param_1 + 0x2c8) = 100;
    }
    *(uint32_t *)(param_1 + 0x2cc) = 1;
    *(void **)(param_1 + 700) = props_locker_tall_die;
    trap_LinkEntity(param_1);
    return;
  }
  G_Printf("^1props_locker_tall with NULL model\n");
  return;
}

void Props_TurnLightsOff(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_desklamp");
  if ((tmp_i1 == 0) && (*(int *)(param_1 + 0x254) != 0)) {
    G_UseTargets(param_1,0);
    *(uint32_t *)(param_1 + 0x254) = 0;
  }
  return;
}

void Props_Activated(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  float tmp_f4;
  int tmp_i5;
  int tmp_i6;
  uint tmp_u7;
  int tmp_i8;
  int *tmp_pi9;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  float local_34;
  float local_30;
  float local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  tmp_i6 = g_unk_00abe908;
  uStack_14 = 0xb2de9;
  tmp_i8 = *(int *)(param_1 + 0x180);
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
  if (*(int *)(g_entities + tmp_i8 * 0x600 + 400) == 0) {
    return;
  }
  tmp_i5 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_desklamp");
  if ((tmp_i5 == 0) && (*(int *)(param_1 + 0x254) != 0)) {
    G_UseTargets(param_1,0);
    *(uint32_t *)(param_1 + 0x254) = 0;
  }
  tmp_i5 = tmp_i8 * 0x600;
  if (*(int *)(g_entities + tmp_i5 + 0x368) == 0) {
    *(uint32_t *)(g_entities + tmp_i5 + 0x5b4) = 0;
    *(uint32_t *)(param_1 + 0x1cc) = 1;
    *(uint32_t *)(param_1 + 0x5c4) = 0;
    *(uint32_t *)(param_1 + 0x5c8) = 0;
    *(uint32_t *)(param_1 + 0xc) = 6;
    *(uint32_t *)(param_1 + 0x94) = 0xffffffff;
    tmp_pi9 = (int *)(g_entities + tmp_i5 + 400);
    *(uint32_t *)(param_1 + 0x368) = 0;
    tmp_i8 = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x1d0) = 0x3e4ccccd;
    *(int *)(param_1 + 0x10) = tmp_i8;
    AngleVectors(*tmp_pi9 + 0xb0,&local_34,0,0,tmp_i6);
    local_34 = local_34 * 250.0;
    local_30 = local_30 * 250.0;
    local_2c = local_2c * 250.0;
    tmp_u7 = rand();
    tmp_f4 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
    local_2c = (tmp_f4 + tmp_f4) * 25.0 + 100.0 + local_2c;
    *(uint32_t *)(param_1 + 0x2a4) = 0;
    *(uint32_t *)(param_1 + 0x29c) = 0;
    *(float *)(param_1 + 0x24) = local_34;
    *(float *)(param_1 + 0x28) = local_30;
    *(float *)(param_1 + 0x2c) = local_2c;
    tmp_i8 = G_Spawn();
    *(uint32_t *)(tmp_i8 + 0xa4) = *(uint32_t *)(param_1 + 0xa4);
    G_SetOrigin(tmp_i8,param_1 + 0x168);
    local_24 = *(uint32_t *)(*tmp_pi9 + 0xb4);
    local_20 = *(uint32_t *)(*tmp_pi9 + 0xb8);
    local_28 = 0;
    G_SetAngle(tmp_i8,&local_28);
    *(uint32_t *)(tmp_i8 + 0x1d4) = 1;
    *(uint32_t *)(tmp_i8 + 0x14c) = 1;
    *(uint32_t *)(tmp_i8 + 900) = 1;
    *(uint32_t *)(tmp_i8 + 0x1cc) = 1;
    *(uint32_t *)(tmp_i8 + 0x5c8) = 0;
    *(uint32_t *)(tmp_i8 + 0x128) = 0;
    *(uint32_t *)(tmp_i8 + 0x134) = 0xc1400000;
    *(uint32_t *)(tmp_i8 + 0x138) = 0xc1400000;
    *(uint32_t *)(tmp_i8 + 0x13c) = 0;
    *(uint32_t *)(tmp_i8 + 0x140) = 0x41400000;
    *(uint32_t *)(tmp_i8 + 0x144) = 0x41400000;
    *(uint32_t *)(tmp_i8 + 0x148) = 0x42400000;
    *(uint32_t *)(tmp_i8 + 0x1d0) = 0x3e4ccccd;
    *(uint32_t *)(tmp_i8 + 0x5c4) = 0;
    *(uint32_t *)(tmp_i8 + 0x18) = *(uint32_t *)(*tmp_pi9 + 0x14);
    *(uint32_t *)(tmp_i8 + 0x1c) = *(uint32_t *)(*tmp_pi9 + 0x18);
    *(uint32_t *)(tmp_i8 + 0x20) = *(uint32_t *)(*tmp_pi9 + 0x1c);
    *(uint32_t *)(tmp_i8 + 0x24) = *(uint32_t *)(param_1 + 0x24);
    *(uint32_t *)(tmp_i8 + 0x28) = *(uint32_t *)(param_1 + 0x28);
    tmp_u1 = *(uint32_t *)(param_1 + 0x2c);
    *(uint32_t *)(tmp_i8 + 0xc) = 6;
    *(uint32_t *)(tmp_i8 + 0x2c) = tmp_u1;
    *(int *)(tmp_i8 + 0x10) = g_unk_00abe908;
    *(uint32_t *)(tmp_i8 + 0x368) = 0;
    *(uint32_t *)(tmp_i8 + 0x2c8) = *(uint32_t *)(param_1 + 0x2c8);
    *(float *)(tmp_i8 + 800) = (float)*(int *)(param_1 + 0x2c8);
    *(uint32_t *)(tmp_i8 + 0x2e4) = *(uint32_t *)(param_1 + 0x2e4);
    *(void **)(tmp_i8 + 0x2a4) = Just_Got_Thrown;
    *(int *)(tmp_i8 + 0x29c) = g_unk_00abe908 + 100;
    *(uint32_t *)(tmp_i8 + 0x2cc) = 1;
    *(uint32_t *)(tmp_i8 + 0x30c) = *(uint32_t *)(param_1 + 0x30c);
    *(uint32_t *)(tmp_i8 + 0x1a4) = *(uint32_t *)(param_1 + 0x1a4);
    *(uint32_t *)(tmp_i8 + 0x94) = 0xffffffff;
    *(uint32_t *)(tmp_i8 + 0x68) = *(uint32_t *)(param_1 + 0x168);
    *(uint32_t *)(tmp_i8 + 0x6c) = *(uint32_t *)(param_1 + 0x16c);
    tmp_u1 = *(uint32_t *)(param_1 + 0x170);
    *(void **)(tmp_i8 + 700) = Props_Chair_Die;
    *(uint32_t *)(tmp_i8 + 0x70) = tmp_u1;
    *(uint32_t *)(tmp_i8 + 0x180) = *(uint32_t *)(g_entities + tmp_i5);
    trap_LinkEntity(tmp_i8);
    G_FreeEntity(param_1);
    return;
  }
  tmp_i6 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_chair_hiback");
  if (tmp_i6 != 0) {
    tmp_i6 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_chair");
    if (tmp_i6 == 0) {
      *(uint32_t *)(param_1 + 0xb0) = 0x1c;
      *(uint32_t *)(param_1 + 0xf4) = 1;
      goto LAB_000b2eb6;
    }
    tmp_i6 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_chair_side");
    if (tmp_i6 != 0) goto LAB_000b2eb6;
  }
  *(uint32_t *)(param_1 + 0xb0) = 0x17;
  *(uint32_t *)(param_1 + 0xf4) = 1;
LAB_000b2eb6:
  trap_UnlinkEntity(param_1);
  tmp_i8 = tmp_i8 * 0x600;
  local_40 = 0;
  local_3c = *(uint32_t *)(*(int *)(g_entities + tmp_i8 + 400) + 0xb4);
  local_38 = *(uint32_t *)(*(int *)(g_entities + tmp_i8 + 400) + 0xb8);
  *(uint32_t *)(param_1 + 0x40) = local_3c;
  AngleVectors(&local_40,&local_34,&local_28,0);
  tmp_u1 = *(uint32_t *)(g_entities + tmp_i8 + 0x168);
  tmp_u2 = *(uint32_t *)(g_entities + tmp_i8 + 0x16c);
  tmp_u3 = *(uint32_t *)(g_entities + tmp_i8 + 0x170);
  *(uint32_t *)(param_1 + 0x168) = tmp_u1;
  *(uint32_t *)(param_1 + 0x16c) = tmp_u2;
  *(uint32_t *)(param_1 + 0x170) = tmp_u3;
  *(uint32_t *)(param_1 + 0x18) = tmp_u1;
  *(uint32_t *)(param_1 + 0x1c) = tmp_u2;
  *(uint32_t *)(param_1 + 0x20) = tmp_u3;
  *(uint32_t *)(param_1 + 4) = 0x1b;
  trap_LinkEntity(param_1);
  return;
}

void Props_Chair_Think(uint32_t *param_1)
{
  int tmp_i1;
  uint32_t local_bc;
  uint32_t local_b8;
  uint32_t local_b4;
  uint32_t local_b0;
  uint32_t local_ac;
  uint32_t local_a8;
  uint32_t local_a4;
  uint32_t local_a0;
  float local_9c;
  uint32_t local_98;
  uint32_t local_94;
  float local_90;
  uint8_t local_8c [8];
  float local_84;
  uint32_t local_54;
  uint32_t local_50;
  float local_4c;
  
  if (param_1[0xda] == 0) {
    BG_EvaluateTrajectory(param_1 + 3,g_unk_00abe908,param_1 + 6,0,param_1[0x44]);
    if ((int)param_1[5] < g_unk_00abe908) {
      param_1[0xb] = 0;
      param_1[10] = 0;
      param_1[9] = 0;
      param_1[5] = 0;
      param_1[3] = 0;
    }
    else {
      local_98 = param_1[0x4d];
      local_94 = param_1[0x4e];
      local_54 = param_1[0x50];
      local_50 = param_1[0x51];
      local_4c = (float)param_1[0x52];
      local_90 = (float)param_1[0x4f] + 1.0;
      trap_Trace(local_8c,param_1 + 0x5a,&local_98,&local_54,param_1 + 6,*param_1,0x6000001);
      if (local_84 == 1.0) {
        param_1[0x5a] = param_1[6];
        param_1[0x5b] = param_1[7];
        param_1[0x5c] = param_1[8];
      }
      else {
        param_1[0xb] = 0;
        param_1[6] = param_1[0x5a];
        param_1[10] = 0;
        param_1[7] = param_1[0x5b];
        param_1[9] = 0;
        param_1[8] = param_1[0x5c];
        param_1[5] = 0;
        param_1[3] = 0;
      }
    }
    if (param_1[0x25] == -1) {
      param_1[3] = 6;
      param_1[0x172] = 0;
      param_1[0x73] = 1;
      param_1[0x74] = 0x3e4ccccd;
      param_1[0x171] = 0;
      param_1[0xb] = (float)param_1[0xb] - 200.0;
      param_1[4] = g_unk_00abe908;
      param_1[0xda] = 0;
      param_1[0xa9] = Just_Got_Thrown;
    }
    param_1[0xa7] = g_unk_00abe908 + 0x32;
    tmp_i1 = VectorCompare(param_1 + 0x5a,param_1 + 0xa1);
    if (tmp_i1 == 0) {
      local_a4 = param_1[0x5a];
      local_a0 = param_1[0x5b];
      local_9c = (float)param_1[0x5c];
      local_90 = local_9c - 4.0;
      local_bc = param_1[0x4d];
      local_b8 = param_1[0x4e];
      local_b4 = param_1[0x4f];
      local_b0 = param_1[0x50];
      local_ac = param_1[0x51];
      local_a8 = param_1[0x52];
      local_98 = local_a4;
      local_94 = local_a0;
      trap_Trace(&local_54,&local_a4,&local_bc,&local_b0,&local_98,*param_1,0x6000001);
      if (local_4c == 1.0) {
        param_1[0x25] = 0xffffffff;
      }
      trap_LinkEntity(param_1);
      param_1[0xa1] = param_1[0x5a];
      param_1[0xa2] = param_1[0x5b];
      param_1[0xa3] = param_1[0x5c];
    }
  }
  else {
    Props_Activated(param_1);
  }
  return;
}

void Props_Chair_Touch(uint32_t *param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  float local_80;
  float local_7c;
  float local_78;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  float local_54;
  uint32_t local_50;
  uint32_t local_4c;
  float local_48;
  uint8_t local_44 [8];
  float local_3c;
  
  if (*(int *)(param_2 + 400) != 0) {
    if ((*(float *)(param_2 + 0x170) <= (float)param_1[0x5c] + 10.0 + 15.0) && (param_1[0xda] == 0))
    {
      local_80 = (float)param_1[0x5a] - *(float *)(param_2 + 0x168);
      local_7c = (float)param_1[0x5b] - *(float *)(param_2 + 0x16c);
      local_78 = (float)param_1[0x5c] - *(float *)(param_2 + 0x170);
      tmp_i1 = Prop_Touch(param_1,param_2,&local_80);
      local_5c = param_1[0x5a];
      local_58 = param_1[0x5b];
      local_54 = (float)param_1[0x5c];
      local_48 = local_54 - 4.0;
      local_74 = param_1[0x4d];
      local_70 = param_1[0x4e];
      local_6c = param_1[0x4f];
      local_68 = param_1[0x50];
      local_64 = param_1[0x51];
      local_60 = param_1[0x52];
      local_50 = local_5c;
      local_4c = local_58;
      trap_Trace(local_44,&local_5c,&local_74,&local_68,&local_50,*param_1,0x6000001);
      if (local_3c == 1.0) {
        param_1[0x25] = 0xffffffff;
      }
      if ((tmp_i1 != 0) && ((float)param_1[0xc4] < (float)g_unk_00abe908)) {
        nitmod_SoundEvent(param_1,7);
        tmp_i1 = g_unk_00abe908;
        tmp_i2 = rand();
        param_1[0xc4] = (float)(tmp_i1 + 1000 + tmp_i2 % 200);
      }
      tmp_i1 = Q_stricmp(param_1[0x69],"props_desklamp");
      if ((tmp_i1 == 0) && (param_1[0x95] != 0)) {
        G_UseTargets(param_1,0);
        param_1[0x95] = 0;
      }
    }
  }
  return;
}

void Use_Props_Shard_Generator(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  tmp_u2 = *(uint32_t *)(param_1 + 0x2e4);
  tmp_f1 = *(float *)(param_1 + 0x30c);
  tmp_i3 = G_Find(0,600,*(uint32_t *)(param_1 + 0x254));
  if (tmp_i3 != 0) {
    Spawn_Shard(param_1,tmp_i3,(int)ROUND(tmp_f1),tmp_u2);
  }
  G_FreeEntity(param_1);
  return;
}

void props_decoration_death(int param_1,uint32_t param_2)
{
  uint tmp_u1;
  
  if ((*(byte *)(param_1 + 0x1a8) & 8) == 0) {
    *(uint32_t *)(param_1 + 0x1d4) = 0;
    *(uint32_t *)(param_1 + 0x14c) = 0;
    *(uint32_t *)(param_1 + 4) = 0;
    trap_LinkEntity(param_1);
  }
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  G_UseTargets(param_1,0);
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u1 & 2) != 0) {
    Spawn_Shard(param_1,param_2,*(uint32_t *)(param_1 + 0x2e4),*(uint32_t *)(param_1 + 0x364));
    tmp_u1 = *(uint *)(param_1 + 0x1a8);
  }
  if ((tmp_u1 & 4) != 0) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
    *(void **)(param_1 + 0x2a4) = props_decoration_animate;
    return;
  }
  G_FreeEntity(param_1);
  return;
}

void props_statue_death(int param_1,uint32_t param_2)
{
  uint tmp_u1;
  
  *(int *)(param_1 + 0x24c) = g_unk_00abe908;
  G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x308));
  if ((*(byte *)(param_1 + 0x1a8) & 8) == 0) {
    *(uint32_t *)(param_1 + 0x1d4) = 0;
    *(uint32_t *)(param_1 + 0x14c) = 0;
    *(uint32_t *)(param_1 + 4) = 0;
    trap_LinkEntity(param_1);
  }
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  G_UseTargets(param_1,0);
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u1 & 2) != 0) {
    Spawn_Shard(param_1,param_2,*(uint32_t *)(param_1 + 0x2e4),*(uint32_t *)(param_1 + 0x364));
    tmp_u1 = *(uint *)(param_1 + 0x1a8);
  }
  if ((tmp_u1 & 4) != 0) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
    *(void **)(param_1 + 0x2a4) = props_statue_animate;
    return;
  }
  G_FreeEntity(param_1);
  return;
}

void Props_Chair_Die(int param_1,uint32_t param_2,uint32_t param_3,int param_4)
{
  int tmp_i1;
  
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  *(void **)(param_1 + 0x2a4) = Props_Chair_Animate;
  *(float *)(param_1 + 0x318) = (float)param_4;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(uint32_t *)(param_1 + 0x2c8) = 0;
  Spawn_Shard(param_1,param_2,(int)ROUND(*(float *)(param_1 + 0x30c)),
              *(uint32_t *)(param_1 + 0x2e4));
  G_AddEvent(param_1,0x2d,0);
  tmp_i1 = *(int *)(param_1 + 0x2e4);
  if (tmp_i1 == 1) {
    G_AddEvent(param_1,0x2d,1);
  }
  else if (tmp_i1 == 2) {
    G_AddEvent(param_1,0x2d,2);
  }
  else if (tmp_i1 == 0) {
    G_AddEvent(param_1,0x2d,0);
  }
  trap_UnlinkEntity(param_1);
  *(uint32_t *)(param_1 + 0x1d4) = 0;
  *(uint32_t *)(param_1 + 0x14c) = 0;
  *(uint32_t *)(param_1 + 4) = 0;
  trap_LinkEntity(param_1);
  return;
}

void Props_Barrel_Die(uint32_t *param_1,int param_2,uint32_t param_3,int param_4)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint8_t local_28 [8];
  uint32_t local_20;
  
  if ((*(byte *)(param_1 + 0x6a) & 1) != 0) {
    param_1[2] = 0x800;
  }
  G_UseTargets(param_1,0);
  if ((*(byte *)(param_1 + 0x6a) & 4) != 0) {
    tmp_i3 = G_Spawn();
    tmp_i2 = g_unk_00abe908;
    *(uint32_t *)(tmp_i3 + 0xf4) = *param_1;
    *(void **)(tmp_i3 + 0x2a4) = OilSlick_remove_think;
    *(int *)(tmp_i3 + 0x29c) = tmp_i2 + 1000;
    *(uint32_t *)(tmp_i3 + 0x168) = param_1[0x5a];
    *(uint32_t *)(tmp_i3 + 0x16c) = param_1[0x5b];
    *(uint32_t *)(tmp_i3 + 0x170) = param_1[0x5c];
    trap_LinkEntity(tmp_i3);
  }
  param_1[0xb2] = 100;
  tmp_i3 = G_Spawn();
  tmp_i2 = g_unk_00abe908;
  *(char **)(tmp_i3 + 0x1a4) = "props_explosion";
  *(int *)(tmp_i3 + 0x29c) = tmp_i2 + 100;
  *(uint32_t *)(tmp_i3 + 0x128) = 0;
  *(uint32_t *)(tmp_i3 + 4) = 3;
  *(uint32_t *)(tmp_i3 + 0x3fc) = 0x3f800000;
  *(void **)(tmp_i3 + 0x2a4) = G_ExplodeMissile;
  *(uint32_t *)(tmp_i3 + 0xe8) = 0;
  *(uint32_t *)(tmp_i3 + 8) = 0x8000000;
  tmp_u1 = *param_1;
  *(uint32_t **)(tmp_i3 + 0x218) = param_1;
  *(uint32_t *)(tmp_i3 + 0x180) = tmp_u1;
  *(uint32_t *)(tmp_i3 + 0x2d0) = param_1[0xb2];
  *(uint32_t *)(tmp_i3 + 0x2d4) = param_1[0xb2];
  *(int *)(tmp_i3 + 0x2d8) = (int)ROUND((float)(int)param_1[0xb2] * 1.5);
  *(uint32_t *)(tmp_i3 + 0x2dc) = 4;
  *(uint32_t *)(tmp_i3 + 0x2e0) = 4;
  *(uint32_t *)(tmp_i3 + 0x1d4) = 0x6000001;
  *(uint32_t *)(tmp_i3 + 0x18) = param_1[0x5a];
  *(uint32_t *)(tmp_i3 + 0x1c) = param_1[0x5b];
  *(uint32_t *)(tmp_i3 + 0x20) = param_1[0x5c];
  *(uint32_t *)(tmp_i3 + 0x168) = param_1[0x5a];
  *(uint32_t *)(tmp_i3 + 0x16c) = param_1[0x5b];
  *(uint32_t *)(tmp_i3 + 0x170) = param_1[0x5c];
  param_1[0xb2] = 0;
  param_1[0xb3] = 0;
  AngleVectors(param_1 + 0x5d,local_28,0,0);
  local_20 = 0x3f800000;
  if ((*(byte *)(param_1 + 0x6a) & 2) == 0) {
    fire_flamebarrel(param_1,param_1 + 0x5a,local_28);
  }
  param_1[0xac] = 0;
  param_1[0xa9] = Props_Barrel_Animate;
  param_1[0xa7] = g_unk_00abe908 + 100;
  param_1[0xb2] = (int)ROUND((float)param_1[200]);
  param_1[0xbb] = param_2;
  param_1[0xc6] = (float)param_4;
  if (param_2 != 0) {
    Spawn_Shard(param_1,param_2,(int)ROUND((float)param_1[0xc3]),param_1[0xb9]);
  }
  G_AddEvent(param_1,0x2d,0);
  tmp_i2 = param_1[0xb9];
  if (tmp_i2 == 1) {
    G_AddEvent(param_1,0x2d,1);
  }
  else if (tmp_i2 == 2) {
    G_AddEvent(param_1,0x2d,2);
  }
  else if (tmp_i2 == 0) {
    G_AddEvent(param_1,0x2d,0);
  }
  trap_UnlinkEntity(param_1);
  param_1[0x75] = 0;
  param_1[0x53] = 0;
  param_1[1] = 0;
  trap_LinkEntity(param_1);
  return;
}

void props_touch(int param_1,uint32_t param_2)
{
  uint tmp_u1;
  
  if ((*(uint *)(param_1 + 0x1a8) & 0x10) == 0) {
    return;
  }
  if ((*(uint *)(param_1 + 0x1a8) & 8) == 0) {
    *(uint32_t *)(param_1 + 0x1d4) = 0;
    *(uint32_t *)(param_1 + 0x14c) = 0;
    *(uint32_t *)(param_1 + 4) = 0;
    trap_LinkEntity(param_1);
  }
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  G_UseTargets(param_1,0);
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u1 & 2) != 0) {
    Spawn_Shard(param_1,param_2,*(uint32_t *)(param_1 + 0x2e4),*(uint32_t *)(param_1 + 0x364));
    tmp_u1 = *(uint *)(param_1 + 0x1a8);
  }
  if ((tmp_u1 & 4) != 0) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
    *(void **)(param_1 + 0x2a4) = props_decoration_animate;
    return;
  }
  G_FreeEntity(param_1);
  return;
}

void props_statue_touch(int param_1,uint32_t param_2)
{
  uint tmp_u1;
  
  *(int *)(param_1 + 0x24c) = g_unk_00abe908;
  G_AddEvent(param_1,0x28,*(uint32_t *)(param_1 + 0x308));
  if ((*(byte *)(param_1 + 0x1a8) & 8) == 0) {
    *(uint32_t *)(param_1 + 0x1d4) = 0;
    *(uint32_t *)(param_1 + 0x14c) = 0;
    *(uint32_t *)(param_1 + 4) = 0;
    trap_LinkEntity(param_1);
  }
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  G_UseTargets(param_1,0);
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u1 & 2) != 0) {
    Spawn_Shard(param_1,param_2,*(uint32_t *)(param_1 + 0x2e4),*(uint32_t *)(param_1 + 0x364));
    tmp_u1 = *(uint *)(param_1 + 0x1a8);
  }
  if ((tmp_u1 & 4) != 0) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
    *(void **)(param_1 + 0x2a4) = props_statue_animate;
    return;
  }
  G_FreeEntity(param_1);
  return;
}

void Props_Chair_Skyboxtouch(int param_1)
{
  *(void **)(param_1 + 0x2a4) = G_FreeEntity;
  return;
}

void SP_Props_Chair(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  int local_10 [2];
  
  local_10[1] = 0xb4c87;
  tmp_u2 = G_ModelIndex("models/furniture/chair/chair_office3.md3");
  *(uint32_t *)(param_1 + 0x318) = 0;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
  tmp_i3 = G_SpawnIntExt(&g_unk_0024d9e7,"5",local_10,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0x5c0);
  if (tmp_i3 == 0) {
    tmp_f1 = 5.0;
  }
  else {
    tmp_f1 = (float)local_10[0];
  }
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 0xf8) = 0xb;
  *(uint32_t *)(param_1 + 900) = 1;
  *(float *)(param_1 + 0x30c) = tmp_f1;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x134) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x41400000;
  *(uint32_t *)(param_1 + 0x144) = 0x41400000;
  *(uint32_t *)(param_1 + 0x148) = 0x42400000;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    tmp_f1 = 10.0;
    *(uint32_t *)(param_1 + 0x2c8) = 10;
  }
  else {
    tmp_f1 = (float)*(int *)(param_1 + 0x2c8);
  }
  *(void **)(param_1 + 0x2a4) = Props_Chair_Think;
  *(float *)(param_1 + 800) = tmp_f1;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2b0) = Props_Chair_Touch;
  *(void **)(param_1 + 700) = Props_Chair_Die;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  trap_LinkEntity(param_1);
  return;
}

void SP_Props_ChairHiback(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  int local_10 [2];
  
  local_10[1] = 0xb4e27;
  tmp_u2 = G_ModelIndex("models/furniture/chair/hiback5.md3");
  *(uint32_t *)(param_1 + 0x318) = 0;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
  tmp_i3 = G_SpawnIntExt(&g_unk_0024d9e7,"5",local_10,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0x5ec);
  if (tmp_i3 == 0) {
    tmp_f1 = 5.0;
  }
  else {
    tmp_f1 = (float)local_10[0];
  }
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 0xf8) = 0xb;
  *(uint32_t *)(param_1 + 900) = 1;
  *(float *)(param_1 + 0x30c) = tmp_f1;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x134) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x41400000;
  *(uint32_t *)(param_1 + 0x144) = 0x41400000;
  *(uint32_t *)(param_1 + 0x148) = 0x42400000;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    tmp_f1 = 10.0;
    *(uint32_t *)(param_1 + 0x2c8) = 10;
  }
  else {
    tmp_f1 = (float)*(int *)(param_1 + 0x2c8);
  }
  *(void **)(param_1 + 0x2a4) = Props_Chair_Think;
  *(float *)(param_1 + 800) = tmp_f1;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2b0) = Props_Chair_Touch;
  *(void **)(param_1 + 700) = Props_Chair_Die;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  trap_LinkEntity(param_1);
  return;
}

void SP_Props_ChairSide(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  int local_10 [2];
  
  local_10[1] = 0xb4fc7;
  tmp_u2 = G_ModelIndex("models/furniture/chair/sidechair3.md3");
  *(uint32_t *)(param_1 + 0x318) = 0;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
  tmp_i3 = G_SpawnIntExt(&g_unk_0024d9e7,"5",local_10,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0x618);
  if (tmp_i3 == 0) {
    tmp_f1 = 5.0;
  }
  else {
    tmp_f1 = (float)local_10[0];
  }
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 0xf8) = 0xb;
  *(uint32_t *)(param_1 + 900) = 1;
  *(float *)(param_1 + 0x30c) = tmp_f1;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x134) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x41400000;
  *(uint32_t *)(param_1 + 0x144) = 0x41400000;
  *(uint32_t *)(param_1 + 0x148) = 0x42400000;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    tmp_f1 = 10.0;
    *(uint32_t *)(param_1 + 0x2c8) = 10;
  }
  else {
    tmp_f1 = (float)*(int *)(param_1 + 0x2c8);
  }
  *(void **)(param_1 + 0x2a4) = Props_Chair_Think;
  *(float *)(param_1 + 800) = tmp_f1;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2b0) = Props_Chair_Touch;
  *(void **)(param_1 + 700) = Props_Chair_Die;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  trap_LinkEntity(param_1);
  return;
}

void SP_Props_ChateauChair(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  int local_10 [2];
  
  local_10[1] = 0xb516c;
  *(uint32_t *)(param_1 + 0x318) = 0;
  tmp_i2 = G_SpawnIntExt(&g_unk_0024d9e7,"5",local_10,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0x649);
  if (tmp_i2 == 0) {
    tmp_f1 = 5.0;
  }
  else {
    tmp_f1 = (float)local_10[0];
  }
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 0xf8) = 0xb;
  *(uint32_t *)(param_1 + 900) = 1;
  *(float *)(param_1 + 0x30c) = tmp_f1;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x134) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x41400000;
  *(uint32_t *)(param_1 + 0x144) = 0x41400000;
  *(uint32_t *)(param_1 + 0x148) = 0x42400000;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    tmp_f1 = 10.0;
    *(uint32_t *)(param_1 + 0x2c8) = 10;
  }
  else {
    tmp_f1 = (float)*(int *)(param_1 + 0x2c8);
  }
  *(void **)(param_1 + 0x2a4) = Props_Chair_Think;
  *(float *)(param_1 + 800) = tmp_f1;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2b0) = Props_Chair_Touch;
  *(void **)(param_1 + 700) = Props_Chair_Die;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  trap_LinkEntity(param_1);
  return;
}

void SP_Props_ChairChat(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  int local_10 [2];
  
  local_10[1] = 0xb52f7;
  tmp_u2 = G_ModelIndex("models/furniture/chair/chair_chat.md3");
  *(uint32_t *)(param_1 + 0x318) = 0;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
  tmp_i3 = G_SpawnIntExt(&g_unk_0024d9e7,"5",local_10,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0x649);
  if (tmp_i3 == 0) {
    tmp_f1 = 5.0;
  }
  else {
    tmp_f1 = (float)local_10[0];
  }
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 0xf8) = 0xb;
  *(uint32_t *)(param_1 + 900) = 1;
  *(float *)(param_1 + 0x30c) = tmp_f1;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x134) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x41400000;
  *(uint32_t *)(param_1 + 0x144) = 0x41400000;
  *(uint32_t *)(param_1 + 0x148) = 0x42400000;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    tmp_f1 = 10.0;
    *(uint32_t *)(param_1 + 0x2c8) = 10;
  }
  else {
    tmp_f1 = (float)*(int *)(param_1 + 0x2c8);
  }
  *(void **)(param_1 + 0x2a4) = Props_Chair_Think;
  *(float *)(param_1 + 800) = tmp_f1;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2b0) = Props_Chair_Touch;
  *(void **)(param_1 + 700) = Props_Chair_Die;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  trap_LinkEntity(param_1);
  return;
}

void SP_Props_ChairChatArm(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  int local_10 [2];
  
  local_10[1] = 0xb5497;
  tmp_u2 = G_ModelIndex("models/furniture/chair/chair_chatarm.md3");
  *(uint32_t *)(param_1 + 0x318) = 0;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
  tmp_i3 = G_SpawnIntExt(&g_unk_0024d9e7,"5",local_10,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0x649);
  if (tmp_i3 == 0) {
    tmp_f1 = 5.0;
  }
  else {
    tmp_f1 = (float)local_10[0];
  }
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 0xf8) = 0xb;
  *(uint32_t *)(param_1 + 900) = 1;
  *(float *)(param_1 + 0x30c) = tmp_f1;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x134) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1400000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x41400000;
  *(uint32_t *)(param_1 + 0x144) = 0x41400000;
  *(uint32_t *)(param_1 + 0x148) = 0x42400000;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    tmp_f1 = 10.0;
    *(uint32_t *)(param_1 + 0x2c8) = 10;
  }
  else {
    tmp_f1 = (float)*(int *)(param_1 + 0x2c8);
  }
  *(void **)(param_1 + 0x2a4) = Props_Chair_Think;
  *(float *)(param_1 + 800) = tmp_f1;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2b0) = Props_Chair_Touch;
  *(void **)(param_1 + 700) = Props_Chair_Die;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  trap_LinkEntity(param_1);
  return;
}

void SP_Props_DamageInflictor(int param_1)
{
  G_SetOrigin(param_1,param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 4) = 0;
  *(void **)(param_1 + 0x2b4) = Use_DamageInflictor;
  trap_LinkEntity(param_1);
  return;
}

void SP_props_shard_generator(int param_1)
{
  G_SetOrigin(param_1,param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 4) = 0;
  *(void **)(param_1 + 0x2b4) = Use_Props_Shard_Generator;
  if (*(float *)(param_1 + 0x30c) == 0.0) {
    *(uint32_t *)(param_1 + 0x30c) = 0x40a00000;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_Props_Desklamp(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  int local_10 [2];
  
  local_10[1] = 0xb5717;
  tmp_u2 = G_ModelIndex("models/furniture/lights/desklamp.md3");
  *(uint32_t *)(param_1 + 0x318) = 0;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
  tmp_i3 = G_SpawnIntExt(&g_unk_0024d9e7,"5",local_10,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0x6e5);
  if (tmp_i3 == 0) {
    tmp_f1 = 2.0;
  }
  else {
    tmp_f1 = (float)local_10[0];
  }
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 900) = 1;
  *(float *)(param_1 + 0x30c) = tmp_f1;
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x134) = 0xc0c00000;
  *(uint32_t *)(param_1 + 0x138) = 0xc0c00000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x40c00000;
  *(uint32_t *)(param_1 + 0x144) = 0x40c00000;
  *(uint32_t *)(param_1 + 0x148) = 0x41600000;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    tmp_f1 = 10.0;
    *(uint32_t *)(param_1 + 0x2c8) = 10;
  }
  else {
    tmp_f1 = (float)*(int *)(param_1 + 0x2c8);
  }
  *(float *)(param_1 + 800) = tmp_f1;
  if (*(int *)(param_1 + 0x2e4) == 0) {
    *(uint32_t *)(param_1 + 0x2e4) = 2;
  }
  *(void **)(param_1 + 0x2a4) = Props_Chair_Think;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2b0) = Props_Chair_Touch;
  *(void **)(param_1 + 700) = Props_Chair_Die;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  trap_LinkEntity(param_1);
  return;
}

void SP_OilSlick(uint32_t *param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_i2 = nitrox_TempEventFromQueue(param_1 + 0x5a,0x4d);
  *(uint32_t *)(tmp_i2 + 0x5c) = param_1[0x5a];
  *(uint32_t *)(tmp_i2 + 0x60) = param_1[0x5b];
  tmp_u1 = param_1[0x5c];
  *(uint32_t *)(tmp_i2 + 0x80) = 0x41800000;
  *(uint32_t *)(tmp_i2 + 100) = tmp_u1;
  *(uint32_t *)(tmp_i2 + 0x84) = 0x42400000;
  *(uint32_t *)(tmp_i2 + 0x88) = 0x461c4000;
  *(uint32_t *)(tmp_i2 + 0xf4) = *param_1;
  return;
}

void SP_OilParticles(void)
{
  return;
}

void SP_Props_Flamebarrel(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  int local_10 [2];
  
  if ((*(uint *)(param_1 + 0x1a8) & 4) == 0) {
    if ((*(uint *)(param_1 + 0x1a8) & 1) == 0) {
      tmp_u2 = G_ModelIndex("models/furniture/barrel/barrel_b.md3");
      *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
    }
    else {
      tmp_u2 = G_ModelIndex("models/furniture/barrel/barrel_d.md3");
      *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
    }
  }
  else {
    tmp_u2 = G_ModelIndex("models/furniture/barrel/barrel_c.md3");
    *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
  }
  *(uint32_t *)(param_1 + 0x318) = 0;
  tmp_i3 = G_SpawnIntExt(&g_unk_0024d9e7,"5",local_10,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0x843);
  if (tmp_i3 == 0) {
    tmp_f1 = 10.0;
  }
  else {
    tmp_f1 = (float)local_10[0];
  }
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 900) = 1;
  *(float *)(param_1 + 0x30c) = tmp_f1;
  *(uint32_t *)(param_1 + 4) = 4;
  *(uint32_t *)(param_1 + 0x134) = 0xc1500000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1500000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x41500000;
  *(uint32_t *)(param_1 + 0x144) = 0x41500000;
  *(uint32_t *)(param_1 + 0x148) = 0x42100000;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    tmp_f1 = 20.0;
    *(uint32_t *)(param_1 + 0x2c8) = 0x14;
  }
  else {
    tmp_f1 = (float)*(int *)(param_1 + 0x2c8);
  }
  *(void **)(param_1 + 0x2a4) = Props_Barrel_Think;
  *(float *)(param_1 + 800) = tmp_f1;
  *(uint32_t *)(param_1 + 0x2e4) = 2;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2b0) = Props_Barrel_Touch;
  *(void **)(param_1 + 700) = Props_Barrel_Die;
  if ((*(byte *)(param_1 + 0x1a8) & 4) != 0) {
    *(void **)(param_1 + 0x2b8) = Props_Barrel_Pain;
  }
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  trap_LinkEntity(param_1);
  return;
}

void SP_crate_64(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = G_ModelIndex("models/furniture/crate/crate64.md3");
  *(uint32_t *)(param_1 + 0x134) = 0xc2000000;
  *(uint32_t *)(param_1 + 0x138) = 0xc2000000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x42000000;
  *(uint32_t *)(param_1 + 0x144) = 0x42000000;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u1;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 900) = 1;
  *(uint32_t *)(param_1 + 0x148) = 0x42800000;
  *(uint32_t *)(param_1 + 4) = 4;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  *(void **)(param_1 + 0x2b0) = touch_crate_64;
  *(void **)(param_1 + 700) = crate_die;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  if (*(int *)(param_1 + 0x2c8) == 0) {
    *(uint32_t *)(param_1 + 0x2c8) = 0x14;
  }
  if (*(int *)(param_1 + 0x2e4) == 0) {
    *(uint32_t *)(param_1 + 0x2e4) = 1;
  }
  if (*(float *)(param_1 + 0x30c) == 0.0) {
    *(uint32_t *)(param_1 + 0x30c) = 0x41200000;
  }
  *(uint32_t *)(param_1 + 900) = 1;
  trap_LinkEntity(param_1);
  *(void **)(param_1 + 0x2a4) = DropToFloor;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

void SP_crate_32(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = G_ModelIndex("models/furniture/crate/crate32.md3");
  *(uint32_t *)(param_1 + 0x134) = 0xc1800000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1800000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x41800000;
  *(uint32_t *)(param_1 + 0x144) = 0x41800000;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u1;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 900) = 1;
  *(uint32_t *)(param_1 + 0x148) = 0x42000000;
  *(uint32_t *)(param_1 + 4) = 4;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  *(void **)(param_1 + 0x2b0) = touch_crate_64;
  *(void **)(param_1 + 700) = crate_die;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  if (*(int *)(param_1 + 0x2c8) == 0) {
    *(uint32_t *)(param_1 + 0x2c8) = 0x14;
  }
  if (*(int *)(param_1 + 0x2e4) == 0) {
    *(uint32_t *)(param_1 + 0x2e4) = 1;
  }
  if (*(float *)(param_1 + 0x30c) == 0.0) {
    *(uint32_t *)(param_1 + 0x30c) = 0x41200000;
  }
  *(uint32_t *)(param_1 + 900) = 1;
  trap_LinkEntity(param_1);
  *(void **)(param_1 + 0x2a4) = DropToFloor;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

void SP_Props_Crate32x64(int param_1)
{
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  InitProp(param_1);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    *(uint32_t *)(param_1 + 0x2c8) = 10;
  }
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(void **)(param_1 + 700) = props_crate32x64_die;
  trap_LinkEntity(param_1);
  return;
}

void props_flippy_table_die(int param_1)
{
  *(void **)(param_1 + 0x2a4) = flippy_table_animate;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(uint32_t *)(param_1 + 0x2cc) = 0;
  G_UseTargets(param_1,0);
  return;
}

void SP_Props_Flipping_Table(int param_1)
{
  uint tmp_u1;
  
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
    *(uint32_t *)(param_1 + 0x268) = 0x43fa0000;
    *(uint32_t *)(param_1 + 0x250) = 0x42b40000;
    if ((*(byte *)(param_1 + 0x1a8) & 0xc) == 0) {
      G_Printf("you forgot to select the X or Y Axis\n");
    }
    tmp_u1 = *(uint *)(param_1 + 0x1a8);
    *(uint32_t *)(param_1 + 0x32c) = 0;
    *(uint32_t *)(param_1 + 0x328) = 0;
    *(uint32_t *)(param_1 + 0x324) = 0;
    if ((tmp_u1 & 4) == 0) {
      if ((tmp_u1 & 8) == 0) {
        *(uint32_t *)(param_1 + 0x328) = 0x3f800000;
      }
      else {
        *(uint32_t *)(param_1 + 0x324) = 0x3f800000;
      }
    }
    else {
      *(uint32_t *)(param_1 + 0x32c) = 0x3f800000;
    }
    *(uint *)(param_1 + 0x1a8) = tmp_u1 | 0x40;
    InitMoverRotate(param_1);
    *(void **)(param_1 + 0x2ac) = props_flippy_blocked;
    *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
    *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
    *(uint32_t *)(param_1 + 0x174) = *(uint32_t *)(param_1 + 0x3c);
    *(uint32_t *)(param_1 + 0x178) = *(uint32_t *)(param_1 + 0x40);
    *(uint32_t *)(param_1 + 0x17c) = *(uint32_t *)(param_1 + 0x44);
    if (*(int *)(param_1 + 0x2c8) == 0) {
      *(uint32_t *)(param_1 + 0x2c8) = 100;
    }
    *(void **)(param_1 + 0x2b4) = flippy_table_use;
    *(float *)(param_1 + 0x30c) = *(float *)(param_1 + 0x30c) * 1000.0;
    trap_LinkEntity(param_1);
    return;
  }
  G_Printf("^1props_Flipping_Table with NULL model\n");
  return;
}

void SP_Props_58x112tablew(int param_1)
{
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  InitProp(param_1);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    *(uint32_t *)(param_1 + 0x2c8) = 10;
  }
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(void **)(param_1 + 700) = props_58x112tablew_die;
  trap_LinkEntity(param_1);
  return;
}

void SP_props_castlebed(int param_1)
{
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  InitProp(param_1);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    *(uint32_t *)(param_1 + 0x2c8) = 0x14;
  }
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  *(void **)(param_1 + 700) = props_castlebed_die;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(void **)(param_1 + 0x2b0) = props_castlebed_touch;
  trap_LinkEntity(param_1);
  return;
}

void SP_props_snowGenerator(int param_1)
{
  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  float local_18;
  float local_14;
  float local_10;
  
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  local_18 = (*(float *)(param_1 + 0x150) + *(float *)(param_1 + 0x15c)) * 0.5;
  local_14 = (*(float *)(param_1 + 0x154) + *(float *)(param_1 + 0x160)) * 0.5;
  local_10 = (*(float *)(param_1 + 0x158) + *(float *)(param_1 + 0x164)) * 0.5;
  *(float *)(param_1 + 0x224) = local_18;
  *(float *)(param_1 + 0x228) = local_14;
  *(float *)(param_1 + 0x22c) = local_10;
  if (*(int *)(param_1 + 0x254) == 0) {
    tmp_u4 = vtos(&local_18);
    G_Printf("snowGenerator at loc %s does not have a target\n",tmp_u4);
    return;
  }
  tmp_i3 = G_Find(0,600,*(int *)(param_1 + 0x254));
  if (tmp_i3 == 0) {
    tmp_u4 = *(uint32_t *)(param_1 + 0x254);
    tmp_u5 = vtos(&local_18);
    G_Printf("error snowGenerator at loc %s does cant find target %s\n",tmp_u5,tmp_u4);
    return;
  }
  *(float *)(param_1 + 0x270) = *(float *)(tmp_i3 + 0x5c) - *(float *)(param_1 + 0x5c);
  *(float *)(param_1 + 0x274) = *(float *)(tmp_i3 + 0x60) - *(float *)(param_1 + 0x60);
  *(float *)(param_1 + 0x278) = *(float *)(tmp_i3 + 100) - *(float *)(param_1 + 100);
  VectorNormalize(param_1 + 0x270);
  *(uint32_t *)(param_1 + 0x128) = 1;
  tmp_u2 = *(uint *)(param_1 + 0x1a8);
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  if ((tmp_u2 & 3) != 0) {
    *(void **)(param_1 + 0x2a4) = props_snowGenerator_think;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
    if ((tmp_u2 & 2) != 0) {
      *(uint *)(param_1 + 0x1a8) = tmp_u2 | 1;
    }
  }
  *(void **)(param_1 + 0x2b4) = props_snowGenerator_use;
  if (*(float *)(param_1 + 0x318) == 0.0) {
    tmp_f1 = 100.0;
  }
  else {
    tmp_f1 = *(float *)(param_1 + 0x318) * 100.0;
  }
  *(float *)(param_1 + 0x318) = tmp_f1;
  if (*(int *)(param_1 + 0x2e4) == 0) {
    *(uint32_t *)(param_1 + 0x2e4) = 0x20;
  }
  if (*(float *)(param_1 + 800) == 0.0) {
    tmp_f1 = 1000.0;
  }
  else {
    tmp_f1 = *(float *)(param_1 + 800) * 1000.0;
  }
  *(float *)(param_1 + 800) = tmp_f1;
  trap_LinkEntity(param_1);
  return;
}

void SP_props_decoration(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  long tmp_l6;
  uint tmp_u7;
  double tmp_d8;
  float local_60;
  float local_48;
  uint32_t local_44;
  uint32_t local_40;
  char *local_3c;
  char *local_38;
  char *local_34;
  char *local_30;
  char *local_2c;
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0xb681e;
  tmp_i2 = G_SpawnStringExt("startonframe",&g_unk_0024bfa6,&local_2c,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xb88);
  if (tmp_i2 != 0) {
    tmp_l6 = strtol(local_2c,(char **)0x0,10);
    *(long *)(param_1 + 0xb0) = tmp_l6;
  }
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u3 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa4) = tmp_u3;
  }
  tmp_i2 = G_SpawnStringExt("noise",&g_unk_002496df,&local_44,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xb91);
  if (tmp_i2 != 0) {
    tmp_u3 = G_SoundIndex(local_44);
    *(uint32_t *)(param_1 + 0xa0) = tmp_u3;
  }
  if (((*(byte *)(param_1 + 0x1a8) & 0x20) != 0) &&
     (tmp_i2 = G_SpawnStringExt("loop",&g_unk_002496df,&local_30,
                               "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xb95),
     tmp_i2 != 0)) {
    tmp_l6 = strtol(local_30,(char **)0x0,10);
    *(long *)(param_1 + 0x374) = tmp_l6;
  }
  tmp_i2 = G_SpawnFloatExt("light",&g_unk_002496df,&local_48,
                          "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xb9a);
  tmp_i4 = G_SpawnVectorExt("color","1 1 1",&local_28,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xb9b);
  if (tmp_i4 != 0 || tmp_i2 != 0) {
    tmp_u7 = (uint)ROUND(local_28 * 255.0);
    tmp_i2 = (int)ROUND(local_24 * 255.0);
    tmp_i4 = (int)ROUND(local_20 * 255.0);
    if (0xff < tmp_i2) {
      tmp_i2 = 0xff;
    }
    if (0xff < tmp_i4) {
      tmp_i4 = 0xff;
    }
    tmp_i5 = (int)ROUND(local_48 * 0.25);
    if (0xff < (int)tmp_u7) {
      tmp_u7 = 0xff;
    }
    if (0xff < tmp_i5) {
      tmp_i5 = 0xff;
    }
    *(uint *)(param_1 + 0x98) = tmp_i5 << 0x18 | tmp_u7 | tmp_i4 << 0x10 | tmp_i2 << 8;
  }
  if (*(int *)(param_1 + 0x2c8) == 0) {
    tmp_u7 = *(uint *)(param_1 + 0x1a8);
    if ((tmp_u7 & 4) != 0) {
      G_SpawnStringExt("frames",&g_unk_0024bfa6,&local_34,
                       "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xbe8);
      tmp_d8 = strtod(local_34,(char **)0x0);
      *(int *)(param_1 + 0x39c) = (int)ROUND((float)tmp_d8);
      *(void **)(param_1 + 0x2b4) = Use_props_decoration;
      tmp_u7 = *(uint *)(param_1 + 0x1a8);
    }
  }
  else {
    *(uint32_t *)(param_1 + 900) = 1;
    *(uint32_t *)(param_1 + 0x2cc) = 1;
    *(void **)(param_1 + 700) = props_decoration_death;
    G_SpawnStringExt("type",&g_unk_0024d9ec,&local_40,
                     "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",3000);
    tmp_i2 = Q_stricmp(local_40,&g_unk_0024d9ec);
    if (tmp_i2 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 1;
    }
    else {
      tmp_i2 = Q_stricmp(local_40,"glass");
      if (tmp_i2 == 0) {
        *(uint32_t *)(param_1 + 0x364) = 0;
      }
      else {
        tmp_i2 = Q_stricmp(local_40,"metal");
        if (tmp_i2 == 0) {
          *(uint32_t *)(param_1 + 0x364) = 2;
        }
        else {
          tmp_i2 = Q_stricmp(local_40,"rubble");
          if (tmp_i2 == 0) {
            *(uint32_t *)(param_1 + 0x364) = 3;
          }
        }
      }
    }
    G_SpawnStringExt(&g_unk_0024df46,&g_unk_0024bfa6,&local_3c,
                     "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xbbe);
    tmp_d8 = strtod(local_3c,(char **)0x0);
    local_60 = (float)tmp_d8;
    if (local_60 == 0.0) {
      local_60 = 4.0;
    }
    G_SpawnStringExt(&g_unk_0024df4b,&g_unk_0024bfa6,&local_38,
                     "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xbc4);
    tmp_d8 = strtod(local_38,(char **)0x0);
    if ((float)tmp_d8 == 0.0) {
      tmp_f1 = 2.0;
    }
    else {
      tmp_f1 = (float)tmp_d8 * 0.5;
    }
    tmp_i2 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_decorBRUSH");
    if (tmp_i2 != 0) {
      *(uint32_t *)(param_1 + 0x13c) = 0;
      *(float *)(param_1 + 0x134) = -tmp_f1;
      *(float *)(param_1 + 0x138) = -tmp_f1;
      *(float *)(param_1 + 0x140) = tmp_f1;
      *(float *)(param_1 + 0x144) = tmp_f1;
      *(float *)(param_1 + 0x148) = local_60;
    }
    *(uint32_t *)(param_1 + 0x1d4) = 1;
    *(uint32_t *)(param_1 + 0x14c) = 1;
    *(uint32_t *)(param_1 + 4) = 4;
    G_SpawnStringExt("frames",&g_unk_0024bfa6,&local_34,
                     "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xbd6);
    tmp_d8 = strtod(local_34,(char **)0x0);
    *(int *)(param_1 + 0x39c) = (int)ROUND((float)tmp_d8);
    if ((*(int *)(param_1 + 600) != 0) && (*(int *)(param_1 + 0x5cc) == 0)) {
      *(void **)(param_1 + 0x2b4) = Use_props_decoration;
    }
    *(void **)(param_1 + 0x2b0) = props_touch;
    tmp_u7 = *(uint *)(param_1 + 0x1a8);
  }
  if ((tmp_u7 & 0x40) != 0) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
    *(void **)(param_1 + 0x2a4) = props_decoration_animate;
  }
  *(uint32_t *)(param_1 + 0x128) = 0;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  if ((*(byte *)(param_1 + 0x1a8) & 1) != 0) {
    *(void **)(param_1 + 0x2b4) = Use_props_decoration;
    return;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_props_decorBRUSH(int param_1)
{
  uint32_t tmp_u1;
  
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  SP_props_decoration(param_1);
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u1 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u1;
  }
  return;
}

void SP_props_decor_Scale(int param_1)
{
  int tmp_i1;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_24 = 0x3f800000;
  local_20 = 0x3f800000;
  local_1c = 0x3f800000;
  SP_props_decoration(param_1);
  *(uint32_t *)(param_1 + 4) = 0x12;
  tmp_i1 = G_SpawnFloatExt("modelscale",&g_unk_00258b23,&local_24,
                          "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xc41);
  if (tmp_i1 != 0) {
    local_20 = local_24;
    local_1c = local_24;
  }
  tmp_i1 = G_SpawnVectorExt("modelscale_vec","1 1 1",&local_18,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xc46);
  if (tmp_i1 != 0) {
    local_24 = local_18;
    local_20 = local_14;
    local_1c = local_10;
  }
  *(uint32_t *)(param_1 + 0x80) = local_24;
  *(uint32_t *)(param_1 + 0x84) = local_20;
  *(uint32_t *)(param_1 + 0x88) = local_1c;
  trap_LinkEntity(param_1);
  return;
}

void SP_skyportal(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  double tmp_d5;
  char *local_34;
  uint32_t local_30;
  uint32_t local_2c;
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0xb6fee;
  G_SpawnStringExt(&g_unk_0024df64,&g_unk_0024df61,&local_34,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xc63);
  tmp_d5 = strtod(local_34,(char **)0x0);
  tmp_i1 = G_SpawnVectorExt("fogcolor","0 0 0",&local_28,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xc67);
  tmp_i2 = G_SpawnIntExt("fognear",&g_unk_0024bfa6,&local_30,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xc68);
  tmp_i3 = G_SpawnIntExt("fogfar",&g_unk_0024df79,&local_2c,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xc69);
  tmp_u4 = va("%.2f %.2f %.2f %.1f %i %.2f %.2f %.2f %i %i",(double)*(float *)(param_1 + 0x5c),
             (double)*(float *)(param_1 + 0x60),(double)*(float *)(param_1 + 100),
             (double)(float)tmp_d5,tmp_i3 + tmp_i1 + tmp_i2,(double)local_28,(double)local_24,
             (double)local_20,local_30,local_2c);
  trap_SetConfigstring(0x13,tmp_u4);
  return;
}

void props_statue_blocked(uint32_t *param_1)
{
  int *tmp_pi1;
  float tmp_f2;
  int tmp_i3;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  float local_50;
  float local_4c;
  float local_48;
  uint8_t local_44 [12];
  uint8_t local_38 [32];
  byte local_18;
  int local_10;
  
  tmp_i3 = Q_stricmp(param_1[0x69],"props_statueBRUSH");
  if (tmp_i3 != 0) {
    local_80 = (float)param_1[0x17];
    local_60 = 0xc1b80000;
    local_7c = (float)param_1[0x18];
    local_54 = 0x41b80000;
    local_78 = (float)param_1[0x19] + 24.0;
    local_68 = param_1[0x4d];
    local_64 = param_1[0x4e];
    local_5c = param_1[0x50];
    local_58 = param_1[0x51];
    AngleVectors(param_1 + 0x5d,&local_50,0,0);
    tmp_f2 = (float)(int)param_1[0x2c] * (((float)param_1[0x52] + 16.0) / (float)(int)param_1[0xe7]);
    local_74 = local_50 * tmp_f2 + local_80;
    local_70 = local_4c * tmp_f2 + local_7c;
    local_6c = tmp_f2 * local_48 + local_78;
    trap_Trace(local_44,&local_80,&local_68,&local_5c,&local_74,*param_1,0x6000001);
    if ((local_18 & 0x10) == 0) {
      local_10 = local_10 * 0x600;
      if ((*(int *)(g_entities + local_10 + 0x2cc) == 0) ||
         (tmp_pi1 = (int *)(g_entities + local_10 + 400), *tmp_pi1 == 0)) {
        G_Damage(g_entities + local_10,param_1,param_1,0,local_38,9999,0,0x1d);
      }
      else {
        G_Damage(g_entities + local_10,param_1,param_1,0,local_38,param_1[0xb4],0,0x1d);
        *(float *)(*tmp_pi1 + 0x20) = local_50 * 128.0 + *(float *)(*tmp_pi1 + 0x20);
        *(float *)(*tmp_pi1 + 0x24) = local_4c * 128.0 + *(float *)(*tmp_pi1 + 0x24);
        *(float *)(*tmp_pi1 + 0x28) = local_48 * 128.0 + *(float *)(*tmp_pi1 + 0x28);
        if (*(int *)(*tmp_pi1 + 0x10) == 0) {
          *(uint32_t *)(*tmp_pi1 + 0x10) = 200;
          *(uint *)(*tmp_pi1 + 0xc) = *(uint *)(*tmp_pi1 + 0xc) | 0x40;
        }
      }
    }
  }
  return;
}

void props_statue_animate(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = *(int *)(param_1 + 0x39c);
  *(uint32_t *)(param_1 + 4) = 0;
  tmp_i1 = *(int *)(param_1 + 0xb0) + 1;
  *(int *)(param_1 + 0xb0) = tmp_i1;
  if (tmp_i2 < tmp_i1) {
    *(int *)(param_1 + 0xb0) = tmp_i2;
    *(uint32_t *)(param_1 + 0x2cc) = 0;
  }
  if ((float)*(int *)(param_1 + 0x24c) + *(float *)(param_1 + 0x318) * 1000.0 <= (float)g_unk_00abe908
     ) {
    if (*(int *)(param_1 + 0x2e4) == 5) {
      *(uint32_t *)(param_1 + 0x2e4) = 0;
      props_statue_blocked(param_1);
      tmp_i2 = *(int *)(param_1 + 0x39c);
    }
    else {
      *(int *)(param_1 + 0x2e4) = *(int *)(param_1 + 0x2e4) + 1;
    }
  }
  else {
    *(uint32_t *)(param_1 + 0x2e4) = 0;
  }
  if (*(int *)(param_1 + 0xb0) < tmp_i2) {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
  }
  return;
}

void SP_props_statue(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint tmp_u5;
  int tmp_i6;
  double tmp_d7;
  float local_60;
  float local_40;
  uint32_t local_3c;
  uint32_t local_38;
  char *local_34;
  char *local_30;
  char *local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u2 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
  }
  tmp_i3 = G_SpawnStringExt("noise",&g_unk_002496df,&local_3c,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xd21);
  if (tmp_i3 != 0) {
    tmp_u2 = G_SoundIndex(local_3c);
    *(uint32_t *)(param_1 + 0x308) = tmp_u2;
  }
  tmp_i3 = G_SpawnFloatExt("light",&g_unk_002496df,&local_40,
                          "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xd26);
  tmp_i4 = G_SpawnVectorExt("color","1 1 1",&local_28,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xd27);
  if (tmp_i4 != 0 || tmp_i3 != 0) {
    tmp_u5 = (uint)ROUND(local_28 * 255.0);
    tmp_i3 = (int)ROUND(local_24 * 255.0);
    tmp_i4 = (int)ROUND(local_20 * 255.0);
    if (0xff < tmp_i3) {
      tmp_i3 = 0xff;
    }
    if (0xff < tmp_i4) {
      tmp_i4 = 0xff;
    }
    if (0xff < (int)tmp_u5) {
      tmp_u5 = 0xff;
    }
    tmp_i6 = 0xff;
    if ((int)ROUND(local_40 * 0.25) < 0x100) {
      tmp_i6 = (int)ROUND(local_40 * 0.25);
    }
    *(uint *)(param_1 + 0x98) = tmp_i3 << 8 | tmp_i4 << 0x10 | tmp_u5 | tmp_i6 << 0x18;
  }
  *(uint32_t *)(param_1 + 900) = 1;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  *(void **)(param_1 + 700) = props_statue_death;
  G_SpawnStringExt("type",&g_unk_0024d9ec,&local_38,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xd42);
  tmp_i3 = Q_stricmp(local_38,&g_unk_0024d9ec);
  if (tmp_i3 == 0) {
    *(uint32_t *)(param_1 + 0x364) = 1;
  }
  else {
    tmp_i3 = Q_stricmp(local_38,"glass");
    if (tmp_i3 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 0;
    }
    else {
      tmp_i3 = Q_stricmp(local_38,"metal");
      if (tmp_i3 == 0) {
        *(uint32_t *)(param_1 + 0x364) = 2;
      }
      else {
        tmp_i3 = Q_stricmp(local_38,"rubble");
        if (tmp_i3 == 0) {
          *(uint32_t *)(param_1 + 0x364) = 3;
        }
      }
    }
  }
  G_SpawnStringExt(&g_unk_0024df46,&g_unk_0024bfa6,&local_34,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xd48);
  tmp_d7 = strtod(local_34,(char **)0x0);
  local_60 = (float)tmp_d7;
  if (local_60 == 0.0) {
    local_60 = 4.0;
  }
  G_SpawnStringExt(&g_unk_0024df4b,&g_unk_0024bfa6,&local_30,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xd4d);
  tmp_d7 = strtod(local_30,(char **)0x0);
  if ((float)tmp_d7 == 0.0) {
    tmp_f1 = 2.0;
  }
  else {
    tmp_f1 = (float)tmp_d7 * 0.5;
  }
  tmp_i3 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),"props_statueBRUSH");
  if (tmp_i3 != 0) {
    *(uint32_t *)(param_1 + 0x13c) = 0;
    *(float *)(param_1 + 0x134) = -tmp_f1;
    *(float *)(param_1 + 0x138) = -tmp_f1;
    *(float *)(param_1 + 0x140) = tmp_f1;
    *(float *)(param_1 + 0x144) = tmp_f1;
    *(float *)(param_1 + 0x148) = local_60;
  }
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 4) = 4;
  G_SpawnStringExt("frames",&g_unk_0024bfa6,&local_2c,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xd5f);
  tmp_d7 = strtod(local_2c,(char **)0x0);
  *(int *)(param_1 + 0x39c) = (int)ROUND((float)tmp_d7);
  *(void **)(param_1 + 0x2b0) = props_statue_touch;
  *(uint32_t *)(param_1 + 0x128) = 0;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  if (*(int *)(param_1 + 0x2d0) == 0) {
    *(uint32_t *)(param_1 + 0x2d0) = 1;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_props_statueBRUSH(int param_1)
{
  uint32_t tmp_u1;
  
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  SP_props_statue(param_1);
  if (*(int *)(param_1 + 0x1b8) != 0) {
    tmp_u1 = G_ModelIndex(*(int *)(param_1 + 0x1b8));
    *(uint32_t *)(param_1 + 0xa8) = tmp_u1;
  }
  if (*(int *)(param_1 + 0x2c8) == 0) {
    *(uint32_t *)(param_1 + 0x2c8) = 6;
  }
  return;
}

void props_locker_spawn_item(uint32_t *param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  
  tmp_i1 = BG_FindItem(param_1[0xe3]);
  if (tmp_i1 != 0) {
    tmp_u3 = *param_1;
    tmp_u2 = tv(0,0,0x41a00000);
    tmp_i1 = LaunchItem(tmp_i1,param_1 + 0x5a,tmp_u2,tmp_u3,0x1000);
    if (tmp_i1 == 0) {
      G_Printf("-----> WARNING <-------\n");
      tmp_u3 = vtos(param_1 + 0x5a);
      G_Printf("props_locker_spawn_item at %s failed!\n",tmp_u3);
    }
  }
  return;
}

void props_locker_mass(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint32_t tmp_u4;
  float tmp_f5;
  uint tmp_u6;
  uint tmp_u7;
  int tmp_i8;
  float local_18;
  float local_14;
  float local_10;
  
  tmp_f1 = *(float *)(param_1 + 0x168);
  tmp_f2 = *(float *)(param_1 + 0x16c);
  tmp_f3 = *(float *)(param_1 + 0x170);
  tmp_u6 = rand();
  tmp_u7 = rand();
  tmp_f5 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
  local_18 = ((tmp_f5 + tmp_f5) * 32.0 + tmp_f1) - *(float *)(param_1 + 0x168);
  tmp_f1 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
  local_14 = ((tmp_f1 + tmp_f1) * 32.0 + tmp_f2) - *(float *)(param_1 + 0x16c);
  local_10 = (tmp_f3 + 16.0) - *(float *)(param_1 + 0x170);
  VectorNormalize(&local_18);
  tmp_i8 = nitrox_TempEventFromQueue(param_1 + 0x168,0x41);
  *(uint32_t *)(tmp_i8 + 0x5c) = *(uint32_t *)(param_1 + 0x168);
  *(uint32_t *)(tmp_i8 + 0x60) = *(uint32_t *)(param_1 + 0x16c);
  tmp_u4 = *(uint32_t *)(param_1 + 0x170);
  *(uint32_t *)(tmp_i8 + 0x9c) = 0;
  *(uint32_t *)(tmp_i8 + 100) = tmp_u4;
  *(float *)(tmp_i8 + 0x80) = local_18;
  *(float *)(tmp_i8 + 0x84) = local_14;
  *(float *)(tmp_i8 + 0x88) = local_10;
  trap_SetConfigstring(0x14,*(uint32_t *)(param_1 + 0x35c));
  tmp_u4 = *(uint32_t *)(param_1 + 0x364);
  *(uint32_t *)(tmp_i8 + 0xbc) = 8;
  *(uint32_t *)(tmp_i8 + 0xf4) = 100;
  *(uint32_t *)(tmp_i8 + 0xb0) = tmp_u4;
  return;
}

void SP_props_footlocker(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20 [4];
  
  if ((*(float *)(param_1 + 0x78) == 90.0) || (*(float *)(param_1 + 0x78) == 270.0)) {
    *(uint32_t *)(param_1 + 0x134) = 0xc1a80000;
    *(uint32_t *)(param_1 + 0x138) = 0xc1400000;
    *(uint32_t *)(param_1 + 0x13c) = 0;
    *(uint32_t *)(param_1 + 0x140) = 0x41a80000;
    *(uint32_t *)(param_1 + 0x144) = 0x41400000;
    *(uint32_t *)(param_1 + 0x148) = 0x41c00000;
  }
  else {
    *(uint32_t *)(param_1 + 0x134) = 0xc1400000;
    *(uint32_t *)(param_1 + 0x138) = 0xc1a80000;
    *(uint32_t *)(param_1 + 0x13c) = 0;
    *(uint32_t *)(param_1 + 0x140) = 0x41400000;
    *(uint32_t *)(param_1 + 0x144) = 0x41a80000;
    *(uint32_t *)(param_1 + 0x148) = 0x41c00000;
  }
  tmp_u2 = G_ModelIndex("models/mapobjects/furniture/footlocker.md3");
  *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
  tmp_i3 = G_SpawnStringExt("noise","NOSOUND",&local_28,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xe59);
  if (tmp_i3 != 0) {
    tmp_u2 = G_SoundIndex(local_28);
    *(uint32_t *)(param_1 + 0x308) = tmp_u2;
  }
  tmp_i3 = G_SpawnStringExt("locknoise","NOSOUND",&local_24,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xe5c);
  if (tmp_i3 != 0) {
    tmp_u2 = G_SoundIndex(local_24);
    *(uint32_t *)(param_1 + 0x1e8) = tmp_u2;
  }
  if (*(float *)(param_1 + 0x30c) == 0.0) {
    tmp_f1 = 1000.0;
  }
  else {
    tmp_f1 = *(float *)(param_1 + 0x30c) * 1000.0;
  }
  *(float *)(param_1 + 0x30c) = tmp_f1;
  tmp_i3 = G_SpawnIntExt(&g_unk_0024d9e7,&g_unk_0024a57a,local_20,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xe64);
  tmp_u2 = 0x4b;
  if (tmp_i3 != 0) {
    tmp_u2 = local_20[0];
  }
  *(uint32_t *)(param_1 + 0x2e4) = tmp_u2;
  tmp_i3 = G_SpawnStringExt("type",&g_unk_0024d9ec,&local_2c,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xe69);
  if ((tmp_i3 != 0) && (tmp_i3 = Q_stricmp(local_2c,&g_unk_0024d9ec), tmp_i3 != 0)) {
    tmp_i3 = Q_stricmp(local_2c,"glass");
    if (tmp_i3 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 1;
      goto LAB_000b7e41;
    }
    tmp_i3 = Q_stricmp(local_2c,"metal");
    if (tmp_i3 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 2;
      goto LAB_000b7e41;
    }
    tmp_i3 = Q_stricmp(local_2c,&g_unk_0024d9fd);
    if (tmp_i3 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 3;
      goto LAB_000b7e41;
    }
    tmp_i3 = Q_stricmp(local_2c,"brick");
    if (tmp_i3 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 4;
      goto LAB_000b7e41;
    }
    tmp_i3 = Q_stricmp(local_2c,&g_unk_0024da08);
    if (tmp_i3 == 0) {
      *(uint32_t *)(param_1 + 0x364) = 5;
      goto LAB_000b7e41;
    }
    tmp_i3 = Q_stricmp(local_2c,"fabric");
    if (tmp_i3 != 0) goto LAB_000b7e41;
  }
  *(uint32_t *)(param_1 + 0x364) = 0;
LAB_000b7e41:
  *(uint32_t *)(param_1 + 0xb0) = 0;
  *(uint32_t *)(param_1 + 0x39c) = 0xb;
  *(void **)(param_1 + 700) = props_locker_death;
  *(void **)(param_1 + 0x2b4) = props_locker_use;
  *(void **)(param_1 + 0x2b8) = props_locker_pain;
  *(uint32_t *)(param_1 + 900) = 1;
  *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - 8.0;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  *(uint32_t *)(param_1 + 0x318) = 0;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 4) = 0x11;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  if (*(int *)(param_1 + 0x2c8) == 0) {
    *(uint32_t *)(param_1 + 0x2c8) = 1;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_props_flamethrower(int param_1)
{
  float tmp_f1;
  double tmp_d2;
  char *local_10;
  uint32_t uStack_c;
  
  uStack_c = 0xb80d7;
  *(void **)(param_1 + 0x2a4) = props_flamethrower_init;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
  *(void **)(param_1 + 0x2b4) = props_flamethrower_use;
  G_SetOrigin(param_1,param_1 + 0x5c);
  if (*(float *)(param_1 + 800) == 0.0) {
    tmp_f1 = 1000.0;
  }
  else {
    tmp_f1 = *(float *)(param_1 + 800) * 1000.0;
  }
  *(float *)(param_1 + 800) = tmp_f1;
  G_SpawnStringExt("size",&g_unk_0024bfa6,&local_10,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_props.c",0xf1f);
  tmp_d2 = strtod(local_10,(char **)0x0);
  tmp_f1 = (float)tmp_d2;
  if (tmp_f1 == 0.0) {
    tmp_f1 = 1.0;
  }
  *(float *)(param_1 + 0x3fc) = tmp_f1;
  return;
}

void SP_script_mover(int param_1)
{
  uint tmp_u1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t local_480;
  uint32_t local_47c;
  uint32_t local_478;
  float local_474;
  float local_470;
  float local_46c;
  float local_468;
  float local_464;
  float local_460;
  uint8_t local_45c [64];
  uint8_t local_41c [1036];
  
  local_474 = 1.0;
  local_470 = 1.0;
  local_46c = 1.0;
  if (*(int *)(param_1 + 0x1b4) == 0) {
    G_Error("script_mover must have a \"model\"\n");
  }
  if (*(int *)(param_1 + 0x3ac) == 0) {
    G_Error("script_mover must have a \"scriptname\"\n");
  }
  *(void **)(param_1 + 0x2ac) = script_mover_blocked;
  *(uint32_t *)(param_1 + 0x224) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x228) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x22c) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x230) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x234) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x238) = *(uint32_t *)(param_1 + 100);
  trap_SetBrushModel(param_1,*(uint32_t *)(param_1 + 0x1b4));
  InitMover(param_1);
  *(uint32_t *)(param_1 + 0xf4) = 0;
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  *(uint32_t *)(param_1 + 0x2a8) = 0;
  *(uint32_t *)(param_1 + 0x11c) = 0;
  if ((tmp_u1 & 0x100) != 0) {
    *(uint32_t *)(param_1 + 0xf4) = 2;
  }
  if ((tmp_u1 & 8) != 0) {
    *(void **)(param_1 + 0x2b4) = script_mover_use;
  }
  *(uint *)(param_1 + 0x58) = tmp_u1 >> 4 & 1;
  if ((tmp_u1 & 0x20) == 0) {
    *(uint *)(param_1 + 0x108) = tmp_u1 >> 6 & 1;
  }
  else {
    *(uint32_t *)(param_1 + 0x108) = 2;
  }
  if ((tmp_u1 & 1) != 0) {
    *(void **)(param_1 + 0x2b4) = script_mover_use;
    trap_UnlinkEntity(param_1);
    return;
  }
  G_SetAngle(param_1,param_1 + 0x74);
  G_SpawnIntExt("health",&g_unk_0024bfa6,param_1 + 0x2c8,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script.c",0x49a);
  tmp_i2 = *(int *)(param_1 + 0x2c8);
  if (tmp_i2 == 0) {
    *(uint32_t *)(param_1 + 0x2e4) = 0;
  }
  else {
    *(int *)(param_1 + 0x2e4) = tmp_i2;
    *(int *)(param_1 + 0x10c) = tmp_i2;
    *(uint32_t *)(param_1 + 0x9c) = 0xff;
    *(uint32_t *)(param_1 + 0x2cc) = 1;
    tmp_i2 = G_SpawnStringExt("description",&g_unk_0026ea14,&local_478,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script.c",0x4a3);
    if (tmp_i2 != 0) {
      trap_GetConfigstring(0x1a,local_41c,0x400);
      tmp_u3 = va("%i",(param_1 + -0x93e4a0 >> 9) * -0x55555555);
      Info_SetValueForKey(local_41c,tmp_u3,local_478);
      trap_SetConfigstring(0x1a,local_41c);
    }
  }
  *(void **)(param_1 + 700) = script_mover_die;
  tmp_i2 = G_SpawnFloatExt("modelscale",&g_unk_00258b23,&local_474,
                          "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script.c",0x4af);
  if (tmp_i2 != 0) {
    local_470 = local_474;
    local_46c = local_474;
  }
  tmp_i2 = G_SpawnStringExt("model2",&g_unk_0026ea14,&local_480,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script.c",0x4b3);
  if (tmp_i2 != 0) {
    COM_StripExtension(local_480,local_45c);
    Q_strcat(local_45c,0x40,&g_unk_0024c792);
    tmp_u3 = trap_LoadTag(local_45c);
    *(uint32_t *)(param_1 + 0x498) = tmp_u3;
  }
  tmp_i2 = G_SpawnVectorExt("modelscale_vec","1 1 1",&local_468,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script.c",0x4bc);
  if (tmp_i2 != 0) {
    local_474 = local_468;
    local_470 = local_464;
    local_46c = local_460;
  }
  if (((local_474 != 1.0) || (local_470 != 1.0)) || (local_46c != 1.0)) {
    *(uint *)(param_1 + 0xf4) = *(uint *)(param_1 + 0xf4) | 1;
    *(float *)(param_1 + 0x80) = local_474;
    *(float *)(param_1 + 0x84) = local_470;
    *(float *)(param_1 + 0x88) = local_46c;
  }
  if ((*(byte *)(param_1 + 0x1a8) & 0x80) != 0) {
    *(uint32_t *)(param_1 + 0x304) = 0;
    *(uint *)(param_1 + 0xf4) = *(uint *)(param_1 + 0xf4) | 4;
    tmp_i2 = G_SpawnStringExt(&g_unk_002401a7,&g_unk_0026ea14,&local_480,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script.c",0x4ca);
    if ((tmp_i2 != 0) && (tmp_i2 = Q_stricmp(local_480,"browning"), tmp_i2 == 0)) {
      *(uint *)(param_1 + 0xf4) = *(uint *)(param_1 + 0xf4) | 8;
    }
    G_SpawnStringExt("tagent",&g_unk_0026ea14,&local_47c,
                     "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_script.c",0x4d0);
    Q_strncpyz(param_1 + 0x4c0,local_47c,0x10);
    *(uint32_t *)(param_1 + 0xe4) = 0xffffffff;
  }
  *(void **)(param_1 + 0x2a4) = script_mover_spawn;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

void SP_script_model_med(int param_1)
{
  uint32_t tmp_u1;
  
  if (*(int *)(param_1 + 0x1b4) == 0) {
    G_Error("script_model_med %s must have a \"model\"\n",*(uint32_t *)(param_1 + 0x3ac));
  }
  if (*(int *)(param_1 + 0x3ac) == 0) {
    G_Error("script_model_med must have a \"scriptname\"\n");
  }
  *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
  *(uint32_t *)(param_1 + 4) = 0;
  *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
  *(uint32_t *)(param_1 + 0x30) = 0;
  *(uint32_t *)(param_1 + 0x34) = 0;
  *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
  *(uint32_t *)(param_1 + 0x38) = 0;
  *(uint32_t *)(param_1 + 0x50) = 0;
  *(uint32_t *)(param_1 + 0x4c) = 0;
  *(uint32_t *)(param_1 + 0x48) = 0;
  if ((*(uint *)(param_1 + 0x1a8) & 1) == 0) {
    if ((*(uint *)(param_1 + 0x1a8) & 2) != 0) {
      *(uint32_t *)(param_1 + 0x1d4) = 1;
      *(uint32_t *)(param_1 + 0x14c) = 1;
    }
    tmp_u1 = G_ModelIndex(*(uint32_t *)(param_1 + 0x1b4));
    *(uint32_t *)(param_1 + 0xc) = 0;
    *(uint32_t *)(param_1 + 0xa4) = tmp_u1;
    *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0xb0) = 0;
    *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
    trap_LinkEntity(param_1);
    return;
  }
  *(void **)(param_1 + 0x2b4) = script_model_med_use;
  trap_UnlinkEntity(param_1);
  return;
}

void SP_script_camera(int param_1)
{
  if (*(int *)(param_1 + 0x3ac) == 0) {
    G_Error("%s must have a \"scriptname\"\n",*(uint32_t *)(param_1 + 0x1a4));
  }
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 1;
  *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
  *(uint32_t *)(param_1 + 4) = 0x1d;
  *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
  *(uint32_t *)(param_1 + 0x30) = 0;
  *(uint32_t *)(param_1 + 0x34) = 0;
  *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
  *(uint32_t *)(param_1 + 0x38) = 0;
  *(uint32_t *)(param_1 + 0x50) = 0;
  *(uint32_t *)(param_1 + 0x4c) = 0;
  *(uint32_t *)(param_1 + 0x48) = 0;
  *(uint32_t *)(param_1 + 0xb0) = 0;
  return;
}

void SP_script_multiplayer(int param_1)
{
  uint32_t tmp_u1;
  
  *(char **)(param_1 + 0x3ac) = "game_manager";
  tmp_u1 = BG_StringHashValue("game_manager");
  *(uint32_t *)(param_1 + 0x128) = 0x20;
  *(uint32_t *)(param_1 + 4) = 0x2e;
  *(uint32_t *)(param_1 + 0x5b0) = tmp_u1;
  if (g_unk_02a9969c != 0) {
    G_Error("^1ERROR: multiple script_multiplayers found^7\n");
  }
  tmp_u1 = GHIDRA_FIELD(team_maxLandmines, 12, 4);
  g_unk_02a9969c = param_1;
  *(uint32_t *)(param_1 + 0x8c) = GHIDRA_FIELD(team_maxLandmines, 12, 4);
  *(uint32_t *)(g_unk_02a9969c + 0x90) = tmp_u1;
  *(uint32_t *)(g_unk_02a9969c + 0xa4) = 0;
  *(uint32_t *)(g_unk_02a9969c + 0xa8) = 0;
  trap_LinkEntity(param_1);
  return;
}

void SP_func_fakebrush(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  long tmp_l3;
  int tmp_i4;
  char *tmp_pc5;
  char *tmp_pc6;
  bool tmp_b7;
  byte tmp_b8;
  
  tmp_b8 = 0;
  tmp_i1 = param_1 + 0x5c;
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x185);
  }
  if (0 < g_unk_00abef88) {
    tmp_i2 = 0;
    tmp_b7 = true;
    do {
      tmp_i4 = 7;
      tmp_pc5 = "origin";
      tmp_pc6 = (char *)(&g_unk_00abef8c)[tmp_i2 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b7 = *tmp_pc5 == *tmp_pc6;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) {
        __isoc99_sscanf((&g_unk_00abef90)[tmp_i2 * 2],"%f %f %f",tmp_i1,param_1 + 0x60,param_1 + 100);
        goto joined_r0x000dc2f0;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_b7 = tmp_i2 == g_unk_00abef88;
    } while (!tmp_b7);
  }
  __isoc99_sscanf("1 0 0","%f %f %f",tmp_i1,param_1 + 0x60,param_1 + 100);
  G_Error("\'func_fakebrush\' does not have an origin\n");
joined_r0x000dc2f0:
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x187);
  }
  if (0 < g_unk_00abef88) {
    tmp_i2 = 0;
    tmp_b7 = true;
    do {
      tmp_i4 = 9;
      tmp_pc5 = "contents";
      tmp_pc6 = (char *)(&g_unk_00abef8c)[tmp_i2 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b7 = *tmp_pc5 == *tmp_pc6;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) {
        tmp_l3 = strtol((char *)(&g_unk_00abef90)[tmp_i2 * 2],(char **)0x0,10);
        *(long *)(param_1 + 0x14c) = tmp_l3;
        goto LAB_000dc399;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_b7 = tmp_i2 == g_unk_00abef88;
    } while (!tmp_b7);
  }
  tmp_l3 = strtol("1",(char **)0x0,10);
  *(long *)(param_1 + 0x14c) = tmp_l3;
  G_Error("\'func_fakebrush\' does not have contents\n");
LAB_000dc399:
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x189);
  }
  if (0 < g_unk_00abef88) {
    tmp_i2 = 0;
    tmp_b7 = true;
    do {
      tmp_i4 = 5;
      tmp_pc5 = "mins";
      tmp_pc6 = (char *)(&g_unk_00abef8c)[tmp_i2 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b7 = *tmp_pc5 == *tmp_pc6;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) {
        __isoc99_sscanf((&g_unk_00abef90)[tmp_i2 * 2],"%f %f %f",param_1 + 0x134,param_1 + 0x138,
                        param_1 + 0x13c);
        goto LAB_000dc476;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_b7 = tmp_i2 == g_unk_00abef88;
    } while (!tmp_b7);
  }
  __isoc99_sscanf("0 0 0","%f %f %f",param_1 + 0x134,param_1 + 0x138,param_1 + 0x13c);
  G_Error("\'func_fakebrush\' does not have mins\n");
LAB_000dc476:
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x18b);
  }
  if (0 < g_unk_00abef88) {
    tmp_i2 = 0;
    tmp_b7 = true;
    do {
      tmp_i4 = 5;
      tmp_pc5 = "maxs";
      tmp_pc6 = (char *)(&g_unk_00abef8c)[tmp_i2 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b7 = *tmp_pc5 == *tmp_pc6;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) {
        __isoc99_sscanf((&g_unk_00abef90)[tmp_i2 * 2],"%f %f %f",param_1 + 0x140,param_1 + 0x144,
                        param_1 + 0x148);
        goto LAB_000dc556;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_b7 = tmp_i2 == g_unk_00abef88;
    } while (!tmp_b7);
  }
  __isoc99_sscanf("0 0 0","%f %f %f",param_1 + 0x140,param_1 + 0x144,param_1 + 0x148);
  G_Error("\'func_fakebrush\' does not have maxs\n");
LAB_000dc556:
  *(uint32_t *)(param_1 + 0x1d4) = *(uint32_t *)(param_1 + 0x14c);
  G_SetOrigin(param_1,tmp_i1);
  G_SetAngle(param_1,param_1 + 0x74);
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x10000;
  *(uint32_t *)(param_1 + 4) = 0;
  *(uint32_t *)(param_1 + 0x68) = *(uint32_t *)(param_1 + 0x134);
  *(uint32_t *)(param_1 + 0x6c) = *(uint32_t *)(param_1 + 0x138);
  *(uint32_t *)(param_1 + 0x70) = *(uint32_t *)(param_1 + 0x13c);
  *(uint32_t *)(param_1 + 0x80) = *(uint32_t *)(param_1 + 0x140);
  *(uint32_t *)(param_1 + 0x84) = *(uint32_t *)(param_1 + 0x144);
  *(uint32_t *)(param_1 + 0x88) = *(uint32_t *)(param_1 + 0x148);
  trap_LinkEntity(param_1);
  return;
}

uint32_t
G_SpawnStringExt(char *param_1,uint32_t param_2,uint32_t *param_3,uint32_t param_4,
                uint32_t param_5)

{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (g_unk_00abef84 == 0) {
    *param_3 = param_2;
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",param_4,param_5);
  }
  tmp_i1 = g_unk_00abef88;
  if (0 < g_unk_00abef88) {
    tmp_i3 = 0;
    do {
      tmp_i2 = strcmp(param_1,(char *)(&g_unk_00abef8c)[tmp_i3 * 2]);
      if (tmp_i2 == 0) {
        *param_3 = (&g_unk_00abef90)[tmp_i3 * 2];
        return 1;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != tmp_i1);
  }
  *param_3 = param_2;
  return 0;
}

int G_SpawnFloatExt(char *param_1,char *param_2,float *param_3,uint32_t param_4,uint32_t param_5
                   )

{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  double tmp_d4;
  
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",param_4,param_5);
  }
  tmp_i1 = g_unk_00abef88;
  tmp_i3 = 0;
  if (0 < g_unk_00abef88) {
    do {
      tmp_i2 = strcmp(param_1,(char *)(&g_unk_00abef8c)[tmp_i3 * 2]);
      if (tmp_i2 == 0) {
        param_2 = (char *)(&g_unk_00abef90)[tmp_i3 * 2];
        tmp_i3 = 1;
        goto LAB_000dc7ce;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != tmp_i1);
    tmp_i3 = 0;
  }
LAB_000dc7ce:
  tmp_d4 = strtod(param_2,(char **)0x0);
  *param_3 = (float)tmp_d4;
  return tmp_i3;
}

void SP_worldspawn(void)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  uint32_t tmp_u3;
  long tmp_l4;
  uint8_t *tmp_pu5;
  char *tmp_pc6;
  int tmp_i7;
  char *tmp_pc8;
  bool tmp_b9;
  byte tmp_b10;
  uint8_t *local_28;
  
  tmp_b10 = 0;
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x3c5);
  }
  if (0 < g_unk_00abef88) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 10;
      tmp_pc6 = "classname";
      tmp_pc8 = (char *)(&g_unk_00abef8c)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pu2 = (uint8_t *)(&g_unk_00abef90)[tmp_i1 * 2];
        goto LAB_000dd80a;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_00abef88;
    } while (!tmp_b9);
  }
  tmp_pu2 = &g_unk_0026ea14;
LAB_000dd80a:
  local_28 = &g_unk_0026ea14;
  tmp_i1 = Q_stricmp(tmp_pu2,"worldspawn");
  if (tmp_i1 != 0) {
    G_Error("SP_worldspawn: The first entity isn\'t \'worldspawn\'");
  }
  trap_SetConfigstring(10,"Enemy Territory");
  tmp_u3 = va("%i",g_unk_00abe918);
  trap_SetConfigstring(0xb,tmp_u3);
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x3cf);
  }
  if (0 < g_unk_00abef88) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 6;
      tmp_pc6 = "music";
      tmp_pc8 = (char *)(&g_unk_00abef8c)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        local_28 = (uint8_t *)(&g_unk_00abef90)[tmp_i1 * 2];
        break;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_00abef88;
    } while (!tmp_b9);
  }
  trap_SetConfigstring(2,local_28);
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x3d5);
  }
  if (0 < g_unk_00abef88) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 9;
      tmp_pc6 = "cclayers";
      tmp_pc8 = (char *)(&g_unk_00abef8c)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pc6 = (char *)(&g_unk_00abef90)[tmp_i1 * 2];
        goto LAB_000dd92e;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_00abef88;
    } while (!tmp_b9);
  }
  tmp_pc6 = "0";
LAB_000dd92e:
  tmp_l4 = strtol(tmp_pc6,(char **)0x0,10);
  if (tmp_l4 != 0) {
    g_unk_02a99a64 = 1;
  }
  g_unk_02a99b8c = 0;
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x3da);
  }
  if (0 < g_unk_00abef88) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 0xe;
      tmp_pc6 = "mapcoordsmins";
      tmp_pc8 = (char *)(&g_unk_00abef8c)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        __isoc99_sscanf((&g_unk_00abef90)[tmp_i1 * 2],"%f %f",&g_unk_02a99b94,&g_unk_02a99b98);
        if (g_unk_00abef84 == 0) {
          G_Error("G_SpawnString() called while not spawning, file %s, line %i",
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x3db);
        }
        if (g_unk_00abef88 < 1) goto LAB_000ddd60;
        tmp_i1 = 0;
        tmp_b9 = true;
        goto LAB_000dda1b;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_00abef88;
    } while (!tmp_b9);
  }
  __isoc99_sscanf("-128 128","%f %f",&g_unk_02a99b94,&g_unk_02a99b98);
  goto LAB_000dda9c;
  while( true ) {
    tmp_i1 = tmp_i1 + 1;
    tmp_b9 = false;
    if (tmp_i1 == g_unk_00abef88) break;
LAB_000dda1b:
    tmp_i7 = 0xe;
    tmp_pc6 = "mapcoordsmaxs";
    tmp_pc8 = (char *)(&g_unk_00abef8c)[tmp_i1 * 2];
    do {
      if (tmp_i7 == 0) break;
      tmp_i7 = tmp_i7 + -1;
      tmp_b9 = *tmp_pc6 == *tmp_pc8;
      tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
      tmp_pc8 = tmp_pc8 + (uint)tmp_b10 * -2 + 1;
    } while (tmp_b9);
    if (tmp_b9) {
      __isoc99_sscanf((&g_unk_00abef90)[tmp_i1 * 2],"%f %f",&g_unk_02a99b9c,&g_unk_02a99ba0);
      g_unk_02a99b8c = 1;
      goto LAB_000dda9c;
    }
  }
LAB_000ddd60:
  __isoc99_sscanf("128 -128","%f %f",&g_unk_02a99b9c,&g_unk_02a99ba0);
LAB_000dda9c:
  BG_InitLocations(&g_unk_02a99b94,&g_unk_02a99b9c);
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x3e2);
  }
  if (0 < g_unk_00abef88) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 8;
      tmp_pc6 = "gravity";
      tmp_pc8 = (char *)(&g_unk_00abef8c)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pu5 = (uint8_t *)(&g_unk_00abef90)[tmp_i1 * 2];
        goto LAB_000ddb0e;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_00abef88;
    } while (!tmp_b9);
  }
  tmp_pu5 = &g_unk_0024a8b7;
LAB_000ddb0e:
  trap_Cvar_Set("g_gravity",tmp_pu5);
  if (g_unk_00abef84 == 0) {
    G_Error("G_SpawnString() called while not spawning, file %s, line %i",
            "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_spawn.c",0x3e5);
  }
  if (0 < g_unk_00abef88) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 0xb;
      tmp_pc6 = "spawnflags";
      tmp_pc8 = (char *)(&g_unk_00abef8c)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pc6 = (char *)(&g_unk_00abef90)[tmp_i1 * 2];
        goto LAB_000ddb7e;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_00abef88;
    } while (!tmp_b9);
  }
  tmp_pc6 = "0";
LAB_000ddb7e:
  GHIDRA_FIELD(g_entities, 1570184, 4) = strtol(tmp_pc6,(char **)0x0,10);
  GHIDRA_FIELD(g_entities, 1569792, 4) = 0x3fe;
  GHIDRA_FIELD(g_entities, 1570212, 4) = s_worldspawn_0024df2e;
  GHIDRA_FIELD(g_entities, 1570216, 4) = GHIDRA_FIELD(g_entities, 1570184, 4);
  trap_SetConfigstring(5,&g_unk_0026ea14);
  if (GHIDRA_FIELD(g_restarted, 12, 4) != 0) {
    trap_Cvar_Set("g_restarted",&g_unk_0024bfa6);
    g_unk_00abe8ac = 0;
  }
  if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
    G_initMatch();
  }
  return;
}

void target_rumble_use(int param_1)
{
  uint tmp_u1;
  
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u1 & 1) == 0) {
    *(uint *)(param_1 + 0x1a8) = tmp_u1 | 1;
    *(uint32_t *)(param_1 + 0x2a4) = 0;
    *(uint32_t *)(param_1 + 0x2e4) = 0;
    return;
  }
  *(uint *)(param_1 + 0x1a8) = tmp_u1 & 0xfffffffe;
  *(void **)(param_1 + 0x2a4) = target_rumble_think;
  *(uint32_t *)(param_1 + 0x2e4) = 0;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
  return;
}

void Use_Target_Lock(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = 0;
  while( true ) {
    tmp_i1 = G_FindByTargetnameFast
                      (tmp_i1,*(uint32_t *)(param_1 + 0x254),*(uint32_t *)(param_1 + 0x5bc));
    if (tmp_i1 == 0) break;
    *(uint32_t *)(tmp_i1 + 0x364) = *(uint32_t *)(param_1 + 0x364);
  }
  return;
}

void Use_target_remove_powerups(uint32_t param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  uint tmp_u2;
  uint tmp_u3;
  uint16_t *tmp_pu4;
  uint32_t *tmp_pu5;
  bool tmp_b6;
  
  tmp_i1 = *(int *)(param_3 + 400);
  if (tmp_i1 != 0) {
    if ((*(int *)(tmp_i1 + 0x164) != 0) || (*(int *)(tmp_i1 + 0x168) != 0)) {
      Team_ReturnFlag(g_entities + *(int *)(tmp_i1 + 0x5294) * 0x600,param_3);
      tmp_i1 = *(int *)(param_3 + 400);
    }
    tmp_pu4 = (uint16_t *)(tmp_i1 + 0x150);
    tmp_u3 = 0x40;
    tmp_b6 = ((uint)tmp_pu4 & 1) != 0;
    if (tmp_b6) {
      *(uint8_t *)(tmp_i1 + 0x150) = 0;
      tmp_pu4 = (uint16_t *)(tmp_i1 + 0x151);
      tmp_u3 = 0x3f;
    }
    if (((uint)tmp_pu4 & 2) != 0) {
      *tmp_pu4 = 0;
      tmp_u3 = tmp_u3 - 2;
      tmp_pu4 = tmp_pu4 + 1;
    }
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)tmp_pu4 + tmp_u2) = 0;
      *(uint32_t *)((int)tmp_pu4 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < (tmp_u3 & 0xfffffff8));
    tmp_pu5 = (uint32_t *)((int)tmp_pu4 + tmp_u2);
    if ((tmp_u3 & 4) != 0) {
      *tmp_pu5 = 0;
      tmp_pu5 = tmp_pu5 + 1;
    }
    if ((tmp_u3 & 2) != 0) {
      *(uint16_t *)tmp_pu5 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
    }
    if (tmp_b6) {
      *(uint8_t *)tmp_pu5 = 0;
    }
  }
  return;
}

void Think_Target_Delay(int param_1)
{
  G_UseTargets(param_1,*(uint32_t *)(param_1 + 0x2f0));
  return;
}

void Use_Target_Counter(int param_1,uint32_t param_2)
{
  int tmp_i1;
  
  if ((-1 < *(int *)(param_1 + 0x2e4)) &&
     (tmp_i1 = *(int *)(param_1 + 0x2e4) + -1, *(int *)(param_1 + 0x2e4) = tmp_i1, tmp_i1 == 0)) {
    G_UseTargets(param_1,param_2);
    return;
  }
  return;
}

void Use_Target_Alarm(uint32_t param_1,uint32_t param_2)
{
  G_UseTargets(param_1,param_2);
  return;
}

void Use_Target_Delay(int param_1,uint32_t param_2,uint32_t param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint tmp_u5;
  
  tmp_f4 = (float)g_unk_00abe908;
  tmp_f1 = *(float *)(param_1 + 0x30c);
  tmp_f2 = *(float *)(param_1 + 0x310);
  tmp_u5 = rand();
  tmp_f3 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
  *(int *)(param_1 + 0x29c) = (int)ROUND(((tmp_f3 + tmp_f3) * tmp_f2 + tmp_f1) * 1000.0 + tmp_f4);
  *(void **)(param_1 + 0x2a4) = Think_Target_Delay;
  *(uint32_t *)(param_1 + 0x2f0) = param_3;
  return;
}

void Use_Target_Score(int param_1,uint32_t param_2,uint32_t param_3)
{
  AddScore(param_3,*(uint32_t *)(param_1 + 0x2e4));
  return;
}

void Use_Target_Print(int param_1,uint32_t param_2,int param_3)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  
  tmp_u2 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u2 & 4) != 0) {
    if (param_3 == 0) {
      G_Error("G_scripting: call to client only target_print with no activator\n");
    }
    if (*(int *)(param_3 + 400) != 0) {
      tmp_u1 = va("cp \"%s\"",*(uint32_t *)(param_1 + 0x248));
      trap_SendServerCommand((param_3 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
      return;
    }
    tmp_u2 = *(uint *)(param_1 + 0x1a8);
  }
  if ((tmp_u2 & 3) == 0) {
    tmp_u1 = va("cp \"%s\"",*(uint32_t *)(param_1 + 0x248));
    trap_SendServerCommand(0xffffffff,tmp_u1);
    return;
  }
  if ((tmp_u2 & 1) != 0) {
    tmp_u1 = va("cp \"%s\"",*(uint32_t *)(param_1 + 0x248));
    G_TeamCommand(1,tmp_u1);
    tmp_u2 = *(uint *)(param_1 + 0x1a8);
  }
  if ((tmp_u2 & 2) == 0) {
    return;
  }
  tmp_u1 = va("cp \"%s\"",*(uint32_t *)(param_1 + 0x248));
  G_TeamCommand(2,tmp_u1);
  return;
}

void misc_beam_think(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_i5 = *(int *)(param_1 + 0x2ec);
  if (tmp_i5 != 0) {
    if (param_1 == tmp_i5) {
      *(uint32_t *)(param_1 + 0x30) = 0;
      *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x5c);
      *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x60);
      *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 100);
    }
    else {
      *(uint32_t *)(param_1 + 0x30) = *(uint32_t *)(tmp_i5 + 0xc);
      *(uint32_t *)(param_1 + 0x34) = *(uint32_t *)(tmp_i5 + 0x10);
      *(uint32_t *)(param_1 + 0x38) = *(uint32_t *)(tmp_i5 + 0x14);
      *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(tmp_i5 + 0x18);
      *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(tmp_i5 + 0x1c);
      *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(tmp_i5 + 0x20);
      *(uint32_t *)(param_1 + 0x48) = *(uint32_t *)(tmp_i5 + 0x24);
      *(uint32_t *)(param_1 + 0x4c) = *(uint32_t *)(tmp_i5 + 0x28);
      *(uint32_t *)(param_1 + 0x50) = *(uint32_t *)(tmp_i5 + 0x2c);
      *(uint32_t *)(param_1 + 0x110) = *(uint32_t *)(tmp_i5 + 0x110);
    }
  }
  tmp_i5 = *(int *)(param_1 + 0x264);
  tmp_i6 = *(int *)(tmp_i5 + 0xc);
  *(int *)(param_1 + 0xc) = tmp_i6;
  *(uint32_t *)(param_1 + 0x10) = *(uint32_t *)(tmp_i5 + 0x10);
  *(uint32_t *)(param_1 + 0x14) = *(uint32_t *)(tmp_i5 + 0x14);
  tmp_u1 = *(uint32_t *)(tmp_i5 + 0x18);
  *(uint32_t *)(param_1 + 0x18) = tmp_u1;
  tmp_u2 = *(uint32_t *)(tmp_i5 + 0x1c);
  *(uint32_t *)(param_1 + 0x1c) = tmp_u2;
  tmp_f3 = *(float *)(tmp_i5 + 0x20);
  *(float *)(param_1 + 0x20) = tmp_f3;
  *(uint32_t *)(param_1 + 0x24) = *(uint32_t *)(tmp_i5 + 0x24);
  *(uint32_t *)(param_1 + 0x28) = *(uint32_t *)(tmp_i5 + 0x28);
  *(uint32_t *)(param_1 + 0x2c) = *(uint32_t *)(tmp_i5 + 0x2c);
  *(uint32_t *)(param_1 + 0x10c) = *(uint32_t *)(tmp_i5 + 0x110);
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  if (((tmp_i6 != 0) || (*(int *)(param_1 + 0x30) != 0)) || (*(float *)(param_1 + 0x3fc) == 0.0)) {
    *(uint32_t *)(param_1 + 0x134) = tmp_u1;
    *(uint32_t *)(param_1 + 0x138) = tmp_u2;
    *(float *)(param_1 + 0x13c) = tmp_f3;
    *(uint32_t *)(param_1 + 0x3fc) = 0x3f800000;
    *(uint32_t *)(param_1 + 0x140) = *(uint32_t *)(param_1 + 0x3c);
    *(uint32_t *)(param_1 + 0x14c) = 1;
    *(uint32_t *)(param_1 + 0x144) = *(uint32_t *)(param_1 + 0x40);
    tmp_f4 = *(float *)(param_1 + 0x44);
    *(float *)(param_1 + 0x148) = tmp_f4;
    if (tmp_f4 < tmp_f3) {
      *(float *)(param_1 + 0x13c) = tmp_f4;
      *(float *)(param_1 + 0x148) = tmp_f3;
    }
    tmp_f3 = *(float *)(param_1 + 0x138);
    if (*(float *)(param_1 + 0x144) < tmp_f3) {
      *(float *)(param_1 + 0x138) = *(float *)(param_1 + 0x144);
      *(float *)(param_1 + 0x144) = tmp_f3;
    }
    tmp_f3 = *(float *)(param_1 + 0x134);
    if (*(float *)(param_1 + 0x140) < tmp_f3) {
      *(float *)(param_1 + 0x134) = *(float *)(param_1 + 0x140);
      *(float *)(param_1 + 0x140) = tmp_f3;
    }
    tmp_f3 = *(float *)(param_1 + 0x5c);
    *(float *)(param_1 + 0x168) = tmp_f3;
    tmp_f4 = *(float *)(param_1 + 0x60);
    *(float *)(param_1 + 0x16c) = tmp_f4;
    *(float *)(param_1 + 0x170) = *(float *)(param_1 + 100);
    *(float *)(param_1 + 0x134) = (*(float *)(param_1 + 0x134) - 4.0) - tmp_f3;
    *(float *)(param_1 + 0x138) = (*(float *)(param_1 + 0x138) - 4.0) - tmp_f4;
    *(float *)(param_1 + 0x13c) = (*(float *)(param_1 + 0x13c) - 4.0) - *(float *)(param_1 + 100);
    *(float *)(param_1 + 0x140) = (*(float *)(param_1 + 0x140) + 4.0) - tmp_f3;
    *(float *)(param_1 + 0x144) = (*(float *)(param_1 + 0x144) + 4.0) - tmp_f4;
    *(float *)(param_1 + 0x148) = (*(float *)(param_1 + 0x148) + 4.0) - *(float *)(param_1 + 100);
    trap_LinkEntity(param_1);
  }
  return;
}

void misc_beam_start(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  
  *(uint32_t *)(param_1 + 4) = 0x23;
  if (*(int *)(param_1 + 0x254) == 0) {
    tmp_u2 = vtos(param_1 + 0x5c);
    G_Printf("%s at %s: with no target\n",*(uint32_t *)(param_1 + 0x1a4),tmp_u2);
    G_FreeEntity(param_1);
    return;
  }
  tmp_i1 = G_FindByTargetnameFast(0,*(int *)(param_1 + 0x254),*(uint32_t *)(param_1 + 0x5bc));
  if (tmp_i1 == 0) {
    tmp_u2 = *(uint32_t *)(param_1 + 0x254);
    tmp_u3 = vtos(param_1 + 0x5c);
    G_Printf("%s at %s: %s is a bad target\n",*(uint32_t *)(param_1 + 0x1a4),tmp_u3,tmp_u2);
    G_FreeEntity(param_1);
  }
  else {
    *(int *)(param_1 + 0x264) = tmp_i1;
    if (*(int *)(param_1 + 0x248) == 0) {
      *(int *)(param_1 + 0x2ec) = param_1;
    }
    else {
      tmp_u2 = BG_StringHashValue(*(int *)(param_1 + 0x248));
      tmp_i1 = G_FindByTargetnameFast(0,*(uint32_t *)(param_1 + 0x248),tmp_u2);
      if (tmp_i1 == 0) {
        tmp_u2 = *(uint32_t *)(param_1 + 0x248);
        tmp_u3 = vtos(param_1 + 0x5c);
        G_Printf("%s at %s: %s is a bad target2\n",*(uint32_t *)(param_1 + 0x1a4),tmp_u3,tmp_u2);
        G_FreeEntity(param_1);
        return;
      }
      *(int *)(param_1 + 0x2ec) = tmp_i1;
    }
    *(void **)(param_1 + 0x2a4) = misc_beam_think;
    *(uint32_t *)(param_1 + 0x3fc) = 0;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  }
  return;
}

void target_laser_think(uint32_t *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  int tmp_i7;
  float local_50;
  float local_4c;
  float local_48;
  uint8_t local_44 [12];
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  int local_10;
  
  tmp_i7 = param_1[0xbb];
  if (tmp_i7 != 0) {
    tmp_f1 = *(float *)(tmp_i7 + 0x138);
    tmp_f2 = *(float *)(tmp_i7 + 0x60);
    tmp_f3 = *(float *)(tmp_i7 + 0x144);
    tmp_f4 = *(float *)(tmp_i7 + 0x13c);
    tmp_f5 = *(float *)(tmp_i7 + 100);
    tmp_f6 = *(float *)(tmp_i7 + 0x148);
    param_1[0x9c] =
         (*(float *)(tmp_i7 + 0x140) * 0.5 +
         *(float *)(tmp_i7 + 0x134) * 0.5 + *(float *)(tmp_i7 + 0x5c)) - (float)param_1[0x17];
    param_1[0x9d] = (tmp_f3 * 0.5 + tmp_f1 * 0.5 + tmp_f2) - (float)param_1[0x18];
    param_1[0x9e] = (tmp_f6 * 0.5 + tmp_f4 * 0.5 + tmp_f5) - (float)param_1[0x19];
    VectorNormalize(param_1 + 0x9c);
  }
  local_50 = (float)param_1[0x9c] * 2048.0 + (float)param_1[0x17];
  local_4c = (float)param_1[0x9d] * 2048.0 + (float)param_1[0x18];
  local_48 = (float)param_1[0x9e] * 2048.0 + (float)param_1[0x19];
  trap_Trace(local_44,param_1 + 0x17,0,0,&local_50,*param_1,0x6000001);
  if (local_10 != 0) {
    G_Damage(g_entities + local_10 * 0x600,param_1,param_1[0xbc],param_1 + 0x9c,&local_38,
             param_1[0xb4],4,0x21);
  }
  param_1[0x1a] = local_38;
  param_1[0x1b] = local_34;
  param_1[0x1c] = local_30;
  trap_LinkEntity(param_1);
  param_1[0xa7] = g_unk_00abe908 + 100;
  return;
}

void target_teleporter_use(int param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  
  if (*(int *)(param_3 + 400) != 0) {
    tmp_i1 = G_PickTarget(*(uint32_t *)(param_1 + 0x254));
    if (tmp_i1 == 0) {
      G_Printf("Couldn\'t find teleporter destination\n");
    }
    else {
      TeleportPlayer(param_3,tmp_i1 + 0x5c,tmp_i1 + 0x74);
    }
  }
  return;
}

void target_relay_use(int param_1,uint32_t param_2,int param_3)
{
  uint tmp_u1;
  int tmp_i2;
  
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  if (param_3 != 0) {
    if ((tmp_u1 & 1) == 0) {
      if ((((tmp_u1 & 2) != 0) && (*(int *)(param_3 + 400) != 0)) &&
         (*(int *)(*(int *)(param_3 + 400) + 3000) != 2)) {
        return;
      }
    }
    else if (*(int *)(param_3 + 400) != 0) {
      if (*(int *)(*(int *)(param_3 + 400) + 3000) != 1) {
        return;
      }
      if ((tmp_u1 & 2) != 0) {
        return;
      }
    }
  }
  if ((tmp_u1 & 4) == 0) {
    if ((param_3 == 0) || (*(int *)(param_1 + 0x364) != -1)) {
      G_UseTargets(param_1,param_3);
    }
    else if (*(int *)(param_1 + 0x1e8) != 0) {
      G_Sound(param_1,*(int *)(param_1 + 0x1e8));
    }
  }
  else {
    tmp_i2 = G_PickTarget(*(uint32_t *)(param_1 + 0x254));
    if ((tmp_i2 != 0) && (*(int *)(tmp_i2 + 0x2b4) != 0)) {
      G_UseEntity(tmp_i2,param_1,param_3);
      return;
    }
  }
  return;
}

void Use_target_fog(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = va("%f %f %f %f %f %f %i",0x3ff0000000000000,(double)*(int *)(param_1 + 0xf4),
             0x3ff0000000000000,(double)*(float *)(param_1 + 0x34c),
             (double)*(float *)(param_1 + 0x350),(double)*(float *)(param_1 + 0x354),
             *(uint32_t *)(param_1 + 0x54));
  trap_SetConfigstring(0x12,tmp_u1);
  return;
}

void target_script_trigger_use(int param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  if (*(int *)(param_1 + 0x340) != 0) {
    tmp_u1 = BG_StringHashValue(*(int *)(param_1 + 0x340));
    tmp_i2 = nitrox_FindByScriptNameHash(0,tmp_u1);
    if (tmp_i2 != 0) {
      G_Script_ScriptEvent(tmp_i2,"trigger",*(uint32_t *)(param_1 + 0x254));
      goto LAB_000e8186;
    }
  }
  if (*(int *)(param_1 + 0x3ac) != 0) {
    G_Script_ScriptEvent(param_1,"trigger",*(uint32_t *)(param_1 + 0x254));
  }
LAB_000e8186:
  G_UseTargets(param_1,param_2);
  return;
}

void target_rumble_think(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  if (*(int *)(param_1 + 0x2e4) == 0) {
    *(int *)(param_1 + 0x24c) = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x2e4) = 1;
    if (*(int *)(param_1 + 0x1e8) != 0) {
      G_AddEvent(param_1,0x28,*(int *)(param_1 + 0x1e8));
    }
  }
  else {
    *(uint32_t *)(param_1 + 0xa0) = *(uint32_t *)(param_1 + 0x1f8);
  }
  tmp_i4 = *(int *)(param_1 + 0x37c);
  tmp_f1 = *(float *)(param_1 + 0x318);
  tmp_f2 = *(float *)(param_1 + 0x310);
  if (tmp_i4 == 0) {
    tmp_f3 = 1.0;
  }
  else {
    tmp_i5 = *(int *)(param_1 + 0x24c);
    if (g_unk_00abe908 < tmp_i4 + tmp_i5) {
      tmp_f3 = (float)(g_unk_00abe908 - tmp_i5) / (float)tmp_i4;
    }
    else {
      tmp_i6 = g_unk_00abe908;
      if (tmp_i4 + *(int *)(param_1 + 0x380) + tmp_i5 <= g_unk_00abe908) goto LAB_000e82e0;
      tmp_f3 = (float)((*(int *)(param_1 + 0x380) + tmp_i4 + tmp_i5) - tmp_i5) /
              (float)(g_unk_00abe908 - tmp_i5);
    }
  }
  tmp_i4 = nitrox_TempEventFromQueue(param_1 + 0x168,0x51);
  tmp_i6 = g_unk_00abe908;
  *(float *)(tmp_i4 + 0x74) = tmp_f1 * tmp_f3;
  *(float *)(tmp_i4 + 0x78) = tmp_f3 * tmp_f2;
  tmp_i5 = *(int *)(param_1 + 0x24c);
LAB_000e82e0:
  if ((float)tmp_i6 <= (float)tmp_i5 + *(float *)(param_1 + 800)) {
    *(int *)(param_1 + 0x29c) = tmp_i6 + 0x32;
  }
  else {
    if (*(int *)(param_1 + 500) != 0) {
      G_AddEvent(param_1,0x28,*(int *)(param_1 + 500));
      *(uint32_t *)(param_1 + 0xa0) = 0;
    }
    *(uint32_t *)(param_1 + 0x29c) = 0;
  }
  return;
}

void Use_Target_Give(int param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  uint tmp_u2;
  int tmp_i3;
  uint32_t local_54 [17];
  
  if ((*(int *)(param_3 + 400) != 0) && (tmp_i1 = *(int *)(param_1 + 0x254), tmp_i1 != 0)) {
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)local_54 + tmp_u2) = 0;
      *(uint32_t *)((int)local_54 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < 0x38);
    tmp_i3 = 0;
    while( true ) {
      tmp_i3 = G_FindByTargetnameFast(tmp_i3,tmp_i1,*(uint32_t *)(param_1 + 0x5bc));
      if (tmp_i3 == 0) break;
      if (*(int *)(tmp_i3 + 0x33c) != 0) {
        Touch_Item(tmp_i3,param_3,local_54);
        *(uint32_t *)(tmp_i3 + 0x29c) = 0;
        trap_UnlinkEntity(tmp_i3);
      }
      tmp_i1 = *(int *)(param_1 + 0x254);
    }
  }
  return;
}

void Use_Target_Speaker(int param_1,uint32_t param_2,uint32_t param_3)
{
  if ((*(uint *)(param_1 + 0x1a8) & 3) == 0) {
    if ((*(uint *)(param_1 + 0x1a8) & 8) == 0) {
      G_AddEvent(param_1,0x29,*(uint32_t *)(param_1 + 0x308));
      return;
    }
    G_AddEvent(param_3,0x29,*(uint32_t *)(param_1 + 0x308));
    return;
  }
  if (*(int *)(param_1 + 0xa0) != 0) {
    *(uint32_t *)(param_1 + 0xa0) = 0;
    return;
  }
  *(uint32_t *)(param_1 + 0xa0) = *(uint32_t *)(param_1 + 0x308);
  return;
}

void target_speaker_multiple(int param_1)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  
  tmp_i1 = *(int *)(param_1 + 0x254);
  if (tmp_i1 == 0) {
    tmp_u3 = vtos(param_1 + 0x5c);
    G_Error("target_speaker missing target at pos %s",tmp_u3);
    tmp_i1 = *(int *)(param_1 + 0x254);
  }
  tmp_pu2 = (uint32_t *)G_FindByTargetnameFast(0,tmp_i1,*(uint32_t *)(param_1 + 0x5bc));
  if (tmp_pu2 != (uint32_t *)0x0) {
    *(uint32_t *)(param_1 + 0x8c) = *tmp_pu2;
    return;
  }
  tmp_u3 = vtos(param_1 + 0x5c);
  G_Error("target_speaker cant find vis_dummy_multiple %s",tmp_u3);
  return;
}

void target_laser_use(uint32_t *param_1,uint32_t param_2,int param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  int tmp_i7;
  float local_50;
  float local_4c;
  float local_48;
  uint8_t local_44 [12];
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  int local_10;
  
  param_1[0xbc] = param_3;
  if ((int)param_1[0xa7] < 1) {
    if (param_3 == 0) {
      param_1[0xbc] = param_1;
    }
    tmp_i7 = param_1[0xbb];
    if (tmp_i7 != 0) {
      tmp_f1 = *(float *)(tmp_i7 + 0x138);
      tmp_f2 = *(float *)(tmp_i7 + 0x60);
      tmp_f3 = *(float *)(tmp_i7 + 0x144);
      tmp_f4 = *(float *)(tmp_i7 + 0x13c);
      tmp_f5 = *(float *)(tmp_i7 + 100);
      tmp_f6 = *(float *)(tmp_i7 + 0x148);
      param_1[0x9c] =
           (*(float *)(tmp_i7 + 0x140) * 0.5 +
           *(float *)(tmp_i7 + 0x134) * 0.5 + *(float *)(tmp_i7 + 0x5c)) - (float)param_1[0x17];
      param_1[0x9d] = (tmp_f3 * 0.5 + tmp_f1 * 0.5 + tmp_f2) - (float)param_1[0x18];
      param_1[0x9e] = (tmp_f6 * 0.5 + tmp_f4 * 0.5 + tmp_f5) - (float)param_1[0x19];
      VectorNormalize(param_1 + 0x9c);
    }
    local_50 = (float)param_1[0x9c] * 2048.0 + (float)param_1[0x17];
    local_4c = (float)param_1[0x9d] * 2048.0 + (float)param_1[0x18];
    local_48 = (float)param_1[0x9e] * 2048.0 + (float)param_1[0x19];
    trap_Trace(local_44,param_1 + 0x17,0,0,&local_50,*param_1,0x6000001);
    if (local_10 != 0) {
      G_Damage(g_entities + local_10 * 0x600,param_1,param_1[0xbc],param_1 + 0x9c,&local_38,
               param_1[0xb4],4,0x21);
    }
    param_1[0x1a] = local_38;
    param_1[0x1b] = local_34;
    param_1[0x1c] = local_30;
    trap_LinkEntity(param_1);
    param_1[0xa7] = g_unk_00abe908 + 100;
    return;
  }
  trap_UnlinkEntity(param_1);
  param_1[0xa7] = 0;
  return;
}

void target_laser_start(uint32_t *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  uint32_t tmp_u7;
  int tmp_i8;
  uint32_t tmp_u9;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [12];
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  int local_20;
  
  param_1[1] = 5;
  if (param_1[0x95] == 0) {
    G_SetMovedir(param_1 + 0x1d,param_1 + 0x9c);
  }
  else {
    tmp_i8 = G_FindByTargetnameFast(0,param_1[0x95],param_1[0x16f]);
    if (tmp_i8 == 0) {
      tmp_u7 = param_1[0x95];
      tmp_u9 = vtos(param_1 + 0x17);
      G_Printf("%s at %s: %s is a bad target\n",param_1[0x69],tmp_u9,tmp_u7);
    }
    param_1[0xbb] = tmp_i8;
  }
  param_1[0xad] = target_laser_use;
  param_1[0xa9] = target_laser_think;
  if (param_1[0xb4] == 0) {
    param_1[0xb4] = 1;
  }
  if ((*(byte *)(param_1 + 0x6a) & 1) != 0) {
    if (param_1[0xbc] == 0) {
      param_1[0xbc] = param_1;
    }
    tmp_i8 = param_1[0xbb];
    if (tmp_i8 != 0) {
      tmp_f1 = *(float *)(tmp_i8 + 0x138);
      tmp_f2 = *(float *)(tmp_i8 + 0x60);
      tmp_f3 = *(float *)(tmp_i8 + 0x144);
      tmp_f4 = *(float *)(tmp_i8 + 0x13c);
      tmp_f5 = *(float *)(tmp_i8 + 100);
      tmp_f6 = *(float *)(tmp_i8 + 0x148);
      param_1[0x9c] =
           (*(float *)(tmp_i8 + 0x140) * 0.5 +
           *(float *)(tmp_i8 + 0x134) * 0.5 + *(float *)(tmp_i8 + 0x5c)) - (float)param_1[0x17];
      param_1[0x9d] = (tmp_f3 * 0.5 + tmp_f1 * 0.5 + tmp_f2) - (float)param_1[0x18];
      param_1[0x9e] = (tmp_f6 * 0.5 + tmp_f4 * 0.5 + tmp_f5) - (float)param_1[0x19];
      VectorNormalize(param_1 + 0x9c);
    }
    local_60 = (float)param_1[0x9c] * 2048.0 + (float)param_1[0x17];
    local_5c = (float)param_1[0x9d] * 2048.0 + (float)param_1[0x18];
    local_58 = (float)param_1[0x9e] * 2048.0 + (float)param_1[0x19];
    trap_Trace(local_54,param_1 + 0x17,0,0,&local_60,*param_1,0x6000001);
    if (local_20 != 0) {
      G_Damage(g_entities + local_20 * 0x600,param_1,param_1[0xbc],param_1 + 0x9c,&local_48,
               param_1[0xb4],4,0x21);
    }
    param_1[0x1a] = local_48;
    param_1[0x1b] = local_44;
    param_1[0x1c] = local_40;
    trap_LinkEntity(param_1);
    param_1[0xa7] = g_unk_00abe908 + 100;
    return;
  }
  trap_UnlinkEntity(param_1);
  param_1[0xa7] = 0;
  return;
}

void SP_target_give(int param_1)
{
  *(void **)(param_1 + 0x2b4) = Use_Target_Give;
  return;
}

void SP_target_remove_powerups(int param_1)
{
  *(void **)(param_1 + 0x2b4) = Use_target_remove_powerups;
  return;
}

void SP_target_delay(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = G_SpawnFloatExt("delay",&g_unk_0024bfa6,param_1 + 0x30c,
                          "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x57);
  if (tmp_i1 == 0) {
    G_SpawnFloatExt(&g_unk_0023f11d,&g_unk_00258b23,param_1 + 0x30c,
                    "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x58);
  }
  if (*(float *)(param_1 + 0x30c) == 0.0) {
    *(uint32_t *)(param_1 + 0x30c) = 0x3f800000;
  }
  *(void **)(param_1 + 0x2b4) = Use_Target_Delay;
  return;
}

void SP_target_score(int param_1)
{
  if (*(int *)(param_1 + 0x2e4) == 0) {
    *(uint32_t *)(param_1 + 0x2e4) = 1;
  }
  *(void **)(param_1 + 0x2b4) = Use_Target_Score;
  return;
}

void SP_target_print(int param_1)
{
  *(void **)(param_1 + 0x2b4) = Use_Target_Print;
  return;
}

void SP_target_speaker(int param_1)
{
  char tmp_c1;
  uint tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  char *local_60;
  uint8_t local_5c [76];
  
  G_SpawnFloatExt(&g_unk_0023f11d,&g_unk_0024bfa6,param_1 + 0x30c,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0xd4);
  G_SpawnFloatExt("random",&g_unk_0024bfa6,param_1 + 0x310,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0xd5);
  tmp_i3 = G_SpawnStringExt("noise","NOSOUND",&local_60,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0xd7);
  if (tmp_i3 == 0) {
    tmp_u4 = vtos(param_1 + 0x5c);
    G_Error("target_speaker without a noise key at %s",tmp_u4);
    tmp_c1 = *local_60;
  }
  else {
    tmp_c1 = *local_60;
  }
  if (tmp_c1 == '*') {
    *(uint *)(param_1 + 0x1a8) = *(uint *)(param_1 + 0x1a8) | 8;
  }
  Q_strncpyz(local_5c,local_60,0x40);
  tmp_u4 = G_SoundIndex(local_5c);
  *(uint32_t *)(param_1 + 4) = 7;
  *(uint32_t *)(param_1 + 0x308) = tmp_u4;
  *(uint32_t *)(param_1 + 0xbc) = tmp_u4;
  *(int *)(param_1 + 0xb0) = (int)ROUND(*(float *)(param_1 + 0x30c) * 10.0);
  tmp_u2 = *(uint *)(param_1 + 0x1a8);
  *(int *)(param_1 + 0xac) = (int)ROUND(*(float *)(param_1 + 0x310) * 10.0);
  if ((tmp_u2 & 1) != 0) {
    *(uint32_t *)(param_1 + 0xa0) = tmp_u4;
  }
  *(void **)(param_1 + 0x2b4) = Use_Target_Speaker;
  if ((tmp_u2 & 0x24) != 0) {
    *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 0x20;
  }
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  if ((tmp_u2 & 0x10) != 0) {
    *(void **)(param_1 + 0x2a4) = target_speaker_multiple;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
  }
  *(uint *)(param_1 + 0xf4) = tmp_u2 >> 5 & 1;
  *(uint32_t *)(param_1 + 0xf8) = *(uint32_t *)(param_1 + 0x314);
  G_SpawnIntExt("volume",&g_unk_00259502,param_1 + 0xfc,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x112);
  if (*(int *)(param_1 + 0xfc) == 0) {
    *(uint32_t *)(param_1 + 0xfc) = 0xff;
  }
  trap_LinkEntity(param_1);
  return;
}

void SP_misc_beam(int param_1)
{
  uint32_t tmp_u1;
  char *local_20 [4];
  
  G_SpawnStringExt("target2",&g_unk_0026ea14,local_20,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x18c);
  if (*local_20[0] != '\0') {
    tmp_u1 = G_NewString(local_20[0]);
    *(uint32_t *)(param_1 + 0x248) = tmp_u1;
  }
  G_SpawnStringExt("shader","lightningBolt",local_20,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x191);
  if (*local_20[0] != '\0') {
    tmp_u1 = G_ShaderIndex(local_20[0]);
    *(uint32_t *)(param_1 + 0xa8) = tmp_u1;
  }
  G_SpawnIntExt("scale",&g_unk_00258b23,param_1 + 0xf0,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x195);
  G_SpawnVectorExt("color","1 1 1",param_1 + 0x80,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x196);
  *(void **)(param_1 + 0x2a4) = misc_beam_start;
  *(uint32_t *)(param_1 + 0x3fc) = 0;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

void target_laser_on(uint32_t *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  int tmp_i7;
  float local_50;
  float local_4c;
  float local_48;
  uint8_t local_44 [12];
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  int local_10;
  
  if (param_1[0xbc] == 0) {
    param_1[0xbc] = param_1;
  }
  tmp_i7 = param_1[0xbb];
  if (tmp_i7 != 0) {
    tmp_f1 = *(float *)(tmp_i7 + 0x138);
    tmp_f2 = *(float *)(tmp_i7 + 0x60);
    tmp_f3 = *(float *)(tmp_i7 + 0x144);
    tmp_f4 = *(float *)(tmp_i7 + 0x13c);
    tmp_f5 = *(float *)(tmp_i7 + 100);
    tmp_f6 = *(float *)(tmp_i7 + 0x148);
    param_1[0x9c] =
         (*(float *)(tmp_i7 + 0x140) * 0.5 +
         *(float *)(tmp_i7 + 0x134) * 0.5 + *(float *)(tmp_i7 + 0x5c)) - (float)param_1[0x17];
    param_1[0x9d] = (tmp_f3 * 0.5 + tmp_f1 * 0.5 + tmp_f2) - (float)param_1[0x18];
    param_1[0x9e] = (tmp_f6 * 0.5 + tmp_f4 * 0.5 + tmp_f5) - (float)param_1[0x19];
    VectorNormalize(param_1 + 0x9c);
  }
  local_50 = (float)param_1[0x9c] * 2048.0 + (float)param_1[0x17];
  local_4c = (float)param_1[0x9d] * 2048.0 + (float)param_1[0x18];
  local_48 = (float)param_1[0x9e] * 2048.0 + (float)param_1[0x19];
  trap_Trace(local_44,param_1 + 0x17,0,0,&local_50,*param_1,0x6000001);
  if (local_10 != 0) {
    G_Damage(g_entities + local_10 * 0x600,param_1,param_1[0xbc],param_1 + 0x9c,&local_38,
             param_1[0xb4],4,0x21);
  }
  param_1[0x1a] = local_38;
  param_1[0x1b] = local_34;
  param_1[0x1c] = local_30;
  trap_LinkEntity(param_1);
  param_1[0xa7] = g_unk_00abe908 + 100;
  return;
}

void target_laser_off(int param_1)
{
  trap_UnlinkEntity(param_1);
  *(uint32_t *)(param_1 + 0x29c) = 0;
  return;
}

void SP_target_laser(int param_1)
{
  *(uint32_t *)(param_1 + 0xec) = 1;
  *(uint32_t *)(param_1 + 0x80) = 0x3f800000;
  *(uint32_t *)(param_1 + 0x84) = 0x3f800000;
  *(void **)(param_1 + 0x2a4) = target_laser_start;
  *(uint32_t *)(param_1 + 0x88) = 0x3f800000;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

void SP_target_teleporter(int param_1)
{
  uint32_t tmp_u1;
  
  if (*(int *)(param_1 + 600) == 0) {
    tmp_u1 = vtos(param_1 + 0x5c);
    G_Printf("untargeted %s at %s\n",*(uint32_t *)(param_1 + 0x1a4),tmp_u1);
  }
  *(void **)(param_1 + 0x2b4) = target_teleporter_use;
  return;
}

void SP_target_relay(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t local_10 [2];
  
  *(void **)(param_1 + 0x2b4) = target_relay_use;
  if ((*(byte *)(param_1 + 0x1a8) & 0x20) == 0) {
    tmp_i1 = G_SpawnStringExt("lockednoise",&g_unk_0024bfa6,local_10,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x262);
    if (tmp_i1 == 0) {
      *(uint32_t *)(param_1 + 0x1e8) = 0x11;
      return;
    }
    tmp_u2 = G_SoundIndex(local_10[0]);
    *(uint32_t *)(param_1 + 0x1e8) = tmp_u2;
  }
  return;
}

void target_kill_use(int param_1,uint32_t param_2,uint32_t param_3)
{
  if ((*(byte *)(param_1 + 0x1a8) & 1) != 0) {
    G_Damage(param_3,0,0,0,0,100000,8,0x1e);
  }
  G_KillEnts(*(uint32_t *)(param_1 + 0x254),param_3,param_1,0);
  return;
}

void SP_target_kill(int param_1)
{
  *(void **)(param_1 + 0x2b4) = target_kill_use;
  return;
}

void SP_target_position(int param_1)
{
  G_SetOrigin(param_1,param_1 + 0x5c);
  return;
}

void SP_target_location(uint32_t param_1)
{
  G_FreeEntity(param_1);
  return;
}

void SP_target_fog(int param_1)
{
  int tmp_i1;
  int local_14;
  float local_10;
  
  *(void **)(param_1 + 0x2b4) = Use_target_fog;
  tmp_i1 = G_SpawnIntExt("distance",&g_unk_0024bfa6,&local_14,
                        "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x2fc);
  if ((tmp_i1 != 0) && (-1 < local_14)) {
    *(int *)(param_1 + 0xf4) = local_14;
  }
  tmp_i1 = G_SpawnFloatExt("time",&g_unk_00259546,&local_10,
                          "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x303);
  if ((tmp_i1 != 0) && (0.0 <= local_10)) {
    *(int *)(param_1 + 0x54) = (int)ROUND(local_10 * 1000.0);
  }
  return;
}

void SP_target_counter(int param_1)
{
  *(void **)(param_1 + 0x2b4) = Use_Target_Counter;
  return;
}

void SP_target_autosave(uint32_t param_1)
{
  G_FreeEntity(param_1);
  return;
}

void SP_target_lock(int param_1)
{
  *(void **)(param_1 + 0x2b4) = Use_Target_Lock;
  return;
}

void SP_target_alarm(int param_1)
{
  *(void **)(param_1 + 0x2b4) = Use_Target_Alarm;
  return;
}

void SP_target_smoke(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  long tmp_l3;
  uint32_t tmp_u4;
  uint tmp_u5;
  char *local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0xe979e;
  tmp_i1 = G_SpawnStringExt("shader",&g_unk_0026ea14,local_20,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x37a);
  if (tmp_i1 == 0) {
    *(uint32_t *)(param_1 + 0xa8) = 0;
  }
  else {
    tmp_u4 = G_ShaderIndex(local_20[0]);
    *(uint32_t *)(param_1 + 0xa8) = tmp_u4;
  }
  if (*(float *)(param_1 + 0x318) == 0.0) {
    *(uint32_t *)(param_1 + 0x318) = 0x42c80000;
  }
  *(void **)(param_1 + 0x2b4) = smoke_toggle;
  *(void **)(param_1 + 0x2a4) = smoke_init;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  G_SetOrigin(param_1,param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 4) = 0x27;
  tmp_i1 = G_SpawnStringExt("density",&g_unk_0026ea14,local_20,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x38d);
  if (tmp_i1 == 0) {
    tmp_u5 = *(uint *)(param_1 + 0x1a8);
    *(uint *)(param_1 + 0xf4) = tmp_u5 * 2 & 4;
  }
  else {
    tmp_l3 = strtol(local_20[0],(char **)0x0,10);
    tmp_u5 = *(uint *)(param_1 + 0x1a8);
    *(long *)(param_1 + 0xf4) = tmp_l3;
  }
  tmp_i1 = (int)ROUND(*(float *)(param_1 + 0x268));
  if (tmp_i1 == 0) {
    *(uint32_t *)(param_1 + 0x54) = 5000;
    tmp_i1 = 5000;
  }
  else {
    *(int *)(param_1 + 0x54) = tmp_i1;
  }
  tmp_i2 = (int)ROUND(*(float *)(param_1 + 800));
  if (tmp_i2 == 0) {
    *(uint32_t *)(param_1 + 0x58) = 2000;
    tmp_i2 = 2000;
  }
  else {
    *(int *)(param_1 + 0x58) = tmp_i2;
  }
  if ((float)*(int *)(param_1 + 0x37c) == 0.0) {
    *(uint32_t *)(param_1 + 0x80) = 0x41c00000;
  }
  else {
    *(float *)(param_1 + 0x80) = (float)*(int *)(param_1 + 0x37c);
  }
  if ((float)*(int *)(param_1 + 0x380) == 0.0) {
    *(uint32_t *)(param_1 + 0x84) = 0x42c00000;
  }
  else {
    *(float *)(param_1 + 0x84) = (float)*(int *)(param_1 + 0x380);
  }
  if (*(float *)(param_1 + 0x30c) == 0.0) {
    *(uint32_t *)(param_1 + 0x88) = 0x42480000;
  }
  else {
    *(float *)(param_1 + 0x88) = *(float *)(param_1 + 0x30c);
  }
  if (tmp_i1 < tmp_i2) {
    *(int *)(param_1 + 0x54) = tmp_i2 + 100;
  }
  if ((tmp_u5 & 8) != 0) {
    *(uint32_t *)(param_1 + 0xb0) = 1;
  }
  *(uint32_t *)(param_1 + 0x9c) = *(uint32_t *)(param_1 + 0x2c8);
  *(int *)(param_1 + 0x98) = (int)ROUND(*(float *)(param_1 + 0x318));
  if ((tmp_u5 & 4) != 0) {
    trap_LinkEntity(param_1);
  }
  return;
}

void SP_target_script_trigger(int param_1)
{
  G_SetOrigin(param_1,param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 4) = 0;
  *(void **)(param_1 + 0x2b4) = target_script_trigger_use;
  return;
}

void SP_target_rumble(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  long tmp_l3;
  uint32_t tmp_u4;
  double tmp_d5;
  char *local_38;
  char *local_34;
  char *local_30;
  char *local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0xe9a9e;
  tmp_i2 = G_SpawnStringExt("noise",&g_unk_0026ea14,&local_28,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x468);
  if (tmp_i2 != 0) {
    tmp_u4 = G_SoundIndex(local_28);
    *(uint32_t *)(param_1 + 0x1f8) = tmp_u4;
  }
  tmp_i2 = G_SpawnStringExt("startnoise",&g_unk_0026ea14,&local_24,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x46c);
  if (tmp_i2 != 0) {
    tmp_u4 = G_SoundIndex(local_24);
    *(uint32_t *)(param_1 + 0x1e8) = tmp_u4;
  }
  tmp_i2 = G_SpawnStringExt("endnoise",&g_unk_0026ea14,local_20,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x470);
  if (tmp_i2 != 0) {
    tmp_u4 = G_SoundIndex(local_20[0]);
    *(uint32_t *)(param_1 + 500) = tmp_u4;
  }
  *(void **)(param_1 + 0x2b4) = target_rumble_use;
  G_SpawnStringExt("pitch",&g_unk_0024bfa6,&local_38,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x476);
  tmp_d5 = strtod(local_38,(char **)0x0);
  if ((float)tmp_d5 == 0.0) {
    *(uint32_t *)(param_1 + 0x318) = 0x40a00000;
  }
  else {
    *(float *)(param_1 + 0x318) = (float)tmp_d5;
  }
  G_SpawnStringExt(&g_unk_00259564,&g_unk_0024bfa6,&local_34,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x47c);
  tmp_d5 = strtod(local_34,(char **)0x0);
  if ((float)tmp_d5 == 0.0) {
    *(uint32_t *)(param_1 + 0x310) = 0x40a00000;
  }
  else {
    *(float *)(param_1 + 0x310) = (float)tmp_d5;
  }
  G_SpawnStringExt("rampup",&g_unk_0024bfa6,&local_30,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x482);
  tmp_l3 = strtol(local_30,(char **)0x0,10);
  tmp_i2 = tmp_l3 * 1000;
  if (tmp_i2 == 0) {
    tmp_i2 = 1000;
  }
  *(int *)(param_1 + 0x37c) = tmp_i2;
  G_SpawnStringExt("rampdown",&g_unk_0024bfa6,&local_2c,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_target.c",0x487);
  tmp_l3 = strtol(local_2c,(char **)0x0,10);
  tmp_i2 = tmp_l3 * 1000;
  if (tmp_l3 * 1000 == 0) {
    tmp_i2 = 1000;
  }
  *(int *)(param_1 + 0x380) = tmp_i2;
  if (*(float *)(param_1 + 800) == 0.0) {
    tmp_f1 = 1000.0;
  }
  else {
    tmp_f1 = *(float *)(param_1 + 800) * 1000.0;
  }
  *(float *)(param_1 + 800) = tmp_f1;
  trap_LinkEntity(param_1);
  return;
}

void Use_Team_Spawnpoint(int param_1)
{
  uint tmp_u1;
  
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u1 & 2) == 0) {
    *(uint *)(param_1 + 0x1a8) = tmp_u1 | 2;
    if (GHIDRA_FIELD(g_developer, 12, 4) != 0) {
      G_Printf("setting %s %s active\n",*(uint32_t *)(param_1 + 0x1a4),
               *(uint32_t *)(param_1 + 600));
      return;
    }
  }
  else {
    *(uint *)(param_1 + 0x1a8) = tmp_u1 & 0xfffffffd;
    if (GHIDRA_FIELD(g_developer, 12, 4) != 0) {
      G_Printf("setting %s %s inactive\n",*(uint32_t *)(param_1 + 0x1a4),
               *(uint32_t *)(param_1 + 600));
      return;
    }
  }
  return;
}

void Use_Team_InitialSpawnpoint(int param_1)
{
  uint tmp_u1;
  uint tmp_u2;
  
  tmp_u1 = *(uint *)(param_1 + 0x1a8);
  tmp_u2 = tmp_u1 | 4;
  if ((tmp_u1 & 4) != 0) {
    tmp_u2 = tmp_u1 & 0xfffffffb;
  }
  *(uint *)(param_1 + 0x1a8) = tmp_u2;
  return;
}

void SP_team_CTF_redplayer(uint32_t param_1)
{
  G_Printf("^1team_ctf_*player entities are now obsolete, please remove them!\n");
  G_FreeEntity(param_1);
  return;
}

void SP_team_CTF_blueplayer(uint32_t param_1)
{
  G_Printf("^1team_ctf_*player entities are now obsolete, please remove them!\n");
  G_FreeEntity(param_1);
  return;
}

void SP_team_CTF_redspawn(int param_1)
{
  int tmp_i1;
  float local_18;
  float local_14;
  float local_10;
  uint32_t uStack_c;
  
  uStack_c = 0xec8e7;
  if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
    tmp_i1 = G_PickTarget(*(uint32_t *)(param_1 + 0x254));
    *(int *)(param_1 + 0x2ec) = tmp_i1;
    if (tmp_i1 != 0) {
      local_18 = *(float *)(tmp_i1 + 0x5c) - *(float *)(param_1 + 0x5c);
      local_14 = *(float *)(tmp_i1 + 0x60) - *(float *)(param_1 + 0x60);
      local_10 = *(float *)(tmp_i1 + 100) - *(float *)(param_1 + 100);
      vectoangles(&local_18,param_1 + 0x74);
    }
    *(void **)(param_1 + 0x2b4) = Use_Team_Spawnpoint;
    *(uint32_t *)(param_1 + 0x134) = 0xc1800000;
    *(uint32_t *)(param_1 + 0x138) = 0xc1800000;
    *(uint32_t *)(param_1 + 0x13c) = 0xc1c00000;
    *(uint32_t *)(param_1 + 0x140) = 0x41800000;
    *(uint32_t *)(param_1 + 0x144) = 0x41800000;
    *(uint32_t *)(param_1 + 0x148) = 0x42000000;
    *(void **)(param_1 + 0x2a4) = DropToFloor;
    return;
  }
  G_FreeEntity(param_1);
  return;
}

void SP_team_CTF_bluespawn(int param_1)
{
  int tmp_i1;
  float local_18;
  float local_14;
  float local_10;
  uint32_t uStack_c;
  
  uStack_c = 0xec9c7;
  if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
    tmp_i1 = G_PickTarget(*(uint32_t *)(param_1 + 0x254));
    *(int *)(param_1 + 0x2ec) = tmp_i1;
    if (tmp_i1 != 0) {
      local_18 = *(float *)(tmp_i1 + 0x5c) - *(float *)(param_1 + 0x5c);
      local_14 = *(float *)(tmp_i1 + 0x60) - *(float *)(param_1 + 0x60);
      local_10 = *(float *)(tmp_i1 + 100) - *(float *)(param_1 + 100);
      vectoangles(&local_18,param_1 + 0x74);
    }
    *(void **)(param_1 + 0x2b4) = Use_Team_Spawnpoint;
    *(uint32_t *)(param_1 + 0x134) = 0xc1800000;
    *(uint32_t *)(param_1 + 0x138) = 0xc1800000;
    *(uint32_t *)(param_1 + 0x13c) = 0xc1c00000;
    *(uint32_t *)(param_1 + 0x140) = 0x41800000;
    *(uint32_t *)(param_1 + 0x144) = 0x41800000;
    *(uint32_t *)(param_1 + 0x148) = 0x42000000;
    *(void **)(param_1 + 0x2a4) = DropToFloor;
    return;
  }
  G_FreeEntity(param_1);
  return;
}

void SP_team_CTF_greenspawn(int param_1)
{
  int tmp_i1;
  float local_18;
  float local_14;
  float local_10;
  
  if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
    G_FreeEntity(param_1);
    return;
  }
  tmp_i1 = G_PickTarget(*(uint32_t *)(param_1 + 0x254));
  *(int *)(param_1 + 0x2ec) = tmp_i1;
  if (tmp_i1 != 0) {
    local_18 = *(float *)(tmp_i1 + 0x5c) - *(float *)(param_1 + 0x5c);
    local_14 = *(float *)(tmp_i1 + 0x60) - *(float *)(param_1 + 0x60);
    local_10 = *(float *)(tmp_i1 + 100) - *(float *)(param_1 + 100);
    vectoangles(&local_18,param_1 + 0x74);
  }
  *(void **)(param_1 + 0x2b4) = Use_Team_Spawnpoint;
  *(uint32_t *)(param_1 + 0x134) = 0xc1800000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1800000;
  *(uint32_t *)(param_1 + 0x13c) = 0xc1c00000;
  *(uint32_t *)(param_1 + 0x140) = 0x41800000;
  *(uint32_t *)(param_1 + 0x144) = 0x41800000;
  *(uint32_t *)(param_1 + 0x148) = 0x42000000;
  *(void **)(param_1 + 0x2a4) = DropToFloor;
  return;
}

void SP_team_WOLF_objective(int param_1)
{
  int tmp_i1;
  size_t tmp_s2;
  uint32_t tmp_u3;
  char *local_20 [4];
  
  G_SpawnStringExt("description","WARNING: No objective description set",local_20,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_team.c",0x452);
  tmp_s2 = strlen(local_20[0]);
  tmp_u3 = G_Alloc(tmp_s2 + 1);
  *(uint32_t *)(param_1 + 0x248) = tmp_u3;
  tmp_s2 = strlen(local_20[0]);
  Q_strncpyz(tmp_u3,local_20[0],tmp_s2 + 1);
  tmp_i1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 4) = 0x38;
  *(int *)(param_1 + 0x29c) = tmp_i1 + 100;
  *(void **)(param_1 + 0x2a4) = objective_Register;
  if ((*(uint *)(param_1 + 0x1a8) & 1) == 0) {
    if ((*(uint *)(param_1 + 0x1a8) & 2) != 0) {
      *(uint32_t *)(param_1 + 0x39c) = 2;
    }
  }
  else {
    *(uint32_t *)(param_1 + 0x39c) = 1;
  }
  return;
}

void SP_team_WOLF_checkpoint(int param_1)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t local_10 [2];
  
  if (*(int *)(param_1 + 0x3ac) == 0) {
    G_Error("team_WOLF_checkpoint must have a \"scriptname\"\n");
  }
  tmp_pc1 = *(char **)(param_1 + 0x1b4);
  *(uint32_t *)(param_1 + 4) = 0x11;
  if (tmp_pc1 == (char *)0x0) {
    tmp_pc1 = "models/multiplayer/flagpole/flagpole.md3";
  }
  tmp_u2 = G_ModelIndex(tmp_pc1);
  *(uint32_t *)(param_1 + 0xa4) = tmp_u2;
  G_SpawnStringExt("noise","sound/movers/doors/door6_open.wav",local_10,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_team.c",0x608);
  tmp_u2 = G_SoundIndex(local_10[0]);
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x14c) = 1;
  *(uint32_t *)(param_1 + 0x134) = 0xc1000000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1000000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x1e8) = tmp_u2;
  *(uint32_t *)(param_1 + 0x140) = 0x41000000;
  *(uint32_t *)(param_1 + 0x144) = 0x41000000;
  *(uint32_t *)(param_1 + 0x148) = 0x43000000;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  *(uint32_t *)(param_1 + 0xb0) = 0;
  *(uint32_t *)(param_1 + 0x108) = 1;
  *(uint32_t *)(param_1 + 0x29c) = 0;
  *(uint32_t *)(param_1 + 0x2c8) = 0xffffffff;
  *(uint32_t *)(param_1 + 0x39c) = 0xffffffff;
  *(uint32_t *)(param_1 + 0x2e4) = 0xffffffff;
  if ((*(uint *)(param_1 + 0x1a8) & 1) == 0) {
    if ((*(uint *)(param_1 + 0x1a8) & 2) == 0) {
      *(void **)(param_1 + 0x2b0) = checkpoint_touch;
      trap_LinkEntity(param_1);
      return;
    }
    *(void **)(param_1 + 0x2b4) = checkpoint_use;
    trap_LinkEntity(param_1);
    return;
  }
  *(void **)(param_1 + 0x2b0) = checkpoint_spawntouch;
  trap_LinkEntity(param_1);
  return;
}

void trigger_heal_think(int param_1)
{
  int tmp_i1;
  
  *(int *)(param_1 + 0x29c) = GHIDRA_FIELD(g_healthCabinetTime, 12, 4) + g_unk_00abe908;
  tmp_i1 = *(int *)(param_1 + 0x2d0) + *(int *)(param_1 + 0x2c8);
  *(int *)(param_1 + 0x2c8) = tmp_i1;
  if (*(int *)(param_1 + 0x2e4) < tmp_i1) {
    *(int *)(param_1 + 0x2c8) = *(int *)(param_1 + 0x2e4);
  }
  return;
}

void trigger_ammo_think(int param_1)
{
  int tmp_i1;
  
  *(int *)(param_1 + 0x29c) = GHIDRA_FIELD(g_ammoCabinetTime, 12, 4) + g_unk_00abe908;
  tmp_i1 = *(int *)(param_1 + 0x2d0) + *(int *)(param_1 + 0x2c8);
  *(int *)(param_1 + 0x2c8) = tmp_i1;
  if (*(int *)(param_1 + 0x2e4) < tmp_i1) {
    *(int *)(param_1 + 0x2c8) = *(int *)(param_1 + 0x2e4);
  }
  return;
}

void Touch_ObjectiveInfo(uint32_t param_1,int param_2)
{
  if (*(int *)(param_2 + 400) != 0) {
    *(uint32_t *)(*(int *)(param_2 + 400) + 0x103c) = param_1;
  }
  return;
}

void func_timer_think(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  
  G_UseTargets(param_1,*(uint32_t *)(param_1 + 0x2f0));
  tmp_f3 = (float)g_unk_00abe908;
  tmp_f1 = *(float *)(param_1 + 0x30c);
  tmp_u4 = rand();
  tmp_f2 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
  *(int *)(param_1 + 0x29c) =
       (int)ROUND(((tmp_f2 + tmp_f2) * *(float *)(param_1 + 0x310) + tmp_f1) * 1000.0 + tmp_f3);
  return;
}

void trigger_always_think(uint32_t param_1)
{
  G_UseTargets(param_1,param_1);
  G_FreeEntity(param_1);
  return;
}

void Use_target_push(int param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_3 + 400);
  if ((tmp_i1 != 0) && (*(int *)(tmp_i1 + 4) == 0)) {
    *(uint32_t *)(tmp_i1 + 0x20) = *(uint32_t *)(param_1 + 0x68);
    *(uint32_t *)(*(int *)(param_3 + 400) + 0x24) = *(uint32_t *)(param_1 + 0x6c);
    *(uint32_t *)(*(int *)(param_3 + 400) + 0x28) = *(uint32_t *)(param_1 + 0x70);
    if (*(int *)(param_3 + 0x2c4) < g_unk_00abe908) {
      *(int *)(param_3 + 0x2c4) = g_unk_00abe908 + 0x5dc;
      G_Sound(param_3,*(uint32_t *)(param_1 + 0x308));
      return;
    }
  }
  return;
}

void trigger_heal_setup(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = G_FindByTargetnameFast
                    (0,*(uint32_t *)(param_1 + 0x254),*(uint32_t *)(param_1 + 0x5bc));
  *(int *)(param_1 + 0x264) = tmp_i1;
  if (tmp_i1 == 0) {
    G_Error("trigger_heal failed to find target: %s\n",*(uint32_t *)(param_1 + 0x254));
  }
  if (*(int *)(param_1 + 0x2e4) != -9999) {
    *(void **)(param_1 + 0x2a4) = trigger_heal_think;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  }
  return;
}

void trigger_ammo_setup(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = G_FindByTargetnameFast
                    (0,*(uint32_t *)(param_1 + 0x254),*(uint32_t *)(param_1 + 0x5bc));
  *(int *)(param_1 + 0x264) = tmp_i1;
  if (tmp_i1 == 0) {
    G_Error("trigger_ammo failed to find target: %s\n",*(uint32_t *)(param_1 + 0x254));
  }
  if (*(int *)(param_1 + 0x2e4) != -9999) {
    *(void **)(param_1 + 0x2a4) = trigger_ammo_think;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  }
  return;
}

void Touch_flagonly(int param_1,int param_2)
{
  int tmp_i1;
  uint tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  
  tmp_i1 = *(int *)(param_2 + 400);
  if (tmp_i1 != 0) {
    tmp_u2 = *(uint *)(param_1 + 0x1a8);
    if (((tmp_u2 & 1) == 0) || (*(int *)(tmp_i1 + 0x164) == 0)) {
      if ((tmp_u2 & 2) == 0) {
        return;
      }
      if (*(int *)(tmp_i1 + 0x168) == 0) {
        return;
      }
      if ((tmp_u2 & 4) != 0) {
        *(uint32_t *)(tmp_i1 + 0x168) = 0;
        *(uint32_t *)(*(int *)(param_2 + 400) + 0x1050) = 0;
      }
      AddScore(param_2,(int)ROUND(*(float *)(param_1 + 0x3fc)));
      tmp_u3 = *(uint32_t *)(param_1 + 0x218);
      *(int *)(param_1 + 0x218) = param_2;
      G_Script_ScriptEvent(param_1,"death",&g_unk_0026ea14);
      G_Script_ScriptEvent
                (g_entities + *(int *)(*(int *)(param_2 + 400) + 0x5294) * 0x600,"trigger",
                 "captured");
      tmp_u4 = va("Axis captured %s",*(uint32_t *)(param_1 + 0x3ac));
      Bot_Util_SendTrigger(param_1,0,tmp_u4,&g_unk_0026ea14);
      *(uint32_t *)(param_1 + 0x218) = tmp_u3;
    }
    else {
      if ((tmp_u2 & 4) != 0) {
        *(uint32_t *)(tmp_i1 + 0x164) = 0;
        *(uint32_t *)(*(int *)(param_2 + 400) + 0x1050) = 0;
      }
      AddScore(param_2,(int)ROUND(*(float *)(param_1 + 0x3fc)));
      tmp_u3 = *(uint32_t *)(param_1 + 0x218);
      *(int *)(param_1 + 0x218) = param_2;
      G_Script_ScriptEvent(param_1,"death",&g_unk_0026ea14);
      tmp_u4 = va("Allies captured %s",*(uint32_t *)(param_1 + 0x3ac));
      Bot_Util_SendTrigger(param_1,0,tmp_u4,&g_unk_0026ea14);
      G_Script_ScriptEvent
                (g_entities + *(int *)(*(int *)(param_2 + 400) + 0x5294) * 0x600,"trigger",
                 "captured");
      *(uint32_t *)(param_1 + 0x218) = tmp_u3;
    }
    *(uint32_t *)(param_1 + 0x2b0) = 0;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
    *(void **)(param_1 + 0x2a4) = G_FreeEntity;
  }
  return;
}

void Touch_flagonly_multiple(int param_1,int param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  uint32_t local_24;
  
  tmp_i1 = *(int *)(param_2 + 400);
  if (tmp_i1 != 0) {
    if (((*(uint *)(param_1 + 0x1a8) & 1) == 0) || (*(int *)(tmp_i1 + 0x164) == 0)) {
      if ((*(uint *)(param_1 + 0x1a8) & 2) == 0) {
        return;
      }
      if (*(int *)(tmp_i1 + 0x168) == 0) {
        return;
      }
      *(uint32_t *)(tmp_i1 + 0x168) = 0;
      *(uint32_t *)(*(int *)(param_2 + 400) + 0x1050) = 0;
      AddScore(param_2,(int)ROUND(*(float *)(param_1 + 0x3fc)));
      local_24 = *(uint32_t *)(param_1 + 0x218);
      *(int *)(param_1 + 0x218) = param_2;
      G_Script_ScriptEvent(param_1,"death",&g_unk_0026ea14);
      G_Script_ScriptEvent
                (g_entities + *(int *)(*(int *)(param_2 + 400) + 0x5294) * 0x600,"trigger",
                 "captured");
      tmp_u3 = *(uint32_t *)(param_1 + 0x3ac);
      tmp_pc2 = "Axis captured %s";
    }
    else {
      *(uint32_t *)(tmp_i1 + 0x164) = 0;
      *(uint32_t *)(*(int *)(param_2 + 400) + 0x1050) = 0;
      AddScore(param_2,(int)ROUND(*(float *)(param_1 + 0x3fc)));
      local_24 = *(uint32_t *)(param_1 + 0x218);
      *(int *)(param_1 + 0x218) = param_2;
      G_Script_ScriptEvent(param_1,"death",&g_unk_0026ea14);
      G_Script_ScriptEvent
                (g_entities + *(int *)(*(int *)(param_2 + 400) + 0x5294) * 0x600,"trigger",
                 "captured");
      tmp_u3 = *(uint32_t *)(param_1 + 0x3ac);
      tmp_pc2 = "Allies captured %s";
    }
    tmp_u3 = va(tmp_pc2,tmp_u3);
    Bot_Util_SendTrigger(param_1,0,tmp_u3,&g_unk_0026ea14);
    *(uint32_t *)(param_1 + 0x218) = local_24;
  }
  return;
}

void Think_SetupObjectiveInfo(uint32_t *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int local_40;
  
  tmp_i5 = G_FindByTargetnameFast(0,param_1[0x95],param_1[0x16f]);
  param_1[0x99] = tmp_i5;
  if (tmp_i5 == 0) {
    G_Error("\'trigger_objective_info\' has a missing target \'%s\'\n",param_1[0x95]);
    tmp_i5 = param_1[0x99];
  }
  tmp_i6 = *(int *)(tmp_i5 + 4);
  if (tmp_i6 == 0xe) {
    if ((*(byte *)(param_1 + 0x6a) & 3) != 0) {
      tmp_i5 = G_Spawn();
      nitrox_AddEntityToEntityArray(&IndicatorEntities,tmp_i5);
      *(uint32_t *)(tmp_i5 + 0x128) = 0x20;
      *(char **)(tmp_i5 + 0x1a4) = "explosive_indicator";
      tmp_u4 = param_1[0x6a];
      *(uint32_t **)(tmp_i5 + 0x218) = param_1;
      *(uint32_t *)(tmp_i5 + 0xc) = 0;
      *(uint *)(tmp_i5 + 4) = (-(uint)((tmp_u4 & 8) == 0) & 0xffffffe9) + 0x24;
      if ((param_1[0x6a] & 1) == 0) {
        if ((param_1[0x6a] & 2) != 0) {
          *(uint32_t *)(tmp_i5 + 0x108) = 2;
        }
      }
      else {
        *(uint32_t *)(tmp_i5 + 0x108) = 1;
      }
      G_SetOrigin(tmp_i5,param_1 + 0x5a);
      *(uint32_t *)(tmp_i5 + 0xa8) = param_1[0x42];
      *(uint32_t *)(tmp_i5 + 0x180) = *param_1;
      *(void **)(tmp_i5 + 0x2a4) = explosive_indicator_think;
      *(int *)(tmp_i5 + 0x29c) = g_unk_00abe908 + 100;
      *(uint32_t *)(tmp_i5 + 0x10c) = *(uint32_t *)(param_1[0x99] + 0x4f4);
      if (param_1[0x110] == 0) {
        tmp_f1 = (float)param_1[0x54];
        *(float *)(tmp_i5 + 0x18) = tmp_f1;
        tmp_f2 = (float)param_1[0x55];
        *(float *)(tmp_i5 + 0x1c) = tmp_f2;
        tmp_f3 = (float)param_1[0x56];
        *(float *)(tmp_i5 + 0x20) = tmp_f3;
        tmp_f1 = tmp_f1 + (float)param_1[0x57];
        *(float *)(tmp_i5 + 0x18) = tmp_f1;
        tmp_f2 = tmp_f2 + (float)param_1[0x58];
        *(float *)(tmp_i5 + 0x1c) = tmp_f2;
        tmp_f1 = tmp_f1 * 0.5;
        tmp_f2 = tmp_f2 * 0.5;
        tmp_f3 = (tmp_f3 + (float)param_1[0x59]) * 0.5;
      }
      else {
        *(uint32_t *)(tmp_i5 + 0x440) = param_1[0x110];
        Q_strncpyz(tmp_i5 + 0x400,param_1 + 0x100,0x40);
        tmp_f1 = *(float *)(tmp_i5 + 0x18);
        tmp_f2 = *(float *)(tmp_i5 + 0x1c);
        tmp_f3 = *(float *)(tmp_i5 + 0x20);
      }
      *(float *)(tmp_i5 + 0x18) = (float)(int)ROUND(tmp_f1);
      *(float *)(tmp_i5 + 0x1c) = (float)(int)ROUND(tmp_f2);
      *(float *)(tmp_i5 + 0x20) = (float)(int)ROUND(tmp_f3);
      trap_LinkEntity(tmp_i5);
      *(uint32_t **)(param_1[0x99] + 0x218) = param_1;
    }
  }
  else if (tmp_i6 == 0x20) {
    *(uint32_t **)(tmp_i5 + 0x218) = param_1;
    tmp_i5 = param_1[0x99];
    tmp_i6 = G_FindByTargetnameFast(tmp_i5,param_1[0x95],param_1[0x16f]);
    tmp_i8 = ((*(int *)(tmp_i5 + 0x1a8) << 0x1d) >> 0x1f) + 2;
    *(uint32_t *)(tmp_i5 + 0x90) = param_1[0x42];
    if (tmp_i6 == 0) {
      *(uint32_t *)(tmp_i5 + 0x2e8) = 0;
      local_40 = 0;
    }
    else {
      local_40 = ((*(int *)(tmp_i6 + 0x1a8) << 0x1d) >> 0x1f) + 2;
      if (*(int *)(tmp_i6 + 4) != 0x20) {
        G_Error("\'trigger_objective_info\' targets multiple entities with targetname \'%s\', the second one isn\'t a \'func_constructible\'\n"
                ,param_1[0x95]);
      }
      if (tmp_i8 == local_40) {
        G_Error("\'trigger_objective_info\' targets two \'func_constructible\' entities with targetname \'%s\' that are constructible by the same team\n"
                ,param_1[0x95]);
      }
      *(uint32_t *)(tmp_i6 + 0x90) = param_1[0x42];
      param_1[0xba] = tmp_i6;
      *(uint32_t **)(tmp_i6 + 0x218) = param_1;
      *(int *)(tmp_i5 + 0x2e8) = tmp_i6;
      *(int *)(tmp_i6 + 0x2e8) = tmp_i5;
    }
    if (*(float *)(tmp_i5 + 0x84) == 0.0) {
      tmp_i7 = G_Spawn();
      nitrox_AddEntityToEntityArray(&IndicatorEntities,tmp_i7);
      *(uint32_t *)(tmp_i7 + 0x128) = 0x20;
      *(char **)(tmp_i7 + 0x1a4) = "constructible_indicator";
      tmp_u4 = param_1[0x6a];
      *(uint32_t *)(tmp_i7 + 0xc) = 0;
      *(uint *)(tmp_i7 + 4) = (-(uint)((tmp_u4 & 8) == 0) & 0xfffffffa) + 0x25;
      if ((tmp_i6 == 0) || ((*(int *)(tmp_i5 + 0x39c) != 0 && (1 < *(int *)(tmp_i5 + 0x3a4))))) {
        *(int *)(tmp_i7 + 0x108) = tmp_i8;
      }
      else if ((*(int *)(tmp_i6 + 0x39c) == 0) || (*(int *)(tmp_i6 + 0x3a4) < 2)) {
        *(uint32_t *)(tmp_i7 + 0x108) = 3;
      }
      else {
        *(int *)(tmp_i7 + 0x108) = local_40;
      }
      *(uint32_t *)(tmp_i7 + 0xa8) = param_1[0x42];
      *(uint32_t *)(tmp_i7 + 0x180) = *param_1;
      param_1[0xe7] = (tmp_i7 + -0x93e4a0 >> 9) * -0x55555555;
      *(void **)(tmp_i7 + 0x2a4) = constructible_indicator_think;
      *(uint32_t **)(tmp_i7 + 0x218) = param_1;
      *(int *)(tmp_i7 + 0x29c) = g_unk_00abe908 + 100;
      if (param_1[0x110] == 0) {
        tmp_f1 = (float)param_1[0x54];
        *(float *)(tmp_i7 + 0x18) = tmp_f1;
        tmp_f2 = (float)param_1[0x55];
        *(float *)(tmp_i7 + 0x1c) = tmp_f2;
        tmp_f3 = (float)param_1[0x56];
        *(float *)(tmp_i7 + 0x20) = tmp_f3;
        tmp_f1 = tmp_f1 + (float)param_1[0x57];
        *(float *)(tmp_i7 + 0x18) = tmp_f1;
        tmp_f2 = tmp_f2 + (float)param_1[0x58];
        *(float *)(tmp_i7 + 0x1c) = tmp_f2;
        tmp_f1 = tmp_f1 * 0.5;
        tmp_f2 = tmp_f2 * 0.5;
        tmp_f3 = (tmp_f3 + (float)param_1[0x59]) * 0.5;
      }
      else {
        *(uint32_t *)(tmp_i7 + 0x440) = param_1[0x110];
        Q_strncpyz(tmp_i7 + 0x400,param_1 + 0x100,0x40);
        tmp_f1 = *(float *)(tmp_i7 + 0x18);
        tmp_f2 = *(float *)(tmp_i7 + 0x1c);
        tmp_f3 = *(float *)(tmp_i7 + 0x20);
      }
      *(float *)(tmp_i7 + 0x18) = (float)(int)ROUND(tmp_f1);
      *(float *)(tmp_i7 + 0x1c) = (float)(int)ROUND(tmp_f2);
      *(float *)(tmp_i7 + 0x20) = (float)(int)ROUND(tmp_f3);
      trap_LinkEntity(tmp_i7);
    }
    param_1[0xac] = Touch_ObjectiveInfo;
  }
  else if (tmp_i6 == 0x37) {
    *(uint32_t **)(tmp_i5 + 0x218) = param_1;
  }
  trap_LinkEntity(param_1);
  return;
}

void trigger_teleporter_touch(int param_1,int param_2)
{
  int tmp_i1;
  
  if ((*(int *)(param_2 + 400) != 0) && (*(int *)(*(int *)(param_2 + 400) + 4) != 3)) {
    tmp_i1 = G_PickTarget(*(uint32_t *)(param_1 + 0x254));
    if (tmp_i1 == 0) {
      G_Printf("Couldn\'t find teleporter destination\n");
    }
    else {
      TeleportPlayer(param_2,tmp_i1 + 0x5c,tmp_i1 + 0x74);
    }
  }
  return;
}

void func_timer_use(int param_1,uint32_t param_2,uint32_t param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  
  *(uint32_t *)(param_1 + 0x2f0) = param_3;
  if (*(int *)(param_1 + 0x29c) != 0) {
    *(uint32_t *)(param_1 + 0x29c) = 0;
    return;
  }
  G_UseTargets(param_1,param_3);
  tmp_f3 = (float)g_unk_00abe908;
  tmp_f1 = *(float *)(param_1 + 0x30c);
  tmp_u4 = rand();
  tmp_f2 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
  *(int *)(param_1 + 0x29c) =
       (int)ROUND(((tmp_f2 + tmp_f2) * *(float *)(param_1 + 0x310) + tmp_f1) * 1000.0 + tmp_f3);
  return;
}

void Use_Multi(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  param_2 = param_3;
  multi_trigger();
  return;
}

void Touch_Multi(int param_1,int param_2)
{
  uint tmp_u1;
  int tmp_i2;
  
  tmp_i2 = *(int *)(param_2 + 400);
  if (tmp_i2 != 0) {
    tmp_u1 = *(uint *)(param_1 + 0x1a8);
    if ((tmp_u1 & 1) == 0) {
      if (((tmp_u1 & 2) != 0) && (*(int *)(tmp_i2 + 3000) != 2)) {
        return;
      }
    }
    else if (*(int *)(tmp_i2 + 3000) != 1) {
      return;
    }
    if ((tmp_u1 & 4) == 0) {
      if (((tmp_u1 & 8) != 0) && ((*(byte *)(param_2 + 0x128) & 8) == 0)) {
        return;
      }
    }
    else {
      if ((*(byte *)(param_2 + 0x128) & 8) != 0) {
        return;
      }
      if ((tmp_u1 & 8) != 0) {
        return;
      }
    }
    if ((tmp_u1 & 0x10) != 0) {
      tmp_i2 = IsClass(param_2,0);
      if (tmp_i2 == 0) {
        return;
      }
      tmp_u1 = *(uint *)(param_1 + 0x1a8);
    }
    if ((tmp_u1 & 0x20) != 0) {
      tmp_i2 = IsClass(param_2,3);
      if (tmp_i2 == 0) {
        return;
      }
      tmp_u1 = *(uint *)(param_1 + 0x1a8);
    }
    if ((tmp_u1 & 0x40) != 0) {
      tmp_i2 = IsClass(param_2,1);
      if (tmp_i2 == 0) {
        return;
      }
      tmp_u1 = *(uint *)(param_1 + 0x1a8);
    }
    if ((tmp_u1 & 0x80) != 0) {
      tmp_i2 = IsClass(param_2,2);
      if (tmp_i2 == 0) {
        return;
      }
      tmp_u1 = *(uint *)(param_1 + 0x1a8);
    }
    if (((tmp_u1 & 0x100) == 0) || (tmp_i2 = IsClass(param_2,4), tmp_i2 != 0)) {
      multi_trigger();
      return;
    }
  }
  return;
}

void SP_trigger_multiple(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  
  G_SpawnFloatExt(&g_unk_0023f11d,&g_unk_00259546,param_1 + 0x30c,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x8d);
  G_SpawnFloatExt("random",&g_unk_0024bfa6,param_1 + 0x310,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x8e);
  G_SpawnIntExt("numPlayers",&g_unk_00258b23,param_1 + 0x504,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x8f);
  tmp_f1 = *(float *)(param_1 + 0x30c);
  if ((tmp_f1 <= *(float *)(param_1 + 0x310)) && (0.0 <= tmp_f1)) {
    *(float *)(param_1 + 0x310) = tmp_f1 - 0.1;
    G_Printf("trigger_multiple has random >= wait\n");
  }
  *(void **)(param_1 + 0x2b0) = Touch_Multi;
  *(void **)(param_1 + 0x2b4) = Use_Multi;
  *(uint32_t *)(param_1 + 4) = 0x2b;
  tmp_i2 = VectorCompare(param_1 + 0x74,&vec3_origin);
  if (tmp_i2 == 0) {
    G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  }
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
  }
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(uint32_t *)(param_1 + 0x128) = 1;
  trap_LinkEntity(param_1);
  return;
}

void SP_trigger_always(int param_1)
{
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 300;
  *(void **)(param_1 + 0x2a4) = trigger_always_think;
  return;
}

void trigger_push_touch(void)
{
  return;
}

void trigger_push_use(void)
{
  return;
}

void SP_trigger_push(void)
{
  return;
}

void SP_target_push(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  
  if (*(float *)(param_1 + 0x268) == 0.0) {
    *(uint32_t *)(param_1 + 0x268) = 0x447a0000;
  }
  G_SetMovedir(param_1 + 0x74,param_1 + 0x68);
  tmp_f1 = *(float *)(param_1 + 0x268);
  *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) * tmp_f1;
  *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) * tmp_f1;
  *(float *)(param_1 + 0x70) = tmp_f1 * *(float *)(param_1 + 0x70);
  if (*(int *)(param_1 + 0x254) != 0) {
    *(void **)(param_1 + 0x2a4) = AimAtTarget;
    *(uint32_t *)(param_1 + 0x150) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x154) = *(uint32_t *)(param_1 + 0x60);
    tmp_i2 = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x158) = *(uint32_t *)(param_1 + 100);
    *(uint32_t *)(param_1 + 0x15c) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x160) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x164) = *(uint32_t *)(param_1 + 100);
    *(int *)(param_1 + 0x29c) = tmp_i2 + 100;
  }
  *(void **)(param_1 + 0x2b4) = Use_target_push;
  return;
}

void SP_trigger_teleport(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = VectorCompare(param_1 + 0x74,&vec3_origin);
  if (tmp_i1 == 0) {
    G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  }
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
  }
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(uint32_t *)(param_1 + 0x128) = 0;
  *(uint32_t *)(param_1 + 4) = 9;
  *(void **)(param_1 + 0x2b0) = trigger_teleporter_touch;
  trap_LinkEntity(param_1);
  return;
}

void SP_trigger_hurt(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  double tmp_d3;
  char *local_14;
  uint32_t local_10;
  
  local_10 = 0xf4338;
  tmp_i1 = VectorCompare(param_1 + 0x74,&vec3_origin);
  if (tmp_i1 == 0) {
    G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  }
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
  }
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(uint32_t *)(param_1 + 0x128) = 1;
  G_SpawnStringExt("sound","sound/player/hurt_barbwire.wav",&local_10,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x1a6);
  tmp_u2 = G_SoundIndex(local_10);
  *(uint32_t *)(param_1 + 0x308) = tmp_u2;
  if (*(int *)(param_1 + 0x2d0) == 0) {
    *(uint32_t *)(param_1 + 0x2d0) = 5;
  }
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(void **)(param_1 + 0x2b4) = hurt_use;
  if ((*(byte *)(param_1 + 0x1a8) & 1) == 0) {
    *(void **)(param_1 + 0x2b0) = hurt_touch;
  }
  G_SpawnStringExt(&g_unk_00259b85,&g_unk_0024bfa6,&local_14,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x1b4);
  tmp_d3 = strtod(local_14,(char **)0x0);
  *(float *)(param_1 + 0x318) = (float)tmp_d3;
  return;
}

void SP_trigger_removeProtection(int param_1)
{
  int tmp_i1;
  double tmp_d2;
  char *local_10;
  
  tmp_i1 = VectorCompare(param_1 + 0x74,&vec3_origin);
  if (tmp_i1 == 0) {
    G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  }
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
  }
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(uint32_t *)(param_1 + 0x128) = 1;
  *(void **)(param_1 + 0x2b4) = removeprotection_use;
  if ((*(byte *)(param_1 + 0x1a8) & 1) == 0) {
    *(void **)(param_1 + 0x2b0) = removeprotection_touch;
  }
  G_SpawnStringExt(&g_unk_00259b85,&g_unk_0024bfa6,&local_10,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x1fd);
  tmp_d2 = strtod(local_10,(char **)0x0);
  *(float *)(param_1 + 0x318) = (float)tmp_d2;
  return;
}

void SP_misc_cabinet_health(int param_1)
{
  if ((GHIDRA_FIELD(g_gametype, 12, 4) == 8) && ((g_DMOptions[0xc] & 0x40) != 0)) {
    G_FreeEntity(param_1);
    return;
  }
  *(uint32_t *)(param_1 + 0x134) = 0xc1a00000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1a00000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x41a00000;
  *(uint32_t *)(param_1 + 0x144) = 0x41a00000;
  *(uint32_t *)(param_1 + 0x148) = 0x42700000;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  *(uint32_t *)(param_1 + 4) = 0x2f;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x14c) = 1;
  trap_LinkEntity(param_1);
  return;
}

void SP_trigger_heal(int param_1)
{
  int tmp_i1;
  long tmp_l2;
  char *local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0xf4699;
  tmp_i1 = VectorCompare(param_1 + 0x74,&vec3_origin);
  if (tmp_i1 == 0) {
    G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  }
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
  }
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(uint32_t *)(param_1 + 0x128) = 1;
  *(void **)(param_1 + 0x2b0) = heal_touch;
  G_SpawnStringExt("healtotal",&g_unk_0024bfa6,local_20,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x295);
  tmp_l2 = strtol(local_20[0],(char **)0x0,10);
  *(long *)(param_1 + 0x2c8) = tmp_l2;
  if (tmp_l2 < 1) {
    *(uint32_t *)(param_1 + 0x2c8) = 0xffffd8f1;
    *(uint32_t *)(param_1 + 0x2e4) = 0xffffd8f1;
    *(uint32_t *)(param_1 + 0x264) = 0;
    *(uint32_t *)(param_1 + 4) = 0x31;
    if ((*(char **)(param_1 + 0x254) == (char *)0x0) || (**(char **)(param_1 + 0x254) == '\0'))
    goto LAB_000f47a5;
  }
  else {
    *(long *)(param_1 + 0x2e4) = tmp_l2;
    *(uint32_t *)(param_1 + 0x264) = 0;
    *(uint32_t *)(param_1 + 4) = 0x31;
    if ((*(char **)(param_1 + 0x254) == (char *)0x0) || (**(char **)(param_1 + 0x254) == '\0')) {
      *(void **)(param_1 + 0x2a4) = trigger_heal_think;
      *(int *)(param_1 + 0x29c) = GHIDRA_FIELD(g_healthCabinetTime, 12, 4) + g_unk_00abe908;
      goto LAB_000f47a5;
    }
  }
  *(void **)(param_1 + 0x2a4) = trigger_heal_setup;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
LAB_000f47a5:
  G_SpawnStringExt("healrate",&g_unk_0024a16e,local_20,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x2a9);
  tmp_l2 = strtol(local_20[0],(char **)0x0,10);
  *(long *)(param_1 + 0x2d0) = tmp_l2;
  return;
}

void SP_misc_cabinet_supply(int param_1)
{
  if ((GHIDRA_FIELD(g_gametype, 12, 4) == 8) && ((g_DMOptions[0xc] & 0x80) != 0)) {
    G_FreeEntity(param_1);
    return;
  }
  *(uint32_t *)(param_1 + 0x134) = 0xc1a00000;
  *(uint32_t *)(param_1 + 0x138) = 0xc1a00000;
  *(uint32_t *)(param_1 + 0x13c) = 0;
  *(uint32_t *)(param_1 + 0x140) = 0x41a00000;
  *(uint32_t *)(param_1 + 0x144) = 0x41a00000;
  *(uint32_t *)(param_1 + 0x148) = 0x42700000;
  G_SetOrigin(param_1,param_1 + 0x5c);
  G_SetAngle(param_1,param_1 + 0x74);
  *(uint32_t *)(param_1 + 4) = 0x30;
  *(uint32_t *)(param_1 + 0x1d4) = 1;
  *(uint32_t *)(param_1 + 0x14c) = 1;
  trap_LinkEntity(param_1);
  return;
}

void SP_trigger_ammo(int param_1)
{
  int tmp_i1;
  long tmp_l2;
  char *local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0xf49b9;
  tmp_i1 = VectorCompare(param_1 + 0x74,&vec3_origin);
  if (tmp_i1 == 0) {
    G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  }
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
  }
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(uint32_t *)(param_1 + 0x128) = 1;
  *(void **)(param_1 + 0x2b0) = ammo_touch;
  G_SpawnStringExt("ammototal",&g_unk_0024bfa6,local_20,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x347);
  tmp_l2 = strtol(local_20[0],(char **)0x0,10);
  *(long *)(param_1 + 0x2c8) = tmp_l2;
  if (tmp_l2 < 1) {
    *(uint32_t *)(param_1 + 0x2c8) = 0xffffd8f1;
    *(uint32_t *)(param_1 + 0x2e4) = 0xffffd8f1;
    *(uint32_t *)(param_1 + 0x264) = 0;
    *(uint32_t *)(param_1 + 4) = 0x32;
    if ((*(char **)(param_1 + 0x254) == (char *)0x0) || (**(char **)(param_1 + 0x254) == '\0'))
    goto LAB_000f4ac5;
  }
  else {
    *(long *)(param_1 + 0x2e4) = tmp_l2;
    *(uint32_t *)(param_1 + 0x264) = 0;
    *(uint32_t *)(param_1 + 4) = 0x32;
    if ((*(char **)(param_1 + 0x254) == (char *)0x0) || (**(char **)(param_1 + 0x254) == '\0')) {
      *(void **)(param_1 + 0x2a4) = trigger_ammo_think;
      *(int *)(param_1 + 0x29c) = GHIDRA_FIELD(g_ammoCabinetTime, 12, 4) + g_unk_00abe908;
      goto LAB_000f4ac5;
    }
  }
  *(void **)(param_1 + 0x2a4) = trigger_ammo_setup;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
LAB_000f4ac5:
  G_SpawnStringExt("ammorate",&g_unk_00258b23,local_20,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x35f);
  tmp_l2 = strtol(local_20[0],(char **)0x0,10);
  *(long *)(param_1 + 0x2d0) = tmp_l2;
  return;
}

void SP_func_timer(int param_1)
{
  uint32_t tmp_u1;
  
  G_SpawnFloatExt("random",&g_unk_0024bfa6,param_1 + 0x310,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x38f);
  G_SpawnFloatExt(&g_unk_0023f11d,&g_unk_00258b23,param_1 + 0x30c,
                  "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x390);
  *(void **)(param_1 + 0x2b4) = func_timer_use;
  *(void **)(param_1 + 0x2a4) = func_timer_think;
  if (*(float *)(param_1 + 0x30c) <= *(float *)(param_1 + 0x310)) {
    *(float *)(param_1 + 0x310) = *(float *)(param_1 + 0x30c) - 0.1;
    tmp_u1 = vtos(param_1 + 0x5c);
    G_Printf("func_timer at %s has random >= wait\n",tmp_u1);
  }
  if ((*(byte *)(param_1 + 0x1a8) & 1) != 0) {
    *(int *)(param_1 + 0x2f0) = param_1;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  }
  *(uint32_t *)(param_1 + 0x128) = 1;
  return;
}

void SP_trigger_once(int param_1)
{
  int tmp_i1;
  
  *(void **)(param_1 + 0x2b0) = Touch_Multi;
  *(void **)(param_1 + 0x2b4) = Use_Multi;
  *(uint32_t *)(param_1 + 0x30c) = 0xbf800000;
  tmp_i1 = VectorCompare(param_1 + 0x74,&vec3_origin);
  if (tmp_i1 == 0) {
    G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  }
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
  }
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(uint32_t *)(param_1 + 0x128) = 1;
  trap_LinkEntity(param_1);
  return;
}

void trigger_aidoor_stayopen(int param_1,int param_2)
{
  char *tmp_pc1;
  int tmp_i2;
  
  if ((((*(int *)(param_2 + 400) != 0) && (0 < *(int *)(param_2 + 0x2c8))) &&
      (tmp_pc1 = *(char **)(param_1 + 0x254), tmp_pc1 != (char *)0x0)) && (*tmp_pc1 != '\0')) {
    tmp_i2 = G_FindByTargetnameFast(0,tmp_pc1,*(uint32_t *)(param_1 + 0x5bc));
    if ((tmp_i2 != 0) && ((*(int *)(tmp_i2 + 0x1e4) == 1 || (*(int *)(tmp_i2 + 0x1e4) == 8)))) {
      *(int *)(tmp_i2 + 0x29c) = (int)ROUND((float)g_unk_00abe908 + *(float *)(tmp_i2 + 0x30c) + 3000.0)
      ;
      return;
    }
  }
  return;
}

void SP_gas(void)
{
  return;
}

void SP_trigger_flagonly(int param_1)
{
  int tmp_i1;
  double tmp_d2;
  char *local_10;
  
  *(void **)(param_1 + 0x2b0) = Touch_flagonly;
  tmp_i1 = VectorCompare(param_1 + 0x74,&vec3_origin);
  if (tmp_i1 == 0) {
    G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  }
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
  }
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(uint32_t *)(param_1 + 0x128) = 1;
  G_SpawnStringExt("score",&g_unk_0024a16e,&local_10,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x45c);
  tmp_d2 = strtod(local_10,(char **)0x0);
  *(float *)(param_1 + 0x3fc) = (float)tmp_d2;
  *(uint32_t *)(param_1 + 4) = 0x2c;
  trap_LinkEntity(param_1);
  return;
}

void SP_trigger_flagonly_multiple(int param_1)
{
  int tmp_i1;
  double tmp_d2;
  char *local_10;
  
  *(void **)(param_1 + 0x2b0) = Touch_flagonly_multiple;
  tmp_i1 = VectorCompare(param_1 + 0x74,&vec3_origin);
  if (tmp_i1 == 0) {
    G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  }
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
  }
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(uint32_t *)(param_1 + 0x128) = 1;
  G_SpawnStringExt("score",&g_unk_0024a16e,&local_10,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x478);
  tmp_d2 = strtod(local_10,(char **)0x0);
  *(float *)(param_1 + 0x3fc) = (float)tmp_d2;
  *(uint32_t *)(param_1 + 4) = 0x2d;
  trap_LinkEntity(param_1);
  return;
}

void SP_trigger_objective_info(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  uint tmp_u5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint32_t tmp_u8;
  uint8_t *tmp_pu9;
  double tmp_d10;
  uint8_t *local_848;
  uint32_t local_840;
  char *local_828;
  uint32_t local_824;
  uint32_t local_820;
  uint32_t local_81c;
  uint32_t local_818 [255];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xf50dd;
  local_81c = 0;
  tmp_u4 = 0;
  do {
    tmp_u5 = tmp_u4;
    *(uint32_t *)((int)local_818 + tmp_u5) = 0;
    *(uint32_t *)((int)local_818 + tmp_u5 + 4) = 0;
    tmp_u4 = tmp_u5 + 8;
  } while (tmp_u5 + 8 < 0x3f8);
  *(uint32_t *)((int)local_818 + tmp_u5 + 8) = 0;
  nitrox_GetConfigstring(g_unk_02a983b4 + 0x261,local_41c,0x400);
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    G_FreeEntity(param_1);
    return;
  }
  if (*(int *)(param_1 + 0x3a8) == 0) {
    G_Error("\'trigger_objective_info\' does not have a \'track\' \n");
  }
  if (((*(byte *)(param_1 + 0x1a8) & 4) != 0) && (*(int *)(param_1 + 0x38c) == 0)) {
    G_Error("\'trigger_objective_info\' has override flag set but no override text\n");
  }
  G_SpawnIntExt("objflags",&g_unk_0024bfa6,&local_820,
                "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x5ab);
  tmp_i6 = G_SpawnStringExt("customimage",&g_unk_0026ea14,&local_824,
                           "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x5ad);
  if (tmp_i6 == 0) {
    tmp_i6 = G_SpawnStringExt("customaxisimage",&g_unk_0026ea14,&local_824,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x5b0);
    local_840 = 0;
    if (tmp_i6 != 0) {
      local_840 = G_ShaderIndex(local_824);
    }
    tmp_i6 = G_SpawnStringExt("customalliesimage",&g_unk_0026ea14,&local_824,
                             "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x5b6);
    if (tmp_i6 == 0) {
      tmp_i6 = G_SpawnStringExt("customalliedimage",&g_unk_0026ea14,&local_824,
                               "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x5b8)
      ;
      tmp_u7 = 0;
      if (tmp_i6 == 0) goto LAB_000f5203;
    }
    tmp_u7 = G_ShaderIndex(local_824);
  }
  else {
    tmp_u7 = G_ShaderIndex(local_824);
    local_840 = tmp_u7;
  }
LAB_000f5203:
  local_848 = &g_unk_0026ea14;
  tmp_u8 = va("%i",(param_1 + -0x93e4a0 >> 9) * -0x55555555);
  Info_SetValueForKey(local_41c,&g_unk_0025feb2,tmp_u8);
  tmp_u8 = va("%i",local_820);
  Info_SetValueForKey(local_41c,&g_unk_0024d8f6,tmp_u8);
  tmp_u8 = va("%i",local_840);
  Info_SetValueForKey(local_41c,"r",tmp_u8);
  tmp_u7 = va("%i",tmp_u7);
  Info_SetValueForKey(local_41c,&g_unk_0026dcfc,tmp_u7);
  tmp_u7 = va("%i",*(uint32_t *)(param_1 + 0x1a8));
  Info_SetValueForKey(local_41c,&g_unk_0024e6ea,tmp_u7);
  tmp_pu9 = *(uint8_t **)(param_1 + 0x248);
  if (*(uint8_t **)(param_1 + 0x248) == (uint8_t *)0x0) {
    tmp_pu9 = local_848;
  }
  Info_SetValueForKey(local_41c,&g_unk_0023bf57,tmp_pu9);
  Q_strncpyz(&local_81c,*(uint32_t *)(param_1 + 0x3a8),0x400);
  Nit_RemoveWordInString(&local_81c,&g_unk_00251d18);
  Info_SetValueForKey(local_41c,&g_unk_0026176c,&local_81c);
  if (0x11 < g_unk_02a983b4) {
    G_Error("Exceeded maximum number of \'trigger_objective_info\' entities\n");
  }
  G_SpawnStringExt("score",&g_unk_0024bfa6,&local_828,
                   "/home/nitrox/Desktop/nitmodsvn/tags/2.3/src/game/g_trigger.c",0x5d2);
  tmp_d10 = strtod(local_828,(char **)0x0);
  *(float *)(param_1 + 0x3fc) = (float)tmp_d10;
  tmp_i6 = VectorCompare(param_1 + 0x74,&vec3_origin);
  if (tmp_i6 == 0) {
    G_SetMovedir(param_1 + 0x74,param_1 + 0x270);
  }
  if (*(int *)(param_1 + 0x1b4) != 0) {
    trap_SetBrushModel(param_1,*(int *)(param_1 + 0x1b4));
  }
  *(uint32_t *)(param_1 + 0x14c) = 0x40000000;
  *(uint32_t *)(param_1 + 0x128) = 1;
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
  tmp_u7 = va("%i",*(uint32_t *)(param_1 + 0x108));
  Info_SetValueForKey(local_41c,"i",tmp_u7);
  nitrox_SetConfigstring(g_unk_02a983b4 + 0x261,local_41c);
  tmp_i6 = g_unk_02a983b4 + 1;
  *(int *)(param_1 + 0x108) = g_unk_02a983b4;
  g_unk_02a983b4 = tmp_i6;
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0xfffffffe;
  *(uint32_t *)(param_1 + 4) = 0xc;
  if (*(int *)(param_1 + 0x254) == 0) {
    trap_LinkEntity(param_1);
  }
  else {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 300;
    *(void **)(param_1 + 0x2a4) = Think_SetupObjectiveInfo;
  }
  nitrox_AddEntityToEntityArray(&TriggerEntities,param_1);
  return;
}

void SP_trigger_concussive_dust(uint32_t param_1)
{
  G_Printf("trigger_concussive_dust is obsolote, delete it please \n");
  G_FreeEntity(param_1);
  return;
}

