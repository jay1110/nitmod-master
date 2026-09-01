/* Client entity placement and scene submission — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_ents.h"

void CG_ItemPickup(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  uint64_t tmp_u6;
  int local_24;
  int local_20 [3];
  uint32_t uStack_14;
  
  tmp_i5 = 7;
  uStack_14 = 0x1a5c9;
  tmp_i1 = *(int *)(bg_itemlist + param_1 * 0x38 + 0x28);
  tmp_u4 = *(uint *)(bg_itemlist + param_1 * 0x38 + 0x24);
  if (tmp_u4 != 2) {
    if (tmp_u4 < 3) {
      if (tmp_u4 == 1) {
        tmp_i5 = (uint)(tmp_i1 == 0xc) * 3 + 4;
        goto LAB_0001a61c;
      }
    }
    else {
      tmp_i5 = 8;
      if ((tmp_u4 == 3) || (tmp_i5 = 5, tmp_u4 == 5)) goto LAB_0001a61c;
    }
    tmp_i5 = 4;
  }
LAB_0001a61c:
  tmp_u2 = *(uint32_t *)(cgs + tmp_i5 * 4 + 0x202b8);
  tmp_u3 = CG_PickupItemText(param_1);
  tmp_u3 = va("Picked up %s",tmp_u3);
  CG_AddPMItem(tmp_i5,tmp_u3,tmp_u2,0);
  if ((((*(int *)(bg_itemlist + param_1 * 0x38 + 0x24) == 1) && (GHIDRA_FIELD(cg_autoswitch, 12, 4) != 0)) &&
      (g_unk_010907a4 != 7)) && ((tmp_u4 = tmp_i1 - 0x27, 2 < tmp_u4 && (tmp_i1 != 0xc)))) {
    if (g_unk_01091814 == 0) {
      g_unk_010aac34 = g_unk_010906e0;
      g_unk_01091814 = tmp_i1;
    }
    else {
      if (GHIDRA_FIELD(cg_autoswitch, 12, 4) != 1) {
        if ((GHIDRA_FIELD(cg_autoswitch, 12, 4) - 2 & 0xfffffffd) == 0) {
          tmp_u6 = COM_BitCheck(g_unk_01047b00 + 0x400,tmp_i1,tmp_i1,tmp_i1);
          tmp_u4 = (uint)((ulonglong)tmp_u6 >> 0x20);
          if ((int)tmp_u6 == 0) {
            g_unk_010aac34 = g_unk_010906e0;
            g_unk_01091814 = tmp_i1;
          }
        }
        if (1 < GHIDRA_FIELD(cg_autoswitch, 12, 4) - 3) {
          return;
        }
        tmp_i5 = CG_WeaponIndex(g_unk_01091814,&local_24,0,tmp_u4);
        if (tmp_i5 == 0) {
          return;
        }
        tmp_i5 = CG_WeaponIndex(tmp_i1,local_20,0,tmp_i5);
        if (tmp_i5 == 0) {
          return;
        }
        if (local_20[0] <= local_24) {
          return;
        }
      }
      g_unk_010aac34 = g_unk_010906e0;
      g_unk_01091814 = tmp_i1;
    }
  }
  return;
}

void CG_AddAtmosphericEffects(void)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  float local_40;
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x390a9;
  if (((0 < (int)GHIDRA_FIELD(cg_atmFx, 272028, 4)) && (GHIDRA_FIELD(cg_atmFx, 272092, 4) != 0)) &&
     (0.0 < (float)GHIDRA_FIELD(cg_atmosphericEffects, 8, 4))) {
    tmp_f1 = (float)(int)GHIDRA_FIELD(cg_atmFx, 272028, 4);
    if ((float)GHIDRA_FIELD(cg_atmosphericEffects, 8, 4) < 1.0) {
      tmp_f1 = tmp_f1 * (float)GHIDRA_FIELD(cg_atmosphericEffects, 8, 4);
    }
    if (g_unk_010906e0 < (int)GHIDRA_FIELD(cg_atmFx, 272044, 4)) {
      local_28 = (float)GHIDRA_FIELD(cg_atmFx, 272096, 4);
      local_24 = (float)GHIDRA_FIELD(cg_atmFx, 272100, 4);
      local_20 = (float)GHIDRA_FIELD(cg_atmFx, 272104, 4);
      local_40 = (float)GHIDRA_FIELD(cg_atmFx, 272072, 4);
    }
    else {
      local_28 = (float)GHIDRA_FIELD(cg_atmFx, 272108, 4);
      local_24 = (float)GHIDRA_FIELD(cg_atmFx, 272112, 4);
      local_20 = (float)GHIDRA_FIELD(cg_atmFx, 272116, 4);
      if (g_unk_010906e0 < (int)GHIDRA_FIELD(cg_atmFx, 272032, 4)) {
        tmp_f2 = (float)(g_unk_010906e0 - GHIDRA_FIELD(cg_atmFx, 272044, 4)) /
                (float)(int)(GHIDRA_FIELD(cg_atmFx, 272032, 4) - GHIDRA_FIELD(cg_atmFx, 272044, 4));
        local_28 = (float)GHIDRA_FIELD(cg_atmFx, 272096, 4) +
                   ((float)GHIDRA_FIELD(cg_atmFx, 272108, 4) - (float)GHIDRA_FIELD(cg_atmFx, 272096, 4)) * tmp_f2;
        local_24 = ((float)GHIDRA_FIELD(cg_atmFx, 272112, 4) - (float)GHIDRA_FIELD(cg_atmFx, 272100, 4)) * tmp_f2 +
                   (float)GHIDRA_FIELD(cg_atmFx, 272100, 4);
        local_20 = ((float)GHIDRA_FIELD(cg_atmFx, 272116, 4) - (float)GHIDRA_FIELD(cg_atmFx, 272104, 4)) * tmp_f2 +
                   (float)GHIDRA_FIELD(cg_atmFx, 272104, 4);
        local_40 = ((float)GHIDRA_FIELD(cg_atmFx, 272076, 4) - (float)GHIDRA_FIELD(cg_atmFx, 272072, 4)) * tmp_f2 +
                   (float)GHIDRA_FIELD(cg_atmFx, 272072, 4);
      }
      else if (g_unk_010906e0 < (int)GHIDRA_FIELD(cg_atmFx, 272036, 4)) {
        local_40 = (float)GHIDRA_FIELD(cg_atmFx, 272076, 4);
      }
      else {
        tmp_f2 = 1.0 - (float)(g_unk_010906e0 - GHIDRA_FIELD(cg_atmFx, 272036, 4)) /
                      (float)(int)(GHIDRA_FIELD(cg_atmFx, 272040, 4) - GHIDRA_FIELD(cg_atmFx, 272036, 4));
        local_28 = (float)GHIDRA_FIELD(cg_atmFx, 272096, 4) +
                   ((float)GHIDRA_FIELD(cg_atmFx, 272108, 4) - (float)GHIDRA_FIELD(cg_atmFx, 272096, 4)) * tmp_f2;
        local_24 = ((float)GHIDRA_FIELD(cg_atmFx, 272112, 4) - (float)GHIDRA_FIELD(cg_atmFx, 272100, 4)) * tmp_f2 +
                   (float)GHIDRA_FIELD(cg_atmFx, 272100, 4);
        local_20 = ((float)GHIDRA_FIELD(cg_atmFx, 272116, 4) - (float)GHIDRA_FIELD(cg_atmFx, 272104, 4)) * tmp_f2 +
                   (float)GHIDRA_FIELD(cg_atmFx, 272104, 4);
        local_40 = ((float)GHIDRA_FIELD(cg_atmFx, 272076, 4) - (float)GHIDRA_FIELD(cg_atmFx, 272072, 4)) * tmp_f2 +
                   (float)GHIDRA_FIELD(cg_atmFx, 272072, 4);
        if ((int)GHIDRA_FIELD(cg_atmFx, 272040, 4) <= g_unk_010906e0) {
          CG_EffectGust();
        }
      }
    }
    GHIDRA_FIELD(cg_atmFx, 272148, 4) = GHIDRA_FIELD(cg_atmFx, 272144, 4);
    GHIDRA_FIELD(cg_atmFx, 272160, 4) = 0;
    GHIDRA_FIELD(cg_atmFx, 272156, 4) = 0;
    GHIDRA_FIELD(cg_atmFx, 272144, 4) = 0;
    GHIDRA_FIELD(cg_atmFx, 272152, 4) = 0;
    GHIDRA_FIELD(cg_atmFx, 272120, 4) = *(uint32_t *)(g_unk_010afbcc + 0x24);
    GHIDRA_FIELD(cg_atmFx, 272124, 4) = *(uint32_t *)(g_unk_010afbcc + 0x28);
    GHIDRA_FIELD(cg_atmFx, 272128, 4) = 0;
    if (0 < (int)ROUND(tmp_f1)) {
      tmp_i5 = 0;
      tmp_pu4 = cg_atmFx;
      do {
        tmp_i3 = (*(void *)GHIDRA_FIELD(cg_atmFx, 272132, 4))(tmp_pu4);
        if (tmp_i3 == 0) {
          tmp_i3 = (*(void *)GHIDRA_FIELD(cg_atmFx, 272136, 4))(tmp_pu4,&local_28,local_40);
          if (tmp_i3 != 0) {
            GHIDRA_FIELD(cg_atmFx, 272156, 4) = GHIDRA_FIELD(cg_atmFx, 272156, 4) + 1;
            goto LAB_00039332;
          }
          *(int *)(tmp_pu4 + 0x3c) = g_unk_010906e0 + 1000;
        }
        else {
LAB_00039332:
          (*(void *)GHIDRA_FIELD(cg_atmFx, 272140, 4))(tmp_pu4);
          GHIDRA_FIELD(cg_atmFx, 272144, 4) = GHIDRA_FIELD(cg_atmFx, 272144, 4) + 1;
        }
        tmp_i5 = tmp_i5 + 1;
        tmp_pu4 = tmp_pu4 + 0x44;
      } while (tmp_i5 != (int)ROUND(tmp_f1));
    }
    GHIDRA_FIELD(cg_atmFx, 272024, 4) = g_unk_010906e0;
  }
  return;
}

void CG_AdjustAutomapZoom(int param_1)
{
  float tmp_f1;
  int tmp_i2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint32_t tmp_u6;
  int *tmp_pi7;
  int tmp_i8;
  
  if (param_1 == 0) {
    tmp_f1 = (float)GHIDRA_FIELD(cg_automapZoom, 8, 4) / 1.2;
    if (tmp_f1 < 1.0) {
      tmp_f1 = 1.0;
    }
  }
  else {
    tmp_f1 = (float)GHIDRA_FIELD(cg_automapZoom, 8, 4) * 1.2;
    if (7.43 < tmp_f1) {
      tmp_f1 = 7.43;
    }
  }
  tmp_u6 = va(&g_unk_0011e95f,(double)tmp_f1);
  trap_Cvar_Set("cg_automapZoom",tmp_u6);
  tmp_f5 = g_unk_010abd68;
  tmp_f4 = g_unk_010abd64;
  tmp_f3 = g_unk_010abd58;
  tmp_f1 = g_unk_010abd54;
  tmp_u6 = GHIDRA_FIELD(cg_automapZoom, 8, 4);
  tmp_i2 = mapEntityCount;
  if (0 < mapEntityCount) {
    tmp_i8 = 0;
    tmp_pi7 = &mapEntities;
    do {
      tmp_i8 = tmp_i8 + 1;
      tmp_pi7[8] = (int)(((float)*tmp_pi7 - tmp_f1) * tmp_f4 * 100.0 * (float)tmp_u6);
      tmp_pi7[9] = (int)(((float)tmp_pi7[1] - tmp_f3) * tmp_f5 * 100.0 * (float)tmp_u6);
      tmp_pi7 = tmp_pi7 + 0xb;
    } while (tmp_i8 != tmp_i2);
  }
  return;
}

void CG_AddLagometerFrameInfo(void)
{
  uint tmp_u1;
  
  tmp_u1 = GHIDRA_FIELD(lagometer, 512, 4) & 0x7f;
  GHIDRA_FIELD(lagometer, 512, 4) = GHIDRA_FIELD(lagometer, 512, 4) + 1;
  *(int *)(lagometer + tmp_u1 * 4) = g_unk_010906e0 - g_unk_01047afc;
  return;
}

void CG_AddLagometerSnapshotInfo(uint32_t *param_1)
{
  uint tmp_u1;
  int tmp_i2;
  
  if (param_1 == (uint32_t *)0x0) {
    *(uint32_t *)(lagometer + (GHIDRA_FIELD(lagometer, 1540, 4) & 0x7f) * 4 + 0x404) = 0xffffffff;
    *(uint32_t *)(lagometer + (GHIDRA_FIELD(lagometer, 1540, 4) & 0x7f) * 4 + 0x608) = 0xffffffff;
    GHIDRA_FIELD(lagometer, 1540, 4) = GHIDRA_FIELD(lagometer, 1540, 4) + 1;
  }
  else {
    if (g_unk_01047aec == 0) {
      *(uint32_t *)(lagometer + (GHIDRA_FIELD(lagometer, 1540, 4) & 0x7f) * 4 + 0x404) = param_1[1];
      tmp_i2 = param_1[0x46];
      if (tmp_i2 < 0) {
        tmp_i2 = 0;
      }
      *(int *)(lagometer + (GHIDRA_FIELD(lagometer, 1540, 4) & 0x7f) * 4 + 0x608) = param_1[1] - tmp_i2;
    }
    else {
      *(int *)(lagometer + (GHIDRA_FIELD(lagometer, 1540, 4) & 0x7f) * 4 + 0x404) = param_1[2] - lasttime_12176;
      *(int *)(lagometer + (GHIDRA_FIELD(lagometer, 1540, 4) & 0x7f) * 4 + 0x608) = param_1[2] - lasttime_12176;
      lasttime_12176 = param_1[2];
    }
    tmp_u1 = GHIDRA_FIELD(lagometer, 1540, 4) & 0x7f;
    GHIDRA_FIELD(lagometer, 1540, 4) = GHIDRA_FIELD(lagometer, 1540, 4) + 1;
    *(uint32_t *)(lagometer + tmp_u1 * 4 + 0x204) = *param_1;
  }
  return;
}

void CG_AdjustFrom640(float *param_1,float *param_2,float *param_3,float *param_4)
{
  if (cg_hudPlacement == 1) {
    *param_1 = *param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else if (cg_hudPlacement == 2) {
    *param_1 = (float)GHIDRA_FIELD(cgs, 27372, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4) + *param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  }
  else {
    *param_1 = *param_1 * (float)GHIDRA_FIELD(cgs, 27364, 4) + (float)GHIDRA_FIELD(cgs, 27372, 4);
  }
  *param_2 = *param_2 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  *param_3 = *param_3 * (float)GHIDRA_FIELD(cgs, 27364, 4);
  *param_4 = *param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  return;
}

void CG_AdjustFrom640FullScreen(float *param_1,float *param_2,float *param_3,float *param_4)
{
  float tmp_f1;
  
  tmp_f1 = (float)(int)GHIDRA_FIELD(cgs, 27336, 4);
  *param_1 = *param_1 * (tmp_f1 / 640.0);
  *param_2 = *param_2 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  *param_3 = (tmp_f1 / 640.0) * *param_3;
  *param_4 = *param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4);
  return;
}

void CG_DrawPicFullScreen
               (float param_1,float param_2,float param_3,float param_4,uint32_t param_5)

{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  
  if (param_3 < 0.0) {
    param_3 = -param_3;
    tmp_u2 = 0;
    tmp_u4 = 0x3f800000;
  }
  else {
    tmp_u2 = 0x3f800000;
    tmp_u4 = 0;
  }
  if (param_4 < 0.0) {
    param_4 = -param_4;
    tmp_u1 = 0;
    tmp_u3 = 0x3f800000;
  }
  else {
    tmp_u1 = 0x3f800000;
    tmp_u3 = 0;
  }
  trap_R_DrawStretchPic
            (((float)(int)GHIDRA_FIELD(cgs, 27336, 4) / 640.0) * param_1,(float)GHIDRA_FIELD(cgs, 27368, 4) * param_2,
             param_3 * ((float)(int)GHIDRA_FIELD(cgs, 27336, 4) / 640.0),param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4),tmp_u4,
             tmp_u3,tmp_u2,tmp_u1,param_5);
  return;
}

void CG_FillRectFullScreen
               (float param_1,float param_2,float param_3,float param_4,uint32_t param_5)

{
  trap_R_SetColor(param_5);
  trap_R_DrawStretchPic
            (((float)(int)GHIDRA_FIELD(cgs, 27336, 4) / 640.0) * param_1,(float)GHIDRA_FIELD(cgs, 27368, 4) * param_2,
             param_3 * ((float)(int)GHIDRA_FIELD(cgs, 27336, 4) / 640.0),param_4 * (float)GHIDRA_FIELD(cgs, 27368, 4),0,0,0,
             0x3f800000,GHIDRA_FIELD(cgs, 67836, 4));
  trap_R_SetColor(0);
  return;
}

void CG_AddSmokeSprites(void)
{
  float tmp_f1;
  float tmp_f2;
  int *tmp_pi3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  uint tmp_u8;
  bool tmp_b9;
  uint tmp_u10;
  uint32_t *tmp_pu11;
  int tmp_i12;
  int *tmp_pi13;
  int *local_10c;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  uint32_t local_cc;
  uint32_t local_c8;
  uint32_t local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  uint8_t local_b4 [8];
  float local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  float local_7c;
  float local_78;
  float local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint8_t local_68;
  uint8_t local_67;
  uint8_t local_66;
  uint8_t local_65;
  float local_64;
  float local_60;
  float local_5c;
  uint32_t local_58;
  uint32_t local_54;
  uint8_t local_50;
  uint8_t local_4f;
  uint8_t local_4e;
  uint8_t local_4d;
  float local_4c;
  float local_48;
  float local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint8_t local_38;
  uint8_t local_37;
  uint8_t local_36;
  uint8_t local_35;
  float local_34;
  float local_30;
  float local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint8_t local_20;
  uint8_t local_1f;
  uint8_t local_1e;
  uint8_t local_1d;
  uint32_t uStack_14;
  
  uStack_14 = 0x64de9;
  tmp_f4 = (float)g_unk_010906dc * 0.078;
  tmp_pi3 = lastusedsmokesprite;
  do {
    while( true ) {
      if (tmp_pi3 == (int *)0x0) {
        return;
      }
      if ((tmp_pi3[0xe] == 0) || (*(int *)(tmp_pi3[0xe] + 0x244) != 0)) break;
LAB_00065320:
      tmp_pi3 = (int *)tmp_pi3[1];
    }
    local_c0 = (float)tmp_pi3[2];
    local_bc = (float)tmp_pi3[3];
    local_b8 = (float)tmp_pi3[4];
    tmp_pi3[2] = (int)((float)tmp_pi3[9] * tmp_f4 + local_c0);
    tmp_pi3[3] = (int)((float)tmp_pi3[10] * tmp_f4 + local_bc);
    tmp_pi3[4] = (int)((float)tmp_pi3[0xb] * tmp_f4 + local_b8);
    tmp_pi3[0xc] = (int)((float)tmp_pi3[0xc] + tmp_f4);
    tmp_pi3[0xd] = (int)(tmp_f4 * 1.25 + (float)tmp_pi3[0xd]);
    CG_Trace(local_b4,&local_c0,0,0,tmp_pi3 + 2,0xffffffff,1);
    tmp_f1 = (float)tmp_pi3[0xc];
    if (local_ac == 1.0) {
LAB_00064f12:
      tmp_i12 = tmp_pi3[0xe];
      if (tmp_i12 == 0) {
        tmp_f2 = 320.0;
        if (tmp_f1 <= 320.0) goto LAB_00065010;
      }
      else {
        if ((float)*(int *)(tmp_i12 + 0x10c) < 0.0) {
          tmp_f2 = 320.0;
        }
        else {
          tmp_f2 = (float)*(int *)(tmp_i12 + 0x10c) * 0.5;
        }
        if (tmp_f1 <= tmp_f2) {
LAB_00065010:
          tmp_f5 = (float)tmp_pi3[0xd] * 0.5;
          local_cc = *(uint32_t *)(g_unk_010afbcc + 0x30);
          local_c8 = *(uint32_t *)(g_unk_010afbcc + 0x34);
          local_c4 = *(uint32_t *)(g_unk_010afbcc + 0x38);
          RotatePointAroundVector(&local_e4,g_unk_010afbcc + 0x24,&local_cc,0);
          CrossProduct(g_unk_010afbcc + 0x24,&local_e4,&local_d8);
          local_64 = local_d8 * tmp_f5 + (float)tmp_pi3[2];
          local_60 = local_d4 * tmp_f5 + (float)tmp_pi3[3];
          local_5c = local_d0 * tmp_f5 + (float)tmp_pi3[4];
          tmp_f6 = -tmp_f5;
          local_34 = local_d8 * tmp_f6 + (float)tmp_pi3[2];
          local_30 = local_d4 * tmp_f6 + (float)tmp_pi3[3];
          local_2c = local_d0 * tmp_f6 + (float)tmp_pi3[4];
          tmp_f1 = (float)tmp_pi3[8];
          tmp_f7 = tmp_f2 * 0.8;
          if (tmp_f7 < (float)tmp_pi3[0xc]) {
            local_65 = (uint8_t)
                       (short)ROUND((tmp_f1 - (((float)tmp_pi3[0xc] - tmp_f7) / (tmp_f2 - tmp_f7)) *
                                             tmp_f1) * 255.0);
          }
          else {
            local_65 = (uint8_t)(short)ROUND(tmp_f1 * 255.0);
          }
          GHIDRA_FIELD(local_10c, 0, 1) = (uint8_t)(short)ROUND((float)tmp_pi3[5] * 255.0);
          local_70 = 0x3f800000;
          local_68 = GHIDRA_FIELD(local_10c, 0, 1);
          local_7c = local_64 + local_e4 * tmp_f5;
          local_67 = (uint8_t)(short)ROUND((float)tmp_pi3[6] * 255.0);
          local_6c = 0;
          local_66 = (uint8_t)(short)ROUND((float)tmp_pi3[7] * 255.0);
          local_50 = GHIDRA_FIELD(local_10c, 0, 1);
          local_58 = 0;
          local_54 = 0;
          local_78 = local_60 + local_e0 * tmp_f5;
          local_74 = local_5c + tmp_f5 * local_dc;
          local_64 = local_64 + local_e4 * tmp_f6;
          local_60 = local_60 + local_e0 * tmp_f6;
          local_5c = local_5c + tmp_f6 * local_dc;
          local_4c = local_e4 * tmp_f6 + local_34;
          local_48 = local_e0 * tmp_f6 + local_30;
          local_44 = tmp_f6 * local_dc + local_2c;
          local_34 = local_e4 * tmp_f5 + local_34;
          local_40 = 0;
          local_30 = local_e0 * tmp_f5 + local_30;
          local_38 = GHIDRA_FIELD(local_10c, 0, 1);
          local_3c = 0x3f800000;
          local_2c = tmp_f5 * local_dc + local_2c;
          local_20 = GHIDRA_FIELD(local_10c, 0, 1);
          local_28 = 0x3f800000;
          local_24 = 0x3f800000;
          local_4f = local_67;
          local_4e = local_66;
          local_4d = local_65;
          local_37 = local_67;
          local_36 = local_66;
          local_35 = local_65;
          local_1f = local_67;
          local_1e = local_66;
          local_1d = local_65;
          trap_R_AddPolyToScene(GHIDRA_FIELD(cgs, 68088, 4),4,&local_7c);
          goto LAB_00065320;
        }
        *(int *)(tmp_i12 + 0x260) = *(int *)(tmp_i12 + 0x260) + -1;
      }
      tmp_i12 = *tmp_pi3;
      if ((int *)tmp_pi3[1] == (int *)0x0) {
        tmp_pi13 = (int *)0x0;
        if (tmp_i12 != 0) goto LAB_00064f6e;
        lastusedsmokesprite = (int *)0x0;
        local_10c = (int *)0x0;
LAB_00064f78:
        if (((uint)tmp_pi3 & 1) == 0) goto LAB_00064f8b;
LAB_000654c0:
        tmp_u10 = 0x3b;
        tmp_b9 = true;
        *(uint8_t *)tmp_pi3 = 0;
        tmp_pi13 = (int *)((int)tmp_pi3 + 1);
      }
      else {
        *(int *)tmp_pi3[1] = tmp_i12;
        tmp_i12 = *tmp_pi3;
        tmp_pi13 = (int *)tmp_pi3[1];
        if (tmp_i12 != 0) {
LAB_00064f6e:
          *(int **)(tmp_i12 + 4) = tmp_pi13;
          local_10c = (int *)tmp_pi3[1];
          goto LAB_00064f78;
        }
        lastusedsmokesprite = tmp_pi13;
        if (tmp_pi13 == (int *)0x0) {
          local_10c = (int *)0x0;
          goto LAB_00064f78;
        }
        *tmp_pi13 = 0;
        local_10c = (int *)tmp_pi3[1];
        if (((uint)tmp_pi3 & 1) != 0) goto LAB_000654c0;
LAB_00064f8b:
        tmp_u10 = 0x3c;
        tmp_b9 = false;
        tmp_pi13 = tmp_pi3;
      }
      if (((uint)tmp_pi13 & 2) != 0) {
        *(uint16_t *)tmp_pi13 = 0;
        tmp_u10 = tmp_u10 - 2;
        tmp_pi13 = (int *)((int)tmp_pi13 + 2);
      }
      tmp_u8 = 0;
      do {
        *(uint32_t *)((int)tmp_pi13 + tmp_u8) = 0;
        *(uint32_t *)((int)tmp_pi13 + tmp_u8 + 4) = 0;
        tmp_u8 = tmp_u8 + 8;
      } while (tmp_u8 < (tmp_u10 & 0xfffffff8));
      tmp_pu11 = (uint32_t *)((int)tmp_pi13 + tmp_u8);
      if ((tmp_u10 & 4) == 0) goto LAB_00064fbc;
LAB_00065478:
      *tmp_pu11 = 0;
      tmp_pu11 = tmp_pu11 + 1;
      if ((tmp_u10 & 2) != 0) goto LAB_00065460;
LAB_00064fc5:
      if (tmp_b9) {
LAB_00065450:
        *(uint8_t *)tmp_pu11 = 0;
      }
    }
    else {
      if (24.0 <= tmp_f1) {
        tmp_pi3[2] = local_a8;
        tmp_pi3[3] = local_a4;
        tmp_pi3[4] = local_a0;
        goto LAB_00064f12;
      }
      if (tmp_pi3[0xe] != 0) {
        tmp_pi13 = (int *)(tmp_pi3[0xe] + 0x260);
        *tmp_pi13 = *tmp_pi13 + -1;
      }
      tmp_i12 = *tmp_pi3;
      if ((int *)tmp_pi3[1] == (int *)0x0) {
        tmp_pi13 = (int *)0x0;
        if (tmp_i12 != 0) goto LAB_00065357;
        lastusedsmokesprite = (int *)0x0;
        local_10c = (int *)0x0;
LAB_00065361:
        if (((uint)tmp_pi3 & 1) == 0) goto LAB_00065374;
LAB_000653f0:
        tmp_u10 = 0x3b;
        tmp_b9 = true;
        *(uint8_t *)tmp_pi3 = 0;
        tmp_pi13 = (int *)((int)tmp_pi3 + 1);
      }
      else {
        *(int *)tmp_pi3[1] = tmp_i12;
        tmp_i12 = *tmp_pi3;
        tmp_pi13 = (int *)tmp_pi3[1];
        if (tmp_i12 != 0) {
LAB_00065357:
          *(int **)(tmp_i12 + 4) = tmp_pi13;
          local_10c = (int *)tmp_pi3[1];
          goto LAB_00065361;
        }
        lastusedsmokesprite = tmp_pi13;
        if (tmp_pi13 == (int *)0x0) {
          local_10c = (int *)0x0;
          goto LAB_00065361;
        }
        *tmp_pi13 = 0;
        local_10c = (int *)tmp_pi3[1];
        if (((uint)tmp_pi3 & 1) != 0) goto LAB_000653f0;
LAB_00065374:
        tmp_u10 = 0x3c;
        tmp_b9 = false;
        tmp_pi13 = tmp_pi3;
      }
      if (((uint)tmp_pi13 & 2) != 0) {
        *(uint16_t *)tmp_pi13 = 0;
        tmp_u10 = tmp_u10 - 2;
        tmp_pi13 = (int *)((int)tmp_pi13 + 2);
      }
      tmp_u8 = 0;
      do {
        *(uint32_t *)((int)tmp_pi13 + tmp_u8) = 0;
        *(uint32_t *)((int)tmp_pi13 + tmp_u8 + 4) = 0;
        tmp_u8 = tmp_u8 + 8;
      } while (tmp_u8 < (tmp_u10 & 0xfffffff8));
      tmp_pu11 = (uint32_t *)((int)tmp_pi13 + tmp_u8);
      if ((tmp_u10 & 4) != 0) goto LAB_00065478;
LAB_00064fbc:
      if ((tmp_u10 & 2) == 0) goto LAB_00064fc5;
LAB_00065460:
      *(uint16_t *)tmp_pu11 = 0;
      tmp_pu11 = (uint32_t *)((int)tmp_pu11 + 2);
      if (tmp_b9) goto LAB_00065450;
    }
    SmokeSpriteCount = SmokeSpriteCount + -1;
    *tmp_pi3 = (int)firstfreesmokesprite;
    firstfreesmokesprite = tmp_pi3;
    tmp_pi3 = local_10c;
  } while( true );
}

void CG_EntityEffects(uint32_t *param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  size_t tmp_s4;
  int tmp_i5;
  uint tmp_u6;
  int tmp_i7;
  uint32_t tmp_u8;
  float tmp_f9;
  int local_4c;
  float local_28;
  float local_24;
  float local_20;
  
  if (param_1[0x2d] == 0xffffff) {
    tmp_i7 = param_1[0x29] * 0xc;
    local_28 = (float)param_1[0x1e5] + *(float *)(cgs + tmp_i7 + 0x880c);
    local_24 = (float)param_1[0x1e6] + *(float *)(cgs + tmp_i7 + 0x8810);
    local_20 = (float)param_1[0x1e7] + *(float *)(cgs + tmp_i7 + 0x8814);
    trap_S_UpdateEntityPosition(*param_1,&local_28);
  }
  else {
    trap_S_UpdateEntityPosition(*param_1,param_1 + 0x1e5);
  }
  tmp_i7 = param_1[0x28];
  if (tmp_i7 == 0) {
    if (param_1[0x99] != 0) {
      param_1[0x99] = 0;
    }
  }
  else {
    tmp_i3 = param_1[0x99];
    if (tmp_i3 == 0) {
      tmp_i3 = trap_S_GetCurrentSoundTime();
      tmp_i7 = param_1[0x28];
      param_1[0x99] = tmp_i3;
      tmp_i5 = param_1[1];
    }
    else {
      tmp_i5 = param_1[1];
    }
    if (tmp_i5 == 7) {
      tmp_i5 = param_1[0x3e];
      tmp_u8 = param_1[0x3f];
      if (tmp_i5 == 0) {
        tmp_u2 = CG_GetGameSound(tmp_i7);
        tmp_i5 = 0x4e2;
      }
      else {
        tmp_u2 = CG_GetGameSound(tmp_i7);
      }
      trap_S_AddRealLoopingSound(param_1 + 0x1e5,&vec3_origin,tmp_u2,tmp_i5,tmp_u8,tmp_i3);
    }
    else {
      if (tmp_i5 == 4) {
        tmp_u8 = param_1[0x3f];
        tmp_u2 = CG_GetGameSound(tmp_i7);
      }
      else {
        if (param_1[0x2d] == 0xffffff) {
          tmp_u8 = param_1[0x3f];
          tmp_i5 = param_1[0x29] * 0xc;
          local_28 = (float)param_1[0x1e5] + *(float *)(cgs + tmp_i5 + 0x880c);
          local_24 = (float)param_1[0x1e6] + *(float *)(cgs + tmp_i5 + 0x8810);
          local_20 = (float)param_1[0x1e7] + *(float *)(cgs + tmp_i5 + 0x8814);
          tmp_u2 = CG_GetGameSound(tmp_i7);
          trap_S_AddLoopingSound(&local_28,&vec3_origin,tmp_u2,tmp_u8,tmp_i3);
          goto LAB_0006696a;
        }
        tmp_u2 = CG_GetGameSound(tmp_i7);
        tmp_u8 = 0xff;
      }
      trap_S_AddLoopingSound(param_1 + 0x1e5,&vec3_origin,tmp_u2,tmp_u8,tmp_i3);
    }
  }
LAB_0006696a:
  tmp_i7 = g_unk_010906e0;
  if (param_1[1] == 0x26) {
    return;
  }
  if (param_1[1] == 1) {
    return;
  }
  tmp_u6 = param_1[0x26];
  if (tmp_u6 != 0) {
    if (*(char *)(param_1 + 0x1fc) == '\0') {
      trap_R_AddLightToScene
                (param_1 + 0x1e5,(float)((tmp_u6 >> 0x18) * 4),0x3f800000,
                 (float)(tmp_u6 & 0xff) / 255.0,(float)(tmp_u6 >> 8 & 0xff) / 255.0,
                 (float)((int)tmp_u6 >> 0x10 & 0xff) / 255.0,0,0);
    }
    else {
      tmp_i3 = g_unk_010906e0 - param_1[0x1fb];
      tmp_s4 = strlen((char *)(param_1 + 0x1fc));
      if (tmp_i3 < 0xc9) {
        tmp_i5 = param_1[0x1f9];
        param_1[0x1fb] = tmp_i7;
        tmp_f9 = (float)tmp_i3 / 100.0 + (float)param_1[0x1fa];
        param_1[0x1fa] = tmp_f9;
        if (tmp_f9 <= 1.0) goto LAB_000672b0;
        local_4c = (int)ROUND(tmp_f9);
        tmp_i5 = tmp_i5 + local_4c;
        tmp_i7 = tmp_i5 + 1;
        param_1[0x1f9] = tmp_i5;
        param_1[0x1f8] = tmp_i7;
        if ((((int)tmp_s4 <= tmp_i5) && (param_1[0x1f9] = tmp_i5 % (int)tmp_s4, tmp_i5 % (int)tmp_s4 < 3))
           && (param_1[0x20c] != 0)) {
          tmp_u8 = CG_GetGameSound(param_1[0x20c]);
          trap_S_StartSound(0,*param_1,0,tmp_u8);
          tmp_i7 = param_1[0x1f8];
          tmp_f9 = (float)param_1[0x1fa];
          local_4c = (int)ROUND(tmp_f9);
          tmp_u6 = param_1[0x26];
        }
        if ((int)tmp_s4 <= tmp_i7) {
          tmp_i7 = tmp_i7 % (int)tmp_s4;
          param_1[0x1f8] = tmp_i7;
        }
        tmp_i5 = param_1[0x1f9];
        tmp_f9 = tmp_f9 - (float)local_4c;
        param_1[0x1fa] = tmp_f9;
      }
      else {
        param_1[0x1f9] = 0;
        tmp_f9 = 0.0;
        param_1[0x1f8] = 0;
        param_1[0x1fa] = 0;
        param_1[0x1fb] = g_unk_010906e0;
        tmp_i5 = 0;
LAB_000672b0:
        tmp_i7 = param_1[0x1f8];
      }
      tmp_f9 = ((1.0 - tmp_f9) * (float)(*(char *)((int)param_1 + tmp_i5 + 0x7f0) + -0x61) +
              (float)(*(char *)((int)param_1 + tmp_i7 + 0x7f0) + -0x61) * tmp_f9) * 0.071429;
      if (tmp_f9 < 0.0) {
        tmp_f9 = 0.0;
      }
      else if (20.0 < tmp_f9) {
        tmp_f9 = 20.0;
      }
      if ((((float)param_1[0x1d] == 0.0) && ((float)param_1[0x1e] == 0.0)) &&
         ((float)param_1[0x1f] == 0.0)) {
        trap_R_AddLightToScene
                  (param_1 + 0x1e5,0x43800000,tmp_f9,(float)(tmp_u6 & 0xff) / 255.0,
                   (float)(tmp_u6 >> 8 & 0xff) / 255.0,(float)((int)tmp_u6 >> 0x10 & 0xff) / 255.0,0,0
                  );
      }
      else {
        AngleVectors(param_1 + 0x1d,&local_28,0,0);
        tmp_f1 = (float)(tmp_u6 & 0xff) / 255.0;
        trap_R_AddLightToScene(&local_28,0x43800000,tmp_f9,tmp_f1,tmp_f1,tmp_f1,0,0x20000000);
      }
    }
  }
  tmp_i7 = CG_EntOnFire(param_1);
  if (tmp_i7 != 0) {
    trap_S_AddLoopingSound
              (param_1 + 0x1e5,&vec3_origin,GHIDRA_FIELD(cgs, 69520, 4),
               (int)ROUND((1.0 - ABS((float)param_1[0x1f6])) * 255.0),0);
    trap_S_AddLoopingSound
              (param_1 + 0x1e5,&vec3_origin,GHIDRA_FIELD(cgs, 69516, 4),
               (int)ROUND((float)param_1[0x1f6] * (float)param_1[0x1f6] * 76.5),0);
  }
  tmp_u6 = param_1[2];
  if (((tmp_u6 & 0x2800) == 0x2800) && (GHIDRA_FIELD(cg_smokeparticles, 12, 4) != 0)) {
    if ((int)param_1[0x93] < g_unk_010906e0 + -3000) {
      param_1[0x93] = g_unk_010906e0;
    }
    tmp_i7 = rand();
    if (tmp_i7 == (tmp_i7 / 3) * 3) {
      tmp_i7 = CG_CalcMuzzlePoint(((int)(param_1 + -0xc4cf90) >> 3) * -0xbab6561,&local_28);
      if (tmp_i7 == 0) {
        local_28 = (float)param_1[0x1e5];
        local_24 = (float)param_1[0x1e6];
        local_20 = (float)param_1[0x1e7];
      }
      else {
        local_20 = local_20 - 40.0;
      }
      CG_ParticleImpactSmokePuffExtended
                (GHIDRA_FIELD(cgs, 68876, 4),&local_28,1000,8,0x14,0x1e,
                 (1.0 - (float)(g_unk_010906e0 - param_1[0x93]) / 3000.0) * 0.25,0x41000000);
    }
  }
  else if ((tmp_u6 & 0x2000) == 0) {
    if (((tmp_u6 & 0x800) != 0) && (tmp_u6 = rand(), (int)param_1[499] < g_unk_010906e0)) {
      param_1[499] = g_unk_010906e0 + 0x4b;
      CG_GetWindVector(&dir_11984);
      tmp_u8 = GHIDRA_FIELD(cgs, 68088, 4);
      tmp_i7 = g_unk_010906e0;
      dir_11984 = dir_11984 * 50.0;
      g_unk_002bb264 = g_unk_002bb264 * 50.0;
      g_unk_002bb268 = g_unk_002bb268 * 50.0;
      if (g_unk_002bb268 < 50.0) {
        g_unk_002bb268 = g_unk_002bb268 + 50.0;
      }
      tmp_i5 = rand();
      tmp_f9 = ((float)(tmp_u6 & 0x7fff) / 32767.0) * 0.1;
      tmp_u6 = rand();
      tmp_u2 = 0x3f800000;
      tmp_i3 = 0;
      tmp_i5 = tmp_i5 % 4000 + 0xaf0;
      tmp_f1 = ((float)(tmp_u6 & 0x7fff) / 32767.0) * 70.0 + 40.0;
LAB_00066f0f:
      CG_SmokePuff(param_1 + 0x1e5,&dir_11984,tmp_f1,tmp_f9,tmp_f9,tmp_f9,tmp_u2,(float)tmp_i5,tmp_i7,tmp_i3
                   ,0,tmp_u8);
      return;
    }
  }
  else {
    tmp_u6 = rand();
    if ((int)param_1[499] < g_unk_010906e0) {
      param_1[499] = g_unk_010906e0 + 100;
      CG_GetWindVector(&dir_11984);
      tmp_u8 = GHIDRA_FIELD(cgs, 68088, 4);
      tmp_i7 = g_unk_010906e0;
      dir_11984 = dir_11984 * 20.0;
      g_unk_002bb264 = g_unk_002bb264 * 20.0;
      g_unk_002bb268 = g_unk_002bb268 * 20.0;
      if (g_unk_002bb268 < 10.0) {
        g_unk_002bb268 = g_unk_002bb268 + 10.0;
      }
      tmp_i5 = rand();
      tmp_f9 = (float)(tmp_u6 & 0x7fff) / 32767.0 + 0.3;
      tmp_u6 = rand();
      tmp_u2 = 0x3ecccccd;
      tmp_i3 = tmp_i7 + 500;
      tmp_i5 = tmp_i5 % 500 + 0x5dc;
      tmp_f1 = ((float)(tmp_u6 & 0x7fff) / 32767.0) * 10.0 + 15.0;
      goto LAB_00066f0f;
    }
  }
  return;
}

void CG_PositionRotatedEntityOnTag(int param_1,int param_2,uint32_t param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint8_t local_70 [36];
  float local_4c;
  float local_48;
  float local_44;
  uint8_t local_40 [48];
  
  trap_R_LerpTag(&local_4c,param_2,param_3,0);
  tmp_f1 = *(float *)(param_2 + 0x68);
  *(float *)(param_1 + 0x68) = tmp_f1;
  tmp_f2 = *(float *)(param_2 + 0x6c);
  *(float *)(param_1 + 0x6c) = tmp_f2;
  tmp_f3 = *(float *)(param_2 + 0x70);
  *(float *)(param_1 + 0x70) = tmp_f3;
  tmp_f1 = *(float *)(param_2 + 0x1c) * local_4c + tmp_f1;
  *(float *)(param_1 + 0x68) = tmp_f1;
  tmp_f2 = *(float *)(param_2 + 0x20) * local_4c + tmp_f2;
  *(float *)(param_1 + 0x6c) = tmp_f2;
  tmp_f3 = local_4c * *(float *)(param_2 + 0x24) + tmp_f3;
  *(float *)(param_1 + 0x70) = tmp_f3;
  tmp_f1 = *(float *)(param_2 + 0x28) * local_48 + tmp_f1;
  *(float *)(param_1 + 0x68) = tmp_f1;
  tmp_f2 = *(float *)(param_2 + 0x2c) * local_48 + tmp_f2;
  *(float *)(param_1 + 0x6c) = tmp_f2;
  tmp_f3 = local_48 * *(float *)(param_2 + 0x30) + tmp_f3;
  *(float *)(param_1 + 0x70) = tmp_f3;
  *(float *)(param_1 + 0x68) = *(float *)(param_2 + 0x34) * local_44 + tmp_f1;
  *(float *)(param_1 + 0x6c) = *(float *)(param_2 + 0x38) * local_44 + tmp_f2;
  *(float *)(param_1 + 0x70) = local_44 * *(float *)(param_2 + 0x3c) + tmp_f3;
  MatrixMultiply(param_1 + 0x1c,local_40,local_70);
  MatrixMultiply(local_70,(float *)(param_2 + 0x1c),param_1 + 0x1c);
  return;
}

void CG_AddLightstyle(uint32_t *param_1)
{
  float tmp_f1;
  uint tmp_u2;
  float tmp_f3;
  int tmp_i4;
  size_t tmp_s5;
  int tmp_i6;
  uint32_t tmp_u7;
  int tmp_i8;
  int local_40;
  uint8_t local_28 [24];
  
  tmp_i8 = g_unk_010906e0;
  if (*(char *)(param_1 + 0x1fc) == '\0') {
    return;
  }
  tmp_i4 = g_unk_010906e0 - param_1[0x1fb];
  tmp_s5 = strlen((char *)(param_1 + 0x1fc));
  if (tmp_i4 < 0xc9) {
    tmp_i6 = param_1[0x1f9];
    param_1[0x1fb] = tmp_i8;
    tmp_f1 = (float)tmp_i4 / 100.0 + (float)param_1[0x1fa];
    param_1[0x1fa] = tmp_f1;
    if (1.0 < tmp_f1) {
      local_40 = (int)ROUND(tmp_f1);
      tmp_i6 = tmp_i6 + local_40;
      tmp_i8 = tmp_i6 + 1;
      param_1[0x1f9] = tmp_i6;
      param_1[0x1f8] = tmp_i8;
      if ((((int)tmp_s5 <= tmp_i6) && (param_1[0x1f9] = tmp_i6 % (int)tmp_s5, tmp_i6 % (int)tmp_s5 < 3))
         && (param_1[0x20c] != 0)) {
        tmp_u7 = CG_GetGameSound(param_1[0x20c]);
        trap_S_StartSound(0,*param_1,0,tmp_u7);
        tmp_i8 = param_1[0x1f8];
        tmp_f1 = (float)param_1[0x1fa];
        local_40 = (int)ROUND(tmp_f1);
      }
      if ((int)tmp_s5 <= tmp_i8) {
        tmp_i8 = tmp_i8 % (int)tmp_s5;
        param_1[0x1f8] = tmp_i8;
      }
      tmp_i6 = param_1[0x1f9];
      tmp_f1 = tmp_f1 - (float)local_40;
      param_1[0x1fa] = tmp_f1;
      goto LAB_00067af4;
    }
  }
  else {
    param_1[0x1f9] = 0;
    tmp_f1 = 0.0;
    param_1[0x1f8] = 0;
    param_1[0x1fa] = 0;
    param_1[0x1fb] = g_unk_010906e0;
    tmp_i6 = 0;
  }
  tmp_i8 = param_1[0x1f8];
LAB_00067af4:
  tmp_f1 = ((1.0 - tmp_f1) * (float)(*(char *)((int)param_1 + tmp_i6 + 0x7f0) + -0x61) +
          (float)(*(char *)((int)param_1 + tmp_i8 + 0x7f0) + -0x61) * tmp_f1) * 0.071429;
  if (tmp_f1 < 0.0) {
    tmp_f1 = 0.0;
  }
  else if (20.0 < tmp_f1) {
    tmp_f1 = 20.0;
  }
  tmp_u2 = param_1[0x26];
  if ((((float)param_1[0x1d] == 0.0) && ((float)param_1[0x1e] == 0.0)) &&
     ((float)param_1[0x1f] == 0.0)) {
    trap_R_AddLightToScene
              (param_1 + 0x1e5,0x43800000,tmp_f1,(float)(tmp_u2 & 0xff) / 255.0,
               (float)(tmp_u2 >> 8 & 0xff) / 255.0,(float)((int)tmp_u2 >> 0x10 & 0xff) / 255.0,0,0);
  }
  else {
    AngleVectors(param_1 + 0x1d,local_28,0,0);
    tmp_f3 = (float)(tmp_u2 & 0xff) / 255.0;
    trap_R_AddLightToScene(local_28,0x43800000,tmp_f1,tmp_f3,tmp_f3,tmp_f3,0,0x20000000);
  }
  return;
}

void CG_Item(int param_1)
{
  uint tmp_u1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  char *tmp_pc5;
  int tmp_i6;
  int tmp_i7;
  uint tmp_u8;
  float local_230;
  float local_22c;
  float local_228;
  float local_224;
  float local_220;
  float local_21c;
  uint8_t local_218 [36];
  uint local_1f4 [7];
  float local_1d8;
  float local_1d4;
  float local_1d0;
  float local_1cc;
  float local_1c8;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  uint32_t local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_170;
  float local_16c;
  float local_168;
  int local_148;
  uint32_t local_144;
  float local_114;
  float local_108 [7];
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_a0;
  float local_9c;
  float local_98;
  
  tmp_i6 = *(int *)(param_1 + 0xa4);
  if (bg_numItems <= tmp_i6) {
    CG_Error("Bad item index %i on entity",tmp_i6);
    tmp_i6 = *(int *)(param_1 + 0xa4);
  }
  if (tmp_i6 == 0) {
    return;
  }
  tmp_u1 = *(uint *)(param_1 + 8);
  if ((tmp_u1 & 0x40) != 0) {
    return;
  }
  tmp_u8 = 0;
  do {
    *(uint32_t *)((int)local_1f4 + tmp_u8) = 0;
    *(uint32_t *)((int)local_1f4 + tmp_u8 + 4) = 0;
    tmp_u8 = tmp_u8 + 8;
  } while (tmp_u8 < 0xe8);
  *(uint32_t *)((int)local_1f4 + tmp_u8) = 0;
  if (*(int *)(bg_itemlist + tmp_i6 * 0x38 + 0x24) == 1) {
    tmp_f2 = *(float *)(cg_weapons + *(int *)(bg_itemlist + tmp_i6 * 0x38 + 0x28) * 0x17ac + 0x5b8);
    if (tmp_f2 == 0.0) {
      if ((*(int *)(cg_weapons + *(int *)(bg_itemlist + tmp_i6 * 0x38 + 0x28) * 0x17ac + 0x5bc) != 0)
         && ((*(int *)(param_1 + 0xc) == 9 || (*(int *)(param_1 + 0xc) == 0)))) {
        *(float *)(param_1 + 0x7a8) = *(float *)(param_1 + 0x7a8) + 90.0;
      }
      AnglesToAxis(param_1 + 0x7a0,&local_1d8);
      local_190 = 1;
      local_1d8 = local_1d8 * 1.5;
      local_1d4 = local_1d4 * 1.5;
      local_1d0 = local_1d0 * 1.5;
      local_1cc = local_1cc * 1.5;
      local_1c8 = local_1c8 * 1.5;
      local_1c4 = local_1c4 * 1.5;
      local_1c0 = local_1c0 * 1.5;
      local_1bc = local_1bc * 1.5;
      local_1b8 = local_1b8 * 1.5;
      local_18c = *(float *)(param_1 + 0x794);
      local_188 = *(float *)(param_1 + 0x798);
      local_184 = *(float *)(param_1 + 0x79c);
      local_170 = local_18c;
      local_16c = local_188;
      local_168 = local_184;
      if ((*(byte *)(param_1 + 9) & 1) != 0) {
        if (*(int *)(param_1 + 0x94) + 1U < 2) {
          *(uint32_t *)(param_1 + 0x7a0) = g_unk_01091818;
          *(uint32_t *)(param_1 + 0x7a4) = g_unk_0109181c;
          *(uint32_t *)(param_1 + 0x7a8) = g_unk_01091820;
          *(uint32_t *)(param_1 + 0x7ac) = g_unk_01091818;
          *(uint32_t *)(param_1 + 0x7b0) = g_unk_0109181c;
          *(uint32_t *)(param_1 + 0x7b4) = g_unk_01091820;
        }
        else {
          *(uint32_t *)(param_1 + 0x7a0) = *(uint32_t *)(param_1 + 0x7ac);
          *(uint32_t *)(param_1 + 0x7a4) = *(uint32_t *)(param_1 + 0x7b0);
          *(uint32_t *)(param_1 + 0x7a8) = *(uint32_t *)(param_1 + 0x7b4);
        }
      }
    }
    else {
      tmp_u8 = 0;
      do {
        *(uint32_t *)((int)local_108 + tmp_u8) = 0;
        *(uint32_t *)((int)local_108 + tmp_u8 + 4) = 0;
        tmp_u8 = tmp_u8 + 8;
      } while (tmp_u8 < 0xe8);
      *(uint32_t *)((int)local_108 + tmp_u8) = 0;
      if ((tmp_u1 & 0x100) != 0) {
        if (*(int *)(param_1 + 0x94) + 1U < 2) {
          *(uint32_t *)(param_1 + 0x7a0) = g_unk_01091818;
          *(uint32_t *)(param_1 + 0x7a4) = g_unk_0109181c;
          *(uint32_t *)(param_1 + 0x7a8) = g_unk_01091820;
          *(uint32_t *)(param_1 + 0x7ac) = g_unk_01091818;
          *(uint32_t *)(param_1 + 0x7b0) = g_unk_0109181c;
          *(uint32_t *)(param_1 + 0x7b4) = g_unk_01091820;
        }
        else {
          *(uint32_t *)(param_1 + 0x7a0) = *(uint32_t *)(param_1 + 0x7ac);
          *(uint32_t *)(param_1 + 0x7a4) = *(uint32_t *)(param_1 + 0x7b0);
          *(uint32_t *)(param_1 + 0x7a8) = *(uint32_t *)(param_1 + 0x7b4);
        }
      }
      local_108[2] = tmp_f2;
      AnglesToAxis(param_1 + 0x7a0,&local_ec);
      local_a0 = *(float *)(param_1 + 0x794);
      local_9c = *(float *)(param_1 + 0x798);
      local_98 = *(float *)(param_1 + 0x79c);
      local_ec = local_ec * 1.5;
      local_e8 = local_e8 * 1.5;
      local_e4 = local_e4 * 1.5;
      local_e0 = local_e0 * 1.5;
      local_dc = local_dc * 1.5;
      local_d8 = local_d8 * 1.5;
      local_d4 = local_d4 * 1.5;
      local_d0 = local_d0 * 1.5;
      local_cc = local_cc * 1.5;
      if (*(int *)(param_1 + 0xb0) == 0) {
        tmp_pc5 = "tag_stand";
      }
      else {
        tmp_pc5 = (char *)va("tag_stand%d",*(int *)(param_1 + 0xb0));
      }
      trap_R_LerpTag(&local_224,local_108,tmp_pc5,0);
      local_188 = local_e8 * local_224 + local_9c + local_dc * local_220 + local_d0 * local_21c;
      local_184 = local_e4 * local_224 + local_98 + local_d8 * local_220 + local_cc * local_21c;
      local_18c = local_a0 + local_224 * local_ec + local_e0 * local_220 + local_21c * local_d4;
      MatrixMultiply(local_218,&local_ec,&local_1d8);
      local_190 = 1;
      local_170 = local_18c;
      local_16c = local_188;
      local_168 = local_184;
    }
  }
  else {
    AnglesToAxis(param_1 + 0x7a0,&local_1d8);
    local_18c = *(float *)(param_1 + 0x794);
    local_188 = *(float *)(param_1 + 0x798);
    local_184 = *(float *)(param_1 + 0x79c);
    local_170 = local_18c;
    local_16c = local_188;
    local_168 = local_184;
    if ((*(byte *)(param_1 + 9) & 1) != 0) {
      *(uint32_t *)(param_1 + 0x7a0) = g_unk_01091818;
      *(uint32_t *)(param_1 + 0x7a4) = g_unk_0109181c;
      *(uint32_t *)(param_1 + 0x7a8) = g_unk_01091820;
      AxisCopy(&g_unk_01091824,&local_1d8);
    }
  }
  if (*(int *)(param_1 + 0xa8) != 0) {
    local_1f4[2] = CG_GetGameModel(*(int *)(param_1 + 0xa8));
    goto LAB_0006823f;
  }
  tmp_i4 = tmp_i6 * 0x38;
  tmp_i7 = *(int *)(bg_itemlist + tmp_i4 + 0x24);
  tmp_i3 = *(int *)(bg_itemlist + tmp_i4 + 0x28);
  if ((tmp_i7 == 1) || (tmp_i3 == 0x12)) {
    if (*(int *)(param_1 + 0x108) == 1) {
      local_1f4[2] = *(uint *)(cg_weapons + tmp_i3 * 0x17ac + 0x5f4);
      if (local_1f4[2] == 0) {
        local_1f4[2] = *(uint *)(cg_weapons + tmp_i3 * 0x17ac + 0x5f0);
      }
      local_148 = *(int *)(cg_weapons + tmp_i3 * 0x17ac + 0x600);
      if (local_148 == 0) goto LAB_00068411;
    }
    else {
      tmp_i7 = tmp_i3 * 0x17ac;
      if (*(int *)(param_1 + 0x108) == 2) {
        local_1f4[2] = *(uint *)(cg_weapons + tmp_i7 + 0x5f8);
        if (local_1f4[2] == 0) {
          local_1f4[2] = *(uint *)(cg_weapons + tmp_i7 + 0x5f0);
        }
        local_148 = *(int *)(cg_weapons + tmp_i3 * 0x17ac + 0x604);
        if (local_148 != 0) goto LAB_00068420;
      }
      else {
        local_1f4[2] = *(uint *)(cg_weapons + tmp_i7 + 0x5f0);
      }
LAB_00068411:
      local_148 = *(int *)(cg_weapons + tmp_i3 * 0x17ac + 0x5fc);
    }
LAB_00068420:
    if ((tmp_i3 == 0xc) && (*(int *)(param_1 + 0xf4) == 2)) {
      local_144 = GHIDRA_FIELD(cg_weapons, 78500, 4);
    }
  }
  else if (tmp_i7 - 2U < 2) {
    if (0x1ff < *(int *)(param_1 + 0xf4)) goto LAB_00068227;
    local_1f4[2] = (&g_unk_010202a4)[*(int *)(param_1 + 0xf4) + *(int *)(param_1 + 0xa4) * 8];
  }
  else if ((tmp_i7 == 6) &&
          (((*(int *)(bg_itemlist + tmp_i4 + 0x2c) == 3 ||
            (*(int *)(bg_itemlist + tmp_i4 + 0x2c) == 0xc)) &&
           (tmp_i7 = CG_CharacterForPlayerstate(g_unk_01047b00 + 0x2c), tmp_i7 != 0)))) {
    local_1f4[2] = *(int *)(tmp_i7 + 0x60);
    local_148 = *(int *)(tmp_i7 + 0x8c);
    local_18c = local_1c0 * -4.0 + local_18c;
    local_188 = local_1bc * -4.0 + local_188;
    local_184 = local_1b8 * -4.0 + local_184;
  }
  else {
LAB_00068227:
    local_1f4[2] = (&g_unk_010202a4)[*(int *)(param_1 + 0xa4) * 8];
  }
LAB_0006823f:
  if (*(int *)(param_1 + 0x898) == 0) {
    trap_R_ModelBounds(local_1f4[2],&local_230,&local_224);
    local_108[0] = (local_224 - local_230) * 0.5 + local_230;
    local_108[1] = (local_220 - local_22c) * 0.5 + local_22c;
    local_108[2] = (local_21c - local_228) * 0.5 + local_228;
    *(float *)(param_1 + 0x88c) =
         local_1c0 * local_108[2] + local_1cc * local_108[1] + local_1d8 * local_108[0] +
         *(float *)(param_1 + 0x794);
    *(float *)(param_1 + 0x890) =
         local_1bc * local_108[2] + local_1c8 * local_108[1] + local_1d4 * local_108[0] +
         *(float *)(param_1 + 0x798);
    *(float *)(param_1 + 0x894) =
         local_108[2] * local_1b8 + local_108[1] * local_1c4 + local_108[0] * local_1d0 +
         *(float *)(param_1 + 0x79c);
    *(uint32_t *)(param_1 + 0x898) = 1;
  }
  local_1f4[1] = local_1f4[1] | 1;
  if (GHIDRA_FIELD(cg_drawCrosshairPickups, 12, 4) == 0) goto LAB_00068320;
  if (GHIDRA_FIELD(cg_drawCrosshairPickups, 12, 4) == 2) {
    CG_PlayerSeesItem(&g_unk_010906fc,param_1,g_unk_010906e0,
                      *(uint32_t *)(bg_itemlist + tmp_i6 * 0x38 + 0x24));
LAB_000684ac:
    if (*(int *)(param_1 + 0x998) == 0) {
      *(uint32_t *)(param_1 + 0x998) = 1;
      tmp_i6 = g_unk_010906e0;
      *(int *)(param_1 + 0x994) = g_unk_010906e0;
    }
    else {
      tmp_i6 = *(int *)(param_1 + 0x994);
    }
    local_114 = (float)(g_unk_010906e0 - tmp_i6) / 250.0;
  }
  else {
    tmp_i6 = CG_PlayerSeesItem(&g_unk_010906fc,param_1,g_unk_010906e0,
                              *(uint32_t *)(bg_itemlist + tmp_i6 * 0x38 + 0x24));
    if (tmp_i6 != 0) goto LAB_000684ac;
    if (*(int *)(param_1 + 0x998) == 0) {
      tmp_i6 = *(int *)(param_1 + 0x994);
    }
    else {
      *(uint32_t *)(param_1 + 0x998) = 0;
      tmp_i6 = g_unk_010906e0;
      *(int *)(param_1 + 0x994) = g_unk_010906e0;
    }
    local_114 = 1.0 - (float)(g_unk_010906e0 - tmp_i6) / 1000.0;
  }
  if (0.25 <= local_114) {
    if (1.0 < local_114) {
      local_114 = 1.0;
    }
  }
  else {
    local_114 = 0.25;
  }
LAB_00068320:
  trap_R_AddRefEntityToScene(local_1f4);
  return;
}

void CG_Beam_2(int param_1)
{
  uint tmp_u1;
  uint32_t local_110;
  uint32_t local_10c;
  uint32_t local_108;
  uint32_t local_104;
  uint32_t local_100;
  uint32_t local_fc;
  uint32_t local_f8 [7];
  uint8_t local_dc [76];
  uint32_t local_90;
  uint32_t local_8c;
  uint32_t local_88;
  uint32_t local_84;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_48;
  uint8_t local_44;
  uint8_t local_43;
  uint8_t local_42;
  uint8_t local_41;
  uint32_t local_34;
  
  BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0,&local_110,0,*(uint32_t *)(param_1 + 0x10c));
  BG_EvaluateTrajectory(param_1 + 0x30,g_unk_010906e0,&local_104,0,*(uint32_t *)(param_1 + 0x110));
  tmp_u1 = 0;
  do {
    *(uint32_t *)((int)local_f8 + tmp_u1) = 0;
    *(uint32_t *)((int)local_f8 + tmp_u1 + 4) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0xe8);
  *(uint32_t *)((int)local_f8 + tmp_u1) = 0;
  local_90 = local_110;
  local_8c = local_10c;
  local_88 = local_108;
  local_74 = local_104;
  local_70 = local_100;
  local_6c = local_fc;
  AxisClear(local_dc);
  local_f8[0] = 5;
  local_34 = 0x41000000;
  local_41 = 0xff;
  local_48 = *(uint32_t *)(cgs + *(int *)(param_1 + 0xa8) * 4 + 0x7b48);
  local_84 = 2;
  local_44 = (uint8_t)(short)ROUND(*(float *)(param_1 + 0x80) * 255.0);
  local_43 = (uint8_t)(short)ROUND(*(float *)(param_1 + 0x84) * 255.0);
  local_42 = (uint8_t)(short)ROUND(*(float *)(param_1 + 0x88) * 255.0);
  trap_R_AddRefEntityToScene(local_f8);
  return;
}

void CG_Beam(int param_1)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  uint32_t local_f8 [7];
  uint8_t local_dc [76];
  uint32_t local_90;
  uint32_t local_8c;
  uint32_t local_88;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_48;
  uint8_t local_44;
  uint8_t local_43;
  uint8_t local_42;
  uint8_t local_41;
  
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)local_f8 + tmp_u2) = 0;
    *(uint32_t *)((int)local_f8 + tmp_u2 + 4) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0xe8);
  tmp_u1 = *(uint32_t *)(param_1 + 0x18);
  *(uint32_t *)((int)local_f8 + tmp_u2) = 0;
  local_8c = *(uint32_t *)(param_1 + 0x1c);
  local_88 = *(uint32_t *)(param_1 + 0x20);
  local_74 = *(uint32_t *)(param_1 + 0x68);
  local_70 = *(uint32_t *)(param_1 + 0x6c);
  local_6c = *(uint32_t *)(param_1 + 0x70);
  local_90 = tmp_u1;
  AxisClear(local_dc);
  local_f8[0] = 5;
  if (*(int *)(param_1 + 0xec) == 1) {
    local_48 = GHIDRA_FIELD(cgs, 67960, 4);
  }
  else {
    local_48 = GHIDRA_FIELD(cgs, 67956, 4);
  }
  local_f8[1] = 0x10;
  local_44 = (uint8_t)(short)ROUND(*(float *)(param_1 + 0x80) * 255.0);
  local_43 = (uint8_t)(short)ROUND(*(float *)(param_1 + 0x84) * 255.0);
  local_42 = (uint8_t)(short)ROUND(*(float *)(param_1 + 0x88) * 255.0);
  local_41 = 0xff;
  trap_R_AddRefEntityToScene(local_f8);
  return;
}

uint32_t CG_AddLinkedEntity(int param_1,int param_2,int param_3)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  float tmp_f6;
  float tmp_f7;
  int local_44;
  float local_28;
  float local_24;
  float local_20;
  
  if (0x3a < *(uint *)(param_1 + 4)) {
    return 1;
  }
  if (param_2 == 0) {
    if ((*(int *)(param_1 + 0x988) == cg) && (g_unk_010ee058 == 0)) {
      return 1;
    }
    tmp_i5 = *(int *)(param_1 + 0xf0);
    tmp_i3 = tmp_i5 * 0xaf8;
    if (*(int *)(cg_entities + tmp_i3 + 0x244) == 0) {
      return 0;
    }
    if ((cg == *(int *)(cg_entities + tmp_i3 + 0x988)) || ((cg_entities[tmp_i3 + 10] & 2) == 0)) {
LAB_0006a5a8:
      *(int *)(param_1 + 0x988) = cg;
    }
    else {
LAB_0006a7e8:
      tmp_i3 = CG_AddLinkedEntity(cg_entities + tmp_i3,param_2,param_3);
      if (tmp_i3 == 0) {
        return 0;
      }
      if (param_2 == 0) goto LAB_0006a5a8;
    }
    tmp_i3 = tmp_i5 * 0xaf8;
    if ((cg_entities[tmp_i3 + 10] & 2) == 0) goto LAB_0006a74d;
    if (*(int *)(cg_entities + tmp_i3 + 0x9b4) == 0) {
      *(uint32_t *)(param_1 + 0x9b4) = 0;
      *(uint32_t *)(param_1 + 0x794) = *(uint32_t *)(param_1 + 0x18);
      *(uint32_t *)(param_1 + 0x798) = *(uint32_t *)(param_1 + 0x1c);
      *(uint32_t *)(param_1 + 0x79c) = *(uint32_t *)(param_1 + 0x20);
      *(uint32_t *)(param_1 + 0x7a0) = *(uint32_t *)(param_1 + 0x3c);
      *(uint32_t *)(param_1 + 0x7a4) = *(uint32_t *)(param_1 + 0x40);
      *(uint32_t *)(param_1 + 0x7a8) = *(uint32_t *)(param_1 + 0x44);
      goto LAB_0006a79e;
    }
    local_28 = *(float *)(cg_entities + tmp_i3 + 0x99c);
    tmp_u2 = *(uint32_t *)(cg_entities + tmp_i3 + 0x9b0);
    local_24 = *(float *)(cg_entities + tmp_i3 + 0x9a0);
    local_20 = *(float *)(cg_entities + tmp_i3 + 0x9a4);
    *(uint32_t *)(param_1 + 0x9b0) = tmp_u2;
    *(uint32_t *)(param_1 + 0x9ac) = *(uint32_t *)(cg_entities + tmp_i3 + 0x9ac);
    tmp_i5 = *(int *)(cg_entities + tmp_i3 + 0x9a8);
    *(float *)(param_1 + 0x794) = local_28;
    *(float *)(param_1 + 0x798) = local_24;
    *(float *)(param_1 + 0x79c) = local_20;
    tmp_f1 = *(float *)(param_1 + 0x80);
    *(int *)(param_1 + 0x9a8) = tmp_i5;
    if ((tmp_f1 != 0.0) && (tmp_i5 != 0)) {
      BG_LinearPathOrigin2(tmp_f1,param_1 + 0x9a8,param_1 + 0x9ac,&local_28,tmp_u2);
      tmp_f1 = *(float *)(param_1 + 0x80);
    }
    *(float *)(param_1 + 0x99c) = local_28;
    *(float *)(param_1 + 0x9a0) = local_24;
    *(float *)(param_1 + 0x9a4) = local_20;
    if (0.0 <= tmp_f1) {
      if (tmp_f1 <= 0.0) goto LAB_0006a890;
      local_28 = *(float *)(param_1 + 0x794) - local_28;
      local_24 = *(float *)(param_1 + 0x798) - local_24;
      goto LAB_0006a6e6;
    }
    local_28 = local_28 - *(float *)(param_1 + 0x794);
    local_24 = local_24 - *(float *)(param_1 + 0x798);
    local_20 = local_20 - *(float *)(param_1 + 0x79c);
LAB_0006a6ec:
    vectoangles(&local_28,param_1 + 0x7a0);
  }
  else {
    tmp_i5 = *(int *)(param_1 + 0xf0);
    tmp_i3 = tmp_i5 * 0xaf8;
    if (*(int *)(cg_entities + tmp_i3 + 0x244) == 0) {
      return 0;
    }
    if ((cg_entities[tmp_i3 + 10] & 2) != 0) goto LAB_0006a7e8;
LAB_0006a74d:
    tmp_i3 = tmp_i5 * 0xaf8;
    if (*(int *)(cg_entities + tmp_i3 + 0xc) != 0xd) {
      *(uint32_t *)(param_1 + 0x9b4) = 0;
      *(uint32_t *)(param_1 + 0x794) = *(uint32_t *)(param_1 + 0x18);
      *(uint32_t *)(param_1 + 0x798) = *(uint32_t *)(param_1 + 0x1c);
      *(uint32_t *)(param_1 + 0x79c) = *(uint32_t *)(param_1 + 0x20);
      *(uint32_t *)(param_1 + 0x7a0) = *(uint32_t *)(param_1 + 0x3c);
      *(uint32_t *)(param_1 + 0x7a4) = *(uint32_t *)(param_1 + 0x40);
      *(uint32_t *)(param_1 + 0x7a8) = *(uint32_t *)(param_1 + 0x44);
      goto LAB_0006a79e;
    }
    tmp_i4 = BG_GetSplineData(*(uint32_t *)(cg_entities + tmp_i3 + 0x110),param_1 + 0x9b0);
    *(int *)(param_1 + 0x9a8) = tmp_i4;
    if (tmp_i4 == 0) {
      return 0;
    }
    if (*(int *)(cg_entities + tmp_i3 + 0x14) == 0) {
      *(uint32_t *)(param_1 + 0x9ac) = 0;
      tmp_f1 = 0.0;
LAB_0006aa81:
      local_44 = *(int *)(param_1 + 0x9b0);
      if (local_44 == 0) {
        tmp_f1 = tmp_f1 * 16.0;
        tmp_f6 = floorf(tmp_f1);
        tmp_i3 = (int)ROUND(tmp_f6);
      }
      else {
        tmp_f6 = 1.0 - tmp_f1;
        tmp_f1 = tmp_f6 * 16.0;
        tmp_f7 = floorf(tmp_f1);
        tmp_i3 = (int)ROUND(tmp_f7);
LAB_0006a945:
        *(float *)(param_1 + 0x9ac) = tmp_f6;
      }
      if (0xf < tmp_i3) goto LAB_0006a956;
LAB_0006aafa:
      tmp_f1 = (tmp_f1 - (float)tmp_i3) * *(float *)(tmp_i4 + 0x1e0 + tmp_i3 * 0x1c);
    }
    else {
      tmp_f1 = (float)(param_3 - *(int *)(cg_entities + tmp_i3 + 0x10)) /
              (float)*(int *)(cg_entities + tmp_i3 + 0x14);
      if (tmp_f1 < 0.0) {
        local_44 = *(int *)(param_1 + 0x9b0);
        *(uint32_t *)(param_1 + 0x9ac) = 0;
        if (local_44 != 0) {
          tmp_f1 = 16.0;
          tmp_i3 = 0x10;
          tmp_f6 = 1.0;
          goto LAB_0006a945;
        }
        tmp_f1 = 0.0;
        tmp_i3 = 0;
        goto LAB_0006aafa;
      }
      if (tmp_f1 <= 1.0) {
        *(float *)(param_1 + 0x9ac) = tmp_f1;
        goto LAB_0006aa81;
      }
      local_44 = *(int *)(param_1 + 0x9b0);
      *(uint32_t *)(param_1 + 0x9ac) = 0x3f800000;
      if (local_44 != 0) {
        tmp_f1 = 0.0;
        tmp_i3 = 0;
        tmp_f6 = tmp_f1;
        goto LAB_0006a945;
      }
LAB_0006a956:
      tmp_f1 = *(float *)(tmp_i4 + 900);
      tmp_i3 = 0xf;
    }
    tmp_i3 = tmp_i3 * 0x1c;
    local_28 = *(float *)(tmp_i4 + 0x1d4 + tmp_i3) * tmp_f1 + *(float *)(tmp_i4 + 0x1c8 + tmp_i3);
    local_24 = *(float *)(tmp_i4 + 0x1d8 + tmp_i3) * tmp_f1 + *(float *)(tmp_i4 + 0x1cc + tmp_i3);
    local_20 = tmp_f1 * *(float *)(tmp_i4 + 0x1dc + tmp_i3) + *(float *)(tmp_i4 + 0x1d0 + tmp_i3);
    if (*(float *)(cg_entities + tmp_i5 * 0xaf8 + 0x3c) != 0.0) {
      BG_LinearPathOrigin2
                (*(float *)(cg_entities + tmp_i5 * 0xaf8 + 0x3c),param_1 + 0x9a8,param_1 + 0x9ac,
                 &local_28,local_44);
    }
    *(float *)(param_1 + 0x794) = local_28;
    *(float *)(param_1 + 0x798) = local_24;
    *(float *)(param_1 + 0x79c) = local_20;
    tmp_f1 = *(float *)(param_1 + 0x80);
    if (tmp_f1 != 0.0) {
      BG_LinearPathOrigin2
                (tmp_f1,param_1 + 0x9a8,param_1 + 0x9ac,&local_28,*(uint32_t *)(param_1 + 0x9b0));
      tmp_f1 = *(float *)(param_1 + 0x80);
    }
    *(float *)(param_1 + 0x99c) = local_28;
    *(float *)(param_1 + 0x9a0) = local_24;
    *(float *)(param_1 + 0x9a4) = local_20;
    if (tmp_f1 < 0.0) {
      local_28 = local_28 - *(float *)(param_1 + 0x794);
      local_24 = local_24 - *(float *)(param_1 + 0x798);
      local_20 = local_20 - *(float *)(param_1 + 0x79c);
      goto LAB_0006a6ec;
    }
    if (0.0 < tmp_f1) {
      local_28 = *(float *)(param_1 + 0x794) - local_28;
      local_24 = *(float *)(param_1 + 0x798) - local_24;
LAB_0006a6e6:
      local_20 = *(float *)(param_1 + 0x79c) - local_20;
      goto LAB_0006a6ec;
    }
LAB_0006a890:
    *(uint32_t *)(param_1 + 0x7a8) = 0;
    *(uint32_t *)(param_1 + 0x7a4) = 0;
    *(uint32_t *)(param_1 + 0x7a0) = 0;
  }
  *(uint32_t *)(param_1 + 0x9b4) = 1;
LAB_0006a79e:
  if (param_2 == 0) {
    CG_EntityEffects();
    CG_ProcessEntity();
  }
  return 1;
}

void CG_AdjustPositionForMover
               (float *param_1,int param_2,uint32_t param_3,uint32_t param_4,float *param_5,
               float *param_6)

{
  uint32_t *tmp_pu1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint8_t *tmp_pu5;
  int tmp_i6;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
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
  uint8_t local_64 [36];
  uint8_t local_40 [48];
  
  if (param_6 != (float *)0x0) {
    param_6[2] = 0.0;
    param_6[1] = 0.0;
    *param_6 = 0.0;
  }
  if (param_2 - 1U < 0x3fd) {
    tmp_i6 = param_2 * 0xaf8;
    tmp_pu5 = cg_entities + tmp_i6;
    if (*(int *)(cg_entities + tmp_i6 + 4) == 4) {
      if ((cg_entities[tmp_i6 + 10] & 2) == 0) {
        tmp_pu1 = (uint32_t *)(cg_entities + tmp_i6 + 0x110);
        BG_EvaluateTrajectory(tmp_i6 + 0x3133e4c,param_3,&local_ac,0,*tmp_pu1);
        BG_EvaluateTrajectory(tmp_i6 + 0x3133e70,param_3,&local_94,1,*tmp_pu1);
        BG_EvaluateTrajectory(tmp_i6 + 0x3133e4c,param_4,&local_a0,0,*tmp_pu1);
        BG_EvaluateTrajectory(tmp_i6 + 0x3133e70,param_4,&local_88,1,*tmp_pu1);
        local_cc = local_a0 - local_ac;
        local_c8 = local_9c - local_a8;
        local_c4 = local_98 - local_a4;
        local_7c = local_88 - local_94;
        local_78 = local_84 - local_90;
        local_74 = local_80 - local_8c;
      }
      else {
        CG_AddLinkedEntity(tmp_pu5,1,param_3);
        local_ac = *(float *)(cg_entities + tmp_i6 + 0x794);
        local_a8 = *(float *)(cg_entities + tmp_i6 + 0x798);
        local_a4 = *(float *)(cg_entities + tmp_i6 + 0x79c);
        local_94 = *(float *)(cg_entities + tmp_i6 + 0x7a0);
        local_90 = *(float *)(cg_entities + tmp_i6 + 0x7a4);
        local_8c = *(float *)(cg_entities + tmp_i6 + 0x7a8);
        CG_AddLinkedEntity(tmp_pu5,1,param_4);
        local_cc = *(float *)(cg_entities + tmp_i6 + 0x794) - local_ac;
        local_c8 = *(float *)(cg_entities + tmp_i6 + 0x798) - local_a8;
        local_c4 = *(float *)(cg_entities + tmp_i6 + 0x79c) - local_a4;
        local_7c = *(float *)(cg_entities + tmp_i6 + 0x7a0) - local_94;
        local_78 = *(float *)(cg_entities + tmp_i6 + 0x7a4) - local_90;
        local_74 = *(float *)(cg_entities + tmp_i6 + 0x7a8) - local_8c;
        CG_AddLinkedEntity(tmp_pu5,1,g_unk_010906e0);
      }
      BG_CreateRotationMatrix(&local_7c,local_64);
      BG_TransposeMatrix(local_64,local_40);
      param_2 = param_2 * 0xaf8;
      tmp_f2 = *(float *)(g_unk_01047b00 + 0x40) - *(float *)(cg_entities + param_2 + 0x794);
      tmp_f3 = *(float *)(g_unk_01047b00 + 0x44) - *(float *)(cg_entities + param_2 + 0x798);
      tmp_f4 = *(float *)(g_unk_01047b00 + 0x48) - *(float *)(cg_entities + param_2 + 0x79c);
      local_70 = tmp_f2;
      local_6c = tmp_f3;
      local_68 = tmp_f4;
      BG_RotatePoint(&local_70,local_40);
      *param_5 = (local_70 - tmp_f2) + local_cc + *param_1;
      param_5[1] = (local_6c - tmp_f3) + local_c8 + param_1[1];
      param_5[2] = (local_68 - tmp_f4) + local_c4 + param_1[2];
      if (param_6 == (float *)0x0) {
        return;
      }
      *param_6 = local_7c;
      param_6[1] = local_78;
      param_6[2] = local_74;
      return;
    }
  }
  *param_5 = *param_1;
  param_5[1] = param_1[1];
  param_5[2] = param_1[2];
  return;
}

void CG_CalcEntityLerpPositions(int *param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [8];
  float local_4c;
  
  if (param_1[0x90] != 0) {
    if (param_1[3] == 1) {
LAB_0006b268:
      if (g_unk_01047b04 == 0) {
        return;
      }
      CG_InterpolateEntityPosition_part_3();
      return;
    }
    if (param_1[3] == 3) {
      if (*param_1 < 0x40) goto LAB_0006b268;
      param_1[0x1eb] = param_1[0x1e8];
      param_1[0x1ec] = param_1[0x1e9];
      param_1[0x1ed] = param_1[0x1ea];
      param_1[0x1ee] = param_1[0x1e5];
      param_1[0x1ef] = param_1[0x1e6];
      param_1[0x1f0] = param_1[0x1e7];
      goto LAB_0006b1b6;
    }
  }
  param_1[0x1eb] = param_1[0x1e8];
  param_1[0x1ec] = param_1[0x1e9];
  param_1[0x1ed] = param_1[0x1ea];
  param_1[0x1ee] = param_1[0x1e5];
  param_1[0x1ef] = param_1[0x1e6];
  param_1[0x1f0] = param_1[0x1e7];
  if ((*param_1 < 0x40) && (param_1[0x2b] != g_unk_0109079c)) {
    param_1[3] = 3;
    param_1[4] = *(int *)(g_unk_01047b00 + 8);
    param_1[5] = (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4));
  }
LAB_0006b1b6:
  if ((int)GHIDRA_FIELD(cg_projectileNudge, 12, 4) < 1) {
    tmp_pi1 = param_1 + 0x1e5;
    BG_EvaluateTrajectory(param_1 + 3,g_unk_010906e0,tmp_pi1,0,param_1[0x44]);
    BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0,param_1 + 0x1e8,1,param_1[0x44]);
    if ((param_1 != (int *)&g_unk_01090ca8) && (g_unk_010abd78 == 0)) {
      CG_AdjustPositionForMover
                (tmp_pi1,param_1[0x25],*(uint32_t *)(g_unk_01047b00 + 8),g_unk_010906e0,tmp_pi1,0);
    }
  }
  else if (param_1[1] == 3) {
    if (param_1[0x2b] == g_unk_01047ac4) {
      tmp_i2 = (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4));
    }
    else if (GHIDRA_FIELD(cg_projectileNudge, 12, 4) == 1) {
      tmp_i2 = (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4)) + *(int *)(g_unk_01047b00 + 4);
    }
    else {
      tmp_i2 = (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4)) + GHIDRA_FIELD(cg_projectileNudge, 12, 4);
    }
    BG_EvaluateTrajectory(param_1 + 3,tmp_i2 + g_unk_010906e0,param_1 + 0x1e5,0,param_1[0x44]);
    BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0 + tmp_i2,param_1 + 0x1e8,1,param_1[0x44]);
    if (tmp_i2 != 0) {
      BG_EvaluateTrajectory(param_1 + 3,tmp_i2 + g_unk_010906e0,&local_60,0,param_1[0x44]);
      CG_Trace(local_54,&local_60,&vec3_origin,&vec3_origin,param_1 + 0x1e5,*param_1,0x6000001);
      if (local_4c < 1.0) {
        param_1[0x1e5] = (int)(((float)param_1[0x1e5] - local_60) * local_4c + local_60);
        param_1[0x1e6] = (int)(((float)param_1[0x1e6] - local_5c) * local_4c + local_5c);
        param_1[0x1e7] = (int)(((float)param_1[0x1e7] - local_58) * local_4c + local_58);
      }
    }
  }
  else {
    BG_EvaluateTrajectory(param_1 + 3,g_unk_010906e0,param_1 + 0x1e5,0,param_1[0x44]);
    BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0,param_1 + 0x1e8,1,param_1[0x44]);
  }
  return;
}

void CG_AddCEntity(int *param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [8];
  float local_4c;
  
  if (0x3a < (uint)param_1[1]) {
    return;
  }
  param_1[0x262] = cg;
  if (param_1[0x90] == 0) {
LAB_0006b5cd:
    param_1[0x1eb] = param_1[0x1e8];
    param_1[0x1ec] = param_1[0x1e9];
    param_1[0x1ed] = param_1[0x1ea];
    param_1[0x1ee] = param_1[0x1e5];
    param_1[0x1ef] = param_1[0x1e6];
    param_1[0x1f0] = param_1[0x1e7];
    if ((*param_1 < 0x40) && (param_1[0x2b] != g_unk_0109079c)) {
      param_1[3] = 3;
      param_1[4] = *(int *)(g_unk_01047b00 + 8);
      param_1[5] = (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4));
    }
  }
  else {
    if (param_1[3] == 1) {
LAB_0006b860:
      if (g_unk_01047b04 != 0) {
        CG_InterpolateEntityPosition_part_3();
      }
      goto LAB_0006b6e0;
    }
    if (param_1[3] != 3) goto LAB_0006b5cd;
    if (*param_1 < 0x40) goto LAB_0006b860;
    param_1[0x1eb] = param_1[0x1e8];
    param_1[0x1ec] = param_1[0x1e9];
    param_1[0x1ed] = param_1[0x1ea];
    param_1[0x1ee] = param_1[0x1e5];
    param_1[0x1ef] = param_1[0x1e6];
    param_1[0x1f0] = param_1[0x1e7];
  }
  if ((int)GHIDRA_FIELD(cg_projectileNudge, 12, 4) < 1) {
    tmp_pi1 = param_1 + 0x1e5;
    BG_EvaluateTrajectory(param_1 + 3,g_unk_010906e0,tmp_pi1,0,param_1[0x44]);
    BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0,param_1 + 0x1e8,1,param_1[0x44]);
    if ((param_1 != (int *)&g_unk_01090ca8) && (g_unk_010abd78 == 0)) {
      CG_AdjustPositionForMover
                (tmp_pi1,param_1[0x25],*(uint32_t *)(g_unk_01047b00 + 8),g_unk_010906e0,tmp_pi1,0);
    }
  }
  else if (param_1[1] == 3) {
    if (param_1[0x2b] == g_unk_01047ac4) {
      tmp_i2 = (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4));
    }
    else if (GHIDRA_FIELD(cg_projectileNudge, 12, 4) == 1) {
      tmp_i2 = (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4)) + *(int *)(g_unk_01047b00 + 4);
    }
    else {
      tmp_i2 = (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4)) + GHIDRA_FIELD(cg_projectileNudge, 12, 4);
    }
    BG_EvaluateTrajectory(param_1 + 3,tmp_i2 + g_unk_010906e0,param_1 + 0x1e5,0,param_1[0x44]);
    BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0 + tmp_i2,param_1 + 0x1e8,1,param_1[0x44]);
    if (tmp_i2 != 0) {
      BG_EvaluateTrajectory(param_1 + 3,tmp_i2 + g_unk_010906e0,&local_60,0,param_1[0x44]);
      CG_Trace(local_54,&local_60,&vec3_origin,&vec3_origin,param_1 + 0x1e5,*param_1,0x6000001);
      if (local_4c < 1.0) {
        param_1[0x1e5] = (int)(((float)param_1[0x1e5] - local_60) * local_4c + local_60);
        param_1[0x1e6] = (int)(((float)param_1[0x1e6] - local_5c) * local_4c + local_5c);
        param_1[0x1e7] = (int)(((float)param_1[0x1e7] - local_58) * local_4c + local_58);
      }
    }
  }
  else {
    BG_EvaluateTrajectory(param_1 + 3,g_unk_010906e0,param_1 + 0x1e5,0,param_1[0x44]);
    BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0,param_1 + 0x1e8,1,param_1[0x44]);
  }
LAB_0006b6e0:
  CG_EntityEffects();
  CG_ProcessEntity();
  return;
}

uint32_t CG_AddCEntity_Filter(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  float __x;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  float tmp_f7;
  int local_38;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i6 = g_unk_010906e0;
  tmp_i1 = *(int *)(param_1 + 0x988);
  if (tmp_i1 == cg) {
    if (g_unk_010ee058 == 0) {
      return 1;
    }
    tmp_u2 = *(uint *)(param_1 + 8);
  }
  else {
    tmp_u2 = *(uint *)(param_1 + 8);
  }
  if ((tmp_u2 & 0x20000) == 0) {
    if ((tmp_u2 & 0x8000) == 0) {
      if (((GHIDRA_FIELD(cg_earlyTransition, 12, 4) != 0) && (g_unk_01047b04 != 0)) &&
         ((*(int *)(param_1 + 0x124) == 0 || (*(int *)(param_1 + 0x124) == 3)))) {
        return 1;
      }
      if (*(uint *)(param_1 + 4) < 0x3b) {
        *(int *)(param_1 + 0x988) = cg;
        CG_CalcEntityLerpPositions(param_1);
        CG_EntityEffects();
        CG_ProcessEntity();
        return 1;
      }
      return 1;
    }
    if (0x3a < *(uint *)(param_1 + 4)) {
      return 0;
    }
    if ((tmp_i1 == cg) && (g_unk_010ee058 == 0)) {
      return 1;
    }
    tmp_u4 = CG_AddEntityToTag_part_10();
    return tmp_u4;
  }
  if (0x3a < *(uint *)(param_1 + 4)) {
    return 1;
  }
  if ((tmp_i1 == cg) && (g_unk_010ee058 == 0)) {
    return 1;
  }
  tmp_i1 = *(int *)(param_1 + 0xf0);
  tmp_i3 = tmp_i1 * 0xaf8;
  if ((*(int *)(cg_entities + tmp_i3 + 0x244) == 0) ||
     (((cg != *(int *)(cg_entities + tmp_i3 + 0x988) && ((cg_entities[tmp_i3 + 10] & 2) != 0)) &&
      (tmp_i3 = CG_AddLinkedEntity(cg_entities + tmp_i3,0,g_unk_010906e0), tmp_i3 == 0)))) {
    return 0;
  }
  tmp_i3 = tmp_i1 * 0xaf8;
  *(int *)(param_1 + 0x988) = cg;
  if ((cg_entities[tmp_i3 + 10] & 2) == 0) {
    if (*(int *)(cg_entities + tmp_i3 + 0xc) != 0xd) goto LAB_0006bd12;
    tmp_i5 = BG_GetSplineData(*(uint32_t *)(cg_entities + tmp_i3 + 0x110),param_1 + 0x9b0);
    *(int *)(param_1 + 0x9a8) = tmp_i5;
    if (tmp_i5 == 0) {
      return 0;
    }
    if (*(int *)(cg_entities + tmp_i3 + 0x14) == 0) {
      local_38 = *(int *)(param_1 + 0x9b0);
      *(uint32_t *)(param_1 + 0x9ac) = 0;
joined_r0x0006bf8b:
      tmp_i6 = 0;
      tmp_f7 = 0.0;
      __x = 0.0;
      if (local_38 != 0) {
LAB_0006be21:
        tmp_f7 = 1.0 - tmp_f7;
        *(float *)(param_1 + 0x9ac) = tmp_f7;
LAB_0006be2d:
        __x = tmp_f7 * 16.0;
        tmp_f7 = floorf(__x);
        tmp_i6 = (int)ROUND(tmp_f7);
        if (0xf < tmp_i6) goto LAB_0006be83;
      }
      tmp_f7 = (__x - (float)tmp_i6) * *(float *)(tmp_i5 + 0x1e0 + tmp_i6 * 0x1c);
    }
    else {
      tmp_f7 = (float)(tmp_i6 - *(int *)(cg_entities + tmp_i3 + 0x10)) /
              (float)*(int *)(cg_entities + tmp_i3 + 0x14);
      if (tmp_f7 < 0.0) {
        local_38 = *(int *)(param_1 + 0x9b0);
        *(uint32_t *)(param_1 + 0x9ac) = 0;
        goto joined_r0x0006bf8b;
      }
      if (tmp_f7 <= 1.0) {
        local_38 = *(int *)(param_1 + 0x9b0);
        *(float *)(param_1 + 0x9ac) = tmp_f7;
        if (local_38 != 0) goto LAB_0006be21;
        goto LAB_0006be2d;
      }
      local_38 = *(int *)(param_1 + 0x9b0);
      *(uint32_t *)(param_1 + 0x9ac) = 0x3f800000;
      if (local_38 != 0) {
        tmp_f7 = 1.0;
        goto LAB_0006be21;
      }
LAB_0006be83:
      tmp_f7 = *(float *)(tmp_i5 + 900);
      tmp_i6 = 0xf;
    }
    tmp_i6 = tmp_i6 * 0x1c;
    local_28 = *(float *)(tmp_i5 + 0x1d4 + tmp_i6) * tmp_f7 + *(float *)(tmp_i5 + 0x1c8 + tmp_i6);
    local_24 = *(float *)(tmp_i5 + 0x1d8 + tmp_i6) * tmp_f7 + *(float *)(tmp_i5 + 0x1cc + tmp_i6);
    local_20 = tmp_f7 * *(float *)(tmp_i5 + 0x1dc + tmp_i6) + *(float *)(tmp_i5 + 0x1d0 + tmp_i6);
    if (*(float *)(cg_entities + tmp_i1 * 0xaf8 + 0x3c) != 0.0) {
      BG_LinearPathOrigin2
                (*(float *)(cg_entities + tmp_i1 * 0xaf8 + 0x3c),param_1 + 0x9a8,param_1 + 0x9ac,
                 &local_28,local_38);
    }
    *(float *)(param_1 + 0x794) = local_28;
    *(float *)(param_1 + 0x798) = local_24;
    *(float *)(param_1 + 0x79c) = local_20;
    tmp_f7 = *(float *)(param_1 + 0x80);
    if (tmp_f7 != 0.0) {
      BG_LinearPathOrigin2
                (tmp_f7,param_1 + 0x9a8,param_1 + 0x9ac,&local_28,*(uint32_t *)(param_1 + 0x9b0));
      tmp_f7 = *(float *)(param_1 + 0x80);
    }
    *(float *)(param_1 + 0x99c) = local_28;
    *(float *)(param_1 + 0x9a0) = local_24;
    *(float *)(param_1 + 0x9a4) = local_20;
    if (0.0 <= tmp_f7) goto LAB_0006bc60;
LAB_0006bf58:
    local_28 = local_28 - *(float *)(param_1 + 0x794);
    local_24 = local_24 - *(float *)(param_1 + 0x798);
    local_20 = local_20 - *(float *)(param_1 + 0x79c);
LAB_0006bc88:
    vectoangles(&local_28,param_1 + 0x7a0);
  }
  else {
    if (*(int *)(cg_entities + tmp_i3 + 0x9b4) == 0) {
LAB_0006bd12:
      *(uint32_t *)(param_1 + 0x9b4) = 0;
      *(uint32_t *)(param_1 + 0x794) = *(uint32_t *)(param_1 + 0x18);
      *(uint32_t *)(param_1 + 0x798) = *(uint32_t *)(param_1 + 0x1c);
      *(uint32_t *)(param_1 + 0x79c) = *(uint32_t *)(param_1 + 0x20);
      *(uint32_t *)(param_1 + 0x7a0) = *(uint32_t *)(param_1 + 0x3c);
      *(uint32_t *)(param_1 + 0x7a4) = *(uint32_t *)(param_1 + 0x40);
      *(uint32_t *)(param_1 + 0x7a8) = *(uint32_t *)(param_1 + 0x44);
      goto LAB_0006bcad;
    }
    local_28 = *(float *)(cg_entities + tmp_i3 + 0x99c);
    tmp_u4 = *(uint32_t *)(cg_entities + tmp_i3 + 0x9b0);
    local_24 = *(float *)(cg_entities + tmp_i3 + 0x9a0);
    local_20 = *(float *)(cg_entities + tmp_i3 + 0x9a4);
    *(uint32_t *)(param_1 + 0x9b0) = tmp_u4;
    *(uint32_t *)(param_1 + 0x9ac) = *(uint32_t *)(cg_entities + tmp_i3 + 0x9ac);
    tmp_i1 = *(int *)(cg_entities + tmp_i3 + 0x9a8);
    *(float *)(param_1 + 0x794) = local_28;
    *(float *)(param_1 + 0x798) = local_24;
    *(float *)(param_1 + 0x79c) = local_20;
    tmp_f7 = *(float *)(param_1 + 0x80);
    *(int *)(param_1 + 0x9a8) = tmp_i1;
    if ((tmp_f7 != 0.0) && (tmp_i1 != 0)) {
      BG_LinearPathOrigin2(tmp_f7,param_1 + 0x9a8,param_1 + 0x9ac,&local_28,tmp_u4);
      tmp_f7 = *(float *)(param_1 + 0x80);
    }
    *(float *)(param_1 + 0x99c) = local_28;
    *(float *)(param_1 + 0x9a0) = local_24;
    *(float *)(param_1 + 0x9a4) = local_20;
    if (tmp_f7 < 0.0) goto LAB_0006bf58;
LAB_0006bc60:
    if (0.0 < tmp_f7) {
      local_28 = *(float *)(param_1 + 0x794) - local_28;
      local_24 = *(float *)(param_1 + 0x798) - local_24;
      local_20 = *(float *)(param_1 + 0x79c) - local_20;
      goto LAB_0006bc88;
    }
    *(uint32_t *)(param_1 + 0x7a8) = 0;
    *(uint32_t *)(param_1 + 0x7a4) = 0;
    *(uint32_t *)(param_1 + 0x7a0) = 0;
  }
  *(uint32_t *)(param_1 + 0x9b4) = 1;
LAB_0006bcad:
  CG_EntityEffects();
  CG_ProcessEntity();
  return 1;
}

uint32_t CG_AddEntityToTag_part_10(int *param_1)
{
  int *tmp_pi1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  uint8_t local_15c [36];
  float local_138 [3];
  uint8_t local_12c [36];
  uint8_t local_108 [8];
  float local_100;
  uint32_t local_ec [19];
  float local_a0;
  float local_9c;
  float local_98;
  
  if (param_1[0x90] == 0) {
LAB_0006c0e6:
    param_1[0x1eb] = param_1[0x1e8];
    param_1[0x1ec] = param_1[0x1e9];
    param_1[0x1ed] = param_1[0x1ea];
    param_1[0x1ee] = param_1[0x1e5];
    param_1[0x1ef] = param_1[0x1e6];
    param_1[0x1f0] = param_1[0x1e7];
    if ((*param_1 < 0x40) && (param_1[0x2b] != g_unk_0109079c)) {
      param_1[3] = 3;
      param_1[4] = *(int *)(g_unk_01047b00 + 8);
      param_1[5] = (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4));
    }
  }
  else {
    if (param_1[3] == 1) {
LAB_0006c430:
      if (g_unk_01047b04 != 0) {
        CG_InterpolateEntityPosition_part_3();
      }
      goto LAB_0006c200;
    }
    if (param_1[3] != 3) goto LAB_0006c0e6;
    if (*param_1 < 0x40) goto LAB_0006c430;
    param_1[0x1eb] = param_1[0x1e8];
    param_1[0x1ec] = param_1[0x1e9];
    param_1[0x1ed] = param_1[0x1ea];
    param_1[0x1ee] = param_1[0x1e5];
    param_1[0x1ef] = param_1[0x1e6];
    param_1[0x1f0] = param_1[0x1e7];
  }
  if ((int)GHIDRA_FIELD(cg_projectileNudge, 12, 4) < 1) {
    tmp_pi1 = param_1 + 0x1e5;
    BG_EvaluateTrajectory(param_1 + 3,g_unk_010906e0,tmp_pi1,0,param_1[0x44]);
    BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0,param_1 + 0x1e8,1,param_1[0x44]);
    if ((param_1 != (int *)&g_unk_01090ca8) && (g_unk_010abd78 == 0)) {
      CG_AdjustPositionForMover
                (tmp_pi1,param_1[0x25],*(uint32_t *)(g_unk_01047b00 + 8),g_unk_010906e0,tmp_pi1,0);
    }
  }
  else if (param_1[1] == 3) {
    if (param_1[0x2b] == g_unk_01047ac4) {
      tmp_i4 = (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4));
    }
    else if (GHIDRA_FIELD(cg_projectileNudge, 12, 4) == 1) {
      tmp_i4 = (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4)) + *(int *)(g_unk_01047b00 + 4);
    }
    else {
      tmp_i4 = GHIDRA_FIELD(cg_projectileNudge, 12, 4) + (int)(1000 / (longlong)(int)GHIDRA_FIELD(sv_fps, 12, 4));
    }
    BG_EvaluateTrajectory(param_1 + 3,g_unk_010906e0 + tmp_i4,param_1 + 0x1e5,0,param_1[0x44]);
    BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0 + tmp_i4,param_1 + 0x1e8,1,param_1[0x44]);
    if (tmp_i4 != 0) {
      BG_EvaluateTrajectory(param_1 + 3,g_unk_010906e0 + tmp_i4,local_138,0,param_1[0x44]);
      CG_Trace(local_108,local_138,&vec3_origin,&vec3_origin,param_1 + 0x1e5,*param_1,0x6000001);
      if (local_100 < 1.0) {
        param_1[0x1e5] = (int)(((float)param_1[0x1e5] - local_138[0]) * local_100 + local_138[0]);
        param_1[0x1e6] = (int)(((float)param_1[0x1e6] - local_138[1]) * local_100 + local_138[1]);
        param_1[0x1e7] = (int)(((float)param_1[0x1e7] - local_138[2]) * local_100 + local_138[2]);
      }
    }
  }
  else {
    BG_EvaluateTrajectory(param_1 + 3,g_unk_010906e0,param_1 + 0x1e5,0,param_1[0x44]);
    BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0,param_1 + 0x1e8,1,param_1[0x44]);
  }
LAB_0006c200:
  tmp_i4 = param_1[0x2ad];
  if (((0x3f < tmp_i4) && (tmp_i2 = tmp_i4 * 0xaf8, *(int *)(cg_entities + tmp_i2 + 0x244) != 0)) &&
     ((*(int *)(cg_entities + tmp_i2 + 0x988) == cg ||
      (tmp_i2 = CG_AddCEntity_Filter(cg_entities + tmp_i2), tmp_i2 != 0)))) {
    tmp_i4 = tmp_i4 * 0xaf8;
    param_1[0x262] = cg;
    AnglesToAxis(&vec3_origin,local_ec);
    trap_R_LerpTag(local_138,tmp_i4 + 0x31346dc,param_1 + 0x2ae,0);
    local_9c = *(float *)(cg_entities + tmp_i4 + 0x8bc) * local_138[0] +
               *(float *)(cg_entities + tmp_i4 + 0x908) +
               *(float *)(cg_entities + tmp_i4 + 0x8c8) * local_138[1] +
               local_138[2] * *(float *)(cg_entities + tmp_i4 + 0x8d4);
    local_98 = *(float *)(cg_entities + tmp_i4 + 0x8d8) * local_138[2] +
               *(float *)(cg_entities + tmp_i4 + 0x8c0) * local_138[0] +
               *(float *)(cg_entities + tmp_i4 + 0x90c) +
               *(float *)(cg_entities + tmp_i4 + 0x8cc) * local_138[1];
    local_a0 = *(float *)(cg_entities + tmp_i4 + 0x904) +
               local_138[0] * *(float *)(cg_entities + tmp_i4 + 0x8b8) +
               local_138[1] * *(float *)(cg_entities + tmp_i4 + 0x8c4) +
               local_138[2] * *(float *)(cg_entities + tmp_i4 + 0x8d0);
    MatrixMultiply(local_12c,cg_entities + tmp_i4 + 0x8b8,local_ec);
    param_1[0x1e5] = (int)local_a0;
    param_1[0x1e6] = (int)local_9c;
    param_1[0x1e7] = (int)local_98;
    if (param_1[1] != 1) {
      if (param_1[0x3d] == 0) {
        tmp_u3 = 0;
        do {
          *(uint32_t *)((int)local_138 + tmp_u3) = *(uint32_t *)((int)local_ec + tmp_u3);
          tmp_u3 = tmp_u3 + 4;
        } while (tmp_u3 < 0x24);
        BG_CreateRotationMatrix(param_1 + 0x1e8,local_15c);
        MatrixMultiply(local_15c,local_138,local_ec);
        AxisToAngles(local_ec,param_1 + 0x1e8);
      }
      else {
        BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0,param_1 + 0x1e8,1,param_1[0x44]);
      }
    }
    CG_EntityEffects();
    CG_ProcessEntity();
    return 1;
  }
  return 0;
}

uint32_t CG_AddEntityToTag(int param_1)
{
  uint32_t tmp_u1;
  
  if (0x3a < *(uint *)(param_1 + 4)) {
    return 0;
  }
  if ((*(int *)(param_1 + 0x988) == cg) && (g_unk_010ee058 == 0)) {
    return 1;
  }
  tmp_u1 = CG_AddEntityToTag_part_10();
  return tmp_u1;
}

void CG_Mover_PostProcess_part_11(int param_1)
{
  float *pfVar1;
  float *pfVar2;
  uint tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  uint tmp_u6;
  int *tmp_pi7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  float local_638;
  float *local_634;
  float local_62c;
  float local_628;
  float local_624;
  float local_61c;
  float local_618;
  float local_614;
  float local_604;
  float local_600;
  float local_5fc;
  uint8_t local_5f8 [36];
  float local_5d4;
  float local_5d0;
  float local_5cc;
  uint8_t local_5c8 [36];
  float local_5a4 [59];
  float local_4b8 [59];
  float local_3cc [59];
  float local_2e0 [179];
  uint32_t uStack_14;
  
  uStack_14 = 0x6c7a9;
  if ((*(byte *)(g_unk_01047b00 + 0x95) & 0x80) == 0) {
    tmp_i8 = *(int *)(param_1 + 0x114);
LAB_0006c7df:
    tmp_i9 = 0;
    tmp_pi7 = (int *)(cg_entities + 0x244);
    if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
      do {
        if (((*tmp_pi7 != 0) && ((*(byte *)((int)tmp_pi7 + -0x23b) & 0x80) != 0)) &&
           (tmp_i10 = tmp_i9, tmp_pi7[0x21c] == tmp_i8)) break;
        tmp_i9 = tmp_i9 + 1;
        tmp_pi7 = tmp_pi7 + 0x2be;
        tmp_i10 = GHIDRA_FIELD(cgs, 27400, 4);
      } while (tmp_i9 != GHIDRA_FIELD(cgs, 27400, 4));
      goto joined_r0x0006ceb6;
    }
    tmp_i10 = 0;
  }
  else {
    tmp_i8 = *(int *)(param_1 + 0x114);
    tmp_i10 = *(int *)(g_unk_01047b00 + 0xcc);
    if (*(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xab4) != tmp_i8)
    goto LAB_0006c7df;
joined_r0x0006ceb6:
    if (tmp_i10 == 0x40) {
      local_634 = (float *)&vec3_origin;
      goto LAB_0006c84a;
    }
  }
  if (tmp_i10 == *(int *)(g_unk_01047b00 + 0xcc)) {
    local_634 = (float *)&g_unk_010907ac;
  }
  else {
    local_634 = (float *)(cg_entities + tmp_i10 * 0xaf8 + 0x7a0);
  }
LAB_0006c84a:
  *(int *)(cg_entities + tmp_i8 * 0xaf8 + 0x9bc) = (param_1 + -0x3133e40 >> 3) * -0xbab6561;
  tmp_i8 = *(int *)(param_1 + 0x114);
  tmp_u6 = *(uint *)(param_1 + 0xf4);
  tmp_i9 = tmp_i8 * 0xaf8;
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)local_5a4 + tmp_u3) = 0;
    *(uint32_t *)((int)local_5a4 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0xe8);
  *(uint32_t *)((int)local_5a4 + tmp_u3) = 0;
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)local_3cc + tmp_u3) = 0;
    *(uint32_t *)((int)local_3cc + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0xe8);
  *(uint32_t *)((int)local_3cc + tmp_u3) = 0;
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)local_4b8 + tmp_u3) = 0;
    *(uint32_t *)((int)local_4b8 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0xe8);
  *(uint32_t *)((int)local_4b8 + tmp_u3) = 0;
  tmp_u3 = 0;
  do {
    tmp_u4 = tmp_u3;
    *(uint32_t *)((int)local_2e0 + tmp_u4) = 0;
    *(uint32_t *)((int)local_2e0 + tmp_u4 + 4) = 0;
    tmp_u3 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0xe8);
  *(uint32_t *)((int)local_2e0 + tmp_u4 + 8) = 0;
  tmp_u3 = 0;
  do {
    tmp_u4 = tmp_u3;
    *(uint32_t *)((int)local_2e0 + tmp_u4 + 0xec) = 0;
    *(uint32_t *)((int)local_2e0 + tmp_u4 + 0xf0) = 0;
    tmp_u3 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0xe8);
  *(uint32_t *)((int)local_2e0 + tmp_u4 + 0xf4) = 0;
  local_5a4[2] = (float)GHIDRA_FIELD(cgs, 69836, 4);
  local_4b8[2] = (float)GHIDRA_FIELD(cgs, 69840, 4);
  local_3cc[2] = (float)GHIDRA_FIELD(cgs, 69848, 4);
  if ((tmp_u6 & 8) == 0) {
    local_3cc[2] = (float)GHIDRA_FIELD(cgs, 69844, 4);
  }
  tmp_i5 = CG_AddCEntity_Filter(cg_entities + tmp_i9);
  if (tmp_i5 != 0) {
    if (*(int *)(cg_entities + tmp_i8 * 0xaf8 + 0x9b8) == cg) {
      local_5a4[0x1a] = *(float *)(cg_entities + tmp_i9 + 0x9c0);
      local_5a4[0x1b] = *(float *)(cg_entities + tmp_i9 + 0x9c4);
      local_5a4[0x1c] = *(float *)(cg_entities + tmp_i9 + 0x9c8);
      local_4b8[0x1a] = *(float *)(cg_entities + tmp_i9 + 0x9f0);
      local_4b8[0x1b] = *(float *)(cg_entities + tmp_i9 + 0x9f4);
      local_4b8[0x1c] = *(float *)(cg_entities + tmp_i9 + 0x9f8);
      local_638 = *(float *)(cg_entities + tmp_i9 + 0xa20);
      local_634 = *(float **)(cg_entities + tmp_i9 + 0xa24);
      local_62c = *(float *)(cg_entities + tmp_i9 + 0xa28);
      local_2e0[0x1a] = *(float *)(cg_entities + tmp_i9 + 0xa50);
      local_628 = *(float *)(cg_entities + tmp_i9 + 0xa54);
      local_624 = *(float *)(cg_entities + tmp_i9 + 0xa58);
      local_61c = *(float *)(cg_entities + tmp_i9 + 0xa80);
      local_618 = *(float *)(cg_entities + tmp_i9 + 0xa84);
      local_614 = *(float *)(cg_entities + tmp_i9 + 0xa88);
    }
    else {
      *(int *)(cg_entities + tmp_i8 * 0xaf8 + 0x9b8) = cg;
      pfVar1 = local_2e0 + 0x76;
      tmp_u6 = 0;
      do {
        *(uint32_t *)((int)pfVar1 + tmp_u6) = 0;
        *(uint32_t *)((int)local_2e0 + tmp_u6 + 0x1dc) = 0;
        tmp_u6 = tmp_u6 + 8;
      } while (tmp_u6 < 0xe8);
      *(uint32_t *)((int)pfVar1 + tmp_u6) = 0;
      tmp_i5 = tmp_i8 * 0xaf8;
      if (*(int *)(cg_entities + tmp_i5 + 0xb4) == 0xffffff) {
        local_2e0[0x78] = (float)CG_GetGameModel(*(uint32_t *)(cg_entities + tmp_i5 + 0xa8));
      }
      else {
        local_2e0[0x78] = (float)CG_GetGameModel(*(uint32_t *)(cg_entities + tmp_i5 + 0xa4));
      }
      tmp_i5 = tmp_i8 * 0xaf8;
      local_2e0[0x9e] = *(float *)(cg_entities + tmp_i5 + 0x850);
      local_2e0[0x93] = *(float *)(cg_entities + tmp_i5 + 0x844);
      local_2e0[0x9a] = *(float *)(cg_entities + tmp_i5 + 0x838);
      AnglesToAxis(cg_entities + tmp_i5 + 0x7a0,local_2e0 + 0x7d);
      pfVar2 = local_5a4 + 7;
      local_2e0[0x90] = *(float *)(cg_entities + tmp_i5 + 0x794);
      local_2e0[0x91] = *(float *)(cg_entities + tmp_i5 + 0x798);
      local_2e0[0x92] = *(float *)(cg_entities + tmp_i5 + 0x79c);
      AxisClear(pfVar2);
      trap_R_LerpTag(&local_5d4,pfVar1,"tag_player",0);
      local_5a4[0x1b] =
           local_2e0[0x81] * local_5d0 + local_2e0[0x7e] * local_5d4 + local_2e0[0x91] +
           local_2e0[0x84] * local_5cc;
      local_5a4[0x1c] =
           local_2e0[0x82] * local_5d0 + local_2e0[0x7f] * local_5d4 + local_2e0[0x92] +
           local_2e0[0x85] * local_5cc;
      local_5a4[0x1a] =
           local_5d4 * local_2e0[0x7d] + local_2e0[0x90] + local_2e0[0x80] * local_5d0 +
           local_5cc * local_2e0[0x83];
      MatrixMultiply(local_5c8,local_2e0 + 0x7d,pfVar2);
      local_604 = 0.0;
      local_600 = local_634[1];
      local_5fc = local_634[2];
      if (((*(byte *)(g_unk_01047b00 + 0x95) & 0x80) == 0) ||
         (*(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xab4) !=
          (tmp_i9 >> 3) * -0xbab6561)) {
        if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
          tmp_i5 = 0;
          tmp_pi7 = (int *)(cg_entities + 0x244);
          do {
            if (((*tmp_pi7 != 0) && ((*(byte *)((int)tmp_pi7 + -0x23b) & 0x80) != 0)) &&
               (tmp_pi7[0x21c] == (tmp_i9 >> 3) * -0xbab6561)) {
              local_600 = local_600 - *(float *)(cg_entities + tmp_i8 * 0xaf8 + 0x7a4);
              local_604 = 0.0 - *(float *)(cg_entities + tmp_i8 * 0xaf8 + 0x7a0);
              break;
            }
            tmp_i5 = tmp_i5 + 1;
            tmp_pi7 = tmp_pi7 + 0x2be;
          } while (tmp_i5 != GHIDRA_FIELD(cgs, 27400, 4));
        }
      }
      else {
        local_600 = local_600 - *(float *)(cg_entities + tmp_i5 + 0x7a4);
        local_604 = 0.0 - *(float *)(cg_entities + tmp_i5 + 0x7a0);
      }
      pfVar1 = local_4b8 + 7;
      AnglesToAxis(&local_604,pfVar1);
      trap_R_LerpTag(&local_5d4,local_5a4,"tag_mg42nest",0);
      local_4b8[0x1b] =
           local_5a4[0xb] * local_5d0 + local_5a4[8] * local_5d4 + local_5a4[0x1b] +
           local_5a4[0xe] * local_5cc;
      local_4b8[0x1c] =
           local_5a4[0xc] * local_5d0 + local_5a4[9] * local_5d4 + local_5a4[0x1c] +
           local_5a4[0xf] * local_5cc;
      local_4b8[0x1a] =
           local_5d0 * local_5a4[10] + local_5d4 * local_5a4[7] + local_5a4[0x1a] +
           local_5cc * local_5a4[0xd];
      MatrixMultiply(pfVar1,local_5c8,local_5f8);
      MatrixMultiply(local_5f8,pfVar2,pfVar1);
      local_600 = 0.0;
      local_5fc = 0.0;
      local_604 = *local_634;
      pfVar2 = local_3cc + 7;
      AnglesToAxis(&local_604,pfVar2);
      trap_R_LerpTag(&local_5d4,local_4b8,"tag_mg42",0);
      local_3cc[0x1b] =
           local_4b8[0xb] * local_5d0 + local_4b8[8] * local_5d4 + local_4b8[0x1b] +
           local_4b8[0xe] * local_5cc;
      local_3cc[0x1c] =
           local_4b8[0xc] * local_5d0 + local_4b8[9] * local_5d4 + local_4b8[0x1c] +
           local_4b8[0xf] * local_5cc;
      local_3cc[0x1a] =
           local_5d0 * local_4b8[10] + local_5d4 * local_4b8[7] + local_4b8[0x1a] +
           local_5cc * local_4b8[0xd];
      MatrixMultiply(pfVar2,local_5c8,local_5f8);
      MatrixMultiply(local_5f8,pfVar1,pfVar2);
      trap_R_LerpTag(&local_5d4,local_4b8,"tag_playerpo",0);
      local_2e0[0x1b] =
           local_4b8[0xb] * local_5d0 + local_4b8[8] * local_5d4 + local_4b8[0x1b] +
           local_4b8[0xe] * local_5cc;
      local_2e0[0x1c] =
           local_4b8[0xc] * local_5d0 + local_4b8[9] * local_5d4 + local_4b8[0x1c] +
           local_4b8[0xf] * local_5cc;
      local_2e0[0x1a] =
           local_5d4 * local_4b8[7] + local_4b8[0x1a] + local_4b8[10] * local_5d0 +
           local_5cc * local_4b8[0xd];
      MatrixMultiply(local_5c8,pfVar1,local_2e0 + 7);
      trap_R_LerpTag(&local_5d4,local_3cc,"tag_flash",0);
      local_2e0[0x56] =
           local_3cc[0xb] * local_5d0 + local_3cc[8] * local_5d4 + local_3cc[0x1b] +
           local_3cc[0xe] * local_5cc;
      local_2e0[0x57] =
           local_3cc[0xc] * local_5d0 + local_3cc[9] * local_5d4 + local_3cc[0x1c] +
           local_3cc[0xf] * local_5cc;
      local_2e0[0x55] =
           local_5d0 * local_3cc[10] + local_5d4 * local_3cc[7] + local_3cc[0x1a] +
           local_5cc * local_3cc[0xd];
      MatrixMultiply(local_5c8,pfVar2,local_2e0 + 0x42);
      *(float *)(cg_entities + tmp_i9 + 0x9c0) = local_5a4[0x1a];
      *(float *)(cg_entities + tmp_i9 + 0x9c4) = local_5a4[0x1b];
      *(float *)(cg_entities + tmp_i9 + 0x9c8) = local_5a4[0x1c];
      *(float *)(cg_entities + tmp_i9 + 0x9cc) = local_5a4[7];
      *(float *)(cg_entities + tmp_i9 + 0x9d0) = local_5a4[8];
      *(float *)(cg_entities + tmp_i9 + 0x9d4) = local_5a4[9];
      *(float *)(cg_entities + tmp_i9 + 0x9d8) = local_5a4[10];
      *(float *)(cg_entities + tmp_i9 + 0x9dc) = local_5a4[0xb];
      *(float *)(cg_entities + tmp_i9 + 0x9e0) = local_5a4[0xc];
      *(float *)(cg_entities + tmp_i9 + 0x9e4) = local_5a4[0xd];
      *(float *)(cg_entities + tmp_i9 + 0x9e8) = local_5a4[0xe];
      *(float *)(cg_entities + tmp_i9 + 0x9ec) = local_5a4[0xf];
      *(float *)(cg_entities + tmp_i9 + 0x9f0) = local_4b8[0x1a];
      *(float *)(cg_entities + tmp_i9 + 0x9f4) = local_4b8[0x1b];
      *(float *)(cg_entities + tmp_i9 + 0x9f8) = local_4b8[0x1c];
      *(float *)(cg_entities + tmp_i9 + 0x9fc) = local_4b8[7];
      *(float *)(cg_entities + tmp_i9 + 0xa00) = local_4b8[8];
      *(float *)(cg_entities + tmp_i9 + 0xa04) = local_4b8[9];
      *(float *)(cg_entities + tmp_i9 + 0xa08) = local_4b8[10];
      *(float *)(cg_entities + tmp_i9 + 0xa0c) = local_4b8[0xb];
      *(float *)(cg_entities + tmp_i9 + 0xa10) = local_4b8[0xc];
      *(float *)(cg_entities + tmp_i9 + 0xa14) = local_4b8[0xd];
      *(float *)(cg_entities + tmp_i9 + 0xa18) = local_4b8[0xe];
      *(float *)(cg_entities + tmp_i9 + 0xa1c) = local_4b8[0xf];
      local_638 = local_3cc[0x1a];
      *(float *)(cg_entities + tmp_i9 + 0xa20) = local_3cc[0x1a];
      local_634 = (float *)local_3cc[0x1b];
      *(float *)(cg_entities + tmp_i9 + 0xa24) = local_3cc[0x1b];
      local_62c = local_3cc[0x1c];
      *(float *)(cg_entities + tmp_i9 + 0xa28) = local_3cc[0x1c];
      *(float *)(cg_entities + tmp_i9 + 0xa2c) = local_3cc[7];
      *(float *)(cg_entities + tmp_i9 + 0xa30) = local_3cc[8];
      *(float *)(cg_entities + tmp_i9 + 0xa34) = local_3cc[9];
      *(float *)(cg_entities + tmp_i9 + 0xa38) = local_3cc[10];
      *(float *)(cg_entities + tmp_i9 + 0xa3c) = local_3cc[0xb];
      *(float *)(cg_entities + tmp_i9 + 0xa40) = local_3cc[0xc];
      *(float *)(cg_entities + tmp_i9 + 0xa44) = local_3cc[0xd];
      *(float *)(cg_entities + tmp_i9 + 0xa48) = local_3cc[0xe];
      *(float *)(cg_entities + tmp_i9 + 0xa4c) = local_3cc[0xf];
      *(float *)(cg_entities + tmp_i9 + 0xa50) = local_2e0[0x1a];
      local_628 = local_2e0[0x1b];
      *(float *)(cg_entities + tmp_i9 + 0xa54) = local_2e0[0x1b];
      local_624 = local_2e0[0x1c];
      *(float *)(cg_entities + tmp_i9 + 0xa58) = local_2e0[0x1c];
      *(float *)(cg_entities + tmp_i9 + 0xa5c) = local_2e0[7];
      *(float *)(cg_entities + tmp_i9 + 0xa60) = local_2e0[8];
      *(float *)(cg_entities + tmp_i9 + 0xa64) = local_2e0[9];
      *(float *)(cg_entities + tmp_i9 + 0xa68) = local_2e0[10];
      *(float *)(cg_entities + tmp_i9 + 0xa6c) = local_2e0[0xb];
      *(float *)(cg_entities + tmp_i9 + 0xa70) = local_2e0[0xc];
      *(float *)(cg_entities + tmp_i9 + 0xa74) = local_2e0[0xd];
      *(float *)(cg_entities + tmp_i9 + 0xa78) = local_2e0[0xe];
      *(float *)(cg_entities + tmp_i9 + 0xa7c) = local_2e0[0xf];
      local_61c = local_2e0[0x55];
      *(float *)(cg_entities + tmp_i9 + 0xa80) = local_2e0[0x55];
      local_618 = local_2e0[0x56];
      *(float *)(cg_entities + tmp_i9 + 0xa84) = local_2e0[0x56];
      local_614 = local_2e0[0x57];
      *(float *)(cg_entities + tmp_i9 + 0xa88) = local_2e0[0x57];
      *(float *)(cg_entities + tmp_i9 + 0xa8c) = local_2e0[0x42];
      *(float *)(cg_entities + tmp_i9 + 0xa90) = local_2e0[0x43];
      *(float *)(cg_entities + tmp_i9 + 0xa94) = local_2e0[0x44];
      *(float *)(cg_entities + tmp_i9 + 0xa98) = local_2e0[0x45];
      *(float *)(cg_entities + tmp_i9 + 0xa9c) = local_2e0[0x46];
      *(float *)(cg_entities + tmp_i9 + 0xaa0) = local_2e0[0x47];
      *(float *)(cg_entities + tmp_i9 + 0xaa4) = local_2e0[0x48];
      *(float *)(cg_entities + tmp_i9 + 0xaa8) = local_2e0[0x49];
      *(float *)(cg_entities + tmp_i9 + 0xaac) = local_2e0[0x4a];
    }
    local_5a4[7] = *(float *)(cg_entities + tmp_i9 + 0x9cc);
    local_5a4[8] = *(float *)(cg_entities + tmp_i9 + 0x9d0);
    local_5a4[9] = *(float *)(cg_entities + tmp_i9 + 0x9d4);
    local_5a4[10] = *(float *)(cg_entities + tmp_i9 + 0x9d8);
    local_5a4[0xb] = *(float *)(cg_entities + tmp_i9 + 0x9dc);
    local_5a4[0xc] = *(float *)(cg_entities + tmp_i9 + 0x9e0);
    local_5a4[0xd] = *(float *)(cg_entities + tmp_i9 + 0x9e4);
    local_5a4[0xe] = *(float *)(cg_entities + tmp_i9 + 0x9e8);
    local_5a4[0xf] = *(float *)(cg_entities + tmp_i9 + 0x9ec);
    local_4b8[7] = *(float *)(cg_entities + tmp_i9 + 0x9fc);
    local_4b8[8] = *(float *)(cg_entities + tmp_i9 + 0xa00);
    local_4b8[9] = *(float *)(cg_entities + tmp_i9 + 0xa04);
    local_4b8[10] = *(float *)(cg_entities + tmp_i9 + 0xa08);
    local_4b8[0xb] = *(float *)(cg_entities + tmp_i9 + 0xa0c);
    local_4b8[0xc] = *(float *)(cg_entities + tmp_i9 + 0xa10);
    local_4b8[0xd] = *(float *)(cg_entities + tmp_i9 + 0xa14);
    local_4b8[0xe] = *(float *)(cg_entities + tmp_i9 + 0xa18);
    local_4b8[0xf] = *(float *)(cg_entities + tmp_i9 + 0xa1c);
    local_3cc[0x1a] = local_638;
    local_3cc[0x1b] = (float)local_634;
    local_3cc[0x1c] = local_62c;
    local_3cc[7] = *(float *)(cg_entities + tmp_i9 + 0xa2c);
    local_3cc[8] = *(float *)(cg_entities + tmp_i9 + 0xa30);
    local_3cc[9] = *(float *)(cg_entities + tmp_i9 + 0xa34);
    local_3cc[10] = *(float *)(cg_entities + tmp_i9 + 0xa38);
    local_3cc[0xb] = *(float *)(cg_entities + tmp_i9 + 0xa3c);
    local_3cc[0xc] = *(float *)(cg_entities + tmp_i9 + 0xa40);
    local_3cc[0xd] = *(float *)(cg_entities + tmp_i9 + 0xa44);
    local_3cc[0xe] = *(float *)(cg_entities + tmp_i9 + 0xa48);
    local_3cc[0xf] = *(float *)(cg_entities + tmp_i9 + 0xa4c);
    local_2e0[0x1b] = local_628;
    local_2e0[0x1c] = local_624;
    local_2e0[7] = *(float *)(cg_entities + tmp_i9 + 0xa5c);
    local_2e0[8] = *(float *)(cg_entities + tmp_i9 + 0xa60);
    local_2e0[9] = *(float *)(cg_entities + tmp_i9 + 0xa64);
    local_2e0[10] = *(float *)(cg_entities + tmp_i9 + 0xa68);
    local_2e0[0xb] = *(float *)(cg_entities + tmp_i9 + 0xa6c);
    local_2e0[0xc] = *(float *)(cg_entities + tmp_i9 + 0xa70);
    local_2e0[0xd] = *(float *)(cg_entities + tmp_i9 + 0xa74);
    local_2e0[0xe] = *(float *)(cg_entities + tmp_i9 + 0xa78);
    local_2e0[0xf] = *(float *)(cg_entities + tmp_i9 + 0xa7c);
    local_2e0[0x55] = local_61c;
    local_2e0[0x56] = local_618;
    local_2e0[0x57] = local_614;
    local_2e0[0x42] = *(float *)(cg_entities + tmp_i9 + 0xa8c);
    local_2e0[0x43] = *(float *)(cg_entities + tmp_i9 + 0xa90);
    local_2e0[0x44] = *(float *)(cg_entities + tmp_i9 + 0xa94);
    local_2e0[0x45] = *(float *)(cg_entities + tmp_i9 + 0xa98);
    local_2e0[0x46] = *(float *)(cg_entities + tmp_i9 + 0xa9c);
    local_2e0[0x47] = *(float *)(cg_entities + tmp_i9 + 0xaa0);
    local_2e0[0x48] = *(float *)(cg_entities + tmp_i9 + 0xaa4);
    local_2e0[0x49] = *(float *)(cg_entities + tmp_i9 + 0xaa8);
    local_2e0[0x4a] = *(float *)(cg_entities + tmp_i9 + 0xaac);
  }
  if (((*(byte *)(g_unk_01047b00 + 0x95) & 0x80) != 0) &&
     (cg_entities + *(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xab4) * 0xaf8 ==
      cg_entities + *(int *)(param_1 + 0x114) * 0xaf8)) {
    CG_CalcViewValues();
  }
  local_5a4[3] = local_5a4[0x1a];
  local_5a4[4] = local_5a4[0x1b];
  local_5a4[5] = local_5a4[0x1c];
  local_5a4[0x21] = local_5a4[0x1a];
  local_5a4[0x22] = local_5a4[0x1b];
  local_5a4[0x23] = local_5a4[0x1c];
  local_4b8[3] = local_4b8[0x1a];
  local_4b8[4] = local_4b8[0x1b];
  local_4b8[5] = local_4b8[0x1c];
  local_4b8[0x21] = local_4b8[0x1a];
  local_4b8[0x22] = local_4b8[0x1b];
  local_4b8[0x23] = local_4b8[0x1c];
  local_3cc[3] = local_3cc[0x1a];
  local_3cc[4] = local_3cc[0x1b];
  local_3cc[5] = local_3cc[0x1c];
  local_3cc[0x21] = local_3cc[0x1a];
  local_3cc[0x22] = local_3cc[0x1b];
  local_3cc[0x23] = local_3cc[0x1c];
  trap_R_AddRefEntityToScene(local_5a4);
  if ((tmp_i10 != *(int *)(g_unk_01047b00 + 0xcc)) || (g_unk_010906f4 != 0)) {
    trap_R_AddRefEntityToScene(local_4b8);
    trap_R_AddRefEntityToScene(local_3cc);
  }
  return;
}

void CG_Mover_PostProcess(int param_1)
{
  if ((*(byte *)(param_1 + 0xf4) & 4) != 0) {
    CG_Mover_PostProcess_part_11();
    return;
  }
  return;
}

void CG_AddPacketEntities(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int local_34;
  int local_30;
  
  if (g_unk_01047b04 != 0) {
    tmp_i1 = *(int *)(g_unk_01047b04 + 8) - *(int *)(g_unk_01047b00 + 8);
    if (tmp_i1 != 0) {
      g_unk_010906d0 = (float)(int)(g_unk_010906e0 - *(int *)(g_unk_01047b00 + 8)) / (float)tmp_i1;
      goto LAB_0006d9e6;
    }
  }
  g_unk_010906d0 = 0.0;
LAB_0006d9e6:
  g_unk_01091818 = 0;
  g_unk_0109181c = (float)((g_unk_010906e0 & 0xfff) * 0x168) / 4095.0;
  g_unk_01091820 = 0;
  g_unk_01091848 = 0;
  g_unk_0109184c = (float)((g_unk_010906e0 & 0x7ff) * 0x168) * 0.00048828125;
  g_unk_0109187c = (float)((g_unk_010906e0 & 0x3ff) * 0x168) * 0.0009765625;
  g_unk_01091850 = 0;
  g_unk_01091878 = 0;
  g_unk_01091880 = 0;
  AnglesToAxis(&g_unk_01091818,&g_unk_01091824);
  AnglesToAxis(&g_unk_01091848,&g_unk_01091854);
  AnglesToAxis(&g_unk_01091878,&g_unk_01091884);
  BG_PlayerStateToEntityState(&g_unk_010906fc,&g_unk_01090ca8,g_unk_010906e0,0);
  if (g_unk_01090cac < 0x3b) {
    g_unk_01091630 = cg;
    CG_CalcEntityLerpPositions(&g_unk_01090ca8);
    CG_EntityEffects();
    CG_ProcessEntity();
  }
  CG_CalcEntityLerpPositions(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8);
  g_unk_010b4530 = 0;
  g_unk_010ee054 = 0;
  if (((GHIDRA_FIELD(cg_earlyTransition, 12, 4) != 0) && (g_unk_01047b04 != 0)) &&
     (tmp_i1 = *(int *)(g_unk_01047b04 + 0x5d8), 0 < tmp_i1)) {
    tmp_i4 = 0;
    tmp_i2 = g_unk_01047b04;
    do {
      while( true ) {
        tmp_i3 = *(int *)(tmp_i2 + 0x5dc + tmp_i4 * 0x120);
        if ((*(int *)(cg_entities + tmp_i3 * 0xaf8 + 0x124) != 0) &&
           (*(int *)(cg_entities + tmp_i3 * 0xaf8 + 0x124) != 3)) break;
        tmp_i3 = tmp_i3 * 0xaf8;
        CG_TransitionEntity(cg_entities + tmp_i3);
        *(uint32_t *)(cg_entities + tmp_i3 + 0x240) = 1;
        if (*(uint *)(cg_entities + tmp_i3 + 4) < 0x3b) {
          *(int *)(cg_entities + tmp_i3 + 0x988) = cg;
          CG_CalcEntityLerpPositions(cg_entities + tmp_i3);
          CG_EntityEffects();
          CG_ProcessEntity();
        }
        tmp_i4 = tmp_i4 + 1;
        tmp_i1 = *(int *)(g_unk_01047b04 + 0x5d8);
        tmp_i2 = g_unk_01047b04;
        if (tmp_i1 <= tmp_i4) goto LAB_0006dc10;
      }
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_i4 < tmp_i1);
  }
LAB_0006dc10:
  local_34 = g_unk_01047b00;
  local_30 = *(int *)(g_unk_01047b00 + 0x5d8);
  if (0 < local_30) {
    tmp_i1 = 0;
    do {
      while( true ) {
        tmp_i2 = *(int *)(local_34 + 0x5dc + tmp_i1 * 0x120);
        if ((*(int *)(cg_entities + tmp_i2 * 0xaf8 + 0x988) == cg) && (g_unk_010ee058 == 0))
        goto LAB_0006dc97;
        tmp_i4 = tmp_i2 * 0xaf8;
        if ((*(uint *)(cg_entities + tmp_i4 + 8) & 0x20000) == 0) break;
        CG_AddLinkedEntity(cg_entities + tmp_i2 * 0xaf8,0,g_unk_010906e0);
LAB_0006dd23:
        tmp_i1 = tmp_i1 + 1;
        local_34 = g_unk_01047b00;
        local_30 = *(int *)(g_unk_01047b00 + 0x5d8);
        if (local_30 <= tmp_i1) goto LAB_0006dd45;
      }
      if ((*(uint *)(cg_entities + tmp_i4 + 8) & 0x8000) != 0) {
        if ((0x3a < *(uint *)(cg_entities + tmp_i4 + 4)) ||
           ((*(int *)(cg_entities + tmp_i2 * 0xaf8 + 0x988) == cg && (g_unk_010ee058 == 0))))
        goto LAB_0006dc97;
        CG_AddEntityToTag_part_10();
        goto LAB_0006dd23;
      }
      if (GHIDRA_FIELD(cg_earlyTransition, 12, 4) == 0) {
        if (*(uint *)(cg_entities + tmp_i4 + 4) < 0x3b) {
          *(int *)(cg_entities + tmp_i4 + 0x988) = cg;
          goto LAB_0006dd09;
        }
      }
      else if (((g_unk_01047b04 == 0) ||
               ((*(int *)(cg_entities + tmp_i4 + 0x124) != 0 &&
                (*(int *)(cg_entities + tmp_i4 + 0x124) != 3)))) &&
              (*(uint *)(cg_entities + tmp_i2 * 0xaf8 + 4) < 0x3b)) {
        *(int *)(cg_entities + tmp_i2 * 0xaf8 + 0x988) = cg;
LAB_0006dd09:
        CG_CalcEntityLerpPositions(cg_entities + tmp_i2 * 0xaf8);
        CG_EntityEffects();
        CG_ProcessEntity();
        goto LAB_0006dd23;
      }
LAB_0006dc97:
      tmp_i1 = tmp_i1 + 1;
    } while (tmp_i1 < local_30);
LAB_0006dd45:
    if (0 < local_30) {
      tmp_i1 = 0;
      do {
        while ((tmp_i2 = *(int *)(local_34 + 0x5dc + tmp_i1 * 0x120) * 0xaf8,
               *(int *)(cg_entities + tmp_i2 + 4) != 4 || ((cg_entities[tmp_i2 + 0xf4] & 4) == 0))) {
          tmp_i1 = tmp_i1 + 1;
          if (local_30 <= tmp_i1) goto LAB_0006dda0;
        }
        CG_Mover_PostProcess_part_11();
        tmp_i1 = tmp_i1 + 1;
        local_30 = *(int *)(g_unk_01047b00 + 0x5d8);
        local_34 = g_unk_01047b00;
      } while (tmp_i1 < local_30);
    }
  }
LAB_0006dda0:
  CG_UpdateFlamethrowerSounds();
  return;
}

void CG_AddFlameSpriteToScene(int param_1,float param_2,float param_3)
{
  int tmp_i1;
  float *pfVar2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  float tmp_f9;
  float tmp_f10;
  float tmp_f11;
  int tmp_i12;
  int tmp_i13;
  uint8_t tmp_u14;
  int tmp_i15;
  long double tmp_l16;
  float tmp_f17;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  uint8_t local_28 [8];
  float local_20;
  
  if (0.0 <= param_3) {
    tmp_f17 = *(float *)(param_1 + 0x80) * 0.5;
    tmp_f6 = 6.0;
    if (6.0 <= tmp_f17) {
      tmp_f6 = tmp_f17;
    }
    tmp_i12 = CG_CullPointAndRadius(param_1 + 0x74,tmp_f6);
    if (tmp_i12 == 0) {
      tmp_f17 = floorf(param_2 * 20.0);
      tmp_i12 = 0x13;
      if ((int)ROUND(tmp_f17) < 0x14) {
        tmp_i12 = (int)ROUND(tmp_f17);
      }
      if (tmp_i12 < 0) {
        tmp_i12 = 0;
      }
      tmp_i13 = CG_PB_FindFreePolyBuffer((&flameShaders)[tmp_i12],4,6);
      tmp_i12 = *(int *)(tmp_i13 + 0x701c);
      tmp_u14 = (uint8_t)(short)ROUND(param_3 * 255.0);
      *(uint8_t *)(tmp_i13 + 8 + (tmp_i12 + 0x1804) * 4) = tmp_u14;
      *(uint8_t *)(tmp_i13 + 0x6019 + tmp_i12 * 4) = tmp_u14;
      *(uint8_t *)(tmp_i13 + 0x601a + tmp_i12 * 4) = tmp_u14;
      *(uint8_t *)(tmp_i13 + 0x601b + tmp_i12 * 4) = tmp_u14;
      *(uint32_t *)(tmp_i13 + 0x601c + tmp_i12 * 4) =
           *(uint32_t *)(tmp_i13 + 8 + (tmp_i12 + 0x1804) * 4);
      *(uint32_t *)(tmp_i13 + 0x6020 + *(int *)(tmp_i13 + 0x701c) * 4) =
           *(uint32_t *)(tmp_i13 + 0x6018 + *(int *)(tmp_i13 + 0x701c) * 4);
      *(uint32_t *)(tmp_i13 + 0x6024 + *(int *)(tmp_i13 + 0x701c) * 4) =
           *(uint32_t *)(tmp_i13 + 0x6018 + *(int *)(tmp_i13 + 0x701c) * 4);
      local_4c = *(float *)(g_unk_010afbcc + 0x24) * 1024.0 + *(float *)(g_unk_010afbcc + 0x18);
      local_48 = *(float *)(g_unk_010afbcc + 0x28) * 1024.0 + *(float *)(g_unk_010afbcc + 0x1c);
      local_44 = *(float *)(g_unk_010afbcc + 0x2c) * 1024.0 + *(float *)(g_unk_010afbcc + 0x20);
      ProjectPointOntoVector(param_1 + 0x74,(float *)(g_unk_010afbcc + 0x18),&local_4c,&local_40);
      local_34 = local_40 - *(float *)(g_unk_010afbcc + 0x18);
      local_30 = local_3c - *(float *)(g_unk_010afbcc + 0x1c);
      local_2c = local_38 - *(float *)(g_unk_010afbcc + 0x20);
      tmp_l16 = (long double)VectorNormalize(&local_34);
      if ((tmp_l16 != (long double)0) &&
         (0.0 <= local_2c * *(float *)(g_unk_010afbcc + 0x2c) +
                 local_30 * *(float *)(g_unk_010afbcc + 0x28) +
                 local_34 * *(float *)(g_unk_010afbcc + 0x24))) {
        if (rotatingFlames == 0) {
          rright = vright;
          g_unk_002bb420 = g_unk_002bb438;
          g_unk_002bb424 = g_unk_002bb43c;
          rup = vup;
          g_unk_002bb414 = g_unk_002bb42c;
          g_unk_002bb418 = g_unk_002bb430;
        }
        else {
          vectoangles(g_unk_010afbcc + 0x24,local_28);
          local_20 = local_20 + *(float *)(param_1 + 0x54);
          AngleVectors(local_28,0,&rright,&rup);
        }
        tmp_f17 = tmp_f6 / 1.481;
        tmp_f10 = -tmp_f17;
        tmp_f7 = -tmp_f6;
        tmp_f9 = rright * tmp_f7 + rup * tmp_f10 + *(float *)(param_1 + 0x74);
        tmp_f11 = g_unk_002bb420 * tmp_f7 + g_unk_002bb414 * tmp_f10 + *(float *)(param_1 + 0x78);
        tmp_i4 = *(int *)(tmp_i13 + 0x701c);
        tmp_i15 = tmp_i4 * 0x10;
        pfVar2 = (float *)(tmp_i13 + tmp_i15);
        tmp_i12 = tmp_i4 + 1;
        tmp_f7 = tmp_f7 * g_unk_002bb424 + g_unk_002bb418 * tmp_f10 + *(float *)(param_1 + 0x7c);
        *pfVar2 = tmp_f9;
        *(float *)(tmp_i13 + 4 + tmp_i15) = tmp_f11;
        *(float *)(tmp_i13 + 8 + tmp_i15) = tmp_f7;
        tmp_i3 = tmp_i13 + tmp_i4 * 8;
        tmp_f17 = tmp_f17 + tmp_f17;
        *(uint32_t *)(tmp_i3 + 0x4010) = 0;
        tmp_f8 = rup * tmp_f17;
        *(uint32_t *)(tmp_i13 + 0x4014 + tmp_i4 * 8) = 0;
        tmp_f8 = tmp_f8 + tmp_f9;
        tmp_f11 = g_unk_002bb414 * tmp_f17 + tmp_f11;
        tmp_f7 = tmp_f17 * g_unk_002bb418 + tmp_f7;
        pfVar2[4] = tmp_f8;
        *(float *)(tmp_i13 + 4 + tmp_i12 * 0x10) = tmp_f11;
        *(float *)(tmp_i13 + 8 + tmp_i12 * 0x10) = tmp_f7;
        tmp_f6 = tmp_f6 + tmp_f6;
        *(uint32_t *)(tmp_i3 + 0x4018) = 0;
        tmp_f17 = rright * tmp_f6;
        *(uint32_t *)(tmp_i13 + 0x4014 + tmp_i12 * 8) = 0x3f800000;
        tmp_i15 = tmp_i4 + 2;
        tmp_f17 = tmp_f17 + tmp_f8;
        tmp_f11 = g_unk_002bb420 * tmp_f6 + tmp_f11;
        tmp_f7 = tmp_f6 * g_unk_002bb424 + tmp_f7;
        pfVar2[8] = tmp_f17;
        *(float *)(tmp_i13 + 4 + tmp_i15 * 0x10) = tmp_f11;
        *(float *)(tmp_i13 + 8 + tmp_i15 * 0x10) = tmp_f7;
        tmp_f10 = tmp_f10 + tmp_f10;
        *(uint32_t *)(tmp_i3 + 0x4020) = 0x3f800000;
        *(uint32_t *)(tmp_i13 + 0x4014 + tmp_i15 * 8) = 0x3f800000;
        tmp_i1 = tmp_i4 + 3;
        tmp_f8 = g_unk_002bb414 * tmp_f10;
        tmp_f6 = g_unk_002bb418 * tmp_f10;
        pfVar2[0xc] = tmp_f10 * rup + tmp_f17;
        *(float *)(tmp_i13 + 4 + tmp_i1 * 0x10) = tmp_f8 + tmp_f11;
        *(float *)(tmp_i13 + 8 + tmp_i1 * 0x10) = tmp_f6 + tmp_f7;
        *(uint32_t *)(tmp_i3 + 0x4028) = 0x3f800000;
        *(uint32_t *)(tmp_i13 + 0x4014 + tmp_i1 * 8) = 0;
        tmp_i5 = *(int *)(tmp_i13 + 0xd038);
        tmp_i3 = tmp_i13 + tmp_i5 * 4;
        *(int *)(tmp_i3 + 0x7024) = tmp_i12;
        *(int *)(tmp_i3 + 0x7020) = tmp_i4;
        *(int *)(tmp_i3 + 0x7034) = tmp_i4;
        *(int *)(tmp_i3 + 0x7030) = tmp_i1;
        *(int *)(tmp_i3 + 0x7028) = tmp_i15;
        *(int *)(tmp_i3 + 0x702c) = tmp_i15;
        *(int *)(tmp_i13 + 0xd038) = tmp_i5 + 6;
        *(int *)(tmp_i13 + 0x701c) = tmp_i4 + 4;
      }
    }
  }
  return;
}

void CG_AddFlameToScene(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  long double tmp_l3;
  float tmp_f4;
  bool tmp_b5;
  float tmp_f6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  int tmp_i12;
  bool tmp_b13;
  long double tmp_l14;
  long double tmp_l15;
  double tmp_d16;
  double tmp_d17;
  float local_7c;
  int local_70;
  int local_68;
  uint32_t local_64;
  uint32_t local_60;
  float local_54;
  float local_50;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_b13 = *(int *)(centFlameInfo + *(int *)(param_1 + 0x1c) * 0x34 + 0x1c) == param_1;
  if ((tmp_b13) && ((cg_entities[*(int *)(param_1 + 0x1c) * 0xaf8 + 8] & 0x80) != 0)) {
    local_70 = *(int *)(param_1 + 0x20);
  }
  else {
    local_70 = g_unk_010906e0;
  }
  tmp_i9 = 0;
  local_20 = 0.0;
  local_24 = 0.0;
  local_28 = 0.0;
  tmp_i8 = *(int *)(param_1 + 8);
  local_60 = 0;
  local_54 = 1.0;
  local_7c = 0.0;
  tmp_f1 = 0.0;
  local_68 = 0;
  local_64 = 0;
  tmp_i12 = param_1;
  if (tmp_i8 == 0) goto LAB_0007f2f7;
LAB_0007efd0:
  tmp_i10 = tmp_i9;
  tmp_i11 = tmp_i8;
  if (*(int *)(tmp_i8 + 0x18) != 0) {
    tmp_i11 = 0;
    CG_FreeFlameChunk(tmp_i8);
    *(uint32_t *)(tmp_i12 + 8) = 0;
  }
  do {
    tmp_i9 = tmp_i12;
    tmp_i7 = local_70 - *(int *)(tmp_i9 + 0x20);
    tmp_i8 = tmp_i9 + 0x74;
    tmp_f4 = (float)tmp_i7;
    tmp_l14 = (long double)Distance(g_unk_010afbcc + 0x18,tmp_i8);
    if (tmp_i10 != 0) {
      if ((((long double)(float)(&centFlameStatus)[*(int *)(tmp_i9 + 0x1c) * 2] < (long double)1) &&
          (tmp_l15 = (long double)*(float *)(tmp_i10 + 0x6c) * (long double)*(float *)(tmp_i9 + 0x6c) +
                    (long double)*(float *)(tmp_i10 + 0x68) * (long double)*(float *)(tmp_i9 + 0x68) +
                    (long double)*(float *)(tmp_i10 + 100) * (long double)*(float *)(tmp_i9 + 100),
          tmp_l14 < (long double)1024.0)) && (tmp_l3 = (long double)1, tmp_l15 < tmp_l3)) {
        (&centFlameStatus)[*(int *)(tmp_i9 + 0x1c) * 2] =
             (float)((tmp_l3 - tmp_l15) * (long double)500.0 *
                     (tmp_l3 - tmp_l14 * (long double)0.0009765625) +
                    (long double)(float)(&centFlameStatus)[*(int *)(tmp_i9 + 0x1c) * 2]);
        if (tmp_l3 < (long double)(float)(&centFlameStatus)[*(int *)(tmp_i9 + 0x1c) * 2]) {
          (&centFlameStatus)[*(int *)(tmp_i9 + 0x1c) * 2] = 0x3f800000;
        }
      }
    }
    tmp_f2 = *(float *)(tmp_i9 + 0x80) / 20.0;
    local_28 = tmp_f2 * *(float *)(tmp_i9 + 0x74) + local_28;
    local_24 = tmp_f2 * *(float *)(tmp_i9 + 0x78) + local_24;
    local_20 = tmp_f2 * *(float *)(tmp_i9 + 0x7c) + local_20;
    tmp_f1 = *(float *)(tmp_i9 + 0x80) + tmp_f1;
    local_7c = tmp_f2 + local_7c;
    tmp_i10 = *(int *)(tmp_i9 + 0x58);
    tmp_i12 = tmp_i11;
    if (tmp_i10 == 0) {
      if (*(float *)(tmp_i9 + 0x50) < 1.0) {
        CG_AddFlameSpriteToScene(tmp_i9,*(uint32_t *)(tmp_i9 + 0x84),0x3f800000);
        tmp_i10 = *(int *)(tmp_i9 + 0x58);
        tmp_b5 = true;
        goto LAB_0007f6aa;
      }
      if (tmp_b13) goto LAB_0007f307;
LAB_0007f0ee:
      tmp_b5 = true;
LAB_0007f0f0:
      tmp_f2 = (float)*(int *)(tmp_i9 + 0x5c) * 0.2;
      if (tmp_f2 < tmp_f4) {
        if ((tmp_b5) && (tmp_i11 != 0)) {
          do {
            tmp_l14 = (long double)Distance(tmp_i8);
            if ((((long double)0.9 * (long double)*(float *)(tmp_i9 + 0x84) + (long double)0.1) *
                 (long double)*(float *)(tmp_i9 + 0x80) * (long double)0.35 <= tmp_l14) ||
               ((((long double)40.0 <=
                  ABS((long double)*(float *)(tmp_i9 + 0x80) - (long double)*(float *)(tmp_i11 + 0x80))
                 || (0xc6 < (*(int *)(tmp_i9 + 0x20) - *(int *)(tmp_i11 + 0x20)) + 99U)) ||
                (*(float *)(tmp_i9 + 0x4c) * *(float *)(tmp_i11 + 0x4c) +
                 *(float *)(tmp_i9 + 0x48) * *(float *)(tmp_i11 + 0x48) +
                 *(float *)(tmp_i9 + 0x44) * *(float *)(tmp_i11 + 0x44) <= 0.99)))) break;
            if (tmp_i11 != *(int *)(tmp_i9 + 8)) {
              CG_Error("CG_MergeFlameChunks: f2 doesn\'t follow f1, cannot merge\n");
            }
            *(uint32_t *)(tmp_i9 + 8) = *(uint32_t *)(tmp_i11 + 8);
            *(uint32_t *)(tmp_i11 + 8) = 0;
            *(uint32_t *)(tmp_i9 + 0x44) = *(uint32_t *)(tmp_i11 + 0x44);
            *(uint32_t *)(tmp_i9 + 0x48) = *(uint32_t *)(tmp_i11 + 0x48);
            *(uint32_t *)(tmp_i9 + 0x4c) = *(uint32_t *)(tmp_i11 + 0x4c);
            *(uint32_t *)(tmp_i9 + 0x34) = *(uint32_t *)(tmp_i11 + 0x34);
            *(uint32_t *)(tmp_i9 + 0x38) = *(uint32_t *)(tmp_i11 + 0x38);
            *(uint32_t *)(tmp_i9 + 0x3c) = *(uint32_t *)(tmp_i11 + 0x3c);
            *(uint32_t *)(tmp_i9 + 0x40) = *(uint32_t *)(tmp_i11 + 0x40);
            *(uint32_t *)(tmp_i9 + 0x50) = *(uint32_t *)(tmp_i11 + 0x50);
            *(uint32_t *)(tmp_i9 + 0x28) = *(uint32_t *)(tmp_i11 + 0x28);
            *(uint32_t *)(tmp_i9 + 0x80) = *(uint32_t *)(tmp_i11 + 0x80);
            *(uint32_t *)(tmp_i9 + 0x20) = *(uint32_t *)(tmp_i11 + 0x20);
            *(uint32_t *)(tmp_i9 + 0x24) = *(uint32_t *)(tmp_i11 + 0x24);
            CG_FreeFlameChunk(tmp_i11);
            tmp_i11 = *(int *)(tmp_i9 + 8);
          } while (tmp_i11 != 0);
          tmp_f2 = (float)*(int *)(tmp_i9 + 0x5c) * 0.2;
        }
        tmp_f4 = (tmp_f4 - tmp_f2) / (2125.0 - tmp_f2);
        tmp_f2 = (1.0 - tmp_f4) * 1.4;
        if (1.0 < tmp_f2) {
          tmp_f2 = 1.0;
        }
        CG_AddFlameSpriteToScene(tmp_i9,tmp_f4,tmp_f2);
        *(float *)(tmp_i9 + 0x30) = (*(float *)(tmp_i9 + 0x28) / 2125.0) / 0.3;
        tmp_i12 = tmp_i11;
      }
    }
    else if (tmp_b13) {
LAB_0007f307:
      if ((float)*(int *)(tmp_i9 + 0x5c) <= tmp_f4 * 0.5) {
        tmp_b5 = true;
      }
      else {
        tmp_b5 = (tmp_i9 != param_1 && local_68 != 0) && tmp_i11 != 0;
        if ((tmp_i9 != param_1 && local_68 != 0) && tmp_i11 != 0) {
          local_34 = *(float *)(tmp_i9 + 0x74) - *(float *)(local_68 + 0x74);
          local_30 = *(float *)(tmp_i9 + 0x78) - *(float *)(local_68 + 0x78);
          local_2c = *(float *)(tmp_i9 + 0x7c) - *(float *)(local_68 + 0x7c);
          tmp_l14 = (long double)VectorNormalize();
          if ((tmp_l14 < (long double)0.5 * (long double)*(float *)(tmp_i9 + 0x80)) ||
             (local_2c * *(float *)(tmp_i9 + 0x4c) +
              local_30 * *(float *)(tmp_i9 + 0x48) + local_34 * *(float *)(tmp_i9 + 0x44) < 0.0)) {
            if (*(int *)(tmp_i9 + 0x58) != 0) goto joined_r0x0007f6b6;
            (&g_unk_002bb464)[*(int *)(tmp_i9 + 0x1c) * 2] =
                 (float)(&g_unk_002bb464)[*(int *)(tmp_i9 + 0x1c) * 2] + 0.05;
            if (1.0 < (float)(&g_unk_002bb464)[*(int *)(tmp_i9 + 0x1c) * 2]) {
              (&g_unk_002bb464)[*(int *)(tmp_i9 + 0x1c) * 2] = 0x3f800000;
            }
            tmp_i10 = *(int *)(tmp_i9 + 0x58);
            goto LAB_0007f6aa;
          }
          tmp_i10 = *(int *)(tmp_i9 + 0x58);
        }
        if (tmp_i10 == 0) {
          (&g_unk_002bb464)[*(int *)(tmp_i9 + 0x1c) * 2] =
               (float)(&g_unk_002bb464)[*(int *)(tmp_i9 + 0x1c) * 2] + 0.05;
          if (1.0 < (float)(&g_unk_002bb464)[*(int *)(tmp_i9 + 0x1c) * 2]) {
            (&g_unk_002bb464)[*(int *)(tmp_i9 + 0x1c) * 2] = 0x3f800000;
          }
          tmp_i10 = *(int *)(tmp_i9 + 0x58);
        }
        tmp_f2 = 1.0;
        local_40 = 1.0;
        local_3c = 1.0;
        local_38 = 1.0;
        if ((float)tmp_i7 * 3.0 < (float)*(int *)(tmp_i9 + 0x5c)) {
          if (tmp_i10 != 0) {
            tmp_f2 = 2.0;
          }
          local_64 = CG_AddTrailJunc(local_64,0,
                                     (&nozzleShaders)
                                     [((g_unk_010906e0 / 0x32 >> 1) + g_unk_010906e0 / 0x32) % 8],
                                     g_unk_010906e0,0,tmp_i8,1,0x3f800000,0x3f800000,
                                     tmp_f2 * *(float *)(tmp_i9 + 0x80),0x432f0000,0xc,&local_40,
                                     &local_40,0x3f800000,0x40a00000);
          tmp_i10 = *(int *)(tmp_i9 + 0x58);
        }
        local_68 = tmp_i9;
        if (tmp_i10 != 0) goto joined_r0x0007f6b6;
        if (*(int *)(tmp_i9 + 8) == 0) {
LAB_0007f9f3:
          if (local_54 <= 0.0) goto LAB_0007f0ee;
          local_50 = 0.0;
        }
        else {
          local_50 = (float)tmp_i7 / 1.3;
          tmp_f2 = (float)*(int *)(tmp_i9 + 0x5c);
          if (tmp_f2 * 0.2 <= local_50) {
            tmp_f6 = tmp_f2 - tmp_f2 * 0.05;
            if (tmp_f6 <= local_50) {
              local_50 = 1.0 - (local_50 - tmp_f6) / (tmp_f2 * 0.05);
              goto LAB_0007f554;
            }
            local_50 = 1.0;
          }
          else {
            local_50 = local_50 / (tmp_f2 * 0.2);
LAB_0007f554:
            if (local_50 <= 0.0) goto LAB_0007f9f3;
          }
        }
        tmp_f2 = *(float *)(tmp_i9 + 0x80) * 0.5;
        tmp_f6 = *(float *)(tmp_i9 + 0x28) * 0.25;
        if (tmp_f2 < tmp_f6) {
          tmp_f6 = tmp_f2;
        }
        local_40 = local_50;
        local_3c = local_50;
        local_38 = local_50;
        local_60 = CG_AddTrailJunc(local_60,0,GHIDRA_FIELD(cgs, 68848, 4),g_unk_010906e0,1,tmp_i8,1,local_50,local_50
                                   ,tmp_f6,0x432f0000,0xe,&local_40,&local_40,0x3f000000,0x3fc00000);
        tmp_i10 = *(int *)(tmp_i9 + 0x58);
        tmp_b5 = false;
        local_54 = local_50;
      }
LAB_0007f6aa:
      if (tmp_i10 == 0) goto LAB_0007f0f0;
    }
joined_r0x0007f6b6:
    if (tmp_i12 == 0) {
      tmp_i8 = *(int *)(param_1 + 0x1c);
      if ((tmp_i8 != lastFlameOwner) || (cg != nextFlameLight)) {
        tmp_i12 = *(int *)(param_1 + 0x58);
        if (tmp_i12 == 0) {
          nextFlameLight = cg;
          lastFlameOwner = tmp_i8;
        }
        if (tmp_f1 < 80.0) {
          tmp_f1 = 80.0;
        }
        else if (500.0 < tmp_f1) {
          tmp_f1 = 500.0;
        }
        tmp_d17 = (double)g_unk_010906e0;
        tmp_d16 = sin(tmp_d17 / 50.0);
        tmp_d17 = cos(tmp_d17 / 43.0);
        tmp_f1 = (float)(((long double)tmp_d17 * (long double)tmp_d16 * (long double)0.2 + (long double)1)
                       * (long double)tmp_f1) * 0.005;
        if (2.0 < tmp_f1) {
          tmp_f1 = 2.0;
        }
        tmp_l14 = (long double)1 / (long double)local_7c;
        local_28 = (float)(tmp_l14 * (long double)local_28);
        local_24 = (float)(tmp_l14 * (long double)local_24);
        local_20 = (float)(tmp_l14 * (long double)local_20);
        if (tmp_i12 != 0) {
          trap_R_AddLightToScene(&local_28,0x42a00000,tmp_f1,0x3e4ccccd,0x3e570a3d,0x3f000000,0,0);
          return;
        }
        if ((tmp_b13) || (tmp_i8 == *(int *)(g_unk_01047b00 + 0xcc))) {
          trap_R_AddLightToScene(&local_28,0x43a00000,tmp_f1,0x3f800000,0x3f1a9aa2,0x3e54d4cc,0,0);
          return;
        }
      }
      return;
    }
    tmp_i8 = *(int *)(tmp_i12 + 8);
    if (tmp_i8 != 0) goto LAB_0007efd0;
LAB_0007f2f7:
    tmp_i11 = 0;
    tmp_i10 = tmp_i9;
  } while( true );
}

void CG_GenerateShaders(uint32_t param_1,uint32_t param_2,uint32_t param_3,int param_4,
                       uint32_t param_5,uint32_t param_6,uint32_t param_7,int param_8,
                       int param_9)

{
  bool tmp_b1;
  int tmp_i2;
  int tmp_i3;
  uint tmp_u4;
  uint tmp_u5;
  char *tmp_pc6;
  int tmp_i7;
  uint *tmp_pu8;
  uint *tmp_pu9;
  int tmp_i10;
  uint32_t local_220;
  uint local_21c [131];
  
  trap_FS_FOpenFile(param_1,&local_220,1);
  if (0 < param_4) {
    tmp_i10 = 1;
    do {
      tmp_i2 = (tmp_i10 + -1) / 100;
      tmp_i7 = (tmp_i10 + -1) % 100;
      tmp_i3 = tmp_i7 / 10;
      tmp_i7 = tmp_i7 % 10;
      if (param_8 == 0) {
        if (param_9 == 0) {
          tmp_pc6 = "";
        }
        else {
          tmp_pc6 = "\n\tnomipmap";
        }
        Com_sprintf(local_21c,0x200,
                    "%s%i\n{\n\tnofog%s\n\tallowCompress\n\tcull none\n\t{\n\t\tmap sprites/%s/spr%i%i%i.tga\n\t\tblendFunc %s %s\n%s\t}\n}\n"
                    ,param_2,tmp_i10,tmp_pc6,param_3,tmp_i2,tmp_i3,tmp_i7,param_5,param_6,param_7);
        tmp_pu9 = local_21c;
      }
      else {
        if (param_9 == 0) {
          tmp_pc6 = "";
        }
        else {
          tmp_pc6 = "\n\tnomipmaps";
        }
        Com_sprintf(local_21c,0x200,
                    "%s%i\n{\n\tnofog%s\n\tallowCompress\n\tcull none\n\t{\n\t\tmapcomp sprites/%s_lg/spr%i%i%i.tga\n\t\tmapnocomp sprites/%s/spr%i%i%i.tga\n\t\tblendFunc %s %s\n%s\t}\n}\n"
                    ,param_2,tmp_i10,tmp_pc6,param_3,tmp_i2,tmp_i3,tmp_i7,param_3,tmp_i2,tmp_i3,tmp_i7,
                    param_5,param_6,param_7);
        tmp_pu9 = local_21c;
      }
      do {
        tmp_pu8 = tmp_pu9;
        tmp_u4 = *tmp_pu8 + 0xfefefeff & ~*tmp_pu8;
        tmp_u5 = tmp_u4 & 0x80808080;
        tmp_pu9 = tmp_pu8 + 1;
      } while (tmp_u5 == 0);
      if ((tmp_u4 & 0x8080) == 0) {
        tmp_pu9 = (uint *)((int)tmp_pu8 + 6);
        tmp_u5 = tmp_u5 >> 0x10;
      }
      trap_FS_Write(local_21c,
                    (int)tmp_pu9 + ((-3 - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5)) - (int)local_21c),
                    local_220);
      tmp_b1 = tmp_i10 < param_4;
      tmp_i10 = tmp_i10 + 1;
    } while (tmp_b1);
  }
  trap_FS_FCloseFile(local_220);
  return;
}

void CG_AddFlameChunks(void)
{
  int *tmp_pi1;
  int *tmp_pi2;
  int *tmp_pi3;
  int *tmp_pi4;
  int *tmp_pi5;
  int *tmp_pi6;
  int tmp_i7;
  uint32_t *tmp_pu8;
  int *local_34;
  int *local_2c;
  int *local_24;
  int local_20;
  
  tmp_pi1 = activeFlameChunks;
  vright = *(uint32_t *)(g_unk_010afbcc + 0x30);
  g_unk_002bb438 = *(uint32_t *)(g_unk_010afbcc + 0x34);
  g_unk_002bb43c = *(uint32_t *)(g_unk_010afbcc + 0x38);
  vup = *(uint32_t *)(g_unk_010afbcc + 0x3c);
  g_unk_002bb42c = *(uint32_t *)(g_unk_010afbcc + 0x40);
  g_unk_002bb430 = *(uint32_t *)(g_unk_010afbcc + 0x44);
  tmp_pu8 = &centFlameStatus;
  for (tmp_i7 = 0x800; tmp_i7 != 0; tmp_i7 = tmp_i7 + -1) {
    *tmp_pu8 = 0;
    tmp_pu8 = tmp_pu8 + 1;
  }
joined_r0x0007fe4d:
  do {
    tmp_pi2 = headFlameChunks;
    if (tmp_pi1 == (int *)0x0) {
      while (tmp_pi1 = tmp_pi2, tmp_pi1 != (int *)0x0) {
        tmp_pi2 = (int *)tmp_pi1[3];
        if (tmp_pi1[6] == 0) {
          if ((tmp_pi1[0x16] == 0) || (*(int **)(centFlameInfo + tmp_pi1[7] * 0x34 + 0x1c) == tmp_pi1))
          {
            CG_AddFlameToScene(tmp_pi1);
          }
        }
        else {
          if (*(int **)(centFlameInfo + tmp_pi1[7] * 0x34 + 0x1c) == tmp_pi1) {
            *(uint32_t *)(centFlameInfo + tmp_pi1[7] * 0x34 + 0x1c) = 0;
            *(uint32_t *)(centFlameInfo + tmp_pi1[7] * 0x34) = 0;
          }
          tmp_pi3 = (int *)tmp_pi1[2];
          if (tmp_pi3 != (int *)0x0) {
            tmp_pi4 = (int *)tmp_pi3[2];
            if (tmp_pi4 != (int *)0x0) {
              local_34 = (int *)tmp_pi4[2];
              if (local_34 == (int *)0x0) {
                local_34 = freeFlameChunks;
              }
              else {
                tmp_pi5 = (int *)local_34[2];
                if (tmp_pi5 == (int *)0x0) {
                  local_2c = (int *)numFlameChunksInuse;
                }
                else {
                  local_2c = (int *)tmp_pi5[2];
                  if (local_2c == (int *)0x0) {
                    local_2c = freeFlameChunks;
                    local_24 = (int *)numFlameChunksInuse;
                  }
                  else {
                    local_24 = (int *)local_2c[2];
                    if (local_24 == (int *)0x0) {
                      local_24 = freeFlameChunks;
                      local_20 = numFlameChunksInuse;
                    }
                    else {
                      if (local_24[2] != 0) {
                        CG_FreeFlameChunk(local_24[2]);
                        local_24[2] = 0;
                      }
                      local_24[5] = 0;
                      local_24[6] = 0;
                      if (*local_24 != 0) {
                        *(int *)(*local_24 + 4) = local_24[1];
                      }
                      if ((int *)local_24[1] != (int *)0x0) {
                        *(int *)local_24[1] = *local_24;
                      }
                      if (local_24 == activeFlameChunks) {
                        activeFlameChunks = (int *)*local_24;
                      }
                      tmp_pi6 = (int *)local_24[3];
                      if (local_24 == headFlameChunks) {
                        headFlameChunks = tmp_pi6;
                      }
                      if (tmp_pi6 != (int *)0x0) {
                        tmp_pi6[4] = local_24[4];
                      }
                      if (local_24[4] != 0) {
                        *(int *)(local_24[4] + 0xc) = local_24[3];
                      }
                      local_24[3] = 0;
                      local_24[4] = 0;
                      local_24[1] = 0;
                      *local_24 = (int)freeFlameChunks;
                      if (freeFlameChunks != (int *)0x0) {
                        freeFlameChunks[1] = (int)local_24;
                      }
                      local_20 = numFlameChunksInuse + -1;
                      local_2c[2] = 0;
                    }
                    local_2c[5] = 0;
                    local_2c[6] = 0;
                    if (*local_2c != 0) {
                      *(int *)(*local_2c + 4) = local_2c[1];
                    }
                    if ((int *)local_2c[1] != (int *)0x0) {
                      *(int *)local_2c[1] = *local_2c;
                    }
                    if (local_2c == activeFlameChunks) {
                      activeFlameChunks = (int *)*local_2c;
                      tmp_pi6 = (int *)local_2c[3];
                    }
                    else {
                      tmp_pi6 = (int *)local_2c[3];
                    }
                    if (local_2c == headFlameChunks) {
                      headFlameChunks = tmp_pi6;
                    }
                    if (tmp_pi6 != (int *)0x0) {
                      tmp_pi6[4] = local_2c[4];
                    }
                    if (local_2c[4] != 0) {
                      *(int *)(local_2c[4] + 0xc) = local_2c[3];
                    }
                    local_2c[3] = 0;
                    local_2c[4] = 0;
                    local_2c[1] = 0;
                    *local_2c = (int)local_24;
                    if (local_24 != (int *)0x0) {
                      local_24[1] = (int)local_2c;
                    }
                    tmp_pi5[2] = 0;
                    local_24 = (int *)(local_20 + -1);
                  }
                  tmp_pi5[5] = 0;
                  tmp_pi5[6] = 0;
                  if (*tmp_pi5 != 0) {
                    *(int *)(*tmp_pi5 + 4) = tmp_pi5[1];
                  }
                  if ((int *)tmp_pi5[1] != (int *)0x0) {
                    *(int *)tmp_pi5[1] = *tmp_pi5;
                  }
                  if (tmp_pi5 == activeFlameChunks) {
                    activeFlameChunks = (int *)*tmp_pi5;
                  }
                  tmp_pi6 = (int *)tmp_pi5[3];
                  if (tmp_pi5 == headFlameChunks) {
                    headFlameChunks = tmp_pi6;
                  }
                  if (tmp_pi6 != (int *)0x0) {
                    tmp_pi6[4] = tmp_pi5[4];
                  }
                  if (tmp_pi5[4] != 0) {
                    *(int *)(tmp_pi5[4] + 0xc) = tmp_pi5[3];
                  }
                  tmp_pi5[3] = 0;
                  tmp_pi5[4] = 0;
                  tmp_pi5[1] = 0;
                  *tmp_pi5 = (int)local_2c;
                  if (local_2c != (int *)0x0) {
                    local_2c[1] = (int)tmp_pi5;
                  }
                  local_2c = (int *)((int)local_24 + -1);
                  local_34[2] = 0;
                  freeFlameChunks = tmp_pi5;
                }
                local_34[5] = 0;
                local_34[6] = 0;
                if (*local_34 != 0) {
                  *(int *)(*local_34 + 4) = local_34[1];
                }
                if ((int *)local_34[1] != (int *)0x0) {
                  *(int *)local_34[1] = *local_34;
                }
                if (local_34 == activeFlameChunks) {
                  activeFlameChunks = (int *)*local_34;
                }
                tmp_pi5 = (int *)local_34[3];
                if (local_34 == headFlameChunks) {
                  headFlameChunks = tmp_pi5;
                }
                if (tmp_pi5 != (int *)0x0) {
                  tmp_pi5[4] = local_34[4];
                }
                if (local_34[4] != 0) {
                  *(int *)(local_34[4] + 0xc) = local_34[3];
                }
                local_34[3] = 0;
                local_34[4] = 0;
                local_34[1] = 0;
                *local_34 = (int)freeFlameChunks;
                if (freeFlameChunks != (int *)0x0) {
                  freeFlameChunks[1] = (int)local_34;
                }
                tmp_pi4[2] = 0;
                numFlameChunksInuse = (int)local_2c + -1;
              }
              tmp_pi4[5] = 0;
              tmp_pi4[6] = 0;
              if (*tmp_pi4 != 0) {
                *(int *)(*tmp_pi4 + 4) = tmp_pi4[1];
              }
              if ((int *)tmp_pi4[1] != (int *)0x0) {
                *(int *)tmp_pi4[1] = *tmp_pi4;
              }
              if (tmp_pi4 == activeFlameChunks) {
                activeFlameChunks = (int *)*tmp_pi4;
              }
              tmp_pi5 = (int *)tmp_pi4[3];
              if (tmp_pi4 == headFlameChunks) {
                headFlameChunks = tmp_pi5;
              }
              if (tmp_pi5 != (int *)0x0) {
                tmp_pi5[4] = tmp_pi4[4];
              }
              if (tmp_pi4[4] != 0) {
                *(int *)(tmp_pi4[4] + 0xc) = tmp_pi4[3];
              }
              tmp_pi4[3] = 0;
              tmp_pi4[4] = 0;
              tmp_pi4[1] = 0;
              *tmp_pi4 = (int)local_34;
              if (local_34 != (int *)0x0) {
                local_34[1] = (int)tmp_pi4;
              }
              numFlameChunksInuse = numFlameChunksInuse + -1;
              tmp_pi3[2] = 0;
              freeFlameChunks = tmp_pi4;
            }
            tmp_pi3[5] = 0;
            tmp_pi3[6] = 0;
            if (*tmp_pi3 != 0) {
              *(int *)(*tmp_pi3 + 4) = tmp_pi3[1];
            }
            if ((int *)tmp_pi3[1] != (int *)0x0) {
              *(int *)tmp_pi3[1] = *tmp_pi3;
            }
            if (tmp_pi3 == activeFlameChunks) {
              activeFlameChunks = (int *)*tmp_pi3;
            }
            tmp_pi4 = (int *)tmp_pi3[3];
            if (tmp_pi3 == headFlameChunks) {
              headFlameChunks = tmp_pi4;
            }
            if (tmp_pi4 != (int *)0x0) {
              tmp_pi4[4] = tmp_pi3[4];
            }
            if (tmp_pi3[4] != 0) {
              *(int *)(tmp_pi3[4] + 0xc) = tmp_pi3[3];
            }
            tmp_pi3[3] = 0;
            tmp_pi3[4] = 0;
            tmp_pi3[1] = 0;
            *tmp_pi3 = (int)freeFlameChunks;
            if (freeFlameChunks != (int *)0x0) {
              freeFlameChunks[1] = (int)tmp_pi3;
            }
            numFlameChunksInuse = numFlameChunksInuse + -1;
            tmp_pi1[2] = 0;
            freeFlameChunks = tmp_pi3;
          }
          tmp_pi1[5] = 0;
          tmp_pi1[6] = 0;
          if (*tmp_pi1 != 0) {
            *(int *)(*tmp_pi1 + 4) = tmp_pi1[1];
          }
          if ((int *)tmp_pi1[1] != (int *)0x0) {
            *(int *)tmp_pi1[1] = *tmp_pi1;
          }
          if (tmp_pi1 == activeFlameChunks) {
            activeFlameChunks = (int *)*tmp_pi1;
          }
          tmp_pi3 = (int *)tmp_pi1[3];
          if (tmp_pi1 == headFlameChunks) {
            headFlameChunks = tmp_pi3;
          }
          if (tmp_pi3 != (int *)0x0) {
            tmp_pi3[4] = tmp_pi1[4];
          }
          if (tmp_pi1[4] != 0) {
            *(int *)(tmp_pi1[4] + 0xc) = tmp_pi1[3];
          }
          tmp_pi1[3] = 0;
          tmp_pi1[4] = 0;
          tmp_pi1[1] = 0;
          *tmp_pi1 = (int)freeFlameChunks;
          if (freeFlameChunks != (int *)0x0) {
            freeFlameChunks[1] = (int)tmp_pi1;
          }
          numFlameChunksInuse = numFlameChunksInuse + -1;
          freeFlameChunks = tmp_pi1;
        }
      }
      return;
    }
    if (tmp_pi1[6] == 0) {
      if ((tmp_pi1[9] < g_unk_010906e0) ||
         ((tmp_pi1[0x16] != 0 && (tmp_pi1[0x17] < g_unk_010906e0 - tmp_pi1[8])))) {
        tmp_pi1[6] = 1;
        tmp_pi1 = (int *)*tmp_pi1;
        goto joined_r0x0007fe4d;
      }
      CG_MoveFlameChunk(tmp_pi1);
      tmp_pi1[0x21] = (int)((float)(g_unk_010906e0 - tmp_pi1[8]) / (float)(tmp_pi1[9] - tmp_pi1[8]));
    }
    tmp_pi1 = (int *)*tmp_pi1;
  } while( true );
}

void CG_AddEmitter(int param_1)
{
  float local_18;
  float local_14;
  float local_10;
  
  if (g_unk_010906e0 < *(int *)(param_1 + 0x1ac)) {
    return;
  }
  local_18 = *(float *)(param_1 + 0x50) * 30.0;
  local_14 = *(float *)(param_1 + 0x54) * 30.0;
  local_10 = *(float *)(param_1 + 0x58) * 30.0;
  CG_Particle_OilParticle
            (GHIDRA_FIELD(cgs, 68516, 4),param_1 + 0x2c,&local_18,15000,*(uint32_t *)(param_1 + 0x1a4));
  *(int *)(param_1 + 0x1ac) = g_unk_010906e0 + 0x32;
  return;
}

void CG_AddFragment(int *param_1)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  uint tmp_u6;
  int *tmp_pi7;
  uint tmp_u8;
  int tmp_i9;
  int tmp_i10;
  uint32_t tmp_u11;
  int *tmp_pi12;
  uint32_t *tmp_pu13;
  int *tmp_pi14;
  uint32_t *tmp_pu15;
  int *tmp_pi16;
  bool tmp_b17;
  long double tmp_l18;
  uint8_t *local_1ac;
  uint local_1a4;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  uint8_t local_140 [8];
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  float local_108 [26];
  uint8_t local_a0 [144];
  
  tmp_i1 = g_unk_010906e0;
  tmp_i5 = param_1[5];
  if ((param_1[0x5c] == 0) || (param_1[0x5d] < tmp_i5)) {
    param_1[0x5d] = tmp_i5;
    tmp_i9 = param_1[0x67];
    tmp_i10 = tmp_i5 + -1000;
    if (5000 < tmp_i5 - tmp_i1) {
      tmp_i10 = tmp_i5 + -5000;
    }
    param_1[0x5c] = tmp_i10;
    if (tmp_i9 != 0) goto LAB_0008db97;
LAB_0008dcb7:
    tmp_f3 = 0.0;
    tmp_b17 = false;
    if ((*(byte *)(param_1 + 3) & 8) != 0) {
LAB_0008dcbd:
      if ((GHIDRA_FIELD(cg_smokeparticles, 12, 4) != 0) && (tmp_i5 = rand(), tmp_i5 == (tmp_i5 / 5) * 5)) {
        tmp_i5 = param_1[4];
        tmp_i1 = param_1[5];
        tmp_i9 = g_unk_010906e0 - tmp_i5;
        tmp_u6 = 0;
        do {
          *(uint32_t *)((int)local_108 + tmp_u6) = 0;
          *(uint32_t *)((int)local_108 + tmp_u6 + 4) = 0;
          tmp_u6 = tmp_u6 + 8;
        } while (tmp_u6 < 0xe8);
        *(uint32_t *)((int)local_108 + tmp_u6) = 0;
        CG_PositionEntityOnTag(local_108,param_1 + 0x26,"tag_flash",0,0);
        CG_ParticleImpactSmokePuffExtended
                  (GHIDRA_FIELD(cgs, 68876, 4),local_a0,1000,8,0x14,0x14,
                   (1.0 - (float)tmp_i9 / (float)(tmp_i1 - tmp_i5)) * 0.25,0x41000000);
      }
    }
  }
  else {
    tmp_i9 = param_1[0x67];
    if (tmp_i9 == 0) goto LAB_0008dcb7;
LAB_0008db97:
    if ((g_unk_010906e0 <= tmp_i9) || (param_1[0x68] <= g_unk_010906e0)) goto LAB_0008dcb7;
    tmp_f3 = 1.0 - (float)(g_unk_010906e0 - tmp_i9) / (float)(param_1[0x68] - tmp_i9);
    if (tmp_f3 < 0.0) {
      tmp_i5 = 0;
      tmp_f3 = 0.0;
    }
    else if (tmp_f3 <= 1.0) {
      tmp_i5 = (int)ROUND(tmp_f3 * 20.0);
    }
    else {
      tmp_i5 = 0x14;
      tmp_f3 = 1.0;
    }
    tmp_b17 = true;
    trap_S_AddLoopingSound(param_1 + 0x40,&vec3_origin,GHIDRA_FIELD(cgs, 69532, 4),tmp_i5,0);
    if ((*(byte *)(param_1 + 3) & 8) != 0) goto LAB_0008dcbd;
    tmp_b17 = true;
  }
  if (param_1[8] == 0) {
    if (!tmp_b17) goto LAB_0008dc59;
    tmp_pi14 = param_1 + 0x26;
    tmp_u6 = 0;
    do {
      tmp_u8 = tmp_u6;
      tmp_u11 = *(uint32_t *)((int)param_1 + tmp_u8 + 0x9c);
      *(uint32_t *)((int)local_108 + tmp_u8) = *(uint32_t *)((int)param_1 + tmp_u8 + 0x98);
      *(uint32_t *)((int)local_108 + tmp_u8 + 4) = tmp_u11;
      tmp_u6 = tmp_u8 + 8;
    } while (tmp_u6 < 0xe8);
    local_154 = 0.0;
    *(uint32_t *)((int)local_108 + tmp_u8 + 8) = *(uint32_t *)((int)tmp_pi14 + tmp_u6);
    local_158 = 0.0;
    local_150 = 1.0;
    param_1[0x59] = 0;
    param_1[0x5a] = 0;
    param_1[0x5b] = 0x3f800000;
    *(char *)((int)param_1 + 0x14f) = (char)(short)ROUND(tmp_f3 * 255.0);
    param_1[0x52] = GHIDRA_FIELD(cgs, 68852, 4);
    trap_R_AddRefEntityToScene(tmp_pi14);
    param_1[0x52] = GHIDRA_FIELD(cgs, 68856, 4);
    trap_R_AddRefEntityToScene(tmp_pi14);
    tmp_u6 = 0;
    do {
      tmp_u11 = *(uint32_t *)((int)local_108 + tmp_u6 + 4);
      *(uint32_t *)((int)param_1 + tmp_u6 + 0x98) = *(uint32_t *)((int)local_108 + tmp_u6);
      *(uint32_t *)((int)param_1 + tmp_u6 + 0x9c) = tmp_u11;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < 0xe8);
  }
  else {
    if (param_1[8] == 9) {
      if (tmp_b17) {
        tmp_pi14 = param_1 + 0x26;
        tmp_u6 = 0;
        do {
          tmp_u8 = tmp_u6;
          tmp_u11 = *(uint32_t *)((int)param_1 + tmp_u8 + 0x9c);
          *(uint32_t *)((int)local_108 + tmp_u8) = *(uint32_t *)((int)param_1 + tmp_u8 + 0x98);
          *(uint32_t *)((int)local_108 + tmp_u8 + 4) = tmp_u11;
          tmp_u6 = tmp_u8 + 8;
        } while (tmp_u6 < 0xe8);
        local_154 = 0.0;
        *(uint32_t *)((int)local_108 + tmp_u8 + 8) = *(uint32_t *)((int)tmp_pi14 + tmp_u6);
        local_158 = 0.0;
        local_150 = 1.0;
        param_1[0x59] = 0;
        param_1[0x5a] = 0;
        param_1[0x5b] = 0x3f800000;
        *(char *)((int)param_1 + 0x14f) = (char)(short)ROUND(tmp_f3 * 255.0);
        param_1[0x52] = GHIDRA_FIELD(cgs, 68852, 4);
        trap_R_AddRefEntityToScene(tmp_pi14);
        param_1[0x52] = GHIDRA_FIELD(cgs, 68856, 4);
        trap_R_AddRefEntityToScene(tmp_pi14);
        tmp_u6 = 0;
        do {
          tmp_u8 = tmp_u6;
          *(uint32_t *)((int)param_1 + tmp_u8 + 0x98) = *(uint32_t *)((int)local_108 + tmp_u8);
          *(uint32_t *)((int)param_1 + tmp_u8 + 0x9c) = *(uint32_t *)((int)local_108 + tmp_u8 + 4)
          ;
          tmp_u6 = tmp_u8 + 8;
        } while (tmp_u6 < 0xe8);
        *(uint32_t *)((int)tmp_pi14 + tmp_u6) = *(uint32_t *)((int)local_108 + tmp_u8 + 8);
      }
      trap_R_AddRefEntityToScene(param_1 + 0x26);
      local_164 = (float)param_1[0x40];
      local_160 = (float)param_1[0x41];
      local_15c = (float)param_1[0x42] - 5.0;
      CG_Trace(local_140,param_1 + 0x40,0,0,&local_164,0xffffffff,0x10081);
      if (local_138 != 1.0) {
        return;
      }
      param_1[0x10] = 0;
      param_1[0xf] = 0;
      param_1[0xe] = 0;
      param_1[0x19] = 0;
      param_1[0x18] = 0;
      param_1[0x17] = 0;
      param_1[8] = 6;
    }
    local_1ac = local_140;
    BG_EvaluateTrajectory(param_1 + 8,g_unk_010906e0,&local_164,0,0xffffffff);
    if (tmp_b17) {
      local_158 = (float)param_1[0x40] - local_164;
      local_154 = (float)param_1[0x41] - local_160;
      local_150 = (float)param_1[0x42] - local_15c;
      tmp_l18 = (long double)VectorLengthSquared(&local_158);
      if (tmp_l18 == (long double)0) {
        local_150 = 1.0;
        tmp_u11 = GHIDRA_FIELD(cgs, 69516, 4);
      }
      else {
        VectorNormalize(&local_158);
        tmp_u11 = GHIDRA_FIELD(cgs, 69520, 4);
      }
      trap_S_AddLoopingSound(&local_164,&vec3_origin,tmp_u11,(int)ROUND(tmp_f3 * 76.5),0);
    }
    CG_Trace(local_1ac,param_1 + 0x40,0,0,&local_164,0xffffffff,1);
    if (local_138 == 1.0) {
      param_1[0x40] = (int)local_164;
      param_1[0x41] = (int)local_160;
      param_1[0x42] = (int)local_15c;
      if (((*(byte *)(param_1 + 3) & 2) == 0) && (param_1[0x11] != 2)) {
        AnglesToAxis(param_1 + 0x14,param_1 + 0x2d);
        tmp_f2 = (float)param_1[0x6c];
      }
      else {
        BG_EvaluateTrajectory(param_1 + 0x11,g_unk_010906e0,local_108,1,0xffffffff);
        AnglesToAxis(local_108,param_1 + 0x2d);
        tmp_f2 = (float)param_1[0x6c];
      }
      if ((tmp_f2 != 0.0) && (tmp_f2 != 1.0)) {
        param_1[0x3f] = 1;
        param_1[0x33] = (int)((float)param_1[0x33] * tmp_f2);
        param_1[0x34] = (int)((float)param_1[0x34] * tmp_f2);
        param_1[0x35] = (int)((float)param_1[0x35] * tmp_f2);
        param_1[0x30] = (int)((float)param_1[0x30] * tmp_f2);
        param_1[0x31] = (int)((float)param_1[0x31] * tmp_f2);
        param_1[0x32] = (int)((float)param_1[0x32] * tmp_f2);
        param_1[0x2d] = (int)((float)param_1[0x2d] * tmp_f2);
        param_1[0x2e] = (int)((float)param_1[0x2e] * tmp_f2);
        param_1[0x2f] = (int)(tmp_f2 * (float)param_1[0x2f]);
      }
      if (tmp_b17) {
        tmp_pi14 = param_1 + 0x26;
        tmp_u6 = 0;
        do {
          tmp_u8 = tmp_u6;
          tmp_u11 = *(uint32_t *)((int)param_1 + tmp_u8 + 0x9c);
          *(uint32_t *)((int)local_108 + tmp_u8) = *(uint32_t *)((int)param_1 + tmp_u8 + 0x98);
          *(uint32_t *)((int)local_108 + tmp_u8 + 4) = tmp_u11;
          tmp_u6 = tmp_u8 + 8;
        } while (tmp_u6 < 0xe8);
        *(uint32_t *)((int)local_108 + tmp_u8 + 8) = *(uint32_t *)((int)tmp_pi14 + tmp_u6);
        param_1[0x59] = (int)local_158;
        *(char *)((int)param_1 + 0x14f) = (char)(short)ROUND(tmp_f3 * 255.0);
        param_1[0x5a] = (int)local_154;
        param_1[0x5b] = (int)local_150;
        param_1[0x52] = GHIDRA_FIELD(cgs, 68852, 4);
        trap_R_AddRefEntityToScene(tmp_pi14);
        param_1[0x52] = GHIDRA_FIELD(cgs, 68856, 4);
        trap_R_AddRefEntityToScene(tmp_pi14);
        tmp_u6 = 0;
        do {
          tmp_u8 = tmp_u6;
          tmp_u11 = *(uint32_t *)((int)local_108 + tmp_u8 + 4);
          *(uint32_t *)((int)param_1 + tmp_u8 + 0x98) = *(uint32_t *)((int)local_108 + tmp_u8);
          *(uint32_t *)((int)param_1 + tmp_u8 + 0x9c) = tmp_u11;
          tmp_u6 = tmp_u8 + 8;
        } while (tmp_u6 < 0xe8);
        *(uint32_t *)((int)tmp_pi14 + tmp_u6) = *(uint32_t *)((int)local_108 + tmp_u8 + 8);
      }
      trap_R_AddRefEntityToScene(param_1 + 0x26);
      if (param_1[0x25] != 1) {
        return;
      }
      CG_BloodTrail(param_1);
      return;
    }
    tmp_i5 = CG_PointContents(&local_134,0);
    if (tmp_i5 < 0) {
LAB_0008e7c2:
      tmp_i5 = *param_1;
joined_r0x0008e7c7:
      if (tmp_i5 == 0) {
        CG_Error("CG_FreeLocalEntity: not active");
      }
      localEntCount = localEntCount + -1;
      *(int *)(*param_1 + 4) = param_1[1];
      *(int *)param_1[1] = *param_1;
      tmp_pi14 = cg_freeLocalEntities;
      cg_freeLocalEntities = param_1;
      param_1[1] = (int)tmp_pi14;
      return;
    }
    CG_FragmentBounceSound(param_1,local_1ac);
    CG_ReflectVelocity(param_1,local_1ac);
    if ((*(byte *)(param_1 + 3) & 0x10) == 0) {
      if (param_1[0x6b] != 0) {
        tmp_u6 = param_1[0x69];
        if (0x3f < tmp_u6) {
          CG_Error("Bad clientNum on player entity");
        }
        tmp_i5 = CG_CharacterForClientinfo(tmp_u6 * 0x1a4 + 0x10f926c,0);
        if (-1 < param_1[0x6b]) {
          tmp_i1 = 0;
          do {
            tmp_pi14 = cg_activeLocalEntities;
            if (cg_freeLocalEntities == (int *)0x0) {
              if (*cg_activeLocalEntities == 0) {
                CG_Error("CG_FreeLocalEntity: not active");
              }
              localEntCount = localEntCount + -1;
              *(int *)(*tmp_pi14 + 4) = tmp_pi14[1];
              *(int *)tmp_pi14[1] = *tmp_pi14;
              tmp_pi14[1] = (int)cg_freeLocalEntities;
              tmp_pi7 = cg_freeLocalEntities;
            }
            else {
              tmp_pi7 = (int *)cg_freeLocalEntities[1];
              tmp_pi14 = cg_freeLocalEntities;
            }
            localEntCount = localEntCount + 1;
            tmp_b17 = ((uint)tmp_pi14 & 1) != 0;
            tmp_u6 = 0x1bc;
            tmp_pi12 = tmp_pi14;
            cg_freeLocalEntities = tmp_pi7;
            if (tmp_b17) {
              *(uint8_t *)tmp_pi14 = 0;
              tmp_pi12 = (int *)((int)tmp_pi14 + 1);
              tmp_u6 = 0x1bb;
            }
            if (((uint)tmp_pi12 & 2) != 0) {
              *(uint16_t *)tmp_pi12 = 0;
              tmp_u6 = tmp_u6 - 2;
              tmp_pi12 = (int *)((int)tmp_pi12 + 2);
            }
            tmp_u8 = 0;
            do {
              *(uint32_t *)((int)tmp_pi12 + tmp_u8) = 0;
              *(uint32_t *)((int)tmp_pi12 + tmp_u8 + 4) = 0;
              tmp_u8 = tmp_u8 + 8;
            } while (tmp_u8 < (tmp_u6 & 0xfffffff8));
            tmp_pu13 = (uint32_t *)((int)tmp_pi12 + tmp_u8);
            if ((tmp_u6 & 4) != 0) {
              *tmp_pu13 = 0;
              tmp_pu13 = tmp_pu13 + 1;
            }
            if ((tmp_u6 & 2) != 0) {
              *(uint16_t *)tmp_pu13 = 0;
              tmp_pu13 = (uint32_t *)((int)tmp_pu13 + 2);
            }
            if (tmp_b17) {
              *(uint8_t *)tmp_pu13 = 0;
            }
            tmp_u6 = 0x1b4;
            tmp_pi14[1] = (int)g_unk_00f69564;
            *tmp_pi14 = (int)&cg_activeLocalEntities;
            *g_unk_00f69564 = (int)tmp_pi14;
            tmp_pi7 = tmp_pi14 + 2;
            tmp_b17 = ((uint)tmp_pi7 & 1) != 0;
            tmp_pi12 = param_1 + 2;
            g_unk_00f69564 = tmp_pi14;
            if (tmp_b17) {
              tmp_pi7 = (int *)((int)tmp_pi14 + 9);
              tmp_u6 = 0x1b3;
              tmp_pi12 = (int *)((int)param_1 + 9);
              *(char *)(tmp_pi14 + 2) = (char)param_1[2];
            }
            tmp_pi16 = tmp_pi7;
            if (((uint)tmp_pi7 & 2) != 0) {
              tmp_i9 = *tmp_pi12;
              tmp_pi16 = (int *)((int)tmp_pi7 + 2);
              tmp_pi12 = (int *)((int)tmp_pi12 + 2);
              tmp_u6 = tmp_u6 - 2;
              *(short *)tmp_pi7 = (short)tmp_i9;
            }
            local_1a4 = tmp_u6 & 0xfffffff8;
            tmp_u8 = 0;
            do {
              tmp_u11 = *(uint32_t *)((int)tmp_pi12 + tmp_u8);
              *(uint32_t *)((int)tmp_pi16 + tmp_u8 + 4) = *(uint32_t *)((int)tmp_pi12 + tmp_u8 + 4);
              *(uint32_t *)((int)tmp_pi16 + tmp_u8) = tmp_u11;
              tmp_u8 = tmp_u8 + 8;
            } while (tmp_u8 < local_1a4);
            tmp_pu15 = (uint32_t *)((int)tmp_pi16 + tmp_u8);
            tmp_pu13 = (uint32_t *)((int)tmp_pi12 + tmp_u8);
            tmp_i9 = 0;
            if ((tmp_u6 & 4) != 0) {
              *tmp_pu15 = *tmp_pu13;
              tmp_i9 = 4;
            }
            if ((tmp_u6 & 2) != 0) {
              *(uint16_t *)((int)tmp_pu15 + tmp_i9) = *(uint16_t *)((int)tmp_pu13 + tmp_i9);
              tmp_i9 = tmp_i9 + 2;
            }
            if (tmp_b17) {
              *(uint8_t *)((int)tmp_pu15 + tmp_i9) = *(uint8_t *)((int)tmp_pu13 + tmp_i9);
            }
            tmp_i9 = tmp_pi14[0x6b];
            tmp_pi14[0x6b] = tmp_i9 + -1;
            if (tmp_i9 < 2) {
              tmp_i9 = rand();
              tmp_pi14[0x28] = *(int *)(tmp_i5 + 0x7a8 + (tmp_i9 % 2) * 4);
            }
            else {
              tmp_i9 = rand();
              tmp_pi14[0x28] = *(int *)(tmp_i5 + 0x7a8 + (tmp_i9 % 4) * 4);
            }
            tmp_i9 = g_unk_010906e0 + 5000;
            tmp_i10 = rand();
            tmp_pi14[5] = tmp_i9 + tmp_i10 % 2000;
            if ((float)tmp_pi14[0x6c] * 0.8 < 0.7) {
              tmp_pi14[0x6c] = 0x3f333333;
              tmp_pi14[0x25] = 0;
            }
            else {
              tmp_pi14[0x6c] = (int)((float)tmp_pi14[0x6c] * 0.8);
            }
            tmp_pi7 = tmp_pi14 + 0xe;
            VectorNormalize2(tmp_pi7,local_108);
            tmp_f3 = (float)tmp_i1;
            tmp_pi14[0xb] = (int)((float)param_1[0x6c] * 4.0 * tmp_f3 * local_108[0] + local_134);
            tmp_pi14[0xc] = (int)((float)param_1[0x6c] * 4.0 * tmp_f3 * local_108[1] + local_130);
            tmp_pi14[0xd] = (int)((float)param_1[0x6c] * 4.0 * tmp_f3 * local_108[2] + local_12c);
            tmp_f3 = (float)tmp_pi14[0xe];
            tmp_i9 = rand();
            tmp_f2 = (float)(&bytedirs)[(tmp_i9 % 0xa2) * 3];
            tmp_l18 = (long double)VectorLength(tmp_pi7);
            tmp_pi14[0xe] = (int)(float)((long double)0.3 * tmp_l18 * (long double)tmp_f2 +
                                       (long double)tmp_f3);
            tmp_f3 = (float)tmp_pi14[0xf];
            tmp_i9 = rand();
            tmp_f2 = (float)(&g_unk_00149844)[(tmp_i9 % 0xa2) * 3];
            tmp_l18 = (long double)VectorLength(tmp_pi7);
            tmp_pi14[0xf] = (int)(float)((long double)0.3 * tmp_l18 * (long double)tmp_f2 +
                                       (long double)tmp_f3);
            tmp_f3 = (float)tmp_pi14[0x10];
            tmp_i9 = rand();
            tmp_f2 = (float)(&g_unk_00149848)[(tmp_i9 % 0xa2) * 3];
            tmp_l18 = (long double)VectorLength(tmp_pi7);
            tmp_i1 = tmp_i1 + 1;
            tmp_pi14[0x10] =
                 (int)(float)((long double)0.3 * tmp_l18 * (long double)tmp_f2 + (long double)tmp_f3);
          } while (tmp_i1 <= param_1[0x6b]);
        }
        goto LAB_0008e7c2;
      }
    }
    else {
      param_1[0x17] = (int)((float)param_1[0x17] * 0.8);
      param_1[0x18] = (int)((float)param_1[0x18] * 0.8);
      param_1[0x19] = (int)((float)param_1[0x19] * 0.8);
      if (param_1[0x6b] != 0) {
        tmp_f3 = (float)param_1[0x6c] * 0.8;
        if (tmp_f3 < 0.7) {
          tmp_f3 = 0.7;
        }
        tmp_pi14 = param_1 + 0xe;
        VectorNormalize2(tmp_pi14,local_108);
        tmp_f2 = tmp_f3 * 4.0;
        local_14c = tmp_f2 * local_108[0] + local_134;
        local_148 = tmp_f2 * local_108[1] + local_130;
        local_144 = tmp_f2 * local_108[2] + local_12c;
        tmp_f2 = (float)param_1[0xe];
        tmp_i5 = rand();
        tmp_f4 = (float)(&bytedirs)[(tmp_i5 % 0xa2) * 3];
        tmp_l18 = (long double)VectorLength(tmp_pi14);
        local_108[0] = (float)((long double)0.3 * tmp_l18 * (long double)tmp_f4 + (long double)tmp_f2);
        tmp_f2 = (float)param_1[0xf];
        tmp_i5 = rand();
        tmp_f4 = (float)(&g_unk_00149844)[(tmp_i5 % 0xa2) * 3];
        tmp_l18 = (long double)VectorLength(tmp_pi14);
        local_108[1] = (float)((long double)0.3 * tmp_l18 * (long double)tmp_f4 + (long double)tmp_f2);
        tmp_f2 = (float)param_1[0x10];
        tmp_i5 = rand();
        tmp_f4 = (float)(&g_unk_00149848)[(tmp_i5 % 0xa2) * 3];
        tmp_l18 = (long double)VectorLength(tmp_pi14);
        local_108[2] = (float)((long double)0.3 * tmp_l18 * (long double)tmp_f4 + (long double)tmp_f2);
        tmp_u11 = trap_R_GetShaderFromModel(param_1[0x28],0,0);
        CG_Explodef(&local_14c,local_108,(int)ROUND(tmp_f3 * 50.0),0,0,0,tmp_u11);
        tmp_i5 = *param_1;
        goto joined_r0x0008e7c7;
      }
    }
    if ((param_1[8] == 0) && (param_1[0x24] == 1)) {
      CG_FragmentBounceMark(param_1,local_1ac);
    }
    if (!tmp_b17) goto LAB_0008dc59;
    tmp_pi14 = param_1 + 0x26;
    tmp_u6 = 0;
    do {
      tmp_u8 = tmp_u6;
      tmp_u11 = *(uint32_t *)((int)param_1 + tmp_u8 + 0x9c);
      *(uint32_t *)((int)local_108 + tmp_u8) = *(uint32_t *)((int)param_1 + tmp_u8 + 0x98);
      *(uint32_t *)((int)local_108 + tmp_u8 + 4) = tmp_u11;
      tmp_u6 = tmp_u8 + 8;
    } while (tmp_u6 < 0xe8);
    *(uint32_t *)((int)local_108 + tmp_u8 + 8) = *(uint32_t *)((int)tmp_pi14 + tmp_u6);
    param_1[0x59] = (int)local_158;
    *(char *)((int)param_1 + 0x14f) = (char)(short)ROUND(tmp_f3 * 255.0);
    param_1[0x5a] = (int)local_154;
    param_1[0x5b] = (int)local_150;
    param_1[0x52] = GHIDRA_FIELD(cgs, 68852, 4);
    trap_R_AddRefEntityToScene(tmp_pi14);
    param_1[0x52] = GHIDRA_FIELD(cgs, 68856, 4);
    trap_R_AddRefEntityToScene(tmp_pi14);
    tmp_u6 = 0;
    do {
      tmp_u11 = *(uint32_t *)((int)local_108 + tmp_u6 + 4);
      *(uint32_t *)((int)param_1 + tmp_u6 + 0x98) = *(uint32_t *)((int)local_108 + tmp_u6);
      *(uint32_t *)((int)param_1 + tmp_u6 + 0x9c) = tmp_u11;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < 0xe8);
  }
  *(uint32_t *)((int)param_1 + tmp_u6 + 0x98) = *(uint32_t *)((int)local_108 + tmp_u6);
LAB_0008dc59:
  trap_R_AddRefEntityToScene(param_1 + 0x26);
  return;
}

void CG_AddMovingTracer(int param_1)
{
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  BG_EvaluateTrajectory(param_1 + 0x20,g_unk_010906e0,&local_30,0,0xffffffff);
  VectorNormalize2(param_1 + 0x38,&local_18);
  local_24 = local_18 * (float)GHIDRA_FIELD(cg_tracerLength, 8, 4) + local_30;
  local_20 = local_14 * (float)GHIDRA_FIELD(cg_tracerLength, 8, 4) + local_2c;
  local_1c = (float)GHIDRA_FIELD(cg_tracerLength, 8, 4) * local_10 + local_28;
  CG_DrawTracer(&local_30,&local_24);
  return;
}

void CG_AddSparkElements(int *param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  float local_84;
  int local_60;
  int local_5c;
  int local_58;
  uint8_t local_54 [4];
  int local_50;
  float local_4c;
  int local_48;
  int local_44;
  int local_40;
  uint32_t uStack_14;
  
  uStack_14 = 0x8efc9;
  local_84 = (float)(g_unk_010906e0 - g_unk_010906dc);
  do {
    BG_EvaluateTrajectory(param_1 + 8,g_unk_010906e0,&local_60,0,0xffffffff);
    CG_Trace(local_54,param_1 + 0x40,0,0,&local_60,0xffffffff,0x6000001);
    if (local_50 != 0) {
      local_48 = local_60;
      local_4c = 1.0;
      local_44 = local_5c;
      local_40 = local_58;
    }
    param_1[0x40] = local_48;
    param_1[0x41] = local_44;
    param_1[0x42] = local_40;
    tmp_i3 = param_1[5] - param_1[4];
    local_84 = (float)g_unk_010906dc * local_4c + local_84;
    tmp_f2 = (float)(g_unk_010906e0 - param_1[4]) / (float)tmp_i3;
    tmp_f1 = tmp_f2 + tmp_f2;
    if (400 < tmp_i3) {
      tmp_f1 = tmp_f1 + tmp_f1;
    }
    tmp_i3 = CG_AddSparkJunc(param_1[0x62],param_1,param_1[0x52],param_1 + 0x40,200,1.0 - tmp_f2,0,
                            tmp_f1 * 1.5,tmp_f1 * 1.5);
    param_1[0x62] = tmp_i3;
    if (local_4c < 1.0) {
      if (*param_1 == 0) {
        CG_Error("CG_FreeLocalEntity: not active");
      }
      localEntCount = localEntCount + -1;
      *(int *)(*param_1 + 4) = param_1[1];
      *(int *)param_1[1] = *param_1;
      tmp_i3 = (int)cg_freeLocalEntities;
      cg_freeLocalEntities = param_1;
      param_1[1] = tmp_i3;
      return;
    }
    if (local_4c == 1.0) {
      return;
    }
  } while (local_84 < (float)g_unk_010906e0);
  return;
}

void CG_AddFuseSparkElements(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint32_t tmp_u5;
  
  tmp_f1 = (float)*(int *)(param_1 + 0x184);
  if (tmp_f1 < (float)g_unk_010906e0) {
    do {
      BG_EvaluateTrajectory(param_1 + 0x20,(int)ROUND(tmp_f1),param_1 + 0x100,0,0xffffffff);
      tmp_f4 = (float)(*(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x10));
      tmp_f2 = (tmp_f1 - (float)*(int *)(param_1 + 0x10)) / tmp_f4;
      tmp_f3 = 1.0 - tmp_f2;
      tmp_u5 = CG_AddTrailJunc(*(uint32_t *)(param_1 + 0x188),param_1,GHIDRA_FIELD(cgs, 68840, 4),
                              (int)ROUND(tmp_f1),0,param_1 + 0x100,(int)ROUND(tmp_f2 * tmp_f4 * 0.5),
                              0x3f800000,0,tmp_f3,tmp_f3,0x10,whiteColor_12126,whiteColor_12126,0,0);
      *(uint32_t *)(param_1 + 0x188) = tmp_u5;
      tmp_f1 = tmp_f1 + 10.0;
      *(int *)(param_1 + 0x184) = (int)ROUND(tmp_f1);
    } while (tmp_f1 < (float)g_unk_010906e0);
  }
  return;
}

void CG_AddBloodElements(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  float local_88;
  int local_74;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint8_t local_54 [4];
  int local_50;
  float local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t uStack_14;
  
  uStack_14 = 0x8f3ce;
  local_74 = 5;
  local_88 = (float)(g_unk_010906e0 - g_unk_010906dc);
  do {
    BG_EvaluateTrajectory(param_1 + 0x20,g_unk_010906e0,&local_60,0,0xffffffff);
    CG_Trace(local_54,param_1 + 0x100,0,0,&local_60,0xffffffff,0x6000001);
    if (local_50 != 0) {
      local_48 = local_60;
      local_4c = 1.0;
      local_44 = local_5c;
      local_40 = local_58;
    }
    *(uint32_t *)(param_1 + 0x100) = local_48;
    *(uint32_t *)(param_1 + 0x104) = local_44;
    *(uint32_t *)(param_1 + 0x108) = local_40;
    local_88 = (float)g_unk_010906dc * local_4c + local_88;
    tmp_f1 = 1.0 - (float)(g_unk_010906e0 - *(int *)(param_1 + 0x10)) /
                  (float)(*(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x10));
    tmp_u2 = CG_AddSparkJunc(*(uint32_t *)(param_1 + 0x188),param_1,GHIDRA_FIELD(cgs, 68100, 4),param_1 + 0x100,
                            200,tmp_f1,tmp_f1,0x40400000,0x40a00000);
    *(uint32_t *)(param_1 + 0x188) = tmp_u2;
    if (local_4c < 1.0) {
      CG_ReflectVelocity(param_1,local_54);
      *(int *)(param_1 + 0x24) = (int)ROUND(local_88);
    }
  } while (((local_4c != 1.0) && (local_88 < (float)g_unk_010906e0)) &&
          (local_74 = local_74 + -1, local_74 != 0));
  return;
}

void CG_AddDebrisElements(int *param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  long double tmp_l5;
  int local_60;
  int local_5c;
  int local_58;
  uint8_t local_54 [4];
  int local_50;
  float local_4c;
  int local_48;
  int local_44;
  int local_40;
  
  tmp_i4 = param_1[0x61] + 0x32;
  if (tmp_i4 < g_unk_010906e0) {
    do {
      BG_EvaluateTrajectory(param_1 + 8,tmp_i4,&local_60,0,0xffffffff);
      CG_Trace(local_54,param_1 + 0x40,0,0,&local_60,0xffffffff,0x6000001);
      if (local_50 != 0) {
        local_48 = local_60;
        local_4c = 1.0;
        local_44 = local_5c;
        local_40 = local_58;
      }
      param_1[0x40] = local_48;
      param_1[0x41] = local_44;
      param_1[0x42] = local_40;
      if ((*(byte *)(param_1 + 0x65) & 1) != 0) {
        tmp_f1 = 1.0;
        tmp_f2 = (1.0 - (float)(tmp_i4 - param_1[4]) / (float)(param_1[5] - param_1[4])) * 0.5 + 0.5;
        if (local_4c != 1.0) {
          tmp_f1 = 0.0;
        }
        tmp_i3 = CG_AddSmokeJunc(param_1[99],param_1,GHIDRA_FIELD(cgs, 68844, 4),param_1 + 0x40,
                                (int)ROUND(tmp_f2 * 2000.0),tmp_f1 * tmp_f2,0x3f800000,
                                (float)(int)ROUND(tmp_f2 * 60.0));
        param_1[99] = tmp_i3;
      }
      if (local_4c < 1.0) {
        CG_ReflectVelocity(param_1,local_54);
        tmp_l5 = (long double)VectorLengthSquared(param_1 + 0xe);
        if (tmp_l5 < (long double)1) {
          if (*param_1 == 0) {
            CG_Error("CG_FreeLocalEntity: not active");
          }
          localEntCount = localEntCount + -1;
          *(int *)(*param_1 + 4) = param_1[1];
          *(int *)param_1[1] = *param_1;
          tmp_i4 = (int)cg_freeLocalEntities;
          cg_freeLocalEntities = param_1;
          param_1[1] = tmp_i4;
          return;
        }
        param_1[9] = tmp_i4;
      }
      param_1[0x61] = tmp_i4;
      tmp_i4 = tmp_i4 + 0x32;
    } while (tmp_i4 < g_unk_010906e0);
  }
  return;
}

void CG_AddFadeRGB(int param_1)
{
  float tmp_f1;
  
  tmp_f1 = (float)(*(int *)(param_1 + 0x14) - g_unk_010906e0) * *(float *)(param_1 + 0x1c) * 255.0;
  *(char *)(param_1 + 0x14c) = (char)(short)ROUND(*(float *)(param_1 + 0x6c) * tmp_f1);
  *(char *)(param_1 + 0x14d) = (char)(short)ROUND(*(float *)(param_1 + 0x70) * tmp_f1);
  *(char *)(param_1 + 0x14e) = (char)(short)ROUND(*(float *)(param_1 + 0x74) * tmp_f1);
  *(char *)(param_1 + 0x14f) = (char)(short)ROUND(tmp_f1 * *(float *)(param_1 + 0x78));
  trap_R_AddRefEntityToScene(param_1 + 0x98);
  return;
}

void CG_AddConstRGB(int param_1)
{
  *(char *)(param_1 + 0x14c) = (char)(short)ROUND(*(float *)(param_1 + 0x6c) * 255.0);
  *(char *)(param_1 + 0x14d) = (char)(short)ROUND(*(float *)(param_1 + 0x70) * 255.0);
  *(char *)(param_1 + 0x14e) = (char)(short)ROUND(*(float *)(param_1 + 0x74) * 255.0);
  *(char *)(param_1 + 0x14f) = (char)(short)ROUND(*(float *)(param_1 + 0x78) * 255.0);
  trap_R_AddRefEntityToScene(param_1 + 0x98);
  return;
}

void CG_AddLocalEntities(void)
{
  float tmp_f1;
  int *tmp_pi2;
  uint32_t tmp_u3;
  int *tmp_pi4;
  int tmp_i5;
  float tmp_f6;
  uint tmp_u7;
  uint tmp_u8;
  int *tmp_pi9;
  int tmp_i10;
  long double tmp_l11;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float local_110;
  float local_10c;
  float local_108 [44];
  int local_58;
  uint8_t local_54;
  uint8_t local_53;
  uint8_t local_52;
  uint8_t local_51;
  float local_44;
  uint32_t uStack_14;
  
  uStack_14 = 0x8fa29;
  tmp_pi9 = cg_activeLocalEntities;
  if ((int **)cg_activeLocalEntities != &cg_activeLocalEntities) {
    do {
      tmp_pi2 = (int *)*tmp_pi9;
      tmp_i10 = tmp_pi9[5];
      tmp_pi4 = tmp_pi2;
      if (tmp_i10 <= g_unk_010906e0) {
joined_r0x0008fc32:
        if (tmp_pi4 == (int *)0x0) {
          CG_Error("CG_FreeLocalEntity: not active");
        }
        localEntCount = localEntCount + -1;
        *(int *)(*tmp_pi9 + 4) = tmp_pi9[1];
        *(int *)tmp_pi9[1] = *tmp_pi9;
        tmp_pi9[1] = (int)cg_freeLocalEntities;
        cg_freeLocalEntities = tmp_pi9;
        goto joined_r0x000902b8;
      }
      switch(tmp_pi9[2]) {
      case 1:
        if (-1 < tmp_pi9[0x52]) {
          trap_R_AddRefEntityToScene(tmp_pi9 + 0x26);
          tmp_i10 = tmp_pi9[5];
        }
        tmp_f1 = (float)(g_unk_010906e0 - tmp_pi9[4]) / (float)(tmp_i10 - tmp_pi9[4]);
        if (tmp_f1 < 0.5) {
          tmp_f1 = 1.0;
        }
        else {
          tmp_f1 = tmp_f1 - 0.5;
          tmp_f1 = 1.0 - (tmp_f1 + tmp_f1);
        }
        trap_R_AddLightToScene
                  (tmp_pi9 + 0x40,0x44000000,tmp_f1 * (float)tmp_pi9[0x20],tmp_pi9[0x21],tmp_pi9[0x22],
                   tmp_pi9[0x23],0,0);
        break;
      case 2:
        tmp_u8 = 0;
        do {
          tmp_u7 = tmp_u8;
          tmp_u3 = *(uint32_t *)((int)tmp_pi9 + tmp_u7 + 0x98);
          *(uint32_t *)((int)local_108 + tmp_u7 + 4) = *(uint32_t *)((int)tmp_pi9 + tmp_u7 + 0x9c);
          *(uint32_t *)((int)local_108 + tmp_u7) = tmp_u3;
          tmp_u8 = tmp_u7 + 8;
        } while (tmp_u8 < 0xe8);
        *(uint32_t *)((int)local_108 + tmp_u8) = *(uint32_t *)((int)tmp_pi9 + tmp_u7 + 0xa0);
        tmp_f1 = (float)(tmp_pi9[5] - g_unk_010906e0) / (float)(tmp_pi9[5] - tmp_pi9[4]);
        if (tmp_f1 <= 1.0) {
          local_51 = (uint8_t)(short)ROUND(tmp_f1 * 255.0 * 0.33);
          tmp_f1 = 1.0 - tmp_f1;
          local_44 = tmp_f1 * 42.0 + 30.0;
        }
        else {
          local_44 = 30.0;
          local_51 = 0x54;
          tmp_f1 = 0.0;
        }
        local_54 = 0xff;
        local_53 = 0xff;
        local_52 = 0xff;
        local_108[0] = 2.8026e-45;
        local_108[0x1a] = tmp_f1 * (float)tmp_pi9[0xe] + (float)tmp_pi9[0xb];
        local_108[0x1b] = tmp_f1 * (float)tmp_pi9[0xf] + (float)tmp_pi9[0xc];
        local_108[0x1c] = tmp_f1 * (float)tmp_pi9[0x10] + (float)tmp_pi9[0xd];
        if (-1 < local_58) {
          trap_R_AddRefEntityToScene(local_108);
        }
        tmp_f1 = (float)(g_unk_010906e0 - tmp_pi9[4]) / (float)(tmp_pi9[5] - tmp_pi9[4]);
        if (tmp_f1 < 0.5) {
          tmp_f1 = 1.0;
        }
        else {
          tmp_f1 = tmp_f1 - 0.5;
          tmp_f1 = 1.0 - (tmp_f1 + tmp_f1);
        }
        trap_R_AddLightToScene
                  (local_108 + 0x1a,0x43a00000,tmp_f1,tmp_pi9[0x21],tmp_pi9[0x22],tmp_pi9[0x23],0,0);
      case 0:
_L543:
        break;
      case 3:
        CG_AddFragment(tmp_pi9);
        break;
      case 4:
        tmp_i5 = tmp_pi9[6];
        if ((tmp_pi9[4] < tmp_i5) && (g_unk_010906e0 < tmp_i5)) {
          tmp_f1 = 1.0 - (float)(tmp_i5 - g_unk_010906e0) / (float)(tmp_i5 - tmp_pi9[4]);
        }
        else {
          tmp_f1 = (float)(tmp_i10 - g_unk_010906e0) * (float)tmp_pi9[7];
        }
        if ((tmp_pi9[3] & 4U) == 0) {
          *(char *)((int)tmp_pi9 + 0x14f) = (char)(short)ROUND(tmp_f1 * 255.0 * (float)tmp_pi9[0x1e]);
        }
        if ((tmp_pi9[3] & 1U) == 0) {
          tmp_pi9[0x57] = (int)((1.0 - (float)(tmp_i10 - g_unk_010906e0) * (float)tmp_pi9[7]) *
                               (float)tmp_pi9[0x1f] + 8.0);
        }
        BG_EvaluateTrajectory(tmp_pi9 + 8,g_unk_010906e0,tmp_pi9 + 0x40,0,0xffffffff);
        local_108[0] = (float)tmp_pi9[0x40] - *(float *)(g_unk_010afbcc + 0x18);
        local_108[1] = (float)tmp_pi9[0x41] - *(float *)(g_unk_010afbcc + 0x1c);
        local_108[2] = (float)tmp_pi9[0x42] - *(float *)(g_unk_010afbcc + 0x20);
        tmp_l11 = (long double)VectorLength(local_108);
        if (tmp_l11 < (long double)(float)tmp_pi9[0x1f]) goto LAB_0008ffc2;
        trap_R_AddRefEntityToScene(tmp_pi9 + 0x26);
        break;
      case 5:
        tmp_f1 = (float)(tmp_i10 - g_unk_010906e0) * (float)tmp_pi9[7];
        tmp_f6 = 1.0 - tmp_f1;
        *(char *)((int)tmp_pi9 + 0x14f) = (char)(short)ROUND(tmp_f1 * 255.0 * (float)tmp_pi9[0x1e]);
        local_108[2] = (float)tmp_pi9[0xd] - tmp_f6 * (float)tmp_pi9[0x10];
        tmp_pi9[0x42] = (int)local_108[2];
        tmp_pi9[0x57] = (int)(tmp_f6 * (float)tmp_pi9[0x1f] + 16.0);
        local_108[0] = (float)tmp_pi9[0x40] - *(float *)(g_unk_010afbcc + 0x18);
        local_108[1] = (float)tmp_pi9[0x41] - *(float *)(g_unk_010afbcc + 0x1c);
        local_108[2] = local_108[2] - *(float *)(g_unk_010afbcc + 0x20);
        tmp_l11 = (long double)VectorLength(local_108);
        if (tmp_l11 < (long double)(float)tmp_pi9[0x1f]) goto LAB_0008ffc2;
        goto LAB_0008fe40;
      case 6:
        tmp_f1 = (float)(tmp_i10 - g_unk_010906e0) * (float)tmp_pi9[7] * 255.0;
        goto LAB_0008fe66;
      case 7:
        tmp_f1 = 255.0;
LAB_0008fe66:
        *(char *)(tmp_pi9 + 0x53) = (char)(short)ROUND((float)tmp_pi9[0x1b] * tmp_f1);
        *(char *)((int)tmp_pi9 + 0x14d) = (char)(short)ROUND((float)tmp_pi9[0x1c] * tmp_f1);
        *(char *)((int)tmp_pi9 + 0x14e) = (char)(short)ROUND((float)tmp_pi9[0x1d] * tmp_f1);
        *(char *)((int)tmp_pi9 + 0x14f) = (char)(short)ROUND(tmp_f1 * (float)tmp_pi9[0x1e]);
LAB_0008fe40:
        trap_R_AddRefEntityToScene(tmp_pi9 + 0x26);
        break;
      case 8:
        tmp_f1 = (float)(tmp_i10 - g_unk_010906e0) * (float)tmp_pi9[7];
        *(char *)((int)tmp_pi9 + 0x14f) = (char)(short)ROUND(tmp_f1 * 255.0 * (float)tmp_pi9[0x1e]);
        if ((*(byte *)(tmp_pi9 + 3) & 1) == 0) {
          tmp_pi9[0x57] = (int)((1.0 - tmp_f1) * (float)tmp_pi9[0x1f] + 8.0);
        }
        local_108[0] = (float)tmp_pi9[0x40] - *(float *)(g_unk_010afbcc + 0x18);
        local_108[1] = (float)tmp_pi9[0x41] - *(float *)(g_unk_010afbcc + 0x1c);
        local_108[2] = (float)tmp_pi9[0x42] - *(float *)(g_unk_010afbcc + 0x20);
        tmp_l11 = (long double)VectorLength(local_108);
        if ((long double)(float)tmp_pi9[0x1f] <= tmp_l11) goto LAB_0008fe40;
LAB_0008ffc2:
        tmp_pi4 = (int *)*tmp_pi9;
        goto joined_r0x0008fc32;
      case 9:
        CG_AddSparkElements(tmp_pi9);
        break;
      case 10:
        CG_AddDebrisElements(tmp_pi9);
        break;
      case 0xb:
        CG_AddBloodElements(tmp_pi9);
        break;
      case 0xc:
        CG_AddFuseSparkElements(tmp_pi9);
        break;
      case 0xd:
        BG_EvaluateTrajectory(tmp_pi9 + 8,g_unk_010906e0,&local_120,0,0xffffffff);
        VectorNormalize2(tmp_pi9 + 0xe,local_108);
        local_114 = local_108[0] * (float)GHIDRA_FIELD(cg_tracerLength, 8, 4) + local_120;
        local_110 = local_108[1] * (float)GHIDRA_FIELD(cg_tracerLength, 8, 4) + local_11c;
        local_10c = (float)GHIDRA_FIELD(cg_tracerLength, 8, 4) * local_108[2] + local_118;
        CG_DrawTracer(&local_120,&local_114);
        break;
      case 0xe:
        if (g_unk_010906e0 < tmp_pi9[0x6b]) goto _L543;
        local_108[0] = (float)tmp_pi9[0x14] * 30.0;
        local_108[1] = (float)tmp_pi9[0x15] * 30.0;
        local_108[2] = (float)tmp_pi9[0x16] * 30.0;
        CG_Particle_OilParticle(GHIDRA_FIELD(cgs, 68516, 4),tmp_pi9 + 0xb,local_108,15000,tmp_pi9[0x69]);
        tmp_pi9[0x6b] = g_unk_010906e0 + 0x32;
        break;
      default:
        CG_Error("Bad leType: %i",tmp_pi9[2]);
      }
joined_r0x000902b8:
      tmp_pi9 = tmp_pi2;
    } while ((int **)tmp_pi2 != &cg_activeLocalEntities);
  }
  return;
}

void CG_AddToTeamChat(char *param_1,int param_2)
{
  char tmp_c1;
  void *tmp_pc2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  char *tmp_pc5;
  uint32_t tmp_u6;
  char tmp_c7;
  int tmp_i8;
  char *tmp_pc9;
  char *tmp_pc10;
  int tmp_i11;
  int local_28;
  
  tmp_u3 = g_unk_010906e0;
  if ((int)GHIDRA_FIELD(cg_teamChatHeight, 12, 4) < 8) {
    local_28 = GHIDRA_FIELD(cg_teamChatHeight, 12, 4);
    if ((int)GHIDRA_FIELD(cg_teamChatHeight, 12, 4) < 1) {
      GHIDRA_FIELD(cgs, 66532, 4) = 0;
      GHIDRA_FIELD(cgs, 66536, 4) = 0;
      return;
    }
  }
  else {
    local_28 = 8;
  }
  if ((int)GHIDRA_FIELD(cg_teamChatTime, 12, 4) < 1) {
    GHIDRA_FIELD(cgs, 66536, 4) = 0;
    GHIDRA_FIELD(cgs, 66532, 4) = 0;
    return;
  }
  tmp_pc10 = (char *)0x0;
  tmp_i11 = 0;
  tmp_i8 = ((int)GHIDRA_FIELD(cgs, 66532, 4) % local_28) * 0xd3;
  tmp_pc4 = cgs + tmp_i8 + 0xfd0c;
  cgs[tmp_i8 + 0xfd0c] = 0;
  tmp_c1 = '7';
  if (param_2 == -2) {
    while (tmp_c7 = *param_1, tmp_c7 != '\0') {
      while( true ) {
        tmp_pc5 = tmp_pc4;
        tmp_pc9 = param_1;
        if (0x45 < tmp_i11) {
          if (tmp_pc10 != (char *)0x0) {
            tmp_i8 = (int)tmp_pc4 - (int)tmp_pc10;
            tmp_pc4 = tmp_pc4 + -tmp_i8;
            param_1 = param_1 + (1 - tmp_i8);
          }
          *tmp_pc4 = '\0';
          *(uint32_t *)(cgs + ((int)GHIDRA_FIELD(cgs, 66532, 4) % local_28) * 4 + 0x103a4) = tmp_u3;
          *(uint32_t *)(cgs + ((int)GHIDRA_FIELD(cgs, 66532, 4) % local_28) * 4 + 0x103c4) = 0;
          GHIDRA_FIELD(cgs, 66532, 4) = GHIDRA_FIELD(cgs, 66532, 4) + 1;
          tmp_i8 = ((int)GHIDRA_FIELD(cgs, 66532, 4) % local_28) * 0xd3;
          cgs[tmp_i8 + 0xfd0c] = 0x5e;
          cgs[tmp_i8 + 0xfd0d] = tmp_c1;
          if (param_1 == (char *)0x0) goto LAB_00096f90;
          tmp_c7 = *param_1;
          tmp_pc5 = cgs + tmp_i8 + 0xfd0e;
          tmp_pc10 = (char *)0x0;
          tmp_i11 = 0;
          tmp_pc9 = param_1;
        }
        if (tmp_c7 != '^') break;
        if ((tmp_pc9[1] == '\0') || (tmp_pc9[1] == '^')) goto LAB_00096fb6;
        *tmp_pc5 = '^';
        param_1 = tmp_pc9 + 2;
        tmp_pc4 = tmp_pc5 + 2;
        tmp_c1 = tmp_pc9[1];
        tmp_pc5[1] = tmp_c1;
        tmp_c7 = *param_1;
        if (tmp_c7 == '\0') goto LAB_00097090;
      }
      if (tmp_c7 == ' ') {
        tmp_pc10 = tmp_pc5;
      }
LAB_00096fb6:
      *tmp_pc5 = tmp_c7;
      tmp_i11 = tmp_i11 + 1;
      tmp_pc4 = tmp_pc5 + 1;
      param_1 = tmp_pc9 + 1;
    }
LAB_00097090:
    *tmp_pc4 = '\0';
    tmp_u6 = 0;
  }
  else {
    while (tmp_c7 = *param_1, tmp_c7 != '\0') {
LAB_00096e27:
      tmp_pc5 = tmp_pc4;
      tmp_pc9 = param_1;
      if (0x45 < tmp_i11) {
        if (tmp_pc10 != (char *)0x0) {
          tmp_i8 = (int)tmp_pc4 - (int)tmp_pc10;
          tmp_pc4 = tmp_pc4 + -tmp_i8;
          param_1 = param_1 + (1 - tmp_i8);
        }
        *tmp_pc4 = '\0';
        *(uint32_t *)(cgs + ((int)GHIDRA_FIELD(cgs, 66532, 4) % local_28) * 4 + 0x103a4) = tmp_u3;
        *(uint32_t *)(cgs + ((int)GHIDRA_FIELD(cgs, 66532, 4) % local_28) * 4 + 0x103c4) =
             *(uint32_t *)(cgs + param_2 * 0x1a4 + 0x9494);
        GHIDRA_FIELD(cgs, 66532, 4) = GHIDRA_FIELD(cgs, 66532, 4) + 1;
        tmp_i8 = ((int)GHIDRA_FIELD(cgs, 66532, 4) % local_28) * 0xd3;
        cgs[tmp_i8 + 0xfd0c] = 0x5e;
        cgs[tmp_i8 + 0xfd0d] = tmp_c1;
        if (param_1 == (char *)0x0) {
LAB_00096f90:
          tmp_pc2 = (void *)invalidInstructionException();
          (*tmp_pc2)();
        }
        tmp_c7 = *param_1;
        tmp_pc5 = cgs + tmp_i8 + 0xfd0e;
        tmp_pc10 = (char *)0x0;
        tmp_i11 = 0;
        tmp_pc9 = param_1;
      }
      if (tmp_c7 == '^') {
        if ((tmp_pc9[1] == '\0') || (tmp_pc9[1] == '^')) goto LAB_00096e16;
        *tmp_pc5 = '^';
        param_1 = tmp_pc9 + 2;
        tmp_pc4 = tmp_pc5 + 2;
        tmp_c1 = tmp_pc9[1];
        tmp_pc5[1] = tmp_c1;
        tmp_c7 = *param_1;
        if (tmp_c7 == '\0') break;
        goto LAB_00096e27;
      }
      if (tmp_c7 == ' ') {
        tmp_pc10 = tmp_pc5;
      }
LAB_00096e16:
      *tmp_pc5 = tmp_c7;
      tmp_i11 = tmp_i11 + 1;
      tmp_pc4 = tmp_pc5 + 1;
      param_1 = tmp_pc9 + 1;
    }
    *tmp_pc4 = '\0';
    tmp_u6 = *(uint32_t *)(cgs + param_2 * 0x1a4 + 0x9494);
  }
  *(uint32_t *)(cgs + ((int)GHIDRA_FIELD(cgs, 66532, 4) % local_28) * 4 + 0x103c4) = tmp_u6;
  *(uint32_t *)(cgs + ((int)GHIDRA_FIELD(cgs, 66532, 4) % local_28) * 4 + 0x103a4) = tmp_u3;
  GHIDRA_FIELD(cgs, 66532, 4) = GHIDRA_FIELD(cgs, 66532, 4) + 1;
  if (local_28 < (int)(GHIDRA_FIELD(cgs, 66532, 4) - GHIDRA_FIELD(cgs, 66536, 4))) {
    GHIDRA_FIELD(cgs, 66536, 4) = GHIDRA_FIELD(cgs, 66532, 4) - local_28;
    return;
  }
  return;
}

void CG_AddMarks(void)
{
  int *tmp_pi1;
  float tmp_f2;
  uint8_t tmp_u3;
  int tmp_i4;
  uint8_t tmp_u5;
  uint8_t tmp_u6;
  int *tmp_pi7;
  int *tmp_pi8;
  int local_3c;
  
  if ((GHIDRA_FIELD(cg_markTime, 12, 4) != 0) && (tmp_pi8 = g_unk_03404da4, g_unk_03404da4 != &cg_activeMarkPolys)) {
    do {
      while( true ) {
        tmp_pi1 = (int *)tmp_pi8[1];
        tmp_i4 = tmp_pi8[2] + tmp_pi8[0x48];
        if (tmp_i4 < g_unk_010906e0) break;
        tmp_i4 = tmp_i4 - g_unk_010906e0;
        tmp_f2 = (float)tmp_pi8[0x48] * 0.5;
        if (tmp_f2 <= (float)tmp_i4) {
          local_3c = tmp_pi8[10];
        }
        else {
          tmp_i4 = (int)ROUND(((float)tmp_i4 * 255.0) / tmp_f2);
          local_3c = tmp_pi8[10];
          if (tmp_pi8[4] == 0) {
            if (0 < local_3c) {
              tmp_f2 = (float)tmp_i4;
              tmp_u3 = (uint8_t)(short)ROUND((float)tmp_pi8[5] * tmp_f2);
              tmp_u5 = (uint8_t)(short)ROUND((float)tmp_pi8[6] * tmp_f2);
              *(uint8_t *)(tmp_pi8 + 0x11) = tmp_u3;
              *(uint8_t *)((int)tmp_pi8 + 0x45) = tmp_u5;
              tmp_u6 = (uint8_t)(short)ROUND(tmp_f2 * (float)tmp_pi8[7]);
              *(uint8_t *)((int)tmp_pi8 + 0x46) = tmp_u6;
              if (local_3c != 1) {
                *(uint8_t *)((int)tmp_pi8 + 0x5d) = tmp_u5;
                *(uint8_t *)((int)tmp_pi8 + 0x5e) = tmp_u6;
                *(uint8_t *)(tmp_pi8 + 0x17) = tmp_u3;
                if (local_3c != 2) {
                  *(uint8_t *)(tmp_pi8 + 0x1d) = tmp_u3;
                  *(uint8_t *)((int)tmp_pi8 + 0x75) = tmp_u5;
                  *(uint8_t *)((int)tmp_pi8 + 0x76) = tmp_u6;
                  if (local_3c != 3) {
                    *(uint8_t *)(tmp_pi8 + 0x23) = tmp_u3;
                    *(uint8_t *)((int)tmp_pi8 + 0x8d) = tmp_u5;
                    *(uint8_t *)((int)tmp_pi8 + 0x8e) = tmp_u6;
                    if (local_3c != 4) {
                      *(uint8_t *)(tmp_pi8 + 0x29) = tmp_u3;
                      *(uint8_t *)((int)tmp_pi8 + 0xa5) = tmp_u5;
                      *(uint8_t *)((int)tmp_pi8 + 0xa6) = tmp_u6;
                      if (local_3c != 5) {
                        *(uint8_t *)(tmp_pi8 + 0x2f) = tmp_u3;
                        *(uint8_t *)((int)tmp_pi8 + 0xbd) = tmp_u5;
                        *(uint8_t *)((int)tmp_pi8 + 0xbe) = tmp_u6;
                        if (local_3c != 6) {
                          *(uint8_t *)(tmp_pi8 + 0x35) = tmp_u3;
                          *(uint8_t *)((int)tmp_pi8 + 0xd5) = tmp_u5;
                          *(uint8_t *)((int)tmp_pi8 + 0xd6) = tmp_u6;
                          if (local_3c != 7) {
                            *(uint8_t *)(tmp_pi8 + 0x3b) = tmp_u3;
                            *(uint8_t *)((int)tmp_pi8 + 0xee) = tmp_u6;
                            *(uint8_t *)((int)tmp_pi8 + 0xed) = tmp_u5;
                            if (local_3c != 8) {
                              *(uint8_t *)(tmp_pi8 + 0x41) = tmp_u3;
                              *(uint8_t *)((int)tmp_pi8 + 0x106) = tmp_u6;
                              *(uint8_t *)((int)tmp_pi8 + 0x105) = tmp_u5;
                              if (local_3c != 9) {
                                *(uint8_t *)(tmp_pi8 + 0x47) = tmp_u3;
                                *(uint8_t *)((int)tmp_pi8 + 0x11e) = tmp_u6;
                                *(uint8_t *)((int)tmp_pi8 + 0x11d) = tmp_u5;
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
          else if (0 < local_3c) {
            tmp_u3 = (uint8_t)tmp_i4;
            *(uint8_t *)((int)tmp_pi8 + 0x47) = tmp_u3;
            if ((((((local_3c != 1) && (*(uint8_t *)((int)tmp_pi8 + 0x5f) = tmp_u3, local_3c != 2))
                  && (*(uint8_t *)((int)tmp_pi8 + 0x77) = tmp_u3, local_3c != 3)) &&
                 ((*(uint8_t *)((int)tmp_pi8 + 0x8f) = tmp_u3, local_3c != 4 &&
                  (*(uint8_t *)((int)tmp_pi8 + 0xa7) = tmp_u3, local_3c != 5)))) &&
                ((*(uint8_t *)((int)tmp_pi8 + 0xbf) = tmp_u3, local_3c != 6 &&
                 ((*(uint8_t *)((int)tmp_pi8 + 0xd7) = tmp_u3, local_3c != 7 &&
                  (*(uint8_t *)((int)tmp_pi8 + 0xef) = tmp_u3, local_3c != 8)))))) &&
               (*(uint8_t *)((int)tmp_pi8 + 0x107) = tmp_u3, local_3c != 9)) {
              *(uint8_t *)((int)tmp_pi8 + 0x11f) = tmp_u3;
            }
          }
        }
        trap_R_AddPolyToScene(tmp_pi8[3],local_3c,tmp_pi8 + 0xc);
        tmp_pi8 = tmp_pi1;
        if (tmp_pi1 == &cg_activeMarkPolys) {
          return;
        }
      }
      tmp_i4 = *tmp_pi8;
      tmp_pi7 = tmp_pi1;
      if (tmp_i4 == 0) {
        CG_Error("CG_FreeLocalEntity: not active");
        tmp_i4 = *tmp_pi8;
        tmp_pi7 = (int *)tmp_pi8[1];
      }
      *(int **)(tmp_i4 + 4) = tmp_pi7;
      *(int *)tmp_pi8[1] = *tmp_pi8;
      tmp_pi8[1] = (int)cg_freeMarkPolys;
      cg_freeMarkPolys = tmp_pi8;
      tmp_pi8 = tmp_pi1;
    } while (tmp_pi1 != &cg_activeMarkPolys);
  }
  return;
}

void CG_AddParticleToScene(int param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  uint tmp_u3;
  bool tmp_b4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  int tmp_i8;
  long double tmp_l9;
  long double tmp_l10;
  float tmp_f11;
  uint local_13c;
  uint local_134;
  byte local_12c;
  float local_124;
  float local_11c;
  float local_118;
  double local_f4;
  double local_ec;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  uint32_t local_b8;
  uint32_t local_b4;
  uint8_t local_b0;
  uint8_t local_af;
  uint8_t local_ae;
  uint8_t local_ad;
  float local_ac;
  float local_a8;
  float local_a4;
  uint32_t local_a0;
  uint32_t local_9c;
  uint8_t local_98;
  uint8_t local_97;
  uint8_t local_96;
  uint8_t local_95;
  float local_94;
  float local_90;
  float local_8c;
  uint32_t local_88;
  uint32_t local_84;
  uint8_t local_80;
  uint8_t local_7f;
  uint8_t local_7e;
  uint8_t local_7d;
  float local_7c;
  float local_78;
  float local_74;
  uint32_t local_70;
  uint32_t local_6c;
  byte local_68;
  byte local_67;
  byte local_66;
  uint8_t local_65;
  float local_64;
  float local_60;
  float local_5c;
  uint32_t local_58;
  uint32_t local_54;
  byte local_50;
  byte local_4f;
  byte local_4e;
  uint8_t local_4d;
  float local_4c;
  float local_48;
  float local_44;
  uint32_t local_40;
  uint32_t local_3c;
  byte local_38;
  byte local_37;
  byte local_36;
  uint8_t local_35;
  float local_34;
  float local_30;
  float local_2c;
  uint32_t local_28;
  uint32_t local_24;
  byte local_20;
  byte local_1f;
  byte local_1e;
  uint8_t local_1d;
  
  tmp_u3 = *(uint *)(param_1 + 0x40);
  tmp_b4 = tmp_u3 - 0xd < 2;
  if (((tmp_u3 & 0xfffffffb) == 1 || tmp_u3 == 0xb) || (tmp_b4)) {
    if (tmp_u3 != 0xb) {
      if (tmp_b4) {
        if (*(float *)(param_1 + 0x5c) < param_2[2]) {
          *(float *)(param_1 + 4) = (float)g_unk_010906e0;
          *(float *)(param_1 + 0xc) = *param_2;
          *(float *)(param_1 + 0x10) = param_2[1];
          *(float *)(param_1 + 0x14) = param_2[2];
          tmp_f11 = *(float *)(param_1 + 0x58);
          local_134 = rand();
          local_134 = local_134 & 0x7fff;
          tmp_f1 = (float)local_134 / 32767.0 - 0.5;
          *(float *)(param_1 + 0x14) = (tmp_f1 + tmp_f1) * 4.0 + tmp_f11;
          if (*(int *)(param_1 + 0x40) == 0xe) {
            local_13c = rand();
            local_13c = local_13c & 0x7fff;
            tmp_f11 = (float)local_13c / 32767.0 - 0.5;
            *(float *)(param_1 + 0x18) = (tmp_f11 + tmp_f11) * 4.0;
            local_13c = rand();
            local_13c = local_13c & 0x7fff;
            tmp_f11 = (float)local_13c / 32767.0 - 0.5;
            *(float *)(param_1 + 0x1c) = (tmp_f11 + tmp_f11) * 4.0;
          }
        }
      }
      else {
        tmp_f11 = *(float *)(param_1 + 0x5c);
        if (param_2[2] < tmp_f11) {
          *(float *)(param_1 + 4) = (float)g_unk_010906e0;
          *(float *)(param_1 + 0xc) = *param_2;
          *(float *)(param_1 + 0x10) = param_2[1];
          tmp_f1 = param_2[2];
          *(float *)(param_1 + 0x14) = tmp_f1;
          if (tmp_f1 < tmp_f11) {
            do {
              tmp_f1 = tmp_f1 + (*(float *)(param_1 + 0x58) - tmp_f11);
            } while (tmp_f1 < tmp_f11);
            *(float *)(param_1 + 0x14) = tmp_f1;
          }
          if (tmp_u3 == 5) {
            local_13c = rand();
            local_13c = local_13c & 0x7fff;
            tmp_f11 = (float)local_13c / 32767.0 - 0.5;
            *(float *)(param_1 + 0x18) = (tmp_f11 + tmp_f11) * 16.0;
            local_13c = rand();
            local_13c = local_13c & 0x7fff;
            tmp_f11 = (float)local_13c / 32767.0 - 0.5;
            *(float *)(param_1 + 0x1c) = (tmp_f11 + tmp_f11) * 16.0;
          }
        }
      }
      if (*(int *)(param_1 + 0x6c) == 0) {
        return;
      }
      *(uint32_t *)(param_1 + 0x38) = 0x3f800000;
    }
    tmp_l9 = (long double)VectorDistanceSquared(g_unk_01047b00 + 0x40,param_2);
    if ((long double)1048576.0 < tmp_l9) {
      return;
    }
    tmp_f11 = *param_2;
    tmp_f1 = -*(float *)(param_1 + 0x48);
    if (*(int *)(param_1 + 0x40) - 0xdU < 2) {
      local_68 = 0xff;
      local_67 = 0xff;
      local_66 = 0xff;
      local_70 = 0;
      local_64 = vup * tmp_f1 + tmp_f11;
      local_6c = 0;
      local_60 = g_unk_034fcf34 * tmp_f1 + param_2[1];
      local_5c = param_2[2] + tmp_f1 * g_unk_034fcf38;
      tmp_f1 = -*(float *)(param_1 + 0x4c);
      local_7c = vright * tmp_f1 + local_64;
      local_78 = g_unk_03404f08 * tmp_f1 + local_60;
      local_74 = tmp_f1 * g_unk_03404f0c + local_5c;
      local_65 = (uint8_t)(short)ROUND(*(float *)(param_1 + 0x38) * 255.0);
      local_4c = vright * *(float *)(param_1 + 0x4c);
      local_50 = 0xff;
      local_4f = 0xff;
      local_4e = 0xff;
      local_38 = 0xff;
      local_48 = *(float *)(param_1 + 0x4c) * g_unk_03404f08;
      local_37 = 0xff;
      local_36 = 0xff;
      local_44 = *(float *)(param_1 + 0x4c) * g_unk_03404f0c;
      local_58 = 0;
      local_54 = 0x3f800000;
      local_40 = 0x3f800000;
      local_3c = 0x3f800000;
      local_64 = local_64 + local_4c;
      local_60 = local_60 + local_48;
      local_5c = local_5c + local_44;
      local_34 = vup * *(float *)(param_1 + 0x48) + tmp_f11;
      local_30 = *(float *)(param_1 + 0x48) * g_unk_034fcf34 + param_2[1];
      local_2c = *(float *)(param_1 + 0x48) * g_unk_034fcf38 + param_2[2];
      local_4c = local_4c + local_34;
      local_48 = local_48 + local_30;
      local_44 = local_44 + local_2c;
      local_34 = local_34 + vright * tmp_f1;
      local_30 = local_30 + g_unk_03404f08 * tmp_f1;
      local_2c = local_2c + tmp_f1 * g_unk_03404f0c;
      local_20 = 0xff;
      tmp_i8 = *(int *)(param_1 + 0x44);
      local_28 = 0x3f800000;
      local_24 = 0;
      local_1f = 0xff;
      local_1e = 0xff;
      local_4d = local_65;
      local_35 = local_65;
      local_1d = local_65;
    }
    else {
      tmp_f2 = -*(float *)(param_1 + 0x4c);
      local_af = 0xff;
      local_ae = 0xff;
      local_b0 = 0xff;
      local_b8 = 0x3f800000;
      local_b4 = 0;
      local_c4 = vup * tmp_f1 + tmp_f11 + vright * tmp_f2;
      local_c0 = g_unk_034fcf34 * tmp_f1 + param_2[1] + g_unk_03404f08 * tmp_f2;
      local_bc = tmp_f1 * g_unk_034fcf38 + param_2[2] + tmp_f2 * g_unk_03404f0c;
      local_ad = (uint8_t)(short)ROUND(*(float *)(param_1 + 0x38) * 255.0);
      tmp_f11 = vup * *(float *)(param_1 + 0x48) + tmp_f11;
      local_90 = *(float *)(param_1 + 0x48) * g_unk_034fcf34 + param_2[1];
      local_8c = *(float *)(param_1 + 0x48) * g_unk_034fcf38 + param_2[2];
      local_ac = vright * tmp_f2 + tmp_f11;
      local_a8 = g_unk_03404f08 * tmp_f2 + local_90;
      tmp_i8 = *(int *)(param_1 + 0x44);
      local_98 = 0xff;
      local_a4 = tmp_f2 * g_unk_03404f0c + local_8c;
      local_97 = 0xff;
      local_96 = 0xff;
      local_80 = 0xff;
      local_a0 = 0;
      local_9c = 0;
      local_88 = 0;
      local_84 = 0x3f800000;
      local_7f = 0xff;
      local_94 = vright * *(float *)(param_1 + 0x4c) + tmp_f11;
      local_7e = 0xff;
      local_90 = *(float *)(param_1 + 0x4c) * g_unk_03404f08 + local_90;
      local_8c = *(float *)(param_1 + 0x4c) * g_unk_03404f0c + local_8c;
      local_95 = local_ad;
      local_7d = local_ad;
    }
    goto LAB_0009a18d;
  }
  if (tmp_u3 != 0xf) {
    if (tmp_u3 == 0xc) {
      tmp_l9 = (long double)VectorDistanceSquared(g_unk_01047b00 + 0x40,param_2);
      if ((long double)1048576.0 < tmp_l9) {
        return;
      }
    }
    else if (tmp_u3 != 3) {
      if (tmp_u3 == 8) {
        local_118 = *(float *)(param_1 + 0x38);
        if (GHIDRA_FIELD(cgs, 27292, 4) == 3) {
          local_118 = 1.0;
        }
        if (*(int *)(param_1 + 0x74) == 0) {
          local_11c = g_unk_03404f0c;
          local_dc = vright;
          local_d8 = g_unk_03404f08;
          local_d0 = vup;
          local_cc = g_unk_034fcf34;
          local_c8 = g_unk_034fcf38;
        }
        else {
          vectoangles(g_unk_010afbcc + 0x24,&local_c4);
          local_bc = (float)*(int *)(param_1 + 0x74) + local_bc;
          AngleVectors(&local_c4,0,&local_dc,&local_d0);
          local_11c = local_d4;
        }
        tmp_f11 = -*(float *)(param_1 + 0x48);
        local_68 = 0x6f;
        local_67 = 0x13;
        local_66 = 9;
        local_70 = 0;
        local_64 = *param_2 + local_d0 * tmp_f11;
        local_6c = 0;
        local_60 = param_2[1] + local_cc * tmp_f11;
        local_5c = param_2[2] + tmp_f11 * local_c8;
        tmp_f11 = -*(float *)(param_1 + 0x4c);
        local_7c = tmp_f11 * local_dc + local_64;
        local_78 = tmp_f11 * local_d8 + local_60;
        local_74 = tmp_f11 * local_11c + local_5c;
        local_65 = (uint8_t)(short)ROUND(local_118 * 255.0);
        local_4c = local_dc * *(float *)(param_1 + 0x4c);
        local_50 = 0x6f;
        local_4f = 0x13;
        local_4e = 9;
        local_38 = 0x6f;
        local_48 = local_d8 * *(float *)(param_1 + 0x4c);
        local_37 = 0x13;
        local_36 = 9;
        local_58 = 0;
        local_44 = local_11c * *(float *)(param_1 + 0x4c);
        local_54 = 0x3f800000;
        local_40 = 0x3f800000;
        local_3c = 0x3f800000;
        local_64 = local_64 + local_4c;
        local_60 = local_60 + local_48;
        local_5c = local_5c + local_44;
        local_34 = local_d0 * *(float *)(param_1 + 0x48) + *param_2;
        local_30 = local_cc * *(float *)(param_1 + 0x48) + param_2[1];
        local_2c = local_c8 * *(float *)(param_1 + 0x48) + param_2[2];
        local_4c = local_4c + local_34;
        local_48 = local_48 + local_30;
        local_44 = local_44 + local_2c;
        local_34 = local_34 + tmp_f11 * local_dc;
        local_30 = local_30 + tmp_f11 * local_d8;
        local_20 = 0x6f;
        tmp_i8 = *(int *)(param_1 + 0x44);
        local_28 = 0x3f800000;
        local_24 = 0;
        local_1f = 0x13;
        local_2c = local_2c + tmp_f11 * local_11c;
        local_1e = 9;
        local_4d = local_65;
        local_35 = local_65;
        local_1d = local_65;
        goto LAB_0009a18d;
      }
      if (tmp_u3 == 9) {
        local_12c = (*(int *)(param_1 + 0x30) != 2) - 1U | 0x7f;
        tmp_f2 = ((float)g_unk_010906e0 - *(float *)(param_1 + 4)) /
                (*(float *)(param_1 + 8) - *(float *)(param_1 + 4));
        tmp_f11 = *(float *)(param_1 + 0x54);
        tmp_f5 = (tmp_f11 - *(float *)(param_1 + 0x4c)) * tmp_f2 + *(float *)(param_1 + 0x4c);
        tmp_f1 = *(float *)(param_1 + 0x50);
        tmp_f2 = (tmp_f1 - *(float *)(param_1 + 0x48)) * tmp_f2 + *(float *)(param_1 + 0x48);
        if (tmp_f11 < tmp_f5) {
          tmp_f5 = tmp_f11;
        }
        if (tmp_f1 < tmp_f2) {
          tmp_f2 = tmp_f1;
        }
        sincos(((double)*(int *)(param_1 + 0x74) * 3.141592653589793) / 180.0,&local_ec,&local_f4);
        local_68 = local_12c;
        local_65 = 0xff;
        local_4d = 0xff;
        tmp_f11 = tmp_f2 * (float)local_ec * 1.4142135;
        local_70 = 0;
        local_6c = 0;
        local_58 = 0;
        local_54 = 0x3f800000;
        local_e0 = tmp_f5 * (float)local_f4 * 1.4142135;
        local_34 = *param_2;
        local_30 = param_2[1];
        local_74 = param_2[2];
        local_7c = local_34 - tmp_f11;
        local_78 = local_30 - local_e0;
        local_64 = local_34 - local_e0;
        local_60 = tmp_f11 + local_30;
        local_4c = tmp_f11 + local_34;
        local_48 = local_e0 + local_30;
        local_34 = local_e0 + local_34;
        local_30 = local_30 - tmp_f11;
        tmp_i8 = *(int *)(param_1 + 0x44);
        local_40 = 0x3f800000;
        local_3c = 0x3f800000;
        local_35 = 0xff;
        local_28 = 0x3f800000;
        local_24 = 0;
        local_1d = 0xff;
        local_67 = local_68;
        local_66 = local_68;
        local_5c = local_74;
        local_50 = local_68;
        local_4f = local_68;
        local_4e = local_68;
        local_44 = local_74;
        local_38 = local_68;
        local_37 = local_68;
        local_36 = local_68;
        local_2c = local_74;
        local_20 = local_68;
        local_1f = local_68;
        local_1e = local_68;
        goto LAB_0009a18d;
      }
      if (tmp_u3 == 2) {
        local_74 = param_2[2];
        local_7c = *param_2 - *(float *)(param_1 + 0x48);
        local_78 = param_2[1] - *(float *)(param_1 + 0x4c);
        local_60 = param_2[1] + *(float *)(param_1 + 0x4c);
        local_4c = *param_2 + *(float *)(param_1 + 0x48);
        local_64 = local_7c;
        local_5c = local_74;
        local_48 = local_60;
        local_44 = local_74;
        local_34 = local_4c;
        local_30 = local_78;
        local_2c = local_74;
        goto LAB_0009a600;
      }
      if (1 < tmp_u3 - 6) {
        tmp_i8 = *(int *)(param_1 + 0x44);
        goto LAB_0009a18d;
      }
      tmp_f11 = ((float)g_unk_010906e0 - *(float *)(param_1 + 4)) /
               (*(float *)(param_1 + 8) - *(float *)(param_1 + 4));
      if (tmp_f11 < 1.0) {
        if (tmp_f11 < 0.0) {
          tmp_f11 = 0.0001;
        }
      }
      else {
        tmp_f11 = 0.9999;
      }
      tmp_f5 = (*(float *)(param_1 + 0x54) - *(float *)(param_1 + 0x4c)) * tmp_f11 +
              *(float *)(param_1 + 0x4c);
      tmp_f1 = *(float *)(param_1 + 0x50);
      tmp_f2 = *(float *)(param_1 + 0x48);
      if (tmp_u3 == 7) {
        trap_R_AddLightToScene
                  (param_2,0x43a00000,(1.0 - tmp_f11) * 1.25,0x3f800000,0x3f733333,0x3f59999a,0,0);
      }
      tmp_l9 = (long double)VectorDistanceSquared(g_unk_01047b00 + 0x40);
      if (tmp_l9 < ((long double)tmp_f5 / (long double)1.5) * ((long double)tmp_f5 / (long double)1.5)) {
        return;
      }
      tmp_i8 = *(int *)(param_1 + 0x70);
      tmp_f2 = (tmp_f1 - tmp_f2) * tmp_f11 + tmp_f2;
      tmp_f11 = floorf((float)*(int *)(shaderAnimCounts + tmp_i8 * 4) * tmp_f11);
      tmp_i8 = (&shaderAnims)[(int)ROUND(tmp_f11) + tmp_i8 * 0x40];
      *(int *)(param_1 + 0x44) = tmp_i8;
      if (*(int *)(param_1 + 0x74) == 0) {
LAB_0009b707:
        tmp_f11 = -tmp_f2;
        tmp_f1 = -tmp_f5;
        local_7c = vright * tmp_f1 + vup * tmp_f11 + *param_2;
        local_78 = g_unk_03404f08 * tmp_f1 + tmp_f11 * g_unk_034fcf34 + param_2[1];
        local_74 = tmp_f1 * g_unk_03404f0c + tmp_f11 * g_unk_034fcf38 + param_2[2];
        tmp_f11 = tmp_f2 + tmp_f2;
        local_64 = vup * tmp_f11 + local_7c;
        local_60 = g_unk_034fcf34 * tmp_f11 + local_78;
        local_5c = tmp_f11 * g_unk_034fcf38 + local_74;
        tmp_f5 = tmp_f5 + tmp_f5;
        local_4c = vright * tmp_f5 + local_64;
        local_48 = g_unk_03404f08 * tmp_f5 + local_60;
        local_44 = tmp_f5 * g_unk_03404f0c + local_5c;
        tmp_f2 = tmp_f2 * -2.0;
        local_34 = local_4c + vup * tmp_f2;
        local_30 = g_unk_034fcf34 * tmp_f2 + local_48;
        local_2c = tmp_f2 * g_unk_034fcf38 + local_44;
      }
      else {
        vectoangles(g_unk_010afbcc + 0x24,&local_c4);
        local_bc = (float)*(int *)(param_1 + 0x74) + local_bc;
        AngleVectors(&local_c4,0,&local_dc,&local_d0);
        if (*(int *)(param_1 + 0x74) == 0) {
          tmp_i8 = *(int *)(param_1 + 0x44);
          goto LAB_0009b707;
        }
        tmp_f11 = -tmp_f2;
        tmp_f1 = -tmp_f5;
        local_7c = local_dc * tmp_f1 + local_d0 * tmp_f11 + *param_2;
        local_78 = local_d8 * tmp_f1 + tmp_f11 * local_cc + param_2[1];
        local_74 = tmp_f1 * local_d4 + tmp_f11 * local_c8 + param_2[2];
        tmp_f11 = tmp_f2 + tmp_f2;
        local_64 = local_d0 * tmp_f11 + local_7c;
        local_60 = local_cc * tmp_f11 + local_78;
        local_5c = tmp_f11 * local_c8 + local_74;
        tmp_f5 = tmp_f5 + tmp_f5;
        local_4c = local_dc * tmp_f5 + local_64;
        local_48 = local_d8 * tmp_f5 + local_60;
        local_44 = tmp_f5 * local_d4 + local_5c;
        tmp_f2 = tmp_f2 * -2.0;
        tmp_i8 = *(int *)(param_1 + 0x44);
        local_34 = local_4c + local_d0 * tmp_f2;
        local_30 = local_cc * tmp_f2 + local_48;
        local_2c = tmp_f2 * local_c8 + local_44;
      }
      local_35 = 0xff;
      local_36 = 0xff;
      local_37 = 0xff;
      local_38 = 0xff;
      local_3c = 0x3f800000;
      local_40 = 0x3f800000;
      local_4d = 0xff;
      local_4e = 0xff;
      local_4f = 0xff;
      local_50 = 0xff;
      local_54 = 0x3f800000;
      local_58 = 0;
      local_65 = 0xff;
      local_66 = 0xff;
      local_67 = 0xff;
      local_68 = 0xff;
      local_6c = 0;
      local_70 = 0;
      local_20 = 0xff;
      local_1f = 0xff;
      local_28 = 0x3f800000;
      local_24 = 0;
      local_1e = 0xff;
      local_1d = 0xff;
      goto LAB_0009a18d;
    }
    tmp_i8 = *(int *)(param_1 + 0x30);
    if (tmp_i8 == 1) {
      local_124 = 0.33;
      local_11c = 0.42;
      tmp_f11 = 0.19;
    }
    else if (tmp_i8 == 2) {
      local_124 = 0.0;
      local_11c = 0.22;
      tmp_f11 = 0.0;
    }
    else if (tmp_i8 == 5) {
      local_124 = 0.28;
      local_11c = 0.4;
      tmp_f11 = 0.23;
    }
    else if (tmp_i8 == 4) {
      tmp_l9 = (long double)Distance(g_unk_01047b00 + 0x40,param_2);
      if (tmp_l9 == (long double)0) {
        local_11c = 0.5;
        local_124 = local_11c;
        tmp_f11 = 0.5;
      }
      else {
        tmp_l10 = ((long double)4096.0 / tmp_l9) * (long double)0.25;
        local_11c = (float)tmp_l10;
        tmp_l9 = (long double)0.5;
        local_124 = local_11c;
        tmp_f11 = local_11c;
        if (tmp_l9 < tmp_l10) goto LAB_0009ac8f;
      }
    }
    else {
      tmp_l9 = (long double)1;
LAB_0009ac8f:
      local_124 = (float)tmp_l9;
      local_11c = (float)tmp_l9;
      tmp_f11 = (float)tmp_l9;
    }
    tmp_f5 = (float)g_unk_010906e0;
    tmp_f2 = (tmp_f5 - *(float *)(param_1 + 4)) / (*(float *)(param_1 + 8) - *(float *)(param_1 + 4));
    tmp_f1 = *(float *)(param_1 + 0x60);
    if (tmp_f5 <= tmp_f1) {
      tmp_f1 = *(float *)(param_1 + 0x38);
    }
    else {
      tmp_f1 = 1.0 - (tmp_f5 - tmp_f1) / (*(float *)(param_1 + 8) - tmp_f1);
      if (*(int *)(param_1 + 0x30) == 3) {
        local_11c = tmp_f1 * tmp_f1;
        local_124 = local_11c;
        tmp_f11 = local_11c;
      }
      tmp_f1 = tmp_f1 * *(float *)(param_1 + 0x38);
    }
    if (GHIDRA_FIELD(cgs, 27292, 4) == 3) {
      tmp_f1 = 1.0;
    }
    else if (1.0 < tmp_f1) {
      tmp_f1 = 1.0;
    }
    tmp_f5 = (*(float *)(param_1 + 0x54) - *(float *)(param_1 + 0x4c)) * tmp_f2 +
            *(float *)(param_1 + 0x4c);
    tmp_f2 = (*(float *)(param_1 + 0x50) - *(float *)(param_1 + 0x48)) * tmp_f2 +
            *(float *)(param_1 + 0x48);
    vectoangles(rforward,&local_7c);
    tmp_i8 = *(int *)(param_1 + 0x74) + *(int *)(param_1 + 0x78);
    *(int *)(param_1 + 0x78) = tmp_i8;
    local_74 = (float)tmp_i8 * 0.1 + local_74;
    AngleVectors(&local_7c,0,&local_dc,&local_d0);
    local_34 = *param_2;
    if (*(int *)(param_1 + 100) == 0) {
      tmp_f7 = -*(float *)(param_1 + 0x48);
      local_30 = param_2[1];
      local_2c = param_2[2];
      tmp_f6 = -*(float *)(param_1 + 0x4c);
      local_7c = vright * tmp_f6 + vup * tmp_f7 + local_34;
      local_78 = g_unk_03404f08 * tmp_f6 + g_unk_034fcf34 * tmp_f7 + local_30;
      local_74 = tmp_f6 * g_unk_03404f0c + tmp_f7 * g_unk_034fcf38 + local_2c;
    }
    else {
      local_30 = param_2[1];
      local_2c = param_2[2];
      tmp_f7 = -tmp_f2;
      tmp_f6 = -tmp_f5;
      local_7c = local_dc * tmp_f6 + local_d0 * tmp_f7 + local_34;
      local_78 = local_d8 * tmp_f6 + local_cc * tmp_f7 + local_30;
      local_74 = tmp_f6 * local_d4 + tmp_f7 * local_c8 + local_2c;
    }
    local_70 = 0;
    local_6c = 0;
    local_68 = (byte)(short)ROUND(local_11c * 255.0);
    local_67 = (byte)(short)ROUND(local_124 * 255.0);
    local_66 = (byte)(short)ROUND(tmp_f11 * 255.0);
    local_65 = (uint8_t)(short)ROUND(tmp_f1 * 255.0);
    if (*(int *)(param_1 + 100) == 0) {
      tmp_f11 = *(float *)(param_1 + 0x48);
      tmp_f1 = -tmp_f11;
      local_4c = vright * *(float *)(param_1 + 0x4c);
      local_48 = *(float *)(param_1 + 0x4c) * g_unk_03404f08;
      local_44 = *(float *)(param_1 + 0x4c) * g_unk_03404f0c;
      local_64 = vup * tmp_f1 + local_34 + local_4c;
      local_60 = g_unk_034fcf34 * tmp_f1 + local_30 + local_48;
      local_5c = tmp_f1 * g_unk_034fcf38 + local_2c + local_44;
      local_34 = vup * tmp_f11 + local_34;
      local_30 = g_unk_034fcf34 * tmp_f11 + local_30;
      local_2c = tmp_f11 * g_unk_034fcf38 + local_2c;
      local_4c = local_4c + local_34;
      local_48 = local_48 + local_30;
      local_44 = local_44 + local_2c;
      tmp_f11 = -*(float *)(param_1 + 0x4c);
      local_34 = vright * tmp_f11 + local_34;
      local_30 = g_unk_03404f08 * tmp_f11 + local_30;
      local_2c = tmp_f11 * g_unk_03404f0c + local_2c;
    }
    else {
      tmp_f11 = -tmp_f2;
      local_64 = local_d0 * tmp_f11 + local_34 + local_dc * tmp_f5;
      local_60 = local_cc * tmp_f11 + local_30 + local_d8 * tmp_f5;
      local_5c = tmp_f11 * local_c8 + local_2c + tmp_f5 * local_d4;
      local_34 = local_d0 * tmp_f2 + local_34;
      local_30 = local_cc * tmp_f2 + local_30;
      local_2c = tmp_f2 * local_c8 + local_2c;
      local_4c = local_dc * tmp_f5 + local_34;
      local_48 = local_d8 * tmp_f5 + local_30;
      local_44 = tmp_f5 * local_d4 + local_2c;
      tmp_f5 = -tmp_f5;
      local_34 = local_dc * tmp_f5 + local_34;
      local_30 = local_d8 * tmp_f5 + local_30;
      local_2c = tmp_f5 * local_d4 + local_2c;
    }
    local_3c = 0x3f800000;
    local_40 = 0x3f800000;
    local_54 = 0x3f800000;
    local_58 = 0;
    local_28 = 0x3f800000;
    local_24 = 0;
    tmp_i8 = *(int *)(param_1 + 0x44);
    local_50 = local_68;
    local_4f = local_67;
    local_4e = local_66;
    local_4d = local_65;
    local_38 = local_68;
    local_37 = local_67;
    local_36 = local_66;
    local_35 = local_65;
    local_20 = local_68;
    local_1f = local_67;
    local_1e = local_66;
    local_1d = local_65;
    goto LAB_0009a18d;
  }
  tmp_f11 = ((float)g_unk_010906e0 - *(float *)(param_1 + 4)) /
           (*(float *)(param_1 + 8) - *(float *)(param_1 + 4));
  tmp_f1 = (*(float *)(param_1 + 0x54) - *(float *)(param_1 + 0x4c)) * tmp_f11 +
          *(float *)(param_1 + 0x4c);
  tmp_f11 = (*(float *)(param_1 + 0x50) - *(float *)(param_1 + 0x48)) * tmp_f11 +
           *(float *)(param_1 + 0x48);
  if (*(int *)(param_1 + 0x74) == 0) {
LAB_0009a44a:
    tmp_f5 = -tmp_f11;
    tmp_f2 = -tmp_f1;
    local_7c = vright * tmp_f2 + vup * tmp_f5 + *param_2;
    local_78 = g_unk_03404f08 * tmp_f2 + g_unk_034fcf34 * tmp_f5 + param_2[1];
    local_74 = tmp_f2 * g_unk_03404f0c + tmp_f5 * g_unk_034fcf38 + param_2[2];
    tmp_f2 = tmp_f11 + tmp_f11;
    local_64 = vup * tmp_f2 + local_7c;
    local_60 = g_unk_034fcf34 * tmp_f2 + local_78;
    local_5c = tmp_f2 * g_unk_034fcf38 + local_74;
    tmp_f1 = tmp_f1 + tmp_f1;
    local_4c = vright * tmp_f1 + local_64;
    local_48 = g_unk_03404f08 * tmp_f1 + local_60;
    local_44 = tmp_f1 * g_unk_03404f0c + local_5c;
    tmp_f11 = tmp_f11 * -2.0;
    local_34 = local_4c + vup * tmp_f11;
    local_30 = g_unk_034fcf34 * tmp_f11 + local_48;
    local_2c = tmp_f11 * g_unk_034fcf38 + local_44;
  }
  else {
    vectoangles(g_unk_010afbcc + 0x24,&local_c4);
    local_bc = (float)*(int *)(param_1 + 0x74) + local_bc;
    AngleVectors(&local_c4,0,&local_dc,&local_d0);
    if (*(int *)(param_1 + 0x74) == 0) goto LAB_0009a44a;
    tmp_f5 = -tmp_f11;
    tmp_f2 = -tmp_f1;
    local_7c = local_dc * tmp_f2 + *param_2 + local_d0 * tmp_f5;
    local_78 = local_d8 * tmp_f2 + local_cc * tmp_f5 + param_2[1];
    local_74 = tmp_f2 * local_d4 + tmp_f5 * local_c8 + param_2[2];
    tmp_f2 = tmp_f11 + tmp_f11;
    local_64 = local_d0 * tmp_f2 + local_7c;
    local_60 = local_cc * tmp_f2 + local_78;
    local_5c = tmp_f2 * local_c8 + local_74;
    tmp_f1 = tmp_f1 + tmp_f1;
    local_4c = local_dc * tmp_f1 + local_64;
    local_48 = local_d8 * tmp_f1 + local_60;
    local_44 = tmp_f1 * local_d4 + local_5c;
    tmp_f11 = tmp_f11 * -2.0;
    local_34 = local_4c + local_d0 * tmp_f11;
    local_30 = local_cc * tmp_f11 + local_48;
    local_2c = tmp_f11 * local_c8 + local_44;
  }
LAB_0009a600:
  local_35 = 0xff;
  local_36 = 0xff;
  local_37 = 0xff;
  local_38 = 0xff;
  local_3c = 0x3f800000;
  local_40 = 0x3f800000;
  local_4d = 0xff;
  local_4e = 0xff;
  local_4f = 0xff;
  local_50 = 0xff;
  local_54 = 0x3f800000;
  local_58 = 0;
  local_65 = 0xff;
  local_66 = 0xff;
  local_67 = 0xff;
  local_68 = 0xff;
  local_6c = 0;
  local_70 = 0;
  local_20 = 0xff;
  local_1f = 0xff;
  local_1e = 0xff;
  local_1d = 0xff;
  tmp_i8 = *(int *)(param_1 + 0x44);
  local_28 = 0x3f800000;
  local_24 = 0;
LAB_0009a18d:
  if (tmp_i8 != 0) {
    if (((*(uint *)(param_1 + 0x40) & 0xfffffffb) == 1) || (*(uint *)(param_1 + 0x40) == 0xb)) {
      trap_R_AddPolyToScene(tmp_i8,3,&local_c4);
      return;
    }
    trap_R_AddPolyToScene(tmp_i8,4,&local_7c);
  }
  return;
}

void CG_AddParticles(void)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint32_t *tmp_pu6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  uint32_t tmp_u9;
  int tmp_i10;
  int tmp_i11;
  uint32_t *tmp_pu12;
  char *tmp_pc13;
  uint32_t *local_54;
  uint32_t *local_4c;
  float local_34;
  float local_30;
  float local_2c;
  uint8_t local_28 [8];
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x9bcb9;
  if (initparticles == 0) {
    memset(particles,0,0xf8000);
    active_particles = (uint32_t *)0x0;
    free_particles = particles;
    tmp_i1 = cl_numparticles + -1;
    if (cl_numparticles != 0) {
      tmp_pu7 = particles + cl_numparticles * 0x7c;
      do {
        *(uint32_t *)(tmp_pu7 + -0x3c) = 0;
        *(uint8_t **)(tmp_pu7 + -0x7c) = tmp_pu7;
        tmp_pu7 = tmp_pu7 + -0x7c;
      } while (tmp_pu7 != particles);
    }
    *(uint32_t *)(particles + tmp_i1 * 0x7c) = 0;
    tmp_pu12 = &shaderAnims;
    tmp_pc13 = "explode1";
    oldtime = (float)g_unk_010906e0;
    local_4c = (uint32_t *)0x0;
    do {
      tmp_i8 = (int)local_4c * 4;
      tmp_i1 = *(int *)(shaderAnimCounts + tmp_i8);
      if (0 < tmp_i1) {
        tmp_i10 = 0;
        do {
          tmp_i11 = tmp_i10 + 1;
          tmp_u9 = va(&g_unk_00118c8a,tmp_pc13,tmp_i11);
          tmp_u9 = trap_R_RegisterShader(tmp_u9);
          tmp_pu12[tmp_i10] = tmp_u9;
          tmp_i10 = tmp_i11;
        } while (tmp_i11 != tmp_i1);
      }
      tmp_pu12 = tmp_pu12 + 0x40;
      local_4c = (uint32_t *)((int)local_4c + 1);
      tmp_pc13 = *(char **)(shaderAnimNames + tmp_i8 + 4);
    } while (tmp_pc13 != (char *)0x0);
    initparticles = 1;
    numShaderAnims = (int)local_4c;
  }
  vforward = *(uint32_t *)(g_unk_010afbcc + 0x24);
  g_unk_03404efc = *(uint32_t *)(g_unk_010afbcc + 0x28);
  g_unk_03404f00 = *(uint32_t *)(g_unk_010afbcc + 0x2c);
  vright = *(uint32_t *)(g_unk_010afbcc + 0x30);
  g_unk_03404f08 = *(uint32_t *)(g_unk_010afbcc + 0x34);
  g_unk_03404f0c = *(uint32_t *)(g_unk_010afbcc + 0x38);
  vup = *(uint32_t *)(g_unk_010afbcc + 0x3c);
  g_unk_034fcf34 = *(uint32_t *)(g_unk_010afbcc + 0x40);
  g_unk_034fcf38 = *(uint32_t *)(g_unk_010afbcc + 0x44);
  vectoangles(g_unk_010afbcc + 0x24,local_28);
  roll = ((float)g_unk_010906e0 - oldtime) * 0.1 + roll;
  local_20 = roll * 0.9 + local_20;
  AngleVectors(local_28,rforward,rright,rup);
  tmp_f3 = (float)g_unk_010906e0;
  if (active_particles == (uint32_t *)0x0) {
    oldtime = tmp_f3;
    active_particles = (uint32_t *)0x0;
    return;
  }
  local_54 = (uint32_t *)0x0;
  local_4c = (uint32_t *)0x0;
  tmp_pu12 = active_particles;
  oldtime = tmp_f3;
  do {
    tmp_pu2 = (uint32_t *)*tmp_pu12;
    tmp_f4 = (tmp_f3 - (float)tmp_pu12[1]) * 0.001;
    tmp_f5 = (float)tmp_pu12[0xf] * tmp_f4 + (float)tmp_pu12[0xe];
    if ((tmp_f5 <= 0.0) ||
       (((tmp_i1 = tmp_pu12[0x10], tmp_i1 == 0xc || tmp_i1 == 3 || (tmp_i1 - 6U < 3)) &&
        ((float)tmp_pu12[2] < tmp_f3)))) {
LAB_0009bee6:
      tmp_pu12[0x10] = 0;
      tmp_pu12[0xc] = 0;
      tmp_pu12[0xe] = 0;
      *tmp_pu12 = free_particles;
      free_particles = (uint8_t *)tmp_pu12;
    }
    else {
      if ((tmp_i1 == 0xb) || (tmp_i1 == 10)) {
        if ((float)tmp_pu12[2] < tmp_f3) goto LAB_0009bee6;
      }
      else if ((tmp_i1 == 0xf) && ((float)tmp_pu12[2] < 0.0)) {
        CG_AddParticleToScene(tmp_pu12,tmp_pu12 + 3,tmp_f5);
        goto LAB_0009bee6;
      }
      *tmp_pu12 = 0;
      tmp_pu6 = tmp_pu12;
      if (local_54 != (uint32_t *)0x0) {
        *local_54 = tmp_pu12;
        tmp_pu6 = local_4c;
      }
      local_4c = tmp_pu6;
      if (1.0 < tmp_f5) {
        tmp_f5 = 1.0;
      }
      tmp_f3 = tmp_f4 * tmp_f4;
      local_34 = (float)tmp_pu12[9] * tmp_f3 + (float)tmp_pu12[6] * tmp_f4 + (float)tmp_pu12[3];
      local_30 = (float)tmp_pu12[10] * tmp_f3 + (float)tmp_pu12[7] * tmp_f4 + (float)tmp_pu12[4];
      local_2c = tmp_f3 * (float)tmp_pu12[0xb] + tmp_f4 * (float)tmp_pu12[8] + (float)tmp_pu12[5];
      CG_AddParticleToScene(tmp_pu12,&local_34,tmp_f5);
      local_54 = tmp_pu12;
    }
    if (tmp_pu2 == (uint32_t *)0x0) {
      active_particles = local_4c;
      return;
    }
    tmp_f3 = (float)g_unk_010906e0;
    tmp_pu12 = tmp_pu2;
  } while( true );
}

void CG_AddParticleShrapnel(void)
{
  return;
}

void CG_AddOnScreenText(uint32_t param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  uint tmp_u10;
  long double tmp_l11;
  long double tmp_l12;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  if (g_unk_010ee740 < 0x10) {
    AngleVectors(&g_unk_01091a54,&local_40,&local_34,&local_28);
    tmp_f1 = *param_2 - g_unk_010918c0;
    tmp_f4 = param_2[1] - g_unk_010918c4;
    tmp_f3 = param_2[2] - g_unk_010918c8;
    tmp_f2 = local_38 * tmp_f3 + local_3c * tmp_f4 + local_40 * tmp_f1;
    if (tmp_f2 < 0.01) {
      tmp_i7 = g_unk_010ee740 * 0x2c;
      tmp_u10 = 0;
      do {
        *(uint32_t *)((int)&g_unk_010ee480 + tmp_u10 + tmp_i7) = 0;
        *(uint32_t *)((int)&g_unk_010ee484 + tmp_u10 + tmp_i7) = 0;
        tmp_u10 = tmp_u10 + 8;
      } while (tmp_u10 < 0x28);
      *(uint32_t *)((int)&g_unk_010ee480 + tmp_u10 + tmp_i7) = 0;
    }
    else {
      tmp_f5 = 96.0 / g_unk_010918b8;
      tmp_f6 = 102.0 / g_unk_010918bc;
      tmp_l11 = (long double)VectorDistance(param_2,g_unk_010afbcc + 0x18);
      if (tmp_l11 <= (long double)1500.0) {
        tmp_l12 = (long double)0.5 - tmp_l11 / (long double)3000.0;
        tmp_l11 = (long double)0.125;
        if ((long double)0.125 <= tmp_l12) {
          tmp_l11 = tmp_l12;
        }
      }
      else {
        tmp_l11 = (long double)0.125;
      }
      tmp_i7 = CG_Text_Width_Ext(param_1,(float)tmp_l11,0,0x1100f64);
      tmp_i8 = CG_Text_Height_Ext(param_1,(float)tmp_l11,0,0x1100f64);
      tmp_i9 = g_unk_010ee740 * 0x2c;
      (&g_unk_010ee4a8)[g_unk_010ee740 * 0xb] = 1;
      (&g_unk_010ee480)[g_unk_010ee740 * 0xb] =
           (tmp_f5 * (320.0 / tmp_f2) * (local_2c * tmp_f3 + local_30 * tmp_f4 + local_34 * tmp_f1) +
           320.0) - (float)tmp_i7 * 0.5;
      (&g_unk_010ee484)[g_unk_010ee740 * 0xb] =
           (240.0 - tmp_f6 * (240.0 / tmp_f2) *
                    (tmp_f3 * local_20 + tmp_f4 * local_24 + tmp_f1 * local_28)) - (float)tmp_i8 * 0.5;
      (&g_unk_010ee488)[g_unk_010ee740 * 0xb] = (float)tmp_l11;
      (&g_unk_010ee490)[g_unk_010ee740 * 0xb] = param_1;
      *(float *)(&g_unk_010ee494 + tmp_i9) = *param_2;
      *(float *)(&g_unk_010ee498 + tmp_i9) = param_2[1];
      g_unk_010ee740 = g_unk_010ee740 + 1;
      *(float *)(&g_unk_010ee49c + tmp_i9) = param_2[2];
    }
  }
  return;
}

void CG_AddWoundedPlayer(uint32_t param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  if (g_unk_010eecc4 < 0x20) {
    AngleVectors(&g_unk_01091a54,&local_40,&local_34,&local_28);
    tmp_f1 = *param_2 - g_unk_010918c0;
    tmp_f4 = param_2[1] - g_unk_010918c4;
    tmp_f3 = param_2[2] - g_unk_010918c8;
    tmp_f2 = local_38 * tmp_f3 + local_3c * tmp_f4 + local_40 * tmp_f1;
    if (0.01 <= tmp_f2) {
      tmp_f5 = 96.0 / g_unk_010918b8;
      tmp_f6 = 102.0 / g_unk_010918bc;
      tmp_i7 = CG_Text_Width_Ext(param_1,0x3e3851ec,0,0x110afec);
      tmp_i8 = CG_Text_Height_Ext(param_1,0x3e3851ec,0,0x110afec);
      param_2[1] = param_2[1] - (float)tmp_i7 * 0.5;
      *param_2 = *param_2 - (float)tmp_i8 * 0.5;
      tmp_i9 = g_unk_010eecc4 * 0x2c;
      *(float *)(&g_unk_010ee744 + tmp_i9) =
           (tmp_f5 * (320.0 / tmp_f2) * (local_2c * tmp_f3 + local_30 * tmp_f4 + local_34 * tmp_f1) +
           320.0) - (float)tmp_i7 * 0.5;
      *(uint32_t *)((int)&g_unk_010ee749 + tmp_i9 + 3) = 0x3e3851ec;
      *(float *)((int)&g_unk_010ee745 + tmp_i9 + 3) =
           (240.0 - tmp_f6 * (240.0 / tmp_f2) *
                    (tmp_f3 * local_20 + tmp_f4 * local_24 + tmp_f1 * local_28)) - (float)tmp_i8 * 0.5;
      (&g_unk_010ee754)[g_unk_010eecc4 * 0xb] = param_1;
      *(float *)(&g_unk_010ee758 + g_unk_010eecc4 * 0x16) = *param_2;
      *(float *)(&g_unk_010ee75c + tmp_i9) = param_2[1];
      g_unk_010eecc4 = g_unk_010eecc4 + 1;
      *(float *)(&g_unk_010ee760 + tmp_i9) = param_2[2];
    }
  }
  return;
}

void CG_AddToListFront(int *param_1,int param_2)
{
  *(int *)(param_2 + 0x124) = *param_1;
  *param_1 = param_2;
  return;
}

void CG_AddPMItem(uint param_1,char *param_2,uint param_3,uint *param_4)
{
  uint *tmp_pu1;
  int tmp_i2;
  size_t tmp_s3;
  char *tmp_pc4;
  int *tmp_pi5;
  uint *tmp_pu6;
  uint *tmp_pu7;
  uint *tmp_pu8;
  
  if ((param_2 != (char *)0x0) && (*param_2 != '\0')) {
    if (10 < param_1) {
      CG_Printf("Invalid popup type: %d\n",param_1);
      return;
    }
    tmp_pi5 = &g_unk_03b7f184;
    tmp_i2 = 0;
    do {
      if (*tmp_pi5 == 0) {
        tmp_pu8 = &cg_pmStack + tmp_i2 * 0x4a;
        goto LAB_000a9ab3;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pi5 = tmp_pi5 + 0x4a;
    } while (tmp_i2 != 0x20);
    tmp_pu1 = cg_pmOldList;
    tmp_pu7 = cg_pmOldList;
    if (cg_pmOldList != (uint *)0x0) {
      do {
        tmp_pu8 = tmp_pu7;
        tmp_pu6 = tmp_pu1;
        tmp_pu1 = tmp_pu8;
        tmp_pu7 = (uint *)tmp_pu8[0x49];
      } while ((uint *)tmp_pu8[0x49] != (uint *)0x0);
      if (cg_pmOldList == tmp_pu6) {
        cg_pmOldList = (uint *)0x0;
      }
      else {
        tmp_pu6[0x49] = 0;
      }
      tmp_pu8[1] = 0;
LAB_000a9ab3:
      if (param_3 == 0) {
        param_3 = *(uint *)(cgs + param_1 * 4 + 0x202b8);
      }
      tmp_pu8[0x45] = param_3;
      tmp_pu1 = tmp_pu8 + 3;
      tmp_pu8[1] = 1;
      *tmp_pu8 = param_1;
      Q_strncpyz(tmp_pu1,param_2,0x80);
      Q_strncpyz(tmp_pu8 + 0x23,&g_unk_0011d841,0x80);
      tmp_pu8[0x43] = 0;
      tmp_pu8[0x44] = 0;
      tmp_pu8[0x48] = 0x3f800000;
      tmp_pu8[0x47] = 0x3f800000;
      tmp_pu8[0x46] = 0x3f800000;
      if (param_4 != (uint *)0x0) {
        tmp_pu8[0x46] = *param_4;
        tmp_pu8[0x47] = param_4[1];
        tmp_pu8[0x48] = param_4[2];
      }
      tmp_s3 = strlen((char *)tmp_pu1);
      if ((*(char *)((int)tmp_pu8 + tmp_s3 + 0xb) != '\n') && (tmp_s3 < 0x80)) {
        *(uint8_t *)((int)tmp_pu8 + tmp_s3 + 0xc) = 10;
        *(uint8_t *)((int)tmp_pu8 + tmp_s3 + 0xd) = 0;
      }
      trap_Print(tmp_pu1);
      while (tmp_pc4 = strchr((char *)tmp_pu1,10), tmp_pc4 != (char *)0x0) {
        *tmp_pc4 = '\0';
      }
      if ((char)tmp_pu8[3] != '\0') {
        tmp_pu1 = cg_pmWaitingList;
        if (cg_pmWaitingList == (uint *)0x0) {
          cg_pmWaitingList = tmp_pu8;
          tmp_pu8[2] = g_unk_010906e0;
        }
        else {
          do {
            tmp_pu7 = tmp_pu1;
            tmp_pu1 = (uint *)tmp_pu7[0x49];
          } while (tmp_pu1 != (uint *)0x0);
          tmp_pu7[0x49] = (uint)tmp_pu8;
        }
      }
    }
  }
  return;
}

void CG_AddPMItemBig(int param_1,uint32_t param_2,int param_3,uint32_t *param_4)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  
  if (g_unk_03b816a4 == 0) {
    tmp_i1 = 0;
  }
  else if (_DAT_03b81744 == 0) {
    tmp_i1 = 1;
  }
  else if (_DAT_03b817e4 == 0) {
    tmp_i1 = 2;
  }
  else if (_DAT_03b81884 == 0) {
    tmp_i1 = 3;
  }
  else if (_DAT_03b81924 == 0) {
    tmp_i1 = 4;
  }
  else if (_DAT_03b819c4 == 0) {
    tmp_i1 = 5;
  }
  else if (_DAT_03b81a64 == 0) {
    tmp_i1 = 6;
  }
  else {
    tmp_i1 = 7;
    if (_DAT_03b81b04 != 0) {
      return;
    }
  }
  if (param_3 == 0) {
    param_3 = *(int *)(cgs + param_1 * 4 + 0x202b8);
  }
  tmp_i4 = tmp_i1 * 0xa0;
  *(int *)(&g_unk_03b8172c + tmp_i4) = param_3;
  (&cg_pmStackBig)[tmp_i1 * 0x28] = param_1;
  (&g_unk_03b816a4)[tmp_i1 * 0x28] = 1;
  *(uint32_t *)(tmp_i4 + 0x3b8173c) = 0;
  Q_strncpyz(tmp_i4 + 0x3b816ac,param_2,0x80);
  *(uint32_t *)(tmp_i4 + 0x3b81738) = 0x3f800000;
  *(uint32_t *)(tmp_i4 + 0x3b81734) = 0x3f800000;
  *(uint32_t *)(tmp_i4 + 0x3b81730) = 0x3f800000;
  if (param_4 != (uint32_t *)0x0) {
    *(uint32_t *)(tmp_i4 + 0x3b81730) = *param_4;
    *(uint32_t *)(tmp_i4 + 0x3b81734) = param_4[1];
    *(uint32_t *)(tmp_i4 + 0x3b81738) = param_4[2];
  }
  tmp_i2 = g_unk_01047b00;
  tmp_i4 = (int)cg_pmWaitingListBig;
  if (cg_pmWaitingListBig == (uint32_t *)0x0) {
    cg_pmWaitingListBig = &cg_pmStackBig + tmp_i1 * 0x28;
    *(uint32_t *)(tmp_i1 * 0xa0 + 0x3b816a8) = g_unk_010906e0;
    if ((tmp_i2 != 0) &&
       ((tmp_u3 = GHIDRA_FIELD(cgs, 69644, 4), (&cg_pmStackBig)[tmp_i1 * 0x28] == 0 ||
        (tmp_u3 = GHIDRA_FIELD(cgs, 69640, 4), (&cg_pmStackBig)[tmp_i1 * 0x28] == 1)))) {
      trap_S_StartSound(0,*(uint32_t *)(tmp_i2 + 0xcc),0,tmp_u3);
    }
    return;
  }
  do {
    tmp_i2 = tmp_i4;
    tmp_i4 = *(int *)(tmp_i2 + 0x9c);
  } while (tmp_i4 != 0);
  *(uint32_t **)(tmp_i2 + 0x9c) = &cg_pmStackBig + tmp_i1 * 0x28;
  return;
}

void CG_AddToNotify(char *param_1)
{
  char tmp_c1;
  void *tmp_pc2;
  uint32_t tmp_u3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  char tmp_c6;
  char *tmp_pc7;
  char *tmp_pc8;
  char *tmp_pc9;
  char *tmp_pc10;
  int tmp_i11;
  int tmp_i12;
  double tmp_d13;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xb4d10;
  trap_Cvar_VariableStringBuffer("con_notifytime",local_41c,0x400);
  tmp_d13 = strtod(local_41c,(char **)0x0);
  if ((float)tmp_d13 * 1000.0 <= 0.0) {
    GHIDRA_FIELD(cgs, 67772, 4) = 0;
    GHIDRA_FIELD(cgs, 67768, 4) = 0;
    return;
  }
  tmp_pc9 = (char *)0x0;
  tmp_i11 = ((int)GHIDRA_FIELD(cgs, 67768, 4) % 5) * 0xf1;
  cgs[tmp_i11 + 0x103ec] = 0;
  tmp_u3 = g_unk_010906e0;
  tmp_pc8 = cgs + tmp_i11 + 0x103ec;
  tmp_c1 = '7';
  tmp_i11 = 0;
  tmp_c6 = *param_1;
  while (tmp_pc7 = tmp_pc8, tmp_c6 != '\0') {
    if (tmp_i11 < 0x50) {
      if (tmp_c6 == '\n') {
        if (param_1[1] == '\0') goto LAB_000b4e00;
        goto LAB_000b4e80;
      }
      tmp_pc10 = param_1;
      if (tmp_c6 == '^') goto LAB_000b4f1d;
LAB_000b4ded:
      if (tmp_c6 == ' ') {
        tmp_c6 = ' ';
        tmp_pc9 = tmp_pc7;
        tmp_pc10 = param_1;
      }
      else {
        while (tmp_c6 == '\n') {
LAB_000b4e00:
          param_1 = param_1 + 1;
          tmp_c6 = *param_1;
        }
        tmp_pc10 = param_1;
        if (tmp_c6 == '\0') break;
      }
LAB_000b4f5c:
      *tmp_pc7 = tmp_c6;
      tmp_c6 = tmp_pc10[1];
      tmp_i11 = tmp_i11 + 1;
      tmp_pc8 = tmp_pc7 + 1;
      param_1 = tmp_pc10 + 1;
    }
    else {
LAB_000b4e80:
      if (tmp_pc9 != (char *)0x0) {
        tmp_i11 = (int)tmp_pc8 - (int)tmp_pc9;
        tmp_pc8 = tmp_pc8 + -tmp_i11;
        param_1 = param_1 + (1 - tmp_i11);
      }
      *tmp_pc8 = '\0';
      tmp_i12 = GHIDRA_FIELD(cgs, 67768, 4) + 1;
      tmp_i11 = (int)GHIDRA_FIELD(cgs, 67768, 4) % 5;
      GHIDRA_FIELD(cgs, 67768, 4) = tmp_i12;
      *(uint32_t *)(cgs + (int)("sendto" + tmp_i11 * 4 + 6)) = tmp_u3;
      tmp_i11 = (tmp_i12 % 5) * 0xf1;
      cgs[tmp_i11 + 0x103ec] = 0x5e;
      cgs[tmp_i11 + 0x103ed] = tmp_c1;
      if (param_1 == (char *)0x0) {
        tmp_pc2 = (void *)invalidInstructionException();
        (*tmp_pc2)();
      }
      tmp_c6 = *param_1;
      tmp_pc7 = cgs + tmp_i11 + 0x103ee;
      tmp_pc9 = (char *)0x0;
      tmp_i11 = 0;
      tmp_pc10 = param_1;
      if (tmp_c6 != '^') goto LAB_000b4ded;
LAB_000b4f1d:
      if ((tmp_pc10[1] == '\0') || (tmp_pc10[1] == '^')) {
        tmp_c6 = '^';
        goto LAB_000b4f5c;
      }
      *tmp_pc7 = '^';
      param_1 = tmp_pc10 + 2;
      tmp_pc8 = tmp_pc7 + 2;
      tmp_c1 = tmp_pc10[1];
      tmp_pc7[1] = tmp_c1;
      tmp_c6 = *param_1;
    }
  }
  *tmp_pc7 = '\0';
  tmp_u5 = GHIDRA_FIELD(cgs, 67772, 4);
  tmp_u4 = GHIDRA_FIELD(cgs, 67768, 4);
  *(uint32_t *)(cgs + (int)("sendto" + ((int)GHIDRA_FIELD(cgs, 67768, 4) % 5) * 4 + 6)) = tmp_u3;
  GHIDRA_FIELD(cgs, 67768, 4) = GHIDRA_FIELD(cgs, 67768, 4) + 1;
  if (5 < (int)(GHIDRA_FIELD(cgs, 67768, 4) - tmp_u5)) {
    GHIDRA_FIELD(cgs, 67772, 4) = tmp_u4 + -4;
  }
  return;
}

void CG_AddBufferedVoiceChat(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  bool tmp_b5;
  
  tmp_u3 = 0;
  do {
    tmp_u1 = *(uint32_t *)(param_1 + tmp_u3);
    *(uint32_t *)((int)&g_unk_03b83fa4 + tmp_u3) = *(uint32_t *)(param_1 + 4 + tmp_u3);
    *(uint32_t *)((int)&voiceChatBuffer + tmp_u3) = tmp_u1;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0x148);
  g_unk_010ab2e8 = 0;
  if ((GHIDRA_FIELD(cg_noVoiceChats, 12, 4) == 0) &&
     (trap_S_StartLocalSound(g_unk_03b83fa4,3), tmp_i2 = g_unk_03b83fa8, voiceChatBuffer != -1)) {
    if (voiceChatBuffer == *(int *)(g_unk_01047b00 + 0xcc)) {
      g_unk_01091634 = g_unk_03b83fa8;
      if (g_unk_03b83fa8 == GHIDRA_FIELD(cgs, 67984, 4)) {
        g_unk_01091638 = GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) + g_unk_010906e0;
      }
      else {
        g_unk_01091638 = g_unk_010906e0 + GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) * 2;
      }
    }
    else {
      tmp_i4 = voiceChatBuffer * 0xaf8;
      *(uint32_t *)(cg_entities + tmp_i4 + 0x794) = g_unk_03b840dc;
      tmp_b5 = tmp_i2 == GHIDRA_FIELD(cgs, 67984, 4);
      *(uint32_t *)(cg_entities + tmp_i4 + 0x798) = g_unk_03b840e0;
      tmp_u1 = g_unk_03b840e4;
      *(int *)(cg_entities + tmp_i4 + 0x98c) = tmp_i2;
      *(uint32_t *)(cg_entities + tmp_i4 + 0x79c) = tmp_u1;
      if (tmp_b5) {
        *(int *)(cg_entities + tmp_i4 + 0x990) = GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) + g_unk_010906e0;
      }
      else {
        *(int *)(cg_entities + tmp_i4 + 0x990) = g_unk_010906e0 + GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) * 2;
      }
    }
  }
  if ((g_unk_03b83fac == 0) && (GHIDRA_FIELD(cg_noVoiceText, 12, 4) == 0)) {
    CG_AddToTeamChat(&g_unk_03b84046,voiceChatBuffer);
    CG_Printf("[skipnotify]: %s\n",&g_unk_03b84046);
    if (GHIDRA_FIELD(cg_clientLog, 12, 4) != 0) {
      CG_WriteToLog(&g_unk_00121ff9,&g_unk_03b84046);
    }
  }
  (&g_unk_03b83fa4)[g_unk_010ab2ec * 0x52] = 0;
  return;
}

void CG_VoiceChatLocal(int param_1,uint32_t param_2,uint param_3,uint32_t param_4,
                      uint32_t param_5,uint32_t *param_6,float param_7)

{
  int tmp_i1;
  uint tmp_u2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  uint8_t *tmp_pu5;
  int tmp_i6;
  uint8_t *tmp_pu7;
  uint32_t local_16c;
  uint32_t local_168;
  uint local_164 [4];
  uint8_t local_154 [150];
  uint8_t local_be [150];
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  tmp_u2 = 0;
  if (param_3 < 0x40) {
    tmp_u2 = param_3;
  }
  if (*(int *)(cgs + tmp_u2 * 0x1a4 + 0x9494) == 1) {
    tmp_pu5 = voiceChatLists;
  }
  else {
    tmp_pu5 = (uint8_t *)0x3c25228;
  }
  tmp_pu7 = tmp_pu5 + 0x48;
  GHIDRA_FIELD(cgs, 33525340, 4) = tmp_u2;
  if (0 < *(int *)(tmp_pu5 + 0x44)) {
    tmp_i6 = 0;
    do {
      tmp_i1 = Q_stricmp(param_5,tmp_pu7);
      if (tmp_i1 == 0) {
        tmp_i1 = tmp_i6 * 0x251 + (int)ROUND((float)*(int *)(tmp_pu5 + tmp_i6 * 0x944 + 0x88) * param_7)
        ;
        local_164[1] = *(uint *)(tmp_pu5 + tmp_i1 * 4 + 0x8c);
        tmp_pu7 = tmp_pu5 + tmp_i6 * 0x944 + 0x4c +
                          ((int)ROUND((float)*(int *)(tmp_pu5 + tmp_i6 * 0x944 + 0x88) * param_7) + 3)
                          * 0x40;
        local_164[2] = *(uint *)(tmp_pu5 + tmp_i1 * 4 + 0x90c);
        local_164[0] = tmp_u2;
        if (param_1 == 1) {
          local_164[3] = param_2;
          local_28 = *param_6;
          local_24 = param_6[1];
          local_20 = param_6[2];
          Q_strncpyz(local_154,param_5,0x96);
LAB_000b5fb1:
          local_16c = *param_6;
          local_168 = param_6[1];
          if (((GHIDRA_FIELD(cg_locations, 12, 4) & 2) == 0) ||
             ((tmp_pc3 = (char *)CG_GetLocationMsg(param_6), (GHIDRA_FIELD(cg_locations, 12, 4) & 8) == 0 &&
              (tmp_i6 = Q_stricmp(tmp_pc3,"Unknown"), tmp_i6 == 0)))) {
            tmp_pc3 = (char *)BG_GetLocationString(&local_16c);
          }
          else if ((GHIDRA_FIELD(cg_locations, 12, 4) & 0x10) != 0) {
            tmp_u4 = BG_GetLocationString(&local_16c);
            tmp_pc3 = (char *)va(&g_unk_0011d97b,tmp_pc3,tmp_u4);
          }
          if (tmp_pc3 == (char *)0x0) {
            tmp_pc3 = " ";
          }
          else if (*tmp_pc3 == '\0') {
            tmp_pc3 = " ";
          }
          if (param_1 == 1) {
            Com_sprintf(local_be,0x96,&g_unk_0011d985,tmp_u2 * 0x1a4 + 0x10f9274,tmp_pc3,param_4,tmp_pu7)
            ;
            goto LAB_000b5ee4;
          }
          if (param_1 == 2) {
            Com_sprintf(local_be,0x96,"<%s^7>%c%c<%s>: %c%c%s",tmp_u2 * 0x1a4 + 0x10f9274,0x5e,0x33,
                        tmp_pc3,0x5e,param_4,tmp_pu7);
            goto LAB_000b5ee4;
          }
        }
        else {
          if (GHIDRA_FIELD(cg_teamChatsOnly, 12, 4) != 0) {
            return;
          }
          local_164[3] = param_2;
          local_28 = *param_6;
          local_24 = param_6[1];
          local_20 = param_6[2];
          Q_strncpyz(local_154,param_5,0x96);
          if (param_1 != 0) goto LAB_000b5fb1;
        }
        Com_sprintf(local_be,0x96,"%s%c%c: %c%c%s",tmp_u2 * 0x1a4 + 0x10f9274,0x5e,0x33,0x5e,param_4,
                    tmp_pu7);
LAB_000b5ee4:
        tmp_u2 = 0;
        do {
          tmp_u4 = *(uint32_t *)((int)local_164 + tmp_u2 + 4);
          *(uint32_t *)((int)&voiceChatBuffer + tmp_u2) = *(uint32_t *)((int)local_164 + tmp_u2);
          *(uint32_t *)((int)&g_unk_03b83fa4 + tmp_u2) = tmp_u4;
          tmp_u2 = tmp_u2 + 8;
        } while (tmp_u2 < 0x148);
        g_unk_010ab2e8 = 0;
        CG_PlayVoiceChat(&voiceChatBuffer);
        return;
      }
      tmp_i6 = tmp_i6 + 1;
      tmp_pu7 = tmp_pu7 + 0x944;
    } while (tmp_i6 < *(int *)(tmp_pu5 + 0x44));
  }
  return;
}

void CG_AddBufferedSoundScript(uint32_t param_1)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  
  if (g_unk_010b49bc < 0x10) {
    tmp_i3 = g_unk_010b49bc + 1;
    tmp_pu1 = &g_unk_010b4978 + g_unk_010b49bc;
    g_unk_010b49bc = tmp_i3;
    *tmp_pu1 = param_1;
    tmp_i2 = g_unk_010906e0;
    if (tmp_i3 == 1) {
      tmp_i3 = CG_SoundPickOldestRandomSound(g_unk_010b4978,0,0xffffffff);
      g_unk_010b49b8 = tmp_i3 + tmp_i2;
      return;
    }
  }
  return;
}

void CG_AddLineToScene(uint32_t *param_1,uint32_t *param_2,float *param_3)
{
  uint tmp_u1;
  uint32_t local_f8 [45];
  uint8_t local_44;
  uint8_t local_43;
  uint8_t local_42;
  uint8_t local_41;
  uint32_t uStack_8;
  
  tmp_u1 = 0;
  uStack_8 = 0xc0e68;
  do {
    *(uint32_t *)((int)local_f8 + tmp_u1) = 0;
    *(uint32_t *)((int)local_f8 + tmp_u1 + 4) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0xe8);
  *(uint32_t *)((int)local_f8 + tmp_u1) = 0;
  local_f8[0] = 5;
  local_f8[0x2c] = GHIDRA_FIELD(cgs, 67956, 4);
  local_f8[0x1a] = *param_1;
  local_f8[0x1b] = param_1[1];
  local_f8[0x1c] = param_1[2];
  local_f8[0x21] = *param_2;
  local_f8[0x22] = param_2[1];
  local_f8[0x23] = param_2[2];
  local_44 = (uint8_t)(short)ROUND(*param_3 * 255.0);
  local_43 = (uint8_t)(short)ROUND(param_3[1] * 255.0);
  local_42 = (uint8_t)(short)ROUND(param_3[2] * 255.0);
  local_41 = (uint8_t)(short)ROUND(param_3[3] * 255.0);
  trap_R_AddRefEntityToScene(local_f8);
  return;
}

void CG_AddScriptSpeakers(void)
{
  float tmp_f1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int local_24;
  
  if (g_unk_010b4554 != 0) {
    CG_RenderScriptSpeakers();
  }
  tmp_i2 = BG_NumScriptSpeakers();
  tmp_i6 = 0;
  if (0 < tmp_i2) {
    do {
      tmp_i2 = BG_GetScriptSpeaker(tmp_i6);
      if (*(int *)(tmp_i2 + 0x40) != 0) {
        if ((*(int *)(tmp_i2 + 0x74) == 0) && (*(int *)(tmp_i2 + 0x90) <= g_unk_010906e0)) {
          if (*(int *)(tmp_i2 + 0x7c) == 0) {
            local_24 = *(int *)(tmp_i2 + 0x80);
            if (local_24 == 0) goto LAB_000c2080;
          }
          else {
            local_24 = *(int *)(tmp_i2 + 0x80);
          }
          *(uint32_t *)(tmp_i2 + 0x8c) = 1;
          tmp_i4 = *(int *)(tmp_i2 + 0x7c) + g_unk_010906e0;
          tmp_u3 = rand();
          tmp_i5 = *(int *)(tmp_i2 + 0x8c);
          tmp_f1 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
          *(int *)(tmp_i2 + 0x90) = (int)ROUND((tmp_f1 + tmp_f1) * (float)local_24 + (float)tmp_i4);
        }
        else {
LAB_000c2080:
          tmp_i5 = *(int *)(tmp_i2 + 0x8c);
        }
        if (tmp_i5 == 0) {
          *(uint32_t *)(tmp_i2 + 0x94) = 0;
        }
        else {
          tmp_i5 = *(int *)(tmp_i2 + 0x78);
          if (tmp_i5 == 1) {
            tmp_u3 = *(uint *)(tmp_i2 + 0x74);
            if (tmp_u3 == 0) {
              trap_S_StartLocalSound(*(uint32_t *)(tmp_i2 + 0x40),4);
              tmp_u3 = *(uint *)(tmp_i2 + 0x74);
            }
            else {
LAB_000c215e:
              if (tmp_u3 < 3) {
                tmp_i5 = *(int *)(tmp_i2 + 0x94);
                if (tmp_i5 == 0) {
                  tmp_i5 = trap_S_GetCurrentSoundTime();
                  *(int *)(tmp_i2 + 0x94) = tmp_i5;
                }
                trap_S_AddRealLoopingSound
                          (tmp_i2 + 0x44,&vec3_origin,*(uint32_t *)(tmp_i2 + 0x40),
                           *(uint32_t *)(tmp_i2 + 0x88),*(uint32_t *)(tmp_i2 + 0x84),tmp_i5);
                tmp_u3 = *(uint *)(tmp_i2 + 0x74);
              }
            }
          }
          else if (tmp_i5 == 0) {
            tmp_i5 = tmp_i2 + 0x44;
            tmp_i4 = trap_R_inPVS(g_unk_010afbcc + 0x18,tmp_i5);
            tmp_u3 = *(uint *)(tmp_i2 + 0x74);
            if (tmp_i4 != 0) {
              if (tmp_u3 == 0) {
                trap_S_StartSoundVControl
                          (tmp_i5,0xffffffff,4,*(uint32_t *)(tmp_i2 + 0x40),
                           *(uint32_t *)(tmp_i2 + 0x84));
                tmp_u3 = *(uint *)(tmp_i2 + 0x74);
              }
              else if (tmp_u3 < 3) {
                tmp_i4 = *(int *)(tmp_i2 + 0x94);
                if (tmp_i4 == 0) {
                  tmp_i4 = trap_S_GetCurrentSoundTime();
                  *(int *)(tmp_i2 + 0x94) = tmp_i4;
                }
                trap_S_AddRealLoopingSound
                          (tmp_i5,&vec3_origin,*(uint32_t *)(tmp_i2 + 0x40),
                           *(uint32_t *)(tmp_i2 + 0x88),*(uint32_t *)(tmp_i2 + 0x84),tmp_i4);
                tmp_u3 = *(uint *)(tmp_i2 + 0x74);
              }
            }
          }
          else {
            tmp_u3 = *(uint *)(tmp_i2 + 0x74);
            if (tmp_i5 == 2) {
              if (tmp_u3 != 0) goto LAB_000c215e;
              trap_S_StartSoundVControl
                        (tmp_i2 + 0x44,0xffffffff,4,*(uint32_t *)(tmp_i2 + 0x40),
                         *(uint32_t *)(tmp_i2 + 0x84));
              tmp_u3 = *(uint *)(tmp_i2 + 0x74);
            }
          }
          if (tmp_u3 == 0) {
            *(uint32_t *)(tmp_i2 + 0x8c) = 0;
          }
        }
      }
      tmp_i6 = tmp_i6 + 1;
      tmp_i2 = BG_NumScriptSpeakers();
    } while (tmp_i6 < tmp_i2);
  }
  return;
}

void CG_AddSpawnVarToken(char *param_1)
{
  uint tmp_u1;
  char tmp_c2;
  uint16_t tmp_u3;
  uint32_t tmp_u4;
  size_t tmp_s5;
  char *tmp_pc6;
  char *tmp_pc7;
  byte tmp_b8;
  uint local_24;
  
  tmp_b8 = 0;
  tmp_s5 = strlen(param_1);
  if (0x7ff < (int)(g_unk_010ab550 + tmp_s5)) {
    CG_Error("CG_AddSpawnVarToken: MAX_SPAWN_VARS");
  }
  tmp_pc6 = &g_unk_010ab554 + g_unk_010ab550;
  tmp_u1 = tmp_s5 + 1;
  local_24 = tmp_u1;
  if (7 < tmp_u1) {
    if (((uint)tmp_pc6 & 1) != 0) {
      tmp_c2 = *param_1;
      param_1 = param_1 + 1;
      tmp_pc6 = (char *)((int)&g_unk_010ab555 + g_unk_010ab550);
      (&g_unk_010ab554)[g_unk_010ab550] = tmp_c2;
      local_24 = tmp_s5;
    }
    tmp_pc7 = tmp_pc6;
    if (((uint)tmp_pc6 & 2) != 0) {
      tmp_u3 = *(uint16_t *)param_1;
      tmp_pc7 = tmp_pc6 + 2;
      param_1 = param_1 + 2;
      *(uint16_t *)tmp_pc6 = tmp_u3;
      local_24 = local_24 - 2;
    }
    tmp_pc6 = tmp_pc7;
    if (((uint)tmp_pc7 & 4) != 0) {
      tmp_u4 = *(uint32_t *)param_1;
      tmp_pc6 = tmp_pc7 + 4;
      param_1 = param_1 + 4;
      *(uint32_t *)tmp_pc7 = tmp_u4;
      local_24 = local_24 - 4;
    }
  }
  for (; local_24 != 0; local_24 = local_24 - 1) {
    *tmp_pc6 = *param_1;
    param_1 = param_1 + (uint)tmp_b8 * -2 + 1;
    tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
  }
  g_unk_010ab550 = g_unk_010ab550 + tmp_u1;
  return;
}

void CG_AddTrailToScene(int param_1,int param_2,int param_3)
{
  int *tmp_pi1;
  int tmp_i2;
  float *pfVar3;
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
  float tmp_f19;
  float tmp_f20;
  float tmp_f21;
  float tmp_f22;
  float tmp_f23;
  byte tmp_b24;
  byte tmp_b25;
  byte tmp_b26;
  byte tmp_b27;
  byte tmp_b28;
  byte tmp_b29;
  byte tmp_b30;
  byte tmp_b31;
  byte tmp_b32;
  byte tmp_b33;
  byte tmp_b34;
  byte tmp_b35;
  byte tmp_b36;
  byte tmp_b37;
  byte tmp_b38;
  byte tmp_b39;
  int tmp_i40;
  int tmp_i41;
  uint tmp_u42;
  double *pdVar43;
  float *pfVar44;
  int tmp_i45;
  float *pfVar46;
  int tmp_i47;
  uint32_t *tmp_pu48;
  int tmp_i49;
  int tmp_i50;
  long double tmp_l51;
  uint32_t tmp_u52;
  uint32_t *tmp_pu53;
  float local_94;
  int local_90;
  int local_8c;
  int local_88;
  uint8_t local_84;
  uint8_t local_6c;
  float local_64;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  if (((*(byte *)(param_1 + 0x2c) & 0x10) != 0) &&
     (tmp_i45 = CG_PB_FindFreePolyBuffer(GHIDRA_FIELD(cgs, 68860, 4),4,6), tmp_i45 != 0)) {
    tmp_i2 = *(int *)(tmp_i45 + 0x701c);
    tmp_i49 = tmp_i2 * 0x10;
    pfVar44 = (float *)(tmp_i45 + tmp_i49);
    *pfVar44 = *(float *)(param_1 + 0x34);
    pfVar46 = (float *)(tmp_i45 + 4 + tmp_i49);
    pfVar3 = (float *)(tmp_i45 + 8 + tmp_i49);
    *pfVar46 = *(float *)(param_1 + 0x38);
    *pfVar3 = *(float *)(param_1 + 0x3c);
    tmp_f4 = vup;
    *pfVar44 = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * vup + *pfVar44;
    tmp_f5 = g_unk_00c21a44;
    *pfVar46 = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * g_unk_00c21a44 + *pfVar46
    ;
    tmp_f6 = g_unk_00c21a48;
    *pfVar3 = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * g_unk_00c21a48 + *pfVar3;
    tmp_f7 = vright;
    *pfVar44 = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * vright + *pfVar44;
    tmp_f8 = g_unk_00c21a50;
    *pfVar46 = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * g_unk_00c21a50 + *pfVar46
    ;
    tmp_f9 = g_unk_00c21a54;
    tmp_i41 = tmp_i45 + tmp_i2 * 8;
    *pfVar3 = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * g_unk_00c21a54 + *pfVar3;
    *(uint32_t *)(tmp_i41 + 0x4010) = 0;
    *(uint32_t *)(tmp_i45 + 0x4014 + tmp_i2 * 8) = 0;
    tmp_i49 = tmp_i2 + 1;
    pfVar44[4] = *(float *)(param_1 + 0x34);
    pfVar46 = (float *)(tmp_i45 + 4 + tmp_i49 * 0x10);
    pfVar3 = (float *)(tmp_i45 + 8 + tmp_i49 * 0x10);
    *pfVar46 = *(float *)(param_1 + 0x38);
    *pfVar3 = *(float *)(param_1 + 0x3c);
    pfVar44[4] = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * tmp_f4 + pfVar44[4];
    *pfVar46 = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * tmp_f5 + *pfVar46;
    *pfVar3 = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * tmp_f6 + *pfVar3;
    pfVar44[4] = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f7 + pfVar44[4];
    *pfVar46 = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f8 + *pfVar46;
    tmp_i50 = tmp_i2 + 2;
    *pfVar3 = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f9 + *pfVar3;
    *(uint32_t *)(tmp_i41 + 0x4018) = 0;
    *(uint32_t *)(tmp_i45 + 0x4014 + tmp_i49 * 8) = 0x3f800000;
    pfVar44[8] = *(float *)(param_1 + 0x34);
    pfVar46 = (float *)(tmp_i45 + 4 + tmp_i50 * 0x10);
    pfVar3 = (float *)(tmp_i45 + 8 + tmp_i50 * 0x10);
    *pfVar46 = *(float *)(param_1 + 0x38);
    *pfVar3 = *(float *)(param_1 + 0x3c);
    pfVar44[8] = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f4 + pfVar44[8];
    *pfVar46 = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f5 + *pfVar46;
    *pfVar3 = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f6 + *pfVar3;
    pfVar44[8] = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f7 + pfVar44[8];
    *pfVar46 = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f8 + *pfVar46;
    *pfVar3 = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f9 + *pfVar3;
    *(uint32_t *)(tmp_i41 + 0x4020) = 0x3f800000;
    *(uint32_t *)(tmp_i45 + 0x4014 + tmp_i50 * 8) = 0x3f800000;
    tmp_i47 = tmp_i2 + 3;
    pfVar44[0xc] = *(float *)(param_1 + 0x34);
    pfVar46 = (float *)(tmp_i45 + 4 + tmp_i47 * 0x10);
    pfVar3 = (float *)(tmp_i45 + 8 + tmp_i47 * 0x10);
    *pfVar46 = *(float *)(param_1 + 0x38);
    *pfVar3 = *(float *)(param_1 + 0x3c);
    pfVar44[0xc] = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f4 + pfVar44[0xc];
    *pfVar46 = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f5 + *pfVar46;
    *pfVar3 = (*(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x74)) * tmp_f6 + *pfVar3;
    pfVar44[0xc] = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * tmp_f7 +
                   pfVar44[0xc];
    *pfVar46 = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * tmp_f8 + *pfVar46;
    *pfVar3 = (-*(float *)(param_1 + 0x74) + -*(float *)(param_1 + 0x74)) * tmp_f9 + *pfVar3;
    *(uint32_t *)(tmp_i41 + 0x4028) = 0x3f800000;
    *(uint32_t *)(tmp_i45 + 0x4014 + tmp_i47 * 8) = 0;
    *(uint8_t *)(tmp_i45 + 0x6018 + tmp_i2 * 4) = 0xff;
    *(uint8_t *)(tmp_i45 + 0x6019 + tmp_i2 * 4) = 0xff;
    *(uint8_t *)(tmp_i45 + 0x601a + tmp_i2 * 4) = 0xff;
    *(char *)(tmp_i45 + 0x601b + tmp_i2 * 4) = (char)(short)ROUND(*(float *)(param_1 + 0x70) * 255.0);
    *(uint8_t *)(tmp_i45 + 0x601c + tmp_i2 * 4) = 0xff;
    *(uint8_t *)(tmp_i45 + 0x6019 + tmp_i49 * 4) = 0xff;
    *(uint8_t *)(tmp_i45 + 0x601a + tmp_i49 * 4) = 0xff;
    *(char *)(tmp_i45 + 0x601b + tmp_i49 * 4) = (char)(short)ROUND(*(float *)(param_1 + 0x70) * 255.0)
    ;
    *(uint8_t *)(tmp_i45 + 0x6020 + tmp_i2 * 4) = 0xff;
    *(uint8_t *)(tmp_i45 + 0x6019 + tmp_i50 * 4) = 0xff;
    *(uint8_t *)(tmp_i45 + 0x601a + tmp_i50 * 4) = 0xff;
    *(char *)(tmp_i45 + 0x601b + tmp_i50 * 4) = (char)(short)ROUND(*(float *)(param_1 + 0x70) * 255.0)
    ;
    *(uint8_t *)(tmp_i45 + 0x6024 + tmp_i2 * 4) = 0xff;
    *(uint8_t *)(tmp_i45 + 0x6019 + tmp_i47 * 4) = 0xff;
    *(uint8_t *)(tmp_i45 + 0x601a + tmp_i47 * 4) = 0xff;
    *(char *)(tmp_i45 + 0x601b + tmp_i47 * 4) = (char)(short)ROUND(*(float *)(param_1 + 0x70) * 255.0)
    ;
    tmp_i40 = *(int *)(tmp_i45 + 0xd038);
    tmp_i41 = tmp_i45 + tmp_i40 * 4;
    *(int *)(tmp_i41 + 0x7020) = tmp_i2;
    *(int *)(tmp_i41 + 0x7028) = tmp_i50;
    *(int *)(tmp_i41 + 0x702c) = tmp_i50;
    *(int *)(tmp_i41 + 0x7030) = tmp_i47;
    *(int *)(tmp_i41 + 0x7024) = tmp_i49;
    *(int *)(tmp_i41 + 0x7034) = tmp_i2;
    *(int *)(tmp_i45 + 0x701c) = tmp_i2 + 4;
    *(int *)(tmp_i45 + 0xd038) = tmp_i40 + 6;
  }
  if (param_3 == 0) {
    local_64 = 0.0;
    param_3 = 0;
    tmp_i45 = param_1;
    do {
      param_3 = param_3 + 1;
      tmp_i49 = *(int *)(tmp_i45 + 8);
      if (*(int *)(tmp_i45 + 0x18) == 0) {
        if (tmp_i49 == 0) break;
        if (*(int *)(tmp_i49 + 0x18) != 0) goto LAB_000c8b50;
        CG_KillTrail(tmp_i45);
        tmp_i49 = *(int *)(tmp_i45 + 8);
        if (tmp_i49 == 0) break;
      }
      else {
        if (tmp_i49 == 0) break;
LAB_000c8b50:
        if (*(int *)(tmp_i49 + 0x1c) != 0) {
          *(uint32_t *)(tmp_i45 + 8) = 0;
          break;
        }
      }
      tmp_l51 = (long double)VectorDistance(tmp_i49 + 0x34,tmp_i45 + 0x34);
      tmp_i45 = *(int *)(tmp_i45 + 8);
      local_64 = (float)(tmp_l51 + (long double)local_64);
    } while (tmp_i45 != 0);
  }
  else {
    local_64 = 0.0;
  }
  if (param_3 < 2) {
    return;
  }
  if (*(int *)(param_1 + 0x28) == 0) {
    local_94 = 0.05;
    tmp_i45 = *(int *)(param_1 + 8);
  }
  else {
    if (*(int *)(param_1 + 0x28) == 1) {
      local_94 = *(float *)(param_1 + 0x30);
    }
    else {
      local_94 = 0.0;
    }
    tmp_i45 = *(int *)(param_1 + 8);
  }
  if (tmp_i45 == 0) {
    tmp_u42 = *(uint *)(param_1 + 0x2c);
    if ((tmp_u42 & 8) == 0) {
      local_8c = 0;
      if ((tmp_u42 & 0x20) != 0) goto LAB_000c9069;
      goto LAB_000c9608;
    }
    if ((tmp_u42 & 0x20) != 0) goto LAB_000c9069;
    local_8c = 0;
LAB_000c9649:
    tmp_pu53 = &outVerts;
    tmp_u52 = 3;
  }
  else {
    pfVar44 = (float *)&verts;
    local_8c = 0;
    tmp_i41 = param_1;
    pfVar46 = pfVar44;
    tmp_i49 = local_8c;
    local_88 = param_1 + 0x34;
    do {
      local_8c = tmp_i49;
      tmp_i2 = tmp_i45 + 0x34;
      GetPerpendicularViewVector(g_unk_010afbcc + 0x18,local_88,tmp_i2,&local_40);
      if ((*(uint *)(tmp_i41 + 0x2c) & 2) == 0) {
        if (((*(uint *)(tmp_i41 + 0x2c) & 4) == 0) &&
           ((4.0 < *(float *)(tmp_i41 + 0x6c) || (4.0 < *(float *)(tmp_i45 + 0x6c))))) {
          ProjectPointOntoVector(g_unk_010afbcc + 0x18,local_88,tmp_i2,&local_28);
          tmp_l51 = (long double)Distance(&local_28,g_unk_010afbcc + 0x18);
          if (tmp_l51 < (long double)256.0) {
            if (tmp_l51 < (long double)64.0) {
              tmp_f4 = 0.0;
            }
            else {
              tmp_f4 = (float)((tmp_l51 - (long double)64.0) * (long double)0.00390625);
            }
            if (tmp_f4 < *(float *)(tmp_i41 + 0x70)) {
              *(float *)(tmp_i41 + 0x70) = tmp_f4;
            }
            if (tmp_f4 < *(float *)(tmp_i45 + 0x70)) {
              *(float *)(tmp_i45 + 0x70) = tmp_f4;
            }
          }
        }
      }
      else if (0 < param_2) {
        ProjectPointOntoVector(g_unk_010afbcc + 0x18,local_88,tmp_i2,&local_28);
        local_34 = *(float *)(g_unk_010afbcc + 0x18) - local_28;
        local_30 = *(float *)(g_unk_010afbcc + 0x1c) - local_24;
        local_2c = *(float *)(g_unk_010afbcc + 0x20) - local_20;
        VectorNormalize(&local_34);
        if (param_2 == 1) {
          pdVar43 = (double *)&g_unk_0010f3a0;
          tmp_f4 = 0.3;
        }
        else {
          pdVar43 = (double *)&g_unk_0011ef50;
          tmp_f4 = -0.3;
        }
        local_40 = tmp_f4 * local_34 + local_40;
        local_3c = (float)*pdVar43 * local_30 + local_3c;
        local_38 = (float)*pdVar43 * local_2c + local_38;
        VectorNormalize(&local_40);
      }
      tmp_f5 = *(float *)(tmp_i41 + 0x74) * 0.5;
      tmp_f6 = local_40 * tmp_f5 + *(float *)(tmp_i41 + 0x34);
      tmp_f4 = local_3c * tmp_f5 + *(float *)(tmp_i41 + 0x38);
      tmp_f5 = local_38 * tmp_f5 + *(float *)(tmp_i41 + 0x3c);
      *pfVar46 = tmp_f6;
      pfVar46[1] = tmp_f4;
      pfVar46[2] = tmp_f5;
      pfVar46[4] = 1.0;
      pfVar46[3] = local_94;
      *(char *)(pfVar46 + 5) = (char)(short)ROUND(*(float *)(tmp_i41 + 0x78) * 255.0);
      *(char *)((int)pfVar46 + 0x15) = (char)(short)ROUND(*(float *)(tmp_i41 + 0x7c) * 255.0);
      *(char *)((int)pfVar46 + 0x16) = (char)(short)ROUND(*(float *)(tmp_i41 + 0x80) * 255.0);
      *(char *)((int)pfVar46 + 0x17) = (char)(short)ROUND(*(float *)(tmp_i41 + 0x70) * 255.0);
      if (tmp_i41 == param_1) {
        if ((*(byte *)(tmp_i41 + 0x2c) & 1) != 0) {
          *(uint8_t *)((int)pfVar46 + 0x17) = 0;
        }
      }
      else {
        tmp_f9 = (pfVar46[-6] + tmp_f6) * 0.5;
        *pfVar46 = tmp_f9;
        tmp_f7 = (pfVar46[-5] + tmp_f4) * 0.5;
        pfVar46[1] = tmp_f7;
        tmp_f8 = (pfVar46[-4] + tmp_f5) * 0.5;
        pfVar46[2] = tmp_f8;
        pfVar46[-6] = tmp_f9;
        pfVar46[-5] = tmp_f7;
        pfVar46[-4] = tmp_f8;
      }
      tmp_f7 = -*(float *)(tmp_i41 + 0x74);
      pfVar46[10] = 0.0;
      tmp_f6 = local_40 * tmp_f7 + tmp_f6;
      pfVar46[6] = tmp_f6;
      tmp_f4 = local_3c * tmp_f7 + tmp_f4;
      pfVar46[7] = tmp_f4;
      tmp_f5 = tmp_f7 * local_38 + tmp_f5;
      pfVar46[8] = tmp_f5;
      pfVar46[9] = local_94;
      *(char *)(pfVar46 + 0xb) = (char)(short)ROUND(*(float *)(tmp_i41 + 0x78) * 255.0);
      *(char *)((int)pfVar46 + 0x2d) = (char)(short)ROUND(*(float *)(tmp_i41 + 0x7c) * 255.0);
      *(char *)((int)pfVar46 + 0x2e) = (char)(short)ROUND(*(float *)(tmp_i41 + 0x80) * 255.0);
      *(char *)((int)pfVar46 + 0x2f) = (char)(short)ROUND(*(float *)(tmp_i41 + 0x70) * 255.0);
      if (tmp_i41 == param_1) {
        if ((*(byte *)(param_1 + 0x2c) & 1) != 0) {
          *(uint8_t *)((int)pfVar46 + 0x2f) = 0;
        }
      }
      else {
        tmp_f6 = (tmp_f6 + pfVar46[-0xc]) * 0.5;
        pfVar46[6] = tmp_f6;
        tmp_f4 = (tmp_f4 + pfVar46[-0xb]) * 0.5;
        pfVar46[7] = tmp_f4;
        tmp_f5 = (tmp_f5 + pfVar46[-10]) * 0.5;
        pfVar46[8] = tmp_f5;
        pfVar46[-0xc] = tmp_f6;
        pfVar46[-0xb] = tmp_f4;
        pfVar46[-10] = tmp_f5;
      }
      if (*(int *)(param_1 + 0x28) == 1) {
        local_94 = *(float *)(tmp_i45 + 0x30);
      }
      else {
        tmp_l51 = (long double)VectorDistance(local_88,tmp_i2);
        tmp_l51 = tmp_l51 / (long double)local_64 + (long double)local_94;
        local_94 = (float)tmp_l51;
        if ((long double)1 < tmp_l51) {
          local_94 = 1.0;
        }
      }
      tmp_f4 = *(float *)(tmp_i45 + 0x74) * -0.5;
      tmp_f7 = local_40 * tmp_f4 + *(float *)(tmp_i45 + 0x34);
      tmp_f6 = local_3c * tmp_f4 + *(float *)(tmp_i45 + 0x38);
      tmp_f5 = tmp_f4 * local_38 + *(float *)(tmp_i45 + 0x3c);
      pfVar46[0xc] = tmp_f7;
      pfVar46[0xd] = tmp_f6;
      pfVar46[0xe] = tmp_f5;
      pfVar46[0x10] = 0.0;
      pfVar46[0xf] = local_94;
      *(char *)(pfVar46 + 0x11) = (char)(short)ROUND(*(float *)(tmp_i45 + 0x78) * 255.0);
      *(char *)((int)pfVar46 + 0x45) = (char)(short)ROUND(*(float *)(tmp_i45 + 0x7c) * 255.0);
      *(char *)((int)pfVar46 + 0x46) = (char)(short)ROUND(*(float *)(tmp_i45 + 0x80) * 255.0);
      *(char *)((int)pfVar46 + 0x47) = (char)(short)ROUND(*(float *)(tmp_i45 + 0x70) * 255.0);
      tmp_f4 = *(float *)(tmp_i45 + 0x74);
      pfVar46[0x16] = 1.0;
      pfVar46[0x12] = local_40 * tmp_f4 + tmp_f7;
      pfVar46[0x13] = local_3c * tmp_f4 + tmp_f6;
      pfVar46[0x14] = tmp_f4 * local_38 + tmp_f5;
      pfVar46[0x15] = local_94;
      *(char *)(pfVar46 + 0x17) = (char)(short)ROUND(*(float *)(tmp_i45 + 0x78) * 255.0);
      *(char *)((int)pfVar46 + 0x5d) = (char)(short)ROUND(*(float *)(tmp_i45 + 0x7c) * 255.0);
      tmp_i49 = local_8c + 4;
      *(char *)((int)pfVar46 + 0x5e) = (char)(short)ROUND(*(float *)(tmp_i45 + 0x80) * 255.0);
      *(char *)((int)pfVar46 + 0x5f) = (char)(short)ROUND(*(float *)(tmp_i45 + 0x70) * 255.0);
      if (tmp_i49 == 0x800) {
        if ((*(uint *)(param_1 + 0x2c) & 8) != 0) goto LAB_000c8d3e;
        tmp_i45 = 0x200;
        local_8c = tmp_i49;
        if ((*(uint *)(param_1 + 0x2c) & 0x20) != 0) goto LAB_000c910c;
        goto LAB_000c9608;
      }
      tmp_pi1 = (int *)(tmp_i45 + 8);
      pfVar46 = pfVar46 + 0x18;
      tmp_i41 = tmp_i45;
      tmp_i45 = *tmp_pi1;
      local_88 = tmp_i2;
    } while (*tmp_pi1 != 0);
    tmp_u42 = *(uint *)(param_1 + 0x2c);
    if ((tmp_u42 & 8) != 0) {
LAB_000c8d3e:
      tmp_i45 = 0;
      local_90 = 0;
      do {
        tmp_f4 = *pfVar44;
        tmp_f5 = pfVar44[6];
        tmp_f6 = pfVar44[1];
        tmp_f7 = pfVar44[7];
        tmp_f8 = pfVar44[2];
        tmp_f9 = pfVar44[8];
        tmp_f10 = pfVar44[3];
        tmp_f11 = pfVar44[9];
        tmp_f12 = pfVar44[4];
        tmp_f13 = pfVar44[10];
        tmp_f14 = pfVar44[0xc];
        tmp_f15 = pfVar44[0xd];
        tmp_f16 = pfVar44[0xe];
        tmp_f17 = pfVar44[0xf];
        tmp_f18 = pfVar44[0x10];
        tmp_f19 = pfVar44[0x12];
        tmp_f20 = pfVar44[0x13];
        tmp_f21 = pfVar44[0x14];
        tmp_f22 = pfVar44[0x15];
        tmp_f23 = pfVar44[0x16];
        tmp_b24 = *(byte *)(pfVar44 + 0xb);
        tmp_b25 = *(byte *)(pfVar44 + 5);
        tmp_b26 = *(byte *)(pfVar44 + 0x11);
        tmp_b27 = *(byte *)(pfVar44 + 0x17);
        tmp_b28 = *(byte *)((int)pfVar44 + 0x45);
        tmp_b29 = *(byte *)((int)pfVar44 + 0x2d);
        tmp_b30 = *(byte *)((int)pfVar44 + 0x15);
        tmp_b31 = *(byte *)((int)pfVar44 + 0x5d);
        tmp_b32 = *(byte *)((int)pfVar44 + 0x5e);
        tmp_b33 = *(byte *)((int)pfVar44 + 0x46);
        tmp_b34 = *(byte *)((int)pfVar44 + 0x2e);
        tmp_b35 = *(byte *)((int)pfVar44 + 0x16);
        tmp_b36 = *(byte *)((int)pfVar44 + 0x5f);
        tmp_b37 = *(byte *)((int)pfVar44 + 0x2f);
        tmp_b38 = *(byte *)((int)pfVar44 + 0x17);
        tmp_b39 = *(byte *)((int)pfVar44 + 0x47);
        tmp_pu53 = &outVerts + tmp_i45 * 6;
        tmp_i49 = tmp_i45;
        pfVar46 = pfVar44;
LAB_000c8f4a:
        tmp_i41 = tmp_i49;
        tmp_u42 = 0;
        do {
          *(uint32_t *)((int)tmp_pu53 + tmp_u42) = *(uint32_t *)((int)pfVar46 + tmp_u42);
          tmp_u42 = tmp_u42 + 4;
        } while (tmp_u42 < 0x18);
        local_6c = (uint8_t)
                   (short)ROUND(((double)tmp_b27 + (double)tmp_b26 + (double)tmp_b25 + (double)tmp_b24)
                                * 0.25);
        tmp_pu53[6] = (tmp_f4 + tmp_f5 + tmp_f14 + tmp_f19) * 0.25;
        tmp_pu53[7] = (tmp_f6 + tmp_f7 + tmp_f15 + tmp_f20) * 0.25;
        tmp_pu53[8] = (tmp_f8 + tmp_f9 + tmp_f16 + tmp_f21) * 0.25;
        *(uint8_t *)(tmp_pu53 + 0xb) = local_6c;
        local_84 = (uint8_t)
                   (short)ROUND(((double)tmp_b31 + (double)tmp_b30 + (double)tmp_b29 + (double)tmp_b28)
                                * 0.25);
        tmp_pu53[9] = (tmp_f10 + tmp_f11 + tmp_f17 + tmp_f22) * 0.25;
        tmp_pu53[10] = (tmp_f12 + tmp_f13 + tmp_f18 + tmp_f23) * 0.25;
        *(char *)((int)tmp_pu53 + 0x2f) =
             (char)(short)ROUND(((double)tmp_b39 + (double)tmp_b38 + (double)tmp_b37 + (double)tmp_b36)
                                * 0.25);
        *(uint8_t *)((int)tmp_pu53 + 0x2d) = local_84;
        GHIDRA_FIELD(local_88, 0, 1) =
             (uint8_t)
             (short)ROUND(((float)tmp_b35 + (float)tmp_b34 + (float)tmp_b33 + (float)tmp_b32) * 0.25);
        *(uint8_t *)((int)tmp_pu53 + 0x2e) = (uint8_t)local_88;
        if (tmp_i41 != tmp_i45 + 9) goto code_r0x000c8fa7;
        tmp_u42 = 0;
        do {
          *(uint32_t *)((int)&outVerts + tmp_u42 + (tmp_i41 + 2) * 0x18) =
               *(uint32_t *)((int)pfVar44 + tmp_u42);
          tmp_u42 = tmp_u42 + 4;
        } while (tmp_u42 < 0x18);
LAB_000c8fe0:
        tmp_i45 = tmp_i41 + 3;
        local_90 = local_90 + 4;
        pfVar44 = pfVar44 + 0x18;
        if (local_90 == local_8c + 4) {
          tmp_u42 = *(uint *)(param_1 + 0x2c);
          local_8c = tmp_i45 / 3;
          if ((tmp_u42 & 0x20) != 0) {
            if (local_8c < 1) goto LAB_000c9069;
            tmp_pu53 = &outVerts;
            do {
              tmp_pu48 = tmp_pu53 + 0x12;
              trap_R_AddPolyToScene(*(uint32_t *)(param_1 + 0x24),3,tmp_pu53);
              tmp_pu53 = tmp_pu48;
            } while (tmp_pu48 != &outVerts + local_8c * 0x12);
            goto LAB_000c905f;
          }
          goto LAB_000c9649;
        }
      } while( true );
    }
    local_8c = tmp_i49;
    if ((tmp_u42 & 0x20) != 0) {
      tmp_i45 = tmp_i49 >> 2;
      if (tmp_i45 != 0) {
LAB_000c910c:
        tmp_i49 = 0;
        do {
          tmp_i49 = tmp_i49 + 1;
          trap_R_AddPolyToScene(*(uint32_t *)(param_1 + 0x24),4,pfVar44);
          pfVar44 = pfVar44 + 0x18;
        } while (tmp_i49 != tmp_i45);
LAB_000c905f:
        tmp_u42 = *(uint *)(param_1 + 0x2c);
      }
      goto LAB_000c9069;
    }
LAB_000c9608:
    tmp_u52 = 4;
    local_8c = local_8c >> 2;
    tmp_pu53 = &verts;
  }
  trap_R_AddPolysToScene(*(uint32_t *)(param_1 + 0x24),tmp_u52,tmp_pu53,local_8c);
  tmp_u42 = *(uint *)(param_1 + 0x2c);
LAB_000c9069:
  if (((tmp_u42 & 2) != 0) && (param_2 < 2)) {
    CG_AddTrailToScene(param_1,param_2 + 1,param_3);
    return;
  }
  return;
code_r0x000c8fa7:
  tmp_u42 = 0;
  do {
    *(uint32_t *)((int)tmp_pu53 + tmp_u42 + 0x30) = *(uint32_t *)((int)pfVar46 + tmp_u42 + 0x18);
    tmp_u42 = tmp_u42 + 4;
  } while (tmp_u42 < 0x18);
  pfVar46 = pfVar46 + 6;
  tmp_pu53 = tmp_pu53 + 0x12;
  tmp_i49 = tmp_i41 + 3;
  if (tmp_i41 + 3 == tmp_i45 + 0xc) goto LAB_000c8fe0;
  goto LAB_000c8f4a;
}

void CG_AddTrails(void)
{
  int tmp_i1;
  float *pfVar2;
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
  float tmp_f19;
  float tmp_f20;
  float tmp_f21;
  float tmp_f22;
  byte tmp_b23;
  byte tmp_b24;
  byte tmp_b25;
  byte tmp_b26;
  byte tmp_b27;
  byte tmp_b28;
  byte tmp_b29;
  byte tmp_b30;
  byte tmp_b31;
  byte tmp_b32;
  byte tmp_b33;
  byte tmp_b34;
  byte tmp_b35;
  byte tmp_b36;
  byte tmp_b37;
  byte tmp_b38;
  int tmp_i39;
  int *tmp_pi40;
  uint tmp_u41;
  uint32_t *tmp_pu42;
  int tmp_i43;
  int tmp_i44;
  float *pfVar45;
  int tmp_i46;
  int tmp_i47;
  int tmp_i48;
  float *pfVar49;
  uint32_t *tmp_pu50;
  int tmp_i51;
  int tmp_i52;
  long double tmp_l53;
  uint32_t tmp_u54;
  float local_88;
  int local_84;
  int local_80;
  uint8_t local_7c;
  uint8_t local_74;
  uint8_t local_6c;
  float local_64;
  int local_54;
  uint32_t *local_4c;
  float local_34;
  float local_30;
  float local_2c;
  uint8_t local_28 [20];
  uint32_t uStack_14;
  
  uStack_14 = 0xc9689;
  tmp_pi40 = activeTrails;
  if (initTrails == 0) {
    memset(&trailJuncs,0,0x84000);
    tmp_i46 = 0;
    activeTrails = (int *)0x0;
    headTrails = 0;
    freeTrails = &trailJuncs;
    tmp_pu42 = &g_unk_04073f44;
    do {
      tmp_pu42[-0x21] = tmp_pu42;
      if (tmp_i46 == 0) {
        g_unk_04073ec4 = 0;
      }
      else {
        tmp_pu42[-0x20] = tmp_pu42 + -0x42;
      }
      tmp_i46 = tmp_i46 + 1;
      tmp_pu42[-0x1b] = 0;
      tmp_pu42 = tmp_pu42 + 0x21;
    } while (tmp_i46 != 0x1000);
    numTrailsInuse = 0;
    g_unk_040f7e3c = 0;
    initTrails = 1;
    tmp_pi40 = (int *)0x0;
  }
  vforward = *(uint32_t *)(g_unk_010afbcc + 0x24);
  g_unk_00c21a5c = *(uint32_t *)(g_unk_010afbcc + 0x28);
  g_unk_00c21a60 = *(uint32_t *)(g_unk_010afbcc + 0x2c);
  vright = *(float *)(g_unk_010afbcc + 0x30);
  g_unk_00c21a50 = *(float *)(g_unk_010afbcc + 0x34);
  g_unk_00c21a54 = *(float *)(g_unk_010afbcc + 0x38);
  vup = *(float *)(g_unk_010afbcc + 0x3c);
  g_unk_00c21a44 = *(float *)(g_unk_010afbcc + 0x40);
  g_unk_00c21a48 = *(float *)(g_unk_010afbcc + 0x44);
  for (; tmp_i46 = headTrails, tmp_pi40 != (int *)0x0; tmp_pi40 = (int *)*tmp_pi40) {
    while (tmp_f3 = (float)(g_unk_010906e0 - tmp_pi40[0x10]) / (float)(tmp_pi40[0x11] - tmp_pi40[0x10]),
          1.0 <= tmp_f3) {
      tmp_pi40[6] = 0;
      tmp_pi40[0x1d] = tmp_pi40[0x1b];
      tmp_f3 = (float)tmp_pi40[0x13];
      if (tmp_f3 <= 1.0) {
        tmp_f4 = 0.0;
        if (0.0 <= tmp_f3) {
          tmp_f4 = tmp_f3;
        }
        tmp_pi40[0x1c] = (int)tmp_f4;
      }
      else {
        tmp_pi40[0x1c] = 0x3f800000;
      }
      tmp_pi40[0x1e] = tmp_pi40[0x17];
      tmp_pi40[0x1f] = tmp_pi40[0x18];
      tmp_pi40[0x20] = tmp_pi40[0x19];
      tmp_pi40 = (int *)*tmp_pi40;
      tmp_i46 = headTrails;
      if (tmp_pi40 == (int *)0x0) goto joined_r0x000c97fb;
    }
    tmp_pi40[0x1d] =
         (int)(((float)tmp_pi40[0x1b] - (float)tmp_pi40[0x1a]) * tmp_f3 + (float)tmp_pi40[0x1a]);
    tmp_f4 = ((float)tmp_pi40[0x13] - (float)tmp_pi40[0x12]) * tmp_f3 + (float)tmp_pi40[0x12];
    if (tmp_f4 <= 1.0) {
      tmp_f5 = 0.0;
      if (0.0 <= tmp_f4) {
        tmp_f5 = tmp_f4;
      }
      tmp_pi40[0x1c] = (int)tmp_f5;
    }
    else {
      tmp_pi40[0x1c] = 0x3f800000;
    }
    tmp_pi40[0x1e] =
         (int)(((float)tmp_pi40[0x17] - (float)tmp_pi40[0x14]) * tmp_f3 + (float)tmp_pi40[0x14]);
    tmp_pi40[0x1f] =
         (int)(((float)tmp_pi40[0x18] - (float)tmp_pi40[0x15]) * tmp_f3 + (float)tmp_pi40[0x15]);
    tmp_pi40[0x20] =
         (int)(((float)tmp_pi40[0x19] - (float)tmp_pi40[0x16]) * tmp_f3 + (float)tmp_pi40[0x16]);
  }
joined_r0x000c97fb:
  do {
    do {
      while( true ) {
        tmp_i39 = tmp_i46;
        if (tmp_i39 == 0) {
          return;
        }
        tmp_i46 = *(int *)(tmp_i39 + 0xc);
        tmp_i48 = *(int *)(tmp_i39 + 0x18);
        if (tmp_i48 != 0) break;
        CG_FreeTrailJunc(tmp_i39);
      }
      if ((*(byte *)(tmp_i39 + 0x2c) & 0x10) != 0) {
        tmp_i48 = CG_PB_FindFreePolyBuffer(GHIDRA_FIELD(cgs, 68860, 4),4,6);
        if (tmp_i48 == 0) {
          tmp_i48 = *(int *)(tmp_i39 + 0x18);
        }
        else {
          tmp_i47 = *(int *)(tmp_i48 + 0x701c);
          tmp_i51 = tmp_i47 * 0x10;
          pfVar45 = (float *)(tmp_i48 + tmp_i51);
          *pfVar45 = *(float *)(tmp_i39 + 0x34);
          pfVar49 = (float *)(tmp_i48 + 4 + tmp_i51);
          pfVar2 = (float *)(tmp_i48 + 8 + tmp_i51);
          *pfVar49 = *(float *)(tmp_i39 + 0x38);
          *pfVar2 = *(float *)(tmp_i39 + 0x3c);
          tmp_f3 = vup;
          *pfVar45 = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * vup + *pfVar45;
          tmp_f4 = g_unk_00c21a44;
          *pfVar49 = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * g_unk_00c21a44 +
                     *pfVar49;
          tmp_f5 = g_unk_00c21a48;
          *pfVar2 = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * g_unk_00c21a48 +
                    *pfVar2;
          tmp_f6 = vright;
          *pfVar45 = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * vright + *pfVar45;
          tmp_f7 = g_unk_00c21a50;
          *pfVar49 = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * g_unk_00c21a50 +
                     *pfVar49;
          tmp_f8 = g_unk_00c21a54;
          tmp_i43 = tmp_i48 + tmp_i47 * 8;
          *pfVar2 = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * g_unk_00c21a54 +
                    *pfVar2;
          tmp_i51 = tmp_i47 + 1;
          *(uint32_t *)(tmp_i43 + 0x4010) = 0;
          *(uint32_t *)(tmp_i48 + 0x4014 + tmp_i47 * 8) = 0;
          pfVar49 = (float *)(tmp_i48 + 4 + tmp_i51 * 0x10);
          pfVar45[4] = *(float *)(tmp_i39 + 0x34);
          pfVar2 = (float *)(tmp_i48 + 8 + tmp_i51 * 0x10);
          *pfVar49 = *(float *)(tmp_i39 + 0x38);
          *pfVar2 = *(float *)(tmp_i39 + 0x3c);
          pfVar45[4] = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * tmp_f3 +
                       pfVar45[4];
          *pfVar49 = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * tmp_f4 + *pfVar49;
          *pfVar2 = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * tmp_f5 + *pfVar2;
          pfVar45[4] = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f6 + pfVar45[4];
          *pfVar49 = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f7 + *pfVar49;
          *pfVar2 = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f8 + *pfVar2;
          *(uint32_t *)(tmp_i43 + 0x4018) = 0;
          *(uint32_t *)(tmp_i48 + 0x4014 + tmp_i51 * 8) = 0x3f800000;
          pfVar45[8] = *(float *)(tmp_i39 + 0x34);
          tmp_i44 = tmp_i47 + 2;
          pfVar49 = (float *)(tmp_i48 + 4 + tmp_i44 * 0x10);
          *pfVar49 = *(float *)(tmp_i39 + 0x38);
          pfVar2 = (float *)(tmp_i48 + 8 + tmp_i44 * 0x10);
          *pfVar2 = *(float *)(tmp_i39 + 0x3c);
          pfVar45[8] = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f3 + pfVar45[8];
          *pfVar49 = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f4 + *pfVar49;
          *pfVar2 = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f5 + *pfVar2;
          pfVar45[8] = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f6 + pfVar45[8];
          *pfVar49 = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f7 + *pfVar49;
          *pfVar2 = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f8 + *pfVar2;
          *(uint32_t *)(tmp_i43 + 0x4020) = 0x3f800000;
          *(uint32_t *)(tmp_i48 + 0x4014 + tmp_i44 * 8) = 0x3f800000;
          tmp_i52 = tmp_i47 + 3;
          pfVar45[0xc] = *(float *)(tmp_i39 + 0x34);
          pfVar49 = (float *)(tmp_i48 + 4 + tmp_i52 * 0x10);
          *pfVar49 = *(float *)(tmp_i39 + 0x38);
          pfVar2 = (float *)(tmp_i48 + 8 + tmp_i52 * 0x10);
          *pfVar2 = *(float *)(tmp_i39 + 0x3c);
          pfVar45[0xc] = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f3 +
                         pfVar45[0xc];
          *pfVar49 = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f4 + *pfVar49;
          *pfVar2 = (*(float *)(tmp_i39 + 0x74) + *(float *)(tmp_i39 + 0x74)) * tmp_f5 + *pfVar2;
          pfVar45[0xc] = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * tmp_f6 +
                         pfVar45[0xc];
          *pfVar49 = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * tmp_f7 + *pfVar49;
          *pfVar2 = (-*(float *)(tmp_i39 + 0x74) + -*(float *)(tmp_i39 + 0x74)) * tmp_f8 + *pfVar2;
          *(uint32_t *)(tmp_i43 + 0x4028) = 0x3f800000;
          *(uint32_t *)(tmp_i48 + 0x4014 + tmp_i52 * 8) = 0;
          tmp_i43 = tmp_i48 + tmp_i47 * 4;
          *(uint8_t *)(tmp_i43 + 0x6018) = 0xff;
          *(uint8_t *)(tmp_i48 + 0x6019 + tmp_i47 * 4) = 0xff;
          *(uint8_t *)(tmp_i48 + 0x601a + tmp_i47 * 4) = 0xff;
          *(char *)(tmp_i48 + 0x601b + tmp_i47 * 4) =
               (char)(short)ROUND(*(float *)(tmp_i39 + 0x70) * 255.0);
          *(uint8_t *)(tmp_i43 + 0x601c) = 0xff;
          *(uint8_t *)(tmp_i48 + 0x6019 + tmp_i51 * 4) = 0xff;
          *(uint8_t *)(tmp_i48 + 0x601a + tmp_i51 * 4) = 0xff;
          *(char *)(tmp_i48 + 0x601b + tmp_i51 * 4) =
               (char)(short)ROUND(*(float *)(tmp_i39 + 0x70) * 255.0);
          *(uint8_t *)(tmp_i43 + 0x6020) = 0xff;
          *(uint8_t *)(tmp_i48 + 0x6019 + tmp_i44 * 4) = 0xff;
          *(uint8_t *)(tmp_i48 + 0x601a + tmp_i44 * 4) = 0xff;
          *(char *)(tmp_i48 + 0x601b + tmp_i44 * 4) =
               (char)(short)ROUND(*(float *)(tmp_i39 + 0x70) * 255.0);
          *(uint8_t *)(tmp_i43 + 0x6024) = 0xff;
          *(uint8_t *)(tmp_i48 + 0x6019 + tmp_i52 * 4) = 0xff;
          *(uint8_t *)(tmp_i48 + 0x601a + tmp_i52 * 4) = 0xff;
          *(char *)(tmp_i48 + 0x601b + tmp_i52 * 4) =
               (char)(short)ROUND(*(float *)(tmp_i39 + 0x70) * 255.0);
          tmp_i1 = *(int *)(tmp_i48 + 0xd038);
          tmp_i43 = tmp_i48 + tmp_i1 * 4;
          *(int *)(tmp_i43 + 0x7020) = tmp_i47;
          *(int *)(tmp_i43 + 0x7024) = tmp_i51;
          *(int *)(tmp_i43 + 0x7028) = tmp_i44;
          *(int *)(tmp_i43 + 0x702c) = tmp_i44;
          *(int *)(tmp_i43 + 0x7030) = tmp_i52;
          *(int *)(tmp_i43 + 0x7034) = tmp_i47;
          *(int *)(tmp_i48 + 0x701c) = tmp_i47 + 4;
          *(int *)(tmp_i48 + 0xd038) = tmp_i1 + 6;
          tmp_i48 = *(int *)(tmp_i39 + 0x18);
        }
      }
      local_54 = 1;
      local_64 = 0.0;
      tmp_i51 = *(int *)(tmp_i39 + 8);
      tmp_i43 = tmp_i39;
      if (tmp_i48 != 0) goto LAB_000c9e5b;
      while (tmp_i51 != 0) {
        if (*(int *)(tmp_i51 + 0x18) == 0) {
          CG_KillTrail(tmp_i43);
          tmp_i51 = *(int *)(tmp_i43 + 8);
          if (tmp_i51 != 0) goto LAB_000c9e2b;
          break;
        }
        while( true ) {
          if (*(int *)(tmp_i51 + 0x1c) != 0) {
            *(uint32_t *)(tmp_i43 + 8) = 0;
            goto LAB_000c9889;
          }
LAB_000c9e2b:
          tmp_l53 = (long double)VectorDistance(tmp_i51 + 0x34,tmp_i43 + 0x34);
          tmp_i43 = *(int *)(tmp_i43 + 8);
          local_64 = (float)(tmp_l53 + (long double)local_64);
          if (tmp_i43 == 0) goto LAB_000c9889;
          local_54 = local_54 + 1;
          tmp_i51 = *(int *)(tmp_i43 + 8);
          if (*(int *)(tmp_i43 + 0x18) == 0) break;
LAB_000c9e5b:
          if (tmp_i51 == 0) goto LAB_000c9889;
        }
      }
LAB_000c9889:
    } while (local_54 == 1);
    if (*(int *)(tmp_i39 + 0x28) == 0) {
      local_88 = 0.05;
      tmp_i48 = *(int *)(tmp_i39 + 8);
    }
    else {
      if (*(int *)(tmp_i39 + 0x28) == 1) {
        local_88 = *(float *)(tmp_i39 + 0x30);
      }
      else {
        local_88 = 0.0;
      }
      tmp_i48 = *(int *)(tmp_i39 + 8);
    }
    if (tmp_i48 == 0) {
      tmp_u41 = *(uint *)(tmp_i39 + 0x2c);
      if ((tmp_u41 & 8) == 0) {
        local_80 = 0;
        if ((tmp_u41 & 0x20) == 0) goto LAB_000ca745;
      }
      else if ((tmp_u41 & 0x20) == 0) {
        local_80 = 0;
LAB_000ca6f1:
        local_4c = &outVerts;
        tmp_u54 = 3;
        goto LAB_000ca702;
      }
    }
    else {
      local_80 = 0;
      pfVar45 = (float *)&verts;
      tmp_i43 = tmp_i39 + 0x34;
      tmp_i47 = tmp_i39;
      pfVar49 = pfVar45;
      tmp_i51 = local_80;
      do {
        local_80 = tmp_i51;
        tmp_i1 = tmp_i48 + 0x34;
        GetPerpendicularViewVector(g_unk_010afbcc + 0x18,tmp_i43,tmp_i1,&local_34);
        if (((*(byte *)(tmp_i47 + 0x2c) & 6) == 0) &&
           ((4.0 < *(float *)(tmp_i47 + 0x6c) || (4.0 < *(float *)(tmp_i48 + 0x6c))))) {
          ProjectPointOntoVector(g_unk_010afbcc + 0x18,tmp_i43,tmp_i1,local_28);
          tmp_l53 = (long double)Distance(local_28,g_unk_010afbcc + 0x18);
          if (tmp_l53 < (long double)256.0) {
            if (tmp_l53 < (long double)64.0) {
              tmp_f3 = 0.0;
            }
            else {
              tmp_f3 = (float)((tmp_l53 - (long double)64.0) * (long double)0.00390625);
            }
            if (tmp_f3 < *(float *)(tmp_i47 + 0x70)) {
              *(float *)(tmp_i47 + 0x70) = tmp_f3;
            }
            if (tmp_f3 < *(float *)(tmp_i48 + 0x70)) {
              *(float *)(tmp_i48 + 0x70) = tmp_f3;
            }
          }
        }
        tmp_f4 = *(float *)(tmp_i47 + 0x74) * 0.5;
        tmp_f5 = local_34 * tmp_f4 + *(float *)(tmp_i47 + 0x34);
        tmp_f3 = local_30 * tmp_f4 + *(float *)(tmp_i47 + 0x38);
        tmp_f4 = local_2c * tmp_f4 + *(float *)(tmp_i47 + 0x3c);
        *pfVar49 = tmp_f5;
        pfVar49[1] = tmp_f3;
        pfVar49[2] = tmp_f4;
        pfVar49[4] = 1.0;
        pfVar49[3] = local_88;
        *(char *)(pfVar49 + 5) = (char)(short)ROUND(*(float *)(tmp_i47 + 0x78) * 255.0);
        *(char *)((int)pfVar49 + 0x15) = (char)(short)ROUND(*(float *)(tmp_i47 + 0x7c) * 255.0);
        *(char *)((int)pfVar49 + 0x16) = (char)(short)ROUND(*(float *)(tmp_i47 + 0x80) * 255.0);
        *(char *)((int)pfVar49 + 0x17) = (char)(short)ROUND(*(float *)(tmp_i47 + 0x70) * 255.0);
        if (tmp_i39 == tmp_i47) {
          if ((*(byte *)(tmp_i39 + 0x2c) & 1) != 0) {
            *(uint8_t *)((int)pfVar49 + 0x17) = 0;
          }
        }
        else {
          tmp_f8 = (pfVar49[-6] + tmp_f5) * 0.5;
          *pfVar49 = tmp_f8;
          tmp_f6 = (pfVar49[-5] + tmp_f3) * 0.5;
          pfVar49[1] = tmp_f6;
          tmp_f7 = (pfVar49[-4] + tmp_f4) * 0.5;
          pfVar49[2] = tmp_f7;
          pfVar49[-6] = tmp_f8;
          pfVar49[-5] = tmp_f6;
          pfVar49[-4] = tmp_f7;
        }
        tmp_f6 = -*(float *)(tmp_i47 + 0x74);
        pfVar49[10] = 0.0;
        tmp_f5 = local_34 * tmp_f6 + tmp_f5;
        pfVar49[6] = tmp_f5;
        tmp_f3 = local_30 * tmp_f6 + tmp_f3;
        pfVar49[7] = tmp_f3;
        tmp_f4 = tmp_f6 * local_2c + tmp_f4;
        pfVar49[8] = tmp_f4;
        pfVar49[9] = local_88;
        *(char *)(pfVar49 + 0xb) = (char)(short)ROUND(*(float *)(tmp_i47 + 0x78) * 255.0);
        *(char *)((int)pfVar49 + 0x2d) = (char)(short)ROUND(*(float *)(tmp_i47 + 0x7c) * 255.0);
        *(char *)((int)pfVar49 + 0x2e) = (char)(short)ROUND(*(float *)(tmp_i47 + 0x80) * 255.0);
        *(char *)((int)pfVar49 + 0x2f) = (char)(short)ROUND(*(float *)(tmp_i47 + 0x70) * 255.0);
        if (tmp_i39 == tmp_i47) {
          if ((*(byte *)(tmp_i39 + 0x2c) & 1) != 0) {
            *(uint8_t *)((int)pfVar49 + 0x2f) = 0;
          }
        }
        else {
          tmp_f5 = (tmp_f5 + pfVar49[-0xc]) * 0.5;
          pfVar49[6] = tmp_f5;
          tmp_f3 = (tmp_f3 + pfVar49[-0xb]) * 0.5;
          pfVar49[7] = tmp_f3;
          tmp_f4 = (tmp_f4 + pfVar49[-10]) * 0.5;
          pfVar49[8] = tmp_f4;
          pfVar49[-0xc] = tmp_f5;
          pfVar49[-0xb] = tmp_f3;
          pfVar49[-10] = tmp_f4;
        }
        if (*(int *)(tmp_i39 + 0x28) == 1) {
          local_88 = *(float *)(tmp_i48 + 0x30);
        }
        else {
          tmp_l53 = (long double)VectorDistance(tmp_i43,tmp_i1);
          tmp_l53 = tmp_l53 / (long double)local_64 + (long double)local_88;
          local_88 = (float)tmp_l53;
          if ((long double)1 < tmp_l53) {
            local_88 = 1.0;
          }
        }
        tmp_f3 = *(float *)(tmp_i48 + 0x74) * -0.5;
        tmp_f6 = local_34 * tmp_f3 + *(float *)(tmp_i48 + 0x34);
        tmp_f5 = local_30 * tmp_f3 + *(float *)(tmp_i48 + 0x38);
        tmp_f4 = tmp_f3 * local_2c + *(float *)(tmp_i48 + 0x3c);
        pfVar49[0xc] = tmp_f6;
        pfVar49[0xd] = tmp_f5;
        pfVar49[0xe] = tmp_f4;
        pfVar49[0x10] = 0.0;
        pfVar49[0xf] = local_88;
        *(char *)(pfVar49 + 0x11) = (char)(short)ROUND(*(float *)(tmp_i48 + 0x78) * 255.0);
        *(char *)((int)pfVar49 + 0x45) = (char)(short)ROUND(*(float *)(tmp_i48 + 0x7c) * 255.0);
        *(char *)((int)pfVar49 + 0x46) = (char)(short)ROUND(*(float *)(tmp_i48 + 0x80) * 255.0);
        *(char *)((int)pfVar49 + 0x47) = (char)(short)ROUND(*(float *)(tmp_i48 + 0x70) * 255.0);
        tmp_f3 = *(float *)(tmp_i48 + 0x74);
        pfVar49[0x16] = 1.0;
        pfVar49[0x12] = local_34 * tmp_f3 + tmp_f6;
        pfVar49[0x13] = local_30 * tmp_f3 + tmp_f5;
        pfVar49[0x14] = tmp_f3 * local_2c + tmp_f4;
        pfVar49[0x15] = local_88;
        *(char *)(pfVar49 + 0x17) = (char)(short)ROUND(*(float *)(tmp_i48 + 0x78) * 255.0);
        *(char *)((int)pfVar49 + 0x5d) = (char)(short)ROUND(*(float *)(tmp_i48 + 0x7c) * 255.0);
        tmp_i51 = local_80 + 4;
        *(char *)((int)pfVar49 + 0x5e) = (char)(short)ROUND(*(float *)(tmp_i48 + 0x80) * 255.0);
        *(char *)((int)pfVar49 + 0x5f) = (char)(short)ROUND(*(float *)(tmp_i48 + 0x70) * 255.0);
        if (tmp_i51 == 0x800) {
          if ((*(uint *)(tmp_i39 + 0x2c) & 8) != 0) goto LAB_000c9ec2;
          tmp_i48 = 0x200;
          local_80 = tmp_i51;
          if ((*(uint *)(tmp_i39 + 0x2c) & 0x20) == 0) goto LAB_000ca745;
          goto LAB_000ca264;
        }
        tmp_pi40 = (int *)(tmp_i48 + 8);
        pfVar49 = pfVar49 + 0x18;
        tmp_i43 = tmp_i1;
        tmp_i47 = tmp_i48;
        tmp_i48 = *tmp_pi40;
      } while (*tmp_pi40 != 0);
      tmp_u41 = *(uint *)(tmp_i39 + 0x2c);
      if ((tmp_u41 & 8) != 0) {
LAB_000c9ec2:
        tmp_i48 = 0;
        local_84 = 0;
        do {
          tmp_f3 = *pfVar45;
          tmp_f4 = pfVar45[6];
          tmp_f5 = pfVar45[1];
          tmp_f6 = pfVar45[7];
          tmp_f7 = pfVar45[2];
          tmp_f8 = pfVar45[8];
          tmp_f9 = pfVar45[3];
          tmp_f10 = pfVar45[9];
          tmp_f11 = pfVar45[4];
          tmp_f12 = pfVar45[10];
          tmp_f13 = pfVar45[0xc];
          tmp_f14 = pfVar45[0xd];
          tmp_f15 = pfVar45[0xe];
          tmp_f16 = pfVar45[0xf];
          tmp_f17 = pfVar45[0x10];
          tmp_f18 = pfVar45[0x12];
          tmp_f19 = pfVar45[0x13];
          tmp_f20 = pfVar45[0x14];
          tmp_f21 = pfVar45[0x15];
          tmp_f22 = pfVar45[0x16];
          tmp_b23 = *(byte *)(pfVar45 + 0x17);
          tmp_b24 = *(byte *)(pfVar45 + 5);
          tmp_b25 = *(byte *)(pfVar45 + 0xb);
          tmp_b26 = *(byte *)(pfVar45 + 0x11);
          tmp_b27 = *(byte *)((int)pfVar45 + 0x45);
          tmp_b28 = *(byte *)((int)pfVar45 + 0x2d);
          tmp_b29 = *(byte *)((int)pfVar45 + 0x15);
          tmp_b30 = *(byte *)((int)pfVar45 + 0x5d);
          tmp_b31 = *(byte *)((int)pfVar45 + 0x46);
          tmp_b32 = *(byte *)((int)pfVar45 + 0x2e);
          tmp_b33 = *(byte *)((int)pfVar45 + 0x16);
          tmp_b34 = *(byte *)((int)pfVar45 + 0x5e);
          tmp_b35 = *(byte *)((int)pfVar45 + 0x2f);
          tmp_b36 = *(byte *)((int)pfVar45 + 0x17);
          tmp_b37 = *(byte *)((int)pfVar45 + 0x47);
          tmp_b38 = *(byte *)((int)pfVar45 + 0x5f);
          tmp_pu42 = &outVerts + tmp_i48 * 6;
          tmp_i51 = tmp_i48;
          pfVar49 = pfVar45;
LAB_000ca0ba:
          tmp_i43 = tmp_i51;
          tmp_u41 = 0;
          do {
            *(uint32_t *)((int)tmp_pu42 + tmp_u41) = *(uint32_t *)((int)pfVar49 + tmp_u41);
            tmp_u41 = tmp_u41 + 4;
          } while (tmp_u41 < 0x18);
          local_7c = (uint8_t)
                     (short)ROUND(((double)tmp_b26 + (double)tmp_b25 + (double)tmp_b24 + (double)tmp_b23
                                  ) * 0.25);
          tmp_pu42[6] = (tmp_f3 + tmp_f4 + tmp_f13 + tmp_f18) * 0.25;
          tmp_pu42[7] = (tmp_f5 + tmp_f6 + tmp_f14 + tmp_f19) * 0.25;
          tmp_pu42[8] = (tmp_f7 + tmp_f8 + tmp_f15 + tmp_f20) * 0.25;
          *(uint8_t *)(tmp_pu42 + 0xb) = local_7c;
          local_74 = (uint8_t)
                     (short)ROUND(((double)tmp_b30 + (double)tmp_b29 + (double)tmp_b28 + (double)tmp_b27
                                  ) * 0.25);
          tmp_pu42[9] = (tmp_f9 + tmp_f10 + tmp_f16 + tmp_f21) * 0.25;
          tmp_pu42[10] = (tmp_f11 + tmp_f12 + tmp_f17 + tmp_f22) * 0.25;
          *(char *)((int)tmp_pu42 + 0x2f) =
               (char)(short)ROUND(((double)tmp_b38 + (double)tmp_b37 + (double)tmp_b36 + (double)tmp_b35
                                  ) * 0.25);
          *(uint8_t *)((int)tmp_pu42 + 0x2d) = local_74;
          local_6c = (uint8_t)
                     (short)ROUND(((double)tmp_b34 + (double)tmp_b33 + (double)tmp_b32 + (double)tmp_b31
                                  ) * 0.25);
          *(uint8_t *)((int)tmp_pu42 + 0x2e) = local_6c;
          if (tmp_i43 != tmp_i48 + 9) goto code_r0x000ca117;
          tmp_u41 = 0;
          do {
            *(uint32_t *)((int)&outVerts + tmp_u41 + (tmp_i43 + 2) * 0x18) =
                 *(uint32_t *)((int)pfVar45 + tmp_u41);
            tmp_u41 = tmp_u41 + 4;
          } while (tmp_u41 < 0x18);
LAB_000ca150:
          tmp_i48 = tmp_i43 + 3;
          local_84 = local_84 + 4;
          pfVar45 = pfVar45 + 0x18;
          if (local_84 == local_80 + 4) {
            tmp_u41 = *(uint *)(tmp_i39 + 0x2c);
            local_80 = tmp_i48 / 3;
            if ((tmp_u41 & 0x20) == 0) goto LAB_000ca6f1;
            if (0 < local_80) {
              tmp_pu42 = &outVerts;
              do {
                tmp_pu50 = tmp_pu42 + 0x12;
                trap_R_AddPolyToScene(*(uint32_t *)(tmp_i39 + 0x24),3,tmp_pu42);
                tmp_pu42 = tmp_pu50;
              } while (tmp_pu50 != &outVerts + local_80 * 0x12);
              goto LAB_000ca1bf;
            }
            goto LAB_000ca1c6;
          }
        } while( true );
      }
      local_80 = tmp_i51;
      if ((tmp_u41 & 0x20) == 0) {
LAB_000ca745:
        local_4c = &verts;
        tmp_u54 = 4;
        local_80 = local_80 >> 2;
LAB_000ca702:
        trap_R_AddPolysToScene(*(uint32_t *)(tmp_i39 + 0x24),tmp_u54,local_4c,local_80);
        tmp_u41 = *(uint *)(tmp_i39 + 0x2c);
      }
      else {
        tmp_i48 = tmp_i51 >> 2;
        if (tmp_i48 != 0) {
LAB_000ca264:
          tmp_i51 = 0;
          do {
            tmp_i51 = tmp_i51 + 1;
            trap_R_AddPolyToScene(*(uint32_t *)(tmp_i39 + 0x24),4,pfVar45);
            pfVar45 = pfVar45 + 0x18;
          } while (tmp_i51 != tmp_i48);
LAB_000ca1bf:
          tmp_u41 = *(uint *)(tmp_i39 + 0x2c);
        }
      }
    }
LAB_000ca1c6:
    if ((tmp_u41 & 2) != 0) {
      CG_AddTrailToScene(tmp_i39,1,local_54);
    }
  } while( true );
code_r0x000ca117:
  tmp_u41 = 0;
  do {
    *(uint32_t *)((int)tmp_pu42 + tmp_u41 + 0x30) = *(uint32_t *)((int)pfVar49 + tmp_u41 + 0x18);
    tmp_u41 = tmp_u41 + 4;
  } while (tmp_u41 < 0x18);
  pfVar49 = pfVar49 + 6;
  tmp_pu42 = tmp_pu42 + 0x12;
  tmp_i51 = tmp_i43 + 3;
  if (tmp_i43 + 3 == tmp_i48 + 0xc) goto LAB_000ca150;
  goto LAB_000ca0ba;
}

void CG_AdjustZoomVal(float param_1,int param_2)
{
  g_unk_01091a74 = param_1 + g_unk_01091a74;
  if (*(float *)(zoomTable + param_2 * 8) < g_unk_01091a74) {
    g_unk_01091a74 = *(float *)(zoomTable + param_2 * 8);
  }
  if (g_unk_01091a74 < *(float *)(zoomTable + param_2 * 8 + 4)) {
    g_unk_01091a74 = *(float *)(zoomTable + param_2 * 8 + 4);
  }
  return;
}

void CG_AddWeaponWithPowerups_isra_1(int param_1)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  uint tmp_u3;
  uint32_t local_f8 [59];
  
  tmp_u2 = 0;
  do {
    tmp_u3 = tmp_u2;
    tmp_u1 = *(uint32_t *)(param_1 + tmp_u3);
    *(uint32_t *)((int)local_f8 + tmp_u3 + 4) = *(uint32_t *)(param_1 + 4 + tmp_u3);
    *(uint32_t *)((int)local_f8 + tmp_u3) = tmp_u1;
    tmp_u2 = tmp_u3 + 8;
  } while (tmp_u2 < 0xe8);
  *(uint32_t *)((int)local_f8 + tmp_u3 + 8) = *(uint32_t *)(param_1 + tmp_u2);
  trap_R_AddRefEntityToScene(param_1);
  tmp_u2 = 0;
  do {
    tmp_u3 = tmp_u2;
    tmp_u1 = *(uint32_t *)((int)local_f8 + tmp_u3);
    *(uint32_t *)(param_1 + 4 + tmp_u3) = *(uint32_t *)((int)local_f8 + tmp_u3 + 4);
    *(uint32_t *)(param_1 + tmp_u3) = tmp_u1;
    tmp_u2 = tmp_u3 + 8;
  } while (tmp_u2 < 0xe8);
  *(uint32_t *)(param_1 + tmp_u2) = *(uint32_t *)((int)local_f8 + tmp_u3 + 8);
  return;
}

void CG_AddSparks_part_12
          (float *param_1,float *param_2,int param_3,int param_4,int param_5,float param_6)

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
  int tmp_i10;
  uint32_t tmp_u11;
  int tmp_i12;
  uint tmp_u13;
  uint tmp_u14;
  int tmp_i15;
  uint local_6c;
  
  if (0 < param_5) {
    tmp_f6 = (float)param_3;
    tmp_i15 = 0;
    do {
      tmp_i12 = CG_AllocLocalEntity();
      tmp_f1 = *param_2;
      tmp_u13 = rand();
      tmp_f2 = param_2[1];
      local_6c = rand();
      tmp_f3 = param_2[2];
      tmp_u14 = rand();
      tmp_f7 = (float)(tmp_u13 & 0x7fff) / 32767.0 - 0.5;
      local_6c = local_6c & 0x7fff;
      tmp_f4 = (float)local_6c;
      local_6c = tmp_u14 & 0x7fff;
      tmp_f9 = tmp_f4 / 32767.0 - 0.5;
      tmp_f8 = (float)local_6c / 32767.0 - 0.5;
      *(uint32_t *)(tmp_i12 + 8) = 9;
      tmp_i10 = g_unk_010906e0;
      *(int *)(tmp_i12 + 0x10) = g_unk_010906e0;
      tmp_u13 = rand();
      *(int *)(tmp_i12 + 0x14) =
           (tmp_i10 + param_4) -
           (int)ROUND(((float)(tmp_u13 & 0x7fff) / 32767.0) * 0.5 * (float)param_4);
      *(int *)(tmp_i12 + 0x184) = g_unk_010906e0;
      *(float *)(tmp_i12 + 0x100) = *param_1;
      *(float *)(tmp_i12 + 0x104) = param_1[1];
      *(float *)(tmp_i12 + 0x108) = param_1[2];
      AxisCopy(axisDefault,tmp_i12 + 0xb4);
      *(uint32_t *)(tmp_i12 + 0x20) = 7;
      tmp_f4 = *param_1;
      *(float *)(tmp_i12 + 0x2c) = tmp_f4;
      *(float *)(tmp_i12 + 0x30) = param_1[1];
      *(float *)(tmp_i12 + 0x34) = param_1[2];
      tmp_f5 = *param_2;
      tmp_u13 = rand();
      *(float *)(tmp_i12 + 0x2c) = tmp_f4 + (((float)(tmp_u13 & 0x7fff) / 32767.0) * 4.0 + 2.0) * tmp_f5
      ;
      tmp_f4 = *(float *)(tmp_i12 + 0x30);
      tmp_f5 = param_2[1];
      tmp_u13 = rand();
      *(float *)(tmp_i12 + 0x30) = (((float)(tmp_u13 & 0x7fff) / 32767.0) * 4.0 + 2.0) * tmp_f5 + tmp_f4
      ;
      tmp_f4 = *(float *)(tmp_i12 + 0x34);
      tmp_f5 = param_2[2];
      tmp_u13 = rand();
      tmp_i15 = tmp_i15 + 1;
      *(float *)(tmp_i12 + 0x34) = (((float)(tmp_u13 & 0x7fff) / 32767.0) * 4.0 + 2.0) * tmp_f5 + tmp_f4
      ;
      *(float *)(tmp_i12 + 0x38) = ((tmp_f7 + tmp_f7) * param_6 + tmp_f1) * tmp_f6;
      *(float *)(tmp_i12 + 0x3c) = ((tmp_f9 + tmp_f9) * param_6 + tmp_f2) * tmp_f6;
      *(float *)(tmp_i12 + 0x40) = ((tmp_f8 + tmp_f8) * param_6 + tmp_f3) * tmp_f6;
      *(int *)(tmp_i12 + 0x24) = g_unk_010906e0;
      tmp_u11 = GHIDRA_FIELD(cgs, 68840, 4);
      *(uint32_t *)(tmp_i12 + 0x68) = 0x3f666666;
      *(uint32_t *)(tmp_i12 + 0x148) = tmp_u11;
    } while (tmp_i15 != param_5);
  }
  return;
}

void CG_AddBulletParticles_part_13(float *param_1,float *param_2,int param_3,int param_4,float param_5)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint tmp_u5;
  int tmp_i6;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  if (param_4 != 0) {
    tmp_f3 = (float)param_3;
    do {
      tmp_f1 = *param_2;
      tmp_u5 = rand();
      tmp_f2 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
      local_34 = (tmp_f2 + tmp_f2) * param_5 + tmp_f1;
      tmp_f1 = param_2[1];
      tmp_u5 = rand();
      tmp_f2 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
      local_30 = (tmp_f2 + tmp_f2) * param_5 + tmp_f1;
      tmp_f1 = param_2[2];
      tmp_u5 = rand();
      local_34 = local_34 * tmp_f3;
      local_30 = local_30 * tmp_f3;
      tmp_f2 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
      local_2c = ((tmp_f2 + tmp_f2) * param_5 + tmp_f1) * tmp_f3;
      tmp_f1 = *param_1;
      local_24 = param_1[1];
      local_20 = param_1[2];
      tmp_f2 = *param_2;
      local_28 = tmp_f1;
      tmp_u5 = rand();
      tmp_f4 = local_24;
      local_28 = tmp_f1 + (((float)(tmp_u5 & 0x7fff) / 32767.0) * 4.0 + 2.0) * tmp_f2;
      tmp_f1 = param_2[1];
      tmp_u5 = rand();
      tmp_f2 = local_20;
      local_24 = (((float)(tmp_u5 & 0x7fff) / 32767.0) * 4.0 + 2.0) * tmp_f1 + tmp_f4;
      tmp_f1 = param_2[2];
      tmp_u5 = rand();
      local_20 = (((float)(tmp_u5 & 0x7fff) / 32767.0) * 4.0 + 2.0) * tmp_f1 + tmp_f2;
      tmp_i6 = rand();
      CG_ParticleBulletDebris(&local_28,&local_34,tmp_i6 % 300 + 300);
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  return;
}

void CG_AddDirtBulletParticles_part_14
          (uint32_t *param_1,float *param_2,int param_3,int param_4,int param_5,float param_6,
          uint32_t param_7,uint32_t param_8,uint32_t param_9,uint32_t param_10)

{
  float tmp_f1;
  float tmp_f2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  float local_34;
  float local_30;
  float local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  local_34 = 0.0;
  local_30 = 0.0;
  local_28 = *param_1;
  local_24 = param_1[1];
  local_20 = param_1[2];
  local_2c = (float)param_3;
  CG_ParticleDirtBulletDebris_Core(&local_28,&local_34,param_4,param_7,param_8,param_9,param_10);
  if (0 < param_5) {
    tmp_i5 = 0;
    do {
      tmp_f1 = *param_2;
      tmp_i5 = tmp_i5 + 1;
      tmp_u3 = rand();
      tmp_f2 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
      local_34 = (tmp_f2 + tmp_f2) * tmp_f1 * (float)param_3 * param_6;
      tmp_f1 = param_2[1];
      tmp_u3 = rand();
      tmp_f2 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
      local_30 = (tmp_f2 + tmp_f2) * tmp_f1 * (float)param_3 * param_6;
      tmp_f1 = param_2[2];
      tmp_u3 = rand();
      local_2c = ((float)(tmp_u3 & 0x7fff) / 32767.0) * tmp_f1 * (float)param_3;
      tmp_i4 = rand();
      CG_ParticleDirtBulletDebris_Core
                (&local_28,&local_34,tmp_i4 % (param_4 >> 1) + param_4,param_7,param_8,param_9,
                 param_10);
    } while (tmp_i5 != param_5);
  }
  return;
}

void CG_AddPlayerWeapon(float *param_1,int param_2,int *param_3)
{
  float tmp_f1;
  byte tmp_b2;
  bool tmp_b3;
  uint tmp_u4;
  uint tmp_u5;
  int tmp_i6;
  char *tmp_pc7;
  bool tmp_b8;
  bool tmp_b9;
  int tmp_i10;
  int tmp_i11;
  int tmp_i12;
  int *tmp_pi13;
  float *pfVar14;
  float *pfVar15;
  bool tmp_b16;
  bool tmp_b17;
  byte tmp_b18;
  long double tmp_l19;
  float tmp_f20;
  uint32_t tmp_u21;
  uint32_t tmp_u22;
  int local_424;
  uint local_420;
  int local_410;
  int *local_40c;
  int local_408;
  int *local_400;
  float *local_3f4;
  float *local_3f0;
  float *local_3e8;
  uint local_3e4;
  float local_3d8;
  float local_3d4;
  float local_3d0;
  float local_3cc [2];
  int local_3c4;
  float local_3c0;
  float local_3bc;
  float local_3b8;
  float local_3b4;
  uint8_t local_3b0 [88];
  int local_358;
  int local_33c;
  float local_32c;
  int local_320;
  uint32_t local_31c;
  int local_2e0;
  float local_2dc;
  int local_2d8;
  float local_2d4;
  float local_2d0;
  float local_2cc;
  float local_2c8;
  uint8_t local_2c4 [76];
  float local_278;
  float local_274;
  float local_270;
  int local_26c;
  int local_250;
  float local_240;
  int local_234;
  uint32_t local_230;
  float local_1f4 [2];
  int local_1ec;
  float local_1e8;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  uint8_t local_1d8 [144];
  int local_148;
  uint32_t local_144;
  float local_108 [2];
  int local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_a0;
  float local_9c;
  float local_98;
  
  tmp_b18 = 0;
  tmp_i11 = param_3[0x2b];
  tmp_b16 = tmp_i11 == *(int *)(g_unk_01047b00 + 0xcc);
  tmp_i10 = param_3[0x3a];
  if (param_2 == 0) {
    tmp_u4 = param_3[2];
    if ((tmp_u4 & 0x40000) != 0) {
      return;
    }
    tmp_b8 = tmp_i10 == 4 || tmp_i10 == 9;
    tmp_b3 = false;
  }
  else {
    if (g_unk_010aaecc != 0) {
      return;
    }
    tmp_u4 = param_3[2];
    if ((tmp_u4 & 0x40000) != 0) {
      return;
    }
    if (((tmp_i10 - 0x27U < 3) && (tmp_b16)) && (g_unk_010906f4 == 0)) {
      return;
    }
    tmp_b8 = tmp_i10 == 4 || tmp_i10 == 9;
    if (tmp_i10 == 4 || tmp_i10 == 9) {
      tmp_b3 = tmp_b8;
      if (*(int *)(param_2 + (tmp_i10 + 0xa4) * 4) == 0) {
        return;
      }
    }
    else {
      tmp_b3 = true;
    }
  }
  if ((tmp_u4 & 0x8000) != 0) {
    if ((tmp_b16) && (g_unk_010906f4 == 0)) {
      return;
    }
    if (0x1d < g_unk_010906e0 - param_3[0x92]) {
      return;
    }
    tmp_u4 = 0;
    do {
      *(uint32_t *)((int)local_108 + tmp_u4) = 0;
      *(uint32_t *)((int)local_108 + tmp_u4 + 4) = 0;
      tmp_u4 = tmp_u4 + 8;
    } while (tmp_u4 < 0xe8);
    *(uint32_t *)((int)local_108 + tmp_u4) = 0;
    local_108[1] = 4.48416e-44;
    local_100 = GHIDRA_FIELD(cgs, 68816, 4);
    tmp_i10 = *(int *)(cg_entities + *param_3 * 0xaf8 + 0xab4) * 0xaf8;
    local_a0 = *(float *)(cg_entities + tmp_i10 + 0xa80);
    local_9c = *(float *)(cg_entities + tmp_i10 + 0xa84);
    local_98 = *(float *)(cg_entities + tmp_i10 + 0xa88);
    AxisCopy(tmp_i10 + 0x31348cc,&local_ec);
    trap_R_AddRefEntityToScene(local_108);
    rand();
    tmp_u22 = 0x3e6b851f;
    tmp_u21 = 0x3f19999a;
    tmp_f20 = 1.0;
    goto LAB_000da0e1;
  }
  if ((tmp_u4 & 0x20) != 0) {
    if (0x1d < g_unk_010906e0 - param_3[0x92]) {
      return;
    }
    CG_MG42EFX(param_3);
    return;
  }
  if (((param_2 == 0) || (g_unk_010906f4 != 0)) && ((tmp_u4 & 0x100000) != 0)) {
    return;
  }
  tmp_b9 = tmp_i10 - 0x2cU < 2 || tmp_i10 - 0x22U < 2;
  local_424 = 0;
  if (tmp_b9) {
    if (tmp_b16) {
      tmp_u22 = BG_AkimboSidearm(tmp_i10);
      tmp_i11 = BG_FindClipForWeapon(tmp_u22);
      tmp_u22 = *(uint32_t *)(&g_unk_0109098c + tmp_i11 * 4);
      tmp_i11 = BG_FindClipForWeapon(tmp_i10);
      local_424 = BG_AkimboFireSequence(tmp_i10,*(uint32_t *)(&g_unk_0109098c + tmp_i11 * 4),tmp_u22);
      goto LAB_000da1c3;
    }
    if (!tmp_b3) {
      tmp_u4 = 0;
      do {
        tmp_u5 = tmp_u4;
        *(uint32_t *)((int)local_3cc + tmp_u5) = 0;
        *(uint32_t *)((int)local_3cc + tmp_u5 + 4) = 0;
        tmp_u4 = tmp_u5 + 8;
      } while (tmp_u5 + 8 < 0xe8);
      local_424 = 0;
      *(uint32_t *)((int)&local_3c4 + tmp_u5) = 0;
      local_3c0 = param_1[3];
      local_3bc = param_1[4];
      local_3b8 = param_1[5];
      local_3b4 = param_1[6];
      local_3cc[1] = param_1[1];
      goto LAB_000dc091;
    }
    tmp_u22 = BG_AkimboSidearm(tmp_i10);
    tmp_i11 = BG_FindClipForWeapon(tmp_u22);
    tmp_u22 = *(uint32_t *)(param_2 + (tmp_i11 + 0xa4) * 4);
    tmp_i11 = BG_FindClipForWeapon(tmp_i10);
    local_424 = BG_AkimboFireSequence(tmp_i10,*(uint32_t *)(param_2 + (tmp_i11 + 0xa4) * 4),tmp_u22);
    tmp_u4 = 0;
    do {
      tmp_u5 = tmp_u4;
      *(uint32_t *)((int)local_3cc + tmp_u5) = 0;
      *(uint32_t *)((int)local_3cc + tmp_u5 + 4) = 0;
      tmp_u4 = tmp_u5 + 8;
    } while (tmp_u5 + 8 < 0xe8);
    *(uint32_t *)((int)&local_3c4 + tmp_u5) = 0;
    local_3c0 = param_1[3];
    local_3bc = param_1[4];
    local_3b8 = param_1[5];
    local_3b4 = param_1[6];
    local_3cc[1] = param_1[1];
LAB_000da23c:
    tmp_i11 = *(int *)(param_2 + 300);
    if ((tmp_i10 == 0x1a) || ((*(byte *)(param_3 + 0x39) & 0x80) == 0)) {
      if (tmp_i11 == 1) goto LAB_000da26d;
      if (tmp_i11 == 2) goto LAB_000dbe64;
      local_3c4 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5d8);
    }
    else {
      if (tmp_i11 == 1) {
LAB_000dbe64:
        local_3c4 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5e0);
        if (local_3c4 == 0) {
          local_3c4 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5d8);
        }
        local_320 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5ec);
      }
      else {
LAB_000da26d:
        local_3c4 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5dc);
        if (local_3c4 == 0) {
          local_3c4 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5d8);
        }
        local_320 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5e8);
      }
      if (local_320 != 0) goto LAB_000da2c3;
    }
    local_320 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5e4);
  }
  else {
LAB_000da1c3:
    tmp_u4 = 0;
    do {
      tmp_u5 = tmp_u4;
      *(uint32_t *)((int)local_3cc + tmp_u5) = 0;
      *(uint32_t *)((int)local_3cc + tmp_u5 + 4) = 0;
      tmp_u4 = tmp_u5 + 8;
    } while (tmp_u5 + 8 < 0xe8);
    *(uint32_t *)((int)&local_3c4 + tmp_u5) = 0;
    local_3c0 = param_1[3];
    local_3bc = param_1[4];
    local_3b8 = param_1[5];
    local_3b4 = param_1[6];
    local_3cc[1] = param_1[1];
    if (tmp_b3) goto LAB_000da23c;
    tmp_i11 = param_3[0x2b];
LAB_000dc091:
    tmp_i11 = *(int *)(cgs + tmp_i11 * 0x1a4 + 0x9494);
    if ((tmp_i10 == 0x1a) || ((*(byte *)(param_3 + 0x39) & 0x80) == 0)) {
      if (tmp_i11 == 1) goto LAB_000dc0c9;
      if (tmp_i11 == 2) goto LAB_000dc6d6;
      local_3c4 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5c0);
LAB_000dc10d:
      local_320 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5cc);
    }
    else {
      if (tmp_i11 == 1) {
LAB_000dc6d6:
        local_3c4 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5c8);
        if (local_3c4 == 0) {
          local_3c4 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5c0);
        }
        local_320 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5d4);
      }
      else {
LAB_000dc0c9:
        local_3c4 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5c4);
        if (local_3c4 == 0) {
          local_3c4 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5c0);
        }
        local_320 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x5d0);
      }
      if (local_320 == 0) goto LAB_000dc10d;
    }
  }
LAB_000da2c3:
  local_3f0 = local_3cc;
  if (local_3c4 == 0) {
    return;
  }
  if (param_2 == 0) {
    if (((*(byte *)(g_unk_01047b00 + 0x38) & 4) != 0) && (tmp_b16)) {
      return;
    }
    param_3[0x11d] = 0;
    local_3e4 = param_3[2] & 0x80;
    if ((local_3e4 == 0) || (*(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x1754) == 0)) {
      if (*(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x1750) != 0) {
        trap_S_AddLoopingSound
                  (param_3 + 0x1e5,&vec3_origin,*(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x1750),0xff
                   ,0);
        local_3e4 = param_3[2] & 0x80;
      }
    }
    else {
      trap_S_AddLoopingSound
                (param_3 + 0x1e5,&vec3_origin,*(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x1754),0xff,0
                );
      param_3[0x11d] = 1;
      local_3e4 = param_3[2] & 0x80;
    }
LAB_000dbcf5:
    if ((tmp_i10 == 0x21) || (tmp_i10 == 0x2a)) {
      tmp_pc7 = "tag_weapon2";
    }
    else {
LAB_000da312:
      tmp_pc7 = "tag_weapon";
    }
    CG_PositionEntityOnTag(local_3f0,param_1,tmp_pc7,0,0);
    if (tmp_b3) goto LAB_000da355;
    if (tmp_i10 == 0xc) goto LAB_000dbf0a;
LAB_000da57e:
    local_3f4 = local_108;
    if (param_2 != 0) {
      if ((tmp_b16) && (g_unk_010906f4 == 0)) {
LAB_000dbf52:
        if (1 < (int)GHIDRA_FIELD(cg_drawGun, 12, 4)) {
          if (GHIDRA_FIELD(cg_drawGun, 12, 4) == 4) {
            local_31c = GHIDRA_FIELD(cgs, 131920, 4);
          }
          else if ((int)GHIDRA_FIELD(cg_drawGun, 12, 4) < 5) {
            if (GHIDRA_FIELD(cg_drawGun, 12, 4) == 3) {
              local_31c = GHIDRA_FIELD(cgs, 131916, 4);
            }
            else {
LAB_000dcc12:
              local_31c = GHIDRA_FIELD(cgs, 131912, 4);
            }
          }
          else if (GHIDRA_FIELD(cg_drawGun, 12, 4) == 5) {
            local_31c = GHIDRA_FIELD(cgs, 131924, 4);
          }
          else {
            if (GHIDRA_FIELD(cg_drawGun, 12, 4) != 6) goto LAB_000dcc12;
            local_31c = GHIDRA_FIELD(cgs, 68892, 4);
          }
        }
        goto LAB_000dbf99;
      }
      for (tmp_i11 = 0x3b; tmp_i11 != 0; tmp_i11 = tmp_i11 + -1) {
        *local_3f4 = *local_3f0;
        local_3f0 = local_3f0 + (uint)tmp_b18 * -2 + 1;
        local_3f4 = local_3f4 + (uint)tmp_b18 * -2 + 1;
      }
      trap_R_AddRefEntityToScene(local_3cc);
      pfVar14 = local_108;
      pfVar15 = local_3cc;
      for (tmp_i11 = 0x3b; tmp_i11 != 0; tmp_i11 = tmp_i11 + -1) {
        *pfVar15 = *pfVar14;
        pfVar14 = pfVar14 + (uint)tmp_b18 * -2 + 1;
        pfVar15 = pfVar15 + (uint)tmp_b18 * -2 + 1;
      }
      goto LAB_000da5cc;
    }
    if ((tmp_i10 == 0xb) && ((cgs[param_3[0x2b] * 0x1a4 + 0x9594] & 8) != 0)) {
      local_31c = GHIDRA_FIELD(cg_weapons, 72440, 4);
    }
    if (tmp_b16) goto LAB_000dbf42;
    for (tmp_i11 = 0x3b; tmp_i11 != 0; tmp_i11 = tmp_i11 + -1) {
      *local_3f4 = *local_3f0;
      local_3f0 = local_3f0 + (uint)tmp_b18 * -2 + 1;
      local_3f4 = local_3f4 + (uint)tmp_b18 * -2 + 1;
    }
    trap_R_AddRefEntityToScene(local_3cc);
    pfVar14 = local_108;
    pfVar15 = local_3cc;
    for (tmp_i11 = 0x3b; tmp_i11 != 0; tmp_i11 = tmp_i11 + -1) {
      *pfVar15 = *pfVar14;
      pfVar14 = pfVar14 + (uint)tmp_b18 * -2 + 1;
      pfVar15 = pfVar15 + (uint)tmp_b18 * -2 + 1;
    }
LAB_000dba4d:
    local_3f0 = local_3cc;
    if (tmp_b9) {
      tmp_pc7 = "tag_weapon2";
      CG_PositionEntityOnTag(local_3f0,param_1,"tag_weapon2",0,0);
      tmp_u4 = 0;
      do {
        tmp_u5 = tmp_u4;
        local_3f0 = local_3cc;
        tmp_u22 = *(uint32_t *)((int)local_3cc + tmp_u5 + 4);
        *(uint32_t *)((int)local_108 + tmp_u5) = *(uint32_t *)((int)local_3cc + tmp_u5);
        *(uint32_t *)((int)local_108 + tmp_u5 + 4) = tmp_u22;
        tmp_u4 = tmp_u5 + 8;
      } while (tmp_u4 < 0xe8);
      *(uint32_t *)((int)&local_100 + tmp_u5) = *(uint32_t *)((int)local_3f0 + tmp_u4);
      trap_R_AddRefEntityToScene(local_3f0);
      tmp_u4 = 0;
      do {
        tmp_u5 = tmp_u4;
        tmp_u22 = *(uint32_t *)((int)local_108 + tmp_u5 + 4);
        *(uint32_t *)((int)local_3cc + tmp_u5) = *(uint32_t *)((int)local_108 + tmp_u5);
        *(uint32_t *)((int)local_3cc + tmp_u5 + 4) = tmp_u22;
        tmp_u4 = tmp_u5 + 8;
      } while (tmp_u5 + 8 < 0xe8);
      *(uint32_t *)((int)&local_3c4 + tmp_u5) = *(uint32_t *)((int)&local_100 + tmp_u5);
      if ((!tmp_b3) || (g_unk_010906f4 != 0)) {
        if (param_3[0x2ac] != 0) goto LAB_000dba73;
        goto LAB_000dba7d;
      }
LAB_000dc221:
      tmp_pc7 = "tag_brass2";
      if (local_424 == 0) goto LAB_000da5eb;
      goto LAB_000da5f1;
    }
    if ((tmp_b3) && (g_unk_010906f4 == 0)) goto LAB_000da5eb;
LAB_000dba73:
    tmp_pc7 = "tag_weapon";
LAB_000dba7d:
    local_3f4 = local_108;
    CG_PositionRotatedEntityOnTag(local_3f4,param_1,tmp_pc7);
    param_3[0x1d6] = (int)local_a0;
    param_3[0x1d7] = (int)local_9c;
    param_3[0x1d8] = (int)local_98;
    tmp_u4 = 0;
    do {
      tmp_u5 = tmp_u4;
      *(uint32_t *)((int)&local_2e0 + tmp_u5) = 0;
      *(uint32_t *)((int)&local_2dc + tmp_u5) = 0;
      tmp_u4 = tmp_u5 + 8;
    } while (tmp_u5 + 8 < 0xe8);
    local_3d8 = 0.0;
    local_3d4 = 0.0;
    *(uint32_t *)((int)&local_2d8 + tmp_u5) = 0;
    local_2d4 = param_1[3];
    local_2d0 = param_1[4];
    local_2cc = param_1[5];
    local_2c8 = param_1[6];
    local_2dc = param_1[1];
    if (tmp_b3) goto LAB_000da6b8;
LAB_000dbb53:
    local_3f0 = local_3cc;
    local_400 = &local_2e0;
    if (tmp_i10 - 0x24U < 2) {
      local_2d8 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x1698);
      CG_PositionEntityOnTag(local_400,local_3f0,"tag_flash",0,0);
      CG_AddWeaponWithPowerups_isra_1();
      if (tmp_i10 == 0x25) {
        local_2d8 = GHIDRA_FIELD(cg_weapons, 230136, 4);
        CG_PositionEntityOnTag(local_400,local_400,"tag_prj",0,0);
        CG_AddWeaponWithPowerups_isra_1();
      }
    }
    else {
      if (((tmp_i10 != 0x18) && (1 < tmp_i10 - 0x27U)) && (tmp_i10 != 0x1e)) {
        if (tmp_i10 == 0x1d) {
          local_26c = 1;
          local_2d8 = GHIDRA_FIELD(cg_weapons, 181520, 4);
        }
        else {
          if (tmp_i10 != 0x2e) goto LAB_000daf13;
          local_26c = 0;
          local_2d8 = GHIDRA_FIELD(cg_weapons, 284540, 4);
        }
        tmp_pc7 = "tag_bipod";
        goto LAB_000dbbc1;
      }
      local_2d8 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x169c);
      CG_PositionEntityOnTag(local_400,local_3f0,"tag_scope",0,0);
      tmp_u4 = 0;
      do {
        tmp_u5 = tmp_u4;
        local_400 = &local_2e0;
        *(uint32_t *)((int)local_108 + tmp_u5) = *(uint32_t *)((int)&local_2e0 + tmp_u5);
        *(uint32_t *)((int)local_108 + tmp_u5 + 4) = *(uint32_t *)((int)&local_2dc + tmp_u5);
        tmp_u4 = tmp_u5 + 8;
      } while (tmp_u4 < 0xe8);
      *(uint32_t *)((int)&local_100 + tmp_u5) = *(uint32_t *)((int)local_400 + tmp_u4);
      trap_R_AddRefEntityToScene(local_400);
      tmp_u4 = 0;
      do {
        tmp_u5 = tmp_u4;
        tmp_u22 = *(uint32_t *)((int)local_108 + tmp_u5 + 4);
        *(uint32_t *)((int)&local_2e0 + tmp_u5) = *(uint32_t *)((int)local_108 + tmp_u5);
        *(uint32_t *)((int)&local_2dc + tmp_u5) = tmp_u22;
        tmp_u4 = tmp_u5 + 8;
      } while (tmp_u5 + 8 < 0xe8);
      *(uint32_t *)((int)&local_2d8 + tmp_u5) = *(uint32_t *)((int)&local_100 + tmp_u5);
    }
  }
  else {
    local_3e4 = param_3[2] & 0x80;
    if (g_unk_010906f4 != 0) goto LAB_000dbcf5;
    if ((g_unk_010907a0 != 0x2a) || (g_unk_010907a4 == 1)) goto LAB_000da312;
    local_100 = 0;
    local_108[1] = 0.0;
    tmp_l19 = (long double)AngleNormalize180(g_unk_010b16a4 - *(float *)(param_2 + 0xb0));
    local_108[0] = (float)(tmp_l19 * (long double)-0.4);
    AnglesToAxis(local_108,local_3b0);
    CG_PositionRotatedEntityOnTag(local_3f0,param_1,"tag_weapon");
LAB_000da355:
    tmp_i11 = param_3[0xe6];
    tmp_u4 = param_3[0xe4] & 0xfffffdff;
    if ((int)tmp_u4 < 1) {
      tmp_i12 = 0;
    }
    else {
      tmp_i12 = 0;
      if ((cg_weapons[tmp_i10 * 0x17ac + 0x5e] & 1) != 0) {
        tmp_i12 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x4c);
      }
      if (tmp_u4 != 1) {
        if ((cg_weapons[tmp_i10 * 0x17ac + 0xce] & 1) != 0) {
          tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0xbc);
        }
        if (tmp_u4 != 2) {
          if ((cg_weapons[tmp_i10 * 0x17ac + 0x13e] & 1) != 0) {
            tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 300);
          }
          if (tmp_u4 != 3) {
            if ((cg_weapons[tmp_i10 * 0x17ac + 0x1ae] & 1) != 0) {
              tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x19c);
            }
            if (tmp_u4 != 4) {
              if ((cg_weapons[tmp_i10 * 0x17ac + 0x21e] & 1) != 0) {
                tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x20c);
              }
              if (tmp_u4 != 5) {
                if ((cg_weapons[tmp_i10 * 0x17ac + 0x28e] & 1) != 0) {
                  tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x27c);
                }
                if (tmp_u4 != 6) {
                  if ((cg_weapons[tmp_i10 * 0x17ac + 0x2fe] & 1) != 0) {
                    tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x2ec);
                  }
                  if (tmp_u4 != 7) {
                    if ((cg_weapons[tmp_i10 * 0x17ac + 0x36e] & 1) != 0) {
                      tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x35c);
                    }
                    if (tmp_u4 != 8) {
                      if ((cg_weapons[tmp_i10 * 0x17ac + 0x3de] & 1) != 0) {
                        tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x3cc);
                      }
                      if (tmp_u4 != 9) {
                        if ((cg_weapons[tmp_i10 * 0x17ac + 0x44e] & 1) != 0) {
                          tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x43c);
                        }
                        if (tmp_u4 != 10) {
                          if ((cg_weapons[tmp_i10 * 0x17ac + 0x4be] & 1) != 0) {
                            tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x4ac);
                          }
                          if (tmp_u4 != 0xb) {
                            if ((cg_weapons[tmp_i10 * 0x17ac + 0x52e] & 1) != 0) {
                              tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x51c);
                            }
                            if ((tmp_u4 != 0xc) && ((cg_weapons[tmp_i10 * 0x17ac + 0x59e] & 1) != 0))
                            {
                              tmp_i12 = tmp_i12 + *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x58c);
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
    }
    if ((*(byte *)(tmp_i11 + 0x5a) & 1) != 0) {
      local_32c = param_1[0x28];
      local_33c = ((int)param_1[0x24] + tmp_i12) - *(int *)(tmp_i11 + 0x44);
      local_358 = (tmp_i12 + (int)param_1[0x1d]) - *(int *)(tmp_i11 + 0x44);
    }
    if (tmp_i10 != 0xc) goto LAB_000da57e;
    if (tmp_b3) {
      tmp_b2 = cgs[*(int *)(param_2 + 0xa0) * 0x1a4 + 0x9598];
    }
    else {
LAB_000dbf0a:
      tmp_b2 = cgs[param_3[0x2b] * 0x1a4 + 0x9598];
    }
    if ((tmp_b2 & 2) != 0) {
      local_31c = GHIDRA_FIELD(cg_weapons, 78500, 4);
    }
    if (tmp_b16) {
LAB_000dbf42:
      if (g_unk_010906f4 == 0) goto LAB_000dbf52;
    }
LAB_000dbf99:
    tmp_u4 = 0;
    do {
      tmp_u5 = tmp_u4;
      local_3f0 = local_3cc;
      tmp_u22 = *(uint32_t *)((int)local_3cc + tmp_u5 + 4);
      *(uint32_t *)((int)local_108 + tmp_u5) = *(uint32_t *)((int)local_3cc + tmp_u5);
      *(uint32_t *)((int)local_108 + tmp_u5 + 4) = tmp_u22;
      tmp_u4 = tmp_u5 + 8;
    } while (tmp_u4 < 0xe8);
    *(uint32_t *)((int)&local_100 + tmp_u5) = *(uint32_t *)((int)local_3f0 + tmp_u4);
    trap_R_AddRefEntityToScene(local_3f0);
    tmp_u4 = 0;
    do {
      tmp_u5 = tmp_u4;
      tmp_u22 = *(uint32_t *)((int)local_108 + tmp_u5 + 4);
      *(uint32_t *)((int)local_3cc + tmp_u5) = *(uint32_t *)((int)local_108 + tmp_u5);
      *(uint32_t *)((int)local_3cc + tmp_u5 + 4) = tmp_u22;
      tmp_u4 = tmp_u5 + 8;
    } while (tmp_u5 + 8 < 0xe8);
    *(uint32_t *)((int)&local_3c4 + tmp_u5) = *(uint32_t *)((int)&local_100 + tmp_u5);
    if (param_2 == 0) goto LAB_000dba4d;
LAB_000da5cc:
    if (g_unk_010906f4 != 0) goto LAB_000dba4d;
    if (tmp_b9) goto LAB_000dc221;
LAB_000da5eb:
    tmp_pc7 = "tag_brass";
LAB_000da5f1:
    local_3f4 = local_108;
    CG_PositionRotatedEntityOnTag(local_3f4,param_1,tmp_pc7);
    param_3[0x1d6] = (int)local_a0;
    param_3[0x1d7] = (int)local_9c;
    param_3[0x1d8] = (int)local_98;
    tmp_u4 = 0;
    do {
      tmp_u5 = tmp_u4;
      *(uint32_t *)((int)&local_2e0 + tmp_u5) = 0;
      *(uint32_t *)((int)&local_2dc + tmp_u5) = 0;
      tmp_u4 = tmp_u5 + 8;
    } while (tmp_u5 + 8 < 0xe8);
    *(uint32_t *)((int)&local_2d8 + tmp_u5) = 0;
    local_2d4 = param_1[3];
    local_2d0 = param_1[4];
    local_2cc = param_1[5];
    local_2c8 = param_1[6];
    local_2dc = param_1[1];
LAB_000da6b8:
    local_3f0 = local_3cc;
    local_400 = &local_2e0;
    local_3d4 = 0.0;
    local_3d8 = 0.0;
    local_410 = *(int *)(cgs + param_3[0x2b] * 0x1a4 + 0x9494);
    if ((tmp_i10 != 0x1a) && ((*(byte *)(param_3 + 0x39) & 0x80) != 0)) {
      local_410 = (local_410 == 1) + 1;
    }
    tmp_i11 = tmp_i10 * 0x17ac;
    local_420 = 0;
    local_40c = (int *)(cg_weapons + tmp_i11 + 0xbd0);
    local_408 = tmp_i11 + 0xfbee48;
    do {
      if (tmp_i10 == 0x1a) goto LAB_000dae70;
LAB_000da74b:
      if ((*(byte *)(param_3 + 0x39) & 0x80) == 0) {
        if (((tmp_i10 == 0x2a) && (local_420 - 3 < 2)) && (g_unk_010906f4 == 0)) goto LAB_000dae5a;
LAB_000dae70:
        if (local_410 != 1) {
          if (local_410 == 2) goto LAB_000db490;
LAB_000dae86:
          local_2d8 = local_40c[-2];
          goto LAB_000dae94;
        }
LAB_000da775:
        local_2d8 = local_40c[-1];
        if (local_2d8 == 0) {
          local_410 = 1;
          goto LAB_000dae86;
        }
        local_410 = 1;
        if (tmp_i10 == 0x2a) goto LAB_000db398;
LAB_000da7a0:
        CG_PositionEntityOnTag(local_400,param_1,local_408,0,0);
        goto LAB_000da7cb;
      }
      if (local_410 != 1) {
        if (((tmp_i10 == 0x2a) && (local_420 - 3 < 2)) && (local_410 = 1, g_unk_010906f4 == 0))
        goto LAB_000dae5a;
        goto LAB_000da775;
      }
      if (((tmp_i10 == 0x2a) && (local_420 - 3 < 2)) && (local_410 = 2, g_unk_010906f4 == 0)) {
LAB_000dae5a:
        if (g_unk_010907a4 == 1) goto LAB_000dae70;
        goto LAB_000daea7;
      }
LAB_000db490:
      if (local_40c[-0x160] == 0) {
        local_410 = 2;
        goto LAB_000dae86;
      }
      local_2d8 = *local_40c;
      local_410 = 2;
LAB_000dae94:
      if (tmp_i10 != 0x2a) {
LAB_000dae9f:
        if (local_2d8 != 0) goto LAB_000da7a0;
        goto LAB_000daea7;
      }
LAB_000db398:
      if (local_420 == 2) {
        if ((g_unk_010906f4 == 0) && (g_unk_010907a4 != 1)) {
          local_3d4 = 0.0;
          local_3d8 = 0.0;
          tmp_l19 = (long double)AngleNormalize180(g_unk_010b16a8 - *(float *)(param_2 + 0xb4));
          local_3d0 = (float)(tmp_l19 * (long double)0.8);
          AnglesToAxis(&local_3d8,local_2c4);
          if (local_2d8 != 0) goto LAB_000db42f;
        }
        else if (local_2d8 != 0) goto LAB_000da7a0;
        local_40c = local_40c + 0x16;
        local_408 = local_408 + 0x58;
        local_420 = 3;
        goto LAB_000da74b;
      }
      if (((1 < (int)local_420) || (g_unk_010906f4 != 0)) || (g_unk_010907a4 == 1)) goto LAB_000dae9f;
      local_3d0 = 0.0;
      local_3d4 = 0.0;
      tmp_l19 = (long double)AngleNormalize180(g_unk_010b16a4 - *(float *)(param_2 + 0xb0));
      local_3d8 = (float)(tmp_l19 * (long double)-0.4);
      AnglesToAxis(&local_3d8,local_2c4);
      if (local_2d8 == 0) goto LAB_000daea7;
LAB_000db42f:
      CG_PositionRotatedEntityOnTag(local_400,param_1,local_408);
LAB_000da7cb:
      tmp_i12 = param_3[0xe6];
      tmp_b2 = (byte)local_420;
      if ((*(int *)(tmp_i12 + 0x58) >> (tmp_b2 + 8 & 0x1f) & 1U) == 0) {
        tmp_u4 = param_3[0xe4] & 0xfffffdff;
        if ((int)tmp_u4 < 1) {
          tmp_i6 = 0;
        }
        else {
          tmp_u5 = 1 << (tmp_b2 & 0x1f);
          tmp_i6 = 0;
          if ((*(uint *)(cg_weapons + tmp_i11 + 0x5c) & tmp_u5) != 0) {
            tmp_i6 = *(int *)(cg_weapons + tmp_i11 + 0x4c);
          }
          if (tmp_u4 != 1) {
            if ((*(uint *)(cg_weapons + tmp_i11 + 0xcc) & tmp_u5) != 0) {
              tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 0xbc);
            }
            if (tmp_u4 != 2) {
              if ((*(uint *)(cg_weapons + tmp_i11 + 0x13c) & tmp_u5) != 0) {
                tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 300);
              }
              if (tmp_u4 != 3) {
                if ((*(uint *)(cg_weapons + tmp_i11 + 0x1ac) & tmp_u5) != 0) {
                  tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 0x19c);
                }
                if (tmp_u4 != 4) {
                  if ((*(uint *)(cg_weapons + tmp_i11 + 0x21c) & tmp_u5) != 0) {
                    tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 0x20c);
                  }
                  if (tmp_u4 != 5) {
                    if ((*(uint *)(cg_weapons + tmp_i11 + 0x28c) & tmp_u5) != 0) {
                      tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 0x27c);
                    }
                    if (tmp_u4 != 6) {
                      if ((*(uint *)(cg_weapons + tmp_i11 + 0x2fc) & tmp_u5) != 0) {
                        tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 0x2ec);
                      }
                      if (tmp_u4 != 7) {
                        if ((*(uint *)(cg_weapons + tmp_i11 + 0x36c) & tmp_u5) != 0) {
                          tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 0x35c);
                        }
                        if (tmp_u4 != 8) {
                          if ((*(uint *)(cg_weapons + tmp_i11 + 0x3dc) & tmp_u5) != 0) {
                            tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 0x3cc);
                          }
                          if (tmp_u4 != 9) {
                            if ((*(uint *)(cg_weapons + tmp_i11 + 0x44c) & tmp_u5) != 0) {
                              tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 0x43c);
                            }
                            if (tmp_u4 != 10) {
                              if ((*(uint *)(cg_weapons + tmp_i11 + 0x4bc) & tmp_u5) != 0) {
                                tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 0x4ac);
                              }
                              if (tmp_u4 != 0xb) {
                                if ((*(uint *)(cg_weapons + tmp_i11 + 0x52c) & tmp_u5) != 0) {
                                  tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 0x51c);
                                }
                                if ((tmp_u4 != 0xc) &&
                                   ((*(uint *)(cg_weapons + tmp_i11 + 0x59c) & tmp_u5) != 0)) {
                                  tmp_i6 = tmp_i6 + *(int *)(cg_weapons + tmp_i11 + 0x58c);
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
        }
        if ((*(int *)(tmp_i12 + 0x58) >> (tmp_b2 & 0x1f) & 1U) != 0) {
          local_240 = param_1[0x28];
          local_250 = ((int)param_1[0x24] + tmp_i6) - *(int *)(tmp_i12 + 0x44);
          local_26c = (tmp_i6 + (int)param_1[0x1d]) - *(int *)(tmp_i12 + 0x44);
        }
        tmp_b17 = tmp_i10 == 0x2a;
        if ((local_420 < 2 && tmp_b17) && (tmp_b17 = local_420 < 2 && tmp_b17, g_unk_010906f4 == 0)) {
          tmp_b17 = true;
LAB_000da9f0:
          if (g_unk_010907a4 != 1) {
            tmp_f20 = local_3d8 * 0.5;
            local_278 = *(float *)(g_unk_010afbcc + 0x24) * tmp_f20 + local_278;
            local_274 = *(float *)(g_unk_010afbcc + 0x28) * tmp_f20 + local_274;
            local_270 = tmp_f20 * *(float *)(g_unk_010afbcc + 0x2c) + local_270;
          }
          if (!tmp_b17) goto LAB_000daea7;
          tmp_b17 = true;
        }
        if (local_410 == 1) {
          local_234 = local_40c[2];
joined_r0x000db829:
          if (local_234 == 0) goto LAB_000daa66;
        }
        else {
          if (local_410 == 2) {
            local_234 = local_40c[3];
            goto joined_r0x000db829;
          }
LAB_000daa66:
          local_234 = local_40c[1];
        }
        if (((local_420 == 0) && (tmp_i10 == 0xb)) &&
           ((cgs[*(int *)(param_2 + 0xa0) * 0x1a4 + 0x9594] & 8) != 0)) {
          local_230 = GHIDRA_FIELD(cg_weapons, 72440, 4);
        }
        if (((tmp_b16) && (g_unk_010906f4 == 0)) && (1 < (int)GHIDRA_FIELD(cg_drawGun, 12, 4))) {
          if (GHIDRA_FIELD(cg_drawGun, 12, 4) == 4) {
            local_230 = GHIDRA_FIELD(cgs, 131920, 4);
          }
          else if ((int)GHIDRA_FIELD(cg_drawGun, 12, 4) < 5) {
            if (GHIDRA_FIELD(cg_drawGun, 12, 4) == 3) {
              local_230 = GHIDRA_FIELD(cgs, 131916, 4);
            }
            else {
LAB_000dc496:
              local_230 = GHIDRA_FIELD(cgs, 131912, 4);
            }
          }
          else if (GHIDRA_FIELD(cg_drawGun, 12, 4) == 5) {
            local_230 = GHIDRA_FIELD(cgs, 131924, 4);
          }
          else {
            if (GHIDRA_FIELD(cg_drawGun, 12, 4) != 6) goto LAB_000dc496;
            local_230 = GHIDRA_FIELD(cgs, 68892, 4);
          }
        }
        tmp_u4 = 0;
        do {
          tmp_u5 = tmp_u4;
          *(uint32_t *)((int)local_108 + tmp_u5) = *(uint32_t *)((int)&local_2e0 + tmp_u5);
          *(uint32_t *)((int)local_108 + tmp_u5 + 4) = *(uint32_t *)((int)&local_2dc + tmp_u5);
          tmp_u4 = tmp_u5 + 8;
        } while (tmp_u4 < 0xe8);
        *(uint32_t *)((int)&local_100 + tmp_u5) = *(uint32_t *)((int)local_400 + tmp_u4);
        trap_R_AddRefEntityToScene(local_400);
        tmp_u4 = 0;
        do {
          tmp_u5 = tmp_u4;
          tmp_u22 = *(uint32_t *)((int)local_108 + tmp_u5 + 4);
          *(uint32_t *)((int)&local_2e0 + tmp_u5) = *(uint32_t *)((int)local_108 + tmp_u5);
          *(uint32_t *)((int)&local_2dc + tmp_u5) = tmp_u22;
          tmp_u4 = tmp_u5 + 8;
        } while (tmp_u4 < 0xe8);
        *(uint32_t *)((int)local_400 + tmp_u4) = *(uint32_t *)((int)&local_100 + tmp_u5);
        if (tmp_i10 == 1) {
          if (g_unk_010ee05c != 0) {
            if (g_unk_010ee05c < 0xc9) {
              if (g_unk_010ee05c < 0x97) {
                if (g_unk_010ee05c < 0x65) {
                  if (g_unk_010ee05c < 0x33) {
                    local_230 = GHIDRA_FIELD(cg_weapons, 11840, 4);
                  }
                  else {
                    local_230 = GHIDRA_FIELD(cg_weapons, 11844, 4);
                  }
                }
                else {
                  local_230 = GHIDRA_FIELD(cg_weapons, 11848, 4);
                }
              }
              else {
                local_230 = GHIDRA_FIELD(cg_weapons, 11852, 4);
              }
            }
            else {
              local_230 = GHIDRA_FIELD(cg_weapons, 11856, 4);
            }
            trap_R_AddRefEntityToScene(local_400);
          }
        }
        else if ((local_420 == 0) && (tmp_i10 == 0x1b)) {
          if (g_unk_010b4530 == 0) {
            tmp_l19 = (long double)4004001.0;
          }
          else {
            tmp_l19 = (long double)DistanceSquared(g_unk_010b4530 + 0x794,&g_unk_0109143c);
          }
          tmp_u4 = 0;
          do {
            *(uint32_t *)((int)local_1f4 + tmp_u4) = 0;
            *(uint32_t *)((int)local_1f4 + tmp_u4 + 4) = 0;
            tmp_u4 = tmp_u4 + 8;
          } while (tmp_u4 < 0xe8);
          *(uint32_t *)((int)local_1f4 + tmp_u4) = 0;
          local_1e8 = param_1[3];
          local_1e4 = param_1[4];
          local_1e0 = param_1[5];
          local_1dc = param_1[6];
          local_1f4[1] = param_1[1];
          local_1ec = GHIDRA_FIELD(cg_weapons, 169400, 4);
          CG_PositionEntityOnTag(local_1f4,local_400,"tag_rlight",0,0);
          if (4e+06 < (float)tmp_l19) {
            local_144 = GHIDRA_FIELD(cg_weapons, 169412, 4);
            tmp_u4 = 0;
            do {
              tmp_u5 = tmp_u4;
              tmp_u22 = *(uint32_t *)((int)local_1f4 + tmp_u5 + 4);
              *(uint32_t *)((int)local_108 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u5);
              *(uint32_t *)((int)local_108 + tmp_u5 + 4) = tmp_u22;
              tmp_u4 = tmp_u5 + 8;
            } while (tmp_u4 < 0xe8);
            *(uint32_t *)((int)&local_100 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u4);
            trap_R_AddRefEntityToScene(local_1f4);
            tmp_u4 = 0;
            do {
              tmp_u5 = tmp_u4;
              tmp_u22 = *(uint32_t *)((int)local_108 + tmp_u5 + 4);
              *(uint32_t *)((int)local_1f4 + tmp_u5) = *(uint32_t *)((int)local_108 + tmp_u5);
              *(uint32_t *)((int)local_1f4 + tmp_u5 + 4) = tmp_u22;
              tmp_u4 = tmp_u5 + 8;
            } while (tmp_u4 < 0xe8);
            *(uint32_t *)((int)local_1f4 + tmp_u4) = *(uint32_t *)((int)&local_100 + tmp_u5);
            CG_PositionEntityOnTag(local_1f4,local_400,"tag_glight",0,0);
            local_144 = GHIDRA_FIELD(cg_weapons, 169416, 4);
            tmp_u4 = 0;
            do {
              tmp_u5 = tmp_u4;
              tmp_u22 = *(uint32_t *)((int)local_1f4 + tmp_u5 + 4);
              *(uint32_t *)((int)local_108 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u5);
              *(uint32_t *)((int)local_108 + tmp_u5 + 4) = tmp_u22;
              tmp_u4 = tmp_u5 + 8;
            } while (tmp_u4 < 0xe8);
            *(uint32_t *)((int)&local_100 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u4);
            trap_R_AddRefEntityToScene(local_1f4);
            tmp_u4 = 0;
            do {
              tmp_u5 = tmp_u4;
              tmp_u22 = *(uint32_t *)((int)local_108 + tmp_u5 + 4);
              *(uint32_t *)((int)local_1f4 + tmp_u5) = *(uint32_t *)((int)local_108 + tmp_u5);
              *(uint32_t *)((int)local_1f4 + tmp_u5 + 4) = tmp_u22;
              tmp_u4 = tmp_u5 + 8;
            } while (tmp_u4 < 0xe8);
            local_3d4 = 30.0;
            *(uint32_t *)((int)local_1f4 + tmp_u4) = *(uint32_t *)((int)&local_100 + tmp_u5);
          }
          else {
            local_144 = GHIDRA_FIELD(cg_weapons, 169408, 4);
            tmp_u4 = 0;
            do {
              tmp_u5 = tmp_u4;
              tmp_u22 = *(uint32_t *)((int)local_1f4 + tmp_u5 + 4);
              *(uint32_t *)((int)local_108 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u5);
              *(uint32_t *)((int)local_108 + tmp_u5 + 4) = tmp_u22;
              tmp_u4 = tmp_u5 + 8;
            } while (tmp_u4 < 0xe8);
            *(uint32_t *)((int)&local_100 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u4);
            trap_R_AddRefEntityToScene(local_1f4);
            tmp_u4 = 0;
            do {
              tmp_u5 = tmp_u4;
              tmp_u22 = *(uint32_t *)((int)local_108 + tmp_u5 + 4);
              *(uint32_t *)((int)local_1f4 + tmp_u5) = *(uint32_t *)((int)local_108 + tmp_u5);
              *(uint32_t *)((int)local_1f4 + tmp_u5 + 4) = tmp_u22;
              tmp_u4 = tmp_u5 + 8;
            } while (tmp_u4 < 0xe8);
            *(uint32_t *)((int)local_1f4 + tmp_u4) = *(uint32_t *)((int)&local_100 + tmp_u5);
            CG_PositionEntityOnTag(local_1f4,local_400,"tag_glight",0,0);
            local_144 = GHIDRA_FIELD(cg_weapons, 169420, 4);
            tmp_u4 = 0;
            do {
              tmp_u5 = tmp_u4;
              tmp_u22 = *(uint32_t *)((int)local_1f4 + tmp_u5 + 4);
              *(uint32_t *)((int)local_108 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u5);
              *(uint32_t *)((int)local_108 + tmp_u5 + 4) = tmp_u22;
              tmp_u4 = tmp_u5 + 8;
            } while (tmp_u4 < 0xe8);
            *(uint32_t *)((int)&local_100 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u4);
            trap_R_AddRefEntityToScene(local_1f4);
            tmp_u4 = 0;
            do {
              tmp_u5 = tmp_u4;
              tmp_u22 = *(uint32_t *)((int)local_108 + tmp_u5 + 4);
              *(uint32_t *)((int)local_1f4 + tmp_u5) = *(uint32_t *)((int)local_108 + tmp_u5);
              *(uint32_t *)((int)local_1f4 + tmp_u5 + 4) = tmp_u22;
              tmp_u4 = tmp_u5 + 8;
            } while (tmp_u4 < 0xe8);
            *(uint32_t *)((int)local_1f4 + tmp_u4) = *(uint32_t *)((int)&local_100 + tmp_u5);
            local_3d4 = ((float)tmp_l19 / 4e+06) * 60.0 - 30.0;
          }
          local_3d0 = 0.0;
          local_3d8 = 0.0;
          local_1ec = GHIDRA_FIELD(cg_weapons, 169404, 4);
          AnglesToAxis(&local_3d8,local_1d8);
          CG_PositionRotatedEntityOnTag(local_1f4,local_400,"tag_needle");
          local_144 = GHIDRA_FIELD(cg_weapons, 169408, 4);
          trap_R_AddRefEntityToScene(local_1f4);
          goto LAB_000daea7;
        }
        if ((((tmp_b17) && (local_420 == 2)) && (g_unk_010906f4 == 0)) && (g_unk_010907a4 != 1)) {
          tmp_u4 = 0;
          do {
            local_3f4 = local_108;
            *(uint32_t *)((int)local_1f4 + tmp_u4) = 0;
            *(uint32_t *)((int)local_1f4 + tmp_u4 + 4) = 0;
            tmp_u4 = tmp_u4 + 8;
          } while (tmp_u4 < 0xe8);
          *(uint32_t *)((int)local_1f4 + tmp_u4) = 0;
          local_1e8 = param_1[3];
          local_1e4 = param_1[4];
          local_1e0 = param_1[5];
          local_1dc = param_1[6];
          local_1f4[1] = param_1[1];
          if (local_410 == 1) {
            local_1ec = GHIDRA_FIELD(cg_weapons, 257804, 4);
            if (GHIDRA_FIELD(cg_weapons, 257804, 4) == 0) {
              local_1ec = GHIDRA_FIELD(cg_weapons, 257800, 4);
            }
            local_148 = GHIDRA_FIELD(cg_weapons, 257816, 4);
            if (GHIDRA_FIELD(cg_weapons, 257816, 4) == 0) {
              local_148 = GHIDRA_FIELD(cg_weapons, 257812, 4);
              CG_PositionEntityOnTag(local_1f4,local_400,"tag_barrel4",0,0);
              tmp_u4 = 0;
              do {
                tmp_u5 = tmp_u4;
                tmp_u22 = *(uint32_t *)((int)local_1f4 + tmp_u5 + 4);
                *(uint32_t *)((int)local_108 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u5);
                *(uint32_t *)((int)local_108 + tmp_u5 + 4) = tmp_u22;
                tmp_u4 = tmp_u5 + 8;
              } while (tmp_u4 < 0xe8);
              *(uint32_t *)((int)&local_100 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u4);
              trap_R_AddRefEntityToScene(local_1f4);
              tmp_u4 = 0;
              do {
                tmp_u5 = tmp_u4;
                tmp_u22 = *(uint32_t *)((int)local_108 + tmp_u5 + 4);
                *(uint32_t *)((int)local_1f4 + tmp_u5) = *(uint32_t *)((int)local_108 + tmp_u5);
                *(uint32_t *)((int)local_1f4 + tmp_u5 + 4) = tmp_u22;
                tmp_u4 = tmp_u5 + 8;
              } while (tmp_u4 < 0xe8);
              *(uint32_t *)((int)local_1f4 + tmp_u4) = *(uint32_t *)((int)&local_100 + tmp_u5);
              local_148 = GHIDRA_FIELD(cg_weapons, 257904, 4);
            }
            else {
              CG_PositionEntityOnTag(local_1f4,local_400,"tag_barrel4",0,0);
              pfVar14 = local_1f4;
              for (tmp_i12 = 0x3b; tmp_i12 != 0; tmp_i12 = tmp_i12 + -1) {
                *local_3f4 = *pfVar14;
                pfVar14 = pfVar14 + (uint)tmp_b18 * -2 + 1;
                local_3f4 = local_3f4 + (uint)tmp_b18 * -2 + 1;
              }
              trap_R_AddRefEntityToScene(local_1f4);
              pfVar14 = local_108;
              pfVar15 = local_1f4;
              for (tmp_i12 = 0x3b; local_148 = GHIDRA_FIELD(cg_weapons, 257904, 4), tmp_i12 != 0;
                  tmp_i12 = tmp_i12 + -1) {
                *pfVar15 = *pfVar14;
                pfVar14 = pfVar14 + (uint)tmp_b18 * -2 + 1;
                pfVar15 = pfVar15 + (uint)tmp_b18 * -2 + 1;
              }
            }
            local_1ec = GHIDRA_FIELD(cg_weapons, 257892, 4);
            if (GHIDRA_FIELD(cg_weapons, 257892, 4) == 0) {
              local_1ec = GHIDRA_FIELD(cg_weapons, 257888, 4);
            }
            GHIDRA_FIELD(cg_weapons, 257904, 4) = local_148;
            if (local_148 == 0) goto LAB_000dc7e3;
          }
          else {
            if (local_410 == 2) {
              local_1ec = GHIDRA_FIELD(cg_weapons, 257808, 4);
              if (GHIDRA_FIELD(cg_weapons, 257808, 4) == 0) {
                local_1ec = GHIDRA_FIELD(cg_weapons, 257800, 4);
              }
              local_148 = GHIDRA_FIELD(cg_weapons, 257820, 4);
              if (GHIDRA_FIELD(cg_weapons, 257820, 4) == 0) {
                local_148 = GHIDRA_FIELD(cg_weapons, 257812, 4);
              }
              CG_PositionEntityOnTag(local_1f4,local_400,"tag_barrel4",0,0);
              pfVar14 = local_1f4;
              for (tmp_i12 = 0x3b; tmp_i12 != 0; tmp_i12 = tmp_i12 + -1) {
                *local_3f4 = *pfVar14;
                pfVar14 = pfVar14 + (uint)tmp_b18 * -2 + 1;
                local_3f4 = local_3f4 + (uint)tmp_b18 * -2 + 1;
              }
              trap_R_AddRefEntityToScene(local_1f4);
              pfVar14 = local_108;
              pfVar15 = local_1f4;
              for (tmp_i12 = 0x3b; tmp_i12 != 0; tmp_i12 = tmp_i12 + -1) {
                *pfVar15 = *pfVar14;
                pfVar14 = pfVar14 + (uint)tmp_b18 * -2 + 1;
                pfVar15 = pfVar15 + (uint)tmp_b18 * -2 + 1;
              }
              local_1ec = GHIDRA_FIELD(cg_weapons, 257896, 4);
              if (GHIDRA_FIELD(cg_weapons, 257896, 4) == 0) {
                local_1ec = GHIDRA_FIELD(cg_weapons, 257888, 4);
              }
              local_148 = GHIDRA_FIELD(cg_weapons, 257908, 4);
              if (GHIDRA_FIELD(cg_weapons, 257908, 4) != 0) goto LAB_000dc7e9;
            }
            else {
              local_1ec = GHIDRA_FIELD(cg_weapons, 257800, 4);
              local_148 = GHIDRA_FIELD(cg_weapons, 257812, 4);
              CG_PositionEntityOnTag(local_1f4,local_400,"tag_barrel4",0,0);
              tmp_u4 = 0;
              do {
                tmp_u5 = tmp_u4;
                tmp_u22 = *(uint32_t *)((int)local_1f4 + tmp_u5 + 4);
                *(uint32_t *)((int)local_108 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u5);
                *(uint32_t *)((int)local_108 + tmp_u5 + 4) = tmp_u22;
                tmp_u4 = tmp_u5 + 8;
              } while (tmp_u4 < 0xe8);
              *(uint32_t *)((int)&local_100 + tmp_u5) = *(uint32_t *)((int)local_1f4 + tmp_u4);
              trap_R_AddRefEntityToScene(local_1f4);
              tmp_u4 = 0;
              do {
                tmp_u5 = tmp_u4;
                tmp_u22 = *(uint32_t *)((int)local_108 + tmp_u5 + 4);
                *(uint32_t *)((int)local_1f4 + tmp_u5) = *(uint32_t *)((int)local_108 + tmp_u5);
                *(uint32_t *)((int)local_1f4 + tmp_u5 + 4) = tmp_u22;
                tmp_u4 = tmp_u5 + 8;
              } while (tmp_u4 < 0xe8);
              *(uint32_t *)((int)local_1f4 + tmp_u4) = *(uint32_t *)((int)&local_100 + tmp_u5);
              local_1ec = GHIDRA_FIELD(cg_weapons, 257888, 4);
            }
LAB_000dc7e3:
            local_148 = GHIDRA_FIELD(cg_weapons, 257900, 4);
          }
LAB_000dc7e9:
          CG_PositionEntityOnTag(local_1f4,local_400,"tag_barrel5",0,0);
          trap_R_AddRefEntityToScene(local_1f4);
        }
      }
      else if (((local_420 < 2) && (tmp_i10 == 0x2a)) && (tmp_b17 = false, g_unk_010906f4 == 0))
      goto LAB_000da9f0;
LAB_000daea7:
      tmp_i12 = g_unk_01047b00;
      local_420 = local_420 + 1;
      local_40c = local_40c + 0x16;
      local_408 = local_408 + 0x58;
    } while (local_420 != 0x10);
    if ((g_unk_010906f4 != 0) || (!tmp_b16)) goto LAB_000dbb53;
    if ((tmp_i10 - 0x24U < 2) || (tmp_i10 - 0x16U < 2)) {
      tmp_i6 = BG_FindAmmoForWeapon(0x24);
      tmp_i11 = g_unk_01047b00;
      if ((*(int *)(tmp_i12 + 0x1bc + tmp_i6 * 4) == 0) &&
         (((tmp_i6 = BG_FindAmmoForWeapon(0x25), tmp_i12 = g_unk_01047b00,
           *(int *)(tmp_i11 + 0x1bc + tmp_i6 * 4) == 0 &&
           (tmp_i6 = BG_FindAmmoForWeapon(0x24), tmp_i11 = g_unk_01047b00,
           *(int *)(tmp_i12 + 700 + tmp_i6 * 4) == 0)) &&
          (tmp_i12 = BG_FindAmmoForWeapon(0x25), *(int *)(tmp_i11 + 700 + tmp_i12 * 4) == 0))))
      goto LAB_000daf13;
      tmp_u4 = *(uint *)(g_unk_01047b00 + 0x4ac);
      tmp_u5 = PM_AltSwitchFromForWeapon(tmp_i10);
      tmp_u4 = tmp_u4 & 0xfffffdff;
      if ((((tmp_u5 != tmp_u4) && (tmp_u5 = PM_AltSwitchToForWeapon(tmp_i10), tmp_u5 != tmp_u4)) &&
          (tmp_u5 = PM_IdleAnimForWeapon(tmp_i10), tmp_u5 != tmp_u4)) ||
         (local_2d8 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x1694), local_2d8 == 0))
      goto LAB_000daf13;
      tmp_pc7 = "tag_scope";
      local_3f0 = param_1;
    }
    else {
      if (tmp_i10 == 0x18) {
        local_2d8 = GHIDRA_FIELD(cg_weapons, 151220, 4);
        if (GHIDRA_FIELD(cg_weapons, 151220, 4) != 0) {
          CG_PositionEntityOnTag(local_400,local_3f0,"tag_scope2",0,0);
          CG_AddWeaponWithPowerups_isra_1();
        }
        local_2d8 = GHIDRA_FIELD(cg_weapons, 151224, 4);
        tmp_pc7 = "tag_flash";
      }
      else {
        if (tmp_i10 != 0x1e) goto LAB_000daf13;
        local_2d8 = GHIDRA_FIELD(cg_weapons, 187580, 4);
        if (GHIDRA_FIELD(cg_weapons, 187580, 4) != 0) {
          CG_PositionEntityOnTag(local_400,local_3f0,"tag_scope",0,0);
          CG_AddWeaponWithPowerups_isra_1();
        }
        local_2d8 = GHIDRA_FIELD(cg_weapons, 187584, 4);
        tmp_pc7 = "tag_flash";
      }
LAB_000dbbc1:
      local_3f0 = local_3cc;
    }
    local_400 = &local_2e0;
    CG_PositionEntityOnTag(local_400,local_3f0,tmp_pc7,0,0);
    CG_AddWeaponWithPowerups_isra_1();
  }
LAB_000daf13:
  local_420 = tmp_i10 - 0x24;
  local_3e8 = &local_3d8;
  local_3f0 = local_3cc;
  local_3f4 = local_108;
  tmp_i11 = param_3[0x2b] * 0xaf8;
  tmp_pi13 = (int *)(cg_entities + tmp_i11);
  if (param_3[0x2b] != (tmp_i11 >> 3) * -0xbab6561) {
    tmp_pi13 = param_3;
  }
  tmp_u4 = 0;
  do {
    *(uint32_t *)((int)local_3f4 + tmp_u4) = 0;
    *(uint32_t *)((int)local_108 + tmp_u4 + 4) = 0;
    tmp_u4 = tmp_u4 + 8;
  } while (tmp_u4 < 0xe8);
  *(uint32_t *)((int)local_3f4 + tmp_u4) = 0;
  local_fc = param_1[3];
  local_f8 = param_1[4];
  local_f4 = param_1[5];
  local_f0 = param_1[6];
  local_108[1] = param_1[1];
  if (tmp_b3) {
    local_100 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x168c);
  }
  else {
    local_100 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x1688);
  }
  local_3d4 = 0.0;
  local_3d8 = 0.0;
  tmp_u4 = rand();
  tmp_f20 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
  local_3d0 = (tmp_f20 + tmp_f20) * 10.0;
  AnglesToAxis(local_3e8,&local_ec);
  if (tmp_b9) {
    if ((param_2 == 0) || (g_unk_010906f4 != 0)) {
      if (param_3[0x2ac] != 0) goto LAB_000db025;
      CG_PositionRotatedEntityOnTag(local_3f4,param_1,"tag_weapon");
      local_a0 = local_ec * 10.0 + local_a0;
      local_9c = local_e8 * 10.0 + local_9c;
      local_98 = local_e4 * 10.0 + local_98;
    }
    else {
      if (param_3[0x2ac] == 0) {
        tmp_pc7 = "tag_flash2";
      }
      else {
        tmp_pc7 = "tag_flash";
      }
      CG_PositionRotatedEntityOnTag(local_3f4,param_1,tmp_pc7);
    }
  }
  else {
LAB_000db025:
    CG_PositionRotatedEntityOnTag(local_3f4,local_3f0,"tag_flash");
  }
  tmp_u4 = 0;
  do {
    tmp_u5 = tmp_u4;
    *(uint32_t *)((int)param_3 + tmp_u5 + 0x650) = *(uint32_t *)((int)local_3cc + tmp_u5);
    *(uint32_t *)((int)param_3 + tmp_u5 + 0x654) = *(uint32_t *)((int)local_3cc + tmp_u5 + 4);
    tmp_u4 = tmp_u5 + 8;
  } while (tmp_u4 < 0xe8);
  *(uint32_t *)((int)param_3 + tmp_u5 + 0x658) = *(uint32_t *)((int)local_3f0 + tmp_u4);
  param_3[0x1cf] = cg;
  if (tmp_i10 == 6) {
    if ((*(byte *)(tmp_pi13 + 2) & 0x80) == 0) {
      if (tmp_b3) {
        if (g_unk_010906e0 - param_3[0x93] < 3000) goto LAB_000dc365;
        goto LAB_000dc26a;
      }
      if (tmp_b16 <= (g_unk_010906f4 != 0)) goto LAB_000db0c3;
      goto LAB_000dc2c2;
    }
    if (tmp_b8) {
      return;
    }
  }
  else {
    if ((!tmp_b3) && ((g_unk_010906f4 != 0) < tmp_b16)) goto LAB_000dc2c2;
    if (tmp_i10 == 5) {
      if ((g_unk_010906e0 - param_3[0x92] < 1000) && (tmp_i11 = rand(), tmp_i11 % 5 == 0)) {
        CG_ParticleImpactSmokePuffExtended
                  (GHIDRA_FIELD(cgs, 68876, 4),&local_a0,1000,8,0x14,0x1e,
                   (1.0 - (float)(g_unk_010906e0 - param_3[0x92]) / 1000.0) * 0.25,0x41000000);
      }
LAB_000dc26a:
      tmp_i11 = g_unk_010906e0 - param_3[0x92];
    }
    else {
LAB_000db0c3:
      if (g_unk_010906e0 - param_3[0x93] < 3000) {
LAB_000dc365:
        tmp_i11 = rand();
        if (tmp_i11 == (tmp_i11 / 3) * 3) {
          CG_ParticleImpactSmokePuffExtended
                    (GHIDRA_FIELD(cgs, 68876, 4),&local_a0,1000,8,0x14,0x1e,
                     (1.0 - (float)(g_unk_010906e0 - param_3[0x93]) / 3000.0) * 0.25,0x41000000);
        }
      }
      if ((!tmp_b3) || (tmp_i10 != 0x2a)) goto LAB_000dc26a;
      if (g_unk_010906f4 == 0) {
        tmp_i11 = g_unk_010906e0 - param_3[0x92];
        if (tmp_i11 < 800) {
          CG_ParticleImpactSmokePuffExtended
                    (GHIDRA_FIELD(cgs, 68876, 4),&local_a0,700,0x10,0x14,0x1e,0x3df5c28f,0x40800000);
          goto LAB_000dc2c2;
        }
      }
      else {
LAB_000dc2c2:
        tmp_i11 = g_unk_010906e0 - param_3[0x92];
      }
    }
    if ((0x1e < tmp_i11) && (tmp_i10 != 6)) {
      return;
    }
    if (tmp_b8) {
      return;
    }
    if (local_420 < 2) {
      return;
    }
    if (tmp_i10 == 1) {
      return;
    }
  }
  if (tmp_i10 == 0xf) {
    return;
  }
  if (tmp_i10 - 0x19U < 4) {
    return;
  }
  if (tmp_i10 - 0xbU < 2) {
    return;
  }
  if (tmp_i10 == 0x2b) {
    return;
  }
  if (tmp_i10 - 0x12U < 4) {
    return;
  }
  if (tmp_i10 - 0x2fU < 5) {
    return;
  }
  if ((tmp_b3) || (tmp_b16 <= (g_unk_010906f4 != 0))) {
    if (tmp_i10 == 10) {
      tmp_i11 = GHIDRA_FIELD(cg_weapons, 66612, 4);
      if (GHIDRA_FIELD(cg_weapons, 66612, 4) != 0) goto LAB_000db1ca;
      if (g_unk_010906e0 - param_3[0x92] < 100) {
        CG_ParticleImpactSmokePuffExtended
                  (GHIDRA_FIELD(cgs, 68876, 4),&local_a0,500,8,0x14,0x1e,0x3e800000,0x41000000);
      }
    }
    else {
      tmp_i11 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x177c);
      if (*(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x177c) != 0) {
LAB_000db1ca:
        tmp_f20 = *(float *)(cg_weapons + tmp_i10 * 0x17ac + 0x1788);
        if (tmp_f20 == 0.0) {
          tmp_f20 = 0.25;
        }
        tmp_i12 = *(int *)(cg_weapons + tmp_i10 * 0x17ac + 0x1784);
        tmp_f1 = *(float *)(cg_weapons + tmp_i10 * 0x17ac + 0x1780);
        if (tmp_i12 == 0) {
          tmp_i12 = 500;
        }
        if (tmp_f1 == 0.0) {
          tmp_f1 = 8.0;
        }
        CG_ParticleImpactSmokePuffExtended(tmp_i11,&local_a0,tmp_i12,8,0x14,0x1e,tmp_f20,tmp_f1);
      }
    }
    if (local_100 != 0) goto LAB_000db268;
LAB_000dcdb8:
    if ((!tmp_b3) && ((g_unk_010906f4 != 0) < tmp_b16)) {
      return;
    }
  }
  else {
    if (local_100 == 0) {
      return;
    }
LAB_000db268:
    if ((param_2 == 0) || (GHIDRA_FIELD(cg_muzzleFlash, 12, 4) != 0)) {
      if ((tmp_i10 != 6) && (g_unk_010906e0 - param_3[0x92] < 0x1e)) {
        trap_R_AddRefEntityToScene(local_3f4);
      }
      goto LAB_000dcdb8;
    }
  }
  if ((local_3e4 == 0) || ((param_3[2] & 0x100001U) != 0)) {
    if (tmp_i10 != 6) {
      return;
    }
    AxisToAngles(&local_ec,local_1f4);
    tmp_i10 = BG_FindAmmoForWeapon(6);
    if ((tmp_b3) && (*(int *)(param_2 + (tmp_i10 + 0xa4) * 4) == 0)) {
      return;
    }
    CG_FireFlameChunks(param_3,&local_a0,local_1f4,0x3f800000,0,0);
    return;
  }
  if (param_3[0x3a] == 6) {
    CG_FireFlameChunks(param_3,&local_a0,param_3 + 0x1e8,0x3f800000,1,0);
  }
  tmp_i11 = tmp_i10 * 0x17ac;
  tmp_f20 = *(float *)(cg_weapons + tmp_i11 + 0x16ac);
  if (((tmp_f20 == 0.0) && (*(float *)(cg_weapons + tmp_i11 + 0x16b0) == 0.0)) &&
     (*(float *)(cg_weapons + tmp_i11 + 0x16b4) == 0.0)) {
    return;
  }
  tmp_u22 = *(uint32_t *)(cg_weapons + tmp_i10 * 0x17ac + 0x16b4);
  tmp_u21 = *(uint32_t *)(cg_weapons + tmp_i10 * 0x17ac + 0x16b0);
  rand();
LAB_000da0e1:
  trap_R_AddLightToScene(&local_a0,0x43a00000,0x3fa00000,tmp_f20,tmp_u21,tmp_u22,0,0);
  return;
}

void CG_AddViewWeapon(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  float tmp_f5;
  float tmp_f6;
  uint tmp_u7;
  int tmp_i8;
  float *pfVar9;
  int tmp_i10;
  float *pfVar11;
  float *pfVar12;
  uint32_t local_200;
  uint32_t local_1fc;
  float local_1f8;
  float local_1f4 [29];
  int local_180;
  int local_164;
  float local_154;
  uint32_t local_144;
  float local_108 [62];
  
  if (*(int *)(param_1 + 300) == 3) {
    return;
  }
  if (*(int *)(param_1 + 0xd0) < 1) {
    return;
  }
  tmp_u7 = *(uint *)(param_1 + 0x68);
  if ((tmp_u7 & 0x800000) != 0) {
    return;
  }
  if (*(int *)(param_1 + 4) == 5) {
    return;
  }
  if (g_unk_010906f4 != 0) {
    return;
  }
  if (g_unk_010b4554 != 0) {
    return;
  }
  if (GHIDRA_FIELD(cg_drawGun, 12, 4) == 0) {
    if ((_DAT_01090764 & 0x80a0) == 0x80) {
      local_108[0] = *(float *)(g_unk_010afbcc + 0x3c) * -4.0 +
                     *(float *)(g_unk_010afbcc + 0x30) * -7.0 +
                     *(float *)(g_unk_010afbcc + 0x24) * 18.0 + *(float *)(g_unk_010afbcc + 0x18);
      local_108[1] = *(float *)(g_unk_010afbcc + 0x40) * -4.0 +
                     *(float *)(g_unk_010afbcc + 0x34) * -7.0 +
                     *(float *)(g_unk_010afbcc + 0x28) * 18.0 + *(float *)(g_unk_010afbcc + 0x1c);
      local_108[2] = *(float *)(g_unk_010afbcc + 0x44) * -4.0 +
                     *(float *)(g_unk_010afbcc + 0x38) * -7.0 +
                     *(float *)(g_unk_010afbcc + 0x2c) * 18.0 + *(float *)(g_unk_010afbcc + 0x20);
      if (g_unk_01090d90 == 6) {
        CG_FireFlameChunks(&g_unk_01090ca8,local_108,&g_unk_01091448,0x3f800000,1,0);
      }
    }
    if (g_unk_010b3b24 == 0) {
      return;
    }
    if (g_unk_010b3b24 < 0) {
      if (g_unk_010906e0 <= 700 - g_unk_010b3b24) {
        return;
      }
    }
    else {
      if (g_unk_010906e0 <= g_unk_010b3b24 + 500) {
        return;
      }
      trap_SendConsoleCommand("+zoom\n");
    }
    g_unk_010b3b24 = 0;
    return;
  }
  if (g_unk_010aaea8 != 0) {
    return;
  }
  if ((tmp_u7 & 0x20) != 0) {
    return;
  }
  if ((int)GHIDRA_FIELD(cg_fov, 12, 4) < 0x5b) {
    tmp_f1 = 0.0;
  }
  else {
    tmp_f1 = (float)(GHIDRA_FIELD(cg_fov, 12, 4) + -0x5a) * -0.2;
  }
  if ((tmp_u7 & 0x8000) != 0) {
    tmp_u7 = 0;
    do {
      *(uint32_t *)((int)local_1f4 + tmp_u7) = 0;
      *(uint32_t *)((int)local_1f4 + tmp_u7 + 4) = 0;
      tmp_u7 = tmp_u7 + 8;
    } while (tmp_u7 < 0xe8);
    *(uint32_t *)((int)local_1f4 + tmp_u7) = 0;
    CG_CalculateWeaponPosition();
    AnglesToAxis(&local_200,local_1f4 + 7);
    local_1f4[1] = 1.82169e-44;
    local_1f4[2] = (float)GHIDRA_FIELD(cgs, 69856, 4);
    if ((cg_entities
         [*(int *)(cg_entities +
                  *(int *)(cg_entities + *(int *)(param_1 + 0xa0) * 0xaf8 + 0xab4) * 0xaf8 + 0x9bc)
          * 0xaf8 + 0xf4] & 8) == 0) {
      local_1f4[2] = (float)GHIDRA_FIELD(cgs, 69852, 4);
    }
    if (g_unk_010906e0 - g_unk_01090ef0 < 0x1e) {
      tmp_u7 = rand();
      tmp_f2 = (float)(tmp_u7 & 0x7fff) / 32767.0;
      tmp_f2 = tmp_f2 + tmp_f2 + 20.0;
    }
    else {
      tmp_f2 = 20.0;
    }
    tmp_f1 = tmp_f1 - 8.0;
    local_1f4[0x1a] =
         *(float *)(g_unk_010afbcc + 0x3c) * tmp_f1 +
         *(float *)(g_unk_010afbcc + 0x30) * -10.0 +
         *(float *)(g_unk_010afbcc + 0x24) * tmp_f2 + local_1f4[0x1a];
    local_1f4[0x1b] =
         *(float *)(g_unk_010afbcc + 0x40) * tmp_f1 +
         *(float *)(g_unk_010afbcc + 0x34) * -10.0 +
         *(float *)(g_unk_010afbcc + 0x28) * tmp_f2 + local_1f4[0x1b];
    local_1f4[0x1c] =
         tmp_f1 * *(float *)(g_unk_010afbcc + 0x44) +
         *(float *)(g_unk_010afbcc + 0x38) * -10.0 +
         tmp_f2 * *(float *)(g_unk_010afbcc + 0x2c) + local_1f4[0x1c];
    if (1 < (int)GHIDRA_FIELD(cg_drawGun, 12, 4)) {
      if (GHIDRA_FIELD(cg_drawGun, 12, 4) == 4) {
        local_144 = GHIDRA_FIELD(cgs, 131920, 4);
      }
      else {
        if ((int)GHIDRA_FIELD(cg_drawGun, 12, 4) < 5) {
          if (GHIDRA_FIELD(cg_drawGun, 12, 4) == 3) {
            local_144 = GHIDRA_FIELD(cgs, 131916, 4);
            goto LAB_000dd63c;
          }
        }
        else {
          if (GHIDRA_FIELD(cg_drawGun, 12, 4) == 5) {
            local_144 = GHIDRA_FIELD(cgs, 131924, 4);
            goto LAB_000dd63c;
          }
          if (GHIDRA_FIELD(cg_drawGun, 12, 4) == 6) {
            local_144 = GHIDRA_FIELD(cgs, 68892, 4);
            goto LAB_000dd63c;
          }
        }
        local_144 = GHIDRA_FIELD(cgs, 131912, 4);
      }
    }
LAB_000dd63c:
    CG_AddWeaponWithPowerups_isra_1();
    if ((g_unk_010906e0 - g_unk_01090ef4 < 3000) && (tmp_i10 = rand(), tmp_i10 % 3 == 0)) {
      CG_ParticleImpactSmokePuffExtended
                (GHIDRA_FIELD(cgs, 68876, 4),&g_unk_010b4548,1000,8,0x14,0x1e,
                 (1.0 - (float)(g_unk_010906e0 - g_unk_01090ef4) / 3000.0) * 0.25,0x41000000);
    }
    tmp_u7 = 0;
    do {
      *(uint32_t *)((int)local_108 + tmp_u7) = 0;
      *(uint32_t *)((int)local_108 + tmp_u7 + 4) = 0;
      tmp_u7 = tmp_u7 + 8;
    } while (tmp_u7 < 0xe8);
    *(uint32_t *)((int)local_108 + tmp_u7) = 0;
    local_108[2] = (float)GHIDRA_FIELD(cgs, 68816, 4);
    local_108[1] = 5.60519e-44;
    local_1fc = 0;
    local_200 = 0;
    tmp_u7 = rand();
    tmp_f1 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
    local_1f8 = (tmp_f1 + tmp_f1) * 10.0;
    AnglesToAxis(&local_200,local_108 + 7);
    CG_PositionRotatedEntityOnTag(local_108,local_1f4,"tag_flash");
    local_108[0x1a] = local_108[7] * 22.0 + local_108[0x1a];
    local_108[0x1b] = local_108[8] * 22.0 + local_108[0x1b];
    local_108[0x1c] = local_108[9] * 22.0 + local_108[0x1c];
    if (0x1d < g_unk_010906e0 - g_unk_01090ef0) {
      g_unk_010b4548 = local_108[0x1a];
      g_unk_010b454c = local_108[0x1b];
      g_unk_010b4550 = local_108[0x1c];
      return;
    }
    g_unk_010b4548 = local_108[0x1a];
    g_unk_010b454c = local_108[0x1b];
    g_unk_010b4550 = local_108[0x1c];
    trap_R_AddRefEntityToScene(local_108);
    return;
  }
  tmp_i10 = *(int *)(param_1 + 0xa4);
  if (tmp_i10 < 1) {
    return;
  }
  tmp_u7 = 0;
  do {
    *(uint32_t *)((int)local_1f4 + tmp_u7) = 0;
    *(uint32_t *)((int)local_1f4 + tmp_u7 + 4) = 0;
    tmp_u7 = tmp_u7 + 8;
  } while (tmp_u7 < 0xe8);
  *(uint32_t *)((int)local_1f4 + tmp_u7) = 0;
  CG_CalculateWeaponPosition();
  tmp_i8 = tmp_i10 * 0x17ac;
  if (((*(float *)(cg_weapons + tmp_i8 + 0x17a0) != 0.0) ||
      (*(float *)(cg_weapons + tmp_i8 + 0x17a4) != 0.0)) ||
     (tmp_f2 = (float)GHIDRA_FIELD(cg_gun_x, 8, 4), tmp_f5 = (float)GHIDRA_FIELD(cg_gun_z, 8, 4), tmp_f6 = (float)GHIDRA_FIELD(cg_gun_y, 8, 4),
     *(float *)(cg_weapons + tmp_i8 + 0x17a8) != 0.0)) {
    tmp_f2 = (float)GHIDRA_FIELD(cg_gun_x, 8, 4) + *(float *)(cg_weapons + tmp_i8 + 0x17a0);
    tmp_f5 = (float)GHIDRA_FIELD(cg_gun_z, 8, 4) + *(float *)(cg_weapons + tmp_i10 * 0x17ac + 0x17a8);
    tmp_f6 = (float)GHIDRA_FIELD(cg_gun_y, 8, 4) + *(float *)(cg_weapons + tmp_i10 * 0x17ac + 0x17a4);
  }
  tmp_f1 = tmp_f1 + tmp_f5;
  local_1f4[0x1a] =
       *(float *)(g_unk_010afbcc + 0x3c) * tmp_f1 +
       *(float *)(g_unk_010afbcc + 0x30) * tmp_f6 +
       *(float *)(g_unk_010afbcc + 0x24) * tmp_f2 + local_1f4[0x1a];
  local_1f4[0x1b] =
       *(float *)(g_unk_010afbcc + 0x40) * tmp_f1 +
       *(float *)(g_unk_010afbcc + 0x34) * tmp_f6 +
       *(float *)(g_unk_010afbcc + 0x28) * tmp_f2 + local_1f4[0x1b];
  pfVar12 = local_1f4 + 7;
  local_1f4[0x1c] =
       tmp_f1 * *(float *)(g_unk_010afbcc + 0x44) +
       tmp_f6 * *(float *)(g_unk_010afbcc + 0x38) +
       tmp_f2 * *(float *)(g_unk_010afbcc + 0x2c) + local_1f4[0x1c];
  AnglesToAxis(&local_200,pfVar12);
  if (g_unk_010b3b24 != 0) {
    if (g_unk_010b3b24 < 0) {
      if (700 - g_unk_010b3b24 < g_unk_010906e0) {
        g_unk_010b3b24 = 0;
      }
      else {
        if (g_unk_010906e0 <= 200 - g_unk_010b3b24) goto LAB_000dd2d1;
        CG_ContinueWeaponAnim();
      }
    }
    else if (g_unk_010b3b24 + 500 < g_unk_010906e0) {
      trap_SendConsoleCommand("+zoom\n");
      g_unk_010b3b24 = 0;
LAB_000dd2d1:
      CG_ContinueWeaponAnim();
    }
    else {
      CG_ContinueWeaponAnim();
    }
  }
  if (GHIDRA_FIELD(cg_noPlayerAnims, 12, 4) != 0) {
    local_180 = 0;
    local_164 = 0;
    goto LAB_000dd302;
  }
  tmp_u7 = *(uint *)(param_1 + 0x480);
  if (GHIDRA_FIELD(cg_animSpeed, 12, 4) == 0) {
    g_unk_01091024 = 0.0;
    g_unk_01091018 = 0;
    g_unk_0109100c = 0;
  }
  else {
    if (g_unk_01091040 == (uint32_t *)0x0) {
      g_unk_01091010 = g_unk_010906e0;
      pfVar9 = (float *)(tmp_u7 & 0xfffffdff);
      g_unk_0109101c = g_unk_010906e0;
      g_unk_01091038 = tmp_u7;
      if (0xd < (int)pfVar9 + 1U) {
        CG_Error("Bad animation number (CG_SWLFA): %i",pfVar9);
        pfVar12 = pfVar9;
      }
LAB_000ddba7:
      pfVar9 = (float *)(tmp_u7 & 0xfffffdff);
      tmp_i8 = tmp_i10 * 0x17ac + (int)pfVar9 * 0x70;
      g_unk_01091040 = (uint32_t *)(cg_weapons + tmp_i8 + 4);
      g_unk_01091044 = *(int *)(cg_weapons + tmp_i8 + 0x58) + g_unk_0109101c;
      if ((GHIDRA_FIELD(cg_debugAnim, 12, 4) & 2) != 0) {
        CG_Printf("Weap Anim: %d\n",pfVar9);
        pfVar12 = pfVar9;
      }
      g_unk_0109100c = g_unk_01091040[0x11];
      g_unk_01091014 = *g_unk_01091040;
      g_unk_01091018 = g_unk_0109100c;
      g_unk_01091020 = g_unk_01091014;
    }
    else if ((tmp_u7 != g_unk_01091038) && (tmp_u7 != 0xffffffff)) {
      pfVar11 = (float *)(tmp_u7 & 0xfffffdff);
      pfVar9 = (float *)PM_RaiseAnimForWeapon(*(uint32_t *)(g_unk_01047b00 + 0x448));
      if (pfVar11 == pfVar9) {
        g_unk_01091010 = g_unk_010906e0;
        g_unk_0109101c = g_unk_010906e0;
        g_unk_01091038 = tmp_u7;
        if (0xd < (int)pfVar11 + 1U) {
          CG_Error("Bad animation number (CG_SWLFA): %i",pfVar11);
          pfVar12 = pfVar11;
        }
        goto LAB_000ddba7;
      }
      g_unk_01091038 = tmp_u7;
      if (0xd < (int)pfVar11 + 1U) {
        pfVar12 = pfVar11;
        CG_Error("Bad animation number (CG_SWLFA): %i",pfVar11);
      }
      tmp_i8 = tmp_i10 * 0x17ac + (int)pfVar11 * 0x70;
      g_unk_01091040 = (uint32_t *)(cg_weapons + tmp_i8 + 4);
      g_unk_01091044 = *(int *)(cg_weapons + tmp_i8 + 0x58) + g_unk_0109101c;
      if ((GHIDRA_FIELD(cg_debugAnim, 12, 4) & 2) != 0) {
        CG_Printf("Weap Anim: %d\n",pfVar11);
        pfVar12 = pfVar11;
      }
    }
    if (g_unk_0109101c <= g_unk_010906e0) {
      g_unk_01091010 = g_unk_0109101c;
      g_unk_0109100c = g_unk_01091018;
      g_unk_01091014 = g_unk_01091020;
      if (g_unk_01091040[0x14] == 0) goto LAB_000dd9a2;
      g_unk_0109101c = g_unk_01091040[0x14] + g_unk_0109101c;
      if (g_unk_010906e0 < g_unk_01091044) {
        g_unk_0109101c = g_unk_01091044;
      }
      tmp_i8 = (int)ROUND((long double)((g_unk_0109101c - g_unk_01091044) / (int)g_unk_01091040[0x14]));
      tmp_i3 = g_unk_01091040[0x12];
      if (tmp_i3 <= tmp_i8) {
        tmp_i4 = g_unk_01091040[0x13];
        if (tmp_i4 == 0) {
          tmp_i8 = tmp_i3 + -1;
          g_unk_0109101c = g_unk_010906e0;
        }
        else {
          tmp_i8 = (tmp_i3 - tmp_i4) + (tmp_i8 - tmp_i3) % tmp_i4;
        }
      }
      g_unk_01091018 = tmp_i8 + g_unk_01091040[0x11];
      g_unk_01091020 = *g_unk_01091040;
      if ((g_unk_0109101c < g_unk_010906e0) && (g_unk_0109101c = g_unk_010906e0, GHIDRA_FIELD(cg_debugAnim, 12, 4) != 0))
      {
        CG_Printf("Clamp lf->frameTime\n",pfVar12);
      }
    }
    if (g_unk_010906e0 + 200 < g_unk_0109101c) {
      g_unk_0109101c = g_unk_010906e0;
    }
    if (g_unk_010906e0 < g_unk_01091010) {
      g_unk_01091010 = g_unk_010906e0;
    }
    if (g_unk_0109101c == g_unk_01091010) {
      g_unk_01091024 = 0.0;
    }
    else {
      g_unk_01091024 = 1.0 - (float)(g_unk_010906e0 - g_unk_01091010) /
                           (float)(g_unk_0109101c - g_unk_01091010);
    }
  }
LAB_000dd9a2:
  local_164 = g_unk_0109100c;
  local_180 = g_unk_01091018;
  local_154 = g_unk_01091024;
  if (GHIDRA_FIELD(cg_debugAnim, 12, 4) == 3) {
    CG_Printf("oldframe: %d   frame: %d   backlerp: %f\n",g_unk_0109100c,g_unk_01091018,
              (double)g_unk_01091024);
  }
LAB_000dd302:
  local_1f4[2] = *(float *)(cg_weapons + tmp_i10 * 0x17ac + 0x5b4);
  tmp_f1 = *(float *)(cg_weapons + tmp_i10 * 0x17ac + 0x179c);
  if (tmp_f1 != 0.0) {
    local_1f4[7] = local_1f4[7] * tmp_f1;
    local_1f4[0x19] = 1.4013e-45;
    local_1f4[8] = local_1f4[8] * tmp_f1;
    local_1f4[9] = tmp_f1 * local_1f4[9];
  }
  local_1f4[5] = *(float *)(param_1 + 0x1c) + 31.0;
  local_1f4[1] = 6.30584e-44;
  local_1f4[3] = *(float *)(param_1 + 0x14);
  local_1f4[4] = *(float *)(param_1 + 0x18);
  CG_AddPlayerWeapon(local_1f4,param_1,&g_unk_01090ca8);
  return;
}

uint32_t CG_AddSparks(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  uint32_t tmp_u1;
  
  if (GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0) {
    param_2 = param_4;
    tmp_u1 = CG_AddSparks_part_12();
    return tmp_u1;
  }
  return param_1;
}

uint32_t CG_AddBulletParticles(uint32_t param_1)
{
  uint32_t tmp_u1;
  uint32_t uStack00000008;
  uint32_t in_stack_00000014;
  
  if (GHIDRA_FIELD(cg_impactparticles, 12, 4) != 0) {
    uStack00000008 = in_stack_00000014;
    tmp_u1 = CG_AddBulletParticles_part_13();
    return tmp_u1;
  }
  return param_1;
}

void CG_AddDirtBulletParticles(void)
{
  uint32_t uStack00000008;
  uint32_t in_stack_00000010;
  
  if (GHIDRA_FIELD(cg_impactparticles, 12, 4) == 0) {
    return;
  }
  uStack00000008 = in_stack_00000010;
  CG_AddDirtBulletParticles_part_14();
  return;
}

void CG_AddDebris(uint32_t *param_1,float *param_2,int param_3,int param_4,int param_5)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  uint tmp_u9;
  uint tmp_u10;
  int tmp_i11;
  uint tmp_u12;
  int tmp_i13;
  int local_80;
  uint local_7c;
  
  if (0 < param_5) {
    tmp_f4 = (float)param_3;
    local_80 = 0;
    do {
      tmp_i11 = CG_AllocLocalEntity();
      tmp_f1 = *param_2;
      tmp_u12 = rand();
      tmp_f7 = (float)(tmp_u12 & 0x7fff) / 32767.0 - 0.5;
      tmp_f2 = param_2[1];
      tmp_u12 = rand();
      tmp_f8 = (float)(tmp_u12 & 0x7fff) / 32767.0 - 0.5;
      tmp_f3 = param_2[2];
      if (0.5 < ABS(tmp_f3)) {
        tmp_u12 = rand();
        tmp_f3 = tmp_f3 * (((float)(tmp_u12 & 0x7fff) / 32767.0) * 0.8 + 0.2);
      }
      else {
        tmp_u12 = rand();
        tmp_f3 = ((float)(tmp_u12 & 0x7fff) / 32767.0) * 0.6;
      }
      tmp_f5 = tmp_f4 * 0.5;
      tmp_u12 = rand();
      local_7c = rand();
      tmp_u9 = rand();
      *(uint32_t *)(tmp_i11 + 8) = 10;
      tmp_i13 = param_4 + g_unk_010906e0;
      *(int *)(tmp_i11 + 0x10) = g_unk_010906e0;
      tmp_u10 = rand();
      tmp_f6 = (float)(tmp_u10 & 0x7fff) / 32767.0 - 0.5;
      *(int *)(tmp_i11 + 0x14) = (int)ROUND((tmp_f6 + tmp_f6) * (float)param_4 * 0.8) + tmp_i13;
      *(int *)(tmp_i11 + 0x184) = g_unk_010906e0;
      *(uint32_t *)(tmp_i11 + 0x100) = *param_1;
      *(uint32_t *)(tmp_i11 + 0x104) = param_1[1];
      *(uint32_t *)(tmp_i11 + 0x108) = param_1[2];
      AxisCopy(axisDefault,tmp_i11 + 0xb4);
      *(uint32_t *)(tmp_i11 + 0x20) = 7;
      *(uint32_t *)(tmp_i11 + 0x2c) = *param_1;
      *(uint32_t *)(tmp_i11 + 0x30) = param_1[1];
      *(uint32_t *)(tmp_i11 + 0x34) = param_1[2];
      tmp_f6 = (float)(tmp_u12 & 0x7fff) / 32767.0 - 0.5;
      local_7c = local_7c & 0x7fff;
      *(float *)(tmp_i11 + 0x38) =
           ((tmp_f6 + tmp_f6) * tmp_f5 + tmp_f4) * ((tmp_f7 + tmp_f7) * 0.9 + tmp_f1);
      tmp_f1 = (float)local_7c;
      local_7c = tmp_u9 & 0x7fff;
      tmp_f1 = tmp_f1 / 32767.0 - 0.5;
      *(float *)(tmp_i11 + 0x3c) =
           ((tmp_f1 + tmp_f1) * tmp_f5 + tmp_f4) * ((tmp_f8 + tmp_f8) * 0.9 + tmp_f2);
      tmp_f1 = (float)local_7c / 32767.0 - 0.5;
      *(float *)(tmp_i11 + 0x40) = ((tmp_f1 + tmp_f1) * tmp_f5 + tmp_f4) * tmp_f3;
      *(int *)(tmp_i11 + 0x24) = g_unk_010906e0;
      local_7c = rand();
      local_7c = local_7c & 0x7fff;
      BG_EvaluateTrajectory
                (tmp_i11 + 0x20,(int)ROUND(((float)local_7c / 32767.0) * 40.0 + 10.0) + g_unk_010906e0,
                 tmp_i11 + 0x2c,0,0xffffffff);
      *(uint32_t *)(tmp_i11 + 0x68) = 0x3f000000;
      local_7c = rand();
      local_80 = local_80 + 1;
      *(uint *)(tmp_i11 + 0x194) = *(uint *)(tmp_i11 + 0x194) | 1;
      local_7c = local_7c & 0x7fff;
      *(float *)(tmp_i11 + 400) = ((float)local_7c / 32767.0) * 5.0 + 5.0;
    } while (local_80 != param_5);
  }
  return;
}

void CG_WaterRipple(uint32_t param_1,uint32_t *param_2,uint32_t param_3,int param_4,
                   int param_5)

{
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i3 = CG_AllocLocalEntity();
  *(uint32_t *)(tmp_i3 + 8) = 8;
  *(uint32_t *)(tmp_i3 + 0xc) = 1;
  tmp_i2 = g_unk_010906e0;
  *(int *)(tmp_i3 + 0x10) = g_unk_010906e0;
  param_5 = param_5 + g_unk_010906e0;
  *(int *)(tmp_i3 + 0x14) = param_5;
  *(float *)(tmp_i3 + 0x1c) = 1.0 / (float)(param_5 - tmp_i2);
  *(uint32_t *)(tmp_i3 + 0x100) = *param_2;
  *(uint32_t *)(tmp_i3 + 0x104) = param_2[1];
  *(uint32_t *)(tmp_i3 + 0x108) = param_2[2];
  tmp_f1 = (float)g_unk_010906e0;
  *(uint32_t *)(tmp_i3 + 0x98) = 3;
  *(uint8_t *)(tmp_i3 + 0x14c) = 0xff;
  *(uint8_t *)(tmp_i3 + 0x14d) = 0xff;
  *(uint8_t *)(tmp_i3 + 0x14e) = 0xff;
  *(uint32_t *)(tmp_i3 + 0x148) = param_1;
  *(uint8_t *)(tmp_i3 + 0x14f) = 0xff;
  *(uint32_t *)(tmp_i3 + 0x78) = 0x3f800000;
  *(float *)(tmp_i3 + 0x158) = tmp_f1 / 1000.0;
  *(float *)(tmp_i3 + 0x15c) = (float)param_4;
  return;
}

