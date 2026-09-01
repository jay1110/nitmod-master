/* Admin, bans, mutes, shrubbot/nitrox permissions — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_admin.h"

void G_WarnFireTeamPlayer(uint param_1,uint param_2)
{
  char tmp_c1;
  int tmp_i2;
  char *tmp_pc3;
  char *tmp_pc4;
  int local_30;
  
  if (param_1 == param_2) {
    return;
  }
  if ((0x3f < param_1) || (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
    G_Error("G_WarnFireTeamPlayer: invalid client");
  }
  if ((0x3f < param_2) || (*(int *)(g_entities + param_2 * 0x600 + 400) == 0)) {
    G_Error("G_WarnFireTeamPlayer: invalid client");
  }
  if ((0x3f < param_1) || (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
    G_Error("G_IsFireteamLeader: invalid client");
  }
  if ((g_unk_02a996ec == 0) || (param_1 != (int)g_unk_02a996a8)) {
    if ((g_unk_02a9973c == 0) || (param_1 != (int)g_unk_02a996f8)) {
      if ((g_unk_02a9978c == 0) || (param_1 != (int)g_unk_02a99748)) {
        if ((g_unk_02a997dc == 0) || (param_1 != (int)g_unk_02a99798)) {
          if ((g_unk_02a9982c == 0) || (param_1 != (int)g_unk_02a997e8)) {
            if ((g_unk_02a9987c == 0) || (param_1 != (int)g_unk_02a99838)) {
              if ((g_unk_02a998cc == 0) || (param_1 != (int)g_unk_02a99888)) {
                if ((g_unk_02a9991c == 0) || (param_1 != (int)g_unk_02a998d8)) {
                  if ((g_unk_02a9996c == 0) || (param_1 != (int)g_unk_02a99928)) {
                    if ((g_unk_02a999bc == 0) || (param_1 != (int)g_unk_02a99978)) {
                      if ((g_unk_02a99a0c == 0) || (param_1 != (int)g_unk_02a999c8)) {
                        if ((g_unk_02a99a5c == 0) || (param_1 != (int)g_unk_02a99a18)) {
                          trap_SendServerCommand
                                    (param_1,"cpm \"You are not the leader of a fireteam\"\n");
                          return;
                        }
                        tmp_i2 = 0xb;
                      }
                      else {
                        tmp_i2 = 10;
                      }
                    }
                    else {
                      tmp_i2 = 9;
                    }
                  }
                  else {
                    tmp_i2 = 8;
                  }
                }
                else {
                  tmp_i2 = 7;
                }
              }
              else {
                tmp_i2 = 6;
              }
            }
            else {
              tmp_i2 = 5;
            }
          }
          else {
            tmp_i2 = 4;
          }
        }
        else {
          tmp_i2 = 3;
        }
      }
      else {
        tmp_i2 = 2;
      }
    }
    else {
      tmp_i2 = 1;
    }
  }
  else {
    tmp_i2 = 0;
  }
  if ((((int)param_2 < 0) || ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= (int)param_2)) ||
     (*(int *)(g_entities + param_2 * 0x600 + 400) == 0)) {
    G_Error("G_IsOnFireteam: invalid client");
  }
  tmp_pc4 = &g_unk_02a996a9;
  local_30 = 0;
  do {
    if (((*(int *)(tmp_pc4 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && (tmp_pc4[-1] != -1)) {
      if (param_2 == (int)tmp_pc4[-1]) {
LAB_0007fae8:
        if (&g_unk_02a996a4 + tmp_i2 * 0x14 == &g_unk_02a996a4 + local_30 * 0x14) {
          trap_SendServerCommand
                    (param_2,"cpm \"You have been warned by your Fireteam Commander\n\"");
          Bot_Event_FireTeam_Warn(param_1,param_2);
          return;
        }
        break;
      }
      tmp_pc3 = tmp_pc4;
      while ((tmp_pc4 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 != tmp_pc3 && (tmp_c1 = *tmp_pc3, tmp_c1 != -1))) {
        tmp_pc3 = tmp_pc3 + 1;
        if (param_2 == (int)tmp_c1) goto LAB_0007fae8;
      }
    }
    tmp_pc4 = tmp_pc4 + 0x50;
    local_30 = local_30 + 1;
  } while (tmp_pc4 != (char *)((int)&g_unk_02a99a68 + 1));
  trap_SendServerCommand(param_1,"cpm \"You are not on the same Fireteam as the other player\"\n");
  return;
}

void G_KickFireTeamPlayer(uint param_1,uint param_2)
{
  char tmp_c1;
  uint32_t tmp_u2;
  int tmp_i3;
  char *tmp_pc4;
  char *tmp_pc5;
  int tmp_i6;
  int local_c8;
  int local_c0;
  int local_bc;
  char *local_b4;
  uint32_t local_a4;
  uint32_t local_a0;
  uint8_t local_9c [140];
  
  if (param_1 == param_2) {
    return;
  }
  if ((0x3f < param_1) || (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
    G_Error("G_KickFireTeamPlayer: invalid client");
  }
  if ((0x3f < param_2) || (*(int *)(g_entities + param_2 * 0x600 + 400) == 0)) {
    G_Error("G_KickFireTeamPlayer: invalid client");
  }
  if ((0x3f < param_1) || (*(int *)(g_entities + param_1 * 0x600 + 400) == 0)) {
    G_Error("G_IsFireteamLeader: invalid client");
  }
  if ((g_unk_02a996ec == 0) || (param_1 != (int)g_unk_02a996a8)) {
    if ((g_unk_02a9973c == 0) || (param_1 != (int)g_unk_02a996f8)) {
      if ((g_unk_02a9978c == 0) || (param_1 != (int)g_unk_02a99748)) {
        if ((g_unk_02a997dc == 0) || (param_1 != (int)g_unk_02a99798)) {
          if ((g_unk_02a9982c == 0) || (param_1 != (int)g_unk_02a997e8)) {
            if ((g_unk_02a9987c == 0) || (param_1 != (int)g_unk_02a99838)) {
              if ((g_unk_02a998cc == 0) || (param_1 != (int)g_unk_02a99888)) {
                if ((g_unk_02a9991c == 0) || (param_1 != (int)g_unk_02a998d8)) {
                  if ((g_unk_02a9996c == 0) || (param_1 != (int)g_unk_02a99928)) {
                    if ((g_unk_02a999bc == 0) || (param_1 != (int)g_unk_02a99978)) {
                      if ((g_unk_02a99a0c == 0) || (param_1 != (int)g_unk_02a999c8)) {
                        if ((g_unk_02a99a5c == 0) || (param_1 != (int)g_unk_02a99a18)) {
                          trap_SendServerCommand
                                    (param_1,"cpm \"You are not the leader of a fireteam\"\n");
                          return;
                        }
                        tmp_i3 = 0xb;
                      }
                      else {
                        tmp_i3 = 10;
                      }
                    }
                    else {
                      tmp_i3 = 9;
                    }
                  }
                  else {
                    tmp_i3 = 8;
                  }
                }
                else {
                  tmp_i3 = 7;
                }
              }
              else {
                tmp_i3 = 6;
              }
            }
            else {
              tmp_i3 = 5;
            }
          }
          else {
            tmp_i3 = 4;
          }
        }
        else {
          tmp_i3 = 3;
        }
      }
      else {
        tmp_i3 = 2;
      }
    }
    else {
      tmp_i3 = 1;
    }
  }
  else {
    tmp_i3 = 0;
  }
  if ((((int)param_2 < 0) || ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= (int)param_2)) ||
     (*(int *)(g_entities + param_2 * 0x600 + 400) == 0)) {
    G_Error("G_IsOnFireteam: invalid client");
  }
  tmp_pc4 = &g_unk_02a996a9;
  local_c8 = 0;
  do {
    if (((*(int *)(tmp_pc4 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && (tmp_pc4[-1] != -1)) {
      if (param_2 == (int)tmp_pc4[-1]) {
LAB_0007ffc0:
        if (&g_unk_02a996a4 + tmp_i3 * 0x14 == &g_unk_02a996a4 + local_c8 * 0x14) {
          Bot_Event_LeftFireTeam(param_2);
          if ((int)param_2 < 0) {
            G_Error("G_RemoveClientFromFireteams: invalid client");
LAB_00080203:
            G_Error("G_IsOnFireteam: invalid client");
          }
          else if ((((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= (int)param_2) ||
                   (*(int *)(g_entities + param_2 * 0x600 + 400) == 0)) &&
                  ((G_Error("G_RemoveClientFromFireteams: invalid client"),
                   (int)GHIDRA_FIELD(g_maxclients, 12, 4) <= (int)param_2 ||
                   (*(int *)(g_entities + param_2 * 0x600 + 400) == 0)))) goto LAB_00080203;
          tmp_u2 = GHIDRA_FIELD(g_maxclients, 12, 4);
          local_b4 = &g_unk_02a996a9;
          local_c0 = 0;
          goto LAB_00080032;
        }
        break;
      }
      tmp_pc5 = tmp_pc4;
      while ((tmp_pc5 != tmp_pc4 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 && (tmp_c1 = *tmp_pc5, tmp_c1 != -1))) {
        tmp_pc5 = tmp_pc5 + 1;
        if (param_2 == (int)tmp_c1) goto LAB_0007ffc0;
      }
    }
    tmp_pc4 = tmp_pc4 + 0x50;
    local_c8 = local_c8 + 1;
  } while (tmp_pc4 != (char *)((int)&g_unk_02a99a68 + 1));
  trap_SendServerCommand(param_1,"cpm \"You are not on the same Fireteam as the other player\"\n");
  return;
LAB_00080032:
  do {
    if (((*(int *)(local_b4 + 0x43) != 0) && (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4))) && (local_b4[-1] != -1)
       ) {
      if (param_2 == (int)local_b4[-1]) {
        if ((&g_unk_02a996a9)[local_c0 * 0x50] == -1) {
          (&g_unk_02a996ec)[local_c0 * 0x14] = 0;
          (&g_unk_02a996a4)[local_c0 * 0x14] = 0xffffffff;
        }
        tmp_i3 = 0;
        goto LAB_0008024c;
      }
      tmp_pc4 = local_b4;
      while ((tmp_pc4 != local_b4 + GHIDRA_FIELD(g_maxclients, 12, 4) + -1 && (tmp_c1 = *tmp_pc4, tmp_c1 != -1))) {
        tmp_pc4 = tmp_pc4 + 1;
        if (param_2 == (int)tmp_c1) {
          tmp_i3 = 0;
          goto LAB_000800d0;
        }
      }
    }
    local_b4 = local_b4 + 0x50;
    local_c0 = local_c0 + 1;
  } while (local_b4 != (char *)((int)&g_unk_02a99a68 + 1));
  goto LAB_0008007d;
  while (param_2 != (int)(&g_unk_02a996a8)[tmp_i3 + local_c0 * 0x50]) {
LAB_000800d0:
    tmp_i3 = tmp_i3 + 1;
    if ((int)GHIDRA_FIELD(g_maxclients, 12, 4) <= tmp_i3) goto LAB_000800d5;
  }
LAB_0008024c:
  local_bc = tmp_u2 + -1;
  if (tmp_i3 < local_bc) {
    tmp_i6 = local_c0 * 0x50 + tmp_i3;
    memmove(&g_unk_02a996a8 + tmp_i6,&g_unk_02a996a9 + tmp_i6,(tmp_u2 - tmp_i3) - 1);
  }
  (&g_unk_02a996a8)[local_bc + local_c0 * 0x50] = 0xff;
LAB_000800d5:
  Bot_Event_LeftFireTeam(param_2);
  local_a4 = 0;
  local_a0 = 0;
  if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
    if ((&g_unk_02a996ec)[local_c0 * 0x14] == 0) {
      Com_sprintf(local_9c,0x80,"\\n\\-1");
    }
    else {
      if (0 < (int)GHIDRA_FIELD(g_maxclients, 12, 4)) {
        tmp_i6 = 0;
        tmp_i3 = GHIDRA_FIELD(g_maxclients, 12, 4);
        do {
          if ((&g_unk_02a996a8)[tmp_i6 + local_c0 * 0x50] != -1) {
            COM_BitSet(&local_a4,(int)(&g_unk_02a996a8)[tmp_i6 + local_c0 * 0x50]);
            tmp_i3 = GHIDRA_FIELD(g_maxclients, 12, 4);
          }
          tmp_i6 = tmp_i6 + 1;
        } while (tmp_i6 < tmp_i3);
      }
      Com_sprintf(local_9c,0x80,"\\n\\%i\\l\\%i\\c\\%.8x%.8x",(&g_unk_02a996a4)[local_c0 * 0x14] + -1,
                  (int)(&g_unk_02a996a8)[local_c0 * 0x50],local_a0,local_a4);
    }
    nitrox_SetConfigstring((local_c0 * 0x50 >> 4) * -0x33333333 + 0x283,local_9c);
  }
LAB_0008007d:
  trap_SendServerCommand(param_2,"cpm \"You have been kicked from the fireteam\"\n");
  return;
}

void G_PrintBanners(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint8_t local_11c [268];
  
  tmp_u1 = va("g_msg%d",g_unk_02aa3f8c);
  trap_Cvar_VariableStringBuffer(tmp_u1,local_11c,0x100);
  tmp_i2 = Q_stricmp(local_11c,&g_unk_0026ea14);
  if (tmp_i2 == 0) {
    g_unk_02aa3f8c = 1;
    tmp_u1 = va("g_msg%d",1);
    trap_Cvar_VariableStringBuffer(tmp_u1,local_11c,0x100);
  }
  else {
    g_unk_02aa3f8c = g_unk_02aa3f8c + 1;
  }
  tmp_i2 = Q_stricmp(local_11c,&g_unk_0026ea14);
  if (tmp_i2 != 0) {
    if (g_unk_02aa3f8c == 1) {
      g_unk_02aa3f8c = 2;
    }
    tmp_u1 = va("bp %i \"%s\"",GHIDRA_FIELD(g_msgpos, 12, 4),local_11c);
    trap_SendServerCommand(0xffffffff,tmp_u1);
  }
  return;
}

void G_PlayerBan(void)
{
  int tmp_i1;
  int tmp_i2;
  char local_81c [1024];
  char local_41c [1036];
  
  trap_Argv(1,local_81c,0x400);
  if (local_81c[0] == '\0') {
    G_Printf("usage: ban <clientname>.");
  }
  else {
    tmp_i2 = 0;
    if (0 < g_unk_00abe938) {
      do {
        Q_strncpyz(local_41c,(&g_unk_00abe944)[tmp_i2] * 0x54dc + level + 0x5f8,0x400);
        Q_CleanStr(local_41c);
        tmp_i1 = strcmp(local_41c,local_81c);
        if (tmp_i1 == 0) {
          if ((&g_unk_00abe944)[tmp_i2] == 0x40) {
            return;
          }
          AddIPBan((&g_unk_00abe944)[tmp_i2] * 0x54dc + level + 0x63d);
          return;
        }
        tmp_i2 = tmp_i2 + 1;
      } while (tmp_i2 < g_unk_00abe938);
    }
    G_refPrintf_constprop_4(0,"Client not on server.");
  }
  return;
}

void G_MakeReferee(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  char local_81c [1024];
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xb86ce;
  trap_Argv(1,local_81c,0x400);
  if (local_81c[0] == '\0') {
    G_Printf("usage: MakeReferee <clientname>.");
    return;
  }
  tmp_i3 = 0;
  if (0 < g_unk_00abe938) {
    do {
      Q_strncpyz(local_41c,(&g_unk_00abe944)[tmp_i3] * 0x54dc + level + 0x5f8,0x400);
      Q_CleanStr(local_41c);
      tmp_i1 = strcmp(local_41c,local_81c);
      if (tmp_i1 == 0) {
        tmp_i3 = (&g_unk_00abe944)[tmp_i3];
        if (tmp_i3 == 0x40) {
          return;
        }
        tmp_i1 = tmp_i3 * 0x54dc + level;
        if (*(int *)(tmp_i1 + 0xc80) == 0) {
          *(uint32_t *)(tmp_i1 + 0xc80) = 1;
          tmp_u2 = va("cp \"%s\n^3has been made a referee\n\"",local_81c);
          trap_SendServerCommand(0xffffffff,tmp_u2);
          G_Printf("%s has been made a referee.\n",local_81c);
          ClientUserinfoChanged(tmp_i3);
          return;
        }
        G_Printf("User is already authed.\n");
        return;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 < g_unk_00abe938);
  }
  G_refPrintf_constprop_4(0,"Client not on server.");
  return;
}

void G_RemoveReferee(void)
{
  int tmp_i1;
  int tmp_i2;
  char local_81c [1024];
  char local_41c [1036];
  
  trap_Argv(1,local_81c,0x400);
  if (local_81c[0] == '\0') {
    G_Printf("usage: RemoveReferee <clientname>.");
  }
  else {
    tmp_i2 = 0;
    if (0 < g_unk_00abe938) {
      do {
        Q_strncpyz(local_41c,(&g_unk_00abe944)[tmp_i2] * 0x54dc + level + 0x5f8,0x400);
        Q_CleanStr(local_41c);
        tmp_i1 = strcmp(local_41c,local_81c);
        if (tmp_i1 == 0) {
          tmp_i2 = (&g_unk_00abe944)[tmp_i2];
          if (tmp_i2 == 0x40) {
            return;
          }
          tmp_i1 = tmp_i2 * 0x54dc + level;
          if (*(int *)(tmp_i1 + 0xc80) != 1) {
            G_Printf("User is not a referee.\n");
            return;
          }
          *(uint32_t *)(tmp_i1 + 0xc80) = 0;
          G_Printf("%s is no longer a referee.\n",local_81c);
          ClientUserinfoChanged(tmp_i2);
          return;
        }
        tmp_i2 = tmp_i2 + 1;
      } while (tmp_i2 < g_unk_00abe938);
    }
    G_refPrintf_constprop_4(0,"Client not on server.");
  }
  return;
}

void G_MuteClient(void)
{
  int tmp_i1;
  int tmp_i2;
  char local_81c [1024];
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xb89de;
  trap_Argv(1,local_81c,0x400);
  if (local_81c[0] == '\0') {
    G_Printf("usage: Mute <clientname>.");
    return;
  }
  tmp_i2 = 0;
  if (0 < g_unk_00abe938) {
    do {
      Q_strncpyz(local_41c,(&g_unk_00abe944)[tmp_i2] * 0x54dc + level + 0x5f8,0x400);
      Q_CleanStr(local_41c);
      tmp_i1 = strcmp(local_41c,local_81c);
      if (tmp_i1 == 0) {
        tmp_i2 = (&g_unk_00abe944)[tmp_i2];
        if (tmp_i2 == 0x40) {
          return;
        }
        if (*(int *)(level + 0xc80 + tmp_i2 * 0x54dc) != 2) {
          trap_SendServerCommand(tmp_i2,"cpm \"^3You have been muted\"");
          tmp_i1 = tmp_i2 * 0x54dc + level;
          *(uint32_t *)(tmp_i1 + 0xbf0) = 1;
          *(uint32_t *)(tmp_i1 + 0xca4) = 0xffffffff;
          G_Printf("%s^7 has been muted\n",local_81c);
          ClientUserinfoChanged(tmp_i2);
          return;
        }
        G_Printf("Cannot mute a referee.\n");
        return;
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 < g_unk_00abe938);
  }
  G_refPrintf_constprop_4(0,"Client not on server.");
  return;
}

void G_UnMuteClient(void)
{
  int tmp_i1;
  int tmp_i2;
  char local_81c [1024];
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xb8b7e;
  trap_Argv(1,local_81c,0x400);
  if (local_81c[0] == '\0') {
    G_Printf("usage: Unmute <clientname>.\n");
    return;
  }
  tmp_i2 = 0;
  if (0 < g_unk_00abe938) {
    do {
      Q_strncpyz(local_41c,(&g_unk_00abe944)[tmp_i2] * 0x54dc + level + 0x5f8,0x400);
      Q_CleanStr(local_41c);
      tmp_i1 = strcmp(local_41c,local_81c);
      if (tmp_i1 == 0) {
        tmp_i2 = (&g_unk_00abe944)[tmp_i2];
        if (tmp_i2 == 0x40) {
          return;
        }
        if (*(int *)(level + 0xbf0 + tmp_i2 * 0x54dc) != 0) {
          trap_SendServerCommand(tmp_i2,"cpm \"^2You have been un-muted\"");
          tmp_i1 = tmp_i2 * 0x54dc + level;
          *(uint32_t *)(tmp_i1 + 0xbf0) = 0;
          *(uint32_t *)(tmp_i1 + 0xca4) = 0xffffffff;
          G_Printf("%s has been un-muted\n",local_81c);
          ClientUserinfoChanged(tmp_i2);
          return;
        }
        G_Printf("User is not muted.\n");
        return;
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 < g_unk_00abe938);
  }
  G_refPrintf_constprop_4(0,"Client not on server.");
  return;
}

void G_refMute_cmd(uint32_t param_1,int param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  int tmp_i3;
  int tmp_i4;
  uint8_t local_41c [1036];
  
  trap_Argv(2,local_41c,0x400);
  tmp_i3 = ClientNumberFromString(param_1,local_41c);
  if (tmp_i3 != -1) {
    tmp_i4 = tmp_i3 * 0x600;
    tmp_i1 = *(int *)(g_entities + tmp_i4 + 400);
    if ((param_2 == 0) || (*(int *)(tmp_i1 + 0xc80) == 0)) {
      if (*(int *)(tmp_i1 + 0xbf0) == param_2) {
        if (param_2 == 0) {
          tmp_pc2 = "Player is not muted!";
        }
        else {
          tmp_pc2 = "Player is already muted!";
        }
        G_refPrintf(param_1,&g_unk_0024e6e2,tmp_i1 + 0x5f8,tmp_pc2 + 7);
      }
      else {
        if (param_2 == 0) {
          trap_SendServerCommand(tmp_i3,"print \"^5You\'ve been unmuted\n\"");
          *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0xbf0) = 0;
          *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0xca4) = 0xffffffff;
          G_Printf("\"%s^7\" has been unmuted\n",*(int *)(g_entities + tmp_i4 + 400) + 0x5f8);
        }
        else {
          trap_SendServerCommand(tmp_i3,"print \"^5You\'ve been muted\n\"");
          *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0xbf0) = 1;
          *(uint32_t *)(*(int *)(g_entities + tmp_i4 + 400) + 0xca4) = 0xffffffff;
          G_Printf("\"%s^7\" has been muted\n",*(int *)(g_entities + tmp_i4 + 400) + 0x5f8);
        }
        ClientUserinfoChanged(tmp_i3);
      }
    }
    else {
      G_refPrintf(param_1,"Cannot mute a referee.");
    }
  }
  return;
}

void G_refWarning_cmd(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  int tmp_i4;
  char local_c1c [1024];
  char local_81c [1024];
  char local_41c [1036];
  
  trap_Argv(2,local_c1c,0x400);
  if (local_c1c[0] == '\0') {
    G_refPrintf(param_1,"usage: ref warn <clientname> [reason].");
  }
  else {
    trap_Argv(3,local_81c,0x400);
    if (local_c1c[0] != '\0') {
      if (0 < g_unk_00abe938) {
        tmp_i4 = 0;
        do {
          Q_strncpyz(local_41c,(&g_unk_00abe944)[tmp_i4] * 0x54dc + level + 0x5f8,0x400);
          Q_CleanStr(local_41c);
          tmp_i1 = strcmp(local_41c,local_c1c);
          if (tmp_i1 == 0) {
            if ((&g_unk_00abe944)[tmp_i4] == 0x40) {
              return;
            }
            tmp_i1 = (&g_unk_00abe944)[tmp_i4] * 0x54dc + level;
            tmp_i4 = *(int *)(tmp_i1 + 0xc80);
            if ((tmp_i4 != 0) &&
               (((param_1 != 0 && (*(int *)(*(int *)(param_1 + 400) + 0xc80) != 2)) || (1 < tmp_i4)))
               ) {
              G_refPrintf(param_1,"Insufficient rights to issue client a warning.");
              return;
            }
            tmp_pc3 = local_81c;
            if (local_81c[0] == '\0') {
              tmp_pc3 = "No Reason Supplied";
            }
            tmp_u2 = va("cpm \"%s^7 was issued a ^1Warning^7 (%s)\n\"\n",tmp_i1 + 0x5f8,tmp_pc3);
            trap_SendServerCommand(0xffffffff,tmp_u2);
            return;
          }
          tmp_i4 = tmp_i4 + 1;
        } while (tmp_i4 < g_unk_00abe938);
      }
      G_refPrintf(param_1,"Client not on server.");
    }
  }
  return;
}

bool G_shrubbot_time(void)
{
  time_t tVar1;
  tm *__tp;
  uint32_t tmp_u2;
  time_t local_44;
  char local_3e [54];
  
  tVar1 = time(&local_44);
  if (tVar1 != 0) {
    __tp = localtime(&local_44);
    strftime(local_3e,0x32,"%I:%M%p %Z",__tp);
    tmp_u2 = va("chat \"^xtime:^g %s\" -2",local_3e);
    trap_SendServerCommand(0xffffffff,tmp_u2);
  }
  return tVar1 != 0;
}

uint32_t G_shrubbot_spec999(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  
  if (0 < g_unk_00abe900) {
    tmp_i4 = 0;
    tmp_i3 = g_unk_00abe900;
    tmp_pu5 = g_entities;
    do {
      while ((((tmp_i1 = *(int *)(tmp_pu5 + 400), tmp_i1 == 0 || (*(int *)(tmp_i1 + 0x5ac) != 2)) ||
              (*(int *)(tmp_i1 + 3000) == 3)) || (*(int *)(tmp_i1 + 0x468) != 999))) {
        tmp_i4 = tmp_i4 + 1;
        tmp_pu5 = tmp_pu5 + 0x600;
        if (tmp_i3 <= tmp_i4) {
          return 1;
        }
      }
      tmp_i4 = tmp_i4 + 1;
      SetTeam(tmp_pu5,&g_unk_0024e6ea,1,0xffffffff,0xffffffff,0);
      tmp_u2 = va("cpm \"^xspec999: ^7%s ^9moved to spectators^7\" -1",*(int *)(tmp_pu5 + 400) + 0x5f8
                );
      trap_SendServerCommand(0xffffffff,tmp_u2);
      tmp_i3 = g_unk_00abe900;
      tmp_pu5 = tmp_pu5 + 0x600;
    } while (tmp_i4 < g_unk_00abe900);
  }
  return 1;
}

uint32_t G_shrubbot_pause(uint32_t param_1)
{
  G_refPause_cmd(param_1,1);
  return 1;
}

uint32_t G_shrubbot_unpause(uint32_t param_1)
{
  G_refPause_cmd(param_1,0);
  return 1;
}

uint32_t G_shrubbot_shuffle(void)
{
  G_shuffleTeams();
  return 1;
}

uint32_t G_shrubbot_medpack(int param_1)
{
  float tmp_f1;
  uint tmp_u2;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  if (param_1 != 0) {
    tmp_u2 = rand();
    local_18 = (float)(tmp_u2 & 0x7fff) / 32767.0 - 0.5;
    local_18 = local_18 + local_18;
    tmp_u2 = rand();
    local_18 = local_18 * 100.0;
    tmp_f1 = (float)(tmp_u2 & 0x7fff) / 32767.0 - 0.5;
    local_14 = (tmp_f1 + tmp_f1) * 100.0;
    local_10 = (float)(int)GHIDRA_FIELD(g_throwDistance, 12, 4);
    local_24 = *(uint32_t *)(param_1 + 0x168);
    local_20 = *(uint32_t *)(param_1 + 0x16c);
    local_1c = *(uint32_t *)(param_1 + 0x170);
    Weapon_Medic_Ext(param_1,&local_24,&local_24,&local_18);
    return 1;
  }
  return 0;
}

uint32_t G_shrubbot_ammopack(int param_1)
{
  float tmp_f1;
  uint tmp_u2;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  if (param_1 != 0) {
    tmp_u2 = rand();
    local_18 = (float)(tmp_u2 & 0x7fff) / 32767.0 - 0.5;
    local_18 = local_18 + local_18;
    tmp_u2 = rand();
    local_18 = local_18 * 100.0;
    tmp_f1 = (float)(tmp_u2 & 0x7fff) / 32767.0 - 0.5;
    local_14 = (tmp_f1 + tmp_f1) * 100.0;
    local_10 = (float)(int)GHIDRA_FIELD(g_throwDistance, 12, 4);
    local_24 = *(uint32_t *)(param_1 + 0x168);
    local_20 = *(uint32_t *)(param_1 + 0x16c);
    local_1c = *(uint32_t *)(param_1 + 0x170);
    Weapon_MagicAmmo_Ext(param_1,&local_24,&local_24,&local_18);
    return 1;
  }
  return 0;
}

uint32_t G_shrubbot_news(uint32_t param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t local_40c [1024];
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_40c);
  }
  else {
    Q_strncpyz(local_40c,&g_unk_00abe8c0,0x400);
  }
  tmp_u2 = va("sound/vo/%s/news_%s.wav",local_40c,local_40c);
  G_globalSound(tmp_u2);
  return 1;
}

uint32_t G_shrubbot_swap_restart(void)
{
  Svcmd_SwapTeams_f();
  trap_SendServerCommand
            (0xffffffff,"chat \"^xswap_restart: ^9Teams swapped, match restarting^7\" -2");
  return 1;
}

uint32_t G_shrubbot_swap(void)
{
  G_swapTeams();
  trap_SendServerCommand(0xffffffff,"chat \"^xswap: ^9Teams swapped^7\" -2");
  return 1;
}

uint32_t G_shrubbot_reset(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  uint8_t local_1d [21];
  
  Q_SayArgv(param_2,local_1d,0x11);
  tmp_i1 = Q_stricmp(local_1d,"reset");
  if (tmp_i1 == 0) {
    Svcmd_ResetMatch_f(0,1);
  }
  else {
    Svcmd_ResetMatch_f(1,1);
  }
  return 1;
}

uint32_t G_shrubbot_nextmap(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 4) {
    tmp_i2 = g_unk_02a98490 * 0x494;
    if (*(int *)(g_campaigns + tmp_i2 + 0x284) + 1 < *(int *)(g_campaigns + tmp_i2 + 0x280)) {
      tmp_u1 = va("%i",*(int *)(g_campaigns + tmp_i2 + 0x284) + 1);
      trap_Cvar_Set("g_currentCampaignMap",tmp_u1);
      tmp_u1 = va("map %s\n",g_campaigns + tmp_i2 + (*(int *)(g_campaigns + tmp_i2 + 0x284) + 1) * 0x40
                );
      trap_SendConsoleCommand(2,tmp_u1);
    }
    else {
      trap_SendConsoleCommand(2,"vstr nextcampaign\n");
    }
  }
  else if ((GHIDRA_FIELD(g_gametype, 12, 4) == 6) && ((g_mapVoteFlags[0xc] & 0x10) != 0)) {
    LogExit("Nextmap forced by admin");
    trap_SendServerCommand
              (0xffffffff,"chat \"^3*** Nextmap forced by admin! Choose a new map! ***\" -2");
  }
  else {
    trap_SendConsoleCommand(2,"vstr nextmap\n");
  }
  return 1;
}

uint32_t G_shrubbot_mute_check_part_6(char *param_1,char *param_2)
{
  time_t tVar1;
  int tmp_i2;
  size_t tmp_s3;
  int tmp_i4;
  uint32_t tmp_u5;
  int *tmp_pi6;
  int tmp_i7;
  int local_44;
  int local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0xc8e1d;
  tVar1 = time(local_20);
  if ((tVar1 != 0) && (local_20[0] = local_20[0] + -0x386a4c20, Mutes != 0)) {
    tmp_pi6 = &Mutes;
    local_44 = 0;
    tmp_i2 = Mutes;
    do {
      tmp_i2 = Q_stricmp(param_1,tmp_i2 + 0x24);
      if (tmp_i2 == 0) {
        tmp_i4 = *tmp_pi6;
        tmp_i2 = *(int *)(tmp_i4 + 0x48c);
        if ((tmp_i2 != 0) && (tmp_i2 == local_20[0] || tmp_i2 - local_20[0] < 0)) goto LAB_000c8fb4;
      }
      tmp_s3 = strlen(param_1);
      if ((tmp_s3 == 0x20) && (tmp_i2 = Q_stricmp(*tmp_pi6 + 0x24,param_1), tmp_i2 == 0)) {
        return 1;
      }
      if (*param_2 != '\0') {
        tmp_i2 = Q_stricmp(param_2,*tmp_pi6 + 0x4b4);
        if (tmp_i2 == 0) {
          tmp_i4 = *tmp_pi6;
          tmp_i2 = *(int *)(tmp_i4 + 0x48c);
          if ((tmp_i2 != 0) && (tmp_i2 == local_20[0] || tmp_i2 - local_20[0] < 0)) {
LAB_000c8fb4:
            if (0 < g_unk_00abe938) {
              tmp_i2 = 0;
              while( true ) {
                tmp_i7 = (&g_unk_00abe944)[tmp_i2] * 0x600;
                tmp_i4 = Q_stricmp(tmp_i4 + 0x24,*(int *)(g_entities + tmp_i7 + 400) + 0x61c);
                if ((tmp_i4 == 0) ||
                   ((*param_2 != '\0' &&
                    (tmp_i4 = Q_stricmp((&Mutes)[local_44] + 0x4b4,
                                       *(int *)(g_entities + tmp_i7 + 400) + 0xaf4), tmp_i4 == 0)))) {
                  *(uint32_t *)(*(int *)(g_entities + tmp_i7 + 400) + 0xbf0) = 0;
                  *(uint32_t *)(*(int *)(g_entities + tmp_i7 + 400) + 0xca4) = 0xffffffff;
                  tmp_u5 = va("pop \"^3Mute for player ^7%s ^3has expired\"",
                             *(int *)(g_entities + tmp_i7 + 400) + 0x5f8);
                  trap_SendServerCommand(0xffffffff,tmp_u5);
                }
                tmp_i2 = tmp_i2 + 1;
                if (g_unk_00abe938 <= tmp_i2) break;
                tmp_i4 = (&Mutes)[local_44];
              }
              tmp_i4 = (&Mutes)[local_44];
            }
            *(uint32_t *)(tmp_i4 + 0x4c8) = 0;
            *(uint32_t *)((&Mutes)[local_44] + 0x4cc) = 1;
            nitrox_SaveMutes(0,0);
            free((void *)(&Mutes)[local_44]);
            (&Mutes)[local_44] = 0;
            nitrox_LoadMutes();
            return 0;
          }
        }
        if (((*param_2 != '\0') && (tmp_i2 = Q_stricmp(param_2,"00-00-00-00-00-00"), tmp_i2 != 0)) &&
           (tmp_i2 = Q_stricmp(*tmp_pi6 + 0x4b4,param_2), tmp_i2 == 0)) {
          return 1;
        }
      }
      tmp_pi6 = tmp_pi6 + 1;
      tmp_i2 = *tmp_pi6;
      local_44 = local_44 + 1;
    } while (tmp_i2 != 0);
  }
  return 0;
}

void G_shrubbot_print_part_8(uint32_t param_1)
{
  uint8_t local_40c [1028];
  
  DecolorString(param_1,local_40c);
  G_Printf(local_40c);
  return;
}

uint32_t _shrubbot_command_permission(int param_1,uint32_t param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  int *tmp_pi4;
  
  if (g_unk_02af58b8 == 0) {
    if (param_1 == 0) {
      return 1;
    }
  }
  else {
    if (param_1 == 0) {
      return 1;
    }
    if (*(int *)(param_1 + 0x5e8) != 0) {
      tmp_i2 = GetUserPointer(param_1);
      tmp_i2 = **(int **)(tmp_i2 + 0x4c);
      goto LAB_000c917b;
    }
  }
  tmp_i2 = 0;
LAB_000c917b:
  tmp_i3 = CustomCommands;
  tmp_pi1 = &g_unk_02db0e44;
  do {
    if (tmp_i3 == 0) {
      return 0;
    }
    tmp_i3 = Q_stricmp(param_2,tmp_i3);
    if (tmp_i3 == 0) {
      tmp_i3 = *(int *)(tmp_pi1[-1] + 0x840);
      if (tmp_i3 != -1) {
        if (tmp_i3 == tmp_i2) {
          return 1;
        }
        tmp_pi4 = (int *)(tmp_pi1[-1] + 0x844);
        while (tmp_i3 = *tmp_pi4, tmp_i3 != -1) {
          tmp_pi4 = tmp_pi4 + 1;
          if (tmp_i3 == tmp_i2) {
            return 1;
          }
        }
      }
    }
    tmp_i3 = *tmp_pi1;
    tmp_pi1 = tmp_pi1 + 1;
  } while( true );
}

uint32_t G_shrubbot_splata(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  int local_20;
  
  if (g_unk_00abe93c < 1) {
    local_20 = 0;
  }
  else {
    tmp_i5 = 0;
    local_20 = 0;
    do {
      tmp_pu4 = g_entities + (&g_unk_00abe944)[tmp_i5] * 0x600;
      if ((tmp_pu4 == (uint8_t *)0x0) || (param_1 == 0)) {
LAB_000c9296:
        G_Damage(tmp_pu4,0,0,0,0,0,0x28,0);
        local_20 = local_20 + 1;
      }
      else {
        tmp_i1 = nitrox_GetAdminLevel(param_1,0);
        tmp_i2 = nitrox_GetAdminLevel(tmp_pu4,0);
        if (tmp_i2 <= tmp_i1) goto LAB_000c9296;
      }
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_i5 < g_unk_00abe93c);
  }
  tmp_u3 = va("cpm \"^xsplata: ^7%d ^9players splattered^7\"",local_20);
  trap_SendServerCommand(0xffffffff,tmp_u3);
  return 1;
}

uint32_t G_shrubbot_cancelvote(int param_1)
{
  uint32_t tmp_u1;
  
  g_unk_00abee54 = g_unk_00abe938;
  CheckVote();
  if (param_1 == 0) {
    G_shrubbot_print_part_8();
  }
  else {
    tmp_u1 = va("print \"%s\"","^xcancelvote: ^9Current vote has been canceled\n");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
  }
  return 1;
}

uint32_t G_shrubbot_passvote(int param_1)
{
  uint32_t tmp_u1;
  
  g_unk_00abee50 = g_unk_00abe938;
  g_unk_00abee54 = 0;
  CheckVote();
  if (param_1 != 0) {
    tmp_u1 = va("print \"%s\"","^xpassvote: ^9Current vote has been forced to pass\n");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
    return 1;
  }
  G_shrubbot_print_part_8();
  return 1;
}

uint32_t G_shrubbot_resetmyxp(int param_1)
{
  uint32_t tmp_u1;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    G_ResetXP(param_1);
    tmp_u1 = va("cpm \"^xresetmyxp: ^9XP has been reset for player ^7%s\"",
               *(int *)(param_1 + 400) + 0x5f8);
    trap_SendServerCommand(0xffffffff,tmp_u1);
    tmp_u1 = va("print \"%s\"","^xresetmyxp: ^7you have reset your XP\n");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
    return 1;
  }
  return 0;
}

void G_shrubbot_buffer_print_part_15(int param_1,uint32_t param_2)
{
  size_t tmp_s1;
  uint32_t tmp_u2;
  uint tmp_u3;
  uint tmp_u4;
  uint *tmp_pu5;
  uint *tmp_pu6;
  uint local_81c [256];
  uint8_t local_41c [1036];
  
  DecolorString(param_2,local_81c);
  tmp_pu6 = local_81c;
  do {
    tmp_pu5 = tmp_pu6;
    tmp_u3 = *tmp_pu5 + 0xfefefeff & ~*tmp_pu5;
    tmp_u4 = tmp_u3 & 0x80808080;
    tmp_pu6 = tmp_pu5 + 1;
  } while (tmp_u4 == 0);
  if ((tmp_u3 & 0x8080) == 0) {
    tmp_pu6 = (uint *)((int)tmp_pu5 + 6);
    tmp_u4 = tmp_u4 >> 0x10;
  }
  tmp_s1 = strlen(&bigTextBuffer);
  if (0xef < (int)tmp_pu6 + tmp_s1 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_81c))
  {
    if (param_1 == 0) {
      DecolorString(&bigTextBuffer,local_41c);
      G_Printf(local_41c);
    }
    else {
      tmp_u2 = va("print \"%s\"",&bigTextBuffer);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
    }
    bigTextBuffer = 0;
  }
  Q_strcat(&bigTextBuffer,100000,local_81c);
  return;
}

uint32_t G_shrubbot_disguise_part_12(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  Q_SayArgv(param_2 + 1,local_940,0x24);
  tmp_i1 = ClientNumbersFromString(local_940,local_91c);
  if (tmp_i1 == 1) {
    if (*(int *)(*(int *)(g_entities + local_91c[0] * 0x600 + 400) + 3000) - 1U < 2) {
      Cmd_GiveDisguise_f(g_entities + local_91c[0] * 0x600,param_2 + 1);
      return 1;
    }
    if (param_1 == 0) {
      tmp_pc3 = "^1disguise error: ^9Player must be on a team.^7\n";
LAB_000c979b:
      DecolorString(tmp_pc3,local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_u2 = va("print \"%s\"","^1disguise error: ^9Player must be on a team.^7\n");
  }
  else {
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_pc3 = (char *)va("^1disguise %s\n",local_81c);
    if (param_1 == 0) goto LAB_000c979b;
    tmp_u2 = va("print \"%s\"",tmp_pc3);
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  return 0;
}

uint32_t G_shrubbot_disguise(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 2 < tmp_i1) {
    tmp_u2 = G_shrubbot_disguise_part_12();
    return tmp_u2;
  }
  if (param_1 == 0) {
    G_shrubbot_print_part_8();
  }
  else {
    tmp_u2 = va("print \"%s\"","^9usage: ^g!disguise [name|slot#] [class]^7\n");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  }
  return 0;
}

uint32_t G_shrubbot_about(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = va("^9-- Mod informations\n");
  if (param_1 != 0) {
    tmp_u1 = va("print \"%s\"",tmp_u1);
    tmp_i2 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand(tmp_i2,tmp_u1);
    tmp_u1 = va(" ^9Version : ^7N^1!^7tmod ^g%s\n",&g_unk_00249e9e);
    tmp_u1 = va("print \"%s\"",tmp_u1);
    trap_SendServerCommand(tmp_i2,tmp_u1);
    tmp_u1 = va(" ^9Website : ^g%s \n","etmods.net");
    tmp_u1 = va("print \"%s\"",tmp_u1);
    trap_SendServerCommand(tmp_i2,tmp_u1);
    tmp_u1 = va(" ^9Build : ^g%s %s\n","linux-i386","Feb 14 2023");
    tmp_u1 = va("print \"%s\"",tmp_u1);
    trap_SendServerCommand(tmp_i2,tmp_u1);
    tmp_u1 = va(" ^9SQLite version : ^g%s\n","3.35.5");
    tmp_u1 = va("print \"%s\"",tmp_u1);
    trap_SendServerCommand(tmp_i2,tmp_u1);
    tmp_u1 = va("^9-- Dev. Team\n");
    tmp_u1 = va("print \"%s\"",tmp_u1);
    trap_SendServerCommand(tmp_i2,tmp_u1);
    tmp_u1 = va(" ^7N^1!^7trox^0*^9: ^gProject lead, programmer\n");
    tmp_u1 = va("print \"%s\"",tmp_u1);
    trap_SendServerCommand(tmp_i2,tmp_u1);
    tmp_u1 = va(" ^hN^7ico^h$^9: ^gProgrammer\n");
    tmp_u1 = va("print \"%s\"",tmp_u1);
    trap_SendServerCommand(tmp_i2,tmp_u1);
    tmp_u1 = va(" ^77Killer^9: ^gProgrammer\n");
    tmp_u1 = va("print \"%s\"",tmp_u1);
    trap_SendServerCommand(tmp_i2,tmp_u1);
    return 1;
  }
  G_shrubbot_print_part_8();
  va(" ^9Version : ^7N^1!^7tmod ^g%s\n",&g_unk_00249e9e);
  G_shrubbot_print_part_8();
  va(" ^9Website : ^g%s \n","etmods.net");
  G_shrubbot_print_part_8();
  va(" ^9Build : ^g%s %s\n","linux-i386","Feb 14 2023");
  G_shrubbot_print_part_8();
  va(" ^9SQLite version : ^g%s\n","3.35.5");
  G_shrubbot_print_part_8();
  va("^9-- Dev. Team\n");
  G_shrubbot_print_part_8();
  va(" ^7N^1!^7trox^0*^9: ^gProject lead, programmer\n");
  G_shrubbot_print_part_8();
  va(" ^hN^7ico^h$^9: ^gProgrammer\n");
  G_shrubbot_print_part_8();
  va(" ^77Killer^9: ^gProgrammer\n");
  G_shrubbot_print_part_8();
  return 1;
}

uint32_t G_shrubbot_revive_part_11(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  Q_SayArgv(param_2 + 1,local_940,0x24);
  tmp_i1 = ClientNumbersFromString(local_940,local_91c);
  if (tmp_i1 == 1) {
    local_91c[0] = local_91c[0] * 0x600;
    tmp_i1 = *(int *)(g_entities + local_91c[0] + 400);
    if (*(int *)(tmp_i1 + 3000) - 1U < 2) {
      if (*(int *)(g_entities + local_91c[0] + 0x2c8) < 1) {
        ReviveEntity(0,g_entities + local_91c[0]);
        return 1;
      }
      tmp_u2 = va("^1revive error: ^7%s ^9is alive.^7\n\n",tmp_i1 + 0x5f8);
    }
    else {
      tmp_u2 = va("^1revive error: ^7%s ^9is not in a team.^7\n",tmp_i1 + 0x5f8);
    }
    if (param_1 == 0) {
      G_shrubbot_print_part_8();
      return 0;
    }
    tmp_u2 = va("print \"%s\"",tmp_u2);
  }
  else {
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_u2 = va("^1revive %s\n",local_81c);
    if (param_1 == 0) {
      DecolorString(tmp_u2,local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_u2 = va("print \"%s\"",tmp_u2);
  }
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  return 0;
}

uint32_t G_shrubbot_revive(int param_1,int param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  
  tmp_i1 = Q_SayArgc();
  if (param_2 < tmp_i1) {
    tmp_u3 = G_shrubbot_revive_part_11();
    return tmp_u3;
  }
  if (param_1 != 0) {
    if (*(int *)(*(int *)(param_1 + 400) + 3000) - 1U < 2) {
      if (*(int *)(param_1 + 0x2c8) < 1) {
        ReviveEntity(0,param_1);
        return 1;
      }
      tmp_pc2 = "^1revive error: ^9You are alive.^7\n";
    }
    else {
      tmp_pc2 = "^1revive error: ^9You are not on a team.^7\n";
    }
    tmp_u3 = va("print \"%s\"",tmp_pc2);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
  }
  return 0;
}

uint32_t G_shrubbot_admintest(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  uint8_t *tmp_pu4;
  uint8_t *tmp_pu5;
  
  if (param_1 == 0) {
    G_shrubbot_print_part_8();
  }
  else {
    tmp_i1 = GetUserPointer(param_1);
    if (*(char *)(*(int *)(tmp_i1 + 0x4c) + 4) == '\0') {
      tmp_pu4 = &g_unk_0026ea14;
      tmp_pc3 = "^7";
      tmp_pu5 = tmp_pu4;
    }
    else {
      tmp_pu4 = &g_unk_002520ce;
      tmp_i1 = GetUserPointer(param_1);
      tmp_pc3 = "^9)^7";
      tmp_pu5 = (uint8_t *)(*(int *)(tmp_i1 + 0x4c) + 4);
    }
    tmp_u2 = nitrox_GetAdminLevel(param_1,0);
    tmp_u2 = va("chat \"^xadmintest: ^7%s ^9is a level ^x%d ^9user %s%s%s\" -2",
               *(int *)(param_1 + 400) + 0x5f8,tmp_u2,tmp_pu4,tmp_pu5,tmp_pc3);
    trap_SendServerCommand(0xffffffff,tmp_u2);
  }
  return 1;
}

uint32_t G_shrubbot_levinfo(int param_1,int param_2)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t *tmp_pu3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  char local_28 [24];
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_28,0xc);
    tmp_l2 = strtol(local_28,(char **)0x0,10);
    tmp_i1 = nitrox_LevelExists(tmp_l2);
    if (tmp_i1 == 0) {
      tmp_u4 = 0;
      if (param_1 == 0) {
        G_shrubbot_print_part_8();
      }
      else {
        tmp_u5 = va("print \"%s\"","^1levinfo error: ^9Unknown level^7\n");
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
      }
    }
    else {
      tmp_pu3 = (uint32_t *)nitrox_LevelPointer(tmp_l2);
      if (param_1 == 0) {
        G_shrubbot_print_part_8();
        va("^9Level : ^g%d\n",*tmp_pu3);
        G_shrubbot_print_part_8();
        va("^9Name  : ^g%s\n",tmp_pu3 + 1);
        G_shrubbot_print_part_8();
        va("^9Flags :^g%s\n",tmp_pu3 + 10);
        G_shrubbot_print_part_8();
        va("^9GText : ^g%s\n",tmp_pu3 + 0x10a);
        G_shrubbot_print_part_8();
        tmp_u4 = 1;
        va("^9GSound: ^g%s\n",tmp_pu3 + 0x20a);
        G_shrubbot_print_part_8();
      }
      else {
        tmp_u4 = va("print \"%s\"","^xlevinfo: ^9Level Informations\n");
        tmp_i1 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        trap_SendServerCommand(tmp_i1,tmp_u4);
        tmp_u4 = va("^9Level : ^g%d\n",*tmp_pu3);
        tmp_u4 = va("print \"%s\"",tmp_u4);
        trap_SendServerCommand(tmp_i1,tmp_u4);
        tmp_u4 = va("^9Name  : ^g%s\n",tmp_pu3 + 1);
        tmp_u4 = va("print \"%s\"",tmp_u4);
        trap_SendServerCommand(tmp_i1,tmp_u4);
        tmp_u4 = va("^9Flags :^g%s\n",tmp_pu3 + 10);
        tmp_u4 = va("print \"%s\"",tmp_u4);
        trap_SendServerCommand(tmp_i1,tmp_u4);
        tmp_u4 = va("^9GText : ^g%s\n",tmp_pu3 + 0x10a);
        tmp_u4 = va("print \"%s\"",tmp_u4);
        trap_SendServerCommand(tmp_i1,tmp_u4);
        tmp_u4 = 1;
        tmp_u5 = va("^9GSound: ^g%s\n",tmp_pu3 + 0x20a);
        tmp_u5 = va("print \"%s\"",tmp_u5);
        trap_SendServerCommand(tmp_i1,tmp_u5);
      }
    }
  }
  else if (param_1 == 0) {
    G_shrubbot_print_part_8();
    tmp_u4 = 0;
  }
  else {
    tmp_u4 = 0;
    tmp_u5 = va("print \"%s\"","^9usage: ^g!levinfo [level]^7\n");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
  }
  return tmp_u4;
}

uint32_t G_shrubbot_give(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t *tmp_pu3;
  uint8_t *tmp_pu4;
  char *tmp_pc5;
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    if (GHIDRA_FIELD(g_war, 12, 4) - 1 < 4) {
      if (param_1 != 0) {
        tmp_pc5 = "^1give error: ^9Not allowed during panzerwar/sniperwar !^7\n";
        goto LAB_000ca485;
      }
      tmp_pc5 = "^1give error: ^9Not allowed during panzerwar/sniperwar !^7\n";
    }
    else {
      Q_SayArgv(param_2 + 1,local_940,0x24);
      tmp_u2 = Q_SayConcatArgs(param_2 + 2);
      tmp_pu3 = (uint8_t *)Q_SayConcatArgs(param_2 + 3);
      tmp_pu4 = (uint8_t *)Q_SayConcatArgs(param_2 + 4);
      tmp_i1 = ClientNumbersFromString(local_940,local_91c);
      if (tmp_i1 == 1) {
        if (tmp_pu4 == (uint8_t *)0x0) {
          tmp_pu4 = &g_unk_0026ea14;
        }
        if (tmp_pu3 == (uint8_t *)0x0) {
          tmp_pu3 = &g_unk_0026ea14;
        }
        ExecGive(g_entities + local_91c[0] * 0x600,tmp_u2,tmp_pu3,tmp_pu4);
        return 1;
      }
      G_MatchOnePlayer(local_91c,local_81c,0x400);
      tmp_pc5 = (char *)va("^1give %s\n",local_81c);
      if (param_1 != 0) goto LAB_000ca485;
    }
    DecolorString(tmp_pc5,local_41c);
    G_Printf(local_41c);
  }
  else {
    tmp_pc5 = "^9usage: ^g!give [name|slot#] [item] [args]^7\n";
    if (param_1 == 0) {
      G_shrubbot_print_part_8();
      return 0;
    }
LAB_000ca485:
    tmp_u2 = va("print \"%s\"",tmp_pc5);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  }
  return 0;
}

uint32_t G_shrubbot_warn(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  int tmp_i6;
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 2 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_940,0x24);
    tmp_u2 = Q_SayConcatArgs(param_2 + 2);
    tmp_i3 = ClientNumbersFromString(local_940,local_91c);
    tmp_i1 = local_91c[0];
    if (tmp_i3 == 1) {
      if (param_1 == 0) {
        nitmod_Sound_Global(0xc);
        tmp_u5 = va("cpm \"^xwarn: ^7%s ^9was warned^7\"",
                   *(int *)(g_entities + tmp_i1 * 0x600 + 400) + 0x5f8);
        trap_SendServerCommand(0xffffffff,tmp_u5);
        tmp_pc4 = "^3SERVER CONSOLE";
      }
      else {
        tmp_i6 = local_91c[0] * 0x600;
        tmp_i1 = nitrox_GetAdminLevel(param_1,0);
        tmp_i3 = nitrox_GetAdminLevel(g_entities + tmp_i6,0);
        if (tmp_i1 < tmp_i3) {
          tmp_pc4 = "^1warn error: ^9Specified player has a higher admin level than you do.^7\n";
          goto LAB_000ca63c;
        }
        nitmod_Sound_Global(0xc);
        tmp_u5 = va("cpm \"^xwarn: ^7%s ^9was warned^7\"",*(int *)(g_entities + tmp_i6 + 400) + 0x5f8)
        ;
        trap_SendServerCommand(0xffffffff,tmp_u5);
        tmp_pc4 = (char *)(*(int *)(param_1 + 400) + 0x5f8);
      }
      tmp_u2 = va("cp \"^7%s ^xwarned ^9you because:\n^x%s\"",tmp_pc4,tmp_u2);
      trap_SendServerCommand(local_91c[0],tmp_u2);
      return 1;
    }
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_pc4 = (char *)va("^1warn %s\n",local_81c);
    if (param_1 == 0) goto LAB_000ca7b1;
  }
  else {
    if (param_1 == 0) {
      tmp_pc4 = "^9usage: ^g!warn [name|slot#] [reason]^7\n";
LAB_000ca7b1:
      DecolorString(tmp_pc4,local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_pc4 = "^9usage: ^g!warn [name|slot#] [reason]^7\n";
  }
LAB_000ca63c:
  tmp_u2 = va("print \"%s\"",tmp_pc4);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  return 0;
}

uint32_t G_shrubbot_resetxp(int param_1,int param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  char *tmp_pc5;
  char *tmp_pc6;
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_940,0x24);
    tmp_pc2 = (char *)ConcatArgs(param_2 + 2);
    tmp_i1 = ClientNumbersFromString(local_940,local_91c);
    if (tmp_i1 == 1) {
      tmp_i1 = local_91c[0] * 0x600;
      if (param_1 == 0) {
        G_ResetXP(g_entities + tmp_i1);
        tmp_u3 = va("cpm \"^xresetxp: ^9XP has been reset for player ^7%s\"",
                   *(int *)(g_entities + tmp_i1 + 400) + 0x5f8);
        trap_SendServerCommand(0xffffffff,tmp_u3);
        if (*tmp_pc2 == '\0') {
          tmp_pc6 = "";
          tmp_pc5 = "^3SERVER CONSOLE";
          tmp_pc2 = tmp_pc6;
        }
        else {
          tmp_pc6 = "^7 because:\n";
          tmp_pc5 = "^3SERVER CONSOLE";
        }
LAB_000caa33:
        tmp_u3 = va("chat \"^xresetxp ^7%s ^9has reset your XP %s%s\" -2",tmp_pc5,tmp_pc6,tmp_pc2);
        trap_SendServerCommand(local_91c[0],tmp_u3);
        return 1;
      }
      tmp_i4 = nitrox_GetAdminLevel(param_1,0);
      tmp_i1 = nitrox_GetAdminLevel(g_entities + tmp_i1,0);
      if (tmp_i1 <= tmp_i4) {
        tmp_i1 = local_91c[0] * 0x600;
        G_ResetXP(g_entities + tmp_i1);
        tmp_u3 = va("cpm \"^xresetxp: ^9XP has been reset for player ^7%s\"",
                   *(int *)(g_entities + tmp_i1 + 400) + 0x5f8);
        trap_SendServerCommand(0xffffffff,tmp_u3);
        if ((param_1 + -0x93e4a0 >> 9) * -0x55555555 - local_91c[0] == 0) {
          return 1;
        }
        if (*tmp_pc2 == '\0') {
          tmp_pc6 = "";
          tmp_pc2 = tmp_pc6;
        }
        else {
          tmp_pc6 = "^7 because:\n";
        }
        tmp_pc5 = (char *)(*(int *)(param_1 + 400) + 0x5f8);
        goto LAB_000caa33;
      }
      tmp_u3 = va("print \"%s\"",
                 "^1resetxp error: ^9Specified player has a higher ^7 admin level than you.\n");
      goto LAB_000ca92b;
    }
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_pc2 = (char *)va("^1resetxp: %s\n",local_81c);
    if (param_1 == 0) goto LAB_000caab9;
  }
  else {
    if (param_1 == 0) {
      tmp_pc2 = "^9usage: ^g!resetxp [name|slot#] [reason]\n";
LAB_000caab9:
      DecolorString(tmp_pc2,local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_pc2 = "^9usage: ^g!resetxp [name|slot#] [reason]\n";
  }
  tmp_u3 = va("print \"%s\"",tmp_pc2);
LAB_000ca92b:
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
  return 0;
}

uint32_t G_shrubbot_rename(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 2 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_940,0x24);
    tmp_u2 = Q_SayConcatArgs(param_2 + 2);
    tmp_i3 = ClientNumbersFromString(local_940,local_91c);
    tmp_i1 = local_91c[0];
    if (tmp_i3 == 1) {
      if (param_1 != 0) {
        tmp_i3 = nitrox_GetAdminLevel(param_1,0);
        tmp_i1 = nitrox_GetAdminLevel(g_entities + tmp_i1 * 0x600,0);
        if (tmp_i3 < tmp_i1) {
          tmp_u2 = va("^1rename error: ^7%s ^9is a higher level admin than you are.^7\n",
                     *(int *)(g_entities + local_91c[0] * 0x600 + 400) + 0x5f8);
          tmp_u2 = va("print \"%s\"",tmp_u2);
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
          return 0;
        }
      }
      trap_GetUserinfo(local_91c[0],local_41c,0x400);
      tmp_u5 = Info_ValueForKey(local_41c,"name");
      tmp_u5 = va("cpm \"^xrename: ^7%s ^9renamed to ^7%s\"",tmp_u5,tmp_u2);
      trap_SendServerCommand(0xffffffff,tmp_u5);
      Info_SetValueForKey(local_41c,"name",tmp_u2);
      trap_SetUserinfo(local_91c[0],local_41c);
      ClientCleanName(tmp_u2,*(int *)(g_entities + local_91c[0] * 0x600 + 400) + 0x5f8,0x24);
      ClientUserinfoChanged(local_91c[0]);
      return 1;
    }
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_pc4 = (char *)va("^1rename %s\n",local_81c);
    if (param_1 == 0) {
LAB_000cae41:
      DecolorString(tmp_pc4,local_41c);
      G_Printf(local_41c);
      return 0;
    }
  }
  else {
    if (param_1 == 0) {
      tmp_pc4 = "^9usage: ^g!rename [name] [newname]^7\n";
      goto LAB_000cae41;
    }
    tmp_pc4 = "^9usage: ^g!rename [name] [newname]^7\n";
  }
  tmp_u2 = va("print \"%s\"",tmp_pc4);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  return 0;
}

uint32_t G_shrubbot_unban(int param_1,int param_2)
{
  time_t tVar1;
  int tmp_i2;
  long tmp_l3;
  uint32_t tmp_u4;
  int local_14;
  char local_10 [4];
  
  tVar1 = time(&local_14);
  if (tVar1 != 0) {
    tmp_i2 = Q_SayArgc();
    if (param_2 + 1 < tmp_i2) {
      Q_SayArgv(param_2 + 1,local_10,4);
      tmp_l3 = strtol(local_10,(char **)0x0,10);
      if (0 < tmp_l3) {
        tmp_i2 = tmp_l3 + -1;
        if ((&Bans)[tmp_i2] != 0) {
          *(int *)((&Bans)[tmp_i2] + 0x48c) = local_14 + -0x386a4c20;
          tmp_u4 = va("^xunban: ^9ban ^g#%d ^9removed\n",tmp_l3);
          if (param_1 == 0) {
            G_shrubbot_print_part_8();
          }
          else {
            tmp_u4 = va("print \"%s\"",tmp_u4);
            trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
          }
          *(uint32_t *)((&Bans)[tmp_i2] + 0x4c8) = 0;
          *(uint32_t *)((&Bans)[tmp_i2] + 0x4cc) = 1;
          nitrox_SaveBans(0,0xffffffff);
          G_Printf("Reloading bans from database...\n");
          nitrox_LoadBans();
          return 1;
        }
      }
      if (param_1 == 0) {
        G_shrubbot_print_part_8();
      }
      else {
        tmp_u4 = va("print \"%s\"","^1unban error: ^9invalid ban #\n");
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
      }
    }
    else if (param_1 == 0) {
      G_shrubbot_print_part_8();
    }
    else {
      tmp_u4 = va("print \"%s\"","^9usage: ^g!unban [ban #]\n");
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
    }
  }
  return 0;
}

uint32_t G_shrubbot_spec(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1036];
  
  if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
    tmp_i1 = Q_SayArgc();
    if (param_2 + 1 < tmp_i1) {
      Q_SayArgv(param_2 + 1,local_540,0x24);
      tmp_i1 = ClientNumbersFromString(local_540,local_51c);
      if (tmp_i1 == 1) {
        tmp_i1 = *(int *)(g_entities + local_51c[0] * 0x600 + 400);
        tmp_i2 = *(int *)(param_1 + 400);
        if (*(int *)(tmp_i1 + 0xa0) == *(int *)(tmp_i2 + 0xa0)) {
          return 0;
        }
        if (*(int *)(tmp_i1 + 3000) == 3) {
          tmp_u3 = va("^1spec error: ^7%s ^9isn\'t on a team^7\n",tmp_i1 + 0x5f8);
          tmp_u3 = va("print \"%s\"",tmp_u3);
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
          return 0;
        }
        if (*(int *)(tmp_i2 + 3000) != 3) {
          SetTeam(param_1,&g_unk_0024e6ea,1,0xffffffff,0xffffffff,0);
          tmp_i2 = *(int *)(param_1 + 400);
        }
        *(uint32_t *)(tmp_i2 + 0xbc0) = 2;
        *(uint32_t *)(*(int *)(param_1 + 400) + 0xbc4) =
             *(uint32_t *)(*(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0xa0);
        tmp_u3 = va("^xspec: ^9Now following %s^7\n",
                   *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8);
        tmp_u3 = va("print \"%s\"",tmp_u3);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
        return 1;
      }
      G_MatchOnePlayer(local_51c,local_41c,0x400);
      tmp_pc4 = (char *)va("^1spec %s\n",local_41c);
    }
    else {
      tmp_pc4 = "^9usage: ^g!spec ^7[name|slot#]^7\n";
    }
    tmp_u3 = va("print \"%s\"",tmp_pc4);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
  }
  return 0;
}

uint32_t G_shrubbot_userdelete(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  uint8_t local_25 [21];
  
  if (param_1 == 0) {
    tmp_i1 = Q_SayArgc();
    if (tmp_i1 <= param_2) {
      G_shrubbot_print_part_8();
      return 0;
    }
    Q_SayArgv(param_2 + 1,local_25,9);
    if (Users == 0) {
      va("^1userdelete error: ^9Unknown UserID : ^g%s^7\n",local_25);
    }
    else {
LAB_000cb384:
      tmp_pu5 = local_25;
      tmp_i4 = 0;
      tmp_i1 = Users;
      do {
        tmp_i1 = Q_stricmp(tmp_pu5,tmp_i1 + 0x1c);
        if (tmp_i1 == 0) {
          nitrox_SaveSingleUser((&Users)[tmp_i4],0);
          tmp_u2 = va("^xuserdelete: ^9User ^7%s ^9(UserID ^g%s^9) successfully deleted from database^7\n"
                     ,(&Users)[tmp_i4] + 0x25,tmp_pu5);
          if (param_1 == 0) {
            G_shrubbot_print_part_8();
          }
          else {
            tmp_u2 = va("print \"%s\"",tmp_u2,tmp_pu5);
            trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
          }
          G_Printf("Reloading users from database...\n");
          nitrox_LoadUsers();
          return 0;
        }
        tmp_i4 = tmp_i4 + 1;
        tmp_i1 = (&Users)[tmp_i4];
      } while (tmp_i1 != 0);
      tmp_pc3 = (char *)va("^1userdelete error: ^9Unknown UserID : ^g%s^7\n",tmp_pu5);
      if (param_1 != 0) goto LAB_000cb44e;
    }
    G_shrubbot_print_part_8();
  }
  else {
    tmp_i1 = Nit_SecureShrubEnabled();
    if ((tmp_i1 != 0) && (*(int *)(*(int *)(param_1 + 400) + 0xf2c) == 0)) {
      Nit_SecureShrubError(param_1,"userdelete");
      return 0;
    }
    tmp_i1 = Q_SayArgc();
    if (param_2 < tmp_i1) {
      Q_SayArgv(param_2 + 1,local_25,9);
      if (Users != 0) goto LAB_000cb384;
      tmp_pc3 = (char *)va("^1userdelete error: ^9Unknown UserID : ^g%s^7\n",local_25);
    }
    else {
      tmp_pc3 = "^9usage: ^g!userdelete [UserID]^7\n";
    }
LAB_000cb44e:
    tmp_u2 = va("print \"%s\"",tmp_pc3);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  }
  return 0;
}

uint32_t G_shrubbot_orient(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1036];
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_540,0x24);
    tmp_i1 = ClientNumbersFromString(local_540,local_51c);
    if (tmp_i1 == 1) {
      tmp_i1 = *(int *)(g_entities + local_51c[0] * 0x600 + 400);
      if (*(int *)(tmp_i1 + 0x530c) == 0) {
        tmp_u2 = va("^1orient error: ^7%s ^9is not disoriented\n",tmp_i1 + 0x5f8);
        if (param_1 != 0) {
          tmp_u2 = va("print \"%s\"",tmp_u2);
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
          return 0;
        }
        G_shrubbot_print_part_8();
        return 0;
      }
      if ((*(byte *)(tmp_i1 + 0x6a) & 0x20) == 0) {
        *(uint32_t *)(tmp_i1 + 0x530c) = 0;
        tmp_u2 = va("cpm \"^xorient: ^7%s ^9is no longer disoriented\"",
                   *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8);
        trap_SendServerCommand(0xffffffff,tmp_u2);
        return 1;
      }
      tmp_pc3 = (char *)va("^1orient error: ^9Can\'t orient poisoned players\n");
      if (param_1 == 0) goto LAB_000cb721;
      tmp_u2 = va("print \"%s\"",tmp_pc3);
      goto LAB_000cb684;
    }
    G_MatchOnePlayer(local_51c,local_41c,0x400);
    tmp_pc3 = (char *)va("^1orient %s\n",local_41c);
    if (param_1 == 0) {
      G_shrubbot_print_part_8();
      return 0;
    }
  }
  else {
    if (param_1 == 0) {
      tmp_pc3 = "^9usage: ^g!orient [name|slot#]\n";
LAB_000cb721:
      DecolorString(tmp_pc3,local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_pc3 = "^9usage: ^g!orient [name|slot#]\n";
  }
  tmp_u2 = va("print \"%s\"",tmp_pc3);
LAB_000cb684:
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  return 0;
}

uint32_t G_shrubbot_putteam(int param_1,int param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint8_t local_947 [7];
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 2 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_940,0x24);
    Q_SayArgv(param_2 + 2,local_947,7);
    tmp_i1 = ClientNumbersFromString(local_940,local_91c);
    if (tmp_i1 == 1) {
      tmp_i1 = local_91c[0] * 0x600;
      if (param_1 == 0) {
        tmp_i1 = SetTeam(g_entities + tmp_i1,local_947,1,0xffffffff,0xffffffff,0);
        if (tmp_i1 == 0) {
          G_shrubbot_print_part_8();
          return 0;
        }
      }
      else {
        tmp_i4 = nitrox_GetAdminLevel(param_1,0);
        tmp_i1 = nitrox_GetAdminLevel(g_entities + tmp_i1,0);
        if (tmp_i4 < tmp_i1) {
          tmp_u3 = va("^1putteam error: ^7%s ^9is a higher level admin than you are.\n",
                     *(int *)(g_entities + local_91c[0] * 0x600 + 400) + 0x5f8);
          tmp_u3 = va("print \"%s\"",tmp_u3);
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
          return 0;
        }
        tmp_i1 = SetTeam(g_entities + local_91c[0] * 0x600,local_947,1,0xffffffff,0xffffffff,0);
        if (tmp_i1 == 0) {
          tmp_u3 = va("print \"%s\"","^1putteam error: ^9Put team failed^7\n");
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
          return 0;
        }
      }
      return 1;
    }
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_pc2 = (char *)va("^1putteam %s\n",local_81c);
    if (param_1 == 0) {
LAB_000cba21:
      DecolorString(tmp_pc2,local_41c);
      G_Printf(local_41c);
      return 0;
    }
  }
  else {
    if (param_1 == 0) {
      tmp_pc2 = "^9usage: ^g!putteam ^7[name] [r|b|s]\n";
      goto LAB_000cba21;
    }
    tmp_pc2 = "^9usage: ^g!putteam ^7[name] [r|b|s]\n";
  }
  tmp_u3 = va("print \"%s\"",tmp_pc2);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
  return 0;
}

uint32_t G_shrubbot_lock(int param_1,int param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  uint8_t local_31 [4];
  char local_2d;
  char local_2c [28];
  
  Q_SayArgv(param_2,&local_2d,0x11);
  tmp_pc4 = &local_2d;
  if (local_2d == '!') {
    tmp_pc4 = local_2c;
  }
  tmp_i1 = Q_SayArgc();
  if (tmp_i1 <= param_2 + 1) {
    tmp_u3 = va("^9usage: ^g!%s [r|b|s|all]^7\n",tmp_pc4);
joined_r0x000cbd18:
    if (param_1 == 0) {
      G_shrubbot_print_part_8();
      return 0;
    }
    tmp_u3 = va("print \"%s\"",tmp_u3);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
    return 0;
  }
  Q_SayArgv(param_2 + 1,local_31,4);
  tmp_i1 = Q_stricmp(local_31,"all");
  if (tmp_i1 == 0) {
    tmp_i1 = TeamCount(0xffffffff,1);
    GHIDRA_FIELD(teamInfo, 20, 4) = ZEXT14(tmp_i1 != 0);
    tmp_i1 = TeamCount(0xffffffff,2);
    GHIDRA_FIELD(teamInfo, 36, 4) = ZEXT14(tmp_i1 != 0);
    tmp_i1 = TeamCount(0xffffffff,1);
    G_updateSpecLock(1,tmp_i1 != 0);
    tmp_i1 = TeamCount(0xffffffff,2);
    G_updateSpecLock(2,tmp_i1 != 0);
    tmp_pc2 = "cpm \"^x%s: ^9All teams %sed^7\" -1";
LAB_000cbc17:
    g_unk_02a99a80 = g_unk_02a99a80 | 0x40;
    tmp_u3 = va(tmp_pc2,tmp_pc4,tmp_pc4);
    trap_SendServerCommand(0xffffffff,tmp_u3);
  }
  else {
    tmp_i1 = Q_stricmp(local_31,"r");
    if (tmp_i1 == 0) {
      tmp_i1 = TeamCount(0xffffffff,1);
      GHIDRA_FIELD(teamInfo, 20, 4) = ZEXT14(tmp_i1 != 0);
      tmp_pc2 = "cpm \"^x%s: ^9Axis team %sed^7\" -1";
    }
    else {
      tmp_i1 = Q_stricmp(local_31,&g_unk_0026dcfc);
      if (tmp_i1 != 0) {
        tmp_i1 = Q_stricmp(local_31,&g_unk_0024e6ea);
        if (tmp_i1 != 0) {
          tmp_u3 = va("^9usage: ^g!%s ^7r|b|s|all^7\n",tmp_pc4);
          goto joined_r0x000cbd18;
        }
        tmp_i1 = TeamCount(0xffffffff,1);
        G_updateSpecLock(1,tmp_i1 != 0);
        tmp_i1 = TeamCount(0xffffffff,2);
        G_updateSpecLock(2,tmp_i1 != 0);
        tmp_pc2 = "cpm \"^x%s: ^9Spectators %sed^7\" -1";
        goto LAB_000cbc17;
      }
      tmp_i1 = TeamCount(0xffffffff,2);
      GHIDRA_FIELD(teamInfo, 36, 4) = ZEXT14(tmp_i1 != 0);
      tmp_pc2 = "cpm \"^x%s: ^9Allied team %sed^7\" -1";
    }
    tmp_u3 = va(tmp_pc2,tmp_pc4,tmp_pc4);
    trap_SendServerCommand(0xffffffff,tmp_u3);
  }
  g_unk_02a99a80 = g_unk_02a99a80 | 0x20;
  tmp_u3 = va(&g_unk_00245ee9,g_unk_02a99a80,tmp_pc4);
  trap_SetConfigstring(0x1d,tmp_u3);
  return 1;
}

uint32_t G_shrubbot_unlock(int param_1,int param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  uint8_t local_31 [4];
  char local_2d;
  char local_2c [28];
  
  Q_SayArgv(param_2,&local_2d,0x11);
  tmp_pc4 = &local_2d;
  if (local_2d == '!') {
    tmp_pc4 = local_2c;
  }
  tmp_i1 = Q_SayArgc();
  if (tmp_i1 <= param_2 + 1) {
    tmp_u3 = va("^9usage: ^g!%s [r|b|s|all]^7\n",tmp_pc4);
joined_r0x000cc0a8:
    if (param_1 == 0) {
      G_shrubbot_print_part_8();
      return 0;
    }
    tmp_u3 = va("print \"%s\"",tmp_u3);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
    return 0;
  }
  Q_SayArgv(param_2 + 1,local_31,4);
  tmp_i1 = Q_stricmp(local_31,"all");
  if (tmp_i1 == 0) {
    TeamCount(0xffffffff,1);
    GHIDRA_FIELD(teamInfo, 20, 4) = 0;
    TeamCount(0xffffffff,2);
    GHIDRA_FIELD(teamInfo, 36, 4) = 0;
    TeamCount(0xffffffff,1);
    G_updateSpecLock(1,0);
    TeamCount(0xffffffff,2);
    G_updateSpecLock(2,0);
    tmp_pc2 = "cpm \"^x%s: ^9All teams %sed^7\" -1";
LAB_000cbf9f:
    g_unk_02a99a80 = g_unk_02a99a80 & 0xffffffbf;
    tmp_u3 = va(tmp_pc2,tmp_pc4,tmp_pc4);
    trap_SendServerCommand(0xffffffff,tmp_u3);
  }
  else {
    tmp_i1 = Q_stricmp(local_31,"r");
    if (tmp_i1 == 0) {
      TeamCount(0xffffffff,1);
      GHIDRA_FIELD(teamInfo, 20, 4) = 0;
      tmp_pc2 = "cpm \"^x%s: ^9Axis team %sed^7\" -1";
    }
    else {
      tmp_i1 = Q_stricmp(local_31,&g_unk_0026dcfc);
      if (tmp_i1 != 0) {
        tmp_i1 = Q_stricmp(local_31,&g_unk_0024e6ea);
        if (tmp_i1 != 0) {
          tmp_u3 = va("^9usage: ^g!%s ^7r|b|s|all^7\n",tmp_pc4);
          goto joined_r0x000cc0a8;
        }
        TeamCount(0xffffffff,1);
        G_updateSpecLock(1,0);
        TeamCount(0xffffffff,2);
        G_updateSpecLock(2,0);
        tmp_pc2 = "cpm \"^x%s: ^9Spectators %sed^7\" -1";
        goto LAB_000cbf9f;
      }
      TeamCount(0xffffffff,2);
      GHIDRA_FIELD(teamInfo, 36, 4) = 0;
      tmp_pc2 = "cpm \"^x%s: ^9Allied team %sed^7\" -1";
    }
    tmp_u3 = va(tmp_pc2,tmp_pc4,tmp_pc4);
    trap_SendServerCommand(0xffffffff,tmp_u3);
  }
  g_unk_02a99a80 = g_unk_02a99a80 & 0xffffffdf;
  tmp_u3 = va(&g_unk_00245ee9,g_unk_02a99a80,tmp_pc4);
  trap_SetConfigstring(0x1d,tmp_u3);
  return 1;
}

uint32_t G_shrubbot_levlist(int param_1)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  char *tmp_pc3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  
  if (param_1 != 0) {
    tmp_u1 = va("print \"%s\"",
               "^xlevlist:\n^9LVL | NAME\n^9---------------------------------------\n");
    tmp_i4 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand(tmp_i4,tmp_u1);
    if (Levels != (uint32_t *)0x0) {
      tmp_pu2 = Levels;
      tmp_pu5 = &g_unk_02db0c44;
      do {
        tmp_pc3 = (char *)(tmp_pu2 + 1);
        if (*(char *)(tmp_pu2 + 1) == '\0') {
          tmp_pc3 = "^gNO_NAME";
        }
        tmp_u1 = va(" ^g%2d ^9| ^g%s^7\n",*tmp_pu2,tmp_pc3);
        tmp_u1 = va("print \"%s\"",tmp_u1);
        trap_SendServerCommand(tmp_i4,tmp_u1);
        tmp_pu2 = (uint32_t *)*tmp_pu5;
        tmp_pu5 = tmp_pu5 + 1;
      } while (tmp_pu2 != (uint32_t *)0x0);
      tmp_i4 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    }
    tmp_u1 = va("print \"%s\"","^9---------------------------------------\n");
    trap_SendServerCommand(tmp_i4,tmp_u1);
    tmp_u1 = va("print \"%s\"","^9Use ^g!levinfo [level] ^9for specific infos about a level.^7\n");
    trap_SendServerCommand(tmp_i4,tmp_u1);
    return 1;
  }
  G_shrubbot_print_part_8();
  if (Levels != (uint32_t *)0x0) {
    tmp_pu2 = Levels;
    tmp_pu5 = &g_unk_02db0c44;
    do {
      tmp_pc3 = (char *)(tmp_pu2 + 1);
      if (*(char *)(tmp_pu2 + 1) == '\0') {
        tmp_pc3 = "^gNO_NAME";
      }
      va(" ^g%2d ^9| ^g%s^7\n",*tmp_pu2,tmp_pc3);
      G_shrubbot_print_part_8();
      tmp_pu2 = (uint32_t *)*tmp_pu5;
      tmp_pu5 = tmp_pu5 + 1;
    } while (tmp_pu2 != (uint32_t *)0x0);
  }
  G_shrubbot_print_part_8();
  G_shrubbot_print_part_8();
  return 1;
}

void nitrox_SetAdminCommandPermissions(int param_1)
{
  uint16_t *tmp_pu1;
  uint32_t *tmp_pu2;
  char *tmp_pc3;
  int tmp_i4;
  uint tmp_u5;
  uint tmp_u6;
  int tmp_i7;
  uint8_t **tmp_ppu8;
  bool tmp_b9;
  int local_20 [4];
  
  if (param_1 != 0) {
    if (*(char *)(param_1 + 0x50) != '\0') {
      local_20[0] = param_1 + 0x50;
      tmp_u5 = 0x138;
      tmp_pu1 = (uint16_t *)(param_1 + 0x10e8);
      tmp_b9 = ((uint)tmp_pu1 & 1) != 0;
      if (tmp_b9) {
        tmp_u5 = 0x137;
        *(uint8_t *)(param_1 + 0x10e8) = 0;
        tmp_pu1 = (uint16_t *)(param_1 + 0x10e9);
      }
      if (((uint)tmp_pu1 & 2) != 0) {
        *tmp_pu1 = 0;
        tmp_u5 = tmp_u5 - 2;
        tmp_pu1 = tmp_pu1 + 1;
      }
      tmp_u6 = 0;
      do {
        *(uint32_t *)((int)tmp_pu1 + tmp_u6) = 0;
        *(uint32_t *)((int)tmp_pu1 + tmp_u6 + 4) = 0;
        tmp_u6 = tmp_u6 + 8;
      } while (tmp_u6 < (tmp_u5 & 0xfffffff8));
      tmp_pu2 = (uint32_t *)((int)tmp_pu1 + tmp_u6);
      if ((tmp_u5 & 4) != 0) {
        *tmp_pu2 = 0;
        tmp_pu2 = tmp_pu2 + 1;
      }
      if ((tmp_u5 & 2) != 0) {
        *(uint16_t *)tmp_pu2 = 0;
        tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
      }
      if (tmp_b9) {
        *(uint8_t *)tmp_pu2 = 0;
      }
      do {
        tmp_pc3 = (char *)COM_ParseExt(local_20,0);
        if (tmp_pc3 == (char *)0x0) {
          return;
        }
        if (*tmp_pc3 == '\0') {
          return;
        }
        tmp_ppu8 = &g_shrubbot_cmds;
        tmp_i7 = 0;
        do {
          tmp_i4 = Q_stricmp(*tmp_ppu8,tmp_pc3);
          if (tmp_i4 == 0) {
            *(uint32_t *)(param_1 + 0x10e8 + tmp_i7 * 4) = 1;
            break;
          }
          tmp_i7 = tmp_i7 + 1;
          tmp_ppu8 = tmp_ppu8 + 5;
        } while (tmp_i7 != 0x4e);
      } while( true );
    }
    tmp_pu1 = (uint16_t *)(param_1 + 0x10e8);
    tmp_u5 = 0x138;
    tmp_b9 = ((uint)tmp_pu1 & 1) != 0;
    if (tmp_b9) {
      tmp_u5 = 0x137;
      *(uint8_t *)(param_1 + 0x10e8) = 0;
      tmp_pu1 = (uint16_t *)(param_1 + 0x10e9);
    }
    if (((uint)tmp_pu1 & 2) != 0) {
      *tmp_pu1 = 0;
      tmp_u5 = tmp_u5 - 2;
      tmp_pu1 = tmp_pu1 + 1;
    }
    tmp_u6 = 0;
    do {
      *(uint32_t *)((int)tmp_pu1 + tmp_u6) = 0;
      *(uint32_t *)((int)tmp_pu1 + tmp_u6 + 4) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < (tmp_u5 & 0xfffffff8));
    tmp_pu2 = (uint32_t *)((int)tmp_pu1 + tmp_u6);
    if ((tmp_u5 & 4) != 0) {
      *tmp_pu2 = 0;
      tmp_pu2 = tmp_pu2 + 1;
    }
    if ((tmp_u5 & 2) != 0) {
      *(uint16_t *)tmp_pu2 = 0;
      tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
    }
    if (tmp_b9) {
      *(uint8_t *)tmp_pu2 = 0;
    }
  }
  return;
}

void nitrox_SetLevelCommandPermissions(int param_1)
{
  uint16_t *tmp_pu1;
  uint32_t *tmp_pu2;
  char *tmp_pc3;
  int tmp_i4;
  uint tmp_u5;
  uint tmp_u6;
  int tmp_i7;
  uint8_t **tmp_ppu8;
  bool tmp_b9;
  int local_20 [4];
  
  if (param_1 != 0) {
    if (*(char *)(param_1 + 0x28) != '\0') {
      local_20[0] = param_1 + 0x28;
      tmp_u5 = 0x138;
      tmp_pu1 = (uint16_t *)(param_1 + 0xc30);
      tmp_b9 = ((uint)tmp_pu1 & 1) != 0;
      if (tmp_b9) {
        tmp_u5 = 0x137;
        *(uint8_t *)(param_1 + 0xc30) = 0;
        tmp_pu1 = (uint16_t *)(param_1 + 0xc31);
      }
      if (((uint)tmp_pu1 & 2) != 0) {
        *tmp_pu1 = 0;
        tmp_u5 = tmp_u5 - 2;
        tmp_pu1 = tmp_pu1 + 1;
      }
      tmp_u6 = 0;
      do {
        *(uint32_t *)((int)tmp_pu1 + tmp_u6) = 0;
        *(uint32_t *)((int)tmp_pu1 + tmp_u6 + 4) = 0;
        tmp_u6 = tmp_u6 + 8;
      } while (tmp_u6 < (tmp_u5 & 0xfffffff8));
      tmp_pu2 = (uint32_t *)((int)tmp_pu1 + tmp_u6);
      if ((tmp_u5 & 4) != 0) {
        *tmp_pu2 = 0;
        tmp_pu2 = tmp_pu2 + 1;
      }
      if ((tmp_u5 & 2) != 0) {
        *(uint16_t *)tmp_pu2 = 0;
        tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
      }
      if (tmp_b9) {
        *(uint8_t *)tmp_pu2 = 0;
      }
      do {
        tmp_pc3 = (char *)COM_ParseExt(local_20,0);
        if (tmp_pc3 == (char *)0x0) {
          return;
        }
        if (*tmp_pc3 == '\0') {
          return;
        }
        tmp_ppu8 = &g_shrubbot_cmds;
        tmp_i7 = 0;
        do {
          tmp_i4 = Q_stricmp(*tmp_ppu8,tmp_pc3);
          if (tmp_i4 == 0) {
            *(uint32_t *)(param_1 + 0xc30 + tmp_i7 * 4) = 1;
            break;
          }
          tmp_i7 = tmp_i7 + 1;
          tmp_ppu8 = tmp_ppu8 + 5;
        } while (tmp_i7 != 0x4e);
      } while( true );
    }
    tmp_pu1 = (uint16_t *)(param_1 + 0xc30);
    tmp_u5 = 0x138;
    tmp_b9 = ((uint)tmp_pu1 & 1) != 0;
    if (tmp_b9) {
      tmp_u5 = 0x137;
      *(uint8_t *)(param_1 + 0xc30) = 0;
      tmp_pu1 = (uint16_t *)(param_1 + 0xc31);
    }
    if (((uint)tmp_pu1 & 2) != 0) {
      *tmp_pu1 = 0;
      tmp_u5 = tmp_u5 - 2;
      tmp_pu1 = tmp_pu1 + 1;
    }
    tmp_u6 = 0;
    do {
      *(uint32_t *)((int)tmp_pu1 + tmp_u6) = 0;
      *(uint32_t *)((int)tmp_pu1 + tmp_u6 + 4) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < (tmp_u5 & 0xfffffff8));
    tmp_pu2 = (uint32_t *)((int)tmp_pu1 + tmp_u6);
    if ((tmp_u5 & 4) != 0) {
      *tmp_pu2 = 0;
      tmp_pu2 = tmp_pu2 + 1;
    }
    if ((tmp_u5 & 2) != 0) {
      *(uint16_t *)tmp_pu2 = 0;
      tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
    }
    if (tmp_b9) {
      *(uint8_t *)tmp_pu2 = 0;
    }
  }
  return;
}

int G_shrubbot_permission(int param_1,char *param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  char *tmp_pc3;
  uint8_t **tmp_ppu4;
  char *tmp_pc5;
  bool tmp_b6;
  byte tmp_b7;
  int local_34;
  int local_20 [3];
  uint32_t uStack_14;
  
  tmp_b7 = 0;
  uStack_14 = 0xcc74b;
  local_20[0] = 0;
  if (g_unk_02af58b8 != 0) {
    if (param_1 == 0) {
      return 1;
    }
    if (*(int *)(param_1 + 0x5e8) != 0) {
      tmp_i1 = GetUserPointer(param_1);
      local_20[0] = tmp_i1 + 0x50;
      if (*(char *)(tmp_i1 + 0x50) != '\0') {
        local_34 = 0;
        do {
          tmp_pc2 = (char *)COM_ParseExt(local_20,0);
          if ((tmp_pc2 == (char *)0x0) || (*tmp_pc2 == '\0')) {
            if (local_34 != 0) {
              return 1;
            }
            tmp_i1 = GetUserPointer(param_1);
            local_20[0] = *(int *)(tmp_i1 + 0x4c) + 0x28;
            if (*(char *)(*(int *)(tmp_i1 + 0x4c) + 0x28) == '\0') {
              return 0;
            }
            do {
              tmp_pc2 = (char *)COM_ParseExt(local_20,0);
              if (tmp_pc2 == (char *)0x0) {
                return local_34;
              }
              if (*tmp_pc2 == '\0') {
                return local_34;
              }
              tmp_i1 = Q_stricmp(tmp_pc2,"all");
              if (tmp_i1 == 0) {
                tmp_i1 = 9;
                tmp_b6 = true;
                tmp_pc3 = param_2;
                tmp_pc5 = "immunity";
                do {
                  if (tmp_i1 == 0) break;
                  tmp_i1 = tmp_i1 + -1;
                  tmp_b6 = *tmp_pc3 == *tmp_pc5;
                  tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
                  tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
                } while (tmp_b6);
                if (!tmp_b6) {
                  tmp_i1 = 10;
                  tmp_pc3 = param_2;
                  tmp_pc5 = "incognito";
                  do {
                    if (tmp_i1 == 0) break;
                    tmp_i1 = tmp_i1 + -1;
                    tmp_b6 = *tmp_pc3 == *tmp_pc5;
                    tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
                    tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
                  } while (tmp_b6);
                  if (!tmp_b6) {
                    tmp_i1 = 7;
                    tmp_pc3 = param_2;
                    tmp_pc5 = "novote";
                    do {
                      if (tmp_i1 == 0) break;
                      tmp_i1 = tmp_i1 + -1;
                      tmp_b6 = *tmp_pc3 == *tmp_pc5;
                      tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
                      tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
                    } while (tmp_b6);
                    if (!tmp_b6) {
                      tmp_i1 = 5;
                      tmp_pc3 = param_2;
                      tmp_pc5 = "nopm";
                      do {
                        if (tmp_i1 == 0) break;
                        tmp_i1 = tmp_i1 + -1;
                        tmp_b6 = *tmp_pc3 == *tmp_pc5;
                        tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
                        tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
                      } while (tmp_b6);
                      if (!tmp_b6) {
                        return 1;
                      }
                    }
                  }
                }
              }
              tmp_ppu4 = &g_shrubbot_cmds;
              do {
                tmp_i1 = Q_stricmp(*tmp_ppu4,tmp_pc2);
                if (tmp_i1 == 0) {
                  local_34 = 1;
                  break;
                }
                tmp_ppu4 = tmp_ppu4 + 5;
              } while (tmp_ppu4 != &g_ptr_DAT_002b40b8);
            } while( true );
          }
          tmp_i1 = Q_stricmp(tmp_pc2,"all");
          if (tmp_i1 == 0) {
            tmp_i1 = 9;
            tmp_b6 = true;
            tmp_pc3 = param_2;
            tmp_pc5 = "immunity";
            do {
              if (tmp_i1 == 0) break;
              tmp_i1 = tmp_i1 + -1;
              tmp_b6 = *tmp_pc3 == *tmp_pc5;
              tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
              tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
            } while (tmp_b6);
            if (!tmp_b6) {
              tmp_i1 = 10;
              tmp_pc3 = param_2;
              tmp_pc5 = "incognito";
              do {
                if (tmp_i1 == 0) break;
                tmp_i1 = tmp_i1 + -1;
                tmp_b6 = *tmp_pc3 == *tmp_pc5;
                tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
                tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
              } while (tmp_b6);
              if (!tmp_b6) {
                tmp_i1 = 7;
                tmp_pc3 = param_2;
                tmp_pc5 = "novote";
                do {
                  if (tmp_i1 == 0) break;
                  tmp_i1 = tmp_i1 + -1;
                  tmp_b6 = *tmp_pc3 == *tmp_pc5;
                  tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
                  tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
                } while (tmp_b6);
                if (!tmp_b6) {
                  tmp_i1 = 5;
                  tmp_pc3 = param_2;
                  tmp_pc5 = "nopm";
                  do {
                    if (tmp_i1 == 0) break;
                    tmp_i1 = tmp_i1 + -1;
                    tmp_b6 = *tmp_pc3 == *tmp_pc5;
                    tmp_pc3 = tmp_pc3 + (uint)tmp_b7 * -2 + 1;
                    tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
                  } while (tmp_b6);
                  if (!tmp_b6) {
                    return 1;
                  }
                }
              }
            }
          }
          tmp_ppu4 = &g_shrubbot_cmds;
          do {
            tmp_i1 = Q_stricmp(*tmp_ppu4,tmp_pc2);
            if (tmp_i1 == 0) {
              local_34 = 1;
              break;
            }
            tmp_ppu4 = tmp_ppu4 + 5;
          } while (tmp_ppu4 != &g_ptr_DAT_002b40b8);
        } while( true );
      }
    }
  }
  return 0;
}

bool _shrubbot_admin_higher(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  
  if ((param_1 != 0) && (param_2 != 0)) {
    tmp_i1 = nitrox_GetAdminLevel(param_1,0);
    tmp_i2 = nitrox_GetAdminLevel(param_2,0);
    return tmp_i2 <= tmp_i1;
  }
  return true;
}

void G_shrubbot_writeconfig_string(char *param_1,uint32_t param_2)
{
  uint tmp_u1;
  uint tmp_u2;
  uint *tmp_pu3;
  uint *tmp_pu4;
  uint local_40c [256];
  
  local_40c[0]._0_1_ = 0;
  if (*param_1 != '\0') {
    Q_strncpyz(local_40c,param_1,0x400);
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
    trap_FS_Write(local_40c,
                  (int)tmp_pu4 + ((-3 - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) - (int)local_40c),
                  param_2);
  }
  trap_FS_Write("\n",1,param_2);
  return;
}

void G_shrubbot_writeconfig_int(uint32_t param_1,uint32_t param_2)
{
  uint tmp_u1;
  uint tmp_u2;
  uint *tmp_pu3;
  uint *tmp_pu4;
  uint local_2c [8];
  
  Com_sprintf(local_2c,0x20,&g_unk_00245ee9,param_1);
  tmp_pu4 = local_2c;
  if ((char)local_2c[0] != '\0') {
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
    trap_FS_Write(local_2c,(int)tmp_pu4 +
                           ((-3 - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) - (int)local_2c),param_2);
  }
  trap_FS_Write("\n",1,param_2);
  return;
}

void G_shrubbot_readconfig_string(uint32_t param_1,char *param_2,uint param_3)
{
  char tmp_c1;
  char *__s;
  size_t tmp_s2;
  size_t tmp_s3;
  uint32_t tmp_u4;
  
  __s = (char *)COM_ParseExt(param_1,0);
  if ((*__s == '=') && (__s[1] == '\0')) {
    __s = (char *)COM_ParseExt(param_1,0);
  }
  else {
    tmp_u4 = COM_GetCurrentParseLine();
    G_Printf("^3readconfig: ^9warning missing ^g= ^9before \"^g%s\" ^9on line ^g%d\n",__s,tmp_u4);
  }
  *param_2 = '\0';
  tmp_c1 = '\0';
  if (*__s == '\0') {
    return;
  }
  do {
    if (tmp_c1 == '\0') {
      tmp_s3 = strlen(__s);
      if (param_3 < tmp_s3) goto LAB_000ccc57;
LAB_000ccc6d:
      Q_strcat(param_2,param_3,__s);
      Q_strcat(param_2,param_3,&g_unk_002612df);
    }
    else {
      tmp_s3 = strlen(__s);
LAB_000ccc57:
      tmp_s2 = strlen(param_2);
      if (tmp_s3 + tmp_s2 < param_3) goto LAB_000ccc6d;
    }
    __s = (char *)COM_ParseExt(param_1,0);
    if (*__s == '\0') {
      if (*param_2 == '\0') {
        return;
      }
      tmp_s3 = strlen(param_2);
      if (param_2[tmp_s3 - 1] != ' ') {
        return;
      }
      param_2[tmp_s3 - 1] = '\0';
      return;
    }
    tmp_c1 = *param_2;
  } while( true );
}

void G_shrubbot_readconfig_string_nico(uint32_t param_1,char *param_2,uint param_3)
{
  char tmp_c1;
  char *__s;
  size_t tmp_s2;
  size_t tmp_s3;
  
  __s = (char *)COM_ParseExt_nico(param_1,0);
  *param_2 = '\0';
  tmp_c1 = '\0';
  if (*__s == '\0') {
    return;
  }
  do {
    if (tmp_c1 == '\0') {
      tmp_s3 = strlen(__s);
      if (param_3 < tmp_s3) goto LAB_000ccd67;
LAB_000ccd7d:
      Q_strcat(param_2,param_3,__s);
      Q_strcat(param_2,param_3,&g_unk_002612df);
    }
    else {
      tmp_s3 = strlen(__s);
LAB_000ccd67:
      tmp_s2 = strlen(param_2);
      if (tmp_s3 + tmp_s2 < param_3) goto LAB_000ccd7d;
    }
    __s = (char *)COM_ParseExt_nico(param_1,0);
    if (*__s == '\0') {
      if (*param_2 == '\0') {
        return;
      }
      tmp_s3 = strlen(param_2);
      if (param_2[tmp_s3 - 1] != ' ') {
        return;
      }
      param_2[tmp_s3 - 1] = '\0';
      return;
    }
    tmp_c1 = *param_2;
  } while( true );
}

void G_shrubbot_readconfig_int(uint32_t param_1,long *param_2)
{
  char *__nptr;
  uint32_t tmp_u1;
  long tmp_l2;
  
  __nptr = (char *)COM_ParseExt(param_1,0);
  if ((*__nptr == '=') && (__nptr[1] == '\0')) {
    __nptr = (char *)COM_ParseExt(param_1,0);
  }
  else {
    tmp_u1 = COM_GetCurrentParseLine();
    G_Printf("^3readconfig: ^9warning missing ^g= ^9before \"^g%s\" ^9on line ^g%d\n",__nptr,tmp_u1);
  }
  tmp_l2 = strtol(__nptr,(char **)0x0,10);
  *param_2 = tmp_l2;
  return;
}

uint32_t _shrubbot_level(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = 0;
  if (g_unk_02af58b8 != 0) {
    if (param_1 == 0) {
      return 0x7fffffff;
    }
    if (*(int *)(param_1 + 0x5e8) != 0) {
      tmp_i2 = GetUserPointer(param_1);
      tmp_u1 = **(uint32_t **)(tmp_i2 + 0x4c);
    }
  }
  return tmp_u1;
}

void _shrubbot_log(int param_1,uint32_t param_2,int param_3)
{
  uint *tmp_pu1;
  uint tmp_u2;
  int tmp_i3;
  tm *__tp;
  uint32_t tmp_u4;
  char *tmp_pc5;
  uint tmp_u6;
  char *tmp_pc7;
  uint32_t tmp_u8;
  uint *tmp_pu9;
  uint *tmp_pu10;
  char *tmp_pc11;
  uint32_t local_45c;
  int local_458;
  char local_454 [20];
  char local_440 [4];
  uint auStack_43c [267];
  
  tmp_u2 = 0;
  local_440[0] = '\0';
  local_440[1] = '\0';
  local_440[2] = '\0';
  local_440[3] = '\0';
  do {
    *(uint32_t *)((int)auStack_43c + tmp_u2) = 0;
    *(uint32_t *)((int)auStack_43c + tmp_u2 + 4) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x20);
  if (g_logAdmin[0x10] != '\0') {
    tmp_i3 = trap_FS_FOpenFile(0x2e57f90,&local_45c,2);
    if (tmp_i3 < 0) {
      G_Printf("_shrubbot_log: error could not open %s\n",0x2e57f90);
    }
    else {
      local_458 = G_GetCurrentTime();
      if (local_458 == -1) {
        Q_strncpyz(local_454,"Time error!",0x14);
      }
      else {
        __tp = localtime(&local_458);
        strftime(local_454,0x14,"%Y-%m-%d %H:%M:%S",__tp);
      }
      tmp_u4 = Q_SayConcatArgs(param_3 + 1);
      if (param_1 != 0) {
        DecolorString(*(int *)(param_1 + 400) + 0x5f8,local_440);
      }
      tmp_i3 = Q_stricmp(param_2,"attempted");
      tmp_pc7 = local_440;
      if (tmp_i3 == 0) {
        if (local_440[0] == '\0') {
          tmp_pc7 = "console";
        }
        if (param_1 == 0) {
          tmp_pc11 = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
          tmp_u8 = 0xffffffff;
        }
        else {
          tmp_pc11 = (char *)(*(int *)(param_1 + 400) + 0x61c);
          tmp_u8 = *(uint32_t *)(param_1 + 0xac);
        }
        tmp_pc5 = "%s [%2i] [%s \'%s\']: %s \"%s\"\n";
      }
      else {
        if (local_440[0] == '\0') {
          tmp_pc7 = "console";
        }
        if (param_1 == 0) {
          tmp_pc11 = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
          tmp_u8 = 0xffffffff;
        }
        else {
          tmp_pc11 = (char *)(*(int *)(param_1 + 400) + 0x61c);
          tmp_u8 = *(uint32_t *)(param_1 + 0xac);
        }
        tmp_pc5 = "%s [%2i] [%s \'%s\']: %s %s\n";
      }
      tmp_pu1 = auStack_43c + 8;
      Com_sprintf(tmp_pu1,0x400,tmp_pc5,local_454,tmp_u8,tmp_pc11,tmp_pc7,param_2,tmp_u4);
      tmp_pu10 = tmp_pu1;
      do {
        tmp_pu9 = tmp_pu10;
        tmp_u6 = *tmp_pu9 + 0xfefefeff & ~*tmp_pu9;
        tmp_u2 = tmp_u6 & 0x80808080;
        tmp_pu10 = tmp_pu9 + 1;
      } while (tmp_u2 == 0);
      if ((tmp_u6 & 0x8080) == 0) {
        tmp_pu10 = (uint *)((int)tmp_pu9 + 6);
        tmp_u2 = tmp_u2 >> 0x10;
      }
      trap_FS_Write(tmp_pu1,(int)tmp_pu10 +
                           ((-3 - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) - (int)tmp_pu1),local_45c);
      trap_FS_FCloseFile(local_45c);
    }
  }
  return;
}

void G_shrubbot_duration(uint param_1,uint32_t param_2,uint32_t param_3)
{
  char *tmp_pc1;
  
  if (param_1 < 0x5dfc0f01) {
    if ((int)param_1 < 0x1e13380) {
      if ((int)param_1 < 0x278d00) {
        if ((int)param_1 < 0x93a80) {
          if ((int)param_1 < 0x15180) {
            if ((int)param_1 < 0xe10) {
              if ((int)param_1 < 0x3c) {
                tmp_pc1 = "%i secs";
              }
              else {
                tmp_pc1 = "%i mins";
                param_1 = (int)param_1 / 0x3c;
              }
            }
            else {
              tmp_pc1 = "%i hours";
              param_1 = (int)param_1 / 0xe10;
            }
          }
          else {
            tmp_pc1 = "%i days";
            param_1 = (int)param_1 / 0x15180;
          }
        }
        else {
          tmp_pc1 = "%i weeks";
          param_1 = (int)param_1 / 0x93a80;
        }
      }
      else {
        tmp_pc1 = "%i months";
        param_1 = (int)param_1 / 0x278d00;
      }
    }
    else {
      tmp_pc1 = "%d years";
      param_1 = (int)param_1 / 0x1e13380;
    }
    Com_sprintf(param_2,param_3,tmp_pc1,param_1);
    return;
  }
  Q_strncpyz(param_2,"PERMANENT",param_3);
  return;
}

int G_shrubbot_ban_check(char *param_1,char *param_2,int param_3,char *param_4)
{
  bool tmp_b1;
  char tmp_c2;
  time_t tVar3;
  size_t tmp_s4;
  int tmp_i5;
  char *tmp_pc6;
  int *tmp_pi7;
  int tmp_i8;
  int tmp_i9;
  int local_c8;
  int local_c4;
  int local_a0;
  uint8_t local_9c [136];
  uint32_t uStack_14;
  
  uStack_14 = 0xcd359;
  if (((g_unk_02af58b8 == 0) || (tVar3 = time(&local_a0), tVar3 == 0)) ||
     (local_a0 = local_a0 + -0x386a4c20, Bans == 0)) {
    local_c8 = 0;
  }
  else {
    tmp_pi7 = &Bans;
    local_c8 = 0;
    tmp_b1 = false;
    local_c4 = -1;
    tmp_i9 = 0;
    tmp_i5 = Bans;
    do {
      while( true ) {
        tmp_i8 = *(int *)(tmp_i5 + 0x48c);
        if ((tmp_i8 != 0) && (tmp_i8 == local_a0 || tmp_i8 - local_a0 < 0)) {
          *(uint32_t *)(tmp_i5 + 0x4c8) = 0;
          tmp_b1 = true;
          *(uint32_t *)(*tmp_pi7 + 0x4cc) = 1;
        }
        tmp_i5 = *tmp_pi7;
        if (*(int *)(tmp_i5 + 0x4cc) == 0) break;
LAB_000cd4e0:
        tmp_pi7 = tmp_pi7 + 1;
        tmp_i5 = *tmp_pi7;
        tmp_i9 = tmp_i9 + 1;
        if (tmp_i5 == 0) goto LAB_000cd4ef;
      }
      tmp_i8 = local_c4;
      if (((local_c8 == 0) &&
          ((tmp_s4 = strlen(param_2), tmp_i8 = tmp_i9, tmp_s4 != 0x20 ||
           (tmp_i5 = Q_stricmp(tmp_i5 + 0x24,param_2), tmp_i5 != 0)))) &&
         ((*param_4 == '\0' ||
          ((tmp_i5 = Q_stricmp(param_4,"00-00-00-00-00-00"), tmp_i5 == 0 ||
           (tmp_i5 = Q_stricmp(*tmp_pi7 + 0x4b4,param_4), tmp_i5 != 0)))))) {
        tmp_pc6 = (char *)(*tmp_pi7 + 0x45);
        if ((tmp_pc6 != (char *)0x0) && (tmp_c2 = *(char *)(*tmp_pi7 + 0x45), tmp_c2 != '\0')) {
          tmp_i8 = 0;
          tmp_i5 = 0;
          do {
            if (tmp_c2 == '.') {
              tmp_i5 = tmp_i5 + 1;
              tmp_c2 = tmp_pc6[tmp_i8 + 1];
            }
            else {
              if (9 < (byte)(tmp_c2 - 0x30U)) break;
              tmp_c2 = tmp_pc6[tmp_i8 + 1];
            }
            if (tmp_c2 == '\0') {
              if ((tmp_i8 + 1 != 0x10 && 6 < tmp_i8 + 1) && (tmp_i5 == 3)) {
                tmp_pc6 = strstr(param_1,tmp_pc6);
                if (tmp_pc6 != (char *)0x0) {
                  local_c8 = 1;
                  local_c4 = tmp_i9;
                }
              }
              break;
            }
            tmp_i8 = tmp_i8 + 1;
          } while (tmp_i8 != 0x10);
        }
        goto LAB_000cd4e0;
      }
      local_c4 = tmp_i8;
      tmp_pi7 = tmp_pi7 + 1;
      tmp_i5 = *tmp_pi7;
      tmp_i9 = tmp_i9 + 1;
      local_c8 = 1;
    } while (tmp_i5 != 0);
LAB_000cd4ef:
    if ((local_c8 != 0) && (param_3 != 0)) {
      G_shrubbot_duration(*(int *)((&Bans)[local_c4] + 0x48c) - local_a0,local_9c,0x80);
      Com_sprintf(param_3,0x400,"^7Reason: %s\n^7Expires in: %s.^7",(&Bans)[local_c4] + 0x57,
                  local_9c);
      local_c8 = 1;
    }
    if (tmp_b1) {
      nitrox_SaveBans(0,0);
      nitrox_LoadBans();
    }
  }
  return local_c8;
}

longlong G_shrubbot_mute_check(uint32_t param_1,uint param_2)
{
  longlong tmp_l1;
  
  if (g_unk_02af58b8 == 0) {
    return (ulonglong)param_2 << 0x20;
  }
  tmp_l1 = G_shrubbot_mute_check_part_6();
  return tmp_l1;
}

void G_shrubbot_greeting(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  
  if (param_1 == 0) {
    return;
  }
  if (g_unk_02af58b8 == 0) {
    return;
  }
  if (*(int *)(param_1 + 400) == 0) {
    return;
  }
  if (*(int *)(param_1 + 0x5e8) == 0) {
    return;
  }
  tmp_i1 = nitrox_CheckPermission(param_1,10);
  if (tmp_i1 == 0) {
    tmp_i1 = GetUserPointer(param_1);
    if (*(char *)(tmp_i1 + 0x850) == '\0') {
      tmp_i1 = GetUserPointer(param_1);
      if (*(char *)(*(int *)(tmp_i1 + 0x4c) + 0x828) != '\0') {
        tmp_i1 = GetUserPointer(param_1);
        tmp_i1 = *(int *)(tmp_i1 + 0x4c) + 0x828;
        goto LAB_000cd7ee;
      }
    }
    else {
      tmp_i1 = GetUserPointer(param_1);
      tmp_i1 = tmp_i1 + 0x850;
LAB_000cd7ee:
      tmp_u2 = va("gsnd %s",tmp_i1);
      trap_SendServerCommand(0xffffffff,tmp_u2);
    }
    tmp_i1 = GetUserPointer(param_1);
    if (*(char *)(tmp_i1 + 0x450) == '\0') {
      tmp_i1 = GetUserPointer(param_1);
      if (*(char *)(*(int *)(tmp_i1 + 0x4c) + 0x428) == '\0') {
        return;
      }
      tmp_i1 = GetUserPointer(param_1);
      tmp_i1 = *(int *)(tmp_i1 + 0x4c) + 0x428;
    }
    else {
      tmp_i1 = GetUserPointer(param_1);
      tmp_i1 = tmp_i1 + 0x450;
    }
  }
  else {
    tmp_i1 = nitrox_LevelPointer(0);
    if (*(char *)(tmp_i1 + 0x828) != '\0') {
      tmp_u2 = va("gsnd %s",tmp_i1 + 0x828);
      trap_SendServerCommand(0xffffffff,tmp_u2);
    }
    if (*(char *)(tmp_i1 + 0x428) == '\0') {
      return;
    }
    tmp_i1 = tmp_i1 + 0x428;
  }
  tmp_u2 = Q_StrReplace(tmp_i1,&g_unk_0024580c,*(int *)(param_1 + 400) + 0x5f8);
  if (GHIDRA_FIELD(n_greetingPos, 12, 4) == 2) {
    tmp_pc3 = "cpm \"%s\" -2";
    goto LAB_000cd7a0;
  }
  if ((int)GHIDRA_FIELD(n_greetingPos, 12, 4) < 3) {
    if (GHIDRA_FIELD(n_greetingPos, 12, 4) == 1) {
      tmp_pc3 = "cp \"%s\" -2";
      goto LAB_000cd7a0;
    }
  }
  else {
    if (GHIDRA_FIELD(n_greetingPos, 12, 4) == 3) {
      tmp_pc3 = "bp \"%s\" -2";
      goto LAB_000cd7a0;
    }
    if (GHIDRA_FIELD(n_greetingPos, 12, 4) == 4) {
      tmp_pc3 = "print \"%s\" -2";
      goto LAB_000cd7a0;
    }
  }
  tmp_pc3 = "chat \"%s\" -2";
LAB_000cd7a0:
  tmp_u2 = va(tmp_pc3,tmp_u2);
  trap_SendServerCommand(0xffffffff,tmp_u2);
  return;
}

uint32_t G_shrubbot_tempban(int param_1,char *param_2,int param_3)
{
  time_t tVar1;
  int tmp_i2;
  tm *__tp;
  int *tmp_pi3;
  int tmp_i4;
  int local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0xcd919;
  tVar1 = time(local_20);
  if (tVar1 != 0) {
    tmp_pi3 = (int *)(g_entities + param_1 * 0x600 + 400);
    tmp_i4 = *tmp_pi3;
    tmp_i2 = AllocBan(1);
    if (tmp_i2 != 0) {
      Q_strncpyz(tmp_i2,*tmp_pi3 + 0x5f8,0x24);
      Q_strncpyz(tmp_i2 + 0x24,tmp_i4 + 0x61c,0x21);
      Q_strncpyz(tmp_i2 + 0x4b4,*tmp_pi3 + 0xaf4,0x12);
      Q_strncpyz(tmp_i2 + 0x45,*tmp_pi3 + 0x653,0x12);
      __tp = localtime(local_20);
      strftime((char *)(tmp_i2 + 0x457),0x32,"%m/%d/%y %H:%M:%S",__tp);
      Q_strncpyz(tmp_i2 + 0x490,"Temp Ban System",0x24);
      *(int *)(tmp_i2 + 0x48c) = param_3 + -0x386a4c20 + local_20[0];
      if (*param_2 == '\0') {
        Q_strncpyz(tmp_i2 + 0x57,"banned by Temp Ban System",0x400);
      }
      else {
        Q_strncpyz(tmp_i2 + 0x57,param_2,0x400);
      }
      tmp_i4 = 0;
      if (Bans != 0) {
        tmp_i4 = 0;
        do {
          tmp_i4 = tmp_i4 + 1;
        } while ((&Bans)[tmp_i4] != 0);
      }
      nitrox_SaveSingleBan(tmp_i2,1);
      (&Bans)[tmp_i4] = tmp_i2;
      return 1;
    }
  }
  return 0;
}

uint32_t G_shrubbot_kick_part_9(int param_1,int param_2)
{
  char *tmp_pc1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  char *tmp_pc5;
  uint32_t tmp_u6;
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  Q_SayArgv(param_2 + 1,local_940,0x24);
  tmp_pc1 = (char *)Q_SayConcatArgs(param_2 + 2);
  tmp_i2 = ClientNumbersFromString(local_940,local_91c);
  tmp_i4 = local_91c[0];
  if (tmp_i2 == 1) {
    if (param_1 != 0) {
      tmp_i2 = nitrox_GetAdminLevel(param_1,0);
      tmp_i4 = nitrox_GetAdminLevel(g_entities + tmp_i4 * 0x600,0);
      if (tmp_i2 < tmp_i4) {
        tmp_u3 = va("^1kick error: ^7%s ^9is a higher level admin than you are.\n",
                   *(int *)(g_entities + local_91c[0] * 0x600 + 400) + 0x5f8);
        tmp_u3 = va("print \"%s\"",tmp_u3);
        goto LAB_000cdbad;
      }
    }
    tmp_u3 = GHIDRA_FIELD(g_autoTempBanTime, 12, 4);
    if ((*(int *)(*(int *)(g_entities + local_91c[0] * 0x600 + 400) + 0x5e8) == 0) ||
       ((g_entities[local_91c[0] * 0x600 + 0x128] & 8) == 0)) {
      if ((GHIDRA_FIELD(g_autoTempBan, 12, 4) != 0) && (GHIDRA_FIELD(g_autoTempBanTime, 12, 4) != 0)) {
        tmp_pc5 = tmp_pc1;
        if (*tmp_pc1 == '\0') {
          tmp_pc5 = "^7kicked by admin^7";
        }
        tmp_u6 = va("^7You have been kicked, Reason: %s^7",tmp_pc5);
        G_shrubbot_tempban(local_91c[0],tmp_u6,tmp_u3);
      }
      if (*tmp_pc1 == '\0') {
        tmp_pc1 = "^7kicked by admin^7";
      }
      tmp_u3 = va("^7You have been kicked, Reason: %s^7",tmp_pc1);
      trap_DropClient(local_91c[0],tmp_u3,0x78);
      tmp_u3 = 1;
    }
    else if (param_1 == 0) {
      G_shrubbot_print_part_8();
      tmp_u3 = 0;
    }
    else {
      tmp_u3 = va("print \"%s\"","^1kick error: ^9Can\'t kick server host.\n");
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
      tmp_u3 = 0;
    }
  }
  else {
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_u3 = va("^1kick %s\n",local_81c);
    if (param_1 == 0) {
      DecolorString(tmp_u3,local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_u3 = va("print \"%s\"",tmp_u3);
LAB_000cdbad:
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
    tmp_u3 = 0;
  }
  return tmp_u3;
}

uint32_t G_shrubbot_kick(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  tmp_i1 = nitrox_CheckPermission(param_1,5);
  tmp_i3 = param_2 + 2;
  if (tmp_i1 == 0) {
    tmp_i3 = param_2 + 3;
  }
  tmp_i1 = Q_SayArgc();
  if (tmp_i3 <= tmp_i1) {
    tmp_u2 = G_shrubbot_kick_part_9();
    return tmp_u2;
  }
  if (param_1 == 0) {
    G_shrubbot_print_part_8();
  }
  else {
    tmp_u2 = va("print \"%s\"","^9usage: ^g!kick [name] [reason]^7\n");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
  }
  return 0;
}

int MuteNumbersFromString(char *param_1,int *param_2)
{
  int tmp_i1;
  time_t tVar2;
  size_t tmp_s3;
  long tmp_l4;
  int tmp_i5;
  char *tmp_pc6;
  int tmp_i7;
  int tmp_i8;
  char *local_830;
  int local_820;
  char local_81c [1024];
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xcdeb9;
  tVar2 = time(&local_820);
  if (tVar2 != 0) {
    *param_2 = -1;
    local_820 = local_820 + -0x386a4c20;
    tmp_s3 = strlen(param_1);
    for (tmp_i7 = 0; tmp_i7 < (int)tmp_s3; tmp_i7 = tmp_i7 + 1) {
      if (9 < (byte)(param_1[tmp_i7] - 0x30U)) {
        SanitizeString(param_1,local_81c,1);
        goto LAB_000cdf7d;
      }
    }
    tmp_l4 = strtol(param_1,(char **)0x0,10);
    tmp_i7 = tmp_l4 * 0x54dc + level;
    if (*(int *)(tmp_i7 + 0x5ac) - 1U < 2) {
      SanitizeString(tmp_i7 + 0x5f8,local_81c,1);
LAB_000cdf7d:
      local_830 = local_81c;
      if (local_81c[0] != '\0') {
        tmp_i7 = 0;
        if (Mutes != 0) {
          tmp_i8 = 0;
          tmp_i7 = 0;
          tmp_i5 = Mutes;
          do {
            tmp_i1 = *(int *)(tmp_i5 + 0x48c);
            if ((tmp_i1 == 0) || (tmp_i1 != local_820 && -1 < tmp_i1 - local_820)) {
              SanitizeString(tmp_i5,local_41c,1);
              tmp_pc6 = strstr(local_41c,local_830);
              if (tmp_pc6 != (char *)0x0) {
                *param_2 = tmp_i8;
                tmp_i7 = tmp_i7 + 1;
                param_2 = param_2 + 1;
              }
              if (0x3e < tmp_i7) break;
            }
            tmp_i8 = tmp_i8 + 1;
            tmp_i5 = (&Mutes)[tmp_i8];
          } while (tmp_i5 != 0);
        }
        *param_2 = -1;
        return tmp_i7;
      }
    }
  }
  return 0;
}

uint32_t G_MatchOneMute(int *param_1,char *param_2,uint param_3)
{
  uint32_t tmp_u1;
  uint8_t *tmp_pu2;
  size_t tmp_s3;
  size_t tmp_s4;
  int tmp_i5;
  char local_4a [58];
  
  local_4a[0] = '\0';
  *param_2 = '\0';
  if (*param_1 == -1) {
    Q_strcat(param_2,param_3,"^9no player by that name or slot # is muted");
    tmp_u1 = 0;
  }
  else {
    tmp_u1 = 1;
    if (param_1[1] != -1) {
      Q_strcat(param_2,param_3,
               "^9more than one player name matches. be more specific or use the slot #:\n");
      tmp_i5 = *param_1;
      if (tmp_i5 != -1) {
        do {
          if ((&Mutes)[tmp_i5] + 0x57 == 0) {
            tmp_pu2 = &g_unk_0026ea14;
          }
          else {
            tmp_pu2 = (uint8_t *)va("^9for ^x%s^7",(&Mutes)[tmp_i5] + 0x57);
          }
          Com_sprintf(local_4a,0x2e,"^9%2i ^7- %s^7 %s\n",*param_1,(&Mutes)[*param_1],tmp_pu2);
          tmp_s3 = strlen(param_2);
          tmp_s4 = strlen(local_4a);
          if (param_3 < tmp_s4 + tmp_s3) {
            return 0;
          }
          param_1 = param_1 + 1;
          Q_strcat(param_2,param_3,local_4a);
          tmp_i5 = *param_1;
        } while (tmp_i5 != -1);
      }
      return 0;
    }
  }
  return tmp_u1;
}

uint32_t G_shrubbot_lockteams(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  uint8_t local_31 [4];
  char local_2d;
  char local_2c [28];
  
  Q_SayArgv(param_2,&local_2d,0x11);
  tmp_pc5 = &local_2d;
  if (local_2d == '!') {
    tmp_pc5 = local_2c;
  }
  tmp_i1 = Q_SayArgc();
  if (tmp_i1 <= param_2 + 1) {
    tmp_u4 = va("^9usage: ^g!%s [r|b|s|all]^7\n",tmp_pc5);
joined_r0x000ce4d0:
    if (param_1 == 0) {
      G_shrubbot_print_part_8();
    }
    else {
      tmp_u4 = va("print \"%s\"",tmp_u4);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
    }
    return 0;
  }
  Q_SayArgv(param_2 + 1,local_31,4);
  tmp_i1 = Q_stricmp(local_31,"all");
  if (tmp_i1 == 0) {
    tmp_i1 = TeamCount(0xffffffff,1);
    GHIDRA_FIELD(teamInfo, 20, 4) = 0;
    if (tmp_i1 != 0) {
      GHIDRA_FIELD(teamInfo, 20, 4) = param_3;
    }
    tmp_i1 = TeamCount(0xffffffff,2);
    GHIDRA_FIELD(teamInfo, 36, 4) = 0;
    if (tmp_i1 != 0) {
      GHIDRA_FIELD(teamInfo, 36, 4) = param_3;
    }
    tmp_i2 = TeamCount(0xffffffff,1);
    tmp_i1 = 0;
    if (tmp_i2 != 0) {
      tmp_i1 = param_3;
    }
    G_updateSpecLock(1,tmp_i1);
    tmp_i2 = TeamCount(0xffffffff,2);
    tmp_i1 = 0;
    if (tmp_i2 != 0) {
      tmp_i1 = param_3;
    }
    G_updateSpecLock(2,tmp_i1);
    if (param_3 == 0) {
      g_unk_02a99a80 = g_unk_02a99a80 & 0xffffffbf;
    }
    else {
      g_unk_02a99a80 = g_unk_02a99a80 | 0x40;
    }
    tmp_pc3 = "cpm \"^x%s: ^9All teams %sed^7\" -1";
LAB_000ce3c3:
    tmp_u4 = va(tmp_pc3,tmp_pc5,tmp_pc5);
    trap_SendServerCommand(0xffffffff,tmp_u4);
  }
  else {
    tmp_i1 = Q_stricmp(local_31,"r");
    if (tmp_i1 == 0) {
      tmp_i1 = TeamCount(0xffffffff,1);
      GHIDRA_FIELD(teamInfo, 20, 4) = 0;
      if (tmp_i1 != 0) {
        GHIDRA_FIELD(teamInfo, 20, 4) = param_3;
      }
      tmp_pc3 = "cpm \"^x%s: ^9Axis team %sed^7\" -1";
    }
    else {
      tmp_i1 = Q_stricmp(local_31,&g_unk_0026dcfc);
      if (tmp_i1 != 0) {
        tmp_i1 = Q_stricmp(local_31,&g_unk_0024e6ea);
        if (tmp_i1 != 0) {
          tmp_u4 = va("^9usage: ^g!%s ^7r|b|s|all^7\n",tmp_pc5);
          goto joined_r0x000ce4d0;
        }
        tmp_i2 = TeamCount(0xffffffff,1);
        tmp_i1 = 0;
        if (tmp_i2 != 0) {
          tmp_i1 = param_3;
        }
        G_updateSpecLock(1,tmp_i1);
        tmp_i2 = TeamCount(0xffffffff,2);
        tmp_i1 = 0;
        if (tmp_i2 != 0) {
          tmp_i1 = param_3;
        }
        G_updateSpecLock(2,tmp_i1);
        if (param_3 == 0) {
          g_unk_02a99a80 = g_unk_02a99a80 & 0xffffffbf;
        }
        else {
          g_unk_02a99a80 = g_unk_02a99a80 | 0x40;
        }
        tmp_pc3 = "cpm \"^x%s: ^9Spectators %sed^7\" -1";
        goto LAB_000ce3c3;
      }
      tmp_i1 = TeamCount(0xffffffff,2);
      GHIDRA_FIELD(teamInfo, 36, 4) = 0;
      if (tmp_i1 != 0) {
        GHIDRA_FIELD(teamInfo, 36, 4) = param_3;
      }
      tmp_pc3 = "cpm \"^x%s: ^9Allied team %sed^7\" -1";
    }
    tmp_u4 = va(tmp_pc3,tmp_pc5,tmp_pc5);
    trap_SendServerCommand(0xffffffff,tmp_u4);
  }
  if (param_3 == 0) {
    g_unk_02a99a80 = g_unk_02a99a80 & 0xffffffdf;
  }
  else {
    g_unk_02a99a80 = g_unk_02a99a80 | 0x20;
  }
  tmp_u4 = va(&g_unk_00245ee9,g_unk_02a99a80);
  trap_SetConfigstring(0x1d,tmp_u4);
  return 1;
}

void G_shrubbot_print_chat(int param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  char tmp_c4;
  int tmp_i5;
  char local_41c [1036];
  
  if (param_1 == 0) {
    DecolorString(param_2,local_41c);
    tmp_u2 = va(&g_unk_0026fe3c,local_41c);
    G_Printf(tmp_u2);
    return;
  }
  tmp_pc3 = local_41c;
  Q_strncpyz(tmp_pc3,param_2,0x400);
  tmp_i5 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  while (tmp_c4 = *tmp_pc3, tmp_pc1 = tmp_pc3, tmp_c4 != '\0') {
    while (tmp_c4 != '\n') {
      tmp_pc1 = tmp_pc1 + 1;
      tmp_c4 = *tmp_pc1;
      if (tmp_c4 == '\0') goto LAB_000ce6e3;
    }
    *tmp_pc1 = '\0';
    tmp_u2 = va("chat \"%s\" -2",tmp_pc3);
    trap_SendServerCommand(tmp_i5,tmp_u2);
    tmp_pc3 = tmp_pc1 + 1;
  }
LAB_000ce6e3:
  tmp_u2 = va("chat \"%s\" -2",tmp_pc3);
  trap_SendServerCommand(tmp_i5,tmp_u2);
  return;
}

uint32_t G_shrubbot_records(uint32_t param_1)
{
  if (GHIDRA_FIELD(n_mapRecords, 12, 4) != 0) {
    nitrox_SQLite_FindMapRecords(7);
    return 1;
  }
  G_shrubbot_print_chat(param_1,"^xrecords: ^gSorry, map records are not enabled.");
  return 1;
}

uint32_t G_shrubbot_uptime(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_i2 = (g_unk_00abe908 / 1000) % 0x15180;
  tmp_u1 = va("^xuptime: ^g%i days, %i hours, %i minutes.",(g_unk_00abe908 / 1000) / 0x15180,
             tmp_i2 / 0xe10,(tmp_i2 % 0xe10) / 0x3c);
  G_shrubbot_print_chat(param_1,tmp_u1);
  return 1;
}

uint32_t G_shrubbot_delrecords(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  char *tmp_pc4;
  uint8_t tmp_u5;
  byte tmp_b6;
  char local_5c [76];
  
  tmp_b6 = 0;
  if (GHIDRA_FIELD(n_mapRecords, 12, 4) == 0) {
    G_shrubbot_print_chat(param_1,"^xdelrecords: ^gSorry, map records are not enabled.");
    tmp_u2 = 1;
  }
  else {
    param_2 = param_2 + 1;
    tmp_i1 = Q_SayArgc();
    tmp_u5 = param_2 == tmp_i1;
    if (param_2 < tmp_i1) {
      Q_SayArgv(param_2,local_5c,0x40);
      tmp_i1 = 10;
      tmp_pc3 = local_5c;
      tmp_pc4 = "DELETEALL";
      do {
        if (tmp_i1 == 0) break;
        tmp_i1 = tmp_i1 + -1;
        tmp_u5 = *tmp_pc3 == *tmp_pc4;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b6 * -2 + 1;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
      } while ((bool)tmp_u5);
      if ((bool)tmp_u5) {
        nitrox_SQLite_ClearAllMapRecords();
        tmp_u2 = va("^xdelrecords: ^9Sucessfully deleted all map records^7\n");
      }
      else {
        tmp_i1 = nitrox_SQLite_ClearMapRecords(local_5c);
        if (tmp_i1 == 0) {
          tmp_u2 = va("^9delrecords : ^9map records not found for \'^g%s^9\'\n",local_5c);
        }
        else {
          tmp_u2 = va("^xdelrecords: ^9Map records for ^g%s^9 successfully deleted from database^7\n"
                     ,local_5c);
        }
      }
      if (param_1 == 0) {
        G_shrubbot_print_part_8();
        tmp_u2 = 1;
      }
      else {
        tmp_u2 = va("print \"%s\"",tmp_u2);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
        tmp_u2 = 1;
      }
    }
    else if (param_1 == 0) {
      G_shrubbot_print_part_8();
      tmp_u2 = 0;
    }
    else {
      tmp_u2 = va("print \"%s\"","^9usage: ^g!delrecord [map_name|DELETEALL]^7\n");
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
      tmp_u2 = 0;
    }
  }
  return tmp_u2;
}

void G_shrubbot_print(int param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  
  if (param_1 != 0) {
    tmp_u1 = va("print \"%s\"",param_2);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
    return;
  }
  G_shrubbot_print_part_8();
  return;
}

uint32_t G_shrubbot_cmd_check(int param_1)
{
  byte tmp_b1;
  int tmp_i2;
  char *__needle;
  char *tmp_pc3;
  int tmp_i4;
  uint32_t tmp_u5;
  char *tmp_pc6;
  char *tmp_pc7;
  uint8_t **tmp_ppu8;
  uint8_t **tmp_ppu9;
  int tmp_i10;
  int local_80;
  int local_7c;
  uint32_t local_78;
  int local_74;
  int local_70;
  int local_6c;
  char local_51;
  uint8_t local_50 [16];
  char local_40 [48];
  
  if (g_unk_02af58b8 == 0) {
    return 0;
  }
  local_51 = '\0';
  Q_SayArgv(0,&local_51,0x11);
  tmp_i2 = Q_stricmp(&local_51,&g_unk_00258b16);
  if ((tmp_i2 == 0) ||
     ((tmp_i2 = nitrox_CheckPermission(param_1,8), tmp_i2 != 0 &&
      ((tmp_i2 = Q_stricmp(&local_51,"say_team"), tmp_i2 == 0 ||
       (tmp_i2 = Q_stricmp(&local_51,"say_buddy"), tmp_i2 == 0)))))) {
    Q_SayArgv(1,&local_51,0x11);
    local_78 = 0;
    local_7c = 1;
  }
  else {
    local_78 = 0xffffffff;
    local_7c = 0;
  }
  if (local_51 == '\0') {
    return 0;
  }
  if (local_51 == '!') {
    __needle = (char *)Q_strlwr(local_50);
  }
  else {
    if (param_1 != 0) {
      return 0;
    }
    __needle = (char *)Q_strlwr(&local_51);
  }
  tmp_ppu8 = &g_ptr_s_time_002528fd_0x18_002b3ab4;
  tmp_pc6 = "readconfig";
  local_6c = 0;
  local_74 = 0;
  local_80 = 0;
  tmp_pc7 = tmp_pc6;
  tmp_ppu9 = tmp_ppu8;
  do {
    tmp_i2 = Q_stricmp(tmp_pc7,__needle);
    if (tmp_i2 == 0) {
      tmp_b1 = 0;
      tmp_i2 = 0;
      if (CustomCommands != 0) goto LAB_000cec60;
      goto LAB_000cecd4;
    }
    tmp_pc3 = strstr(tmp_pc7,__needle);
    if ((tmp_pc3 != (char *)0x0) && (tmp_i2 = Q_stricmp(tmp_pc3,tmp_pc7), tmp_i2 == 0)) {
      local_6c = local_6c + 1;
      local_74 = local_80;
    }
    tmp_pc7 = *tmp_ppu9;
    tmp_ppu9 = tmp_ppu9 + 5;
    local_80 = local_80 + 1;
  } while (*tmp_pc7 != '\0');
  tmp_b1 = 1;
  if (CustomCommands == 0) {
    tmp_i2 = 0;
    if (local_6c != 1) goto LAB_000cecd4;
  }
  else {
LAB_000cec60:
    tmp_i10 = 0;
    local_70 = 0;
    tmp_i2 = CustomCommands;
    do {
      tmp_i4 = Q_stricmp(tmp_i2,__needle);
      tmp_i2 = CustomCommands;
      if (tmp_i4 == 0) goto LAB_000cecd4;
      tmp_pc7 = (char *)(&CustomCommands)[tmp_i10];
      tmp_pc3 = strstr(tmp_pc7,__needle);
      if ((tmp_pc3 != (char *)0x0) && (tmp_i2 = Q_stricmp(tmp_pc3,tmp_pc7), tmp_i2 == 0)) {
        local_70 = local_70 + 1;
        local_74 = tmp_i10;
      }
      tmp_i2 = (&g_unk_02db0e44)[tmp_i10];
      tmp_i10 = tmp_i10 + 1;
    } while (tmp_i2 != 0);
    if ((local_70 != 0) || (!(bool)(tmp_b1 & local_6c == 1))) {
      tmp_i2 = CustomCommands;
      if ((!(bool)(tmp_b1 & local_6c == 0)) || (local_70 != 1)) goto LAB_000cecd4;
      tmp_i2 = _shrubbot_command_permission();
      if (tmp_i2 == 0) {
        tmp_u5 = (&CustomCommands)[local_74];
LAB_000cf194:
        tmp_u5 = va("^x%s: ^1Permission denied\n",tmp_u5);
        G_shrubbot_print(param_1,tmp_u5);
        _shrubbot_log(param_1,"attempted",local_78);
        return 0;
      }
      if (GHIDRA_FIELD(g_shortcuts, 12, 4) == 0) {
        local_74 = (&CustomCommands)[local_74] + 0x40;
      }
      else {
        local_74 = G_Shortcuts(param_1,(&CustomCommands)[local_74] + 0x40);
      }
      if ((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) {
        tmp_u5 = va("%i",*(uint32_t *)(*(int *)(param_1 + 400) + 0xa0));
        local_74 = Q_StrReplace(local_74,&g_unk_002523bf,tmp_u5);
      }
      tmp_i2 = 1;
      do {
        Q_SayArgv(local_7c + tmp_i2,local_40,0x24);
        tmp_pc6 = strchr(local_40,0x3b);
        if (tmp_pc6 != (char *)0x0) {
          Nit_RemoveWordInString(local_40,&g_unk_0026ea0e);
        }
        tmp_i10 = tmp_i2 + 1;
        tmp_u5 = va(&g_unk_002523c3,tmp_i2);
        local_74 = Q_StrReplace(local_74,tmp_u5,local_40);
        tmp_i2 = tmp_i10;
      } while (tmp_i10 != 10);
      trap_SendConsoleCommand(2,local_74);
      goto LAB_000cefaf;
    }
  }
  tmp_i2 = nitrox_CheckCommandPermission(param_1,(&g_unk_002b3aa4)[local_74 * 5]);
  if (tmp_i2 == 0) {
    tmp_u5 = va("^x%s: ^1Permission denied\n",(&g_shrubbot_cmds)[local_74 * 5]);
    G_shrubbot_print(param_1,tmp_u5);
    _shrubbot_log(param_1,"attempted",local_78);
    tmp_i2 = CustomCommands;
LAB_000cecd4:
    tmp_i10 = 0;
    while (tmp_i2 != 0) {
      tmp_i2 = Q_stricmp(__needle,tmp_i2);
      if (tmp_i2 == 0) {
        tmp_i2 = _shrubbot_command_permission();
        if (tmp_i2 != 0) {
          if (GHIDRA_FIELD(g_shortcuts, 12, 4) == 0) {
            tmp_i2 = (&CustomCommands)[tmp_i10] + 0x40;
          }
          else {
            tmp_i2 = G_Shortcuts(param_1,(&CustomCommands)[tmp_i10] + 0x40);
          }
          tmp_i10 = 1;
          do {
            Q_SayArgv(local_7c + tmp_i10,local_40,0x24);
            tmp_i4 = tmp_i10 + 1;
            tmp_u5 = va(&g_unk_002523c3,tmp_i10);
            tmp_i2 = Q_StrReplace(tmp_i2,tmp_u5,local_40);
            tmp_i10 = tmp_i4;
          } while (tmp_i4 != 10);
          trap_SendConsoleCommand(2,tmp_i2);
          goto LAB_000cefaf;
        }
        tmp_u5 = (&CustomCommands)[tmp_i10];
        goto LAB_000cf194;
      }
      tmp_i10 = tmp_i10 + 1;
      tmp_i2 = (&CustomCommands)[tmp_i10];
    }
    local_80 = 0;
    if (param_1 == 0) {
      do {
        tmp_i2 = Q_stricmp(__needle,tmp_pc6);
        if (tmp_i2 == 0) {
          tmp_i2 = nitrox_CheckCommandPermission(0,tmp_ppu8[-4]);
          if (tmp_i2 != 0) goto LAB_000cf2b4;
          va("^x%s: ^1Permission denied\n",tmp_pc6);
          G_shrubbot_print_part_8();
          _shrubbot_log(0,"attempted",local_78);
        }
        tmp_pc6 = *tmp_ppu8;
        local_80 = local_80 + 1;
        tmp_ppu8 = tmp_ppu8 + 5;
      } while (*tmp_pc6 != '\0');
    }
    else {
      local_80 = 0;
      do {
        tmp_i2 = Q_stricmp(__needle,tmp_pc6);
        if (tmp_i2 == 0) {
          tmp_i2 = nitrox_CheckCommandPermission(param_1,tmp_ppu8[-4]);
          if (tmp_i2 != 0) goto LAB_000cf2b4;
          tmp_u5 = va("^x%s: ^1Permission denied\n",tmp_pc6);
          tmp_u5 = va("print \"%s\"",tmp_u5);
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
          _shrubbot_log(param_1,"attempted",local_78);
        }
        tmp_pc6 = *tmp_ppu8;
        tmp_ppu8 = tmp_ppu8 + 5;
        local_80 = local_80 + 1;
      } while (*tmp_pc6 != '\0');
    }
    return 0;
  }
  (*(void *)(&g_ptr_nitrox_LoadDBFiles_002b3aa8)[local_74 * 5])(param_1,local_7c);
LAB_000cefaf:
  _shrubbot_log(param_1,__needle,local_7c);
  return 1;
LAB_000cf2b4:
  (*(void *)(&g_ptr_nitrox_LoadDBFiles_002b3aa8)[local_80 * 5])(param_1,local_7c);
  goto LAB_000cefaf;
}

uint32_t G_shrubbot_setlevel(int param_1,int param_2)
{
  bool tmp_b1;
  int tmp_i2;
  long tmp_l3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  int tmp_i6;
  size_t tmp_s7;
  int *tmp_pi8;
  int local_970;
  uint8_t *local_96c;
  int local_958;
  char local_94c [12];
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xcf2e9;
  tmp_i2 = Q_SayArgc();
  if (param_2 + 2 < tmp_i2) {
    Q_SayArgv(param_2 + 1,local_940,0x24);
    Q_SayArgv(param_2 + 2,local_94c,0xc);
    tmp_l3 = strtol(local_94c,(char **)0x0,10);
    if (g_unk_02af58b8 == 0) {
      if (tmp_l3 < 1) {
        tmp_i2 = nitrox_LevelExists(tmp_l3);
        if (tmp_i2 == 0) {
          if (param_1 == 0) goto LAB_000cf68f;
LAB_000cf3b1:
          tmp_pc4 = "^1setlevel error: ^9unknown level\n";
        }
        else {
LAB_000cf3d4:
          tmp_i2 = ClientNumbersFromString(local_940,local_91c);
          if (tmp_i2 == 1) {
            local_958 = local_91c[0];
            local_96c = g_entities + local_91c[0] * 0x600;
            if (param_1 != 0) {
              tmp_i2 = nitrox_GetAdminLevel(param_1,0);
              tmp_i6 = nitrox_GetAdminLevel(local_96c,0);
              if (tmp_i2 < tmp_i6) {
                tmp_pc4 = "^1setlevel error: ^9Specified player has a higher admin level than you.\n"
                ;
                goto LAB_000cf766;
              }
              local_958 = local_91c[0];
              local_96c = g_entities + local_91c[0] * 0x600;
            }
            goto LAB_000cf522;
          }
          G_MatchOnePlayer(local_91c,local_81c,0x400);
          tmp_pc4 = (char *)va("^1setlevel %s\n",local_81c);
          if (param_1 == 0) {
LAB_000cf6a0:
            DecolorString(tmp_pc4,local_41c);
            G_Printf(local_41c);
            return 0;
          }
        }
        goto LAB_000cf445;
      }
      if (param_1 == 0) {
        G_shrubbot_print_part_8();
        return 0;
      }
    }
    else {
      if (param_1 == 0) {
        tmp_i2 = nitrox_LevelExists(tmp_l3);
        if (tmp_i2 == 0) {
LAB_000cf68f:
          tmp_pc4 = "^1setlevel error: ^9unknown level\n";
          goto LAB_000cf6a0;
        }
        tmp_i2 = ClientNumbersFromString(local_940,local_91c);
        if (tmp_i2 != 1) {
          G_MatchOnePlayer(local_91c,local_81c,0x400);
          tmp_pc4 = (char *)va("^1setlevel %s\n",local_81c);
          goto LAB_000cf6a0;
        }
        local_958 = local_91c[0];
        local_96c = g_entities + local_91c[0] * 0x600;
LAB_000cf522:
        tmp_pc4 = (char *)(local_958 * 0x54dc + level + 0x61c);
        tmp_i2 = *(int *)(g_entities + local_958 * 0x600 + 400);
        if (*(int *)(tmp_i2 + 0x54d8) != 0) {
          tmp_pc4 = "^1setlevel error: ^9Player is a Demo Client\n";
LAB_000cf766:
          G_shrubbot_print(param_1,tmp_pc4);
          return 0;
        }
        tmp_s7 = strlen(tmp_pc4);
        if (tmp_s7 == 0x20) {
          if ((g_entities[local_958 * 0x600 + 0x128] & 8) != 0) {
            tmp_pc4 = "^1setlevel error: ^9Player is a Bot.\n";
            goto LAB_000cf766;
          }
          Q_strncpyz(local_41c,tmp_i2 + 0x5f8,0x24);
          if (Users == 0) {
            local_970 = 0;
          }
          else {
            tmp_pi8 = &Users;
            tmp_b1 = false;
            local_970 = 0;
            tmp_i2 = Users;
            do {
              tmp_i6 = strcmp((char *)(tmp_i2 + 4),tmp_pc4);
              if (tmp_i6 == 0) {
                tmp_u5 = nitrox_LevelPointer(tmp_l3);
                *(uint32_t *)(tmp_i2 + 0x4c) = tmp_u5;
                Q_strncpyz(*tmp_pi8 + 0x25,local_41c,0x24);
                nitrox_SaveSingleUser(*tmp_pi8,2);
                nitrox_SetAdminPointers(local_96c,*tmp_pi8);
                tmp_b1 = true;
              }
              tmp_pi8 = tmp_pi8 + 1;
              tmp_i2 = *tmp_pi8;
              local_970 = local_970 + 1;
            } while (tmp_i2 != 0);
            if (tmp_b1) goto LAB_000cf8c4;
          }
          tmp_i2 = AllocUser();
          tmp_u5 = nitrox_LevelPointer(tmp_l3);
          *(uint32_t *)(tmp_i2 + 0x4c) = tmp_u5;
          Q_strncpyz(tmp_i2 + 0x25,local_41c,0x24);
          Q_strncpyz(tmp_i2 + 4,tmp_pc4,0x21);
          Q_strncpyz(tmp_i2 + 0xc62,*(int *)(g_entities + local_958 * 0x600 + 400) + 0x653,0x12);
          Q_strncpyz(tmp_i2 + 0xc50,*(int *)(g_entities + local_958 * 0x600 + 400) + 0xaf4,0x12);
          nitrox_SaveSingleUser(tmp_i2,1);
          (&Users)[local_970] = tmp_i2;
          nitrox_SetAdminPointers(local_96c,tmp_i2);
LAB_000cf8c4:
          tmp_u5 = va("cpm \"^xsetlevel: ^7%s^7^9\'s level set to ^x%d^7\" -1",
                     *(int *)(g_entities + local_958 * 0x600 + 400) + 0x5f8,tmp_l3);
          trap_SendServerCommand(0xffffffff,tmp_u5);
          return 1;
        }
        if (param_1 == 0) {
          G_shrubbot_print_part_8();
          return 0;
        }
        tmp_u5 = va("print \"%s\"","^1setlevel error: ^9Player has no or invalid NGUID\n");
        goto LAB_000cf46a;
      }
      if (*(int *)(param_1 + 0x5e8) == 0) {
        tmp_i2 = 0;
      }
      else {
        tmp_i2 = GetUserPointer(param_1);
        tmp_i2 = **(int **)(tmp_i2 + 0x4c);
      }
      if (tmp_l3 <= tmp_i2) {
        tmp_i2 = nitrox_LevelExists(tmp_l3);
        if (tmp_i2 == 0) goto LAB_000cf3b1;
        goto LAB_000cf3d4;
      }
    }
    tmp_pc4 = "^1setlevel error: ^9you can\'t setlevel higher than your level\n";
  }
  else {
    if (param_1 == 0) {
      tmp_pc4 = "^9usage: ^g!setlevel [name|slot#] [level]\n";
      goto LAB_000cf6a0;
    }
    tmp_pc4 = "^9usage: ^g!setlevel [name|slot#] [level]\n";
  }
LAB_000cf445:
  tmp_u5 = va("print \"%s\"",tmp_pc4);
LAB_000cf46a:
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
  return 0;
}

uint32_t G_shrubbot_ban(int param_1,int param_2)
{
  int *tmp_pi1;
  char tmp_c2;
  time_t tVar3;
  int tmp_i4;
  int tmp_i5;
  size_t tmp_s6;
  long tmp_l7;
  char *tmp_pc8;
  uint32_t tmp_u9;
  int tmp_i10;
  tm *__tp;
  int local_960;
  char *local_95c;
  int local_94c;
  char acStack_948 [8];
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tVar3 = time(&local_94c);
  if (tVar3 == 0) {
    return 0;
  }
  tmp_i4 = nitrox_CheckPermission(param_1,7);
  if ((tmp_i4 == 0) || (tmp_i4 = nitrox_CheckPermission(param_1,5), tmp_i4 == 0)) {
    tmp_i4 = nitrox_CheckPermission(param_1,7);
    if ((tmp_i4 == 0) && (tmp_i4 = nitrox_CheckPermission(param_1,5), tmp_i4 == 0)) {
      tmp_i4 = param_2 + 4;
    }
    else {
      tmp_i4 = param_2 + 3;
    }
  }
  else {
    tmp_i4 = param_2 + 2;
  }
  tmp_i5 = Q_SayArgc();
  if (tmp_i5 < tmp_i4) {
    if (param_1 == 0) {
      tmp_pc8 = "^9usage: ^g!ban [name] [seconds] [reason]\n";
LAB_000cffe1:
      DecolorString(tmp_pc8,local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_pc8 = "^9usage: ^g!ban [name] [seconds] [reason]\n";
  }
  else {
    tmp_pc8 = acStack_948 + 1;
    Q_SayArgv(param_2 + 1,local_940,0x24);
    Q_SayArgv(param_2 + 2,tmp_pc8,7);
    local_960 = 1;
    if (acStack_948[1] != '\0') {
      tmp_s6 = strlen(tmp_pc8);
      tmp_c2 = acStack_948[tmp_s6];
      if (9 < (byte)(tmp_c2 - 0x30U)) {
        if (tmp_c2 == 'w') {
          local_960 = 0x93a80;
        }
        else if (tmp_c2 == 'd') {
          local_960 = 0x15180;
        }
        else if (tmp_c2 == 'h') {
          local_960 = 0xe10;
        }
        else {
          local_960 = 0x3c;
          if (tmp_c2 != 'm') {
            local_960 = 1;
          }
        }
        acStack_948[tmp_s6] = '\0';
      }
    }
    tmp_l7 = strtol(tmp_pc8,(char **)0x0,10);
    if (tmp_l7 < 1) {
      tmp_i4 = nitrox_CheckPermission(param_1,7);
      if (tmp_i4 == 0) {
        if (param_1 == 0) {
          G_shrubbot_print_part_8();
          return 0;
        }
        tmp_u9 = va("print \"%s\"","^1ban error: ^9seconds must be a positive integer\n");
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u9);
        return 0;
      }
      local_95c = (char *)Q_SayConcatArgs(param_2 + 2);
      local_960 = 0;
    }
    else {
      local_960 = tmp_l7 * local_960;
      local_95c = (char *)Q_SayConcatArgs(param_2 + 3);
    }
    tmp_i5 = ClientNumbersFromString(local_940,local_91c);
    tmp_i4 = local_91c[0];
    if (tmp_i5 == 1) {
      if (param_1 == 0) {
        tmp_i4 = *(int *)(g_entities + local_91c[0] * 0x600 + 400);
        if (*(int *)(tmp_i4 + 0x5e8) != 0) {
          G_shrubbot_print_part_8();
          return 0;
        }
LAB_000cfcb7:
        tmp_i5 = local_91c[0];
        tmp_i10 = AllocBan(1);
        if (tmp_i10 == 0) {
          return 0;
        }
        tmp_pi1 = (int *)(g_entities + tmp_i5 * 0x600 + 400);
        Q_strncpyz(tmp_i10 + 0x4b4,*tmp_pi1 + 0xaf4,0x12);
        Q_strncpyz(tmp_i10,*tmp_pi1 + 0x5f8,0x24);
        Q_strncpyz(tmp_i10 + 0x24,tmp_i4 + 0x61c,0x21);
        Q_strncpyz(tmp_i10 + 0x45,*tmp_pi1 + 0x653,0x12);
        __tp = localtime(&local_94c);
        strftime((char *)(tmp_i10 + 0x457),0x32,"%m/%d/%y %H:%M:%S",__tp);
        if (param_1 == 0) {
          Q_strncpyz(tmp_i10 + 0x490,"console",0x24);
        }
        else {
          Q_strncpyz(tmp_i10 + 0x490,*(int *)(param_1 + 400) + 0x5f8,0x24);
        }
        tmp_i4 = 0;
        if (local_960 != 0) {
          tmp_i4 = local_960 + -0x386a4c20 + local_94c;
        }
        *(int *)(tmp_i10 + 0x48c) = tmp_i4;
        if (*local_95c == '\0') {
          Q_strncpyz(tmp_i10 + 0x57,"banned by admin",0x400);
        }
        else {
          Q_strncpyz(tmp_i10 + 0x57,local_95c,0x400);
        }
        tmp_i4 = 0;
        if (Bans != 0) {
          tmp_i4 = 0;
          do {
            tmp_i4 = tmp_i4 + 1;
          } while ((&Bans)[tmp_i4] != 0);
        }
        nitrox_SaveSingleBan(tmp_i10,1);
        (&Bans)[tmp_i4] = tmp_i10;
        tmp_u9 = va("^xban: ^7%s ^9is now banned\n",
                   *(int *)(g_entities + tmp_i5 * 0x600 + 400) + 0x5f8);
        if (param_1 == 0) {
          G_shrubbot_print_part_8();
        }
        else {
          tmp_u9 = va("print \"%s\"",tmp_u9);
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u9);
        }
        if (local_960 == 0) {
          Q_strncpyz(local_41c,"^1PERMANENTLY",0x400);
        }
        else {
          Com_sprintf(local_41c,0x400,"for %i seconds",local_960);
        }
        if (*local_95c == '\0') {
          local_95c = "banned by admin";
        }
        tmp_u9 = va("You have been banned %s, Reason: %s",local_41c,local_95c);
        trap_DropClient(local_91c[0],tmp_u9,0);
        return 1;
      }
      tmp_i5 = nitrox_GetAdminLevel(param_1,0);
      tmp_i4 = nitrox_GetAdminLevel(g_entities + tmp_i4 * 0x600,0);
      if (tmp_i5 < tmp_i4) {
        G_shrubbot_print(param_1,
                         "^1ban error: ^9Specficied player has a higher admin level than you do.\n")
        ;
        return 0;
      }
      tmp_i4 = *(int *)(g_entities + local_91c[0] * 0x600 + 400);
      if (*(int *)(tmp_i4 + 0x5e8) == 0) goto LAB_000cfcb7;
      tmp_u9 = va("print \"%s\"","^1ban error: ^9Cannot ban server host.\n");
      goto LAB_000cfb67;
    }
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_pc8 = (char *)va("^1ban %s\n",local_81c);
    if (param_1 == 0) goto LAB_000cffe1;
  }
  tmp_u9 = va("print \"%s\"",tmp_pc8);
LAB_000cfb67:
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u9);
  return 0;
}

uint32_t G_shrubbot_mute(int param_1,int param_2)
{
  char tmp_c1;
  time_t tVar2;
  int tmp_i3;
  size_t tmp_s4;
  long tmp_l5;
  int tmp_i6;
  char *tmp_pc7;
  uint32_t tmp_u8;
  int tmp_i9;
  tm *__tp;
  int tmp_i10;
  char *tmp_pc11;
  bool tmp_b12;
  byte tmp_b13;
  int local_95c;
  char *local_958;
  int local_94c;
  char acStack_948 [8];
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tmp_b13 = 0;
  tVar2 = time(&local_94c);
  if (tVar2 != 0) {
    tmp_i3 = nitrox_CheckPermission(param_1,5);
    tmp_i9 = param_2 + 2;
    tmp_i6 = param_2 + 3;
    if (tmp_i3 != 0) {
      tmp_i6 = tmp_i9;
    }
    tmp_i3 = Q_SayArgc();
    if (tmp_i3 < tmp_i6) {
      if (param_1 != 0) {
        tmp_pc7 = "^9usage: ^g!mute [name] [seconds] [reason]\n";
        goto LAB_000d02cf;
      }
      tmp_pc7 = "^9usage: ^g!mute [name] [seconds] [reason]\n";
    }
    else {
      Q_SayArgv(param_2 + 1,local_940,0x24);
      tmp_pc7 = acStack_948 + 1;
      Q_SayArgv(tmp_i9,tmp_pc7,7);
      local_95c = 1;
      if (acStack_948[1] != '\0') {
        tmp_s4 = strlen(tmp_pc7);
        tmp_c1 = acStack_948[tmp_s4];
        if (9 < (byte)(tmp_c1 - 0x30U)) {
          if (tmp_c1 == 'w') {
            local_95c = 0x93a80;
          }
          else if (tmp_c1 == 'd') {
            local_95c = 0x15180;
          }
          else if (tmp_c1 == 'h') {
            local_95c = 0xe10;
          }
          else {
            local_95c = 0x3c;
            if (tmp_c1 != 'm') {
              local_95c = 1;
            }
          }
          acStack_948[tmp_s4] = '\0';
        }
      }
      tmp_l5 = strtol(tmp_pc7,(char **)0x0,10);
      if (tmp_l5 < 1) {
        local_95c = 10;
        if (9 < (int)GHIDRA_FIELD(g_defaultMute, 12, 4)) {
          local_95c = GHIDRA_FIELD(g_defaultMute, 12, 4);
        }
        local_958 = (char *)Q_SayConcatArgs(tmp_i9);
      }
      else {
        local_95c = tmp_l5 * local_95c;
        local_958 = (char *)Q_SayConcatArgs(param_2 + 3);
      }
      tmp_i6 = ClientNumbersFromString(local_940,local_91c);
      tmp_i9 = local_91c[0];
      if (tmp_i6 == 1) {
        if (param_1 != 0) {
          tmp_i6 = nitrox_GetAdminLevel(param_1,0);
          tmp_i9 = nitrox_GetAdminLevel(g_entities + tmp_i9 * 0x600,0);
          if (tmp_i6 < tmp_i9) {
            tmp_pc7 = "^1mute error: ^9Specified player has a higher admin level than you.\n";
            goto LAB_000d02cf;
          }
        }
        tmp_i6 = local_91c[0] * 0x54dc + level;
        tmp_i9 = tmp_i6 + 0x61c;
        if (g_unk_02af58b8 != 0) {
          tmp_i6 = G_shrubbot_mute_check_part_6();
          if (tmp_i6 != 0) {
            G_shrubbot_print(param_1,"^1mute error: ^9already muted\n");
            return 0;
          }
          tmp_i6 = local_91c[0] * 0x54dc + level;
        }
        tmp_i3 = local_91c[0];
        tmp_b12 = (char *)(tmp_i6 + 0x653) == (char *)0x0;
        tmp_i10 = 10;
        tmp_pc7 = (char *)(tmp_i6 + 0x653);
        tmp_pc11 = "localhost";
        do {
          if (tmp_i10 == 0) break;
          tmp_i10 = tmp_i10 + -1;
          tmp_b12 = *tmp_pc7 == *tmp_pc11;
          tmp_pc7 = tmp_pc7 + (uint)tmp_b13 * -2 + 1;
          tmp_pc11 = tmp_pc11 + (uint)tmp_b13 * -2 + 1;
        } while (tmp_b12);
        if (!tmp_b12) {
          tmp_i6 = AllocMute(1);
          if (tmp_i6 == 0) {
            return 0;
          }
          Q_strncpyz(tmp_i6,*(int *)(g_entities + tmp_i3 * 0x600 + 400) + 0x5f8,0x24);
          Q_strncpyz(tmp_i6 + 0x24,tmp_i9,0x21);
          Q_strncpyz(tmp_i6 + 0x4b4,*(int *)(g_entities + tmp_i3 * 0x600 + 400) + 0xaf4,0x12);
          Q_strncpyz(tmp_i6 + 0x45,local_91c[0] * 0x54dc + level + 0x653,0x12);
          __tp = localtime(&local_94c);
          strftime((char *)(tmp_i6 + 0x457),0x32,"%m/%d/%y %H:%M:%S",__tp);
          if (param_1 == 0) {
            tmp_pc7 = "console";
          }
          else {
            tmp_pc7 = (char *)(*(int *)(param_1 + 400) + 0x5f8);
          }
          Q_strncpyz(tmp_i6 + 0x490,tmp_pc7,0x24);
          *(int *)(tmp_i6 + 0x48c) = local_95c + -0x386a4c20 + local_94c;
          if (*local_958 == '\0') {
            Q_strncpyz(tmp_i6 + 0x57,"muted by admin",0x400);
          }
          else {
            Q_strncpyz(tmp_i6 + 0x57,local_958,0x400);
          }
          tmp_i10 = 0;
          tmp_i9 = Mutes;
          while (tmp_i9 != 0) {
            tmp_i10 = tmp_i10 + 1;
            tmp_i9 = (&Mutes)[tmp_i10];
          }
          nitrox_SaveSingleMute(tmp_i6,1);
          (&Mutes)[tmp_i10] = tmp_i6;
          Com_sprintf(local_41c,0x400,"for ^x%i seconds",local_95c);
          *(uint32_t *)(*(int *)(g_entities + tmp_i3 * 0x600 + 400) + 0xbf0) = 1;
          tmp_u8 = va("cpm \"^xmute: ^7%s ^9has been muted %s\"",
                     *(int *)(g_entities + tmp_i3 * 0x600 + 400) + 0x5f8,local_41c);
          trap_SendServerCommand(0xffffffff,tmp_u8);
          return 1;
        }
        tmp_pc7 = "^1mute error: ^9Cannot mute host players\n";
        if (param_1 == 0) {
          G_shrubbot_print_part_8();
          return 0;
        }
LAB_000d02cf:
        tmp_u8 = va("print \"%s\"",tmp_pc7);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u8);
        return 0;
      }
      G_MatchOnePlayer(local_91c,local_81c,0x400);
      tmp_pc7 = (char *)va("^1mute %s\n",local_81c);
      if (param_1 != 0) goto LAB_000d02cf;
    }
    DecolorString(tmp_pc7,local_41c);
    G_Printf(local_41c);
  }
  return 0;
}

uint32_t G_shrubbot_unmute(int param_1,int param_2)
{
  int *tmp_pi1;
  int *tmp_pi2;
  time_t tVar3;
  int tmp_i4;
  uint32_t tmp_u5;
  char *tmp_pc6;
  long tmp_l7;
  int tmp_i8;
  int local_944;
  char local_940 [32];
  int aiStack_920 [65];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tVar3 = time(&local_944);
  if (tVar3 == 0) {
    return 0;
  }
  tmp_i4 = Q_SayArgc();
  if (param_2 + 1 < tmp_i4) {
    Q_SayArgv(param_2 + 1,local_940,0x24);
    tmp_pi2 = aiStack_920 + 1;
    tmp_i4 = ClientNumbersFromString(local_940,tmp_pi2);
    if (tmp_i4 == 1) {
      tmp_pi1 = (int *)(g_entities + aiStack_920[1] * 0x600 + 400);
      if (*(int *)(*tmp_pi1 + 0xbf0) == 0) {
        tmp_i4 = MuteNumbersFromString(local_940,tmp_pi2);
        if (tmp_i4 != 1) {
          tmp_i8 = Q_SayArgc();
          if (tmp_i8 != param_2 + 3) {
            G_MatchOneMute(tmp_pi2,local_81c,0x400);
            tmp_u5 = va("^1unmute %s\n",local_81c);
            if (param_1 != 0) {
              tmp_u5 = va("print \"%s\"",tmp_u5);
              trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
              return 0;
            }
            G_shrubbot_print_part_8();
            return 0;
          }
          Q_SayArgv(param_2 + 2,local_940,0x24);
          tmp_l7 = strtol(local_940,(char **)0x0,10);
          if ((tmp_i4 < tmp_l7) || (tmp_l7 < 1)) {
            G_shrubbot_print(param_1,"^9invalid number\n");
            return 0;
          }
          aiStack_920[1] = aiStack_920[tmp_l7];
        }
        *(int *)((&Mutes)[aiStack_920[1]] + 0x48c) = local_944 + -0x386a4c20;
        tmp_u5 = va("cpm \"^xunmute: ^7%s ^9has been unmuted\"",(&Mutes)[aiStack_920[1]]);
        trap_SendServerCommand(0xffffffff,tmp_u5);
        *(uint32_t *)((&Mutes)[aiStack_920[1]] + 0x4cc) = 1;
        tmp_i4 = (&Mutes)[aiStack_920[1]];
LAB_000d08cd:
        *(uint32_t *)(tmp_i4 + 0x4c8) = 0;
        nitrox_SaveMutes(0,0xffffffff);
        nitrox_LoadMutes();
      }
      else {
        *(uint32_t *)(*tmp_pi1 + 0xbf0) = 0;
        tmp_i8 = 0;
        *(uint32_t *)(*tmp_pi1 + 0xca4) = 0xffffffff;
        tmp_u5 = va("cpm \"^xunmute: ^7%s ^9has been unmuted\"",*tmp_pi1 + 0x5f8);
        trap_SendServerCommand(0xffffffff,tmp_u5);
        tmp_i4 = Mutes;
        while (tmp_i4 != 0) {
          tmp_i4 = Q_stricmp(tmp_i4 + 0x24,*(int *)(g_entities + aiStack_920[1] * 0x600 + 400) + 0x61c
                           );
          if (tmp_i4 == 0) {
            *(uint32_t *)((&Mutes)[tmp_i8] + 0x4cc) = 1;
            tmp_i4 = (&Mutes)[tmp_i8];
            goto LAB_000d08cd;
          }
          tmp_i8 = tmp_i8 + 1;
          tmp_i4 = (&Mutes)[tmp_i8];
        }
      }
      return 1;
    }
    G_MatchOnePlayer(tmp_pi2,local_81c,0x400);
    tmp_pc6 = (char *)va("^1unmute %s\n",local_81c);
    if (param_1 == 0) {
      DecolorString(tmp_pc6,local_41c);
      G_Printf(local_41c);
      return 0;
    }
  }
  else {
    if (param_1 == 0) {
      DecolorString("^9usage: ^g!unmute [name]\n",local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_pc6 = "^9usage: ^g!unmute [name]\n";
  }
  tmp_u5 = va("print \"%s\"",tmp_pc6);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
  return 0;
}

uint32_t G_shrubbot_splat(int param_1,int param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_940,0x24);
    tmp_i1 = ClientNumbersFromString(local_940,local_91c);
    if (tmp_i1 == 1) {
      tmp_i1 = local_91c[0] * 0x600;
      if (param_1 == 0) {
        if (1 < *(int *)(*(int *)(g_entities + tmp_i1 + 400) + 3000) - 1U) {
          tmp_pc2 = "^1splat error: ^9player isn\'t on a team^7\n";
          goto LAB_000d0d41;
        }
      }
      else {
        tmp_i4 = nitrox_GetAdminLevel(param_1,0);
        tmp_i5 = nitrox_GetAdminLevel(g_entities + tmp_i1,0);
        if (tmp_i4 < tmp_i5) {
          G_shrubbot_print(param_1,
                           "^1splat error: ^9Specified player has a higher level admin than you.^7\n"
                          );
          return 0;
        }
        if (1 < *(int *)(*(int *)(g_entities + tmp_i1 + 400) + 3000) - 1U) {
          tmp_pc2 = "^1splat error: ^9player isn\'t on a team^7\n";
          goto LAB_000d0c31;
        }
      }
      G_Damage(g_entities + tmp_i1,0,0,0,0,0,0x28,0);
      tmp_u3 = va("cpm \"^xsplat: ^7%s ^9went splat^7\"",
                 *(int *)(g_entities + local_91c[0] * 0x600 + 400) + 0x5f8);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
      return 1;
    }
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_pc2 = (char *)va("^1splat %s\n",local_81c);
    if (param_1 == 0) goto LAB_000d0d41;
  }
  else {
    if (param_1 == 0) {
      tmp_pc2 = "^9usage: ^g!splat ^7[name|slot#]^7\n";
LAB_000d0d41:
      DecolorString(tmp_pc2,local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_pc2 = "^9usage: ^g!splat ^7[name|slot#]^7\n";
  }
LAB_000d0c31:
  tmp_u3 = va("print \"%s\"",tmp_pc2);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
  return 0;
}

uint32_t G_shrubbot_gibme(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  
  if (param_1 == 0) {
    tmp_u2 = 0;
    G_shrubbot_print(0,"^1gibme error: ^9You are on the server console, you can\'t gib yourself^7\n"
                    );
  }
  else if (((*(byte *)(*(int *)(param_1 + 400) + 0xd) & 0x40) == 0) &&
          (0 < *(int *)(param_1 + 0x2c8))) {
    tmp_u2 = 0;
    if (g_unk_02a99a78 == 0) {
      if (*(int *)(*(int *)(param_1 + 400) + 3000) == 3) {
        tmp_u1 = va("print \"%s\"","^1gibme error: ^9You must be on a team to use ^g!gibme^7\n");
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
      }
      else {
        tmp_u2 = 1;
        G_Damage(param_1,param_1,param_1,0,0,0,0x28,0x40);
      }
    }
  }
  else {
    tmp_u2 = 0;
    tmp_u1 = va("print \"%s\"","^1gibme error: ^9You must be alive to use this command^7\n");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
  }
  return tmp_u2;
}

uint32_t G_shrubbot_slap(int param_1,int param_2)
{
  int tmp_i1;
  long tmp_l2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  char local_944 [4];
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_940,0x24);
    Q_SayArgv(param_2 + 2,local_944,4);
    tmp_l2 = strtol(local_944,(char **)0x0,10);
    if (tmp_l2 < 1) {
      tmp_l2 = 0x14;
    }
    tmp_i1 = ClientNumbersFromString(local_940,local_91c);
    if (tmp_i1 == 1) {
      tmp_i1 = local_91c[0] * 0x600;
      if (param_1 == 0) {
        tmp_i5 = *(int *)(g_entities + tmp_i1 + 400);
        if (1 < *(int *)(tmp_i5 + 3000) - 1U) {
          G_shrubbot_print_part_8();
          return 0;
        }
      }
      else {
        tmp_i5 = nitrox_GetAdminLevel(param_1,0);
        tmp_i6 = nitrox_GetAdminLevel(g_entities + tmp_i1,0);
        if (tmp_i5 < tmp_i6) {
          G_shrubbot_print(param_1,
                           "^1slap error: ^9Specified player has a higher admin level than you do.^7\n"
                          );
          return 0;
        }
        tmp_i5 = *(int *)(g_entities + tmp_i1 + 400);
        if (1 < *(int *)(tmp_i5 + 3000) - 1U) {
          tmp_u4 = va("print \"%s\"","^1slap error: ^9Player must be on a team.^7\n");
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
          return 0;
        }
      }
      tmp_i7 = local_91c[0] * 0x600;
      tmp_i6 = *(int *)(g_entities + tmp_i7 + 0x2c8);
      if ((0 < tmp_i6) && ((*(byte *)(tmp_i5 + 0xd) & 0x40) == 0)) {
        tmp_i8 = 1;
        if (tmp_l2 < tmp_i6) {
          tmp_i8 = tmp_i6 - tmp_l2;
        }
        *(int *)(g_entities + tmp_i7 + 0x2c8) = tmp_i8;
        tmp_i5 = nitrox_TempEventFromQueue(tmp_i5 + 0x14,0x66);
        *(uint32_t *)(tmp_i5 + 0xfc) = 2;
        *(uint32_t *)(tmp_i5 + 0x128) = 0x820;
        *(int *)(tmp_i5 + 300) = (tmp_i1 >> 9) * -0x55555555;
        tmp_u4 = va("cpm \"^xslap: ^7%s ^9was slapped^7\"",*(int *)(g_entities + tmp_i7 + 400) + 0x5f8
                  );
        trap_SendServerCommand(0xffffffff,tmp_u4);
        return 1;
      }
      tmp_u4 = va("^1slap error: ^7%s ^9is dead.^7\n",tmp_i5 + 0x5f8);
      G_shrubbot_print(param_1,tmp_u4);
      return 0;
    }
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_pc3 = (char *)va("^1slap %s\n",local_81c);
    if (param_1 == 0) {
LAB_000d1271:
      DecolorString(tmp_pc3,local_41c);
      G_Printf(local_41c);
      return 0;
    }
  }
  else {
    if (param_1 == 0) {
      tmp_pc3 = "^9usage: ^g!slap [name|slot#] (damage)^7\n";
      goto LAB_000d1271;
    }
    tmp_pc3 = "^9usage: ^g!slap [name|slot#] (damage)^7\n";
  }
  tmp_u4 = va("print \"%s\"",tmp_pc3);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
  return 0;
}

uint32_t G_shrubbot_panzerwar(int param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  uint8_t local_40 [44];
  uint32_t uStack_14;
  
  uStack_14 = 0xd1349;
  tmp_i2 = Q_SayArgc();
  if (tmp_i2 <= param_2 + 1) {
    tmp_pc3 = "^9usage : ^g!panzerwar [1|on|0|off]^7\n";
joined_r0x000d146c:
    if (param_1 != 0) {
      tmp_u4 = va("print \"%s\"",tmp_pc3);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
      return 0;
    }
    G_shrubbot_print_part_8();
    return 0;
  }
  Q_SayArgv(param_2 + 1,local_40,0x24);
  tmp_i2 = Q_stricmp(local_40,&g_unk_00258b23);
  if ((tmp_i2 == 0) || (tmp_i2 = Q_stricmp(local_40,"on"), tmp_i2 == 0)) {
    if (GHIDRA_FIELD(g_war, 12, 4) == 1) {
      tmp_pc3 = "^1panzerwar error: ^9Panzerwar is already enabled.^7\n";
      goto joined_r0x000d146c;
    }
    trap_Cvar_Set("g_war",&g_unk_00258b23);
    if (0 < g_unk_00abe93c) {
      tmp_i2 = 0;
      do {
        tmp_pi1 = &g_unk_00abe944 + tmp_i2;
        tmp_i2 = tmp_i2 + 1;
        G_Damage(g_entities + *tmp_pi1 * 0x600,0,0,0,0,0,0x28,0);
      } while (tmp_i2 < g_unk_00abe93c);
    }
    tmp_pc3 = "cpm \"^xpanzerwar: ^2Enabled !\"";
  }
  else {
    tmp_i2 = Q_stricmp(local_40,&g_unk_0024bfa6);
    if ((tmp_i2 != 0) && (tmp_i2 = Q_stricmp(local_40,"off"), tmp_i2 != 0)) {
      return 0;
    }
    if (GHIDRA_FIELD(g_war, 12, 4) != 1) {
      G_shrubbot_print(param_1,"^1panzerwar error: ^9Panzerwar is already disabled.^7\n");
      return 0;
    }
    trap_Cvar_Set("g_war",&g_unk_0024bfa6);
    Nit_GibAll();
    tmp_pc3 = "cpm \"^xpanzerwar: ^1Disabled !\"";
  }
  tmp_u4 = va(tmp_pc3);
  trap_SendServerCommand(0xffffffff,tmp_u4);
  return 1;
}

uint32_t G_shrubbot_sniperwar(int param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  uint8_t local_40 [44];
  uint32_t uStack_14;
  
  uStack_14 = 0xd1579;
  tmp_i2 = Q_SayArgc();
  if (tmp_i2 <= param_2 + 1) {
    tmp_pc3 = "^9usage : ^g!sniperwar [1|on|0|off]^7\n";
joined_r0x000d169c:
    if (param_1 != 0) {
      tmp_u4 = va("print \"%s\"",tmp_pc3);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
      return 0;
    }
    G_shrubbot_print_part_8();
    return 0;
  }
  Q_SayArgv(param_2 + 1,local_40,0x24);
  tmp_i2 = Q_stricmp(local_40,&g_unk_00258b23);
  if ((tmp_i2 == 0) || (tmp_i2 = Q_stricmp(local_40,"on"), tmp_i2 == 0)) {
    if (GHIDRA_FIELD(g_war, 12, 4) == 2) {
      tmp_pc3 = "^1sniperwar error: ^9Sniperwar is already enabled.^7\n";
      goto joined_r0x000d169c;
    }
    trap_Cvar_Set("g_war","2");
    if (0 < g_unk_00abe93c) {
      tmp_i2 = 0;
      do {
        tmp_pi1 = &g_unk_00abe944 + tmp_i2;
        tmp_i2 = tmp_i2 + 1;
        G_Damage(g_entities + *tmp_pi1 * 0x600,0,0,0,0,0,0x28,0);
      } while (tmp_i2 < g_unk_00abe93c);
    }
    tmp_pc3 = "cpm \"^xsniperwar: ^2Enabled !\"";
  }
  else {
    tmp_i2 = Q_stricmp(local_40,&g_unk_0024bfa6);
    if ((tmp_i2 != 0) && (tmp_i2 = Q_stricmp(local_40,"off"), tmp_i2 != 0)) {
      return 0;
    }
    if (GHIDRA_FIELD(g_war, 12, 4) != 2) {
      G_shrubbot_print(param_1,"^1sniperwar error: ^9Sniperwar is already disabled.^7\n");
      return 0;
    }
    trap_Cvar_Set("g_war",&g_unk_0024bfa6);
    Nit_GibAll();
    tmp_pc3 = "cpm \"^xsniperwar: ^1Disabled !\"";
  }
  tmp_u4 = va(tmp_pc3);
  trap_SendServerCommand(0xffffffff,tmp_u4);
  return 1;
}

uint32_t G_shrubbot_poison(int param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  int tmp_i5;
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tmp_i2 = Q_SayArgc();
  if (param_2 + 1 < tmp_i2) {
    Q_SayArgv(param_2 + 1,local_940,0x24);
    tmp_i2 = ClientNumbersFromString(local_940,local_91c);
    if (tmp_i2 == 1) {
      if (param_1 == 0) {
        tmp_i2 = *(int *)(g_entities + local_91c[0] * 0x600 + 400);
        if (1 < *(int *)(tmp_i2 + 3000) - 1U) {
          tmp_pc3 = "^1poison error: ^9Player must be on a team.^7\n";
          goto LAB_000d1981;
        }
LAB_000d19b0:
        *(uint *)(tmp_i2 + 0x68) = *(uint *)(tmp_i2 + 0x68) | 0x200000;
        tmp_pi1 = (int *)(g_entities + local_91c[0] * 0x600 + 400);
        *(uint32_t *)(*tmp_pi1 + 0x5300) = *(uint32_t *)(g_entities + local_91c[0] * 0x600);
        *(uint32_t *)(*tmp_pi1 + 0x5304) = 1;
        *(uint32_t *)(*tmp_pi1 + 0x53a0) = g_unk_00abe908;
        tmp_u4 = va("cpm \"^xpoison: ^7%s ^9was poisoned^7\"",*tmp_pi1 + 0x5f8);
        trap_SendServerCommand(0xffffffff,tmp_u4);
        return 1;
      }
      tmp_i2 = nitrox_GetAdminLevel(param_1,0);
      tmp_i5 = nitrox_GetAdminLevel(g_entities + local_91c[0] * 0x600,0);
      if (tmp_i2 < tmp_i5) {
        G_shrubbot_print(param_1,
                         "^1poison error: ^9Specified player has a higher admin level than you do.^7\n"
                        );
        return 0;
      }
      tmp_i2 = *(int *)(g_entities + local_91c[0] * 0x600 + 400);
      if (*(int *)(tmp_i2 + 3000) - 1U < 2) goto LAB_000d19b0;
      tmp_u4 = va("print \"%s\"","^1poison error: ^9Player must be on a team.^7\n");
      goto LAB_000d186f;
    }
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_pc3 = (char *)va("^1poison %s\n",local_81c);
    if (param_1 == 0) goto LAB_000d1981;
  }
  else {
    if (param_1 == 0) {
      tmp_pc3 = "^9usage: ^g!poison [name|slot#]^7\n";
LAB_000d1981:
      DecolorString(tmp_pc3,local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_pc3 = "^9usage: ^g!poison [name|slot#]^7\n";
  }
  tmp_u4 = va("print \"%s\"",tmp_pc3);
LAB_000d186f:
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
  return 0;
}

uint32_t G_shrubbot_blind(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  int tmp_i6;
  int local_550;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xd1a79;
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_540,0x24);
    tmp_i1 = Q_stricmp(local_540,&g_unk_0025a5f5);
    if (tmp_i1 == 0) {
      if (g_unk_00abe93c < 1) {
        local_550 = 0;
      }
      else {
        local_550 = 0;
        tmp_i1 = 0;
        do {
          tmp_i6 = (&g_unk_00abe944)[tmp_i1];
          if ((g_entities + tmp_i6 * 0x600 == (uint8_t *)0x0) || (param_1 == 0)) {
LAB_000d1b57:
            local_550 = local_550 + 1;
            *(uint *)(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 0x68) =
                 *(uint *)(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 0x68) | 0x400000;
          }
          else {
            tmp_i2 = nitrox_GetAdminLevel(param_1,0);
            tmp_i3 = nitrox_GetAdminLevel(g_entities + tmp_i6 * 0x600,0);
            if (tmp_i3 <= tmp_i2) goto LAB_000d1b57;
          }
          tmp_i1 = tmp_i1 + 1;
        } while (tmp_i1 < g_unk_00abe93c);
      }
      tmp_pc5 = "cpm \"^xblind: %d ^9players are now blind^7\"";
    }
    else {
      tmp_i1 = ClientNumbersFromString(local_540,local_51c);
      if (tmp_i1 != 1) {
        G_MatchOnePlayer(local_51c,local_41c,0x400);
        tmp_pc5 = (char *)va("^1blind %s\n",local_41c);
LAB_000d1c49:
        G_shrubbot_print(param_1,tmp_pc5);
        return 0;
      }
      if (param_1 != 0) {
        tmp_i1 = nitrox_GetAdminLevel(param_1,0);
        tmp_i6 = nitrox_GetAdminLevel(g_entities + local_51c[0] * 0x600,0);
        if (tmp_i1 < tmp_i6) {
          tmp_pc5 = "^1blind error: ^9Specified player has a higher admin level than you.^7\n";
          goto LAB_000d1c49;
        }
      }
      tmp_i1 = *(int *)(g_entities + local_51c[0] * 0x600 + 400);
      if (*(int *)(tmp_i1 + 3000) == 3) {
        tmp_pc5 = "^1blind error: ^9Can\'t blind spectators\n";
        goto LAB_000d1c49;
      }
      if ((*(uint *)(tmp_i1 + 0x68) & 0x400000) != 0) {
        tmp_pc5 = (char *)va("^1blind error: ^7%s ^9is already blind^7\n",tmp_i1 + 0x5f8);
        goto LAB_000d1c49;
      }
      *(uint *)(tmp_i1 + 0x68) = *(uint *)(tmp_i1 + 0x68) | 0x400000;
      local_550 = *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8;
      tmp_pc5 = "cpm \"^xblind: ^7%s ^9is now blind\"";
    }
    tmp_u4 = va(tmp_pc5,local_550);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    tmp_u4 = 1;
  }
  else {
    if (param_1 != 0) {
      tmp_u4 = va("print \"%s\"","^9usage: ^g!blind [name|slot#|-1]^7\n");
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
      return 0;
    }
    DecolorString("^9usage: ^g!blind [name|slot#|-1]^7\n",local_41c);
    G_Printf(local_41c);
    tmp_u4 = 0;
  }
  return tmp_u4;
}

uint32_t G_shrubbot_unblind(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  char *tmp_pc6;
  uint8_t *tmp_pu7;
  int local_550;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xd1d89;
  tmp_i2 = Q_SayArgc();
  if (param_2 + 1 < tmp_i2) {
    Q_SayArgv(param_2 + 1,local_540,0x24);
    tmp_i2 = Q_stricmp(local_540,&g_unk_0025a5f5);
    if (tmp_i2 == 0) {
      if (g_unk_00abe93c < 1) {
        local_550 = 0;
      }
      else {
        tmp_i2 = 0;
        local_550 = 0;
        do {
          tmp_i1 = (&g_unk_00abe944)[tmp_i2];
          if ((g_entities + tmp_i1 * 0x600 == (uint8_t *)0x0) || (param_1 == 0)) {
LAB_000d1e59:
            local_550 = local_550 + 1;
            *(uint *)(*(int *)(g_entities + tmp_i1 * 0x600 + 400) + 0x68) =
                 *(uint *)(*(int *)(g_entities + tmp_i1 * 0x600 + 400) + 0x68) & 0xffbfffff;
          }
          else {
            tmp_i3 = nitrox_GetAdminLevel(param_1,0);
            tmp_i4 = nitrox_GetAdminLevel(g_entities + tmp_i1 * 0x600,0);
            if (tmp_i4 <= tmp_i3) goto LAB_000d1e59;
          }
          tmp_i2 = tmp_i2 + 1;
        } while (tmp_i2 < g_unk_00abe93c);
      }
      tmp_pc6 = "cpm \"^xunblind: ^7%d ^9players can see again^7\"";
    }
    else {
      tmp_i2 = ClientNumbersFromString(local_540,local_51c);
      if (tmp_i2 != 1) {
        tmp_pu7 = local_41c;
        G_MatchOnePlayer(local_51c,tmp_pu7,0x400);
        tmp_pc6 = "^1unblind %s\n";
LAB_000d1fb0:
        tmp_u5 = va(tmp_pc6,tmp_pu7);
        G_shrubbot_print(param_1,tmp_u5);
        return 0;
      }
      tmp_i2 = *(int *)(g_entities + local_51c[0] * 0x600 + 400);
      if ((*(uint *)(tmp_i2 + 0x68) & 0x400000) == 0) {
        tmp_pu7 = (uint8_t *)(tmp_i2 + 0x5f8);
        tmp_pc6 = "^1unblind error: ^7%s ^9is not blind^7\n";
        goto LAB_000d1fb0;
      }
      *(uint *)(tmp_i2 + 0x68) = *(uint *)(tmp_i2 + 0x68) & 0xffbfffff;
      local_550 = *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8;
      tmp_pc6 = "cpm \"^xunblind: ^7%s ^9can see again\"";
    }
    tmp_u5 = va(tmp_pc6,local_550);
    trap_SendServerCommand(0xffffffff,tmp_u5);
    tmp_u5 = 1;
  }
  else {
    if (param_1 != 0) {
      tmp_u5 = va("print \"%s\"","^9usage: ^g!unblind [name|slot#]^7\n");
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
      return 0;
    }
    DecolorString("^9usage: ^g!unblind [name|slot#]^7\n",local_41c);
    G_Printf(local_41c);
    tmp_u5 = 0;
  }
  return tmp_u5;
}

uint32_t G_shrubbot_glow(int param_1,int param_2)
{
  uint *tmp_pu1;
  uint tmp_u2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint32_t tmp_u6;
  char *tmp_pc7;
  int tmp_i8;
  int local_550;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xd2009;
  tmp_i3 = Q_SayArgc();
  if (param_2 + 1 < tmp_i3) {
    Q_SayArgv(param_2 + 1,local_540,0x24);
    tmp_i3 = Q_stricmp(local_540,&g_unk_0025a5f5);
    if (tmp_i3 == 0) {
      if (g_unk_00abe93c < 1) {
        local_550 = 0;
      }
      else {
        local_550 = 0;
        tmp_i3 = 0;
        do {
          tmp_i8 = (&g_unk_00abe944)[tmp_i3];
          if ((g_entities + tmp_i8 * 0x600 == (uint8_t *)0x0) || (param_1 == 0)) {
LAB_000d20e7:
            tmp_u2 = *(uint *)(*(int *)(g_entities + tmp_i8 * 0x600 + 400) + 0x68);
            if ((tmp_u2 & 0x40) == 0) {
              local_550 = local_550 + 1;
              *(uint *)(*(int *)(g_entities + tmp_i8 * 0x600 + 400) + 0x68) = tmp_u2 | 0x40;
            }
          }
          else {
            tmp_i4 = nitrox_GetAdminLevel(param_1,0);
            tmp_i5 = nitrox_GetAdminLevel(g_entities + tmp_i8 * 0x600,0);
            if (tmp_i5 <= tmp_i4) goto LAB_000d20e7;
          }
          tmp_i3 = tmp_i3 + 1;
        } while (tmp_i3 < g_unk_00abe93c);
      }
      tmp_pc7 = "cpm \"^xglow: %d ^9players are now glowing^7\"";
    }
    else {
      tmp_i3 = ClientNumbersFromString(local_540,local_51c);
      if (tmp_i3 != 1) {
        G_MatchOnePlayer(local_51c,local_41c,0x400);
        tmp_pc7 = (char *)va("^1glow %s^7\n",local_41c);
LAB_000d21d9:
        G_shrubbot_print(param_1,tmp_pc7);
        return 0;
      }
      if (param_1 != 0) {
        tmp_i3 = nitrox_GetAdminLevel(param_1,0);
        tmp_i8 = nitrox_GetAdminLevel(g_entities + local_51c[0] * 0x600,0);
        if (tmp_i3 < tmp_i8) {
          tmp_pc7 = "^1glow error: ^9Specified player has a higher admin level than you do.^7\n";
          goto LAB_000d21d9;
        }
      }
      tmp_i3 = *(int *)(g_entities + local_51c[0] * 0x600 + 400);
      if (1 < *(int *)(tmp_i3 + 3000) - 1U) {
        tmp_pc7 = "^1glow error: ^9player must be on a team^7\n";
        goto LAB_000d21d9;
      }
      tmp_pu1 = (uint *)(tmp_i3 + 0x68);
      *tmp_pu1 = *tmp_pu1 ^ 0x40;
      local_550 = *(int *)(g_entities + local_51c[0] * 0x600 + 400);
      if ((*(byte *)(local_550 + 0x68) & 0x40) == 0) {
        local_550 = local_550 + 0x5f8;
        tmp_pc7 = "cpm \"^xglow: ^7%s ^9stopped glowing^7\"";
      }
      else {
        local_550 = local_550 + 0x5f8;
        tmp_pc7 = "cpm \"^xglow: ^7%s ^9is now glowing^7\"";
      }
    }
    tmp_u6 = va(tmp_pc7,local_550);
    trap_SendServerCommand(0xffffffff,tmp_u6);
    tmp_u6 = 1;
  }
  else {
    if (param_1 != 0) {
      tmp_u6 = va("print \"%s\"","^9usage: ^g!glow [name|slot#|-1]^7\n");
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
      return 0;
    }
    DecolorString("^9usage: ^g!glow [name|slot#|-1]^7\n",local_41c);
    G_Printf(local_41c);
    tmp_u6 = 0;
  }
  return tmp_u6;
}

uint32_t G_shrubbot_pants(int param_1,int param_2)
{
  uint tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  char *tmp_pc6;
  int tmp_i7;
  int local_550;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xd2309;
  tmp_i2 = Q_SayArgc();
  if (param_2 + 1 < tmp_i2) {
    Q_SayArgv(param_2 + 1,local_540,0x24);
    tmp_i2 = Q_stricmp(local_540,&g_unk_0025a5f5);
    if (tmp_i2 == 0) {
      if (g_unk_00abe93c < 1) {
        local_550 = 0;
      }
      else {
        local_550 = 0;
        tmp_i2 = 0;
        do {
          tmp_i7 = (&g_unk_00abe944)[tmp_i2] * 0x600;
          if ((g_entities + tmp_i7 == (uint8_t *)0x0) || (param_1 == 0)) {
LAB_000d23e7:
            if (0 < *(int *)(g_entities + tmp_i7 + 0x2c8)) {
              tmp_u1 = *(uint *)(*(int *)(g_entities + tmp_i7 + 400) + 0x68);
              if ((tmp_u1 & 0x10000) == 0) {
                local_550 = local_550 + 1;
                *(uint *)(*(int *)(g_entities + tmp_i7 + 400) + 0x68) = tmp_u1 | 0x10000;
              }
            }
          }
          else {
            tmp_i3 = nitrox_GetAdminLevel(param_1,0);
            tmp_i4 = nitrox_GetAdminLevel(g_entities + tmp_i7,0);
            if (tmp_i4 <= tmp_i3) goto LAB_000d23e7;
          }
          tmp_i2 = tmp_i2 + 1;
        } while (tmp_i2 < g_unk_00abe93c);
      }
      tmp_pc6 = "cpm \"^xpants: %d ^9players stripped^7\"";
    }
    else {
      tmp_i2 = ClientNumbersFromString(local_540,local_51c);
      if (tmp_i2 != 1) {
        G_MatchOnePlayer(local_51c,local_41c,0x400);
        tmp_pc6 = (char *)va("^1pants error: ^7%s^7\n",local_41c);
LAB_000d24e9:
        G_shrubbot_print(param_1,tmp_pc6);
        return 0;
      }
      if (param_1 != 0) {
        tmp_i2 = nitrox_GetAdminLevel(param_1,0);
        tmp_i7 = nitrox_GetAdminLevel(g_entities + local_51c[0] * 0x600,0);
        if (tmp_i2 < tmp_i7) {
          tmp_pc6 = "^1pants error: ^9Specified player has a higher admin level than you do.^7\n";
          goto LAB_000d24e9;
        }
      }
      tmp_i2 = *(int *)(g_entities + local_51c[0] * 0x600 + 400);
      if ((*(uint *)(tmp_i2 + 0x68) & 0x10000) != 0) {
        tmp_pc6 = "^1pants error: ^9Player is already stripped^7\n";
        goto LAB_000d24e9;
      }
      if (1 < *(int *)(tmp_i2 + 3000) - 1U) {
        tmp_pc6 = "^1pants error: ^9Player must be on a team^7\n";
        goto LAB_000d24e9;
      }
      if (*(int *)(g_entities + local_51c[0] * 0x600 + 0x2c8) == 0) {
        tmp_pc6 = "^1pants error: ^9Player must be alive^7\n";
        goto LAB_000d24e9;
      }
      *(uint *)(tmp_i2 + 0x68) = *(uint *)(tmp_i2 + 0x68) | 0x10000;
      local_550 = *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8;
      tmp_pc6 = "cpm \"^xpants: ^7%s ^9was stripped^7\"";
    }
    tmp_u5 = va(tmp_pc6,local_550);
    trap_SendServerCommand(0xffffffff,tmp_u5);
    tmp_u5 = 1;
  }
  else {
    if (param_1 != 0) {
      tmp_u5 = va("print \"%s\"","^9usage: ^g!pants [name|slot#|-1]^7\n");
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
      return 0;
    }
    DecolorString("^9usage: ^g!pants [name|slot#|-1]^7\n",local_41c);
    G_Printf(local_41c);
    tmp_u5 = 0;
  }
  return tmp_u5;
}

uint32_t G_shrubbot_freeze(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  int tmp_i6;
  int local_550;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xd2629;
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_540,0x24);
    tmp_i1 = Q_stricmp(local_540,&g_unk_0025a5f5);
    if (tmp_i1 == 0) {
      if (g_unk_00abe93c < 1) {
        local_550 = 0;
      }
      else {
        local_550 = 0;
        tmp_i1 = 0;
        do {
          tmp_i6 = (&g_unk_00abe944)[tmp_i1];
          if ((g_entities + tmp_i6 * 0x600 == (uint8_t *)0x0) || (param_1 == 0)) {
LAB_000d2707:
            if (*(int *)(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 0x539c) == 0) {
              local_550 = local_550 + 1;
              *(uint32_t *)(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 0x539c) = 1;
            }
          }
          else {
            tmp_i2 = nitrox_GetAdminLevel(param_1,0);
            tmp_i3 = nitrox_GetAdminLevel(g_entities + tmp_i6 * 0x600,0);
            if (tmp_i3 <= tmp_i2) goto LAB_000d2707;
          }
          tmp_i1 = tmp_i1 + 1;
        } while (tmp_i1 < g_unk_00abe93c);
      }
      tmp_pc5 = "cpm \"^xfreeze: %d ^9players frozen^7\"";
    }
    else {
      tmp_i1 = ClientNumbersFromString(local_540,local_51c);
      if (tmp_i1 != 1) {
        G_MatchOnePlayer(local_51c,local_41c,0x400);
        tmp_pc5 = (char *)va("^1freeze %s^7\n",local_41c);
LAB_000d2801:
        G_shrubbot_print(param_1,tmp_pc5);
        return 0;
      }
      if (param_1 != 0) {
        tmp_i1 = nitrox_GetAdminLevel(param_1,0);
        tmp_i6 = nitrox_GetAdminLevel(g_entities + local_51c[0] * 0x600,0);
        if (tmp_i1 < tmp_i6) {
          tmp_pc5 = "^1freeze error: ^9Specified player has a higher admin level than you do.^7\n";
          goto LAB_000d2801;
        }
      }
      tmp_i1 = *(int *)(g_entities + local_51c[0] * 0x600 + 400);
      if (1 < *(int *)(tmp_i1 + 3000) - 1U) {
        tmp_pc5 = "^1freeze error: ^9Player must be on a team^7\n";
        goto LAB_000d2801;
      }
      tmp_pc5 = "^1freeze error: ^9Player is already freezed^7\n";
      if (*(int *)(tmp_i1 + 0x539c) != 0) goto LAB_000d2801;
      *(uint32_t *)(tmp_i1 + 0x539c) = 1;
      local_550 = *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8;
      tmp_pc5 = "cpm \"^xfreeze: ^7%s ^9was frozen^7\"";
    }
    tmp_u4 = va(tmp_pc5,local_550);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    tmp_u4 = 1;
  }
  else {
    if (param_1 != 0) {
      tmp_u4 = va("print \"%s\"","^9usage: ^g!freeze [name|slot#|-1]^7\n");
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
      return 0;
    }
    DecolorString("^9usage: ^g!freeze [name|slot#|-1]^7\n",local_41c);
    G_Printf(local_41c);
    tmp_u4 = 0;
  }
  return tmp_u4;
}

uint32_t G_shrubbot_unfreeze(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  int tmp_i6;
  int local_550;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xd2929;
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_540,0x24);
    tmp_i1 = Q_stricmp(local_540,&g_unk_0025a5f5);
    if (tmp_i1 == 0) {
      if (g_unk_00abe93c < 1) {
        local_550 = 0;
      }
      else {
        local_550 = 0;
        tmp_i1 = 0;
        do {
          tmp_i6 = (&g_unk_00abe944)[tmp_i1];
          if ((g_entities + tmp_i6 * 0x600 == (uint8_t *)0x0) || (param_1 == 0)) {
LAB_000d2a07:
            if (*(int *)(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 0x539c) != 0) {
              local_550 = local_550 + 1;
              *(uint32_t *)(*(int *)(g_entities + tmp_i6 * 0x600 + 400) + 0x539c) = 0;
            }
          }
          else {
            tmp_i2 = nitrox_GetAdminLevel(param_1,0);
            tmp_i3 = nitrox_GetAdminLevel(g_entities + tmp_i6 * 0x600,0);
            if (tmp_i3 <= tmp_i2) goto LAB_000d2a07;
          }
          tmp_i1 = tmp_i1 + 1;
        } while (tmp_i1 < g_unk_00abe93c);
      }
      tmp_pc5 = "cpm \"^xunfreeze: %d players unfrozen^7\"";
    }
    else {
      tmp_i1 = ClientNumbersFromString(local_540,local_51c);
      if (tmp_i1 != 1) {
        G_MatchOnePlayer(local_51c,local_41c,0x400);
        tmp_pc5 = (char *)va("^1unfreeze %s^7\n",local_41c);
LAB_000d2b01:
        G_shrubbot_print(param_1,tmp_pc5);
        return 0;
      }
      if (param_1 != 0) {
        tmp_i1 = nitrox_GetAdminLevel(param_1,0);
        tmp_i6 = nitrox_GetAdminLevel(g_entities + local_51c[0] * 0x600,0);
        if (tmp_i1 < tmp_i6) {
          tmp_pc5 = "^1unfreeze error: ^9Specivied player has a higher admin level than you do.^7\n";
          goto LAB_000d2b01;
        }
      }
      tmp_i1 = *(int *)(g_entities + local_51c[0] * 0x600 + 400);
      if (1 < *(int *)(tmp_i1 + 3000) - 1U) {
        tmp_pc5 = "^1unfreeze error: ^9Player must be on a team^7\n";
        goto LAB_000d2b01;
      }
      if (*(int *)(tmp_i1 + 0x539c) == 0) {
        G_shrubbot_print(param_1,"^1unfreeze error: ^9Player is not freezed^7\n");
        return 0;
      }
      *(uint32_t *)(tmp_i1 + 0x539c) = 0;
      local_550 = *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8;
      tmp_pc5 = "cpm \"^xunfreeze: ^7%s ^9was unfroze^7\"";
    }
    tmp_u4 = va(tmp_pc5,local_550);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    tmp_u4 = 1;
  }
  else {
    if (param_1 != 0) {
      tmp_u4 = va("print \"%s\"","^9usage: ^g!unfreeze [name|slot#|-1]^7\n");
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
      return 0;
    }
    DecolorString("^9usage: ^g!unfreeze [name|slot#|-1]^7\n",local_41c);
    G_Printf(local_41c);
    tmp_u4 = 0;
  }
  return tmp_u4;
}

uint32_t G_shrubbot_burn(int param_1,int param_2)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  char *tmp_pc6;
  int local_550;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xd2c49;
  param_2 = param_2 + 1;
  tmp_i1 = Q_SayArgc();
  if (param_2 < tmp_i1) {
    Q_SayArgv(param_2,local_540,0x24);
    tmp_i1 = Q_stricmp(local_540,&g_unk_0025a5f5);
    if (tmp_i1 != 0) {
      tmp_i1 = ClientNumbersFromString(local_540,local_51c);
      if (tmp_i1 != 1) {
        G_MatchOnePlayer(local_51c,local_41c,0x400);
        tmp_pc6 = (char *)va("^1burn %s^7\n",local_41c);
LAB_000d2de4:
        G_shrubbot_print(param_1,tmp_pc6);
        return 0;
      }
      tmp_pu2 = g_entities + local_51c[0] * 0x600;
      tmp_i1 = _shrubbot_admin_higher(param_1,tmp_pu2);
      if (tmp_i1 == 0) {
        G_shrubbot_print(param_1,
                         "^1burn error: ^9Specified player has a higher admin level than you do.^7\n"
                        );
        return 0;
      }
      if (1 < *(int *)(*(int *)(g_entities + local_51c[0] * 0x600 + 400) + 3000) - 1U) {
        tmp_pc6 = "^1burn error: ^9player must be on a team^7\n";
        goto LAB_000d2de4;
      }
      G_BurnMeGood(tmp_pu2,tmp_pu2,0);
      local_550 = *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8;
      tmp_pc6 = "cpm \"^xburn: ^7%s ^9was set ablaze^7\"";
      goto LAB_000d2d48;
    }
  }
  else {
    Q_SayArgv(param_2,local_540,0x24);
    Q_stricmp(local_540,&g_unk_0025a5f5);
  }
  if (g_unk_00abe93c < 1) {
    local_550 = 0;
  }
  else {
    tmp_i1 = 0;
    local_550 = 0;
    do {
      tmp_pu2 = g_entities + (&g_unk_00abe944)[tmp_i1] * 0x600;
      if ((tmp_pu2 == (uint8_t *)0x0) || (param_1 == 0)) {
LAB_000d2d1b:
        G_BurnMeGood(tmp_pu2,tmp_pu2,0);
        local_550 = local_550 + 1;
      }
      else {
        tmp_i3 = nitrox_GetAdminLevel(param_1,0);
        tmp_i4 = nitrox_GetAdminLevel(tmp_pu2,0);
        if (tmp_i4 <= tmp_i3) goto LAB_000d2d1b;
      }
      tmp_i1 = tmp_i1 + 1;
    } while (tmp_i1 < g_unk_00abe93c);
  }
  tmp_pc6 = "cpm \"^xburn: %d ^9players burned^7\"";
LAB_000d2d48:
  tmp_u5 = va(tmp_pc6,local_550);
  trap_SendServerCommand(0xffffffff,tmp_u5);
  return 1;
}

uint32_t G_shrubbot_lol(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  long tmp_l7;
  char *tmp_pc8;
  uint8_t *tmp_pu9;
  int tmp_i10;
  int local_560;
  int local_558;
  char local_544 [4];
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xd2eb9;
  if (g_unk_00abe908 - lol_flood_control < 600) {
    if (param_1 == 0) {
      DecolorString("^1nade error: ^9denied by entities overflow protection.^7\n",local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_pc8 = "^1nade error: ^9denied by entities overflow protection.^7\n";
LAB_000d305d:
    tmp_u4 = va("print \"%s\"",tmp_pc8);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
    return 0;
  }
  lol_flood_control = g_unk_00abe908;
  tmp_i1 = Q_SayArgc();
  local_558 = 0;
  if (param_2 + 2 < tmp_i1) {
    Q_SayArgv(param_2 + 2,local_544,4);
    tmp_l7 = strtol(local_544,(char **)0x0,10);
    if (tmp_l7 < 1) {
      local_558 = 1;
    }
    else {
      local_558 = 0x10;
      if (tmp_l7 < 0x11) {
        local_558 = tmp_l7;
      }
    }
  }
  Q_SayArgv(param_2 + 1,local_540,0x24);
  tmp_i1 = Q_SayArgc();
  if (tmp_i1 <= param_2 + 1) {
    tmp_pc8 = "^9usage: ^g!nade [name|slot#|-1] [nades]^7\n";
    if (param_1 == 0) {
      G_shrubbot_print_part_8();
      return 0;
    }
    goto LAB_000d305d;
  }
  tmp_i1 = Q_stricmp(local_540,&g_unk_0025a5f5);
  if (tmp_i1 == 0) {
    tmp_i1 = G_GentitiesAvailable();
    if (0x3f < tmp_i1 + local_558 * g_unk_00abe938 * -2) {
      if (g_unk_00abe93c < 1) {
        local_560 = 0;
      }
      else {
        tmp_i1 = 0;
        local_560 = 0;
        do {
          tmp_pu9 = g_entities + (&g_unk_00abe944)[tmp_i1] * 0x600;
          if ((tmp_pu9 == (uint8_t *)0x0) || (param_1 == 0)) {
LAB_000d2fe7:
            G_createClusterNade(tmp_pu9,1,1);
            local_560 = local_560 + 1;
          }
          else {
            tmp_i2 = nitrox_GetAdminLevel(param_1,0);
            tmp_i3 = nitrox_GetAdminLevel(tmp_pu9,0);
            if (tmp_i3 <= tmp_i2) goto LAB_000d2fe7;
          }
          tmp_i1 = tmp_i1 + 1;
        } while (tmp_i1 < g_unk_00abe93c);
      }
      tmp_pc8 = "cpm \"^xnade: ^7%d players naded^7\"";
LAB_000d301c:
      tmp_u4 = va(tmp_pc8,local_560);
      trap_SendServerCommand(0xffffffff,tmp_u4);
      return 1;
    }
  }
  else {
    tmp_i1 = ClientNumbersFromString(local_540,local_51c);
    if (tmp_i1 < 2) {
      if (tmp_i1 == 1) {
        tmp_pu9 = g_entities + local_51c[0] * 0x600;
        if (param_1 != 0) {
          tmp_i1 = nitrox_GetAdminLevel(param_1,0);
          tmp_i2 = nitrox_GetAdminLevel(tmp_pu9,0);
          if (tmp_i1 < tmp_i2) {
            tmp_pc8 = "^1nade error: ^9Specified player has a higher admin level than you do.^7\n";
            goto LAB_000d3455;
          }
        }
        if (*(int *)(*(int *)(g_entities + local_51c[0] * 0x600 + 400) + 3000) == 3) {
          tmp_u4 = va("^1nade error: ^7%s ^9must be on a team to be naded^7\n",
                     *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8);
          G_shrubbot_print(param_1,tmp_u4);
          return 1;
        }
        if (local_558 == 0) {
          G_createClusterNade(tmp_pu9,1,1);
        }
        else {
          G_createClusterNade(tmp_pu9,local_558,1);
        }
        local_560 = *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8;
        tmp_pc8 = "cpm \"^xnade: ^7%s ^9was naded^7\"";
        goto LAB_000d301c;
      }
      G_MatchOnePlayer(local_51c,local_41c,0x400);
      tmp_pc8 = (char *)va("^1nade %s\n",local_41c);
      goto LAB_000d3455;
    }
    tmp_i2 = G_GentitiesAvailable();
    if (0x3f < tmp_i2 + local_558 * tmp_i1 * -3) {
      tmp_i2 = 0;
      do {
        tmp_i3 = local_51c[tmp_i2];
        tmp_i10 = tmp_i3 * 0x600;
        tmp_pu9 = g_entities + tmp_i10;
        if (param_1 == 0) {
          if (*(int *)(*(int *)(g_entities + tmp_i10 + 400) + 3000) - 1U < 2) {
LAB_000d3280:
            if (local_558 == 0) {
              G_createClusterNade(tmp_pu9,1,1);
            }
            else {
              G_createClusterNade(tmp_pu9,local_558,1);
            }
            tmp_u4 = va("cpm \"^xnade: ^7%s ^9was naded\"",
                       *(int *)(g_entities + tmp_i3 * 0x600 + 400) + 0x5f8);
            trap_SendServerCommand(0xffffffff,tmp_u4);
          }
          else {
            tmp_u4 = va("^1nade error: ^7%s ^9must be on a team to be naded^7\n",
                       *(int *)(g_entities + tmp_i10 + 400) + 0x5f8);
            DecolorString(tmp_u4,local_41c);
            G_Printf(local_41c);
          }
        }
        else {
          tmp_i5 = nitrox_GetAdminLevel(param_1,0);
          tmp_i6 = nitrox_GetAdminLevel(tmp_pu9,0);
          if (tmp_i5 < tmp_i6) {
            tmp_i10 = *(int *)(g_entities + tmp_i10 + 400);
            tmp_pc8 = "^1nade error: ^7%s ^9has a higher admin level than you do.^7\n";
          }
          else {
            tmp_i10 = *(int *)(g_entities + tmp_i10 + 400);
            tmp_pc8 = "^1nade error: ^7%s ^9must be on a team to be naded^7\n";
            if (*(int *)(tmp_i10 + 3000) - 1U < 2) goto LAB_000d3280;
          }
          tmp_u4 = va(tmp_pc8,tmp_i10 + 0x5f8);
          tmp_u4 = va("print \"%s\"",tmp_u4);
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
        }
        tmp_i2 = tmp_i2 + 1;
        if (tmp_i2 == tmp_i1) {
          return 1;
        }
      } while( true );
    }
  }
  tmp_pc8 = "^1nade error: ^9too many entities, use fewer nades or nade fewer players.^7\n";
LAB_000d3455:
  G_shrubbot_print(param_1,tmp_pc8);
  return 0;
}

uint32_t G_shrubbot_pop(int param_1,int param_2)
{
  uint tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  char *tmp_pc8;
  int tmp_i9;
  uint8_t *tmp_pu10;
  int local_55c;
  uint32_t local_54c;
  uint32_t local_548;
  uint32_t local_544;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1036];
  
  local_54c = 0x40a00000;
  local_548 = 0x40a00000;
  local_544 = 0x40a00000;
  Q_SayArgv(param_2 + 1,local_540,0x24);
  tmp_i2 = Q_stricmp(local_540,&g_unk_0025a5f5);
  if (tmp_i2 == 0) {
    if (g_unk_00abe93c < 1) {
      local_55c = 0;
    }
    else {
      local_55c = 0;
      tmp_i2 = 0;
      do {
        while( true ) {
          tmp_i9 = (&g_unk_00abe944)[tmp_i2];
          tmp_pu10 = g_entities + tmp_i9 * 0x600;
          if ((tmp_pu10 == (uint8_t *)0x0) || (param_1 == 0)) break;
          tmp_i3 = nitrox_GetAdminLevel(param_1,0);
          tmp_i4 = nitrox_GetAdminLevel(tmp_pu10,0);
          if (tmp_i4 <= tmp_i3) break;
LAB_000d35c0:
          tmp_i2 = tmp_i2 + 1;
          if (g_unk_00abe93c <= tmp_i2) goto LAB_000d3670;
        }
        tmp_u1 = *(uint *)(*(int *)(g_entities + tmp_i9 * 0x600 + 400) + 0x68);
        if ((tmp_u1 & 0x1000) != 0) goto LAB_000d35c0;
        tmp_i2 = tmp_i2 + 1;
        *(uint *)(*(int *)(g_entities + tmp_i9 * 0x600 + 400) + 0x68) = tmp_u1 | 0x1000;
        tmp_u5 = DirToByte(&local_54c);
        G_AddEvent(tmp_pu10,0x33,tmp_u5);
        local_55c = local_55c + 1;
      } while (tmp_i2 < g_unk_00abe93c);
    }
LAB_000d3670:
    tmp_pc8 = "cpm \"^xpop: %d ^9players pop\'d\"";
LAB_000d367e:
    tmp_u5 = va(tmp_pc8,local_55c);
    trap_SendServerCommand(0xffffffff,tmp_u5);
    return 1;
  }
  tmp_i2 = ClientNumbersFromString(local_540,local_51c);
  if (1 < tmp_i2) {
    tmp_i9 = 0;
    do {
      tmp_i3 = local_51c[tmp_i9];
      tmp_i4 = tmp_i3 * 0x600;
      if (param_1 == 0) {
        if (*(int *)(*(int *)(g_entities + tmp_i4 + 400) + 3000) - 1U < 2) {
LAB_000d37c0:
          tmp_u5 = DirToByte(&local_54c);
          G_AddEvent(g_entities + tmp_i4,0x33,tmp_u5);
          tmp_u5 = va("cpm \"^xpop: ^7%s ^9was pop\'d^7\"",
                     *(int *)(g_entities + tmp_i3 * 0x600 + 400) + 0x5f8);
          trap_SendServerCommand(0xffffffff,tmp_u5);
        }
        else {
          tmp_u5 = va("^1pop error: ^7%s ^9must be on a team to be popped^7\n",
                     *(int *)(g_entities + tmp_i4 + 400) + 0x5f8);
          DecolorString(tmp_u5,local_41c);
          G_Printf(local_41c);
        }
      }
      else {
        tmp_i6 = nitrox_GetAdminLevel(param_1,0);
        tmp_i7 = nitrox_GetAdminLevel(g_entities + tmp_i4,0);
        if (tmp_i6 < tmp_i7) {
          tmp_i6 = *(int *)(g_entities + tmp_i4 + 400);
          tmp_pc8 = "^1pop error: ^7%s ^9has a higher admin level than you do.^7\n";
        }
        else {
          tmp_i6 = *(int *)(g_entities + tmp_i4 + 400);
          tmp_pc8 = "^1pop error: ^7%s ^9must be on a team to be popped^7\n";
          if (*(int *)(tmp_i6 + 3000) - 1U < 2) goto LAB_000d37c0;
        }
        tmp_u5 = va(tmp_pc8,tmp_i6 + 0x5f8);
        tmp_u5 = va("print \"%s\"",tmp_u5);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
      }
      tmp_i9 = tmp_i9 + 1;
      if (tmp_i9 == tmp_i2) {
        return 1;
      }
    } while( true );
  }
  if (tmp_i2 == 1) {
    if (param_1 != 0) {
      tmp_i2 = nitrox_GetAdminLevel(param_1,0);
      tmp_i9 = nitrox_GetAdminLevel(g_entities + local_51c[0] * 0x600,0);
      if (tmp_i2 < tmp_i9) {
        tmp_pc8 = "^1pop error: ^9Specified player has a higher ^7admin level than you do.^7\n";
        goto LAB_000d38eb;
      }
    }
    if (*(int *)(*(int *)(g_entities + local_51c[0] * 0x600 + 400) + 3000) - 1U < 2) {
      tmp_u5 = DirToByte(&local_54c);
      G_AddEvent(g_entities + local_51c[0] * 0x600,0x33,tmp_u5);
      local_55c = *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8;
      tmp_pc8 = "cpm \"^xpop: ^7%s ^9was pop\'d^7\" -1";
      goto LAB_000d367e;
    }
    tmp_pc8 = "^1pop error: ^9Player must be on a team^7\n";
  }
  else {
    G_MatchOnePlayer(local_51c,local_41c,0x400);
    tmp_pc8 = (char *)va("^1pop %s\n",local_41c);
  }
LAB_000d38eb:
  G_shrubbot_print(param_1,tmp_pc8);
  return 0;
}

uint32_t G_shrubbot_pip(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  char *tmp_pc7;
  uint8_t *tmp_pu8;
  int tmp_i9;
  int local_55c;
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1036];
  
  Q_SayArgv(param_2 + 1,local_540,0x24);
  tmp_i1 = Q_stricmp(local_540,&g_unk_0025a5f5);
  if (tmp_i1 == 0) {
    if (g_unk_00abe93c < 1) {
      local_55c = 0;
    }
    else {
      tmp_i1 = 0;
      local_55c = 0;
      do {
        tmp_pu8 = g_entities + (&g_unk_00abe944)[tmp_i1] * 0x600;
        if ((tmp_pu8 == (uint8_t *)0x0) || (param_1 == 0)) {
LAB_000d3a67:
          G_MakePip(tmp_pu8);
          local_55c = local_55c + 1;
        }
        else {
          tmp_i2 = nitrox_GetAdminLevel(param_1,0);
          tmp_i3 = nitrox_GetAdminLevel(tmp_pu8,0);
          if (tmp_i3 <= tmp_i2) goto LAB_000d3a67;
        }
        tmp_i1 = tmp_i1 + 1;
      } while (tmp_i1 < g_unk_00abe93c);
    }
    tmp_pc7 = "cpm \"^xpip: %d ^9players pip\'d^7\"";
LAB_000d3a8a:
    tmp_u4 = va(tmp_pc7,local_55c);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    return 1;
  }
  tmp_i1 = ClientNumbersFromString(local_540,local_51c);
  if (1 < tmp_i1) {
    tmp_i2 = 0;
    do {
      tmp_i3 = local_51c[tmp_i2];
      tmp_i9 = tmp_i3 * 0x600;
      if (param_1 == 0) {
        if (*(int *)(*(int *)(g_entities + tmp_i9 + 400) + 3000) - 1U < 2) {
LAB_000d3bf0:
          G_MakePip(g_entities + tmp_i9);
          tmp_u4 = va("cpm \"^xpip: ^7%s ^9was pip\'d^7\"",
                     *(int *)(g_entities + tmp_i3 * 0x600 + 400) + 0x5f8);
          trap_SendServerCommand(0xffffffff,tmp_u4);
        }
        else {
          tmp_u4 = va("^1pip error: ^7%s ^9must be on a team^7\n",
                     *(int *)(g_entities + tmp_i9 + 400) + 0x5f8);
          DecolorString(tmp_u4,local_41c);
          G_Printf(local_41c);
        }
      }
      else {
        tmp_i5 = nitrox_GetAdminLevel(param_1,0);
        tmp_i6 = nitrox_GetAdminLevel(g_entities + tmp_i9,0);
        if (tmp_i5 < tmp_i6) {
          tmp_i5 = *(int *)(g_entities + tmp_i9 + 400);
          tmp_pc7 = "^1pip error: ^7%s ^9has a higher admin level than you do.\n";
        }
        else {
          tmp_i5 = *(int *)(g_entities + tmp_i9 + 400);
          tmp_pc7 = "^1pip error: ^7%s ^9must be on a team^7\n";
          if (*(int *)(tmp_i5 + 3000) - 1U < 2) goto LAB_000d3bf0;
        }
        tmp_u4 = va(tmp_pc7,tmp_i5 + 0x5f8);
        tmp_u4 = va("print \"%s\"",tmp_u4);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
      }
      tmp_i2 = tmp_i2 + 1;
      if (tmp_i2 == tmp_i1) {
        return 1;
      }
    } while( true );
  }
  if (tmp_i1 == 1) {
    if (param_1 != 0) {
      tmp_i1 = nitrox_GetAdminLevel(param_1,0);
      tmp_i2 = nitrox_GetAdminLevel(g_entities + local_51c[0] * 0x600,0);
      if (tmp_i1 < tmp_i2) {
        tmp_pc7 = "^1pip error: ^9Specified player has a higher admin level than you do.^7\n";
        goto LAB_000d3d1f;
      }
    }
    if (*(int *)(*(int *)(g_entities + local_51c[0] * 0x600 + 400) + 3000) - 1U < 2) {
      G_MakePip(g_entities + local_51c[0] * 0x600);
      local_55c = *(int *)(g_entities + local_51c[0] * 0x600 + 400) + 0x5f8;
      tmp_pc7 = "cpm \"^xpip: ^7%s ^9was pip\'d^7\"";
      goto LAB_000d3a8a;
    }
    tmp_pc7 = "^1pip error: ^9Player must be on a team\n";
  }
  else {
    G_MatchOnePlayer(local_51c,local_41c,0x400);
    tmp_pc7 = (char *)va("^1pip %s\n",local_41c);
  }
LAB_000d3d1f:
  G_shrubbot_print(param_1,tmp_pc7);
  return 0;
}

uint32_t G_shrubbot_fling(int param_1,int param_2)
{
  int *tmp_pi1;
  char *tmp_pc2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  uint32_t tmp_u8;
  char *tmp_pc9;
  uint8_t *tmp_pu10;
  int local_554;
  int local_550;
  char local_549;
  char local_548 [8];
  uint8_t local_540 [36];
  int local_51c [64];
  uint8_t local_41c [1036];
  
  Q_SayArgv(param_2,&local_549,9);
  tmp_pc9 = &local_549;
  if (local_549 == '!') {
    tmp_pc9 = local_548;
  }
  tmp_pc2 = strstr("throw",tmp_pc9);
  local_554 = 1;
  if (tmp_pc2 == (char *)0x0) {
    tmp_pc2 = strstr("launch",tmp_pc9);
    local_554 = 2;
    if (tmp_pc2 == (char *)0x0) {
      tmp_pc9 = strstr("fling",tmp_pc9);
      local_554 = -(uint)(tmp_pc9 == (char *)0x0);
    }
  }
  tmp_i3 = Q_SayArgc();
  param_2 = param_2 + 1;
  if (param_2 < tmp_i3) {
    Q_SayArgv(param_2,local_540,0x24);
    tmp_i3 = ClientNumbersFromString(local_540,local_51c);
    if (tmp_i3 < 2) {
      if (tmp_i3 != 1) {
        G_MatchOnePlayer(local_51c,local_41c,0x400);
        if (local_554 == 1) {
          tmp_pc9 = "^1throw %s\n";
        }
        else if (local_554 == 2) {
          tmp_pc9 = "^1launch %s\n";
        }
        else {
          if (local_554 != 0) {
            return 0;
          }
          tmp_pc9 = "^1fling %s\n";
        }
        tmp_u8 = va(tmp_pc9,local_41c);
        G_shrubbot_print(param_1,tmp_u8);
        return 0;
      }
      tmp_i4 = local_51c[0] * 0x600;
      tmp_i3 = _shrubbot_admin_higher(param_1,g_entities + tmp_i4);
      if (tmp_i3 != 0) {
        tmp_i3 = G_FlingClient(g_entities + tmp_i4,local_554);
        if (tmp_i3 == 0) {
          return 1;
        }
        if (local_554 == 1) {
          tmp_i3 = *(int *)(g_entities + tmp_i4 + 400) + 0x5f8;
          tmp_pc9 = "cpm \"^xthrow: ^7%s ^9was thrown^7\"";
        }
        else if (local_554 == 2) {
          tmp_i3 = *(int *)(g_entities + tmp_i4 + 400) + 0x5f8;
          tmp_pc9 = "cpm \"^xlaunch: ^7%s ^9was launched^7\"";
        }
        else {
          if (local_554 != 0) {
            return 1;
          }
          tmp_i3 = *(int *)(g_entities + tmp_i4 + 400) + 0x5f8;
          tmp_pc9 = "cpm \"^xfling: ^7%s ^9was flung^7\"";
        }
        tmp_u8 = va(tmp_pc9,tmp_i3);
        trap_SendServerCommand(0xffffffff,tmp_u8);
        return 1;
      }
      if (local_554 == 1) {
        tmp_i3 = *(int *)(g_entities + tmp_i4 + 400) + 0x5f8;
        tmp_pc9 = "^1throw error: ^7%s ^9has a higher admin level than you.^7\n";
      }
      else if (local_554 == 2) {
        tmp_i3 = *(int *)(g_entities + tmp_i4 + 400) + 0x5f8;
        tmp_pc9 = "^1launch error: ^7%s ^9has a higher admin level than you.^7\n";
      }
      else {
        if (local_554 != 0) {
          return 0;
        }
        tmp_i3 = *(int *)(g_entities + tmp_i4 + 400) + 0x5f8;
        tmp_pc9 = "^1fling error: ^7%s ^9has a higher admin level than you.^7\n";
      }
      tmp_u8 = va(tmp_pc9,tmp_i3);
      G_shrubbot_print(param_1,tmp_u8);
      return 0;
    }
    if (param_1 == 0) {
      tmp_i4 = 0;
      local_550 = 0;
      do {
        tmp_pi1 = local_51c + tmp_i4;
        tmp_i4 = tmp_i4 + 1;
        tmp_i5 = G_FlingClient(g_entities + *tmp_pi1 * 0x600,local_554);
        local_550 = local_550 + tmp_i5;
      } while (tmp_i4 != tmp_i3);
    }
    else {
      tmp_i4 = 0;
      local_550 = 0;
      do {
        tmp_i5 = local_51c[tmp_i4];
        tmp_i6 = nitrox_GetAdminLevel(param_1,0);
        tmp_i7 = nitrox_GetAdminLevel(g_entities + tmp_i5 * 0x600,0);
        if (tmp_i7 <= tmp_i6) {
          tmp_i5 = G_FlingClient(g_entities + tmp_i5 * 0x600,local_554);
          local_550 = local_550 + tmp_i5;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 != tmp_i3);
    }
  }
  else {
    Q_SayArgv(param_2,local_540,0x24);
    if (g_unk_00abe93c < 1) {
      local_550 = 0;
    }
    else {
      tmp_i3 = 0;
      local_550 = 0;
      do {
        tmp_pu10 = g_entities + (&g_unk_00abe944)[tmp_i3] * 0x600;
        if ((tmp_pu10 == (uint8_t *)0x0) || (param_1 == 0)) {
LAB_000d3ea7:
          tmp_i4 = G_FlingClient(tmp_pu10,local_554);
          local_550 = local_550 + tmp_i4;
        }
        else {
          tmp_i4 = nitrox_GetAdminLevel(param_1,0);
          tmp_i5 = nitrox_GetAdminLevel(tmp_pu10,0);
          if (tmp_i5 <= tmp_i4) goto LAB_000d3ea7;
        }
        tmp_i3 = tmp_i3 + 1;
      } while (tmp_i3 < g_unk_00abe93c);
    }
  }
  if (local_554 == 1) {
    tmp_pc9 = "cpm \"^xthrow: %d ^9players thrown^7\"";
  }
  else if (local_554 == 2) {
    tmp_pc9 = "cpm \"^xlaunch: %d ^9players launched^7\"";
  }
  else {
    if (local_554 != 0) {
      return 1;
    }
    tmp_pc9 = "cpm \"^xfling: %d ^9players flung^7\"";
  }
  tmp_u8 = va(tmp_pc9,local_550);
  trap_SendServerCommand(0xffffffff,tmp_u8);
  return 1;
}

uint32_t G_shrubbot_disorient(int param_1,int param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint8_t local_940 [36];
  int local_91c [64];
  uint8_t local_81c [1024];
  uint8_t local_41c [1036];
  
  tmp_i1 = Q_SayArgc();
  if (param_2 + 1 < tmp_i1) {
    Q_SayArgv(param_2 + 1,local_940,0x24);
    tmp_i1 = ClientNumbersFromString(local_940,local_91c);
    if (tmp_i1 == 1) {
      if (param_1 == 0) {
        tmp_i1 = *(int *)(g_entities + local_91c[0] * 0x600 + 400);
        if (1 < *(int *)(tmp_i1 + 3000) - 1U) {
          G_shrubbot_print_part_8();
          return 0;
        }
      }
      else {
        tmp_i1 = nitrox_GetAdminLevel(param_1,0);
        tmp_i4 = nitrox_GetAdminLevel(g_entities + local_91c[0] * 0x600,0);
        if (tmp_i1 < tmp_i4) {
          G_shrubbot_print(param_1,
                           "^1disorient error: ^9Specified player has a higher admin level than you do.\n"
                          );
          return 0;
        }
        tmp_i1 = *(int *)(g_entities + local_91c[0] * 0x600 + 400);
        if (1 < *(int *)(tmp_i1 + 3000) - 1U) {
          tmp_u3 = va("print \"%s\"","^1disorient error: ^9Player must be on a team\n");
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
          return 0;
        }
      }
      if (*(int *)(tmp_i1 + 0x530c) == 0) {
        *(uint32_t *)(tmp_i1 + 0x530c) = 1;
        tmp_u3 = va("cpm \"^xdisorient: ^7%s ^9is disoriented\" -1",
                   *(int *)(g_entities + local_91c[0] * 0x600 + 400) + 0x5f8);
        trap_SendServerCommand(0xffffffff,tmp_u3);
        return 1;
      }
      tmp_u3 = va("^1disorient error: ^7%s ^9is already disoriented\n",tmp_i1 + 0x5f8);
      G_shrubbot_print(param_1,tmp_u3);
      return 0;
    }
    G_MatchOnePlayer(local_91c,local_81c,0x400);
    tmp_pc2 = (char *)va("^1disorient %s\n",local_81c);
    if (param_1 == 0) {
LAB_000d44a1:
      DecolorString(tmp_pc2,local_41c);
      G_Printf(local_41c);
      return 0;
    }
  }
  else {
    if (param_1 == 0) {
      tmp_pc2 = "^9usage: ^g!disorient [name|slot#]\n";
      goto LAB_000d44a1;
    }
    tmp_pc2 = "^9usage: ^g!disorient [name|slot#]\n";
  }
  tmp_u3 = va("print \"%s\"",tmp_pc2);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
  return 0;
}

uint32_t G_shrubbot_finger(int param_1,int param_2)
{
  int *tmp_pi1;
  uint32_t *tmp_pu2;
  uint tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  uint32_t tmp_u6;
  char *tmp_pc7;
  uint32_t tmp_u8;
  uint32_t tmp_u9;
  size_t tmp_s10;
  int tmp_i11;
  int local_b58;
  uint8_t local_b40 [36];
  int local_b1c [64];
  uint32_t local_a1c;
  uint32_t local_a18 [63];
  uint32_t local_91c;
  uint32_t local_918 [319];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xd458d;
  local_918[0x3f] = 0;
  tmp_u3 = 0;
  do {
    tmp_u4 = tmp_u3;
    *(uint32_t *)((int)local_918 + tmp_u4 + 0x100) = 0;
    *(uint32_t *)((int)local_918 + tmp_u4 + 0x104) = 0;
    tmp_u3 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0x3f8);
  *(uint32_t *)((int)local_918 + tmp_u4 + 0x108) = 0;
  local_a1c = 0;
  tmp_u3 = 0;
  do {
    tmp_u4 = tmp_u3;
    *(uint32_t *)((int)local_a18 + tmp_u4) = 0;
    *(uint32_t *)((int)local_a18 + tmp_u4 + 4) = 0;
    tmp_u3 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0xf8);
  *(uint32_t *)((int)local_a18 + tmp_u4 + 8) = 0;
  local_91c = 0;
  tmp_u3 = 0;
  do {
    tmp_u4 = tmp_u3;
    *(uint32_t *)((int)local_918 + tmp_u4) = 0;
    *(uint32_t *)((int)local_918 + tmp_u4 + 4) = 0;
    tmp_u3 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0xf8);
  *(uint32_t *)((int)local_918 + tmp_u4 + 8) = 0;
  tmp_i5 = Q_SayArgc();
  if (tmp_i5 != param_2 + 2) {
    if (param_1 == 0) {
      DecolorString("^9usage: ^g!finger [name|slot#]\n",local_41c);
      G_Printf(local_41c);
      return 0;
    }
    tmp_pc7 = "^9usage: ^g!finger [name|slot#]\n";
LAB_000d4662:
    tmp_u6 = va("print \"%s\"",tmp_pc7);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
    return 0;
  }
  Q_SayArgv(param_2 + 1,local_b40,0x24);
  tmp_i5 = ClientNumbersFromString(local_b40,local_b1c);
  if (tmp_i5 != 1) {
    G_MatchOnePlayer(local_b1c,local_41c,0x400);
    tmp_pc7 = (char *)va("^1finger %s\n",local_41c);
    if (param_1 == 0) {
      G_shrubbot_print_part_8();
      return 0;
    }
    goto LAB_000d4662;
  }
  local_b58 = local_b1c[0] * 0x600;
  tmp_pc7 = (char *)(*(int *)(g_entities + local_b58 + 400) + 0x61c);
  tmp_u6 = nitrox_GetAdminLevel(g_entities + local_b58,0);
  tmp_i5 = GetUserPointer(g_entities + local_b58);
  tmp_u8 = va("^9Information about ^7%s\n",*(int *)(g_entities + local_b58 + 400) + 0x5f8);
  local_b58 = local_b58 >> 9;
  if (param_1 == 0) {
    DecolorString(tmp_u8,local_41c);
    G_Printf(local_41c);
    tmp_u8 = va("^9Slot:   ^g%i\n",local_b58 * -0x55555555);
    DecolorString(tmp_u8,local_41c);
    G_Printf(local_41c);
  }
  else {
    tmp_u8 = va("print \"%s\"",tmp_u8);
    tmp_i11 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    trap_SendServerCommand(tmp_i11,tmp_u8);
    tmp_u8 = va("^9Slot:   ^g%i\n",local_b58 * -0x55555555);
    tmp_u8 = va("print \"%s\"",tmp_u8);
    trap_SendServerCommand(tmp_i11,tmp_u8);
  }
  local_b58 = local_b58 * -0x55555555;
  tmp_pi1 = (int *)(g_entities + local_b1c[0] * 0x600 + 400);
  if (*(int *)(*tmp_pi1 + 3000) == 3) {
    tmp_u8 = BG_TeamName(3);
    tmp_u8 = va("^9Team:   ^7%s\n",tmp_u8);
    G_shrubbot_print(param_1,tmp_u8);
    tmp_s10 = strlen(tmp_pc7);
    if (tmp_s10 == 0x20) {
      tmp_u8 = va("^9NGUID:  ^g%s\n",tmp_pc7);
      G_shrubbot_print(param_1,tmp_u8);
      tmp_u8 = va("^9IP:     ^g%s\n",*tmp_pi1 + 0x653);
      if (param_1 != 0) goto LAB_000d4daf;
      goto LAB_000d4bf8;
    }
    if (param_1 == 0) goto LAB_000d4bb0;
    tmp_i11 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
LAB_000d48a9:
    tmp_u8 = va("print \"%s\"","^9NGUID:  ^1INVALID%s\n");
    trap_SendServerCommand(tmp_i11,tmp_u8);
    tmp_u8 = va("^9IP:     ^g%s\n",*(int *)(g_entities + local_b1c[0] * 0x600 + 400) + 0x653);
LAB_000d48f5:
    tmp_u8 = va("print \"%s\"",tmp_u8);
    trap_SendServerCommand(tmp_i11,tmp_u8);
    tmp_u8 = va("^9MAC:    ^g%s\n",*(int *)(g_entities + local_b1c[0] * 0x600 + 400) + 0xaf4);
    tmp_u8 = va("print \"%s\"",tmp_u8);
    trap_SendServerCommand(tmp_i11,tmp_u8);
  }
  else {
    tmp_u8 = BG_ClassnameForNumber(*(uint32_t *)(*tmp_pi1 + 0xbc8));
    tmp_u9 = BG_TeamName(*(uint32_t *)(*tmp_pi1 + 3000));
    tmp_u9 = va("^9Team:   ^7%s ^9(^7%s^9)\n",tmp_u9,tmp_u8);
    if (param_1 != 0) {
      tmp_u9 = va("print \"%s\"",tmp_u9,tmp_u8);
      tmp_i11 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
      trap_SendServerCommand(tmp_i11,tmp_u9);
      tmp_s10 = strlen(tmp_pc7);
      if (tmp_s10 != 0x20) goto LAB_000d48a9;
      tmp_u8 = va("^9NGUID:  ^g%s\n",tmp_pc7,tmp_u8);
      G_shrubbot_print(param_1,tmp_u8);
      tmp_u8 = va("^9IP:     ^g%s\n",*tmp_pi1 + 0x653);
LAB_000d4daf:
      tmp_i11 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
      goto LAB_000d48f5;
    }
    DecolorString(tmp_u9,local_41c);
    G_Printf(local_41c);
    tmp_s10 = strlen(tmp_pc7);
    if (tmp_s10 == 0x20) {
      tmp_u8 = va("^9NGUID:  ^g%s\n",tmp_pc7,tmp_u8);
      G_shrubbot_print(0,tmp_u8);
      tmp_i11 = *tmp_pi1;
    }
    else {
LAB_000d4bb0:
      DecolorString("^9NGUID:  ^1INVALID%s\n",local_41c);
      G_Printf(local_41c);
      tmp_i11 = *(int *)(g_entities + local_b1c[0] * 0x600 + 400);
    }
    tmp_u8 = va("^9IP:     ^g%s\n",tmp_i11 + 0x653);
LAB_000d4bf8:
    DecolorString(tmp_u8,local_41c);
    G_Printf(local_41c);
    tmp_u8 = va("^9MAC:    ^g%s\n",*(int *)(g_entities + local_b1c[0] * 0x600 + 400) + 0xaf4);
    DecolorString(tmp_u8,local_41c);
    G_Printf(local_41c);
  }
  tmp_pu2 = local_918 + 0x3f;
  trap_GetUserinfo(local_b58,tmp_pu2,0x400);
  tmp_u8 = Info_ValueForKey(tmp_pu2,"etVersion");
  Q_strncpyz(&local_a1c,tmp_u8,0x100);
  if ((char)local_a1c != '\0') {
    tmp_u8 = va("^9Client: ^g%s\n",&local_a1c);
    G_shrubbot_print(param_1,tmp_u8);
  }
  tmp_u8 = Info_ValueForKey(tmp_pu2,"build");
  Q_strncpyz(&local_91c,tmp_u8,0x100);
  if ((char)local_91c != '\0') {
    tmp_u8 = va("^9Mod build: ^g%s\n",&local_91c);
    G_shrubbot_print(param_1,tmp_u8);
  }
  if (tmp_i5 != 0) {
    tmp_u6 = va("^9Level:  ^g%i^7\n",tmp_u6);
    if (param_1 == 0) {
      DecolorString(tmp_u6,local_41c);
      G_Printf(local_41c);
      tmp_u6 = va("^9GText:  ^g%s\n",tmp_i5 + 0x450);
      DecolorString(tmp_u6,local_41c);
      G_Printf(local_41c);
      tmp_u6 = va("^9GAudio: ^g%s\n",tmp_i5 + 0x850);
      DecolorString(tmp_u6,local_41c);
      G_Printf(local_41c);
      if (*(char *)(tmp_i5 + 0x1078) != '\0') {
        va("^2Registered user\n^9Username: ^g%s\n",tmp_i5 + 0x1078);
        goto LAB_000d4d59;
      }
    }
    else {
      tmp_u6 = va("print \"%s\"",tmp_u6);
      tmp_i11 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
      trap_SendServerCommand(tmp_i11,tmp_u6);
      tmp_u6 = va("^9GText:  ^g%s\n",tmp_i5 + 0x450);
      tmp_u6 = va("print \"%s\"",tmp_u6);
      trap_SendServerCommand(tmp_i11,tmp_u6);
      tmp_u6 = va("^9GAudio: ^g%s\n",tmp_i5 + 0x850);
      tmp_u6 = va("print \"%s\"",tmp_u6);
      trap_SendServerCommand(tmp_i11,tmp_u6);
      if (*(char *)(tmp_i5 + 0x1078) != '\0') {
        tmp_u6 = va("^2Registered user\n^9Username: ^g%s\n",tmp_i5 + 0x1078);
        tmp_u6 = va("print \"%s\"",tmp_u6);
        trap_SendServerCommand(tmp_i11,tmp_u6);
      }
    }
    return 1;
  }
  if (param_1 != 0) {
    tmp_u6 = va("print \"%s\"","Admin information temporarly unavailable.\n");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
    return 1;
  }
LAB_000d4d59:
  G_shrubbot_print_part_8();
  return 1;
}

uint32_t G_shrubbot_leveledit(int param_1,int param_2)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  char *tmp_pc5;
  uint16_t *tmp_pu6;
  uint32_t *tmp_pu7;
  uint32_t tmp_u8;
  int tmp_i9;
  char tmp_c10;
  uint tmp_u11;
  uint tmp_u12;
  uint8_t **tmp_ppu13;
  int tmp_i14;
  bool tmp_b15;
  uint32_t *tmp_pu16;
  int local_450;
  char local_44c [12];
  uint8_t local_440 [16];
  char local_430 [20];
  uint32_t local_41c;
  
  if (param_1 == 0) {
    tmp_i1 = Q_SayArgc();
    if (tmp_i1 <= param_2 + 2) {
      tmp_pc5 = "^9usage: ^g!levedit [level] [grant|revoke|name|gtext|gsound] [args]^7\n";
      goto LAB_000d543e;
    }
    Q_SayArgv(param_2 + 1,local_44c,0xc);
    tmp_l2 = strtol(local_44c,(char **)0x0,10);
    Q_SayArgv(param_2 + 2,local_440,0x10);
    Q_SayArgv(param_2 + 3,local_430,0x14);
    if (Levels == (int *)0x0) {
      va("^1levedit error: ^9Unknown level : ^g%d^7\n",tmp_l2);
      goto LAB_000d5041;
    }
  }
  else {
    tmp_i1 = Nit_SecureShrubEnabled();
    if ((tmp_i1 != 0) && (*(int *)(*(int *)(param_1 + 400) + 0xf2c) == 0)) {
      Nit_SecureShrubError(param_1,"levedit");
      return 0;
    }
    tmp_i1 = Q_SayArgc();
    if (tmp_i1 <= param_2 + 2) {
      tmp_pc5 = "^9usage: ^g!levedit [level] [grant|revoke|name|gtext|gsound] [args]^7\n";
      goto LAB_000d5056;
    }
    Q_SayArgv(param_2 + 1,local_44c,0xc);
    tmp_l2 = strtol(local_44c,(char **)0x0,10);
    Q_SayArgv(param_2 + 2,local_440,0x10);
    Q_SayArgv(param_2 + 3,local_430,0x14);
    if (Levels == (int *)0x0) {
      tmp_pc5 = (char *)va("^1levedit error: ^9Unknown level : ^g%d^7\n",tmp_l2);
      goto LAB_000d5056;
    }
  }
  local_450 = param_2 + 3;
  tmp_i14 = 0;
  tmp_i1 = *Levels;
  while (tmp_i1 != tmp_l2) {
    tmp_i14 = tmp_i14 + 1;
    if ((&Levels)[tmp_i14] == (int *)0x0) {
      tmp_pc5 = (char *)va("^1levedit error: ^9Unknown level : ^g%d^7\n",tmp_l2);
      goto joined_r0x000d503f;
    }
    tmp_i1 = *(&Levels)[tmp_i14];
  }
  tmp_i1 = Q_stricmp(local_440,"grant");
  if (tmp_i1 == 0) {
    if (local_430[0] != '\0') {
      tmp_ppu13 = &g_ptr_s_time_002528fd_0x18_002b3ab4;
      tmp_pc5 = "readconfig";
      do {
        tmp_i1 = Q_stricmp(tmp_pc5,local_430);
        if (tmp_i1 == 0) goto LAB_000d50f7;
        tmp_pc5 = *tmp_ppu13;
        tmp_ppu13 = tmp_ppu13 + 5;
      } while (*tmp_pc5 != '\0');
      tmp_ppu13 = &AdminPermissions;
      do {
        tmp_i1 = Q_stricmp(*tmp_ppu13,local_430);
        if (tmp_i1 == 0) goto LAB_000d50f7;
        tmp_ppu13 = tmp_ppu13 + 3;
      } while (tmp_ppu13 != &spawns);
      tmp_pc5 = (char *)va("^1levedit error: ^9Unknown command/privilege : ^g\'%s\'\n",local_430);
joined_r0x000d503f:
      if (param_1 == 0) {
LAB_000d5041:
        G_shrubbot_print_part_8();
        return 0;
      }
LAB_000d5056:
      tmp_u3 = va("print \"%s\"",tmp_pc5);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
      return 0;
    }
  }
  else {
    tmp_i1 = Q_stricmp(local_440,"revoke");
    if (tmp_i1 != 0) {
      tmp_i1 = Q_stricmp(local_440,"name");
      if (tmp_i1 == 0) {
        tmp_pc5 = (char *)Q_SayConcatArgs(local_450);
        if (tmp_pc5 != (char *)0x0) {
          tmp_c10 = *tmp_pc5;
          tmp_i1 = 0;
          if (tmp_c10 != '\0') {
            do {
              *(char *)((int)(&Levels)[tmp_i14] + 4 + tmp_i1) = tmp_c10;
              tmp_i1 = tmp_i1 + 1;
              tmp_c10 = tmp_pc5[tmp_i1];
              if (tmp_c10 == '\0') break;
            } while (tmp_i1 != 0x23);
          }
          *(uint8_t *)((int)(&Levels)[tmp_i14] + 4 + tmp_i1) = 0;
          tmp_pu16 = (&Levels)[tmp_i14] + 1;
          tmp_u3 = *(&Levels)[tmp_i14];
          tmp_pc5 = "^xlevedit : ^gname ^9has been modified for level ^g%d ^9: \'^g%s^9\'^7\n";
          goto LAB_000d54de;
        }
        tmp_pc5 = (char *)va("^1levedit error: ^9No ^gname ^9specified^7\n");
      }
      else {
        tmp_i1 = Q_stricmp(local_440,&g_unk_00252693);
        if (tmp_i1 == 0) {
          tmp_pc5 = (char *)Q_SayConcatArgs(local_450);
          if (tmp_pc5 != (char *)0x0) {
            tmp_c10 = *tmp_pc5;
            tmp_i1 = 0;
            tmp_pu7 = (&Levels)[tmp_i14];
            if (tmp_c10 != '\0') {
              do {
                *(char *)((int)tmp_pu7 + tmp_i1 + 0x428) = tmp_c10;
                tmp_i1 = tmp_i1 + 1;
                tmp_c10 = tmp_pc5[tmp_i1];
                if (tmp_c10 == '\0') break;
              } while (tmp_i1 != 0x3ff);
            }
            *(uint8_t *)((int)tmp_pu7 + tmp_i1 + 0x428) = 0;
            tmp_pu16 = tmp_pu7 + 0x10a;
            tmp_u3 = *tmp_pu7;
            tmp_pc5 = "^xlevedit : ^ggreeting ^9has been modified for level ^g%d ^9: \'^g%s^9\'^7\n";
LAB_000d54de:
            tmp_u3 = va(tmp_pc5,tmp_u3,tmp_pu16);
            G_shrubbot_print(param_1,tmp_u3);
            nitrox_SaveDBFile_levels();
            return 1;
          }
          tmp_pc5 = (char *)va("^1levedit error: ^9No ^ggreeting ^9specified^7\n");
        }
        else {
          tmp_i1 = Q_stricmp(local_440,"gsound");
          if (tmp_i1 == 0) {
            Q_SayArgv(local_450,&local_41c,0x400);
            tmp_i1 = 0;
            tmp_pu7 = (&Levels)[tmp_i14];
            while ((char)local_41c != '\0') {
              *(char *)((int)tmp_pu7 + tmp_i1 + 0x828) = (char)local_41c;
              tmp_i1 = tmp_i1 + 1;
              GHIDRA_FIELD(local_41c, 0, 1) = *(char *)((int)&local_41c + tmp_i1);
            }
            *(uint8_t *)((int)tmp_pu7 + tmp_i1 + 0x828) = 0;
            tmp_pu16 = tmp_pu7 + 0x20a;
            tmp_u3 = *tmp_pu7;
            tmp_pc5 = 
            "^xlevedit : ^gGreeting sound ^9has been modified for level ^g%d ^9: \'^g%s^9\'^7\n";
            goto LAB_000d54de;
          }
          tmp_u3 = va("^1levedit error: ^9Unknown action^7\n");
          G_shrubbot_print(param_1,tmp_u3);
          tmp_pc5 = "^9usage: ^g!levedit [level] [grant|revoke|name|gtext|gsound] [args]^7\n";
        }
      }
      goto LAB_000d5306;
    }
    if (local_430[0] != '\0') {
      tmp_ppu13 = &g_ptr_s_time_002528fd_0x18_002b3ab4;
      tmp_pc5 = "readconfig";
      do {
        tmp_i1 = Q_stricmp(tmp_pc5,local_430);
        if (tmp_i1 == 0) goto LAB_000d51d7;
        tmp_pc5 = *tmp_ppu13;
        tmp_ppu13 = tmp_ppu13 + 5;
      } while (*tmp_pc5 != '\0');
      tmp_ppu13 = &AdminPermissions;
      do {
        tmp_i1 = Q_stricmp(*tmp_ppu13,local_430);
        if (tmp_i1 == 0) goto LAB_000d51d7;
        tmp_ppu13 = tmp_ppu13 + 3;
      } while (tmp_ppu13 != &spawns);
      tmp_pc5 = (char *)va("^1levedit error: ^9Unknown command/privilege : ^g\'%s\'\n",local_430);
      goto LAB_000d5306;
    }
  }
  tmp_pc5 = (char *)va("^1levedit error: ^9No command/privilege specified\n");
LAB_000d5306:
  G_shrubbot_print(param_1,tmp_pc5);
  return 0;
LAB_000d51d7:
  tmp_pc5 = (char *)va(&g_unk_0024e6e8,local_430);
  tmp_pu7 = (&Levels)[tmp_i14];
  tmp_pc5 = strstr((char *)(tmp_pu7 + 10),tmp_pc5);
  if (tmp_pc5 != (char *)0x0) {
    tmp_u3 = va(&g_unk_0024e6e8,local_430);
    Nit_RemoveWordInString((int)(&Levels)[tmp_i14] + 0x28,tmp_u3);
    tmp_u3 = va("^xlevedit: ^9Acces to ^g\'%s\' ^9successfully revoked to level ^g%d\n",local_430,
               *(&Levels)[tmp_i14]);
    G_shrubbot_print(param_1,tmp_u3);
    nitrox_SaveDBFile_levels();
    nitrox_SetLevelPermissions((&Levels)[tmp_i14]);
    tmp_i1 = (int)(&Levels)[tmp_i14];
    if (tmp_i1 != 0) {
      if (*(char *)(tmp_i1 + 0x28) != '\0') {
        local_41c = tmp_i1 + 0x28;
        tmp_u11 = 0x138;
        tmp_pu6 = (uint16_t *)(tmp_i1 + 0xc30);
        tmp_b15 = ((uint)tmp_pu6 & 1) != 0;
        if (tmp_b15) {
          tmp_u11 = 0x137;
          *(uint8_t *)(tmp_i1 + 0xc30) = 0;
          tmp_pu6 = (uint16_t *)(tmp_i1 + 0xc31);
        }
        if (((uint)tmp_pu6 & 2) != 0) {
          *tmp_pu6 = 0;
          tmp_u11 = tmp_u11 - 2;
          tmp_pu6 = tmp_pu6 + 1;
        }
        tmp_u12 = 0;
        do {
          *(uint32_t *)((int)tmp_pu6 + tmp_u12) = 0;
          *(uint32_t *)((int)tmp_pu6 + tmp_u12 + 4) = 0;
          tmp_u12 = tmp_u12 + 8;
        } while (tmp_u12 < (tmp_u11 & 0xfffffff8));
        tmp_pu7 = (uint32_t *)((int)tmp_pu6 + tmp_u12);
        if ((tmp_u11 & 4) != 0) {
          *tmp_pu7 = 0;
          tmp_pu7 = tmp_pu7 + 1;
        }
        if ((tmp_u11 & 2) != 0) {
          *(uint16_t *)tmp_pu7 = 0;
          tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
        }
        if (tmp_b15) {
          *(uint8_t *)tmp_pu7 = 0;
        }
        do {
          tmp_pc5 = (char *)COM_ParseExt(&local_41c,0);
          if (tmp_pc5 == (char *)0x0) {
            return 1;
          }
          if (*tmp_pc5 == '\0') {
            return 1;
          }
          tmp_ppu13 = &g_shrubbot_cmds;
          tmp_i14 = 0;
          do {
            tmp_i9 = Q_stricmp(*tmp_ppu13,tmp_pc5);
            if (tmp_i9 == 0) {
              *(uint32_t *)(tmp_i1 + 0xc30 + tmp_i14 * 4) = 1;
              break;
            }
            tmp_i14 = tmp_i14 + 1;
            tmp_ppu13 = tmp_ppu13 + 5;
          } while (tmp_i14 != 0x4e);
        } while( true );
      }
      tmp_pu6 = (uint16_t *)(tmp_i1 + 0xc30);
      tmp_u11 = 0x138;
      tmp_b15 = ((uint)tmp_pu6 & 1) != 0;
      if (tmp_b15) {
        tmp_u11 = 0x137;
        *(uint8_t *)(tmp_i1 + 0xc30) = 0;
        tmp_pu6 = (uint16_t *)(tmp_i1 + 0xc31);
      }
      if (((uint)tmp_pu6 & 2) != 0) {
        *tmp_pu6 = 0;
        tmp_u11 = tmp_u11 - 2;
        tmp_pu6 = tmp_pu6 + 1;
      }
      tmp_u12 = 0;
      do {
        *(uint32_t *)((int)tmp_pu6 + tmp_u12) = 0;
        *(uint32_t *)((int)tmp_pu6 + tmp_u12 + 4) = 0;
        tmp_u12 = tmp_u12 + 8;
      } while (tmp_u12 < (tmp_u11 & 0xfffffff8));
      tmp_pu7 = (uint32_t *)((int)tmp_pu6 + tmp_u12);
      if ((tmp_u11 & 4) != 0) {
        *tmp_pu7 = 0;
        tmp_pu7 = tmp_pu7 + 1;
      }
      if ((tmp_u11 & 2) != 0) {
        *(uint16_t *)tmp_pu7 = 0;
        tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
      }
      if (tmp_b15) {
        *(uint8_t *)tmp_pu7 = 0;
      }
    }
    return 1;
  }
  tmp_pc5 = (char *)va("^1levedit error: ^9Acces to ^g\'%s\' ^9already revoked to level ^g%d\n",
                      local_430,*tmp_pu7);
  goto LAB_000d5306;
LAB_000d50f7:
  tmp_pu7 = (&Levels)[tmp_i14];
  tmp_pc5 = (char *)(tmp_pu7 + 10);
  tmp_pc4 = strstr(tmp_pc5,local_430);
  if (tmp_pc4 == (char *)0x0) {
    Q_strcat(tmp_pc5,0x400,&g_unk_002612df);
    Q_strcat((int)(&Levels)[tmp_i14] + 0x28,0x400,local_430);
    tmp_u3 = *(&Levels)[tmp_i14];
    tmp_u8 = va("^xlevedit: ^9Acces to ^g\'%s\' ^9successfully granted to level ^g%d\n",local_430,
               tmp_u3);
    if (param_1 == 0) {
      G_shrubbot_print_part_8();
    }
    else {
      tmp_u3 = va("print \"%s\"",tmp_u8,tmp_u3);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
    }
    nitrox_SaveDBFile_levels();
    nitrox_SetLevelPermissions((&Levels)[tmp_i14]);
    nitrox_SetLevelCommandPermissions((&Levels)[tmp_i14]);
    return 1;
  }
  tmp_pc5 = (char *)va("^1levedit error: ^9Acces to ^g\'%s\' ^9already granted to level ^g%d\n",
                      local_430,*tmp_pu7);
  if (param_1 == 0) {
LAB_000d543e:
    DecolorString(tmp_pc5,&local_41c);
    G_Printf(&local_41c);
    return 0;
  }
  goto LAB_000d5056;
}

int G_shrubbot_banguid(int param_1,int param_2)
{
  time_t tVar1;
  int tmp_i2;
  int tmp_i3;
  size_t tmp_s4;
  long tmp_l5;
  uint32_t tmp_u6;
  int tmp_i7;
  char *tmp_pc8;
  tm *__tp;
  int tmp_i9;
  char tmp_c10;
  int *tmp_pi11;
  time_t *__timer;
  char *tmp_pc12;
  char *local_488;
  tm *local_480;
  int local_470;
  char acStack_46c [8];
  uint8_t local_464 [36];
  char local_440 [1068];
  uint32_t uStack_14;
  
  uStack_14 = 0xd5909;
  __timer = &local_470;
  tVar1 = time(__timer);
  if (tVar1 == 0) {
    return 0;
  }
  tmp_i2 = nitrox_CheckPermission(param_1,7);
  if ((tmp_i2 == 0) || (tmp_i2 = nitrox_CheckPermission(param_1,5), tmp_i2 == 0)) {
    tmp_i2 = nitrox_CheckPermission(param_1,7);
    if ((tmp_i2 == 0) && (tmp_i2 = nitrox_CheckPermission(param_1,5), tmp_i2 == 0)) {
      tmp_i2 = param_2 + 4;
    }
    else {
      tmp_i2 = param_2 + 3;
    }
  }
  else {
    tmp_i2 = param_2 + 2;
  }
  tmp_i3 = Q_SayArgc();
  if (tmp_i3 < tmp_i2) {
    if (param_1 == 0) {
      tmp_pc8 = "^9usage: ^g!banguid [guid] [seconds] [reason]\n";
LAB_000d5d81:
      DecolorString(tmp_pc8,local_440 + 0x24);
      G_Printf(local_440 + 0x24);
      return 0;
    }
    tmp_pc8 = "^9usage: ^g!banguid [guid] [seconds] [reason]\n";
LAB_000d5afe:
    tmp_u6 = va("print \"%s\"",tmp_pc8);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
    return 0;
  }
  tmp_pc8 = acStack_46c + 1;
  Q_SayArgv(param_2 + 1,local_464,0x24);
  Q_SayArgv(param_2 + 2,tmp_pc8,7);
  local_488 = (char *)0x1;
  if (acStack_46c[1] != '\0') {
    tmp_s4 = strlen(tmp_pc8);
    tmp_c10 = acStack_46c[tmp_s4];
    if (9 < (byte)(tmp_c10 - 0x30U)) {
      if (tmp_c10 == 'w') {
        local_488 = (char *)0x93a80;
      }
      else if (tmp_c10 == 'd') {
        local_488 = (char *)0x15180;
      }
      else if (tmp_c10 == 'h') {
        local_488 = (char *)0xe10;
      }
      else {
        local_488 = (char *)0x3c;
        if (tmp_c10 != 'm') {
          local_488 = (char *)1;
        }
      }
      acStack_46c[tmp_s4] = '\0';
    }
  }
  tmp_l5 = strtol(tmp_pc8,(char **)0x0,10);
  if (tmp_l5 < 1) {
    tmp_i2 = nitrox_CheckPermission(param_1,7);
    if (tmp_i2 == 0) {
      if (param_1 == 0) {
        G_shrubbot_print_part_8();
        return tmp_i2;
      }
      tmp_u6 = va("print \"%s\"","^1banguid error: ^9seconds must be a positive integer\n");
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
      return tmp_i2;
    }
    local_488 = (char *)Q_SayConcatArgs(param_2 + 2);
    local_480 = (tm *)0x0;
  }
  else {
    local_480 = (tm *)(tmp_l5 * (int)local_488);
    local_488 = (char *)Q_SayConcatArgs(param_2 + 3);
  }
  if (Users != 0) {
    tmp_i3 = 0;
    tmp_i2 = Users;
    do {
      tmp_i2 = Q_stricmp(local_464,tmp_i2 + 0x1c);
      if (tmp_i2 == 0) {
        if (Bans != 0) goto LAB_000d5ab9;
        goto LAB_000d5c1d;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_i2 = (&Users)[tmp_i3];
    } while (tmp_i2 != 0);
  }
  tmp_i3 = -1;
  if (Bans != 0) {
LAB_000d5ab9:
    tmp_i2 = Bans;
    tmp_pi11 = &g_unk_02df1044;
    do {
      tmp_i2 = Q_stricmp(local_464,tmp_i2 + 0x3c);
      if (tmp_i2 == 0) {
        if (param_1 != 0) {
          tmp_pc8 = "^1banguid error: ^9Player already banned.\n";
          goto LAB_000d5afe;
        }
        tmp_pc8 = "^1banguid error: ^9Player already banned.\n";
        goto LAB_000d5d81;
      }
      tmp_i2 = *tmp_pi11;
      tmp_pi11 = tmp_pi11 + 1;
    } while (tmp_i2 != 0);
    if (tmp_i3 != -1) {
LAB_000d5c1d:
      if (param_1 == 0) {
        tmp_i2 = Q_stricmp((&Users)[tmp_i3] + 0xc62,"localhost");
        if ((tmp_i2 == 0) || (tmp_i2 = Q_stricmp((&Users)[tmp_i3] + 0xc62,"127.0.0.1"), tmp_i2 == 0)) {
          va("^1banguid error: ^9Cannot ban local players (IP: %s).\n",(&Users)[tmp_i3] + 0xc62);
          G_shrubbot_print_part_8();
          return 0;
        }
      }
      else {
        if (*(int *)(param_1 + 400) == 0) {
          tmp_i2 = (&Users)[tmp_i3];
        }
        else {
          tmp_i7 = nitrox_GetAdminLevel(param_1,0);
          tmp_i2 = (&Users)[tmp_i3];
          if (tmp_i7 < **(int **)(tmp_i2 + 0x4c)) {
            tmp_pc8 = "^1banguid error: ^9Specified player has a higher admin level than you do.\n";
            goto LAB_000d5bf9;
          }
        }
        tmp_i2 = Q_stricmp(tmp_i2 + 0xc62,"localhost");
        if ((tmp_i2 == 0) || (tmp_i2 = Q_stricmp((&Users)[tmp_i3] + 0xc62,"127.0.0.1"), tmp_i2 == 0)) {
          tmp_pc8 = (char *)va("^1banguid error: ^9Cannot ban local players (IP: %s).\n",
                              (&Users)[tmp_i3] + 0xc62);
          goto LAB_000d5afe;
        }
      }
      tmp_i2 = AllocBan(1);
      if (tmp_i2 == 0) {
        return 0;
      }
      Q_strncpyz(tmp_i2,(&Users)[tmp_i3] + 0x25,0x24);
      Q_strncpyz(tmp_i2 + 0x24,(&Users)[tmp_i3] + 4,0x21);
      Q_strncpyz(tmp_i2 + 0x4b4,(&Users)[tmp_i3] + 0xc50,0x12);
      tmp_i3 = (&Users)[tmp_i3];
      tmp_c10 = *(char *)(tmp_i3 + 0xc62);
      if ((tmp_c10 == '\0') || (tmp_i7 = 0, tmp_c10 == ':')) {
        tmp_i9 = 0;
      }
      else {
        do {
          tmp_i9 = tmp_i7 + 1;
          local_440[tmp_i7] = tmp_c10;
          tmp_c10 = *(char *)(tmp_i3 + 0xc62 + tmp_i9);
          if ((tmp_c10 == '\0') || (tmp_i9 == 0x24)) break;
          tmp_i7 = tmp_i9;
        } while (tmp_c10 != ':');
      }
      local_440[tmp_i9] = '\0';
      Q_strncpyz(tmp_i2 + 0x45,local_440,0x12);
      __tp = localtime(__timer);
      strftime((char *)(tmp_i2 + 0x457),0x32,"%m/%d/%y %H:%M:%S",__tp);
      if (param_1 == 0) {
        tmp_pc8 = "console";
      }
      else {
        __timer = *(time_t **)(param_1 + 400);
        tmp_pc8 = (char *)(__timer + 0x17e);
      }
      Q_strncpyz(tmp_i2 + 0x490,tmp_pc8,0x24,__tp,__timer);
      tmp_i3 = 0;
      if (local_480 != (tm *)0x0) {
        tmp_i3 = (int)local_480 + local_470 + -0x386a4c20;
      }
      *(int *)(tmp_i2 + 0x48c) = tmp_i3;
      tmp_pc8 = local_488;
      if (*local_488 == '\0') {
        tmp_pc8 = "banned by admin";
      }
      tmp_i7 = 0;
      Q_strncpyz(tmp_i2 + 0x57,tmp_pc8,0x400,__tp,__timer);
      tmp_i3 = Bans;
      while (tmp_i3 != 0) {
        tmp_i7 = tmp_i7 + 1;
        tmp_i3 = (&Bans)[tmp_i7];
      }
      nitrox_SaveSingleBan(tmp_i2,1);
      (&Bans)[tmp_i7] = tmp_i2;
      tmp_u6 = va("banguid: %s^7 is now banned\n",tmp_i2);
      G_shrubbot_print(param_1,tmp_u6);
      if (local_480 == (tm *)0x0) {
        tmp_pc8 = (char *)0x400;
        Q_strncpyz(local_440 + 0x24,"PERMANENTLY",0x400);
      }
      else {
        tmp_pc8 = "for %i seconds";
        Com_sprintf(local_440 + 0x24,0x400,"for %i seconds",local_480);
        __tp = local_480;
      }
      local_480 = (tm *)(local_440 + 0x24);
      if (0 < g_unk_00abe938) {
        tmp_pc12 = "You have been banned %s, Reason: %s";
        tmp_i3 = 0;
        do {
          tmp_i9 = (&g_unk_00abe944)[tmp_i3] * 0x54dc + level;
          tmp_i7 = Q_stricmp(tmp_i2 + 0x24,tmp_i9 + 0x61c,tmp_pc8,__tp,tmp_pc12);
          if (tmp_i7 == 0) {
            tmp_pc8 = local_488;
            if (*local_488 == '\0') {
              tmp_pc8 = "banned by admin";
            }
            tmp_u6 = va(tmp_pc12,local_480,tmp_pc8);
            tmp_pc8 = (char *)0x0;
            trap_DropClient(*(uint32_t *)(tmp_i9 + 0xa0),tmp_u6);
          }
          tmp_i3 = tmp_i3 + 1;
        } while (tmp_i3 < g_unk_00abe938);
      }
      return 1;
    }
  }
  tmp_pc8 = "^1banguid error: ^9Player not found.\n";
LAB_000d5bf9:
  G_shrubbot_print(param_1,tmp_pc8);
  return 0;
}

uint32_t G_shrubbot_useredit(int param_1,int param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  uint16_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint32_t tmp_u5;
  int tmp_i6;
  long tmp_l7;
  uint tmp_u8;
  uint tmp_u9;
  int tmp_i10;
  uint8_t **tmp_ppu11;
  int tmp_i12;
  bool tmp_b13;
  char *local_470;
  uint8_t *local_46c;
  int local_450;
  char local_449 [9];
  uint8_t local_440 [16];
  char local_430 [20];
  int local_41c [259];
  
  if (param_1 != 0) {
    tmp_i1 = Nit_SecureShrubEnabled();
    if ((tmp_i1 != 0) && (*(int *)(*(int *)(param_1 + 400) + 0xf2c) == 0)) {
      Nit_SecureShrubError(param_1,"useredit");
      return 0;
    }
    tmp_i1 = Q_SayArgc();
    if (param_2 + 2 < tmp_i1) {
      Q_SayArgv(param_2 + 1,local_449,9);
      strtol(local_449,(char **)0x0,10);
      Q_SayArgv(param_2 + 2,local_440,0x10);
      Q_SayArgv(param_2 + 3,local_430,0x14);
      if (Users != 0) goto LAB_000d626d;
      tmp_pc2 = (char *)va("^1useredit error: ^9Unknown UserID : ^g%s^7\n",local_449);
    }
    else {
      tmp_pc2 = "^9usage: ^g!useredit [UserID] [grant|revoke|level|gtext|gsound] [args]^7\n";
    }
    goto LAB_000d648e;
  }
  tmp_i1 = Q_SayArgc();
  if (tmp_i1 <= param_2 + 2) {
    DecolorString("^9usage: ^g!useredit [UserID] [grant|revoke|level|gtext|gsound] [args]^7\n",
                  local_41c);
    G_Printf(local_41c);
    return 0;
  }
  Q_SayArgv(param_2 + 1,local_449,9);
  strtol(local_449,(char **)0x0,10);
  Q_SayArgv(param_2 + 2,local_440,0x10);
  Q_SayArgv(param_2 + 3,local_430,0x14);
  if (Users != 0) {
LAB_000d626d:
    local_46c = local_440;
    local_470 = local_430;
    param_2 = param_2 + 3;
    tmp_i12 = 0;
    tmp_i1 = Users;
    while (tmp_i1 = Q_stricmp(local_449,tmp_i1 + 0x1c), tmp_i1 != 0) {
      tmp_i12 = tmp_i12 + 1;
      tmp_i1 = (&Users)[tmp_i12];
      if (tmp_i1 == 0) goto LAB_000d64d8;
    }
    tmp_i1 = Q_stricmp(local_46c,"grant");
    if (tmp_i1 == 0) {
      if (local_430[0] != '\0') {
        tmp_ppu11 = &g_ptr_s_time_002528fd_0x18_002b3ab4;
        tmp_pc2 = "readconfig";
        goto LAB_000d62ee;
      }
    }
    else {
      tmp_i1 = Q_stricmp(local_46c,"revoke");
      if (tmp_i1 != 0) {
        tmp_i1 = Q_stricmp(local_46c,&g_unk_00252693);
        if (tmp_i1 != 0) {
          tmp_i1 = Q_stricmp(local_46c,"gsound");
          if (tmp_i1 == 0) {
            Q_SayArgv(param_2,local_41c,0x400);
            Q_strncpyz((&Users)[tmp_i12] + 0x850,local_41c,0x400);
            nitrox_SaveSingleUser((&Users)[tmp_i12],2);
            nitrox_SetAdminPermissions((&Users)[tmp_i12]);
            nitrox_SetAdminCommandPermissions((&Users)[tmp_i12]);
            tmp_i1 = (&Users)[tmp_i12] + 0x850;
            local_470 = (char *)((&Users)[tmp_i12] + 0x25);
            tmp_pc2 = 
            "^xuseredit : ^gGreeting sound ^9has been modified for user ^7%s ^9: \'^g%s^9\'^7\n";
            goto LAB_000d6457;
          }
          tmp_i1 = Q_stricmp(local_46c,"level");
          if (tmp_i1 != 0) {
            tmp_u5 = va("^1useredit error: ^9Unknown action^7\n");
            G_shrubbot_print(param_1,tmp_u5);
            tmp_pc2 = "^9usage: ^g!useredit [UserID] [grant|revoke|level|gtext|gsound] [args]^7\n";
            goto LAB_000d661d;
          }
          tmp_i1 = Q_SayArgv(param_2,local_41c,0xc);
          if (tmp_i1 == 0) {
            tmp_pc2 = "^1useredit error: ^9no level specified\n";
          }
          else {
            tmp_l7 = strtol((char *)local_41c,(char **)0x0,10);
            tmp_i1 = nitrox_LevelExists(tmp_l7);
            if (tmp_i1 != 0) {
              tmp_i1 = (&Users)[tmp_i12];
              tmp_u5 = nitrox_LevelPointer(tmp_l7);
              *(uint32_t *)(tmp_i1 + 0x4c) = tmp_u5;
              nitrox_SaveSingleUser((&Users)[tmp_i12],2);
              nitrox_SetAdminPermissions((&Users)[tmp_i12]);
              nitrox_SetAdminCommandPermissions((&Users)[tmp_i12]);
              local_470 = (char *)((&Users)[tmp_i12] + 0x25);
              tmp_i1 = **(int **)((&Users)[tmp_i12] + 0x4c);
              tmp_pc2 = "^xuseredit : ^7%s^9\'s level set to ^g%d^9^7\n";
              goto LAB_000d6457;
            }
            tmp_pc2 = "^1useredit error: ^9unknown level\n";
          }
          G_shrubbot_print(param_1,tmp_pc2);
          return 0;
        }
        tmp_i1 = Q_SayConcatArgs(param_2);
        if (tmp_i1 == 0) {
          tmp_pc2 = (char *)va("^1useredit error: ^9No ^ggreeting ^9specified^7\n");
          goto LAB_000d661d;
        }
        Q_strncpyz((&Users)[tmp_i12] + 0x450,tmp_i1,0x400);
        nitrox_SaveSingleUser((&Users)[tmp_i12],2);
        nitrox_SetAdminPermissions((&Users)[tmp_i12]);
        local_470 = (char *)(&Users)[tmp_i12];
        if (local_470 == (char *)0x0) goto LAB_000d6973;
        if (*(char *)((int)local_470 + 0x50) == '\0') {
          tmp_pu3 = (uint16_t *)((int)local_470 + 0x10e8);
          tmp_u8 = 0x138;
          tmp_b13 = ((uint)tmp_pu3 & 1) != 0;
          if (tmp_b13) {
            tmp_u8 = 0x137;
            *(uint8_t *)((int)local_470 + 0x10e8) = 0;
            tmp_pu3 = (uint16_t *)((int)local_470 + 0x10e9);
          }
          if (((uint)tmp_pu3 & 2) != 0) {
            *tmp_pu3 = 0;
            tmp_u8 = tmp_u8 - 2;
            tmp_pu3 = tmp_pu3 + 1;
          }
          tmp_u9 = 0;
          do {
            *(uint32_t *)((int)tmp_pu3 + tmp_u9) = 0;
            *(uint32_t *)((int)tmp_pu3 + tmp_u9 + 4) = 0;
            tmp_u9 = tmp_u9 + 8;
          } while (tmp_u9 < (tmp_u8 & 0xfffffff8));
          tmp_pu4 = (uint32_t *)((int)tmp_pu3 + tmp_u9);
          if ((tmp_u8 & 4) != 0) {
            *tmp_pu4 = 0;
            tmp_pu4 = tmp_pu4 + 1;
          }
          if ((tmp_u8 & 2) != 0) {
            *(uint16_t *)tmp_pu4 = 0;
            tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
          }
          if (tmp_b13) {
            *(uint8_t *)tmp_pu4 = 0;
          }
LAB_000d6968:
          local_470 = (char *)(&Users)[tmp_i12];
LAB_000d6973:
          tmp_i1 = (int)local_470 + 0x450;
          local_470 = (char *)((int)local_470 + 0x25);
          tmp_pc2 = 
          "^xuseredit : ^gGreeting text ^9has been modified for user ^7%s ^9: \'^g%s^9\'^7\n";
          goto LAB_000d6457;
        }
        tmp_u8 = 0x138;
        local_41c[0] = (int)local_470 + 0x50;
        tmp_pu3 = (uint16_t *)((int)local_470 + 0x10e8);
        tmp_b13 = ((uint)tmp_pu3 & 1) != 0;
        if (tmp_b13) {
          tmp_u8 = 0x137;
          *(uint8_t *)((int)local_470 + 0x10e8) = 0;
          tmp_pu3 = (uint16_t *)((int)local_470 + 0x10e9);
        }
        if (((uint)tmp_pu3 & 2) != 0) {
          *tmp_pu3 = 0;
          tmp_u8 = tmp_u8 - 2;
          tmp_pu3 = tmp_pu3 + 1;
        }
        tmp_u9 = 0;
        do {
          *(uint32_t *)((int)tmp_pu3 + tmp_u9) = 0;
          *(uint32_t *)((int)tmp_pu3 + tmp_u9 + 4) = 0;
          tmp_u9 = tmp_u9 + 8;
        } while (tmp_u9 < (tmp_u8 & 0xfffffff8));
        tmp_pu4 = (uint32_t *)((int)tmp_pu3 + tmp_u9);
        if ((tmp_u8 & 4) != 0) {
          *tmp_pu4 = 0;
          tmp_pu4 = tmp_pu4 + 1;
        }
        if ((tmp_u8 & 2) != 0) {
          *(uint16_t *)tmp_pu4 = 0;
          tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
        }
        if (tmp_b13) {
          *(uint8_t *)tmp_pu4 = 0;
        }
        do {
          tmp_pc2 = (char *)COM_ParseExt(local_41c,0);
          if ((tmp_pc2 == (char *)0x0) || (*tmp_pc2 == '\0')) goto LAB_000d6968;
          tmp_ppu11 = &g_shrubbot_cmds;
          tmp_i1 = 0;
          do {
            tmp_i10 = Q_stricmp(*tmp_ppu11,tmp_pc2);
            if (tmp_i10 == 0) {
              *(uint32_t *)((int)local_470 + 0x10e8 + tmp_i1 * 4) = 1;
              break;
            }
            tmp_i1 = tmp_i1 + 1;
            tmp_ppu11 = tmp_ppu11 + 5;
          } while (tmp_i1 != 0x4e);
        } while( true );
      }
      if (local_430[0] != '\0') {
        tmp_ppu11 = &g_ptr_s_time_002528fd_0x18_002b3ab4;
        tmp_pc2 = "readconfig";
        goto LAB_000d656e;
      }
    }
    tmp_pc2 = (char *)va("^1useredit error: ^9No command/privilege specified\n");
    goto LAB_000d661d;
  }
  va("^1useredit error: ^9Unknown UserID : ^g%s^7\n",local_449);
  goto LAB_000d64f5;
LAB_000d64d8:
  tmp_pc2 = (char *)va("^1useredit error: ^9Unknown UserID : ^g%s^7\n",local_449);
  goto joined_r0x000d64f3;
  while( true ) {
    tmp_pc2 = *tmp_ppu11;
    tmp_ppu11 = tmp_ppu11 + 5;
    if (*tmp_pc2 == '\0') break;
LAB_000d656e:
    tmp_i1 = Q_stricmp(tmp_pc2,local_470);
    if (tmp_i1 == 0) goto LAB_000d657e;
  }
  tmp_ppu11 = &AdminPermissions;
  do {
    tmp_i1 = Q_stricmp(*tmp_ppu11,local_470);
    if (tmp_i1 == 0) goto LAB_000d657e;
    tmp_ppu11 = tmp_ppu11 + 3;
  } while (tmp_ppu11 != &spawns);
  goto LAB_000d6719;
LAB_000d62fe:
  local_450 = (&Users)[tmp_i12] + 0x50;
  tmp_i1 = nitrox_GetTokenForString(local_470);
  while ((tmp_pc2 = (char *)COM_ParseExt(&local_450,0), tmp_pc2 != (char *)0x0 && (*tmp_pc2 != '\0')))
  {
    tmp_i10 = nitrox_GetTokenForString(tmp_pc2);
    if (tmp_i1 == tmp_i10) goto LAB_000d6762;
  }
  Q_strcat((&Users)[tmp_i12] + 0x50,0x400,&g_unk_002612df);
  Q_strcat((&Users)[tmp_i12] + 0x50,0x400,local_470);
  nitrox_SaveSingleUser((&Users)[tmp_i12],2);
  nitrox_SetAdminPermissions((&Users)[tmp_i12]);
  tmp_i1 = (&Users)[tmp_i12];
  if (tmp_i1 == 0) {
    tmp_i1 = 0;
    goto LAB_000d6442;
  }
  if (*(char *)(tmp_i1 + 0x50) == '\0') {
    tmp_pu3 = (uint16_t *)(tmp_i1 + 0x10e8);
    tmp_u8 = 0x138;
    tmp_b13 = ((uint)tmp_pu3 & 1) != 0;
    if (tmp_b13) {
      tmp_u8 = 0x137;
      *(uint8_t *)(tmp_i1 + 0x10e8) = 0;
      tmp_pu3 = (uint16_t *)(tmp_i1 + 0x10e9);
    }
    if (((uint)tmp_pu3 & 2) != 0) {
      *tmp_pu3 = 0;
      tmp_u8 = tmp_u8 - 2;
      tmp_pu3 = tmp_pu3 + 1;
    }
    tmp_u9 = 0;
    do {
      *(uint32_t *)((int)tmp_pu3 + tmp_u9) = 0;
      *(uint32_t *)((int)tmp_pu3 + tmp_u9 + 4) = 0;
      tmp_u9 = tmp_u9 + 8;
    } while (tmp_u9 < (tmp_u8 & 0xfffffff8));
    tmp_pu4 = (uint32_t *)((int)tmp_pu3 + tmp_u9);
    if ((tmp_u8 & 4) != 0) {
      *tmp_pu4 = 0;
      tmp_pu4 = tmp_pu4 + 1;
    }
    if ((tmp_u8 & 2) != 0) {
      *(uint16_t *)tmp_pu4 = 0;
      tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
    }
    if (tmp_b13) {
      *(uint8_t *)tmp_pu4 = 0;
    }
LAB_000d6435:
    tmp_i1 = (&Users)[tmp_i12];
LAB_000d6442:
    tmp_i1 = tmp_i1 + 0x25;
    tmp_pc2 = "^xuseredit: ^9Acces to ^g\'%s\' ^9successfully granted to user ^7\'%s\'\n";
LAB_000d6457:
    tmp_u5 = va(tmp_pc2,local_470,tmp_i1);
    G_shrubbot_print(param_1,tmp_u5);
    return 1;
  }
  local_41c[0] = tmp_i1 + 0x50;
  tmp_u8 = 0x138;
  tmp_pu3 = (uint16_t *)(tmp_i1 + 0x10e8);
  tmp_b13 = ((uint)tmp_pu3 & 1) != 0;
  if (tmp_b13) {
    tmp_u8 = 0x137;
    *(uint8_t *)(tmp_i1 + 0x10e8) = 0;
    tmp_pu3 = (uint16_t *)(tmp_i1 + 0x10e9);
  }
  if (((uint)tmp_pu3 & 2) != 0) {
    *tmp_pu3 = 0;
    tmp_u8 = tmp_u8 - 2;
    tmp_pu3 = tmp_pu3 + 1;
  }
  tmp_u9 = 0;
  do {
    *(uint32_t *)((int)tmp_pu3 + tmp_u9) = 0;
    *(uint32_t *)((int)tmp_pu3 + tmp_u9 + 4) = 0;
    tmp_u9 = tmp_u9 + 8;
  } while (tmp_u9 < (tmp_u8 & 0xfffffff8));
  tmp_pu4 = (uint32_t *)((int)tmp_pu3 + tmp_u9);
  if ((tmp_u8 & 4) != 0) {
    *tmp_pu4 = 0;
    tmp_pu4 = tmp_pu4 + 1;
  }
  if ((tmp_u8 & 2) != 0) {
    *(uint16_t *)tmp_pu4 = 0;
    tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
  }
  if (tmp_b13) {
    *(uint8_t *)tmp_pu4 = 0;
  }
  do {
    tmp_pc2 = (char *)COM_ParseExt(local_41c,0);
    if ((tmp_pc2 == (char *)0x0) || (*tmp_pc2 == '\0')) goto LAB_000d6435;
    tmp_ppu11 = &g_shrubbot_cmds;
    tmp_i10 = 0;
    do {
      tmp_i6 = Q_stricmp(*tmp_ppu11,tmp_pc2);
      if (tmp_i6 == 0) {
        *(uint32_t *)(tmp_i1 + 0x10e8 + tmp_i10 * 4) = 1;
        break;
      }
      tmp_i10 = tmp_i10 + 1;
      tmp_ppu11 = tmp_ppu11 + 5;
    } while (tmp_i10 != 0x4e);
  } while( true );
LAB_000d6762:
  tmp_pc2 = (char *)va("^1useredit error: ^9Acces to ^g\'%s\' ^9already granted to user ^7\'%s\'\n",
                      local_470,(&Users)[tmp_i12] + 0x25);
  goto LAB_000d661d;
LAB_000d657e:
  local_450 = (&Users)[tmp_i12] + 0x50;
  tmp_i1 = nitrox_GetTokenForString(local_470);
  while ((tmp_pc2 = (char *)COM_ParseExt(&local_450,0), tmp_pc2 != (char *)0x0 && (*tmp_pc2 != '\0')))
  {
    tmp_i10 = nitrox_GetTokenForString(tmp_pc2);
    if (tmp_i1 == tmp_i10) {
      tmp_u5 = va(&g_unk_0024e6e8,local_470);
      Nit_RemoveWordInString((&Users)[tmp_i12] + 0x50,tmp_u5);
      nitrox_SaveSingleUser((&Users)[tmp_i12],2);
      nitrox_SetAdminPermissions((&Users)[tmp_i12]);
      nitrox_SetAdminCommandPermissions((&Users)[tmp_i12]);
      tmp_i1 = (&Users)[tmp_i12] + 0x25;
      tmp_u5 = va("^xuseredit: ^9Acces to ^g\'%s\' ^9successfully revoked to user ^7\'%s\'\n",
                 local_470,tmp_i1);
      if (param_1 == 0) {
        G_shrubbot_print_part_8();
        return 1;
      }
      tmp_u5 = va("print \"%s\"",tmp_u5,tmp_i1);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
      return 1;
    }
  }
  tmp_pc2 = (char *)va("^1useredit error: ^9Acces to ^g\'%s\' ^9already revoked to user ^7\'%s\'\n",
                      local_470,(&Users)[tmp_i12] + 0x25);
joined_r0x000d64f3:
  if (param_1 != 0) {
LAB_000d648e:
    tmp_u5 = va("print \"%s\"",tmp_pc2);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
    return 0;
  }
LAB_000d64f5:
  G_shrubbot_print_part_8();
  return 0;
  while( true ) {
    tmp_pc2 = *tmp_ppu11;
    tmp_ppu11 = tmp_ppu11 + 5;
    if (*tmp_pc2 == '\0') break;
LAB_000d62ee:
    tmp_i1 = Q_stricmp(tmp_pc2,local_470);
    if (tmp_i1 == 0) goto LAB_000d62fe;
  }
  tmp_ppu11 = &AdminPermissions;
  do {
    tmp_i1 = Q_stricmp(*tmp_ppu11,local_470);
    if (tmp_i1 == 0) goto LAB_000d62fe;
    tmp_ppu11 = tmp_ppu11 + 3;
  } while (tmp_ppu11 != &spawns);
LAB_000d6719:
  tmp_pc2 = (char *)va("^1useredit error: ^9Unknown command/privilege : ^g\'%s\'\n",local_470);
LAB_000d661d:
  G_shrubbot_print(param_1,tmp_pc2);
  return 0;
}

uint32_t G_shrubbot_seen(int param_1,int param_2)
{
  bool tmp_b1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int local_88c;
  int *local_888;
  int local_878;
  uint8_t local_864 [36];
  char local_840 [36];
  uint8_t local_81c [1024];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xd6e49;
  tmp_i2 = Q_SayArgc();
  if (tmp_i2 <= param_2 + 1) {
    G_shrubbot_print(param_1,"^9usage: ^g!seen [name]^7\n");
    return 0;
  }
  Q_SayArgv(param_2 + 1,local_864,0x24);
  if (Users != 0) {
    local_878 = 0;
    tmp_i7 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
    local_888 = &Users;
    tmp_i2 = Users;
    do {
      while( true ) {
        SanitizeString(tmp_i2 + 0x25,local_840,1);
        tmp_pc3 = (char *)Q_strlwr(local_864);
        tmp_pc3 = strstr(local_840,tmp_pc3);
        if ((tmp_pc3 != (char *)0x0) && (local_878 = local_878 + 1, local_878 < 0x10)) break;
LAB_000d7019:
        tmp_i2 = local_888[1];
joined_r0x000d723b:
        local_888 = local_888 + 1;
        if (tmp_i2 == 0) goto LAB_000d702c;
      }
      local_88c = g_unk_00abe938;
      if (0 < g_unk_00abe938) {
        tmp_i2 = 0;
        tmp_b1 = false;
        if (param_1 == 0) {
          do {
            tmp_i6 = *local_888;
            tmp_i5 = strcmp((char *)(*(int *)(g_entities + (&g_unk_00abe944)[tmp_i2] * 0x600 + 400) +
                                   0xeec),(char *)(tmp_i6 + 4));
            if (tmp_i5 == 0) {
              tmp_u4 = va("^xSeen : ^w%s ^g(%s) is online.\n",tmp_i6 + 0x25,tmp_i6 + 0x1c);
              DecolorString(tmp_u4,local_41c);
              G_Printf(local_41c);
              local_88c = g_unk_00abe938;
              tmp_b1 = true;
            }
            tmp_i2 = tmp_i2 + 1;
          } while (tmp_i2 < local_88c);
        }
        else {
          do {
            while( true ) {
              tmp_i6 = *local_888;
              tmp_i5 = strcmp((char *)(*(int *)(g_entities + (&g_unk_00abe944)[tmp_i2] * 0x600 + 400) +
                                     0xeec),(char *)(tmp_i6 + 4));
              if (tmp_i5 != 0) break;
              tmp_i2 = tmp_i2 + 1;
              tmp_u4 = va("^xSeen : ^w%s ^g(%s) is online.\n",tmp_i6 + 0x25,tmp_i6 + 0x1c);
              tmp_u4 = va("print \"%s\"",tmp_u4);
              trap_SendServerCommand(tmp_i7,tmp_u4);
              local_88c = g_unk_00abe938;
              tmp_b1 = true;
              if (g_unk_00abe938 <= tmp_i2) goto LAB_000d700d;
            }
            tmp_i2 = tmp_i2 + 1;
          } while (tmp_i2 < local_88c);
        }
LAB_000d700d:
        if (tmp_b1) goto LAB_000d7019;
      }
      tmp_i6 = G_GetCurrentTime();
      tmp_i2 = *local_888;
      if (*(int *)(tmp_i2 + 0xc74) == 0) {
        tmp_i6 = tmp_i2 + 0x1c;
        tmp_u4 = va("^xSeen: ^w%s ^g(%s) ???\n",tmp_i2 + 0x25,tmp_i6);
      }
      else {
        G_shrubbot_duration(tmp_i6 - *(int *)(tmp_i2 + 0xc74),local_81c,0x400);
        tmp_i6 = *local_888 + 0x1c;
        tmp_u4 = va("^xSeen: ^w%s ^g(%s) %s ago.\n",*local_888 + 0x25,tmp_i6,local_81c);
      }
      if (param_1 == 0) {
        DecolorString(tmp_u4,local_41c);
        G_Printf(local_41c);
        tmp_i2 = local_888[1];
        goto joined_r0x000d723b;
      }
      tmp_u4 = va("print \"%s\"",tmp_u4,tmp_i6);
      trap_SendServerCommand(tmp_i7,tmp_u4);
      local_888 = local_888 + 1;
      tmp_i2 = *local_888;
    } while (tmp_i2 != 0);
LAB_000d702c:
    if (local_878 != 0) {
      if (0xe < local_878) {
        tmp_u4 = va("^xSeen: ^g%d player(s) found.\n",0xf);
        G_shrubbot_print(param_1,tmp_u4);
        if (local_878 != 0xf) {
          tmp_u4 = va("^xSeen: ^gToo many matches (%d). Please be more specific.\n",local_878);
          G_shrubbot_print(param_1,tmp_u4);
        }
        return 1;
      }
      tmp_u4 = va("^xSeen: ^g%d player(s) found.\n",local_878);
      goto LAB_000d7262;
    }
  }
  tmp_u4 = va("^xSeen: ^gNo player found.\n");
LAB_000d7262:
  G_shrubbot_print(param_1,tmp_u4);
  return 1;
}

uint32_t G_shrubbot_levdelete(int param_1,int param_2)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  int *tmp_pi5;
  int tmp_i6;
  int local_44;
  long local_40;
  char local_34 [12];
  char local_28 [24];
  
  if (param_1 == 0) {
    tmp_i1 = Q_SayArgc();
    if (tmp_i1 <= param_2 + 1) {
      G_shrubbot_print_part_8();
      return 0;
    }
  }
  else {
    tmp_i1 = Nit_SecureShrubEnabled();
    if ((tmp_i1 != 0) && (*(int *)(*(int *)(param_1 + 400) + 0xf2c) == 0)) {
      Nit_SecureShrubError(param_1,"levdelete");
      return 0;
    }
    tmp_i1 = Q_SayArgc();
    if (tmp_i1 <= param_2 + 1) {
      tmp_pc4 = "^9usage: ^g!levdelete [level#] (MigrateUsersToLevel#)^7\n";
      goto LAB_000d74c7;
    }
  }
  Q_SayArgv(param_2 + 1,local_34,0xc);
  tmp_i6 = 0;
  Q_SayArgv(param_2 + 2,local_28,0xc);
  tmp_l2 = strtol(local_34,(char **)0x0,10);
  tmp_i1 = Levels;
  while (tmp_i1 != 0) {
    tmp_i6 = tmp_i6 + 1;
    tmp_i1 = (&Levels)[tmp_i6];
  }
  tmp_i1 = nitrox_LevelExists(tmp_l2);
  if (tmp_i1 == 0) {
    G_shrubbot_print(param_1,"^1levdelete error: ^9Unknown level^7\n");
    return 0;
  }
  if (tmp_l2 != 0) {
    if (tmp_i6 == 1) {
      G_shrubbot_print(param_1,"^1levdelete error: ^9You can\'t delete the last level!^7\n");
      return 0;
    }
    if (local_28[0] == '\0') {
      local_40 = 0;
    }
    else {
      local_40 = strtol(local_28,(char **)0x0,10);
      tmp_i1 = nitrox_LevelExists(local_40);
      if (tmp_i1 == 0) {
        G_shrubbot_print(param_1,"^1levdelete error: ^9Unknown level to migrate users to^7\n");
        return 0;
      }
      if (tmp_l2 == local_40) {
        tmp_u3 = va(
                  "^1levdelete error: ^9You can\'t migrate users to the level you are about to delete^7\n"
                  );
        G_shrubbot_print(param_1,tmp_u3);
        return 0;
      }
    }
    tmp_i1 = nitrox_LevelPointer(tmp_l2);
    *(uint32_t *)(tmp_i1 + 0xc28) = 1;
    tmp_u3 = va("^xlevdelete: ^9level ^7%d successfully deleted^7\n",tmp_l2);
    if (param_1 == 0) {
      G_shrubbot_print_part_8();
    }
    else {
      tmp_u3 = va("print \"%s\"",tmp_u3);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
    }
    if (Users != 0) {
      local_44 = 0;
      tmp_pi5 = &g_unk_02db1044;
      tmp_i1 = Users;
      do {
        while (**(int **)(tmp_i1 + 0x4c) != tmp_l2) {
          tmp_i1 = *tmp_pi5;
          tmp_pi5 = tmp_pi5 + 1;
          if (tmp_i1 == 0) goto LAB_000d7466;
        }
        tmp_u3 = nitrox_LevelPointer(local_40);
        local_44 = local_44 + 1;
        *(uint32_t *)(tmp_i1 + 0x4c) = tmp_u3;
        tmp_i1 = *tmp_pi5;
        tmp_pi5 = tmp_pi5 + 1;
      } while (tmp_i1 != 0);
LAB_000d7466:
      if (local_44 != 0) {
        nitrox_SQLite_MigrateUsers(tmp_l2,local_40);
        tmp_u3 = va("^xlevdelete: ^7%i ^gusers migrated to level ^7%i\n",local_44,local_40);
        G_shrubbot_print(param_1,tmp_u3);
      }
    }
    nitrox_SaveDBFile_levels();
    nitrox_LoadDBFile_levels();
    nitrox_LoadUsers();
    return 0;
  }
  tmp_pc4 = "^1levdelete error: ^9Level ^70 ^gcan not be deleted!^7\n";
  if (param_1 == 0) {
    G_shrubbot_print_part_8();
    return 0;
  }
LAB_000d74c7:
  tmp_u3 = va("print \"%s\"",tmp_pc4);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u3);
  return 0;
}

uint32_t G_shrubbot_levadd(int param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  long tmp_l3;
  long *plVar4;
  uint32_t tmp_u5;
  uint tmp_u6;
  char *tmp_pc7;
  int tmp_i8;
  uint32_t *tmp_pu9;
  uint8_t **tmp_ppu10;
  long *local_2c;
  char local_28 [24];
  
  if (param_1 == 0) {
    tmp_i2 = Q_SayArgc();
    if (param_2 + 1 < tmp_i2) {
LAB_000d766f:
      Q_SayArgv(param_2 + 1,local_28,0xc);
      tmp_l3 = strtol(local_28,(char **)0x0,10);
      if (Levels != (int *)0x0) {
        if (*Levels == tmp_l3) {
LAB_000d7800:
          tmp_u5 = va("^1levadd error: ^9Level already exists : ^g%d^7\n",tmp_l3);
          G_shrubbot_print(param_1,tmp_u5);
          return 0;
        }
        tmp_pu9 = &g_unk_02db0c44;
LAB_000d76cb:
        tmp_pi1 = (int *)*tmp_pu9;
        if (tmp_pi1 != (int *)0x0) goto LAB_000d76c0;
        tmp_i2 = 0;
        do {
          tmp_i2 = tmp_i2 + 1;
        } while ((&Levels)[tmp_i2] != (int *)0x0);
        goto LAB_000d76ec;
      }
      tmp_i2 = 0;
LAB_000d76ec:
      plVar4 = malloc(0xd68);
      plVar4[0x30a] = 0;
      *plVar4 = tmp_l3;
      *(uint8_t *)(plVar4 + 1) = 0;
      *(uint8_t *)(plVar4 + 10) = 0;
      *(uint8_t *)(plVar4 + 0x10a) = 0;
      *(uint8_t *)(plVar4 + 0x20a) = 0;
      (&Levels)[tmp_i2] = plVar4;
      tmp_u5 = va("^xlevadd: ^9level ^7%d successfully added^7\n",tmp_l3);
      if (param_1 == 0) {
        G_shrubbot_print_part_8();
      }
      else {
        tmp_u5 = va("print \"%s\"",tmp_u5);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
      }
      nitrox_SaveDBFile_levels();
      nitrox_SetLevelPermissions(plVar4);
      if ((char)plVar4[10] != '\0') {
        local_2c = plVar4 + 10;
        tmp_u6 = 0;
        do {
          *(uint32_t *)((int)plVar4 + tmp_u6 + 0xc30) = 0;
          *(uint32_t *)((int)plVar4 + tmp_u6 + 0xc34) = 0;
          tmp_u6 = tmp_u6 + 8;
        } while (tmp_u6 < 0x138);
        do {
          tmp_pc7 = (char *)COM_ParseExt(&local_2c,0);
          if ((tmp_pc7 == (char *)0x0) || (*tmp_pc7 == '\0')) goto LAB_000d77b2;
          tmp_ppu10 = &g_shrubbot_cmds;
          tmp_i2 = 0;
          do {
            tmp_i8 = Q_stricmp(*tmp_ppu10,tmp_pc7);
            if (tmp_i8 == 0) {
              plVar4[tmp_i2 + 0x30c] = 1;
              break;
            }
            tmp_i2 = tmp_i2 + 1;
            tmp_ppu10 = tmp_ppu10 + 5;
          } while (tmp_i2 != 0x4e);
        } while( true );
      }
      tmp_u6 = 0;
      do {
        *(uint32_t *)((int)plVar4 + tmp_u6 + 0xc30) = 0;
        *(uint32_t *)((int)plVar4 + tmp_u6 + 0xc34) = 0;
        tmp_u6 = tmp_u6 + 8;
      } while (tmp_u6 < 0x138);
LAB_000d77b2:
      nitrox_LoadDBFile_levels();
      return 0;
    }
    G_shrubbot_print_part_8();
  }
  else {
    tmp_i2 = Nit_SecureShrubEnabled();
    if ((tmp_i2 == 0) || (*(int *)(*(int *)(param_1 + 400) + 0xf2c) != 0)) {
      tmp_i2 = Q_SayArgc();
      if (param_2 + 1 < tmp_i2) goto LAB_000d766f;
      tmp_u5 = va("print \"%s\"","^9usage: ^g!levadd [level#]^7\n");
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
    }
    else {
      Nit_SecureShrubError(param_1,"levadd");
    }
  }
  return 0;
LAB_000d76c0:
  tmp_pu9 = tmp_pu9 + 1;
  if (*tmp_pi1 == tmp_l3) goto LAB_000d7800;
  goto LAB_000d76cb;
}

uint32_t G_shrubbot_listplayers(int param_1)
{
  uint32_t tmp_u1;
  int *tmp_pi2;
  uint32_t tmp_u3;
  size_t tmp_s4;
  uint8_t *tmp_pu5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  int local_38;
  int local_34;
  
  if (g_unk_00abe938 < 1) {
    G_shrubbot_print(param_1,"^9No players connected\n");
    return 0;
  }
  if (param_1 == 0) {
    G_shrubbot_print_part_8();
  }
  else {
    tmp_u1 = va("print \"%s\"","^9  # | L  | NAME                                  \n");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
  }
  if (0 < g_unk_00abe938) {
    local_34 = 0;
    tmp_pi2 = &g_unk_00abe944;
    tmp_i8 = 0;
    local_38 = 0;
    do {
      while (tmp_i9 = *(int *)(level + 3000 + *tmp_pi2 * 0x54dc), tmp_i9 != 3) {
        if (tmp_i9 == 2) {
          local_34 = local_34 + 1;
        }
        else {
          tmp_i8 = tmp_i8 + (uint)(tmp_i9 == 1);
        }
        tmp_pi2 = tmp_pi2 + 1;
        if (tmp_pi2 == &g_unk_00abe944 + g_unk_00abe938) goto LAB_000d7b76;
      }
      tmp_pi2 = tmp_pi2 + 1;
      local_38 = local_38 + 1;
    } while (tmp_pi2 != &g_unk_00abe944 + g_unk_00abe938);
LAB_000d7b76:
    if (tmp_i8 != 0) {
      if (param_1 == 0) {
        G_shrubbot_print_part_8();
      }
      else {
        tmp_u1 = va("print \"%s\"","^9----------------------^_AXIS^9-----------------------\n");
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
      }
      if (0 < g_unk_00abe938) {
        tmp_i9 = 0;
        tmp_i8 = g_unk_00abe938;
        do {
          while( true ) {
            tmp_i7 = (&g_unk_00abe944)[tmp_i9];
            tmp_i6 = tmp_i7 * 0x54dc + level;
            if (*(int *)(tmp_i6 + 3000) == 1) break;
LAB_000d7bf8:
            tmp_i9 = tmp_i9 + 1;
            if (tmp_i8 <= tmp_i9) goto LAB_000d7d20;
          }
          tmp_u1 = nitrox_GetAdminLevel(g_entities + tmp_i7 * 0x600,1);
          bigTextBuffer = 0;
          tmp_i8 = tmp_i6 + 0x5f8;
          if ((*(int *)(tmp_i6 + 0xbf0) == 0) &&
             ((g_unk_02af58b8 == 0 || (tmp_i6 = G_shrubbot_mute_check_part_6(), tmp_i6 == 0)))) {
            tmp_pu5 = &g_unk_0026f114;
          }
          else {
            tmp_pu5 = &g_unk_00258b23;
          }
          tmp_u3 = va(" ^%s%2i ^9| ^g%-2i ^9| ^7%s\n",tmp_pu5,tmp_i7,tmp_u1,tmp_i8);
          if (param_1 == 0) {
            G_shrubbot_buffer_print_part_15();
            G_shrubbot_print_part_8();
            tmp_i8 = g_unk_00abe938;
            goto LAB_000d7bf8;
          }
          Q_strcat(&bigTextBuffer,100000,tmp_u3);
          tmp_s4 = strlen(&bigTextBuffer);
          if (1000 < tmp_s4) {
            nitrox_bigBufferPrint(param_1);
            tmp_i8 = g_unk_00abe938;
            goto LAB_000d7bf8;
          }
          tmp_i9 = tmp_i9 + 1;
          tmp_u1 = va("print \"%s\"",&bigTextBuffer,tmp_u3,tmp_u1,tmp_i8);
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
          tmp_i8 = g_unk_00abe938;
        } while (tmp_i9 < g_unk_00abe938);
      }
    }
LAB_000d7d20:
    if (local_34 != 0) {
      if (param_1 == 0) {
        G_shrubbot_print_part_8();
      }
      else {
        tmp_u1 = va("print \"%s\"","^9---------------------^4ALLIES^9----------------------\n");
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
      }
      if (0 < g_unk_00abe938) {
        tmp_i9 = 0;
        tmp_i8 = g_unk_00abe938;
        do {
          while( true ) {
            tmp_i7 = (&g_unk_00abe944)[tmp_i9];
            tmp_i6 = tmp_i7 * 0x54dc + level;
            if (*(int *)(tmp_i6 + 3000) == 2) break;
LAB_000d7da8:
            tmp_i9 = tmp_i9 + 1;
            if (tmp_i8 <= tmp_i9) goto LAB_000d7ed0;
          }
          tmp_u1 = nitrox_GetAdminLevel(g_entities + tmp_i7 * 0x600,1);
          bigTextBuffer = 0;
          tmp_i8 = tmp_i6 + 0x5f8;
          if ((*(int *)(tmp_i6 + 0xbf0) == 0) &&
             ((g_unk_02af58b8 == 0 || (tmp_i6 = G_shrubbot_mute_check_part_6(), tmp_i6 == 0)))) {
            tmp_pu5 = &g_unk_0026f114;
          }
          else {
            tmp_pu5 = &g_unk_00258b23;
          }
          tmp_u3 = va(" ^%s%2i ^9| ^g%-2i ^9| ^7%s\n",tmp_pu5,tmp_i7,tmp_u1,tmp_i8);
          if (param_1 == 0) {
            G_shrubbot_buffer_print_part_15();
            G_shrubbot_print_part_8();
            tmp_i8 = g_unk_00abe938;
            goto LAB_000d7da8;
          }
          Q_strcat(&bigTextBuffer,100000,tmp_u3);
          tmp_s4 = strlen(&bigTextBuffer);
          if (1000 < tmp_s4) {
            nitrox_bigBufferPrint(param_1);
            tmp_i8 = g_unk_00abe938;
            goto LAB_000d7da8;
          }
          tmp_i9 = tmp_i9 + 1;
          tmp_u1 = va("print \"%s\"",&bigTextBuffer,tmp_u3,tmp_u1,tmp_i8);
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
          tmp_i8 = g_unk_00abe938;
        } while (tmp_i9 < g_unk_00abe938);
      }
    }
LAB_000d7ed0:
    if (local_38 != 0) {
      if (param_1 == 0) {
        G_shrubbot_print_part_8();
        if (g_unk_00abe938 < 1) goto LAB_000d8299;
      }
      else {
        tmp_u1 = va("print \"%s\"","^9-------------------^xSPECTATORS^9--------------------\n");
        tmp_i8 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        trap_SendServerCommand(tmp_i8,tmp_u1);
        if (g_unk_00abe938 < 1) goto LAB_000d80a7;
      }
      tmp_i8 = 0;
      do {
        while( true ) {
          tmp_i9 = (&g_unk_00abe944)[tmp_i8];
          tmp_i7 = tmp_i9 * 0x54dc + level;
          if (*(int *)(tmp_i7 + 3000) == 3) break;
LAB_000d7f50:
          tmp_i8 = tmp_i8 + 1;
          if (g_unk_00abe938 <= tmp_i8) goto LAB_000d8080;
        }
        tmp_u1 = nitrox_GetAdminLevel(g_entities + tmp_i9 * 0x600,1);
        bigTextBuffer = 0;
        tmp_i6 = tmp_i7 + 0x5f8;
        if ((*(int *)(tmp_i7 + 0xbf0) == 0) &&
           ((g_unk_02af58b8 == 0 || (tmp_i7 = G_shrubbot_mute_check_part_6(), tmp_i7 == 0)))) {
          tmp_pu5 = &g_unk_0026f114;
        }
        else {
          tmp_pu5 = &g_unk_00258b23;
        }
        tmp_u3 = va(" ^%s%2i ^9| ^g%-2i ^9| ^7%s\n",tmp_pu5,tmp_i9,tmp_u1,tmp_i6);
        if (param_1 == 0) {
          G_shrubbot_buffer_print_part_15();
          G_shrubbot_print_part_8();
          goto LAB_000d7f50;
        }
        Q_strcat(&bigTextBuffer,100000,tmp_u3);
        tmp_s4 = strlen(&bigTextBuffer);
        if (1000 < tmp_s4) {
          nitrox_bigBufferPrint(param_1);
          goto LAB_000d7f50;
        }
        tmp_i8 = tmp_i8 + 1;
        tmp_u1 = va("print \"%s\"",&bigTextBuffer,tmp_u3,tmp_u1,tmp_i6);
        trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
      } while (tmp_i8 < g_unk_00abe938);
    }
  }
LAB_000d8080:
  if (param_1 == 0) {
LAB_000d8299:
    G_shrubbot_print_part_8();
    G_shrubbot_print_part_8();
    va("^x%d ^9players connected\n",g_unk_00abe938);
    G_shrubbot_print_part_8();
    return 1;
  }
  tmp_i8 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
LAB_000d80a7:
  tmp_u1 = va("print \"%s\"","^9-------------------------------------------------\n");
  trap_SendServerCommand(tmp_i8,tmp_u1);
  tmp_u1 = va("print \"%s\"","^9Info : ^gred slot# = player muted\n");
  trap_SendServerCommand(tmp_i8,tmp_u1);
  tmp_u1 = va("^x%d ^9players connected\n",g_unk_00abe938);
  tmp_u1 = va("print \"%s\"",tmp_u1);
  trap_SendServerCommand(tmp_i8,tmp_u1);
  return 1;
}

uint32_t G_shrubbot_stats(int param_1)
{
  char *__s;
  float tmp_f1;
  uint tmp_u2;
  uint tmp_u3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  size_t tmp_s8;
  uint *tmp_pu9;
  uint *tmp_pu10;
  int tmp_i11;
  uint *tmp_pu12;
  int tmp_i13;
  int local_c94;
  int local_c80;
  uint local_c7c;
  float local_c70;
  uint8_t local_c69 [5];
  uint local_c64 [9];
  uint8_t local_c40 [36];
  uint8_t local_c1c [1024];
  uint local_81c [256];
  uint local_41c [258];
  uint32_t uStack_14;
  
  uStack_14 = 0xd8329;
  bigTextBuffer = 0;
  if (param_1 == 0) {
    DecolorString("^xstats: ^9Showing ^gThompson^9 and ^gMP40 ^9stats of all connected players\n",
                  local_41c);
    tmp_pu9 = local_41c;
    do {
      tmp_pu10 = tmp_pu9;
      tmp_u2 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
      tmp_u3 = tmp_u2 & 0x80808080;
      tmp_pu9 = tmp_pu10 + 1;
    } while (tmp_u3 == 0);
    if ((tmp_u2 & 0x8080) == 0) {
      tmp_pu9 = (uint *)((int)tmp_pu10 + 6);
      tmp_u3 = tmp_u3 >> 0x10;
    }
    tmp_s8 = strlen(&bigTextBuffer);
    if (0xef < (int)tmp_pu9 + tmp_s8 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_41c)
       ) {
      G_shrubbot_print(0,&bigTextBuffer);
      bigTextBuffer = 0;
    }
    Q_strcat(&bigTextBuffer,100000,local_41c);
    if (0 < g_unk_00abe900) goto LAB_000d837f;
    Com_sprintf(local_c1c,0x400,"^x%%%is SHOTS  HITS   ACC  HEAD    HR\n",4);
    tmp_u4 = va(local_c1c,"^gNAME");
    local_c7c = 4;
LAB_000d89c7:
    DecolorString(tmp_u4,local_41c);
    tmp_pu9 = local_41c;
    do {
      tmp_pu10 = tmp_pu9;
      tmp_u2 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
      tmp_u3 = tmp_u2 & 0x80808080;
      tmp_pu9 = tmp_pu10 + 1;
    } while (tmp_u3 == 0);
    if ((tmp_u2 & 0x8080) == 0) {
      tmp_pu9 = (uint *)((int)tmp_pu10 + 6);
      tmp_u3 = tmp_u3 >> 0x10;
    }
    tmp_s8 = strlen(&bigTextBuffer);
    if (0xef < (int)tmp_pu9 + tmp_s8 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_41c)
       ) {
      G_shrubbot_print(0,&bigTextBuffer);
      bigTextBuffer = 0;
    }
    Q_strcat(&bigTextBuffer,100000,local_41c);
    if (0 < g_unk_00abe900) goto LAB_000d8491;
LAB_000d8a62:
    DecolorString(&bigTextBuffer,local_41c);
    G_Printf(local_41c);
  }
  else {
    Q_strcat(&bigTextBuffer,100000,
             "^xstats: ^9Showing ^gThompson^9 and ^gMP40 ^9stats of all connected players\n");
    if (g_unk_00abe900 < 1) {
      Com_sprintf(local_c1c,0x400,"^x%%%is SHOTS  HITS   ACC  HEAD    HR\n",4);
      tmp_u4 = va(local_c1c,"^gNAME");
      local_c7c = 4;
    }
    else {
LAB_000d837f:
      tmp_i13 = 0;
      local_c7c = 4;
      tmp_i11 = 0;
      do {
        while (*(int *)(level + tmp_i13 + 0x5ac) == 2) {
          DecolorString(level + tmp_i13 + 0x5f8,local_c64);
          tmp_pu9 = local_c64;
          do {
            tmp_pu10 = tmp_pu9;
            tmp_u2 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
            tmp_u3 = tmp_u2 & 0x80808080;
            tmp_pu9 = tmp_pu10 + 1;
          } while (tmp_u3 == 0);
          if ((tmp_u2 & 0x8080) == 0) {
            tmp_pu9 = (uint *)((int)tmp_pu10 + 6);
            tmp_u3 = tmp_u3 >> 0x10;
          }
          tmp_u3 = (int)tmp_pu9 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_c64);
          if (tmp_u3 <= local_c7c) {
            tmp_u3 = local_c7c;
          }
          tmp_i11 = tmp_i11 + 1;
          tmp_i13 = tmp_i13 + 0x54dc;
          local_c7c = tmp_u3;
          if (g_unk_00abe900 <= tmp_i11) goto LAB_000d8420;
        }
        tmp_i11 = tmp_i11 + 1;
        tmp_i13 = tmp_i13 + 0x54dc;
      } while (tmp_i11 < g_unk_00abe900);
LAB_000d8420:
      Com_sprintf(local_c1c,0x400,"^x%%%is SHOTS  HITS   ACC  HEAD    HR\n",local_c7c);
      tmp_u4 = va(local_c1c,"^gNAME");
      if (param_1 == 0) goto LAB_000d89c7;
    }
    Q_strcat(&bigTextBuffer,100000,tmp_u4);
    if (0 < g_unk_00abe900) {
LAB_000d8491:
      tmp_i11 = 0;
      do {
        while (tmp_i13 = tmp_i11 * 0x54dc + level, *(int *)(tmp_i13 + 0x5ac) == 2) {
          tmp_i5 = *(int *)(tmp_i13 + 0xce8) + *(int *)(tmp_i13 + 0xcfc);
          tmp_i6 = *(int *)(tmp_i13 + 0xcf4) + *(int *)(tmp_i13 + 0xd08);
          tmp_i7 = *(int *)(tmp_i13 + 0xcf0) + *(int *)(tmp_i13 + 0xd04);
          if ((tmp_i6 < 0) || (tmp_i5 < 1)) {
            if ((tmp_i7 < 0) || (tmp_i6 < 1)) {
              local_c70 = 0.0;
              tmp_f1 = 0.0;
LAB_000d8844:
              local_c94 = 0x33 - (uint)(tmp_f1 < 30.0);
LAB_000d8859:
              if (12.5 <= local_c70) goto LAB_000d88ba;
LAB_000d8872:
              local_c80 = 0x33 - (uint)(local_c70 < 7.5);
            }
            else {
              local_c70 = ((float)tmp_i7 * 100.0) / (float)tmp_i6;
              tmp_f1 = 0.0;
LAB_000d87c0:
              if (local_c70 <= 999.9) {
LAB_000d8832:
                if (tmp_f1 < 40.0) goto LAB_000d8844;
                local_c94 = 0x31;
                goto LAB_000d8859;
              }
              if (tmp_f1 < 40.0) {
                if (tmp_f1 < 30.0) {
                  local_c70 = 999.9;
                  local_c94 = 0x32;
                  goto LAB_000d8859;
                }
                local_c70 = 999.9;
                local_c94 = 0x33;
                local_c80 = 0x31;
              }
              else {
                local_c70 = 999.9;
                local_c94 = 0x31;
                local_c80 = 0x31;
              }
            }
          }
          else {
            tmp_f1 = ((float)tmp_i6 * 100.0) / (float)tmp_i5;
            if ((-1 < tmp_i7) && (0 < tmp_i6)) {
              local_c70 = ((float)tmp_i7 * 100.0) / (float)tmp_i6;
              if (tmp_f1 <= 999.9) goto LAB_000d87c0;
              if (local_c70 <= 999.9) goto LAB_000d8892;
              tmp_f1 = 999.9;
              local_c94 = 0x31;
              local_c80 = 0x31;
              local_c70 = tmp_f1;
              goto LAB_000d85b0;
            }
            local_c70 = 0.0;
            if (tmp_f1 <= 999.9) goto LAB_000d8832;
            local_c70 = 0.0;
LAB_000d8892:
            tmp_f1 = 999.9;
            local_c94 = 0x31;
            if (local_c70 < 12.5) goto LAB_000d8872;
LAB_000d88ba:
            local_c80 = 0x31;
          }
LAB_000d85b0:
          __s = (char *)(tmp_i13 + 0x5f8);
          DecolorString(__s,local_c64);
          tmp_pu9 = local_c64;
          do {
            tmp_pu10 = tmp_pu9;
            tmp_u2 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
            tmp_u3 = tmp_u2 & 0x80808080;
            tmp_pu9 = tmp_pu10 + 1;
          } while (tmp_u3 == 0);
          if ((tmp_u2 & 0x8080) == 0) {
            tmp_pu9 = (uint *)((int)tmp_pu10 + 6);
            tmp_u3 = tmp_u3 >> 0x10;
          }
          tmp_s8 = strlen(__s);
          Com_sprintf(local_c69,5,&g_unk_002527aa,
                      tmp_s8 + (local_c7c -
                              ((int)tmp_pu9 +
                              ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_c64))));
          Com_sprintf(local_c40,0x24,local_c69,__s);
          tmp_pu9 = (uint *)va("^7%s ^2%5i %5i ^%c%5.1f ^2%5i ^%c%5.1f\n",local_c40,tmp_i5,tmp_i6,
                              local_c94,(double)tmp_f1,tmp_i7,local_c80,(double)local_c70);
          if (param_1 == 0) {
            DecolorString(tmp_pu9,local_81c);
            tmp_pu9 = local_81c;
            do {
              tmp_pu10 = tmp_pu9;
              tmp_u2 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
              tmp_u3 = tmp_u2 & 0x80808080;
              tmp_pu9 = tmp_pu10 + 1;
            } while (tmp_u3 == 0);
            tmp_pu12 = tmp_pu10 + 1;
            if ((tmp_u2 & 0x8080) == 0) {
              tmp_pu12 = (uint *)((int)tmp_pu10 + 6);
              tmp_u3 = tmp_u3 >> 0x10;
            }
            tmp_s8 = strlen(&bigTextBuffer);
            tmp_pu9 = local_81c;
            if (0xef < (int)tmp_pu12 +
                       tmp_s8 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_81c)) {
              DecolorString(&bigTextBuffer,local_41c);
              G_Printf(local_41c);
              bigTextBuffer = 0;
            }
          }
          tmp_i11 = tmp_i11 + 1;
          Q_strcat(&bigTextBuffer,100000,tmp_pu9);
          if (g_unk_00abe900 <= tmp_i11) goto LAB_000d8702;
        }
        tmp_i11 = tmp_i11 + 1;
      } while (tmp_i11 < g_unk_00abe900);
LAB_000d8702:
      if (param_1 == 0) goto LAB_000d8a62;
    }
    tmp_s8 = strlen(&bigTextBuffer);
    if (1000 < tmp_s8) {
      nitrox_bigBufferPrint(param_1);
      return 1;
    }
    tmp_u4 = va("print \"%s\"",&bigTextBuffer);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
  }
  return 1;
}

uint32_t G_shrubbot_userinfo(int param_1,int param_2)
{
  char tmp_c1;
  int tmp_i2;
  size_t tmp_s3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  int tmp_i6;
  char local_65 [9];
  uint8_t local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0xd8c49;
  tmp_i2 = Q_SayArgc();
  if (param_2 + 1 < tmp_i2) {
    Q_SayArgv(param_2 + 1,local_65,9);
    tmp_s3 = strlen(local_65);
    if (tmp_s3 == 8) {
      tmp_i6 = 0;
      tmp_i2 = Users;
      while (tmp_i2 != 0) {
        tmp_i2 = Q_stricmp(local_65,tmp_i2 + 0x1c);
        if (tmp_i2 == 0) {
          bigTextBuffer = 0;
          tmp_u4 = va("^9Name:   ^g%s\n",(&Users)[tmp_i6] + 0x25);
          if (param_1 == 0) {
            G_shrubbot_buffer_print_part_15();
            va("^9Level:  ^g%d\n",**(uint32_t **)((&Users)[tmp_i6] + 0x4c));
            G_shrubbot_buffer_print_part_15();
            va("^9NGUID:  ^g%s\n",(&Users)[tmp_i6] + 4);
            G_shrubbot_buffer_print_part_15();
            va("^9UserID: ^g%s\n",(&Users)[tmp_i6] + 0x1c);
            G_shrubbot_buffer_print_part_15();
            va("^9IP:     ^g%s\n",(&Users)[tmp_i6] + 0xc62);
            G_shrubbot_buffer_print_part_15();
            va("^9MAC:    ^g%s\n",(&Users)[tmp_i6] + 0xc50);
            G_shrubbot_buffer_print_part_15();
            tmp_i2 = (&Users)[tmp_i6];
            if (*(char *)(tmp_i2 + 0x450) == '\0') {
              if (*(char *)(tmp_i2 + 0x850) == '\0') goto LAB_000d8e1a;
LAB_000d916a:
              va("^9GSound: ^g%s\n",tmp_i2 + 0x850);
              G_shrubbot_buffer_print_part_15();
              tmp_i2 = (&Users)[tmp_i6];
              tmp_c1 = *(char *)(tmp_i2 + 0x50);
            }
            else {
              va("^9GText:  ^g%s\n",tmp_i2 + 0x450);
              G_shrubbot_buffer_print_part_15();
              tmp_i2 = (&Users)[tmp_i6];
              if (*(char *)(tmp_i2 + 0x850) != '\0') goto LAB_000d916a;
              tmp_c1 = *(char *)(tmp_i2 + 0x50);
            }
            if (tmp_c1 != '\0') {
              va("^9Flags:  ^g%s\n",tmp_i2 + 0x50);
              goto LAB_000d91ac;
            }
LAB_000d8e24:
            if (*(int *)(tmp_i2 + 0xc74) == 0) goto LAB_000d8e32;
            tmp_i2 = G_GetCurrentTime();
            G_shrubbot_duration(tmp_i2 - *(int *)((&Users)[tmp_i6] + 0xc74),local_5c,0x40);
            tmp_u4 = va("^xSeen:   ^g%s ago.\n",local_5c);
            if (param_1 != 0) goto LAB_000d8fd2;
          }
          else {
            Q_strcat(&bigTextBuffer,100000,tmp_u4);
            tmp_u4 = va("^9Level:  ^g%d\n",**(uint32_t **)((&Users)[tmp_i6] + 0x4c));
            Q_strcat(&bigTextBuffer,100000,tmp_u4);
            tmp_u4 = va("^9NGUID:  ^g%s\n",(&Users)[tmp_i6] + 4);
            Q_strcat(&bigTextBuffer,100000,tmp_u4);
            tmp_u4 = va("^9UserID: ^g%s\n",(&Users)[tmp_i6] + 0x1c);
            Q_strcat(&bigTextBuffer,100000,tmp_u4);
            tmp_u4 = va("^9IP:     ^g%s\n",(&Users)[tmp_i6] + 0xc62);
            Q_strcat(&bigTextBuffer,100000,tmp_u4);
            tmp_u4 = va("^9MAC:    ^g%s\n",(&Users)[tmp_i6] + 0xc50);
            Q_strcat(&bigTextBuffer,100000,tmp_u4);
            tmp_i2 = (&Users)[tmp_i6];
            if (*(char *)(tmp_i2 + 0x450) != '\0') {
              tmp_u4 = va("^9GText:  ^g%s\n",tmp_i2 + 0x450);
              Q_strcat(&bigTextBuffer,100000,tmp_u4);
              tmp_i2 = (&Users)[tmp_i6];
              if (*(char *)(tmp_i2 + 0x850) != '\0') {
LAB_000d925b:
                tmp_u4 = va("^9GSound: ^g%s\n",tmp_i2 + 0x850);
                Q_strcat(&bigTextBuffer,100000,tmp_u4);
                tmp_i2 = (&Users)[tmp_i6];
                if (*(char *)(tmp_i2 + 0x50) != '\0') goto LAB_000d9294;
                goto LAB_000d8e24;
              }
              if (*(char *)(tmp_i2 + 0x50) == '\0') goto LAB_000d8e24;
LAB_000d9294:
              tmp_u4 = va("^9Flags:  ^g%s\n",tmp_i2 + 0x50);
LAB_000d9014:
              Q_strcat(&bigTextBuffer,100000,tmp_u4);
              if (*(int *)((&Users)[tmp_i6] + 0xc74) != 0) {
                tmp_i2 = G_GetCurrentTime();
                G_shrubbot_duration(tmp_i2 - *(int *)((&Users)[tmp_i6] + 0xc74),local_5c,0x40);
                tmp_u4 = va("^xSeen:   ^g%s ago.\n",local_5c);
LAB_000d8fd2:
                Q_strcat(&bigTextBuffer,100000,tmp_u4);
              }
LAB_000d8e32:
              if (param_1 != 0) {
                tmp_s3 = strlen(&bigTextBuffer);
                if (1000 < tmp_s3) {
                  nitrox_bigBufferPrint(param_1);
                  return 1;
                }
                tmp_u4 = va("print \"%s\"",&bigTextBuffer);
                trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
                return 1;
              }
              goto LAB_000d920b;
            }
            if (*(char *)(tmp_i2 + 0x850) != '\0') goto LAB_000d925b;
LAB_000d8e1a:
            if (*(char *)(tmp_i2 + 0x50) == '\0') goto LAB_000d8e24;
            tmp_u4 = va("^9Flags:  ^g%s\n",tmp_i2 + 0x50);
            if (param_1 != 0) goto LAB_000d9014;
LAB_000d91ac:
            G_shrubbot_buffer_print_part_15();
            if (*(int *)((&Users)[tmp_i6] + 0xc74) == 0) goto LAB_000d920b;
            tmp_i2 = G_GetCurrentTime();
            G_shrubbot_duration(tmp_i2 - *(int *)((&Users)[tmp_i6] + 0xc74),local_5c,0x40);
            va("^xSeen:   ^g%s ago.\n",local_5c);
          }
          G_shrubbot_buffer_print_part_15();
LAB_000d920b:
          G_shrubbot_print_part_8();
          return 1;
        }
        tmp_i6 = tmp_i6 + 1;
        tmp_i2 = (&Users)[tmp_i6];
      }
      tmp_pc5 = (char *)va("^1userinfo error: ^9Unknown UserID (^g%s^9)^7\n",local_65);
    }
    else {
      tmp_pc5 = "^1userinfo error: ^9UserID must be 8 chars long. (Extra chars will be ignored)^7\n";
    }
    if (param_1 != 0) {
      tmp_u4 = va("print \"%s\"",tmp_pc5);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
      return 0;
    }
  }
  else if (param_1 != 0) {
    tmp_u4 = va("print \"%s\"","^9usage: ^g!userinfo [userID]^7\n");
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
    return 0;
  }
  G_shrubbot_print_part_8();
  return 0;
}

uint32_t G_shrubbot_showbans(int param_1,int param_2)
{
  byte tmp_b1;
  bool tmp_b2;
  time_t tVar3;
  int tmp_i4;
  int tmp_i5;
  ushort **tmp_ppu6;
  uint32_t tmp_u7;
  char *tmp_pc8;
  uint tmp_u9;
  int tmp_i10;
  size_t tmp_s11;
  size_t tmp_s12;
  char *tmp_pc13;
  uint *tmp_pu14;
  uint *tmp_pu15;
  uint8_t *tmp_pu16;
  uint8_t *tmp_pu17;
  uint8_t *tmp_pu18;
  uint *tmp_pu19;
  uint tmp_u20;
  uint tmp_u21;
  uint tmp_u22;
  char tmp_c23;
  int *tmp_pi24;
  uint *tmp_pu25;
  uint *tmp_pu26;
  int tmp_i27;
  byte tmp_b28;
  uint8_t *tmp_pu29;
  uint *local_24cc;
  int *local_24c8;
  int local_24c4;
  int local_24bc;
  uint *local_24ac;
  int local_24a8;
  uint *local_24a4;
  int local_2490;
  uint *local_2488;
  int local_2478;
  char local_2471;
  char local_2470;
  byte local_2466;
  byte local_2465;
  byte local_2464;
  byte local_2463;
  byte local_2462;
  byte local_2461;
  byte local_2460;
  byte local_245f;
  byte local_245e;
  byte local_245d;
  uint8_t local_245c;
  char local_245b [11];
  uint local_2450 [4];
  uint local_2440 [9];
  uint8_t local_241c [1024];
  uint8_t local_201c [1024];
  uint8_t local_1c1c [1024];
  uint local_181c [256];
  uint32_t local_141c;
  int local_1418 [255];
  int local_101c [1026];
  uint32_t uStack_14;
  
  tmp_b28 = 0;
  uStack_14 = 0xd9309;
  tVar3 = time(&local_2478);
  if (tVar3 == 0) {
    return 0;
  }
  if (first_13464 != 0) {
    memset(&lastViewed_13465,0,0x40004);
    first_13464 = 0;
  }
  local_24c8 = local_1418 + 0xff;
  tmp_u20 = 0x1000;
  tmp_pi24 = local_24c8;
  if (((uint)local_24c8 & 4) != 0) {
    tmp_u20 = 0xffc;
    local_101c[0] = 0;
    tmp_pi24 = local_1418 + 0x100;
  }
  for (tmp_u20 = tmp_u20 >> 2; tmp_u20 != 0; tmp_u20 = tmp_u20 - 1) {
    *tmp_pi24 = 0;
    tmp_pi24 = tmp_pi24 + (uint)tmp_b28 * -2 + 1;
  }
  local_2478 = local_2478 + -0x386a4c20;
  tmp_i4 = Q_SayArgc();
  if (param_1 == 0) {
    g_unk_00818f60 = 0x1e;
    local_2490 = 0;
  }
  else {
    if (0x185ff < param_1 + -0x93e4a0) {
      return 0;
    }
    tmp_i27 = (param_1 + -0x93e4a0 >> 9) * -0x5555390c + level;
    if (Users == 0) {
      local_2490 = 0;
    }
    else {
      local_2490 = 0;
      tmp_i5 = Users;
      do {
        tmp_i5 = strcmp((char *)(tmp_i5 + 4),(char *)(tmp_i27 + 0x61c));
        if (tmp_i5 == 0) {
          (&lastViewed_13465)[local_2490] = 0x1e;
          break;
        }
        local_2490 = local_2490 + 1;
        tmp_i5 = (&Users)[local_2490];
      } while (tmp_i5 != 0);
    }
  }
  tmp_i4 = tmp_i4 - param_2;
  if (tmp_i4 == 1) {
    if (Bans == 0) {
      local_24a4 = (uint *)0x1e;
      local_2488 = (uint *)0x1;
      tmp_pu25 = (uint *)0x0;
      tmp_b2 = true;
      local_24ac = (uint *)0x0;
    }
    else {
      tmp_pu25 = (uint *)0x0;
      tmp_i27 = Bans;
      tmp_pi24 = &g_unk_02df1044;
      do {
        tmp_i27 = *(int *)(tmp_i27 + 0x48c);
        if ((tmp_i27 == 0) || (tmp_i27 != local_2478 && -1 < tmp_i27 - local_2478)) {
          tmp_pu25 = (uint *)((int)tmp_pu25 + 1);
        }
        tmp_i27 = *tmp_pi24;
        tmp_pi24 = tmp_pi24 + 1;
      } while (tmp_i27 != 0);
      tmp_b2 = true;
      local_24ac = (uint *)0x0;
LAB_000d9616:
      local_2488 = (uint *)((int)tmp_pu25 / 0x1e + 1);
      local_24a4 = (uint *)((int)local_24ac + 0x1e);
      tmp_i27 = (&Bans)[(int)local_24ac];
      if ((&Bans)[(int)local_24ac] != 0) goto LAB_000d9652;
    }
    local_24c4 = 0;
    bigTextBuffer = 0;
    tmp_pu26 = local_24ac;
LAB_000da101:
    tmp_i27 = (int)local_24ac / 0x1e;
    tmp_pu18 = (uint8_t *)(tmp_i27 + 1);
    tmp_pu19 = local_24a4;
    if ((int)tmp_pu25 <= (int)local_24ac + 0x1d) {
      tmp_pu19 = tmp_pu25;
    }
    tmp_pu15 = tmp_pu25;
    tmp_pu14 = (uint *)va("^xshowbans: ^9showing bans ^g%d ^9- ^g%d ^9of ^g%d ^9(Page ^g%i ^9of ^g%i^9)\n"
                         ,(int)local_24ac + 1,tmp_pu19,tmp_pu25,tmp_pu18,local_2488);
    if (param_1 == 0) {
      G_shrubbot_buffer_print_part_15();
    }
    else {
      Q_strcat(&bigTextBuffer,100000,tmp_pu14);
      tmp_pu19 = tmp_pu14;
    }
    tmp_pu29 = tmp_pu18;
    if ((int)local_24a4 < (int)tmp_pu25) goto LAB_000da189;
    tmp_pu25 = tmp_pu19;
    if (local_24c4 != 0) goto LAB_000da290;
  }
  else {
    if (tmp_i4 < 2) {
      local_2488 = (uint *)0x1;
      tmp_pu25 = (uint *)0x0;
      local_24a4 = (uint *)0x1e;
      local_24c4 = 0;
      local_24ac = (uint *)0x0;
      if (Bans != 0) {
        tmp_b2 = true;
        tmp_i27 = Bans;
LAB_000d9652:
        local_24bc = 1;
        tmp_pi24 = &Bans + (int)local_24ac;
        local_24a8 = 1;
        tmp_i5 = 0;
        do {
          local_181c[0] = 0;
          tmp_u20 = 0;
          do {
            tmp_u21 = tmp_u20;
            *(uint32_t *)((int)local_181c + tmp_u21 + 4) = 0;
            *(uint32_t *)((int)local_181c + tmp_u21 + 8) = 0;
            tmp_u20 = tmp_u21 + 8;
          } while (tmp_u21 + 8 < 0x3f8);
          *(uint32_t *)((int)local_181c + tmp_u21 + 0xc) = 0;
          local_141c = 0;
          tmp_u20 = 0;
          do {
            tmp_u21 = tmp_u20;
            *(uint32_t *)((int)local_1418 + tmp_u21) = 0;
            *(uint32_t *)((int)local_1418 + tmp_u21 + 4) = 0;
            tmp_u20 = tmp_u21 + 8;
          } while (tmp_u21 + 8 < 0x3f8);
          *(uint32_t *)((int)local_1418 + tmp_u21 + 8) = 0;
          DecolorString(tmp_i27,local_181c);
          tmp_pu26 = local_181c;
          do {
            tmp_pu15 = tmp_pu26;
            tmp_u21 = *tmp_pu15 + 0xfefefeff & ~*tmp_pu15;
            tmp_u20 = tmp_u21 & 0x80808080;
            tmp_pu26 = tmp_pu15 + 1;
          } while (tmp_u20 == 0);
          if ((tmp_u21 & 0x8080) == 0) {
            tmp_pu26 = (uint *)((int)tmp_pu15 + 6);
            tmp_u20 = tmp_u20 >> 0x10;
          }
          DecolorString(*tmp_pi24 + 0x490,&local_141c);
          tmp_pu15 = &local_141c;
          do {
            local_24cc = tmp_pu15;
            tmp_u21 = *local_24cc + 0xfefefeff & ~*local_24cc;
            tmp_u22 = tmp_u21 & 0x80808080;
            tmp_pu15 = local_24cc + 1;
          } while (tmp_u22 == 0);
          tmp_u9 = tmp_u22 >> 0x10;
          tmp_pu15 = (uint *)((int)local_24cc + 6);
          if ((tmp_u21 & 0x8080) != 0) {
            tmp_pu15 = local_24cc + 1;
            tmp_u9 = tmp_u22;
          }
          tmp_i10 = (int)tmp_pu15 + ((-3 - (uint)CARRY1((byte)tmp_u9,(byte)tmp_u9)) - (int)&local_141c);
          tmp_pu15 = local_181c;
          if (local_24a8 <
              (int)((int)tmp_pu26 +
                   ((-3 - (uint)CARRY1((byte)tmp_u20,(byte)tmp_u20)) - (int)local_181c))) {
            do {
              tmp_pu26 = tmp_pu15;
              tmp_u21 = *tmp_pu26 + 0xfefefeff & ~*tmp_pu26;
              tmp_u20 = tmp_u21 & 0x80808080;
              tmp_pu15 = tmp_pu26 + 1;
            } while (tmp_u20 == 0);
            if ((tmp_u21 & 0x8080) == 0) {
              tmp_pu15 = (uint *)((int)tmp_pu26 + 6);
              tmp_u20 = tmp_u20 >> 0x10;
            }
            local_24a8 = (int)tmp_pu15 +
                         ((-3 - (uint)CARRY1((byte)tmp_u20,(byte)tmp_u20)) - (int)local_181c);
          }
          tmp_i27 = tmp_pi24[1];
          if (local_24bc < tmp_i10) {
            local_24bc = tmp_i10;
          }
          tmp_i5 = tmp_i5 + 1;
          tmp_pi24 = tmp_pi24 + 1;
        } while ((tmp_i27 != 0) && (tmp_i5 < 0x1e));
        local_24c4 = 0;
        goto LAB_000d982f;
      }
LAB_000da0bb:
      tmp_b2 = true;
      bigTextBuffer = 0;
      tmp_pu26 = local_24ac;
    }
    else {
      Q_SayArgv(param_2 + 1,&local_2471,0xb);
      if ((tmp_i4 == 2) || (Q_SayArgv(param_2 + 2,local_2450,0x10), tmp_i4 == 3)) {
        local_24ac = (uint *)0x0;
      }
      else {
        Q_SayArgv(param_2 + 3,local_245b,0xb);
        local_24ac = (uint *)strtol(local_245b,(char **)0x0,10);
      }
      tmp_ppu6 = __ctype_b_loc();
      if (((((*(byte *)((int)*tmp_ppu6 + local_2471 * 2 + 1) & 8) != 0) || (local_2471 == '-')) &&
          ((*(byte *)((int)*tmp_ppu6 + local_2470 * 2 + 1) & 8) != 0)) ||
         ((tmp_i27 = Q_stricmp(&local_2471,"next"), tmp_i27 == 0 ||
          (tmp_i27 = Q_stricmp(&local_2471,"prev"), tmp_i27 == 0)))) {
        if (Bans == 0) {
          tmp_pu25 = (uint *)0x0;
        }
        else {
          tmp_pu25 = (uint *)0x0;
          tmp_i27 = Bans;
          tmp_pi24 = &g_unk_02df1044;
          do {
            tmp_i27 = *(int *)(tmp_i27 + 0x48c);
            if ((tmp_i27 == 0) || (tmp_i27 != local_2478 && -1 < tmp_i27 - local_2478)) {
              tmp_pu25 = (uint *)((int)tmp_pu25 + 1);
            }
            tmp_i27 = *tmp_pi24;
            tmp_pi24 = tmp_pi24 + 1;
          } while (tmp_i27 != 0);
        }
        tmp_i27 = Q_stricmp(&local_2471,"next");
        if (tmp_i27 == 0) {
          local_24ac = (uint *)((&lastViewed_13465)[local_2490] + 1);
LAB_000d94e3:
          if ((int)local_24ac < 1) {
            tmp_b2 = false;
            if (local_24ac == (uint *)0x0) goto LAB_000d9616;
            tmp_pu26 = (uint *)((int)local_24ac + (int)tmp_pu25);
            local_24ac = (uint *)0x0;
            if (-1 < (int)tmp_pu26) {
              local_24ac = tmp_pu26;
            }
          }
          else {
            local_24ac = (uint *)((int)local_24ac + -1);
          }
        }
        else {
          tmp_i27 = Q_stricmp(&local_2471,"prev");
          if (tmp_i27 == 0) {
            local_24ac = (uint *)((&lastViewed_13465)[local_2490] + -0x1e);
            goto LAB_000d94e3;
          }
          local_24ac = (uint *)strtol(&local_2471,(char **)0x0,10);
          if ((int)local_24ac < 0x400) goto LAB_000d94e3;
          local_24ac = (uint *)0x3fe;
        }
        tmp_b2 = false;
        if ((int)tmp_pu25 < (int)local_24ac) {
          tmp_u7 = va("^xshowbans: ^9there are only ^g%d ^9active bans!\n",tmp_pu25);
          if (param_1 == 0) {
            DecolorString(tmp_u7,&local_141c);
            tmp_u7 = va(&g_unk_0026fe3c,&local_141c);
            G_Printf(tmp_u7);
            return 0;
          }
          tmp_pc13 = (char *)&local_141c;
          Q_strncpyz(tmp_pc13,tmp_u7,0x400);
          tmp_i4 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
          while (tmp_c23 = *tmp_pc13, tmp_pc8 = tmp_pc13, tmp_c23 != '\0') {
            while (tmp_c23 != '\n') {
              tmp_pc8 = tmp_pc8 + 1;
              tmp_c23 = *tmp_pc8;
              if (tmp_c23 == '\0') goto LAB_000d9577;
            }
            *tmp_pc8 = '\0';
            tmp_u7 = va("chat \"%s\" -2",tmp_pc13);
            trap_SendServerCommand(tmp_i4,tmp_u7);
            tmp_pc13 = tmp_pc8 + 1;
          }
LAB_000d9577:
          tmp_u7 = va("chat \"%s\" -2",tmp_pc13);
          trap_SendServerCommand(tmp_i4,tmp_u7);
          return 0;
        }
        goto LAB_000d9616;
      }
      tmp_i27 = Q_stricmp(&local_2471,"find");
      if (tmp_i27 == 0) {
        if (tmp_i4 == 2) {
          tmp_pc13 = 
          "^9usage : ^g!showbans find <match> ^7\n^9        (shows banned players matching <match>)\n"
          ;
          goto LAB_000da791;
        }
        if (Bans == 0) {
          tmp_pu25 = (uint *)0x0;
          local_2488 = (uint *)0x1;
          local_24c4 = 1;
        }
        else {
          local_24cc = (uint *)0x0;
          tmp_i27 = Bans;
          tmp_i5 = 0;
          do {
            tmp_i27 = *(int *)(tmp_i27 + 0x48c);
            if ((tmp_i27 == 0) || (tmp_i27 != local_2478 && -1 < tmp_i27 - local_2478)) {
              tmp_pc13 = (char *)Q_strlwr(local_2450);
              tmp_pc8 = (char *)Q_strlwr(*(uint32_t *)((int)&Bans + tmp_i5));
              tmp_pc13 = strstr(tmp_pc8,tmp_pc13);
              if (tmp_pc13 != (char *)0x0) {
                local_24cc = (uint *)((int)local_24cc + 1);
                *(uint32_t *)((int)local_24c8 + tmp_i5) = 1;
              }
            }
            tmp_i27 = *(int *)((int)&g_unk_02df1044 + tmp_i5);
            tmp_i5 = tmp_i5 + 4;
          } while (tmp_i27 != 0);
          local_24c4 = 1;
          local_2488 = (uint *)((int)local_24cc / 0x1e + 1);
          tmp_pu25 = local_24cc;
        }
      }
      else {
        tmp_i27 = Q_stricmp(&local_2471,"banner");
        if (tmp_i27 == 0) {
          if (tmp_i4 == 2) {
            tmp_pc13 = 
            "^9usage : ^g!showbans ^9banner <match> [start]^7\n^9        (shows bans made by admins matching <match>)\n"
            ;
            goto LAB_000da791;
          }
          if (Bans == 0) {
            local_2488 = (uint *)0x1;
            tmp_pu25 = (uint *)0x0;
            local_24c4 = 2;
          }
          else {
            tmp_pu25 = (uint *)0x0;
            tmp_i27 = Bans;
            tmp_i5 = 0;
            do {
              tmp_i27 = *(int *)(tmp_i27 + 0x48c);
              if ((tmp_i27 == 0) || (tmp_i27 != local_2478 && -1 < tmp_i27 - local_2478)) {
                tmp_pc13 = (char *)Q_strlwr(local_2450);
                tmp_pc8 = (char *)Q_strlwr(*(int *)((int)&Bans + tmp_i5) + 0x490);
                tmp_pc13 = strstr(tmp_pc8,tmp_pc13);
                if (tmp_pc13 != (char *)0x0) {
                  tmp_pu25 = (uint *)((int)tmp_pu25 + 1);
                  *(uint32_t *)((int)local_24c8 + tmp_i5) = 1;
                }
              }
              tmp_i27 = *(int *)((int)&g_unk_02df1044 + tmp_i5);
              tmp_i5 = tmp_i5 + 4;
            } while (tmp_i27 != 0);
            local_24c4 = 2;
            local_2488 = (uint *)((int)tmp_pu25 / 0x1e + 1);
          }
        }
        else {
          tmp_i27 = Q_stricmp(&local_2471,"reason");
          if (tmp_i27 != 0) {
            tmp_pc13 = 
            "^9usage : ^g!showbans [start|find <match>|banner <match>|reason <match>]^7\n^9        (displays current list of active bans, filtered by argument criteria)\n"
            ;
LAB_000da791:
            G_shrubbot_print_chat(param_1,tmp_pc13);
            return 0;
          }
          if (tmp_i4 == 2) {
            tmp_pc13 = 
            "^9usage : ^g!showbans ^9reason <match>^7 \n^9        (shows bans with reasons matching <match>)\n"
            ;
            goto LAB_000da791;
          }
          if (Bans == 0) {
            local_2488 = (uint *)0x1;
            tmp_pu25 = (uint *)0x0;
            local_24c4 = 3;
          }
          else {
            tmp_pu25 = (uint *)0x0;
            tmp_i27 = Bans;
            tmp_i5 = 0;
            do {
              tmp_i27 = *(int *)(tmp_i27 + 0x48c);
              if ((tmp_i27 == 0) || (tmp_i27 != local_2478 && -1 < tmp_i27 - local_2478)) {
                tmp_pc13 = (char *)Q_strlwr(local_2450);
                tmp_pc8 = (char *)Q_strlwr(*(int *)((int)&Bans + tmp_i5) + 0x57);
                tmp_pc13 = strstr(tmp_pc8,tmp_pc13);
                if (tmp_pc13 != (char *)0x0) {
                  tmp_pu25 = (uint *)((int)tmp_pu25 + 1);
                  *(uint32_t *)((int)local_24c8 + tmp_i5) = 1;
                }
              }
              tmp_i27 = *(int *)((int)&g_unk_02df1044 + tmp_i5);
              tmp_i5 = tmp_i5 + 4;
            } while (tmp_i27 != 0);
            local_24c4 = 3;
            local_2488 = (uint *)((int)tmp_pu25 / 0x1e + 1);
          }
        }
      }
      local_24a4 = (uint *)((int)local_24ac + 0x1e);
      tmp_i27 = (&Bans)[(int)local_24ac];
      if (tmp_i27 == 0) goto LAB_000da0bb;
      local_24c8 = local_24c8 + (int)local_24ac;
      tmp_pi24 = &g_unk_02df1044 + (int)local_24ac;
      local_24cc = (uint *)0x0;
      local_24bc = 1;
      local_24a8 = 1;
      do {
        local_181c[0] = 0;
        tmp_u20 = 0;
        do {
          tmp_u21 = tmp_u20;
          *(uint32_t *)((int)local_181c + tmp_u21 + 4) = 0;
          *(uint32_t *)((int)local_181c + tmp_u21 + 8) = 0;
          tmp_u20 = tmp_u21 + 8;
        } while (tmp_u21 + 8 < 0x3f8);
        *(uint32_t *)((int)local_181c + tmp_u21 + 0xc) = 0;
        local_141c = 0;
        tmp_u20 = 0;
        do {
          tmp_u21 = tmp_u20;
          *(uint32_t *)((int)local_1418 + tmp_u21) = 0;
          *(uint32_t *)((int)local_1418 + tmp_u21 + 4) = 0;
          tmp_u20 = tmp_u21 + 8;
        } while (tmp_u21 + 8 < 0x3f8);
        *(uint32_t *)((int)local_1418 + tmp_u21 + 8) = 0;
        if (*local_24c8 != 0) {
          DecolorString(tmp_i27,local_181c);
          tmp_pu26 = local_181c;
          do {
            tmp_pu15 = tmp_pu26;
            tmp_u21 = *tmp_pu15 + 0xfefefeff & ~*tmp_pu15;
            tmp_u20 = tmp_u21 & 0x80808080;
            tmp_pu26 = tmp_pu15 + 1;
          } while (tmp_u20 == 0);
          if ((tmp_u21 & 0x8080) == 0) {
            tmp_pu26 = (uint *)((int)tmp_pu15 + 6);
            tmp_u20 = tmp_u20 >> 0x10;
          }
          DecolorString(tmp_pi24[-1] + 0x490,&local_141c);
          tmp_pu15 = &local_141c;
          do {
            tmp_pu19 = tmp_pu15;
            tmp_u22 = *tmp_pu19 + 0xfefefeff & ~*tmp_pu19;
            tmp_u21 = tmp_u22 & 0x80808080;
            tmp_pu15 = tmp_pu19 + 1;
          } while (tmp_u21 == 0);
          if ((tmp_u22 & 0x8080) == 0) {
            tmp_pu15 = (uint *)((int)tmp_pu19 + 6);
            tmp_u21 = tmp_u21 >> 0x10;
          }
          tmp_i27 = (int)tmp_pu15 +
                   ((-3 - (uint)CARRY1((byte)tmp_u21,(byte)tmp_u21)) - (int)&local_141c);
          tmp_pu15 = local_181c;
          if (local_24a8 <
              (int)((int)tmp_pu26 +
                   ((-3 - (uint)CARRY1((byte)tmp_u20,(byte)tmp_u20)) - (int)local_181c))) {
            do {
              tmp_pu26 = tmp_pu15;
              tmp_u21 = *tmp_pu26 + 0xfefefeff & ~*tmp_pu26;
              tmp_u20 = tmp_u21 & 0x80808080;
              tmp_pu15 = tmp_pu26 + 1;
            } while (tmp_u20 == 0);
            if ((tmp_u21 & 0x8080) == 0) {
              tmp_pu15 = (uint *)((int)tmp_pu26 + 6);
              tmp_u20 = tmp_u20 >> 0x10;
            }
            local_24a8 = (int)tmp_pu15 +
                         ((-3 - (uint)CARRY1((byte)tmp_u20,(byte)tmp_u20)) - (int)local_181c);
          }
          if (tmp_i27 <= local_24bc) {
            tmp_i27 = local_24bc;
          }
          local_24cc = (uint *)((int)local_24cc + 1);
          local_24bc = tmp_i27;
        }
        tmp_i27 = *tmp_pi24;
        tmp_pi24 = tmp_pi24 + 1;
        local_24c8 = local_24c8 + 1;
      } while (((int)local_24cc < 0x1e) && (tmp_i27 != 0));
      tmp_b2 = true;
LAB_000d982f:
      tmp_i27 = (&Bans)[(int)local_24ac];
      bigTextBuffer = 0;
      tmp_pu26 = local_24ac;
      if (tmp_i27 != 0) {
        tmp_pi24 = &Bans + (int)local_24ac;
        local_24c8 = (int *)0x0;
        tmp_pu15 = local_24ac;
        do {
          tmp_pu26 = (uint *)((int)tmp_pu15 + 1);
          tmp_i5 = *(int *)(tmp_i27 + 0x48c);
          if (((tmp_i5 == 0) || (tmp_i5 != local_2478 && -1 < tmp_i5 - local_2478)) &&
             ((local_24c4 == 0 || (local_1418[(int)tmp_pu15 + 0xff] != 0)))) {
            local_2466 = 0;
            tmp_b28 = *(byte *)(tmp_i27 + 0x457);
            if ((tmp_b28 & 0xdf) != 0) {
              local_2465 = 0;
              tmp_b1 = *(byte *)(tmp_i27 + 0x458);
              local_2466 = tmp_b28;
              if ((tmp_b1 & 0xdf) != 0) {
                local_2464 = 0;
                tmp_b28 = *(byte *)(tmp_i27 + 0x459);
                local_2465 = tmp_b1;
                if ((tmp_b28 & 0xdf) != 0) {
                  local_2463 = 0;
                  tmp_b1 = *(byte *)(tmp_i27 + 0x45a);
                  local_2464 = tmp_b28;
                  if ((tmp_b1 & 0xdf) != 0) {
                    local_2462 = 0;
                    tmp_b28 = *(byte *)(tmp_i27 + 0x45b);
                    local_2463 = tmp_b1;
                    if ((tmp_b28 & 0xdf) != 0) {
                      local_2461 = 0;
                      tmp_b1 = *(byte *)(tmp_i27 + 0x45c);
                      local_2462 = tmp_b28;
                      if ((tmp_b1 & 0xdf) != 0) {
                        local_2460 = 0;
                        tmp_b28 = *(byte *)(tmp_i27 + 0x45d);
                        local_2461 = tmp_b1;
                        if ((tmp_b28 & 0xdf) != 0) {
                          local_245f = 0;
                          tmp_b1 = *(byte *)(tmp_i27 + 0x45e);
                          local_2460 = tmp_b28;
                          if ((tmp_b1 & 0xdf) != 0) {
                            local_245e = 0;
                            tmp_b28 = *(byte *)(tmp_i27 + 0x45f);
                            local_245f = tmp_b1;
                            if ((tmp_b28 & 0xdf) != 0) {
                              local_245d = 0;
                              local_245e = tmp_b28;
                              if ((*(byte *)(tmp_i27 + 0x460) & 0xdf) != 0) {
                                local_245c = 0;
                                local_245d = *(byte *)(tmp_i27 + 0x460);
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
            G_shrubbot_duration(tmp_i5 - local_2478,local_241c,0x400);
            DecolorString(*tmp_pi24,local_2440);
            tmp_pu15 = local_2440;
            do {
              tmp_pu19 = tmp_pu15;
              tmp_u21 = *tmp_pu19 + 0xfefefeff & ~*tmp_pu19;
              tmp_u20 = tmp_u21 & 0x80808080;
              tmp_pu15 = tmp_pu19 + 1;
            } while (tmp_u20 == 0);
            if ((tmp_u21 & 0x8080) == 0) {
              tmp_pu15 = (uint *)((int)tmp_pu19 + 6);
              tmp_u20 = tmp_u20 >> 0x10;
            }
            DecolorString(*tmp_pi24 + 0x490,local_2440);
            tmp_pu19 = local_2440;
            do {
              tmp_pu14 = tmp_pu19;
              tmp_u22 = *tmp_pu14 + 0xfefefeff & ~*tmp_pu14;
              tmp_u21 = tmp_u22 & 0x80808080;
              tmp_pu19 = tmp_pu14 + 1;
            } while (tmp_u21 == 0);
            if ((tmp_u22 & 0x8080) == 0) {
              tmp_pu19 = (uint *)((int)tmp_pu14 + 6);
              tmp_u21 = tmp_u21 >> 0x10;
            }
            DecolorString(*tmp_pi24 + 0x57,local_1c1c);
            tmp_pc13 = (char *)*tmp_pi24;
            tmp_s11 = strlen(tmp_pc13 + 0x490);
            tmp_s12 = strlen(tmp_pc13);
            Com_sprintf(local_201c,0x400,
                        "^g%%i ^9| ^7%%-%ds ^9| ^g%%-8s ^9| ^g%%-8s ^9| ^7%%-%ds ^9| ^g%%-9s ^9| ^g%%s\n"
                        ,tmp_s12 + (local_24a8 -
                                  ((int)tmp_pu15 +
                                  ((-3 - (uint)CARRY1((byte)tmp_u20,(byte)tmp_u20)) - (int)local_2440)
                                  )),
                        tmp_s11 + (local_24bc -
                                 ((int)tmp_pu19 +
                                 ((-3 - (uint)CARRY1((byte)tmp_u21,(byte)tmp_u21)) - (int)local_2440))
                                 ));
            tmp_i27 = *tmp_pi24;
            tmp_u7 = va(local_201c,tmp_pu26,tmp_i27,tmp_i27 + 0x3c,&local_2466,tmp_i27 + 0x490,local_241c
                       ,local_1c1c);
            if (param_1 == 0) {
              DecolorString(tmp_u7,&local_141c);
              tmp_pu15 = &local_141c;
              do {
                tmp_pu19 = tmp_pu15;
                tmp_u21 = *tmp_pu19 + 0xfefefeff & ~*tmp_pu19;
                tmp_u20 = tmp_u21 & 0x80808080;
                tmp_pu15 = tmp_pu19 + 1;
              } while (tmp_u20 == 0);
              if ((tmp_u21 & 0x8080) == 0) {
                tmp_pu15 = (uint *)((int)tmp_pu19 + 6);
                tmp_u20 = tmp_u20 >> 0x10;
              }
              tmp_s11 = strlen(&bigTextBuffer);
              if (0xef < (int)tmp_pu15 +
                         tmp_s11 + ((-3 - (uint)CARRY1((byte)tmp_u20,(byte)tmp_u20)) - (int)&local_141c
                                  )) {
                G_shrubbot_print(0,&bigTextBuffer);
                bigTextBuffer = 0;
              }
              Q_strcat(&bigTextBuffer,100000,&local_141c);
            }
            else {
              Q_strcat(&bigTextBuffer,100000,tmp_u7);
            }
            local_24c8 = (int *)((int)local_24c8 + 1);
          }
          tmp_pi24 = tmp_pi24 + 1;
          tmp_i27 = (&Bans)[(int)tmp_pu26];
        } while ((tmp_i27 != 0) && (tmp_pu15 = tmp_pu26, (int)local_24c8 < 0x1e));
      }
    }
    if (local_24c4 == 1) {
      tmp_pu18 = &g_unk_0024e6ea;
      if (local_2488 == (uint *)0x1) {
        tmp_pu18 = &g_unk_0026ea14;
      }
      tmp_pu15 = local_2450;
      tmp_pu19 = (uint *)va("^xshowbans: ^g%i ^9bans found for players matching ^g%s ^9(%i Page%s)\n"
                           ,tmp_pu25,tmp_pu15,local_2488,tmp_pu18);
      if (param_1 != 0) goto LAB_000da30f;
LAB_000da4ca:
      G_shrubbot_buffer_print_part_15();
      tmp_pu19 = tmp_pu15;
      tmp_pu15 = local_2488;
    }
    else {
      if (local_24c4 == 2) {
        tmp_pu18 = &g_unk_0024e6ea;
        if (local_2488 == (uint *)0x1) {
          tmp_pu18 = &g_unk_0026ea14;
        }
        tmp_pu15 = (uint *)va("^xshowbans: ^g%i ^9bans found for admins matching ^g%s ^9(%i Page%s)\n"
                             ,tmp_pu25,local_2450,local_2488,tmp_pu18);
        tmp_pu19 = tmp_pu15;
        if (param_1 == 0) {
          tmp_pu19 = local_181c;
          DecolorString(tmp_pu15,tmp_pu19);
          tmp_pu15 = tmp_pu19;
          do {
            tmp_pu14 = tmp_pu15;
            tmp_u21 = *tmp_pu14 + 0xfefefeff & ~*tmp_pu14;
            tmp_u20 = tmp_u21 & 0x80808080;
            tmp_pu15 = tmp_pu14 + 1;
          } while (tmp_u20 == 0);
          if ((tmp_u21 & 0x8080) == 0) {
            tmp_pu15 = (uint *)((int)tmp_pu14 + 6);
            tmp_u20 = tmp_u20 >> 0x10;
          }
          tmp_s11 = strlen(&bigTextBuffer);
          if (0xef < (int)tmp_pu15 +
                     tmp_s11 + ((-3 - (uint)CARRY1((byte)tmp_u20,(byte)tmp_u20)) - (int)tmp_pu19)) {
            DecolorString(&bigTextBuffer,&local_141c);
            G_Printf(&local_141c);
            bigTextBuffer = 0;
          }
        }
      }
      else {
        if (local_24c4 != 3) goto LAB_000da101;
        tmp_pu18 = &g_unk_0024e6ea;
        if (local_2488 == (uint *)0x1) {
          tmp_pu18 = &g_unk_0026ea14;
        }
        tmp_pu15 = local_2450;
        tmp_pu19 = (uint *)va("^xshowbans: ^g%i ^9bans found with reasons matching ^g%s ^9(%i Page%s)\n"
                             ,tmp_pu25,tmp_pu15,local_2488,tmp_pu18);
        if (param_1 == 0) goto LAB_000da4ca;
      }
LAB_000da30f:
      Q_strcat(&bigTextBuffer,100000,tmp_pu19);
      tmp_pu15 = local_2488;
    }
    if ((int)local_24a4 < (int)tmp_pu25) {
      tmp_i27 = (int)local_24ac / 0x1e;
      tmp_pu29 = tmp_pu18;
LAB_000da189:
      tmp_pu18 = (uint8_t *)(tmp_i27 + 2);
      tmp_pu17 = &g_unk_0026ea14;
      if (2 < tmp_i4) {
        tmp_pu17 = (uint8_t *)va(&g_unk_00249b72,local_2450,tmp_pu19,tmp_pu15,tmp_pu29);
      }
      if ((tmp_b2) && (1 < tmp_i4)) {
        tmp_pu16 = (uint8_t *)va(&g_unk_00249b72,&local_2471);
      }
      else {
        tmp_pu16 = &g_unk_0026ea14;
      }
      tmp_pu15 = (uint *)0x245f48;
      tmp_pu25 = (uint *)va("\n          ^9(type !showbans ^g%s%s%s ^9to continue to page ^g%i)\n",
                           tmp_pu16,tmp_pu17,"next",tmp_pu18);
      if (param_1 == 0) {
        tmp_pu19 = local_181c;
        DecolorString(tmp_pu25,tmp_pu19);
        tmp_pu25 = tmp_pu19;
        do {
          tmp_pu14 = tmp_pu25;
          tmp_u21 = *tmp_pu14 + 0xfefefeff & ~*tmp_pu14;
          tmp_u20 = tmp_u21 & 0x80808080;
          tmp_pu25 = tmp_pu14 + 1;
        } while (tmp_u20 == 0);
        if ((tmp_u21 & 0x8080) == 0) {
          tmp_pu25 = (uint *)((int)tmp_pu14 + 6);
          tmp_u20 = tmp_u20 >> 0x10;
        }
        tmp_s11 = strlen(&bigTextBuffer);
        if (0xef < (int)tmp_pu25 +
                   tmp_s11 + ((-3 - (uint)CARRY1((byte)tmp_u20,(byte)tmp_u20)) - (int)tmp_pu19)) {
          DecolorString(&bigTextBuffer,&local_141c);
          G_Printf(&local_141c);
          bigTextBuffer = 0;
        }
        Q_strcat(&bigTextBuffer,100000,tmp_pu19);
        if (local_24c4 == 0) {
          (&lastViewed_13465)[local_2490] = local_24a4;
          goto LAB_000da2b2;
        }
      }
      else {
        Q_strcat(&bigTextBuffer,100000,tmp_pu25);
        tmp_pu19 = tmp_pu25;
        if (local_24c4 == 0) {
          (&lastViewed_13465)[local_2490] = local_24a4;
          goto LAB_000da220;
        }
      }
    }
LAB_000da290:
    tmp_pu25 = tmp_pu19;
    local_24a4 = tmp_pu26;
  }
  (&lastViewed_13465)[local_2490] = local_24a4;
  if (param_1 == 0) {
LAB_000da2b2:
    G_shrubbot_print_part_8();
    return 1;
  }
LAB_000da220:
  tmp_s11 = strlen(&bigTextBuffer);
  if (tmp_s11 < 0x3e9) {
    tmp_u7 = va("print \"%s\"",&bigTextBuffer,tmp_pu25,tmp_pu15,tmp_pu18);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u7);
    return 1;
  }
  nitrox_bigBufferPrint(param_1);
  return 1;
}

uint32_t G_shrubbot_userlist(int param_1,int param_2)
{
  bool tmp_b1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  char *tmp_pc6;
  size_t tmp_s7;
  uint tmp_u8;
  uint tmp_u9;
  uint *tmp_pu10;
  uint *tmp_pu11;
  int *tmp_pi12;
  char *tmp_pc13;
  int local_cac;
  int local_ca8;
  long local_ca0;
  uint local_c9c;
  char local_c87 [11];
  uint8_t local_c7c [20];
  char local_c68 [36];
  char local_c44 [40];
  uint local_c1c [256];
  uint local_81c [256];
  uint local_41c [258];
  uint32_t uStack_14;
  
  uStack_14 = 0xda8d9;
  tmp_i2 = Q_SayArgc();
  tmp_i5 = param_2 + 1;
  tmp_i3 = Q_SayArgc();
  if (tmp_i3 == param_2 + 2) {
    Q_SayArgv(tmp_i5,local_c87,0xb);
    local_c9c = strtol(local_c87,(char **)0x0,10);
    local_ca0 = 0;
LAB_000da92b:
    if (Users != 0) {
      tmp_b1 = (int)local_c9c < 1;
      goto LAB_000da94e;
    }
    tmp_b1 = (int)local_c9c < 1;
    tmp_pu10 = (uint *)0x0;
    local_cac = 0;
  }
  else {
    tmp_i3 = Q_SayArgc();
    if (tmp_i3 <= tmp_i5) {
      local_c9c = (uint)(tmp_i2 == tmp_i5);
      local_ca0 = 0;
      goto LAB_000da92b;
    }
    Q_SayArgv(tmp_i5,local_c7c,0x14);
    tmp_u4 = Q_strlwr(local_c7c);
    tmp_i5 = Q_stricmp(tmp_u4,"name");
    if (tmp_i5 == 0) {
LAB_000db1d9:
      tmp_i5 = Q_SayArgv(param_2 + 2,local_c44,0x28);
      if (tmp_i5 == 0) {
        G_shrubbot_print(param_1,"^1userlist error: ^9Missing argument\n");
        return 0;
      }
    }
    else {
      tmp_u4 = Q_strlwr(local_c7c);
      tmp_i5 = Q_stricmp(tmp_u4,"level");
      if (tmp_i5 == 0) goto LAB_000db1d9;
      tmp_u4 = Q_strlwr(local_c7c);
      tmp_i5 = Q_stricmp(tmp_u4,"ip");
      if (tmp_i5 == 0) goto LAB_000db1d9;
      tmp_u4 = Q_strlwr(local_c7c);
      tmp_i5 = Q_stricmp(tmp_u4,&g_unk_0025280c);
      if (tmp_i5 == 0) goto LAB_000db1d9;
    }
    local_ca0 = strtol(local_c44,(char **)0x0,10);
    tmp_i5 = Q_SayArgc();
    if (param_2 + 3 < tmp_i5) {
      tmp_i5 = Q_SayArgv(param_2 + 3,local_c87,0xb);
      if (tmp_i5 != 0) {
        local_c9c = strtol(local_c87,(char **)0x0,10);
        goto LAB_000da92b;
      }
    }
    if (Users == 0) goto LAB_000db139;
    tmp_b1 = false;
    local_c9c = 1;
LAB_000da94e:
    local_cac = 0;
    tmp_pi12 = &Users;
    do {
      while( true ) {
        tmp_u4 = Q_strlwr(local_c7c);
        tmp_i5 = Q_stricmp(tmp_u4,"name");
        if (tmp_i5 != 0) break;
        SanitizeString(*tmp_pi12 + 0x25,local_c68,1);
        tmp_pc13 = (char *)Q_strlwr(local_c44);
        tmp_pc13 = strstr(local_c68,tmp_pc13);
        local_cac = (local_cac + 1) - (uint)(tmp_pc13 == (char *)0x0);
LAB_000da9b9:
        tmp_pi12 = tmp_pi12 + 1;
        if (*tmp_pi12 == 0) goto LAB_000daa18;
      }
      tmp_u4 = Q_strlwr(local_c7c);
      tmp_i5 = Q_stricmp(tmp_u4,"level");
      if (tmp_i5 != 0) {
        tmp_u4 = Q_strlwr(local_c7c);
        tmp_i5 = Q_stricmp(tmp_u4,"ip");
        if (tmp_i5 == 0) {
          tmp_pc13 = (char *)Q_strlwr(local_c44);
          tmp_pc13 = strstr((char *)(*tmp_pi12 + 0xc62),tmp_pc13);
          local_cac = (local_cac + 1) - (uint)(tmp_pc13 == (char *)0x0);
        }
        else {
          tmp_u4 = Q_strlwr(local_c7c);
          tmp_i5 = Q_stricmp(tmp_u4,&g_unk_0025280c);
          if (tmp_i5 == 0) {
            tmp_pc13 = (char *)Q_strlwr(local_c44);
            tmp_pc13 = strstr((char *)(*tmp_pi12 + 0xc50),tmp_pc13);
            local_cac = (local_cac + 1) - (uint)(tmp_pc13 == (char *)0x0);
          }
          else {
            local_cac = local_cac + 1;
          }
        }
        goto LAB_000da9b9;
      }
      tmp_i5 = *tmp_pi12;
      tmp_pi12 = tmp_pi12 + 1;
      local_cac = local_cac + (uint)(**(int **)(tmp_i5 + 0x4c) == local_ca0);
    } while (*tmp_pi12 != 0);
LAB_000daa18:
    tmp_pu10 = (uint *)((local_cac + 0x13) / 0x14);
  }
  if (((int)local_c9c <= (int)tmp_pu10) && (!tmp_b1)) {
    tmp_u4 = va("^xpage %d/%d (%d matches)\n",local_c9c,tmp_pu10,local_cac);
    tmp_i5 = local_cac;
    G_shrubbot_print(param_1,tmp_u4);
    bigTextBuffer = 0;
    if (Users != 0) {
      tmp_pi12 = &Users;
      local_cac = 0;
      local_ca8 = 0;
      tmp_pc13 = (char *)tmp_pu10;
      do {
        while( true ) {
          tmp_u4 = Q_strlwr(local_c7c);
          tmp_i2 = Q_stricmp(tmp_u4,"name");
          if (tmp_i2 != 0) break;
          tmp_pc13 = (char *)0x1;
          SanitizeString(*tmp_pi12 + 0x25,local_c68,1);
          tmp_pc6 = (char *)Q_strlwr(local_c44);
          tmp_pc6 = strstr(local_c68,tmp_pc6);
          if (tmp_pc6 != (char *)0x0) {
            if (local_cac / 0x14 + 1U == local_c9c) {
              tmp_i2 = *tmp_pi12;
              tmp_pu11 = local_c1c;
              tmp_i5 = tmp_i2 + 0x1c;
              Com_sprintf(tmp_pu11,0x400,"^g%s ^x%3i ^7%s\n",tmp_i5,**(uint32_t **)(tmp_i2 + 0x4c),
                          tmp_i2 + 0x25);
              if (param_1 == 0) {
                tmp_pc13 = (char *)local_41c;
                DecolorString(tmp_pu11,tmp_pc13);
                tmp_pu10 = (uint *)tmp_pc13;
                do {
                  tmp_pu11 = tmp_pu10;
                  tmp_u9 = *tmp_pu11 + 0xfefefeff & ~*tmp_pu11;
                  tmp_u8 = tmp_u9 & 0x80808080;
                  tmp_pu10 = tmp_pu11 + 1;
                } while (tmp_u8 == 0);
                if ((tmp_u9 & 0x8080) == 0) {
                  tmp_pu10 = (uint *)((int)tmp_pu11 + 6);
                  tmp_u8 = tmp_u8 >> 0x10;
                }
                tmp_s7 = strlen(&bigTextBuffer);
                if ((char *)0xef <
                    (char *)((int)tmp_pu10 +
                            tmp_s7 + ((-3 - (uint)CARRY1((byte)tmp_u8,(byte)tmp_u8)) - (int)tmp_pc13)))
                {
                  G_shrubbot_print(0,&bigTextBuffer);
                  bigTextBuffer = 0;
                }
                Q_strcat(&bigTextBuffer,100000,tmp_pc13);
              }
              else {
LAB_000dae7a:
                Q_strcat(&bigTextBuffer,100000,tmp_pu11);
                tmp_pc13 = (char *)tmp_pu11;
              }
            }
LAB_000dab1f:
            local_cac = local_cac + 1;
          }
LAB_000dab23:
          tmp_pi12 = tmp_pi12 + 1;
          local_ca8 = local_ca8 + 1;
          tmp_pu10 = (uint *)tmp_pc13;
          if (*tmp_pi12 == 0) goto LAB_000db012;
        }
        tmp_u4 = Q_strlwr(local_c7c);
        tmp_i2 = Q_stricmp(tmp_u4,"level");
        if (tmp_i2 == 0) {
          tmp_i2 = *tmp_pi12;
          if (**(int **)(tmp_i2 + 0x4c) == local_ca0) {
            if (local_cac / 0x14 + 1U == local_c9c) {
              tmp_i5 = tmp_i2 + 0x1c;
              Com_sprintf(local_c1c,0x400,"^g%s ^x%3i ^7%s\n",tmp_i5,local_ca0,tmp_i2 + 0x25);
              if (param_1 == 0) {
                tmp_pu10 = local_81c;
                DecolorString(local_c1c,tmp_pu10);
                do {
                  tmp_u8 = *tmp_pu10;
                  tmp_pu10 = tmp_pu10 + 1;
                  tmp_u8 = tmp_u8 + 0xfefefeff & ~tmp_u8 & 0x80808080;
                } while (tmp_u8 == 0);
LAB_000dadb0:
                tmp_pu11 = local_81c;
                if ((tmp_u8 & 0x8080) == 0) {
                  tmp_pu10 = (uint *)((int)tmp_pu10 + 2);
                  tmp_u8 = tmp_u8 >> 0x10;
                }
                tmp_s7 = strlen(&bigTextBuffer);
                if (0xef < (int)tmp_pu10 +
                           tmp_s7 + ((-3 - (uint)CARRY1((byte)tmp_u8,(byte)tmp_u8)) - (int)tmp_pu11)) {
                  DecolorString(&bigTextBuffer,local_41c);
                  G_Printf(local_41c);
                  bigTextBuffer = 0;
                }
                goto LAB_000dae7a;
              }
LAB_000dabf4:
              tmp_pc13 = (char *)local_c1c;
              Q_strcat(&bigTextBuffer,100000,tmp_pc13);
            }
            goto LAB_000dab1f;
          }
          goto LAB_000dab23;
        }
        tmp_u4 = Q_strlwr(local_c7c);
        tmp_i2 = Q_stricmp(tmp_u4,"ip");
        if (tmp_i2 == 0) {
          tmp_i2 = *tmp_pi12;
          tmp_pc6 = strstr((char *)(tmp_i2 + 0xc62),local_c44);
          if (tmp_pc6 != (char *)0x0) {
            if (local_cac / 0x14 + 1U == local_c9c) {
              tmp_i5 = tmp_i2 + 0x1c;
              Com_sprintf(local_c1c,0x400,"^g%s ^x%3i %15s ^7%s\n",tmp_i5,
                          **(uint32_t **)(tmp_i2 + 0x4c),(char *)(tmp_i2 + 0xc62),tmp_i2 + 0x25);
              if (param_1 == 0) {
                tmp_pu10 = local_81c;
                DecolorString(local_c1c,tmp_pu10);
                do {
                  tmp_u8 = *tmp_pu10;
                  tmp_pu10 = tmp_pu10 + 1;
                  tmp_u8 = tmp_u8 + 0xfefefeff & ~tmp_u8 & 0x80808080;
                } while (tmp_u8 == 0);
                goto LAB_000dadb0;
              }
              goto LAB_000dabf4;
            }
            goto LAB_000dab1f;
          }
          goto LAB_000dab23;
        }
        tmp_u4 = Q_strlwr(local_c7c);
        tmp_i2 = Q_stricmp(tmp_u4,&g_unk_0025280c);
        if (tmp_i2 == 0) {
          tmp_i2 = *tmp_pi12;
          tmp_pc6 = strstr((char *)(tmp_i2 + 0xc50),local_c44);
          if (tmp_pc6 != (char *)0x0) {
            if (local_cac / 0x14 + 1U == local_c9c) {
              tmp_i5 = tmp_i2 + 0x1c;
              tmp_pu11 = local_c1c;
              tmp_pc13 = "^g%s ^x%3i %17s ^7%s\n";
              Com_sprintf(tmp_pu11,0x400,"^g%s ^x%3i %17s ^7%s\n",tmp_i5,
                          **(uint32_t **)(tmp_i2 + 0x4c),(char *)(tmp_i2 + 0xc50),tmp_i2 + 0x25);
              if (param_1 != 0) goto LAB_000dae7a;
              G_shrubbot_buffer_print_part_15();
            }
            goto LAB_000dab1f;
          }
          goto LAB_000dab23;
        }
        if (local_ca8 / 0x14 + 1U != local_c9c) goto LAB_000dab23;
        tmp_i2 = *tmp_pi12;
        tmp_i5 = tmp_i2 + 0x1c;
        tmp_pu10 = local_c1c;
        Com_sprintf(tmp_pu10,0x400,"^g%s ^x%3i ^7%s\n",tmp_i5,**(uint32_t **)(tmp_i2 + 0x4c),
                    tmp_i2 + 0x25);
        if (param_1 == 0) {
          tmp_pc13 = (char *)local_81c;
          DecolorString(tmp_pu10,tmp_pc13);
          tmp_pu10 = (uint *)tmp_pc13;
          do {
            tmp_pu11 = tmp_pu10;
            tmp_u9 = *tmp_pu11 + 0xfefefeff & ~*tmp_pu11;
            tmp_u8 = tmp_u9 & 0x80808080;
            tmp_pu10 = tmp_pu11 + 1;
          } while (tmp_u8 == 0);
          if ((tmp_u9 & 0x8080) == 0) {
            tmp_pu10 = (uint *)((int)tmp_pu11 + 6);
            tmp_u8 = tmp_u8 >> 0x10;
          }
          tmp_s7 = strlen(&bigTextBuffer);
          if ((char *)0xef <
              (char *)((int)tmp_pu10 +
                      tmp_s7 + ((-3 - (uint)CARRY1((byte)tmp_u8,(byte)tmp_u8)) - (int)tmp_pc13))) {
            DecolorString(&bigTextBuffer,local_41c);
            G_Printf(local_41c);
            bigTextBuffer = 0;
          }
          Q_strcat(&bigTextBuffer,100000,tmp_pc13);
          goto LAB_000dab23;
        }
        tmp_pi12 = tmp_pi12 + 1;
        Q_strcat(&bigTextBuffer,100000,tmp_pu10);
        local_ca8 = local_ca8 + 1;
        tmp_pc13 = (char *)tmp_pu10;
      } while (*tmp_pi12 != 0);
    }
LAB_000db012:
    if (param_1 == 0) {
      DecolorString(&bigTextBuffer,local_41c);
      G_Printf(local_41c);
      return 1;
    }
    tmp_s7 = strlen(&bigTextBuffer);
    if (tmp_s7 < 0x3e9) {
      tmp_u4 = va("print \"%s\"",&bigTextBuffer,tmp_pu10,tmp_i5);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
      return 1;
    }
    nitrox_bigBufferPrint(param_1);
    return 1;
  }
LAB_000db139:
  G_shrubbot_print(param_1,"^1userlist error: ^9Invalid page\n");
  return 0;
}

void G_shrubbot_buffer_begin(void)
{
  bigTextBuffer = 0;
  return;
}

void G_shrubbot_buffer_end(int param_1)
{
  size_t tmp_s1;
  uint32_t tmp_u2;
  
  if (param_1 == 0) {
    G_shrubbot_print_part_8();
    return;
  }
  tmp_s1 = strlen(&bigTextBuffer);
  if (tmp_s1 < 0x3e9) {
    tmp_u2 = va("print \"%s\"",&bigTextBuffer);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u2);
    return;
  }
  nitrox_bigBufferPrint();
  return;
}

uint32_t G_shrubbot_help(int param_1,int param_2)
{
  char tmp_c1;
  char *tmp_pc2;
  int tmp_i3;
  int tmp_i4;
  int *tmp_pi5;
  uint32_t tmp_u6;
  uint tmp_u7;
  uint8_t *tmp_pu8;
  char *tmp_pc9;
  int tmp_i10;
  size_t tmp_s11;
  uint32_t *tmp_pu12;
  uint8_t **tmp_ppu13;
  uint32_t *local_5c;
  uint32_t *local_58;
  int local_54;
  uint8_t *local_50;
  uint8_t local_30 [28];
  uint32_t uStack_14;
  
  uStack_14 = 0xdb579;
  tmp_i3 = Q_SayArgc();
  if (param_2 + 1 < tmp_i3) {
    tmp_pc9 = "readconfig";
    Q_SayArgv(param_2 + 1,local_30,0x14);
    tmp_ppu13 = &g_ptr_s_time_002528fd_0x18_002b3ab4;
    bigTextBuffer = 0;
    local_5c = (uint32_t *)0x0;
    do {
      tmp_i3 = Q_stricmp(local_30,tmp_pc9);
      if (tmp_i3 == 0) {
        tmp_i3 = nitrox_CheckCommandPermission(param_1,(&g_unk_002b3aa4)[(int)local_5c * 5]);
        if (tmp_i3 == 0) {
          tmp_u6 = va("^1help error: ^9You dont have the permission to use \'^g%s^9\'\n",tmp_pc9);
          if (param_1 != 0) {
            Q_strcat(&bigTextBuffer,100000,tmp_u6);
            return 0;
          }
          G_shrubbot_buffer_print_part_15();
          return 0;
        }
        tmp_u6 = va("^xhelp: ^9help for \'^g%s^9\':\n",tmp_pc9);
        if (param_1 == 0) {
          G_shrubbot_buffer_print_part_15();
          va("^xFunction: ^9%s\n",
             (&g_ptr_s_Reloads_levels_and_commands_data_002b3aac)[(int)local_5c * 5]);
          G_shrubbot_buffer_print_part_15();
          va("^xSyntax: ^g!%s %s\n",tmp_pc9,(&g_ptr_DAT_002b3ab0)[(int)local_5c * 5]);
          goto LAB_000dbaf7;
        }
        Q_strcat(&bigTextBuffer,100000,tmp_u6);
        tmp_u6 = va("^xFunction: ^9%s\n",
                   (&g_ptr_s_Reloads_levels_and_commands_data_002b3aac)[(int)local_5c * 5]);
        Q_strcat(&bigTextBuffer,100000,tmp_u6);
        tmp_u6 = va("^xSyntax: ^g!%s %s\n",tmp_pc9,(&g_ptr_DAT_002b3ab0)[(int)local_5c * 5]);
        Q_strcat(&bigTextBuffer,100000,tmp_u6);
        tmp_u7 = strlen(&bigTextBuffer);
        goto joined_r0x000dbbbb;
      }
      tmp_pc9 = *tmp_ppu13;
      tmp_ppu13 = tmp_ppu13 + 5;
      local_5c = (uint32_t *)((int)local_5c + 1);
    } while (*tmp_pc9 != '\0');
    tmp_i3 = 0;
    tmp_pc9 = CustomCommands;
    while( true ) {
      if (tmp_pc9 == (char *)0x0) {
        tmp_u6 = va("^1help error: ^9no help found for \'^g%s^9\'^7\n",local_30);
        if (param_1 == 0) {
          G_shrubbot_buffer_print_part_15();
          G_shrubbot_print_part_8();
          return 0;
        }
        Q_strcat(&bigTextBuffer,100000,tmp_u6);
        tmp_s11 = strlen(&bigTextBuffer);
        if (tmp_s11 < 0x3e9) {
          tmp_u6 = va("print \"%s\"",&bigTextBuffer);
          trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
          return 0;
        }
        nitrox_bigBufferPrint(param_1);
        return 0;
      }
      tmp_i4 = Q_stricmp(local_30,tmp_pc9);
      if (tmp_i4 == 0) break;
      tmp_i3 = tmp_i3 + 1;
      tmp_pc9 = (&CustomCommands)[tmp_i3];
    }
    tmp_u6 = (&CustomCommands)[tmp_i3];
    tmp_i4 = 0;
    if (g_unk_02af58b8 == 0) {
      if (param_1 == 0) goto LAB_000dbea5;
    }
    else {
      if (param_1 == 0) {
LAB_000dbea5:
        va("^xhelp: ^9help for \'^g%s^9\':\n",tmp_u6);
LAB_000dbebb:
        G_shrubbot_buffer_print_part_15();
        va("^xDescription: ^9%s\n",(int)(&CustomCommands)[tmp_i3] + 0x440);
        G_shrubbot_buffer_print_part_15();
        va("^xSyntax: ^g!%s\n",(&CustomCommands)[tmp_i3]);
        G_shrubbot_buffer_print_part_15();
LAB_000dbe8b:
        G_shrubbot_buffer_end(param_1);
        return 1;
      }
      if (*(int *)(param_1 + 0x5e8) != 0) {
        tmp_i4 = GetUserPointer(param_1);
        tmp_i4 = **(int **)(tmp_i4 + 0x4c);
      }
    }
    if (CustomCommands == (char *)0x0) {
      tmp_u6 = va("^1help error: ^9you have no permission to use \'^g%s^9\'\n",
                 (&CustomCommands)[tmp_i3]);
    }
    else {
      tmp_pc9 = CustomCommands;
      local_5c = &g_unk_02db0e44;
      do {
        tmp_i10 = Q_stricmp(tmp_u6,tmp_pc9);
        if (tmp_i10 == 0) {
          tmp_i10 = *(int *)(local_5c[-1] + 0x840);
          if (tmp_i10 != -1) {
            if (tmp_i10 == tmp_i4) {
LAB_000dbdf0:
              tmp_u6 = va("^xhelp: ^9help for \'^g%s^9\':\n",(&CustomCommands)[tmp_i3]);
              if (param_1 == 0) goto LAB_000dbebb;
              Q_strcat(&bigTextBuffer,100000,tmp_u6);
              tmp_u6 = va("^xDescription: ^9%s\n",(int)(&CustomCommands)[tmp_i3] + 0x440);
              Q_strcat(&bigTextBuffer,100000,tmp_u6);
              tmp_u6 = va("^xSyntax: ^g!%s\n",(&CustomCommands)[tmp_i3]);
              Q_strcat(&bigTextBuffer,100000,tmp_u6);
              goto LAB_000dbe8b;
            }
            tmp_pi5 = (int *)(local_5c[-1] + 0x844);
            while (tmp_i10 = *tmp_pi5, tmp_i10 != -1) {
              tmp_pi5 = tmp_pi5 + 1;
              if (tmp_i10 == tmp_i4) goto LAB_000dbdf0;
            }
          }
        }
        tmp_pc9 = (char *)*local_5c;
        local_5c = local_5c + 1;
      } while (tmp_pc9 != (char *)0x0);
      tmp_u6 = va("^1help error: ^9you have no permission to use \'^g%s^9\'\n",
                 (&CustomCommands)[tmp_i3]);
      if (param_1 == 0) {
        G_shrubbot_buffer_print_part_15();
        goto LAB_000dbd09;
      }
    }
    Q_strcat(&bigTextBuffer,100000,tmp_u6);
LAB_000dbd09:
    G_shrubbot_buffer_end(param_1);
    return 0;
  }
  tmp_pu8 = &g_unk_0026ea14;
  tmp_pu12 = &g_unk_002b3aa4;
  local_54 = 0;
  tmp_pc9 = "readconfig";
  local_5c = (uint32_t *)0x0;
  tmp_i3 = 0;
  local_58 = (uint32_t *)tmp_pu8;
  do {
    tmp_i4 = nitrox_CheckCommandPermission(param_1,*tmp_pu12);
    if (tmp_i4 == 0) {
      if (local_5c == (uint32_t *)0x6) goto LAB_000db63a;
LAB_000db5e7:
      tmp_pc9 = (char *)tmp_pu12[4];
      tmp_c1 = *tmp_pc9;
    }
    else {
      local_58 = (uint32_t *)va("%s%-12s",local_58,tmp_pc9);
      local_5c = (uint32_t *)((int)local_5c + 1);
      local_54 = local_54 + 1;
      if (local_5c != (uint32_t *)0x6) goto LAB_000db5e7;
LAB_000db63a:
      local_58 = (uint32_t *)va(&g_unk_0026fe3c,local_58);
      tmp_pc9 = (char *)tmp_pu12[4];
      tmp_c1 = *tmp_pc9;
      local_5c = (uint32_t *)0x0;
    }
    if (tmp_c1 == '\0') break;
    tmp_i3 = tmp_i3 + 1;
    tmp_pu12 = tmp_pu12 + 5;
  } while (tmp_i3 != 0x3c);
  bigTextBuffer = 0;
  if (param_1 == 0) {
    G_shrubbot_buffer_print_part_15();
  }
  else {
    Q_strcat(&bigTextBuffer,100000,local_58);
  }
  tmp_pc9 = "unblind";
  local_58 = (uint32_t *)&g_unk_0026ea14;
  tmp_pu12 = (uint32_t *)&g_unk_002b3f54;
  do {
    while (tmp_i3 = nitrox_CheckCommandPermission(param_1,*tmp_pu12), tmp_i3 != 0) {
      local_58 = (uint32_t *)va("%s%-12s",local_58,tmp_pc9);
      local_5c = (uint32_t *)((int)local_5c + 1);
      local_54 = local_54 + 1;
      if (local_5c != (uint32_t *)0x6) goto LAB_000db6c7;
LAB_000db710:
      local_58 = (uint32_t *)va(&g_unk_0026fe3c,local_58);
      tmp_pc9 = (char *)tmp_pu12[4];
      local_5c = (uint32_t *)0x0;
      tmp_pu12 = tmp_pu12 + 5;
      if (*tmp_pc9 == '\0') goto LAB_000db73c;
    }
    if (local_5c == (uint32_t *)0x6) goto LAB_000db710;
LAB_000db6c7:
    tmp_pc9 = (char *)tmp_pu12[4];
    tmp_pu12 = tmp_pu12 + 5;
  } while (*tmp_pc9 != '\0');
LAB_000db73c:
  if (param_1 == 0) {
    G_shrubbot_buffer_print_part_15();
    if ((CustomCommands != (char *)0x0) && (*CustomCommands != '\0')) goto LAB_000db778;
LAB_000dbd3e:
    G_shrubbot_buffer_print_part_15();
    if (local_54 == 0) goto LAB_000dbac9;
  }
  else {
    Q_strcat(&bigTextBuffer,100000,local_58);
    local_50 = tmp_pu8;
    if ((CustomCommands != (char *)0x0) && (*CustomCommands != '\0')) {
LAB_000db778:
      local_50 = &g_unk_0026ea14;
      tmp_pc9 = CustomCommands;
      local_58 = &g_unk_02db0e44;
      do {
        tmp_pu12 = &g_unk_02db0e44;
        if (g_unk_02af58b8 == 0) {
          if (param_1 != 0) {
LAB_000dba48:
            tmp_i3 = 0;
            tmp_pc2 = CustomCommands;
            goto joined_r0x000db7e7;
          }
LAB_000dba50:
          local_50 = (uint8_t *)va("%s%-12s",local_50,local_58[-1]);
          local_5c = (uint32_t *)((int)local_5c + 1);
          local_54 = local_54 + 1;
        }
        else {
          if (param_1 == 0) goto LAB_000dba50;
          if (*(int *)(param_1 + 0x5e8) == 0) goto LAB_000dba48;
          tmp_i3 = GetUserPointer(param_1);
          tmp_i3 = **(int **)(tmp_i3 + 0x4c);
          tmp_pc2 = CustomCommands;
joined_r0x000db7e7:
          while (tmp_pc2 != (char *)0x0) {
            tmp_i4 = Q_stricmp(tmp_pc9,tmp_pc2);
            if (tmp_i4 == 0) {
              tmp_i4 = *(int *)(tmp_pu12[-1] + 0x840);
              if (tmp_i4 != -1) {
                if (tmp_i4 == tmp_i3) goto LAB_000dba50;
                tmp_pi5 = (int *)(tmp_pu12[-1] + 0x844);
                while (tmp_i4 = *tmp_pi5, tmp_i4 != -1) {
                  tmp_pi5 = tmp_pi5 + 1;
                  if (tmp_i4 == tmp_i3) goto LAB_000dba50;
                }
              }
            }
            tmp_pc2 = (char *)*tmp_pu12;
            tmp_pu12 = tmp_pu12 + 1;
          }
        }
        if (local_5c == (uint32_t *)0x6) {
          local_50 = (uint8_t *)va(&g_unk_0026fe3c,local_50);
          local_5c = (uint32_t *)0x0;
        }
        tmp_pc9 = (char *)*local_58;
      } while ((tmp_pc9 != (char *)0x0) && (local_58 = local_58 + 1, *tmp_pc9 != '\0'));
      if (param_1 == 0) goto LAB_000dbd3e;
    }
    Q_strcat(&bigTextBuffer,100000,local_50);
    if (local_54 == 0) goto LAB_000db898;
  }
  tmp_pu8 = (uint8_t *)va(&g_unk_0026fe3c,&g_unk_0026ea14);
  if (param_1 == 0) {
LAB_000dbac9:
    G_shrubbot_buffer_print_part_15();
    va("^g%i ^9Commands available\n",local_54);
    G_shrubbot_buffer_print_part_15();
LAB_000dbaf7:
    G_shrubbot_buffer_print_part_15();
    G_shrubbot_print_part_8();
    return 1;
  }
LAB_000db898:
  Q_strcat(&bigTextBuffer,100000,tmp_pu8);
  tmp_u6 = va("^g%i ^9Commands available\n",local_54);
  Q_strcat(&bigTextBuffer,100000,tmp_u6);
  Q_strcat(&bigTextBuffer,100000,"^9Type !help [command] for help with a specific command.^7\n");
  tmp_u7 = strlen(&bigTextBuffer);
joined_r0x000dbbbb:
  if (tmp_u7 < 0x3e9) {
    tmp_u6 = va("print \"%s\"",&bigTextBuffer);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
    return 1;
  }
  nitrox_bigBufferPrint(param_1);
  return 1;
}

void G_shrubbot_buffer_print(int param_1,uint32_t param_2)
{
  if (param_1 != 0) {
    Q_strcat(&bigTextBuffer,100000,param_2);
    return;
  }
  G_shrubbot_buffer_print_part_15();
  return;
}

void G_shrubbot_cleanup(void)
{
  void *pvVar1;
  int *tmp_pi2;
  
  if (Levels != (void *)0x0) {
    pvVar1 = Levels;
    tmp_pi2 = (int *)&Levels;
    do {
      free(pvVar1);
      *tmp_pi2 = 0;
      pvVar1 = (void *)tmp_pi2[1];
      tmp_pi2 = tmp_pi2 + 1;
    } while (pvVar1 != (void *)0x0);
  }
  if (Users != (void *)0x0) {
    pvVar1 = Users;
    tmp_pi2 = (int *)&Users;
    do {
      free(pvVar1);
      *tmp_pi2 = 0;
      pvVar1 = (void *)tmp_pi2[1];
      tmp_pi2 = tmp_pi2 + 1;
    } while (pvVar1 != (void *)0x0);
  }
  if (Bans != (void *)0x0) {
    pvVar1 = Bans;
    tmp_pi2 = (int *)&Bans;
    do {
      free(pvVar1);
      *tmp_pi2 = 0;
      pvVar1 = (void *)tmp_pi2[1];
      tmp_pi2 = tmp_pi2 + 1;
    } while (pvVar1 != (void *)0x0);
  }
  if (Mutes != (void *)0x0) {
    pvVar1 = Mutes;
    tmp_pi2 = (int *)&Mutes;
    do {
      free(pvVar1);
      *tmp_pi2 = 0;
      pvVar1 = (void *)tmp_pi2[1];
      tmp_pi2 = tmp_pi2 + 1;
    } while (pvVar1 != (void *)0x0);
  }
  if (CustomCommands != (void *)0x0) {
    pvVar1 = CustomCommands;
    tmp_pi2 = (int *)&CustomCommands;
    do {
      free(pvVar1);
      *tmp_pi2 = 0;
      pvVar1 = (void *)tmp_pi2[1];
      tmp_pi2 = tmp_pi2 + 1;
    } while (pvVar1 != (void *)0x0);
  }
  if (CustomVotes != (void *)0x0) {
    pvVar1 = CustomVotes;
    tmp_pi2 = (int *)&CustomVotes;
    do {
      free(pvVar1);
      *tmp_pi2 = 0;
      pvVar1 = (void *)tmp_pi2[1];
      tmp_pi2 = tmp_pi2 + 1;
    } while (pvVar1 != (void *)0x0);
  }
  g_unk_02af58b8 = 0;
  return;
}

uint32_t G_shrubbot_level(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = 0;
  if (g_unk_02af58b8 != 0) {
    if ((param_1 == 0) || (*(int *)(param_1 + 400) == 0)) {
      return 0x7fffffff;
    }
    if (*(int *)(param_1 + 0x5e8) != 0) {
      tmp_i2 = GetUserPointer(param_1);
      tmp_u1 = **(uint32_t **)(tmp_i2 + 0x4c);
    }
  }
  return tmp_u1;
}

void UpdateIPBans(int param_1)
{
  int tmp_i1;
  uint *tmp_pu2;
  uint32_t tmp_u3;
  uint *tmp_pu4;
  uint *tmp_pu5;
  uint tmp_u6;
  uint tmp_u7;
  uint tmp_u8;
  int tmp_i9;
  int tmp_i10;
  int local_164;
  uint32_t local_160;
  uint local_15c [16];
  uint8_t local_11c [264];
  uint32_t uStack_14;
  
  tmp_i9 = 0;
  uStack_14 = 0xe1efb;
  tmp_i10 = *(int *)(param_1 + 0x2000);
  local_11c[0] = 0;
  if (0 < tmp_i10) {
    do {
      tmp_i1 = *(int *)(param_1 + 4 + tmp_i9 * 8);
      if (tmp_i1 != -1) {
        local_164 = tmp_i1;
        tmp_i10 = 0;
        local_15c[0]._0_1_ = 0;
        local_160 = *(uint32_t *)(param_1 + tmp_i9 * 8);
        while( true ) {
          if (*(char *)((int)local_15c + tmp_i10 + -4) == -1) {
            tmp_u3 = va("%i",*(uint8_t *)((int)&local_164 + tmp_i10));
            Q_strcat(local_15c,0x40,tmp_u3);
          }
          else {
            Q_strcat(local_15c,0x40,"*");
          }
          if (tmp_i10 == 3) break;
          tmp_i10 = tmp_i10 + 1;
          Q_strcat(local_15c,0x40,&g_unk_0026f722);
        }
        Q_strcat(local_15c,0x40,&g_unk_002612df);
        tmp_pu2 = (uint *)local_11c;
        do {
          tmp_pu5 = tmp_pu2;
          tmp_u6 = *tmp_pu5 + 0xfefefeff & ~*tmp_pu5;
          tmp_u7 = tmp_u6 & 0x80808080;
          tmp_pu2 = tmp_pu5 + 1;
        } while (tmp_u7 == 0);
        if ((tmp_u6 & 0x8080) == 0) {
          tmp_pu2 = (uint *)((int)tmp_pu5 + 6);
          tmp_u7 = tmp_u7 >> 0x10;
        }
        tmp_pu5 = local_15c;
        do {
          tmp_pu4 = tmp_pu5;
          tmp_u8 = *tmp_pu4 + 0xfefefeff & ~*tmp_pu4;
          tmp_u6 = tmp_u8 & 0x80808080;
          tmp_pu5 = tmp_pu4 + 1;
        } while (tmp_u6 == 0);
        if ((tmp_u8 & 0x8080) == 0) {
          tmp_pu5 = (uint *)((int)tmp_pu4 + 6);
          tmp_u6 = tmp_u6 >> 0x10;
        }
        if (0xff < (int)tmp_pu2 +
                   (int)tmp_pu5 +
                   (-(int)local_11c - (uint)CARRY1((byte)tmp_u7,(byte)tmp_u7)) +
                   ((-6 - (uint)CARRY1((byte)tmp_u6,(byte)tmp_u6)) - (int)local_15c)) {
          Com_Printf("%s overflowed at MAX_CVAR_VALUE_STRING\n",param_1 + 0x2004);
          break;
        }
        Q_strcat(local_11c,0x100,local_15c);
        tmp_i10 = *(int *)(param_1 + 0x2000);
      }
      tmp_i9 = tmp_i9 + 1;
    } while (tmp_i9 < tmp_i10);
  }
  trap_Cvar_Set(param_1 + 0x2004,local_11c);
  return;
}

bool G_FilterIPBanPacket(char *param_1)
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
  if (0 < g_unk_008253e0) {
    if ((ipFilters & local_14) != g_unk_008233e4) {
      tmp_i6 = 0;
      tmp_pu4 = &g_unk_008233e8;
      do {
        tmp_i6 = tmp_i6 + 1;
        if (tmp_i6 == g_unk_008253e0) goto LAB_000e2471;
        tmp_u2 = *tmp_pu4;
        tmp_pu1 = tmp_pu4 + 1;
        tmp_pu4 = tmp_pu4 + 2;
      } while ((tmp_u2 & local_14) != *tmp_pu1);
    }
    return GHIDRA_FIELD(g_filterBan, 12, 4) != 0;
  }
LAB_000e2471:
  return GHIDRA_FIELD(g_filterBan, 12, 4) == 0;
}

void AddIPBan(char *param_1)
{
  int tmp_i1;
  char tmp_c2;
  long tmp_l3;
  int tmp_i4;
  char *tmp_pc5;
  int tmp_i6;
  int tmp_i7;
  uint32_t local_a4;
  uint32_t local_a0;
  char local_9c [136];
  uint32_t uStack_14;
  
  uStack_14 = 0xe27d9;
  if (g_unk_008253e0 < 1) {
    if (g_unk_008253e0 == 0) {
LAB_000e282b:
      tmp_i6 = g_unk_008253e0;
      g_unk_008253e0 = g_unk_008253e0 + 1;
    }
    else {
      tmp_i6 = 0;
    }
  }
  else {
    tmp_i6 = 0;
    tmp_i7 = g_unk_008233e4;
    while (tmp_i7 != -1) {
      tmp_i6 = tmp_i6 + 1;
      if (tmp_i6 == g_unk_008253e0) {
        if (tmp_i6 == 0x400) {
          G_Printf("IP filter list is full\n");
          return;
        }
        goto LAB_000e282b;
      }
      tmp_i7 = (&g_unk_008233e4)[tmp_i6 * 2];
    }
  }
  local_a0 = 0;
  tmp_i7 = 0;
  local_a4 = 0;
  do {
    tmp_c2 = *param_1;
    if ((byte)(tmp_c2 - 0x30U) < 10) {
      tmp_i1 = 0;
      tmp_pc5 = param_1;
      do {
        param_1 = tmp_pc5;
        tmp_i4 = tmp_i1;
        tmp_pc5 = param_1 + 1;
        local_9c[tmp_i4] = tmp_c2;
        tmp_c2 = *tmp_pc5;
        tmp_i1 = tmp_i4 + 1;
      } while ((byte)(tmp_c2 - 0x30U) < 10);
      local_9c[tmp_i4 + 1] = '\0';
      tmp_l3 = strtol(local_9c,(char **)0x0,10);
      tmp_c2 = *tmp_pc5;
      local_9c[tmp_i7 + -4] = -1;
      *(char *)((int)&local_a4 + tmp_i7) = (char)tmp_l3;
    }
    else {
      if (tmp_c2 != '*') {
        G_Printf("Bad filter address: %s\n",param_1);
        (&g_unk_008233e4)[tmp_i6 * 2] = 0xffffffff;
        goto LAB_000e288d;
      }
      tmp_c2 = param_1[1];
    }
    if (tmp_c2 == '\0') break;
    param_1 = param_1 + 2;
    tmp_i7 = tmp_i7 + 1;
  } while (tmp_i7 != 4);
  (&ipFilters)[tmp_i6 * 2] = local_a0;
  (&g_unk_008233e4)[tmp_i6 * 2] = local_a4;
LAB_000e288d:
  UpdateIPBans();
  return;
}

void G_ProcessIPBans(void)
{
  char tmp_c1;
  int tmp_i2;
  char *tmp_pc3;
  long tmp_l4;
  int tmp_i5;
  char tmp_c6;
  char *tmp_pc7;
  int tmp_i8;
  char *__s;
  char *tmp_pc9;
  int local_1bc;
  uint32_t local_1a4;
  uint32_t local_1a0;
  char local_19c [128];
  uint8_t local_11c [264];
  uint32_t uStack_14;
  
  uStack_14 = 0xe2b6b;
  g_unk_008253e0 = 0;
  Q_strncpyz(&g_unk_008253e4,"g_banIPs",0x20);
  Q_strncpyz(local_11c,0x2e53af0,0x100);
  tmp_pc7 = g_banIPs + 0x10;
  tmp_c1 = g_banIPs[0x10];
joined_r0x000e2bd5:
  tmp_c6 = tmp_c1;
  __s = tmp_pc7;
  if ((tmp_c6 == '\0') || (tmp_pc3 = strchr(__s,0x20), tmp_pc3 == (char *)0x0)) {
    return;
  }
  if (*tmp_pc3 == ' ') goto LAB_000e2c10;
  goto LAB_000e2c37;
LAB_000e2c10:
  do {
    tmp_pc7 = tmp_pc3 + 1;
    *tmp_pc3 = '\0';
    tmp_pc3 = tmp_pc7;
  } while (*tmp_pc7 == ' ');
  tmp_c6 = *__s;
  tmp_c1 = *tmp_pc7;
  if (tmp_c6 == '\0') goto joined_r0x000e2bd5;
LAB_000e2c37:
  tmp_i8 = g_unk_008253e0;
  tmp_pc7 = tmp_pc3;
  if (g_unk_008253e0 < 1) {
    if (g_unk_008253e0 == 0) {
LAB_000e2c83:
      g_unk_008253e0 = g_unk_008253e0 + 1;
      local_1bc = tmp_i8;
      goto LAB_000e2c90;
    }
  }
  else if (g_unk_008233e4 != -1) {
    local_1bc = 0;
    do {
      local_1bc = local_1bc + 1;
      if (local_1bc == g_unk_008253e0) {
        if (local_1bc != 0x400) goto LAB_000e2c83;
        G_Printf("IP filter list is full\n");
        tmp_c1 = *tmp_pc3;
        goto joined_r0x000e2bd5;
      }
    } while ((&g_unk_008233e4)[local_1bc * 2] != -1);
    goto LAB_000e2c90;
  }
  local_1bc = 0;
LAB_000e2c90:
  local_1a0 = 0;
  tmp_i8 = 0;
  local_1a4 = 0;
  if ((byte)(tmp_c6 - 0x30U) < 10) goto LAB_000e2cd7;
  while (tmp_c6 == '*') {
    tmp_c1 = __s[1];
    while( true ) {
      if ((tmp_c1 == '\0') || (tmp_i8 = tmp_i8 + 1, tmp_i8 == 4)) {
        (&ipFilters)[local_1bc * 2] = local_1a0;
        (&g_unk_008233e4)[local_1bc * 2] = local_1a4;
        goto LAB_000e2d46;
      }
      __s = __s + 2;
      tmp_c6 = *__s;
      if (9 < (byte)(tmp_c6 - 0x30U)) break;
LAB_000e2cd7:
      tmp_i2 = 0;
      tmp_pc9 = __s;
      do {
        __s = tmp_pc9;
        tmp_i5 = tmp_i2;
        tmp_pc9 = __s + 1;
        local_19c[tmp_i5] = tmp_c6;
        tmp_c6 = *tmp_pc9;
        tmp_i2 = tmp_i5 + 1;
      } while ((byte)(tmp_c6 - 0x30U) < 10);
      local_19c[tmp_i5 + 1] = '\0';
      tmp_l4 = strtol(local_19c,(char **)0x0,10);
      tmp_c1 = *tmp_pc9;
      local_19c[tmp_i8 + -4] = -1;
      *(char *)((int)&local_1a4 + tmp_i8) = (char)tmp_l4;
    }
  }
  G_Printf("Bad filter address: %s\n",__s);
  (&g_unk_008233e4)[local_1bc * 2] = 0xffffffff;
LAB_000e2d46:
  UpdateIPBans();
  tmp_c1 = *tmp_pc3;
  goto joined_r0x000e2bd5;
}

void ClearMaxLivesBans(void)
{
  uint8_t *tmp_pu1;
  
  if (0 < numMaxLivesFilters) {
    tmp_pu1 = &guidMaxLivesFilters;
    do {
      *tmp_pu1 = 0;
      tmp_pu1 = tmp_pu1 + 0x21;
    } while (tmp_pu1 != &guidMaxLivesFilters + numMaxLivesFilters * 0x21);
  }
  numMaxLivesFilters = 0;
  g_unk_008233a0 = 0;
  Q_strncpyz(&g_unk_008233a4,"g_maxlivesbanIPs",0x20);
  return;
}

uint32_t G_Kick_v(int param_1,uint32_t param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  int tmp_i2;
  long tmp_l3;
  uint32_t tmp_u4;
  int tmp_i5;
  
  if (param_3 == 0) {
    tmp_l3 = strtol(&g_unk_00abee68,(char **)0x0,10);
    trap_DropClient(tmp_l3,"You have been kicked",0x78);
    tmp_i1 = level;
    tmp_l3 = strtol(&g_unk_00abee68,(char **)0x0,10);
    tmp_u4 = va("cp \"%s\n^3has been kicked!\n\"",tmp_i1 + 0x5f8 + tmp_l3 * 0x54dc);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    return 0;
  }
  if (((param_1 != 0) && (GHIDRA_FIELD(vote_allow_kick, 12, 4) == 0)) &&
     ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
      (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 == 0)))) {
    G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
    return 0xffffffff;
  }
  tmp_i1 = G_voteDescription(param_1,param_5,param_2);
  if ((tmp_i1 != 0) || (tmp_i1 = ClientNumberFromString(param_1,param_4), tmp_i1 == -1)) {
    return 0xffffffff;
  }
  tmp_i5 = tmp_i1 * 0x54dc;
  if (*(int *)(level + tmp_i5 + 0xc80) != 0) {
    G_refPrintf(param_1,"Can\'t vote to kick referees!");
    return 0xffffffff;
  }
  if ((*(int *)(level + tmp_i5 + 0xf34) != 0) && ((g_ettvFlags[0xc] & 1) != 0)) {
    G_refPrintf(param_1,"Can\'t vote to kick ETTV Slaves!");
    return 0xffffffff;
  }
  tmp_i2 = nitrox_CheckPermission(g_entities + tmp_i1 * 0x600,0);
  if (tmp_i2 != 0) {
    G_refPrintf(param_1,"Can\'t vote to kick admins!");
    return 0xffffffff;
  }
  if ((((param_1 != 0) && (param_5 == 0)) && (tmp_i2 = *(int *)(level + 3000 + tmp_i5), tmp_i2 != 3))
     && (tmp_i2 != *(int *)(*(int *)(param_1 + 400) + 3000))) {
    G_refPrintf(param_1,"Can\'t vote to kick players on opposing team!");
    return 0xffffffff;
  }
  Com_sprintf(&g_unk_00abee68,0x100,&g_unk_00245ee9,tmp_i1);
  Com_sprintf(param_4,0x100,&g_unk_0024e6e9,tmp_i5 + level + 0x5f8);
  return 0;
}

uint32_t G_Mute_v(int param_1,uint32_t param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  int tmp_i2;
  long tmp_l3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  int tmp_i6;
  
  if (param_5 != 0) {
    return 0xfffffffe;
  }
  if (param_3 != 0) {
    if (((param_1 != 0) && (GHIDRA_FIELD(vote_allow_muting, 12, 4) == 0)) &&
       ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
        (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 == 0)))) {
      G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
      return 0xffffffff;
    }
    tmp_i1 = G_voteDescription(param_1,0,param_2);
    if ((tmp_i1 != 0) || (tmp_i1 = ClientNumberFromString(param_1,param_4), tmp_i1 == -1)) {
      return 0xffffffff;
    }
    tmp_i6 = tmp_i1 * 0x54dc;
    if (*(int *)(level + 0xc80 + tmp_i6) == 0) {
      tmp_i2 = nitrox_CheckPermission(g_entities + tmp_i1 * 0x600,0);
      if (tmp_i2 == 0) {
        tmp_i2 = level + tmp_i6;
        if ((*(int *)(tmp_i2 + 0xbf0) == 0) &&
           (tmp_i2 = G_shrubbot_mute_check(tmp_i2 + 0x61c,tmp_i2 + 0xaf4), tmp_i2 == 0)) {
          Com_sprintf(&g_unk_00abee68,0x100,&g_unk_00245ee9,tmp_i1);
          Com_sprintf(param_4,0x100,&g_unk_0024e6e9,tmp_i6 + level + 0x5f8);
          return 0;
        }
        G_refPrintf(param_1,"Player is already muted!");
        return 0xffffffff;
      }
      G_refPrintf(param_1,"Can\'t vote to mute admins with the immunity flag!");
    }
    else {
      G_refPrintf(param_1,"Can\'t vote to mute referees!");
    }
    return 0xffffffff;
  }
  tmp_l3 = strtol(&g_unk_00abee68,(char **)0x0,10);
  if (*(int *)(level + 0xc80 + tmp_l3 * 0x54dc) != 2) {
    tmp_u5 = 0x3c;
    if (0x3b < (int)GHIDRA_FIELD(g_defaultMute, 12, 4)) {
      tmp_u5 = GHIDRA_FIELD(g_defaultMute, 12, 4);
    }
    tmp_u4 = va("!mute %i %d MuteVote\n",tmp_l3,tmp_u5);
    trap_SendConsoleCommand(2,tmp_u4);
    tmp_u4 = va("print \"^9You\'ve been muted by vote for %d seconds.\n\"",tmp_u5);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u4);
    tmp_i1 = tmp_l3 * 0x54dc + level;
    *(uint32_t *)(tmp_i1 + 0xbf0) = 1;
    tmp_u5 = va("cp \"%s\n^3has been muted for %d seconds!\n\"",tmp_i1 + 0x5f8,tmp_u5);
    trap_SendServerCommand(0xffffffff,tmp_u5);
    ClientUserinfoChanged(tmp_l3);
    return 0;
  }
  G_Printf("Cannot mute a referee.\n");
  return 0;
}

uint32_t G_UnMute_v(int param_1,uint32_t param_2,int param_3,uint32_t param_4,int param_5)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t tmp_u3;
  
  if (param_5 != 0) {
    return 0xfffffffe;
  }
  if (param_3 == 0) {
    tmp_l2 = strtol(&g_unk_00abee68,(char **)0x0,10);
    if (*(int *)(level + 0xc80 + tmp_l2 * 0x54dc) == 2) {
      G_Printf("Cannot un-mute a referee.\n");
      return 0;
    }
    trap_SendServerCommand(tmp_l2,"cpm \"^3You have been un-muted\"");
    tmp_i1 = tmp_l2 * 0x54dc + level;
    *(uint32_t *)(tmp_i1 + 0xbf0) = 0;
    *(uint32_t *)(tmp_i1 + 0xca4) = 0xffffffff;
    tmp_u3 = va("cp \"%s\n^3has been un-muted!\n\"",tmp_i1 + 0x5f8);
    trap_SendServerCommand(0xffffffff,tmp_u3);
    ClientUserinfoChanged(tmp_l2);
    return 0;
  }
  if (((param_1 == 0) || (GHIDRA_FIELD(vote_allow_muting, 12, 4) != 0)) ||
     ((*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0 &&
      (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 != 0)))) {
    tmp_i1 = G_voteDescription(param_1,0,param_2);
    if ((tmp_i1 == 0) && (tmp_i1 = ClientNumberFromString(param_1,param_4), tmp_i1 != -1)) {
      if (*(int *)(level + 0xbf0 + tmp_i1 * 0x54dc) != 0) {
        Com_sprintf(&g_unk_00abee68,0x100,&g_unk_00245ee9,tmp_i1);
        Com_sprintf(param_4,0x100,&g_unk_0024e6e9,tmp_i1 * 0x54dc + level + 0x5f8);
        return 0;
      }
      G_refPrintf(param_1,"Player is not muted!");
    }
  }
  else {
    G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
  }
  return 0xffffffff;
}

G_Referee_v(int param_1,uint32_t param_2,int param_3,uint32_t param_4,uint32_t param_5)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t tmp_u3;
  int tmp_i4;
  
  tmp_i1 = level;
  if (param_3 == 0) {
    tmp_l2 = strtol(&g_unk_00abee68,(char **)0x0,10);
    tmp_i1 = tmp_l2 * 0x54dc + tmp_i1;
    if (*(int *)(tmp_i1 + 0x5ac) == 0) {
      trap_SendServerCommand(0xffffffff,"print \"Player left before becoming referee\n\"");
      return 0;
    }
    *(uint32_t *)(tmp_i1 + 0xc80) = 1;
    *(uint32_t *)(tmp_i1 + 0xc88) = 3;
    tmp_u3 = va("cp \"%s^7 is now a referee\n\"",tmp_i1 + 0x5f8);
    trap_SendServerCommand(0xffffffff,tmp_u3);
    tmp_l2 = strtol(&g_unk_00abee68,(char **)0x0,10);
    ClientUserinfoChanged(tmp_l2);
    return 0;
  }
  if (((param_1 != 0) && (GHIDRA_FIELD(vote_allow_referee, 12, 4) == 0)) &&
     ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
      (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 == 0)))) {
    G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
    return 0xffffffff;
  }
  if (*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0) {
    if (g_unk_00abe940 < 3) {
      G_refPrintf(param_1,"Sorry, not enough clients in the game to vote for a referee");
      return 0xffffffff;
    }
  }
  else {
    tmp_i1 = trap_Argc();
    if (tmp_i1 == 2) {
      G_refPrintf(param_1,"Use the ^3players^7 command to find a valid player ID.");
      return 0xffffffff;
    }
  }
  tmp_i1 = trap_Argc();
  if (tmp_i1 == 2) {
    tmp_i1 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  }
  else {
    tmp_i1 = G_voteDescription(param_1,param_5,param_2);
    if (tmp_i1 != 0) {
      return 0xffffffff;
    }
    tmp_i1 = ClientNumberFromString(param_1,param_4);
    if (tmp_i1 == -1) {
      return 0xffffffff;
    }
  }
  tmp_i4 = level + tmp_i1 * 0x54dc;
  if (*(int *)(tmp_i4 + 0xc80) != 0) {
    G_refPrintf(param_1,"[lof]%s [lon]is already a referee!",tmp_i4 + 0x5f8);
    return 0xffffffff;
  }
  Com_sprintf(&g_unk_00abee68,0x100,&g_unk_00245ee9,tmp_i1);
  Com_sprintf(param_4,0x100,&g_unk_0024e6e9,tmp_i1 * 0x54dc + level + 0x5f8);
  return 0;
}

G_Unreferee_v(int param_1,uint32_t param_2,int param_3,uint32_t param_4,uint32_t param_5)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t tmp_u3;
  int tmp_i4;
  
  tmp_i1 = level;
  if (param_3 == 0) {
    tmp_l2 = strtol(&g_unk_00abee68,(char **)0x0,10);
    tmp_i1 = tmp_l2 * 0x54dc + tmp_i1;
    *(uint32_t *)(tmp_i1 + 0xc80) = 0;
    *(uint32_t *)(tmp_i1 + 0xc88) = 0;
    tmp_u3 = va("cp \"%s^7\nis no longer a referee\n\"",tmp_i1 + 0x5f8);
    trap_SendServerCommand(0xffffffff,tmp_u3);
    tmp_l2 = strtol(&g_unk_00abee68,(char **)0x0,10);
    ClientUserinfoChanged(tmp_l2);
    return 0;
  }
  if (((param_1 != 0) && (GHIDRA_FIELD(vote_allow_referee, 12, 4) == 0)) &&
     ((*(int *)(*(int *)(param_1 + 400) + 0xc80) == 0 ||
      (tmp_i1 = nitrox_CheckPermission(param_1,6), tmp_i1 == 0)))) {
    G_refPrintf(param_1,"Sorry, [lof]^3%s^7 [lon]voting has been disabled",param_3);
    return 0xffffffff;
  }
  if ((*(int *)(*(int *)(param_1 + 400) + 0xc80) != 0) && (tmp_i1 = trap_Argc(), tmp_i1 == 2)) {
    G_refPrintf(param_1,"Use the ^3players^7 command to find a valid player ID.");
    return 0xffffffff;
  }
  tmp_i1 = trap_Argc();
  if (tmp_i1 == 2) {
    tmp_i1 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  }
  else {
    tmp_i1 = G_voteDescription(param_1,param_5,param_2);
    if (tmp_i1 != 0) {
      return 0xffffffff;
    }
    tmp_i1 = ClientNumberFromString(param_1,param_4);
    if (tmp_i1 == -1) {
      return 0xffffffff;
    }
  }
  tmp_i4 = level + tmp_i1 * 0x54dc;
  if (*(int *)(tmp_i4 + 0xc80) == 0) {
    G_refPrintf(param_1,"[lof]%s [lon]isn\'t a referee!",tmp_i4 + 0x5f8);
    return 0xffffffff;
  }
  if (*(int *)(tmp_i4 + 0xc80) != 2) {
    if (*(int *)(tmp_i4 + 0x5e8) != 0) {
      G_refPrintf(param_1,"[lof]%s\'s [lon]is the Server Host",tmp_i4 + 0x5f8);
      return 0xffffffff;
    }
    Com_sprintf(&g_unk_00abee68,0x100,&g_unk_00245ee9,tmp_i1);
    Com_sprintf(param_4,0x100,&g_unk_0024e6e9,tmp_i1 * 0x54dc + level + 0x5f8);
    return 0;
  }
  G_refPrintf(param_1,"[lof]%s\'s [lon]status cannot be removed",tmp_i4 + 0x5f8);
  return 0xffffffff;
}

uint32_t G_Mutespecs_v(int param_1,int param_2,int param_3,char *param_4,uint32_t param_5)
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
    tmp_u4 = va("cpm \"^3%s is: ^5%s\n\"","Spectator Muting",tmp_pc3);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    trap_Cvar_Set("match_mutespecs",&g_unk_00abee68);
    tmp_u4 = 0;
  }
  else {
    tmp_b5 = GHIDRA_FIELD(match_mutespecs, 12, 4) != 0;
    if (((param_1 == 0) || (GHIDRA_FIELD(vote_allow_mutespecs, 12, 4) != 0)) ||
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

void G_CanisterKick(uint32_t *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float *pfVar4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  uint32_t tmp_u9;
  float local_1070;
  float local_106c;
  float local_1068;
  uint8_t local_1064 [12];
  uint8_t local_1058 [12];
  float local_104c;
  uint32_t local_1048;
  uint32_t local_1044;
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
  
  tmp_i5 = param_1[100];
  if ((((*(byte *)(tmp_i5 + 0xd) & 0x40) == 0) && (*(int *)(tmp_i5 + 4) != 3)) &&
     ((*(byte *)(tmp_i5 + 0x6a) & 8) == 0)) {
    local_1048 = *(uint32_t *)(tmp_i5 + 0xb4);
    local_104c = 0.0;
    local_1044 = 0;
    AngleVectors(&local_104c,&local_1070,local_1064,local_1058);
    tmp_f1 = local_1070 * 24.0 + (float)param_1[0x5a];
    local_1024 = local_106c * 24.0 + (float)param_1[0x5b];
    local_1020 = local_1068 * 24.0 + (float)param_1[0x5c];
    local_1028 = tmp_f1;
    pfVar4 = (float *)tv(0xc2000000,0xc2000000,0xc1c00000);
    tmp_f2 = local_1024;
    local_1040 = tmp_f1 + *pfVar4;
    tmp_i5 = tv(0xc2000000,0xc2000000,0xc1c00000);
    tmp_f3 = local_1020;
    local_103c = tmp_f2 + *(float *)(tmp_i5 + 4);
    tmp_i5 = tv(0xc2000000,0xc2000000,0xc1c00000);
    tmp_f1 = local_1028;
    local_1038 = tmp_f3 + *(float *)(tmp_i5 + 8);
    pfVar4 = (float *)tv(0x42000000,0x42000000,0x41000000);
    tmp_f2 = local_1024;
    local_1034 = tmp_f1 + *pfVar4;
    tmp_i5 = tv(0x42000000,0x42000000,0x41000000);
    tmp_f1 = local_1020;
    local_1030 = tmp_f2 + *(float *)(tmp_i5 + 4);
    tmp_i5 = tv(0x42000000,0x42000000,0x41000000);
    local_102c = tmp_f1 + *(float *)(tmp_i5 + 8);
    tmp_i5 = trap_EntitiesInBox(&local_1040,&local_1034,local_101c,0x400);
    if (GHIDRA_FIELD(g_debugBullets, 12, 4) != 0) {
      tmp_u9 = tv(0x3f800000,0,0);
      G_RailBox(&local_1028,&local_1040,&local_1034,tmp_u9,0xffffffff);
    }
    if (0 < tmp_i5) {
      tmp_i6 = 0;
      tmp_i7 = *(int *)(g_entities + local_101c[0] * 0x600 + 4);
      tmp_i8 = local_101c[0];
      while (tmp_i7 != 3) {
        tmp_i6 = tmp_i6 + 1;
        if (tmp_i6 == tmp_i5) {
          return;
        }
        tmp_i8 = local_101c[tmp_i6];
        tmp_i7 = *(int *)(g_entities + tmp_i8 * 0x600 + 4);
      }
      switch(*(uint32_t *)(g_entities + tmp_i8 * 0x600 + 0xe8)) {
      case 4:
      case 9:
      case 0x15:
      case 0x1c:
      case 0x30:
      case 0x32:
        tmp_i5 = param_1[100];
        local_104c = *(float *)(tmp_i5 + 0xb0);
        local_1048 = *(uint32_t *)(tmp_i5 + 0xb4);
        local_1044 = *(uint32_t *)(tmp_i5 + 0xb8);
        if (-15.0 < local_104c) {
          local_104c = -15.0;
        }
        AngleVectors(&local_104c,&local_1070,local_1064,local_1058);
        tmp_i7 = tmp_i8 * 0x600;
        *(uint32_t *)(g_entities + tmp_i7 + 0xc) = 6;
        *(int *)(g_entities + tmp_i7 + 0x10) = g_unk_00abe908 + -0x32;
        *(uint32_t *)(g_entities + tmp_i7 + 0x168) = *(uint32_t *)(g_entities + tmp_i7 + 0x18);
        *(uint32_t *)(g_entities + tmp_i7 + 0x16c) = *(uint32_t *)(g_entities + tmp_i7 + 0x1c);
        *(float *)(g_entities + tmp_i7 + 0x170) = *(float *)(g_entities + tmp_i7 + 0x20) + 30.0;
        *(float *)(g_entities + tmp_i7 + 0x20) = *(float *)(g_entities + tmp_i7 + 0x20) + 30.0;
        tmp_i5 = GHIDRA_FIELD(g_canisterKick, 12, 4) * 2;
        tmp_f1 = (float)(GHIDRA_FIELD(g_canisterKick, 12, 4) * 10);
        *(float *)(g_entities + tmp_i7 + 0x24) = local_1070 * tmp_f1;
        *(float *)(g_entities + tmp_i7 + 0x28) = local_106c * tmp_f1;
        *(float *)(g_entities + tmp_i7 + 0x2c) = (float)tmp_i5 + tmp_f1 * local_1068;
        *(float *)(g_entities + tmp_i7 + 0x24) =
             (float)(int)ROUND(*(float *)(g_entities + tmp_i7 + 0x24));
        *(float *)(g_entities + tmp_i7 + 0x28) =
             (float)(int)ROUND(*(float *)(g_entities + tmp_i7 + 0x28));
        *(float *)(g_entities + tmp_i7 + 0x2c) =
             (float)(int)ROUND(*(float *)(g_entities + tmp_i7 + 0x2c));
        if ((GHIDRA_FIELD(g_canisterKickOwner, 12, 4) != 0) &&
           ((*(int *)(g_entities + tmp_i7 + 0xe8) != 0x15 ||
            (*(int *)(g_entities + tmp_i7 + 0x368) == 0)))) {
          tmp_i8 = tmp_i8 * 0x600;
          *(uint32_t **)(g_entities + tmp_i8 + 0x218) = param_1;
          *(uint32_t *)(g_entities + tmp_i8 + 0x180) = *param_1;
          *(uint32_t *)(g_entities + tmp_i8 + 0x108) = *(uint32_t *)(param_1[100] + 3000);
        }
      }
    }
  }
  return;
}

uint32_t _et_G_shrubbot_level(uint32_t param_1)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  uint32_t tmp_u3;
  
  tmp_i1 = luaL_optinteger(param_1,1,0xffffffff);
  if (tmp_i1 < 0) {
    tmp_pu2 = (uint8_t *)0x0;
  }
  else {
    tmp_pu2 = g_entities + tmp_i1 * 0x600;
  }
  tmp_u3 = G_shrubbot_level(tmp_pu2);
  lua_pushinteger(param_1,tmp_u3);
  return 1;
}

uint32_t _et_G_shrubbot_permission(uint32_t param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t *tmp_pu3;
  
  tmp_i1 = luaL_optinteger(param_1,1,0xffffffff);
  tmp_u2 = luaL_checklstring(param_1,2,0);
  if (tmp_i1 < 0) {
    tmp_pu3 = (uint8_t *)0x0;
  }
  else {
    tmp_pu3 = g_entities + tmp_i1 * 0x600;
  }
  tmp_u2 = G_shrubbot_permission(tmp_pu3,tmp_u2);
  lua_pushinteger(param_1,tmp_u2);
  return 1;
}

void Nit_AdminChat(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  char *tmp_pc4;
  int tmp_i5;
  uint8_t *tmp_pu6;
  int tmp_i7;
  char local_28;
  char local_27;
  char local_26;
  char local_25;
  
  if (((param_1 != 0) && (tmp_i1 = *(int *)(param_1 + 400), tmp_i1 != 0)) &&
     (*(int *)(tmp_i1 + 0x54d8) == 0)) {
    if ((*(int *)(tmp_i1 + 0xbf0) == 0) &&
       (tmp_i1 = G_shrubbot_mute_check(tmp_i1 + 0x61c,tmp_i1 + 0xaf4), tmp_i1 == 0)) {
      tmp_i1 = nitrox_CheckPermission(param_1,0xd);
      if (tmp_i1 != 0) {
        tmp_i1 = 1;
        Q_SayArgv(0,&local_28,0xc);
        if (((local_28 == 's') && (local_27 == 'a')) && (local_26 == 'y')) {
          if (local_25 == '\0') {
            tmp_i1 = 2;
            Q_SayArgv(1,&local_28,0xc);
          }
          else {
            tmp_i1 = 1;
          }
        }
        tmp_i3 = Q_SayArgc();
        if ((tmp_i1 < tmp_i3) && (tmp_pc4 = (char *)Q_SayConcatArgs(tmp_i1), *tmp_pc4 != '\0')) {
          if (0 < g_unk_00abe938) {
            tmp_i3 = 0;
            tmp_i1 = g_unk_00abe938;
            do {
              tmp_i5 = (&g_unk_00abe944)[tmp_i3] * 0x600;
              if (((g_entities[tmp_i5 + 0x128] & 8) == 0) &&
                 (*(int *)(g_entities + tmp_i5 + 400) != 0)) {
                if (*(int *)(*(int *)(g_entities + tmp_i5 + 400) + 0x54d8) != 0) {
                  return;
                }
                tmp_pu6 = g_entities + tmp_i5;
                tmp_i7 = nitrox_CheckPermission(tmp_pu6,0xd);
                tmp_i1 = g_unk_00abe938;
                if ((tmp_i7 != 0) &&
                   (tmp_i7 = nitrox_CheckPermission(tmp_pu6,0xd), tmp_i1 = g_unk_00abe938, tmp_i7 != 0)) {
                  tmp_u2 = va("pop \"^xAdminChat from ^7%s\"",*(int *)(param_1 + 400) + 0x5f8);
                  tmp_i1 = (tmp_i5 >> 9) * -0x55555555;
                  trap_SendServerCommand(tmp_i1,tmp_u2);
                  tmp_u2 = va("chat \"^7%s^1(AdminChat):\" -2",*(int *)(param_1 + 400) + 0x5f8);
                  trap_SendServerCommand(tmp_i1,tmp_u2);
                  tmp_u2 = Q_CleanStr(tmp_pc4);
                  tmp_u2 = va("lc \"%s\"",tmp_u2);
                  trap_SendServerCommand(tmp_i1,tmp_u2);
                  G_AddEvent(tmp_pu6,0x62,0);
                  tmp_i1 = g_unk_00abe938;
                }
              }
              tmp_i3 = tmp_i3 + 1;
            } while (tmp_i3 < tmp_i1);
          }
          G_LogPrintf("adminchat: %s: %s\n",*(int *)(param_1 + 400) + 0x5f8,tmp_pc4);
          return;
        }
        G_shrubbot_print(param_1,"^9usage: ma [message]\n");
        return;
      }
      tmp_pc4 = "^1Error ^9: You don\'t have the permission to use AdminChat\n";
    }
    else {
      tmp_pc4 = "^1Adminchat Error ^9: You are muted\n";
    }
    tmp_u2 = va(tmp_pc4);
    G_shrubbot_print(param_1,tmp_u2);
  }
  return;
}

void nitrox_InitBansTable(void)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_InitBansTable();
  }
  return;
}

void nitrox_InitMutesTable(void)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_InitMutesTable();
  }
  return;
}

void nitrox_LoadBans(void)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_LoadBans();
  }
  return;
}

void nitrox_LoadMutes(void)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_LoadMutes();
  }
  return;
}

void nitrox_SaveBans(uint32_t param_1,uint32_t param_2)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_SaveBans(param_1,param_2);
  }
  return;
}

void nitrox_SaveMutes(uint32_t param_1,uint32_t param_2)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_SaveMutes(param_1,param_2);
  }
  return;
}

void nitrox_SaveSingleBan(uint32_t param_1,uint32_t param_2)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_SaveBan(param_1,param_2);
  }
  return;
}

void nitrox_SaveSingleMute(uint32_t param_1,uint32_t param_2)
{
  if (g_unk_02af58b8 != 0) {
    nitrox_SQLite_SaveMute(param_1,param_2);
  }
  return;
}

void nitrox_InitAdminSystem(void)
{
  int tmp_i1;
  time_t tVar2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  int *tmp_pi6;
  int tmp_i7;
  int local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0x1fd25e;
  g_unk_02af58b8 = 1;
  G_LogPrintf("-----------------------------------\n");
  G_LogPrintf("| [Admin::Initialize] Initializing Admin System...\n");
  tmp_i7 = -1;
  nitrox_LoadDBFiles(0,0xffffffff);
  nitrox_SQLite_init();
  nitrox_InitUsersTable();
  nitrox_InitBansTable();
  nitrox_InitMutesTable();
  nitrox_InitMailsTable();
  nitrox_LoadUsers();
  nitrox_LoadBans();
  nitrox_LoadMutes();
  if (g_unk_02af58b8 != 0) {
    nitrox_ClearInvalidUsers_part_0();
    if (g_unk_02af58b8 != 0) {
      tVar2 = time(local_20);
      if (tVar2 != 0) {
        G_LogPrintf("| [Admin::ClearExpiredBans] Looking for expired bans...\n");
        local_20[0] = local_20[0] + -0x386a4c20;
        if (Bans != 0) {
          tmp_i5 = 0;
          tmp_i4 = Bans;
          tmp_pi6 = &g_unk_02df1044;
          do {
            tmp_i1 = *(int *)(tmp_i4 + 0x48c);
            if ((tmp_i1 != 0) && (tmp_i1 == local_20[0] || tmp_i1 - local_20[0] < 0)) {
              tmp_i5 = tmp_i5 + 1;
              tmp_i7 = 0;
              nitrox_SaveSingleBan(tmp_i4,0);
            }
            tmp_i4 = *tmp_pi6;
            tmp_pi6 = tmp_pi6 + 1;
          } while (tmp_i4 != 0);
          if (tmp_i5 != 0) {
            tmp_pu3 = &g_unk_0024e6ea;
            if (tmp_i5 == 1) {
              tmp_pu3 = &g_unk_0026ea14;
            }
            G_LogPrintf("| [Admin::ClearExpiredBans] Cleared %d expired ban%s. Reloading...\n",tmp_i5
                        ,tmp_pu3);
            nitrox_LoadBans();
            tmp_i7 = tmp_i5;
          }
        }
      }
      if (g_unk_02af58b8 != 0) {
        tVar2 = time(local_20);
        if (tVar2 != 0) {
          G_LogPrintf("| [Admin::ClearExpiredMutes] Looking for expired mutes...\n",tmp_i7);
          local_20[0] = local_20[0] + -0x386a4c20;
          if (Mutes != 0) {
            tmp_i5 = 0;
            tmp_i4 = Mutes;
            tmp_pi6 = &g_unk_02df2044;
            do {
              tmp_i1 = *(int *)(tmp_i4 + 0x48c);
              if ((tmp_i1 != 0) && (tmp_i1 == local_20[0] || tmp_i1 - local_20[0] < 0)) {
                tmp_i5 = tmp_i5 + 1;
                tmp_i7 = 0;
                nitrox_SaveSingleMute(tmp_i4,0);
              }
              tmp_i4 = *tmp_pi6;
              tmp_pi6 = tmp_pi6 + 1;
            } while (tmp_i4 != 0);
            if (tmp_i5 != 0) {
              tmp_pu3 = &g_unk_0024e6ea;
              if (tmp_i5 == 1) {
                tmp_pu3 = &g_unk_0026ea14;
              }
              G_LogPrintf("| [Admin::ClearExpiredMutes] Cleared %d expired mute%s. Reloading...\n",
                          tmp_i5,tmp_pu3);
              nitrox_LoadMutes();
              tmp_i7 = tmp_i5;
            }
          }
        }
        if (g_unk_02af58b8 != 0) {
          G_LogPrintf("| [Admin::Initialize] Done!\n",tmp_i7);
          G_LogPrintf("-----------------------------------\n");
          return;
        }
      }
    }
  }
  G_LogPrintf("! [Admin::Initialize] Couldn\'t initialize Admin System!\n",tmp_i7);
  G_shrubbot_cleanup();
  G_LogPrintf("-----------------------------------\n");
  return;
}

void nitrox_ClearExpiredBans(void)
{
  int tmp_i1;
  time_t tVar2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  int *tmp_pi6;
  time_t local_10;
  
  local_10 = 0x1fd748;
  if (g_unk_02af58b8 != 0) {
    tVar2 = time(&local_10);
    if (tVar2 != 0) {
      G_LogPrintf("| [Admin::ClearExpiredBans] Looking for expired bans...\n");
      local_10 = local_10 + -0x386a4c20;
      if (Bans != 0) {
        tmp_i5 = 0;
        tmp_i4 = Bans;
        tmp_pi6 = &g_unk_02df1044;
        do {
          tmp_i1 = *(int *)(tmp_i4 + 0x48c);
          if ((tmp_i1 != 0) && (tmp_i1 == local_10 || tmp_i1 - local_10 < 0)) {
            tmp_i5 = tmp_i5 + 1;
            nitrox_SaveSingleBan(tmp_i4,0);
          }
          tmp_i4 = *tmp_pi6;
          tmp_pi6 = tmp_pi6 + 1;
        } while (tmp_i4 != 0);
        if (tmp_i5 != 0) {
          tmp_pu3 = &g_unk_0024e6ea;
          if (tmp_i5 == 1) {
            tmp_pu3 = &g_unk_0026ea14;
          }
          G_LogPrintf("| [Admin::ClearExpiredBans] Cleared %d expired ban%s. Reloading...\n",tmp_i5,
                      tmp_pu3);
          nitrox_LoadBans();
        }
      }
    }
  }
  return;
}

void nitrox_ClearExpiredMutes(void)
{
  int tmp_i1;
  time_t tVar2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  int *tmp_pi6;
  time_t local_10;
  
  local_10 = 0x1fd828;
  if (g_unk_02af58b8 != 0) {
    tVar2 = time(&local_10);
    if (tVar2 != 0) {
      G_LogPrintf("| [Admin::ClearExpiredMutes] Looking for expired mutes...\n");
      local_10 = local_10 + -0x386a4c20;
      if (Mutes != 0) {
        tmp_i5 = 0;
        tmp_i4 = Mutes;
        tmp_pi6 = &g_unk_02df2044;
        do {
          tmp_i1 = *(int *)(tmp_i4 + 0x48c);
          if ((tmp_i1 != 0) && (tmp_i1 == local_10 || tmp_i1 - local_10 < 0)) {
            tmp_i5 = tmp_i5 + 1;
            nitrox_SaveSingleMute(tmp_i4,0);
          }
          tmp_i4 = *tmp_pi6;
          tmp_pi6 = tmp_pi6 + 1;
        } while (tmp_i4 != 0);
        if (tmp_i5 != 0) {
          tmp_pu3 = &g_unk_0024e6ea;
          if (tmp_i5 == 1) {
            tmp_pu3 = &g_unk_0026ea14;
          }
          G_LogPrintf("| [Admin::ClearExpiredMutes] Cleared %d expired mute%s. Reloading...\n",tmp_i5
                      ,tmp_pu3);
          nitrox_LoadMutes();
        }
      }
    }
  }
  return;
}

void nitrox_SetAdminPointers(int param_1,int param_2)
{
  char *tmp_pc1;
  int tmp_i2;
  int local_20 [4];
  
  if ((((param_1 != 0) && (g_unk_02af58b8 != 0)) && (*(int *)(param_1 + 400) != 0)) &&
     (*(int *)(*(int *)(param_1 + 400) + 0x54d8) == 0)) {
    if (param_2 != 0) {
      if (*(char *)(param_2 + 0x50) == '\0') {
        *(uint32_t *)(param_2 + 0x10e4) = 0;
      }
      else {
        local_20[0] = param_2 + 0x50;
        *(uint32_t *)(param_2 + 0x10e4) = 0;
        while( true ) {
          tmp_pc1 = (char *)COM_ParseExt(local_20,0);
          if ((tmp_pc1 == (char *)0x0) || (*tmp_pc1 == '\0')) break;
          tmp_i2 = nitrox_GetTokenForString(tmp_pc1);
          if (tmp_i2 == g_unk_002ba9e4) {
            tmp_i2 = 0;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002ba9f0) {
            tmp_i2 = 1;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002ba9fc) {
            tmp_i2 = 2;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa08) {
            tmp_i2 = 3;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa14) {
            tmp_i2 = 4;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa20) {
            tmp_i2 = 5;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa2c) {
            tmp_i2 = 6;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa38) {
            tmp_i2 = 7;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa44) {
            tmp_i2 = 8;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa50) {
            tmp_i2 = 9;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa5c) {
            tmp_i2 = 10;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa68) {
            tmp_i2 = 0xb;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa74) {
            tmp_i2 = 0xc;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa80) {
            tmp_i2 = 0xd;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa8c) {
            tmp_i2 = 0xe;
            goto LAB_001fdb80;
          }
          if (tmp_i2 == g_unk_002baa98) {
            tmp_i2 = 0xf;
LAB_001fdb80:
            *(uint *)(param_2 + 0x10e4) = *(uint *)(param_2 + 0x10e4) | (&g_unk_002ba9e8)[tmp_i2 * 3];
          }
        }
      }
    }
    nitrox_SetAdminCommandPermissions(param_2);
    *(int *)(param_1 + 0x5e8) = param_2;
  }
  return;
}

uint32_t nitrox_GetAdminLevel(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  
  if ((((param_1 == 0) || (g_unk_02af58b8 == 0)) || (*(int *)(param_1 + 400) == 0)) ||
     (tmp_i1 = *(int *)(param_1 + 0x5e8), tmp_i1 == 0)) {
    return 0;
  }
  if (param_2 == 0) {
    tmp_u3 = **(uint32_t **)(tmp_i1 + 0x4c);
  }
  else {
    if ((*(uint *)(tmp_i1 + 0x10e4) != 0) && ((g_unk_002baa60 & *(uint *)(tmp_i1 + 0x10e4)) != 0)) {
      return 0;
    }
    tmp_pu2 = *(uint32_t **)(tmp_i1 + 0x4c);
    if (((tmp_pu2 != (uint32_t *)0x0) && (tmp_pu2[0x30b] != 0)) &&
       ((g_unk_002baa60 & tmp_pu2[0x30b]) != 0)) {
      return 0;
    }
    tmp_u3 = *tmp_pu2;
  }
  return tmp_u3;
}

void nitrox_SetAdminPermissions(int param_1)
{
  char *tmp_pc1;
  int tmp_i2;
  int local_20 [4];
  
  if (param_1 != 0) {
    if (*(char *)(param_1 + 0x50) == '\0') {
      *(uint32_t *)(param_1 + 0x10e4) = 0;
    }
    else {
      local_20[0] = param_1 + 0x50;
      *(uint32_t *)(param_1 + 0x10e4) = 0;
      while( true ) {
        tmp_pc1 = (char *)COM_ParseExt(local_20,0);
        if ((tmp_pc1 == (char *)0x0) || (*tmp_pc1 == '\0')) break;
        tmp_i2 = nitrox_GetTokenForString(tmp_pc1);
        if (tmp_i2 == g_unk_002ba9e4) {
          tmp_i2 = 0;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002ba9f0) {
          tmp_i2 = 1;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002ba9fc) {
          tmp_i2 = 2;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa08) {
          tmp_i2 = 3;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa14) {
          tmp_i2 = 4;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa20) {
          tmp_i2 = 5;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa2c) {
          tmp_i2 = 6;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa38) {
          tmp_i2 = 7;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa44) {
          tmp_i2 = 8;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa50) {
          tmp_i2 = 9;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa5c) {
          tmp_i2 = 10;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa68) {
          tmp_i2 = 0xb;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa74) {
          tmp_i2 = 0xc;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa80) {
          tmp_i2 = 0xd;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa8c) {
          tmp_i2 = 0xe;
          goto LAB_001fdef0;
        }
        if (tmp_i2 == g_unk_002baa98) {
          tmp_i2 = 0xf;
LAB_001fdef0:
          *(uint *)(param_1 + 0x10e4) = *(uint *)(param_1 + 0x10e4) | (&g_unk_002ba9e8)[tmp_i2 * 3];
        }
      }
    }
  }
  return;
}

void nitrox_SetLevelPermissions(int param_1)
{
  char *tmp_pc1;
  int tmp_i2;
  int local_20 [4];
  
  if (param_1 != 0) {
    if (*(char *)(param_1 + 0x28) == '\0') {
      *(uint32_t *)(param_1 + 0xc2c) = 0;
    }
    else {
      local_20[0] = param_1 + 0x28;
      *(uint32_t *)(param_1 + 0xc2c) = 0;
      while( true ) {
        tmp_pc1 = (char *)COM_ParseExt(local_20,0);
        if ((tmp_pc1 == (char *)0x0) || (*tmp_pc1 == '\0')) break;
        tmp_i2 = nitrox_GetTokenForString(tmp_pc1);
        if (g_unk_002ba9e4 == tmp_i2) {
          tmp_i2 = 0;
          goto LAB_001fe120;
        }
        if (g_unk_002ba9f0 == tmp_i2) {
          tmp_i2 = 1;
          goto LAB_001fe120;
        }
        if (g_unk_002ba9fc == tmp_i2) {
          tmp_i2 = 2;
          goto LAB_001fe120;
        }
        if (g_unk_002baa08 == tmp_i2) {
          tmp_i2 = 3;
          goto LAB_001fe120;
        }
        if (g_unk_002baa14 == tmp_i2) {
          tmp_i2 = 4;
          goto LAB_001fe120;
        }
        if (g_unk_002baa20 == tmp_i2) {
          tmp_i2 = 5;
          goto LAB_001fe120;
        }
        if (g_unk_002baa2c == tmp_i2) {
          tmp_i2 = 6;
          goto LAB_001fe120;
        }
        if (g_unk_002baa38 == tmp_i2) {
          tmp_i2 = 7;
          goto LAB_001fe120;
        }
        if (g_unk_002baa44 == tmp_i2) {
          tmp_i2 = 8;
          goto LAB_001fe120;
        }
        if (g_unk_002baa50 == tmp_i2) {
          tmp_i2 = 9;
          goto LAB_001fe120;
        }
        if (g_unk_002baa5c == tmp_i2) {
          tmp_i2 = 10;
          goto LAB_001fe120;
        }
        if (g_unk_002baa68 == tmp_i2) {
          tmp_i2 = 0xb;
          goto LAB_001fe120;
        }
        if (g_unk_002baa74 == tmp_i2) {
          tmp_i2 = 0xc;
          goto LAB_001fe120;
        }
        if (g_unk_002baa80 == tmp_i2) {
          tmp_i2 = 0xd;
          goto LAB_001fe120;
        }
        if (g_unk_002baa8c == tmp_i2) {
          tmp_i2 = 0xe;
          goto LAB_001fe120;
        }
        if (g_unk_002baa98 == tmp_i2) {
          tmp_i2 = 0xf;
LAB_001fe120:
          *(uint *)(param_1 + 0xc2c) = *(uint *)(param_1 + 0xc2c) | (&g_unk_002ba9e8)[tmp_i2 * 3];
        }
      }
    }
  }
  return;
}

bool nitrox_CheckPermission(int param_1,int param_2)
{
  int tmp_i1;
  uint tmp_u2;
  bool tmp_b3;
  
  tmp_b3 = false;
  if (g_unk_02af58b8 != 0) {
    if (param_1 == 0) {
      tmp_b3 = true;
    }
    else {
      tmp_i1 = *(int *)(param_1 + 0x5e8);
      if (tmp_i1 != 0) {
        tmp_u2 = *(uint *)(tmp_i1 + 0x10e4);
        if (tmp_u2 != 0) {
          if (((((tmp_u2 & 0x8000) != 0) && (1 < param_2 - 10U)) && (param_2 != 0)) &&
             (param_2 != 0xe)) {
            return true;
          }
          if (((&g_unk_002ba9e8)[param_2 * 3] & tmp_u2) != 0) {
            return true;
          }
        }
        if (*(int *)(tmp_i1 + 0x4c) != 0) {
          tmp_u2 = *(uint *)(*(int *)(tmp_i1 + 0x4c) + 0xc2c);
          if (tmp_u2 == 0) {
            return false;
          }
          if ((((tmp_u2 & 0x8000) != 0) && (1 < param_2 - 10U)) &&
             ((param_2 != 0 && (param_2 != 0xe)))) {
            return true;
          }
          return ((&g_unk_002ba9e8)[param_2 * 3] & tmp_u2) != 0;
        }
      }
      tmp_b3 = false;
    }
  }
  return tmp_b3;
}

bool nitrox_CheckCommandPermission(int param_1,int param_2)
{
  int tmp_i1;
  bool tmp_b2;
  
  tmp_b2 = false;
  if (g_unk_02af58b8 != 0) {
    if (param_1 == 0) {
      return true;
    }
    tmp_i1 = *(int *)(param_1 + 0x5e8);
    if (tmp_i1 == 0) {
      return false;
    }
    if (((*(uint *)(tmp_i1 + 0x10e4) == 0) ||
        (tmp_b2 = true, (*(uint *)(tmp_i1 + 0x10e4) & 0x8000) == 0)) &&
       (tmp_b2 = true, *(int *)(tmp_i1 + 0x10e8 + param_2 * 4) < 1)) {
      tmp_i1 = *(int *)(tmp_i1 + 0x4c);
      if (tmp_i1 == 0) {
        return false;
      }
      if ((*(uint *)(tmp_i1 + 0xc2c) == 0) || ((*(uint *)(tmp_i1 + 0xc2c) & 0x8000) == 0)) {
        return 0 < *(int *)(tmp_i1 + (param_2 + 0x30c) * 4);
      }
    }
  }
  return tmp_b2;
}

