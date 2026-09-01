/* Fireteam UI and state — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_fireteams.h"

uint32_t CG_FireteamHasClass(int param_1,int param_2)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  
  if ((((GHIDRA_FIELD(cgs, 27388, 4) != 8) && (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3)) &&
      (tmp_i1 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9578), tmp_i1 != 0)) &&
     (0 < (int)GHIDRA_FIELD(cgs, 27400, 4))) {
    tmp_pi2 = (int *)(cgs + 0x940c);
    tmp_i3 = 0;
    if (param_2 == 0) {
      do {
        if ((((*tmp_pi2 != 0) && (tmp_pi2[0x22] != 3)) && (tmp_i1 == tmp_pi2[0x5b])) &&
           (tmp_pi2[0x2b] == param_1)) {
          return 1;
        }
        tmp_i3 = tmp_i3 + 1;
        tmp_pi2 = tmp_pi2 + 0x69;
      } while (tmp_i3 != GHIDRA_FIELD(cgs, 27400, 4));
    }
    else {
      do {
        if (((*tmp_pi2 != 0) && (tmp_pi2[0x22] != 3)) &&
           ((tmp_i1 == tmp_pi2[0x5b] && ((tmp_pi2[0x2b] == param_1 && (tmp_pi2[0x5c] != 0)))))) {
          return 1;
        }
        tmp_i3 = tmp_i3 + 1;
        tmp_pi2 = tmp_pi2 + 0x69;
      } while (tmp_i3 != GHIDRA_FIELD(cgs, 27400, 4));
    }
  }
  return 0;
}

void CG_Fireteams_MenuTitleText_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  
  if (GHIDRA_FIELD(cgs, 27388, 4) != 8) {
    switch(GHIDRA_FIELD(cgs, 33701700, 4)) {
    case 0:
      tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
      CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),
                        (float)*(int *)(param_1 + 0x18) + *(float *)(param_1 + 0xc),*tmp_pu1,
                        tmp_pu1[1],tmp_pu1 + 2,"MESSAGE",0,0,tmp_pu1[6],tmp_pu1[8]);
      return;
    case 1:
      tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
      tmp_u6 = tmp_pu1[8];
      tmp_u5 = tmp_pu1[6];
      tmp_pc4 = "FIRETEAMS";
      tmp_u3 = tmp_pu1[1];
      tmp_u2 = *tmp_pu1;
      break;
    case 2:
      tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
      CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),
                        (float)*(int *)(param_1 + 0x18) + *(float *)(param_1 + 0xc),*tmp_pu1,
                        tmp_pu1[1],tmp_pu1 + 2,&g_unk_00115af2,0,0,tmp_pu1[6],tmp_pu1[8]);
      return;
    case 3:
      tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
      CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),
                        (float)*(int *)(param_1 + 0x18) + *(float *)(param_1 + 0xc),*tmp_pu1,
                        tmp_pu1[1],tmp_pu1 + 2,"PROPOSE",0,0,tmp_pu1[6],tmp_pu1[8]);
      return;
    case 4:
      if (GHIDRA_FIELD(cgs, 33701696, 4) == 3) {
        tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
        CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),
                          (float)*(int *)(param_1 + 0x18) + *(float *)(param_1 + 0xc),*tmp_pu1,
                          tmp_pu1[1],tmp_pu1 + 2,&g_unk_00115b06,0,0,tmp_pu1[6],tmp_pu1[8]);
        return;
      }
      if (GHIDRA_FIELD(cgs, 33701696, 4) == 4) {
        tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
        tmp_u6 = tmp_pu1[8];
        tmp_u5 = tmp_pu1[6];
        tmp_pc4 = "WARN";
      }
      else {
        if (GHIDRA_FIELD(cgs, 33701696, 4) != 2) {
          return;
        }
        tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
        tmp_u6 = tmp_pu1[8];
        tmp_u5 = tmp_pu1[6];
        tmp_pc4 = "INVITE";
      }
      tmp_u3 = tmp_pu1[1];
      tmp_u2 = *tmp_pu1;
      break;
    default:
      goto switchD_00077dca_default;
    }
    CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),
                      (float)*(int *)(param_1 + 0x18) + *(float *)(param_1 + 0xc),tmp_u2,tmp_u3,
                      tmp_pu1 + 2,tmp_pc4,0,0,tmp_u5,tmp_u6);
  }
switchD_00077dca_default:
  return;
}

void CG_Fireteams_MenuText_Draw(int param_1)
{
  uint8_t **tmp_ppu1;
  uint32_t *tmp_pu2;
  int *tmp_pi3;
  uint32_t tmp_u4;
  uint8_t *tmp_pu5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  uint8_t *tmp_pu10;
  int tmp_i11;
  int tmp_i12;
  float local_34;
  int local_30;
  uint local_2c;
  int local_28;
  int local_24;
  
  local_34 = *(float *)(param_1 + 0xc);
  if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
    return;
  }
  switch(GHIDRA_FIELD(cgs, 33701700, 4)) {
  case 0:
    if (GHIDRA_FIELD(cgs, 33701696, 4) == -1) {
      if (ftMenuRootStrings != (uint8_t *)0x0) {
        tmp_i11 = 1;
        do {
          if ((4 < tmp_i11 - 1U) || (tmp_i12 = CG_FireteamHasClass(tmp_i11 - 1U,1), tmp_i12 != 0)) {
            if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
              tmp_u4 = va("%s. %s",*(uint32_t *)(ftMenuSoliderStrings + tmp_i11 * 4 + 0xc),
                         *(uint32_t *)(tmp_i11 * 4 + 0x144ddc));
            }
            else {
              tmp_u4 = va("%i. %s",tmp_i11 % 10,*(uint32_t *)(tmp_i11 * 4 + 0x144ddc));
            }
            tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
            CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_34,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,
                              tmp_u4,0,0,tmp_pu2[6],tmp_pu2[8]);
            local_34 = local_34 + *(float *)(param_1 + 0x14);
          }
          tmp_ppu1 = &ftMenuRootStrings + tmp_i11;
          tmp_i11 = tmp_i11 + 1;
        } while (*tmp_ppu1 != (uint8_t *)0x0);
      }
    }
    else if ((uint)GHIDRA_FIELD(cgs, 33701696, 4) < 5) {
      tmp_pi3 = *(int **)(ftMenuStrings + GHIDRA_FIELD(cgs, 33701696, 4) * 4);
      tmp_i11 = *tmp_pi3;
      if (tmp_i11 != 0) {
        tmp_i12 = 1;
        do {
          if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
            tmp_u4 = va("%s. %s",*(uint32_t *)
                                 (*(int *)(ftMenuStringsAlphachars + GHIDRA_FIELD(cgs, 33701696, 4) * 4) +
                                 tmp_i12 * 4 + -4),tmp_i11);
          }
          else {
            tmp_u4 = va("%i. %s",tmp_i12 % 10,tmp_i11);
          }
          tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
          CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_34,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,tmp_u4
                            ,0,0,tmp_pu2[6],tmp_pu2[8]);
          tmp_i11 = tmp_pi3[tmp_i12];
          local_34 = local_34 + *(float *)(param_1 + 0x14);
          tmp_i12 = tmp_i12 + 1;
        } while (tmp_i11 != 0);
      }
    }
    break;
  case 1:
    tmp_i11 = CG_IsOnFireteam(g_unk_01047ac4);
    if (tmp_i11 == 0) {
      if (ftOffMenuList != (uint8_t *)0x0) {
        tmp_i11 = 1;
        tmp_pu5 = ftOffMenuList;
        do {
          if (tmp_i11 == 1) {
            tmp_i12 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
            if (tmp_i12 - 1U < 2) {
              local_2c = 0;
              if (g_unk_010b3b78 != 0) {
                local_2c = (uint)(tmp_i12 == *(int *)(cgs + g_unk_010b3b74 * 0x1a4 + 0x9494));
              }
              if (g_unk_010b3bc8 != 0) {
                local_2c = local_2c + (tmp_i12 == *(int *)(cgs + g_unk_010b3bc4 * 0x1a4 + 0x9494));
              }
              if (g_unk_010b3c18 != 0) {
                local_2c = local_2c + (tmp_i12 == *(int *)(cgs + g_unk_010b3c14 * 0x1a4 + 0x9494));
              }
              if (g_unk_010b3c68 != 0) {
                local_2c = local_2c + (tmp_i12 == *(int *)(cgs + g_unk_010b3c64 * 0x1a4 + 0x9494));
              }
              if (g_unk_010b3cb8 != 0) {
                local_2c = local_2c + (tmp_i12 == *(int *)(cgs + g_unk_010b3cb4 * 0x1a4 + 0x9494));
              }
              if (g_unk_010b3d08 != 0) {
                local_2c = local_2c + (tmp_i12 == *(int *)(cgs + g_unk_010b3d04 * 0x1a4 + 0x9494));
              }
              if (g_unk_010b3d58 != 0) {
                local_2c = local_2c + (tmp_i12 == *(int *)(cgs + g_unk_010b3d54 * 0x1a4 + 0x9494));
              }
              if (g_unk_010b3da8 != 0) {
                local_2c = local_2c + (tmp_i12 == *(int *)(cgs + g_unk_010b3da4 * 0x1a4 + 0x9494));
              }
              if (g_unk_010b3df8 != 0) {
                local_2c = local_2c + (tmp_i12 == *(int *)(cgs + g_unk_010b3df4 * 0x1a4 + 0x9494));
              }
              if (g_unk_010b3e48 != 0) {
                local_2c = local_2c + (tmp_i12 == *(int *)(cgs + g_unk_010b3e44 * 0x1a4 + 0x9494));
              }
              if ((g_unk_010b3e98 == 0) || (tmp_i12 != *(int *)(cgs + g_unk_010b3e94 * 0x1a4 + 0x9494)))
              {
                if (g_unk_010b3ee8 != 0) goto LAB_00079eed;
              }
              else {
                local_2c = local_2c + 1;
                if (g_unk_010b3ee8 == 0) goto LAB_00079f20;
LAB_00079eed:
                if (tmp_i12 == *(int *)(cgs + g_unk_010b3ee4 * 0x1a4 + 0x9494)) goto LAB_00079f20;
              }
              if (local_2c != 0) goto LAB_00079f20;
            }
            tmp_i12 = 1;
          }
          else {
LAB_00079f20:
            if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
              tmp_u4 = va("%s. %s",(&g_unk_00144bc4)[tmp_i11],tmp_pu5);
            }
            else {
              tmp_u4 = va("%i. %s",tmp_i11 % 10,tmp_pu5);
            }
            tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
            CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_34,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,
                              tmp_u4,0,0,tmp_pu2[6],tmp_pu2[8]);
            local_34 = local_34 + *(float *)(param_1 + 0x14);
            tmp_i12 = tmp_i11;
          }
          tmp_i11 = tmp_i11 + 1;
          tmp_pu5 = (&ftOffMenuList)[tmp_i12];
        } while (tmp_pu5 != (uint8_t *)0x0);
      }
    }
    else {
      tmp_i11 = CG_IsFireTeamLeader(g_unk_01047ac4);
      if (tmp_i11 == 0) {
        if (ftOnMenuList != (uint8_t *)0x0) {
          tmp_i11 = 1;
          do {
            if (tmp_i11 == 1) {
              tmp_pu10 = cgs;
              local_30 = GHIDRA_FIELD(cgs, 27400, 4);
              if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
                local_28 = 0;
                tmp_i12 = 0;
                do {
                  if (((g_unk_01047ac4 != tmp_i12) && (*(int *)(tmp_pu10 + 0x940c) != 0)) &&
                     (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu10 + 0x9494)))
                  {
                    tmp_i8 = CG_IsOnFireteam(tmp_i12);
                    if (tmp_i8 == 0) {
                      local_28 = local_28 + 1;
                    }
                    local_30 = GHIDRA_FIELD(cgs, 27400, 4);
                  }
                  tmp_i12 = tmp_i12 + 1;
                  tmp_pu10 = tmp_pu10 + 0x1a4;
                } while (tmp_i12 < local_30);
                if (local_28 != 0) goto LAB_0007a236;
              }
              tmp_i12 = 1;
            }
            else {
LAB_0007a236:
              if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
                tmp_u4 = va("%s. %s",*(uint32_t *)(tmp_i11 * 4 + 0x144bac),
                           *(uint32_t *)(tmp_i11 * 4 + 0x144bb8));
              }
              else {
                tmp_u4 = va("%i. %s",tmp_i11 % 10,*(uint32_t *)(tmp_i11 * 4 + 0x144bb8));
              }
              tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
              CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_34,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,
                                tmp_u4,0,0,tmp_pu2[6],tmp_pu2[8]);
              local_34 = local_34 + *(float *)(param_1 + 0x14);
              tmp_i12 = tmp_i11;
            }
            tmp_i11 = tmp_i11 + 1;
          } while ((&ftOnMenuList)[tmp_i12] != (uint8_t *)0x0);
        }
      }
      else if (ftLeaderMenuList != (uint8_t *)0x0) {
        tmp_i11 = 1;
        do {
          tmp_i12 = tmp_i11;
          if (tmp_i11 == 3) {
            tmp_pu10 = cgs;
            local_30 = GHIDRA_FIELD(cgs, 27400, 4);
            tmp_i12 = 3;
            if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
              local_24 = 0;
              tmp_i12 = 0;
              do {
                if (((g_unk_01047ac4 != tmp_i12) && (*(int *)(tmp_pu10 + 0x940c) != 0)) &&
                   (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu10 + 0x9494))) {
                  tmp_i8 = CG_IsOnFireteam(tmp_i12);
                  if (tmp_i8 == 0) {
                    local_24 = local_24 + 1;
                  }
                  local_30 = GHIDRA_FIELD(cgs, 27400, 4);
                }
                tmp_i12 = tmp_i12 + 1;
                tmp_pu10 = tmp_pu10 + 0x1a4;
              } while (tmp_i12 < local_30);
              tmp_i12 = 3;
joined_r0x00079b60:
              if (local_24 != 0) goto LAB_000798ed;
            }
          }
          else if (tmp_i11 - 4U < 2) {
            tmp_pu10 = cgs;
            if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
              local_30 = 0;
              tmp_i9 = 0;
              tmp_i8 = GHIDRA_FIELD(cgs, 27400, 4);
              do {
                if (((g_unk_01047ac4 != tmp_i9) && (*(int *)(tmp_pu10 + 0x940c) != 0)) &&
                   (*(int *)(tmp_pu10 + 0x9494) == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) {
                  tmp_i6 = CG_IsOnFireteam(tmp_i9);
                  tmp_i7 = CG_IsOnFireteam(g_unk_01047ac4);
                  tmp_i8 = GHIDRA_FIELD(cgs, 27400, 4);
                  if (tmp_i6 == tmp_i7) {
                    local_30 = local_30 + 1;
                  }
                }
                tmp_i9 = tmp_i9 + 1;
                tmp_pu10 = tmp_pu10 + 0x1a4;
                local_24 = local_30;
              } while (tmp_i9 < tmp_i8);
              goto joined_r0x00079b60;
            }
          }
          else {
LAB_000798ed:
            if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
              tmp_u4 = va("%s. %s",*(uint32_t *)(tmp_i11 * 4 + 0x144b7c),
                         *(uint32_t *)(tmp_i11 * 4 + 0x144b94));
            }
            else {
              tmp_u4 = va("%i. %s",tmp_i11 % 10,*(uint32_t *)(tmp_i11 * 4 + 0x144b94));
            }
            tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
            CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),local_34,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,
                              tmp_u4,0,0,tmp_pu2[6],tmp_pu2[8]);
            local_34 = local_34 + *(float *)(param_1 + 0x14);
            tmp_i12 = tmp_i11;
          }
          tmp_i11 = tmp_i11 + 1;
        } while ((&ftLeaderMenuList)[tmp_i12] != (uint8_t *)0x0);
      }
    }
    break;
  case 2:
    tmp_i11 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
    if (1 < tmp_i11 - 1U) {
      GHIDRA_FIELD(cgs, 33701700, 4) = 1;
      return;
    }
    local_34 = 0.0;
    if (g_unk_010b3b78 != 0) {
      local_34 = (float)(uint)(tmp_i11 == *(int *)(cgs + g_unk_010b3b74 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3bc8 != 0) {
      local_34 = (float)((int)local_34 +
                        (uint)(tmp_i11 == *(int *)(cgs + g_unk_010b3bc4 * 0x1a4 + 0x9494)));
    }
    if (g_unk_010b3c18 != 0) {
      local_34 = (float)((int)local_34 +
                        (uint)(tmp_i11 == *(int *)(cgs + g_unk_010b3c14 * 0x1a4 + 0x9494)));
    }
    if (g_unk_010b3c68 != 0) {
      local_34 = (float)((int)local_34 +
                        (uint)(tmp_i11 == *(int *)(cgs + g_unk_010b3c64 * 0x1a4 + 0x9494)));
    }
    if (g_unk_010b3cb8 != 0) {
      local_34 = (float)((int)local_34 +
                        (uint)(tmp_i11 == *(int *)(cgs + g_unk_010b3cb4 * 0x1a4 + 0x9494)));
    }
    if (g_unk_010b3d08 != 0) {
      local_34 = (float)((int)local_34 +
                        (uint)(tmp_i11 == *(int *)(cgs + g_unk_010b3d04 * 0x1a4 + 0x9494)));
    }
    if (g_unk_010b3d58 != 0) {
      local_34 = (float)((int)local_34 +
                        (uint)(tmp_i11 == *(int *)(cgs + g_unk_010b3d54 * 0x1a4 + 0x9494)));
    }
    if (g_unk_010b3da8 != 0) {
      local_34 = (float)((int)local_34 +
                        (uint)(tmp_i11 == *(int *)(cgs + g_unk_010b3da4 * 0x1a4 + 0x9494)));
    }
    if (g_unk_010b3df8 != 0) {
      local_34 = (float)((int)local_34 +
                        (uint)(tmp_i11 == *(int *)(cgs + g_unk_010b3df4 * 0x1a4 + 0x9494)));
    }
    if (g_unk_010b3e48 != 0) {
      local_34 = (float)((int)local_34 +
                        (uint)(tmp_i11 == *(int *)(cgs + g_unk_010b3e44 * 0x1a4 + 0x9494)));
    }
    if ((g_unk_010b3e98 == 0) || (tmp_i11 != *(int *)(cgs + g_unk_010b3e94 * 0x1a4 + 0x9494))) {
      if (g_unk_010b3ee8 != 0) goto LAB_000795ff;
    }
    else {
      local_34 = (float)((int)local_34 + 1);
      if (g_unk_010b3ee8 == 0) goto LAB_00079624;
LAB_000795ff:
      if (tmp_i11 == *(int *)(cgs + g_unk_010b3ee4 * 0x1a4 + 0x9494)) goto LAB_00079624;
    }
    if (local_34 == 0.0) {
      GHIDRA_FIELD(cgs, 33701700, 4) = 1;
      return;
    }
LAB_00079624:
    tmp_i11 = CG_IsOnFireteam(g_unk_01047ac4);
    if (tmp_i11 != 0) {
      GHIDRA_FIELD(cgs, 33701700, 4) = 1;
      return;
    }
    CG_DrawFireteamsByTeam(param_1,*(uint32_t *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494));
    return;
  case 3:
    tmp_pu10 = cgs;
    local_34 = (float)GHIDRA_FIELD(cgs, 27400, 4);
    if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
      GHIDRA_FIELD(cgs, 33701700, 4) = 1;
      return;
    }
    local_30 = 0;
    tmp_i11 = 0;
    do {
      if (((g_unk_01047ac4 != tmp_i11) && (*(int *)(tmp_pu10 + 0x940c) != 0)) &&
         (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu10 + 0x9494))) {
        tmp_i12 = CG_IsOnFireteam(tmp_i11);
        if (tmp_i12 == 0) {
          local_30 = local_30 + 1;
        }
        local_34 = (float)GHIDRA_FIELD(cgs, 27400, 4);
      }
      tmp_i11 = tmp_i11 + 1;
      tmp_pu10 = tmp_pu10 + 0x1a4;
    } while (tmp_i11 < (int)local_34);
    goto LAB_000796dd;
  case 4:
    if (GHIDRA_FIELD(cgs, 33701696, 4) != 2) {
      if ((int)GHIDRA_FIELD(cgs, 33701696, 4) < 2) {
        return;
      }
      if (4 < (int)GHIDRA_FIELD(cgs, 33701696, 4)) {
        return;
      }
      tmp_pu10 = cgs;
      if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
        GHIDRA_FIELD(cgs, 33701700, 4) = 1;
        return;
      }
      local_34 = 0.0;
      tmp_i12 = 0;
      tmp_i11 = GHIDRA_FIELD(cgs, 27400, 4);
      do {
        if (((g_unk_01047ac4 != tmp_i12) && (*(int *)(tmp_pu10 + 0x940c) != 0)) &&
           (*(int *)(tmp_pu10 + 0x9494) == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) {
          tmp_i8 = CG_IsOnFireteam(tmp_i12);
          tmp_i9 = CG_IsOnFireteam(g_unk_01047ac4);
          tmp_i11 = GHIDRA_FIELD(cgs, 27400, 4);
          if (tmp_i8 == tmp_i9) {
            local_34 = (float)((int)local_34 + 1);
          }
        }
        tmp_i12 = tmp_i12 + 1;
        tmp_pu10 = tmp_pu10 + 0x1a4;
      } while (tmp_i12 < tmp_i11);
      if (local_34 == 0.0) {
        GHIDRA_FIELD(cgs, 33701700, 4) = 1;
        return;
      }
      CG_DrawPlayerSF(param_1,0x3113da8);
      return;
    }
    tmp_pu10 = cgs;
    local_34 = (float)GHIDRA_FIELD(cgs, 27400, 4);
    if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
      GHIDRA_FIELD(cgs, 33701700, 4) = 1;
      return;
    }
    local_30 = 0;
    tmp_i11 = 0;
    do {
      if (((g_unk_01047ac4 != tmp_i11) && (*(int *)(tmp_pu10 + 0x940c) != 0)) &&
         (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu10 + 0x9494))) {
        tmp_i12 = CG_IsOnFireteam(tmp_i11);
        if (tmp_i12 == 0) {
          local_30 = local_30 + 1;
        }
        local_34 = (float)GHIDRA_FIELD(cgs, 27400, 4);
      }
      tmp_i11 = tmp_i11 + 1;
      tmp_pu10 = tmp_pu10 + 0x1a4;
    } while (tmp_i11 < (int)local_34);
LAB_000796dd:
    if (local_30 == 0) {
      GHIDRA_FIELD(cgs, 33701700, 4) = 1;
      return;
    }
    CG_DrawPlayerNF(param_1,0x3113da8);
  }
  return;
}

void CG_Fireteams_Setup(void)
{
  BG_PanelButtonsSetup(fireteamButtons);
  return;
}

void CG_Fireteams_KeyHandling(uint param_1,int param_2)
{
  __int32_t *p_Var1;
  int *tmp_pi2;
  int tmp_i3;
  char *tmp_pc4;
  __int32_t **pp_Var5;
  uint32_t tmp_u6;
  uint32_t tmp_u7;
  int tmp_i8;
  int tmp_i9;
  uint8_t **tmp_ppu10;
  uint8_t *tmp_pu11;
  int tmp_i12;
  bool tmp_b13;
  bool tmp_b14;
  int local_2c;
  int local_28;
  int local_24;
  
  tmp_u7 = GHIDRA_FIELD(cgs, 33701696, 4);
  if (param_2 == 0 || param_1 == 0x1b) {
    return;
  }
  if ((param_1 & 0x400) != 0) {
    return;
  }
  param_1 = param_1 & 0xfffffbff;
  switch(GHIDRA_FIELD(cgs, 33701700, 4)) {
  case 0:
    if (GHIDRA_FIELD(cgs, 33701696, 4) == -1) {
      if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
        if (ftMenuRootStrings == (uint8_t *)0x0) {
          return;
        }
        pp_Var5 = __ctype_tolower_loc();
        p_Var1 = *pp_Var5;
        if (param_1 == p_Var1[(char)*ftMenuRootStringsAlphachars]) {
          tmp_u7 = 0;
LAB_0007b778:
          tmp_i3 = CG_FireteamHasClass(tmp_u7,1);
          if (tmp_i3 != 0) {
            GHIDRA_FIELD(cgs, 33701696, 4) = tmp_u7;
            return;
          }
          return;
        }
        if (g_ptr_s_Medic_00118582_0xd_00144de4 == (uint8_t *)0x0) {
          return;
        }
        if (param_1 == p_Var1[(char)*g_ptr_s_M_00116922_0xc_00144d64]) {
          tmp_u7 = 1;
          goto LAB_0007b778;
        }
        if (g_ptr_s_Engineer_001218b2_5_00144de8 == (uint8_t *)0x0) {
          return;
        }
        if (param_1 == p_Var1[(char)*g_ptr_s_E_00114a93_0x10_00144d68]) {
          tmp_u7 = 2;
          goto LAB_0007b778;
        }
        if (g_ptr_s_Field_Ops_00144dec == (uint8_t *)0x0) {
          return;
        }
        if (param_1 == p_Var1[(char)*g_ptr_s_F_00120566_0xf_00144d6c]) {
          tmp_u7 = 3;
          goto LAB_0007b778;
        }
        if (g_ptr_s_Covert_Ops_00144df0 == (uint8_t *)0x0) {
          return;
        }
        if (param_1 == p_Var1[(char)*g_ptr_DAT_00144d70]) {
          tmp_u7 = 4;
          goto LAB_0007b778;
        }
        if (g_ptr_s_General_0010d33a_0xa_00144df4 == (uint8_t *)0x0) {
          return;
        }
        if (param_1 == p_Var1[(char)*g_ptr_s_G_0010c134_0xa_00144d74]) goto LAB_0007b657;
        if (g_ptr_s_Attack_00115e81_2_00144df8 == (uint8_t *)0x0) {
          return;
        }
        if (param_1 == p_Var1[(char)*g_ptr_DAT_00144d78]) {
          tmp_i3 = 6;
        }
        else {
          if (g_ptr_s_Fall_Back_00144dfc == (uint8_t *)0x0) {
            return;
          }
          if (param_1 == p_Var1[(char)*g_ptr_s_B_0010dfdf_9_00144d7c]) {
            tmp_i3 = 7;
          }
          else {
            if (g_unk_00144e00 == 0) {
              return;
            }
            tmp_i3 = 8;
          }
        }
        tmp_u7 = *(uint32_t *)(ftMenuRootStringsMsg + tmp_i3 * 4);
      }
      else {
        if (9 < param_1 - 0x30) {
          return;
        }
        tmp_i3 = (int)(param_1 - 0x27) % 10;
        if (tmp_i3 < 5) {
          tmp_i12 = CG_FireteamHasClass(tmp_i3,1);
          if (tmp_i12 != 0) {
            GHIDRA_FIELD(cgs, 33701696, 4) = tmp_i3;
            return;
          }
          return;
        }
        if (7 < tmp_i3) {
          return;
        }
        if (tmp_i3 == 5) {
LAB_0007b657:
          CG_QuickFireteamMessage_f();
          return;
        }
        tmp_u7 = *(uint32_t *)(ftMenuRootStringsMsg + tmp_i3 * 4);
      }
      tmp_u6 = CG_BuildSelectedFirteamString();
      tmp_u7 = va("vsay_buddy -1 %s %s",tmp_u6,tmp_u7);
    }
    else {
      if (4 < (uint)GHIDRA_FIELD(cgs, 33701696, 4)) {
        return;
      }
      if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
        tmp_pi2 = *(int **)(ftMenuStrings + GHIDRA_FIELD(cgs, 33701696, 4) * 4);
        if (*tmp_pi2 == 0) {
          return;
        }
        pp_Var5 = __ctype_tolower_loc();
        tmp_i3 = 0;
        while (param_1 !=
               (*pp_Var5)[**(char **)(*(int *)(ftMenuStringsAlphachars + tmp_u7 * 4) + tmp_i3)]) {
          tmp_i3 = tmp_i3 + 4;
          if (*(int *)((int)tmp_pi2 + tmp_i3) == 0) {
            return;
          }
        }
        tmp_u7 = *(uint32_t *)(*(int *)(ftMenuStringsMsg + tmp_u7 * 4) + tmp_i3);
      }
      else {
        if (9 < param_1 - 0x30) {
          return;
        }
        tmp_i3 = (int)(param_1 - 0x27) % 10;
        if (**(int **)(ftMenuStrings + GHIDRA_FIELD(cgs, 33701696, 4) * 4) == 0) {
          return;
        }
        if (tmp_i3 != 0) {
          tmp_i12 = 0;
          do {
            tmp_i12 = tmp_i12 + 1;
            if ((*(int **)(ftMenuStrings + GHIDRA_FIELD(cgs, 33701696, 4) * 4))[tmp_i12] == 0) {
              return;
            }
          } while (tmp_i3 != tmp_i12);
        }
        tmp_u7 = *(uint32_t *)(*(int *)(ftMenuStringsMsg + GHIDRA_FIELD(cgs, 33701696, 4) * 4) + tmp_i3 * 4);
      }
      tmp_u6 = CG_BuildSelectedFirteamString();
      tmp_u7 = va("vsay_buddy %i %s %s",GHIDRA_FIELD(cgs, 33701696, 4),tmp_u6,tmp_u7);
    }
    trap_SendClientCommand(tmp_u7);
    CG_EventHandling(0,0);
    return;
  case 1:
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      tmp_i3 = CG_IsOnFireteam(g_unk_01047ac4);
      if (tmp_i3 == 0) {
        tmp_ppu10 = &ftOffMenuListAlphachars;
      }
      else {
        tmp_i3 = CG_IsFireTeamLeader(g_unk_01047ac4);
        if (tmp_i3 == 0) {
          tmp_ppu10 = &ftOnMenuListAlphachars;
        }
        else {
          tmp_ppu10 = &ftLeaderMenuListAlphachars;
        }
      }
      tmp_pc4 = *tmp_ppu10;
      if (tmp_pc4 == (char *)0x0) {
        return;
      }
      pp_Var5 = __ctype_tolower_loc();
      tmp_i3 = 0;
      while (param_1 != (*pp_Var5)[*tmp_pc4]) {
        tmp_i3 = tmp_i3 + 1;
        tmp_pc4 = tmp_ppu10[tmp_i3];
        if (tmp_pc4 == (char *)0x0) {
          return;
        }
      }
    }
    else {
      if (9 < param_1 - 0x30) {
        return;
      }
      tmp_i3 = (int)(param_1 - 0x27) % 10;
    }
    tmp_i12 = CG_IsOnFireteam(g_unk_01047ac4);
    if (tmp_i12 == 0) {
      if (1 < tmp_i3) {
        return;
      }
      if (tmp_i3 == 0) {
        if (1 < *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) - 1U) {
          return;
        }
        tmp_i3 = CG_CountFireteamsByTeam_part_0();
        if (tmp_i3 != 0) {
          GHIDRA_FIELD(cgs, 33701696, 4) = 0;
          GHIDRA_FIELD(cgs, 33701700, 4) = 2;
          GHIDRA_FIELD(cgs, 33701704, 4) = 0;
          return;
        }
        return;
      }
      tmp_pc4 = "fireteam create\n";
    }
    else {
      tmp_i12 = CG_IsFireTeamLeader(g_unk_01047ac4);
      if (tmp_i12 == 0) {
        if (1 < tmp_i3) {
          return;
        }
        if (tmp_i3 == 0) {
          tmp_i3 = CG_CountPlayersNF();
          if (tmp_i3 != 0) {
            GHIDRA_FIELD(cgs, 33701696, 4) = 0;
            GHIDRA_FIELD(cgs, 33701700, 4) = 3;
            GHIDRA_FIELD(cgs, 33701704, 4) = 0;
            return;
          }
          return;
        }
      }
      else {
        if (4 < tmp_i3) {
          return;
        }
        if (tmp_i3 == 2) {
          tmp_i12 = CG_CountPlayersNF();
joined_r0x0007b5f2:
          if (tmp_i12 != 0) {
            GHIDRA_FIELD(cgs, 33701696, 4) = tmp_i3;
            GHIDRA_FIELD(cgs, 33701700, 4) = 4;
            GHIDRA_FIELD(cgs, 33701704, 4) = 0;
            return;
          }
          return;
        }
        if (tmp_i3 - 3U < 2) {
          tmp_i12 = CG_CountPlayersSF();
          goto joined_r0x0007b5f2;
        }
        if (tmp_i3 == 0) {
          tmp_pc4 = "fireteam disband\n";
          break;
        }
        if (tmp_i3 != 1) {
          GHIDRA_FIELD(cgs, 33701696, 4) = tmp_i3;
          GHIDRA_FIELD(cgs, 33701700, 4) = 4;
          GHIDRA_FIELD(cgs, 33701704, 4) = 0;
          return;
        }
      }
      tmp_pc4 = "fireteam leave\n";
    }
    break;
  case 2:
    tmp_i3 = (int)(param_1 - 0x27) % 10;
    if (param_1 - 0x30 < 10) {
      if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) goto LAB_0007a53d;
      if (((g_unk_010b3b78 == 0) ||
          (*(int *)(cgs + g_unk_010b3b74 * 0x1a4 + 0x9494) !=
           *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i3 != g_unk_010b3b30)) {
        if (((g_unk_010b3bc8 == 0) ||
            (*(int *)(cgs + g_unk_010b3bc4 * 0x1a4 + 0x9494) !=
             *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i3 != g_unk_010b3b80)) {
          if (((g_unk_010b3c18 == 0) ||
              (*(int *)(cgs + g_unk_010b3c14 * 0x1a4 + 0x9494) !=
               *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i3 != g_unk_010b3bd0)) {
            if (((g_unk_010b3c68 == 0) ||
                (*(int *)(cgs + g_unk_010b3c64 * 0x1a4 + 0x9494) !=
                 *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i3 != g_unk_010b3c20)) {
              if (((g_unk_010b3cb8 == 0) ||
                  (*(int *)(cgs + g_unk_010b3cb4 * 0x1a4 + 0x9494) !=
                   *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i3 != g_unk_010b3c70)) {
                if (((g_unk_010b3d08 == 0) ||
                    (*(int *)(cgs + g_unk_010b3d04 * 0x1a4 + 0x9494) !=
                     *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i3 != g_unk_010b3cc0)) {
                  if (((g_unk_010b3d58 == 0) ||
                      (*(int *)(cgs + g_unk_010b3d54 * 0x1a4 + 0x9494) !=
                       *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i3 != g_unk_010b3d10)) {
                    if (((g_unk_010b3da8 == 0) ||
                        (*(int *)(cgs + g_unk_010b3da4 * 0x1a4 + 0x9494) !=
                         *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i3 != g_unk_010b3d60))
                    {
                      if (((g_unk_010b3df8 == 0) ||
                          (*(int *)(cgs + g_unk_010b3df4 * 0x1a4 + 0x9494) !=
                           *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                         (tmp_i3 != g_unk_010b3db0)) {
                        if (((g_unk_010b3e48 == 0) ||
                            (*(int *)(cgs + g_unk_010b3e44 * 0x1a4 + 0x9494) !=
                             *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                           (tmp_i3 != g_unk_010b3e00)) {
                          if (((g_unk_010b3e98 == 0) ||
                              (*(int *)(cgs + g_unk_010b3e94 * 0x1a4 + 0x9494) !=
                               *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                             (tmp_i3 != g_unk_010b3e50)) {
                            if (g_unk_010b3ee8 == 0) {
                              return;
                            }
                            if (*(int *)(cgs + g_unk_010b3ee4 * 0x1a4 + 0x9494) !=
                                *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494)) {
                              return;
                            }
                            goto joined_r0x0007aebe;
                          }
                          goto LAB_0007b5cf;
                        }
                        goto LAB_0007b5b4;
                      }
                      goto LAB_0007b50f;
                    }
                    goto LAB_0007b4ef;
                  }
                  goto LAB_0007b4cf;
                }
                goto LAB_0007b4af;
              }
              goto LAB_0007b490;
            }
            goto LAB_0007b45f;
          }
          goto LAB_0007b43f;
        }
        goto LAB_0007b52f;
      }
LAB_0007b422:
      tmp_i3 = 0;
    }
    else {
      if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) != 0) {
        return;
      }
LAB_0007a53d:
      if (((g_unk_010b3b78 != 0) &&
          (*(int *)(cgs + g_unk_010b3b74 * 0x1a4 + 0x9494) ==
           *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) && (param_1 - 0x61 == g_unk_010b3b30))
      goto LAB_0007b422;
      if (((g_unk_010b3bc8 == 0) ||
          (*(int *)(cgs + g_unk_010b3bc4 * 0x1a4 + 0x9494) !=
           *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (param_1 - 0x61 != g_unk_010b3b80)) {
        if (((g_unk_010b3c18 == 0) ||
            (*(int *)(cgs + g_unk_010b3c14 * 0x1a4 + 0x9494) !=
             *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (param_1 - 0x61 != g_unk_010b3bd0)) {
          if (((g_unk_010b3c68 == 0) ||
              (*(int *)(cgs + g_unk_010b3c64 * 0x1a4 + 0x9494) !=
               *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (param_1 - 0x61 != g_unk_010b3c20))
          {
            if (((g_unk_010b3cb8 == 0) ||
                (*(int *)(cgs + g_unk_010b3cb4 * 0x1a4 + 0x9494) !=
                 *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (param_1 - 0x61 != g_unk_010b3c70)
               ) {
              if (((g_unk_010b3d08 == 0) ||
                  (*(int *)(cgs + g_unk_010b3d04 * 0x1a4 + 0x9494) !=
                   *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                 (param_1 - 0x61 != g_unk_010b3cc0)) {
                if (((g_unk_010b3d58 == 0) ||
                    (*(int *)(cgs + g_unk_010b3d54 * 0x1a4 + 0x9494) !=
                     *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                   (param_1 - 0x61 != g_unk_010b3d10)) {
                  if (((g_unk_010b3da8 == 0) ||
                      (*(int *)(cgs + g_unk_010b3da4 * 0x1a4 + 0x9494) !=
                       *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                     (param_1 - 0x61 != g_unk_010b3d60)) {
                    if (((g_unk_010b3df8 == 0) ||
                        (*(int *)(cgs + g_unk_010b3df4 * 0x1a4 + 0x9494) !=
                         *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                       (param_1 - 0x61 != g_unk_010b3db0)) {
                      if (((g_unk_010b3e48 == 0) ||
                          (*(int *)(cgs + g_unk_010b3e44 * 0x1a4 + 0x9494) !=
                           *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                         (param_1 - 0x61 != g_unk_010b3e00)) {
                        if (((g_unk_010b3e98 == 0) ||
                            (*(int *)(cgs + g_unk_010b3e94 * 0x1a4 + 0x9494) !=
                             *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                           (param_1 - 0x61 != g_unk_010b3e50)) {
                          if (g_unk_010b3ee8 == 0) {
                            return;
                          }
                          if (*(int *)(cgs + g_unk_010b3ee4 * 0x1a4 + 0x9494) !=
                              *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494)) {
                            return;
                          }
                          tmp_i3 = param_1 - 0x61;
joined_r0x0007aebe:
                          if (tmp_i3 != g_unk_010b3ea0) {
                            return;
                          }
                          tmp_i3 = 0xb;
                        }
                        else {
LAB_0007b5cf:
                          tmp_i3 = 10;
                        }
                      }
                      else {
LAB_0007b5b4:
                        tmp_i3 = 9;
                      }
                    }
                    else {
LAB_0007b50f:
                      tmp_i3 = 8;
                    }
                  }
                  else {
LAB_0007b4ef:
                    tmp_i3 = 7;
                  }
                }
                else {
LAB_0007b4cf:
                  tmp_i3 = 6;
                }
              }
              else {
LAB_0007b4af:
                tmp_i3 = 5;
              }
            }
            else {
LAB_0007b490:
              tmp_i3 = 4;
            }
          }
          else {
LAB_0007b45f:
            tmp_i3 = 3;
          }
        }
        else {
LAB_0007b43f:
          tmp_i3 = 2;
        }
      }
      else {
LAB_0007b52f:
        tmp_i3 = 1;
      }
    }
    tmp_pc4 = (char *)va("fireteam apply %i",tmp_i3 + 1);
    break;
  case 3:
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      if (param_1 != 0x6e) {
        if (param_1 == 0x70) {
          tmp_b14 = true;
          local_28 = 0;
          tmp_b13 = false;
        }
        else {
          local_28 = param_1 - 0x61;
          if (local_28 == -1) {
            return;
          }
          tmp_b13 = local_28 == 9;
          tmp_b14 = local_28 == 0;
        }
        goto LAB_0007a851;
      }
      if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
        tmp_b13 = true;
        tmp_b14 = false;
        local_28 = 9;
        goto LAB_0007a865;
      }
      tmp_b13 = true;
      local_28 = 9;
    }
    else {
      if (9 < param_1 - 0x30) {
        return;
      }
      local_28 = (int)(param_1 - 0x27) % 10;
      tmp_b13 = local_28 == 9;
      tmp_b14 = local_28 == 0;
LAB_0007a851:
      if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
        local_24 = 0;
      }
      else {
LAB_0007a865:
        tmp_pu11 = cgs;
        local_24 = 0;
        tmp_i12 = 0;
        tmp_i3 = GHIDRA_FIELD(cgs, 27400, 4);
        do {
          if ((((g_unk_01047ac4 != tmp_i12) && (*(int *)(tmp_pu11 + 0x940c) != 0)) &&
              (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu11 + 0x9494))) &&
             (tmp_i8 = CG_IsOnFireteam(tmp_i12), tmp_i3 = GHIDRA_FIELD(cgs, 27400, 4), tmp_i8 == 0)) {
            local_24 = local_24 + 1;
          }
          tmp_i12 = tmp_i12 + 1;
          tmp_pu11 = tmp_pu11 + 0x1a4;
        } while (tmp_i12 < tmp_i3);
      }
      if (((GHIDRA_FIELD(cgs, 33701704, 4) + 1) * 8 < local_24) && (tmp_b14)) {
        GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + 1;
      }
    }
    if ((GHIDRA_FIELD(cgs, 33701704, 4) != 0) && (tmp_b13)) {
      GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + -1;
    }
    tmp_i3 = CG_PlayerNFFromPos(local_28,0x3113da8);
    if (tmp_i3 == -1) {
      return;
    }
    tmp_pc4 = (char *)va("fireteam propose %i",tmp_i3 + 1);
    break;
  case 4:
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      if (param_1 == 0x6e) {
        local_28 = 9;
      }
      else if (param_1 == 0x70) {
        local_28 = 8;
      }
      else {
        local_28 = param_1 - 0x61;
        if (local_28 == -1) {
          return;
        }
      }
    }
    else {
      if (9 < param_1 - 0x30) {
        return;
      }
      local_28 = (int)(param_1 - 0x27) % 10;
    }
    if (GHIDRA_FIELD(cgs, 33701696, 4) == 2) {
      tmp_pu11 = cgs;
      if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
        local_24 = 0;
      }
      else {
        local_24 = 0;
        tmp_i12 = 0;
        tmp_i3 = GHIDRA_FIELD(cgs, 27400, 4);
        do {
          if ((((g_unk_01047ac4 != tmp_i12) && (*(int *)(tmp_pu11 + 0x940c) != 0)) &&
              (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu11 + 0x9494))) &&
             (tmp_i8 = CG_IsOnFireteam(tmp_i12), tmp_i3 = GHIDRA_FIELD(cgs, 27400, 4), tmp_i8 == 0)) {
            local_24 = local_24 + 1;
          }
          tmp_i12 = tmp_i12 + 1;
          tmp_pu11 = tmp_pu11 + 0x1a4;
        } while (tmp_i12 < tmp_i3);
      }
      if (((GHIDRA_FIELD(cgs, 33701704, 4) + 1) * 8 < local_24) && (local_28 == 9)) {
        GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + 1;
        return;
      }
      if ((local_28 == 8) && (GHIDRA_FIELD(cgs, 33701704, 4) != 0)) {
        GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + -1;
        return;
      }
      tmp_i3 = CG_PlayerNFFromPos(local_28,0x3113da8);
      if (tmp_i3 == -1) {
        return;
      }
      tmp_pc4 = (char *)va("fireteam invite %i",tmp_i3 + 1);
    }
    else {
      if ((int)GHIDRA_FIELD(cgs, 33701696, 4) < 2) {
        return;
      }
      if (4 < (int)GHIDRA_FIELD(cgs, 33701696, 4)) {
        return;
      }
      tmp_pu11 = cgs;
      local_2c = 0;
      if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
        local_2c = 0;
        tmp_i12 = 0;
        tmp_i3 = GHIDRA_FIELD(cgs, 27400, 4);
        do {
          if (((g_unk_01047ac4 != tmp_i12) && (*(int *)(tmp_pu11 + 0x940c) != 0)) &&
             (*(int *)(tmp_pu11 + 0x9494) == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) {
            tmp_i8 = CG_IsOnFireteam(tmp_i12);
            tmp_i9 = CG_IsOnFireteam(g_unk_01047ac4);
            tmp_i3 = GHIDRA_FIELD(cgs, 27400, 4);
            if (tmp_i8 == tmp_i9) {
              local_2c = local_2c + 1;
            }
          }
          tmp_i12 = tmp_i12 + 1;
          tmp_pu11 = tmp_pu11 + 0x1a4;
        } while (tmp_i12 < tmp_i3);
      }
      if (((GHIDRA_FIELD(cgs, 33701704, 4) + 1) * 8 < local_2c) && (local_28 == 0)) {
        GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + 1;
      }
      if ((GHIDRA_FIELD(cgs, 33701704, 4) != 0) && (local_28 == 9)) {
        GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + -1;
      }
      tmp_i3 = CG_PlayerSFFromPos(local_28,0x3113da8);
      if (tmp_i3 == -1) {
        return;
      }
      if (GHIDRA_FIELD(cgs, 33701696, 4) == 3) {
        tmp_pc4 = "fireteam kick %i";
      }
      else {
        if (GHIDRA_FIELD(cgs, 33701696, 4) != 4) {
          return;
        }
        tmp_pc4 = "fireteam warn %i";
      }
      tmp_pc4 = (char *)va(tmp_pc4,tmp_i3 + 1);
    }
    break;
  default:
    goto switchD_0007a4ed_default;
  }
  trap_SendConsoleCommand(tmp_pc4);
  CG_EventHandling(0,0);
switchD_0007a4ed_default:
  return;
}

void CG_Fireteams_Draw(void)
{
  BG_PanelButtonsRender(fireteamButtons);
  return;
}

uint32_t CG_FireteamCheckExecKey(uint param_1,int param_2)
{
  __int32_t *p_Var1;
  int *tmp_pi2;
  char *tmp_pc3;
  int tmp_i4;
  __int32_t **pp_Var5;
  uint32_t tmp_u6;
  uint32_t tmp_u7;
  int tmp_i8;
  int tmp_i9;
  uint8_t *tmp_pu10;
  int tmp_i11;
  bool tmp_b12;
  bool tmp_b13;
  uint8_t **local_34;
  int local_30;
  int local_2c;
  
  tmp_u7 = GHIDRA_FIELD(cgs, 33701696, 4);
  if (param_1 == 0x1b) {
    return 1;
  }
  if ((param_1 & 0x400) != 0) {
    return 0;
  }
  tmp_pu10 = cgs;
  param_1 = param_1 & 0xfffffbff;
  switch(GHIDRA_FIELD(cgs, 33701700, 4)) {
  case 0:
    if (GHIDRA_FIELD(cgs, 33701696, 4) == -1) {
      if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
        if (ftMenuRootStrings == (uint8_t *)0x0) {
          return 0;
        }
        pp_Var5 = __ctype_tolower_loc();
        p_Var1 = *pp_Var5;
        if (param_1 == p_Var1[(char)*ftMenuRootStringsAlphachars]) {
          tmp_u7 = 0;
LAB_0007cc4d:
          tmp_i4 = CG_FireteamHasClass(tmp_u7,1);
          if (tmp_i4 == 0) {
            return 0;
          }
          if (param_2 == 0) {
            return 1;
          }
          GHIDRA_FIELD(cgs, 33701696, 4) = tmp_u7;
          return 1;
        }
        if (g_ptr_s_Medic_00118582_0xd_00144de4 == (uint8_t *)0x0) {
          return 0;
        }
        if (param_1 == p_Var1[(char)*g_ptr_s_M_00116922_0xc_00144d64]) {
          tmp_u7 = 1;
          goto LAB_0007cc4d;
        }
        if (g_ptr_s_Engineer_001218b2_5_00144de8 == (uint8_t *)0x0) {
          return 0;
        }
        if (param_1 == p_Var1[(char)*g_ptr_s_E_00114a93_0x10_00144d68]) {
          tmp_u7 = 2;
          goto LAB_0007cc4d;
        }
        if (g_ptr_s_Field_Ops_00144dec == (uint8_t *)0x0) {
          return 0;
        }
        if (param_1 == p_Var1[(char)*g_ptr_s_F_00120566_0xf_00144d6c]) {
          tmp_u7 = 3;
          goto LAB_0007cc4d;
        }
        if (g_ptr_s_Covert_Ops_00144df0 == (uint8_t *)0x0) {
          return 0;
        }
        if (param_1 == p_Var1[(char)*g_ptr_DAT_00144d70]) {
          tmp_u7 = 4;
          goto LAB_0007cc4d;
        }
        if (g_ptr_s_General_0010d33a_0xa_00144df4 == (uint8_t *)0x0) {
          return 0;
        }
        if (param_1 == p_Var1[(char)*g_ptr_s_G_0010c134_0xa_00144d74]) {
          tmp_i4 = 5;
        }
        else {
          if (g_ptr_s_Attack_00115e81_2_00144df8 == (uint8_t *)0x0) {
            return 0;
          }
          if (param_1 == p_Var1[(char)*g_ptr_DAT_00144d78]) {
            tmp_i4 = 6;
          }
          else {
            if (g_ptr_s_Fall_Back_00144dfc == (uint8_t *)0x0) {
              return 0;
            }
            if (param_1 == p_Var1[(char)*g_ptr_s_B_0010dfdf_9_00144d7c]) {
              tmp_i4 = 7;
            }
            else {
              if (g_unk_00144e00 == 0) {
                return 0;
              }
              tmp_i4 = 8;
            }
          }
        }
        if (param_2 == 0) {
          return 1;
        }
        if (tmp_i4 == 5) goto LAB_0007cb33;
        tmp_u7 = *(uint32_t *)(ftMenuRootStringsMsg + tmp_i4 * 4);
      }
      else {
        if (9 < param_1 - 0x30) {
          return 0;
        }
        tmp_i4 = (int)(param_1 - 0x27) % 10;
        if (tmp_i4 < 5) {
          tmp_i11 = CG_FireteamHasClass(tmp_i4,1);
          if (tmp_i11 == 0) {
            return 0;
          }
          if (param_2 == 0) {
            return 1;
          }
          GHIDRA_FIELD(cgs, 33701696, 4) = tmp_i4;
          return 1;
        }
        if (7 < tmp_i4) {
          return 0;
        }
        if (param_2 == 0) {
          return 1;
        }
        if (tmp_i4 == 5) {
LAB_0007cb33:
          CG_QuickFireteamMessage_f();
          return 1;
        }
        tmp_u7 = *(uint32_t *)(ftMenuRootStringsMsg + tmp_i4 * 4);
      }
      tmp_u6 = CG_BuildSelectedFirteamString();
      tmp_u7 = va("vsay_buddy -1 %s %s",tmp_u6,tmp_u7);
    }
    else {
      if (4 < (uint)GHIDRA_FIELD(cgs, 33701696, 4)) {
        return 0;
      }
      if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
        tmp_pi2 = *(int **)(ftMenuStrings + GHIDRA_FIELD(cgs, 33701696, 4) * 4);
        if (*tmp_pi2 == 0) {
          return 0;
        }
        pp_Var5 = __ctype_tolower_loc();
        tmp_i4 = 0;
        while (param_1 !=
               (*pp_Var5)[**(char **)(*(int *)(ftMenuStringsAlphachars + tmp_u7 * 4) + tmp_i4)]) {
          tmp_i4 = tmp_i4 + 4;
          if (*(int *)((int)tmp_pi2 + tmp_i4) == 0) {
            return 0;
          }
        }
        if (param_2 == 0) {
          return 1;
        }
        tmp_u7 = *(uint32_t *)(*(int *)(ftMenuStringsMsg + tmp_u7 * 4) + tmp_i4);
      }
      else {
        if (9 < param_1 - 0x30) {
          return 0;
        }
        tmp_i4 = (int)(param_1 - 0x27) % 10;
        if (**(int **)(ftMenuStrings + GHIDRA_FIELD(cgs, 33701696, 4) * 4) == 0) {
          return 0;
        }
        if (tmp_i4 != 0) {
          tmp_i11 = 0;
          do {
            tmp_i11 = tmp_i11 + 1;
            if ((*(int **)(ftMenuStrings + GHIDRA_FIELD(cgs, 33701696, 4) * 4))[tmp_i11] == 0) {
              return 0;
            }
          } while (tmp_i4 != tmp_i11);
        }
        if (param_2 == 0) {
          return 1;
        }
        tmp_u7 = *(uint32_t *)(*(int *)(ftMenuStringsMsg + GHIDRA_FIELD(cgs, 33701696, 4) * 4) + tmp_i4 * 4);
      }
      tmp_u6 = CG_BuildSelectedFirteamString();
      tmp_u7 = va("vsay_buddy %i %s %s",GHIDRA_FIELD(cgs, 33701696, 4),tmp_u6,tmp_u7);
    }
    trap_SendClientCommand(tmp_u7);
    CG_EventHandling(0,0);
    return 1;
  case 1:
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      tmp_i4 = CG_IsOnFireteam(g_unk_01047ac4);
      if (tmp_i4 == 0) {
        local_34 = &ftOffMenuListAlphachars;
      }
      else {
        tmp_i4 = CG_IsFireTeamLeader(g_unk_01047ac4);
        if (tmp_i4 == 0) {
          local_34 = &ftOnMenuListAlphachars;
        }
        else {
          local_34 = &ftLeaderMenuListAlphachars;
        }
      }
      tmp_pc3 = *local_34;
      if (tmp_pc3 == (char *)0x0) {
        return 0;
      }
      pp_Var5 = __ctype_tolower_loc();
      tmp_i4 = 0;
      while (param_1 != (*pp_Var5)[*tmp_pc3]) {
        tmp_i4 = tmp_i4 + 1;
        tmp_pc3 = local_34[tmp_i4];
        if (tmp_pc3 == (char *)0x0) {
          return 0;
        }
      }
    }
    else {
      if (9 < param_1 - 0x30) {
        return 0;
      }
      tmp_i4 = (int)(param_1 - 0x27) % 10;
    }
    tmp_i11 = CG_IsOnFireteam(g_unk_01047ac4);
    if (tmp_i11 == 0) {
      if (1 < tmp_i4) {
        return 0;
      }
      if (tmp_i4 == 0) {
        if (1 < *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) - 1U) {
          return 0;
        }
        tmp_i4 = CG_CountFireteamsByTeam_part_0();
        if (tmp_i4 == 0) {
          return 0;
        }
        if (param_2 == 0) {
          return 1;
        }
        GHIDRA_FIELD(cgs, 33701696, 4) = 0;
        GHIDRA_FIELD(cgs, 33701700, 4) = 2;
        GHIDRA_FIELD(cgs, 33701704, 4) = 0;
        return 1;
      }
      if (param_2 == 0) {
        return 1;
      }
      tmp_pc3 = "fireteam create\n";
    }
    else {
      tmp_i11 = CG_IsFireTeamLeader(g_unk_01047ac4);
      if (tmp_i11 == 0) {
        if (1 < tmp_i4) {
          return 0;
        }
        if (tmp_i4 == 0) {
          tmp_i4 = CG_CountPlayersNF();
          if (tmp_i4 == 0) {
            return 0;
          }
          if (param_2 == 0) {
            return 1;
          }
          GHIDRA_FIELD(cgs, 33701696, 4) = 0;
          GHIDRA_FIELD(cgs, 33701700, 4) = 3;
          GHIDRA_FIELD(cgs, 33701704, 4) = 0;
          return 1;
        }
        if (param_2 == 0) {
          return 1;
        }
      }
      else {
        if (4 < tmp_i4) {
          return 0;
        }
        if (tmp_i4 == 2) {
          if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
            return 0;
          }
          local_30 = 0;
          tmp_i8 = 0;
          tmp_i11 = GHIDRA_FIELD(cgs, 27400, 4);
          do {
            if (((g_unk_01047ac4 != tmp_i8) && (*(int *)(tmp_pu10 + 0x940c) != 0)) &&
               ((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu10 + 0x9494) &&
                (tmp_i9 = CG_IsOnFireteam(tmp_i8), tmp_i11 = GHIDRA_FIELD(cgs, 27400, 4), tmp_i9 == 0)))) {
              local_30 = local_30 + 1;
            }
            tmp_i8 = tmp_i8 + 1;
            tmp_pu10 = tmp_pu10 + 0x1a4;
          } while (tmp_i8 < tmp_i11);
          if (local_30 == 0) {
            return 0;
          }
          if (param_2 == 0) {
            return 1;
          }
          GHIDRA_FIELD(cgs, 33701696, 4) = tmp_i4;
          GHIDRA_FIELD(cgs, 33701700, 4) = 4;
          GHIDRA_FIELD(cgs, 33701704, 4) = 0;
          return 1;
        }
        if ((tmp_i4 - 3U < 2) && (tmp_i11 = CG_CountPlayersSF(), tmp_i11 == 0)) {
          return 0;
        }
        if (param_2 == 0) {
          return 1;
        }
        tmp_pc3 = "fireteam disband\n";
        if (tmp_i4 == 0) goto LAB_0007bd98;
        if (tmp_i4 != 1) {
          GHIDRA_FIELD(cgs, 33701696, 4) = tmp_i4;
          GHIDRA_FIELD(cgs, 33701700, 4) = 4;
          GHIDRA_FIELD(cgs, 33701704, 4) = 0;
          return 1;
        }
      }
      tmp_pc3 = "fireteam leave\n";
    }
    goto LAB_0007bd98;
  case 2:
    tmp_i4 = (int)(param_1 - 0x27) % 10;
    if (param_1 - 0x30 < 10) {
      if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) goto LAB_0007b8d1;
      if (((g_unk_010b3b78 == 0) ||
          (*(int *)(cgs + g_unk_010b3b74 * 0x1a4 + 0x9494) !=
           *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i4 != g_unk_010b3b30)) {
        if (((g_unk_010b3bc8 == 0) ||
            (*(int *)(cgs + g_unk_010b3bc4 * 0x1a4 + 0x9494) !=
             *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i4 != g_unk_010b3b80)) {
          if (((g_unk_010b3c18 == 0) ||
              (*(int *)(cgs + g_unk_010b3c14 * 0x1a4 + 0x9494) !=
               *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i4 != g_unk_010b3bd0)) {
            if (((g_unk_010b3c68 == 0) ||
                (*(int *)(cgs + g_unk_010b3c64 * 0x1a4 + 0x9494) !=
                 *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i4 != g_unk_010b3c20)) {
              if (((g_unk_010b3cb8 == 0) ||
                  (*(int *)(cgs + g_unk_010b3cb4 * 0x1a4 + 0x9494) !=
                   *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i4 != g_unk_010b3c70)) {
                if (((g_unk_010b3d08 == 0) ||
                    (*(int *)(cgs + g_unk_010b3d04 * 0x1a4 + 0x9494) !=
                     *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i4 != g_unk_010b3cc0)) {
                  if (((g_unk_010b3d58 == 0) ||
                      (*(int *)(cgs + g_unk_010b3d54 * 0x1a4 + 0x9494) !=
                       *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i4 != g_unk_010b3d10)) {
                    if (((g_unk_010b3da8 == 0) ||
                        (*(int *)(cgs + g_unk_010b3da4 * 0x1a4 + 0x9494) !=
                         *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (tmp_i4 != g_unk_010b3d60))
                    {
                      if (((g_unk_010b3df8 == 0) ||
                          (*(int *)(cgs + g_unk_010b3df4 * 0x1a4 + 0x9494) !=
                           *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                         (tmp_i4 != g_unk_010b3db0)) {
                        if (((g_unk_010b3e48 == 0) ||
                            (*(int *)(cgs + g_unk_010b3e44 * 0x1a4 + 0x9494) !=
                             *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                           (tmp_i4 != g_unk_010b3e00)) {
                          if (((g_unk_010b3e98 == 0) ||
                              (*(int *)(cgs + g_unk_010b3e94 * 0x1a4 + 0x9494) !=
                               *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                             (tmp_i4 != g_unk_010b3e50)) {
                            if (g_unk_010b3ee8 == 0) {
                              return 0;
                            }
                            if (*(int *)(cgs + g_unk_010b3ee4 * 0x1a4 + 0x9494) !=
                                *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494)) {
                              return 0;
                            }
                            goto joined_r0x0007bd6e;
                          }
                          goto LAB_0007c91f;
                        }
                        goto LAB_0007c8ff;
                      }
                      goto LAB_0007c8df;
                    }
                    goto LAB_0007c8bf;
                  }
                  goto LAB_0007c89e;
                }
                goto LAB_0007c9df;
              }
              goto LAB_0007c9bf;
            }
            goto LAB_0007c99f;
          }
          goto LAB_0007c97f;
        }
        goto LAB_0007c95f;
      }
LAB_0007c93f:
      tmp_i4 = 0;
    }
    else {
      if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) != 0) {
        return 0;
      }
LAB_0007b8d1:
      if (((g_unk_010b3b78 != 0) &&
          (*(int *)(cgs + g_unk_010b3b74 * 0x1a4 + 0x9494) ==
           *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) && (param_1 - 0x61 == g_unk_010b3b30))
      goto LAB_0007c93f;
      if (((g_unk_010b3bc8 == 0) ||
          (*(int *)(cgs + g_unk_010b3bc4 * 0x1a4 + 0x9494) !=
           *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (param_1 - 0x61 != g_unk_010b3b80)) {
        if (((g_unk_010b3c18 == 0) ||
            (*(int *)(cgs + g_unk_010b3c14 * 0x1a4 + 0x9494) !=
             *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (param_1 - 0x61 != g_unk_010b3bd0)) {
          if (((g_unk_010b3c68 == 0) ||
              (*(int *)(cgs + g_unk_010b3c64 * 0x1a4 + 0x9494) !=
               *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (param_1 - 0x61 != g_unk_010b3c20))
          {
            if (((g_unk_010b3cb8 == 0) ||
                (*(int *)(cgs + g_unk_010b3cb4 * 0x1a4 + 0x9494) !=
                 *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) || (param_1 - 0x61 != g_unk_010b3c70)
               ) {
              if (((g_unk_010b3d08 == 0) ||
                  (*(int *)(cgs + g_unk_010b3d04 * 0x1a4 + 0x9494) !=
                   *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                 (param_1 - 0x61 != g_unk_010b3cc0)) {
                if (((g_unk_010b3d58 == 0) ||
                    (*(int *)(cgs + g_unk_010b3d54 * 0x1a4 + 0x9494) !=
                     *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                   (param_1 - 0x61 != g_unk_010b3d10)) {
                  if (((g_unk_010b3da8 == 0) ||
                      (*(int *)(cgs + g_unk_010b3da4 * 0x1a4 + 0x9494) !=
                       *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                     (param_1 - 0x61 != g_unk_010b3d60)) {
                    if (((g_unk_010b3df8 == 0) ||
                        (*(int *)(cgs + g_unk_010b3df4 * 0x1a4 + 0x9494) !=
                         *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                       (param_1 - 0x61 != g_unk_010b3db0)) {
                      if (((g_unk_010b3e48 == 0) ||
                          (*(int *)(cgs + g_unk_010b3e44 * 0x1a4 + 0x9494) !=
                           *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                         (param_1 - 0x61 != g_unk_010b3e00)) {
                        if (((g_unk_010b3e98 == 0) ||
                            (*(int *)(cgs + g_unk_010b3e94 * 0x1a4 + 0x9494) !=
                             *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) ||
                           (param_1 - 0x61 != g_unk_010b3e50)) {
                          if (g_unk_010b3ee8 == 0) {
                            return 0;
                          }
                          if (*(int *)(cgs + g_unk_010b3ee4 * 0x1a4 + 0x9494) !=
                              *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494)) {
                            return 0;
                          }
                          tmp_i4 = param_1 - 0x61;
joined_r0x0007bd6e:
                          if (tmp_i4 != g_unk_010b3ea0) {
LAB_0007bb12:
                            return 0;
                          }
                          tmp_i4 = 0xb;
                        }
                        else {
LAB_0007c91f:
                          tmp_i4 = 10;
                        }
                      }
                      else {
LAB_0007c8ff:
                        tmp_i4 = 9;
                      }
                    }
                    else {
LAB_0007c8df:
                      tmp_i4 = 8;
                    }
                  }
                  else {
LAB_0007c8bf:
                    tmp_i4 = 7;
                  }
                }
                else {
LAB_0007c89e:
                  tmp_i4 = 6;
                }
              }
              else {
LAB_0007c9df:
                tmp_i4 = 5;
              }
            }
            else {
LAB_0007c9bf:
              tmp_i4 = 4;
            }
          }
          else {
LAB_0007c99f:
            tmp_i4 = 3;
          }
        }
        else {
LAB_0007c97f:
          tmp_i4 = 2;
        }
      }
      else {
LAB_0007c95f:
        tmp_i4 = 1;
      }
    }
    if (param_2 == 0) {
      return 1;
    }
    tmp_i4 = tmp_i4 + 1;
    tmp_pc3 = "fireteam apply %i";
    break;
  case 3:
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      if (param_1 != 0x6e) {
        if (param_1 == 0x70) {
          tmp_b13 = true;
          tmp_b12 = false;
          local_30 = 0;
        }
        else {
          local_30 = param_1 - 0x61;
          if (local_30 == -1) {
            return 0;
          }
          tmp_b12 = local_30 == 9;
          tmp_b13 = local_30 == 0;
        }
        goto LAB_0007be20;
      }
      if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
        tmp_b13 = false;
        tmp_b12 = true;
        local_30 = 9;
        goto LAB_0007be2e;
      }
      tmp_b12 = true;
      local_30 = 9;
    }
    else {
      if (9 < param_1 - 0x30) {
        return 0;
      }
      local_30 = (int)(param_1 - 0x27) % 10;
      tmp_b12 = local_30 == 9;
      tmp_b13 = local_30 == 0;
LAB_0007be20:
      if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
        local_2c = 0;
      }
      else {
LAB_0007be2e:
        local_2c = 0;
        tmp_i11 = 0;
        tmp_i4 = GHIDRA_FIELD(cgs, 27400, 4);
        do {
          if ((((g_unk_01047ac4 != tmp_i11) && (*(int *)(tmp_pu10 + 0x940c) != 0)) &&
              (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu10 + 0x9494))) &&
             (tmp_i8 = CG_IsOnFireteam(tmp_i11), tmp_i4 = GHIDRA_FIELD(cgs, 27400, 4), tmp_i8 == 0)) {
            local_2c = local_2c + 1;
          }
          tmp_i11 = tmp_i11 + 1;
          tmp_pu10 = tmp_pu10 + 0x1a4;
        } while (tmp_i11 < tmp_i4);
      }
      if (((GHIDRA_FIELD(cgs, 33701704, 4) + 1) * 8 < local_2c) && (tmp_b13)) {
        GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + 1;
      }
    }
    if ((GHIDRA_FIELD(cgs, 33701704, 4) != 0) && (tmp_b12)) {
      GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + -1;
    }
    tmp_i4 = CG_PlayerNFFromPos(local_30,0x3113da8);
    if (tmp_i4 == -1) {
      return 0;
    }
    if (param_2 == 0) {
      return 1;
    }
    tmp_i4 = tmp_i4 + 1;
    tmp_pc3 = "fireteam propose %i";
    break;
  case 4:
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
      if (param_1 == 0x6e) {
        local_30 = 9;
      }
      else if (param_1 == 0x70) {
        local_30 = 8;
      }
      else {
        local_30 = param_1 - 0x61;
        if (local_30 == -1) {
          return 0;
        }
      }
    }
    else {
      if (9 < param_1 - 0x30) {
        return 0;
      }
      local_30 = (int)(param_1 - 0x27) % 10;
    }
    if (GHIDRA_FIELD(cgs, 33701696, 4) == 2) {
      if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
        local_2c = 0;
      }
      else {
        local_2c = 0;
        tmp_i11 = 0;
        tmp_i4 = GHIDRA_FIELD(cgs, 27400, 4);
        do {
          if ((((g_unk_01047ac4 != tmp_i11) && (*(int *)(tmp_pu10 + 0x940c) != 0)) &&
              (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu10 + 0x9494))) &&
             (tmp_i8 = CG_IsOnFireteam(tmp_i11), tmp_i4 = GHIDRA_FIELD(cgs, 27400, 4), tmp_i8 == 0)) {
            local_2c = local_2c + 1;
          }
          tmp_i11 = tmp_i11 + 1;
          tmp_pu10 = tmp_pu10 + 0x1a4;
        } while (tmp_i11 < tmp_i4);
      }
      if (((GHIDRA_FIELD(cgs, 33701704, 4) + 1) * 8 < local_2c) && (local_30 == 9)) {
        if (param_2 == 0) {
          return 1;
        }
        GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + 1;
        return 1;
      }
      if ((local_30 == 8) && (GHIDRA_FIELD(cgs, 33701704, 4) != 0)) {
        if (param_2 == 0) {
          return 1;
        }
        GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + -1;
        return 1;
      }
      tmp_i4 = CG_PlayerNFFromPos(local_30,0x3113da8);
      if (tmp_i4 == -1) {
        return 0;
      }
      if (param_2 == 0) {
        return 1;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pc3 = "fireteam invite %i";
    }
    else {
      if ((int)GHIDRA_FIELD(cgs, 33701696, 4) < 2) {
        return 0;
      }
      if (4 < (int)GHIDRA_FIELD(cgs, 33701696, 4)) {
        return 0;
      }
      if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
        local_34 = (uint8_t **)0x0;
      }
      else {
        local_34 = (uint8_t **)0x0;
        tmp_i11 = 0;
        tmp_i4 = GHIDRA_FIELD(cgs, 27400, 4);
        do {
          if (((g_unk_01047ac4 != tmp_i11) && (*(int *)(tmp_pu10 + 0x940c) != 0)) &&
             (*(int *)(tmp_pu10 + 0x9494) == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) {
            tmp_i8 = CG_IsOnFireteam(tmp_i11);
            tmp_i9 = CG_IsOnFireteam(g_unk_01047ac4);
            tmp_i4 = GHIDRA_FIELD(cgs, 27400, 4);
            if (tmp_i8 == tmp_i9) {
              local_34 = (uint8_t **)((int)local_34 + 1);
            }
          }
          tmp_i11 = tmp_i11 + 1;
          tmp_pu10 = tmp_pu10 + 0x1a4;
        } while (tmp_i11 < tmp_i4);
      }
      if (((GHIDRA_FIELD(cgs, 33701704, 4) + 1) * 8 < (int)local_34) && (local_30 == 0)) {
        GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + 1;
      }
      if ((GHIDRA_FIELD(cgs, 33701704, 4) != 0) && (local_30 == 9)) {
        GHIDRA_FIELD(cgs, 33701704, 4) = GHIDRA_FIELD(cgs, 33701704, 4) + -1;
      }
      tmp_i4 = CG_PlayerSFFromPos(local_30,0x3113da8);
      if (tmp_i4 == -1) {
        return 0;
      }
      if (param_2 == 0) {
        return 1;
      }
      if (GHIDRA_FIELD(cgs, 33701696, 4) == 3) {
        tmp_i4 = tmp_i4 + 1;
        tmp_pc3 = "fireteam kick %i";
      }
      else {
        if (GHIDRA_FIELD(cgs, 33701696, 4) != 4) {
          return 1;
        }
        tmp_i4 = tmp_i4 + 1;
        tmp_pc3 = "fireteam warn %i";
      }
    }
    break;
  default:
    goto LAB_0007bb12;
  }
  tmp_pc3 = (char *)va(tmp_pc3,tmp_i4);
LAB_0007bd98:
  trap_SendConsoleCommand(tmp_pc3);
  CG_EventHandling(0,0);
  return 1;
}

