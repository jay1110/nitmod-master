/* Client and server console commands — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_cmds.h"

void Cmd_SetViewpos_f_part_9(uint32_t param_1)
{
  int tmp_i1;
  double tmp_d2;
  float afStack_438 [4];
  uint32_t local_428;
  float local_424;
  uint32_t local_420;
  char local_41c [1036];
  
  tmp_i1 = 0;
  local_420 = 0;
  local_424 = 0.0;
  local_428 = 0;
  do {
    tmp_i1 = tmp_i1 + 1;
    trap_Argv(tmp_i1,local_41c,0x400);
    tmp_d2 = strtod(local_41c,(char **)0x0);
    afStack_438[tmp_i1] = (float)tmp_d2;
  } while (tmp_i1 != 3);
  trap_Argv(4,local_41c,0x400);
  tmp_d2 = strtod(local_41c,(char **)0x0);
  local_424 = (float)tmp_d2;
  TeleportPlayer(param_1,afStack_438 + 1,&local_428);
  return;
}

void Cmd_IntermissionPlayerKillsDeaths_f_part_18(int param_1)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x611be;
  Q_strncpyz(local_41c,"impkd ",0x400);
  tmp_pu4 = g_entities;
  if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
    tmp_i2 = 0;
    tmp_i3 = 0;
    do {
      if (*(int *)(tmp_pu4 + 0x194) == 0) {
        tmp_pu1 = &g_unk_00245833;
      }
      else {
        tmp_pu1 = (uint8_t *)
                 va("%i %i ",*(uint32_t *)(level + tmp_i2 + 0xc7c),
                    *(uint32_t *)(level + tmp_i2 + 0xc74));
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu4 = tmp_pu4 + 0x600;
      tmp_i2 = tmp_i2 + 0x54dc;
      Q_strcat(local_41c,0x400,tmp_pu1);
    } while (tmp_i3 < (int)GHIDRA_FIELD(g_maxclients, 12, 4));
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,local_41c);
  return;
}

void Cmd_IntermissionWeaponAccuracies_f_part_19(int param_1)
{
  float *pfVar1;
  float tmp_f2;
  int *tmp_pi3;
  int *tmp_pi4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int local_43c;
  int *local_438;
  uint8_t *local_434;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  tmp_u5 = GHIDRA_FIELD(g_maxclients, 12, 4);
  uStack_14 = 0x612b9;
  local_434 = g_entities;
  if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
    local_43c = 0;
    local_438 = (int *)(level + 0xcac);
    do {
      if (*(int *)(local_434 + 0x194) == 0) {
        local_438[0x11af] = 0;
        local_438[0x11b0] = 0;
      }
      else {
        tmp_i6 = 0;
        tmp_i7 = 0;
        tmp_i8 = 0;
        tmp_pi3 = local_438;
        do {
          tmp_pi4 = tmp_pi3 + 5;
          tmp_i7 = tmp_i7 + *tmp_pi3;
          tmp_i6 = tmp_i6 + tmp_pi3[3];
          tmp_i8 = tmp_i8 + tmp_pi3[2];
          tmp_pi3 = tmp_pi4;
        } while (tmp_pi4 != local_438 + 0x82);
        tmp_f2 = 0.0;
        if (tmp_i7 != 0) {
          tmp_f2 = (float)(tmp_i6 * 100) / (float)tmp_i7;
        }
        local_438[0x11af] = (int)tmp_f2;
        local_438[0x11b0] = tmp_i8;
      }
      local_43c = local_43c + 1;
      local_434 = local_434 + 0x600;
      local_438 = local_438 + 0x1537;
    } while (local_43c < (int)tmp_u5);
  }
  Q_strncpyz(local_41c,"imwa ",0x400);
  if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
    tmp_i6 = 0;
    tmp_i7 = 0;
    do {
      tmp_i6 = tmp_i6 + 1;
      pfVar1 = (float *)(level + 0x5368 + tmp_i7);
      tmp_i7 = tmp_i7 + 0x54dc;
      tmp_u5 = va(&g_unk_002580b3,(int)ROUND(*pfVar1));
      Q_strcat(local_41c,0x400,tmp_u5);
    } while (tmp_i6 < (int)GHIDRA_FIELD(g_maxclients, 12, 4));
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,local_41c);
  return;
}

void Cmd_Score_f(int param_1)
{
  *(uint32_t *)(*(int *)(param_1 + 400) + 0x5374) = 1;
  return;
}

void Cmd_GiveDisguise_f(int param_1,int param_2)
{
  char *__nptr;
  uint tmp_u1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint tmp_u4;
  uint tmp_u5;
  bool tmp_b6;
  char *local_24;
  
  __nptr = (char *)ConcatArgs(param_2 + 1);
  if (*__nptr == '\0') {
    tmp_i2 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand(tmp_i2,"print \"^9usage : ^7givedisguise ^2<class>\n\"");
    trap_SendServerCommand
              (tmp_i2,
               "print \"^9        available choices are ^2s, m, e, f, ^9and ^2c^9, or the numbers ^20 ^9through ^24\n\""
              );
    trap_SendServerCommand(tmp_i2,"print \"^2        -1 ^9removes any current disguise.\n\"");
    return;
  }
  tmp_u1 = strtol(__nptr,(char **)0x0,10);
  if ((int)tmp_u1 < -1) {
    tmp_b6 = false;
    tmp_u1 = 0xffffffff;
LAB_00063eaa:
    tmp_i2 = Q_stricmpn(__nptr,"m",1);
    if ((tmp_i2 == 0) || (tmp_b6)) goto LAB_00063bbc;
    tmp_b6 = tmp_u1 == 2;
LAB_00063ee0:
    tmp_i2 = Q_stricmpn(__nptr,&g_unk_0025feb2,1);
    if ((tmp_i2 != 0) && (!tmp_b6)) {
      tmp_b6 = tmp_u1 == 3;
      local_24 = (char *)0x0;
      goto LAB_00063f1c;
    }
LAB_00063bdf:
    tmp_i2 = Q_stricmpn(__nptr,"f",1);
    if (tmp_i2 != 0) {
      local_24 = "^9givedisguise : ^7Engineer\n";
      tmp_u1 = 2;
      tmp_b6 = false;
      goto LAB_00063c12;
    }
LAB_00063c48:
    tmp_i2 = Q_stricmpn(__nptr,"c",1);
    if (tmp_i2 == 0) goto LAB_00063cb0;
    local_24 = "^9givedisguise : ^7Field Ops\n";
    tmp_u1 = 3;
    tmp_b6 = false;
LAB_00063c7b:
    tmp_i2 = Q_stricmpn(__nptr,&g_unk_0024e6ea,1);
    if ((tmp_i2 == 0) || (tmp_b6)) {
LAB_00063cd3:
      tmp_i2 = Q_stricmpn(__nptr,&g_unk_0025a5f5,1);
      if (tmp_i2 == 0) goto LAB_00063e10;
      local_24 = "^9givedisguise : ^7Soldier\n";
      tmp_u1 = 0;
      tmp_u4 = 0;
      tmp_u5 = 0;
      goto LAB_00063d06;
    }
    tmp_b6 = tmp_u1 == 0xffffffff;
  }
  else {
    if ((int)tmp_u1 < 5) {
      tmp_b6 = tmp_u1 == 1;
      goto LAB_00063eaa;
    }
    tmp_i2 = Q_stricmpn(__nptr,"m",1);
    if (tmp_i2 != 0) {
      tmp_b6 = false;
      tmp_u1 = 4;
      goto LAB_00063ee0;
    }
LAB_00063bbc:
    tmp_i2 = Q_stricmpn(__nptr,&g_unk_0025feb2,1);
    if (tmp_i2 == 0) goto LAB_00063bdf;
    local_24 = "^9givedisguise : ^7Medic\n";
    tmp_u1 = 1;
    tmp_b6 = false;
LAB_00063f1c:
    tmp_i2 = Q_stricmpn(__nptr,"f",1);
    if ((tmp_i2 == 0) || (tmp_b6)) goto LAB_00063c48;
    tmp_b6 = tmp_u1 == 4;
LAB_00063c12:
    tmp_i2 = Q_stricmpn(__nptr,"c",1);
    if ((tmp_i2 != 0) && (!tmp_b6)) {
      tmp_b6 = tmp_u1 == 0;
      goto LAB_00063c7b;
    }
LAB_00063cb0:
    tmp_i2 = Q_stricmpn(__nptr,&g_unk_0024e6ea,1);
    if (tmp_i2 == 0) goto LAB_00063cd3;
    local_24 = "^9givedisguise : ^7Covert Ops\n";
    tmp_u1 = 4;
    tmp_b6 = false;
  }
  tmp_i2 = Q_stricmpn(__nptr,&g_unk_0025a5f5,1);
  if ((tmp_i2 == 0) || (tmp_b6)) {
LAB_00063e10:
    trap_SendServerCommand
              ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
               "print \"^9givedisguise : ^7Removing disguise\n\"");
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x16c) = 0;
    return;
  }
  tmp_u5 = tmp_u1 & 1;
  tmp_u4 = tmp_u1 & 2;
  tmp_u1 = tmp_u1 & 4;
LAB_00063d06:
  *(uint32_t *)(*(int *)(param_1 + 400) + 0x16c) = 1;
  *(uint *)(*(int *)(param_1 + 400) + 0x170) = tmp_u5;
  *(uint *)(*(int *)(param_1 + 400) + 0x174) = tmp_u4;
  *(uint *)(*(int *)(param_1 + 400) + 0x178) = tmp_u1;
  Q_strncpyz(*(int *)(param_1 + 400) + 0x533c,*(int *)(param_1 + 400) + 0x5f8,0x24);
  *(uint32_t *)(*(int *)(param_1 + 400) + 0x5360) =
       *(uint32_t *)(*(int *)(param_1 + 400) + 0xc4c);
  tmp_u3 = va("print \"%s\"",local_24);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
  ClientUserinfoChanged(*(uint32_t *)(param_1 + 0xac));
  return;
}

void Cmd_Give_f(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  
  tmp_pc4 = "print \"Cheats are not enabled on this server.\n\"";
  if (GHIDRA_FIELD(g_cheats, 12, 4) != 0) {
    if (0 < *(int *)(param_1 + 0x2c8)) {
      tmp_u1 = ConcatArgs(3);
      tmp_u2 = ConcatArgs(2);
      tmp_u3 = ConcatArgs(1);
      ExecGive(param_1,tmp_u3,tmp_u2,tmp_u1);
      return;
    }
    tmp_pc4 = "print \"You must be alive to use this command.\n\"";
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc4);
  return;
}

void Cmd_God_f(int param_1)
{
  char tmp_c1;
  char *tmp_pc2;
  uint tmp_u3;
  long tmp_l4;
  
  if (GHIDRA_FIELD(g_cheats, 12, 4) == 0) {
    tmp_pc2 = "print \"Cheats are not enabled on this server.\n\"";
    goto LAB_000647c7;
  }
  tmp_pc2 = "print \"You must be alive to use this command.\n\"";
  if (*(int *)(param_1 + 0x2c8) < 1) goto LAB_000647c7;
  tmp_pc2 = (char *)ConcatArgs(1);
  if ((((*tmp_pc2 == 'o') && (tmp_pc2[1] == 'n')) && (tmp_pc2[2] == '\0')) ||
     (tmp_l4 = strtol(tmp_pc2,(char **)0x0,10), tmp_l4 != 0)) {
    tmp_u3 = *(uint *)(param_1 + 0x1b0) | 0x10;
    *(uint *)(param_1 + 0x1b0) = tmp_u3;
  }
  else {
    if (*tmp_pc2 == 'o') {
      if ((tmp_pc2[1] == 'f') && (tmp_pc2[2] == 'f')) {
        tmp_c1 = tmp_pc2[3];
joined_r0x00064869:
        if (tmp_c1 == '\0') {
          tmp_u3 = *(uint *)(param_1 + 0x1b0) & 0xffffffef;
          *(uint *)(param_1 + 0x1b0) = tmp_u3;
          goto LAB_000647b9;
        }
      }
    }
    else if (*tmp_pc2 == '0') {
      tmp_c1 = tmp_pc2[1];
      goto joined_r0x00064869;
    }
    tmp_u3 = *(uint *)(param_1 + 0x1b0) ^ 0x10;
    *(uint *)(param_1 + 0x1b0) = tmp_u3;
  }
LAB_000647b9:
  if ((tmp_u3 & 0x10) == 0) {
    tmp_pc2 = "print \"^9godmode ^1OFF\n\"";
  }
  else {
    tmp_pc2 = "print \"^9godmode ^2ON\n\"";
  }
LAB_000647c7:
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc2);
  return;
}

void Cmd_Nofatigue_f(int param_1)
{
  char *tmp_pc1;
  long tmp_l2;
  uint tmp_u3;
  
  tmp_pc1 = (char *)ConcatArgs(1);
  if (GHIDRA_FIELD(g_cheats, 12, 4) == 0) {
    tmp_pc1 = "print \"Cheats are not enabled on this server.\n\"";
    goto LAB_00064976;
  }
  if (*(int *)(param_1 + 0x2c8) < 1) {
    tmp_pc1 = "print \"You must be alive to use this command.\n\"";
    goto LAB_00064976;
  }
  if (((*tmp_pc1 == 'o') && (tmp_pc1[1] == 'n')) && (tmp_pc1[2] == '\0')) {
LAB_0006494c:
    tmp_u3 = *(uint *)(param_1 + 0x1b0) | 0x10000;
    *(uint *)(param_1 + 0x1b0) = tmp_u3;
  }
  else {
    tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
    if (tmp_l2 != 0) goto LAB_0006494c;
    if (*tmp_pc1 == 'o') {
      if ((tmp_pc1[1] == 'f') && ((tmp_pc1[2] == 'f' && (tmp_pc1[3] == '\0')))) goto LAB_00064925;
LAB_000649d0:
      tmp_u3 = *(uint *)(param_1 + 0x1b0) ^ 0x10000;
      *(uint *)(param_1 + 0x1b0) = tmp_u3;
    }
    else {
      if ((*tmp_pc1 != '0') || (tmp_pc1[1] != '\0')) goto LAB_000649d0;
LAB_00064925:
      tmp_u3 = *(uint *)(param_1 + 0x1b0) & 0xfffeffff;
      *(uint *)(param_1 + 0x1b0) = tmp_u3;
    }
  }
  if ((tmp_u3 & 0x10000) == 0) {
    tmp_pc1 = "print \"^9nofatigue ^1OFF\n\"";
  }
  else {
    tmp_pc1 = "print \"^9nofatigue ^2ON\n\"";
  }
LAB_00064976:
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc1);
  return;
}

void Cmd_Notarget_f(int param_1)
{
  uint tmp_u1;
  char *tmp_pc2;
  
  if (GHIDRA_FIELD(g_cheats, 12, 4) == 0) {
    tmp_pc2 = "print \"Cheats are not enabled on this server.\n\"";
  }
  else {
    tmp_pc2 = "print \"You must be alive to use this command.\n\"";
    if (0 < *(int *)(param_1 + 0x2c8)) {
      tmp_u1 = *(uint *)(param_1 + 0x1b0) ^ 0x20;
      *(uint *)(param_1 + 0x1b0) = tmp_u1;
      if ((tmp_u1 & 0x20) == 0) {
        tmp_pc2 = "print \"notarget ^1OFF\n\"";
      }
      else {
        tmp_pc2 = "print \"notarget ^2ON\n\"";
      }
    }
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc2);
  return;
}

void Cmd_Noclip_f(int param_1)
{
  char *__nptr;
  long tmp_l1;
  char *tmp_pc2;
  
  __nptr = (char *)ConcatArgs(1);
  if (GHIDRA_FIELD(g_cheats, 12, 4) == 0) {
    tmp_pc2 = "print \"Cheats are not enabled on this server.\n\"";
    goto LAB_00064b63;
  }
  tmp_pc2 = "print \"You must be alive to use this command.\n\"";
  if (*(int *)(param_1 + 0x2c8) < 1) goto LAB_00064b63;
  if (((*__nptr == 'o') && (__nptr[1] == 'n')) && (__nptr[2] == '\0')) {
LAB_00064b3c:
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xf6c) = 1;
  }
  else {
    tmp_l1 = strtol(__nptr,(char **)0x0,10);
    if (tmp_l1 != 0) goto LAB_00064b3c;
    if (*__nptr == 'o') {
      if ((__nptr[1] == 'f') && ((__nptr[2] == 'f' && (__nptr[3] == '\0')))) goto LAB_00064b1b;
LAB_00064bc0:
      *(uint *)(*(int *)(param_1 + 400) + 0xf6c) =
           (uint)(*(int *)(*(int *)(param_1 + 400) + 0xf6c) == 0);
    }
    else {
      if ((*__nptr != '0') || (__nptr[1] != '\0')) goto LAB_00064bc0;
LAB_00064b1b:
      *(uint32_t *)(*(int *)(param_1 + 400) + 0xf6c) = 0;
    }
  }
  if (*(int *)(*(int *)(param_1 + 400) + 0xf6c) == 0) {
    tmp_pc2 = "print \"^9noclip ^1OFF\n\"";
  }
  else {
    tmp_pc2 = "print \"^9noclip ^2ON\n\"";
  }
LAB_00064b63:
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc2);
  return;
}

void Cmd_Kill_f(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  if (param_1 == 0) {
    return;
  }
  tmp_i1 = *(int *)(param_1 + 400);
  if (tmp_i1 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0x2c8) < 1) {
    if ((*(byte *)(param_1 + 0x128) & 8) == 0) {
      return;
    }
    limbo(param_1,1);
    return;
  }
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    if ((*(byte *)(param_1 + 0x128) & 8) != 0) {
      return;
    }
    if ((g_DMOptions[0xc] & 4) != 0) {
      G_shrubbot_print(param_1,"^1Sorry, Selfkill is disabled on this server during DeathMatch!\n");
      return;
    }
  }
  else {
    if ((GHIDRA_FIELD(g_gametype, 12, 4) == 7) && ((g_TDMOptions[0xc] & 2) != 0)) {
      G_shrubbot_print(param_1,
                       "^1Sorry, Selfkill is disabled on this server during TeamDeathMatch!\n");
      return;
    }
    if ((*(byte *)(param_1 + 0x128) & 8) != 0) goto LAB_00064c4e;
  }
  if ((GHIDRA_FIELD(g_slashKill, 12, 4) & 8) != 0) {
    G_shrubbot_print(param_1,"Selfkill disabled on this server.\n");
    return;
  }
  if (((GHIDRA_FIELD(g_slashKill, 12, 4) & 0x10) != 0) && ((*(byte *)(tmp_i1 + 0x6a) & 0x20) != 0)) {
    G_shrubbot_print(param_1,"Selfkill disabled while you are poisoned.\n");
    return;
  }
  if (((GHIDRA_FIELD(g_slashKill, 12, 4) & 0x40) != 0) && (g_unk_00abe908 - *(int *)(tmp_i1 + 0xfac) < 3000)) {
    G_shrubbot_print(param_1,"Selfkill disabled while being in a fight.\n");
    return;
  }
LAB_00064c4e:
  if (((*(int *)(tmp_i1 + 3000) != 3) && ((*(byte *)(tmp_i1 + 0xd) & 0x40) == 0)) &&
     (g_unk_02a99a78 == 0)) {
    *(uint32_t *)(tmp_i1 + 0x9cc) = 1;
    *(uint *)(param_1 + 0x1b0) = *(uint *)(param_1 + 0x1b0) & 0xffffffef;
    *(uint32_t *)(param_1 + 0x2c8) = 0;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xd0) = 0;
    tmp_u2 = GHIDRA_FIELD(g_fear, 12, 4);
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x140) = 0;
    tmp_i1 = *(int *)(param_1 + 400);
    tmp_i3 = *(int *)(tmp_i1 + 0xfa4) * 0x600 + g_unk_00abe8a4;
    if ((((tmp_i3 == 0) || (tmp_u2 == 0)) ||
        ((*(int *)(tmp_i3 + 400) == 0 ||
         (((int)tmp_u2 <= g_unk_00abe908 - *(int *)(tmp_i1 + 0xfac) ||
          (*(int *)(*(int *)(tmp_i3 + 400) + 3000) == *(int *)(tmp_i1 + 3000))))))) ||
       (*(int *)(tmp_i3 + 0x2c8) < 1)) {
      player_die(param_1,param_1,param_1,(-(uint)(GHIDRA_FIELD(g_gamestate, 12, 4) == 0) & 0x18619) + 0x87,0x20);
    }
    else {
      player_die(param_1,tmp_i3,tmp_i3,*(int *)(param_1 + 0x2c8) + 0x96,0x3c);
    }
  }
  return;
}

void G_TeamDataForString(byte *param_1,int param_2,uint *param_3,uint32_t *param_4,
                        uint32_t *param_5)

{
  byte tmp_b1;
  uint tmp_u2;
  int tmp_i3;
  byte *tmp_pb4;
  byte *tmp_pb5;
  bool tmp_b6;
  bool tmp_b7;
  bool tmp_b8;
  
  tmp_i3 = 8;
  tmp_b8 = false;
  *param_4 = 0;
  tmp_pb4 = param_1;
  tmp_pb5 = (byte *)"follow1";
  do {
    if (tmp_i3 == 0) break;
    tmp_i3 = tmp_i3 + -1;
    tmp_b8 = *tmp_pb4 == *tmp_pb5;
    tmp_pb4 = tmp_pb4 + 1;
    tmp_pb5 = tmp_pb5 + 1;
  } while (tmp_b8);
  if (tmp_b8) {
    *param_3 = 3;
    *param_4 = 2;
    if (param_5 != (uint32_t *)0x0) {
      *param_5 = 0xffffffff;
      return;
    }
    return;
  }
  tmp_i3 = 8;
  tmp_b8 = false;
  tmp_pb4 = param_1;
  tmp_pb5 = (byte *)"follow2";
  do {
    if (tmp_i3 == 0) break;
    tmp_i3 = tmp_i3 + -1;
    tmp_b8 = *tmp_pb4 == *tmp_pb5;
    tmp_pb4 = tmp_pb4 + 1;
    tmp_pb5 = tmp_pb5 + 1;
  } while (tmp_b8);
  if (tmp_b8) {
    *param_3 = 3;
    *param_4 = 2;
    if (param_5 != (uint32_t *)0x0) {
      *param_5 = 0xfffffffe;
      return;
    }
    return;
  }
  tmp_i3 = 10;
  tmp_b8 = false;
  tmp_pb4 = param_1;
  tmp_pb5 = (byte *)"spectator";
  do {
    if (tmp_i3 == 0) break;
    tmp_i3 = tmp_i3 + -1;
    tmp_b8 = *tmp_pb4 == *tmp_pb5;
    tmp_pb4 = tmp_pb4 + 1;
    tmp_pb5 = tmp_pb5 + 1;
  } while (tmp_b8);
  if (tmp_b8) {
LAB_00064f95:
    *param_3 = 3;
    *param_4 = 1;
    return;
  }
  tmp_b1 = *param_1;
  if (tmp_b1 == 0x73) {
    tmp_b6 = false;
    tmp_b8 = false;
    if (param_1[1] == 0) goto LAB_00064f95;
  }
  else {
    tmp_b6 = tmp_b1 < 0x72;
    tmp_b8 = false;
    if (tmp_b1 == 0x72) {
      if (param_1[1] == 0x65) {
        tmp_b6 = param_1[2] < 100;
        tmp_b8 = false;
        if (param_1[2] != 100) goto LAB_00064fd0;
        tmp_b7 = param_1[3] == 0;
        tmp_b8 = false;
      }
      else {
        tmp_b7 = param_1[1] == 0;
        tmp_b8 = tmp_b7;
      }
      tmp_b6 = false;
      if (tmp_b7) goto LAB_0006503c;
    }
  }
LAB_00064fd0:
  tmp_i3 = 5;
  tmp_pb4 = param_1;
  tmp_pb5 = (byte *)0x24e767;
  do {
    if (tmp_i3 == 0) break;
    tmp_i3 = tmp_i3 + -1;
    tmp_b6 = *tmp_pb4 < *tmp_pb5;
    tmp_b8 = *tmp_pb4 == *tmp_pb5;
    tmp_pb4 = tmp_pb4 + 1;
    tmp_pb5 = tmp_pb5 + 1;
  } while (tmp_b8);
  tmp_b7 = (!tmp_b6 && !tmp_b8) < tmp_b6;
  tmp_b8 = (!tmp_b6 && !tmp_b8) == tmp_b6;
  if (!tmp_b8) {
    tmp_i3 = 5;
    tmp_pb4 = param_1;
    tmp_pb5 = &g_unk_0023bbe7;
    do {
      if (tmp_i3 == 0) break;
      tmp_i3 = tmp_i3 + -1;
      tmp_b7 = *tmp_pb4 < *tmp_pb5;
      tmp_b8 = *tmp_pb4 == *tmp_pb5;
      tmp_pb4 = tmp_pb4 + 1;
      tmp_pb5 = tmp_pb5 + 1;
    } while (tmp_b8);
    if (((!tmp_b7 && !tmp_b8) != tmp_b7) &&
       ((tmp_b8 = tmp_b1 == 0x62, !tmp_b8 || (tmp_b8 = param_1[1] == 0, !tmp_b8)))) {
      tmp_i3 = 7;
      tmp_pb4 = (byte *)0x24e75d;
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_b8 = *param_1 == *tmp_pb4;
        param_1 = param_1 + 1;
        tmp_pb4 = tmp_pb4 + 1;
      } while (tmp_b8);
      if (!tmp_b8) {
        tmp_u2 = PickTeam(param_2);
        *param_3 = tmp_u2;
        tmp_i3 = G_teamJoinCheck(tmp_u2,g_entities + param_2 * 0x600);
        if (tmp_i3 == 0) {
          *param_3 = ~*param_3 & 3;
          return;
        }
        return;
      }
    }
    *param_3 = 2;
    return;
  }
LAB_0006503c:
  *param_3 = 1;
  return;
}

void Cmd_ResetSetup_f(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  bool tmp_b3;
  
  if (param_1 == 0) {
    return;
  }
  tmp_i1 = *(int *)(param_1 + 400);
  if (tmp_i1 == 0) {
    return;
  }
  tmp_i2 = *(int *)(tmp_i1 + 0xbc8);
  tmp_b3 = *(int *)(tmp_i1 + 0xbd8) == tmp_i2;
  if (!tmp_b3) {
    *(int *)(tmp_i1 + 0xbd8) = tmp_i2;
    tmp_i1 = *(int *)(param_1 + 400);
  }
  if (*(int *)(tmp_i1 + 0xbdc) == *(int *)(tmp_i1 + 0xbcc)) {
    tmp_i2 = *(int *)(tmp_i1 + 0xbd0);
    if (*(int *)(tmp_i1 + 0xbe0) == tmp_i2) {
      if (tmp_b3) {
        return;
      }
      goto LAB_00066383;
    }
  }
  else {
    *(int *)(tmp_i1 + 0xbdc) = *(int *)(tmp_i1 + 0xbcc);
    tmp_i1 = *(int *)(param_1 + 400);
    tmp_i2 = *(int *)(tmp_i1 + 0xbd0);
    if (*(int *)(tmp_i1 + 0xbe0) == tmp_i2) goto LAB_00066383;
  }
  *(int *)(tmp_i1 + 0xbe0) = tmp_i2;
LAB_00066383:
  ClientUserinfoChanged((param_1 + -0x93e4a0 >> 9) * -0x55555555);
  return;
}

void Cmd_Say_f(uint32_t param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = trap_Argc();
  if ((1 < tmp_i1) || (param_3 != 0)) {
    tmp_u2 = ConcatArgs(0);
    if ((GHIDRA_FIELD(g_privateMessages, 12, 4) != 0) &&
       (((((tmp_i1 = Q_stricmpn(tmp_u2,"say /m ",7), tmp_i1 == 0 ||
           (tmp_i1 = Q_stricmpn(tmp_u2,"say_team /m ",0xc), tmp_i1 == 0)) ||
          (tmp_i1 = Q_stricmpn(tmp_u2,"say_buddy /m ",0xd), tmp_i1 == 0)) ||
         ((tmp_i1 = Q_stricmpn(tmp_u2,"say /pm ",8), tmp_i1 == 0 ||
          (tmp_i1 = Q_stricmpn(tmp_u2,"say_team /pm ",0xd), tmp_i1 == 0)))) ||
        (tmp_i1 = Q_stricmpn(tmp_u2,"say_buddy /pm ",0xe), tmp_i1 == 0)))) {
      G_PrivateMessage();
      return;
    }
    tmp_i1 = Q_stricmpn(tmp_u2,"say /ma ",8);
    if (((tmp_i1 != 0) && (tmp_i1 = Q_stricmpn(tmp_u2,"say_team /ma ",0xd), tmp_i1 != 0)) &&
       (tmp_i1 = Q_stricmpn(tmp_u2,"say_buddy /ma ",0xe), tmp_i1 != 0)) {
      tmp_u2 = ConcatArgs(param_3 == 0);
      G_Say(param_1,0,param_2,tmp_u2);
      return;
    }
    Nit_AdminChat(param_1);
  }
  return;
}

void Cmd_Where_f(int param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = vtos(param_1 + 0x5c);
  tmp_u1 = va("print \"%s\n\"",tmp_u1);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
  return;
}

uint32_t Cmd_CallVote_f(uint32_t *param_1,uint32_t param_2,int param_3)
{
  uint *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  char *tmp_pc4;
  char *tmp_pc5;
  long tmp_l6;
  uint32_t tmp_u7;
  int tmp_i8;
  char local_31c [256];
  char local_21c [256];
  uint8_t local_11c [268];
  
  tmp_i8 = ((int)(param_1 + -0x24f928) >> 9) * -0x55555555;
  tmp_i3 = ((int)(param_1 + -0x24f928) >> 9) * -0x5555390c + level;
  tmp_i3 = G_shrubbot_mute_check(tmp_i3 + 0x61c,tmp_i3 + 0xaf4);
  if ((tmp_i3 == 0) && (*(int *)(param_1[100] + 0xbf0) == 0)) {
    if (param_3 != 0) goto LAB_00069460;
    if (g_unk_00abee4c != 0) {
      nitmod_cp(param_1,0x1c);
      return 0;
    }
    if (g_unk_00abf994 != 0) {
      nitmod_cp(param_1,0x1d);
      return 0;
    }
    if (*(int *)(param_1[100] + 0xc80) == 0) {
      tmp_i3 = nitrox_CheckPermission(param_1,6);
      if ((tmp_i3 == 0) && (GHIDRA_FIELD(voteFlags, 12, 4) == (1 << ((byte)numVotesAvailable & 0x1f)) + -1)) {
        nitmod_cp(param_1,0x1e);
        return 0;
      }
      tmp_i2 = param_1[100];
      if (((0 < (int)GHIDRA_FIELD(vote_limit, 12, 4)) && (tmp_i3 == 0)) &&
         ((int)GHIDRA_FIELD(vote_limit, 12, 4) <= *(int *)(tmp_i2 + 0x68c))) {
        tmp_u7 = va("cp \"You have already called the maximum number of votes (%d).\"",
                   GHIDRA_FIELD(vote_limit, 12, 4));
        trap_SendServerCommand(tmp_i8,tmp_u7);
        return 0;
      }
      if ((*(int *)(tmp_i2 + 3000) == 3) && (*(int *)(tmp_i2 + 0xc80) == 0)) {
        nitmod_cp(param_1,0x1f);
        return 0;
      }
      tmp_i3 = nitrox_CheckPermission(param_1,0xb);
      if (tmp_i3 != 0) {
        nitmod_cp(param_1,0x20);
        return 0;
      }
    }
    trap_Argv(1,local_31c,0x100);
    trap_Argv(2,local_21c,0x100);
    tmp_pc5 = strchr(local_31c,0x3b);
    if ((tmp_pc5 == (char *)0x0) && (tmp_pc5 = strchr(local_21c,0x3b), tmp_pc5 == (char *)0x0)) {
LAB_00069679:
      tmp_pc5 = strchr(local_31c,0xd);
      if ((tmp_pc5 == (char *)0x0) &&
         ((((tmp_pc5 = strchr(local_21c,0xd), tmp_pc5 == (char *)0x0 &&
            (tmp_pc5 = strchr(local_31c,10), tmp_pc5 == (char *)0x0)) &&
           (tmp_pc5 = strchr(local_21c,10), tmp_pc5 == (char *)0x0)) &&
          ((tmp_pc5 = strchr(local_31c,0x5c), tmp_pc5 == (char *)0x0 &&
           (tmp_pc5 = strchr(local_21c,0x5c), tmp_pc5 == (char *)0x0)))))) {
        tmp_i3 = trap_Argc();
        if ((tmp_i3 < 2) ||
           (tmp_i3 = G_voteCmdCheck(param_1,local_31c,local_21c,param_3), tmp_i3 == -2)) {
          if (param_3 != 0) {
            return 0;
          }
          tmp_u7 = va("print \"\n^3>>> Unknown vote command: ^7%s %s\n\"",local_31c,local_21c);
          trap_SendServerCommand(tmp_i8,tmp_u7);
          G_voteHelp(param_1,1);
          return 0;
        }
        if (tmp_i3 != 0) {
          return 1;
        }
        tmp_i3 = Q_stricmp(local_31c,"timelimit");
        if (((tmp_i3 == 0) && (0 < (int)GHIDRA_FIELD(n_voteMaxTimelimit, 12, 4))) &&
           (tmp_l6 = strtol(local_21c,(char **)0x0,10), (int)GHIDRA_FIELD(n_voteMaxTimelimit, 12, 4) < tmp_l6)) {
          tmp_u7 = va("%i",GHIDRA_FIELD(n_voteMaxTimelimit, 12, 4));
          Q_strncpyz(local_21c,tmp_u7,0x100);
        }
        Com_sprintf(&g_unk_00abea4c,0x400,"%s %s",local_31c,local_21c);
        if (param_3 != 0) {
          if ((g_unk_00abee64 != G_Kick_v) && (g_unk_00abee64 != G_Mute_v)) {
            nitmod_cp(0,0x21);
          }
          (*g_unk_00abee64)(0,0,0,0,0);
          nitmod_Sound_Global(0xc);
          g_unk_00abee4c = g_unk_00abe908;
          g_unk_00abee54 = 0;
          return 1;
        }
        g_unk_00abee50 = (uint)(g_unk_00abee64 != G_Poll_v);
        tmp_u7 = va("print \"[lof]%s^7 [lon]called a vote.[lof]  Voting for: %s\n\"",
                   param_1[100] + 0x5f8,&g_unk_00abea4c);
        trap_SendServerCommand(0xffffffff,tmp_u7);
        g_unk_00abef68 = *param_1;
        g_unk_00abef6c = *(uint32_t *)(param_1[100] + 3000);
        tmp_u7 = va("print \"[lof]%s^7 [lon]called a vote.\n\"",param_1[100] + 0x5f8);
        trap_SendServerCommand(0xffffffff,tmp_u7);
        tmp_u7 = va("cp \"[lof]%s\n^7[lon]called a vote.\n\"",param_1[100] + 0x5f8);
        trap_SendServerCommand(0xffffffff,tmp_u7);
        nitmod_Sound_Global(0xd);
        tmp_i8 = level;
        g_unk_00abee54 = 0;
        g_unk_00abee4c = g_unk_00abe908;
        for (tmp_i3 = 0; tmp_i3 < g_unk_00abe938; tmp_i3 = tmp_i3 + 1) {
          tmp_pu1 = (uint *)(tmp_i8 + 0x68 + (&g_unk_00abe944)[tmp_i3] * 0x54dc);
          *tmp_pu1 = *tmp_pu1 & 0xffffbfff;
        }
        *(int *)(param_1[100] + 0x68c) = *(int *)(param_1[100] + 0x68c) + 1;
        if (g_unk_00abee64 != G_Poll_v) {
          *(uint *)(param_1[100] + 0x68) = *(uint *)(param_1[100] + 0x68) | 0x4000;
        }
        tmp_u7 = va("%i",g_unk_00abee50);
        trap_SetConfigstring(8,tmp_u7);
        tmp_u7 = va("%i",g_unk_00abee54);
        trap_SetConfigstring(9,tmp_u7);
        Q_strncpyz(local_11c,&g_unk_00abea4c,0x100);
        if ((g_voting[0xc] & 4) != 0) {
          Q_strcat(local_11c,0x100," (called by ");
          Q_strcat(local_11c,0x100,param_1[100] + 0x5f8);
          Q_strcat(local_11c,0x100,&g_unk_002612da);
        }
        trap_SetConfigstring(7,local_11c);
        tmp_u7 = va("%i",g_unk_00abee4c);
        trap_SetConfigstring(6,tmp_u7);
        return 1;
      }
      goto LAB_000694d1;
    }
  }
  else {
    if (param_3 == 0) {
      nitmod_cp(param_1,0x1b);
      return 0;
    }
LAB_00069460:
    trap_Argv(1,local_31c,0x100);
    trap_Argv(2,local_21c,0x100);
    tmp_pc4 = strchr(local_31c,0x3b);
    tmp_pc5 = "ref command";
    if (tmp_pc4 != (char *)0x0) goto LAB_00069443;
    tmp_pc5 = strchr(local_21c,0x3b);
    if (tmp_pc5 == (char *)0x0) goto LAB_00069679;
LAB_000694d1:
    tmp_pc5 = "ref command";
    if (param_3 != 0) goto LAB_00069443;
  }
  tmp_pc5 = "vote";
LAB_00069443:
  G_refPrintf(param_1,"Invalid %s string.",tmp_pc5);
  return 0;
}

void Cmd_Vote_f(int param_1)
{
  uint *tmp_pu1;
  bool tmp_b2;
  int tmp_i3;
  char *tmp_pc4;
  int tmp_i5;
  uint tmp_u6;
  long tmp_l7;
  uint32_t tmp_u8;
  int tmp_i9;
  int tmp_i10;
  int local_8c;
  uint local_64;
  uint local_60;
  char local_5c;
  char local_5b;
  
  tmp_i3 = G_shrubbot_mute_check(*(int *)(param_1 + 400) + 0x61c,*(int *)(param_1 + 400) + 0xaf4);
  tmp_i10 = g_unk_00abe908;
  tmp_i9 = *(int *)(param_1 + 400);
  if ((tmp_i3 != 0) || (tmp_b2 = false, *(int *)(tmp_i9 + 0xbf0) != 0)) {
    tmp_b2 = true;
  }
  if (((*(int *)(tmp_i9 + 0x69c) <= g_unk_00abe908) || (GHIDRA_FIELD(g_gamestate, 12, 4) != 0)) ||
     (GHIDRA_FIELD(g_complaintlimit, 12, 4) == 0)) {
    if (g_unk_00abe908 < *(int *)(tmp_i9 + 0x6b0)) {
      if (*(int *)(g_entities + *(int *)(tmp_i9 + 0x6ac) * 0x600 + 400) == 0) {
        return;
      }
      if (*(int *)(*(int *)(g_entities + *(int *)(tmp_i9 + 0x6ac) * 0x600 + 400) + 0x5ac) != 2) {
        return;
      }
      trap_Argv(1,&local_5c,0x40);
      if (((local_5c == 'y') || (local_5b == 'Y')) || (local_5b == '1')) {
        tmp_i9 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        trap_SendServerCommand(tmp_i9,"application -4");
        trap_SendServerCommand(*(uint32_t *)(*(int *)(param_1 + 400) + 0x6ac),"application -3");
        G_AddClientToFireteam(*(uint32_t *)(*(int *)(param_1 + 400) + 0x6ac),tmp_i9);
      }
      else {
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,"application -4");
        trap_SendServerCommand(*(uint32_t *)(*(int *)(param_1 + 400) + 0x6ac),"application -2");
      }
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x6b0) = 0;
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x6ac) = 0xffffffff;
      return;
    }
    *(uint32_t *)(tmp_i9 + 0x6b0) = 0;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x6ac) = 0xffffffff;
    tmp_i9 = *(int *)(param_1 + 400);
    if (tmp_i10 < *(int *)(tmp_i9 + 0x6b8)) {
      if (*(int *)(g_entities + *(int *)(tmp_i9 + 0x6b4) * 0x600 + 400) == 0) {
        return;
      }
      if (*(int *)(*(int *)(g_entities + *(int *)(tmp_i9 + 0x6b4) * 0x600 + 400) + 0x5ac) != 2) {
        return;
      }
      trap_Argv(1,&local_5c,0x40);
      if (((local_5c == 'y') || (local_5b == 'Y')) || (local_5b == '1')) {
        tmp_i9 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        trap_SendServerCommand(tmp_i9,"invitation -4");
        trap_SendServerCommand(*(uint32_t *)(*(int *)(param_1 + 400) + 0x6b4),"invitation -3");
        G_AddClientToFireteam(tmp_i9,*(uint32_t *)(*(int *)(param_1 + 400) + 0x6b4));
      }
      else {
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,"invitation -4");
        trap_SendServerCommand(*(uint32_t *)(*(int *)(param_1 + 400) + 0x6b4),"invitation -2");
      }
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x6b8) = 0;
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x6b4) = 0xffffffff;
      return;
    }
    *(uint32_t *)(tmp_i9 + 0x6b8) = 0;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x6b4) = 0xffffffff;
    tmp_i9 = *(int *)(param_1 + 400);
    if (tmp_i10 < *(int *)(tmp_i9 + 0x6c4)) {
      if (*(int *)(g_entities + *(int *)(tmp_i9 + 0x6bc) * 0x600 + 400) == 0) {
        return;
      }
      if (*(int *)(*(int *)(g_entities + *(int *)(tmp_i9 + 0x6bc) * 0x600 + 400) + 0x5ac) != 2) {
        return;
      }
      trap_Argv(1,&local_5c,0x40);
      if (((local_5c == 'y') || (local_5b == 'Y')) || (local_5b == '1')) {
        tmp_i9 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        trap_SendServerCommand(tmp_i9,"proposition -4");
        trap_SendServerCommand(*(uint32_t *)(*(int *)(param_1 + 400) + 0x6c0),"proposition -3");
        G_InviteToFireTeam(tmp_i9,*(uint32_t *)(*(int *)(param_1 + 400) + 0x6bc));
      }
      else {
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,"proposition -4");
        trap_SendServerCommand(*(uint32_t *)(*(int *)(param_1 + 400) + 0x6c0),"proposition -2");
      }
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x6c4) = 0;
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x6bc) = 0xffffffff;
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x6c0) = 0xffffffff;
      return;
    }
    if (tmp_i10 < *(int *)(tmp_i9 + 0x6c8)) {
      trap_Argv(1,&local_5c,0x40);
      if (((local_5c == 'y') || (local_5b == '1')) || (local_5b == 'Y')) {
        tmp_i9 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        trap_SendServerCommand(tmp_i9,"aft -2");
        tmp_i9 = G_IsFireteamLeader(tmp_i9,&local_64);
        if (tmp_i9 != 0) {
          *(uint32_t *)(local_64 + 0x4c) = 1;
        }
      }
      else {
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,"aft -2");
      }
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x6c8) = 0;
      return;
    }
    if (tmp_i10 < *(int *)(tmp_i9 + 0x6cc)) {
      trap_Argv(1,&local_5c,0x40);
      if (((local_5c == 'y') || (local_5b == 'Y')) || (local_5b == '1')) {
        tmp_i9 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        trap_SendServerCommand(tmp_i9,"aftc -2");
        G_RegisterFireteam(tmp_i9);
        goto LAB_0006a2e2;
      }
      tmp_pc4 = "aftc -2";
    }
    else {
      if (*(int *)(tmp_i9 + 0x6d0) <= tmp_i10) {
        *(uint32_t *)(tmp_i9 + 0x6c4) = 0;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x6bc) = 0xffffffff;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x6c0) = 0xffffffff;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x69c) = 0xffffffff;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0x698) = 0xffffffff;
        tmp_pc4 = "print \"No vote in progress.\n\"";
        if (g_unk_00abee4c != 0) {
          tmp_i9 = *(int *)(param_1 + 400);
          if ((*(byte *)(tmp_i9 + 0x69) & 0x40) == 0) {
            if ((*(int *)(tmp_i9 + 3000) == 3) && (*(int *)(tmp_i9 + 0xc80) == 0)) {
              trap_SendServerCommand
                        ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                         "print \"Not allowed to vote as spectator.\n\"");
              return;
            }
            tmp_pc4 = "print \"Not allowed to vote when muted.\n\"";
            if (!tmp_b2) {
              if (g_unk_00abee64 == G_Kick_v) {
                tmp_l7 = strtol(&g_unk_00abee68,(char **)0x0,10);
                if (*(int *)(g_entities + tmp_l7 * 0x600 + 400) == 0) {
                  return;
                }
                tmp_i9 = *(int *)(*(int *)(g_entities + tmp_l7 * 0x600 + 400) + 3000);
                if ((tmp_i9 != 3) && (tmp_i9 != *(int *)(*(int *)(param_1 + 400) + 3000))) {
                  trap_SendServerCommand
                            ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
                             "print \"Cannot vote to kick player on opposing team.\n\"");
                  return;
                }
              }
              else if ((g_unk_00abee64 == G_Surrender_v) && (*(int *)(tmp_i9 + 3000) != g_unk_00abef6c))
              {
                nitmod_cp(param_1,0x22);
                return;
              }
              trap_SendServerCommand
                        ((param_1 + -0x93e4a0 >> 9) * -0x55555555,"print \"Vote cast.\n\"");
              tmp_pu1 = (uint *)(*(int *)(param_1 + 400) + 0x68);
              *tmp_pu1 = *tmp_pu1 | 0x4000;
              trap_Argv(1,&local_5c,0x40);
              if (((local_5c != 'y') && (local_5b != 'Y')) && (local_5b != '1')) {
                g_unk_00abee54 = g_unk_00abee54 + 1;
                tmp_u8 = va("%i",g_unk_00abee54);
                trap_SetConfigstring(9,tmp_u8);
                return;
              }
              g_unk_00abee50 = g_unk_00abee50 + 1;
              tmp_u8 = va("%i",g_unk_00abee50);
              trap_SetConfigstring(8,tmp_u8);
              return;
            }
          }
          else {
            tmp_pc4 = "print \"Vote already cast.\n\"";
          }
        }
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc4);
        return;
      }
      trap_Argv(1,&local_5c,0x40);
      if (((local_5c == 'y') || (local_5b == '1')) || (local_5b == 'Y')) {
        tmp_i10 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        trap_SendServerCommand(tmp_i10,"aftj -2");
        tmp_i9 = G_FindFreePublicFireteam(*(uint32_t *)(*(int *)(param_1 + 400) + 3000));
        if (tmp_i9 != 0) {
          G_AddClientToFireteam(tmp_i10,(int)*(char *)(tmp_i9 + 4));
        }
        goto LAB_0006a2e2;
      }
      tmp_pc4 = "aftj -2";
    }
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc4);
LAB_0006a2e2:
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x6cc) = 0;
    return;
  }
  tmp_i10 = *(int *)(tmp_i9 + 0x698);
  tmp_i9 = *(int *)(g_entities + tmp_i10 * 0x600 + 400);
  if (tmp_i9 == 0) {
    return;
  }
  if (*(int *)(tmp_i9 + 0x5ac) != 2) {
    return;
  }
  if (*(int *)(tmp_i9 + 0x5e8) != 0) {
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,"complaint -3");
    return;
  }
  trap_Argv(1,&local_5c,0x40);
  if (((local_5c != 'y') && (local_5b != 'Y')) && (local_5b != '1')) {
    trap_SendServerCommand
              (*(uint32_t *)(*(int *)(param_1 + 400) + 0x698),
               "cpm \"No complaint filed against you.\n\"");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,"complaint -2");
    goto LAB_0006a5b2;
  }
  tmp_i3 = *(int *)(tmp_i9 + 0x694) + 1;
  *(int *)(tmp_i9 + 0x694) = tmp_i3;
  tmp_u8 = GHIDRA_FIELD(g_complaintlimit, 12, 4);
  if (*(int *)(tmp_i9 + 0x5e8) == 0) {
    tmp_i5 = param_1 + -0x93e4a0 >> 9;
    local_8c = tmp_i5 * -0x55555555;
    StringToFilter(tmp_i5 * -0x5555390c + level + 0x63d,&local_64);
    if (tmp_u8 == tmp_i3 || tmp_u8 - tmp_i3 < 0) {
LAB_0006a7ed:
      tmp_u8 = 0;
      if (*(int *)(tmp_i9 + 0xc80) == 0) {
        tmp_u8 = 300;
      }
      trap_DropClient((tmp_i9 - level >> 2) * -0x66e64f79,"kicked after too many complaints.",tmp_u8);
      trap_SendServerCommand(local_8c,"complaint -1");
      return;
    }
    if (GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) != 0) {
      if ((int)GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) < 1) goto LAB_0006a7ed;
      if ((*(uint *)(tmp_i9 + 0x9a8) == 0) && (*(uint *)(tmp_i9 + 0x9a4) == 0)) {
        tmp_i3 = 0;
LAB_0006a8e3:
        tmp_i9 = tmp_i9 + tmp_i3 * 8;
        *(uint *)(tmp_i9 + 0x9a8) = local_60;
        *(uint *)(tmp_i9 + 0x9a4) = local_64;
      }
      else {
        tmp_u6 = local_64 & local_60;
        if ((*(uint *)(tmp_i9 + 0x9a4) & *(uint *)(tmp_i9 + 0x9a8)) != tmp_u6) {
          if (GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) == 1) goto LAB_0006a7ed;
          if ((*(uint *)(tmp_i9 + 0x9b0) == 0) && (*(uint *)(tmp_i9 + 0x9ac) == 0)) {
            tmp_i3 = 1;
            goto LAB_0006a8e3;
          }
          if ((*(uint *)(tmp_i9 + 0x9ac) & *(uint *)(tmp_i9 + 0x9b0)) != tmp_u6) {
            if (GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) == 2) goto LAB_0006a7ed;
            if ((*(uint *)(tmp_i9 + 0x9b8) == 0) && (*(uint *)(tmp_i9 + 0x9b4) == 0)) {
              tmp_i3 = 2;
              goto LAB_0006a8e3;
            }
            if (tmp_u6 != (*(uint *)(tmp_i9 + 0x9b4) & *(uint *)(tmp_i9 + 0x9b8))) {
              if (GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) == 3) goto LAB_0006a7ed;
              if ((*(uint *)(tmp_i9 + 0x9c0) == 0) && (*(uint *)(tmp_i9 + 0x9bc) == 0)) {
                tmp_i3 = 3;
                goto LAB_0006a8e3;
              }
              if (tmp_u6 != (*(uint *)(tmp_i9 + 0x9bc) & *(uint *)(tmp_i9 + 0x9c0))) {
                if (GHIDRA_FIELD(g_ipcomplaintlimit, 12, 4) == 4) goto LAB_0006a7ed;
                if ((*(uint *)(tmp_i9 + 0x9c8) == 0) && (*(uint *)(tmp_i9 + 0x9c4) == 0)) {
                  tmp_i3 = 4;
                  goto LAB_0006a8e3;
                }
                if (tmp_u6 != (*(uint *)(tmp_i9 + 0x9c4) & *(uint *)(tmp_i9 + 0x9c8)))
                goto LAB_0006a7ed;
              }
            }
          }
        }
      }
    }
  }
  else {
    local_8c = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  }
  tmp_u8 = va("cpm \"^1Warning^7: Complaint filed against you by %s^7 You have Lost XP.\n\"",
             *(int *)(param_1 + 400) + 0x5f8);
  trap_SendServerCommand(*(uint32_t *)(*(int *)(param_1 + 400) + 0x698),tmp_u8);
  trap_SendServerCommand(local_8c,"complaint -1");
  AddScore(g_entities + tmp_i10 * 0x600,0xfffffffd);
  G_LoseKillSkillPoints
            (g_entities + tmp_i10 * 0x600,*(uint32_t *)(param_1 + 0x1f0),
             *(uint32_t *)(param_1 + 0x1ec),*(int *)(param_1 + 0x1fc) != 0);
LAB_0006a5b2:
  *(uint32_t *)(*(int *)(param_1 + 400) + 0x69c) = 0xffffffff;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0x698) = 0xffffffff;
  return;
}

void Cmd_SetViewpos_f(int param_1)
{
  char *tmp_pc1;
  int tmp_i2;
  
  if (GHIDRA_FIELD(g_cheats, 12, 4) == 0) {
    tmp_pc1 = "print \"Cheats are not enabled on this server.\n\"";
  }
  else {
    tmp_i2 = trap_Argc();
    if (tmp_i2 == 5) {
      Cmd_SetViewpos_f_part_9();
      return;
    }
    tmp_pc1 = "print \"usage: setviewpos x y z yaw\n\"";
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc1);
  return;
}

void Cmd_Activate_f(int *param_1)
{
  float tmp_f1;
  uint8_t *tmp_pu2;
  bool tmp_b3;
  int tmp_i4;
  uint tmp_u5;
  uint32_t tmp_u6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  byte *tmp_pb10;
  byte *tmp_pb11;
  int tmp_i12;
  bool tmp_b13;
  bool tmp_b14;
  byte tmp_b15;
  long double tmp_l16;
  uint8_t *local_f0;
  uint local_e8;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  uint8_t local_a4 [12];
  float local_98;
  float local_94;
  float local_90;
  uint8_t local_8c [4];
  int local_88;
  byte local_60;
  int local_58;
  float local_54 [17];
  
  tmp_b15 = 0;
  tmp_i8 = param_1[100];
  if (param_1[0xda] == 0) {
    if ((((*(byte *)(tmp_i8 + 0x69) & 0x80) == 0) || ((*(byte *)((int)param_1 + 9) & 0x80) == 0)) ||
       (g_unk_02aa29a0 != 0)) {
      AngleVectors(tmp_i8 + 0xb0,&local_bc,&local_b0,local_a4);
      tmp_i8 = param_1[100];
      local_98 = *(float *)(tmp_i8 + 0x14);
      local_94 = *(float *)(tmp_i8 + 0x18);
      local_90 = (float)*(int *)(tmp_i8 + 0xbc) + *(float *)(tmp_i8 + 0x1c);
      tmp_f1 = *(float *)(tmp_i8 + 0x3c);
      if (tmp_f1 != 0.0) {
        local_98 = local_b0 * tmp_f1 + local_98;
        local_94 = local_ac * tmp_f1 + local_94;
        local_90 = tmp_f1 * local_a8 + local_90;
      }
      local_c8 = local_bc * 96.0 + local_98;
      local_c4 = local_b8 * 96.0 + local_94;
      local_c0 = local_b4 * 96.0 + local_90;
      trap_Trace(local_8c,&local_98,0,0,&local_c8,*param_1,0x6000081);
      if (((local_60 & 0x10) == 0) && (local_58 != 0x3fe)) {
        tmp_b3 = false;
        local_f0 = g_entities + local_58 * 0x600;
        if (*(int *)(g_entities + local_58 * 0x600 + 0x458) - 1U < 2) goto LAB_0006c66c;
LAB_0006c510:
        do {
          tmp_i8 = local_58;
          local_e8 = 1;
          if ((*(byte *)(param_1[100] + 0x5b4) & 0x10) == 0) {
            local_e8 = *(uint *)(param_1[100] + 0xc) & 1;
          }
          tmp_i9 = local_58 * 0x600;
          if (*(int *)(g_entities + tmp_i9 + 0x1a4) != 0) {
            *(uint *)(g_entities + tmp_i9 + 0x1b0) =
                 *(uint *)(g_entities + tmp_i9 + 0x1b0) & 0xffffffbf;
            tmp_i7 = *(int *)(g_entities + tmp_i9 + 4);
            if (tmp_i7 == 0xf) {
              if (*(int *)(param_1[100] + 3000) != 3) {
                tmp_u5 = 0;
                do {
                  *(uint32_t *)((int)local_54 + tmp_u5) = 0;
                  *(uint32_t *)((int)local_54 + tmp_u5 + 4) = 0;
                  tmp_u5 = tmp_u5 + 8;
                } while (tmp_u5 < 0x38);
                if (*(int *)(g_entities + local_58 * 0x600 + 0x2b4) == 0) {
                  return;
                }
                G_UseEntity(local_f0,param_1,0);
                return;
              }
            }
            else if (tmp_i7 == 2) {
              tmp_i8 = param_1[100];
              if (*(int *)(tmp_i8 + 3000) != 3) {
                tmp_u5 = 0;
                do {
                  *(uint32_t *)((int)local_54 + tmp_u5) = 0;
                  *(uint32_t *)((int)local_54 + tmp_u5 + 4) = 0;
                  tmp_u5 = tmp_u5 + 8;
                } while (tmp_u5 < 0x38);
                if (*(int *)(g_entities + local_58 * 0x600 + 0x2b0) == 0) {
                  return;
                }
                if (*(int *)(tmp_i8 + 0x66c) == 0) {
                  *(uint32_t *)(tmp_i8 + 0x66c) = 2;
                }
                *(uint32_t *)(g_entities + local_58 * 0x600 + 0x368) = 1;
                (**(void **)(g_entities + local_58 * 0x600 + 0x2b0))(local_f0,param_1,local_54);
                return;
              }
            }
            else {
              if ((((tmp_i7 == 4) && ((g_entities[tmp_i9 + 0x1a8] & 0x80) != 0)) &&
                  (g_unk_02aa29a4 == 0)) &&
                 (((tmp_i7 = BG_IsScopedWeapon(*(uint32_t *)(param_1[100] + 0xa4)), tmp_i7 == 0 &&
                   (*(int *)(g_entities + tmp_i9 + 0x444) == 0)) &&
                  ((0 < *(int *)(g_entities + tmp_i9 + 0x2c8) &&
                   ((0 < *(int *)(param_1[100] + 0xd0) && (*(int *)(param_1[100] + 0x30) == 0)))))))
                 ) {
                if (((int)GHIDRA_FIELD(n_tankMountDelay, 12, 4) < 1) ||
                   ((param_1[0x17d] < 1 || (param_1[0x17d] <= g_unk_00abe908)))) {
                  G_Script_ScriptEvent(local_f0,&g_unk_0024c710,"mount");
                  tmp_i8 = tmp_i8 * 0x600;
                  param_1[0x110] = *(int *)(g_entities + tmp_i8 + 0x21c);
                  Q_strncpyz(param_1 + 0x100,"tag_player",0x40);
                  param_1[0x134] = *(int *)(param_1[100] + 0x2c);
                  *(uint32_t *)(param_1[100] + 0x2c) = *(uint32_t *)(g_entities + tmp_i8 + 0x4d0)
                  ;
                  *(uint32_t *)(param_1[100] + 0x51c) =
                       *(uint32_t *)(g_entities + tmp_i8 + 0x4d4);
                  param_1[0x111] = (int)local_f0;
                  *(int **)(g_entities + tmp_i8 + 0x444) = param_1;
                  G_ProcessTagConnect(param_1,1);
                  return;
                }
                tmp_u6 = va("cp \"You must wait %d seconds before you can mount a tank again.^7\" 1",
                           GHIDRA_FIELD(n_tankMountDelay, 12, 4));
                trap_SendServerCommand(((int)(param_1 + -0x24f928) >> 9) * -0x55555555,tmp_u6);
              }
              tmp_i9 = G_EmplacedGunIsMountable(local_f0,param_1);
              if (tmp_i9 != 0) {
                tmp_i8 = tmp_i8 * 0x600;
                tmp_i12 = param_1[0x2b] * 0x54dc + level;
                AngleVectors(tmp_i8 + 0x93e4dc,local_54,0,0);
                tmp_f1 = *(float *)(g_entities + tmp_i8 + 0x16c);
                param_1[0xcc] = (int)(local_54[0] * -36.0 + *(float *)(g_entities + tmp_i8 + 0x168));
                param_1[0xcd] = (int)(local_54[1] * -36.0 + tmp_f1);
                param_1[0xce] = param_1[0x5c];
                tmp_i9 = vec3_origin;
                *(int *)(param_1[100] + 0x20) = vec3_origin;
                tmp_i7 = g_unk_008277c4;
                *(int *)(param_1[100] + 0x24) = g_unk_008277c4;
                tmp_i4 = g_unk_008277c8;
                *(int *)(param_1[100] + 0x28) = g_unk_008277c8;
                param_1[9] = tmp_i9;
                param_1[10] = tmp_i7;
                param_1[0xb] = tmp_i4;
                *(uint32_t *)(g_entities + tmp_i8 + 0x368) = 1;
                param_1[0xda] = 1;
                *(int *)(g_entities + tmp_i8 + 0x180) = *param_1;
                *(uint32_t *)(g_entities + tmp_i8 + 0x330) =
                     *(uint32_t *)(g_entities + tmp_i8 + 0x74);
                *(uint32_t *)(g_entities + tmp_i8 + 0x334) =
                     *(uint32_t *)(g_entities + tmp_i8 + 0x78);
                *(uint32_t *)(g_entities + tmp_i8 + 0x338) =
                     *(uint32_t *)(g_entities + tmp_i8 + 0x7c);
                *(int *)(g_entities + tmp_i8 + 0x8c) = *param_1;
                *(uint32_t *)(tmp_i12 + 0x52bc) = *(uint32_t *)(g_entities + tmp_i8 + 0x36c);
                *(uint32_t *)(tmp_i12 + 0x52b8) = *(uint32_t *)(g_entities + tmp_i8 + 0x370);
                tmp_u6 = *(uint32_t *)(g_entities + tmp_i8 + 0x74);
                *(uint32_t *)(tmp_i12 + 0x52c0) = tmp_u6;
                *(uint32_t *)(tmp_i12 + 0x52c4) = *(uint32_t *)(g_entities + tmp_i8 + 0x78);
                *(uint32_t *)(tmp_i12 + 0x52c8) = *(uint32_t *)(g_entities + tmp_i8 + 0x7c);
                tmp_l16 = (long double)AngleNormalize180(tmp_u6);
                *(float *)(tmp_i12 + 0x52c0) = (float)tmp_l16;
                tmp_l16 = (long double)AngleNormalize180(*(uint32_t *)(tmp_i12 + 0x52c4));
                *(float *)(tmp_i12 + 0x52c4) = (float)tmp_l16;
                tmp_l16 = (long double)AngleNormalize180(*(uint32_t *)(tmp_i12 + 0x52c8));
                *(float *)(tmp_i12 + 0x52c8) = (float)tmp_l16;
                param_1[0x134] = *(int *)(param_1[100] + 0x2c);
                *(uint32_t *)(param_1[100] + 0x2c) = *(uint32_t *)(g_entities + tmp_i8 + 0x4d0);
                *(uint32_t *)(param_1[100] + 0x51c) = *(uint32_t *)(g_entities + tmp_i8 + 0x4d4);
                G_UseTargets(local_f0,param_1);
                return;
              }
              tmp_i9 = tmp_i8 * 0x600;
              tmp_pu2 = *(uint8_t **)(g_entities + tmp_i9 + 0x5c0);
              if ((tmp_pu2 == (uint8_t *)0x3bf8a) || (tmp_pu2 == (uint8_t *)0x1cce6)) {
                if (local_e8 != 0) {
                  *(uint *)(g_entities + tmp_i8 * 0x600 + 0x1b0) =
                       *(uint *)(g_entities + tmp_i8 * 0x600 + 0x1b0) | 0x40;
                }
                G_TryDoor(local_f0,param_1,param_1);
                return;
              }
              tmp_b13 = tmp_pu2 < &g_unk_00042729;
              if (tmp_pu2 == &g_unk_00042729) {
                if (*(int *)(g_entities + tmp_i9 + 0x2e4) == *(int *)(param_1[100] + 3000)) {
                  return;
                }
                *(int *)(g_entities + tmp_i9 + 0x2c8) = *(int *)(g_entities + tmp_i9 + 0x2c8) + 1;
                return;
              }
              tmp_i7 = 0xc;
              tmp_b14 = false;
              tmp_pb10 = *(byte **)(g_entities + tmp_i9 + 0x1a4);
              tmp_pb11 = (byte *)"func_button";
              do {
                if (tmp_i7 == 0) break;
                tmp_i7 = tmp_i7 + -1;
                tmp_b13 = *tmp_pb10 < *tmp_pb11;
                tmp_b14 = *tmp_pb10 == *tmp_pb11;
                tmp_pb10 = tmp_pb10 + (uint)tmp_b15 * -2 + 1;
                tmp_pb11 = tmp_pb11 + (uint)tmp_b15 * -2 + 1;
              } while (tmp_b14);
              if (((((!tmp_b13 && !tmp_b14) == tmp_b13) && (*(int *)(g_entities + tmp_i9 + 0x30) == 0))
                  && (*(int *)(g_entities + tmp_i9 + 0xc) == 0)) &&
                 (*(int *)(g_entities + tmp_i9 + 0x368) == 0)) {
                Use_BinaryMover(local_f0,param_1,param_1);
                *(uint32_t *)(g_entities + tmp_i9 + 0x368) = 1;
                return;
              }
              if (tmp_pu2 == (uint8_t *)0x3f73d) {
                if (local_e8 != 0) {
                  *(uint *)(g_entities + tmp_i8 * 0x600 + 0x1b0) =
                       *(uint *)(g_entities + tmp_i8 * 0x600 + 0x1b0) | 0x40;
                }
LAB_0006cd22:
                G_UseEntity(local_f0,param_1,param_1);
                return;
              }
              tmp_i8 = 0x11;
              tmp_b13 = false;
              tmp_pb10 = *(byte **)(g_entities + tmp_i9 + 0x1a4);
              tmp_pb11 = (byte *)"props_footlocker";
              do {
                if (tmp_i8 == 0) break;
                tmp_i8 = tmp_i8 + -1;
                tmp_b13 = *tmp_pb10 == *tmp_pb11;
                tmp_pb10 = tmp_pb10 + (uint)tmp_b15 * -2 + 1;
                tmp_pb11 = tmp_pb11 + (uint)tmp_b15 * -2 + 1;
              } while (tmp_b13);
              if (tmp_b13) goto LAB_0006cd22;
            }
          }
          if (tmp_b3) {
            return;
          }
LAB_0006c66c:
          trap_Trace(local_8c,&local_98,0,0,&local_c8,*param_1,0x46000081);
          if ((local_60 & 0x10) != 0) {
            return;
          }
          if (local_58 == 0x3fe) {
            return;
          }
          local_f0 = g_entities + local_58 * 0x600;
          tmp_b3 = true;
          if (*(int *)(g_entities + local_58 * 0x600 + 0x458) - 1U < 2) {
            return;
          }
        } while( true );
      }
      trap_Trace(local_8c,&local_98,0,0,&local_c8,*param_1,0x46000081);
      if (((local_60 & 0x10) == 0) && (local_58 != 0x3fe)) {
        tmp_b3 = true;
        local_f0 = g_entities + local_58 * 0x600;
        if (1 < *(int *)(g_entities + local_58 * 0x600 + 0x458) - 1U) goto LAB_0006c510;
      }
    }
    else {
      G_LeaveTank(param_1,1,1);
    }
  }
  else if (*(int *)(tmp_i8 + 0x140) == 0) {
    param_1[0xda] = 0;
  }
  else {
    trap_Trace(local_8c,param_1 + 0x5a,param_1 + 0x4d,param_1 + 0x50,param_1 + 0x5a,*param_1,
               &g_unk_02010001);
    if (local_88 != 0) {
      *(int *)(param_1[100] + 0x14) = param_1[0xcc];
      *(int *)(param_1[100] + 0x18) = param_1[0xcd];
      *(int *)(param_1[100] + 0x1c) = param_1[0xce];
      param_1[0x53] = 0x4000000;
      param_1[0x5a] = param_1[0xcc];
      param_1[0x5b] = param_1[0xcd];
      param_1[0x5c] = param_1[0xce];
    }
    tmp_i8 = MG42Entities;
    *(uint *)(param_1[100] + 0x68) = *(uint *)(param_1[100] + 0x68) & 0xffffffdf;
    *(uint32_t *)(param_1[100] + 0x140) = 0;
    param_1[0xda] = 0;
    if (0 < tmp_i8) {
      tmp_i9 = g_unk_0087a9c4;
      if (*(int *)(g_unk_0087a9c4 + 0x180) != *param_1) {
        tmp_i7 = 0;
        do {
          tmp_i7 = tmp_i7 + 1;
          if (tmp_i7 == tmp_i8) goto LAB_0006ccf0;
          tmp_i9 = (&g_unk_0087a9c4)[tmp_i7];
        } while (*(int *)(tmp_i9 + 0x180) != *param_1);
      }
      *(uint32_t *)(tmp_i9 + 0x4d4) = *(uint32_t *)(param_1[100] + 0x51c);
      *(uint32_t *)(tmp_i9 + 0x4d0) = *(uint32_t *)(param_1[100] + 0x2c);
    }
LAB_0006ccf0:
    *(int *)(param_1[100] + 0x2c) = param_1[0x134];
  }
  return;
}

void Cmd_Activate2_f(uint32_t *param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint8_t *tmp_pu6;
  long double tmp_l7;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  uint8_t local_84 [12];
  uint8_t local_78 [12];
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  uint32_t local_58;
  uint8_t local_54 [52];
  int local_20;
  
  if (((0 < (int)param_1[0xb2]) && (tmp_i5 = param_1[100], (*(byte *)(tmp_i5 + 0x6a) & 0x80) == 0)) &&
     ((param_1[0x3a] & 0xfffffffb) != 0x2a)) {
    if (GHIDRA_FIELD(g_canisterKick, 12, 4) != 0) {
      G_CanisterKick(param_1);
      tmp_i5 = param_1[100];
    }
    AngleVectors(tmp_i5 + 0xb0,&local_90,local_84,local_78);
    CalcMuzzlePointForActivate(param_1,&local_90,local_84,local_78,&local_6c,0);
    local_9c = local_90 * 96.0 + local_6c;
    local_98 = local_8c * 96.0 + local_68;
    local_94 = local_88 * 96.0 + local_64;
    trap_Trace(local_54,&local_6c,0,0,&local_9c,*param_1,0x4000000);
    if (-1 < local_20) {
      tmp_i5 = local_20 * 0x600;
      tmp_pi1 = (int *)(g_entities + tmp_i5 + 400);
      if (*tmp_pi1 != 0) {
        if (GHIDRA_FIELD(g_dragCorpse, 12, 4) == 0) {
          return;
        }
        local_60 = (float)param_1[0x5a] - *(float *)(g_entities + tmp_i5 + 0x168);
        local_5c = (float)param_1[0x5b] - *(float *)(g_entities + tmp_i5 + 0x16c);
        local_58 = 0;
        tmp_l7 = (long double)VectorNormalize(&local_60);
        if ((long double)85.0 < tmp_l7) {
          return;
        }
        if (tmp_l7 < (long double)40.0) {
          return;
        }
        tmp_i2 = *tmp_pi1;
        tmp_f3 = local_60 * 110.0 - *(float *)(tmp_i2 + 0x20);
        tmp_f4 = local_5c * 110.0 - *(float *)(tmp_i2 + 0x24);
        *(float *)(g_entities + tmp_i5 + 0x24) = *(float *)(g_entities + tmp_i5 + 0x24) + tmp_f3;
        *(float *)(g_entities + tmp_i5 + 0x28) = *(float *)(g_entities + tmp_i5 + 0x28) + tmp_f4;
        *(float *)(g_entities + tmp_i5 + 0x2c) = *(float *)(g_entities + tmp_i5 + 0x2c) + 0.0;
        *(float *)(tmp_i2 + 0x20) = tmp_f3 + *(float *)(tmp_i2 + 0x20);
        *(float *)(*tmp_pi1 + 0x24) = tmp_f4 + *(float *)(*tmp_pi1 + 0x24);
        *(float *)(*tmp_pi1 + 0x28) = *(float *)(*tmp_pi1 + 0x28) + 0.0;
        return;
      }
    }
    if ((((g_OmniBotFlags[0xc] & 0x40) != 0) || ((*(byte *)(param_1 + 0x4a) & 8) == 0)) &&
       (trap_Trace(local_54,&local_6c,0,0,&local_9c,*param_1,0x2000000), -1 < local_20)) {
      tmp_i5 = local_20 * 0x600;
      tmp_pi1 = (int *)(g_entities + tmp_i5 + 400);
      if (*tmp_pi1 != 0) {
        if ((*(byte *)(*tmp_pi1 + 0x6a) & 0x80) == 0) {
          tmp_pu6 = g_entities + tmp_i5;
          tmp_i5 = OnSameTeam(param_1,tmp_pu6);
          if (((tmp_i5 == 0) && (tmp_i5 = param_1[100], *(int *)(tmp_i5 + 0xbc8) == 4)) &&
             (((*(byte *)(tmp_i5 + 0xee8) & 0x10) != 0 &&
              ((((g_misc[0xc] & 0x80) != 0 && ((*(byte *)(*tmp_pi1 + 0x6a) & 1) == 0)) &&
               (AnglesSubtract(*tmp_pi1 + 0xb0,tmp_i5 + 0xb0,&local_60), ABS(local_5c) < 50.0)))))) {
            G_UniformSteal_2(param_1,tmp_pu6);
            return;
          }
          G_PushPlayer(param_1,tmp_pu6);
          return;
        }
        if (GHIDRA_FIELD(g_dragCorpse, 12, 4) == 0) {
          return;
        }
        local_60 = (float)param_1[0x5a] - *(float *)(g_entities + tmp_i5 + 0x168);
        local_5c = (float)param_1[0x5b] - *(float *)(g_entities + tmp_i5 + 0x16c);
        local_58 = 0;
        tmp_l7 = (long double)VectorNormalize(&local_60);
        if ((long double)85.0 < tmp_l7) {
          return;
        }
        if (tmp_l7 < (long double)40.0) {
          return;
        }
        tmp_i2 = *tmp_pi1;
        tmp_f3 = local_60 * 110.0 - *(float *)(tmp_i2 + 0x20);
        tmp_f4 = local_5c * 110.0 - *(float *)(tmp_i2 + 0x24);
        *(float *)(g_entities + tmp_i5 + 0x24) = *(float *)(g_entities + tmp_i5 + 0x24) + tmp_f3;
        *(float *)(g_entities + tmp_i5 + 0x28) = *(float *)(g_entities + tmp_i5 + 0x28) + tmp_f4;
        *(float *)(g_entities + tmp_i5 + 0x2c) = *(float *)(g_entities + tmp_i5 + 0x2c) + 0.0;
        *(float *)(tmp_i2 + 0x20) = tmp_f3 + *(float *)(tmp_i2 + 0x20);
        *(float *)(*tmp_pi1 + 0x24) = tmp_f4 + *(float *)(*tmp_pi1 + 0x24);
        *(float *)(*tmp_pi1 + 0x28) = *(float *)(*tmp_pi1 + 0x28) + 0.0;
        return;
      }
    }
    trap_Trace(local_54,&local_6c,0,0,&local_9c,*param_1,0x6000001);
    if (-1 < local_20) {
      local_20 = local_20 * 0x600;
      if (((*(int *)(g_entities + local_20 + 4) == 0x26) &&
          (*(int *)(g_entities + local_20 + 0xa4) != 0)) &&
         (*(int *)(g_entities + local_20 + 0x58) == 0)) {
        tmp_i5 = param_1[100];
        if ((*(int *)(g_entities + local_20 + 0xa4) == *(int *)(tmp_i5 + 3000)) &&
           (*(int *)(tmp_i5 + 0xbc8) != *(int *)(g_entities + local_20 + 0xa8))) {
          G_ClassSteal(param_1,g_entities + local_20);
        }
        else if (*(int *)(tmp_i5 + 0xbc8) == 4) {
          G_UniformSteal(param_1,g_entities + local_20);
        }
      }
    }
  }
  return;
}

void Cmd_Team_f(int param_1)
{
  int tmp_i1;
  long tmp_l2;
  long tmp_l3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  int *tmp_pi6;
  int tmp_i7;
  long tmp_l8;
  bool tmp_b9;
  char local_428 [4];
  char local_424 [4];
  char local_420 [4];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x6e469;
  tmp_i1 = trap_Argc();
  if (tmp_i1 < 2) {
    tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 3000);
    if (tmp_i1 == 2) {
      tmp_pc4 = "Allies";
    }
    else if (tmp_i1 == 3) {
      tmp_pc4 = "Spectator";
    }
    else if (tmp_i1 == 1) {
      tmp_pc4 = "Axis";
    }
    else {
      tmp_pc4 = "Free";
    }
    tmp_u5 = va("print \"%s team\n\"",tmp_pc4);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
    return;
  }
  trap_Argv(1,local_41c,0x400);
  trap_Argv(2,local_428,4);
  trap_Argv(3,local_424,4);
  trap_Argv(4,local_420,4);
  tmp_l2 = strtol(local_424,(char **)0x0,10);
  tmp_l3 = strtol(local_420,(char **)0x0,10);
  if (local_428[0] != '\0') {
    tmp_i1 = *(int *)(param_1 + 400);
    tmp_l8 = strtol(local_428,(char **)0x0,10);
    *(long *)(tmp_i1 + 0xbd8) = tmp_l8;
    tmp_i1 = G_IsClassDisabled(param_1,*(uint32_t *)(*(int *)(param_1 + 400) + 0xbd8),1);
    if (tmp_i1 != 0) {
      tmp_i1 = 0;
      while (tmp_i7 = G_IsClassDisabled(param_1,tmp_i1,1), tmp_i7 != 0) {
        tmp_i1 = tmp_i1 + 1;
        if (tmp_i1 == 5) {
          SetTeam(param_1,&g_unk_0024e6ea,1,0xffffffff,0xffffffff,0);
          return;
        }
      }
      tmp_i7 = *(int *)(param_1 + 400);
      *(int *)(tmp_i7 + 0xbc8) = tmp_i1;
      *(int *)(tmp_i7 + 0xbd8) = tmp_i1;
    }
  }
  if (4 < *(uint *)(*(int *)(param_1 + 400) + 0xbd8)) {
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xbd8) = 0;
  }
  tmp_i1 = SetTeam(param_1,local_41c,0,tmp_l2,tmp_l3,1);
  if (tmp_i1 != 0) {
    return;
  }
  if (g_unk_00abe938 < 1) {
    g_unk_02b9a450 = 0;
    g_unk_02b9a44c = 0;
  }
  else {
    tmp_pi6 = &g_unk_00abe944;
    g_unk_02b9a450 = 0;
    g_unk_02b9a44c = 0;
    do {
      while (tmp_i1 = *(int *)(level + 3000 + *tmp_pi6 * 0x54dc), tmp_i1 == 1) {
        tmp_pi6 = tmp_pi6 + 1;
        g_unk_02b9a44c = g_unk_02b9a44c + 1;
        if (tmp_pi6 == &g_unk_00abe944 + g_unk_00abe938) goto LAB_0006e684;
      }
      tmp_pi6 = tmp_pi6 + 1;
      g_unk_02b9a450 = g_unk_02b9a450 + (uint)(tmp_i1 == 2);
    } while (tmp_pi6 != &g_unk_00abe944 + g_unk_00abe938);
  }
LAB_0006e684:
  tmp_b9 = tmp_l3 == *(int *)(*(int *)(param_1 + 400) + 0xbe0);
  if (!tmp_b9) {
    *(long *)(*(int *)(param_1 + 400) + 0xbe0) = tmp_l3;
  }
  tmp_i7 = G_IsWeaponDisabled(param_1,tmp_l2,0,0);
  tmp_i1 = *(int *)(param_1 + 400);
  if (tmp_i7 == 0) {
    if (tmp_l2 != *(int *)(tmp_i1 + 0xbdc)) {
      *(long *)(tmp_i1 + 0xbdc) = tmp_l2;
      goto LAB_0006e70c;
    }
  }
  else if (*(int *)(tmp_i1 + 0xbdc) != 0) {
    *(uint32_t *)(tmp_i1 + 0xbdc) = 0;
    goto LAB_0006e70c;
  }
  if (tmp_b9) {
    return;
  }
LAB_0006e70c:
  ClientUserinfoChanged((param_1 + -0x93e4a0 >> 9) * -0x55555555);
  return;
}

void Cmd_SetClass_f(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  long tmp_l3;
  long tmp_l4;
  int *tmp_pi5;
  int tmp_i6;
  long tmp_l7;
  char *tmp_pc8;
  bool tmp_b9;
  char local_428 [4];
  char local_424 [4];
  char local_420 [4];
  uint32_t local_41c;
  ushort local_418;
  uint8_t local_416;
  uint32_t uStack_14;
  
  uStack_14 = 0x6e889;
  tmp_i1 = trap_Argc();
  if (tmp_i1 < 2) {
    switch(*(uint32_t *)(*(int *)(param_1 + 400) + 0xbd8)) {
    case 0:
      tmp_pc8 = "Soldier";
      break;
    case 1:
      tmp_pc8 = "Medic";
      break;
    case 2:
      tmp_pc8 = "Engineer";
      break;
    case 3:
      tmp_pc8 = "Field Ops";
      break;
    case 4:
      tmp_pc8 = "Covert Ops";
      break;
    default:
      tmp_pc8 = "^1Unknown!";
    }
    tmp_u2 = va("print \"%s class\n\"",tmp_pc8);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
    return;
  }
  tmp_i1 = *(int *)(*(int *)(param_1 + 400) + 3000);
  if (tmp_i1 == 2) {
    local_41c = 0x696c6c41;
    local_418 = 0x7365;
    local_416 = 0;
  }
  else if (tmp_i1 == 1) {
    local_41c = 0x73697841;
    local_418 = local_418 & 0xff00;
  }
  else {
    tmp_u2 = va("print \"^3Cannot pick a class unless you\'re on a team!\n\"");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  }
  trap_Argv(1,local_428,4);
  trap_Argv(2,local_424,4);
  trap_Argv(3,local_420,4);
  tmp_l3 = strtol(local_424,(char **)0x0,10);
  tmp_l4 = strtol(local_420,(char **)0x0,10);
  if (((local_428[0] != '\0') && (tmp_l7 = strtol(local_428,(char **)0x0,10), -1 < tmp_l7)) &&
     (tmp_l7 = strtol(local_428,(char **)0x0,10), tmp_l7 < 5)) {
    tmp_i1 = *(int *)(param_1 + 400);
    tmp_l7 = strtol(local_428,(char **)0x0,10);
    *(long *)(tmp_i1 + 0xbd8) = tmp_l7;
  }
  tmp_i1 = SetTeam(param_1,&local_41c,0,tmp_l3,tmp_l4,1);
  if (tmp_i1 != 0) {
    return;
  }
  if (g_unk_00abe938 < 1) {
    g_unk_02b9a450 = 0;
    g_unk_02b9a44c = 0;
  }
  else {
    tmp_pi5 = &g_unk_00abe944;
    g_unk_02b9a450 = 0;
    g_unk_02b9a44c = 0;
    do {
      while (tmp_i1 = *(int *)(level + 3000 + *tmp_pi5 * 0x54dc), tmp_i1 == 1) {
        tmp_pi5 = tmp_pi5 + 1;
        g_unk_02b9a44c = g_unk_02b9a44c + 1;
        if (tmp_pi5 == &g_unk_00abe944 + g_unk_00abe938) goto LAB_0006ea64;
      }
      tmp_pi5 = tmp_pi5 + 1;
      g_unk_02b9a450 = g_unk_02b9a450 + (uint)(tmp_i1 == 2);
    } while (tmp_pi5 != &g_unk_00abe944 + g_unk_00abe938);
  }
LAB_0006ea64:
  tmp_b9 = tmp_l4 == *(int *)(*(int *)(param_1 + 400) + 0xbe0);
  if (!tmp_b9) {
    *(long *)(*(int *)(param_1 + 400) + 0xbe0) = tmp_l4;
  }
  tmp_i6 = G_IsWeaponDisabled(param_1,tmp_l3,0,0);
  tmp_i1 = *(int *)(param_1 + 400);
  if (tmp_i6 == 0) {
    if (tmp_l3 != *(int *)(tmp_i1 + 0xbdc)) {
      *(long *)(tmp_i1 + 0xbdc) = tmp_l3;
      goto LAB_0006eaec;
    }
  }
  else if (*(int *)(tmp_i1 + 0xbdc) != 0) {
    *(uint32_t *)(tmp_i1 + 0xbdc) = 0;
    goto LAB_0006eaec;
  }
  if (tmp_b9) {
    return;
  }
LAB_0006eaec:
  ClientUserinfoChanged((param_1 + -0x93e4a0 >> 9) * -0x55555555);
  return;
}

void Cmd_FollowCycle_f(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i4 = *(int *)(param_1 + 400);
  if ((GHIDRA_FIELD(g_gametype, 12, 4) == 8) && (*(int *)(tmp_i4 + 3000) != 3)) {
    return;
  }
  if (g_unk_00abe938 == 1) {
    *(uint32_t *)(tmp_i4 + 0xbc0) = 1;
    return;
  }
  if ((*(int *)(tmp_i4 + 0xbc0) == 0) && ((*(byte *)(tmp_i4 + 0xd) & 0x40) == 0)) {
    SetTeam(param_1,"spectator",0,0xffffffff,0xffffffff,0);
  }
  if ((param_2 + 1U & 0xfffffffd) != 0) {
    G_Error("Cmd_FollowCycle_f: bad dir %i",param_2);
  }
  tmp_i4 = *(int *)(*(int *)(param_1 + 400) + 0xbc4);
  tmp_i3 = 0;
  if (-1 < tmp_i4) {
    tmp_i3 = tmp_i4;
  }
  do {
    tmp_i4 = tmp_i4 + param_2;
    if (tmp_i4 < g_unk_00abe900) {
      if (tmp_i4 < 0) {
        tmp_i4 = g_unk_00abe900 + -1;
      }
      tmp_i1 = tmp_i4 * 0x54dc + level;
      tmp_i2 = *(int *)(tmp_i1 + 0x5ac);
    }
    else {
      tmp_i4 = 0;
      tmp_i2 = *(int *)(level + 0x5ac);
      tmp_i1 = level;
    }
    if ((tmp_i2 == 2) && (tmp_i2 = *(int *)(tmp_i1 + 3000), tmp_i2 != 3)) {
      if ((*(byte *)(*(int *)(param_1 + 400) + 0xd) & 0x40) == 0) {
        if ((*(byte *)(tmp_i1 + 0xd) & 0x40) == 0) goto LAB_0006ed5f;
      }
      else if (((*(byte *)(tmp_i1 + 0xd) & 0x40) == 0) &&
              (tmp_i2 == *(int *)(*(int *)(param_1 + 400) + 3000))) {
LAB_0006ed5f:
        tmp_i2 = G_desiredFollow(param_1,tmp_i2);
        if (tmp_i2 != 0) {
          *(int *)(*(int *)(param_1 + 400) + 0xbc4) = tmp_i4;
          *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc0) = 2;
          return;
        }
      }
    }
    if (tmp_i4 == tmp_i3) {
      return;
    }
  } while( true );
}

void Cmd_Follow_f(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  int tmp_i6;
  int tmp_i7;
  char *tmp_pc8;
  uint tmp_u9;
  bool tmp_b10;
  byte tmp_b11;
  int local_51c [64];
  uint32_t local_41c;
  uint32_t local_418;
  uint32_t local_414;
  
  tmp_b11 = 0;
  tmp_i3 = trap_Argc();
  if (tmp_i3 != 2) {
    tmp_i3 = *(int *)(param_1 + 400);
    if (*(int *)(tmp_i3 + 0xbc0) != 2) {
      return;
    }
    if (*(int *)(tmp_i3 + 3000) != 3) {
      *(uint32_t *)(tmp_i3 + 0xbc0) = 1;
      *(int *)(*(int *)(param_1 + 400) + 0xa0) = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
      return;
    }
    tmp_u4 = *(uint32_t *)(tmp_i3 + 0x14);
    tmp_u1 = *(uint32_t *)(tmp_i3 + 0x18);
    tmp_u2 = *(uint32_t *)(tmp_i3 + 0x1c);
    local_41c = *(uint32_t *)(tmp_i3 + 0xb0);
    local_418 = *(uint32_t *)(tmp_i3 + 0xb4);
    local_414 = *(uint32_t *)(tmp_i3 + 0xb8);
    SetTeam(param_1,&g_unk_0024e6ea,1,0xffffffff,0xffffffff,0);
    *(uint32_t *)(tmp_i3 + 0x14) = tmp_u4;
    *(uint32_t *)(tmp_i3 + 0x18) = tmp_u1;
    *(uint32_t *)(tmp_i3 + 0x1c) = tmp_u2;
    SetClientViewAngle(param_1,&local_41c);
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc0) = 1;
    return;
  }
  if ((1 < *(int *)(*(int *)(param_1 + 400) + 3000) - 1U) ||
     (tmp_pc5 = "print \"Can\'t follow while not in limbo if on a team!\n\"",
     (*(byte *)(*(int *)(param_1 + 400) + 0xd) & 0x40) != 0)) {
    trap_Argv(1,&local_41c,0x400);
    tmp_i3 = ClientNumbersFromString(&local_41c,local_51c);
    if (tmp_i3 < 2) {
      if (local_51c[0] == -1) {
        tmp_i3 = 7;
        tmp_b10 = true;
        tmp_pc5 = (char *)&local_41c;
        tmp_pc8 = "allies";
        do {
          if (tmp_i3 == 0) break;
          tmp_i3 = tmp_i3 + -1;
          tmp_b10 = *tmp_pc5 == *tmp_pc8;
          tmp_pc5 = tmp_pc5 + (uint)tmp_b11 * -2 + 1;
          tmp_pc8 = tmp_pc8 + (uint)tmp_b11 * -2 + 1;
        } while (tmp_b10);
        if (tmp_b10) {
          tmp_i3 = 2;
          tmp_u9 = 2;
        }
        else {
          tmp_i3 = 5;
          tmp_b10 = false;
          tmp_pc5 = (char *)&local_41c;
          tmp_pc8 = "axis";
          do {
            if (tmp_i3 == 0) break;
            tmp_i3 = tmp_i3 + -1;
            tmp_b10 = *tmp_pc5 == *tmp_pc8;
            tmp_pc5 = tmp_pc5 + (uint)tmp_b11 * -2 + 1;
            tmp_pc8 = tmp_pc8 + (uint)tmp_b11 * -2 + 1;
          } while (tmp_b10);
          if (!tmp_b10) {
            return;
          }
          tmp_i3 = 1;
          tmp_u9 = 1;
        }
        tmp_i7 = *(int *)(*(int *)(param_1 + 400) + 3000);
        if ((1 < tmp_i7 - 1U) || (tmp_i7 == tmp_i3)) {
          tmp_i6 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
          tmp_i7 = TeamCount(tmp_i6,tmp_u9);
          if (tmp_i7 == 0) {
            tmp_pc5 = "is";
            if (*(int *)(*(int *)(param_1 + 400) + 3000) == tmp_i3) {
              tmp_pc5 = "would be";
            }
            tmp_u4 = va("print \"The %s team %s empty!  Follow command ignored.\n\"",
                       *(uint32_t *)(aTeams + tmp_u9 * 4),tmp_pc5);
            trap_SendServerCommand(tmp_i6,tmp_u4);
            return;
          }
          tmp_i3 = *(int *)(param_1 + 400);
          if (*(uint *)(tmp_i3 + 0xc8c) == tmp_u9) {
            *(uint32_t *)(tmp_i3 + 0xc8c) = 0;
            tmp_u4 = *(uint32_t *)(aTeams + tmp_u9 * 4);
            tmp_pc5 = "print \"%s team spectating is now disabled.\n\"";
          }
          else {
            if ((*(int *)(teamInfo + tmp_u9 * 0x10) == 0) ||
               ((*(uint *)(tmp_i3 + 0xc88) & tmp_u9) != 0)) {
              *(uint *)(tmp_i3 + 0xc8c) = tmp_u9;
              tmp_u4 = va("print \"Spectator follow is now locked on the %s team.\n\"",
                         *(uint32_t *)(aTeams + tmp_u9 * 4));
              trap_SendServerCommand(tmp_i6,tmp_u4);
              Cmd_FollowCycle_f(param_1,1);
              return;
            }
            tmp_u4 = *(uint32_t *)(aTeams + tmp_u9 * 4);
            tmp_pc5 = "print \"Sorry, the %s team is locked from spectators.\n\"";
          }
          tmp_u4 = va(tmp_pc5,tmp_u4);
          trap_SendServerCommand(tmp_i6,tmp_u4);
          return;
        }
      }
      else {
        tmp_i7 = local_51c[0] * 0x54dc;
        tmp_i3 = *(int *)(*(int *)(param_1 + 400) + 3000);
        if ((1 < tmp_i3 - 1U) || (tmp_i3 == *(int *)(tmp_i7 + level + 3000))) {
          tmp_i3 = tmp_i7 + level;
          if (*(int *)(param_1 + 400) == tmp_i3) {
            return;
          }
          if (*(int *)(tmp_i3 + 3000) == 3) {
            return;
          }
          if ((*(byte *)(tmp_i3 + 0xd) & 0x40) != 0) {
            return;
          }
          tmp_i3 = G_allowFollow(param_1,*(int *)(tmp_i3 + 3000));
          if (tmp_i3 != 0) {
            *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc0) = 2;
            *(int *)(*(int *)(param_1 + 400) + 0xbc4) = local_51c[0];
            return;
          }
          tmp_pc5 = (char *)va("print \"Sorry, the %s team is locked from spectators.\n\"",
                              *(uint32_t *)(aTeams + *(int *)(level + 3000 + tmp_i7) * 4));
          goto LAB_0006ef23;
        }
      }
      tmp_pc5 = "print \"Can\'t follow a player on an enemy team!\n\"";
    }
    else {
      tmp_pc5 = "print \"Partial Name Matches more than 1 Player.\n\"";
    }
  }
LAB_0006ef23:
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc5);
  return;
}

void Cmd_SetSpawnPoint_f_part_17(int param_1)
{
  int *tmp_pi1;
  uint tmp_u2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x6f335;
  trap_Argv(1,local_41c,0x400);
  tmp_u2 = strtol(local_41c,(char **)0x0,10);
  tmp_i6 = *(int *)(param_1 + 400);
  if (tmp_i6 != 0) {
    if (tmp_u2 < 0x10) {
      *(uint *)(tmp_i6 + 0xbd4) = tmp_u2;
    }
    else if (tmp_u2 != 0xfffffc19) {
      *(uint32_t *)(tmp_i6 + 0xbd4) = 0;
    }
    G_UpdateSpawnCounts();
  }
  if (0 < g_unk_02aa2ec8) {
    if ((tmp_u2 == *(int *)(g_entities + g_unk_02aa29cc * 0x600 + 0x2e4) - 0x272U) &&
       (g_unk_02aa29e8 != 0)) {
      tmp_i6 = 0;
    }
    else {
      tmp_i6 = 0;
      tmp_pi1 = &g_unk_02aa29f4;
      do {
        tmp_pi4 = tmp_pi1;
        tmp_i6 = tmp_i6 + 1;
        if (tmp_i6 == g_unk_02aa2ec8) {
          return;
        }
        tmp_pi1 = tmp_pi4 + 10;
      } while ((tmp_pi4[7] == 0) ||
              (tmp_u2 != *(int *)(g_entities + *tmp_pi4 * 0x600 + 0x2e4) - 0x272U));
    }
    *(uint32_t *)(param_1 + 0x68) = (&g_unk_02aa29dc)[tmp_i6 * 10];
    *(uint32_t *)(param_1 + 0x6c) = (&g_unk_02aa29e0)[tmp_i6 * 10];
    tmp_u3 = (&g_unk_02aa29e4)[tmp_i6 * 10];
    tmp_u5 = 0xffffffff;
    *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 0x10000;
    *(uint32_t *)(param_1 + 0x70) = tmp_u3;
    if ((&g_unk_02aa29c8)[tmp_i6 * 10] != 0) {
      tmp_u5 = (&g_unk_02aa29cc)[tmp_i6 * 10];
    }
    tmp_i7 = tmp_i6 * 0x28;
    tmp_u3 = va("z5 %i %i %i %i %i %i %i %i",tmp_u2 - 1,(int)ROUND((float)(&g_unk_02aa29dc)[tmp_i6 * 10])
               ,(int)ROUND((float)(&g_unk_02aa29e0)[tmp_i6 * 10]),
               (int)ROUND((float)(&g_unk_02aa29e4)[tmp_i6 * 10]),
               (int)ROUND(*(float *)(&g_unk_02aa29d0 + tmp_i7)),
               (int)ROUND(*(float *)(&g_unk_02aa29d4 + tmp_i7)),
               (int)ROUND(*(float *)(&g_unk_02aa29d8 + tmp_i7)),tmp_u5);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
  }
  return;
}

void Cmd_SetSpawnPoint_f(void)
{
  int tmp_i1;
  
  tmp_i1 = trap_Argc();
  if (tmp_i1 != 2) {
    return;
  }
  Cmd_SetSpawnPoint_f_part_17();
  return;
}

void Cmd_WeaponStat_f(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  uint32_t tmp_u3;
  char local_1c [16];
  
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    tmp_i1 = trap_Argc();
    if (tmp_i1 == 2) {
      trap_Argv(1,local_1c,0x10);
      tmp_u2 = strtol(local_1c,(char **)0x0,10);
      if (tmp_u2 < 0x1a) {
        tmp_i1 = tmp_u2 * 0x14 + 0xca0 + *(int *)(param_1 + 400);
        tmp_u3 = va("rws %i %i",*(uint32_t *)(tmp_i1 + 0xc),*(uint32_t *)(tmp_i1 + 0x18));
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
      }
    }
  }
  return;
}

void Cmd_IntermissionWeaponStats_f(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  char local_41c [1036];
  
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    trap_Argv(1,local_41c,0x400);
    tmp_u2 = strtol(local_41c,(char **)0x0,10);
    if (tmp_u2 < 0x41) {
      Q_strncpyz(local_41c,"imws ",0x400);
      tmp_i5 = 0;
      do {
        tmp_i6 = tmp_i5 + 1;
        tmp_i4 = tmp_u2 * 0x54dc + level;
        tmp_i1 = tmp_i4 + 0xca0 + tmp_i5 * 0x14;
        tmp_u3 = va("%i %i %i ",*(uint32_t *)(tmp_i1 + 0xc),*(uint32_t *)(tmp_i1 + 0x18),
                   *(uint32_t *)(tmp_i4 + 0xcbc + tmp_i5 * 0x14));
        Q_strcat(local_41c,0x400,tmp_u3);
        tmp_i5 = tmp_i6;
      } while (tmp_i6 != 0x1a);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,local_41c);
      return;
    }
  }
  return;
}

void Cmd_IntermissionReady_f(int param_1)
{
  uint *tmp_pu1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    tmp_pu1 = (uint *)(*(int *)(param_1 + 400) + 0x68);
    *tmp_pu1 = *tmp_pu1 | 8;
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 8;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0x998) = 1;
  }
  return;
}

void Cmd_IntermissionPlayerKillsDeaths_f(int param_1)
{
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    Cmd_IntermissionPlayerKillsDeaths_f_part_18();
    return;
  }
  return;
}

void Cmd_IntermissionWeaponAccuracies_f(int param_1)
{
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    Cmd_IntermissionWeaponAccuracies_f_part_19();
    return;
  }
  return;
}

void Cmd_IntermissionHitRegions_f(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  char local_41c [1036];
  
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    trap_Argv(1,local_41c,0x400);
    tmp_u2 = strtol(local_41c,(char **)0x0,10);
    if (tmp_u2 < 0x41) {
      tmp_i3 = level + tmp_u2 * 0x54dc;
      tmp_i3 = *(int *)(tmp_i3 + 0xba8) + *(int *)(tmp_i3 + 0xbac) + *(int *)(tmp_i3 + 0xbb0) +
              *(int *)(tmp_i3 + 0xbb4);
      if (tmp_i3 != 0) {
        Q_strncpyz(local_41c,"imhr ",0x400);
        tmp_i5 = 0;
        do {
          tmp_i1 = tmp_i5 * 4;
          tmp_i5 = tmp_i5 + 1;
          tmp_i1 = *(int *)(tmp_u2 * 0x54dc + tmp_i1 + 0xba8 + level);
          tmp_u4 = va("%i %.1f ",tmp_i1,(double)(((float)tmp_i1 / (float)tmp_i3) * 100.0));
          Q_strcat(local_41c,0x400,tmp_u4);
        } while (tmp_i5 != 4);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,local_41c);
      }
    }
  }
  return;
}

void Cmd_SelectedObjective_f(int param_1)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  long double tmp_l7;
  int local_40;
  float local_38;
  char local_2c [28];
  
  if (((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) && (tmp_i1 = trap_Argc(), tmp_i1 == 2)) {
    trap_Argv(1,local_2c,0x10);
    tmp_l2 = strtol(local_2c,(char **)0x0,10);
    if (0 < g_unk_02aa2ec8) {
      local_40 = -1;
      tmp_pu5 = &g_unk_02aa29dc;
      tmp_i6 = 0;
      local_38 = 0.0;
      tmp_i1 = g_unk_02aa2ec8;
      do {
        if ((tmp_pu5[3] == 0) && (tmp_l2 + 1 == tmp_pu5[4])) {
          if (tmp_pu5[-5] == 0) {
            *(uint32_t *)(param_1 + 0x68) = (&g_unk_02aa29dc)[tmp_i6 * 10];
            *(uint32_t *)(param_1 + 0x6c) = (&g_unk_02aa29e0)[tmp_i6 * 10];
            tmp_u4 = (&g_unk_02aa29e4)[tmp_i6 * 10];
            tmp_u3 = 0xffffffff;
            *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 0x10000;
            *(uint32_t *)(param_1 + 0x70) = tmp_u4;
            if ((&g_unk_02aa29c8)[tmp_i6 * 10] != 0) {
              tmp_u3 = (&g_unk_02aa29cc)[tmp_i6 * 10];
            }
            tmp_i1 = tmp_i6 * 0x28;
            tmp_u4 = va("z5 %i %i %i %i %i %i %i %i",tmp_l2,
                       (int)ROUND((float)(&g_unk_02aa29dc)[tmp_i6 * 10]),
                       (int)ROUND((float)(&g_unk_02aa29e0)[tmp_i6 * 10]),
                       (int)ROUND((float)(&g_unk_02aa29e4)[tmp_i6 * 10]),
                       (int)ROUND(*(float *)(&g_unk_02aa29d0 + tmp_i1)),
                       (int)ROUND(*(float *)(&g_unk_02aa29d4 + tmp_i1)),
                       (int)ROUND(*(float *)(&g_unk_02aa29d8 + tmp_i1)),tmp_u3);
            trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
            break;
          }
          tmp_l7 = (long double)VectorDistanceSquared(tmp_pu5,tmp_pu5[-4] * 0x600 + 0x93e608);
          tmp_i1 = g_unk_02aa2ec8;
          if ((local_40 == -1) || (tmp_l7 < (long double)local_38)) {
            local_38 = (float)tmp_l7;
            local_40 = tmp_i6;
          }
        }
        tmp_i6 = tmp_i6 + 1;
        tmp_pu5 = tmp_pu5 + 10;
      } while (tmp_i6 < tmp_i1);
      if (local_40 != -1) {
        *(uint32_t *)(param_1 + 0x68) = (&g_unk_02aa29dc)[local_40 * 10];
        *(uint32_t *)(param_1 + 0x6c) = (&g_unk_02aa29e0)[local_40 * 10];
        tmp_u4 = (&g_unk_02aa29e4)[local_40 * 10];
        tmp_u3 = 0xffffffff;
        *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 0x10000;
        *(uint32_t *)(param_1 + 0x70) = tmp_u4;
        if ((&g_unk_02aa29c8)[local_40 * 10] != 0) {
          tmp_u3 = (&g_unk_02aa29cc)[local_40 * 10];
        }
        tmp_i1 = local_40 * 0x28;
        tmp_u4 = va("z5 %i %i %i %i %i %i %i %i",tmp_l2,
                   (int)ROUND((float)(&g_unk_02aa29dc)[local_40 * 10]),
                   (int)ROUND((float)(&g_unk_02aa29e0)[local_40 * 10]),
                   (int)ROUND((float)(&g_unk_02aa29e4)[local_40 * 10]),
                   (int)ROUND(*(float *)(&g_unk_02aa29d0 + tmp_i1)),
                   (int)ROUND(*(float *)(&g_unk_02aa29d4 + tmp_i1)),
                   (int)ROUND(*(float *)(&g_unk_02aa29d8 + tmp_i1)),tmp_u3);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
      }
    }
  }
  return;
}

void Cmd_Ignore_f(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  char *tmp_pc3;
  int tmp_i4;
  uint32_t tmp_u5;
  int local_91c [64];
  char local_81c [1024];
  uint8_t local_41c [1036];
  
  trap_Argv(1,local_81c,0x400);
  if (local_81c[0] == '\0') {
    tmp_pc3 = "print \"^9usage: ^gignore [name|slot#]\n\"";
  }
  else {
    tmp_i2 = ClientNumbersFromString(local_81c,local_91c);
    tmp_i1 = local_91c[0];
    if (tmp_i2 == 1) {
      tmp_i2 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
      if (local_91c[0] == tmp_i2) {
        trap_SendServerCommand
                  (local_91c[0],"print \"^1ignore error: ^9You can\'t ignore yourself\n\"");
        return;
      }
      tmp_i4 = COM_BitCheck(*(int *)(param_1 + 400) + 0xbe8,local_91c[0]);
      if (tmp_i4 != 0) {
        tmp_u5 = va("print \"^1ignore error: ^9You are already ignoring ^7%s\n\"",
                   *(int *)(g_entities + tmp_i1 * 0x600 + 400) + 0x5f8);
        trap_SendServerCommand(tmp_i2,tmp_u5);
        return;
      }
      COM_BitSet(*(int *)(param_1 + 400) + 0xbe8,local_91c[0]);
      tmp_u5 = va("print \"^xignore: ^7%s^9 added to your ignore list\n\"",
                 *(int *)(g_entities + tmp_i1 * 0x600 + 400) + 0x5f8);
      trap_SendServerCommand(tmp_i2,tmp_u5);
      tmp_u5 = va("chat \"%s^9 is now ignoring you\" -2",*(int *)(param_1 + 400) + 0x5f8);
      trap_SendServerCommand(local_91c[0],tmp_u5);
      return;
    }
    G_MatchOnePlayer(local_91c,local_41c,0x400);
    tmp_pc3 = (char *)va("print \"^1ignore %s\n\"",local_41c);
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc3);
  return;
}

void Cmd_UnIgnore_f(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  int local_524;
  int local_520;
  int local_51c [64];
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x70d2e;
  trap_Argv(1,local_41c,0x400);
  if (local_41c[0] == '\0') {
    tmp_pu4 = g_entities;
    tmp_i1 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand(tmp_i1,"print \"^9usage: ^gunignore [name|slot#]\n\"");
    if ((*(int *)(*(int *)(param_1 + 400) + 0xbe8) != 0) ||
       (*(int *)(*(int *)(param_1 + 400) + 0xbec) != 0)) {
      trap_SendServerCommand(tmp_i1,"print \"^xunignore: ^9You are currently ignoring:\n\"");
      if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
        tmp_i5 = 0;
        do {
          tmp_i2 = COM_BitCheck(*(int *)(param_1 + 400) + 0xbe8,tmp_i5);
          if ((tmp_i2 != 0) && (*(int *)(tmp_pu4 + 400) != 0)) {
            tmp_u3 = va("print \" ^9%2d^g: ^7%s\n\"",tmp_i5,*(int *)(tmp_pu4 + 400) + 0x5f8);
            trap_SendServerCommand(tmp_i1,tmp_u3);
          }
          tmp_i5 = tmp_i5 + 1;
          tmp_pu4 = tmp_pu4 + 0x600;
        } while (tmp_i5 < (int)GHIDRA_FIELD(g_maxclients, 12, 4));
      }
    }
    return;
  }
  local_524 = ClientNumbersFromString(local_41c,local_51c);
  if (0 < local_524) {
    tmp_i1 = 0;
    local_520 = 0;
    do {
      while( true ) {
        tmp_i5 = COM_BitCheck(*(int *)(param_1 + 400) + 0xbe8,local_51c[tmp_i1]);
        if (tmp_i5 == 0) break;
        local_520 = local_51c[tmp_i1];
        tmp_i1 = tmp_i1 + 1;
        if (local_524 <= tmp_i1) goto LAB_00070ebf;
      }
      local_524 = local_524 + -1;
      tmp_i1 = tmp_i1 + 1;
    } while (tmp_i1 < local_524);
LAB_00070ebf:
    if (local_524 == 1) {
      COM_BitClear(*(int *)(param_1 + 400) + 0xbe8,local_520);
      tmp_u3 = va("print \"^xunignore: ^7%s^9 removed from your ignore list\n\"",
                 *(int *)(g_entities + local_520 * 0x600 + 400) + 0x5f8);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
      tmp_u3 = va("chat \"^7%s ^9has stopped ignoring you\" -2",*(int *)(param_1 + 400) + 0x5f8);
      trap_SendServerCommand(local_520,tmp_u3);
      return;
    }
  }
  trap_SendServerCommand
            ((param_1 + -0x93e4a0 >> 9) * -0x55555555,
             "print \"^1unignore error: ^9No match found. Use /unignore with no parameter for a list\n\""
            );
  return;
}

void Cmd_DropObj(uint32_t *param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
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
  
  if (GHIDRA_FIELD(g_dropObj, 12, 4) == 0) {
    return;
  }
  tmp_i1 = param_1[100];
  if ((int)GHIDRA_FIELD(g_dropObj, 12, 4) < *(int *)(tmp_i1 + 0x532c)) {
    return;
  }
  if (*(int *)(tmp_i1 + 0x164) == 0) {
    if (*(int *)(tmp_i1 + 0x168) == 0) {
      return;
    }
LAB_0007112d:
    tmp_i1 = BG_FindItem("Blue Flag");
    if (tmp_i1 == 0) {
      tmp_i1 = BG_FindItem("Objective");
    }
    *(uint32_t *)(param_1[100] + 0x168) = 0;
    tmp_i3 = param_1[100];
LAB_00071159:
    if (tmp_i1 == 0) goto LAB_000712df;
  }
  else {
    tmp_i1 = BG_FindItem("Red Flag");
    if (tmp_i1 == 0) {
      tmp_i1 = BG_FindItem("Objective");
      *(uint32_t *)(param_1[100] + 0x164) = 0;
      tmp_i3 = param_1[100];
      if (*(int *)(tmp_i3 + 0x168) != 0) goto LAB_0007112d;
      goto LAB_00071159;
    }
    *(uint32_t *)(param_1[100] + 0x164) = 0;
    tmp_i3 = param_1[100];
    if (*(int *)(tmp_i3 + 0x168) != 0) goto LAB_0007112d;
  }
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
  tmp_i1 = LaunchItem(tmp_i1,&local_24,&local_3c,*param_1,0x1000);
  *(uint32_t *)(tmp_i1 + 0xa8) = param_1[0x24];
  tmp_u2 = param_1[0x92];
  *(uint32_t *)(tmp_i1 + 0x248) = tmp_u2;
  tmp_u2 = va("%s dropped.",tmp_u2);
  Bot_Util_SendTrigger(tmp_i1,0,tmp_u2,"dropped");
  tmp_i3 = param_1[100];
  param_1[0x24] = 0;
  param_1[0x92] = 0;
LAB_000712df:
  *(int *)(tmp_i3 + 0x532c) = *(int *)(tmp_i3 + 0x532c) + 1;
  return;
}

void Cmd_FireTeam_MP_f(int param_1)
{
  bool tmp_b1;
  int tmp_i2;
  char *tmp_pc3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  long tmp_l7;
  int *tmp_pi8;
  uint8_t *tmp_pu9;
  int tmp_i10;
  int local_68;
  uint8_t local_5c [32];
  char local_3c [44];
  
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    tmp_pc3 = "cpm \"^1Fireteams disabled during Death Match!\"\n";
LAB_00080c1e:
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc3);
    return;
  }
  tmp_i2 = trap_Argc();
  if (tmp_i2 < 2) {
    tmp_pc3 = "cpm \"^9usage: ^gfireteam [create|leave|apply|invite]\"\n";
    goto LAB_00080c1e;
  }
  trap_Argv(1,local_5c,0x20);
  tmp_i2 = Q_stricmp(local_5c,"create");
  if (tmp_i2 == 0) {
    G_RegisterFireteam((param_1 + -0x93e4a0 >> 9) * -0x55555555);
    return;
  }
  tmp_i2 = Q_stricmp(local_5c,"disband");
  if (tmp_i2 == 0) {
    G_DestroyFireteam((param_1 + -0x93e4a0 >> 9) * -0x55555555);
    return;
  }
  tmp_i2 = Q_stricmp(local_5c,"leave");
  if (tmp_i2 == 0) {
    G_RemoveClientFromFireteams((param_1 + -0x93e4a0 >> 9) * -0x55555555,1,1);
    return;
  }
  tmp_i2 = Q_stricmp(local_5c,"apply");
  if (tmp_i2 == 0) {
    tmp_i2 = trap_Argc();
    if (2 < tmp_i2) {
      tmp_i10 = 1;
      trap_Argv(2,local_3c,0x20);
      tmp_i2 = *(int *)(*(int *)(param_1 + 400) + 3000);
      tmp_pi8 = &g_unk_02a996ec;
      local_68 = 0;
      do {
        if (((*tmp_pi8 != 0) &&
            (tmp_i2 == *(int *)(*(int *)(g_entities + (char)tmp_pi8[-0x11] * 0x600 + 400) + 3000))) &&
           (tmp_i4 = Q_stricmp(*(uint32_t *)(bg_fireteamNames + (tmp_pi8[-0x12] + -1) * 4),local_3c)
           , tmp_i4 == 0)) {
          local_68 = tmp_i10;
        }
        tmp_pi8 = tmp_pi8 + 0x14;
        tmp_i10 = tmp_i10 + 1;
      } while (tmp_pi8 != (int *)&g_unk_02a99aac);
      if ((local_68 != 0) || (local_68 = strtol(local_3c,(char **)0x0,10), 0 < local_68)) {
        G_ApplyToFireTeam((param_1 + -0x93e4a0 >> 9) * -0x55555555,local_68 + -1);
        return;
      }
    }
    tmp_pc3 = "cpm \"^9usage: ^gfireteam apply [fireteamname|fireteamnumber]\"\n";
  }
  else {
    tmp_i2 = Q_stricmp(local_5c,"invite");
    if (tmp_i2 == 0) {
      tmp_i2 = trap_Argc();
      if (tmp_i2 < 3) {
        tmp_pc3 = "cpm \"^9usage: ^gfireteam invite [clientname|clientnumber]\"\n";
        goto LAB_00080c1e;
      }
      trap_Argv(2,local_3c,0x20);
      tmp_pu9 = g_entities;
      if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
        local_68 = 0;
        tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
        tmp_i10 = 1;
        do {
          tmp_i4 = local_68;
          if (((*(int *)(tmp_pu9 + 0x194) != 0) && (*(int *)(tmp_pu9 + 400) != 0)) &&
             (tmp_i5 = Q_stricmp(*(int *)(tmp_pu9 + 400) + 0x5f8,local_3c),
             tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4), tmp_i4 = tmp_i10, tmp_i5 != 0)) {
            tmp_i4 = local_68;
          }
          local_68 = tmp_i4;
          tmp_pu9 = tmp_pu9 + 0x600;
          tmp_b1 = tmp_i10 < tmp_i2;
          tmp_i10 = tmp_i10 + 1;
        } while (tmp_b1);
        if (0 < local_68) {
          tmp_u6 = local_68 - 1;
          goto LAB_00080f2c;
        }
      }
      tmp_l7 = strtol(local_3c,(char **)0x0,10);
      tmp_u6 = tmp_l7 - 1;
      if (((tmp_u6 < 0x40) && (*(int *)(g_entities + tmp_u6 * 0x600 + 0x194) != 0)) &&
         (*(int *)(g_entities + tmp_u6 * 0x600 + 400) != 0)) {
LAB_00080f2c:
        G_InviteToFireTeam((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
        return;
      }
    }
    else {
      tmp_i2 = Q_stricmp(local_5c,&g_unk_0024962a);
      if (tmp_i2 == 0) {
        tmp_i2 = trap_Argc();
        if (tmp_i2 < 3) {
          tmp_pc3 = "cpm \"^9usage :^g fireteam warn [clientname|clientnumber]\"\n";
          goto LAB_00080c1e;
        }
        trap_Argv(2,local_3c,0x20);
        tmp_pu9 = g_entities;
        if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
          local_68 = 0;
          tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
          tmp_i10 = 1;
          do {
            tmp_i4 = local_68;
            if (((*(int *)(tmp_pu9 + 0x194) != 0) && (*(int *)(tmp_pu9 + 400) != 0)) &&
               (tmp_i5 = Q_stricmp(*(int *)(tmp_pu9 + 400) + 0x5f8,local_3c),
               tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4), tmp_i4 = tmp_i10, tmp_i5 != 0)) {
              tmp_i4 = local_68;
            }
            local_68 = tmp_i4;
            tmp_pu9 = tmp_pu9 + 0x600;
            tmp_b1 = tmp_i10 < tmp_i2;
            tmp_i10 = tmp_i10 + 1;
          } while (tmp_b1);
          if (0 < local_68) {
            tmp_u6 = local_68 - 1;
            goto LAB_00081038;
          }
        }
        tmp_l7 = strtol(local_3c,(char **)0x0,10);
        tmp_u6 = tmp_l7 - 1;
        if (((tmp_u6 < 0x40) && (*(int *)(g_entities + tmp_u6 * 0x600 + 0x194) != 0)) &&
           (*(int *)(g_entities + tmp_u6 * 0x600 + 400) != 0)) {
LAB_00081038:
          G_WarnFireTeamPlayer((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
          return;
        }
      }
      else {
        tmp_i2 = Q_stricmp(local_5c,"kick");
        if (tmp_i2 == 0) {
          tmp_i2 = trap_Argc();
          if (tmp_i2 < 3) {
            tmp_pc3 = "cpm \"^9usage :^g fireteam kick [clientname|clientnumber]\"\n";
            goto LAB_00080c1e;
          }
          trap_Argv(2,local_3c,0x20);
          tmp_pu9 = g_entities;
          if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
            local_68 = 0;
            tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
            tmp_i10 = 1;
            do {
              tmp_i4 = local_68;
              if (((*(int *)(tmp_pu9 + 0x194) != 0) && (*(int *)(tmp_pu9 + 400) != 0)) &&
                 (tmp_i5 = Q_stricmp(*(int *)(tmp_pu9 + 400) + 0x5f8,local_3c),
                 tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4), tmp_i4 = tmp_i10, tmp_i5 != 0)) {
                tmp_i4 = local_68;
              }
              local_68 = tmp_i4;
              tmp_pu9 = tmp_pu9 + 0x600;
              tmp_b1 = tmp_i10 < tmp_i2;
              tmp_i10 = tmp_i10 + 1;
            } while (tmp_b1);
            if (0 < local_68) {
              tmp_u6 = local_68 - 1;
              goto LAB_00081145;
            }
          }
          tmp_l7 = strtol(local_3c,(char **)0x0,10);
          tmp_u6 = tmp_l7 - 1;
          if (((tmp_u6 < 0x40) && (*(int *)(g_entities + tmp_u6 * 0x600 + 0x194) != 0)) &&
             (*(int *)(g_entities + tmp_u6 * 0x600 + 400) != 0)) {
LAB_00081145:
            G_KickFireTeamPlayer((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
            return;
          }
        }
        else {
          tmp_i2 = Q_stricmp(local_5c,"propose");
          if (tmp_i2 != 0) {
            return;
          }
          tmp_i2 = trap_Argc();
          if (tmp_i2 < 3) {
            tmp_pc3 = "cpm \"^9usage :^g fireteam propose [clientname|clientnumber]\"\n";
            goto LAB_00080c1e;
          }
          trap_Argv(2,local_3c,0x20);
          tmp_pu9 = g_entities;
          if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
            local_68 = 0;
            tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4);
            tmp_i10 = 1;
            do {
              tmp_i4 = local_68;
              if (((*(int *)(tmp_pu9 + 0x194) != 0) && (*(int *)(tmp_pu9 + 400) != 0)) &&
                 (tmp_i5 = Q_stricmp(*(int *)(tmp_pu9 + 400) + 0x5f8,local_3c),
                 tmp_i2 = GHIDRA_FIELD(g_maxclients, 12, 4), tmp_i4 = tmp_i10, tmp_i5 != 0)) {
                tmp_i4 = local_68;
              }
              local_68 = tmp_i4;
              tmp_pu9 = tmp_pu9 + 0x600;
              tmp_b1 = tmp_i10 < tmp_i2;
              tmp_i10 = tmp_i10 + 1;
            } while (tmp_b1);
            if (0 < local_68) {
              tmp_u6 = local_68 - 1;
              goto LAB_00081261;
            }
          }
          tmp_l7 = strtol(local_3c,(char **)0x0,10);
          tmp_u6 = tmp_l7 - 1;
          if (((tmp_u6 < 0x40) && (*(int *)(g_entities + tmp_u6 * 0x600 + 0x194) != 0)) &&
             (*(int *)(g_entities + tmp_u6 * 0x600 + 400) != 0)) {
LAB_00081261:
            G_ProposeFireTeamPlayer((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
            return;
          }
        }
      }
    }
    tmp_pc3 = "cpm \"^1fireteam error: ^9Invalid client selected\"\n";
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_pc3);
  return;
}

void Svcmd_GameMem_f(void)
{
  G_Printf("Game memory status: %i out of %i bytes allocated\n",allocPoint,0x400000);
  return;
}

void Cmd_AuthRcon_f(int param_1)
{
  int tmp_i1;
  char local_80c [1024];
  char local_40c [1024];
  
  trap_Cvar_VariableStringBuffer("rconPassword",local_80c,0x400);
  trap_Argv(1,local_40c,0x400);
  if (local_80c[0] != '\0') {
    tmp_i1 = strcmp(local_80c,local_40c);
    if (tmp_i1 == 0) {
      *(uint32_t *)(*(int *)(param_1 + 400) + 0xc80) = 2;
    }
  }
  return;
}

void Svcmd_AddIP_f(void)
{
  int tmp_i1;
  char tmp_c2;
  int tmp_i3;
  long tmp_l4;
  int tmp_i5;
  char *tmp_pc6;
  char *tmp_pc7;
  int tmp_i8;
  uint32_t local_4a4;
  uint32_t local_4a0;
  char local_49c [128];
  char local_41c;
  char local_41b [1031];
  uint32_t uStack_14;
  
  uStack_14 = 0xe2dc9;
  tmp_i3 = trap_Argc();
  if (tmp_i3 < 2) {
    G_Printf("Usage:  addip <ip-mask>\n");
    return;
  }
  tmp_pc7 = &local_41c;
  trap_Argv(1,tmp_pc7,0x400);
  if (g_unk_008253e0 < 1) {
    if (g_unk_008253e0 == 0) {
LAB_000e2e3b:
      tmp_i3 = g_unk_008253e0;
      g_unk_008253e0 = g_unk_008253e0 + 1;
    }
    else {
      tmp_i3 = 0;
    }
  }
  else {
    tmp_i3 = 0;
    tmp_i8 = g_unk_008233e4;
    while (tmp_i8 != -1) {
      tmp_i3 = tmp_i3 + 1;
      if (tmp_i3 == g_unk_008253e0) {
        if (tmp_i3 == 0x400) {
          G_Printf("IP filter list is full\n");
          return;
        }
        goto LAB_000e2e3b;
      }
      tmp_i8 = (&g_unk_008233e4)[tmp_i3 * 2];
    }
  }
  local_4a0 = 0;
  tmp_i8 = 0;
  local_4a4 = 0;
  do {
    tmp_c2 = *tmp_pc7;
    if ((byte)(tmp_c2 - 0x30U) < 10) {
      tmp_i1 = 0;
      tmp_pc6 = tmp_pc7;
      do {
        tmp_pc7 = tmp_pc6;
        tmp_i5 = tmp_i1;
        tmp_pc6 = tmp_pc7 + 1;
        local_49c[tmp_i5] = tmp_c2;
        tmp_c2 = *tmp_pc6;
        tmp_i1 = tmp_i5 + 1;
      } while ((byte)(tmp_c2 - 0x30U) < 10);
      local_49c[tmp_i5 + 1] = '\0';
      tmp_l4 = strtol(local_49c,(char **)0x0,10);
      tmp_c2 = *tmp_pc6;
      local_49c[tmp_i8 + -4] = -1;
      *(char *)((int)&local_4a4 + tmp_i8) = (char)tmp_l4;
    }
    else {
      if (tmp_c2 != '*') {
        G_Printf("Bad filter address: %s\n",tmp_pc7);
        (&g_unk_008233e4)[tmp_i3 * 2] = 0xffffffff;
        goto LAB_000e2e9d;
      }
      tmp_c2 = tmp_pc7[1];
    }
    if (tmp_c2 == '\0') break;
    tmp_pc7 = tmp_pc7 + 2;
    tmp_i8 = tmp_i8 + 1;
  } while (tmp_i8 != 4);
  (&ipFilters)[tmp_i3 * 2] = local_4a0;
  (&g_unk_008233e4)[tmp_i3 * 2] = local_4a4;
LAB_000e2e9d:
  UpdateIPBans();
  return;
}

void Svcmd_RemoveIP_f(void)
{
  int tmp_i1;
  char tmp_c2;
  int tmp_i3;
  long tmp_l4;
  int tmp_i5;
  char *tmp_pc6;
  char *tmp_pc7;
  int local_4a4;
  int local_4a0;
  char local_49c [128];
  char local_41c;
  char local_41b [1031];
  uint32_t uStack_14;
  
  uStack_14 = 0xe2f89;
  tmp_i3 = trap_Argc();
  if (tmp_i3 < 2) {
    G_Printf("Usage:  removeip <ip-mask>\n");
    return;
  }
  trap_Argv(1,&local_41c,0x400);
  local_4a4 = 0;
  tmp_i3 = 0;
  local_4a0 = 0;
  tmp_pc7 = &local_41c;
  do {
    tmp_c2 = *tmp_pc7;
    if ((byte)(tmp_c2 - 0x30U) < 10) {
      tmp_i1 = 0;
      tmp_pc6 = tmp_pc7;
      do {
        tmp_pc7 = tmp_pc6;
        tmp_i5 = tmp_i1;
        tmp_pc6 = tmp_pc7 + 1;
        local_49c[tmp_i5] = tmp_c2;
        tmp_c2 = *tmp_pc6;
        tmp_i1 = tmp_i5 + 1;
      } while ((byte)(tmp_c2 - 0x30U) < 10);
      local_49c[tmp_i5 + 1] = '\0';
      tmp_l4 = strtol(local_49c,(char **)0x0,10);
      tmp_c2 = *tmp_pc6;
      local_49c[tmp_i3 + -4] = -1;
      *(char *)((int)&local_4a4 + tmp_i3) = (char)tmp_l4;
    }
    else {
      if (tmp_c2 != '*') {
        G_Printf("Bad filter address: %s\n",tmp_pc7);
        return;
      }
      tmp_c2 = tmp_pc7[1];
    }
    if (tmp_c2 == '\0') break;
    tmp_pc7 = tmp_pc7 + 2;
    tmp_i3 = tmp_i3 + 1;
  } while (tmp_i3 != 4);
  tmp_i3 = 0;
  if (0 < g_unk_008253e0) {
    do {
      if (((&ipFilters)[tmp_i3 * 2] == local_4a0) && ((&g_unk_008233e4)[tmp_i3 * 2] == local_4a4)) {
        (&g_unk_008233e4)[tmp_i3 * 2] = 0xffffffff;
        G_Printf("Removed.\n");
        UpdateIPBans();
        return;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != g_unk_008253e0);
  }
  G_Printf("Didn\'t find %s.\n",&local_41c);
  return;
}

void Svcmd_EntityList_f(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  if (1 < g_unk_00abe8a8) {
    tmp_i3 = 1;
    tmp_i2 = 0x93eaa0;
    tmp_i1 = g_unk_00abe8a8;
    do {
      if (*(int *)(tmp_i2 + 0x194) != 0) {
        tmp_i4 = tmp_i3;
        G_Printf(&g_unk_002584d8,tmp_i3);
        tmp_i1 = *(int *)(tmp_i2 + 4);
        switch(tmp_i1) {
        case 0:
          G_Printf("ET_GENERAL          ",tmp_i4);
          break;
        case 1:
          G_Printf("ET_PLAYER           ",tmp_i4);
          break;
        case 2:
          G_Printf("ET_ITEM             ",tmp_i4);
          break;
        case 3:
          G_Printf("ET_MISSILE          ",tmp_i4);
          break;
        case 4:
          G_Printf("ET_MOVER            ",tmp_i4);
          break;
        case 5:
          G_Printf("ET_BEAM             ",tmp_i4);
          break;
        case 6:
          G_Printf("ET_PORTAL           ",tmp_i4);
          break;
        case 7:
          G_Printf("ET_SPEAKER          ",tmp_i4);
          break;
        case 8:
          G_Printf("ET_PUSH_TRIGGER     ",tmp_i4);
          break;
        case 9:
          G_Printf("ET_TELEPORT_TRIGGER ",tmp_i4);
          break;
        case 10:
          G_Printf("ET_INVISIBLE        ",tmp_i4);
          break;
        case 0xb:
          G_Printf("ET_CONCUSSIVE_TRIGGR",tmp_i4);
          break;
        default:
          G_Printf("%3i                 ",tmp_i1);
          tmp_i4 = tmp_i1;
          break;
        case 0xe:
          G_Printf("ET_EXPLOSIVE        ",tmp_i4);
          break;
        case 0xf:
          G_Printf("ET_ALARMBOX          ",tmp_i4);
          break;
        case 0x39:
          G_Printf("ET_MISSILECAM          ",tmp_i4);
          break;
        case 0x3b:
          G_Printf("ET_EVENTS           ",tmp_i4);
        }
        tmp_i1 = *(int *)(tmp_i2 + 0x1a4);
        if (tmp_i1 != 0) {
          G_Printf(&g_unk_0024e6e9,tmp_i1);
          tmp_i4 = tmp_i1;
        }
        G_Printf("\n",tmp_i4);
        tmp_i1 = g_unk_00abe8a8;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_i2 = tmp_i2 + 0x600;
    } while (tmp_i3 < tmp_i1);
  }
  return;
}

void Svcmd_ForceTeam_f(void)
{
  int tmp_i1;
  uint8_t local_40c [1024];
  
  trap_Argv(1,local_40c,0x400);
  tmp_i1 = ClientForString(local_40c);
  if (tmp_i1 != 0) {
    trap_Argv(2,local_40c,0x400);
    SetTeam(g_entities + (tmp_i1 - level >> 2) * -0x65dcd600,local_40c,0,
            *(uint32_t *)(tmp_i1 + 0xbcc),*(uint32_t *)(tmp_i1 + 0xbd0),1);
  }
  return;
}

void Svcmd_ResetMatch_f(int param_1,int param_2)
{
  int tmp_i1;
  int *tmp_pi2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  if (0 < g_unk_00abe938) {
    tmp_pi2 = &g_unk_00abe944;
    tmp_pi4 = &g_unk_00abe944 + g_unk_00abe938;
    do {
      tmp_i1 = *tmp_pi2;
      tmp_pi2 = tmp_pi2 + 1;
      *(uint32_t *)(*(int *)(g_entities + tmp_i1 * 0x600 + 400) + 0x998) = 0;
    } while (tmp_pi2 != tmp_pi4);
  }
  if (param_1 != 0) {
    G_resetRoundState();
    G_resetModeState();
  }
  if (param_2 != 0) {
    if ((GHIDRA_FIELD(g_gamestate, 12, 4) == 0) || (GHIDRA_FIELD(g_gamestate, 12, 4) == 3)) {
      tmp_u3 = 2;
    }
    else {
      tmp_u3 = 5;
    }
    tmp_u3 = va("map_restart 0 %i\n",tmp_u3);
    trap_SendConsoleCommand(2,tmp_u3);
  }
  trap_Cvar_Set("g_reset",&g_unk_00258b23);
  return;
}

void Svcmd_SwapTeams_f(void)
{
  int tmp_i1;
  int *tmp_pi2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  G_resetRoundState();
  if ((GHIDRA_FIELD(g_gamestate, 12, 4) != 2 && GHIDRA_FIELD(g_gamestate, 12, 4) != -1) && (GHIDRA_FIELD(g_gamestate, 12, 4) != 5)) {
    G_resetModeState();
    trap_Cvar_Set("g_swapteams",&g_unk_00258b23);
    if (0 < g_unk_00abe938) {
      tmp_pi2 = &g_unk_00abe944;
      tmp_pi4 = &g_unk_00abe944 + g_unk_00abe938;
      do {
        tmp_i1 = *tmp_pi2;
        tmp_pi2 = tmp_pi2 + 1;
        *(uint32_t *)(*(int *)(g_entities + tmp_i1 * 0x600 + 400) + 0x998) = 0;
      } while (tmp_pi2 != tmp_pi4);
    }
    if ((GHIDRA_FIELD(g_gamestate, 12, 4) == 0) || (GHIDRA_FIELD(g_gamestate, 12, 4) == 3)) {
      tmp_u3 = 2;
    }
    else {
      tmp_u3 = 5;
    }
    tmp_u3 = va("map_restart 0 %i\n",tmp_u3);
    trap_SendConsoleCommand(2,tmp_u3);
    trap_Cvar_Set("g_reset",&g_unk_00258b23);
    return;
  }
  G_swapTeams();
  return;
}

void Svcmd_ShuffleTeams_f(int param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  
  if (param_1 == 0) {
    G_shuffleTeams();
  }
  else {
    G_resetRoundState();
    G_shuffleTeams();
    if ((GHIDRA_FIELD(g_gamestate, 12, 4) != -1 && GHIDRA_FIELD(g_gamestate, 12, 4) != 2) && GHIDRA_FIELD(g_gamestate, 12, 4) != 5) {
      G_resetModeState();
      if (0 < g_unk_00abe938) {
        tmp_pi2 = &g_unk_00abe944;
        tmp_pi4 = &g_unk_00abe944 + g_unk_00abe938;
        do {
          tmp_i1 = *tmp_pi2;
          tmp_pi2 = tmp_pi2 + 1;
          *(uint32_t *)(*(int *)(g_entities + tmp_i1 * 0x600 + 400) + 0x998) = 0;
        } while (tmp_pi2 != tmp_pi4);
      }
      if ((GHIDRA_FIELD(g_gamestate, 12, 4) == 0) || (GHIDRA_FIELD(g_gamestate, 12, 4) == 3)) {
        tmp_u3 = 2;
      }
      else {
        tmp_u3 = 5;
      }
      tmp_u3 = va("map_restart 0 %i\n",tmp_u3);
      trap_SendConsoleCommand(2,tmp_u3);
      trap_Cvar_Set("g_reset",&g_unk_00258b23);
      return;
    }
  }
  return;
}

void Svcmd_Campaign_f(void)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint8_t *local_424;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xe3ace;
  trap_Argv(1,local_41c,0x400);
  tmp_i1 = g_unk_02a9848c;
  if (g_unk_02a9848c < 1) {
    if (g_unk_02a9848c != 0) {
      local_424 = (uint8_t *)0x0;
LAB_000e3b3f:
      if ((local_424[0x488] & 4) != 0) {
        trap_Cvar_Set("g_oldCampaign",0x2e515d0);
        trap_Cvar_Set("g_currentCampaign",local_424 + 0x288);
        trap_Cvar_Set("g_currentCampaignMap",&g_unk_0024bfa6);
        g_unk_02a98494 = 1;
        tmp_u3 = va("%i",4);
        trap_Cvar_Set("g_gametype",tmp_u3);
        tmp_u3 = va("map %s\n",local_424);
        trap_SendConsoleCommand(2,tmp_u3);
        return;
      }
    }
  }
  else {
    local_424 = g_campaigns;
    tmp_i4 = 0;
    do {
      tmp_i2 = strcmp(local_424 + 0x288,local_41c);
      if (tmp_i2 == 0) goto LAB_000e3b3f;
      tmp_i4 = tmp_i4 + 1;
      local_424 = local_424 + 0x494;
    } while (tmp_i4 != tmp_i1);
  }
  G_Printf("Can\'t find campaign \'%s\'\n",local_41c);
  return;
}

void Svcmd_ListCampaigns_f(void)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  int tmp_i4;
  
  if (0 < g_unk_02a9848c) {
    tmp_pu2 = g_campaigns;
    tmp_i1 = 0;
    tmp_i3 = 0;
    do {
      if ((tmp_pu2[0x488] & 4) != 0) {
        tmp_i1 = tmp_i1 + 1;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu2 = tmp_pu2 + 0x494;
    } while (tmp_i3 != g_unk_02a9848c);
    if (tmp_i1 != 0) {
      tmp_i4 = 0;
      G_Printf("%i campaigns found:\n",tmp_i1);
      tmp_i1 = g_unk_02a9848c;
      tmp_i3 = 0x2cee4e8;
      if (0 < g_unk_02a9848c) {
        do {
          while ((*(byte *)(tmp_i3 + 0x200) & 4) == 0) {
            tmp_i4 = tmp_i4 + 1;
            tmp_i3 = tmp_i3 + 0x494;
            if (tmp_i1 <= tmp_i4) {
              return;
            }
          }
          tmp_i4 = tmp_i4 + 1;
          G_Printf(" %s\n",tmp_i3);
          tmp_i1 = g_unk_02a9848c;
          tmp_i3 = tmp_i3 + 0x494;
        } while (tmp_i4 < g_unk_02a9848c);
      }
      return;
    }
  }
  G_Printf("No campaigns found.\n");
  return;
}

void Svcmd_RevivePlayer(uint32_t param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  if (GHIDRA_FIELD(g_cheats, 12, 4) != 0) {
    tmp_i1 = FindClientByName(param_1);
    if (-1 < tmp_i1) {
      ReviveEntity(g_entities + tmp_i1 * 0x600,g_entities + tmp_i1 * 0x600);
    }
    return;
  }
  tmp_u2 = va("print \"Cheats are not enabled on this server.\n\"");
  trap_SendServerCommand(0xffffffff,tmp_u2);
  return;
}

