/* Weapons, ammo, missiles, fire logic — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_weapons.h"

void G_RemoveWeapons(int param_1)
{
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,5);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,6);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x1d);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x2e);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x21);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x2a);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x1f);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x29);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x1e);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x18);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x28);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x27);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,10);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,3);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,8);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x16);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x24);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x17);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x25);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,7);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x26);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x22);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x2c);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,2);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0xe);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x23);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x2d);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,9);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,4);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x13);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x2f);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x14);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0xf);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x19);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x2b);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0xb);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x12);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0xc);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0xd);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x15);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x1c);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x30);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x1a);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x32);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x31);
  COM_BitClear(*(int *)(param_1 + 400) + 0x3d4,0x33);
  return;
}

void G_DropLimboAmmo(int param_1)
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
  
  if ((((GHIDRA_FIELD(g_dropAmmo, 12, 4) != 0) && (3 < GHIDRA_FIELD(g_war, 12, 4) - 1)) && (*(int *)(param_1 + 400) != 0)) &&
     ((tmp_i2 = IsClass(param_1,3), tmp_i2 != 0 && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)))) {
    local_48 = GHIDRA_FIELD(g_dropAmmo, 12, 4);
    if ((int)GHIDRA_FIELD(g_dropAmmo, 12, 4) < 10) {
      if ((int)GHIDRA_FIELD(g_dropAmmo, 12, 4) < 1) {
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
      Weapon_MagicAmmo_Ext(param_1,&local_28,&local_28,&local_34);
    } while (tmp_i2 < local_48);
  }
  return;
}

char G_CorrectSecondaryWeapon(uint32_t param_1,int param_2,int param_3,int param_4,int param_5)
{
  switch(param_1) {
  default:
    return '\0';
  case 2:
  case 7:
  case 0xe:
  case 0x26:
    break;
  case 3:
  case 8:
    if ((3 < param_4) && ((param_5 == 0 && (GHIDRA_FIELD(g_dualSMG, 12, 4) == 0)))) {
      return (param_2 == 2) * '\x05' + '\x03';
    }
    if (3 < param_3) {
LAB_00059ffe:
      return (param_2 != 2) + '\"';
    }
    break;
  case 0x22:
  case 0x23:
    if ((3 < param_3) && ((param_5 != 1 || ((g_medics[0xc] & 2) == 0)))) goto LAB_00059ffe;
    break;
  case 0x2c:
  case 0x2d:
    if (3 < param_3) {
      if (param_5 == 4) {
        return (param_2 != 2) + ',';
      }
      goto LAB_00059ffe;
    }
  }
  return (param_2 == 2) * '\x05' + '\x02';
}

void G_AddClassWeapons(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int local_48;
  int local_44;
  uint32_t local_40;
  uint8_t *local_3c;
  int local_38;
  
  tmp_i5 = *(int *)(param_1 + 0xbc8);
  tmp_i2 = *(int *)(param_1 + 3000);
  if (tmp_i2 == 2) {
    local_3c = bg_allies_playerclasses;
  }
  else {
    local_3c = bg_axis_playerclasses;
  }
  local_3c = local_3c + tmp_i5 * 0x30;
  tmp_i6 = *(int *)(param_1 + 0xbdc);
  tmp_u3 = *(uint32_t *)(param_1 + 0xbe0);
  switch(tmp_i5) {
  case 0:
  case 2:
    local_48 = G_CorrectSecondaryWeapon
                         (tmp_u3,tmp_i2,*(uint32_t *)(param_1 + 0xc40),
                          *(uint32_t *)(param_1 + 0xc44),tmp_i5);
    if (local_48 - 1U < 0x33) {
      local_40 = 4;
      local_44 = 1;
      if (tmp_i5 == 4) goto LAB_0005bd29;
      goto LAB_0005be81;
    }
    if ((((*(byte *)(param_1 + 0xee4) & 0x10) == 0) || (tmp_i5 != 0)) ||
       (*(int *)(param_1 + 0xb0c) != 0)) {
      local_40 = 4;
      local_44 = 1;
      if ((*(byte *)(param_1 + 0xee0) & 0x10) == 0) goto LAB_0005bf28;
      goto LAB_0005bde6;
    }
    if (tmp_i2 == 2) {
      local_48 = 8;
      local_40 = 4;
      local_44 = 1;
      local_38 = 0;
    }
    else {
      local_48 = 3;
      local_40 = 4;
      local_44 = 1;
      local_38 = 0;
    }
    goto LAB_0005bb40;
  case 1:
    local_48 = G_CorrectSecondaryWeapon
                         (tmp_u3,tmp_i2,*(uint32_t *)(param_1 + 0xc40),
                          *(uint32_t *)(param_1 + 0xc44),1);
    local_44 = 0;
    break;
  case 3:
    local_48 = G_CorrectSecondaryWeapon
                         (tmp_u3,tmp_i2,*(uint32_t *)(param_1 + 0xc40),
                          *(uint32_t *)(param_1 + 0xc44),3);
    local_44 = 1;
    break;
  case 4:
    local_48 = G_CorrectSecondaryWeapon
                         (tmp_u3,tmp_i2,*(uint32_t *)(param_1 + 0xc40),
                          *(uint32_t *)(param_1 + 0xc44),4);
    local_40 = 2;
    local_44 = 1;
    if (local_48 - 1U < 0x33) {
LAB_0005bd29:
      local_44 = 1;
      local_38 = *(int *)(weapAlts + local_48 * 4);
      tmp_i2 = BG_IsAkimboWeapon(local_48);
      goto joined_r0x0005bd4a;
    }
    goto LAB_0005bdd9;
  default:
    return;
  }
  local_40 = 1;
  if (local_48 - 1U < 0x33) {
LAB_0005be81:
    local_38 = 0;
  }
  else {
LAB_0005bdd9:
    if ((*(byte *)(param_1 + 0xee0) & 0x10) == 0) {
LAB_0005bf28:
      if (tmp_i5 == 4) {
LAB_0005c138:
        if (tmp_i2 == 2) {
          local_48 = 7;
          local_38 = 0x26;
        }
        else {
          local_48 = 2;
          local_38 = 0xe;
        }
      }
      else {
LAB_0005bf33:
        if (tmp_i2 == 2) {
          local_48 = 7;
          local_38 = 0;
        }
        else {
          local_48 = 2;
          local_38 = 0;
        }
      }
    }
    else {
LAB_0005bde6:
      if (tmp_i5 == 4) {
        if (*(int *)(param_1 + 0xb0c) != 0) goto LAB_0005c138;
        if (tmp_i2 == 2) {
          local_48 = 0x2c;
          local_38 = 0;
        }
        else {
          local_48 = 0x2d;
          local_38 = 0;
        }
      }
      else {
        if (*(int *)(param_1 + 0xb0c) != 0) goto LAB_0005bf33;
        if (tmp_i2 == 2) {
          local_48 = 0x22;
          local_38 = 0;
        }
        else {
          local_48 = 0x23;
          local_38 = 0;
        }
      }
    }
  }
LAB_0005bb40:
  tmp_i2 = BG_IsAkimboWeapon(local_48);
joined_r0x0005bd4a:
  if (tmp_i2 != 0) {
    tmp_u3 = BG_AkimboSidearm(local_48);
    tmp_i2 = BG_FindClipForWeapon(tmp_u3);
    *(uint32_t *)(param_1 + 0x290 + tmp_i2 * 4) =
         *(uint32_t *)(ammoTableMP + local_48 * 0x48 + 0x10);
  }
  tmp_u3 = *(uint32_t *)(ammoTableMP + local_48 * 0x48 + 0x10);
  tmp_u1 = *(uint32_t *)(ammoTableMP + local_48 * 0x48 + 0xc);
  COM_BitSet(param_1 + 0x3d4,local_48);
  tmp_i2 = BG_FindClipForWeapon(local_48);
  *(uint32_t *)(param_1 + 0x290 + tmp_i2 * 4) = tmp_u3;
  tmp_i2 = BG_FindAmmoForWeapon(local_48);
  *(uint32_t *)(param_1 + 400 + tmp_i2 * 4) = tmp_u1;
  *(int *)(param_1 + 0xa4) = local_48;
  AddExtraSpawnAmmo();
  tmp_u3 = Bot_WeaponGameToBot(local_48);
  Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u3);
  if (local_38 != 0) {
    AddWeaponToPlayer(param_1,local_38,*(uint32_t *)(ammoTableMP + local_38 * 0x48 + 0xc),
                      *(uint32_t *)(ammoTableMP + local_38 * 0x48 + 0x10),1);
  }
  if (((0x32 < tmp_i6 - 1U) || (tmp_i2 = BG_ClassHasWeapon(local_3c,tmp_i6,0), tmp_i2 == 0)) ||
     (tmp_i2 = G_IsWeaponDisabled(g_entities + *(int *)(param_1 + 0xa0) * 0x600,tmp_i6,1,1),
     tmp_i2 != 0)) {
    tmp_i6 = *(int *)(local_3c + 0x10);
  }
  if ((tmp_i5 != 1) || ((g_medics[0xc] & 4) == 0)) {
    tmp_u3 = *(uint32_t *)(ammoTableMP + tmp_i6 * 0x48 + 0x10);
    tmp_i2 = *(int *)(ammoTableMP + tmp_i6 * 0x48 + 0xc);
    COM_BitSet(param_1 + 0x3d4,tmp_i6);
    tmp_i4 = BG_FindClipForWeapon(tmp_i6);
    *(uint32_t *)(param_1 + 0x290 + tmp_i4 * 4) = tmp_u3;
    tmp_i4 = BG_FindAmmoForWeapon(tmp_i6);
    *(int *)(param_1 + 400 + tmp_i4 * 4) = local_44 * tmp_i2;
    *(int *)(param_1 + 0xa4) = tmp_i6;
    AddExtraSpawnAmmo();
    tmp_u3 = Bot_WeaponGameToBot(tmp_i6);
    Bot_Event_AddWeapon(*(uint32_t *)(param_1 + 0xa0),tmp_u3);
  }
  if ((GHIDRA_FIELD(g_dualSMG, 12, 4) != 0) && (tmp_i5 != 4)) {
    if (tmp_i6 == 3) {
      tmp_i5 = 8;
    }
    else if (tmp_i6 == 8) {
      tmp_i5 = 3;
    }
    else {
      tmp_i5 = (uint)(*(int *)(param_1 + 3000) != 1) * 5 + 3;
    }
    AddWeaponToPlayer_constprop_8
              (local_44 * *(int *)(ammoTableMP + tmp_i5 * 0x48 + 0xc),
               *(uint32_t *)(ammoTableMP + tmp_i5 * 0x48 + 0x10));
  }
  if (((*(int *)(weapAlts + tmp_i6 * 4) == 0) ||
      (tmp_i5 = G_IsWeaponDisabled(g_entities + *(int *)(param_1 + 0xa0) * 0x600,
                                  *(int *)(weapAlts + tmp_i6 * 4),1,0), tmp_i5 != 0)) ||
     (AddWeaponToPlayer_constprop_8
                (local_44 * *(int *)(ammoTableMP + *(int *)(weapAlts + tmp_i6 * 4) * 0x48 + 0xc),
                 *(uint32_t *)(ammoTableMP + *(int *)(weapAlts + tmp_i6 * 4) * 0x48 + 0x10)),
     1 < *(int *)(weapAlts + tmp_i6 * 4) - 0x24U)) {
    if (*(int *)(param_1 + 0xbe4) != 0) {
      *(uint32_t *)(param_1 + 0xbe4) = 0;
    }
  }
  else if (*(int *)(param_1 + 0xbe4) != 1) {
    *(uint32_t *)(param_1 + 0xbe4) = 1;
  }
  AddWeaponToPlayer_constprop_8(0,local_40);
  ClientUserinfoChanged();
  return;
}

bool G_IsHeavyWeapon(int param_1)
{
  if ((((bg_heavyWeapons != param_1) && (g_unk_002b5148 != param_1)) && (g_unk_002b514c != param_1)) &&
     ((g_unk_002b5150 != param_1 && (g_unk_002b5154 != param_1)))) {
    return g_unk_002b5158 == param_1;
  }
  return true;
}

void G_TeamCountWeapons(void)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  int *tmp_pi4;
  int tmp_i5;
  int tmp_i6;
  int *local_1c;
  
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)&g_unk_02b9a454 + tmp_u3) = 0;
    *(uint32_t *)((int)&g_unk_02b9a458 + tmp_u3) = 0;
    tmp_i2 = level;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0x200);
  if (0 < g_unk_00abe938) {
    tmp_pi4 = &g_unk_00abe944 + g_unk_00abe938;
    local_1c = &g_unk_00abe944;
    do {
      tmp_i6 = *local_1c * 0x54dc + tmp_i2;
      if ((tmp_i6 != 0) && (*(int *)(tmp_i6 + 3000) != 3)) {
        tmp_i5 = 0;
        do {
          while (tmp_i5 - 0x24U < 2) {
            if ((*(int *)(tmp_i6 + 0xbe4) != 0) &&
               ((*(int *)(tmp_i6 + 0xbcc) == *(int *)(weapAlts + tmp_i5 * 4) ||
                (*(int *)(weapAlts + tmp_i5 * 4) == *(int *)(tmp_i6 + 0xbdc))))) goto LAB_00065893;
LAB_0006587b:
            tmp_i5 = tmp_i5 + 1;
            if (tmp_i5 == 0x34) goto LAB_000658b0;
          }
          if ((*(int *)(tmp_i6 + 0xbcc) != tmp_i5) &&
             (((*(int *)(tmp_i6 + 0xbdc) != tmp_i5 &&
               (*(int *)(tmp_i6 + 0xbcc) != *(int *)(weapTeamConversion + tmp_i5 * 4))) &&
              (*(int *)(tmp_i6 + 0xbdc) != *(int *)(weapTeamConversion + tmp_i5 * 4)))))
          goto LAB_0006587b;
LAB_00065893:
          tmp_i1 = (*(int *)(tmp_i6 + 3000) + -1) * 0x40 + tmp_i5;
          tmp_i5 = tmp_i5 + 1;
          (&g_unk_00abe8a4)[(int)(&g_unk_00836eec + tmp_i1)] =
               (&g_unk_00abe8a4)[(int)(&g_unk_00836eec + tmp_i1)] + 1;
        } while (tmp_i5 != 0x34);
      }
LAB_000658b0:
      local_1c = local_1c + 1;
    } while (local_1c != tmp_pi4);
  }
  return;
}

uint32_t G_IsWeaponDisabled(int param_1,int param_2,int param_3,int param_4)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int *tmp_pi5;
  int local_4c;
  int local_48;
  
  tmp_i2 = BG_WeaponIsPrimaryForClassAndTeam
                    (*(uint32_t *)(*(int *)(param_1 + 400) + 0xbc8),
                     *(uint32_t *)(*(int *)(param_1 + 400) + 3000),param_2,param_4);
  tmp_i1 = *(int *)(param_1 + 400);
  tmp_i4 = *(int *)(tmp_i1 + 3000);
  if ((tmp_i4 == 3) && ((*(byte *)(param_1 + 0x128) & 8) == 0)) {
    return 1;
  }
  if (GHIDRA_FIELD(g_war, 12, 4) == 4) {
    if (param_2 == 1) {
      return 0;
    }
  }
  else if (GHIDRA_FIELD(g_war, 12, 4) == 1) {
    if (param_2 == 5) {
      return 0;
    }
  }
  else if (GHIDRA_FIELD(g_war, 12, 4) == 2) {
    if (param_2 == 0x18) {
      return 0;
    }
    if (param_2 == 0x1e) {
      return 0;
    }
  }
  else if (GHIDRA_FIELD(g_war, 12, 4) == 3) {
    if (param_2 - 0x24U < 2) {
      return 0;
    }
    if (param_2 - 0x16U < 2) {
      return 0;
    }
  }
  tmp_i3 = G_TeamCount(param_1,param_2);
  if (((((param_2 == bg_heavyWeapons) || (param_2 == g_unk_002b5148)) || (param_2 == g_unk_002b514c)) ||
      ((param_2 == g_unk_002b5150 || (param_2 == g_unk_002b5154)))) || (param_2 == g_unk_002b5158)) {
    local_4c = g_unk_02b9a44c;
    if ((tmp_i4 != 1) && (local_4c = g_unk_02b9a450, tmp_i4 != 2)) {
      if (g_unk_00abe93c < 1) {
        local_4c = 1;
      }
      else {
        tmp_pi5 = &g_unk_00abe944;
        local_4c = 1;
        do {
          if (*tmp_pi5 != (param_1 + -0x93e4a0 >> 9) * -0x55555555) {
            local_4c = local_4c + (uint)(tmp_i4 == *(int *)(level + 3000 + *tmp_pi5 * 0x54dc));
          }
          tmp_pi5 = tmp_pi5 + 1;
        } while (tmp_pi5 != &g_unk_00abe944 + g_unk_00abe93c);
      }
    }
    if (ROUND((float)(GHIDRA_FIELD(g_heavyWeaponRestriction, 12, 4) * local_4c) * 0.01) <= (float)tmp_i3) {
      if (tmp_i2 == 0) {
        return 1;
      }
      if (param_3 != 0) {
        return 1;
      }
      if ((*(byte *)(tmp_i1 + 0xd) & 0x40) != 0) {
        return 1;
      }
      nitmod_cp(param_1,0x13);
      return 1;
    }
    if (param_2 == 5) {
      if ((float)local_4c / ((float)(int)GHIDRA_FIELD(g_maxclients, 12, 4) * 0.5) <=
          (float)(int)GHIDRA_FIELD(team_panzerRestriction, 12, 4) * 0.01) {
        if (tmp_i2 == 0) {
          return 1;
        }
        if (param_3 != 0) {
          return 1;
        }
        if ((*(byte *)(tmp_i1 + 0xd) & 0x40) != 0) {
          return 1;
        }
        nitmod_cp(param_1,0x14);
        return 1;
      }
      goto _L1051;
    }
  }
  switch(param_2) {
  case 5:
_L1051:
    if (GHIDRA_FIELD(team_maxPanzers, 12, 4) == -1) {
      return 0;
    }
    if (tmp_i3 < (int)GHIDRA_FIELD(team_maxPanzers, 12, 4)) {
      return 0;
    }
    if (((tmp_i2 != 0) && (param_3 == 0)) && ((*(byte *)(tmp_i1 + 0xd) & 0x40) == 0)) {
      nitmod_cp(param_1,0x15);
      return 1;
    }
    return 1;
  case 6:
    if ((GHIDRA_FIELD(team_maxFlamers, 12, 4) != -1) && ((int)GHIDRA_FIELD(team_maxFlamers, 12, 4) <= tmp_i3)) {
      if (tmp_i2 == 0) {
        return 1;
      }
      if (param_3 != 0) {
        return 1;
      }
      if ((*(byte *)(tmp_i1 + 0xd) & 0x40) != 0) {
        return 1;
      }
      nitmod_cp(param_1,0x16);
      return 1;
    }
    break;
  case 10:
    if ((((param_4 == 0) || (GHIDRA_FIELD(g_pickAnyWeapon, 12, 4) == 0)) && ((g_weapons[0xd] & 2) == 0)) &&
       (*(int *)(tmp_i1 + 0xbc8) != 4)) {
      return 1;
    }
    break;
  case 0x1d:
    if ((GHIDRA_FIELD(team_maxMG42s, 12, 4) != -1) && ((int)GHIDRA_FIELD(team_maxMG42s, 12, 4) <= tmp_i3)) {
      if (tmp_i2 == 0) {
        return 1;
      }
      if (param_3 == 0) {
        if ((*(byte *)(tmp_i1 + 0xd) & 0x40) == 0) {
          nitmod_cp(param_1,0x17);
          return 1;
        }
        return 1;
      }
      return 1;
    }
    break;
  case 0x21:
    if ((GHIDRA_FIELD(team_maxMortars, 12, 4) != -1) && ((int)GHIDRA_FIELD(team_maxMortars, 12, 4) <= tmp_i3)) {
      if (tmp_i2 == 0) {
        return 1;
      }
      if (param_3 == 0) {
        if ((*(byte *)(tmp_i1 + 0xd) & 0x40) == 0) {
          nitmod_cp(param_1,0x18);
          return 1;
        }
        return 1;
      }
      return 1;
    }
    break;
  case 0x24:
    if (GHIDRA_FIELD(team_maxriflegrenades, 12, 4) == -1) {
      return 0;
    }
    if (g_unk_00abe93c < 1) {
LAB_0006620e:
      local_48 = 0;
    }
    else {
      tmp_pi5 = &g_unk_00abe944;
      local_48 = 0;
      do {
        if (((*tmp_pi5 != (param_1 + -0x93e4a0 >> 9) * -0x55555555) &&
            (tmp_i4 = *tmp_pi5 * 0x54dc + level, *(int *)(tmp_i4 + 3000) == *(int *)(tmp_i1 + 3000))) &&
           ((*(int *)(tmp_i4 + 0xbe4) != 0 &&
            ((*(int *)(tmp_i4 + 0xbcc) == GHIDRA_FIELD(weapAlts, 148, 4) ||
             (GHIDRA_FIELD(weapAlts, 148, 4) == *(int *)(tmp_i4 + 0xbdc))))))) {
          local_48 = local_48 + 1;
        }
        tmp_pi5 = tmp_pi5 + 1;
      } while (tmp_pi5 != &g_unk_00abe944 + g_unk_00abe93c);
    }
    goto LAB_000661b4;
  case 0x25:
    if (GHIDRA_FIELD(team_maxriflegrenades, 12, 4) == -1) {
      return 0;
    }
    if (g_unk_00abe93c < 1) goto LAB_0006620e;
    tmp_pi5 = &g_unk_00abe944;
    local_48 = 0;
    do {
      if (((((param_1 + -0x93e4a0 >> 9) * -0x55555555 - *tmp_pi5 != 0) &&
           (tmp_i4 = *tmp_pi5 * 0x54dc + level, *(int *)(tmp_i4 + 3000) == *(int *)(tmp_i1 + 3000))) &&
          (*(int *)(tmp_i4 + 0xbe4) != 0)) &&
         ((*(int *)(tmp_i4 + 0xbcc) == GHIDRA_FIELD(weapAlts, 144, 4) ||
          (GHIDRA_FIELD(weapAlts, 144, 4) == *(int *)(tmp_i4 + 0xbdc))))) {
        local_48 = local_48 + 1;
      }
      tmp_pi5 = tmp_pi5 + 1;
    } while (tmp_pi5 != &g_unk_00abe944 + g_unk_00abe93c);
LAB_000661b4:
    if ((int)GHIDRA_FIELD(team_maxriflegrenades, 12, 4) <= tmp_i3 + local_48) {
      if (tmp_i2 == 0) {
        return 1;
      }
      if (param_3 == 0) {
        if ((*(byte *)(tmp_i1 + 0xd) & 0x40) == 0) {
          nitmod_cp(param_1,0x19);
          return 1;
        }
        return 1;
      }
      return 1;
    }
  }
  return 0;
}

void G_SetClientWeapons(int param_1,int param_2,int param_3,int param_4)
{
  int tmp_i1;
  int tmp_i2;
  bool tmp_b3;
  
  tmp_b3 = *(int *)(*(int *)(param_1 + 400) + 0xbe0) == param_3;
  if (!tmp_b3) {
    *(int *)(*(int *)(param_1 + 400) + 0xbe0) = param_3;
  }
  tmp_i2 = G_IsWeaponDisabled(param_1,param_2,0,0);
  tmp_i1 = *(int *)(param_1 + 400);
  if (tmp_i2 == 0) {
    if (*(int *)(tmp_i1 + 0xbdc) != param_2) {
      *(int *)(tmp_i1 + 0xbdc) = param_2;
      goto joined_r0x000662e4;
    }
  }
  else if (*(int *)(tmp_i1 + 0xbdc) != 0) {
    *(uint32_t *)(tmp_i1 + 0xbdc) = 0;
    goto joined_r0x000662e4;
  }
  if (tmp_b3) {
    return;
  }
joined_r0x000662e4:
  if (param_4 != 0) {
    ClientUserinfoChanged((param_1 + -0x93e4a0 >> 9) * -0x55555555);
  }
  return;
}

void G_weaponStats_cmd(uint32_t param_1)
{
  G_statsPrint(param_1,0);
  return;
}

void G_weaponStatsLeaders_cmd(int param_1,int param_2,int param_3)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  uint tmp_u3;
  uint tmp_u4;
  uint tmp_u5;
  float tmp_f6;
  int tmp_i7;
  int tmp_i8;
  char *tmp_pc9;
  uint32_t tmp_u10;
  int tmp_i11;
  int tmp_i12;
  int local_568;
  ulonglong local_564;
  int local_544;
  int local_540;
  int local_51c [64];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x751cb;
  local_41c[0] = 0;
  local_540 = 1;
  do {
    tmp_i7 = local_540 + -1;
    if (param_2 == 0) {
      if (0 < g_unk_00abe93c) {
        tmp_i11 = 0;
        local_544 = 0;
        local_568 = 99999;
        tmp_u3 = *(uint *)(&UNK_002482bc + local_540 * 4);
        tmp_i12 = 0;
        do {
          tmp_i8 = (&g_unk_00abe944)[tmp_i11] * 0x54dc + level + tmp_i7 * 0x14 + 0xca0;
          tmp_u4 = *(uint *)(tmp_i8 + 0xc);
          tmp_i1 = tmp_i12;
          if (tmp_u3 <= tmp_u4) {
            tmp_u5 = *(uint *)(tmp_i8 + 0x18);
            tmp_i1 = tmp_i12 + 1;
            local_51c[tmp_i12] = (&g_unk_00abe944)[tmp_i11];
            tmp_f6 = ((float)tmp_u5 * 100.0) / (float)tmp_u4;
            if (tmp_f6 < (float)local_568) {
              local_544 = local_544 + 1;
              local_568 = (int)ROUND(tmp_f6);
            }
          }
          tmp_i11 = tmp_i11 + 1;
          tmp_i12 = tmp_i1;
        } while (tmp_i11 < g_unk_00abe93c);
        goto LAB_00075332;
      }
    }
    else if (0 < g_unk_00abe93c) {
      local_568 = 0;
      tmp_i11 = 0;
      tmp_u3 = *(uint *)(&UNK_002482bc + local_540 * 4);
      local_544 = 0;
      tmp_i12 = 0;
      do {
        while( true ) {
          tmp_i8 = (&g_unk_00abe944)[tmp_i11] * 0x54dc + level + tmp_i7 * 0x14 + 0xca0;
          tmp_u4 = *(uint *)(tmp_i8 + 0xc);
          tmp_i1 = tmp_i12;
          if (tmp_u3 <= tmp_u4) break;
LAB_00075297:
          tmp_i11 = tmp_i11 + 1;
          tmp_i12 = tmp_i1;
          if (g_unk_00abe93c <= tmp_i11) goto LAB_00075332;
        }
        tmp_u5 = *(uint *)(tmp_i8 + 0x18);
        tmp_i1 = tmp_i12 + 1;
        local_51c[tmp_i12] = (&g_unk_00abe944)[tmp_i11];
        tmp_f6 = ((float)tmp_u5 * 100.0) / (float)tmp_u4;
        if ((float)local_568 < tmp_f6) {
          local_544 = local_544 + 1;
          local_568 = (int)ROUND(tmp_f6);
          goto LAB_00075297;
        }
        tmp_i11 = tmp_i11 + 1;
        tmp_i12 = tmp_i1;
      } while (tmp_i11 < g_unk_00abe93c);
LAB_00075332:
      if (((param_2 != 0) || (1 < local_544)) && (tmp_i1 != 0)) {
        tmp_i12 = 0;
        if (param_2 == 0) {
          do {
            tmp_i8 = local_51c[tmp_i12] * 0x54dc + level;
            tmp_i11 = tmp_i8 + tmp_i7 * 0x14 + 0xca0;
            local_564 = (ulonglong)*(uint *)(tmp_i11 + 0x18);
            tmp_f6 = (float)local_564;
            local_564 = (ulonglong)*(uint *)(tmp_i11 + 0xc);
            if ((tmp_f6 * 100.0) / (float)local_564 <= (float)local_568 + 0.999) {
              tmp_u10 = va(" %d %d %d %d %d %d",local_540,local_51c[tmp_i12],*(uint *)(tmp_i11 + 0x18),
                          *(uint *)(tmp_i11 + 0xc),*(uint32_t *)(tmp_i8 + 0xcbc + tmp_i7 * 0x14),
                          *(uint32_t *)(tmp_i11 + 0x10));
              Q_strcat(local_41c,0x400,tmp_u10);
            }
            tmp_i12 = tmp_i12 + 1;
          } while (tmp_i12 != tmp_i1);
        }
        else {
          do {
            tmp_i8 = local_51c[tmp_i12] * 0x54dc + level;
            tmp_i11 = tmp_i8 + tmp_i7 * 0x14 + 0xca0;
            local_564 = (ulonglong)*(uint *)(tmp_i11 + 0x18);
            tmp_f6 = (float)local_564;
            local_564 = (ulonglong)*(uint *)(tmp_i11 + 0xc);
            if ((float)local_568 <= (tmp_f6 * 100.0) / (float)local_564) {
              tmp_u10 = va(" %d %d %d %d %d %d",local_540,local_51c[tmp_i12],*(uint *)(tmp_i11 + 0x18),
                          *(uint *)(tmp_i11 + 0xc),*(uint32_t *)(tmp_i8 + 0xcbc + tmp_i7 * 0x14),
                          *(uint32_t *)(tmp_i11 + 0x10));
              Q_strcat(local_41c,0x400,tmp_u10);
            }
            tmp_i12 = tmp_i12 + 1;
          } while (tmp_i12 != tmp_i1);
        }
      }
    }
    local_540 = local_540 + 1;
    if (local_540 == 0x1b) {
      if (param_2 == 0) {
        tmp_pu2 = &g_unk_0026dcfc;
      }
      else {
        tmp_pu2 = &g_unk_0026ea14;
      }
      if (param_3 == 0) {
        tmp_pc9 = "";
      }
      else {
        tmp_pc9 = "w";
      }
      tmp_u10 = va("%sbstats%s %s 0",tmp_pc9,tmp_pu2,local_41c);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u10);
      return;
    }
  } while( true );
}

void G_weaponRankings_cmd(int param_1,int param_2,int param_3)
{
  uint tmp_u1;
  float tmp_f2;
  int tmp_i3;
  uint tmp_u4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  uint8_t *tmp_pu8;
  int tmp_i9;
  char *tmp_pc10;
  uint8_t **tmp_ppu11;
  uint8_t **tmp_ppu12;
  int local_854;
  int local_848;
  int local_844;
  int local_838;
  char local_81c [1024];
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x75709;
  tmp_i3 = trap_Argc();
  if (tmp_i3 < 2) {
    G_weaponStatsLeaders_cmd(param_1,param_3,0);
    return;
  }
  if (param_3 == 0) {
    trap_Argv(1,local_81c,0x400);
    iWeap = strtol(local_81c,(char **)0x0,10);
    if (0x18 < iWeap - 1U) {
      local_844 = 99999;
LAB_000757c9:
      iWeap = 0xe;
      do {
        tmp_i3 = Q_stricmp(local_81c,*(uint32_t *)(aWeaponInfo + iWeap * 0xc + 4));
        if (tmp_i3 == 0) {
          if (-1 < iWeap) goto LAB_0007581a;
          break;
        }
        iWeap = iWeap + -1;
      } while (-1 < iWeap);
      if (param_3 == 0) {
        tmp_pc10 = "bottomshots";
      }
      else {
        tmp_pc10 = "topshots";
      }
      if (param_1 != 0) {
        trap_Argv(1,local_41c,0x400);
        tmp_i3 = Q_stricmp(local_41c,&g_unk_0026f751);
        if (tmp_i3 == 0) {
          tmp_u5 = va(&g_unk_002480b8,tmp_pc10,
                     (&g_ptr_s_7_HUD_overlay_showing_current_w_002b37b0)[param_2 * 5]);
          local_848 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
          trap_SendServerCommand(local_848,tmp_u5);
          goto LAB_00075aee;
        }
      }
      local_848 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
LAB_00075aee:
      Q_strncpyz(local_81c,"^3Available weapon codes:^7\n",0x400);
      tmp_ppu11 = (uint8_t **)(aWeaponInfo + 8);
      do {
        tmp_ppu12 = tmp_ppu11 + 3;
        tmp_u5 = va("  %s - %s\n",tmp_ppu11[-1],*tmp_ppu11);
        Q_strcat(local_81c,0x400,tmp_u5);
        tmp_ppu11 = tmp_ppu12;
      } while (tmp_ppu12 != &voteToggles);
      tmp_u5 = va("print \"%s\"",local_81c);
      trap_SendServerCommand(local_848,tmp_u5);
      return;
    }
    local_844 = 99999;
  }
  else {
    trap_Argv(1,local_81c,0x400);
    iWeap = strtol(local_81c,(char **)0x0,10);
    if (0x18 < iWeap - 1U) {
      local_844 = 0;
      goto LAB_000757c9;
    }
    local_844 = 0;
  }
LAB_0007581a:
  tmp_u4 = 0;
  do {
    *(uint32_t *)((int)&g_unk_02a99a84 + tmp_u4) = *(uint32_t *)((int)&g_unk_00abe944 + tmp_u4);
    *(uint32_t *)((int)&g_unk_02a99a88 + tmp_u4) = *(uint32_t *)((int)&g_unk_00abe948 + tmp_u4);
    tmp_u4 = tmp_u4 + 8;
  } while (tmp_u4 < 0x100);
  qsort(&g_unk_02a99a84,g_unk_00abe938,4,SortStats);
  local_81c[0] = '\0';
  local_854 = g_unk_00abe93c;
  tmp_i3 = iWeap;
  if (g_unk_00abe93c < 1) {
    local_838 = 0;
LAB_000759e4:
    if (param_3 != 0) {
      tmp_pu8 = &g_unk_0026ea14;
      goto LAB_000759f9;
    }
  }
  else {
    tmp_i9 = 0;
    local_838 = 0;
    if (param_3 != 0) {
      do {
        tmp_i7 = (&g_unk_02a99a84)[tmp_i9] * 0x54dc + level;
        tmp_i6 = tmp_i3 * 0x14 + 0xca0 + tmp_i7;
        tmp_u4 = *(uint *)(tmp_i6 + 0xc);
        if ((uint)(&cQualifyingShots)[tmp_i3] <= tmp_u4) {
          tmp_u1 = *(uint *)(tmp_i6 + 0x18);
          local_838 = local_838 + 1;
          tmp_f2 = ((float)tmp_u1 * 100.0) / (float)tmp_u4;
          if ((float)local_844 < tmp_f2) {
            local_844 = (int)ROUND(tmp_f2);
          }
          tmp_u5 = va(" %d %d %d %d %d",(&g_unk_02a99a84)[tmp_i9],tmp_u1,tmp_u4,
                     *(uint32_t *)(tmp_i7 + 0xcbc + tmp_i3 * 0x14),
                     *(uint32_t *)(tmp_i7 + 0xcb0 + tmp_i3 * 0x14));
          Q_strcat(local_81c,0x400,tmp_u5);
          local_854 = g_unk_00abe93c;
          tmp_i3 = iWeap;
        }
        tmp_i9 = tmp_i9 + 1;
      } while (tmp_i9 < local_854);
      goto LAB_000759e4;
    }
    do {
      tmp_i7 = (&g_unk_02a99a84)[tmp_i9] * 0x54dc + level;
      tmp_i6 = tmp_i3 * 0x14 + 0xca0 + tmp_i7;
      tmp_u4 = *(uint *)(tmp_i6 + 0xc);
      if ((uint)(&cQualifyingShots)[tmp_i3] <= tmp_u4) {
        tmp_u1 = *(uint *)(tmp_i6 + 0x18);
        local_838 = local_838 + 1;
        tmp_f2 = ((float)tmp_u1 * 100.0) / (float)tmp_u4;
        if (tmp_f2 < (float)local_844) {
          local_844 = (int)ROUND(tmp_f2);
        }
        tmp_u5 = va(" %d %d %d %d %d",(&g_unk_02a99a84)[tmp_i9],tmp_u1,tmp_u4,
                   *(uint32_t *)(tmp_i7 + 0xcbc + tmp_i3 * 0x14),
                   *(uint32_t *)(tmp_i7 + 0xcb0 + tmp_i3 * 0x14));
        Q_strcat(local_81c,0x400,tmp_u5);
        local_854 = g_unk_00abe93c;
        tmp_i3 = iWeap;
      }
      tmp_i9 = tmp_i9 + 1;
    } while (tmp_i9 < local_854);
  }
  tmp_pu8 = &g_unk_0026dcfc;
LAB_000759f9:
  tmp_u5 = va("astats%s %d %d %d%s",tmp_pu8,local_838,tmp_i3,local_844,local_81c);
  trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5);
  return;
}

bool G_WeaponCanGib(uint32_t param_1)
{
  int tmp_i1;
  bool tmp_b2;
  
  tmp_i1 = BG_WeaponForMOD(param_1);
  if (*(int *)(BG_Weapons + tmp_i1 * 0x6b0 + 0x688) != 1) {
    tmp_b2 = false;
    if (*(int *)(BG_Weapons + tmp_i1 * 0x6b0 + 0x688) != 2) {
      tmp_i1 = G_WeaponIsExplosive(param_1);
      tmp_b2 = tmp_i1 != 0;
    }
    return tmp_b2;
  }
  return true;
}

void G_Damage(int *param_1,int param_2,int *param_3,float *param_4,float *param_5,int param_6,
             uint param_7,int param_8)

{
  uint *tmp_pu1;
  int *tmp_pi2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  bool tmp_b6;
  int tmp_i7;
  int tmp_i8;
  uint32_t tmp_u9;
  int tmp_i10;
  int tmp_i11;
  char *tmp_pc12;
  int tmp_i13;
  uint tmp_u14;
  bool tmp_b15;
  long double tmp_l16;
  long double tmp_l17;
  uint local_50;
  int local_4c;
  int local_38;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i7 = OnSameTeam(param_1,param_3);
  if (param_1[0xb3] == 0) {
    return;
  }
  if (g_unk_00abf990 != 0) {
    return;
  }
  if (((GHIDRA_FIELD(g_gamestate, 12, 4) != 0) && (GHIDRA_FIELD(match_warmupDamage, 12, 4) == 0)) && (param_1[100] != 0)) {
    return;
  }
  if (param_2 == 0) {
    param_2 = 0xabd8a0;
  }
  if (param_3 == (int *)0x0) {
    param_3 = (int *)(g_entities + 0x17f400);
  }
  if (param_1[0x116] - 1U < 2) {
    return;
  }
  tmp_i10 = param_1[0xb2];
  if ((int)GHIDRA_FIELD(g_forceLimboHealth, 12, 4) < 1) {
    local_4c = -0x4b;
    if (GHIDRA_FIELD(g_forceLimboHealth, 12, 4) != 0) {
      local_4c = GHIDRA_FIELD(g_forceLimboHealth, 12, 4);
    }
  }
  else {
    local_4c = -GHIDRA_FIELD(g_forceLimboHealth, 12, 4);
  }
  if (((param_1[1] == 0x22) && (param_1[0xb7] == 0x42)) && ((g_damageweapons[0xc] & 0x20) == 0)) {
    return;
  }
  if (((param_1[100] != 0) && ((param_3[100] != 0 && GHIDRA_FIELD(g_gamestate, 12, 4) == 0) && tmp_i7 == 0)) &&
     (param_3 != param_1)) {
    tmp_pu1 = (uint *)(param_1[100] + 0x1054);
    *tmp_pu1 = *tmp_pu1 | 4;
    *(uint *)(param_3[100] + 0x1054) = *(uint *)(param_3[100] + 0x1054) | 2;
  }
  if ((param_8 == 0x11) && (2 < param_1[0xc1])) {
    return;
  }
  tmp_i11 = param_1[1];
  if (tmp_i11 == 4) {
    if (param_1[0xe1] == 0) {
      if (param_1[0xeb] == 0) {
        if (param_1[0xad] == 0) {
          return;
        }
        if (param_1[0x79] != 0) {
          return;
        }
        G_UseEntity(param_1,param_2,param_3);
        return;
      }
      if ((*(byte *)(param_1 + 0x6a) & 4) != 0) {
        tmp_i11 = G_WeaponIsExplosive(param_8);
        if (tmp_i11 == 0) {
          return;
        }
        tmp_i11 = G_GetTeamFromEntity(param_2);
        tmp_i8 = G_GetTeamFromEntity(param_1);
        if ((tmp_i11 == tmp_i8) && ((GHIDRA_FIELD(g_friendlyFire, 12, 4) & 8) == 0)) {
          return;
        }
      }
    }
  }
  else if (tmp_i11 == 0xe) {
    if ((param_1[0x86] != 0) && (tmp_i11 = G_GetWeaponClassForMOD(param_8), tmp_i11 == 2)) {
      return;
    }
    tmp_i11 = G_GetTeamFromEntity(param_2);
    tmp_i8 = G_GetTeamFromEntity(param_1);
    if (tmp_i11 == tmp_i8) {
      return;
    }
    tmp_i11 = G_GetWeaponClassForMOD(param_8);
    if (tmp_i11 < param_1[0x13d]) {
      return;
    }
  }
  else if (tmp_i11 == 3) {
    if (param_1[0xb7] == 0x28) {
      if (param_1[0x2a] == 0) {
        return;
      }
      tmp_i7 = G_WeaponIsExplosive(param_8);
      if (tmp_i7 == 0) {
        return;
      }
      if (param_3[100] != 0) {
        AddScore(param_3,1);
      }
      G_ExplodeMissile(param_1);
      return;
    }
  }
  else if (tmp_i11 == 0x20) {
    tmp_i11 = G_GetTeamFromEntity(param_2);
    tmp_i8 = G_GetTeamFromEntity(param_1);
    if (tmp_i11 == tmp_i8) {
      return;
    }
    tmp_i11 = G_GetWeaponClassForMOD(param_8);
    if (tmp_i11 < param_1[0x13d]) {
      return;
    }
    if ((param_8 == 0x15) && ((*(byte *)(param_2 + 0x4fc) & 1) == 0)) {
      return;
    }
  }
  tmp_i11 = param_1[100];
  if (tmp_i11 == 0) {
    local_50 = param_7 & 8;
    if (local_50 == 0) goto LAB_00079500;
  }
  else {
    local_50 = param_7 & 8;
    if (local_50 == 0) {
      if (*(int *)(tmp_i11 + 0xf6c) != 0) {
        return;
      }
      if (*(int *)(tmp_i11 + 0x154) != 0) {
        return;
      }
LAB_00079500:
      local_50 = param_1[0x6c] & 0x10;
      if (local_50 != 0) {
        return;
      }
    }
  }
  if (param_4 == (float *)0x0) {
    local_50 = param_7 & 8;
    tmp_i8 = tmp_i11;
    param_7 = param_7 | 4;
  }
  else {
    VectorNormalize(param_4);
    tmp_i8 = param_1[100];
  }
  tmp_i13 = 0;
  if (((*(byte *)((int)param_1 + 0x1b1) & 8) == 0) && (tmp_i13 = 200, param_6 < 0xc9)) {
    tmp_i13 = param_6;
  }
  if ((param_7 & 4) == 0) {
    if ((param_7 & 2) != 0) {
      tmp_i13 = (int)ROUND((float)tmp_i13 * 0.5);
    }
  }
  else {
    tmp_i13 = 0;
  }
  if ((tmp_i11 != 0) && ((*(uint *)(tmp_i11 + 0xa4) & 0xfffffffb) == 0x2a)) {
    tmp_i13 = (int)ROUND((float)tmp_i13 * 0.5);
  }
  tmp_b15 = tmp_i7 != 0;
  if (((((tmp_i8 == 0) || (!tmp_b15)) || ((GHIDRA_FIELD(g_friendlyFire, 12, 4) & 0x11) != 0)) ||
      (GHIDRA_FIELD(g_gametype, 12, 4) == 8)) && ((0 < tmp_i13 && (tmp_i8 != 0)))) {
    tmp_f5 = ((float)tmp_i13 * (float)GHIDRA_FIELD(g_knockback, 8, 4)) / 200.0;
    tmp_f3 = param_4[1];
    tmp_f4 = param_4[2];
    *(float *)(tmp_i8 + 0x20) = tmp_f5 * *param_4 + *(float *)(tmp_i8 + 0x20);
    *(float *)(param_1[100] + 0x24) = tmp_f3 * tmp_f5 + *(float *)(param_1[100] + 0x24);
    *(float *)(param_1[100] + 0x28) = tmp_f4 * tmp_f5 + *(float *)(param_1[100] + 0x28);
    if (param_3[100] != 0) {
      tmp_i8 = param_1[100];
      if (*(int *)(tmp_i8 + 0x50) == 0x3ff) {
        tmp_i8 = G_WeaponIsExplosive(param_8);
        if (tmp_i8 == 0) goto LAB_0007a282;
        tmp_i8 = param_1[100];
      }
      *(uint32_t *)(tmp_i8 + 0x5318) = 1;
      *(int *)(param_1[100] + 0x531c) = ((int)(param_3 + -0x24f928) >> 9) * -0x55555555;
    }
LAB_0007a282:
    if (param_3 == param_1) {
      switch(param_8) {
      case 4:
      case 0x10:
      case 0x15:
      case 0x26:
      case 0x27:
      case 0x28:
        break;
      default:
        *(float *)(param_3[100] + 0x28) = *(float *)(param_3[100] + 0x28) * 0.25;
      }
    }
    if (*(int *)(param_1[100] + 0x10) == 0) {
      tmp_i13 = tmp_i13 * 2;
      tmp_i8 = 0x32;
      if ((0x31 < tmp_i13) && (tmp_i8 = 200, tmp_i13 < 0xc9)) {
        tmp_i8 = tmp_i13;
      }
      *(int *)(param_1[100] + 0x10) = tmp_i8;
      *(uint *)(param_1[100] + 0xc) = *(uint *)(param_1[100] + 0xc) | 0x40;
    }
  }
  if (((local_50 == 0) && (param_3 != param_1)) && (tmp_b15)) {
    if ((GHIDRA_FIELD(g_gamestate, 12, 4) != 0) && (GHIDRA_FIELD(match_warmupDamage, 12, 4) == 1)) {
      return;
    }
    if ((GHIDRA_FIELD(g_friendlyFire, 12, 4) & 1) != 0) goto LAB_0007a078;
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
      local_50 = 0;
      if (-1 < param_6) {
        local_50 = param_6;
      }
    }
    else {
      if (param_8 != 0x28) {
        return;
      }
      if ((GHIDRA_FIELD(g_friendlyFire, 12, 4) & 0x40) == 0) {
        return;
      }
      local_50 = 0;
      if (-1 < param_6) {
        local_50 = param_6;
      }
      if ((GHIDRA_FIELD(g_friendlyFire, 12, 4) & 4) != 0) {
LAB_0007967b:
        G_Damage(param_3,param_3,param_3,param_4,param_5,local_50,param_7,param_8);
      }
LAB_000796ca:
      if ((((GHIDRA_FIELD(g_friendlyFire, 12, 4) & 2) != 0) && (tmp_b15 && param_3 != param_1)) &&
         (param_8 != 0x3b)) {
        local_50 = (uint)ROUND((float)(int)local_50 * 0.5);
      }
    }
  }
  else {
LAB_0007a078:
    local_50 = 0;
    if (-1 < param_6) {
      local_50 = param_6;
    }
    if (GHIDRA_FIELD(g_gametype, 12, 4) != 8) {
      if ((GHIDRA_FIELD(g_friendlyFire, 12, 4) & 4) == 0) goto LAB_000796ca;
      if ((param_3 != param_1) && (tmp_b15)) goto LAB_0007967b;
    }
  }
  tmp_i8 = 0;
  if (param_1[100] != 0) {
    if (*(int *)(param_1[100] + 0x17c) != 0) {
      local_50 = (uint)ROUND((float)(int)local_50 * 0.5);
    }
    tmp_i8 = G_WeaponIsExplosive(param_8);
    if (((tmp_i8 != 0) || (param_8 == 0x42)) && (tmp_i8 = G_HasFlakJacket(param_1), tmp_i8 != 0)) {
      local_50 = (uint)ROUND((float)(int)local_50 * 0.5);
    }
    tmp_i8 = param_1[100];
  }
  if (((GHIDRA_FIELD(g_weapons, 12, 4) & 8) == 0) || (param_8 != 0x28)) {
    if ((param_8 != 0x3f) || ((GHIDRA_FIELD(g_weapons, 12, 4) & 0x800) == 0)) goto LAB_000797e0;
    if (tmp_i8 != 0) {
      if (0 < param_1[0xb2]) {
        *(uint *)(tmp_i8 + 0x68) = *(uint *)(tmp_i8 + 0x68) | 0x200000;
        *(int *)(param_1[100] + 0x5300) = *param_3;
        *(uint32_t *)(param_1[100] + 0x53a0) = g_unk_00abe908;
        *(uint32_t *)(param_1[100] + 0x5304) = 1;
        tmp_i8 = param_1[100];
        goto LAB_000797e0;
      }
      goto LAB_000797e8;
    }
    tmp_i7 = 0;
    if ((g_headshot[0xc] & 1) == 0) goto LAB_0007a366;
    local_38 = -1;
    if (param_3[100] != 0) goto LAB_0007a03e;
    goto LAB_0007a36b;
  }
  if ((param_3[100] != 0) && ((*(byte *)(param_3[100] + 0xed4) & 0x20) != 0)) {
    local_50 = (uint)ROUND((float)(int)local_50 * 1.5);
  }
LAB_000797e0:
  if (tmp_i8 == 0) {
    if ((g_headshot[0xc] & 1) != 0) {
      if (param_3[100] == 0) {
        tmp_i7 = 0;
        goto LAB_0007a366;
      }
      goto LAB_0007a03e;
    }
    goto _L861;
  }
LAB_000797e8:
  tmp_i8 = BG_WeaponForMOD(param_8);
  if (*(int *)(BG_Weapons + tmp_i8 * 0x6b0 + 0x684) == 1) goto _L715;
  tmp_i8 = BG_WeaponForMOD(param_8);
  if (*(int *)(BG_Weapons + tmp_i8 * 0x6b0 + 0x684) == 2) goto _L712;
  switch(param_8) {
  case 5:
    tmp_u14 = GHIDRA_FIELD(g_weapons, 12, 4) & 1;
    goto joined_r0x0007a06a;
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0x24:
  case 0x25:
  case 0x2c:
  case 0x2d:
  case 0x31:
  case 0x32:
  case 0x34:
  case 0x35:
  case 0x36:
  case 0x37:
    goto _L715;
  case 0x2b:
    if ((GHIDRA_FIELD(g_weapons, 12, 4) & 0x80) != 0) goto _L715;
    break;
  case 0x3f:
    tmp_u14 = GHIDRA_FIELD(g_weapons, 12, 4) & 2;
joined_r0x0007a06a:
    if (tmp_u14 == 0) break;
_L715:
    local_38 = param_3[0x17b];
    if (((g_headshot[0xc] & 1) == 0) || (param_3[100] == 0)) {
      if (local_38 == 0) goto LAB_000798a0;
      goto LAB_0007a9a9;
    }
    if (local_38 != 0) goto LAB_0007a03e;
LAB_000798a0:
    tmp_i8 = *(int *)(BG_Weapons + param_3[0x3a] * 0x6b0 + 0x698);
    tmp_f3 = *(float *)(BG_Weapons + param_3[0x3a] * 0x6b0 + 0x69c);
    if (tmp_i8 == 0) {
      tmp_i8 = 0x32;
    }
    if (tmp_f3 == 0.0) {
      tmp_f3 = 2.0;
    }
    tmp_f4 = (float)(int)local_50;
    local_50 = tmp_i8;
    if (tmp_i8 <= (int)ROUND(tmp_f4 * tmp_f3)) {
      local_50 = (int)ROUND(tmp_f4 * tmp_f3);
    }
    local_28 = *param_5 - muzzleTrace;
    local_24 = param_5[1] - g_unk_02e432e4;
    local_20 = param_5[2] - g_unk_02e432e8;
    tmp_l16 = (long double)VectorLength(&local_28);
    if ((param_7 & 0x10) != 0) {
      tmp_l16 = (long double)1 -
               ((tmp_l16 - (long double)1500.0) / (long double)1000.0) * (long double)0.8;
      if (tmp_l16 <= (long double)1) {
        tmp_l17 = (long double)0.2;
        if ((long double)0.2 <= tmp_l16) {
          tmp_l17 = tmp_l16;
        }
      }
      else {
        tmp_l17 = (long double)1;
      }
      local_50 = (uint)ROUND((long double)(int)local_50 * tmp_l17);
    }
    if ((*(byte *)(param_1[100] + 0x69) & 0x10) == 0) {
      tmp_u9 = DirToByte(param_4);
      G_AddEvent(param_1,0x33,tmp_u9);
      if ((param_8 != 0x2d) && (param_8 != 0x32)) {
        local_50 = (uint)ROUND((float)(int)local_50 * 0.8);
      }
    }
    tmp_u14 = param_7 | 0x20;
    if ((g_headshot[0xc] & 2) == 0) {
      tmp_u14 = param_7;
    }
    param_7 = tmp_u14;
    if ((param_8 == 0x2d) || (param_8 == 0x32)) {
      if ((tmp_i7 == 0) && ((*(byte *)(param_1 + 0x4a) & 8) == 0)) {
        nitrox_CheckGlobalAwards(param_3,7,1);
      }
      if (GHIDRA_FIELD(g_war, 12, 4) == 2) {
        if ((n_sniperWarOptions[0xc] & 2) == 0) {
          if (((*(byte *)(param_3[100] + 0xee8) & 0x20) == 0) ||
             (tmp_u14 = param_1[0xb2], param_1[0xb2] < 1)) {
            tmp_u14 = (int)ROUND((long double)(int)local_50);
          }
        }
        else {
          param_7 = tmp_u14 | 0x20;
          tmp_u14 = local_50;
        }
        local_50 = tmp_u14;
        Nit_HitSound(param_3,4);
        goto LAB_000799f1;
      }
      tmp_i8 = param_3[100];
      if (((*(byte *)(tmp_i8 + 0xee8) & 0x20) == 0) || (tmp_u14 = param_1[0xb2], param_1[0xb2] < 1)) {
        tmp_u14 = (int)ROUND((long double)(int)local_50);
      }
    }
    else {
LAB_000799f1:
      tmp_i8 = param_3[100];
      tmp_u14 = local_50;
    }
    local_50 = tmp_u14;
    *(int *)(tmp_i8 + 0x536c) = *(int *)(tmp_i8 + 0x536c) + 1;
    if ((((tmp_i11 != 0) && (param_3[100] != 0)) &&
        (*(int *)(param_3[100] + 3000) != *(int *)(param_1[100] + 3000))) && (0 < param_1[0xb2])) {
      G_addStatsHeadShot(param_3,param_8);
    }
    if (GHIDRA_FIELD(g_debugBullets, 12, 4) != 0) {
      trap_SendServerCommand
                (((int)(param_3 + -0x24f928) >> 9) * -0x55555555,"print \"Head Shot\n\"\n");
    }
    G_LogRegionHit(param_3,0);
    if (((((g_unk_02b9a658 == 0) && ((g_announcer[0xc] & 0x10) != 0)) &&
         ((param_1[100] != 0 && ((0 < param_1[0xb2] && (param_3[100] != 0)))))) &&
        (1 < *param_3 - 0x3feU)) &&
       (((param_3 != param_1 && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) && (tmp_i7 == 0)))) {
      nitmod_Sound_Global(0xf);
      tmp_u9 = va("pop \"^7%s ^ghad the ^1FIRST HEADSHOT^g from ^7%s^7!\"",param_3[100] + 0x5f8,
                 param_1[100] + 0x5f8);
      trap_SendServerCommand(0xffffffff,tmp_u9);
      trap_SendServerCommand(((int)(param_3 + -0x24f928) >> 9) * -0x55555555,"an 5 0");
      g_unk_02b9a658 = 1;
    }
    tmp_b6 = true;
    local_38 = 0;
    goto LAB_00079adf;
  }
_L712:
  if ((g_headshot[0xc] & 1) == 0) {
    tmp_i7 = param_1[100];
LAB_0007a366:
    local_38 = -1;
LAB_0007a36b:
    if (GHIDRA_FIELD(g_hitboxes, 12, 4) == 0) {
      if (tmp_i7 != 0) {
        tmp_i7 = IsLegShot(param_1,param_4,param_5,param_8);
        if ((tmp_i7 == 0) && (param_3[0x17b] != 3)) {
          if (GHIDRA_FIELD(g_hitboxes, 12, 4) == 0) {
            if (param_1[100] == 0) goto _L861;
            tmp_i7 = IsArmShot(param_1,param_3,param_5,param_8);
            if (tmp_i7 != 0) {
              G_LogRegionHit(param_3,1);
              if (GHIDRA_FIELD(g_debugBullets, 12, 4) == 0) {
                tmp_b6 = false;
                local_38 = 1;
              }
              else {
                trap_SendServerCommand
                          (((int)(param_3 + -0x24f928) >> 9) * -0x55555555,"print \"Arm Shot\n\"\n")
                ;
                tmp_b6 = false;
                local_38 = 1;
              }
              goto LAB_00079adf;
            }
            tmp_i7 = param_1[100];
          }
          else {
            tmp_i7 = param_1[100];
          }
          goto LAB_0007a421;
        }
        G_LogRegionHit(param_3,3);
        if (GHIDRA_FIELD(g_debugBullets, 12, 4) == 0) {
          tmp_b6 = false;
          local_38 = 3;
        }
        else {
          trap_SendServerCommand
                    (((int)(param_3 + -0x24f928) >> 9) * -0x55555555,"print \"Leg Shot\n\"\n");
          tmp_b6 = false;
          local_38 = 3;
        }
        goto LAB_00079adf;
      }
      goto _L861;
    }
LAB_0007a421:
    if (tmp_i7 == 0) goto _L861;
    tmp_i7 = param_1[0xb2];
    if (0 < tmp_i7) {
      if (GHIDRA_FIELD(g_hitboxes, 12, 4) != 0) {
        if (0 < local_38) {
          G_LogRegionHit(param_3,local_38);
          tmp_b6 = false;
          if (GHIDRA_FIELD(g_debugBullets, 12, 4) != 0) {
            if (local_38 == 2) {
              tmp_pc12 = "print \"Body Shot\n\"\n";
            }
            else if (local_38 == 3) {
              tmp_pc12 = "print \"Leg Shot\n\"\n";
            }
            else {
              if (local_38 != 1) goto LAB_00079adf;
              tmp_pc12 = "print \"Arm Shot\n\"\n";
            }
            tmp_u9 = va(tmp_pc12);
            trap_SendServerCommand(((int)(param_3 + -0x24f928) >> 9) * -0x55555555,tmp_u9);
          }
          goto LAB_00079adf;
        }
        if ((param_7 & 0x20) == 0) {
          if (param_8 != 0x3a) goto LAB_0007ad40;
          tmp_b6 = false;
          local_38 = 4;
          goto LAB_0007a534;
        }
        tmp_b6 = false;
        local_38 = 4;
        goto LAB_00079afb;
      }
      tmp_i7 = BG_WeaponForMOD(param_8);
      if (*(int *)(BG_Weapons + tmp_i7 * 0x6b0 + 0x684) == 1) {
_L754:
        G_LogRegionHit(param_3,2);
        if (GHIDRA_FIELD(g_debugBullets, 12, 4) == 0) {
          tmp_b6 = false;
          local_38 = 2;
        }
        else {
          tmp_u9 = va("print \"Body Shot\n\"\n");
          trap_SendServerCommand(((int)(param_3 + -0x24f928) >> 9) * -0x55555555,tmp_u9);
          tmp_b6 = false;
          local_38 = 2;
        }
        goto LAB_00079adf;
      }
      tmp_i7 = BG_WeaponForMOD(param_8);
      if (*(int *)(BG_Weapons + tmp_i7 * 0x6b0 + 0x684) == 2) goto _L861;
      switch(param_8) {
      case 5:
        tmp_u14 = GHIDRA_FIELD(g_weapons, 12, 4) & 1;
        break;
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 0xb:
      case 0xc:
      case 0xd:
      case 0xe:
      case 0x24:
      case 0x25:
      case 0x2c:
      case 0x2d:
      case 0x31:
      case 0x32:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
        goto _L754;
      default:
        goto _L861;
      case 0x2b:
        tmp_u14 = GHIDRA_FIELD(g_weapons, 12, 4) & 0x80;
        break;
      case 0x3f:
        tmp_u14 = GHIDRA_FIELD(g_weapons, 12, 4) & 2;
      }
      if (tmp_u14 != 0) goto _L754;
      if ((param_7 & 0x20) == 0) goto LAB_0007ad40;
      tmp_i7 = param_1[0xb2];
      tmp_b6 = false;
      local_38 = 4;
      goto LAB_00079af3;
    }
    if ((param_7 & 0x20) == 0) {
      if (param_8 == 0x3a) {
        tmp_b6 = false;
        local_38 = 4;
        goto LAB_0007ae82;
      }
LAB_0007ad40:
      tmp_b6 = false;
      local_38 = 4;
      tmp_u14 = local_50;
      goto LAB_00079b04;
    }
    tmp_b6 = false;
    local_38 = 4;
LAB_0007a744:
    local_50 = 0xaf;
    tmp_u14 = local_50;
  }
  else {
    if (param_3[100] == 0) {
      local_38 = -1;
LAB_0007a9a9:
      tmp_i7 = param_1[100];
      goto LAB_0007a36b;
    }
LAB_0007a03e:
    if (param_1[100] != 0) {
      return;
    }
_L861:
    tmp_b6 = false;
    local_38 = 4;
LAB_00079adf:
    if ((param_7 & 0x20) == 0) {
      tmp_u14 = local_50;
      if (param_8 == 0x3a) {
        tmp_i7 = param_1[0xb2];
        if (tmp_i7 < 1) {
LAB_0007ae82:
          tmp_u14 = 0xaf;
          if ((int)local_50 <= -local_4c) {
            tmp_u14 = local_50;
          }
        }
        else {
LAB_0007a534:
          tmp_u14 = local_50;
          if (tmp_i7 - local_4c < (int)local_50) goto LAB_00079afb;
        }
      }
    }
    else {
      tmp_i7 = param_1[0xb2];
LAB_00079af3:
      if (tmp_i7 < 1) goto LAB_0007a744;
LAB_00079afb:
      tmp_u14 = tmp_i7 + 0xaf;
    }
  }
LAB_00079b04:
  local_50 = tmp_u14;
  if (GHIDRA_FIELD(g_debugDamage, 12, 4) != 0) {
    G_Printf("client:%i health:%i damage:%i mod:%s\n",*param_1,param_1[0xb2],local_50,
             *(uint32_t *)(modNames + param_8 * 4));
  }
  if (tmp_i11 != 0) {
    if (param_4 == (float *)0x0) {
      *(int *)(tmp_i11 + 0xf94) = param_1[0x5a];
      *(int *)(tmp_i11 + 0xf98) = param_1[0x5b];
      tmp_i7 = param_1[0x5c];
      *(uint32_t *)(tmp_i11 + 4000) = 1;
      *(int *)(tmp_i11 + 0xf9c) = tmp_i7;
    }
    else {
      *(float *)(tmp_i11 + 0xf94) = *param_4;
      *(float *)(tmp_i11 + 0xf98) = param_4[1];
      tmp_f3 = param_4[2];
      *(uint32_t *)(tmp_i11 + 4000) = 0;
      *(float *)(tmp_i11 + 0xf9c) = tmp_f3;
    }
  }
  tmp_i7 = param_3[100];
  tmp_i8 = param_1[100];
  if (((tmp_i7 == 0) || (param_3 == param_1)) || (tmp_i8 == 0)) {
    if (tmp_b6) {
LAB_0007a0dc:
      *(uint *)(tmp_i8 + 0x68) = *(uint *)(tmp_i8 + 0x68) | 0x1000;
      *(uint *)(param_1[100] + 0x1a10) = *(uint *)(param_1[100] + 0x1a10) | 0x1000;
      if (!tmp_b15) {
        if (((*(int *)(param_1[100] + 0x16c) == 0) ||
            (((GHIDRA_FIELD(g_friendlyFire, 12, 4) & 1) == 0 && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)))) ||
           (((*(byte *)(param_3[100] + 0xedc) & 0x10) != 0 &&
            ((tmp_i7 = IsClass(param_3,3), tmp_i7 != 0 || ((jp_keepAwards[0xc] & 2) != 0)))))) {
          *(int *)(param_3[100] + 0x114) = *(int *)(param_3[100] + 0x114) + 1;
          tmp_i7 = param_1[0xb2];
        }
        else {
          Nit_HitSound(param_3,3);
          tmp_i7 = param_1[0xb2];
        }
        if (0 < tmp_i7) {
          *(int *)(param_3[100] + 0x124) = *(int *)(param_3[100] + 0x124) + 1;
          *(int *)(param_3[100] + 0xf3c) = *(int *)(param_3[100] + 0xf3c) + 1;
        }
        goto LAB_00079c30;
      }
      Nit_HitSound(param_3,3);
      tmp_i8 = param_1[100];
    }
LAB_00079c36:
    if (tmp_i8 != 0) goto LAB_00079c3a;
  }
  else {
    if ((((local_4c < param_1[0xb2]) && (param_8 != 0x39)) && (param_8 != 0x20)) &&
       ((1 < param_8 - 0x3bU && ((bool)(tmp_b6 ^ 1))))) {
      if (tmp_b15) {
        Nit_HitSound(param_3,3);
        goto LAB_00079c30;
      }
      if ((*(int *)(tmp_i8 + 0x16c) == 0) ||
         (((GHIDRA_FIELD(g_friendlyFire, 12, 4) & 1) == 0 && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)))) {
LAB_00079bfb:
        *(int *)(tmp_i7 + 0x118) = *(int *)(tmp_i7 + 0x118) + 1;
        tmp_i7 = param_1[0xb2];
      }
      else {
        if (((*(byte *)(tmp_i7 + 0xedc) & 0x10) != 0) &&
           ((tmp_i7 = IsClass(param_3,3), tmp_i7 != 0 || ((jp_keepAwards[0xc] & 2) != 0)))) {
          tmp_i7 = param_3[100];
          goto LAB_00079bfb;
        }
        Nit_HitSound(param_3,3);
        tmp_i7 = param_1[0xb2];
      }
      if (0 < tmp_i7) {
        *(int *)(param_3[100] + 0x128) = *(int *)(param_3[100] + 0x128) + 1;
        *(int *)(param_3[100] + 0xf38) = *(int *)(param_3[100] + 0xf38) + 1;
      }
LAB_00079c30:
      tmp_i8 = param_1[100];
      goto LAB_00079c36;
    }
    if (tmp_b6) goto LAB_0007a0dc;
LAB_00079c3a:
    *(int *)(tmp_i8 + 0xfa4) = *param_3;
    *(int *)(param_1[100] + 0xfa8) = param_8;
    *(uint32_t *)(param_1[100] + 0xfac) = g_unk_00abe908;
    if (param_3[100] != 0) {
      tmp_pi2 = (int *)(param_1[100] + 0x53bc + ((int)(param_3 + -0x24f928) >> 9) * -0x55555554);
      *tmp_pi2 = *tmp_pi2 + local_50;
    }
  }
  if (local_50 == 0) goto LAB_00079d83;
  tmp_i7 = param_1[0xb2];
  param_1[0xb2] = tmp_i7 - local_50;
  if ((int)(tmp_i7 - local_50) < -0xae) {
    tmp_i7 = BG_WeaponForMOD(param_8);
    if ((*(int *)(BG_Weapons + tmp_i7 * 0x6b0 + 0x688) != 1) &&
       ((*(int *)(BG_Weapons + tmp_i7 * 0x6b0 + 0x688) == 2 ||
        (tmp_i7 = G_WeaponIsExplosive(param_8), tmp_i7 == 0)))) {
      param_1[0xb2] = -0xae;
    }
  }
  if (((int)local_50 < 0xbf) || (0x3f < *param_1)) {
    tmp_i7 = param_1[0xb2];
    if ((param_1[1] == 4) && (param_1[0x170] == 0x27cac)) goto LAB_0007a8e8;
LAB_0007a488:
    if (tmp_i7 < 1) goto LAB_00079ced;
    if ((void *)param_1[0xae] == (void *)0x0) {
      if ((param_8 != 0x11) && (param_8 != 0x3b)) {
        G_addStats(param_1,param_3,local_50,param_8);
        tmp_i7 = param_1[0xb2];
      }
    }
    else {
      if (param_4 == (float *)0x0) {
        param_1[0xcb] = 0;
        param_1[0xca] = 0;
        param_1[0xc9] = 0;
        param_1[0x91] = 0;
        param_1[0x90] = 0;
        param_1[0x8f] = 0;
      }
      else {
        param_1[0xc9] = (int)*param_4;
        param_1[0xca] = (int)param_4[1];
        param_1[0xcb] = (int)param_4[2];
        param_1[0x8f] = (int)*param_5;
        param_1[0x90] = (int)param_5[1];
        param_1[0x91] = (int)param_5[2];
      }
      (*(void *)param_1[0xae])(param_1,param_3,local_50,param_5);
      tmp_i7 = param_1[0xb2];
    }
  }
  else {
    param_1[0xb2] = -0xb0;
    if ((param_1[1] == 4) && (param_1[0x170] == 0x27cac)) {
      tmp_i7 = -0xb0;
LAB_0007a8e8:
      param_1[0x27] = (int)ROUND(((float)tmp_i7 / (float)param_1[0xb9]) * 255.0);
      goto LAB_0007a488;
    }
LAB_00079ced:
    if ((0 < tmp_i10) < (tmp_i11 != 0)) {
      param_1[0x6c] = param_1[0x6c] | 0x800;
      if (*(int *)(param_1[100] + 4) == 3) {
        G_addStats(param_1,param_3,local_50,param_8);
      }
      tmp_i7 = param_1[0xb2];
      if ((tmp_i7 < local_4c) && (-0xaf < tmp_i7)) {
        limbo(param_1,1);
        tmp_i7 = param_1[0xb2];
      }
      if (tmp_i7 < -0xae) {
        GibEntity(param_1,0);
        tmp_i7 = param_1[0xb2];
      }
    }
    else {
      param_1[0x7c] = param_8;
      param_1[0x7b] = local_38;
      param_1[0x7f] = param_7 & 1;
      if (tmp_i11 != 0) {
        tmp_i7 = G_GetTeamFromEntity(param_2);
        tmp_i10 = G_GetTeamFromEntity(param_1);
        if (tmp_i7 != tmp_i10) {
          G_AddKillSkillPoints(param_3,param_1,param_8,local_38,param_7 & 1);
        }
      }
      if (param_1[0xb2] < -999) {
        param_1[0xb2] = -999;
      }
      param_1[0xbb] = (int)param_3;
      param_1[0xbf] = param_8;
      if ((void *)param_1[0xaf] != (void *)0x0) {
        (*(void *)param_1[0xaf])(param_1,param_2,param_3,local_50,param_8);
      }
      tmp_i10 = param_1[1];
      if (((tmp_i10 == 4) && (param_1[0x170] == 0x27cac)) && ((*(byte *)(param_1 + 0x6a) & 8) != 0))
      {
        return;
      }
      if (param_1[0x65] == 0) {
        return;
      }
      tmp_i7 = param_1[0xb2];
      if (tmp_i7 < 1) {
        if ((*(byte *)(param_1 + 0x4a) & 8) == 0) {
          if (tmp_i10 == 0x20) {
LAB_0007b18b:
            if (param_1[0x118] != 0) goto LAB_00079d40;
          }
          else if (tmp_i10 == 0xe) goto LAB_00079d40;
          G_Script_ScriptEvent(param_1,"death",&g_unk_0026ea14);
          tmp_i7 = param_1[0xb2];
        }
        else if (tmp_i10 == 0x20) goto LAB_0007b18b;
      }
    }
  }
LAB_00079d40:
  tmp_u9 = va("%d %d",tmp_i7,local_50 + tmp_i7);
  G_Script_ScriptEvent(param_1,&g_unk_00248452,tmp_u9);
  if (*param_1 < g_unk_00abe900) {
    Bot_Event_TakeDamage(((int)(param_1 + -0x24f928) >> 9) * -0x55555555,param_3);
  }
LAB_00079d83:
  tmp_i7 = param_1[100];
  if (tmp_i7 == 0) {
    return;
  }
  if (*(int *)(tmp_i7 + 4) != 3) {
    if (local_50 == 0) {
      return;
    }
    tmp_u14 = 0x7f;
    if ((int)local_50 < 0x80) {
      tmp_u14 = local_50;
    }
    if ((param_8 == 0x3b) || (*(int *)(tmp_i11 + 4000) == 0)) {
      vectoangles(tmp_i11 + 0xf94,&local_28);
      if (param_8 == 0x3b) {
        tmp_u14 = 0;
      }
      tmp_i7 = (int)ROUND((local_28 / 360.0) * 256.0);
      tmp_i10 = (int)ROUND((local_24 / 360.0) * 256.0);
    }
    else {
      tmp_i10 = 0xff;
      *(uint32_t *)(tmp_i11 + 4000) = 0;
      tmp_i7 = 0xff;
    }
    nitrox_AddPredictableDamage(tmp_u14,tmp_i7,tmp_i10,param_1[100]);
    *(uint32_t *)(tmp_i11 + 4000) = 0;
    *(uint32_t *)(tmp_i11 + 0xf9c) = 0;
    *(uint32_t *)(tmp_i11 + 0xf98) = 0;
    *(uint32_t *)(tmp_i11 + 0xf94) = 0;
    tmp_i7 = param_1[100];
    if (tmp_i7 == 0) {
      return;
    }
  }
  *(int *)(tmp_i7 + 0xd0) = param_1[0xb2];
  return;
}

byte G_GetPrimaryWeaponForClient(int param_1)
{
  int tmp_i1;
  byte tmp_b2;
  
  tmp_b2 = 0;
  if (*(int *)(param_1 + 3000) != 3) {
    param_1 = param_1 + 0x3d4;
    tmp_i1 = COM_BitCheck(param_1,5);
    tmp_b2 = 5;
    if (tmp_i1 == 0) {
      tmp_i1 = COM_BitCheck(param_1,0x1d);
      tmp_b2 = 0x1d;
      if (tmp_i1 == 0) {
        tmp_i1 = COM_BitCheck(param_1,0x21);
        tmp_b2 = 0x21;
        if (tmp_i1 == 0) {
          tmp_i1 = COM_BitCheck(param_1,6);
          tmp_b2 = 6;
          if (tmp_i1 == 0) {
            tmp_i1 = COM_BitCheck(param_1,0x1e);
            tmp_b2 = 0x1e;
            if (tmp_i1 == 0) {
              tmp_i1 = COM_BitCheck(param_1,0x18);
              tmp_b2 = 0x18;
              if (tmp_i1 == 0) {
                tmp_i1 = COM_BitCheck(param_1,0x17);
                tmp_b2 = 0x17;
                if (tmp_i1 == 0) {
                  tmp_i1 = COM_BitCheck(param_1,0x16);
                  tmp_b2 = 0x16;
                  if (tmp_i1 == 0) {
                    tmp_i1 = COM_BitCheck(param_1,0x1f);
                    tmp_b2 = 0x1f;
                    if (tmp_i1 == 0) {
                      tmp_i1 = COM_BitCheck(param_1,10);
                      tmp_b2 = 10;
                      if (tmp_i1 == 0) {
                        tmp_i1 = COM_BitCheck(param_1,3);
                        tmp_b2 = 3;
                        if (tmp_i1 == 0) {
                          tmp_i1 = COM_BitCheck(param_1,8);
                          tmp_b2 = ~-(tmp_i1 == 0) & 8;
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
  }
  return tmp_b2;
}

bool G_CanPickupWeapon(uint param_1,int param_2)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  bool tmp_b3;
  int tmp_i4;
  
  tmp_u1 = *(uint32_t *)(*(int *)(param_2 + 400) + 0xbc8);
  tmp_i4 = G_IsWeaponDisabled(param_2,param_1,0,1);
  if (tmp_i4 != 0) {
    return false;
  }
  if (GHIDRA_FIELD(g_war, 12, 4) == 2) {
    return param_1 == 0x1e || param_1 == 0x18;
  }
  if ((int)GHIDRA_FIELD(g_war, 12, 4) < 3) {
    if (GHIDRA_FIELD(g_war, 12, 4) == 1) {
      return param_1 == 5;
    }
  }
  else {
    if (GHIDRA_FIELD(g_war, 12, 4) == 3) goto LAB_00081ed0;
    if (GHIDRA_FIELD(g_war, 12, 4) == 4) {
      return param_1 == 1;
    }
  }
  if ((param_1 != 1) && (GHIDRA_FIELD(g_pickAnyWeapon, 12, 4) == 0)) {
    tmp_u2 = *(uint *)(BG_Weapons + param_1 * 0x6b0 + 0x6ac);
    tmp_b3 = false;
    if (tmp_u2 == 0) {
      switch(tmp_u1) {
      case 0:
        goto _L131;
      case 1:
_L132:
        if ((param_1 == 8 || param_1 == 3) || (param_1 == 10)) {
          if ((g_medics[0xc] & 4) != 0) {
            return false;
          }
          if (param_1 == 8 || param_1 == 3) {
            return true;
          }
        }
        return param_1 == 10;
      case 2:
        goto _L133;
      case 3:
        goto _L134;
      case 4:
        goto _L135;
      default:
        goto switchD_00081f7c_default;
      }
    }
    switch(tmp_u1) {
    case 0:
      if ((tmp_u2 & 1) != 0) {
        return true;
      }
_L131:
      if (param_1 - 5 < 2) {
        return true;
      }
      if ((param_1 - 0x1d & 0xfffffffb) != 0) {
        return param_1 == 8 || param_1 == 3;
      }
      return true;
    case 1:
      if ((tmp_u2 & 2) == 0) goto _L132;
      break;
    case 2:
      if ((tmp_u2 & 4) != 0) {
        return true;
      }
_L133:
      if ((param_1 != 3) && (param_1 != 8)) {
LAB_00081ed0:
        return param_1 - 0x16 < 2;
      }
      break;
    case 3:
      if ((tmp_u2 & 8) != 0) {
        return true;
      }
_L134:
      return param_1 == 3 || (param_1 & 0xfffffffd) == 8;
    case 4:
      if ((tmp_u2 & 0x10) != 0) {
        return true;
      }
_L135:
      if ((1 < param_1 - 0x1e) && (param_1 != 10)) {
        return param_1 == 0x18;
      }
      break;
    default:
      goto switchD_00081f7c_default;
    }
  }
  tmp_b3 = true;
switchD_00081f7c_default:
  return tmp_b3;
}

uint32_t Pickup_Ammo(int param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  uint32_t tmp_u7;
  int tmp_i8;
  int tmp_i9;
  int local_30;
  
  tmp_i9 = *(int *)(param_2 + 400);
  if (g_unk_00abe908 - *(int *)(tmp_i9 + 0xfe8) < 1000) {
    return 0;
  }
  tmp_i3 = *(int *)(param_1 + 0xf4);
  if (tmp_i3 == 0) {
    tmp_i3 = 1;
  }
  tmp_i2 = *(int *)(*(int *)(param_1 + 0x33c) + 0x28);
  if (tmp_i2 == 0xc) {
    BG_AddMagicAmmo(tmp_i9,tmp_i9 + 0xed0,*(uint32_t *)(tmp_i9 + 3000),
                    tmp_i3 * *(int *)(param_1 + 0x2e4));
    goto LAB_000821e7;
  }
  local_30 = *(int *)(param_1 + 0x2e4);
  if (local_30 == 0) {
    local_30 = tmp_i3 * *(int *)(*(int *)(param_1 + 0x33c) + 0x20);
  }
  tmp_i4 = BG_FindAmmoForWeapon(tmp_i2);
  tmp_i3 = tmp_i4 * 4;
  tmp_i5 = BG_MaxAmmoForWeapon(tmp_i4,*(int *)(param_2 + 400) + 0xed0);
  tmp_i8 = *(int *)(param_2 + 400);
  tmp_i9 = tmp_i8 + tmp_i3;
  if (tmp_i4 - 1U < 0x1b) {
    tmp_u6 = 1 << ((byte)(tmp_i4 - 1U) & 0x1f);
    if ((tmp_u6 & 0x4004108) == 0) {
      if ((tmp_u6 & 1) == 0) {
        if ((tmp_u6 & 0x30) == 0) goto LAB_000821b0;
      }
      else {
        COM_BitSet(tmp_i8 + 0x3d4,tmp_i4);
        tmp_i9 = *(int *)(param_2 + 400) + tmp_i3;
      }
      *(int *)(tmp_i9 + 0x290) = *(int *)(tmp_i9 + 0x290) + local_30;
      tmp_i3 = tmp_i3 + *(int *)(param_2 + 400);
      if (tmp_i5 < *(int *)(tmp_i3 + 0x290)) {
        *(int *)(tmp_i3 + 0x290) = tmp_i5;
      }
    }
    else {
      COM_BitSet(tmp_i8 + 0x3d4,tmp_i4);
      tmp_i9 = *(int *)(param_2 + 400);
      tmp_i3 = BG_FindAmmoForWeapon(tmp_i2);
      if (tmp_i2 - 2U < 0x32) {
        tmp_i8 = BG_FindClipForWeapon(tmp_i2);
        tmp_i5 = *(int *)(ammoTableMP + tmp_i2 * 0x48 + 8) - *(int *)(tmp_i9 + (tmp_i8 + 0xa4) * 4);
        tmp_i3 = tmp_i9 + tmp_i3 * 4;
        tmp_i8 = *(int *)(tmp_i3 + 400);
        if (tmp_i8 < tmp_i5) {
          tmp_i5 = tmp_i8;
        }
        if (tmp_i5 != 0) {
          *(int *)(tmp_i3 + 400) = tmp_i8 - tmp_i5;
          tmp_i3 = BG_FindClipForWeapon(tmp_i2);
          tmp_pi1 = (int *)(tmp_i9 + 0x290 + tmp_i3 * 4);
          *tmp_pi1 = *tmp_pi1 + tmp_i5;
        }
      }
    }
  }
  else {
LAB_000821b0:
    *(int *)(tmp_i9 + 400) = *(int *)(tmp_i9 + 400) + local_30;
    tmp_i3 = tmp_i3 + *(int *)(param_2 + 400);
    if (tmp_i5 < *(int *)(tmp_i3 + 400)) {
      *(int *)(tmp_i3 + 400) = tmp_i5;
    }
  }
  if (0x3e6 < local_30) {
    *(int *)(*(int *)(param_2 + 400) + 400 + tmp_i4 * 4) = local_30;
  }
LAB_000821e7:
  if (*(int *)(param_1 + 0xf4) == 2) {
    tmp_u7 = 0x3e6;
  }
  else {
    tmp_u7 = 0xffffffff;
  }
  return tmp_u7;
}

void G_DropWeapon(uint32_t *param_1,int param_2)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint tmp_u6;
  int tmp_i7;
  uint32_t tmp_u8;
  int tmp_i9;
  float local_90;
  float local_8c;
  uint32_t local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint8_t local_54 [12];
  float local_48;
  uint32_t local_44;
  uint32_t local_40;
  
  tmp_i1 = param_1[100];
  tmp_i5 = BG_FindItemForWeapon(param_2);
  if (tmp_i5 == 0) {
    return;
  }
  local_90 = *(float *)(tmp_i1 + 0xb0);
  local_8c = *(float *)(tmp_i1 + 0xb4);
  local_88 = *(uint32_t *)(tmp_i1 + 0xb8);
  if (local_90 < -30.0) {
    local_90 = -30.0;
  }
  else if (30.0 < local_90) {
    local_90 = 30.0;
  }
  if (param_2 == 1) {
    local_8c = local_8c + 5.0;
  }
  AngleVectors(&local_90,&local_84,0,0);
  tmp_f4 = local_80;
  tmp_f3 = local_84;
  local_84 = local_84 * 75.0;
  local_80 = local_80 * 75.0;
  tmp_f2 = local_7c * 64.0;
  tmp_i7 = *(int *)(tmp_i1 + 0xbc);
  local_7c = local_7c * 75.0;
  tmp_u6 = rand();
  local_6c = 0xc1200000;
  local_68 = 0xc1200000;
  local_64 = 0;
  local_60 = 0x41200000;
  local_5c = 0x41200000;
  local_58 = 0x41a00000;
  local_7c = ((float)(tmp_u6 & 0x7fff) / 32767.0) * 35.0 + 50.0 + local_7c;
  local_78 = tmp_f3 * 64.0 + *(float *)(tmp_i1 + 0x14);
  local_74 = tmp_f4 * 64.0 + *(float *)(tmp_i1 + 0x18);
  local_70 = (float)tmp_i7 * 0.5 + tmp_f2 + *(float *)(tmp_i1 + 0x1c);
  trap_Trace(local_54,tmp_i1 + 0x14,&local_6c,&local_60,&local_78,*param_1,1);
  local_78 = local_48;
  local_74 = (float)local_44;
  local_70 = (float)local_40;
  tmp_i5 = LaunchItem(tmp_i5,&local_78,&local_84,*(uint32_t *)(tmp_i1 + 0xa0),0x1000);
  if ((0x32 < param_2 - 1U) ||
     (tmp_i7 = *(int *)(weapAlts + param_2 * 4), *(int *)(weapAlts + param_2 * 4) == 0)) {
    tmp_i7 = param_2;
  }
  COM_BitClear(tmp_i1 + 0x3d4,tmp_i7);
  COM_BitClear(tmp_i1 + 0x3d4,param_2);
  G_AddEvent(param_1,0x1a,0);
  if (*(int *)(tmp_i1 + 0xa4) == param_2) {
    *(uint32_t *)(tmp_i1 + 0xa4) = 0;
  }
  if (param_2 == 0x21) {
    tmp_i7 = BG_FindAmmoForWeapon(0x21);
    tmp_i7 = *(int *)(tmp_i1 + (tmp_i7 + 100) * 4);
    tmp_i9 = BG_FindClipForWeapon(0x21);
    *(int *)(tmp_i5 + 0x2e4) = tmp_i7 + *(int *)(tmp_i1 + (tmp_i9 + 0xa4) * 4);
  }
  else {
    tmp_i7 = BG_FindClipForWeapon(param_2);
    *(uint32_t *)(tmp_i5 + 0x2e4) = *(uint32_t *)(tmp_i1 + (tmp_i7 + 0xa4) * 4);
    tmp_i7 = BG_FindAmmoForWeapon(param_2);
    *(uint32_t *)(tmp_i5 + 0x39c) = *(uint32_t *)(tmp_i1 + (tmp_i7 + 100) * 4);
    if (param_2 - 0x16U < 2) {
      tmp_i7 = BG_FindAmmoForWeapon(*(uint32_t *)(weapAlts + param_2 * 4));
      *(float *)(tmp_i5 + 0x318) = (float)*(int *)(tmp_i1 + (tmp_i7 + 100) * 4);
      goto LAB_00082f23;
    }
  }
  *(uint32_t *)(tmp_i5 + 0x318) = 0;
LAB_00082f23:
  *(uint32_t *)(tmp_i5 + 0x108) = *(uint32_t *)(param_1[100] + 3000);
  tmp_i5 = *(int *)(tmp_i5 + 0x33c);
  tmp_i7 = BG_FindClipForWeapon(param_2);
  *(uint32_t *)(tmp_i5 + 0x20) = *(uint32_t *)(tmp_i1 + (tmp_i7 + 0xa4) * 4);
  tmp_i5 = BG_FindClipForWeapon(param_2);
  *(uint32_t *)(tmp_i1 + 0x290 + tmp_i5 * 4) = 0;
  tmp_u8 = Bot_WeaponGameToBot(param_2);
  Bot_Event_RemoveWeapon(*(uint32_t *)(tmp_i1 + 0xa0),tmp_u8);
  return;
}

uint32_t Pickup_Weapon(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  int local_2c;
  
  tmp_i1 = *(int *)(*(int *)(param_1 + 0x33c) + 0x28);
  if (tmp_i1 == 0xc) {
    tmp_i1 = *(int *)(param_2 + 400);
    BG_AddMagicAmmo(tmp_i1,tmp_i1 + 0xed0,*(uint32_t *)(tmp_i1 + 3000),
                    *(uint32_t *)(param_1 + 0x2e4));
    tmp_i1 = *(int *)(param_1 + 0x218);
    if ((tmp_i1 != 0) && (*(int *)(tmp_i1 + 400) != 0)) {
      *(uint32_t *)(*(int *)(param_2 + 400) + 0x9dc) = *(uint32_t *)(tmp_i1 + 0xac);
    }
    tmp_i1 = IsClass(param_2,3);
    if (tmp_i1 != 0) {
      return 0xffffffff;
    }
    tmp_i1 = *(int *)(param_1 + 0x218);
    if (tmp_i1 == 0) {
      return 0xffffffff;
    }
    tmp_i4 = *(int *)(tmp_i1 + 400);
    if (tmp_i4 == 0) {
      return 0xffffffff;
    }
    if (*(int *)(*(int *)(param_2 + 400) + 3000) != *(int *)(tmp_i4 + 3000)) {
      return 0xffffffff;
    }
    if ((g_misc[0xc] & 8) == 0) {
      local_2c = *(int *)(tmp_i4 + 0xff8);
      if (local_2c == (local_2c / 3) * 3) {
        AddScore(tmp_i1,1);
        tmp_i1 = *(int *)(param_1 + 0x218);
        if (tmp_i1 == 0) {
          local_2c = *(int *)(_DAT_00000190 + 0xff8);
          tmp_i4 = _DAT_00000190;
        }
        else if (*(int *)(tmp_i1 + 400) == 0) {
          local_2c = _DAT_00000ff8;
          tmp_i4 = 0;
        }
        else {
          G_LogPrintf("Ammo_Pack: %d %d\n",(tmp_i1 + -0x93e4a0 >> 9) * -0x55555555,
                      (param_2 + -0x93e4a0 >> 9) * -0x55555555);
          tmp_i4 = *(int *)(*(int *)(param_1 + 0x218) + 400);
          local_2c = *(int *)(tmp_i4 + 0xff8);
        }
      }
      *(int *)(tmp_i4 + 0xff8) = local_2c + 1;
      G_AddSkillPoints(*(uint32_t *)(param_1 + 0x218),3,0x3f800000);
      if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
        G_DebugAddSkillPoints(*(uint32_t *)(param_1 + 0x218),3,0x3f800000,"ammo pack picked up");
      }
      tmp_i4 = *(int *)(*(int *)(param_1 + 0x218) + 400);
    }
    *(int *)(tmp_i4 + 0xba4) = *(int *)(tmp_i4 + 0xba4) + 1;
    if (*(int *)(param_1 + 0x218) == 0) {
      return 0xffffffff;
    }
    Bot_Event_RecievedAmmo((param_2 + -0x93e4a0 >> 9) * -0x55555555,*(int *)(param_1 + 0x218));
    return 0xffffffff;
  }
  tmp_i4 = *(int *)(param_1 + 0x2e4);
  tmp_i5 = 0;
  if ((GHIDRA_FIELD(g_weaponItems, 12, 4) & 4) != 0) {
    tmp_i5 = *(int *)(param_1 + 0x39c);
  }
  if (tmp_i1 == 1) {
    if (7 < *(int *)(*(int *)(param_2 + 400) + 0x294)) {
      return 0;
    }
    Add_Ammo(param_2,1,1,0);
    return 0xffffffff;
  }
  tmp_i1 = COM_BitCheck(*(int *)(param_2 + 400) + 0x3d4,tmp_i1);
  if (tmp_i1 != 0) {
    tmp_i1 = 0;
    if ((tmp_i4 != 0) && (tmp_i3 = *(int *)(*(int *)(param_1 + 0x33c) + 0x28), 1 < tmp_i3 - 0x17U)) {
      tmp_i1 = Add_Ammo(param_2,tmp_i3,tmp_i4,0);
    }
    if (tmp_i5 != 0) {
      tmp_i4 = Add_Ammo(param_2,*(uint32_t *)(*(int *)(param_1 + 0x33c) + 0x28),tmp_i5,0);
      tmp_i1 = tmp_i1 + tmp_i4;
    }
    if (*(float *)(param_1 + 0x318) != 0.0) {
      tmp_i4 = Add_Ammo(param_2,*(uint32_t *)
                                (weapAlts + *(int *)(*(int *)(param_1 + 0x33c) + 0x28) * 4),
                       (int)ROUND(*(float *)(param_1 + 0x318)),0);
      tmp_i1 = tmp_i1 + tmp_i4;
    }
    if ((tmp_i1 == 0) && ((GHIDRA_FIELD(g_weaponItems, 12, 4) & 0x10) != 0)) {
      return 0;
    }
    tmp_i1 = *(int *)(*(int *)(param_1 + 0x33c) + 0x28);
    if (((GHIDRA_FIELD(g_weaponItems, 12, 4) & 8) != 0) && (tmp_i1 != 0x13)) {
      if ((*(int *)(param_1 + 0x2e4) != 0) ||
         ((*(int *)(param_1 + 0x39c) != 0 || (*(float *)(param_1 + 0x318) != 0.0)))) {
        tmp_u2 = 0x16;
        if (*(int *)(param_1 + 0x308) != 0) {
          G_AddEvent(param_2,0x28,*(int *)(param_1 + 0x308));
          tmp_u2 = 0x17;
        }
        G_AddEvent(param_2,tmp_u2,*(uint32_t *)(param_1 + 0xa4));
      }
      *(uint32_t *)(param_1 + 0x318) = 0;
      *(uint32_t *)(param_1 + 0x39c) = 0;
      *(uint32_t *)(param_1 + 0x2e4) = 0;
      return 0;
    }
    goto LAB_00083630;
  }
  if (g_unk_00abe908 - *(int *)(*(int *)(param_2 + 400) + 0xfe8) < 1000) {
    return 0;
  }
  if ((*(uint *)(*(int *)(param_2 + 400) + 0xa4) & 0xfffffffb) == 0x2a) {
    return 0;
  }
  tmp_i1 = G_CanPickupWeapon(*(uint32_t *)(*(int *)(param_1 + 0x33c) + 0x28),param_2);
  if (tmp_i1 == 0) {
    return 0;
  }
  tmp_i1 = *(int *)(param_2 + 400);
  if (*(int *)(tmp_i1 + 3000) != 3) {
    tmp_i1 = tmp_i1 + 0x3d4;
    tmp_i3 = COM_BitCheck(tmp_i1,5);
    tmp_u2 = 5;
    if (tmp_i3 == 0) {
      tmp_i3 = COM_BitCheck(tmp_i1,0x1d);
      tmp_u2 = 0x1d;
      if (tmp_i3 != 0) goto LAB_00083291;
      tmp_i3 = COM_BitCheck(tmp_i1,0x21);
      tmp_u2 = 0x21;
      if (tmp_i3 != 0) goto LAB_00083291;
      tmp_i3 = COM_BitCheck(tmp_i1,6);
      tmp_u2 = 6;
      if (tmp_i3 != 0) goto LAB_00083291;
      tmp_i3 = COM_BitCheck(tmp_i1,0x1e);
      tmp_u2 = 0x1e;
      if (tmp_i3 != 0) goto LAB_00083291;
      tmp_i3 = COM_BitCheck(tmp_i1,0x18);
      tmp_u2 = 0x18;
      if (tmp_i3 != 0) goto LAB_00083291;
      tmp_i3 = COM_BitCheck(tmp_i1,0x17);
      tmp_u2 = 0x17;
      if (tmp_i3 != 0) goto LAB_00083291;
      tmp_i3 = COM_BitCheck(tmp_i1,0x16);
      tmp_u2 = 0x16;
      if (tmp_i3 != 0) goto LAB_00083291;
      tmp_i3 = COM_BitCheck(tmp_i1,0x1f);
      tmp_u2 = 0x1f;
      if (tmp_i3 != 0) goto LAB_00083291;
      tmp_i3 = COM_BitCheck(tmp_i1,10);
      tmp_u2 = 10;
      if (tmp_i3 != 0) goto LAB_00083291;
      tmp_i3 = COM_BitCheck(tmp_i1,3);
      tmp_u2 = 3;
      if (tmp_i3 != 0) goto LAB_00083291;
      tmp_i1 = COM_BitCheck(tmp_i1,8);
      if (tmp_i1 != 0) {
        tmp_u2 = 8;
        goto LAB_00083291;
      }
    }
    else {
LAB_00083291:
      if (*(int *)(*(int *)(param_1 + 0x33c) + 0x28) != 0x13) {
        G_DropWeapon(param_2,tmp_u2);
        tmp_i1 = *(int *)(param_2 + 400);
        goto LAB_000832bb;
      }
    }
    tmp_i1 = *(int *)(param_2 + 400);
  }
LAB_000832bb:
  *(int *)(tmp_i1 + 0xfe8) = g_unk_00abe908;
  tmp_i1 = *(int *)(param_2 + 400);
  if (*(int *)(tmp_i1 + 0xa4) - 0x24U < 2) {
    *(uint32_t *)(tmp_i1 + 0xa4) = 0;
    tmp_i1 = *(int *)(param_2 + 400);
  }
  COM_BitSet(tmp_i1 + 0x3d4,*(uint32_t *)(*(int *)(param_1 + 0x33c) + 0x28));
  tmp_i1 = *(int *)(param_1 + 0x33c);
  switch(*(uint32_t *)(tmp_i1 + 0x28)) {
  case 0x16:
    tmp_i1 = G_IsWeaponDisabled(param_2,0x24,1,0);
    if (tmp_i1 == 0) {
      tmp_u2 = 0x24;
      break;
    }
    goto LAB_00083529;
  case 0x17:
    tmp_i1 = G_IsWeaponDisabled(param_2,0x25,1,0);
    if (tmp_i1 != 0) goto LAB_00083529;
    tmp_u2 = 0x25;
    break;
  case 0x18:
    tmp_u2 = 0x27;
    break;
  default:
    goto _L346;
  case 0x1d:
    tmp_u2 = 0x2e;
    break;
  case 0x1e:
    tmp_u2 = 0x28;
    break;
  case 0x1f:
    tmp_u2 = 0x29;
    break;
  case 0x21:
    tmp_u2 = 0x2a;
  }
  COM_BitSet(*(int *)(param_2 + 400) + 0x3d4,tmp_u2);
LAB_00083529:
  tmp_i1 = *(int *)(param_1 + 0x33c);
_L346:
  tmp_i3 = *(int *)(param_2 + 400);
  tmp_i1 = BG_FindClipForWeapon(*(uint32_t *)(tmp_i1 + 0x28));
  *(uint32_t *)(tmp_i3 + 0x290 + tmp_i1 * 4) = 0;
  tmp_i1 = *(int *)(param_2 + 400);
  tmp_i3 = BG_FindAmmoForWeapon(*(uint32_t *)(*(int *)(param_1 + 0x33c) + 0x28));
  *(uint32_t *)(tmp_i1 + 400 + tmp_i3 * 4) = 0;
  tmp_i1 = *(int *)(*(int *)(param_1 + 0x33c) + 0x28);
  if (tmp_i1 == 0x21) {
    tmp_i1 = *(int *)(param_2 + 400);
    tmp_i5 = BG_FindClipForWeapon(0x21);
    *(int *)(tmp_i1 + 400 + tmp_i5 * 4) = tmp_i4;
    if (*(float *)(param_1 + 0x318) != 0.0) {
      Add_Ammo(param_2,*(uint32_t *)(weapAlts + *(int *)(*(int *)(param_1 + 0x33c) + 0x28) * 4),
               (int)ROUND(*(float *)(param_1 + 0x318)),0);
      tmp_i1 = *(int *)(*(int *)(param_1 + 0x33c) + 0x28);
      goto LAB_00083630;
    }
  }
  else {
    tmp_i3 = *(int *)(param_2 + 400);
    tmp_i1 = BG_FindClipForWeapon(tmp_i1);
    *(int *)(tmp_i3 + 0x290 + tmp_i1 * 4) = tmp_i4;
    tmp_i1 = *(int *)(param_2 + 400);
    tmp_i4 = BG_FindAmmoForWeapon(*(uint32_t *)(*(int *)(param_1 + 0x33c) + 0x28));
    *(int *)(tmp_i1 + 400 + tmp_i4 * 4) = tmp_i5;
    if (*(float *)(param_1 + 0x318) != 0.0) {
      *(int *)(*(int *)(param_2 + 400) + 400 +
              *(int *)(weapAlts + *(int *)(*(int *)(param_1 + 0x33c) + 0x28) * 4) * 4) =
           (int)ROUND(*(float *)(param_1 + 0x318));
    }
  }
  tmp_i1 = *(int *)(*(int *)(param_1 + 0x33c) + 0x28);
LAB_00083630:
  tmp_u2 = Bot_WeaponGameToBot(tmp_i1);
  Bot_Event_AddWeapon(*(uint32_t *)(*(int *)(param_2 + 400) + 0xa0),tmp_u2);
  return 0xffffffff;
}

bool G_EmplacedGunIsMountable(int param_1,int param_2)
{
  float tmp_f1;
  int tmp_i2;
  bool tmp_b3;
  
  if ((((((*(int *)(param_1 + 0x5c0) != 0x1908e) || (*(int *)(param_2 + 400) == 0)) ||
        (tmp_i2 = BG_IsScopedWeapon(*(uint32_t *)(*(int *)(param_2 + 400) + 0xa4)), tmp_i2 != 0)) ||
       ((tmp_i2 = *(int *)(param_2 + 400), (*(byte *)(tmp_i2 + 0xc) & 1) != 0 ||
        (*(int *)(tmp_i2 + 0x140) != 0)))) ||
      ((tmp_f1 = *(float *)(param_1 + 0x170) - *(float *)(param_2 + 0x170), 40.0 <= tmp_f1 ||
       ((tmp_f1 < 0.0 || (*(int *)(param_1 + 0xb0) != 0)))))) ||
     ((*(int *)(param_1 + 0x368) != 0 || (*(int *)(tmp_i2 + 0x34) != 0)))) {
    tmp_b3 = false;
  }
  else {
    tmp_i2 = infront(param_1,param_2);
    tmp_b3 = tmp_i2 == 0;
  }
  return tmp_b3;
}

bool G_EmplacedGunIsRepairable(int param_1,int param_2)
{
  int tmp_i1;
  
  if ((*(int *)(param_1 + 0x5c0) == 0x1908e) && (*(int *)(param_2 + 400) != 0)) {
    tmp_i1 = BG_IsScopedWeapon(*(uint32_t *)(*(int *)(param_2 + 400) + 0xa4));
    if ((tmp_i1 == 0) && (*(int *)(*(int *)(param_2 + 400) + 0x140) == 0)) {
      return *(int *)(param_1 + 0xb0) != 0;
    }
  }
  return false;
}

uint32_t G_weapStatIndex_MOD(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = 0;
  do {
    if ((&aWeapMOD)[tmp_i1 * 2] == param_1) {
      return (&g_unk_0024c044)[tmp_i1 * 2];
    }
    tmp_i1 = tmp_i1 + 1;
  } while (tmp_i1 != 0x45);
  return 0x1a;
}

void Nit_WeapDie(int param_1)
{
  *(uint32_t *)(param_1 + 0x2a0) = 0;
  *(uint32_t *)(param_1 + 0x14c) = 0x2000000;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 1;
  *(void **)(param_1 + 0x2a4) = G_ExplodeMissile;
  return;
}

void G_ExplodeMissile(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  uint local_1060;
  uint32_t local_104c;
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
  
  if ((*(int *)(param_1 + 0xe8) == 0x15) && (*(int *)(param_1 + 0x368) != 0)) {
    (&g_unk_02aa2ec8)[*(int *)(param_1 + 0x108)] = (&g_unk_02aa2ec8)[*(int *)(param_1 + 0x108)] + -1;
  }
  tmp_i4 = *(int *)(param_1 + 4);
  *(uint32_t *)(param_1 + 4) = 0;
  if (*(int *)(param_1 + 0x2d4) == 0) goto LAB_00099521;
  local_1028 = *(float *)(param_1 + 0x168);
  local_1024 = *(float *)(param_1 + 0x16c);
  local_1020 = *(float *)(param_1 + 0x170);
  if (*(int *)(param_1 + 0xe8) == 0xf) {
    local_1020 = local_1020 + 4.0;
  }
  trap_Trace(local_101c,&local_1028,&vec3_origin,&vec3_origin,&local_1028,0x3ff,0x6000001);
  if (*(int *)(param_1 + 0xe8) == 0xf) {
    if ((*(byte *)(param_1 + 0x4fc) & 1) == 0) goto LAB_0009970d;
  }
  else if (*(int *)(param_1 + 0xe8) != 0x1a) {
LAB_0009970d:
    G_RadiusDamage(&local_1028,param_1,*(uint32_t *)(param_1 + 0x218),
                   (float)*(int *)(param_1 + 0x2d4),(float)*(int *)(param_1 + 0x2d8),param_1,
                   *(uint32_t *)(param_1 + 0x2e0));
    goto LAB_00099521;
  }
  etpro_RadiusDamage(&local_1028,param_1,*(uint32_t *)(param_1 + 0x218),
                     (float)*(int *)(param_1 + 0x2d4),(float)*(int *)(param_1 + 0x2d8),param_1,
                     *(uint32_t *)(param_1 + 0x2e0),1);
  G_TempTraceIgnorePlayersAndBodies();
  etpro_RadiusDamage(&local_1028,param_1,*(uint32_t *)(param_1 + 0x218),
                     (float)*(int *)(param_1 + 0x2d4),(float)*(int *)(param_1 + 0x2d8),param_1,
                     *(uint32_t *)(param_1 + 0x2e0),0);
  G_ResetTempTraceIgnoreEnts();
LAB_00099521:
  BG_EvaluateTrajectory(param_1 + 0xc,g_unk_00abe908,&local_1040,0,*(uint32_t *)(param_1 + 0x110));
  local_1040 = (float)(int)ROUND(local_1040);
  local_103c = (float)(int)ROUND(local_103c);
  local_1038 = (float)(int)ROUND(local_1038);
  G_SetOrigin(param_1,&local_1040);
  local_1048 = 0;
  local_104c = 0;
  local_1044 = 0x3f800000;
  tmp_f1 = *(float *)(param_1 + 0x3fc);
  if (tmp_f1 == 1.0) {
    tmp_u3 = DirToByte(&local_104c);
    G_AddEvent(param_1,0x46,tmp_u3);
  }
  else if (tmp_f1 == 2.0) {
    tmp_u3 = DirToByte(&local_104c);
    G_AddEvent(param_1,0x47,tmp_u3);
  }
  else {
    if (tmp_f1 == 3.0) {
      *(uint32_t *)(param_1 + 0x1c4) = 1;
      trap_LinkEntity(param_1);
      return;
    }
    tmp_u3 = DirToByte(&local_104c);
    G_AddEvent(param_1,0x31,tmp_u3);
    *(uint32_t *)(param_1 + 0xac) = *(uint32_t *)(param_1 + 0x180);
  }
  *(uint32_t *)(param_1 + 0x1c4) = 1;
  trap_LinkEntity(param_1);
  if (tmp_i4 != 0x22) {
    if (tmp_i4 != 3) {
      return;
    }
    tmp_u3 = *(uint32_t *)(param_1 + 0xe8);
    switch(tmp_u3) {
    case 0xf:
      if ((*(byte *)(param_1 + 0x4fc) & 1) == 0) {
_L29:
        tmp_i4 = nitrox_TempEventFromQueue(param_1 + 0x168,0x56);
        *(int *)(tmp_i4 + 0xfc) = *(int *)(param_1 + 0x2d4) << 2;
        *(uint *)(tmp_i4 + 0x128) = *(uint *)(tmp_i4 + 0x128) | 0x20;
        return;
      }
      local_1034 = *(float *)(param_1 + 0x168) + *(float *)(param_1 + 0x134);
      *(uint32_t *)(param_1 + 0x2a0) = 0;
      local_1030 = *(float *)(param_1 + 0x16c) + *(float *)(param_1 + 0x138);
      local_102c = *(float *)(param_1 + 0x170) + *(float *)(param_1 + 0x13c);
      local_1028 = *(float *)(param_1 + 0x168) + *(float *)(param_1 + 0x140);
      local_1024 = *(float *)(param_1 + 0x16c) + *(float *)(param_1 + 0x144);
      local_1020 = *(float *)(param_1 + 0x170) + *(float *)(param_1 + 0x148);
      tmp_i4 = trap_EntitiesInBox(&local_1034,&local_1028,local_101c,0x400);
      if (0 < tmp_i4) {
        tmp_i8 = 0;
        do {
          tmp_i2 = local_101c[tmp_i8];
          tmp_i5 = tmp_i2 * 0x600;
          if (((((*(int *)(g_entities + tmp_i5 + 0x254) != 0) &&
                (*(int *)(g_entities + tmp_i5 + 4) == 0xc)) &&
               (local_1060 = *(uint *)(g_entities + tmp_i5 + 0x1a8), (local_1060 & 3) != 0)) &&
              ((tmp_i5 = *(int *)(g_entities + tmp_i5 + 0x264), tmp_i5 == 0 ||
               ((*(int *)(tmp_i5 + 4) == 0xe && (0 < *(int *)(tmp_i5 + 0x4f4))))))) &&
             ((((local_1060 & 1) != 0 && (*(int *)(param_1 + 0x108) == 2)) ||
              (((local_1060 & 2) != 0 && (*(int *)(param_1 + 0x108) == 1)))))) {
            tmp_i5 = *(int *)(param_1 + 0x218);
            if (*(int *)(tmp_i5 + 400) != 0) {
              tmp_i5 = G_GetWeaponClassForMOD(0x15);
              tmp_i6 = tmp_i2 * 0x600;
              if (tmp_i5 < *(int *)(*(int *)(g_entities + tmp_i6 + 0x264) + 0x4f4)) {
                local_1060 = *(uint *)(g_entities + tmp_i6 + 0x1a8);
                tmp_i5 = *(int *)(param_1 + 0x218);
              }
              else {
                G_AddKillSkillPointsForDestruction
                          (*(uint32_t *)(param_1 + 0x218),0x15,
                           *(int *)(g_entities + tmp_i6 + 0x264) + 0x4e4);
                local_1060 = *(uint *)(g_entities + tmp_i6 + 0x1a8);
                tmp_i5 = *(int *)(param_1 + 0x218);
              }
            }
            tmp_pu7 = g_entities + tmp_i2 * 0x600;
            if ((local_1060 & 8) == 0) {
              nitmod_objective(4,3,tmp_pu7,tmp_i5,0x15);
            }
            else {
              nitmod_objective(4,4,tmp_pu7,tmp_i5,0x15);
            }
            G_UseTargets(tmp_pu7,param_1);
            *(void **)(g_entities + tmp_i2 * 0x600 + 0x2a4) = G_FreeEntity;
            *(int *)(g_entities + tmp_i2 * 0x600 + 0x29c) = g_unk_00abe908 + 100;
            G_Script_ScriptEvent(tmp_pu7,"destroyed",&g_unk_0026ea14);
          }
          tmp_i8 = tmp_i8 + 1;
        } while (tmp_i8 != tmp_i4);
      }
      tmp_u3 = *(uint32_t *)(param_1 + 0xe8);
      break;
    case 0x15:
      nitrox_RemoveEntityFromEntityArray(&AirstrikeEntities,param_1);
      tmp_u3 = *(uint32_t *)(param_1 + 0xe8);
      break;
    case 0x19:
    case 0x33:
      tmp_i8 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
      tmp_i4 = G_FindMapEntityData(mapEntityData,tmp_i8);
      if (tmp_i4 != 0) {
        G_FreeMapEntityData(mapEntityData,tmp_i4);
      }
      tmp_i4 = G_FindMapEntityData(0x2d8ca94,tmp_i8);
      if (tmp_i4 != 0) {
        G_FreeMapEntityData(0x2d8ca94,tmp_i4);
      }
      nitrox_RemoveEntityFromEntityArray(&LandmineEntities,param_1);
      tmp_u3 = *(uint32_t *)(param_1 + 0xe8);
      break;
    case 0x1a:
      nitrox_RemoveEntityFromEntityArray(&SatchelEntities,param_1);
      tmp_u3 = *(uint32_t *)(param_1 + 0xe8);
    }
    switch(tmp_u3) {
    case 4:
    case 5:
    case 9:
    case 0xd:
    case 0xf:
    case 0x15:
    case 0x19:
    case 0x1a:
    case 0x30:
    case 0x31:
      goto _L29;
    default:
      return;
    }
  }
  nitrox_RemoveEntityFromEntityArray(&TripmineEntities,param_1);
  return;
}

void G_FreeSatchel(int param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  
  *(uint32_t *)(param_1 + 0x2a0) = 0;
  if (*(int *)(param_1 + 4) == 3) {
    tmp_pi2 = (int *)(g_entities + *(int *)(param_1 + 0xac) * 0x600 + 400);
    tmp_i1 = *tmp_pi2;
    if (((tmp_i1 != 0) && (*(int *)(tmp_i1 + 0x5ac) == 2)) && (*(int *)(tmp_i1 + 0xbc8) == 4)) {
      *(uint32_t *)(tmp_i1 + 0x1fc) = 0;
      *(uint32_t *)(*tmp_pi2 + 0x2fc) = 0;
      *(uint32_t *)(*tmp_pi2 + 0x2f8) = 1;
      return;
    }
  }
  return;
}

void Nit_SatchelDie(int param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  
  if (*(int *)(param_1 + 4) == 3) {
    *(uint32_t *)(param_1 + 0x2a0) = 0;
    *(uint32_t *)(param_1 + 0x14c) = 0x2000000;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 1;
    *(void **)(param_1 + 0x2a4) = G_ExplodeMissile;
    tmp_i2 = *(int *)(param_1 + 0xac) * 0x600;
    tmp_pi1 = (int *)(g_entities + tmp_i2 + 400);
    *(uint32_t *)(*tmp_pi1 + 0x1fc) = 0;
    *(uint32_t *)(*tmp_pi1 + 0x2fc) = 0;
    *(uint32_t *)(*tmp_pi1 + 0x2f8) = 1;
    if (*(int *)(*tmp_pi1 + 0xa4) == 0x1b) {
      G_AddEvent(g_entities + tmp_i2,0x19,0);
    }
  }
  return;
}

void G_TripMineThink(uint32_t *param_1)
{
  int tmp_i1;
  int tmp_i2;
  long double tmp_l3;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [52];
  int local_20;
  
  param_1[0x43] = 2;
  local_6c = (float)param_1[0x1a] * 0.0 + (float)param_1[0x5a];
  local_68 = (float)param_1[0x1b] * 0.0 + (float)param_1[0x5b];
  param_1[0xa7] = g_unk_00abe908 + 100;
  local_64 = (float)param_1[0x1c] * 0.0 + (float)param_1[0x5c];
  local_60 = (float)param_1[0x1a] * 2048.0 + local_6c;
  local_5c = (float)param_1[0x1b] * 2048.0 + local_68;
  local_58 = (float)param_1[0x1c] * 2048.0 + local_64;
  tmp_l3 = (long double)DistanceSquared(&local_6c,&local_60);
  if ((tmp_l3 < (long double)10000.0) || (tmp_i1 = CheckForSmoke_part_4(), tmp_i1 == 0)) {
    G_Trace(param_1,local_54,&local_6c,0,0,&local_60,*param_1,0x6000001,1,1);
    tmp_i1 = local_20 * 0x600;
    if (*(int *)(g_entities + tmp_i1 + 400) == 0) {
      if (((param_1[0x17b] == -1) && (*(int *)(g_entities + tmp_i1 + 0x5c0) != 0x1cce6)) &&
         (*(int *)(g_entities + tmp_i1 + 0x5c0) != 0x3bf8a)) {
        return;
      }
    }
    else {
      if (((param_1[0x86] != 0) && ((g_friendlyFire[0xc] & 0x80) != 0)) &&
         ((tmp_i2 = G_LandmineTeam(param_1),
          tmp_i2 == *(int *)(*(int *)(g_entities + tmp_i1 + 400) + 3000) &&
          (*(int *)(g_entities + tmp_i1 + 0xac) != *(int *)(param_1[0x86] + 0xac))))) {
        return;
      }
      if ((((g_OmniBotFlags[0xc] & 0x20) == 0) && ((g_entities[local_20 * 0x600 + 0x128] & 8) != 0))
         && (tmp_i1 = G_LandmineTeam(param_1),
            tmp_i1 == *(int *)(*(int *)(g_entities + local_20 * 0x600 + 400) + 3000))) {
        return;
      }
    }
    param_1[0xa9] = G_ExplodeMissile;
  }
  return;
}

void G_LandmineThink(int param_1)
{
  int tmp_i1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  long double tmp_l7;
  float local_1040;
  float local_103c;
  float local_1038;
  float local_1034;
  float local_1030;
  float local_102c;
  float local_1028;
  float local_1024;
  float local_1020;
  int local_101c [1026];
  uint32_t uStack_14;
  
  uStack_14 = 0x9ab89;
  tmp_i3 = g_unk_00abe908 - *(int *)(param_1 + 0x378);
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  if (200 < tmp_i3) {
    *(uint32_t *)(param_1 + 0xf4) = 0;
  }
  local_1040 = *(float *)(param_1 + 0x168) - 64.0;
  local_103c = *(float *)(param_1 + 0x16c) - 64.0;
  local_1038 = *(float *)(param_1 + 0x170) - 64.0;
  local_1034 = *(float *)(param_1 + 0x168) + 64.0;
  local_1030 = *(float *)(param_1 + 0x16c) + 64.0;
  local_102c = *(float *)(param_1 + 0x170) + 64.0;
  tmp_i3 = trap_EntitiesInBox(&local_1040,&local_1034,local_101c,0x400);
  if (0 < tmp_i3) {
    tmp_i6 = 0;
    do {
      while( true ) {
        tmp_i1 = local_101c[tmp_i6];
        if (*(int *)(g_entities + tmp_i1 * 0x600 + 400) != 0) break;
LAB_0009acd0:
        tmp_i6 = tmp_i6 + 1;
        if (tmp_i6 == tmp_i3) {
          return;
        }
      }
      tmp_i4 = *(int *)(param_1 + 0x218);
      if (tmp_i4 != 0) {
        if ((GHIDRA_FIELD(g_friendlyFire, 12, 4) & 0x20) != 0) {
          tmp_i5 = G_LandmineTeam(param_1);
          tmp_i4 = *(int *)(param_1 + 0x218);
          if (tmp_i5 == *(int *)(*(int *)(g_entities + tmp_i1 * 0x600 + 400) + 3000)) {
            if (*(int *)(g_entities + tmp_i1 * 0x600 + 0xac) != *(int *)(tmp_i4 + 0xac))
            goto LAB_0009acd0;
          }
          else if (tmp_i4 == 0) goto LAB_0009ac81;
        }
        if ((((GHIDRA_FIELD(g_friendlyFire, 12, 4) & 0x100) != 0) &&
            (*(int *)(g_entities + tmp_i1 * 0x600 + 0xac) == *(int *)(tmp_i4 + 0xac))) &&
           (*(int *)(g_entities + tmp_i1 * 0x600 + 0xe8) != 0x14)) goto LAB_0009acd0;
      }
LAB_0009ac81:
      if (((g_OmniBotFlags[0xc] & 0x20) != 0) || ((g_entities[tmp_i1 * 0x600 + 0x128] & 8) == 0)) {
LAB_0009aca1:
        tmp_i4 = tmp_i1 * 0x600;
        if ((*(int *)(g_entities + tmp_i4 + 4) == 1) && (*(int *)(g_entities + tmp_i4 + 400) != 0)) {
          if ((GHIDRA_FIELD(n_preciseLandmineTrigger, 12, 4) == 0) ||
             ((*(int *)(param_1 + 0xfc) != 0 ||
              ((*(uint *)(*(int *)(g_entities + tmp_i4 + 400) + 0x68) & 0x880001) != 0)))) {
            tmp_i4 = tmp_i1 * 0x600;
            local_1028 = *(float *)(param_1 + 0x168) - *(float *)(g_entities + tmp_i4 + 0x168);
            local_1024 = *(float *)(param_1 + 0x16c) - *(float *)(g_entities + tmp_i4 + 0x16c);
            local_1020 = *(float *)(param_1 + 0x170) - *(float *)(g_entities + tmp_i4 + 0x170);
            tmp_l7 = (long double)VectorLengthSquared(&local_1028);
            tmp_f2 = local_1020;
            if (tmp_l7 <= (long double)4096.0) goto joined_r0x0009aeb7;
          }
          else if (((int)ROUND(((*(float *)(param_1 + 0x16c) - (*(float *)(param_1 + 0x138) + 3.0))
                               - (*(float *)(param_1 + 0x144) - 3.0)) -
                               *(float *)(g_entities + tmp_i4 + 0x16c)) + 0x17U < 0x2f) &&
                  ((int)ROUND(((*(float *)(param_1 + 0x168) - (*(float *)(param_1 + 0x134) + 3.0)) -
                              (*(float *)(param_1 + 0x140) - 3.0)) -
                              *(float *)(g_entities + tmp_i4 + 0x168)) + 0x17U < 0x2f)) {
            tmp_f2 = ((*(float *)(param_1 + 0x170) - *(float *)(param_1 + 0x13c)) -
                    *(float *)(param_1 + 0x148)) - *(float *)(g_entities + tmp_i4 + 0x170);
joined_r0x0009aeb7:
            if (ABS(tmp_f2) < 45.0) {
              Bot_Event_PreTriggerMine((tmp_i1 * 0x600 >> 9) * -0x55555555,param_1);
              *(uint32_t *)(param_1 + 0x14c) = 0x4000000;
              trap_LinkEntity(param_1);
              tmp_i3 = g_unk_00abe908;
              *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
              if (*(int *)(param_1 + 0xe8) == 0x33) {
                *(int *)(param_1 + 0x29c) = tmp_i3 + 1000;
                nitmod_SoundEvent(param_1,0xb);
                *(void **)(param_1 + 0x2a4) = weapon_smokeBombExplode;
                tmp_i3 = g_unk_00abe908;
              }
              else {
                *(void **)(param_1 + 0x2a4) = LandminePostThink;
              }
              *(int *)(param_1 + 0x108) = *(int *)(param_1 + 0x108) + 8;
              *(int *)(param_1 + 0x54) = tmp_i3;
              *(uint32_t *)(param_1 + 0xfc) = 1;
              return;
            }
          }
        }
        goto LAB_0009acd0;
      }
      tmp_i4 = G_LandmineTeam(param_1);
      if (tmp_i4 == *(int *)(*(int *)(g_entities + tmp_i1 * 0x600 + 400) + 3000)) goto LAB_0009acd0;
      tmp_i4 = G_LandmineSpotted(param_1);
      if (tmp_i4 == 0) goto LAB_0009aca1;
      tmp_i6 = tmp_i6 + 1;
    } while (tmp_i6 != tmp_i3);
  }
  return;
}

void G_MissileDie(int param_1,int param_2,int *param_3,uint32_t param_4,uint32_t param_5)
{
  if (param_2 != param_1) {
    if (((param_3 != (int *)0x0) && (param_3[100] != 0)) && (*param_3 != *(int *)(param_1 + 0x180)))
    {
      switch(param_5) {
      case 1:
      case 2:
      case 3:
      case 0x2b:
        G_AddSkillPoints(param_3,5,0x40a00000);
        if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
          G_DebugAddSkillPoints(param_3,5,0x40a00000,"Heavy weapon missile shot");
        }
        break;
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
        G_AddSkillPoints(param_3,4,0x40a00000);
        if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
          G_DebugAddSkillPoints(param_3,4,0x40a00000,"Light weapon missile shot");
        }
        break;
      case 0xe:
      case 0x2d:
      case 0x32:
        G_AddSkillPoints(param_3,6,0x40a00000);
        if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
          G_DebugAddSkillPoints(param_3,6,0x40a00000,"Scoped weapon missile shot");
        }
      }
    }
    *(uint32_t *)(param_1 + 0x2cc) = 0;
    *(void **)(param_1 + 0x2a4) = G_ExplodeMissile;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 10;
  }
  return;
}

void G_MissileImpact(int param_1,int param_2,int param_3)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  int tmp_i6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  uint32_t tmp_u9;
  long double tmp_l10;
  int local_44;
  uint8_t local_34 [8];
  uint32_t local_2c;
  uint8_t local_28 [24];
  
  tmp_i8 = *(int *)(param_2 + 0x34);
  tmp_i6 = tmp_i8 * 0x600;
  tmp_pu1 = g_entities + tmp_i6;
  tmp_i2 = *(int *)(param_1 + 0x180);
  if (((*(int *)(g_entities + tmp_i6 + 0x5c0) == 0x2e686) &&
      (tmp_i3 = *(int *)(g_entities + tmp_i6 + 0x2c8), tmp_i3 <= param_3)) && (tmp_i3 != 0)) {
    if (*(int *)(g_entities + tmp_i6 + 0x2cc) != 0) {
      BG_EvaluateTrajectoryDelta
                (param_1 + 0xc,g_unk_00abe908,local_34,0,*(uint32_t *)(param_1 + 0x110));
      G_Damage(tmp_pu1,param_1,g_entities + tmp_i2 * 0x600,local_34,param_1 + 0x5c,param_3,0,
               *(uint32_t *)(param_1 + 0x2dc));
      if (*(int *)(g_entities + tmp_i6 + 0x2c8) < 1) {
        return;
      }
      goto LAB_0009ba0a;
    }
    if (tmp_i3 < 1) {
      return;
    }
LAB_0009ba1c:
    if ((*(uint *)(param_1 + 8) & 0xc000000) != 0) {
LAB_0009ba83:
      G_BounceMissile(param_1,param_2);
      tmp_i8 = Q_stricmp(*(uint32_t *)(param_1 + 0x1a4),&g_unk_0024c979);
      if (tmp_i8 != 0) {
        tmp_u9 = BG_FootstepForSurface(*(uint32_t *)(param_2 + 0x2c));
        G_AddEvent(param_1,0x27,tmp_u9);
      }
      return;
    }
    if (*(int *)(g_entities + tmp_i8 * 0x600 + 0x490) != 0) {
      if (*(int *)(param_1 + 0x2d0) == 0) {
LAB_0009ba49:
        G_BounceMissile(param_1,param_2);
        return;
      }
      goto LAB_0009bae0;
    }
  }
  else {
LAB_0009ba0a:
    if (*(int *)(g_entities + tmp_i8 * 0x600 + 0x2cc) == 0) goto LAB_0009ba1c;
    if (*(int *)(param_1 + 0x2d0) == 0) {
      if ((*(uint *)(param_1 + 8) & 0xc000000) == 0) goto LAB_0009ba49;
      goto LAB_0009ba83;
    }
LAB_0009bae0:
    BG_EvaluateTrajectoryDelta
              (param_1 + 0xc,g_unk_00abe908,local_34,0,*(uint32_t *)(param_1 + 0x110));
    tmp_l10 = (long double)VectorLengthSquared(local_34);
    if (tmp_l10 == (long double)0) {
      local_2c = 0x3f800000;
    }
    tmp_i8 = tmp_i8 * 0x600;
    tmp_pu7 = *(uint8_t **)(g_entities + tmp_i8 + 0x490);
    if (*(uint8_t **)(g_entities + tmp_i8 + 0x490) == (uint8_t *)0x0) {
      tmp_pu7 = tmp_pu1;
    }
    G_Damage(tmp_pu7,param_1,g_entities + tmp_i2 * 0x600,local_34,param_1 + 0x5c,
             *(uint32_t *)(param_1 + 0x2d0),0,*(uint32_t *)(param_1 + 0x2dc));
    if ((*(int *)(g_entities + tmp_i8 + 0x2cc) != 0) && (*(int *)(g_entities + tmp_i8 + 400) != 0)) {
      tmp_u4 = DirToByte(param_2 + 0x18);
      tmp_u9 = *(uint32_t *)(g_entities + tmp_i8);
      tmp_u5 = 0x30;
      goto LAB_0009bbd2;
    }
  }
  local_44 = param_1 + 0xc;
  BG_EvaluateTrajectoryDelta(local_44,g_unk_00abe908,local_28,0,*(uint32_t *)(param_1 + 0x110));
  BG_GetMarkDir(local_28,param_2 + 0x18,local_28);
  tmp_u9 = 0;
  tmp_u4 = DirToByte(local_28);
  tmp_u5 = 0x31;
LAB_0009bbd2:
  tmp_i8 = nitrox_TempEventFromQueue(param_2 + 0xc,tmp_u5);
  *(uint32_t *)(tmp_i8 + 0x8c) = tmp_u9;
  *(uint32_t *)(tmp_i8 + 0xbc) = tmp_u4;
  *(uint32_t *)(tmp_i8 + 0xe8) = *(uint32_t *)(param_1 + 0xe8);
  *(uint32_t *)(tmp_i8 + 0xac) = *(uint32_t *)(param_1 + 0x180);
  if (*(int *)(param_1 + 0xe8) == 0x2a) {
    tmp_u9 = *(uint32_t *)(param_1 + 0xec);
    *(uint *)(tmp_i8 + 0x128) = *(uint *)(tmp_i8 + 0x128) | 0x20;
    *(uint32_t *)(tmp_i8 + 0xec) = tmp_u9;
  }
  if (*(int *)(param_1 + 0x2d4) != 0) {
    G_RadiusDamage(param_2 + 0xc,param_1,*(uint32_t *)(param_1 + 0x218),
                   (float)*(int *)(param_1 + 0x2d4),(float)*(int *)(param_1 + 0x2d8),tmp_pu1,
                   *(uint32_t *)(param_1 + 0x2e0));
  }
  G_FreeEntity(param_1);
  return;
}

void G_MissileDownXPAward(int param_1,uint32_t param_2)
{
  if (*(int *)(param_1 + 400) != 0) {
    switch(param_2) {
    case 1:
    case 2:
    case 3:
    case 0x2b:
      G_AddSkillPoints(param_1,5,0x40a00000);
      if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
        G_DebugAddSkillPoints(param_1,5,0x40a00000,"Heavy weapon missile shot");
      }
      break;
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
      G_AddSkillPoints(param_1,4,0x40a00000);
      if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
        G_DebugAddSkillPoints(param_1,4,0x40a00000,"Light weapon missile shot");
      }
      break;
    case 0xe:
    case 0x2d:
    case 0x32:
      G_AddSkillPoints(param_1,6,0x40a00000);
      if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
        G_DebugAddSkillPoints(param_1,6,0x40a00000,"Scoped weapon missile shot");
      }
    }
  }
  return;
}

void G_RunMissile(uint32_t *param_1)
{
  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  long double tmp_l6;
  long double tmp_l7;
  float *local_d0;
  uint32_t local_b0;
  uint32_t local_ac;
  uint32_t local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  uint32_t local_80;
  uint32_t local_7c;
  uint32_t local_78;
  uint local_60;
  uint8_t local_54 [8];
  float local_4c;
  
  switch(param_1[0x3a]) {
  case 0xf:
  case 0x19:
  case 0x1a:
  case 0x30:
  case 0x33:
    local_98 = (float)param_1[0x5a];
    local_94 = (float)param_1[0x5b];
    local_90 = (float)param_1[0x5c];
    local_84 = local_90 - 4.0;
    local_b0 = param_1[0x4d];
    local_ac = param_1[0x4e];
    local_a8 = param_1[0x4f];
    local_a4 = (float)param_1[0x50];
    local_a0 = (float)param_1[0x51];
    local_9c = (float)param_1[0x52];
    local_8c = local_98;
    local_88 = local_94;
    trap_Trace(local_54,&local_98,&local_b0,&local_a4,&local_8c,*param_1,0x6000081);
    if (local_4c == 1.0) {
      param_1[0x25] = 0xffffffff;
    }
    else if (param_1[0x25] != -1) break;
    if (param_1[3] != 6) {
      param_1[3] = 6;
      param_1[4] = g_unk_00abe908;
    }
    break;
  default:
  }
  local_d0 = &local_a4;
  BG_EvaluateTrajectory(param_1 + 3,g_unk_00abe908,local_d0,0,param_1[0x44]);
  tmp_u2 = param_1[0x75];
  if ((tmp_u2 & 0x2000000) != 0) {
    switch(param_1[0x3a]) {
    case 4:
    case 9:
    case 0xd:
    case 0xf:
    case 0x15:
    case 0x19:
    case 0x1a:
    case 0x1c:
    case 0x30:
    case 0x32:
    case 0x33:
      if ((((float)param_1[9] == 0.0) && ((float)param_1[10] == 0.0)) &&
         ((float)param_1[0xb] == 0.0)) {
        tmp_u2 = tmp_u2 & 0xfdffffff;
        param_1[0x75] = tmp_u2;
      }
    }
  }
  if (g_unk_02a99b90 != 0) {
    switch(param_1[0x3a]) {
    case 4:
    case 9:
    case 0x24:
    case 0x25:
    case 0x2a:
      if (param_1[0xb9] == 0) {
        if (param_1[0xe7] == 0) {
          tmp_l6 = (long double)BG_GetSkyHeightAtPoint(local_d0);
          tmp_l7 = (long double)BG_GetGroundHeightAtPoint(local_d0);
          if (((long double)512.0 < (long double)(float)tmp_l6 - tmp_l7) &&
             (local_9c - (float)param_1[0x5c] < 0.0)) {
            param_1[0xe7] = 1;
          }
          tmp_u2 = param_1[0x75];
        }
      }
      else {
        if ((((float)param_1[0x5a] < g_unk_02a99b94) || (g_unk_02a99b98 < (float)param_1[0x5b])) ||
           ((g_unk_02a99b9c < (float)param_1[0x5a] || ((float)param_1[0x5b] < g_unk_02a99ba0)))) {
          tmp_i4 = nitrox_TempEventFromQueue(param_1 + 0x5a,0x49);
          tmp_u5 = param_1[0x60];
          *(uint *)(tmp_i4 + 0x128) = *(uint *)(tmp_i4 + 0x128) | 0x20;
          *(uint32_t *)(tmp_i4 + 0xf4) = 1;
          *(uint32_t *)(tmp_i4 + 0xac) = tmp_u5;
          G_FreeEntity(param_1);
          return;
        }
        tmp_l6 = (long double)BG_GetSkyHeightAtPoint(local_d0);
        tmp_f1 = local_9c;
        tmp_i4 = BG_GetTracemapGroundFloor();
        if (tmp_f1 < (float)tmp_i4) {
          tmp_i4 = nitrox_TempEventFromQueue(param_1 + 0x5a,0x49);
          tmp_u5 = param_1[0x60];
          *(uint *)(tmp_i4 + 0x128) = *(uint *)(tmp_i4 + 0x128) | 0x20;
          *(uint32_t *)(tmp_i4 + 0xac) = tmp_u5;
          *(uint32_t *)(tmp_i4 + 0xf4) = 0;
          G_FreeEntity(param_1);
          return;
        }
        if ((float)tmp_l6 == 65536.0) {
          G_RunThink(param_1);
          param_1[0x5a] = local_a4;
          param_1[0x5b] = local_a0;
          param_1[0x5c] = local_9c;
          return;
        }
        if ((float)tmp_l6 <= local_9c) goto LAB_0009c520;
        tmp_u2 = param_1[0x75];
        param_1[0x5a] = local_a4;
        param_1[0xb9] = 0;
        param_1[0x5b] = local_a0;
        param_1[0x5c] = local_9c;
        param_1[0xe7] = 1;
      }
    }
  }
  trap_Trace(&local_8c,param_1 + 0x5a,param_1 + 0x4d,param_1 + 0x50,local_d0,param_1[0x60],tmp_u2);
  tmp_f1 = local_9c;
  if ((((param_1[0x3a] == 0x2a) && (param_1[0xe7] == 1)) && (local_9c < (float)param_1[0x5c])) &&
     (tmp_l6 = (long double)BG_GetGroundHeightAtPoint(local_d0),
     (long double)tmp_f1 - tmp_l6 < (long double)512.0)) {
    local_98 = (local_a4 - (float)param_1[0x5a]) * 8.0 + local_a4;
    local_94 = (local_a0 - (float)param_1[0x5b]) * 8.0 + local_a0;
    local_90 = (local_9c - (float)param_1[0x5c]) * 8.0 + local_9c;
    trap_Trace(local_54,local_d0,param_1 + 0x4d,param_1 + 0x50,&local_98,param_1[0x60],param_1[0x75]
              );
    if (local_4c != 1.0) {
      tmp_l6 = (long double)BG_GetGroundHeightAtPoint(&local_98);
      local_90 = (float)tmp_l6;
      tmp_i4 = nitrox_TempEventFromQueue(&local_98,0x48);
      tmp_u5 = param_1[0x60];
      *(uint *)(tmp_i4 + 0x128) = *(uint *)(tmp_i4 + 0x128) | 0x20;
      *(uint32_t *)(tmp_i4 + 0xac) = tmp_u5;
      param_1[0xe7] = 2;
      param_1[0x3b] = 1;
    }
  }
  param_1[0x5a] = local_80;
  param_1[0x5b] = local_7c;
  param_1[0x5c] = local_78;
  if (local_88 != 0.0) {
    local_84 = 0.0;
  }
  trap_LinkEntity(param_1);
  if (local_84 == 1.0) {
    tmp_l6 = (long double)VectorLengthSquared(param_1 + 9);
    if (tmp_l6 != (long double)0) {
      param_1[0x25] = 0x3ff;
    }
    goto LAB_0009c520;
  }
  if ((g_unk_02a99b90 == 0) || ((local_60 & 4) == 0)) {
    if ((local_60 & 0x10) != 0) {
      G_FreeEntity(param_1);
      return;
    }
    tmp_i4 = param_1[0x3a];
  }
  else {
    tmp_i4 = param_1[0x3a];
    switch(tmp_i4) {
    case 4:
    case 9:
    case 0x24:
    case 0x25:
    case 0x2a:
      param_1[0xb9] = 1;
      trap_UnlinkEntity(param_1);
      G_RunThink(param_1);
      return;
    }
  }
  if ((tmp_i4 == 5) || (tmp_i4 == 0x2a)) {
    tmp_u5 = 999;
    if (0x1a < tmp_i4) goto LAB_0009c68e;
LAB_0009c35f:
    if ((tmp_i4 < 0x19) && (tmp_i4 != 0xf)) goto LAB_0009c697;
LAB_0009c36d:
    if (param_1[3] != 0) goto LAB_0009c697;
  }
  else {
    tmp_u5 = 0x14;
    if (tmp_i4 < 0x1b) goto LAB_0009c35f;
LAB_0009c68e:
    if (tmp_i4 == 0x30) goto LAB_0009c36d;
LAB_0009c697:
    G_MissileImpact(param_1,&local_8c,tmp_u5);
  }
  if (param_1[1] != 3) {
    tmp_i3 = nitrox_TempEventFromQueue(param_1 + 0x5a,0x56);
    tmp_i4 = param_1[0xb5];
    *(uint *)(tmp_i3 + 0x128) = *(uint *)(tmp_i3 + 0x128) | 0x20;
    *(int *)(tmp_i3 + 0xfc) = tmp_i4 << 2;
    return;
  }
LAB_0009c520:
  G_RunThink(param_1);
  return;
}

void G_FlameDamage(int param_1,uint8_t *param_2)
{
  uint8_t *tmp_pu1;
  int *tmp_pi2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint32_t tmp_u7;
  int tmp_i8;
  int tmp_i9;
  long double tmp_l10;
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
  int local_101c [1026];
  uint32_t uStack_14;
  
  uStack_14 = 0x9ccfe;
  local_1070 = *(float *)(param_1 + 0x268) * 1.4142135;
  local_1084 = *(float *)(param_1 + 0x168) - local_1070;
  local_1078 = *(float *)(param_1 + 0x168) + local_1070;
  local_1080 = *(float *)(param_1 + 0x16c) - local_1070;
  local_1074 = *(float *)(param_1 + 0x16c) + local_1070;
  local_107c = *(float *)(param_1 + 0x170) - local_1070;
  local_1070 = *(float *)(param_1 + 0x170) + local_1070;
  tmp_i4 = trap_EntitiesInBox(&local_1084,&local_1078,local_101c,0x400);
  if (0 < tmp_i4) {
    tmp_i9 = 0;
    do {
      while( true ) {
        tmp_i6 = g_unk_00abe908;
        tmp_i8 = local_101c[tmp_i9];
        tmp_i5 = tmp_i8 * 0x600;
        tmp_pu1 = g_entities + tmp_i5;
        if ((tmp_pu1 != param_2) && (*(int *)(g_entities + tmp_i5 + 0x2cc) != 0)) break;
LAB_0009cdd0:
        tmp_i9 = tmp_i9 + 1;
        if (tmp_i9 == tmp_i4) {
          return;
        }
      }
      if (*(int *)(g_entities + tmp_i5 + 400) != 0) {
        if (*(int *)(*(int *)(g_entities + tmp_i5 + 400) + 0x154) < g_unk_00abe908) {
          if ((((g_friendlyFire[0xc] & 1) != 0) || (GHIDRA_FIELD(g_gametype, 12, 4) == 8)) ||
             (tmp_i6 = OnSameTeam(tmp_pu1,*(uint32_t *)(param_1 + 0x218)), tmp_i6 == 0))
          goto LAB_0009ce60;
        }
        else {
          *(uint32_t *)(g_entities + tmp_i5 + 0x390) = 0;
          *(int *)(g_entities + tmp_i5 + 0x100) = tmp_i6 + -1;
        }
        goto LAB_0009cdd0;
      }
LAB_0009ce60:
      tmp_i6 = tmp_i8 * 0x600;
      if (*(int *)(g_entities + tmp_i6 + 0x304) < 3) {
        if (*(int *)(g_entities + tmp_i6 + 0x130) == 0) {
          local_106c = *(float *)(g_entities + tmp_i6 + 0x168);
          local_1068 = *(float *)(g_entities + tmp_i6 + 0x16c);
          local_1064 = *(float *)(g_entities + tmp_i6 + 0x170);
          if (*(int *)(g_entities + tmp_i6 + 400) != 0) {
            local_1064 = (float)*(int *)(*(int *)(g_entities + tmp_i6 + 400) + 0xbc) + local_1064;
          }
          local_1060 = local_106c - *(float *)(param_1 + 0x168);
          local_105c = local_1068 - *(float *)(param_1 + 0x16c);
          local_1058 = local_1064 - *(float *)(param_1 + 0x170);
        }
        else {
          if (*(float *)(param_1 + 0x5c) < *(float *)(g_entities + tmp_i6 + 0x150)) {
            local_1060 = *(float *)(g_entities + tmp_i6 + 0x150) - *(float *)(param_1 + 0x168);
          }
          else if (*(float *)(g_entities + tmp_i6 + 0x15c) < *(float *)(param_1 + 0x168)) {
            local_1060 = *(float *)(param_1 + 0x168) - *(float *)(g_entities + tmp_i6 + 0x15c);
          }
          else {
            local_1060 = 0.0;
          }
          if (*(float *)(param_1 + 0x60) < *(float *)(g_entities + tmp_i8 * 0x600 + 0x154)) {
            local_105c = *(float *)(g_entities + tmp_i8 * 0x600 + 0x154) -
                         *(float *)(param_1 + 0x16c);
          }
          else if (*(float *)(g_entities + tmp_i8 * 0x600 + 0x160) < *(float *)(param_1 + 0x16c)) {
            local_105c = *(float *)(param_1 + 0x16c) -
                         *(float *)(g_entities + tmp_i8 * 0x600 + 0x160);
          }
          else {
            local_105c = 0.0;
          }
          if (*(float *)(param_1 + 100) < *(float *)(g_entities + tmp_i8 * 0x600 + 0x158)) {
            local_1058 = *(float *)(g_entities + tmp_i8 * 0x600 + 0x158) -
                         *(float *)(param_1 + 0x170);
          }
          else if (*(float *)(g_entities + tmp_i8 * 0x600 + 0x164) < *(float *)(param_1 + 0x170)) {
            local_1058 = *(float *)(param_1 + 0x170) -
                         *(float *)(g_entities + tmp_i8 * 0x600 + 0x164);
          }
          else {
            local_1058 = 0.0;
          }
        }
        tmp_f3 = *(float *)(param_1 + 0x268);
        tmp_l10 = (long double)VectorLength(&local_1060);
        if (((*(int *)(g_entities + tmp_i8 * 0x600) != *(int *)(param_1 + 0x180)) ||
            (tmp_l10 < (long double)tmp_f3 * (long double)0.5)) && (tmp_l10 < (long double)tmp_f3)) {
          tmp_i6 = tmp_i8 * 0x600;
          if (*(int *)(g_entities + tmp_i6 + 400) == 0) {
            if (0 < *(int *)(g_entities + tmp_i6 + 0x2c8)) {
              tmp_u7 = G_GetWeaponDamage(6);
              G_Damage(tmp_pu1,*(uint32_t *)(param_1 + 0x218),*(uint32_t *)(param_1 + 0x218),
                       &vec3_origin,param_1 + 0x168,tmp_u7,0,0x11);
            }
          }
          else {
            trap_Trace(local_1054,param_1 + 0x168,0,0,&local_106c,
                       *(int *)(g_entities + tmp_i8 * 0x600),0x6000001);
            if (1.0 <= local_104c) {
              tmp_pi2 = (int *)(g_entities + tmp_i6 + 0x390);
              if ((*(int *)(g_entities + tmp_i6 + 0x394) != 0) && (0 < *tmp_pi2)) {
                tmp_i8 = *tmp_pi2 - (int)ROUND(((float)(g_unk_00abe908 -
                                                     *(int *)(g_entities + tmp_i6 + 0x394)) / 1000.0)
                                             * 2.5);
                if (tmp_i8 < 0) {
                  *tmp_pi2 = 0;
                }
                else {
                  *tmp_pi2 = tmp_i8;
                }
              }
              G_BurnMeGood(*(uint32_t *)(param_1 + 0x218),tmp_pu1,param_1);
              if (((*(int *)(param_1 + 0x2e4) != 0) && (*(int *)(param_1 + 0x218) != 0)) &&
                 (*(int *)(*(int *)(param_1 + 0x218) + 400) != 0)) {
                tmp_u7 = G_GetWeaponDamage(6);
                G_addStats(tmp_pu1,*(uint32_t *)(param_1 + 0x218),tmp_u7,0x11);
                *(uint32_t *)(param_1 + 0x2e4) = 0;
              }
            }
          }
        }
        goto LAB_0009cdd0;
      }
      tmp_i9 = tmp_i9 + 1;
      *(uint32_t *)(g_entities + tmp_i6 + 0x390) = 0;
      *(int *)(g_entities + tmp_i6 + 0x100) = g_unk_00abe908 + -1;
    } while (tmp_i9 != tmp_i4);
  }
  return;
}

void G_RunFlamechunk(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint8_t *tmp_pu6;
  long double tmp_l7;
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
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  float local_3c;
  float local_38;
  float local_34;
  byte local_28;
  int local_20;
  
  local_78 = *(float *)(param_1 + 0x24);
  local_74 = *(float *)(param_1 + 0x28);
  local_70 = *(float *)(param_1 + 0x2c);
  tmp_l7 = (long double)VectorNormalize(&local_78);
  if (g_unk_00abe908 - *(int *)(param_1 + 0x24c) < 0x33) {
    tmp_f1 = *(float *)(param_1 + 0x24);
    tmp_f2 = *(float *)(param_1 + 0x28);
    tmp_f3 = *(float *)(param_1 + 0x2c);
    tmp_f4 = 1200.0;
  }
  else {
    tmp_f4 = 60.0;
    if (60.0 <= (float)(tmp_l7 - (long double)120.00000178813934)) {
      tmp_f4 = (float)(tmp_l7 - (long double)120.00000178813934);
    }
    tmp_f1 = local_78 * tmp_f4;
    *(float *)(param_1 + 0x24) = tmp_f1;
    tmp_f2 = local_74 * tmp_f4;
    *(float *)(param_1 + 0x28) = tmp_f2;
    tmp_f3 = local_70 * tmp_f4;
    *(float *)(param_1 + 0x2c) = tmp_f3;
  }
  local_6c = tmp_f1 * 0.05 + *(float *)(param_1 + 0x168);
  local_68 = tmp_f2 * 0.05 + *(float *)(param_1 + 0x16c);
  local_64 = tmp_f3 * 0.05 + *(float *)(param_1 + 0x170);
  trap_Trace(local_54,param_1 + 0x168,param_1 + 0x134,param_1 + 0x140,&local_6c,
             *(uint32_t *)(param_1 + 0x180),0x6000039);
  tmp_i5 = g_unk_00abe908;
  if (local_50 == 0) {
    if ((local_4c != 1.0) && ((local_28 & 0x10) == 0)) {
      *(uint32_t *)(param_1 + 0x168) = local_48;
      *(uint32_t *)(param_1 + 0x16c) = local_44;
      *(uint32_t *)(param_1 + 0x170) = local_40;
      tmp_pu6 = (uint8_t *)0x0;
      tmp_f1 = local_70 * local_34 + local_74 * local_38 + local_78 * local_3c;
      tmp_f2 = tmp_f1 * -2.0;
      local_78 = local_3c * tmp_f2 + local_78;
      local_74 = local_38 * tmp_f2 + local_74;
      local_70 = tmp_f2 * local_34 + local_70;
      VectorNormalize(&local_78);
      tmp_f4 = tmp_f4 * ((tmp_f1 + 1.0) * 0.5 * 0.75 + 0.25) * 0.5;
      *(float *)(param_1 + 0x24) = local_78 * tmp_f4;
      *(float *)(param_1 + 0x28) = local_74 * tmp_f4;
      *(float *)(param_1 + 0x2c) = tmp_f4 * local_70;
      if (1 < local_20 - 0x3feU) {
        tmp_pu6 = g_entities + local_20 * 0x600;
        G_BurnTarget(param_1,tmp_pu6,1);
      }
      *(int *)(param_1 + 0x39c) = *(int *)(param_1 + 0x39c) + 1;
      goto LAB_0009d400;
    }
    tmp_pu6 = (uint8_t *)0x0;
    *(float *)(param_1 + 0x168) = local_6c;
    *(float *)(param_1 + 0x16c) = local_68;
    *(float *)(param_1 + 0x170) = local_64;
    if (tmp_i5 < *(int *)(param_1 + 0x394)) goto LAB_0009d40f;
  }
  else {
    *(int *)(param_1 + 0x39c) = *(int *)(param_1 + 0x39c) + 1;
    tmp_pu6 = (uint8_t *)0x0;
    *(uint32_t *)(param_1 + 0x2c) = 0;
    *(uint32_t *)(param_1 + 0x28) = 0;
    *(uint32_t *)(param_1 + 0x24) = 0;
LAB_0009d400:
    tmp_i5 = g_unk_00abe908;
    if (g_unk_00abe908 < *(int *)(param_1 + 0x394)) goto LAB_0009d40f;
  }
  *(int *)(param_1 + 0x394) = tmp_i5 + 100;
  G_FlameDamage(param_1,tmp_pu6);
LAB_0009d40f:
  if (GHIDRA_FIELD(g_debugBullets, 12, 4) - 4 < 0x7c) {
    tmp_f3 = *(float *)(param_1 + 0x268) * 0.5;
    local_60 = *(float *)(param_1 + 0x168) - tmp_f3;
    local_5c = *(float *)(param_1 + 0x16c) - tmp_f3;
    local_58 = *(float *)(param_1 + 0x170) - tmp_f3;
    tmp_f4 = *(float *)(param_1 + 0x168);
    tmp_f1 = *(float *)(param_1 + 0x16c);
    tmp_f2 = *(float *)(param_1 + 0x170);
    tmp_i5 = nitrox_TempEventFromQueue(&local_60,0x32);
    *(uint32_t *)(tmp_i5 + 0xf8) = 1;
    *(float *)(tmp_i5 + 0x68) = tmp_f4 + tmp_f3;
    *(float *)(tmp_i5 + 0x6c) = tmp_f1 + tmp_f3;
    *(float *)(tmp_i5 + 0x70) = tmp_f3 + tmp_f2;
  }
  if (*(float *)(param_1 + 0x268) < 100.0) {
    tmp_f4 = *(float *)(param_1 + 0x268) + 10.0;
    if (100.0 < tmp_f4) {
      tmp_f4 = 100.0;
    }
    *(float *)(param_1 + 0x268) = tmp_f4;
  }
  if (g_unk_00abe908 - *(int *)(param_1 + 0x24c) < 0x7b8) {
    G_RunThink();
    return;
  }
  G_FreeEntity(param_1);
  return;
}

void nitrox_FadeLandmines(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i3 = LandmineEntities + -1;
  if (-1 < tmp_i3) {
    do {
      while (((tmp_i1 = (&g_unk_0087ca04)[tmp_i3], *(int *)(tmp_i1 + 0x194) == 0 ||
              (*(int *)(tmp_i1 + 0x218) != param_1)) || (*(int *)(tmp_i1 + 0x218) == 0))) {
        tmp_i3 = tmp_i3 + -1;
        if (tmp_i3 == -1) {
          return;
        }
      }
      tmp_i4 = (tmp_i1 + -0x93e4a0 >> 9) * -0x55555555;
      tmp_i2 = G_FindMapEntityData(mapEntityData,tmp_i4);
      if (tmp_i2 != 0) {
        G_FreeMapEntityData(mapEntityData,tmp_i2);
      }
      tmp_i2 = G_FindMapEntityData(0x2d8ca94,tmp_i4);
      if (tmp_i2 != 0) {
        G_FreeMapEntityData(0x2d8ca94,tmp_i2);
      }
      *(uint32_t *)(tmp_i1 + 0x218) = 0;
      tmp_i3 = tmp_i3 + -1;
      *(uint32_t *)(tmp_i1 + 0x180) = 0x3ff;
      G_FreeEntity(tmp_i1);
    } while (tmp_i3 != -1);
  }
  return;
}

void nitrox_FadeSatchels(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = SatchelEntities + -1;
  if (-1 < tmp_i2) {
    do {
      while (tmp_i1 = (&g_unk_008799a4)[tmp_i2], *(int *)(tmp_i1 + 0x218) != param_1) {
        tmp_i2 = tmp_i2 + -1;
        if (tmp_i2 == -1) {
          return;
        }
      }
      *(uint32_t *)(tmp_i1 + 0x218) = 0;
      tmp_i2 = tmp_i2 + -1;
      *(uint32_t *)(tmp_i1 + 0x180) = 0x3ff;
      G_FreeEntity(tmp_i1);
    } while (tmp_i2 != -1);
  }
  return;
}

void nitrox_FadeAirstrikes(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = AirstrikeEntities + -1;
  if (-1 < tmp_i2) {
    do {
      while ((tmp_i1 = *(int *)(&g_unk_00878984 + tmp_i2 * 4), *(int *)(tmp_i1 + 0x194) == 0 ||
             (*(int *)(tmp_i1 + 0x218) != param_1))) {
        tmp_i2 = tmp_i2 + -1;
        if (tmp_i2 == -1) {
          return;
        }
      }
      *(uint32_t *)(tmp_i1 + 0x218) = 0;
      tmp_i2 = tmp_i2 + -1;
      *(uint32_t *)(tmp_i1 + 0x180) = 0x3ff;
      G_FreeEntity(tmp_i1);
    } while (tmp_i2 != -1);
  }
  return;
}

uint64_t G_CountTeamLandmines(int param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  int *local_14;
  
  local_14 = (int *)0x9db69;
  if (LandmineEntities < 1) {
    tmp_i3 = 0;
  }
  else {
    tmp_pi2 = &g_unk_0087ca04;
    local_14 = &g_unk_0087ca04 + LandmineEntities;
    tmp_i3 = 0;
    do {
      if (*(int *)(*tmp_pi2 + 0x108) % 4 == param_1 && *(int *)(*tmp_pi2 + 0x108) < 4) {
        tmp_i3 = tmp_i3 + 1;
      }
      tmp_pi2 = tmp_pi2 + 1;
    } while (tmp_pi2 != local_14);
  }
  tmp_i1 = GHIDRA_FIELD(team_maxLandmines, 12, 4);
  if (tmp_i3 <= (int)GHIDRA_FIELD(team_maxLandmines, 12, 4)) {
    tmp_i1 = tmp_i3;
  }
  return CONCAT44(local_14,tmp_i1);
}

uint32_t G_SweepForLandmines(float *param_1,float param_2)
{
  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  int tmp_i4;
  float local_1024;
  float local_1020;
  float local_101c;
  float local_1018;
  float local_1014;
  float local_1010;
  uint8_t local_100c [4100];
  
  tmp_f1 = *param_1;
  tmp_f2 = -param_2;
  pfVar3 = (float *)tv(tmp_f2,tmp_f2,tmp_f2);
  local_1024 = tmp_f1 + *pfVar3;
  tmp_f1 = param_1[1];
  tmp_i4 = tv(tmp_f2,tmp_f2,tmp_f2);
  local_1020 = tmp_f1 + *(float *)(tmp_i4 + 4);
  tmp_f1 = param_1[2];
  tmp_i4 = tv(tmp_f2,tmp_f2,tmp_f2);
  local_101c = tmp_f1 + *(float *)(tmp_i4 + 8);
  tmp_f1 = *param_1;
  pfVar3 = (float *)tv(param_2,param_2,param_2);
  local_1018 = tmp_f1 + *pfVar3;
  tmp_f1 = param_1[1];
  tmp_i4 = tv(param_2,param_2,param_2);
  local_1014 = tmp_f1 + *(float *)(tmp_i4 + 4);
  tmp_f1 = param_1[2];
  tmp_i4 = tv(param_2,param_2,param_2);
  local_1010 = tmp_f1 + *(float *)(tmp_i4 + 8);
  trap_EntitiesInBox(&local_1024,&local_1018,local_100c,0x400);
  return 0;
}

int G_FindSatchel(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (0 < SatchelEntities) {
    tmp_i3 = 0;
    tmp_i1 = *(int *)(g_unk_008799a4 + 0x218);
    tmp_i2 = g_unk_008799a4;
    while( true ) {
      if (tmp_i1 == param_1) {
        return tmp_i2;
      }
      tmp_i3 = tmp_i3 + 1;
      if (tmp_i3 == SatchelEntities) break;
      tmp_i2 = (&g_unk_008799a4)[tmp_i3];
      tmp_i1 = *(int *)(tmp_i2 + 0x218);
    }
  }
  return 0;
}

uint32_t G_ExplodeSatchels(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  long double tmp_l4;
  uint32_t local_30;
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x9dd8b;
  local_30 = 0;
  if (SatchelEntities < 1) {
    return 0;
  }
  tmp_i3 = 0;
  tmp_i2 = SatchelEntities;
  do {
    while ((tmp_i1 = (&g_unk_008799a4)[tmp_i3], *(int *)(tmp_i1 + 0x194) == 0 ||
           (*(int *)(tmp_i1 + 0x218) != param_1))) {
LAB_0009ddc0:
      tmp_i3 = tmp_i3 + 1;
      if (tmp_i2 <= tmp_i3) {
        return local_30;
      }
    }
    local_28 = *(float *)(tmp_i1 + 0x168) - *(float *)(param_1 + 0x168);
    local_24 = *(float *)(tmp_i1 + 0x16c) - *(float *)(param_1 + 0x16c);
    local_20 = *(float *)(tmp_i1 + 0x170) - *(float *)(param_1 + 0x170);
    tmp_l4 = (long double)VectorLengthSquared(&local_28);
    if (tmp_l4 <= (long double)4e+06) {
      G_ExplodeMissile(tmp_i1);
      local_30 = 1;
      tmp_i2 = SatchelEntities;
      goto LAB_0009ddc0;
    }
    tmp_i3 = tmp_i3 + 1;
    tmp_i2 = SatchelEntities;
    if (SatchelEntities <= tmp_i3) {
      return local_30;
    }
  } while( true );
}

void G_TripMinePrime(int param_1)
{
  *(uint32_t *)(param_1 + 0x2cc) = 1;
  *(uint32_t *)(param_1 + 0x2c8) = 0x14;
  *(void **)(param_1 + 700) = Nit_WeapDie;
  *(void **)(param_1 + 0x2a4) = G_TripMineThink;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 5;
  return;
}

void G_LandminePrime(int param_1)
{
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  *(void **)(param_1 + 0x2a4) = G_LandmineThink;
  return;
}

bool G_LandmineSnapshotCallback(int param_1,int param_2)
{
  bool tmp_b1;
  int tmp_i2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  
  tmp_i2 = trap_InPVS(param_2 * 0x600 + 0x93e608,param_1 * 0x600 + 0x93e608);
  tmp_b1 = false;
  if (tmp_i2 != 0) {
    if ((*(byte *)(*(int *)(g_entities + param_2 * 0x600 + 400) + 0xed0) & 0x10) == 0) {
      tmp_pu4 = g_entities + param_1 * 0x600;
      tmp_i2 = G_LandmineArmed(tmp_pu4);
      if ((tmp_i2 != 0) && (tmp_i2 = G_LandmineSpotted(tmp_pu4), tmp_i2 == 0)) {
        tmp_i3 = G_LandmineTeam(tmp_pu4);
        tmp_i2 = *(int *)(g_entities + param_2 * 0x600 + 400);
        if ((*(int *)(tmp_i2 + 3000) != tmp_i3) &&
           (((*(int *)(tmp_i2 + 0xbc8) != 4 || ((*(byte *)(tmp_i2 + 0x6a) & 4) == 0)) ||
            ((*(byte *)(tmp_i2 + 0xd4) & 0x40) == 0)))) {
          return *(int *)(tmp_i2 + 3000) == 3;
        }
      }
    }
    tmp_b1 = true;
  }
  return tmp_b1;
}

void G_UpdateTeamMapData_LandMine(int param_1,int param_2,int param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint tmp_u4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  bool tmp_b7;
  uint local_24;
  
  tmp_i2 = *(int *)(param_1 + 0x108);
  tmp_i6 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
  tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49196, 4);
  if (tmp_i2 % 4 == 1) {
LAB_000effb0:
    if (3 < tmp_i2 - 4U) {
joined_r0x000efe7e:
      for (; (tmp_pu3 != (uint32_t *)0x0 && (tmp_pu3 != (uint32_t *)(mapEntityData + 0xc004)));
          tmp_pu3 = (uint32_t *)tmp_pu3[10]) {
        if (((int)tmp_pu3[7] < 0) && (tmp_i6 == tmp_pu3[9])) goto LAB_000efeaf;
      }
      tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
      if (GHIDRA_FIELD(mapEntityData, 49152, 4) == 0) {
        G_Error("G_AllocMapEntityData: out of entities");
        tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 49152, 4);
      }
      GHIDRA_FIELD(mapEntityData, 49152, 4) = tmp_pu3[10];
      tmp_b7 = ((uint)tmp_pu3 & 1) != 0;
      local_24 = 0x30;
      tmp_pu5 = tmp_pu3;
      if (tmp_b7) {
        *(uint8_t *)tmp_pu3 = 0;
        tmp_pu5 = (uint32_t *)((int)tmp_pu3 + 1);
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
      tmp_pu3[7] = 0xffffffff;
      tmp_pu3[10] = GHIDRA_FIELD(mapEntityData, 49196, 4);
      tmp_pu3[0xb] = 0x2d8ca64;
      *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 49196, 4) + 0x2c) = tmp_pu3;
      GHIDRA_FIELD(mapEntityData, 49196, 4) = tmp_pu3;
      tmp_pu3[9] = tmp_i6;
LAB_000efeaf:
      *tmp_pu3 = *(uint32_t *)(param_1 + 0x168);
      tmp_pu3[1] = *(uint32_t *)(param_1 + 0x16c);
      tmp_pu3[2] = *(uint32_t *)(param_1 + 0x170);
      tmp_pu3[4] = *(int *)(param_1 + 0x108) % 4;
      tmp_u1 = g_unk_00abe908;
      *(uint8_t *)(tmp_pu3 + 5) = 6;
      tmp_pu3[6] = tmp_u1;
    }
  }
  else {
    if (tmp_i2 % 4 == 2) {
      if (param_3 == 0) goto LAB_000eff03;
      if (tmp_i2 - 4U < 4) {
        return;
      }
      param_2 = 1;
      goto joined_r0x000efe7e;
    }
    if (param_3 != 0) goto LAB_000effb0;
  }
  if (param_2 == 0) {
    return;
  }
  tmp_i2 = *(int *)(param_1 + 0x108);
LAB_000eff03:
  tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98400, 4);
  if (3 < tmp_i2 - 4U) {
    for (; (tmp_pu3 != (uint32_t *)0x0 && (tmp_pu3 != (uint32_t *)(mapEntityData + 0x18038)));
        tmp_pu3 = (uint32_t *)tmp_pu3[10]) {
      if (((int)tmp_pu3[7] < 0) && (tmp_i6 == tmp_pu3[9])) goto LAB_000eff4f;
    }
    tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
    if (GHIDRA_FIELD(mapEntityData, 98356, 4) == 0) {
      G_Error("G_AllocMapEntityData: out of entities");
      tmp_pu3 = (uint32_t *)GHIDRA_FIELD(mapEntityData, 98356, 4);
    }
    GHIDRA_FIELD(mapEntityData, 98356, 4) = tmp_pu3[10];
    tmp_b7 = ((uint)tmp_pu3 & 1) != 0;
    local_24 = 0x30;
    tmp_pu5 = tmp_pu3;
    if (tmp_b7) {
      *(uint8_t *)tmp_pu3 = 0;
      tmp_pu5 = (uint32_t *)((int)tmp_pu3 + 1);
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
    tmp_pu3[7] = 0xffffffff;
    tmp_pu3[10] = GHIDRA_FIELD(mapEntityData, 98400, 4);
    tmp_pu3[0xb] = 0x2d98a98;
    *(uint32_t **)(GHIDRA_FIELD(mapEntityData, 98400, 4) + 0x2c) = tmp_pu3;
    GHIDRA_FIELD(mapEntityData, 98400, 4) = tmp_pu3;
    tmp_pu3[9] = tmp_i6;
LAB_000eff4f:
    *tmp_pu3 = *(uint32_t *)(param_1 + 0x168);
    tmp_pu3[1] = *(uint32_t *)(param_1 + 0x16c);
    tmp_pu3[2] = *(uint32_t *)(param_1 + 0x170);
    tmp_pu3[4] = *(int *)(param_1 + 0x108) % 4;
    tmp_u1 = g_unk_00abe908;
    *(uint8_t *)(tmp_pu3 + 5) = 6;
    tmp_pu3[6] = tmp_u1;
  }
  return;
}

bool G_IsAllowedAmmo(int param_1)
{
  int tmp_i1;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 400) != 0)) && (-1 < *(int *)(param_1 + 0x2c8))) {
    tmp_i1 = AddMagicAmmo(param_1,0);
    return tmp_i1 != 0;
  }
  return false;
}

void G_AirStrikeExplode(int param_1)
{
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0xfffffffe | 0x20;
  *(void **)(param_1 + 0x2a4) = G_ExplodeMissile;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 0x32;
  return;
}

void nitrox_artillerySpotter_Think(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = rand();
  if (tmp_i1 % 3 == 1) {
    G_AddEvent(param_1,0x28,2);
  }
  else if (tmp_i1 % 3 == 2) {
    G_AddEvent(param_1,0x28,3);
  }
  else if (tmp_i1 == (tmp_i1 / 3) * 3) {
    G_AddEvent(param_1,0x28,1);
  }
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 500;
  *(void **)(param_1 + 0x2a4) = artillerySpotterThink;
  return;
}

void weapon_callSecondPlane(int param_1)
{
  nitmod_Sound_Global(0x10);
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 1000;
  *(void **)(param_1 + 0x2a4) = weapon_callAirStrike;
  return;
}

void weapon_smokeBombExplode(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = g_unk_00abe908;
  if (*(int *)(param_1 + 0x3a0) == 0) {
    *(int *)(param_1 + 0x3a0) = g_unk_00abe908;
    *(int *)(param_1 + 0x29c) = tmp_i1 + 100;
    tmp_i1 = 0;
    if (1 < *(int *)(param_1 + 0xe8) - 0x32U) goto LAB_000fe80d;
LAB_000fe878:
    nitmod_PoisonGasThink(param_1);
  }
  else {
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
    tmp_i1 = tmp_i1 - *(int *)(param_1 + 0x3a0);
    if (*(int *)(param_1 + 0xe8) - 0x32U < 2) goto LAB_000fe878;
  }
  if (999 < tmp_i1) {
    if (tmp_i1 < 16000) {
      *(uint32_t *)(param_1 + 0x10c) = 0x280;
      return;
    }
    if (tmp_i1 < 18000) {
      *(uint32_t *)(param_1 + 0x10c) = 0xffffffff;
      return;
    }
    G_FreeEntity(param_1);
    return;
  }
LAB_000fe80d:
  *(int *)(param_1 + 0x10c) = (int)ROUND((float)tmp_i1 * 0.624 + 16.0);
  return;
}

long double G_GetWeaponSpread_part_6(int param_1)
{
  char *tmp_pc1;
  
  switch(param_1) {
  default:
    if (param_1 - 1U < 0x33) {
      tmp_pc1 = (char *)(param_1 * 0x6b0 + 0x898ef4);
    }
    else {
      tmp_pc1 = "^1invalid";
    }
    G_Printf("^1ERROR : ^7G_GetWeaponSpread ^9no case for weapon %d (%s)\n",param_1,tmp_pc1);
_L67:
    return (long double)0;
  case 1:
  case 5:
  case 0x2f:
    goto _L67;
  case 2:
  case 7:
  case 0xe:
  case 0x22:
  case 0x23:
  case 0x26:
  case 0x2c:
  case 0x2d:
    return (long double)600.0;
  case 3:
  case 8:
    return (long double)400.0;
  case 10:
  case 0x29:
    return (long double)200.0;
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x1e:
    return (long double)250.0;
  case 0x1d:
  case 0x2e:
    return (long double)2500.0;
  case 0x1f:
    return (long double)500.0;
  case 0x27:
  case 0x28:
    return (long double)700.0;
  }
}

void weapon_checkAirStrikeThink1(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  void *tmp_pc7;
  long double tmp_l8;
  
  if (*(int *)(param_1 + 0x108) == 1) {
    g_unk_02aa2ecc = g_unk_02aa2ecc + 1;
  }
  else {
    g_unk_02aa2ed0 = g_unk_02aa2ed0 + 1;
  }
  tmp_i5 = *(int *)(param_1 + 0x218);
  if (((((g_friendlyFire[0xc] & 1) == 0) && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) &&
      (*(int *)(tmp_i5 + 400) != 0)) && (*(int *)(*(int *)(tmp_i5 + 400) + 3000) == 3)) {
    tmp_f2 = (float)g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x2d4) = 0;
    *(void **)(param_1 + 0x2a4) = G_ExplodeMissile;
    tmp_u6 = rand();
    tmp_f1 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    *(int *)(param_1 + 0x29c) = (int)ROUND((tmp_f1 + tmp_f1) * 50.0 + tmp_f2);
    *(uint32_t *)(param_1 + 0x368) = 0;
    if (*(int *)(param_1 + 0x108) == 1) {
      g_unk_02aa2ecc = g_unk_02aa2ecc + -1;
    }
    else {
      g_unk_02aa2ed0 = g_unk_02aa2ed0 + -1;
    }
    goto LAB_000ff356;
  }
  if (*(int *)(param_1 + 0x108) == 1) {
    if (g_unk_02aa2ecc < 7) {
      tmp_i4 = *(int *)(*(int *)(tmp_i5 + 400) + 3000);
      goto joined_r0x000ff3aa;
    }
  }
  else if (g_unk_02aa2ed0 < 7) {
    tmp_i4 = *(int *)(*(int *)(tmp_i5 + 400) + 3000);
joined_r0x000ff3aa:
    tmp_i3 = g_unk_02aa29a8;
    if (tmp_i4 != 1) {
      tmp_i3 = g_unk_02aa29ac;
    }
    if (tmp_i3 < 1) {
      tmp_pc7 = weapon_callAirStrike;
      tmp_i5 = g_unk_00abe908 + 0x5dc;
      goto LAB_000ff360;
    }
  }
  tmp_i4 = nitrox_TempEventFromQueue(&vec3_origin,0x5c);
  *(uint32_t *)(tmp_i4 + 0xf4) = 0;
  *(uint32_t *)(tmp_i4 + 0x10c) = 1;
  *(int *)(tmp_i4 + 300) = (tmp_i5 + -0x93e4a0 >> 9) * -0x55555555;
  *(uint32_t *)(tmp_i4 + 0x128) = 0x820;
  *(uint32_t *)(param_1 + 0x368) = 0;
  if (*(int *)(param_1 + 0x108) == 1) {
    g_unk_02aa2ecc = g_unk_02aa2ecc + -1;
    if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 2) == 0) goto LAB_000ff30f;
LAB_000ff3cf:
    tmp_l8 = (long double)
            BG_GetFromTable(&chargeCost_Artillery,*(int *)(*(int *)(param_1 + 0x218) + 400) + 0xed0,
                            3);
    if (((*(int *)(param_1 + 0x218) != 0) &&
        (tmp_i5 = *(int *)(*(int *)(param_1 + 0x218) + 400), tmp_i5 != 0)) && (GHIDRA_FIELD(g_noCharge, 12, 4) == 0)
       ) {
      tmp_i4 = *(int *)(tmp_i5 + 0x478);
LAB_000ff4c7:
      *(int *)(tmp_i5 + 0x478) =
           (int)ROUND((long double)tmp_i4 -
                      (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i5 + 3000)] * tmp_l8);
    }
  }
  else {
    g_unk_02aa2ed0 = g_unk_02aa2ed0 + -1;
    if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 2) != 0) goto LAB_000ff3cf;
LAB_000ff30f:
    if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 4) != 0) {
      tmp_l8 = (long double)
              BG_GetFromTable(&chargeCost_Artillery,
                              *(int *)(*(int *)(param_1 + 0x218) + 400) + 0xed0,3);
      if (((*(int *)(param_1 + 0x218) == 0) ||
          (tmp_i5 = *(int *)(*(int *)(param_1 + 0x218) + 400), tmp_i5 == 0)) ||
         (GHIDRA_FIELD(g_noCharge, 12, 4) != 0)) goto LAB_000ff356;
      tmp_i4 = *(int *)(tmp_i5 + 0x478);
      tmp_l8 = tmp_l8 * (long double)0.5;
      goto LAB_000ff4c7;
    }
  }
LAB_000ff356:
  tmp_pc7 = G_ExplodeMissile;
  tmp_i5 = g_unk_00abe908 + 1000;
LAB_000ff360:
  *(int *)(param_1 + 0x29c) = tmp_i5;
  *(void **)(param_1 + 0x2a4) = tmp_pc7;
  return;
}

void weapon_checkAirStrikeThink2(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  void *tmp_pc7;
  long double tmp_l8;
  
  if (*(int *)(param_1 + 0x108) == 1) {
    g_unk_02aa2ecc = g_unk_02aa2ecc + 1;
  }
  else {
    g_unk_02aa2ed0 = g_unk_02aa2ed0 + 1;
  }
  tmp_i5 = *(int *)(param_1 + 0x218);
  if (((((g_friendlyFire[0xc] & 1) == 0) && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) &&
      (*(int *)(tmp_i5 + 400) != 0)) && (*(int *)(*(int *)(tmp_i5 + 400) + 3000) == 3)) {
    tmp_f2 = (float)g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x2d4) = 0;
    *(void **)(param_1 + 0x2a4) = G_ExplodeMissile;
    tmp_u6 = rand();
    tmp_f1 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
    *(int *)(param_1 + 0x29c) = (int)ROUND((tmp_f1 + tmp_f1) * 50.0 + tmp_f2);
    *(uint32_t *)(param_1 + 0x368) = 0;
    if (*(int *)(param_1 + 0x108) == 1) {
      g_unk_02aa2ecc = g_unk_02aa2ecc + -1;
    }
    else {
      g_unk_02aa2ed0 = g_unk_02aa2ed0 + -1;
    }
    goto LAB_000ff706;
  }
  if (*(int *)(param_1 + 0x108) == 1) {
    if (g_unk_02aa2ecc < 7) {
      tmp_i4 = *(int *)(*(int *)(tmp_i5 + 400) + 3000);
      goto joined_r0x000ff75a;
    }
  }
  else if (g_unk_02aa2ed0 < 7) {
    tmp_i4 = *(int *)(*(int *)(tmp_i5 + 400) + 3000);
joined_r0x000ff75a:
    tmp_i3 = g_unk_02aa29a8;
    if (tmp_i4 != 1) {
      tmp_i3 = g_unk_02aa29ac;
    }
    if (tmp_i3 < 1) {
      tmp_pc7 = weapon_callSecondPlane;
      tmp_i5 = g_unk_00abe908 + 500;
      goto LAB_000ff710;
    }
  }
  tmp_i4 = nitrox_TempEventFromQueue(&vec3_origin,0x5c);
  *(uint32_t *)(tmp_i4 + 0xf4) = 0;
  *(uint32_t *)(tmp_i4 + 0x10c) = 1;
  *(int *)(tmp_i4 + 300) = (tmp_i5 + -0x93e4a0 >> 9) * -0x55555555;
  *(uint32_t *)(tmp_i4 + 0x128) = 0x820;
  *(uint32_t *)(param_1 + 0x368) = 0;
  if (*(int *)(param_1 + 0x108) == 1) {
    g_unk_02aa2ecc = g_unk_02aa2ecc + -1;
    if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 2) == 0) goto LAB_000ff6bf;
LAB_000ff77f:
    tmp_l8 = (long double)
            BG_GetFromTable(&chargeCost_Artillery,*(int *)(*(int *)(param_1 + 0x218) + 400) + 0xed0,
                            3);
    if (((*(int *)(param_1 + 0x218) != 0) &&
        (tmp_i5 = *(int *)(*(int *)(param_1 + 0x218) + 400), tmp_i5 != 0)) && (GHIDRA_FIELD(g_noCharge, 12, 4) == 0)
       ) {
      tmp_i4 = *(int *)(tmp_i5 + 0x478);
LAB_000ff877:
      *(int *)(tmp_i5 + 0x478) =
           (int)ROUND((long double)tmp_i4 -
                      (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i5 + 3000)] * tmp_l8);
    }
  }
  else {
    g_unk_02aa2ed0 = g_unk_02aa2ed0 + -1;
    if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 2) != 0) goto LAB_000ff77f;
LAB_000ff6bf:
    if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 4) != 0) {
      tmp_l8 = (long double)
              BG_GetFromTable(&chargeCost_Artillery,
                              *(int *)(*(int *)(param_1 + 0x218) + 400) + 0xed0,3);
      if (((*(int *)(param_1 + 0x218) == 0) ||
          (tmp_i5 = *(int *)(*(int *)(param_1 + 0x218) + 400), tmp_i5 == 0)) ||
         (GHIDRA_FIELD(g_noCharge, 12, 4) != 0)) goto LAB_000ff706;
      tmp_i4 = *(int *)(tmp_i5 + 0x478);
      tmp_l8 = tmp_l8 * (long double)0.5;
      goto LAB_000ff877;
    }
  }
LAB_000ff706:
  tmp_pc7 = G_ExplodeMissile;
  tmp_i5 = g_unk_00abe908 + 1000;
LAB_000ff710:
  *(int *)(param_1 + 0x29c) = tmp_i5;
  *(void **)(param_1 + 0x2a4) = tmp_pc7;
  return;
}

void weapon_callAirStrike(uint32_t *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint tmp_u6;
  int tmp_i7;
  int tmp_i8;
  uint32_t tmp_u9;
  char *tmp_pc10;
  float *pfVar11;
  float tmp_f12;
  long double tmp_l13;
  long double tmp_l14;
  float tmp_f15;
  float tmp_f16;
  uint64_t tmp_u17;
  float local_1134;
  float local_1128;
  uint local_1124;
  uint local_111c;
  float local_110c;
  uint8_t *local_1108;
  float *local_10fc;
  int local_10d8;
  float local_10b4;
  float local_10b0;
  float local_10ac;
  float local_10a8;
  float local_10a4;
  uint32_t local_10a0;
  float local_109c;
  float local_1098;
  float local_1094;
  float local_1090;
  float local_108c;
  float local_1088;
  uint32_t local_1084;
  uint32_t local_1080;
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
  float local_1048;
  float local_1044;
  float local_1040;
  float local_103c;
  float local_1038;
  float local_1034;
  byte local_1028;
  int local_1020;
  float local_101c [1026];
  uint32_t uStack_14;
  
  uStack_14 = 0xff959;
  local_109c = (float)param_1[6];
  local_1098 = (float)param_1[7];
  param_1[0xa9] = G_ExplodeMissile;
  local_1094 = (float)param_1[8] + 4096.0;
  tmp_i5 = g_unk_00abe908 + 0x79e;
  tmp_u6 = rand();
  tmp_f12 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
  param_1[0xa7] = (int)ROUND((tmp_f12 + tmp_f12) * 50.0 + (float)tmp_i5);
  param_1[0xda] = 1;
  if (*(int *)(*(int *)(param_1[0x86] + 400) + 3000) == 1) {
    g_unk_02aa29a8 = g_unk_02aa29a8 + GHIDRA_FIELD(team_airstrikeTime, 12, 4) * 1000;
  }
  else {
    g_unk_02aa29ac = g_unk_02aa29ac + GHIDRA_FIELD(team_airstrikeTime, 12, 4) * 1000;
  }
  nitmod_Sound_Global(0x10);
  tmp_u6 = *(uint *)(*(int *)(param_1[0x86] + 400) + 0xedc) & 8;
  if ((tmp_u6 == 0) || ((GHIDRA_FIELD(g_asblock, 12, 4) & 4) == 0)) {
    if ((GHIDRA_FIELD(g_asblock, 12, 4) & 2) == 0) {
LAB_000ffa98:
      if ((tmp_u6 != 0) && ((GHIDRA_FIELD(g_asblock, 12, 4) & 4) != 0)) goto LAB_00100364;
      trap_Trace(local_1054,param_1 + 6,0,0,&local_109c,*param_1,0x6000001);
      goto LAB_000ffaee;
    }
    tmp_f12 = (float)param_1[0x5a];
    tmp_f1 = (float)param_1[0x5b];
    tmp_f16 = (float)param_1[0x5c];
    pfVar11 = (float *)tv(0xc1000000,0xc1000000,0xc1000000);
    local_106c = (float)(int)ROUND(tmp_f12) + *pfVar11;
    tmp_i5 = tv(0xc1000000,0xc1000000,0xc1000000);
    local_1068 = (float)(int)ROUND(tmp_f1) + *(float *)(tmp_i5 + 4);
    tmp_i5 = tv(0xc1000000,0xc1000000,0xc1000000);
    local_1064 = (float)(int)ROUND(tmp_f16) + *(float *)(tmp_i5 + 8);
    pfVar11 = (float *)tv(0x41000000,0x41000000,0x41000000);
    local_1060 = (float)(int)ROUND(tmp_f12) + *pfVar11;
    tmp_i5 = tv(0x41000000,0x41000000,0x41000000);
    local_105c = (float)(int)ROUND(tmp_f1) + *(float *)(tmp_i5 + 4);
    tmp_i5 = tv(0x41000000,0x41000000,0x41000000);
    local_1058 = (float)(int)ROUND(tmp_f16) + *(float *)(tmp_i5 + 8);
    if (1 < (int)GHIDRA_FIELD(g_debugBullets, 12, 4)) {
      G_Printf("mins: %f, %f, %f\n",(double)local_106c,(double)local_1068,(double)local_1064);
      G_Printf("maxs: %f, %f, %f\n",(double)local_1060,(double)local_105c,(double)local_1058);
      tmp_f12 = (float)param_1[0x5a];
      tmp_f1 = (float)param_1[0x5b];
      tmp_f16 = (float)param_1[0x5c];
      local_101c[0] = tmp_f12;
      local_101c[1] = tmp_f1;
      local_101c[2] = tmp_f16;
      pfVar11 = (float *)tv(0xc1000000,0xc1000000,0xc1000000);
      tmp_f2 = local_101c[1];
      local_101c[0] = tmp_f12 + *pfVar11;
      tmp_i5 = tv(0xc1000000,0xc1000000,0xc1000000);
      tmp_f3 = local_101c[2];
      local_101c[1] = tmp_f2 + *(float *)(tmp_i5 + 4);
      tmp_i5 = tv(0xc1000000,0xc1000000,0xc1000000);
      local_101c[2] = tmp_f3 + *(float *)(tmp_i5 + 8);
      pfVar11 = (float *)tv(0x41000000,0x41000000,0x41000000);
      tmp_f2 = *pfVar11;
      tmp_i5 = tv(0x41000000,0x41000000,0x41000000);
      tmp_f3 = *(float *)(tmp_i5 + 4);
      tmp_i5 = tv(0x41000000,0x41000000,0x41000000);
      tmp_f4 = *(float *)(tmp_i5 + 8);
      tmp_i5 = nitrox_TempEventFromQueue(local_101c,0x32);
      *(uint32_t *)(tmp_i5 + 0xf8) = 1;
      *(float *)(tmp_i5 + 0x68) = tmp_f12 + tmp_f2;
      *(float *)(tmp_i5 + 0x6c) = tmp_f1 + tmp_f3;
      *(float *)(tmp_i5 + 0x70) = tmp_f16 + tmp_f4;
    }
    tmp_i5 = trap_EntitiesInBox(&local_106c,&local_1060,local_101c,0x400);
    if (tmp_i5 < 1) {
      tmp_u6 = *(uint *)(*(int *)(param_1[0x86] + 400) + 0xedc) & 8;
      goto LAB_000ffa98;
    }
    tmp_f12 = local_101c[0];
    if (*(int *)(g_entities + (int)local_101c[0] * 0x600 + 400) == 0) {
      tmp_i7 = 0;
      do {
        tmp_i7 = tmp_i7 + 1;
        if (tmp_i7 == tmp_i5) {
          tmp_u6 = *(uint *)(*(int *)(param_1[0x86] + 400) + 0xedc) & 8;
          goto LAB_000ffa98;
        }
        tmp_f12 = local_101c[tmp_i7];
      } while (*(int *)(g_entities + (int)tmp_f12 * 0x600 + 400) == 0);
    }
    if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 2) == 0) {
      if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 4) == 0) {
LAB_0010092d:
        tmp_i5 = param_1[0x86];
      }
      else {
        tmp_l13 = (long double)
                 BG_GetFromTable(&chargeCost_Artillery,*(int *)(param_1[0x86] + 400) + 0xed0,3);
        tmp_i5 = param_1[0x86];
        if (((tmp_i5 != 0) && (tmp_i7 = *(int *)(tmp_i5 + 400), tmp_i7 != 0)) &&
           (GHIDRA_FIELD(g_noCharge, 12, 4) == 0)) {
          tmp_i5 = *(int *)(tmp_i7 + 0x478);
          tmp_l13 = (long double)0.5 * tmp_l13;
          tmp_l14 = (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i7 + 3000)];
          goto LAB_00100b33;
        }
      }
    }
    else {
      tmp_l14 = (long double)
               BG_GetFromTable(&chargeCost_Artillery,*(int *)(param_1[0x86] + 400) + 0xed0,3);
      tmp_i5 = param_1[0x86];
      if (((tmp_i5 != 0) && (tmp_i7 = *(int *)(tmp_i5 + 400), tmp_i7 != 0)) && (GHIDRA_FIELD(g_noCharge, 12, 4) == 0))
      {
        tmp_i5 = *(int *)(tmp_i7 + 0x478);
        tmp_l13 = (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i7 + 3000)];
LAB_00100b33:
        *(int *)(tmp_i7 + 0x478) = (int)ROUND((long double)tmp_i5 - tmp_l13 * tmp_l14);
        goto LAB_0010092d;
      }
    }
    if ((GHIDRA_FIELD(g_asblock, 12, 4) & 1) == 0) goto LAB_00100222;
    tmp_u17 = CONCAT44(*(int *)(tmp_i5 + 400) + 0x5f8,
                      *(int *)(g_entities + (int)tmp_f12 * 0x600 + 400) + 0x5f8);
    tmp_pc10 = "cpm \"%s ^7blocked %s^7\'s airstrike!\"";
  }
  else {
LAB_00100364:
    tmp_u9 = *param_1;
    G_TempTraceIgnorePlayersAndBodies();
    trap_Trace(local_1054,param_1 + 6,0,0,&local_109c,tmp_u9,0x6000001);
    G_ResetTempTraceIgnoreEnts();
LAB_000ffaee:
    local_10fc = &local_109c;
    local_1108 = local_1054;
    if ((1.0 <= local_104c) || ((local_1028 & 0x10) != 0)) {
      trap_Trace(local_1108,param_1 + 6,0,0,local_10fc,*param_1,0x6000001);
      if ((1.0 <= local_104c) || ((local_1028 & 0x10) != 0)) {
        tmp_i5 = param_1[0x86];
        tmp_i7 = nitrox_TempEventFromQueue(&vec3_origin,0x5c);
        tmp_f1 = local_1040;
        local_10a0 = 0;
        *(int *)(tmp_i7 + 300) = (tmp_i5 + -0x93e4a0 >> 9) * -0x55555555;
        local_109c = local_1048;
        *(uint32_t *)(tmp_i7 + 0xf4) = 2;
        local_1098 = local_1044;
        *(uint32_t *)(tmp_i7 + 0x128) = 0x820;
        local_1094 = local_1040;
        local_1078 = local_1048;
        local_1074 = local_1044;
        *(uint32_t *)(tmp_i7 + 0x10c) = 1;
        local_1070 = local_1040;
        tmp_f12 = local_1040 - 8192.0;
        local_10a8 = (float)param_1[6] - *(float *)(*(int *)(param_1[0x86] + 400) + 0x14);
        local_10a4 = (float)param_1[7] - *(float *)(*(int *)(param_1[0x86] + 400) + 0x18);
        VectorNormalize(&local_10a8);
        local_1084 = 0;
        local_1080 = 0;
        tmp_u6 = rand();
        local_1134 = (float)(tmp_u6 & 0x7fff);
        local_107c = (float)(int)local_1134 / 32767.0 - 0.5;
        local_107c = local_107c + local_107c;
        VectorNormalize(&local_1084);
        if ((int)param_1[0xb9] < 1) {
          return;
        }
        local_10d8 = 0;
        do {
          tmp_u6 = rand();
          tmp_f16 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
          RotatePointAroundVector
                    (&local_10b4,&local_1084,&local_10a8,(tmp_f16 + tmp_f16) * 30.0 + 90.0);
          tmp_i5 = 0;
          VectorNormalize(&local_10b4);
          local_110c = local_10b4 * -750.0 + (float)param_1[6];
          local_1128 = local_10b0 * -750.0 + (float)param_1[7];
          local_1134 = local_10ac * -750.0 + (float)param_1[8];
          local_10b4 = local_10b4 * 150.0;
          local_10b0 = local_10b0 * 150.0;
          local_10ac = local_10ac * 150.0;
          do {
            tmp_i7 = G_Spawn();
            tmp_i8 = g_unk_00abe908 + tmp_i5;
            local_111c = rand();
            local_111c = local_111c & 0x7fff;
            tmp_f16 = (float)local_111c / 32767.0 - 0.5;
            *(int *)(tmp_i7 + 0x29c) =
                 (int)ROUND((tmp_f16 + tmp_f16) * 50.0 + (float)tmp_i8 + 1000.0 +
                            (float)(local_10d8 * 2000));
            *(void **)(tmp_i7 + 0x2a4) = G_AirStrikeExplode;
            *(uint32_t *)(tmp_i7 + 4) = 3;
            *(uint32_t *)(tmp_i7 + 0x128) = 1;
            *(uint32_t *)(tmp_i7 + 0xe8) = 0x15;
            *(uint32_t *)(tmp_i7 + 0x180) = *param_1;
            *(uint32_t *)(tmp_i7 + 0x218) = param_1[0x86];
            *(uint32_t *)(tmp_i7 + 0x108) = param_1[0x42];
            tmp_u9 = GHIDRA_FIELD(BG_Weapons, 37444, 4);
            if (GHIDRA_FIELD(BG_Weapons, 37444, 4) == 0) {
              tmp_u9 = GHIDRA_FIELD(ammoTableMP, 1552, 4);
            }
            *(uint32_t *)(tmp_i7 + 0x2d0) = tmp_u9;
            tmp_u9 = nitrox_GetWeaponSplashDamage(0x15);
            *(uint32_t *)(tmp_i7 + 0x3fc) = 0x40000000;
            *(uint32_t *)(tmp_i7 + 0x2d4) = tmp_u9;
            *(char **)(tmp_i7 + 0x1a4) = "air strike";
            tmp_u9 = nitrox_GetWeaponSplashDamageRadius(0x15);
            *(uint32_t *)(tmp_i7 + 0xc) = 0;
            *(uint32_t *)(tmp_i7 + 0x2d8) = tmp_u9;
            *(uint32_t *)(tmp_i7 + 0x2dc) = 0x16;
            *(uint32_t *)(tmp_i7 + 0x2e0) = 0x16;
            *(uint32_t *)(tmp_i7 + 0x1d4) = 0x6000081;
            local_1124 = rand();
            local_1124 = local_1124 & 0x7fff;
            tmp_f16 = (float)local_1124 / 32767.0 - 0.5;
            local_109c = (tmp_f16 + tmp_f16) * 0.5 * 150.0;
            local_1124 = rand();
            local_109c = local_110c + local_109c;
            local_1124 = local_1124 & 0x7fff;
            *(float *)(tmp_i7 + 0x18) = local_109c;
            tmp_f16 = (float)local_1124 / 32767.0 - 0.5;
            local_1098 = (tmp_f16 + tmp_f16) * 0.5 * 150.0 + local_1128;
            *(float *)(tmp_i7 + 0x1c) = local_1098;
            *(float *)(tmp_i7 + 0x20) = local_1134 + 0.0;
            local_1094 = tmp_f1;
            local_1090 = local_109c;
            local_108c = local_1098;
            local_1088 = tmp_f12;
            trap_Trace(local_1108,local_10fc,0,0,&local_1090,
                       ((int)(param_1 + -0x24f928) >> 9) * -0x55555555,
                       *(uint32_t *)(tmp_i7 + 0x1d4));
            tmp_f2 = local_1040;
            tmp_f16 = local_1044;
            if (local_104c == 1.0) {
LAB_000ffe68:
              tmp_f3 = local_10ac;
              tmp_f16 = local_10b0;
              tmp_f2 = local_10b4;
              *(uint32_t *)(tmp_i7 + 0x168) = *(uint32_t *)(tmp_i7 + 0x18);
              *(uint32_t *)(tmp_i7 + 0x16c) = *(uint32_t *)(tmp_i7 + 0x1c);
              *(uint32_t *)(tmp_i7 + 0x170) = *(uint32_t *)(tmp_i7 + 0x20);
              nitrox_AddEntityToEntityArray(&AirstrikeEntities);
            }
            else {
              *(float *)(tmp_i7 + 0x18) = local_1048;
              *(float *)(tmp_i7 + 0x1c) = local_1044;
              *(float *)(tmp_i7 + 0x20) = local_1040;
              tmp_f3 = local_1038 + local_1038 + local_1044;
              tmp_f4 = local_1034 + local_1034 + local_1040;
              if (local_1048 < local_103c + local_103c + local_1048) {
                tmp_f15 = ceilf(local_1048);
                *(float *)(tmp_i7 + 0x18) = tmp_f15;
                if (tmp_f3 <= tmp_f16) goto LAB_001001cf;
LAB_000ffdf2:
                tmp_f16 = ceilf(tmp_f16);
              }
              else {
                tmp_f15 = floorf(local_1048);
                *(float *)(tmp_i7 + 0x18) = tmp_f15;
                if (tmp_f16 < tmp_f3) goto LAB_000ffdf2;
LAB_001001cf:
                tmp_f16 = floorf(tmp_f16);
              }
              *(float *)(tmp_i7 + 0x1c) = tmp_f16;
              if (tmp_f4 <= tmp_f2) {
                tmp_f16 = floorf(tmp_f2);
              }
              else {
                tmp_f16 = ceilf(tmp_f2);
              }
              *(float *)(tmp_i7 + 0x20) = tmp_f16;
              trap_TraceNoEnts(local_1108);
              if (1.0 <= local_104c) goto LAB_000ffe68;
              G_FreeEntity(tmp_i7);
              tmp_f16 = local_10b0;
              tmp_f2 = local_10b4;
              tmp_f3 = local_10ac;
            }
            local_1134 = local_1134 + tmp_f3;
            local_110c = local_110c + tmp_f2;
            local_1128 = local_1128 + tmp_f16;
            tmp_i5 = tmp_i5 + 100;
          } while (tmp_i5 != 1000);
          local_10d8 = local_10d8 + 1;
          if ((int)param_1[0xb9] <= local_10d8) {
            return;
          }
        } while( true );
      }
      if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 2) == 0) {
        if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 4) != 0) {
          tmp_l13 = (long double)
                   BG_GetFromTable(&chargeCost_Artillery,*(int *)(param_1[0x86] + 400) + 0xed0,3);
          tmp_i5 = param_1[0x86];
          if (((tmp_i5 == 0) || (tmp_i7 = *(int *)(tmp_i5 + 400), tmp_i7 == 0)) ||
             (GHIDRA_FIELD(g_noCharge, 12, 4) != 0)) goto LAB_00100222;
          tmp_i5 = *(int *)(tmp_i7 + 0x478);
          tmp_l13 = (long double)0.5 * tmp_l13;
          tmp_l14 = (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i7 + 3000)];
          goto LAB_00100a07;
        }
      }
      else {
        tmp_l14 = (long double)
                 BG_GetFromTable(&chargeCost_Artillery,*(int *)(param_1[0x86] + 400) + 0xed0,3);
        tmp_i5 = param_1[0x86];
        if (((tmp_i5 == 0) || (tmp_i7 = *(int *)(tmp_i5 + 400), tmp_i7 == 0)) ||
           (GHIDRA_FIELD(g_noCharge, 12, 4) != 0)) goto LAB_00100222;
        tmp_i5 = *(int *)(tmp_i7 + 0x478);
        tmp_l13 = (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i7 + 3000)];
LAB_00100a07:
        *(int *)(tmp_i7 + 0x478) = (int)ROUND((long double)tmp_i5 - tmp_l13 * tmp_l14);
      }
      tmp_i5 = param_1[0x86];
      goto LAB_00100222;
    }
    if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 2) == 0) {
      if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 4) == 0) {
LAB_001002c4:
        tmp_i5 = param_1[0x86];
      }
      else {
        tmp_l13 = (long double)
                 BG_GetFromTable(&chargeCost_Artillery,*(int *)(param_1[0x86] + 400) + 0xed0,3);
        tmp_i5 = param_1[0x86];
        if (((tmp_i5 != 0) && (tmp_i7 = *(int *)(tmp_i5 + 400), tmp_i7 != 0)) &&
           (GHIDRA_FIELD(g_noCharge, 12, 4) == 0)) {
          tmp_i5 = *(int *)(tmp_i7 + 0x478);
          tmp_l13 = (long double)0.5 * tmp_l13;
          tmp_l14 = (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i7 + 3000)];
          goto LAB_001008c9;
        }
      }
    }
    else {
      tmp_l14 = (long double)
               BG_GetFromTable(&chargeCost_Artillery,*(int *)(param_1[0x86] + 400) + 0xed0,3);
      tmp_i5 = param_1[0x86];
      if (((tmp_i5 != 0) && (tmp_i7 = *(int *)(tmp_i5 + 400), tmp_i7 != 0)) && (GHIDRA_FIELD(g_noCharge, 12, 4) == 0))
      {
        tmp_i5 = *(int *)(tmp_i7 + 0x478);
        tmp_l13 = (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i7 + 3000)];
LAB_001008c9:
        *(int *)(tmp_i7 + 0x478) = (int)ROUND((long double)tmp_i5 - tmp_l13 * tmp_l14);
        goto LAB_001002c4;
      }
    }
    if ((*(int *)(g_entities + local_1020 * 0x600 + 400) == 0) || ((GHIDRA_FIELD(g_asblock, 12, 4) & 1) == 0))
    goto LAB_00100222;
    tmp_pc10 = "cpm \"%s ^7blocked %s\'^7s airstrike!\"";
    tmp_u17 = CONCAT44(*(int *)(tmp_i5 + 400) + 0x5f8,
                      *(int *)(g_entities + local_1020 * 0x600 + 400) + 0x5f8);
  }
  tmp_u9 = va(tmp_pc10,tmp_u17);
  trap_SendServerCommand(0xffffffff,tmp_u9);
  tmp_i5 = param_1[0x86];
LAB_00100222:
  tmp_i7 = nitrox_TempEventFromQueue(&vec3_origin,0x5c);
  *(uint32_t *)(tmp_i7 + 0xf4) = 1;
  *(uint32_t *)(tmp_i7 + 0x128) = 0x820;
  *(uint32_t *)(tmp_i7 + 0x10c) = 1;
  *(int *)(tmp_i7 + 300) = (tmp_i5 + -0x93e4a0 >> 9) * -0x55555555;
  if (param_1[0x42] == 1) {
    g_unk_02aa2ecc = g_unk_02aa2ecc + -1;
  }
  else {
    g_unk_02aa2ed0 = g_unk_02aa2ed0 + -1;
  }
  param_1[0xda] = 0;
  return;
}

uint G_WeaponIsExplosive(uint32_t param_1)
{
  switch(param_1) {
  case 4:
  case 0xf:
  case 0x10:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x19:
  case 0x1d:
  case 0x1e:
  case 0x23:
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x33:
    return 1;
  default:
    return 0;
  case 0x41:
    return (uint)GHIDRA_FIELD(g_weapons, 12, 4) >> 4 & 1;
  }
}

int G_GetWeaponClassForMOD(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = -1;
  if (param_1 - 4U < 0x30) {
    tmp_i1 = (int)(char)(&UNK_0025c81c)[param_1];
  }
  return tmp_i1;
}

void Weapon_Knife(uint32_t *param_1)
{
  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint8_t local_78 [12];
  uint8_t local_6c [12];
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  uint8_t local_48 [12];
  uint8_t local_3c [20];
  byte local_28;
  int local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x101099;
  AngleVectors(param_1[100] + 0xb0,&forward,&right,&up);
  tmp_i3 = param_1[100];
  tmp_u2 = param_1[0x3a];
  muzzleTrace = (float)param_1[0x5a];
  g_unk_02e432e4 = (float)param_1[0x5b];
  if ((30.0 < *(float *)(tmp_i3 + 0xb0)) && ((*(byte *)(tmp_i3 + 0x68) & 0x10) != 0)) {
    g_unk_02e432e8 = (float)param_1[0x5c] + 30.0;
    if (tmp_u2 < 0x33) goto LAB_0010113d;
_L571:
    muzzleTrace = up * -4.0 + right * 6.0 + muzzleTrace;
    g_unk_02e432e4 = g_unk_02e432fc * -4.0 + g_unk_02e43308 * 6.0 + g_unk_02e432e4;
    g_unk_02e432e8 = g_unk_02e43300 * -4.0 + g_unk_02e4330c * 6.0 + g_unk_02e432e8;
    if (tmp_u2 == 0) goto LAB_0010121b;
    goto LAB_001011d6;
  }
  g_unk_02e432e8 = (float)*(int *)(tmp_i3 + 0xbc) + (float)param_1[0x5c];
  if (0x32 < tmp_u2) goto _L571;
LAB_0010113d:
  switch((int)&_GLOBAL_OFFSET_TABLE_ + (&switchD_00101146::switchdataD_0025beb0)[tmp_u2]) {
  case 0x101160:
    goto _L571;
  case 0x1011d0:
    break;
  case 0x1014c0:
    muzzleTrace = up * -4.0 + right * -6.0 + muzzleTrace;
    g_unk_02e432e4 = g_unk_02e432fc * -4.0 + g_unk_02e43308 * -6.0 + g_unk_02e432e4;
    g_unk_02e432e8 = g_unk_02e43300 * -4.0 + g_unk_02e4330c * -6.0 + g_unk_02e432e8;
    break;
  case 0x101528:
    tmp_f1 = 10.0;
LAB_0010152e:
    muzzleTrace = right * tmp_f1 + muzzleTrace;
    g_unk_02e432e4 = g_unk_02e43308 * tmp_f1 + g_unk_02e432e4;
    g_unk_02e432e8 = tmp_f1 * g_unk_02e4330c + g_unk_02e432e8;
    break;
  case 0x101570:
    tmp_f1 = 20.0;
    goto LAB_0010152e;
  }
LAB_001011d6:
  if (*(float *)(tmp_i3 + 0x3c) != 0.0) {
    AngleVectors(tmp_i3 + 0xb0,&local_60,&local_54,0);
    tmp_f1 = *(float *)(param_1[100] + 0x3c);
    muzzleTrace = local_54 * tmp_f1 + muzzleTrace;
    g_unk_02e432e4 = local_50 * tmp_f1 + g_unk_02e432e4;
    g_unk_02e432e8 = (local_4c * tmp_f1 + g_unk_02e432e8) - ABS(tmp_f1 / 3.5);
  }
LAB_0010121b:
  muzzleTrace = (float)(int)ROUND(muzzleTrace);
  g_unk_02e432e4 = (float)(int)ROUND(g_unk_02e432e4);
  g_unk_02e432e8 = (float)(int)ROUND(g_unk_02e432e8);
  local_60 = forward * 64.0 + muzzleTrace;
  local_5c = g_unk_02e432f0 * 64.0 + g_unk_02e432e4;
  local_58 = g_unk_02e432f4 * 64.0 + g_unk_02e432e8;
  G_HistoricalTrace(param_1,&local_54,&muzzleTrace,0,0,&local_60,*param_1,0x6000001,0);
  if (((local_28 & 0x10) == 0) && (local_4c != 1.0)) {
    if (local_20 < 0x40) {
      tmp_u7 = 0x30;
    }
    else {
      tmp_u7 = 0x31;
    }
    tmp_i3 = nitrox_TempEventFromQueue(local_48,tmp_u7);
    *(int *)(tmp_i3 + 0x8c) = local_20;
    tmp_u7 = DirToByte(local_3c);
    *(uint32_t *)(tmp_i3 + 0xbc) = tmp_u7;
    *(uint32_t *)(tmp_i3 + 0xe8) = param_1[0x3a];
    *(uint32_t *)(tmp_i3 + 0xac) = param_1[0x60];
    if ((local_20 != 0x3fe) && (*(int *)(g_entities + local_20 * 0x600 + 0x2cc) != 0)) {
      tmp_i3 = *(int *)(BG_Weapons + param_1[0x3a] * 0x6b0 + 0x5d4);
      if (tmp_i3 == 0) {
        tmp_i3 = *(int *)(ammoTableMP + param_1[0x3a] * 0x48 + 0x28);
      }
      if (*(int *)(param_1[100] + 0xbc8) == 4) {
        tmp_i3 = tmp_i3 * 2;
      }
      tmp_i6 = local_20 * 0x600;
      tmp_pu4 = g_entities + tmp_i6;
      if (*(int *)(g_entities + tmp_i6 + 400) != 0) {
        AngleVectors(param_1[100] + 0xb0,local_78,0,0);
        AngleVectors(*(int *)(g_entities + tmp_i6 + 400) + 0xb0,local_6c,0,0);
        tmp_i5 = G_GetEnemyPosition(param_1,tmp_pu4);
        if (tmp_i5 == 1) {
          tmp_i3 = *(int *)(g_entities + tmp_i6 + 0x2c8);
          if (tmp_i3 < 1) {
            tmp_i3 = tmp_i3 + 0xaf;
          }
          else if ((*(byte *)(param_1[100] + 0xee8) & 0x10) == 0) {
            tmp_i3 = 100;
          }
          else if ((*(int *)(param_1[100] + 0xbc8) != 4) && ((jp_keepAwards[0xc] & 4) == 0)) {
            tmp_i3 = 100;
          }
          if (((g_entities[local_20 * 0x600 + 0x128] & 8) == 0) &&
             (tmp_i6 = OnSameTeam(param_1,tmp_pu4), tmp_i6 == 0)) {
            nitrox_CheckGlobalAwards(param_1,0xd,1);
          }
        }
      }
      G_Damage(tmp_pu4,param_1,param_1,&forward,local_48,tmp_i3,4,5);
    }
  }
  return;
}

void Weapon_Medic_Ext(uint32_t *param_1,float *param_2,float *param_3,uint32_t param_4)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  long double tmp_l5;
  float tmp_f6;
  float tmp_f7;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint8_t local_54 [4];
  int local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  uint32_t uStack_14;
  
  uStack_14 = 0x1016f9;
  if ((int)GHIDRA_FIELD(n_medPackSinkDelay, 12, 4) < 5000) {
    tmp_i4 = 30000;
  }
  else {
    tmp_i4 = GHIDRA_FIELD(n_medPackSinkDelay, 12, 4);
    if (60000 < (int)GHIDRA_FIELD(n_medPackSinkDelay, 12, 4)) {
      tmp_i4 = 30000;
    }
  }
  tmp_l5 = (long double)BG_GetFromTable(&chargeCost_Health,param_1[100] + 0xed0,2);
  jP_DoChargeCost(param_1,(float)tmp_l5);
  tmp_u1 = BG_FindItemForClassName("item_health");
  tmp_u3 = *param_1;
  local_6c = 0xc1900000;
  local_68 = 0xc1900000;
  local_64 = 0;
  local_60 = 0x41900000;
  local_5c = 0x41900000;
  local_58 = 0x42100000;
  G_TempTraceIgnorePlayersAndBodies();
  trap_Trace(local_54,param_2,&local_6c,&local_60,param_3,tmp_u3,0x6000081);
  G_ResetTempTraceIgnoreEnts();
  if (local_50 == 0) {
    if (local_4c < 1.0) {
      *param_3 = local_48;
      param_3[1] = local_44;
      param_3[2] = local_40;
      tmp_f6 = floorf(local_48);
      tmp_f7 = ceilf(local_48);
      if (local_48 < *param_2) {
        tmp_f6 = tmp_f7;
      }
      *param_3 = tmp_f6;
      tmp_f6 = floorf(local_44);
      tmp_f7 = ceilf(local_44);
      if (local_44 < param_2[1]) {
        tmp_f6 = tmp_f7;
      }
      param_3[1] = tmp_f6;
      tmp_f6 = floorf(local_40);
      tmp_f7 = ceilf(local_40);
      if (local_40 < param_2[2]) {
        tmp_f6 = tmp_f7;
      }
      param_3[2] = tmp_f6;
    }
  }
  else {
    *param_2 = forward;
    param_2[1] = g_unk_02e432f0;
    param_2[2] = g_unk_02e432f4;
    VectorNormalizeFast(param_2);
    *param_2 = *param_2 * -24.0 + (float)param_1[0x5a];
    param_2[1] = param_2[1] * -24.0 + (float)param_1[0x5b];
    param_2[2] = param_2[2] * -24.0 + (float)param_1[0x5c];
    tmp_u3 = *param_1;
    G_TempTraceIgnorePlayersAndBodies();
    trap_Trace(local_54,param_2,&local_6c,&local_60,param_3,tmp_u3,0x6000081);
    G_ResetTempTraceIgnoreEnts();
    *param_3 = local_48;
    param_3[1] = local_44;
    param_3[2] = local_40;
  }
  tmp_i2 = LaunchItem(tmp_u1,param_3,param_4,*param_1,0x1000);
  *(void **)(tmp_i2 + 0x2a4) = MagicSink;
  *(int *)(tmp_i2 + 0x29c) = tmp_i4 + g_unk_00abe908;
  tmp_u3 = *(uint32_t *)(param_1[100] + 3000);
  *(uint32_t **)(tmp_i2 + 0x218) = param_1;
  *(uint32_t *)(tmp_i2 + 0x108) = tmp_u3;
  tmp_u3 = Bot_WeaponGameToBot(param_1[0x3a]);
  Bot_Event_FireWeapon(((int)(param_1 + -0x24f928) >> 9) * -0x55555555,tmp_u3,tmp_i2);
  return;
}

void Weapon_Medic(int param_1)
{
  int tmp_i1;
  float tmp_f2;
  uint tmp_u3;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  float local_24;
  float local_20;
  float local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  tmp_i1 = *(int *)(param_1 + 400);
  local_30 = *(float *)(tmp_i1 + 0xb0);
  local_2c = *(uint32_t *)(tmp_i1 + 0xb4);
  local_28 = *(uint32_t *)(tmp_i1 + 0xb8);
  if (local_30 < -30.0) {
    local_30 = -30.0;
  }
  else if (30.0 < local_30) {
    local_30 = 30.0;
  }
  AngleVectors(&local_30,&local_3c,0,0);
  tmp_f2 = (float)(int)GHIDRA_FIELD(g_throwDistance, 12, 4);
  local_3c = local_3c * tmp_f2;
  local_38 = local_38 * tmp_f2;
  local_34 = tmp_f2 * local_34;
  tmp_u3 = rand();
  tmp_f2 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
  local_34 = (tmp_f2 + tmp_f2) * 25.0 + 50.0 + local_34;
  tmp_i1 = *(int *)(param_1 + 400);
  local_24 = forward * 48.0 + muzzleEffect;
  local_20 = g_unk_02e432f0 * 48.0 + g_unk_02e43314;
  local_1c = g_unk_02e432f4 * 48.0 + g_unk_02e43318;
  local_18 = *(uint32_t *)(tmp_i1 + 0x14);
  local_14 = *(uint32_t *)(tmp_i1 + 0x18);
  local_10 = *(uint32_t *)(tmp_i1 + 0x1c);
  Weapon_Medic_Ext(param_1,&local_18,&local_24,&local_3c);
  return;
}

void G_PlaceTripmine(uint32_t *param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
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
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  
  tmp_i2 = param_1[100];
  local_78 = *(float *)(tmp_i2 + 0x14);
  local_74 = *(float *)(tmp_i2 + 0x18);
  local_70 = (float)*(int *)(tmp_i2 + 0xbc) + *(float *)(tmp_i2 + 0x1c);
  AngleVectors(tmp_i2 + 0xb0,&local_60,0,0);
  local_6c = local_60 * 64.0 + local_78;
  local_68 = local_5c * 64.0 + local_74;
  local_64 = local_58 * 64.0 + local_70;
  trap_Trace(local_54,&local_78,0,0,&local_6c,*param_1,0x6000001);
  tmp_i2 = G_Spawn();
  *(uint32_t *)(tmp_i2 + 0x128) = 0x20;
  *(char **)(tmp_i2 + 0x1a4) = "tripmine";
  *(uint32_t *)(tmp_i2 + 0xe8) = 0x31;
  *(uint32_t *)(tmp_i2 + 4) = 0x22;
  *(uint32_t *)(tmp_i2 + 8) = 0;
  *(uint32_t **)(tmp_i2 + 0x218) = param_1;
  tmp_u3 = GHIDRA_FIELD(BG_Weapons, 85380, 4);
  if (GHIDRA_FIELD(BG_Weapons, 85380, 4) == 0) {
    tmp_u3 = GHIDRA_FIELD(ammoTableMP, 3568, 4);
  }
  *(uint32_t *)(tmp_i2 + 0x2d0) = tmp_u3;
  tmp_u3 = nitrox_GetWeaponSplashDamage(0x31);
  *(uint32_t *)(tmp_i2 + 0x2d4) = tmp_u3;
  tmp_u3 = nitrox_GetWeaponSplashDamageRadius(0x31);
  *(uint32_t *)(tmp_i2 + 0x2e0) = 0x42;
  *(uint32_t *)(tmp_i2 + 0x14c) = 0x4000000;
  *(uint32_t *)(tmp_i2 + 0x2d8) = tmp_u3;
  *(uint32_t *)(tmp_i2 + 0x2dc) = 0x42;
  local_78 = local_48 - local_3c;
  tmp_i1 = *(int *)(param_1[100] + 3000);
  *(uint32_t *)(tmp_i2 + 0x134) = 0xc0800000;
  *(uint32_t *)(tmp_i2 + 0x138) = 0xc0800000;
  *(int *)(tmp_i2 + 0x108) = tmp_i1 + 4;
  local_74 = local_44 - local_38;
  *(uint32_t *)(tmp_i2 + 0x5f8) = 0;
  *(uint32_t *)(tmp_i2 + 0x13c) = 0xc0400000;
  *(uint32_t *)(tmp_i2 + 0x150) = 0xc0800000;
  *(uint32_t *)(tmp_i2 + 0x154) = 0xc0800000;
  *(void **)(tmp_i2 + 0x2a4) = G_FreeEntity;
  tmp_i1 = g_unk_00abe908;
  local_70 = local_40 - local_34;
  *(uint32_t *)(tmp_i2 + 0x158) = 0xc0400000;
  *(uint32_t *)(tmp_i2 + 0x140) = 0x40800000;
  *(uint32_t *)(tmp_i2 + 0x144) = 0x40800000;
  *(int *)(tmp_i2 + 0x29c) = tmp_i1 + 15000;
  *(uint32_t *)(tmp_i2 + 0x148) = 0x40400000;
  *(uint32_t *)(tmp_i2 + 0x15c) = 0x40800000;
  *(uint32_t *)(tmp_i2 + 0x160) = 0x40800000;
  *(uint32_t *)(tmp_i2 + 0x164) = 0x40400000;
  G_SetOrigin(tmp_i2,&local_78);
  G_SetAngle(tmp_i2,&vec3_origin);
  *(float *)(tmp_i2 + 0x68) = local_3c;
  *(float *)(tmp_i2 + 0x6c) = local_38;
  *(float *)(tmp_i2 + 0x70) = local_34;
  nitmod_cp(param_1,0x36);
  nitrox_AddEntityToEntityArray(&TripmineEntities,tmp_i2);
  trap_LinkEntity(tmp_i2);
  return;
}

void Weapon_MagicAmmo_Ext(uint32_t *param_1,float *param_2,float *param_3,uint32_t param_4)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  long double tmp_l6;
  float tmp_f7;
  float tmp_f8;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint8_t local_54 [4];
  int local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  uint32_t uStack_14;
  
  uStack_14 = 0x101ea9;
  if ((int)GHIDRA_FIELD(n_ammoPackSinkDelay, 12, 4) < 5000) {
    tmp_i5 = 30000;
  }
  else {
    tmp_i5 = GHIDRA_FIELD(n_ammoPackSinkDelay, 12, 4);
    if (60000 < (int)GHIDRA_FIELD(n_ammoPackSinkDelay, 12, 4)) {
      tmp_i5 = 30000;
    }
  }
  tmp_l6 = (long double)BG_GetFromTable(&chargeCost_Ammo,param_1[100] + 0xed0,3);
  jP_DoChargeCost(param_1,(float)tmp_l6);
  if ((*(uint *)(param_1[100] + 0xedc) & 0x20) == 0) {
    if ((*(uint *)(param_1[100] + 0xedc) & 2) == 0) {
      tmp_pc2 = "Ammo Pack";
    }
    else {
      tmp_pc2 = "Mega Ammo Pack";
    }
    tmp_u3 = BG_FindItem(tmp_pc2);
  }
  else {
    tmp_u3 = BG_FindItem("Huge Ammo Pack");
  }
  tmp_u1 = *param_1;
  local_6c = 0xc1900000;
  local_68 = 0xc1900000;
  local_64 = 0;
  local_60 = 0x41900000;
  local_5c = 0x41900000;
  local_58 = 0x42100000;
  G_TempTraceIgnorePlayersAndBodies();
  trap_Trace(local_54,param_2,&local_6c,&local_60,param_3,tmp_u1,0x6000081);
  G_ResetTempTraceIgnoreEnts();
  if (local_50 == 0) {
    if (local_4c < 1.0) {
      *param_3 = local_48;
      param_3[1] = local_44;
      param_3[2] = local_40;
      tmp_f7 = floorf(local_48);
      tmp_f8 = ceilf(local_48);
      if (local_48 < *param_2) {
        tmp_f7 = tmp_f8;
      }
      *param_3 = tmp_f7;
      tmp_f7 = floorf(local_44);
      tmp_f8 = ceilf(local_44);
      if (local_44 < param_2[1]) {
        tmp_f7 = tmp_f8;
      }
      param_3[1] = tmp_f7;
      tmp_f7 = floorf(local_40);
      tmp_f8 = ceilf(local_40);
      if (local_40 < param_2[2]) {
        tmp_f7 = tmp_f8;
      }
      param_3[2] = tmp_f7;
    }
  }
  else {
    *param_2 = forward;
    param_2[1] = g_unk_02e432f0;
    param_2[2] = g_unk_02e432f4;
    VectorNormalizeFast(param_2);
    *param_2 = *param_2 * -24.0 + (float)param_1[0x5a];
    param_2[1] = param_2[1] * -24.0 + (float)param_1[0x5b];
    param_2[2] = param_2[2] * -24.0 + (float)param_1[0x5c];
    tmp_u1 = *param_1;
    G_TempTraceIgnorePlayersAndBodies();
    trap_Trace(local_54,param_2,&local_6c,&local_60,param_3,tmp_u1,0x6000081);
    G_ResetTempTraceIgnoreEnts();
    *param_3 = local_48;
    param_3[1] = local_44;
    param_3[2] = local_40;
  }
  tmp_i4 = LaunchItem(tmp_u3,param_3,param_4,*param_1,0x1000);
  tmp_u3 = *(uint32_t *)(param_1[100] + 3000);
  *(uint32_t **)(tmp_i4 + 0x218) = param_1;
  *(uint32_t *)(tmp_i4 + 0x108) = tmp_u3;
  *(void **)(tmp_i4 + 0x2a4) = MagicSink;
  *(int *)(tmp_i4 + 0x29c) = tmp_i5 + g_unk_00abe908;
  tmp_i5 = 2 - (uint)((*(uint *)(param_1[100] + 0xedc) & 2) == 0);
  *(int *)(tmp_i4 + 0xf4) = tmp_i5;
  *(int *)(tmp_i4 + 0x2e4) = tmp_i5;
  tmp_u3 = Bot_WeaponGameToBot(param_1[0x3a]);
  Bot_Event_FireWeapon(((int)(param_1 + -0x24f928) >> 9) * -0x55555555,tmp_u3,tmp_i4);
  return;
}

void Weapon_MagicAmmo(int param_1)
{
  int tmp_i1;
  float tmp_f2;
  uint tmp_u3;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  float local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  tmp_i1 = *(int *)(param_1 + 400);
  local_18 = *(float *)(tmp_i1 + 0xb0);
  local_14 = *(uint32_t *)(tmp_i1 + 0xb4);
  local_10 = *(uint32_t *)(tmp_i1 + 0xb8);
  if (local_18 < -30.0) {
    local_18 = -30.0;
  }
  else if (30.0 < local_18) {
    local_18 = 30.0;
  }
  AngleVectors(&local_18,&local_3c,0,0);
  tmp_f2 = (float)(int)GHIDRA_FIELD(g_throwDistance, 12, 4);
  local_3c = local_3c * tmp_f2;
  local_38 = local_38 * tmp_f2;
  local_34 = tmp_f2 * local_34;
  tmp_u3 = rand();
  tmp_f2 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
  local_34 = (tmp_f2 + tmp_f2) * 25.0 + 50.0 + local_34;
  tmp_i1 = *(int *)(param_1 + 400);
  local_30 = forward * 48.0 + muzzleEffect;
  local_2c = g_unk_02e432f0 * 48.0 + g_unk_02e43314;
  local_28 = g_unk_02e432f4 * 48.0 + g_unk_02e43318;
  local_24 = *(uint32_t *)(tmp_i1 + 0x14);
  local_20 = *(uint32_t *)(tmp_i1 + 0x18);
  local_1c = *(uint32_t *)(tmp_i1 + 0x1c);
  Weapon_MagicAmmo_Ext(param_1,&local_24,&local_30,&local_3c);
  return;
}

int Weapon_Syringe(uint32_t *param_1)
{
  int *tmp_pi1;
  float tmp_f2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  uint tmp_u5;
  int tmp_i6;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  int local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x102d29;
  AngleVectors(param_1[100] + 0xb0,&forward,&right,&up);
  muzzleTrace = (float)param_1[6];
  g_unk_02e432e4 = (float)param_1[7];
  tmp_f2 = (float)param_1[8];
  if ((int)param_1[0xb2] < 1) {
    g_unk_02e432e8 = tmp_f2 + 25.0;
    tmp_i4 = param_1[100];
    if (tmp_i4 == 0) goto LAB_00102def;
  }
  else {
    tmp_i4 = param_1[100];
    if ((*(float *)(tmp_i4 + 0xb0) <= 30.0) || ((*(byte *)(tmp_i4 + 0x68) & 0x10) == 0)) {
      g_unk_02e432e8 = (float)*(int *)(tmp_i4 + 0xbc) + tmp_f2;
    }
    else {
      g_unk_02e432e8 = tmp_f2 + 30.0;
    }
  }
  if (*(float *)(tmp_i4 + 0x3c) != 0.0) {
    AngleVectors(tmp_i4 + 0xb0,&local_60,&local_54,0);
    tmp_f2 = *(float *)(param_1[100] + 0x3c);
    muzzleTrace = local_54 * tmp_f2 + muzzleTrace;
    g_unk_02e432e4 = local_50 * tmp_f2 + g_unk_02e432e4;
    g_unk_02e432e8 = (local_4c * tmp_f2 + g_unk_02e432e8) - ABS(tmp_f2 / 3.5);
  }
LAB_00102def:
  local_60 = forward * 64.0 + muzzleTrace;
  local_5c = g_unk_02e432f0 * 64.0 + g_unk_02e432e4;
  local_58 = g_unk_02e432f4 * 64.0 + g_unk_02e432e8;
  G_HistoricalTrace(param_1,&local_54,&muzzleTrace,0,0,&local_60,*param_1,0x6000001,0);
  if (local_50 != 0.0) {
    local_60 = forward * 8.0 + muzzleTrace;
    local_5c = g_unk_02e432f0 * 8.0 + g_unk_02e432e4;
    local_58 = g_unk_02e432f4 * 8.0 + g_unk_02e432e8;
    G_HistoricalTrace(param_1,&local_54,&muzzleTrace,0,0,&local_60,*param_1,0x6000001,0);
  }
  if (local_4c != 1.0) {
    tmp_i6 = local_20 * 0x600;
    tmp_pu3 = g_entities + tmp_i6;
    tmp_pi1 = (int *)(g_entities + tmp_i6 + 400);
    tmp_i4 = *tmp_pi1;
    if (tmp_i4 == 0) {
      return 0;
    }
    if (*(int *)(tmp_i4 + 4) == 3) {
      if (*(int *)(tmp_i4 + 3000) != *(int *)(param_1[100] + 3000)) {
        return 0;
      }
      if ((*(byte *)(tmp_i4 + 0x6a) & 0x80) != 0) {
        return 0;
      }
      tmp_i4 = ReviveEntity(param_1,tmp_pu3);
      if ((param_1[100] != 0) &&
         (G_LogPrintf("Medic_Revive: %d %d\n",((int)(param_1 + -0x24f928) >> 9) * -0x55555555,
                      (tmp_i6 >> 9) * -0x55555555), (g_entities[tmp_i6 + 0x128] & 8) == 0)) {
        nitrox_CheckGlobalAwards(param_1,4,1);
      }
      if (*(int *)(g_entities + local_20 * 0x600 + 900) == 0) {
        AddScore(param_1,2);
        G_AddSkillPoints(param_1,2,0x40800000);
        if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
          G_DebugAddSkillPoints(param_1,2,0x40800000,"reviving a player");
        }
      }
      if (tmp_i4 != 0) {
        *(float *)(param_1[100] + 0xc9c) = *(float *)(param_1[100] + 0xc9c) - 2.0;
      }
      if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
        CalculateRanks(0);
        return tmp_i4;
      }
      return tmp_i4;
    }
    if ((*(uint *)(tmp_i4 + 0x68) & 0x200000) == 0) {
      if ((g_medics[0xc] & 8) == 0) {
        return 0;
      }
    }
    else {
      if (*(int *)(tmp_i4 + 3000) != *(int *)(param_1[100] + 3000)) {
        return 0;
      }
      *(uint *)(tmp_i4 + 0x68) = *(uint *)(tmp_i4 + 0x68) & 0xffdfffff;
      *(uint32_t *)(*tmp_pi1 + 0x5304) = 0;
      nitmod_SoundEvent(tmp_pu3,8);
      if ((g_medics[0xc] & 8) == 0) {
        return 1;
      }
      tmp_i4 = *tmp_pi1;
    }
    if (*(int *)(tmp_i4 + 3000) == *(int *)(param_1[100] + 3000)) {
      tmp_i4 = *(int *)(tmp_i4 + 0xe0);
      if ((float)*(int *)(g_entities + local_20 * 0x600 + 0x2c8) <= (float)tmp_i4 * 0.25) {
        if ((*(byte *)(param_1[100] + 0xed8) & 8) == 0) {
          tmp_i4 = (int)ROUND((float)tmp_i4 * 0.5);
        }
        tmp_i6 = local_20 * 0x600;
        *(int *)(g_entities + tmp_i6 + 0x2c8) = tmp_i4;
        nitmod_SoundEvent(tmp_pu3,8);
        *(float *)(param_1[100] + 0xc9c) = *(float *)(param_1[100] + 0xc9c) - 2.0;
        *(uint32_t *)(*(int *)(g_entities + tmp_i6 + 400) + 0x9d4) = param_1[0x2b];
        if (*(int *)(g_entities + tmp_i6 + 900) == 0) {
          AddScore(param_1,1);
          G_AddSkillPoints(param_1,2,0x40000000);
          if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
            G_DebugAddSkillPoints(param_1,2,0x40000000,"syringe heal a player");
          }
        }
        tmp_u5 = GHIDRA_FIELD(n_reviveSpreeOptions, 12, 4);
        if ((GHIDRA_FIELD(n_reviveSpreeOptions, 12, 4) & 2) != 0) {
          *(int *)(param_1[100] + 0xb94) = *(int *)(param_1[100] + 0xb94) + 1;
          tmp_i4 = param_1[100];
          tmp_i6 = *(int *)(tmp_i4 + 0xb94);
          if (*(int *)(tmp_i4 + 0xb98) < tmp_i6) {
            *(int *)(tmp_i4 + 0xb98) = tmp_i6;
            tmp_i6 = *(int *)(param_1[100] + 0xb94);
          }
          if ((4 < tmp_i6) && (tmp_i6 == (tmp_i6 / 5) * 5)) {
            nitmod_Announce(((int)(param_1 + -0x24f928) >> 9) * -0x55555555,tmp_i6,4);
            tmp_u5 = GHIDRA_FIELD(n_reviveSpreeOptions, 12, 4);
          }
        }
        tmp_i4 = g_unk_00abe908;
        if ((tmp_u5 & 0x10) != 0) {
          if ((int)GHIDRA_FIELD(n_multiReviveTime, 12, 4) < 1) {
            tmp_i6 = param_1[100];
          }
          else {
            tmp_i6 = param_1[100];
            if ((int)GHIDRA_FIELD(n_multiReviveTime, 12, 4) < g_unk_00abe908 - *(int *)(tmp_i6 + 0x53b4)) {
              *(uint32_t *)(tmp_i6 + 0x53b8) = 1;
              tmp_i6 = param_1[100];
            }
            else {
              *(int *)(tmp_i6 + 0x53b8) = *(int *)(tmp_i6 + 0x53b8) + 1;
              tmp_i6 = param_1[100];
              tmp_u5 = *(int *)(tmp_i6 + 0x53b8) - 2;
              if (tmp_u5 < 4) {
                nitmod_Announce(((int)(param_1 + -0x24f928) >> 9) * -0x55555555,tmp_u5,5);
                tmp_i6 = param_1[100];
                tmp_i4 = g_unk_00abe908;
              }
              else if (5 < *(int *)(tmp_i6 + 0x53b8)) {
                *(uint32_t *)(tmp_i6 + 0x53b8) = 1;
                tmp_i6 = param_1[100];
              }
            }
          }
          *(int *)(tmp_i6 + 0x53b4) = tmp_i4;
        }
        return 1;
      }
    }
  }
  return 0;
}

uint32_t Weapon_Poison(uint32_t *param_1)
{
  int *tmp_pi1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint32_t tmp_u6;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  int local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x103529;
  AngleVectors(param_1[100] + 0xb0,&forward,&right,&up);
  muzzleTrace = (float)param_1[6];
  g_unk_02e432e4 = (float)param_1[7];
  tmp_f2 = (float)param_1[8];
  if ((int)param_1[0xb2] < 1) {
    g_unk_02e432e8 = tmp_f2 + 25.0;
    tmp_i3 = param_1[100];
    if (tmp_i3 != 0) goto LAB_001035d0;
  }
  else {
    tmp_i3 = param_1[100];
    if ((*(float *)(tmp_i3 + 0xb0) <= 30.0) || ((*(byte *)(tmp_i3 + 0x68) & 0x10) == 0)) {
      g_unk_02e432e8 = (float)*(int *)(tmp_i3 + 0xbc) + tmp_f2;
    }
    else {
      g_unk_02e432e8 = tmp_f2 + 30.0;
    }
LAB_001035d0:
    if (*(float *)(tmp_i3 + 0x3c) != 0.0) {
      AngleVectors(tmp_i3 + 0xb0,&local_60,&local_54,0);
      tmp_f2 = *(float *)(param_1[100] + 0x3c);
      muzzleTrace = local_54 * tmp_f2 + muzzleTrace;
      g_unk_02e432e4 = local_50 * tmp_f2 + g_unk_02e432e4;
      g_unk_02e432e8 = (local_4c * tmp_f2 + g_unk_02e432e8) - ABS(tmp_f2 / 3.5);
    }
  }
  local_60 = forward * 64.0 + muzzleTrace;
  local_5c = g_unk_02e432f0 * 64.0 + g_unk_02e432e4;
  local_58 = g_unk_02e432f4 * 64.0 + g_unk_02e432e8;
  G_HistoricalTrace(param_1,&local_54,&muzzleTrace,0,0,&local_60,*param_1,0x6000001,0);
  tmp_i3 = local_20;
  if (((local_4c == 1.0) || (0x3f < local_20)) ||
     (tmp_i4 = local_20 * 0x600, g_unk_00abe908 <= *(int *)(*(int *)(g_entities + tmp_i4 + 400) + 0x154)
     )) {
LAB_00103760:
    tmp_u6 = 0;
  }
  else {
    if (((g_friendlyFire[0xc] & 1) == 0) && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) {
      tmp_i5 = OnSameTeam(param_1,g_entities + tmp_i4);
      if (tmp_i5 != 0) goto LAB_00103760;
      if (local_20 < 0x40) goto LAB_001036ba;
    }
    else {
LAB_001036ba:
      nitmod_SoundEvent(g_entities + tmp_i4,8);
    }
    tmp_pi1 = (int *)(g_entities + tmp_i3 * 0x600 + 400);
    tmp_i3 = *tmp_pi1;
    if ((*(uint *)(tmp_i3 + 0x68) & 0x200000) == 0) {
      *(uint *)(tmp_i3 + 0x68) = *(uint *)(tmp_i3 + 0x68) | 0x200000;
      *(uint32_t *)(*tmp_pi1 + 0x5300) = *param_1;
      *(int *)(*tmp_pi1 + 0x53a0) = g_unk_00abe908;
      *(uint32_t *)(*tmp_pi1 + 0x5304) = 1;
      return 1;
    }
    *(uint32_t *)(tmp_i3 + 0x5300) = *param_1;
    *(int *)(*tmp_pi1 + 0x5304) = *(int *)(*tmp_pi1 + 0x5304) + 1;
    tmp_u6 = 1;
  }
  return tmp_u6;
}

bool G_LandmineTriggered(int param_1)
{
  return *(int *)(param_1 + 0x108) - 9U < 2;
}

bool G_LandmineArmed(int param_1)
{
  return *(int *)(param_1 + 0x108) - 1U < 2;
}

bool G_LandmineUnarmed(int param_1)
{
  if (*(int *)(param_1 + 0x108) - 1U < 2) {
    return false;
  }
  return 1 < *(int *)(param_1 + 0x108) - 9U;
}

int G_LandmineTeam(int param_1)
{
  return *(int *)(param_1 + 0x108) % 4;
}

bool G_LandmineSpotted(int param_1)
{
  return *(int *)(param_1 + 0xa8) != 0;
}

void trap_EngineerTrace(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
                       uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  G_TempTraceIgnorePlayersAndBodies();
  trap_Trace(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  G_ResetTempTraceIgnoreEnts();
  return;
}

uint8_t * Weapon_Engineer(uint32_t *param_1)
{
  float *pfVar1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint tmp_u6;
  bool tmp_b7;
  bool tmp_b8;
  float *pfVar9;
  int tmp_i10;
  uint32_t tmp_u11;
  char *tmp_pc12;
  int tmp_i13;
  int tmp_i14;
  int tmp_i15;
  float *pfVar16;
  uint32_t tmp_u17;
  uint8_t *tmp_pu18;
  int tmp_i19;
  int *tmp_pi20;
  int *tmp_pi21;
  uint8_t *tmp_pu22;
  int tmp_i23;
  bool tmp_b24;
  bool tmp_b25;
  long double tmp_l26;
  int local_20d4;
  int local_20d0;
  int local_20cc;
  float *local_20c8;
  int local_20c4;
  int local_2088;
  float local_2084;
  float local_2080;
  float local_207c;
  float local_2078;
  float local_2074;
  float local_2070;
  float local_206c;
  float local_2068;
  float local_2064;
  float local_2060;
  float local_205c;
  float local_2058;
  float local_2054;
  float local_2050;
  float local_204c;
  byte local_2028;
  float *local_2020;
  int local_201c [2];
  float local_2014;
  float local_101c [11];
  int local_ff0;
  int local_fe8;
  
  pfVar9 = (float *)param_1[100];
  if (pfVar9[0x50] != 0.0) {
    return (uint8_t *)pfVar9;
  }
  tmp_f5 = pfVar9[0x40f];
  if (((tmp_f5 != 0.0) && (tmp_pi21 = *(int **)((int)tmp_f5 + 0x264), g_unk_00abe8ac == 0)) &&
     (tmp_pi21[1] == 0x20)) {
    if (*(int **)((int)tmp_f5 + 0x2e8) != (int *)0x0) {
      tmp_pi20 = *(int **)((int)tmp_f5 + 0x2e8);
      if ((float)tmp_pi21[0x42] == pfVar9[0x2ee]) {
        tmp_pi20 = tmp_pi21;
      }
      tmp_i10 = tmp_pi20[0xba];
      if ((((*(float *)(tmp_i10 + 0x80) != 0.0) || (*(float *)(tmp_i10 + 0x84) != 0.0)) ||
          ((*(int *)(tmp_i10 + 0x39c) != 0 && (*(int *)(tmp_i10 + 0x3a4) != 0)))) ||
         (tmp_pi21 = tmp_pi20, tmp_pi20[1] != 0x20)) goto LAB_001045e0;
    }
    if ((((float)tmp_pi21[0x42] == pfVar9[0x2ee]) && ((float)tmp_pi21[0x20] < 250.0)) &&
       ((float)tmp_pi21[0x21] == 0.0)) {
      tmp_i10 = ReadyToConstruct(param_1,tmp_pi21,1);
      if (tmp_i10 == 0) {
        return (uint8_t *)(float *)0x0;
      }
      if ((float)tmp_pi21[0x20] <= 0.0) {
        if ((int)g_unk_00abe908 - tmp_pi21[0x112] < 500) {
          return (uint8_t *)(float *)((int)g_unk_00abe908 - tmp_pi21[0x112]);
        }
        if (tmp_pi21[0xe7] != 0) {
          tmp_i10 = tmp_pi21[0xe9];
          tmp_pi21[0xe9] = tmp_i10 + 1;
          tmp_pi21[0x2a] = tmp_pi21[tmp_i10 + 0x11a];
        }
        G_SetEntState(tmp_pi21,2);
        tmp_pc12 = "final";
        if (tmp_pi21[0xe7] == 0) {
LAB_00105cb4:
          G_Script_ScriptEvent(tmp_pi21,"buildstart",tmp_pc12);
          tmp_pi21[0x2c] = 1;
        }
        else {
          tmp_i10 = tmp_pi21[0xe9];
          if (tmp_pi21[0xe7] == tmp_i10) {
            G_Script_ScriptEvent(tmp_pi21,"buildstart","final");
            tmp_pi21[0x2c] = tmp_pi21[0xe9];
          }
          else if (tmp_i10 == 2) {
            G_Script_ScriptEvent(tmp_pi21,"buildstart","stage2");
            tmp_pi21[0x2c] = 2;
          }
          else if (tmp_i10 == 3) {
            G_Script_ScriptEvent(tmp_pi21,"buildstart","stage3");
            tmp_pi21[0x2c] = 3;
          }
          else if (tmp_i10 == 1) {
            tmp_pc12 = "stage1";
            goto LAB_00105cb4;
          }
        }
        tmp_i10 = tmp_pi21[0x86];
        local_101c[0] = (*(float *)(tmp_i10 + 0x150) + *(float *)(tmp_i10 + 0x15c)) * 0.5;
        local_101c[1] = (*(float *)(tmp_i10 + 0x154) + *(float *)(tmp_i10 + 0x160)) * 0.5;
        local_101c[2] = (*(float *)(tmp_i10 + 0x158) + *(float *)(tmp_i10 + 0x164)) * 0.5;
        tmp_i10 = nitrox_TempEventFromQueue(local_101c,100);
        *(uint32_t *)(tmp_i10 + 0xbc) = 6;
        if ((*(int *)(*(int *)(param_1[100] + 0x103c) + 0x2e8) != 0) &&
           (tmp_i10 = *(int *)(*(int *)(param_1[100] + 0x103c) + 0x39c), tmp_i10 != 0)) {
          tmp_i10 = tmp_i10 * 0x600;
          tmp_i19 = tmp_pi21[0x42];
          *(int *)(g_entities + tmp_i10 + 0x108) = tmp_i19;
          if (tmp_i19 == 1) {
            tmp_pu22 = (uint8_t *)0x2d8ca94;
          }
          else {
            tmp_pu22 = mapEntityData;
          }
          tmp_i10 = G_FindMapEntityData(tmp_pu22,(tmp_i10 >> 9) * -0x55555555);
          if (tmp_i10 != 0) {
            G_FreeMapEntityData(tmp_pu22,tmp_i10);
          }
        }
        if ((tmp_pi21[0xe7] == 0) || (tmp_pi21[0xe9] == 1)) {
          G_UseEntity(tmp_pi21,*(uint32_t *)(param_1[100] + 0x103c),param_1);
        }
        tmp_pi21[0xa9] = (int)func_constructible_underconstructionthink;
        tmp_pi21[0xa7] = (int)(g_unk_00abe908 + 0x19);
        nitmod_cp(param_1,0x2c);
      }
      if (GHIDRA_FIELD(g_constructiblexpsharing, 12, 4) == 0) {
        tmp_f5 = 255.0 / ((float)tmp_pi21[0x13e] / 100.0) + (float)tmp_pi21[0x20];
        tmp_pi21[0x20] = (int)tmp_f5;
      }
      else {
        tmp_f5 = 255.0 / ((float)tmp_pi21[0x13e] / 100.0);
        tmp_f2 = (float)tmp_pi21[0x13a] / (255.0 / tmp_f5) + 0.01;
        G_AddSkillPoints(param_1,1,tmp_f2);
        if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
          G_DebugAddSkillPoints(param_1,1,tmp_f2,"construction sharing.");
        }
        tmp_f5 = tmp_f5 + (float)tmp_pi21[0x20];
        tmp_pi21[0x20] = (int)tmp_f5;
      }
      if (tmp_f5 < 250.0) {
        tmp_pi21[0x112] = (int)g_unk_00abe908;
        tmp_i10 = tmp_pi21[0x29];
        tmp_i19 = tmp_pi21[0x75];
        tmp_i14 = tmp_pi21[0x53];
        tmp_u6 = tmp_pi21[2];
        tmp_u11 = va(&g_unk_0024d859,tmp_pi21[0x2a]);
        trap_SetBrushModel(tmp_pi21,tmp_u11);
        tmp_pi21[0x75] = tmp_i19;
        tmp_pi21[0x53] = tmp_i14;
        if ((tmp_u6 & 2) == 0) {
          tmp_pi21[2] = tmp_pi21[2] & 0xfffffffd;
        }
        trap_LinkEntity(tmp_pi21);
        tmp_pi21[0x1a] = (int)(((float)tmp_pi21[0x54] + (float)tmp_pi21[0x57]) * 0.5);
        tmp_pi21[0x1b] = (int)(((float)tmp_pi21[0x55] + (float)tmp_pi21[0x58]) * 0.5);
        tmp_pi21[0x1c] = (int)(((float)tmp_pi21[0x56] + (float)tmp_pi21[0x59]) * 0.5);
        if (((char *)tmp_pi21[0xea] == (char *)0x0) || (*(char *)tmp_pi21[0xea] == '\0')) {
          local_20d0 = trap_EntitiesInBox(tmp_pi21 + 0x54,tmp_pi21 + 0x57,local_101c,0x400);
          if (tmp_pi21[0x116] == 2) {
            tmp_pi21[0x75] = tmp_pi21[0x76];
            tmp_pi21[0x53] = tmp_pi21[0x77];
            if (tmp_pi21[0x78] == 0) {
              tmp_pi21[2] = tmp_pi21[2] & 0xfffffffd;
            }
          }
          trap_LinkEntity(tmp_pi21);
          local_20c4 = 0;
        }
        else {
          tmp_pi20 = (int *)0x0;
          local_20cc = 0;
          local_2060 = (float)tmp_pi21[0x54];
          local_205c = (float)tmp_pi21[0x55];
          local_2058 = (float)tmp_pi21[0x56];
          local_2054 = (float)tmp_pi21[0x57];
          local_2050 = (float)tmp_pi21[0x58];
          local_204c = (float)tmp_pi21[0x59];
          while( true ) {
            do {
              tmp_pi20 = (int *)G_Find(tmp_pi20,0x3a8,tmp_pi21[0xea]);
            } while (tmp_pi21 == tmp_pi20);
            if (tmp_pi20 == (int *)0x0) break;
            if ((tmp_pi21[0xe7] == 0) || (tmp_pi20[0x121] == tmp_pi21[0xe9])) {
              AddPointToBounds(tmp_pi20 + 0x54,&local_2060,&local_2054);
              AddPointToBounds(tmp_pi20 + 0x57,&local_2060,&local_2054);
              local_201c[local_20cc] = *tmp_pi20;
              local_20cc = local_20cc + 1;
            }
          }
          local_20c4 = local_20cc;
          local_20d0 = trap_EntitiesInBox(&local_2060,&local_2054,local_101c,0x400);
          if (tmp_pi21[0x116] == 2) {
            tmp_pi21[0x75] = tmp_pi21[0x76];
            tmp_pi21[0x53] = tmp_pi21[0x77];
            if (tmp_pi21[0x78] == 0) {
              tmp_pi21[2] = tmp_pi21[2] & 0xfffffffd;
            }
          }
          trap_LinkEntity(tmp_pi21);
          if (local_20cc != 0) {
            tmp_i23 = 0;
            do {
              tmp_i13 = local_201c[tmp_i23] * 0x600;
              if (*(int *)(g_entities + tmp_i13 + 0x458) == 2) {
                *(uint32_t *)(g_entities + tmp_i13 + 0x1d4) =
                     *(uint32_t *)(g_entities + tmp_i13 + 0x1d8);
                *(uint32_t *)(g_entities + tmp_i13 + 0x14c) =
                     *(uint32_t *)(g_entities + tmp_i13 + 0x1dc);
                if (*(int *)(g_entities + tmp_i13 + 0x1e0) == 0) {
                  *(uint *)(g_entities + tmp_i13 + 8) =
                       *(uint *)(g_entities + tmp_i13 + 8) & 0xfffffffd;
                }
              }
              tmp_i23 = tmp_i23 + 1;
              trap_LinkEntity(g_entities + tmp_i13);
            } while (tmp_i23 != local_20cc);
          }
        }
        if (0 < local_20d0) {
          tmp_i23 = 0;
          do {
            tmp_i13 = (int)local_101c[tmp_i23] * 0x600;
            if (((*(int *)(g_entities + tmp_i13 + 4) - 1U < 3) ||
                (*(int *)(g_entities + tmp_i13 + 0x1cc) != 0)) &&
               (tmp_i13 = (int)local_101c[tmp_i23] * 0x600,
               *(int *)(g_entities + tmp_i13 + 0x14c) != 0x4000000)) {
              tmp_i15 = G_TestEntityPosition(g_entities + tmp_i13);
              if (((tmp_i15 != 0) && (*(int *)(g_entities + tmp_i13 + 4) == 1)) &&
                 (tmp_pi20 = (int *)(g_entities + tmp_i13 + 400),
                 4999 < (int)g_unk_00abe908 - *(int *)(*tmp_pi20 + 0x1040))) {
                nitmod_cp(g_entities + tmp_i13,2);
                *(int *)(*tmp_pi20 + 0x1044) = ((int)(tmp_pi21 + -0x24f928) >> 9) * -0x55555555;
                *(float **)(*tmp_pi20 + 0x1040) = g_unk_00abe908;
              }
            }
            tmp_i23 = tmp_i23 + 1;
          } while (tmp_i23 != local_20d0);
        }
        tmp_pi21[0x116] = 2;
        tmp_pi21[0x39] = 2;
        tmp_pi21[0x76] = tmp_pi21[0x75];
        tmp_pi21[0x75] = 0;
        tmp_pi21[0x77] = tmp_pi21[0x53];
        tmp_pi21[0x53] = 0;
        if ((tmp_pi21[2] & 2U) == 0) {
          tmp_pi21[2] = tmp_pi21[2] | 2;
        }
        else {
          tmp_pi21[0x78] = 1;
        }
        trap_LinkEntity(tmp_pi21);
        if ((((char *)tmp_pi21[0xea] != (char *)0x0) && (*(char *)tmp_pi21[0xea] != '\0')) &&
           (local_20c4 != 0)) {
          local_20d4 = 0;
          do {
            tmp_i23 = local_201c[local_20d4] * 0x600;
            *(uint32_t *)(g_entities + tmp_i23 + 0x458) = 2;
            *(uint32_t *)(g_entities + tmp_i23 + 0xe4) = 2;
            tmp_u11 = *(uint32_t *)(g_entities + tmp_i23 + 0x1d4);
            *(uint32_t *)(g_entities + tmp_i23 + 0x1d4) = 0;
            *(uint32_t *)(g_entities + tmp_i23 + 0x1d8) = tmp_u11;
            *(uint32_t *)(g_entities + tmp_i23 + 0x1dc) =
                 *(uint32_t *)(g_entities + tmp_i23 + 0x14c);
            *(uint32_t *)(g_entities + tmp_i23 + 0x14c) = 0;
            if ((*(uint *)(g_entities + tmp_i23 + 8) & 2) == 0) {
              *(uint *)(g_entities + tmp_i23 + 8) = *(uint *)(g_entities + tmp_i23 + 8) | 2;
            }
            else {
              *(uint32_t *)(g_entities + tmp_i23 + 0x1e0) = 1;
            }
            trap_LinkEntity(g_entities + tmp_i23);
            local_20d4 = local_20d4 + 1;
          } while (local_20d4 != local_20c4);
        }
        if (tmp_i10 == 0) {
          tmp_pi21[0x29] = 0;
        }
        else {
          tmp_u11 = va(&g_unk_0024d859,tmp_i10);
          trap_SetBrushModel(tmp_pi21,tmp_u11);
          tmp_pi21[0x75] = tmp_i19;
          tmp_pi21[0x53] = tmp_i14;
          if ((tmp_u6 & 2) == 0) {
            tmp_pi21[2] = tmp_pi21[2] & 0xfffffffd;
          }
        }
        pfVar9 = (float *)trap_LinkEntity(tmp_pi21);
        return (uint8_t *)pfVar9;
      }
      tmp_pi21[0x20] = 0;
      HandleEntsThatBlockConstructible_constprop_7();
      if (tmp_pi21[0xe7] == 0) {
        tmp_i10 = tmp_pi21[0x53];
        tmp_pi21[0x2a] = 0;
        tmp_i19 = tmp_pi21[0x75];
        tmp_u6 = tmp_pi21[2];
        trap_SetBrushModel(tmp_pi21,tmp_pi21[0x6d]);
        tmp_pi21[0x53] = tmp_i10;
        tmp_pi21[0x75] = tmp_i19;
        if ((tmp_u6 & 2) == 0) {
          tmp_pi21[2] = tmp_pi21[2] & 0xfffffffd;
        }
        tmp_pi21[0x21] = 0x3f800000;
        nitmod_objective(4,2,*(uint32_t *)(param_1[100] + 0x103c),param_1,0);
        nitrox_CheckGlobalAwards(param_1,9,1);
      }
      else {
        tmp_u6 = tmp_pi21[2];
        tmp_i10 = tmp_pi21[0x75];
        tmp_i19 = tmp_pi21[0x53];
        tmp_pi21[0x2a] = 0;
        tmp_u11 = va(&g_unk_0024d859,tmp_pi21[tmp_pi21[0xe9] + 0x119]);
        trap_SetBrushModel(tmp_pi21,tmp_u11);
        tmp_pi21[0x75] = tmp_i10;
        tmp_pi21[0x53] = tmp_i19;
        if ((tmp_u6 & 2) == 0) {
          tmp_pi21[2] = tmp_pi21[2] & 0xfffffffd;
        }
        if (tmp_pi21[0xe9] == tmp_pi21[0xe7]) {
          tmp_pi21[0x21] = 0x3f800000;
        }
      }
      AddScore(param_1,(int)ROUND((float)tmp_pi21[0xff]));
      if ((GHIDRA_FIELD(g_constructiblexpsharing, 12, 4) == 0) &&
         (G_AddSkillPoints(param_1,1,tmp_pi21[0x13a]), GHIDRA_FIELD(g_debugSkills, 12, 4) != 0)) {
        G_DebugAddSkillPoints(param_1,1,tmp_pi21[0x13a],"finishing a construction");
      }
      G_SetEntState(tmp_pi21,0);
      if ((*(byte *)(tmp_pi21 + 0x6a) & 2) == 0) {
        tmp_pi21[0xb3] = 1;
        tmp_pi21[0xb2] = tmp_pi21[0x7b];
      }
      tmp_pi21[0xa9] = 0;
      tmp_pi21[0xa7] = 0;
      if ((tmp_pi21[0xe7] == 0) || (tmp_i10 = tmp_pi21[0xe9], tmp_pi21[0xe7] == tmp_i10)) {
        tmp_pc12 = "final";
      }
      else if (tmp_i10 == 2) {
        tmp_pc12 = "stage2";
      }
      else if (tmp_i10 == 3) {
        tmp_pc12 = "stage3";
      }
      else {
        if (tmp_i10 != 1) goto LAB_001049c9;
        tmp_pc12 = "stage1";
      }
      G_Script_ScriptEvent(tmp_pi21,"built",tmp_pc12);
LAB_001049c9:
      pfVar9 = (float *)tmp_pi21[0x86];
      if (((uint)pfVar9[0x6a] & 8) == 0) {
        pfVar9 = (float *)0x0;
        tmp_pi21[0x28] = 0;
      }
      else {
        pfVar9[0x28] = 0.0;
      }
      if (((*(byte *)(tmp_pi21 + 0x6a) & 2) == 0) &&
         (pfVar9 = (float *)tmp_pi21[0x13d], 0 < (int)pfVar9)) {
        if ((tmp_pi21[0xe7] == 0) || (tmp_pi21[0xe9] == 1)) {
          tmp_i19 = BG_StringHashValue(tmp_pi21[0x96]);
          tmp_i14 = G_Spawn();
          nitrox_AddEntityToEntityArray(&IndicatorEntities,tmp_i14);
          *(char **)(tmp_i14 + 0x1a4) = "explosive_indicator";
          tmp_i10 = TriggerEntities;
          *(uint32_t *)(tmp_i14 + 0x128) = 0x20;
          *(uint32_t *)(tmp_i14 + 0xc) = 0;
          *(uint32_t *)(tmp_i14 + 4) = 0xd;
          tmp_i23 = 0;
          if (0 < tmp_i10) {
            do {
              tmp_i13 = (&g_unk_0087ea44)[tmp_i23];
              if (((tmp_i19 == *(int *)(tmp_i13 + 0x5bc)) &&
                  (tmp_i15 = Q_stricmp(*(uint32_t *)(tmp_i13 + 0x254),tmp_pi21[0x96]),
                  tmp_i10 = TriggerEntities, tmp_i15 == 0)) && (*(int *)(tmp_i13 + 4) == 0xc)) {
                if ((*(byte *)(tmp_i13 + 0x1a8) & 8) != 0) {
                  *(uint32_t *)(tmp_i14 + 4) = 0x24;
                }
                *(int *)(tmp_i14 + 0x218) = tmp_i13;
                tmp_i10 = TriggerEntities;
              }
              tmp_i23 = tmp_i23 + 1;
            } while (tmp_i23 < tmp_i10);
          }
          if ((tmp_pi21[0x6a] & 4U) == 0) {
            if ((tmp_pi21[0x6a] & 8U) != 0) {
              *(uint32_t *)(tmp_i14 + 0x108) = 2;
            }
          }
          else {
            *(uint32_t *)(tmp_i14 + 0x108) = 1;
          }
          *(uint32_t *)(tmp_i14 + 0xa8) = *(uint32_t *)(*(int *)(param_1[100] + 0x103c) + 0x108);
          *(int *)(tmp_i14 + 0x180) = *tmp_pi21;
          *(void **)(tmp_i14 + 0x2a4) = explosive_indicator_think;
          *(float **)(tmp_i14 + 0x29c) = g_unk_00abe908 + 0x19;
          *(int *)(tmp_i14 + 0x10c) = tmp_pi21[0x13d];
          if (*(int *)(tmp_pi21[0x86] + 0x440) == 0) {
            tmp_f5 = (float)tmp_pi21[0x54];
            *(float *)(tmp_i14 + 0x18) = tmp_f5;
            tmp_f2 = (float)tmp_pi21[0x55];
            *(float *)(tmp_i14 + 0x1c) = tmp_f2;
            tmp_f3 = (float)tmp_pi21[0x56];
            *(float *)(tmp_i14 + 0x20) = tmp_f3;
            tmp_f5 = tmp_f5 + (float)tmp_pi21[0x57];
            *(float *)(tmp_i14 + 0x18) = tmp_f5;
            tmp_f2 = tmp_f2 + (float)tmp_pi21[0x58];
            *(float *)(tmp_i14 + 0x1c) = tmp_f2;
            tmp_f4 = (float)tmp_pi21[0x59];
            *(float *)(tmp_i14 + 0x18) = tmp_f5 * 0.5;
            *(float *)(tmp_i14 + 0x1c) = tmp_f2 * 0.5;
            *(float *)(tmp_i14 + 0x20) = (tmp_f3 + tmp_f4) * 0.5;
          }
          else {
            *(int *)(tmp_i14 + 0x440) = *(int *)(tmp_pi21[0x86] + 0x440);
            Q_strncpyz(tmp_i14 + 0x400,tmp_pi21[0x86] + 0x400,0x40);
          }
          *(float *)(tmp_i14 + 0x18) = (float)(int)ROUND(*(float *)(tmp_i14 + 0x18));
          *(float *)(tmp_i14 + 0x1c) = (float)(int)ROUND(*(float *)(tmp_i14 + 0x1c));
          *(float *)(tmp_i14 + 0x20) = (float)(int)ROUND(*(float *)(tmp_i14 + 0x20));
          pfVar9 = (float *)trap_LinkEntity(tmp_i14);
        }
        else {
          pfVar9 = (float *)0x0;
          if (0 < (int)IndicatorEntities) {
            do {
              tmp_i10 = (&g_unk_0087b9e4)[(int)pfVar9];
              if (((*(int *)(tmp_i10 + 4) - 0x24U < 2) || (*(int *)(tmp_i10 + 4) == 0xd)) &&
                 (*(int *)(tmp_i10 + 0x180) == *tmp_pi21)) {
                if (*(int *)(tmp_pi21[0x86] + 0x440) == 0) {
                  tmp_f5 = (float)tmp_pi21[0x54];
                  *(float *)(tmp_i10 + 0x18) = tmp_f5;
                  tmp_f2 = (float)tmp_pi21[0x55];
                  *(float *)(tmp_i10 + 0x1c) = tmp_f2;
                  tmp_f3 = (float)tmp_pi21[0x56];
                  *(float *)(tmp_i10 + 0x20) = tmp_f3;
                  tmp_f5 = tmp_f5 + (float)tmp_pi21[0x57];
                  *(float *)(tmp_i10 + 0x18) = tmp_f5;
                  tmp_f2 = tmp_f2 + (float)tmp_pi21[0x58];
                  *(float *)(tmp_i10 + 0x1c) = tmp_f2;
                  tmp_f4 = (float)tmp_pi21[0x59];
                  *(float *)(tmp_i10 + 0x18) = (float)(int)ROUND(tmp_f5 * 0.5);
                  *(float *)(tmp_i10 + 0x1c) = (float)(int)ROUND(tmp_f2 * 0.5);
                  *(float *)(tmp_i10 + 0x20) = (float)(int)ROUND((tmp_f3 + tmp_f4) * 0.5);
                }
                else {
                  *(int *)(tmp_i10 + 0x440) = *(int *)(tmp_pi21[0x86] + 0x440);
                  Q_strncpyz(tmp_i10 + 0x400,tmp_pi21[0x86] + 0x400,0x40);
                }
                pfVar9 = (float *)trap_LinkEntity(tmp_i10);
                break;
              }
              pfVar9 = (float *)((int)pfVar9 + 1);
            } while (pfVar9 != IndicatorEntities);
          }
        }
      }
      if ((*(byte *)(param_1 + 0x6a) & 0x60) != 0) {
        return (uint8_t *)pfVar9;
      }
      if ((*(byte *)(tmp_pi21 + 0x6a) & 0x10) != 0) {
        return (uint8_t *)pfVar9;
      }
      if ((GHIDRA_FIELD(g_gametype, 12, 4) == 7) && ((g_TDMOptions[0xc] & 1) != 0)) {
        return (uint8_t *)(float *)g_TDMOptions;
      }
      pfVar9 = (float *)(*(int *)(param_1[100] + 3000) + 0x1c);
      (&g_unk_00abe8ac)[(int)pfVar9] =
           (int)ROUND((float)(&g_unk_00abe8ac)[(int)pfVar9] + (float)tmp_pi21[0x13a]);
      return (uint8_t *)pfVar9;
    }
  }
LAB_001045e0:
  AngleVectors(pfVar9 + 0x2c,&forward,&right,&up);
  tmp_i10 = param_1[100];
  muzzleTrace = *(float *)(tmp_i10 + 0x14);
  g_unk_02e432e4 = *(float *)(tmp_i10 + 0x18);
  g_unk_02e432e8 = *(float *)(tmp_i10 + 0x1c) + (float)*(int *)(tmp_i10 + 0xbc);
  tmp_u11 = *param_1;
  local_206c = forward * 64.0 + muzzleTrace;
  local_2068 = g_unk_02e432f0 * 64.0 + g_unk_02e432e4;
  local_2064 = g_unk_02e432f4 * 64.0 + g_unk_02e432e8;
  G_TempTraceIgnorePlayersAndBodies();
  trap_Trace(&local_2054,&muzzleTrace,0,0,&local_206c,tmp_u11,0x46000001);
  pfVar9 = (float *)G_ResetTempTraceIgnoreEnts();
  if ((local_2028 & 0x10) != 0) {
    return (uint8_t *)pfVar9;
  }
  if (local_204c == 1.0) {
    return (uint8_t *)pfVar9;
  }
  if ((int)local_2020 - 0x3feU < 2) {
    return (uint8_t *)local_2020;
  }
  tmp_i19 = (int)local_2020 * 0x600;
  tmp_i10 = G_EmplacedGunIsRepairable(g_entities + tmp_i19,param_1);
  if (tmp_i10 != 0) {
    pfVar9 = (float *)Engineer_MG42(param_1,g_entities + tmp_i19);
    return (uint8_t *)pfVar9;
  }
  tmp_u11 = *param_1;
  G_TempTraceIgnorePlayersAndBodies();
  trap_Trace(&local_2054,&muzzleTrace,0,0,&local_206c,tmp_u11,0x6000001);
  pfVar9 = (float *)G_ResetTempTraceIgnoreEnts();
  if ((local_2028 & 0x10) != 0) {
    return (uint8_t *)pfVar9;
  }
  if (local_204c == 1.0) {
    return (uint8_t *)pfVar9;
  }
  if ((float *)((int)local_2020 - 0x3feU) < (float *)0x2) {
    return (uint8_t *)(float *)((int)local_2020 - 0x3feU);
  }
  tmp_i10 = (int)local_2020 * 0x600;
  tmp_pu22 = g_entities + tmp_i10;
  pfVar9 = (float *)(*(int *)(g_entities + tmp_i10 + 0x2dc) - 0x15);
  if ((float *)0x2f < pfVar9) {
    return (uint8_t *)pfVar9;
  }
  tmp_pu18 = (uint8_t *)
            ((int)&_GLOBAL_OFFSET_TABLE_ + (&switchD_00104bc3::switchdataD_0025bf7c)[(int)pfVar9]);
  switch(pfVar9) {
  case (float *)0x0:
    local_2088 = GHIDRA_FIELD(n_dynamiteTimer, 12, 4);
    nitrox_ClampInt(&local_2088,0x459c4000,0x476a6000);
    tmp_pu18 = (uint8_t *)((int)local_2020 * 0x600);
    tmp_f5 = *(float *)((int)tmp_pu18 + 0x93e5a8);
    if ((int)tmp_f5 < 4) {
      if (((int)*(float *)((int)tmp_pu18 + 0x93e6ec) <= (int)g_unk_00abe908) &&
         ((int)*(float *)((int)tmp_pu18 + 0x93ea90) < 0xf8)) {
        if ((g_misc[0xc] & 1) == 0) {
          tmp_i10 = param_1[100];
        }
        else {
          tmp_i10 = param_1[100];
          if (((*(float *)((int)tmp_pu18 + 0x93e5b4) == 1.4013e-45) &&
              (tmp_f5 == *(float *)(tmp_i10 + 3000))) &&
             (*(uint32_t **)((int)tmp_pu18 + 0x93e6b8) != param_1)) {
            pfVar9 = (float *)nitmod_cp(param_1,0x31);
            return (uint8_t *)pfVar9;
          }
        }
        tmp_l26 = (long double)BG_GetFromTable(disarmSpeed_Dynamite,tmp_i10 + 0xed0,1);
        tmp_i10 = (int)local_2020 * 0x600;
        *(int *)(g_entities + tmp_i10 + 0x5f0) =
             *(int *)(g_entities + tmp_i10 + 0x5f0) + (int)ROUND(tmp_l26);
        if (3000 < (int)g_unk_00abe908 - *(int *)(g_entities + tmp_i10 + 0x5f8)) {
          nitmod_cp(param_1,0x2b);
          *(float **)(g_entities + tmp_i10 + 0x5f8) = g_unk_00abe908;
        }
        tmp_i10 = (int)local_2020 * 0x600;
        tmp_pu18 = g_entities + tmp_i10 + 0x5f0;
        if (0xf7 < (int)*(float *)tmp_pu18) {
          *(float *)tmp_pu18 = 3.57331e-43;
          *(void **)(g_entities + tmp_i10 + 0x2a4) = G_FreeEntity;
          *(float **)(g_entities + tmp_i10 + 0x29c) = g_unk_00abe908 + 0x19;
          local_2084 = *(float *)(g_entities + tmp_i10 + 0x134) +
                       (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x168));
          local_2080 = *(float *)(g_entities + tmp_i10 + 0x138) +
                       (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x16c));
          local_207c = *(float *)(g_entities + tmp_i10 + 0x13c) +
                       (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x170));
          local_2078 = (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x168)) +
                       *(float *)(g_entities + tmp_i10 + 0x140);
          local_2074 = (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x16c)) +
                       *(float *)(g_entities + tmp_i10 + 0x144);
          local_2070 = (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x170)) +
                       *(float *)(g_entities + tmp_i10 + 0x148);
          pfVar9 = (float *)trap_EntitiesInBox(&local_2084,&local_2078,local_201c,0x400);
          tmp_b24 = tmp_f5 == *(float *)(param_1[100] + 3000);
          if (tmp_b24) {
            tmp_b25 = param_1 == *(uint32_t **)(g_entities + tmp_i10 + 0x218);
          }
          else {
            tmp_b25 = false;
          }
          if ((int)pfVar9 < 1) {
            tmp_b8 = false;
          }
          else {
            tmp_b7 = false;
            local_20c8 = (float *)0x0;
            tmp_b8 = false;
            do {
              tmp_i10 = local_201c[(int)local_20c8];
              tmp_i19 = tmp_i10 * 0x600;
              if (((((g_entities[tmp_i19 + 0x14f] & 0x40) != 0) &&
                   (*(int *)(g_entities + tmp_i19 + 4) == 0xc)) &&
                  ((tmp_u6 = *(uint *)(g_entities + tmp_i19 + 0x1a8), (tmp_u6 & 3) != 0 &&
                   (((tmp_u6 & 0x80) == 0 &&
                    (tmp_i14 = *(int *)(g_entities + tmp_i19 + 0x264), tmp_i14 != 0)))))) &&
                 (*(int *)(tmp_i14 + 4) == 0xe)) {
                if (tmp_b24) {
                  if (tmp_b25) {
                    tmp_pc12 = "owner";
                  }
                  else {
                    tmp_pc12 = "teammate";
                  }
                }
                else if (*(int *)(param_1[100] + 3000) == 1) {
                  if ((!tmp_b8) && ((tmp_u6 & 1) != 0)) {
                    AddScore(param_1,5);
                    G_AddSkillPoints(param_1,1,0x40c00000);
                    if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
                      G_DebugAddSkillPoints(param_1,1,0x40c00000,"defusing enemy dynamite");
                    }
                    tmp_i14 = *(int *)(g_entities + tmp_i10 * 0x600 + 0x264);
                    tmp_b8 = true;
                    if (tmp_i14 == 0) goto LAB_0010754b;
                  }
                  tmp_pc12 = "axis";
                }
                else {
                  if ((!tmp_b8) && ((tmp_u6 & 2) != 0)) {
                    AddScore(param_1,5);
                    G_AddSkillPoints(param_1,1,0x40c00000);
                    if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
                      G_DebugAddSkillPoints(param_1,1,0x40c00000,"defusing enemy dynamite");
                    }
                    tmp_i14 = *(int *)(g_entities + tmp_i10 * 0x600 + 0x264);
                    *(uint *)(g_entities + tmp_i10 * 0x600 + 0x1a8) =
                         *(uint *)(g_entities + tmp_i10 * 0x600 + 0x1a8) & 0xfffffffb;
                    if (tmp_i14 == 0) {
LAB_0010754b:
                      tmp_b7 = true;
                      tmp_b8 = true;
                      goto LAB_00105f00;
                    }
                    tmp_b8 = true;
                  }
                  tmp_pc12 = "allies";
                }
                G_Script_ScriptEvent(tmp_i14,"defused",tmp_pc12);
                nitmod_objective(0,1,g_entities + tmp_i19,param_1,0);
                tmp_b7 = true;
              }
LAB_00105f00:
              local_20c8 = (float *)((int)local_20c8 + 1);
            } while (local_20c8 != pfVar9);
            if (tmp_b7) {
              return (uint8_t *)local_20c8;
            }
          }
          tmp_i10 = (int)local_2020 * 0x600;
          local_2060 = *(float *)(g_entities + tmp_i10 + 0x168);
          local_205c = *(float *)(g_entities + tmp_i10 + 0x16c);
          local_2058 = *(float *)(g_entities + tmp_i10 + 0x170) + 4.0;
          pfVar9 = (float *)EntsThatRadiusCanDamage
                                      (&local_2060,(float)*(int *)(g_entities + tmp_i10 + 0x2d8),
                                       local_101c);
          tmp_pu18 = (uint8_t *)pfVar9;
          for (tmp_i10 = 0; tmp_i10 < (int)pfVar9; tmp_i10 = tmp_i10 + 1) {
            tmp_f5 = local_101c[tmp_i10];
            tmp_pu18 = (uint8_t *)((int)tmp_f5 * 0x600);
            if (((*(float *)((int)tmp_pu18 + 0x93e4a4) == 4.48416e-44) &&
                (((uint)*(float *)((int)tmp_pu18 + 0x93e648) & 2) == 0)) &&
               (0 < (int)*(float *)((int)tmp_pu18 + 0x93e994))) {
              if (*(int *)(param_1[100] + 3000) == 1) {
                if ((!tmp_b8) && (*(float *)((int)tmp_pu18 + 0x93e5a8) == 1.4013e-45)) {
                  AddScore(param_1,5);
                  if (param_1[100] != 0) {
                    G_LogPrintf("Dynamite_Diffuse: %d\n",
                                ((int)(param_1 + -0x24f928) >> 9) * -0x55555555);
                  }
                  G_AddSkillPoints(param_1,1,0x40c00000);
                  if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
                    G_DebugAddSkillPoints(param_1,1,0x40c00000,"defusing enemy dynamite");
                  }
                }
                tmp_pc12 = "putaxis";
              }
              else {
                if ((!tmp_b8) && (*(float *)((int)tmp_pu18 + 0x93e5a8) == 2.8026e-45)) {
                  AddScore(param_1,5);
                  if (param_1[100] != 0) {
                    G_LogPrintf("Dynamite_Diffuse: %d\n",
                                ((int)(param_1 + -0x24f928) >> 9) * -0x55555555);
                  }
                  G_AddSkillPoints(param_1,1,0x40c00000);
                  if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
                    G_DebugAddSkillPoints(param_1,1,0x40c00000,"defusing enemy dynamite");
                  }
                }
                tmp_pc12 = "putallies";
              }
              G_Script_ScriptEvent((float *)((int)tmp_pu18 + 0x93e4a0),"defused",tmp_pc12 + 3);
              pfVar9 = (float *)nitmod_objective(0,1,*(uint32_t *)
                                                      (g_entities + (int)tmp_f5 * 0x600 + 0x218),
                                                 param_1,0);
              return (uint8_t *)pfVar9;
            }
          }
        }
      }
    }
    else {
      tmp_i10 = param_1[100];
      if ((int)tmp_f5 + -4 == *(int *)(tmp_i10 + 3000)) {
        if (3000 < (int)g_unk_00abe908 - (int)*(float *)((int)tmp_pu18 + 0x93ea98)) {
          nitmod_cp(param_1,0x2a);
          *(float **)((int)tmp_pu18 + 0x93ea98) = g_unk_00abe908;
          tmp_i10 = param_1[100];
        }
        tmp_l26 = (long double)BG_GetFromTable(armSpeed_Dynamite,tmp_i10 + 0xed0,1);
        tmp_i19 = (int)local_2020 * 0x600;
        local_201c[0] = *(int *)(g_entities + tmp_i19 + 0x168);
        *(int *)(g_entities + tmp_i19 + 0x5f0) =
             *(int *)(g_entities + tmp_i19 + 0x5f0) + (int)ROUND(tmp_l26);
        local_201c[1] = *(int *)(g_entities + tmp_i19 + 0x16c);
        local_2014 = *(float *)(g_entities + tmp_i19 + 0x170) + 4.0;
        G_TempTraceIgnorePlayersAndBodies();
        tmp_i10 = EntsThatRadiusCanDamage
                           (local_201c,(float)*(int *)(g_entities + tmp_i19 + 0x2d8),local_101c);
        G_ResetTempTraceIgnoreEnts();
        if (tmp_i10 < 1) {
          tmp_b24 = false;
        }
        else {
          tmp_i14 = 0;
          tmp_b25 = false;
          do {
            tmp_f5 = local_101c[tmp_i14];
            tmp_i23 = (int)tmp_f5 * 0x600;
            tmp_b24 = tmp_b25;
            if (((*(int *)(g_entities + tmp_i23 + 4) == 0x20) &&
                ((g_entities[tmp_i23 + 0x1a8] & 2) == 0)) &&
               ((*(int *)(g_entities + tmp_i23 + 0x218) == 0 ||
                ((*(byte *)(*(int *)(g_entities + tmp_i23 + 0x218) + 0x1a8) & 8) == 0)))) {
              tmp_i13 = (int)tmp_f5 * 0x600;
              tmp_i23 = G_ConstructionIsPartlyBuilt(g_entities + tmp_i13);
              if ((tmp_i23 != 0) &&
                 (tmp_b24 = true,
                 *(int *)(g_entities + tmp_i13 + 0x108) != *(int *)(g_entities + tmp_i19 + 0x108) + -4
                 )) {
                tmp_b24 = tmp_b25;
              }
            }
            tmp_i14 = tmp_i14 + 1;
            tmp_b25 = tmp_b24;
          } while (tmp_i14 != tmp_i10);
        }
        tmp_i10 = (int)local_2020 * 0x600;
        tmp_f5 = (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x168));
        tmp_f2 = (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x16c));
        tmp_f3 = (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x170));
        local_2084 = *(float *)(g_entities + tmp_i10 + 0x134) + tmp_f5;
        local_2080 = *(float *)(g_entities + tmp_i10 + 0x138) + tmp_f2;
        local_207c = *(float *)(g_entities + tmp_i10 + 0x13c) + tmp_f3;
        local_2078 = tmp_f5 + *(float *)(g_entities + tmp_i10 + 0x140);
        local_2074 = tmp_f2 + *(float *)(g_entities + tmp_i10 + 0x144);
        local_2070 = tmp_f3 + *(float *)(g_entities + tmp_i10 + 0x148);
        tmp_pu18 = (uint8_t *)trap_EntitiesInBox(&local_2084,&local_2078,local_201c,0x400);
        pfVar9 = g_unk_00abe908;
        local_2084 = *(float *)(g_entities + tmp_i10 + 0x134) + tmp_f5;
        local_2080 = *(float *)(g_entities + tmp_i10 + 0x138) + tmp_f2;
        local_207c = *(float *)(g_entities + tmp_i10 + 0x13c) + tmp_f3;
        local_2078 = tmp_f5 + *(float *)(g_entities + tmp_i10 + 0x140);
        local_2074 = tmp_f2 + *(float *)(g_entities + tmp_i10 + 0x144);
        local_2070 = tmp_f3 + *(float *)(g_entities + tmp_i10 + 0x148);
        if ((int)tmp_pu18 < 1) {
          tmp_b25 = false;
        }
        else {
          tmp_b25 = false;
          tmp_pi21 = local_201c + (int)tmp_pu18;
          tmp_pi20 = local_201c;
          do {
            tmp_pu18 = (uint8_t *)(*tmp_pi20 * 0x600);
            if (((((*(byte *)((int)tmp_pu18 + 0x93e5ef) & 0x40) != 0) &&
                 (*(float *)((int)tmp_pu18 + 0x93e4a4) == 1.68156e-44)) &&
                (tmp_f5 = *(float *)((int)tmp_pu18 + 0x93e648), ((uint)tmp_f5 & 3) != 0)) &&
               ((tmp_pu18 = *(uint8_t **)((int)tmp_pu18 + 0x93e704),
                (float *)tmp_pu18 == (float *)0x0 ||
                (*(float *)((int)tmp_pu18 + 0x5c0) == 2.66367e-40)))) {
              if (((uint)tmp_f5 & 1) == 0) {
                if (((uint)tmp_f5 & 2) == 0) goto LAB_001063f8;
                tmp_pu18 = (uint8_t *)param_1[100];
                tmp_b8 = true;
                if (*(float *)((int)tmp_pu18 + 3000) != 2.8026e-45) {
                  tmp_b8 = tmp_b24;
                }
LAB_00106468:
                tmp_b24 = tmp_b8;
                if ((((uint)tmp_f5 & 2) == 0) || (*(float *)((int)tmp_pu18 + 3000) != 1.4013e-45))
                goto LAB_001063f8;
              }
              else {
                tmp_pu18 = (uint8_t *)param_1[100];
                if (*(float *)((int)tmp_pu18 + 3000) == 1.4013e-45) {
LAB_001064bf:
                  tmp_b24 = true;
                  tmp_b8 = tmp_b24;
                  if (*(float *)((int)tmp_pu18 + 3000) != 2.8026e-45) goto LAB_00106468;
                }
                else {
                  if (((uint)tmp_f5 & 2) != 0) {
                    tmp_b8 = tmp_b24;
                    if (*(float *)((int)tmp_pu18 + 3000) != 2.8026e-45) goto LAB_00106468;
                    goto LAB_001064bf;
                  }
                  if (*(float *)((int)tmp_pu18 + 3000) != 2.8026e-45) goto LAB_001063f8;
                }
              }
              tmp_b25 = true;
            }
LAB_001063f8:
            tmp_pi20 = tmp_pi20 + 1;
          } while (tmp_pi20 != tmp_pi21);
        }
        if ((tmp_b25) || (!tmp_b24)) {
          tmp_i10 = (int)local_2020 * 0x600;
          if (0xf9 < *(int *)(g_entities + tmp_i10 + 0x5f0)) {
            *(float **)(g_entities + tmp_i10 + 0x24c) = g_unk_00abe908 + 0xfa;
            *(int *)(g_entities + tmp_i10 + 0x5f0) = 5;
            tmp_u11 = *(uint32_t *)(param_1[100] + 3000);
            *(float **)(g_entities + tmp_i10 + 0x10c) = pfVar9;
            *(uint32_t *)(g_entities + tmp_i10 + 0x108) = tmp_u11;
            *(int *)(g_entities + tmp_i10 + 0x29c) = (int)pfVar9 + local_2088;
            *(int *)(g_entities + tmp_i10 + 0x58) = local_2088;
            *(void **)(g_entities + tmp_i10 + 0x2a4) = G_ExplodeMissile;
            nitmod_cp(param_1,7);
            local_2084 = *(float *)(g_entities + tmp_i10 + 0x134) +
                         (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x168));
            local_2080 = *(float *)(g_entities + tmp_i10 + 0x138) +
                         (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x16c));
            local_207c = *(float *)(g_entities + tmp_i10 + 0x13c) +
                         (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x170));
            local_2078 = (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x168)) +
                         *(float *)(g_entities + tmp_i10 + 0x140);
            local_2074 = (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x16c)) +
                         *(float *)(g_entities + tmp_i10 + 0x144);
            local_2070 = (float)(int)ROUND(*(float *)(g_entities + tmp_i10 + 0x170)) +
                         *(float *)(g_entities + tmp_i10 + 0x148);
            tmp_i10 = trap_EntitiesInBox(&local_2084,&local_2078,local_201c,0x400);
            for (tmp_i19 = 0; tmp_i19 < tmp_i10; tmp_i19 = tmp_i19 + 1) {
              tmp_i14 = local_201c[tmp_i19];
              tmp_i23 = tmp_i14 * 0x600;
              if (((((g_entities[tmp_i23 + 0x14f] & 0x40) != 0) &&
                   (*(int *)(g_entities + tmp_i23 + 4) == 0xc)) &&
                  (tmp_u6 = *(uint *)(g_entities + tmp_i23 + 0x1a8), (tmp_u6 & 3) != 0)) &&
                 ((*(int *)(g_entities + tmp_i23 + 0x264) == 0 ||
                  (*(int *)(*(int *)(g_entities + tmp_i23 + 0x264) + 0x5c0) == 0x2e686)))) {
                pfVar16 = (float *)(tmp_i14 * 0x600);
                pfVar9 = pfVar16 + 0x24f928;
                if ((tmp_u6 & 1) == 0) {
                  if (((tmp_u6 & 2) != 0) && (*(int *)(param_1[100] + 3000) == 1)) {
                    pfVar1 = pfVar16 + 0x24fa27;
                    pfVar16 = (float *)((int)local_2020 * 0x600);
                    pfVar16[0x24fa27] = *pfVar1;
                  }
LAB_001066ca:
                  if ((tmp_u6 & 0x80) != 0) {
                    return (uint8_t *)pfVar16;
                  }
                }
                else {
                  if (*(int *)(param_1[100] + 3000) != 2) goto LAB_001066ca;
                  ((float *)((int)local_2020 * 0x600))[0x24fa27] = pfVar16[0x24fa27];
                  if ((tmp_u6 & 0x80) != 0) {
                    return (uint8_t *)(float *)((int)local_2020 * 0x600);
                  }
                  pfVar16 = (float *)param_1[100];
                  if (pfVar16[0x2ee] == 2.8026e-45) goto LAB_001066f2;
                }
                if ((tmp_u6 & 2) == 0) {
                  return (uint8_t *)pfVar16;
                }
                if (((float *)param_1[100])[0x2ee] != 1.4013e-45) {
                  return (uint8_t *)(float *)param_1[100];
                }
LAB_001066f2:
                tmp_u11 = _GetEntityName(pfVar9);
                nitmod_objective(0,0,pfVar9,param_1,0x15);
                tmp_i23 = (int)local_2020 * 0x600;
                *(uint32_t **)(g_entities + tmp_i23 + 0x218) = param_1;
                tmp_u17 = BG_TeamName(*(uint32_t *)(param_1[100] + 3000));
                G_Script_ScriptEvent(pfVar9,"dynamited",tmp_u17);
                tmp_i19 = tmp_i14 * 0x600;
                tmp_i10 = *(int *)(g_entities + tmp_i19 + 0x5d8);
                *(int *)(g_entities + tmp_i19 + 0x5d8) = tmp_i10 + 1;
                tmp_u11 = va("%s_%i",tmp_u11,tmp_i10 + 1);
                Bot_AddDynamiteGoal(tmp_pu22,*(uint32_t *)(g_entities + tmp_i23 + 0x108),tmp_u11);
                if ((g_entities[tmp_i19 + 0x1a8] & 4) == 0) {
                  AddScore(*(uint32_t *)(g_entities + tmp_i23 + 0x218),5);
                  tmp_i10 = *(int *)(g_entities + tmp_i23 + 0x218);
                  if ((tmp_i10 != 0) && (*(int *)(tmp_i10 + 400) != 0)) {
                    G_LogPrintf("Dynamite_Plant: %d\n",(tmp_i10 + -0x93e4a0 >> 9) * -0x55555555);
                  }
                  *(uint32_t **)(g_entities + (int)local_2020 * 0x600 + 0x218) = param_1;
                }
                tmp_i10 = (int)local_2020 * 0x600;
                *(uint *)(g_entities + tmp_i10 + 0x4fc) = *(uint *)(g_entities + tmp_i10 + 0x4fc) | 1;
                pfVar9 = *(float **)(g_entities + tmp_i14 * 0x600);
                *(uint32_t *)(g_entities + tmp_i10 + 0x114) = 1;
                *(float **)(g_entities + tmp_i10 + 0x500) = pfVar9;
                return (uint8_t *)pfVar9;
              }
            }
            tmp_i19 = (int)local_2020 * 0x600;
            local_2060 = *(float *)(g_entities + tmp_i19 + 0x168);
            local_205c = *(float *)(g_entities + tmp_i19 + 0x16c);
            local_2058 = *(float *)(g_entities + tmp_i19 + 0x170) + 4.0;
            G_TempTraceIgnorePlayersAndBodies();
            tmp_i10 = EntsThatRadiusCanDamage
                               (&local_2060,(float)*(int *)(g_entities + tmp_i19 + 0x2d8),local_101c)
            ;
            tmp_pu18 = (uint8_t *)G_ResetTempTraceIgnoreEnts();
            for (local_20d4 = 0; local_20d4 < tmp_i10; local_20d4 = local_20d4 + 1) {
              tmp_i14 = (int)local_101c[local_20d4] * 0x600;
              tmp_pu18 = (uint8_t *)local_101c;
              if ((*(int *)(g_entities + tmp_i14 + 4) == 0x20) &&
                 ((g_entities[tmp_i14 + 0x1a8] & 2) == 0)) {
                tmp_i23 = G_ConstructionIsPartlyBuilt(g_entities + tmp_i14);
                tmp_pu18 = (uint8_t *)0x0;
                if ((tmp_i23 != 0) &&
                   ((tmp_pu18 = g_entities + tmp_i14 + 0x100,
                    *(int *)(g_entities + tmp_i14 + 0x108) != *(int *)(g_entities + tmp_i19 + 0x108)
                    && (0 < *(int *)(g_entities + tmp_i14 + 0x4f4))))) {
                  if (*(int *)(g_entities + tmp_i14 + 0x218) == 0) {
                    return (uint8_t *)(float *)0x0;
                  }
                  tmp_u11 = _GetEntityName(*(int *)(g_entities + tmp_i14 + 0x218));
                  nitmod_objective(0,0,*(uint32_t *)(g_entities + tmp_i14 + 0x218),param_1,0x15);
                  tmp_u17 = BG_TeamName(*(uint32_t *)(param_1[100] + 3000));
                  G_Script_ScriptEvent(g_entities + tmp_i14,"dynamited",tmp_u17);
                  *(uint32_t *)(g_entities + tmp_i14 + 0x114) =
                       *(uint32_t *)(*(int *)(*(int *)(g_entities + tmp_i19 + 0x218) + 400) + 0xa0)
                  ;
                  tmp_i10 = *(int *)(g_entities + tmp_i14 + 0x5d8);
                  *(int *)(g_entities + tmp_i14 + 0x5d8) = tmp_i10 + 1;
                  tmp_u11 = va("%s_%i",tmp_u11,tmp_i10 + 1);
                  Bot_AddDynamiteGoal(tmp_pu22,*(uint32_t *)(g_entities + tmp_i19 + 0x108),tmp_u11);
                  pfVar9 = *(float **)(g_entities + tmp_i14 + 0x218);
                  if (((((uint)pfVar9[0x6a] & 4) == 0) &&
                      (pfVar9 = *(float **)(g_entities + tmp_i14 + 0x108), pfVar9 != (float *)0x0))
                     && (pfVar9 == *(float **)(param_1[100] + 3000))) {
                    AddScore(*(uint32_t *)(g_entities + (int)local_2020 * 0x600 + 0x218),5);
                    tmp_i10 = *(int *)(g_entities + (int)local_2020 * 0x600 + 0x218);
                    if ((tmp_i10 != 0) && (*(int *)(tmp_i10 + 400) != 0)) {
                      G_LogPrintf("Dynamite_Plant: %d\n",(tmp_i10 + -0x93e4a0 >> 9) * -0x55555555);
                    }
                    pfVar9 = (float *)((int)local_2020 * 0x600);
                    pfVar9[0x24f9ae] = (float)param_1;
                  }
                  *(uint *)(g_entities + (int)local_2020 * 0x600 + 0x4fc) =
                       *(uint *)(g_entities + (int)local_2020 * 0x600 + 0x4fc) | 1;
                  *(uint32_t *)(g_entities + (int)local_2020 * 0x600 + 0x114) = 1;
                  return (uint8_t *)pfVar9;
                }
              }
            }
          }
        }
        else {
          G_FreeEntity(tmp_pu22);
          tmp_pu18 = (uint8_t *)nitmod_cp(param_1,6);
        }
      }
    }
    break;
  case (float *)0x13:
  case (float *)0x2e:
  case (float *)0x2f:
    tmp_i19 = (int)local_2020 * 0x600;
    local_201c[0] = *(int *)(g_entities + tmp_i19 + 0x18);
    local_201c[1] = *(int *)(g_entities + tmp_i19 + 0x1c);
    local_2014 = *(float *)(g_entities + tmp_i19 + 0x20) - 16.0;
    tmp_u11 = *(uint32_t *)(g_entities + tmp_i19);
    G_TempTraceIgnorePlayersAndBodies();
    trap_Trace(local_101c,tmp_i19 + 0x93e4b8,0,0,local_201c,tmp_u11,0x6000001);
    G_ResetTempTraceIgnoreEnts();
    if ((local_ff0 < 0) &&
       ((local_fe8 == 0x3fe ||
        ((*(int *)(g_entities + local_fe8 * 0x600 + 0x194) != 0 &&
         (*(int *)(g_entities + local_fe8 * 0x600 + 4) == 0x20)))))) {
      tmp_i19 = G_CountTeamLandmines(*(uint32_t *)(param_1[100] + 3000));
      if ((tmp_i19 < (int)GHIDRA_FIELD(team_maxLandmines, 12, 4)) ||
         (tmp_i19 = *(int *)(g_entities + (int)local_2020 * 0x600 + 0x108),
         tmp_i19 % 4 != *(int *)(param_1[100] + 3000))) {
        tmp_i14 = (int)local_2020 * 0x600;
        tmp_i19 = *(int *)(g_entities + tmp_i14 + 0x108);
        if ((1 < tmp_i19 - 1U) && (1 < tmp_i19 - 9U)) {
          tmp_i10 = param_1[100];
          if (*(int *)(tmp_i10 + 3000) != tmp_i19 % 4) {
            return (uint8_t *)(float *)(tmp_i19 / 4);
          }
          if (3000 < (int)g_unk_00abe908 - *(int *)(g_entities + tmp_i14 + 0x5f8)) {
            nitmod_cp(param_1,0x26);
            *(float **)(g_entities + tmp_i14 + 0x5f8) = g_unk_00abe908;
            tmp_i10 = param_1[100];
          }
          tmp_l26 = (long double)BG_GetFromTable(armSpeed_LandMine,tmp_i10 + 0xed0,1);
          tmp_i10 = (int)local_2020 * 0x600;
          tmp_pi21 = (int *)(g_entities + tmp_i10 + 0x5f0);
          pfVar9 = (float *)((int)ROUND(tmp_l26) + *tmp_pi21);
          *tmp_pi21 = (int)pfVar9;
          if ((int)pfVar9 < 0xfa) {
            return (uint8_t *)pfVar9;
          }
          nitmod_cp(param_1,4);
          *(uint32_t *)(g_entities + tmp_i10 + 0x14c) = 0;
          trap_LinkEntity(tmp_pu22);
          *(uint32_t *)(g_entities + tmp_i10 + 0x8c) = *param_1;
          pfVar9 = g_unk_00abe908 + 500;
          *(float **)(g_entities + tmp_i10 + 0x24c) = g_unk_00abe908 + 0xfa;
          *tmp_pi21 = 0;
          tmp_u11 = *(uint32_t *)(param_1[100] + 3000);
          *(float **)(g_entities + tmp_i10 + 0x29c) = pfVar9;
          *(uint32_t *)(g_entities + tmp_i10 + 0xa8) = 0;
          *(uint32_t *)(g_entities + tmp_i10 + 0x108) = tmp_u11;
          *(void **)(g_entities + tmp_i10 + 0x2a4) = G_LandminePrime;
          return (uint8_t *)(float *)G_LandminePrime;
        }
      }
      else if ((1 < tmp_i19 - 1U) && (1 < tmp_i19 - 9U)) {
        nitmod_cp(param_1,1);
        G_FreeEntity(tmp_pu22);
        goto LAB_00104e73;
      }
      tmp_pu18 = (uint8_t *)((int)local_2020 * 0x600);
      if (((*(float *)((int)tmp_pu18 + 0x93e588) != 7.14662e-44) &&
          ((int)*(float *)((int)tmp_pu18 + 0x93e6ec) <= (int)g_unk_00abe908)) &&
         (pfVar9 = (float *)((int)tmp_pu18 + 0x93ea90), (int)*pfVar9 < 0xfa)) {
        tmp_l26 = (long double)BG_GetFromTable(disarmSpeed_LandMine,param_1[100] + 0xed0,1);
        *pfVar9 = (float)((int)*pfVar9 + (int)ROUND(tmp_l26));
        pfVar9 = (float *)((int)g_unk_00abe908 - (int)*(float *)((int)tmp_pu18 + 0x93ea98));
        if (3000 < (int)pfVar9) {
          nitmod_cp(param_1,0x27);
          pfVar9 = g_unk_00abe908;
          *(float **)((int)tmp_pu18 + 0x93ea98) = g_unk_00abe908;
        }
        tmp_i19 = (int)local_2020 * 0x600;
        tmp_pu18 = (uint8_t *)pfVar9;
        if (0xf9 < *(int *)(g_entities + tmp_i19 + 0x5f0)) {
          nitmod_cp(param_1,5);
          tmp_i14 = *(int *)(g_entities + tmp_i19 + 0xe8);
          if (tmp_i14 != 0x33) {
            tmp_i14 = 0x19;
          }
          Add_Ammo(param_1,tmp_i14,1,0);
          if ((*(int *)(param_1[100] + 3000) != *(int *)(g_entities + tmp_i19 + 0x108) % 4) &&
             (G_AddSkillPoints(param_1,1,0x40800000), GHIDRA_FIELD(g_debugSkills, 12, 4) != 0)) {
            G_DebugAddSkillPoints(param_1,1,0x40800000,"defusing an enemy landmine");
          }
          tmp_i19 = (tmp_i10 >> 9) * -0x55555555;
          tmp_i10 = G_FindMapEntityData(mapEntityData,tmp_i19);
          if (tmp_i10 != 0) {
            G_FreeMapEntityData(mapEntityData,tmp_i10);
          }
          tmp_i10 = G_FindMapEntityData(0x2d8ca94,tmp_i19);
          if (tmp_i10 != 0) {
            G_FreeMapEntityData(0x2d8ca94,tmp_i10);
          }
          tmp_pu18 = (uint8_t *)G_FreeEntity(tmp_pu22);
        }
      }
    }
    else {
      nitmod_cp(param_1,0);
      G_FreeEntity(tmp_pu22);
LAB_00104e73:
      tmp_i10 = *(int *)(g_entities + (int)local_2020 * 0x600 + 0xe8);
      if (tmp_i10 != 0x33) {
        tmp_i10 = 0x19;
      }
      Add_Ammo(param_1,tmp_i10,1,0);
      tmp_l26 = (long double)BG_GetFromTable(&chargeCost_Landmine,param_1[100] + 0xed0,1);
      jP_UnDoChargeCost(param_1,1,(float)tmp_l26);
      tmp_pu18 = (uint8_t *)param_1[100];
      pfVar9 = (float *)((int)tmp_pu18 + 0xe00);
      *pfVar9 = (float)((int)*pfVar9 + -1);
    }
    break;
  case (float *)0x14:
    tmp_pu18 = (uint8_t *)((int)local_2020 * 0x600);
    pfVar9 = (float *)((int)tmp_pu18 + 0x93ea90);
    if ((int)*pfVar9 < 0xfa) {
      tmp_l26 = (long double)BG_GetFromTable(disarmSpeed_Satchel,param_1[100] + 0xed0,1);
      *pfVar9 = (float)((int)*pfVar9 + (int)ROUND(tmp_l26));
      if (3000 < (int)g_unk_00abe908 - (int)*(float *)((int)tmp_pu18 + 0x93ea98)) {
        nitmod_cp(param_1,0x28);
        *(float **)((int)tmp_pu18 + 0x93ea98) = g_unk_00abe908;
      }
      tmp_i10 = (int)local_2020 * 0x600;
      tmp_pu18 = g_entities + tmp_i10 + 0x5f0;
      if (0xf9 < (int)*(float *)tmp_pu18) {
        *(float *)tmp_pu18 = 3.57331e-43;
        *(void **)(g_entities + tmp_i10 + 0x2a4) = G_FreeEntity;
        *(float **)(g_entities + tmp_i10 + 0x29c) = g_unk_00abe908 + 0x19;
        nitmod_cp(param_1,0x29);
        tmp_pu18 = *(uint8_t **)(param_1[100] + 3000);
        if (*(float **)(g_entities + tmp_i10 + 0x108) != (float *)tmp_pu18) {
          G_AddSkillPoints(param_1,1,0x40c00000);
          tmp_pu18 = g_debugSkills;
          if (GHIDRA_FIELD(g_debugSkills, 12, 4) != 0) {
            tmp_pu18 = (uint8_t *)
                      G_DebugAddSkillPoints(param_1,1,0x40c00000,"disarming satchel charge");
          }
        }
      }
    }
    break;
  case (float *)0x2d:
    tmp_i10 = (int)local_2020 * 0x600;
    if ((int)*(uint *)(g_entities + tmp_i10 + 0x108) < 4) {
      tmp_pu18 = (uint8_t *)g_unk_00abe908;
      if ((*(int *)(g_entities + tmp_i10 + 0x24c) <= (int)g_unk_00abe908) &&
         (tmp_pi21 = (int *)(g_entities + tmp_i10 + 0x5f0), *tmp_pi21 < 0xff)) {
        tmp_l26 = (long double)BG_GetFromTable(armSpeed_Dynamite,param_1[100] + 0xed0,1);
        *tmp_pi21 = *tmp_pi21 + (int)ROUND(tmp_l26);
        if (3000 < (int)g_unk_00abe908 - *(int *)(g_entities + tmp_i10 + 0x5f8)) {
          nitmod_cp(param_1,0x2d);
          *(float **)(g_entities + tmp_i10 + 0x5f8) = g_unk_00abe908;
        }
        tmp_i10 = (int)local_2020 * 0x600;
        tmp_pu18 = g_entities + tmp_i10 + 0x5f0;
        if (0xfe < (int)*(float *)tmp_pu18) {
          *(float *)tmp_pu18 = 3.57331e-43;
          *(void **)(g_entities + tmp_i10 + 0x2a4) = G_FreeEntity;
          *(float **)(g_entities + tmp_i10 + 0x29c) = g_unk_00abe908;
          if ((*(int *)(param_1[100] + 3000) != *(int *)(g_entities + tmp_i10 + 0x108) % 4) &&
             (G_AddSkillPoints(param_1,1,0x40800000), GHIDRA_FIELD(g_debugSkills, 12, 4) != 0)) {
            G_DebugAddSkillPoints(param_1,1,0x40800000,"defusing an enemy tripmine");
          }
          tmp_pu18 = (uint8_t *)nitmod_cp(param_1,0x2e);
        }
      }
    }
    else if (*(uint *)(param_1[100] + 3000) == (*(uint *)(g_entities + tmp_i10 + 0x108) & 3)) {
      tmp_i19 = nitmod_CountTeamTripmines(*(uint *)(param_1[100] + 3000));
      if (tmp_i19 < (int)GHIDRA_FIELD(team_maxTripmines, 12, 4)) {
        if (3000 < (int)g_unk_00abe908 - *(int *)(g_entities + tmp_i10 + 0x5f8)) {
          nitmod_cp(param_1,0x32);
          *(float **)(g_entities + tmp_i10 + 0x5f8) = g_unk_00abe908;
        }
        tmp_l26 = (long double)BG_GetFromTable(armSpeed_LandMine,param_1[100] + 0xed0,1);
        tmp_i10 = (int)local_2020 * 0x600;
        tmp_pi21 = (int *)(g_entities + tmp_i10 + 0x5f0);
        tmp_pu18 = (uint8_t *)((int)ROUND(tmp_l26) + *tmp_pi21);
        *tmp_pi21 = (int)tmp_pu18;
        if (0xfe < (int)tmp_pu18) {
          *tmp_pi21 = 0xff;
          nitmod_cp(param_1,0x33);
          pfVar9 = g_unk_00abe908 + 0xfa;
          *(float **)(g_entities + tmp_i10 + 0x24c) = pfVar9;
          *tmp_pi21 = 0;
          *(float **)(g_entities + tmp_i10 + 0x29c) = pfVar9;
          *(void **)(g_entities + tmp_i10 + 0x2a4) = G_TripMinePrime;
          *(uint32_t *)(g_entities + tmp_i10 + 0x10c) = 1;
          *(uint32_t *)(g_entities + tmp_i10 + 0x108) = *(uint32_t *)(param_1[100] + 3000);
          tmp_pu18 = g_entities + tmp_i10 + 0x100;
        }
      }
      else {
        nitmod_cp(param_1,0x34);
        G_FreeEntity(tmp_pu22);
        tmp_pu18 = (uint8_t *)param_1[100];
        pfVar9 = (float *)((int)tmp_pu18 + 0xe78);
        *pfVar9 = (float)((int)*pfVar9 + -1);
      }
    }
    else {
      tmp_pu18 = (uint8_t *)((int)g_unk_00abe908 - *(int *)(g_entities + tmp_i10 + 0x5f8));
      if (3000 < (int)g_unk_00abe908 - *(int *)(g_entities + tmp_i10 + 0x5f8)) {
        nitmod_cp(param_1,0x35);
        tmp_pu18 = (uint8_t *)g_unk_00abe908;
        *(float **)(g_entities + tmp_i10 + 0x5f8) = g_unk_00abe908;
      }
    }
  }
  return tmp_pu18;
}

bool G_AvailableAirstrikes(int param_1)
{
  if (*(int *)(*(int *)(param_1 + 400) + 3000) != 1) {
    return g_unk_02aa29ac < 1;
  }
  return g_unk_02aa29a8 < 1;
}

void G_AddAirstrikeToCounters(int param_1)
{
  if (*(int *)(*(int *)(param_1 + 400) + 3000) != 1) {
    g_unk_02aa29ac = g_unk_02aa29ac + GHIDRA_FIELD(team_airstrikeTime, 12, 4) * 1000;
    return;
  }
  g_unk_02aa29a8 = g_unk_02aa29a8 + GHIDRA_FIELD(team_airstrikeTime, 12, 4) * 1000;
  return;
}

uint32_t weapon_checkAirStrike(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  uint tmp_u5;
  long double tmp_l6;
  long double tmp_l7;
  long double tmp_l8;
  
  if (*(int *)(param_1 + 0x108) == 1) {
    g_unk_02aa2ecc = g_unk_02aa2ecc + 1;
  }
  else {
    g_unk_02aa2ed0 = g_unk_02aa2ed0 + 1;
  }
  tmp_i4 = *(int *)(param_1 + 0x218);
  if (((((g_friendlyFire[0xc] & 1) == 0) && (GHIDRA_FIELD(g_gametype, 12, 4) != 8)) &&
      (*(int *)(tmp_i4 + 400) != 0)) && (*(int *)(*(int *)(tmp_i4 + 400) + 3000) == 3)) {
    tmp_f2 = (float)g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x2d4) = 0;
    *(void **)(param_1 + 0x2a4) = G_ExplodeMissile;
    tmp_u5 = rand();
    tmp_f1 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
    *(int *)(param_1 + 0x29c) = (int)ROUND((tmp_f1 + tmp_f1) * 50.0 + tmp_f2);
    *(uint32_t *)(param_1 + 0x368) = 0;
    if (*(int *)(param_1 + 0x108) == 1) {
      g_unk_02aa2ecc = g_unk_02aa2ecc + -1;
      return 0;
    }
    g_unk_02aa2ed0 = g_unk_02aa2ed0 + -1;
    return 0;
  }
  if (*(int *)(param_1 + 0x108) == 1) {
    if (g_unk_02aa2ecc < 7) {
      tmp_i3 = g_unk_02aa29a8;
      if (*(int *)(*(int *)(tmp_i4 + 400) + 3000) != 1) {
        tmp_i3 = g_unk_02aa29ac;
      }
      if (tmp_i3 < 1) {
        return 1;
      }
    }
    tmp_i3 = nitrox_TempEventFromQueue(&vec3_origin,0x5c);
    *(uint32_t *)(tmp_i3 + 0xf4) = 0;
    *(uint32_t *)(tmp_i3 + 0x10c) = 1;
    *(int *)(tmp_i3 + 300) = (tmp_i4 + -0x93e4a0 >> 9) * -0x55555555;
    *(uint32_t *)(tmp_i3 + 0x128) = 0x820;
    *(uint32_t *)(param_1 + 0x368) = 0;
    if (*(int *)(param_1 + 0x108) == 1) {
      g_unk_02aa2ecc = g_unk_02aa2ecc + -1;
    }
    else {
      g_unk_02aa2ed0 = g_unk_02aa2ed0 + -1;
    }
    if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 2) == 0) {
      if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 4) == 0) {
        return 0;
      }
      tmp_l6 = (long double)
              BG_GetFromTable(&chargeCost_Artillery,
                              *(int *)(*(int *)(param_1 + 0x218) + 400) + 0xed0,3);
      if (*(int *)(param_1 + 0x218) == 0) {
        return 0;
      }
      tmp_i4 = *(int *)(*(int *)(param_1 + 0x218) + 400);
      if (tmp_i4 == 0) {
        return 0;
      }
      if (GHIDRA_FIELD(g_noCharge, 12, 4) != 0) {
        return 0;
      }
      tmp_l7 = (long double)*(int *)(tmp_i4 + 0x478);
      tmp_l6 = tmp_l6 * (long double)0.5;
      tmp_l8 = (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i4 + 3000)];
      goto LAB_00107b1c;
    }
  }
  else {
    if (g_unk_02aa2ed0 < 7) {
      tmp_i3 = g_unk_02aa29a8;
      if (*(int *)(*(int *)(tmp_i4 + 400) + 3000) != 1) {
        tmp_i3 = g_unk_02aa29ac;
      }
      if (tmp_i3 < 1) {
        return 1;
      }
    }
    tmp_i3 = nitrox_TempEventFromQueue(&vec3_origin,0x5c);
    *(uint32_t *)(tmp_i3 + 0xf4) = 0;
    *(uint32_t *)(tmp_i3 + 0x10c) = 1;
    *(int *)(tmp_i3 + 300) = (tmp_i4 + -0x93e4a0 >> 9) * -0x55555555;
    *(uint32_t *)(tmp_i3 + 0x128) = 0x820;
    *(uint32_t *)(param_1 + 0x368) = 0;
    if (*(int *)(param_1 + 0x108) == 1) {
      g_unk_02aa2ecc = g_unk_02aa2ecc + -1;
    }
    else {
      g_unk_02aa2ed0 = g_unk_02aa2ed0 + -1;
    }
    if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 2) == 0) {
      if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 4) == 0) {
        return 0;
      }
      tmp_l6 = (long double)
              BG_GetFromTable(&chargeCost_Artillery,
                              *(int *)(*(int *)(param_1 + 0x218) + 400) + 0xed0,3);
      if (*(int *)(param_1 + 0x218) == 0) {
        return 0;
      }
      tmp_i4 = *(int *)(*(int *)(param_1 + 0x218) + 400);
      if (tmp_i4 == 0) {
        return 0;
      }
      if (GHIDRA_FIELD(g_noCharge, 12, 4) != 0) {
        return 0;
      }
      tmp_l7 = (long double)*(int *)(tmp_i4 + 0x478);
      tmp_l8 = (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i4 + 3000)];
      tmp_l6 = tmp_l6 * (long double)0.5;
      goto LAB_00107b1c;
    }
  }
  tmp_l6 = (long double)
          BG_GetFromTable(&chargeCost_Artillery,*(int *)(*(int *)(param_1 + 0x218) + 400) + 0xed0,3)
  ;
  if (*(int *)(param_1 + 0x218) == 0) {
    return 0;
  }
  tmp_i4 = *(int *)(*(int *)(param_1 + 0x218) + 400);
  if (tmp_i4 == 0) {
    return 0;
  }
  if (GHIDRA_FIELD(g_noCharge, 12, 4) != 0) {
    return 0;
  }
  tmp_l7 = (long double)*(int *)(tmp_i4 + 0x478);
  tmp_l8 = (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i4 + 3000)];
LAB_00107b1c:
  *(int *)(tmp_i4 + 0x478) = (int)ROUND(tmp_l7 - tmp_l6 * tmp_l8);
  return 0;
}

void Weapon_Artillery(uint32_t *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  byte tmp_b5;
  float tmp_f6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  uint32_t tmp_u10;
  uint tmp_u11;
  long double tmp_l12;
  int local_e8;
  uint local_dc;
  float *local_d4;
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
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  byte local_28;
  
  if (*(int *)(param_1[100] + 0xe4) != 3) {
    return;
  }
  if (GHIDRA_FIELD(g_war, 12, 4) - 1 < 4) {
    return;
  }
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    tmp_b5 = g_DMOptions[0xc] & 0x20;
joined_r0x001083aa:
    if (tmp_b5 != 0) {
      return;
    }
  }
  else if (GHIDRA_FIELD(g_gametype, 12, 4) == 7) {
    tmp_b5 = g_TDMOptions[0xc] & 4;
    goto joined_r0x001083aa;
  }
  tmp_l12 = (long double)BG_GetFromTable(&chargeCost_Artillery,param_1[100] + 0xed0,3);
  tmp_i7 = jP_DoChargeCost(param_1,(float)tmp_l12);
  if (tmp_i7 == 0) {
    return;
  }
  tmp_i7 = g_unk_02aa29b0;
  if (*(int *)(param_1[100] + 3000) != 1) {
    tmp_i7 = g_unk_02aa29b4;
  }
  if (0 < tmp_i7) {
    param_1[0xda] = 0;
    tmp_i7 = nitrox_TempEventFromQueue(&vec3_origin,0x5b);
    *(uint32_t *)(tmp_i7 + 0xf4) = 0;
    *(uint32_t *)(tmp_i7 + 0x10c) = 1;
    *(int *)(tmp_i7 + 300) = ((int)(param_1 + -0x24f928) >> 9) * -0x55555555;
    *(uint32_t *)(tmp_i7 + 0x128) = 0x820;
    if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 2) == 0) {
      if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 4) == 0) {
        return;
      }
      tmp_l12 = (long double)BG_GetFromTable(&chargeCost_Artillery,param_1[100] + 0xed0,3);
      tmp_i7 = param_1[100];
      if (tmp_i7 == 0) {
        return;
      }
      if (GHIDRA_FIELD(g_noCharge, 12, 4) != 0) {
        return;
      }
      tmp_i8 = *(int *)(tmp_i7 + 0x478);
      tmp_l12 = tmp_l12 * (long double)0.5;
    }
    else {
      tmp_l12 = (long double)BG_GetFromTable(&chargeCost_Artillery,param_1[100] + 0xed0,3);
      tmp_i7 = param_1[100];
      if (tmp_i7 == 0) {
        return;
      }
      if (GHIDRA_FIELD(g_noCharge, 12, 4) != 0) {
        return;
      }
      tmp_i8 = *(int *)(tmp_i7 + 0x478);
    }
    *(int *)(tmp_i7 + 0x478) =
         (int)ROUND((long double)tmp_i8 -
                    (long double)(int)(&g_unk_02a983f8)[*(int *)(tmp_i7 + 3000)] * tmp_l12);
    return;
  }
  AngleVectors(param_1[100] + 0xb0,&forward,&right,&up);
  local_90 = (float)param_1[6];
  local_8c = (float)param_1[7];
  if ((int)param_1[0xb2] < 1) {
    local_88 = (float)param_1[8] + 25.0;
    tmp_i7 = param_1[100];
    if (tmp_i7 == 0) goto LAB_0010844a;
  }
  else {
    tmp_i7 = param_1[100];
    local_88 = (float)*(int *)(tmp_i7 + 0xbc) + (float)param_1[8];
  }
  if (*(float *)(tmp_i7 + 0x3c) != 0.0) {
    AngleVectors(tmp_i7 + 0xb0,&local_60,&local_54,0);
    tmp_f4 = *(float *)(param_1[100] + 0x3c);
    local_90 = local_90 + local_54 * tmp_f4;
    local_8c = local_8c + local_50 * tmp_f4;
    local_88 = (local_4c * tmp_f4 + local_88) - ABS(tmp_f4 / 3.5);
  }
LAB_0010844a:
  local_d4 = &local_54;
  local_84 = forward * 8192.0 + local_90;
  local_80 = g_unk_02e432f0 * 8192.0 + local_8c;
  local_7c = g_unk_02e432f4 * 8192.0 + local_88;
  trap_Trace(local_d4,&local_90,0,0,&local_84,*param_1,0x6000001);
  if ((local_28 & 0x10) == 0) {
    local_6c = local_48;
    local_68 = local_44;
    local_64 = local_40;
    local_78 = local_48;
    local_74 = local_44;
    local_70 = local_40 + 4096.0;
    trap_Trace(local_d4,&local_6c,0,0,&local_78,*param_1,0x6000001);
    if ((1.0 <= local_4c) || ((local_28 & 0x10) != 0)) {
      if (*(int *)(param_1[100] + 3000) == 1) {
        g_unk_02aa29b0 = g_unk_02aa29b0 + GHIDRA_FIELD(team_artyTime, 12, 4) * 1000;
      }
      else {
        g_unk_02aa29b4 = g_unk_02aa29b4 + GHIDRA_FIELD(team_artyTime, 12, 4) * 1000;
      }
      tmp_i7 = ((int)(param_1 + -0x24f928) >> 9) * -0x55555555;
      tmp_i8 = nitrox_TempEventFromQueue(&vec3_origin,0x5b);
      tmp_f6 = local_40;
      *(int *)(tmp_i8 + 300) = tmp_i7;
      *(uint32_t *)(tmp_i8 + 0xf4) = 2;
      *(uint32_t *)(tmp_i8 + 0x128) = 0x820;
      *(uint32_t *)(tmp_i8 + 0x10c) = 1;
      local_78 = local_48;
      local_74 = local_44;
      local_70 = local_40;
      tmp_f4 = local_40 - 8192.0;
      tmp_l12 = (long double)BG_GetFromTable(artilleryBombs,param_1[100] + 0xed0,3);
      if (0 < (int)ROUND(tmp_l12)) {
        local_e8 = 0;
        do {
          tmp_i9 = G_Spawn();
          *(uint32_t *)(tmp_i9 + 4) = 3;
          *(uint32_t *)(tmp_i9 + 0x128) = 1;
          *(void **)(tmp_i9 + 0x2a4) = artilleryThink;
          *(uint32_t *)(tmp_i9 + 0xe8) = 0xd;
          *(uint32_t *)(tmp_i9 + 0x180) = *param_1;
          tmp_u10 = *param_1;
          *(uint32_t **)(tmp_i9 + 0x218) = param_1;
          *(uint32_t *)(tmp_i9 + 0xac) = tmp_u10;
          *(uint32_t *)(tmp_i9 + 0x108) = *(uint32_t *)(param_1[100] + 3000);
          tmp_i8 = g_unk_00abe908;
          if (local_e8 == 0) {
            *(uint32_t *)(tmp_i9 + 0xc) = 0;
            *(uint32_t *)(tmp_i9 + 0x128) = 0x20;
            *(uint32_t *)(tmp_i9 + 0x2d0) = 0;
            *(int *)(tmp_i9 + 0x29c) = tmp_i8 + 0x1194;
            *(char **)(tmp_i9 + 0x1a4) = "props_explosion";
            *(void **)(tmp_i9 + 0x2a4) = nitrox_artillerySpotter_Think;
            tmp_i8 = g_unk_00abe908;
            *(uint32_t *)(tmp_i9 + 0x2d4) = 0x5a;
            *(uint32_t *)(tmp_i9 + 0x2d8) = 0x32;
            *(uint32_t *)(tmp_i9 + 0x2e4) = 7;
            *(uint32_t *)(tmp_i9 + 0x39c) = 1000;
            *(uint32_t *)(tmp_i9 + 0x318) = 0x43960000;
            *(uint32_t *)(tmp_i9 + 0x90) = 1;
            *(uint32_t *)(tmp_i9 + 0x2dc) = 0x19;
            *(uint32_t *)(tmp_i9 + 0x2e0) = 0x19;
            *(uint32_t *)(tmp_i9 + 0x1d4) = 0x6000081;
            *(int *)(tmp_i9 + 0x10) = tmp_i8;
            tmp_u11 = rand();
            tmp_f1 = (float)(tmp_u11 & 0x7fff) / 32767.0 - 0.5;
            local_78 = (tmp_f1 + tmp_f1) * 50.0;
            tmp_u11 = rand();
            tmp_f1 = (float)(tmp_u11 & 0x7fff) / 32767.0 - 0.5;
            local_74 = (tmp_f1 + tmp_f1) * 50.0;
          }
          else {
            tmp_i8 = local_e8 * 2000 + 0x22f6 + g_unk_00abe908;
            local_dc = rand();
            local_dc = local_dc & 0x7fff;
            tmp_f1 = (float)local_dc / 32767.0 - 0.5;
            *(int *)(tmp_i9 + 0x29c) = (int)ROUND(((tmp_f1 + tmp_f1) * 800.0 + (float)tmp_i8) - 600.0);
            *(char **)(tmp_i9 + 0x1a4) = "air strike";
            *(uint32_t *)(tmp_i9 + 0x3fc) = 0x40000000;
            *(uint32_t *)(tmp_i9 + 0x2d0) = 0;
            tmp_u10 = nitrox_GetWeaponSplashDamage(0xd);
            *(uint32_t *)(tmp_i9 + 0x2d4) = tmp_u10;
            tmp_u10 = nitrox_GetWeaponSplashDamageRadius(0xd);
            *(uint32_t *)(tmp_i9 + 0xc) = 0;
            *(uint32_t *)(tmp_i9 + 0x1d4) = 0x6000081;
            *(uint32_t *)(tmp_i9 + 0x2d8) = tmp_u10;
            *(uint32_t *)(tmp_i9 + 0x2dc) = 0x19;
            *(uint32_t *)(tmp_i9 + 0x2e0) = 0x19;
            *(int *)(tmp_i9 + 0x10) = g_unk_00abe908;
            tmp_u11 = rand();
            tmp_f1 = (float)(tmp_u11 & 0x7fff) / 32767.0 - 0.5;
            local_78 = (tmp_f1 + tmp_f1) * 250.0;
            tmp_u11 = rand();
            tmp_f1 = (float)(tmp_u11 & 0x7fff) / 32767.0 - 0.5;
            local_74 = (tmp_f1 + tmp_f1) * 250.0;
          }
          local_78 = local_6c + local_78;
          *(float *)(tmp_i9 + 0x18) = local_78;
          local_74 = local_74 + local_68;
          *(float *)(tmp_i9 + 0x1c) = local_74;
          *(float *)(tmp_i9 + 0x20) = local_64 + 0.0;
          local_70 = tmp_f6;
          local_60 = local_78;
          local_5c = local_74;
          local_58 = tmp_f4;
          trap_Trace(local_d4,&local_78,0,0,&local_60,*param_1,0x6000001);
          if (local_4c == 1.0) {
            tmp_f1 = *(float *)(tmp_i9 + 0x18);
            tmp_f2 = *(float *)(tmp_i9 + 0x1c);
            tmp_f3 = *(float *)(tmp_i9 + 0x20);
          }
          else {
            *(float *)(tmp_i9 + 0x18) = local_48;
            *(float *)(tmp_i9 + 0x1c) = local_44;
            *(float *)(tmp_i9 + 0x20) = local_40;
            tmp_f1 = local_48;
            tmp_f2 = local_44;
            tmp_f3 = local_40;
          }
          local_e8 = local_e8 + 1;
          *(float *)(tmp_i9 + 0x168) = tmp_f1;
          *(float *)(tmp_i9 + 0x16c) = tmp_f2;
          *(float *)(tmp_i9 + 0x170) = tmp_f3;
          *(uint32_t *)(tmp_i9 + 0x24) = 0;
          *(uint32_t *)(tmp_i9 + 0x28) = 0;
          *(uint32_t *)(tmp_i9 + 0x2c) = 0;
        } while (local_e8 != (int)ROUND(tmp_l12));
      }
      if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
        *(int *)(param_1[100] + 0xdb0) = *(int *)(param_1[100] + 0xdb0) + 1;
      }
      tmp_u10 = Bot_WeaponGameToBot(0xd);
      Bot_Event_FireWeapon(tmp_i7,tmp_u10,0);
    }
    else {
      tmp_i7 = nitrox_TempEventFromQueue(&vec3_origin,0x5b);
      *(uint32_t *)(tmp_i7 + 0xf4) = 1;
      *(uint32_t *)(tmp_i7 + 0x128) = 0x820;
      *(uint32_t *)(tmp_i7 + 0x10c) = 1;
      *(int *)(tmp_i7 + 300) = ((int)(param_1 + -0x24f928) >> 9) * -0x55555555;
      if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 2) == 0) {
        if ((GHIDRA_FIELD(g_fieldOps, 12, 4) & 4) != 0) {
          tmp_l12 = (long double)BG_GetFromTable(&chargeCost_Artillery,param_1[100] + 0xed0,3);
          jP_UnDoChargeCost(param_1,3,(float)(tmp_l12 * (long double)0.5));
        }
      }
      else {
        tmp_l12 = (long double)BG_GetFromTable(&chargeCost_Artillery,param_1[100] + 0xed0,3);
        jP_UnDoChargeCost(param_1,3,(float)tmp_l12);
      }
    }
  }
  return;
}

int G_GetWeaponDamage(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(BG_Weapons + param_1 * 0x6b0 + 0x5d4);
  if (tmp_i1 == 0) {
    tmp_i1 = *(int *)(ammoTableMP + param_1 * 0x48 + 0x28);
  }
  return tmp_i1;
}

long double G_GetWeaponSpread(int param_1)
{
  char *tmp_pc1;
  long double tmp_l2;
  
  if (*(int *)(BG_Weapons + param_1 * 0x6b0 + 0x5d8) == 0) {
    switch(param_1) {
    default:
      if (param_1 - 1U < 0x33) {
        tmp_pc1 = (char *)(param_1 * 0x6b0 + 0x898ef4);
      }
      else {
        tmp_pc1 = "^1invalid";
      }
      G_Printf("^1ERROR : ^7G_GetWeaponSpread ^9no case for weapon %d (%s)\n",param_1,tmp_pc1);
    case 1:
    case 5:
    case 0x2f:
      return (long double)0;
    case 2:
    case 7:
    case 0xe:
    case 0x22:
    case 0x23:
    case 0x26:
    case 0x2c:
    case 0x2d:
      tmp_l2 = (long double)600.0;
      break;
    case 3:
    case 8:
      tmp_l2 = (long double)400.0;
      break;
    case 10:
    case 0x29:
      tmp_l2 = (long double)200.0;
      break;
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x1e:
      tmp_l2 = (long double)250.0;
      break;
    case 0x1d:
    case 0x2e:
      tmp_l2 = (long double)2500.0;
      break;
    case 0x1f:
      tmp_l2 = (long double)500.0;
      break;
    case 0x27:
    case 0x28:
      tmp_l2 = (long double)700.0;
    }
  }
  else {
    tmp_l2 = (long double)*(int *)(BG_Weapons + param_1 * 0x6b0 + 0x5d8);
  }
  return tmp_l2;
}

void Bullet_Fire(int param_1,float param_2,uint32_t param_3,uint32_t param_4)
{
  long double tmp_l1;
  uint8_t local_18 [12];
  
  switch(*(int *)(param_1 + 0xe8)) {
  case 2:
  case 3:
  case 7:
  case 8:
  case 10:
  case 0xe:
  case 0x22:
  case 0x23:
  case 0x26:
  case 0x2c:
  case 0x2d:
    if (*(int *)(*(int *)(param_1 + 400) + 0xc40) < 3) break;
    param_2 = param_2 * 0.65;
    if (1 < GHIDRA_FIELD(n_proneDelay, 12, 4) - 1) goto LAB_00109dc3;
    goto LAB_00109e80;
  case 0x2e:
    muzzleTrace = forward * 48.0 + muzzleTrace;
    g_unk_02e432e4 = g_unk_02e432f0 * 48.0 + g_unk_02e432e4;
    g_unk_02e432e8 = g_unk_02e432f4 * 48.0 + g_unk_02e432e8;
  }
  if (GHIDRA_FIELD(n_proneDelay, 12, 4) - 1 < 2) {
LAB_00109e80:
    if ((g_unk_00abe908 - *(int *)(*(int *)(param_1 + 400) + 0x52d0) < 1000) &&
       ((*(byte *)(*(int *)(param_1 + 400) + 0x6a) & 8) != 0)) {
      if (*(int *)(BG_Weapons + *(int *)(param_1 + 0xe8) * 0x6b0 + 0x5d8) == 0) {
        tmp_l1 = (long double)G_GetWeaponSpread_part_6();
      }
      else {
        tmp_l1 = (long double)*(int *)(BG_Weapons + *(int *)(param_1 + 0xe8) * 0x6b0 + 0x5d8);
      }
      param_2 = (float)(tmp_l1 + tmp_l1);
    }
  }
LAB_00109dc3:
  Bullet_Endpos(param_1,param_2,local_18);
  if ((g_antilag[0xc] & 4) != 0) {
    nitrox_DrawHitboxesOnShoot(param_1);
  }
  G_HistoricalTraceBegin(param_1);
  Bullet_Fire_Extended(param_1,param_1,&muzzleTrace,local_18,param_2,param_3,param_4,1);
  G_HistoricalTraceEnd(param_1);
  return;
}

void weapon_gpg40_fire(uint32_t *param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  int tmp_i4;
  float tmp_f5;
  float tmp_f6;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [8];
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  uint32_t uStack_14;
  
  uStack_14 = 0x109efd;
  AngleVectors(param_1[100] + 0xb0,&forward,0,0);
  tmp_u1 = *param_1;
  local_6c = muzzleEffect;
  local_68 = g_unk_02e43314;
  local_64 = g_unk_02e43318;
  local_58 = (float)param_1[8] + (float)*(int *)(param_1[100] + 0xbc);
  local_60 = (float)param_1[6];
  local_5c = (float)param_1[7];
  local_78 = forward * 32.0 + local_60;
  local_74 = g_unk_02e432f0 * 32.0 + local_5c;
  local_70 = g_unk_02e432f4 * 32.0 + local_58;
  tmp_u2 = tv(0x40800000,0x40800000,0x40c00000);
  tmp_u3 = tv(0xc0800000,0xc0800000,0);
  trap_Trace(local_54,&local_60,tmp_u3,tmp_u2,&local_78,tmp_u1,0x6000081);
  if (local_4c < 1.0) {
    tmp_f5 = floorf(local_48);
    tmp_f6 = ceilf(local_48);
    local_6c = tmp_f5;
    if (local_48 < local_60) {
      local_6c = tmp_f6;
    }
    tmp_f5 = floorf(local_44);
    tmp_f6 = ceilf(local_44);
    local_68 = tmp_f5;
    if (local_44 < local_5c) {
      local_68 = tmp_f6;
    }
    tmp_f5 = floorf(local_40);
    tmp_f6 = ceilf(local_40);
    local_64 = tmp_f5;
    if (local_40 < local_58) {
      local_64 = tmp_f6;
    }
  }
  else {
    tmp_u1 = *param_1;
    tmp_u2 = tv(0x40800000,0x40800000,0x40c00000);
    tmp_u3 = tv(0xc0800000,0xc0800000,0);
    trap_Trace(local_54,&local_78,tmp_u3,tmp_u2,&local_6c,tmp_u1,0x6000081);
    if (local_4c < 1.0) {
      tmp_f5 = floorf(local_48);
      tmp_f6 = ceilf(local_48);
      local_6c = tmp_f5;
      if (local_48 < local_78) {
        local_6c = tmp_f6;
      }
      tmp_f5 = floorf(local_44);
      tmp_f6 = ceilf(local_44);
      local_68 = tmp_f5;
      if (local_44 < local_74) {
        local_68 = tmp_f6;
      }
      tmp_f5 = floorf(local_40);
      tmp_f6 = ceilf(local_40);
      local_64 = tmp_f5;
      if (local_40 < local_70) {
        local_64 = tmp_f6;
      }
    }
  }
  forward = forward * 2000.0;
  g_unk_02e432f0 = g_unk_02e432f0 * 2000.0;
  g_unk_02e432f4 = g_unk_02e432f4 * 2000.0;
  tmp_i4 = fire_grenade(param_1,&local_6c,&forward,param_2);
  *(uint32_t *)(tmp_i4 + 0x2d0) = 0;
  return;
}

uint32_t weapon_mortar_fire(uint32_t *param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  float tmp_f5;
  float tmp_f6;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint8_t local_54 [8];
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  
  tmp_i1 = param_1[100];
  local_5c = *(uint32_t *)(tmp_i1 + 0xb4);
  local_58 = *(uint32_t *)(tmp_i1 + 0xb8);
  local_60 = *(float *)(tmp_i1 + 0xb0) - 60.0;
  AngleVectors(&local_60,&forward,0,0);
  local_78 = muzzleEffect;
  local_74 = g_unk_02e43314;
  local_70 = g_unk_02e43318;
  local_6c = forward * 32.0 + muzzleEffect;
  local_68 = g_unk_02e432f0 * 32.0 + g_unk_02e43314;
  local_64 = g_unk_02e432f4 * 32.0 + g_unk_02e43318;
  forward = forward * 3300.0;
  g_unk_02e432f0 = g_unk_02e432f0 * 3300.0;
  g_unk_02e432f4 = g_unk_02e432f4 * 1650.0;
  tmp_u4 = *param_1;
  tmp_u2 = tv(0x40800000,0x40800000,0x40c00000);
  tmp_u3 = tv(0xc0800000,0xc0800000,0);
  trap_Trace(local_54,&local_6c,tmp_u3,tmp_u2,&local_78,tmp_u4,0x6000081);
  if (local_4c < 1.0) {
    tmp_f5 = floorf(local_48);
    tmp_f6 = ceilf(local_48);
    local_78 = tmp_f5;
    if (local_48 < local_6c) {
      local_78 = tmp_f6;
    }
    tmp_f5 = floorf(local_44);
    tmp_f6 = ceilf(local_44);
    local_74 = tmp_f5;
    if (local_44 < local_68) {
      local_74 = tmp_f6;
    }
    tmp_f5 = floorf(local_40);
    tmp_f6 = ceilf(local_40);
    local_70 = tmp_f5;
    if (local_40 < local_64) {
      local_70 = tmp_f6;
    }
  }
  tmp_u4 = fire_grenade(param_1,&local_78,&forward,param_2);
  nitrox_TempMissileCam(param_1,tmp_u4);
  return tmp_u4;
}

void weapon_grenadelauncher_fire(uint32_t *param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  float tmp_f3;
  float tmp_f4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  float local_88;
  uint32_t local_7c;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [4];
  int local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  
  if ((float)param_1[0xf] < 0.0) {
    tmp_f3 = -(float)param_1[0xf];
    if (tmp_f3 < 30.0) {
      tmp_f3 = 1.0 - tmp_f3 / 30.0;
      tmp_f4 = tmp_f3 * 0.5;
      local_88 = tmp_f3 * 0.3 + 1.0;
    }
    else {
      local_88 = 1.0;
      tmp_f4 = 0.0;
    }
    g_unk_02e432f4 = tmp_f4 + g_unk_02e432f4;
  }
  else {
    g_unk_02e432f4 = g_unk_02e432f4 + 0.5;
    local_88 = 1.3;
  }
  VectorNormalizeFast(&forward);
  tmp_f3 = -(float)param_1[0xf];
  if (tmp_f3 < 50.0) {
    if ((tmp_f3 <= -50.0) || (tmp_f3 = tmp_f3 / 100.0 + 0.5, tmp_f3 < 0.1)) {
      tmp_f3 = 0.1;
    }
  }
  else {
    tmp_f3 = 1.0;
  }
  switch(param_2) {
  case 4:
  case 9:
  case 0x15:
  case 0x1c:
  case 0x30:
  case 0x32:
    tmp_f4 = 900.0;
    break;
  default:
    tmp_f4 = 400.0;
  }
  local_88 = tmp_f3 * tmp_f4 * local_88;
  local_60 = (float)(int)ROUND(forward * 8.0 + muzzleEffect);
  local_5c = (float)(int)ROUND(g_unk_02e432f0 * 8.0 + g_unk_02e43314);
  local_58 = (float)(int)ROUND((g_unk_02e432f4 * 8.0 + g_unk_02e43318) - 8.0);
  forward = forward * local_88;
  g_unk_02e432f0 = g_unk_02e432f0 * local_88;
  g_unk_02e432f4 = local_88 * g_unk_02e432f4;
  local_6c = (float)param_1[6];
  local_68 = (float)param_1[7];
  tmp_u1 = *param_1;
  local_64 = (float)*(int *)(param_1[100] + 0xbc) + (float)param_1[8];
  switch(param_2 + -0xf) {
  case 0:
  case 0xb:
  case 0x21:
    local_88 = (float)tv(0x41400000,0x41400000,0x41a00000);
    tmp_u6 = 0xc1400000;
    tmp_u5 = 0xc1400000;
    break;
  default:
    local_88 = (float)tv(0x40800000,0x40800000,0x40c00000);
    tmp_u6 = 0xc0800000;
    tmp_u5 = 0xc0800000;
    break;
  case 10:
  case 0x24:
    local_88 = (float)tv(0x41800000,0x41800000,0x41800000);
    tmp_u6 = 0xc1800000;
    tmp_u5 = 0xc1800000;
  }
  tmp_u5 = tv(tmp_u5,tmp_u6,0);
  trap_Trace(local_54,&local_6c,tmp_u5,local_88,&local_60,tmp_u1,0x6000081);
  if (local_50 == 0) {
    if (local_4c < 1.0) {
      tmp_f3 = floorf(local_48);
      tmp_f4 = ceilf(local_48);
      local_60 = tmp_f3;
      if (local_48 < local_6c) {
        local_60 = tmp_f4;
      }
      tmp_f3 = floorf(local_44);
      tmp_f4 = ceilf(local_44);
      local_5c = tmp_f3;
      if (local_44 < local_68) {
        local_5c = tmp_f4;
      }
      tmp_f3 = floorf(local_40);
      tmp_f4 = ceilf(local_40);
      local_58 = tmp_f3;
      if (local_40 < local_64) {
        local_58 = tmp_f4;
      }
    }
  }
  else {
    local_6c = forward;
    local_68 = g_unk_02e432f0;
    local_64 = g_unk_02e432f4;
    VectorNormalizeFast(&local_6c);
    tmp_u1 = *param_1;
    local_6c = local_6c * -24.0 + (float)param_1[0x5a];
    local_68 = local_68 * -24.0 + (float)param_1[0x5b];
    local_64 = local_64 * -24.0 + (float)param_1[0x5c];
    switch(param_2 + -0xf) {
    case 0:
    case 0xb:
    case 0x21:
      local_7c = tv(0x41400000,0x41400000,0x41a00000);
      tmp_u6 = 0xc1400000;
      tmp_u5 = 0xc1400000;
      break;
    default:
      local_7c = tv(0x40800000,0x40800000,0x40c00000);
      tmp_u6 = 0xc0800000;
      tmp_u5 = 0xc0800000;
      break;
    case 10:
    case 0x24:
      local_7c = tv(0x41800000,0x41800000,0x41800000);
      tmp_u6 = 0xc1800000;
      tmp_u5 = 0xc1800000;
    }
    tmp_u5 = tv(tmp_u5,tmp_u6,0);
    trap_Trace(local_54,&local_6c,tmp_u5,local_7c,&local_60,tmp_u1,0x6000081);
    local_60 = local_48;
    local_5c = local_44;
    local_58 = local_40;
  }
  tmp_i2 = fire_grenade(param_1,&local_60,&forward,param_2);
  *(uint32_t *)(tmp_i2 + 0x2d0) = 0;
  switch(param_2) {
  case 0x15:
    *(uint32_t *)(tmp_i2 + 0x108) = *(uint32_t *)(param_1[100] + 3000);
    if ((*(byte *)(param_1[100] + 0xedc) & 8) == 0) {
      *(uint32_t *)(tmp_i2 + 0x2e4) = 1;
      *(int *)(tmp_i2 + 0x29c) = g_unk_00abe908 + 0x9c4;
      *(void **)(tmp_i2 + 0x2a4) = weapon_checkAirStrikeThink1;
    }
    else {
      *(uint32_t *)(tmp_i2 + 0x2e4) = 2;
      *(int *)(tmp_i2 + 0x29c) = g_unk_00abe908 + 0xdac;
      *(void **)(tmp_i2 + 0x2a4) = weapon_checkAirStrikeThink2;
    }
    break;
  case 0x19:
  case 0x33:
    *(uint *)(tmp_i2 + 0x90) = (uint)(*(int *)(param_1[100] + 3000) == 1);
    return;
  case 0x1c:
    *(uint32_t *)(tmp_i2 + 0x10c) = 0x10;
    *(void **)(tmp_i2 + 0x2a4) = weapon_smokeBombExplode;
    return;
  case 0x30:
    *(uint32_t *)(tmp_i2 + 0x10c) = 1;
    return;
  case 0x32:
    *(uint32_t *)(tmp_i2 + 0x10c) = 0x10;
    *(void **)(tmp_i2 + 0x2a4) = weapon_smokeBombExplode;
    *(uint32_t *)(tmp_i2 + 0x110) = 1;
    return;
  }
  return;
}

void Weapon_Panzerfaust_Fire(uint32_t param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint tmp_u6;
  
  tmp_u6 = rand();
  tmp_f1 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
  if (GHIDRA_FIELD(BG_Weapons, 10056, 4) == 0) {
    tmp_f2 = 0.0;
  }
  else {
    tmp_f2 = (float)(int)GHIDRA_FIELD(BG_Weapons, 10056, 4) / 1000.0;
  }
  tmp_f2 = tmp_f2 * (tmp_f1 + tmp_f1);
  tmp_u6 = rand();
  tmp_f1 = (float)(tmp_u6 & 0x7fff) / 32767.0 - 0.5;
  if (GHIDRA_FIELD(BG_Weapons, 10056, 4) == 0) {
    tmp_f3 = 0.0;
  }
  else {
    tmp_f3 = (float)(int)GHIDRA_FIELD(BG_Weapons, 10056, 4) / 1000.0;
  }
  tmp_f3 = tmp_f3 * (tmp_f1 + tmp_f1);
  tmp_f5 = forward * 16.0;
  *param_2 = tmp_f5;
  tmp_f4 = g_unk_02e432f0 * 16.0;
  param_2[1] = tmp_f4;
  tmp_f1 = g_unk_02e432f4 * 16.0;
  param_2[2] = tmp_f1;
  tmp_f5 = right * tmp_f2 + tmp_f5;
  *param_2 = tmp_f5;
  tmp_f4 = g_unk_02e43308 * tmp_f2 + tmp_f4;
  param_2[1] = tmp_f4;
  tmp_f1 = tmp_f1 + g_unk_02e4330c * tmp_f2;
  param_2[2] = tmp_f1;
  *param_2 = up * tmp_f3 + tmp_f5;
  param_2[1] = g_unk_02e432fc * tmp_f3 + tmp_f4;
  param_2[2] = tmp_f3 * g_unk_02e43300 + tmp_f1;
  VectorNormalize(param_2);
  fire_rocket(param_1,&muzzleEffect,param_2,5);
  return;
}

void Weapon_FlamethrowerFire(uint32_t *param_1)
{
  float tmp_f1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  uint32_t local_60;
  uint32_t local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  
  tmp_i2 = param_1[100];
  local_78 = (float)param_1[0x5a];
  local_74 = (float)param_1[0x5b];
  local_70 = (float)*(int *)(tmp_i2 + 0xbc) + (float)param_1[0x5c];
  local_84 = up * -6.0 + right * 10.0 + forward * -8.0 + local_78;
  local_80 = g_unk_02e432fc * -6.0 + g_unk_02e43308 * 10.0 + g_unk_02e432f0 * -8.0 + local_74;
  local_7c = g_unk_02e43300 * -6.0 + g_unk_02e4330c * 10.0 + g_unk_02e432f4 * -8.0 + local_70;
  if (*(float *)(tmp_i2 + 0x3c) != 0.0) {
    AngleVectors(tmp_i2 + 0xb0,&local_60,&local_54,0);
    tmp_f1 = *(float *)(param_1[100] + 0x3c);
    local_84 = local_54 * tmp_f1 + local_84;
    local_80 = local_50 * tmp_f1 + local_80;
    local_7c = (local_4c * tmp_f1 + local_7c) - ABS(tmp_f1 / 3.5);
  }
  local_6c = local_78 + forward * 77.0;
  local_68 = g_unk_02e432f0 * 77.0 + local_74;
  local_64 = g_unk_02e432f4 * 77.0 + local_70;
  trap_Trace(&local_54,&local_78,flameChunkMins,flameChunkMaxs,&local_6c,*param_1,0x6000039);
  if (((local_4c != 1.0) &&
      (tmp_f1 = (float)param_1[0x5c], ((float)param_1[0x4f] + tmp_f1) - 8.0 < local_40)) &&
     (local_40 < tmp_f1)) {
    local_78 = local_78 - local_48;
    local_74 = local_74 - local_44;
    if (local_74 * local_74 + local_78 * local_78 < 441.0) {
      local_60 = param_1[0x5a];
      param_1[0xe4] = param_1[0xe4] + 5;
      tmp_u3 = *param_1;
      local_5c = param_1[0x5b];
      param_1[0xe5] = g_unk_00abe908;
      local_58 = tmp_f1;
      if (param_1[0x115] != g_unk_00abe904) {
        tmp_u4 = GHIDRA_FIELD(BG_Weapons, 11764, 4);
        if (GHIDRA_FIELD(BG_Weapons, 11764, 4) == 0) {
          tmp_u4 = GHIDRA_FIELD(ammoTableMP, 472, 4);
        }
        G_Damage(param_1,param_1,param_1,&vec3_origin,&local_60,tmp_u4,0,0x11);
        param_1[0x115] = g_unk_00abe904;
      }
      tmp_i2 = g_unk_00abe908;
      if ((param_1[100] != 0) && (((int)param_1[0xb2] < 1 || (0 < (int)param_1[0xe4])))) {
        if ((int)param_1[0x40] < g_unk_00abe908) {
          param_1[0x3f] = g_unk_00abe908;
        }
        param_1[0x40] = tmp_i2 + 2000;
        param_1[0xe6] = tmp_u3;
        *(int *)(param_1[100] + 0x424) = tmp_i2;
      }
    }
  }
  fire_flamechunk(param_1,&local_84,&forward);
  tmp_i2 = g_unk_00abe908;
  param_1[0x4a] = param_1[0x4a] | 0x20;
  *(int *)(param_1[100] + 0x5380) = tmp_i2 + 0x9c4;
  return;
}

void CalcMuzzlePoint(int param_1,uint param_2,uint32_t param_3,float *param_4,float *param_5,
                    float *param_6)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint8_t local_34 [12];
  float local_28;
  float local_24;
  float local_20;
  
  tmp_f1 = *(float *)(param_1 + 0x168);
  *param_6 = tmp_f1;
  tmp_f2 = *(float *)(param_1 + 0x16c);
  param_6[1] = tmp_f2;
  tmp_f3 = *(float *)(param_1 + 0x170);
  param_6[2] = tmp_f3;
  tmp_i5 = *(int *)(param_1 + 400);
  if ((30.0 < *(float *)(tmp_i5 + 0xb0)) && ((*(byte *)(tmp_i5 + 0x68) & 0x10) != 0)) {
    tmp_f3 = tmp_f3 + 30.0;
    param_6[2] = tmp_f3;
    if (param_2 < 0x33) goto LAB_0010b3d2;
_L2006:
    tmp_f1 = *param_4 * 6.0 + tmp_f1;
    *param_6 = tmp_f1;
    tmp_f2 = param_4[1] * 6.0 + tmp_f2;
    param_6[1] = tmp_f2;
    tmp_f3 = param_4[2] * 6.0 + tmp_f3;
    param_6[2] = tmp_f3;
    tmp_f1 = *param_5 * -4.0 + tmp_f1;
    *param_6 = tmp_f1;
    tmp_f2 = param_5[1] * -4.0 + tmp_f2;
    param_6[1] = tmp_f2;
    tmp_f3 = param_5[2] * -4.0 + tmp_f3;
    param_6[2] = tmp_f3;
    if (param_2 == 0) goto LAB_0010b48a;
    goto LAB_0010b456;
  }
  tmp_f3 = (float)*(int *)(tmp_i5 + 0xbc) + tmp_f3;
  param_6[2] = tmp_f3;
  if (0x32 < param_2) goto _L2006;
LAB_0010b3d2:
  switch((int)&_GLOBAL_OFFSET_TABLE_ + (&switchD_0010b3db::switchdataD_0025c418)[param_2]) {
  case 0x10b3f0:
    goto _L2006;
  case 0x10b450:
    break;
  case 0x10b4f0:
    tmp_f1 = *param_4 * -6.0 + tmp_f1;
    *param_6 = tmp_f1;
    tmp_f2 = param_4[1] * -6.0 + tmp_f2;
    param_6[1] = tmp_f2;
    tmp_f3 = param_4[2] * -6.0 + tmp_f3;
    param_6[2] = tmp_f3;
    *param_6 = *param_5 * -4.0 + tmp_f1;
    param_6[1] = param_5[1] * -4.0 + tmp_f2;
    param_6[2] = param_5[2] * -4.0 + tmp_f3;
    break;
  case 0x10b548:
    tmp_f4 = 10.0;
LAB_0010b54e:
    *param_6 = *param_4 * tmp_f4 + tmp_f1;
    param_6[1] = param_4[1] * tmp_f4 + tmp_f2;
    param_6[2] = tmp_f4 * param_4[2] + tmp_f3;
    break;
  case 0x10b578:
    tmp_f4 = 20.0;
    goto LAB_0010b54e;
  }
LAB_0010b456:
  tmp_i5 = *(int *)(param_1 + 400);
  if ((tmp_i5 == 0) || (*(float *)(tmp_i5 + 0x3c) == 0.0)) {
    tmp_f1 = *param_6;
    tmp_f2 = param_6[1];
    tmp_f3 = param_6[2];
  }
  else {
    AngleVectors(tmp_i5 + 0xb0,local_34,&local_28,0);
    tmp_f1 = local_28 * *(float *)(*(int *)(param_1 + 400) + 0x3c) + *param_6;
    *param_6 = tmp_f1;
    tmp_f2 = local_24 * *(float *)(*(int *)(param_1 + 400) + 0x3c) + param_6[1];
    param_6[1] = tmp_f2;
    tmp_f3 = local_20 * *(float *)(*(int *)(param_1 + 400) + 0x3c) + param_6[2];
    param_6[2] = tmp_f3;
    tmp_f3 = tmp_f3 - ABS(*(float *)(*(int *)(param_1 + 400) + 0x3c) / 3.5);
  }
LAB_0010b48a:
  *param_6 = (float)(int)ROUND(tmp_f1);
  param_6[1] = (float)(int)ROUND(tmp_f2);
  param_6[2] = (float)(int)ROUND(tmp_f3);
  return;
}

void CalcMuzzlePointForActivate(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  float *in_stack_00000014;
  int in_stack_00000018;
  uint8_t local_24 [12];
  float local_18;
  float local_14;
  float local_10;
  
  *in_stack_00000014 = *(float *)(param_1 + 0x18);
  in_stack_00000014[1] = *(float *)(param_1 + 0x1c);
  tmp_f1 = *(float *)(param_1 + 0x20);
  in_stack_00000014[2] = tmp_f1;
  if (*(int *)(param_1 + 0x2c8) < 1) {
    in_stack_00000014[2] = tmp_f1 + 25.0;
  }
  else {
    tmp_i2 = *(int *)(param_1 + 400);
    if (((in_stack_00000018 != 0) || (*(float *)(tmp_i2 + 0xb0) <= 30.0)) ||
       ((*(byte *)(tmp_i2 + 0x68) & 0x10) == 0)) {
      in_stack_00000014[2] = (float)*(int *)(tmp_i2 + 0xbc) + tmp_f1;
    }
    else {
      in_stack_00000014[2] = tmp_f1 + 30.0;
    }
  }
  tmp_i2 = *(int *)(param_1 + 400);
  if ((tmp_i2 != 0) && (*(float *)(tmp_i2 + 0x3c) != 0.0)) {
    AngleVectors(tmp_i2 + 0xb0,local_24,&local_18,0);
    *in_stack_00000014 = local_18 * *(float *)(*(int *)(param_1 + 400) + 0x3c) + *in_stack_00000014;
    in_stack_00000014[1] =
         local_14 * *(float *)(*(int *)(param_1 + 400) + 0x3c) + in_stack_00000014[1];
    tmp_f1 = local_10 * *(float *)(*(int *)(param_1 + 400) + 0x3c) + in_stack_00000014[2];
    in_stack_00000014[2] = tmp_f1;
    in_stack_00000014[2] = tmp_f1 - ABS(*(float *)(*(int *)(param_1 + 400) + 0x3c) / 3.5);
    return;
  }
  return;
}

void CalcMuzzlePoints(int param_1,uint param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  int tmp_i6;
  double tmp_d7;
  float local_68;
  float local_40;
  float local_3c;
  float local_38;
  uint8_t local_34 [12];
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i6 = *(int *)(param_1 + 400);
  local_40 = *(float *)(tmp_i6 + 0xb0);
  local_3c = *(float *)(tmp_i6 + 0xb4);
  local_38 = *(float *)(tmp_i6 + 0xb8);
  tmp_i5 = BG_IsScopedWeapon(param_2);
  tmp_i6 = *(int *)(param_1 + 400);
  if (tmp_i5 == 0) {
    if (tmp_i6 != 0) goto LAB_0010b7be;
  }
  else {
    tmp_f2 = *(float *)(tmp_i6 + 0xfd4);
    if (param_2 == 0x29) {
      local_68 = 0.8;
      tmp_f1 = 0.4;
    }
    else {
      local_68 = 0.2;
      tmp_f1 = 0.1;
    }
    tmp_f4 = (float)g_unk_00abe908;
    tmp_f3 = (tmp_f4 / 1000.0) * 0.24 * 3.1415927;
    tmp_d7 = sin((double)(tmp_f3 + tmp_f3));
    local_40 = (tmp_f1 + tmp_f2) * (float)tmp_d7 * 0.13 + local_40;
    tmp_f1 = (tmp_f4 / 1000.0) * 0.12 * 3.1415927;
    tmp_d7 = sin((double)(tmp_f1 + tmp_f1));
    local_3c = (tmp_f2 + local_68) * (float)tmp_d7 * 0.7 + local_3c;
LAB_0010b7be:
    if ((*(byte *)(tmp_i6 + 0x6a) & 0x20) != 0) {
      tmp_f2 = ((float)g_unk_00abe908 / 1000.0) * 0.3 * 3.1415927;
      tmp_d7 = sin((double)tmp_f2);
      local_38 = (float)tmp_d7 * 36.0 + local_38;
      local_3c = (float)tmp_d7 * 24.0 + local_3c;
      tmp_d7 = sin((double)tmp_f2 * 2.5);
      local_40 = (float)tmp_d7 * 12.0 + local_40;
    }
  }
  AngleVectors(&local_40,&forward,&right,&up);
  tmp_i6 = *(int *)(param_1 + 400);
  muzzleTrace = *(float *)(param_1 + 0x18);
  g_unk_02e432e4 = *(float *)(param_1 + 0x1c);
  if (*(int *)(param_1 + 0x2c8) < 1) {
    g_unk_02e432e8 = *(float *)(param_1 + 0x20) + 25.0;
    if (tmp_i6 != 0) goto LAB_0010b892;
  }
  else {
    g_unk_02e432e8 = (float)*(int *)(tmp_i6 + 0xbc) + *(float *)(param_1 + 0x20);
LAB_0010b892:
    if (*(float *)(tmp_i6 + 0x3c) != 0.0) {
      AngleVectors(tmp_i6 + 0xb0,local_34,&local_28,0);
      tmp_i6 = *(int *)(param_1 + 400);
      tmp_f2 = *(float *)(tmp_i6 + 0x3c);
      muzzleTrace = local_28 * tmp_f2 + muzzleTrace;
      g_unk_02e432e4 = local_24 * tmp_f2 + g_unk_02e432e4;
      g_unk_02e432e8 = (local_20 * tmp_f2 + g_unk_02e432e8) - ABS(tmp_f2 / 3.5);
    }
  }
  muzzleEffect = *(float *)(param_1 + 0x168);
  g_unk_02e43314 = *(float *)(param_1 + 0x16c);
  if ((30.0 < *(float *)(tmp_i6 + 0xb0)) && ((*(byte *)(tmp_i6 + 0x68) & 0x10) != 0)) {
    g_unk_02e43318 = *(float *)(param_1 + 0x170) + 30.0;
    if (param_2 < 0x33) goto LAB_0010b909;
_L2065:
    muzzleEffect = up * -4.0 + right * 6.0 + muzzleEffect;
    g_unk_02e43314 = g_unk_02e432fc * -4.0 + g_unk_02e43308 * 6.0 + g_unk_02e43314;
    g_unk_02e43318 = g_unk_02e43300 * -4.0 + g_unk_02e4330c * 6.0 + g_unk_02e43318;
    if (param_2 == 0) goto LAB_0010ba9c;
    goto LAB_0010ba66;
  }
  g_unk_02e43318 = (float)*(int *)(tmp_i6 + 0xbc) + *(float *)(param_1 + 0x170);
  if (0x32 < param_2) goto _L2065;
LAB_0010b909:
  switch((int)&_GLOBAL_OFFSET_TABLE_ + (&switchD_0010b913::switchdataD_0025c4e4)[param_2]) {
  case 0x10b9f0:
    goto _L2065;
  case 0x10ba60:
    break;
  case 0x10bb00:
    tmp_f2 = 20.0;
    goto LAB_0010bb06;
  case 0x10bb40:
    muzzleEffect = up * -4.0 + right * -6.0 + muzzleEffect;
    g_unk_02e43314 = g_unk_02e432fc * -4.0 + g_unk_02e43308 * -6.0 + g_unk_02e43314;
    g_unk_02e43318 = g_unk_02e43300 * -4.0 + g_unk_02e4330c * -6.0 + g_unk_02e43318;
    break;
  case 0x10bba8:
    tmp_f2 = 10.0;
LAB_0010bb06:
    muzzleEffect = right * tmp_f2 + muzzleEffect;
    g_unk_02e43314 = g_unk_02e43308 * tmp_f2 + g_unk_02e43314;
    g_unk_02e43318 = tmp_f2 * g_unk_02e4330c + g_unk_02e43318;
  }
LAB_0010ba66:
  if (*(float *)(tmp_i6 + 0x3c) != 0.0) {
    AngleVectors(tmp_i6 + 0xb0,local_34,&local_28,0);
    tmp_f2 = *(float *)(*(int *)(param_1 + 400) + 0x3c);
    muzzleEffect = local_28 * tmp_f2 + muzzleEffect;
    g_unk_02e43314 = local_24 * tmp_f2 + g_unk_02e43314;
    g_unk_02e43318 = (g_unk_02e43318 + local_20 * tmp_f2) - ABS(tmp_f2 / 3.5);
  }
LAB_0010ba9c:
  muzzleEffect = (float)(int)ROUND(muzzleEffect);
  g_unk_02e43314 = (float)(int)ROUND(g_unk_02e43314);
  g_unk_02e43318 = (float)(int)ROUND(g_unk_02e43318);
  return;
}

void nitrox_tripmine(int param_1)
{
  int tmp_i1;
  long double tmp_l2;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [8];
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  byte local_28;
  int local_20;
  
  tmp_i1 = *(int *)(param_1 + 400);
  local_78 = *(float *)(tmp_i1 + 0x14);
  local_74 = *(float *)(tmp_i1 + 0x18);
  local_70 = (float)*(int *)(tmp_i1 + 0xbc) + *(float *)(tmp_i1 + 0x1c);
  AngleVectors(tmp_i1 + 0xb0,&local_60,0,0);
  local_6c = local_60 * 64.0 + local_78;
  local_68 = local_5c * 64.0 + local_74;
  local_64 = local_58 * 64.0 + local_70;
  trap_Trace(local_54,&local_78,0,0,&local_6c,*(uint32_t *)(*(int *)(param_1 + 400) + 0xa0),
             0x6000001);
  if (((local_4c != 1.0) && ((local_28 & 0x14) == 0)) && (local_20 == 0x3fe)) {
    local_78 = local_48;
    local_74 = local_44;
    local_70 = local_40;
    local_6c = local_3c * 512.0 + local_48;
    local_68 = local_38 * 512.0 + local_44;
    local_64 = local_34 * 512.0 + local_40;
    trap_Trace(local_54,&local_78,0,0,&local_6c,*(uint32_t *)(*(int *)(param_1 + 400) + 0xa0),
               0x6000001);
    if (((local_4c != 1.0) && ((local_28 & 0x14) == 0)) && (local_20 == 0x3fe)) {
      tmp_i1 = nitmod_CountTeamTripmines(*(uint32_t *)(*(int *)(param_1 + 400) + 3000));
      if ((int)GHIDRA_FIELD(team_maxTripmines, 12, 4) <= tmp_i1) {
        nitmod_cp(param_1,0x34);
        return;
      }
      tmp_l2 = (long double)BG_GetFromTable(&chargeCost_Tripmine,*(int *)(param_1 + 400) + 0xed0,1);
      jP_DoChargeCost(param_1,(float)tmp_l2);
      G_PlaceTripmine(param_1);
      return;
    }
  }
  nitmod_cp(param_1,0x30);
  return;
}

void FireWeapon(int param_1)
{
  int *tmp_pi1;
  float tmp_f2;
  uint tmp_u3;
  uint8_t *tmp_pu4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  uint32_t tmp_u8;
  long double tmp_l9;
  int tmp_i10;
  int local_34;
  float local_28;
  float local_24;
  float local_20;
  
  if (*(int *)(*(int *)(param_1 + 400) + 4) == 3) {
    return;
  }
  if ((*(int *)(*(int *)(param_1 + 400) + 0x140) != 0) && (*(int *)(param_1 + 0x368) != 0)) {
    return;
  }
  CalcMuzzlePoints(param_1,*(uint32_t *)(param_1 + 0xe8));
  tmp_i6 = *(int *)(param_1 + 400);
  if (GHIDRA_FIELD(g_userAim, 12, 4) == 0) {
    tmp_f2 = 1.0;
  }
  else {
    tmp_f2 = *(float *)(tmp_i6 + 0xfd4) + 0.15;
    if (1.0 < tmp_f2) {
      tmp_f2 = 1.0;
    }
  }
  if ((((*(byte *)(tmp_i6 + 0x6a) & 4) != 0) && ((*(byte *)(tmp_i6 + 0xd4) & 0x40) != 0)) &&
     (*(int *)(tmp_i6 + 0xbc8) == 3)) {
    if (*(float *)(tmp_i6 + 0x3c) != 0.0) {
      return;
    }
    Weapon_Artillery(param_1);
    return;
  }
  tmp_u3 = BG_WeapStatForWeapon(*(uint32_t *)(param_1 + 0xe8));
  tmp_i6 = *(int *)(param_1 + 400);
  if (*(int *)(tmp_i6 + 0x50) == 0x3ff) {
    tmp_f2 = 2.0;
  }
  tmp_i10 = *(int *)(param_1 + 0xe8);
  switch(tmp_i10) {
  case 0:
  case 0xd:
  case 0x10:
  case 0x11:
  case 0x13:
  case 0x20:
  case 0x21:
  default:
    tmp_u8 = 0;
    local_34 = 1;
    break;
  case 1:
    tmp_u8 = 0;
    Weapon_Knife(param_1);
    tmp_i10 = *(int *)(param_1 + 0xe8);
    local_34 = 1;
    break;
  case 2:
  case 3:
  case 7:
  case 8:
  case 10:
  case 0xe:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x1e:
  case 0x1f:
  case 0x22:
  case 0x23:
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2c:
  case 0x2d:
    tmp_u8 = *(uint32_t *)(BG_Weapons + tmp_i10 * 0x6b0 + 0x68c);
    tmp_i7 = *(int *)(BG_Weapons + tmp_i10 * 0x6b0 + 0x5d4);
    if (tmp_i7 == 0) {
      tmp_i7 = *(int *)(ammoTableMP + tmp_i10 * 0x48 + 0x28);
    }
    if (*(int *)(BG_Weapons + tmp_i10 * 0x6b0 + 0x5d8) == 0) {
      tmp_l9 = (long double)G_GetWeaponSpread_part_6();
    }
    else {
      tmp_l9 = (long double)*(int *)(BG_Weapons + tmp_i10 * 0x6b0 + 0x5d8);
    }
    goto LAB_0010ca90;
  case 4:
  case 9:
    goto LAB_0010c6c4;
  case 5:
    tmp_l9 = (long double)BG_GetFromTable(&chargeCost_Panzer,tmp_i6 + 0xed0,5);
    jP_DoChargeCost(param_1,(float)tmp_l9);
    tmp_u8 = Weapon_Panzerfaust_Fire(param_1,&forward);
    if (*(int *)(param_1 + 400) == 0) goto LAB_0010cbb4;
    AngleVectors(*(int *)(param_1 + 400) + 0xb0,&local_28,0,0);
    local_34 = 1;
    *(float *)(*(int *)(param_1 + 400) + 0x20) =
         local_28 * -64.0 + *(float *)(*(int *)(param_1 + 400) + 0x20);
    *(float *)(*(int *)(param_1 + 400) + 0x24) =
         local_24 * -64.0 + *(float *)(*(int *)(param_1 + 400) + 0x24);
    *(float *)(*(int *)(param_1 + 400) + 0x28) =
         local_20 * -64.0 + *(float *)(*(int *)(param_1 + 400) + 0x28);
    tmp_i10 = *(int *)(param_1 + 0xe8);
    break;
  case 6:
    tmp_u8 = Weapon_FlamethrowerFire(param_1);
LAB_0010cbb4:
    tmp_i10 = *(int *)(param_1 + 0xe8);
    local_34 = 1;
    break;
  case 0xb:
    tmp_i6 = Weapon_Syringe(param_1);
    if (tmp_i6 == 0) {
      tmp_u8 = 0xb;
LAB_0010cdac:
      tmp_i6 = BG_FindClipForWeapon(tmp_u8);
      tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0x290 + tmp_i6 * 4);
      *tmp_pi1 = *tmp_pi1 + 1;
    }
    else if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
      tmp_u8 = 0;
      local_34 = 1;
      tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0xdd0);
      *tmp_pi1 = *tmp_pi1 + 1;
      tmp_i10 = *(int *)(param_1 + 0xe8);
      break;
    }
    goto LAB_0010ca9e;
  case 0xc:
    Weapon_MagicAmmo(param_1);
    goto LAB_0010c86a;
  case 0xf:
  case 0x30:
    tmp_u8 = 1;
    tmp_pu4 = (uint8_t *)&chargeCost_Dynamite;
    goto LAB_0010c68b;
  case 0x12:
    Weapon_Medic(param_1);
LAB_0010c86a:
    local_34 = 1;
    goto LAB_0010c708;
  case 0x14:
    tmp_u8 = 0;
    Weapon_Engineer(param_1);
    tmp_i10 = *(int *)(param_1 + 0xe8);
    local_34 = 1;
    break;
  case 0x15:
    tmp_l9 = (long double)BG_GetFromTable(&chargeCost_Artillery,tmp_i6 + 0xed0,3);
    jP_DoChargeCost(param_1,(float)tmp_l9);
    tmp_i10 = 0x15;
    goto LAB_0010c6c4;
  case 0x19:
  case 0x33:
    tmp_u8 = 1;
    tmp_pu4 = (uint8_t *)&chargeCost_Landmine;
    goto LAB_0010c68b;
  case 0x1a:
    tmp_u8 = 6;
    tmp_pu4 = (uint8_t *)&chargeCost_Satchel;
    goto LAB_0010c68b;
  case 0x1b:
    tmp_i6 = G_ExplodeSatchels(param_1);
    if (tmp_i6 == 0) {
      tmp_i10 = *(int *)(param_1 + 0xe8);
      tmp_u8 = 0;
      local_34 = 0;
    }
    else {
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x1fc) = 0;
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x2fc) = 0;
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x2f8) = 1;
      tmp_u8 = 0;
      G_AddEvent(param_1,0x19,0);
      tmp_i10 = *(int *)(param_1 + 0xe8);
      local_34 = 1;
    }
    break;
  case 0x1c:
  case 0x32:
    tmp_pu4 = chargeCost_Smoke;
    tmp_u8 = 6;
LAB_0010c68b:
    tmp_l9 = (long double)BG_GetFromTable(tmp_pu4,tmp_i6 + 0xed0,tmp_u8);
    jP_DoChargeCost(param_1,(float)tmp_l9);
    tmp_i10 = *(int *)(param_1 + 0xe8);
LAB_0010c6c4:
    tmp_u8 = weapon_grenadelauncher_fire(param_1,tmp_i10);
    local_34 = 1;
    tmp_i10 = *(int *)(param_1 + 0xe8);
    break;
  case 0x1d:
    tmp_i7 = GHIDRA_FIELD(BG_Weapons, 51140, 4);
    if (((*(byte *)(tmp_i6 + 0xc) & 1) == 0) && ((*(byte *)(tmp_i6 + 0x6a) & 8) == 0)) {
      if (GHIDRA_FIELD(BG_Weapons, 51140, 4) == 0) {
        tmp_i7 = GHIDRA_FIELD(ammoTableMP, 2128, 4);
      }
      if (GHIDRA_FIELD(BG_Weapons, 51144, 4) == 0) {
        tmp_l9 = (long double)G_GetWeaponSpread_part_6();
      }
      else {
        tmp_l9 = (long double)(int)GHIDRA_FIELD(BG_Weapons, 51144, 4);
      }
      tmp_u8 = 0;
    }
    else {
      if (GHIDRA_FIELD(BG_Weapons, 51140, 4) == 0) {
        tmp_i7 = GHIDRA_FIELD(ammoTableMP, 2128, 4);
      }
      if (GHIDRA_FIELD(BG_Weapons, 51144, 4) == 0) {
        tmp_l9 = (long double)G_GetWeaponSpread_part_6();
      }
      else {
        tmp_l9 = (long double)(int)GHIDRA_FIELD(BG_Weapons, 51144, 4);
      }
      tmp_u8 = 0;
      tmp_l9 = tmp_l9 * (long double)0.6;
    }
    goto LAB_0010ca90;
  case 0x24:
  case 0x25:
    tmp_l9 = (long double)BG_GetFromTable(&chargeCost_Riflenade,tmp_i6 + 0xed0,1);
    jP_DoChargeCost(param_1,(float)tmp_l9);
    tmp_u8 = weapon_gpg40_fire(param_1,*(uint32_t *)(param_1 + 0xe8));
    local_34 = 1;
    tmp_i10 = *(int *)(param_1 + 0xe8);
    break;
  case 0x2a:
    tmp_l9 = (long double)BG_GetFromTable(&chargeCost_Mortar,tmp_i6 + 0xed0,5);
    jP_DoChargeCost(param_1,(float)tmp_l9);
    tmp_u8 = weapon_mortar_fire(param_1,*(uint32_t *)(param_1 + 0xe8));
    local_34 = 1;
    tmp_i10 = *(int *)(param_1 + 0xe8);
    break;
  case 0x2b:
    tmp_u8 = 0;
    tmp_l9 = (long double)BG_GetFromTable(&chargeCost_Adrenaline,tmp_i6 + 0xed0,2);
    jP_DoChargeCost(param_1,(float)tmp_l9);
    local_34 = 1;
    *(int *)(*(int *)(param_1 + 400) + 0x17c) = g_unk_00abe908 + 10000;
    tmp_i10 = *(int *)(param_1 + 0xe8);
    break;
  case 0x2e:
    tmp_i7 = GHIDRA_FIELD(BG_Weapons, 80244, 4);
    if (GHIDRA_FIELD(BG_Weapons, 80244, 4) == 0) {
      tmp_i7 = GHIDRA_FIELD(ammoTableMP, 3352, 4);
    }
    if (GHIDRA_FIELD(BG_Weapons, 80248, 4) == 0) {
      tmp_l9 = (long double)G_GetWeaponSpread_part_6();
    }
    else {
      tmp_l9 = (long double)(int)GHIDRA_FIELD(BG_Weapons, 80248, 4);
    }
    tmp_u8 = 0;
    tmp_l9 = tmp_l9 * (long double)0.05;
LAB_0010ca90:
    Bullet_Fire(param_1,(float)(tmp_l9 * (long double)tmp_f2),tmp_i7,tmp_u8);
LAB_0010ca9e:
    tmp_i10 = *(int *)(param_1 + 0xe8);
    tmp_u8 = 0;
    local_34 = 1;
    break;
  case 0x2f:
    tmp_i6 = Weapon_Poison(param_1);
    if (tmp_i6 == 0) {
      tmp_u8 = 0x2f;
      goto LAB_0010cdac;
    }
    if (GHIDRA_FIELD(g_gamestate, 12, 4) != 0) goto LAB_0010ca9e;
    tmp_u8 = 0;
    local_34 = 1;
    tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0xe5c);
    *tmp_pi1 = *tmp_pi1 + 1;
    tmp_i10 = *(int *)(param_1 + 0xe8);
    break;
  case 0x31:
    tmp_u8 = 0;
    nitrox_tripmine(param_1);
    tmp_i10 = *(int *)(param_1 + 0xe8);
    local_34 = 1;
  }
  tmp_u5 = Bot_WeaponGameToBot(tmp_i10);
  Bot_Event_FireWeapon((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u5,tmp_u8);
LAB_0010c708:
  if ((tmp_u3 < 0x1a) && (GHIDRA_FIELD(g_gamestate, 12, 4) == 0)) {
    tmp_pi1 = (int *)(tmp_u3 * 0x14 + *(int *)(param_1 + 400) + 0xcac);
    *tmp_pi1 = *tmp_pi1 + local_34;
  }
  return;
}

int nitmod_CountTeamTripmines(int param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  
  if (TripmineEntities < 1) {
    tmp_i1 = 0;
  }
  else {
    tmp_pi2 = &g_unk_0087da24;
    tmp_i1 = 0;
    do {
      if (*(int *)(*tmp_pi2 + 0x108) == param_1) {
        tmp_i1 = tmp_i1 + 1;
      }
      tmp_pi2 = tmp_pi2 + 1;
    } while (tmp_pi2 != &g_unk_0087da24 + TripmineEntities);
  }
  return tmp_i1;
}

void nitmod_PoisonGasThink(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 800;
  if (0x18 < *(int *)(param_1 + 0x10c)) {
    tmp_i2 = *(int *)(param_1 + 0xe8);
    tmp_u1 = *(uint32_t *)(param_1 + 0x2dc);
    tmp_i3 = *(int *)(BG_Weapons + tmp_i2 * 0x6b0 + 0x694);
    if (tmp_i3 == 0) {
      tmp_i3 = *(int *)(ammoTableMP + tmp_i2 * 0x48 + 0x30);
    }
    tmp_i2 = G_GetWeaponDamage(tmp_i2);
    G_RadiusDamage(param_1 + 0x5c,param_1,*(uint32_t *)(param_1 + 0x218),(float)tmp_i2,(float)tmp_i3
                   ,param_1,tmp_u1);
    *(uint32_t *)(param_1 + 0x110) = 0;
  }
  return;
}

uint32_t nitmod_AddNewWeapon(uint32_t param_1,int param_2)
{
  byte tmp_b1;
  
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 8) {
    if (param_2 == 0x32) {
      tmp_b1 = g_DMOptions[0xd] & 4;
    }
    else if (param_2 == 0x33) {
      tmp_b1 = g_DMOptions[0xd] & 2;
    }
    else {
      if (param_2 != 0x31) {
        return 0;
      }
      tmp_b1 = g_DMOptions[0xd] & 8;
    }
  }
  else if (param_2 == 0x32) {
    tmp_b1 = g_weapons[0xd] & 0x20;
  }
  else if (param_2 == 0x33) {
    tmp_b1 = g_weapons[0xd] & 0x40;
  }
  else {
    if (param_2 != 0x31) {
      return 0;
    }
    tmp_b1 = g_weapons[0xd] & 0x80;
  }
  if (tmp_b1 == 0) {
    return 0;
  }
  AddWeaponToPlayer(param_1,param_2,*(uint32_t *)(ammoTableMP + param_2 * 0x48 + 0xc),
                    *(uint32_t *)(ammoTableMP + param_2 * 0x48 + 0x10),0);
  return 1;
}

void nitrox_RemoveTripmines(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i2 = TripmineEntities + -1;
  if (-1 < tmp_i2) {
    do {
      while (tmp_i1 = (&g_unk_0087da24)[tmp_i2], *(int *)(tmp_i1 + 0x218) != param_1) {
        tmp_i2 = tmp_i2 + -1;
        if (tmp_i2 == -1) {
          return;
        }
      }
      *(uint32_t *)(tmp_i1 + 0x218) = 0;
      tmp_i2 = tmp_i2 + -1;
      *(uint32_t *)(tmp_i1 + 0x180) = 0x3ff;
      G_FreeEntity(tmp_i1);
    } while (tmp_i2 != -1);
  }
  return;
}

int nitrox_GetWeaponSplashDamage(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(BG_Weapons + param_1 * 0x6b0 + 0x690);
  if (tmp_i1 == 0) {
    tmp_i1 = *(int *)(ammoTableMP + param_1 * 0x48 + 0x2c);
  }
  return tmp_i1;
}

int nitrox_GetWeaponSplashDamageRadius(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(BG_Weapons + param_1 * 0x6b0 + 0x694);
  if (tmp_i1 == 0) {
    tmp_i1 = *(int *)(ammoTableMP + param_1 * 0x48 + 0x30);
  }
  return tmp_i1;
}

