/**
 * @file ui_ui_shared.c
 * @brief ui_shared
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 */

#include "ui_types.h"
#include "ui_globals.h"
#include "ui_imports.h"
#include "ui_ui_shared.h"

bool BG_AddMagicAmmo(int param_1,int param_2,int param_3,int param_4) {
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  float tmp_f5;
  bool tmp_b6;
  uint tmp_u7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  int *tmp_pi12;
  int *tmp_pi13;
  int tmp_i14;
  bool tmp_b15;
  int local_30;

  tmp_b15 = (*(uint *)(param_1 + 0x68) & 0x1000) != 0;
  if (tmp_b15) {
    *(uint *)(param_1 + 0x68) = *(uint *)(param_1 + 0x68) & 0xffffefff;
  }
  tmp_i14 = 5;
  tmp_u7 = *(int *)(param_1 + 0xe4) - 1;
  if (tmp_u7 < 4) {
    tmp_i14 = *(int *)(CSWTCH_90 + tmp_u7 * 4);
  }
  tmp_u7 = *(uint *)(param_2 + 0x10);
  tmp_f5 = (float)jP_GrenadesPerLevel._96_4_;
  if (((float)jP_GrenadesPerLevel._96_4_ != (float)jP_GrenadesPerLevel._100_4_) &&
     ((tmp_u7 & 2) != 0)) {
    tmp_f5 = (float)jP_GrenadesPerLevel._100_4_;
  }
  if (((float)jP_GrenadesPerLevel._104_4_ != (float)jP_GrenadesPerLevel._100_4_) &&
     ((tmp_u7 & 4) != 0)) {
    tmp_f5 = (float)jP_GrenadesPerLevel._104_4_;
  }
  if (((float)jP_GrenadesPerLevel._108_4_ != (float)jP_GrenadesPerLevel._104_4_) &&
     ((tmp_u7 & 8) != 0)) {
    tmp_f5 = (float)jP_GrenadesPerLevel._108_4_;
  }
  if (((float)jP_GrenadesPerLevel._112_4_ != (float)jP_GrenadesPerLevel._108_4_) &&
     ((tmp_u7 & 0x10) != 0)) {
    tmp_f5 = (float)jP_GrenadesPerLevel._112_4_;
  }
  if (((float)jP_GrenadesPerLevel._116_4_ != (float)jP_GrenadesPerLevel._112_4_) &&
     ((tmp_u7 & 0x20) != 0)) {
    tmp_f5 = (float)jP_GrenadesPerLevel._116_4_;
  }
  tmp_i8 = tmp_i14 * 0x18;
  tmp_f1 = *(float *)(jP_GrenadesPerLevel + tmp_i8);
  tmp_f2 = *(float *)(jP_GrenadesPerLevel + tmp_i8 + 4);
  tmp_u4 = *(uint *)(param_2 + tmp_i14 * 4);
  if ((tmp_f2 != tmp_f1) && ((tmp_u4 & 2) != 0)) {
    tmp_f1 = tmp_f2;
  }
  tmp_f3 = *(float *)(jP_GrenadesPerLevel + tmp_i8 + 8);
  if ((tmp_f3 != tmp_f2) && ((tmp_u4 & 4) != 0)) {
    tmp_f1 = tmp_f3;
  }
  tmp_f2 = *(float *)(jP_GrenadesPerLevel + tmp_i8 + 0xc);
  if ((tmp_f2 != tmp_f3) && ((tmp_u4 & 8) != 0)) {
    tmp_f1 = tmp_f2;
  }
  tmp_f3 = *(float *)(jP_GrenadesPerLevel + tmp_i8 + 0x10);
  if ((tmp_f3 != tmp_f2) && ((tmp_u4 & 0x10) != 0)) {
    tmp_f1 = tmp_f3;
  }
  tmp_f2 = tmp_f1;
  if ((*(float *)(jP_GrenadesPerLevel + tmp_i8 + 0x14) != tmp_f3) &&
     (tmp_f2 = *(float *)(jP_GrenadesPerLevel + tmp_i8 + 0x14), (tmp_u4 & 0x20) == 0)) {
    tmp_f2 = tmp_f1;
  }
  tmp_i14 = (int)ROUND(tmp_f5) + (int)ROUND(tmp_f2);
  if (param_3 == 1) {
    tmp_i8 = 4;
  }
  else {
    tmp_i8 = (uint)(param_3 == 2) * 9;
  }
  tmp_b6 = tmp_b15;
  if (bg_itemlist._56_4_ == 0) {
    tmp_i10 = *(int *)(param_1 + 0x290);
    if (tmp_i10 < tmp_i14) {
      local_30 = 0;
      goto LAB_00017fd2;
    }
LAB_0001809c:
    tmp_i14 = 0;
LAB_0001809e:
    tmp_i8 = 1;
    if ((tmp_u7 & 0x20) != 0) {
      tmp_i8 = ammoTableMP._72_4_;
    }
    if (tmp_i10 < tmp_i8) {
      if (param_4 == 0) goto LAB_00017fde;
      tmp_i14 = param_1 + tmp_i14 * 4;
      *(int *)(tmp_i14 + 0x290) = tmp_i10 + param_4;
      COM_BitSet(param_1 + 0x3d4,1);
      if (tmp_i8 < *(int *)(tmp_i14 + 0x290)) {
        *(int *)(tmp_i14 + 0x290) = tmp_i8;
        tmp_b6 = true;
        tmp_b15 = true;
      }
      else {
        tmp_b6 = true;
        tmp_b15 = true;
      }
    }
    tmp_i14 = param_1 + 0x3d4;
    tmp_i8 = COM_BitCheck(tmp_i14,0xb);
    if (tmp_i8 != 0) {
      tmp_i8 = ammoTableMP._792_4_;
      if ((*(byte *)(param_2 + 8) & 4) != 0) {
        tmp_i8 = ammoTableMP._792_4_ + 2;
      }
      if (bg_itemlist._56_4_ != 0) {
        tmp_pi13 = (int *)(bg_itemlist + 0x38);
        do {
          if ((tmp_pi13[9] == 1) && (tmp_pi13[10] == 0xb)) {
            tmp_i10 = tmp_pi13[0xd];
            goto LAB_0001819c;
          }
          tmp_pi13 = tmp_pi13 + 0xe;
        } while (*tmp_pi13 != 0);
      }
      tmp_i10 = 0;
LAB_0001819c:
      tmp_i10 = param_1 + tmp_i10 * 4;
      if (*(int *)(tmp_i10 + 0x290) < tmp_i8) {
        if (param_4 == 0) goto LAB_00017fde;
        tmp_i9 = *(int *)(tmp_i10 + 0x290) + param_4;
        if (tmp_i8 < tmp_i9) {
          tmp_b6 = true;
          *(int *)(tmp_i10 + 0x290) = tmp_i8;
          tmp_b15 = true;
        }
        else {
          *(int *)(tmp_i10 + 0x290) = tmp_i9;
          tmp_b6 = true;
          tmp_b15 = true;
        }
      }
    }
    tmp_i8 = COM_BitCheck(tmp_i14,0x2b);
    if (tmp_i8 != 0) {
      tmp_i8 = ammoTableMP._3096_4_;
      if ((*(byte *)(param_2 + 8) & 4) != 0) {
        tmp_i8 = ammoTableMP._3096_4_ + 2;
      }
      if (bg_itemlist._56_4_ != 0) {
        tmp_pi13 = (int *)(bg_itemlist + 0x38);
        do {
          if ((tmp_pi13[9] == 1) && (tmp_pi13[10] == 0x2b)) {
            tmp_i10 = tmp_pi13[0xd];
            goto LAB_0001824c;
          }
          tmp_pi13 = tmp_pi13 + 0xe;
        } while (*tmp_pi13 != 0);
      }
      tmp_i10 = 0;
LAB_0001824c:
      tmp_i10 = param_1 + tmp_i10 * 4;
      if (*(int *)(tmp_i10 + 0x290) < tmp_i8) {
        if (param_4 == 0) goto LAB_00017fde;
        tmp_i9 = *(int *)(tmp_i10 + 0x290) + param_4;
        if (tmp_i8 < tmp_i9) {
          tmp_b6 = true;
          *(int *)(tmp_i10 + 0x290) = tmp_i8;
          tmp_b15 = true;
        }
        else {
          *(int *)(tmp_i10 + 0x290) = tmp_i9;
          tmp_b6 = true;
          tmp_b15 = true;
        }
      }
    }
    tmp_i8 = COM_BitCheck(tmp_i14,0x2f);
    if (tmp_i8 != 0) {
      if (bg_itemlist._56_4_ != 0) {
        tmp_pi13 = (int *)(bg_itemlist + 0x38);
        do {
          if ((tmp_pi13[9] == 1) && (tmp_pi13[10] == 0x2f)) {
            tmp_i8 = tmp_pi13[0xd];
            goto LAB_000185d8;
          }
          tmp_pi13 = tmp_pi13 + 0xe;
        } while (*tmp_pi13 != 0);
      }
      tmp_i8 = 0;
LAB_000185d8:
      tmp_i8 = param_1 + tmp_i8 * 4;
      if (*(int *)(tmp_i8 + 0x290) < (int)ammoTableMP._3384_4_) {
        if (param_4 == 0) goto LAB_00017fde;
        tmp_i10 = *(int *)(tmp_i8 + 0x290) + param_4;
        if ((int)ammoTableMP._3384_4_ < tmp_i10) {
          tmp_b6 = true;
          *(uint32_t *)(tmp_i8 + 0x290) = ammoTableMP._3384_4_;
          tmp_b15 = true;
        }
        else {
          *(int *)(tmp_i8 + 0x290) = tmp_i10;
          tmp_b6 = true;
          tmp_b15 = true;
        }
      }
    }
    if (-1 < reloadableWeapons) {
      tmp_pi13 = &g_dat_00064944;
      tmp_i8 = reloadableWeapons;
      do {
        tmp_i10 = COM_BitCheck(tmp_i14,tmp_i8);
        if (tmp_i10 != 0) {
          tmp_i10 = BG_MaxAmmoForWeapon(tmp_i8,param_2);
          if (tmp_i8 == 6) {
            if (bg_itemlist._56_4_ != 0) {
              tmp_pi12 = (int *)(bg_itemlist + 0x38);
              do {
                if ((tmp_pi12[9] == 1) && (tmp_pi12[10] == 6)) {
                  tmp_i8 = tmp_pi12[0xc];
                  goto LAB_0001840f;
                }
                tmp_pi12 = tmp_pi12 + 0xe;
              } while (*tmp_pi12 != 0);
            }
            tmp_i8 = 0;
LAB_0001840f:
            tmp_i8 = param_1 + tmp_i8 * 4;
            if (*(int *)(tmp_i8 + 0x290) < tmp_i10) {
              if (param_4 == 0) goto LAB_00017fde;
              *(int *)(tmp_i8 + 0x290) = tmp_i10;
              tmp_b15 = true;
            }
          }
          else if (tmp_i8 == 5) {
            if (bg_itemlist._56_4_ != 0) {
              tmp_pi12 = (int *)(bg_itemlist + 0x38);
              do {
                if ((tmp_pi12[9] == 1) && (tmp_pi12[10] == 5)) {
                  tmp_i8 = tmp_pi12[0xc];
                  goto LAB_00018477;
                }
                tmp_pi12 = tmp_pi12 + 0xe;
              } while (*tmp_pi12 != 0);
            }
            tmp_i8 = 0;
LAB_00018477:
            tmp_i8 = param_1 + tmp_i8 * 4;
            if (*(int *)(tmp_i8 + 0x290) < tmp_i10) {
              if (param_4 == 0) goto LAB_00017fde;
              tmp_i9 = *(int *)(tmp_i8 + 0x290) + param_4;
              if (tmp_i9 < tmp_i10) {
                *(int *)(tmp_i8 + 0x290) = tmp_i9;
                goto LAB_0001839d;
              }
              *(int *)(tmp_i8 + 0x290) = tmp_i10;
              tmp_b15 = true;
            }
          }
          else {
            tmp_pi12 = (int *)(bg_itemlist + 0x38);
            tmp_i9 = bg_itemlist._56_4_;
            while (tmp_i9 != 0) {
              if ((tmp_pi12[9] == 1) && (tmp_i8 == tmp_pi12[10])) {
                tmp_i9 = tmp_pi12[0xc];
                goto LAB_00018343;
              }
              tmp_pi12 = tmp_pi12 + 0xe;
              tmp_i9 = *tmp_pi12;
            }
            tmp_i9 = 0;
LAB_00018343:
            tmp_i9 = param_1 + tmp_i9 * 4;
            if (*(int *)(tmp_i9 + 400) < tmp_i10) {
              if (param_4 == 0) goto LAB_00017fde;
              if ((tmp_i8 - 0x2cU < 2) || (tmp_i11 = param_4, tmp_i8 - 0x22U < 2)) {
                tmp_i11 = param_4 * 2;
              }
              tmp_i8 = tmp_i11 * *(int *)(ammoTableMP + tmp_i8 * 0x48 + 8) + *(int *)(tmp_i9 + 400);
              if (tmp_i10 < tmp_i8) {
                *(int *)(tmp_i9 + 400) = tmp_i10;
              }
              else {
                *(int *)(tmp_i9 + 400) = tmp_i8;
              }
LAB_0001839d:
              tmp_b15 = true;
            }
          }
        }
        tmp_i8 = *tmp_pi13;
        tmp_pi13 = tmp_pi13 + 1;
        if (tmp_i8 < 0) {
          return tmp_b15;
        }
      } while( true );
    }
  }
  else {
    tmp_pi13 = (int *)(bg_itemlist + 0x38);
    tmp_pi12 = tmp_pi13;
    do {
      if ((tmp_pi12[9] == 1) && (tmp_i8 == tmp_pi12[10])) {
        local_30 = tmp_pi12[0xd];
        goto LAB_00017fbe;
      }
      tmp_pi12 = tmp_pi12 + 0xe;
    } while (*tmp_pi12 != 0);
    local_30 = 0;
LAB_00017fbe:
    tmp_i10 = *(int *)(param_1 + (local_30 + 0xa4) * 4);
    if (tmp_i14 <= tmp_i10) {
LAB_00018083:
      do {
        while (tmp_pi13[9] == 1) {
          if (tmp_pi13[10] == 1) {
            tmp_i14 = tmp_pi13[0xd];
            tmp_i10 = *(int *)(param_1 + (tmp_i14 + 0xa4) * 4);
            goto LAB_0001809e;
          }
          tmp_pi13 = tmp_pi13 + 0xe;
          if (*tmp_pi13 == 0) goto LAB_00018092;
        }
        tmp_pi13 = tmp_pi13 + 0xe;
      } while (*tmp_pi13 != 0);
LAB_00018092:
      tmp_i10 = *(int *)(param_1 + 0x290);
      goto LAB_0001809c;
    }
LAB_00017fd2:
    if (param_4 != 0) {
      tmp_i9 = param_1 + local_30 * 4;
      *(int *)(tmp_i9 + 0x290) = tmp_i10 + param_4;
      COM_BitSet(param_1 + 0x3d4,tmp_i8);
      if (tmp_i14 < *(int *)(tmp_i9 + 0x290)) {
        *(int *)(tmp_i9 + 0x290) = tmp_i14;
      }
      if (bg_itemlist._56_4_ != 0) {
        tmp_b6 = true;
        tmp_b15 = true;
        tmp_pi13 = (int *)(bg_itemlist + 0x38);
        tmp_u7 = *(uint *)(param_2 + 0x10);
        goto LAB_00018083;
      }
      tmp_b15 = true;
      tmp_b6 = true;
      tmp_i14 = 0;
      tmp_i10 = *(int *)(param_1 + 0x290);
      tmp_u7 = *(uint *)(param_2 + 0x10);
      goto LAB_0001809e;
    }
LAB_00017fde:
    tmp_b6 = true;
  }
  return tmp_b6;
}

void BG_AddPathCorner(uint32_t param_1,uint32_t *param_2) {
  int tmp_i1;

  if (0x1ff < numPathCorners) {
    Com_Error(2,"MAX PATH CORNERS (%i) hit",0x200);
  }
  tmp_i1 = numPathCorners * 0x4c;
  *(uint32_t *)(pathCorners + tmp_i1 + 0x40) = *param_2;
  *(uint32_t *)(pathCorners + tmp_i1 + 0x44) = param_2[1];
  *(uint32_t *)(pathCorners + tmp_i1 + 0x48) = param_2[2];
  Q_strncpyz(pathCorners + tmp_i1,param_1,0x40);
  numPathCorners = numPathCorners + 1;
  return;
}

void BG_AddPredictableEventToPlayerstate(uint32_t param_1,uint32_t param_2,int param_3) {
  int tmp_i1;
  uint tmp_u2;

  tmp_u2 = *(uint *)(param_3 + 0x6c);
  tmp_i1 = param_3 + (tmp_u2 & 3) * 4;
  *(uint32_t *)(tmp_i1 + 0x70) = param_1;
  *(uint32_t *)(tmp_i1 + 0x80) = param_2;
  *(uint *)(param_3 + 0x6c) = tmp_u2 + 1;
  return;
}

void BG_AddSplineControl(int param_1,uint32_t param_2) {
  int tmp_i1;

  tmp_i1 = *(int *)(param_1 + 0x1c4);
  if (3 < tmp_i1) {
    Com_Error(2,"MAX SPLINE CONTROLS (%i) hit",4);
    tmp_i1 = *(int *)(param_1 + 0x1c4);
  }
  Q_strncpyz(param_1 + 0x94 + tmp_i1 * 0x4c,param_2,0x40);
  *(int *)(param_1 + 0x1c4) = *(int *)(param_1 + 0x1c4) + 1;
  return;
}

uint8_t * BG_AddSplinePath(uint32_t param_1,char *param_2,uint32_t *param_3) {
  uint tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint8_t *tmp_pu4;

  if (0x1ff < numSplinePaths) {
    Com_Error(2,"MAX SPLINES (%i) hit",0x200);
  }
  tmp_i2 = numSplinePaths;
  tmp_i3 = numSplinePaths * 0x394;
  tmp_pu4 = splinePaths + tmp_i3;
  tmp_u1 = 0;
  do {
    *(uint32_t *)(tmp_pu4 + tmp_u1) = 0;
    *(uint32_t *)(tmp_i3 + 0x312624 + tmp_u1) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x390);
  *(uint32_t *)(tmp_pu4 + tmp_u1) = 0;
  tmp_i3 = tmp_i2 * 0x394;
  *(uint32_t *)(splinePaths + tmp_i3 + 0x40) = *param_3;
  *(uint32_t *)(splinePaths + tmp_i3 + 0x44) = param_3[1];
  *(uint32_t *)(splinePaths + tmp_i3 + 0x48) = param_3[2];
  Q_strncpyz(tmp_pu4,param_1,0x40);
  if (param_2 == (char *)0x0) {
    param_2 = "";
  }
  tmp_i2 = tmp_i2 * 0x394;
  Q_strncpyz(tmp_i2 + 0x31266c,param_2,0x40);
  *(uint32_t *)(splinePaths + tmp_i2 + 0x1c4) = 0;
  numSplinePaths = numSplinePaths + 1;
  return tmp_pu4;
}

uint BG_AkimboFireSequence(int param_1,int param_2,int param_3) {
  uint tmp_u1;

  if ((((param_1 - 0x2cU < 2) || (tmp_u1 = 0, param_1 - 0x22U < 2)) && (tmp_u1 = 0, param_2 != 0)) &&
     (tmp_u1 = 1, param_3 != 0)) {
    return param_2 + param_3 & 1U ^ 1;
  }
  return tmp_u1;
}

uint32_t BG_AkimboSidearm(int param_1) {
  uint32_t tmp_u1;

  tmp_u1 = 0;
  if (param_1 - 0x22U < 0xc) {
    tmp_u1 = *(uint32_t *)(CSWTCH_85 + (param_1 - 0x22U) * 4);
  }
  return tmp_u1;
}

bool BG_BBoxCollision(float *param_1,float *param_2,float *param_3,float *param_4) {
  if ((((*param_1 <= *param_4) && (*param_3 <= *param_2)) && (param_1[1] <= param_4[1])) &&
     ((param_3[1] <= param_2[1] && (param_1[2] <= param_4[2])))) {
    return param_3[2] <= param_2[2];
  }
  return false;
}

void BG_BuildSplinePaths(void) {
  char *tmp_pc1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  char *tmp_pc4;
  int tmp_i5;
  long double tmp_l6;
  int local_34;
  char *local_30;
  int local_28;

  if (0 < numSplinePaths) {
    local_30 = splinePaths + 0x4c;
    local_28 = 0;
    tmp_i5 = numSplinePaths;
    do {
      if (*local_30 != '\0') {
        tmp_pc1 = local_30 + -0x4c;
        if (*(int *)(local_30 + 0x178) < 1) {
LAB_00017b17:
          tmp_pu3 = splinePaths;
          tmp_i5 = 0;
          do {
            tmp_i2 = Q_stricmp(tmp_pu3,local_30);
            if (tmp_i2 == 0) {
              *(uint8_t **)(local_30 + 0x40) = tmp_pu3;
              tmp_l6 = (long double)BG_SplineLength(tmp_pc1);
              *(float *)(local_30 + 0x33c) = (float)tmp_l6;
              BG_ComputeSegments(tmp_pc1);
              tmp_i5 = numSplinePaths;
              goto LAB_00017b72;
            }
            tmp_i5 = tmp_i5 + 1;
            tmp_pu3 = tmp_pu3 + 0x394;
          } while (tmp_i5 < numSplinePaths);
        }
        else {
          tmp_pc4 = local_30 + 0x48;
          local_34 = 0;
          do {
            if (0 < numPathCorners) {
              tmp_pu3 = pathCorners;
              tmp_i5 = 0;
              do {
                tmp_i2 = Q_stricmp(tmp_pu3,tmp_pc4);
                if (tmp_i2 == 0) {
                  *(uint32_t *)(tmp_pc4 + 0x40) = *(uint32_t *)(tmp_pu3 + 0x40);
                  *(uint32_t *)(tmp_pc4 + 0x44) = *(uint32_t *)(tmp_pu3 + 0x44);
                  *(uint32_t *)(tmp_pc4 + 0x48) = *(uint32_t *)(tmp_pu3 + 0x48);
                  goto LAB_00017af2;
                }
                tmp_i5 = tmp_i5 + 1;
                tmp_pu3 = tmp_pu3 + 0x4c;
              } while (tmp_i5 < numPathCorners);
            }
            Com_Printf("^1Cant find control point (%s) for spline (%s)\n",tmp_pc4,tmp_pc1);
LAB_00017af2:
            local_34 = local_34 + 1;
            tmp_pc4 = tmp_pc4 + 0x4c;
          } while (local_34 < *(int *)(local_30 + 0x178));
          if (0 < numSplinePaths) goto LAB_00017b17;
        }
        Com_Printf("^1Cant find target point (%s) for spline (%s)\n",local_30,tmp_pc1);
        tmp_i5 = numSplinePaths;
      }
LAB_00017b72:
      local_28 = local_28 + 1;
      local_30 = local_30 + 0x394;
    } while (local_28 < tmp_i5);
    if (0 < tmp_i5) {
      tmp_pu3 = splinePaths;
      tmp_i2 = 0;
      do {
        if (*(int *)(tmp_pu3 + 0x8c) != 0) {
          *(uint8_t **)(*(int *)(tmp_pu3 + 0x8c) + 0x90) = tmp_pu3;
        }
        tmp_i2 = tmp_i2 + 1;
        tmp_pu3 = tmp_pu3 + 0x394;
      } while (tmp_i2 != tmp_i5);
    }
  }
  return;
}

void BG_CalculateSpline_r(int param_1,float *param_2,uint32_t *param_3,float param_4) {
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float *pfVar4;
  int tmp_i5;
  int tmp_i7;
  float local_e4 [4];
  uint32_t local_d4;
  uint32_t local_d0;
  uint32_t local_cc;
  uint32_t local_c8;
  uint32_t local_c4;
  uint32_t local_c0;
  uint32_t local_bc;
  uint32_t local_b8;
  uint32_t local_b4;
  uint32_t local_b0;
  uint32_t local_ac;
  int tmp_i6;

  tmp_i5 = *(int *)(param_1 + 0x1c4);
  local_e4[0] = *(float *)(param_1 + 0x40);
  local_e4[1] = *(float *)(param_1 + 0x44);
  tmp_i6 = tmp_i5 + 2;
  local_e4[2] = *(float *)(param_1 + 0x48);
  if (tmp_i5 < 1) {
    tmp_i5 = 0;
  }
  else {
    local_e4[3] = (float)*(uint32_t *)(param_1 + 0xd4);
    local_d4 = *(uint32_t *)(param_1 + 0xd8);
    local_d0 = *(uint32_t *)(param_1 + 0xdc);
    if (tmp_i5 != 1) {
      local_cc = *(uint32_t *)(param_1 + 0x120);
      local_c8 = *(uint32_t *)(param_1 + 0x124);
      local_c4 = *(uint32_t *)(param_1 + 0x128);
      if (tmp_i5 != 2) {
        local_c0 = *(uint32_t *)(param_1 + 0x16c);
        local_bc = *(uint32_t *)(param_1 + 0x170);
        local_b8 = *(uint32_t *)(param_1 + 0x174);
        if (tmp_i5 != 3) {
          local_b4 = *(uint32_t *)(param_1 + 0x1b8);
          local_b0 = *(uint32_t *)(param_1 + 0x1bc);
          local_ac = *(uint32_t *)(param_1 + 0x1c0);
        }
      }
    }
  }
  tmp_i7 = *(int *)(param_1 + 0x8c);
  if (tmp_i7 != 0) {
    tmp_i5 = tmp_i5 * 3;
    local_e4[tmp_i5 + 3] = *(float *)(tmp_i7 + 0x40);
    local_e4[tmp_i5 + 4] = *(float *)(tmp_i7 + 0x44);
    local_e4[tmp_i5 + 5] = *(float *)(tmp_i7 + 0x48);
    if (2 < tmp_i6) {
      do {
        tmp_i5 = tmp_i6 + -1;
        tmp_i7 = 0;
        if (tmp_i5 != 2) {
          tmp_i7 = 0;
          pfVar4 = local_e4 + 3;
          tmp_f3 = local_e4[2];
          tmp_f2 = local_e4[1];
          tmp_f1 = local_e4[0];
          do {
            tmp_i7 = tmp_i7 + 2;
            pfVar4[-3] = (*pfVar4 - tmp_f1) * param_4 + tmp_f1;
            pfVar4[-2] = (pfVar4[1] - tmp_f2) * param_4 + tmp_f2;
            pfVar4[-1] = (pfVar4[2] - tmp_f3) * param_4 + tmp_f3;
            tmp_f1 = pfVar4[3];
            tmp_f2 = pfVar4[4];
            tmp_f3 = pfVar4[5];
            *pfVar4 = (tmp_f1 - *pfVar4) * param_4 + *pfVar4;
            pfVar4[1] = (tmp_f2 - pfVar4[1]) * param_4 + pfVar4[1];
            pfVar4[2] = (tmp_f3 - pfVar4[2]) * param_4 + pfVar4[2];
            pfVar4 = pfVar4 + 6;
          } while (tmp_i7 != (tmp_i6 - 4U & 0xfffffffe) + 2);
        }
        pfVar4 = local_e4 + tmp_i7 * 3 + 1;
        do {
          tmp_i7 = tmp_i7 + 1;
          pfVar4[-1] = (pfVar4[2] - pfVar4[-1]) * param_4 + pfVar4[-1];
          *pfVar4 = *pfVar4 + (pfVar4[3] - *pfVar4) * param_4;
          pfVar4[1] = pfVar4[1] + (pfVar4[4] - pfVar4[1]) * param_4;
          pfVar4 = pfVar4 + 3;
        } while (tmp_i7 < tmp_i5);
        tmp_i6 = tmp_i5;
      } while (tmp_i5 != 2);
    }
    *param_2 = local_e4[0];
    param_2[1] = local_e4[1];
    param_2[2] = local_e4[2];
    *param_3 = local_e4[3];
    param_3[1] = local_d4;
    param_3[2] = local_d0;
  }
  return;
}

uint BG_CanItemBeGrabbed(int param_1,int param_2,uint32_t param_3) {
  int tmp_i1;
  uint tmp_u2;
  int tmp_i3;
  int *tmp_pi4;
  int tmp_i5;

  tmp_i5 = *(int *)(param_1 + 0xa4);
  if ((tmp_i5 < 1) || (bg_numItems <= tmp_i5)) {
    Com_Error(2,"BG_CanItemBeGrabbed: index out of range");
    return 0;
  }
  switch(*(uint32_t *)(bg_itemlist + tmp_i5 * 0x38 + 0x24)) {
  case 0:
    Com_Error(2,"BG_CanItemBeGrabbed: IT_BAD");
    tmp_u2 = 0;
    break;
  case 1:
    if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x28) != 0xc) {
      return 1;
    }
    goto LAB_000189dd;
  case 2:
    tmp_i1 = *(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x28);
    if (tmp_i1 != 0xc) {
      tmp_i3 = *(int *)(param_2 + (tmp_i1 + 100) * 4);
      tmp_i1 = BG_MaxAmmoForWeapon(tmp_i1,param_3);
      if (tmp_i1 <= tmp_i3) {
        return 0;
      }
      tmp_i1 = 0;
      do {
        tmp_i3 = COM_BitCheck(param_2 + 0x3d4,tmp_i1);
        if (tmp_i3 != 0) {
          if (bg_itemlist._56_4_ != 0) {
            tmp_pi4 = (int *)(bg_itemlist + 0x38);
            do {
              if ((tmp_pi4[9] == 1) && (tmp_i1 == tmp_pi4[10])) {
                tmp_i3 = tmp_pi4[0xc];
                goto LAB_0001895b;
              }
              tmp_pi4 = tmp_pi4 + 0xe;
            } while (*tmp_pi4 != 0);
          }
          tmp_i3 = 0;
LAB_0001895b:
          if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x28) == tmp_i3) {
            return 1;
          }
        }
        tmp_i1 = tmp_i1 + 1;
        if (tmp_i1 == 0x34) {
          return 0;
        }
      } while( true );
    }
LAB_000189dd:
    tmp_u2 = BG_AddMagicAmmo();
    return tmp_u2;
  case 3:
    tmp_u2 = (uint)(*(int *)(param_2 + 0xd0) < *(int *)(param_2 + 0xf4));
    break;
  case 4:
    return 1;
  case 5:
    if (*(int *)(param_2 + 300) == 1) {
      if (*(int *)(param_1 + 0xf4) < 1) {
        return 0;
      }
      if (*(int *)(param_2 + 0x168) != 0) {
        return 0;
      }
      if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x2c) == 6) {
        return 1;
      }
      if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x2c) != 5) {
        return 0;
      }
    }
    else {
      if (*(int *)(param_2 + 300) != 2) {
        return 0;
      }
      if (*(int *)(param_1 + 0xf4) < 1) {
        return 0;
      }
      if (*(int *)(param_2 + 0x164) != 0) {
        return 0;
      }
      if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x2c) == 5) {
        return 1;
      }
      if (*(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x2c) != 6) {
        return 0;
      }
    }
    tmp_u2 = 0;
    if (*(int *)(param_1 + 0x90) != 0) {
      return 1;
    }
    break;
  case 6:
    tmp_i3 = tmp_i5 * 0x38;
    tmp_i1 = *(int *)(bg_itemlist + tmp_i3 + 0x2c);
    if (tmp_i1 == 7) {
      if (*(int *)(bg_itemlist + tmp_i3 + 0x20) == *(int *)(param_2 + 0x420)) {
        tmp_i5 = *(int *)(bg_itemlist + tmp_i3 + 0x30);
        tmp_i1 = *(int *)(param_2 + 300);
        if (((*(byte *)(param_2 + 0x6a) & 1) != 0) && (tmp_i5 == tmp_i1)) {
          return 1;
        }
      }
      else {
        tmp_i5 = *(int *)(bg_itemlist + tmp_i3 + 0x30);
        tmp_i1 = *(int *)(param_2 + 300);
      }
      if (tmp_i5 == tmp_i1) {
        return 0;
      }
      if (*(int *)(param_2 + 0x420) == 4) {
        return (uint)(*(int *)(param_2 + 0x16c) == 0);
      }
      return 0;
    }
    if (tmp_i1 == 3) {
      if ((*(byte *)(param_2 + 0x69) & 0x10) == 0) {
        return 0;
      }
    }
    else {
      if (tmp_i1 == 2) {
        tmp_i3 = *(int *)(param_2 + 0x158);
      }
      else {
        if (tmp_i1 != 0xc) goto LAB_000188c1;
        tmp_i3 = *(int *)(param_2 + 0x180);
      }
      if (tmp_i3 != 0) {
        return 0;
      }
    }
LAB_000188c1:
    tmp_u2 = (uint)(*(int *)(param_2 + (tmp_i1 + 0x54) * 4) !=
                  *(int *)(bg_itemlist + tmp_i5 * 0x38 + 0x20));
    break;
  default:
    return 0;
  }
  return tmp_u2;
}

bool BG_CheckCharge(int *param_1) {
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint tmp_u5;
  bool tmp_b6;
  int local_1c;
  int local_18;

  local_18 = 5;
  tmp_i1 = *param_1;
  tmp_u5 = *(int *)(tmp_i1 + 0xe4) - 1;
  if (tmp_u5 < 4) {
    local_18 = *(int *)(CSWTCH_90 + tmp_u5 * 4);
  }
  tmp_u5 = *(uint *)(tmp_i1 + 0xa4);
  if (((((((tmp_u5 != 0x12 && tmp_u5 != 0xf) && (tmp_u5 & 0xffffffef) != 5) &&
         (tmp_u5 & 0xffffffef) != 0xc) && 1 < tmp_u5 - 0x2a) && 3 < tmp_u5 - 0x30) && 1 < tmp_u5 - 0x24)
     && (1 < tmp_u5 - 0x19)) {
    return true;
  }
  switch(*(int *)(tmp_i1 + 0xe4)) {
  default:
    local_1c = param_1[0x15];
    break;
  case 1:
    local_1c = param_1[0x17];
    break;
  case 2:
    local_1c = param_1[0x16];
    break;
  case 3:
    local_1c = param_1[0x14];
    break;
  case 4:
    local_1c = param_1[0x18];
  }
  switch(tmp_u5) {
  case 5:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Panzer;
    if ((chargeCost_Panzer != g_dat_000644f8) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_dat_000644f8;
    }
    if ((g_dat_000644fc != g_dat_000644f8) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_dat_000644fc;
    }
    if ((g_dat_00064500 != g_dat_000644fc) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_dat_00064500;
    }
    if ((g_dat_00064504 != g_dat_00064500) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_dat_00064504;
    }
    tmp_b6 = g_dat_00064508 == g_dat_00064504;
    tmp_f3 = g_dat_00064508;
    if (!NAN(g_dat_00064508) && !NAN(g_dat_00064504)) {
LAB_00019940:
      if (tmp_b6) goto LAB_00019952;
    }
    break;
  default:
    return true;
  case 0xc:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Ammo;
    if ((chargeCost_Ammo != g_dat_00064540) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_dat_00064540;
    }
    if ((g_dat_00064544 != g_dat_00064540) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_dat_00064544;
    }
    if ((g_dat_00064548 != g_dat_00064544) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_dat_00064548;
    }
    if ((g_dat_0006454c != g_dat_00064548) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_dat_0006454c;
    }
    tmp_b6 = g_dat_00064550 == g_dat_0006454c;
    tmp_f3 = g_dat_00064550;
    if (!NAN(g_dat_00064550) && !NAN(g_dat_0006454c)) goto LAB_00019940;
    break;
  case 0xf:
  case 0x30:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Dynamite;
    if ((chargeCost_Dynamite != g_dat_000645b8) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_dat_000645b8;
    }
    if ((g_dat_000645bc != g_dat_000645b8) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_dat_000645bc;
    }
    if ((g_dat_000645c0 != g_dat_000645bc) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_dat_000645c0;
    }
    if ((g_dat_000645c4 != g_dat_000645c0) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_dat_000645c4;
    }
    tmp_b6 = g_dat_000645c8 == g_dat_000645c4;
    tmp_f3 = g_dat_000645c8;
    if (!NAN(g_dat_000645c8) && !NAN(g_dat_000645c4)) goto LAB_00019940;
    break;
  case 0x12:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Health;
    if ((chargeCost_Health != g_dat_00064558) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_dat_00064558;
    }
    if ((g_dat_0006455c != g_dat_00064558) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_dat_0006455c;
    }
    if ((g_dat_00064560 != g_dat_0006455c) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_dat_00064560;
    }
    if ((g_dat_00064564 != g_dat_00064560) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_dat_00064564;
    }
    tmp_b6 = g_dat_00064568 == g_dat_00064564;
    tmp_f3 = g_dat_00064568;
    if (!NAN(g_dat_00064568) && !NAN(g_dat_00064564)) goto LAB_00019940;
    break;
  case 0x15:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Artillery;
    if ((chargeCost_Artillery != g_dat_00064510) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_dat_00064510;
    }
    if ((g_dat_00064514 != g_dat_00064510) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_dat_00064514;
    }
    if ((g_dat_00064518 != g_dat_00064514) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_dat_00064518;
    }
    if ((g_dat_0006451c != g_dat_00064518) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_dat_0006451c;
    }
    tmp_b6 = g_dat_00064520 == g_dat_0006451c;
    tmp_f3 = g_dat_00064520;
    if (!NAN(g_dat_00064520) && !NAN(g_dat_0006451c)) goto LAB_00019940;
    break;
  case 0x19:
  case 0x33:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Landmine;
    if ((chargeCost_Landmine != g_dat_000645d0) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_dat_000645d0;
    }
    if ((g_dat_000645d4 != g_dat_000645d0) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_dat_000645d4;
    }
    if ((g_dat_000645d8 != g_dat_000645d4) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_dat_000645d8;
    }
    if ((g_dat_000645dc != g_dat_000645d8) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_dat_000645dc;
    }
    tmp_b6 = g_dat_000645e0 == g_dat_000645dc;
    tmp_f3 = g_dat_000645e0;
    if (!NAN(g_dat_000645e0) && !NAN(g_dat_000645dc)) goto LAB_00019940;
    break;
  case 0x1a:
  case 0x1c:
  case 0x32:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Satchel;
    if ((chargeCost_Satchel != g_dat_00064588) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_dat_00064588;
    }
    if ((g_dat_0006458c != g_dat_00064588) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_dat_0006458c;
    }
    if ((g_dat_00064590 != g_dat_0006458c) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_dat_00064590;
    }
    if ((g_dat_00064594 != g_dat_00064590) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_dat_00064594;
    }
    tmp_b6 = g_dat_00064598 == g_dat_00064594;
    tmp_f3 = g_dat_00064598;
    if (!NAN(g_dat_00064598) && !NAN(g_dat_00064594)) goto LAB_00019940;
    break;
  case 0x24:
  case 0x25:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Riflenade;
    if ((chargeCost_Riflenade != g_dat_000645a0) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_dat_000645a0;
    }
    if ((g_dat_000645a4 != g_dat_000645a0) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_dat_000645a4;
    }
    if ((g_dat_000645a8 != g_dat_000645a4) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_dat_000645a8;
    }
    if ((g_dat_000645ac != g_dat_000645a8) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_dat_000645ac;
    }
    tmp_b6 = g_dat_000645b0 == g_dat_000645ac;
    tmp_f3 = g_dat_000645b0;
    if (!NAN(g_dat_000645b0) && !NAN(g_dat_000645ac)) goto LAB_00019940;
    break;
  case 0x2a:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Mortar;
    if ((chargeCost_Mortar != g_dat_000644e0) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_dat_000644e0;
    }
    if ((g_dat_000644e4 != g_dat_000644e0) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_dat_000644e4;
    }
    if ((g_dat_000644e8 != g_dat_000644e4) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_dat_000644e8;
    }
    if ((g_dat_000644ec != g_dat_000644e8) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_dat_000644ec;
    }
    tmp_b6 = g_dat_000644f0 == g_dat_000644ec;
    tmp_f3 = g_dat_000644f0;
    if (!NAN(g_dat_000644f0) && !NAN(g_dat_000644ec)) goto LAB_00019940;
    break;
  case 0x2b:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Adrenaline;
    if ((chargeCost_Adrenaline != g_dat_00064528) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_dat_00064528;
    }
    if ((g_dat_0006452c != g_dat_00064528) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_dat_0006452c;
    }
    if ((g_dat_00064530 != g_dat_0006452c) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_dat_00064530;
    }
    if ((g_dat_00064534 != g_dat_00064530) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_dat_00064534;
    }
    tmp_b6 = g_dat_00064538 == g_dat_00064534;
    tmp_f3 = g_dat_00064538;
    if (!NAN(g_dat_00064538) && !NAN(g_dat_00064534)) goto LAB_00019940;
    break;
  case 0x31:
    tmp_f4 = (float)(param_1[3] - *(int *)(tmp_i1 + 0x478));
    tmp_u5 = param_1[local_18 + 0x49];
    tmp_f2 = chargeCost_Tripmine;
    if ((chargeCost_Tripmine != g_dat_000644c8) && ((tmp_u5 & 2) != 0)) {
      tmp_f2 = g_dat_000644c8;
    }
    if ((g_dat_000644cc != g_dat_000644c8) && ((tmp_u5 & 4) != 0)) {
      tmp_f2 = g_dat_000644cc;
    }
    if ((g_dat_000644d0 != g_dat_000644cc) && ((tmp_u5 & 8) != 0)) {
      tmp_f2 = g_dat_000644d0;
    }
    if ((g_dat_000644d4 != g_dat_000644d0) && ((tmp_u5 & 0x10) != 0)) {
      tmp_f2 = g_dat_000644d4;
    }
    tmp_b6 = g_dat_000644d8 == g_dat_000644d4;
    tmp_f3 = g_dat_000644d8;
    if (!NAN(g_dat_000644d8) && !NAN(g_dat_000644d4)) goto LAB_00019940;
  }
  if ((tmp_u5 & 0x20) != 0) {
    tmp_f2 = tmp_f3;
  }
LAB_00019952:
  return tmp_f2 * (float)local_1c <= tmp_f4;
}

void BG_ClipVelocity(float *param_1,float *param_2,float *param_3,float param_4) {
  float tmp_f1;

  tmp_f1 = param_1[2] * param_2[2] + param_1[1] * param_2[1] + *param_1 * *param_2;
  if (tmp_f1 < 0.0) {
    tmp_f1 = tmp_f1 * param_4;
  }
  else {
    tmp_f1 = tmp_f1 / param_4;
  }
  *param_3 = *param_1 - *param_2 * tmp_f1;
  param_3[1] = param_1[1] - param_2[1] * tmp_f1;
  param_3[2] = param_1[2] - tmp_f1 * param_2[2];
  return;
}

void BG_ComputeSegments(int param_1) {
  float tmp_f1;
  float tmp_f2;
  float *pfVar3;
  long double tmp_l4;
  int local_64;
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

  local_64 = 0;
  tmp_f1 = 0.0;
  pfVar3 = (float *)(param_1 + 0x1d4);
  do {
    tmp_f1 = tmp_f1 * 0.0625;
    BG_CalculateSpline_r(param_1,&local_4c,&local_40,tmp_f1);
    local_64 = local_64 + 1;
    pfVar3[-3] = (local_40 - local_4c) * tmp_f1 + local_4c;
    pfVar3[-2] = (local_3c - local_48) * tmp_f1 + local_48;
    pfVar3[-1] = (local_38 - local_44) * tmp_f1 + local_44;
    tmp_f1 = (float)local_64;
    tmp_f2 = tmp_f1 * 0.0625;
    BG_CalculateSpline_r(param_1,&local_34,&local_28,tmp_f2);
    local_4c = (local_28 - local_34) * tmp_f2 + local_34;
    local_48 = (local_24 - local_30) * tmp_f2 + local_30;
    local_44 = tmp_f2 * (local_20 - local_2c) + local_2c;
    *pfVar3 = local_4c - pfVar3[-3];
    pfVar3[1] = local_48 - pfVar3[-2];
    pfVar3[2] = local_44 - pfVar3[-1];
    tmp_l4 = (long double)VectorLength(pfVar3);
    pfVar3[3] = (float)tmp_l4;
    VectorNormalize(pfVar3);
    pfVar3 = pfVar3 + 7;
  } while (local_64 != 0x10);
  return;
}

void BG_CreateRotationMatrix(uint32_t param_1,int param_2) {
  AngleVectors(param_1,param_2,param_2 + 0xc,param_2 + 0x18);
  VectorInverse(param_2 + 0xc);
  return;
}

uint BG_DuplicateWeapon(uint param_1) {
  uint tmp_u1;

  if (param_1 == 0x25) {
    return 0x24;
  }
  if (param_1 < 0x26) {
    tmp_u1 = 4;
    if (param_1 != 9) {
      return param_1;
    }
  }
  else {
    tmp_u1 = 0x18;
    if ((param_1 != 0x27) && (tmp_u1 = 0x1e, param_1 != 0x28)) {
      return param_1;
    }
  }
  return tmp_u1;
}

void BG_EvaluateTrajectory(uint32_t *param_1,int param_2,float *param_3,int param_4,int param_5) {
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  bool tmp_b5;
  uint8_t *tmp_pu6;
  int tmp_i7;
  bool tmp_b8;
  long double tmp_l9;
  double tmp_d10;
  float tmp_f11;
  int local_54;
  float local_3c;
  uint8_t *local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;

  switch(*param_1) {
  case 0:
  case 1:
  case 9:
    *param_3 = (float)param_1[3];
    param_3[1] = (float)param_1[4];
    param_3[2] = (float)param_1[5];
    break;
  case 2:
    tmp_f3 = (float)(param_2 - param_1[1]) * 0.001;
    goto LAB_00016122;
  case 3:
    tmp_i7 = param_1[2] + param_1[1];
    if (param_2 <= tmp_i7) {
      tmp_i7 = param_2;
    }
    tmp_f11 = (float)(tmp_i7 - param_1[1]) * 0.001;
    tmp_f3 = 0.0;
    if (0.0 <= tmp_f11) {
      tmp_f3 = tmp_f11;
    }
    goto LAB_00016122;
  default:
    Com_Error(2,"BG_EvaluateTrajectory: unknown trType: %i",param_1[1]);
    break;
  case 5:
    tmp_d10 = ((double)(param_2 - param_1[1]) / (double)(int)param_1[2]) * 3.141592653589793;
    tmp_d10 = sin(tmp_d10 + tmp_d10);
    tmp_f3 = (float)tmp_d10;
LAB_00016122:
    *param_3 = (float)param_1[6] * tmp_f3 + (float)param_1[3];
    param_3[1] = (float)param_1[7] * tmp_f3 + (float)param_1[4];
    param_3[2] = tmp_f3 * (float)param_1[8] + (float)param_1[5];
    break;
  case 6:
  case 7:
    tmp_f3 = (float)(param_2 - param_1[1]) * 0.001;
    *param_3 = (float)param_1[6] * tmp_f3 + (float)param_1[3];
    param_3[1] = (float)param_1[7] * tmp_f3 + (float)param_1[4];
    param_3[2] = ((float)param_1[5] + tmp_f3 * (float)param_1[8]) - tmp_f3 * 0.0 * tmp_f3;
    break;
  case 8:
    tmp_f3 = (float)(param_2 - param_1[1]) * 0.001;
    *param_3 = (float)param_1[6] * tmp_f3 + (float)param_1[3];
    param_3[1] = (float)param_1[7] * tmp_f3 + (float)param_1[4];
    param_3[2] = ((float)param_1[8] * tmp_f3 + (float)param_1[5]) - tmp_f3 * 0.0;
    break;
  case 10:
    tmp_i7 = param_1[2] + param_1[1];
    if (param_2 <= tmp_i7) {
      tmp_i7 = param_2;
    }
    local_3c = (float)(tmp_i7 - param_1[1]) * 0.001;
    tmp_l9 = (long double)VectorLength(param_1 + 6);
    tmp_i7 = param_1[2];
    VectorNormalize2(param_1 + 6,param_3);
    local_3c = (float)(tmp_l9 / ((long double)tmp_i7 * (long double)0.001)) * 0.5 * local_3c * local_3c;
    *param_3 = local_3c * *param_3 + (float)param_1[3];
    param_3[1] = local_3c * param_3[1] + (float)param_1[4];
    param_3[2] = local_3c * param_3[2] + (float)param_1[5];
    break;
  case 0xb:
    tmp_i7 = param_1[2] + param_1[1];
    if (param_2 <= tmp_i7) {
      tmp_i7 = param_2;
    }
    local_3c = (float)(tmp_i7 - param_1[1]) * 0.001;
    tmp_l9 = (long double)VectorLength(param_1 + 6);
    tmp_i7 = param_1[2];
    VectorNormalize2(param_1 + 6,param_3);
    tmp_f3 = (float)param_1[7];
    tmp_f11 = (float)param_1[4];
    tmp_f1 = (float)param_1[8];
    tmp_f2 = (float)param_1[5];
    tmp_f4 = -(float)(tmp_l9 / ((long double)tmp_i7 * (long double)0.001)) * 0.5 * local_3c * local_3c;
    *param_3 = tmp_f4 * *param_3 + local_3c * (float)param_1[6] + (float)param_1[3];
    param_3[1] = tmp_f4 * param_3[1] + tmp_f3 * local_3c + tmp_f11;
    param_3[2] = tmp_f4 * param_3[2] + tmp_f1 * local_3c + tmp_f2;
    break;
  case 0xc:
    tmp_b8 = param_5 < 0;
    if (tmp_b8) {
      param_5 = -param_5;
    }
    param_5 = param_5 + -1;
    if (param_5 == -1) {
      return;
    }
    if (numSplinePaths <= param_5) {
      return;
    }
    local_38 = splinePaths + param_5 * 0x394;
    if ((param_1[2] == 0) ||
       (local_3c = (float)(param_2 - param_1[1]) / (float)(int)param_1[2], local_3c < 0.0)) {
      local_3c = 0.0;
    }
    else if (1.0 < local_3c) {
      local_3c = 1.0;
    }
    if (tmp_b8) {
      local_3c = 1.0 - local_3c;
    }
    tmp_f3 = local_3c;
    BG_CalculateSpline_r(local_38,&local_34,&local_28,local_3c);
    if (param_4 == 0) {
      *param_3 = (local_28 - local_34) * local_3c + local_34;
      param_3[1] = (local_24 - local_30) * local_3c + local_30;
      param_3[2] = (local_20 - local_2c) * local_3c + local_2c;
      return;
    }
    if ((float)param_1[3] == 0.0) {
LAB_00016050:
      *param_3 = local_28 - local_34;
      param_3[1] = local_24 - local_30;
      param_3[2] = local_20 - local_2c;
    }
    else {
      tmp_f11 = *(float *)(local_38 + 0x388);
      tmp_f3 = (float)param_1[3] / tmp_f11 + tmp_f3;
      tmp_pu6 = local_38;
      if (1.0 < tmp_f3) {
        tmp_pu6 = *(uint8_t **)(local_38 + 0x8c);
        tmp_f3 = tmp_f11 * (tmp_f3 - 1.0);
        if (tmp_pu6 != (uint8_t *)0x0) {
          tmp_f11 = *(float *)(tmp_pu6 + 0x388);
          while (tmp_f11 != 0.0) {
            tmp_f3 = tmp_f3 / tmp_f11;
            if (tmp_f3 <= 1.0) goto LAB_000166d0;
            tmp_pu6 = *(uint8_t **)(tmp_pu6 + 0x8c);
            tmp_f3 = (tmp_f3 - 1.0) * tmp_f11;
            if (tmp_pu6 == (uint8_t *)0x0) break;
            tmp_f11 = *(float *)(tmp_pu6 + 0x388);
          }
        }
        goto LAB_00016050;
      }
LAB_000166d0:
      if (tmp_f3 < 0.0) {
        tmp_f3 = tmp_f3 * tmp_f11;
        tmp_pu6 = *(uint8_t **)(tmp_pu6 + 0x90);
        if (tmp_pu6 != (uint8_t *)0x0) {
          tmp_f11 = *(float *)(tmp_pu6 + 0x388);
          while (tmp_f11 != 0.0) {
            tmp_f3 = 1.0 - -tmp_f3 / tmp_f11;
            if (0.0 <= tmp_f3) goto LAB_0001675a;
            tmp_f3 = tmp_f3 * tmp_f11;
            tmp_pu6 = *(uint8_t **)(tmp_pu6 + 0x90);
            if (tmp_pu6 == (uint8_t *)0x0) break;
            tmp_f11 = *(float *)(tmp_pu6 + 0x388);
          }
        }
        goto LAB_00016050;
      }
LAB_0001675a:
      *param_3 = (local_28 - local_34) * local_3c + local_34;
      param_3[1] = (local_24 - local_30) * local_3c + local_30;
      param_3[2] = (local_20 - local_2c) * local_3c + local_2c;
      BG_CalculateSpline_r(tmp_pu6,&local_34,&local_28,tmp_f3);
      local_34 = (local_28 - local_34) * tmp_f3 + local_34;
      local_30 = (local_24 - local_30) * tmp_f3 + local_30;
      local_2c = (local_20 - local_2c) * tmp_f3 + local_2c;
      if ((float)param_1[3] < 0.0) {
        *param_3 = *param_3 - local_34;
        param_3[1] = param_3[1] - local_30;
        param_3[2] = param_3[2] - local_2c;
      }
      else {
        *param_3 = local_34 - *param_3;
        param_3[1] = local_30 - param_3[1];
        param_3[2] = local_2c - param_3[2];
      }
    }
    vectoangles(param_3,param_3);
    tmp_f3 = (float)param_1[4];
    if ((10000.0 <= tmp_f3) || (tmp_f3 < -10000.0)) {
      if (tmp_f3 < 0.0) {
        tmp_f3 = tmp_f3 + 10000.0;
        tmp_b5 = true;
        tmp_b8 = true;
      }
      else {
        tmp_f3 = tmp_f3 - 10000.0;
        tmp_b5 = true;
        tmp_b8 = true;
      }
    }
    else {
      tmp_b5 = false;
      tmp_b8 = false;
    }
    if ((1000.0 <= tmp_f3) || (tmp_f3 < -1000.0)) {
      if (tmp_f3 < 0.0) {
        tmp_f3 = tmp_f3 + 1000.0;
      }
      else {
        tmp_f3 = tmp_f3 - 1000.0;
      }
      if (tmp_b5) {
        tmp_d10 = sin((double)(((local_3c + local_3c) - 1.0) * 3.1415927 * 0.5));
        param_3[2] = tmp_f3 + ((float)tmp_d10 + 1.0) * 0.5 * (float)param_1[5];
        return;
      }
      if (!tmp_b8) {
        tmp_d10 = sin((double)((1.0 - local_3c) * 3.1415927 * 0.5));
        param_3[2] = tmp_f3 + (1.0 - (float)tmp_d10) * (float)param_1[5];
        return;
      }
    }
    else if (!tmp_b8) {
      param_3[2] = (float)param_1[5] * local_3c + tmp_f3;
      return;
    }
    tmp_d10 = sin((double)local_3c * 3.141592653589793 * 0.5);
    param_3[2] = tmp_f3 + (float)tmp_d10 * (float)param_1[5];
    break;
  case 0xd:
    tmp_b8 = param_5 < 0;
    if (tmp_b8) {
      param_5 = -param_5;
    }
    param_5 = param_5 + -1;
    if ((param_5 != -1) && (param_5 < numSplinePaths)) {
      local_38 = splinePaths + param_5 * 0x394;
      if ((param_1[2] == 0) ||
         (local_3c = (float)(param_2 - param_1[1]) / (float)(int)param_1[2], local_3c < 0.0)) {
        local_3c = 0.0;
      }
      else if (1.0 < local_3c) {
        local_3c = 1.0;
      }
      if (tmp_b8) {
        local_3c = 1.0 - local_3c;
      }
      if (param_4 == 0) {
        tmp_f3 = local_3c * 16.0;
        tmp_f11 = floorf(tmp_f3);
        tmp_i7 = (int)ROUND(tmp_f11);
        if (tmp_i7 < 0x10) {
          tmp_f3 = (tmp_f3 - (float)tmp_i7) *
                  *(float *)(splinePaths + tmp_i7 * 0x1c + param_5 * 0x394 + 0x1e0);
        }
        else {
          tmp_f3 = *(float *)(splinePaths + param_5 * 0x394 + 900);
          tmp_i7 = 0xf;
        }
        tmp_i7 = param_5 * 0x394 + tmp_i7 * 0x1c;
        *param_3 = *(float *)(splinePaths + tmp_i7 + 0x1d4) * tmp_f3 +
                   *(float *)(splinePaths + tmp_i7 + 0x1c8);
        param_3[1] = *(float *)(splinePaths + tmp_i7 + 0x1d8) * tmp_f3 +
                     *(float *)(splinePaths + tmp_i7 + 0x1cc);
        param_3[2] = tmp_f3 * *(float *)(splinePaths + tmp_i7 + 0x1dc) +
                     *(float *)(splinePaths + tmp_i7 + 0x1d0);
      }
      else {
        tmp_f3 = local_3c * 16.0;
        tmp_f11 = floorf(tmp_f3);
        local_54 = (int)ROUND(tmp_f11);
        if (local_54 < 0x10) {
          tmp_f3 = (tmp_f3 - (float)local_54) *
                  *(float *)(splinePaths + local_54 * 0x1c + param_5 * 0x394 + 0x1e0);
        }
        else {
          tmp_f3 = *(float *)(splinePaths + param_5 * 0x394 + 900);
          local_54 = 0xf;
        }
        if ((float)param_1[3] == 0.0) {
          vectoangles(local_54 * 0x1c + param_5 * 0x394 + 0x3127f4,param_3);
        }
        else {
          tmp_i7 = local_54 * 0x1c + param_5 * 0x394;
          local_34 = *(float *)(splinePaths + tmp_i7 + 0x1d4) * tmp_f3 +
                     *(float *)(splinePaths + tmp_i7 + 0x1c8);
          *param_3 = local_34;
          local_30 = *(float *)(splinePaths + tmp_i7 + 0x1d8) * tmp_f3 +
                     *(float *)(splinePaths + tmp_i7 + 0x1cc);
          param_3[1] = local_30;
          local_2c = tmp_f3 * *(float *)(splinePaths + tmp_i7 + 0x1dc) +
                     *(float *)(splinePaths + tmp_i7 + 0x1d0);
          param_3[2] = local_2c;
          BG_LinearPathOrigin2(param_1[3],&local_38,&local_3c,&local_34,tmp_b8);
          if ((float)param_1[3] < 0.0) {
            *param_3 = local_34 - *param_3;
            param_3[1] = local_30 - param_3[1];
            param_3[2] = local_2c - param_3[2];
          }
          else {
            *param_3 = *param_3 - local_34;
            param_3[1] = param_3[1] - local_30;
            param_3[2] = param_3[2] - local_2c;
          }
          vectoangles(param_3,param_3);
        }
      }
    }
  }
  return;
}

void BG_EvaluateTrajectoryDelta(uint32_t *param_1,int param_2,float *param_3) {
  int tmp_i1;
  float tmp_f2;
  double tmp_d3;

  switch(*param_1) {
  case 0:
  case 1:
  case 0xc:
  case 0xd:
    goto _L566;
  case 2:
    *param_3 = (float)param_1[6];
    param_3[1] = (float)param_1[7];
    param_3[2] = (float)param_1[8];
    break;
  case 3:
    if (param_2 <= (int)(param_1[2] + param_1[1])) {
      *param_3 = (float)param_1[6];
      param_3[1] = (float)param_1[7];
      param_3[2] = (float)param_1[8];
      return;
    }
    goto _L566;
  default:
    Com_Error(2,"BG_EvaluateTrajectoryDelta: unknown trType: %i",param_1[1]);
    break;
  case 5:
    tmp_d3 = ((double)(param_2 - param_1[1]) / (double)(int)param_1[2]) * 3.141592653589793;
    tmp_d3 = cos(tmp_d3 + tmp_d3);
    tmp_f2 = (float)tmp_d3 * 0.5;
LAB_000169d6:
    *param_3 = (float)param_1[6] * tmp_f2;
    param_3[1] = (float)param_1[7] * tmp_f2;
    param_3[2] = tmp_f2 * (float)param_1[8];
    return;
  case 6:
    tmp_i1 = param_1[1];
    *param_3 = (float)param_1[6];
    param_3[1] = (float)param_1[7];
    param_3[2] = (float)param_1[8] - (float)(param_2 - tmp_i1) * 0.001 * 0.0;
    break;
  case 7:
    tmp_i1 = param_1[1];
    *param_3 = (float)param_1[6];
    param_3[1] = (float)param_1[7];
    param_3[2] = (float)param_1[8] - (float)(param_2 - tmp_i1) * 0.001 * 0.0;
    break;
  case 8:
    tmp_i1 = param_1[1];
    *param_3 = (float)param_1[6];
    param_3[1] = (float)param_1[7];
    param_3[2] = (float)param_1[8] - (float)(param_2 - tmp_i1) * 0.001 * 0.0;
    break;
  case 10:
    if (param_2 <= (int)(param_1[2] + param_1[1])) {
      tmp_f2 = (float)(param_2 - param_1[1]) * 0.001;
      tmp_f2 = tmp_f2 * tmp_f2;
      goto LAB_000169d6;
    }
    goto _L566;
  case 0xb:
    if (param_2 <= (int)(param_1[2] + param_1[1])) {
      tmp_f2 = (float)(param_2 - param_1[1]) * 0.001;
      goto LAB_000169d6;
    }
_L566:
    param_3[2] = 0.0;
    param_3[1] = 0.0;
    *param_3 = 0.0;
  }
  return;
}

int BG_FindAmmoForWeapon(int param_1) {
  int *tmp_pi1;

  if (bg_itemlist._56_4_ != 0) {
    tmp_pi1 = (int *)(bg_itemlist + 0x38);
    do {
      if ((tmp_pi1[9] == 1) && (tmp_pi1[10] == param_1)) {
        return tmp_pi1[0xc];
      }
      tmp_pi1 = tmp_pi1 + 0xe;
    } while (*tmp_pi1 != 0);
  }
  return 0;
}

int BG_FindClipForWeapon(int param_1) {
  int *tmp_pi1;

  if (bg_itemlist._56_4_ != 0) {
    tmp_pi1 = (int *)(bg_itemlist + 0x38);
    do {
      if ((tmp_pi1[9] == 1) && (tmp_pi1[10] == param_1)) {
        return tmp_pi1[0xd];
      }
      tmp_pi1 = tmp_pi1 + 0xe;
    } while (*tmp_pi1 != 0);
  }
  return 0;
}

int * BG_FindItem(uint32_t param_1) {
  int tmp_i1;
  int *tmp_pi2;

  tmp_pi2 = (int *)(bg_itemlist + 0x38);
  tmp_i1 = bg_itemlist._56_4_;
  while( true ) {
    if (tmp_i1 == 0) {
      return (int *)0x0;
    }
    tmp_i1 = Q_stricmp(tmp_pi2[7],param_1);
    if (tmp_i1 == 0) break;
    tmp_pi2 = tmp_pi2 + 0xe;
    tmp_i1 = *tmp_pi2;
  }
  return tmp_pi2;
}

int * BG_FindItemForClassName(uint32_t param_1) {
  int tmp_i1;
  int *tmp_pi2;

  tmp_pi2 = (int *)(bg_itemlist + 0x38);
  tmp_i1 = bg_itemlist._56_4_;
  while( true ) {
    if (tmp_i1 == 0) {
      return (int *)0x0;
    }
    tmp_i1 = Q_stricmp(tmp_i1,param_1);
    if (tmp_i1 == 0) break;
    tmp_pi2 = tmp_pi2 + 0xe;
    tmp_i1 = *tmp_pi2;
  }
  return tmp_pi2;
}

int * BG_FindItemForWeapon(int param_1) {
  int *tmp_pi1;
  char *tmp_pc2;

  if (param_1 == 0) {
    return (int *)0x0;
  }
  if (bg_itemlist._56_4_ != 0) {
    tmp_pi1 = (int *)(bg_itemlist + 0x38);
    do {
      if ((tmp_pi1[9] == 1) && (tmp_pi1[10] == param_1)) {
        return tmp_pi1;
      }
      tmp_pi1 = tmp_pi1 + 0xe;
    } while (*tmp_pi1 != 0);
  }
  if (param_1 - 1U < 0x33) {
    tmp_pc2 = (char *)(param_1 * 0x6b0 + 0x2f7fd4);
  }
  else {
    tmp_pc2 = "^1invalid";
  }
  Com_Printf("^1ERROR : ^7BG_FindItemForWeapon() ^9no item for weapon %i (%s^9)\n",param_1,tmp_pc2);
  return (int *)0x0;
}

uint8_t * BG_Find_PathCorner(uint32_t param_1) {
  int tmp_i1;
  uint8_t *tmp_pu2;
  int tmp_i3;

  if (0 < numPathCorners) {
    tmp_pu2 = pathCorners;
    tmp_i3 = 0;
    do {
      tmp_i1 = Q_stricmp(tmp_pu2,param_1);
      if (tmp_i1 == 0) {
        return tmp_pu2;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu2 = tmp_pu2 + 0x4c;
    } while (tmp_i3 < numPathCorners);
  }
  return (uint8_t *)0x0;
}

uint8_t * BG_Find_Spline(uint32_t param_1) {
  int tmp_i1;
  uint8_t *tmp_pu2;
  int tmp_i3;

  if (0 < numSplinePaths) {
    tmp_pu2 = splinePaths;
    tmp_i3 = 0;
    do {
      tmp_i1 = Q_stricmp(tmp_pu2,param_1);
      if (tmp_i1 == 0) {
        return tmp_pu2;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu2 = tmp_pu2 + 0x394;
    } while (tmp_i3 < numSplinePaths);
  }
  return (uint8_t *)0x0;
}

uint32_t BG_FootstepForSurface(uint param_1) {
  uint32_t tmp_u1;

  tmp_u1 = 9;
  if ((((((param_1 & 0x2000) == 0) && (tmp_u1 = 1, (param_1 & 0x1000) == 0)) &&
       (tmp_u1 = 2, (param_1 & 0x40000) == 0)) &&
      ((tmp_u1 = 3, (param_1 & 0x80000) == 0 && (tmp_u1 = 4, (param_1 & 0x100000) == 0)))) &&
     ((tmp_u1 = 6, (param_1 & 0x800000) == 0 &&
      ((tmp_u1 = 7, (param_1 & 0x400000) == 0 && (tmp_u1 = 8, (param_1 & 0x2000000) == 0)))))) {
    tmp_u1 = 0;
    if ((param_1 & 0x40) != 0) {
      tmp_u1 = 5;
    }
    return tmp_u1;
  }
  return tmp_u1;
}

void BG_GetFromTable(int param_1) {
  if (*(float *)(param_1 + 0x14) != *(float *)(param_1 + 0x10)) {
    return;
  }
  return;
}

uint8_t * BG_GetLocationString(float *param_1) {
  int tmp_i1;
  int tmp_i2;

  coord_7557 = 0;
  tmp_i1 = (int)ROUND((*param_1 - locInfo) / g_dat_0006c108);
  tmp_i2 = (int)ROUND((g_dat_0006c104 - param_1[1]) / g_dat_0006c10c);
  if (tmp_i2 < 0) {
    tmp_i2 = 0;
  }
  if (tmp_i1 < 0) {
    tmp_i1 = 0;
  }
  Com_sprintf(&coord_7557,6,"%c,%i",tmp_i1 + 0x41,tmp_i2);
  return &coord_7557;
}

void BG_GetMarkDir(float *param_1,int param_2,float *param_3) {
  int tmp_i1;
  long double tmp_l2;
  float local_44;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;

  if ((*param_1 < 0.001) && (param_1[1] < 0.001)) {
    *param_3 = *param_1;
    param_3[1] = param_1[1];
    param_3[2] = param_1[2];
    return;
  }
  tmp_l2 = (long double)VectorLengthSquared(param_2);
  if (tmp_l2 < (long double)1) {
    local_28 = 0.0;
    local_24 = 0.0;
    local_20 = 1.0;
  }
  else {
    VectorNormalize2(param_2,&local_28);
  }
  local_34 = -*param_1;
  local_30 = -param_1[1];
  local_2c = -param_1[2];
  VectorNormalize(&local_34);
  if (*(float *)(param_2 + 8) <= 0.8) {
    local_44 = 0.3;
  }
  else {
    local_44 = 0.7;
  }
  tmp_i1 = 0;
  if (local_2c * local_20 + local_30 * local_24 + local_34 * local_28 < local_44) {
    do {
      tmp_i1 = tmp_i1 + 1;
      local_34 = local_34 + local_28 * 0.5;
      local_30 = local_24 * 0.5 + local_30;
      local_2c = local_20 * 0.5 + local_2c;
      VectorNormalize(&local_34);
      if (local_44 <= local_2c * local_20 + local_30 * local_24 + local_34 * local_28) break;
    } while (tmp_i1 != 10);
  }
  *param_3 = local_34;
  param_3[1] = local_30;
  param_3[2] = local_2c;
  return;
}

byte BG_GetPrimaryWeaponForPlayerState(int param_1) {
  int tmp_i1;
  byte tmp_b2;

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
  return tmp_b2;
}

uint8_t * BG_GetSplineData(int param_1,uint *param_2) {
  bool tmp_b1;

  tmp_b1 = param_1 < 0;
  if (tmp_b1) {
    param_1 = -param_1;
  }
  param_1 = param_1 + -1;
  *param_2 = (uint)tmp_b1;
  if ((param_1 != -1) && (param_1 < numSplinePaths)) {
    return splinePaths + param_1 * 0x394;
  }
  return (uint8_t *)0x0;
}

char BG_GrenadeTypeForTeam(int param_1) {
  if (param_1 != 1) {
    return (param_1 == 2) * '\t';
  }
  return '\x04';
}

int BG_GrenadesForClass(int param_1,int param_2) {
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint tmp_u5;
  float tmp_f6;
  int tmp_i7;

  tmp_i7 = 5;
  if (param_1 - 1U < 4) {
    tmp_i7 = *(int *)(CSWTCH_90 + (param_1 - 1U) * 4);
  }
  tmp_u5 = *(uint *)(param_2 + 0x10);
  tmp_f6 = (float)jP_GrenadesPerLevel._96_4_;
  if (((float)jP_GrenadesPerLevel._96_4_ != (float)jP_GrenadesPerLevel._100_4_) &&
     ((tmp_u5 & 2) != 0)) {
    tmp_f6 = (float)jP_GrenadesPerLevel._100_4_;
  }
  if (((float)jP_GrenadesPerLevel._104_4_ != (float)jP_GrenadesPerLevel._100_4_) &&
     ((tmp_u5 & 4) != 0)) {
    tmp_f6 = (float)jP_GrenadesPerLevel._104_4_;
  }
  if (((float)jP_GrenadesPerLevel._108_4_ != (float)jP_GrenadesPerLevel._104_4_) &&
     ((tmp_u5 & 8) != 0)) {
    tmp_f6 = (float)jP_GrenadesPerLevel._108_4_;
  }
  if (((float)jP_GrenadesPerLevel._112_4_ != (float)jP_GrenadesPerLevel._108_4_) &&
     ((tmp_u5 & 0x10) != 0)) {
    tmp_f6 = (float)jP_GrenadesPerLevel._112_4_;
  }
  if (((float)jP_GrenadesPerLevel._116_4_ != (float)jP_GrenadesPerLevel._112_4_) &&
     ((tmp_u5 & 0x20) != 0)) {
    tmp_f6 = (float)jP_GrenadesPerLevel._116_4_;
  }
  tmp_i1 = tmp_i7 * 0x18;
  tmp_f2 = *(float *)(jP_GrenadesPerLevel + tmp_i1);
  tmp_f3 = *(float *)(jP_GrenadesPerLevel + tmp_i1 + 4);
  tmp_u5 = *(uint *)(param_2 + tmp_i7 * 4);
  if ((tmp_f3 != tmp_f2) && ((tmp_u5 & 2) != 0)) {
    tmp_f2 = tmp_f3;
  }
  tmp_f4 = *(float *)(jP_GrenadesPerLevel + tmp_i1 + 8);
  if ((tmp_f4 != tmp_f3) && ((tmp_u5 & 4) != 0)) {
    tmp_f2 = tmp_f4;
  }
  tmp_f3 = *(float *)(jP_GrenadesPerLevel + tmp_i1 + 0xc);
  if ((tmp_f3 != tmp_f4) && ((tmp_u5 & 8) != 0)) {
    tmp_f2 = tmp_f3;
  }
  tmp_f4 = *(float *)(jP_GrenadesPerLevel + tmp_i1 + 0x10);
  if ((tmp_f4 != tmp_f3) && ((tmp_u5 & 0x10) != 0)) {
    tmp_f2 = tmp_f4;
  }
  if ((*(float *)(jP_GrenadesPerLevel + tmp_i1 + 0x14) != tmp_f4) && ((tmp_u5 & 0x20) != 0)) {
    tmp_f2 = *(float *)(jP_GrenadesPerLevel + tmp_i1 + 0x14);
  }
  return (int)ROUND(tmp_f6) + (int)ROUND(tmp_f2);
}

void BG_InitLocations(float *param_1,float *param_2) {
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;

  g_dat_0006c108 = 1200.0;
  tmp_f2 = *param_2 - *param_1;
  tmp_f1 = tmp_f2 / 1200.0;
  while (tmp_f1 < 7.0) {
    g_dat_0006c108 = g_dat_0006c108 - 50.0;
    tmp_f1 = tmp_f2 / g_dat_0006c108;
  }
  tmp_f2 = param_1[1] - param_2[1];
  g_dat_0006c10c = 1200.0;
  tmp_f3 = tmp_f2 / 1200.0;
  while (tmp_f3 < 7.0) {
    g_dat_0006c10c = g_dat_0006c10c - 50.0;
    tmp_f3 = tmp_f2 / g_dat_0006c10c;
  }
  locInfo = (tmp_f1 - (float)(int)ROUND(tmp_f1)) * g_dat_0006c108 * 0.5 + *param_1;
  g_dat_0006c104 = param_1[1] - (tmp_f3 - (float)(int)ROUND(tmp_f3)) * g_dat_0006c10c * 0.5;
  return;
}

bool BG_IsAkimboSideArm(int param_1,int param_2) {
  if (param_1 == 2) {
    return *(int *)(param_2 + 0xa4) == 0x23 || *(int *)(param_2 + 0xa4) == 0x2d;
  }
  if (param_1 == 7) {
    return *(int *)(param_2 + 0xa4) == 0x22 || *(int *)(param_2 + 0xa4) == 0x2c;
  }
  return false;
}

bool BG_IsAkimboWeapon(int param_1) {
  return param_1 - 0x22U < 2 || param_1 - 0x2cU < 2;
}

bool BG_IsScopedWeapon(int param_1) {
  return param_1 - 0x27U < 3;
}

void BG_LinearPathOrigin2(float param_1,int *param_2,float *param_3,float *param_4) {
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  bool tmp_b7;
  int tmp_i8;
  int tmp_i9;
  bool tmp_b10;
  float tmp_f11;
  float tmp_f12;

  tmp_f4 = *param_3;
  tmp_f11 = floorf(tmp_f4 * 16.0);
  tmp_i8 = (int)ROUND(tmp_f11);
  if (tmp_i8 < 0x10) {
    tmp_f4 = tmp_f4 * 16.0 - (float)tmp_i8;
  }
  else {
    tmp_i8 = 0xf;
    tmp_f4 = 1.0;
  }
  tmp_b10 = true;
  tmp_i9 = *param_2;
  do {
    tmp_i3 = tmp_i8 * 0x1c;
    tmp_i1 = tmp_i9 + 0x1c0 + tmp_i3;
    tmp_i2 = tmp_i9 + 0x1c4 + tmp_i3;
    tmp_f5 = *(float *)(tmp_i1 + 8) - *param_4;
    tmp_i3 = tmp_i9 + 0x1c8 + tmp_i3;
    tmp_f12 = *(float *)(tmp_i2 + 8) - param_4[1];
    tmp_f11 = *(float *)(tmp_i3 + 8) - param_4[2];
    tmp_f6 = *(float *)(tmp_i3 + 0x14) * tmp_f11 +
            *(float *)(tmp_i2 + 0x14) * tmp_f12 + *(float *)(tmp_i1 + 0x14) * tmp_f5;
    tmp_f6 = tmp_f6 + tmp_f6;
    tmp_f11 = tmp_f6 * tmp_f6 -
             ((tmp_f11 * tmp_f11 + tmp_f12 * tmp_f12 + tmp_f5 * tmp_f5) - param_1 * param_1) * 4.0;
    if (tmp_f11 < 0.0) {
LAB_0001588c:
      if (param_1 < 0.0) goto LAB_00015a10;
      tmp_i8 = tmp_i8 + 1;
      if (tmp_i8 == 0x10) {
        tmp_i8 = 0;
        if (0.0 <= param_1) {
          tmp_i9 = *(int *)(tmp_i9 + 0x8c);
          if (tmp_i9 == 0) {
            return;
          }
          tmp_i8 = 0;
          *param_2 = tmp_i9;
          goto LAB_000158be;
        }
        goto LAB_00015a1c;
      }
    }
    else {
      tmp_f12 = SQRT(tmp_f11);
      if (NAN(tmp_f12)) {
        tmp_f12 = sqrtf(tmp_f11);
      }
      tmp_i9 = *param_2;
      tmp_f11 = *(float *)(tmp_i9 + 0x1e0 + tmp_i8 * 0x1c);
      tmp_f5 = ((tmp_f12 - tmp_f6) * 0.5) / tmp_f11;
      tmp_f11 = ((-tmp_f6 - tmp_f12) * 0.5) / tmp_f11;
      if (!tmp_b10) {
        if (param_1 < 0.0) {
          tmp_b10 = tmp_f11 < tmp_f5;
        }
        else {
          tmp_b10 = tmp_f5 < tmp_f11;
        }
        tmp_b7 = 0.0 <= tmp_f5;
        if (tmp_f5 <= 1.0 && ((!tmp_b10 && tmp_f5 != tmp_f11) && tmp_b7)) {
          tmp_b10 = true;
        }
        else {
          tmp_b10 = tmp_f11 <= 1.0;
          tmp_b7 = 0.0 <= tmp_f11;
          tmp_f5 = tmp_f11;
        }
LAB_00015860:
        if ((tmp_b7) && (tmp_b10)) {
          tmp_i9 = tmp_i8 * 0x1c;
          *param_3 = tmp_f5 * 0.0625 + (float)tmp_i8 * 0.0625;
          tmp_i8 = *param_2;
          *param_4 = *(float *)(tmp_i8 + 0x1e0 + tmp_i9) * tmp_f5 * *(float *)(tmp_i8 + 0x1d4 + tmp_i9) +
                     *(float *)(tmp_i8 + 0x1c8 + tmp_i9);
          tmp_i8 = *param_2;
          param_4[1] = *(float *)(tmp_i8 + 0x1e0 + tmp_i9) * tmp_f5 * *(float *)(tmp_i8 + 0x1d8 + tmp_i9)
                       + *(float *)(tmp_i8 + 0x1cc + tmp_i9);
          tmp_i8 = *param_2;
          param_4[2] = tmp_f5 * *(float *)(tmp_i8 + 0x1e0 + tmp_i9) * *(float *)(tmp_i8 + 0x1dc + tmp_i9)
                       + *(float *)(tmp_i8 + 0x1d0 + tmp_i9);
          return;
        }
        goto LAB_0001588c;
      }
      if (0.0 <= param_1) {
        tmp_b7 = 0.0 <= tmp_f5;
        if (1.0 < tmp_f5 || (tmp_f5 <= tmp_f4 || !tmp_b7)) {
          if (tmp_f4 < tmp_f11) goto LAB_00015824;
          goto LAB_0001588c;
        }
        tmp_b10 = true;
        goto LAB_00015860;
      }
      tmp_b7 = 0.0 <= tmp_f5;
      if (tmp_f5 <= 1.0 && (tmp_f5 < tmp_f4 && tmp_b7)) {
        tmp_b10 = true;
        goto LAB_00015860;
      }
      if (tmp_f11 < tmp_f4) {
LAB_00015824:
        tmp_b10 = tmp_f11 <= 1.0;
        tmp_b7 = 0.0 <= tmp_f11;
        tmp_f5 = tmp_f11;
        goto LAB_00015860;
      }
LAB_00015a10:
      tmp_i8 = tmp_i8 + -1;
      if (tmp_i8 < 0) {
        tmp_i8 = 0xf;
LAB_00015a1c:
        tmp_i9 = *(int *)(tmp_i9 + 0x90);
        if (tmp_i9 == 0) {
          return;
        }
        *param_2 = tmp_i9;
      }
    }
LAB_000158be:
    tmp_b10 = false;
  } while( true );
}

uint32_t BG_LoadCampaignSave(uint32_t param_1,int *param_2,char *param_3) {
  char tmp_c1;
  int tmp_i2;
  __int32_t **pp_Var3;
  int tmp_i4;
  int *tmp_pi5;
  char *tmp_pc6;
  int *tmp_pi7;
  int local_30;
  uint32_t local_20 [4];

  memset(param_2,0,0x6010);
  tmp_i2 = trap_FS_FOpenFile(param_1,local_20,0);
  if (tmp_i2 < 0) {
    return 0;
  }
  trap_FS_Read(param_2,4,local_20[0]);
  if (*param_2 != 0x53504349) {
    trap_FS_FCloseFile(local_20[0]);
    Com_Printf("^1ERROR: BG_LoadCampaignSave: not a campaignsave\n");
    return 0;
  }
  trap_FS_Read(param_2 + 1,1,local_20[0]);
  trap_FS_Read(param_2 + 2,4,local_20[0]);
  trap_FS_Read(param_2 + 3,4,local_20[0]);
  tmp_c1 = *param_3;
  if (tmp_c1 == '\0') {
    tmp_i2 = 0;
  }
  else {
    pp_Var3 = __ctype_tolower_loc();
    tmp_i2 = 0;
    tmp_pc6 = param_3;
    do {
      tmp_i4 = (int)tmp_c1;
      tmp_c1 = tmp_pc6[1];
      tmp_i2 = tmp_i2 + (int)(tmp_pc6 + (0x77 - (int)param_3)) * (*pp_Var3)[tmp_i4];
      tmp_pc6 = tmp_pc6 + 1;
    } while (tmp_c1 != '\0');
  }
  if (param_2[3] == tmp_i2) {
    if (0 < param_2[2]) {
      tmp_pi7 = param_2 + 5;
      local_30 = 0;
      do {
        tmp_i2 = 0;
        trap_FS_Read(tmp_pi7 + -1,4,local_20[0]);
        trap_FS_Read(tmp_pi7,4,local_20[0]);
        tmp_pi5 = tmp_pi7;
        if (0 < *tmp_pi7) {
          do {
            tmp_pi5 = tmp_pi5 + 1;
            tmp_i2 = tmp_i2 + 1;
            trap_FS_Read(tmp_pi5,4,local_20[0]);
          } while (tmp_i2 < *tmp_pi7);
        }
        local_30 = local_30 + 1;
        tmp_pi7 = tmp_pi7 + 0xc;
      } while (local_30 < param_2[2]);
    }
    trap_FS_FCloseFile(local_20[0]);
    return 1;
  }
  trap_FS_FCloseFile(local_20[0]);
  Com_Printf("^1WARNING: BG_LoadCampaignSave: campaignsave is for another profile\n");
  return 0;
}

int BG_MaxAmmoForWeapon(int param_1,int param_2) {
  byte tmp_b1;
  uint tmp_u2;

  tmp_u2 = *(uint *)(param_2 + 0x10) >> 1 & 1;
  switch(param_1) {
  case 1:
    if ((*(uint *)(param_2 + 0x10) & 0x20) == 0) {
      return 1;
    }
    return ammoTableMP._72_4_;
  case 2:
  case 7:
  case 10:
  case 0xe:
  case 0x16:
  case 0x17:
  case 0x26:
    goto _L854;
  case 3:
  case 8:
    tmp_b1 = *(byte *)(param_2 + 8);
    goto LAB_00017cb4;
  case 4:
  case 9:
    if (((*(byte *)(param_2 + 4) & 2) == 0) && ((*(byte *)(param_2 + 8) & 2) != 0)) {
      return *(int *)(ammoTableMP + param_1 * 0x48) + 1;
    }
    break;
  case 5:
    return ammoTableMP._360_4_;
  case 6:
    if ((*(byte *)(param_2 + 0x14) & 0x20) == 0) {
      return ammoTableMP._432_4_;
    }
    return ammoTableMP._432_4_ + 0x32;
  case 0xb:
  case 0x2b:
    tmp_b1 = *(byte *)(param_2 + 8) & 4;
    goto joined_r0x00017d74;
  case 0x18:
  case 0x1e:
  case 0x1f:
  case 0x27:
  case 0x28:
  case 0x29:
    tmp_b1 = *(byte *)(param_2 + 0x18);
LAB_00017cb4:
    if ((tmp_b1 & 2) != 0) {
      tmp_u2 = 1;
    }
_L854:
    return tmp_u2 * *(int *)(ammoTableMP + param_1 * 0x48 + 8) +
           *(int *)(ammoTableMP + param_1 * 0x48);
  case 0x1d:
  case 0x2e:
    if ((*(byte *)(param_2 + 0x14) & 0x20) != 0) {
      return *(int *)(ammoTableMP + param_1 * 0x48 + 8) + *(int *)(ammoTableMP + param_1 * 0x48);
    }
    break;
  case 0x21:
  case 0x2a:
    tmp_b1 = *(byte *)(param_2 + 0x14) & 0x20;
joined_r0x00017d74:
    if (tmp_b1 != 0) {
      return *(int *)(ammoTableMP + param_1 * 0x48) + 2;
    }
    break;
  case 0x24:
  case 0x25:
    if ((*(byte *)(param_2 + 4) & 2) != 0) {
      return *(int *)(ammoTableMP + param_1 * 0x48) + 4;
    }
  }
  return *(int *)(ammoTableMP + param_1 * 0x48);
}

void BG_PlayerStateToEntityState(int param_1,uint32_t *param_2,uint32_t param_3,int param_4) {
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  uint32_t tmp_u5;
  uint tmp_u6;
  uint tmp_u7;
  uint tmp_u8;

  if (((*(int *)(param_1 + 4) == 2) || (*(int *)(param_1 + 4) == 5)) ||
     (*(int *)(param_1 + 0xd0) < -0xae)) {
    param_2[1] = 10;
  }
  else {
    param_2[1] = 1;
  }
  tmp_u5 = *(uint32_t *)(param_1 + 0xa0);
  param_2[3] = 1;
  *param_2 = tmp_u5;
  param_2[4] = param_3;
  tmp_f2 = *(float *)(param_1 + 0x14);
  param_2[6] = tmp_f2;
  tmp_f3 = *(float *)(param_1 + 0x18);
  param_2[7] = tmp_f3;
  tmp_f4 = *(float *)(param_1 + 0x1c);
  param_2[8] = tmp_f4;
  if (param_4 == 0) {
    param_2[9] = *(uint32_t *)(param_1 + 0x20);
    param_2[10] = *(uint32_t *)(param_1 + 0x24);
    tmp_u5 = *(uint32_t *)(param_1 + 0x28);
    param_2[0xc] = 1;
    param_2[0xb] = tmp_u5;
    param_2[0xf] = *(uint32_t *)(param_1 + 0xb0);
    param_2[0x10] = *(uint32_t *)(param_1 + 0xb4);
    param_2[0x11] = *(uint32_t *)(param_1 + 0xb8);
  }
  else {
    param_2[6] = (float)(int)ROUND(tmp_f2);
    param_2[7] = (float)(int)ROUND(tmp_f3);
    param_2[8] = (float)(int)ROUND(tmp_f4);
    tmp_f2 = *(float *)(param_1 + 0x20);
    param_2[9] = tmp_f2;
    tmp_f3 = *(float *)(param_1 + 0x24);
    param_2[10] = tmp_f3;
    tmp_f4 = *(float *)(param_1 + 0x28);
    param_2[9] = (float)(int)ROUND(tmp_f2);
    param_2[10] = (float)(int)ROUND(tmp_f3);
    param_2[0xc] = 1;
    param_2[0xb] = (float)(int)ROUND(tmp_f4);
    tmp_f2 = *(float *)(param_1 + 0xb0);
    param_2[0xf] = tmp_f2;
    tmp_f3 = *(float *)(param_1 + 0xb4);
    param_2[0x10] = tmp_f3;
    tmp_f4 = *(float *)(param_1 + 0xb8);
    param_2[0xf] = (float)(int)ROUND(tmp_f2);
    param_2[0x10] = (float)(int)ROUND(tmp_f3);
    param_2[0x11] = (float)(int)ROUND(tmp_f4);
  }
  tmp_f2 = (float)*(int *)(param_1 + 100);
  if (0x80 < *(int *)(param_1 + 100)) {
    tmp_f2 = tmp_f2 - 256.0;
  }
  param_2[0x21] = tmp_f2;
  if ((*(byte *)(param_1 + 0x6a) & 0x80) == 0) {
    tmp_f2 = 0.0;
  }
  else {
    tmp_f2 = (float)*(int *)(param_1 + 0xd8) * 0.005493164;
  }
  param_2[0x20] = tmp_f2;
  param_2[0x3b] = *(uint32_t *)(param_1 + 0x58);
  param_2[0x3c] = *(uint32_t *)(param_1 + 0x60);
  param_2[0x2b] = *(uint32_t *)(param_1 + 0xa0);
  tmp_u6 = *(uint *)(param_1 + 0x68);
  if ((tmp_u6 & 0x8000) == 0) {
    if (*(int *)(param_1 + 0x140) == 1) {
      tmp_u6 = tmp_u6 | 0x20;
      *(uint *)(param_1 + 0x68) = tmp_u6;
      *(uint32_t *)(param_1 + 0x16c) = 0;
      goto LAB_000170d4;
    }
    if (*(int *)(param_1 + 0x140) == 2) {
      tmp_u6 = tmp_u6 & 0xffffffdf;
      *(uint *)(param_1 + 0x68) = tmp_u6;
      *(uint32_t *)(param_1 + 0x16c) = 0;
      goto LAB_000170d4;
    }
  }
  tmp_u6 = tmp_u6 & 0xffffffdf;
  *(uint *)(param_1 + 0x68) = tmp_u6;
LAB_000170d4:
  param_2[2] = tmp_u6;
  tmp_u7 = tmp_u6 & 0xfffffffe;
  if (*(int *)(param_1 + 0xd0) < 1) {
    tmp_u7 = tmp_u6 | 1;
  }
  param_2[2] = tmp_u7;
  tmp_u6 = *(uint *)(param_1 + 0x470);
  tmp_u7 = *(uint *)(param_1 + 0x6c);
  if ((int)tmp_u6 < (int)tmp_u7) {
    tmp_u7 = tmp_u7 - 4;
    if ((int)tmp_u6 < (int)tmp_u7) {
      *(uint *)(param_1 + 0x470) = tmp_u7;
      tmp_u6 = tmp_u7;
    }
    tmp_i1 = param_1 + (tmp_u6 & 3) * 4;
    param_2[0x2e] = (tmp_u6 & 3) << 8 | *(uint *)(tmp_i1 + 0x70);
    param_2[0x2f] = *(uint32_t *)(tmp_i1 + 0x80);
    *(int *)(param_1 + 0x470) = *(int *)(param_1 + 0x470) + 1;
    tmp_u7 = *(uint *)(param_1 + 0x6c);
  }
  tmp_u6 = *(uint *)(param_1 + 0x90);
  if (tmp_u7 != tmp_u6) {
    tmp_u7 = param_2[0x30];
    tmp_u8 = tmp_u6;
    do {
      tmp_u6 = tmp_u8 + 1;
      tmp_i1 = param_1 + (tmp_u8 & 3) * 4;
      tmp_u8 = tmp_u7 & 3;
      tmp_u7 = tmp_u7 + 1;
      param_2[tmp_u8 + 0x31] = *(uint32_t *)(tmp_i1 + 0x70);
      param_2[tmp_u8 + 0x35] = *(uint32_t *)(tmp_i1 + 0x80);
      param_2[0x30] = tmp_u7;
      tmp_u8 = tmp_u6;
    } while (*(uint *)(param_1 + 0x6c) != tmp_u6);
  }
  *(uint *)(param_1 + 0x90) = tmp_u6;
  param_2[0x3a] = *(uint32_t *)(param_1 + 0xa4);
  param_2[0x25] = *(uint32_t *)(param_1 + 0x50);
  param_2[0x39] = 0;
  if (*(int *)(param_1 + 0x150) != 0) {
    param_2[0x39] = 1;
  }
  if (*(int *)(param_1 + 0x154) != 0) {
    param_2[0x39] = param_2[0x39] | 2;
  }
  if (*(int *)(param_1 + 0x158) != 0) {
    param_2[0x39] = param_2[0x39] | 4;
  }
  if (*(int *)(param_1 + 0x15c) != 0) {
    param_2[0x39] = param_2[0x39] | 8;
  }
  if (*(int *)(param_1 + 0x160) != 0) {
    param_2[0x39] = param_2[0x39] | 0x10;
  }
  if (*(int *)(param_1 + 0x164) != 0) {
    param_2[0x39] = param_2[0x39] | 0x20;
  }
  if (*(int *)(param_1 + 0x168) != 0) {
    param_2[0x39] = param_2[0x39] | 0x40;
  }
  if (*(int *)(param_1 + 0x16c) != 0) {
    param_2[0x39] = param_2[0x39] | 0x80;
  }
  if (*(int *)(param_1 + 0x170) != 0) {
    param_2[0x39] = param_2[0x39] | 0x100;
  }
  if (*(int *)(param_1 + 0x174) != 0) {
    param_2[0x39] = param_2[0x39] | 0x200;
  }
  if (*(int *)(param_1 + 0x178) != 0) {
    param_2[0x39] = param_2[0x39] | 0x400;
  }
  if (*(int *)(param_1 + 0x17c) != 0) {
    param_2[0x39] = param_2[0x39] | 0x800;
  }
  if (*(int *)(param_1 + 0x180) != 0) {
    param_2[0x39] = param_2[0x39] | 0x1000;
  }
  if (*(int *)(param_1 + 0x184) != 0) {
    param_2[0x39] = param_2[0x39] | 0x2000;
  }
  if (*(int *)(param_1 + 0x188) != 0) {
    param_2[0x39] = param_2[0x39] | 0x4000;
  }
  if (*(int *)(param_1 + 0x18c) != 0) {
    param_2[0x39] = param_2[0x39] | 0x8000;
  }
  param_2[0x41] = *(uint32_t *)(param_1 + 0x41c);
  param_2[0x42] = *(uint32_t *)(param_1 + 0x420);
  param_2[0x46] = *(uint32_t *)(param_1 + 0x5a8);
  if (*(int *)(param_1 + 4) != 2) {
    param_2[0x26] = *(uint32_t *)(param_1 + 0x398);
    param_2[0x27] = *(uint32_t *)(param_1 + 0xd0);
  }
  return;
}

bool BG_PlayerTouchesItem(int param_1,int param_2,int param_3) {
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  bool tmp_b5;
  long double tmp_l6;
  float tmp_f7;
  double tmp_d8;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;

  tmp_i3 = *(int *)(param_2 + 0x110);
  switch(*(uint32_t *)(param_2 + 0xc)) {
  case 0:
  case 1:
  case 9:
    local_40 = *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x1c);
    local_38 = *(float *)(param_2 + 0x20);
    break;
  case 2:
    tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) * 0.001;
    goto LAB_000151e2;
  case 3:
    tmp_i3 = *(int *)(param_2 + 0x14) + *(int *)(param_2 + 0x10);
    if (param_3 <= tmp_i3) {
      tmp_i3 = param_3;
    }
    tmp_f7 = (float)(tmp_i3 - *(int *)(param_2 + 0x10)) * 0.001;
    tmp_f1 = 0.0;
    if (0.0 <= tmp_f7) {
      tmp_f1 = tmp_f7;
    }
    goto LAB_000151e2;
  default:
    Com_Error(2,"BG_EvaluateTrajectory: unknown trType: %i",*(uint32_t *)(param_2 + 0x10));
    break;
  case 5:
    tmp_d8 = ((double)(param_3 - *(int *)(param_2 + 0x10)) / (double)*(int *)(param_2 + 0x14)) *
            3.141592653589793;
    tmp_d8 = sin(tmp_d8 + tmp_d8);
    tmp_f1 = (float)tmp_d8;
LAB_000151e2:
    local_40 = *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x28) * tmp_f1 + *(float *)(param_2 + 0x1c);
    local_38 = tmp_f1 * *(float *)(param_2 + 0x2c) + *(float *)(param_2 + 0x20);
    break;
  case 6:
  case 7:
    tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) * 0.001;
    local_40 = *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x28) * tmp_f1 + *(float *)(param_2 + 0x1c);
    local_38 = (*(float *)(param_2 + 0x20) + tmp_f1 * *(float *)(param_2 + 0x2c)) -
               tmp_f1 * 0.0 * tmp_f1;
    break;
  case 8:
    tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) * 0.001;
    local_40 = *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = *(float *)(param_2 + 0x28) * tmp_f1 + *(float *)(param_2 + 0x1c);
    local_38 = (*(float *)(param_2 + 0x2c) * tmp_f1 + *(float *)(param_2 + 0x20)) - tmp_f1 * 0.0;
    break;
  case 10:
    tmp_i2 = *(int *)(param_2 + 0x10);
    tmp_i4 = tmp_i2 + *(int *)(param_2 + 0x14);
    tmp_l6 = (long double)VectorLength(param_2 + 0x24);
    tmp_i3 = *(int *)(param_2 + 0x14);
    VectorNormalize2(param_2 + 0x24,&local_40);
    if (param_3 <= tmp_i4) {
      tmp_i4 = param_3;
    }
    tmp_f1 = (float)(tmp_i4 - tmp_i2) * 0.001;
    tmp_f1 = (float)(tmp_l6 / ((long double)tmp_i3 * (long double)0.001)) * 0.5 * tmp_f1 * tmp_f1;
    local_40 = tmp_f1 * local_40 + *(float *)(param_2 + 0x18);
    local_3c = tmp_f1 * local_3c + *(float *)(param_2 + 0x1c);
    local_38 = tmp_f1 * local_38 + *(float *)(param_2 + 0x20);
    break;
  case 0xb:
    tmp_i3 = *(int *)(param_2 + 0x14) + *(int *)(param_2 + 0x10);
    if (param_3 <= tmp_i3) {
      tmp_i3 = param_3;
    }
    tmp_f1 = (float)(tmp_i3 - *(int *)(param_2 + 0x10)) * 0.001;
    tmp_l6 = (long double)VectorLength(param_2 + 0x24);
    tmp_i3 = *(int *)(param_2 + 0x14);
    VectorNormalize2(param_2 + 0x24,&local_40);
    tmp_f7 = -(float)(tmp_l6 / ((long double)tmp_i3 * (long double)0.001)) * 0.5 * tmp_f1 * tmp_f1;
    local_40 = tmp_f7 * local_40 + *(float *)(param_2 + 0x24) * tmp_f1 + *(float *)(param_2 + 0x18);
    local_3c = tmp_f7 * local_3c + tmp_f1 * *(float *)(param_2 + 0x28) + *(float *)(param_2 + 0x1c);
    local_38 = tmp_f7 * local_38 + *(float *)(param_2 + 0x2c) * tmp_f1 + *(float *)(param_2 + 0x20);
    break;
  case 0xc:
    tmp_b5 = tmp_i3 < 0;
    if (tmp_b5) {
      tmp_i3 = -tmp_i3;
    }
    tmp_i3 = tmp_i3 + -1;
    if ((tmp_i3 != -1) && (tmp_i3 < numSplinePaths)) {
      if ((*(int *)(param_2 + 0x14) == 0) ||
         (tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) / (float)*(int *)(param_2 + 0x14),
         tmp_f1 < 0.0)) {
        tmp_f1 = 0.0;
      }
      else if (1.0 < tmp_f1) {
        tmp_f1 = 1.0;
      }
      if (tmp_b5) {
        tmp_f1 = 1.0 - tmp_f1;
      }
      BG_CalculateSpline_r(splinePaths + tmp_i3 * 0x394,&local_34,&local_28,tmp_f1);
      local_40 = (local_28 - local_34) * tmp_f1 + local_34;
      local_3c = (local_24 - local_30) * tmp_f1 + local_30;
      local_38 = (local_20 - local_2c) * tmp_f1 + local_2c;
    }
    break;
  case 0xd:
    tmp_b5 = tmp_i3 < 0;
    if (tmp_b5) {
      tmp_i3 = -tmp_i3;
    }
    tmp_i3 = tmp_i3 + -1;
    if ((tmp_i3 == -1) || (numSplinePaths <= tmp_i3)) break;
    if (*(int *)(param_2 + 0x14) == 0) {
      tmp_f1 = 0.0;
LAB_000152b7:
      if (tmp_b5) {
        tmp_f1 = 1.0 - tmp_f1;
      }
      tmp_f1 = tmp_f1 * 16.0;
      tmp_f7 = floorf(tmp_f1);
      tmp_i2 = (int)ROUND(tmp_f7);
LAB_000152f9:
      if (0xf < tmp_i2) goto LAB_00015304;
      tmp_f1 = tmp_f1 - (float)tmp_i2;
LAB_000154aa:
      tmp_f1 = tmp_f1 * *(float *)(splinePaths + tmp_i2 * 0x1c + tmp_i3 * 0x394 + 0x1e0);
    }
    else {
      tmp_f1 = (float)(param_3 - *(int *)(param_2 + 0x10)) / (float)*(int *)(param_2 + 0x14);
      if (tmp_f1 < 0.0) {
        if (tmp_b5) {
          tmp_i2 = 0x10;
          tmp_f1 = 16.0;
          goto LAB_000152f9;
        }
        tmp_f1 = 0.0;
        tmp_i2 = 0;
        goto LAB_000154aa;
      }
      if (tmp_f1 <= 1.0) goto LAB_000152b7;
      if (tmp_b5) {
        tmp_i2 = 0;
        tmp_f1 = 0.0;
        goto LAB_000152f9;
      }
LAB_00015304:
      tmp_f1 = *(float *)(splinePaths + tmp_i3 * 0x394 + 900);
      tmp_i2 = 0xf;
    }
    tmp_i3 = tmp_i2 * 0x1c + tmp_i3 * 0x394;
    local_40 = *(float *)(splinePaths + tmp_i3 + 0x1d4) * tmp_f1 +
               *(float *)(splinePaths + tmp_i3 + 0x1c8);
    local_3c = *(float *)(splinePaths + tmp_i3 + 0x1d8) * tmp_f1 +
               *(float *)(splinePaths + tmp_i3 + 0x1cc);
    local_38 = tmp_f1 * *(float *)(splinePaths + tmp_i3 + 0x1dc) +
               *(float *)(splinePaths + tmp_i3 + 0x1d0);
  }
  tmp_f1 = *(float *)(param_1 + 0x14) - local_40;
  tmp_b5 = false;
  if ((((tmp_f1 <= 36.0) && (-36.0 <= tmp_f1)) &&
      (tmp_f1 = *(float *)(param_1 + 0x18) - local_3c, tmp_f1 <= 36.0)) &&
     ((-36.0 <= tmp_f1 && (tmp_f1 = *(float *)(param_1 + 0x1c) - local_38, tmp_f1 <= 36.0)))) {
    tmp_b5 = -36.0 <= tmp_f1;
  }
  return tmp_b5;
}

uint32_t
BG_RaySphereIntersection(float param_1,float *param_2,float *param_3,float *param_4,float *param_5) {
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;

  tmp_f1 = *param_3 - *param_2;
  tmp_f4 = param_3[1] - param_2[1];
  tmp_f3 = param_3[2] - param_2[2];
  tmp_f2 = param_3[5] * tmp_f3 + param_3[4] * tmp_f4 + param_3[3] * tmp_f1;
  tmp_f2 = tmp_f2 + tmp_f2;
  tmp_f1 = tmp_f2 * tmp_f2 -
          ((tmp_f3 * tmp_f3 + tmp_f4 * tmp_f4 + tmp_f1 * tmp_f1) - param_1 * param_1) * 4.0;
  if (tmp_f1 < 0.0) {
    return 0;
  }
  tmp_f4 = SQRT(tmp_f1);
  if (NAN(tmp_f4)) {
    tmp_f4 = sqrtf(tmp_f1);
  }
  *param_4 = (tmp_f4 - tmp_f2) * 0.5;
  *param_5 = (-tmp_f2 - tmp_f4) * 0.5;
  return 1;
}

void BG_RotatePoint(float *param_1,float *param_2) {
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;

  tmp_f1 = *param_1;
  tmp_f2 = param_1[1];
  tmp_f3 = param_1[2];
  *param_1 = param_2[2] * tmp_f3 + param_2[1] * tmp_f2 + *param_2 * tmp_f1;
  param_1[1] = param_2[5] * tmp_f3 + param_2[4] * tmp_f2 + param_2[3] * tmp_f1;
  param_1[2] = tmp_f3 * param_2[8] + tmp_f2 * param_2[7] + tmp_f1 * param_2[6];
  return;
}

long double BG_SplineLength(uint32_t param_1) {
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  long double tmp_l6;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;

  tmp_f1 = 0.0;
  tmp_i5 = 0x65;
  local_64 = 0.0;
  local_5c = 0.0;
  local_60 = 0.0;
  local_58 = 0.0;
  do {
    BG_CalculateSpline_r(param_1,&local_34,&local_28,tmp_f1);
    tmp_f4 = (local_28 - local_34) * tmp_f1 + local_34;
    tmp_f3 = (local_24 - local_30) * tmp_f1 + local_30;
    tmp_f2 = (local_20 - local_2c) * tmp_f1 + local_2c;
    if (tmp_f1 != 0.0) {
      local_34 = tmp_f4 - local_60;
      local_30 = tmp_f3 - local_5c;
      local_2c = tmp_f2 - local_64;
      tmp_l6 = (long double)VectorLength(&local_34);
      local_58 = (float)(tmp_l6 + (long double)local_58);
    }
    tmp_i5 = tmp_i5 + -1;
    tmp_f1 = tmp_f1 + 0.01;
    local_64 = tmp_f2;
    local_60 = tmp_f4;
    local_5c = tmp_f3;
  } while (tmp_i5 != 0);
  return (long double)local_58;
}

uint32_t BG_StoreCampaignSave(uint32_t param_1,uint32_t *param_2,char *param_3) {
  char tmp_c1;
  int tmp_i2;
  __int32_t **pp_Var3;
  int tmp_i4;
  int *tmp_pi5;
  char *tmp_pc6;
  int *tmp_pi7;
  int local_30;
  uint32_t local_20 [4];

  tmp_i2 = trap_FS_FOpenFile(param_1,local_20,1);
  if (-1 < tmp_i2) {
    *param_2 = 0x53504349;
    param_2[1] = 1;
    trap_FS_Write(param_2,4,local_20[0]);
    trap_FS_Write(param_2 + 1,1,local_20[0]);
    trap_FS_Write(param_2 + 2,4,local_20[0]);
    tmp_c1 = *param_3;
    if (tmp_c1 == '\0') {
      tmp_i2 = 0;
    }
    else {
      pp_Var3 = __ctype_tolower_loc();
      tmp_i2 = 0;
      tmp_pc6 = param_3;
      do {
        tmp_i4 = (int)tmp_c1;
        tmp_c1 = tmp_pc6[1];
        tmp_i2 = tmp_i2 + (int)(tmp_pc6 + (0x77 - (int)param_3)) * (*pp_Var3)[tmp_i4];
        tmp_pc6 = tmp_pc6 + 1;
      } while (tmp_c1 != '\0');
    }
    param_2[3] = tmp_i2;
    trap_FS_Write(param_2 + 3,4,local_20[0]);
    if (0 < (int)param_2[2]) {
      tmp_pi7 = param_2 + 5;
      local_30 = 0;
      do {
        tmp_i2 = 0;
        trap_FS_Write(tmp_pi7 + -1,4,local_20[0]);
        trap_FS_Write(tmp_pi7,4,local_20[0]);
        tmp_pi5 = tmp_pi7;
        if (0 < *tmp_pi7) {
          do {
            tmp_pi5 = tmp_pi5 + 1;
            tmp_i2 = tmp_i2 + 1;
            trap_FS_Write(tmp_pi5,4,local_20[0]);
          } while (tmp_i2 < *tmp_pi7);
        }
        local_30 = local_30 + 1;
        tmp_pi7 = tmp_pi7 + 0xc;
      } while (local_30 < (int)param_2[2]);
    }
    trap_FS_FCloseFile(local_20[0]);
    return 1;
  }
  return 0;
}

void BG_TransposeMatrix(uint32_t *param_1,uint32_t *param_2) {
  *param_2 = *param_1;
  param_2[1] = param_1[3];
  param_2[2] = param_1[6];
  param_2[3] = param_1[1];
  param_2[4] = param_1[4];
  param_2[5] = param_1[7];
  param_2[6] = param_1[2];
  param_2[7] = param_1[5];
  param_2[8] = param_1[8];
  return;
}

uint32_t BG_TraverseSpline(float *param_1,int *param_2) {
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;

  tmp_f1 = *param_1;
  if (tmp_f1 <= 1.0) {
LAB_000155b0:
    if (0.0 <= tmp_f1) {
      return 1;
    }
    tmp_f1 = tmp_f1 * *(float *)(*param_2 + 0x388);
    tmp_i3 = *(int *)(*param_2 + 0x90);
    if (tmp_i3 != 0) {
      tmp_f2 = *(float *)(tmp_i3 + 0x388);
      while (tmp_f2 != 0.0) {
        *param_2 = tmp_i3;
        tmp_f1 = 1.0 - -tmp_f1 / *(float *)(tmp_i3 + 0x388);
        *param_1 = tmp_f1;
        if (0.0 <= tmp_f1) {
          return 1;
        }
        tmp_f1 = tmp_f1 * *(float *)(*param_2 + 0x388);
        tmp_i3 = *(int *)(*param_2 + 0x90);
        if (tmp_i3 == 0) {
          return 0;
        }
        tmp_f2 = *(float *)(tmp_i3 + 0x388);
      }
    }
  }
  else {
    *param_1 = tmp_f1 - 1.0;
    tmp_f1 = (tmp_f1 - 1.0) * *(float *)(*param_2 + 0x388);
    tmp_i3 = *(int *)(*param_2 + 0x8c);
    if (tmp_i3 != 0) {
      tmp_f2 = *(float *)(tmp_i3 + 0x388);
      while (tmp_f2 != 0.0) {
        *param_2 = tmp_i3;
        tmp_f1 = tmp_f1 / *(float *)(tmp_i3 + 0x388);
        if (tmp_f1 <= 1.0) {
          *param_1 = tmp_f1;
          goto LAB_000155b0;
        }
        *param_1 = tmp_f1 - 1.0;
        tmp_f1 = (tmp_f1 - 1.0) * *(float *)(*param_2 + 0x388);
        tmp_i3 = *(int *)(*param_2 + 0x8c);
        if (tmp_i3 == 0) {
          return 0;
        }
        tmp_f2 = *(float *)(tmp_i3 + 0x388);
      }
    }
  }
  return 0;
}

int * BG_ValidStatWeapon(uint param_1) {
  int tmp_i1;
  int *tmp_pi2;

  if ((param_1 - 1 < 0x33) &&
     ((0x11 < param_1 - 0xb || ((1 << ((byte)(param_1 - 0xb) & 0x1f) & 0x202a3U) == 0)))) {
    switch(param_1) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
      if (param_1 != 0x25) {
        if (param_1 < 0x26) {
          if (param_1 != 9) {
LAB_00017478:
            tmp_pi2 = (int *)(bg_itemlist + 0x38);
            tmp_i1 = bg_itemlist._56_4_;
            while (tmp_i1 != 0) {
              while (tmp_pi2[9] == 1) {
                if (param_1 == tmp_pi2[10]) {
                  return tmp_pi2;
                }
                tmp_pi2 = tmp_pi2 + 0xe;
                if (*tmp_pi2 == 0) goto LAB_000174ad;
              }
              tmp_pi2 = tmp_pi2 + 0xe;
              tmp_i1 = *tmp_pi2;
            }
LAB_000174ad:
            Com_Printf("^1ERROR : ^7BG_FindItemForWeapon() ^9no item for weapon %i (%s^9)\n",param_1
                       ,param_1 * 0x6b0 + 0x2f7fd4);
            return (int *)0x0;
          }
        }
        else if (1 < param_1 - 0x27) goto LAB_00017478;
      }
    }
  }
  return (int *)0x0;
}

int BG_WeaponForMOD(int param_1) {
  int tmp_i1;
  int *tmp_pi2;

  if (param_1 == 0x3f) {
    return 1;
  }
  tmp_pi2 = (int *)(ammoTableMP + 0x3c);
  tmp_i1 = 0;
  do {
    if (*tmp_pi2 == param_1) {
      return tmp_i1;
    }
    tmp_i1 = tmp_i1 + 1;
    tmp_pi2 = tmp_pi2 + 0x12;
  } while (tmp_i1 != 0x34);
  return 0;
}

uint32_t BG_WeaponInWolfMP(uint32_t param_1) {
  switch(param_1) {
  default:
    return 0;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
  case 0x31:
  case 0x32:
  case 0x33:
    return 1;
  }
}

int BG_cleanName(char *param_1,char *param_2,int param_3,int param_4) {
  char tmp_c1;
  int tmp_i2;
  char *tmp_pc3;

  tmp_c1 = *param_1;
  tmp_pc3 = param_2;
joined_r0x000190b2:
  do {
    if (tmp_c1 == '\0') {
LAB_000190e0:
      tmp_i2 = (int)tmp_pc3 - (int)param_2;
LAB_000190e4:
      *tmp_pc3 = '\0';
      return tmp_i2;
    }
    tmp_i2 = (int)tmp_pc3 - (int)param_2;
    if (param_3 + -1 <= tmp_i2) goto LAB_000190e4;
    if (tmp_c1 != '^') {
      if (tmp_c1 < ' ') {
        if ((tmp_c1 == '\n') && (param_4 != 0)) {
LAB_000190f5:
          *tmp_pc3 = tmp_c1;
          param_1 = param_1 + 1;
          tmp_pc3 = tmp_pc3 + 1;
          tmp_c1 = *param_1;
          goto joined_r0x000190b2;
        }
      }
      else if (tmp_c1 != '\x7f') goto LAB_000190f5;
      tmp_c1 = param_1[1];
      param_1 = param_1 + 1;
      goto joined_r0x000190b2;
    }
    if (param_1[1] == '\0') goto LAB_000190e0;
    tmp_c1 = param_1[2];
    param_1 = param_1 + 2;
  } while( true );
}

bool BG_isLightWeaponSupportingFastReload(uint param_1) {
  if (((1 < param_1 - 2) && (1 < param_1 - 7)) && ((param_1 & 0xfffffffb) != 10)) {
    return param_1 == 0x26 || param_1 == 0x1f;
  }
  return true;
}

void BG_setCrosshair(char *param_1,float *param_2,float param_3,uint32_t param_4) {
  byte tmp_b1;
  byte tmp_b2;
  byte tmp_b3;
  char tmp_c4;
  uint32_t *tmp_pu5;
  float tmp_f6;
  int tmp_i7;
  int tmp_i8;

  tmp_f6 = 1.0;
  *param_2 = 1.0;
  param_2[1] = 1.0;
  param_2[2] = 1.0;
  if ((param_3 <= 1.0) && (tmp_f6 = 0.0, 0.0 <= param_3)) {
    tmp_f6 = param_3;
  }
  param_2[3] = tmp_f6;
  if ((*param_1 == '0') && ((param_1[1] & 0xdfU) == 0x58)) {
    tmp_b1 = param_1[2];
    tmp_i8 = (int)(char)tmp_b1;
    if (((((tmp_b1 != 0) &&
          (((((byte)((tmp_b1 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b1 - 0x30) < 10)) &&
            (tmp_b2 = param_1[3], tmp_b2 != 0)) &&
           (((byte)((tmp_b2 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b2 - 0x30) < 10)))))) &&
         (tmp_b3 = param_1[4], tmp_b3 != 0)) &&
        ((((byte)((tmp_b3 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b3 - 0x30) < 10)) &&
         ((tmp_b3 = param_1[5], tmp_b3 != 0 &&
          ((((byte)((tmp_b3 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b3 - 0x30) < 10)) &&
           (tmp_b3 = param_1[6], tmp_b3 != 0)))))))) &&
       ((((byte)((tmp_b3 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b3 - 0x30) < 10)) &&
        ((tmp_b3 = param_1[7], tmp_b3 != 0 &&
         (((byte)((tmp_b3 & 0xdf) + 0xbf) < 6 || ((byte)(tmp_b3 - 0x30) < 10)))))))) {
      if ((char)tmp_b1 < ':') {
        tmp_i8 = (tmp_i8 + -0x30) * 0x10;
      }
      else if ((char)tmp_b1 < 'a') {
        tmp_i8 = (tmp_i8 + -0x37) * 0x10;
      }
      else {
        tmp_i8 = (tmp_i8 + -0x57) * 0x10;
      }
      tmp_i7 = (int)(char)tmp_b2;
      if ((char)tmp_b2 < ':') {
        tmp_i7 = tmp_i7 + -0x30;
      }
      else if ((char)tmp_b2 < 'a') {
        tmp_i7 = tmp_i7 + -0x37;
      }
      else {
        tmp_i7 = tmp_i7 + -0x57;
      }
      *param_2 = (float)(tmp_i8 + tmp_i7) / 255.0;
      tmp_c4 = param_1[4];
      tmp_i8 = (int)tmp_c4;
      if (tmp_c4 < ':') {
        tmp_i8 = (tmp_i8 + -0x30) * 0x10;
      }
      else if (tmp_c4 < 'a') {
        tmp_i8 = (tmp_i8 + -0x37) * 0x10;
      }
      else {
        tmp_i8 = (tmp_i8 + -0x57) * 0x10;
      }
      tmp_c4 = param_1[5];
      tmp_i7 = (int)tmp_c4;
      if (tmp_c4 < ':') {
        tmp_i7 = tmp_i7 + -0x30;
      }
      else if (tmp_c4 < 'a') {
        tmp_i7 = tmp_i7 + -0x37;
      }
      else {
        tmp_i7 = tmp_i7 + -0x57;
      }
      param_2[1] = (float)(tmp_i8 + tmp_i7) / 255.0;
      tmp_c4 = param_1[6];
      tmp_i8 = (int)tmp_c4;
      if (tmp_c4 < ':') {
        tmp_i8 = (tmp_i8 + -0x30) * 0x10;
      }
      else if (tmp_c4 < 'a') {
        tmp_i8 = (tmp_i8 + -0x37) * 0x10;
      }
      else {
        tmp_i8 = (tmp_i8 + -0x57) * 0x10;
      }
      tmp_c4 = param_1[7];
      tmp_i7 = (int)tmp_c4;
      if (tmp_c4 < ':') {
        tmp_i7 = tmp_i7 + -0x30;
      }
      else if (tmp_c4 < 'a') {
        tmp_i7 = tmp_i7 + -0x37;
      }
      else {
        tmp_i7 = tmp_i7 + -0x57;
      }
      param_2[2] = (float)(tmp_i8 + tmp_i7) / 255.0;
      return;
    }
  }
  else {
    tmp_i8 = 0;
    tmp_pu5 = OSP_Colortable;
    while (tmp_pu5 != (uint32_t *)0x0) {
      tmp_i7 = Q_stricmp(param_1,tmp_pu5);
      if (tmp_i7 == 0) {
        *param_2 = *(float *)(&PTR_colorWhite_00066e24)[tmp_i8 * 2];
        param_2[1] = *(float *)((&PTR_colorWhite_00066e24)[tmp_i8 * 2] + 4);
        param_2[2] = *(float *)((&PTR_colorWhite_00066e24)[tmp_i8 * 2] + 8);
        return;
      }
      tmp_i8 = tmp_i8 + 1;
      tmp_pu5 = (&OSP_Colortable)[tmp_i8 * 2];
    }
  }
  trap_Cvar_Set(param_4,"White");
  return;
}

byte BG_simpleWeaponState(int param_1) {
  byte tmp_b1;
  uint tmp_u2;

  tmp_b1 = 0;
  if (param_1 - 1U < 7) {
    tmp_b1 = 1;
    tmp_u2 = 1 << ((byte)(param_1 - 1U) & 0x1f);
    if (((tmp_u2 & 0xd) == 0) && (tmp_b1 = 3, (tmp_u2 & 0x40) == 0)) {
      return ~-((tmp_u2 & 0x30) == 0) & 2;
    }
  }
  return tmp_b1;
}
