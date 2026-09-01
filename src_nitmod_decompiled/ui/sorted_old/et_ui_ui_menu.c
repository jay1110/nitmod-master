/* Menu definitions, menu item handling, menu events
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"
#include "et_ui_imports.h"
#include "et_ui_ui_menu.h"

void UI_RunMenuScript(void)

{
{  char tmp_c1;
  size_t tmp_s2;
  int tmp_i3;
  int tmp_i4;
  uint tmp_u5;
  uint tmp_u6;
  uint32_t *tmp_pu7;
  uint32_t tmp_u8;
  char *tmp_pc9;
  long tmp_l10;
  int tmp_i11;
  uint32_t *tmp_pu12;
  uint *tmp_pu13;
  uint *tmp_pu14;
  bool tmp_b15;
  byte tmp_b16;
  long double tmp_l17;
  long double tmp_l18;
  uint32_t local_7b40;
  int local_7b20;
  int local_7b1c;
  char local_7a64 [256];
  uint local_7964 [262];
  uint local_754c [7503];
  
  tmp_b16 = 0;
  tmp_pu12 = (uint32_t *)&stack0xffff84c4;
  local_7b40 = 0x310ff;
  tmp_i3 = String_Parse();
  if (tmp_i3 == 0) {
    return;
  }
  local_7b40 = 0x31129;
  tmp_i3 = Q_stricmp();
  if (tmp_i3 == 0) {
    if (GHIDRA_FIELD(ui_dedicated, 12, 4) == 0) {
      local_7b40 = 0x313e6;
      tmp_l17 = (long double)trap_Cvar_VariableValue();
      local_7b40 = 0x313f8;
      tmp_l18 = (long double)trap_Cvar_VariableValue();
      if (((int)ROUND(tmp_l18) == 0) && ((int)ROUND((float)tmp_l17) != 0)) {
        local_7b40 = 0x31477;
        trap_Cvar_Set();
        local_7b40 = 0x3148e;
        Menus_ActivateByName();
        return;
      }
    }
    local_7b40 = 0x3115d;
    trap_Cvar_Set();
    local_7b40 = 0x31175;
    trap_Cvar_Set();
    local_7b40 = 0x31187;
    trap_Cvar_Set();
    local_7b40 = 0x31199;
    trap_Cvar_Set();
    local_7b40 = 0x311b7;
    Com_Clamp();
    local_7b40 = 0x311c9;
    trap_Cvar_SetValue();
    local_7b40 = 0x311e7;
    Com_Clamp();
    local_7b40 = 0x311f9;
    trap_Cvar_SetValue();
    local_7b40 = 0x31228;
    va();
    local_7b40 = 0x31238;
    trap_Cmd_ExecuteText();
    local_7b40 = 0x31246;
    tmp_l17 = (long double)trap_Cvar_VariableValue();
    if (((int)ROUND(tmp_l17) == 0) ||
       (*(int *)(&g_dat_003babd0 + GHIDRA_FIELD(ui_mapIndex, 12, 4) * 0x80) == (int)ROUND(tmp_l17))) {
      local_7b40 = 0x314e2;
      trap_Cvar_Set();
    }
    else {
      local_7b40 = 0x312ad;
      va();
      local_7b40 = 0x312bf;
      trap_Cvar_Set();
    }
    local_7b40 = 0x312cd;
    tmp_l17 = (long double)trap_Cvar_VariableValue();
    if (((int)ROUND(tmp_l17) == 0) ||
       (*(int *)(&g_dat_003babd4 + GHIDRA_FIELD(ui_mapIndex, 12, 4) * 0x80) == (int)ROUND(tmp_l17))) {
      local_7b40 = 0x314ca;
      trap_Cvar_Set();
    }
    else {
      local_7b40 = 0x31334;
      va();
      local_7b40 = 0x31346;
      trap_Cvar_Set();
    }
    local_7b40 = 0x31354;
    tmp_l17 = (long double)trap_Cvar_VariableValue();
    if (((int)ROUND(tmp_l17) != 0) &&
       (*(int *)(&g_dat_003babd8 + GHIDRA_FIELD(ui_mapIndex, 12, 4) * 0x80) != (int)ROUND(tmp_l17))) {
      local_7b40 = 0x313bb;
      va();
      local_7b40 = 0x313cd;
      trap_Cvar_Set();
      return;
    }
    local_7b40 = 0x314aa;
    trap_Cvar_Set();
    return;
  }
  local_7b40 = 0x31509;
  tmp_i4 = Q_stricmp();
  tmp_i3 = g_dat_003bab6c;
  if (tmp_i4 != 0) {
    local_7b40 = 0x317f9;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      local_7b40 = 0x3181d;
      trap_Cmd_ExecuteText();
      local_7b40 = 0x31833;
      trap_Cmd_ExecuteText();
      local_7b40 = 0x31849;
      trap_Cmd_ExecuteText();
      local_7b40 = 0x3185f;
      trap_Cmd_ExecuteText();
      local_7b40 = 0x3186b;
      Controls_SetDefaults();
      local_7b40 = 0x3187d;
      trap_Cvar_Set();
      local_7b40 = 0x3188f;
      trap_Cvar_Set();
      local_7b40 = 0x318a5;
      trap_Cmd_ExecuteText();
      return;
    }
    local_7b40 = 0x318c3;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      local_7b40 = 0x318ef;
      trap_GetCDKey();
      local_7b40 = 0x318fb;
      trap_Cvar_Set();
      local_7b40 = 0x31911;
      trap_Cvar_Set();
      local_7b40 = 0x31927;
      trap_Cvar_Set();
      local_7b40 = 0x3193b;
      trap_Cvar_Set();
      tmp_pu13 = local_754c;
      do {
        tmp_pu14 = tmp_pu13;
        tmp_u5 = *tmp_pu14 + 0xfefefeff & ~*tmp_pu14;
        tmp_u6 = tmp_u5 & 0x80808080;
        tmp_pu13 = tmp_pu14 + 1;
      } while (tmp_u6 == 0);
      if ((tmp_u5 & 0x8080) == 0) {
        tmp_pu13 = (uint *)((int)tmp_pu14 + 6);
        tmp_u6 = tmp_u6 >> 0x10;
      }
      if ((int)tmp_pu13 + ((-3 - (uint)CARRY1((byte)tmp_u6,(byte)tmp_u6)) - (int)local_754c) != 0x10) {
        return;
      }
      local_7b40 = 0x31992;
      Q_strncpyz();
      local_7b40 = 0x319a3;
      trap_Cvar_Set();
      local_7b40 = 0x319ba;
      Q_strncpyz();
      local_7b40 = 0x319ca;
      trap_Cvar_Set();
      local_7b40 = 0x319e6;
      Q_strncpyz();
      local_7b40 = 0x319f6;
      trap_Cvar_Set();
      local_7b40 = 0x31a12;
      Q_strncpyz();
      local_7b40 = 0x31a1e;
      trap_Cvar_Set();
      return;
    }
    local_7b40 = 0x31a56;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      local_754c[0] = local_754c[0] & 0xffffff00;
      local_7b40 = 0x31a7c;
      UI_Cvar_VariableString();
      local_7b40 = 0x31a91;
      Q_strcat();
      local_7b40 = 0x31a9f;
      UI_Cvar_VariableString();
      local_7b40 = 0x31ab4;
      Q_strcat();
      local_7b40 = 0x31ac2;
      UI_Cvar_VariableString();
      local_7b40 = 0x31ad7;
      Q_strcat();
      local_7b40 = 0x31ae5;
      UI_Cvar_VariableString();
      local_7b40 = 0x31afa;
      Q_strcat();
      local_7b40 = 0x31b0c;
      trap_Cvar_Set();
      local_7b40 = 0x31b1a;
      UI_Cvar_VariableString();
      local_7b40 = 0x31b26;
      tmp_i3 = trap_VerifyCDKey();
      if (tmp_i3 != 0) {
        local_7b40 = 0x31b46;
        trap_Cvar_Set();
        local_7b40 = 0x31b4e;
        trap_SetCDKey();
        return;
      }
      local_7b40 = 0x31c93;
      trap_Cvar_Set();
      return;
    }
    local_7b40 = 0x31b85;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      local_7b40 = 0x31b92;
      UI_LoadArenas();
      if ((GHIDRA_FIELD(ui_netGameType, 12, 4) != 4) && (0 < g_dat_003bab6c)) {
        tmp_pu7 = (uint32_t *)&g_dat_003babcc;
        tmp_i3 = g_dat_003bab6c * 0x80;
        tmp_b16 = (byte)GHIDRA_FIELD(ui_netGameType, 12, 4);
        do {
          *tmp_pu7 = 0;
          if ((tmp_pu7[-0x14] & 1 << (tmp_b16 & 0x1f)) != 0) {
            *tmp_pu7 = 1;
          }
          tmp_pu7 = tmp_pu7 + 0x20;
        } while (tmp_pu7 != (uint32_t *)(&g_dat_003babcc + tmp_i3));
      }
      local_7b40 = 0x31bfb;
      Menu_SetFeederSelection();
      local_7b40 = 0x31c00;
      UI_LoadCampaigns();
      local_7b40 = 0x31c1f;
      Menu_SetFeederSelection();
      return;
    }
    local_7b40 = 0x31c4d;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      local_7b40 = 0x31c76;
      Menu_SetFeederSelection();
      return;
    }
    local_7b40 = 0x31cc3;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      local_7b40 = 0x31cd3;
      Controls_SetConfig();
      return;
    }
    local_7b40 = 0x31cf1;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      local_7b40 = 0x31cfa;
      Controls_GetConfig();
      return;
    }
    local_7b40 = 0x31d1e;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      local_7b40 = 0x31d3a;
      trap_Cvar_Set();
      local_7b40 = 0x31d4c;
      trap_Cvar_Set();
      local_7b40 = 0x31d5e;
      trap_Cvar_Set();
      return;
    }
    local_7b40 = 0x31d7c;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      local_7b40 = 0x31d85;
      UI_ParseGameInfo_constprop_57();
      return;
    }
    local_7b40 = 0x31da3;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      return;
    }
    local_7b40 = 0x31dc4;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      local_7b40 = 0x31dd2;
      UI_StartServerRefresh();
      UI_BuildServerDisplayList();
      return;
    }
    local_7b40 = 0x31dfa;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      local_7b40 = 0x31e0f;
      UI_StartServerRefresh();
      UI_BuildServerDisplayList();
      return;
    }
    local_7b40 = 0x31e37;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      if (_DAT_003b7f30 == 0) {
        return;
      }
      local_7b40 = 0x31e83;
      va();
      local_7b40 = 0x31e93;
      trap_Cmd_ExecuteText();
      return;
    }
    local_7b40 = 0x31eb1;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      tmp_pu13 = local_754c;
      local_7b40 = 0x31ece;
      trap_Cvar_VariableValue();
      local_7b40 = 0x31f22;
      Com_sprintf();
      local_7b40 = 0x31f40;
      g_dat_003e0f98 = trap_FS_GetFileList();
      local_7b40 = 0x31f4e;
      trap_Cvar_VariableValue();
      local_7b40 = 0x31f95;
      Com_sprintf();
      if (g_dat_003e0f98 == 0) {
        return;
      }
      if (0x200 < g_dat_003e0f98) {
        g_dat_003e0f98 = 0x200;
      }
      local_7b1c = 0;
      do {
        if (g_dat_003e0f98 <= local_7b1c) {
          return;
        }
        tmp_u6 = 0xffffffff;
        tmp_pu14 = tmp_pu13;
        do {
          if (tmp_u6 == 0) break;
          tmp_u6 = tmp_u6 - 1;
          tmp_u5 = *tmp_pu14;
          tmp_pu14 = (uint *)((int)tmp_pu14 + (uint)tmp_b16 * -2 + 1);
        } while ((char)tmp_u5 != '\0');
        tmp_i3 = -1;
        tmp_pu14 = local_7964;
        do {
          if (tmp_i3 == 0) break;
          tmp_i3 = tmp_i3 + -1;
          tmp_u5 = *tmp_pu14;
          tmp_pu14 = (uint *)((int)tmp_pu14 + (uint)tmp_b16 * -2 + 1);
        } while ((char)tmp_u5 != '\0');
        local_7b40 = 0x32010;
        tmp_i3 = Q_stricmp();
        if (tmp_i3 == 0) {
          tmp_i3 = -1;
          tmp_pu14 = local_7964;
          do {
            if (tmp_i3 == 0) break;
            tmp_i3 = tmp_i3 + -1;
            tmp_u5 = *tmp_pu14;
            tmp_pu14 = (uint *)((int)tmp_pu14 + (uint)tmp_b16 * -2 + 1);
          } while ((char)tmp_u5 != '\0');
          *(char *)((int)tmp_pu13 + ~tmp_u6 + 1 + tmp_i3) = '\0';
        }
        tmp_pu13 = (uint *)((int)tmp_pu13 + ~tmp_u6);
        local_7b40 = 0x32039;
        tmp_u8 = String_Alloc();
        *(uint32_t *)(&g_dat_003e0798 + local_7b1c * 4) = tmp_u8;
        local_7b1c = local_7b1c + 1;
      } while( true );
    }
    local_7b40 = 0x32067;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 == 0) {
      tmp_pu13 = local_754c;
      local_7b40 = 0x3209a;
      g_dat_003e13a0 = trap_FS_GetFileList();
      if (g_dat_003e13a0 == 0) {
        return;
      }
      if (0x100 < g_dat_003e13a0) {
        g_dat_003e13a0 = 0x100;
      }
      tmp_i3 = 0;
      do {
        if (g_dat_003e13a0 <= tmp_i3) {
          return;
        }
        tmp_u6 = 0xffffffff;
        tmp_pu14 = tmp_pu13;
        do {
          if (tmp_u6 == 0) break;
          tmp_u6 = tmp_u6 - 1;
          tmp_u5 = *tmp_pu14;
          tmp_pu14 = (uint *)((int)tmp_pu14 + (uint)tmp_b16 * -2 + 1);
        } while ((char)tmp_u5 != '\0');
        local_7b40 = 0x32108;
        tmp_i4 = Q_stricmp();
        if (tmp_i4 == 0) {
          *(char *)((int)tmp_pu13 + (~tmp_u6 - 5)) = '\0';
        }
        local_7b40 = 0x3211b;
        Q_strupr();
        tmp_pu13 = (uint *)((int)tmp_pu13 + ~tmp_u6);
        local_7b40 = 0x32127;
        tmp_u8 = String_Alloc();
        *(uint32_t *)(&g_dat_003e0fa0 + tmp_i3 * 4) = tmp_u8;
        tmp_i3 = tmp_i3 + 1;
      } while( true );
    }
    local_7b40 = 0x3214a;
    tmp_i3 = Q_stricmp();
    if (tmp_i3 != 0) {
      local_7b40 = 0x32297;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (-1 < g_dat_003e13a8) {
          local_7b40 = 0x322ad;
          trap_CIN_StopCinematic();
        }
        local_7b40 = 0x322cc;
        va();
        local_7b40 = 0x322dc;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x322fa;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32322;
        trap_Cvar_Set();
        local_7b40 = 0x32338;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x323c0;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003e0f9c < 0) {
          return;
        }
        if (g_dat_003e0f98 <= _DAT_003e0f9c) {
          return;
        }
        local_7b40 = 0x323fb;
        va();
        local_7b40 = 0x3240b;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x32464;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003e0f9c < 0) {
          return;
        }
        if (g_dat_003e0f98 <= _DAT_003e0f9c) {
          return;
        }
        local_7b40 = 0x32494;
        trap_Cvar_VariableValue();
        local_7b40 = 0x324e0;
        va();
        local_7b40 = 0x324e8;
        trap_FS_Delete();
        return;
      }
      local_7b40 = 0x3253d;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (g_dat_003e13b8 != 0) {
          local_7b40 = 0x32553;
          UI_StopServerRefresh_part_19();
          _DAT_003e53d8 = 0;
          _DAT_003e6940 = 0;
          _DAT_003e7e10 = 0;
          local_7b40 = 0x3257b;
          UI_BuildServerDisplayList();
          return;
        }
        local_7b40 = 0x325c9;
        Menus_CloseByName();
        local_7b40 = 0x325d7;
        Menus_OpenByName();
        return;
      }
      local_7b40 = 0x325f5;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (g_dat_003e13b8 != 0) {
          local_7b40 = 0x32607;
          UI_StopServerRefresh_part_19();
        }
        _DAT_003e53d8 = 0;
        _DAT_003e6940 = 0;
        _DAT_003e7e10 = 0;
        return;
      }
      local_7b40 = 0x32643;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32659;
        trap_Cvar_Update();
        if ((GHIDRA_FIELD(ui_netSource, 12, 4) == 0) || (g_dat_003e53c0 == 0)) {
          tmp_pu12 = &local_7b40;
          local_7b40 = 0x32675;
          UI_StartServerRefresh();
        }
        tmp_pu12[-1] = 0x3267f;
        UI_BuildServerDisplayList();
        *tmp_pu12 = 0x40000000;
        tmp_pu12[-1] = 0x3268d;
        UI_FeederSelection_part_24();
        return;
      }
      local_7b40 = 0x326e6;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x326fc;
        tmp_pc9 = (char *)UI_Cvar_VariableString();
        local_7b40 = 0x3270c;
        tmp_i3 = Menus_FindByName();
        if (*tmp_pc9 != '\0') {
          local_7b40 = 0x32725;
          tmp_i4 = strcmp(tmp_pc9,"localhost");
          if (tmp_i4 != 0) {
            if (tmp_i3 == 0) {
              return;
            }
            local_7b40 = 0x3274b;
            Menu_ShowItemByName();
            return;
          }
        }
        if (tmp_i3 == 0) {
          return;
        }
        local_7b40 = 0x327ad;
        Menu_ShowItemByName();
        return;
      }
      local_7b40 = 0x327cb;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x327e1;
        tmp_l17 = (long double)trap_Cvar_VariableValue();
        if (tmp_l17 == (long double)1) {
          local_7b40 = 0x3281e;
          trap_LAN_GetServerAddressString();
          local_7b40 = 0x32828;
          UI_BuildServerStatus();
          return;
        }
        local_7b40 = 0x32876;
        tmp_pc9 = (char *)UI_Cvar_VariableString();
        if (*tmp_pc9 != '\0') {
          local_7b40 = 0x3288d;
          tmp_i3 = strcmp(tmp_pc9,"localhost");
          if (tmp_i3 != 0) {
            local_7b40 = 0x3291a;
            trap_Cvar_VariableStringBuffer();
            g_dat_003e53c0 = 1;
            local_7b40 = 0x3292e;
            UI_BuildServerStatus();
            return;
          }
        }
        local_7b40 = 0x3289f;
        Com_Printf();
        return;
      }
      local_7b40 = 0x328bd;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x328d0;
        trap_GetClientState();
        local_7b40 = 0x328f1;
        Q_strncpyz();
        local_7b40 = 0x328fb;
        UI_BuildServerStatus();
        return;
      }
      local_7b40 = 0x3294c;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x3295e;
        tmp_pc9 = (char *)UI_Cvar_VariableString();
        local_7b40 = 0x3296e;
        tmp_i3 = Menus_FindByName();
        if (*tmp_pc9 != '\0') {
          local_7b40 = 0x32988;
          tmp_i4 = strcmp(tmp_pc9,"localhost");
          if (tmp_i4 != 0) {
            local_7b40 = 0x32a57;
            trap_Cvar_VariableStringBuffer();
            g_dat_003e53c0 = 1;
            if (tmp_i3 != 0) {
              local_7b40 = 0x32a7f;
              Menu_ShowItemByName();
            }
            local_7b40 = 0x32a89;
            UI_BuildServerStatus();
            return;
          }
        }
        if (tmp_i3 == 0) {
          return;
        }
        local_7b40 = 0x329b2;
        Menu_ShowItemByName();
        return;
      }
      local_7b40 = 0x329d0;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32a0a;
        Q_strncpyz();
        local_7b40 = 0x32a14;
        UI_BuildServerStatus();
        local_7b40 = 0x32a38;
        Menu_SetFeederSelection();
        return;
      }
      local_7b40 = 0x32aa7;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32ab5;
        UI_BuildFindPlayerList();
        g_dat_003e693c = 0;
        local_7b40 = 0x32ae3;
        Menu_SetFeederSelection();
        return;
      }
      local_7b40 = 0x32b01;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003e13bc < 0) {
          return;
        }
        if (g_dat_003e53c0 <= _DAT_003e13bc) {
          return;
        }
        local_7b40 = 0x32b28;
        Menus_CloseAll();
        local_7b40 = 0x32b46;
        trap_Cvar_Set();
        local_7b40 = 0x32b5e;
        trap_Cvar_Set();
        local_7b40 = 0x32b70;
        trap_Cvar_Set();
        local_7b40 = 0x32b89;
        trap_Cvar_Set();
        local_7b40 = 0x32bb4;
        trap_LAN_GetServerAddressString();
        local_7b40 = 0x32bc6;
        va();
        local_7b40 = 0x32bd6;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x32bf4;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32c01;
        Menus_CloseAll();
        local_7b40 = 0x32c1f;
        trap_Cvar_Set();
        local_7b40 = 0x32c31;
        trap_Cvar_Set();
        local_7b40 = 0x32c43;
        trap_Cvar_Set();
        local_7b40 = 0x32c55;
        trap_Cvar_Set();
        local_7b40 = 0x32c63;
        UI_Cvar_VariableString();
        local_7b40 = 0x32c75;
        va();
        local_7b40 = 0x32c85;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x32ca3;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32cbf;
        trap_Cvar_Set();
        if (_DAT_003e7e08 < 0) {
          return;
        }
        if (g_dat_003e7e0c <= _DAT_003e7e08) {
          return;
        }
        local_7b40 = 0x32cfa;
        va();
        local_7b40 = 0x32d0a;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x32d28;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32d44;
        trap_Cvar_Set();
        local_7b40 = 0x32d5a;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x32d78;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32d94;
        trap_Cvar_Set();
        local_7b40 = 0x32da0;
        trap_Key_SetCatcher();
        local_7b40 = 0x32da5;
        Menus_CloseAll();
        local_7b40 = 0x32dbb;
        Menus_ActivateByName();
        return;
      }
      local_7b40 = 0x32dd9;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32deb;
        tmp_l17 = (long double)trap_Cvar_VariableValue();
        if (tmp_l17 == (long double)0) {
          local_7b40 = 0x32efe;
          trap_Cmd_ExecuteText();
          local_7b40 = 0x32f0a;
          trap_Key_SetCatcher();
          local_7b40 = 0x32f0f;
          Menus_CloseAll();
          local_7b40 = 0x32f25;
          Menus_ActivateByName();
          local_7b40 = 0x32f3b;
          Menus_ActivateByName();
          return;
        }
        local_7b40 = 0x32e13;
        trap_Cvar_Set();
        return;
      }
      local_7b40 = 0x32e31;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32e48;
        tmp_i3 = Int_Parse();
        if (tmp_i3 == 0) {
          return;
        }
        if (_DAT_003e13b0 == local_754c[0]) {
          _DAT_003e13b4 = (uint)(_DAT_003e13b4 == 0);
        }
        local_7b40 = 0x32e81;
        UI_ServersSort();
        return;
      }
      local_7b40 = 0x32e9f;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32eba;
        tmp_i3 = Int_Parse();
        if (tmp_i3 == 0) {
          return;
        }
        _DAT_003e13b4 = 0;
        local_7b40 = 0x32ee3;
        UI_ServersSort();
        return;
      }
      local_7b40 = 0x32f59;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        return;
      }
      local_7b40 = 0x32f7a;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        return;
      }
      local_7b40 = 0x32f9b;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x32fa4;
        trap_Key_GetCatcher();
        local_7b40 = 0x32faf;
        trap_Key_SetCatcher();
        local_7b40 = 0x32fb4;
        trap_Key_ClearStates();
        local_7b40 = 0x32fcc;
        trap_Cvar_Set();
        local_7b40 = 0x32fd1;
        Menus_CloseAll();
        return;
      }
      local_7b40 = 0x32fef;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (GHIDRA_FIELD(ui_netGameType, 12, 4) == 4) {
          if ((int)GHIDRA_FIELD(ui_currentNetMap, 12, 4) < 0) {
            return;
          }
          if (g_dat_003cab70 <= (int)GHIDRA_FIELD(ui_currentNetMap, 12, 4)) {
            return;
          }
          local_7b40 = 0x330e7;
          va();
          local_7b40 = 0x330f7;
          trap_Cmd_ExecuteText();
          return;
        }
        if ((int)GHIDRA_FIELD(ui_currentNetMap, 12, 4) < 0) {
          return;
        }
        if (g_dat_003bab6c <= (int)GHIDRA_FIELD(ui_currentNetMap, 12, 4)) {
          return;
        }
        local_7b40 = 0x33036;
        va();
        local_7b40 = 0x33046;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33064;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x330a2;
        va();
        local_7b40 = 0x330b2;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33115;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x33154;
        trap_Cvar_VariableStringBuffer();
        local_7b40 = 0x33166;
        va();
        local_7b40 = 0x33176;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33194;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x331ce;
        va();
        local_7b40 = 0x331de;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x331fc;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x33236;
        va();
        local_7b40 = 0x33246;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33264;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x3329e;
        va();
        local_7b40 = 0x332ae;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x332cc;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x33306;
        va();
        local_7b40 = 0x33316;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33334;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x3334a;
        tmp_l17 = (long double)trap_Cvar_VariableValue();
        if ((int)ROUND(tmp_l17) < 0) {
          return;
        }
        if (g_dat_003b8b48 <= (int)ROUND(tmp_l17)) {
          return;
        }
        local_7b40 = 0x333a7;
        va();
        local_7b40 = 0x333b7;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x333d5;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x333eb;
        tmp_l17 = (long double)trap_Cvar_VariableValue();
        if ((int)ROUND(tmp_l17) < 0) {
          return;
        }
        if (g_dat_003b8b48 <= (int)ROUND(tmp_l17)) {
          return;
        }
        local_7b40 = 0x33448;
        va();
        local_7b40 = 0x33458;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33476;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x33488;
        trap_Cvar_VariableValue();
        local_7b40 = 0x3349a;
        va();
        local_7b40 = 0x334aa;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x334c8;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x334da;
        trap_Cvar_VariableValue();
        local_7b40 = 0x33515;
        va();
        local_7b40 = 0x33525;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33543;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x33555;
        trap_Cvar_VariableValue();
        local_7b40 = 0x33567;
        va();
        local_7b40 = 0x33577;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33595;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x335a7;
        trap_Cvar_VariableValue();
        local_7b40 = 0x335e2;
        va();
        local_7b40 = 0x335f2;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33610;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x33637;
        trap_GetConfigString();
        local_7b40 = 0x3364f;
        strtol((char *)local_754c,(char **)0x0,10);
        local_7b40 = 0x33667;
        va();
        local_7b40 = 0x33679;
        trap_Cvar_Set();
        local_7b40 = 0x33691;
        trap_GetConfigString();
        local_7b40 = 0x336a3;
        tmp_pc9 = (char *)Info_ValueForKey();
        local_7b40 = 0x336bb;
        strtol(tmp_pc9,(char **)0x0,10);
        local_7b40 = 0x336cd;
        va();
        local_7b40 = 0x336df;
        trap_Cvar_Set();
        local_7b40 = 0x336f7;
        trap_Cvar_Set();
        return;
      }
      local_7b40 = 0x33715;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d5c < 0) {
          return;
        }
        if (g_dat_003b8d58 <= _DAT_003b8d5c) {
          return;
        }
        local_7b40 = 0x3374f;
        va();
        local_7b40 = 0x3375f;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x3377d;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (GHIDRA_FIELD(ui_netSource, 12, 4) == 2) {
          return;
        }
        local_7b40 = 0x337c7;
        trap_LAN_GetServerInfo();
        local_7964[0] = local_7964[0] & 0xffffff00;
        local_7a64[0] = '\0';
        local_7b40 = 0x337e9;
        Info_ValueForKey();
        local_7b40 = 0x337fd;
        Q_strncpyz();
        local_7b40 = 0x33816;
        Info_ValueForKey();
        local_7b40 = 0x3382a;
        Q_strncpyz();
        if (local_7a64[0] == '\0') {
          return;
        }
        if ((char)local_7964[0] == '\0') {
          return;
        }
        local_7b40 = 0x3385a;
        tmp_i3 = trap_LAN_AddServer();
        if (tmp_i3 != 0) {
          if (tmp_i3 != -1) {
            local_7b40 = 0x3387b;
            Com_Printf();
            return;
          }
          local_7b40 = 0x33944;
          Com_Printf();
          return;
        }
        local_7b40 = 0x33957;
        Com_Printf();
        return;
      }
      local_7b40 = 0x33899;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (GHIDRA_FIELD(ui_netSource, 12, 4) != 2) {
          return;
        }
        local_7b40 = 0x338de;
        trap_LAN_GetServerInfo();
        local_7964[0] = local_7964[0] & 0xffffff00;
        local_7b40 = 0x338ff;
        Info_ValueForKey();
        local_7b40 = 0x33913;
        Q_strncpyz();
        if ((char)local_7964[0] == '\0') {
          return;
        }
        local_7b40 = 0x33931;
        trap_LAN_RemoveServer();
        return;
      }
      local_7b40 = 0x33975;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (GHIDRA_FIELD(ui_netSource, 12, 4) != 2) {
          return;
        }
        local_754c[0] = local_754c[0] & 0xffffff00;
        local_7964[0] = local_7964[0] & 0xffffff00;
        local_7b40 = 0x339b6;
        UI_Cvar_VariableString();
        local_7b40 = 0x339ca;
        Q_strncpyz();
        local_7b40 = 0x339d8;
        UI_Cvar_VariableString();
        local_7b40 = 0x339ec;
        Q_strncpyz();
        if ((char)local_7964[0] == '\0') {
          return;
        }
        if ((char)local_754c[0] == '\0') {
          return;
        }
        local_7b40 = 0x33a1c;
        tmp_i3 = trap_LAN_AddServer();
        if (tmp_i3 != 0) {
          if (tmp_i3 != -1) {
            local_7b40 = 0x33a3d;
            Com_Printf();
            return;
          }
          local_7b40 = 0x33b35;
          Com_Printf();
          return;
        }
        local_7b40 = 0x33b48;
        Com_Printf();
        return;
      }
      local_7b40 = 0x33a5b;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x33a80;
        trap_GetClientState();
        local_7964[0] = local_7964[0] & 0xffffff00;
        local_7a64[0] = '\0';
        local_7b40 = 0x33aa4;
        Q_strncpyz();
        local_7b40 = 0x33abf;
        Q_strncpyz();
        if (local_7a64[0] == '\0') {
          return;
        }
        if ((char)local_7964[0] == '\0') {
          return;
        }
        local_7b40 = 0x33aed;
        tmp_i3 = Q_stricmp();
        if (tmp_i3 == 0) {
          return;
        }
        local_7b40 = 0x33b09;
        tmp_i3 = trap_LAN_AddServer();
        if (tmp_i3 != 0) {
          if (tmp_i3 != -1) {
            local_7b40 = 0x33b22;
            Com_Printf();
            return;
          }
          local_7b40 = 0x33b5b;
          Com_Printf();
          return;
        }
        local_7b40 = 0x33b6e;
        Com_Printf();
        return;
      }
      local_7b40 = 0x33b8c;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x33ba8;
        trap_Cvar_Set();
        return;
      }
      local_7b40 = 0x33bc6;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x33bdd;
        tmp_i3 = String_Parse();
        if (tmp_i3 == 0) {
          return;
        }
        local_7b40 = 0x33bf4;
        UI_Update();
        return;
      }
      local_7b40 = 0x33c12;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x33c24;
        tmp_pc9 = (char *)UI_Cvar_VariableString();
        local_7b40 = 0x33c3c;
        tmp_l10 = strtol(tmp_pc9,(char **)0x0,10);
        if (tmp_l10 == 0) {
          return;
        }
        local_7b40 = 0x33c5a;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33c78;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x33c8f;
        tmp_i3 = Int_Parse();
        if (tmp_i3 == 0) {
          return;
        }
        local_7b40 = 0x33ca6;
        trap_SetPbClStatus();
        return;
      }
      local_7b40 = 0x33cc4;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if ((int)GHIDRA_FIELD(ui_netGameType, 12, 4) < 0) {
          return;
        }
        if (g_dat_003b8b48 <= (int)GHIDRA_FIELD(ui_netGameType, 12, 4)) {
          return;
        }
        local_7b40 = 0x33cf4;
        va();
        local_7b40 = 0x33d04;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33d22;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if ((int)GHIDRA_FIELD(ui_currentNetMap, 12, 4) < 0) {
          return;
        }
        if (g_dat_003bab6c <= (int)GHIDRA_FIELD(ui_currentNetMap, 12, 4)) {
          return;
        }
        local_7b40 = 0x33d5c;
        va();
        local_7b40 = 0x33d6c;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33d8a;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (GHIDRA_FIELD(ui_netGameType, 12, 4) == 4) {
          if ((int)GHIDRA_FIELD(ui_currentNetMap, 12, 4) < 0) {
            return;
          }
          if (g_dat_003cab70 <= (int)GHIDRA_FIELD(ui_currentNetMap, 12, 4)) {
            return;
          }
          local_7b40 = 0x33e82;
          va();
          local_7b40 = 0x33e92;
          trap_Cmd_ExecuteText();
          return;
        }
        if ((int)GHIDRA_FIELD(ui_currentNetMap, 12, 4) < 0) {
          return;
        }
        if (g_dat_003bab6c <= (int)GHIDRA_FIELD(ui_currentNetMap, 12, 4)) {
          return;
        }
        local_7b40 = 0x33dd1;
        va();
        local_7b40 = 0x33de1;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33dff;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x33e3d;
        va();
        local_7b40 = 0x33e4d;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33eb0;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x33eea;
        va();
        local_7b40 = 0x33efa;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33f18;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x33f52;
        va();
        local_7b40 = 0x33f62;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33f80;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x33fba;
        va();
        local_7b40 = 0x33fca;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x33fe8;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x34022;
        va();
        local_7b40 = 0x34032;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x34050;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x3408a;
        va();
        local_7b40 = 0x3409a;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x340b8;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x340f2;
        va();
        local_7b40 = 0x34102;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x34120;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x3415a;
        va();
        local_7b40 = 0x3416a;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x34188;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x341c2;
        va();
        local_7b40 = 0x341d2;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x341f0;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x3422a;
        va();
        local_7b40 = 0x3423a;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x34258;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x34292;
        va();
        local_7b40 = 0x342a2;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x342c0;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x342fa;
        va();
        local_7b40 = 0x3430a;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x34328;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x34362;
        va();
        local_7b40 = 0x34372;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x34390;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x343ca;
        va();
        local_7b40 = 0x343da;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x343f8;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x34437;
        trap_Cvar_VariableStringBuffer();
        local_7b40 = 0x3445b;
        va();
        local_7b40 = 0x3446b;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x34489;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x344ae;
        trap_Cvar_VariableStringBuffer();
        local_7b40 = 0x344c0;
        va();
        local_7b40 = 0x344d0;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x344ee;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x34528;
        va();
        local_7b40 = 0x34538;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x34556;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        if (_DAT_003b8d64 < 0) {
          return;
        }
        if (g_dat_003b8d54 <= _DAT_003b8d64) {
          return;
        }
        local_7b40 = 0x34590;
        va();
        local_7b40 = 0x345a0;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x345be;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x345c7;
        trap_LAN_LoadCachedServers();
        return;
      }
      local_7b40 = 0x345e5;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x34609;
        va();
        local_7b40 = 0x3461b;
        trap_Cvar_Set();
        return;
      }
      local_7b40 = 0x34639;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 == 0) {
        local_7b40 = 0x3464f;
        tmp_l17 = (long double)trap_Cvar_VariableValue();
        if ((int)(&g_dat_003cabd8)[GHIDRA_FIELD(ui_currentCampaign, 12, 4) * 0x1d] < (int)ROUND(tmp_l17)) {
          return;
        }
        local_7b40 = 0x346c2;
        va();
        local_7b40 = 0x346d2;
        trap_Cmd_ExecuteText();
        return;
      }
      local_7b40 = 0x346f0;
      tmp_i3 = Q_stricmp();
      if (tmp_i3 != 0) {
        local_7b40 = 0x34799;
        tmp_i3 = Q_stricmp();
        if (tmp_i3 != 0) {
          local_7b40 = 0x3487b;
          tmp_i3 = Q_stricmp();
          if (tmp_i3 == 0) {
            local_7b40 = 0x3489b;
            va();
            local_7b40 = 0x348b6;
            tmp_i3 = trap_FS_FOpenFile();
            if (tmp_i3 < 0) {
              return;
            }
            local_7b40 = 0x348cd;
            trap_FS_FCloseFile();
            local_7b40 = 0x348d9;
            va();
            local_7b40 = 0x348e1;
            trap_FS_Delete();
            return;
          }
          local_7b40 = 0x34a6e;
          tmp_i3 = Q_stricmp();
          if (tmp_i3 == 0) {
            local_7b40 = 0x34a92;
            Q_strncpyz();
            local_7b40 = 0x34a9a;
            Q_CleanStr();
            local_7b40 = 0x34aa2;
            Q_CleanDirName();
            local_7b40 = 0x34ab4;
            trap_Cvar_Set();
            return;
          }
          local_7b40 = 0x34ad2;
          tmp_i3 = Q_stricmp();
          if (tmp_i3 != 0) {
            local_7b40 = 0x34c46;
            tmp_i3 = Q_stricmp();
            if (tmp_i3 != 0) {
              local_7b40 = 0x34ce7;
              tmp_i3 = Q_stricmp();
              if (tmp_i3 == 0) {
                local_7b40 = 0x34d07;
                trap_Cvar_Set();
                return;
              }
              local_7b40 = 0x34db3;
              tmp_i3 = Q_stricmp();
              if (tmp_i3 != 0) {
                local_7b40 = 0x34f25;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x34f3b;
                  tmp_l17 = (long double)trap_Cvar_VariableValue();
                  if ((int)ROUND(tmp_l17) != 0) {
                    local_7b40 = 0x34f86;
                    trap_SetPbSvStatus();
                    return;
                  }
                  local_7b40 = 0x35068;
                  trap_SetPbSvStatus();
                  return;
                }
                local_7b40 = 0x35086;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x3509c;
                  tmp_l17 = (long double)trap_Cvar_VariableValue();
                  if ((int)ROUND(tmp_l17) == 0) {
                    local_7b40 = 0x35259;
                    trap_Cvar_Set();
                  }
                  else {
                    local_7b40 = 0x350f3;
                    trap_Cvar_Set();
                  }
                  local_7b40 = 0x35101;
                  tmp_l17 = (long double)trap_Cvar_VariableValue();
                  if ((int)ROUND(tmp_l17) != 100) {
                    local_7b40 = 0x35159;
                    trap_Cvar_Set();
                    return;
                  }
                  local_7b40 = 0x35276;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x35294;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x352aa;
                  tmp_l17 = (long double)trap_Cvar_VariableValue();
                  if ((int)ROUND(tmp_l17) != 0) {
                    local_7b40 = 0x35301;
                    trap_Cvar_Set();
                    return;
                  }
                  local_7b40 = 0x3541e;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x3543c;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x3544e;
                  tmp_l17 = (long double)trap_Cvar_VariableValue();
                  if ((int)ROUND(tmp_l17) != 0) {
                    local_7b40 = 0x354a1;
                    trap_Cvar_Set();
                    return;
                  }
                  local_7b40 = 0x35500;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x354bf;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x354d1;
                  UI_Cvar_VariableString();
                  local_7b40 = 0x354e3;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x3551e;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x35530;
                  UI_Cvar_VariableString();
                  local_7b40 = 0x35542;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x35560;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x35572;
                  UI_Cvar_VariableString();
                  local_7b40 = 0x3557a;
                  trap_openURL();
                  return;
                }
                local_7b40 = 0x35598;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x355aa;
                  tmp_l17 = (long double)trap_Cvar_VariableValue();
                  if ((1 << ((byte)numVotesAvailable & 0x1f)) + -1 != (int)ROUND(tmp_l17)) {
                    local_7b40 = 0x3560c;
                    trap_Cvar_SetValue();
                    return;
                  }
                  local_7b40 = 0x3565f;
                  trap_Cvar_SetValue();
                  return;
                }
                local_7b40 = 0x3562a;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x35644;
                  trap_Cmd_ExecuteText();
                  return;
                }
                local_7b40 = 0x3567d;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x356a2;
                  trap_Cvar_VariableStringBuffer();
                  local_7b40 = 0x356b4;
                  va();
                  local_7b40 = 0x356c4;
                  trap_Cmd_ExecuteText();
                  local_7b40 = 0x356d6;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x356f4;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x3570a;
                  trap_Cvar_Update();
                  tmp_i3 = g_dat_003bab6c;
                  tmp_u8 = GHIDRA_FIELD(ui_mapIndex, 12, 4);
                  if (GHIDRA_FIELD(ui_netGameType, 12, 4) == 4) {
                    tmp_i4 = 0;
                    for (tmp_i3 = 0; tmp_i3 < g_dat_003cab70; tmp_i3 = tmp_i3 + 1) {
                      tmp_i4 = (tmp_i4 + 1) -
                              (uint)((*(uint *)(&g_dat_003cabe4 + tmp_i3 * 0x74) & 4) == 0);
                    }
                  }
                  else {
                    tmp_b16 = (byte)GHIDRA_FIELD(ui_netGameType, 12, 4);
                    tmp_i4 = 0;
                    tmp_pu7 = &uiInfo;
                    for (tmp_i11 = 0; tmp_i11 < tmp_i3; tmp_i11 = tmp_i11 + 1) {
                      tmp_pu7[0x8b43] = 0;
                      if ((tmp_pu7[0x8b2f] & 1 << (tmp_b16 & 0x1f)) != 0) {
                        tmp_i4 = tmp_i4 + 1;
                        tmp_pu7[0x8b43] = 1;
                      }
                      tmp_pu7 = tmp_pu7 + 0x20;
                    }
                  }
                  if ((int)tmp_u8 < tmp_i4) {
                    return;
                  }
                  local_7b40 = 0x3578b;
                  Menu_SetFeederSelection();
                  local_7b40 = 0x357af;
                  Menu_SetFeederSelection();
                  return;
                }
                local_7b40 = 0x357f1;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x35803;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35846;
                  trap_Cvar_SetValue();
                  return;
                }
                local_7b40 = 0x35864;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x3587a;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x358d5;
                  trap_Cvar_SetValue();
                  local_7b40 = 0x358e7;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x35905;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x35921;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x3593f;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x3595c;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x3597a;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x3598c;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x3599e;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x359b0;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x359c2;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x359d4;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x359e6;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x359f8;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35a0a;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35a1c;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35a2e;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35a40;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35a52;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35a64;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35a76;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35a88;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35a9a;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35aac;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35abe;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x35adc;
                  trap_Cvar_VariableStringBuffer();
                  local_7b40 = 0x35b15;
                  va();
                  local_7b40 = 0x35b27;
                  trap_Cvar_Set();
                  local_7b40 = 0x35b37;
                  va();
                  local_7b40 = 0x35b49;
                  trap_Cvar_Set();
                  local_7b40 = 0x35b82;
                  va();
                  local_7b40 = 0x35b94;
                  trap_Cvar_Set();
                  local_7b40 = 0x35bcd;
                  va();
                  local_7b40 = 0x35bdf;
                  trap_Cvar_Set();
                  local_7b40 = 0x35c18;
                  va();
                  local_7b40 = 0x35c2a;
                  trap_Cvar_Set();
                  local_7b40 = 0x35c3a;
                  va();
                  local_7b40 = 0x35c4c;
                  trap_Cvar_Set();
                  local_7b40 = 0x35c85;
                  va();
                  local_7b40 = 0x35c97;
                  trap_Cvar_Set();
                  local_7b40 = 0x35cd0;
                  va();
                  local_7b40 = 0x35ce2;
                  trap_Cvar_Set();
                  local_7b40 = 0x35d1b;
                  va();
                  local_7b40 = 0x35d2d;
                  trap_Cvar_Set();
                  local_7b40 = 0x35d66;
                  va();
                  local_7b40 = 0x35d78;
                  trap_Cvar_Set();
                  local_7b40 = 0x35db1;
                  va();
                  local_7b40 = 0x35dc3;
                  trap_Cvar_Set();
                  local_7b40 = 0x35dfc;
                  va();
                  local_7b40 = 0x35e0e;
                  trap_Cvar_Set();
                  local_7b40 = 0x35e47;
                  va();
                  local_7b40 = 0x35e59;
                  trap_Cvar_Set();
                  local_7b40 = 0x35e92;
                  va();
                  local_7b40 = 0x35ea4;
                  trap_Cvar_Set();
                  local_7b40 = 0x35edd;
                  va();
                  local_7b40 = 0x35eef;
                  trap_Cvar_Set();
                  local_7b40 = 0x35f28;
                  va();
                  local_7b40 = 0x35f3a;
                  trap_Cvar_Set();
                  local_7b40 = 0x35f73;
                  va();
                  local_7b40 = 0x35f85;
                  trap_Cvar_Set();
                  local_7b40 = 0x35fbe;
                  va();
                  local_7b40 = 0x35fd0;
                  trap_Cvar_Set();
                  local_7b40 = 0x36009;
                  va();
                  local_7b40 = 0x3601b;
                  trap_Cvar_Set();
                  local_7b40 = 0x36054;
                  va();
                  local_7b40 = 0x36066;
                  trap_Cvar_Set();
                  local_7b40 = 0x36078;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x36096;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x360b6;
                  trap_Cvar_Set();
                  local_7b40 = 0x360c8;
                  trap_Cvar_Set();
                  local_7b40 = 0x360da;
                  trap_Cvar_Set();
                  local_7b40 = 0x360ec;
                  trap_Cvar_Set();
                  local_7b40 = 0x360fe;
                  trap_Cvar_Set();
                  local_7b40 = 0x36110;
                  trap_Cvar_Set();
                  local_7b40 = 0x36122;
                  trap_Cvar_Set();
                  local_7b40 = 0x36134;
                  trap_Cvar_Set();
                  local_7b40 = 0x36146;
                  trap_Cvar_Set();
                  local_7b40 = 0x36158;
                  trap_Cvar_Set();
                  local_7b40 = 0x3616a;
                  trap_Cvar_Set();
                  local_7b40 = 0x3617c;
                  trap_Cvar_Set();
                  local_7b40 = 0x3618e;
                  trap_Cvar_Set();
                  local_7b40 = 0x361a0;
                  trap_Cvar_Set();
                  local_7b40 = 0x361b2;
                  trap_Cvar_Set();
                  local_7b40 = 0x361c4;
                  trap_Cvar_Set();
                  local_7b40 = 0x361d6;
                  trap_Cvar_Set();
                  local_7b40 = 0x361e8;
                  trap_Cvar_Set();
                  local_7b40 = 0x361fa;
                  trap_Cvar_Set();
                  local_7b40 = 0x3620c;
                  trap_Cvar_Set();
                  local_7b40 = 0x3621e;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x3623c;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x3625d;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x362a6;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x362bc;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x36305;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x36344;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x36386;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x3639f;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x363e1;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x36420;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x3645f;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x364a1;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x364e3;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x36525;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x36567;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x365a9;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x365eb;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x3662d;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x3666f;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x366b1;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x366f3;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x36741;
                  trap_Cvar_VariableStringBuffer();
                  local_7b40 = 0x3676c;
                  va();
                  local_7b40 = 0x3677e;
                  trap_Cvar_Set();
                  local_7b40 = 0x36798;
                  va();
                  local_7b40 = 0x367aa;
                  trap_Cvar_Set();
                  local_7b40 = 0x367b6;
                  va();
                  local_7b40 = 0x367c8;
                  trap_Cvar_Set();
                  local_7b40 = 0x367d8;
                  va();
                  local_7b40 = 0x367ea;
                  trap_Cvar_Set();
                  local_7b40 = 0x367fa;
                  va();
                  local_7b40 = 0x3680c;
                  trap_Cvar_Set();
                  local_7b40 = 0x36820;
                  va();
                  local_7b40 = 0x36832;
                  trap_Cvar_Set();
                  local_7b40 = 0x36842;
                  va();
                  local_7b40 = 0x36854;
                  trap_Cvar_Set();
                  local_7b40 = 0x36864;
                  va();
                  local_7b40 = 0x36876;
                  trap_Cvar_Set();
                  local_7b40 = 0x36886;
                  va();
                  local_7b40 = 0x36898;
                  trap_Cvar_Set();
                  local_7b40 = 0x368a8;
                  va();
                  local_7b40 = 0x368ba;
                  trap_Cvar_Set();
                  local_7b40 = 0x368ca;
                  va();
                  local_7b40 = 0x368dc;
                  trap_Cvar_Set();
                  local_7b40 = 0x368ec;
                  va();
                  local_7b40 = 0x368fe;
                  trap_Cvar_Set();
                  local_7b40 = 0x3690e;
                  va();
                  local_7b40 = 0x36920;
                  trap_Cvar_Set();
                  local_7b40 = 0x36930;
                  va();
                  local_7b40 = 0x36942;
                  trap_Cvar_Set();
                  local_7b40 = 0x36952;
                  va();
                  local_7b40 = 0x36964;
                  trap_Cvar_Set();
                  local_7b40 = 0x36974;
                  va();
                  local_7b40 = 0x36986;
                  trap_Cvar_Set();
                  local_7b40 = 0x36996;
                  va();
                  local_7b40 = 0x369a8;
                  trap_Cvar_Set();
                  local_7b40 = 0x369b8;
                  va();
                  local_7b40 = 0x369ca;
                  trap_Cvar_Set();
                  local_7b40 = 0x369da;
                  va();
                  local_7b40 = 0x369ec;
                  trap_Cvar_Set();
                  local_7b40 = 0x369fc;
                  va();
                  local_7b40 = 0x36a0e;
                  trap_Cvar_Set();
                  local_7b40 = 0x36a26;
                  trap_Cvar_Set();
                  local_7b40 = 0x36a36;
                  trap_Cvar_Set();
                  local_7b40 = 0x36a46;
                  trap_Cvar_Set();
                  local_7b40 = 0x36a56;
                  trap_Cvar_Set();
                  local_7b40 = 0x36a66;
                  trap_Cvar_Set();
                  local_7b40 = 0x36a76;
                  trap_Cvar_Set();
                  local_7b40 = 0x36a89;
                  trap_Cvar_Set();
                  local_7b40 = 0x36a9c;
                  trap_Cvar_Set();
                  local_7b40 = 0x36aaf;
                  trap_Cvar_Set();
                  local_7b40 = 0x36abf;
                  trap_Cvar_Set();
                  local_7b40 = 0x36acf;
                  trap_Cvar_Set();
                  local_7b40 = 0x36ae2;
                  trap_Cvar_Set();
                  local_7b40 = 0x36af5;
                  trap_Cvar_Set();
                  local_7b40 = 0x36b08;
                  trap_Cvar_Set();
                  local_7b40 = 0x36b1b;
                  trap_Cvar_Set();
                  local_7b40 = 0x36b2e;
                  trap_Cvar_Set();
                  local_7b40 = 0x36b41;
                  trap_Cvar_Set();
                  local_7b40 = 0x36b54;
                  trap_Cvar_Set();
                  local_7b40 = 0x36b67;
                  trap_Cvar_Set();
                  local_7b40 = 0x36b7a;
                  trap_Cvar_Set();
                  local_7b40 = 0x36b8d;
                  trap_Cvar_Set();
                  local_7b40 = 0x36ba0;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x36bbe;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x36bd0;
                  trap_Cvar_VariableValue();
                  local_7b40 = 0x36c0b;
                  va();
                  local_7b40 = 0x36c1d;
                  trap_Cvar_Set();
                  return;
                }
                local_7b40 = 0x36c3b;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x36c57;
                  tmp_l17 = (long double)trap_Cvar_VariableValue();
                  local_7b40 = 0x36c96;
                  tmp_l18 = (long double)trap_Cvar_VariableValue();
                  local_7b40 = 0x36ce3;
                  va();
                  local_7b40 = 0x36cf5;
                  trap_Cvar_Set();
                  if ((int)ROUND(tmp_l18) == 0) {
                    local_7b40 = 0x36d17;
                    trap_Cvar_SetValue();
                  }
                  else {
                    local_7b40 = 0x36dc5;
                    trap_Cvar_SetValue();
                  }
                  if ((int)ROUND(tmp_l17) == 0) {
                    local_7b40 = 0x36d31;
                    trap_Cmd_ExecuteText();
                    local_7b40 = 0x36d3d;
                    Controls_SetDefaults();
                  }
                  else {
                    local_7b40 = 0x36da1;
                    trap_Cmd_ExecuteText();
                    local_7b40 = 0x36dad;
                    Controls_SetDefaults();
                  }
                }
                else {
                  local_7b40 = 0x36d79;
                  tmp_i3 = Q_stricmp();
                  if (tmp_i3 != 0) {
                    local_7b40 = 0x36de3;
                    tmp_i3 = Q_stricmp();
                    if (tmp_i3 != 0) {
                      local_7b40 = 0x36e70;
                      Com_Printf();
                      return;
                    }
                    local_7b40 = 0x36df5;
                    tmp_l17 = (long double)trap_Cvar_VariableValue();
                    if ((int)ROUND(tmp_l17) == 0) {
                      local_7b40 = 0x36e46;
                      trap_Cmd_ExecuteText();
                      local_7b40 = 0x36e52;
                      Controls_SetDefaults();
                      return;
                    }
                    local_7b40 = 0x36e8b;
                    trap_Cmd_ExecuteText();
                    local_7b40 = 0x36e97;
                    Controls_SetDefaults();
                    return;
                  }
                }
                local_7b40 = 0x36d4f;
                trap_Cvar_Set();
                local_7b40 = 0x36d5b;
                trap_Cvar_Set();
                return;
              }
              local_7b40 = 0x34df2;
              trap_Cvar_VariableStringBuffer();
              local_7b40 = 0x34e06;
              Q_strncpyz();
              local_7b40 = 0x34e0e;
              Q_CleanStr();
              local_7b40 = 0x34e16;
              Q_CleanDirName();
              local_7b40 = 0x34e30;
              Q_strncpyz();
              local_7b40 = 0x34e38;
              Q_CleanStr();
              local_7b40 = 0x34e40;
              Q_CleanDirName();
              local_7b40 = 0x34e52;
              va();
              local_7b40 = 0x34e71;
              tmp_i3 = trap_FS_FOpenFile();
              if (-1 < tmp_i3) {
                tmp_i3 = -1;
                tmp_pu13 = local_7964;
                do {
                  if (tmp_i3 == 0) break;
                  tmp_i3 = tmp_i3 + -1;
                  tmp_u6 = *tmp_pu13;
                  tmp_pu13 = (uint *)((int)tmp_pu13 + (uint)tmp_b16 * -2 + 1);
                } while ((char)tmp_u6 != '\0');
                local_7b40 = 0x34ea3;
                va();
                local_7b40 = 0x34eb8;
                trap_FS_Write();
                local_7b40 = 0x34ec7;
                trap_FS_FCloseFile();
              }
              local_7b40 = 0x34ed3;
              tmp_i3 = Q_stricmp();
              if (tmp_i3 != 0) {
                local_7b40 = 0x34fab;
                va();
                local_7b40 = 0x34fc3;
                tmp_i3 = trap_FS_FOpenFile();
                if (-1 < tmp_i3) {
                  local_7b40 = 0x34fe6;
                  va();
                  local_7b40 = 0x35001;
                  tmp_i3 = trap_FS_FOpenFile();
                  tmp_i4 = 0;
                  if (-1 < tmp_i3) {
                    for (; tmp_i4 != tmp_i3; tmp_i4 = tmp_i4 + 1) {
                      local_7b40 = 0x35036;
                      trap_FS_Read();
                      local_7b40 = 0x35051;
                      trap_FS_Write();
                    }
                    local_7b40 = 0x3516d;
                    trap_FS_FCloseFile();
                  }
                  local_7b40 = 0x3517c;
                  trap_FS_FCloseFile();
                }
                local_7b40 = 0x3518e;
                va();
                local_7b40 = 0x351a6;
                tmp_i3 = trap_FS_FOpenFile();
                if (-1 < tmp_i3) {
                  local_7b40 = 0x351cb;
                  va();
                  local_7b40 = 0x351e6;
                  tmp_i3 = trap_FS_FOpenFile();
                  tmp_i4 = 0;
                  if (-1 < tmp_i3) {
                    for (; tmp_i4 != tmp_i3; tmp_i4 = tmp_i4 + 1) {
                      local_7b40 = 0x3521b;
                      trap_FS_Read();
                      local_7b40 = 0x35236;
                      trap_FS_Write();
                    }
                    local_7b40 = 0x35315;
                    trap_FS_FCloseFile();
                  }
                  local_7b40 = 0x35324;
                  trap_FS_FCloseFile();
                }
                local_7b40 = 0x35336;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x35391;
                  trap_Cvar_Set();
                  local_7b40 = 0x353af;
                  tmp_i3 = trap_FS_FOpenFile();
                  if (-1 < tmp_i3) {
                    tmp_i3 = -1;
                    tmp_pc9 = local_7a64;
                    do {
                      if (tmp_i3 == 0) break;
                      tmp_i3 = tmp_i3 + -1;
                      tmp_c1 = *tmp_pc9;
                      tmp_pc9 = tmp_pc9 + (uint)tmp_b16 * -2 + 1;
                    } while (tmp_c1 != '\0');
                    local_7b40 = 0x353db;
                    va();
                    local_7b40 = 0x353f2;
                    trap_FS_Write();
                    local_7b40 = 0x35401;
                    trap_FS_FCloseFile();
                  }
                }
                local_7b40 = 0x3534a;
                tmp_i3 = Q_stricmp();
                if (tmp_i3 == 0) {
                  local_7b40 = 0x35360;
                  trap_Cvar_Set();
                }
                local_7b40 = 0x35372;
                va();
                local_7b40 = 0x3537a;
                trap_FS_Delete();
              }
              local_7b40 = 0x34ef1;
              trap_Cvar_Set();
              local_7b40 = 0x34f07;
              trap_Cvar_Set();
              return;
            }
            local_7b40 = 0x34c75;
            Q_strncpyz();
            local_7b40 = 0x34c7d;
            Q_CleanStr();
            local_7b40 = 0x34c85;
            Q_CleanDirName();
            local_7b40 = 0x34c91;
            tmp_i3 = Q_stricmp();
            if (tmp_i3 == 0) {
              return;
            }
            local_7b40 = 0x34cab;
            tmp_i3 = Q_stricmp();
            if (tmp_i3 == 0) {
              local_7b40 = 0x34d1e;
              trap_Cvar_Set();
              local_7b40 = 0x34d3f;
              tmp_i3 = trap_FS_FOpenFile();
              if (-1 < tmp_i3) {
                tmp_i3 = -1;
                tmp_pc9 = cl_profile + 0x10;
                do {
                  if (tmp_i3 == 0) break;
                  tmp_i3 = tmp_i3 + -1;
                  tmp_c1 = *tmp_pc9;
                  tmp_pc9 = tmp_pc9 + (uint)tmp_b16 * -2 + 1;
                } while (tmp_c1 != '\0');
                local_7b40 = 0x34d6f;
                va();
                local_7b40 = 0x34d86;
                trap_FS_Write();
                local_7b40 = 0x34d95;
                trap_FS_FCloseFile();
              }
            }
            local_7b40 = 0x34cc1;
            va();
            local_7b40 = 0x34cc9;
            trap_FS_Delete();
            return;
          }
          local_7b40 = 0x34afa;
          Q_strncpyz();
          local_7b40 = 0x34b02;
          Q_CleanStr();
          local_7b40 = 0x34b0a;
          Q_CleanDirName();
          local_7b40 = 0x34b1c;
          trap_Cvar_Set();
          local_7b40 = 0x34b3d;
          tmp_i3 = trap_FS_FOpenFile();
          if (tmp_i3 < 0) {
            return;
          }
          tmp_i3 = -1;
          tmp_pc9 = cl_defaultProfile + 0x10;
          do {
            if (tmp_i3 == 0) break;
            tmp_i3 = tmp_i3 + -1;
            tmp_c1 = *tmp_pc9;
            tmp_pc9 = tmp_pc9 + (uint)tmp_b16 * -2 + 1;
          } while (tmp_c1 != '\0');
          local_7b40 = 0x34b69;
          va();
          local_7b40 = 0x34b7e;
          trap_FS_Write();
          local_7b40 = 0x34b8d;
          trap_FS_FCloseFile();
          return;
        }
        local_7b40 = 0x347c2;
        Q_strncpyz();
        local_7b40 = 0x347ca;
        Q_CleanStr();
        local_7b40 = 0x347d2;
        Q_CleanDirName();
        local_7b40 = 0x347e4;
        va();
        local_7b40 = 0x347ff;
        tmp_i3 = trap_FS_FOpenFile();
        if (-1 < tmp_i3) {
          tmp_i3 = -1;
          tmp_pc9 = ui_profile + 0x10;
          do {
            if (tmp_i3 == 0) break;
            tmp_i3 = tmp_i3 + -1;
            tmp_c1 = *tmp_pc9;
            tmp_pc9 = tmp_pc9 + (uint)tmp_b16 * -2 + 1;
          } while (tmp_c1 != '\0');
          local_7b40 = 0x34827;
          va();
          local_7b40 = 0x3483c;
          trap_FS_Write();
          local_7b40 = 0x3484b;
          trap_FS_FCloseFile();
        }
        local_7b40 = 0x3485d;
        trap_Cvar_Set();
        return;
      }
      tmp_pu13 = local_754c;
      g_dat_003df584 = 0;
      _DAT_003df588 = -1;
      local_7b40 = 0x34739;
      tmp_i3 = trap_FS_GetFileList();
      for (local_7b20 = 0; local_7b20 < tmp_i3; local_7b20 = local_7b20 + 1) {
        tmp_u6 = 0xffffffff;
        tmp_pu14 = tmp_pu13;
        do {
          if (tmp_u6 == 0) break;
          tmp_u6 = tmp_u6 - 1;
          tmp_u5 = *tmp_pu14;
          tmp_pu14 = (uint *)((int)tmp_pu14 + (uint)tmp_b16 * -2 + 1);
        } while ((char)tmp_u5 != '\0');
        if ((char)*tmp_pu13 != '\0') {
          local_7b40 = 0x348f6;
          tmp_i4 = Q_stricmp();
          if (tmp_i4 != 0) {
            local_7b40 = 0x34910;
            tmp_i4 = Q_stricmp();
            if (tmp_i4 != 0) {
              local_7b40 = 0x3492a;
              va();
              local_7b40 = 0x34932;
              tmp_i4 = trap_PC_LoadSource();
              if (tmp_i4 != 0) {
                local_7b40 = 0x3494f;
                tmp_i11 = trap_PC_ReadToken();
                tmp_i4 = g_dat_003df584;
                if (tmp_i11 == 0) {
                  local_7b40 = 0x3495b;
                  trap_PC_FreeSource();
                }
                else {
                  local_7b40 = 0x34987;
                  tmp_u8 = String_Alloc();
                  *(uint32_t *)(&g_dat_003df384 + tmp_i4 * 8) = tmp_u8;
                  local_7b40 = 0x349a5;
                  trap_PC_FreeSource();
                  tmp_i4 = g_dat_003df584;
                  local_7b40 = 0x349b3;
                  tmp_u8 = String_Alloc();
                  g_dat_003df584 = g_dat_003df584 + 1;
                  tmp_b15 = _DAT_003df588 == -1;
                  *(uint32_t *)(&g_dat_003df388 + tmp_i4 * 8) = tmp_u8;
                  if (tmp_b15) {
                    local_7b40 = 0x34b9a;
                    Q_CleanStr();
                    local_7b40 = 0x34ba2;
                    Q_CleanDirName();
                    local_7b40 = 0x34bb4;
                    tmp_i4 = Q_stricmp();
                    if (tmp_i4 == 0) {
                      tmp_i4 = 0;
                      _DAT_003df588 = local_7b20;
                      local_7b40 = 0x34be0;
                      trap_Cvar_Set();
                      local_7b40 = 0x34bee;
                      trap_Cvar_Update();
                      while( true ) {
                        local_7b40 = 0x34bf3;
                        tmp_i11 = Menu_Count();
                        if (tmp_i11 <= tmp_i4) break;
                        tmp_i4 = tmp_i4 + 1;
                        local_7b40 = 0x34c0f;
                        Menu_Get();
                        local_7b40 = 0x34c2b;
                        Menu_SetFeederSelection();
                      }
                    }
                  }
                  if (0x3f < g_dat_003df584) break;
                }
              }
            }
          }
        }
        tmp_pu13 = (uint *)((int)tmp_pu13 + ~tmp_u6);
      }
      if (_DAT_003df588 != -1) {
        return;
      }
      tmp_i3 = 0;
      _DAT_003df588 = 0;
      local_7b40 = 0x34a0f;
      trap_Cvar_Set();
      local_7b40 = 0x34a1d;
      trap_Cvar_Update();
      while( true ) {
        local_7b40 = 0x34a22;
        tmp_i4 = Menu_Count();
        if (tmp_i4 <= tmp_i3) break;
        tmp_i3 = tmp_i3 + 1;
        local_7b40 = 0x34a33;
        Menu_Get();
        local_7b40 = 0x34a53;
        Menu_SetFeederSelection();
      }
      return;
    }
    tmp_pu13 = local_754c;
    g_dat_003e0790 = 0;
    local_7b40 = 0x32187;
    tmp_i3 = trap_FS_GetFileList();
    for (local_7b1c = 0; local_7b1c < tmp_i3; local_7b1c = local_7b1c + 1) {
      tmp_u6 = 0xffffffff;
      tmp_pu14 = tmp_pu13;
      do {
        if (tmp_u6 == 0) break;
        tmp_u6 = tmp_u6 - 1;
        tmp_u5 = *tmp_pu14;
        tmp_pu14 = (uint *)((int)tmp_pu14 + (uint)tmp_b16 * -2 + 1);
      } while ((char)tmp_u5 != '\0');
      tmp_i4 = g_dat_003e0790 * 0x48;
      local_7b40 = 0x321db;
      tmp_u8 = String_Alloc();
      *(uint32_t *)(&g_dat_003df590 + tmp_i4) = tmp_u8;
      local_7b40 = 0x32200;
      tmp_i4 = Q_stricmp();
      if (tmp_i4 == 0) {
LAB_00032216:
        local_7b40 = 0x32230;
        Q_strncpyz();
      }
      else {
        local_7b40 = 0x3235d;
        tmp_i4 = Q_stricmp();
        if (tmp_i4 == 0) goto LAB_00032216;
        local_7b40 = 0x32430;
        tmp_i4 = Q_stricmp();
        if (tmp_i4 == 0) goto LAB_00032216;
        local_7b40 = 0x3250d;
        tmp_i4 = Q_stricmp();
        if (tmp_i4 == 0) goto LAB_00032216;
        local_7b40 = 0x325a0;
        tmp_i4 = Q_stricmp();
        if (tmp_i4 == 0) goto LAB_00032216;
        local_7b40 = 0x326b2;
        tmp_i4 = Q_stricmp();
        if (tmp_i4 == 0) goto LAB_00032216;
        local_7b40 = 0x32770;
        tmp_i4 = Q_stricmp();
        if (tmp_i4 == 0) goto LAB_00032216;
        local_7b40 = 0x3284d;
        tmp_i4 = Q_stricmp();
        if (tmp_i4 == 0) goto LAB_00032216;
      }
      tmp_s2 = g_dat_003e0790;
      local_7b40 = 0x32242;
      tmp_u8 = String_Alloc();
      tmp_i4 = -1;
      *(uint32_t *)(&g_dat_003df5d4 + tmp_s2 * 0x48) = tmp_u8;
      tmp_pc9 = (char *)((int)tmp_pu13 + ~tmp_u6);
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_c1 = *tmp_pc9;
        tmp_pc9 = tmp_pc9 + (uint)tmp_b16 * -2 + 1;
      } while (tmp_c1 != '\0');
      tmp_pu13 = (uint *)((int)tmp_pu13 + ((~tmp_u6 - 1) - tmp_i4));
      g_dat_003e0790 = g_dat_003e0790 + 1;
      if (0x3f < (int)g_dat_003e0790) break;
    }
    local_7b40 = 0x323a2;
    qsort(&g_dat_003df590,g_dat_003e0790,0x48,UI_SortMods);
    return;
  }
  if (GHIDRA_FIELD(ui_netGameType, 12, 4) == 4) {
    if (g_dat_003bab6c < 1) goto LAB_0003158a;
  }
  else {
    if (g_dat_003bab6c < 1) goto LAB_0003158a;
    tmp_b16 = (byte)GHIDRA_FIELD(ui_netGameType, 12, 4);
    tmp_pu7 = (uint32_t *)&g_dat_003babcc;
    tmp_i4 = g_dat_003bab6c * 0x80;
    do {
      *tmp_pu7 = 0;
      if ((tmp_pu7[-0x14] & 1 << (tmp_b16 & 0x1f)) != 0) {
        *tmp_pu7 = 1;
      }
      tmp_pu7 = tmp_pu7 + 0x20;
    } while (tmp_pu7 != (uint32_t *)(&g_dat_003babcc + tmp_i4));
  }
  GHIDRA_FIELD(ui_mapIndex, 12, 4) = 0;
  tmp_i4 = 0;
  do {
    if (*(int *)(&g_dat_003babcc + tmp_i4 * 0x80) != 0) {
      if (GHIDRA_FIELD(ui_currentMap, 12, 4) == tmp_i4) goto LAB_0003158c;
      GHIDRA_FIELD(ui_mapIndex, 12, 4) = GHIDRA_FIELD(ui_mapIndex, 12, 4) + 1;
    }
    tmp_i4 = tmp_i4 + 1;
  } while (tmp_i4 != tmp_i3);
LAB_0003158a:
  GHIDRA_FIELD(ui_mapIndex, 12, 4) = 0;
LAB_0003158c:
  local_7b40 = 0x315ad;
  va();
  local_7b40 = 0x315bf;
  trap_Cvar_Set();
  local_7b40 = 0x315e3;
  Menu_SetFeederSelection();
  GHIDRA_FIELD(ui_campaignIndex, 12, 4) = 0;
  if (0 < g_dat_003bab6c) {
    tmp_i3 = 0;
    tmp_i4 = 0;
    do {
      if (*(int *)(&g_dat_003babcc + tmp_i4 * 0x80) != 0) {
        GHIDRA_FIELD(ui_campaignIndex, 12, 4) = tmp_i3;
        if (GHIDRA_FIELD(ui_currentCampaign, 12, 4) == tmp_i4) break;
        tmp_i3 = tmp_i3 + 1;
      }
      tmp_i4 = tmp_i4 + 1;
      GHIDRA_FIELD(ui_campaignIndex, 12, 4) = 0;
    } while (tmp_i4 != g_dat_003bab6c);
  }
  local_7b40 = 0x31634;
  va();
  local_7b40 = 0x31646;
  trap_Cvar_Set();
  local_7b40 = 0x3166f;
  Menu_SetFeederSelection();
  if ((GHIDRA_FIELD(ui_netGameType, 12, 4) != 4) && (0 < g_dat_003bab6c)) {
    tmp_pu7 = (uint32_t *)&g_dat_003babcc;
    tmp_i3 = g_dat_003bab6c * 0x80;
    tmp_b16 = (byte)GHIDRA_FIELD(ui_netGameType, 12, 4);
    do {
      *tmp_pu7 = 0;
      if ((tmp_pu7[-0x14] & 1 << (tmp_b16 & 0x1f)) != 0) {
        *tmp_pu7 = 1;
      }
      tmp_pu7 = tmp_pu7 + 0x20;
    } while (tmp_pu7 != (uint32_t *)(&g_dat_003babcc + tmp_i3));
  }
  GHIDRA_FIELD(ui_gameType, 12, 4) = GHIDRA_FIELD(ui_gameType, 12, 4) + 1;
  if ((int)GHIDRA_FIELD(ui_gameType, 12, 4) < g_dat_003b8b48) {
    if (GHIDRA_FIELD(ui_gameType, 12, 4) == 2) {
      GHIDRA_FIELD(ui_gameType, 12, 4) = 3;
    }
  }
  else {
    GHIDRA_FIELD(ui_gameType, 12, 4) = 1;
  }
  local_7b40 = 0x316fa;
  trap_Cvar_Set();
  local_7b40 = 0x31710;
  va();
  local_7b40 = 0x3171c;
  trap_Cvar_Set();
  if ((GHIDRA_FIELD(ui_netGameType, 12, 4) != 4) && (0 < g_dat_003bab6c)) {
    tmp_b16 = (byte)GHIDRA_FIELD(ui_netGameType, 12, 4);
    tmp_i3 = g_dat_003bab6c * 0x80;
    tmp_pu7 = (uint32_t *)&g_dat_003babcc;
    do {
      *tmp_pu7 = 0;
      if ((tmp_pu7[-0x14] & 1 << (tmp_b16 & 0x1f)) != 0) {
        *tmp_pu7 = 1;
      }
      tmp_pu7 = tmp_pu7 + 0x20;
    } while (tmp_pu7 != (uint32_t *)(&g_dat_003babcc + tmp_i3));
  }
  GHIDRA_FIELD(ui_gameType, 12, 4) = GHIDRA_FIELD(ui_gameType, 12, 4) + -1;
  if (GHIDRA_FIELD(ui_gameType, 12, 4) == 2) {
    GHIDRA_FIELD(ui_gameType, 12, 4) = 1;
  }
  else if ((int)GHIDRA_FIELD(ui_gameType, 12, 4) < 2) {
    GHIDRA_FIELD(ui_gameType, 12, 4) = g_dat_003b8b48 + -1;
  }
  local_7b40 = 0x31791;
  trap_Cvar_Set();
  local_7b40 = 0x317a7;
  va();
  local_7b40 = 0x317b3;
  trap_Cvar_Set();
  return;
}

void _UI_SetActiveMenu(uint32_t param_1)

{
{  int tmp_i1;
  long tmp_l2;
  uint tmp_u3;
  uint tmp_u4;
  char *tmp_pc5;
  uint32_t tmp_u6;
  uint *tmp_pu7;
  uint *tmp_pu8;
  uint local_100c;
  uint8_t local_1007 [4091];
  
  tmp_i1 = Menu_Count();
  if (0 < tmp_i1) {
    menutype = param_1;
    switch(param_1) {
    case 0:
      tmp_u4 = trap_Key_GetCatcher();
      trap_Key_SetCatcher(tmp_u4 & 0xfffffffd);
      trap_Key_ClearStates();
      trap_Cvar_Set("cl_paused","0");
      Menus_CloseAll();
      break;
    case 1:
      trap_Key_SetCatcher(2);
      Menus_CloseAll();
      Menus_ActivateByName("backgroundmusic",1);
      Menus_ActivateByName("main_opener",1);
      trap_Cvar_VariableStringBuffer("com_errorMessage",&local_100c,0x1000);
      if (((char)local_100c != '\0') && (tmp_i1 = Q_stricmp(&local_100c,";"), tmp_i1 != 0)) {
        trap_Cvar_Set("ui_connecting","0");
        tmp_i1 = Q_stricmpn(&local_100c,"Invalid password",0x10);
        tmp_pu8 = &local_100c;
        if (tmp_i1 == 0) {
          trap_Cvar_Set("com_errorMessage",&local_100c);
          Menus_ActivateByName("popupPassword",1);
        }
        else {
          do {
            tmp_pu7 = tmp_pu8;
            tmp_u3 = *tmp_pu7 + 0xfefefeff & ~*tmp_pu7;
            tmp_u4 = tmp_u3 & 0x80808080;
            tmp_pu8 = tmp_pu7 + 1;
          } while (tmp_u4 == 0);
          if ((tmp_u3 & 0x8080) == 0) {
            tmp_pu8 = (uint *)((int)tmp_pu7 + 6);
            tmp_u4 = tmp_u4 >> 0x10;
          }
          if (((char *)((int)tmp_pu8 +
                       ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)&local_100c)) <
               (char *)0x6) || (tmp_i1 = Q_stricmpn(&local_100c,&g_dat_000571ed,5), tmp_i1 != 0)) {
            tmp_pc5 = strstr((char *)&local_100c,"must be Enabled");
            if (tmp_pc5 == (char *)0x0) {
              trap_Cvar_Set("com_errorMessage",&local_100c);
              tmp_pc5 = (char *)UI_Cvar_VariableString("com_errorDiagnoseIP");
              if ((*tmp_pc5 != '\0') &&
                 (tmp_pc5 = (char *)UI_Cvar_VariableString("com_missingFiles"), *tmp_pc5 != '\0')) {
                tmp_u6 = UI_Cvar_VariableString("com_errorMessage");
                tmp_u6 = va("%s\n\n%s\n%s",tmp_u6,"The following packs are missing:",tmp_pc5);
                trap_Cvar_Set("com_errorMessage",tmp_u6);
              }
              Menus_ActivateByName("popupError",1);
            }
            else {
              trap_Cvar_Set("com_errorMessage",&local_100c);
              tmp_pc5 = (char *)UI_Cvar_VariableString("com_errorDiagnoseIP");
              if ((*tmp_pc5 != '\0') &&
                 (tmp_pc5 = (char *)UI_Cvar_VariableString("com_missingFiles"), *tmp_pc5 != '\0')) {
                tmp_u6 = UI_Cvar_VariableString("com_errorMessage");
                tmp_u6 = va("%s\n\n%s\n%s",tmp_u6,"The following packs are missing:",tmp_pc5);
                trap_Cvar_Set("com_errorMessage",tmp_u6);
              }
              Menus_ActivateByName("popupError_pbenable",1);
            }
          }
          else {
            Q_strncpyz(&local_100c,local_1007,0x1000);
            Com_Printf("Server is full, redirect to: %s\n",&local_100c);
            if (GHIDRA_FIELD(ui_autoredirect, 12, 4) == 1) {
              trap_Cvar_Set("com_errorMessage","");
              tmp_u6 = va("connect %s\n",&local_100c);
              trap_Cmd_ExecuteText(2,tmp_u6);
            }
            else {
              trap_Cvar_Set("com_errorMessage",&local_100c);
              Menus_ActivateByName("popupServerRedirect",1);
            }
          }
        }
      }
      trap_S_FadeAllSound(0x3f800000,1000,0);
      break;
    case 2:
      if (GHIDRA_FIELD(g_gameType, 12, 4) == 0) {
        trap_Cvar_Set("cl_paused","1");
      }
      trap_Key_SetCatcher(2);
      UI_BuildPlayerList();
      Menu_SetFeederSelection(0,7,0,0);
      Menus_CloseAll();
      Menus_ActivateByName("ingame_main",1);
      break;
    case 3:
      trap_Key_SetCatcher(2);
      Menus_ActivateByName("needcd",1);
      break;
    case 4:
      trap_Key_SetCatcher(2);
      Menus_ActivateByName("badcd",1);
      break;
    case 5:
      trap_Key_SetCatcher(2);
      Menus_ActivateByName(&g_dat_00057785,1);
      break;
    case 8:
      g_dat_00397fe4 = 0x27f;
      g_dat_00397fe8 = 0x1df;
      trap_Key_SetCatcher(2);
      Menus_CloseAll();
      Menus_OpenByName("wm_quickmessage");
      break;
    case 9:
      g_dat_00397fe4 = 0x27f;
      g_dat_00397fe8 = 0x1df;
      trap_Key_SetCatcher(2);
      Menus_CloseAll();
      Menus_OpenByName("wm_quickmessageAlt");
      break;
    case 10:
      g_dat_00397fe4 = 0x27f;
      g_dat_00397fe8 = 0x1df;
      trap_Key_SetCatcher(2);
      Menus_CloseAll();
      Menus_OpenByName("wm_ftquickmessage");
      break;
    case 0xb:
      g_dat_00397fe4 = 0x27f;
      g_dat_00397fe8 = 0x1df;
      trap_Key_SetCatcher(2);
      Menus_CloseAll();
      Menus_OpenByName("wm_ftquickmessageAlt");
      break;
    case 0xc:
      g_dat_00397fe4 = 0x27f;
      g_dat_00397fe8 = 0x1df;
      trap_Key_SetCatcher(2);
      Menus_CloseAll();
      Menus_OpenByName("tapoutmsg");
      break;
    case 0xd:
      g_dat_00397fe4 = 0x27f;
      g_dat_00397fe8 = 0x1df;
      trap_Key_SetCatcher(2);
      Menus_CloseAll();
      Menus_OpenByName("tapoutmsglms");
      break;
    case 0xe:
      Menus_OpenByName("wm_autoupdate_modal");
      break;
    case 0xf:
      g_dat_00397fe4 = 0x27f;
      g_dat_00397fe8 = 0x1df;
      trap_Key_SetCatcher(2);
      Menus_CloseAll();
      Menus_OpenByName("wm_class");
      break;
    case 0x10:
      g_dat_00397fe4 = 0x27f;
      g_dat_00397fe8 = 0x1df;
      trap_Key_SetCatcher(2);
      Menus_CloseAll();
      Menus_OpenByName("wm_classAlt");
      break;
    case 0x11:
      trap_Key_SetCatcher(2);
      trap_Cvar_VariableStringBuffer("cg_messageType",&local_100c,0x100);
      tmp_l2 = strtol((char *)&local_100c,(char **)0x0,10);
      if (tmp_l2 == 4) {
        Menus_OpenByName("ingame_messagemode4");
      }
      else {
        Menus_OpenByName("ingame_messagemode");
      }
    }
  }
  return;
}

bool MenuParse_background(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t local_10 [3];
  
  local_10[0] = 0;
  tmp_i1 = PC_String_Parse(param_2,local_10);
  if (tmp_i1 != 0) {
    tmp_u2 = (*(void *)*DC)(local_10[0]);
    *(uint32_t *)(param_1 + 0xb4) = tmp_u2;
  }
  return tmp_i1 != 0;
}

uint32_t MenuParse_backcolor(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  int tmp_i2;
  uint32_t local_20 [4];
  
  tmp_i2 = 0;
  local_20[0] = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_1 + 0x84 + tmp_i2 * 4) = local_20[0];
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 4);
  return 1;
}

uint32_t MenuParse_forecolor(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t *tmp_pu3;
  uint32_t local_20 [4];
  
  local_20[0] = 0;
  tmp_pu2 = (uint32_t *)(param_1 + 0x74);
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    tmp_pu3 = tmp_pu2 + 1;
    *tmp_pu2 = local_20[0];
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x200;
    tmp_pu2 = tmp_pu3;
  } while (tmp_pu3 != (uint32_t *)(param_1 + 0x84));
  return 1;
}

uint32_t MenuParse_bordercolor(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  int tmp_i2;
  uint32_t local_20 [4];
  
  tmp_i2 = 0;
  local_20[0] = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_1 + 0x94 + tmp_i2 * 4) = local_20[0];
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 4);
  return 1;
}

uint32_t MenuParse_focuscolor(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  int tmp_i2;
  uint32_t local_20 [4];
  
  tmp_i2 = 0;
  local_20[0] = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_1 + 0x4f4 + tmp_i2 * 4) = local_20[0];
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 4);
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x8000000;
  return 1;
}

uint32_t MenuParse_disablecolor(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  int tmp_i2;
  uint32_t local_20 [4];
  
  tmp_i2 = 0;
  local_20[0] = 0;
  do {
    tmp_i1 = PC_Float_Parse(param_2,local_20);
    if (tmp_i1 == 0) {
      return 0;
    }
    *(uint32_t *)(param_1 + 0x504 + tmp_i2 * 4) = local_20[0];
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 4);
  return 1;
}

uint32_t MenuParse_visible(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  uint32_t tmp_u2;
  int local_10 [3];
  
  local_10[0] = 0;
  tmp_i1 = PC_Int_Parse(param_2,local_10);
  tmp_u2 = 0;
  if ((tmp_i1 != 0) && (tmp_u2 = 1, local_10[0] != 0)) {
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 4;
  }
  return tmp_u2;
}

bool MenuParse_name(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  
  tmp_i1 = PC_String_Parse(param_2,param_1 + 0x20);
  if (tmp_i1 != 0) {
    Q_stricmp(*(uint32_t *)(param_1 + 0x20),"main");
  }
  return tmp_i1 != 0;
}

bool MenuParse_rect(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_2,param_1);
  if (((tmp_i1 != 0) && (tmp_i1 = PC_Float_Parse(param_2,param_1 + 4), tmp_i1 != 0)) &&
     (tmp_i1 = PC_Float_Parse(param_2,param_1 + 8), tmp_i1 != 0)) {
    tmp_i1 = PC_Float_Parse(param_2,param_1 + 0xc);
    return tmp_i1 != 0;
  }
  return false;
}

bool ItemParse_contextMenu(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x250);
  if (tmp_i1 == 0) {
    Item_ValidateTypeData_part_21();
    tmp_i1 = *(int *)(param_1 + 0x250);
    if (tmp_i1 == 0) {
      return false;
    }
  }
  tmp_i1 = PC_String_Parse(param_2,tmp_i1 + 0xe4);
  return tmp_i1 != 0;
}

void Script_CloseAllOtherMenus(int param_1)

{
{  uint tmp_u1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  
  if (0 < menuCount) {
    tmp_pu3 = &Menus;
    tmp_i4 = 0;
    tmp_i2 = menuCount;
    do {
      if (tmp_pu3 != *(uint32_t **)(param_1 + 0xec)) {
        tmp_u1 = tmp_pu3[0x12];
        if ((tmp_u1 & 4) != 0) {
          Menu_RunCloseScript_part_10();
          tmp_u1 = tmp_pu3[0x12];
          tmp_i2 = menuCount;
        }
        tmp_pu3[0x12] = tmp_u1 & 0xfffffff8;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu3 = tmp_pu3 + 0x346;
    } while (tmp_i4 < tmp_i2);
  }
  return;
}

void Script_FadeOutMenu(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if (((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) &&
     (tmp_u3 = String_Alloc(tmp_pc2), 0 < menuCount)) {
    tmp_pu6 = &g_dat_003f16a0;
    tmp_i5 = 0;
    do {
      tmp_i4 = Q_stricmp(*tmp_pu6,tmp_u3);
      if (tmp_i4 == 0) {
        if ((int)(&g_dat_003f1740)[tmp_i5 * 0x346] < 1) {
          return;
        }
        tmp_i4 = 0;
        do {
          tmp_i1 = tmp_i5 * 0x346 + tmp_i4;
          tmp_i4 = tmp_i4 + 1;
          *(uint *)((&g_dat_003f1b94)[tmp_i1] + 0x48) =
               *(uint *)((&g_dat_003f1b94)[tmp_i1] + 0x48) & 0xffffffbf | 0x24;
        } while (tmp_i4 < (int)(&g_dat_003f1740)[tmp_i5 * 0x346]);
        return;
      }
      tmp_i5 = tmp_i5 + 1;
      tmp_pu6 = tmp_pu6 + 0x346;
    } while (tmp_i5 < menuCount);
  }
  return;
}

void Script_FadeInMenu(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  
  tmp_pc2 = (char *)COM_ParseExt(param_3,0);
  if (((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) &&
     (tmp_u3 = String_Alloc(tmp_pc2), 0 < menuCount)) {
    tmp_pu6 = &g_dat_003f16a0;
    tmp_i5 = 0;
    do {
      tmp_i4 = Q_stricmp(*tmp_pu6,tmp_u3);
      if (tmp_i4 == 0) {
        if ((int)(&g_dat_003f1740)[tmp_i5 * 0x346] < 1) {
          return;
        }
        tmp_i4 = 0;
        do {
          tmp_i1 = tmp_i5 * 0x346 + tmp_i4;
          tmp_i4 = tmp_i4 + 1;
          *(uint *)((&g_dat_003f1b94)[tmp_i1] + 0x48) =
               *(uint *)((&g_dat_003f1b94)[tmp_i1] + 0x48) & 0xffffffdf | 0x44;
        } while (tmp_i4 < (int)(&g_dat_003f1740)[tmp_i5 * 0x346]);
        return;
      }
      tmp_i5 = tmp_i5 + 1;
      tmp_pu6 = tmp_pu6 + 0x346;
    } while (tmp_i5 < menuCount);
  }
  return;
}

bool MenuParse_onTimeout(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  bool tmp_b2;
  
  tmp_i1 = PC_Int_Parse(param_2,param_1 + 0xe8);
  tmp_b2 = false;
  if (tmp_i1 != 0) {
    tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xf0);
    tmp_b2 = tmp_i1 != 0;
  }
  return tmp_b2;
}

bool MenuParse_execKey(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  bool tmp_b2;
  char local_d [9];
  
  local_d[0] = '\0';
  tmp_i1 = PC_Char_Parse(param_2,local_d);
  tmp_b2 = false;
  if (tmp_i1 != 0) {
    tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xf4 + local_d[0] * 4);
    tmp_b2 = tmp_i1 != 0;
  }
  return tmp_b2;
}

bool MenuParse_execKeyInt(int param_1,uint32_t param_2)

{
{  int tmp_i1;
  bool tmp_b2;
  int local_10 [2];
  
  local_10[0] = 0;
  tmp_i1 = PC_Int_Parse(param_2,local_10);
  tmp_b2 = false;
  if (tmp_i1 != 0) {
    tmp_i1 = PC_Script_Parse(param_2,param_1 + 0xf4 + local_10[0] * 4);
    tmp_b2 = tmp_i1 != 0;
  }
  return tmp_b2;
}

void Menu_UpdatePosition(float *param_1)

{
{  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float tmp_f9;
  bool tmp_b10;
  bool tmp_b11;
  bool tmp_b12;
  int tmp_i13;
  int tmp_i14;
  int tmp_i15;
  long double tmp_l16;
  float local_40;
  
  if (*(float *)(&g_dat_0002003c + DC) <= 1.3333334) {
    local_40 = 0.0;
  }
  else {
    local_40 = (*(float *)(&g_dat_0002003c + DC) * 0.75 * 640.0 - 640.0) * 0.5;
  }
  if (param_1 == (float *)0x0) {
    return;
  }
  tmp_f1 = *param_1;
  tmp_f2 = param_1[1];
  if (((tmp_f1 == 0.0) && (tmp_f2 == 0.0)) && (param_1[2] == 640.0)) {
    tmp_b10 = param_1[3] == 480.0;
  }
  else {
    if ((tmp_f1 == 16.0) && (param_1[2] == 608.0)) {
      tmp_b11 = true;
      *param_1 = local_40 + 16.0;
      tmp_b10 = false;
      goto LAB_0003eee3;
    }
    tmp_b10 = false;
  }
  tmp_b11 = false;
LAB_0003eee3:
  if (0 < (int)param_1[0x30]) {
    tmp_i15 = 0;
    do {
      while( true ) {
        tmp_f9 = param_1[tmp_i15 + 0x145];
        if (((*(float *)((int)tmp_f9 + 0x10) == 0.0) && (*(float *)((int)tmp_f9 + 0x14) == 0.0)) &&
           ((*(float *)((int)tmp_f9 + 0x18) == 640.0 && (*(float *)((int)tmp_f9 + 0x1c) == 480.0))))
        break;
        tmp_i14 = Q_stricmp(*(uint32_t *)((int)tmp_f9 + 0x20),"clouds");
        tmp_b12 = tmp_b10;
        if (tmp_i14 == 0) {
LAB_0003ef90:
          *(float *)((int)tmp_f9 + 0x18) = local_40 + local_40 + *(float *)((int)tmp_f9 + 0x18);
        }
        if (!tmp_b12) goto LAB_0003efa2;
LAB_0003efad:
        tmp_f9 = tmp_f1 + local_40;
        pfVar3 = (float *)param_1[tmp_i15 + 0x145];
        if (pfVar3 != (float *)0x0) {
          pfVar4 = (float *)pfVar3[0x9c];
          *pfVar3 = pfVar3[4] + tmp_f9;
          pfVar3[1] = pfVar3[5] + tmp_f2;
          pfVar3[2] = pfVar3[6];
          pfVar3[3] = pfVar3[7];
          if (pfVar4 != (float *)0x0) {
            pfVar5 = (float *)pfVar4[0x9c];
            *pfVar4 = pfVar4[4] + tmp_f9;
            pfVar4[1] = pfVar4[5] + tmp_f2;
            pfVar4[2] = pfVar4[6];
            pfVar4[3] = pfVar4[7];
            if (pfVar5 != (float *)0x0) {
              pfVar6 = (float *)pfVar5[0x9c];
              *pfVar5 = pfVar5[4] + tmp_f9;
              pfVar5[1] = pfVar5[5] + tmp_f2;
              pfVar5[2] = pfVar5[6];
              pfVar5[3] = pfVar5[7];
              if (pfVar6 != (float *)0x0) {
                pfVar7 = (float *)pfVar6[0x9c];
                *pfVar6 = pfVar6[4] + tmp_f9;
                pfVar6[1] = pfVar6[5] + tmp_f2;
                pfVar6[2] = pfVar6[6];
                pfVar6[3] = pfVar6[7];
                if (pfVar7 != (float *)0x0) {
                  *pfVar7 = pfVar7[4] + tmp_f9;
                  pfVar7[1] = pfVar7[5] + tmp_f2;
                  pfVar7[2] = pfVar7[6];
                  pfVar7[3] = pfVar7[7];
                  if (pfVar7[0x9c] != 0.0) {
                    Item_SetScreenCoords(pfVar7[0x9c],tmp_f9,tmp_f2);
                    pfVar8 = (float *)pfVar7[0x9c];
                    tmp_f9 = (pfVar8[2] + *pfVar8) - 635.0;
                    if (0.0 < tmp_f9) {
                      pfVar8[4] = pfVar8[4] - tmp_f9;
                      *(float *)pfVar7[0x9c] = *(float *)pfVar7[0x9c] - tmp_f9;
                    }
                  }
                  pfVar7[0x30] = 0.0;
                  pfVar7[0x31] = 0.0;
                  pfVar7 = (float *)pfVar6[0x9c];
                  tmp_f9 = (*pfVar7 + pfVar7[2]) - 635.0;
                  if (0.0 < tmp_f9) {
                    pfVar7[4] = pfVar7[4] - tmp_f9;
                    *(float *)pfVar6[0x9c] = *(float *)pfVar6[0x9c] - tmp_f9;
                  }
                }
                pfVar6[0x30] = 0.0;
                pfVar6[0x31] = 0.0;
                pfVar6 = (float *)pfVar5[0x9c];
                tmp_f9 = (*pfVar6 + pfVar6[2]) - 635.0;
                if (0.0 < tmp_f9) {
                  pfVar6[4] = pfVar6[4] - tmp_f9;
                  *(float *)pfVar5[0x9c] = *(float *)pfVar5[0x9c] - tmp_f9;
                }
              }
              pfVar5[0x30] = 0.0;
              pfVar5[0x31] = 0.0;
              pfVar5 = (float *)pfVar4[0x9c];
              tmp_f9 = (*pfVar5 + pfVar5[2]) - 635.0;
              if (0.0 < tmp_f9) {
                pfVar5[4] = pfVar5[4] - tmp_f9;
                *(float *)pfVar4[0x9c] = *(float *)pfVar4[0x9c] - tmp_f9;
              }
            }
            pfVar4[0x30] = 0.0;
            pfVar4[0x31] = 0.0;
            pfVar4 = (float *)pfVar3[0x9c];
            tmp_f9 = (*pfVar4 + pfVar4[2]) - 635.0;
            if (0.0 < tmp_f9) {
              pfVar4[4] = pfVar4[4] - tmp_f9;
              *(float *)pfVar3[0x9c] = *(float *)pfVar3[0x9c] - tmp_f9;
            }
          }
          pfVar3[0x30] = 0.0;
          pfVar3[0x31] = 0.0;
        }
        tmp_i15 = tmp_i15 + 1;
        if ((int)param_1[0x30] <= tmp_i15) {
          return;
        }
      }
      tmp_i13 = Q_stricmp(*(uint32_t *)((int)tmp_f9 + 0x20),"clouds");
      tmp_i14 = DC;
      if (tmp_i13 == 0) {
        tmp_b12 = false;
        goto LAB_0003ef90;
      }
      *(float *)((int)tmp_f9 + 0x10) = *(float *)((int)tmp_f9 + 0x10) * *(float *)(DC + 0x114);
      *(float *)((int)tmp_f9 + 0x14) = *(float *)((int)tmp_f9 + 0x14) * *(float *)(tmp_i14 + 0x110);
      *(float *)((int)tmp_f9 + 0x18) = *(float *)((int)tmp_f9 + 0x18) * *(float *)(tmp_i14 + 0x114);
      *(float *)((int)tmp_f9 + 0x1c) = *(float *)((int)tmp_f9 + 0x1c) * *(float *)(tmp_i14 + 0x110);
      if ((1.3333334 < *(float *)(&g_dat_0002003c + tmp_i14)) &&
         (tmp_l16 = (long double)(**(void **)(tmp_i14 + 0x74))("r_mode"), tmp_i14 = DC,
         tmp_l16 != (long double)11.0)) {
        *(float *)((int)tmp_f9 + 0x10) =
             (1.3333334 / *(float *)(&g_dat_0002003c + DC)) * *(float *)((int)tmp_f9 + 0x10);
        *(float *)((int)tmp_f9 + 0x18) =
             (1.3333334 / *(float *)(&g_dat_0002003c + tmp_i14)) * *(float *)((int)tmp_f9 + 0x18);
      }
LAB_0003efa2:
      if (tmp_b11) goto LAB_0003efad;
      Item_SetScreenCoords(param_1[tmp_i15 + 0x145],tmp_f1,tmp_f2);
      tmp_i15 = tmp_i15 + 1;
    } while (tmp_i15 < (int)param_1[0x30]);
  }
  return;
}

void Menu_PostParse(uint32_t *param_1)

{
{  if (param_1 != (uint32_t *)0x0) {
    if (param_1[0x2f] != 0) {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0x44200000;
      param_1[3] = 0x43f00000;
    }
    Menu_UpdatePosition();
    return;
  }
  return;
}

int Menu_ClearFocus(int param_1)

{
{  uint *tmp_pu1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint32_t local_10;
  
  if (param_1 == 0) {
    local_10 = 0;
  }
  else {
    local_10 = 0;
    if (0 < *(int *)(param_1 + 0xc0)) {
      tmp_i5 = 0;
      do {
        tmp_i2 = *(int *)(param_1 + 0x514 + tmp_i5 * 4);
        tmp_u3 = *(uint *)(tmp_i2 + 0x48);
        tmp_i4 = tmp_i2;
        if ((tmp_u3 & 2) != 0) {
          *(uint *)(tmp_i2 + 0x48) = tmp_u3 & 0xfffffffd;
          tmp_i4 = *(int *)(param_1 + 0x514 + tmp_i5 * 4);
          tmp_u3 = *(uint *)(tmp_i4 + 0x48);
          local_10 = tmp_i2;
        }
        if ((tmp_u3 & 1) != 0) {
          if ((tmp_u3 & 0x80) != 0) {
            Item_RunScript_constprop_37();
            *(uint *)(tmp_i4 + 0x48) = *(uint *)(tmp_i4 + 0x48) & 0xffffff7f;
          }
          Item_RunScript_constprop_37();
          *(uint *)(tmp_i4 + 0x48) = *(uint *)(tmp_i4 + 0x48) & 0xffffe7ff;
          tmp_i2 = *(int *)(param_1 + 0x514 + tmp_i5 * 4);
          tmp_i4 = 0;
          if (tmp_i2 != 0) {
            tmp_pu1 = (uint *)(tmp_i2 + 0x48);
            *tmp_pu1 = *tmp_pu1 & 0xfffffffe;
            tmp_i4 = *(int *)(param_1 + 0x514 + tmp_i5 * 4);
          }
        }
        if (*(int *)(tmp_i4 + 0x110) != 0) {
          Item_RunScript_constprop_37();
        }
        tmp_i5 = tmp_i5 + 1;
      } while (tmp_i5 < *(int *)(param_1 + 0xc0));
    }
  }
  return local_10;
}

void Script_SetMenuFocus(int param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) &&
     (tmp_u2 = String_Alloc(tmp_pc1), 0 < menuCount)) {
    tmp_pu5 = &g_dat_003f16a0;
    tmp_i4 = 0;
    do {
      tmp_i3 = Q_stricmp(*tmp_pu5,tmp_u2);
      if (tmp_i3 == 0) {
        if ((*(byte *)(&g_dat_003f16c8 + tmp_i4 * 0x346) & 2) != 0) {
          return;
        }
        Menu_ClearFocus(*(uint32_t *)(param_1 + 0xec));
        (&g_dat_003f16c8)[tmp_i4 * 0x346] = (&g_dat_003f16c8)[tmp_i4 * 0x346] | 2;
        return;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu5 = tmp_pu5 + 0x346;
    } while (tmp_i4 < menuCount);
  }
  return;
}

int Menu_ItemsMatchingGroup(int param_1,char *param_2)

{
{  char *tmp_pc1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int local_20;
  
  tmp_pc1 = strchr(param_2,0x2a);
  if (tmp_pc1 == (char *)0x0) {
    tmp_i4 = 0;
    local_20 = 0;
    if (0 < *(int *)(param_1 + 0xc0)) {
LAB_0003fae0:
      do {
        tmp_i2 = Q_stricmp(*(uint32_t *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x20),param_2);
        if ((tmp_i2 == 0) ||
           ((tmp_i2 = *(int *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x28), tmp_i2 != 0 &&
            (tmp_i2 = Q_stricmp(tmp_i2,param_2), tmp_i2 == 0)))) {
          local_20 = local_20 + 1;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 < *(int *)(param_1 + 0xc0));
      return local_20;
    }
  }
  else {
    tmp_i2 = (int)tmp_pc1 - (int)param_2;
    local_20 = 0;
    if (0 < *(int *)(param_1 + 0xc0)) {
      tmp_i4 = 0;
      if (tmp_i2 == -1) goto LAB_0003fae0;
      tmp_i4 = 0;
      do {
        tmp_i3 = Q_strncmp(*(uint32_t *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x20),param_2,
                          tmp_i2);
        if ((tmp_i3 == 0) ||
           ((tmp_i3 = *(int *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x28), tmp_i3 != 0 &&
            (tmp_i3 = Q_strncmp(tmp_i3,param_2,tmp_i2), tmp_i3 == 0)))) {
          local_20 = local_20 + 1;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 < *(int *)(param_1 + 0xc0));
    }
  }
  return local_20;
}

uint32_t Menu_GetMatchingItemByNumber(int param_1,int param_2,char *param_3)

{
{  char *tmp_pc1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int local_24;
  int local_20;
  
  tmp_pc1 = strchr(param_3,0x2a);
  if (tmp_pc1 == (char *)0x0) {
    tmp_i2 = 0;
    local_24 = 0;
    if (*(int *)(param_1 + 0xc0) < 1) {
      return 0;
    }
  }
  else {
    tmp_i2 = (int)tmp_pc1 - (int)param_3;
    if (*(int *)(param_1 + 0xc0) < 1) {
      return 0;
    }
    if (tmp_i2 != -1) {
      local_20 = 0;
      tmp_i4 = 0;
      do {
        tmp_i3 = Q_strncmp(*(uint32_t *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x20),param_3,
                          tmp_i2);
        if ((tmp_i3 == 0) ||
           ((tmp_i3 = *(int *)(*(int *)(param_1 + 0x514 + tmp_i4 * 4) + 0x28), tmp_i3 != 0 &&
            (tmp_i3 = Q_strncmp(tmp_i3,param_3,tmp_i2), tmp_i3 == 0)))) {
          if (local_20 == param_2) {
            return *(uint32_t *)(param_1 + 0x514 + tmp_i4 * 4);
          }
          local_20 = local_20 + 1;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 < *(int *)(param_1 + 0xc0));
      return 0;
    }
    local_24 = 0;
    tmp_i2 = 0;
  }
  do {
    tmp_i4 = Q_stricmp(*(uint32_t *)(*(int *)(param_1 + 0x514 + tmp_i2 * 4) + 0x20),param_3);
    if ((tmp_i4 == 0) ||
       ((tmp_i4 = *(int *)(*(int *)(param_1 + 0x514 + tmp_i2 * 4) + 0x28), tmp_i4 != 0 &&
        (tmp_i4 = Q_stricmp(tmp_i4,param_3), tmp_i4 == 0)))) {
      if (local_24 == param_2) {
        return *(uint32_t *)(param_1 + 0x514 + tmp_i2 * 4);
      }
      local_24 = local_24 + 1;
    }
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 < *(int *)(param_1 + 0xc0));
  return 0;
}

void Script_SetMenuItemColor(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
{  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  uint32_t *tmp_pu9;
  int tmp_i10;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
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
  tmp_u3 = String_Alloc(tmp_pc1);
  tmp_pc1 = (char *)COM_ParseExt(param_3,0);
  if (tmp_pc1 == (char *)0x0) {
    return;
  }
  if (*tmp_pc1 == '\0') {
    return;
  }
  tmp_u4 = String_Alloc(tmp_pc1);
  if (menuCount < 1) {
    return;
  }
  tmp_pu9 = &g_dat_003f16a0;
  tmp_i10 = 0;
  while (tmp_i5 = Q_stricmp(*tmp_pu9,tmp_u2), tmp_i5 != 0) {
    tmp_i10 = tmp_i10 + 1;
    tmp_pu9 = tmp_pu9 + 0x346;
    if (menuCount <= tmp_i10) {
      return;
    }
  }
  tmp_i5 = Menu_ItemsMatchingGroup(&Menus + tmp_i10 * 0x346,tmp_u3);
  tmp_i6 = Color_Parse(param_3,&local_2c);
  if (tmp_i6 == 0) {
    return;
  }
  tmp_i6 = 0;
  if (tmp_i5 < 1) {
    return;
  }
  do {
    tmp_i7 = Menu_GetMatchingItemByNumber(&Menus + tmp_i10 * 0x346,tmp_i6,tmp_u3);
    if (tmp_i7 != 0) {
      tmp_i8 = Q_stricmp(tmp_u4,"backcolor");
      if (tmp_i8 == 0) {
        tmp_pu9 = (uint32_t *)(tmp_i7 + 0x84);
      }
      else {
        tmp_i8 = Q_stricmp(tmp_u4,"forecolor");
        if (tmp_i8 == 0) {
          tmp_pu9 = (uint32_t *)(tmp_i7 + 0x74);
          *(uint *)(tmp_i7 + 0x48) = *(uint *)(tmp_i7 + 0x48) | 0x200;
        }
        else {
          tmp_i8 = Q_stricmp(tmp_u4,"bordercolor");
          tmp_pu9 = (uint32_t *)(tmp_i7 + 0x94);
          if (tmp_i8 != 0) goto LAB_0003fff1;
        }
      }
      *tmp_pu9 = local_2c;
      tmp_pu9[1] = local_28;
      tmp_pu9[2] = local_24;
      tmp_pu9[3] = local_20;
    }
LAB_0003fff1:
    tmp_i6 = tmp_i6 + 1;
    if (tmp_i6 == tmp_i5) {
      return;
    }
  } while( true );
}

uint32_t Menu_FindItemByName(int param_1,int param_2)

{
{  int tmp_i1;
  int tmp_i2;
  
  if (((param_1 != 0) && (param_2 != 0)) && (0 < *(int *)(param_1 + 0xc0))) {
    tmp_i2 = 0;
    do {
      tmp_i1 = Q_stricmp(param_2,*(uint32_t *)(*(int *)(param_1 + 0x514 + tmp_i2 * 4) + 0x20));
      if (tmp_i1 == 0) {
        return *(uint32_t *)(param_1 + 0x514 + tmp_i2 * 4);
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 < *(int *)(param_1 + 0xc0));
  }
  return 0;
}

void Menu_ShowItemByName(uint32_t param_1,uint32_t param_2,int param_3)

{
{  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  
  tmp_i1 = Menu_ItemsMatchingGroup(param_1,param_2);
  if (0 < tmp_i1) {
    tmp_i4 = 0;
    if (param_3 == 0) {
      do {
        tmp_i2 = Menu_GetMatchingItemByNumber(param_1,tmp_i4,param_2);
        if (tmp_i2 != 0) {
          tmp_u3 = *(uint *)(tmp_i2 + 0x48);
          if ((tmp_u3 & 1) != 0) {
            if ((tmp_u3 & 0x80) != 0) {
              Item_RunScript_constprop_37();
              *(uint *)(tmp_i2 + 0x48) = *(uint *)(tmp_i2 + 0x48) & 0xffffff7f;
            }
            Item_RunScript_constprop_37();
            tmp_u3 = *(uint *)(tmp_i2 + 0x48) & 0xffffe7fe;
          }
          *(uint *)(tmp_i2 + 0x48) = tmp_u3 & 0xfffffffb;
          if (-1 < *(int *)(tmp_i2 + 0x30)) {
            (**(void **)(DC + 0xec))(*(int *)(tmp_i2 + 0x30));
            *(uint32_t *)(tmp_i2 + 0x30) = 0xffffffff;
          }
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 != tmp_i1);
    }
    else {
      tmp_i4 = 0;
      do {
        tmp_i2 = Menu_GetMatchingItemByNumber(param_1,tmp_i4,param_2);
        if (tmp_i2 != 0) {
          *(uint *)(tmp_i2 + 0x48) = *(uint *)(tmp_i2 + 0x48) | 4;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 != tmp_i1);
    }
  }
  return;
}

void Menu_FadeItemByName(uint32_t param_1,uint32_t param_2,int param_3)

{
{  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i1 = Menu_ItemsMatchingGroup(param_1,param_2);
  if (0 < tmp_i1) {
    tmp_i3 = 0;
    if (param_3 != 0) {
      do {
        tmp_i2 = Menu_GetMatchingItemByNumber(param_1,tmp_i3,param_2);
        if (tmp_i2 != 0) {
          *(uint *)(tmp_i2 + 0x48) = *(uint *)(tmp_i2 + 0x48) & 0xffffffbf | 0x24;
        }
        tmp_i3 = tmp_i3 + 1;
      } while (tmp_i3 != tmp_i1);
      return;
    }
    do {
      tmp_i2 = Menu_GetMatchingItemByNumber(param_1,tmp_i3,param_2);
      if (tmp_i2 != 0) {
        *(uint *)(tmp_i2 + 0x48) = *(uint *)(tmp_i2 + 0x48) & 0xffffffdf | 0x44;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != tmp_i1);
  }
  return;
}

uint32_t * Menus_FindByName(uint32_t param_1)

{
{  int tmp_i1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  
  if (0 < menuCount) {
    tmp_pu3 = &g_dat_003f16a0;
    tmp_i2 = 0;
    do {
      tmp_i1 = Q_stricmp(*tmp_pu3,param_1);
      if (tmp_i1 == 0) {
        return &Menus + tmp_i2 * 0x346;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pu3 = tmp_pu3 + 0x346;
    } while (tmp_i2 < menuCount);
  }
  return (uint32_t *)0x0;
}

void Menus_CloseAll(void)

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

void Menu_FadeMenuByName(uint32_t param_1,uint32_t param_2,int param_3)

{
{  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  
  if (0 < menuCount) {
    tmp_pu5 = &g_dat_003f16a0;
    tmp_i4 = 0;
    do {
      tmp_i3 = Q_stricmp(*tmp_pu5,param_1);
      if (tmp_i3 == 0) {
        tmp_pi1 = &g_dat_003f1740 + tmp_i4 * 0x346;
        if (*tmp_pi1 < 1) {
          return;
        }
        tmp_i3 = 0;
        if (param_3 == 0) {
          do {
            tmp_i2 = tmp_i4 * 0x346 + tmp_i3;
            tmp_i3 = tmp_i3 + 1;
            *(uint *)((&g_dat_003f1b94)[tmp_i2] + 0x48) =
                 *(uint *)((&g_dat_003f1b94)[tmp_i2] + 0x48) & 0xffffffdf | 0x44;
          } while (tmp_i3 < *tmp_pi1);
          return;
        }
        do {
          tmp_i2 = tmp_i4 * 0x346 + tmp_i3;
          tmp_i3 = tmp_i3 + 1;
          *(uint *)((&g_dat_003f1b94)[tmp_i2] + 0x48) =
               *(uint *)((&g_dat_003f1b94)[tmp_i2] + 0x48) & 0xffffffbf | 0x24;
        } while (tmp_i3 < *tmp_pi1);
        return;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu5 = tmp_pu5 + 0x346;
    } while (tmp_i4 < menuCount);
  }
  return;
}

float * Menu_HitTest(int param_1,float param_2,float param_3)

{
{  float tmp_f1;
  float *pfVar2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  
  if (0 < *(int *)(param_1 + 0xc0)) {
    tmp_i6 = 0;
    do {
      pfVar2 = *(float **)(param_1 + 0x514 + tmp_i6 * 4);
      if (pfVar2 != (float *)0x0) {
        tmp_f1 = *(float *)(&g_dat_0002003c + DC);
        if (1.3333334 < tmp_f1) {
          tmp_f5 = tmp_f1 * 0.75;
          tmp_f3 = param_2 * tmp_f5;
          if (tmp_f5 * *pfVar2 < tmp_f3) {
            tmp_f4 = *pfVar2 + pfVar2[2];
            if (1.3333334 < tmp_f1) {
              tmp_f4 = tmp_f4 * tmp_f5;
            }
            goto LAB_000441fc;
          }
        }
        else if (*pfVar2 < param_2) {
          tmp_f4 = *pfVar2 + pfVar2[2];
          tmp_f3 = param_2;
LAB_000441fc:
          if (((tmp_f3 < tmp_f4) && (pfVar2[1] < param_3)) && (param_3 < pfVar2[1] + pfVar2[3])) {
            return pfVar2;
          }
        }
      }
      tmp_i6 = tmp_i6 + 1;
    } while (tmp_i6 != *(int *)(param_1 + 0xc0));
  }
  return (float *)0x0;
}

void Menus_Activate(int param_1)

{
{  char *tmp_pc1;
  uint *tmp_pu2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  int local_2a0;
  
  if (0 < menuCount) {
    tmp_pu2 = &g_dat_003f16c8;
    tmp_i4 = menuCount * 0x346;
    do {
      *tmp_pu2 = *tmp_pu2 & 0xfffffffc;
      tmp_pu2 = tmp_pu2 + 0x346;
    } while (tmp_pu2 != &g_dat_003f16c8 + tmp_i4);
  }
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 6;
  if (*(int *)(param_1 + 0xd8) != 0) {
    Item_RunScript_constprop_37();
  }
  tmp_i4 = DC;
  *(uint32_t *)(param_1 + 0xec) = *(uint32_t *)(DC + 0x11c);
  tmp_pc1 = *(char **)(param_1 + 0x4f0);
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 != '\0')) {
    (**(void **)(tmp_i4 + 0xe0))(tmp_pc1,tmp_pc1,0);
  }
  if (0 < menuCount) {
    tmp_pu3 = &Menus;
    local_2a0 = 0;
    do {
      if ((tmp_pu3[0xd] == 5) && (-1 < (int)tmp_pu3[0xc])) {
        (**(void **)(DC + 0xec))(tmp_pu3[0xc]);
        tmp_pu3[0xc] = 0xffffffff;
      }
      if (0 < (int)tmp_pu3[0x30]) {
        tmp_i4 = 0;
        do {
          while( true ) {
            tmp_i5 = tmp_pu3[tmp_i4 + 0x145];
            if ((*(int *)(tmp_i5 + 0x34) == 5) && (-1 < *(int *)(tmp_i5 + 0x30))) break;
            if (*(int *)(tmp_i5 + 200) != 8) goto LAB_00045399;
LAB_000453f0:
            tmp_i4 = tmp_i4 + 1;
            (**(void **)(DC + 0xec))(-*(int *)(tmp_i5 + 0x3c));
            if ((int)tmp_pu3[0x30] <= tmp_i4) goto LAB_00045410;
          }
          (**(void **)(DC + 0xec))(*(int *)(tmp_i5 + 0x30));
          *(uint32_t *)(tmp_i5 + 0x30) = 0xffffffff;
          tmp_i5 = tmp_pu3[tmp_i4 + 0x145];
          if (*(int *)(tmp_i5 + 200) == 8) goto LAB_000453f0;
LAB_00045399:
          tmp_i4 = tmp_i4 + 1;
        } while (tmp_i4 < (int)tmp_pu3[0x30]);
      }
LAB_00045410:
      local_2a0 = local_2a0 + 1;
      tmp_pu3 = tmp_pu3 + 0x346;
    } while (local_2a0 < menuCount);
  }
  return;
}

void Menus_ShowByName(uint32_t param_1)

{
{  int tmp_i1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  
  if (0 < menuCount) {
    tmp_pu3 = &g_dat_003f16a0;
    tmp_i2 = 0;
    do {
      tmp_i1 = Q_stricmp(*tmp_pu3,param_1);
      if (tmp_i1 == 0) {
        Menus_Activate();
        return;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pu3 = tmp_pu3 + 0x346;
    } while (tmp_i2 < menuCount);
  }
  return;
}

int Display_VisibleMenuCount(void)

{
{  int tmp_i1;
  uint *tmp_pu2;
  
  if (menuCount < 1) {
    tmp_i1 = 0;
  }
  else {
    tmp_pu2 = &g_dat_003f16c8;
    tmp_i1 = 0;
    do {
      if ((*tmp_pu2 & 0x100004) != 0) {
        tmp_i1 = tmp_i1 + 1;
      }
      tmp_pu2 = tmp_pu2 + 0x346;
    } while (tmp_pu2 != &g_dat_003f16c8 + menuCount * 0x346);
  }
  return tmp_i1;
}

void Menu_Paint_part_20(uint32_t *param_1,int param_2)

{
{  int tmp_i1;
  int tmp_i2;
  long double tmp_l3;
  uint32_t local_294;
  uint32_t local_290;
  uint32_t local_28c;
  uint32_t local_288;
  uint32_t *local_1a8;
  
  if (param_2 != 0) {
    param_1[0x12] = param_1[0x12] | 0x100000;
  }
  if (param_1[0x2f] != 0) {
    (**(void **)(DC + 8))(0,0,0x44200000,0x43f00000,param_1[0x2d]);
  }
  Window_Paint(param_1,param_1[0x35],param_1[0x34],(float)(int)param_1[0x33]);
  if ((int)param_1[0x30] < 1) {
    (**(void **)(DC + 0x74))("ui_showtooltips");
  }
  else {
    tmp_i1 = 0;
    tmp_i2 = 0;
    do {
      Item_Paint(param_1[tmp_i2 + 0x145]);
      if ((*(byte *)(param_1[tmp_i2 + 0x145] + 0x48) & 1) != 0) {
        tmp_i1 = param_1[tmp_i2 + 0x145];
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 < (int)param_1[0x30]);
    tmp_l3 = (long double)(**(void **)(DC + 0x74))("ui_showtooltips");
    if ((((tmp_l3 != (long double)0) && (tmp_i1 != 0)) && (tmp_i1 = *(int *)(tmp_i1 + 0x270), tmp_i1 != 0)
        ) && ((*(char **)(tmp_i1 + 0xe8) != (char *)0x0 && (**(char **)(tmp_i1 + 0xe8) != '\0')))) {
      Item_Paint(tmp_i1);
    }
  }
  if (param_1[0x3b] == 0) {
    param_1[0x3b] = *(uint32_t *)(DC + 0x11c);
  }
  else if ((((*(byte *)(param_1 + 0x12) & 4) != 0) && (0 < (int)param_1[0x3a])) &&
          ((param_1[0x3c] != 0 && ((int)(param_1[0x3b] + param_1[0x3a]) <= *(int *)(DC + 0x11c)))))
  {
    local_1a8 = param_1;
    Item_RunScript_constprop_37();
  }
  if (debugMode != 0) {
    local_288 = 0x3f800000;
    local_28c = 0x3f800000;
    local_294 = 0x3f800000;
    local_290 = 0;
    (**(void **)(DC + 0x40))(*param_1,param_1[1],param_1[2],param_1[3],0x3f800000,&local_294);
  }
  return;
}

void Menu_Init(uint32_t *param_1)

{
{  uint32_t tmp_u1;
  bool tmp_b2;
  int tmp_i3;
  uint tmp_u4;
  uint tmp_u5;
  uint32_t *tmp_pu6;
  
  tmp_u5 = 0xd18;
  tmp_b2 = false;
  if (((uint)param_1 & 1) == 0) {
    tmp_pu6 = param_1;
    if (((uint)param_1 & 2) != 0) {
LAB_0004a800:
      *(uint16_t *)tmp_pu6 = 0;
      tmp_u5 = tmp_u5 - 2;
      tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
    }
  }
  else {
    tmp_pu6 = (uint32_t *)((int)param_1 + 1);
    tmp_u5 = 0xd17;
    tmp_b2 = true;
    *(uint8_t *)param_1 = 0;
    if (((uint)tmp_pu6 & 2) != 0) {
      tmp_u5 = 0xd17;
      tmp_b2 = true;
      goto LAB_0004a800;
    }
  }
  if (((uint)tmp_pu6 & 4) != 0) {
    *tmp_pu6 = 0;
    tmp_u5 = tmp_u5 - 4;
    tmp_pu6 = tmp_pu6 + 1;
  }
  for (tmp_u4 = tmp_u5 >> 2; tmp_u4 != 0; tmp_u4 = tmp_u4 - 1) {
    *tmp_pu6 = 0;
    tmp_pu6 = tmp_pu6 + 1;
  }
  if ((tmp_u5 & 2) != 0) {
    *(uint16_t *)tmp_pu6 = 0;
    tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
  }
  if (tmp_b2) {
    *(uint8_t *)tmp_pu6 = 0;
  }
  param_1[0x32] = 0xffffffff;
  tmp_i3 = DC;
  tmp_u5 = 0xb8;
  tmp_b2 = false;
  param_1[0x35] = *(uint32_t *)(DC + 0x1e32c);
  param_1[0x34] = *(uint32_t *)(tmp_i3 + 0x1e324);
  tmp_u1 = *(uint32_t *)(tmp_i3 + 0x1e328);
  param_1[0x345] = 0;
  param_1[0x33] = tmp_u1;
  if (((uint)param_1 & 1) == 0) {
    tmp_pu6 = param_1;
    if (((uint)param_1 & 2) == 0) goto LAB_0004a761;
  }
  else {
    tmp_pu6 = (uint32_t *)((int)param_1 + 1);
    tmp_u5 = 0xb7;
    tmp_b2 = true;
    *(uint8_t *)param_1 = 0;
    if (((uint)tmp_pu6 & 2) == 0) goto LAB_0004a761;
    tmp_u5 = 0xb7;
    tmp_b2 = true;
  }
  *(uint16_t *)tmp_pu6 = 0;
  tmp_u5 = tmp_u5 - 2;
  tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
LAB_0004a761:
  tmp_u4 = 0;
  do {
    *(uint32_t *)((int)tmp_pu6 + tmp_u4) = 0;
    *(uint32_t *)((int)tmp_pu6 + tmp_u4 + 4) = 0;
    tmp_u4 = tmp_u4 + 8;
  } while (tmp_u4 < (tmp_u5 & 0xfffffff8));
  tmp_pu6 = (uint32_t *)((int)tmp_pu6 + tmp_u4);
  if ((tmp_u5 & 4) != 0) {
    *tmp_pu6 = 0;
    tmp_pu6 = tmp_pu6 + 1;
  }
  if ((tmp_u5 & 2) != 0) {
    *(uint16_t *)tmp_pu6 = 0;
    tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
  }
  if (tmp_b2) {
    *(uint8_t *)tmp_pu6 = 0;
  }
  param_1[0x11] = 0x3f800000;
  param_1[0x20] = 0x3f800000;
  param_1[0x1f] = 0x3f800000;
  param_1[0x1e] = 0x3f800000;
  param_1[0x1d] = 0x3f800000;
  param_1[0xc] = 0xffffffff;
  return;
}

int Menu_GetFocusedItem(int param_1)

{
{  int tmp_i1;
  int tmp_i2;
  
  if ((param_1 == 0) || (*(int *)(param_1 + 0xc0) < 1)) {
LAB_0004a89a:
    tmp_i1 = 0;
  }
  else {
    tmp_i1 = *(int *)(param_1 + 0x514);
    if ((*(byte *)(tmp_i1 + 0x48) & 2) == 0) {
      tmp_i2 = 0;
      do {
        tmp_i2 = tmp_i2 + 1;
        if (tmp_i2 == *(int *)(param_1 + 0xc0)) goto LAB_0004a89a;
        tmp_i1 = *(int *)(param_1 + 0x514 + tmp_i2 * 4);
      } while ((*(byte *)(tmp_i1 + 0x48) & 2) == 0);
    }
  }
  return tmp_i1;
}

uint32_t * Menu_GetFocused(void)

{
{  uint tmp_u1;
  uint *tmp_pu2;
  int tmp_i3;
  
  if (menuCount < 1) {
    return (uint32_t *)0x0;
  }
  if ((g_dat_003f16c8 & 6) == 6) {
    tmp_i3 = 0;
  }
  else {
    tmp_pu2 = &g_dat_003f23e0;
    tmp_i3 = 0;
    do {
      tmp_i3 = tmp_i3 + 1;
      if (tmp_i3 == menuCount) {
        return (uint32_t *)0x0;
      }
      tmp_u1 = *tmp_pu2;
      tmp_pu2 = tmp_pu2 + 0x346;
    } while ((tmp_u1 & 6) != 6);
  }
  return &Menus + tmp_i3 * 0x346;
}

void Menu_SetFeederSelection(uint32_t *param_1,int param_2,int param_3,int param_4)

{
{  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  uint *tmp_pu4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  
  if (param_1 == (uint32_t *)0x0) {
    if (param_4 == 0) {
      if (menuCount < 1) {
        return;
      }
      if ((g_dat_003f16c8 & 6) == 6) {
        tmp_i6 = 0;
      }
      else {
        tmp_pu4 = &g_dat_003f23e0;
        tmp_i6 = 0;
        do {
          tmp_i6 = tmp_i6 + 1;
          if (tmp_i6 == menuCount) {
            return;
          }
          tmp_u2 = *tmp_pu4;
          tmp_pu4 = tmp_pu4 + 0x346;
        } while ((tmp_u2 & 6) != 6);
      }
      param_1 = &Menus + tmp_i6 * 0x346;
    }
    else {
      if (menuCount < 1) {
        return;
      }
      tmp_pu5 = &g_dat_003f16a0;
      tmp_i6 = 0;
      while (tmp_i3 = Q_stricmp(*tmp_pu5,param_4), tmp_i3 != 0) {
        tmp_i6 = tmp_i6 + 1;
        tmp_pu5 = tmp_pu5 + 0x346;
        if (menuCount <= tmp_i6) {
          return;
        }
      }
      param_1 = &Menus + tmp_i6 * 0x346;
    }
  }
  if (0 < (int)param_1[0x30]) {
    tmp_i6 = param_1[0x145];
    tmp_f1 = *(float *)(tmp_i6 + 0x248);
    tmp_i3 = 0;
    while( true ) {
      if (tmp_f1 == (float)param_2) {
        if (param_3 == 0) {
          tmp_pu5 = *(uint32_t **)(tmp_i6 + 0x250);
          tmp_pu5[3] = 0;
          *tmp_pu5 = 0;
          tmp_i6 = param_1[tmp_i3 + 0x145];
        }
        *(int *)(tmp_i6 + 0x24c) = param_3;
        (**(void **)(DC + 0xa0))
                  (*(uint32_t *)(param_1[tmp_i3 + 0x145] + 0x248),
                   *(uint32_t *)(param_1[tmp_i3 + 0x145] + 0x24c));
        return;
      }
      if (tmp_i3 + 1 == param_1[0x30]) break;
      tmp_i6 = param_1[tmp_i3 + 0x146];
      tmp_f1 = *(float *)(tmp_i6 + 0x248);
      tmp_i3 = tmp_i3 + 1;
    }
  }
  return;
}

uint32_t Menus_AnyFullScreenVisible(void)

{
{  byte *tmp_pb1;
  int tmp_i2;
  
  if (0 < menuCount) {
    tmp_pb1 = (byte *)&g_dat_003f16c8;
    tmp_i2 = 0;
    do {
      if (((*tmp_pb1 & 4) != 0) && (*(int *)(tmp_pb1 + 0x74) != 0)) {
        return 1;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pb1 = tmp_pb1 + 0xd18;
    } while (tmp_i2 != menuCount);
  }
  return 0;
}

uint32_t * Menus_ActivateByName(uint32_t param_1,int param_2)

{
{  uint tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint *tmp_pu4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  uint32_t *local_28;
  int local_24;
  uint32_t *local_20;
  
  if (menuCount < 1) {
    local_20 = (uint32_t *)0x0;
  }
  else {
    if ((g_dat_003f16c8 & 6) == 6) {
      tmp_i5 = 0;
    }
    else {
      tmp_pu4 = &g_dat_003f23e0;
      tmp_i5 = 0;
      do {
        tmp_i5 = tmp_i5 + 1;
        if (tmp_i5 == menuCount) {
          local_28 = (uint32_t *)0x0;
          goto LAB_0004ab3f;
        }
        tmp_u1 = *tmp_pu4;
        tmp_pu4 = tmp_pu4 + 0x346;
      } while ((tmp_u1 & 6) != 6);
    }
    local_28 = &Menus + tmp_i5 * 0x346;
LAB_0004ab3f:
    tmp_pu4 = &g_dat_003f16c8;
    tmp_i5 = 0;
    do {
      tmp_i2 = Q_stricmp(tmp_pu4[-10],param_1);
      tmp_i3 = menuCount;
      if (tmp_i2 == 0) {
        local_20 = &Menus + tmp_i5 * 0x346;
        Menus_Activate(local_20);
        tmp_i3 = menuCount;
        if ((param_2 != 0) && ((*(byte *)((int)&g_dat_003f16c8 + tmp_i5 * 0xd18 + 3) & 4) != 0)) {
          if (0xf < modalMenuCount) {
            Com_Error(2,"MAX_MODAL_MENUS exceeded\n");
          }
          tmp_i5 = modalMenuCount * 4;
          modalMenuCount = modalMenuCount + 1;
          *(uint32_t **)(modalMenuStack + tmp_i5) = local_28;
          tmp_i3 = menuCount;
        }
        goto LAB_0004aba8;
      }
      tmp_i5 = tmp_i5 + 1;
      *tmp_pu4 = *tmp_pu4 & 0xfffffffc;
      tmp_pu4 = tmp_pu4 + 0x346;
    } while (tmp_i5 < tmp_i3);
    local_20 = (uint32_t *)0x0;
LAB_0004aba8:
    if (0 < tmp_i3) {
      tmp_pu6 = &Menus;
      local_24 = 0;
      do {
        if ((tmp_pu6[0xd] == 5) && (-1 < (int)tmp_pu6[0xc])) {
          (**(void **)(DC + 0xec))(tmp_pu6[0xc]);
          tmp_pu6[0xc] = 0xffffffff;
        }
        if (0 < (int)tmp_pu6[0x30]) {
          tmp_i5 = 0;
          do {
            while( true ) {
              tmp_i3 = tmp_pu6[tmp_i5 + 0x145];
              if ((*(int *)(tmp_i3 + 0x34) == 5) && (-1 < *(int *)(tmp_i3 + 0x30))) break;
              if (*(int *)(tmp_i3 + 200) != 8) goto LAB_0004abe9;
LAB_0004ac40:
              tmp_i5 = tmp_i5 + 1;
              (**(void **)(DC + 0xec))(-*(int *)(tmp_i3 + 0x3c));
              if ((int)tmp_pu6[0x30] <= tmp_i5) goto LAB_0004ac60;
            }
            (**(void **)(DC + 0xec))(*(int *)(tmp_i3 + 0x30));
            *(uint32_t *)(tmp_i3 + 0x30) = 0xffffffff;
            tmp_i3 = tmp_pu6[tmp_i5 + 0x145];
            if (*(int *)(tmp_i3 + 200) == 8) goto LAB_0004ac40;
LAB_0004abe9:
            tmp_i5 = tmp_i5 + 1;
          } while (tmp_i5 < (int)tmp_pu6[0x30]);
        }
LAB_0004ac60:
        local_24 = local_24 + 1;
        tmp_pu6 = tmp_pu6 + 0x346;
      } while (local_24 < menuCount);
    }
  }
  return local_20;
}

void Menus_CloseByName(uint32_t param_1)

{
{  int tmp_i1;
  int *tmp_pi2;
  uint tmp_u3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  
  if (0 < menuCount) {
    tmp_pu5 = &g_dat_003f16a0;
    tmp_i4 = 0;
    do {
      tmp_i1 = Q_stricmp(*tmp_pu5,param_1);
      if (tmp_i1 == 0) {
        tmp_i1 = g_editItem;
        if (0 < (int)(&g_dat_003f1740)[tmp_i4 * 0x346]) {
          tmp_pi2 = &g_dat_003f1b94 + tmp_i4 * 0x346;
          do {
            if (*tmp_pi2 == g_editItem) {
              tmp_i1 = 0;
              g_editingField = 0;
              g_editItem = 0;
            }
            tmp_pi2 = tmp_pi2 + 1;
          } while (tmp_pi2 != &Menus + (&g_dat_003f1740)[tmp_i4 * 0x346] + 0x145 + tmp_i4 * 0x346);
        }
        g_editItem = tmp_i1;
        (&g_dat_003f1748)[tmp_i4 * 0x346] = 0xffffffff;
        Menu_ClearFocus(&Menus + tmp_i4 * 0x346);
        tmp_u3 = (&g_dat_003f16c8)[tmp_i4 * 0x346];
        if ((tmp_u3 & 4) != 0) {
          Menu_RunCloseScript_part_10();
          tmp_u3 = (&g_dat_003f16c8)[tmp_i4 * 0x346];
        }
        (&g_dat_003f16c8)[tmp_i4 * 0x346] = tmp_u3 & 0xfffffff8;
        if ((tmp_u3 & 0x4000000) == 0) {
          return;
        }
        if (modalMenuCount < 1) {
          Com_Printf("^3WARNING: tried closing a modal window with an empty modal stack!\n");
          return;
        }
        modalMenuCount = modalMenuCount + -1;
        if (*(int *)(modalMenuStack + modalMenuCount * 4) == 0) {
          return;
        }
        Menus_ActivateByName
                  (*(uint32_t *)(*(int *)(modalMenuStack + modalMenuCount * 4) + 0x20),0);
        return;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu5 = tmp_pu5 + 0x346;
    } while (tmp_i4 < menuCount);
  }
  return;
}

void Menu_ScrollFeeder(int param_1,int param_2,int param_3)

{
{  int tmp_i1;
  int tmp_i2;
  
  if ((param_1 != 0) && (0 < *(int *)(param_1 + 0xc0))) {
    tmp_i2 = *(int *)(param_1 + 0x514);
    if (*(float *)(tmp_i2 + 0x248) != (float)param_2) {
      tmp_i1 = 0;
      do {
        tmp_i1 = tmp_i1 + 1;
        if (tmp_i1 == *(int *)(param_1 + 0xc0)) {
          return;
        }
        tmp_i2 = *(int *)(param_1 + 0x514 + tmp_i1 * 4);
      } while (*(float *)(tmp_i2 + 0x248) != (float)param_2);
    }
    Item_ListBox_HandleKey(tmp_i2,0x85 - (uint)(param_3 == 0),1,1);
    return;
  }
  return;
}

void Menu_HandleMouseMove(int param_1,float param_2,float param_3)

{
{  uint *tmp_pu1;
  byte tmp_b2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  bool tmp_b7;
  int tmp_i8;
  uint32_t tmp_u9;
  int tmp_i10;
  float *pfVar11;
  int *tmp_pi12;
  int local_20;
  
  if ((param_1 != 0) && ((*(uint *)(param_1 + 0x48) & 0x100004) != 0)) {
    if (itemCapture == 0) {
      if ((g_waitingForKey == 0) && (g_editingField == 0)) {
        tmp_i8 = *(int *)(param_1 + 0xc0);
        local_20 = 0;
        tmp_b7 = false;
        while (tmp_i8 < 1) {
LAB_0004c548:
          if (tmp_b7) {
            return;
          }
          tmp_b7 = true;
        }
        tmp_pi12 = (int *)(param_1 + 0x514);
        tmp_i10 = 1;
        do {
          pfVar11 = (float *)*tmp_pi12;
          if (((uint)pfVar11[0x12] & 0x100004) == 0) {
LAB_0004c3d0:
            tmp_i8 = *(int *)(param_1 + 0xc0);
            if (tmp_i8 <= tmp_i10) goto LAB_0004c548;
          }
          else {
            tmp_f3 = pfVar11[0x48];
            if (((uint)tmp_f3 & 3) != 0) {
              tmp_i8 = Item_EnableShowViaCvar(pfVar11,1);
              if (tmp_i8 == 0) goto LAB_0004c3d0;
              pfVar11 = (float *)*tmp_pi12;
              tmp_f3 = pfVar11[0x48];
            }
            if (((uint)tmp_f3 & 0xc) == 0) {
              tmp_b2 = *(byte *)(pfVar11 + 0x98);
            }
            else {
              tmp_i8 = Item_EnableShowViaCvar(pfVar11,4);
              if (tmp_i8 == 0) goto LAB_0004c3d0;
              pfVar11 = (float *)*tmp_pi12;
              tmp_b2 = *(byte *)(pfVar11 + 0x98);
            }
            if ((tmp_b2 & 3) == 0) {
              tmp_f3 = pfVar11[0x99];
            }
            else {
              tmp_i8 = Item_SettingShow_constprop_35();
              if (tmp_i8 == 0) goto LAB_0004c3d0;
              pfVar11 = (float *)*tmp_pi12;
              tmp_f3 = pfVar11[0x99];
            }
            if (tmp_f3 != 0.0) {
              tmp_i8 = Item_SettingShow_constprop_36();
              if (tmp_i8 == 0) goto LAB_0004c3d0;
              pfVar11 = (float *)*tmp_pi12;
            }
            if (pfVar11 == (float *)0x0) {
LAB_0004c3c0:
              if (((uint)pfVar11[0x12] & 1) != 0) {
                if (((uint)pfVar11[0x12] & 0x80) != 0) {
                  Item_RunScript_constprop_37();
                  pfVar11[0x12] = (float)((uint)pfVar11[0x12] & 0xffffff7f);
                }
                Item_RunScript_constprop_37();
                pfVar11[0x12] = (float)((uint)pfVar11[0x12] & 0xffffe7ff);
                if (*tmp_pi12 != 0) {
                  tmp_pu1 = (uint *)(*tmp_pi12 + 0x48);
                  *tmp_pu1 = *tmp_pu1 & 0xfffffffe;
                }
              }
              goto LAB_0004c3d0;
            }
            tmp_f3 = *(float *)(&g_dat_0002003c + DC);
            if (tmp_f3 <= 1.3333334) {
              if (*pfVar11 < param_2) {
                tmp_f6 = *pfVar11 + pfVar11[2];
                tmp_f5 = param_2;
                goto LAB_0004c372;
              }
              goto LAB_0004c3c0;
            }
            tmp_f4 = tmp_f3 * 0.75;
            tmp_f5 = param_2 * tmp_f4;
            if (tmp_f5 <= tmp_f4 * *pfVar11) goto LAB_0004c3c0;
            tmp_f6 = *pfVar11 + pfVar11[2];
            if (1.3333334 < tmp_f3) {
              tmp_f6 = tmp_f4 * tmp_f6;
            }
LAB_0004c372:
            if (((tmp_f6 <= tmp_f5) || (param_3 <= pfVar11[1])) ||
               (pfVar11[1] + pfVar11[3] <= param_3)) goto LAB_0004c3c0;
            if (!tmp_b7) goto LAB_0004c3d0;
            if ((pfVar11[0x32] == 0.0) && (pfVar11[0x3a] != 0.0)) {
              tmp_u9 = Item_CorrectedTextRect();
              tmp_i8 = Rect_ContainsPoint(tmp_u9,param_2,param_3);
              if (tmp_i8 != 0) goto LAB_0004c528;
            }
            else {
LAB_0004c528:
              if ((((uint)pfVar11[0x12] & 0x24) == 4) &&
                 (Item_MouseEnter(pfVar11,param_2,param_3), local_20 == 0)) {
                local_20 = Item_SetFocus(pfVar11,param_2,param_3);
              }
            }
            if (*(int *)(param_1 + 0xc0) <= tmp_i10) {
              return;
            }
          }
          tmp_pi12 = tmp_pi12 + 1;
          tmp_i10 = tmp_i10 + 1;
        } while( true );
      }
    }
    else if ((*(int *)(itemCapture + 200) == 6) &&
            (tmp_i8 = Rect_ContainsPoint(itemCapture,param_2,param_3), tmp_i8 == 0)) {
      itemCapture = 0;
      captureFunc = 0;
      captureData = 0;
    }
  }
  return;
}

uint32_t Menu_SetPrevCursorItem(int param_1)

{
{  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  float *pfVar5;
  float tmp_f6;
  float tmp_f7;
  bool tmp_b8;
  int tmp_i9;
  int tmp_i10;
  uint tmp_u11;
  int tmp_i12;
  int tmp_i13;
  int tmp_i14;
  
  tmp_i13 = *(int *)(param_1 + 200);
  if (tmp_i13 < 0) {
    tmp_b8 = true;
    tmp_i10 = *(int *)(param_1 + 0xc0) + -1;
    *(int *)(param_1 + 200) = tmp_i10;
  }
  else {
    tmp_b8 = false;
    tmp_i10 = tmp_i13;
  }
LAB_0004c670:
  do {
    if (tmp_i10 < 0) {
LAB_0004c8e0:
      *(int *)(param_1 + 200) = tmp_i13;
      return 0;
    }
    tmp_i10 = tmp_i10 + -1;
    *(int *)(param_1 + 200) = tmp_i10;
    if (tmp_i10 == -1) {
      if (tmp_b8) goto LAB_0004c8e0;
      tmp_i10 = *(int *)(param_1 + 0xc0) + -1;
      *(int *)(param_1 + 200) = tmp_i10;
      if (tmp_i10 < 0) goto LAB_0004c8e0;
      tmp_b8 = true;
    }
    tmp_i9 = DC;
    tmp_i3 = *(int *)(param_1 + 0x514 + tmp_i10 * 4);
    tmp_i14 = *(int *)(DC + 0x128);
    tmp_i4 = *(int *)(DC + 0x124);
  } while ((tmp_i3 == 0) || ((*(uint *)(tmp_i3 + 0x48) & 0x16) != 4));
  tmp_i10 = *(int *)(tmp_i3 + 0xec);
  tmp_u11 = *(uint *)(tmp_i3 + 0x120);
  if ((tmp_u11 & 3) == 0) {
LAB_0004c6d0:
    if (((tmp_u11 & 0xc) == 0) || (tmp_i12 = Item_EnableShowViaCvar(tmp_i3,4), tmp_i12 != 0)) {
      if (((*(byte *)(tmp_i3 + 0x260) & 3) != 0) &&
         (tmp_i12 = Item_SettingShow_constprop_35(), tmp_i12 == 0)) {
        tmp_i10 = *(int *)(param_1 + 200);
        goto LAB_0004c670;
      }
      if ((*(int *)(tmp_i3 + 0x264) == 0) || (tmp_i12 = Item_SettingShow_constprop_36(), tmp_i12 != 0))
      {
        tmp_i12 = Menu_ClearFocus(*(uint32_t *)(tmp_i3 + 0xec));
        tmp_i13 = DC;
        if (*(int *)(tmp_i3 + 200) == 0) {
          tmp_f6 = (float)tmp_i4;
          tmp_f1 = *(float *)(tmp_i3 + 0xb8);
          tmp_f2 = *(float *)(&g_dat_0002003c + DC);
          if (tmp_f2 <= 1.3333334) {
            if (tmp_f1 < tmp_f6) {
LAB_0004c85f:
              if (tmp_f6 < tmp_f1 + *(float *)(tmp_i3 + 0xc0)) {
LAB_0004c875:
                tmp_f1 = *(float *)(tmp_i3 + 0xbc) - *(float *)(tmp_i3 + 0xc4);
                if ((tmp_f1 < (float)tmp_i14) && ((float)tmp_i14 < tmp_f1 + *(float *)(tmp_i3 + 0xc4))) {
                  tmp_i14 = *(int *)(tmp_i3 + 0x124);
                  *(uint *)(tmp_i3 + 0x48) = *(uint *)(tmp_i3 + 0x48) | 2;
                  if (tmp_i14 == 0) {
                    tmp_i14 = *(int *)(tmp_i9 + 0x1e320);
                  }
                  goto LAB_0004c977;
                }
              }
            }
          }
          else {
            tmp_f7 = tmp_f2 * 0.75;
            tmp_f6 = tmp_f6 * tmp_f7;
            if (tmp_f7 * tmp_f1 < tmp_f6) {
              if (tmp_f2 <= 1.3333334) goto LAB_0004c85f;
              if (tmp_f6 < (tmp_f1 + *(float *)(tmp_i3 + 0xc0)) * tmp_f7) goto LAB_0004c875;
            }
          }
          if ((tmp_i12 != 0) &&
             (*(uint *)(tmp_i12 + 0x48) = *(uint *)(tmp_i12 + 0x48) | 2, *(int *)(tmp_i12 + 0x10c) != 0
             )) {
            Item_RunScript_constprop_37();
          }
        }
        else {
          *(uint *)(tmp_i3 + 0x48) = *(uint *)(tmp_i3 + 0x48) | 2;
          if (*(int *)(tmp_i3 + 0x10c) != 0) {
            Item_RunScript_constprop_37();
          }
          tmp_i14 = *(int *)(tmp_i3 + 0x124);
          tmp_i13 = DC;
          if (tmp_i14 == 0) {
            tmp_i14 = *(int *)(tmp_i9 + 0x1e320);
          }
LAB_0004c977:
          (**(void **)(tmp_i13 + 0x88))(tmp_i14,6);
        }
        if (*(int *)(tmp_i10 + 0xc0) < 1) goto LAB_0004c80a;
        tmp_i13 = 0;
        if (tmp_i3 == *(int *)(tmp_i10 + 0x514)) goto LAB_0004c9a0;
        goto LAB_0004c805;
      }
    }
  }
  else {
    tmp_i12 = Item_EnableShowViaCvar(tmp_i3,1);
    if (tmp_i12 != 0) {
      tmp_u11 = *(uint *)(tmp_i3 + 0x120);
      goto LAB_0004c6d0;
    }
  }
  tmp_i10 = *(int *)(param_1 + 200);
  goto LAB_0004c670;
  while (tmp_i3 != *(int *)(tmp_i10 + 0x514 + tmp_i13 * 4)) {
LAB_0004c805:
    tmp_i13 = tmp_i13 + 1;
    if (tmp_i13 == *(int *)(tmp_i10 + 0xc0)) goto LAB_0004c80a;
  }
LAB_0004c9a0:
  *(int *)(tmp_i10 + 200) = tmp_i13;
LAB_0004c80a:
  pfVar5 = *(float **)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
  Menu_HandleMouseMove(param_1,*pfVar5 + 1.0,pfVar5[1] + 1.0);
  return *(uint32_t *)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
}

uint32_t Menu_SetNextCursorItem(int param_1)

{
{  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  float *pfVar6;
  float tmp_f7;
  float tmp_f8;
  int tmp_i9;
  int tmp_i10;
  uint tmp_u11;
  int tmp_i12;
  int tmp_i13;
  bool tmp_b14;
  
  if (param_1 == 0) {
    return 0;
  }
  tmp_i13 = *(int *)(param_1 + 200);
  tmp_b14 = tmp_i13 == -1;
  tmp_i10 = tmp_i13;
  if (tmp_b14) {
    *(uint32_t *)(param_1 + 200) = 0;
    tmp_i10 = 0;
  }
  tmp_i12 = *(int *)(param_1 + 0xc0);
  while (tmp_i10 < tmp_i12) {
    while( true ) {
      tmp_i10 = tmp_i10 + 1;
      *(int *)(param_1 + 200) = tmp_i10;
      if (tmp_i12 <= tmp_i10) {
        if (tmp_b14) {
          return *(uint32_t *)(param_1 + 0x514 + tmp_i13 * 4);
        }
        *(uint32_t *)(param_1 + 200) = 0;
        tmp_i10 = 0;
        tmp_b14 = true;
      }
      tmp_i9 = DC;
      tmp_i3 = *(int *)(DC + 0x128);
      tmp_i4 = *(int *)(DC + 0x124);
      tmp_i5 = *(int *)(param_1 + 0x514 + tmp_i10 * 4);
      if ((tmp_i5 == 0) || ((*(uint *)(tmp_i5 + 0x48) & 0x16) != 4)) break;
      tmp_u11 = *(uint *)(tmp_i5 + 0x120);
      tmp_i10 = *(int *)(tmp_i5 + 0xec);
      if ((tmp_u11 & 3) == 0) {
LAB_0004cb06:
        if (((tmp_u11 & 0xc) != 0) && (tmp_i12 = Item_EnableShowViaCvar(tmp_i5,4), tmp_i12 == 0))
        goto LAB_0004cd01;
        if (((*(byte *)(tmp_i5 + 0x260) & 3) == 0) ||
           (tmp_i12 = Item_SettingShow_constprop_35(), tmp_i12 != 0)) {
          if ((*(int *)(tmp_i5 + 0x264) != 0) &&
             (tmp_i12 = Item_SettingShow_constprop_36(), tmp_i12 == 0)) goto LAB_0004cd01;
          tmp_i12 = Menu_ClearFocus(*(uint32_t *)(tmp_i5 + 0xec));
          tmp_i13 = DC;
          if (*(int *)(tmp_i5 + 200) == 0) {
            tmp_f7 = (float)tmp_i4;
            tmp_f1 = *(float *)(tmp_i5 + 0xb8);
            tmp_f2 = *(float *)(&g_dat_0002003c + DC);
            if (tmp_f2 <= 1.3333334) {
              if (tmp_f1 < tmp_f7) {
LAB_0004cc8f:
                if (tmp_f7 < tmp_f1 + *(float *)(tmp_i5 + 0xc0)) {
LAB_0004cca5:
                  tmp_f1 = *(float *)(tmp_i5 + 0xbc) - *(float *)(tmp_i5 + 0xc4);
                  if ((tmp_f1 < (float)tmp_i3) && ((float)tmp_i3 < tmp_f1 + *(float *)(tmp_i5 + 0xc4))) {
                    tmp_i12 = *(int *)(tmp_i5 + 0x124);
                    *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) | 2;
                    if (tmp_i12 == 0) {
                      tmp_i12 = *(int *)(tmp_i9 + 0x1e320);
                    }
                    goto LAB_0004cd97;
                  }
                }
              }
            }
            else {
              tmp_f8 = tmp_f2 * 0.75;
              tmp_f7 = tmp_f7 * tmp_f8;
              if (tmp_f8 * tmp_f1 < tmp_f7) {
                if (tmp_f2 <= 1.3333334) goto LAB_0004cc8f;
                if (tmp_f7 < (tmp_f1 + *(float *)(tmp_i5 + 0xc0)) * tmp_f8) goto LAB_0004cca5;
              }
            }
            if ((tmp_i12 != 0) &&
               (*(uint *)(tmp_i12 + 0x48) = *(uint *)(tmp_i12 + 0x48) | 2,
               *(int *)(tmp_i12 + 0x10c) != 0)) {
              Item_RunScript_constprop_37();
            }
          }
          else {
            *(uint *)(tmp_i5 + 0x48) = *(uint *)(tmp_i5 + 0x48) | 2;
            if (*(int *)(tmp_i5 + 0x10c) != 0) {
              Item_RunScript_constprop_37();
            }
            tmp_i12 = *(int *)(tmp_i5 + 0x124);
            tmp_i13 = DC;
            if (tmp_i12 == 0) {
              tmp_i12 = *(int *)(tmp_i9 + 0x1e320);
            }
LAB_0004cd97:
            (**(void **)(tmp_i13 + 0x88))(tmp_i12,6);
          }
          if (*(int *)(tmp_i10 + 0xc0) < 1) goto LAB_0004cc3a;
          tmp_i12 = 0;
          tmp_i13 = *(int *)(tmp_i10 + 0x514);
          goto joined_r0x0004cc1b;
        }
        tmp_i10 = *(int *)(param_1 + 200);
        tmp_i12 = *(int *)(param_1 + 0xc0);
      }
      else {
        tmp_i12 = Item_EnableShowViaCvar(tmp_i5,1);
        if (tmp_i12 != 0) {
          tmp_u11 = *(uint *)(tmp_i5 + 0x120);
          goto LAB_0004cb06;
        }
LAB_0004cd01:
        tmp_i10 = *(int *)(param_1 + 200);
        tmp_i12 = *(int *)(param_1 + 0xc0);
      }
      if (tmp_i12 <= tmp_i10) goto LAB_0004cd20;
    }
  }
LAB_0004cd20:
  *(int *)(param_1 + 200) = tmp_i13;
  return 0;
joined_r0x0004cc1b:
  if (tmp_i5 == tmp_i13) {
    *(int *)(tmp_i10 + 200) = tmp_i12;
LAB_0004cc3a:
    pfVar6 = *(float **)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
    Menu_HandleMouseMove(param_1,*pfVar6 + 1.0,pfVar6[1] + 1.0);
    return *(uint32_t *)(param_1 + 0x514 + *(int *)(param_1 + 200) * 4);
  }
  tmp_i12 = tmp_i12 + 1;
  if (tmp_i12 == *(int *)(tmp_i10 + 0xc0)) goto LAB_0004cc3a;
  tmp_i13 = *(int *)(tmp_i10 + 0x514 + tmp_i12 * 4);
  goto joined_r0x0004cc1b;
}

void Menu_HandleKey(int param_1,int param_2,int param_3)

{
{  int tmp_i1;
  bool tmp_b2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  int *tmp_pi6;
  uint *tmp_pu7;
  int tmp_i8;
  uint tmp_u9;
  uint32_t *tmp_pu10;
  long double tmp_l11;
  
  Menu_HandleMouseMove(param_1,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128));
  if (param_3 == 0) {
    tmp_b2 = false;
    goto LAB_0004d60d;
  }
  if (((param_2 == 0xa9) || (param_2 == 0xd)) && (*(int *)(param_1 + 0xe4) != 0)) goto LAB_0004d84e;
  if (g_waitingForKey != 0) {
    Item_Bind_HandleKey(g_bindItem,param_2,param_3);
    return;
  }
  if (g_editingField == 0) {
LAB_0004d9a9:
    tmp_b2 = true;
LAB_0004d60d:
    if (param_1 == 0) {
      return;
    }
    if (tmp_b2) goto LAB_0004d6d0;
  }
  else {
    tmp_i4 = Item_TextField_HandleKey(g_editItem,param_2);
    if (tmp_i4 == 0) {
      g_editItem = 0;
      g_editingField = 0;
      return;
    }
    if (2 < param_2 - 0xb2U) {
      if (param_2 - 0x84U < 2) {
        return;
      }
      tmp_b2 = true;
      if (param_2 == 9) {
        return;
      }
      goto LAB_0004d60d;
    }
    g_editingField = 0;
    g_editItem = 0;
    tmp_i4 = *(int *)(DC + 0x128);
    tmp_i3 = *(int *)(DC + 0x124);
    if (menuCount < 1) goto LAB_0004d9a9;
    if ((g_dat_003f16c8 & 6) == 6) {
      tmp_i8 = 0;
      tmp_u9 = g_dat_003f16c8;
    }
    else {
      tmp_pu7 = &g_dat_003f23e0;
      tmp_i8 = 0;
      do {
        tmp_i8 = tmp_i8 + 1;
        if (tmp_i8 == menuCount) goto LAB_0004db28;
        tmp_u9 = *tmp_pu7;
        tmp_pu7 = tmp_pu7 + 0x346;
      } while ((tmp_u9 & 6) != 6);
    }
    if ((tmp_u9 & 0x200000) == 0) {
LAB_0004db28:
      tmp_i8 = 0;
      tmp_pu10 = &Menus;
      do {
        tmp_i8 = tmp_i8 + 1;
        Menu_HandleMouseMove(tmp_pu10,(float)tmp_i3,(float)tmp_i4);
        tmp_pu10 = tmp_pu10 + 0x346;
      } while (tmp_i8 < menuCount);
      tmp_b2 = true;
      goto LAB_0004d60d;
    }
    Menu_HandleMouseMove(&Menus + tmp_i8 * 0x346,(float)tmp_i3,(float)tmp_i4);
    if (param_1 == 0) {
      return;
    }
LAB_0004d6d0:
    if ((((*(byte *)(param_1 + 0x4a) & 0x20) == 0) &&
        (tmp_i4 = Rect_ContainsPoint(param_1,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128))
        , tmp_i4 == 0)) && ((inHandleKey_10166 == 0 && (param_2 - 0xb2U < 3)))) {
      inHandleKey_10166 = 1;
      Menus_HandleOOBClick(param_1,param_2,param_3);
      inHandleKey_10166 = 0;
      return;
    }
  }
  if (*(int *)(param_1 + 0xc0) < 1) {
    tmp_i4 = 0;
  }
  else {
    tmp_i4 = 0;
    tmp_pi6 = (int *)(param_1 + 0x514);
    do {
      if ((*(byte *)(*tmp_pi6 + 0x48) & 2) != 0) {
        tmp_i4 = *tmp_pi6;
      }
      tmp_pi6 = tmp_pi6 + 1;
    } while (tmp_pi6 != (int *)(*(int *)(param_1 + 0xc0) * 4 + 0x514 + param_1));
    if ((tmp_i4 != 0) && (tmp_i3 = Item_HandleKey(tmp_i4,param_2,param_3), tmp_i3 != 0))
    goto LAB_0004d677;
  }
  if (param_3 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0xd14) == 0) {
    if ((param_2 - 1U < 0xff) && (*(int *)(param_1 + 0xf4 + param_2 * 4) != 0)) goto LAB_0004d84e;
  }
  else if ((param_2 - 1U < 0xff) && (tmp_i3 = *(int *)(param_1 + 0xc0), 0 < tmp_i3)) {
    tmp_i8 = 0;
    do {
      tmp_i1 = *(int *)(param_1 + 0x514 + tmp_i8 * 4);
      if (*(int *)(tmp_i1 + 0x254) == param_2) {
        tmp_i3 = Item_EnableShowViaCvar(tmp_i1,4);
        if (tmp_i3 != 0) {
          Item_RunScript_constprop_37();
          return;
        }
        tmp_i3 = *(int *)(param_1 + 0xc0);
      }
      tmp_i8 = tmp_i8 + 1;
    } while (tmp_i8 < tmp_i3);
  }
  if (param_2 == 0x9c) {
    tmp_l11 = (long double)(**(void **)(DC + 0x74))("developer");
    if (tmp_l11 == (long double)0) {
      return;
    }
    (**(void **)(DC + 200))(2,"screenshot\n");
    return;
  }
  if (param_2 < 0x9d) {
    if (param_2 == 0x1b) {
      if (g_waitingForKey != 0) {
        return;
      }
      if (*(int *)(param_1 + 0xe0) == 0) {
        return;
      }
LAB_0004d84e:
      Item_RunScript_constprop_37();
      return;
    }
    if (0x1b < param_2) {
      if (param_2 != 0x85) {
        if (param_2 == 0x9b) {
          tmp_l11 = (long double)(**(void **)(DC + 0x74))("developer");
          if (tmp_l11 == (long double)0) {
            return;
          }
          debugMode = debugMode ^ 1;
          return;
        }
        if (param_2 != 0x84) {
          return;
        }
        goto LAB_0004da0a;
      }
LAB_0004d99f:
      Menu_SetNextCursorItem(param_1);
      return;
    }
    if (param_2 == 9) {
      tmp_i4 = (**(void **)(DC + 0xc0))(0x8a);
      if (tmp_i4 != 0) {
        Menu_SetPrevCursorItem(param_1);
        return;
      }
      goto LAB_0004d99f;
    }
    if (param_2 != 0xd) {
      return;
    }
  }
  else if (param_2 != 0xa9) {
    if (param_2 < 0xaa) {
      if (param_2 != 0xa1) {
        if (param_2 != 0xa7) {
          return;
        }
        goto LAB_0004d99f;
      }
LAB_0004da0a:
      Menu_SetPrevCursorItem(param_1);
      return;
    }
    if (param_2 < 0xb2) {
      return;
    }
    if (param_2 < 0xb4) {
      if (tmp_i4 == 0) {
        return;
      }
      tmp_i3 = *(int *)(tmp_i4 + 200);
      if (tmp_i3 == 0) {
        tmp_i4 = *(int *)(DC + 0x128);
        tmp_i3 = *(int *)(DC + 0x124);
        tmp_u5 = Item_CorrectedTextRect();
        tmp_i4 = Rect_ContainsPoint(tmp_u5,(float)tmp_i3,(float)tmp_i4);
        if (tmp_i4 == 0) {
          return;
        }
        goto LAB_0004d677;
      }
      if ((tmp_i3 != 9) && (tmp_i3 != 4)) {
        tmp_i4 = Rect_ContainsPoint(tmp_i4,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128));
        if (tmp_i4 == 0) {
          return;
        }
        goto LAB_0004d677;
      }
      tmp_i3 = Rect_ContainsPoint(tmp_i4,(float)*(int *)(DC + 0x124),(float)*(int *)(DC + 0x128));
      if (tmp_i3 == 0) {
        return;
      }
      if (*(int *)(tmp_i4 + 0x250) != 0) {
        *(uint32_t *)(*(int *)(tmp_i4 + 0x250) + 0x18) = 0;
      }
      goto LAB_0004da3f;
    }
    if (param_2 != 0xb4) {
      return;
    }
  }
  if (tmp_i4 == 0) {
    return;
  }
  if ((*(int *)(tmp_i4 + 200) != 9) && (*(int *)(tmp_i4 + 200) != 4)) {
LAB_0004d677:
    Item_RunScript_constprop_37();
    return;
  }
LAB_0004da3f:
  *(uint32_t *)(tmp_i4 + 0x24c) = 0;
  g_editingField = 1;
  g_editItem = tmp_i4;
  return;
}

void Menus_HandleOOBClick(int param_1,uint32_t param_2,int param_3)

{
{  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint *tmp_pu6;
  void *tmp_pc7;
  uint tmp_u8;
  int tmp_i9;
  uint32_t *tmp_pu10;
  int tmp_i11;
  int local_38;
  int local_34;
  int local_28;
  
  if (param_1 == 0) {
    return;
  }
  if ((param_3 == 0) || (tmp_u8 = *(uint *)(param_1 + 0x48), (tmp_u8 & 0x20000) == 0)) {
    if (menuCount < 1) goto LAB_0004dff4;
LAB_0004dc7a:
    local_38 = 0;
    tmp_pu10 = &Menus;
    local_28 = menuCount;
    do {
      tmp_i9 = DC;
      if ((tmp_pu10[0x12] & 0x100004) != 0) {
        tmp_f1 = (float)*(int *)(DC + 0x128);
        tmp_f2 = (float)*(int *)(DC + 0x124);
        tmp_i3 = Rect_ContainsPoint(tmp_pu10,tmp_f2,tmp_f1);
        if ((tmp_i3 != 0) && (tmp_i3 = tmp_pu10[0x30], 0 < tmp_i3)) {
          tmp_i11 = 0;
          do {
            tmp_i5 = tmp_pu10[tmp_i11 + 0x145];
            if ((((*(uint *)(tmp_i5 + 0x48) & 0x100004) != 0) &&
                ((*(uint *)(tmp_i5 + 0x48) & 0x10) == 0)) &&
               (tmp_i4 = Rect_ContainsPoint(tmp_i5,tmp_f2,tmp_f1), tmp_i4 != 0)) {
              if ((*(int *)(tmp_i5 + 200) == 0) && (*(int *)(tmp_i5 + 0xe8) != 0)) {
                rect_10156 = *(uint32_t *)(tmp_i5 + 0xb8);
                g_dat_0008c160 = *(float *)(tmp_i5 + 0xbc);
                g_dat_0008c164 = *(float *)(tmp_i5 + 0xc0);
                g_dat_0008c168 = *(float *)(tmp_i5 + 0xc4);
                if (g_dat_0008c164 != 0.0) {
                  g_dat_0008c160 = g_dat_0008c160 - g_dat_0008c168;
                }
                tmp_i5 = Rect_ContainsPoint(&rect_10156,tmp_f2,tmp_f1);
                if (tmp_i5 == 0) goto LAB_0004dd00;
              }
              *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xfffffffc;
              tmp_pu10[0x12] = tmp_pu10[0x12] | 6;
              Menu_HandleMouseMove
                        (tmp_pu10,(float)*(int *)(tmp_i9 + 0x124),(float)*(int *)(tmp_i9 + 0x128));
              Menu_HandleKey(tmp_pu10,param_2,param_3);
              local_28 = menuCount;
              break;
            }
LAB_0004dd00:
            tmp_i11 = tmp_i11 + 1;
          } while (tmp_i11 != tmp_i3);
        }
      }
      local_38 = local_38 + 1;
      tmp_pu10 = tmp_pu10 + 0x346;
    } while (local_38 < local_28);
    if (0 < local_28) {
      tmp_pu6 = &g_dat_003f16c8;
      tmp_i9 = 0;
      do {
        if ((*tmp_pu6 & 0x100004) != 0) {
          tmp_i9 = tmp_i9 + 1;
        }
        tmp_pu6 = tmp_pu6 + 0x346;
      } while (tmp_pu6 != &g_dat_003f16c8 + local_28 * 0x346);
      if (tmp_i9 != 0) goto LAB_0004de8d;
    }
    tmp_pc7 = *(void **)(DC + 0xd4);
    if (tmp_pc7 == (void *)0x0) goto LAB_0004de8d;
  }
  else {
    if ((tmp_u8 & 4) != 0) {
      Menu_RunCloseScript_part_10();
      tmp_u8 = *(uint *)(param_1 + 0x48);
    }
    *(uint *)(param_1 + 0x48) = tmp_u8 & 0xfffffff8;
    if (0 < menuCount) goto LAB_0004dc7a;
LAB_0004dff4:
    tmp_pc7 = *(void **)(DC + 0xd4);
    if (tmp_pc7 == (void *)0x0) {
      return;
    }
  }
  (*tmp_pc7)(0);
  local_28 = menuCount;
LAB_0004de8d:
  if (0 < local_28) {
    tmp_pu10 = &Menus;
    local_34 = 0;
    do {
      if ((tmp_pu10[0xd] == 5) && (-1 < (int)tmp_pu10[0xc])) {
        (**(void **)(DC + 0xec))(tmp_pu10[0xc]);
        tmp_pu10[0xc] = 0xffffffff;
      }
      if (0 < (int)tmp_pu10[0x30]) {
        tmp_i9 = 0;
        do {
          while ((tmp_i3 = tmp_pu10[tmp_i9 + 0x145], *(int *)(tmp_i3 + 0x34) != 5 ||
                 (*(int *)(tmp_i3 + 0x30) < 0))) {
            if (*(int *)(tmp_i3 + 200) != 8) goto LAB_0004ded9;
LAB_0004df30:
            tmp_i9 = tmp_i9 + 1;
            (**(void **)(DC + 0xec))(-*(int *)(tmp_i3 + 0x3c));
            if ((int)tmp_pu10[0x30] <= tmp_i9) goto LAB_0004df50;
          }
          (**(void **)(DC + 0xec))(*(int *)(tmp_i3 + 0x30));
          *(uint32_t *)(tmp_i3 + 0x30) = 0xffffffff;
          tmp_i3 = tmp_pu10[tmp_i9 + 0x145];
          if (*(int *)(tmp_i3 + 200) == 8) goto LAB_0004df30;
LAB_0004ded9:
          tmp_i9 = tmp_i9 + 1;
        } while (tmp_i9 < (int)tmp_pu10[0x30]);
      }
LAB_0004df50:
      local_34 = local_34 + 1;
      tmp_pu10 = tmp_pu10 + 0x346;
    } while (local_34 < menuCount);
  }
  return;
}

void Menu_Paint(int param_1,int param_2)

{
{  int tmp_i1;
  
  if ((param_1 == 0) || ((param_2 == 0 && ((*(byte *)(param_1 + 0x48) & 4) == 0)))) {
    return;
  }
  if ((*(int *)(param_1 + 0x40) != 0) &&
     ((*(void **)(DC + 100) != (void *)0x0 &&
      (tmp_i1 = (**(void **)(DC + 100))(*(int *)(param_1 + 0x40)), tmp_i1 == 0)))) {
    return;
  }
  Menu_Paint_part_20();
  return;
}

uint32_t MenuParse_itemDef(int param_1,uint32_t param_2)

{
{  uint16_t *tmp_pu1;
  uint tmp_u2;
  uint16_t *tmp_pu3;
  int tmp_i4;
  uint32_t tmp_u5;
  uint8_t *tmp_pu6;
  int tmp_i7;
  uint32_t *tmp_pu8;
  uint tmp_u9;
  uint32_t tmp_u10;
  bool tmp_b11;
  
  tmp_i4 = *(int *)(param_1 + 0xc0);
  if (tmp_i4 < 0x200) {
    tmp_i7 = tmp_i4;
    if (allocPoint < 0x1ffd89) {
      tmp_pu6 = memoryPool + allocPoint;
      allocPoint = allocPoint + 0x280;
    }
    else {
      outOfMemory = 1;
      if (*(void **)(DC + 0xd0) == (void *)0x0) {
        tmp_pu6 = (uint8_t *)0x0;
      }
      else {
        (**(void **)(DC + 0xd0))("UI_Alloc: Failure. Out of memory!\n");
        tmp_pu6 = (uint8_t *)0x0;
        tmp_i7 = *(int *)(param_1 + 0xc0);
      }
    }
    *(uint8_t **)(param_1 + 0x514 + tmp_i4 * 4) = tmp_pu6;
    tmp_u9 = 0x278;
    tmp_pu1 = *(uint16_t **)(param_1 + 0x514 + tmp_i7 * 4);
    tmp_b11 = ((uint)tmp_pu1 & 1) != 0;
    tmp_pu3 = tmp_pu1;
    if (tmp_b11) {
      *(uint8_t *)tmp_pu1 = 0;
      tmp_pu3 = (uint16_t *)((int)tmp_pu1 + 1);
      tmp_u9 = 0x277;
    }
    if (((uint)tmp_pu3 & 2) != 0) {
      *tmp_pu3 = 0;
      tmp_u9 = tmp_u9 - 2;
      tmp_pu3 = tmp_pu3 + 1;
    }
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)tmp_pu3 + tmp_u2) = 0;
      *(uint32_t *)((int)tmp_pu3 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < (tmp_u9 & 0xfffffff8));
    tmp_pu8 = (uint32_t *)((int)tmp_pu3 + tmp_u2);
    if ((tmp_u9 & 4) != 0) {
      *tmp_pu8 = 0;
      tmp_pu8 = tmp_pu8 + 1;
    }
    if ((tmp_u9 & 2) != 0) {
      *(uint16_t *)tmp_pu8 = 0;
      tmp_pu8 = (uint32_t *)((int)tmp_pu8 + 2);
    }
    if (tmp_b11) {
      *(uint8_t *)tmp_pu8 = 0;
    }
    tmp_b11 = ((uint)tmp_pu1 & 1) != 0;
    tmp_u9 = 0xb8;
    *(uint32_t *)(tmp_pu1 + 0x12a) = 0xffffffff;
    *(uint32_t *)(tmp_pu1 + 0x6e) = 0x3f0ccccd;
    *(uint32_t *)(tmp_pu1 + 0x13a) = 0;
    tmp_pu3 = tmp_pu1;
    if (tmp_b11) {
      *(uint8_t *)tmp_pu1 = 0;
      tmp_pu3 = (uint16_t *)((int)tmp_pu1 + 1);
      tmp_u9 = 0xb7;
    }
    if (((uint)tmp_pu3 & 2) != 0) {
      *tmp_pu3 = 0;
      tmp_u9 = tmp_u9 - 2;
      tmp_pu3 = tmp_pu3 + 1;
    }
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)tmp_pu3 + tmp_u2) = 0;
      *(uint32_t *)((int)tmp_pu3 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < (tmp_u9 & 0xfffffff8));
    tmp_pu8 = (uint32_t *)((int)tmp_pu3 + tmp_u2);
    if ((tmp_u9 & 4) != 0) {
      *tmp_pu8 = 0;
      tmp_pu8 = tmp_pu8 + 1;
    }
    if ((tmp_u9 & 2) != 0) {
      *(uint16_t *)tmp_pu8 = 0;
      tmp_pu8 = (uint32_t *)((int)tmp_pu8 + 2);
    }
    if (tmp_b11) {
      *(uint8_t *)tmp_pu8 = 0;
    }
    *(uint32_t *)(tmp_pu1 + 0x22) = 0x3f800000;
    *(uint32_t *)(tmp_pu1 + 0x40) = 0x3f800000;
    *(uint32_t *)(tmp_pu1 + 0x3e) = 0x3f800000;
    *(uint32_t *)(tmp_pu1 + 0x3c) = 0x3f800000;
    *(uint32_t *)(tmp_pu1 + 0x3a) = 0x3f800000;
    *(uint32_t *)(tmp_pu1 + 0x18) = 0xffffffff;
    tmp_i4 = Item_Parse(param_2,*(uint32_t *)(param_1 + 0x514 + *(int *)(param_1 + 0xc0) * 4));
    tmp_u10 = 0;
    if (tmp_i4 != 0) {
      *(int *)(*(int *)(param_1 + 0x514 + *(int *)(param_1 + 0xc0) * 4) + 0xec) = param_1;
      tmp_i4 = *(int *)(param_1 + 0xc0);
      *(int *)(param_1 + 0xc0) = tmp_i4 + 1;
      tmp_i4 = *(int *)(param_1 + 0x514 + tmp_i4 * 4);
      if (tmp_i4 != 0) {
        if (*(int *)(tmp_i4 + 200) == 6) {
          tmp_pu8 = *(uint32_t **)(tmp_i4 + 0x250);
          *(uint32_t *)(tmp_i4 + 0x24c) = 0;
          if (tmp_pu8 != (uint32_t *)0x0) {
            tmp_pu8[3] = 0;
            *tmp_pu8 = 0;
            tmp_pu8[1] = 0;
          }
        }
        if (*(int *)(tmp_i4 + 0x270) != 0) {
          Tooltip_ComputePosition(tmp_i4);
        }
      }
      tmp_u10 = 1;
      if (*(int *)(param_1 + 0xd14) != 0) {
        tmp_i4 = *(int *)(param_1 + 0x510 + *(int *)(param_1 + 0xc0) * 4);
        tmp_i7 = *(int *)(tmp_i4 + 0x254);
        if (-1 < tmp_i7) {
          tmp_u5 = String_Alloc(*(uint32_t *)(tmp_i4 + 600));
          *(uint32_t *)(param_1 + 0xf4 + tmp_i7 * 4) = tmp_u5;
        }
      }
    }
  }
  else {
    tmp_u10 = 1;
    trap_Print("^3UI WARNING: Reached MAX_MENUITEMS\n");
  }
  return tmp_u10;
}

void Menu_SetupKeywordHash(void)

{
{  uint8_t *tmp_pu1;
  char *tmp_pc2;
  int tmp_i3;
  uint8_t **tmp_ppu4;
  uint tmp_u5;
  uint32_t *tmp_pu6;
  int tmp_i7;
  char tmp_c8;
  uint32_t *local_14;
  
  local_14 = &menuParseKeywordHash;
  tmp_pu6 = &menuParseKeywordHash;
  for (tmp_i7 = 0x200; tmp_i7 != 0; tmp_i7 = tmp_i7 + -1) {
    *tmp_pu6 = 0;
    tmp_pu6 = tmp_pu6 + 1;
  }
  tmp_ppu4 = &menuParseKeywords;
  tmp_pc2 = menuParseKeywords;
  while (tmp_pc2 != (char *)0x0) {
    tmp_c8 = *tmp_pc2;
    tmp_pu6 = local_14;
    if (tmp_c8 != '\0') {
      tmp_u5 = 0;
      tmp_i7 = 0x77;
      do {
        tmp_i3 = (int)tmp_c8;
        if ((byte)(tmp_c8 + 0xbfU) < 0x1a) {
          tmp_i3 = tmp_c8 + 0x20;
        }
        tmp_u5 = tmp_i3 * tmp_i7 + tmp_u5;
        tmp_c8 = tmp_pc2[tmp_i7 + -0x76];
        tmp_i7 = tmp_i7 + 1;
      } while (tmp_c8 != '\0');
      tmp_pu6 = &menuParseKeywordHash + ((tmp_u5 ^ (int)tmp_u5 >> 0x14 ^ (int)tmp_u5 >> 10) & 0x1ff);
    }
    tmp_pu1 = (uint8_t *)*tmp_pu6;
    *tmp_pu6 = tmp_ppu4;
    tmp_ppu4[2] = tmp_pu1;
    tmp_pc2 = tmp_ppu4[3];
    tmp_ppu4 = tmp_ppu4 + 3;
  }
  return;
}

int Menu_Parse(uint32_t param_1,uint32_t param_2)

{
{  int tmp_i1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint tmp_u4;
  char tmp_c5;
  byte tmp_b6;
  char acStack_49a [58];
  uint32_t uStack_460;
  uint32_t local_45c;
  char *local_458;
  char *local_454;
  uint32_t *local_444;
  char *local_440;
  uint32_t local_434;
  uint32_t local_430 [3];
  char local_424;
  char acStack_423 [1043];
  
  tmp_b6 = 0;
  local_458 = (char *)&local_434;
  local_45c = param_1;
  uStack_460 = 0x4ec10;
  local_444 = (uint32_t *)local_458;
  tmp_i2 = trap_PC_ReadToken();
  if ((tmp_i2 == 0) || (local_424 != '{')) {
    return 0;
  }
  local_440 = "unknown menu keyword %s";
  local_424 = '{';
  local_458 = (char *)local_444;
joined_r0x0004ec4d:
  do {
    tmp_u4 = 0x418;
    tmp_pu3 = (uint32_t *)local_458;
    if (((uint)local_458 & 4) != 0) {
      *(uint32_t *)local_458 = 0;
      tmp_pu3 = local_430;
      tmp_u4 = 0x414;
    }
    for (tmp_u4 = tmp_u4 >> 2; tmp_u4 != 0; tmp_u4 = tmp_u4 - 1) {
      *tmp_pu3 = 0;
      tmp_pu3 = tmp_pu3 + (uint)tmp_b6 * -2 + 1;
    }
    local_45c = param_1;
    uStack_460 = 0x4ec71;
    local_444 = (uint32_t *)local_458;
    tmp_i2 = trap_PC_ReadToken();
    if (tmp_i2 == 0) {
      local_458 = "end of file inside menu\n";
      local_45c = param_1;
      uStack_460 = 0x4edbe;
      PC_SourceError();
      return 0;
    }
    if (local_424 == '}') {
      return 1;
    }
    if (local_424 == '\0') {
      tmp_pu3 = &menuParseKeywordHash;
    }
    else {
      tmp_u4 = 0;
      tmp_i2 = 0x77;
      tmp_c5 = local_424;
      do {
        tmp_i1 = (int)tmp_c5;
        if ((byte)(tmp_c5 + 0xbfU) < 0x1a) {
          tmp_i1 = tmp_c5 + 0x20;
        }
        tmp_u4 = tmp_i1 * tmp_i2 + tmp_u4;
        tmp_c5 = acStack_49a[tmp_i2];
        tmp_i2 = tmp_i2 + 1;
      } while (tmp_c5 != '\0');
      tmp_pu3 = &menuParseKeywordHash + ((tmp_u4 ^ (int)tmp_u4 >> 10 ^ (int)tmp_u4 >> 0x14) & 0x1ff);
    }
    for (tmp_pu3 = (uint32_t *)*tmp_pu3; tmp_pu3 != (uint32_t *)0x0;
        tmp_pu3 = (uint32_t *)tmp_pu3[2]) {
      local_45c = *tmp_pu3;
      uStack_460 = 0x4ed05;
      local_458 = &local_424;
      tmp_i2 = Q_stricmp();
      if (tmp_i2 == 0) {
        local_458 = (char *)param_1;
        local_45c = param_2;
        uStack_460 = 0x4ed21;
        tmp_i2 = (*(void *)tmp_pu3[1])();
        local_458 = (char *)local_444;
        if (tmp_i2 == 0) {
          local_458 = "couldn\'t parse menu keyword %s";
          local_45c = param_1;
          uStack_460 = 0x4ed4a;
          local_454 = &local_424;
          local_444 = (uint32_t *)tmp_i2;
          PC_SourceError();
          return (int)local_444;
        }
        goto joined_r0x0004ec4d;
      }
    }
    local_45c = param_1;
    uStack_460 = 0x4ed73;
    local_458 = local_440;
    local_454 = &local_424;
    PC_SourceError();
    local_458 = (char *)local_444;
  } while( true );
}

void Menu_New(uint32_t param_1)

{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  uint32_t *tmp_pu7;
  
  tmp_i1 = menuCount;
  if (menuCount < 0x100) {
    tmp_i5 = menuCount * 0xd18;
    tmp_pu6 = &Menus + menuCount * 0x346;
    tmp_pu7 = tmp_pu6;
    for (tmp_i4 = 0x346; tmp_i2 = DC, tmp_i4 != 0; tmp_i4 = tmp_i4 + -1) {
      *tmp_pu7 = 0;
      tmp_pu7 = tmp_pu7 + 1;
    }
    tmp_i4 = tmp_i1 * 0xd18;
    (&g_dat_003f1748)[tmp_i1 * 0x346] = 0xffffffff;
    *(uint32_t *)(&g_dat_003f1754 + tmp_i4) = *(uint32_t *)(tmp_i2 + 0x1e32c);
    *(uint32_t *)(&g_dat_003f1750 + tmp_i4) = *(uint32_t *)(tmp_i2 + 0x1e324);
    *(uint32_t *)(&g_dat_003f174c + tmp_i4) = *(uint32_t *)(tmp_i2 + 0x1e328);
    *(uint32_t *)(&g_dat_003f2394 + tmp_i4) = 0;
    tmp_u3 = 0;
    do {
      *(uint32_t *)((int)tmp_pu6 + tmp_u3) = 0;
      *(uint32_t *)((int)&g_dat_003f1684 + tmp_u3 + tmp_i5) = 0;
      tmp_u3 = tmp_u3 + 8;
    } while (tmp_u3 < 0xb8);
    *(uint32_t *)(&g_dat_003f16c4 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_dat_003f1700 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_dat_003f16fc + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_dat_003f16f8 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_dat_003f16f4 + tmp_i5) = 0x3f800000;
    *(uint32_t *)(&g_dat_003f16b0 + tmp_i5) = 0xffffffff;
    tmp_i4 = Menu_Parse(param_1,tmp_pu6);
    if (tmp_i4 != 0) {
      if ((&g_dat_003f173c)[tmp_i1 * 0x346] != 0) {
        (&Menus)[tmp_i1 * 0x346] = 0;
        (&g_dat_003f1684)[tmp_i1 * 0x346] = 0;
        (&g_dat_003f1688)[tmp_i1 * 0x346] = 0x44200000;
        (&g_dat_003f168c)[tmp_i1 * 0x346] = 0x43f00000;
      }
      Menu_UpdatePosition(tmp_pu6);
      menuCount = menuCount + 1;
    }
  }
  else {
    trap_Print("^3UI WARNING: Reached MAX_MENUS\n");
  }
  return;
}

uint32_t Menu_Count(void)

{
  return menuCount;
}

uint32_t * Menu_Get(int param_1)

{
  if ((-1 < param_1) && (param_1 < menuCount)) {
    return &Menus + param_1 * 0x346;
  }
  return (uint32_t *)0x0;
}

void Menu_PaintAll(void)

{
  void *tmp_pc1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  uint32_t *tmp_pu7;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x4f0a9;
  if (captureFunc != (void *)0x0) {
    (*captureFunc)(captureData);
  }
  if (0 < menuCount) {
    tmp_pu6 = &Menus;
    tmp_i5 = 0;
    tmp_i3 = menuCount;
    tmp_pu7 = tmp_pu6;
    do {
      while ((((tmp_pu7[0x12] & 0x2000000) != 0 || ((tmp_pu7[0x12] & 4) == 0)) ||
             ((tmp_pu7[0x10] != 0 &&
              ((*(void **)(DC + 100) != (void *)0x0 &&
               (tmp_i2 = (**(void **)(DC + 100))(tmp_pu7[0x10]), tmp_i3 = menuCount, tmp_i2 == 0)))))))
      {
        tmp_i5 = tmp_i5 + 1;
        tmp_pu7 = tmp_pu7 + 0x346;
        if (tmp_i3 <= tmp_i5) goto LAB_0004f13e;
      }
      Menu_Paint_part_20();
      tmp_i5 = tmp_i5 + 1;
      tmp_pu7 = tmp_pu7 + 0x346;
      tmp_i3 = menuCount;
    } while (tmp_i5 < menuCount);
LAB_0004f13e:
    if (0 < tmp_i3) {
      tmp_i5 = 0;
      do {
        while ((tmp_pu6[0x12] & 0x2000004) != 0x2000004) {
LAB_0004f160:
          tmp_i5 = tmp_i5 + 1;
          tmp_pu6 = tmp_pu6 + 0x346;
          if (tmp_i3 <= tmp_i5) goto LAB_0004f1b0;
        }
        if (((tmp_pu6[0x10] == 0) || (*(void **)(DC + 100) == (void *)0x0)) ||
           (tmp_i3 = (**(void **)(DC + 100))(tmp_pu6[0x10]), tmp_i3 != 0)) {
          Menu_Paint_part_20();
          tmp_i3 = menuCount;
          goto LAB_0004f160;
        }
        tmp_i5 = tmp_i5 + 1;
        tmp_pu6 = tmp_pu6 + 0x346;
        tmp_i3 = menuCount;
      } while (tmp_i5 < menuCount);
    }
  }
LAB_0004f1b0:
  if (debugMode != 0) {
    local_2c = 0x3f800000;
    local_28 = 0x3f800000;
    local_24 = 0x3f800000;
    local_20 = 0x3f800000;
    (**(void **)(DC + 0x30))(2);
    tmp_pc1 = *(void **)(DC + 0x10);
    tmp_u4 = va("fps: %.2f",(double)*(float *)(DC + 0x2005c));
    (*tmp_pc1)(0x40a00000,0x41200000,0x3e4ccccd,&local_2c,tmp_u4,0,0,0);
    tmp_pc1 = *(void **)(DC + 0x10);
    tmp_u4 = va("mouse: %i %i",*(uint32_t *)(DC + 0x124),*(uint32_t *)(DC + 0x128));
    (*tmp_pc1)(0x40a00000,0x41a00000,0x3e4ccccd,&local_2c,tmp_u4,0,0,0);
  }
  return;
}

void Menu_Reset(void)

{
  menuCount = 0;
  return;
}

uint32_t Display_GetContext(void)

{
  return DC;
}

uint32_t * Display_CaptureItem(int param_1,int param_2)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float *pfVar4;
  int tmp_i5;
  
  if (0 < menuCount) {
    tmp_f3 = (float)param_2;
    tmp_f2 = (float)param_1;
    pfVar4 = (float *)&Menus;
    if (*(float *)(&g_dat_0002003c + DC) <= 1.3333334) {
      tmp_i5 = 0;
      do {
        if ((((*pfVar4 < tmp_f2) && (tmp_f2 < *pfVar4 + pfVar4[2])) && (pfVar4[1] < tmp_f3)) &&
           (tmp_f3 < pfVar4[1] + pfVar4[3])) goto LAB_0004f424;
        tmp_i5 = tmp_i5 + 1;
        pfVar4 = pfVar4 + 0x346;
      } while (tmp_i5 != menuCount);
    }
    else {
      tmp_f1 = *(float *)(&g_dat_0002003c + DC) * 0.75;
      tmp_i5 = 0;
      do {
        if (((tmp_f1 * *pfVar4 < tmp_f2 * tmp_f1) && (tmp_f2 * tmp_f1 < (*pfVar4 + pfVar4[2]) * tmp_f1))
           && ((pfVar4[1] < tmp_f3 && (tmp_f3 < pfVar4[1] + pfVar4[3])))) {
LAB_0004f424:
          return &Menus + tmp_i5 * 0x346;
        }
        tmp_i5 = tmp_i5 + 1;
        pfVar4 = pfVar4 + 0x346;
      } while (tmp_i5 != menuCount);
    }
  }
  return (uint32_t *)0x0;
}

uint32_t Display_MouseMove(float *param_1,int param_2,int param_3)

{
  int tmp_i1;
  uint tmp_u2;
  uint *tmp_pu3;
  uint32_t *tmp_pu4;
  
  if (param_1 == (float *)0x0) {
    if (0 < menuCount) {
      if ((g_dat_003f16c8 & 6) == 6) {
        tmp_i1 = 0;
        tmp_u2 = g_dat_003f16c8;
      }
      else {
        tmp_pu3 = &g_dat_003f23e0;
        tmp_i1 = 0;
        do {
          tmp_i1 = tmp_i1 + 1;
          if (tmp_i1 == menuCount) goto LAB_0004f4af;
          tmp_u2 = *tmp_pu3;
          tmp_pu3 = tmp_pu3 + 0x346;
        } while ((tmp_u2 & 6) != 6);
      }
      if ((tmp_u2 & 0x200000) == 0) {
LAB_0004f4af:
        tmp_i1 = 0;
        tmp_pu4 = &Menus;
        do {
          tmp_i1 = tmp_i1 + 1;
          Menu_HandleMouseMove(tmp_pu4,(float)param_2,(float)param_3);
          tmp_pu4 = tmp_pu4 + 0x346;
        } while (tmp_i1 < menuCount);
        return 1;
      }
      Menu_HandleMouseMove(&Menus + tmp_i1 * 0x346,(float)param_2,(float)param_3);
    }
  }
  else {
    *param_1 = (float)param_2 + *param_1;
    param_1[1] = (float)param_3 + param_1[1];
    Menu_UpdatePosition(param_1);
  }
  return 1;
}

uint32_t Display_CursorType(int param_1,int param_2)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float *pfVar4;
  int tmp_i5;
  
  if (0 < menuCount) {
    tmp_f3 = (float)param_2;
    tmp_f2 = (float)param_1;
    pfVar4 = (float *)&Menus;
    if (*(float *)(&g_dat_0002003c + DC) <= 1.3333334) {
      tmp_i5 = 0;
      do {
        if ((((*pfVar4 - 3.0 < tmp_f2) && (tmp_f2 < (*pfVar4 - 3.0) + 7.0)) &&
            (pfVar4[1] - 3.0 < tmp_f3)) && (tmp_f3 < (pfVar4[1] - 3.0) + 7.0)) {
          return 4;
        }
        tmp_i5 = tmp_i5 + 1;
        pfVar4 = pfVar4 + 0x346;
      } while (tmp_i5 != menuCount);
    }
    else {
      tmp_f1 = *(float *)(&g_dat_0002003c + DC) * 0.75;
      tmp_i5 = 0;
      do {
        if ((((*pfVar4 - 3.0) * tmp_f1 < tmp_f2 * tmp_f1) &&
            (tmp_f2 * tmp_f1 < ((*pfVar4 - 3.0) + 7.0) * tmp_f1)) &&
           ((pfVar4[1] - 3.0 < tmp_f3 && (tmp_f3 < (pfVar4[1] - 3.0) + 7.0)))) {
          return 4;
        }
        tmp_i5 = tmp_i5 + 1;
        pfVar4 = pfVar4 + 0x346;
      } while (tmp_i5 != menuCount);
    }
  }
  return 2;
}

void Display_HandleKey(uint32_t param_1,uint32_t param_2,int param_3,int param_4)

{
  uint tmp_u1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  float *pfVar6;
  uint *tmp_pu7;
  
  if (menuCount < 1) {
    return;
  }
  pfVar6 = (float *)&Menus;
  tmp_f4 = (float)param_4;
  tmp_f3 = (float)param_3;
  if (*(float *)(&g_dat_0002003c + DC) <= 1.3333334) {
    tmp_i5 = 0;
    do {
      if ((((*pfVar6 < tmp_f3) && (tmp_f3 < *pfVar6 + pfVar6[2])) && (pfVar6[1] < tmp_f4)) &&
         (tmp_f4 < pfVar6[1] + pfVar6[3])) goto LAB_0004f7e4;
      tmp_i5 = tmp_i5 + 1;
      pfVar6 = pfVar6 + 0x346;
    } while (tmp_i5 != menuCount);
  }
  else {
    tmp_f2 = *(float *)(&g_dat_0002003c + DC) * 0.75;
    tmp_i5 = 0;
    do {
      if (((tmp_f2 * *pfVar6 < tmp_f3 * tmp_f2) && (tmp_f3 * tmp_f2 < (*pfVar6 + pfVar6[2]) * tmp_f2)) &&
         ((pfVar6[1] < tmp_f4 && (tmp_f4 < pfVar6[1] + pfVar6[3])))) goto LAB_0004f7e4;
      tmp_i5 = tmp_i5 + 1;
      pfVar6 = pfVar6 + 0x346;
    } while (tmp_i5 != menuCount);
  }
  if ((g_dat_003f16c8 & 6) != 6) {
    tmp_pu7 = &g_dat_003f23e0;
    tmp_i5 = 0;
    do {
      tmp_i5 = tmp_i5 + 1;
      if (tmp_i5 == menuCount) {
        return;
      }
      tmp_u1 = *tmp_pu7;
      tmp_pu7 = tmp_pu7 + 0x346;
    } while ((tmp_u1 & 6) != 6);
  }
LAB_0004f7e4:
  Menu_HandleKey();
  return;
}

void Display_CacheAll(void)

{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  int tmp_i7;
  
  if (0 < menuCount) {
    tmp_pu5 = &Menus;
    tmp_i7 = 0;
    do {
      if (tmp_pu5[0xb] != 0) {
        tmp_u3 = (**(void **)(DC + 0xe8))(tmp_pu5[0xb],0,0,0,0);
        (**(void **)(DC + 0xec))(tmp_u3);
      }
      tmp_i4 = tmp_pu5[0x30];
      if (0 < tmp_i4) {
        tmp_i6 = 0;
        do {
          if ((tmp_pu5[tmp_i6 + 0x145] != 0) &&
             (tmp_i1 = *(int *)(tmp_pu5[tmp_i6 + 0x145] + 0x2c), tmp_i1 != 0)) {
            tmp_u3 = (**(void **)(DC + 0xe8))(tmp_i1,0,0,0,0);
            (**(void **)(DC + 0xec))(tmp_u3);
            tmp_i4 = tmp_pu5[0x30];
          }
          tmp_i6 = tmp_i6 + 1;
        } while (tmp_i6 < tmp_i4);
      }
      tmp_pc2 = (char *)tmp_pu5[0x13c];
      if ((tmp_pc2 != (char *)0x0) && (*tmp_pc2 != '\0')) {
        (**(void **)(DC + 0xdc))(tmp_pc2,1);
      }
      tmp_i7 = tmp_i7 + 1;
      tmp_pu5 = tmp_pu5 + 0x346;
    } while (tmp_i7 < menuCount);
  }
  return;
}

bool PC_String_Parse_Trans(uint32_t param_1,uint32_t *param_2)

{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t local_424 [16];
  uint8_t local_414 [1040];
  
  tmp_i1 = trap_PC_ReadToken(param_1,local_424);
  if (tmp_i1 != 0) {
    tmp_u2 = String_Alloc(local_414);
    *param_2 = tmp_u2;
  }
  return tmp_i1 != 0;
}

bool PC_Rect_Parse(uint32_t param_1,int param_2)

{
  int tmp_i1;
  
  tmp_i1 = PC_Float_Parse(param_1,param_2);
  if (((tmp_i1 != 0) && (tmp_i1 = PC_Float_Parse(param_1,param_2 + 4), tmp_i1 != 0)) &&
     (tmp_i1 = PC_Float_Parse(param_1,param_2 + 8), tmp_i1 != 0)) {
    tmp_i1 = PC_Float_Parse(param_1,param_2 + 0xc);
    return tmp_i1 != 0;
  }
  return false;
}

bool BG_RectContainsPoint
               (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6)

{
  if (((param_1 < param_5) && (param_5 < param_3 + param_1)) && (param_2 < param_6)) {
    return param_6 < param_4 + param_2;
  }
  return false;
}

longlong BG_CursorInRect(float *param_1)

{
  uint tmp_u1;
  uint local_8;
  
  local_8 = 0x4fb26;
  tmp_u1 = *(uint *)(DC + 0x128);
  if (((*param_1 < (float)*(int *)(DC + 0x124)) &&
      (local_8 = tmp_u1, (float)*(int *)(DC + 0x124) < *param_1 + param_1[2])) &&
     (param_1[1] < (float)(int)tmp_u1)) {
    return CONCAT44(tmp_u1,(uint)((float)(int)tmp_u1 < param_1[1] + param_1[3]));
  }
  return (ulonglong)local_8 << 0x20;
}

void BG_PanelButton_RenderEdit(int param_1)

{
  uint32_t *tmp_pu1;
  void *tmp_pc2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  int tmp_i6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  uint32_t tmp_u9;
  char *tmp_pc10;
  char local_11d [269];
  
  if (*(int *)(param_1 + 0x18) == 0) {
    trap_Cvar_VariableStringBuffer(*(uint32_t *)(param_1 + 4),local_11d,0x101);
    if ((param_1 == bg_focusButton) && ((*(int *)(DC + 0x11c) / 1000 & 1U) != 0)) {
      tmp_i6 = trap_Key_GetOverstrikeMode();
      if (tmp_i6 == 0) {
        tmp_pu7 = &g_dat_00058a0a;
      }
      else {
        tmp_pu7 = &g_dat_00058a02;
      }
    }
    else {
      tmp_pu7 = &g_dat_0005661b;
    }
    tmp_i6 = -1;
    Q_strcat(local_11d,0x101,tmp_pu7);
    tmp_pc5 = local_11d;
    do {
      tmp_pc10 = tmp_pc5;
      tmp_i6 = tmp_i6 + 1;
      if (*tmp_pc10 == '\0') {
        tmp_pc10 = local_11d + tmp_i6;
        break;
      }
      tmp_i8 = (**(void **)(DC + 0x1c))
                        (tmp_pc10,**(uint32_t **)(param_1 + 0x38),0,
                         (*(uint32_t **)(param_1 + 0x38))[8]);
      tmp_pc5 = tmp_pc10 + 1;
    } while (*(float *)(param_1 + 0x10) < (float)tmp_i8);
    tmp_pc2 = *(void **)(DC + 0x14);
    tmp_u3 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
    tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x18);
    tmp_u9 = va(&g_dat_00055b27,tmp_pc10);
    tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
    (*tmp_pc2)(*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14),
              *tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_u9,0,0,tmp_u4,tmp_u3);
    return;
  }
  if ((param_1 == bg_focusButton) && ((*(int *)(DC + 0x11c) / 1000 & 1U) != 0)) {
    tmp_i6 = (**(void **)(DC + 0x84))();
    if (tmp_i6 == 0) {
      tmp_pc5 = (char *)va(&g_dat_00058a06,*(uint32_t *)(param_1 + 4));
    }
    else {
      tmp_pc5 = (char *)va(&g_dat_000589fe,*(uint32_t *)(param_1 + 4));
    }
  }
  else {
    tmp_pc5 = (char *)va("^7%s ",*(uint32_t *)(param_1 + 4));
  }
  do {
    tmp_pc10 = tmp_pc5;
    if (*tmp_pc10 == '\0') break;
    tmp_i6 = (**(void **)(DC + 0x1c))
                      (tmp_pc10,**(uint32_t **)(param_1 + 0x38),0,
                       (*(uint32_t **)(param_1 + 0x38))[8]);
    tmp_pc5 = tmp_pc10 + 1;
  } while (*(float *)(param_1 + 0x10) < (float)tmp_i6);
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  (**(void **)(DC + 0x14))
            (*(uint32_t *)(param_1 + 8),*(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14),
             *tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,tmp_pc10,0,0,tmp_pu1[6],tmp_pu1[8]);
  return;
}

uint32_t BG_PanelButton_EditClick(int param_1,uint param_2)

{
  uint tmp_u1;
  uint tmp_u2;
  uint *tmp_pu3;
  uint *tmp_pu4;
  char *__s;
  int tmp_i5;
  bool tmp_b6;
  size_t local_128;
  uint32_t local_120;
  uint32_t local_11c;
  
  if (param_2 == 0xb2) {
    if (((((*(float *)(param_1 + 8) < (float)*(int *)(DC + 0x124)) &&
          ((float)*(int *)(DC + 0x124) < *(float *)(param_1 + 8) + *(float *)(param_1 + 0x10))) &&
         (*(float *)(param_1 + 0xc) < (float)*(int *)(DC + 0x128))) &&
        ((float)*(int *)(DC + 0x128) < *(float *)(param_1 + 0xc) + *(float *)(param_1 + 0x14))) ||
       (param_1 != bg_focusButton)) {
      bg_focusButton = param_1;
      return 1;
    }
    bg_focusButton = 0;
    if (*(void **)(param_1 + 0x48) != (void *)0x0) {
      (**(void **)(param_1 + 0x48))(param_1);
      return 0;
    }
  }
  else if (param_1 == bg_focusButton) {
    tmp_i5 = *(int *)(param_1 + 0x18);
    tmp_b6 = tmp_i5 == 0;
    if (tmp_b6) {
      (**(void **)(DC + 0x70))(*(uint32_t *)(param_1 + 4),&local_11c,0x100);
      tmp_pu4 = &local_11c;
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
      __s = (char *)0x0;
      local_128 = (int)tmp_pu4 + ((-3 - (uint)CARRY1((byte)tmp_u2,(byte)tmp_u2)) - (int)&local_11c);
      tmp_i5 = 0x100;
    }
    else {
      __s = *(char **)(param_1 + 4);
      local_128 = strlen(__s);
    }
    if ((param_2 & 0x400) != 0) {
      param_2 = param_2 & 0xfffffbff;
      if (param_2 == 8) {
        if (local_128 == 0) {
          return 1;
        }
        if (!tmp_b6) {
          __s[local_128 - 1] = '\0';
          return 1;
        }
        *(uint8_t *)((int)&local_120 + local_128 + 3) = 0;
        (**(void **)(DC + 0x78))(*(uint32_t *)(param_1 + 4),&local_11c);
        return 1;
      }
      if ((int)param_2 < 0x20) {
        return 1;
      }
      local_120 = *(int *)(param_1 + 0x1c);
      if ((local_120 != 0) && (9 < param_2 - 0x30)) {
        if (local_120 == 2) {
          return 1;
        }
        if ((local_128 != 0) || (param_2 != 0x2d)) {
          return 1;
        }
      }
      if (tmp_i5 + -1 <= (int)local_128) {
        return 1;
      }
      if (!tmp_b6) {
        __s[local_128] = (char)param_2;
        __s[local_128 + 1] = '\0';
        return 1;
      }
      *(char *)((int)&local_11c + local_128) = (char)param_2;
      *(uint8_t *)((int)&local_11c + local_128 + 1) = 0;
      trap_Cvar_Set(*(uint32_t *)(param_1 + 4),&local_11c);
      return 1;
    }
    if ((param_2 != 0xa9) && (param_2 != 0xd)) {
      return 1;
    }
    if (*(void **)(param_1 + 0x48) != (void *)0x0) {
      (**(void **)(param_1 + 0x48))(param_1);
    }
    bg_focusButton = 0;
  }
  return 0;
}

uint32_t BG_PanelButtonsKeyEvent(uint32_t param_1,int param_2,int *param_3)

{
  int tmp_i1;
  int tmp_i2;
  
  if (bg_focusButton == 0) {
    if (param_2 == 0) {
      for (; tmp_i1 = *param_3, tmp_i1 != 0; param_3 = param_3 + 1) {
        if (*(void **)(tmp_i1 + 0x40) != (void *)0x0) {
          if ((((*(float *)(tmp_i1 + 8) < (float)*(int *)(DC + 0x124)) &&
               ((float)*(int *)(DC + 0x124) < *(float *)(tmp_i1 + 8) + *(float *)(tmp_i1 + 0x10))) &&
              (*(float *)(tmp_i1 + 0xc) < (float)*(int *)(DC + 0x128))) &&
             (((float)*(int *)(DC + 0x128) < *(float *)(tmp_i1 + 0xc) + *(float *)(tmp_i1 + 0x14) &&
              (tmp_i1 = (**(void **)(tmp_i1 + 0x40))(tmp_i1,param_1), tmp_i1 != 0)))) {
            return 1;
          }
        }
      }
    }
    else {
      tmp_i1 = *param_3;
      while (tmp_i1 != 0) {
        if (*(void **)(tmp_i1 + 0x3c) != (void *)0x0) {
          if (((*(float *)(tmp_i1 + 8) < (float)*(int *)(DC + 0x124)) &&
              ((float)*(int *)(DC + 0x124) < *(float *)(tmp_i1 + 8) + *(float *)(tmp_i1 + 0x10))) &&
             ((*(float *)(tmp_i1 + 0xc) < (float)*(int *)(DC + 0x128) &&
              (((float)*(int *)(DC + 0x128) < *(float *)(tmp_i1 + 0xc) + *(float *)(tmp_i1 + 0x14) &&
               (tmp_i1 = (**(void **)(tmp_i1 + 0x3c))(tmp_i1,param_1), tmp_i1 != 0)))))) {
            return 1;
          }
        }
        param_3 = param_3 + 1;
        tmp_i1 = *param_3;
      }
    }
  }
  else {
    tmp_i1 = *param_3;
    tmp_i2 = bg_focusButton;
    while (tmp_i1 != 0) {
      if (tmp_i1 == tmp_i2) {
        tmp_i2 = tmp_i1;
        if ((param_2 != 0) && (*(void **)(tmp_i1 + 0x3c) != (void *)0x0)) {
          tmp_i2 = (**(void **)(tmp_i1 + 0x3c))(tmp_i1,param_1);
          if (tmp_i2 != 0) {
            return 1;
          }
          tmp_i2 = 0;
          if (bg_focusButton != 0) {
            return 0;
          }
        }
        if ((param_2 == 0) && (*(void **)(tmp_i1 + 0x40) != (void *)0x0)) {
          tmp_i1 = (**(void **)(tmp_i1 + 0x40))(tmp_i1,param_1);
          if (tmp_i1 != 0) {
            return 1;
          }
          tmp_i2 = 0;
          if (bg_focusButton != 0) {
            return 0;
          }
        }
      }
      param_3 = param_3 + 1;
      tmp_i1 = *param_3;
    }
  }
  return 0;
}

void BG_PanelButtonsSetup(uint32_t *param_1)

{
  int *tmp_pi1;
  int tmp_i2;
  
  tmp_pi1 = (int *)*param_1;
  while (tmp_pi1 != (int *)0x0) {
    if (*tmp_pi1 != 0) {
      tmp_i2 = trap_R_RegisterShaderNoMip(*tmp_pi1);
      tmp_pi1[0x13] = tmp_i2;
    }
    param_1 = param_1 + 1;
    tmp_pi1 = (int *)*param_1;
  }
  return;
}

uint64_t BG_PanelButtonsGetHighlightButton(int *param_1)

{
  int tmp_i1;
  int tmp_i2;
  int local_c;
  
  tmp_i2 = *param_1;
  if (tmp_i2 == 0) {
    tmp_i2 = 0;
  }
  else {
    do {
      if (*(int *)(tmp_i2 + 0x3c) != 0) {
        tmp_i1 = *(int *)(DC + 0x128);
        if ((((*(float *)(tmp_i2 + 8) < (float)*(int *)(DC + 0x124)) &&
             (local_c = tmp_i1,
             (float)*(int *)(DC + 0x124) < *(float *)(tmp_i2 + 8) + *(float *)(tmp_i2 + 0x10))) &&
            (*(float *)(tmp_i2 + 0xc) < (float)tmp_i1)) &&
           ((float)tmp_i1 < *(float *)(tmp_i2 + 0xc) + *(float *)(tmp_i2 + 0x14))) break;
      }
      param_1 = param_1 + 1;
      tmp_i2 = *param_1;
    } while (tmp_i2 != 0);
  }
  return CONCAT44(local_c,tmp_i2);
}

void BG_PanelButtonsRender(int *param_1)

{
  int tmp_i1;
  
  tmp_i1 = *param_1;
  while (tmp_i1 != 0) {
    if (*(void **)(tmp_i1 + 0x44) != (void *)0x0) {
      (**(void **)(tmp_i1 + 0x44))(tmp_i1);
    }
    param_1 = param_1 + 1;
    tmp_i1 = *param_1;
  }
  return;
}

void BG_PanelButtonsRender_TextExt(int param_1,uint32_t param_2)

{
  float tmp_f1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  tmp_pu3 = *(uint32_t **)(param_1 + 0x38);
  tmp_f1 = *(float *)(param_1 + 8);
  if (tmp_pu3 != (uint32_t *)0x0) {
    if (tmp_pu3[7] == 1) {
      tmp_i4 = (**(void **)(DC + 0x1c))(param_2,*tmp_pu3,0,tmp_pu3[8]);
      tmp_f1 = tmp_f1 + (*(float *)(param_1 + 0x10) - (float)tmp_i4) * 0.5;
    }
    else if (tmp_pu3[7] == 2) {
      tmp_f2 = *(float *)(param_1 + 0x10);
      tmp_i4 = (**(void **)(DC + 0x1c))(param_2,*tmp_pu3,0,tmp_pu3[8]);
      tmp_f1 = tmp_f1 + (tmp_f2 - (float)tmp_i4);
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      local_2c = 0x3f000000;
      local_28 = 0x3f000000;
      local_24 = 0x3f000000;
      local_20 = 0x3f800000;
      local_1c = 0;
      local_18 = 0;
      local_14 = 0;
      local_10 = 0x3f4ccccd;
      (**(void **)(DC + 0x3c))
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_1c);
      (**(void **)(DC + 0x40))
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),0x3f800000,
                 &local_2c);
    }
    tmp_pu3 = *(uint32_t **)(param_1 + 0x38);
    (**(void **)(DC + 0x14))
              (tmp_f1,(float)*(int *)(param_1 + 0x18) + *(float *)(param_1 + 0xc),*tmp_pu3,tmp_pu3[1],
               tmp_pu3 + 2,param_2,0,0,tmp_pu3[6],tmp_pu3[8]);
  }
  return;
}

void BG_PanelButtonsRender_Text(int param_1)

{
  float tmp_f1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  uint32_t tmp_u4;
  int tmp_i5;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  tmp_pu3 = *(uint32_t **)(param_1 + 0x38);
  tmp_u4 = *(uint32_t *)(param_1 + 4);
  tmp_f1 = *(float *)(param_1 + 8);
  if (tmp_pu3 != (uint32_t *)0x0) {
    if (tmp_pu3[7] == 1) {
      tmp_i5 = (**(void **)(DC + 0x1c))(tmp_u4,*tmp_pu3,0,tmp_pu3[8]);
      tmp_f1 = tmp_f1 + (*(float *)(param_1 + 0x10) - (float)tmp_i5) * 0.5;
    }
    else if (tmp_pu3[7] == 2) {
      tmp_f2 = *(float *)(param_1 + 0x10);
      tmp_i5 = (**(void **)(DC + 0x1c))(tmp_u4,*tmp_pu3,0,tmp_pu3[8]);
      tmp_f1 = tmp_f1 + (tmp_f2 - (float)tmp_i5);
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      local_2c = 0x3f000000;
      local_28 = 0x3f000000;
      local_24 = 0x3f000000;
      local_20 = 0x3f800000;
      local_1c = 0;
      local_18 = 0;
      local_14 = 0;
      local_10 = 0x3f4ccccd;
      (**(void **)(DC + 0x3c))
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_1c);
      (**(void **)(DC + 0x40))
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),0x3f800000,
                 &local_2c);
    }
    tmp_pu3 = *(uint32_t **)(param_1 + 0x38);
    (**(void **)(DC + 0x14))
              (tmp_f1,(float)*(int *)(param_1 + 0x18) + *(float *)(param_1 + 0xc),*tmp_pu3,tmp_pu3[1],
               tmp_pu3 + 2,tmp_u4,0,0,tmp_pu3[6],tmp_pu3[8]);
  }
  return;
}

void BG_PanelButtonsRender_Img(int param_1)

{
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_1c = 1.0;
  local_18 = 1.0;
  local_14 = 1.0;
  local_10 = 1.0;
  if (*(int *)(param_1 + 0x18) != 0) {
    local_1c = (float)*(int *)(param_1 + 0x1c) / 255.0;
    local_18 = (float)*(int *)(param_1 + 0x20) / 255.0;
    local_14 = (float)*(int *)(param_1 + 0x24) / 255.0;
    local_10 = (float)*(int *)(param_1 + 0x28) / 255.0;
    trap_R_SetColor(&local_1c);
  }
  if (*(int *)(param_1 + 0x2c) == 0) {
    (**(void **)(DC + 8))
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),
               *(uint32_t *)(param_1 + 0x4c));
  }
  else {
    (**(void **)(DC + 0x40))
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),0x3f800000,&local_1c)
    ;
  }
  if (*(int *)(param_1 + 0x18) != 0) {
    trap_R_SetColor(0);
  }
  return;
}

uint32_t BG_PanelButtons_GetFocusButton(void)

{
  return bg_focusButton;
}

void BG_PanelButtons_SetFocusButton(uint32_t param_1)

{
  bg_focusButton = param_1;
  return;
}

void BG_FitTextToWidth_Ext
               (char *param_1,uint32_t param_2,float param_3,uint param_4,uint32_t param_5)

{
  char *tmp_pc1;
  char tmp_c2;
  char *tmp_pc3;
  int tmp_i4;
  uint tmp_u5;
  char *tmp_pc6;
  char *tmp_pc7;
  char *tmp_pc8;
  byte tmp_b9;
  char local_41c [1036];
  
  tmp_b9 = 0;
  Q_strncpyz(local_41c,param_1,0x400);
  tmp_pc8 = param_1;
  if (7 < param_4) {
    tmp_u5 = param_4;
    if (((uint)param_1 & 1) != 0) {
      *param_1 = '\0';
      tmp_pc8 = param_1 + 1;
      tmp_u5 = param_4 - 1;
    }
    if (((uint)tmp_pc8 & 2) != 0) {
      tmp_pc8[0] = '\0';
      tmp_pc8[1] = '\0';
      tmp_u5 = tmp_u5 - 2;
      tmp_pc8 = tmp_pc8 + 2;
    }
    if (((uint)tmp_pc8 & 4) != 0) {
      tmp_pc8[0] = '\0';
      tmp_pc8[1] = '\0';
      tmp_pc8[2] = '\0';
      tmp_pc8[3] = '\0';
      tmp_u5 = tmp_u5 - 4;
      tmp_pc8 = tmp_pc8 + 4;
    }
    param_4 = tmp_u5 & 3;
    for (tmp_u5 = tmp_u5 >> 2; tmp_u5 != 0; tmp_u5 = tmp_u5 - 1) {
      tmp_pc8[0] = '\0';
      tmp_pc8[1] = '\0';
      tmp_pc8[2] = '\0';
      tmp_pc8[3] = '\0';
      tmp_pc8 = tmp_pc8 + (uint)tmp_b9 * -8 + 4;
    }
  }
  if ((param_4 & 4) != 0) {
    tmp_pc8[0] = '\0';
    tmp_pc8[1] = '\0';
    tmp_pc8[2] = '\0';
    tmp_pc8[3] = '\0';
    tmp_pc8 = tmp_pc8 + 4;
  }
  if ((param_4 & 2) != 0) {
    tmp_pc8[0] = '\0';
    tmp_pc8[1] = '\0';
    tmp_pc8 = tmp_pc8 + 2;
  }
  if ((param_4 & 1) != 0) {
    *tmp_pc8 = '\0';
  }
  tmp_pc6 = (char *)0x0;
  tmp_pc8 = local_41c;
  tmp_pc3 = param_1;
  while (local_41c[0] != '\0') {
    tmp_pc8 = tmp_pc8 + 1;
    if (local_41c[0] == ' ') {
      tmp_pc6 = tmp_pc3;
    }
    tmp_c2 = *tmp_pc8;
    *tmp_pc3 = local_41c[0];
    tmp_pc1 = tmp_pc3 + 1;
    tmp_pc7 = tmp_pc1;
    if (tmp_c2 == '\n') {
      param_1 = tmp_pc3 + 2;
    }
    else {
      tmp_i4 = (**(void **)(DC + 0x1c))(param_1,param_2,0,param_5);
      if (param_3 < (float)tmp_i4) {
        if (tmp_pc6 == (char *)0x0) {
          tmp_c2 = *tmp_pc3;
          *tmp_pc3 = '\n';
          tmp_pc3[1] = tmp_c2;
          tmp_pc7 = tmp_pc3 + 2;
          param_1 = tmp_pc1;
        }
        else {
          param_1 = tmp_pc6 + 1;
          *tmp_pc6 = '\n';
          tmp_pc6 = (char *)0x0;
        }
      }
    }
    tmp_pc3 = tmp_pc7;
    local_41c[0] = *tmp_pc8;
  }
  if (tmp_pc3 != local_41c) {
    tmp_pc8 = tmp_pc3;
    if (tmp_pc3[-1] != '\n') {
      tmp_pc8 = tmp_pc3 + 1;
      *tmp_pc3 = '\n';
    }
    *tmp_pc8 = '\0';
    return;
  }
  return;
}

void C_PanelButtonsSetup(int *param_1,float param_2)

{
  int tmp_i1;
  
  if (param_2 != 0.0) {
    for (; tmp_i1 = *param_1, tmp_i1 != 0; param_1 = param_1 + 1) {
      *(float *)(tmp_i1 + 8) = *(float *)(tmp_i1 + 8) + param_2;
    }
  }
  return;
}

void dllEntry(uint32_t param_1)

{
  syscall = param_1;
  return;
}

uint32_t PASSFLOAT(uint32_t param_1)

{
  return param_1;
}

void trap_Print(uint32_t param_1)

{
  (*syscall)(1,param_1,0xfffffac7);
  return;
}

void trap_Error(uint32_t param_1)

{
  (*syscall)(0,param_1,0xfffffac7);
  return;
}

void trap_Milliseconds(void)

{
  (*syscall)(2,0xfffffac7);
  return;
}

void trap_Cvar_Register(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  (*syscall)(0x41,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_Cvar_Update(uint32_t param_1)

{
  (*syscall)(0x42,param_1,0xfffffac7);
  return;
}

void trap_Cvar_Set(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(3,param_1,param_2,0xfffffac7);
  return;
}

long double trap_Cvar_VariableValue(uint32_t param_1)

{
  float tmp_f1;
  
  tmp_f1 = (float)(*syscall)(4,param_1,0xfffffac7);
  return (long double)tmp_f1;
}

void trap_Cvar_VariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(5,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Cvar_LatchedVariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(6,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Cvar_SetValue(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(7,param_1,param_2,0xfffffac7);
  return;
}

void trap_Cvar_Reset(uint32_t param_1)

{
  (*syscall)(8,param_1,0xfffffac7);
  return;
}

void trap_Cvar_Create(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(9,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Cvar_InfoStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(10,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Argc(void)

{
  (*syscall)(0xb,0xfffffac7);
  return;
}

void trap_Argv(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0xc,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Cmd_ExecuteText(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0xd,param_1,param_2,0xfffffac7);
  return;
}

void trap_AddCommand(uint32_t param_1)

{
  (*syscall)(0xe,param_1,0xfffffac7);
  return;
}

void trap_FS_FOpenFile(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0xf,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_FS_Read(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x10,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_FS_Write(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x11,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_FS_FCloseFile(uint32_t param_1)

{
  (*syscall)(0x12,param_1,0xfffffac7);
  return;
}

void trap_FS_GetFileList(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        )

{
  (*syscall)(0x13,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_FS_Delete(uint32_t param_1)

{
  (*syscall)(0x14,param_1,0xfffffac7);
  return;
}

void trap_R_RegisterModel(uint32_t param_1)

{
  (*syscall)(0x16,param_1,0xfffffac7);
  return;
}

void trap_R_RegisterSkin(uint32_t param_1)

{
  (*syscall)(0x17,param_1,0xfffffac7);
  return;
}

void trap_R_RegisterFont(uint32_t param_1,uint32_t param_2,int param_3)

{
  uint32_t tmp_u1;
  
  (*syscall)(0x46,param_1,param_2,param_3,0xfffffac7);
  if (*(int *)(param_3 + 0x4fdc) == 0) {
    tmp_u1 = (*syscall)(0x18,param_3 + 0x4fe0,0xfffffac7);
    *(uint32_t *)(param_3 + 0x4fdc) = tmp_u1;
  }
  return;
}

void trap_R_RegisterShaderNoMip(uint32_t param_1)

{
  (*syscall)(0x18,param_1,0xfffffac7);
  return;
}

void trap_R_ClearScene(void)

{
  (*syscall)(0x19,0xfffffac7);
  return;
}

void trap_R_AddRefEntityToScene(uint32_t param_1)

{
  (*syscall)(0x1a,param_1,0xfffffac7);
  return;
}

void trap_R_AddPolyToScene(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x1b,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_R_AddLightToScene
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8)

{
  (*syscall)(0x1d,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xfffffac7);
  return;
}

void trap_R_AddCoronaToScene
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x1e,param_1,param_2,param_3,param_4,param_5,param_6,param_7,0xfffffac7);
  return;
}

void trap_R_RenderScene(uint32_t param_1)

{
  (*syscall)(0x1f,param_1,0xfffffac7);
  return;
}

void trap_R_SetColor(uint32_t param_1)

{
  (*syscall)(0x20,param_1,0xfffffac7);
  return;
}

void trap_R_Add2dPolys(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x21,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_R_DrawStretchPic
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8,
               uint32_t param_9)

{
  (*syscall)(0x22,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xfffffac7
            );
  return;
}

void trap_R_DrawRotatedPic
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8,
               uint32_t param_9,uint32_t param_10)

{
  (*syscall)(0x23,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
             0xfffffac7);
  return;
}

void trap_R_ModelBounds(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x47,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_UpdateScreen(void)

{
  (*syscall)(0x24,0xfffffac7);
  return;
}

void trap_CM_LerpTag(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x25,param_1,param_2,param_3,0,0xfffffac7);
  return;
}

void trap_S_StartLocalSound(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x28,param_1,param_2,0x7f,0xfffffac7);
  return;
}

void trap_S_RegisterSound(uint32_t param_1)

{
  (*syscall)(0x27,param_1,0,0xfffffac7);
  return;
}

void trap_S_FadeBackgroundTrack(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x29,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_S_FadeAllSound(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x2a,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Key_KeynumToStringBuf(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x2b,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Key_GetBindingBuf(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x2c,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Key_KeysForBinding(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x2e,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Key_SetBinding(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x2d,param_1,param_2,0xfffffac7);
  return;
}

void trap_Key_IsDown(uint32_t param_1)

{
  (*syscall)(0x2f,param_1,0xfffffac7);
  return;
}

void trap_Key_GetOverstrikeMode(void)

{
  (*syscall)(0x30,0xfffffac7);
  return;
}

void trap_Key_SetOverstrikeMode(uint32_t param_1)

{
  (*syscall)(0x31,param_1,0xfffffac7);
  return;
}

void trap_Key_ClearStates(void)

{
  (*syscall)(0x32,0xfffffac7);
  return;
}

void trap_Key_GetCatcher(void)

{
  (*syscall)(0x33,0xfffffac7);
  return;
}

void trap_Key_SetCatcher(uint32_t param_1)

{
  (*syscall)(0x34,param_1,0xfffffac7);
  return;
}

void trap_GetClipboardData(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x35,param_1,param_2,0xfffffac7);
  return;
}

void trap_GetClientState(uint32_t param_1)

{
  (*syscall)(0x37,param_1,0xfffffac7);
  return;
}

void trap_GetGlconfig(uint32_t param_1)

{
  (*syscall)(0x36,param_1,0xfffffac7);
  return;
}

void trap_GetConfigString(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x38,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_GetLocalServerCount(void)

{
  (*syscall)(0x39,0xfffffac7);
  return;
}

void trap_LAN_GetLocalServerAddressString(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x3a,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_GetGlobalServerCount(void)

{
  (*syscall)(0x3b,0xfffffac7);
  return;
}

void trap_LAN_GetGlobalServerAddressString(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x3c,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_GetPingQueueCount(void)

{
  (*syscall)(0x3d,0xfffffac7);
  return;
}

void trap_LAN_ClearPing(uint32_t param_1)

{
  (*syscall)(0x3e,param_1,0xfffffac7);
  return;
}

void trap_LAN_GetPing(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  (*syscall)(0x3f,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_LAN_GetPingInfo(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x40,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_UpdateVisiblePings(uint32_t param_1)

{
  (*syscall)(0x56,param_1,0xfffffac7);
  return;
}

void trap_LAN_GetServerCount(uint32_t param_1)

{
  (*syscall)(0x52,param_1,0xfffffac7);
  return;
}

void trap_LAN_CompareServers
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5)

{
  (*syscall)(0x66,param_1,param_2,param_3,param_4,param_5,0xfffffac7);
  return;
}

void trap_LAN_GetServerAddressString
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  (*syscall)(0x53,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_LAN_GetServerInfo
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)

{
  (*syscall)(0x54,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_LAN_AddServer(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x5a,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_RemoveServer(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x5b,param_1,param_2,0xfffffac7);
  return;
}

void trap_LAN_GetServerPing(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(100,param_1,param_2,0xfffffac7);
  return;
}

void trap_LAN_ServerIsVisible(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x65,param_1,param_2,0xfffffac7);
  return;
}

void trap_LAN_ServerStatus(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(99,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LAN_ServerIsInFavoriteList(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x67,param_1,param_2,0xfffffac7);
  return;
}

void trap_LAN_SaveCachedServers(void)

{
  (*syscall)(0x59,0xfffffac7);
  return;
}

void trap_LAN_LoadCachedServers(void)

{
  (*syscall)(0x58,0xfffffac7);
  return;
}

void trap_LAN_MarkServerVisible(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x55,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_SetPbClStatus(uint32_t param_1)

{
  (*syscall)(0x69,param_1,0xfffffac7);
  return;
}

void trap_SetPbSvStatus(uint32_t param_1)

{
  (*syscall)(0x6e,param_1,0xfffffac7);
  return;
}

void trap_LAN_ResetPings(uint32_t param_1)

{
  (*syscall)(0x57,param_1,0xfffffac7);
  return;
}

void trap_MemoryRemaining(void)

{
  (*syscall)(0x43,0xfffffac7);
  return;
}

void trap_GetCDKey(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x44,param_1,param_2,0xfffffac7);
  return;
}

void trap_SetCDKey(uint32_t param_1)

{
  (*syscall)(0x45,param_1,0xfffffac7);
  return;
}

void trap_PC_AddGlobalDefine(uint32_t param_1)

{
  (*syscall)(0x48,param_1,0xfffffac7);
  return;
}

void trap_PC_RemoveAllGlobalDefines(void)

{
  (*syscall)(0x49,0xfffffac7);
  return;
}

void trap_PC_LoadSource(uint32_t param_1)

{
  (*syscall)(0x4a,param_1,0xfffffac7);
  return;
}

void trap_PC_FreeSource(uint32_t param_1)

{
  (*syscall)(0x4b,param_1,0xfffffac7);
  return;
}

void trap_PC_ReadToken(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x4c,param_1,param_2,0xfffffac7);
  return;
}

void trap_PC_SourceFileAndLine(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x4d,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_PC_UnReadToken(uint32_t param_1)

{
  (*syscall)(0x4e,param_1,0xfffffac7);
  return;
}

void trap_S_StopBackgroundTrack(void)

{
  (*syscall)(0x4f,0xfffffac7);
  return;
}

void trap_S_StartBackgroundTrack(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x50,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_RealTime(uint32_t param_1)

{
  (*syscall)(0x51,param_1,0xfffffac7);
  return;
}

void trap_CIN_PlayCinematic
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6)

{
  (*syscall)(0x5c,param_1,param_2,param_3,param_4,param_5,param_6,0xfffffac7);
  return;
}

void trap_CIN_StopCinematic(uint32_t param_1)

{
  (*syscall)(0x5d,param_1,0xfffffac7);
  return;
}

void trap_CIN_RunCinematic(uint32_t param_1)

{
  (*syscall)(0x5e,param_1,0xfffffac7);
  return;
}

void trap_CIN_DrawCinematic(uint32_t param_1)

{
  (*syscall)(0x5f,param_1,0xfffffac7);
  return;
}

void trap_CIN_SetExtents(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        ,uint32_t param_5)

{
  (*syscall)(0x60,param_1,param_2,param_3,param_4,param_5,0xfffffac7);
  return;
}

void trap_R_RemapShader(uint32_t param_1,uint32_t param_2,uint32_t param_3)

{
  (*syscall)(0x61,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_VerifyCDKey(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x62,param_1,param_2,0xfffffac7);
  return;
}

void trap_GetLimboString(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0x68,param_1,param_2,0xfffffac7);
  return;
}

void trap_CheckAutoUpdate(void)

{
  (*syscall)(0x6a,0xfffffac7);
  return;
}

void trap_GetAutoUpdate(void)

{
  (*syscall)(0x6b,0xfffffac7);
  return;
}

void trap_openURL(uint32_t param_1)

{
  (*syscall)(0x6d,param_1,0xfffffac7);
  return;
}

void trap_GetHunkData(uint32_t param_1,uint32_t param_2)

{
  (*syscall)(0xd1,param_1,param_2,0xfffffac7);
  return;
}

void _fini(void)

{
  return;
}
