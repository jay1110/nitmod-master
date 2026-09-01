/* Entity events and event-driven effects — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_events.h"

void CG_EntityEvent(int *param_1,uint32_t *param_2)
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
  float tmp_f11;
  float tmp_f12;
  float tmp_f13;
  float tmp_f14;
  float tmp_f15;
  float tmp_f16;
  float tmp_f17;
  float tmp_f18;
  char tmp_c19;
  long double tmp_l20;
  uint tmp_u21;
  uint32_t tmp_u22;
  int tmp_i23;
  uint tmp_u24;
  int tmp_i25;
  uint tmp_u26;
  uint32_t tmp_u27;
  int tmp_i28;
  int tmp_i29;
  uint32_t tmp_u30;
  float *pfVar31;
  float *pfVar32;
  int tmp_i33;
  char *tmp_pc34;
  char *tmp_pc35;
  uint8_t *tmp_pu36;
  uint tmp_u37;
  uint *tmp_pu38;
  uint *tmp_pu39;
  uint16_t *tmp_pu40;
  float *pfVar41;
  uint tmp_u42;
  int tmp_i43;
  uint32_t *tmp_pu44;
  byte tmp_b45;
  long double tmp_l46;
  uint32_t *local_19c;
  uint32_t local_18c;
  int local_184;
  int local_180;
  uint32_t *local_17c;
  uint32_t *local_178;
  uint32_t local_158;
  uint32_t local_154;
  uint8_t local_150 [4];
  uint32_t local_14c;
  float local_148 [9];
  float local_124;
  uint8_t local_120 [4];
  uint32_t local_11c;
  float local_118 [9];
  float local_f4;
  float local_f0;
  
  tmp_b45 = 0;
  tmp_u37 = param_1[0x2e] & 0xfffffcff;
  if (GHIDRA_FIELD(cg_debugEvents, 12, 4) == 0) {
LAB_00071dee:
    if (tmp_u37 == 0) {
      return;
    }
    tmp_u42 = param_1[0x2b];
    if (0x3f < tmp_u42) {
      tmp_u42 = 0;
    }
LAB_00071e29:
    tmp_i23 = tmp_u42 * 0x1a4 + 0x10f926c;
    CG_PlayerClassForClientinfo(tmp_i23,param_1);
    tmp_i23 = CG_CharacterForClientinfo(tmp_i23,param_1);
    tmp_u22 = GHIDRA_FIELD(cg_obituary, 12, 4);
    tmp_u30 = GHIDRA_FIELD(cgs, 131780, 4);
    tmp_u21 = g_unk_01090b7c;
    tmp_u24 = splashfootstepcnt_12305;
    tmp_u26 = footstepcnt_12304;
    switch(tmp_u37) {
    default:
      CG_Error("Unknown event: %i",tmp_u37);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 1:
      if (param_1[0x2f] != 9) {
        if (param_1[0x2f] == 0) {
          if (GHIDRA_FIELD(cg_footsteps, 12, 4) != 0) {
            CG_StartFootStepSound_isra_0_part_1();
            tmp_u24 = splashfootstepcnt_12305;
            tmp_u26 = footstepcnt_12304;
          }
        }
        else if (GHIDRA_FIELD(cg_footsteps, 12, 4) != 0) {
          CG_StartFootStepSound_isra_0_part_1();
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      break;
    case 9:
      if (GHIDRA_FIELD(cg_footsteps, 12, 4) != 0) {
        CG_StartFootStepSound_isra_0_part_1();
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 10:
      if (GHIDRA_FIELD(cg_footsteps, 12, 4) != 0) {
        CG_StartFootStepSound_isra_0_part_1();
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0xb:
      if ((((g_unk_0109079c == tmp_u42) && (g_unk_01047aec == 0)) &&
          ((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) == 0)) && (GHIDRA_FIELD(cg_nopredict, 12, 4) == 0)) {
        if (g_unk_010906e0 - g_unk_010917fc < 200) {
          tmp_f1 = ((float)(200 - (g_unk_010906e0 - g_unk_010917fc)) * g_unk_010917f8) / 200.0;
        }
        else {
          tmp_f1 = 0.0;
        }
        g_unk_010917f8 = (float)param_1[0x2f] + tmp_f1;
        g_unk_010917fc = g_unk_010906e0;
        if (32.0 < (float)param_1[0x2f] + tmp_f1) {
          g_unk_010917f8 = 32.0;
        }
      }
      break;
    case 0xc:
      tmp_i33 = param_1[0x2f];
      if (tmp_i33 != 9) {
        if (tmp_i33 == 0) {
          tmp_u30 = *(uint32_t *)(cgs + *(int *)(*(int *)(tmp_i23 + 0x7f0) + 0x84) * 4 + 0x10f28);
        }
        else {
          tmp_u30 = *(uint32_t *)(cgs + tmp_i33 * 4 + 0x10f28);
        }
        trap_S_StartSound(0,*param_1,0,tmp_u30);
      }
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (g_unk_0109079c == tmp_u42) {
        g_unk_0109180c = 0xc1000000;
        g_unk_01091810 = g_unk_010906e0;
      }
      break;
    case 0xd:
      tmp_i33 = param_1[0x2f];
      if (tmp_i33 != 9) {
        if (tmp_i33 == 0) {
          tmp_u30 = *(uint32_t *)(cgs + *(int *)(*(int *)(tmp_i23 + 0x7f0) + 0x84) * 4 + 0x10f28);
        }
        else {
          tmp_u30 = *(uint32_t *)(cgs + tmp_i33 * 4 + 0x10f28);
        }
        trap_S_StartSound(0,*param_1,0,tmp_u30);
      }
      trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 33787800, 4));
      tmp_u26 = footstepcnt_12304;
      tmp_u24 = splashfootstepcnt_12305;
      param_1[0x118] = g_unk_010906e0;
      break;
    case 0xe:
      tmp_i33 = param_1[0x2f];
      if (tmp_i33 != 9) {
        if (tmp_i33 == 0) {
          tmp_u30 = *(uint32_t *)(cgs + *(int *)(*(int *)(tmp_i23 + 0x7f0) + 0x84) * 4 + 0x10f28);
        }
        else {
          tmp_u30 = *(uint32_t *)(cgs + tmp_i33 * 4 + 0x10f28);
        }
        trap_S_StartSound(0,*param_1,0,tmp_u30);
      }
      trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 33787800, 4));
      param_1[0x118] = g_unk_010906e0;
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (g_unk_0109079c == tmp_u42) {
        g_unk_0109180c = 0xc1800000;
        g_unk_01091810 = g_unk_010906e0;
      }
      break;
    case 0xf:
      tmp_i33 = param_1[0x2f];
      if (tmp_i33 != 9) {
        if (tmp_i33 == 0) {
          tmp_u30 = *(uint32_t *)(cgs + *(int *)(*(int *)(tmp_i23 + 0x7f0) + 0x84) * 4 + 0x10f28);
        }
        else {
          tmp_u30 = *(uint32_t *)(cgs + tmp_i33 * 4 + 0x10f28);
        }
        trap_S_StartSound(0,*param_1,0,tmp_u30);
      }
      trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 33787800, 4));
      param_1[0x118] = g_unk_010906e0;
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (g_unk_0109079c == tmp_u42) {
        g_unk_0109180c = 0xc1800000;
        g_unk_01091810 = g_unk_010906e0;
      }
      break;
    case 0x10:
      tmp_i33 = param_1[0x2f];
      if (tmp_i33 != 9) {
        if (tmp_i33 == 0) {
          tmp_u30 = *(uint32_t *)(cgs + *(int *)(*(int *)(tmp_i23 + 0x7f0) + 0x84) * 4 + 0x10f28);
        }
        else {
          tmp_u30 = *(uint32_t *)(cgs + tmp_i33 * 4 + 0x10f28);
        }
        trap_S_StartSound(0,*param_1,0,tmp_u30);
      }
      trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 33787800, 4));
      param_1[0x118] = g_unk_010906e0;
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (g_unk_0109079c == tmp_u42) {
        g_unk_0109180c = 0xc1c00000;
        g_unk_01091810 = g_unk_010906e0;
      }
      break;
    case 0x11:
      tmp_i33 = param_1[0x2f];
      if (tmp_i33 != 9) {
        if (tmp_i33 == 0) {
          tmp_u30 = *(uint32_t *)(cgs + *(int *)(*(int *)(tmp_i23 + 0x7f0) + 0x84) * 4 + 0x10f28);
        }
        else {
          tmp_u30 = *(uint32_t *)(cgs + tmp_i33 * 4 + 0x10f28);
        }
        trap_S_StartSound(0,*param_1,0,tmp_u30);
      }
      trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 33787800, 4));
      param_1[0x118] = g_unk_010906e0;
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (g_unk_0109079c == tmp_u42) {
        g_unk_01091810 = g_unk_010906e0;
        g_unk_0109180c = 0xc1c00000;
      }
      break;
    case 0x12:
      trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 69476, 4));
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x13:
      trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 69480, 4));
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x14:
      if (param_1[0x2f] != 0) {
        trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 69484, 4));
      }
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (g_unk_01047ac4 == *param_1) {
        if ((cgs[*(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x958c] & 0x20) == 0) {
          g_unk_010b5e40 = g_unk_010906e0 + 12000;
        }
        else {
          g_unk_010b5e40 = g_unk_010906e0 + 15000;
        }
      }
      break;
    case 0x15:
      trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 69480, 4));
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (param_1[0x2f] != 0) {
        trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 69488, 4));
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x16:
    case 0x17:
      tmp_i23 = param_1[0x2f];
      if ((0 < tmp_i23) && (tmp_i23 < bg_numItems)) {
        if (tmp_u37 == 0x16) {
          tmp_u30 = GHIDRA_FIELD(cgs, 132360, 4);
          if (*(int *)(bg_itemlist + tmp_i23 * 0x38 + 0x24) != 5) {
            tmp_u30 = *(uint32_t *)(cgs + tmp_i23 * 4 + 0x203ac);
          }
          trap_S_StartSound(0,*param_1,0,tmp_u30);
        }
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
        if (*param_1 == *(int *)(g_unk_01047b00 + 0xcc)) {
          CG_ItemPickup();
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      break;
    case 0x18:
      tmp_i23 = param_1[0x2f];
      if ((0 < tmp_i23) && (tmp_i23 < bg_numItems)) {
        if (**(char **)(bg_itemlist + tmp_i23 * 0x38 + 4) != '\0') {
          trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),0,
                            *(uint32_t *)(cgs + tmp_i23 * 4 + 0x203ac));
        }
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
        if (*param_1 == *(int *)(g_unk_01047b00 + 0xcc)) {
          CG_ItemPickup();
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      break;
    case 0x19:
    case 0x1a:
      tmp_u42 = param_1[0x3a];
      if ((((tmp_u42 & 0xfffffff7) != 4 && (tmp_u42 != 0x12 && (tmp_u42 != 0xf && tmp_u42 != 9))) &&
           3 < tmp_u42 - 0x19) && (3 < tmp_u42 - 0x30)) {
        trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 69412, 4));
      }
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if ((*param_1 == *(int *)(g_unk_01047b00 + 0xcc)) &&
         ((((0 < (int)GHIDRA_FIELD(cg_noAmmoAutoSwitch, 12, 4) &&
            (tmp_i23 = CG_WeaponSelectable(g_unk_01091814), tmp_i23 == 0)) ||
           (tmp_u42 = param_1[0x3a],
           (((((tmp_u42 == 0x2a || tmp_u42 == 9) || tmp_u42 == 0xf) || tmp_u42 == 0x15) ||
            tmp_u42 == 0x12) || tmp_u42 - 0x19 < 4) || tmp_u42 - 0x30 < 4)) ||
          (tmp_u24 = splashfootstepcnt_12305, tmp_u26 = footstepcnt_12304,
          (tmp_u42 & 0xfffffff7) - 4 < 2)))) {
        CG_OutOfAmmoChange(tmp_u37 != 0x1a);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x1b:
    case 0x1d:
      break;
    case 0x1c:
      if ((cgs[*param_1 * 0x1a4 + 0x959c] & 4) == 0) {
        tmp_i23 = param_1[0x3a];
      }
      else {
        tmp_i33 = BG_isLightWeaponSupportingFastReload(param_1[0x3a]);
        tmp_i23 = param_1[0x3a];
        if ((tmp_i33 != 0) && (*(int *)(cg_weapons + tmp_i23 * 0x17ac + 0x1760) != 0)) {
          trap_S_StartSound(0,*param_1,2,*(int *)(cg_weapons + tmp_i23 * 0x17ac + 0x1760));
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
          break;
        }
      }
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (*(int *)(cg_weapons + tmp_i23 * 0x17ac + 0x175c) != 0) {
        trap_S_StartSound(0,*param_1,2,*(int *)(cg_weapons + tmp_i23 * 0x17ac + 0x175c));
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x1e:
      if (*param_1 == *(int *)(g_unk_01047b00 + 0xcc)) {
        tmp_u37 = PM_IdleAnimForWeapon(*(uint32_t *)(g_unk_01047b00 + 0xd0));
        g_unk_01090b7c = ~tmp_u21 & 0x200 | tmp_u37;
        param_1[0x93] = g_unk_010906e0;
      }
      if ((param_1[2] & 0x8020U) == 0) {
        if ((param_1[2] & 0x8000U) == 0) {
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
          if (*(int *)(cg_weapons + param_1[0x3a] * 0x17ac + 0x1758) != 0) {
            trap_S_StartSound(0,*param_1,0,*(int *)(cg_weapons + param_1[0x3a] * 0x17ac + 0x1758));
            tmp_u24 = splashfootstepcnt_12305;
            tmp_u26 = footstepcnt_12304;
          }
        }
        else {
          tmp_i23 = *param_1;
          if ((cg_entities
               [*(int *)(cg_entities +
                        *(int *)(cg_entities + tmp_i23 * 0xaf8 + 0xab4) * 0xaf8 + 0x9bc) * 0xaf8 +
                0xf4] & 8) == 0) {
            trap_S_StartSoundVControl(0,tmp_i23,0,GHIDRA_FIELD(cgs, 69820, 4),0xff);
            tmp_u24 = splashfootstepcnt_12305;
            tmp_u26 = footstepcnt_12304;
          }
          else {
            trap_S_StartSoundVControl(0,tmp_i23,0,GHIDRA_FIELD(cgs, 69832, 4),0xff);
            tmp_u24 = splashfootstepcnt_12305;
            tmp_u26 = footstepcnt_12304;
          }
        }
      }
      else {
        trap_S_StartSoundVControl(0,*param_1,0,GHIDRA_FIELD(cgs, 69820, 4),0xff);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x1f:
      trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 68952, 4));
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x20:
      trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 68952, 4));
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (*param_1 == *(int *)(g_unk_01047b00 + 0xcc)) {
        tmp_u37 = param_1[0x3a] - 0x27;
        if ((tmp_u37 < 3) && (*(int *)(CSWTCH_55 + tmp_u37 * 4) != 0)) {
          CG_FinishWeaponChange(param_1[0x3a],*(int *)(CSWTCH_55 + tmp_u37 * 4));
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      break;
    case 0x21:
    case 0x22:
      if (param_1[0x2b] == *(int *)(g_unk_01047b00 + 0xcc)) {
        if ((*(uint *)(g_unk_01047b00 + 0x94) & 0x40000) != 0) break;
        if ((param_1[0x3a] == 1) && (g_unk_010ee05c = g_unk_010ee05c + -10, g_unk_010ee05c < 0)) {
          g_unk_010ee05c = 0;
        }
      }
      CG_FireWeapon(param_1,tmp_u37);
      tmp_u26 = footstepcnt_12304;
      tmp_u24 = splashfootstepcnt_12305;
      if (tmp_u37 == 0x22) {
        param_1[0x2ac] = 1;
        tmp_u24 = splashfootstepcnt_12305;
      }
      else {
        param_1[0x2ac] = 0;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x23:
      CG_FireWeapon(param_1,0x23);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x24:
      if (GHIDRA_FIELD(cgs, 68948, 4) != 0) {
        trap_S_StartSound(0,*param_1,2,GHIDRA_FIELD(cgs, 68948, 4));
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x25:
    case 0x26:
      local_14c = (float)param_1[6];
      local_148[0] = (float)param_1[7];
      local_148[1] = (float)param_1[8];
      local_11c = local_14c - *(float *)(g_unk_010afbcc + 0x18);
      local_118[0] = (float)param_1[7] - *(float *)(g_unk_010afbcc + 0x1c);
      local_118[1] = local_148[1] - *(float *)(g_unk_010afbcc + 0x20);
      tmp_l46 = (long double)VectorNormalize(&local_11c);
      if (((long double)512.0 < tmp_l46) && (tmp_l46 < (long double)4096.0)) {
        local_14c = local_11c * 64.0 + *(float *)(g_unk_010afbcc + 0x18);
        local_148[0] = local_118[0] * 64.0 + *(float *)(g_unk_010afbcc + 0x1c);
        local_148[1] = local_118[1] * 64.0 + *(float *)(g_unk_010afbcc + 0x20);
        tmp_u30 = GHIDRA_FIELD(cgs, 69816, 4);
        if ((cg_entities
             [*(int *)(cg_entities +
                      *(int *)(cg_entities + *param_1 * 0xaf8 + 0xab4) * 0xaf8 + 0x9bc) * 0xaf8 +
              0xf4] & 8) != 0) {
          tmp_u30 = GHIDRA_FIELD(cgs, 69828, 4);
        }
        trap_S_StartSoundEx(&local_14c,*param_1,2,tmp_u30,0x10);
      }
      CG_FireWeapon(param_1,tmp_u37);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x27:
      tmp_i23 = param_1[0x3a];
      if (tmp_i23 == 0x1a) {
        trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 69620, 4));
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      else if (tmp_i23 == 0xf) {
        trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 69612, 4));
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      else if ((tmp_i23 == 0x33) || (tmp_i23 == 0x19)) {
        trap_S_StartSound(0,*param_1,0,GHIDRA_FIELD(cgs, 69616, 4));
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      else if (param_1[0x2f] != 9) {
        tmp_u37 = rand();
        if ((tmp_u37 & 1) == 0) {
          trap_S_StartSound(0,*param_1,0,*(uint32_t *)(cgs + param_1[0x2f] * 8 + 0x10fa8));
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
        else {
          trap_S_StartSound(0,*param_1,0,*(uint32_t *)(cgs + param_1[0x2f] * 8 + 0x10fa4));
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      break;
    case 0x28:
      tmp_i23 = param_1[0x2f];
      if (tmp_i23 < 0x54) {
        tmp_i33 = *(int *)(cgs + tmp_i23 * 4 + 0x2038f84);
      }
      else {
        tmp_i33 = *(int *)(cgs + tmp_i23 * 4 + 0x7eb8);
      }
      if (tmp_i33 == 0) {
        tmp_pc34 = (char *)nitrox_ConfigString(tmp_i23 + 0xac);
        tmp_pc35 = strstr(tmp_pc34,"d!");
        if (tmp_pc35 == (char *)0x0) {
          tmp_i23 = CG_SoundPlaySoundScript(tmp_pc34,0,*param_1,0);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
          if ((tmp_i23 == 0) &&
             (tmp_i23 = trap_S_RegisterSound(tmp_pc34,0), tmp_u24 = splashfootstepcnt_12305,
             tmp_u26 = footstepcnt_12304, tmp_i23 != 0)) {
            trap_S_StartSoundVControl(0,*param_1,3,tmp_i23,0xff);
            tmp_u24 = splashfootstepcnt_12305;
            tmp_u26 = footstepcnt_12304;
          }
        }
        else {
          Q_strncpyz(&local_11c,tmp_pc34,0x100);
          Nit_RemoveWordInString(&local_11c,"d!");
          tmp_u30 = va("sound/movers/doors/door%s.wav",&local_11c);
          tmp_u30 = trap_S_RegisterSound(tmp_u30,0);
          trap_S_StartSoundVControl(0,*param_1,3,tmp_u30,0xff);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      else {
        trap_S_StartSoundVControl(0,*param_1,3,tmp_i33,0xff);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x29:
      tmp_i23 = param_1[0x2f];
      tmp_i33 = param_1[0x3f];
      if (tmp_i23 < 0x54) {
        tmp_i25 = *(int *)(cgs + tmp_i23 * 4 + 0x2038f84);
      }
      else {
        tmp_i25 = *(int *)(cgs + tmp_i23 * 4 + 0x7eb8);
      }
      if (tmp_i25 == 0) {
        tmp_i23 = nitrox_ConfigString(tmp_i23 + 0xac);
        tmp_i25 = CG_SoundPlaySoundScript(tmp_i23,0,*param_1,0);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
        if (((tmp_i25 == 0) && (tmp_i23 != 0)) &&
           (tmp_i23 = trap_S_RegisterSound(tmp_i23,0), tmp_u24 = splashfootstepcnt_12305,
           tmp_u26 = footstepcnt_12304, tmp_i23 != 0)) {
          trap_S_StartSoundVControl(0,*param_1,3,tmp_i23,tmp_i33);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      else {
        trap_S_StartSoundVControl(0,*param_1,3,tmp_i25,tmp_i33);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x2b:
      if (*(int *)(g_unk_01047b00 + 0xcc) == param_1[0x42]) {
        tmp_i23 = param_1[0x2f];
        if (tmp_i23 < 0x54) {
          tmp_i33 = *(int *)(cgs + tmp_i23 * 4 + 0x2038f84);
        }
        else {
          tmp_i33 = *(int *)(cgs + tmp_i23 * 4 + 0x7eb8);
        }
        if (tmp_i33 == 0) {
          tmp_i23 = nitrox_ConfigString(tmp_i23 + 0xac);
          tmp_i33 = CG_SoundPlaySoundScript(tmp_i23,0,0xffffffff,param_1[0x43] == 0);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
          if (tmp_i33 == 0) {
            tmp_u30 = 0;
            if (tmp_i23 != 0) {
              tmp_u30 = trap_S_RegisterSound(tmp_i23,0);
            }
            trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),0,tmp_u30);
            tmp_u24 = splashfootstepcnt_12305;
            tmp_u26 = footstepcnt_12304;
          }
        }
        else {
          trap_S_StartSound(0,*(int *)(g_unk_01047b00 + 0xcc),0,tmp_i33);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      break;
    case 0x2c:
      if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) != param_1[0x42]) break;
    case 0x2a:
      tmp_i23 = param_1[0x2f];
      if (tmp_i23 < 0x54) {
        tmp_i33 = *(int *)(cgs + tmp_i23 * 4 + 0x2038f84);
      }
      else {
        tmp_i33 = *(int *)(cgs + tmp_i23 * 4 + 0x7eb8);
      }
      if (tmp_i33 == 0) {
        tmp_i23 = nitrox_ConfigString(tmp_i23 + 0xac);
        tmp_i33 = CG_SoundPlaySoundScript(tmp_i23,0,0xffffffff,1);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
        if (((tmp_i33 == 0) && (tmp_i23 != 0)) &&
           (tmp_i23 = trap_S_RegisterSound(tmp_i23,0), tmp_u24 = splashfootstepcnt_12305,
           tmp_u26 = footstepcnt_12304, tmp_i23 != 0)) {
          trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),0,tmp_i23);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      else {
        trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),0,tmp_i33);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x2d:
      tmp_u37 = rand();
      tmp_i23 = (int)ROUND((float)(int)(&fxSounds)[param_1[0x2f] * 7] *
                          ((float)(tmp_u37 & 0x7fff) / 32767.0));
      tmp_i25 = param_1[0x2f] * 7 + tmp_i23;
      tmp_i33 = (&g_unk_00144884)[tmp_i25];
      if (tmp_i33 == -1) {
        tmp_u30 = trap_S_RegisterSound((&fxSounds)[tmp_i25 + 4],0);
        (&g_unk_00144884)[tmp_i25] = tmp_u30;
        tmp_i33 = (&g_unk_00144884)[tmp_i23 + param_1[0x2f] * 7];
      }
      trap_S_StartSoundVControl(0,*param_1,3,tmp_i33,0xff);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x2e:
      CG_Bullet(param_1 + 6,param_1[0x23],&local_158,1,param_1[0x2f],param_1[0x24],0,0);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x2f:
      ByteToDir(param_1[0x2f],&local_158);
      CG_Bullet(param_1 + 6,param_1[0x23],&local_158,0,0x3fe,param_1[0x24],param_1[0x1a],0);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x30:
      ByteToDir(param_1[0x2f],&local_158);
      CG_MissileHitPlayer(param_1,param_1[0x3a],param_2,&local_158,param_1[0x23]);
      tmp_i23 = param_1[0x3a];
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (tmp_i23 == 1) {
        if (param_1[0x2b] != *(int *)(g_unk_01047b00 + 0xcc)) break;
        g_unk_010ee05c = g_unk_010ee05c + 0x2d;
        if (0xff < g_unk_010ee05c) {
          g_unk_010ee05c = 0xff;
        }
        tmp_i23 = param_1[0x3a];
      }
      if (tmp_i23 == 0x2a) {
        if (param_1[0x3b] == 0) {
          CG_MortarImpact(param_1,param_2,3,1);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
        else {
          CG_MortarImpact_part_2();
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      break;
    case 0x31:
      ByteToDir(param_1[0x2f],&local_158);
      CG_MissileHitWall(param_1[0x3a],0,param_2,&local_158,0);
      tmp_i23 = param_1[0x3a];
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (tmp_i23 == 1) {
        if (param_1[0x2b] != *(int *)(g_unk_01047b00 + 0xcc)) break;
        g_unk_010ee05c = g_unk_010ee05c + -10;
        if (g_unk_010ee05c < 0) {
          g_unk_010ee05c = 0;
        }
        tmp_i23 = param_1[0x3a];
      }
      if (tmp_i23 == 0x2a) {
        if (param_1[0x3b] == 0) {
          CG_MortarImpact(param_1,param_2,3,1);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
        else {
          CG_MortarImpact_part_2();
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      break;
    case 0x32:
      goto _L461;
    case 0x33:
      ByteToDir(param_1[0x2f],&local_158);
      CG_LoseACC(param_1,&local_158,6,"tag_mouth",1);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
      tmp_i23 = param_1[0x3a];
      tmp_i33 = tmp_i23 * 0x17ac;
      *(int *)(cg_entities + param_1[0x24] * 0xaf8 + 0x774) = g_unk_010906e0;
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (*(int *)(cg_weapons + tmp_i33 + 0x16e8) != 0) {
        tmp_i23 = tmp_i23 * 0x5eb;
        if (((*(int *)(cg_weapons +
                      ((int)(tmp_u37 - 0x34) % *(int *)(cg_weapons + tmp_i33 + 0x1708) + 0x5b8 +
                      tmp_i23) * 4 + 8) != 0) &&
            (trap_S_StartSound(0,*param_1,2,
                               *(int *)(cg_weapons +
                                       ((int)(tmp_u37 - 0x34) %
                                        *(int *)(cg_weapons + tmp_i33 + 0x1708) + 0x5b8 + tmp_i23) * 4
                                       + 8)), tmp_u24 = splashfootstepcnt_12305,
            tmp_u26 = footstepcnt_12304, *(int *)(cg_weapons + tmp_i33 + 0x16f8) != 0)) &&
           (tmp_i23 = tmp_i23 + 0x5bc + (int)(tmp_u37 - 0x34) % *(int *)(cg_weapons + tmp_i33 + 0x170c),
           *(int *)(cg_weapons + tmp_i23 * 4 + 8) != 0)) {
          local_14c = (float)param_1[6];
          local_148[0] = (float)param_1[7];
          local_148[1] = (float)param_1[8];
          local_11c = local_14c - *(float *)(g_unk_010afbcc + 0x18);
          local_118[0] = local_148[0] - *(float *)(g_unk_010afbcc + 0x1c);
          local_118[1] = local_148[1] - *(float *)(g_unk_010afbcc + 0x20);
          tmp_l46 = (long double)VectorNormalize(&local_11c);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
          if (((long double)512.0 < tmp_l46) && (tmp_l46 < (long double)4096.0)) {
            local_14c = local_11c * 64.0 + *(float *)(g_unk_010afbcc + 0x18);
            local_148[0] = local_118[0] * 64.0 + *(float *)(g_unk_010afbcc + 0x1c);
            local_148[1] = local_118[1] * 64.0 + *(float *)(g_unk_010afbcc + 0x20);
            trap_S_StartSoundEx(&local_14c,*param_1,2,*(uint32_t *)(cg_weapons + tmp_i23 * 4 + 8),
                                0x10);
            tmp_u24 = splashfootstepcnt_12305;
            tmp_u26 = footstepcnt_12304;
          }
        }
      }
      break;
    case 0x38:
      tmp_i23 = param_1[0x2f];
      tmp_u37 = param_1[0x24];
      local_14c = 4.48416e-44;
      tmp_u42 = param_1[0x23];
      tmp_u24 = 0;
      do {
        *(uint32_t *)((int)local_148 + tmp_u24) = 0;
        *(uint32_t *)((int)local_148 + tmp_u24 + 4) = 0;
        tmp_u24 = tmp_u24 + 8;
      } while (tmp_u24 < 0x20);
      tmp_u24 = 0;
      local_11c = 4.48416e-44;
      do {
        *(uint32_t *)((int)local_118 + tmp_u24) = 0;
        *(uint32_t *)((int)local_118 + tmp_u24 + 4) = 0;
        tmp_u24 = tmp_u24 + 8;
      } while (tmp_u24 < 0x20);
      local_158 = 0x3f800000;
      local_154 = 0x3f800000;
      local_150 = (uint8_t  [4])0x3f800000;
      tmp_i33 = param_1[0x3a];
      tmp_i25 = BG_WeaponForMOD(tmp_i23);
      local_180 = GHIDRA_FIELD(cgs, 131780, 4);
      if (0x3f < tmp_u42) {
        CG_Error("CG_Obituary: target out of range");
      }
      if (tmp_u37 < 0x40) {
        local_184 = tmp_u37 * 0x1a4 + 0x10f926c;
        if (tmp_i25 < 1) {
          Q_strncpyz(&local_14c,tmp_u42 * 0x1a4 + 0x10f9274,0x22);
          tmp_u24 = 0xffffffff;
          tmp_pc34 = (char *)&local_14c;
          do {
            if (tmp_u24 == 0) break;
            tmp_u24 = tmp_u24 - 1;
            tmp_c19 = *tmp_pc34;
            tmp_pc34 = tmp_pc34 + (uint)tmp_b45 * -2 + 1;
          } while (tmp_c19 != '\0');
          local_18c = 1;
          *(uint16_t *)(local_150 + ~tmp_u24 + 3) = 0x375e;
          *(uint8_t *)((int)&local_14c + ~tmp_u24 + 1) = 0;
        }
        else {
          tmp_i28 = *(int *)(cg_weapons + tmp_i25 * 0x17ac + 0x1714);
          if (tmp_i28 != 0) goto LAB_000753b8;
          local_18c = 1;
          Q_strncpyz(&local_14c,tmp_u42 * 0x1a4 + 0x10f9274,0x22);
          tmp_pu39 = &local_14c;
          do {
            tmp_pu38 = tmp_pu39;
            tmp_u26 = *tmp_pu38 + 0xfefefeff & ~*tmp_pu38;
            tmp_u24 = tmp_u26 & 0x80808080;
            tmp_pu39 = tmp_pu38 + 1;
          } while (tmp_u24 == 0);
          if ((tmp_u26 & 0x8080) == 0) {
            tmp_pu39 = (uint *)((int)tmp_pu38 + 6);
            tmp_u24 = tmp_u24 >> 0x10;
          }
          tmp_pu40 = (uint16_t *)((int)tmp_pu39 + (-3 - (uint)CARRY1((byte)tmp_u24,(byte)tmp_u24)));
          *tmp_pu40 = 0x375e;
          *(uint8_t *)(tmp_pu40 + 1) = 0;
        }
LAB_00072529:
        if (tmp_u42 == tmp_u37) {
          switch(tmp_i23) {
          case 0xf:
            goto _L632;
          case 0x10:
          case 0x12:
            goto _L800;
          case 0x11:
            goto _L635;
          case 0x15:
            goto _L636;
          case 0x16:
            goto _L637;
          case 0x19:
            goto _L638;
          case 0x1f:
          case 0x3e:
            goto _L639;
          case 0x20:
            goto _L640;
          case 0x26:
          case 0x27:
            goto _L641;
          case 0x28:
            goto _L642;
          case 0x29:
            goto _L643;
          case 0x2e:
            goto _L644;
          case 0x2f:
            goto _L645;
          case 0x33:
            goto _L646;
          case 0x38:
            goto _L647;
          case 0x39:
            goto _L648;
          case 0x3b:
            goto _L649;
          case 0x3d:
            goto _L650;
          case 0x3f:
            goto _L651;
          case 0x40:
            goto _L652;
          case 0x41:
            goto _L653;
          case 0x42:
            goto _L654;
          case 0x43:
            goto _L655;
          case 0x44:
            goto _L656;
          }
        }
        if ((*(uint *)(g_unk_01047b00 + 0xcc) == tmp_u37) && (tmp_i23 != 0x17)) {
LAB_0007255f:
          local_19c = &local_14c;
          if ((*(int *)(cgs + tmp_u42 * 0x1a4 + 0x9494) == *(int *)(local_184 + 0x88)) &&
             (GHIDRA_FIELD(cgs, 27388, 4) != 8)) {
            tmp_u27 = va("You killed ^1TEAMMATE ^7%s",local_19c);
          }
          else {
            tmp_u27 = va("You killed %s",local_19c);
            if ((cg_HUDFlags[0xc] & 4) != 0) {
              Q_strncpyz(&g_unk_010ef0d8,tmp_u27,0x40);
              nitmod_AddKillPrint();
              goto LAB_000725c7;
            }
          }
          CG_CenterPrint(tmp_u27,0x168,9);
        }
LAB_000725c7:
        local_19c = &local_14c;
        Q_strncpyz(&local_11c,local_184 + 8,0x22);
        tmp_u24 = 0xffffffff;
        tmp_pc34 = (char *)&local_11c;
        do {
          if (tmp_u24 == 0) break;
          tmp_u24 = tmp_u24 - 1;
          tmp_c19 = *tmp_pc34;
          tmp_pc34 = tmp_pc34 + (uint)tmp_b45 * -2 + 1;
        } while (tmp_c19 != '\0');
        *(uint16_t *)(local_120 + ~tmp_u24 + 3) = 0x375e;
        *(uint8_t *)((int)&local_11c + ~tmp_u24 + 1) = 0;
        if (tmp_u42 == *(uint *)(g_unk_01047b00 + 0xcc)) {
          Q_strncpyz(&g_unk_010928bc,&local_11c,0x24);
        }
        local_178 = &local_11c;
        if (tmp_i23 == 0x3a) {
          tmp_u24 = *(uint *)(g_unk_01047b00 + 0xcc);
          if ((tmp_u24 == tmp_u37) || (tmp_u42 == tmp_u24)) {
            trap_S_StartSound(g_unk_01047b00 + 0x40,tmp_u24,0,GHIDRA_FIELD(cgs, 33787796, 4));
          }
        }
        else if (tmp_i23 == 0x3f) {
          if ((*(uint *)(g_unk_01047b00 + 0xcc) == tmp_u37) ||
             (tmp_u42 == *(uint *)(g_unk_01047b00 + 0xcc))) {
            tmp_b45 = cg_goatSound[0xc] & 2;
            goto joined_r0x00075c97;
          }
        }
        else if ((tmp_i23 == 5) &&
                ((*(uint *)(g_unk_01047b00 + 0xcc) == tmp_u37 ||
                 (tmp_u42 == *(uint *)(g_unk_01047b00 + 0xcc))))) {
          tmp_b45 = cg_goatSound[0xc] & 1;
joined_r0x00075c97:
          if (tmp_b45 != 0) {
            trap_S_StartSound(g_unk_01047b00 + 0x40,tmp_u37,2,GHIDRA_FIELD(cgs, 69512, 4));
            trap_S_StartSound(g_unk_01047b00 + 0x40,tmp_u42,2,GHIDRA_FIELD(cgs, 69512, 4));
          }
        }
        local_17c = *(uint32_t **)(Obituaries_killedby + tmp_i23 * 8);
        tmp_i25 = *(int *)(Obituaries_killedby + tmp_i23 * 8 + 4);
        tmp_i28 = tmp_i33 * 0x6b0;
        if (BG_Weapons[tmp_i28 + 0x604] != '\0') {
          local_17c = (uint32_t *)va("%s",tmp_i28 + 0xeb14c4);
        }
        tmp_i33 = tmp_i33 * 0x6b0;
        if (BG_Weapons[tmp_i33 + 0x644] != '\0') {
          tmp_i25 = va("%s",tmp_i33 + 0xeb1504);
        }
        if (local_17c == (uint32_t *)0x0) {
LAB_0007562b:
          local_19c = &local_14c;
          local_178 = &local_11c;
          if (GHIDRA_FIELD(cg_obituary, 12, 4) == 2) {
            tmp_pu36 = &g_unk_0011d841;
          }
          else {
            tmp_pu36 = &g_unk_0011d840;
          }
          tmp_u27 = va("%s ^7died%s",local_19c,tmp_pu36);
          if (tmp_u22 == 2) {
            CG_AddToTeamChat(tmp_u27,param_1[0x2b]);
          }
          else if ((int)tmp_u22 < 3) {
            if (tmp_u22 == 1) {
              CG_AddPMItem(3,tmp_u27,tmp_u30,OB_YELLOW);
              tmp_u24 = splashfootstepcnt_12305;
              tmp_u26 = footstepcnt_12304;
              break;
            }
          }
          else if ((int)tmp_u22 < 5) {
            nitrox_AddGraphicObituary(local_19c,local_180,local_178,OB_YELLOW,local_18c);
          }
          else {
            tmp_u24 = splashfootstepcnt_12305;
            tmp_u26 = footstepcnt_12304;
            if (tmp_u22 == 1) break;
          }
          if (GHIDRA_FIELD(cg_obituary, 12, 4) == 2) {
            tmp_pu36 = &g_unk_0011d840;
          }
          else {
            tmp_pu36 = &g_unk_0011d841;
          }
          tmp_u30 = va("%s%s",tmp_u27,tmp_pu36);
          trap_Print(tmp_u30);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
          break;
        }
        if (tmp_i25 != 0) {
          if ((((tmp_u42 == tmp_u37) ||
               (*(int *)(cgs + tmp_u42 * 0x1a4 + 0x9494) != *(int *)(local_184 + 0x88))) ||
              (GHIDRA_FIELD(cgs, 27388, 4) == 8)) || (tmp_i23 == 0x17)) {
            if (GHIDRA_FIELD(cg_obituary, 12, 4) == 2) {
              tmp_pu36 = &g_unk_0011d841;
            }
            else {
              tmp_pu36 = &g_unk_0011d840;
            }
            tmp_pu44 = local_178;
            tmp_u27 = va("%s %s %s%s%s",local_19c,local_17c,local_178,tmp_i25,tmp_pu36);
            local_17c = tmp_pu44;
          }
          else {
            local_158 = OB_RED;
            local_154 = g_unk_001446a8;
            local_150 = (uint8_t  [4])g_unk_001446ac;
            if (GHIDRA_FIELD(cg_obituary, 12, 4) == 2) {
              tmp_pu36 = &g_unk_0011d841;
            }
            else {
              tmp_pu36 = &g_unk_0011d840;
            }
            tmp_u27 = va("%s%s %s ^7%s%s%s","^1TEAM KILL^7:",local_19c,local_17c,local_178,tmp_i25,
                        tmp_pu36);
            if ((GHIDRA_FIELD(cg_tkSounds, 12, 4) != 0) && (GHIDRA_FIELD(cgs, 27388, 4) != 8)) {
              local_17c = (uint32_t *)GHIDRA_FIELD(cgs, 132364, 4);
              trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),0,GHIDRA_FIELD(cgs, 132364, 4));
            }
          }
          if (tmp_u22 == 2) {
            CG_AddToTeamChat(tmp_u27,param_1[0x2b]);
          }
          else if ((int)tmp_u22 < 3) {
            if (tmp_u22 == 1) {
              if (tmp_i23 == 0x17) {
                tmp_u30 = GHIDRA_FIELD(cgs, 131800, 4);
              }
              CG_AddPMItem(3,tmp_u27,tmp_u30,&local_158);
              goto _L648;
            }
          }
          else if (tmp_u22 == 3) {
            local_17c = &local_158;
            if (tmp_i23 == 0x17) {
              local_17c = (uint32_t *)OB_GREEN;
            }
LAB_00075ec9:
            nitrox_AddGraphicObituary(local_178,local_180,local_19c,local_17c,local_18c);
          }
          else if (tmp_u22 == 4) {
            if (tmp_i23 == 0x17) {
              local_17c = (uint32_t *)OB_GREEN;
              goto LAB_00075ec9;
            }
            local_17c = &local_158;
            nitrox_AddGraphicObituary(local_19c,local_180,local_178,local_17c,local_18c);
          }
          else if (tmp_u22 == 1) goto _L648;
          if (GHIDRA_FIELD(cg_obituary, 12, 4) == 2) {
            tmp_pu36 = &g_unk_0011d840;
          }
          else {
            tmp_pu36 = &g_unk_0011d841;
          }
          goto LAB_00072794;
        }
      }
      else {
        if ((tmp_i25 < 1) || (tmp_i28 = *(int *)(cg_weapons + tmp_i25 * 0x17ac + 0x1714), tmp_i28 == 0))
        {
          tmp_u37 = 0x3fe;
          Q_strncpyz(&local_14c,tmp_u42 * 0x1a4 + 0x10f9274,0x22);
          tmp_u24 = 0xffffffff;
          tmp_pc34 = (char *)&local_14c;
          do {
            if (tmp_u24 == 0) break;
            tmp_u24 = tmp_u24 - 1;
            tmp_c19 = *tmp_pc34;
            tmp_pc34 = tmp_pc34 + (uint)tmp_b45 * -2 + 1;
          } while (tmp_c19 != '\0');
          *(uint16_t *)(local_150 + ~tmp_u24 + 3) = 0x375e;
          *(uint8_t *)((int)&local_14c + ~tmp_u24 + 1) = 0;
          local_18c = 1;
        }
        else {
          tmp_u37 = 0x3fe;
          local_184 = 0;
LAB_000753b8:
          local_18c = weaponIconScale(tmp_i25);
          Q_strncpyz(&local_14c,tmp_u42 * 0x1a4 + 0x10f9274,0x22);
          tmp_pu39 = &local_14c;
          do {
            tmp_pu38 = tmp_pu39;
            tmp_u26 = *tmp_pu38 + 0xfefefeff & ~*tmp_pu38;
            tmp_u24 = tmp_u26 & 0x80808080;
            tmp_pu39 = tmp_pu38 + 1;
          } while (tmp_u24 == 0);
          if ((tmp_u26 & 0x8080) == 0) {
            tmp_pu39 = (uint *)((int)tmp_pu38 + 6);
            tmp_u24 = tmp_u24 >> 0x10;
          }
          tmp_pu40 = (uint16_t *)((int)tmp_pu39 + (-3 - (uint)CARRY1((byte)tmp_u24,(byte)tmp_u24)));
          *tmp_pu40 = 0x375e;
          *(uint8_t *)(tmp_pu40 + 1) = 0;
          local_180 = tmp_i28;
          if (local_184 != 0) goto LAB_00072529;
        }
        if (**(char **)(Obituaries_killedby + tmp_i23 * 8 + 4) != '\0') {
          if (tmp_u42 == tmp_u37) {
            switch(tmp_i23) {
            case 0xf:
              goto _L632;
            case 0x10:
            case 0x12:
              goto _L800;
            case 0x11:
              goto _L635;
            case 0x15:
              goto _L636;
            case 0x16:
              goto _L637;
            case 0x19:
              goto _L638;
            case 0x1f:
            case 0x3e:
              goto _L639;
            case 0x20:
              goto _L640;
            case 0x26:
            case 0x27:
              goto _L641;
            case 0x28:
              goto _L642;
            case 0x29:
              goto _L643;
            case 0x2e:
              goto _L644;
            case 0x2f:
              goto _L645;
            case 0x33:
              goto _L646;
            case 0x38:
              goto _L647;
            case 0x39:
              goto _L648;
            case 0x3b:
              goto _L649;
            case 0x3d:
              goto _L650;
            case 0x3f:
              goto _L651;
            case 0x40:
              goto _L652;
            case 0x41:
              goto _L653;
            case 0x42:
              goto _L654;
            case 0x43:
              goto _L655;
            case 0x44:
              goto _L656;
            }
          }
          tmp_pc34 = "^7died";
          goto LAB_0007466b;
        }
        tmp_pc34 = *(char **)(Obituaries_killedby + tmp_i23 * 8);
        if (tmp_u42 != tmp_u37) {
_L631:
          if (tmp_pc34 != (char *)0x0) goto LAB_0007466b;
          local_184 = 0;
          if ((*(uint *)(g_unk_01047b00 + 0xcc) == tmp_u37) && (tmp_i23 != 0x17)) goto LAB_0007255f;
          tmp_pc34 = "noname";
          tmp_pc35 = (char *)&local_11c;
          for (tmp_i23 = 7; tmp_i23 != 0; tmp_i23 = tmp_i23 + -1) {
            *tmp_pc35 = *tmp_pc34;
            tmp_pc34 = tmp_pc34 + (uint)tmp_b45 * -2 + 1;
            tmp_pc35 = tmp_pc35 + (uint)tmp_b45 * -2 + 1;
          }
          goto LAB_0007562b;
        }
        switch(tmp_i23) {
        case 0xf:
_L632:
          tmp_pc34 = "vaporized himself";
          break;
        case 0x10:
        case 0x12:
_L800:
          tmp_pc34 = "dove on his own grenade";
          break;
        case 0x11:
_L635:
          tmp_pc34 = "played with fire";
          break;
        default:
          goto _L631;
        case 0x15:
_L636:
          tmp_pc34 = "dynamited himself to pieces";
          break;
        case 0x16:
_L637:
          tmp_pc34 = "obliterated himself";
          break;
        case 0x19:
_L638:
          tmp_pc34 = "fired-for-effect on himself";
          break;
        case 0x1f:
        case 0x3e:
_L639:
          tmp_pc34 = "fell to his death";
          break;
        case 0x20:
_L640:
          tmp_pc34 = "killed himself";
          break;
        case 0x26:
        case 0x27:
_L641:
          tmp_pc34 = "ate his own rifle grenade";
          break;
        case 0x28:
_L642:
          tmp_pc34 = "failed to spot his own landmine";
          break;
        case 0x29:
_L643:
          tmp_pc34 = "embraced his own satchel explosion";
          break;
        case 0x2e:
_L644:
          tmp_pc34 = "engineered himself into oblivion";
          break;
        case 0x2f:
_L645:
          tmp_pc34 = "buried himself alive";
          break;
        case 0x33:
_L646:
          tmp_pc34 = "never saw his own mortar round coming";
          break;
        case 0x38:
_L647:
          tmp_pc34 = "danced on his airstrike marker";
          break;
        case 0x39:
          goto _L648;
        case 0x3b:
_L649:
          tmp_pc34 = "poisonned himself";
          break;
        case 0x3d:
_L650:
          tmp_pc34 = "was killed (Censor)";
          break;
        case 0x3f:
_L651:
          tmp_pc34 = "played with knives!";
          break;
        case 0x40:
_L652:
          tmp_pc34 = "gibbed himself";
          break;
        case 0x41:
_L653:
          tmp_pc34 = "was detonated by his own bomb";
          break;
        case 0x42:
_L654:
          tmp_pc34 = "forgot where his tripmine was";
          break;
        case 0x43:
_L655:
          tmp_pc34 = "choked on his own poison gas";
          break;
        case 0x44:
_L656:
          tmp_pc34 = "choked on his own poison gas landmine";
        }
LAB_0007466b:
        local_19c = &local_14c;
        if (GHIDRA_FIELD(cg_obituary, 12, 4) == 2) {
          local_17c = (uint32_t *)&g_unk_0011d841;
        }
        else {
          local_17c = (uint32_t *)&g_unk_0011d840;
        }
        tmp_u27 = va("%s %s%s",local_19c,tmp_pc34,local_17c);
        if (tmp_u22 == 2) {
          CG_AddToTeamChat(tmp_u27,param_1[0x2b]);
        }
        else if ((int)tmp_u22 < 3) {
          if (tmp_u22 == 1) {
            CG_AddPMItem(3,tmp_u27,tmp_u30,OB_YELLOW);
            goto _L648;
          }
        }
        else if ((int)tmp_u22 < 5) {
          local_17c = (uint32_t *)OB_YELLOW;
          nitrox_AddGraphicObituary(local_19c,local_180,&local_11c,OB_YELLOW,local_18c);
        }
        else if (tmp_u22 == 1) goto _L648;
        if (GHIDRA_FIELD(cg_obituary, 12, 4) == 2) {
          tmp_pu36 = &g_unk_0011d840;
        }
        else {
          tmp_pu36 = &g_unk_0011d841;
        }
LAB_00072794:
        tmp_u30 = va("%s%s",tmp_u27,tmp_pu36,local_17c);
        trap_Print(tmp_u30);
      }
_L648:
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x39:
      trap_S_StartSoundEx(0,*param_1,2,0,8);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x3a:
      trap_S_StartSound(param_1 + 6,0xffffffff,0,GHIDRA_FIELD(cgs, 33787796, 4));
      ByteToDir(param_1[0x2f],&local_158);
      CG_GibPlayer(param_1,param_1 + 0x1e5,&local_158);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x3b:
      param_1[0x28] = 0;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x3c:
      if (param_1[0x3d] == 3) {
        CG_ParticleSmoke(GHIDRA_FIELD(cgs, 68524, 4),param_1);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      else {
        CG_ParticleSmoke(GHIDRA_FIELD(cgs, 68088, 4),param_1);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x3d:
    case 0x3e:
      if (param_1[0x3d] == 0) {
        param_1[0x3d] = 1;
      }
      tmp_i29 = rand();
      tmp_i23 = param_1[0x20];
      tmp_i29 = tmp_i29 % param_1[0x3d];
      tmp_i28 = param_1[0x2c];
      tmp_i33 = param_1[0x21];
      tmp_i25 = param_1[0x22];
      if (tmp_i29 == 0) {
        tmp_i29 = 1;
      }
      else {
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
        if (tmp_i29 < 1) break;
      }
      if (tmp_u37 == 0x3e) {
        tmp_i23 = 0;
        do {
          local_14c = (float)param_1[0x17];
          tmp_i23 = tmp_i23 + 1;
          local_148[0] = (float)param_1[0x18];
          local_148[1] = (float)param_1[0x19];
          local_11c = local_14c;
          local_118[0] = local_148[0];
          local_118[1] = local_148[1];
          tmp_u37 = rand();
          local_11c = (float)(int)((tmp_u37 & 0x1f) - 0x10) + local_11c;
          tmp_u37 = rand();
          local_118[0] = (float)(int)((tmp_u37 & 0x1f) - 0x10) + local_118[0];
          tmp_u37 = rand();
          local_118[1] = (float)(int)((tmp_u37 & 0x1f) - 0x10) + local_118[1];
          CG_Tracer(&local_14c,&local_11c,1);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        } while (tmp_i23 < tmp_i29);
      }
      else {
        tmp_i43 = 0;
        do {
          tmp_i43 = tmp_i43 + 1;
          CG_ParticleSparks(param_1 + 0x17,param_1 + 0x1d,tmp_i28,tmp_i23,tmp_i33,tmp_i25);
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        } while (tmp_i43 < tmp_i29);
      }
      break;
    case 0x3f:
      ByteToDir(param_1[0x2f],&local_158);
      CG_Explode(param_1,param_2,&local_158,0);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x40:
      ByteToDir(param_1[0x2f],&local_158);
      CG_Rubble(param_1,param_2,&local_158,0);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x41:
      ByteToDir(param_1[0x2f],&local_158);
      CG_Effect(param_1,param_2,&local_158);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x42:
      CG_MortarEFX(param_1);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x43:
      trap_S_StartSound(0,*param_1,0,*(uint32_t *)(cg_weapons + param_1[0x3a] * 0x17ac + 0x1764));
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x44:
      CG_SnowLink(param_1,1);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x45:
      CG_SnowLink(param_1,0);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x46:
      ByteToDir(param_1[0x2f],&local_158);
      CG_MissileHitWallSmall(param_1[0x3a],0,param_2,&local_158);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x47:
      ByteToDir(param_1[0x2f],&local_158);
      if ((param_1[0x3a] - 0xdU & 0xfffffff7) == 0) {
        CG_MissileHitWall(param_1[0x3a],0,param_2,&local_158,0);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      else {
        CG_MissileHitWall(0x11,0,param_2,&local_158,0);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x48:
      tmp_i23 = rand();
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (-1 < tmp_i23 % 3) {
        trap_S_StartSound(param_2,0xffffffff,0,*(uint32_t *)(cgs + (tmp_i23 % 3) * 4 + 0x10e08));
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x49:
      if ((param_1[0x2b] == *(int *)(g_unk_01047b00 + 0xcc)) && (g_unk_010b4564 != -2)) {
        g_unk_010b4564 = g_unk_010906e0;
        g_unk_010b4568 = *param_2;
        g_unk_010b456c = param_2[1];
        g_unk_010b4570 = param_2[2];
        if (param_1[0x3d] == 0) {
          g_unk_010b4574 = 0;
        }
        else {
          g_unk_010b4574 = 1;
        }
      }
      break;
    case 0x4a:
      ByteToDir(param_1[0x2f],&local_158);
      CG_Shard(param_1,param_2,&local_158);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x4b:
      tmp_i33 = CG_AllocLocalEntity();
      tmp_u26 = footstepcnt_12304;
      tmp_u24 = splashfootstepcnt_12305;
      *(uint32_t *)(tmp_i33 + 8) = 0xe;
      tmp_i23 = g_unk_010906e0;
      *(uint32_t *)(tmp_i33 + 0x20) = 0;
      *(int *)(tmp_i33 + 0x10) = tmp_i23;
      *(int *)(tmp_i33 + 0x14) = tmp_i23 + 20000;
      *(int *)(tmp_i33 + 0x2c) = param_1[0x17];
      *(int *)(tmp_i33 + 0x30) = param_1[0x18];
      *(int *)(tmp_i33 + 0x34) = param_1[0x19];
      *(int *)(tmp_i33 + 0x50) = param_1[0x1a];
      *(int *)(tmp_i33 + 0x54) = param_1[0x1b];
      tmp_i23 = param_1[0x1c];
      *(uint32_t *)(tmp_i33 + 0x1a4) = 0;
      *(int *)(tmp_i33 + 0x58) = tmp_i23;
      break;
    case 0x4c:
      CG_Particle_OilParticle
                (GHIDRA_FIELD(cgs, 68516, 4),param_1 + 0x17,param_1 + 0x1a,param_1[0x15],param_1[0x3d]);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x4d:
      CG_Particle_OilSlick(GHIDRA_FIELD(cgs, 68520, 4),param_1);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x4e:
      CG_OilSlickRemove(param_1);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x4f:
      CG_ParticleSnowFlurry(GHIDRA_FIELD(cgs, 68512, 4),param_1);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x50:
      CG_ParticleDust(param_1,param_1 + 0x17,param_1 + 0x1d);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x51:
      CG_RumbleEfx(param_1[0x1d],param_1[0x1e]);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x52:
      CG_AddBulletParticles
                (param_1 + 0x17,param_1 + 0x1d,(int)ROUND((float)param_1[0x22]),800,param_1[0x3d],
                 0x3f800000);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x53:
      CG_FireFlameChunks(param_1,param_1 + 0x17,param_1 + 0xf,0x3f19999a,1,1);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x54:
      CG_Bullet(param_1 + 6,param_1[0x23],&local_158,1,param_1[0x2f],param_1[0x24],0,param_1[0x43]);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x55:
      ByteToDir(param_1[0x2f],&local_158);
      CG_Bullet(param_1 + 6,param_1[0x23],&local_158,0,0x3fe,param_1[0x24],param_1[0x1a],
                param_1[0x43]);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x56:
      local_11c = *(float *)(g_unk_01047b00 + 0x40) - (float)param_1[0x1e5];
      local_118[0] = *(float *)(g_unk_01047b00 + 0x44) - (float)param_1[0x1e6];
      local_118[1] = *(float *)(g_unk_01047b00 + 0x48) - (float)param_1[0x1e7];
      tmp_l46 = (long double)VectorLength(&local_11c);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (tmp_l46 <= (long double)param_1[0x3f]) {
        tmp_l20 = (long double)1;
        tmp_l46 = tmp_l20 - tmp_l46 / (long double)param_1[0x3f];
        if (tmp_l20 < tmp_l46) {
          tmp_l46 = tmp_l20;
        }
        CG_StartShakeCamera((float)tmp_l46);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x57:
      trap_S_StartSound(0,*param_1,2,GHIDRA_FIELD(cgs, 69624, 4));
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x58:
      CG_Debris(param_1,param_2,param_1 + 0x1a);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x59:
      if (param_1[0x24] == 1) {
        CG_UnsetActiveOnScriptSpeaker(param_1[0x23]);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      else if (param_1[0x24] == 2) {
        CG_SetActiveOnScriptSpeaker(param_1[0x23]);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      else {
        CG_ToggleActiveOnScriptSpeaker(param_1[0x23]);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x5a:
      tmp_i23 = CG_GetPMItemText(param_1);
      tmp_u30 = CG_GetPMItemIcon(param_1);
      if (tmp_i23 != 0) {
        CG_AddPMItem(param_1[0x43],tmp_i23,tmp_u30,0);
      }
      CG_PlayPMItemSound(param_1);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x5b:
      tmp_i23 = param_1[0x3d];
      if (tmp_i23 == 1) {
        if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) == 1) {
          tmp_pc34 = "axis_hq_ffe_abort";
        }
        else {
          tmp_pc34 = "allies_hq_ffe_abort";
        }
        CG_AddToTeamChat("^7Fire Mission: ^3Aborting, can\'t see target.",
                         *(int *)(g_unk_01047b00 + 0xcc));
      }
      else if (tmp_i23 == 2) {
        if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) == 1) {
          tmp_pc34 = "axis_hq_ffe";
        }
        else {
          tmp_pc34 = "allies_hq_ffe";
        }
        CG_AddToTeamChat("^7Fire Mission: ^3Firing for effect!",*(int *)(g_unk_01047b00 + 0xcc));
      }
      else {
        if (tmp_i23 != 0) break;
        if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) == 1) {
          tmp_pc34 = "axis_hq_ffe_denied";
        }
        else {
          tmp_pc34 = "allies_hq_ffe_denied";
        }
        CG_AddToTeamChat("^7Fire Mission: ^3Insufficient fire support.",
                         *(int *)(g_unk_01047b00 + 0xcc));
      }
      CG_SoundPlaySoundScript(tmp_pc34,0,0xffffffff,param_1[0x43] == 0);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x5c:
      tmp_i23 = param_1[0x3d];
      if (tmp_i23 == 1) {
        if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) == 1) {
          tmp_pc34 = "axis_hq_airstrike_abort";
        }
        else {
          tmp_pc34 = "allies_hq_airstrike_abort";
        }
        CG_AddToTeamChat("^7Pilot: ^3Aborting, can\'t see target.",*(int *)(g_unk_01047b00 + 0xcc));
      }
      else if (tmp_i23 == 2) {
        if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) == 1) {
          tmp_pc34 = "axis_hq_airstrike";
        }
        else {
          tmp_pc34 = "allies_hq_airstrike";
        }
      }
      else {
        if (tmp_i23 != 0) break;
        if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) == 1) {
          tmp_pc34 = "axis_hq_airstrike_denied";
        }
        else {
          tmp_pc34 = "allies_hq_airstrike_denied";
        }
        CG_AddToTeamChat("^7HQ: ^3All available planes are already en-route.",
                         *(int *)(g_unk_01047b00 + 0xcc));
      }
      CG_SoundPlaySoundScript(tmp_pc34,0,0xffffffff,param_1[0x43] == 0);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x5d:
      tmp_i23 = *param_1;
      if (*(int *)(cgs + tmp_i23 * 0x1a4 + 0x9494) == 1) {
        trap_S_StartSound(0,tmp_i23,0,GHIDRA_FIELD(cgs, 69648, 4));
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      else if (*(int *)(cgs + tmp_i23 * 0x1a4 + 0x9494) == 2) {
        trap_S_StartSound(0,tmp_i23,0,GHIDRA_FIELD(cgs, 69652, 4));
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x5e:
      tmp_pu44 = (uint32_t *)(cg_entities + param_1[0x24] * 0xaf8 + 0x268);
      for (tmp_i23 = 0x145; tmp_u24 = splashfootstepcnt_12305, tmp_u26 = footstepcnt_12304, tmp_i23 != 0
          ; tmp_i23 = tmp_i23 + -1) {
        *tmp_pu44 = 0;
        tmp_pu44 = tmp_pu44 + (uint)tmp_b45 * -2 + 1;
      }
      break;
    case 0x5f:
      CG_FireWeapon(param_1,0x5f);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x60:
      if (GHIDRA_FIELD(cg_shoveSounds, 12, 4) != 0) {
        trap_S_StartSoundVControl(0,*param_1,0,GHIDRA_FIELD(cgs, 69264, 4),0xff);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x61:
      if (*param_1 == *(int *)(g_unk_01047b00 + 0xcc)) {
        CG_FinishWeaponChange(g_unk_01091814,param_1[0x2f]);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x62:
      if ((*param_1 == g_unk_01047ac4) && (GHIDRA_FIELD(cg_pmSounds, 12, 4) != 0)) {
        trap_S_StartSoundVControl(0,*param_1,3,GHIDRA_FIELD(cgs, 69656, 4),0xff);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 99:
      if (GHIDRA_FIELD(cg_hitSounds, 12, 4) != 0) {
        if (param_1[0x2f] == 3) {
          trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),3,GHIDRA_FIELD(cgs, 132008, 4));
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
        else if (param_1[0x2f] == 4) {
          trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),3,GHIDRA_FIELD(cgs, 132000, 4));
          tmp_u24 = splashfootstepcnt_12305;
          tmp_u26 = footstepcnt_12304;
        }
      }
      break;
    case 100:
      trap_S_StartSoundVControl
                (0,*param_1,0,*(uint32_t *)(cgs + param_1[0x2f] * 4 + 0x2038f84),0xff);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x65:
      g_unk_010ef120 = param_1[0x43];
      GHIDRA_FIELD(cgs, 33787768, 4) = param_1[0x44];
      g_unk_010ef124 = param_1[0x45];
      nitmod_AddSpreePrint();
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x66:
      trap_S_StartSound(g_unk_01047b00 + 0x40,*(uint32_t *)(g_unk_01047b00 + 0xcc),7,GHIDRA_FIELD(cgs, 132356, 4));
      local_11c = *(float *)(g_unk_01047b00 + 0x40) - (float)param_1[0x1e5];
      local_118[0] = *(float *)(g_unk_01047b00 + 0x44) - (float)param_1[0x1e6];
      local_118[1] = *(float *)(g_unk_01047b00 + 0x48) - (float)param_1[0x1e7];
      tmp_l46 = (long double)VectorLength(&local_11c);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      if (tmp_l46 <= (long double)param_1[0x3f]) {
        tmp_l20 = (long double)1;
        tmp_l46 = tmp_l20 - tmp_l46 / (long double)param_1[0x3f];
        if (tmp_l20 < tmp_l46) {
          tmp_l46 = tmp_l20;
        }
        CG_StartShakeCamera((float)tmp_l46);
        tmp_u24 = splashfootstepcnt_12305;
        tmp_u26 = footstepcnt_12304;
      }
      break;
    case 0x67:
      trap_S_StartSoundVControl
                (0,*(uint32_t *)(g_unk_01047b00 + 0xcc),0,
                 *(uint32_t *)(cgs + param_1[0x2f] * 4 + 0x2038f84),0xff);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x68:
      CG_BotDebugLine(param_1 + 0x20);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x69:
      local_118[7] = (float)param_1[8];
      local_14c = 1.0;
      local_148[0] = 0.0;
      local_148[1] = 0.0;
      local_11c = (float)param_1[0x1a] * 5.0 + (float)param_1[6];
      local_118[0] = (float)param_1[0x1b] * 5.0 + (float)param_1[7];
      local_118[1] = (float)param_1[0x1c] * 5.0 + local_118[7];
      local_118[2] = (float)param_1[0x1d] * 5.0 + (float)param_1[6];
      local_118[3] = (float)param_1[0x1e] * 5.0 + (float)param_1[7];
      local_118[4] = (float)param_1[0x1f] * 5.0 + local_118[7];
      local_118[5] = (float)param_1[0x20] * 5.0 + (float)param_1[6];
      local_118[6] = (float)param_1[0x21] * 5.0 + (float)param_1[7];
      local_118[7] = (float)param_1[0x22] * 5.0 + local_118[7];
      CG_BotDebugLine(&local_14c);
      local_14c = 0.0;
      local_148[0] = 1.0;
      local_148[1] = 0.0;
      CG_BotDebugLine(&local_14c);
      local_14c = 0.0;
      local_148[0] = 0.0;
      local_148[1] = 1.0;
      CG_BotDebugLine(&local_14c);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
      break;
    case 0x6a:
      tmp_i23 = param_1[0x23];
      local_14c = (float)-(param_1[0x43] / 2);
      local_148[0] = (float)-(param_1[0x44] / 2);
      local_148[1] = (float)(param_1[0x45] / 2);
      local_148[2] = (float)(param_1[0x43] / 2);
      local_148[3] = local_148[0];
      local_148[4] = local_148[1];
      local_148[5] = local_148[2];
      local_148[6] = local_148[0];
      local_148[7] = (float)-(param_1[0x45] / 2);
      local_148[8] = local_14c;
      local_124 = local_148[0];
      local_120 = (uint8_t  [4])local_148[7];
      local_11c = local_14c;
      local_118[0] = (float)(param_1[0x44] / 2);
      local_118[1] = local_148[1];
      local_118[2] = local_148[2];
      local_118[3] = local_118[0];
      local_118[4] = local_148[1];
      local_118[5] = local_148[2];
      local_118[6] = local_118[0];
      local_118[7] = local_148[7];
      local_118[8] = local_14c;
      local_f4 = local_118[0];
      local_f0 = local_148[7];
      tmp_f1 = (float)param_1[0x1a];
      tmp_f2 = (float)param_1[0x1b];
      tmp_f3 = (float)param_1[0x1c];
      tmp_f4 = (float)param_1[0x1d];
      tmp_f5 = (float)param_1[0x1e];
      tmp_f6 = (float)param_1[0x1f];
      tmp_f7 = (float)param_1[0x20];
      tmp_f8 = (float)param_1[0x21];
      tmp_f9 = (float)param_1[0x22];
      tmp_f10 = (float)param_1[6];
      tmp_f11 = (float)param_1[7];
      tmp_f12 = (float)param_1[8];
      pfVar31 = (float *)&local_14c;
      pfVar41 = (float *)&local_11c;
      do {
        tmp_f13 = *pfVar31;
        pfVar32 = pfVar31 + 3;
        tmp_f14 = *pfVar41;
        tmp_f15 = pfVar31[1];
        tmp_f16 = pfVar41[1];
        tmp_f17 = pfVar41[1];
        tmp_f18 = pfVar41[1];
        *pfVar31 = tmp_f7 * pfVar31[2] + tmp_f4 * pfVar31[1] + tmp_f1 * tmp_f13 + tmp_f10;
        pfVar31[1] = tmp_f8 * pfVar31[2] + tmp_f5 * pfVar31[1] + tmp_f2 * tmp_f13 + tmp_f11;
        pfVar31[2] = pfVar31[2] * tmp_f9 + tmp_f6 * tmp_f15 + tmp_f13 * tmp_f3 + tmp_f12;
        *pfVar41 = tmp_f7 * pfVar41[2] + tmp_f4 * tmp_f16 + tmp_f1 * tmp_f14 + tmp_f10;
        pfVar41[1] = tmp_f8 * pfVar41[2] + tmp_f5 * tmp_f17 + tmp_f2 * tmp_f14 + tmp_f11;
        pfVar41[2] = tmp_f6 * tmp_f18 + tmp_f14 * tmp_f3 + tmp_f12 + pfVar41[2] * tmp_f9;
        pfVar31 = pfVar32;
        pfVar41 = pfVar41 + 3;
      } while (pfVar32 != (float *)&local_11c);
      tmp_i33 = 0x1f;
      if (tmp_i23 < 0x20) {
        tmp_i33 = tmp_i23;
      }
      tmp_i33 = tmp_i33 * 0x10;
      local_158 = *(uint32_t *)(g_color_table + tmp_i33);
      local_154 = *(uint32_t *)(g_color_table + tmp_i33 + 4);
      local_150 = *(uint8_t (*) [4])(g_color_table + tmp_i33 + 8);
      CG_BotDebugLine(&local_158);
      CG_BotDebugLine(&local_158);
      CG_BotDebugLine(&local_158);
      CG_BotDebugLine(&local_158);
      CG_BotDebugLine(&local_158);
      CG_BotDebugLine(&local_158);
      CG_BotDebugLine(&local_158);
      CG_BotDebugLine(&local_158);
      CG_BotDebugLine(&local_158);
      CG_BotDebugLine(&local_158);
      CG_BotDebugLine(&local_158);
      CG_BotDebugLine(&local_158);
      tmp_u24 = splashfootstepcnt_12305;
      tmp_u26 = footstepcnt_12304;
    }
  }
  else {
    if (tmp_u37 != 0x32) {
      CG_Printf("time:%i ent:%3i  event:%s \n",g_unk_010906e0,*param_1,
                *(uint32_t *)(eventnames + tmp_u37 * 4));
      goto LAB_00071dee;
    }
    tmp_u42 = param_1[0x2b];
    if (tmp_u42 < 0x40) goto LAB_00071e29;
    CG_PlayerClassForClientinfo(0x10f926c,param_1);
    CG_CharacterForClientinfo(0x10f926c,param_1);
_L461:
    local_11c = (float)param_1[0x1d] / 255.0;
    local_118[0] = (float)param_1[0x1e] / 255.0;
    local_118[1] = (float)param_1[0x1f] / 255.0;
    CG_RailTrail(&local_11c,param_1 + 0x1a,param_1 + 6,param_1[0x3e],param_1[0x43]);
    tmp_u24 = splashfootstepcnt_12305;
    tmp_u26 = footstepcnt_12304;
  }
  tmp_u37 = rand();
  footstepcnt_12304 = tmp_u37 & 3;
  splashfootstepcnt_12305 = footstepcnt_12304;
  if ((footstepcnt_12304 == tmp_u24) &&
     (splashfootstepcnt_12305 = tmp_u24 + 1, 3 < (int)splashfootstepcnt_12305)) {
    splashfootstepcnt_12305 = 0;
  }
  if ((footstepcnt_12304 == tmp_u26) &&
     (footstepcnt_12304 = footstepcnt_12304 + 1, 3 < footstepcnt_12304)) {
    footstepcnt_12304 = 0;
  }
  return;
}

void CG_CheckEvents(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  uint tmp_u4;
  uint tmp_u5;
  
  tmp_i1 = param_1 + 0x794;
  BG_EvaluateTrajectory
            (param_1 + 0xc,*(uint32_t *)(g_unk_01047b00 + 8),tmp_i1,0,
             *(uint32_t *)(param_1 + 0x110));
  CG_SetEntitySoundPosition(param_1);
  if (*(uint *)(param_1 + 4) < 0x3c) {
    tmp_u3 = *(uint *)(param_1 + 0xc0);
    tmp_u4 = *(uint *)(param_1 + 0x254);
    if ((int)tmp_u3 < (int)tmp_u4) {
      tmp_u4 = tmp_u4 - 0x100;
      *(uint *)(param_1 + 0x254) = tmp_u4;
    }
    if (4 < (int)(tmp_u3 - tmp_u4)) {
      tmp_u4 = tmp_u3 - 4;
      *(uint *)(param_1 + 0x254) = tmp_u4;
    }
    tmp_u5 = tmp_u4;
    if (tmp_u3 != tmp_u4) {
      do {
        tmp_u4 = tmp_u5 + 1;
        tmp_i2 = param_1 + (tmp_u5 & 3) * 4;
        *(uint32_t *)(param_1 + 0xb8) = *(uint32_t *)(tmp_i2 + 0xc4);
        *(uint32_t *)(param_1 + 0xbc) = *(uint32_t *)(tmp_i2 + 0xd4);
        CG_EntityEvent(param_1,tmp_i1);
        tmp_u5 = tmp_u4;
      } while (*(uint *)(param_1 + 0xc0) != tmp_u4);
    }
    *(uint *)(param_1 + 0x254) = tmp_u4;
    *(uint32_t *)(param_1 + 0xb8) = *(uint32_t *)(param_1 + 0x250);
    return;
  }
  if (*(int *)(param_1 + 0x250) == 0) {
    *(uint32_t *)(param_1 + 0x250) = 1;
    *(uint *)(param_1 + 0xb8) = *(uint *)(param_1 + 4) - 0x3b;
    CG_EntityEvent(param_1,tmp_i1);
    return;
  }
  return;
}

