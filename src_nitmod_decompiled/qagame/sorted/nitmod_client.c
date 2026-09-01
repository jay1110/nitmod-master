/* Client think, connect, spectator, revive — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_client.h"

void ClientImpacts(int param_1,int param_2)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  uint32_t local_54 [16];
  uint32_t uStack_14;
  
  uStack_14 = 0x4d349;
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)local_54 + tmp_u3) = 0;
    *(uint32_t *)((int)local_54 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0x38);
  tmp_i6 = *(int *)(param_2 + 100);
  if (0 < tmp_i6) {
    tmp_i7 = 0;
    do {
      if (tmp_i7 < 1) {
        if (tmp_i7 == 0) {
          tmp_i5 = 0;
LAB_0004d3c1:
          tmp_i6 = *(int *)(param_2 + 0x68 + tmp_i5 * 4);
          tmp_i5 = tmp_i6 * 0x600;
          tmp_pu1 = g_entities + tmp_i5;
          if (((*(int *)(param_1 + 400) != 0) && ((g_entities[tmp_i5 + 0x128] & 8) != 0)) &&
             (*(int *)(*(int *)(g_entities + tmp_i5 + 400) + 0x154) == 0)) {
            PushBot(param_1,tmp_pu1);
          }
          if ((((*(byte *)(param_1 + 0x128) & 8) != 0) &&
              (*(int *)(param_1 + 0x94) == *(int *)(g_entities + tmp_i6 * 0x600))) &&
             ((*(int *)(g_entities + tmp_i6 * 0x600 + 400) != 0 &&
              (*(int *)(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 0x154) == 0)))) {
            PushBot(tmp_pu1,param_1);
          }
          if (*(void **)(g_entities + tmp_i6 * 0x600 + 0x2b0) == (void *)0x0) {
            tmp_i6 = *(int *)(param_2 + 100);
          }
          else {
            (**(void **)(g_entities + tmp_i6 * 0x600 + 0x2b0))(tmp_pu1,param_1,local_54);
            tmp_i6 = *(int *)(param_2 + 100);
          }
        }
      }
      else {
        tmp_i2 = *(int *)(param_2 + 0x68 + tmp_i7 * 4);
        if (*(int *)(param_2 + 0x68) != tmp_i2) {
          tmp_i4 = 0;
          do {
            tmp_i4 = tmp_i4 + 1;
            tmp_i5 = tmp_i7;
            if (tmp_i4 == tmp_i7) goto LAB_0004d3c1;
          } while (*(int *)(param_2 + 0x68 + tmp_i4 * 4) != tmp_i2);
        }
      }
      tmp_i7 = tmp_i7 + 1;
    } while (tmp_i7 < tmp_i6);
  }
  return;
}

void SpectatorThink(int param_1,int param_2)
{
  byte tmp_b1;
  byte tmp_b2;
  uint tmp_u3;
  int tmp_i4;
  uint tmp_u5;
  int tmp_i6;
  byte tmp_b7;
  int local_160 [70];
  void *local_48;
  void *local_44;
  
  tmp_i6 = *(int *)(param_1 + 400);
  tmp_i4 = *(int *)(tmp_i6 + 0x5a0) * 0x600;
  if (((*(int *)(g_entities + tmp_i4 + 0x194) == 0) || (*(int *)(g_entities + tmp_i4 + 400) == 0)) ||
     ((*(int *)(g_entities + tmp_i4 + 0x260) != *(int *)(param_1 + 0x260) &&
      ((*(int *)(*(int *)(g_entities + tmp_i4 + 400) + 0x16c) == 0 &&
       ((*(byte *)(tmp_i6 + 0xd) & 0x10) == 0)))))) {
    *(uint32_t *)(tmp_i6 + 0x5a0) = 0xffffffff;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x5a4) = 0;
  }
  else {
    *(uint32_t *)(tmp_i6 + 0x5a4) =
         *(uint32_t *)(g_entities + *(int *)(tmp_i6 + 0x5a0) * 0x600 + 0x2c8);
  }
  if (*(int *)(tmp_i6 + 0xbc0) != 2) {
    *(uint32_t *)(tmp_i6 + 4) = 2;
    *(uint32_t *)(tmp_i6 + 0x40) = 800;
    if (*(int *)(tmp_i6 + 0x474) != 0) {
      *(uint32_t *)(tmp_i6 + 0x40) = 0x960;
    }
    if (((*(byte *)(tmp_i6 + 0xd) & 0x40) == 0) || (g_unk_02a99a78 == 0)) {
      if (*(int *)(tmp_i6 + 0xf6c) != 0) {
        *(uint32_t *)(tmp_i6 + 4) = 1;
      }
    }
    else {
      *(uint32_t *)(tmp_i6 + 4) = 4;
    }
    tmp_u5 = 0;
    do {
      *(uint32_t *)((int)local_160 + tmp_u5) = 0;
      *(uint32_t *)((int)local_160 + tmp_u5 + 4) = 0;
      tmp_u5 = tmp_u5 + 8;
    } while (tmp_u5 < 0x140);
    *(uint32_t *)((int)local_160 + tmp_u5) = 0;
    local_160[1] = tmp_i6 + 0x52a0;
    local_160[2] = *(uint32_t *)(tmp_i6 + 0x99c);
    tmp_u5 = 0;
    do {
      *(uint32_t *)((int)local_160 + tmp_u5 + 0xc) = *(uint32_t *)(param_2 + tmp_u5);
      tmp_u5 = tmp_u5 + 4;
    } while (tmp_u5 < 0x1c);
    local_160[0x43] = tmp_i6 + 0xc30;
    local_160[0x11] = 0x10001;
    local_48 = trap_TraceCapsuleNoEnts;
    local_44 = trap_PointContents;
    local_160[0] = tmp_i6;
    Pmove(local_160);
    if ((*(byte *)(tmp_i6 + 0xf78) & 0x40) != 0) {
      Cmd_Activate_f(param_1);
    }
    *(uint32_t *)(param_1 + 0x5c) = *(uint32_t *)(tmp_i6 + 0x14);
    *(uint32_t *)(param_1 + 0x60) = *(uint32_t *)(tmp_i6 + 0x18);
    *(uint32_t *)(param_1 + 100) = *(uint32_t *)(tmp_i6 + 0x1c);
    G_TouchTriggers(param_1);
    trap_UnlinkEntity(param_1);
  }
  if ((*(byte *)(param_1 + 0x1b2) & 1) != 0) {
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x52b0) = 20000;
  }
  tmp_u5 = *(uint *)(tmp_i6 + 0xf70);
  *(uint *)(tmp_i6 + 0xf74) = tmp_u5;
  tmp_b1 = *(byte *)(param_2 + 4);
  *(uint *)(tmp_i6 + 0xf70) = (uint)tmp_b1;
  tmp_u3 = *(uint *)(tmp_i6 + 0xf7c);
  *(uint *)(tmp_i6 + 0xf80) = tmp_u3;
  tmp_b2 = *(byte *)(param_2 + 5);
  tmp_b7 = tmp_b1 & 0x40;
  *(uint *)(tmp_i6 + 0xf7c) = (uint)tmp_b2;
  if (((tmp_b7 == 0) || ((tmp_u5 & 0x40) != 0)) || (*(int *)(tmp_i6 + 0xbc0) == 2)) {
    if ((((tmp_b1 & 1) == 0) || ((tmp_u5 & 1) != 0)) || (tmp_b7 != 0)) {
      if ((((tmp_b2 & 1) == 0) || ((tmp_u3 & 1) != 0)) || (tmp_b7 != 0)) {
        if (((*(int *)(tmp_i6 + 3000) == 3) && (*(int *)(tmp_i6 + 0xbc0) == 2)) &&
           ((((tmp_b7 != 0 && ((tmp_u5 & 0x40) == 0)) || ('\0' < *(char *)(param_2 + 0x16))) &&
            ((tmp_i6 = G_allowFollow(param_1,1), tmp_i6 != 0 &&
             (tmp_i6 = G_allowFollow(param_1,2), tmp_i6 != 0)))))) {
          StopFollowing(param_1);
        }
      }
      else {
        Cmd_FollowCycle_f(param_1,0xffffffff);
      }
    }
    else {
      Cmd_FollowCycle_f(param_1,1);
    }
  }
  else {
    G_SpectatorAttackFollow(param_1);
  }
  return;
}

uint32_t ClientInactivityTimer(int param_1)
{
  bool tmp_b1;
  int *tmp_pi2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint32_t tmp_u6;
  int tmp_i7;
  
  tmp_i5 = *(int *)(param_1 + 3000);
  if ((((int)GHIDRA_FIELD(g_inactivity, 12, 4) < 1) && (tmp_i5 - 1U < 2)) ||
     (((int)GHIDRA_FIELD(g_spectatorInactivity, 12, 4) < 1 && (tmp_i5 == 3)))) {
    *(int *)(param_1 + 0xfb4) = g_unk_00abe908 + 60000;
    *(uint32_t *)(param_1 + 0xfb8) = 0;
    return 1;
  }
  if ((int)GHIDRA_FIELD(sv_privateClients, 12, 4) < 1) {
    tmp_i7 = 0;
  }
  else {
    tmp_pi2 = (int *)(level + 0x5ac);
    tmp_i7 = 0;
    do {
      if (*tmp_pi2 != 0) {
        tmp_i7 = tmp_i7 + 1;
      }
      tmp_pi2 = tmp_pi2 + 0x1537;
    } while (tmp_pi2 != (int *)(level + 0x5ac + GHIDRA_FIELD(sv_privateClients, 12, 4) * 0x54dc));
  }
  if (((((*(uint *)(param_1 + 0x5c4) & 0xffffff) == 0) && ((*(byte *)(param_1 + 0x5b5) & 1) == 0))
      && ((*(byte *)(param_1 + 0x5b4) & 1) == 0)) &&
     ((((*(byte *)(param_1 + 0x5b5) & 0x30) == 0 && (*(int *)(param_1 + 4) != 3)) &&
      (((*(byte *)(param_1 + 0xd) & 0x40) == 0 &&
       (((*(byte *)(param_1 + 0x6a) & 8) == 0 || (*(int *)(param_1 + 0xa4) != 0x2e)))))))) {
    tmp_i3 = param_1 - level >> 2;
    tmp_i4 = tmp_i3 * -0x66e64f79;
    tmp_b1 = (int)GHIDRA_FIELD(sv_privateClients, 12, 4) <= tmp_i4;
    if (tmp_i5 == 3) {
      if ((((*(int *)(param_1 + 0xbc0) != 2) || ((g_inactivityOptions[0xc] & 1) == 0)) &&
          (*(int *)(param_1 + 0xf34) == 0)) &&
         (((((int)GHIDRA_FIELD(sv_privateClients, 12, 4) <= tmp_i7 || (tmp_b1)) &&
           ((tmp_i7 - GHIDRA_FIELD(sv_privateClients, 12, 4)) + g_unk_00abe900 <= g_unk_00abe938)) ||
          ((g_inactivityOptions[0xc] & 2) != 0)))) goto LAB_0004de79;
LAB_0004e00e:
      *(uint32_t *)(param_1 + 0xfb8) = 0;
      tmp_i7 = GHIDRA_FIELD(g_spectatorInactivity, 12, 4);
      goto LAB_0004ddf7;
    }
    if (*(int *)(param_1 + 0xf34) == 0) {
LAB_0004de79:
      tmp_i5 = nitrox_CheckPermission(g_entities + tmp_i3 * -0x65dcd600,9);
      if (tmp_i5 == 0) {
LAB_0004dece:
        if (*(int *)(param_1 + 0x5e8) == 0) {
          if (*(int *)(param_1 + 0xfb8) == 0) {
            if (*(int *)(param_1 + 3000) != 3) {
              if (g_unk_00abe908 <= GHIDRA_FIELD(g_inactivity, 12, 4) * -500 + *(int *)(param_1 + 0xfb4)) {
                return 1;
              }
              tmp_u6 = va("pop \"^8INACTIVITY WARNING: ^7%i seconds until moving to spectators for inactivity!\""
                         ,(int)GHIDRA_FIELD(g_inactivity, 12, 4) / 2);
              trap_SendServerCommand(tmp_i4,tmp_u6);
              G_Printf("%is inactivity warning issued to: %s\n",(int)GHIDRA_FIELD(g_inactivity, 12, 4) / 2,
                       param_1 + 0x5f8);
              *(uint32_t *)(param_1 + 0xfb8) = 1;
              return 1;
            }
            if ((((!tmp_b1) && (tmp_i7 < (int)GHIDRA_FIELD(sv_privateClients, 12, 4))) ||
                (g_unk_00abe938 < (g_unk_00abe900 + tmp_i7) - GHIDRA_FIELD(sv_privateClients, 12, 4))) &&
               ((g_inactivityOptions[0xc] & 2) == 0)) {
              return 1;
            }
            if (g_unk_00abe908 <= GHIDRA_FIELD(g_spectatorInactivity, 12, 4) * -500 + *(int *)(param_1 + 0xfb4)) {
              return 1;
            }
            tmp_u6 = va("pop \"^8INACTIVITY WARNING: ^7%i seconds until inactivity drop!\"",
                       (int)GHIDRA_FIELD(g_spectatorInactivity, 12, 4) / 2);
            trap_SendServerCommand(tmp_i4,tmp_u6);
            G_Printf("%is spectator inactivity warning issued to: %s\n",
                     (int)GHIDRA_FIELD(g_spectatorInactivity, 12, 4) / 2,param_1 + 0x5f8);
            *(uint32_t *)(param_1 + 0xfb8) = 1;
            return 1;
          }
          if (*(int *)(param_1 + 0xfb4) < g_unk_00abe908) {
            if (*(int *)(param_1 + 3000) != 3) {
              tmp_i5 = 60000;
              if (GHIDRA_FIELD(g_spectatorInactivity, 12, 4) != 0) {
                tmp_i5 = GHIDRA_FIELD(g_spectatorInactivity, 12, 4) * 1000;
              }
              *(int *)(param_1 + 0xfb4) = g_unk_00abe908 + tmp_i5;
              *(uint32_t *)(param_1 + 0xfb8) = 0;
              SetTeam(g_entities + tmp_i3 * -0x65dcd600,&g_unk_0024e6ea,1,0,0,0);
              tmp_u6 = va("pop \"^8INACTIVITY: ^7%s^7 moved to spectators\"",param_1 + 0x5f8);
              trap_SendServerCommand(0xffffffff,tmp_u6);
              return 1;
            }
            if ((((tmp_b1) || ((int)GHIDRA_FIELD(sv_privateClients, 12, 4) <= tmp_i7)) &&
                ((g_unk_00abe900 + tmp_i7) - GHIDRA_FIELD(sv_privateClients, 12, 4) <= g_unk_00abe938)) ||
               ((g_inactivityOptions[0xc] & 2) != 0)) {
              trap_DropClient((param_1 - level >> 2) * -0x66e64f79,"Dropped due to inactivity",0);
              return 0;
            }
          }
        }
        return 1;
      }
      if (*(int *)(param_1 + 3000) == 3) goto LAB_0004e00e;
      if ((g_inactivityOptions[0xc] & 4) != 0) goto LAB_0004dece;
    }
    *(uint32_t *)(param_1 + 0xfb8) = 0;
  }
  else {
    *(uint32_t *)(param_1 + 0xfb8) = 0;
    tmp_i7 = GHIDRA_FIELD(g_spectatorInactivity, 12, 4);
    if (tmp_i5 == 3) goto LAB_0004ddf7;
  }
  tmp_i7 = GHIDRA_FIELD(g_inactivity, 12, 4);
LAB_0004ddf7:
  *(int *)(param_1 + 0xfb4) = tmp_i7 * 1000 + g_unk_00abe908;
  return 1;
}

void ClientTimerActions(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int local_24;
  uint local_20;
  
  tmp_i4 = IsClass(param_1,1);
  tmp_u3 = GHIDRA_FIELD(g_medics, 12, 4);
  if (((tmp_i4 == 0) || ((GHIDRA_FIELD(g_medics, 12, 4) & 0x20) == 0)) && (3 < GHIDRA_FIELD(g_war, 12, 4) - 1)) {
    tmp_i4 = *(int *)(param_1 + 400);
    param_2 = param_2 + *(int *)(tmp_i4 + 0xfd0);
    *(int *)(tmp_i4 + 0xfd0) = param_2;
    if ((tmp_u3 & 0x40) == 0) {
      local_20 = -(uint)((tmp_u3 & 0x80) == 0) & 2;
      local_24 = local_20 + 1;
    }
    else {
      local_20 = 1;
      local_24 = 2;
    }
    tmp_i1 = *(int *)(tmp_i4 + 0xf4);
    tmp_i2 = *(int *)(tmp_i4 + 0xe0);
    while (999 < param_2) {
      *(int *)(tmp_i4 + 0xfd0) = param_2 + -1000;
      tmp_i6 = IsClass(param_1,1);
      if ((tmp_i6 == 0) || ((*(uint *)(tmp_i4 + 0x68) & 0x200001) != 0)) {
        if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) goto LAB_0004e400;
LAB_0004e399:
        if (((GHIDRA_FIELD(g_medics, 12, 4) & 0x10) != 0) &&
           ((*(byte *)(*(int *)(param_1 + 400) + 0xed8) & 0x20) != 0)) goto LAB_0004e333;
        tmp_i6 = *(int *)(param_1 + 0x2c8);
        if ((tmp_i1 < tmp_i6) && (1 < tmp_i6)) {
          *(int *)(param_1 + 0x2c8) = tmp_i6 + -1;
        }
      }
      else {
        if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
LAB_0004e400:
          if ((g_DMOptions[0xc] & 2) == 0) goto LAB_0004e399;
        }
LAB_0004e333:
        tmp_i6 = *(int *)(param_1 + 0x2c8);
        if (tmp_i6 < tmp_i2) {
          tmp_i5 = tmp_i6 + local_24;
          if (tmp_i2 < tmp_i6 + local_24) {
            tmp_i5 = tmp_i2;
          }
          *(int *)(param_1 + 0x2c8) = tmp_i5;
        }
        else if ((tmp_i2 != tmp_i1) && (tmp_i6 < tmp_i1)) {
          tmp_i5 = tmp_i6 + local_20;
          if (tmp_i1 < (int)(tmp_i6 + local_20)) {
            tmp_i5 = tmp_i1;
          }
          *(int *)(param_1 + 0x2c8) = tmp_i5;
        }
      }
      param_2 = *(int *)(tmp_i4 + 0xfd0);
    }
  }
  return;
}

void ClientIntermissionThink(int param_1)
{
  *(uint *)(param_1 + 0x68) = *(uint *)(param_1 + 0x68) & 0xfffffd7f;
  *(uint32_t *)(param_1 + 0xf74) = *(uint32_t *)(param_1 + 0xf70);
  *(uint *)(param_1 + 0xf70) = (uint)*(byte *)(param_1 + 0x5b4);
  *(uint32_t *)(param_1 + 0xf80) = *(uint32_t *)(param_1 + 0xf7c);
  *(uint *)(param_1 + 0xf7c) = (uint)*(byte *)(param_1 + 0x5b5);
  return;
}

void ClientEvents(uint32_t *param_1,uint param_2)
{
  uint *tmp_pu1;
  int *tmp_pi2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  int local_88;
  uint local_84;
  int local_80;
  int local_74;
  uint32_t local_6c;
  uint32_t local_68;
  float local_64;
  uint32_t local_60;
  uint32_t local_5c;
  float local_58;
  uint8_t local_54 [52];
  int local_20;
  
  tmp_i3 = param_1[100];
  tmp_i5 = *(int *)(tmp_i3 + 0x6c);
  if ((int)param_2 < (int)(tmp_i5 - 4U)) {
    param_2 = tmp_i5 - 4U;
  }
  if ((int)param_2 < tmp_i5) {
    do {
      while (tmp_i4 = *(int *)(tmp_i3 + ((param_2 & 3) + 0x1c) * 4), tmp_i4 < 0x24) {
        if (0x20 < tmp_i4) {
          tmp_i5 = param_1[100];
          if ((GHIDRA_FIELD(g_noAttacklInvul, 12, 4) == 0) || (g_unk_00abe908 - *(int *)(tmp_i5 + 0x970) < 0x1f5)) {
            tmp_i5 = *(int *)(tmp_i5 + 0x16c);
          }
          else {
            *(uint32_t *)(tmp_i5 + 0x154) = 0;
            tmp_i5 = *(int *)(param_1[100] + 0x16c);
          }
          if ((tmp_i5 != 0) && (tmp_i5 = jP_CheckDisguise(param_1), tmp_i5 == 0)) {
            *(uint32_t *)(param_1[100] + 0x16c) = 0;
          }
          FireWeapon(param_1);
          tmp_i5 = *(int *)(tmp_i3 + 0x6c);
          goto LAB_0004e8f0;
        }
        if (5 < tmp_i4 - 0xcU) goto LAB_0004e8f0;
        if (param_1[1] != 1) goto LAB_0004e921;
        local_88 = param_1[0x25] * 0x600 + g_unk_00abe8a4;
        if (*(int *)(local_88 + 400) == 0) {
          local_6c = param_1[0x5a];
          local_68 = param_1[0x5b];
          local_64 = (float)param_1[0x5c];
          local_58 = local_64 - 4.0;
          local_60 = local_6c;
          local_5c = local_68;
          trap_Trace(local_54,&local_6c,0,0,&local_60,*param_1,0x6000001);
          local_88 = local_20 * 0x600 + g_unk_00abe8a4;
        }
        switch(tmp_i4) {
        case 0xd:
          if ((GHIDRA_FIELD(g_goomba, 12, 4) != 0) && (local_88 != 0)) {
            local_84 = 500;
            local_80 = 0;
            goto LAB_0004eb36;
          }
          local_84 = 500;
          goto LAB_0004eb79;
        case 0xe:
          local_80 = 0xfa;
          local_84 = 10;
          break;
        case 0xf:
          local_80 = 0xfa;
          local_84 = 0xf;
          break;
        case 0x10:
          local_80 = 500;
          local_84 = 0x19;
          break;
        case 0x11:
          local_80 = 1000;
          local_84 = 0x32;
          break;
        default:
          if ((((GHIDRA_FIELD(g_goombaFlags, 12, 4) & 2) == 0) && (local_88 != 0)) &&
             (local_74 = *(int *)(local_88 + 400), local_74 != 0)) {
            tmp_i5 = param_1[100];
            if (((*(int *)(local_74 + 3000) == *(int *)(tmp_i5 + 3000)) &&
                ((GHIDRA_FIELD(g_goombaFlags, 12, 4) & 4) != 0)) || (GHIDRA_FIELD(g_goomba, 12, 4) == 0)) goto LAB_0004e927;
            local_80 = 0;
            local_84 = 0;
            if (*(int *)(local_88 + 0x2cc) == 0) goto LAB_0004e927;
            goto LAB_0004ecc2;
          }
          tmp_i5 = param_1[100];
          goto LAB_0004e927;
        }
        if (GHIDRA_FIELD(g_goomba, 12, 4) == 0) {
LAB_0004ebf6:
          *(int *)(param_1[100] + 0x10) = local_80;
          *(uint *)(param_1[100] + 0xc) = *(uint *)(param_1[100] + 0xc) | 0x40;
LAB_0004eb79:
          param_1[0xb0] = g_unk_00abe908 + 200;
LAB_0004eba4:
          G_Damage(param_1,0,0,0,0,local_84,0,0x1f);
          tmp_i5 = param_1[100];
        }
        else {
          if (local_88 == 0) {
LAB_0004eb5a:
            if (local_80 != 0) goto LAB_0004ebf6;
            goto LAB_0004eb79;
          }
LAB_0004eb36:
          local_74 = *(int *)(local_88 + 400);
          if ((local_74 == 0) || (*(int *)(local_88 + 0x2cc) == 0)) goto LAB_0004eb5a;
LAB_0004ecc2:
          if (((GHIDRA_FIELD(g_gametype, 12, 4) == 8) || ((GHIDRA_FIELD(g_goombaFlags, 12, 4) & 1) == 0)) ||
             (tmp_i5 = param_1[100], *(int *)(local_74 + 3000) != *(int *)(tmp_i5 + 3000))) {
            tmp_u6 = 5;
            if (local_84 != 0) {
              tmp_u6 = local_84;
            }
            if (local_80 != 0) {
              *(int *)(local_74 + 0x10) = local_80;
              tmp_pu1 = (uint *)(*(int *)(local_88 + 400) + 0xc);
              *tmp_pu1 = *tmp_pu1 | 0x40;
            }
            *(int *)(local_88 + 0x2c0) = g_unk_00abe908 + 200;
            if (0 < (int)param_1[0xb2]) {
              if ((GHIDRA_FIELD(g_goombaFlags, 12, 4) & 0x10) == 0) {
                G_Damage(local_88,param_1,param_1,0,0,tmp_u6 * GHIDRA_FIELD(g_goomba, 12, 4),0,0x3a);
              }
              else {
                G_Damage(local_88,param_1,param_1,0,0,*(uint32_t *)(local_88 + 0x2c8),0x20,0x3a);
              }
            }
            if (tmp_u6 < 6) {
              nitmod_SoundEvent(local_88,5);
LAB_0004e921:
              tmp_i5 = param_1[100];
              goto LAB_0004e927;
            }
            if ((GHIDRA_FIELD(g_goombaFlags, 12, 4) & 8) != 0) goto LAB_0004e921;
            local_84 = (uint)ROUND((float)tmp_u6 * 0.2);
            goto LAB_0004eba4;
          }
        }
LAB_0004e927:
        param_2 = param_2 + 1;
        *(uint32_t *)(tmp_i5 + 0x5318) = 0;
        tmp_i5 = *(int *)(tmp_i3 + 0x6c);
        if (tmp_i5 <= (int)param_2) {
          return;
        }
      }
      if (tmp_i4 == 0x26) {
        *(uint32_t *)(param_1[100] + 0x16c) = 0;
        if (GHIDRA_FIELD(g_noAttacklInvul, 12, 4) != 0) {
          *(uint32_t *)(param_1[100] + 0x154) = 0;
        }
        mountedmg42_fire(param_1);
joined_r0x0004ea5c:
        if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
          tmp_i5 = param_1[100];
          tmp_i4 = BG_WeapStatForWeapon(0x1d);
          tmp_pi2 = (int *)(tmp_i5 + 0xcac + tmp_i4 * 0x14);
          *tmp_pi2 = *tmp_pi2 + 1;
          tmp_i5 = *(int *)(tmp_i3 + 0x6c);
          goto LAB_0004e8f0;
        }
      }
      else {
        if (tmp_i4 != 0x5f) {
          if (tmp_i4 != 0x25) goto LAB_0004e8f0;
          if (GHIDRA_FIELD(g_noAttacklInvul, 12, 4) != 0) {
            *(uint32_t *)(param_1[100] + 0x154) = 0;
          }
          *(uint32_t *)(param_1[100] + 0x16c) = 0;
          mg42_fire(param_1);
          goto joined_r0x0004ea5c;
        }
        if (GHIDRA_FIELD(g_noAttacklInvul, 12, 4) != 0) {
          *(uint32_t *)(param_1[100] + 0x154) = 0;
        }
        ThrowKnife(param_1);
      }
      tmp_i5 = *(int *)(tmp_i3 + 0x6c);
LAB_0004e8f0:
      param_2 = param_2 + 1;
    } while ((int)param_2 < tmp_i5);
  }
  return;
}

void ClientThink_checkWeapons(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int *tmp_pi5;
  int tmp_i6;
  
  tmp_i2 = *(int *)(param_1 + 400);
  if (((*(int *)(tmp_i2 + 0x54d8) != 0) || ((*(byte *)(tmp_i2 + 0xd) & 0x10) != 0)) ||
     (*(int *)(param_1 + 0x2c8) < 1)) {
    return;
  }
  if ((GHIDRA_FIELD(g_war, 12, 4) == 4) && (*(int *)(tmp_i2 + 0x5394) == 0)) {
    G_RemoveWeapons(param_1);
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xa4) = 1;
    G_AddEvent(param_1,0x19,0);
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x5394) = 1;
  }
  tmp_pi5 = (int *)(ammoTableMP + 0x44);
  tmp_i1 = tmp_i2 + 0x3d4;
  tmp_i6 = 0;
  do {
    while (*tmp_pi5 == 0) {
LAB_0004f720:
      tmp_i6 = tmp_i6 + 1;
      tmp_pi5 = tmp_pi5 + 0x12;
      if (tmp_i6 == 0x34) {
        return;
      }
    }
    tmp_i3 = COM_BitCheck(tmp_i1,tmp_i6);
    if ((tmp_i3 != 0) && (tmp_i3 = G_IsWeaponDisabled(param_1,tmp_i6,1,1), tmp_i3 != 0)) {
      if (tmp_i6 - 0x24U < 2) {
        COM_BitClear(*(int *)(param_1 + 400) + 0x3d4);
        if (*(int *)(tmp_i2 + 0xbe4) != 0) {
          *(uint32_t *)(tmp_i2 + 0xbe4) = 0;
          goto LAB_0004f850;
        }
      }
      else {
        G_DropWeapon(param_1,tmp_i6);
        tmp_i3 = G_IsWeaponDisabled(param_1,*(uint32_t *)(tmp_i2 + 0xbdc),1,0);
        if (tmp_i3 != 0) {
          tmp_i4 = BG_PlayerClassForPlayerState(*(uint32_t *)(param_1 + 400));
          tmp_i4 = *(int *)(tmp_i4 + 0x10);
          *(int *)(tmp_i2 + 0xbdc) = tmp_i4;
        }
        else {
          tmp_i4 = *(int *)(tmp_i2 + 0xbdc);
        }
        if (*(int *)(tmp_i2 + 0xbcc) == tmp_i4) {
          tmp_i4 = G_IsWeaponDisabled(param_1,tmp_i4,1,0);
          if (tmp_i4 != 0) goto LAB_0004f978;
          if (tmp_i3 == 0) goto LAB_0004f813;
        }
        else {
          *(int *)(tmp_i2 + 0xbcc) = tmp_i4;
          tmp_i3 = G_IsWeaponDisabled(param_1,tmp_i4,1,0);
          if (tmp_i3 != 0) {
LAB_0004f978:
            tmp_i3 = BG_PlayerClassForPlayerState(*(uint32_t *)(param_1 + 400));
            *(uint32_t *)(tmp_i2 + 0xbcc) = *(uint32_t *)(tmp_i3 + 0x10);
          }
        }
LAB_0004f850:
        ClientUserinfoChanged((param_1 + -0x93e4a0 >> 9) * -0x55555555);
      }
LAB_0004f813:
      tmp_i3 = COM_BitCheck(tmp_i1,0x2b);
      if ((tmp_i3 != 0) && (tmp_i3 = EntHasAdren(param_1), tmp_i3 == 0)) {
        COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x2b);
      }
      nitmod_cp(param_1,8);
      goto LAB_0004f720;
    }
    tmp_i3 = COM_BitCheck(tmp_i1,0x2b);
    if ((tmp_i3 == 0) || (tmp_i3 = EntHasAdren(param_1), tmp_i3 != 0)) goto LAB_0004f720;
    tmp_i6 = tmp_i6 + 1;
    tmp_pi5 = tmp_pi5 + 0x12;
    COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x2b);
    if (tmp_i6 == 0x34) {
      return;
    }
  } while( true );
}

void ClientThink_doPmove(int param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  float tmp_f3;
  void *tmp_pc4;
  void *tmp_pc5;
  uint tmp_u6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  uint8_t *tmp_pu10;
  int tmp_i11;
  uint8_t *local_1b4;
  int local_198 [18];
  uint8_t local_14e;
  uint32_t auStack_138 [7];
  uint8_t *local_11c;
  uint32_t local_118;
  uint32_t local_114;
  uint32_t local_110;
  uint32_t local_10c;
  uint32_t local_108;
  uint32_t local_104;
  uint32_t local_100;
  int local_fc;
  int local_f8 [32];
  uint32_t local_78;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  int local_54;
  uint local_50;
  uint32_t local_4c;
  void *local_48;
  void *local_44;
  uint32_t local_3c [7];
  void *local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x4fa09;
  tmp_i7 = *(int *)(param_1 + 400);
  if (g_unk_02a99a78 == 0) {
    if (*(int *)(tmp_i7 + 0xf6c) == 0) {
      if (*(int *)(tmp_i7 + 4) != 6) {
        if ((*(int *)(tmp_i7 + 0xd0) < 1) || ((*(byte *)(tmp_i7 + 0x6a) & 0x80) != 0)) {
          *(uint32_t *)(tmp_i7 + 4) = 3;
        }
        else {
          *(uint *)(tmp_i7 + 4) = ~-(uint)(*(int *)(tmp_i7 + 0x539c) == 0) & 4;
        }
      }
    }
    else {
      *(uint32_t *)(tmp_i7 + 4) = 1;
    }
  }
  else {
    *(uint8_t *)(param_2 + 4) = 0;
    *(uint8_t *)(param_2 + 0x14) = 0;
    *(uint8_t *)(param_2 + 0x15) = 0;
    *(uint8_t *)(param_2 + 0x16) = 0;
    *(uint8_t *)(param_2 + 5) = 0;
    *(uint8_t *)(param_2 + 0x17) = 0;
    if (g_unk_02a99a78 != 0) {
      *(uint32_t *)(tmp_i7 + 4) = 4;
    }
  }
  *(uint32_t *)(tmp_i7 + 0x5a8) = 3;
  *(int *)(tmp_i7 + 0x38) = (int)ROUND((float)GHIDRA_FIELD(g_gravity, 8, 4));
  tmp_f3 = ROUND((float)GHIDRA_FIELD(g_speed, 8, 4));
  *(int *)(tmp_i7 + 0x40) = (int)tmp_f3;
  if (*(int *)(tmp_i7 + 0x1050) != 0) {
    *(int *)(tmp_i7 + 0x40) =
         (int)ROUND((double)*(int *)(tmp_i7 + 0x1050) * 0.01 * (double)(int)tmp_f3);
  }
  tmp_i2 = *(int *)(tmp_i7 + 0x6c);
  tmp_pi1 = local_198 + 0xe;
  tmp_u6 = 0;
  *(float *)(tmp_i7 + 0xfd4) = (float)*(int *)(tmp_i7 + 0x48c) / 255.0;
  do {
    *(uint32_t *)((int)tmp_pi1 + tmp_u6) = 0;
    *(uint32_t *)((int)local_198 + tmp_u6 + 0x3c) = 0;
    tmp_u6 = tmp_u6 + 8;
  } while (tmp_u6 < 0x140);
  *(uint32_t *)((int)tmp_pi1 + tmp_u6) = 0;
  local_198[0xf] = tmp_i7 + 0x52a0;
  local_198[0x10] = *(uint32_t *)(tmp_i7 + 0x99c);
  tmp_u6 = 0;
  do {
    *(uint32_t *)((int)local_198 + tmp_u6 + 0x44) = *(uint32_t *)(param_2 + tmp_u6);
    tmp_u6 = tmp_u6 + 4;
  } while (tmp_u6 < 0x1c);
  tmp_u6 = 0;
  do {
    *(uint32_t *)((int)auStack_138 + tmp_u6) = *(uint32_t *)(tmp_i7 + 0x5cc + tmp_u6);
    tmp_u6 = tmp_u6 + 4;
  } while (tmp_u6 < 0x1c);
  local_48 = trap_TraceCapsule;
  local_20 = G_SendVoiceChat;
  tmp_u6 = *(uint *)(tmp_i7 + 0x68);
  if (*(int *)(tmp_i7 + 4) == 3) {
    tmp_u6 = tmp_u6 | 1;
    local_11c = (uint8_t *)0x10001;
    *(uint *)(tmp_i7 + 0x68) = tmp_u6;
  }
  else {
    local_11c = &g_unk_02010001;
  }
  tmp_i11 = g_unk_00abe908;
  local_198[0xe] = tmp_i7;
  tmp_pc4 = trap_TraceCapsule;
  tmp_pc5 = G_SendVoiceChat;
  if (((tmp_u6 & 0x200000) != 0) &&
     (tmp_pc4 = local_48, tmp_pc5 = local_20, *(int *)(tmp_i7 + 0x53a0) < g_unk_00abe908)) {
    if (*(int *)(tmp_i7 + 0x5300) == -1) {
      local_1b4 = (uint8_t *)0x0;
    }
    else {
      local_1b4 = g_entities + *(int *)(tmp_i7 + 0x5300) * 0x600;
    }
    tmp_i11 = (-(uint)((GHIDRA_FIELD(g_poison, 12, 4) & 4) == 0) & 0xfffffff7) + 10;
    if (GHIDRA_FIELD(BG_Weapons, 81956, 4) != 0) {
      tmp_i11 = GHIDRA_FIELD(BG_Weapons, 81956, 4);
    }
    tmp_i9 = (-(uint)((GHIDRA_FIELD(g_poison, 12, 4) & 4) == 0) & 0xfffffa56) + 0x5dc;
    if (GHIDRA_FIELD(BG_Weapons, 81960, 4) != 0) {
      tmp_i9 = GHIDRA_FIELD(BG_Weapons, 81960, 4);
    }
    local_48 = trap_TraceCapsule;
    local_20 = G_SendVoiceChat;
    G_Damage(param_1,local_1b4,local_1b4,0,0,tmp_i11 * *(int *)(*(int *)(param_1 + 400) + 0x5304),0,
             0x3b);
    tmp_i11 = g_unk_00abe908;
    *(int *)(tmp_i7 + 0x53a0) = g_unk_00abe908 + tmp_i9;
    tmp_pc4 = local_48;
    tmp_pc5 = local_20;
  }
  local_20 = tmp_pc5;
  local_48 = tmp_pc4;
  local_44 = trap_PointContents;
  local_118 = GHIDRA_FIELD(g_debugMove, 12, 4);
  local_50 = GHIDRA_FIELD(pmove_fixed, 12, 4) | *(uint *)(tmp_i7 + 0x5f4);
  tmp_i9 = *(int *)(tmp_i7 + 3000);
  local_4c = GHIDRA_FIELD(pmove_msec, 12, 4);
  *(uint32_t *)(tmp_i7 + 0xf88) = *(uint32_t *)(tmp_i7 + 0x14);
  local_114 = GHIDRA_FIELD(g_gametype, 12, 4);
  *(uint32_t *)(tmp_i7 + 0xf8c) = *(uint32_t *)(tmp_i7 + 0x18);
  *(uint32_t *)(tmp_i7 + 0xf90) = *(uint32_t *)(tmp_i7 + 0x1c);
  local_10c = (&g_unk_00abe8a4)[(int)(&g_unk_007f66cf + tmp_i9)];
  local_104 = (&g_unk_00abe8ac)[(int)(&g_unk_007f66cf + tmp_i9)];
  local_108 = (&g_unk_00abe8a4)[(int)(&g_unk_007f66d3 + tmp_i9)];
  local_110 = (&g_unk_00abe8ac)[(int)(&g_unk_007f66d3 + tmp_i9)];
  local_100 = (&g_unk_02a98400)[tmp_i9];
  local_54 = tmp_i7 + 0xc30;
  tmp_u6 = 0;
  do {
    *(uint32_t *)((int)local_3c + tmp_u6) = *(uint32_t *)(tmp_i7 + 0xed0 + tmp_u6);
    tmp_u6 = tmp_u6 + 4;
  } while (tmp_u6 < 0x1c);
  *(int *)(tmp_i7 + 0x52b4) = *(int *)(*(int *)(param_1 + 400) + 0xfc0) - tmp_i11;
  if (tmp_i11 - *(int *)(tmp_i7 + 0x970) < 1000) {
    local_14e = (uint8_t)*(uint32_t *)(tmp_i7 + 0xa4);
  }
  Pmove(tmp_pi1);
  tmp_i7 = g_unk_00abe908;
  if (((*(byte *)(param_1 + 0x128) & 8) == 0) && (*(int *)(param_1 + 0x448) < g_unk_00abe908)) {
    G_CheckForCursorHints(param_1);
    tmp_i7 = g_unk_00abe908;
    *(int *)(param_1 + 0x448) = g_unk_00abe908 + 100;
  }
  tmp_i11 = *(int *)(param_1 + 400);
  *(uint *)(param_1 + 0x11c) = *(uint *)(tmp_i11 + 0xc) & 1;
  if (*(int *)(tmp_i11 + 0x6c) != tmp_i2) {
    *(int *)(param_1 + 0x1c0) = tmp_i7;
    *(int *)(param_1 + 0x184) = tmp_i7;
  }
  BG_PlayerStateToEntityState(tmp_i11,param_1,tmp_i7,1);
  *(uint32_t *)(param_1 + 0x304) = local_5c;
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x18);
  *(uint32_t *)(param_1 + 0x300) = local_60;
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x1c);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 0x20);
  *(uint32_t *)(param_1 + 0x134) = local_78;
  *(uint32_t *)(param_1 + 0x138) = local_74;
  *(uint32_t *)(param_1 + 0x13c) = local_70;
  *(uint32_t *)(param_1 + 0x140) = local_6c;
  *(uint32_t *)(param_1 + 0x144) = local_68;
  *(uint32_t *)(param_1 + 0x148) = local_64;
  if (g_unk_02a99a78 == 0) {
    ClientEvents(param_1,tmp_i2);
    tmp_i7 = *(int *)(param_1 + 400);
    if ((*(int *)(tmp_i7 + 0x50) != 0x3ff) && ((*(byte *)(tmp_i7 + 0xc) & 0x20) == 0)) {
      *(uint32_t *)(tmp_i7 + 0x5318) = 0;
    }
  }
  trap_LinkEntity(param_1);
  local_1b4 = *(uint8_t **)(param_1 + 400);
  if (*(int *)((int)local_1b4 + 0xf6c) == 0) {
    G_TouchTriggers(param_1);
    local_1b4 = *(uint8_t **)(param_1 + 400);
  }
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)((int)local_1b4 + 0x14);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)((int)local_1b4 + 0x18);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)((int)local_1b4 + 0x1c);
  tmp_u6 = 0;
  do {
    *(uint32_t *)((int)local_198 + tmp_u6) = 0;
    *(uint32_t *)((int)local_198 + tmp_u6 + 4) = 0;
    tmp_u6 = tmp_u6 + 8;
  } while (tmp_u6 < 0x38);
  tmp_i11 = 0;
  tmp_i7 = local_fc;
  if (0 < local_fc) {
    do {
      if (tmp_i11 < 1) {
        if (tmp_i11 == 0) {
          tmp_i9 = 0;
LAB_0004ff91:
          tmp_i7 = local_f8[tmp_i9];
          tmp_i9 = tmp_i7 * 0x600;
          tmp_pu10 = g_entities + tmp_i9;
          if (((local_1b4 != (uint8_t *)0x0) && ((g_entities[tmp_i9 + 0x128] & 8) != 0)) &&
             (*(int *)(*(int *)(g_entities + tmp_i9 + 400) + 0x154) == 0)) {
            PushBot(param_1,tmp_pu10);
          }
          if ((((*(byte *)(param_1 + 0x128) & 8) != 0) &&
              (*(int *)(param_1 + 0x94) == *(int *)(g_entities + tmp_i7 * 0x600))) &&
             ((*(int *)(g_entities + tmp_i7 * 0x600 + 400) != 0 &&
              (*(int *)(*(int *)(g_entities + tmp_i7 * 0x600 + 400) + 0x154) == 0)))) {
            PushBot(tmp_pu10,param_1);
          }
          if (*(void **)(g_entities + tmp_i7 * 0x600 + 0x2b0) == (void *)0x0) {
            local_1b4 = *(uint8_t **)(param_1 + 400);
            tmp_i7 = local_fc;
          }
          else {
            (**(void **)(g_entities + tmp_i7 * 0x600 + 0x2b0))(tmp_pu10,param_1,local_198);
            local_1b4 = *(uint8_t **)(param_1 + 400);
            tmp_i7 = local_fc;
          }
        }
      }
      else if (local_f8[0] != local_f8[tmp_i11]) {
        tmp_i8 = 0;
        do {
          tmp_i8 = tmp_i8 + 1;
          tmp_i9 = tmp_i11;
          if (tmp_i8 == tmp_i11) goto LAB_0004ff91;
        } while (local_f8[tmp_i8] != local_f8[tmp_i11]);
      }
      tmp_i11 = tmp_i11 + 1;
    } while (tmp_i11 < tmp_i7);
  }
  if (*(int *)((int)local_1b4 + 0x6c) != tmp_i2) {
    *(int *)(param_1 + 0x1c0) = g_unk_00abe908;
  }
  return;
}

void ClientThink_real(uint32_t *param_1)
{
  byte tmp_b1;
  int *tmp_pi2;
  uint tmp_u3;
  int tmp_i4;
  int *tmp_pi5;
  uint32_t tmp_u6;
  uint *tmp_pu7;
  int tmp_i8;
  uint tmp_u9;
  int tmp_i10;
  int tmp_i11;
  long double tmp_l12;
  uint32_t tmp_u13;
  char *tmp_pc14;
  int local_4c;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  uint32_t local_20;
  
  tmp_pi2 = (int *)param_1[100];
  if (tmp_pi2[0x16b] != 2) {
    return;
  }
  if (((*(byte *)((int)param_1 + 9) & 0x80) != 0) && (param_1[0x110] != 0)) {
    tmp_pi2[0x14b1] = *(int *)(param_1[0x110] + 0x178);
    tmp_pi2[0x14b0] = *(int *)(param_1[0x110] + 0x174);
  }
  tmp_pi2[0x71] = 0;
  tmp_i4 = G_AvailableAirstrikes(param_1);
  if (tmp_i4 == 0) {
    tmp_pi2[0x71] = tmp_pi2[0x71] | 1;
  }
  tmp_i4 = G_AvailableArty(param_1);
  if (tmp_i4 == 0) {
    tmp_pi2[0x71] = tmp_pi2[0x71] | 2;
  }
  tmp_i4 = param_1[100];
  *(uint *)(tmp_i4 + 0x5a0) = (uint)*(byte *)(tmp_i4 + 0x5c8);
  tmp_i8 = tmp_pi2[699];
  tmp_pi2[tmp_i8 + 0x27b] = (tmp_pi2[0x14e2] + g_unk_00abe910) - *(int *)(tmp_i4 + 0x5b0);
  if (tmp_i8 + 1 < 0x40) {
    tmp_pi2[699] = tmp_i8 + 1;
    if (GHIDRA_FIELD(g_truePing, 12, 4) != 0) goto LAB_000502e6;
LAB_0005071a:
    tmp_i8 = tmp_pi2[0x11a];
    tmp_pi2[0x27a] = tmp_i8;
  }
  else {
    tmp_pi2[699] = tmp_i8 + -0x3f;
    if (GHIDRA_FIELD(g_truePing, 12, 4) == 0) goto LAB_0005071a;
LAB_000502e6:
    tmp_pi5 = tmp_pi2 + 0x27b;
    tmp_i8 = 0;
    do {
      tmp_i8 = tmp_i8 + *tmp_pi5;
      tmp_pi5 = tmp_pi5 + 1;
    } while (tmp_pi5 != tmp_pi2 + 699);
    if (tmp_i8 < 0) {
      tmp_i8 = tmp_i8 + 0x3f;
    }
    tmp_i8 = tmp_i8 >> 6;
    tmp_pi2[0x27a] = tmp_i8;
  }
  if ((tmp_pi2[0x14e3] != 0) && (GHIDRA_FIELD(g_maxWarp, 12, 4) != 0)) {
    tmp_i10 = G_DoAntiwarp(param_1);
    tmp_i8 = g_unk_00abe910;
    if (tmp_i10 != 0) {
      tmp_i11 = g_unk_00abe910 - g_unk_00abe908;
      tmp_i10 = g_unk_00abe904 - tmp_pi2[0x14e1];
      if ((int)GHIDRA_FIELD(g_maxWarp, 12, 4) < g_unk_00abe904 - tmp_pi2[0x14e1]) {
        tmp_i10 = GHIDRA_FIELD(g_maxWarp, 12, 4);
      }
      tmp_pi2[0x14e4] = 1;
      *tmp_pi2 = tmp_i10 * tmp_i11 + tmp_i8;
    }
    tmp_i8 = tmp_pi2[0x27a];
  }
  tmp_pi2[0x14e3] = 0;
  tmp_pi2[0x14e1] = g_unk_00abe904;
  if (tmp_i8 < 0) {
    tmp_pi2[0x27a] = 0;
  }
  local_4c = *(int *)(tmp_i4 + 0x5b0);
  tmp_i8 = g_unk_00abe908;
  if (g_unk_00abe908 + 200 < local_4c) {
    tmp_i10 = G_DoAntiwarp(param_1);
    tmp_i8 = g_unk_00abe908;
    if (tmp_i10 == 0) {
      local_4c = g_unk_00abe908 + 200;
      *(int *)(tmp_i4 + 0x5b0) = local_4c;
    }
    else {
      local_4c = *(int *)(tmp_i4 + 0x5b0);
    }
  }
  if (local_4c < tmp_i8 + -1000) {
    tmp_i10 = G_DoAntiwarp(param_1);
    tmp_i8 = g_unk_00abe908;
    if (tmp_i10 == 0) {
      local_4c = g_unk_00abe908 + -1000;
      *(int *)(tmp_i4 + 0x5b0) = local_4c;
    }
    else {
      local_4c = *(int *)(tmp_i4 + 0x5b0);
    }
  }
  tmp_pi2[0x14e9] = local_4c + (tmp_i8 - g_unk_00abe910) * 2;
  if (((tmp_pi2[0x2fc] != 0) && (tmp_pi2[0x329] != -1)) &&
     (GHIDRA_FIELD(g_censorMuteTime, 12, 4) * 1000 < tmp_i8 - tmp_pi2[0x329])) {
    trap_SendServerCommand
              (((int)(param_1 + -0x24f928) >> 9) * -0x55555555,
               "print \"^5You\'ve been auto-unmuted. Language penalty lifted.\n\"");
    tmp_pi2[0x2fc] = 0;
    tmp_pi2[0x329] = -1;
    tmp_u13 = va("pop \"^8CENSOR: ^7%s^7 has been auto-unmuted.\"",param_1[100] + 0x5f8);
    trap_SendServerCommand(0xffffffff,tmp_u13);
    G_shrubbot_mute_check(param_1[100] + 0x61c,param_1[100] + 0xaf4);
  }
  tmp_i8 = *(int *)(tmp_i4 + 0x5b0) - *tmp_pi2;
  if (tmp_i8 < 1) {
    local_4c = tmp_i8;
    if (tmp_pi2[0x2f0] != 2) {
      return;
    }
  }
  else {
    local_4c = 200;
    if (tmp_i8 < 0xc9) {
      local_4c = tmp_i8;
    }
  }
  tmp_i8 = G_DoAntiwarp(param_1);
  if ((tmp_i8 == 0) && ((GHIDRA_FIELD(pmove_fixed, 12, 4) != 0 || (tmp_pi2[0x17d] != 0)))) {
    *(int *)(tmp_i4 + 0x5b0) =
         ((*(int *)(tmp_i4 + 0x5b0) + GHIDRA_FIELD(pmove_msec, 12, 4) + -1) / (int)GHIDRA_FIELD(pmove_msec, 12, 4)) *
         GHIDRA_FIELD(pmove_msec, 12, 4);
  }
  if (tmp_pi2[0x14dd] != 0) {
    G_SendScore(param_1);
    nitmod_TeamScores();
    G_SendKD(param_1);
    tmp_pi2[0x14dd] = 0;
  }
  if (g_unk_00abf994 != 0) {
    tmp_pi2[0x1a] = tmp_pi2[0x1a] & 0xfffffd7f;
    tmp_pi2[0x3dd] = tmp_pi2[0x3dc];
    tmp_pi2[0x3dc] = (uint)*(byte *)(tmp_pi2 + 0x16d);
    tmp_pi2[0x3e0] = tmp_pi2[0x3df];
    tmp_pi2[0x3df] = (uint)*(byte *)((int)tmp_pi2 + 0x5b5);
    return;
  }
  if ((*(byte *)(param_1 + 0x4a) & 8) == 0) {
    if (tmp_pi2[0x1536] == 0) {
      tmp_i8 = param_1[100];
      if (((GHIDRA_FIELD(n_NxAC_CvarScan, 12, 4) != 0) && (0 < *(int *)(tmp_i8 + 0xb24))) &&
         (*(int *)(tmp_i8 + 0xb24) < g_unk_00abe908)) {
        NxAC_ScanClientCvars(param_1,0);
        tmp_i8 = param_1[100];
      }
      if ((0 < *(int *)(tmp_i8 + 0xb20)) && (*(int *)(tmp_i8 + 0xb20) < g_unk_00abe908)) {
        *(uint32_t *)(tmp_i8 + 0xb20) = 0;
        NxAC_ScanClientCvars(param_1,*(uint32_t *)(param_1[100] + 0xb14));
      }
      tmp_i8 = ClientInactivityTimer(tmp_pi2);
      if (tmp_i8 == 0) {
        return;
      }
      if ((*(byte *)(param_1 + 0x4a) & 8) != 0) goto LAB_000504eb;
    }
    if (2000 < g_unk_00abe908 - tmp_pi2[0x25b]) {
      G_SendMapEntityInfo(param_1);
      tmp_pi2[0x25b] = g_unk_00abe908;
    }
  }
LAB_000504eb:
  if (((((*(byte *)(tmp_i4 + 0x5b7) & 1) == 0) || ((*(uint *)(tmp_i4 + 0x5c4) & 0xffffff) != 0)) ||
      (*(char *)(tmp_i4 + 0x5b5) != '\0')) || (*(char *)(tmp_i4 + 0x5c7) != '\0')) {
    param_1[0x4a] = param_1[0x4a] & 0xfffe7fff;
  }
  if ((tmp_pi2[0x2ee] == 3) || ((*(byte *)((int)tmp_pi2 + 0xd) & 0x40) != 0)) {
    SpectatorThink(param_1,tmp_i4 + 0x5b0);
    return;
  }
  if ((tmp_pi2[0x14e0] != 0) && (tmp_pi2[0x14e0] < g_unk_00abe908)) {
    tmp_pi2[0x14e0] = 0;
    param_1[0x4a] = param_1[0x4a] & 0xffffffdf;
  }
  if ((tmp_pi2[1] != 3) && (45000 < g_unk_02a99b84 - tmp_pi2[0x25a])) {
    if (tmp_pi2[0x415] != 0) {
      if ((tmp_pi2[0x415] & 0xcU) == 0xc) {
        G_AddSkillPoints(param_1,0,0x41000000);
        if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
          tmp_pc14 = "combatstate super-hot";
          tmp_u13 = 0x41000000;
          goto LAB_00050de9;
        }
      }
      else if ((tmp_pi2[0x415] & 6U) == 6) {
        G_AddSkillPoints(param_1,0,0x40a00000);
        if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
          tmp_pc14 = "combatstate hot";
          tmp_u13 = 0x40a00000;
          goto LAB_00050de9;
        }
      }
      else {
        G_AddSkillPoints(param_1,0,0x40000000);
        if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
          tmp_pc14 = "combatstate warm";
          tmp_u13 = 0x40000000;
LAB_00050de9:
          G_DebugAddSkillPoints(param_1,0,tmp_u13,tmp_pc14);
        }
      }
    }
    tmp_pi2[0x25a] = g_unk_02a99b84;
    tmp_pi2[0x415] = 0;
  }
  ClientThink_doPmove(param_1,tmp_i4 + 0x5b0);
  tmp_pi2[0x3dd] = tmp_pi2[0x3dc];
  tmp_u9 = ~tmp_pi2[0x3dc] & (uint)*(byte *)(tmp_i4 + 0x5b4);
  tmp_pi2[0x3dc] = (uint)*(byte *)(tmp_i4 + 0x5b4);
  tmp_u3 = tmp_pi2[0x3df];
  tmp_pi2[0x3de] = tmp_u9;
  tmp_pi2[0x3e0] = tmp_u3;
  tmp_b1 = *(byte *)(tmp_i4 + 0x5b5);
  tmp_pi2[0x3df] = (uint)tmp_b1;
  tmp_pi2[0x3e1] = ~tmp_u3 & (uint)tmp_b1;
  if ((tmp_u9 & 0x40) != 0) {
    Cmd_Activate_f(param_1);
  }
  if ((*(byte *)((int)param_1 + 0x1b2) & 1) != 0) {
    *(uint32_t *)(param_1[100] + 0x52b0) = 20000;
  }
  tmp_i8 = param_1[100];
  tmp_i10 = *(int *)(tmp_i8 + 0x5a0) * 0x600;
  if (((*(int *)(g_entities + tmp_i10 + 0x194) == 0) || (*(int *)(g_entities + tmp_i10 + 400) == 0))
     || ((*(int *)(g_entities + tmp_i10 + 0x260) != param_1[0x98] &&
         ((*(int *)(*(int *)(g_entities + tmp_i10 + 400) + 0x16c) == 0 &&
          ((*(byte *)(tmp_i8 + 0xd) & 0x10) == 0)))))) {
    *(uint32_t *)(tmp_i8 + 0x5a0) = 0xffffffff;
    *(uint32_t *)(param_1[100] + 0x5a4) = 0;
  }
  else {
    *(uint32_t *)(tmp_i8 + 0x5a4) =
         *(uint32_t *)(g_entities + *(int *)(tmp_i8 + 0x5a0) * 0x600 + 0x2c8);
  }
  Bot_Util_CheckForSuicide(param_1);
  if ((tmp_pi2[0x34] < 1) && ((*(byte *)((int)tmp_pi2 + 0x6a) & 0x80) == 0)) {
    WolfFindMedic(param_1);
    if (g_unk_02a99b84 <= tmp_pi2[0x3ec]) {
      return;
    }
    if ((*(byte *)(param_1[100] + 0xd) & 0x40) != 0) {
      return;
    }
    if ('\0' < *(char *)(tmp_i4 + 0x5c6)) {
      if (((GHIDRA_FIELD(g_gametype, 12, 4) == 5) || (-1 < tmp_pi2[0x4d])) &&
         ((*(byte *)(param_1 + 0x4a) & 8) == 0)) {
        trap_SendServerCommand(((int)(param_1 + -0x24f928) >> 9) * -0x55555555,"reqforcespawn");
      }
      else {
        limbo(param_1,-0xaf < tmp_pi2[0x34]);
      }
    }
    if (((int)GHIDRA_FIELD(g_forcerespawn, 12, 4) < 1) ||
       (g_unk_02a99b84 - tmp_pi2[0x3ec] <= GHIDRA_FIELD(g_forcerespawn, 12, 4) * 1000)) {
      tmp_i4 = tmp_pi2[0x34];
      if (-0xaf < tmp_i4) {
        return;
      }
    }
    else {
      tmp_i4 = tmp_pi2[0x34];
    }
    limbo(param_1,-0xaf < tmp_i4);
    return;
  }
  if (((g_unk_02a9969c != 0) && ((*(byte *)(param_1 + 0x4a) & 8) == 0)) &&
     ((*(uint *)(param_1[100] + 0x68) & 0x200001) == 0)) {
    if ((*(int *)(g_unk_02a9969c + 0xa4) == 0) || (tmp_pi2[0x2ee] != 1)) {
      if ((*(int *)(g_unk_02a9969c + 0xa8) == 0) || (tmp_pi2[0x2ee] != 2)) goto LAB_0005080f;
      tmp_u13 = 2;
    }
    else {
      tmp_u13 = 1;
    }
    tmp_i4 = G_SweepForLandmines(param_1 + 0x5a,0x43800000,tmp_u13);
    if (tmp_i4 != 0) {
      nitmod_cp(param_1,9);
    }
  }
LAB_0005080f:
  if ((g_debugPlayerHitboxes[0xc] & 2) != 0) {
    local_34 = (float)param_1[0x50];
    local_30 = (float)param_1[0x51];
    local_2c = (float)param_1[0x52];
    local_28 = (float)param_1[0x4d];
    local_24 = (float)param_1[0x4e];
    local_20 = param_1[0x4f];
    if ((int)GHIDRA_FIELD(g_hitboxes, 12, 4) < 1) {
      if ((g_realBody[0xc] & 1) != 0) {
        local_34 = local_34 - 3.0;
        local_28 = local_28 + 3.0;
        local_30 = local_30 - 3.0;
        local_24 = local_24 + 3.0;
      }
      tmp_l12 = (long double)nitrox_HitboxHeight(param_1,0);
      local_2c = (float)tmp_l12;
    }
    tmp_u13 = *param_1;
    tmp_u6 = tv(0,0,0x3f800000);
    G_RailBox(param_1 + 0x5a,&local_28,&local_34,tmp_u6,tmp_u13);
    tmp_pu7 = (uint *)G_BuildHead(param_1,1);
    tmp_u3 = *tmp_pu7;
    tmp_u13 = tv(0,0,0x3f800000);
    G_RailBox(tmp_pu7 + 0x5a,tmp_pu7 + 0x4d,tmp_pu7 + 0x50,tmp_u13,tmp_u3 | 0x400);
    G_FreeEntity(tmp_pu7);
    tmp_pu7 = (uint *)G_BuildLeg(param_1,1);
    if (tmp_pu7 != (uint *)0x0) {
      tmp_u3 = *tmp_pu7;
      tmp_u13 = tv(0,0,0x3f800000);
      G_RailBox(tmp_pu7 + 0x5a,tmp_pu7 + 0x4d,tmp_pu7 + 0x50,tmp_u13,tmp_u3 | 0x800);
      G_FreeEntity(tmp_pu7);
    }
  }
  if (g_unk_02a99a78 == 0) {
    ClientTimerActions(param_1,local_4c);
  }
  return;
}

void ClientThink_cmd(int param_1,int param_2)
{
  int tmp_i1;
  uint tmp_u2;
  
  tmp_u2 = 0;
  tmp_i1 = *(int *)(param_1 + 400);
  do {
    *(uint32_t *)(tmp_i1 + 0x5cc + tmp_u2) = *(uint32_t *)(tmp_i1 + 0x5b0 + tmp_u2);
    tmp_u2 = tmp_u2 + 4;
  } while (tmp_u2 < 0x1c);
  tmp_i1 = *(int *)(param_1 + 400);
  tmp_u2 = 0;
  do {
    *(uint32_t *)(tmp_i1 + 0x5b0 + tmp_u2) = *(uint32_t *)(param_2 + tmp_u2);
    tmp_u2 = tmp_u2 + 4;
  } while (tmp_u2 < 0x1c);
  ClientThink_real();
  return;
}

void ClientThink(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  uint32_t local_38;
  byte local_31;
  
  tmp_i3 = param_1 * 0x600;
  tmp_pu4 = g_entities + tmp_i3;
  trap_GetUsercmd(param_1,&local_38);
  if ((local_31 == 0) || ((g_entities[tmp_i3 + 0x128] & 8) != 0)) {
    tmp_i1 = G_DoAntiwarp(tmp_pu4);
  }
  else {
    tmp_u2 = (uint)local_31;
    if ((local_31 & 1) != 0) {
      tmp_u2 = local_31 & 0xfffffffe;
    }
    *(uint *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb2c) =
         *(uint *)(*(int *)(g_entities + tmp_i3 + 400) + 0xb2c) | tmp_u2;
    tmp_i1 = G_DoAntiwarp(tmp_pu4);
  }
  if (tmp_i1 == 0) {
    tmp_i1 = *(int *)(g_entities + tmp_i3 + 400);
    tmp_u2 = 0;
    do {
      *(uint32_t *)(tmp_i1 + 0x5cc + tmp_u2) = *(uint32_t *)(tmp_i1 + 0x5b0 + tmp_u2);
      tmp_u2 = tmp_u2 + 4;
    } while (tmp_u2 < 0x1c);
    tmp_i3 = *(int *)(g_entities + tmp_i3 + 400);
    tmp_u2 = 0;
    do {
      *(uint32_t *)(tmp_i3 + 0x5b0 + tmp_u2) = *(uint32_t *)((int)&local_38 + tmp_u2);
      tmp_u2 = tmp_u2 + 4;
    } while (tmp_u2 < 0x1c);
    ClientThink_real(tmp_pu4);
  }
  else {
    etpro_AddUsercmd(param_1,&local_38);
    DoClientThinks(tmp_pu4);
  }
  return;
}

void SpectatorClientEndFrame(int param_1)
{
  uint *tmp_pu1;
  byte tmp_b2;
  int tmp_i3;
  int tmp_i4;
  uint tmp_u5;
  uint tmp_u6;
  uint32_t tmp_u7;
  uint32_t tmp_u8;
  uint32_t tmp_u9;
  uint32_t tmp_u10;
  uint32_t tmp_u11;
  uint32_t tmp_u12;
  uint32_t tmp_u13;
  uint32_t tmp_u14;
  int tmp_i15;
  int tmp_i16;
  uint8_t *tmp_pu17;
  uint tmp_u18;
  uint32_t *tmp_pu19;
  uint32_t *tmp_pu20;
  uint32_t *tmp_pu21;
  bool tmp_b22;
  
  tmp_u7 = GHIDRA_FIELD(g_gamestate, 12, 4);
  tmp_i15 = *(int *)(param_1 + 400);
  if ((*(int *)(tmp_i15 + 0xbc0) != 2) && ((*(byte *)(tmp_i15 + 0xd) & 0x40) == 0)) {
    return;
  }
  if (((GHIDRA_FIELD(g_gamestate, 12, 4) == 0) && (GHIDRA_FIELD(g_instantSpawn, 12, 4) == 0)) ||
     (g_unk_02a99b84 < *(int *)(tmp_i15 + 0xfb0))) {
    if (*(int *)(tmp_i15 + 3000) == 1) {
      tmp_i16 = (g_unk_02a99b84 + g_unk_02a99a6c) - g_unk_00abe918;
      tmp_pu17 = g_redlimbotime;
LAB_00051c3f:
      tmp_i3 = *(int *)(tmp_pu17 + 0xc);
      tmp_i4 = *(int *)(tmp_i15 + 0x6a0);
      *(int *)(tmp_i15 + 0x6a0) = tmp_i16 % tmp_i3;
      tmp_b22 = tmp_i16 % tmp_i3 < tmp_i4;
    }
    else {
      tmp_b22 = false;
      if (*(int *)(tmp_i15 + 3000) == 2) {
        tmp_i16 = (g_unk_02a99b84 + g_unk_02a99a68) - g_unk_00abe918;
        tmp_pu17 = g_bluelimbotime;
        goto LAB_00051c3f;
      }
    }
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) goto LAB_00051a40;
LAB_00051b13:
    if ((((int)GHIDRA_FIELD(g_maxlives, 12, 4) < 1) &&
        (((int)GHIDRA_FIELD(g_alliedmaxlives, 12, 4) < 1 && ((int)GHIDRA_FIELD(g_axismaxlives, 12, 4) < 1)))) ||
       (tmp_pu20 = *(uint32_t **)(param_1 + 400), tmp_pu20[0x4d] != 0)) {
LAB_00051be0:
      if (tmp_b22) {
LAB_00051ab0:
        reinforce(param_1);
        return;
      }
      goto LAB_00051be8;
    }
    if ((tmp_b22) && (GHIDRA_FIELD(g_maxlivesRespawnPenalty, 12, 4) != 0)) {
      if ((int)tmp_pu20[0x4e] < 1) goto LAB_00051ab0;
      tmp_pu20[0x4e] = tmp_pu20[0x4e] + -1;
      tmp_pu20 = *(uint32_t **)(param_1 + 400);
    }
LAB_00051b40:
    tmp_i15 = tmp_pu20[0x2f1];
    if (tmp_i15 != -1) goto LAB_00051b4f;
LAB_00051bfd:
    tmp_b2 = *(byte *)((int)tmp_pu20 + 0xd);
    tmp_i16 = g_unk_00abea44;
  }
  else {
    tmp_b22 = *(int *)(tmp_i15 + 3000) != 3;
    if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) goto LAB_00051b13;
LAB_00051a40:
    if (tmp_u7 != 0) goto LAB_00051be0;
    if (((g_unk_02a98484 == 0) && (g_unk_00abef74 == g_unk_02a983ac)) && (g_unk_00abef78 == g_unk_02a983b0)) {
      tmp_pu20 = *(uint32_t **)(param_1 + 400);
      if (((int)tmp_pu20[0x3ec] <= g_unk_02a99b84) && (tmp_pu20[0x2ee] != 3)) goto LAB_00051ab0;
      goto LAB_00051b40;
    }
LAB_00051be8:
    tmp_pu20 = *(uint32_t **)(param_1 + 400);
    tmp_i15 = tmp_pu20[0x2f1];
    if (tmp_i15 == -1) goto LAB_00051bfd;
LAB_00051b4f:
    tmp_i16 = tmp_i15;
    if (tmp_i15 != -2) goto LAB_00051b5a;
    tmp_b2 = *(byte *)((int)tmp_pu20 + 0xd);
    tmp_i16 = g_unk_00abea48;
  }
  if ((tmp_b2 & 0x40) == 0) {
    return;
  }
LAB_00051b5a:
  tmp_i3 = level;
  if (-1 < tmp_i16) {
    tmp_pu19 = (uint32_t *)(tmp_i16 * 0x54dc + level);
    if ((tmp_pu19[0x16b] == 2) && (tmp_pu19[0x2ee] != 3)) {
      tmp_u5 = tmp_pu20[0x1a];
      tmp_u6 = tmp_pu19[0x1a];
      tmp_u7 = tmp_pu20[0x11a];
      if ((tmp_pu20[0x2ee] == 3) || ((*(byte *)((int)tmp_pu20 + 0xd) & 0x40) == 0)) {
        tmp_u18 = 0x5ac;
        tmp_pu21 = tmp_pu20;
        if (((uint)tmp_pu20 & 4) != 0) {
          tmp_u13 = *tmp_pu19;
          tmp_pu21 = tmp_pu20 + 1;
          tmp_pu19 = tmp_pu19 + 1;
          *tmp_pu20 = tmp_u13;
          tmp_u18 = 0x5a8;
        }
        for (tmp_u18 = tmp_u18 >> 2; tmp_u18 != 0; tmp_u18 = tmp_u18 - 1) {
          *tmp_pu21 = *tmp_pu19;
          tmp_pu19 = tmp_pu19 + 1;
          tmp_pu21 = tmp_pu21 + 1;
        }
        tmp_pu1 = (uint *)(*(int *)(param_1 + 400) + 0xc);
        *tmp_pu1 = *tmp_pu1 | 0x1000;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x110) = 0;
      }
      else {
        tmp_u13 = tmp_pu20[0x44];
        tmp_u8 = tmp_pu20[0x4d];
        tmp_u9 = tmp_pu20[0x4e];
        tmp_u10 = tmp_pu20[0x51];
        tmp_u11 = tmp_pu20[0x52];
        tmp_u12 = tmp_pu20[4];
        tmp_u18 = 0x5ac;
        tmp_pu21 = tmp_pu20;
        if (((uint)tmp_pu20 & 4) != 0) {
          tmp_u14 = *tmp_pu19;
          tmp_pu21 = tmp_pu20 + 1;
          tmp_pu19 = tmp_pu19 + 1;
          *tmp_pu20 = tmp_u14;
          tmp_u18 = 0x5a8;
        }
        for (tmp_u18 = tmp_u18 >> 2; tmp_u18 != 0; tmp_u18 = tmp_u18 - 1) {
          *tmp_pu21 = *tmp_pu19;
          tmp_pu19 = tmp_pu19 + 1;
          tmp_pu21 = tmp_pu21 + 1;
        }
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x10) = tmp_u12;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x134) = tmp_u8;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x138) = tmp_u9;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x110) = tmp_u13;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x144) = tmp_u10;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x148) = tmp_u11;
        tmp_pu1 = (uint *)(*(int *)(param_1 + 400) + 0xc);
        *tmp_pu1 = *tmp_pu1 | 0x1000;
        tmp_pu1 = (uint *)(*(int *)(param_1 + 400) + 0xc);
        *tmp_pu1 = *tmp_pu1 | 0x4000;
      }
      *(uint *)(*(int *)(param_1 + 400) + 0x68) = tmp_u5 & 0x4000 | tmp_u6 & 0xffffbfff;
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x468) = tmp_u7;
    }
    else if (-1 < tmp_i15) {
      tmp_pu20[0x2f0] = 1;
      ClientBegin((*(int *)(param_1 + 400) - tmp_i3 >> 2) * -0x66e64f79);
    }
  }
  return;
}

uint32_t StuckInClient(uint8_t *param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  if (0 < g_unk_00abe93c) {
    tmp_i2 = 0;
    do {
      tmp_i1 = (&g_unk_00abe944)[tmp_i2] * 0x600;
      if ((((param_1 != g_entities + tmp_i1) && (*(int *)(g_entities + tmp_i1 + 0x194) != 0)) &&
          (*(int *)(g_entities + tmp_i1 + 400) != 0)) &&
         ((*(int *)(g_entities + tmp_i1 + 0xb4) != 0 && (0 < *(int *)(g_entities + tmp_i1 + 0x2c8)))))
      {
        if ((((*(float *)(g_entities + tmp_i1 + 0x134) + *(float *)(g_entities + tmp_i1 + 0x168) <=
               *(float *)(param_1 + 0x168) + *(float *)(param_1 + 0x140)) &&
             ((*(float *)(param_1 + 0x168) + *(float *)(param_1 + 0x134) <=
               *(float *)(g_entities + tmp_i1 + 0x140) + *(float *)(g_entities + tmp_i1 + 0x168) &&
              (*(float *)(g_entities + tmp_i1 + 0x138) + *(float *)(g_entities + tmp_i1 + 0x16c) <=
               *(float *)(param_1 + 0x16c) + *(float *)(param_1 + 0x144))))) &&
            (*(float *)(param_1 + 0x16c) + *(float *)(param_1 + 0x138) <=
             *(float *)(g_entities + tmp_i1 + 0x16c) + *(float *)(g_entities + tmp_i1 + 0x144))) &&
           ((*(float *)(g_entities + tmp_i1 + 0x13c) + *(float *)(g_entities + tmp_i1 + 0x170) <=
             *(float *)(param_1 + 0x170) + *(float *)(param_1 + 0x148) &&
            (*(float *)(param_1 + 0x170) + *(float *)(param_1 + 0x13c) <=
             *(float *)(g_entities + tmp_i1 + 0x170) + *(float *)(g_entities + tmp_i1 + 0x148))))) {
          return 1;
        }
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 != g_unk_00abe93c);
  }
  return 0;
}

void WolfRevivePushEnt(int param_1,int param_2)
{
  int tmp_i1;
  float local_18;
  float local_14;
  float local_10;
  
  local_10 = 0.0;
  local_18 = *(float *)(param_1 + 0x168) - *(float *)(param_2 + 0x168);
  local_14 = *(float *)(param_1 + 0x16c) - *(float *)(param_2 + 0x16c);
  VectorNormalizeFast(&local_18);
  tmp_i1 = *(int *)(param_1 + 400);
  if (tmp_i1 != 0) {
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + local_18 * 25.0;
    *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) + local_14 * 25.0;
    *(float *)(param_1 + 0x2c) = *(float *)(param_1 + 0x2c) + local_10 * 25.0;
    *(float *)(tmp_i1 + 0x20) = local_18 * 25.0 + *(float *)(tmp_i1 + 0x20);
    *(float *)(*(int *)(param_1 + 400) + 0x24) =
         local_14 * 25.0 + *(float *)(*(int *)(param_1 + 400) + 0x24);
    *(float *)(*(int *)(param_1 + 400) + 0x28) =
         local_10 * 25.0 + *(float *)(*(int *)(param_1 + 400) + 0x28);
  }
  *(float *)(param_2 + 0x24) = *(float *)(param_2 + 0x24) + local_18 * -25.0;
  *(float *)(param_2 + 0x28) = *(float *)(param_2 + 0x28) + local_14 * -25.0;
  *(float *)(param_2 + 0x2c) = *(float *)(param_2 + 0x2c) + 12.0;
  *(float *)(*(int *)(param_2 + 400) + 0x20) =
       local_18 * -25.0 + *(float *)(*(int *)(param_2 + 400) + 0x20);
  *(float *)(*(int *)(param_2 + 400) + 0x24) =
       local_14 * -25.0 + *(float *)(*(int *)(param_2 + 400) + 0x24);
  *(float *)(*(int *)(param_2 + 400) + 0x28) = *(float *)(*(int *)(param_2 + 400) + 0x28) + 12.0;
  return;
}

void WolfReviveBbox(int *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int *tmp_pi4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int *tmp_pi9;
  int tmp_i10;
  float *pfVar11;
  float *pfVar12;
  int local_1054;
  float local_1040;
  float local_103c;
  float local_1038;
  float local_1034;
  float local_1030;
  float local_102c;
  float local_1028;
  float local_1024;
  float local_1020;
  int local_101c [1027];
  
  tmp_pi4 = (int *)G_TestEntityPosition(param_1);
  if ((tmp_pi4 != (int *)0x0) &&
     ((*tmp_pi4 == 0x3fe ||
      ((tmp_i5 = tmp_pi4[100], tmp_i5 != 0 &&
       ((*(int *)(tmp_i5 + 0x140) != 0 || ((*(byte *)(tmp_i5 + 0x69) & 0x80) != 0)))))))) {
    G_DPrintf("WolfReviveBbox: Player stuck in world or MG42 using player\n");
    if (-1 < param_1[0xdd]) {
      *(uint32_t *)(param_1[100] + 0x14) =
           *(uint32_t *)(*(int *)(g_entities + param_1[0xdd] * 0x600 + 400) + 0x14);
      *(uint32_t *)(param_1[100] + 0x18) =
           *(uint32_t *)(*(int *)(g_entities + param_1[0xdd] * 0x600 + 400) + 0x18);
      *(uint32_t *)(param_1[100] + 0x1c) =
           *(uint32_t *)(*(int *)(g_entities + param_1[0xdd] * 0x600 + 400) + 0x1c);
      tmp_i5 = param_1[100];
      param_1[0x5a] = *(int *)(tmp_i5 + 0x14);
      param_1[0x5b] = *(int *)(tmp_i5 + 0x18);
      param_1[0x5c] = *(int *)(tmp_i5 + 0x1c);
      trap_LinkEntity(param_1);
      param_1[0xdd] = -1;
    }
    return;
  }
  tmp_f1 = (float)param_1[0x5a];
  local_1040 = playerMins + tmp_f1;
  tmp_f2 = (float)param_1[0x5b];
  local_103c = g_unk_002b7dd0 + tmp_f2;
  tmp_f3 = (float)param_1[0x5c];
  local_1038 = g_unk_002b7dd4 + tmp_f3;
  local_1034 = tmp_f1 + playerMaxs;
  local_1030 = g_unk_002b7dc4 + tmp_f2;
  local_102c = g_unk_002b7dc8 + tmp_f3;
  pfVar12 = &local_1034;
  pfVar11 = &local_1040;
  tmp_i5 = trap_EntitiesInBox(pfVar11,pfVar12,local_101c,0x400,tmp_f1,tmp_f2,tmp_f3,pfVar11,pfVar12);
  if (tmp_i5 < 1) {
    tmp_i5 = 0;
    G_DPrintf("WolfReviveBbox: Touchnum: %d\n",0);
  }
  else {
    local_1054 = 0;
    tmp_i8 = 0;
    do {
      while( true ) {
        tmp_i10 = local_101c[tmp_i8];
        tmp_i7 = tmp_i10 * 0x600;
        tmp_pi4 = (int *)(g_entities + tmp_i7);
        tmp_i6 = trap_EntityContactCapsule(pfVar11,pfVar12,tmp_pi4);
        if (tmp_i6 != 0) break;
LAB_000524a0:
        tmp_i8 = tmp_i8 + 1;
        if (tmp_i8 == tmp_i5) goto LAB_0005253c;
      }
      tmp_pi9 = (int *)(g_entities + tmp_i7 + 400);
      if ((*tmp_pi9 != 0) && (0 < *(int *)(g_entities + tmp_i7 + 0x2c8))) {
        if (*tmp_pi4 != *param_1) {
          local_1028 = *(float *)(g_entities + tmp_i7 + 0x168) - (float)param_1[0x5a];
          local_1024 = *(float *)(g_entities + tmp_i7 + 0x16c) - (float)param_1[0x5b];
          local_1020 = 0.0;
          VectorNormalizeFast(&local_1028);
          tmp_i10 = *tmp_pi9;
          if (tmp_i10 != 0) {
            *(float *)(g_entities + tmp_i7 + 0x24) =
                 *(float *)(g_entities + tmp_i7 + 0x24) + local_1028 * 25.0;
            *(float *)(g_entities + tmp_i7 + 0x28) =
                 *(float *)(g_entities + tmp_i7 + 0x28) + local_1024 * 25.0;
            *(float *)(g_entities + tmp_i7 + 0x2c) =
                 *(float *)(g_entities + tmp_i7 + 0x2c) + local_1020 * 25.0;
            *(float *)(tmp_i10 + 0x20) = local_1028 * 25.0 + *(float *)(tmp_i10 + 0x20);
            *(float *)(*tmp_pi9 + 0x24) = local_1024 * 25.0 + *(float *)(*tmp_pi9 + 0x24);
            *(float *)(*tmp_pi9 + 0x28) = local_1020 * 25.0 + *(float *)(*tmp_pi9 + 0x28);
          }
          local_1054 = local_1054 + 1;
          param_1[9] = (int)((float)param_1[9] + local_1028 * -25.0);
          param_1[10] = (int)((float)param_1[10] + local_1024 * -25.0);
          param_1[0xb] = (int)((float)param_1[0xb] + 12.0);
          *(float *)(param_1[100] + 0x20) = local_1028 * -25.0 + *(float *)(param_1[100] + 0x20);
          *(float *)(param_1[100] + 0x24) = local_1024 * -25.0 + *(float *)(param_1[100] + 0x24);
          *(float *)(param_1[100] + 0x28) = *(float *)(param_1[100] + 0x28) + 12.0;
        }
        goto LAB_000524a0;
      }
      if ((*(uint *)(g_entities + tmp_i10 * 0x600 + 0x14c) & 0x2010001) == 0) goto LAB_000524a0;
      tmp_i8 = tmp_i8 + 1;
      WolfRevivePushEnt(tmp_pi4,param_1);
      local_1054 = local_1054 + 1;
    } while (tmp_i8 != tmp_i5);
LAB_0005253c:
    tmp_i5 = local_1054;
    G_DPrintf("WolfReviveBbox: Touchnum: %d\n",local_1054);
    if (local_1054 != 0) {
      return;
    }
  }
  G_DPrintf("WolfReviveBbox:  Player is solid now!\n",tmp_i5);
  param_1[0x53] = 0x2000000;
  return;
}

void ClientEndFrame(uint *param_1)
{
  int tmp_i1;
  int tmp_i2;
  float tmp_f3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint *tmp_pu8;
  uint tmp_u9;
  int tmp_i10;
  long double tmp_l11;
  uint8_t local_f0 [4];
  uint8_t local_ec [4];
  uint8_t local_e8 [4];
  uint8_t local_e4 [12];
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  uint local_c4;
  uint32_t uStack_14;
  
  uStack_14 = 0x525a9;
  if (((g_XPDecay[0xc] & 1) != 0) && (g_unk_00abe908 == ((int)g_unk_00abe908 / 60000) * 60000)) {
    G_XPDecay(param_1,0x3c,0);
  }
  tmp_u4 = g_unk_00abe908;
  tmp_u9 = param_1[100];
  if ((*(int *)(tmp_u9 + 0x53a8) + 999 < (int)g_unk_00abe908) && (*(int *)(tmp_u9 + 0x53ac) != 0)) {
    *(int *)(tmp_u9 + 0x53ac) = *(int *)(tmp_u9 + 0x53ac) + -1;
    tmp_u9 = param_1[100];
    if (*(int *)(tmp_u9 + 0x53ac) == 0) {
      *(uint32_t *)(tmp_u9 + 0x53b0) = 0;
      tmp_u9 = param_1[100];
    }
  }
  *(uint32_t *)(tmp_u9 + 0x188) = 0;
  tmp_u9 = param_1[100];
  if ((*(int *)(tmp_u9 + 3000) == 3) || ((*(byte *)(tmp_u9 + 0xd) & 0x40) != 0)) {
    SpectatorClientEndFrame(param_1);
    return;
  }
  tmp_i5 = tmp_u4 - g_unk_00abe910;
  tmp_i6 = 1;
  do {
    tmp_i1 = tmp_i6 + -1;
    if (tmp_i1 != 4) {
      tmp_i2 = tmp_u9 + tmp_i1 * 4;
      tmp_i10 = *(int *)(tmp_i2 + 0x150);
      if (tmp_i10 != 0) {
        if (tmp_i6 - 8U < 4) goto LAB_000526e5;
        if ((tmp_i10 != 0x7fffffff) && (g_unk_02a99a78 != 0)) {
          *(int *)(tmp_i2 + 0x150) = tmp_i10 + tmp_i5;
          tmp_u9 = param_1[100];
          tmp_i10 = *(int *)(tmp_u9 + (tmp_i6 + 0x53) * 4);
        }
        if (tmp_i10 < (int)tmp_u4) {
          *(uint32_t *)(tmp_u9 + 0x150 + tmp_i1 * 4) = 0;
          tmp_u9 = param_1[100];
        }
      }
      if (tmp_i6 == 0x10) break;
    }
LAB_000526e5:
    tmp_i6 = tmp_i6 + 1;
  } while( true );
  *(uint32_t *)(tmp_u9 + 0xf0) = 0;
  tmp_u9 = param_1[100];
  *(int *)(tmp_u9 + 0xf0) = (int)ROUND((float)*(int *)(tmp_u9 + 0xf0) + *(float *)(tmp_u9 + 0xbf4));
  tmp_u9 = param_1[100];
  *(int *)(tmp_u9 + 0xf0) = (int)ROUND((float)*(int *)(tmp_u9 + 0xf0) + *(float *)(tmp_u9 + 0xbf8));
  tmp_u9 = param_1[100];
  *(int *)(tmp_u9 + 0xf0) = (int)ROUND((float)*(int *)(tmp_u9 + 0xf0) + *(float *)(tmp_u9 + 0xbfc));
  tmp_u9 = param_1[100];
  *(int *)(tmp_u9 + 0xf0) = (int)ROUND((float)*(int *)(tmp_u9 + 0xf0) + *(float *)(tmp_u9 + 0xc00));
  tmp_u9 = param_1[100];
  *(int *)(tmp_u9 + 0xf0) = (int)ROUND((float)*(int *)(tmp_u9 + 0xf0) + *(float *)(tmp_u9 + 0xc04));
  tmp_u9 = param_1[100];
  *(int *)(tmp_u9 + 0xf0) = (int)ROUND((float)*(int *)(tmp_u9 + 0xf0) + *(float *)(tmp_u9 + 0xc08));
  tmp_u9 = param_1[100];
  *(int *)(tmp_u9 + 0xf0) = (int)ROUND((float)*(int *)(tmp_u9 + 0xf0) + *(float *)(tmp_u9 + 0xc0c));
  tmp_i5 = *(int *)(param_1[100] + 0xf0);
  tmp_i6 = tmp_i5 + 0x7fff;
  if (-1 < tmp_i5) {
    tmp_i6 = tmp_i5;
  }
  *(int *)(param_1[100] + 0xdc) = tmp_i6 >> 0xf;
  *(int *)(param_1[100] + 0xf0) = *(int *)(param_1[100] + 0xf0) % 0x8000;
  if (g_unk_02a99a78 != 0) {
    tmp_i5 = tmp_u4 - g_unk_00abe910;
    *(int *)(param_1[100] + 0xfc0) = *(int *)(param_1[100] + 0xfc0) + tmp_i5;
    *(int *)(param_1[100] + 0xfb4) = *(int *)(param_1[100] + 0xfb4) + tmp_i5;
    *(int *)(param_1[100] + 0xff4) = *(int *)(param_1[100] + 0xff4) + tmp_i5;
    *(int *)(param_1[100] + 0x678) = *(int *)(param_1[100] + 0x678) + tmp_i5;
    *(int *)(param_1[100] + 0x674) = *(int *)(param_1[100] + 0x674) + tmp_i5;
    *(int *)(param_1[100] + 0x478) = *(int *)(param_1[100] + 0x478) + tmp_i5;
    param_1[0x112] = param_1[0x112] + tmp_i5;
    param_1[0xb0] = param_1[0xb0] + tmp_i5;
    param_1[0x40] = param_1[0x40] + tmp_i5;
  }
  if (g_unk_00abf994 != 0) {
    return;
  }
  P_WorldEffects(param_1);
  tmp_u9 = param_1[100];
  if (*(int *)(tmp_u9 + 0x530c) == 0) {
    if (*(int *)(tmp_u9 + 0x5310) != 0) {
      *(uint32_t *)(tmp_u9 + 0x4c) = 0;
      *(uint32_t *)(param_1[100] + 0x5310) = 0;
      tmp_u9 = param_1[100];
    }
  }
  else {
    if ((*(int *)(tmp_u9 + 4) == 3) && ((*(byte *)(tmp_u9 + 0x6a) & 0x80) == 0)) {
      return;
    }
    *(uint32_t *)(tmp_u9 + 0x4c) = 32000;
    *(uint32_t *)(param_1[100] + 0xb8) = 0;
    *(uint32_t *)(param_1[100] + 0x5310) = 1;
    tmp_u9 = param_1[100];
  }
  *(uint *)(tmp_u9 + 0xd0) = param_1[0xb2];
  param_1[0x28] = 0;
  BG_PlayerStateToEntityState(param_1[100],param_1,g_unk_00abe908,0);
  if ((-1 < (int)param_1[0xdd]) && (100 < (int)(g_unk_00abe908 - param_1[0x45]))) {
    param_1[0xdd] = 0xffffffff;
  }
  if (0 < (int)param_1[0xb2]) {
    tmp_i5 = StuckInClient(param_1);
    if (tmp_i5 == 0) {
      if (param_1[0x53] != 0x4000000) goto LAB_000529e7;
    }
    else {
      G_DPrintf("%s is stuck in a client.\n",param_1[100] + 0x5f8);
      param_1[0x53] = 0x4000000;
      if ((int)param_1[0xb2] < 1) goto LAB_000529e7;
    }
    if ((param_1[2] & 0x808000) == 0) {
      WolfReviveBbox(param_1);
    }
  }
LAB_000529e7:
  if ((*(byte *)(param_1[100] + 0xf70) & 1) == 0) {
    param_1[0xe7] = 0;
  }
  G_TouchTriggers(param_1);
  G_Script_ScriptRun(param_1);
  *(uint *)(param_1[100] + 0x68) = *(uint *)(param_1[100] + 0x68) & 0xfffffbff;
  tmp_u9 = param_1[100];
  tmp_i5 = (g_unk_00abe904 - *(int *)(tmp_u9 + 0x5384)) + -1;
  if (((int)GHIDRA_FIELD(g_maxWarp, 12, 4) < tmp_i5) && (GHIDRA_FIELD(g_maxWarp, 12, 4) != 0)) {
    tmp_i6 = G_DoAntiwarp(param_1);
    tmp_u9 = param_1[100];
    if (tmp_i6 != 0) {
      *(uint32_t *)(tmp_u9 + 0x538c) = 1;
      tmp_u9 = param_1[100];
    }
  }
  if (((GHIDRA_FIELD(g_skipCorrection, 12, 4) != 0) && (0 < tmp_i5)) && (*(int *)(tmp_u9 + 0x5390) == 0)) {
    tmp_i6 = G_DoAntiwarp(param_1);
    if (tmp_i6 == 0) {
      if (tmp_i5 < 3) {
        tmp_f3 = (float)tmp_i5;
      }
      else {
        tmp_f3 = 2.0;
        *(uint *)(param_1[100] + 0x68) = *(uint *)(param_1[100] + 0x68) | 0x400;
        param_1[2] = param_1[2] | 0x400;
      }
      G_PredictPmove(param_1,tmp_f3 / (float)(int)GHIDRA_FIELD(sv_fps, 12, 4));
      param_1[6] = (uint)(float)(int)ROUND((float)param_1[6]);
      param_1[7] = (uint)(float)(int)ROUND((float)param_1[7]);
      param_1[8] = (uint)(float)(int)ROUND((float)param_1[8]);
    }
    tmp_u9 = param_1[100];
  }
  *(uint32_t *)(tmp_u9 + 0x5390) = 0;
  mdx_PlayerAnimation(param_1);
  if ((g_debugPlayerHitboxes[0xc] & 1) != 0) {
    if (GHIDRA_FIELD(g_hitboxes, 12, 4) == 0) {
      local_d8 = (float)param_1[0x50];
      local_d4 = (float)param_1[0x51];
      local_d0 = (float)param_1[0x52];
      local_cc = (float)param_1[0x4d];
      local_c8 = (float)param_1[0x4e];
      local_c4 = param_1[0x4f];
      if ((g_realBody[0xc] & 1) != 0) {
        local_d8 = local_d8 - 3.0;
        local_cc = local_cc + 3.0;
        local_d4 = local_d4 - 3.0;
        local_c8 = local_c8 + 3.0;
      }
      tmp_l11 = (long double)nitrox_HitboxHeight(param_1,0);
      tmp_u9 = *param_1;
      local_d0 = (float)tmp_l11;
      tmp_u7 = tv(0,0,0x3f800000);
      G_RailBox(param_1 + 0x5a,&local_cc,&local_d8,tmp_u7,tmp_u9);
      tmp_i5 = G_BuildHead(param_1,1);
      tmp_u9 = *param_1;
      tmp_u7 = tv(0x3f800000,0,0);
      G_RailBox(tmp_i5 + 0x168,tmp_i5 + 0x134,tmp_i5 + 0x140,tmp_u7,tmp_u9 | 0x400);
      G_FreeEntity(tmp_i5);
      if ((*(uint *)(param_1[100] + 0x68) & 0x80001) != 0) {
        tmp_pu8 = (uint *)G_BuildLeg(param_1,1);
        tmp_u9 = *tmp_pu8;
        tmp_u7 = tv(0x3f800000,0,0x3f800000);
        G_RailBox(tmp_pu8 + 0x5a,tmp_pu8 + 0x4d,tmp_pu8 + 0x50,tmp_u7,tmp_u9 | 0x800);
        G_FreeEntity(tmp_pu8);
      }
    }
    else if (hitbox_debug_cmpt == 5) {
      hitbox_debug_cmpt = 0;
      tmp_u9 = param_1[0x16a];
      if (param_1[0x16a] == 0) {
        tmp_u9 = g_unk_00abe908;
      }
      mdx_gentity_to_grefEntity(param_1,&local_cc,tmp_u9);
      mdx_shot_test(0,local_e4,&local_d8,param_1,&local_cc,local_f0,local_ec,local_e8);
    }
    else {
      hitbox_debug_cmpt = hitbox_debug_cmpt + 1;
    }
  }
  G_StoreClientPosition(param_1);
  return;
}

void BodySink(int param_1)
{
  int tmp_i1;
  
  if (*(int *)(param_1 + 0x2f0) != 0) {
    if (*(int *)(*(int *)(*(int *)(param_1 + 0x2f0) + 400) + 0x16c) != 0) {
      *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
      return;
    }
    *(uint32_t *)(param_1 + 0x2f0) = 0;
  }
  *(uint32_t *)(param_1 + 0x1cc) = 0;
  tmp_i1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0xc) = 2;
  *(int *)(param_1 + 0x29c) = tmp_i1 + 0x708;
  *(void **)(param_1 + 0x2a4) = BodyUnlink;
  tmp_i1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x168);
  *(uint32_t *)(param_1 + 0x24) = 0;
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x16c);
  *(int *)(param_1 + 0x10) = tmp_i1;
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 0x170);
  *(uint32_t *)(param_1 + 0x28) = 0;
  *(uint32_t *)(param_1 + 0x2c) = 0xc1000000;
  return;
}

void BodySink2(int param_1)
{
  int tmp_i1;
  
  *(uint32_t *)(param_1 + 0x1cc) = 0;
  tmp_i1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0xc) = 2;
  *(int *)(param_1 + 0x29c) = tmp_i1 + 0x708;
  *(void **)(param_1 + 0x2a4) = BodyUnlink;
  tmp_i1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x168);
  *(uint32_t *)(param_1 + 0x2c) = 0xc1000000;
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x16c);
  *(int *)(param_1 + 0x10) = tmp_i1;
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 0x170);
  *(uint32_t *)(param_1 + 0x24) = 0;
  *(uint32_t *)(param_1 + 0x28) = 0;
  return;
}

void CopyToBodyQue(int param_1)
{
  int *tmp_pi1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint tmp_u5;
  
  trap_UnlinkEntity(param_1);
  tmp_i4 = trap_PointContents(*(int *)(param_1 + 400) + 0x14,0xffffffff);
  if (-1 < tmp_i4) {
    tmp_pi1 = (int *)(&g_unk_00abf9b8)[g_unk_00abf9b4];
    g_unk_00abf9b4 = (g_unk_00abf9b4 + 1) % 8;
    tmp_u5 = 0;
    do {
      tmp_u2 = *(uint32_t *)(param_1 + tmp_u5);
      *(uint32_t *)((int)tmp_pi1 + tmp_u5 + 4) = *(uint32_t *)(param_1 + 4 + tmp_u5);
      *(uint32_t *)((int)tmp_pi1 + tmp_u5) = tmp_u2;
      tmp_u5 = tmp_u5 + 8;
    } while (tmp_u5 < 0x120);
    tmp_pi1[2] = 1;
    if ((*(byte *)(*(int *)(param_1 + 400) + 0x69) & 0x10) != 0) {
      tmp_pi1[2] = 0x1001;
    }
    tmp_pi1[0x69] = (int)"corpse";
    tmp_pi1[0x28] = 0;
    tmp_pi1[1] = 0x26;
    tmp_pi1[0x39] = 0;
    tmp_pi1[0x73] = 1;
    tmp_pi1[0x74] = 0;
    *tmp_pi1 = ((int)(tmp_pi1 + -0x24f928) >> 9) * -0x55555555;
    tmp_i4 = g_unk_00abe908;
    tmp_pi1[0x172] = 0;
    tmp_pi1[0x93] = tmp_i4;
    tmp_pi1[0x171] = 0;
    tmp_pi1[0x1d] = *(int *)(*(int *)(param_1 + 400) + 0xb0);
    tmp_pi1[0x1e] = *(int *)(*(int *)(param_1 + 400) + 0xb4);
    tmp_pi1[0x1f] = *(int *)(*(int *)(param_1 + 400) + 0xb8);
    tmp_pi1[0x5d] = *(int *)(*(int *)(param_1 + 400) + 0xb0);
    tmp_pi1[0x5e] = *(int *)(*(int *)(param_1 + 400) + 0xb4);
    tmp_pi1[0x5f] = *(int *)(*(int *)(param_1 + 400) + 0xb8);
    if (*(int *)(*(int *)(param_1 + 400) + 0x180) != 0) {
      tmp_pi1[0x39] = 0x1000;
    }
    if (tmp_pi1[0x25] == 0x3ff) {
      tmp_pi1[3] = 6;
      tmp_pi1[4] = g_unk_00abe908;
      tmp_pi1[9] = *(int *)(*(int *)(param_1 + 400) + 0x20);
      tmp_pi1[10] = *(int *)(*(int *)(param_1 + 400) + 0x24);
      tmp_pi1[0xb] = *(int *)(*(int *)(param_1 + 400) + 0x28);
    }
    else {
      tmp_pi1[3] = 0;
    }
    tmp_pi1[0x2e] = 0;
    tmp_pi1[0x31] = 0;
    tmp_pi1[0x32] = 0;
    tmp_pi1[0x33] = 0;
    tmp_i3 = g_unk_00abe908;
    tmp_pi1[0x34] = 0;
    tmp_pi1[0x30] = 0;
    tmp_i4 = *(int *)(*(int *)(param_1 + 400) + 0x529c);
    tmp_pi1[0x3b] = tmp_i4;
    tmp_pi1[0x3c] = tmp_i4;
    tmp_pi1[0x4a] = *(uint *)(param_1 + 0x128) & 0xfffffff7;
    tmp_pi1[0x4d] = *(int *)(param_1 + 0x134);
    tmp_pi1[0x4e] = *(int *)(param_1 + 0x138);
    tmp_pi1[0x4f] = *(int *)(param_1 + 0x13c);
    tmp_pi1[0x50] = *(int *)(param_1 + 0x140);
    tmp_i4 = *(int *)(param_1 + 0x144);
    tmp_pi1[0x52] = 0;
    tmp_pi1[0x51] = tmp_i4;
    tmp_pi1[0x43] = *(int *)(*(int *)(param_1 + 400) + 0x5398);
    if (tmp_i3 < tmp_pi1[0x40]) {
      tmp_pi1[0x40] = *(int *)(*(int *)(param_1 + 400) + 0x5398) + 0x5dc;
    }
    tmp_pi1[0x75] = 0x10001;
    tmp_pi1[0x5a] = tmp_pi1[6];
    tmp_pi1[0x53] = 0x4000000;
    tmp_pi1[0x5b] = tmp_pi1[7];
    tmp_pi1[0x5c] = tmp_pi1[8];
    tmp_pi1[0x60] = *(int *)(param_1 + 0x180);
    tmp_pi1[0x29] = *(int *)(*(int *)(param_1 + 400) + 3000);
    tmp_pi1[0x2a] = *(int *)(*(int *)(param_1 + 400) + 0xbc8);
    tmp_i4 = *(int *)(*(int *)(param_1 + 400) + 0x9a0);
    tmp_pi1[0xc0] = 0;
    tmp_pi1[0x3f] = tmp_i4;
    tmp_pi1[0x16] = *(ushort *)(*(int *)(param_1 + 400) + 0x6a) & 1;
    tmp_pi1[0xbc] = 0;
    tmp_pi1[0xa7] = g_unk_00abe908 + 20000;
    tmp_pi1[0xa9] = (int)BodySink;
    tmp_pi1[0xaf] = (int)body_die;
    tmp_pi1[0xb3] = (uint)(-0xaf < *(int *)(param_1 + 0x2c8));
    trap_LinkEntity(tmp_pi1);
  }
  return;
}

void SetClientViewAngle(int param_1,float *param_2)
{
  float tmp_f1;
  
  *(uint *)(*(int *)(param_1 + 400) + 0x44) =
       ((int)ROUND((*param_2 * 65536.0) / 360.0) & 0xffffU) -
       *(int *)(*(int *)(param_1 + 400) + 0x5b8);
  *(uint *)(*(int *)(param_1 + 400) + 0x48) =
       ((int)ROUND((param_2[1] * 65536.0) / 360.0) & 0xffffU) -
       *(int *)(*(int *)(param_1 + 400) + 0x5bc);
  *(uint *)(*(int *)(param_1 + 400) + 0x4c) =
       ((int)ROUND((param_2[2] * 65536.0) / 360.0) & 0xffffU) -
       *(int *)(*(int *)(param_1 + 400) + 0x5c0);
  tmp_f1 = *param_2;
  *(float *)(param_1 + 0x74) = tmp_f1;
  *(float *)(param_1 + 0x78) = param_2[1];
  *(float *)(param_1 + 0x7c) = param_2[2];
  *(float *)(*(int *)(param_1 + 400) + 0xb0) = tmp_f1;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb4) = *(uint32_t *)(param_1 + 0x78);
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb8) = *(uint32_t *)(param_1 + 0x7c);
  return;
}

void ClientCleanName(char *param_1,char *param_2,int param_3)
{
  char tmp_c1;
  char *tmp_pc2;
  char *tmp_pc3;
  char *tmp_pc4;
  int tmp_i5;
  int local_2c;
  int local_28;
  
  *param_2 = '\0';
  tmp_c1 = *param_1;
  local_2c = 0;
  tmp_i5 = 0;
  local_28 = 0;
  tmp_pc2 = param_2;
  while (tmp_c1 != '\0') {
    tmp_pc3 = param_1 + 1;
    tmp_pc4 = tmp_pc2;
    if ((tmp_c1 != ' ') || (*param_2 != '\0')) {
      if (tmp_c1 == '^') {
        if ((param_1[1] == '\0') || (param_3 + -2 <= tmp_i5)) break;
        *tmp_pc2 = '^';
        tmp_pc3 = param_1 + 2;
        tmp_i5 = tmp_i5 + 2;
        tmp_pc2[1] = param_1[1];
        tmp_pc4 = tmp_pc2 + 2;
      }
      else {
        if (tmp_c1 == ' ') {
          local_2c = local_2c + 1;
          if (3 < local_2c) goto LAB_0005a3f0;
        }
        else {
          local_2c = 0;
        }
        if (param_3 + -1 <= tmp_i5) break;
        local_28 = local_28 + 1;
        tmp_i5 = tmp_i5 + 1;
        tmp_pc4 = tmp_pc2 + 1;
        *tmp_pc2 = tmp_c1;
      }
    }
LAB_0005a3f0:
    tmp_pc2 = tmp_pc4;
    param_1 = tmp_pc3;
    tmp_c1 = *tmp_pc3;
  }
  *tmp_pc2 = '\0';
  if ((local_28 != 0) && (*param_2 != '\0')) {
    return;
  }
  Q_strncpyz(param_2,"UnnamedPlayer",param_3 + -1);
  return;
}

void ClientUserinfoChanged(int param_1)
{
  uint *__s;
  char tmp_c1;
  int tmp_i2;
  bool tmp_b3;
  bool tmp_b4;
  uint tmp_u5;
  int tmp_i6;
  int tmp_i7;
  uint8_t *tmp_pu8;
  int tmp_i9;
  char *tmp_pc10;
  int tmp_i11;
  char *tmp_pc12;
  size_t tmp_s13;
  int tmp_i14;
  uint16_t *tmp_pu15;
  uint32_t *tmp_pu16;
  uint32_t tmp_u17;
  uint tmp_u18;
  uint *tmp_pu19;
  uint *tmp_pu20;
  char *tmp_pc21;
  uint tmp_u22;
  uint32_t *tmp_pu23;
  char *tmp_pc24;
  bool tmp_b25;
  bool tmp_b26;
  bool tmp_b27;
  byte tmp_b28;
  int local_265c;
  int local_2658;
  uint32_t *local_263c;
  uint32_t *local_262c;
  uint32_t local_2625;
  uint32_t local_2621;
  uint32_t local_261d;
  uint32_t local_2619;
  uint32_t local_2615;
  uint32_t local_2611;
  uint32_t local_260d;
  uint32_t local_2609;
  uint32_t local_2605;
  uint8_t local_2601;
  uint32_t local_2600 [7];
  uint32_t local_25e4;
  uint32_t local_25e0 [8];
  uint8_t local_25c0 [36];
  uint32_t local_259c;
  uint32_t local_2598 [31];
  uint32_t local_251c;
  uint32_t local_2518 [63];
  uint32_t local_241c;
  uint32_t local_2418 [1023];
  uint32_t local_141c;
  uint local_1418 [1281];
  uint32_t uStack_14;
  
  tmp_b28 = 0;
  local_241c = 0;
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_2418 + tmp_u18) = 0;
    *(uint32_t *)((int)local_2418 + tmp_u18 + 4) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x3f8);
  *(uint32_t *)((int)local_2418 + tmp_u18 + 8) = 0;
  local_2418[0xff] = 0;
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_2418 + tmp_u18 + 0x400) = 0;
    *(uint32_t *)((int)local_2418 + tmp_u18 + 0x404) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x3f8);
  *(uint32_t *)((int)local_2418 + tmp_u18 + 0x408) = 0;
  local_2418[0x1ff] = 0;
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_2418 + tmp_u18 + 0x800) = 0;
    *(uint32_t *)((int)local_2418 + tmp_u18 + 0x804) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x3f8);
  *(uint32_t *)((int)local_2418 + tmp_u18 + 0x808) = 0;
  local_2418[0x2ff] = 0;
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_2418 + tmp_u18 + 0xc00) = 0;
    *(uint32_t *)((int)local_2418 + tmp_u18 + 0xc04) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x3f8);
  *(uint32_t *)((int)local_2418 + tmp_u18 + 0xc08) = 0;
  local_2619 = 0;
  local_2615 = 0;
  local_2611 = 0;
  local_260d = 0;
  local_2609 = 0;
  local_2625 = 0;
  local_2621 = 0;
  local_261d = 0;
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_1418 + tmp_u18) = 0;
    *(uint32_t *)((int)local_1418 + tmp_u18 + 4) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x3f8);
  *(uint32_t *)((int)local_1418 + tmp_u18 + 8) = 0;
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_1418 + tmp_u18 + 0x400) = 0;
    *(uint32_t *)((int)local_1418 + tmp_u18 + 0x404) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x3f8);
  *(uint32_t *)((int)local_1418 + tmp_u18 + 0x408) = 0;
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_1418 + tmp_u18 + 0x800) = 0;
    *(uint32_t *)((int)local_1418 + tmp_u18 + 0x804) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x3f8);
  *(uint32_t *)((int)local_1418 + tmp_u18 + 0x808) = 0;
  tmp_u5 = 0;
  local_25e4 = 0;
  do {
    *(uint32_t *)((int)local_25e0 + tmp_u5) = 0;
    *(uint32_t *)((int)local_25e0 + tmp_u5 + 4) = 0;
    tmp_u5 = tmp_u5 + 8;
  } while (tmp_u5 < 0x20);
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_1418 + tmp_u18 + 0xc00) = 0;
    *(uint32_t *)((int)local_1418 + tmp_u18 + 0xc04) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x3f8);
  *(uint32_t *)((int)local_1418 + tmp_u18 + 0xc08) = 0;
  local_259c = 0;
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_2598 + tmp_u18) = 0;
    *(uint32_t *)((int)local_2598 + tmp_u18 + 4) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x78);
  *(uint32_t *)((int)local_2598 + tmp_u18 + 8) = 0;
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_1418 + tmp_u18 + 0x1000) = 0;
    *(uint32_t *)((int)local_1418 + tmp_u18 + 0x1004) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x3f8);
  *(uint32_t *)((int)local_1418 + tmp_u18 + 0x1008) = 0;
  local_2601 = 0;
  local_2605 = 0;
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_2600 + tmp_u18) = 0;
    *(uint32_t *)((int)local_2600 + tmp_u18 + 4) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0x18);
  *(uint32_t *)((int)local_2600 + tmp_u18 + 8) = 0;
  uStack_14 = 0x5a4dd;
  local_1418[0x3ff] = 0;
  local_1418[0x2ff] = 0;
  local_1418[0x1ff] = 0;
  local_1418[0xff] = 0;
  local_141c = 0;
  local_251c = 0;
  tmp_u5 = 0;
  do {
    tmp_u18 = tmp_u5;
    *(uint32_t *)((int)local_2518 + tmp_u18) = 0;
    *(uint32_t *)((int)local_2518 + tmp_u18 + 4) = 0;
    tmp_u5 = tmp_u18 + 8;
  } while (tmp_u18 + 8 < 0xf8);
  *(uint32_t *)((int)local_2518 + tmp_u18 + 8) = 0;
  local_262c = (uint32_t *)0x0;
  tmp_i6 = trap_Cvar_VariableIntegerValue("sv_demoState");
  tmp_i7 = trap_Cvar_VariableIntegerValue("sv_demoClients");
  tmp_b26 = tmp_i6 - 1U < 3;
  tmp_b27 = param_1 < tmp_i7;
  tmp_i7 = param_1 * 0x600;
  tmp_pu8 = g_entities + tmp_i7;
  tmp_i6 = *(int *)(g_entities + tmp_i7 + 400);
  tmp_u5 = *(uint *)(g_entities + tmp_i7 + 0x128) >> 3;
  *(int *)(tmp_i6 + 0xa0) = param_1;
  *(uint *)(tmp_i6 + 0x54d8) = (uint)(tmp_b27 && tmp_b26);
  tmp_pu16 = local_2418 + 0x2ff;
  trap_GetUserinfo(param_1,tmp_pu16,0x400);
  tmp_i9 = Info_Validate(tmp_pu16);
  if (tmp_i9 == 0) {
    G_LogPrintf("[ClientUserinfoChanged::BadInfo] Client %i - Malformed Userinfo, illegal characters\n"
                ,param_1);
    Q_strncpyz(tmp_pu16,"\\name\\badinfo",0x400);
  }
  if (((GHIDRA_FIELD(g_developer, 12, 4) != 0) || (g_log[0x10] != '\0')) || (GHIDRA_FIELD(g_dedicated, 12, 4) != 0)) {
    G_LogPrintf("Userinfo: %s\n",tmp_pu16);
  }
  tmp_b4 = false;
  tmp_b3 = false;
  __s = local_1418 + 0xff;
  local_262c = tmp_pu16;
_L755:
  tmp_i9 = Info_NextPair(&local_262c,&local_141c,__s);
  if ((tmp_i9 != 0) || (tmp_b27 && tmp_b26)) {
    if ((char)local_141c == '\0') goto LAB_0005adb4;
    tmp_i9 = nitrox_GetTokenForString(&local_141c);
    if (tmp_i9 - 0x5cU < 0x21) {
      tmp_b25 = (&switchD_0005aa16::switchdataD_00244ce8)[tmp_i9 - 0x5cU] == 0xffd4b9ec;
      switch(tmp_i9) {
      case 0x5c:
        Q_strncpyz(local_1418 + 0x1ff,__s,0x400);
        tmp_b4 = true;
        break;
      case 0x76:
        tmp_pu20 = __s;
        if ((!tmp_b27 || !tmp_b26) && (tmp_u5 & 1) == 0) {
          do {
            tmp_pu19 = tmp_pu20;
            tmp_u22 = *tmp_pu19 + 0xfefefeff & ~*tmp_pu19;
            tmp_u18 = tmp_u22 & 0x80808080;
            tmp_pu20 = tmp_pu19 + 1;
          } while (tmp_u18 == 0);
          if ((tmp_u22 & 0x8080) == 0) {
            tmp_pu20 = (uint *)((int)tmp_pu19 + 6);
            tmp_u18 = tmp_u18 >> 0x10;
          }
          if ((char *)((int)tmp_pu20 + ((-3 - (uint)CARRY1((byte)tmp_u18,(byte)tmp_u18)) - (int)__s))
              != (char *)0x20) {
            G_LogPrintf("[DROPCLIENT] Client %d Invalid NGUID length (%s)\n",param_1,__s);
            tmp_pc12 = "Invalid NGUID length";
LAB_0005ab92:
            Com_sprintf(local_1418 + 0x3ff,0x400,tmp_pc12);
            tmp_b3 = true;
            break;
          }
          if (*(char *)(tmp_i6 + 0x61c) != '\0') {
            tmp_i9 = Q_stricmp(tmp_i6 + 0x61c,__s);
            if (tmp_i9 != 0) {
              G_LogPrintf("[DROPCLIENT] Client %d NGUID has changed (%s -> %s)\n",param_1,
                          tmp_i6 + 0x61c,__s);
              tmp_pc12 = "Your NGUID has changed";
              goto LAB_0005ab92;
            }
          }
          if (GHIDRA_FIELD(g_GUIDChecks, 12, 4) != 0) {
            tmp_i9 = nitrox_GUIDCheckValid(&local_2605,local_1418 + 0x3ff);
            if (tmp_i9 == 0) {
              G_LogPrintf("[DROPCLIENT] Client %i %s\n",param_1,local_1418 + 0x3ff);
              tmp_b3 = true;
              break;
            }
          }
          if (((g_XPSave[0xc] & 8) != 0) && (0 < g_unk_00abe938)) {
            tmp_i11 = 0;
            tmp_i9 = g_unk_00abe938;
            do {
              tmp_i2 = (&g_unk_00abe944)[tmp_i11];
              if (((param_1 != tmp_i2) &&
                  (tmp_i14 = tmp_i2 * 0x54dc + level, *(int *)(tmp_i14 + 0x54d8) == 0)) &&
                 (tmp_i14 = Q_stricmp(__s,tmp_i14 + 0x61c), tmp_i9 = g_unk_00abe938, tmp_i14 == 0)) {
                G_LogPrintf("[DROPCLIENT] Client %i Duplicate NGUID detected on the server\n",tmp_i2)
                ;
                trap_DropClient(tmp_i2,"Duplicate NGUID detected on the server",0);
                tmp_i9 = g_unk_00abe938;
              }
              tmp_i11 = tmp_i11 + 1;
            } while (tmp_i11 < tmp_i9);
          }
        }
        local_263c = &local_2605;
        if ((*(int *)(g_entities + tmp_i7 + 0x5fc) != 0) &&
           (tmp_pu20 = __s, *(char *)(tmp_i6 + 0x61c) == '\0')) {
          do {
            tmp_pu19 = tmp_pu20;
            tmp_u22 = *tmp_pu19 + 0xfefefeff & ~*tmp_pu19;
            tmp_u18 = tmp_u22 & 0x80808080;
            tmp_pu20 = tmp_pu19 + 1;
          } while (tmp_u18 == 0);
          if ((tmp_u22 & 0x8080) == 0) {
            tmp_pu20 = (uint *)((int)tmp_pu19 + 6);
            tmp_u18 = tmp_u18 >> 0x10;
          }
          if ((char *)((int)tmp_pu20 + ((-3 - (uint)CARRY1((byte)tmp_u18,(byte)tmp_u18)) - (int)__s))
              == (char *)0x20) {
            *(uint32_t *)(g_entities + tmp_i7 + 0x5fc) = 0;
          }
        }
        Q_strncpyz(local_263c,__s,0x21);
        break;
      case 0x77:
        Q_strncpyz(tmp_i6 + 0xaf4,__s,0x12);
        break;
      case 0x78:
        tmp_i9 = 10;
        tmp_pc12 = (char *)(tmp_i6 + 0x653);
        tmp_pc10 = "localhost";
        do {
          if (tmp_i9 == 0) break;
          tmp_i9 = tmp_i9 + -1;
          tmp_b25 = *tmp_pc12 == *tmp_pc10;
          tmp_pc12 = tmp_pc12 + (uint)tmp_b28 * -2 + 1;
          tmp_pc10 = tmp_pc10 + (uint)tmp_b28 * -2 + 1;
        } while (tmp_b25);
        if (tmp_b25) {
          *(uint32_t *)(tmp_i6 + 0x5e8) = 1;
          g_unk_02a99a70 = 1;
          if ((tmp_u5 & 1) == 0) {
            *(uint32_t *)(tmp_i6 + 0xc80) = 1;
          }
        }
        if ((!tmp_b27 || !tmp_b26) && (tmp_u5 & 1) == 0) {
          tmp_pc12 = (char *)(tmp_i6 + 0x63d);
          tmp_pc10 = strchr(tmp_pc12,0x3a);
          if (tmp_pc10 == (char *)0x0) {
            tmp_i9 = 0x7fffffff;
            tmp_pc10 = strchr((char *)__s,0x3a);
            if (tmp_pc10 != (char *)0x0) goto LAB_0005ab34;
LAB_0005ad00:
            tmp_i9 = strcmp(tmp_pc12,(char *)__s);
          }
          else {
            tmp_i9 = (int)tmp_pc10 - (int)tmp_pc12;
            tmp_pc10 = strchr((char *)__s,0x3a);
            if (tmp_pc10 == (char *)0x0) {
              tmp_i11 = 0x7fffffff;
            }
            else {
LAB_0005ab34:
              tmp_i11 = (int)tmp_pc10 - (int)__s;
            }
            if (tmp_i11 < tmp_i9) {
              tmp_i9 = tmp_i11;
            }
            if (tmp_i9 == 0x7fffffff) goto LAB_0005ad00;
            tmp_i9 = Q_strncmp(tmp_pc12,__s,tmp_i9);
          }
          if (tmp_i9 != 0) {
            G_LogPrintf("[DROPCLIENT] Client %d IP address has changed (%s -> %s)\n",param_1,tmp_pc12
                        ,__s);
            tmp_pc12 = "Your IP adress has changed";
            goto LAB_0005ab92;
          }
        }
        nitrox_CacheClientIP(tmp_pu8,__s);
        break;
      case 0x7a:
        if (((!tmp_b27 || !tmp_b26) && (tmp_u5 & 1) == 0) && (g_censorNames[0x10] != '\0')) {
          SanitizeString(__s,local_25c0,1);
          tmp_i9 = G_CensorText(local_25c0,censorNamesDictionary);
          if (tmp_i9 != 0) {
            G_LogPrintf("[NAME CENSOR] Client %i Censored Name: \"%s\"\n",param_1,__s);
            Q_strncpyz(__s,local_25c0,0x24);
            Info_SetValueForKey(tmp_pu16,"name",local_25c0);
            trap_SetUserinfo(param_1,tmp_pu16);
            if ((g_censorPenalty[0xc] & 2) != 0) {
              G_LogPrintf("[DROPCLIENT] Client %d Name censor (%s)\n",param_1,__s);
              tmp_pc12 = "Name censor. Please change your name.";
              goto LAB_0005ab92;
            }
          }
        }
        Q_strncpyz(&local_25e4,__s,0x24);
        break;
      case 0x7c:
        Q_strncpyz(local_1418 + 0x2ff,__s,0x400);
      }
    }
    goto _L755;
  }
  G_LogPrintf("[DROPCLIENT] Client %i Malformed Userinfo, empty key found\n",param_1);
  Com_sprintf(local_1418 + 0x3ff,0x400,"Malformed Userinfo, empty key found");
  tmp_b3 = true;
LAB_0005adb4:
  if (((tmp_u5 & 1) == 0) && (*(int *)(tmp_i6 + 0x54d8) == 0)) {
    if (tmp_b3) {
      trap_DropClient(param_1,local_1418 + 0x3ff,0);
      return;
    }
    tmp_i9 = G_shrubbot_mute_check(&local_2605,tmp_i6 + 0xaf4);
    tmp_b27 = tmp_i9 != 0;
    if (tmp_b27) {
      *(uint32_t *)(*(int *)(g_entities + tmp_i7 + 400) + 0xbf0) = 1;
    }
    tmp_i9 = G_shrubbot_ban_check(tmp_i6 + 0x653,tmp_i6 + 0x61c,local_1418 + 0x3ff,tmp_i6 + 0xaf4);
    if (tmp_i9 != 0) {
      G_LogPrintf("[DROPCLIENT] Client %i is banned from this server\n",param_1);
      tmp_u17 = va("You are banned from this server\n^7%s\n",local_1418 + 0x3ff);
      trap_DropClient(param_1,tmp_u17,0);
      return;
    }
  }
  else {
    tmp_b27 = false;
  }
  tmp_u17 = Info_ValueForKey(tmp_pu16,"etVersion");
  Q_strncpyz(&local_251c,tmp_u17,0x100);
  tmp_pc12 = strstr((char *)&local_251c,"ET Legacy");
  if (tmp_pc12 == (char *)0x0) {
    *(uint32_t *)(*(int *)(g_entities + tmp_i7 + 400) + 0x54d4) = 0;
  }
  else {
    *(uint32_t *)(*(int *)(g_entities + tmp_i7 + 400) + 0x54d4) = 1;
  }
  tmp_i9 = *(int *)(g_entities + tmp_i7 + 400);
  if (tmp_b26) {
    if (*(int *)(tmp_i9 + 0x54d8) == 0) {
      *(uint32_t *)(tmp_i9 + 0xf30) = 1;
      tmp_i9 = *(int *)(g_entities + tmp_i7 + 400);
    }
    else {
      *(uint32_t *)(g_entities + tmp_i7 + 0x5fc) = 1;
    }
  }
  if (*(int *)(tmp_i9 + 0xbf0) != 0) {
    tmp_b27 = true;
  }
  if (((char)local_2605 == '\0') && (*(char *)(tmp_i9 + 0x61c) == '\0')) {
    trap_SendServerCommand(param_1,"getnguid");
  }
  else {
    Q_strncpyz(tmp_i6 + 0x61c,&local_2605,0x21);
    Q_strncpyz(*(int *)(g_entities + tmp_i7 + 400) + 0xeec,tmp_i6 + 0x61c,0x21);
  }
  *(int *)(tmp_i6 + 0x5364) =
       *(int *)(tmp_i6 + 0xc50) + *(int *)(tmp_i6 + 0xc54) + *(int *)(tmp_i6 + 0xc58) +
       *(int *)(tmp_i6 + 0xc5c) + *(int *)(tmp_i6 + 0xc60) + *(int *)(tmp_i6 + 0xc64) +
       *(int *)(tmp_i6 + 0xc68);
  if ((tmp_u5 & 1) == 0) {
    if (tmp_b4) {
      __isoc99_sscanf(local_1418 + 0x1ff,"%i %i %i",tmp_i6 + 0x97c,tmp_i6 + 0x984,tmp_i6 + 0x980);
      tmp_u18 = *(uint *)(tmp_i6 + 0x97c);
    }
    else {
      tmp_u18 = *(uint *)(tmp_i6 + 0x97c);
      if (tmp_u18 == 0) {
        *(uint32_t *)(tmp_i6 + 0x97c) = 0xd;
        tmp_u18 = 0xd;
      }
      if (*(int *)(tmp_i6 + 0x980) == 0) {
        tmp_u18 = *(uint *)(tmp_i6 + 0x97c);
        *(uint32_t *)(tmp_i6 + 0x980) = 0x1e;
      }
    }
    *(uint *)(tmp_i6 + 0x66c) = tmp_u18 >> 2 & 1;
    *(uint *)(tmp_i6 + 0x5f0) = tmp_u18 >> 3 & 1;
    tmp_u22 = tmp_u18 >> 4 & 1;
    *(uint *)(tmp_i6 + 0xaf0) = tmp_u22;
    *(uint *)(tmp_i6 + 0x5328) = tmp_u22;
    *(uint *)(tmp_i6 + 0x52a0) = tmp_u18 & 1;
    *(uint *)(tmp_i6 + 0x6a8) = tmp_u18 & 1;
    *(uint *)(tmp_i6 + 0x5f4) = tmp_u18 >> 5 & 1;
    *(uint *)(tmp_i6 + 0xb0c) = tmp_u18 >> 6 & 1;
  }
  else {
    *(uint32_t *)(tmp_i6 + 0x66c) = 1;
    *(uint32_t *)(tmp_i6 + 0x6a8) = 1;
    *(uint32_t *)(tmp_i6 + 0x52a0) = 1;
    *(uint32_t *)(tmp_i6 + 0x5f0) = 0;
    *(uint32_t *)(tmp_i6 + 0x5f4) = 0;
    *(uint32_t *)(tmp_i6 + 0xb0c) = 0;
  }
  tmp_pc12 = (char *)(tmp_i6 + 0x5f8);
  Q_strncpyz(&local_241c,tmp_pc12,0x400);
  if (((!tmp_b27) || ((char)local_241c == '\0')) || (*(char *)(tmp_i6 + 0x5f8) == '\0')) {
    local_265c = 0;
    local_2658 = 0;
    tmp_i9 = 0;
    *(uint8_t *)(tmp_i6 + 0x5f8) = 0;
    tmp_pc10 = (char *)&local_25e4;
    tmp_pc24 = tmp_pc12;
LAB_0005b010:
    do {
      tmp_pc21 = tmp_pc10;
      tmp_c1 = *tmp_pc21;
      tmp_pc10 = tmp_pc21 + 1;
      if (tmp_c1 == '\0') goto LAB_0005b080;
      if ((tmp_c1 != ' ') || (*(char *)(tmp_i6 + 0x5f8) != '\0')) {
        if (tmp_c1 == '^') {
          if ((tmp_pc21[1] == '\0') || (0x21 < tmp_i9)) goto LAB_0005b080;
          *tmp_pc24 = '^';
          tmp_i9 = tmp_i9 + 2;
          tmp_pc24[1] = tmp_pc21[1];
          tmp_pc10 = tmp_pc21 + 2;
          tmp_pc24 = tmp_pc24 + 2;
          goto LAB_0005b010;
        }
        if (tmp_c1 != ' ') {
          local_265c = 0;
        }
        else {
          local_265c = local_265c + 1;
          if (3 < local_265c) goto LAB_0005b010;
        }
        if (0x22 < tmp_i9) goto LAB_0005b080;
        local_2658 = local_2658 + 1;
        tmp_i9 = tmp_i9 + 1;
        *tmp_pc24 = tmp_c1;
        tmp_pc24 = tmp_pc24 + 1;
      }
    } while( true );
  }
LAB_0005b0b5:
  if ((*(int *)(tmp_i6 + 0x5ac) == 2) && (tmp_i9 = strcmp((char *)&local_241c,tmp_pc12), tmp_i9 != 0)) {
    tmp_u17 = va("print \"[lof]%s^7 [lon]renamed to[lof] %s\n\"",&local_241c,tmp_pc12);
    trap_SendServerCommand(0xffffffff,tmp_u17);
  }
  tmp_s13 = strlen((char *)(*(int *)(g_entities + tmp_i7 + 400) + 0x61c));
  if (tmp_s13 == 0x20) {
    if (*(int *)(g_entities + tmp_i7 + 0x5fc) == 0) {
      if (g_unk_02af58b8 != 0) {
        G_SetDefaultLevel_part_4();
      }
      nitrox_SQLite_LoadSingleUser(tmp_pu8);
      tmp_u17 = nitrox_XPSave_LoadXP(tmp_pu8);
      *(uint32_t *)(g_entities + tmp_i7 + 0x5fc) = tmp_u17;
    }
    if (((((tmp_u5 & 1) == 0) && (g_unk_02b99228 != 0)) &&
        (tmp_i9 = *(int *)(g_entities + tmp_i7 + 400), *(int *)(tmp_i9 + 0xb8c) == 0)) &&
       ((*(int *)(tmp_i9 + 0xb90) == 0 || (*(int *)(tmp_i9 + 0xb90) < g_unk_00abe908)))) {
      tmp_pu15 = (uint16_t *)(tmp_i9 + 0xb48);
      tmp_u5 = 0x40;
      tmp_b26 = ((uint)tmp_pu15 & 1) != 0;
      if (tmp_b26) {
        *(uint8_t *)(tmp_i9 + 0xb48) = 0;
        tmp_pu15 = (uint16_t *)(tmp_i9 + 0xb49);
        tmp_u5 = 0x3f;
      }
      if (((uint)tmp_pu15 & 2) != 0) {
        *tmp_pu15 = 0;
        tmp_u5 = tmp_u5 - 2;
        tmp_pu15 = tmp_pu15 + 1;
      }
      tmp_u18 = 0;
      do {
        *(uint32_t *)((int)tmp_pu15 + tmp_u18) = 0;
        *(uint32_t *)((int)tmp_pu15 + tmp_u18 + 4) = 0;
        tmp_u18 = tmp_u18 + 8;
      } while (tmp_u18 < (tmp_u5 & 0xfffffff8));
      tmp_pu16 = (uint32_t *)((int)tmp_pu15 + tmp_u18);
      if ((tmp_u5 & 4) != 0) {
        *tmp_pu16 = 0;
        tmp_pu16 = tmp_pu16 + 1;
      }
      if ((tmp_u5 & 2) != 0) {
        *(uint16_t *)tmp_pu16 = 0;
        tmp_pu16 = (uint32_t *)((int)tmp_pu16 + 2);
      }
      if (tmp_b26) {
        *(uint8_t *)tmp_pu16 = 0;
      }
      nitrox_QueryGlobalStats(*(int *)(g_entities + tmp_i7 + 400) + 0x61c);
      *(int *)(*(int *)(g_entities + tmp_i7 + 400) + 0xb90) = g_unk_00abe908 + 3000;
    }
  }
  tmp_pu16 = (uint32_t *)(tmp_i6 + 0xed0);
  do {
    tmp_pu23 = tmp_pu16 + 1;
    tmp_u17 = va(&g_unk_002580b3,*tmp_pu16);
    Q_strcat(&local_259c,0x80,tmp_u17);
    tmp_u17 = va("%i",tmp_pu16[-0xa8]);
    Q_strcat(&local_2625,0x10,tmp_u17);
    tmp_u17 = va("%i",tmp_pu16[-0xa0]);
    Q_strcat(&local_2615,0x10,tmp_u17);
    tmp_pu16 = tmp_pu23;
  } while (tmp_pu23 != (uint32_t *)(tmp_i6 + 0xeec));
  tmp_b26 = GHIDRA_FIELD(g_gametype, 12, 4) == 8;
  *(uint32_t *)(tmp_i6 + 0xe0) = *(uint32_t *)(tmp_i6 + 0x670);
  *(uint32_t *)(tmp_i6 + 0xe4) = *(uint32_t *)(tmp_i6 + 0xbc8);
  if ((tmp_b26) && ((g_DMOptions[0xc] & 8) != 0)) {
    tmp_i7 = *(int *)(tmp_i6 + 3000);
    if (tmp_i7 == 3) {
      *(uint32_t *)(tmp_i6 + 0xf30) = 1;
      tmp_u17 = 1;
    }
    else {
      tmp_u17 = *(uint32_t *)(tmp_i6 + 0xf30);
    }
  }
  else {
    tmp_u17 = *(uint32_t *)(tmp_i6 + 0xf30);
    tmp_i7 = *(int *)(tmp_i6 + 3000);
  }
  tmp_pu16 = local_2418 + 0x1ff;
  Com_sprintf(tmp_pu16,0x400,
              "n\\%s\\t\\%i\\mu\\%i\\rf\\%i\\c\\%i\\r\\%i\\m\\%s\\s\\%s\\dn\\%s\\dr\\%i\\w\\%i\\lw\\%i\\sw\\%i\\rn\\%i\\lc\\%i\\xp\\%s\\u\\%u\\sc\\%i\\tv\\%i"
              ,tmp_pc12,tmp_i7,*(int *)(tmp_i6 + 0xbf0) != 0,*(uint32_t *)(tmp_i6 + 0xc80),
              *(uint32_t *)(tmp_i6 + 0xbc8),*(uint32_t *)(tmp_i6 + 0xc4c),&local_2615,&local_2625,
              tmp_i6 + 0x533c,*(uint32_t *)(tmp_i6 + 0x5360),*(uint32_t *)(tmp_i6 + 0xbcc),
              *(uint32_t *)(tmp_i6 + 0xbdc),*(uint32_t *)(tmp_i6 + 0xbe0),
              *(uint32_t *)(tmp_i6 + 0xbe4),*(uint32_t *)(tmp_i6 + 0xbd8),&local_259c,
              *(uint32_t *)(tmp_i6 + 0xf14),tmp_u17,*(uint32_t *)(tmp_i6 + 0xf34));
  trap_GetConfigstring(param_1 + 0x2b1,local_2418 + 0xff,0x400);
  trap_SetConfigstring(param_1 + 0x2b1,tmp_pu16);
  tmp_i6 = Q_stricmp(local_2418 + 0xff,tmp_pu16);
  if (tmp_i6 == 0) {
    return;
  }
  G_LogPrintf("ClientUserinfoChanged: %i %s\n",param_1,tmp_pu16);
  G_LuaHook_ClientUserinfoChanged(param_1);
  return;
LAB_0005b080:
  *tmp_pc24 = '\0';
  if ((local_2658 == 0) || (*(char *)(tmp_i6 + 0x5f8) == '\0')) {
    Q_strncpyz(tmp_pc12,"UnnamedPlayer",0x23);
  }
  goto LAB_0005b0b5;
}

int ClientVisibleNameLength(char *param_1)
{
  char tmp_c1;
  int tmp_i2;
  char *tmp_pc3;
  
  tmp_i2 = 0;
  tmp_c1 = *param_1;
  do {
    if (tmp_c1 == '\0') {
      return tmp_i2;
    }
    tmp_pc3 = param_1 + 1;
    if (tmp_c1 != ' ') {
      if (tmp_c1 == '^') {
        if (param_1[1] == '\0') {
          return tmp_i2;
        }
        tmp_pc3 = param_1 + 2;
      }
      else {
        tmp_i2 = tmp_i2 + 1;
      }
    }
    tmp_c1 = *tmp_pc3;
    param_1 = tmp_pc3;
  } while( true );
}

void ClientSpawn(int param_1,int param_2,int param_3,int param_4)
{
  float tmp_f1;
  uint16_t tmp_u2;
  int *__s;
  uint tmp_u3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  uint tmp_u12;
  int *tmp_pi13;
  int *tmp_pi14;
  uint tmp_u15;
  int tmp_i16;
  uint32_t *tmp_pu17;
  int *tmp_pi18;
  uint tmp_u19;
  int *tmp_pi20;
  bool tmp_b21;
  byte tmp_b22;
  uint32_t *local_a8c;
  int local_a88;
  uint32_t local_a40;
  uint32_t local_a3c;
  float local_a38;
  float local_a34;
  float local_a30;
  float local_a2c;
  uint32_t local_a28;
  float local_a24;
  uint32_t local_a20;
  uint8_t local_a1c [64];
  int local_9dc [238];
  int local_624 [388];
  uint32_t uStack_14;
  
  tmp_b22 = 0;
  uStack_14 = 0x5d289;
  __s = *(int **)(param_1 + 400);
  tmp_i10 = param_1 + -0x93e4a0 >> 9;
  tmp_i11 = tmp_i10 * -0x55555555;
  G_UpdateSpawnCounts();
  __s[0x25c] = g_unk_00abe908;
  __s[0x25a] = g_unk_02a99b84;
  if (param_2 == 0) {
    if (__s[0x2ee] - 1U < 2) {
      local_a88 = SelectCTFSpawnPoint(__s[0x2ee],__s[0x19f],&local_a40,&local_a34,__s[0x2f5],param_3
                                     );
      if ((local_a88 == 0) && (GHIDRA_FIELD(g_gametype, 12, 4) == 8)) {
        if (param_3 == 0) {
          return;
        }
        local_a88 = 0;
      }
    }
    else {
      FindIntermissionPoint();
      local_a88 = 0;
      local_a40 = g_unk_00abf998;
      local_a3c = g_unk_00abf99c;
      local_a38 = g_unk_00abf9a0;
      local_a34 = g_unk_00abf9a4;
      local_a30 = g_unk_00abf9a8;
      local_a2c = g_unk_00abf9ac;
    }
  }
  else {
    local_a40 = *(uint32_t *)(param_1 + 0x168);
    local_a88 = param_1;
    local_a3c = *(uint32_t *)(param_1 + 0x16c);
    local_a38 = *(float *)(param_1 + 0x170) + 9.0;
    local_a34 = *(float *)(param_1 + 0x74);
    local_a30 = *(float *)(param_1 + 0x78);
    local_a2c = *(float *)(param_1 + 0x7c);
  }
  local_a8c = &local_a40;
  __s[0x19f] = 1;
  tmp_u3 = *(uint *)(*(int *)(param_1 + 400) + 0x68);
  G_ResetMarkers(param_1);
  tmp_u15 = __s[0x1a];
  tmp_pi14 = __s + 0x16b;
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xffff7fff;
  tmp_pi18 = local_9dc + 0xed;
  tmp_pi13 = tmp_pi14;
  tmp_pi20 = tmp_pi18;
  for (tmp_i16 = 0x183; tmp_i16 != 0; tmp_i16 = tmp_i16 + -1) {
    *tmp_pi20 = *tmp_pi13;
    tmp_pi13 = tmp_pi13 + (uint)tmp_b22 * -2 + 1;
    tmp_pi20 = tmp_pi20 + (uint)tmp_b22 * -2 + 1;
  }
  tmp_u12 = 0;
  do {
    tmp_u19 = tmp_u12;
    tmp_u4 = *(uint32_t *)((int)__s + tmp_u19 + 0xbbc);
    *(uint32_t *)((int)local_9dc + tmp_u19) = *(uint32_t *)((int)__s + tmp_u19 + 3000);
    *(uint32_t *)((int)local_9dc + tmp_u19 + 4) = tmp_u4;
    tmp_u12 = tmp_u19 + 8;
  } while (tmp_u19 + 8 < 0x3b0);
  *(uint32_t *)((int)local_9dc + tmp_u19 + 8) = *(uint32_t *)((int)__s + tmp_u19 + 0xbc0);
  tmp_i16 = __s[0x11a];
  tmp_i5 = __s[0x108];
  tmp_i6 = __s[0x11e];
  tmp_i7 = __s[0x14ce];
  tmp_pi13 = __s + 0x44;
  tmp_pu17 = (uint32_t *)local_a1c;
  tmp_u12 = 0;
  do {
    *(uint32_t *)((int)tmp_pu17 + tmp_u12) = *(uint32_t *)((int)tmp_pi13 + tmp_u12);
    tmp_u12 = tmp_u12 + 4;
  } while (tmp_u12 < 0x40);
  tmp_i8 = __s[0x14de];
  tmp_i9 = __s[0x14df];
  memset(__s,0,0x54dc);
  tmp_u12 = 0x60c;
  __s[0x14de] = tmp_i8;
  __s[0x14df] = tmp_i9;
  if (((uint)tmp_pi14 & 4) != 0) {
    tmp_pi14 = __s + 0x16c;
    tmp_u12 = 0x608;
    tmp_pi18 = local_624;
    __s[0x16b] = local_9dc[0xed];
  }
  for (tmp_u12 = tmp_u12 >> 2; tmp_u19 = 0, tmp_u12 != 0; tmp_u12 = tmp_u12 - 1) {
    *tmp_pi14 = *tmp_pi18;
    tmp_pi18 = tmp_pi18 + (uint)tmp_b22 * -2 + 1;
    tmp_pi14 = tmp_pi14 + (uint)tmp_b22 * -2 + 1;
  }
  do {
    tmp_u12 = tmp_u19;
    tmp_u4 = *(uint32_t *)((int)local_9dc + tmp_u12 + 4);
    *(uint32_t *)((int)__s + tmp_u12 + 3000) = *(uint32_t *)((int)local_9dc + tmp_u12);
    *(uint32_t *)((int)__s + tmp_u12 + 0xbbc) = tmp_u4;
    tmp_u19 = tmp_u12 + 8;
  } while (tmp_u12 + 8 < 0x3b0);
  *(uint32_t *)((int)__s + tmp_u12 + 0xbc0) = *(uint32_t *)((int)local_9dc + tmp_u12 + 8);
  tmp_u12 = 0x40;
  __s[0x11a] = tmp_i16;
  __s[0x108] = tmp_i5;
  tmp_b21 = ((uint)tmp_pi13 & 1) != 0;
  if (tmp_b21) {
    tmp_pi13 = (int *)((int)__s + 0x111);
    tmp_u12 = 0x3f;
    *(uint8_t *)(__s + 0x44) = local_a1c[0];
    tmp_pu17 = (uint32_t *)((int)local_a1c + 1);
  }
  tmp_pi14 = tmp_pi13;
  if (((uint)tmp_pi13 & 2) != 0) {
    tmp_u2 = *(uint16_t *)tmp_pu17;
    tmp_pi14 = (int *)((int)tmp_pi13 + 2);
    tmp_pu17 = (uint32_t *)((int)tmp_pu17 + 2);
    tmp_u12 = tmp_u12 - 2;
    *(uint16_t *)tmp_pi13 = tmp_u2;
  }
  tmp_u19 = 0;
  do {
    *(uint32_t *)((int)tmp_pi14 + tmp_u19) = *(uint32_t *)((int)tmp_pu17 + tmp_u19);
    tmp_u19 = tmp_u19 + 4;
  } while (tmp_u19 < (tmp_u12 & 0xfffffffc));
  tmp_i16 = 0;
  if ((tmp_u12 & 2) != 0) {
    *(uint16_t *)((int)tmp_pi14 + tmp_u19) = *(uint16_t *)((int)tmp_pu17 + tmp_u19);
    tmp_i16 = 2;
  }
  if (tmp_b21) {
    *(uint8_t *)((int)((int)tmp_pi14 + tmp_u19) + tmp_i16) =
         *(uint8_t *)((int)((int)tmp_pu17 + tmp_u19) + tmp_i16);
  }
  __s[0x4c] = __s[0x4c] + 1;
  if (param_2 != 0) {
    __s[0x4f] = __s[0x4f] + 1;
  }
  __s[0x4b] = __s[0x2ee];
  __s[0x50] = 0;
  if ((*(byte *)(__s + 0x3b4) & 0x20) == 0) {
    tmp_i16 = g_unk_00abe908 + 12000;
  }
  else {
    tmp_i16 = g_unk_00abe908 + 15000;
  }
  __s[0x3f0] = tmp_i16;
  __s[0x38] = __s[0x19c];
  __s[0x1a] = tmp_u3 & 4 ^ 4 | tmp_u15 & 0x4000;
  __s[0x11e] = tmp_i6;
  __s[0x14ce] = tmp_i7;
  *(uint32_t *)(param_1 + 0x94) = 0x3ff;
  *(uint32_t *)(param_1 + 0x14c) = 0x2000000;
  *(uint8_t **)(param_1 + 0x1d4) = &g_unk_02010001;
  tmp_i16 = level;
  *(int *)(param_1 + 400) = tmp_i10 * -0x5555390c + level;
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  *(uint32_t *)(param_1 + 0x194) = 1;
  *(char **)(param_1 + 0x1a4) = "player";
  if (param_2 == 0) {
    *(uint32_t *)(param_1 + 0x374) = 0xffffffff;
  }
  tmp_i10 = playerMins;
  *(int *)(param_1 + 0x134) = playerMins;
  *(uint32_t *)(param_1 + 0x138) = g_unk_002b7dd0;
  tmp_u4 = g_unk_002b7dd4;
  *(void **)(param_1 + 700) = player_die;
  *(uint32_t *)(param_1 + 0x13c) = tmp_u4;
  tmp_u4 = playerMaxs;
  *(uint32_t *)(param_1 + 0x304) = 0;
  *(uint32_t *)(param_1 + 0x140) = tmp_u4;
  tmp_u4 = g_unk_002b7dc4;
  *(uint32_t *)(param_1 + 0x300) = 0;
  *(uint32_t *)(param_1 + 0x144) = tmp_u4;
  tmp_u4 = g_unk_002b7dc8;
  *(uint32_t *)(param_1 + 0x1b0) = 0;
  *(uint32_t *)(param_1 + 0x148) = tmp_u4;
  __s[0xf7] = tmp_i10;
  __s[0xf8] = *(int *)(param_1 + 0x138);
  __s[0xf9] = *(int *)(param_1 + 0x13c);
  __s[0xfa] = *(int *)(param_1 + 0x140);
  __s[0xfb] = *(int *)(param_1 + 0x144);
  tmp_f1 = *(float *)(param_1 + 0x148);
  __s[0xfe] = 0x41800000;
  __s[0xfc] = (int)tmp_f1;
  __s[0xff] = 0x42200000;
  __s[0x100] = -0x3e800000;
  __s[0xfd] = (int)(tmp_f1 - 24.0);
  __s[0x101] = 0x3f4ccccd;
  __s[0x11d] = 0;
  __s[0x102] = 0x3f8ccccd;
  __s[0x103] = 0x3e800000;
  __s[0x2a] = 0;
  __s[0x14a8] = __s[0x1aa];
  __s[0x14ac] = 20000;
  __s[0x106] = 0x3f800000;
  __s[0x14ca] = __s[700];
  __s[0x28] = tmp_i11;
  trap_GetUsercmd(((int)__s - tmp_i16 >> 2) * -0x66e64f79,*(int *)(param_1 + 400) + 0x5b0);
  if (param_2 == 0) {
    if (GHIDRA_FIELD(g_war, 12, 4) == 1) {
      tmp_b21 = true;
      __s[0x2f2] = 0;
    }
    else if (((int)GHIDRA_FIELD(g_war, 12, 4) < 1) || (3 < (int)GHIDRA_FIELD(g_war, 12, 4))) {
      tmp_b21 = __s[0x2f2] != __s[0x2f6];
      __s[0x2f2] = __s[0x2f6];
    }
    else {
      tmp_b21 = true;
      __s[0x2f2] = 4;
    }
    tmp_i10 = G_IsWeaponDisabled(param_1,__s[0x2f7],1,0);
    if (tmp_i10 == 0) {
      tmp_i10 = __s[0x2f7];
    }
    else {
      tmp_b21 = true;
      tmp_i10 = BG_PlayerClassForPlayerState(*(uint32_t *)(param_1 + 400));
      tmp_i10 = *(int *)(tmp_i10 + 0x10);
      __s[0x2f7] = tmp_i10;
    }
    if (__s[0x2f3] != tmp_i10) {
      __s[0x2f3] = tmp_i10;
      tmp_b21 = true;
    }
    tmp_i10 = G_IsClassDisabled(param_1,__s[0x2f2],1);
    if (tmp_i10 != 0) {
      tmp_i10 = 0;
      do {
        tmp_i16 = G_IsClassDisabled(param_1,tmp_i10,1);
        if (tmp_i16 == 0) {
          __s[0x2f2] = tmp_i10;
          __s[0x2f6] = tmp_i10;
          tmp_b21 = true;
          goto LAB_0005d908;
        }
        tmp_i10 = tmp_i10 + 1;
      } while (tmp_i10 != 5);
      tmp_b21 = true;
      SetTeam(param_1,&g_unk_0024e6ea,1,0xffffffff,0xffffffff,0);
    }
LAB_0005d908:
    tmp_i10 = G_IsWeaponDisabled(param_1,__s[0x2f3],1,0);
    if (tmp_i10 != 0) {
      tmp_b21 = true;
      tmp_i10 = BG_PlayerClassForPlayerState(*(uint32_t *)(param_1 + 400));
      __s[0x2f3] = *(int *)(tmp_i10 + 0x10);
    }
    __s[0x2f4] = __s[0x2f8];
    if (tmp_b21 || param_3 != 0) {
      ClientUserinfoChanged(tmp_i11);
    }
  }
  if (__s[0x2ee] == 3) {
LAB_0005de96:
    G_UpdateCharacter(__s);
    tmp_i10 = __s[0x2ee];
    tmp_i16 = __s[0x2f2];
    if (tmp_i10 != 3) goto LAB_0005deb7;
  }
  else {
    if (GHIDRA_FIELD(g_fastres, 12, 4) == 1) {
      if (param_2 == 0) goto LAB_0005de78;
      __s[0x55] = g_unk_00abe908 + 1000;
    }
    else {
      if (param_2 == 0) {
LAB_0005de78:
        __s[0x55] = GHIDRA_FIELD(g_spawnInvul, 12, 4) * 1000 + g_unk_00abe908;
        goto LAB_0005de96;
      }
      __s[0x55] = g_unk_00abe908 + 3000;
    }
    G_UpdateCharacter(__s);
    tmp_i10 = __s[0x2ee];
    tmp_i16 = __s[0x2f2];
    if (tmp_i10 == 3) {
      AddMedicTeamBonus(__s);
      goto joined_r0x0005df0c;
    }
LAB_0005deb7:
    __s[0x108] = tmp_i10;
    __s[0x39] = tmp_i16;
    SetWolfSpawnWeapons_part_5();
  }
  AddMedicTeamBonus(__s);
  if (param_2 == 0) {
    *(char *)((int)__s + 0x5b6) = (char)*(uint32_t *)(*(int *)(param_1 + 400) + 0xa4);
  }
joined_r0x0005df0c:
  if (param_4 == 0) {
    __s[0x34] = *(int *)(param_1 + 0x2c8);
  }
  else if (((GHIDRA_FIELD(g_war, 12, 4) == 0) && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) &&
          ((int)(&g_unk_02b9a438)[*(int *)(*(int *)(param_1 + 400) + 0xbc8)] < 1)) {
    tmp_i10 = __s[0x38];
    if ((*(byte *)(__s + 0x3b4) & 8) == 0) {
      __s[0x34] = tmp_i10;
      *(int *)(param_1 + 0x2c8) = tmp_i10;
    }
    else {
      __s[0x34] = tmp_i10 + -0xf;
      *(int *)(param_1 + 0x2c8) = tmp_i10 + -0xf;
    }
  }
  else {
    __s[0x34] = __s[0x38];
    *(int *)(param_1 + 0x2c8) = __s[0x38];
  }
  G_SetOrigin(param_1,local_a8c);
  __s[3] = __s[3] | 0x200;
  if (param_2 == 0) {
    *(uint *)(*(int *)(param_1 + 400) + 0x44) =
         ((int)ROUND((local_a34 * 65536.0) / 360.0) & 0xffffU) -
         *(int *)(*(int *)(param_1 + 400) + 0x5b8);
    *(uint *)(*(int *)(param_1 + 400) + 0x48) =
         ((int)ROUND((local_a30 * 65536.0) / 360.0) & 0xffffU) -
         *(int *)(*(int *)(param_1 + 400) + 0x5bc);
    *(uint *)(*(int *)(param_1 + 400) + 0x4c) =
         ((int)ROUND((local_a2c * 65536.0) / 360.0) & 0xffffU) -
         *(int *)(*(int *)(param_1 + 400) + 0x5c0);
    *(float *)(param_1 + 0x74) = local_a34;
    *(float *)(param_1 + 0x78) = local_a30;
    *(float *)(param_1 + 0x7c) = local_a2c;
    *(float *)(*(int *)(param_1 + 400) + 0xb0) = local_a34;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xb4) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xb8) = *(uint32_t *)(param_1 + 0x7c);
  }
  else {
    tmp_i10 = *(int *)(param_1 + 400);
    local_a28 = 0;
    local_a20 = 0;
    local_a24 = (float)(*(int *)(tmp_i10 + 0x48) + *(int *)(tmp_i10 + 0x5bc)) * 0.005493164;
    *(int *)(tmp_i10 + 0x44) = -*(int *)(tmp_i10 + 0x5b8);
    *(uint *)(*(int *)(param_1 + 400) + 0x48) =
         ((int)ROUND((local_a24 * 65536.0) / 360.0) & 0xffffU) -
         *(int *)(*(int *)(param_1 + 400) + 0x5bc);
    *(int *)(*(int *)(param_1 + 400) + 0x4c) = -*(int *)(*(int *)(param_1 + 400) + 0x5c0);
    *(float *)(param_1 + 0x78) = local_a24;
    *(uint32_t *)(param_1 + 0x74) = 0;
    *(uint32_t *)(param_1 + 0x7c) = 0;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xb0) = 0;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xb4) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xb8) = *(uint32_t *)(param_1 + 0x7c);
  }
  if (*(int *)(*(int *)(param_1 + 400) + 3000) != 3) {
    trap_LinkEntity(param_1);
  }
  tmp_i16 = g_unk_02a99b84;
  tmp_i10 = g_unk_00abe908;
  __s[0x3ee] = 0;
  __s[0x3ec] = tmp_i16;
  __s[0x3ed] = GHIDRA_FIELD(g_inactivity, 12, 4) * 1000 + tmp_i10;
  __s[0x3de] = 0;
  __s[0x3e1] = 0;
  __s[0x14ce] = 0;
  if (g_unk_00abf994 == 0) {
    if (param_2 == 0) {
      G_UseTargets(local_a88,param_1);
    }
  }
  else {
    MoveClientToIntermission(param_1);
  }
  G_LuaHook_ClientSpawn(tmp_i11,param_2,param_3,param_4);
  *__s = g_unk_00abe908 + -100;
  *(int *)(*(int *)(param_1 + 400) + 0x5b0) = g_unk_00abe908;
  ClientThink(tmp_i11);
  if (*(int *)(*(int *)(param_1 + 400) + 3000) != 3) {
    BG_PlayerStateToEntityState(__s,param_1,g_unk_00abe908,1);
    tmp_i10 = *(int *)(param_1 + 400);
    *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(tmp_i10 + 0x14);
    *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(tmp_i10 + 0x18);
    *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(tmp_i10 + 0x1c);
    trap_LinkEntity(param_1);
  }
  ClientEndFrame(param_1);
  tmp_i10 = *(int *)(param_1 + 400);
  tmp_u3 = *(uint *)(tmp_i10 + 0x480);
  tmp_u15 = PM_IdleAnimForWeapon(*(uint32_t *)(tmp_i10 + 0xa4));
  *(uint *)(tmp_i10 + 0x480) = ~tmp_u3 & 0x200 | tmp_u15;
  BG_PlayerStateToEntityState(*(uint32_t *)(param_1 + 400),param_1,g_unk_00abe908,1);
  G_ResetMarkers(param_1);
  if ((param_2 == 0) && (__s[0x2ee] != 3)) {
    G_Script_ScriptEvent(param_1,"playerstart",&g_unk_0026ea14);
  }
  return;
}

void ClientBegin(int param_1)
{
  uint tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  float tmp_f7;
  bool tmp_b8;
  bool tmp_b9;
  int tmp_i10;
  uint8_t *tmp_pu11;
  int tmp_i12;
  int tmp_i13;
  size_t tmp_s14;
  uint32_t tmp_u15;
  uint tmp_u16;
  uint tmp_u17;
  int tmp_i18;
  uint32_t *tmp_pu19;
  uint8_t *tmp_pu20;
  uint32_t *tmp_pu21;
  int tmp_i22;
  bool tmp_b23;
  bool tmp_b24;
  byte tmp_b25;
  int local_54;
  int local_40;
  int local_3c;
  
  tmp_b25 = 0;
  tmp_b24 = true;
  tmp_i10 = param_1 * 0x600;
  tmp_pu11 = g_entities + tmp_i10;
  tmp_u1 = *(uint *)(g_entities + tmp_i10 + 0x128);
  tmp_b9 = (bool)((byte)(tmp_u1 >> 3) & 1);
  tmp_i12 = param_1 * 0x54dc;
  tmp_pu19 = (uint32_t *)(level + tmp_i12);
  local_54 = *(int *)(g_entities + tmp_i10 + 0x2c8);
  if ((GHIDRA_FIELD(g_maxlives, 12, 4) == 0) && (GHIDRA_FIELD(g_alliedmaxlives, 12, 4) == 0)) {
    tmp_i22 = *(int *)(g_entities + tmp_i10 + 0x120);
    tmp_b24 = GHIDRA_FIELD(g_axismaxlives, 12, 4) != 0;
  }
  else {
    tmp_i22 = *(int *)(g_entities + tmp_i10 + 0x120);
  }
  if (tmp_i22 != 0) {
    trap_UnlinkEntity(tmp_pu11);
  }
  G_InitGentity(tmp_pu11);
  *(uint32_t *)(g_entities + tmp_i10 + 0x2b8) = 0;
  *(uint32_t *)(g_entities + tmp_i10 + 0x2b0) = 0;
  *(uint32_t **)(g_entities + tmp_i10 + 400) = tmp_pu19;
  Q_strncpyz(tmp_pu19 + 0x3bb,tmp_pu19 + 0x187,0x21);
  tmp_b8 = false;
  if ((tmp_b9 < (tmp_pu19[0x16b] == 1)) && (tmp_pu19[0x1536] == 0)) {
    if (0 < g_unk_02aabf90) {
      tmp_i22 = 0;
      tmp_pu20 = &g_unk_02aa3f90;
      do {
        tmp_i22 = tmp_i22 + 1;
        tmp_u15 = va("fc \"%s\" \"%s\"",tmp_pu20,tmp_pu20 + 0x100);
        trap_SendServerCommand((tmp_i10 >> 9) * -0x55555555,tmp_u15);
        tmp_pu20 = tmp_pu20 + 0x200;
      } while (tmp_i22 < g_unk_02aabf90);
    }
    tmp_b8 = true;
  }
  tmp_pu19[0x16b] = 2;
  tmp_u15 = tmp_pu19[0x4c];
  tmp_pu19[0x19f] = 0;
  tmp_i22 = *(int *)(g_entities + tmp_i10 + 400);
  tmp_u2 = *(uint32_t *)(tmp_i22 + 0xc7c);
  tmp_u3 = *(uint32_t *)(tmp_i22 + 0xc74);
  tmp_u4 = *(uint32_t *)(tmp_i22 + 0xf38);
  tmp_u5 = *(uint32_t *)(tmp_i22 + 0xf3c);
  tmp_u17 = 0x5ac;
  tmp_i22 = tmp_pu19[0x4d];
  tmp_u6 = tmp_pu19[0x1a];
  tmp_b23 = ((uint)tmp_pu19 & 1) != 0;
  tmp_pu21 = tmp_pu19;
  if (tmp_b23) {
    tmp_u17 = 0x5ab;
    *(uint8_t *)tmp_pu19 = 0;
    tmp_pu21 = (uint32_t *)((int)tmp_pu19 + 1);
  }
  if (((uint)tmp_pu21 & 2) != 0) {
    *(uint16_t *)tmp_pu21 = 0;
    tmp_u17 = tmp_u17 - 2;
    tmp_pu21 = (uint32_t *)((int)tmp_pu21 + 2);
  }
  if (((uint)tmp_pu21 & 4) != 0) {
    *tmp_pu21 = 0;
    tmp_u17 = tmp_u17 - 4;
    tmp_pu21 = tmp_pu21 + 1;
  }
  for (tmp_u16 = tmp_u17 >> 2; tmp_u16 != 0; tmp_u16 = tmp_u16 - 1) {
    *tmp_pu21 = 0;
    tmp_pu21 = tmp_pu21 + (uint)tmp_b25 * -2 + 1;
  }
  if ((tmp_u17 & 2) != 0) {
    *(uint16_t *)tmp_pu21 = 0;
    tmp_pu21 = (uint32_t *)((int)tmp_pu21 + 2);
  }
  if (tmp_b23) {
    *(uint8_t *)tmp_pu21 = 0;
  }
  tmp_pu21 = tmp_pu19 + 0x14a8;
  tmp_u17 = 0x98;
  tmp_b23 = ((uint)tmp_pu21 & 1) != 0;
  if (tmp_b23) {
    *(uint8_t *)(tmp_pu19 + 0x14a8) = 0;
    tmp_pu21 = (uint32_t *)((int)tmp_pu19 + 0x52a1);
    tmp_u17 = 0x97;
  }
  if (((uint)tmp_pu21 & 2) != 0) {
    *(uint16_t *)tmp_pu21 = 0;
    tmp_u17 = tmp_u17 - 2;
    tmp_pu21 = (uint32_t *)((int)tmp_pu21 + 2);
  }
  tmp_u16 = 0;
  do {
    *(uint32_t *)((int)tmp_pu21 + tmp_u16) = 0;
    *(uint32_t *)((int)tmp_pu21 + tmp_u16 + 4) = 0;
    tmp_u16 = tmp_u16 + 8;
  } while (tmp_u16 < (tmp_u17 & 0xfffffff8));
  tmp_pu21 = (uint32_t *)((int)tmp_pu21 + tmp_u16);
  if ((tmp_u17 & 4) != 0) {
    *tmp_pu21 = 0;
    tmp_pu21 = tmp_pu21 + 1;
  }
  if ((tmp_u17 & 2) != 0) {
    *(uint16_t *)tmp_pu21 = 0;
    tmp_pu21 = (uint32_t *)((int)tmp_pu21 + 2);
  }
  if (tmp_b23) {
    *(uint8_t *)tmp_pu21 = 0;
  }
  tmp_pu21 = tmp_pu19 + 0x14ef;
  tmp_u17 = 0x100;
  tmp_b23 = ((uint)tmp_pu21 & 1) != 0;
  if (tmp_b23) {
    *(uint8_t *)(tmp_pu19 + 0x14ef) = 0;
    tmp_pu21 = (uint32_t *)((int)tmp_pu19 + 0x53bd);
    tmp_u17 = 0xff;
  }
  if (((uint)tmp_pu21 & 2) != 0) {
    *(uint16_t *)tmp_pu21 = 0;
    tmp_u17 = tmp_u17 - 2;
    tmp_pu21 = (uint32_t *)((int)tmp_pu21 + 2);
  }
  tmp_u16 = 0;
  do {
    *(uint32_t *)((int)tmp_pu21 + tmp_u16) = 0;
    *(uint32_t *)((int)tmp_pu21 + tmp_u16 + 4) = 0;
    tmp_u16 = tmp_u16 + 8;
  } while (tmp_u16 < (tmp_u17 & 0xfffffff8));
  tmp_pu21 = (uint32_t *)((int)tmp_pu21 + tmp_u16);
  if ((tmp_u17 & 4) != 0) {
    *tmp_pu21 = 0;
    tmp_pu21 = tmp_pu21 + 1;
  }
  if ((tmp_u17 & 2) != 0) {
    *(uint16_t *)tmp_pu21 = 0;
    tmp_pu21 = (uint32_t *)((int)tmp_pu21 + 2);
  }
  if (tmp_b23) {
    *(uint8_t *)tmp_pu21 = 0;
  }
  tmp_pu19[0x277] = 0xffffffff;
  tmp_pu19[0x278] = 0xffffffff;
  tmp_pu19[0x275] = 0xffffffff;
  tmp_pu19[0x276] = 0xffffffff;
  tmp_pu19[0x279] = 0xffffffff;
  tmp_pu19[0x274] = 0xffffffff;
  tmp_pu19[0x1a] = tmp_u6;
  tmp_pu19[0x4c] = tmp_u15;
  *(uint32_t *)(*(int *)(g_entities + tmp_i10 + 400) + 0x11c) = tmp_u2;
  *(uint32_t *)(*(int *)(g_entities + tmp_i10 + 400) + 0x120) = tmp_u3;
  *(uint32_t *)(*(int *)(g_entities + tmp_i10 + 400) + 0x128) = tmp_u4;
  *(uint32_t *)(*(int *)(g_entities + tmp_i10 + 400) + 0x124) = tmp_u5;
  tmp_pu19[0x1a6] = 0xffffffff;
  tmp_pu19[0x1a7] = 0xffffffff;
  tmp_i13 = -1;
  if (tmp_b24) {
    tmp_i13 = tmp_i22 - (uint)(0 < tmp_i22);
  }
  tmp_pu19[0x3c9] = 0;
  tmp_pu19[0x4d] = tmp_i13;
  tmp_pu19[0x3ca] = (uint)tmp_b9;
  tmp_i22 = tmp_pu19[0x2ee];
  if (tmp_i22 == 1) {
    if (g_unk_00abe908 - tmp_pu19[0x25d] < (int)GHIDRA_FIELD(g_redlimbotime, 12, 4)) {
      tmp_b9 = false;
      local_54 = 0;
    }
    else {
LAB_0005ece0:
      tmp_b9 = 0 < local_54;
    }
    if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) {
LAB_0005eab0:
      if (tmp_pu19[0x14de] == 0) {
        if ((int)GHIDRA_FIELD(g_maxlives, 12, 4) < 1) {
          tmp_pu19[0x4d] = 0xffffffff;
        }
        else {
          local_3c = GHIDRA_FIELD(g_maxlives, 12, 4) + -1;
          if ((float)GHIDRA_FIELD(g_timelimit, 8, 4) != 0.0) {
            if ((float)GHIDRA_FIELD(g_timelimit, 8, 4) * 60000.0 <= (float)(g_unk_00abe908 - g_unk_00abe918)) {
              local_3c = -1;
            }
            else {
              tmp_f7 = (1.0 - (float)(g_unk_00abe908 - g_unk_00abe918) /
                             ((float)GHIDRA_FIELD(g_timelimit, 8, 4) * 60000.0)) * (float)(GHIDRA_FIELD(g_maxlives, 12, 4) + -1)
              ;
              local_3c = (int)ROUND(tmp_f7);
              local_3c = (uint)(0.5 <= tmp_f7 - (float)local_3c) + local_3c;
              if ((((g_XPSave[0xc] & 1) != 0) && (tmp_i13 = tmp_pu19[0x14df], tmp_i13 < local_3c)) &&
                 (tmp_i13 != -999)) {
                local_3c = tmp_i13;
              }
            }
          }
          tmp_pu19[0x4d] = local_3c;
        }
        if ((0 < (int)GHIDRA_FIELD(g_axismaxlives, 12, 4)) || (0 < (int)GHIDRA_FIELD(g_alliedmaxlives, 12, 4))) {
          if (tmp_i22 == 1) {
            local_40 = GHIDRA_FIELD(g_axismaxlives, 12, 4) + -1;
            if ((float)GHIDRA_FIELD(g_timelimit, 8, 4) != 0.0) {
              if ((float)GHIDRA_FIELD(g_timelimit, 8, 4) * 60000.0 <= (float)(g_unk_00abe908 - g_unk_00abe918)) {
                local_40 = -1;
              }
              else {
                tmp_f7 = (1.0 - (float)(g_unk_00abe908 - g_unk_00abe918) /
                               ((float)GHIDRA_FIELD(g_timelimit, 8, 4) * 60000.0)) *
                        (float)(GHIDRA_FIELD(g_axismaxlives, 12, 4) + -1);
                local_40 = (int)ROUND(tmp_f7);
                local_40 = (uint)(0.5 <= tmp_f7 - (float)local_40) + local_40;
                if ((((g_XPSave[0xc] & 1) != 0) && (tmp_i22 = tmp_pu19[0x14df], tmp_i22 < local_40)) &&
                   (tmp_i22 != -999)) {
                  local_40 = tmp_i22;
                }
              }
            }
            tmp_pu19[0x4d] = local_40;
          }
          else {
            tmp_i22 = GHIDRA_FIELD(g_alliedmaxlives, 12, 4) + -1;
            if ((float)GHIDRA_FIELD(g_timelimit, 8, 4) != 0.0) {
              if ((float)GHIDRA_FIELD(g_timelimit, 8, 4) * 60000.0 <= (float)(g_unk_00abe908 - g_unk_00abe918)) {
                tmp_i22 = -1;
              }
              else {
                tmp_f7 = (1.0 - (float)(g_unk_00abe908 - g_unk_00abe918) /
                               ((float)GHIDRA_FIELD(g_timelimit, 8, 4) * 60000.0)) *
                        (float)(GHIDRA_FIELD(g_alliedmaxlives, 12, 4) + -1);
                tmp_i22 = (int)ROUND(tmp_f7);
                tmp_i22 = tmp_i22 + (uint)(0.5 <= tmp_f7 - (float)tmp_i22);
                if ((((g_XPSave[0xc] & 1) != 0) && (tmp_i13 = tmp_pu19[0x14df], tmp_i13 < tmp_i22)) &&
                   (tmp_i13 != -999)) {
                  tmp_i22 = tmp_i13;
                }
              }
            }
            tmp_pu19[0x4d] = tmp_i22;
          }
        }
        tmp_pu19[0x14de] = 1;
      }
      else if ((0 < (int)GHIDRA_FIELD(g_axismaxlives, 12, 4)) || (0 < (int)GHIDRA_FIELD(g_alliedmaxlives, 12, 4))) {
        tmp_i18 = GHIDRA_FIELD(g_axismaxlives, 12, 4);
        if (tmp_i22 != 1) {
          tmp_i18 = GHIDRA_FIELD(g_alliedmaxlives, 12, 4);
        }
        if (tmp_i18 < tmp_i13) {
          tmp_pu19[0x4d] = tmp_i18;
        }
      }
    }
LAB_0005e70e:
    if ((!tmp_b9) || (GHIDRA_FIELD(g_teamChangeKills, 12, 4) != 0)) goto LAB_0005ea20;
    ClientSpawn(tmp_pu11,0,1,0);
  }
  else {
    if (tmp_i22 != 2) {
      tmp_b9 = 0 < local_54;
      goto LAB_0005e70e;
    }
    if ((int)GHIDRA_FIELD(g_bluelimbotime, 12, 4) <= g_unk_00abe908 - tmp_pu19[0x25d]) goto LAB_0005ece0;
    if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) {
      tmp_b9 = false;
      local_54 = 0;
      goto LAB_0005eab0;
    }
    local_54 = 0;
LAB_0005ea20:
    ClientSpawn(tmp_pu11,0,1,1);
  }
  if (tmp_pu19[0x2ee] != 3) {
    if (600 < g_unk_00abe908 - g_unk_00abe918) {
      if ((tmp_b24) && (GHIDRA_FIELD(g_gametype, 12, 4) != 5)) {
        tmp_pu19[0x4d] = tmp_pu19[0x4d] + 1;
      }
      if ((local_54 < 1) || (GHIDRA_FIELD(g_teamChangeKills, 12, 4) != 0)) {
        *(uint32_t *)(g_entities + tmp_i10 + 0x2c8) = 0;
        *(uint32_t *)(g_entities + tmp_i10 + 0x14c) = 0x4000000;
        tmp_pu19[0x34] = 0;
        tmp_pu19[1] = 3;
        limbo(tmp_pu11,0);
        if (tmp_pu19[0x2ee] == 3) goto LAB_0005e7dd;
      }
    }
    tmp_u15 = va("print \"[lof]%s^7 [lon]entered the game\n\"",tmp_pu19 + 0x17e);
    trap_SendServerCommand(0xffffffff,tmp_u15);
  }
LAB_0005e7dd:
  G_LogPrintf("ClientBegin: %i\n",param_1);
  if (((GHIDRA_FIELD(g_gametype, 12, 4) != 5) && (GHIDRA_FIELD(g_enforcemaxlives, 12, 4) == 1)) &&
     ((0 < (int)GHIDRA_FIELD(g_maxlives, 12, 4) ||
      ((0 < (int)GHIDRA_FIELD(g_axismaxlives, 12, 4) || (0 < (int)GHIDRA_FIELD(g_alliedmaxlives, 12, 4))))))) {
    tmp_i22 = tmp_i12 + level + 0x61c;
    G_LogPrintf("EnforceMaxLives-GUID: %s\n",tmp_i22);
    AddMaxLivesGUID(tmp_i22);
    tmp_i12 = tmp_i12 + level + 0x63d;
    G_LogPrintf("EnforceMaxLives-IP: %s\n",tmp_i12);
    AddMaxLivesBan(tmp_i12);
  }
  CalculateRanks(1);
  G_TeamCountPlayers();
  *(uint32_t *)(g_entities + tmp_i10 + 0x4bc) = 0;
  if ((*(char *)(*(int *)(g_entities + tmp_i10 + 400) + 0x61c) == '\0') ||
     (tmp_s14 = strlen((char *)(*(int *)(g_entities + tmp_i10 + 400) + 0x61c)), tmp_s14 != 0x20)) {
    if ((tmp_u1 >> 3 & 1) == 0) {
      trap_SendServerCommand(param_1,"getnguid");
    }
  }
  else {
    if (*(int *)(g_entities + tmp_i10 + 0x5fc) == 0) {
      if (g_unk_02af58b8 != 0) {
        G_SetDefaultLevel_part_4();
      }
      nitrox_SQLite_LoadSingleUser(tmp_pu11);
      tmp_u15 = nitrox_XPSave_LoadXP(tmp_pu11);
      *(uint32_t *)(g_entities + tmp_i10 + 0x5fc) = tmp_u15;
    }
    if (tmp_pu19[0x3c4] != 0) {
      G_shrubbot_greeting(tmp_pu11);
      tmp_pu19[0x3c4] = 0;
    }
  }
  if (tmp_b8) {
    G_LuaHook_ClientBegin(param_1);
  }
  return;
}

void ClientDisconnect(int param_1)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  uint tmp_u4;
  uint16_t *tmp_pu5;
  uint32_t tmp_u6;
  uint tmp_u7;
  int tmp_i8;
  uint8_t *tmp_pu9;
  int tmp_i10;
  int tmp_i11;
  bool tmp_b12;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x5f019;
  tmp_i1 = param_1 * 0x600;
  tmp_pu2 = (uint32_t *)(g_entities + tmp_i1);
  if (*(int *)(g_entities + tmp_i1 + 400) == 0) {
    return;
  }
  if (*(int *)(*(int *)(g_entities + tmp_i1 + 400) + 0x54d8) == 0) {
    nitrox_XPSave_WriteXP(tmp_pu2);
  }
  G_LuaHook_ClientDisconnect(param_1);
  Bot_Event_ClientDisConnected(param_1);
  if (((*(int *)(*(int *)(g_entities + tmp_i1 + 400) + 0xb3c) != 0) &&
      (NxAC_Log(tmp_pu2,1,1,"]^5 Disconnected before screenshot was received"),
      0 < *(int *)(NxAC_Violations + *(int *)(*(int *)(g_entities + tmp_i1 + 400) + 0xb40) * 0xc + 4)
      )) && (0 < (int)GHIDRA_FIELD(n_NxAC, 12, 4))) {
    NxAC_BanClient(tmp_pu2);
  }
  G_RemoveClientFromFireteams(param_1,1,0);
  G_RemoveFromAllIgnoreLists(param_1);
  G_LeaveTank(tmp_pu2,0,0);
  if (0 < g_unk_00abe938) {
    tmp_i10 = 0;
LAB_0005f122:
    do {
      tmp_i8 = (&g_unk_00abe944)[tmp_i10] * 0x600;
      tmp_i3 = *(int *)(g_entities + tmp_i8 + 400);
      if ((*(int *)(tmp_i3 + 3000) == 3) && (*(int *)(tmp_i3 + 0xbc0) == 2)) {
        if (*(int *)(tmp_i3 + 0xbc4) == param_1) {
          StopFollowing(g_entities + tmp_i8);
          tmp_i3 = *(int *)(g_entities + tmp_i8 + 400);
          goto LAB_0005f0e8;
        }
      }
      else {
LAB_0005f0e8:
        if (((*(byte *)(tmp_i3 + 0xd) & 0x40) != 0) && (*(int *)(tmp_i3 + 0xbc4) == param_1)) {
          Cmd_FollowCycle_f(g_entities + tmp_i8,1);
          tmp_i3 = *(int *)(g_entities + tmp_i8 + 400);
        }
      }
      if ((*(int *)(tmp_i3 + 0x69c) <= g_unk_00abe908) || (*(int *)(tmp_i3 + 0x698) != param_1)) {
        tmp_i10 = tmp_i10 + 1;
        if (g_unk_00abe938 <= tmp_i10) break;
        goto LAB_0005f122;
      }
      tmp_i11 = tmp_i10 + 1;
      *(uint32_t *)(tmp_i3 + 0x698) = 0xffffffff;
      *(uint32_t *)(*(int *)(g_entities + tmp_i8 + 400) + 0x69c) = 0xffffffff;
      trap_SendServerCommand((&g_unk_00abe944)[tmp_i10],"complaint -2");
      tmp_i10 = tmp_i11;
    } while (tmp_i11 < g_unk_00abe938);
  }
  if (GHIDRA_FIELD(g_landminetimeout, 12, 4) != 0) {
    nitrox_FadeLandmines(tmp_pu2);
  }
  if (GHIDRA_FIELD(n_tripmineTimeout, 12, 4) != 0) {
    nitrox_RemoveTripmines(tmp_pu2);
  }
  nitrox_FadeSatchels(tmp_pu2);
  nitrox_FadeAirstrikes(tmp_pu2);
  G_FadeItems(tmp_pu2,0x19);
  if ((GHIDRA_FIELD(g_missileCams, 12, 4) & 2) != 0) {
    G_FadeItems(tmp_pu2,0x33);
  }
  if ((GHIDRA_FIELD(g_missileCams, 12, 4) & 1) != 0) {
    G_FadeItems(tmp_pu2,0xf);
  }
  if ((GHIDRA_FIELD(g_missileCams, 12, 4) & 4) != 0) {
    G_FadeItems(tmp_pu2,0x26);
    G_FadeItems(tmp_pu2,0x27);
  }
  tmp_pu9 = mapEntityData;
  tmp_i10 = (tmp_i1 >> 9) * -0x55555555;
  do {
    tmp_i3 = G_FindMapEntityData(mapEntityData,tmp_i10);
    if (tmp_i3 != 0) {
      G_FreeMapEntityData(tmp_pu9,tmp_i3);
    }
    tmp_i3 = G_FindMapEntityDataSingleClient(tmp_pu9,0,*tmp_pu2,0xffffffff);
    while (tmp_i3 != 0) {
      tmp_i8 = G_FindMapEntityDataSingleClient(tmp_pu9,tmp_i3,*tmp_pu2,0xffffffff);
      G_FreeMapEntityData(tmp_pu9,tmp_i3);
      tmp_i3 = tmp_i8;
    }
    tmp_pu9 = tmp_pu9 + 0xc034;
  } while (tmp_pu9 != &g_unk_02d98ac8);
  tmp_i3 = *(int *)(g_entities + tmp_i1 + 400);
  if (((*(int *)(tmp_i3 + 0x5ac) != 2) || (*(int *)(tmp_i3 + 3000) == 3)) ||
     ((*(byte *)(tmp_i3 + 0xd) & 0x40) != 0)) goto LAB_0005f302;
  TossClientItems(tmp_pu2);
  if (*(int *)(*(int *)(g_entities + tmp_i1 + 400) + 0x164) == 0) {
    if (*(int *)(*(int *)(g_entities + tmp_i1 + 400) + 0x168) != 0) goto LAB_0005f7f0;
  }
  else {
    tmp_i3 = BG_FindItem("Red Flag");
    if (tmp_i3 == 0) {
      tmp_i3 = BG_FindItem("Objective");
      *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 0x164) = 0;
      if (*(int *)(*(int *)(g_entities + tmp_i1 + 400) + 0x168) != 0) goto LAB_0005f7f0;
LAB_0005f814:
      if (tmp_i3 == 0) goto LAB_0005f69f;
    }
    else {
      *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 0x164) = 0;
      if (*(int *)(*(int *)(g_entities + tmp_i1 + 400) + 0x168) != 0) {
LAB_0005f7f0:
        tmp_i3 = BG_FindItem("Blue Flag");
        if (tmp_i3 == 0) {
          tmp_i3 = BG_FindItem("Objective");
        }
        *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 0x168) = 0;
        goto LAB_0005f814;
      }
    }
    local_28 = 0;
    local_24 = 0;
    local_20 = 0;
    tmp_i10 = LaunchItem(tmp_i3,tmp_i1 + 0x93e608,&local_28,tmp_i10,0x1000);
    *(uint32_t *)(tmp_i10 + 0xa8) = *(uint32_t *)(g_entities + tmp_i1 + 0x90);
    tmp_u6 = *(uint32_t *)(g_entities + tmp_i1 + 0x248);
    *(uint32_t *)(tmp_i10 + 0x248) = tmp_u6;
    tmp_u6 = va("%s dropped.",tmp_u6);
    Bot_Util_SendTrigger(tmp_i10,0,tmp_u6,"dropped");
    *(uint32_t *)(g_entities + tmp_i1 + 0x90) = 0;
    *(uint32_t *)(g_entities + tmp_i1 + 0x248) = 0;
  }
LAB_0005f69f:
  tmp_u6 = G_createStats(tmp_pu2);
  G_LogPrintf("WeaponStats: %s\n",tmp_u6);
LAB_0005f302:
  G_LogPrintf("ClientDisconnect: %i\n",param_1);
  trap_UnlinkEntity(tmp_pu2);
  *(char **)(g_entities + tmp_i1 + 0x1a4) = "disconnected";
  *(uint32_t *)(g_entities + tmp_i1 + 0xa4) = 0;
  *(uint32_t *)(g_entities + tmp_i1 + 0x194) = 0;
  *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 0x5ac) = 0;
  *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 300) = 0;
  *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 3000) = 0;
  *(uint32_t *)(g_entities + tmp_i1 + 0x368) = 0;
  *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 0x54d4) = 0;
  *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 0x54d8) = 0;
  if ((g_entities[tmp_i1 + 0x128] & 8) == 0) {
    nitrox_SendStatsToMaster(tmp_pu2);
  }
  tmp_u4 = 0;
  do {
    *(uint32_t *)((int)&g_unk_02b9922c + tmp_u4 + param_1 * 0x40) = 0;
    *(uint32_t *)((int)&g_unk_02b99230 + tmp_u4 + param_1 * 0x40) = 0;
    tmp_u4 = tmp_u4 + 8;
  } while (tmp_u4 < 0x40);
  *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 0xb88) = 0;
  *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 0xb8c) = 0;
  tmp_i10 = *(int *)(g_entities + tmp_i1 + 400);
  tmp_u4 = 0x40;
  tmp_pu5 = (uint16_t *)(tmp_i10 + 0xb48);
  tmp_b12 = ((uint)tmp_pu5 & 1) != 0;
  if (tmp_b12) {
    *(uint8_t *)(tmp_i10 + 0xb48) = 0;
    tmp_pu5 = (uint16_t *)(tmp_i10 + 0xb49);
    tmp_u4 = 0x3f;
  }
  if (((uint)tmp_pu5 & 2) != 0) {
    *tmp_pu5 = 0;
    tmp_u4 = tmp_u4 - 2;
    tmp_pu5 = tmp_pu5 + 1;
  }
  tmp_u7 = 0;
  do {
    *(uint32_t *)((int)tmp_pu5 + tmp_u7) = 0;
    *(uint32_t *)((int)tmp_pu5 + tmp_u7 + 4) = 0;
    tmp_u7 = tmp_u7 + 8;
  } while (tmp_u7 < (tmp_u4 & 0xfffffff8));
  tmp_pu2 = (uint32_t *)((int)tmp_pu5 + tmp_u7);
  if ((tmp_u4 & 4) != 0) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + 1;
  }
  if ((tmp_u4 & 2) != 0) {
    *(uint16_t *)tmp_pu2 = 0;
    tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
  }
  if (tmp_b12) {
    *(uint8_t *)tmp_pu2 = 0;
  }
  (&g_unk_02b9a22c)[param_1] = 0;
  *(uint *)(g_entities + tmp_i1 + 0x128) = *(uint *)(g_entities + tmp_i1 + 0x128) & 0xfffffff7;
  trap_SetConfigstring(param_1 + 0x2b1,&g_unk_0026ea14);
  CalculateRanks(1);
  G_TeamCountPlayers();
  *(uint32_t *)(g_entities + tmp_i1 + 0x5e8) = 0;
  *(uint32_t *)(g_entities + tmp_i1 + 0x5fc) = 0;
  (&g_unk_02b99128)[param_1] = 0;
  *(uint32_t *)(*(int *)(g_entities + tmp_i1 + 400) + 0x6a0) = 0;
  *(uint8_t *)(*(int *)(g_entities + tmp_i1 + 400) + 0xf48) = 0;
  G_verifyMatchState(0x10);
  nitrox_ClearSocketInfos(param_1);
  return;
}

uint32_t ClientConnect(int param_1,int param_2,int param_3)
{
  int *tmp_pi1;
  uint *tmp_pu2;
  uint *tmp_pu3;
  int tmp_i4;
  bool tmp_b5;
  bool tmp_b6;
  bool tmp_b7;
  bool tmp_b8;
  char tmp_c9;
  uint tmp_u10;
  int tmp_i11;
  int tmp_i12;
  uint tmp_u13;
  size_t tmp_s14;
  void *__s;
  uint32_t tmp_u15;
  char *tmp_pc16;
  int tmp_i17;
  uint *tmp_pu18;
  bool tmp_b19;
  uint *tmp_pu20;
  int tmp_i21;
  byte *tmp_pb22;
  byte *tmp_pb23;
  uint8_t tmp_u24;
  bool tmp_b25;
  bool tmp_b26;
  uint8_t tmp_u27;
  byte tmp_b28;
  char *__s_00;
  byte *local_1ed4;
  char *local_1ec0;
  uint *local_1eac;
  uint32_t local_1ea7;
  uint32_t local_1ea3;
  uint32_t local_1e9f;
  uint32_t local_1e9b;
  uint32_t local_1e97;
  uint32_t local_1e93;
  uint32_t local_1e8f;
  uint32_t local_1e8b;
  uint16_t local_1e87;
  uint32_t local_1e85;
  uint8_t local_1e81;
  uint32_t local_1e80 [7];
  uint32_t local_1e64;
  uint32_t auStack_1e60 [8];
  uint8_t local_1e40 [36];
  uint32_t local_1e1c;
  uint32_t local_1e18 [63];
  uint32_t local_1d1c;
  uint local_1d18 [575];
  uint32_t local_141c;
  uint32_t local_1418 [255];
  uint local_101c;
  uint32_t local_1018 [255];
  uint32_t local_c1c;
  uint32_t local_c18 [255];
  uint32_t local_81c;
  uint32_t local_818 [513];
  uint32_t uStack_14;
  
  tmp_b28 = 0;
  local_1d18[0x3f] = 0;
  tmp_u10 = 0;
  do {
    tmp_u13 = tmp_u10;
    *(uint32_t *)((int)local_1d18 + tmp_u13 + 0x100) = 0;
    *(uint32_t *)((int)local_1d18 + tmp_u13 + 0x104) = 0;
    tmp_u10 = tmp_u13 + 8;
  } while (tmp_u13 + 8 < 0x3f8);
  *(uint32_t *)((int)local_1d18 + tmp_u13 + 0x108) = 0;
  local_1d18[0x13f] = 0;
  tmp_u10 = 0;
  do {
    tmp_u13 = tmp_u10;
    *(uint32_t *)((int)local_1d18 + tmp_u13 + 0x500) = 0;
    *(uint32_t *)((int)local_1d18 + tmp_u13 + 0x504) = 0;
    tmp_u10 = tmp_u13 + 8;
  } while (tmp_u13 + 8 < 0x3f8);
  *(uint32_t *)((int)local_1d18 + tmp_u13 + 0x508) = 0;
  local_1eac = (uint *)0x0;
  local_141c = 0;
  tmp_u10 = 0;
  do {
    tmp_u13 = tmp_u10;
    *(uint32_t *)((int)local_1418 + tmp_u13) = 0;
    *(uint32_t *)((int)local_1418 + tmp_u13 + 4) = 0;
    tmp_u10 = tmp_u13 + 8;
  } while (tmp_u13 + 8 < 0x3f8);
  *(uint32_t *)((int)local_1418 + tmp_u13 + 8) = 0;
  local_101c = 0;
  tmp_u10 = 0;
  do {
    tmp_u13 = tmp_u10;
    *(uint32_t *)((int)local_1018 + tmp_u13) = 0;
    *(uint32_t *)((int)local_1018 + tmp_u13 + 4) = 0;
    tmp_u10 = tmp_u13 + 8;
  } while (tmp_u13 + 8 < 0x3f8);
  *(uint32_t *)((int)local_1018 + tmp_u13 + 8) = 0;
  tmp_u10 = 0;
  do {
    tmp_u13 = tmp_u10;
    *(uint32_t *)((int)local_c18 + tmp_u13) = 0;
    *(uint32_t *)((int)local_c18 + tmp_u13 + 4) = 0;
    tmp_u10 = tmp_u13 + 8;
  } while (tmp_u13 + 8 < 0x3f8);
  *(uint32_t *)((int)local_c18 + tmp_u13 + 8) = 0;
  tmp_u10 = 0;
  do {
    tmp_u13 = tmp_u10;
    *(uint32_t *)((int)local_818 + tmp_u13) = 0;
    *(uint32_t *)((int)local_818 + tmp_u13 + 4) = 0;
    tmp_u10 = tmp_u13 + 8;
  } while (tmp_u13 + 8 < 0x3f8);
  *(uint32_t *)((int)local_818 + tmp_u13 + 8) = 0;
  tmp_u10 = 0;
  local_1e64 = 0;
  do {
    *(uint32_t *)((int)auStack_1e60 + tmp_u10) = 0;
    *(uint32_t *)((int)auStack_1e60 + tmp_u10 + 4) = 0;
    tmp_u10 = tmp_u10 + 8;
  } while (tmp_u10 < 0x20);
  tmp_u10 = 0;
  do {
    tmp_u13 = tmp_u10;
    *(uint32_t *)((int)local_818 + tmp_u13 + 0x400) = 0;
    *(uint32_t *)((int)local_818 + tmp_u13 + 0x404) = 0;
    tmp_u10 = tmp_u13 + 8;
  } while (tmp_u13 + 8 < 0x3f8);
  *(uint32_t *)((int)local_818 + tmp_u13 + 0x408) = 0;
  local_1ea3 = 0;
  local_1e9f = 0;
  local_1e9b = 0;
  local_1e85 = 0;
  local_1ea7 = 0;
  local_1e81 = 0;
  tmp_u10 = 0;
  do {
    tmp_u13 = tmp_u10;
    *(uint32_t *)((int)local_1e80 + tmp_u13) = 0;
    *(uint32_t *)((int)local_1e80 + tmp_u13 + 4) = 0;
    tmp_u10 = tmp_u13 + 8;
  } while (tmp_u13 + 8 < 0x18);
  *(uint32_t *)((int)local_1e80 + tmp_u13 + 8) = 0;
  uStack_14 = 0x5f86d;
  local_818[0xff] = 0;
  local_81c = 0;
  local_c1c = 0;
  local_1e8b = 0;
  local_1e1c = 0;
  local_1e97 = 0;
  local_1e93 = 0;
  local_1e8f = 0;
  local_1e87 = 0;
  tmp_u10 = 0;
  do {
    tmp_u13 = tmp_u10;
    *(uint32_t *)((int)local_1e18 + tmp_u13) = 0;
    *(uint32_t *)((int)local_1e18 + tmp_u13 + 4) = 0;
    tmp_u10 = tmp_u13 + 8;
  } while (tmp_u13 + 8 < 0xf8);
  *(uint32_t *)((int)local_1e18 + tmp_u13 + 8) = 0;
  local_1d1c = 0;
  tmp_u10 = 0;
  do {
    tmp_u13 = tmp_u10;
    *(uint32_t *)((int)local_1d18 + tmp_u13) = 0;
    *(uint32_t *)((int)local_1d18 + tmp_u13 + 4) = 0;
    tmp_u10 = tmp_u13 + 8;
  } while (tmp_u13 + 8 < 0xf8);
  *(uint32_t *)((int)local_1d18 + tmp_u13 + 8) = 0;
  tmp_i11 = trap_Cvar_VariableIntegerValue("sv_demoState");
  tmp_i12 = trap_Cvar_VariableIntegerValue("sv_demoClients");
  tmp_b5 = tmp_i11 - 1U < 3;
  tmp_i11 = param_1 * 0x600;
  *(uint *)(*(int *)(g_entities + tmp_i11 + 400) + 0x54d8) = (uint)(tmp_b5 && param_1 < tmp_i12);
  tmp_pu2 = local_1d18 + 0x3f;
  trap_GetUserinfo(param_1,tmp_pu2,0x400);
  (&g_unk_02b99128)[param_1] = 0;
  tmp_u10 = 0;
  do {
    *(uint32_t *)((int)&g_unk_02b9922c + tmp_u10 + param_1 * 0x40) = 0;
    *(uint32_t *)((int)&g_unk_02b99230 + tmp_u10 + param_1 * 0x40) = 0;
    tmp_u10 = tmp_u10 + 8;
  } while (tmp_u10 < 0x40);
  nitrox_ClearSocketInfos(param_1);
  (&g_unk_02b9a22c)[param_1] = 0;
  tmp_b25 = param_3 == 0;
  tmp_b5 = !tmp_b5;
  tmp_b6 = param_1 >= tmp_i12;
  tmp_b19 = (tmp_b5 || tmp_b6) && tmp_b25;
  tmp_pu3 = local_1d18 + 0x13f;
  local_1eac = tmp_pu2;
  tmp_b8 = false;
_L1854:
  do {
    tmp_pc16 = (char *)&local_101c;
    Info_NextPair(&local_1eac,&local_141c,&local_101c);
    if ((char)local_141c == '\0') {
      tmp_b5 = false;
LAB_0005fe1f:
      if (tmp_b19) goto LAB_00060120;
      tmp_u10 = 0;
      goto LAB_000601c3;
    }
    tmp_i12 = nitrox_GetTokenForString(&local_141c);
  } while (7 < tmp_i12 - 0x76U);
  tmp_b26 = (&switchD_0005fcef::switchdataD_00244d80)[tmp_i12 - 0x76U] == 0xffd4b9ec;
  switch(tmp_i12) {
  case 0x76:
    tmp_pu20 = &local_101c;
    if ((tmp_b5 || tmp_b6) && tmp_b25) {
      do {
        tmp_pu18 = tmp_pu20;
        tmp_u13 = *tmp_pu18 + 0xfefefeff & ~*tmp_pu18;
        tmp_u10 = tmp_u13 & 0x80808080;
        tmp_pu20 = tmp_pu18 + 1;
      } while (tmp_u10 == 0);
      if ((tmp_u13 & 0x8080) == 0) {
        tmp_pu20 = (uint *)((int)tmp_pu18 + 6);
        tmp_u10 = tmp_u10 >> 0x10;
      }
      if ((char *)((int)tmp_pu20 +
                  ((-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)) - (int)&local_101c)) !=
          (char *)0x20) {
        G_LogPrintf("[DROPCLIENT] Client %d Invalid NGUID length (%s)\n",param_1,&local_101c);
        tmp_pc16 = "Invalid NGUID length";
        goto LAB_0006059e;
      }
      if ((GHIDRA_FIELD(g_GUIDChecks, 12, 4) == 0) ||
         (tmp_i12 = nitrox_GUIDCheckValid(&local_1e85,tmp_pu3), tmp_i12 != 0)) {
        if (((param_2 != 0) && ((g_XPSave[0xc] & 1) != 0)) &&
           (((tmp_i12 = trap_Cvar_VariableIntegerValue("sv_wwwDlDisconnected"), tmp_i12 == 0 ||
             ((g_XPSave[0xc] & 8) != 0)) && (0 < g_unk_00abe938)))) {
          tmp_i21 = 0;
          tmp_i12 = g_unk_00abe938;
          do {
            while ((tmp_i4 = (&g_unk_00abe944)[tmp_i21], param_1 != tmp_i4 &&
                   (tmp_i17 = tmp_i4 * 0x54dc + level, *(int *)(tmp_i17 + 0x54d8) == 0))) {
              tmp_i12 = Q_stricmp(&local_101c,tmp_i17 + 0x61c);
              if (tmp_i12 == 0) {
                G_LogPrintf("[DROPCLIENT] Client %i Duplicate NGUID detected on the server\n",tmp_i4)
                ;
                trap_DropClient(tmp_i4,"Duplicate NGUID detected on the server",0);
              }
              tmp_i21 = tmp_i21 + 1;
              tmp_i12 = g_unk_00abe938;
              if (g_unk_00abe938 <= tmp_i21) goto LAB_00060032;
            }
            tmp_i21 = tmp_i21 + 1;
          } while (tmp_i21 < tmp_i12);
        }
LAB_00060032:
        if ((((GHIDRA_FIELD(g_gametype, 12, 4) == 5) || (GHIDRA_FIELD(g_enforcemaxlives, 12, 4) == 0)) ||
            (((int)GHIDRA_FIELD(g_maxlives, 12, 4) < 1 &&
             (((int)GHIDRA_FIELD(g_axismaxlives, 12, 4) < 1 && ((int)GHIDRA_FIELD(g_alliedmaxlives, 12, 4) < 1)))))) ||
           (tmp_i12 = G_FilterMaxLivesPacket(&local_101c), tmp_i12 == 0)) goto LAB_00060079;
LAB_0006057f:
        G_LogPrintf("[DROPCLIENT] Client %d Max lives enforcement temp ban\n",param_1);
        tmp_pc16 = 
        "Max Lives Enforcement Temp Ban. You will be able to reconnect when the next round starts. This ban is enforced to ensure you don\'t reconnect to get additional lives."
        ;
        goto LAB_0006059e;
      }
      tmp_pc16 = (char *)tmp_pu3;
      G_LogPrintf("[DROPCLIENT] Client %i %s\n",param_1,tmp_pu3);
LAB_0005fe1a:
      tmp_b5 = true;
      goto LAB_0005fe1f;
    }
LAB_00060079:
    Q_strncpyz(&local_1e85,&local_101c,0x21);
    goto _L1854;
  case 0x77:
    Q_strncpyz(&local_1e97,&local_101c,0x12);
    goto _L1854;
  case 0x78:
    tmp_i12 = 10;
    tmp_pu20 = &local_101c;
    tmp_pc16 = "localhost";
    do {
      if (tmp_i12 == 0) break;
      tmp_i12 = tmp_i12 + -1;
      tmp_b26 = (char)*tmp_pu20 == *tmp_pc16;
      tmp_pu20 = (uint *)((int)tmp_pu20 + (uint)tmp_b28 * -2 + 1);
      tmp_pc16 = tmp_pc16 + (uint)tmp_b28 * -2 + 1;
    } while (tmp_b26);
    tmp_b7 = true;
    if (!tmp_b26) {
      tmp_b7 = tmp_b8;
    }
    tmp_b8 = tmp_b7;
    if (tmp_b19) {
      tmp_i12 = G_FilterIPBanPacket(&local_c1c);
      if (tmp_i12 != 0) {
        G_LogPrintf("[DROPCLIENT] Client %d g_banIPs match (%s)\n",param_1,&local_101c);
        tmp_pc16 = "Your IP address is banned from this server.";
LAB_0006059e:
        Com_sprintf(tmp_pu3,0x400,tmp_pc16);
        goto LAB_0005fe1a;
      }
      if (((!tmp_b7) && (g_password[0x10] != '\0')) &&
         (tmp_i12 = Q_stricmp(0x2e4a1f0,"none"), tmp_i12 != 0)) {
        tmp_i12 = strcmp(g_password + 0x10,(char *)&local_81c);
        if ((tmp_i12 != 0) &&
           ((sv_privatepassword[0x10] == '\0' ||
            (tmp_i12 = strcmp(sv_privatepassword + 0x10,(char *)&local_81c), tmp_i12 != 0)))) {
          G_LogPrintf("[DROPCLIENT] Client %d Invalid password\n",param_1);
          tmp_pc16 = "Invalid password";
          goto LAB_0006059e;
        }
      }
      local_1ec0 = "localhost";
      __s_00 = (char *)&local_1ea7;
      Q_strncpyz(__s_00,&local_101c,0x10);
      tmp_pc16 = __s_00;
      tmp_c9 = (char)local_1ea7;
      while (tmp_c9 != '\0') {
        if (tmp_c9 == ':') {
          *tmp_pc16 = '\0';
          break;
        }
        tmp_pc16 = tmp_pc16 + 1;
        tmp_c9 = *tmp_pc16;
      }
      tmp_b26 = GHIDRA_FIELD(g_IPChecks, 12, 4) == 0;
      if (!tmp_b26) {
        tmp_i12 = 10;
        tmp_pc16 = __s_00;
        do {
          if (tmp_i12 == 0) break;
          tmp_i12 = tmp_i12 + -1;
          tmp_b26 = *tmp_pc16 == *local_1ec0;
          tmp_pc16 = tmp_pc16 + (uint)tmp_b28 * -2 + 1;
          local_1ec0 = local_1ec0 + (uint)tmp_b28 * -2 + 1;
        } while (tmp_b26);
        if (!tmp_b26) {
          tmp_s14 = strlen(__s_00);
          if ((tmp_s14 < 0x11) && ((char)local_1ea7 != '\0')) {
            tmp_i12 = 0;
            tmp_i21 = 0;
            tmp_c9 = (char)local_1ea7;
            do {
              if (tmp_c9 == '.') {
                tmp_i21 = tmp_i21 + 1;
              }
              else if (9 < (byte)(tmp_c9 - 0x30U)) goto LAB_000608c8;
              tmp_i12 = tmp_i12 + 1;
              tmp_c9 = __s_00[tmp_i12];
            } while ((tmp_c9 != '\0') && (tmp_i12 != 0x10));
            if (tmp_i21 == 3) goto LAB_00060530;
          }
LAB_000608c8:
          G_LogPrintf("[DROPCLIENT] Client %d Invalid IP Address (%s)\n",param_1,__s_00);
          tmp_pc16 = "Invalid IP Address (%s)";
          goto LAB_0005fe01;
        }
      }
LAB_00060530:
      if ((((GHIDRA_FIELD(g_gametype, 12, 4) != 5) && (GHIDRA_FIELD(g_enforcemaxlives, 12, 4) != 0)) &&
          ((0 < (int)GHIDRA_FIELD(g_maxlives, 12, 4) ||
           ((0 < (int)GHIDRA_FIELD(g_axismaxlives, 12, 4) || (0 < (int)GHIDRA_FIELD(g_alliedmaxlives, 12, 4))))))) &&
         (tmp_i12 = G_FilterMaxLivesIPPacket(&local_101c), tmp_i12 != 0)) goto LAB_0006057f;
    }
    Q_strncpyz(&local_c1c,&local_101c,0x400);
    goto _L1854;
  case 0x79:
    Q_strncpyz(local_818 + 0xff,&local_101c,0x400);
    goto _L1854;
  case 0x7a:
    break;
  default:
    goto _L1854;
  case 0x7d:
    Q_strncpyz(&local_81c,&local_101c,0x400);
    goto _L1854;
  }
  tmp_pu20 = &local_101c;
  if (!tmp_b5 && !tmp_b6 || !tmp_b25) {
    Q_strncpyz(&local_1e64,&local_101c,0x24);
    goto _L1854;
  }
  do {
    tmp_pu18 = tmp_pu20;
    tmp_u13 = *tmp_pu18 + 0xfefefeff & ~*tmp_pu18;
    tmp_u10 = tmp_u13 & 0x80808080;
    tmp_pu20 = tmp_pu18 + 1;
  } while (tmp_u10 == 0);
  if ((tmp_u13 & 0x8080) == 0) {
    tmp_pu20 = (uint *)((int)tmp_pu18 + 6);
    tmp_u10 = tmp_u10 >> 0x10;
  }
  tmp_pu18 = &local_101c;
  do {
    if (tmp_pu18 == (uint *)((int)tmp_pu20 + (-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)))) {
      tmp_b26 = false;
      goto joined_r0x0005fd7f;
    }
    tmp_u13 = *tmp_pu18;
    tmp_pu18 = (uint *)((int)tmp_pu18 + 1);
  } while ('\x1f' < (char)tmp_u13);
  G_LogPrintf("[DROPCLIENT] Client %d Name contains extended ASCII characters (%s)\n",param_1,
              &local_101c);
  Com_sprintf(tmp_pu3,0x400,"Bad name: Extended ASCII characters. Please change your name.");
  tmp_b26 = true;
joined_r0x0005fd7f:
  if (g_censorNames[0x10] != '\0') {
    SanitizeString(&local_101c,local_1e40,1);
    tmp_i12 = G_CensorText(local_1e40,censorNamesDictionary);
    if (tmp_i12 != 0) {
      G_LogPrintf("[NAME CENSOR] Client %i Censored Name: \"%s\"\n",param_1,&local_101c);
      Q_strncpyz(&local_101c,local_1e40,0x400);
      Info_SetValueForKey(tmp_pu2,"name",local_1e40);
      trap_SetUserinfo(param_1,tmp_pu2);
      if ((g_censorPenalty[0xc] & 2) != 0) {
        G_LogPrintf("[DROPCLIENT] Client %d Name censor (%s)\n",param_1,&local_101c);
        tmp_pc16 = "Name censor. Please change your name.";
        goto LAB_0006059e;
      }
    }
  }
  if (0 < (int)GHIDRA_FIELD(n_minNameLength, 12, 4)) {
    tmp_i12 = 0;
    if ((char)local_101c != '\0') {
      tmp_i12 = 0;
      tmp_pu20 = &local_101c;
      tmp_c9 = (char)local_101c;
      do {
        tmp_pu18 = (uint *)((int)tmp_pu20 + 1);
        if (tmp_c9 != ' ') {
          if (tmp_c9 == '^') {
            if (*(char *)((int)tmp_pu20 + 1) == '\0') break;
            tmp_pu18 = (uint *)((int)tmp_pu20 + 2);
          }
          else {
            tmp_i12 = tmp_i12 + 1;
          }
        }
        tmp_c9 = (char)*tmp_pu18;
        tmp_pu20 = tmp_pu18;
      } while (tmp_c9 != '\0');
    }
    if (tmp_i12 < (int)GHIDRA_FIELD(n_minNameLength, 12, 4)) {
      G_LogPrintf("[DROPCLIENT] Client %d Name too short (%s)\n",param_1,&local_101c);
      tmp_pc16 = "Your name is too short, it must contain at least %d visible characters.\n";
      __s_00 = (char *)GHIDRA_FIELD(n_minNameLength, 12, 4);
      tmp_b7 = tmp_b8;
LAB_0005fe01:
      Com_sprintf(tmp_pu3,0x400,tmp_pc16,__s_00);
      tmp_b8 = tmp_b7;
      goto LAB_0005fe1a;
    }
  }
  tmp_pc16 = (char *)0x24;
  Q_strncpyz(&local_1e64,&local_101c,0x24);
  if (tmp_b26) goto code_r0x00060110;
  goto _L1854;
code_r0x00060110:
  tmp_b5 = true;
LAB_00060120:
  if (*(int *)(g_entities + param_1 * 0x600 + 0x194) != 0) {
    tmp_i12 = (tmp_i11 >> 9) * -0x55555555;
    G_LogPrintf("Forcing disconnect on active client: %i\n",tmp_i12,tmp_pc16);
    ClientDisconnect(tmp_i12);
  }
  tmp_i12 = G_shrubbot_ban_check(&local_1ea7,&local_1e85,tmp_pu3,&local_1e97);
  if (tmp_i12 != 0) {
    G_LogPrintf("[DROPCLIENT] Client %i is banned from this server\n",param_1);
    tmp_u15 = va("You are banned from this server\n^7%s\n",tmp_pu3);
    return tmp_u15;
  }
  if ((tmp_b5) ||
     (tmp_i12 = IsFakepConnection(param_1,&local_c1c,local_818 + 0xff,tmp_pu3), tmp_i12 != 0)) {
    tmp_u15 = va(&g_unk_0024e6e9,tmp_pu3);
    return tmp_u15;
  }
  tmp_i12 = G_shrubbot_mute_check(&local_1e85,&local_1e97);
  tmp_u10 = (uint)(tmp_i12 != 0);
LAB_000601c3:
  local_1ed4 = (byte *)&local_c1c;
  __s = (void *)(param_1 * 0x54dc + level);
  tmp_pi1 = (int *)(g_entities + param_1 * 0x600 + 400);
  *tmp_pi1 = (int)__s;
  memset(__s,0,0x54dc);
  *(uint32_t *)((int)__s + 0xb3c) = 0;
  *(uint32_t *)((int)__s + 0xb44) = 0;
  *(uint *)((int)__s + 0xbf0) = tmp_u10;
  *(uint32_t *)((int)__s + 0xb40) = 0;
  *(uint32_t *)((int)__s + 0xb38) = 0;
  *(uint32_t *)((int)__s + 0xb30) = 0;
  *(uint32_t *)((int)__s + 0xb34) = 0;
  *(uint32_t *)((int)__s + 0xb2c) = 0;
  *(uint32_t *)(*tmp_pi1 + 0xf44) = 0;
  *(uint32_t *)(*tmp_pi1 + 0xb28) = 0;
  *(uint32_t *)((int)__s + 0x5ac) = 1;
  *(uint32_t *)((int)__s + 0x678) = g_unk_00abe908;
  if (tmp_b8) {
    *(uint32_t *)((int)__s + 0x5e8) = 1;
    g_unk_02a99a70 = 1;
    *(uint32_t *)((int)__s + 0xc80) = 1;
  }
  nitrox_CacheClientIP(g_entities + tmp_i11,local_1ed4);
  if ((g_entities[param_1 * 0x600 + 0x128] & 8) != 0) {
    Q_strncpyz((int)__s + 0x61c,&local_1e85,0x21);
  }
  if ((char)local_1e97 == '\0') {
    Q_strncpyz((int)__s + 0xaf4,"00-00-00-00-00-00",0x12);
  }
  else {
    Q_strncpyz((int)__s + 0xaf4,&local_1e97,0x12);
  }
  tmp_u15 = Info_ValueForKey(tmp_pu2,"etVersion");
  Q_strncpyz(&local_1d1c,tmp_u15,0x100);
  tmp_pc16 = strstr((char *)&local_1d1c,"ET Legacy");
  *(uint *)((int)__s + 0x54d4) = (uint)(tmp_pc16 != (char *)0x0);
  *(uint32_t *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 0x537c) = 0xfffffc19;
  if (param_2 == 0) {
    G_ReadSessionData(__s);
  }
  else {
    *(uint32_t *)((int)__s + 0x974) = 0;
    G_InitSessionData(__s,tmp_pu2);
    *(uint32_t *)((int)__s + 0x674) = g_unk_00abe908;
    *(uint32_t *)((int)__s + 0x110) = 0;
  }
  if (gidb == 0) {
    tmp_i12 = 0xff;
    *(uint32_t *)((int)__s + 0xf14) = 0xff;
  }
  else {
    tmp_u27 = true;
    if (param_3 == 0) {
LAB_000603e7:
      tmp_u24 = 0;
    }
    else {
      tmp_u24 = 0;
      tmp_u27 = (g_countryflags[0xc] & 2) == 0;
      if ((bool)tmp_u27) goto LAB_000603e7;
      local_1ed4 = (byte *)&local_1e1c;
      trap_Cvar_VariableStringBuffer("net_ip",local_1ed4,0x100);
    }
    tmp_i12 = 10;
    tmp_pb22 = local_1ed4;
    tmp_pb23 = (byte *)"localhost";
    do {
      if (tmp_i12 == 0) break;
      tmp_i12 = tmp_i12 + -1;
      tmp_u24 = *tmp_pb22 < *tmp_pb23;
      tmp_u27 = *tmp_pb22 == *tmp_pb23;
      tmp_pb22 = tmp_pb22 + (uint)tmp_b28 * -2 + 1;
      tmp_pb23 = tmp_pb23 + (uint)tmp_b28 * -2 + 1;
    } while ((bool)tmp_u27);
    if ((!(bool)tmp_u24 && !(bool)tmp_u27) == (bool)tmp_u24) {
      *(uint32_t *)((int)__s + 0xf14) = 0;
      tmp_i12 = 0;
    }
    else {
      tmp_u10 = GeoIP_addr_to_num(local_1ed4);
      if (((((tmp_u10 & 0xff000000) == 0xa000000) || ((tmp_u10 & 0xfff00000) == 0xac100000)) ||
          ((tmp_u10 & 0xffff0000) == 0xc0a80000)) || (tmp_u10 == 0x7f000001)) {
        *(uint32_t *)((int)__s + 0xf14) = 0;
        tmp_i12 = 0;
      }
      else {
        tmp_i12 = GeoIP_seek_record(gidb,tmp_u10);
        if (tmp_i12 == 0) {
          *(uint32_t *)((int)__s + 0xf14) = 0xf6;
          G_LogPrintf("GeoIP: This IP:%s cannot be located\n",local_1ed4);
          tmp_i12 = *(int *)((int)__s + 0xf14);
        }
        else {
          *(int *)((int)__s + 0xf14) = tmp_i12;
        }
      }
    }
  }
  (&g_unk_02b99268)[(tmp_i11 >> 9) * -0x15555550] = tmp_i12;
  G_deleteStats(param_1);
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 4) {
    if ((*(int *)(g_campaigns + g_unk_02a98490 * 0x494 + 0x284) == 0) || (g_unk_02a98494 != 0)) {
      *(uint32_t *)((int)__s + 0x674) = g_unk_00abe908;
    }
  }
  else {
    *(uint32_t *)((int)__s + 0x674) = g_unk_00abe908;
  }
  if (param_3 == 0) {
    if (param_2 == 0) {
      tmp_i11 = G_LuaHook_ClientConnect(param_1,0,0,tmp_pu3);
      if ((tmp_i11 == 0) || ((g_entities[param_1 * 0x600 + 0x128] & 8) != 0)) {
        G_LogPrintf("ClientConnect: %i\n",param_1);
        G_UpdateCharacter(__s);
        Bot_Event_ClientConnected(param_1,0);
        ClientUserinfoChanged(param_1);
        goto LAB_00060833;
      }
      goto LAB_000604fb;
    }
    *(uint32_t *)((int)__s + 0xbc4) = 0;
    *(uint32_t *)((int)__s + 3000) = 3;
    *(uint32_t *)((int)__s + 0xbc0) = 1;
    trap_UnlinkEntity(g_entities + tmp_i11);
    tmp_i11 = G_LuaHook_ClientConnect(param_1,param_2,0,tmp_pu3);
    if (tmp_i11 == 0) {
      G_LogPrintf("ClientConnect: %i\n",param_1);
      G_UpdateCharacter(__s);
      Bot_Event_ClientConnected(param_1,0);
      ClientUserinfoChanged(param_1);
      goto LAB_00060bdf;
    }
    if ((g_entities[param_1 * 0x600 + 0x128] & 8) == 0) goto LAB_000604fb;
    G_LogPrintf("ClientConnect: %i\n",param_1);
    G_UpdateCharacter(__s);
    Bot_Event_ClientConnected(param_1,0);
    ClientUserinfoChanged(param_1);
    tmp_u15 = va("cpm \"%s^7 connected",(int)__s + 0x5f8);
    trap_SendServerCommand(0xffffffff,tmp_u15);
  }
  else {
    tmp_i11 = param_1 * 0x600;
    *(int *)(g_entities + tmp_i11) = param_1;
    *(uint *)(g_entities + tmp_i11 + 0x128) = *(uint *)(g_entities + tmp_i11 + 0x128) | 8;
    *(uint32_t *)(g_entities + tmp_i11 + 0x194) = 1;
    tmp_i12 = G_LuaHook_ClientConnect(param_1,param_2,param_3,tmp_pu3);
    if (((tmp_i12 != 0) && (tmp_b25)) && ((g_entities[tmp_i11 + 0x128] & 8) == 0)) {
LAB_000604fb:
      tmp_u15 = va("You are excluded from this server. %s\n",tmp_pu3);
      return tmp_u15;
    }
    G_LogPrintf("ClientConnect: %i\n",param_1);
    G_UpdateCharacter(__s);
    Bot_Event_ClientConnected(param_1,param_3);
    ClientUserinfoChanged(param_1);
    if (param_2 == 0) goto LAB_00060833;
LAB_00060bdf:
    tmp_u15 = va("cpm \"%s^7 connected",(int)__s + 0x5f8);
    trap_SendServerCommand(0xffffffff,tmp_u15);
    if (!tmp_b25) goto LAB_00060833;
  }
  *(uint32_t *)(*(int *)(g_entities + param_1 * 0x600 + 400) + 0xf10) = 1;
LAB_00060833:
  CalculateRanks(1);
  G_TeamCountPlayers();
  *(uint32_t *)((int)__s + 0x6a0) = 0;
  *(uint8_t *)((int)__s + 0xf48) = 0;
  return 0;
}

void ClientStoreSurfaceFlags(int param_1,uint32_t param_2)
{
  *(uint32_t *)(g_entities + param_1 * 0x600 + 0x4bc) = param_2;
  return;
}

int ClientNumbersFromString(char *param_1,long *param_2)
{
  long tmp_l1;
  __int32_t **pp_Var2;
  char *tmp_pc3;
  char tmp_c4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  char *tmp_pc8;
  int tmp_i9;
  int local_834;
  char *local_820;
  char local_81c [1024];
  char local_41c [1036];
  
  local_820 = (char *)0x0;
  *param_2 = -1;
  tmp_l1 = strtol(param_1,&local_820,10);
  if ((((local_820 == (char *)0x0) || (*local_820 == '\0')) && (-1 < tmp_l1)) &&
     ((tmp_l1 < g_unk_00abe900 && (*(int *)(tmp_l1 * 0x54dc + level + 0x5ac) - 1U < 2)))) {
    *param_2 = tmp_l1;
    local_834 = 1;
    param_2[1] = -1;
  }
  else {
    tmp_c4 = *param_1;
    tmp_pc8 = local_81c;
LAB_00062a20:
    if (tmp_c4 != '\0') {
      while ((tmp_c4 != '^' && (tmp_c4 != '\x1b'))) {
        if ('\x1f' < tmp_c4) {
          param_1 = param_1 + 1;
          pp_Var2 = __ctype_tolower_loc();
          tmp_i6 = (int)tmp_c4;
          tmp_c4 = *param_1;
          *tmp_pc8 = (char)(*pp_Var2)[tmp_i6];
          tmp_pc8 = tmp_pc8 + 1;
          goto LAB_00062a20;
        }
        tmp_c4 = param_1[1];
        param_1 = param_1 + 1;
        if (tmp_c4 == '\0') goto LAB_00062a50;
      }
      if (param_1[1] == '\0') goto LAB_00062a50;
      tmp_c4 = param_1[2];
      param_1 = param_1 + 2;
      goto LAB_00062a20;
    }
LAB_00062a50:
    *tmp_pc8 = '\0';
    local_834 = 0;
    if (local_81c[0] != '\0') {
      if (g_unk_00abe900 < 1) {
        local_834 = 0;
      }
      else {
        tmp_i9 = 0;
        tmp_i7 = 0;
        local_834 = 0;
        tmp_i6 = g_unk_00abe900;
        do {
          while (tmp_i5 = level + tmp_i9, 1 < *(int *)(tmp_i5 + 0x5ac) - 1U) {
LAB_00062a90:
            tmp_i7 = tmp_i7 + 1;
            tmp_i9 = tmp_i9 + 0x54dc;
            if (tmp_i6 <= tmp_i7) goto LAB_00062b60;
          }
          tmp_pc8 = (char *)(tmp_i5 + 0x5f8);
          tmp_c4 = *(char *)(tmp_i5 + 0x5f8);
          tmp_pc3 = local_41c;
LAB_00062ad0:
          if (tmp_c4 != '\0') {
            while ((tmp_c4 != '^' && (tmp_c4 != '\x1b'))) {
              if ('\x1f' < tmp_c4) {
                tmp_pc8 = tmp_pc8 + 1;
                pp_Var2 = __ctype_tolower_loc();
                tmp_i6 = (int)tmp_c4;
                tmp_c4 = *tmp_pc8;
                *tmp_pc3 = (char)(*pp_Var2)[tmp_i6];
                tmp_pc3 = tmp_pc3 + 1;
                goto LAB_00062ad0;
              }
              tmp_c4 = tmp_pc8[1];
              tmp_pc8 = tmp_pc8 + 1;
              if (tmp_c4 == '\0') goto LAB_00062b00;
            }
            if (tmp_pc8[1] == '\0') goto LAB_00062b00;
            tmp_c4 = tmp_pc8[2];
            tmp_pc8 = tmp_pc8 + 2;
            goto LAB_00062ad0;
          }
LAB_00062b00:
          *tmp_pc3 = '\0';
          tmp_pc8 = strstr(local_41c,local_81c);
          tmp_i6 = g_unk_00abe900;
          if (tmp_pc8 == (char *)0x0) goto LAB_00062a90;
          tmp_i9 = tmp_i9 + 0x54dc;
          local_834 = local_834 + 1;
          *param_2 = tmp_i7;
          tmp_i7 = tmp_i7 + 1;
          param_2 = param_2 + 1;
          tmp_i6 = g_unk_00abe900;
        } while (tmp_i7 < g_unk_00abe900);
      }
LAB_00062b60:
      *param_2 = -1;
    }
  }
  return local_834;
}

char * ClientNumberFromString(int param_1,char *param_2)
{
  bool tmp_b1;
  char *tmp_pc2;
  size_t tmp_s3;
  __int32_t **pp_Var4;
  uint32_t tmp_u5;
  int tmp_i6;
  char *tmp_pc7;
  char tmp_c8;
  char *tmp_pc9;
  char *tmp_pc10;
  char *tmp_pc11;
  char local_81c [1024];
  char local_41c [1036];
  
  tmp_s3 = strlen(param_2);
  for (tmp_i6 = 0; (tmp_i6 < (int)tmp_s3 && (param_2[tmp_i6] != '\0')); tmp_i6 = tmp_i6 + 1) {
    if (9 < (byte)(param_2[tmp_i6] - 0x30U)) {
      tmp_b1 = false;
      goto LAB_000638f2;
    }
  }
  tmp_b1 = true;
LAB_000638f2:
  tmp_c8 = *param_2;
  tmp_pc9 = param_2;
  tmp_pc11 = local_81c;
  while (tmp_pc2 = g_unk_00abe900, tmp_c8 != '\0') {
    if ((tmp_c8 == '^') || (tmp_c8 == '\x1b')) {
      if (tmp_pc9[1] == '\0') break;
      tmp_c8 = tmp_pc9[2];
      tmp_pc9 = tmp_pc9 + 2;
    }
    else if (tmp_c8 < ' ') {
      tmp_c8 = tmp_pc9[1];
      tmp_pc9 = tmp_pc9 + 1;
    }
    else {
      tmp_pc9 = tmp_pc9 + 1;
      pp_Var4 = __ctype_tolower_loc();
      tmp_i6 = (int)tmp_c8;
      tmp_c8 = *tmp_pc9;
      *tmp_pc11 = (char)(*pp_Var4)[tmp_i6];
      tmp_pc11 = tmp_pc11 + 1;
    }
  }
  *tmp_pc11 = '\0';
  tmp_pc9 = (char *)0x0;
  tmp_pc11 = (char *)(level + 0x5f8);
  if (0 < (int)g_unk_00abe900) {
    do {
      if (*(int *)(tmp_pc11 + -0x4c) == 2) {
        tmp_c8 = *tmp_pc11;
        tmp_pc7 = local_41c;
        tmp_pc10 = tmp_pc11;
LAB_000639a0:
        if (tmp_c8 != '\0') {
          while ((tmp_c8 != '^' && (tmp_c8 != '\x1b'))) {
            if ('\x1f' < tmp_c8) {
              tmp_pc10 = tmp_pc10 + 1;
              pp_Var4 = __ctype_tolower_loc();
              tmp_i6 = (int)tmp_c8;
              tmp_c8 = *tmp_pc10;
              *tmp_pc7 = (char)(*pp_Var4)[tmp_i6];
              tmp_pc7 = tmp_pc7 + 1;
              goto LAB_000639a0;
            }
            tmp_c8 = tmp_pc10[1];
            tmp_pc10 = tmp_pc10 + 1;
            if (tmp_c8 == '\0') goto LAB_000639c0;
          }
          if (tmp_pc10[1] == '\0') goto LAB_000639c0;
          tmp_c8 = tmp_pc10[2];
          tmp_pc10 = tmp_pc10 + 2;
          goto LAB_000639a0;
        }
LAB_000639c0:
        *tmp_pc7 = '\0';
        tmp_i6 = strcmp(local_41c,local_81c);
        if (tmp_i6 == 0) {
          return tmp_pc9;
        }
      }
      tmp_pc9 = tmp_pc9 + 1;
      tmp_pc11 = tmp_pc11 + 0x54dc;
    } while (tmp_pc9 != tmp_pc2);
  }
  if (tmp_b1) {
    param_2 = (char *)strtol(param_2,(char **)0x0,10);
    if (((int)param_2 < 0) || ((int)g_unk_00abe900 <= (int)param_2)) {
      tmp_pc9 = "print \"Bad client slot: [lof]%i\n\"";
    }
    else {
      if (*(int *)((int)param_2 * 0x54dc + level + 0x5ac) == 2) {
        return param_2;
      }
      tmp_pc9 = "print \"Client[lof] %i [lon]is not active\n\"";
    }
  }
  else {
    tmp_pc9 = "print \"User [lof]%s [lon]is not on the server\n\"";
  }
  tmp_u5 = va(tmp_pc9,param_2);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
  return &g_unk_ffffffff;
}

uint32_t ClientIsFlooding(int param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  bool tmp_b4;
  
  tmp_i3 = g_unk_00abe908;
  tmp_i2 = *(int *)(param_1 + 400);
  if ((tmp_i2 == 0) || (GHIDRA_FIELD(g_floodprotect, 12, 4) == 0)) {
    return 0;
  }
  tmp_b4 = param_2 == 0;
  if ((tmp_b4) && (30000 < g_unk_00abe908 - *(int *)(tmp_i2 + 0x53b0))) {
    *(int *)(tmp_i2 + 0x53b0) = g_unk_00abe908;
    tmp_i2 = *(int *)(param_1 + 400);
  }
  if (*(int *)(tmp_i2 + 0x53a8) <= tmp_i3) {
    tmp_i3 = nitrox_CheckPermission(param_1,1);
    tmp_i2 = g_unk_00abe908;
    if (((tmp_i3 != 0) ||
        (tmp_i3 = *(int *)(param_1 + 400), 30000 < g_unk_00abe908 - *(int *)(tmp_i3 + 0x53b0))) ||
       (*(int *)(tmp_i3 + 0x53ac) <= (int)GHIDRA_FIELD(g_floodthreshold, 12, 4))) {
      if (!tmp_b4) {
        return 0;
      }
      tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0x53ac);
      *tmp_pi1 = *tmp_pi1 + 1;
      *(int *)(*(int *)(param_1 + 400) + 0x53a8) = GHIDRA_FIELD(g_floodWait, 12, 4) + tmp_i2;
      return 0;
    }
    if (tmp_b4) {
      *(int *)(tmp_i3 + 0x53a8) = g_unk_00abe908 + 500;
    }
  }
  return 1;
}

void ClientCommand(int param_1)
{
  uint *tmp_pu1;
  int *tmp_pi2;
  float tmp_f3;
  char tmp_c4;
  float tmp_f5;
  float tmp_f6;
  int tmp_i7;
  uint8_t *tmp_pu8;
  int tmp_i9;
  int tmp_i10;
  uint tmp_u11;
  uint32_t tmp_u12;
  long tmp_l13;
  char *tmp_pc14;
  uint tmp_u15;
  int tmp_i16;
  char *tmp_pc17;
  uint8_t tmp_u18;
  bool tmp_b19;
  bool tmp_b20;
  byte tmp_b21;
  double tmp_d22;
  char local_620 [2];
  char acStack_61e [2];
  uint32_t local_61c;
  uint32_t local_618 [63];
  char local_51c [256];
  char local_41c;
  char local_41b;
  char local_41a;
  char local_419;
  
  tmp_b21 = 0;
  tmp_i7 = param_1 * 0x600;
  tmp_pu8 = g_entities + tmp_i7;
  tmp_i9 = *(int *)(g_entities + tmp_i7 + 400);
  if (tmp_i9 == 0) {
    return;
  }
  tmp_i9 = G_shrubbot_mute_check(tmp_i9 + 0x61c,tmp_i9 + 0xaf4);
  tmp_b20 = true;
  tmp_u18 = false;
  if (tmp_i9 == 0) {
    tmp_u18 = *(int *)(*(int *)(g_entities + tmp_i7 + 400) + 0xbf0) == 0;
    tmp_b20 = !(bool)tmp_u18;
  }
  trap_Argv(0,&local_41c);
  tmp_i9 = 0xb;
  tmp_pc14 = &local_41c;
  tmp_pc17 = "lua_status";
  do {
    if (tmp_i9 == 0) break;
    tmp_i9 = tmp_i9 + -1;
    tmp_u18 = *tmp_pc14 == *tmp_pc17;
    tmp_pc14 = tmp_pc14 + (uint)tmp_b21 * -2 + 1;
    tmp_pc17 = tmp_pc17 + (uint)tmp_b21 * -2 + 1;
  } while ((bool)tmp_u18);
  if ((bool)tmp_u18) {
    G_LuaStatus(tmp_pu8);
    return;
  }
  tmp_i10 = G_LuaHook_ClientCommand(param_1,&local_41c);
  tmp_i9 = g_unk_00abe908;
  if (tmp_i10 != 0) {
    return;
  }
  if ((((local_41c == 's') && (local_41b == 'a')) && (local_41a == 'y')) && (local_419 == '\0')) {
    tmp_i10 = *(int *)(g_entities + tmp_i7 + 400);
    if ((tmp_i10 == 0) || (GHIDRA_FIELD(g_floodprotect, 12, 4) == 0)) goto LAB_0007151e;
    if (30000 < g_unk_00abe908 - *(int *)(tmp_i10 + 0x53b0)) {
      *(int *)(tmp_i10 + 0x53b0) = g_unk_00abe908;
      tmp_i10 = *(int *)(g_entities + tmp_i7 + 400);
    }
    if (tmp_i9 < *(int *)(tmp_i10 + 0x53a8)) {
LAB_00071505:
      tmp_i9 = nitrox_CheckPermission(tmp_pu8,1);
      if (tmp_i9 == 0) {
        return;
      }
    }
    else {
      tmp_i10 = nitrox_CheckPermission(tmp_pu8,1);
      tmp_i9 = g_unk_00abe908;
      if (tmp_i10 == 0) {
        tmp_i10 = *(int *)(g_entities + tmp_i7 + 400);
        tmp_i16 = *(int *)(tmp_i10 + 0x53ac);
        if ((g_unk_00abe908 - *(int *)(tmp_i10 + 0x53b0) < 0x7531) &&
           ((int)GHIDRA_FIELD(g_floodthreshold, 12, 4) < tmp_i16)) {
          *(int *)(tmp_i10 + 0x53a8) = g_unk_00abe908 + 500;
          goto LAB_00071505;
        }
      }
      else {
        tmp_i10 = *(int *)(g_entities + tmp_i7 + 400);
        tmp_i16 = *(int *)(tmp_i10 + 0x53ac);
      }
      *(int *)(tmp_i10 + 0x53ac) = tmp_i16 + 1;
      *(int *)(*(int *)(g_entities + tmp_i7 + 400) + 0x53a8) = tmp_i9 + GHIDRA_FIELD(g_floodWait, 12, 4);
    }
LAB_0007151e:
    if (tmp_b20) {
      return;
    }
    Cmd_Say_f(tmp_pu8,0,0);
    return;
  }
  tmp_i10 = Q_stricmp(&local_41c,&g_unk_00245e1e);
  tmp_c4 = local_41c;
  tmp_i9 = g_unk_00abe908;
  tmp_i16 = tmp_i7 >> 9;
  if (tmp_i10 == 0) {
    local_61c = 0;
    tmp_u15 = 0;
    do {
      tmp_u11 = tmp_u15;
      *(uint32_t *)((int)local_618 + tmp_u11) = 0;
      *(uint32_t *)((int)local_618 + tmp_u11 + 4) = 0;
      tmp_u15 = tmp_u11 + 8;
    } while (tmp_u11 + 8 < 0xf8);
    *(uint32_t *)((int)local_618 + tmp_u11 + 8) = 0;
    if (g_unk_02b99228 == 0) {
      return;
    }
    trap_Argv(1,local_51c);
    tmp_u15 = strtol(local_51c,(char **)0x0,10);
    if (0x3f < tmp_u15) {
      return;
    }
    if (((g_entities[tmp_u15 * 0x600 + 0x128] & 8) == 0) &&
       (tmp_i9 = *(int *)(g_entities + tmp_u15 * 0x600 + 400), tmp_i9 != 0)) {
      if (*(int *)(tmp_i9 + 0xb8c) == 0) {
        Com_sprintf(&local_61c,0x100,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                    *(uint32_t *)(tmp_i9 + 0xb88),(&g_unk_00abe8ac)[(tmp_u15 + 0x836a6) * 0x10],
                    (&g_unk_02b99230)[tmp_u15 * 0x10],(&g_unk_02b99234)[tmp_u15 * 0x10],
                    (&g_unk_02b99238)[tmp_u15 * 0x10],(&g_unk_02b9923c)[tmp_u15 * 0x10],
                    (&g_unk_02b99240)[tmp_u15 * 0x10],(&g_unk_02b99244)[tmp_u15 * 0x10],
                    (&g_unk_02b99248)[tmp_u15 * 0x10],(&g_unk_02b9924c)[tmp_u15 * 0x10],
                    (&g_unk_02b99250)[tmp_u15 * 0x10],(&g_unk_02b99254)[tmp_u15 * 0x10],
                    (&g_unk_02b99258)[tmp_u15 * 0x10],(&g_unk_02b9925c)[tmp_u15 * 0x10],
                    (&g_unk_02b99260)[tmp_u15 * 0x10],(&g_unk_02b99264)[tmp_u15 * 0x10]);
        tmp_u12 = va("glstats %s\n",&local_61c);
        trap_SendServerCommand(tmp_i16 * -0x55555555,tmp_u12);
        return;
      }
      Com_sprintf(&local_61c,0x100,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                  *(uint32_t *)(tmp_i9 + 0xb88),
                  (&g_unk_00abe8ac)[(tmp_u15 + 0x836a6) * 0x10] + *(int *)(tmp_i9 + 0xb48),
                  (&g_unk_02b99230)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb4c),
                  (&g_unk_02b99234)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb50),
                  (&g_unk_02b99238)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb54),
                  (&g_unk_02b9923c)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb58),
                  (&g_unk_02b99240)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb5c),
                  (&g_unk_02b99244)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb60),
                  (&g_unk_02b99248)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb64),
                  (&g_unk_02b9924c)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb68),
                  (&g_unk_02b99250)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb6c),
                  (&g_unk_02b99254)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb70),
                  (&g_unk_02b99258)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb74),
                  (&g_unk_02b9925c)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb78),
                  (&g_unk_02b99260)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb7c),
                  (&g_unk_02b99264)[tmp_u15 * 0x10] + *(int *)(tmp_i9 + 0xb80));
      tmp_u12 = va("glstats %s\n",&local_61c);
      trap_SendServerCommand(tmp_i16 * -0x55555555,tmp_u12);
      return;
    }
    trap_SendServerCommand(tmp_i16 * -0x55555555,"glstats 0 NR\n");
    return;
  }
  if (local_41c == 'm') {
    if (local_41b == '\0') {
LAB_000715a9:
      tmp_i10 = *(int *)(g_entities + tmp_i7 + 400);
      if ((tmp_i10 == 0) || (GHIDRA_FIELD(g_floodprotect, 12, 4) == 0)) goto LAB_0007160c;
      if (30000 < g_unk_00abe908 - *(int *)(tmp_i10 + 0x53b0)) {
        *(int *)(tmp_i10 + 0x53b0) = g_unk_00abe908;
        tmp_i10 = *(int *)(g_entities + tmp_i7 + 400);
      }
      if (tmp_i9 < *(int *)(tmp_i10 + 0x53a8)) {
LAB_000715f3:
        tmp_i9 = nitrox_CheckPermission(tmp_pu8,1);
        if (tmp_i9 == 0) {
          tmp_u12 = va("^1Flood Protection ^3: ^7Rejecting private message!\n");
          G_shrubbot_print(tmp_pu8,tmp_u12);
          return;
        }
      }
      else {
        tmp_i10 = nitrox_CheckPermission(tmp_pu8,1);
        tmp_i9 = g_unk_00abe908;
        if (tmp_i10 == 0) {
          tmp_i10 = *(int *)(g_entities + tmp_i7 + 400);
          if ((g_unk_00abe908 - *(int *)(tmp_i10 + 0x53b0) < 0x7531) &&
             ((int)GHIDRA_FIELD(g_floodthreshold, 12, 4) < *(int *)(tmp_i10 + 0x53ac))) {
            *(int *)(tmp_i10 + 0x53a8) = g_unk_00abe908 + 500;
            goto LAB_000715f3;
          }
        }
        else {
          tmp_i10 = *(int *)(g_entities + tmp_i7 + 400);
        }
        *(int *)(tmp_i10 + 0x53ac) = *(int *)(tmp_i10 + 0x53ac) + 1;
        *(int *)(*(int *)(g_entities + tmp_i7 + 400) + 0x53a8) = tmp_i9 + GHIDRA_FIELD(g_floodWait, 12, 4);
      }
LAB_0007160c:
      G_PrivateMessage(tmp_pu8);
      return;
    }
    if ((local_41b == 'a') && (local_41a == '\0')) {
      Nit_AdminChat(tmp_pu8);
      return;
    }
  }
  else if (((local_41c == 'p') && (local_41b == 'm')) && (local_41a == '\0')) goto LAB_000715a9;
  tmp_b19 = false;
  tmp_i10 = 7;
  tmp_pc14 = &local_41c;
  tmp_pc17 = "damage";
  do {
    if (tmp_i10 == 0) break;
    tmp_i10 = tmp_i10 + -1;
    tmp_b19 = *tmp_pc14 == *tmp_pc17;
    tmp_pc14 = tmp_pc14 + (uint)tmp_b21 * -2 + 1;
    tmp_pc17 = tmp_pc17 + (uint)tmp_b21 * -2 + 1;
  } while (tmp_b19);
  if (tmp_b19) {
    tmp_i9 = *(int *)(g_entities + tmp_i7 + 400);
    if (tmp_i9 == 0) {
      return;
    }
    tmp_f3 = *(float *)(tmp_i9 + 0xca0);
    tmp_f5 = 0.0;
    if (tmp_f3 != 0.0) {
      tmp_f5 = (*(float *)(tmp_i9 + 0xc9c) / tmp_f3) * 100.0;
    }
    tmp_u12 = va("print \"Team Hits: %.2f Total Hits: %.2f Pct: %.2f Limit: %d\n\"",
                (double)*(float *)(tmp_i9 + 0xc9c),(double)tmp_f3,(double)tmp_f5,
                GHIDRA_FIELD(g_teamDamageRestriction, 12, 4));
    trap_SendServerCommand(tmp_i16 * -0x55555555,tmp_u12);
    return;
  }
  tmp_i10 = 9;
  tmp_b19 = false;
  tmp_pc14 = &local_41c;
  tmp_pc17 = "say_team";
  do {
    if (tmp_i10 == 0) break;
    tmp_i10 = tmp_i10 + -1;
    tmp_b19 = *tmp_pc14 == *tmp_pc17;
    tmp_pc14 = tmp_pc14 + (uint)tmp_b21 * -2 + 1;
    tmp_pc17 = tmp_pc17 + (uint)tmp_b21 * -2 + 1;
  } while (tmp_b19);
  if (tmp_b19) {
    tmp_i10 = *(int *)(g_entities + tmp_i7 + 400);
    if ((tmp_i10 == 0) || (GHIDRA_FIELD(g_floodprotect, 12, 4) == 0)) goto LAB_00071b29;
    if (30000 < g_unk_00abe908 - *(int *)(tmp_i10 + 0x53b0)) {
      *(int *)(tmp_i10 + 0x53b0) = g_unk_00abe908;
      tmp_i10 = *(int *)(g_entities + tmp_i7 + 400);
    }
    if (tmp_i9 < *(int *)(tmp_i10 + 0x53a8)) {
LAB_00071b11:
      tmp_i9 = nitrox_CheckPermission(tmp_pu8,1);
      if (tmp_i9 == 0) {
        return;
      }
    }
    else {
      tmp_i9 = nitrox_CheckPermission(tmp_pu8,1);
      if (tmp_i9 == 0) {
        tmp_i9 = *(int *)(g_entities + tmp_i7 + 400);
        if ((g_unk_00abe908 - *(int *)(tmp_i9 + 0x53b0) < 0x7531) &&
           ((int)GHIDRA_FIELD(g_floodthreshold, 12, 4) < *(int *)(tmp_i9 + 0x53ac))) {
          *(int *)(tmp_i9 + 0x53a8) = g_unk_00abe908 + 500;
          goto LAB_00071b11;
        }
      }
      else {
        tmp_i9 = *(int *)(g_entities + tmp_i7 + 400);
      }
      *(int *)(tmp_i9 + 0x53ac) = *(int *)(tmp_i9 + 0x53ac) + 1;
      *(int *)(*(int *)(g_entities + tmp_i7 + 400) + 0x53a8) = GHIDRA_FIELD(g_floodWait, 12, 4) + g_unk_00abe908;
    }
LAB_00071b29:
    if (tmp_b20) {
      return;
    }
    Cmd_Say_f(tmp_pu8,1,0);
    return;
  }
  tmp_i9 = 5;
  tmp_b19 = false;
  tmp_pc14 = &local_41c;
  tmp_pc17 = "vsay";
  do {
    if (tmp_i9 == 0) break;
    tmp_i9 = tmp_i9 + -1;
    tmp_b19 = *tmp_pc14 == *tmp_pc17;
    tmp_pc14 = tmp_pc14 + (uint)tmp_b21 * -2 + 1;
    tmp_pc17 = tmp_pc17 + (uint)tmp_b21 * -2 + 1;
  } while (tmp_b19);
  if (tmp_b19) {
    tmp_i9 = ClientIsFlooding(tmp_pu8,0);
    if ((tmp_i9 != 0) && (tmp_i9 = nitrox_CheckPermission(tmp_pu8,1), tmp_i9 == 0)) {
      return;
    }
    if (tmp_b20) {
      return;
    }
    tmp_i9 = trap_Argc();
    if (tmp_i9 < 2) {
      return;
    }
    trap_Argv(1,local_51c,0x20);
    tmp_u12 = ConcatArgs(2);
    G_Voice(tmp_pu8,0,0,local_51c,tmp_u12,0);
    return;
  }
  tmp_i9 = 10;
  tmp_b19 = false;
  tmp_pc14 = &local_41c;
  tmp_pc17 = "vsay_team";
  do {
    if (tmp_i9 == 0) break;
    tmp_i9 = tmp_i9 + -1;
    tmp_b19 = *tmp_pc14 == *tmp_pc17;
    tmp_pc14 = tmp_pc14 + (uint)tmp_b21 * -2 + 1;
    tmp_pc17 = tmp_pc17 + (uint)tmp_b21 * -2 + 1;
  } while (tmp_b19);
  if (tmp_b19) {
    tmp_i9 = ClientIsFlooding(tmp_pu8,0);
    if ((tmp_i9 != 0) && (tmp_i9 = nitrox_CheckPermission(tmp_pu8,1), tmp_i9 == 0)) {
      return;
    }
    if (tmp_b20) {
      return;
    }
    tmp_i9 = trap_Argc();
    if (tmp_i9 < 2) {
      return;
    }
    trap_Argv(1,local_51c,0x20);
    tmp_u12 = ConcatArgs(2);
    G_Voice(tmp_pu8,0,1,local_51c,tmp_u12,0);
    return;
  }
  tmp_i9 = 10;
  tmp_b19 = false;
  tmp_pc14 = &local_41c;
  tmp_pc17 = "say_buddy";
  do {
    if (tmp_i9 == 0) break;
    tmp_i9 = tmp_i9 + -1;
    tmp_b19 = *tmp_pc14 == *tmp_pc17;
    tmp_pc14 = tmp_pc14 + (uint)tmp_b21 * -2 + 1;
    tmp_pc17 = tmp_pc17 + (uint)tmp_b21 * -2 + 1;
  } while (tmp_b19);
  if (tmp_b19) {
    tmp_i9 = ClientIsFlooding(tmp_pu8,0);
    if ((tmp_i9 != 0) && (tmp_i9 = nitrox_CheckPermission(tmp_pu8,1), tmp_i9 == 0)) {
      return;
    }
    if (tmp_b20) {
      return;
    }
    Cmd_Say_f(tmp_pu8,2,0);
    return;
  }
  tmp_i9 = 0xb;
  tmp_b19 = false;
  tmp_pc14 = &local_41c;
  tmp_pc17 = "vsay_buddy";
  do {
    if (tmp_i9 == 0) break;
    tmp_i9 = tmp_i9 + -1;
    tmp_b19 = *tmp_pc14 == *tmp_pc17;
    tmp_pc14 = tmp_pc14 + (uint)tmp_b21 * -2 + 1;
    tmp_pc17 = tmp_pc17 + (uint)tmp_b21 * -2 + 1;
  } while (tmp_b19);
  if (tmp_b19) {
    tmp_i9 = ClientIsFlooding(tmp_pu8,0);
    if ((tmp_i9 != 0) && (tmp_i9 = nitrox_CheckPermission(tmp_pu8,1), tmp_i9 == 0)) {
      return;
    }
    if (tmp_b20) {
      return;
    }
    trap_Argv(2,&local_61c);
    tmp_l13 = strtol((char *)&local_61c,(char **)0x0,10);
    tmp_i9 = 0;
    if (-1 < tmp_l13) {
      tmp_i9 = tmp_l13;
    }
    tmp_i7 = trap_Argc();
    if (tmp_i7 <= tmp_i9 + 2) {
      return;
    }
    trap_Argv(tmp_i9 + 3,local_51c,0x20);
    tmp_u12 = ConcatArgs(tmp_i9 + 4);
    G_Voice(tmp_pu8,0,2,local_51c,tmp_u12,0);
    return;
  }
  tmp_i9 = 6;
  tmp_b20 = false;
  tmp_pc14 = &local_41c;
  tmp_pc17 = "score";
  do {
    if (tmp_i9 == 0) break;
    tmp_i9 = tmp_i9 + -1;
    tmp_b20 = *tmp_pc14 == *tmp_pc17;
    tmp_pc14 = tmp_pc14 + (uint)tmp_b21 * -2 + 1;
    tmp_pc17 = tmp_pc17 + (uint)tmp_b21 * -2 + 1;
  } while (tmp_b20);
  if (tmp_b20) {
    *(uint32_t *)(*(int *)(g_entities + tmp_i7 + 400) + 0x5374) = 1;
    return;
  }
  tmp_i9 = strcmp(&local_41c,"vote");
  if (tmp_i9 == 0) {
    Cmd_Vote_f(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"fireteam");
  if (tmp_i9 == 0) {
    Cmd_FireTeam_MP_f(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"showstats");
  if (tmp_i9 == 0) {
    G_PrintAccuracyLog(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"rconAuth");
  if (tmp_i9 == 0) {
    Cmd_AuthRcon_f(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"ignore");
  if (tmp_i9 == 0) {
    Cmd_Ignore_f(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"unignore");
  if (tmp_i9 == 0) {
    Cmd_UnIgnore_f(tmp_pu8);
    return;
  }
  if ((((tmp_c4 == 'o') && (local_41b == 'b')) && (local_41a == 'j')) && (local_419 == '\0')) {
    Cmd_SelectedObjective_f(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"impkd");
  if (tmp_i9 == 0) {
    if (*(int *)(g_entities + tmp_i7 + 400) == 0) {
      return;
    }
    Cmd_IntermissionPlayerKillsDeaths_f_part_18();
    return;
  }
  tmp_i9 = strcmp(&local_41c,"imwa");
  if (tmp_i9 == 0) {
    if (*(int *)(g_entities + tmp_i7 + 400) == 0) {
      return;
    }
    Cmd_IntermissionWeaponAccuracies_f_part_19();
    return;
  }
  tmp_i9 = strcmp(&local_41c,"imws");
  if (tmp_i9 == 0) {
    Cmd_IntermissionWeaponStats_f(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"imhr");
  if (tmp_i9 == 0) {
    Cmd_IntermissionHitRegions_f(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"imready");
  if (tmp_i9 == 0) {
    if (*(int *)(g_entities + tmp_i7 + 400) == 0) {
      return;
    }
    tmp_pu1 = (uint *)(*(int *)(g_entities + tmp_i7 + 400) + 0x68);
    *tmp_pu1 = *tmp_pu1 | 8;
    *(uint *)(g_entities + tmp_i7 + 8) = *(uint *)(g_entities + tmp_i7 + 8) | 8;
    *(uint32_t *)(*(int *)(g_entities + tmp_i7 + 400) + 0x998) = 1;
    return;
  }
  tmp_i9 = strcmp(&local_41c,"mapvote");
  if (tmp_i9 == 0) {
    G_IntermissionMapVote(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"immaplist");
  if (tmp_i9 == 0) {
    G_IntermissionMapList(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"imvotetally");
  if (tmp_i9 == 0) {
    G_IntermissionVoteTally(tmp_pu8);
    return;
  }
  if (((tmp_c4 == 'w') && (local_41b == 's')) && (local_41a == '\0')) {
    Cmd_WeaponStat_f(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"forcetapout");
  if (tmp_i9 == 0) {
    if (*(int *)(g_entities + tmp_i7 + 400) == 0) {
      return;
    }
    if (0 < *(int *)(g_entities + tmp_i7 + 0x2c8)) {
      return;
    }
    if (1 < *(int *)(*(int *)(g_entities + tmp_i7 + 400) + 3000) - 1U) {
      return;
    }
    limbo(tmp_pu8,1);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"wstats");
  if (tmp_i9 == 0) {
    G_statsPrint(tmp_pu8,1);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"sgstats");
  if (tmp_i9 == 0) {
    G_statsPrint(tmp_pu8,2);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"stshots");
  if (tmp_i9 == 0) {
    G_weaponStatsLeaders_cmd(tmp_pu8,1,1);
    return;
  }
  if (((tmp_c4 == 'r') && (local_41b == 's')) && (local_41a == '\0')) {
    Cmd_ResetSetup_f(tmp_pu8);
    return;
  }
  tmp_i9 = G_commandCheck(tmp_pu8,&local_41c);
  tmp_c4 = local_41c;
  if (tmp_i9 != 0) {
    return;
  }
  if (local_41c == 'f') {
    if ((local_41b == 'u') && (local_41a == '\0')) {
      G_SendScore(tmp_pu8);
      nitmod_TeamScores();
      G_SendKD(tmp_pu8);
      TeamplayInfoMessage(1);
      TeamplayInfoMessage(2);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"imhere");
    if (tmp_i9 == 0) {
LAB_000727a3:
      trap_SendServerCommand(tmp_i16 * -0x55555555,"handshake");
      return;
    }
  }
  else {
    tmp_i9 = strcmp(&local_41c,"imhere");
    if (tmp_i9 == 0) goto LAB_000727a3;
    if ((((tmp_c4 == 'r') && (local_41b == 'h')) && (local_41a == 's')) && (local_419 == '\0')) {
      if ((&g_unk_00abe8a8)[(int)(&g_unk_00836a20 + tmp_i16 * -0x55555555)] == 0) {
        return;
      }
      (&g_unk_00abe8a8)[(int)(&g_unk_00836a20 + tmp_i16 * -0x55555555)] = 0;
      return;
    }
  }
  tmp_i9 = strcmp(&local_41c,"handshake");
  if (tmp_i9 == 0) {
    if ((&g_unk_00abe8a8)[(int)(&g_unk_00836a20 + tmp_i16 * -0x55555555)] != 0) {
      return;
    }
    (&g_unk_00abe8a8)[(int)(&g_unk_00836a20 + tmp_i16 * -0x55555555)] = 1;
    nitrox_SendNewGameState(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"getdata");
  if (tmp_i9 == 0) {
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 7) {
      tmp_u12 = va(&g_unk_00245ee6,GHIDRA_FIELD(g_TDMScore, 12, 4));
      trap_SendServerCommand(0xffffffff,tmp_u12);
    }
    nitmod_SimpleCS(tmp_pu8);
    nitmod_SendNCS(tmp_pu8);
    nitrox_SendSkillLevels(tmp_pu8);
    nitmod_SendChargeTimes(tmp_pu8);
    nitmod_TeamScores();
    if (GHIDRA_FIELD(n_NxAC_CvarScan, 12, 4) == 0) {
      return;
    }
    *(int *)(*(int *)(g_entities + tmp_i7 + 400) + 0xb24) = GHIDRA_FIELD(n_NxAC_CvarScanWait, 12, 4) + g_unk_00abe908
    ;
    return;
  }
  tmp_i9 = strcmp(&local_41c,"register");
  if (tmp_i9 == 0) {
    nitrox_user_register(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"login");
  if (tmp_i9 == 0) {
    nitrox_user_login(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"mailto");
  if (tmp_i9 == 0) {
    nitrox_MailTo(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"mails");
  if (tmp_i9 == 0) {
    nitrox_CheckMails(tmp_pu8);
    return;
  }
  tmp_i9 = strcmp(&local_41c,"deletemail");
  if (tmp_i9 == 0) {
    trap_Argv(1,local_51c);
    if (local_51c[0] == '\0') {
      trap_SendServerCommand(param_1,"print \"^1Deletemail: ^9You must specify a mail ID\n\"");
      return;
    }
    tmp_l13 = strtol(local_51c,(char **)0x0,10);
    nitrox_DeleteMail(tmp_pu8,tmp_l13);
    return;
  }
  if (tmp_c4 != 'c') {
LAB_000727f3:
    tmp_i9 = nitrox_CheckPermission(tmp_pu8,2);
    if ((tmp_i9 != 0) && (tmp_i9 = G_shrubbot_cmd_check(tmp_pu8), tmp_i9 != 0)) {
      return;
    }
    if (g_unk_00abf994 != 0) {
      tmp_u12 = va("print \"^3%s^7 not allowed during intermission.\n\"",&local_41c);
      trap_SendServerCommand(param_1,tmp_u12);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"give");
    if (tmp_i9 == 0) {
      Cmd_Give_f(tmp_pu8);
      return;
    }
    if (((local_41c == 'g') && (local_41b == 'o')) && ((local_41a == 'd' && (local_419 == '\0')))) {
      Cmd_God_f(tmp_pu8);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"nofatigue");
    if (tmp_i9 == 0) {
      Cmd_Nofatigue_f(tmp_pu8);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"notarget");
    if (tmp_i9 == 0) {
      Cmd_Notarget_f(tmp_pu8);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"noclip");
    if (tmp_i9 == 0) {
      Cmd_Noclip_f(tmp_pu8);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"kill");
    if (tmp_i9 == 0) {
      Cmd_Kill_f(tmp_pu8);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"follownext");
    if (tmp_i9 == 0) {
      Cmd_FollowCycle_f(tmp_pu8,1);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"followprev");
    if (tmp_i9 == 0) {
      Cmd_FollowCycle_f(tmp_pu8,0xffffffff);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"where");
    if (tmp_i9 == 0) {
      Cmd_Where_f(tmp_pu8);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"setviewpos");
    if (tmp_i9 == 0) {
      Cmd_SetViewpos_f(tmp_pu8);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"setspawnpt");
    if (tmp_i9 == 0) {
      Cmd_SetSpawnPoint_f(tmp_pu8);
      return;
    }
    tmp_i9 = G_commandCheck(tmp_pu8,&local_41c);
    if (tmp_i9 != 0) {
      return;
    }
    tmp_i9 = strcmp(&local_41c,"playdead");
    if (tmp_i9 == 0) {
      G_PlayDead(tmp_pu8);
      return;
    }
    tmp_i9 = strcmp(&local_41c,"dropobj");
    if (tmp_i9 != 0) {
      tmp_i9 = strcmp(&local_41c,"dropweapon");
      if ((tmp_i9 == 0) && (GHIDRA_FIELD(n_allowDropWeapon, 12, 4) != 0)) {
        tmp_u12 = G_GetPrimaryWeaponForClient(*(uint32_t *)(g_entities + tmp_i7 + 400));
        G_DropWeapon(tmp_pu8,tmp_u12);
        return;
      }
      tmp_u12 = va("print \"unknown cmd[lof] %s\n\"",&local_41c);
      trap_SendServerCommand(param_1,tmp_u12);
      return;
    }
    Cmd_DropObj(tmp_pu8);
    return;
  }
  if (local_41b == 's') {
    if ((local_41a == 'm') && (local_419 == '\0')) {
      if (GHIDRA_FIELD(n_NxAC_CheckClientBinary, 12, 4) == 0) {
        return;
      }
      trap_Argv(1,local_51c,0x100);
      decode64(local_51c);
      tmp_i9 = NxAC_VerifyChecksum(local_51c);
      if (tmp_i9 != 0) {
        return;
      }
      NxAC_Log(g_entities + param_1 * 0x600,1,1,"UNKNOWN_CLIENT_BINARY SHA1]^5 %s",local_51c);
      trap_DropClient(param_1,"^9Nx^7AC ^5VIOLATION: ^5[UNKNOWN_CLIENT_BINARY]",0);
      return;
    }
    goto LAB_000727f3;
  }
  if ((((local_41b != 'v') || (local_41a != 's')) || (local_419 != '\0')) ||
     (GHIDRA_FIELD(n_NxAC_CvarScan, 12, 4) == 0)) goto LAB_000727f3;
  tmp_pu8 = g_entities + param_1 * 0x600;
  trap_Argv(1,local_620);
  trap_Argv(2,local_51c);
  trap_Argv(3,&local_61c);
  if ((char)local_61c != '\0') {
    tmp_u15 = 0xffffffff;
    tmp_pc14 = (char *)&local_61c;
    do {
      if (tmp_u15 == 0) break;
      tmp_u15 = tmp_u15 - 1;
      tmp_c4 = *tmp_pc14;
      tmp_pc14 = tmp_pc14 + (uint)tmp_b21 * -2 + 1;
    } while (tmp_c4 != '\0');
    if (acStack_61e[~tmp_u15] == ' ') {
      acStack_61e[~tmp_u15] = '\0';
    }
  }
  tmp_l13 = strtol(local_620,(char **)0x0,10);
  tmp_d22 = strtod((char *)&local_61c,(char **)0x0);
  tmp_f3 = (float)tmp_d22;
  tmp_d22 = strtod((char *)((&CvarChecks)[tmp_l13] + 0x44),(char **)0x0);
  tmp_f5 = (float)tmp_d22;
  tmp_d22 = strtod((char *)((&CvarChecks)[tmp_l13] + 100),(char **)0x0);
  tmp_f6 = (float)tmp_d22;
  tmp_i9 = Q_stricmp((&CvarChecks)[tmp_l13],local_51c);
  if (tmp_i9 != 0) {
    NxAC_Log(tmp_pu8,1,1,"UNEXPECTED CVAR SCAN DATA]");
    trap_DropClient(param_1,"^9Nx^7AC ^5VIOLATION: ^5[UNEXPECTED CVAR SCAN DATA]\n",0);
    return;
  }
  tmp_pi2 = (int *)(g_entities + param_1 * 0x600 + 400);
  *(int *)(*tmp_pi2 + 0xb10) = *(int *)(*tmp_pi2 + 0xb10) + 1;
  *(int *)(*tmp_pi2 + 0xb14) = *(int *)(*tmp_pi2 + 0xb14) + 1;
  if ((int)GHIDRA_FIELD(n_NxAC_CvarScanMaxWarnings, 12, 4) < 1) {
    tmp_b20 = true;
  }
  else {
    tmp_b20 = (int)GHIDRA_FIELD(n_NxAC_CvarScanMaxWarnings, 12, 4) <= *(int *)(*tmp_pi2 + 0xb28);
  }
  tmp_i9 = (&CvarChecks)[tmp_l13];
  switch(*(uint32_t *)(tmp_i9 + 0x40)) {
  case 0:
    if ((char)local_61c != '\0') {
      NxAC_CvarScanViolation(tmp_pu8,1,tmp_l13,&local_61c);
    }
    goto switchD_00072d48_default;
  case 1:
    tmp_i9 = Q_stricmp(tmp_i9 + 0x44,&local_61c);
    if (tmp_i9 == 0) goto switchD_00072d48_default;
    break;
  case 2:
    if (tmp_f3 <= tmp_f6) goto LAB_00072e64;
    break;
  case 3:
    if (((tmp_f6 < tmp_f3) || (tmp_f3 <= tmp_f5)) && (tmp_f6 <= tmp_f3 || tmp_f3 < tmp_f5))
    goto switchD_00072d48_default;
    break;
  case 4:
    if (tmp_f5 < tmp_f3) goto switchD_00072d48_default;
    break;
  case 5:
LAB_00072e64:
    if (tmp_f5 <= tmp_f3) goto switchD_00072d48_default;
    break;
  case 6:
    if (tmp_f3 < tmp_f5) goto switchD_00072d48_default;
    break;
  case 7:
    if (tmp_f3 <= tmp_f5) goto switchD_00072d48_default;
    break;
  case 8:
    tmp_pc14 = strstr((char *)&local_61c,(char *)(tmp_i9 + 0x44));
    if (tmp_pc14 != (char *)0x0) goto switchD_00072d48_default;
    break;
  case 9:
    tmp_pc14 = strstr((char *)&local_61c,(char *)(tmp_i9 + 0x44));
    if (tmp_pc14 != (char *)0x0) {
      NxAC_CvarScanViolation(tmp_pu8,tmp_b20,tmp_l13,&local_61c);
    }
  default:
    goto switchD_00072d48_default;
  }
  NxAC_CvarScanViolation(tmp_pu8,tmp_b20,tmp_l13,&local_61c);
switchD_00072d48_default:
  tmp_i9 = *(int *)(g_entities + param_1 * 0x600 + 400);
  if ((*(int *)(tmp_i9 + 0xb10) == 1) && (*(int *)(tmp_i9 + 0xb14) < *(int *)(tmp_i9 + 0xb18))) {
    *(int *)(*(int *)(g_entities + tmp_i7 + 400) + 0xb20) =
         GHIDRA_FIELD(n_NxAC_CvarScanDelay, 12, 4) + g_unk_00abe908;
  }
  else if (*(int *)(tmp_i9 + 0xb14) == *(int *)(tmp_i9 + 0xb18)) {
    *(int *)(*(int *)(g_entities + tmp_i7 + 400) + 0xb24) =
         GHIDRA_FIELD(n_NxAC_CvarScanInterval, 12, 4) + g_unk_00abe908;
  }
  return;
}

void player_die(uint *param_1,int param_2,uint *param_3,uint32_t param_4,uint param_5)
{
  uint *tmp_pu1;
  int *tmp_pi2;
  float *pfVar3;
  uint32_t tmp_u4;
  byte tmp_b5;
  bool tmp_b6;
  int tmp_i7;
  int tmp_i8;
  char *tmp_pc9;
  uint32_t tmp_u10;
  uint tmp_u11;
  uint tmp_u12;
  int tmp_i13;
  uint16_t *tmp_pu14;
  uint32_t *tmp_pu15;
  char *tmp_pc16;
  int tmp_i17;
  uint8_t *tmp_pu18;
  bool tmp_b19;
  int local_854;
  int local_850;
  int local_84c;
  uint local_848;
  float local_828;
  float local_824;
  float local_820;
  uint32_t local_81c;
  float local_818 [514];
  
  tmp_i7 = OnSameTeam(param_1,param_3);
  local_81c = 0;
  tmp_u11 = 0;
  do {
    tmp_u12 = tmp_u11;
    *(uint32_t *)((int)local_818 + tmp_u12) = 0;
    *(uint32_t *)((int)local_818 + tmp_u12 + 4) = 0;
    tmp_u11 = tmp_u12 + 8;
  } while (tmp_u12 + 8 < 0x3f8);
  *(uint32_t *)((int)local_818 + tmp_u12 + 8) = 0;
  if ((param_3 != (uint *)0x0) && (param_3[100] != 0)) {
    *(uint *)(param_1[100] + 0x9d8) = param_3[0x2b];
    tmp_pu18 = g_entities;
    *(uint *)(param_3[100] + 0x9d0) = param_1[0x2b];
    tmp_i17 = 0;
    local_850 = 1;
    do {
      tmp_u11 = param_1[100];
      tmp_i8 = *(int *)(tmp_u11 + 0xc + (tmp_i17 + 0x14ec) * 4);
      if ((((0 < tmp_i8) && (((int)(param_3 + -0x24f928) >> 9) * -0x55555555 != tmp_i17)) &&
          (((int)(param_1 + -0x24f928) >> 9) * -0x55555555 != tmp_i17)) &&
         (*(int *)(*(int *)(tmp_pu18 + 400) + 3000) != 3)) {
        tmp_i13 = 2;
        if (tmp_i8 < 0x32) {
          tmp_i13 = local_850;
        }
        if (param_3 == param_1 || param_5 == 0x3c) {
          if ((n_killAssistances[0xc] & 2) != 0) {
            tmp_pc9 = "an 2 %i";
            tmp_i8 = tmp_i13;
LAB_0007693e:
            tmp_u10 = va(tmp_pc9,tmp_i8);
            trap_SendServerCommand(tmp_i17,tmp_u10);
            G_LoseSkillPoints(tmp_pu18,0,(float)tmp_i13);
            tmp_u11 = param_1[100];
          }
        }
        else {
          tmp_i8 = OnSameTeam(tmp_pu18,param_1);
          if (tmp_i8 == 0) {
            if ((n_killAssistances[0xc] & 1) != 0) {
              tmp_u10 = va("an 1 %i",tmp_i13);
              trap_SendServerCommand(tmp_i17,tmp_u10);
              G_AddSkillPoints(tmp_pu18,0,(float)tmp_i13);
            }
          }
          else if ((n_killAssistances[0xc] & 4) != 0) {
            tmp_pc9 = "an 3 %i";
            tmp_i8 = -tmp_i13;
            goto LAB_0007693e;
          }
          tmp_u11 = param_1[100];
        }
        *(uint32_t *)(tmp_u11 + 0xc + (tmp_i17 + 0x14ec) * 4) = 0;
        local_850 = tmp_i13;
      }
      tmp_i17 = tmp_i17 + 1;
      tmp_pu18 = tmp_pu18 + 0x600;
    } while (tmp_i17 != 0x40);
    if (GHIDRA_FIELD(g_revenge, 12, 4) != 0) {
      if (param_3 != param_1) {
        *(uint *)(param_1[100] + 0x9e4) = param_3[0x2b];
      }
      if (*(int *)(param_3[100] + 0x9d0) == *(int *)(param_3[100] + 0x9e4)) {
        trap_SendServerCommand(param_3[0x2b],"an -2 1");
        G_AddSkillPoints(param_3,0,0x3f800000);
        *(uint32_t *)(param_3[100] + 0x9e4) = 0xffffffff;
      }
    }
  }
  if (param_5 == 0x3c) {
    tmp_u11 = *(uint *)(param_1[100] + 0xfa8);
LAB_000779db:
    local_84c = BG_WeaponForMOD(tmp_u11);
    tmp_u12 = param_1[100];
  }
  else {
    tmp_u11 = param_5;
    if ((param_5 != 0x1f) || (tmp_u12 = param_1[100], *(int *)(tmp_u12 + 0x5318) == 0))
    goto LAB_000779db;
    param_5 = 0x3e;
    param_3 = (uint *)(g_entities + *(int *)(tmp_u12 + 0x531c) * 0x600);
    local_84c = 0;
  }
  if (*(int *)(tmp_u12 + 0x5338) == 0) {
    *(int *)(tmp_u12 + 0x5338) = g_unk_00abe908;
  }
  G_ReAdjustSingleClientPosition(param_1);
  G_UpdateKillingSpree(param_1,param_3,1);
  if (param_3 == param_1) {
    if (param_3[100] != 0) {
      tmp_pi2 = (int *)(param_3[100] + 0x944);
      *tmp_pi2 = *tmp_pi2 + 1;
      *(int *)(param_3[100] + 0xc74) = *(int *)(param_3[100] + 0xc74) + 1;
      *(int *)(param_3[100] + 0x120) = *(int *)(param_3[100] + 0x120) + 1;
      nitrox_CheckGlobalAwards(param_3,1,1);
      tmp_u10 = va("%d %d %d",*(uint32_t *)(param_3[100] + 3000),
                  *(uint32_t *)(param_3[100] + 0xbc8),local_84c);
      trap_PbStat(((int)(param_3 + -0x24f928) >> 9) * -0x55555555,"suicide",tmp_u10);
    }
LAB_00076b5e:
    if (param_5 != 0x1f) goto LAB_00076b6c;
LAB_00077a7b:
    *(int *)(param_1[100] + 0xec8) = *(int *)(param_1[100] + 0xec8) + 1;
    *(int *)(param_1[100] + 0xc74) = *(int *)(param_1[100] + 0xc74) + 1;
    param_1[0xe1] = (uint)(tmp_i7 != 0);
    tmp_u11 = param_1[100];
  }
  else {
    if (tmp_i7 != 0) {
      G_LogTeamKill(param_3,local_84c);
      goto LAB_00076b5e;
    }
    G_LogDeath(param_1,local_84c);
    G_LogKill(param_3,local_84c);
    if ((GHIDRA_FIELD(g_gamestate, 12, 4) != 0) || (param_3[100] == 0)) goto LAB_00076b5e;
    tmp_pu1 = (uint *)(param_3[100] + 0x1054);
    *tmp_pu1 = *tmp_pu1 | 8;
    if (param_5 == 0x1f) goto LAB_00077a7b;
LAB_00076b6c:
    param_1[0xe1] = (uint)(tmp_i7 != 0);
    tmp_u11 = param_1[100];
    if ((tmp_u11 != 0) && ((param_5 == 0x44 || (param_5 == 0x28)))) {
      tmp_i8 = (param_2 + -0x93e4a0 >> 9) * -0x55555555;
      tmp_i17 = G_FindMapEntityData(mapEntityData,tmp_i8);
      if (tmp_i17 != 0) {
        G_FreeMapEntityData(mapEntityData,tmp_i17);
      }
      tmp_i17 = G_FindMapEntityData(0x2d8ca94,tmp_i8);
      if (tmp_i17 != 0) {
        G_FreeMapEntityData(0x2d8ca94,tmp_i17);
      }
      tmp_u11 = param_1[100];
    }
  }
  tmp_pu18 = mapEntityData;
  if (*(int *)(tmp_u11 + 3000) == 1) {
    tmp_pu18 = (uint8_t *)0x2d8ca94;
  }
  tmp_i17 = G_FindMapEntityDataSingleClient(tmp_pu18,0,*param_1,0xffffffff);
  while (tmp_i17 != 0) {
    while (*(char *)(tmp_i17 + 0x14) != '\x02') {
      tmp_i17 = G_FindMapEntityDataSingleClient(tmp_pu18,tmp_i17,*param_1,0xffffffff);
      if (tmp_i17 == 0) goto LAB_00076c36;
    }
    tmp_i8 = G_FindMapEntityDataSingleClient(tmp_pu18,tmp_i17,*param_1,0xffffffff);
    G_FreeMapEntityData(tmp_pu18,tmp_i17);
    tmp_i17 = tmp_i8;
  }
LAB_00076c36:
  tmp_u11 = param_1[0x111];
  if (tmp_u11 == 0) {
    tmp_u12 = param_1[100];
    tmp_i17 = *(int *)(tmp_u12 + 4);
  }
  else {
    G_LeaveTank(param_1,0,0);
    tmp_u12 = param_1[100];
    tmp_i17 = *(int *)(tmp_u12 + 4);
  }
  tmp_b6 = tmp_u11 != 0;
  if ((tmp_i17 == 3) && ((*(byte *)(tmp_u12 + 0x6a) & 0x80) == 0)) {
    return;
  }
  if (GHIDRA_FIELD(g_gamestate, 12, 4) == 3) {
    return;
  }
  if (param_5 == 0x3c) {
    G_addStats(param_1,param_3,param_4,*(uint32_t *)(tmp_u12 + 0xfa8));
    G_AddKillSkillPoints(param_3,param_1,*(uint32_t *)(param_1[100] + 0xfa8),0,0);
  }
  else {
    G_addStats(param_1,param_3,param_4,param_5);
    if (param_5 == 0x3e) {
      if (((param_3 != (uint *)0x0) && (tmp_i7 == 0)) && (param_3[100] != 0)) {
        G_AddKillSkillPoints(param_3,param_1,0x3e,0,0);
      }
      *(int *)(param_1[100] + 0xc74) = *(int *)(param_1[100] + 0xc74) + 1;
    }
  }
  *(uint32_t *)(param_1[100] + 4) = 3;
  G_AddEvent(param_1,0x39,0);
  if (param_3 == (uint *)0x0) {
LAB_00076d3c:
    tmp_pc9 = "<world>";
    local_848 = 0x3fe;
  }
  else {
    local_848 = *param_3;
    if (param_3[100] == 0) {
      tmp_pc9 = "<non-client>";
    }
    else {
      tmp_pc9 = (char *)(param_3[100] + 0x5f8);
    }
    if (0x3f < local_848) goto LAB_00076d3c;
  }
  if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
    if (((int)param_5 < 0) || (bg_numMods <= (int)param_5)) {
      tmp_pc16 = "<bad obituary>";
    }
    else {
      tmp_pc16 = *(char **)(modNames + param_5 * 4);
    }
    Bot_Event_Death(((int)(param_1 + -0x24f928) >> 9) * -0x55555555,
                    g_entities + ((int)(param_3 + -0x24f928) >> 9) * 0x200,tmp_pc16);
    Bot_Event_KilledSomeone
              (((int)(param_3 + -0x24f928) >> 9) * -0x55555555,
               g_entities + ((int)(param_1 + -0x24f928) >> 9) * 0x200,tmp_pc16);
    G_LogPrintf("Kill: %i %i %i: %s killed %s by %s\n",local_848,*param_1,param_5,tmp_pc9,
                param_1[100] + 0x5f8,tmp_pc16);
  }
  tmp_i17 = G_LuaHook_Obituary(*param_1,local_848,param_5,&local_81c);
  if (tmp_i17 == 0) {
    tmp_i17 = nitrox_TempEventFromQueue(0,0x38);
    *(uint *)(tmp_i17 + 0xbc) = param_5;
    tmp_u11 = *param_1;
    *(uint *)(tmp_i17 + 0x90) = local_848;
    *(uint32_t *)(tmp_i17 + 0x128) = 0x20;
    *(uint *)(tmp_i17 + 0x8c) = tmp_u11;
    *(int *)(tmp_i17 + 0xe8) = local_84c;
  }
  else {
    if (0x3f < *param_1) {
      G_Error("G_LuaHook_Obituary: target out of range");
    }
    tmp_u10 = va("cpm \"%s\n\"",&local_81c);
    trap_SendServerCommand(0xffffffff,tmp_u10);
  }
  param_1[0xbb] = (uint)param_3;
  *(uint32_t *)(param_1[100] + 0x16c) = 0;
  tmp_u11 = param_1[0x3a];
  if (((*(int *)(param_1[100] + 0x34) != 0) &&
      ((tmp_u11 != 1 && tmp_u11 != 0xf) && (tmp_u11 & 0xfffffffd) != 0x31)) && (1 < tmp_u11 - 0x19)) {
    tmp_u11 = rand();
    local_828 = (float)(tmp_u11 & 0x7fff) / 32767.0 - 0.5;
    local_828 = local_828 + local_828;
    tmp_u11 = rand();
    local_824 = (float)(tmp_u11 & 0x7fff) / 32767.0 - 0.5;
    local_824 = local_824 + local_824;
    tmp_u11 = rand();
    local_828 = local_828 * 160.0;
    local_824 = local_824 * 160.0;
    local_820 = ((float)(tmp_u11 & 0x7fff) / 32767.0) * 160.0;
    local_818[0xff] = (float)param_1[0x5a];
    local_818[0x100] = (float)param_1[0x5b];
    local_818[0x101] = (float)param_1[0x5c] + 40.0;
    tmp_i17 = fire_grenade(param_1,local_818 + 0xff,&local_828,param_1[0x3a]);
    *(uint32_t *)(tmp_i17 + 0x2d0) = 0;
    tmp_u11 = param_1[0x3a];
  }
  if (tmp_u11 == 0x25) {
    tmp_u11 = param_1[100];
    tmp_i17 = BG_FindClipForWeapon(0x25);
    if (*(int *)(tmp_u11 + (tmp_i17 + 0xa4) * 4) == 0) {
      param_1[0x3a] = 0x17;
      *(uint32_t *)(param_1[100] + 0xa4) = 0x17;
      *(uint32_t *)(param_1[100] + 0xa8) = 0;
    }
    tmp_u11 = param_1[0x3a];
  }
  if ((tmp_u11 == 0x24) &&
     (tmp_u11 = param_1[100], tmp_i17 = BG_FindClipForWeapon(0x24),
     *(int *)(tmp_u11 + (tmp_i17 + 0xa4) * 4) == 0)) {
    param_1[0x3a] = 0x16;
    *(uint32_t *)(param_1[100] + 0xa4) = 0x16;
    *(uint32_t *)(param_1[100] + 0xa8) = 0;
  }
  if ((param_3 == (uint *)0x0) || (tmp_u11 = param_3[100], tmp_u11 == 0)) {
    tmp_u11 = param_1[100];
    if (tmp_u11 != 0) {
      if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
        if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) {
          *(int *)(tmp_u11 + 0xc78) = *(int *)(tmp_u11 + 0xc78) + -1;
          CalculateRanks(0);
          if ((GHIDRA_FIELD(g_gametype, 12, 4) != 5) || (tmp_u11 = param_1[100], tmp_u11 == 0)) goto LAB_00077250;
        }
      }
      else if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) goto LAB_00077250;
      if ((g_unk_00abe8ac == 0) && (g_unk_02a98488 == 0)) {
        *(int *)(tmp_u11 + 0x110) = *(int *)(tmp_u11 + 0x110) + -1;
        tmp_u11 = param_1[100];
        tmp_pi2 = (int *)(tmp_u11 + 0xc78);
        *tmp_pi2 = *tmp_pi2 + -1;
        *(int *)(&g_unk_00abe91c + *(int *)(tmp_u11 + 300) * 4) =
             *(int *)(&g_unk_00abe91c + *(int *)(tmp_u11 + 300) * 4) + -1;
        CalculateRanks(0);
      }
    }
  }
  else {
    if ((tmp_i7 == 0) && (param_3 != param_1)) {
      if ((((g_misc[0xc] & 2) == 0) || (29999 < *(int *)(param_1[100] + 0xfb4))) ||
         (GHIDRA_FIELD(g_gamestate, 12, 4) != 0)) {
        if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) goto LAB_0007827b;
LAB_00077095:
        tmp_i17 = g_unk_00abe908;
        if ((g_announcer[0xc] & 4) != 0) {
          if ((int)GHIDRA_FIELD(g_multikillTime, 12, 4) < g_unk_00abe908 - *(int *)(tmp_u11 + 0xfc4)) {
            *(uint32_t *)(tmp_u11 + 0xfc8) = 1;
            tmp_u11 = param_3[100];
          }
          else {
            *(int *)(tmp_u11 + 0xfc8) = *(int *)(tmp_u11 + 0xfc8) + 1;
            tmp_u11 = param_3[100];
            tmp_u12 = *(int *)(tmp_u11 + 0xfc8) - 2;
            if (tmp_u12 < 5) {
              tmp_i8 = *(int *)(CSWTCH_57 + tmp_u12 * 4);
              if (tmp_i8 < 3) {
                if (tmp_i8 - 1U < 2) {
                  tmp_i17 = ((int)(param_3 + -0x24f928) >> 9) * -0x55555555;
                  tmp_u10 = va("z2 %i %i",tmp_i17,tmp_i8 - 1U);
                  trap_SendServerCommand(tmp_i17,tmp_u10);
                  tmp_u11 = param_3[100];
                  tmp_i17 = g_unk_00abe908;
                }
              }
              else {
                nitmod_Announce(((int)(param_3 + -0x24f928) >> 9) * -0x55555555,tmp_i8 + -1,3);
                tmp_u11 = param_3[100];
                tmp_i17 = g_unk_00abe908;
              }
            }
          }
        }
        *(int *)(tmp_u11 + 0xfc4) = tmp_i17;
        *(int *)(param_3[100] + 0x11c) = *(int *)(param_3[100] + 0x11c) + 1;
        *(int *)(param_3[100] + 0xc7c) = *(int *)(param_3[100] + 0xc7c) + 1;
        if ((param_1[0x4a] & 8) == 0) {
          nitrox_CheckGlobalAwards(param_3,0,1);
        }
        if ((param_3[0x4a] & 8) == 0) {
          nitrox_CheckGlobalAwards(param_1,1,1);
        }
        *(int *)(param_1[100] + 0xc74) = *(int *)(param_1[100] + 0xc74) + 1;
        *(int *)(param_1[100] + 0x120) = *(int *)(param_1[100] + 0x120) + 1;
      }
      else if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
LAB_0007827b:
        if (g_unk_02a98480 == -1) {
LAB_00078657:
          g_unk_02a98480 = *(int *)(tmp_u11 + 3000);
          tmp_u11 = param_3[100];
          goto LAB_000784e1;
        }
LAB_0007828e:
        if ((g_unk_00abe8ac == 0) && (g_unk_02a98488 == 0)) {
          *(int *)(tmp_u11 + 0x110) = *(int *)(tmp_u11 + 0x110) + 1;
          tmp_u11 = param_3[100];
          tmp_pi2 = (int *)(tmp_u11 + 0xc78);
          *tmp_pi2 = *tmp_pi2 + 1;
          *(int *)(&g_unk_00abe91c + *(int *)(tmp_u11 + 300) * 4) =
               *(int *)(&g_unk_00abe91c + *(int *)(tmp_u11 + 300) * 4) + 1;
          CalculateRanks(0);
          tmp_u11 = param_3[100];
        }
LAB_000782e3:
        if (tmp_u11 != 0) goto LAB_00077095;
      }
      else {
        *(int *)(tmp_u11 + 0xc78) = *(int *)(tmp_u11 + 0xc78) + 1;
        CalculateRanks(0);
        tmp_u11 = param_3[100];
        if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) goto LAB_000782e3;
        if (g_unk_02a98480 == -1) goto LAB_00078657;
LAB_000784e1:
        if (tmp_u11 != 0) goto LAB_0007828e;
      }
      G_UpdateKillingSpree(param_3,0,0);
    }
    else {
      if (param_3 == param_1) goto LAB_00077cb4;
      if (g_unk_00abe8ac < 1) {
        if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
          tmp_i17 = nitrox_CheckPermission(param_3,0);
          if (tmp_i17 == 0) {
            if (*(int *)(param_3[100] + 0x5e8) == 0) {
              if ((2 < param_5 - 0x2e) && (GHIDRA_FIELD(g_complaintlimit, 12, 4) != 0)) {
                tmp_b5 = g_disableComplaints[0xc];
                if (param_5 == 0x28) {
joined_r0x000788c2:
                  tmp_b5 = tmp_b5 & 1;
                  goto joined_r0x00078898;
                }
                if (((param_5 == 0x16) || (param_5 == 0x19)) &&
                   ((g_disableComplaints[0xc] & 2) != 0)) goto LAB_00077cb4;
                if (param_5 == 0x33) {
                  tmp_b5 = g_disableComplaints[0xc] & 4;
joined_r0x00078898:
                  if (tmp_b5 != 0) goto LAB_00077cb4;
                }
                else {
                  if (param_5 == 0x42) {
                    tmp_b5 = g_disableComplaints[0xc] & 8;
                    goto joined_r0x00078898;
                  }
                  if (param_5 == 0x15) {
                    tmp_b5 = *(byte *)(param_2 + 0x4fc);
                    goto joined_r0x000788c2;
                  }
                }
                tmp_u10 = va("complaint %i",*param_3);
                trap_SendServerCommand(((int)(param_1 + -0x24f928) >> 9) * -0x55555555,tmp_u10);
                *(uint *)(param_1[100] + 0x698) = param_3[0x2b];
                *(int *)(param_1[100] + 0x69c) = g_unk_00abe908 + 0x5014;
              }
            }
            else {
              if ((param_3[0x4a] & 8) == 0) {
                tmp_pc9 = "complaint -4";
              }
              else {
                tmp_pc9 = "complaint -5";
              }
              trap_SendServerCommand(((int)(param_1 + -0x24f928) >> 9) * -0x55555555,tmp_pc9);
            }
          }
LAB_00077cb4:
          if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) goto LAB_00077b9e;
          tmp_u11 = param_3[100];
          if (tmp_u11 == 0) goto LAB_000771c4;
        }
        else if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) goto LAB_00077b9e;
        if ((g_unk_00abe8ac == 0) && (g_unk_02a98488 == 0)) {
          *(int *)(tmp_u11 + 0x110) = *(int *)(tmp_u11 + 0x110) + -3;
          tmp_u11 = param_3[100];
          tmp_pi2 = (int *)(tmp_u11 + 0xc78);
          *tmp_pi2 = *tmp_pi2 + -3;
          *(int *)(&g_unk_00abe91c + *(int *)(tmp_u11 + 300) * 4) =
               *(int *)(&g_unk_00abe91c + *(int *)(tmp_u11 + 300) * 4) + -3;
          goto LAB_00077b9e;
        }
      }
      else if (GHIDRA_FIELD(g_gametype, 12, 4) != 5) {
LAB_00077b9e:
        CalculateRanks(0);
      }
    }
LAB_000771c4:
    if ((((0 < (int)GHIDRA_FIELD(g_drawAttackerHP, 12, 4)) && ((param_1[0x4a] & 8) == 0)) && (tmp_i7 == 0)) &&
       (0 < (int)param_3[0xb2])) {
      tmp_u10 = va("chat \"%s ^ghad ^3%i HP\" -2",param_3[100] + 0x5f8,param_3[0xb2]);
      trap_SendServerCommand(((int)(param_1 + -0x24f928) >> 9) * -0x55555555,tmp_u10);
    }
  }
LAB_00077250:
  Team_FragBonuses(param_1,param_2,param_3);
  G_DropItems(param_1);
  if ((((param_1[100] != 0) && (-0xaf < (int)param_1[0xb2])) &&
      ((param_5 != 0x20 && ((param_5 != 0x39 && ((int)param_1[0xc1] < 3)))))) &&
     (((param_3[100] == 0 || (*(int *)(BG_Weapons + local_84c * 0x6b0 + 0x5f8) == 0)) &&
      (G_AddEvent(param_1,0x5d,0), (int)param_1[0xc1] < 2)))) {
    Bot_AddFallenTeammateGoals(param_1,*(uint32_t *)(param_1[100] + 3000));
  }
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 7) {
    nitmod_TeamScores();
  }
  else if ((param_1[0x4a] & 8) == 0) {
    Cmd_Score_f(param_1);
  }
  local_854 = g_unk_00abe938;
  if (0 < g_unk_00abe938) {
    tmp_i17 = 0;
    do {
      while( true ) {
        tmp_pi2 = &g_unk_00abe944 + tmp_i17;
        tmp_i8 = *tmp_pi2 * 0x54dc + level;
        if (((*(int *)(tmp_i8 + 0x5ac) != 2) || (*(int *)(tmp_i8 + 3000) != 3)) ||
           (*(uint *)(tmp_i8 + 0xbc4) != *param_1)) break;
        tmp_i17 = tmp_i17 + 1;
        Cmd_Score_f(g_entities + *tmp_pi2 * 0x600);
        local_854 = g_unk_00abe938;
        if (g_unk_00abe938 <= tmp_i17) goto LAB_000773b0;
      }
      tmp_i17 = tmp_i17 + 1;
    } while (tmp_i17 < local_854);
  }
LAB_000773b0:
  param_1[0xb3] = 1;
  param_1[0x53] = 0x4000000;
  param_1[0x28] = 0;
  tmp_u12 = 0x40;
  param_1[0x39] = 0;
  *(uint *)(param_1[100] + 0xfec) = param_1[0x3a];
  *(uint32_t *)(param_1[100] + 0xb0) = 0;
  *(uint32_t *)(param_1[100] + 0xb8) = 0;
  tmp_u11 = param_1[100];
  param_1[0x52] = *(uint *)(tmp_u11 + 0x3f4);
  *(uint32_t *)(tmp_u11 + 0x3f0) = *(uint32_t *)(tmp_u11 + 0x3f4);
  trap_LinkEntity(param_1);
  *(int *)(param_1[100] + 0xfb0) = g_unk_02a99b84 + 800;
  tmp_u11 = param_1[100];
  tmp_u10 = *(uint32_t *)(tmp_u11 + 0x158);
  tmp_u4 = *(uint32_t *)(tmp_u11 + 0x180);
  tmp_pu14 = (uint16_t *)(tmp_u11 + 0x150);
  tmp_b19 = ((uint)tmp_pu14 & 1) != 0;
  if (tmp_b19) {
    *(uint8_t *)(tmp_u11 + 0x150) = 0;
    tmp_pu14 = (uint16_t *)(tmp_u11 + 0x151);
    tmp_u12 = 0x3f;
  }
  if (((uint)tmp_pu14 & 2) != 0) {
    *tmp_pu14 = 0;
    tmp_u12 = tmp_u12 - 2;
    tmp_pu14 = tmp_pu14 + 1;
  }
  tmp_u11 = 0;
  do {
    *(uint32_t *)((int)tmp_pu14 + tmp_u11) = 0;
    *(uint32_t *)((int)tmp_pu14 + tmp_u11 + 4) = 0;
    tmp_u11 = tmp_u11 + 8;
  } while (tmp_u11 < (tmp_u12 & 0xfffffff8));
  tmp_pu15 = (uint32_t *)((int)tmp_pu14 + tmp_u11);
  if ((tmp_u12 & 4) != 0) {
    *tmp_pu15 = 0;
    tmp_pu15 = tmp_pu15 + 1;
  }
  if ((tmp_u12 & 2) != 0) {
    *(uint16_t *)tmp_pu15 = 0;
    tmp_pu15 = (uint32_t *)((int)tmp_pu15 + 2);
  }
  if (tmp_b19) {
    *(uint8_t *)tmp_pu15 = 0;
  }
  *(uint32_t *)(param_1[100] + 0x158) = tmp_u10;
  *(uint32_t *)(param_1[100] + 0x180) = tmp_u4;
  if ((int)param_1[0xb2] < -0xae) {
    local_818[0x101] = 0.0;
    local_818[0x100] = 0.0;
    tmp_i17 = local_848 * 0x600;
    local_818[0xff] = 0.0;
    if (*(int *)(g_entities + tmp_i17 + 0x194) != 0) {
      if (*(int *)(g_entities + tmp_i17 + 400) == 0) {
        tmp_i8 = VectorCompare(tmp_i17 + 0x93e4c4,&vec3_origin);
        if (tmp_i8 == 0) {
          VectorNormalize2(tmp_i17 + 0x93e4c4,local_818 + 0xff);
        }
      }
      else {
        local_818[0xff] = (float)param_1[0x5a] - *(float *)(g_entities + tmp_i17 + 0x168);
        local_818[0x100] = (float)param_1[0x5b] - *(float *)(g_entities + tmp_i17 + 0x16c);
        local_818[0x101] = (float)param_1[0x5c] - *(float *)(g_entities + tmp_i17 + 0x170);
        VectorNormalize(local_818 + 0xff);
      }
    }
    tmp_u10 = DirToByte(local_818 + 0xff);
    G_AddEvent(param_1,0x3a,tmp_u10);
    param_1[1] = 10;
    tmp_b5 = g_announcer[0xc] & 8;
    param_1[0xb3] = 0;
    param_1[0x53] = 0;
    if (tmp_b5 != 0) goto LAB_000775be;
LAB_0007762d:
    tmp_u11 = param_1[100];
  }
  else {
    tmp_i17 = rand();
    tmp_i17 = tmp_i17 % 4 + 0x34;
    if (tmp_i17 < 0x34) {
      tmp_i17 = 0x34;
    }
    tmp_i17 = nitrox_TempEventFromQueue(param_1 + 0x5a,tmp_i17);
    *(uint *)(tmp_i17 + 0x90) = *param_1;
    *(uint32_t *)(tmp_i17 + 0x128) = 0x20;
    *(int *)(tmp_i17 + 0xe8) = local_84c;
    if ((int)param_1[0xb2] < -0xae) {
      param_1[0xb2] = 0xffffff52;
    }
    tmp_u11 = param_1[100];
    if ((*(byte *)(tmp_u11 + 0x6a) & 0x80) == 0) {
      tmp_u10 = BG_AnimScriptEvent(tmp_u11,*(uint32_t *)(*(int *)(tmp_u11 + 0x99c) + 0x7f0),1,0,1);
      *(uint32_t *)(tmp_u11 + 0x10) = tmp_u10;
      tmp_u11 = param_1[100];
    }
    *(uint32_t *)(tmp_u11 + 0x5298) = *(uint32_t *)(tmp_u11 + 0x60);
    tmp_i17 = g_unk_00abe908;
    *(uint32_t *)(param_1[100] + 0x529c) = *(uint32_t *)(param_1[100] + 0x58);
    *(int *)(param_1[100] + 0x5398) = *(int *)(param_1[100] + 0x10) + tmp_i17;
    param_1[0xaf] = (uint)body_die;
    if ((g_announcer[0xc] & 8) == 0) goto LAB_0007762d;
LAB_000775be:
    tmp_u11 = param_1[100];
    if (((((param_3 != (uint *)0x0) && (tmp_u11 != 0)) &&
         ((tmp_u12 = param_3[100], tmp_u12 != 0 && ((1 < *param_3 - 0x3fe && (param_3 != param_1))))))
        && (tmp_i7 == 0)) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
      if (g_unk_02b9a654 == 0) {
        nitmod_Sound_Global(0xe);
        tmp_u10 = va("pop \"^7%s ^ghad ^1FIRST BLOOD ^gfrom ^7%s^7!\"",param_3[100] + 0x5f8,
                    param_1[100] + 0x5f8);
        trap_SendServerCommand(0xffffffff,tmp_u10);
        trap_SendServerCommand(((int)(param_3 + -0x24f928) >> 9) * -0x55555555,"an 4 0");
        g_unk_02b9a654 = 1;
        tmp_u12 = param_3[100];
      }
      g_unk_02af58ac = tmp_u12 + 0x5f8;
      goto LAB_0007762d;
    }
  }
  if (param_5 == 1) {
    if (*(int *)(tmp_u11 + 3000) == 1) {
      g_unk_02aa29c0 = g_unk_00abe908;
    }
    else {
      if (*(int *)(tmp_u11 + 3000) != 2) goto LAB_00077641;
      g_unk_02aa29c4 = g_unk_00abe908;
    }
    *(uint *)(param_1[100] + 0x68) = *(uint *)(param_1[100] + 0x68) & 0xff7fffff;
    if (tmp_b6) goto LAB_00077d64;
    if (*(int *)(BG_Weapons + local_84c * 0x6b0 + 0x5f8) != 0) goto LAB_00077d35;
  }
  else {
LAB_00077641:
    *(uint *)(tmp_u11 + 0x68) = *(uint *)(tmp_u11 + 0x68) & 0xff7fffff;
    if (tmp_b6) {
LAB_00077d64:
      limbo(param_1,0);
      return;
    }
    if ((((param_5 == 0x3c) || (param_5 == 0x20)) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) ||
       ((*(int *)(BG_Weapons + local_84c * 0x6b0 + 0x5f8) != 0 ||
        ((param_5 == 0x1a && ((g_misc[0xc] & 0x40) != 0)))))) goto LAB_00077d35;
  }
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
    tmp_i7 = G_CountTeamMedics(*(uint32_t *)(param_1[100] + 3000),1);
    if (tmp_i7 != 0) {
      return;
    }
LAB_00077d35:
    limbo(param_1,1);
    return;
  }
  if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
    return;
  }
  if ((((g_DMOptions[0xc] & 0x10) == 0) || (param_5 - 0x39 < 2)) ||
     ((param_5 - 0x1f < 2 || ((param_5 & 0xffffffbf) == 0)))) {
    if (param_3 != (uint *)0x0) {
      tmp_u11 = param_3[100];
      goto LAB_00077738;
    }
  }
  else if (param_3[100] != 0) {
    G_createClusterNade(param_1,1,0);
    tmp_u11 = param_3[100];
LAB_00077738:
    if ((((tmp_u11 != 0) && (g_unk_00abe8ac == 0)) && (g_unk_02a98488 == 0)) &&
       (((g_TDMOptions[0xc] & 1) == 0 || (GHIDRA_FIELD(g_gametype, 12, 4) != 7)))) {
      if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
        *(int *)(tmp_u11 + 0x110) = *(int *)(tmp_u11 + 0x110) + 1;
        tmp_u11 = param_3[100];
        *(int *)(&g_unk_00abe91c + *(int *)(tmp_u11 + 300) * 4) =
             *(int *)(&g_unk_00abe91c + *(int *)(tmp_u11 + 300) * 4) + 1;
      }
      *(int *)(tmp_u11 + 0xc78) = *(int *)(tmp_u11 + 0xc78) + 1;
      CalculateRanks(0);
    }
  }
  if ((int)param_1[0xb2] < -0xae) {
    tmp_i7 = BG_WeaponForMOD(param_5);
    if ((*(int *)(BG_Weapons + tmp_i7 * 0x6b0 + 0x688) == 1) ||
       ((*(int *)(BG_Weapons + tmp_i7 * 0x6b0 + 0x688) != 2 &&
        (tmp_i7 = G_WeaponIsExplosive(param_5), tmp_i7 != 0)))) {
      local_818[0x101] = 0.0;
      local_818[0x100] = 0.0;
      tmp_i7 = local_848 * 0x600;
      local_818[0xff] = 0.0;
      if (*(int *)(g_entities + tmp_i7 + 0x194) != 0) {
        if (*(int *)(g_entities + tmp_i7 + 400) == 0) {
          tmp_i17 = VectorCompare(tmp_i7 + 0x93e4c4,&vec3_origin);
          if (tmp_i17 == 0) {
            VectorNormalize2(tmp_i7 + 0x93e4c4,local_818 + 0xff);
          }
        }
        else {
          local_818[0xff] = (float)param_1[0x5a] - *(float *)(g_entities + tmp_i7 + 0x168);
          local_818[0x100] = (float)param_1[0x5b] - *(float *)(g_entities + tmp_i7 + 0x16c);
          local_818[0x101] = (float)param_1[0x5c] - *(float *)(g_entities + tmp_i7 + 0x170);
          VectorNormalize(local_818 + 0xff);
        }
      }
      tmp_u10 = DirToByte(local_818 + 0xff);
      G_AddEvent(param_1,0x3a,tmp_u10);
      param_1[0xb3] = 0;
      param_1[1] = 10;
      param_1[0x53] = 0;
      goto LAB_000777f2;
    }
  }
  limbo(param_1,1);
LAB_000777f2:
  if ((param_3 != (uint *)0x0) && (tmp_u11 = param_3[100], tmp_u11 != 0)) {
    if ((g_DMOptions[0xc] & 1) != 0) {
      tmp_i7 = 0x14;
      tmp_u12 = *(uint *)(tmp_u11 + 0xe0);
      tmp_u11 = param_3[0xb2] + 0x14;
      if ((int)tmp_u12 <= (int)tmp_u11) {
        tmp_i7 = tmp_u12 - param_3[0xb2];
        tmp_u11 = tmp_u12;
      }
      param_3[0xb2] = tmp_u11;
      tmp_u10 = va("hpb %i",tmp_i7);
      trap_SendServerCommand(((int)(param_3 + -0x24f928) >> 9) * -0x55555555,tmp_u10);
      tmp_u11 = param_3[100];
      if (tmp_u11 == 0) {
        return;
      }
    }
    if (((0 < (int)GHIDRA_FIELD(g_DMFragLimit, 12, 4)) && ((int)GHIDRA_FIELD(g_DMFragLimit, 12, 4) <= *(int *)(tmp_u11 + 0xc7c)))
       && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
      g_unk_02af58ac = tmp_u11 + 0x5f8;
      pfVar3 = local_818 + 0xff;
      trap_GetConfigstring(0xe,pfVar3,0x400);
      Info_SetValueForKey(pfVar3,"w",&g_unk_0024bfa6);
      trap_SetConfigstring(0xe,pfVar3);
      tmp_u10 = va("^1Death Match^7: %s ^gwins this round",param_3[100] + 0x5f8);
      LogExit(tmp_u10);
      tmp_u10 = va("DM %i",*(uint32_t *)(param_3[100] + 0xa0));
      trap_SendServerCommand(0xffffffff,tmp_u10);
      tmp_u10 = va("print \"^1Death Match^7: %s ^gwins this round.\n\"",param_3[100] + 0x5f8);
      trap_SendServerCommand(0xffffffff,tmp_u10);
    }
  }
  return;
}

uint ClientHasAdren(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  
  tmp_u2 = 0;
  if ((*(byte *)(param_1 + 0xed8) & 0x10) != 0) {
    tmp_i1 = *(int *)(param_1 + 0xbc8);
    if (tmp_i1 == 0) {
      return GHIDRA_FIELD(g_adrenClasses, 12, 4) & 1;
    }
    if (tmp_i1 == 1) {
      return (uint)GHIDRA_FIELD(g_adrenClasses, 12, 4) >> 1 & 1;
    }
    if (tmp_i1 == 2) {
      return (uint)GHIDRA_FIELD(g_adrenClasses, 12, 4) >> 2 & 1;
    }
    if (tmp_i1 == 3) {
      return (uint)GHIDRA_FIELD(g_adrenClasses, 12, 4) >> 3 & 1;
    }
    if (tmp_i1 == 4) {
      tmp_u2 = (uint)GHIDRA_FIELD(g_adrenClasses, 12, 4) >> 4 & 1;
    }
  }
  return tmp_u2;
}

char * ClientName_part_9(int param_1,char *param_2,int param_3)
{
  char *__src;
  uint8_t local_41c [1036];
  
  trap_GetConfigstring(param_1 + 0x2b1,local_41c,0x400);
  __src = (char *)Info_ValueForKey(local_41c,&g_unk_0023bf57);
  strncpy(param_2,__src,param_3 - 1);
  param_2[param_3 + -1] = '\0';
  Q_CleanStr(param_2);
  return param_2;
}

char * ClientName(uint param_1)
{
  char *tmp_pc1;
  
  if (param_1 < 0x40) {
    tmp_pc1 = (char *)ClientName_part_9();
    return tmp_pc1;
  }
  G_Printf("^1ClientName: client out of range\n");
  return "[client out of range]";
}

int ClientForString(char *param_1)
{
  long tmp_l1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  
  tmp_i5 = 0;
  tmp_i4 = 0;
  tmp_i2 = g_unk_00abe900;
  if (0 < g_unk_00abe900) {
    do {
      while (tmp_i3 = level + tmp_i4, *(int *)(tmp_i3 + 0x5ac) == 0) {
        tmp_i5 = tmp_i5 + 1;
        tmp_i4 = tmp_i4 + 0x54dc;
        if (tmp_i2 <= tmp_i5) goto LAB_000e3441;
      }
      tmp_i2 = Q_stricmp(tmp_i3 + 0x5f8,param_1);
      if (tmp_i2 == 0) {
        return tmp_i3;
      }
      tmp_i5 = tmp_i5 + 1;
      tmp_i4 = tmp_i4 + 0x54dc;
      tmp_i2 = g_unk_00abe900;
    } while (tmp_i5 < g_unk_00abe900);
  }
LAB_000e3441:
  if ((byte)(*param_1 - 0x30U) < 10) {
    tmp_l1 = strtol(param_1,(char **)0x0,10);
    if ((tmp_l1 < 0) || (g_unk_00abe900 <= tmp_l1)) {
      Com_Printf("Bad client slot: %i\n",tmp_l1);
      tmp_i2 = 0;
    }
    else {
      tmp_i2 = tmp_l1 * 0x54dc + level;
      if (*(int *)(tmp_i2 + 0x5ac) == 0) {
        G_Printf("Client %i is not connected\n",tmp_l1);
        tmp_i2 = 0;
      }
    }
  }
  else {
    G_Printf("User %s is not on the server\n",param_1);
    tmp_i2 = 0;
  }
  return tmp_i2;
}

