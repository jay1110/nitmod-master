/* Miscellaneous client-game logic — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_client.h"

uint32_t CG_RW_ParseViewType(uint32_t param_1,char *param_2,int param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t extraout_ECX;
  uint32_t extraout_ECX_00;
  uint32_t extraout_ECX_01;
  uint32_t extraout_ECX_02;
  uint32_t extraout_ECX_03;
  uint32_t extraout_ECX_04;
  char *saved_ESI;
  char *tmp_pc4;
  char *saved_EDI;
  char *tmp_pc5;
  byte tmp_b6;
  uint64_t tmp_u7;
  char *local_ce8;
  char local_ce4 [64];
  char local_ca4 [64];
  uint8_t local_c64 [16];
  char local_c54 [1032];
  uint8_t local_84c [16];
  char local_83c [1032];
  uint8_t local_434 [16];
  char local_424 [1040];
  uint32_t uStack_14;
  
  tmp_b6 = 0;
  uStack_14 = 0x1a771;
  tmp_i1 = trap_PC_ReadToken(param_1,local_c64);
  tmp_i3 = 0;
  if ((tmp_i1 == 0) || (tmp_i3 = Q_stricmp(local_c54,"{",tmp_i1,tmp_i1), tmp_i3 != 0)) {
    tmp_u2 = CG_RW_ParseError(param_1,"expected \'{\'",tmp_i3,tmp_i3);
  }
  else {
LAB_0001a7d9:
    tmp_i3 = trap_PC_ReadToken(param_1,local_c64,saved_EDI,saved_EDI);
    if ((tmp_i3 == 0) || (local_c54[0] == '}')) {
      return 1;
    }
    tmp_pc4 = local_c54;
    tmp_u7 = Q_stricmp(tmp_pc4,"model",saved_ESI,saved_ESI);
    tmp_u2 = (uint32_t)((ulonglong)tmp_u7 >> 0x20);
    if ((int)tmp_u7 == 0) {
      tmp_i3 = PC_String_ParseNoAlloc(param_1,local_ce4,0x40,extraout_ECX);
      if (tmp_i3 == 0) {
LAB_0001a8d3:
        tmp_u2 = CG_RW_ParseError(param_1,"expected model filename",0,0);
        return tmp_u2;
      }
      tmp_u2 = trap_R_RegisterModel(local_ce4);
      *(uint32_t *)(param_2 + (param_3 * 6 + 0x170) * 4) = tmp_u2;
      saved_ESI = local_ce4;
      goto LAB_0001a7d9;
    }
    tmp_i3 = Q_stricmp(tmp_pc4,"axisModel",tmp_u2,tmp_u2);
    if (tmp_i3 == 0) {
      tmp_i3 = PC_String_ParseNoAlloc(param_1,local_ce4,0x40,0);
      if (tmp_i3 == 0) goto LAB_0001a8d3;
      tmp_u2 = trap_R_RegisterModel(local_ce4);
      *(uint32_t *)(param_2 + (param_3 * 6 + 0x171) * 4) = tmp_u2;
      saved_ESI = local_ce4;
      saved_EDI = param_2;
      goto LAB_0001a7d9;
    }
    tmp_i3 = Q_stricmp(tmp_pc4,"alliedModel",tmp_i3,tmp_i3);
    if (tmp_i3 == 0) {
      tmp_i3 = PC_String_ParseNoAlloc(param_1,local_ce4,0x40,0);
      if (tmp_i3 == 0) goto LAB_0001a8d3;
      tmp_u2 = trap_R_RegisterModel(local_ce4);
      *(uint32_t *)(param_2 + (param_3 * 6 + 0x172) * 4) = tmp_u2;
      saved_ESI = local_ce4;
      saved_EDI = param_2;
      goto LAB_0001a7d9;
    }
    tmp_i3 = Q_stricmp(tmp_pc4,"skin",tmp_i3,tmp_i3);
    if (tmp_i3 == 0) {
      tmp_i3 = PC_String_ParseNoAlloc(param_1,local_ce4,0x40,0);
      if (tmp_i3 == 0) {
LAB_0001a9db:
        tmp_u2 = CG_RW_ParseError(param_1,"expected skin filename",0,0);
        return tmp_u2;
      }
      tmp_u2 = trap_R_RegisterSkin(local_ce4);
      *(uint32_t *)(param_2 + (param_3 * 6 + 0x173) * 4) = tmp_u2;
      saved_ESI = local_ce4;
      saved_EDI = param_2;
      goto LAB_0001a7d9;
    }
    tmp_u7 = Q_stricmp(tmp_pc4,"axisSkin",saved_EDI,saved_EDI);
    tmp_u2 = (uint32_t)((ulonglong)tmp_u7 >> 0x20);
    if ((int)tmp_u7 == 0) {
      tmp_i3 = PC_String_ParseNoAlloc(param_1,local_ce4,0x40,extraout_ECX_00);
      if (tmp_i3 == 0) goto LAB_0001a9db;
      tmp_u2 = trap_R_RegisterSkin(local_ce4);
      *(uint32_t *)(param_2 + (param_3 * 6 + 0x174) * 4) = tmp_u2;
      saved_ESI = local_ce4;
      saved_EDI = param_2;
      goto LAB_0001a7d9;
    }
    tmp_i3 = Q_stricmp(tmp_pc4,"alliedSkin",tmp_u2,tmp_u2);
    if (tmp_i3 == 0) {
      tmp_i3 = PC_String_ParseNoAlloc(param_1,local_ce4,0x40,0);
      if (tmp_i3 == 0) goto LAB_0001a9db;
      tmp_u2 = trap_R_RegisterSkin(local_ce4);
      *(uint32_t *)(param_2 + (param_3 * 6 + 0x175) * 4) = tmp_u2;
      saved_ESI = local_ce4;
      saved_EDI = param_2;
      goto LAB_0001a7d9;
    }
    tmp_i3 = Q_stricmp(tmp_pc4,"flashModel",tmp_i3,tmp_i3);
    if (tmp_i3 == 0) {
      tmp_i3 = PC_String_ParseNoAlloc(param_1,local_ce4,0x40,0);
      if (tmp_i3 == 0) {
        tmp_u2 = CG_RW_ParseError(param_1,"expected flashModel filename",0,0);
        return tmp_u2;
      }
      tmp_u2 = trap_R_RegisterModel(local_ce4);
      *(uint32_t *)(param_2 + (param_3 + 0x5a2) * 4) = tmp_u2;
      saved_ESI = local_ce4;
      saved_EDI = param_2;
      goto LAB_0001a7d9;
    }
    tmp_i3 = Q_stricmp(tmp_pc4,"weaponLink",tmp_i3,tmp_i3);
    if (tmp_i3 != 0) {
      tmp_u2 = CG_RW_ParseError(param_1,"unknown token \'%s\'",tmp_pc4,tmp_i3);
      return tmp_u2;
    }
    tmp_i3 = trap_PC_ReadToken(param_1,local_84c,saved_EDI,saved_EDI);
    if (tmp_i3 != 0) {
      tmp_u7 = Q_stricmp(local_83c,"{",extraout_ECX_01,extraout_ECX_01);
      tmp_u2 = (uint32_t)((ulonglong)tmp_u7 >> 0x20);
      if ((int)tmp_u7 == 0) {
LAB_0001aae0:
        do {
          tmp_i3 = trap_PC_ReadToken(param_1,local_84c,tmp_u2,tmp_u2);
          saved_ESI = tmp_pc4;
          if ((tmp_i3 == 0) || (local_83c[0] == '}')) goto LAB_0001a7d9;
          tmp_pc4 = local_83c;
          tmp_u7 = Q_stricmp(tmp_pc4,&g_unk_0011f23d,tmp_i3,tmp_i3);
          if ((int)tmp_u7 != 0) {
            tmp_i3 = CG_RW_ParseError(param_1,"unknown token \'%s\'",tmp_pc4,
                                     (int)((ulonglong)tmp_u7 >> 0x20));
            goto LAB_0001ae95;
          }
          tmp_i3 = PC_Int_Parse(param_1,&local_ce8,0,0);
          tmp_pc5 = local_ce8;
          if (tmp_i3 == 0) {
            tmp_u7 = CG_RW_ParseError(param_1,"expected part index",0,0);
          }
          else if (local_ce8 < (char *)0x10) {
            saved_EDI = (char *)((int)local_ce8 * 0x58);
            tmp_pc5 = param_2 + (int)(saved_EDI + (param_3 * 0x160 + 0x182) * 4);
            for (tmp_i3 = 0x16; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
              tmp_pc5[0] = '\0';
              tmp_pc5[1] = '\0';
              tmp_pc5[2] = '\0';
              tmp_pc5[3] = '\0';
              tmp_pc5 = tmp_pc5 + ((uint)tmp_b6 * -2 + 1) * 4;
            }
            tmp_i1 = trap_PC_ReadToken(param_1,local_434,0,0);
            tmp_i3 = 0;
            tmp_pc4 = saved_EDI;
            if ((tmp_i1 == 0) || (tmp_i3 = Q_stricmp(local_424,"{",tmp_pc5,tmp_pc5), tmp_i3 != 0)) {
              tmp_u7 = CG_RW_ParseError(param_1,"expected \'{\'",tmp_i3,tmp_i3);
              saved_EDI = tmp_pc5;
            }
            else {
LAB_0001abef:
              do {
                tmp_u7 = trap_PC_ReadToken(param_1,local_434,tmp_pc4,tmp_pc4);
                tmp_u2 = (uint32_t)((ulonglong)tmp_u7 >> 0x20);
                if (((int)tmp_u7 == 0) || (local_424[0] == '}')) goto LAB_0001aae0;
                tmp_pc4 = local_424;
                tmp_u7 = Q_stricmp(tmp_pc4,"tag",extraout_ECX_02,extraout_ECX_02);
                tmp_i3 = (int)tmp_u7;
                if (tmp_i3 != 0) {
                  tmp_i3 = Q_stricmp(tmp_pc4,"model",tmp_i3,tmp_i3);
                  if (tmp_i3 == 0) {
                    tmp_u7 = PC_String_ParseNoAlloc(param_1,local_ca4,0x40,0);
                    tmp_u2 = (uint32_t)((ulonglong)tmp_u7 >> 0x20);
                    if ((int)tmp_u7 != 0) {
                      tmp_u2 = trap_R_RegisterModel(local_ca4);
                      *(uint32_t *)(param_2 + 0x648 + (int)(saved_EDI + param_3 * 0x580)) = tmp_u2;
                      tmp_pc4 = local_ca4;
                      goto LAB_0001abef;
                    }
                  }
                  else {
                    tmp_i3 = Q_stricmp(tmp_pc4,"axisModel",tmp_i3,tmp_i3);
                    if (tmp_i3 == 0) {
                      tmp_u7 = PC_String_ParseNoAlloc(param_1,local_ca4,0x40,0);
                      tmp_u2 = (uint32_t)((ulonglong)tmp_u7 >> 0x20);
                      if ((int)tmp_u7 != 0) {
                        tmp_u2 = trap_R_RegisterModel(local_ca4);
                        *(uint32_t *)(param_2 + 0x64c + (int)(saved_EDI + param_3 * 0x580)) =
                             tmp_u2;
                        tmp_pc4 = local_ca4;
                        goto LAB_0001abef;
                      }
                    }
                    else {
                      tmp_i3 = Q_stricmp(tmp_pc4,"alliedModel",tmp_i3,tmp_i3);
                      if (tmp_i3 != 0) {
                        tmp_i3 = Q_stricmp(tmp_pc4,"skin",tmp_i3,tmp_i3);
                        if (tmp_i3 == 0) {
                          tmp_i3 = PC_String_ParseNoAlloc(param_1,local_ca4,0x40,0);
                          if (tmp_i3 != 0) {
                            tmp_u2 = trap_R_RegisterSkin(local_ca4);
                            *(uint32_t *)(param_2 + 0x654 + (int)(saved_EDI + param_3 * 0x580)) =
                                 tmp_u2;
                            tmp_pc4 = local_ca4;
                            goto LAB_0001abef;
                          }
                        }
                        else {
                          tmp_i3 = Q_stricmp(tmp_pc4,"axisSkin",tmp_i3,tmp_i3);
                          if (tmp_i3 == 0) {
                            tmp_i3 = PC_String_ParseNoAlloc(param_1,local_ca4,0x40,0);
                            if (tmp_i3 != 0) {
                              tmp_u2 = trap_R_RegisterSkin(local_ca4);
                              *(uint32_t *)(param_2 + 0x658 + (int)(saved_EDI + param_3 * 0x580))
                                   = tmp_u2;
                              tmp_pc4 = local_ca4;
                              goto LAB_0001abef;
                            }
                          }
                          else {
                            tmp_i3 = Q_stricmp(tmp_pc4,"alliedSkin",tmp_i3,tmp_i3);
                            if (tmp_i3 != 0) {
                              tmp_u7 = CG_RW_ParseError(param_1,"unknown token \'%s\'",tmp_pc4,
                                                       extraout_ECX_04);
                              goto LAB_0001ae79;
                            }
                            tmp_i3 = PC_String_ParseNoAlloc(param_1,local_ca4,0x40,0);
                            if (tmp_i3 != 0) {
                              tmp_u2 = trap_R_RegisterSkin(local_ca4);
                              *(uint32_t *)(param_2 + 0x65c + (int)(saved_EDI + param_3 * 0x580))
                                   = tmp_u2;
                              tmp_pc4 = local_ca4;
                              goto LAB_0001abef;
                            }
                          }
                        }
                        tmp_pc4 = local_ca4;
                        tmp_u7 = CG_RW_ParseError(param_1,"expected skin filename",tmp_pc4,tmp_pc4);
                        goto LAB_0001ae79;
                      }
                      tmp_u7 = PC_String_ParseNoAlloc(param_1,local_ca4,0x40,extraout_ECX_03);
                      tmp_u2 = (uint32_t)((ulonglong)tmp_u7 >> 0x20);
                      if ((int)tmp_u7 != 0) {
                        tmp_u2 = trap_R_RegisterModel(local_ca4);
                        *(uint32_t *)(param_2 + 0x650 + (int)(saved_EDI + param_3 * 0x580)) =
                             tmp_u2;
                        tmp_pc4 = local_ca4;
                        goto LAB_0001abef;
                      }
                    }
                  }
                  tmp_pc4 = local_ca4;
                  tmp_u7 = CG_RW_ParseError(param_1,"expected model filename",tmp_u2,tmp_u2);
                  goto LAB_0001ae79;
                }
                tmp_i3 = PC_String_ParseNoAlloc
                                  (param_1,param_2 + (int)(saved_EDI + (param_3 * 0x160 + 0x182) * 4
                                                          ),0x40,(int)((ulonglong)tmp_u7 >> 0x20));
              } while (tmp_i3 != 0);
              tmp_u7 = CG_RW_ParseError(param_1,"expected tag name",0,0);
            }
          }
          else {
            tmp_u7 = CG_RW_ParseError(param_1,"part index out of bounds",tmp_i3,tmp_i3);
            tmp_pc4 = tmp_pc5;
          }
LAB_0001ae79:
          tmp_u2 = (uint32_t)((ulonglong)tmp_u7 >> 0x20);
          if ((int)tmp_u7 == 0) {
            return 0;
          }
        } while( true );
      }
    }
    tmp_i3 = CG_RW_ParseError(param_1,"expected \'{\'",tmp_pc4,tmp_pc4);
LAB_0001ae95:
    saved_ESI = tmp_pc4;
    if (tmp_i3 != 0) goto LAB_0001a7d9;
    tmp_u2 = 0;
  }
  return tmp_u2;
}

void CG_ContinueWeaponAnim(uint param_1)
{
  if ((((g_unk_010907a0 != 0) && ((g_unk_01090b7c & 0xfffffdff) != param_1)) && (g_unk_010b1670 < 1)) &&
     (g_unk_01090700 < 3)) {
    g_unk_01090b7c = param_1 | ~g_unk_01090b7c & 0x200;
  }
  return;
}

void CG_GenerateTracemap(void)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  int tmp_i7;
  float *pfVar8;
  float *pfVar9;
  uint32_t tmp_u10;
  float *pfVar11;
  int local_c4;
  uint8_t local_8d;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  uint32_t local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [4];
  int local_50;
  float local_4c;
  uint8_t local_48 [8];
  float local_40;
  byte local_28;
  uint32_t uStack_14;
  
  uStack_14 = 0x33ab9;
  if (GHIDRA_FIELD(developer, 12, 4) == 0) {
    CG_Printf("Can only generate a tracemap in developer mode.\n");
    return;
  }
  if (g_unk_010abd6c == 0) {
    CG_Printf("Need valid mapcoords in the worldspawn to be able to generate a tracemap.\n");
    return;
  }
  if (g_unk_010abd5c - g_unk_010abd54 != g_unk_010abd58 - g_unk_010abd60) {
    CG_Printf("Mapcoords need to be square.\n");
    return;
  }
  CG_Printf("Generating level heightmap and level mask...\n");
  memset(&tracemap,0,0xc001c);
  local_88 = -0x10000;
  local_8c = 0x10000;
  local_74 = 0;
  tmp_f3 = (g_unk_010abd5c - g_unk_010abd54) * 0.00390625;
  tmp_f2 = (g_unk_010abd60 - g_unk_010abd58) * 0.00390625;
  do {
    local_c4 = 0;
    local_6c = (float)local_74 * tmp_f3 + g_unk_010abd54;
    local_60 = local_6c;
    do {
      local_68 = (float)local_c4 * tmp_f2 + g_unk_010abd58;
      local_64 = 65536.0;
      local_58 = -65536.0;
      local_5c = local_68;
      CG_Trace(local_54,&local_6c,0,0,&local_60,0x3ff,0x39);
      tracecount_11973 = tracecount_11973 + 1;
      for (local_64 = local_40 - 1.0; -65536.0 < local_64; local_64 = local_64 - 64.0) {
        if (local_58 <= -65536.0) {
          local_58 = -65535.0;
        }
        CG_Trace(local_54,&local_6c,0,0,&local_60,0x3ff,0x39);
        tracecount_11973 = tracecount_11973 + 1;
        if (local_50 == 0) {
          if (local_4c != 1.0) {
            (&g_unk_00223e24)[local_c4 * 0x100 + local_74] = local_40;
            if ((local_28 & 0x80) == 0) {
              if ((float)local_88 < local_40) {
                local_88 = (int)ROUND(local_40);
              }
              if (local_40 < (float)local_8c) {
                local_8c = (int)ROUND(local_40);
              }
            }
            goto LAB_00033dd0;
          }
          break;
        }
      }
      (&g_unk_00223e24)[local_c4 * 0x100 + local_74] = 0xc7800000;
LAB_00033dd0:
      tmp_i4 = trap_Milliseconds();
      if ((tmp_i4 < lastDraw_11972) || (lastDraw_11972 < tmp_i4 + -499)) {
        tmp_i5 = local_74 * 0x100 + local_c4;
        lastDraw_11972 = tmp_i4;
        CG_Printf("%i of %i gridpoints calculated (%.2f%%), %i total traces\n",tmp_i5,0x10000,
                  (double)((float)tmp_i5 * 1.5258789e-05 * 100.0),tracecount_11973);
        trap_UpdateScreen();
      }
      local_c4 = local_c4 + 1;
    } while (local_c4 != 0x100);
    local_74 = local_74 + 1;
  } while (local_74 < 0x100);
  CG_Printf("%i of %i gridpoints calculated (%.2f%%), %i total traces\n",local_74 * 0x100,0x10000,
            (double)((float)(local_74 * 0x100) * 1.5258789e-05 * 100.0),tracecount_11973);
  trap_UpdateScreen();
  CG_Printf("Generating sky heightmap and sky mask...\n");
  local_78 = -0x10000;
  local_7c = 0x10000;
  local_74 = 0;
  do {
    local_c4 = 0;
    local_6c = (float)local_74 * tmp_f3 + g_unk_010abd54;
    local_60 = local_6c;
    do {
      local_58 = 65536.0;
      tmp_i4 = local_74 + local_c4 * 0x100;
      local_68 = (float)local_c4 * tmp_f2 + g_unk_010abd58;
      local_64 = (float)(&g_unk_00223e24)[tmp_i4];
      local_5c = local_68;
      if (local_64 != -65536.0) {
        while (local_64 < 65536.0) {
          while( true ) {
            if (65536.0 <= local_58) {
              local_58 = 65535.0;
            }
            CG_Trace(local_54,&local_6c,0,0,&local_60,0x3ff,1);
            tracecount_11973 = tracecount_11973 + 1;
            if (local_50 == 0) break;
            if (((local_28 & 4) != 0) &&
               (tmp_u6 = CG_PointContents(local_48,0x3ff), (tmp_u6 & 0x39) == 0)) goto LAB_0003416d;
            local_64 = local_40 + 1.0;
            if (65536.0 <= local_64) goto LAB_000340fd;
          }
          if (local_4c == 1.0) break;
          if ((local_28 & 4) != 0) {
LAB_0003416d:
            (&g_unk_001a3e24)[local_c4 * 0x100 + local_74] = local_40;
            if ((float)local_78 < local_40) {
              local_78 = (int)ROUND(local_40);
            }
            if (local_40 < (float)local_7c) {
              local_7c = (int)ROUND(local_40);
            }
            goto LAB_00033f70;
          }
          local_64 = local_40 + 64.0;
        }
LAB_000340fd:
        tmp_i4 = local_c4 * 0x100 + local_74;
      }
      (&g_unk_001a3e24)[tmp_i4] = 0x47800000;
LAB_00033f70:
      tmp_i4 = trap_Milliseconds();
      if ((tmp_i4 < lastDraw_11972) || (lastDraw_11972 < tmp_i4 + -499)) {
        tmp_i5 = local_74 * 0x100 + local_c4;
        lastDraw_11972 = tmp_i4;
        CG_Printf("%i of %i gridpoints calculated (%.2f%%), %i total traces\n",tmp_i5,0x10000,
                  (double)((float)tmp_i5 * 1.5258789e-05 * 100.0),tracecount_11973);
        trap_UpdateScreen();
      }
      local_c4 = local_c4 + 1;
    } while (local_c4 != 0x100);
    local_74 = local_74 + 1;
  } while (local_74 < 0x100);
  CG_Printf("%i of %i gridpoints calculated (%.2f%%), %i total traces\n",local_74 * 0x100,0x10000,
            (double)((float)(local_74 * 0x100) * 1.5258789e-05 * 100.0),tracecount_11973);
  trap_UpdateScreen();
  CG_Printf("Generating sky groundmap...\n");
  local_80 = -0x10000;
  local_84 = 0x10000;
  local_74 = 0;
  do {
    tmp_i4 = 0;
    local_6c = (float)local_74 * tmp_f3 + g_unk_010abd54;
    local_60 = local_6c;
    do {
      local_58 = -65536.0;
      local_68 = (float)tmp_i4 * tmp_f2 + g_unk_010abd58;
      tmp_i5 = tmp_i4 * 0x100 + local_74;
      local_64 = 65536.0;
      local_5c = local_68;
      if ((float)(&g_unk_001a3e24)[tmp_i5] == 65536.0) {
        tmp_f1 = (float)(&g_unk_00223e24)[tmp_i5];
        if (tmp_f1 == -65536.0) goto LAB_000342bf;
        CG_Trace(local_54,&local_6c,0,0,&local_60,0x3ff,0x39);
        tracecount_11973 = tracecount_11973 + 1;
        if (local_4c != 1.0) {
          (&g_unk_001e3e24)[tmp_i4 * 0x100 + local_74] = local_40;
          tmp_f1 = local_40;
          goto LAB_000342cf;
        }
        (&g_unk_001e3e24)[tmp_i4 * 0x100 + local_74] = 0xc7800000;
      }
      else {
        tmp_f1 = (float)(&g_unk_001a3e24)[local_74 + 0x20000 + tmp_i4 * 0x100];
LAB_000342bf:
        (&g_unk_001a3e24)[local_74 + 0x10000 + tmp_i4 * 0x100] = tmp_f1;
LAB_000342cf:
        if (tmp_f1 != -65536.0) {
          if ((float)local_80 < tmp_f1) {
            local_80 = (int)ROUND(tmp_f1);
          }
          if (tmp_f1 < (float)local_84) {
            local_84 = (int)ROUND(tmp_f1);
          }
        }
      }
      tmp_i5 = trap_Milliseconds();
      if ((tmp_i5 < lastDraw_11972) || (lastDraw_11972 < tmp_i5 + -499)) {
        tmp_i7 = local_74 * 0x100 + tmp_i4;
        lastDraw_11972 = tmp_i5;
        CG_Printf("%i of %i gridpoints calculated (%.2f%%), %i total traces\n",tmp_i7,0x10000,
                  (double)((float)tmp_i7 * 1.5258789e-05 * 100.0),tracecount_11973);
        trap_UpdateScreen();
      }
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_i4 != 0x100);
    local_74 = local_74 + 1;
  } while (local_74 < 0x100);
  CG_Printf("%i of %i gridpoints calculated (%.2f%%), %i total traces\n",local_74 * 0x100,0x10000,
            (double)((float)(local_74 * 0x100) * 1.5258789e-05 * 100.0),tracecount_11973);
  trap_UpdateScreen();
  tmp_f3 = 254.0 / (float)(local_88 - local_8c);
  if (tmp_f3 == 0.0) {
    tmp_f3 = 1.0;
  }
  pfVar11 = (float *)&g_unk_00224224;
  do {
    pfVar9 = pfVar11 + -0x100;
    do {
      while( true ) {
        pfVar8 = pfVar9;
        tmp_f2 = *pfVar8;
        if ((float)local_8c <= tmp_f2) {
          tmp_f2 = (tmp_f2 - (float)local_8c) * tmp_f3 + 1.0;
          *pfVar8 = tmp_f2;
        }
        if (1.0 <= tmp_f2) break;
        *pfVar8 = 1.0;
        pfVar9 = pfVar8 + 1;
        if (pfVar8 + 1 == pfVar11) goto LAB_0003459e;
      }
      if (255.0 < tmp_f2) {
        *pfVar8 = 255.0;
      }
      pfVar9 = pfVar8 + 1;
    } while (pfVar8 + 1 != pfVar11);
LAB_0003459e:
    pfVar11 = pfVar8 + 0x101;
  } while (pfVar11 != (float *)(string_11988 + 0x3e4));
  tmp_f3 = 254.0 / (float)(local_80 - local_84);
  if (tmp_f3 == 0.0) {
    tmp_f3 = 1.0;
  }
  pfVar11 = (float *)&g_unk_001e4224;
  do {
    pfVar9 = pfVar11 + -0x100;
    do {
      while( true ) {
        pfVar8 = pfVar9;
        tmp_f2 = *pfVar8;
        if ((float)local_84 <= tmp_f2) {
          tmp_f2 = (tmp_f2 - (float)local_84) * tmp_f3 + 1.0;
          *pfVar8 = tmp_f2;
        }
        if (1.0 <= tmp_f2) break;
        *pfVar8 = 1.0;
        pfVar9 = pfVar8 + 1;
        if (pfVar8 + 1 == pfVar11) goto LAB_0003463e;
      }
      if (255.0 < tmp_f2) {
        *pfVar8 = 255.0;
      }
      pfVar9 = pfVar8 + 1;
    } while (pfVar8 + 1 != pfVar11);
LAB_0003463e:
    pfVar11 = pfVar8 + 0x101;
  } while (pfVar11 != (float *)&g_unk_00224224);
  if (local_78 == local_7c) {
    tmp_f3 = 1.0;
  }
  else {
    tmp_f3 = 254.0 / (float)(local_78 - local_7c);
  }
  pfVar11 = (float *)&g_unk_001a4224;
  do {
    pfVar9 = pfVar11 + -0x100;
    do {
      while ((*pfVar9 == 65536.0 || (tmp_f2 = (*pfVar9 - (float)local_7c) * tmp_f3 + 1.0, tmp_f2 < 0.0)
             )) {
        *pfVar9 = 0.0;
        pfVar9 = pfVar9 + 1;
        if (pfVar11 == pfVar9) goto LAB_000346df;
      }
      if (255.0 < tmp_f2) {
        tmp_f2 = 255.0;
      }
      pfVar8 = pfVar9 + 1;
      *pfVar9 = tmp_f2;
      pfVar9 = pfVar8;
    } while (pfVar11 != pfVar8);
LAB_000346df:
    pfVar11 = pfVar11 + 0x100;
  } while (pfVar11 != (float *)&g_unk_001e4224);
  local_74 = 0x100;
  tmp_u10 = Q_strlwr(0x10f69ac);
  tmp_u10 = va("maps/%s_tracemap.tga",tmp_u10);
  trap_FS_FOpenFile(tmp_u10,&local_70,1);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 2;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 1;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 1;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0x20;
  trap_FS_Write(&local_8d,1,local_70);
  local_8d = 0;
  trap_FS_Write(&local_8d,1,local_70);
  local_74 = 0;
LAB_00034964:
  tmp_i5 = 1;
  tmp_i4 = 0;
  do {
    if (local_74 != 0) goto LAB_000349cd;
    switch(tmp_i4) {
    default:
      trap_FS_Write(&local_8c,4,local_70);
      tmp_i4 = tmp_i5;
      if (tmp_i5 == 0x100) goto code_r0x00034bf0;
      break;
    case 1:
      trap_FS_Write(&local_88,4,local_70);
      tmp_i4 = tmp_i5;
      break;
    case 2:
      trap_FS_Write(&local_84,4,local_70);
      tmp_i4 = tmp_i5;
      break;
    case 3:
      trap_FS_Write(&local_80,4,local_70);
      tmp_i4 = tmp_i5;
      break;
    case 4:
      trap_FS_Write(&local_7c,4,local_70);
      tmp_i4 = tmp_i5;
      break;
    case 5:
      trap_FS_Write(&local_78,4,local_70);
      tmp_i4 = tmp_i5;
    }
    while (tmp_i5 = tmp_i4 + 1, 5 < tmp_i4) {
LAB_000349cd:
      local_8d = (uint8_t)(short)ROUND((float)(&g_unk_001a3e24)[(0xff - local_74) * 0x100 + tmp_i4])
      ;
      trap_FS_Write(&local_8d,1,local_70);
      if ((float)(&g_unk_001a3e24)[tmp_i4 + 0x10000 + (0xff - local_74) * 0x100] == -65536.0) {
        local_8d = 0;
      }
      else {
        local_8d = (uint8_t)
                   (short)ROUND((float)(&g_unk_001a3e24)[tmp_i4 + 0x10000 + (0xff - local_74) * 0x100])
        ;
      }
      trap_FS_Write(&local_8d,1,local_70);
      if ((float)(&g_unk_001a3e24)[tmp_i4 + 0x20000 + (0xff - local_74) * 0x100] == -65536.0) {
        local_8d = 0;
        trap_FS_Write(&local_8d,1,local_70);
        local_8d = 0;
      }
      else {
        local_8d = (uint8_t)
                   (short)ROUND((float)(&g_unk_001a3e24)[tmp_i4 + 0x20000 + (0xff - local_74) * 0x100])
        ;
        trap_FS_Write(&local_8d,1,local_70);
        local_8d = 0xff;
      }
      trap_FS_Write(&local_8d,1,local_70);
      tmp_i4 = tmp_i5;
      if (tmp_i5 == 0x100) {
        local_74 = local_74 + 1;
        if (local_74 < 0x100) goto LAB_00034964;
        goto LAB_00034b10;
      }
    }
  } while( true );
code_r0x00034bf0:
  local_74 = local_74 + 1;
  if (0xff < local_74) {
LAB_00034b10:
    local_74 = 0;
    trap_FS_Write(&local_74,4,local_70);
    local_74 = 0;
    trap_FS_Write(&local_74,4,local_70);
    trap_FS_Write("TRUEVISION-XFILE.",0x12,local_70);
    trap_FS_FCloseFile(local_70);
    return;
  }
  goto LAB_00034964;
}

int CG_EffectGust(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i2 = g_unk_010906e0 + GHIDRA_FIELD(cg_atmFx, 272064, 4);
  tmp_i1 = rand();
  GHIDRA_FIELD(cg_atmFx, 272044, 4) = tmp_i1 % (int)(GHIDRA_FIELD(cg_atmFx, 272068, 4) - GHIDRA_FIELD(cg_atmFx, 272064, 4)) + tmp_i2;
  tmp_i1 = GHIDRA_FIELD(cg_atmFx, 272044, 4) + GHIDRA_FIELD(cg_atmFx, 272056, 4);
  tmp_i2 = 0;
  tmp_i3 = GHIDRA_FIELD(cg_atmFx, 272060, 4) - GHIDRA_FIELD(cg_atmFx, 272056, 4);
  if (tmp_i3 != 0) {
    tmp_i2 = rand();
    tmp_i2 = tmp_i2 % tmp_i3;
  }
  GHIDRA_FIELD(cg_atmFx, 272032, 4) = tmp_i2 + tmp_i1;
  tmp_i1 = GHIDRA_FIELD(cg_atmFx, 272032, 4) + GHIDRA_FIELD(cg_atmFx, 272048, 4);
  tmp_i2 = 0;
  tmp_i3 = GHIDRA_FIELD(cg_atmFx, 272052, 4) - GHIDRA_FIELD(cg_atmFx, 272048, 4);
  if (tmp_i3 != 0) {
    tmp_i2 = rand();
    tmp_i2 = tmp_i2 % tmp_i3;
  }
  GHIDRA_FIELD(cg_atmFx, 272036, 4) = tmp_i2 + tmp_i1;
  tmp_i1 = GHIDRA_FIELD(cg_atmFx, 272036, 4) + GHIDRA_FIELD(cg_atmFx, 272056, 4);
  tmp_i3 = 0;
  tmp_i4 = GHIDRA_FIELD(cg_atmFx, 272060, 4) - GHIDRA_FIELD(cg_atmFx, 272056, 4);
  tmp_i2 = GHIDRA_FIELD(cg_atmFx, 272056, 4);
  if (tmp_i4 != 0) {
    tmp_i3 = rand();
    tmp_i2 = tmp_i3 / tmp_i4;
    tmp_i3 = tmp_i3 % tmp_i4;
  }
  GHIDRA_FIELD(cg_atmFx, 272040, 4) = tmp_i3 + tmp_i1;
  return tmp_i2;
}

uint32_t CG_SnowParticleGenerate(float *param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  uint tmp_u3;
  uint tmp_u4;
  long double tmp_l5;
  long double tmp_l6;
  double local_2c;
  double local_24 [2];
  
  tmp_u3 = rand();
  tmp_u4 = rand();
  tmp_f1 = (float)(tmp_u3 & 0x7fff) / 32767.0;
  sincos((double)((tmp_f1 + tmp_f1) * 3.1415927),local_24,&local_2c);
  tmp_f1 = ((float)(tmp_u4 & 0x7fff) / 32767.0) * 1000.0 + 20.0;
  *param_1 = (float)local_24[0] * tmp_f1 + *(float *)(g_unk_010afbcc + 0x18);
  param_1[1] = tmp_f1 * (float)local_2c + *(float *)(g_unk_010afbcc + 0x1c);
  tmp_l5 = (long double)BG_GetSkyHeightAtPoint(param_1);
  if (tmp_l5 != (long double)65536.0) {
    tmp_l6 = (long double)BG_GetSkyGroundHeightAtPoint(param_1);
    if (tmp_l6 < (long double)(float)tmp_l5) {
      tmp_f1 = (float)tmp_l6;
      tmp_u3 = rand();
      tmp_f2 = ((float)tmp_l5 - tmp_f1) * ((float)(tmp_u3 & 0x7fff) / 32767.0) + tmp_f1;
      param_1[2] = tmp_f2;
      if (0 < (int)GHIDRA_FIELD(cg_atmFx, 272088, 4)) {
        if (((float)(int)GHIDRA_FIELD(cg_atmFx, 272088, 4) < tmp_f2 - *(float *)(g_unk_010afbcc + 0x20)) &&
           (tmp_f2 = *(float *)(g_unk_010afbcc + 0x20) + (float)(int)GHIDRA_FIELD(cg_atmFx, 272088, 4),
           param_1[2] = tmp_f2, tmp_f2 < tmp_f1)) {
          return 0;
        }
      }
      param_1[0xe] = 1.4013e-45;
      param_1[3] = *param_2;
      param_1[4] = param_2[1];
      param_1[5] = param_2[2];
      tmp_u3 = rand();
      tmp_f1 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
      tmp_f1 = (tmp_f1 + tmp_f1) * 25.0 + param_1[5];
      param_1[5] = tmp_f1;
      param_1[6] = param_1[3];
      param_1[7] = param_1[4];
      param_1[8] = tmp_f1;
      VectorNormalizeFast(param_1 + 6);
      tmp_u3 = rand();
      tmp_f1 = (float)(tmp_u3 & 0x7fff) / 32767.0;
      param_1[0x10] = 3.898973e-39;
      tmp_f1 = tmp_f1 + tmp_f1 + 3.0;
      param_1[0xc] = tmp_f1;
      param_1[0xd] = tmp_f1 * 0.5;
      return 1;
    }
  }
  return 0;
}

uint32_t CG_RainParticleGenerate(float *param_1,float *param_2,float param_3)
{
  float tmp_f1;
  float tmp_f2;
  uint tmp_u3;
  uint tmp_u4;
  long double tmp_l5;
  long double tmp_l6;
  double local_2c;
  double local_24 [2];
  
  tmp_u3 = rand();
  tmp_u4 = rand();
  tmp_f1 = (float)(tmp_u3 & 0x7fff) / 32767.0;
  sincos((double)((tmp_f1 + tmp_f1) * 3.1415927),local_24,&local_2c);
  tmp_f1 = ((float)(tmp_u4 & 0x7fff) / 32767.0) * 1000.0 + 20.0;
  *param_1 = (float)local_24[0] * tmp_f1 + *(float *)(g_unk_010afbcc + 0x18);
  param_1[1] = tmp_f1 * (float)local_2c + *(float *)(g_unk_010afbcc + 0x1c);
  tmp_l5 = (long double)BG_GetSkyHeightAtPoint(param_1);
  if (tmp_l5 != (long double)65536.0) {
    tmp_l6 = (long double)BG_GetSkyGroundHeightAtPoint(param_1);
    if (tmp_l6 < (long double)(float)tmp_l5) {
      tmp_f1 = (float)tmp_l6;
      tmp_u3 = rand();
      tmp_f2 = ((float)tmp_l5 - tmp_f1) * ((float)(tmp_u3 & 0x7fff) / 32767.0) + tmp_f1;
      param_1[2] = tmp_f2;
      if (0 < (int)GHIDRA_FIELD(cg_atmFx, 272088, 4)) {
        if (((float)(int)GHIDRA_FIELD(cg_atmFx, 272088, 4) < tmp_f2 - *(float *)(g_unk_010afbcc + 0x20)) &&
           (tmp_f2 = *(float *)(g_unk_010afbcc + 0x20) + (float)(int)GHIDRA_FIELD(cg_atmFx, 272088, 4),
           param_1[2] = tmp_f2, tmp_f2 < tmp_f1)) {
          return 0;
        }
      }
      if ((float)(int)GHIDRA_FIELD(cg_atmFx, 272148, 4) <=
          (float)(((g_unk_010906e0 / 10000) * 10000 - g_unk_010906e0) + 10000) *
          (float)(int)GHIDRA_FIELD(cg_atmFx, 272028, 4) * 0.001 + (float)(int)GHIDRA_FIELD(cg_atmFx, 272028, 4) * 0.5) {
        param_1[0xe] = 1.4013e-45;
        tmp_u3 = rand();
        param_1[9] = ((float)(tmp_u3 & 0x7fff) / 32767.0) * 0.2 * 255.0 + 0.6;
        tmp_u3 = rand();
        param_1[10] = ((float)(tmp_u3 & 0x7fff) / 32767.0) * 0.2 * 255.0 + 0.6;
        tmp_u3 = rand();
        param_1[0xb] = ((float)(tmp_u3 & 0x7fff) / 32767.0) * 0.2 * 255.0 + 0.6;
        param_1[3] = *param_2;
        param_1[4] = param_2[1];
        param_1[5] = param_2[2];
        tmp_u3 = rand();
        tmp_f1 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
        tmp_f1 = (tmp_f1 + tmp_f1) * 100.0 + param_1[5];
        param_1[5] = tmp_f1;
        param_1[6] = param_1[3];
        param_1[7] = param_1[4];
        param_1[8] = tmp_f1;
        VectorNormalizeFast(param_1 + 6);
        tmp_u3 = rand();
        tmp_f1 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
        param_1[0xc] = (tmp_f1 + tmp_f1) * 100.0 + 150.0;
        param_1[0x10] = 3.898973e-39;
        param_1[0xd] = param_3;
        return 1;
      }
    }
  }
  return 0;
}

uint32_t CG_SnowParticleCheckVisible(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  uint32_t tmp_u3;
  long double tmp_l4;
  
  tmp_u3 = 0;
  if ((param_1 != (float *)0x0) && (param_1[0xe] != 0.0)) {
    tmp_f1 = (float)(g_unk_010906e0 - GHIDRA_FIELD(cg_atmFx, 272024, 4)) * 0.001;
    *param_1 = param_1[3] * tmp_f1 + *param_1;
    param_1[1] = param_1[4] * tmp_f1 + param_1[1];
    tmp_f1 = tmp_f1 * param_1[5] + param_1[2];
    param_1[2] = tmp_f1;
    tmp_l4 = (long double)BG_GetSkyGroundHeightAtPoint(param_1);
    if (((long double)tmp_f1 < tmp_l4) ||
       (tmp_f1 = *param_1 - *(float *)(g_unk_010afbcc + 0x18),
       tmp_f2 = param_1[1] - *(float *)(g_unk_010afbcc + 0x1c), 1e+06 < tmp_f2 * tmp_f2 + tmp_f1 * tmp_f1))
    {
      param_1[0xe] = 0.0;
      return 0;
    }
    tmp_u3 = 1;
  }
  return tmp_u3;
}

uint32_t CG_RainParticleCheckVisible(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  uint32_t tmp_u3;
  long double tmp_l4;
  
  tmp_u3 = 0;
  if ((param_1 != (float *)0x0) && (param_1[0xe] != 0.0)) {
    tmp_f1 = (float)(g_unk_010906e0 - GHIDRA_FIELD(cg_atmFx, 272024, 4)) * 0.001;
    *param_1 = param_1[3] * tmp_f1 + *param_1;
    param_1[1] = param_1[4] * tmp_f1 + param_1[1];
    tmp_f2 = tmp_f1 * param_1[5] + param_1[2];
    param_1[2] = tmp_f2;
    tmp_f1 = param_1[0xc];
    tmp_l4 = (long double)BG_GetSkyGroundHeightAtPoint(param_1);
    if (((long double)(tmp_f1 + tmp_f2) < tmp_l4) ||
       (tmp_f1 = *param_1 - *(float *)(g_unk_010afbcc + 0x18),
       tmp_f2 = param_1[1] - *(float *)(g_unk_010afbcc + 0x1c), 1e+06 < tmp_f2 * tmp_f2 + tmp_f1 * tmp_f1))
    {
      param_1[0xe] = 0.0;
      return 0;
    }
    tmp_u3 = 1;
  }
  return tmp_u3;
}

void CG_SnowParticleRender(float *param_1)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  int tmp_i7;
  float tmp_f8;
  int tmp_i9;
  int tmp_i10;
  long double tmp_l11;
  long double tmp_l12;
  long double tmp_l13;
  double tmp_d14;
  double tmp_d15;
  float local_7c;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint8_t local_40;
  uint8_t local_3f;
  uint8_t local_3e;
  uint8_t local_3d;
  float local_3c;
  float local_38;
  float local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint8_t local_28;
  uint8_t local_27;
  uint8_t local_26;
  uint8_t local_25;
  float local_24;
  float local_20;
  float local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint8_t local_10;
  uint8_t local_f;
  uint8_t local_e;
  uint8_t local_d;
  
  if ((param_1[0xe] != 0.0) && (tmp_i9 = CG_CullPoint(param_1), tmp_i9 == 0)) {
    tmp_f2 = *param_1;
    tmp_f3 = param_1[1];
    tmp_f4 = param_1[2];
    tmp_f5 = param_1[0xd];
    local_58 = tmp_f4;
    tmp_d14 = sin((double)(tmp_f4 * 0.03125 * tmp_f5 * 0.5));
    tmp_d15 = cos((double)(tmp_f5 * 0.5 * (tmp_f4 + tmp_f3) * 0.03125));
    tmp_f4 = (1.0 - param_1[8]) * 24.0;
    local_60 = (float)tmp_d14 * tmp_f4 + tmp_f2;
    local_5c = (float)tmp_d15 * tmp_f4 + tmp_f3;
    tmp_l11 = (long double)BG_GetSkyGroundHeightAtPoint(&local_60);
    tmp_l12 = (long double)param_1[0xc];
    tmp_l13 = (long double)local_58;
    if (tmp_l13 <= tmp_l11) {
      tmp_l11 = (tmp_l12 - tmp_l11) + tmp_l13;
      tmp_l12 = tmp_l11 - tmp_l12;
      local_60 = (float)((long double)param_1[6] * tmp_l12 + (long double)local_60);
      local_5c = (float)((long double)param_1[7] * tmp_l12 + (long double)local_5c);
      local_58 = (float)(tmp_l12 * (long double)param_1[8] + tmp_l13);
      tmp_l12 = tmp_l11;
    }
    if ((long double)0 < tmp_l12) {
      tmp_l11 = (long double)DistanceSquared(param_1,g_unk_010afbcc + 0x18);
      if (tmp_l11 <= (long double)250000.0) {
        local_7c = 1.0;
      }
      else {
        local_7c = (float)((tmp_l11 - (long double)250000.0) * (long double)2.5e-06 + (long double)1.0);
      }
      tmp_f2 = param_1[6];
      tmp_f3 = -((float)tmp_l12 * local_7c);
      tmp_f5 = tmp_f2 * tmp_f3 + local_60;
      tmp_f4 = local_5c + param_1[7] * tmp_f3;
      tmp_f3 = local_58 + tmp_f3 * param_1[8];
      tmp_f8 = param_1[8] * *(float *)(g_unk_010afbcc + 0x44) +
              param_1[7] * *(float *)(g_unk_010afbcc + 0x40) + tmp_f2 * *(float *)(g_unk_010afbcc + 0x3c)
      ;
      tmp_f2 = -(*(float *)(g_unk_010afbcc + 0x38) * param_1[8] +
               param_1[7] * *(float *)(g_unk_010afbcc + 0x34) +
               tmp_f2 * *(float *)(g_unk_010afbcc + 0x30));
      local_6c = *(float *)(g_unk_010afbcc + 0x3c) * tmp_f2 + *(float *)(g_unk_010afbcc + 0x30) * tmp_f8;
      local_68 = *(float *)(g_unk_010afbcc + 0x40) * tmp_f2 + *(float *)(g_unk_010afbcc + 0x34) * tmp_f8;
      local_64 = tmp_f8 * *(float *)(g_unk_010afbcc + 0x38) + tmp_f2 * *(float *)(g_unk_010afbcc + 0x44);
      VectorNormalize(&local_6c);
      local_48 = 0;
      local_44 = 0;
      local_40 = 0xff;
      local_3f = 0xff;
      local_7c = local_7c * param_1[0xd];
      local_3e = 0xff;
      local_3d = 0xff;
      local_30 = 0;
      local_2c = 0x3f800000;
      local_28 = 0xff;
      tmp_f2 = -local_7c;
      local_27 = 0xff;
      local_26 = 0xff;
      local_25 = 0xff;
      local_54 = tmp_f5 + local_6c * tmp_f2;
      local_50 = tmp_f4 + local_68 * tmp_f2;
      local_4c = tmp_f3 + tmp_f2 * local_64;
      local_3c = local_6c * tmp_f2 + local_60;
      local_38 = local_68 * tmp_f2 + local_5c;
      local_34 = tmp_f2 * local_64 + local_58;
      local_24 = local_6c * local_7c + local_60;
      local_20 = local_68 * local_7c + local_5c;
      local_10 = 0xff;
      local_d = 0xff;
      local_18 = 0x3f800000;
      local_14 = 0x3f800000;
      local_f = 0xff;
      local_1c = local_58 + local_7c * local_64;
      local_e = 0xff;
      tmp_i9 = CG_PB_FindFreePolyBuffer(*(uint32_t *)param_1[0x10],3,3);
      if (tmp_i9 != 0) {
        tmp_i6 = *(int *)(tmp_i9 + 0x701c);
        tmp_i7 = *(int *)(tmp_i9 + 0xd038);
        tmp_i1 = tmp_i6 + 2;
        tmp_i10 = tmp_i1 * 0x10;
        *(float *)(tmp_i9 + tmp_i10) = local_24;
        *(float *)(tmp_i9 + 4 + tmp_i10) = local_20;
        *(float *)(tmp_i9 + 8 + tmp_i10) = local_1c;
        *(uint32_t *)(tmp_i9 + 0x4020 + tmp_i6 * 8) = local_18;
        *(uint32_t *)(tmp_i9 + 0x4014 + tmp_i1 * 8) = local_14;
        *(uint8_t *)(tmp_i9 + 0x6020 + tmp_i6 * 4) = local_10;
        *(uint8_t *)(tmp_i9 + 0x6019 + tmp_i1 * 4) = local_f;
        *(uint8_t *)(tmp_i9 + 0x601a + tmp_i1 * 4) = local_e;
        *(uint8_t *)(tmp_i9 + 0x601b + tmp_i1 * 4) = local_d;
        *(int *)(tmp_i9 + 0x7028 + tmp_i7 * 4) = tmp_i1;
        tmp_i1 = tmp_i6 + 1;
        tmp_i10 = tmp_i1 * 0x10;
        *(float *)(tmp_i9 + tmp_i10) = local_3c;
        *(float *)(tmp_i9 + 4 + tmp_i10) = local_38;
        *(float *)(tmp_i9 + 8 + tmp_i10) = local_34;
        *(uint32_t *)(tmp_i9 + 0x4018 + tmp_i6 * 8) = local_30;
        *(uint32_t *)(tmp_i9 + 0x4014 + tmp_i1 * 8) = local_2c;
        *(uint8_t *)(tmp_i9 + 0x601c + tmp_i6 * 4) = local_28;
        *(uint8_t *)(tmp_i9 + 0x6019 + tmp_i1 * 4) = local_27;
        *(uint8_t *)(tmp_i9 + 0x601a + tmp_i1 * 4) = local_26;
        *(uint8_t *)(tmp_i9 + 0x601b + tmp_i1 * 4) = local_25;
        tmp_i10 = tmp_i6 * 0x10;
        *(int *)(tmp_i9 + 0x7024 + tmp_i7 * 4) = tmp_i1;
        *(float *)(tmp_i9 + tmp_i10) = local_54;
        *(float *)(tmp_i9 + 4 + tmp_i10) = local_50;
        *(float *)(tmp_i9 + 8 + tmp_i10) = local_4c;
        *(uint32_t *)(tmp_i9 + 0x4010 + tmp_i6 * 8) = local_48;
        *(uint32_t *)(tmp_i9 + 0x4014 + tmp_i6 * 8) = local_44;
        *(uint8_t *)(tmp_i9 + 0x6018 + tmp_i6 * 4) = local_40;
        *(uint8_t *)(tmp_i9 + 0x6019 + tmp_i6 * 4) = local_3f;
        *(uint8_t *)(tmp_i9 + 0x601a + tmp_i6 * 4) = local_3e;
        *(uint8_t *)(tmp_i9 + 0x601b + tmp_i6 * 4) = local_3d;
        *(int *)(tmp_i9 + 0x7020 + tmp_i7 * 4) = tmp_i6;
        *(int *)(tmp_i9 + 0xd038) = tmp_i7 + 3;
        *(int *)(tmp_i9 + 0x701c) = tmp_i6 + 3;
      }
    }
  }
  return;
}

void CG_RainParticleRender(float *param_1)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  int tmp_i6;
  float tmp_f7;
  int tmp_i8;
  int tmp_i9;
  long double tmp_l10;
  long double tmp_l11;
  long double tmp_l12;
  long double tmp_l13;
  long double tmp_l14;
  long double tmp_l15;
  long double tmp_l16;
  float local_88;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
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
  
  if ((param_1[0xe] != 0.0) && (tmp_i8 = CG_CullPoint(param_1), tmp_i8 == 0)) {
    local_70 = *param_1;
    local_6c = param_1[1];
    local_68 = param_1[2];
    tmp_l10 = (long double)DistanceSquared(param_1,g_unk_010afbcc + 0x18);
    tmp_l11 = (long double)BG_GetSkyGroundHeightAtPoint(&local_70);
    tmp_l12 = (long double)param_1[0xc];
    tmp_l13 = (long double)local_68;
    if (tmp_l13 <= tmp_l11) {
      tmp_l11 = (tmp_l12 - tmp_l11) + tmp_l13;
      tmp_l12 = tmp_l11 - tmp_l12;
      local_70 = (float)((long double)param_1[6] * tmp_l12 + (long double)local_70);
      local_6c = (float)((long double)param_1[7] * tmp_l12 + (long double)local_6c);
      tmp_l13 = tmp_l12 * (long double)param_1[8] + tmp_l13;
      local_68 = (float)tmp_l13;
      tmp_l12 = tmp_l11;
    }
    if ((long double)0 < tmp_l12) {
      if (16384.0 <= (float)tmp_l10) {
        local_88 = 1.0;
      }
      else {
        local_88 = (float)tmp_l10 * 6.1035156e-05 * 0.75 + 0.25;
      }
      tmp_l11 = (long double)param_1[6];
      tmp_l12 = -tmp_l12;
      tmp_l10 = (long double)local_70;
      tmp_f2 = param_1[7];
      tmp_l14 = (long double)local_6c;
      tmp_f3 = param_1[8];
      tmp_l16 = (long double)param_1[8] * (long double)*(float *)(g_unk_010afbcc + 0x44) +
               (long double)param_1[7] * (long double)*(float *)(g_unk_010afbcc + 0x40) +
               tmp_l11 * (long double)*(float *)(g_unk_010afbcc + 0x3c);
      tmp_l15 = -((long double)*(float *)(g_unk_010afbcc + 0x38) * (long double)param_1[8] +
                (long double)param_1[7] * (long double)*(float *)(g_unk_010afbcc + 0x34) +
                tmp_l11 * (long double)*(float *)(g_unk_010afbcc + 0x30));
      local_7c = (float)((long double)*(float *)(g_unk_010afbcc + 0x3c) * tmp_l15 +
                        (long double)*(float *)(g_unk_010afbcc + 0x30) * tmp_l16);
      local_78 = (float)((long double)*(float *)(g_unk_010afbcc + 0x40) * tmp_l15 +
                        (long double)*(float *)(g_unk_010afbcc + 0x34) * tmp_l16);
      local_74 = (float)(tmp_l16 * (long double)*(float *)(g_unk_010afbcc + 0x38) +
                        tmp_l15 * (long double)*(float *)(g_unk_010afbcc + 0x44));
      VectorNormalize(&local_7c);
      local_58 = 0x3f000000;
      local_54 = 0;
      local_50 = (uint8_t)(short)ROUND(param_1[9]);
      local_4f = (uint8_t)(short)ROUND(param_1[10]);
      local_4e = (uint8_t)(short)ROUND(param_1[0xb]);
      tmp_f4 = param_1[0xd];
      tmp_f7 = -tmp_f4;
      local_4d = (uint8_t)(short)ROUND(local_88 * 100.0);
      local_40 = 0;
      local_4c = local_7c * tmp_f7 + local_70;
      local_3c = 0x3f800000;
      local_28 = 0x3f800000;
      local_48 = local_78 * tmp_f7 + local_6c;
      local_44 = tmp_f7 * local_74 + local_68;
      local_34 = local_7c * tmp_f4 + local_70;
      local_35 = (uint8_t)(short)ROUND(local_88 * 200.0);
      local_30 = local_78 * tmp_f4 + local_6c;
      local_2c = local_68 + tmp_f4 * local_74;
      local_24 = 0x3f800000;
      local_64 = (float)(tmp_l11 * tmp_l12 + tmp_l10);
      local_60 = (float)(tmp_l14 + (long double)tmp_f2 * tmp_l12);
      local_5c = (float)(tmp_l12 * (long double)tmp_f3 + tmp_l13);
      local_38 = local_50;
      local_37 = local_4f;
      local_20 = local_50;
      local_1f = local_4f;
      local_1e = local_4e;
      local_1d = local_35;
      tmp_i8 = CG_PB_FindFreePolyBuffer(*(uint32_t *)param_1[0x10],3,3);
      if (tmp_i8 != 0) {
        tmp_i5 = *(int *)(tmp_i8 + 0x701c);
        tmp_i6 = *(int *)(tmp_i8 + 0xd038);
        tmp_i1 = tmp_i5 + 2;
        tmp_i9 = tmp_i1 * 0x10;
        *(float *)(tmp_i8 + tmp_i9) = local_34;
        *(float *)(tmp_i8 + 4 + tmp_i9) = local_30;
        *(float *)(tmp_i8 + 8 + tmp_i9) = local_2c;
        *(uint32_t *)(tmp_i8 + 0x4020 + tmp_i5 * 8) = local_28;
        *(uint32_t *)(tmp_i8 + 0x4014 + tmp_i1 * 8) = local_24;
        *(uint8_t *)(tmp_i8 + 0x6020 + tmp_i5 * 4) = local_20;
        *(uint8_t *)(tmp_i8 + 0x6019 + tmp_i1 * 4) = local_1f;
        *(uint8_t *)(tmp_i8 + 0x601a + tmp_i1 * 4) = local_1e;
        *(uint8_t *)(tmp_i8 + 0x601b + tmp_i1 * 4) = local_1d;
        *(int *)(tmp_i8 + 0x7028 + tmp_i6 * 4) = tmp_i1;
        tmp_i1 = tmp_i5 + 1;
        tmp_i9 = tmp_i1 * 0x10;
        *(float *)(tmp_i8 + tmp_i9) = local_4c;
        *(float *)(tmp_i8 + 4 + tmp_i9) = local_48;
        *(float *)(tmp_i8 + 8 + tmp_i9) = local_44;
        *(uint32_t *)(tmp_i8 + 0x4018 + tmp_i5 * 8) = local_40;
        *(uint32_t *)(tmp_i8 + 0x4014 + tmp_i1 * 8) = local_3c;
        *(uint8_t *)(tmp_i8 + 0x601c + tmp_i5 * 4) = local_38;
        *(uint8_t *)(tmp_i8 + 0x6019 + tmp_i1 * 4) = local_37;
        *(uint8_t *)(tmp_i8 + 0x601a + tmp_i1 * 4) = local_36;
        *(uint8_t *)(tmp_i8 + 0x601b + tmp_i1 * 4) = local_35;
        tmp_i9 = tmp_i5 * 0x10;
        *(int *)(tmp_i8 + 0x7024 + tmp_i6 * 4) = tmp_i1;
        *(float *)(tmp_i8 + tmp_i9) = local_64;
        *(float *)(tmp_i8 + 4 + tmp_i9) = local_60;
        *(float *)(tmp_i8 + 8 + tmp_i9) = local_5c;
        *(uint32_t *)(tmp_i8 + 0x4010 + tmp_i5 * 8) = local_58;
        *(uint32_t *)(tmp_i8 + 0x4014 + tmp_i5 * 8) = local_54;
        *(uint8_t *)(tmp_i8 + 0x6018 + tmp_i5 * 4) = local_50;
        *(uint8_t *)(tmp_i8 + 0x6019 + tmp_i5 * 4) = local_4f;
        *(uint8_t *)(tmp_i8 + 0x601a + tmp_i5 * 4) = local_4e;
        *(uint8_t *)(tmp_i8 + 0x601b + tmp_i5 * 4) = local_4d;
        *(int *)(tmp_i8 + 0x7020 + tmp_i6 * 4) = tmp_i5;
        *(int *)(tmp_i8 + 0xd038) = tmp_i6 + 3;
        *(int *)(tmp_i8 + 0x701c) = tmp_i5 + 3;
      }
    }
  }
  return;
}

uint32_t CG_AtmosphericKludge(void)
{
  if (kludgeChecked == 0) {
    kludgeChecked = 1;
    kludgeResult = 0;
    return 0;
  }
  return kludgeResult;
}

void CG_EffectParse(uint32_t param_1)
{
  byte tmp_b1;
  int tmp_i2;
  int tmp_i3;
  byte *tmp_pb4;
  byte *tmp_pb5;
  int *tmp_pi6;
  bool tmp_b7;
  double tmp_d8;
  byte *__nptr;
  int local_114;
  float local_10c;
  float local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  int local_ec;
  byte local_dc;
  byte local_db [63];
  byte local_9c;
  byte local_9b [135];
  uint32_t uStack_14;
  
  uStack_14 = 0x38689;
  if (kludgeChecked == 0) {
    kludgeChecked = 1;
    kludgeResult = 0;
  }
  else if (kludgeResult != 0) {
    return;
  }
  tmp_pb5 = &local_9c;
  GHIDRA_FIELD(cg_atmFx, 272100, 4) = 0;
  GHIDRA_FIELD(cg_atmFx, 272096, 4) = 0;
  GHIDRA_FIELD(cg_atmFx, 272112, 4) = 0x42c80000;
  GHIDRA_FIELD(cg_atmFx, 272108, 4) = 0x42c80000;
  GHIDRA_FIELD(cg_atmFx, 272072, 4) = 0x3f333333;
  GHIDRA_FIELD(cg_atmFx, 272076, 4) = 0x3fc00000;
  Q_strncpyz(tmp_pb5,param_1,0x80);
  local_ec = 0;
  local_114 = 0;
  local_fc = 0.0;
  local_f4 = 300.0;
  local_f8 = 2.0;
  local_104 = 1.0;
  local_100 = 1.0;
  local_10c = 10.0;
  local_108 = 5.0;
  local_f0 = local_f4;
  while (tmp_b1 = *tmp_pb5, tmp_pb4 = tmp_pb5, tmp_b1 != 0) {
    while (tmp_pb5 = tmp_pb4, tmp_b1 != 0x3d) {
      do {
        if (tmp_b1 == 0x2c) goto LAB_000387a0;
        tmp_pb5 = tmp_pb5 + 1;
        tmp_b1 = *tmp_pb5;
      } while ((tmp_b1 != 0x3d) && (tmp_b1 != 0));
      if (tmp_b1 == 0) goto LAB_000387ab;
      if (tmp_b1 != 0x2c) break;
LAB_000387a0:
      tmp_pb4 = tmp_pb5 + 1;
      tmp_b1 = *tmp_pb4;
      if (tmp_b1 == 0) goto LAB_000387ab;
    }
    tmp_b1 = tmp_pb5[1];
    __nptr = tmp_pb5 + 1;
    *tmp_pb5 = 0;
    tmp_pb5 = __nptr;
    if (tmp_b1 == 0x2c) {
      tmp_b1 = 0x2c;
    }
    else {
      do {
        tmp_b7 = tmp_b1 == 0;
        tmp_b1 = 0;
        if (tmp_b7) break;
        tmp_pb5 = tmp_pb5 + 1;
        tmp_b1 = *tmp_pb5;
      } while (tmp_b1 != 0x2c);
    }
    if (tmp_b1 != 0) {
      *tmp_pb5 = 0;
      tmp_pb5 = tmp_pb5 + 1;
    }
    if (local_114 == 0) {
      tmp_i2 = Q_stricmp(tmp_pb4,"T");
      if (tmp_i2 != 0) {
        GHIDRA_FIELD(cg_atmFx, 272028, 4) = 0;
        CG_Printf("Atmospheric effect must start with a type.\n");
        return;
      }
      tmp_i2 = Q_stricmp(__nptr,&g_unk_00111f40);
      if (tmp_i2 == 0) {
        GHIDRA_FIELD(cg_atmFx, 272132, 4) = CG_RainParticleCheckVisible;
        GHIDRA_FIELD(cg_atmFx, 272136, 4) = CG_RainParticleGenerate;
        GHIDRA_FIELD(cg_atmFx, 272140, 4) = CG_RainParticleRender;
        GHIDRA_FIELD(cg_atmFx, 272116, 4) = 0xc45c0000;
        GHIDRA_FIELD(cg_atmFx, 272104, 4) = 0xc45c0000;
        local_114 = 1;
      }
      else {
        tmp_i2 = Q_stricmp(__nptr,"SNOW");
        if (tmp_i2 != 0) {
          GHIDRA_FIELD(cg_atmFx, 272028, 4) = 0;
          CG_Printf("Only effect type \'rain\' and \'snow\' are supported.\n");
          return;
        }
        GHIDRA_FIELD(cg_atmFx, 272132, 4) = CG_SnowParticleCheckVisible;
        GHIDRA_FIELD(cg_atmFx, 272136, 4) = CG_SnowParticleGenerate;
        GHIDRA_FIELD(cg_atmFx, 272140, 4) = CG_SnowParticleRender;
        GHIDRA_FIELD(cg_atmFx, 272116, 4) = 0xc2a00000;
        GHIDRA_FIELD(cg_atmFx, 272104, 4) = 0xc2a00000;
        local_114 = 2;
      }
    }
    else {
      tmp_i2 = Q_stricmp(tmp_pb4,"B");
      if (tmp_i2 == 0) {
        tmp_pb4 = &local_dc;
        Q_strncpyz(tmp_pb4,__nptr,0x40);
        tmp_b1 = local_dc;
        while ((tmp_b1 & 0xdf) != 0) {
          tmp_pb4 = tmp_pb4 + 1;
          tmp_b1 = *tmp_pb4;
        }
        if (tmp_b1 == 0) {
          tmp_d8 = strtod((char *)__nptr,(char **)0x0);
          local_10c = (float)tmp_d8;
          local_108 = local_10c;
        }
        else {
          *tmp_pb4 = 0;
          tmp_d8 = strtod((char *)__nptr,(char **)0x0);
          local_108 = (float)tmp_d8;
          tmp_d8 = strtod((char *)(tmp_pb4 + 1),(char **)0x0);
          local_10c = (float)tmp_d8;
        }
      }
      else {
        tmp_i2 = Q_stricmp(tmp_pb4,&g_unk_00116f00);
        if (tmp_i2 == 0) {
          tmp_pb4 = &local_dc;
          Q_strncpyz(tmp_pb4,__nptr,0x40);
          tmp_b1 = local_dc;
          while ((tmp_b1 & 0xdf) != 0) {
            tmp_pb4 = tmp_pb4 + 1;
            tmp_b1 = *tmp_pb4;
          }
          if (tmp_b1 == 0) {
            tmp_d8 = strtod((char *)__nptr,(char **)0x0);
            local_104 = (float)tmp_d8;
            local_100 = local_104;
          }
          else {
            *tmp_pb4 = 0;
            tmp_d8 = strtod((char *)__nptr,(char **)0x0);
            local_100 = (float)tmp_d8;
            tmp_d8 = strtod((char *)(tmp_pb4 + 1),(char **)0x0);
            local_104 = (float)tmp_d8;
          }
        }
        else {
          tmp_i2 = Q_stricmp(tmp_pb4,"G");
          if (tmp_i2 == 0) {
            tmp_pb4 = &local_dc;
            Q_strncpyz(tmp_pb4,__nptr,0x40);
            tmp_b1 = local_dc;
            while ((tmp_b1 & 0xdf) != 0) {
              tmp_pb4 = tmp_pb4 + 1;
              tmp_b1 = *tmp_pb4;
            }
            if (tmp_b1 == 0) {
              tmp_d8 = strtod((char *)__nptr,(char **)0x0);
              local_fc = (float)tmp_d8;
              local_f8 = local_fc;
            }
            else {
              *tmp_pb4 = 0;
              tmp_d8 = strtod((char *)__nptr,(char **)0x0);
              local_fc = (float)tmp_d8;
              tmp_d8 = strtod((char *)(tmp_pb4 + 1),(char **)0x0);
              local_f8 = (float)tmp_d8;
            }
          }
          else {
            tmp_i2 = Q_stricmp(tmp_pb4,&g_unk_00111f45);
            if (tmp_i2 == 0) {
              tmp_pb4 = &local_dc;
              Q_strncpyz(tmp_pb4,__nptr,0x40);
              tmp_b1 = local_dc;
              while ((tmp_b1 & 0xdf) != 0) {
                tmp_pb4 = tmp_pb4 + 1;
                tmp_b1 = *tmp_pb4;
              }
              if (tmp_b1 == 0) {
                tmp_d8 = strtod((char *)__nptr,(char **)0x0);
                GHIDRA_FIELD(cg_atmFx, 272096, 4) = (uint32_t)tmp_d8;
                GHIDRA_FIELD(cg_atmFx, 272100, 4) = GHIDRA_FIELD(cg_atmFx, 272096, 4);
              }
              else {
                *tmp_pb4 = 0;
                tmp_d8 = strtod((char *)__nptr,(char **)0x0);
                GHIDRA_FIELD(cg_atmFx, 272096, 4) = (uint32_t)tmp_d8;
                tmp_d8 = strtod((char *)(tmp_pb4 + 1),(char **)0x0);
                GHIDRA_FIELD(cg_atmFx, 272100, 4) = (uint32_t)tmp_d8;
              }
            }
            else {
              tmp_i2 = Q_stricmp(tmp_pb4,&g_unk_00111f48);
              if (tmp_i2 == 0) {
                tmp_pb4 = &local_dc;
                Q_strncpyz(tmp_pb4,__nptr,0x40);
                tmp_b1 = local_dc;
                while ((tmp_b1 & 0xdf) != 0) {
                  tmp_pb4 = tmp_pb4 + 1;
                  tmp_b1 = *tmp_pb4;
                }
                if (tmp_b1 == 0) {
                  tmp_d8 = strtod((char *)__nptr,(char **)0x0);
                  GHIDRA_FIELD(cg_atmFx, 272108, 4) = (uint32_t)tmp_d8;
                  GHIDRA_FIELD(cg_atmFx, 272112, 4) = GHIDRA_FIELD(cg_atmFx, 272108, 4);
                }
                else {
                  *tmp_pb4 = 0;
                  tmp_d8 = strtod((char *)__nptr,(char **)0x0);
                  GHIDRA_FIELD(cg_atmFx, 272108, 4) = (uint32_t)tmp_d8;
                  tmp_d8 = strtod((char *)(tmp_pb4 + 1),(char **)0x0);
                  GHIDRA_FIELD(cg_atmFx, 272112, 4) = (uint32_t)tmp_d8;
                }
              }
              else {
                tmp_i2 = Q_stricmp(tmp_pb4,"W");
                if (tmp_i2 == 0) {
                  tmp_pb4 = &local_dc;
                  Q_strncpyz(tmp_pb4,__nptr,0x40);
                  tmp_b1 = local_dc;
                  while ((tmp_b1 & 0xdf) != 0) {
                    tmp_pb4 = tmp_pb4 + 1;
                    tmp_b1 = *tmp_pb4;
                  }
                  if (tmp_b1 == 0) {
                    tmp_d8 = strtod((char *)__nptr,(char **)0x0);
                    GHIDRA_FIELD(cg_atmFx, 272072, 4) = (uint32_t)tmp_d8;
                    GHIDRA_FIELD(cg_atmFx, 272076, 4) = GHIDRA_FIELD(cg_atmFx, 272072, 4);
                  }
                  else {
                    *tmp_pb4 = 0;
                    tmp_d8 = strtod((char *)__nptr,(char **)0x0);
                    GHIDRA_FIELD(cg_atmFx, 272072, 4) = (uint32_t)tmp_d8;
                    tmp_d8 = strtod((char *)(tmp_pb4 + 1),(char **)0x0);
                    GHIDRA_FIELD(cg_atmFx, 272076, 4) = (uint32_t)tmp_d8;
                  }
                }
                else {
                  tmp_i2 = Q_stricmp(tmp_pb4,&g_unk_0011ccf2);
                  if (tmp_i2 == 0) {
                    tmp_pb4 = &local_dc;
                    Q_strncpyz(tmp_pb4,__nptr,0x40);
                    tmp_b1 = local_dc;
                    while ((tmp_b1 & 0xdf) != 0) {
                      tmp_pb4 = tmp_pb4 + 1;
                      tmp_b1 = *tmp_pb4;
                    }
                    if (tmp_b1 == 0) {
                      tmp_d8 = strtod((char *)__nptr,(char **)0x0);
                      local_f4 = (float)tmp_d8;
                      local_f0 = local_f4;
                    }
                    else {
                      *tmp_pb4 = 0;
                      tmp_d8 = strtod((char *)__nptr,(char **)0x0);
                      local_f0 = (float)tmp_d8;
                      tmp_d8 = strtod((char *)(tmp_pb4 + 1),(char **)0x0);
                      local_f4 = (float)tmp_d8;
                    }
                  }
                  else {
                    tmp_i2 = Q_stricmp(tmp_pb4,&g_unk_00122051);
                    if (tmp_i2 == 0) {
                      tmp_pb4 = &local_dc;
                      Q_strncpyz(tmp_pb4,__nptr,0x40);
                      tmp_b1 = local_dc;
                      while ((tmp_b1 & 0xdf) != 0) {
                        tmp_pb4 = tmp_pb4 + 1;
                        tmp_b1 = *tmp_pb4;
                      }
                      if (tmp_b1 != 0) {
                        *tmp_pb4 = 0;
                        strtod((char *)__nptr,(char **)0x0);
                        __nptr = tmp_pb4 + 1;
                      }
                      tmp_d8 = strtod((char *)__nptr,(char **)0x0);
                      local_ec = (int)ROUND(tmp_d8);
                    }
                    else {
                      CG_Printf("Unknown effect key \'%s\'.\n",tmp_pb4);
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
LAB_000387ab:
  if ((local_114 == 0) ||
     (tmp_i2 = BG_LoadTraceMap(0x10f69ac,&g_unk_010abd54,&g_unk_010abd5c), tmp_i2 == 0)) {
    GHIDRA_FIELD(cg_atmFx, 272028, 4) = 0xffffffff;
    return;
  }
  GHIDRA_FIELD(cg_atmFx, 272088, 4) = 0;
  if (-1 < local_ec) {
    GHIDRA_FIELD(cg_atmFx, 272088, 4) = local_ec;
  }
  GHIDRA_FIELD(cg_atmFx, 272064, 4) = (uint32_t)ROUND(local_108 * 1000.0);
  GHIDRA_FIELD(cg_atmFx, 272068, 4) = (uint32_t)ROUND(local_10c * 1000.0);
  GHIDRA_FIELD(cg_atmFx, 272056, 4) = (uint32_t)ROUND(local_100 * 1000.0);
  GHIDRA_FIELD(cg_atmFx, 272060, 4) = (uint32_t)ROUND(local_104 * 1000.0);
  GHIDRA_FIELD(cg_atmFx, 272048, 4) = (uint32_t)ROUND(local_fc * 1000.0);
  GHIDRA_FIELD(cg_atmFx, 272052, 4) = (uint32_t)ROUND(local_f8 * 1000.0);
  GHIDRA_FIELD(cg_atmFx, 272080, 4) = (uint32_t)ROUND(local_f0);
  GHIDRA_FIELD(cg_atmFx, 272084, 4) = (uint32_t)ROUND(local_f4);
  GHIDRA_FIELD(cg_atmFx, 272028, 4) = GHIDRA_FIELD(cg_atmFx, 272084, 4);
  if ((int)GHIDRA_FIELD(cg_atmFx, 272084, 4) < (int)GHIDRA_FIELD(cg_atmFx, 272080, 4)) {
    GHIDRA_FIELD(cg_atmFx, 272028, 4) = GHIDRA_FIELD(cg_atmFx, 272080, 4);
  }
  if (4000 < (int)GHIDRA_FIELD(cg_atmFx, 272028, 4)) {
    GHIDRA_FIELD(cg_atmFx, 272028, 4) = 4000;
  }
  if (local_114 == 1) {
    GHIDRA_FIELD(cg_atmFx, 272092, 4) = 1;
    GHIDRA_FIELD(cg_atmFx, 272000, 4) = trap_R_RegisterShader("gfx/misc/raindrop");
    if (GHIDRA_FIELD(cg_atmFx, 272000, 4) != 0) goto LAB_00038cfa;
    GHIDRA_FIELD(cg_atmFx, 272000, 4) = 0xffffffff;
  }
  else if (local_114 == 2) {
    GHIDRA_FIELD(cg_atmFx, 272092, 4) = 1;
    GHIDRA_FIELD(cg_atmFx, 272000, 4) = trap_R_RegisterShader("gfx/misc/snow");
    goto LAB_00038cfa;
  }
  GHIDRA_FIELD(cg_atmFx, 272092, 4) = 0;
LAB_00038cfa:
  if (0 < (int)GHIDRA_FIELD(cg_atmFx, 272028, 4)) {
    tmp_i2 = 0;
    tmp_pi6 = (int *)(cg_atmFx + 0x3c);
    do {
      tmp_i3 = rand();
      tmp_i2 = tmp_i2 + 1;
      *tmp_pi6 = tmp_i3 % 1000 + 1000;
      tmp_pi6 = tmp_pi6 + 0x11;
    } while (tmp_i2 < (int)GHIDRA_FIELD(cg_atmFx, 272028, 4));
  }
  CG_EffectGust();
  return;
}

uint32_t CG_RegisterCharacter(uint32_t param_1,int param_2)
{
  uint8_t *tmp_pu1;
  float tmp_f2;
  uint tmp_u3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  uint32_t *tmp_pu7;
  char *tmp_pc8;
  long tmp_l9;
  uint32_t tmp_u10;
  uint tmp_u11;
  uint8_t **tmp_ppu12;
  char *__s;
  uint32_t *tmp_pu13;
  int *tmp_pi14;
  uint8_t **tmp_ppu15;
  bool tmp_b16;
  double tmp_d17;
  int local_480;
  float local_47c;
  uint32_t *local_474;
  int local_46c;
  uint8_t **local_468;
  char *local_448 [5];
  float local_434;
  uint32_t local_430;
  float local_42c;
  uint8_t local_428 [64];
  uint8_t local_3e8 [64];
  uint8_t *local_3a8 [12];
  float local_378;
  uint32_t local_374;
  float local_370;
  uint32_t local_348 [29];
  int local_2d4;
  uint32_t local_2d0;
  uint32_t local_2c8;
  int local_2b8;
  uint32_t local_2b4;
  uint32_t local_2ac;
  char local_25c [4];
  uint32_t auStack_258 [15];
  uint8_t local_21c [64];
  uint8_t local_1dc [64];
  uint8_t local_19c [64];
  uint8_t local_15c [64];
  uint8_t local_11c [64];
  uint8_t local_dc [64];
  uint8_t local_9c [64];
  uint8_t local_5c [72];
  uint32_t uStack_14;
  
  tmp_u3 = 0;
  uStack_14 = 0x3940b;
  do {
    tmp_pc8 = local_25c + tmp_u3;
    tmp_pc8[0] = '\0';
    tmp_pc8[1] = '\0';
    tmp_pc8[2] = '\0';
    tmp_pc8[3] = '\0';
    *(uint32_t *)((int)auStack_258 + tmp_u3) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0x240);
  tmp_i4 = BG_ParseCharacterFile(param_1,local_25c);
  if (tmp_i4 == 0) {
    return 0;
  }
  tmp_i4 = trap_R_RegisterModel(local_15c);
  *(int *)(param_2 + 0x40) = tmp_i4;
  if (tmp_i4 == 0) {
    CG_Printf("^3WARNING: failed to register mesh \'%s\' referenced from \'%s\'\n",local_15c,param_1
             );
  }
  COM_StripExtension(local_15c,local_428);
  tmp_u5 = va("%s_%s.skin",local_428,local_11c);
  tmp_i4 = trap_R_RegisterSkin(tmp_u5);
  *(int *)(param_2 + 0x44) = tmp_i4;
  if (tmp_i4 == 0) {
    CG_Printf("^3WARNING: failed to register skin \'%s\' referenced from \'%s\'\n",tmp_u5,param_1);
  }
  else {
    tmp_ppu12 = &cg_accessories;
    while( true ) {
      tmp_i4 = trap_R_GetSkinModel(tmp_i4,*tmp_ppu12,local_3e8);
      if (tmp_i4 != 0) {
        tmp_pu1 = tmp_ppu12[1];
        tmp_i6 = trap_R_RegisterModel(local_3e8);
        tmp_i4 = param_2 + (int)tmp_pu1 * 4;
        *(int *)(tmp_i4 + 0x48) = tmp_i6;
        if (tmp_i6 == 0) {
          CG_Printf("^3WARNING: failed to register accessory \'%s\' referenced from \'%s\'->\'%s\'\n"
                    ,local_3e8,param_1,tmp_u5);
        }
        else {
          COM_StripExtension(local_3e8,local_348);
          tmp_u10 = va("_%s.skin",local_11c);
          Q_strcat(local_348,0x40,tmp_u10);
          tmp_u10 = trap_R_RegisterSkin(local_348);
          *(uint32_t *)(tmp_i4 + 0x74) = tmp_u10;
        }
      }
      if (tmp_ppu12 == (uint8_t **)0x13d868) break;
      tmp_ppu12 = tmp_ppu12 + 2;
      tmp_i4 = *(int *)(param_2 + 0x44);
    }
    tmp_ppu12 = &cg_headAccessories;
    do {
      tmp_i4 = trap_R_GetSkinModel(*(uint32_t *)(param_2 + 0x44),*tmp_ppu12,local_3e8);
      if (tmp_i4 != 0) {
        tmp_pu1 = tmp_ppu12[1];
        tmp_i6 = trap_R_RegisterModel(local_3e8);
        tmp_i4 = param_2 + (int)tmp_pu1 * 4;
        *(int *)(tmp_i4 + 0x48) = tmp_i6;
        if (tmp_i6 == 0) {
          CG_Printf("^3WARNING: failed to register accessory \'%s\' referenced from \'%s\'->\'%s\'\n"
                    ,local_3e8,param_1,tmp_u5);
        }
        else {
          COM_StripExtension(local_3e8,local_348);
          tmp_u10 = va("_%s.skin",local_11c);
          Q_strcat(local_348,0x40,tmp_u10);
          tmp_u10 = trap_R_RegisterSkin(local_348);
          *(uint32_t *)(tmp_i4 + 0x74) = tmp_u10;
        }
      }
      tmp_ppu12 = tmp_ppu12 + 2;
    } while (tmp_ppu12 != (uint8_t **)&g_unk_0013d828);
  }
  local_474 = local_348;
  COM_StripExtension(local_15c,local_428);
  tmp_u3 = 0x40;
  tmp_pu13 = (uint32_t *)(param_2 + 0x7a8);
  tmp_b16 = ((uint)tmp_pu13 & 1) != 0;
  tmp_pu7 = tmp_pu13;
  if (tmp_b16) {
    tmp_u3 = 0x3f;
    *(uint8_t *)(param_2 + 0x7a8) = 0;
    tmp_pu7 = (uint32_t *)(param_2 + 0x7a9);
  }
  if (((uint)tmp_pu7 & 2) != 0) {
    *(uint16_t *)tmp_pu7 = 0;
    tmp_u3 = tmp_u3 - 2;
    tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
  }
  tmp_u11 = 0;
  do {
    *(uint32_t *)((int)tmp_pu7 + tmp_u11) = 0;
    *(uint32_t *)((int)tmp_pu7 + tmp_u11 + 4) = 0;
    tmp_u11 = tmp_u11 + 8;
  } while (tmp_u11 < (tmp_u3 & 0xfffffff8));
  tmp_pu7 = (uint32_t *)((int)tmp_pu7 + tmp_u11);
  if ((tmp_u3 & 4) != 0) {
    *tmp_pu7 = 0;
    tmp_pu7 = tmp_pu7 + 1;
  }
  if ((tmp_u3 & 2) != 0) {
    *(uint16_t *)tmp_pu7 = 0;
    tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
  }
  if (tmp_b16) {
    *(uint8_t *)tmp_pu7 = 0;
  }
  tmp_i4 = trap_FS_FOpenFile("models/body.gibs",local_474,0);
  if (0 < tmp_i4) {
    if (tmp_i4 < 99999) {
      trap_FS_Read(bigTextBuffer,tmp_i4,local_348[0]);
      bigTextBuffer[tmp_i4] = 0;
      trap_FS_FCloseFile(local_348[0]);
      local_3a8[0] = bigTextBuffer;
      do {
        tmp_i4 = COM_Parse(local_3a8);
        if (tmp_i4 == 0) break;
        tmp_pu7 = tmp_pu13 + 1;
        tmp_u5 = trap_R_RegisterModel(tmp_i4);
        *tmp_pu13 = tmp_u5;
        tmp_pu13 = tmp_pu7;
      } while (tmp_pu7 != (uint32_t *)(param_2 + 0x7e8));
    }
    else {
      CG_Printf("File %s too long\n","body.gibs");
    }
  }
  if (local_25c[0] != '\0') {
    tmp_i4 = trap_R_RegisterModel(local_25c);
    *(int *)(param_2 + 0x7e8) = tmp_i4;
    if (tmp_i4 == 0) {
      CG_Printf("^3WARNING: failed to register undressed corpse model \'%s\' referenced from \'%s\'\n"
                ,local_25c,param_1);
    }
    COM_StripExtension(local_25c,local_428);
    tmp_u5 = va("%s_%s.skin",local_428,local_21c);
    tmp_i4 = trap_R_RegisterSkin(tmp_u5);
    *(int *)(param_2 + 0x7ec) = tmp_i4;
    if (tmp_i4 == 0) {
      CG_Printf("^3WARNING: failed to register undressed corpse skin \'%s\' referenced from \'%s\'\n"
                ,tmp_u5,param_1);
    }
  }
  tmp_i4 = trap_R_RegisterModel(local_dc);
  *(int *)(param_2 + 0xa0) = tmp_i4;
  if (tmp_i4 == 0) {
    CG_Printf("^3WARNING: failed to register hud head model \'%s\' referenced from \'%s\'\n",
              local_dc,param_1);
  }
  tmp_i4 = trap_R_RegisterSkin(local_9c);
  *(int *)(param_2 + 0xa4) = tmp_i4;
  if (tmp_i4 == 0) {
    CG_Printf("^3WARNING: failed to register hud head skin \'%s\' referenced from \'%s\'\n",local_9c
              ,param_1);
  }
  tmp_i4 = trap_FS_FOpenFile(local_5c,local_474,0);
  if (0 < tmp_i4) {
    if (tmp_i4 < 99999) {
      trap_FS_Read(bigTextBuffer,tmp_i4,local_348[0]);
      bigTextBuffer[tmp_i4] = 0;
      trap_FS_FCloseFile(local_348[0]);
      tmp_pi14 = (int *)(param_2 + 0xf4);
      local_3a8[0] = bigTextBuffer;
      do {
        tmp_pc8 = (char *)COM_Parse(local_3a8);
        if (tmp_pc8 == (char *)0x0) {
LAB_00039943:
          CG_Printf("Error parsing hud head animation file: %s",local_5c);
          goto LAB_00039959;
        }
        tmp_l9 = strtol(tmp_pc8,(char **)0x0,10);
        tmp_pi14[-2] = tmp_l9;
        tmp_pc8 = (char *)COM_Parse(local_3a8);
        if (tmp_pc8 == (char *)0x0) goto LAB_00039943;
        tmp_l9 = strtol(tmp_pc8,(char **)0x0,10);
        tmp_pi14[-1] = tmp_l9;
        tmp_pc8 = (char *)COM_Parse(local_3a8);
        if (tmp_pc8 == (char *)0x0) goto LAB_00039943;
        tmp_d17 = strtod(tmp_pc8,(char **)0x0);
        tmp_i4 = 1000;
        if ((float)tmp_d17 != 0.0) {
          tmp_i4 = (int)ROUND(1000.0 / (float)tmp_d17);
        }
        tmp_pi14[1] = tmp_i4;
        tmp_pi14[2] = tmp_i4;
        tmp_pc8 = (char *)COM_Parse(local_3a8);
        if (tmp_pc8 == (char *)0x0) goto LAB_00039943;
        tmp_l9 = strtol(tmp_pc8,(char **)0x0,10);
        *tmp_pi14 = tmp_l9;
        if (tmp_pi14[-1] < tmp_l9) {
          *tmp_pi14 = tmp_pi14[-1];
        }
        else if (tmp_l9 < 0) {
          *tmp_pi14 = 0;
        }
        tmp_pi14 = tmp_pi14 + 0x1c;
      } while (tmp_pi14 != (int *)(param_2 + 0x7f4));
      goto LAB_00039976;
    }
    CG_Printf("File %s too long\n",local_5c);
  }
LAB_00039959:
  CG_Printf("^3WARNING: failed to register hud head animations \'%s\' referenced from \'%s\'\n",
            local_5c,param_1);
LAB_00039976:
  __s = (char *)0x0;
  tmp_pc8 = cgs + 0x20554;
  do {
    if ((*tmp_pc8 == '\0') || (tmp_pc8[0x40] == '\0')) {
      if (__s == (char *)0x0) {
        __s = tmp_pc8;
      }
    }
    else {
      tmp_i4 = Q_stricmp(tmp_pc8,local_1dc);
      if ((tmp_i4 == 0) && (tmp_i4 = Q_stricmp(tmp_pc8 + 0x40,local_19c), tmp_i4 == 0)) {
        *(char **)(param_2 + 0x7f0) = tmp_pc8;
        return 1;
      }
    }
    tmp_pc8 = tmp_pc8 + 0xfeae8;
  } while (tmp_pc8 != cgs + 0x1ff6254);
  if (__s == (char *)0x0) {
    CG_Error("unable to find a free modelinfo slot, cannot continue\n");
  }
  else {
    *(char **)(param_2 + 0x7f0) = __s;
    memset(__s,0,0xfeae8);
  }
  Q_strncpyz(*(uint32_t *)(param_2 + 0x7f0),local_1dc,0x40);
  Q_strncpyz(*(int *)(param_2 + 0x7f0) + 0x40,local_19c,0x40);
  BG_R_RegisterAnimationGroup(local_1dc,*(uint32_t *)(param_2 + 0x7f0));
  local_448[0] = "tag_footleft";
  local_448[1] = "tag_footright";
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)local_474 + tmp_u3) = 0;
    *(uint32_t *)((int)local_348 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0xe8);
  *(uint32_t *)((int)local_474 + tmp_u3) = 0;
  local_348[2] = *(uint32_t *)(param_2 + 0x40);
  tmp_i4 = *(int *)(param_2 + 0x7f0);
  tmp_i6 = *(int *)(tmp_i4 + 0x89c);
  if (0 < tmp_i6) {
    local_46c = 0;
    do {
      while (tmp_pu13 = *(uint32_t **)(tmp_i4 + 0x9c + local_46c * 4), (int)tmp_pu13[0x16] < 0) {
        if ((int)tmp_pu13[0x12] < 1) {
          tmp_f2 = 0.0;
          local_47c = 0.0;
        }
        else {
          local_480 = 0;
          local_47c = 0.0;
          do {
            tmp_i4 = 0;
            local_2d4 = local_480 + tmp_pu13[0x11];
            local_2d0 = *tmp_pu13;
            tmp_ppu15 = local_3a8;
            local_2c8 = local_2d0;
            local_2b8 = local_2d4;
            local_2b4 = local_2d0;
            local_2ac = local_2d0;
            while( true ) {
              tmp_pc8 = local_448[tmp_i4];
              tmp_i6 = trap_R_LerpTag(tmp_ppu15,local_474,tmp_pc8,0);
              if (tmp_i6 < 0) {
                CG_Error("CG_CalcMoveSpeeds: unable to find tag %s, cannot calculate movespeed",
                         tmp_pc8);
              }
              tmp_ppu15 = tmp_ppu15 + 0xc;
              if (tmp_i4 == 1) break;
              tmp_i4 = 1;
            }
            if ((*(byte *)(tmp_pu13 + 0x1a) & 1) == 0) {
              tmp_f2 = (float)local_448[(uint)(local_370 <= (float)local_3a8[2]) * 3 + 2] -
                      (float)local_3a8[(uint)(local_370 <= (float)local_3a8[2]) * 0xc];
            }
            else {
              tmp_f2 = (float)local_448[(uint)((float)local_3a8[0] <= local_378) * 3 + 4] -
                      (float)local_3a8[(uint)((float)local_3a8[0] <= local_378) * 0xc + 2];
            }
            local_47c = ABS(tmp_f2) + local_47c;
            local_448[2] = local_3a8[0];
            local_480 = local_480 + 1;
            local_448[3] = local_3a8[1];
            local_448[4] = local_3a8[2];
            local_434 = local_378;
            local_430 = local_374;
            local_42c = local_370;
          } while (local_480 < (int)tmp_pu13[0x12]);
          tmp_f2 = (float)local_480;
        }
        local_46c = local_46c + 1;
        tmp_pu13[0x16] = (int)ROUND(((local_47c / tmp_f2) * 1000.0) / (float)(int)tmp_pu13[0x14]);
        tmp_i4 = *(int *)(param_2 + 0x7f0);
        tmp_i6 = *(int *)(tmp_i4 + 0x89c);
        if (tmp_i6 <= local_46c) goto LAB_00039d3b;
      }
      local_46c = local_46c + 1;
    } while (local_46c < tmp_i6);
  }
LAB_00039d3b:
  local_468 = local_3a8;
  tmp_i4 = trap_FS_FOpenFile(local_19c,local_468,0);
  if (0 < tmp_i4) {
    if (tmp_i4 < 99999) {
      trap_FS_Read(bigTextBuffer,tmp_i4,local_3a8[0]);
      bigTextBuffer[tmp_i4] = 0;
      trap_FS_FCloseFile(local_3a8[0]);
      BG_AnimParseAnimScript(*(uint32_t *)(param_2 + 0x7f0),0x11103b4,local_19c,bigTextBuffer);
      return 1;
    }
    CG_Printf("File %s is too long\n",local_474);
  }
  CG_Printf("^3WARNING: failed to load animation files referenced from \'%s\'\n",param_1);
  return 0;
}

int CG_CharacterForClientinfo(int param_1,int param_2)
{
  int tmp_i1;
  
  if (param_2 != 0) {
    if (*(int *)(param_2 + 4) == 0x26) {
      if (*(int *)(param_2 + 0xfc) < 0) {
        tmp_i1 = *(int *)(param_2 + 0xa4);
        if (3 < tmp_i1) {
          tmp_i1 = tmp_i1 + -4;
        }
        tmp_i1 = BG_GetCharacter(tmp_i1,*(uint32_t *)(param_2 + 0xa8));
        return tmp_i1;
      }
      return *(int *)(cgs + *(int *)(param_2 + 0xfc) * 4 + 0x7fc8);
    }
    if ((*(uint *)(param_2 + 0xe4) & 0x80) != 0) {
      tmp_i1 = BG_GetCharacter((*(int *)(param_1 + 0x88) == 1) + '\x01',
                              (int)*(uint *)(param_2 + 0xe4) >> 8 & 7);
      return tmp_i1;
    }
  }
  tmp_i1 = *(int *)(param_1 + 0x168);
  if (tmp_i1 == 0) {
    tmp_i1 = BG_GetCharacter(*(uint32_t *)(param_1 + 0x88),*(uint32_t *)(param_1 + 0xac));
  }
  return tmp_i1;
}

void CG_CharacterForPlayerstate(int param_1)
{
  int tmp_i1;
  byte tmp_b2;
  
  if (*(int *)(param_1 + 0x16c) != 0) {
    tmp_b2 = *(int *)(param_1 + 0x170) != 0;
    if (*(int *)(param_1 + 0x174) != 0) {
      tmp_b2 = tmp_b2 | 2;
    }
    if (*(int *)(param_1 + 0x178) != 0) {
      tmp_b2 = tmp_b2 | 4;
    }
    BG_GetCharacter((*(int *)(cgs + *(int *)(param_1 + 0xa0) * 0x1a4 + 0x9494) == 1) + '\x01',tmp_b2)
    ;
    return;
  }
  tmp_i1 = *(int *)(param_1 + 0xa0) * 0x1a4;
  BG_GetCharacter(*(uint32_t *)(cgs + tmp_i1 + 0x9494),*(uint32_t *)(cgs + tmp_i1 + 0x94b8));
  return;
}

void CG_RegisterPlayerClasses(void)
{
  char *tmp_pc1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  int local_24;
  
  local_24 = 1;
  while( true ) {
    tmp_i6 = 0;
    do {
      tmp_pu2 = (uint32_t *)BG_GetPlayerClassInfo(local_24,tmp_i6);
      tmp_u3 = BG_GetCharacter(local_24,tmp_i6);
      Q_strncpyz(tmp_u3,tmp_pu2[1],0x40);
      tmp_i4 = CG_RegisterCharacter(tmp_u3,tmp_u3);
      if (tmp_i4 == 0) {
        tmp_u5 = BG_ClassnameForNumber(*tmp_pu2);
        if (local_24 == 1) {
          tmp_pc1 = "infoAxis";
        }
        else {
          tmp_pc1 = "infoAllied";
        }
        CG_Error("ERROR: CG_RegisterPlayerClasses: failed to load character file \'%s\' for the %s %s\n"
                 ,tmp_u3,tmp_pc1 + 4,tmp_u5);
      }
      tmp_i4 = trap_R_RegisterShaderNoMip(tmp_pu2[2]);
      tmp_pu2[10] = tmp_i4;
      if (tmp_i4 == 0) {
        tmp_u3 = BG_ClassnameForNumber(*tmp_pu2);
        if (local_24 == 1) {
          tmp_pc1 = "infoAxis";
        }
        else {
          tmp_pc1 = "infoAllied";
        }
        CG_Printf("^3WARNING: failed to load class icon \'%s\' for the %s %s\n",tmp_pu2[2],tmp_pc1 + 4
                  ,tmp_u3);
      }
      tmp_i4 = trap_R_RegisterShaderNoMip(tmp_pu2[3]);
      tmp_pu2[0xb] = tmp_i4;
      if (tmp_i4 == 0) {
        tmp_u3 = BG_ClassnameForNumber(*tmp_pu2);
        if (local_24 == 1) {
          tmp_pc1 = "infoAxis";
        }
        else {
          tmp_pc1 = "infoAllied";
        }
        CG_Printf("^3WARNING: failed to load icon arrow \'%s\' for the %s %s\n",tmp_pu2[3],tmp_pc1 + 4
                  ,tmp_u3);
      }
      tmp_i6 = tmp_i6 + 1;
    } while (tmp_i6 != 5);
    if (local_24 == 2) break;
    local_24 = 2;
  }
  return;
}

uint32_t CG_CommandCentreSpawnPointClick_part_3(void)
{
  byte tmp_b1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  
  tmp_pu5 = &cg;
  if (1 < g_unk_010ad280) {
    tmp_i6 = 1;
    do {
      while (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3) {
        tmp_i4 = *(int *)(tmp_i6 * 4 + 0x10ad080);
        if (tmp_i4 == 0) goto LAB_0003ab8f;
        tmp_i3 = CG_LimboPanel_GetRealTeam();
        if (tmp_i4 == tmp_i3) {
          tmp_b1 = *(byte *)(tmp_i6 * 4 + 0x10ad081);
          goto joined_r0x0003ae25;
        }
LAB_0003ad15:
        tmp_i6 = tmp_i6 + 1;
        tmp_pu5 = tmp_pu5 + 3;
        if (g_unk_010ad280 <= tmp_i6) {
          return 0;
        }
      }
      tmp_b1 = *(byte *)(tmp_i6 * 4 + 0x10ad081);
joined_r0x0003ae25:
      if ((tmp_b1 & 1) == 0) {
LAB_0003ab8f:
        if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
          tmp_i4 = (int)ROUND((float)tmp_pu5[0x19515]);
          if (((int)GHIDRA_FIELD(cgs, 33575852, 4) < tmp_i4) && (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
            if (((int)GHIDRA_FIELD(cgs, 33575856, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 1)) {
              if (((int)GHIDRA_FIELD(cgs, 33575860, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 2)) {
                if (((int)GHIDRA_FIELD(cgs, 33575864, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 3)) {
                  if (((int)GHIDRA_FIELD(cgs, 33575868, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 4)) {
                    if (((int)GHIDRA_FIELD(cgs, 33575872, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 5)) {
                      if (((int)GHIDRA_FIELD(cgs, 33575876, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 6)) {
                        if (((int)GHIDRA_FIELD(cgs, 33575880, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 7)) {
                          if (((int)GHIDRA_FIELD(cgs, 33575884, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 8)) {
                            if (((int)GHIDRA_FIELD(cgs, 33575888, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 9)) {
                              if (((int)GHIDRA_FIELD(cgs, 33575892, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 10)) {
                                if (((int)GHIDRA_FIELD(cgs, 33575896, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xb)) {
                                  if (((int)GHIDRA_FIELD(cgs, 33575900, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xc))
                                  {
                                    if (((int)GHIDRA_FIELD(cgs, 33575904, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xd)
                                       ) {
                                      if ((tmp_i4 <= (int)GHIDRA_FIELD(cgs, 33575908, 4)) ||
                                         (tmp_i4 = 0xf, GHIDRA_FIELD(cgs, 33575848, 4) == 0xe)) {
                                        tmp_i4 = 0xe;
                                      }
                                    }
                                    else {
                                      tmp_i4 = 0xd;
                                    }
                                  }
                                  else {
                                    tmp_i4 = 0xc;
                                  }
                                }
                                else {
                                  tmp_i4 = 0xb;
                                }
                              }
                              else {
                                tmp_i4 = 10;
                              }
                            }
                            else {
                              tmp_i4 = 9;
                            }
                          }
                          else {
                            tmp_i4 = 8;
                          }
                        }
                        else {
                          tmp_i4 = 7;
                        }
                      }
                      else {
                        tmp_i4 = 6;
                      }
                    }
                    else {
                      tmp_i4 = 5;
                    }
                  }
                  else {
                    tmp_i4 = 4;
                  }
                }
                else {
                  tmp_i4 = 3;
                }
              }
              else {
                tmp_i4 = 2;
              }
            }
            else {
              tmp_i4 = 1;
            }
            if (GHIDRA_FIELD(cgs, 33575848, 4) == tmp_i4) {
              CG_Printf("^3Warning: no valid command map layer for z\n");
              tmp_i4 = 0;
            }
          }
          else {
            tmp_i4 = 0;
          }
          if (GHIDRA_FIELD(cgs, 33685900, 4) != tmp_i4) goto LAB_0003ad15;
        }
        tmp_i4 = BG_RectContainsPoint
                          (*(float *)(&UNK_0006544c + (int)tmp_pu5) - 16.0,
                           (float)tmp_pu5[0x19514] - 16.0,0x42000000,0x42000000,(float)g_unk_010261a4,
                           (float)g_unk_010261a8);
        if (tmp_i4 != 0) {
          tmp_u2 = va("setspawnpt %i\n",tmp_i6);
          trap_SendConsoleCommand(tmp_u2);
          g_unk_010ad284 = tmp_i6;
          GHIDRA_FIELD(cgs, 33685972, 4) = 0xffffffff;
          return 1;
        }
        goto LAB_0003ad15;
      }
      tmp_i6 = tmp_i6 + 1;
      tmp_pu5 = tmp_pu5 + 3;
    } while (tmp_i6 < g_unk_010ad280);
  }
  return 0;
}

void CG_TransformToCommandMapCoord(float *param_1,float *param_2)
{
  *param_1 = (*param_1 - g_unk_010abd54) * g_unk_010abd64 * 352.0 + 64.0;
  *param_2 = (*param_2 - g_unk_010abd58) * g_unk_010abd68 * 352.0 + 23.0;
  return;
}

int CG_CurLayerForZ(int param_1)
{
  int tmp_i1;
  
  if (((int)GHIDRA_FIELD(cgs, 33575852, 4) < param_1) && (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
    if (((int)GHIDRA_FIELD(cgs, 33575856, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 1)) {
      if (((int)GHIDRA_FIELD(cgs, 33575860, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 2)) {
        if (((int)GHIDRA_FIELD(cgs, 33575864, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 3)) {
          if (((int)GHIDRA_FIELD(cgs, 33575868, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 4)) {
            if (((int)GHIDRA_FIELD(cgs, 33575872, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 5)) {
              if (((int)GHIDRA_FIELD(cgs, 33575876, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 6)) {
                if (((int)GHIDRA_FIELD(cgs, 33575880, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 7)) {
                  if (((int)GHIDRA_FIELD(cgs, 33575884, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 8)) {
                    if (((int)GHIDRA_FIELD(cgs, 33575888, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 9)) {
                      if (((int)GHIDRA_FIELD(cgs, 33575892, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 10)) {
                        if (((int)GHIDRA_FIELD(cgs, 33575896, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xb)) {
                          if (((int)GHIDRA_FIELD(cgs, 33575900, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xc)) {
                            if (((int)GHIDRA_FIELD(cgs, 33575904, 4) < param_1) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xd)) {
                              if ((int)GHIDRA_FIELD(cgs, 33575908, 4) < param_1) {
                                tmp_i1 = (GHIDRA_FIELD(cgs, 33575848, 4) != 0xe) + 0xe;
                              }
                              else {
                                tmp_i1 = 0xe;
                              }
                            }
                            else {
                              tmp_i1 = 0xd;
                            }
                          }
                          else {
                            tmp_i1 = 0xc;
                          }
                        }
                        else {
                          tmp_i1 = 0xb;
                        }
                      }
                      else {
                        tmp_i1 = 10;
                      }
                    }
                    else {
                      tmp_i1 = 9;
                    }
                  }
                  else {
                    tmp_i1 = 8;
                  }
                }
                else {
                  tmp_i1 = 7;
                }
              }
              else {
                tmp_i1 = 6;
              }
            }
            else {
              tmp_i1 = 5;
            }
          }
          else {
            tmp_i1 = 4;
          }
        }
        else {
          tmp_i1 = 3;
        }
      }
      else {
        tmp_i1 = 2;
      }
    }
    else {
      tmp_i1 = 1;
    }
  }
  else {
    tmp_i1 = 0;
  }
  if (tmp_i1 != GHIDRA_FIELD(cgs, 33575848, 4)) {
    return tmp_i1;
  }
  CG_Printf("^3Warning: no valid command map layer for z\n");
  return 0;
}

void CG_TransformAutomapEntity(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  int *tmp_pi7;
  int tmp_i8;
  
  tmp_f6 = g_unk_010abd68;
  tmp_f5 = g_unk_010abd64;
  tmp_f4 = g_unk_010abd58;
  tmp_f3 = g_unk_010abd54;
  tmp_u2 = GHIDRA_FIELD(cg_automapZoom, 8, 4);
  tmp_i1 = mapEntityCount;
  if (0 < mapEntityCount) {
    tmp_i8 = 0;
    tmp_pi7 = &mapEntities;
    do {
      tmp_i8 = tmp_i8 + 1;
      tmp_pi7[8] = (int)(((float)*tmp_pi7 - tmp_f3) * tmp_f5 * 100.0 * (float)tmp_u2);
      tmp_pi7[9] = (int)(((float)tmp_pi7[1] - tmp_f4) * tmp_f6 * 100.0 * (float)tmp_u2);
      tmp_pi7 = tmp_pi7 + 0xb;
    } while (tmp_i8 != tmp_i1);
  }
  return;
}

bool CG_DisguiseMapCheck(int param_1)
{
  uint tmp_u1;
  long double tmp_l2;
  
  tmp_u1 = *(uint *)(param_1 + 0x10);
  if ((tmp_u1 < 0x40) && (*(int *)(cgs + tmp_u1 * 0x1a4 + 0x940c) != 0)) {
    if ((cg_entities[tmp_u1 * 0xaf8 + 0xe4] & 0x80) != 0) {
      tmp_l2 = (long double)VectorDistance(g_unk_01047b00 + 0x40,tmp_u1 * 0xaf8 + 0x31345d4);
      return (long double)512.0 <= tmp_l2;
    }
  }
  return false;
}

void CG_DrawMapEntity(int param_1,float param_2,float param_3,float param_4,float param_5,
                     byte param_6,int *param_7,int param_8,int param_9,int param_10)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  uint tmp_u8;
  int tmp_i9;
  int *tmp_pi10;
  byte tmp_b11;
  int tmp_i12;
  uint8_t *tmp_pu13;
  uint32_t tmp_u14;
  int tmp_i15;
  long double tmp_l16;
  double tmp_d17;
  uint *local_64;
  uint8_t *local_60;
  float local_58;
  float local_54;
  float local_4c;
  float local_48;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  
  local_3c = 0x3f800000;
  local_38 = 0x3f800000;
  tmp_b11 = *(byte *)(param_1 + 0x14);
  local_34 = 0x3f800000;
  local_30 = 0x3f800000;
  if (9 < tmp_b11) {
    return;
  }
  tmp_u8 = 1 << (tmp_b11 & 0x1f);
  if ((tmp_u8 & 0x3b8) == 0) {
    if ((tmp_u8 & 0x40) != 0) {
      if (param_7 != (int *)0x0) {
        tmp_f3 = *(float *)(param_1 + 0x20);
        if (*param_7 == 0) {
          if (tmp_f3 < (float)param_7[2]) {
            return;
          }
          if ((float)param_7[4] < tmp_f3) {
            return;
          }
          if (*(float *)(param_1 + 0x24) < (float)param_7[3]) {
            return;
          }
          if ((float)param_7[5] < *(float *)(param_1 + 0x24)) {
            return;
          }
        }
        else {
          tmp_f4 = ((float)param_7[4] - (float)param_7[2]) * 0.5;
          tmp_f3 = tmp_f3 - ((float)param_7[2] + tmp_f4);
          tmp_f1 = *(float *)(param_1 + 0x24) -
                  (((float)param_7[5] - (float)param_7[3]) * 0.5 + (float)param_7[3]);
          if (GHIDRA_FIELD(cg_drawCompass, 12, 4) != 2) {
            tmp_f4 = ((float)param_7[4] - (float)param_7[2]) * 0.8;
          }
          if (tmp_f4 * tmp_f4 < tmp_f1 * tmp_f1 + tmp_f3 * tmp_f3) {
            return;
          }
        }
      }
      if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
        tmp_i12 = *(int *)(param_1 + 8);
        if (((int)GHIDRA_FIELD(cgs, 33575852, 4) < tmp_i12) && (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
          if (((int)GHIDRA_FIELD(cgs, 33575856, 4) < tmp_i12) && (1 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
            if (((int)GHIDRA_FIELD(cgs, 33575860, 4) < tmp_i12) && (2 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
              if (((int)GHIDRA_FIELD(cgs, 33575864, 4) < tmp_i12) && (3 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                if (((int)GHIDRA_FIELD(cgs, 33575868, 4) < tmp_i12) && (4 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                  if (((int)GHIDRA_FIELD(cgs, 33575872, 4) < tmp_i12) && (5 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                    if (((int)GHIDRA_FIELD(cgs, 33575876, 4) < tmp_i12) && (6 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                      if (((int)GHIDRA_FIELD(cgs, 33575880, 4) < tmp_i12) && (7 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                        if (((int)GHIDRA_FIELD(cgs, 33575884, 4) < tmp_i12) && (8 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                          if (((int)GHIDRA_FIELD(cgs, 33575888, 4) < tmp_i12) && (9 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                            if (((int)GHIDRA_FIELD(cgs, 33575892, 4) < tmp_i12) && (10 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                              if (((int)GHIDRA_FIELD(cgs, 33575896, 4) < tmp_i12) && (0xb < (int)GHIDRA_FIELD(cgs, 33575848, 4)))
                              {
                                if (((int)GHIDRA_FIELD(cgs, 33575900, 4) < tmp_i12) &&
                                   (0xc < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                                  if (((int)GHIDRA_FIELD(cgs, 33575904, 4) < tmp_i12) &&
                                     (0xd < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                                    if ((tmp_i12 <= (int)GHIDRA_FIELD(cgs, 33575908, 4)) ||
                                       (tmp_i12 = 0xf, (int)GHIDRA_FIELD(cgs, 33575848, 4) < 0xf)) {
                                      tmp_i12 = 0xe;
                                    }
                                  }
                                  else {
                                    tmp_i12 = 0xd;
                                  }
                                }
                                else {
                                  tmp_i12 = 0xc;
                                }
                              }
                              else {
                                tmp_i12 = 0xb;
                              }
                            }
                            else {
                              tmp_i12 = 10;
                            }
                          }
                          else {
                            tmp_i12 = 9;
                          }
                        }
                        else {
                          tmp_i12 = 8;
                        }
                      }
                      else {
                        tmp_i12 = 7;
                      }
                    }
                    else {
                      tmp_i12 = 6;
                    }
                  }
                  else {
                    tmp_i12 = 5;
                  }
                }
                else {
                  tmp_i12 = 4;
                }
              }
              else {
                tmp_i12 = 3;
              }
            }
            else {
              tmp_i12 = 2;
            }
          }
          else {
            tmp_i12 = 1;
          }
          if (GHIDRA_FIELD(cgs, 33575848, 4) == tmp_i12) {
            CG_Printf("^3Warning: no valid command map layer for z\n");
            tmp_i12 = 0;
          }
        }
        else {
          tmp_i12 = 0;
        }
        if (GHIDRA_FIELD(cgs, 33685900, 4) != tmp_i12) {
          return;
        }
      }
      local_30 = 0x3f800000;
      tmp_u14 = GHIDRA_FIELD(cgs, 68464, 4);
      if (*(int *)(param_1 + 0x10) == 1) {
        tmp_u14 = GHIDRA_FIELD(cgs, 68460, 4);
      }
      if (param_7 == (int *)0x0) {
        tmp_f3 = *(float *)(param_1 + 0x18);
        tmp_f4 = *(float *)(param_1 + 0x1c);
        tmp_f1 = (float)GHIDRA_FIELD(cgs, 33575916, 4);
      }
      else {
        tmp_f3 = *(float *)(param_1 + 0x20) - (float)param_7[2];
        tmp_f4 = *(float *)(param_1 + 0x24) - (float)param_7[3];
        tmp_f1 = (float)param_7[1] / 5.159;
      }
      tmp_f1 = tmp_f1 * 12.0;
      local_64 = (uint *)(tmp_f3 + param_2);
      trap_R_SetColor(&local_3c);
      CG_DrawPic((float)local_64 - tmp_f1 * 0.5,(param_3 + tmp_f4) - tmp_f1 * 0.5,tmp_f1,tmp_f1,tmp_u14);
      trap_R_SetColor(0);
      return;
    }
    if ((tmp_u8 & 7) == 0) {
      return;
    }
    tmp_i12 = *(int *)(param_1 + 0x10);
    if (*(int *)(cgs + tmp_i12 * 0x1a4 + 0x940c) == 0) {
      return;
    }
    if (((*(byte *)(param_9 + 0x39) & 0x40) != 0) && (tmp_i12 == g_unk_01047ac4)) {
      return;
    }
    if (*(int *)(cgs + tmp_i12 * 0x1a4 + 0x9494) == 1) {
      param_6 = param_6 & 1;
    }
    else {
      if (*(int *)(cgs + tmp_i12 * 0x1a4 + 0x9494) != 2) {
        return;
      }
      param_6 = param_6 & 2;
    }
    if (param_6 != 0) {
      return;
    }
    tmp_i15 = tmp_i12 * 0xaf8;
    if ((tmp_b11 == 2) && ((cg_entities[tmp_i15 + 0xe4] & 0x80) == 0)) {
      return;
    }
    tmp_i9 = CG_PlayerClassForClientinfo(tmp_i12 * 0x1a4 + 0x10f926c,cg_entities + tmp_i15);
    if ((tmp_i15 >> 3) * -0xbab6561 - g_unk_01047ac4 == 0) {
      if (param_7 == (int *)0x0) {
        *(float *)(param_1 + 0x18) = (g_unk_0109143c - g_unk_010abd54) * g_unk_010abd64 * param_4;
        *(float *)(param_1 + 0x1c) = (g_unk_01091440 - g_unk_010abd58) * g_unk_010abd68 * param_5;
      }
      else {
        *(float *)(param_1 + 0x20) =
             (g_unk_0109143c - g_unk_010abd54) * g_unk_010abd64 * param_4 * (float)param_7[1];
        *(float *)(param_1 + 0x24) =
             (g_unk_01091440 - g_unk_010abd58) * g_unk_010abd68 * param_5 * (float)param_7[1];
      }
      *(int *)(param_1 + 0xc) = (int)ROUND(g_unk_010907b0);
    }
    else if ((*(int *)(cgs + tmp_i12 * 0x1a4 + 0x9494) == *(int *)(param_9 + 0x158)) ||
            ((((tmp_u8 = *(uint *)(param_1 + 0x10), tmp_u8 < 0x40 &&
               (*(int *)(cgs + tmp_u8 * 0x1a4 + 0x940c) != 0)) &&
              ((cg_entities[tmp_u8 * 0xaf8 + 0xe4] & 0x80) != 0)) &&
             (tmp_l16 = (long double)VectorDistance(g_unk_01047b00 + 0x40,tmp_u8 * 0xaf8 + 0x31345d4),
             (long double)512.0 <= tmp_l16)))) {
      if (param_7 == (int *)0x0) {
        *(float *)(param_1 + 0x18) =
             (*(float *)(cg_entities + tmp_i12 * 0xaf8 + 0x794) - g_unk_010abd54) * g_unk_010abd64 *
             param_4;
        *(float *)(param_1 + 0x1c) =
             (*(float *)(cg_entities + tmp_i12 * 0xaf8 + 0x798) - g_unk_010abd58) * g_unk_010abd68 *
             param_5;
      }
      else {
        *(float *)(param_1 + 0x20) =
             (*(float *)(cg_entities + tmp_i12 * 0xaf8 + 0x794) - g_unk_010abd54) * g_unk_010abd64 *
             param_4 * (float)param_7[1];
        *(float *)(param_1 + 0x24) =
             (*(float *)(cg_entities + tmp_i12 * 0xaf8 + 0x798) - g_unk_010abd58) * g_unk_010abd68 *
             param_5 * (float)param_7[1];
      }
      *(int *)(param_1 + 0xc) = (int)ROUND(*(float *)(cg_entities + tmp_i12 * 0xaf8 + 0x7a4));
    }
    else if (*(char *)(param_1 + 0x14) == '\x01') {
      return;
    }
    if (param_7 == (int *)0x0) {
      if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) goto LAB_0003d572;
LAB_0003d702:
      local_4c = param_2 + *(float *)(param_1 + 0x18);
      tmp_f3 = (float)param_10;
      local_58 = local_4c - tmp_f3;
      local_48 = param_3 + *(float *)(param_1 + 0x1c);
      local_54 = local_48 - tmp_f3;
      local_48 = local_48 + tmp_f3;
      local_60 = (uint8_t *)(float)(param_10 * 2);
    }
    else {
      tmp_f3 = *(float *)(param_1 + 0x20);
      tmp_f4 = (float)param_7[2];
      if (*param_7 == 0) {
        if (tmp_f3 < tmp_f4) {
          return;
        }
        if ((float)param_7[4] < tmp_f3) {
          return;
        }
        tmp_f1 = *(float *)(param_1 + 0x24);
        tmp_f2 = (float)param_7[3];
        if (tmp_f1 < tmp_f2) {
          return;
        }
        if ((float)param_7[5] < tmp_f1) {
          return;
        }
      }
      else {
        tmp_f7 = ((float)param_7[4] - tmp_f4) * 0.5;
        tmp_f6 = tmp_f3 - (tmp_f4 + tmp_f7);
        tmp_f1 = *(float *)(param_1 + 0x24);
        tmp_f2 = (float)param_7[3];
        tmp_f5 = tmp_f1 - (((float)param_7[5] - tmp_f2) * 0.5 + tmp_f2);
        if (tmp_f7 * tmp_f7 < tmp_f5 * tmp_f5 + tmp_f6 * tmp_f6) {
          return;
        }
      }
      if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
LAB_0003d572:
        tmp_i15 = *(int *)(param_1 + 8);
        if (((int)GHIDRA_FIELD(cgs, 33575848, 4) < 1) || (tmp_i15 <= (int)GHIDRA_FIELD(cgs, 33575852, 4))) {
          tmp_i15 = 0;
        }
        else {
          if (((int)GHIDRA_FIELD(cgs, 33575856, 4) < tmp_i15) && (1 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
            if (((int)GHIDRA_FIELD(cgs, 33575860, 4) < tmp_i15) && (2 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
              if (((int)GHIDRA_FIELD(cgs, 33575864, 4) < tmp_i15) && (3 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                if (((int)GHIDRA_FIELD(cgs, 33575868, 4) < tmp_i15) && (4 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                  if (((int)GHIDRA_FIELD(cgs, 33575872, 4) < tmp_i15) && (5 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                    if (((int)GHIDRA_FIELD(cgs, 33575876, 4) < tmp_i15) && (6 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                      if (((int)GHIDRA_FIELD(cgs, 33575880, 4) < tmp_i15) && (7 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                        if (((int)GHIDRA_FIELD(cgs, 33575884, 4) < tmp_i15) && (8 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                          if (((int)GHIDRA_FIELD(cgs, 33575888, 4) < tmp_i15) && (9 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                            if (((int)GHIDRA_FIELD(cgs, 33575892, 4) < tmp_i15) && (10 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                              if (((int)GHIDRA_FIELD(cgs, 33575896, 4) < tmp_i15) && (0xb < (int)GHIDRA_FIELD(cgs, 33575848, 4)))
                              {
                                if (((int)GHIDRA_FIELD(cgs, 33575900, 4) < tmp_i15) &&
                                   (0xc < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                                  if (((int)GHIDRA_FIELD(cgs, 33575904, 4) < tmp_i15) &&
                                     (0xd < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                                    if ((tmp_i15 <= (int)GHIDRA_FIELD(cgs, 33575908, 4)) ||
                                       (tmp_i15 = 0xf, (int)GHIDRA_FIELD(cgs, 33575848, 4) < 0xf)) {
                                      tmp_i15 = 0xe;
                                    }
                                  }
                                  else {
                                    tmp_i15 = 0xd;
                                  }
                                }
                                else {
                                  tmp_i15 = 0xc;
                                }
                              }
                              else {
                                tmp_i15 = 0xb;
                              }
                            }
                            else {
                              tmp_i15 = 10;
                            }
                          }
                          else {
                            tmp_i15 = 9;
                          }
                        }
                        else {
                          tmp_i15 = 8;
                        }
                      }
                      else {
                        tmp_i15 = 7;
                      }
                    }
                    else {
                      tmp_i15 = 6;
                    }
                  }
                  else {
                    tmp_i15 = 5;
                  }
                }
                else {
                  tmp_i15 = 4;
                }
              }
              else {
                tmp_i15 = 3;
              }
            }
            else {
              tmp_i15 = 2;
            }
          }
          else {
            tmp_i15 = 1;
          }
          if (GHIDRA_FIELD(cgs, 33575848, 4) == tmp_i15) {
            CG_Printf("^3Warning: no valid command map layer for z\n");
            tmp_i15 = 0;
          }
        }
        if (GHIDRA_FIELD(cgs, 33685900, 4) != tmp_i15) {
          return;
        }
        if (param_7 == (int *)0x0) goto LAB_0003d702;
        tmp_f3 = *(float *)(param_1 + 0x20);
        tmp_f4 = (float)param_7[2];
        tmp_f1 = *(float *)(param_1 + 0x24);
        tmp_f2 = (float)param_7[3];
      }
      local_54 = ((float)param_7[1] / 5.159) * (float)param_10;
      local_58 = ((tmp_f3 - tmp_f4) + param_2) - local_54;
      local_54 = ((tmp_f1 - tmp_f2) + param_3) - local_54;
      local_60 = (uint8_t *)(((float)param_7[1] / 5.159) * (float)(param_10 * 2));
      local_4c = 0.0;
      local_48 = 0.0;
    }
    if (*(char *)(param_1 + 0x14) == '\x01') {
      if (GHIDRA_FIELD(cgs, 27388, 4) != 8) {
        local_2c = 0x3f800000;
        local_28 = 0x3f800000;
        local_24 = 0x3f800000;
        local_20 = 1.0;
        if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) == 1) {
          tmp_pu13 = cg_redlimbotime;
        }
        else {
          if (*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) != 2) {
            tmp_f3 = 0.0;
            goto LAB_0003d7b1;
          }
          tmp_pu13 = cg_bluelimbotime;
        }
        tmp_i12 = *(int *)(tmp_pu13 + 0xc);
        tmp_f3 = (float)(tmp_i12 - g_unk_010906e0 % tmp_i12) / (float)tmp_i12;
LAB_0003d7b1:
        tmp_f4 = SQRT(tmp_f3);
        if (NAN(tmp_f4)) {
          tmp_d17 = sqrt((double)tmp_f3);
          tmp_f4 = (float)tmp_d17;
        }
        tmp_d17 = sin((double)((tmp_f4 * 25.0 + tmp_f4 * 25.0) * 3.1415927));
        local_20 = ((float)tmp_d17 + 1.0) * 0.5 * 0.5 + 0.5;
        trap_R_SetColor(&local_2c);
        CG_DrawPic(local_58 + 3.0,local_54 + 3.0,(float)local_60 - 3.0,(float)local_60 - 3.0,
                   GHIDRA_FIELD(cgs, 69804, 4));
        trap_R_SetColor(0);
        return;
      }
      tmp_i15 = *(int *)(param_1 + 0x10);
LAB_0003d388:
      tmp_i15 = CG_IsOnSameFireteam(g_unk_01047ac4,tmp_i15);
      if (tmp_i15 == 0) {
        if (*(int *)(cgs + tmp_i12 * 0x1a4 + 0x9494) == *(int *)(param_9 + 0x158)) {
          if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
            return;
          }
          if (*(int *)(cgs + tmp_i12 * 0x1a4 + 0x94c4) == 0) {
            if (*(int *)(cg_entities + tmp_i12 * 0xaf8 + 0x990) <= g_unk_010906e0) goto LAB_0003c51f;
          }
          else {
            trap_R_SetColor(colorRed);
            CG_DrawPic(local_58,local_54,local_60,local_60,GHIDRA_FIELD(cgs, 69716, 4));
            trap_R_SetColor(0);
            if (*(int *)(cg_entities + tmp_i12 * 0xaf8 + 0x990) <= g_unk_010906e0) goto LAB_0003c512;
          }
LAB_0003d42d:
          CG_DrawPic(local_58 + 12.0,local_54,(float)local_60 * 0.5,(float)local_60 * 0.5,
                     *(uint32_t *)(cg_entities + tmp_i12 * 0xaf8 + 0x98c));
        }
      }
      else {
        if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
          return;
        }
        if (*(int *)(cgs + tmp_i12 * 0x1a4 + 0x94c4) != 0) {
          trap_R_SetColor(colorRed);
        }
        CG_DrawPic(local_58,local_54,local_60,local_60,GHIDRA_FIELD(cgs, 69716, 4));
        trap_R_SetColor(0);
        if (param_7 == (int *)0x0) {
          CG_Text_Paint_Ext(local_4c,local_48,0x3e4ccccd,0x3e4ccccd,&colorWhite,
                            tmp_i12 * 0x1a4 + 0x10f9274,0,0,3,0x110afec);
        }
        if (g_unk_010906e0 < *(int *)(cg_entities + tmp_i12 * 0xaf8 + 0x990)) goto LAB_0003d42d;
      }
    }
    else {
      tmp_i15 = *(int *)(param_1 + 0x10);
      if (g_unk_01047ac4 == tmp_i15) {
        tmp_i15 = g_unk_01047ac4;
        if (GHIDRA_FIELD(cgs, 27388, 4) == 8) goto LAB_0003d388;
        if (*(int *)(cgs + tmp_i12 * 0x1a4 + 0x94c4) == 0) {
          trap_R_SetColor(&colorYellow);
        }
        else {
          trap_R_SetColor(colorRed);
        }
        CG_DrawPic(local_58,local_54,local_60,local_60,GHIDRA_FIELD(cgs, 69716, 4));
        trap_R_SetColor(0);
        if (g_unk_010906e0 < g_unk_01091638) {
          CG_DrawPic(local_58 + 12.0,local_54,(float)local_60 * 0.5,(float)local_60 * 0.5,
                     g_unk_01091634);
        }
      }
      else {
        if ((*(char *)(param_1 + 0x14) != '\x02') || (GHIDRA_FIELD(cgs, 27388, 4) == 8)) goto LAB_0003d388;
        trap_R_SetColor(colorOrange);
        CG_DrawPic(local_58,local_54,local_60,local_60,GHIDRA_FIELD(cgs, 69716, 4));
        trap_R_SetColor(0);
      }
    }
LAB_0003c512:
    if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
      return;
    }
LAB_0003c51f:
    local_30 = 0x3f800000;
    trap_R_SetColor(&local_3c);
    CG_DrawPic(local_58,local_54,local_60,local_60,*(uint32_t *)(tmp_i9 + 0x28));
    CG_DrawRotatedPic(local_58 - 1.0,local_54 - 1.0,(float)local_60 + 2.0,(float)local_60 + 2.0,
                      *(uint32_t *)(tmp_i9 + 0x2c),
                      0.5 - ((float)*(int *)(param_1 + 0xc) - 180.0) / 360.0);
    trap_R_SetColor(0);
    return;
  }
  if ((byte)(tmp_b11 - 7) < 2) {
    local_64 = (uint *)(cgs + *(int *)(param_1 + 0x10) * 0x60 + 0x2023f54);
    tmp_i12 = *(int *)(g_unk_01047b00 + 0x5d8);
    if (tmp_i12 < 1) {
      tmp_i12 = 0;
    }
    else {
      tmp_pi10 = (int *)(g_unk_01047b00 + 0x5e0);
      tmp_i15 = 0;
      do {
        if ((*tmp_pi10 == 0xc) && (*(int *)(param_1 + 0x10) == tmp_pi10[0x41])) {
          tmp_i12 = *(int *)(g_unk_01047b00 + 0x5dc + tmp_i15 * 0x120) * 0xaf8;
          local_60 = cg_entities + tmp_i12;
          if (param_7 == (int *)0x0) {
            *(float *)(param_1 + 0x18) =
                 (*(float *)(cg_entities + tmp_i12 + 0x794) - g_unk_010abd54) * g_unk_010abd64 * param_4;
            *(float *)(param_1 + 0x1c) =
                 (*(float *)(cg_entities + tmp_i12 + 0x798) - g_unk_010abd58) * g_unk_010abd68 * param_5;
            goto LAB_0003ca92;
          }
          param_4 = (*(float *)(cg_entities + tmp_i12 + 0x794) - g_unk_010abd54) * g_unk_010abd64 *
                    param_4 * (float)param_7[1];
          *(float *)(param_1 + 0x20) = param_4;
          *(float *)(param_1 + 0x24) =
               (*(float *)(cg_entities + tmp_i12 + 0x798) - g_unk_010abd58) * g_unk_010abd68 * param_5 *
               (float)param_7[1];
          goto LAB_0003c066;
        }
        tmp_i15 = tmp_i15 + 1;
        tmp_pi10 = tmp_pi10 + 0x48;
      } while (tmp_i15 != tmp_i12);
    }
LAB_0003c04e:
    tmp_i15 = tmp_i12;
    if (param_7 == (int *)0x0) {
      local_60 = (uint8_t *)0x0;
    }
    else {
      local_60 = (uint8_t *)0x0;
      param_4 = *(float *)(param_1 + 0x20);
LAB_0003c066:
      if (*param_7 == 0) {
        if (param_4 < (float)param_7[2]) {
          return;
        }
        if ((float)param_7[4] < param_4) {
          return;
        }
        if (*(float *)(param_1 + 0x24) < (float)param_7[3]) {
          return;
        }
        if ((float)param_7[5] < *(float *)(param_1 + 0x24)) {
          return;
        }
      }
      else {
        tmp_f3 = ((float)param_7[4] - (float)param_7[2]) * 0.5;
        param_4 = param_4 - ((float)param_7[2] + tmp_f3);
        tmp_f4 = *(float *)(param_1 + 0x24) -
                (((float)param_7[5] - (float)param_7[3]) * 0.5 + (float)param_7[3]);
        if (tmp_f3 * tmp_f3 < tmp_f4 * tmp_f4 + param_4 * param_4) {
          return;
        }
      }
    }
    if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) goto LAB_0003caa0;
LAB_0003c6bc:
    tmp_pu13 = (uint8_t *)0x0;
    if (local_64 != (uint *)0x0) goto LAB_0003c6c6;
  }
  else {
    if ((byte)(tmp_b11 - 3) < 3) {
      tmp_i12 = *(int *)(param_1 + 0x10) * 0xaf8;
      local_60 = cg_entities + tmp_i12;
      local_64 = (uint *)(cgs + *(int *)(cg_entities + tmp_i12 + 0xa8) * 0x60 + 0x2023f54);
      if (param_7 != (int *)0x0) {
        param_4 = (*(float *)(cg_entities + tmp_i12 + 0x794) - g_unk_010abd54) * g_unk_010abd64 * param_4
                  * (float)param_7[1];
        *(float *)(param_1 + 0x20) = param_4;
        tmp_i15 = 1;
        *(float *)(param_1 + 0x24) =
             (*(float *)(cg_entities + tmp_i12 + 0x798) - g_unk_010abd58) * g_unk_010abd68 * param_5 *
             (float)param_7[1];
        goto LAB_0003c066;
      }
      *(float *)(param_1 + 0x18) =
           (*(float *)(cg_entities + tmp_i12 + 0x794) - g_unk_010abd54) * g_unk_010abd64 * param_4;
      *(float *)(param_1 + 0x1c) =
           (*(float *)(cg_entities + tmp_i12 + 0x798) - g_unk_010abd58) * g_unk_010abd68 * param_5;
      tmp_i15 = 1;
    }
    else {
      if (tmp_b11 != 9) {
        local_64 = (uint *)0x0;
        tmp_i12 = 1;
        goto LAB_0003c04e;
      }
      tmp_i12 = *(int *)(param_1 + 0x10) * 0x60;
      local_64 = (uint *)(cgs + tmp_i12 + 0x2023f54);
      param_4 = (*(float *)(cgs + tmp_i12 + 0x2023fa8) - g_unk_010abd54) * g_unk_010abd64 * param_4;
      if (param_7 != (int *)0x0) {
        param_4 = param_4 * (float)param_7[1];
        *(float *)(param_1 + 0x20) = param_4;
        local_60 = (uint8_t *)0x0;
        *(float *)(param_1 + 0x24) =
             (*(float *)(cgs + tmp_i12 + 0x2023fac) - g_unk_010abd58) * g_unk_010abd68 * param_5 *
             (float)param_7[1];
        tmp_i15 = 1;
        goto LAB_0003c066;
      }
      *(float *)(param_1 + 0x18) = param_4;
      local_60 = (uint8_t *)0x0;
      *(float *)(param_1 + 0x1c) =
           (*(float *)(cgs + tmp_i12 + 0x2023fac) - g_unk_010abd58) * g_unk_010abd68 * param_5;
      tmp_i15 = 1;
    }
LAB_0003ca92:
    if (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
LAB_0003caa0:
      tmp_i12 = *(int *)(param_1 + 8);
      if (((int)GHIDRA_FIELD(cgs, 33575852, 4) < tmp_i12) && (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
        if (((int)GHIDRA_FIELD(cgs, 33575856, 4) < tmp_i12) && (1 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
          if (((int)GHIDRA_FIELD(cgs, 33575860, 4) < tmp_i12) && (2 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
            if (((int)GHIDRA_FIELD(cgs, 33575864, 4) < tmp_i12) && (3 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
              if (((int)GHIDRA_FIELD(cgs, 33575868, 4) < tmp_i12) && (4 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                if (((int)GHIDRA_FIELD(cgs, 33575872, 4) < tmp_i12) && (5 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                  if (((int)GHIDRA_FIELD(cgs, 33575876, 4) < tmp_i12) && (6 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                    if (((int)GHIDRA_FIELD(cgs, 33575880, 4) < tmp_i12) && (7 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                      if (((int)GHIDRA_FIELD(cgs, 33575884, 4) < tmp_i12) && (8 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                        if (((int)GHIDRA_FIELD(cgs, 33575888, 4) < tmp_i12) && (9 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                          if (((int)GHIDRA_FIELD(cgs, 33575892, 4) < tmp_i12) && (10 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                            if (((int)GHIDRA_FIELD(cgs, 33575896, 4) < tmp_i12) && (0xb < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                              if (((int)GHIDRA_FIELD(cgs, 33575900, 4) < tmp_i12) && (0xc < (int)GHIDRA_FIELD(cgs, 33575848, 4)))
                              {
                                if (((int)GHIDRA_FIELD(cgs, 33575904, 4) < tmp_i12) &&
                                   (0xd < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
                                  if ((tmp_i12 <= (int)GHIDRA_FIELD(cgs, 33575908, 4)) ||
                                     (tmp_i12 = 0xf, (int)GHIDRA_FIELD(cgs, 33575848, 4) < 0xf)) {
                                    tmp_i12 = 0xe;
                                  }
                                }
                                else {
                                  tmp_i12 = 0xd;
                                }
                              }
                              else {
                                tmp_i12 = 0xc;
                              }
                            }
                            else {
                              tmp_i12 = 0xb;
                            }
                          }
                          else {
                            tmp_i12 = 10;
                          }
                        }
                        else {
                          tmp_i12 = 9;
                        }
                      }
                      else {
                        tmp_i12 = 8;
                      }
                    }
                    else {
                      tmp_i12 = 7;
                    }
                  }
                  else {
                    tmp_i12 = 6;
                  }
                }
                else {
                  tmp_i12 = 5;
                }
              }
              else {
                tmp_i12 = 4;
              }
            }
            else {
              tmp_i12 = 3;
            }
          }
          else {
            tmp_i12 = 2;
          }
        }
        else {
          tmp_i12 = 1;
        }
        if (GHIDRA_FIELD(cgs, 33575848, 4) == tmp_i12) {
          CG_Printf("^3Warning: no valid command map layer for z\n");
          tmp_i12 = 0;
        }
      }
      else {
        tmp_i12 = 0;
      }
      if (GHIDRA_FIELD(cgs, 33685900, 4) != tmp_i12) {
        return;
      }
      tmp_b11 = *(byte *)(param_1 + 0x14);
      goto LAB_0003c6bc;
    }
LAB_0003c6c6:
    if (*(int *)(param_1 + 0x28) == 1) {
      tmp_pu13 = (uint8_t *)local_64[2];
    }
    else {
      tmp_pu13 = (uint8_t *)local_64[1];
    }
  }
  if (tmp_b11 == 3) {
    if ((param_6 & 0x20) != 0) {
      return;
    }
    if (*(int *)(param_1 + 0x28) == 1) {
      local_60 = (uint8_t *)GHIDRA_FIELD(cgs, 69720, 4);
    }
    else {
      local_60 = (uint8_t *)GHIDRA_FIELD(cgs, 69724, 4);
    }
  }
  else if (tmp_b11 == 7) {
    if ((param_6 & 0x80) != 0) {
      return;
    }
    local_60 = (uint8_t *)GHIDRA_FIELD(cgs, 69760, 4);
  }
  else if (tmp_b11 == 8) {
    if ((param_6 & 0x80) != 0) {
      return;
    }
    local_60 = (uint8_t *)GHIDRA_FIELD(cgs, 69760, 4);
    trap_R_SetColor(colorRed);
  }
  else if (tmp_b11 == 9) {
    local_60 = (uint8_t *)0x0;
  }
  else {
    if ((tmp_b11 != 5) && ((param_6 & 0x40) != 0)) {
      return;
    }
    if (*(int *)(param_1 + 0x28) == 1) {
      local_60 = *(uint8_t **)(cgs + *(int *)(local_60 + 0x10c) * 8 + 0x11068);
    }
    else {
      local_60 = *(uint8_t **)(cgs + *(int *)(local_60 + 0x10c) * 8 + 0x1106c);
    }
  }
  if (local_64 != (uint *)0x0) {
    tmp_u8 = *local_64;
    if (((tmp_u8 & 0x10) != 0) && ((param_6 & 0x80) != 0)) {
      return;
    }
    if (((tmp_u8 & 0x20) != 0) && ((param_6 & 0x10) != 0)) {
      return;
    }
    if ((tmp_u8 & 0x40) != 0) {
      if (*(char *)(param_1 + 0x14) == '\x05') {
        if (*(int *)(param_1 + 0x28) == 1) {
          local_60 = (uint8_t *)GHIDRA_FIELD(cgs, 69728, 4);
        }
        else {
          local_60 = (uint8_t *)GHIDRA_FIELD(cgs, 69732, 4);
        }
      }
      if ((param_6 & 8) != 0) {
        return;
      }
    }
  }
  if (tmp_pu13 == (uint8_t *)0x0) {
    tmp_pu13 = local_60;
  }
  if (param_7 == (int *)0x0) {
    tmp_f3 = *(float *)(param_1 + 0x18);
    tmp_f4 = *(float *)(param_1 + 0x1c);
  }
  else {
    tmp_f3 = *(float *)(param_1 + 0x20) - (float)param_7[2];
    tmp_f4 = *(float *)(param_1 + 0x24) - (float)param_7[3];
  }
  tmp_f4 = param_3 + tmp_f4;
  tmp_f3 = param_2 + tmp_f3;
  if (param_8 != 0) {
    if ((expanded == 0) &&
       (tmp_i12 = BG_RectContainsPoint
                           ((param_2 + *(float *)(param_1 + 0x18)) - 16.0,
                            (param_3 + *(float *)(param_1 + 0x1c)) - 16.0,0x42000000,0x42000000,
                            (float)g_unk_010261a4,(float)g_unk_010261a8), tmp_i12 != 0)) {
      if ((byte)(*(char *)(param_1 + 0x14) - 7U) < 2) {
        tmp_f1 = 24.0;
        tmp_f2 = 24.0;
      }
      else {
        tmp_f1 = 48.0;
        tmp_f2 = 48.0;
      }
      if (param_7 == (int *)0x0) {
        tmp_f2 = tmp_f2 * (float)GHIDRA_FIELD(cgs, 33575916, 4);
        tmp_f1 = (float)GHIDRA_FIELD(cgs, 33575916, 4);
      }
      else {
        tmp_f2 = ((float)param_7[1] / 5.159) * tmp_f1;
        tmp_f1 = (float)param_7[1] / 5.159;
      }
      CG_DrawPic(tmp_f3 - tmp_f1 * 48.0 * 0.5,tmp_f4 - tmp_f2 * 0.5,tmp_f1 * 48.0,tmp_f2,tmp_pu13);
      if (local_64 == (uint *)0x0) {
        local_64 = (uint *)va("%i",tmp_i15);
      }
      else {
        local_64 = local_64 + 5;
      }
      tmp_i12 = CG_Text_Width_Ext(local_64,0x3e4ccccd,0,0x110afec);
      Q_strncpyz(&cg_highlightText,local_64,0x100);
      expanded = 1;
      g_unk_00f5eb44 = tmp_f4 - 8.0;
      cg_highlightTextRect = tmp_f3 - (float)tmp_i12 * 0.5;
      goto LAB_0003c8b6;
    }
    if (((int)(uint)*(byte *)(param_1 + 0xc) >> ((byte)GHIDRA_FIELD(cgs, 33685904, 4) & 0x1f) & 1U) != 0) {
      tmp_i12 = g_unk_010906e0 % 0x578;
      if (tmp_i12 < 0x2bd) {
        tmp_f1 = (float)(tmp_i12 * 0xc) / 700.0;
      }
      else {
        tmp_f1 = (1.0 - (float)(tmp_i12 + -700) / 700.0) * 12.0;
      }
      tmp_f2 = (float)GHIDRA_FIELD(cgs, 33575916, 4);
      if (param_7 != (int *)0x0) {
        tmp_f2 = (float)param_7[1] / 5.159;
      }
      tmp_f2 = tmp_f2 * (tmp_f1 + 32.0);
      tmp_f1 = tmp_f2;
      if ((byte)(*(char *)(param_1 + 0x14) - 7U) < 2) {
        tmp_f1 = tmp_f2 * 0.5;
      }
      CG_DrawPic(tmp_f3 - tmp_f2 * 0.5,tmp_f4 - tmp_f1 * 0.5,tmp_f2,tmp_f1,tmp_pu13);
      goto LAB_0003c8b6;
    }
  }
  if ((byte)(*(char *)(param_1 + 0x14) - 7U) < 2) {
    tmp_f1 = 16.0;
    tmp_f2 = 16.0;
  }
  else {
    tmp_f1 = 32.0;
    tmp_f2 = 32.0;
  }
  if (param_7 == (int *)0x0) {
    tmp_f2 = (float)GHIDRA_FIELD(cgs, 33575916, 4) * tmp_f2;
    tmp_f1 = (float)GHIDRA_FIELD(cgs, 33575916, 4);
  }
  else {
    tmp_f2 = tmp_f1 * ((float)param_7[1] / 5.159);
    tmp_f1 = (float)param_7[1] / 5.159;
  }
  CG_DrawPic(tmp_f3 - tmp_f1 * 32.0 * 0.5,tmp_f4 - tmp_f2 * 0.5,tmp_f1 * 32.0,tmp_f2,tmp_pu13);
LAB_0003c8b6:
  trap_R_SetColor(0);
  return;
}

uint32_t * CG_ScanForCommandCentreEntity(void)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  int local_30;
  int local_2c;
  
  local_30 = mapEntityCount;
  if (0 < mapEntityCount) {
    tmp_pu5 = &mapEntities;
    tmp_i6 = 0;
    local_2c = 0;
    tmp_f1 = 1e+06;
    do {
      while (GHIDRA_FIELD(cgs, 33575848, 4) != 0) {
        tmp_i4 = tmp_pu5[2];
        if (((int)GHIDRA_FIELD(cgs, 33575852, 4) < tmp_i4) && (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4))) {
          if (((int)GHIDRA_FIELD(cgs, 33575856, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 1)) {
            if (((int)GHIDRA_FIELD(cgs, 33575860, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 2)) {
              if (((int)GHIDRA_FIELD(cgs, 33575864, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 3)) {
                if (((int)GHIDRA_FIELD(cgs, 33575868, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 4)) {
                  if (((int)GHIDRA_FIELD(cgs, 33575872, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 5)) {
                    if (((int)GHIDRA_FIELD(cgs, 33575876, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 6)) {
                      if (((int)GHIDRA_FIELD(cgs, 33575880, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 7)) {
                        if (((int)GHIDRA_FIELD(cgs, 33575884, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 8)) {
                          if (((int)GHIDRA_FIELD(cgs, 33575888, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 9)) {
                            if (((int)GHIDRA_FIELD(cgs, 33575892, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 10)) {
                              if (((int)GHIDRA_FIELD(cgs, 33575896, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xb)) {
                                if (((int)GHIDRA_FIELD(cgs, 33575900, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xc)) {
                                  if (((int)GHIDRA_FIELD(cgs, 33575904, 4) < tmp_i4) && (GHIDRA_FIELD(cgs, 33575848, 4) != 0xd))
                                  {
                                    if ((tmp_i4 <= (int)GHIDRA_FIELD(cgs, 33575908, 4)) ||
                                       (tmp_i4 = 0xf, GHIDRA_FIELD(cgs, 33575848, 4) == 0xe)) {
                                      tmp_i4 = 0xe;
                                    }
                                  }
                                  else {
                                    tmp_i4 = 0xd;
                                  }
                                }
                                else {
                                  tmp_i4 = 0xc;
                                }
                              }
                              else {
                                tmp_i4 = 0xb;
                              }
                            }
                            else {
                              tmp_i4 = 10;
                            }
                          }
                          else {
                            tmp_i4 = 9;
                          }
                        }
                        else {
                          tmp_i4 = 8;
                        }
                      }
                      else {
                        tmp_i4 = 7;
                      }
                    }
                    else {
                      tmp_i4 = 6;
                    }
                  }
                  else {
                    tmp_i4 = 5;
                  }
                }
                else {
                  tmp_i4 = 4;
                }
              }
              else {
                tmp_i4 = 3;
              }
            }
            else {
              tmp_i4 = 2;
            }
          }
          else {
            tmp_i4 = 1;
          }
          if (GHIDRA_FIELD(cgs, 33575848, 4) == tmp_i4) {
            CG_Printf("^3Warning: no valid command map layer for z\n");
            local_30 = mapEntityCount;
            tmp_i4 = 0;
          }
        }
        else {
          tmp_i4 = 0;
        }
        if (GHIDRA_FIELD(cgs, 33685900, 4) == tmp_i4) break;
LAB_00041642:
        tmp_i6 = tmp_i6 + 1;
        tmp_pu5 = tmp_pu5 + 0xb;
        if (local_30 <= tmp_i6) goto LAB_00041698;
      }
      tmp_f2 = ((float)tmp_pu5[6] + 64.0) - (float)g_unk_010261a4;
      tmp_f3 = ((float)tmp_pu5[7] + 23.0) - (float)g_unk_010261a8;
      tmp_f2 = tmp_f3 * tmp_f3 + tmp_f2 * tmp_f2;
      if (tmp_i6 != 0) {
        if (tmp_f2 < tmp_f1) {
          tmp_f1 = tmp_f2;
          local_2c = tmp_i6;
        }
        goto LAB_00041642;
      }
      tmp_i6 = 1;
      tmp_pu5 = tmp_pu5 + 0xb;
      local_2c = 0;
      tmp_f1 = tmp_f2;
    } while (1 < local_30);
LAB_00041698:
    if (tmp_f1 < 64.0) {
      return &mapEntities + local_2c * 0xb;
    }
  }
  return (uint32_t *)0x0;
}

uint32_t CG_CommandCentreLayersClick(void)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t local_20;
  
  if (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4)) {
    tmp_i2 = 0;
    local_20 = 0x157;
    do {
      tmp_i1 = BG_RectContainsPoint
                        (0x43c00000,(float)local_20,0x42000000,0x42000000,(float)g_unk_010261a4,
                         (float)g_unk_010261a8);
      if (tmp_i1 != 0) {
        GHIDRA_FIELD(cgs, 33685900, 4) = tmp_i2;
        return 1;
      }
      tmp_i2 = tmp_i2 + 1;
      local_20 = local_20 + -0x22;
    } while (tmp_i2 < (int)GHIDRA_FIELD(cgs, 33575848, 4));
  }
  return 0;
}

uint32_t CG_CommandCentreSpawnPointClick(void)
{
  uint32_t tmp_u1;
  
  if ((cgs[0x20201cc] & 4) == 0) {
    tmp_u1 = CG_CommandCentreSpawnPointClick_part_3();
    return tmp_u1;
  }
  return 0;
}

void CG_CommandCentreClick(int param_1)
{
  if ((param_1 == 0xb2) && ((cgs[0x20201cc] & 4) == 0)) {
    CG_CommandCentreSpawnPointClick_part_3();
    return;
  }
  return;
}

void CG_CommandMap_SetHighlightText(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  Q_strncpyz(&cg_highlightText,param_1,0x100);
  expanded = 1;
  cg_highlightTextRect = param_2;
  g_unk_00f5eb44 = param_3;
  return;
}

void CG_CommandMap_DrawHighlightText(void)
{
  CG_Text_Paint_Ext(cg_highlightTextRect,g_unk_00f5eb44,0x3e800000,0x3e800000,&colorWhite,
                    &cg_highlightText,0,0,3,0x110afec);
  cg_highlightText = 0;
  return;
}

void CG_ToggleAutomap_f(void)
{
  GHIDRA_FIELD(cgs, 33575980, 4) = (uint)(GHIDRA_FIELD(cgs, 33575980, 4) == 0);
  return;
}

void CG_ResetMaxSpeed_f(void)
{
  resetmaxspeed = 1;
  return;
}

void CG_QuickMessage_f(void)
{
  CG_EventHandling(0,0);
  if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) == 0) {
    trap_UI_Popup(8);
    return;
  }
  trap_UI_Popup(9);
  return;
}

void CG_dumpStats_f(void)
{
  if ((int)GHIDRA_FIELD(cgs, 33576016, 4) < g_unk_010906e0) {
    GHIDRA_FIELD(cgs, 33576016, 4) = g_unk_010906e0 + 2000;
    trap_SendClientCommand("weaponstats");
  }
  return;
}

void CG_ForceTapOut_f(void)
{
  trap_SendClientCommand("forcetapout");
  return;
}

void CG_currentTime_f(void)
{
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  int local_20;
  int local_1c;
  uint32_t uStack_8;
  
  uStack_8 = 0x41cf6;
  trap_RealTime(&local_30);
  CG_Printf("[cgnotify]Current time: ^3%02d:%02d:%02d (%02d %s %d)\n",local_28,local_2c,local_30,
            local_24,*(uint32_t *)(aMonths + local_20 * 4),local_1c + 0x76c);
  return;
}

void CG_Viewpos_f(void)
{
  CG_Printf("(%i %i %i) : %i\n",(int)ROUND(g_unk_010918c0),(int)ROUND(g_unk_010918c4),
            (int)ROUND(g_unk_010918c8),(int)ROUND(g_unk_01091a58));
  return;
}

void CG_autoRecord_f(void)
{
  uint32_t tmp_u1;
  
  tmp_u1 = CG_generateFilename();
  tmp_u1 = va("record %s\n",tmp_u1);
  trap_SendConsoleCommand(tmp_u1);
  return;
}

void CG_SayPlayerClass_f(void)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  
  if ((*(byte *)(g_unk_01047b00 + 0x39) & 0x40) == 0) {
    tmp_u1 = *(uint32_t *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94b8);
  }
  else {
    tmp_u1 = *(uint32_t *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94bc);
  }
  switch(tmp_u1) {
  case 0:
    tmp_pc2 = "IamSoldier";
    break;
  case 1:
    tmp_pc2 = "IamMedic";
    break;
  case 2:
    tmp_pc2 = "IamEngineer";
    break;
  case 3:
    tmp_pc2 = "IamFieldOps";
    break;
  case 4:
    tmp_pc2 = "IamCovertOps";
    break;
  default:
    goto switchD_00041ea3_default;
  }
  if ((*(int *)(g_unk_01047b00 + 0x30) != 5) &&
     ((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 0 ||
      (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3)))) {
    CG_Printf("Can\'t say class when spectator.\n");
    return;
  }
  tmp_u1 = va("cmd vsay_team %s\n",tmp_pc2);
  trap_SendConsoleCommand(tmp_u1);
switchD_00041ea3_default:
  return;
}

void CG_keyOn_f(void)
{
  if (g_unk_01047aec != 0) {
    if (0 < (int)GHIDRA_FIELD(demo_infoWindow, 12, 4)) {
      CG_ShowHelp_On(&g_unk_010afbc8);
    }
    CG_EventHandling(4,1);
    return;
  }
  CG_Printf("[cgnotify]^3*** NOT PLAYING A DEMO!!\n");
  return;
}

void CG_ResetTimer_f(void)
{
  uint32_t tmp_u1;
  
  tmp_u1 = va("%d",(int)ROUND((float)GHIDRA_FIELD(cgs, 27396, 4) * 60.0 * 1000.0 -
                             (float)(g_unk_010906e0 - GHIDRA_FIELD(cgs, 28480, 4))) / 1000);
  trap_Cvar_Set("cg_spawnTimer_set",tmp_u1);
  return;
}

void CG_TimerSet_f(void)
{
  float tmp_f1;
  uint tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  long tmp_l5;
  uint32_t tmp_u6;
  char local_2c [4];
  uint32_t local_28 [7];
  
  local_2c[0] = '\0';
  local_2c[1] = '\0';
  local_2c[2] = '\0';
  local_2c[3] = '\0';
  tmp_u2 = 0;
  do {
    tmp_u3 = tmp_u2;
    *(uint32_t *)((int)local_28 + tmp_u3) = 0;
    *(uint32_t *)((int)local_28 + tmp_u3 + 4) = 0;
    tmp_u2 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0x18);
  *(uint32_t *)((int)local_28 + tmp_u3 + 8) = 0;
  tmp_i4 = trap_Argc();
  if (tmp_i4 == 1) {
    trap_Cvar_Set("cg_spawnTimer_set","-1");
    return;
  }
  tmp_i4 = trap_Argc();
  if (tmp_i4 != 2) {
    CG_Printf("^9usage: ^gtimerSet [seconds]\n");
    return;
  }
  trap_Argv(1,local_2c,0x20);
  tmp_l5 = strtol(local_2c,(char **)0x0,10);
  if (0x3b < tmp_l5 - 1U) {
    CG_Printf("Argument must be a number between 1 and 60.\n");
    return;
  }
  tmp_f1 = (float)GHIDRA_FIELD(cgs, 27396, 4) * 60.0;
  tmp_i4 = g_unk_010906e0 - GHIDRA_FIELD(cgs, 28480, 4);
  trap_Cvar_Set("cg_spawnTimer_period",local_2c);
  tmp_u6 = va("%d",(int)ROUND(tmp_f1 * 1000.0 - (float)tmp_i4) / 1000);
  trap_Cvar_Set("cg_spawnTimer_set",tmp_u6);
  return;
}

void CG_SetWeaponCrosshair_f(void)
{
  long tmp_l1;
  char local_4c [68];
  
  trap_Argv(1,local_4c,0x40);
  tmp_l1 = strtol(local_4c,(char **)0x0,10);
  g_unk_010ab2f0 = tmp_l1 + 1;
  return;
}

void CG_CPM_f(void)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  
  tmp_u1 = GHIDRA_FIELD(cgs, 67984, 4);
  tmp_u2 = CG_Argv(1);
  CG_AddPMItem(4,tmp_u2,tmp_u1,0);
  return;
}

void CG_UndoSpeaker_f(void)
{
  if (g_unk_010b4554 != 0) {
    CG_UndoEditSpeaker();
  }
  return;
}

void CG_ModifySpeaker_f(void)
{
  if (g_unk_010b4554 != 0) {
    CG_ModifyEditSpeaker();
  }
  return;
}

void CG_AutomapZoomOut_f(void)
{
  if (GHIDRA_FIELD(cgs, 33575980, 4) == 0) {
    CG_AdjustAutomapZoom(0);
  }
  return;
}

void CG_AutomapZoomIn_f(void)
{
  if (GHIDRA_FIELD(cgs, 33575980, 4) == 0) {
    CG_AdjustAutomapZoom(1);
  }
  return;
}

void CG_SelectBuddy_f(void)
{
  char *__nptr;
  uint tmp_u1;
  int tmp_i2;
  int tmp_i3;
  
  __nptr = (char *)CG_Argv(1);
  tmp_u1 = strtol(__nptr,(char **)0x0,10);
  if (tmp_u1 == 0xffffffff) {
    tmp_i2 = CG_IsOnFireteam(g_unk_01047ac4);
    if (tmp_i2 != 0) {
      tmp_i2 = 0;
      while (tmp_i3 = CG_SortedFireTeamPlayerForPosition(tmp_i2), tmp_i3 != 0) {
        tmp_i2 = tmp_i2 + 1;
        *(uint32_t *)(tmp_i3 + 0x170) = 0;
        if (tmp_i2 == 6) {
          return;
        }
      }
    }
  }
  else if (tmp_u1 < 0x80000000) {
    if ((((int)tmp_u1 < 8) && (tmp_i2 = CG_IsOnFireteam(g_unk_01047ac4), tmp_i2 != 0)) &&
       (tmp_i2 = CG_SortedFireTeamPlayerForPosition(tmp_u1), tmp_i2 != 0)) {
      *(uint *)(tmp_i2 + 0x170) = *(uint *)(tmp_i2 + 0x170) ^ 1;
      return;
    }
  }
  else if ((tmp_u1 == 0xfffffffe) && (tmp_i2 = CG_IsOnFireteam(g_unk_01047ac4), tmp_i2 != 0)) {
    tmp_i2 = 0;
    do {
      tmp_i3 = CG_SortedFireTeamPlayerForPosition(tmp_i2);
      if (tmp_i3 == 0) {
        return;
      }
      tmp_i2 = tmp_i2 + 1;
      *(uint32_t *)(tmp_i3 + 0x170) = 1;
    } while (tmp_i2 != 6);
  }
  return;
}

void CG_FTSayPlayerClass_f(void)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  
  if ((*(byte *)(g_unk_01047b00 + 0x39) & 0x40) == 0) {
    tmp_u1 = *(uint32_t *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94b8);
  }
  else {
    tmp_u1 = *(uint32_t *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94bc);
  }
  switch(tmp_u1) {
  case 0:
    tmp_pc2 = "IamSoldier";
    break;
  case 1:
    tmp_pc2 = "IamMedic";
    break;
  case 2:
    tmp_pc2 = "IamEngineer";
    break;
  case 3:
    tmp_pc2 = "IamFieldOps";
    break;
  case 4:
    tmp_pc2 = "IamCovertOps";
    break;
  default:
    goto switchD_0004258e_default;
  }
  if ((*(int *)(g_unk_01047b00 + 0x30) != 5) &&
     ((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 0 ||
      (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3)))) {
    CG_Printf("Can\'t say class when spectator.\n");
    return;
  }
  tmp_u1 = CG_BuildSelectedFirteamString();
  tmp_u1 = va("cmd vsay_buddy -1 %s %s\n",tmp_u1,tmp_pc2);
  trap_SendConsoleCommand(tmp_u1);
switchD_0004258e_default:
  return;
}

void CG_MessageSend_f(void)
{
  long tmp_l1;
  uint32_t tmp_u2;
  char local_11c [268];
  
  trap_Cvar_VariableStringBuffer("cg_messageType",local_11c,0x100);
  tmp_l1 = strtol(local_11c,(char **)0x0,10);
  trap_Cvar_VariableStringBuffer("cg_messageText",local_11c,0x100);
  trap_Cvar_Set("cg_messageText",&g_unk_0011d841);
  trap_Cvar_Set("cg_messageType",&g_unk_0011d841);
  if (local_11c[0] != '\0') {
    if (tmp_l1 == 2) {
      tmp_u2 = va("say_team \"%s\"\n",local_11c);
      trap_SendConsoleCommand(tmp_u2);
    }
    else if (tmp_l1 == 3) {
      tmp_u2 = va("say_buddy \"%s\"\n",local_11c);
      trap_SendConsoleCommand(tmp_u2);
    }
    else if (tmp_l1 == 4) {
      tmp_u2 = va("ma \"%s\"\n",local_11c);
      trap_SendConsoleCommand(tmp_u2);
    }
    else {
      tmp_u2 = va("say \"%s\"\n",local_11c);
      trap_SendConsoleCommand(tmp_u2);
    }
  }
  return;
}

void CG_StatsUp_f(void)
{
  float tmp_f1;
  
  if (GHIDRA_FIELD(cgs, 33585516, 4) != 2) {
    return;
  }
  GHIDRA_FIELD(cgs, 33585516, 4) = 1;
  if (g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33585512, 4)) {
    tmp_f1 = ((float)(g_unk_010906e0 * 2) + 200.0) - (float)(int)GHIDRA_FIELD(cgs, 33585512, 4);
  }
  else {
    tmp_f1 = (float)g_unk_010906e0 + 200.0;
  }
  GHIDRA_FIELD(cgs, 33585512, 4) = (int)ROUND(tmp_f1);
  return;
}

void CG_topshotsUp_f(void)
{
  float tmp_f1;
  
  if (GHIDRA_FIELD(cgs, 33598844, 4) != 2) {
    return;
  }
  GHIDRA_FIELD(cgs, 33598844, 4) = 1;
  if (g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33598840, 4)) {
    tmp_f1 = ((float)(g_unk_010906e0 * 2) + 200.0) - (float)(int)GHIDRA_FIELD(cgs, 33598840, 4);
  }
  else {
    tmp_f1 = (float)g_unk_010906e0 + 200.0;
  }
  GHIDRA_FIELD(cgs, 33598840, 4) = (int)ROUND(tmp_f1);
  return;
}

void CG_ScoresUp_f(void)
{
  if (g_unk_010928a4 != 0) {
    g_unk_010928a4 = 0;
    g_unk_010928ac = g_unk_010906e0;
  }
  return;
}

void CG_AutomapExpandDown_f(void)
{
  if (GHIDRA_FIELD(cgs, 33575972, 4) == 0) {
    GHIDRA_FIELD(cgs, 33575972, 4) = 1;
    if ((float)(g_unk_010906e0 - GHIDRA_FIELD(cgs, 33575976, 4)) < 250.0) {
      GHIDRA_FIELD(cgs, 33575976, 4) =
           (int)ROUND((float)g_unk_010906e0 - (250.0 - (float)(g_unk_010906e0 - GHIDRA_FIELD(cgs, 33575976, 4))));
      return;
    }
    GHIDRA_FIELD(cgs, 33575976, 4) = g_unk_010906e0;
  }
  return;
}

void CG_AutomapExpandUp_f(void)
{
  if (GHIDRA_FIELD(cgs, 33575972, 4) != 0) {
    GHIDRA_FIELD(cgs, 33575972, 4) = 0;
    if ((float)(g_unk_010906e0 - GHIDRA_FIELD(cgs, 33575976, 4)) < 250.0) {
      GHIDRA_FIELD(cgs, 33575976, 4) =
           (int)ROUND((float)g_unk_010906e0 - (250.0 - (float)(g_unk_010906e0 - GHIDRA_FIELD(cgs, 33575976, 4))));
      return;
    }
    GHIDRA_FIELD(cgs, 33575976, 4) = g_unk_010906e0;
  }
  return;
}

void CG_keyOff_f(void)
{
  if (g_unk_01047aec != 0) {
    CG_EventHandling(0,0);
  }
  return;
}

void CG_ClassMenu_f(void)
{
  if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3) {
    CG_EventHandling(0,0);
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) != 0) {
      trap_UI_Popup(0x10);
      return;
    }
    trap_UI_Popup(0xf);
  }
  return;
}

void CG_QuickFireteamAdmin_f(void)
{
  if (GHIDRA_FIELD(cgs, 27388, 4) != 8) {
    trap_UI_Popup(0);
    if (g_unk_010abd7c == 0) {
      if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3) {
        return;
      }
      CG_EventHandling(5,0);
    }
    else if (GHIDRA_FIELD(cgs, 33701700, 4) == 1) {
      CG_EventHandling(0,0);
      return;
    }
    GHIDRA_FIELD(cgs, 33701700, 4) = 1;
  }
  return;
}

void CG_topshotsDown_f(void)
{
  float tmp_f1;
  
  if (g_unk_01047aec != 0) {
    return;
  }
  if (GHIDRA_FIELD(cgs, 33598844, 4) == 1) {
    if ((int)GHIDRA_FIELD(cgs, 33598840, 4) <= g_unk_010906e0) goto LAB_00042d6f;
    tmp_f1 = ((float)(g_unk_010906e0 * 2) + 200.0) - (float)(int)GHIDRA_FIELD(cgs, 33598840, 4);
  }
  else {
    if (GHIDRA_FIELD(cgs, 33598844, 4) == 2) goto LAB_00042d9e;
LAB_00042d6f:
    tmp_f1 = (float)g_unk_010906e0 + 200.0;
  }
  GHIDRA_FIELD(cgs, 33598840, 4) = (uint32_t)ROUND(tmp_f1);
LAB_00042d9e:
  GHIDRA_FIELD(cgs, 33598844, 4) = 2;
  if ((int)GHIDRA_FIELD(cgs, 33598848, 4) < g_unk_010906e0) {
    GHIDRA_FIELD(cgs, 33598848, 4) = g_unk_010906e0 + 2000;
    trap_SendClientCommand("stshots");
  }
  return;
}

void CG_ScoresDown_f(void)
{
  if (((g_unk_010928a4 == 0) && (g_unk_010906e0 <= g_unk_010928b0 + 0xf9)) &&
     (g_unk_010928b4 < g_unk_010906e0 + -500)) {
    g_unk_010928b8 = (uint)(g_unk_010928b8 != 1);
    g_unk_010928b4 = g_unk_010906e0;
  }
  g_unk_010928b0 = g_unk_010906e0;
  if (g_unk_010906e0 <= g_unk_01091e80 + 2000) {
    g_unk_010928a4 = 1;
    return;
  }
  g_unk_01091e80 = g_unk_010906e0;
  if (g_unk_01047aec == 0) {
    trap_SendClientCommand("score");
  }
  if (((g_unk_010928a4 == 0) && (g_unk_010928a4 = 1, g_unk_01047aec == 0)) &&
     (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95ac) == 0)) {
    g_unk_01091e84 = 0;
  }
  return;
}

void CG_StatsDown_f(void)
{
  float tmp_f1;
  uint32_t tmp_u2;
  
  if (g_unk_01047aec != 0) {
    return;
  }
  if (GHIDRA_FIELD(cgs, 33585516, 4) == 1) {
    if ((int)GHIDRA_FIELD(cgs, 33585512, 4) <= g_unk_010906e0) goto LAB_00042f84;
    tmp_f1 = ((float)(g_unk_010906e0 * 2) + 200.0) - (float)(int)GHIDRA_FIELD(cgs, 33585512, 4);
  }
  else {
    if (GHIDRA_FIELD(cgs, 33585516, 4) == 2) goto LAB_00042fb3;
LAB_00042f84:
    tmp_f1 = (float)g_unk_010906e0 + 200.0;
  }
  GHIDRA_FIELD(cgs, 33585512, 4) = (uint32_t)ROUND(tmp_f1);
LAB_00042fb3:
  GHIDRA_FIELD(cgs, 33585516, 4) = 2;
  if ((int)GHIDRA_FIELD(cgs, 33585520, 4) < g_unk_010906e0) {
    GHIDRA_FIELD(cgs, 33585520, 4) = g_unk_010906e0 + 2000;
    tmp_u2 = va("sgstats %d",*(uint32_t *)(g_unk_01047b00 + 0xcc));
    trap_SendClientCommand(tmp_u2);
  }
  return;
}

void CG_autoScreenShot_f(void)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  
  if (GHIDRA_FIELD(cgs, 33823104, 4) == 0) {
    tmp_u1 = CG_generateFilename();
    if (GHIDRA_FIELD(cg_useScreenshotJPEG, 12, 4) == 0) {
      tmp_pc2 = "";
    }
    else {
      tmp_pc2 = "JPEG";
    }
    tmp_u1 = va("screenshot%s %s\n",tmp_pc2,tmp_u1);
    trap_SendConsoleCommand(tmp_u1);
    return;
  }
  tmp_u1 = CG_generateFilename();
  tmp_u1 = va("screenshot %s\n",tmp_u1);
  trap_SendConsoleCommand(tmp_u1);
  return;
}

void CG_vstrDown_f(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = trap_Argc();
  if (tmp_i1 != 5) {
    CG_Printf("[cgnotify]Usage: +vstr [down_vstr] [up_vstr]\n");
    return;
  }
  tmp_u2 = CG_Argv(1);
  tmp_u2 = va("vstr %s;",tmp_u2);
  trap_SendConsoleCommand(tmp_u2);
  return;
}

void CG_vstrUp_f(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = trap_Argc();
  if (tmp_i1 != 5) {
    CG_Printf("[cgnotify]Usage: +vstr [down_vstr] [up_vstr]\n");
    return;
  }
  tmp_u2 = CG_Argv(2);
  tmp_u2 = va("vstr %s;",tmp_u2);
  trap_SendConsoleCommand(tmp_u2);
  return;
}

void CG_TeamVoiceChat_f(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t local_4c [68];
  
  tmp_i1 = trap_Argc();
  if (tmp_i1 == 2) {
    trap_Argv(1,local_4c,0x40);
    tmp_u2 = va("cmd vsay_team %s\n",local_4c);
    trap_SendConsoleCommand(tmp_u2);
  }
  return;
}

void CG_VoiceChat_f(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t local_4c [68];
  
  tmp_i1 = trap_Argc();
  if (tmp_i1 == 2) {
    trap_Argv(1,local_4c,0x40);
    tmp_u2 = va("cmd vsay %s\n",local_4c);
    trap_SendConsoleCommand(tmp_u2);
  }
  return;
}

void CG_MessageMode_f(void)
{
  int tmp_i1;
  uint8_t local_4c [68];
  
  if (GHIDRA_FIELD(cgs, 67784, 4) != 0) {
    return;
  }
  trap_Argv(0,local_4c,0x40);
  tmp_i1 = Q_stricmp(local_4c,"messagemode2");
  if (tmp_i1 == 0) {
    trap_Cvar_Set("cg_messageType","2");
  }
  else {
    tmp_i1 = Q_stricmp(local_4c,"messagemode3");
    if (tmp_i1 == 0) {
      trap_Cvar_Set("cg_messageType","3");
    }
    else {
      tmp_i1 = Q_stricmp(local_4c,"messagemode4");
      if (tmp_i1 == 0) {
        trap_Cvar_Set("cg_messageType","4");
      }
      else {
        trap_Cvar_Set("cg_messageType",&g_unk_0011e9db);
      }
    }
  }
  trap_Cvar_Set("cg_messageText",&g_unk_0011d841);
  trap_UI_Popup(0x11);
  return;
}

void CG_DumpSpeaker_f(void)
{
  uint tmp_u1;
  int tmp_i2;
  float local_e8;
  float local_e4;
  float local_e0;
  uint8_t local_dc [8];
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_a4 [38];
  
  if (g_unk_010b4554 == 0) {
    CG_Printf("Speaker Edit mode needs to be activated to dump speakers\n");
  }
  else {
    tmp_u1 = 0;
    do {
      *(uint32_t *)((int)local_a4 + tmp_u1) = 0;
      *(uint32_t *)((int)local_a4 + tmp_u1 + 4) = 0;
      tmp_u1 = tmp_u1 + 8;
    } while (tmp_u1 < 0x98);
    local_a4[0x21] = 1.77965e-43;
    local_a4[0x22] = 1.75162e-42;
    local_e8 = *(float *)(g_unk_010afbcc + 0x24) * 32.0 + *(float *)(g_unk_010afbcc + 0x18);
    local_e4 = *(float *)(g_unk_010afbcc + 0x28) * 32.0 + *(float *)(g_unk_010afbcc + 0x1c);
    local_e0 = *(float *)(g_unk_010afbcc + 0x2c) * 32.0 + *(float *)(g_unk_010afbcc + 0x20);
    CG_Trace(local_dc,(float *)(g_unk_010afbcc + 0x18),0,0,&local_e8,0xffffffff,1);
    if (local_d4 < 1.0) {
      local_a4[0x11] = *(float *)(g_unk_010afbcc + 0x24) * -4.0 + local_d0;
      local_a4[0x12] = *(float *)(g_unk_010afbcc + 0x28) * -4.0 + local_cc;
      local_a4[0x13] = *(float *)(g_unk_010afbcc + 0x2c) * -4.0 + local_c8;
    }
    else {
      local_a4[0x11] = local_d0;
      local_a4[0x12] = local_cc;
      local_a4[0x13] = local_c8;
    }
    tmp_i2 = BG_SS_StoreSpeaker(local_a4);
    if (tmp_i2 == 0) {
      CG_Printf("^1ERROR: Failed to store speaker\n");
    }
  }
  return;
}

void CG_EditSpeakers_f(void)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  
  if (g_unk_010b4554 != 0) {
    CG_DeActivateEditSoundMode();
    return;
  }
  tmp_u1 = CG_ConfigString(1);
  tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"sv_cheats");
  if (*tmp_pc2 != '1') {
    CG_Printf("editSpeakers is cheat protected.\n");
    return;
  }
  CG_ActivateEditSoundMode();
  return;
}

void CG_QuickFireteams_f(void)
{
  int tmp_i1;
  
  if (g_unk_010abd7c == 0) {
    tmp_i1 = CG_IsOnFireteam(g_unk_01047ac4);
    if (tmp_i1 == 0) {
      return;
    }
    CG_EventHandling(5,0);
  }
  else if (GHIDRA_FIELD(cgs, 33701700, 4) == 0) {
    CG_EventHandling(0,0);
    return;
  }
  GHIDRA_FIELD(cgs, 33701700, 4) = 0;
  return;
}

void CG_BuddyVoiceChat_f(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t local_4c [68];
  
  tmp_i1 = trap_Argc();
  if (tmp_i1 == 2) {
    trap_Argv(1,local_4c,0x40);
    tmp_u2 = CG_BuildSelectedFirteamString();
    tmp_u2 = va("cmd vsay_buddy -1 %s %s\n",tmp_u2,local_4c);
    trap_SendConsoleCommand(tmp_u2);
  }
  return;
}

void CG_Class_f(void)
{
  int tmp_i1;
  char *tmp_pc2;
  int tmp_i3;
  uint tmp_u4;
  uint32_t tmp_u5;
  uint32_t tmp_u6;
  long tmp_l7;
  uint8_t *local_20;
  
  if ((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3) && (tmp_i1 = trap_Argc(), 1 < tmp_i1)) {
    tmp_i1 = 0;
    tmp_pc2 = (char *)CG_Argv(1);
    if ((byte)(*tmp_pc2 + 0x9dU) < 0xb) {
      tmp_i1 = *(int *)(CSWTCH_54 + (uint)(byte)(*tmp_pc2 + 0x9dU) * 4);
    }
    if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 1) {
      local_20 = bg_axis_playerclasses + tmp_i1 * 0x30;
    }
    else {
      if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 2) {
        return;
      }
      local_20 = bg_allies_playerclasses + tmp_i1 * 0x30;
    }
    tmp_i3 = trap_Argc();
    if (tmp_i3 < 3) {
      tmp_i3 = *(int *)(local_20 + 0x10);
      tmp_u4 = 0xffffffff;
    }
    else {
      tmp_pc2 = (char *)CG_Argv(2);
      tmp_l7 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_u4 = tmp_l7 - 1;
      if (tmp_u4 < 6) {
        tmp_i3 = *(int *)(local_20 + (tmp_l7 + 3) * 4);
        if (tmp_i3 == 0) {
          tmp_i3 = *(int *)(local_20 + 0x10);
        }
      }
      else {
        tmp_i3 = *(int *)(local_20 + 0x10);
      }
    }
    CG_LimboPanel_SetSelectedWeaponNumForSlot(tmp_u4,0);
    if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 1) {
      tmp_pc2 = "r";
    }
    else {
      tmp_pc2 = "b";
    }
    tmp_u5 = va("team %s %i %i \n",tmp_pc2,tmp_i1,tmp_i3);
    trap_SendClientCommand(tmp_u5);
    if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 1) {
      tmp_pc2 = "Axis";
    }
    else if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 2) {
      tmp_pc2 = "Allied";
    }
    else {
      tmp_pc2 = "unknown";
    }
    tmp_u5 = *(uint32_t *)(ammoTableMP + tmp_i3 * 0x48 + 0x40);
    tmp_u6 = BG_ClassnameForNumber(tmp_i1);
    tmp_u5 = va("You will spawn as an %s %s with a %s.",tmp_pc2,tmp_u6,tmp_u5);
    CG_CenterPrint(tmp_u5,0x188,8);
    GHIDRA_FIELD(cgs, 33701708, 4) = 1;
  }
  return;
}

void CG_QuickFireteamMessage_f(void)
{
  if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3) {
    CG_EventHandling(0,0);
    if (GHIDRA_FIELD(cg_quickMessageAlt, 12, 4) != 0) {
      trap_UI_Popup(0xb);
      return;
    }
    trap_UI_Popup(10);
  }
  return;
}

void CG_wStatsDown_f(void)
{
  uint32_t tmp_u1;
  
  if (*(int *)(g_unk_01047b00 + 0x158) == 3) {
    tmp_u1 = CG_LocalizeServerCommand("You must be a player or following a player to use +wstats\n");
    CG_Printf("[cgnotify]%s",tmp_u1);
  }
  else {
    if (g_unk_010afbd8 < g_unk_010906e0) {
      g_unk_010afbd8 = g_unk_010906e0 + 500;
      tmp_u1 = va("wstats %d",*(uint32_t *)(g_unk_01047b00 + 0xcc));
      trap_SendClientCommand(tmp_u1);
    }
    g_unk_010afbd0 = 1;
  }
  return;
}

void CG_wStatsUp_f(void)
{
  g_unk_010afbd0 = 0;
  CG_windowFree(g_unk_010afbdc);
  g_unk_010afbdc = 0;
  return;
}

void CG_toggleSpecHelp_f(void)
{
  if (g_unk_01047aec == 0) {
    if (g_unk_010afbd4 == 2) {
      CG_ShowHelp_Off(&g_unk_010afbd4);
    }
    else if (0 < (int)GHIDRA_FIELD(cg_specHelp, 12, 4)) {
      CG_ShowHelp_On(&g_unk_010afbd4);
      return;
    }
  }
  return;
}

void CG_parseMapVoteListInfo(void)
{
  int tmp_i1;
  char *tmp_pc2;
  long tmp_l3;
  uint32_t tmp_u4;
  int tmp_i5;
  long *plVar6;
  int tmp_i7;
  int local_28;
  int local_24;
  
  tmp_i1 = trap_Argc();
  tmp_i7 = tmp_i1 + -2;
  if (tmp_i1 + -2 < 0) {
    tmp_i7 = tmp_i1 + 1;
  }
  GHIDRA_FIELD(cgs, 33687752, 4) = tmp_i7 >> 2;
  tmp_pc2 = (char *)CG_Argv(1);
  tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
  if (tmp_l3 != 0) {
    GHIDRA_FIELD(cgs, 33701076, 4) = 1;
  }
  tmp_i1 = 2;
  local_28 = 0;
  local_24 = 0x311172c;
  tmp_i7 = 0x311072c;
  plVar6 = (long *)(cgs + 0x20239cc);
  while (local_28 < (int)GHIDRA_FIELD(cgs, 33687752, 4)) {
    tmp_u4 = CG_Argv(tmp_i1);
    Q_strncpyz(tmp_i7,tmp_u4,0x40);
    plVar6[-0x40] = 0;
    tmp_pc2 = (char *)CG_Argv(tmp_i1 + 1);
    tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    local_28 = local_28 + 1;
    *plVar6 = tmp_l3;
    tmp_pc2 = (char *)CG_Argv(local_28 * 4);
    tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    plVar6[0x40] = tmp_l3;
    tmp_pc2 = (char *)CG_Argv(tmp_i1 + 3);
    tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    plVar6[0x80] = tmp_l3;
    tmp_u4 = va("scripts/%s.arena",tmp_i7);
    tmp_i5 = CG_FindArenaInfo(tmp_u4,tmp_i7,0x30f417c);
    if (tmp_i5 == 0) {
      Q_strncpyz(local_24,tmp_i7,0x40);
    }
    else {
      Q_strncpyz(local_24,0x30f517c,0x40);
    }
    local_24 = local_24 + 0x80;
    tmp_i7 = tmp_i7 + 0x40;
    tmp_i1 = tmp_i1 + 4;
    plVar6 = plVar6 + 1;
  }
  CG_LocateArena();
  GHIDRA_FIELD(cgs, 33701072, 4) = 1;
  return;
}

void CG_parseMapVoteTally(void)
{
  int tmp_i1;
  char *__nptr;
  long tmp_l2;
  int tmp_i3;
  
  tmp_i1 = trap_Argc();
  if (1 < tmp_i1) {
    tmp_i3 = 0;
    do {
      tmp_i3 = tmp_i3 + 1;
      __nptr = (char *)CG_Argv(tmp_i3);
      tmp_l2 = strtol(__nptr,(char **)0x0,10);
      *(long *)(cgs + tmp_i3 * 4 + 0x20238c8) = tmp_l2;
    } while (tmp_i3 != tmp_i1 + -1);
  }
  return;
}

int CG_SortPlayersByXP(int *param_1,int *param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  bool tmp_b4;
  
  tmp_i3 = *param_2 * 0x1a4;
  if (*(int *)(cgs + tmp_i3 + 0x940c) == 0) {
    tmp_i1 = -1;
  }
  else {
    tmp_i2 = *param_1 * 0x1a4;
    tmp_i1 = 1;
    if (*(int *)(cgs + tmp_i2 + 0x940c) != 0) {
      if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
        tmp_i1 = *(int *)(cgs + tmp_i2 + 0x9584);
        tmp_i3 = *(int *)(cgs + tmp_i3 + 0x9584);
        tmp_b4 = SBORROW4(tmp_i3,tmp_i1);
        tmp_i2 = tmp_i3 - tmp_i1;
        if (tmp_i1 < tmp_i3) {
          return 1;
        }
      }
      else {
        tmp_i1 = *(int *)(cgs + tmp_i2 + 0x9498);
        tmp_i3 = *(int *)(cgs + tmp_i3 + 0x9498);
        tmp_b4 = SBORROW4(tmp_i3,tmp_i1);
        tmp_i2 = tmp_i3 - tmp_i1;
        if (tmp_i1 < tmp_i3) {
          return 1;
        }
      }
      tmp_i1 = -(uint)(tmp_b4 != tmp_i2 < 0);
    }
  }
  return tmp_i1;
}

void CG_TeamDebriefingMapWinner_Draw(void)
{
  return;
}

void CG_TeamDebriefingMapList_Draw(int param_1)
{
  float tmp_f1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  int tmp_i4;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x456f9;
  tmp_f1 = *(float *)(param_1 + 0xc);
  if ((int)GHIDRA_FIELD(cgs, 33701652, 4) < 0xb) {
    tmp_i4 = 0;
    tmp_i3 = GHIDRA_FIELD(cgs, 33701652, 4);
    do {
      tmp_f1 = tmp_f1 + 12.0;
      if (tmp_i3 == GHIDRA_FIELD(cgs, 33701656, 4)) {
        local_2c = 0x3f800000;
        local_28 = 0x3f800000;
        local_24 = 0x3f800000;
        local_20 = 0x3e99999a;
        CG_FillRect(*(uint32_t *)(param_1 + 8),tmp_f1 - 10.0,*(uint32_t *)(param_1 + 0x10),
                    0x41400000,&local_2c);
      }
      if (GHIDRA_FIELD(cgs, 33701652, 4) + tmp_i4 == 0) {
        tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
        CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),tmp_f1,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,
                          "Campaign Overview",0,0,0,tmp_pu2[8]);
      }
      else {
        tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
        CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),tmp_f1,*tmp_pu2,tmp_pu2[1],tmp_pu2 + 2,
                          (GHIDRA_FIELD(cgs, 33701652, 4) + tmp_i4 + -1) * 0x1088 + 0x30eac10,0,0,0,tmp_pu2[8]);
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_i3 = GHIDRA_FIELD(cgs, 33701652, 4) + tmp_i4;
    } while ((tmp_i3 < 0xb) && (tmp_i4 != 4));
  }
  return;
}

void CG_MapVoteList_Draw(int param_1)
{
  uint8_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  uint32_t *tmp_pu6;
  int tmp_i7;
  float local_40;
  float local_34;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x45dd9;
  tmp_pu6 = *(uint32_t **)(param_1 + 0x38);
  local_40 = *(float *)(param_1 + 0xc);
  tmp_u4 = tmp_pu6[8];
  if ((int)GHIDRA_FIELD(cgs, 33787488, 4) < 1) {
    tmp_pu1 = &g_unk_0011d841;
  }
  else {
    tmp_pu1 = (uint8_t *)va("Map %d of %d",GHIDRA_FIELD(cgs, 33787484, 4) + 1,GHIDRA_FIELD(cgs, 33787488, 4));
    tmp_pu6 = *(uint32_t **)(param_1 + 0x38);
  }
  CG_Text_Paint_Ext(0x43910000,0x42840000,*tmp_pu6,tmp_pu6[1],tmp_pu6 + 2,tmp_pu1,0,0,0,tmp_u4);
  if ((int)GHIDRA_FIELD(cgs, 33787488, 4) < 1) {
    local_34 = 81.0;
  }
  else if (GHIDRA_FIELD(cgs, 33787484, 4) + 1 < (int)GHIDRA_FIELD(cgs, 33787488, 4)) {
    local_34 = 81.0;
  }
  else {
    tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
    tmp_u2 = va("^1XP Resetting!");
    tmp_pu6 = *(uint32_t **)(param_1 + 0x38);
    CG_Text_Paint_Ext(0x43910000,0x42a20000,*tmp_pu6,tmp_pu6[1],tmp_pu6 + 2,tmp_u2,0,0,0,tmp_u4);
    local_34 = 96.0;
  }
  if (((int)GHIDRA_FIELD(cgs, 33687748, 4) < (int)GHIDRA_FIELD(cgs, 33687752, 4)) &&
     (cgs[(GHIDRA_FIELD(cgs, 33687748, 4) + 0x80823) * 0x40 + 0xc] != '\0')) {
    tmp_i7 = 0;
    tmp_i3 = GHIDRA_FIELD(cgs, 33687748, 4);
    do {
      local_40 = local_40 + 12.0;
      if (tmp_i3 == GHIDRA_FIELD(cgs, 33701068, 4)) {
        local_2c = 0x3f800000;
        local_28 = 0x3f800000;
        local_24 = 0x3f800000;
        local_20 = 0x3e99999a;
        CG_FillRect(*(uint32_t *)(param_1 + 8),local_40 - 10.0,0x437a0000,0x41400000,&local_2c);
        tmp_u4 = va("levelshots/%s.tga",(GHIDRA_FIELD(cgs, 33687748, 4) + tmp_i7 + 0x80823) * 0x40 + 0x10efe6c);
        tmp_i3 = trap_R_RegisterShaderNoMip(tmp_u4);
        if (tmp_i3 != 0) {
          CG_DrawPic(0x44030000,0x42480000,0x42c00000,0x42900000,tmp_i3);
        }
        tmp_u4 = va("levelshots/%s_cc.tga",(GHIDRA_FIELD(cgs, 33687748, 4) + tmp_i7 + 0x80823) * 0x40 + 0x10efe6c);
        tmp_i3 = trap_R_RegisterShaderNoMip(tmp_u4);
        if (tmp_i3 != 0) {
          CG_DrawPic(0x43d60000,0x431a0000,0x43400000,0x43400000,tmp_i3);
        }
        tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
        if (*(int *)(cgs + (GHIDRA_FIELD(cgs, 33687748, 4) + tmp_i7) * 4 + 0x2023acc) == -1) {
          tmp_pc5 = "^1Never";
        }
        else {
          tmp_pc5 = (char *)va("^3%d ^7maps ago",
                              *(int *)(cgs + (GHIDRA_FIELD(cgs, 33687748, 4) + tmp_i7) * 4 + 0x2023acc));
        }
        tmp_u2 = va("Last Played            : %s",tmp_pc5);
        tmp_pu6 = *(uint32_t **)(param_1 + 0x38);
        CG_Text_Paint_Ext(0x43910000,local_34,*tmp_pu6,tmp_pu6[1],tmp_pu6 + 2,tmp_u2,0,0,0,tmp_u4);
        tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
        local_34 = local_34 + 15.0;
        tmp_u2 = va("Total Accumulated Votes: ^3%d",
                   *(uint32_t *)(cgs + (GHIDRA_FIELD(cgs, 33687748, 4) + tmp_i7) * 4 + 0x2023bcc));
        tmp_pu6 = *(uint32_t **)(param_1 + 0x38);
        CG_Text_Paint_Ext(0x43910000,local_34,*tmp_pu6,tmp_pu6[1],tmp_pu6 + 2,tmp_u2,0,0,0,tmp_u4);
      }
      tmp_pu6 = *(uint32_t **)(param_1 + 0x38);
      CG_Text_Paint_Ext(0x41700000,local_40,*tmp_pu6,tmp_pu6[1],tmp_pu6 + 2,
                        (GHIDRA_FIELD(cgs, 33687748, 4) + tmp_i7) * 0x80 + 0x311172c,0,0x1e,0,tmp_pu6[8]);
      tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
      tmp_i3 = GHIDRA_FIELD(cgs, 33687748, 4) + tmp_i7;
      if (*(int *)(cgs + tmp_i3 * 4 + 0x20238cc) == 0) {
        tmp_pc5 = "";
      }
      else {
        tmp_pc5 = "^7";
      }
      tmp_i7 = tmp_i7 + 1;
      tmp_u2 = va(&g_unk_00121550,tmp_pc5,*(int *)(cgs + tmp_i3 * 4 + 0x20238cc));
      tmp_pu6 = *(uint32_t **)(param_1 + 0x38);
      CG_Text_Paint_Ext(0x43610000,local_40,*tmp_pu6,tmp_pu6[1],tmp_pu6 + 2,tmp_u2,0,0,0,tmp_u4);
      tmp_i3 = GHIDRA_FIELD(cgs, 33687748, 4) + tmp_i7;
    } while (((tmp_i3 < (int)GHIDRA_FIELD(cgs, 33687752, 4)) && (tmp_i7 != 0x13)) &&
            (cgs[(tmp_i3 + 0x80823) * 0x40 + 0xc] != '\0'));
  }
  return;
}

void CG_TeamDebriefingOutcome_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  float tmp_f2;
  int tmp_i3;
  char *tmp_pc4;
  byte tmp_b5;
  char *__s;
  char tmp_c6;
  char local_40c [1020];
  uint32_t uStack_10;
  
  uStack_10 = 0x464c8;
  if (GHIDRA_FIELD(cgs, 33701656, 4) != 0) {
    tmp_b5 = (char)GHIDRA_FIELD(cgs, 33701656, 4) - 1;
    if ((g_unk_010aabf4 >> (tmp_b5 & 0x1f) & 1U) == 0) {
      if ((g_unk_010aabf0 >> (tmp_b5 & 0x1f) & 1U) == 0) {
        return;
      }
      tmp_i3 = (GHIDRA_FIELD(cgs, 33701652, 4) + -1) * 0x1088 + 0x30ea810;
    }
    else {
      tmp_i3 = (GHIDRA_FIELD(cgs, 33701652, 4) + -1) * 0x1088 + 0x30ea410;
    }
    __s = local_40c;
    Q_strncpyz(__s,tmp_i3,0x400);
    while (tmp_pc4 = strchr(__s,0x2a), tmp_pc4 != (char *)0x0) {
      *tmp_pc4 = '\n';
    }
    BG_FitTextToWidth_Ext
              (__s,**(uint32_t **)(param_1 + 0x38),*(float *)(param_1 + 0x10) - 16.0,0x400,
               (*(uint32_t **)(param_1 + 0x38))[8]);
    tmp_f2 = *(float *)(param_1 + 0xc) + 12.0;
    while (tmp_c6 = *__s, tmp_pc4 = __s, tmp_c6 != '\0') {
      while (tmp_c6 != '\n') {
        tmp_pc4 = tmp_pc4 + 1;
        tmp_c6 = *tmp_pc4;
        if (tmp_c6 == '\0') {
          return;
        }
      }
      *tmp_pc4 = '\0';
      tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
      CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 4.0,tmp_f2,*tmp_pu1,tmp_pu1[1],tmp_pu1 + 2,__s,0,0,0,
                        tmp_pu1[8]);
      tmp_f2 = tmp_f2 + 8.0;
      __s = tmp_pc4 + 1;
    }
  }
  return;
}

uint32_t CG_TeamDebriefingMapList_KeyDown(int param_1,int param_2)
{
  int tmp_i1;
  
  if (param_2 == 0xb2) {
    tmp_i1 = (int)ROUND((float)(int)GHIDRA_FIELD(cgs, 33701652, 4) +
                       ((float)(int)GHIDRA_FIELD(cgs, 67780, 4) - *(float *)(param_1 + 0xc)) / 12.0);
    if ((-1 < tmp_i1) && (tmp_i1 <= (int)GHIDRA_FIELD(cgs, 33571584, 4))) {
      GHIDRA_FIELD(cgs, 33701656, 4) = tmp_i1;
      return 1;
    }
  }
  return 0;
}

uint32_t CG_MapVote_VoteButton_KeyDown(uint32_t param_1,int param_2)
{
  uint32_t tmp_u1;
  
  if ((param_2 == 0xb2) && (g_unk_01047b00 != 0)) {
    if (GHIDRA_FIELD(cgs, 33701076, 4) != 0) {
      return 0;
    }
    if (GHIDRA_FIELD(cgs, 33701068, 4) != -1) {
      tmp_u1 = va("mapvote %d",*(uint32_t *)(cgs + GHIDRA_FIELD(cgs, 33701068, 4) * 4 + 0x20239cc));
      trap_SendClientCommand(tmp_u1);
      GHIDRA_FIELD(cgs, 33701080, 4) = GHIDRA_FIELD(cgs, 33701068, 4);
      return 1;
    }
  }
  return 0;
}

uint32_t CG_MapVote_MultiVoteButton_KeyDown(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  if (param_2 != 0xb2) {
    return 0;
  }
  if (g_unk_01047b00 == 0) {
    return 0;
  }
  if (GHIDRA_FIELD(cgs, 33701076, 4) == 0) {
    return 0;
  }
  if (GHIDRA_FIELD(cgs, 33701068, 4) == -1) {
    return 0;
  }
  tmp_i1 = *(int *)(param_1 + 0x34) + -1;
  if (tmp_i1 == 2) {
LAB_000469d4:
    if (GHIDRA_FIELD(cgs, 33701068, 4) == GHIDRA_FIELD(cgs, 33701084, 4)) goto LAB_00046a40;
    if (tmp_i1 == 0) goto LAB_000469e8;
  }
  else {
    if (GHIDRA_FIELD(cgs, 33701068, 4) == GHIDRA_FIELD(cgs, 33701088, 4)) goto LAB_00046a40;
    if (tmp_i1 != 1) goto LAB_000469d4;
  }
  if (GHIDRA_FIELD(cgs, 33701068, 4) != GHIDRA_FIELD(cgs, 33701080, 4)) {
LAB_000469e8:
    tmp_u2 = va("mapvote %d %d",*(uint32_t *)(cgs + GHIDRA_FIELD(cgs, 33701068, 4) * 4 + 0x20239cc),
               *(int *)(param_1 + 0x34));
    trap_SendClientCommand(tmp_u2);
    *(uint32_t *)(cgs + tmp_i1 * 4 + 0x2023cd8) = GHIDRA_FIELD(cgs, 33701068, 4);
    return 1;
  }
LAB_00046a40:
  CG_Printf("^3Can\'t vote for the same map twice\n");
  return 0;
}

void CG_TeamDebriefingMapShot_Draw(int param_1)
{
  uint32_t tmp_u1;
  
  if (GHIDRA_FIELD(cgs, 33701656, 4) != 0) {
    tmp_u1 = va("levelshots/%s_cc.tga",GHIDRA_FIELD(cgs, 33701656, 4) * 0x40 + 0x30e9900);
    tmp_u1 = trap_R_RegisterShaderNoMip(tmp_u1);
    CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),tmp_u1);
    return;
  }
  tmp_u1 = trap_R_RegisterShaderNoMip("gfx/loading/map_back");
  CG_DrawPicST(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),0,0,0x3f300000,
               0x3f800000,tmp_u1);
  return;
}

uint32_t CG_MapVoteList_KeyDown(uint32_t param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = 0;
  if (param_2 == 0xb2) {
    tmp_i2 = (GHIDRA_FIELD(cgs, 67780, 4) + -0x38) / 0xc + GHIDRA_FIELD(cgs, 33687748, 4);
    if ((-1 < tmp_i2) && (tmp_i2 < (int)GHIDRA_FIELD(cgs, 33687752, 4))) {
      if (tmp_i2 == GHIDRA_FIELD(cgs, 33701068, 4)) {
        tmp_u1 = 1;
      }
      else {
        tmp_u1 = 1;
        GHIDRA_FIELD(cgs, 33701068, 4) = tmp_i2;
      }
    }
  }
  return tmp_u1;
}

int CG_TeamDebriefing_CalcXP_constprop_18(int param_1,int param_2)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 4) {
    tmp_pu1 = cgs;
    if ((int)GHIDRA_FIELD(cgs, 33571584, 4) < 1) {
      tmp_i2 = 0;
    }
    else {
      tmp_i3 = 0;
      tmp_i2 = 0;
      if (param_1 != 1) {
        if (param_2 == 0) goto LAB_00046e64;
        do {
          if (param_2 == -1) goto LAB_00046e64;
          while( true ) {
            tmp_i3 = tmp_i3 + 1;
            tmp_pu1 = tmp_pu1 + 4;
            if (tmp_i3 == GHIDRA_FIELD(cgs, 33571584, 4)) {
              return tmp_i2;
            }
            if (param_2 != tmp_i3) break;
LAB_00046e64:
            tmp_i2 = tmp_i2 + *(int *)(cgs + (int)(tmp_pu1 + 0xf33f9c)) +
                    *(int *)(cgs + (int)(tmp_pu1 + 0xf33fc4)) +
                    *(int *)(cgs + (int)(tmp_pu1 + 0xf33fec)) +
                    *(int *)(cgs + (int)(tmp_pu1 + 0xf34014)) +
                    *(int *)(cgs + (int)(tmp_pu1 + 0xf3403c)) +
                    *(int *)(cgs + (int)(tmp_pu1 + 0xf34064)) +
                    *(int *)(cgs + (int)(tmp_pu1 + 0xf3408c));
          }
        } while( true );
      }
      do {
        if ((param_2 == tmp_i3) || (param_2 == -1)) {
          tmp_i2 = tmp_i2 + *(int *)(cgs + (int)(tmp_pu1 + 0xf33e84)) +
                  *(int *)(cgs + (int)(tmp_pu1 + 0xf33eac)) +
                  *(int *)(cgs + (int)(tmp_pu1 + 0xf33ed4)) +
                  *(int *)(cgs + (int)(tmp_pu1 + 0xf33efc)) +
                  *(int *)(cgs + (int)(tmp_pu1 + 0xf33f24)) +
                  *(int *)(cgs + (int)(tmp_pu1 + 0xf33f4c)) +
                  *(int *)(cgs + (int)(tmp_pu1 + 0xf33f74));
        }
        tmp_i3 = tmp_i3 + 1;
        tmp_pu1 = tmp_pu1 + 4;
      } while (tmp_i3 != GHIDRA_FIELD(cgs, 33571584, 4));
    }
  }
  else if ((GHIDRA_FIELD(cg_gameType, 12, 4) - 6 < 3) || (tmp_i2 = 0, GHIDRA_FIELD(cg_gameType, 12, 4) - 2 < 2)) {
    if (param_1 == 1) {
      tmp_i2 = GHIDRA_FIELD(cgs, 33701132, 4) + GHIDRA_FIELD(cgs, 33701092, 4) + GHIDRA_FIELD(cgs, 33701172, 4) + GHIDRA_FIELD(cgs, 33701212, 4) +
              GHIDRA_FIELD(cgs, 33701252, 4) + GHIDRA_FIELD(cgs, 33701292, 4) + GHIDRA_FIELD(cgs, 33701332, 4);
    }
    else {
      tmp_i2 = GHIDRA_FIELD(cgs, 33701372, 4) + GHIDRA_FIELD(cgs, 33701412, 4) + GHIDRA_FIELD(cgs, 33701452, 4) + GHIDRA_FIELD(cgs, 33701492, 4) +
              GHIDRA_FIELD(cgs, 33701532, 4) + GHIDRA_FIELD(cgs, 33701572, 4) + GHIDRA_FIELD(cgs, 33701612, 4);
    }
  }
  return tmp_i2;
}

void CG_PanelButtonsRender_Window(int param_1)
{
  int tmp_i1;
  float tmp_f2;
  int tmp_i3;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  local_3c = 0;
  local_38 = 0;
  tmp_i1 = *(int *)(param_1 + 4);
  tmp_i3 = *(int *)(param_1 + 0x18);
  local_34 = 0;
  local_30 = 0x3f4ccccd;
  local_2c = 0x3f19999a;
  local_28 = 0x3f19999a;
  local_24 = 0x3f19999a;
  local_20 = 0x3f800000;
  CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
              *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_3c);
  CG_DrawRect_FixedBorder
            (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
             *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&HUD_Border);
  CG_FillRect(*(float *)(param_1 + 8) + 2.0,*(float *)(param_1 + 0xc) + 2.0,
              *(float *)(param_1 + 0x10) - 4.0,0x41400000,&HUD_Background);
  if (tmp_i1 != 0) {
    if (tmp_i3 == 1) {
      tmp_i3 = CG_Text_Width_Ext(tmp_i1,0x3e428f5c,0,0x1100f64);
      tmp_f2 = (*(float *)(param_1 + 0x10) - (float)tmp_i3) * 0.5 + *(float *)(param_1 + 8);
    }
    else if (tmp_i3 == 2) {
      tmp_i3 = CG_Text_Width_Ext(tmp_i1,0x3e428f5c,0,0x1100f64);
      tmp_f2 = (*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10)) - (float)tmp_i3;
    }
    else {
      tmp_f2 = *(float *)(param_1 + 8) + 5.0;
    }
    CG_Text_Paint_Ext(tmp_f2,*(float *)(param_1 + 0xc) + 11.0,0x3e428f5c,0x3e428f5c,&local_2c,tmp_i1,0
                      ,0,0,0x1100f64);
  }
  return;
}

void CG_PanelButtonsRender_Button(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  uint32_t local_50;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  local_6c = 0x3dcccccd;
  local_68 = 0x3dcccccd;
  tmp_i1 = *(int *)(param_1 + 4);
  local_64 = 0x3dcccccd;
  local_60 = 0x3f000000;
  local_5c = 0x3e99999a;
  local_58 = 0x3e99999a;
  local_54 = 0x3e99999a;
  local_50 = 0x3ecccccd;
  local_4c = 0x3f19999a;
  local_48 = 0x3f19999a;
  local_44 = 0x3f19999a;
  local_40 = 0x3f800000;
  local_3c = 0x3f000000;
  local_38 = 0x3f000000;
  local_34 = 0x3f000000;
  local_30 = 0x3ecccccd;
  local_2c = 0x3f666666;
  local_28 = 0x3f666666;
  local_24 = 0x3f666666;
  local_20 = 0x3f800000;
  tmp_i2 = BG_CursorInRect(param_1 + 8);
  if (tmp_i2 == 0) {
    CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_5c);
    CG_DrawRect_FixedBorder
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&local_6c);
    if (tmp_i1 == 0) {
      return;
    }
    tmp_i2 = CG_Text_Width_Ext(tmp_i1,0x3e4ccccd,0,0x110afec);
    tmp_pu3 = &local_4c;
  }
  else {
    CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_3c);
    CG_DrawRect_FixedBorder
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&local_6c);
    if (tmp_i1 == 0) {
      return;
    }
    tmp_i2 = CG_Text_Width_Ext(tmp_i1,0x3e4ccccd,0,0x110afec);
    tmp_pu3 = &local_2c;
  }
  CG_Text_Paint_Ext(((*(float *)(param_1 + 0x10) + 2.0) - (float)tmp_i2) * 0.5 +
                    *(float *)(param_1 + 8),*(float *)(param_1 + 0xc) + 11.0,0x3e428f5c,0x3e428f5c,
                    tmp_pu3,tmp_i1,0,0,0,0x110afec);
  return;
}

void CG_MapVote_VoteButton_Draw(int param_1)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  char *tmp_pc3;
  uint32_t local_7c;
  uint32_t local_78;
  uint32_t local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  uint32_t local_50;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x48d39;
  local_7c = 0x3f19999a;
  local_78 = 0x3f19999a;
  local_74 = 0x3f19999a;
  local_70 = 0x3f800000;
  if ((g_unk_01047b00 != 0) && (GHIDRA_FIELD(cgs, 33701076, 4) == 0)) {
    if ((*(byte *)(g_unk_01047b00 + 0x95) & 0x40) == 0) {
      tmp_pc3 = "^3VOTE";
    }
    else {
      tmp_pc3 = "^1RE-VOTE";
      CG_Text_Paint_Ext(*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10) + 10.0,
                        *(float *)(param_1 + 0x14) * 0.25 * 3.0 + *(float *)(param_1 + 0xc),
                        0x3e4ccccd,0x3e4ccccd,&local_7c,GHIDRA_FIELD(cgs, 33701080, 4) * 0x80 + 0x311172c,0,0,0,
                        0x110afec);
    }
    local_6c = 0x3dcccccd;
    local_68 = 0x3dcccccd;
    local_64 = 0x3dcccccd;
    local_60 = 0x3f000000;
    local_5c = 0x3e99999a;
    local_58 = 0x3e99999a;
    local_54 = 0x3e99999a;
    local_50 = 0x3ecccccd;
    local_4c = 0x3f19999a;
    local_48 = 0x3f19999a;
    local_44 = 0x3f19999a;
    local_40 = 0x3f800000;
    local_3c = 0x3f000000;
    local_38 = 0x3f000000;
    local_34 = 0x3f000000;
    local_30 = 0x3ecccccd;
    local_2c = 0x3f666666;
    local_28 = 0x3f666666;
    local_24 = 0x3f666666;
    local_20 = 0x3f800000;
    tmp_i1 = BG_CursorInRect(param_1 + 8);
    if (tmp_i1 == 0) {
      CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                  *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_5c);
      CG_DrawRect_FixedBorder
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&local_6c);
      tmp_i1 = CG_Text_Width_Ext(tmp_pc3,0x3e4ccccd,0,0x110afec);
      tmp_pu2 = &local_4c;
    }
    else {
      CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                  *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_3c);
      CG_DrawRect_FixedBorder
                (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&local_6c);
      tmp_i1 = CG_Text_Width_Ext(tmp_pc3,0x3e4ccccd,0,0x110afec);
      tmp_pu2 = &local_2c;
    }
    CG_Text_Paint_Ext(((*(float *)(param_1 + 0x10) + 2.0) - (float)tmp_i1) * 0.5 +
                      *(float *)(param_1 + 8),*(float *)(param_1 + 0xc) + 11.0,0x3e428f5c,0x3e428f5c
                      ,tmp_pu2,tmp_pc3,0,0,0,0x110afec);
  }
  return;
}

void CG_ChatPanel_Setup(void)
{
  BG_PanelButtonsSetup(chatPanelButtons);
  BG_PanelButtonsSetup(teamDebriefPanelButtons);
  BG_PanelButtonsSetup(debriefPanelButtons);
  BG_PanelButtonsSetup(mapVoteButtons);
  return;
}

void CG_MapVote_SetSelectedMap(int param_1)
{
  if (GHIDRA_FIELD(cgs, 33701068, 4) != param_1) {
    GHIDRA_FIELD(cgs, 33701068, 4) = param_1;
  }
  return;
}

void CG_Debrieing_SetSelectedClient(int param_1)
{
  if (((-1 < param_1) && (param_1 < (int)GHIDRA_FIELD(cgs, 27400, 4))) && (param_1 != GHIDRA_FIELD(cgs, 33686236, 4))) {
    GHIDRA_FIELD(cgs, 33686236, 4) = param_1;
    GHIDRA_FIELD(cgs, 33686256, 4) = 0;
    GHIDRA_FIELD(cgs, 33701692, 4) = 0;
  }
  return;
}

int CG_TeamDebriefing_CalcXP(int param_1,int param_2,int param_3)
{
  uint tmp_u1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  bool tmp_b6;
  
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 4) {
    tmp_pu3 = cgs;
    if ((int)GHIDRA_FIELD(cgs, 33571584, 4) < 1) {
      tmp_i2 = 0;
    }
    else {
      tmp_u1 = param_3 + 1;
      tmp_b6 = param_3 == -1;
      tmp_i4 = 0;
      tmp_i2 = 0;
      do {
        if ((param_2 == tmp_i4) || (param_2 == -1)) {
          if (tmp_u1 < 2) {
            if (param_1 == 1) {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf33e84));
            }
            else {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf33f9c));
            }
            tmp_i2 = tmp_i2 + tmp_i5;
          }
          if ((tmp_u1 & 0xfffffffd) == 0) {
            if (param_1 == 1) {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf33eac));
            }
            else {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf33fc4));
            }
            tmp_i2 = tmp_i2 + tmp_i5;
          }
          if (param_3 == 2 || tmp_b6) {
            if (param_1 == 1) {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf33ed4));
            }
            else {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf33fec));
            }
            tmp_i2 = tmp_i2 + tmp_i5;
          }
          if ((tmp_u1 & 0xfffffffb) == 0) {
            if (param_1 == 1) {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf33efc));
            }
            else {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf34014));
            }
            tmp_i2 = tmp_i2 + tmp_i5;
          }
          if (param_3 == 4 || tmp_b6) {
            if (param_1 == 1) {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf33f24));
            }
            else {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf3403c));
            }
            tmp_i2 = tmp_i2 + tmp_i5;
          }
          if (param_3 == 5 || tmp_b6) {
            if (param_1 == 1) {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf33f4c));
            }
            else {
              tmp_i5 = *(int *)(cgs + (int)(tmp_pu3 + 0xf34064));
            }
            tmp_i2 = tmp_i2 + tmp_i5;
          }
          if (param_3 == 6 || tmp_b6) {
            if (param_1 == 1) {
              tmp_i2 = tmp_i2 + *(int *)(cgs + (int)(tmp_pu3 + 0xf33f74));
            }
            else {
              tmp_i2 = tmp_i2 + *(int *)(cgs + (int)(tmp_pu3 + 0xf3408c));
            }
          }
        }
        tmp_i4 = tmp_i4 + 1;
        tmp_pu3 = tmp_pu3 + 4;
      } while (tmp_i4 != GHIDRA_FIELD(cgs, 33571584, 4));
    }
  }
  else if ((GHIDRA_FIELD(cg_gameType, 12, 4) - 6 < 3) || (tmp_i2 = 0, GHIDRA_FIELD(cg_gameType, 12, 4) - 2 < 2)) {
    tmp_b6 = param_3 == -1;
    if (param_1 == 1) {
      if ((param_3 == 0) || (tmp_i2 = 0, tmp_b6)) {
        tmp_i2 = GHIDRA_FIELD(cgs, 33701092, 4);
      }
      if ((param_3 == 1) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701132, 4);
      }
      if ((param_3 == 2) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701172, 4);
      }
      if ((param_3 == 3) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701212, 4);
      }
      if ((param_3 == 4) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701252, 4);
      }
      if ((param_3 == 5) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701292, 4);
      }
      if ((param_3 == 6) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701332, 4);
      }
    }
    else {
      if ((param_3 == 0) || (tmp_i2 = 0, tmp_b6)) {
        tmp_i2 = GHIDRA_FIELD(cgs, 33701372, 4);
      }
      if ((param_3 == 1) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701412, 4);
      }
      if ((param_3 == 2) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701452, 4);
      }
      if ((param_3 == 3) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701492, 4);
      }
      if ((param_3 == 4) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701532, 4);
      }
      if ((param_3 == 5) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701572, 4);
      }
      if ((param_3 == 6) || (tmp_b6)) {
        tmp_i2 = tmp_i2 + GHIDRA_FIELD(cgs, 33701612, 4);
      }
    }
  }
  return tmp_i2;
}

void CG_TeamDebriefingTeamSkillXP_Draw(int param_1)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  uint32_t tmp_u3;
  
  if (*(int *)(param_1 + 0x1c) == 7) {
    tmp_u3 = CG_TeamDebriefing_CalcXP_constprop_18();
  }
  else {
    tmp_u3 = CG_TeamDebriefing_CalcXP
                      (2 - (uint)(*(int *)(param_1 + 0x18) == 0),GHIDRA_FIELD(cgs, 33701656, 4) + -1,
                       *(int *)(param_1 + 0x1c));
  }
  tmp_u1 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
  tmp_u3 = va("%i",tmp_u3);
  tmp_pu2 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu2,tmp_pu2[1],
                    tmp_pu2 + 2,tmp_u3,0,0,0,tmp_u1);
  return;
}

void CG_TeamDebriefingTeamXP_Draw(int param_1)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  
  if (*(int *)(param_1 + 0x18) == 0) {
    tmp_u2 = CG_TeamDebriefing_CalcXP_constprop_18();
    tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
    tmp_pc3 = "Axis";
  }
  else {
    tmp_u2 = CG_TeamDebriefing_CalcXP_constprop_18();
    tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
    tmp_pc3 = "Allies";
  }
  tmp_u2 = va("%s XP: %i",tmp_pc3,tmp_u2);
  tmp_pu1 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu1,tmp_pu1[1],
                    tmp_pu1 + 2,tmp_u2,0,0,0,tmp_u4);
  return;
}

void CG_PanelButtonsRender_Button_Ext(float *param_1,int param_2)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  uint32_t local_50;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  local_6c = 0x3dcccccd;
  local_68 = 0x3dcccccd;
  local_64 = 0x3dcccccd;
  local_60 = 0x3f000000;
  local_5c = 0x3e99999a;
  local_58 = 0x3e99999a;
  local_54 = 0x3e99999a;
  local_50 = 0x3ecccccd;
  local_4c = 0x3f19999a;
  local_48 = 0x3f19999a;
  local_44 = 0x3f19999a;
  local_40 = 0x3f800000;
  local_3c = 0x3f000000;
  local_38 = 0x3f000000;
  local_34 = 0x3f000000;
  local_30 = 0x3ecccccd;
  local_2c = 0x3f666666;
  local_28 = 0x3f666666;
  local_24 = 0x3f666666;
  local_20 = 0x3f800000;
  tmp_i1 = BG_CursorInRect(param_1);
  if (tmp_i1 == 0) {
    CG_FillRect(*param_1,param_1[1],param_1[2],param_1[3],&local_5c);
    CG_DrawRect_FixedBorder(*param_1,param_1[1],param_1[2],param_1[3],1,&local_6c);
    if (param_2 == 0) {
      return;
    }
    tmp_i1 = CG_Text_Width_Ext(param_2,0x3e4ccccd,0,0x110afec);
    tmp_pu2 = &local_4c;
  }
  else {
    CG_FillRect(*param_1,param_1[1],param_1[2],param_1[3],&local_3c);
    CG_DrawRect_FixedBorder(*param_1,param_1[1],param_1[2],param_1[3],1,&local_6c);
    if (param_2 == 0) {
      return;
    }
    tmp_i1 = CG_Text_Width_Ext(param_2,0x3e4ccccd,0,0x110afec);
    tmp_pu2 = &local_2c;
  }
  CG_Text_Paint_Ext(((param_1[2] + 2.0) - (float)tmp_i1) * 0.5 + *param_1,param_1[1] + 11.0,
                    0x3e428f5c,0x3e428f5c,tmp_pu2,param_2,0,0,0,0x110afec);
  return;
}

void CG_MapVote_MultiVoteButton_Draw(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  local_2c = 0x3f19999a;
  local_28 = 0x3f19999a;
  local_24 = 0x3f19999a;
  local_20 = 0x3f800000;
  if ((g_unk_01047b00 != 0) && (GHIDRA_FIELD(cgs, 33701076, 4) != 0)) {
    tmp_i2 = 4 - *(int *)(param_1 + 0x34);
    if (*(int *)(cgs + *(int *)(param_1 + 0x34) * 4 + 0x2023cd4) == -1) {
      tmp_u1 = va(&g_unk_00113183,tmp_i2);
    }
    else {
      tmp_u1 = va("^3%d: ^1RE-VOTE",tmp_i2);
    }
    if (*(int *)(cgs + *(int *)(param_1 + 0x34) * 4 + 0x2023cd4) != -1) {
      CG_Text_Paint_Ext(*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10) + 10.0,
                        *(float *)(param_1 + 0x14) * 0.25 * 3.0 + *(float *)(param_1 + 0xc),
                        0x3e4ccccd,0x3e4ccccd,&local_2c,
                        *(int *)(cgs + *(int *)(param_1 + 0x34) * 4 + 0x2023cd4) * 0x80 + 0x311172c,
                        0,0,0,0x110afec);
    }
    CG_PanelButtonsRender_Button_Ext(param_1 + 8,tmp_u1);
  }
  return;
}

void CG_PanelButtonsRender_Window_Ext
               (float *param_1,int param_2,int param_3,int param_4,uint32_t param_5,int param_6)

{
  float tmp_f1;
  int tmp_i2;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0x3f4ccccd;
  local_2c = 0x3f19999a;
  local_28 = 0x3f19999a;
  local_24 = 0x3f19999a;
  local_20 = 0x3f800000;
  CG_FillRect(*param_1,param_1[1],param_1[2],param_1[3],&local_3c);
  CG_DrawRect_FixedBorder(*param_1,param_1[1],param_1[2],param_1[3],1,&HUD_Border);
  CG_FillRect(*param_1 + 2.0,param_1[1] + 2.0,param_1[2] - 4.0,(float)param_4,&HUD_Background);
  if (param_2 != 0) {
    if (param_3 == 1) {
      tmp_i2 = CG_Text_Width_Ext(param_2,param_5,0,0x1100f64);
      tmp_f1 = (param_1[2] - (float)tmp_i2) * 0.5 + *param_1;
    }
    else if (param_3 == 2) {
      tmp_i2 = CG_Text_Width_Ext(param_2,param_5,0,0x1100f64);
      tmp_f1 = (*param_1 + param_1[2]) - (float)tmp_i2;
    }
    else {
      tmp_f1 = *param_1 + 5.0;
    }
    CG_Text_Paint_Ext(tmp_f1,(float)param_6 + param_1[1],param_5,param_5,&local_2c,param_2,0,0,0,
                      0x1100f64);
  }
  return;
}

char * CG_Debreifing2_WinStringForTeam(int param_1)
{
  if (param_1 == 1) {
    return "AXIS WIN!";
  }
  if (param_1 == 2) {
    return "ALLIES WIN!";
  }
  return "IT\'S A TIE!";
}

void CG_Debreifing2_Maps_Draw(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  char *tmp_pc4;
  float local_60;
  int local_5c;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x4be99;
  local_3c = 0x3f19999a;
  local_38 = 0x3f19999a;
  local_34 = 0x3f19999a;
  local_30 = 0x3f800000;
  local_2c = 0x3e99999a;
  local_28 = 0x3e99999a;
  local_24 = 0x3e99999a;
  local_20 = 0x3ecccccd;
  if ((GHIDRA_FIELD(cg_gameType, 12, 4) == 4) && (GHIDRA_FIELD(cgs, 33526364, 4) != 0)) {
    if (GHIDRA_FIELD(cgs, 33701656, 4) == 0) {
      CG_FillRect(*(float *)(param_1 + 8) + 2.0,*(float *)(param_1 + 0xc) + 2.0,
                  *(float *)(param_1 + 0x10) - 4.0,0x41400000,&local_2c);
    }
    tmp_u2 = va("Campaign: %s",0x30e98c0);
    CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 4.0,*(float *)(param_1 + 0xc) + 11.0,0x3e428f5c,
                      0x3e428f5c,&local_3c,tmp_u2,0,0,0,0x110afec);
    local_60 = *(float *)(param_1 + 0xc);
    if (0 < (int)GHIDRA_FIELD(cgs, 33571584, 4)) {
      local_5c = 0x30eac10;
      tmp_i3 = 0;
      do {
        local_60 = local_60 + 14.0;
        tmp_i1 = tmp_i3 + 1;
        if (GHIDRA_FIELD(cgs, 33701656, 4) == tmp_i1) {
          CG_FillRect(*(float *)(param_1 + 8) + 2.0,local_60 + 2.0,*(float *)(param_1 + 0x10) - 4.0,
                      0x41400000,&local_2c);
        }
        tmp_u2 = va("%i. %s",tmp_i1,local_5c);
        CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 8.0,local_60 + 11.0,0x3e428f5c,0x3e428f5c,
                          &local_3c,tmp_u2,0,0,0,0x110afec);
        if (tmp_i3 <= (int)GHIDRA_FIELD(cgs, 33525616, 4)) {
          tmp_i3 = CG_Debriefing_FindWinningTeamForPos(tmp_i1);
          if (tmp_i3 == 1) {
            tmp_pc4 = "AXIS WIN!";
          }
          else if (tmp_i3 == 2) {
            tmp_pc4 = "ALLIES WIN!";
          }
          else {
            tmp_pc4 = "IT\'S A TIE!";
          }
          tmp_i3 = CG_Text_Width_Ext(tmp_pc4,0x3e4ccccd,0,0x110afec);
          CG_Text_Paint_Ext(((*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10)) - (float)tmp_i3)
                            - 8.0,local_60 + 11.0,0x3e428f5c,0x3e428f5c,&local_3c,tmp_pc4,0,0,0,
                            0x110afec);
        }
        local_5c = local_5c + 0x1088;
        tmp_i3 = tmp_i1;
      } while (tmp_i1 < (int)GHIDRA_FIELD(cgs, 33571584, 4));
    }
  }
  return;
}

void CG_Debreifing2_MissionTitle_Draw(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  long tmp_l5;
  long tmp_l6;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x4c229;
  local_4c = 0x3f19999a;
  local_48 = 0x3f19999a;
  local_44 = 0x3f19999a;
  local_40 = 0x3f800000;
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 3) {
    tmp_u3 = CG_ConfigString(0xd);
    tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,"d");
    tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
    tmp_u3 = CG_ConfigString(0xe);
    tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,"w");
    tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
    if (GHIDRA_FIELD(cgs, 33525344, 4) == 0) {
      if (tmp_l5 == 0) {
        tmp_pc4 = "ALLIES SUCCESSFULLY BEAT THE CLOCK!";
        if (tmp_l6 == 0) {
          tmp_pc4 = "ALLIES COULDN\'T BEAT THE CLOCK!";
        }
      }
      else {
        tmp_pc4 = "AXIS SUCCESSFULLY BEAT THE CLOCK!";
        if (tmp_l5 == tmp_l6) {
          tmp_pc4 = "AXIS COULDN\'T BEAT THE CLOCK!";
        }
      }
    }
    else {
      tmp_i1 = (int)ROUND(((float)GHIDRA_FIELD(cgs, 33525348, 4) * 60.0 * 1000.0) / 1000.0);
      tmp_i2 = tmp_i1 % 0x3c;
      tmp_u3 = va("%i:%i%i",tmp_i1 / 0x3c,tmp_i2 / 10,tmp_i2 % 10);
      tmp_pc4 = (char *)va("Clock is now set to %s!",tmp_u3);
    }
    CG_PanelButtonsRender_Window_Ext(param_1 + 8,tmp_pc4,0,0x12,0x3e800000,0x10);
  }
  else if (GHIDRA_FIELD(cg_gameType, 12, 4) == 4) {
    tmp_u3 = CG_ConfigString(0xe);
    tmp_pc4 = (char *)Info_ValueForKey(tmp_u3,"w");
    tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
    if (tmp_l5 == -1) {
      tmp_pc4 = "IT\'S A TIE!";
    }
    else {
      tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
      if (tmp_l5 == 0) {
        tmp_pc4 = "AXIS WIN!";
      }
      else {
        tmp_pc4 = "ALLIES WIN!";
      }
    }
    CG_PanelButtonsRender_Window_Ext(param_1 + 8,tmp_pc4,0,0x12,0x3e800000,0x10);
    tmp_i2 = CG_Debriefing_FindWinningTeamForPos(0);
    if (tmp_i2 == 1) {
      tmp_pc4 = "AXIS WIN!";
    }
    else if (tmp_i2 == 2) {
      tmp_pc4 = "ALLIES WIN!";
    }
    else {
      tmp_pc4 = "IT\'S A TIE!";
    }
    tmp_u3 = va("CAMPAIGN STATUS: %s",tmp_pc4);
    tmp_i2 = CG_Text_Width_Ext(tmp_u3,0x3e800000,0,0x1100f64);
    CG_Text_Paint_Ext((*(float *)(param_1 + 0x10) - (float)tmp_i2) * 0.5 + *(float *)(param_1 + 8),
                      *(float *)(param_1 + 0xc) + 16.0,0x3e800000,0x3e800000,&local_4c,tmp_u3,0,0,0,
                      0x1100f64);
  }
  else {
    tmp_i2 = CG_Debriefing_FindWinningTeamForPos(0);
    if (tmp_i2 == 1) {
      tmp_pc4 = "AXIS WIN!";
    }
    else if (tmp_i2 == 2) {
      tmp_pc4 = "ALLIES WIN!";
    }
    else {
      tmp_pc4 = "IT\'S A TIE!";
    }
    local_3c = 0;
    local_38 = 0;
    local_34 = 0;
    local_30 = 0x3f4ccccd;
    local_2c = 0x3f19999a;
    local_28 = 0x3f19999a;
    local_24 = 0x3f19999a;
    local_20 = 0x3f800000;
    CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_3c);
    CG_DrawRect_FixedBorder
              (*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
               *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),1,&HUD_Border);
    CG_FillRect(*(float *)(param_1 + 8) + 2.0,*(float *)(param_1 + 0xc) + 2.0,
                *(float *)(param_1 + 0x10) - 4.0,0x41900000,&HUD_Background);
    CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 5.0,*(float *)(param_1 + 0xc) + 16.0,0x3e800000,
                      0x3e800000,&local_2c,tmp_pc4,0,0,0,0x1100f64);
  }
  tmp_i2 = 0;
  if (g_unk_010906e0 - GHIDRA_FIELD(cgs, 28484, 4) < 60000) {
    tmp_i2 = 0x3c - (g_unk_010906e0 - GHIDRA_FIELD(cgs, 28484, 4)) / 1000;
  }
  tmp_u3 = va("%i SECS TO NEXT MAP",tmp_i2);
  tmp_i2 = CG_Text_Width_Ext(tmp_u3,0x3e800000,0,0x1100f64);
  CG_Text_Paint_Ext(((*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10)) - (float)tmp_i2) - 4.0,
                    *(float *)(param_1 + 0xc) + 16.0,0x3e800000,0x3e800000,&local_4c,tmp_u3,0,0,0,
                    0x1100f64);
  return;
}

void CG_Debreifing2_Mission_Draw(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  uint32_t tmp_u7;
  int tmp_i8;
  char *tmp_pc9;
  int tmp_i10;
  int local_48;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x4cd69;
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 4) {
    if (GHIDRA_FIELD(cgs, 33526364, 4) != 0) {
      if (((float)GHIDRA_FIELD(cgs, 33571592, 4) == 0.0) || ((float)GHIDRA_FIELD(cgs, 33571600, 4) == 0.0)) goto LAB_0004d0ec;
      tmp_u7 = trap_R_RegisterShaderNoMip("gfx/loading/camp_map");
      CG_DrawPicST(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                   *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),
                   (float)GHIDRA_FIELD(cgs, 33571592, 4) * 0.0009765625,(float)GHIDRA_FIELD(cgs, 33571596, 4) * 0.0009765625,
                   (float)GHIDRA_FIELD(cgs, 33571600, 4) * 0.0009765625,(float)GHIDRA_FIELD(cgs, 33571604, 4) * 0.0009765625,
                   tmp_u7);
      local_48 = GHIDRA_FIELD(cgs, 33571584, 4);
      if (-1 < GHIDRA_FIELD(cgs, 33571584, 4) + -1) {
        tmp_i8 = (GHIDRA_FIELD(cgs, 33571584, 4) + -1) * 0x1088 + 0x30eac10;
        do {
          local_2c = 0;
          local_28 = 0;
          local_24 = 0;
          local_20 = 0x3ecccccd;
          tmp_f2 = ((*(float *)(tmp_i8 + 0x80) - (float)GHIDRA_FIELD(cgs, 33571592, 4)) / 650.0) *
                  *(float *)(param_1 + 0x10) + *(float *)(param_1 + 8);
          tmp_f3 = *(float *)(param_1 + 0xc) +
                  ((*(float *)(tmp_i8 + 0x84) - (float)GHIDRA_FIELD(cgs, 33571596, 4)) / 650.0) *
                  *(float *)(param_1 + 0x14);
          tmp_i10 = CG_Text_Width_Ext(tmp_i8,0x3e4ccccd,0,0x110afec);
          tmp_f4 = (float)tmp_i10;
          tmp_f1 = tmp_f2 + 14.0 + tmp_f4;
          if (*(float *)(param_1 + 8) + *(float *)(param_1 + 0x10) < tmp_f1) {
            tmp_f5 = (tmp_f2 - tmp_f4) - 17.0;
            CG_FillRect(tmp_f5 + 1.0,(tmp_f3 - 6.0) + 1.0,tmp_f4 + 17.0,0x41400000,&local_2c);
            CG_FillRect(tmp_f5,tmp_f3 - 6.0,tmp_f4 + 17.0,0x41400000,&colorBlack);
          }
          else {
            CG_FillRect(tmp_f2 + 1.0,(tmp_f3 - 6.0) + 1.0,tmp_f4 + 14.0,0x41400000,&local_2c);
            CG_FillRect(tmp_f2,tmp_f3 - 6.0,tmp_f4 + 14.0,0x41400000,&colorBlack);
          }
          tmp_i10 = CG_Debriefing_FindWinningTeamForPos(local_48);
          tmp_pc9 = "gfx/loading/pin_axis";
          if (tmp_i10 != 1) {
            if (tmp_i10 == 2) {
              tmp_pc9 = "gfx/loading/pin_allied";
            }
            else {
              tmp_pc9 = "gfx/loading/pin_neutral";
            }
          }
          tmp_u7 = trap_R_RegisterShaderNoMip(tmp_pc9);
          CG_DrawPic(tmp_f2 - 12.0,tmp_f3 - 12.0,0x41c00000,0x41c00000,tmp_u7);
          if (tmp_f1 <= *(float *)(param_1 + 8) + *(float *)(param_1 + 0x10)) {
            CG_Text_Paint_Ext(tmp_f2 + 12.0,tmp_f3 + 3.0,0x3e4ccccd,0x3e4ccccd,&colorWhite,tmp_i8,0,0,0
                              ,0x110afec);
          }
          else {
            CG_Text_Paint_Ext((tmp_f2 - tmp_f4) - 15.0,tmp_f3 + 3.0,0x3e4ccccd,0x3e4ccccd,&colorWhite,
                              tmp_i8,0,0,0,0x110afec);
          }
          tmp_i8 = tmp_i8 + -0x1088;
          local_48 = local_48 + -1;
        } while (local_48 != 0);
      }
      if (GHIDRA_FIELD(cgs, 33701656, 4) != 0) {
        tmp_i8 = (GHIDRA_FIELD(cgs, 33701656, 4) + -1) * 0x1088;
        tmp_f5 = *(float *)(cgs + tmp_i8 + 0x1ffae30) - (float)GHIDRA_FIELD(cgs, 33571592, 4);
        tmp_f1 = *(float *)(param_1 + 0x10);
        tmp_f4 = *(float *)(param_1 + 8);
        tmp_f6 = *(float *)(cgs + tmp_i8 + 0x1ffae34) - (float)GHIDRA_FIELD(cgs, 33571596, 4);
        tmp_f2 = *(float *)(param_1 + 0x14);
        tmp_f3 = *(float *)(param_1 + 0xc);
        tmp_i8 = CG_Debriefing_FindWinningTeamForPos(GHIDRA_FIELD(cgs, 33701656, 4));
        if (tmp_i8 == 1) {
          tmp_pc9 = "gfx/loading/pin_axis";
        }
        else {
          if (tmp_i8 != 2) {
            return;
          }
          tmp_pc9 = "gfx/loading/pin_allied";
        }
        tmp_u7 = trap_R_RegisterShaderNoMip(tmp_pc9);
        CG_DrawPic(((tmp_f5 / 650.0) * tmp_f1 + tmp_f4) - 12.0,((tmp_f6 / 650.0) * tmp_f2 + tmp_f3) - 12.0
                   ,0x41c00000,0x41c00000,tmp_u7);
      }
    }
  }
  else if (GHIDRA_FIELD(cgs, 33571608, 4) != 0) {
    if (((float)GHIDRA_FIELD(cgs, 33575836, 4) == 0.0) || ((float)GHIDRA_FIELD(cgs, 33575840, 4) == 0.0)) {
LAB_0004d0ec:
      tmp_u7 = trap_R_RegisterShaderNoMip("menu/art/unknownmap");
      CG_DrawPic(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),tmp_u7);
      return;
    }
    local_20 = 0x3ecccccd;
    local_2c = 0;
    local_28 = 0;
    local_24 = 0;
    tmp_f1 = (float)GHIDRA_FIELD(cgs, 33575836, 4) - 325.0;
    if (tmp_f1 < 0.0) {
      tmp_f4 = 650.0;
      tmp_f1 = 0.0;
    }
    else {
      tmp_f4 = tmp_f1 + 650.0;
      if (1024.0 < tmp_f4) {
        tmp_f1 = 374.0;
        tmp_f4 = 1024.0;
      }
    }
    tmp_f2 = (float)GHIDRA_FIELD(cgs, 33575840, 4) - 325.0;
    if (tmp_f2 < 0.0) {
      tmp_f3 = 650.0;
      tmp_f2 = 0.0;
    }
    else {
      tmp_f3 = tmp_f2 + 650.0;
      if (1024.0 < tmp_f3) {
        tmp_f2 = 374.0;
        tmp_f3 = 1024.0;
      }
    }
    tmp_u7 = trap_R_RegisterShaderNoMip("gfx/loading/camp_map");
    CG_DrawPicST(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
                 *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),
                 tmp_f1 * 0.0009765625,tmp_f2 * 0.0009765625,tmp_f4 * 0.0009765625,tmp_f3 * 0.0009765625
                 ,tmp_u7);
    tmp_f1 = (((float)GHIDRA_FIELD(cgs, 33575836, 4) - tmp_f1) / 650.0) * *(float *)(param_1 + 0x10) +
            *(float *)(param_1 + 8);
    tmp_f4 = (((float)GHIDRA_FIELD(cgs, 33575840, 4) - tmp_f2) / 650.0) * *(float *)(param_1 + 0x14) +
            *(float *)(param_1 + 0xc);
    tmp_i8 = CG_Text_Width_Ext(0x30f517c,0x3e4ccccd,0,0x110afec);
    tmp_f2 = (float)tmp_i8;
    tmp_f3 = tmp_f1 + 14.0 + tmp_f2;
    if (tmp_f3 <= *(float *)(param_1 + 8) + *(float *)(param_1 + 0x10)) {
      CG_FillRect(tmp_f1 + 1.0,(tmp_f4 - 6.0) + 1.0,tmp_f2 + 14.0,0x41400000,&local_2c);
      CG_FillRect(tmp_f1,tmp_f4 - 6.0,tmp_f2 + 14.0,0x41400000,&colorBlack);
    }
    else {
      tmp_f5 = (tmp_f1 - tmp_f2) - 17.0;
      CG_FillRect(tmp_f5 + 1.0,(tmp_f4 - 6.0) + 1.0,tmp_f2 + 17.0,0x41400000,&local_2c);
      CG_FillRect(tmp_f5,tmp_f4 - 6.0,tmp_f2 + 17.0,0x41400000,&colorBlack);
    }
    if (GHIDRA_FIELD(cg_gameType, 12, 4) == 4) {
      tmp_i8 = CG_Debriefing_FindWinningTeamForPos(GHIDRA_FIELD(cgs, 33701656, 4));
    }
    else {
      tmp_i8 = CG_Debriefing_FindWinningTeamForPos(0);
    }
    if (tmp_i8 == 1) {
      tmp_pc9 = "gfx/loading/pin_axis";
    }
    else if (tmp_i8 == 2) {
      tmp_pc9 = "gfx/loading/pin_allied";
    }
    else {
      tmp_pc9 = "gfx/loading/pin_neutral";
    }
    tmp_u7 = trap_R_RegisterShaderNoMip(tmp_pc9);
    CG_DrawPic(tmp_f1 - 12.0,tmp_f4 - 12.0,0x41c00000,0x41c00000,tmp_u7);
    if (tmp_f3 <= *(float *)(param_1 + 8) + *(float *)(param_1 + 0x10)) {
      CG_Text_Paint_Ext(tmp_f1 + 12.0,tmp_f4 + 3.0,0x3e4ccccd,0x3e4ccccd,&colorWhite,0x30f517c,0,0,0,
                        0x110afec);
    }
    else {
      CG_Text_Paint_Ext((tmp_f1 - tmp_f2) - 15.0,tmp_f4 + 3.0,0x3e4ccccd,0x3e4ccccd,&colorWhite,
                        0x30f517c,0,0,0,0x110afec);
    }
  }
  return;
}

void CG_Coronas_part_4(void)
{
  int tmp_i1;
  float *pfVar2;
  int tmp_i3;
  long double tmp_l4;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [8];
  float local_4c;
  uint32_t uStack_14;
  
  uStack_14 = 0x4e5c9;
  if (0 < g_unk_010abd74) {
    pfVar2 = (float *)(cgs + 0x2019190);
    tmp_i3 = 0;
    do {
      while (tmp_i1 = trap_R_inPVS(g_unk_010afbcc + 0x18,pfVar2), tmp_i1 == 0) {
LAB_0004e600:
        tmp_i3 = tmp_i3 + 1;
        pfVar2 = pfVar2 + 7;
        if (g_unk_010abd74 <= tmp_i3) {
          return;
        }
      }
      local_60 = *(float *)(g_unk_010afbcc + 0x18) - *pfVar2;
      local_5c = *(float *)(g_unk_010afbcc + 0x1c) - pfVar2[1];
      local_58 = *(float *)(g_unk_010afbcc + 0x20) - pfVar2[2];
      tmp_l4 = (long double)VectorNormalize2(&local_60,&local_60);
      if (local_58 * *(float *)(g_unk_010afbcc + 0x2c) +
          local_5c * *(float *)(g_unk_010afbcc + 0x28) + local_60 * *(float *)(g_unk_010afbcc + 0x24) <
          -0.6) {
        if ((GHIDRA_FIELD(cg_coronas, 12, 4) != 2) && ((long double)(int)GHIDRA_FIELD(cg_coronafardist, 12, 4) < tmp_l4))
        goto LAB_0004e600;
      }
      else if (GHIDRA_FIELD(cg_coronas, 12, 4) != 2) goto LAB_0004e600;
      CG_Trace(local_54,g_unk_010afbcc + 0x18,0,0,pfVar2,0xffffffff,0x2000001);
      tmp_i1 = tmp_i3 + 1;
      trap_R_AddCoronaToScene(pfVar2,pfVar2[3],pfVar2[4],pfVar2[5],pfVar2[-1],tmp_i3,local_4c == 1.0)
      ;
      pfVar2 = pfVar2 + 7;
      tmp_i3 = tmp_i1;
    } while (tmp_i1 < g_unk_010abd74);
  }
  return;
}

char * CG_PickupItemText(int param_1)
{
  byte *tmp_pb1;
  int tmp_i2;
  char *tmp_pc3;
  
  tmp_i2 = param_1 * 0x38;
  if (*(int *)(bg_itemlist + tmp_i2 + 0x24) == 3) {
    if (0 < *(int *)(bg_itemlist + tmp_i2 + 0x20)) {
      if (*(int *)(bg_itemlist + tmp_i2 + 0x10) == 0) {
        tmp_pc3 = (char *)va("%i %s",*(int *)(bg_itemlist + tmp_i2 + 0x20),
                            *(uint32_t *)(bg_itemlist + tmp_i2 + 0x1c));
        return tmp_pc3;
      }
      tmp_pc3 = (char *)va(&g_unk_00113566,*(uint32_t *)(bg_itemlist + tmp_i2 + 0x1c));
      return tmp_pc3;
    }
  }
  else if (*(int *)(bg_itemlist + tmp_i2 + 0x24) == 5) {
    return "an Objective";
  }
  tmp_pb1 = *(byte **)(bg_itemlist + param_1 * 0x38 + 0x1c);
  if ((*tmp_pb1 & 0xdf) != 0x41) {
    tmp_pc3 = (char *)va(&g_unk_00113566,tmp_pb1);
    return tmp_pc3;
  }
  tmp_pc3 = (char *)va("an %s",tmp_pb1);
  return tmp_pc3;
}

char * CG_PickupItemTextShort(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  
  tmp_i1 = param_1 * 0x38;
  if (*(int *)(bg_itemlist + tmp_i1 + 0x24) == 3) {
    if (0 < *(int *)(bg_itemlist + tmp_i1 + 0x20)) {
      tmp_u2 = *(uint32_t *)(bg_itemlist + tmp_i1 + 0x1c);
      if (*(int *)(bg_itemlist + tmp_i1 + 0x10) == 0) {
        tmp_pc3 = (char *)va("%i %s",*(int *)(bg_itemlist + tmp_i1 + 0x20),tmp_u2);
        return tmp_pc3;
      }
      goto LAB_00055e23;
    }
  }
  else if (*(int *)(bg_itemlist + tmp_i1 + 0x24) == 5) {
    return "Objective";
  }
  tmp_u2 = *(uint32_t *)(bg_itemlist + param_1 * 0x38 + 0x1c);
LAB_00055e23:
  tmp_pc3 = (char *)va("%s",tmp_u2);
  return tmp_pc3;
}

void CG_CenterPrint(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  bool tmp_b1;
  char tmp_c2;
  uint tmp_u3;
  uint tmp_u4;
  uint8_t *tmp_pu5;
  char *tmp_pc6;
  uint *tmp_pu7;
  uint *tmp_pu8;
  uint8_t *tmp_pu9;
  
  Q_strncpyz(&g_unk_01092d0c,param_1,0x400);
  tmp_pu8 = (uint *)&g_unk_01092d0c;
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
  tmp_pu9 = (uint8_t *)((int)tmp_pu8 + (-0x1092d0f - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)));
  if (0 < (int)tmp_pu9) {
    tmp_pu5 = (uint8_t *)0x0;
    tmp_b1 = false;
    do {
      while ((tmp_pu5 != (uint8_t *)(((int)tmp_pu5 / 0x24) * 0x24) || ((int)tmp_pu5 < 1))) {
        if (((&g_unk_01092d0c)[(int)tmp_pu5] != ' ') || (!tmp_b1)) goto LAB_000560a9;
        (&g_unk_01092d0c)[(int)tmp_pu5] = 10;
LAB_000560f0:
        tmp_b1 = false;
        tmp_pu5 = tmp_pu5 + 1;
        if (tmp_pu9 == tmp_pu5) goto LAB_00056100;
      }
      if ((&g_unk_01092d0c)[(int)tmp_pu5] == ' ') {
        (&g_unk_01092d0c)[(int)tmp_pu5] = 10;
        goto LAB_000560f0;
      }
      tmp_b1 = true;
LAB_000560a9:
      tmp_pu5 = tmp_pu5 + 1;
    } while (tmp_pu9 != tmp_pu5);
  }
LAB_00056100:
  tmp_pc6 = &g_unk_01092d0c;
  g_unk_01092d00 = g_unk_010906e0;
  g_unk_01092d08 = param_2;
  g_unk_01092d04 = param_3;
  g_unk_0109310c = 1;
  tmp_c2 = g_unk_01092d0c;
  do {
    if (tmp_c2 == '\0') {
      return;
    }
    while (tmp_c2 == '\n') {
      g_unk_0109310c = g_unk_0109310c + 1;
      tmp_pc6 = tmp_pc6 + 1;
      tmp_c2 = *tmp_pc6;
      if (tmp_c2 == '\0') {
        g_unk_01092d00 = g_unk_010906e0;
        return;
      }
    }
    tmp_pc6 = tmp_pc6 + 1;
    tmp_c2 = *tmp_pc6;
  } while( true );
}

void CG_PrintAnnouncement(uint32_t param_1,uint32_t param_2,uint32_t param_3,int param_4)
{
  char tmp_c1;
  bool tmp_b2;
  uint tmp_u3;
  uint tmp_u4;
  uint8_t *tmp_pu5;
  char *tmp_pc6;
  uint *tmp_pu7;
  uint *tmp_pu8;
  uint8_t *tmp_pu9;
  
  if ((-1 < param_4) || (g_unk_01093110 == 0)) {
    Q_strncpyz(&g_unk_01093124,param_1,0x400);
    g_unk_01093120 = param_4;
    tmp_pu8 = (uint *)&g_unk_01093124;
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
    tmp_pu9 = (uint8_t *)((int)tmp_pu8 + (-0x1093127 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)));
    if (0 < (int)tmp_pu9) {
      tmp_pu5 = (uint8_t *)0x0;
      tmp_b2 = false;
      do {
        while ((tmp_pu5 != (uint8_t *)(((int)tmp_pu5 / 0x24) * 0x24) || ((int)tmp_pu5 < 1))) {
          if (((&g_unk_01092d0c)[(int)tmp_pu5] == ' ') && (tmp_b2)) {
            (&g_unk_01092d0c)[(int)tmp_pu5] = 10;
            goto LAB_00056290;
          }
LAB_00056241:
          tmp_pu5 = tmp_pu5 + 1;
          if (tmp_pu9 == tmp_pu5) goto LAB_000562a0;
        }
        if ((&g_unk_01092d0c)[(int)tmp_pu5] != ' ') {
          tmp_b2 = true;
          goto LAB_00056241;
        }
        (&g_unk_01092d0c)[(int)tmp_pu5] = 10;
LAB_00056290:
        tmp_b2 = false;
        tmp_pu5 = tmp_pu5 + 1;
      } while (tmp_pu9 != tmp_pu5);
    }
LAB_000562a0:
    tmp_pc6 = &g_unk_01093124;
    g_unk_01093110 = g_unk_010906e0 + 2000;
    g_unk_01093118 = param_2;
    g_unk_01093114 = param_3;
    g_unk_0109311c = 1;
    tmp_c1 = g_unk_01093124;
    while (tmp_c1 != '\0') {
      if (tmp_c1 == '\n') {
        g_unk_0109310c = g_unk_0109310c + 1;
      }
      tmp_pc6 = tmp_pc6 + 1;
      tmp_c1 = *tmp_pc6;
    }
  }
  return;
}

void CG_ScanForCrosshairMine(int param_1)
{
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  uint8_t local_44 [12];
  float local_38;
  float local_34;
  float local_30;
  uint32_t uStack_10;
  
  uStack_10 = 0x56352;
  local_5c = g_unk_010918c0;
  local_58 = g_unk_010918c4;
  local_54 = g_unk_010918c8;
  local_50 = g_unk_010918cc * 512.0 + g_unk_010918c0;
  local_4c = g_unk_010918d0 * 512.0 + g_unk_010918c4;
  local_48 = g_unk_010918d4 * 512.0 + g_unk_010918c8;
  CG_Trace(local_44,&local_5c,0,0,&local_50,0xffffffff,1);
  local_38 = local_38 - *(float *)(param_1 + 0x18);
  if (((local_38 * local_38 < 256.0) &&
      (local_34 = local_34 - *(float *)(param_1 + 0x1c), local_34 * local_34 < 256.0)) &&
     (local_30 = local_30 - *(float *)(param_1 + 0x20), local_30 * local_30 < 256.0)) {
    g_unk_01093560 = *(int *)(param_1 + 0x8c);
    if (g_unk_01093560 == 0x3fe) {
      g_unk_01093560 = -1;
    }
    else {
      g_unk_01093564 = g_unk_010906e0;
    }
  }
  return;
}

void CG_ScanForCrosshairDynamite(uint32_t *param_1)
{
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  uint8_t local_44 [12];
  float local_38;
  float local_34;
  float local_30;
  uint32_t uStack_10;
  
  uStack_10 = 0x56494;
  local_5c = g_unk_010918c0;
  local_58 = g_unk_010918c4;
  local_54 = g_unk_010918c8;
  local_50 = g_unk_010918cc * 512.0 + g_unk_010918c0;
  local_4c = g_unk_010918d0 * 512.0 + g_unk_010918c4;
  local_48 = g_unk_010918d4 * 512.0 + g_unk_010918c8;
  CG_Trace(local_44,&local_5c,0,0,&local_50,0xffffffff,1);
  if ((((local_38 - (float)param_1[6]) * (local_38 - (float)param_1[6]) < 256.0) &&
      ((local_34 - (float)param_1[7]) * (local_34 - (float)param_1[7]) < 256.0)) &&
     ((local_30 - (float)param_1[8]) * (local_30 - (float)param_1[8]) < 256.0)) {
    g_unk_01093558 = *param_1;
    g_unk_010aabd0 = param_1[0x2b];
    g_unk_0109355c = g_unk_010906e0;
  }
  return;
}

void CG_CheckForCursorHints(void)
{
  float tmp_f1;
  uint tmp_u2;
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
  uint8_t local_44 [8];
  float local_3c;
  uint8_t local_38 [32];
  byte local_18;
  int local_10;
  
  if (g_unk_010906f4 == 0) {
    if (*(int *)(g_unk_01047b00 + 0x454) == 0) {
      local_74 = *(float *)(g_unk_010afbcc + 0x18);
      local_70 = *(float *)(g_unk_010afbcc + 0x1c);
      local_6c = *(float *)(g_unk_010afbcc + 0x20);
      local_68 = *(float *)(g_unk_010afbcc + 0x24) * 100.0 + local_74;
      local_64 = *(float *)(g_unk_010afbcc + 0x28) * 100.0 + local_70;
      local_60 = *(float *)(g_unk_010afbcc + 0x2c) * 100.0 + local_6c;
      CG_Trace(local_44,&local_74,&vec3_origin,&vec3_origin,&local_68,
               *(uint32_t *)(g_unk_01047b00 + 0xcc),0x2010001);
      if (local_3c == 1.0) {
        tmp_u2 = CG_PointContents(local_38,0xffffffff);
        if ((tmp_u2 & 0x20) == 0) {
          return;
        }
        tmp_u2 = CG_PointContents(&g_unk_010918c0,0xffffffff);
        if ((tmp_u2 & 0x20) != 0) {
          return;
        }
      }
      else {
        tmp_f1 = local_3c * 100.0;
        if (local_10 < 0x40) {
          if (48.0 < tmp_f1) {
            return;
          }
          if (*(int *)(g_unk_01047b00 + 0xd0) != 1) {
            return;
          }
          AngleVectors(g_unk_01047b00 + 0xdc,&local_5c,0,0);
          AngleVectors(local_10 * 0xaf8 + 0x31345e0,&local_50,0,0);
          if (local_48 * local_54 + local_4c * local_58 + local_50 * local_5c <= 0.6) {
            return;
          }
          g_unk_010aac08 = 0xe;
          g_unk_010aac0c = g_unk_010906e0;
          g_unk_010aac10 = 500;
          g_unk_010aac14 = 0;
          return;
        }
        if (*(int *)(cg_entities + local_10 * 0xaf8 + 0xe4) - 1U < 2) {
          return;
        }
        if (local_10 != 0x3fe) {
          return;
        }
        tmp_u2 = CG_PointContents(local_38,0xffffffff);
        if (((tmp_u2 & 0x20) == 0) ||
           (tmp_u2 = CG_PointContents(&g_unk_010918c0,0xffffffff), (tmp_u2 & 0x20) != 0)) {
          if ((local_18 & 8) == 0) {
            return;
          }
          if ((*(byte *)(g_unk_01047b00 + 0x38) & 4) != 0) {
            return;
          }
          if (100.0 < tmp_f1) {
            return;
          }
          g_unk_010aac08 = 0xf;
          g_unk_010aac0c = g_unk_010906e0;
          g_unk_010aac10 = 500;
          g_unk_010aac14 = 0;
          return;
        }
        if (100.0 < tmp_f1) {
          return;
        }
      }
      g_unk_010aac08 = 0x11;
      g_unk_010aac10 = 500;
      g_unk_010aac14 = 0;
      g_unk_010aac0c = g_unk_010906e0;
    }
    else {
      g_unk_010aac10 = 500;
      g_unk_010aac0c = g_unk_010906e0;
      g_unk_010aac08 = *(uint32_t *)(g_unk_01047b00 + 0x454);
      g_unk_010aac14 = *(uint32_t *)(g_unk_01047b00 + 0x458);
    }
  }
  return;
}

int CG_CrosshairClientMaxHealth(void)
{
  int *tmp_pi1;
  int tmp_i2;
  int local_24;
  
  tmp_i2 = *(int *)(cgs + *(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x94b8) * 4 + 0x204196c);
  if (tmp_i2 < 1) {
    if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
      local_24 = 100;
    }
    else {
      tmp_pi1 = (int *)(cgs + 0x940c);
      tmp_i2 = 0;
      local_24 = 100;
      do {
        if ((((*tmp_pi1 != 0) &&
             (tmp_pi1[0x22] == *(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494))) &&
            (tmp_pi1[0x2b] == 1)) && (local_24 = local_24 + 10, 0x7c < local_24)) {
          local_24 = 0x7d;
          break;
        }
        tmp_i2 = tmp_i2 + 1;
        tmp_pi1 = tmp_pi1 + 0x69;
      } while (tmp_i2 != GHIDRA_FIELD(cgs, 27400, 4));
    }
    tmp_i2 = local_24 + 0xf;
    if ((cgs[g_unk_01093558 * 0x1a4 + 0x958c] & 8) == 0) {
      tmp_i2 = local_24;
    }
    if (*(int *)(cgs + g_unk_01093558 * 0x1a4 + 0x94b8) == 1) {
      return (int)ROUND((float)tmp_i2 * 1.12);
    }
  }
  return tmp_i2;
}

int CG_CalculateReinfTime_Float(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i1 = GHIDRA_FIELD(cg_bluelimbotime, 12, 4);
  if (param_1 == 0) {
    tmp_i2 = *(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494);
LAB_00057827:
    if (tmp_i2 != 1) goto LAB_00057835;
  }
  else {
    tmp_i2 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
    if (tmp_i2 != 3) goto LAB_00057827;
    tmp_i2 = 2;
    if (GHIDRA_FIELD(cgs, 33685908, 4) != 0) goto LAB_00057835;
  }
  tmp_i2 = 1;
  tmp_i1 = GHIDRA_FIELD(cg_redlimbotime, 12, 4);
LAB_00057835:
  return tmp_i1 - ((g_unk_010906e0 + *(int *)(cgs + tmp_i2 * 4 + 0x2005434)) - GHIDRA_FIELD(cgs, 28480, 4)) % tmp_i1;
}

int CG_CalculateReinfTime(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i1 = GHIDRA_FIELD(cg_bluelimbotime, 12, 4);
  if (param_1 == 0) {
    tmp_i2 = *(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494);
LAB_000578df:
    if (tmp_i2 != 1) goto LAB_000578f1;
  }
  else {
    tmp_i2 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
    if (tmp_i2 != 3) goto LAB_000578df;
    tmp_i2 = 2;
    if (GHIDRA_FIELD(cgs, 33685908, 4) != 0) goto LAB_000578f1;
  }
  tmp_i2 = 1;
  tmp_i1 = GHIDRA_FIELD(cg_redlimbotime, 12, 4);
LAB_000578f1:
  return (int)ROUND((float)(tmp_i1 - ((g_unk_010906e0 + *(int *)(cgs + tmp_i2 * 4 + 0x2005434)) -
                                    GHIDRA_FIELD(cgs, 28480, 4)) % tmp_i1) * 0.001 + 1.0);
}

void CG_ObjectivePrint(uint32_t param_1,uint32_t param_2)
{
  char tmp_c1;
  bool tmp_b2;
  uint tmp_u3;
  uint tmp_u4;
  uint8_t *tmp_pu5;
  char *tmp_pc6;
  uint *tmp_pu7;
  uint *tmp_pu8;
  uint8_t *tmp_pu9;
  
  if (g_unk_01092d00 == 0) {
    Q_strncpyz(&g_unk_010aaee0,param_1,0x400);
    tmp_pu8 = (uint *)&g_unk_010aaee0;
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
    tmp_pu9 = (uint8_t *)((int)tmp_pu8 + (-0x10aaee3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)));
    if (0 < (int)tmp_pu9) {
      tmp_pu5 = (uint8_t *)0x0;
      tmp_b2 = false;
      do {
        while ((tmp_pu5 != (uint8_t *)(((int)tmp_pu5 / 0x24) * 0x24) || ((int)tmp_pu5 < 1))) {
          if (((&g_unk_010aaee0)[(int)tmp_pu5] == ' ') && (tmp_b2)) {
            (&g_unk_010aaee0)[(int)tmp_pu5] = 10;
            goto LAB_00057a80;
          }
LAB_00057a31:
          tmp_pu5 = tmp_pu5 + 1;
          if (tmp_pu9 == tmp_pu5) goto LAB_00057a90;
        }
        if ((&g_unk_010aaee0)[(int)tmp_pu5] != ' ') {
          tmp_b2 = true;
          goto LAB_00057a31;
        }
        (&g_unk_010aaee0)[(int)tmp_pu5] = 10;
LAB_00057a80:
        tmp_b2 = false;
        tmp_pu5 = tmp_pu5 + 1;
      } while (tmp_pu9 != tmp_pu5);
    }
LAB_00057a90:
    tmp_pc6 = &g_unk_010aaee0;
    _DAT_010aaedc = 0x168;
    g_unk_010aaed8 = param_2;
    g_unk_010ab2e0 = 1;
    tmp_c1 = g_unk_010aaee0;
    while (g_unk_010aaed4 = g_unk_010906e0, tmp_c1 != '\0') {
      if (tmp_c1 == '\n') {
        g_unk_010ab2e0 = g_unk_010ab2e0 + 1;
      }
      tmp_pc6 = tmp_pc6 + 1;
      tmp_c1 = *tmp_pc6;
    }
  }
  return;
}

bool CG_CheckDisguise(void)
{
  uint tmp_u1;
  bool tmp_b2;
  
  tmp_b2 = false;
  tmp_u1 = *(int *)(g_unk_01047b00 + 0xd0) - 0x13;
  if (tmp_u1 < 0x20) {
    tmp_b2 = (1 << ((byte)tmp_u1 & 0x1f) & 0xa1000381U) != 0;
  }
  return tmp_b2;
}

int CG_ClassSkillForPosition(int param_1,int param_2)
{
  int tmp_i1;
  
  if (param_2 == 0) {
    tmp_i1 = BG_ClassSkillForClass(*(uint32_t *)(param_1 + 0xac));
    return tmp_i1;
  }
  if (param_2 == 2) {
    if (pm == (int *)0x0) {
      tmp_i1 = 4;
    }
    else if ((*(int *)(*pm + 0x140) != 0) || (tmp_i1 = 4, (*(byte *)(*pm + 0x69) & 0x80) != 0)) {
      return 5 - (uint)(*(int *)(param_1 + 0xac) == 0);
    }
  }
  else {
    tmp_i1 = 0;
  }
  return tmp_i1;
}

void CG_StatsDebugAddText(byte *param_1)
{
  byte tmp_b1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  size_t tmp_s5;
  byte *tmp_pb6;
  int tmp_i7;
  
  if (GHIDRA_FIELD(cg_debugSkills, 12, 4) != 0) {
    statsDebugPos = statsDebugPos + 1;
    if (5 < statsDebugPos) {
      statsDebugPos = 0;
    }
    Q_strncpyz(&statsDebugStrings + statsDebugPos * 0x80,param_1,0x200);
    tmp_i4 = statsDebugPos;
    tmp_f2 = (float)GHIDRA_FIELD(cgs, 131468, 4) * 0.15;
    (&statsDebugTime)[statsDebugPos] = g_unk_010906e0;
    if (param_1 == (byte *)0x0) {
      tmp_f3 = 0.0;
    }
    else {
      tmp_i7 = 0;
      tmp_s5 = strlen((char *)param_1);
      tmp_f3 = 0.0;
      tmp_pb6 = param_1;
      do {
        while( true ) {
          tmp_b1 = *tmp_pb6;
          if ((tmp_b1 == 0) || ((int)tmp_s5 <= tmp_i7)) goto LAB_00058a30;
          if ((tmp_b1 != 0x5e) || ((tmp_pb6[1] == 0 || (tmp_pb6[1] == 0x5e)))) break;
          tmp_pb6 = tmp_pb6 + 2;
          if (tmp_pb6 == (byte *)0x0) goto LAB_00058a30;
        }
        tmp_pb6 = tmp_pb6 + 1;
        tmp_i7 = tmp_i7 + 1;
        tmp_f3 = (float)*(int *)(cgs + (uint)tmp_b1 * 0x50 + 0x1b19c) + tmp_f3;
      } while (tmp_pb6 != (byte *)0x0);
    }
LAB_00058a30:
    (&statsDebugTextWidth)[tmp_i4] = (int)ROUND(tmp_f3 * tmp_f2);
    CG_Printf(&g_unk_00121ff9,param_1);
  }
  return;
}

void CG_BannerPrint(uint32_t param_1)
{
  bool tmp_b1;
  bool tmp_b2;
  char *tmp_pc3;
  uint tmp_u4;
  uint tmp_u5;
  char tmp_c6;
  uint8_t *tmp_pu7;
  char *tmp_pc8;
  int tmp_i9;
  uint8_t *tmp_pu10;
  int tmp_i11;
  uint *tmp_pu12;
  uint *tmp_pu13;
  bool tmp_b14;
  bool tmp_b15;
  uint32_t local_420;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x5937e;
  Q_strncpyz(&g_unk_010eecd0,param_1,0x400);
  tmp_pu13 = (uint *)&g_unk_010eecd0;
  do {
    tmp_pu12 = tmp_pu13;
    tmp_u4 = *tmp_pu12 + 0xfefefeff & ~*tmp_pu12;
    tmp_u5 = tmp_u4 & 0x80808080;
    tmp_pu13 = tmp_pu12 + 1;
  } while (tmp_u5 == 0);
  if ((tmp_u4 & 0x8080) == 0) {
    tmp_pu13 = (uint *)((int)tmp_pu12 + 6);
    tmp_u5 = tmp_u5 >> 0x10;
  }
  tmp_pu10 = (uint8_t *)((int)tmp_pu13 + (-0x10eecd3 - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5)));
  if (0 < (int)tmp_pu10) {
    tmp_i9 = 0;
    tmp_b2 = false;
    tmp_pc8 = &g_unk_010eecd0;
    local_420 = local_41c;
    tmp_i11 = 1;
LAB_0005950f:
    do {
      tmp_c6 = *tmp_pc8;
      if (tmp_c6 == '\\') {
        if (tmp_pc8[1] == 'n') {
          Q_strncpyz(local_420,tmp_pc8 + 2,0x400);
          *tmp_pc8 = '\n';
          tmp_pc8[1] = '\0';
          Q_strcat(&g_unk_010eecd0,0x400,local_420);
          tmp_c6 = *tmp_pc8;
          if (tmp_c6 == '\n') goto LAB_00059580;
          goto LAB_00059421;
        }
LAB_0005943f:
        tmp_b1 = 0 < tmp_i9;
        tmp_b14 = tmp_i9 == (tmp_i9 / 0x37) * 0x37;
        tmp_b15 = tmp_b14 && tmp_b1;
        if (tmp_b14 && tmp_b1) {
LAB_00059470:
          tmp_b1 = tmp_b15;
          tmp_b2 = true;
        }
      }
      else {
        if (tmp_c6 != '\n') {
LAB_00059421:
          if (tmp_c6 == '^') {
            if ((tmp_pc8[1] != '\0') && (tmp_pc8[1] != '^')) {
              tmp_i9 = tmp_i9 + -2;
            }
            goto LAB_0005943f;
          }
          tmp_b1 = 0 < tmp_i9;
          tmp_b15 = tmp_i9 == (tmp_i9 / 0x37) * 0x37;
          if (tmp_b15 && tmp_b1) {
            tmp_b15 = tmp_b15 && tmp_b1;
            if (tmp_c6 != ' ') goto LAB_00059470;
            *tmp_pc8 = '\n';
          }
          else {
            if ((tmp_c6 != ' ') || (!tmp_b2)) goto LAB_00059479;
            *tmp_pc8 = '\n';
          }
          tmp_b2 = false;
          tmp_i9 = 1;
          tmp_pc8 = tmp_pc8 + 1;
          tmp_b1 = (int)tmp_pu10 <= tmp_i11;
          tmp_i11 = tmp_i11 + 1;
          if (tmp_b1) break;
          goto LAB_0005950f;
        }
LAB_00059580:
        tmp_b1 = false;
        tmp_i9 = 0;
      }
LAB_00059479:
      tmp_pc3 = local_420;
      if ((tmp_i9 == (tmp_i9 / 0x41) * 0x41) && (tmp_b1)) {
        Q_strncpyz(local_420,tmp_pc8,0x400);
        *tmp_pc8 = '\n';
        (&g_unk_010eecd0)[tmp_i11] = 0;
        tmp_i9 = 1;
        Q_strcat(&g_unk_010eecd0,0x400,tmp_pc3);
        tmp_b2 = false;
      }
      else {
        tmp_i9 = tmp_i9 + 1;
      }
      tmp_pc8 = tmp_pc8 + 1;
      tmp_b1 = tmp_i11 < (int)tmp_pu10;
      tmp_i11 = tmp_i11 + 1;
    } while (tmp_b1);
    tmp_pu13 = (uint *)&g_unk_010eecd0;
    do {
      tmp_pu12 = tmp_pu13;
      tmp_u4 = *tmp_pu12 + 0xfefefeff & ~*tmp_pu12;
      tmp_u5 = tmp_u4 & 0x80808080;
      tmp_pu13 = tmp_pu12 + 1;
    } while (tmp_u5 == 0);
    if ((tmp_u4 & 0x8080) == 0) {
      tmp_pu13 = (uint *)((int)tmp_pu12 + 6);
      tmp_u5 = tmp_u5 >> 0x10;
    }
    tmp_pu10 = (uint8_t *)((int)tmp_pu13 + (-0x10eecd3 - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5)));
  }
  tmp_pu7 = (uint8_t *)0x0;
  tmp_i9 = 0;
  if (tmp_pu10 != (uint8_t *)0x0) {
    do {
      tmp_c6 = (&g_unk_010eecd0)[(int)tmp_pu7];
      if (tmp_c6 == '\n') {
        if ((tmp_i9 != 0) && (local_41c[tmp_i9 + -1] != ' ')) {
          local_41c[tmp_i9] = ' ';
          tmp_i9 = tmp_i9 + 1;
        }
      }
      else if ((tmp_c6 == ' ') && (tmp_i9 == 0)) {
        tmp_i9 = 0;
      }
      else {
        local_41c[tmp_i9] = tmp_c6;
        tmp_i9 = tmp_i9 + 1;
      }
      tmp_pu7 = tmp_pu7 + 1;
      tmp_pu13 = (uint *)&g_unk_010eecd0;
      do {
        tmp_pu12 = tmp_pu13;
        tmp_u4 = *tmp_pu12 + 0xfefefeff & ~*tmp_pu12;
        tmp_u5 = tmp_u4 & 0x80808080;
        tmp_pu13 = tmp_pu12 + 1;
      } while (tmp_u5 == 0);
      if ((tmp_u4 & 0x8080) == 0) {
        tmp_pu13 = (uint *)((int)tmp_pu12 + 6);
        tmp_u5 = tmp_u5 >> 0x10;
      }
    } while (tmp_pu7 < (uint8_t *)
                      ((int)tmp_pu13 + (-0x10eecd3 - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5))));
  }
  g_unk_010eeccc = g_unk_010906e0;
  return;
}

void CG_StartShakeCamera(float param_1)
{
  float tmp_f1;
  uint tmp_u2;
  
  g_unk_010ab33c = param_1;
  g_unk_010ab340 = param_1 * param_1 * 1000.0;
  nitrox_ClampFloat(&g_unk_010ab340,0,0x447a0000);
  g_unk_010ab334 = (int)ROUND((float)g_unk_010906e0 + g_unk_010ab340);
  tmp_u2 = rand();
  tmp_f1 = (float)(tmp_u2 & 0x7fff) / 32767.0 - 0.5;
  g_unk_010ab338 = (tmp_f1 + tmp_f1) * 3.1415927;
  return;
}

void CG_ShakeCamera(void)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  double tmp_d4;
  
  tmp_f2 = g_unk_010ab338;
  if (g_unk_010ab334 < g_unk_010906e0) {
    g_unk_010ab33c = 0.0;
    g_unk_010ab340 = 0.0;
    g_unk_010ab338 = 0.0;
    g_unk_010ab334 = 0;
    return;
  }
  tmp_f1 = (float)(g_unk_010ab334 - g_unk_010906e0) / g_unk_010ab340;
  tmp_d4 = sin((double)(g_unk_010ab338 + tmp_f1 * 21.991148));
  tmp_f3 = g_unk_010ab33c;
  g_unk_010918c8 = g_unk_010ab33c * (float)tmp_d4 * tmp_f1 * 4.0 + g_unk_010918c8;
  tmp_d4 = sin((double)(tmp_f1 * 40.840706 + tmp_f2));
  g_unk_010918c4 = (float)tmp_d4 * tmp_f1 * 4.0 * tmp_f3 + g_unk_010918c4;
  tmp_d4 = cos((double)(tmp_f1 * 53.407074 + tmp_f2));
  g_unk_010918c0 = (float)tmp_d4 * tmp_f1 * 4.0 * tmp_f3 + g_unk_010918c0;
  AnglesToAxis(&g_unk_01091a54,&g_unk_010918cc);
  return;
}

void CG_Coronas(void)
{
  if (GHIDRA_FIELD(cg_coronas, 12, 4) != 0) {
    CG_Coronas_part_4();
    return;
  }
  return;
}

void CG_HorizontalPercentBar(float param_1,float param_2,float param_3,float param_4,float param_5)
{
  float tmp_f1;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_2c = 0x3f800000;
  local_28 = 0x3f800000;
  local_24 = 0x3f800000;
  local_20 = 0x3e99999a;
  if (param_5 <= 1.0) {
    tmp_f1 = 0.0;
    if (0.0 <= param_5) {
      tmp_f1 = param_5;
    }
  }
  else {
    param_5 = 1.0;
    tmp_f1 = param_5;
  }
  param_5 = tmp_f1;
  local_1c = 0x3f000000;
  local_18 = 0x3f000000;
  local_14 = 0x3f000000;
  local_10 = 0x3e99999a;
  CG_FillRect(param_1,param_2,param_3,param_4,&local_1c);
  CG_FillRect(param_1 + 2.0,param_2 + 2.0,(param_3 - 4.0) * param_5,param_4 - 4.0,&local_2c);
  return;
}

void CG_TileClear(void)
{
  int tmp_i1;
  int tmp_i2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  int tmp_i8;
  int tmp_i9;
  uint32_t tmp_u10;
  uint32_t tmp_u11;
  int tmp_i12;
  
  tmp_u11 = GHIDRA_FIELD(cgs, 27340, 4);
  tmp_u10 = GHIDRA_FIELD(cgs, 27336, 4);
  tmp_i9 = g_unk_010918ac;
  tmp_i8 = g_unk_010918a8;
  if ((((g_unk_010918a8 != 0) || (g_unk_010918ac != 0)) || (g_unk_010918b0 != GHIDRA_FIELD(cgs, 27336, 4))) ||
     (g_unk_010918b4 != GHIDRA_FIELD(cgs, 27340, 4))) {
    tmp_i1 = g_unk_010918ac + -1 + g_unk_010918b4;
    tmp_f3 = (float)(int)GHIDRA_FIELD(cgs, 27336, 4) * 0.015625;
    tmp_i2 = g_unk_010918a8 + -1 + g_unk_010918b0;
    tmp_f4 = (float)g_unk_010918ac * 0.015625;
    tmp_f5 = (float)g_unk_010918ac;
    tmp_f6 = (float)(int)GHIDRA_FIELD(cgs, 27336, 4);
    trap_R_DrawStretchPic(0,0,tmp_f6,tmp_f5,0,0,tmp_f3,tmp_f4,GHIDRA_FIELD(cgs, 68072, 4));
    tmp_i12 = (tmp_i1 - tmp_i9) + 1;
    trap_R_DrawStretchPic
              (0,(float)tmp_i1,tmp_f6,(float)(tmp_u11 - tmp_i1),0,(float)tmp_i1 * 0.015625,tmp_f3,
               (float)(int)tmp_u11 * 0.015625,GHIDRA_FIELD(cgs, 68072, 4));
    tmp_f6 = (float)(tmp_i9 + tmp_i12) * 0.015625;
    tmp_f7 = (float)tmp_i12;
    trap_R_DrawStretchPic
              (0,tmp_f5,(float)tmp_i8,tmp_f7,0,tmp_f4,(float)tmp_i8 * 0.015625,tmp_f6,GHIDRA_FIELD(cgs, 68072, 4));
    trap_R_DrawStretchPic
              ((float)tmp_i2,tmp_f5,(float)(tmp_u10 - tmp_i2),tmp_f7,(float)tmp_i2 * 0.015625,tmp_f4,tmp_f3,
               tmp_f6,GHIDRA_FIELD(cgs, 68072, 4));
  }
  return;
}

uint32_t * CG_FadeColor(int param_1,int param_2)
{
  if ((param_1 != 0) && (g_unk_010906e0 - param_1 < param_2)) {
    param_2 = param_2 - (g_unk_010906e0 - param_1);
    if (param_2 < 200) {
      g_unk_002b3a30 = (float)param_2 / 200.0;
    }
    else {
      g_unk_002b3a30 = 1.0;
    }
    g_unk_002b3a2c = 0x3f800000;
    g_unk_002b3a28 = 0x3f800000;
    color_12271 = 0x3f800000;
    return &color_12271;
  }
  return (uint32_t *)0x0;
}

void CG_ColorForHealth(uint32_t *param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(g_unk_01047b00 + 0xfc);
  if (tmp_i1 < 1) {
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1 = 0;
    param_1[3] = 0x3f800000;
    return;
  }
  *param_1 = 0x3f800000;
  param_1[3] = 0x3f800000;
  if (tmp_i1 < 100) {
    if (tmp_i1 < 0x42) {
      param_1[2] = 0;
      if (tmp_i1 < 0x3d) {
        if (0x1d < tmp_i1) {
          param_1[1] = (float)(tmp_i1 + -0x1e) / 30.0;
          return;
        }
        param_1[1] = 0;
        return;
      }
    }
    else {
      param_1[2] = (float)(tmp_i1 + -0x42) / 33.0;
    }
  }
  else {
    param_1[2] = 0x3f800000;
  }
  param_1[1] = 0x3f800000;
  return;
}

uint CG_BubbleTrail(float *param_1,float *param_2,uint32_t param_3,float param_4)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint32_t tmp_u6;
  int tmp_i7;
  uint tmp_u8;
  int tmp_i9;
  ushort inreg_FPUControlWord;
  long double tmp_l10;
  uint local_4c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_f1 = *param_1;
  tmp_f2 = param_1[1];
  tmp_f3 = param_1[2];
  local_28 = *param_2 - tmp_f1;
  local_24 = param_2[1] - tmp_f2;
  local_20 = param_2[2] - tmp_f3;
  tmp_l10 = (long double)VectorNormalize(&local_28);
  tmp_i7 = rand();
  tmp_u8 = tmp_i7 / (int)ROUND(param_4);
  tmp_f4 = (float)(tmp_i7 % (int)ROUND(param_4));
  tmp_f1 = tmp_f1 + local_28 * tmp_f4;
  tmp_f2 = tmp_f2 + local_24 * tmp_f4;
  tmp_f3 = tmp_f3 + local_20 * tmp_f4;
  local_28 = param_4 * local_28;
  local_24 = param_4 * local_24;
  local_20 = param_4 * local_20;
  for (; tmp_f4 < (float)tmp_l10; tmp_f4 = (float)(int)ROUND(tmp_f4 + param_4)) {
    tmp_i9 = CG_AllocLocalEntity();
    *(uint32_t *)(tmp_i9 + 0xc) = 1;
    *(uint32_t *)(tmp_i9 + 8) = 4;
    *(int *)(tmp_i9 + 0x10) = g_unk_010906e0;
    tmp_i7 = g_unk_010906e0 + 1000;
    local_4c = rand();
    local_4c = local_4c & 0x7fff;
    tmp_i7 = (int)ROUND(((float)local_4c / 32767.0) * 250.0 + (float)tmp_i7);
    *(int *)(tmp_i9 + 0x14) = tmp_i7;
    *(float *)(tmp_i9 + 0x1c) = 1.0 / (float)(tmp_i7 - *(int *)(tmp_i9 + 0x10));
    tmp_f5 = (float)g_unk_010906e0;
    *(uint32_t *)(tmp_i9 + 0x98) = 2;
    *(uint32_t *)(tmp_i9 + 0x160) = 0;
    *(float *)(tmp_i9 + 0x158) = tmp_f5 / 1000.0;
    *(uint32_t *)(tmp_i9 + 0x15c) = param_3;
    tmp_u6 = GHIDRA_FIELD(cgs, 68096, 4);
    *(uint8_t *)(tmp_i9 + 0x14c) = 0xff;
    *(uint8_t *)(tmp_i9 + 0x14d) = 0xff;
    *(uint8_t *)(tmp_i9 + 0x14e) = 0xff;
    *(uint32_t *)(tmp_i9 + 0x148) = tmp_u6;
    *(uint8_t *)(tmp_i9 + 0x14f) = 0xff;
    *(uint32_t *)(tmp_i9 + 0x78) = 0x3f800000;
    *(uint32_t *)(tmp_i9 + 0x20) = 2;
    tmp_i7 = g_unk_010906e0;
    *(float *)(tmp_i9 + 0x2c) = tmp_f1;
    *(int *)(tmp_i9 + 0x24) = tmp_i7;
    *(float *)(tmp_i9 + 0x30) = tmp_f2;
    *(float *)(tmp_i9 + 0x34) = tmp_f3;
    tmp_u8 = rand();
    tmp_f5 = (float)(tmp_u8 & 0x7fff) / 32767.0 - 0.5;
    *(float *)(tmp_i9 + 0x38) = (tmp_f5 + tmp_f5) * 3.0;
    tmp_u8 = rand();
    tmp_f5 = (float)(tmp_u8 & 0x7fff) / 32767.0 - 0.5;
    *(float *)(tmp_i9 + 0x3c) = (tmp_f5 + tmp_f5) * 3.0;
    tmp_u8 = rand();
    tmp_f5 = (float)(tmp_u8 & 0x7fff) / 32767.0 - 0.5;
    *(float *)(tmp_i9 + 0x40) = (tmp_f5 + tmp_f5) * 5.0 + 20.0;
    tmp_f1 = tmp_f1 + local_28;
    tmp_f2 = tmp_f2 + local_24;
    tmp_u8 = (uint)(inreg_FPUControlWord | 0xc00);
    tmp_f3 = tmp_f3 + local_20;
  }
  return tmp_u8;
}

void CG_SmokePuff(uint32_t *param_1,uint32_t *param_2,uint32_t param_3,float param_4,
                 float param_5,float param_6,uint32_t param_7,float param_8,int param_9,
                 int param_10,uint32_t param_11,uint32_t param_12)

{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  long double tmp_l5;
  
  tmp_i4 = CG_AllocLocalEntity();
  *(uint32_t *)(tmp_i4 + 0xc) = param_11;
  *(uint32_t *)(tmp_i4 + 0x7c) = param_3;
  tmp_l5 = (long double)Q_random(&seed_11966);
  *(uint32_t *)(tmp_i4 + 8) = 4;
  *(int *)(tmp_i4 + 0x10) = param_9;
  *(float *)(tmp_i4 + 0x160) = (float)(tmp_l5 * (long double)360.0);
  *(uint32_t *)(tmp_i4 + 0x15c) = param_3;
  *(float *)(tmp_i4 + 0x158) = (float)param_9 / 1000.0;
  tmp_i1 = (int)ROUND((float)param_9 + param_8);
  *(int *)(tmp_i4 + 0x18) = param_10;
  *(int *)(tmp_i4 + 0x14) = tmp_i1;
  tmp_i2 = param_9;
  if (param_9 < param_10) {
    tmp_i2 = param_10;
  }
  *(uint32_t *)(tmp_i4 + 0x20) = 2;
  *(float *)(tmp_i4 + 0x1c) = 1.0 / (float)(tmp_i1 - tmp_i2);
  *(int *)(tmp_i4 + 0x24) = param_9;
  *(float *)(tmp_i4 + 0x6c) = param_4;
  *(float *)(tmp_i4 + 0x70) = param_5;
  *(float *)(tmp_i4 + 0x74) = param_6;
  *(uint32_t *)(tmp_i4 + 0x78) = param_7;
  *(uint32_t *)(tmp_i4 + 0x38) = *param_2;
  *(uint32_t *)(tmp_i4 + 0x3c) = param_2[1];
  *(uint32_t *)(tmp_i4 + 0x40) = param_2[2];
  *(uint32_t *)(tmp_i4 + 0x2c) = *param_1;
  *(uint32_t *)(tmp_i4 + 0x30) = param_1[1];
  *(uint32_t *)(tmp_i4 + 0x34) = param_1[2];
  *(uint32_t *)(tmp_i4 + 0x100) = *param_1;
  *(uint32_t *)(tmp_i4 + 0x104) = param_1[1];
  *(uint32_t *)(tmp_i4 + 0x108) = param_1[2];
  *(uint32_t *)(tmp_i4 + 0x148) = param_12;
  tmp_u3 = GHIDRA_FIELD(cgs, 68092, 4);
  if (GHIDRA_FIELD(cgs, 27292, 4) == 3) {
    *(uint8_t *)(tmp_i4 + 0x14c) = 0xff;
    *(uint8_t *)(tmp_i4 + 0x14d) = 0xff;
    *(uint8_t *)(tmp_i4 + 0x14e) = 0xff;
    *(uint32_t *)(tmp_i4 + 0x148) = tmp_u3;
    *(uint8_t *)(tmp_i4 + 0x14f) = 0xff;
  }
  else {
    *(char *)(tmp_i4 + 0x14c) = (char)(short)ROUND(param_4 * 255.0);
    *(char *)(tmp_i4 + 0x14d) = (char)(short)ROUND(param_5 * 255.0);
    *(uint8_t *)(tmp_i4 + 0x14f) = 0xff;
    *(char *)(tmp_i4 + 0x14e) = (char)(short)ROUND(param_6 * 255.0);
  }
  *(uint32_t *)(tmp_i4 + 0x98) = 2;
  *(uint32_t *)(tmp_i4 + 0x15c) = *(uint32_t *)(tmp_i4 + 0x7c);
  return;
}

void CG_SpawnEffect(void)
{
  return;
}

int CG_MakeExplosion(float *param_1,float *param_2,uint32_t param_3,uint32_t param_4,int param_5
                    ,int param_6)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  
  if (param_5 < 1) {
    CG_Error("CG_MakeExplosion: msec = %i",param_5);
  }
  tmp_u4 = rand();
  tmp_i5 = CG_AllocLocalEntity();
  if (param_6 == 0) {
    *(uint32_t *)(tmp_i5 + 8) = 1;
    tmp_f1 = *param_1;
    tmp_f2 = param_1[1];
    tmp_f3 = param_1[2];
    if (param_2 == (float *)0x0) {
      AxisClear(tmp_i5 + 0xb4);
    }
    else {
      tmp_i6 = rand();
      *(float *)(tmp_i5 + 0xb4) = *param_2;
      *(float *)(tmp_i5 + 0xb8) = param_2[1];
      *(float *)(tmp_i5 + 0xbc) = param_2[2];
      RotateAroundDirection(tmp_i5 + 0xb4,(float)(tmp_i6 % 0x168));
    }
  }
  else {
    *(uint32_t *)(tmp_i5 + 8) = 2;
    tmp_i6 = rand();
    *(float *)(tmp_i5 + 0x160) = (float)(tmp_i6 % 0x168);
    tmp_f1 = *param_2 * 16.0 + *param_1;
    tmp_f2 = param_2[1] * 16.0 + param_1[1];
    tmp_f3 = param_2[2] * 16.0 + param_1[2];
  }
  tmp_i6 = g_unk_010906e0;
  *(uint32_t *)(tmp_i5 + 0x20) = 2;
  tmp_i6 = tmp_i6 - (tmp_u4 & 0x3f);
  *(int *)(tmp_i5 + 0x10) = tmp_i6;
  *(int *)(tmp_i5 + 0x14) = param_5 + tmp_i6;
  *(uint32_t *)(tmp_i5 + 0xa0) = param_3;
  *(uint32_t *)(tmp_i5 + 0x148) = param_4;
  *(float *)(tmp_i5 + 0x158) = (float)tmp_i6 / 1000.0;
  *(float *)(tmp_i5 + 0x100) = tmp_f1;
  *(float *)(tmp_i5 + 0x104) = tmp_f2;
  *(float *)(tmp_i5 + 0x108) = tmp_f3;
  *(float *)(tmp_i5 + 0x11c) = tmp_f1;
  *(float *)(tmp_i5 + 0x120) = tmp_f2;
  *(float *)(tmp_i5 + 0x124) = tmp_f3;
  tmp_i6 = g_unk_010906e0;
  *(float *)(tmp_i5 + 0x2c) = tmp_f1;
  *(float *)(tmp_i5 + 0x30) = tmp_f2;
  *(float *)(tmp_i5 + 0x34) = tmp_f3;
  *(int *)(tmp_i5 + 0x24) = tmp_i6;
  *(float *)(tmp_i5 + 0x38) = *param_2 * 48.0;
  *(float *)(tmp_i5 + 0x3c) = param_2[1] * 48.0;
  *(float *)(tmp_i5 + 0x40) = param_2[2] * 48.0;
  *(uint32_t *)(tmp_i5 + 0x74) = 0x3f800000;
  *(uint32_t *)(tmp_i5 + 0x70) = 0x3f800000;
  *(uint32_t *)(tmp_i5 + 0x6c) = 0x3f800000;
  return tmp_i5;
}

void CG_AddBloodTrails(float *param_1,float *param_2,int param_3,int param_4,int param_5,
                      float param_6)

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
  int tmp_i11;
  uint tmp_u12;
  uint tmp_u13;
  int tmp_i14;
  uint local_5c;
  
  if (0 < param_5) {
    tmp_i14 = 0;
    tmp_f6 = (float)param_3;
    do {
      tmp_i11 = CG_AllocLocalEntity();
      tmp_f1 = *param_2;
      tmp_u12 = rand();
      tmp_f2 = param_2[1];
      local_5c = rand();
      tmp_f3 = param_2[2];
      tmp_u13 = rand();
      tmp_f7 = (float)(tmp_u12 & 0x7fff) / 32767.0 - 0.5;
      local_5c = local_5c & 0x7fff;
      tmp_f4 = (float)local_5c;
      local_5c = tmp_u13 & 0x7fff;
      tmp_f9 = tmp_f4 / 32767.0 - 0.5;
      tmp_f8 = (float)local_5c / 32767.0 - 0.5;
      *(uint32_t *)(tmp_i11 + 8) = 0xb;
      tmp_i10 = g_unk_010906e0;
      *(int *)(tmp_i11 + 0x10) = g_unk_010906e0;
      *(int *)(tmp_i11 + 0x14) = tmp_i10 + param_4;
      *(int *)(tmp_i11 + 0x184) = g_unk_010906e0;
      *(float *)(tmp_i11 + 0x100) = *param_1;
      *(float *)(tmp_i11 + 0x104) = param_1[1];
      *(float *)(tmp_i11 + 0x108) = param_1[2];
      AxisCopy(axisDefault,tmp_i11 + 0xb4);
      *(uint32_t *)(tmp_i11 + 0x20) = 7;
      tmp_f4 = *param_1;
      *(float *)(tmp_i11 + 0x2c) = tmp_f4;
      *(float *)(tmp_i11 + 0x30) = param_1[1];
      *(float *)(tmp_i11 + 0x34) = param_1[2];
      tmp_f5 = *param_2;
      tmp_u12 = rand();
      *(float *)(tmp_i11 + 0x2c) = tmp_f4 + (((float)(tmp_u12 & 0x7fff) / 32767.0) * 4.0 + 2.0) * tmp_f5
      ;
      tmp_f4 = *(float *)(tmp_i11 + 0x30);
      tmp_f5 = param_2[1];
      tmp_u12 = rand();
      *(float *)(tmp_i11 + 0x30) = (((float)(tmp_u12 & 0x7fff) / 32767.0) * 4.0 + 2.0) * tmp_f5 + tmp_f4
      ;
      tmp_f4 = *(float *)(tmp_i11 + 0x34);
      tmp_f5 = param_2[2];
      tmp_u12 = rand();
      tmp_i14 = tmp_i14 + 1;
      *(float *)(tmp_i11 + 0x34) = (((float)(tmp_u12 & 0x7fff) / 32767.0) * 4.0 + 2.0) * tmp_f5 + tmp_f4
      ;
      *(float *)(tmp_i11 + 0x38) = ((tmp_f7 + tmp_f7) * param_6 + tmp_f1) * tmp_f6;
      *(float *)(tmp_i11 + 0x3c) = ((tmp_f9 + tmp_f9) * param_6 + tmp_f2) * tmp_f6;
      *(float *)(tmp_i11 + 0x40) = ((tmp_f8 + tmp_f8) * param_6 + tmp_f3) * tmp_f6;
      tmp_i10 = g_unk_010906e0;
      *(uint32_t *)(tmp_i11 + 0x68) = 0x3f666666;
      *(int *)(tmp_i11 + 0x24) = tmp_i10;
    } while (tmp_i14 != param_5);
  }
  return;
}

void CG_LoseACC(int param_1,float *param_2,int param_3,uint32_t param_4,int param_5)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint32_t tmp_u4;
  float tmp_f5;
  int tmp_i6;
  int tmp_i7;
  uint tmp_u8;
  uint tmp_u9;
  uint tmp_u10;
  uint tmp_u11;
  uint32_t *tmp_pu12;
  int tmp_i13;
  float local_94;
  float local_90;
  float local_84;
  float local_4c;
  float local_48;
  float local_44;
  
  tmp_u8 = *(uint *)(param_1 + 0xac);
  if (0x3f < tmp_u8) {
    CG_Error("Bad clientNum on player entity");
  }
  tmp_i6 = CG_CharacterForClientinfo(tmp_u8 * 0x1a4 + 0x10f926c,param_1);
  tmp_i6 = tmp_i6 + param_3 * 4;
  if (*(int *)(tmp_i6 + 0x48) != 0) {
    tmp_i13 = param_1 + 0x478;
    if (param_5 != 0) {
      tmp_i13 = param_1 + 0x564;
    }
    tmp_i7 = trap_R_LerpTag(&local_4c,tmp_i13,param_4,0);
    if (tmp_i7 < 0) {
      local_84 = 0.0;
      local_90 = 0.0;
      local_94 = 0.0;
    }
    else {
      local_94 = *(float *)(tmp_i13 + 0x28) * local_48 +
                 *(float *)(tmp_i13 + 0x1c) * local_4c + *(float *)(tmp_i13 + 0x68) +
                 *(float *)(tmp_i13 + 0x34) * local_44;
      local_90 = *(float *)(tmp_i13 + 0x2c) * local_48 +
                 *(float *)(tmp_i13 + 0x20) * local_4c + *(float *)(tmp_i13 + 0x6c) +
                 *(float *)(tmp_i13 + 0x38) * local_44;
      local_84 = local_44 * *(float *)(tmp_i13 + 0x3c) +
                 local_48 * *(float *)(tmp_i13 + 0x30) +
                 local_4c * *(float *)(tmp_i13 + 0x24) + *(float *)(tmp_i13 + 0x70);
    }
    tmp_f1 = *param_2;
    tmp_u8 = rand();
    tmp_f2 = param_2[1];
    tmp_u9 = rand();
    tmp_f3 = param_2[2];
    tmp_u10 = rand();
    tmp_i7 = CG_AllocLocalEntity();
    *(uint32_t *)(tmp_i7 + 8) = 3;
    tmp_i13 = g_unk_010906e0;
    *(int *)(tmp_i7 + 0x10) = g_unk_010906e0;
    tmp_u11 = rand();
    tmp_f5 = (float)(tmp_u11 & 0x7fff) / 32767.0 - 0.5;
    *(int *)(tmp_i7 + 0x14) = (int)ROUND((tmp_f5 + tmp_f5) * 5000.0 + (float)(tmp_i13 + 20000));
    *(float *)(tmp_i7 + 0x100) = local_94;
    *(float *)(tmp_i7 + 0x104) = local_90;
    *(float *)(tmp_i7 + 0x108) = local_84;
    AxisCopy(axisDefault,tmp_i7 + 0xb4);
    tmp_i13 = *(int *)(tmp_i6 + 0x48);
    *(int *)(tmp_i7 + 0xa0) = tmp_i13;
    *(uint32_t *)(tmp_i7 + 0x144) = *(uint32_t *)(tmp_i6 + 0x74);
    if (tmp_i13 == 0) {
      CG_FreeLocalEntity(tmp_i7);
    }
    else {
      *(uint32_t *)(tmp_i7 + 0x20) = 6;
      *(float *)(tmp_i7 + 0x2c) = local_94;
      *(int *)(tmp_i7 + 0x174) = *(int *)(tmp_i7 + 0x14);
      *(float *)(tmp_i7 + 0x30) = local_90;
      *(int *)(tmp_i7 + 0x170) = *(int *)(tmp_i7 + 0x14) + -1000;
      *(float *)(tmp_i7 + 0x34) = local_84;
      *(float *)(tmp_i7 + 0x38) = tmp_f1 * ((float)(tmp_u8 & 0x7fff) / 32767.0 + 0.75) * 75.0;
      *(float *)(tmp_i7 + 0x3c) = ((float)(tmp_u9 & 0x7fff) / 32767.0 + 0.75) * tmp_f2 * 75.0;
      *(float *)(tmp_i7 + 0x40) = ((float)(tmp_u10 & 0x7fff) / 32767.0 + 0.5) * tmp_f3 * 75.0 + 200.0;
      tmp_i6 = g_unk_010906e0;
      *(uint32_t *)(tmp_i7 + 0x44) = 2;
      *(int *)(tmp_i7 + 0x24) = tmp_i6;
      tmp_pu12 = (uint32_t *)tv(0,0,0);
      *(uint32_t *)(tmp_i7 + 0x50) = *tmp_pu12;
      tmp_i6 = tv(0,0,0);
      *(uint32_t *)(tmp_i7 + 0x54) = *(uint32_t *)(tmp_i6 + 4);
      tmp_i6 = tv(0,0,0);
      tmp_u4 = *(uint32_t *)(tmp_i6 + 8);
      *(uint32_t *)(tmp_i7 + 0x5c) = 0;
      *(uint32_t *)(tmp_i7 + 0x58) = tmp_u4;
      tmp_u8 = rand();
      *(float *)(tmp_i7 + 0x60) = (float)(int)((tmp_u8 & 500) - 200);
      if (param_5 == 0) {
        *(uint *)(tmp_i7 + 0x194) = *(uint *)(tmp_i7 + 0x194) | 2;
        tmp_u4 = 0x42480000;
      }
      else {
        tmp_u4 = 0x43c80000;
      }
      *(uint32_t *)(tmp_i7 + 100) = tmp_u4;
      tmp_i6 = g_unk_010906e0;
      *(uint32_t *)(tmp_i7 + 0x68) = 0x3e4ccccd;
      *(int *)(tmp_i7 + 0x48) = tmp_i6;
      tmp_i6 = CG_EntOnFire(param_1);
      if (tmp_i6 != 0) {
        *(uint32_t *)(tmp_i7 + 0x19c) = *(uint32_t *)(param_1 + 0xfc);
        *(int *)(tmp_i7 + 0x1a0) = *(int *)(param_1 + 0x100) + 4000;
        return;
      }
    }
  }
  return;
}

int CG_GetOriginForTag(uint32_t param_1,int param_2,uint32_t param_3,uint32_t param_4,
                      float *param_5,int param_6)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  float local_4c;
  float local_48;
  float local_44;
  uint8_t local_40 [48];
  
  tmp_i4 = trap_R_LerpTag(&local_4c,param_2,param_3,param_4);
  if (-1 < tmp_i4) {
    tmp_f1 = *(float *)(param_2 + 0x68);
    *param_5 = tmp_f1;
    tmp_f2 = *(float *)(param_2 + 0x6c);
    param_5[1] = tmp_f2;
    tmp_f3 = *(float *)(param_2 + 0x70);
    param_5[2] = tmp_f3;
    tmp_f1 = *(float *)(param_2 + 0x1c) * local_4c + tmp_f1;
    *param_5 = tmp_f1;
    tmp_f2 = *(float *)(param_2 + 0x20) * local_4c + tmp_f2;
    param_5[1] = tmp_f2;
    tmp_f3 = local_4c * *(float *)(param_2 + 0x24) + tmp_f3;
    param_5[2] = tmp_f3;
    tmp_f1 = *(float *)(param_2 + 0x28) * local_48 + tmp_f1;
    *param_5 = tmp_f1;
    tmp_f2 = *(float *)(param_2 + 0x2c) * local_48 + tmp_f2;
    param_5[1] = tmp_f2;
    tmp_f3 = local_48 * *(float *)(param_2 + 0x30) + tmp_f3;
    param_5[2] = tmp_f3;
    *param_5 = *(float *)(param_2 + 0x34) * local_44 + tmp_f1;
    param_5[1] = *(float *)(param_2 + 0x38) * local_44 + tmp_f2;
    param_5[2] = local_44 * *(float *)(param_2 + 0x3c) + tmp_f3;
    if (param_6 != 0) {
      MatrixMultiply(local_40,param_2 + 0x1c,param_6);
    }
  }
  return tmp_i4;
}

void CG_SparklerSparks(uint32_t *param_1,int param_2)
{
  uint32_t tmp_u1;
  float tmp_f2;
  int tmp_i3;
  uint tmp_u4;
  int tmp_i5;
  
  if (0 < param_2) {
    tmp_i5 = 0;
    do {
      tmp_i3 = CG_AllocLocalEntity();
      *(uint32_t *)(tmp_i3 + 8) = 0xc;
      *(int *)(tmp_i3 + 0x10) = g_unk_010906e0;
      *(int *)(tmp_i3 + 0x14) = g_unk_010906e0 + 100;
      *(int *)(tmp_i3 + 0x184) = g_unk_010906e0;
      *(uint32_t *)(tmp_i3 + 0x100) = *param_1;
      *(uint32_t *)(tmp_i3 + 0x104) = param_1[1];
      tmp_u1 = param_1[2];
      *(uint32_t *)(tmp_i3 + 0x20) = 6;
      *(uint32_t *)(tmp_i3 + 0x108) = tmp_u1;
      *(uint32_t *)(tmp_i3 + 0x2c) = *param_1;
      *(uint32_t *)(tmp_i3 + 0x30) = param_1[1];
      *(uint32_t *)(tmp_i3 + 0x34) = param_1[2];
      tmp_u4 = rand();
      tmp_f2 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
      *(float *)(tmp_i3 + 0x38) = tmp_f2 + tmp_f2;
      tmp_u4 = rand();
      tmp_f2 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
      *(float *)(tmp_i3 + 0x3c) = tmp_f2 + tmp_f2;
      tmp_u4 = rand();
      tmp_f2 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
      *(float *)(tmp_i3 + 0x40) = tmp_f2 + tmp_f2;
      VectorNormalize(tmp_i3 + 0x38);
      tmp_i5 = tmp_i5 + 1;
      *(float *)(tmp_i3 + 0x38) = *(float *)(tmp_i3 + 0x38) * 300.0;
      *(float *)(tmp_i3 + 0x3c) = *(float *)(tmp_i3 + 0x3c) * 300.0;
      *(float *)(tmp_i3 + 0x40) = *(float *)(tmp_i3 + 0x40) * 300.0;
      *(int *)(tmp_i3 + 0x24) = g_unk_010906e0;
    } while (tmp_i5 != param_2);
  }
  return;
}

void CG_ProjectedSpotLight(float *param_1,float *param_2)
{
  float tmp_f1;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  uint8_t local_44 [8];
  float local_3c;
  uint8_t local_38 [44];
  uint32_t uStack_c;
  
  uStack_c = 0x64321;
  local_60 = *param_2 * 1000.0 + *param_1;
  local_5c = param_2[1] * 1000.0 + param_1[1];
  local_58 = param_2[2] * 1000.0 + param_1[2];
  CG_Trace(local_44,param_1,0,0,&local_60,0xffffffff,1);
  if (local_3c != 1.0) {
    tmp_f1 = local_3c * 64.0 + 32.0;
    local_54 = *param_2;
    local_50 = param_2[1];
    local_4c = param_2[2];
    local_48 = tmp_f1 + tmp_f1;
    CG_ImpactMark(GHIDRA_FIELD(cgs, 68864, 4),local_38,&local_54,tmp_f1,0,0x3f800000,0x3f800000,0x3f800000,
                  0x3f800000,0xffffffff);
    return;
  }
  return;
}

void CG_RumbleEfx(float param_1,float param_2)
{
  float tmp_f1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  long double tmp_l5;
  double tmp_d6;
  uint32_t local_2c;
  
  if (param_1 < 1.0) {
    tmp_i4 = 1;
    param_1 = 1.0;
  }
  else {
    tmp_i4 = (int)ROUND(param_1);
  }
  local_2c = rand();
  local_2c = local_2c & 0x7fff;
  tmp_d6 = pow((double)((float)local_2c / 32767.0),8.0);
  tmp_l5 = (long double)VectorLength(g_unk_01047b00 + 0x4c);
  tmp_i2 = rand();
  if (g_unk_010aaeb0 <= 0.0) {
    if (g_unk_010aaeb0 < 0.0) {
      tmp_u3 = rand();
      if ((float)(tmp_u3 & 0x7fff) / 32767.0 < 0.05) goto LAB_000645f0;
    }
    else {
      tmp_u3 = rand();
      if ((float)(tmp_u3 & 0x7fff) / 32767.0 < 0.5) {
LAB_000645f0:
        tmp_u3 = rand();
        tmp_f1 = (float)(tmp_u3 & 0x7fff) / 32767.0;
        goto LAB_00064580;
      }
    }
  }
  else {
    tmp_u3 = rand();
    if (0.05 <= (float)(tmp_u3 & 0x7fff) / 32767.0) goto LAB_000645f0;
  }
  tmp_u3 = rand();
  tmp_f1 = -((float)(tmp_u3 & 0x7fff) / 32767.0);
LAB_00064580:
  tmp_f1 = tmp_f1 * param_2 * 0.5;
  g_unk_010aaeac = -(((float)(tmp_i2 % tmp_i4) - param_1 * 0.5) * 0.5) * 30.0;
  g_unk_010aaeb0 = tmp_f1 * 30.0;
  g_unk_010aaeb4 = -tmp_f1 * 30.0;
  g_unk_010aaec4 = g_unk_010aaec4 -
                 (float)((long double)tmp_d6 * (tmp_l5 / (long double)5.0 + (long double)10.0)) * 0.5;
  return;
}

uint32_t CG_SpawnSmokeSprite(int param_1,float param_2)
{
  float tmp_f1;
  float tmp_f2;
  int *tmp_pi3;
  int tmp_i4;
  uint tmp_u5;
  uint tmp_u6;
  uint32_t *tmp_pu7;
  int *tmp_pi8;
  bool tmp_b9;
  float local_60;
  float local_5c;
  float local_58;
  uint8_t local_54 [8];
  float local_4c;
  int local_48;
  int local_44;
  int local_40;
  uint32_t uStack_14;
  
  tmp_pi3 = firstfreesmokesprite;
  uStack_14 = 0x646e9;
  if (SmokeSpriteCount < 0x200) {
    tmp_pi8 = (int *)*firstfreesmokesprite;
    if (lastusedsmokesprite != (int *)0x0) {
      *lastusedsmokesprite = (int)firstfreesmokesprite;
      firstfreesmokesprite = tmp_pi8;
      tmp_pi8 = firstfreesmokesprite;
    }
    firstfreesmokesprite = tmp_pi8;
    tmp_pi3[1] = (int)lastusedsmokesprite;
    SmokeSpriteCount = SmokeSpriteCount + 1;
    *tmp_pi3 = 0;
    tmp_pi3[0xe] = param_1;
    lastusedsmokesprite = tmp_pi3;
    tmp_pi3[2] = *(int *)(param_1 + 0x99c);
    tmp_pi3[3] = *(int *)(param_1 + 0x9a0);
    tmp_pi3[4] = *(int *)(param_1 + 0x9a4);
    tmp_i4 = rand();
    tmp_pi3[9] = (&bytedirs)[(tmp_i4 % 0xa2) * 3];
    tmp_i4 = rand();
    tmp_pi3[10] = (&g_unk_00149844)[(tmp_i4 % 0xa2) * 3];
    tmp_i4 = rand();
    tmp_f1 = (float)(&g_unk_00149848)[(tmp_i4 % 0xa2) * 3];
    tmp_pi3[0xb] = (int)(tmp_f1 * 0.5);
    if (*(int *)(param_1 + 0xe8) - 0x32U < 2) {
      tmp_pi3[5] = 0x437f0000;
      tmp_f2 = 7.0;
      tmp_pi3[6] = 0x43340000;
      tmp_pi3[7] = 0;
      tmp_pi3[8] = 0x3e800000;
    }
    else {
      tmp_pi3[5] = 0x3eb33333;
      tmp_f2 = 16.0;
      tmp_pi3[6] = 0x3eb33333;
      tmp_pi3[7] = 0x3eb33333;
      tmp_pi3[8] = 0x3f4ccccd;
    }
    local_60 = (float)tmp_pi3[2];
    local_5c = (float)tmp_pi3[3];
    local_58 = (float)tmp_pi3[4];
    tmp_pi3[2] = (int)(param_2 * (float)tmp_pi3[9] + local_60);
    tmp_pi3[3] = (int)(param_2 * (float)tmp_pi3[10] + local_5c);
    tmp_pi3[4] = (int)(tmp_f1 * 0.5 * param_2 + local_58);
    tmp_pi3[0xc] = (int)((float)tmp_pi3[0xc] + param_2);
    tmp_pi3[0xd] = (int)(param_2 * 1.25 + tmp_f2);
    CG_Trace(local_54,&local_60,0,0,tmp_pi3 + 2,0xffffffff,1);
    if (local_4c != 1.0) {
      if ((float)tmp_pi3[0xc] < 24.0) {
        if ((int *)tmp_pi3[1] == (int *)0x0) {
          tmp_i4 = *tmp_pi3;
          tmp_pi8 = (int *)0x0;
          if (tmp_i4 == 0) {
            lastusedsmokesprite = (int *)0x0;
            goto LAB_0006496f;
          }
        }
        else {
          *(int *)tmp_pi3[1] = *tmp_pi3;
          tmp_i4 = *tmp_pi3;
          tmp_pi8 = (int *)tmp_pi3[1];
          if (tmp_i4 == 0) {
            lastusedsmokesprite = tmp_pi8;
            if (tmp_pi8 != (int *)0x0) {
              *tmp_pi8 = 0;
            }
            goto LAB_0006496f;
          }
        }
        *(int **)(tmp_i4 + 4) = tmp_pi8;
LAB_0006496f:
        tmp_b9 = ((uint)tmp_pi3 & 1) != 0;
        tmp_u6 = 0x3c;
        tmp_pi8 = tmp_pi3;
        if (tmp_b9) {
          *(uint8_t *)tmp_pi3 = 0;
          tmp_pi8 = (int *)((int)tmp_pi3 + 1);
          tmp_u6 = 0x3b;
        }
        if (((uint)tmp_pi8 & 2) != 0) {
          *(uint16_t *)tmp_pi8 = 0;
          tmp_u6 = tmp_u6 - 2;
          tmp_pi8 = (int *)((int)tmp_pi8 + 2);
        }
        tmp_u5 = 0;
        do {
          *(uint32_t *)((int)tmp_pi8 + tmp_u5) = 0;
          *(uint32_t *)((int)tmp_pi8 + tmp_u5 + 4) = 0;
          tmp_u5 = tmp_u5 + 8;
        } while (tmp_u5 < (tmp_u6 & 0xfffffff8));
        tmp_pu7 = (uint32_t *)((int)tmp_pi8 + tmp_u5);
        if ((tmp_u6 & 4) != 0) {
          *tmp_pu7 = 0;
          tmp_pu7 = tmp_pu7 + 1;
        }
        if ((tmp_u6 & 2) != 0) {
          *(uint16_t *)tmp_pu7 = 0;
          tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
        }
        if (tmp_b9) {
          *(uint8_t *)tmp_pu7 = 0;
        }
        SmokeSpriteCount = SmokeSpriteCount + -1;
        *tmp_pi3 = (int)firstfreesmokesprite;
        firstfreesmokesprite = tmp_pi3;
        return 0;
      }
      tmp_pi3[2] = local_48;
      tmp_pi3[3] = local_44;
      tmp_pi3[4] = local_40;
    }
    *(int *)(param_1 + 0x260) = *(int *)(param_1 + 0x260) + 1;
  }
  return 1;
}

void CG_RenderSmokeGrenadeSmoke(int param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint8_t local_54 [4];
  int local_50;
  uint32_t local_48;
  uint32_t local_44;
  uint32_t local_40;
  
  tmp_i4 = *(int *)(param_1 + 0x10c);
  if (tmp_i4 != 0x10) {
    if (tmp_i4 < 0x11) {
      if ((tmp_i4 == -1) && (tmp_i4 = lastusedsmokesprite, 0 < *(int *)(param_1 + 0x260))) {
        for (; tmp_i4 != 0; tmp_i4 = *(int *)(tmp_i4 + 4)) {
          if (*(int *)(tmp_i4 + 0x38) == param_1) {
            *(uint32_t *)(tmp_i4 + 0x38) = 0;
            *(int *)(param_1 + 0x260) = *(int *)(param_1 + 0x260) + -1;
          }
        }
      }
    }
    else {
      if (((*(int *)(param_1 + 0x834) == 0) || (*(int *)(param_1 + 0xc) != 0)) ||
         ((*(int *)(param_1 + 0x94) != 0x3fe &&
          (tmp_i5 = VectorCompare(param_1 + 0x7b8,param_1 + 0x794), tmp_i5 == 0)))) {
        *(uint32_t *)(param_1 + 0x99c) = *(uint32_t *)(param_1 + 0x794);
        *(uint32_t *)(param_1 + 0x9a0) = *(uint32_t *)(param_1 + 0x798);
        *(float *)(param_1 + 0x9a4) = *(float *)(param_1 + 0x79c) + 32.0;
        CG_Trace(local_54,param_1 + 0x18,0,0,param_1 + 0x99c,0xffffffff,1);
        tmp_u3 = 2;
        if (local_50 == 0) {
          tmp_u3 = 1;
          *(uint32_t *)(param_1 + 0x99c) = local_48;
          *(uint32_t *)(param_1 + 0x9a0) = local_44;
          *(uint32_t *)(param_1 + 0x9a4) = local_40;
        }
        *(uint32_t *)(param_1 + 0x834) = tmp_u3;
      }
      trap_S_AddLoopingSound
                (param_1 + 0x794,&vec3_origin,*(uint32_t *)(param_2 + 0x1758),
                 (int)ROUND(((float)tmp_i4 / 640.0) * 84.0 + 16.0),0);
      if (((*(int *)(param_1 + 0x834) != 2) && (g_unk_010906e4 != 0)) &&
         (*(int *)(param_1 + 0x7dc) != g_unk_010906e0)) {
        tmp_f2 = (float)(g_unk_010906dc + *(int *)(param_1 + 0x248));
        tmp_i4 = (int)ROUND(tmp_f2 / 100.0);
        tmp_f1 = (float)tmp_i4 * 100.0;
        *(int *)(param_1 + 0x248) = (int)ROUND(tmp_f2 - tmp_f1);
        *(int *)(param_1 + 0x7dc) = g_unk_010906e0;
        if (tmp_i4 != 0) {
          if (tmp_i4 == 1) {
            tmp_i4 = CG_SpawnSmokeSprite(param_1,0);
            if (tmp_i4 == 0) {
              CG_SpawnSmokeSprite(param_1,0);
            }
          }
          else {
            for (; 0.0 < tmp_f1; tmp_f1 = tmp_f1 - 100.0) {
              tmp_i4 = CG_SpawnSmokeSprite(param_1,((float)g_unk_010906dc * 78.0) / 1000.0);
              if (tmp_i4 == 0) {
                CG_SpawnSmokeSprite(param_1,((float)g_unk_010906dc * 78.0) / 1000.0);
              }
            }
          }
        }
      }
    }
    return;
  }
  *(uint32_t *)(param_1 + 0x248) = 0;
  *(uint32_t *)(param_1 + 0x260) = 0;
  *(uint32_t *)(param_1 + 0x7dc) = 0;
  *(uint32_t *)(param_1 + 0x834) = 0;
  return;
}

void CG_Bomb(int param_1)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  bool tmp_b3;
  float local_238;
  float local_234;
  float local_230;
  uint8_t local_22c [12];
  uint32_t local_220;
  uint32_t local_21c;
  uint32_t local_218;
  uint local_1f4 [10];
  uint8_t local_1cc [12];
  uint8_t local_1c0 [52];
  uint32_t local_18c;
  uint32_t local_188;
  uint32_t local_184;
  uint32_t local_170;
  uint32_t local_16c;
  uint32_t local_168;
  uint32_t local_108 [7];
  uint8_t local_ec [76];
  uint32_t local_a0;
  float local_9c;
  float local_98;
  uint32_t local_84;
  uint32_t local_80;
  uint32_t local_7c;
  uint32_t local_58;
  byte local_54;
  uint8_t local_53;
  byte local_52;
  uint8_t local_51;
  
  if ((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3) ||
     (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95a8) != 0)) {
    tmp_u2 = 0;
    do {
      *(uint32_t *)((int)local_1f4 + tmp_u2) = 0;
      *(uint32_t *)((int)local_1f4 + tmp_u2 + 4) = 0;
      tmp_u2 = tmp_u2 + 8;
    } while (tmp_u2 < 0xe8);
    tmp_u1 = *(uint32_t *)(param_1 + 0x68);
    *(uint32_t *)((int)local_1f4 + tmp_u2) = 0;
    local_1f4[8] = *(uint32_t *)(param_1 + 0x6c);
    local_1f4[9] = *(uint32_t *)(param_1 + 0x70);
    local_1f4[7] = tmp_u1;
    PerpendicularVector(local_1cc,local_1f4 + 7);
    CrossProduct(local_1f4 + 7,local_1cc,local_1c0);
    local_1f4[2] = GHIDRA_FIELD(cg_weapons, 302856, 4);
    local_18c = *(uint32_t *)(param_1 + 0x794);
    local_1f4[1] = GHIDRA_FIELD(cg_weapons, 302900, 4) | 0x10;
    local_188 = *(uint32_t *)(param_1 + 0x798);
    local_184 = *(uint32_t *)(param_1 + 0x79c);
    local_170 = local_18c;
    local_16c = local_188;
    local_168 = local_184;
    CG_AddRefEntityWithPowerups(local_1f4,*(uint32_t *)(param_1 + 0xe4),0,param_1,&vec3_origin);
    if (*(int *)(param_1 + 0x10c) != 0) {
      tmp_b3 = *(int *)(param_1 + 0x10c) == 1;
      if ((*(int *)(cgs + *(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x9494) !=
           *(int *)(param_1 + 0x108)) &&
         ((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3 ||
          (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x95a8) == 0)))) {
        if ((cgs[*(int *)(g_unk_01047b00 + 0xcc) * 0x1a4 + 0x958c] & 0x10) == 0) {
          return;
        }
        tmp_b3 = true;
      }
      tmp_u2 = 0;
      do {
        *(uint32_t *)((int)local_108 + tmp_u2) = 0;
        *(uint32_t *)((int)local_108 + tmp_u2 + 4) = 0;
        tmp_u2 = tmp_u2 + 8;
      } while (tmp_u2 < 0xe8);
      tmp_u1 = *(uint32_t *)(param_1 + 0x794);
      *(uint32_t *)((int)local_108 + tmp_u2) = 0;
      local_9c = *(float *)(param_1 + 0x798);
      local_98 = *(float *)(param_1 + 0x79c);
      local_238 = *(float *)(param_1 + 0x68) * 4096.0 + *(float *)(param_1 + 0x794);
      local_234 = *(float *)(param_1 + 0x6c) * 4096.0 + local_9c;
      local_230 = *(float *)(param_1 + 0x70) * 4096.0 + local_98;
      local_a0 = tmp_u1;
      trap_CM_BoxTrace(local_22c,param_1 + 0x794,&local_238,0,0,0,0x6000001);
      local_58 = GHIDRA_FIELD(cgs, 67956, 4);
      local_108[0] = 5;
      local_108[1] = 0x10;
      local_84 = local_220;
      local_80 = local_21c;
      local_7c = local_218;
      if (*(int *)(param_1 + 0x108) == 1) {
        local_54 = -!tmp_b3 | 0x32;
        local_52 = 0;
      }
      else {
        local_52 = -!tmp_b3 | 0x32;
        local_54 = 0;
      }
      local_53 = 0;
      local_51 = 0xff;
      AxisClear(local_ec);
      trap_R_AddRefEntityToScene(local_108);
    }
  }
  return;
}

void CG_Cabinet_part_6(int param_1,int param_2)
{
  float *pfVar1;
  uint tmp_u2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  float *pfVar5;
  uint8_t *tmp_pu6;
  uint8_t *tmp_pu7;
  float local_224;
  float local_220;
  float local_21c;
  uint8_t local_218 [36];
  float local_1f4 [60];
  uint local_104 [2];
  float local_fc;
  float local_f8;
  float local_f4;
  uint8_t local_ec [76];
  float local_a0;
  float local_9c;
  float local_98;
  float local_84;
  float local_80;
  float local_7c;
  uint32_t uStack_14;
  
  tmp_u2 = 0;
  uStack_14 = 0x673fb;
  do {
    *(uint32_t *)((int)local_1f4 + tmp_u2) = 0;
    *(uint32_t *)((int)local_1f4 + tmp_u2 + 4) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0xe8);
  *(uint32_t *)((int)local_1f4 + tmp_u2) = 0;
  pfVar1 = local_1f4 + 0x3b;
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)pfVar1 + tmp_u2) = 0;
    *(uint32_t *)((int)local_104 + tmp_u2) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0xe8);
  local_1f4[3] = *(float *)(param_1 + 0x794);
  local_1f4[4] = *(float *)(param_1 + 0x798);
  local_1f4[0x1c] = *(float *)(param_1 + 0x79c);
  *(uint32_t *)((int)pfVar1 + tmp_u2) = 0;
  local_1f4[2] = *(float *)(cabinetInfo + param_2 * 0x3c + 0x38);
  local_1f4[5] = local_1f4[0x1c] + 16.0;
  local_1f4[1] = 1.4013e-45;
  local_1f4[0x1a] = local_1f4[3];
  local_1f4[0x1b] = local_1f4[4];
  local_1f4[0x21] = local_1f4[3];
  local_1f4[0x22] = local_1f4[4];
  local_1f4[0x23] = local_1f4[0x1c];
  AnglesToAxis(param_1 + 0x7a0,local_1f4 + 7);
  tmp_i3 = *(int *)(param_1 + 0xfc);
  if (tmp_i3 == -9999) {
    tmp_u2 = 6;
  }
  else {
    tmp_u2 = (uint)ROUND(((float)tmp_i3 / (float)*(int *)(param_1 + 0x100)) * 6.0);
    if (tmp_u2 == 0) {
      tmp_u2 = (uint)(tmp_i3 != 0);
    }
    if ((int)tmp_u2 < 1) goto LAB_000676da;
  }
  pfVar5 = &local_224;
  tmp_pu6 = local_ec;
  tmp_pu7 = local_218;
  tmp_i3 = 0;
  tmp_pu4 = (uint32_t *)(cabinetInfo + param_2 * 0x3c + 0x1c);
  do {
    local_104[1] = *tmp_pu4;
    tmp_i3 = tmp_i3 + 1;
    trap_R_LerpTag(pfVar5,local_1f4,tmp_pu4[-7],0,tmp_u2,pfVar5,tmp_pu6,tmp_pu7);
    local_a0 = local_1f4[0xd] * local_21c +
               local_220 * local_1f4[10] + local_224 * local_1f4[7] + local_1f4[0x1a];
    local_9c = local_1f4[0xe] * local_21c +
               local_1f4[0xb] * local_220 + local_1f4[8] * local_224 + local_1f4[0x1b];
    local_98 = local_21c * local_1f4[0xf] +
               local_1f4[0xc] * local_220 + local_1f4[9] * local_224 + local_1f4[0x1c];
    MatrixMultiply(tmp_pu7,local_1f4 + 7,tmp_pu6);
    local_104[0] = local_104[0] | 1;
    local_84 = local_a0;
    local_80 = local_9c;
    local_7c = local_98;
    local_fc = local_a0;
    local_f8 = local_9c;
    local_f4 = local_98;
    trap_R_AddRefEntityToScene(pfVar1);
    tmp_pu4 = tmp_pu4 + 1;
  } while (tmp_i3 < (int)tmp_u2);
LAB_000676da:
  trap_R_AddRefEntityToScene(local_1f4);
  return;
}

void CG_PositionEntityOnTag
               (int param_1,int param_2,uint32_t param_3,uint32_t param_4,float *param_5)

{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float local_4c;
  float local_48;
  float local_44;
  uint8_t local_40 [48];
  
  trap_R_LerpTag(&local_4c,param_2,param_3,param_4);
  tmp_f1 = *(float *)(param_2 + 0x68);
  *(float *)(param_1 + 0x68) = tmp_f1;
  tmp_f2 = *(float *)(param_2 + 0x6c);
  *(float *)(param_1 + 0x6c) = tmp_f2;
  tmp_f3 = *(float *)(param_2 + 0x70);
  *(float *)(param_1 + 0x70) = tmp_f3;
  if (param_5 != (float *)0x0) {
    local_4c = local_4c + *param_5;
    local_48 = local_48 + param_5[1];
    local_44 = local_44 + param_5[2];
  }
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
  MatrixMultiply(local_40,param_2 + 0x1c,param_1 + 0x1c);
  return;
}

void CG_SetEntitySoundPosition(uint32_t *param_1)
{
  int tmp_i1;
  float local_18;
  float local_14;
  float local_10;
  
  if (param_1[0x2d] != 0xffffff) {
    trap_S_UpdateEntityPosition(*param_1,param_1 + 0x1e5);
    return;
  }
  tmp_i1 = param_1[0x29] * 0xc;
  local_18 = (float)param_1[0x1e5] + *(float *)(cgs + tmp_i1 + 0x880c);
  local_14 = (float)param_1[0x1e6] + *(float *)(cgs + tmp_i1 + 0x8810);
  local_10 = (float)param_1[0x1e7] + *(float *)(cgs + tmp_i1 + 0x8814);
  trap_S_UpdateEntityPosition(*param_1,&local_18);
  return;
}

void CG_ProcessEntity(int *param_1)
{
  float *pfVar1;
  float tmp_f2;
  uint16_t tmp_u3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint tmp_u8;
  int tmp_i9;
  uint32_t *tmp_pu10;
  uint8_t *tmp_pu11;
  int tmp_i12;
  int *tmp_pi13;
  uint32_t *tmp_pu14;
  uint tmp_u15;
  int *tmp_pi16;
  int tmp_i17;
  int tmp_i18;
  bool tmp_b19;
  long double tmp_l20;
  int local_134;
  int local_130;
  float local_114;
  float local_110;
  float local_10c;
  uint8_t local_108 [4];
  uint local_104;
  float local_100 [24];
  int local_a0;
  int local_9c;
  int local_98;
  int local_94;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  float local_68;
  uint local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint8_t local_54;
  uint8_t local_53;
  uint8_t local_52;
  uint8_t local_51;
  int local_30;
  int local_2c;
  uint local_24;
  
  tmp_f5 = g_unk_01091a5c;
  tmp_f2 = g_unk_01091a58;
  tmp_i6 = g_unk_010906e0;
  tmp_u15 = param_1[1];
  switch(tmp_u15) {
  case 0:
  case 0x12:
  case 0x13:
  case 0x29:
    tmp_i6 = param_1[0x29];
    if (tmp_i6 == 0) {
      return;
    }
    tmp_pu10 = (uint32_t *)local_108;
    tmp_u15 = 0;
    do {
      *(uint32_t *)((int)tmp_pu10 + tmp_u15) = 0;
      *(uint32_t *)((int)local_100 + (tmp_u15 - 4)) = 0;
      tmp_u15 = tmp_u15 + 8;
    } while (tmp_u15 < 0xe8);
    *(uint32_t *)((int)tmp_pu10 + tmp_u15) = 0;
    local_94 = param_1[0x2c];
    if (local_94 == 0) {
      local_78 = 0;
    }
    else {
      local_78 = local_94 + -1;
      local_68 = 1.0 - g_unk_010906d0;
      if (param_1[0x15] != 0) {
        local_2c = param_1[0x16];
        local_30 = param_1[0x15];
      }
    }
    local_a0 = param_1[0x1e5];
    local_9c = param_1[0x1e6];
    local_98 = param_1[0x1e7];
    local_84 = local_a0;
    local_80 = local_9c;
    local_7c = local_98;
    local_100[0] = (float)CG_GetGameModel(tmp_i6);
    if (*param_1 == *(int *)(g_unk_01047b00 + 0xcc)) {
      local_104 = local_104 | 2;
    }
    if (((param_1[1] == 0x29) && (*(int *)(g_unk_01047b00 + 0xcc) == param_1[0x23])) &&
       (*(int *)(g_unk_01047b00 + 0x43c) != 0)) {
      AnglesToAxis(&g_unk_010907ac,local_100 + 5);
    }
    else {
      AnglesToAxis(param_1 + 0x1e8,local_100 + 5);
    }
    if (param_1[1] == 0x12) {
      tmp_f2 = (float)param_1[0x20];
      local_100[5] = local_100[5] * tmp_f2;
      local_100[0x17] = 1.4013e-45;
      local_100[6] = local_100[6] * tmp_f2;
      local_100[7] = tmp_f2 * local_100[7];
      tmp_f2 = (float)param_1[0x21];
      local_100[8] = local_100[8] * tmp_f2;
      local_100[9] = local_100[9] * tmp_f2;
      local_100[10] = tmp_f2 * local_100[10];
      tmp_f2 = (float)param_1[0x22];
      local_100[0xb] = local_100[0xb] * tmp_f2;
      local_100[0xc] = local_100[0xc] * tmp_f2;
      local_100[0xd] = tmp_f2 * local_100[0xd];
      if (param_1[0xc] != 0) {
        local_24 = local_24 | 0x10;
      }
      tmp_i6 = param_1[0x3c];
      if (tmp_i6 != 0) {
        tmp_i17 = param_1[0x212];
        if (g_unk_010906e0 < tmp_i17) {
          local_78 = param_1[0x2c];
          local_134 = param_1[0x3b];
        }
        else {
          tmp_i9 = param_1[0x211];
          local_134 = param_1[0x3b];
          param_1[0x20f] = tmp_i17;
          param_1[0x20e] = tmp_i9;
          tmp_i12 = tmp_i6 + local_134;
          local_78 = param_1[0x2c];
          while ((tmp_i17 <= g_unk_010906e0 && ((param_1[0x42] != 1 || (local_78 + tmp_i9 != tmp_i12)))))
          {
            tmp_i9 = tmp_i9 + 1;
            param_1[0x211] = tmp_i9;
            tmp_i17 = tmp_i17 + param_1[0x3a];
            param_1[0x212] = tmp_i17;
            if (tmp_i12 <= tmp_i9) {
              tmp_i9 = local_134;
              if (param_1[0x2b] != 0) {
                param_1[0x20e] = tmp_i12 + -1;
                tmp_i9 = tmp_i12 + -1;
              }
              param_1[0x211] = tmp_i9;
            }
          }
        }
        tmp_i9 = param_1[0x20f];
        if (tmp_i9 == tmp_i17) {
          local_68 = 0.0;
        }
        else {
          local_68 = 1.0 - (float)(g_unk_010906e0 - tmp_i9) / (float)(tmp_i17 - tmp_i9);
        }
        param_1[0x214] = (int)local_68;
        local_94 = local_78 + param_1[0x211];
        if (local_134 + tmp_i6 <= local_94) {
          local_94 = local_94 - tmp_i6;
        }
        local_78 = local_78 + param_1[0x20e];
        if (local_134 + tmp_i6 <= local_78) {
          local_78 = local_78 - tmp_i6;
        }
      }
      if ((param_1[0x97] != 0) && (param_1[0x42] != 1)) {
        local_68 = 0.0;
        param_1[0x20e] = param_1[0x211];
        param_1[0x20f] = param_1[0x212];
        param_1[0x211] = param_1[0x3b];
        param_1[0x212] = g_unk_010906e0;
        local_78 = local_94;
        local_94 = param_1[0x3b];
      }
      param_1[0x97] = (uint)(param_1[0x8f] != param_1[0x47]);
      if (param_1[0x2a] != 0) {
        local_5c = *(uint32_t *)(cgs + param_1[0x2a] * 4 + 0x7bc8);
      }
    }
    if (param_1[0x39] == 2) {
      local_58 = GHIDRA_FIELD(cgs, 68892, 4);
    }
    tmp_u15 = 0xec;
    trap_R_AddRefEntityToScene(tmp_pu10);
    tmp_pi13 = param_1 + 0x227;
    tmp_b19 = ((uint)tmp_pi13 & 1) != 0;
    if (tmp_b19) {
      tmp_pi13 = (int *)((int)param_1 + 0x89d);
      tmp_u15 = 0xeb;
      tmp_pu10 = (uint32_t *)((int)local_108 + 1);
      *(uint8_t *)(param_1 + 0x227) = local_108[0];
    }
    tmp_pi16 = tmp_pi13;
    if (((uint)tmp_pi13 & 2) != 0) {
      tmp_u3 = *(uint16_t *)tmp_pu10;
      tmp_pi16 = (int *)((int)tmp_pi13 + 2);
      tmp_pu10 = (uint32_t *)((int)tmp_pu10 + 2);
      tmp_u15 = tmp_u15 - 2;
      *(uint16_t *)tmp_pi13 = tmp_u3;
    }
    tmp_u8 = 0;
    do {
      *(uint32_t *)((int)tmp_pi16 + tmp_u8) = *(uint32_t *)((int)tmp_pu10 + tmp_u8);
      *(uint32_t *)((int)tmp_pi16 + tmp_u8 + 4) = *(uint32_t *)((int)tmp_pu10 + tmp_u8 + 4);
      tmp_u8 = tmp_u8 + 8;
    } while (tmp_u8 < (tmp_u15 & 0xfffffff8));
    goto LAB_00068f2f;
  case 1:
  case 0x26:
    if ((g_unk_010abd78 == 0) || (g_unk_010aabf8 == 0)) {
      CG_Player(param_1);
    }
    break;
  case 2:
    CG_Item();
    break;
  case 3:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x1a:
    CG_Missile();
    break;
  case 4:
  case 0xf:
  case 0x21:
    tmp_pu10 = (uint32_t *)local_108;
    tmp_u15 = 0;
    do {
      *(uint32_t *)((int)tmp_pu10 + tmp_u15) = 0;
      *(uint32_t *)((int)local_100 + (tmp_u15 - 4)) = 0;
      tmp_u15 = tmp_u15 + 8;
    } while (tmp_u15 < 0xe8);
    tmp_i6 = param_1[0x1e5];
    *(uint32_t *)((int)tmp_pu10 + tmp_u15) = 0;
    local_9c = param_1[0x1e6];
    local_98 = param_1[0x1e7];
    local_a0 = tmp_i6;
    local_84 = tmp_i6;
    local_80 = local_9c;
    local_7c = local_98;
    AnglesToAxis(param_1 + 0x1e8,local_100 + 5);
    local_104 = 0;
    local_60 = 0;
    if (param_1[0x2d] == 0xffffff) {
      local_100[0] = *(float *)(cgs + param_1[0x29] * 4 + 0x840c);
    }
    else {
      local_100[0] = (float)CG_GetGameModel(param_1[0x29]);
    }
    if ((param_1[0x3d] & 1U) != 0) {
      tmp_f2 = (float)param_1[0x20];
      local_100[5] = local_100[5] * tmp_f2;
      local_100[0x17] = 1.4013e-45;
      local_100[6] = local_100[6] * tmp_f2;
      local_100[7] = tmp_f2 * local_100[7];
      tmp_f2 = (float)param_1[0x21];
      local_100[8] = local_100[8] * tmp_f2;
      local_100[9] = local_100[9] * tmp_f2;
      local_100[10] = tmp_f2 * local_100[10];
      tmp_f2 = (float)param_1[0x22];
      local_100[0xb] = local_100[0xb] * tmp_f2;
      local_100[0xc] = local_100[0xc] * tmp_f2;
      local_100[0xd] = tmp_f2 * local_100[0xd];
    }
    if (param_1[1] == 0xf) {
      local_104 = local_104 | 1;
    }
    if (param_1[0x39] == 2) {
      local_58 = GHIDRA_FIELD(cgs, 68892, 4);
    }
    if ((param_1[0x2a] == 0) || ((param_1[0x3d] & 2U) != 0)) goto LAB_00069141;
    local_100[0] = (float)CG_GetGameModel(param_1[0x2a]);
    tmp_i6 = param_1[0x2c];
    tmp_i17 = param_1[0x3c];
    local_94 = tmp_i6;
    if (tmp_i17 != 0) {
      local_134 = param_1[0x212];
      tmp_i9 = local_134;
      if (g_unk_010906e0 < local_134) {
        local_130 = param_1[0x20e];
        local_94 = param_1[0x211];
        tmp_i18 = tmp_i17 + param_1[0x3b];
        local_134 = param_1[0x20f];
      }
      else {
        tmp_i12 = param_1[0x3b];
        param_1[0x20f] = local_134;
        local_130 = param_1[0x211];
        tmp_i18 = tmp_i12 + tmp_i17;
        param_1[0x20e] = local_130;
        local_94 = local_130;
        while (tmp_i9 <= g_unk_010906e0) {
          local_94 = local_94 + 1;
          param_1[0x211] = local_94;
          tmp_i9 = tmp_i9 + param_1[0x3a];
          param_1[0x212] = tmp_i9;
          if (tmp_i18 <= local_94) {
            param_1[0x211] = tmp_i12;
            local_94 = tmp_i12;
          }
        }
      }
      if (local_134 == tmp_i9) {
        local_68 = 0.0;
      }
      else {
        local_68 = 1.0 - (float)(g_unk_010906e0 - local_134) / (float)(tmp_i9 - local_134);
      }
      param_1[0x214] = (int)local_68;
      local_94 = local_94 + tmp_i6;
      if (tmp_i18 <= local_94) {
        local_94 = local_94 - tmp_i17;
      }
      local_78 = tmp_i6 + local_130;
      if (tmp_i18 <= local_78) {
        local_78 = local_78 - tmp_i17;
      }
    }
    if (param_1[0x97] != 0) {
      local_68 = 0.0;
      param_1[0x20e] = param_1[0x211];
      param_1[0x20f] = param_1[0x212];
      param_1[0x211] = param_1[0x3b];
      param_1[0x212] = g_unk_010906e0;
      local_78 = local_94;
      local_94 = param_1[0x3b];
    }
    tmp_u15 = 0xec;
    param_1[0x97] = (uint)(param_1[0x8f] != param_1[0x47]);
    trap_R_AddRefEntityToScene(tmp_pu10);
    tmp_pi13 = param_1 + 0x227;
    tmp_b19 = ((uint)tmp_pi13 & 1) != 0;
    if (tmp_b19) {
      tmp_pi13 = (int *)((int)param_1 + 0x89d);
      tmp_u15 = 0xeb;
      tmp_pu10 = (uint32_t *)((int)local_108 + 1);
      *(uint8_t *)(param_1 + 0x227) = local_108[0];
    }
    tmp_pi16 = tmp_pi13;
    if (((uint)tmp_pi13 & 2) != 0) {
      tmp_u3 = *(uint16_t *)tmp_pu10;
      tmp_pi16 = (int *)((int)tmp_pi13 + 2);
      tmp_pu10 = (uint32_t *)((int)tmp_pu10 + 2);
      tmp_u15 = tmp_u15 - 2;
      *(uint16_t *)tmp_pi13 = tmp_u3;
    }
    tmp_u8 = 0;
    do {
      *(uint32_t *)((int)tmp_pi16 + tmp_u8) = *(uint32_t *)((int)tmp_pu10 + tmp_u8);
      *(uint32_t *)((int)tmp_pi16 + tmp_u8 + 4) = *(uint32_t *)((int)tmp_pu10 + tmp_u8 + 4);
      tmp_u8 = tmp_u8 + 8;
    } while (tmp_u8 < (tmp_u15 & 0xfffffff8));
    goto LAB_00068f2f;
  case 5:
    tmp_u15 = 0;
    do {
      *(uint32_t *)((int)local_108 + tmp_u15) = 0;
      *(uint32_t *)((int)local_100 + (tmp_u15 - 4)) = 0;
      tmp_u15 = tmp_u15 + 8;
    } while (tmp_u15 < 0xe8);
    tmp_i6 = param_1[6];
    *(uint32_t *)((int)local_108 + tmp_u15) = 0;
    local_9c = param_1[7];
    local_98 = param_1[8];
    local_84 = param_1[0x1a];
    local_80 = param_1[0x1b];
    local_7c = param_1[0x1c];
    local_a0 = tmp_i6;
    AxisClear(local_100 + 5);
    local_108 = (uint8_t  [4])0x5;
    if (param_1[0x3b] == 1) {
      local_58 = GHIDRA_FIELD(cgs, 67960, 4);
    }
    else {
      local_58 = GHIDRA_FIELD(cgs, 67956, 4);
    }
    local_51 = 0xff;
    local_54 = (uint8_t)(short)ROUND((float)param_1[0x20] * 255.0);
    local_104 = 0x10;
    local_53 = (uint8_t)(short)ROUND((float)param_1[0x21] * 255.0);
    local_52 = (uint8_t)(short)ROUND((float)param_1[0x22] * 255.0);
    trap_R_AddRefEntityToScene(local_108);
    break;
  case 6:
    tmp_u15 = 0;
    do {
      *(uint32_t *)((int)local_108 + tmp_u15) = 0;
      *(uint32_t *)((int)local_100 + (tmp_u15 - 4)) = 0;
      tmp_u15 = tmp_u15 + 8;
    } while (tmp_u15 < 0xe8);
    tmp_i6 = param_1[0x1e5];
    *(uint32_t *)((int)local_108 + tmp_u15) = 0;
    pfVar1 = local_100 + 5;
    local_9c = param_1[0x1e6];
    local_98 = param_1[0x1e7];
    local_84 = param_1[0x1a];
    local_80 = param_1[0x1b];
    local_7c = param_1[0x1c];
    local_a0 = tmp_i6;
    ByteToDir(param_1[0x2f],pfVar1);
    PerpendicularVector(local_100 + 8,pfVar1);
    local_100[8] = vec3_origin - local_100[8];
    local_100[9] = g_unk_00c22b14 - local_100[9];
    local_100[10] = g_unk_00c22b18 - local_100[10];
    CrossProduct(pfVar1,local_100 + 8,local_100 + 0xb);
    local_94 = param_1[0x2c];
    local_108 = (uint8_t  [4])0x9;
    local_60 = (uint)ROUND((float)param_1[0x2b] * 0.00390625 * 360.0);
    trap_R_AddRefEntityToScene(local_108);
    break;
  case 7:
    if ((param_1[0x2b] != 0) && (param_1[0x98] <= g_unk_010906e0)) {
      tmp_u7 = CG_GetGameSound(param_1[0x2f]);
      trap_S_StartSound(0,*param_1,4,tmp_u7);
      tmp_i6 = g_unk_010906e0 + param_1[0x2c] * 100;
      tmp_i17 = param_1[0x2b];
      tmp_u15 = rand();
      tmp_f2 = (float)(tmp_u15 & 0x7fff) / 32767.0 - 0.5;
      param_1[0x98] = (int)ROUND((tmp_f2 + tmp_f2) * (float)(tmp_i17 * 100) + (float)tmp_i6);
    }
    break;
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0x1c:
  case 0x1d:
  case 0x24:
  case 0x25:
  case 0x37:
  case 0x39:
    break;
  case 0xd:
  case 0x1f:
    nitmod_DrawObjectiveHint(param_1);
    break;
  case 0xe:
    tmp_u15 = 0;
    do {
      *(uint32_t *)((int)local_108 + tmp_u15) = 0;
      *(uint32_t *)((int)local_100 + (tmp_u15 - 4)) = 0;
      tmp_u15 = tmp_u15 + 8;
    } while (tmp_u15 < 0xe8);
    tmp_i6 = param_1[0x1e5];
    *(uint32_t *)((int)local_108 + tmp_u15) = 0;
    local_9c = param_1[0x1e6];
    local_98 = param_1[0x1e7];
    local_a0 = tmp_i6;
    AnglesToAxis(param_1 + 0x1e8,local_100 + 5);
    local_104 = 0x10;
    if (param_1[0x2d] == 0xffffff) {
      local_100[0] = *(float *)(cgs + param_1[0x29] * 4 + 0x840c);
    }
    else {
      local_100[0] = (float)CG_GetGameModel(param_1[0x29]);
    }
    if (param_1[0x2a] != 0) {
      local_60 = 0;
      local_100[0] = (float)CG_GetGameModel(param_1[0x2a]);
      trap_R_AddRefEntityToScene(local_108);
      return;
    }
    goto LAB_00069141;
  case 0x10:
    if (GHIDRA_FIELD(cg_coronas, 12, 4) != 0) {
      tmp_u15 = param_1[0x27];
      local_114 = *(float *)(g_unk_010afbcc + 0x18) - (float)param_1[0x1e5];
      local_110 = *(float *)(g_unk_010afbcc + 0x1c) - (float)param_1[0x1e6];
      local_10c = *(float *)(g_unk_010afbcc + 0x20) - (float)param_1[0x1e7];
      tmp_l20 = (long double)VectorNormalize2(&local_114,&local_114);
      if (local_10c * *(float *)(g_unk_010afbcc + 0x2c) +
          local_110 * *(float *)(g_unk_010afbcc + 0x28) + local_114 * *(float *)(g_unk_010afbcc + 0x24)
          < -0.6) {
        if ((GHIDRA_FIELD(cg_coronas, 12, 4) != 2) && ((long double)(int)GHIDRA_FIELD(cg_coronafardist, 12, 4) < tmp_l20)) {
          return;
        }
      }
      else if (GHIDRA_FIELD(cg_coronas, 12, 4) != 2) {
        return;
      }
      CG_Trace(local_108,g_unk_010afbcc + 0x18,0,0,param_1 + 0x1e5,0xffffffff,0x2000001);
      trap_R_AddCoronaToScene
                (param_1 + 0x1e5,(float)(tmp_u15 & 0xff) / 255.0,(float)(tmp_u15 >> 8 & 0xff) / 255.0,
                 (float)((int)tmp_u15 >> 0x10 & 0xff) / 255.0,(float)param_1[0x3d] / 255.0,*param_1,
                 local_100[0] == 1.0);
    }
    break;
  case 0x11:
    tmp_pu10 = (uint32_t *)local_108;
    tmp_u15 = 0;
    do {
      *(uint32_t *)((int)tmp_pu10 + tmp_u15) = 0;
      *(uint32_t *)((int)local_100 + (tmp_u15 - 4)) = 0;
      tmp_u15 = tmp_u15 + 8;
    } while (tmp_u15 < 0xe8);
    tmp_i17 = param_1[0x20f];
    *(uint32_t *)((int)tmp_pu10 + tmp_u15) = 0;
    if (tmp_i17 == 0) {
      tmp_i17 = param_1[0x2c];
      param_1[0x20f] = g_unk_010906e0;
      param_1[0x212] = tmp_i6;
      param_1[0x219] = tmp_i17;
      if (param_1[0x42] == 1) {
        tmp_pu11 = multi_flagpoleAnims + tmp_i17 * 0x70;
        param_1[0x21b] = (int)tmp_pu11;
        param_1[0x21c] = tmp_i6 + *(int *)(multi_flagpoleAnims + tmp_i17 * 0x70 + 0x54);
      }
      else {
        tmp_pu11 = (uint8_t *)param_1[0x21b];
      }
      tmp_i6 = *(int *)(tmp_pu11 + 0x44);
      param_1[0x20e] = tmp_i6;
      param_1[0x211] = tmp_i6;
LAB_00069d25:
      if (param_1[0x21b] == 0) goto LAB_00069304;
    }
    else {
      tmp_i17 = param_1[0x2c];
      if (param_1[0x219] == tmp_i17) goto LAB_00069d25;
LAB_00069304:
      param_1[0x219] = tmp_i17;
      if (param_1[0x42] == 1) {
        tmp_i6 = *(int *)(multi_flagpoleAnims + tmp_i17 * 0x70 + 0x54);
        param_1[0x21b] = (int)(multi_flagpoleAnims + tmp_i17 * 0x70);
        param_1[0x21c] = tmp_i6 + param_1[0x212];
      }
    }
    tmp_u15 = 0xec;
    CG_RunLerpFrame(param_1,0,param_1 + 0x20e,0,0x3f800000);
    local_94 = param_1[0x211];
    local_78 = param_1[0x20e];
    local_68 = (float)param_1[0x214];
    local_a0 = param_1[0x1e5];
    local_9c = param_1[0x1e6];
    local_98 = param_1[0x1e7];
    local_84 = local_a0;
    local_80 = local_9c;
    local_7c = local_98;
    local_100[0] = (float)CG_GetGameModel(param_1[0x29]);
    AnglesToAxis(param_1 + 0x1e8,local_100 + 5);
    trap_R_AddRefEntityToScene(tmp_pu10);
    tmp_pi13 = param_1 + 0x227;
    tmp_b19 = ((uint)tmp_pi13 & 1) != 0;
    if (tmp_b19) {
      tmp_pi13 = (int *)((int)param_1 + 0x89d);
      tmp_u15 = 0xeb;
      tmp_pu10 = (uint32_t *)((int)local_108 + 1);
      *(uint8_t *)(param_1 + 0x227) = local_108[0];
    }
    tmp_pi16 = tmp_pi13;
    if (((uint)tmp_pi13 & 2) != 0) {
      tmp_u3 = *(uint16_t *)tmp_pu10;
      tmp_pi16 = (int *)((int)tmp_pi13 + 2);
      tmp_pu10 = (uint32_t *)((int)tmp_pu10 + 2);
      tmp_u15 = tmp_u15 - 2;
      *(uint16_t *)tmp_pi13 = tmp_u3;
    }
    tmp_u8 = 0;
    do {
      *(uint32_t *)((int)tmp_pi16 + tmp_u8) = *(uint32_t *)((int)tmp_pu10 + tmp_u8);
      *(uint32_t *)((int)tmp_pi16 + tmp_u8 + 4) = *(uint32_t *)((int)tmp_pu10 + tmp_u8 + 4);
      tmp_u8 = tmp_u8 + 8;
    } while (tmp_u8 < (tmp_u15 & 0xfffffff8));
    goto LAB_00068f2f;
  case 0x19:
  case 0x1e:
  case 0x28:
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x31:
  case 0x32:
  case 0x33:
  case 0x34:
  case 0x35:
  case 0x36:
  case 0x38:
    if (tmp_u15 < 0x3b) {
      return;
    }
  default:
    CG_Error("Bad entity type: %i\n",tmp_u15);
    break;
  case 0x1b:
    tmp_pu10 = (uint32_t *)local_108;
    tmp_u15 = 0;
    do {
      *(uint32_t *)((int)tmp_pu10 + tmp_u15) = 0;
      *(uint32_t *)((int)local_100 + (tmp_u15 - 4)) = 0;
      tmp_u15 = tmp_u15 + 8;
    } while (tmp_u15 < 0xe8);
    *(uint32_t *)((int)tmp_pu10 + tmp_u15) = 0;
    if (g_unk_010906f4 == 0) {
      local_a0 = *(int *)(g_unk_010afbcc + 0x18);
      local_9c = *(int *)(g_unk_010afbcc + 0x1c);
      local_98 = *(int *)(g_unk_010afbcc + 0x20);
      tmp_f4 = g_unk_010aad78;
      if (((byte)g_unk_010aad6c & 1) != 0) {
        tmp_f4 = -g_unk_010aad78;
      }
      tmp_f4 = tmp_f4 * g_unk_010aad68;
      param_1[0x1e8] = (int)(g_unk_010aad78 * g_unk_010aad68 * 0.005 + g_unk_01091a54);
      param_1[0x1e9] = (int)(tmp_f4 * 0.01 + tmp_f2);
      param_1[0x1ea] = (int)(tmp_f5 + tmp_f4 * 0.005);
      local_94 = param_1[0x2c];
      if (param_1[0x3d] == 0) {
        if (local_94 == 0) {
          local_104 = 0xc;
          local_78 = 0;
        }
        else {
          local_68 = 1.0 - g_unk_010906d0;
          local_78 = local_94 + -1;
        }
      }
      else {
        local_94 = param_1[0x3d] + local_94;
        local_68 = 1.0 - g_unk_010906d0;
        local_78 = local_94 + -1;
        local_104 = 0xc;
      }
    }
    else {
      local_a0 = param_1[0x1e5];
      local_94 = param_1[0x2c];
      local_9c = param_1[0x1e6];
      local_98 = param_1[0x1e7];
      local_84 = local_a0;
      local_80 = local_9c;
      local_7c = local_98;
      local_78 = local_94;
    }
    AnglesToAxis(param_1 + 0x1e8,local_100 + 5);
    local_104 = local_104 | 0x10;
    local_60 = g_unk_010906e0 >> 6 & 1;
    if (param_1[0x2d] == 0xffffff) {
      local_100[0] = *(float *)(cgs + param_1[0x29] * 4 + 0x840c);
    }
    else {
      local_100[0] = (float)CG_GetGameModel(param_1[0x29]);
    }
    if (param_1[0x39] == 2) {
      local_58 = GHIDRA_FIELD(cgs, 68892, 4);
    }
    if (param_1[0x2a] == 0) goto LAB_00069141;
    local_60 = 0;
    tmp_u15 = 0xec;
    local_100[0] = (float)CG_GetGameModel(param_1[0x2a]);
    local_94 = param_1[0x2c];
    trap_R_AddRefEntityToScene(tmp_pu10);
    tmp_pi13 = param_1 + 0x227;
    tmp_b19 = ((uint)tmp_pi13 & 1) != 0;
    if (tmp_b19) {
      tmp_pi13 = (int *)((int)param_1 + 0x89d);
      tmp_u15 = 0xeb;
      tmp_pu10 = (uint32_t *)((int)local_108 + 1);
      *(uint8_t *)(param_1 + 0x227) = local_108[0];
    }
    tmp_pi16 = tmp_pi13;
    if (((uint)tmp_pi13 & 2) != 0) {
      tmp_u3 = *(uint16_t *)tmp_pu10;
      tmp_pi16 = (int *)((int)tmp_pi13 + 2);
      tmp_pu10 = (uint32_t *)((int)tmp_pu10 + 2);
      tmp_u15 = tmp_u15 - 2;
      *(uint16_t *)tmp_pi13 = tmp_u3;
    }
    tmp_u8 = 0;
    do {
      *(uint32_t *)((int)tmp_pi16 + tmp_u8) = *(uint32_t *)((int)tmp_pu10 + tmp_u8);
      *(uint32_t *)((int)tmp_pi16 + tmp_u8 + 4) = *(uint32_t *)((int)tmp_pu10 + tmp_u8 + 4);
      tmp_u8 = tmp_u8 + 8;
    } while (tmp_u8 < (tmp_u15 & 0xfffffff8));
LAB_00068f2f:
    tmp_pu14 = (uint32_t *)((int)tmp_pi16 + tmp_u8);
    tmp_pu10 = (uint32_t *)((int)tmp_pu10 + tmp_u8);
    tmp_i6 = 0;
    if ((tmp_u15 & 4) != 0) {
      *tmp_pu14 = *tmp_pu10;
      tmp_i6 = 4;
    }
    if ((tmp_u15 & 2) != 0) {
      *(uint16_t *)((int)tmp_pu14 + tmp_i6) = *(uint16_t *)((int)tmp_pu10 + tmp_i6);
      tmp_i6 = tmp_i6 + 2;
    }
    if (tmp_b19) {
      *(uint8_t *)((int)tmp_pu14 + tmp_i6) = *(uint8_t *)((int)tmp_pu10 + tmp_i6);
    }
    break;
  case 0x20:
    tmp_u15 = 0;
    do {
      *(uint32_t *)((int)local_108 + tmp_u15) = 0;
      *(uint32_t *)((int)local_100 + (tmp_u15 - 4)) = 0;
      tmp_u15 = tmp_u15 + 8;
    } while (tmp_u15 < 0xe8);
    tmp_i6 = param_1[0x1e5];
    *(uint32_t *)((int)local_108 + tmp_u15) = 0;
    local_9c = param_1[0x1e6];
    local_98 = param_1[0x1e7];
    local_a0 = tmp_i6;
    local_84 = tmp_i6;
    local_80 = local_9c;
    local_7c = local_98;
    AnglesToAxis(param_1 + 0x1e8,local_100 + 5);
    local_104 = 0x10;
    if (param_1[0x29] != 0) {
      local_100[0] = *(float *)(cgs + param_1[0x29] * 4 + 0x840c);
      trap_R_AddRefEntityToScene(local_108);
    }
    if (param_1[0x2a] == 0) {
      return;
    }
    if (param_1[0x39] == 2) {
      local_58 = GHIDRA_FIELD(cgs, 68892, 4);
    }
    local_100[0] = *(float *)(cgs + param_1[0x2a] * 4 + 0x840c);
LAB_00069141:
    trap_R_AddRefEntityToScene(local_108);
    break;
  case 0x22:
    CG_Bomb();
    break;
  case 0x23:
    CG_Beam_2(param_1);
    break;
  case 0x27:
    if (param_1[0x26] < g_unk_010906e0 - param_1[0x265]) {
      param_1[0x265] = g_unk_010906e0;
      if (param_1[0x2a] == 0) {
        if (param_1[0x3d] == 3) {
          CG_ParticleSmoke(GHIDRA_FIELD(cgs, 68524, 4),param_1);
        }
        else {
          CG_ParticleSmoke(GHIDRA_FIELD(cgs, 68088, 4),param_1);
        }
      }
      else {
        CG_ParticleSmoke(*(uint32_t *)(cgs + param_1[0x2a] * 4 + 0x7b48),param_1);
      }
    }
    param_1[499] = g_unk_010906e0;
    break;
  case 0x2e:
    GHIDRA_FIELD(cgs, 33575844, 4) = param_1;
    break;
  case 0x2f:
    CG_Cabinet_part_6();
    break;
  case 0x30:
    CG_Cabinet_part_6();
    break;
  case 0x3a:
    nitmod_CheckArtilleryHint(param_1);
  }
  return;
}

uint32_t CG_Cabinet(uint32_t param_1,uint param_2)
{
  uint32_t tmp_u1;
  
  if (1 < param_2) {
    return param_1;
  }
  tmp_u1 = CG_Cabinet_part_6();
  return tmp_u1;
}

void CG_SetupCabinets(void)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  
  tmp_pu4 = (uint32_t *)(cabinetInfo + 0x34);
  do {
    tmp_u2 = trap_R_RegisterModel(*tmp_pu4);
    tmp_pu4[1] = tmp_u2;
    tmp_pu1 = tmp_pu4 + -6;
    do {
      tmp_pu3 = tmp_pu1;
      tmp_u2 = trap_R_RegisterModel(tmp_pu4[-7]);
      *tmp_pu3 = tmp_u2;
      tmp_pu1 = tmp_pu3 + 1;
    } while (tmp_pu3 + 1 != tmp_pu4);
    tmp_pu4 = tmp_pu3 + 0x10;
  } while (tmp_pu4 != (uint32_t *)(eventnames + 0xc));
  return;
}

void CG_BotDebugLine(uint32_t *param_1,uint32_t *param_2,uint32_t *param_3)
{
  uint32_t tmp_u1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i4 = CG_AllocLocalEntity();
  *(uint32_t *)(tmp_i4 + 8) = 6;
  tmp_i3 = g_unk_010906e0;
  *(int *)(tmp_i4 + 0x10) = g_unk_010906e0;
  tmp_f2 = (float)g_unk_010906e0 + (float)GHIDRA_FIELD(cg_railTrailTime, 8, 4);
  *(int *)(tmp_i4 + 0x14) = (int)ROUND(tmp_f2);
  *(float *)(tmp_i4 + 0x1c) = 1.0 / (float)((int)ROUND(tmp_f2) - tmp_i3);
  if (GHIDRA_FIELD(cgs, 67956, 4) == 0) {
    GHIDRA_FIELD(cgs, 67956, 4) = trap_R_RegisterShader("railCore");
  }
  *(uint32_t *)(tmp_i4 + 0x98) = 5;
  *(uint32_t *)(tmp_i4 + 0x148) = GHIDRA_FIELD(cgs, 67956, 4);
  *(float *)(tmp_i4 + 0x158) = (float)g_unk_010906e0 / 1000.0;
  *(uint32_t *)(tmp_i4 + 0x100) = *param_1;
  *(uint32_t *)(tmp_i4 + 0x104) = param_1[1];
  *(uint32_t *)(tmp_i4 + 0x108) = param_1[2];
  *(uint32_t *)(tmp_i4 + 0x11c) = *param_2;
  *(uint32_t *)(tmp_i4 + 0x120) = param_2[1];
  *(uint32_t *)(tmp_i4 + 0x124) = param_2[2];
  *(uint32_t *)(tmp_i4 + 0x6c) = *param_3;
  *(uint32_t *)(tmp_i4 + 0x70) = param_3[1];
  tmp_u1 = param_3[2];
  *(uint32_t *)(tmp_i4 + 0x78) = 0x3f800000;
  *(uint32_t *)(tmp_i4 + 0x74) = tmp_u1;
  AxisClear(tmp_i4 + 0xb4);
  return;
}

void CG_StartFootStepSound_isra_0_part_1(uint32_t *param_1,uint32_t param_2)
{
  trap_S_StartSound(0,*param_1,5,param_2);
  return;
}

void CG_MortarImpact_part_2(int param_1,float *param_2)
{
  long double tmp_l1;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  local_28 = *param_2 - *(float *)(g_unk_010afbcc + 0x18);
  local_24 = param_2[1] - *(float *)(g_unk_010afbcc + 0x1c);
  local_20 = param_2[2] - *(float *)(g_unk_010afbcc + 0x20);
  tmp_l1 = (long double)VectorNormalize(&local_28);
  if (((long double)1200.0 < tmp_l1) && (tmp_l1 < (long double)8000.0)) {
    local_34 = local_28 * 800.0 + *(float *)(g_unk_010afbcc + 0x18);
    local_30 = local_24 * 800.0 + *(float *)(g_unk_010afbcc + 0x1c);
    local_2c = local_20 * 800.0 + *(float *)(g_unk_010afbcc + 0x20);
    trap_S_StartSoundEx(&local_34,0xffffffff,2,GHIDRA_FIELD(cgs, 69144, 4),0x10);
  }
  if ((*(int *)(param_1 + 0xac) == *(int *)(g_unk_01047b00 + 0xcc)) && (g_unk_010b4564 != -2)) {
    g_unk_010b4568 = *param_2;
    g_unk_010b4564 = g_unk_010906e0;
    g_unk_010b456c = param_2[1];
    g_unk_010b4570 = param_2[2];
    g_unk_010b4574 = 0;
  }
  return;
}

void CG_PrecacheFXSounds(void)
{
  uint8_t *tmp_pu1;
  uint8_t **tmp_ppu2;
  uint8_t **tmp_ppu3;
  int tmp_i4;
  
  tmp_ppu2 = &g_ptr_s_sound_world_boardbreak_wav_00144890;
  do {
    if (0 < (int)tmp_ppu2[-4]) {
      tmp_i4 = 0;
      tmp_ppu3 = tmp_ppu2;
      do {
        tmp_i4 = tmp_i4 + 1;
        tmp_pu1 = (uint8_t *)trap_S_RegisterSound(*tmp_ppu3,0);
        tmp_ppu3[-3] = tmp_pu1;
        tmp_ppu3 = tmp_ppu3 + 1;
      } while (tmp_i4 < (int)tmp_ppu2[-4]);
    }
    tmp_ppu2 = tmp_ppu2 + 7;
  } while (tmp_ppu2 != (uint8_t **)&g_unk_00144938);
  return;
}

void CG_RubbleFx(uint32_t *param_1,float *param_2,int param_3,int param_4,int param_5,int param_6,
                int param_7,float param_8,float param_9)

{
  int tmp_i1;
  float tmp_f2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int local_78;
  uint local_74;
  float local_70;
  uint32_t local_6c;
  uint32_t local_68;
  float local_60;
  int local_5c;
  int local_50;
  uint8_t *local_4c;
  int local_34 [8];
  uint32_t uStack_14;
  
  uStack_14 = 0x6f349;
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)local_34 + tmp_u3) = 0;
    *(uint32_t *)((int)local_34 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0x18);
  tmp_f2 = (float)param_3;
  local_34[5] = (int)ROUND(tmp_f2 / 250.0);
  local_34[4] = (int)ROUND(tmp_f2 / 76.0);
  local_34[3] = (int)ROUND(tmp_f2 / 37.0);
  local_34[2] = (int)ROUND(tmp_f2 / 15.0);
  local_34[1] = (int)ROUND(tmp_f2 / 10.0);
  local_34[0] = (int)ROUND(tmp_f2 / 5.0);
  if (0x14 < local_34[0]) {
    local_34[0] = 0x14;
  }
  if (0xf < local_34[1]) {
    local_34[1] = 0xf;
  }
  if (10 < local_34[2]) {
    local_34[2] = 10;
  }
  if (param_4 == 0) {
    if (10 < local_34[0]) {
      local_34[0] = 10;
    }
    if (10 < local_34[1]) {
      local_34[1] = 10;
    }
  }
  tmp_i4 = local_34[5] + local_34[4] + local_34[3] + local_34[2] + local_34[1] + local_34[0];
  if (param_5 != 0) {
    trap_S_StartSound(param_1,0xffffffff,0,param_5);
  }
  local_4c = cgs;
  local_70 = 1.0;
  local_50 = 0;
  local_78 = 0;
  do {
    if (0 < local_34[local_78]) {
      local_68 = 0;
      local_6c = 0;
      local_74 = 0;
      do {
        switch(param_4) {
        case 0:
          local_68 = *(uint32_t *)("GLIBC_2_7" + (int)(local_4c + 5));
          if (local_78 == 0) {
            local_60 = 0.5;
            local_5c = -3000;
            local_6c = 3;
          }
          else {
            if (local_78 == 1) {
              local_60 = 0.6;
            }
            else {
              if (local_78 != 2) {
                local_5c = 0;
                if (local_78 == 3) {
                  local_60 = 0.5;
                  local_6c = 3;
                }
                else {
                  local_6c = 3;
                  local_60 = 1.0;
                }
                break;
              }
              local_60 = 0.7;
            }
            local_5c = -3000;
            local_6c = 3;
          }
          break;
        case 1:
          local_68 = GHIDRA_FIELD(cgs, 68636, 4);
          if ((local_78 == 5) || (local_68 = GHIDRA_FIELD(cgs, 68640, 4), (local_78 - 2U & 0xfffffffd) == 0)) {
            local_5c = 0;
            local_60 = 1.0;
            local_6c = 0;
          }
          else {
            if (local_78 != 1) goto _L78;
            local_60 = 0.5;
            local_5c = 0;
            local_6c = 0;
          }
          break;
        case 2:
          if (local_78 == 5) {
            local_5c = 0;
            local_60 = 1.0;
            local_6c = 5;
            local_68 = GHIDRA_FIELD(cgs, 68652, 4);
          }
          else {
            local_68 = GHIDRA_FIELD(cgs, 68656, 4);
            if ((local_78 - 2U & 0xfffffffd) == 0) {
              local_6c = 5;
              local_60 = 1.0;
              local_5c = 0;
            }
            else {
              if (local_78 != 1) goto _L78;
              local_60 = 0.5;
              local_5c = 0;
              local_6c = 5;
            }
          }
          break;
        case 3:
          goto _L78;
        case 4:
          local_60 = 1.0;
          local_68 = *(uint32_t *)("cgame.mp..so" + (int)local_4c);
          local_5c = 0;
          local_6c = 2;
          break;
        case 5:
          local_68 = GHIDRA_FIELD(cgs, 67900, 4);
          if (local_78 == 5) {
            local_5c = 0;
            local_60 = 1.0;
            local_6c = 2;
          }
          else {
            if (local_78 == 4) {
            }
            else {
              if (local_78 != 3) {
                if (local_78 == 2) {
                  local_68 = GHIDRA_FIELD(cgs, 67892, 4);
                }
                else {
                  if (local_78 != 1) {
                    local_68 = GHIDRA_FIELD(cgs, 67868, 4);
                    local_5c = -2000;
                    local_60 = 1.0;
                    local_6c = 2;
                    break;
                  }
                  local_68 = GHIDRA_FIELD(cgs, 67872, 4);
                }
                local_5c = -2000;
                local_60 = 1.0;
                local_6c = 2;
                break;
              }
              local_68 = GHIDRA_FIELD(cgs, 67896, 4);
            }
            local_5c = 0;
            local_60 = 1.0;
            local_6c = 2;
          }
          break;
        case 6:
          if (local_78 == 5) {
            local_60 = 1.0;
            local_68 = GHIDRA_FIELD(cgs, 67904, 4);
            local_5c = 0;
          }
          else if (local_78 == 4) {
            local_60 = 1.0;
            local_68 = GHIDRA_FIELD(cgs, 67908, 4);
            local_5c = 0;
          }
          else {
            local_68 = GHIDRA_FIELD(cgs, 67912, 4);
            if (local_78 == 2) {
              local_60 = 1.0;
              local_5c = 0;
            }
            else {
              if (local_78 != 1) goto _L78;
              local_60 = 0.5;
              local_5c = 0;
            }
          }
          break;
        default:
          local_5c = 0;
          local_60 = 1.0;
        }
        tmp_i5 = CG_AllocLocalEntity();
        *(uint32_t *)(tmp_i5 + 8) = 3;
        tmp_i1 = g_unk_010906e0;
        *(int *)(tmp_i5 + 0x10) = g_unk_010906e0;
        tmp_u3 = rand();
        tmp_i1 = (int)ROUND((float)local_5c +
                           ((float)(tmp_u3 & 0x7fff) / 32767.0) * 5000.0 + (float)(tmp_i1 + 5000));
        tmp_i6 = tmp_i1 + -4000;
        if (param_4 == 1) {
          tmp_i6 = tmp_i1;
        }
        *(int *)(tmp_i5 + 0x14) = tmp_i1;
        *(int *)(tmp_i5 + 0x174) = tmp_i1;
        *(float *)(tmp_i5 + 0x1b0) = local_60 * param_9;
        *(int *)(tmp_i5 + 0x170) = tmp_i6;
        if (5 < tmp_i4) {
          if ((local_50 < 6) && ((local_74 & 7) == 0)) {
            local_50 = local_50 + 1;
          }
          else {
            local_6c = 0;
          }
        }
        *(float *)(tmp_i5 + 0x1c) = 1.0 / (float)(tmp_i1 - *(int *)(tmp_i5 + 0x10));
        *(uint32_t *)(tmp_i5 + 0xc) = 2;
        *(uint32_t *)(tmp_i5 + 0x90) = 0;
        *(uint32_t *)(tmp_i5 + 0x100) = *param_1;
        *(uint32_t *)(tmp_i5 + 0x104) = param_1[1];
        *(uint32_t *)(tmp_i5 + 0x108) = param_1[2];
        AxisCopy(axisDefault,tmp_i5 + 0xb4);
        *(uint32_t *)(tmp_i5 + 0x94) = local_6c;
        *(uint32_t *)(tmp_i5 + 0xa0) = local_68;
        if (param_7 != 0) {
          *(int *)(tmp_i5 + 0x148) = param_7;
        }
        *(uint32_t *)(tmp_i5 + 0x15c) = 0x447a0000;
        if (param_4 == 6) {
          local_70 = 0.3;
          *(uint32_t *)(tmp_i5 + 0x20) = 8;
          *(uint32_t *)(tmp_i5 + 0x68) = 0;
        }
        else {
          if ((param_6 == 0) && (tmp_u3 = rand(), (tmp_u3 & 1) != 0)) {
            *(uint32_t *)(tmp_i5 + 0x20) = 6;
          }
          else {
            *(uint32_t *)(tmp_i5 + 0x20) = 7;
          }
          *(uint32_t *)(tmp_i5 + 0x68) = 0x3ecccccd;
        }
        *(uint32_t *)(tmp_i5 + 0x44) = 2;
        *(int *)(tmp_i5 + 0x48) = g_unk_010906e0;
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 0x50) = (float)(tmp_u3 & 0x1f);
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 0x54) = (float)(tmp_u3 & 0x1f);
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 0x58) = (float)(tmp_u3 & 0x1f);
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 0x5c) = (float)(int)((tmp_u3 & 500) - 200) * local_70;
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 0x60) = (float)(int)((tmp_u3 & 500) - 200) * local_70;
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 100) = (float)(int)((tmp_u3 & 500) - 200) * local_70;
        *(uint32_t *)(tmp_i5 + 0x2c) = *param_1;
        *(uint32_t *)(tmp_i5 + 0x30) = param_1[1];
        *(uint32_t *)(tmp_i5 + 0x34) = param_1[2];
        VectorNormalize(param_2);
        *(int *)(tmp_i5 + 0x24) = g_unk_010906e0;
        if (((*(float *)(tmp_i5 + 0x50) == 1.0) || (*(float *)(tmp_i5 + 0x54) == 1.0)) ||
           (*(float *)(tmp_i5 + 0x58) == 1.0)) {
          *(uint32_t *)(tmp_i5 + 0x20) = 6;
          *(float *)(tmp_i5 + 0x38) = *param_2 * 80.0;
          *(float *)(tmp_i5 + 0x3c) = param_2[1] * 80.0;
          *(float *)(tmp_i5 + 0x40) = param_2[2] * 80.0;
          tmp_u3 = rand();
          *(float *)(tmp_i5 + 0x38) =
               (((float)(tmp_u3 & 0x7fff) / 32767.0) * 400.0 - 200.0) * param_8 +
               *(float *)(tmp_i5 + 0x38);
          tmp_u3 = rand();
          *(float *)(tmp_i5 + 0x3c) =
               (((float)(tmp_u3 & 0x7fff) / 32767.0) * 400.0 - 200.0) * param_8 +
               *(float *)(tmp_i5 + 0x3c);
          tmp_u3 = rand();
          *(float *)(tmp_i5 + 0x40) = (((float)(tmp_u3 & 0x7fff) / 32767.0) * 400.0 + 400.0) * param_8
          ;
        }
        else {
          tmp_f2 = (float)(param_3 + 200);
          *(float *)(tmp_i5 + 0x38) = *param_2 * tmp_f2;
          *(float *)(tmp_i5 + 0x3c) = param_2[1] * tmp_f2;
          *(float *)(tmp_i5 + 0x40) = tmp_f2 * param_2[2];
          tmp_u3 = rand();
          *(float *)(tmp_i5 + 0x38) =
               (((float)(tmp_u3 & 0x7fff) / 32767.0) * 200.0 - 100.0) + *(float *)(tmp_i5 + 0x38);
          tmp_u3 = rand();
          *(float *)(tmp_i5 + 0x3c) =
               (((float)(tmp_u3 & 0x7fff) / 32767.0) * 200.0 - 100.0) + *(float *)(tmp_i5 + 0x3c);
          if (param_2[2] == 0.0) {
            tmp_u3 = rand();
            *(float *)(tmp_i5 + 0x40) = ((float)(tmp_u3 & 0x7fff) / 32767.0) * 20.0;
          }
          else {
            tmp_u3 = rand();
            *(float *)(tmp_i5 + 0x40) = ((float)(tmp_u3 & 0x7fff) / 32767.0) * 200.0 * local_70;
          }
        }
        local_74 = local_74 + 1;
      } while ((int)local_74 < local_34[local_78]);
    }
_L78:
    local_78 = local_78 + 1;
    local_4c = local_4c + 4;
    if (local_78 == 6) {
      return;
    }
  } while( true );
}

void CG_Rubble(int param_1,uint32_t param_2,uint32_t param_3,int param_4)
{
  int tmp_i1;
  uint tmp_u2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint32_t tmp_u7;
  uint32_t tmp_u8;
  
  if (((param_4 == 0) && ((*(byte *)(param_1 + 8) & 0x80) != 0)) &&
     (*(int *)(cgs + *(int *)(param_1 + 0xa4) * 4 + 0x840c) != 0)) {
    param_4 = trap_R_GetShaderFromModel(*(int *)(cgs + *(int *)(param_1 + 0xa4) * 4 + 0x840c),0,0);
  }
  tmp_i1 = *(int *)(param_1 + 0x9c);
  if (tmp_i1 == 0) {
    tmp_u2 = rand();
    tmp_i4 = *(int *)(param_1 + 0xb0);
    tmp_i1 = (int)ROUND((float)(int)(&fxSounds)[tmp_i4 * 7] * ((float)(tmp_u2 & 0x7fff) / 32767.0));
    tmp_i6 = tmp_i4 * 7 + tmp_i1;
    tmp_i5 = (&g_unk_00144884)[tmp_i6];
    if (tmp_i5 == -1) {
      tmp_u3 = trap_S_RegisterSound((&fxSounds)[tmp_i6 + 4],0);
      tmp_i4 = *(int *)(param_1 + 0xb0);
      (&g_unk_00144884)[tmp_i6] = tmp_u3;
      tmp_i5 = (&g_unk_00144884)[tmp_i4 * 7 + tmp_i1];
    }
    tmp_u3 = *(uint32_t *)(param_1 + 0x84);
    tmp_u8 = *(uint32_t *)(param_1 + 0x80);
    tmp_u7 = *(uint32_t *)(param_1 + 0xe8);
  }
  else {
    if (tmp_i1 == -1) {
      tmp_i5 = 0;
    }
    else if (tmp_i1 < 0x54) {
      tmp_i5 = *(int *)(cgs + tmp_i1 * 4 + 0x2038f84);
    }
    else {
      tmp_i5 = *(int *)(cgs + tmp_i1 * 4 + 0x7eb8);
    }
    tmp_u3 = *(uint32_t *)(param_1 + 0x84);
    tmp_u8 = *(uint32_t *)(param_1 + 0x80);
    tmp_u7 = *(uint32_t *)(param_1 + 0xe8);
    tmp_i4 = *(int *)(param_1 + 0xb0);
  }
  CG_RubbleFx(param_2,param_3,*(uint32_t *)(param_1 + 0xf4),tmp_i4,tmp_i5,tmp_u7,param_4,tmp_u8,tmp_u3)
  ;
  return;
}

void CG_Explodef(uint32_t *param_1,float *param_2,int param_3,int param_4,int param_5,int param_6,
                int param_7)

{
  int tmp_i1;
  float tmp_f2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  int local_78;
  uint local_74;
  float local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_60;
  int local_5c;
  int local_50;
  uint8_t *local_4c;
  int local_34 [8];
  uint32_t uStack_14;
  
  uStack_14 = 0x70019;
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)local_34 + tmp_u3) = 0;
    *(uint32_t *)((int)local_34 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0x18);
  tmp_f2 = (float)param_3;
  local_34[5] = (int)ROUND(tmp_f2 / 250.0);
  local_34[4] = (int)ROUND(tmp_f2 / 76.0);
  local_34[3] = (int)ROUND(tmp_f2 / 37.0);
  local_34[2] = (int)ROUND(tmp_f2 / 15.0);
  local_34[1] = (int)ROUND(tmp_f2 / 10.0);
  local_34[0] = (int)ROUND(tmp_f2 / 5.0);
  if (0x14 < local_34[0]) {
    local_34[0] = 0x14;
  }
  if (0xf < local_34[1]) {
    local_34[1] = 0xf;
  }
  if (10 < local_34[2]) {
    local_34[2] = 10;
  }
  if (param_4 == 0) {
    if (10 < local_34[0]) {
      local_34[0] = 10;
    }
    if (10 < local_34[1]) {
      local_34[1] = 10;
    }
  }
  tmp_i4 = local_34[5] + local_34[4] + local_34[3] + local_34[2] + local_34[1] + local_34[0];
  if (param_5 != 0) {
    trap_S_StartSound(param_1,0xffffffff,0,param_5);
  }
  local_4c = cgs;
  local_70 = 1.0;
  local_50 = 0;
  local_78 = 0;
  do {
    if (0 < local_34[local_78]) {
      local_68 = 0;
      local_6c = 0;
      local_74 = 0;
      do {
        switch(param_4) {
        case 0:
          local_68 = *(uint32_t *)("GLIBC_2_7" + (int)(local_4c + 5));
          if (local_78 == 0) {
            local_60 = 0x3f000000;
            local_5c = -3000;
            local_6c = 3;
          }
          else {
            if (local_78 == 1) {
              local_60 = 0x3f19999a;
            }
            else {
              if (local_78 != 2) {
                local_5c = 0;
                if (local_78 == 3) {
                  local_60 = 0x3f000000;
                  local_6c = 3;
                }
                else {
                  local_6c = 3;
                  local_60 = 0x3f800000;
                }
                break;
              }
              local_60 = 0x3f333333;
            }
            local_5c = -3000;
            local_6c = 3;
          }
          break;
        case 1:
          local_68 = GHIDRA_FIELD(cgs, 68636, 4);
          if ((local_78 == 5) || (local_68 = GHIDRA_FIELD(cgs, 68640, 4), (local_78 - 2U & 0xfffffffd) == 0)) {
            local_5c = 0;
            local_60 = 0x3f800000;
            local_6c = 0;
          }
          else {
            if (local_78 != 1) goto _L198;
            local_60 = 0x3f000000;
            local_5c = 0;
            local_6c = 0;
          }
          break;
        case 2:
          local_68 = GHIDRA_FIELD(cgs, 68652, 4);
          if ((local_78 == 5) || (local_68 = GHIDRA_FIELD(cgs, 68656, 4), (local_78 - 2U & 0xfffffffd) == 0)) {
            local_5c = 0;
            local_60 = 0x3f800000;
            local_6c = 4;
          }
          else {
            if (local_78 != 1) goto _L198;
            local_60 = 0x3f000000;
            local_5c = 0;
            local_6c = 4;
          }
          break;
        case 3:
          goto _L198;
        case 4:
          local_60 = 0x3f800000;
          local_68 = *(uint32_t *)("cgame.mp..so" + (int)local_4c);
          local_5c = 0;
          local_6c = 2;
          break;
        case 5:
          local_68 = GHIDRA_FIELD(cgs, 67900, 4);
          if (local_78 == 5) {
            local_5c = 0;
            local_60 = 0x3f800000;
            local_6c = 2;
          }
          else {
            if (local_78 == 4) {
            }
            else {
              if (local_78 != 3) {
                if (local_78 == 2) {
                  local_68 = GHIDRA_FIELD(cgs, 67892, 4);
                }
                else {
                  if (local_78 != 1) {
                    local_68 = GHIDRA_FIELD(cgs, 67868, 4);
                    local_5c = -2000;
                    local_60 = 0x3f800000;
                    local_6c = 2;
                    break;
                  }
                  local_68 = GHIDRA_FIELD(cgs, 67872, 4);
                }
                local_5c = -2000;
                local_60 = 0x3f800000;
                local_6c = 2;
                break;
              }
              local_68 = GHIDRA_FIELD(cgs, 67896, 4);
            }
            local_5c = 0;
            local_60 = 0x3f800000;
            local_6c = 2;
          }
          break;
        case 6:
          if (local_78 == 5) {
            local_60 = 0x3f800000;
            local_68 = GHIDRA_FIELD(cgs, 67904, 4);
            local_5c = 0;
          }
          else if (local_78 == 4) {
            local_60 = 0x3f800000;
            local_68 = GHIDRA_FIELD(cgs, 67908, 4);
            local_5c = 0;
          }
          else {
            local_68 = GHIDRA_FIELD(cgs, 67912, 4);
            if (local_78 == 2) {
              local_60 = 0x3f800000;
              local_5c = 0;
            }
            else {
              if (local_78 != 1) goto _L198;
              local_60 = 0x3f000000;
              local_5c = 0;
            }
          }
          break;
        default:
          local_5c = 0;
          local_60 = 0x3f800000;
        }
        tmp_i5 = CG_AllocLocalEntity();
        *(uint32_t *)(tmp_i5 + 8) = 3;
        tmp_i1 = g_unk_010906e0;
        *(int *)(tmp_i5 + 0x10) = g_unk_010906e0;
        tmp_u3 = rand();
        tmp_i1 = (int)ROUND((float)local_5c +
                           ((float)(tmp_u3 & 0x7fff) / 32767.0) * 5000.0 + (float)(tmp_i1 + 5000));
        *(uint32_t *)(tmp_i5 + 0x1b0) = local_60;
        tmp_i6 = tmp_i1 + -4000;
        if (param_4 == 1) {
          tmp_i6 = tmp_i1;
        }
        *(int *)(tmp_i5 + 0x14) = tmp_i1;
        *(int *)(tmp_i5 + 0x174) = tmp_i1;
        *(int *)(tmp_i5 + 0x170) = tmp_i6;
        if (5 < tmp_i4) {
          if ((local_50 < 6) && ((local_74 & 7) == 0)) {
            local_50 = local_50 + 1;
          }
          else {
            local_6c = 0;
          }
        }
        *(float *)(tmp_i5 + 0x1c) = 1.0 / (float)(tmp_i1 - *(int *)(tmp_i5 + 0x10));
        *(uint32_t *)(tmp_i5 + 0xc) = 2;
        *(uint32_t *)(tmp_i5 + 0x90) = 0;
        *(uint32_t *)(tmp_i5 + 0x100) = *param_1;
        *(uint32_t *)(tmp_i5 + 0x104) = param_1[1];
        *(uint32_t *)(tmp_i5 + 0x108) = param_1[2];
        AxisCopy(axisDefault,tmp_i5 + 0xb4);
        *(uint32_t *)(tmp_i5 + 0x94) = local_6c;
        *(uint32_t *)(tmp_i5 + 0xa0) = local_68;
        if (param_7 != 0) {
          *(int *)(tmp_i5 + 0x148) = param_7;
        }
        *(uint32_t *)(tmp_i5 + 0x15c) = 0x447a0000;
        if (param_4 == 6) {
          local_70 = 0.3;
          *(uint32_t *)(tmp_i5 + 0x20) = 8;
          *(uint32_t *)(tmp_i5 + 0x68) = 0;
        }
        else {
          if ((param_6 == 0) && (tmp_u3 = rand(), (tmp_u3 & 1) != 0)) {
            *(uint32_t *)(tmp_i5 + 0x20) = 6;
          }
          else {
            *(uint32_t *)(tmp_i5 + 0x20) = 7;
          }
          *(uint32_t *)(tmp_i5 + 0x68) = 0x3ecccccd;
        }
        *(uint32_t *)(tmp_i5 + 0x44) = 2;
        *(int *)(tmp_i5 + 0x48) = g_unk_010906e0;
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 0x50) = (float)(tmp_u3 & 0x1f);
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 0x54) = (float)(tmp_u3 & 0x1f);
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 0x58) = (float)(tmp_u3 & 0x1f);
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 0x5c) = (float)(int)((tmp_u3 & 500) - 200) * local_70;
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 0x60) = (float)(int)((tmp_u3 & 500) - 200) * local_70;
        tmp_u3 = rand();
        *(float *)(tmp_i5 + 100) = (float)(int)((tmp_u3 & 500) - 200) * local_70;
        *(uint32_t *)(tmp_i5 + 0x2c) = *param_1;
        *(uint32_t *)(tmp_i5 + 0x30) = param_1[1];
        *(uint32_t *)(tmp_i5 + 0x34) = param_1[2];
        VectorNormalize(param_2);
        *(int *)(tmp_i5 + 0x24) = g_unk_010906e0;
        if (((*(float *)(tmp_i5 + 0x50) == 1.0) || (*(float *)(tmp_i5 + 0x54) == 1.0)) ||
           (*(float *)(tmp_i5 + 0x58) == 1.0)) {
          *(uint32_t *)(tmp_i5 + 0x20) = 6;
          *(float *)(tmp_i5 + 0x38) = *param_2 * 80.0;
          *(float *)(tmp_i5 + 0x3c) = param_2[1] * 80.0;
          *(float *)(tmp_i5 + 0x40) = param_2[2] * 80.0;
          tmp_u3 = rand();
          *(float *)(tmp_i5 + 0x38) =
               (((float)(tmp_u3 & 0x7fff) / 32767.0) * 100.0 - 50.0) + *(float *)(tmp_i5 + 0x38);
          tmp_u3 = rand();
          *(float *)(tmp_i5 + 0x3c) =
               (((float)(tmp_u3 & 0x7fff) / 32767.0) * 100.0 - 50.0) + *(float *)(tmp_i5 + 0x3c);
          tmp_u3 = rand();
          *(float *)(tmp_i5 + 0x40) = ((float)(tmp_u3 & 0x7fff) / 32767.0) * 200.0 + 200.0;
        }
        else {
          tmp_f2 = (float)(param_3 + 200);
          *(float *)(tmp_i5 + 0x38) = *param_2 * tmp_f2;
          *(float *)(tmp_i5 + 0x3c) = param_2[1] * tmp_f2;
          *(float *)(tmp_i5 + 0x40) = tmp_f2 * param_2[2];
          tmp_u3 = rand();
          *(float *)(tmp_i5 + 0x38) =
               (((float)(tmp_u3 & 0x7fff) / 32767.0) * 100.0 - 50.0) + *(float *)(tmp_i5 + 0x38);
          tmp_u3 = rand();
          *(float *)(tmp_i5 + 0x3c) =
               (((float)(tmp_u3 & 0x7fff) / 32767.0) * 100.0 - 50.0) + *(float *)(tmp_i5 + 0x3c);
          if (param_2[2] == 0.0) {
            tmp_u3 = rand();
            *(float *)(tmp_i5 + 0x40) = ((float)(tmp_u3 & 0x7fff) / 32767.0) * 20.0;
          }
          else {
            tmp_u3 = rand();
            *(float *)(tmp_i5 + 0x40) = ((float)(tmp_u3 & 0x7fff) / 32767.0) * 200.0 * local_70;
          }
        }
        local_74 = local_74 + 1;
      } while ((int)local_74 < local_34[local_78]);
    }
_L198:
    local_78 = local_78 + 1;
    local_4c = local_4c + 4;
    if (local_78 == 6) {
      return;
    }
  } while( true );
}

void CG_Explode(int param_1,uint32_t param_2,uint32_t param_3,int param_4)
{
  int tmp_i1;
  uint tmp_u2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  if (((param_4 == 0) && ((*(byte *)(param_1 + 8) & 0x80) != 0)) &&
     (*(int *)(cgs + *(int *)(param_1 + 0xa4) * 4 + 0x840c) != 0)) {
    param_4 = trap_R_GetShaderFromModel(*(int *)(cgs + *(int *)(param_1 + 0xa4) * 4 + 0x840c),0,0);
  }
  tmp_i1 = *(int *)(param_1 + 0x9c);
  if (tmp_i1 == 0) {
    tmp_u2 = rand();
    tmp_i4 = *(int *)(param_1 + 0xb0);
    tmp_i1 = (int)ROUND((float)(int)(&fxSounds)[tmp_i4 * 7] * ((float)(tmp_u2 & 0x7fff) / 32767.0));
    tmp_i6 = tmp_i4 * 7 + tmp_i1;
    tmp_i5 = (&g_unk_00144884)[tmp_i6];
    if (tmp_i5 == -1) {
      tmp_u3 = trap_S_RegisterSound((&fxSounds)[tmp_i6 + 4],0);
      tmp_i4 = *(int *)(param_1 + 0xb0);
      (&g_unk_00144884)[tmp_i6] = tmp_u3;
      tmp_i5 = (&g_unk_00144884)[tmp_i4 * 7 + tmp_i1];
    }
    tmp_u3 = *(uint32_t *)(param_1 + 0xe8);
  }
  else {
    if (tmp_i1 == -1) {
      tmp_i5 = 0;
    }
    else if (tmp_i1 < 0x54) {
      tmp_i5 = *(int *)(cgs + tmp_i1 * 4 + 0x2038f84);
    }
    else {
      tmp_i5 = *(int *)(cgs + tmp_i1 * 4 + 0x7eb8);
    }
    tmp_u3 = *(uint32_t *)(param_1 + 0xe8);
    tmp_i4 = *(int *)(param_1 + 0xb0);
  }
  CG_Explodef(param_2,param_3,*(uint32_t *)(param_1 + 0xf4),tmp_i4,tmp_i5,tmp_u3,param_4);
  return;
}

void CG_Effect(int param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  int tmp_i5;
  char *tmp_pc6;
  uint32_t tmp_u7;
  int tmp_i8;
  int local_6c;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  uint32_t local_3c;
  uint32_t local_38;
  float local_34;
  uint32_t local_30;
  float local_2c [7];
  
  *param_3 = 0.0;
  param_3[1] = 0.0;
  param_3[2] = 1.0;
  tmp_u4 = *(uint *)(param_1 + 0xbc);
  if ((tmp_u4 & 1) != 0) {
    CG_MissileHitWall(0xf,0,param_2,param_3,0);
    return;
  }
  if ((tmp_u4 & 7) != 0) {
    local_6c = 5;
    local_3c = 0;
    local_38 = 0;
    local_34 = 16.0;
    do {
      tmp_i8 = 0;
      do {
        tmp_f1 = param_3[tmp_i8];
        tmp_f2 = param_2[tmp_i8];
        tmp_u4 = rand();
        tmp_f3 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
        local_2c[tmp_i8] = (tmp_f3 + tmp_f3) * 24.0 + tmp_f1 * 64.0 + tmp_f2;
        tmp_i8 = tmp_i8 + 1;
      } while (tmp_i8 != 3);
      tmp_i8 = rand();
      local_34 = (float)(tmp_i8 % 0x32) + local_34;
      tmp_i8 = rand();
      tmp_i5 = rand();
      CG_ParticleExplosion
                ("blacksmokeanim",local_2c,&local_3c,tmp_i5 % 0xfa + 0xdac,10,tmp_i8 % 0x3c + 0xfa,0);
      local_6c = local_6c + -1;
    } while (local_6c != 0);
    tmp_u4 = *(uint *)(param_1 + 0xbc);
  }
  if ((tmp_u4 & 2) != 0) {
    trap_S_StartSound(param_2,0xffffffff,0,GHIDRA_FIELD(cgs, 69100, 4));
    local_48 = *param_3 * 16.0 + *param_2;
    local_44 = param_3[1] * 16.0 + param_2[1];
    local_40 = param_3[2] * 16.0 + param_2[2];
    local_54 = *param_3 * 100.0;
    local_50 = param_3[1] * 100.0;
    local_4c = param_3[2] * 100.0;
    if (GHIDRA_FIELD(cg_wolfparticles, 12, 4) != 0) {
      CG_ParticleExplosion("explode1",&local_48,&local_54,500,0x14,0xa0,1);
    }
    local_3c = 0;
    local_38 = 0;
    local_34 = -1.0;
    local_30 = 0x42800000;
    local_2c[0] = 1.0;
    local_2c[1] = 1.0;
    local_2c[2] = 1.0;
    local_2c[3] = 1.0;
    trap_R_ProjectDecal(GHIDRA_FIELD(cgs, 68808, 4),1,param_2,&local_3c,local_2c,GHIDRA_FIELD(cg_markTime, 12, 4),
                        (int)GHIDRA_FIELD(cg_markTime, 12, 4) >> 4);
    tmp_u4 = *(uint *)(param_1 + 0xbc);
  }
  if ((tmp_u4 & 8) != 0) {
    local_48 = 0.0;
    local_44 = 0.0;
    local_40 = 0.0;
    tmp_f1 = *(float *)(param_1 + 0x80);
    if (tmp_f1 == 0.0) {
      tmp_f2 = *(float *)(param_1 + 0x84);
      if (tmp_f2 == 0.0) {
        tmp_f3 = *(float *)(param_1 + 0x88);
        if (*(float *)(param_1 + 0x88) == 0.0) {
          tmp_f1 = local_48;
          tmp_f2 = local_44;
          tmp_f3 = local_40;
        }
      }
      else {
        tmp_f3 = *(float *)(param_1 + 0x88);
      }
    }
    else {
      tmp_f2 = *(float *)(param_1 + 0x84);
      tmp_f3 = *(float *)(param_1 + 0x88);
    }
    local_40 = tmp_f3;
    local_44 = tmp_f2;
    local_48 = tmp_f1;
    tmp_pc6 = (char *)CG_ConfigString(0x14);
    tmp_u7 = 0;
    if ((tmp_pc6 != (char *)0x0) && (*tmp_pc6 != '\0')) {
      tmp_u7 = va("textures/%s",tmp_pc6);
      tmp_u7 = trap_R_RegisterShader(tmp_u7);
    }
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xffffff7f;
    *(uint32_t *)(param_1 + 0x9c) = 0;
    CG_Explode(param_1,param_2,&local_48,tmp_u7);
    tmp_u4 = *(uint *)(param_1 + 0xbc);
  }
  if ((tmp_u4 & 0x40) == 0) {
    return;
  }
  tmp_i8 = rand();
  CG_AddDebris(param_2,param_3,0x118,0x578,tmp_i8 % 2 + 7);
  return;
}

void CG_Shard(int param_1,uint32_t *param_2,float *param_3)
{
  int tmp_i1;
  float tmp_f2;
  bool tmp_b3;
  int tmp_i4;
  uint tmp_u5;
  int tmp_i6;
  int tmp_i7;
  int local_40;
  int local_3c;
  
  local_40 = *(int *)(param_1 + 0xf4);
  tmp_i1 = *(int *)(param_1 + 0xb0);
  if (0 < tmp_i1) {
    tmp_f2 = (float)(tmp_i1 * 10);
    local_3c = 0;
    tmp_b3 = false;
    do {
      tmp_i4 = CG_AllocLocalEntity();
      *(uint32_t *)(tmp_i4 + 8) = 3;
      tmp_i6 = g_unk_010906e0;
      *(int *)(tmp_i4 + 0x10) = g_unk_010906e0;
      tmp_u5 = rand();
      tmp_i6 = (int)ROUND(((float)(tmp_u5 & 0x7fff) / 32767.0) * 5000.0 + (float)(tmp_i6 + 5000));
      *(int *)(tmp_i4 + 0x14) = tmp_i6;
      *(int *)(tmp_i4 + 0x170) = tmp_i6 + -1000;
      *(int *)(tmp_i4 + 0x174) = tmp_i6;
      tmp_i7 = g_unk_010906e0;
      if (local_40 == 999) {
        tmp_b3 = true;
        local_40 = 1;
        tmp_i6 = g_unk_010906e0 + 100;
        *(int *)(tmp_i4 + 0x10) = g_unk_010906e0;
        *(int *)(tmp_i4 + 0x14) = tmp_i6;
        *(int *)(tmp_i4 + 0x170) = tmp_i7;
        *(int *)(tmp_i4 + 0x174) = tmp_i6;
      }
      else {
        tmp_i7 = *(int *)(tmp_i4 + 0x10);
      }
      *(float *)(tmp_i4 + 0x1c) = 1.0 / (float)(tmp_i6 - tmp_i7);
      *(uint32_t *)(tmp_i4 + 0xc) = 2;
      *(uint32_t *)(tmp_i4 + 0x68) = 0x3ecccccd;
      *(uint32_t *)(tmp_i4 + 0x90) = 0;
      *(uint32_t *)(tmp_i4 + 0x100) = *param_2;
      *(uint32_t *)(tmp_i4 + 0x104) = param_2[1];
      *(uint32_t *)(tmp_i4 + 0x108) = param_2[2];
      AxisCopy(axisDefault,tmp_i4 + 0xb4);
      if (local_40 == 1) {
        tmp_i6 = rand();
        if ((tmp_i6 + -(tmp_i6 >> 0x1f) & 1U) == -(tmp_i6 >> 0x1f)) {
          *(uint32_t *)(tmp_i4 + 0xa0) = GHIDRA_FIELD(cgs, 68640, 4);
        }
        else {
          *(uint32_t *)(tmp_i4 + 0xa0) = GHIDRA_FIELD(cgs, 68636, 4);
        }
      }
      else if (local_40 == 0) {
        tmp_i6 = rand();
        if ((tmp_i6 + -(tmp_i6 >> 0x1f) & 1U) == -(tmp_i6 >> 0x1f)) {
          *(uint32_t *)(tmp_i4 + 0xa0) = GHIDRA_FIELD(cgs, 68648, 4);
        }
        else {
          *(uint32_t *)(tmp_i4 + 0xa0) = GHIDRA_FIELD(cgs, 68644, 4);
        }
      }
      else if (local_40 == 2) {
        tmp_i6 = rand();
        if ((tmp_i6 + -(tmp_i6 >> 0x1f) & 1U) == -(tmp_i6 >> 0x1f)) {
          *(uint32_t *)(tmp_i4 + 0xa0) = GHIDRA_FIELD(cgs, 68656, 4);
        }
        else {
          *(uint32_t *)(tmp_i4 + 0xa0) = GHIDRA_FIELD(cgs, 68652, 4);
        }
      }
      else if (local_40 - 4U < 2) {
        tmp_i6 = rand();
        if (tmp_i6 % 3 == 1) {
          *(uint32_t *)(tmp_i4 + 0xa0) = GHIDRA_FIELD(cgs, 68660, 4);
        }
        else if (tmp_i6 % 3 == 2) {
          *(uint32_t *)(tmp_i4 + 0xa0) = GHIDRA_FIELD(cgs, 68664, 4);
        }
        else {
          *(uint32_t *)(tmp_i4 + 0xa0) = GHIDRA_FIELD(cgs, 68668, 4);
        }
      }
      else {
        CG_Printf("CG_Debris has an unknown type\n");
      }
      *(uint *)(tmp_i4 + 0x20) = 7 - (uint)!tmp_b3;
      *(uint32_t *)(tmp_i4 + 0x2c) = *param_2;
      *(uint32_t *)(tmp_i4 + 0x30) = param_2[1];
      *(uint32_t *)(tmp_i4 + 0x34) = param_2[2];
      VectorNormalize(param_3);
      *(float *)(tmp_i4 + 0x38) = *param_3 * tmp_f2;
      *(float *)(tmp_i4 + 0x3c) = param_3[1] * tmp_f2;
      *(float *)(tmp_i4 + 0x40) = param_3[2] * tmp_f2;
      *(int *)(tmp_i4 + 0x24) = g_unk_010906e0;
      tmp_u5 = rand();
      *(float *)(tmp_i4 + 0x38) =
           (((float)(tmp_u5 & 0x7fff) / 32767.0) * 100.0 - 50.0) + *(float *)(tmp_i4 + 0x38);
      tmp_u5 = rand();
      *(float *)(tmp_i4 + 0x3c) =
           (((float)(tmp_u5 & 0x7fff) / 32767.0) * 100.0 - 50.0) + *(float *)(tmp_i4 + 0x3c);
      if (local_40 == 0) {
        tmp_u5 = rand();
        *(float *)(tmp_i4 + 0x40) = ((float)(tmp_u5 & 0x7fff) / 32767.0) * 100.0 + 50.0;
      }
      else {
        tmp_u5 = rand();
        *(float *)(tmp_i4 + 0x40) = ((float)(tmp_u5 & 0x7fff) / 32767.0) * 200.0 + 100.0;
      }
      *(uint32_t *)(tmp_i4 + 0x44) = 2;
      *(int *)(tmp_i4 + 0x48) = g_unk_010906e0;
      tmp_u5 = rand();
      *(float *)(tmp_i4 + 0x50) = (float)(tmp_u5 & 0x1f);
      tmp_u5 = rand();
      *(float *)(tmp_i4 + 0x54) = (float)(tmp_u5 & 0x1f);
      tmp_u5 = rand();
      *(float *)(tmp_i4 + 0x58) = (float)(tmp_u5 & 0x1f);
      tmp_u5 = rand();
      *(float *)(tmp_i4 + 0x5c) = (float)(int)((tmp_u5 & 500) - 200);
      tmp_u5 = rand();
      *(float *)(tmp_i4 + 0x60) = (float)(int)((tmp_u5 & 500) - 200);
      tmp_u5 = rand();
      local_3c = local_3c + 1;
      *(float *)(tmp_i4 + 100) = (float)(int)((tmp_u5 & 500) - 200);
    } while (local_3c != tmp_i1);
  }
  return;
}

void CG_ShardJunk(uint32_t param_1,uint32_t *param_2,float *param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  int tmp_i4;
  
  tmp_i2 = CG_AllocLocalEntity();
  *(uint32_t *)(tmp_i2 + 8) = 3;
  tmp_i4 = g_unk_010906e0;
  *(int *)(tmp_i2 + 0x10) = g_unk_010906e0;
  tmp_u3 = rand();
  tmp_i4 = (int)ROUND(((float)(tmp_u3 & 0x7fff) / 32767.0) * 5000.0 + (float)(tmp_i4 + 5000));
  *(int *)(tmp_i2 + 0x170) = tmp_i4 + -1000;
  *(int *)(tmp_i2 + 0x14) = tmp_i4;
  *(int *)(tmp_i2 + 0x174) = tmp_i4;
  *(float *)(tmp_i2 + 0x1c) = 1.0 / (float)(tmp_i4 - *(int *)(tmp_i2 + 0x10));
  *(uint32_t *)(tmp_i2 + 0x90) = 0;
  *(uint32_t *)(tmp_i2 + 0xc) = 2;
  *(uint32_t *)(tmp_i2 + 0x68) = 0x3ecccccd;
  *(uint32_t *)(tmp_i2 + 0x100) = *param_2;
  *(uint32_t *)(tmp_i2 + 0x104) = param_2[1];
  *(uint32_t *)(tmp_i2 + 0x108) = param_2[2];
  AxisCopy(axisDefault,tmp_i2 + 0xb4);
  tmp_i4 = rand();
  tmp_u1 = *(uint32_t *)(cgs + (tmp_i4 % 5) * 4 + 0x10c40);
  *(uint32_t *)(tmp_i2 + 0x20) = 6;
  *(uint32_t *)(tmp_i2 + 0xa0) = tmp_u1;
  *(uint32_t *)(tmp_i2 + 0x2c) = *param_2;
  *(uint32_t *)(tmp_i2 + 0x30) = param_2[1];
  *(uint32_t *)(tmp_i2 + 0x34) = param_2[2];
  VectorNormalize(param_3);
  *(float *)(tmp_i2 + 0x38) = *param_3 * 80.0;
  *(float *)(tmp_i2 + 0x3c) = param_3[1] * 80.0;
  *(float *)(tmp_i2 + 0x40) = param_3[2] * 80.0;
  *(int *)(tmp_i2 + 0x24) = g_unk_010906e0;
  tmp_u3 = rand();
  *(float *)(tmp_i2 + 0x38) =
       (((float)(tmp_u3 & 0x7fff) / 32767.0) * 100.0 - 50.0) + *(float *)(tmp_i2 + 0x38);
  tmp_u3 = rand();
  *(float *)(tmp_i2 + 0x3c) =
       (((float)(tmp_u3 & 0x7fff) / 32767.0) * 100.0 - 50.0) + *(float *)(tmp_i2 + 0x3c);
  tmp_u3 = rand();
  *(uint32_t *)(tmp_i2 + 0x44) = 2;
  *(float *)(tmp_i2 + 0x40) = ((float)(tmp_u3 & 0x7fff) / 32767.0) * 100.0 + 50.0;
  *(int *)(tmp_i2 + 0x48) = g_unk_010906e0;
  tmp_u3 = rand();
  *(float *)(tmp_i2 + 0x58) = (float)(tmp_u3 & 0x1f);
  tmp_u3 = rand();
  *(float *)(tmp_i2 + 100) = (float)(int)((tmp_u3 & 500) - 200);
  return;
}

void CG_Debris(int param_1,uint32_t *param_2,uint32_t *param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint tmp_u4;
  
  tmp_i3 = CG_AllocLocalEntity();
  *(uint32_t *)(tmp_i3 + 8) = 3;
  tmp_i1 = g_unk_010906e0;
  *(int *)(tmp_i3 + 0x10) = g_unk_010906e0;
  tmp_u4 = rand();
  tmp_i1 = (int)ROUND(((float)(tmp_u4 & 0x7fff) / 32767.0) * 5000.0 + (float)(tmp_i1 + 5000));
  *(int *)(tmp_i3 + 0x14) = tmp_i1;
  *(int *)(tmp_i3 + 0x174) = tmp_i1;
  *(int *)(tmp_i3 + 0x170) = tmp_i1 + -1000;
  *(float *)(tmp_i3 + 0x1c) = 1.0 / (float)(tmp_i1 - *(int *)(tmp_i3 + 0x10));
  *(uint32_t *)(tmp_i3 + 0x90) = 0;
  *(uint32_t *)(tmp_i3 + 0x1ac) = 1;
  *(uint32_t *)(tmp_i3 + 0xc) = 0x12;
  *(uint32_t *)(tmp_i3 + 0x68) = 0x3ecccccd;
  *(uint32_t *)(tmp_i3 + 0x1b0) = 0x3f000000;
  *(uint32_t *)(tmp_i3 + 0x100) = *param_2;
  *(uint32_t *)(tmp_i3 + 0x104) = param_2[1];
  *(uint32_t *)(tmp_i3 + 0x108) = param_2[2];
  AxisCopy(axisDefault,tmp_i3 + 0xb4);
  tmp_u2 = *(uint32_t *)(cgs + *(int *)(param_1 + 0xa4) * 4 + 0x840c);
  *(uint32_t *)(tmp_i3 + 0x20) = 6;
  *(uint32_t *)(tmp_i3 + 0xa0) = tmp_u2;
  *(uint32_t *)(tmp_i3 + 0x2c) = *param_2;
  *(uint32_t *)(tmp_i3 + 0x30) = param_2[1];
  *(uint32_t *)(tmp_i3 + 0x34) = param_2[2];
  *(uint32_t *)(tmp_i3 + 0x38) = *param_3;
  *(uint32_t *)(tmp_i3 + 0x3c) = param_3[1];
  *(uint32_t *)(tmp_i3 + 0x40) = param_3[2];
  tmp_i1 = g_unk_010906e0;
  *(uint32_t *)(tmp_i3 + 0x44) = 2;
  *(int *)(tmp_i3 + 0x24) = tmp_i1;
  *(int *)(tmp_i3 + 0x48) = g_unk_010906e0;
  tmp_u4 = rand();
  *(float *)(tmp_i3 + 0x58) = (float)(tmp_u4 & 0x1f);
  tmp_u4 = rand();
  *(float *)(tmp_i3 + 100) = (float)(int)((tmp_u4 & 500) - 200);
  tmp_u4 = rand();
  *(float *)(tmp_i3 + 100) = (float)(int)((tmp_u4 & 400) - 0x32);
  tmp_u4 = rand();
  *(float *)(tmp_i3 + 100) = (float)(int)((tmp_u4 & 400) - 0x32);
  return;
}

void CG_MortarImpact(int param_1,float *param_2,int param_3,int param_4)
{
  long double tmp_l1;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  if (-1 < param_3) {
    trap_S_StartSound(param_2,0xffffffff,0,*(uint32_t *)(cgs + param_3 * 4 + 0x10e08));
  }
  if (param_4 != 0) {
    local_18 = *param_2 - *(float *)(g_unk_010afbcc + 0x18);
    local_14 = param_2[1] - *(float *)(g_unk_010afbcc + 0x1c);
    local_10 = param_2[2] - *(float *)(g_unk_010afbcc + 0x20);
    tmp_l1 = (long double)VectorNormalize(&local_18);
    if (((long double)1200.0 < tmp_l1) && (tmp_l1 < (long double)8000.0)) {
      local_24 = local_18 * 800.0 + *(float *)(g_unk_010afbcc + 0x18);
      local_20 = local_14 * 800.0 + *(float *)(g_unk_010afbcc + 0x1c);
      local_1c = local_10 * 800.0 + *(float *)(g_unk_010afbcc + 0x20);
      trap_S_StartSoundEx(&local_24,0xffffffff,2,GHIDRA_FIELD(cgs, 69144, 4),0x10);
    }
    if ((*(int *)(param_1 + 0xac) == *(int *)(g_unk_01047b00 + 0xcc)) && (g_unk_010b4564 != -2)) {
      g_unk_010b4568 = *param_2;
      g_unk_010b4564 = g_unk_010906e0;
      g_unk_010b456c = param_2[1];
      g_unk_010b4570 = param_2[2];
      g_unk_010b4574 = 0;
    }
  }
  return;
}

void CG_MortarMiss(int param_1,uint32_t *param_2)
{
  if ((*(int *)(param_1 + 0xac) == *(int *)(g_unk_01047b00 + 0xcc)) && (g_unk_010b4564 != -2)) {
    g_unk_010b4568 = *param_2;
    g_unk_010b456c = param_2[1];
    g_unk_010b4564 = g_unk_010906e0;
    g_unk_010b4570 = param_2[2];
    g_unk_010b4574 = (uint)(*(int *)(param_1 + 0xf4) != 0);
    return;
  }
  return;
}

uint32_t CG_GetGameSound(int param_1)
{
  if (0x53 < param_1) {
    return *(uint32_t *)(cgs + param_1 * 4 + 0x7eb8);
  }
  return *(uint32_t *)(cgs + param_1 * 4 + 0x2038f84);
}

uint CG_SortFireTeam(int *param_1,int *param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i1 = *param_1;
  tmp_i2 = *param_2;
  if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
    return 0xffffffff;
  }
  if (*(int *)(cgs + tmp_i2 * 0x1a4 + 0x9494) == 3) {
    tmp_i3 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
    if (tmp_i3 == 3) {
      return 0xffffffff;
    }
    tmp_i4 = 0;
LAB_00076304:
    if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9578) != tmp_i4) {
      return 0xffffffff;
    }
    if (*(int *)(cgs + tmp_i2 * 0x1a4 + 0x9494) == 3) {
      return 0xffffffff;
    }
  }
  else {
    tmp_i4 = *(int *)(cgs + tmp_i2 * 0x1a4 + 0x9578);
    tmp_i3 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
    if (tmp_i3 != 3) goto LAB_00076304;
    if (tmp_i4 != 0) {
      return 0xffffffff;
    }
  }
  if (*(int *)(cgs + tmp_i2 * 0x1a4 + 0x9578) == 0) {
    return 0xffffffff;
  }
  if (*(int *)(cgs + tmp_i1 * 0x1a4 + 0x9494) == 3) {
    if (tmp_i3 == 3) {
      return 1;
    }
    tmp_i4 = 0;
  }
  else {
    tmp_i4 = *(int *)(cgs + tmp_i1 * 0x1a4 + 0x9578);
    if (tmp_i3 == 3) {
      if (tmp_i4 != 0) {
        return 1;
      }
      goto LAB_0007637f;
    }
  }
  if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9578) != tmp_i4) {
    return 1;
  }
  if (*(int *)(cgs + tmp_i1 * 0x1a4 + 0x9494) == 3) {
    return 1;
  }
LAB_0007637f:
  if (*(int *)(cgs + tmp_i1 * 0x1a4 + 0x9578) == 0) {
    return 1;
  }
  if (tmp_i1 != *(int *)(*(int *)(cgs + tmp_i1 * 0x1a4 + 0x9578) + 0x44)) {
    if (tmp_i2 == *(int *)(*(int *)(cgs + tmp_i2 * 0x1a4 + 0x9578) + 0x44)) {
      return 1;
    }
    if (*(int *)(cgs + tmp_i1 * 0x1a4 + 0x94c0) <= *(int *)(cgs + tmp_i2 * 0x1a4 + 0x94c0)) {
      return (uint)(*(int *)(cgs + tmp_i1 * 0x1a4 + 0x94c0) < *(int *)(cgs + tmp_i2 * 0x1a4 + 0x94c0))
      ;
    }
  }
  return 0xffffffff;
}

void CG_SortClientFireteam(void)
{
  uint32_t __nmemb;
  int tmp_i1;
  
  __nmemb = GHIDRA_FIELD(cgs, 27400, 4);
  if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
    tmp_i1 = 0;
    do {
      (&sortedFireTeamClients)[tmp_i1] = tmp_i1;
      tmp_i1 = tmp_i1 + 1;
    } while (tmp_i1 != __nmemb);
  }
  qsort(&sortedFireTeamClients,__nmemb,4,CG_SortFireTeam);
  return;
}

uint32_t CG_IsOnSameFireteam(int param_1,int param_2)
{
  int tmp_i1;
  
  if (GHIDRA_FIELD(cgs, 27388, 4) != 8) {
    if (*(int *)(cgs + param_1 * 0x1a4 + 0x9494) == 3) {
      if (*(int *)(cgs + param_2 * 0x1a4 + 0x9494) == 3) {
        return 0;
      }
      tmp_i1 = 0;
    }
    else {
      tmp_i1 = *(int *)(cgs + param_1 * 0x1a4 + 0x9578);
      if (*(int *)(cgs + param_2 * 0x1a4 + 0x9494) == 3) {
        if (tmp_i1 != 0) {
          return 0;
        }
        goto LAB_000767c7;
      }
    }
    if ((*(int *)(cgs + param_2 * 0x1a4 + 0x9578) == tmp_i1) &&
       (*(int *)(cgs + param_1 * 0x1a4 + 0x9494) != 3)) {
LAB_000767c7:
      return *(uint32_t *)(cgs + param_1 * 0x1a4 + 0x9578);
    }
  }
  return 0;
}

uint32_t CG_IsOnFireteam(int param_1)
{
  if ((GHIDRA_FIELD(cgs, 27388, 4) != 8) && (*(int *)(cgs + param_1 * 0x1a4 + 0x9494) != 3)) {
    return *(uint32_t *)(cgs + param_1 * 0x1a4 + 0x9578);
  }
  return 0;
}

int CG_IsFireTeamLeader(int param_1)
{
  int tmp_i1;
  
  if ((GHIDRA_FIELD(cgs, 27388, 4) != 8) && (*(int *)(cgs + param_1 * 0x1a4 + 0x9494) != 3)) {
    tmp_i1 = *(int *)(cgs + param_1 * 0x1a4 + 0x9578);
    if ((tmp_i1 != 0) && (*(int *)(tmp_i1 + 0x44) != param_1)) {
      tmp_i1 = 0;
    }
    return tmp_i1;
  }
  return 0;
}

int CG_SortedFireTeamPlayerForPosition(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  
  if (((((GHIDRA_FIELD(cgs, 27388, 4) != 8) && (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3)) &&
       (tmp_i1 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9578), tmp_i1 != 0)) &&
      (((0 < (int)GHIDRA_FIELD(cgs, 27400, 4) && (*(int *)(cgs + sortedFireTeamClients * 0x1a4 + 0x9494) != 3)) &&
       (tmp_i1 == *(int *)(cgs + sortedFireTeamClients * 0x1a4 + 0x9578))))) &&
     ((tmp_i2 = sortedFireTeamClients, param_1 == 0 ||
      ((((1 < (int)GHIDRA_FIELD(cgs, 27400, 4) && (*(int *)(cgs + g_unk_002bb284 * 0x1a4 + 0x9494) != 3)) &&
        (tmp_i1 == *(int *)(cgs + g_unk_002bb284 * 0x1a4 + 0x9578))) &&
       ((tmp_i2 = g_unk_002bb284, param_1 == 1 ||
        ((((2 < (int)GHIDRA_FIELD(cgs, 27400, 4) && (*(int *)(cgs + g_unk_002bb288 * 0x1a4 + 0x9494) != 3)) &&
          (tmp_i1 == *(int *)(cgs + g_unk_002bb288 * 0x1a4 + 0x9578))) &&
         ((tmp_i2 = g_unk_002bb288, param_1 == 2 ||
          (((3 < (int)GHIDRA_FIELD(cgs, 27400, 4) && (*(int *)(cgs + g_unk_002bb28c * 0x1a4 + 0x9494) != 3)) &&
           ((tmp_i1 == *(int *)(cgs + g_unk_002bb28c * 0x1a4 + 0x9578) &&
            ((tmp_i2 = g_unk_002bb28c, param_1 == 3 ||
             ((((4 < (int)GHIDRA_FIELD(cgs, 27400, 4) && (*(int *)(cgs + g_unk_002bb290 * 0x1a4 + 0x9494) != 3)) &&
               (tmp_i1 == *(int *)(cgs + g_unk_002bb290 * 0x1a4 + 0x9578))) &&
              ((tmp_i2 = g_unk_002bb290, param_1 == 4 ||
               ((((5 < (int)GHIDRA_FIELD(cgs, 27400, 4) && (*(int *)(cgs + g_unk_002bb294 * 0x1a4 + 0x9494) != 3))
                 && (tmp_i1 == *(int *)(cgs + g_unk_002bb294 * 0x1a4 + 0x9578))) &&
                (tmp_i2 = g_unk_002bb294, param_1 == 5)))))))))))))))))))))))) {
    return tmp_i2 * 0x1a4 + 0x10f926c;
  }
  return 0;
}

uint8_t * CG_BuildSelectedFirteamString(void)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int local_124;
  uint8_t local_11c [264];
  uint32_t uStack_14;
  
  tmp_i6 = 0;
  uStack_14 = 0x77acd;
  local_11c[0] = 0;
  local_124 = 0;
  while( true ) {
    if ((((GHIDRA_FIELD(cgs, 27388, 4) == 8) || (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3)) ||
        (tmp_i1 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9578), tmp_i1 == 0)) ||
       ((((int)GHIDRA_FIELD(cgs, 27400, 4) < 1 || (*(int *)(cgs + sortedFireTeamClients * 0x1a4 + 0x9494) == 3))
        || (tmp_i1 != *(int *)(cgs + sortedFireTeamClients * 0x1a4 + 0x9578))))) goto LAB_00077c80;
    tmp_i3 = sortedFireTeamClients;
    if (tmp_i6 != 0) break;
LAB_00077d28:
    if (*(int *)(cgs + tmp_i3 * 0x1a4 + 0x957c) == 0) {
      tmp_i6 = tmp_i6 + 1;
    }
    else {
LAB_00077cd8:
      local_124 = local_124 + 1;
      tmp_u4 = va(&g_unk_00115a1e,*(uint32_t *)(cgs + tmp_i3 * 0x1a4 + 0x9410));
      Q_strcat(local_11c,0x100,tmp_u4);
joined_r0x00077c6f:
      tmp_i6 = tmp_i6 + 1;
      if (tmp_i6 == 6) {
LAB_00077c80:
        if (local_124 == 0) {
          return &g_unk_0011e957;
        }
        if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x957c) == 0) {
          tmp_u4 = va(&g_unk_00115a1e,g_unk_01047ac4);
          Q_strcat(local_11c,0x100,tmp_u4);
          local_124 = local_124 + 1;
        }
        tmp_pu2 = (uint8_t *)va("%i %s",local_124,local_11c);
        return tmp_pu2;
      }
    }
  }
  if (((GHIDRA_FIELD(cgs, 27400, 4) == 1) || (*(int *)(cgs + g_unk_002bb284 * 0x1a4 + 0x9494) == 3)) ||
     (tmp_i1 != *(int *)(cgs + g_unk_002bb284 * 0x1a4 + 0x9578))) goto LAB_00077c80;
  tmp_i3 = g_unk_002bb284;
  if (tmp_i6 == 1) goto LAB_00077d28;
  if (((GHIDRA_FIELD(cgs, 27400, 4) == 2) || (*(int *)(cgs + g_unk_002bb288 * 0x1a4 + 0x9494) == 3)) ||
     (tmp_i1 != *(int *)(cgs + g_unk_002bb288 * 0x1a4 + 0x9578))) goto LAB_00077c80;
  tmp_i3 = g_unk_002bb288;
  if (tmp_i6 == 2) goto LAB_00077d28;
  if (((GHIDRA_FIELD(cgs, 27400, 4) == 3) || (*(int *)(cgs + g_unk_002bb28c * 0x1a4 + 0x9494) == 3)) ||
     (tmp_i1 != *(int *)(cgs + g_unk_002bb28c * 0x1a4 + 0x9578))) goto LAB_00077c80;
  tmp_i3 = g_unk_002bb28c;
  if (tmp_i6 == 3) goto LAB_00077d28;
  if (((GHIDRA_FIELD(cgs, 27400, 4) == 4) || (*(int *)(cgs + g_unk_002bb290 * 0x1a4 + 0x9494) == 3)) ||
     (tmp_i1 != *(int *)(cgs + g_unk_002bb290 * 0x1a4 + 0x9578))) goto LAB_00077c80;
  tmp_i3 = g_unk_002bb290;
  if (tmp_i6 == 4) goto LAB_00077d28;
  if (((GHIDRA_FIELD(cgs, 27400, 4) == 5) || (tmp_i5 = g_unk_002bb294 * 0x1a4, *(int *)(cgs + tmp_i5 + 0x9494) == 3))
     || (tmp_i1 != *(int *)(cgs + tmp_i5 + 0x9578))) goto LAB_00077c80;
  tmp_i3 = g_unk_002bb294;
  if (*(int *)(cgs + tmp_i5 + 0x957c) != 0) goto LAB_00077cd8;
  goto joined_r0x00077c6f;
}

uint64_t CG_CountFireteamsByTeam_part_0(int param_1)
{
  uint tmp_u1;
  uint32_t uStack_c;
  
  tmp_u1 = 0;
  uStack_c = 0x78049;
  if (g_unk_010b3b78 != 0) {
    tmp_u1 = (uint)(param_1 == *(int *)(cgs + g_unk_010b3b74 * 0x1a4 + 0x9494));
  }
  if (g_unk_010b3bc8 != 0) {
    uStack_c = CONCAT13(*(int *)(cgs + g_unk_010b3bc4 * 0x1a4 + 0x9494) == param_1,0x78049);
    tmp_u1 = tmp_u1 + (*(int *)(cgs + g_unk_010b3bc4 * 0x1a4 + 0x9494) == param_1);
  }
  if (g_unk_010b3c18 != 0) {
    uStack_c = CONCAT13(*(int *)(cgs + g_unk_010b3c14 * 0x1a4 + 0x9494) == param_1,
                        (uint32_t)uStack_c);
    tmp_u1 = tmp_u1 + (*(int *)(cgs + g_unk_010b3c14 * 0x1a4 + 0x9494) == param_1);
  }
  if (g_unk_010b3c68 != 0) {
    uStack_c = CONCAT13(*(int *)(cgs + g_unk_010b3c64 * 0x1a4 + 0x9494) == param_1,
                        (uint32_t)uStack_c);
    tmp_u1 = tmp_u1 + (*(int *)(cgs + g_unk_010b3c64 * 0x1a4 + 0x9494) == param_1);
  }
  if (g_unk_010b3cb8 != 0) {
    uStack_c = CONCAT13(*(int *)(cgs + g_unk_010b3cb4 * 0x1a4 + 0x9494) == param_1,
                        (uint32_t)uStack_c);
    tmp_u1 = tmp_u1 + (*(int *)(cgs + g_unk_010b3cb4 * 0x1a4 + 0x9494) == param_1);
  }
  if (g_unk_010b3d08 != 0) {
    uStack_c = CONCAT13(*(int *)(cgs + g_unk_010b3d04 * 0x1a4 + 0x9494) == param_1,
                        (uint32_t)uStack_c);
    tmp_u1 = tmp_u1 + (*(int *)(cgs + g_unk_010b3d04 * 0x1a4 + 0x9494) == param_1);
  }
  if (g_unk_010b3d58 != 0) {
    uStack_c = CONCAT13(*(int *)(cgs + g_unk_010b3d54 * 0x1a4 + 0x9494) == param_1,
                        (uint32_t)uStack_c);
    tmp_u1 = tmp_u1 + (*(int *)(cgs + g_unk_010b3d54 * 0x1a4 + 0x9494) == param_1);
  }
  if (g_unk_010b3da8 != 0) {
    uStack_c = CONCAT13(*(int *)(cgs + g_unk_010b3da4 * 0x1a4 + 0x9494) == param_1,
                        (uint32_t)uStack_c);
    tmp_u1 = tmp_u1 + (*(int *)(cgs + g_unk_010b3da4 * 0x1a4 + 0x9494) == param_1);
  }
  if (g_unk_010b3df8 != 0) {
    uStack_c = CONCAT13(*(int *)(cgs + g_unk_010b3df4 * 0x1a4 + 0x9494) == param_1,
                        (uint32_t)uStack_c);
    tmp_u1 = tmp_u1 + (*(int *)(cgs + g_unk_010b3df4 * 0x1a4 + 0x9494) == param_1);
  }
  if (g_unk_010b3e48 != 0) {
    uStack_c = CONCAT13(*(int *)(cgs + g_unk_010b3e44 * 0x1a4 + 0x9494) == param_1,
                        (uint32_t)uStack_c);
    tmp_u1 = tmp_u1 + (*(int *)(cgs + g_unk_010b3e44 * 0x1a4 + 0x9494) == param_1);
  }
  if (g_unk_010b3e98 != 0) {
    uStack_c = CONCAT13(*(int *)(cgs + g_unk_010b3e94 * 0x1a4 + 0x9494) == param_1,
                        (uint32_t)uStack_c);
    tmp_u1 = tmp_u1 + (*(int *)(cgs + g_unk_010b3e94 * 0x1a4 + 0x9494) == param_1);
  }
  if (g_unk_010b3ee8 != 0) {
    return CONCAT44(uStack_c,tmp_u1 + (*(int *)(cgs + g_unk_010b3ee4 * 0x1a4 + 0x9494) == param_1));
  }
  return CONCAT44(uStack_c,tmp_u1);
}

uint CG_CountFireteamsByTeam(int param_1)
{
  uint tmp_u1;
  
  tmp_u1 = 0;
  if (param_1 - 1U < 2) {
    if (g_unk_010b3b78 != 0) {
      tmp_u1 = (uint)(param_1 == *(int *)(cgs + g_unk_010b3b74 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3bc8 != 0) {
      tmp_u1 = tmp_u1 + (param_1 == *(int *)(cgs + g_unk_010b3bc4 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3c18 != 0) {
      tmp_u1 = tmp_u1 + (param_1 == *(int *)(cgs + g_unk_010b3c14 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3c68 != 0) {
      tmp_u1 = tmp_u1 + (param_1 == *(int *)(cgs + g_unk_010b3c64 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3cb8 != 0) {
      tmp_u1 = tmp_u1 + (param_1 == *(int *)(cgs + g_unk_010b3cb4 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3d08 != 0) {
      tmp_u1 = tmp_u1 + (param_1 == *(int *)(cgs + g_unk_010b3d04 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3d58 != 0) {
      tmp_u1 = tmp_u1 + (param_1 == *(int *)(cgs + g_unk_010b3d54 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3da8 != 0) {
      tmp_u1 = tmp_u1 + (param_1 == *(int *)(cgs + g_unk_010b3da4 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3df8 != 0) {
      tmp_u1 = tmp_u1 + (param_1 == *(int *)(cgs + g_unk_010b3df4 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3e48 != 0) {
      tmp_u1 = tmp_u1 + (param_1 == *(int *)(cgs + g_unk_010b3e44 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3e98 != 0) {
      tmp_u1 = tmp_u1 + (param_1 == *(int *)(cgs + g_unk_010b3e94 * 0x1a4 + 0x9494));
    }
    if (g_unk_010b3ee8 != 0) {
      return tmp_u1 + (param_1 == *(int *)(cgs + g_unk_010b3ee4 * 0x1a4 + 0x9494));
    }
  }
  return tmp_u1;
}

int CG_CountPlayersSF(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  int local_28;
  
  tmp_pu5 = cgs;
  if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
    local_28 = 0;
  }
  else {
    local_28 = 0;
    tmp_i4 = 0;
    tmp_i3 = GHIDRA_FIELD(cgs, 27400, 4);
    do {
      if (((g_unk_01047ac4 != tmp_i4) && (*(int *)(tmp_pu5 + 0x940c) != 0)) &&
         (*(int *)(tmp_pu5 + 0x9494) == *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494))) {
        tmp_i1 = CG_IsOnFireteam(tmp_i4);
        tmp_i2 = CG_IsOnFireteam(g_unk_01047ac4);
        tmp_i3 = GHIDRA_FIELD(cgs, 27400, 4);
        if (tmp_i1 == tmp_i2) {
          local_28 = local_28 + 1;
        }
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu5 = tmp_pu5 + 0x1a4;
    } while (tmp_i4 < tmp_i3);
  }
  return local_28;
}

int CG_CountPlayersNF(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  int local_24;
  
  tmp_pu4 = cgs;
  if ((int)GHIDRA_FIELD(cgs, 27400, 4) < 1) {
    local_24 = 0;
  }
  else {
    local_24 = 0;
    tmp_i3 = 0;
    tmp_i2 = GHIDRA_FIELD(cgs, 27400, 4);
    do {
      if ((((g_unk_01047ac4 != tmp_i3) && (*(int *)(tmp_pu4 + 0x940c) != 0)) &&
          (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(tmp_pu4 + 0x9494))) &&
         (tmp_i1 = CG_IsOnFireteam(tmp_i3), tmp_i2 = GHIDRA_FIELD(cgs, 27400, 4), tmp_i1 == 0)) {
        local_24 = local_24 + 1;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu4 = tmp_pu4 + 0x1a4;
    } while (tmp_i3 < tmp_i2);
  }
  return local_24;
}

void CG_ClearFlameChunks(void)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  
  memset(&flameChunks,0,0x27000);
  memset(centFlameInfo,0,0xd000);
  tmp_i2 = 0;
  activeFlameChunks = 0;
  headFlameChunks = 0;
  tmp_pu1 = &g_unk_002ca51c;
  freeFlameChunks = &flameChunks;
  do {
    tmp_pu1[-0x27] = tmp_pu1;
    if (tmp_i2 == 0) {
      g_unk_002ca484 = 0;
    }
    else {
      tmp_pu1[-0x26] = tmp_pu1 + -0x4e;
    }
    tmp_i2 = tmp_i2 + 1;
    tmp_pu1[-0x22] = 0;
    tmp_pu1 = tmp_pu1 + 0x27;
  } while (tmp_i2 != 0x400);
  g_unk_002f13e4 = 0;
  initFlameChunks = 1;
  numFlameChunksInuse = 0;
  return;
}

void CG_SpawnFlameChunk(int *param_1)
{
  int *tmp_pi1;
  
  tmp_pi1 = freeFlameChunks;
  if (freeFlameChunks != (int *)0x0) {
    if ((headFlameChunks != (int *)0x0) && (headFlameChunks[6] != 0)) {
      headFlameChunks = (int *)0x0;
    }
    freeFlameChunks = (int *)*freeFlameChunks;
    if (freeFlameChunks != (int *)0x0) {
      freeFlameChunks[1] = 0;
    }
    *tmp_pi1 = (int)activeFlameChunks;
    if (activeFlameChunks != (int *)0x0) {
      activeFlameChunks[1] = (int)tmp_pi1;
    }
    activeFlameChunks = tmp_pi1;
    tmp_pi1[1] = 0;
    tmp_pi1[5] = 1;
    tmp_pi1[6] = 0;
    if (param_1 != (int *)0x0) {
      if (param_1 == headFlameChunks) {
        headFlameChunks = (int *)param_1[3];
        if (headFlameChunks != (int *)0x0) {
          headFlameChunks[4] = 0;
        }
      }
      else {
        if (param_1[3] != 0) {
          *(int *)(param_1[3] + 0x10) = param_1[4];
        }
        if (param_1[4] != 0) {
          *(int *)(param_1[4] + 0xc) = param_1[3];
        }
      }
      param_1[4] = 0;
      param_1[3] = 0;
    }
    if (headFlameChunks != (int *)0x0) {
      headFlameChunks[4] = (int)tmp_pi1;
    }
    numFlameChunksInuse = numFlameChunksInuse + 1;
    tmp_pi1[3] = (int)headFlameChunks;
    tmp_pi1[4] = 0;
    headFlameChunks = tmp_pi1;
    tmp_pi1[2] = (int)param_1;
  }
  return;
}

void CG_FireFlameChunks(int *param_1,float *param_2,uint32_t *param_3,float param_4,int param_5,
                       int param_6)

{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  float tmp_f9;
  float tmp_f10;
  float tmp_f11;
  float tmp_f12;
  uint32_t tmp_u13;
  bool tmp_b14;
  float tmp_f15;
  float tmp_f16;
  float tmp_f17;
  int *tmp_pi18;
  int tmp_i19;
  uint tmp_u20;
  int tmp_i21;
  uint32_t tmp_u22;
  int tmp_i23;
  bool tmp_b24;
  uint local_14c;
  int local_140;
  int local_ec;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
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
  float local_64;
  int local_60;
  int local_5c;
  int local_58;
  uint8_t local_54 [4];
  int local_50;
  uint32_t uStack_14;
  
  uStack_14 = 0x7cf79;
  tmp_i21 = *param_1;
  if ((tmp_i21 == *(int *)(g_unk_01047b00 + 0xcc)) && (GHIDRA_FIELD(cg_thirdPerson, 12, 4) == 0)) {
    AngleVectors(param_3,&local_60,0,0);
  }
  else {
    AngleVectors(param_1 + 0x1d,&local_60,0,0);
  }
  AngleVectors(param_3,&local_cc,&local_84,&local_a8);
  tmp_pi18 = freeFlameChunks;
  tmp_f2 = *param_2;
  tmp_f3 = param_2[1];
  tmp_f4 = param_2[2];
  if ((((param_6 == 0) &&
       (tmp_i19 = tmp_i21 * 0x34, *(int *)(centFlameInfo + tmp_i19) == param_1[0x2c])) &&
      (*(int *)(centFlameInfo + tmp_i19 + 0x1c) != 0)) &&
     (tmp_i5 = *(int *)(centFlameInfo + tmp_i19 + 0x24), tmp_i5 == param_5)) {
    AngleVectors(tmp_i19 + 0x2bd464,&local_d8,&local_90,&local_b4);
    tmp_f6 = *(float *)(centFlameInfo + tmp_i19 + 0x10);
    tmp_f7 = *(float *)(centFlameInfo + tmp_i19 + 0x14);
    tmp_f8 = *(float *)(centFlameInfo + tmp_i19 + 0x18);
    *(int *)(centFlameInfo + tmp_i19 + 0x24) = param_5;
    tmp_i19 = *(int *)(centFlameInfo + tmp_i19 + 0x1c);
    if (param_5 == 0) {
      tmp_f9 = 500.0;
    }
    else {
      tmp_f9 = 1000.0;
    }
    local_ec = 0x33;
    tmp_b24 = tmp_i5 == 0;
    tmp_f9 = (8.0 / (param_4 * 1200.0)) * tmp_f9;
    tmp_f15 = (float)*(int *)(tmp_i19 + 0x20) + tmp_f9;
    local_140 = (int)ROUND(tmp_f15);
    tmp_f16 = tmp_f9 / (float)(g_unk_010906e0 - *(int *)(tmp_i19 + 0x20));
    tmp_f10 = 1.0;
    tmp_i23 = g_unk_010906e0;
    do {
      tmp_f10 = tmp_f10 - tmp_f16;
      if (tmp_i23 < local_140) goto LAB_0007d362;
      tmp_f17 = 1.0 - tmp_f10;
      local_6c = tmp_f6 * tmp_f10 + tmp_f2 * tmp_f17;
      local_68 = tmp_f7 * tmp_f10 + tmp_f3 * tmp_f17;
      local_64 = tmp_f4 * tmp_f17 + tmp_f8 * tmp_f10;
      CG_Trace(local_54,&local_6c,flameChunkMins,flameChunkMaxs,&local_6c,*param_1,0x6000039);
      if (local_50 != 0) {
        return;
      }
      tmp_i19 = CG_SpawnFlameChunk(tmp_i19);
      if (tmp_i19 == 0) {
        *(int *)(*(int *)(centFlameInfo + tmp_i21 * 0x34 + 0x1c) + 0x20) = g_unk_010906e0;
        return;
      }
      local_c0 = local_d8 * tmp_f10 + tmp_f17 * local_cc;
      local_bc = local_d4 * tmp_f10 + tmp_f17 * local_c8;
      local_b8 = local_d0 * tmp_f10 + tmp_f17 * local_c4;
      VectorNormalize(&local_c0);
      local_78 = local_90 * tmp_f10 + tmp_f17 * local_84;
      local_74 = local_8c * tmp_f10 + tmp_f17 * local_80;
      local_70 = local_88 * tmp_f10 + tmp_f17 * local_7c;
      VectorNormalize(&local_78);
      local_9c = local_b4 * tmp_f10 + tmp_f17 * local_a8;
      local_98 = local_b0 * tmp_f10 + tmp_f17 * local_a4;
      local_94 = local_ac * tmp_f10 + tmp_f17 * local_a0;
      VectorNormalize(&local_9c);
      *(int *)(tmp_i19 + 0x20) = local_140;
      tmp_f17 = param_4 * 0.5 + 0.5;
      *(int *)(tmp_i19 + 0x24) = (int)ROUND((float)local_140 + (1.0 / tmp_f17) * 2125.0);
      *(float *)(tmp_i19 + 0x80) = param_4;
      if (tmp_i5 == 0) {
        tmp_f12 = (*(float *)(tmp_i19 + 0x2c) * 0.0 + 80.0) * param_4;
        *(uint32_t *)(tmp_i19 + 0x2c) = 0;
        *(float *)(tmp_i19 + 0x28) = tmp_f12;
        if (175.0 < tmp_f12) {
          *(uint32_t *)(tmp_i19 + 0x28) = 0x432f0000;
          tmp_f12 = param_4 * 175.0;
          tmp_f11 = 1.5;
        }
        else {
          tmp_f12 = tmp_f12 * param_4;
          tmp_f11 = 1.5;
        }
      }
      else {
        tmp_f12 = (*(float *)(tmp_i19 + 0x2c) + 80.0) * param_4;
        *(uint32_t *)(tmp_i19 + 0x2c) = 0;
        *(float *)(tmp_i19 + 0x28) = tmp_f12;
        if (175.0 < tmp_f12) {
          *(uint32_t *)(tmp_i19 + 0x28) = 0x432f0000;
          tmp_f12 = param_4 * 175.0;
          if (tmp_b24) {
            tmp_f11 = 1.5;
          }
          else {
            tmp_f11 = 1.0;
          }
        }
        else {
          tmp_f12 = tmp_f12 * param_4;
          tmp_f11 = 1.0;
        }
      }
      *(float *)(tmp_i19 + 0x30) = (tmp_f12 * tmp_f11) / 2125.0;
      *(int *)(tmp_i19 + 0x40) = local_140;
      *(float *)(tmp_i19 + 0x34) = local_6c;
      *(float *)(tmp_i19 + 0x38) = local_68;
      *(float *)(tmp_i19 + 0x3c) = local_64;
      *(float *)(tmp_i19 + 0x44) = local_c0;
      *(float *)(tmp_i19 + 0x48) = local_bc;
      *(float *)(tmp_i19 + 0x4c) = local_b8;
      *(float *)(tmp_i19 + 100) = local_c0;
      *(float *)(tmp_i19 + 0x68) = local_bc;
      *(float *)(tmp_i19 + 0x6c) = local_b8;
      *(float *)(tmp_i19 + 0x70) = param_4;
      VectorNormalize(tmp_i19 + 0x44);
      if (tmp_i5 == 0) {
        tmp_f12 = 4.5;
      }
      else {
        tmp_f12 = 1.0;
      }
      *(float *)(tmp_i19 + 0x50) = tmp_f12 * tmp_f17 * 1200.0;
      *(int *)(tmp_i19 + 0x1c) = *param_1;
      local_14c = rand();
      local_14c = local_14c & 0x7fff;
      tmp_f17 = (float)local_14c / 32767.0 - 0.5;
      *(float *)(tmp_i19 + 0x54) = (tmp_f17 + tmp_f17) * 179.0;
      *(uint *)(tmp_i19 + 0x58) = (uint)tmp_b24;
      if (tmp_b24) {
        tmp_u22 = 10;
        tmp_u13 = 0xc3160000;
      }
      else {
        tmp_u22 = 0x6c;
        tmp_u13 = 0;
      }
      *(uint32_t *)(tmp_i19 + 0x60) = tmp_u13;
      *(uint32_t *)(tmp_i19 + 0x5c) = tmp_u22;
      *(int *)(tmp_i19 + 0x88) = g_unk_010906e0;
      tmp_i23 = g_unk_010906e0;
      *(int *)(tmp_i19 + 0x90) = local_60;
      *(int *)(tmp_i19 + 0x94) = local_5c;
      *(int *)(tmp_i19 + 0x8c) = tmp_i23;
      *(int *)(tmp_i19 + 0x98) = local_58;
      tmp_i23 = g_unk_010906e0;
      tmp_f15 = tmp_f15 + tmp_f9;
      tmp_i1 = (int)ROUND(tmp_f15);
      tmp_b14 = local_140 < g_unk_010906e0;
      local_140 = tmp_i1;
      if ((tmp_b14) && (g_unk_010906e0 < tmp_i1)) {
        tmp_f15 = (float)g_unk_010906e0;
        local_140 = g_unk_010906e0;
        tmp_f10 = tmp_f16;
      }
      local_ec = local_ec + -1;
      *(int *)(centFlameInfo + tmp_i21 * 0x34 + 0x1c) = tmp_i19;
    } while (local_ec != 0);
    *(int *)(tmp_i19 + 0x20) = tmp_i23;
  }
  else {
    tmp_b24 = freeFlameChunks == (int *)0x0;
    *(int *)(centFlameInfo + tmp_i21 * 0x34 + 0x24) = param_5;
    if (tmp_b24) {
      return;
    }
    if ((headFlameChunks != (int *)0x0) && (headFlameChunks[6] != 0)) {
      headFlameChunks = (int *)0x0;
    }
    freeFlameChunks = (int *)*tmp_pi18;
    if (freeFlameChunks != (int *)0x0) {
      freeFlameChunks[1] = 0;
    }
    *tmp_pi18 = (int)activeFlameChunks;
    if (activeFlameChunks != (int *)0x0) {
      activeFlameChunks[1] = (int)tmp_pi18;
    }
    activeFlameChunks = tmp_pi18;
    tmp_pi18[1] = 0;
    tmp_pi18[5] = 1;
    tmp_pi18[6] = 0;
    if (headFlameChunks != (int *)0x0) {
      headFlameChunks[4] = (int)tmp_pi18;
    }
    tmp_pi18[2] = 0;
    tmp_pi18[3] = (int)headFlameChunks;
    tmp_pi18[4] = 0;
    numFlameChunksInuse = numFlameChunksInuse + 1;
    local_c0 = local_cc;
    tmp_pi18[8] = g_unk_010906e0;
    local_bc = local_c8;
    headFlameChunks = tmp_pi18;
    local_b8 = local_c4;
    local_9c = local_a8;
    local_98 = local_a4;
    local_94 = local_a0;
    local_78 = local_84;
    local_74 = local_80;
    local_70 = local_7c;
    tmp_f7 = param_4 * 0.5 + 0.5;
    tmp_pi18[9] = (int)ROUND((1.0 / tmp_f7) * 2125.0 + (float)g_unk_010906e0);
    tmp_pi18[0x20] = (int)param_4;
    tmp_f6 = param_4 * 80.0;
    if (175.0 < tmp_f6) {
      tmp_pi18[10] = 0x432f0000;
      tmp_f6 = 175.0;
    }
    else {
      tmp_pi18[10] = (int)tmp_f6;
    }
    tmp_pi18[0xb] = 0;
    tmp_pi18[0xc] = (int)((tmp_f6 * param_4) / 2125.0);
    tmp_pi18[0xd] = (int)tmp_f2;
    tmp_pi18[0xe] = (int)tmp_f3;
    tmp_pi18[0xf] = (int)tmp_f4;
    tmp_i19 = g_unk_010906e0;
    tmp_pi18[0x11] = (int)local_cc;
    tmp_pi18[0x12] = (int)local_c8;
    tmp_pi18[0x13] = (int)local_c4;
    tmp_pi18[0x19] = (int)local_cc;
    tmp_pi18[0x1a] = (int)local_c8;
    tmp_pi18[0x1b] = (int)local_c4;
    tmp_pi18[0x10] = tmp_i19;
    tmp_pi18[0x14] = (int)(tmp_f7 * 1200.0);
    tmp_pi18[7] = *param_1;
    local_6c = tmp_f2;
    local_68 = tmp_f3;
    local_64 = tmp_f4;
    tmp_u20 = rand();
    tmp_f2 = (float)(tmp_u20 & 0x7fff) / 32767.0 - 0.5;
    tmp_pi18[0x15] = (int)((tmp_f2 + tmp_f2) * 179.0);
    tmp_pi18[0x16] = (uint)(param_5 == 0);
    tmp_pi18[0x1c] = (int)param_4;
    if (param_5 == 0) {
      tmp_i19 = (int)ROUND((1.0 / param_4) * 0.3 * 108.0);
      tmp_i5 = -0x3d380000;
    }
    else {
      tmp_i19 = 0x6c;
      tmp_i5 = 0;
    }
    tmp_pi18[0x18] = tmp_i5;
    tmp_pi18[0x17] = tmp_i19;
    tmp_pi18[0x22] = g_unk_010906e0;
    tmp_i19 = g_unk_010906e0;
    tmp_pi18[0x24] = local_60;
    tmp_pi18[0x25] = local_5c;
    tmp_pi18[0x23] = tmp_i19;
    tmp_pi18[0x26] = local_58;
    *(int **)(centFlameInfo + tmp_i21 * 0x34 + 0x1c) = tmp_pi18;
  }
LAB_0007d362:
  tmp_i21 = tmp_i21 * 0x34;
  *(uint32_t *)(centFlameInfo + tmp_i21 + 4) = *param_3;
  *(uint32_t *)(centFlameInfo + tmp_i21 + 8) = param_3[1];
  *(uint32_t *)(centFlameInfo + tmp_i21 + 0xc) = param_3[2];
  *(float *)(centFlameInfo + tmp_i21 + 0x10) = *param_2;
  *(float *)(centFlameInfo + tmp_i21 + 0x14) = param_2[1];
  *(float *)(centFlameInfo + tmp_i21 + 0x18) = param_2[2];
  *(int *)(centFlameInfo + tmp_i21) = param_1[0x2c];
  return;
}

void CG_FreeFlameChunk(int *param_1)
{
  int *tmp_pi1;
  int *tmp_pi2;
  int *tmp_pi3;
  int *tmp_pi4;
  int *local_2c;
  int *local_28;
  int *local_24;
  int local_20;
  
  tmp_pi1 = (int *)param_1[2];
  if (tmp_pi1 != (int *)0x0) {
    tmp_pi2 = (int *)tmp_pi1[2];
    if (tmp_pi2 != (int *)0x0) {
      local_2c = (int *)tmp_pi2[2];
      if (local_2c == (int *)0x0) {
        local_2c = freeFlameChunks;
      }
      else {
        tmp_pi3 = (int *)local_2c[2];
        if (tmp_pi3 == (int *)0x0) {
          local_28 = (int *)numFlameChunksInuse;
        }
        else {
          local_28 = (int *)tmp_pi3[2];
          if (local_28 == (int *)0x0) {
            local_28 = freeFlameChunks;
            local_24 = (int *)numFlameChunksInuse;
          }
          else {
            local_24 = (int *)local_28[2];
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
              tmp_pi4 = (int *)local_24[3];
              if (local_24 == headFlameChunks) {
                headFlameChunks = tmp_pi4;
              }
              if (tmp_pi4 != (int *)0x0) {
                tmp_pi4[4] = local_24[4];
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
              local_28[2] = 0;
            }
            local_28[5] = 0;
            local_28[6] = 0;
            if (*local_28 != 0) {
              *(int *)(*local_28 + 4) = local_28[1];
            }
            if ((int *)local_28[1] != (int *)0x0) {
              *(int *)local_28[1] = *local_28;
            }
            if (local_28 == activeFlameChunks) {
              activeFlameChunks = (int *)*local_28;
            }
            tmp_pi4 = (int *)local_28[3];
            if (local_28 == headFlameChunks) {
              headFlameChunks = tmp_pi4;
            }
            if (tmp_pi4 != (int *)0x0) {
              tmp_pi4[4] = local_28[4];
            }
            if (local_28[4] != 0) {
              *(int *)(local_28[4] + 0xc) = local_28[3];
            }
            local_28[3] = 0;
            local_28[4] = 0;
            local_28[1] = 0;
            *local_28 = (int)local_24;
            if (local_24 != (int *)0x0) {
              local_24[1] = (int)local_28;
            }
            tmp_pi3[2] = 0;
            local_24 = (int *)(local_20 + -1);
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
          *tmp_pi3 = (int)local_28;
          if (local_28 != (int *)0x0) {
            local_28[1] = (int)tmp_pi3;
          }
          local_28 = (int *)((int)local_24 + -1);
          local_2c[2] = 0;
          freeFlameChunks = tmp_pi3;
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
        }
        tmp_pi3 = (int *)local_2c[3];
        if (local_2c == headFlameChunks) {
          headFlameChunks = tmp_pi3;
        }
        if (tmp_pi3 != (int *)0x0) {
          tmp_pi3[4] = local_2c[4];
        }
        if (local_2c[4] != 0) {
          *(int *)(local_2c[4] + 0xc) = local_2c[3];
        }
        local_2c[3] = 0;
        local_2c[4] = 0;
        local_2c[1] = 0;
        *local_2c = (int)freeFlameChunks;
        if (freeFlameChunks != (int *)0x0) {
          freeFlameChunks[1] = (int)local_2c;
        }
        tmp_pi2[2] = 0;
        numFlameChunksInuse = (int)local_28 + -1;
      }
      tmp_pi2[5] = 0;
      tmp_pi2[6] = 0;
      if (*tmp_pi2 != 0) {
        *(int *)(*tmp_pi2 + 4) = tmp_pi2[1];
      }
      if ((int *)tmp_pi2[1] != (int *)0x0) {
        *(int *)tmp_pi2[1] = *tmp_pi2;
      }
      if (tmp_pi2 == activeFlameChunks) {
        activeFlameChunks = (int *)*tmp_pi2;
      }
      tmp_pi3 = (int *)tmp_pi2[3];
      if (tmp_pi2 == headFlameChunks) {
        headFlameChunks = tmp_pi3;
      }
      if (tmp_pi3 != (int *)0x0) {
        tmp_pi3[4] = tmp_pi2[4];
      }
      if (tmp_pi2[4] != 0) {
        *(int *)(tmp_pi2[4] + 0xc) = tmp_pi2[3];
      }
      tmp_pi2[3] = 0;
      tmp_pi2[4] = 0;
      tmp_pi2[1] = 0;
      *tmp_pi2 = (int)local_2c;
      if (local_2c != (int *)0x0) {
        local_2c[1] = (int)tmp_pi2;
      }
      numFlameChunksInuse = numFlameChunksInuse + -1;
      tmp_pi1[2] = 0;
      freeFlameChunks = tmp_pi2;
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
      tmp_pi2 = (int *)tmp_pi1[3];
    }
    else {
      tmp_pi2 = (int *)tmp_pi1[3];
    }
    if (tmp_pi1 == headFlameChunks) {
      headFlameChunks = tmp_pi2;
    }
    if (tmp_pi2 != (int *)0x0) {
      tmp_pi2[4] = tmp_pi1[4];
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
    param_1[2] = 0;
    freeFlameChunks = tmp_pi1;
  }
  param_1[5] = 0;
  param_1[6] = 0;
  if (*param_1 != 0) {
    *(int *)(*param_1 + 4) = param_1[1];
  }
  if ((int *)param_1[1] != (int *)0x0) {
    *(int *)param_1[1] = *param_1;
  }
  if (param_1 == activeFlameChunks) {
    activeFlameChunks = (int *)*param_1;
    tmp_pi1 = (int *)param_1[3];
  }
  else {
    tmp_pi1 = (int *)param_1[3];
  }
  if (param_1 == headFlameChunks) {
    headFlameChunks = tmp_pi1;
  }
  if (tmp_pi1 != (int *)0x0) {
    tmp_pi1[4] = param_1[4];
  }
  if (param_1[4] != 0) {
    *(int *)(param_1[4] + 0xc) = param_1[3];
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[1] = 0;
  *param_1 = (int)freeFlameChunks;
  if (freeFlameChunks != (int *)0x0) {
    freeFlameChunks[1] = (int)param_1;
  }
  freeFlameChunks = param_1;
  numFlameChunksInuse = numFlameChunksInuse + -1;
  return;
}

void CG_MergeFlameChunks(int param_1,int *param_2)
{
  int *tmp_pi1;
  
  if (*(int **)(param_1 + 8) != param_2) {
    CG_Error("CG_MergeFlameChunks: f2 doesn\'t follow f1, cannot merge\n");
  }
  *(int *)(param_1 + 8) = param_2[2];
  param_2[2] = 0;
  *(int *)(param_1 + 0x44) = param_2[0x11];
  *(int *)(param_1 + 0x48) = param_2[0x12];
  *(int *)(param_1 + 0x4c) = param_2[0x13];
  *(int *)(param_1 + 0x34) = param_2[0xd];
  *(int *)(param_1 + 0x38) = param_2[0xe];
  *(int *)(param_1 + 0x3c) = param_2[0xf];
  *(int *)(param_1 + 0x40) = param_2[0x10];
  *(int *)(param_1 + 0x50) = param_2[0x14];
  *(int *)(param_1 + 0x28) = param_2[10];
  *(int *)(param_1 + 0x80) = param_2[0x20];
  *(int *)(param_1 + 0x20) = param_2[8];
  *(int *)(param_1 + 0x24) = param_2[9];
  if (param_2[2] != 0) {
    CG_FreeFlameChunk(param_2[2]);
    param_2[2] = 0;
  }
  param_2[5] = 0;
  param_2[6] = 0;
  if (*param_2 != 0) {
    *(int *)(*param_2 + 4) = param_2[1];
  }
  if ((int *)param_2[1] != (int *)0x0) {
    *(int *)param_2[1] = *param_2;
  }
  if (param_2 == activeFlameChunks) {
    activeFlameChunks = (int *)*param_2;
    tmp_pi1 = (int *)param_2[3];
  }
  else {
    tmp_pi1 = (int *)param_2[3];
  }
  if (param_2 == headFlameChunks) {
    headFlameChunks = tmp_pi1;
  }
  if (tmp_pi1 != (int *)0x0) {
    tmp_pi1[4] = param_2[4];
  }
  if (param_2[4] != 0) {
    *(int *)(param_2[4] + 0xc) = param_2[3];
  }
  param_2[3] = 0;
  param_2[4] = 0;
  param_2[1] = 0;
  *param_2 = (int)freeFlameChunks;
  if (freeFlameChunks != (int *)0x0) {
    *(int **)((int)freeFlameChunks + 4) = param_2;
  }
  freeFlameChunks = param_2;
  numFlameChunksInuse = numFlameChunksInuse + -1;
  return;
}

void CG_MoveFlameChunk(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  int tmp_i6;
  int tmp_i7;
  long double tmp_l8;
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
  float local_3c;
  float local_38;
  float local_34;
  byte local_28;
  
  tmp_f1 = *(float *)(param_1 + 0x50);
  if ((1.0 < tmp_f1) && (*(int *)(param_1 + 0x8c) < g_unk_010906e0 + -0x32)) {
    tmp_f2 = -((float)(g_unk_010906e0 - *(int *)(param_1 + 0x8c)) / 1000.0) * 2400.0;
    if ((tmp_f2 != 0.0) || (tmp_f1 != 0.0)) {
      tmp_f1 = tmp_f2 + tmp_f1;
      *(float *)(param_1 + 0x50) = tmp_f1;
      if (tmp_f1 < 60.0) {
        *(uint32_t *)(param_1 + 0x50) = 0x42700000;
        tmp_f1 = 60.0;
      }
    }
    *(int *)(param_1 + 0x8c) = g_unk_010906e0;
  }
  tmp_f2 = *(float *)(param_1 + 0x28);
  if (*(float *)(param_1 + 0x80) < tmp_f2) {
    if (g_unk_010906e0 - *(int *)(param_1 + 0x20) < *(int *)(param_1 + 0x5c)) {
      tmp_f3 = 0.037647057;
    }
    else {
      tmp_f3 = (tmp_f2 / 2125.0) / 0.3;
    }
    *(float *)(param_1 + 0x30) = tmp_f3;
    tmp_i6 = *(int *)(param_1 + 0x40);
    tmp_f3 = (float)(g_unk_010906e0 - tmp_i6) * tmp_f3 + *(float *)(param_1 + 0x80);
    *(float *)(param_1 + 0x80) = tmp_f3;
    if (tmp_f2 < tmp_f3) {
      *(float *)(param_1 + 0x80) = tmp_f2;
    }
  }
  else {
    tmp_i6 = *(int *)(param_1 + 0x40);
  }
  local_60 = *(float *)(param_1 + 0x34);
  local_5c = *(float *)(param_1 + 0x38);
  local_58 = *(float *)(param_1 + 0x3c);
  tmp_f2 = *(float *)(param_1 + 0x44);
  tmp_f3 = *(float *)(param_1 + 0x48);
  tmp_f4 = *(float *)(param_1 + 0x4c);
  tmp_i7 = g_unk_010906e0;
  if ((1.0 < tmp_f1) && (tmp_i7 = tmp_i6, tmp_i6 != g_unk_010906e0)) {
    do {
      tmp_f1 = ((float)(g_unk_010906e0 - tmp_i7) / 1000.0) * tmp_f1;
      local_6c = tmp_f2 * tmp_f1 + local_60;
      local_68 = tmp_f3 * tmp_f1 + local_5c;
      local_64 = tmp_f1 * tmp_f4 + local_58;
      CG_Trace(local_54,&local_60,flameChunkMins,flameChunkMaxs,&local_6c,
               *(uint32_t *)(param_1 + 0x1c),0x6000039);
      if (local_50 != 0) {
        local_60 = *(float *)(param_1 + 0x34);
        tmp_f2 = *(float *)(param_1 + 0x44);
        local_5c = *(float *)(param_1 + 0x38);
        tmp_f3 = *(float *)(param_1 + 0x48);
        local_58 = *(float *)(param_1 + 0x3c);
        *(uint32_t *)(param_1 + 0x50) = 0;
        tmp_f4 = *(float *)(param_1 + 0x4c);
        *(uint32_t *)(param_1 + 0x18) = 1;
        tmp_f1 = 0.0;
        tmp_i6 = *(int *)(param_1 + 0x40);
        tmp_i7 = g_unk_010906e0;
        break;
      }
      if ((local_28 & 0x10) != 0) {
LAB_0007e910:
        tmp_f2 = *(float *)(param_1 + 0x44);
        tmp_f1 = *(float *)(param_1 + 0x50);
        tmp_f3 = *(float *)(param_1 + 0x48);
        tmp_f4 = *(float *)(param_1 + 0x4c);
        tmp_i6 = *(int *)(param_1 + 0x40);
        tmp_i7 = g_unk_010906e0;
        local_58 = *(float *)(param_1 + 0x3c);
        local_5c = *(float *)(param_1 + 0x38);
        local_60 = *(float *)(param_1 + 0x34);
        break;
      }
      *(float *)(param_1 + 0x34) = local_48;
      *(float *)(param_1 + 0x38) = local_44;
      *(float *)(param_1 + 0x3c) = local_40;
      tmp_i6 = (int)ROUND((float)(g_unk_010906e0 - *(int *)(param_1 + 0x40)) * local_4c) +
              *(int *)(param_1 + 0x40);
      *(int *)(param_1 + 0x40) = tmp_i6;
      if (local_4c == 1.0) {
        if ((*(int *)(param_1 + 0x1c) == *(int *)(g_unk_01047b00 + 0xcc)) ||
           ((*(byte *)(g_unk_01047b00 + 0x94) & 1) != 0)) {
          tmp_f2 = *(float *)(param_1 + 0x44);
          tmp_f1 = *(float *)(param_1 + 0x50);
          tmp_f3 = *(float *)(param_1 + 0x48);
          tmp_f4 = *(float *)(param_1 + 0x4c);
          tmp_i7 = g_unk_010906e0;
          local_58 = local_40;
          local_5c = local_44;
          local_60 = local_48;
          break;
        }
        tmp_l8 = (long double)VectorDistance(&local_6c,g_unk_01047b00 + 0x40);
        if ((long double)32.0 <= tmp_l8) goto LAB_0007e910;
        tmp_f1 = *(float *)(param_1 + 0x44);
        local_3c = -tmp_f1;
        tmp_f2 = *(float *)(param_1 + 0x48);
        local_38 = -tmp_f2;
        tmp_f3 = *(float *)(param_1 + 0x4c);
        local_34 = -tmp_f3;
      }
      else {
        tmp_f1 = *(float *)(param_1 + 0x44);
        tmp_f2 = *(float *)(param_1 + 0x48);
        tmp_f3 = *(float *)(param_1 + 0x4c);
      }
      tmp_f5 = tmp_f3 * local_34 + tmp_f2 * local_38 + tmp_f1 * local_3c;
      tmp_f4 = tmp_f5 * -2.0;
      *(float *)(param_1 + 0x44) = local_3c * tmp_f4 + tmp_f1;
      *(float *)(param_1 + 0x48) = local_38 * tmp_f4 + tmp_f2;
      *(float *)(param_1 + 0x4c) = tmp_f3 + tmp_f4 * local_34;
      VectorNormalize(param_1 + 0x44);
      tmp_f1 = ((tmp_f5 + 1.0) * 0.5 * 0.75 + 0.25) * 0.5 * *(float *)(param_1 + 0x50);
      *(float *)(param_1 + 0x50) = tmp_f1;
      tmp_f2 = *(float *)(param_1 + 0x44);
      *(float *)(param_1 + 0x90) = tmp_f2;
      tmp_f3 = *(float *)(param_1 + 0x48);
      *(float *)(param_1 + 0x94) = tmp_f3;
      tmp_f4 = *(float *)(param_1 + 0x4c);
      *(float *)(param_1 + 0x98) = tmp_f4;
      local_60 = *(float *)(param_1 + 0x34);
      local_5c = *(float *)(param_1 + 0x38);
      local_58 = *(float *)(param_1 + 0x3c);
      if (tmp_f1 <= 1.0) {
        tmp_i6 = *(int *)(param_1 + 0x40);
        tmp_i7 = g_unk_010906e0;
        break;
      }
      tmp_i7 = *(int *)(param_1 + 0x40);
      tmp_i6 = g_unk_010906e0;
    } while (tmp_i7 != g_unk_010906e0);
  }
  tmp_f1 = ((float)(tmp_i7 - tmp_i6) / 1000.0) * tmp_f1;
  *(float *)(param_1 + 0x74) = tmp_f2 * tmp_f1 + local_60;
  *(float *)(param_1 + 0x78) = tmp_f3 * tmp_f1 + local_5c;
  *(float *)(param_1 + 0x7c) = tmp_f1 * tmp_f4 + local_58;
  *(int *)(param_1 + 0x40) = g_unk_010906e0;
  return;
}

void CG_UpdateFlamethrowerSounds(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  for (tmp_i1 = headFlameChunks; tmp_i1 != 0; tmp_i1 = *(int *)(tmp_i1 + 0xc)) {
    tmp_i3 = g_unk_010906e0;
    tmp_i4 = tmp_i1;
    if (*(int *)(centFlameInfo + *(int *)(tmp_i1 + 0x1c) * 0x34 + 0x20) != g_unk_010906e0) {
      tmp_i3 = tmp_i1 + 0x74;
      if ((float)(&centFlameStatus)[*(int *)(tmp_i1 + 0x1c) * 2] * 255.0 <= 30.0) {
        trap_S_AddLoopingSound(tmp_i3,&vec3_origin,GHIDRA_FIELD(cgs, 69520, 4),0x1e,0);
      }
      else {
        trap_S_AddLoopingSound
                  (tmp_i3,&vec3_origin,GHIDRA_FIELD(cgs, 69520, 4),
                   (int)ROUND((float)(&centFlameStatus)[*(int *)(tmp_i1 + 0x1c) * 2] * 255.0),0);
      }
      tmp_i2 = *(int *)(tmp_i1 + 0x1c);
      if ((float)(&g_unk_002bb464)[tmp_i2 * 2] != 0.0) {
        trap_S_AddLoopingSound
                  (tmp_i3,&vec3_origin,GHIDRA_FIELD(cgs, 69528, 4),
                   (int)ROUND((float)(&g_unk_002bb464)[tmp_i2 * 2] * 255.0),0);
        tmp_i2 = *(int *)(tmp_i1 + 0x1c);
      }
      tmp_i3 = g_unk_010906e0;
      *(int *)(centFlameInfo + tmp_i2 * 0x34 + 0x20) = g_unk_010906e0;
    }
    do {
      if (*(int *)(tmp_i4 + 0x5c) + 100 < tmp_i3 - *(int *)(tmp_i4 + 0x20)) {
        trap_S_AddLoopingSound
                  (tmp_i4 + 0x74,&vec3_origin,GHIDRA_FIELD(cgs, 69516, 4),
                   (int)ROUND((*(float *)(tmp_i4 + 0x80) / 175.0) * 0.2 * 255.0),0);
        tmp_i4 = *(int *)(tmp_i4 + 8);
      }
      else {
        tmp_i4 = *(int *)(tmp_i4 + 8);
      }
      tmp_i3 = g_unk_010906e0;
    } while (tmp_i4 != 0);
  }
  return;
}

void CG_DemoHelpDraw_part_1(void)
{
  float tmp_f1;
  uint tmp_u2;
  int tmp_i3;
  int tmp_i4;
  int *tmp_pi5;
  float local_d4;
  int local_d0;
  int local_c8;
  uint32_t local_b0;
  uint32_t local_ac;
  uint32_t local_a8;
  float local_a4;
  uint32_t local_a0;
  uint32_t local_9c;
  uint32_t local_98;
  float local_94;
  uint32_t local_90;
  uint32_t local_8c;
  uint32_t local_88;
  float local_84;
  uint32_t local_80;
  uint32_t local_7c;
  uint32_t local_78;
  float local_74;
  uint32_t local_70;
  uint32_t local_6c;
  uint32_t local_68;
  float local_64;
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  float local_54;
  int local_50 [15];
  uint32_t uStack_14;
  
  tmp_i4 = g_unk_01093524;
  tmp_u2 = 0;
  uStack_14 = 0x8082b;
  do {
    *(uint32_t *)((int)local_50 + tmp_u2) =
         *(uint32_t *)((int)&g_ptr_s_nTAB_mscores_00145080 + tmp_u2);
    tmp_u2 = tmp_u2 + 4;
  } while (tmp_u2 < 0x34);
  local_b0 = 0;
  local_ac = 0;
  local_a8 = 0;
  local_a4 = 0.6;
  local_a0 = 0x3f000000;
  local_9c = 0x3f000000;
  local_98 = 0x3f000000;
  local_94 = 0.5;
  local_90 = 0x3e23d70a;
  local_8c = 0x3e4ccccd;
  local_88 = 0x3e2e147b;
  local_84 = 0.8;
  local_80 = 0x3dcccccd;
  local_7c = 0x3dcccccd;
  local_78 = 0x3dcccccd;
  local_74 = 0.2;
  local_70 = 0x3f19999a;
  local_6c = 0x3f19999a;
  local_68 = 0x3ecccccd;
  local_64 = 1.0;
  local_60 = 0x3f200000;
  local_5c = 0x3f200000;
  local_58 = 0x3f19999a;
  local_54 = 1.0;
  tmp_i3 = trap_Milliseconds();
  if ((float)(tmp_i4 - tmp_i3) <= 0.0) {
    if (g_unk_010afbc8 == 1) {
      g_unk_010afbc8 = 0;
      return;
    }
    local_d4 = 267.0;
    local_c8 = 0x118;
    local_d0 = 0x115;
  }
  else {
    tmp_f1 = (float)(tmp_i4 - tmp_i3) / 200.0;
    if (g_unk_010afbc8 == 2) {
      tmp_f1 = 1.0 - tmp_f1;
    }
    local_a4 = local_a4 * tmp_f1;
    local_84 = local_84 * tmp_f1;
    local_94 = local_94 * tmp_f1;
    local_74 = local_74 * tmp_f1;
    local_64 = local_64 * tmp_f1;
    local_54 = local_54 * tmp_f1;
    tmp_i4 = (int)ROUND(tmp_f1 * -213.0 + 480.0);
    local_d0 = tmp_i4 + 10;
    local_c8 = tmp_i4 + 0xd;
    local_d4 = (float)tmp_i4;
  }
  tmp_pi5 = local_50;
  CG_DrawRect(0x43ec0000,local_d4,0x43140000,0x43190000,0x3f800000,&local_a0);
  CG_FillRect(0x43ec0000,local_d4,0x43140000,0x43190000,&local_b0);
  CG_FillRect(0x43ec0000,local_d4,0x43140000,0x41500000,&local_90);
  CG_DrawRect(0x43ec0000,local_d4,0x43140000,0x41500000,0x3f800000,&local_80);
  CG_Text_Paint_Ext(0x43ee0000,(float)local_d0,0x3e23d70a,0x3e570a3d,&local_70,"DEMO CONTROLS",0,0,3
                    ,0x1100f64);
  tmp_i4 = local_c8;
  do {
    tmp_i4 = tmp_i4 + 9;
    if (*tmp_pi5 != 0) {
      CG_Text_Paint_Ext(0x43ee0000,(float)tmp_i4,0x3e428f5c,0x3e428f5c,&local_60,*tmp_pi5,0,0,3,
                        0x110afec);
    }
    tmp_pi5 = tmp_pi5 + 1;
  } while (tmp_i4 != local_c8 + 0x75);
  CG_Text_Paint_Ext(0x43ee0000,(float)(local_c8 + 0x87),0x3e428f5c,0x3e428f5c,&local_60,
                    "^nBACKSPACE ^mhelp on/off",0,0,3,0x110afec);
  return;
}

void CG_LoadingString(char *param_1)
{
  uint32_t tmp_u1;
  
  Q_strncpyz(&g_unk_01091a7c,param_1,0x400);
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    tmp_u1 = va("LOADING... %s\n",param_1);
    CG_Printf(tmp_u1);
  }
  return;
}

void CG_ShowHelp_On(int *param_1)
{
  float tmp_f1;
  int tmp_i2;
  
  tmp_i2 = trap_Milliseconds();
  if (*param_1 == 1) {
    if (g_unk_01093524 <= tmp_i2) goto LAB_00080d81;
    tmp_f1 = ((float)(tmp_i2 * 2) + 200.0) - (float)g_unk_01093524;
  }
  else {
    if (*param_1 == 2) goto LAB_00080daf;
LAB_00080d81:
    tmp_f1 = (float)tmp_i2 + 200.0;
  }
  g_unk_01093524 = (int)ROUND(tmp_f1);
LAB_00080daf:
  *param_1 = 2;
  return;
}

void CG_ShowHelp_Off(int *param_1)
{
  float tmp_f1;
  int tmp_i2;
  
  if (*param_1 == 0) {
    return;
  }
  tmp_i2 = trap_Milliseconds();
  if (tmp_i2 < g_unk_01093524) {
    tmp_f1 = ((float)(tmp_i2 * 2) + 200.0) - (float)g_unk_01093524;
  }
  else {
    tmp_f1 = (float)tmp_i2 + 200.0;
  }
  g_unk_01093524 = (int)ROUND(tmp_f1);
  *param_1 = 1;
  return;
}

void CG_DemoClick(int param_1,int param_2)
{
  float tmp_f1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint8_t *tmp_pu4;
  char *tmp_pc5;
  uint8_t *tmp_pu6;
  
  tmp_i2 = trap_Milliseconds();
  if (param_2 != 0) {
    *(int *)(cgs + param_1 * 4 + 0x200ad84) = param_2;
    switch(param_1) {
    case 9:
      CG_ScoresDown_f();
      return;
    default:
      return;
    case 0x1b:
      goto _L64;
    case 0x84:
      goto _L76;
    case 0x85:
      goto _L78;
    case 0x86:
      goto _L83;
    case 0x87:
      goto _L80;
    case 0x91:
      GHIDRA_FIELD(cgs, 33575984, 4) = GHIDRA_FIELD(demo_avifpsF1, 12, 4);
      return;
    case 0x92:
      GHIDRA_FIELD(cgs, 33575984, 4) = GHIDRA_FIELD(demo_avifpsF2, 12, 4);
      return;
    case 0x93:
      GHIDRA_FIELD(cgs, 33575984, 4) = GHIDRA_FIELD(demo_avifpsF3, 12, 4);
      return;
    case 0x94:
      GHIDRA_FIELD(cgs, 33575984, 4) = GHIDRA_FIELD(demo_avifpsF4, 12, 4);
      return;
    case 0x95:
      GHIDRA_FIELD(cgs, 33575984, 4) = GHIDRA_FIELD(demo_avifpsF5, 12, 4);
      return;
    case 0xb7:
      goto _L88;
    case 0xb8:
      goto _L92;
    }
  }
  if (*(int *)(cgs + (param_1 + 0x802b60) * 4 + 4) == 0) {
    return;
  }
  *(uint32_t *)(cgs + (param_1 + 0x802b60) * 4 + 4) = 0;
  switch(param_1) {
  case 9:
    CG_ScoresUp_f();
    break;
  case 0xd:
    if (GHIDRA_FIELD(cg_thirdPerson, 12, 4) == 0) {
      tmp_pu6 = &g_unk_0011e9db;
    }
    else {
      tmp_pu6 = &g_unk_0011e957;
    }
    trap_Cvar_Set("cg_thirdperson",tmp_pu6);
    break;
  case 0x1b:
_L64:
    if (g_unk_010afbc8 != 0) {
      tmp_i2 = trap_Milliseconds();
      if (tmp_i2 < g_unk_01093524) {
        tmp_f1 = ((float)(tmp_i2 * 2) + 200.0) - (float)g_unk_01093524;
      }
      else {
        tmp_f1 = (float)tmp_i2 + 200.0;
      }
      g_unk_01093524 = (int)ROUND(tmp_f1);
      g_unk_010afbc8 = 1;
    }
    CG_keyOff_f();
    return;
  case 0x20:
  case 0xa4:
  case 0xaa:
    trap_Cvar_Set("timescale",&g_unk_0011e9db);
    GHIDRA_FIELD(cgs, 33599876, 4) = g_unk_010906e0 + 1000;
    break;
  case 0x7f:
    if (g_unk_010afbc8 == 2) {
      tmp_i2 = trap_Milliseconds();
      if (tmp_i2 < g_unk_01093524) {
        tmp_f1 = ((float)(tmp_i2 * 2) + 200.0) - (float)g_unk_01093524;
      }
      else {
        tmp_f1 = (float)tmp_i2 + 200.0;
      }
      g_unk_01093524 = (int)ROUND(tmp_f1);
      g_unk_010afbc8 = 1;
      return;
    }
    tmp_i2 = trap_Milliseconds();
    if (g_unk_010afbc8 == 1) {
      if (g_unk_01093524 <= tmp_i2) goto LAB_00080f31;
      tmp_f1 = ((float)(tmp_i2 * 2) + 200.0) - (float)g_unk_01093524;
LAB_00080f3f:
      g_unk_01093524 = (int)ROUND(tmp_f1);
    }
    else if (g_unk_010afbc8 != 2) {
LAB_00080f31:
      tmp_f1 = (float)tmp_i2 + 200.0;
      goto LAB_00080f3f;
    }
    g_unk_010afbc8 = 2;
    break;
  case 0x84:
    goto _L76;
  case 0x85:
_L78:
    if (tmp_i2 <= (int)GHIDRA_FIELD(cgs, 33599880, 4)) {
      return;
    }
    if (720.0 <= (float)GHIDRA_FIELD(cg_thirdPersonRange, 8, 4)) {
      tmp_f1 = 0.0;
    }
    else {
      tmp_f1 = 6.0;
    }
    tmp_f1 = tmp_f1 + (float)GHIDRA_FIELD(cg_thirdPersonRange, 8, 4);
    goto LAB_00081105;
  case 0x86:
_L83:
    if (tmp_i2 <= (int)GHIDRA_FIELD(cgs, 33599880, 4)) {
      return;
    }
    tmp_f1 = (float)GHIDRA_FIELD(cg_thirdPersonAngle, 8, 4) + 4.0;
    if (360.0 <= tmp_f1) {
      tmp_f1 = tmp_f1 - 360.0;
    }
LAB_000810a0:
    GHIDRA_FIELD(cgs, 33599880, 4) = tmp_i2;
    tmp_u3 = va(&g_unk_0011e95f,(double)tmp_f1);
    trap_Cvar_Set("cg_thirdPersonAngle",tmp_u3);
    return;
  case 0x87:
_L80:
    if (tmp_i2 <= (int)GHIDRA_FIELD(cgs, 33599880, 4)) {
      return;
    }
    tmp_f1 = (float)GHIDRA_FIELD(cg_thirdPersonAngle, 8, 4) - 4.0;
    if (tmp_f1 < 0.0) {
      tmp_f1 = tmp_f1 + 360.0;
    }
    goto LAB_000810a0;
  case 0x91:
    tmp_pu4 = demo_avifpsF1;
    goto LAB_00081306;
  case 0x92:
    tmp_pu4 = demo_avifpsF2;
    goto LAB_00081306;
  case 0x93:
    tmp_pu4 = demo_avifpsF3;
    goto LAB_00081306;
  case 0x94:
    tmp_pu4 = demo_avifpsF4;
    goto LAB_00081306;
  case 0x95:
    tmp_pu4 = demo_avifpsF5;
LAB_00081306:
    trap_Cvar_Set("cl_avidemo",tmp_pu4 + 0x10);
    break;
  case 0x9b:
    if (GHIDRA_FIELD(cgs, 33823104, 4) == 0) {
      if (GHIDRA_FIELD(cg_useScreenshotJPEG, 12, 4) == 0) {
        tmp_pc5 = "";
      }
      else {
        tmp_pc5 = "JPEG";
      }
      tmp_u3 = va("screenshot%s\n",tmp_pc5);
      trap_SendConsoleCommand(tmp_u3);
    }
    else {
      trap_SendConsoleCommand("screenshot%s\n");
    }
    break;
  case 0x9c:
    CG_autoScreenShot_f();
    break;
  case 0xa1:
    tmp_u3 = va(&g_unk_0011e95f,(double)((float)GHIDRA_FIELD(cg_timescale, 8, 4) + 1.0));
    trap_Cvar_Set("timescale",tmp_u3);
    tmp_f1 = (float)GHIDRA_FIELD(cg_timescale, 8, 4) * 1000.0 + 1.0;
    goto LAB_00081250;
  case 0xa3:
    goto _L90;
  case 0xa5:
    goto _L94;
  case 0xa7:
    if (1.1 < (float)GHIDRA_FIELD(cg_timescale, 8, 4)) {
      tmp_f1 = (float)GHIDRA_FIELD(cg_timescale, 8, 4) - 1.0;
    }
    else {
      tmp_f1 = (float)GHIDRA_FIELD(cg_timescale, 8, 4);
      if (0.1 < (float)GHIDRA_FIELD(cg_timescale, 8, 4)) {
        tmp_f1 = (float)GHIDRA_FIELD(cg_timescale, 8, 4) - 0.1;
      }
    }
    tmp_u3 = va(&g_unk_0011e95f,(double)tmp_f1);
    trap_Cvar_Set("timescale",tmp_u3);
    tmp_f1 = tmp_f1 * 1000.0;
    goto LAB_00081250;
  case 0xb7:
_L88:
    if (GHIDRA_FIELD(cgs, 33599404, 4) == 0) {
      if (param_2 != 0) {
        return;
      }
      CG_ZoomOut_f();
      return;
    }
    if (param_2 != 0) {
      return;
    }
    goto _L90;
  case 0xb8:
_L92:
    if (GHIDRA_FIELD(cgs, 33599404, 4) == 0) {
      if (param_2 != 0) {
        return;
      }
      CG_ZoomIn_f();
      return;
    }
    if (param_2 != 0) {
      return;
    }
    goto _L94;
  }
  return;
_L94:
  tmp_u3 = va(&g_unk_0011e95f,(double)((float)GHIDRA_FIELD(cg_timescale, 8, 4) + 0.1));
  trap_Cvar_Set("timescale",tmp_u3);
  tmp_f1 = (float)GHIDRA_FIELD(cg_timescale, 8, 4) * 1000.0 + 0.1;
  goto LAB_00081250;
_L76:
  if (tmp_i2 <= (int)GHIDRA_FIELD(cgs, 33599880, 4)) {
    return;
  }
  if (24.0 <= (float)GHIDRA_FIELD(cg_thirdPersonRange, 8, 4)) {
    tmp_f1 = (float)GHIDRA_FIELD(cg_thirdPersonRange, 8, 4) - 6.0;
  }
  else {
    tmp_f1 = (float)GHIDRA_FIELD(cg_thirdPersonRange, 8, 4) - ((float)GHIDRA_FIELD(cg_thirdPersonRange, 8, 4) - 6.0);
  }
LAB_00081105:
  GHIDRA_FIELD(cgs, 33599880, 4) = tmp_i2;
  tmp_u3 = va(&g_unk_0011e95f,(double)tmp_f1);
  trap_Cvar_Set("cg_thirdPersonRange",tmp_u3);
  return;
_L90:
  if ((float)GHIDRA_FIELD(cg_timescale, 8, 4) <= 0.1) {
    return;
  }
  tmp_u3 = va(&g_unk_0011e95f,(double)((float)GHIDRA_FIELD(cg_timescale, 8, 4) - 0.1));
  trap_Cvar_Set("timescale",tmp_u3);
  tmp_f1 = (float)GHIDRA_FIELD(cg_timescale, 8, 4) * 1000.0 - 0.1;
LAB_00081250:
  GHIDRA_FIELD(cgs, 33599876, 4) = (int)ROUND(tmp_f1) + g_unk_010906e0;
  return;
}

void CG_GameStatsDraw(void)
{
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  int local_84;
  float local_7c;
  int local_78;
  int local_6c;
  int local_68;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  float local_50;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  float local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x81669;
  if (GHIDRA_FIELD(cgs, 33585516, 4) == 0) {
    return;
  }
  local_5c = 0x3e23d70a;
  local_58 = 0x3e4ccccd;
  local_54 = 0x3e2e147b;
  local_50 = 0.8;
  local_4c = 0x3dcccccd;
  local_48 = 0x3dcccccd;
  tmp_i2 = 1;
  if (0 < (int)GHIDRA_FIELD(cgs, 33585492, 4)) {
    tmp_i2 = GHIDRA_FIELD(cgs, 33585492, 4);
  }
  local_44 = 0x3dcccccd;
  tmp_i2 = (~-(uint)(GHIDRA_FIELD(cgs, 33585500, 4) == 0) & 0x1b) + tmp_i2 * 9 + 0x1d;
  local_40 = 0.2;
  local_3c = 0x3f19999a;
  local_38 = 0x3f19999a;
  local_34 = 0x3f19999a;
  local_2c = 0x3f200000;
  local_28 = 0x3f200000;
  local_24 = 0x3f19999a;
  local_20 = 1.0;
  if (GHIDRA_FIELD(cgs, 27388, 4) == 5) {
    tmp_i2 = tmp_i2 + 0xb;
  }
  else {
    tmp_i3 = 1;
    if (0 < (int)GHIDRA_FIELD(cgs, 33585496, 4)) {
      tmp_i3 = GHIDRA_FIELD(cgs, 33585496, 4);
    }
    tmp_i2 = tmp_i3 * 9 + 0x42 + tmp_i2;
  }
  if ((float)(GHIDRA_FIELD(cgs, 33585512, 4) - g_unk_010906e0) <= 0.0) {
    if (GHIDRA_FIELD(cgs, 33585516, 4) == 1) {
      GHIDRA_FIELD(cgs, 33585516, 4) = 0;
      return;
    }
    tmp_i3 = 10;
    local_84 = 0x28;
    local_68 = 0x25;
    local_6c = 0x1b;
    local_78 = 0x14;
  }
  else {
    local_20 = (float)(GHIDRA_FIELD(cgs, 33585512, 4) - g_unk_010906e0) / 200.0;
    if (GHIDRA_FIELD(cgs, 33585516, 4) == 2) {
      local_20 = 1.0 - local_20;
    }
    local_50 = local_20 * 0.8;
    local_40 = local_20 * 0.2;
    tmp_i3 = (int)ROUND(10.0 - (1.0 - local_20) * (float)tmp_i2);
    local_78 = tmp_i3 + 10;
    local_6c = tmp_i3 + 0x11;
    local_68 = tmp_i3 + 0x1b;
    local_84 = tmp_i3 + 0x1e;
  }
  local_7c = (float)tmp_i2;
  local_30 = local_20;
  CG_HudPlacement(0);
  tmp_f1 = (float)tmp_i3;
  CG_DrawRect(0x43260000,tmp_f1,0x439a0000,local_7c,0x3f800000,&HUD_Border);
  CG_FillRect(0x43260000,tmp_f1,0x439a0000,local_7c,&HUD_Background);
  CG_FillRect(0x43260000,tmp_f1,0x439a0000,0x41500000,&local_5c);
  CG_DrawRect(0x43260000,tmp_f1,0x439a0000,0x41500000,0x3f800000,&local_4c);
  CG_Text_Paint_Ext(0x432a0000,(float)local_78,0x3e23d70a,0x3e570a3d,&local_3c,"PLAYER STATS",0,0,3,
                    0x1100f64);
  CG_FillRect(0x43260000,(float)local_6c,0x439a0000,0x41400000,&local_5c);
  CG_DrawRect(0x43260000,(float)local_6c,0x439a0000,0x41400000,0x3f800000,&local_4c);
  tmp_f1 = (float)local_68;
  CG_Text_Paint_Ext(0x432a0000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Weapon",0,0,0,0x1105fa8);
  CG_Text_Paint_Ext(0x436c0000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Accuracy",0,0,0,0x1105fa8);
  CG_Text_Paint_Ext(0x43908000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Hits / Shots",0,0,0,0x1105fa8)
  ;
  CG_Text_Paint_Ext(0x43af8000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Kills",0,0,0,0x1105fa8);
  CG_Text_Paint_Ext(0x43be0000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Deaths",0,0,0,0x1105fa8);
  CG_Text_Paint_Ext(0x43d20000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Headshots",0,0,0,0x1105fa8);
  if (GHIDRA_FIELD(cgs, 33585492, 4) == 0) {
    local_84 = tmp_i3 + 0x27;
    CG_Text_Paint_Ext(0x432a0000,(float)local_84,0x3e428f5c,0x3e428f5c,&local_2c,
                      "No weapon info available.",0,0,3,0x110afec);
  }
  else {
    if (0 < (int)GHIDRA_FIELD(cgs, 33585492, 4)) {
      tmp_i3 = 0;
      tmp_i2 = 0x30f52b4;
      do {
        local_84 = local_84 + 9;
        tmp_i3 = tmp_i3 + 1;
        CG_Text_Paint_Ext(0x432a0000,(float)local_84,0x3e428f5c,0x3e428f5c,&local_2c,tmp_i2,0,0,3,
                          0x110afec);
        tmp_i2 = tmp_i2 + 0x100;
      } while (tmp_i3 < (int)GHIDRA_FIELD(cgs, 33585492, 4));
    }
    if (GHIDRA_FIELD(cgs, 33585500, 4) != 0) {
      tmp_i3 = local_84 + 0x24;
      tmp_i2 = 0x30f6cb4;
      local_84 = local_84 + 9;
      do {
        local_84 = local_84 + 9;
        CG_Text_Paint_Ext(0x432a0000,(float)local_84,0x3e428f5c,0x3e428f5c,&local_2c,tmp_i2,0,0,3,
                          0x110afec);
        tmp_i2 = tmp_i2 + 0x100;
      } while (local_84 != tmp_i3);
    }
  }
  if (GHIDRA_FIELD(cgs, 27388, 4) != 5) {
    CG_FillRect(0x43260000,(float)(local_84 + 0xb),0x439a0000,0x41400000,&local_5c);
    CG_DrawRect(0x43260000,(float)(local_84 + 0xb),0x439a0000,0x41400000,0x3f800000,&local_4c);
    CG_Text_Paint_Ext(0x432a0000,(float)(local_84 + 0x15),0x3e23d70a,0x3e4ccccd,&local_3c,
                      &g_unk_001132b2,0,0,0,0x1105fa8);
    CG_Text_Paint_Ext(0x437c0000,(float)(local_84 + 0x15),0x3e23d70a,0x3e4ccccd,&local_3c,"XP",0,0,0
                      ,0x1105fa8);
    CG_Text_Paint_Ext(0x432a0000,(float)(local_84 + 0x1f),0x3e428f5c,0x3e428f5c,&local_2c,0x30f6fb4,
                      0,0,3,0x110afec);
    CG_FillRect(0x43260000,(float)(local_84 + 0x2a),0x439a0000,0x41400000,&local_5c);
    CG_DrawRect(0x43260000,(float)(local_84 + 0x2a),0x439a0000,0x41400000,0x3f800000,&local_4c);
    tmp_f1 = (float)(local_84 + 0x34);
    CG_Text_Paint_Ext(0x432a0000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Skills",0,0,0,0x1105fa8);
    CG_Text_Paint_Ext(0x437e0000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Level",0,0,0,0x1105fa8);
    CG_Text_Paint_Ext(0x43930000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"XP / Next Level",0,0,0,
                      0x1105fa8);
    if (GHIDRA_FIELD(cgs, 27388, 4) == 4) {
      CG_Text_Paint_Ext(0x43be0000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Medals",0,0,0,0x1105fa8);
    }
    if (GHIDRA_FIELD(cgs, 33585496, 4) == 0) {
      CG_Text_Paint_Ext(0x432a0000,(float)(local_84 + 0x3e),0x3e428f5c,0x3e428f5c,&local_2c,
                        "No skills acquired!",0,0,3,0x110afec);
    }
    else if (0 < (int)GHIDRA_FIELD(cgs, 33585496, 4)) {
      local_84 = local_84 + 0x35;
      tmp_i3 = 0;
      tmp_i2 = 0x30f70b4;
      do {
        local_84 = local_84 + 9;
        tmp_i3 = tmp_i3 + 1;
        CG_Text_Paint_Ext(0x432a0000,(float)local_84,0x3e428f5c,0x3e428f5c,&local_2c,tmp_i2,0,0,3,
                          0x110afec);
        tmp_i2 = tmp_i2 + 0x100;
      } while (tmp_i3 < (int)GHIDRA_FIELD(cgs, 33585496, 4));
    }
  }
  return;
}

void CG_TopShotsDraw(void)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  int local_90;
  uint32_t local_7c;
  uint32_t local_78;
  uint32_t local_74;
  float local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  float local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  float local_50;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  float local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x82259;
  if (GHIDRA_FIELD(cgs, 33598844, 4) != 0) {
    local_7c = 0;
    local_78 = 0;
    local_74 = 0;
    local_70 = 0.6;
    local_20 = 1.0;
    tmp_i3 = 1;
    if (0 < (int)GHIDRA_FIELD(cgs, 33598836, 4)) {
      tmp_i3 = GHIDRA_FIELD(cgs, 33598836, 4);
    }
    local_6c = 0x3f000000;
    local_68 = 0x3f000000;
    local_64 = 0x3f000000;
    local_60 = 0.5;
    local_5c = 0x3e23d70a;
    local_58 = 0x3e4ccccd;
    local_54 = 0x3e2e147b;
    local_50 = 0.8;
    local_4c = 0x3dcccccd;
    local_48 = 0x3dcccccd;
    local_44 = 0x3dcccccd;
    local_40 = 0.2;
    local_3c = 0x3f19999a;
    local_38 = 0x3f19999a;
    local_34 = 0x3f19999a;
    local_2c = 0x3f200000;
    local_28 = 0x3f200000;
    local_24 = 0x3f19999a;
    if ((float)(GHIDRA_FIELD(cgs, 33598840, 4) - g_unk_010906e0) <= 0.0) {
      if (GHIDRA_FIELD(cgs, 33598844, 4) == 1) {
        GHIDRA_FIELD(cgs, 33598844, 4) = 0;
        return;
      }
      local_90 = tmp_i3 * -9 + 0x186;
    }
    else {
      local_20 = (float)(GHIDRA_FIELD(cgs, 33598840, 4) - g_unk_010906e0) / 200.0;
      if (GHIDRA_FIELD(cgs, 33598844, 4) == 2) {
        local_20 = 1.0 - local_20;
      }
      local_70 = local_20 * 0.6;
      local_50 = local_20 * 0.8;
      local_60 = local_20 * 0.5;
      local_40 = local_20 * 0.2;
      local_90 = (int)ROUND((float)(tmp_i3 * -9 + -0x5a) * local_20 + 480.0);
    }
    local_30 = local_20;
    CG_HudPlacement(1);
    tmp_f1 = (float)(tmp_i3 * 9 + 0x1e);
    tmp_f2 = (float)local_90;
    CG_DrawRect(0x439c0000,tmp_f2,0x439a0000,tmp_f1,0x3f800000,&local_6c);
    CG_FillRect(0x439c0000,tmp_f2,0x439a0000,tmp_f1,&local_7c);
    CG_FillRect(0x439c0000,tmp_f2,0x439a0000,0x41500000,&local_5c);
    CG_DrawRect(0x439c0000,tmp_f2,0x439a0000,0x41500000,0x3f800000,&local_4c);
    CG_Text_Paint_Ext(0x439e0000,(float)(local_90 + 10),0x3e23d70a,0x3e570a3d,&local_3c,
                      "\"TOPSHOT\" ACCURACIES",0,0,3,0x1100f64);
    CG_FillRect(0x439c0000,(float)(local_90 + 0x10),0x439a0000,0x41400000,&local_5c);
    CG_DrawRect(0x439c0000,(float)(local_90 + 0x10),0x439a0000,0x41400000,0x3f800000,&local_4c);
    tmp_f1 = (float)(local_90 + 0x1a);
    CG_Text_Paint_Ext(0x439e0000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Weapon",0,0,0,0x1105fa8);
    CG_Text_Paint_Ext(0x43bc0000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Accuracy",0,0,0,0x1105fa8);
    CG_Text_Paint_Ext(0x43d68000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Hits / Shots",0,0,0,
                      0x1105fa8);
    CG_Text_Paint_Ext(0x43f58000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Kills",0,0,0,0x1105fa8);
    CG_Text_Paint_Ext(0x4402c000,tmp_f1,0x3e23d70a,0x3e4ccccd,&local_3c,"Player",0,0,0,0x1105fa8);
    if (GHIDRA_FIELD(cgs, 33598836, 4) == 0) {
      CG_Text_Paint_Ext(0x439e0000,(float)(local_90 + 0x24),0x3e428f5c,0x3e428f5c,&local_2c,
                        "No qualifying weapon info available.",0,0,3,0x110afec);
      return;
    }
    if (0 < (int)GHIDRA_FIELD(cgs, 33598836, 4)) {
      local_90 = local_90 + 0x1b;
      tmp_i4 = 0;
      tmp_i3 = 0x30f77d4;
      do {
        local_90 = local_90 + 9;
        tmp_i4 = tmp_i4 + 1;
        CG_Text_Paint_Ext(0x439e0000,(float)local_90,0x3e428f5c,0x3e428f5c,&local_2c,tmp_i3,0,0,3,
                          0x110afec);
        tmp_i3 = tmp_i3 + 0x100;
      } while (tmp_i4 < (int)GHIDRA_FIELD(cgs, 33598836, 4));
    }
  }
  return;
}

void CG_DemoHelpDraw(void)
{
  if (g_unk_010afbc8 == 0) {
    return;
  }
  CG_DemoHelpDraw_part_1();
  return;
}

char * CG_getBindKeyName(uint32_t param_1,char *param_2,uint32_t param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  tmp_i3 = 0;
  do {
    trap_Key_GetBindingBuf(tmp_i3,param_2,param_3);
    if (*param_2 != '\0') {
      tmp_i1 = Q_stricmp(param_2,param_1);
      if (tmp_i1 == 0) {
        trap_Key_KeynumToStringBuf(tmp_i3,param_2,0x100);
        Q_strupr(param_2);
        return param_2;
      }
    }
    tmp_i3 = tmp_i3 + 1;
  } while (tmp_i3 != 0x100);
  tmp_u2 = va(&g_unk_0011d980,param_1);
  Q_strncpyz(param_2,tmp_u2,param_3);
  return param_2;
}

void CG_SpecHelpDraw(void)
{
  uint tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint tmp_u4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  uint *tmp_pu8;
  uint *tmp_pu9;
  float tmp_f10;
  int tmp_i11;
  int tmp_i12;
  int *tmp_pi13;
  int *local_320;
  float local_318;
  int local_314;
  uint32_t local_2fc;
  uint32_t local_2f8;
  uint32_t local_2f4;
  float local_2f0;
  uint32_t local_2ec;
  uint32_t local_2e8;
  uint32_t local_2e4;
  float local_2e0;
  uint32_t local_2dc;
  uint32_t local_2d8;
  uint32_t local_2d4;
  float local_2d0;
  uint32_t local_2cc;
  uint32_t local_2c8;
  uint32_t local_2c4;
  float local_2c0;
  uint32_t local_2bc;
  uint32_t local_2b8;
  uint32_t local_2b4;
  float local_2b0;
  uint32_t local_2ac;
  uint32_t local_2a8;
  uint32_t local_2a4;
  float local_2a0;
  int local_29c [16];
  int local_25c [16];
  uint8_t local_21c [256];
  uint local_11c [66];
  uint32_t uStack_14;
  
  tmp_i12 = g_unk_01093524;
  uStack_14 = 0x82999;
  if (g_unk_010afbd4 == 0) {
    return;
  }
  tmp_u1 = 0;
  do {
    *(uint32_t *)((int)local_29c + tmp_u1) = *(uint32_t *)((int)&g_ptr_s_zoom_001450c0 + tmp_u1);
    tmp_u1 = tmp_u1 + 4;
  } while (tmp_u1 < 0x40);
  local_2fc = 0;
  local_2f8 = 0;
  local_2f4 = 0;
  local_2f0 = 0.6;
  local_2ec = 0x3f000000;
  local_2e8 = 0x3f000000;
  local_2e4 = 0x3f000000;
  local_2e0 = 0.5;
  local_2dc = 0x3e23d70a;
  local_2d8 = 0x3e4ccccd;
  local_2d4 = 0x3e2e147b;
  local_2d0 = 0.8;
  local_2cc = 0x3dcccccd;
  local_2c8 = 0x3dcccccd;
  local_2c4 = 0x3dcccccd;
  local_2c0 = 0.2;
  local_2bc = 0x3f19999a;
  local_2b8 = 0x3f19999a;
  local_2b4 = 0x3ecccccd;
  local_2b0 = 1.0;
  local_2ac = 0x3f200000;
  local_2a8 = 0x3f200000;
  local_2a4 = 0x3f19999a;
  local_2a0 = 1.0;
  tmp_i2 = trap_Milliseconds();
  tmp_pi13 = local_25c;
  local_318 = 0.0;
  local_320 = local_29c;
  do {
    tmp_i7 = *local_320;
    tmp_f10 = local_318;
    if (tmp_i7 != 0) {
      tmp_i11 = 0;
      do {
        trap_Key_GetBindingBuf(tmp_i11,local_11c,0x100);
        if (((char)local_11c[0] != '\0') && (tmp_i3 = Q_stricmp(local_11c,tmp_i7), tmp_i3 == 0)) {
          trap_Key_KeynumToStringBuf(tmp_i11,local_11c,0x100);
          Q_strupr(local_11c);
          tmp_pu9 = local_11c;
          goto LAB_00082b93;
        }
        tmp_i11 = tmp_i11 + 1;
      } while (tmp_i11 != 0x100);
      tmp_u5 = va(&g_unk_0011d980,tmp_i7);
      Q_strncpyz(local_11c,tmp_u5,0x100);
      tmp_pu9 = local_11c;
LAB_00082b93:
      do {
        tmp_pu8 = tmp_pu9;
        tmp_u4 = *tmp_pu8 + 0xfefefeff & ~*tmp_pu8;
        tmp_u1 = tmp_u4 & 0x80808080;
        tmp_pu9 = tmp_pu8 + 1;
      } while (tmp_u1 == 0);
      if ((tmp_u4 & 0x8080) == 0) {
        tmp_pu9 = (uint *)((int)tmp_pu8 + 6);
        tmp_u1 = tmp_u1 >> 0x10;
      }
      tmp_f10 = (float)((int)tmp_pu9 + ((-3 - (uint)CARRY1((byte)tmp_u1,(byte)tmp_u1)) - (int)local_11c)
                      );
      if ((int)tmp_f10 <= (int)local_318) {
        tmp_f10 = local_318;
      }
    }
    local_318 = tmp_f10;
    local_320 = local_320 + 2;
  } while (local_320 != tmp_pi13);
  tmp_u5 = va("^2%%%ds ^N%%s",local_318);
  Q_strncpyz(local_21c,tmp_u5,0x100);
  local_318 = 0.0;
  local_320 = (int *)0x0;
  do {
    tmp_i7 = local_29c[(int)local_320 * 2];
    if (tmp_i7 == 0) {
      tmp_pi13[(int)local_320] = 0;
      tmp_f10 = local_318;
    }
    else {
      tmp_i11 = local_29c[(int)local_320 * 2 + 1];
      tmp_i3 = 0;
      do {
        trap_Key_GetBindingBuf(tmp_i3,local_11c,0x100);
        if (((char)local_11c[0] != '\0') && (tmp_i6 = Q_stricmp(local_11c,tmp_i7), tmp_i6 == 0)) {
          trap_Key_KeynumToStringBuf(tmp_i3,local_11c,0x100);
          Q_strupr(local_11c);
          goto LAB_00082cb9;
        }
        tmp_i3 = tmp_i3 + 1;
      } while (tmp_i3 != 0x100);
      tmp_u5 = va(&g_unk_0011d980,tmp_i7);
      Q_strncpyz(local_11c,tmp_u5,0x100);
LAB_00082cb9:
      tmp_i7 = va(local_21c,local_11c,tmp_i11);
      tmp_pi13[(int)local_320] = tmp_i7;
      tmp_f10 = (float)CG_Text_Width_Ext(tmp_i7,0x3e428f5c,0,0x110afec);
      if ((int)tmp_f10 <= (int)local_318) {
        tmp_f10 = local_318;
      }
    }
    local_318 = tmp_f10;
    local_320 = (int *)((int)local_320 + 1);
    if (local_320 == (int *)0x8) {
      tmp_i7 = (int)local_318 + 8;
      if ((float)(tmp_i12 - tmp_i2) <= 0.0) {
        if (g_unk_010afbd4 == 1) {
          g_unk_010afbd4 = 0;
          return;
        }
        local_314 = 6;
        local_318 = 2.0;
      }
      else {
        tmp_f10 = (float)(tmp_i12 - tmp_i2) / 200.0;
        if (g_unk_010afbd4 == 2) {
          tmp_f10 = 1.0 - tmp_f10;
        }
        local_2f0 = local_2f0 * tmp_f10;
        local_2d0 = local_2d0 * tmp_f10;
        local_2e0 = local_2e0 * tmp_f10;
        local_2c0 = local_2c0 * tmp_f10;
        local_2b0 = local_2b0 * tmp_f10;
        local_2a0 = local_2a0 * tmp_f10;
        local_314 = (int)ROUND(2.0 - (1.0 - tmp_f10) * (float)tmp_i7);
        local_318 = (float)local_314;
        local_314 = local_314 + 4;
      }
      local_320 = (int *)(float)tmp_i7;
      tmp_i12 = 0xa8;
      CG_DrawRect(local_318,0x431b0000,local_320,0x42b40000,0x3f800000,&local_2ec);
      CG_FillRect(local_318,0x431b0000,local_320,0x42b40000,&local_2fc);
      CG_FillRect(local_318,0x431b0000,local_320,0x41500000,&local_2dc);
      CG_DrawRect(local_318,0x431b0000,local_320,0x41500000,0x3f800000,&local_2cc);
      CG_Text_Paint_Ext((float)local_314,0x43250000,0x3e23d70a,0x3e570a3d,&local_2bc,
                        "SPECTATOR CONTROLS",0,0,3,0x1100f64);
      do {
        tmp_i12 = tmp_i12 + 9;
        if (*tmp_pi13 != 0) {
          CG_Text_Paint_Ext((float)local_314,(float)tmp_i12,0x3e428f5c,0x3e428f5c,&local_2ac,*tmp_pi13
                            ,0,0,3,0x110afec);
        }
        tmp_pi13 = tmp_pi13 + 1;
      } while (tmp_i12 != 0xf0);
      return;
    }
  } while( true );
}

bool CG_IsHeavyWeapon(int param_1)
{
  if ((((bg_heavyWeapons != param_1) && (g_unk_0013e4a8 != param_1)) && (g_unk_0013e4ac != param_1)) &&
     ((g_unk_0013e4b0 != param_1 && (g_unk_0013e4b4 != param_1)))) {
    return g_unk_0013e4b8 == param_1;
  }
  return true;
}

float * CG_GetLocation(float *param_1)
{
  int tmp_i1;
  int tmp_i2;
  float *pfVar3;
  long double tmp_l4;
  float local_3c;
  float *local_30;
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x8c7b9;
  if ((int)GHIDRA_FIELD(cgs, 33785368, 4) < 1) {
    local_30 = (float *)0x0;
  }
  else {
    local_3c = 2e+08;
    pfVar3 = (float *)(cgs + 0x202461c);
    tmp_i2 = 0;
    local_30 = (float *)0x0;
    do {
      local_28 = *param_1 - *pfVar3;
      local_24 = param_1[1] - pfVar3[1];
      local_20 = param_1[2] - pfVar3[2];
      tmp_l4 = (long double)VectorLength(&local_28);
      if (tmp_l4 <= (long double)local_3c) {
        tmp_i1 = trap_R_inPVS(param_1,pfVar3);
        if (tmp_i1 != 0) {
          local_30 = pfVar3 + -1;
          local_3c = (float)tmp_l4;
        }
      }
      tmp_i2 = tmp_i2 + 1;
      pfVar3 = pfVar3 + 0x14;
    } while (tmp_i2 < (int)GHIDRA_FIELD(cgs, 33785368, 4));
  }
  return local_30;
}

char * CG_GetLocationMsg(float *param_1)
{
  int tmp_i1;
  size_t tmp_s2;
  char *tmp_pc3;
  int tmp_i4;
  float *pfVar5;
  long double tmp_l6;
  float local_3c;
  float *local_30;
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x8c8a9;
  if (0 < (int)GHIDRA_FIELD(cgs, 33785368, 4)) {
    pfVar5 = (float *)(cgs + 0x202461c);
    local_3c = 2e+08;
    local_30 = (float *)0x0;
    tmp_i4 = 0;
    do {
      local_28 = *param_1 - *pfVar5;
      local_24 = param_1[1] - pfVar5[1];
      local_20 = param_1[2] - pfVar5[2];
      tmp_l6 = (long double)VectorLength(&local_28);
      if (tmp_l6 <= (long double)local_3c) {
        tmp_i1 = trap_R_inPVS(param_1,pfVar5);
        if (tmp_i1 != 0) {
          local_30 = pfVar5 + -1;
          local_3c = (float)tmp_l6;
        }
      }
      tmp_i4 = tmp_i4 + 1;
      pfVar5 = pfVar5 + 0x14;
    } while (tmp_i4 < (int)GHIDRA_FIELD(cgs, 33785368, 4));
    if (local_30 != (float *)0x0) {
      tmp_s2 = strlen((char *)(local_30 + 4));
      if (1 < tmp_s2) {
        tmp_pc3 = (char *)va("%s",local_30 + 4);
        return tmp_pc3;
      }
    }
  }
  return "Unknown";
}

void CG_LoadLocations(void)
{
  char *tmp_pc1;
  uint tmp_u2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  long tmp_l7;
  char tmp_c8;
  int tmp_i9;
  int tmp_i10;
  int local_80c8;
  int local_80c4;
  int local_80c0;
  ushort *local_80bc;
  int local_80b8;
  uint32_t local_80a0;
  ushort local_809c [2];
  uint32_t local_8098 [15];
  ushort local_805c [2];
  uint32_t local_8058 [15];
  char local_801c [32776];
  uint32_t uStack_14;
  
  uStack_14 = 0x8c9bb;
  local_809c[1] = 0;
  local_809c[0] = 0;
  tmp_u6 = 0;
  do {
    tmp_u2 = tmp_u6;
    *(uint32_t *)((int)local_8098 + tmp_u2) = 0;
    *(uint32_t *)((int)local_8098 + tmp_u2 + 4) = 0;
    tmp_u6 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0x38);
  *(uint32_t *)((int)local_8098 + tmp_u2 + 8) = 0;
  local_805c[1] = 0;
  tmp_u6 = 0;
  do {
    tmp_u2 = tmp_u6;
    *(uint32_t *)((int)local_8058 + tmp_u2) = 0;
    *(uint32_t *)((int)local_8058 + tmp_u2 + 4) = 0;
    tmp_u6 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0x38);
  *(uint32_t *)((int)local_8058 + tmp_u2 + 8) = 0;
  local_805c[0] = local_809c[0];
  tmp_u3 = va("maps/%s_loc_override.dat",0x10f69ac);
  local_80c0 = trap_FS_FOpenFile(tmp_u3,&local_80a0,0);
  if (local_80c0 < 0) {
    tmp_u3 = va("maps/%s_loc.dat",0x10f69ac);
    local_80c0 = trap_FS_FOpenFile(tmp_u3,&local_80a0,0);
    if (local_80c0 < 0) {
      return;
    }
  }
  if (0x8000 < local_80c0) {
    CG_Error("Location file is too big, make it smaller (max = %i bytes)\n",0x8000);
    trap_FS_FCloseFile(local_80a0);
  }
  local_80c8 = 0;
  trap_FS_Read(local_801c,local_80c0,local_80a0);
  local_801c[local_80c0] = '\0';
  trap_FS_FCloseFile(local_80a0);
LAB_0008cae0:
  if (local_80c0 <= local_80c8) {
    GHIDRA_FIELD(cgs, 33785372, 4) = 1;
    return;
  }
  tmp_i10 = local_80c8 + 1;
  if ((local_801c[local_80c8] == '/') && (local_801c[local_80c8 + 1] == '/')) {
    if (local_80c0 <= tmp_i10) {
      GHIDRA_FIELD(cgs, 33785372, 4) = 1;
      return;
    }
    do {
      tmp_i10 = tmp_i10 + 1;
      if (tmp_i10 == local_80c0) {
        GHIDRA_FIELD(cgs, 33785372, 4) = 1;
        return;
      }
      tmp_c8 = local_801c[tmp_i10];
    } while ((tmp_c8 != '\r') && (tmp_c8 != '\n'));
  }
  else if (local_80c0 <= tmp_i10) {
    GHIDRA_FIELD(cgs, 33785372, 4) = 1;
    return;
  }
  local_80c8 = tmp_i10;
  if (local_80c0 <= tmp_i10) {
    tmp_i5 = 0;
    goto LAB_0008cb98;
  }
  do {
    local_80bc = local_805c;
    tmp_c8 = local_801c[local_80c8];
    if (tmp_c8 == ' ') {
      local_805c[0] = local_805c[0] & 0xff00;
      local_80c4 = strtol((char *)local_80bc,(char **)0x0,10);
      tmp_u6 = 0;
      do {
        *(uint32_t *)((int)local_80bc + tmp_u6) = 0;
        *(uint32_t *)((int)local_8058 + tmp_u6) = 0;
        tmp_u6 = tmp_u6 + 8;
      } while (tmp_u6 < 0x40);
    }
    else {
      tmp_i5 = 0;
      do {
        tmp_i4 = tmp_i5 + 1;
        *(char *)((int)local_805c + tmp_i5) = tmp_c8;
        tmp_i5 = local_80c0 - local_80c8;
        tmp_i10 = tmp_i4 + local_80c8;
        if (tmp_i4 == local_80c0 - local_80c8) break;
        tmp_c8 = local_801c[tmp_i4 + local_80c8];
        tmp_i5 = tmp_i4;
      } while (tmp_c8 != ' ');
LAB_0008cb98:
      local_80c8 = tmp_i10;
      *(char *)((int)local_805c + tmp_i5) = '\0';
      local_80c4 = strtol((char *)local_805c,(char **)0x0,10);
      tmp_u6 = 0;
      do {
        tmp_pc1 = (char *)((int)local_805c + tmp_u6);
        tmp_pc1[0] = '\0';
        tmp_pc1[1] = '\0';
        tmp_pc1[2] = '\0';
        tmp_pc1[3] = '\0';
        *(uint32_t *)((int)local_8058 + tmp_u6) = 0;
        tmp_u6 = tmp_u6 + 8;
      } while (tmp_u6 < 0x40);
      if (local_80c0 < local_80c8) goto LAB_0008cae0;
    }
    local_80bc = local_805c;
    tmp_i10 = local_80c8 + 1;
    if (tmp_i10 < local_80c0) {
      tmp_c8 = local_801c[local_80c8 + 1];
      if (tmp_c8 != ' ') {
        tmp_i4 = (local_80c0 + -1) - local_80c8;
        tmp_i5 = 0;
        local_80c8 = tmp_i10;
        do {
          tmp_i9 = tmp_i5 + 1;
          local_80c8 = local_80c8 + 1;
          *(char *)((int)local_805c + tmp_i5) = tmp_c8;
          tmp_i10 = tmp_i4;
          if (tmp_i9 == tmp_i4) break;
          tmp_c8 = local_801c[local_80c8];
          tmp_i5 = tmp_i9;
          tmp_i10 = tmp_i9;
        } while (tmp_c8 != ' ');
        goto LAB_0008cc2d;
      }
      local_805c[0] = local_805c[0] & 0xff00;
      local_80b8 = strtol((char *)local_80bc,(char **)0x0,10);
      tmp_u6 = 0;
      do {
        *(uint32_t *)((int)local_80bc + tmp_u6) = 0;
        *(uint32_t *)((int)local_8058 + tmp_u6) = 0;
        tmp_u6 = tmp_u6 + 8;
      } while (tmp_u6 < 0x40);
    }
    else {
      local_80c8 = tmp_i10;
      tmp_i10 = 0;
LAB_0008cc2d:
      *(char *)((int)local_805c + tmp_i10) = '\0';
      local_80b8 = strtol((char *)local_805c,(char **)0x0,10);
      tmp_u6 = 0;
      do {
        tmp_pc1 = (char *)((int)local_805c + tmp_u6);
        tmp_pc1[0] = '\0';
        tmp_pc1[1] = '\0';
        tmp_pc1[2] = '\0';
        tmp_pc1[3] = '\0';
        *(uint32_t *)((int)local_8058 + tmp_u6) = 0;
        tmp_u6 = tmp_u6 + 8;
      } while (tmp_u6 < 0x40);
      tmp_i10 = local_80c8;
      if (local_80c0 < local_80c8) goto LAB_0008cae0;
    }
    local_80bc = local_805c;
    local_80c8 = tmp_i10 + 1;
    if (local_80c8 < local_80c0) {
      tmp_c8 = local_801c[tmp_i10 + 1];
      if (tmp_c8 != ' ') {
        tmp_i10 = (local_80c0 + -1) - tmp_i10;
        tmp_i5 = 0;
        do {
          tmp_i4 = tmp_i5 + 1;
          local_80c8 = local_80c8 + 1;
          *(char *)((int)local_805c + tmp_i5) = tmp_c8;
          tmp_i5 = tmp_i10;
          if (tmp_i4 == tmp_i10) break;
          tmp_c8 = local_801c[local_80c8];
          tmp_i5 = tmp_i4;
        } while (tmp_c8 != ' ');
        goto LAB_0008ccbd;
      }
      local_805c[0] = local_805c[0] & 0xff00;
      tmp_l7 = strtol((char *)local_80bc,(char **)0x0,10);
      tmp_u6 = 0;
      do {
        *(uint32_t *)((int)local_80bc + tmp_u6) = 0;
        *(uint32_t *)((int)local_8058 + tmp_u6) = 0;
        tmp_u6 = tmp_u6 + 8;
      } while (tmp_u6 < 0x40);
    }
    else {
      tmp_i5 = 0;
LAB_0008ccbd:
      *(char *)((int)local_805c + tmp_i5) = '\0';
      tmp_l7 = strtol((char *)local_805c,(char **)0x0,10);
      tmp_u6 = 0;
      do {
        tmp_pc1 = (char *)((int)local_805c + tmp_u6);
        tmp_pc1[0] = '\0';
        tmp_pc1[1] = '\0';
        tmp_pc1[2] = '\0';
        tmp_pc1[3] = '\0';
        *(uint32_t *)((int)local_8058 + tmp_u6) = 0;
        tmp_u6 = tmp_u6 + 8;
      } while (tmp_u6 < 0x40);
      if (local_80c0 < local_80c8) goto LAB_0008cae0;
    }
    if (((local_80c8 + 1 < local_80c0) && (tmp_c8 = local_801c[local_80c8 + 1], tmp_c8 != '\n')) &&
       (tmp_c8 != '\r')) {
      tmp_i10 = 0;
      tmp_i5 = local_80c8 + 2;
      while( true ) {
        local_80c8 = tmp_i5;
        if (tmp_c8 != '\"') {
          *(char *)((int)local_805c + tmp_i10) = tmp_c8;
          tmp_i10 = tmp_i10 + 1;
        }
        if (local_80c0 <= local_80c8) break;
        tmp_c8 = local_801c[local_80c8];
        if ((tmp_c8 == '\n') || (tmp_i5 = local_80c8 + 1, tmp_c8 == '\r')) break;
      }
    }
    else {
      tmp_i10 = 0;
      local_80c8 = local_80c8 + 1;
    }
    *(char *)((int)local_805c + tmp_i10) = '\0';
    tmp_i10 = Q_stricmp(local_805c,&g_unk_00116fd7);
    if (tmp_i10 != 0) {
      strcpy((char *)local_809c,(char *)local_805c);
    }
    if (local_80c0 < local_80c8) goto LAB_0008cae0;
    if (((local_80b8 != 0 || local_80c4 != 0) || tmp_l7 != 0) && ((char)local_809c[0] != '\0')) {
      tmp_i10 = GHIDRA_FIELD(cgs, 33785368, 4) * 0x50;
      *(uint32_t *)(cgs + tmp_i10 + 0x2024618) = GHIDRA_FIELD(cgs, 33785368, 4);
      strcpy(cgs + tmp_i10 + 0x2024628,(char *)local_809c);
      *(float *)(cgs + tmp_i10 + 0x202461c) = (float)local_80c4;
      *(float *)(cgs + tmp_i10 + 0x2024620) = (float)local_80b8;
      *(float *)(cgs + tmp_i10 + 0x2024624) = (float)tmp_l7;
      GHIDRA_FIELD(cgs, 33785368, 4) = GHIDRA_FIELD(cgs, 33785368, 4) + 1;
      if (GHIDRA_FIELD(cgs, 33785368, 4) == 0x400) break;
    }
    if (local_80c0 <= local_80c8) {
      GHIDRA_FIELD(cgs, 33785372, 4) = 1;
      return;
    }
  } while( true );
  CG_Printf("^9Too many locations specifed.\n");
  goto LAB_0008cae0;
}

void CG_FreeLocalEntity(int *param_1)
{
  int tmp_i1;
  
  if (*param_1 == 0) {
    CG_Error("CG_FreeLocalEntity: not active");
  }
  localEntCount = localEntCount + -1;
  *(int *)(*param_1 + 4) = param_1[1];
  *(int *)param_1[1] = *param_1;
  tmp_i1 = (int)cg_freeLocalEntities;
  cg_freeLocalEntities = param_1;
  param_1[1] = tmp_i1;
  return;
}

uint8_t * CG_FindLocalEntity(int param_1,int param_2)
{
  int *tmp_pi1;
  int tmp_i2;
  
  if (0 < localEntCount) {
    tmp_pi1 = (int *)(cg_localEntities + 0x1b4);
    tmp_i2 = 0;
    do {
      if ((*tmp_pi1 == param_1) && (tmp_pi1[1] == param_2)) {
        return cg_localEntities + tmp_i2 * 0x1bc;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pi1 = tmp_pi1 + 0x6f;
    } while (tmp_i2 != localEntCount);
  }
  return (uint8_t *)0x0;
}

int * CG_AllocLocalEntity(void)
{
  int *tmp_pi1;
  uint32_t *tmp_pu2;
  int *tmp_pi3;
  uint tmp_u4;
  uint tmp_u5;
  int *tmp_pi6;
  bool tmp_b7;
  
  tmp_pi6 = cg_activeLocalEntities;
  if (cg_freeLocalEntities == (int *)0x0) {
    if (*cg_activeLocalEntities == 0) {
      CG_Error("CG_FreeLocalEntity: not active");
    }
    localEntCount = localEntCount + -1;
    *(int *)(*tmp_pi6 + 4) = tmp_pi6[1];
    *(int *)tmp_pi6[1] = *tmp_pi6;
    tmp_pi6[1] = (int)cg_freeLocalEntities;
    tmp_pi1 = cg_freeLocalEntities;
  }
  else {
    tmp_pi1 = (int *)cg_freeLocalEntities[1];
    tmp_pi6 = cg_freeLocalEntities;
  }
  localEntCount = localEntCount + 1;
  tmp_b7 = ((uint)tmp_pi6 & 1) != 0;
  tmp_u4 = 0x1bc;
  tmp_pi3 = tmp_pi6;
  cg_freeLocalEntities = tmp_pi1;
  if (tmp_b7) {
    tmp_u4 = 0x1bb;
    *(uint8_t *)tmp_pi6 = 0;
    tmp_pi3 = (int *)((int)tmp_pi6 + 1);
  }
  if (((uint)tmp_pi3 & 2) != 0) {
    *(uint16_t *)tmp_pi3 = 0;
    tmp_u4 = tmp_u4 - 2;
    tmp_pi3 = (int *)((int)tmp_pi3 + 2);
  }
  tmp_u5 = 0;
  do {
    *(uint32_t *)((int)tmp_pi3 + tmp_u5) = 0;
    *(uint32_t *)((int)tmp_pi3 + tmp_u5 + 4) = 0;
    tmp_u5 = tmp_u5 + 8;
  } while (tmp_u5 < (tmp_u4 & 0xfffffff8));
  tmp_pu2 = (uint32_t *)((int)tmp_pi3 + tmp_u5);
  if ((tmp_u4 & 4) != 0) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + 1;
  }
  if ((tmp_u4 & 2) != 0) {
    *(uint16_t *)tmp_pu2 = 0;
    tmp_pu2 = (uint32_t *)((int)tmp_pu2 + 2);
  }
  if (tmp_b7) {
    *(uint8_t *)tmp_pu2 = 0;
  }
  tmp_pi6[1] = (int)g_unk_00f69564;
  *tmp_pi6 = (int)&cg_activeLocalEntities;
  *g_unk_00f69564 = (int)tmp_pi6;
  g_unk_00f69564 = tmp_pi6;
  return tmp_pi6;
}

void CG_BloodTrail(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t tmp_u4;
  long double tmp_l5;
  uint8_t local_28 [24];
  
  if (((GHIDRA_FIELD(cg_gibs, 12, 4) != 0) &&
      (tmp_l5 = (long double)VectorLength(param_1 + 0x38), (long double)1.1920929e-07 <= tmp_l5)) &&
     (tmp_i1 = (int)ROUND((long double)3000.0 / tmp_l5), 0 < tmp_i1)) {
    tmp_i2 = (((g_unk_010906e0 - g_unk_010906dc) + tmp_i1) / tmp_i1) * tmp_i1;
    tmp_i3 = (g_unk_010906e0 / tmp_i1) * tmp_i1;
    if (tmp_i2 - tmp_i3 == 0 || tmp_i2 < tmp_i3) {
      do {
        BG_EvaluateTrajectory(param_1 + 0x20,tmp_i2,local_28,0,0xffffffff);
        tmp_u4 = CG_AddTrailJunc(*(uint32_t *)(param_1 + 0x188),param_1,GHIDRA_FIELD(cgs, 68100, 4),tmp_i2,0,
                                local_28,0xb4,0x3f800000,0,0x41400000,0x41400000,4,col_12026,
                                col_12026,0,0);
        *(uint32_t *)(param_1 + 0x188) = tmp_u4;
        tmp_i2 = tmp_i2 + tmp_i1;
      } while (tmp_i2 <= tmp_i3);
    }
  }
  return;
}

void CG_FragmentBounceMark(int param_1,int param_2)
{
  uint tmp_u1;
  int tmp_i2;
  int tmp_i3;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  if (*(int *)(param_1 + 0x90) == 1) {
    if ((lastBloodMark_12037 <= g_unk_010906e0) && (lastBloodMark_12037 < g_unk_010906e0 + -99)) {
      tmp_u1 = rand();
      local_3c = 0;
      local_38 = 0;
      local_34 = 0xbf800000;
      local_2c = 0x3f800000;
      local_28 = 0x3f800000;
      local_30 = (float)((tmp_u1 & 0x1f) + 0x10);
      local_24 = 0x3f800000;
      local_20 = 0x3f800000;
      tmp_i3 = GHIDRA_FIELD(cg_bloodTime, 12, 4) * 1000;
      tmp_i2 = rand();
      trap_R_ProjectDecal(*(uint32_t *)(cgs + (tmp_i2 % 5) * 4 + 0x10ca4),1,param_2 + 0xc,&local_3c
                          ,&local_2c,tmp_i3,tmp_i3 >> 4);
      lastBloodMark_12037 = g_unk_010906e0;
    }
  }
  *(uint32_t *)(param_1 + 0x90) = 0;
  return;
}

void CG_FragmentBounceSound(int param_1,int param_2)
{
  uint tmp_u1;
  int tmp_i2;
  uint32_t tmp_u3;
  
  tmp_u1 = *(uint *)(param_1 + 0x94);
  if (tmp_u1 == 4) {
    tmp_i2 = rand();
    tmp_i2 = tmp_i2 % 3;
    tmp_u1 = *(uint *)(param_2 + 0x2c);
    if ((tmp_u1 & 0x1000) == 0) {
      if ((tmp_u1 & 0x40000) == 0) {
        if ((tmp_u1 & 0x2580000) == 0) {
          tmp_u3 = *(uint32_t *)(cgs + tmp_i2 * 8 + 0x10e54);
        }
        else {
          tmp_u3 = *(uint32_t *)(cgs + tmp_i2 * 8 + 0x10e3c);
        }
      }
      else {
        tmp_u3 = *(uint32_t *)(cgs + tmp_i2 * 8 + 0x10e6c);
      }
    }
    else {
      tmp_u3 = *(uint32_t *)(cgs + tmp_i2 * 8 + 0x10e24);
    }
LAB_0008d760:
    trap_S_StartSoundVControl(param_2 + 0xc,0xffffffff,0,tmp_u3,0x60);
  }
  else {
    if (tmp_u1 < 5) {
      if (tmp_u1 != 2) {
        return;
      }
      tmp_i2 = rand();
      tmp_u3 = *(uint32_t *)(cgs + (tmp_i2 % 3) * 4 + 0x10e84);
    }
    else {
      tmp_u3 = GHIDRA_FIELD(cgs, 69536, 4);
      if (tmp_u1 != 6) {
        if (tmp_u1 != 7) {
          return;
        }
        tmp_i2 = rand();
        tmp_i2 = tmp_i2 % 3;
        tmp_u1 = *(uint *)(param_2 + 0x2c);
        if ((tmp_u1 & 0x1000) == 0) {
          if ((tmp_u1 & 0x40000) == 0) {
            if ((tmp_u1 & 0x2580000) == 0) {
              tmp_u3 = *(uint32_t *)(cgs + tmp_i2 * 8 + 0x10e58);
            }
            else {
              tmp_u3 = *(uint32_t *)(cgs + tmp_i2 * 8 + 0x10e40);
            }
          }
          else {
            tmp_u3 = *(uint32_t *)(cgs + tmp_i2 * 8 + 0x10e70);
          }
        }
        else {
          tmp_u3 = *(uint32_t *)(cgs + tmp_i2 * 8 + 0x10e28);
        }
        goto LAB_0008d760;
      }
    }
    trap_S_StartSound(param_2 + 0xc,0xffffffff,0,tmp_u3);
  }
  *(uint32_t *)(param_1 + 0x94) = 0;
  return;
}

void CG_ReflectVelocity(int param_1,int *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  long double tmp_l5;
  double tmp_d6;
  float local_40;
  float local_3c;
  float local_38;
  uint8_t local_34 [12];
  uint8_t local_28 [20];
  uint32_t uStack_14;
  
  uStack_14 = 0x8d810;
  BG_EvaluateTrajectoryDelta
            (param_1 + 0x20,
             (int)ROUND((float)g_unk_010906dc * (float)param_2[2] +
                        (float)(g_unk_010906e0 - g_unk_010906dc)),&local_40,0,0xffffffff);
  tmp_f3 = (local_38 * (float)param_2[8] +
          local_3c * (float)param_2[7] + local_40 * (float)param_2[6]) * -2.0;
  local_40 = (float)param_2[6] * tmp_f3 + local_40;
  *(float *)(param_1 + 0x38) = local_40;
  local_3c = (float)param_2[7] * tmp_f3 + local_3c;
  *(float *)(param_1 + 0x3c) = local_3c;
  tmp_f1 = (float)param_2[8];
  tmp_f2 = *(float *)(param_1 + 0x68);
  *(float *)(param_1 + 0x38) = local_40 * tmp_f2;
  *(float *)(param_1 + 0x3c) = local_3c * tmp_f2;
  tmp_f1 = (tmp_f3 * tmp_f1 + local_38) * tmp_f2;
  *(float *)(param_1 + 0x40) = tmp_f1;
  *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * tmp_f2;
  *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * tmp_f2;
  *(float *)(param_1 + 100) = tmp_f2 * *(float *)(param_1 + 100);
  *(int *)(param_1 + 0x2c) = param_2[3];
  *(int *)(param_1 + 0x30) = param_2[4];
  *(int *)(param_1 + 0x34) = param_2[5];
  *(int *)(param_1 + 0x24) = g_unk_010906e0;
  if ((*param_2 != 0) ||
     ((0.0 < (float)param_2[8] && ((tmp_f1 < 40.0 || (tmp_f1 < (float)-g_unk_010906dc * tmp_f1)))))) {
    tmp_i4 = 0;
    if (*(int *)(param_1 + 8) == 3) {
      tmp_i4 = (uint)(param_2[0xd] < 0x3fe) * 9;
    }
    *(int *)(param_1 + 0x20) = tmp_i4;
    if (((*(byte *)(param_1 + 0x194) & 2) != 0) && (*(int *)(param_1 + 0xa0) != 0)) {
      trap_R_ModelBounds(*(int *)(param_1 + 0xa0),local_28,local_34);
      tmp_l5 = (long double)RadiusFromBounds(local_28,local_34);
      vectoangles(param_2 + 6,param_1 + 0x50);
      tmp_f1 = *(float *)(param_1 + 0x50) + 90.0;
      *(float *)(param_1 + 0x50) = tmp_f1;
      if ((tmp_f1 <= 0.0) || (50.0 <= tmp_f1)) {
        tmp_f1 = 90.0;
      }
      else {
        tmp_d6 = tan((double)((tmp_f1 * 3.1415927) / 180.0));
        *(float *)(param_1 + 0x34) = *(float *)(param_1 + 0x34) - (float)tmp_d6 * (float)tmp_l5;
        tmp_f1 = tmp_f1 + 90.0;
      }
      *(float *)(param_1 + 0x50) = tmp_f1;
      AnglesToAxis(param_1 + 0x50,param_1 + 0xb4);
      return;
    }
  }
  return;
}

int CG_FeederCount(float param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  
  if (param_1 == 5.0) {
    if (0 < g_unk_01091e84) {
      tmp_pi2 = &g_unk_01091eb8;
      tmp_i1 = 0;
      do {
        if (*tmp_pi2 == 1) {
          tmp_i1 = tmp_i1 + 1;
        }
        tmp_pi2 = tmp_pi2 + 10;
      } while (tmp_pi2 != &g_unk_01091eb8 + g_unk_01091e84 * 10);
      return tmp_i1;
    }
  }
  else if (param_1 == 6.0) {
    if (0 < g_unk_01091e84) {
      tmp_pi2 = &g_unk_01091eb8;
      tmp_i1 = 0;
      do {
        if (*tmp_pi2 == 2) {
          tmp_i1 = tmp_i1 + 1;
        }
        tmp_pi2 = tmp_pi2 + 10;
      } while (tmp_pi2 != &g_unk_01091eb8 + g_unk_01091e84 * 10);
      return tmp_i1;
    }
  }
  else if (param_1 == 11.0) {
    return g_unk_01091e84;
  }
  return 0;
}

uint32_t CG_FeederItemImage(void)
{
  return 0;
}

void CG_FeederSelection(float param_1,int param_2)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i3 = 1;
  if (param_1 != 5.0) {
    tmp_i3 = 2;
  }
  if (0 < g_unk_01091e84) {
    tmp_pi2 = &g_unk_01091eb8;
    tmp_i4 = 0;
    tmp_i1 = 0;
    do {
      while (tmp_i3 == *tmp_pi2) {
        if (param_2 == tmp_i4) {
          g_unk_01091e88 = tmp_i1;
        }
        tmp_i1 = tmp_i1 + 1;
        tmp_i4 = tmp_i4 + 1;
        tmp_pi2 = tmp_pi2 + 10;
        if (tmp_i1 == g_unk_01091e84) {
          return;
        }
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_pi2 = tmp_pi2 + 10;
    } while (tmp_i1 != g_unk_01091e84);
  }
  return;
}

char * CG_FeederItemText(float param_1,int param_2,int param_3,uint32_t *param_4)
{
  int tmp_i1;
  char *tmp_pc2;
  int *tmp_pi3;
  int tmp_i4;
  int tmp_i5;
  
  *param_4 = 0xffffffff;
  tmp_i4 = 1;
  if ((param_1 != 5.0) && (tmp_i4 = 2, param_1 != 6.0)) {
    tmp_i4 = -1;
  }
  if (0 < g_unk_01091e84) {
    tmp_pi3 = &g_unk_01091eb8;
    tmp_i5 = 0;
    tmp_i1 = 0;
    do {
      while (tmp_i4 != *tmp_pi3) {
        tmp_i1 = tmp_i1 + 1;
        tmp_pi3 = tmp_pi3 + 10;
        if (tmp_i1 == g_unk_01091e84) goto LAB_0009052d;
      }
      if (param_2 == tmp_i5) {
        tmp_i4 = (&g_unk_01091ea4)[tmp_i1 * 10];
        goto LAB_00090549;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_i5 = tmp_i5 + 1;
      tmp_pi3 = tmp_pi3 + 10;
    } while (tmp_i1 != g_unk_01091e84);
  }
LAB_0009052d:
  tmp_i4 = (&g_unk_01091ea4)[param_2 * 10];
  tmp_i1 = param_2;
LAB_00090549:
  tmp_i4 = tmp_i4 * 0x1a4;
  if (*(int *)(cgs + tmp_i4 + 0x940c) != 0) {
    if (param_3 == 4) {
      tmp_pc2 = (char *)va("%i",*(uint32_t *)(cgs + tmp_i4 + 0x9498));
      return tmp_pc2;
    }
    if (param_3 < 5) {
      if (param_3 == 3) {
        return (char *)(tmp_i4 + 0x10f9274);
      }
    }
    else {
      if (param_3 == 5) {
        tmp_pc2 = (char *)va(&g_unk_001170f8,(&g_unk_01091eb0)[tmp_i1 * 10]);
        return tmp_pc2;
      }
      if (param_3 == 6) {
        if (*(int *)(&g_unk_01091eac + tmp_i1 * 0x28) != -1) {
          tmp_pc2 = (char *)va(&g_unk_001170f8,*(int *)(&g_unk_01091eac + tmp_i1 * 0x28));
          return tmp_pc2;
        }
        return "connecting";
      }
    }
  }
  return "";
}

long double CG_Cvar_Get(uint32_t param_1)
{
  char *tmp_pc1;
  uint tmp_u2;
  double tmp_d3;
  char local_8c [4];
  uint32_t auStack_88 [32];
  
  tmp_u2 = 0;
  do {
    tmp_pc1 = local_8c + tmp_u2;
    tmp_pc1[0] = '\0';
    tmp_pc1[1] = '\0';
    tmp_pc1[2] = '\0';
    tmp_pc1[3] = '\0';
    *(uint32_t *)((int)auStack_88 + tmp_u2) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x80);
  trap_Cvar_VariableStringBuffer(param_1,local_8c,0x80);
  tmp_d3 = strtod(local_8c,(char **)0x0);
  return (long double)(float)tmp_d3;
}

void CG_Text_PaintWithCursor
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7,uint32_t param_8,
               uint32_t param_9)

{
  CG_Text_Paint(param_1,param_2,param_3,param_4,param_5,0,param_8,param_9);
  return;
}

void CG_RunCinematicFrame(uint32_t param_1)
{
  trap_CIN_RunCinematic(param_1);
  return;
}

void CG_StopCinematic(uint32_t param_1)
{
  trap_CIN_StopCinematic(param_1);
  return;
}

void CG_RegisterSounds(void)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  uint8_t local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0x908ab;
  CG_LoadingString(":voice chats:");
  CG_LoadVoiceChats();
  CG_LoadingString(":init sounds:");
  CG_SoundInit();
  CG_LoadingString(":script speakers:");
  BG_ClearScriptSpeakerPool();
  tmp_u2 = va("sound/maps/%s.sps",0x10f69ac);
  BG_LoadSpeakerScript(tmp_u2);
  tmp_i4 = 0;
  while( true ) {
    tmp_i3 = BG_NumScriptSpeakers();
    if (tmp_i3 <= tmp_i4) break;
    tmp_i3 = BG_GetScriptSpeaker(tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_i3,0);
    *(uint32_t *)(tmp_i3 + 0x40) = tmp_u2;
    tmp_i4 = tmp_i4 + 1;
  }
  CG_LoadingString(":game sounds:");
  GHIDRA_FIELD(cgs, 69412, 4) = trap_S_RegisterSound("sound/weapons/misc/fire_dry.wav",0);
  GHIDRA_FIELD(cgs, 68948, 4) = trap_S_RegisterSound("sound/weapons/misc/fire_water.wav",0);
  GHIDRA_FIELD(cgs, 68952, 4) = trap_S_RegisterSound("sound/weapons/misc/change.wav",0);
  GHIDRA_FIELD(cgs, 69612, 4) = trap_S_RegisterSound("sound/weapons/dynamite/dynamite_bounce.wav",0);
  GHIDRA_FIELD(cgs, 69620, 4) = trap_S_RegisterSound("sound/weapons/satchel/satchel_bounce.wav",0);
  GHIDRA_FIELD(cgs, 69616, 4) = trap_S_RegisterSound("sound/weapons/landmine/mine_bounce.wav",0);
  GHIDRA_FIELD(cgs, 69476, 4) = trap_S_RegisterSound("sound/player/water_in.wav",0);
  GHIDRA_FIELD(cgs, 69480, 4) = trap_S_RegisterSound("sound/player/water_out.wav",0);
  GHIDRA_FIELD(cgs, 69484, 4) = trap_S_RegisterSound("sound/player/water_un.wav",0);
  GHIDRA_FIELD(cgs, 69488, 4) = trap_S_RegisterSound("sound/player/gasp.wav",0);
  GHIDRA_FIELD(cgs, 69492, 4) = trap_S_RegisterSound("sound/player/underwater.wav",0);
  tmp_i4 = 0;
  tmp_pu5 = cgs;
  do {
    tmp_i3 = tmp_i4 + 1;
    tmp_u2 = va("sound/weapons/grenade/bounce_hard%i.wav",tmp_i3);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0xa7].r_offset + (int)tmp_pu5) = tmp_u2;
    *(uint32_t *)((int)&__DT_REL[0xa6].r_offset + (int)tmp_pu5) = tmp_u2;
    *(uint32_t *)((int)&__DT_REL[0xa2].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/grenade/bounce_metal%i.wav",tmp_i3);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0xa8].r_offset + (int)tmp_pu5) = tmp_u2;
    *(uint32_t *)((int)&__DT_REL[0xa3].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/grenade/bounce_wood%i.wav",tmp_i3);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0xa4].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/grenade/bounce_soft%i.wav",tmp_i3);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0xaa].r_offset + (int)tmp_pu5) = tmp_u2;
    *(uint32_t *)((int)&__DT_REL[0xa9].r_offset + (int)tmp_pu5) = tmp_u2;
    *(uint32_t *)((int)&__DT_REL[0xa5].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_i4 = 1;
    tmp_pu5 = tmp_pu5 + 4;
  } while (tmp_i3 != 2);
  GHIDRA_FIELD(cgs, 69416, 4) = trap_S_RegisterSound("sound/player/footsteps/stone_jump.wav",0);
  GHIDRA_FIELD(cgs, 69436, 4) = trap_S_RegisterSound("sound/player/footsteps/water_jump.wav",0);
  GHIDRA_FIELD(cgs, 69420, 4) = trap_S_RegisterSound("sound/player/footsteps/metal_jump.wav",0);
  GHIDRA_FIELD(cgs, 69424, 4) = trap_S_RegisterSound("sound/player/footsteps/wood_jump.wav",0);
  GHIDRA_FIELD(cgs, 69428, 4) = trap_S_RegisterSound("sound/player/footsteps/grass_jump.wav",0);
  GHIDRA_FIELD(cgs, 69432, 4) = trap_S_RegisterSound("sound/player/footsteps/gravel_jump.wav",0);
  tmp_i4 = 0;
  GHIDRA_FIELD(cgs, 69440, 4) = trap_S_RegisterSound("sound/player/footsteps/roof_jump.wav",0);
  GHIDRA_FIELD(cgs, 69444, 4) = trap_S_RegisterSound("sound/player/footsteps/snow_jump.wav",0);
  GHIDRA_FIELD(cgs, 69448, 4) = trap_S_RegisterSound("sound/player/footsteps/carpet_jump.wav",0);
  tmp_pu5 = cgs;
  do {
    tmp_i4 = tmp_i4 + 1;
    Com_sprintf(local_5c,0x40,"sound/player/footsteps/stone%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(local_5c,0);
    *(uint32_t *)((int)&__DT_REL[0x59].r_offset + (int)tmp_pu5) = tmp_u2;
    Com_sprintf(local_5c,0x40,"sound/player/footsteps/water%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(local_5c,0);
    *(uint32_t *)((int)&__DT_REL[99].r_offset + (int)tmp_pu5) = tmp_u2;
    Com_sprintf(local_5c,0x40,"sound/player/footsteps/metal%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(local_5c,0);
    *(uint32_t *)((int)&__DT_REL[0x5b].r_offset + (int)tmp_pu5) = tmp_u2;
    Com_sprintf(local_5c,0x40,"sound/player/footsteps/wood%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(local_5c,0);
    *(uint32_t *)((int)&__DT_REL[0x5d].r_offset + (int)tmp_pu5) = tmp_u2;
    Com_sprintf(local_5c,0x40,"sound/player/footsteps/grass%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(local_5c,0);
    *(uint32_t *)((int)&__DT_REL[0x5f].r_offset + (int)tmp_pu5) = tmp_u2;
    Com_sprintf(local_5c,0x40,"sound/player/footsteps/gravel%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(local_5c,0);
    *(uint32_t *)((int)&__DT_REL[0x61].r_offset + (int)tmp_pu5) = tmp_u2;
    Com_sprintf(local_5c,0x40,"sound/player/footsteps/roof%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(local_5c,0);
    *(uint32_t *)((int)&__DT_REL[0x65].r_offset + (int)tmp_pu5) = tmp_u2;
    Com_sprintf(local_5c,0x40,"sound/player/footsteps/snow%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(local_5c,0);
    *(uint32_t *)((int)&__DT_REL[0x67].r_offset + (int)tmp_pu5) = tmp_u2;
    Com_sprintf(local_5c,0x40,"sound/player/footsteps/carpet%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(local_5c,0);
    *(uint32_t *)((int)&__DT_REL[0x69].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_pu5 = tmp_pu5 + 4;
  } while (tmp_i4 != 4);
  if (1 < bg_numItems) {
    tmp_pu5 = bg_itemlist;
    tmp_i3 = 1;
    tmp_i4 = bg_numItems;
    do {
      while (tmp_pu1 = (uint32_t *)(tmp_pu5 + 0x3c), *(char *)*tmp_pu1 != '\0') {
        tmp_pu5 = tmp_pu5 + 0x38;
        tmp_u2 = va("sound/%s.wav",(char *)*tmp_pu1);
        tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
        *(uint32_t *)(cgs + tmp_i3 * 4 + 0x203ac) = tmp_u2;
        tmp_i3 = tmp_i3 + 1;
        tmp_i4 = bg_numItems;
        if (bg_numItems <= tmp_i3) goto LAB_00090ed1;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_pu5 = tmp_pu5 + 0x38;
    } while (tmp_i3 < tmp_i4);
  }
LAB_00090ed1:
  GHIDRA_FIELD(cgs, 68912, 4) = trap_S_RegisterSound("sound/nit/fight.wav",0);
  GHIDRA_FIELD(cgs, 68908, 4) = trap_S_RegisterSound("sound/nit/prepare.wav",0);
  GHIDRA_FIELD(cgs, 69512, 4) = trap_S_RegisterSound("sound/nit/goat.wav",0);
  GHIDRA_FIELD(cgs, 69516, 4) = trap_S_RegisterSound("sound/weapons/flamethrower/flame_burn.wav",0);
  GHIDRA_FIELD(cgs, 69520, 4) = trap_S_RegisterSound("sound/weapons/flamethrower/flame_pilot.wav",0);
  GHIDRA_FIELD(cgs, 69524, 4) = trap_S_RegisterSound("sound/weapons/flamethrower/flame_up.wav",0);
  GHIDRA_FIELD(cgs, 69528, 4) = trap_S_RegisterSound("sound/weapons/flamethrower/flame_fire.wav",0);
  GHIDRA_FIELD(cgs, 69532, 4) = 0;
  GHIDRA_FIELD(cgs, 69496, 4) = trap_S_RegisterSound("sound/weapons/grenade/gren_timer4.wav",0);
  GHIDRA_FIELD(cgs, 69500, 4) = trap_S_RegisterSound("sound/weapons/grenade/gren_timer3.wav",0);
  GHIDRA_FIELD(cgs, 69504, 4) = trap_S_RegisterSound("sound/weapons/grenade/gren_timer2.wav",0);
  GHIDRA_FIELD(cgs, 69508, 4) = trap_S_RegisterSound("sound/weapons/grenade/gren_timer1.wav",0);
  GHIDRA_FIELD(cgs, 69536, 4) = trap_S_RegisterSound("sound/world/boardbreak.wav",0);
  GHIDRA_FIELD(cgs, 69100, 4) = trap_S_RegisterSound("sound/weapons/rocket/rocket_expl.wav",0);
  GHIDRA_FIELD(cgs, 69104, 4) = trap_S_RegisterSound("sound/weapons/rocket/rocket_expl_far.wav",0);
  GHIDRA_FIELD(cgs, 68916, 4) = trap_S_RegisterSound("sound/weapons/artillery/artillery_expl_1.wav",0);
  GHIDRA_FIELD(cgs, 68920, 4) = trap_S_RegisterSound("sound/weapons/artillery/artillery_expl_2.wav",0);
  GHIDRA_FIELD(cgs, 68924, 4) = trap_S_RegisterSound("sound/weapons/artillery/artillery_expl_3.wav",0);
  GHIDRA_FIELD(cgs, 68928, 4) = trap_S_RegisterSound("sound/weapons/artillery/artillery_expl_far.wav",0);
  GHIDRA_FIELD(cgs, 68932, 4) = trap_S_RegisterSound("sound/weapons/airstrike/airstrike_expl_1.wav",0);
  GHIDRA_FIELD(cgs, 68936, 4) = trap_S_RegisterSound("sound/weapons/airstrike/airstrike_expl_2.wav",0);
  GHIDRA_FIELD(cgs, 68940, 4) = trap_S_RegisterSound("sound/weapons/airstrike/airstrike_expl_3.wav",0);
  GHIDRA_FIELD(cgs, 68944, 4) = trap_S_RegisterSound("sound/weapons/airstrike/airstrike_expl_far.wav",0);
  GHIDRA_FIELD(cgs, 69384, 4) = trap_S_RegisterSound("sound/weapons/dynamite/dynamite_expl.wav",0);
  GHIDRA_FIELD(cgs, 69388, 4) = trap_S_RegisterSound("sound/weapons/dynamite/dynamite_expl_far.wav",0);
  GHIDRA_FIELD(cgs, 69112, 4) = trap_S_RegisterSound("sound/weapons/satchel/satchel_expl.wav",0);
  GHIDRA_FIELD(cgs, 69116, 4) = trap_S_RegisterSound("sound/weapons/satchel/satchel_expl_far.wav",0);
  GHIDRA_FIELD(cgs, 69120, 4) = trap_S_RegisterSound("sound/weapons/landmine/mine_expl.wav",0);
  GHIDRA_FIELD(cgs, 69124, 4) = trap_S_RegisterSound("sound/weapons/landmine/mine_expl_far.wav",0);
  GHIDRA_FIELD(cgs, 69128, 4) = trap_S_RegisterSound("sound/weapons/mortar/mortar_expl1.wav",0);
  GHIDRA_FIELD(cgs, 69132, 4) = trap_S_RegisterSound("sound/weapons/mortar/mortar_expl2.wav",0);
  GHIDRA_FIELD(cgs, 69136, 4) = trap_S_RegisterSound("sound/weapons/mortar/mortar_expl3.wav",0);
  GHIDRA_FIELD(cgs, 69140, 4) = trap_S_RegisterSound("sound/weapons/mortar/mortar_expl.wav",0);
  GHIDRA_FIELD(cgs, 69144, 4) = trap_S_RegisterSound("sound/weapons/mortar/mortar_expl_far.wav",0);
  tmp_i4 = 0;
  GHIDRA_FIELD(cgs, 69148, 4) = trap_S_RegisterSound("sound/weapons/grenade/gren_expl.wav",0);
  GHIDRA_FIELD(cgs, 69152, 4) = trap_S_RegisterSound("sound/weapons/grenade/gren_expl_far.wav",0);
  GHIDRA_FIELD(cgs, 69108, 4) = trap_S_RegisterSound("sound/weapons/grenade/gren_expl_water.wav",0);
  tmp_pu5 = cgs;
  do {
    tmp_i4 = tmp_i4 + 1;
    tmp_u2 = va("sound/weapons/misc/shell_metal%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x72].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/misc/sg_shell_metal%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x72].r_info + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/misc/shell_soft%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x75].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/misc/sg_shell_soft%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x75].r_info + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/misc/shell_stone%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x78].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/misc/sg_shell_stone%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x78].r_info + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/misc/shell_wood%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x7b].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/misc/sg_shell_wood%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x7b].r_info + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/world/debris%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)(cgs + tmp_i4 * 4 + 0x10e80) = tmp_u2;
    tmp_pu5 = tmp_pu5 + 8;
  } while (tmp_i4 != 3);
  tmp_i4 = 0;
  GHIDRA_FIELD(cgs, 69392, 4) = trap_S_RegisterSound("sound/weapons/knife/knife_hit1.wav",0);
  GHIDRA_FIELD(cgs, 69396, 4) = trap_S_RegisterSound("sound/weapons/knife/knife_hit2.wav",0);
  GHIDRA_FIELD(cgs, 69400, 4) = trap_S_RegisterSound("sound/weapons/knife/knife_hit3.wav",0);
  GHIDRA_FIELD(cgs, 69404, 4) = trap_S_RegisterSound("sound/weapons/knife/knife_hit4.wav",0);
  GHIDRA_FIELD(cgs, 69408, 4) = trap_S_RegisterSound("sound/weapons/knife/knife_hitwall1.wav",0);
  tmp_pu5 = cgs;
  do {
    tmp_i4 = tmp_i4 + 1;
    tmp_u2 = va("sound/weapons/impact/flesh%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x7f].r_info + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/impact/metal%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x82].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/impact/wood%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x84].r_info + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/impact/glass%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x87].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/impact/stone%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x89].r_info + (int)tmp_pu5) = tmp_u2;
    tmp_u2 = va("sound/weapons/impact/water%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)((int)&__DT_REL[0x8c].r_offset + (int)tmp_pu5) = tmp_u2;
    tmp_pu5 = tmp_pu5 + 4;
  } while (tmp_i4 != 5);
  GHIDRA_FIELD(cgs, 69624, 4) = trap_S_RegisterSound("sound/misc/body_pickup.wav",0);
  GHIDRA_FIELD(cgs, 69628, 4) = trap_S_RegisterSound("sound/menu/select.wav",0);
  GHIDRA_FIELD(cgs, 69632, 4) = trap_S_RegisterSound("sound/menu/filter.wav",0);
  GHIDRA_FIELD(cgs, 69636, 4) = trap_S_RegisterSound("sound/menu/cancel.wav",0);
  GHIDRA_FIELD(cgs, 69640, 4) = trap_S_RegisterSound("sound/misc/rank_up.wav",0);
  GHIDRA_FIELD(cgs, 69644, 4) = trap_S_RegisterSound("sound/misc/skill_up.wav",0);
  GHIDRA_FIELD(cgs, 69648, 4) = trap_S_RegisterSound("sound/chat/axis/medic.wav",0);
  GHIDRA_FIELD(cgs, 69652, 4) = trap_S_RegisterSound("sound/chat/allies/medic.wav",0);
  GHIDRA_FIELD(cgs, 131904, 4) = trap_S_RegisterSound("sound/weapons/knife/throw.wav",0);
  GHIDRA_FIELD(cgs, 69656, 4) = trap_S_RegisterSound("sound/nit/pm.wav",0);
  GHIDRA_FIELD(cgs, 131996, 4) = trap_S_RegisterSound("sound/hitsounds/head.wav",0);
  GHIDRA_FIELD(cgs, 132000, 4) = trap_S_RegisterSound("sound/nit/hs.wav",0);
  GHIDRA_FIELD(cgs, 132004, 4) = trap_S_RegisterSound("sound/hitsounds/body.wav",0);
  GHIDRA_FIELD(cgs, 132008, 4) = trap_S_RegisterSound("sound/hitsounds/team.wav",0);
  GHIDRA_FIELD(cgs, 33787780, 4) = trap_S_RegisterSound("sound/player/default/blank.wav",0);
  GHIDRA_FIELD(cgs, 33787784, 4) = trap_S_RegisterSound("sound/weapons/artillery/artillery_fly_1.wav",0);
  GHIDRA_FIELD(cgs, 33787788, 4) = trap_S_RegisterSound("sound/weapons/artillery/artillery_fly_2.wav",0);
  GHIDRA_FIELD(cgs, 33787792, 4) = trap_S_RegisterSound("sound/weapons/artillery/artillery_fly_3.wav",0);
  GHIDRA_FIELD(cgs, 33787796, 4) = trap_S_RegisterSound("sound/player/gib.wav",0);
  GHIDRA_FIELD(cgs, 33787800, 4) = trap_S_RegisterSound("sound/player/land_hurt.wav",0);
  GHIDRA_FIELD(cgs, 33787804, 4) = trap_S_RegisterSound("sound/world/build.wav",0);
  GHIDRA_FIELD(cgs, 33787808, 4) = trap_S_RegisterSound("sound/world/chaircreak.wav",0);
  GHIDRA_FIELD(cgs, 33787812, 4) = trap_S_RegisterSound("sound/misc/vo_revive.wav",0);
  GHIDRA_FIELD(cgs, 33787816, 4) = trap_S_RegisterSound("sound/player/gurp1.wav",0);
  GHIDRA_FIELD(cgs, 33787820, 4) = trap_S_RegisterSound("sound/player/gurp2.wav",0);
  GHIDRA_FIELD(cgs, 33787824, 4) = trap_S_RegisterSound("sound/weapons/landmine/mine_on.wav",0);
  GHIDRA_FIELD(cgs, 33787828, 4) = trap_S_RegisterSound("sound/misc/referee.wav",0);
  GHIDRA_FIELD(cgs, 33787832, 4) = trap_S_RegisterSound("sound/misc/vote.wav",0);
  GHIDRA_FIELD(cgs, 33787836, 4) = trap_S_RegisterSound("sound/nit/firstblood.wav",0);
  GHIDRA_FIELD(cgs, 33787840, 4) = trap_S_RegisterSound("sound/nit/firstheadshot.wav",0);
  GHIDRA_FIELD(cgs, 33787844, 4) = trap_S_RegisterSound("sound/weapons/airstrike/airstrike_plane.wav",0);
  GHIDRA_FIELD(cgs, 33787848, 4) = trap_S_RegisterSound("sound/movers/doors/default_door_locked.wav",0);
  GHIDRA_FIELD(cgs, 33787852, 4) = trap_S_RegisterSound("sound/movers/doors/door1_open.wav",0);
  GHIDRA_FIELD(cgs, 33787856, 4) = trap_S_RegisterSound("sound/movers/doors/door1_endo.wav",0);
  GHIDRA_FIELD(cgs, 33787860, 4) = trap_S_RegisterSound("sound/movers/doors/door1_close.wav",0);
  GHIDRA_FIELD(cgs, 33787864, 4) = trap_S_RegisterSound("sound/movers/doors/door1_endc.wav",0);
  GHIDRA_FIELD(cgs, 33787868, 4) = trap_S_RegisterSound("sound/movers/doors/door1_loopo.wav",0);
  GHIDRA_FIELD(cgs, 33787872, 4) = trap_S_RegisterSound("sound/movers/doors/door1_loopc.wav",0);
  GHIDRA_FIELD(cgs, 33787876, 4) = trap_S_RegisterSound("sound/movers/doors/door1_locked.wav",0);
  GHIDRA_FIELD(cgs, 33787880, 4) = trap_S_RegisterSound("sound/movers/doors/door1_openq.wav",0);
  GHIDRA_FIELD(cgs, 33787884, 4) = trap_S_RegisterSound("sound/movers/doors/door1_endoq.wav",0);
  GHIDRA_FIELD(cgs, 33787888, 4) = trap_S_RegisterSound("sound/movers/doors/door1_closeq.wav",0);
  GHIDRA_FIELD(cgs, 33787892, 4) = trap_S_RegisterSound("sound/movers/doors/door1_endcq.wav",0);
  GHIDRA_FIELD(cgs, 33787896, 4) = trap_S_RegisterSound("sound/movers/doors/door2_open.wav",0);
  GHIDRA_FIELD(cgs, 33787900, 4) = trap_S_RegisterSound("sound/movers/doors/door2_endo.wav",0);
  GHIDRA_FIELD(cgs, 33787904, 4) = trap_S_RegisterSound("sound/movers/doors/door2_close.wav",0);
  GHIDRA_FIELD(cgs, 33787908, 4) = trap_S_RegisterSound("sound/movers/doors/door2_endc.wav",0);
  GHIDRA_FIELD(cgs, 33787912, 4) = trap_S_RegisterSound("sound/movers/doors/door2_loopo.wav",0);
  GHIDRA_FIELD(cgs, 33787916, 4) = trap_S_RegisterSound("sound/movers/doors/door2_loopc.wav",0);
  GHIDRA_FIELD(cgs, 33787920, 4) = trap_S_RegisterSound("sound/movers/doors/door2_locked.wav",0);
  GHIDRA_FIELD(cgs, 33787924, 4) = trap_S_RegisterSound("sound/movers/doors/door2_openq.wav",0);
  GHIDRA_FIELD(cgs, 33787928, 4) = trap_S_RegisterSound("sound/movers/doors/door2_endoq.wav",0);
  GHIDRA_FIELD(cgs, 33787932, 4) = trap_S_RegisterSound("sound/movers/doors/door2_closeq.wav",0);
  GHIDRA_FIELD(cgs, 33787936, 4) = trap_S_RegisterSound("sound/movers/doors/door2_endcq.wav",0);
  GHIDRA_FIELD(cgs, 33787940, 4) = trap_S_RegisterSound("sound/movers/doors/door3_open.wav",0);
  GHIDRA_FIELD(cgs, 33787944, 4) = trap_S_RegisterSound("sound/movers/doors/door3_endo.wav",0);
  GHIDRA_FIELD(cgs, 33787948, 4) = trap_S_RegisterSound("sound/movers/doors/door3_close.wav",0);
  GHIDRA_FIELD(cgs, 33787952, 4) = trap_S_RegisterSound("sound/movers/doors/door3_endc.wav",0);
  GHIDRA_FIELD(cgs, 33787956, 4) = trap_S_RegisterSound("sound/movers/doors/door3_loopo.wav",0);
  GHIDRA_FIELD(cgs, 33787960, 4) = trap_S_RegisterSound("sound/movers/doors/door3_loopc.wav",0);
  GHIDRA_FIELD(cgs, 33787964, 4) = trap_S_RegisterSound("sound/movers/doors/door3_locked.wav",0);
  GHIDRA_FIELD(cgs, 33787968, 4) = trap_S_RegisterSound("sound/movers/doors/door3_openq.wav",0);
  GHIDRA_FIELD(cgs, 33787972, 4) = trap_S_RegisterSound("sound/movers/doors/door3_endoq.wav",0);
  GHIDRA_FIELD(cgs, 33787976, 4) = trap_S_RegisterSound("sound/movers/doors/door3_closeq.wav",0);
  GHIDRA_FIELD(cgs, 33787980, 4) = trap_S_RegisterSound("sound/movers/doors/door3_endcq.wav",0);
  GHIDRA_FIELD(cgs, 33787984, 4) = trap_S_RegisterSound("sound/movers/doors/door4_open.wav",0);
  GHIDRA_FIELD(cgs, 33787988, 4) = trap_S_RegisterSound("sound/movers/doors/door4_endo.wav",0);
  GHIDRA_FIELD(cgs, 33787992, 4) = trap_S_RegisterSound("sound/movers/doors/door4_close.wav",0);
  GHIDRA_FIELD(cgs, 33787996, 4) = trap_S_RegisterSound("sound/movers/doors/door4_endc.wav",0);
  GHIDRA_FIELD(cgs, 33788000, 4) = trap_S_RegisterSound("sound/movers/doors/door4_loopo.wav",0);
  GHIDRA_FIELD(cgs, 33788004, 4) = trap_S_RegisterSound("sound/movers/doors/door4_loopc.wav",0);
  GHIDRA_FIELD(cgs, 33788008, 4) = trap_S_RegisterSound("sound/movers/doors/door4_locked.wav",0);
  GHIDRA_FIELD(cgs, 33788012, 4) = trap_S_RegisterSound("sound/movers/doors/door4_openq.wav",0);
  GHIDRA_FIELD(cgs, 33788016, 4) = trap_S_RegisterSound("sound/movers/doors/door4_endoq.wav",0);
  GHIDRA_FIELD(cgs, 33788020, 4) = trap_S_RegisterSound("sound/movers/doors/door4_closeq.wav",0);
  GHIDRA_FIELD(cgs, 33788024, 4) = trap_S_RegisterSound("sound/movers/doors/door4_endcq.wav",0);
  GHIDRA_FIELD(cgs, 33788028, 4) = trap_S_RegisterSound("sound/movers/doors/door5_open.wav",0);
  GHIDRA_FIELD(cgs, 33788032, 4) = trap_S_RegisterSound("sound/movers/doors/door5_endo.wav",0);
  GHIDRA_FIELD(cgs, 33788036, 4) = trap_S_RegisterSound("sound/movers/doors/door5_close.wav",0);
  GHIDRA_FIELD(cgs, 33788040, 4) = trap_S_RegisterSound("sound/movers/doors/door5_endc.wav",0);
  GHIDRA_FIELD(cgs, 33788044, 4) = trap_S_RegisterSound("sound/movers/doors/door5_loopo.wav",0);
  GHIDRA_FIELD(cgs, 33788048, 4) = trap_S_RegisterSound("sound/movers/doors/door5_loopc.wav",0);
  GHIDRA_FIELD(cgs, 33788052, 4) = trap_S_RegisterSound("sound/movers/doors/door5_locked.wav",0);
  GHIDRA_FIELD(cgs, 33788056, 4) = trap_S_RegisterSound("sound/movers/doors/door5_openq.wav",0);
  GHIDRA_FIELD(cgs, 33788060, 4) = trap_S_RegisterSound("sound/movers/doors/door5_endoq.wav",0);
  GHIDRA_FIELD(cgs, 33788064, 4) = trap_S_RegisterSound("sound/movers/doors/door5_closeq.wav",0);
  GHIDRA_FIELD(cgs, 33788068, 4) = trap_S_RegisterSound("sound/movers/doors/door5_endcq.wav",0);
  GHIDRA_FIELD(cgs, 33788072, 4) = trap_S_RegisterSound("sound/movers/doors/door6_open.wav",0);
  GHIDRA_FIELD(cgs, 33788076, 4) = trap_S_RegisterSound("sound/movers/doors/door6_endo.wav",0);
  GHIDRA_FIELD(cgs, 33788080, 4) = trap_S_RegisterSound("sound/movers/doors/door6_close.wav",0);
  GHIDRA_FIELD(cgs, 33788084, 4) = trap_S_RegisterSound("sound/movers/doors/door6_endc.wav",0);
  GHIDRA_FIELD(cgs, 33788088, 4) = trap_S_RegisterSound("sound/movers/doors/door6_loopo.wav",0);
  GHIDRA_FIELD(cgs, 33788092, 4) = trap_S_RegisterSound("sound/movers/doors/door6_loopc.wav",0);
  GHIDRA_FIELD(cgs, 33788096, 4) = trap_S_RegisterSound("sound/movers/doors/door6_locked.wav",0);
  GHIDRA_FIELD(cgs, 33788100, 4) = trap_S_RegisterSound("sound/movers/doors/door6_openq.wav",0);
  GHIDRA_FIELD(cgs, 33788104, 4) = trap_S_RegisterSound("sound/movers/doors/door6_endoq.wav",0);
  GHIDRA_FIELD(cgs, 33788108, 4) = trap_S_RegisterSound("sound/movers/doors/door6_closeq.wav",0);
  GHIDRA_FIELD(cgs, 33788112, 4) = trap_S_RegisterSound("sound/movers/doors/door6_endcq.wav",0);
  GHIDRA_FIELD(cgs, 132304, 4) = trap_S_RegisterSound("sound/vo/general/axis/hq_minesspot.wav",0);
  tmp_i4 = 0;
  GHIDRA_FIELD(cgs, 132308, 4) = trap_S_RegisterSound("sound/vo/general/allies/hq_minesspot.wav",0);
  do {
    tmp_i4 = tmp_i4 + 1;
    tmp_u2 = va("sound/nit/mk%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)(cgs + tmp_i4 * 4 + 0x204d4) = tmp_u2;
  } while (tmp_i4 != 5);
  tmp_i4 = 0;
  do {
    tmp_i4 = tmp_i4 + 1;
    tmp_u2 = va("sound/nit/mr%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)(cgs + tmp_i4 * 4 + 0x20514) = tmp_u2;
  } while (tmp_i4 != 4);
  tmp_i4 = 0;
  do {
    tmp_i4 = tmp_i4 + 1;
    tmp_u2 = va("sound/nit/ks%i.wav",tmp_i4);
    tmp_u2 = trap_S_RegisterSound(tmp_u2,0);
    *(uint32_t *)(cgs + tmp_i4 * 4 + 0x204e8) = tmp_u2;
  } while (tmp_i4 != 6);
  GHIDRA_FIELD(cgs, 132356, 4) = trap_S_RegisterSound("sound/player/hurt_barbwire.wav",0);
  GHIDRA_FIELD(cgs, 132360, 4) = trap_S_RegisterSound("sound/misc/w_pkup.wav",0);
  GHIDRA_FIELD(cgs, 132364, 4) = trap_S_RegisterSound("sound/nit/tk.wav",0);
  GHIDRA_FIELD(cgs, 132368, 4) = trap_S_RegisterSound("sound/music/axis_win.wav",0);
  GHIDRA_FIELD(cgs, 132372, 4) = trap_S_RegisterSound("sound/music/allies_win.wav",0);
  CG_LoadingString(":caching sounds:");
  if (GHIDRA_FIELD(cg_buildScript, 12, 4) != 0) {
    CG_PrecacheFXSounds();
  }
  return;
}

void CG_setClientFlags_part_0(void)
{
  uint tmp_u1;
  uint32_t tmp_u2;
  uint tmp_u3;
  uint tmp_u4;
  
  g_unk_010b1668 = (uint)(0 < (int)GHIDRA_FIELD(cg_autoReload, 12, 4));
  g_unk_010b16e8 = (uint)(0 < (int)GHIDRA_FIELD(cg_weapAltReloads, 12, 4));
  tmp_u1 = 0;
  if ((GHIDRA_FIELD(cg_autoAction, 12, 4) & 4) != 0) {
    tmp_u1 = 2;
  }
  tmp_u3 = 0x20;
  tmp_u4 = 0x40;
  if ((int)GHIDRA_FIELD(pmove_fixed, 12, 4) < 1) {
    tmp_u3 = 0;
  }
  if ((int)GHIDRA_FIELD(n_forceSinglePistol, 12, 4) < 1) {
    tmp_u4 = 0;
  }
  tmp_u2 = va("%d %d %d",
             ~-(uint)(0 >= (int)GHIDRA_FIELD(cg_weapAltReloads, 12, 4)) & 0x10 |
             (uint)(0 < (int)GHIDRA_FIELD(cg_predictItems, 12, 4)) << 3 |
             g_unk_010b1668 | tmp_u1 | (uint)(0 < (int)GHIDRA_FIELD(cg_autoactivate, 12, 4)) << 2 | tmp_u3 | tmp_u4,
             GHIDRA_FIELD(int_cl_timenudge, 12, 4),GHIDRA_FIELD(int_cl_maxpackets, 12, 4));
  trap_Cvar_Set("cg_uinfo",tmp_u2);
  return;
}

void CG_Error_constprop_3(void)
{
  char local_40c [1028];
  
  vsnprintf(local_40c,0x400,"CG_ConfigString: bad index: %i",&stack0x00000008);
  trap_Error(local_40c);
  return;
}

void CG_ConfigStringCopy(uint param_1,char *param_2,uint32_t param_3)
{
  if (0x3ff < param_1) {
    CG_Error_constprop_3("CG_ConfigString: bad index: %i",param_1);
  }
  Q_strncpyz(param_2,*(int *)(cgs + param_1 * 4) + 0x10f0e60,param_3);
  strlen(param_2);
  return;
}

void CG_RegisterCvars(void)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint8_t **tmp_ppu3;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x92479;
  if (0 < cvarTableSize) {
    tmp_ppu3 = &cvarTable;
    tmp_i2 = 0;
    do {
      while( true ) {
        trap_Cvar_Register(*tmp_ppu3,tmp_ppu3[1],tmp_ppu3[2],tmp_ppu3[3]);
        tmp_pu1 = *tmp_ppu3;
        if (tmp_pu1 != (uint8_t *)0x0) break;
LAB_000924a6:
        tmp_i2 = tmp_i2 + 1;
        tmp_ppu3 = tmp_ppu3 + 5;
        if (cvarTableSize <= tmp_i2) goto LAB_00092500;
      }
      if (tmp_pu1 != cg_errorDecay) {
        tmp_ppu3[4] = *(uint8_t **)(tmp_pu1 + 4);
        goto LAB_000924a6;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_ppu3[4] = (uint8_t *)(uint)(GHIDRA_FIELD(cg_errorDecay, 4, 4) == 0);
      tmp_ppu3 = tmp_ppu3 + 5;
    } while (tmp_i2 < cvarTableSize);
  }
LAB_00092500:
  trap_Cvar_VariableStringBuffer("sv_running",local_41c,0x400);
  GHIDRA_FIELD(cgs, 27384, 4) = strtol(local_41c,(char **)0x0,10);
  if (g_unk_01047aec == 0) {
    CG_setClientFlags_part_0();
  }
  BG_setCrosshair(0x101f2f0,&g_unk_010b14c8,GHIDRA_FIELD(cg_crosshairAlpha, 8, 4),"cg_crosshairColor");
  BG_setCrosshair(0x10ef7b0,&g_unk_010b14d8,GHIDRA_FIELD(cg_crosshairAlphaAlt, 8, 4),"cg_crosshairColorAlt");
  cvarsLoaded = 1;
  return;
}

void CG_UpdateCvars(void)
{
  bool tmp_b1;
  uint8_t *tmp_pu2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  int tmp_i5;
  uint8_t **tmp_ppu6;
  int tmp_i7;
  
  if ((cvarsLoaded != 0) && (0 < cvarTableSize)) {
    tmp_b1 = false;
    tmp_ppu6 = &cvarTable;
    tmp_i7 = 0;
    tmp_i5 = cvarTableSize;
LAB_00092610:
    do {
      while (*tmp_ppu6 == (uint8_t *)0x0) {
LAB_00092726:
        tmp_i7 = tmp_i7 + 1;
        tmp_ppu6 = tmp_ppu6 + 5;
        if (tmp_i5 <= tmp_i7) goto LAB_00092732;
      }
      trap_Cvar_Update(*tmp_ppu6);
      tmp_pu2 = *tmp_ppu6;
      tmp_i5 = cvarTableSize;
      if (tmp_ppu6[4] == *(uint8_t **)(tmp_pu2 + 4)) goto LAB_00092726;
      tmp_ppu6[4] = *(uint8_t **)(tmp_pu2 + 4);
      tmp_i5 = cvarTableSize;
      if ((((((((tmp_pu2 == cg_autoAction || tmp_pu2 == cg_autoReload) || tmp_pu2 == int_cl_timenudge)
              || tmp_pu2 == int_cl_maxpackets) || tmp_pu2 == cg_autoactivate) ||
            tmp_pu2 == cg_predictItems) || tmp_pu2 == cg_weapAltReloads) || tmp_pu2 == pmove_fixed) ||
         (tmp_pu2 == n_forceSinglePistol)) {
        tmp_i7 = tmp_i7 + 1;
        tmp_ppu6 = tmp_ppu6 + 5;
        tmp_b1 = true;
        if (cvarTableSize <= tmp_i7) break;
        goto LAB_00092610;
      }
      if ((tmp_pu2 != cg_crosshairColor) && (tmp_pu2 != cg_crosshairAlpha)) {
        if ((tmp_pu2 != cg_crosshairColorAlt) && (tmp_pu2 != cg_crosshairAlphaAlt)) {
          if (tmp_pu2 == cg_rconPassword) {
            if (cg_rconPassword[0x10] != '\0') {
              tmp_u4 = 0x1024d70;
              tmp_pc3 = "rconAuth %s";
LAB_0009286d:
              tmp_u4 = va(tmp_pc3,tmp_u4);
              trap_SendConsoleCommand(tmp_u4);
              tmp_i5 = cvarTableSize;
            }
          }
          else if (tmp_pu2 == cg_refereePassword) {
            if (cg_refereePassword[0x10] != '\0') {
              tmp_u4 = 0x3133c10;
              tmp_pc3 = "ref %s";
              goto LAB_0009286d;
            }
          }
          else if (tmp_pu2 == demo_infoWindow) {
            if (GHIDRA_FIELD(demo_infoWindow, 12, 4) == 0) {
              if (g_unk_010afbc8 == 2) {
LAB_000928c5:
                CG_ShowHelp_On(&g_unk_010afbc8);
                tmp_i5 = cvarTableSize;
              }
            }
            else if ((0 < (int)GHIDRA_FIELD(demo_infoWindow, 12, 4)) && (g_unk_010afbc8 != 2)) goto LAB_000928c5;
          }
          else if (tmp_pu2 == cg_errorDecay) {
            tmp_pu2 = &g_unk_0011e957;
            if (0.0 <= (float)GHIDRA_FIELD(cg_errorDecay, 8, 4)) {
              if ((float)GHIDRA_FIELD(cg_errorDecay, 8, 4) <= 500.0) goto LAB_00092726;
              tmp_pu2 = &g_unk_00118f3b;
            }
            trap_Cvar_Set("cg_errorDecay",tmp_pu2);
            tmp_i5 = cvarTableSize;
          }
          goto LAB_00092726;
        }
        tmp_i7 = tmp_i7 + 1;
        tmp_ppu6 = tmp_ppu6 + 5;
        BG_setCrosshair(0x10ef7b0,&g_unk_010b14d8,GHIDRA_FIELD(cg_crosshairAlphaAlt, 8, 4),"cg_crosshairColorAlt");
        tmp_i5 = cvarTableSize;
        if (cvarTableSize <= tmp_i7) break;
        goto LAB_00092610;
      }
      tmp_i7 = tmp_i7 + 1;
      tmp_ppu6 = tmp_ppu6 + 5;
      BG_setCrosshair(0x101f2f0,&g_unk_010b14c8,GHIDRA_FIELD(cg_crosshairAlpha, 8, 4),"cg_crosshairColor");
      tmp_i5 = cvarTableSize;
    } while (tmp_i7 < cvarTableSize);
LAB_00092732:
    if ((tmp_b1) && (g_unk_01047aec == 0)) {
      CG_setClientFlags_part_0();
      return;
    }
  }
  return;
}

void CG_setClientFlags(void)
{
  uint tmp_u1;
  uint32_t tmp_u2;
  uint tmp_u3;
  uint tmp_u4;
  
  if (g_unk_01047aec == 0) {
    g_unk_010b1668 = (uint)(0 < (int)GHIDRA_FIELD(cg_autoReload, 12, 4));
    g_unk_010b16e8 = (uint)(0 < (int)GHIDRA_FIELD(cg_weapAltReloads, 12, 4));
    tmp_u1 = 0;
    if ((GHIDRA_FIELD(cg_autoAction, 12, 4) & 4) != 0) {
      tmp_u1 = 2;
    }
    tmp_u3 = 0x20;
    tmp_u4 = 0x40;
    if ((int)GHIDRA_FIELD(pmove_fixed, 12, 4) < 1) {
      tmp_u3 = 0;
    }
    if ((int)GHIDRA_FIELD(n_forceSinglePistol, 12, 4) < 1) {
      tmp_u4 = 0;
    }
    tmp_u2 = va("%d %d %d",
               ~-(uint)(0 >= (int)GHIDRA_FIELD(cg_weapAltReloads, 12, 4)) & 0x10 |
               (uint)(0 < (int)GHIDRA_FIELD(cg_predictItems, 12, 4)) << 3 |
               g_unk_010b1668 | tmp_u1 | (uint)(0 < (int)GHIDRA_FIELD(cg_autoactivate, 12, 4)) << 2 | tmp_u3 | tmp_u4,
               GHIDRA_FIELD(int_cl_timenudge, 12, 4),GHIDRA_FIELD(int_cl_maxpackets, 12, 4));
    trap_Cvar_Set("cg_uinfo",tmp_u2);
  }
  return;
}

uint32_t CG_CrosshairPlayer(void)
{
  if (g_unk_010906e0 <= g_unk_0109355c + 1000) {
    return g_unk_01093558;
  }
  return 0xffffffff;
}

void CG_Printf(char *param_1)
{
  int tmp_i1;
  char local_80c [10];
  uint8_t local_802 [1014];
  uint8_t local_40c [1024];
  
  vsnprintf(local_80c,0x400,param_1,&stack0x00000008);
  tmp_i1 = Q_strncmp(local_80c,"[cgnotify]",10);
  if (tmp_i1 == 0) {
    if (GHIDRA_FIELD(cg_drawNotifyText, 12, 4) == 0) {
      Q_strncpyz(local_40c,local_802,0x3f5);
      trap_Print(local_40c);
      return;
    }
    CG_AddToNotify(local_802);
    Q_strncpyz(local_40c,local_802,0x3f5);
    Q_strncpyz(local_80c,"[skipnotify]",0xd);
    Q_strcat(local_80c,0x3f3,local_40c);
  }
  trap_Print(local_80c);
  return;
}

void CG_Error(char *param_1)
{
  char local_40c [1028];
  
  vsnprintf(local_40c,0x400,param_1,&stack0x00000008);
  trap_Error(local_40c);
  return;
}

void CG_nameCleanFilename(byte *param_1,byte *param_2,uint param_3)
{
  byte tmp_b1;
  uint tmp_u2;
  
  tmp_u2 = 0;
LAB_00092d2d:
  do {
    tmp_b1 = *param_1;
    while( true ) {
      if ((tmp_b1 == 0) || (param_3 <= tmp_u2)) {
        *param_2 = 0;
        return;
      }
      if ((tmp_b1 == 0x5e) || (tmp_b1 == 0x1b)) {
        if (param_1[1] != 0) {
          param_1 = param_1 + 2;
          tmp_u2 = tmp_u2 + 2;
          goto LAB_00092d2d;
        }
        param_1 = param_1 + 1;
        tmp_u2 = tmp_u2 + 1;
        tmp_b1 = 0;
      }
      param_1 = param_1 + 1;
      if (((((tmp_b1 != 0x5c && tmp_b1 != 0x3a) && (tmp_b1 & 0xf7) != 0x22) && (tmp_b1 & 0xbf) != 0x3c)
          && (1 < (byte)((tmp_b1 & 0xef) - 0x2e))) && (' ' < (char)tmp_b1)) break;
      tmp_b1 = *param_1;
      tmp_u2 = tmp_u2 + 1;
    }
    tmp_u2 = tmp_u2 + 1;
    *param_2 = tmp_b1;
    param_2 = param_2 + 1;
  } while( true );
}

void CG_generateFilename(void)
{
  uint32_t tmp_u1;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  int local_20;
  int local_1c;
  uint32_t uStack_c;
  
  tmp_u1 = CachedServerInfo;
  uStack_c = 0x92dd7;
  trap_RealTime(&local_30);
  tmp_u1 = Info_ValueForKey(tmp_u1,"mapname");
  va("%d-%02d-%02d-%02d%02d%02d-%s",local_1c + 0x76c,local_20 + 1,local_24,local_28,local_2c,
     local_30,tmp_u1);
  return;
}

int CG_findClientNum(char *param_1)
{
  char tmp_c1;
  size_t tmp_s2;
  long tmp_l3;
  int tmp_i4;
  char *tmp_pc5;
  int tmp_i6;
  int tmp_i7;
  char local_9c [64];
  char local_5c [76];
  
  tmp_s2 = strlen(param_1);
  tmp_pc5 = param_1;
  do {
    if ((tmp_pc5 == param_1 + tmp_s2) || (tmp_c1 = *tmp_pc5, tmp_c1 == '\0')) {
      tmp_l3 = strtol(param_1,(char **)0x0,10);
      if ((-1 < tmp_l3) &&
         ((tmp_l3 < (int)GHIDRA_FIELD(cgs, 27400, 4) && (*(int *)(cgs + tmp_l3 * 0x1a4 + 0x940c) != 0)))) {
        return tmp_l3;
      }
      break;
    }
    tmp_pc5 = tmp_pc5 + 1;
  } while ((byte)(tmp_c1 - 0x30U) < 10);
  BG_cleanName(param_1,local_9c,0x40,0);
  if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
    tmp_i6 = 0x10f9274;
    tmp_i7 = 0;
    tmp_i4 = GHIDRA_FIELD(cgs, 27400, 4);
    do {
      while (*(int *)(tmp_i6 + -8) != 0) {
        BG_cleanName(tmp_i6,local_5c,0x40,0);
        tmp_i4 = strcmp(local_5c,local_9c);
        if (tmp_i4 == 0) {
          return tmp_i7;
        }
        tmp_i7 = tmp_i7 + 1;
        tmp_i6 = tmp_i6 + 0x1a4;
        tmp_i4 = GHIDRA_FIELD(cgs, 27400, 4);
        if ((int)GHIDRA_FIELD(cgs, 27400, 4) <= tmp_i7) goto LAB_00092f6a;
      }
      tmp_i7 = tmp_i7 + 1;
      tmp_i6 = tmp_i6 + 0x1a4;
    } while (tmp_i7 < tmp_i4);
  }
LAB_00092f6a:
  CG_Printf("[cgnotify]User ^3%s ^7is not on the server.\n",param_1);
  return -1;
}

void CG_printConsoleString(uint32_t param_1)
{
  CG_Printf("[skipnotify]%s",param_1);
  return;
}

void CG_LoadObjectiveData(void)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  int tmp_i3;
  int tmp_i4;
  char *tmp_pc5;
  bool tmp_b6;
  byte tmp_b7;
  uint local_850;
  uint8_t local_84c [16];
  char local_83c [1032];
  uint8_t local_434 [16];
  uint8_t local_424 [1040];
  uint32_t uStack_14;
  
  tmp_b7 = 0;
  uStack_14 = 0x92ff9;
  if (GHIDRA_FIELD(cg_gameType, 12, 4) == 5) {
    tmp_u1 = Q_strlwr(0x10f69ac);
    tmp_pc2 = "maps/%s_lms.objdata";
  }
  else {
    tmp_u1 = Q_strlwr(0x10f69ac);
    tmp_pc2 = "maps/%s.objdata";
  }
  tmp_u1 = va(tmp_pc2,tmp_u1);
  tmp_i3 = trap_PC_LoadSource(tmp_u1);
  if (tmp_i3 != 0) {
LAB_00093060:
    tmp_i4 = trap_PC_ReadToken(tmp_i3,local_84c);
    tmp_b6 = tmp_i4 == 0;
    if (!tmp_b6) {
      tmp_i4 = 0x12;
      tmp_pc2 = local_83c;
      tmp_pc5 = "wm_mapdescription";
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b6 = *tmp_pc2 == *tmp_pc5;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b7 * -2 + 1;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
      } while (tmp_b6);
      if (!tmp_b6) {
        tmp_i4 = 0x17;
        tmp_pc2 = local_83c;
        tmp_pc5 = "wm_objective_axis_desc";
        do {
          if (tmp_i4 == 0) break;
          tmp_i4 = tmp_i4 + -1;
          tmp_b6 = *tmp_pc2 == *tmp_pc5;
          tmp_pc2 = tmp_pc2 + (uint)tmp_b7 * -2 + 1;
          tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
        } while (tmp_b6);
        if (tmp_b6) {
          tmp_i4 = PC_Int_Parse(tmp_i3,&local_850);
          if (tmp_i4 == 0) goto LAB_000932f4;
          tmp_i4 = trap_PC_ReadToken(tmp_i3,local_84c);
          if (tmp_i4 == 0) goto LAB_00093307;
          local_850 = local_850 - 1;
          if (local_850 < 8) {
            Q_strncpyz(local_850 * 0x100 + 0x10b4e40,local_83c,0x100);
            goto LAB_00093060;
          }
        }
        else {
          tmp_i4 = 0x19;
          tmp_b6 = false;
          tmp_pc2 = local_83c;
          tmp_pc5 = "wm_objective_allied_desc";
          do {
            if (tmp_i4 == 0) break;
            tmp_i4 = tmp_i4 + -1;
            tmp_b6 = *tmp_pc2 == *tmp_pc5;
            tmp_pc2 = tmp_pc2 + (uint)tmp_b7 * -2 + 1;
            tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
          } while (tmp_b6);
          if (!tmp_b6) goto LAB_00093060;
          tmp_i4 = PC_Int_Parse(tmp_i3,&local_850);
          if (tmp_i4 == 0) {
LAB_000932f4:
            CG_Printf("^1ERROR: bad objdata line : number parameter required\n");
            goto LAB_00093270;
          }
          tmp_i4 = trap_PC_ReadToken(tmp_i3,local_84c);
          if (tmp_i4 == 0) {
LAB_00093307:
            CG_Printf("^1ERROR: bad objdata line :  description parameter required\n");
            goto LAB_00093270;
          }
          local_850 = local_850 - 1;
          if (local_850 < 8) {
            Q_strncpyz(&g_unk_010b5640 + local_850 * 0x100,local_83c,0x100);
            goto LAB_00093060;
          }
        }
        CG_Printf("^1ERROR: bad objdata line : invalid objective number\n");
        goto LAB_00093270;
      }
      tmp_i4 = trap_PC_ReadToken(tmp_i3,local_84c);
      if (tmp_i4 == 0) {
        CG_Printf("^1ERROR: bad objdata line : team parameter required\n");
        goto LAB_00093270;
      }
      tmp_i4 = trap_PC_ReadToken(tmp_i3,local_434);
      if (tmp_i4 == 0) {
        CG_Printf("^1ERROR: bad objdata line : description parameter required\n");
        goto LAB_00093270;
      }
      tmp_i4 = 5;
      tmp_b6 = false;
      tmp_pc2 = local_83c;
      tmp_pc5 = "axis";
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b6 = *tmp_pc2 == *tmp_pc5;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b7 * -2 + 1;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
      } while (tmp_b6);
      if (tmp_b6) {
        Q_strncpyz(&g_unk_010b49c0,local_424,0x180);
      }
      else {
        tmp_i4 = 7;
        tmp_b6 = false;
        tmp_pc2 = local_83c;
        tmp_pc5 = "allied";
        do {
          if (tmp_i4 == 0) break;
          tmp_i4 = tmp_i4 + -1;
          tmp_b6 = *tmp_pc2 == *tmp_pc5;
          tmp_pc2 = tmp_pc2 + (uint)tmp_b7 * -2 + 1;
          tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
        } while (tmp_b6);
        if (tmp_b6) {
          Q_strncpyz(&g_unk_010b4b40,local_424,0x180);
        }
        else {
          tmp_i4 = 8;
          tmp_b6 = false;
          tmp_pc2 = local_83c;
          tmp_pc5 = "neutral";
          do {
            if (tmp_i4 == 0) break;
            tmp_i4 = tmp_i4 + -1;
            tmp_b6 = *tmp_pc2 == *tmp_pc5;
            tmp_pc2 = tmp_pc2 + (uint)tmp_b7 * -2 + 1;
            tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
          } while (tmp_b6);
          if (tmp_b6) {
            Q_strncpyz(&g_unk_010b4cc0,local_424,0x180);
          }
        }
      }
      goto LAB_00093060;
    }
LAB_00093270:
    trap_PC_FreeSource(tmp_i3);
  }
  return;
}

void CG_SetupDlightstyles(void)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  long tmp_l3;
  char *tmp_pc4;
  size_t tmp_s5;
  long tmp_l6;
  int tmp_i7;
  uint tmp_u8;
  char local_48;
  int *local_40;
  int local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0x9334e;
  local_40 = (int *)(cgs + 0xbc8);
  g_unk_01092cfc = 1;
  do {
    local_20[0] = *local_40 + 0x10f0e60;
    if (cgs[*local_40 + 0x1000] == '\0') {
      return;
    }
    tmp_pc2 = (char *)COM_Parse(local_20);
    tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    tmp_i7 = tmp_l3 * 0xaf8;
    tmp_pc4 = (char *)COM_Parse(local_20);
    tmp_s5 = strlen(tmp_pc4);
    tmp_pc2 = cg_entities + tmp_i7 + 0x7f0;
    Q_strncpyz(tmp_pc2,tmp_pc4,tmp_s5);
    tmp_pc4 = (char *)COM_Parse(local_20);
    tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
    *(long *)(cg_entities + tmp_i7 + 0x7e0) = tmp_l6;
    *(long *)(cg_entities + tmp_i7 + 0x7e4) = tmp_l6 + -1;
    if (tmp_l6 + -1 < 0) {
      tmp_s5 = strlen(tmp_pc2);
      *(size_t *)(cg_entities + tmp_i7 + 0x7e4) = tmp_s5;
    }
    tmp_pc4 = (char *)COM_Parse(local_20);
    tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
    tmp_i7 = tmp_l3 * 0xaf8;
    *(long *)(cg_entities + tmp_i7 + 0x830) = tmp_l6;
    tmp_pc4 = (char *)COM_Parse(local_20);
    tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
    tmp_u8 = 0;
    *(long *)(cg_entities + tmp_i7 + 0x834) = tmp_l6;
    tmp_s5 = strlen(tmp_pc2);
    if (tmp_s5 != 0) {
      do {
        local_48 = (char)tmp_l6;
        local_48 = local_48 + *(char *)(tmp_i7 + 0x3134630 + tmp_u8);
        if (local_48 < 'a') {
          *(uint8_t *)(tmp_i7 + 0x3134630 + tmp_u8) = 0x61;
        }
        else if (local_48 < '{') {
          *(char *)(tmp_i7 + 0x3134630 + tmp_u8) = local_48;
        }
        else {
          *(uint8_t *)(tmp_i7 + 0x3134630 + tmp_u8) = 0x7a;
        }
        tmp_u8 = tmp_u8 + 1;
        tmp_s5 = strlen(tmp_pc2);
      } while (tmp_u8 < tmp_s5);
    }
    tmp_u1 = g_unk_010906e0;
    local_40 = local_40 + 1;
    *(uint32_t *)(cg_entities + tmp_l3 * 0xaf8 + 0x7e8) = 0;
    *(uint32_t *)(cg_entities + tmp_l3 * 0xaf8 + 0x7ec) = tmp_u1;
  } while (local_40 != (int *)(cgs + 0xc04));
  return;
}

int CG_ConfigString(uint param_1)
{
  if (0x3ff < param_1) {
    CG_Error_constprop_3("CG_ConfigString: bad index: %i",param_1);
  }
  return *(int *)(cgs + param_1 * 4) + 0x10f0e60;
}

void CG_StartMusic(void)
{
  uint32_t tmp_u1;
  int local_90;
  char local_8c [64];
  uint8_t local_4c [64];
  
  local_90 = GHIDRA_FIELD(cgs, 8, 4) + 0x10f0e60;
  tmp_u1 = COM_Parse(&local_90);
  Q_strncpyz(local_8c,tmp_u1,0x40);
  tmp_u1 = COM_Parse(&local_90);
  Q_strncpyz(local_4c,tmp_u1,0x40);
  if (local_8c[0] != '\0') {
    trap_S_StartBackgroundTrack(local_8c,local_4c,0);
  }
  return;
}

void CG_QueueMusic(void)
{
  uint32_t tmp_u1;
  int local_50;
  uint8_t local_4c [68];
  
  local_50 = GHIDRA_FIELD(cgs, 100, 4) + 0x10f0e60;
  tmp_u1 = COM_Parse(&local_50);
  Q_strncpyz(local_4c,tmp_u1,0x40);
  trap_S_StartBackgroundTrack(local_4c,&g_unk_0011d841,0xfffffffe);
  return;
}

void CG_LoadHudMenu(void)
{
  cgDC = trap_R_RegisterShaderNoMip;
  g_unk_01026084 = trap_R_SetColor;
  g_unk_01026088 = CG_DrawPic;
  g_unk_0102608c = trap_R_DrawStretchPic;
  g_unk_01026090 = CG_Text_Paint;
  g_unk_01026094 = CG_Text_Paint_Ext;
  g_unk_01026098 = CG_Text_Width;
  g_unk_0102609c = CG_Text_Width_Ext;
  g_unk_010260a4 = CG_Text_Height;
  g_unk_010260a8 = CG_Text_Height_Ext;
  g_unk_010260b0 = CG_Text_SetActiveFont;
  g_unk_010260b4 = trap_R_RegisterModel;
  g_unk_010260b8 = trap_R_ModelBounds;
  g_unk_010260bc = CG_FillRect;
  g_unk_010260c0 = CG_DrawRect;
  g_unk_010260c4 = CG_DrawSides;
  g_unk_010260c8 = CG_DrawTopBottom;
  g_unk_010260cc = trap_R_ClearScene;
  g_unk_010260d0 = trap_R_AddRefEntityToScene;
  g_unk_010260d4 = trap_R_RenderScene;
  g_unk_010260d8 = trap_R_RegisterFont;
  g_unk_010260e0 = CG_GetValue;
  g_unk_010260ec = CG_GetTeamColor;
  g_unk_010260f8 = trap_Cvar_Set;
  g_unk_010260f0 = trap_Cvar_VariableStringBuffer;
  g_unk_010260f4 = CG_Cvar_Get;
  g_unk_010260fc = CG_Text_PaintWithCursor;
  g_unk_01026100 = trap_Key_SetOverstrikeMode;
  g_unk_01026104 = trap_Key_GetOverstrikeMode;
  g_unk_01026108 = trap_S_StartLocalSound;
  g_unk_01026110 = CG_FeederCount;
  g_unk_0102611c = CG_FeederItemImage;
  g_unk_01026114 = CG_FeederItemText;
  g_unk_01026120 = CG_FeederSelection;
  g_unk_01026144 = trap_Key_SetBinding;
  g_unk_01026138 = trap_Key_GetBindingBuf;
  g_unk_01026194 = GHIDRA_FIELD(cgs, 27364, 4);
  g_unk_0102613c = trap_Key_KeysForBinding;
  g_unk_01026190 = GHIDRA_FIELD(cgs, 27368, 4);
  g_unk_01026134 = trap_Key_KeynumToStringBuf;
  g_unk_0102614c = Com_Error;
  g_unk_01026150 = Com_Printf;
  g_unk_0102615c = trap_S_RegisterSound;
  g_unk_01026160 = trap_S_StartBackgroundTrack;
  g_unk_01026164 = trap_S_StopBackgroundTrack;
  g_unk_01026168 = CG_PlayCinematic;
  g_unk_0102616c = CG_StopCinematic;
  g_unk_01026170 = CG_DrawCinematic;
  g_unk_01026174 = CG_RunCinematicFrame;
  g_unk_01026178 = CG_DescriptionForCampaign;
  g_unk_0102617c = CG_NameForCampaign;
  g_unk_01026180 = trap_R_Add2dPolys;
  g_unk_01026184 = trap_UpdateScreen;
  g_unk_01026188 = trap_GetHunkData;
  g_unk_0102618c = CG_ConfigStringCopy;
  Init_Display(&cgDC);
  Menu_Reset();
  CG_Text_SetActiveFont(0);
  return;
}

void CG_AssetCache(void)
{
  _DAT_01044358 = trap_R_RegisterShaderNoMip("ui/assets/gradientbar2.tga");
  _DAT_010443d0 = trap_R_RegisterShaderNoMip("menu/art/fx_base");
  _DAT_010443d4 = trap_R_RegisterShaderNoMip("menu/art/fx_red");
  _DAT_010443d8 = trap_R_RegisterShaderNoMip("menu/art/fx_yel");
  _DAT_010443dc = trap_R_RegisterShaderNoMip("menu/art/fx_grn");
  _DAT_010443e0 = trap_R_RegisterShaderNoMip("menu/art/fx_teal");
  _DAT_010443e4 = trap_R_RegisterShaderNoMip("menu/art/fx_blue");
  _DAT_010443e8 = trap_R_RegisterShaderNoMip("menu/art/fx_cyan");
  _DAT_010443ec = trap_R_RegisterShaderNoMip("menu/art/fx_white");
  _DAT_0104436c = trap_R_RegisterShaderNoMip("ui/assets/scrollbar.tga");
  _DAT_01044360 = trap_R_RegisterShaderNoMip("ui/assets/scrollbar_arrow_dwn_a.tga");
  _DAT_0104435c = trap_R_RegisterShaderNoMip("ui/assets/scrollbar_arrow_up_a.tga");
  _DAT_01044364 = trap_R_RegisterShaderNoMip("ui/assets/scrollbar_arrow_left.tga");
  _DAT_01044368 = trap_R_RegisterShaderNoMip("ui/assets/scrollbar_arrow_right.tga");
  _DAT_01044370 = trap_R_RegisterShaderNoMip("ui/assets/scrollbar_thumb.tga");
  _DAT_01044380 = trap_R_RegisterShaderNoMip("ui/assets/slider2.tga");
  _DAT_01044384 = trap_R_RegisterShaderNoMip("ui/assets/sliderbutt_1.tga");
  return;
}

bool CG_execFile(uint32_t param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = va("%s.cfg",param_1);
  tmp_i2 = trap_PC_LoadSource(tmp_u1);
  trap_PC_FreeSource(tmp_i2);
  if (tmp_i2 != 0) {
    tmp_u1 = va("exec %s.cfg\n",param_1);
    trap_SendConsoleCommand(tmp_u1);
  }
  return tmp_i2 != 0;
}

uint32_t CG_BackupProfile(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint8_t local_325;
  uint32_t local_324;
  uint32_t local_320;
  uint8_t local_31c [256];
  uint8_t local_21c [256];
  uint8_t local_11c [264];
  uint32_t uStack_14;
  
  uStack_14 = 0x93bce;
  trap_Cvar_VariableStringBuffer("cl_profile",local_31c,0x100);
  Com_sprintf(local_21c,0x100,"profiles/%s/%s",local_31c,"etconfig.cfg");
  Com_sprintf(local_11c,0x100,"profiles/%s/%s.bak",local_31c,"etconfig.cfg");
  tmp_i1 = trap_FS_FOpenFile(local_11c,&local_320,0);
  trap_FS_FCloseFile(local_320);
  tmp_u2 = 1;
  if (tmp_i1 == 0) {
    tmp_i1 = trap_FS_FOpenFile(local_21c,&local_324,0);
    if (tmp_i1 < 1) {
      CG_Printf("forcecvar: could not open \"%s\" for backup\n",local_21c);
      tmp_u2 = 0;
    }
    else {
      tmp_i3 = trap_FS_FOpenFile(local_11c,&local_320,1);
      if (-1 < tmp_i3) {
        tmp_i3 = 0;
        do {
          tmp_i3 = tmp_i3 + 1;
          trap_FS_Read(&local_325,1,local_324);
          trap_FS_Write(&local_325,1,local_320);
        } while (tmp_i3 != tmp_i1);
        trap_FS_FCloseFile(local_324);
        trap_FS_FCloseFile(local_320);
        return 1;
      }
      CG_Printf("forcecvar: could not write \"%s\" for backup\n",local_11c);
      trap_FS_FCloseFile(local_324);
      tmp_u2 = 0;
    }
  }
  return tmp_u2;
}

void CG_RestoreProfile(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint8_t local_325;
  uint32_t local_324;
  uint32_t local_320;
  uint8_t local_31c [256];
  uint8_t local_21c [256];
  uint8_t local_11c [264];
  uint32_t uStack_14;
  
  uStack_14 = 0x93da3;
  trap_Cvar_VariableStringBuffer("cl_profile",local_11c,0x100);
  Com_sprintf(local_31c,0x100,"profiles/%s/%s",local_11c,"etconfig.cfg");
  Com_sprintf(local_21c,0x100,"profiles/%s/%s.bak",local_11c,"etconfig.cfg");
  tmp_i1 = trap_FS_FOpenFile(local_21c,&local_320,0);
  if (0 < tmp_i1) {
    tmp_i3 = 0;
    tmp_i2 = trap_FS_FOpenFile(local_31c,&local_324,1);
    if (tmp_i2 < 0) {
      CG_Printf("RestoreProfile: could not open %s.\n",local_31c);
      trap_FS_FCloseFile(local_320);
    }
    else {
      do {
        tmp_i3 = tmp_i3 + 1;
        trap_FS_Read(&local_325,1,local_320);
        trap_FS_Write(&local_325,1,local_324);
      } while (tmp_i3 != tmp_i1);
      trap_FS_FCloseFile(local_324);
      trap_FS_FCloseFile(local_320);
      trap_FS_Delete(local_21c);
      CG_Printf("Old forced cvars cleaned.\n");
    }
  }
  return;
}

void CG_Init(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,int param_5
            )

{
  uint32_t *tmp_pu1;
  uint32_t *tmp_pu2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  uint tmp_u5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  uint8_t *tmp_pu9;
  float *pfVar10;
  char *tmp_pc11;
  uint8_t tmp_u12;
  byte tmp_b13;
  uint8_t *tmp_pu14;
  uint8_t *tmp_pu15;
  uint8_t *tmp_pu16;
  float *pfVar17;
  uint8_t **tmp_ppu18;
  uint8_t *local_568;
  float local_564;
  float local_560;
  float local_55c;
  float local_558;
  float local_554;
  uint8_t local_51c [256];
  char local_41c [4];
  uint32_t auStack_418 [257];
  uint32_t uStack_14;
  
  tmp_b13 = 0;
  uStack_14 = 0x93f27;
  tmp_pu14 = cgs;
  memset(cgs,0,0x2041994);
  memset(&cg,0,0xa7bc0);
  memset(cg_entities,0,0x2be000);
  memset(cg_weapons,0,0x5eb00);
  tmp_pu2 = &cg_items;
  for (tmp_i7 = 0x800; tmp_i7 != 0; tmp_i7 = tmp_i7 + -1) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + (uint)tmp_b13 * -2 + 1;
  }
  g_unk_01047aec = param_4;
  if (param_5 == 1) {
    GHIDRA_FIELD(cgs, 33823104, 4) = 1;
    GHIDRA_FIELD(cgs, 33703444, 4) = 1;
  }
  else {
    GHIDRA_FIELD(cgs, 33703444, 4) = 1;
    trap_Cvar_VariableStringBuffer("version",local_51c,0x100);
    trap_Cvar_Register(0,"etVersion",local_51c,0x442);
    trap_Cvar_Set("etVersion",local_51c);
    if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
      tmp_pu2 = &g_unk_010b4878;
      tmp_pu1 = &g_unk_010b4878 + GHIDRA_FIELD(cgs, 27400, 4);
      do {
        *tmp_pu2 = 0xfffe7961;
        tmp_pu2 = tmp_pu2 + 1;
      } while (tmp_pu2 != tmp_pu1);
    }
  }
  CG_InitStatsDebug();
  g_unk_010afbcc = &g_unk_010918a8;
  GHIDRA_FIELD(cgs, 33575916, 4) = 0x3f800000;
  trap_GetGlconfig(0x10f4ce4);
  GHIDRA_FIELD(cgs, 27368, 4) = (float)(int)GHIDRA_FIELD(cgs, 27340, 4) / 480.0;
  if (GHIDRA_FIELD(cgs, 27340, 4) * 0x280 < GHIDRA_FIELD(cgs, 27336, 4) * 0x1e0) {
    GHIDRA_FIELD(cgs, 27372, 4) = ((float)(int)GHIDRA_FIELD(cgs, 27336, 4) - (float)(int)GHIDRA_FIELD(cgs, 27340, 4) * 1.3333334) * 0.5;
    GHIDRA_FIELD(cgs, 27364, 4) = GHIDRA_FIELD(cgs, 27368, 4);
  }
  else {
    GHIDRA_FIELD(cgs, 27372, 4) = 0.0;
    GHIDRA_FIELD(cgs, 27364, 4) = (float)(int)GHIDRA_FIELD(cgs, 27336, 4) / 640.0;
  }
  GHIDRA_FIELD(cgs, 33525332, 4) = CG_SoundScriptPrecache;
  GHIDRA_FIELD(cgs, 33525336, 4) = CG_SoundPlayIndexedScript;
  g_unk_01047ac4 = param_3;
  GHIDRA_FIELD(cgs, 27380, 4) = param_1;
  GHIDRA_FIELD(cgs, 27376, 4) = param_2;
  GHIDRA_FIELD(cgs, 33685972, 4) = 0xffffffff;
  GHIDRA_FIELD(cgs, 33685968, 4) = 0xfffffffe;
  trap_R_SetColor(0);
  GHIDRA_FIELD(cgs, 67816, 4) = trap_R_RegisterShader("gfx/2d/hudchars");
  GHIDRA_FIELD(cgs, 67820, 4) = trap_R_RegisterShader("gfx/2d/hudchars");
  GHIDRA_FIELD(cgs, 67836, 4) = trap_R_RegisterShader("white");
  GHIDRA_FIELD(cgs, 67824, 4) = trap_R_RegisterShaderNoMip("menu/art/font1_prop.tga");
  GHIDRA_FIELD(cgs, 67828, 4) = trap_R_RegisterShaderNoMip("menu/art/font1_prop_glo.tga");
  GHIDRA_FIELD(cgs, 67832, 4) = trap_R_RegisterShaderNoMip("menu/art/font2_prop.tga");
  CG_RegisterCvars();
  if ((cg_logFile[0x10] == '\0') || (GHIDRA_FIELD(cg_clientLog, 12, 4) == 0)) {
    CG_Printf("Not logging client output to disk.\n");
  }
  else {
    trap_FS_FOpenFile(0x101ff50,&g_unk_010eecc8,2);
    if (g_unk_010eecc8 == 0) {
      CG_Printf("^3WARNING: Couldn\'t open client log: %s\n",0x101ff50);
    }
  }
  CG_InitConsoleCommands();
  CG_LoadHudMenu();
  CG_AssetCache();
  tmp_pu15 = tmp_pu14;
  trap_GetGameState(tmp_pu14);
  g_unk_010aac24 = 0xffffffff;
  CG_ParseServerinfo(&g_unk_0011d841);
  CG_ParseWolfinfo();
  tmp_pc3 = (char *)va("autoexec_%s",tmp_pu14 + 0x6b4c);
  tmp_u4 = va("%s.cfg",tmp_pc3);
  tmp_i7 = trap_PC_LoadSource(tmp_u4);
  trap_PC_FreeSource(tmp_i7);
  if (tmp_i7 == 0) {
    tmp_pc3 = "autoexec_default";
    tmp_u4 = va("%s.cfg","autoexec_default");
    tmp_i7 = trap_PC_LoadSource(tmp_u4);
    trap_PC_FreeSource(tmp_i7);
    if (tmp_i7 == 0) goto LAB_0009429b;
  }
  tmp_u4 = va("exec %s.cfg\n",tmp_pc3);
  trap_SendConsoleCommand(tmp_u4);
LAB_0009429b:
  GHIDRA_FIELD(cgs, 33526364, 4) = 0;
  if (GHIDRA_FIELD(cgs, 27388, 4) == 4) {
    CG_LocateCampaign();
  }
  else {
    CG_LocateArena();
  }
  CG_ClearTrails();
  CG_ClearParticles();
  InitSmokeSprites();
  tmp_pu14 = tmp_pu15 + GHIDRA_FIELD(cgs, 40, 4) + 0x1000;
  tmp_i7 = Q_stricmp(tmp_pu14,"Enemy Territory");
  if (tmp_i7 != 0) {
    CG_Error("Client/Server game mismatch: \'%s/%s\'","Enemy Territory",tmp_pu14);
  }
  trap_Cvar_Set("cg_etVersion","Enemy Territory, ET 2.60");
  tmp_pu16 = tmp_pu15;
  GHIDRA_FIELD(cgs, 28480, 4) = strtol(tmp_pu15 + GHIDRA_FIELD(cgs, 44, 4) + 0x1000,(char **)0x0,10);
  GHIDRA_FIELD(cgs, 28484, 4) = strtol(tmp_pu15 + GHIDRA_FIELD(cgs, 132, 4) + 0x1000,(char **)0x0,10);
  tmp_pu14 = tmp_pu15 + 0x6b0c;
  CG_ParseReinforcementTimes(tmp_pu15 + GHIDRA_FIELD(cgs, 112, 4) + 0x1000);
  CG_initStrings();
  CG_windowInit();
  trap_CM_LoadMap(tmp_pu14);
  String_Init();
  g_unk_01047af0 = 1;
  CG_RegisterSounds();
  CG_LoadingString(tmp_pu14);
  trap_R_LoadWorldMap(tmp_pu14);
  CG_LoadingString(":entities:");
  g_unk_010b16f8 = 0;
  numSplinePaths = 0;
  numPathCorners = 0;
  BG_ClearAnimationPool();
  BG_ClearCharacterPool();
  BG_InitWeaponStrings();
  CG_ParseEntitiesFromString();
  CG_LoadObjectiveData();
  CG_LoadingString(":game media:");
  CG_LoadingString(":textures:");
  tmp_i7 = 0;
  do {
    tmp_u4 = trap_R_RegisterShader(*(uint32_t *)((int)&sb_nums_13097 + tmp_i7));
    *(uint32_t *)(cgs + tmp_i7 + 0x10c54) = tmp_u4;
    tmp_i7 = tmp_i7 + 4;
  } while (tmp_i7 != 0x2c);
  tmp_i7 = 0;
  GHIDRA_FIELD(cgs, 68084, 4) = trap_R_RegisterShader("fleshimpactsmokepuff");
  GHIDRA_FIELD(cgs, 68088, 4) = trap_R_RegisterShader("smokePuff");
  GHIDRA_FIELD(cgs, 68836, 4) = trap_R_RegisterShader("bloodCloud");
  GHIDRA_FIELD(cgs, 68524, 4) = trap_R_RegisterShader("smokePuffdirty");
  GHIDRA_FIELD(cgs, 68528, 4) = trap_R_RegisterShader("smokePuffblack1");
  GHIDRA_FIELD(cgs, 68532, 4) = trap_R_RegisterShader("smokePuffblack2");
  GHIDRA_FIELD(cgs, 68536, 4) = trap_R_RegisterShader("smokePuffblack3");
  GHIDRA_FIELD(cgs, 68540, 4) = trap_R_RegisterShader("smokePuffblack4");
  GHIDRA_FIELD(cgs, 68544, 4) = trap_R_RegisterShader("smokePuffblack5");
  do {
    tmp_i7 = tmp_i7 + 1;
    tmp_u4 = va("viewBloodBlend%i",tmp_i7);
    tmp_u4 = trap_R_RegisterShader(tmp_u4);
    *(uint32_t *)(cgs + tmp_i7 * 4 + 0x10bc0) = tmp_u4;
  } while (tmp_i7 != 5);
  tmp_i7 = 0;
  GHIDRA_FIELD(cgs, 68568, 4) = trap_R_RegisterShader("viewFlashBlood");
  do {
    tmp_i7 = tmp_i7 + 1;
    tmp_u4 = va("viewFlashFire%i",tmp_i7);
    tmp_u4 = trap_R_RegisterShader(tmp_u4);
    *(uint32_t *)(cgs + tmp_i7 * 4 + 0x10bd8) = tmp_u4;
  } while (tmp_i7 != 0x10);
  if (GHIDRA_FIELD(cgs, 27292, 4) == 3) {
    GHIDRA_FIELD(cgs, 68092, 4) = trap_R_RegisterShader("smokePuffRagePro");
  }
  GHIDRA_FIELD(cgs, 68100, 4) = trap_R_RegisterShader("bloodTrail");
  GHIDRA_FIELD(cgs, 68076, 4) = trap_R_RegisterShader("gfx/misc/reticlesimple");
  GHIDRA_FIELD(cgs, 68080, 4) = trap_R_RegisterShader("gfx/misc/binocsimple");
  GHIDRA_FIELD(cgs, 68512, 4) = trap_R_RegisterShader("snow_tri");
  GHIDRA_FIELD(cgs, 68516, 4) = trap_R_RegisterShader("oilParticle");
  GHIDRA_FIELD(cgs, 68520, 4) = trap_R_RegisterShader("oilSlick");
  GHIDRA_FIELD(cgs, 68096, 4) = trap_R_RegisterShader("waterBubble");
  GHIDRA_FIELD(cgs, 68004, 4) = trap_R_RegisterShader("gfx/misc/tracer");
  GHIDRA_FIELD(cgs, 68104, 4) = trap_R_RegisterShader("gfx/2d/usableHint");
  GHIDRA_FIELD(cgs, 68108, 4) = trap_R_RegisterShader("gfx/2d/notUsableHint");
  GHIDRA_FIELD(cgs, 68112, 4) = trap_R_RegisterShader("gfx/2d/doorHint");
  GHIDRA_FIELD(cgs, 68116, 4) = trap_R_RegisterShader("gfx/2d/doorRotateHint");
  GHIDRA_FIELD(cgs, 68120, 4) = trap_R_RegisterShader("gfx/2d/lockedhint");
  GHIDRA_FIELD(cgs, 68124, 4) = trap_R_RegisterShader("gfx/2d/lockedhint");
  GHIDRA_FIELD(cgs, 68128, 4) = trap_R_RegisterShader("gfx/2d/mg42Hint");
  GHIDRA_FIELD(cgs, 68132, 4) = trap_R_RegisterShader("gfx/2d/breakableHint");
  GHIDRA_FIELD(cgs, 68136, 4) = trap_R_RegisterShader("gfx/2d/chairHint");
  GHIDRA_FIELD(cgs, 68140, 4) = trap_R_RegisterShader("gfx/2d/alarmHint");
  GHIDRA_FIELD(cgs, 68144, 4) = trap_R_RegisterShader("icons/iconw_medheal_1_select");
  GHIDRA_FIELD(cgs, 68148, 4) = trap_R_RegisterShader("icons/iconw_knife_1_select.tga");
  GHIDRA_FIELD(cgs, 68152, 4) = trap_R_RegisterShader("gfx/2d/ladderHint");
  GHIDRA_FIELD(cgs, 68156, 4) = trap_R_RegisterShader("gfx/2d/buttonHint");
  GHIDRA_FIELD(cgs, 68160, 4) = trap_R_RegisterShader("gfx/2d/waterHint");
  GHIDRA_FIELD(cgs, 68164, 4) = trap_R_RegisterShader("gfx/2d/weaponHint");
  GHIDRA_FIELD(cgs, 68168, 4) = trap_R_RegisterShader("icons/iconw_ammopack_1_select");
  GHIDRA_FIELD(cgs, 68172, 4) = trap_R_RegisterShader("gfx/2d/powerupHint");
  GHIDRA_FIELD(cgs, 68176, 4) = trap_R_RegisterShader("gfx/2d/holdableHint");
  GHIDRA_FIELD(cgs, 68180, 4) = trap_R_RegisterShader("gfx/2d/inventoryHint");
  GHIDRA_FIELD(cgs, 67964, 4) = trap_R_RegisterShaderNoMip("gfx/2d/friendlycross.tga");
  GHIDRA_FIELD(cgs, 68184, 4) = trap_R_RegisterShader("gfx/2d/buildHint");
  GHIDRA_FIELD(cgs, 68188, 4) = trap_R_RegisterShader("gfx/2d/disarmHint");
  GHIDRA_FIELD(cgs, 68192, 4) = trap_R_RegisterShader("gfx/2d/reviveHint");
  GHIDRA_FIELD(cgs, 68196, 4) = trap_R_RegisterShaderNoMip("gfx/2d/dynamiteHint");
  GHIDRA_FIELD(cgs, 68200, 4) = trap_R_RegisterShaderNoMip("gfx/2d/tankHint");
  GHIDRA_FIELD(cgs, 68204, 4) = trap_R_RegisterShaderNoMip("gfx/2d/satchelchargeHint");
  GHIDRA_FIELD(cgs, 68480, 4) = trap_R_RegisterShaderNoMip("gfx/2d/landmineHint");
  GHIDRA_FIELD(cgs, 68208, 4) = trap_R_RegisterShaderNoMip("gfx/2d/uniformHint");
  if (GHIDRA_FIELD(cgs, 33575848, 4) == 0) {
    tmp_u4 = va("levelshots/%s_cc.tga",0x10f69ac);
    GHIDRA_FIELD(cgs, 68252, 4) = trap_R_RegisterShaderNoMip(tmp_u4);
    tmp_u4 = va("levelshots/%s_cc_trans",0x10f69ac);
    GHIDRA_FIELD(cgs, 68316, 4) = trap_R_RegisterShaderNoMip(tmp_u4);
    tmp_u4 = va("levelshots/%s_cc_automap",0x10f69ac);
    GHIDRA_FIELD(cgs, 68380, 4) = trap_R_RegisterShaderNoMip(tmp_u4);
  }
  else if (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4)) {
    tmp_pc3 = "levelshots/%s_%i_cc.tga";
    tmp_pc11 = "levelshots/%s_%i_cc_trans";
    tmp_i7 = 0;
    tmp_pu2 = (uint32_t *)(cgs + 0x10a9c);
    do {
      tmp_u4 = va(tmp_pc3,0x10f69ac,tmp_i7);
      tmp_u4 = trap_R_RegisterShaderNoMip(tmp_u4);
      *tmp_pu2 = tmp_u4;
      tmp_u4 = va(tmp_pc11,0x10f69ac,tmp_i7);
      tmp_u4 = trap_R_RegisterShaderNoMip(tmp_u4);
      tmp_pu2[0x10] = tmp_u4;
      tmp_i8 = tmp_i7 + 1;
      tmp_u4 = va("levelshots/%s_%i_cc_automap",0x10f69ac,tmp_i7);
      tmp_u4 = trap_R_RegisterShaderNoMip(tmp_u4);
      tmp_pu2[0x20] = tmp_u4;
      tmp_i7 = tmp_i8;
      tmp_pu2 = tmp_pu2 + 1;
    } while (tmp_i8 < (int)GHIDRA_FIELD(cgs, 33575848, 4));
  }
  GHIDRA_FIELD(cgs, 68476, 4) = trap_R_RegisterShaderNoMip("images/blackmask");
  GHIDRA_FIELD(cgs, 68444, 4) = trap_R_RegisterShaderNoMip("levelshots/automap_mask");
  GHIDRA_FIELD(cgs, 68448, 4) = trap_R_RegisterShaderNoMip("ui/assets2/maptrim_long");
  GHIDRA_FIELD(cgs, 68452, 4) = trap_R_RegisterShaderNoMip("ui/assets2/maptrim_long2");
  GHIDRA_FIELD(cgs, 68456, 4) = trap_R_RegisterShaderNoMip("ui/assets2/maptrim_edge.tga");
  GHIDRA_FIELD(cgs, 68460, 4) = trap_R_RegisterShaderNoMip("sprites/landmine_axis");
  GHIDRA_FIELD(cgs, 68464, 4) = trap_R_RegisterShaderNoMip("sprites/landmine_allied");
  GHIDRA_FIELD(cgs, 68468, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_flagaxis");
  GHIDRA_FIELD(cgs, 68472, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_flagallied");
  GHIDRA_FIELD(cgs, 68484, 4) = trap_R_RegisterShaderNoMip("sprites/construct.tga");
  GHIDRA_FIELD(cgs, 131908, 4) = trap_R_RegisterShaderNoMip("gfx/flags/world_flags");
  GHIDRA_FIELD(cgs, 68508, 4) = trap_R_RegisterShaderNoMip("gfx/2d/compass2.tga");
  GHIDRA_FIELD(cgs, 68504, 4) = trap_R_RegisterShaderNoMip("gfx/2d/compass.tga");
  GHIDRA_FIELD(cgs, 68488, 4) = trap_R_RegisterShaderNoMip("sprites/buddy.tga");
  tmp_pc3 = "gfx/2d/crosshair%c_alt";
  tmp_i7 = 0x61;
  do {
    tmp_u4 = va("gfx/2d/crosshair%c",tmp_i7);
    tmp_u4 = trap_R_RegisterShader(tmp_u4);
    tmp_i8 = tmp_i7 + 1;
    *(uint32_t *)(cgs + (int)("strftime" + tmp_i7 * 4 + 4)) = tmp_u4;
    tmp_u4 = va(tmp_pc3,tmp_i7);
    tmp_u4 = trap_R_RegisterShader(tmp_u4);
    *(uint32_t *)(tmp_i7 * 4 + 0x10ab170) = tmp_u4;
    tmp_i7 = tmp_i8;
  } while (tmp_i8 != 0x71);
  tmp_i7 = 0;
  do {
    tmp_u4 = va("gfx/limbo/medals0%i",tmp_i7);
    tmp_u4 = trap_R_RegisterShaderNoMip(tmp_u4);
    *(uint32_t *)(cgs + tmp_i7 * 4 + 0x110e4) = tmp_u4;
    tmp_i7 = tmp_i7 + 1;
  } while (tmp_i7 != 7);
  GHIDRA_FIELD(cgs, 68072, 4) = trap_R_RegisterShader("gfx/2d/backtile");
  GHIDRA_FIELD(cgs, 67864, 4) = trap_R_RegisterShader("gfx/2d/colorbar.tga");
  GHIDRA_FIELD(cgs, 67844, 4) = trap_R_RegisterShader("sprintbar");
  GHIDRA_FIELD(cgs, 67852, 4) = trap_R_RegisterShader("AlliedHelmet");
  GHIDRA_FIELD(cgs, 67848, 4) = trap_R_RegisterShader("AxisHelmet");
  GHIDRA_FIELD(cgs, 67840, 4) = trap_R_RegisterShader("projectionshadow");
  CG_LoadingString(":models:");
  GHIDRA_FIELD(cgs, 67940, 4) = trap_R_RegisterModel("models/weapons2/shells/m_shell.md3");
  GHIDRA_FIELD(cgs, 67944, 4) = trap_R_RegisterModel("models/weapons2/shells/pf_shell.md3");
  GHIDRA_FIELD(cgs, 67948, 4) = trap_R_RegisterModel("models/weapons2/shells/sm_shell.md3");
  GHIDRA_FIELD(cgs, 67868, 4) = trap_R_RegisterModel("models/mapobjects/debris/brick1.md3");
  GHIDRA_FIELD(cgs, 67872, 4) = trap_R_RegisterModel("models/mapobjects/debris/brick2.md3");
  GHIDRA_FIELD(cgs, 67876, 4) = trap_R_RegisterModel("models/mapobjects/debris/brick3.md3");
  GHIDRA_FIELD(cgs, 67880, 4) = trap_R_RegisterModel("models/mapobjects/debris/brick4.md3");
  GHIDRA_FIELD(cgs, 67884, 4) = trap_R_RegisterModel("models/mapobjects/debris/brick5.md3");
  GHIDRA_FIELD(cgs, 67888, 4) = trap_R_RegisterModel("models/mapobjects/debris/brick6.md3");
  GHIDRA_FIELD(cgs, 67892, 4) = trap_R_RegisterModel("models/mapobjects/debris/rubble1.md3");
  GHIDRA_FIELD(cgs, 67896, 4) = trap_R_RegisterModel("models/mapobjects/debris/rubble2.md3");
  GHIDRA_FIELD(cgs, 67900, 4) = trap_R_RegisterModel("models/mapobjects/debris/rubble3.md3");
  GHIDRA_FIELD(cgs, 67916, 4) = trap_R_RegisterModel("models/gibs/wood/wood1.md3");
  GHIDRA_FIELD(cgs, 67920, 4) = trap_R_RegisterModel("models/gibs/wood/wood2.md3");
  GHIDRA_FIELD(cgs, 67924, 4) = trap_R_RegisterModel("models/gibs/wood/wood3.md3");
  GHIDRA_FIELD(cgs, 67928, 4) = trap_R_RegisterModel("models/gibs/wood/wood4.md3");
  GHIDRA_FIELD(cgs, 67932, 4) = trap_R_RegisterModel("models/gibs/wood/wood5.md3");
  GHIDRA_FIELD(cgs, 67936, 4) = trap_R_RegisterModel("models/gibs/wood/wood6.md3");
  GHIDRA_FIELD(cgs, 67904, 4) = trap_R_RegisterModel("models/shards/fabric1.md3");
  GHIDRA_FIELD(cgs, 67908, 4) = trap_R_RegisterModel("models/shards/fabric2.md3");
  GHIDRA_FIELD(cgs, 67912, 4) = trap_R_RegisterModel("models/shards/fabric3.md3");
  GHIDRA_FIELD(cgs, 67968, 4) = trap_R_RegisterShader("sprites/shield");
  GHIDRA_FIELD(cgs, 67972, 4) = trap_R_RegisterShader("sprites/skull");
  GHIDRA_FIELD(cgs, 67980, 4) = trap_R_RegisterShader("sprites/medic_revive");
  GHIDRA_FIELD(cgs, 67976, 4) = trap_R_RegisterShader("sprites/poisoned");
  GHIDRA_FIELD(cgs, 67984, 4) = trap_R_RegisterShader("sprites/voiceChat");
  GHIDRA_FIELD(cgs, 67988, 4) = trap_R_RegisterShader("sprites/balloon3");
  GHIDRA_FIELD(cgs, 67992, 4) = trap_R_RegisterShader("sprites/objective");
  GHIDRA_FIELD(cgs, 67996, 4) = trap_R_RegisterShader("ui/assets/filter_antilag");
  GHIDRA_FIELD(cgs, 68820, 4) = trap_R_RegisterModel("models/weaphits/bullet.md3");
  GHIDRA_FIELD(cgs, 68824, 4) = trap_R_RegisterShader("waterSplash");
  GHIDRA_FIELD(cgs, 68840, 4) = trap_R_RegisterShader("sparkParticle");
  GHIDRA_FIELD(cgs, 68844, 4) = trap_R_RegisterShader("smokeTrail");
  GHIDRA_FIELD(cgs, 68848, 4) = trap_R_RegisterShader("flamethrowerFireStream");
  GHIDRA_FIELD(cgs, 68856, 4) = trap_R_RegisterShader("entityOnFire1");
  GHIDRA_FIELD(cgs, 68852, 4) = trap_R_RegisterShader("entityOnFire2");
  GHIDRA_FIELD(cgs, 68860, 4) = trap_R_RegisterShader("sparkFlareParticle");
  GHIDRA_FIELD(cgs, 68864, 4) = trap_R_RegisterShader("spotLight");
  GHIDRA_FIELD(cgs, 68868, 4) = trap_R_RegisterShader("lightBeam");
  GHIDRA_FIELD(cgs, 68872, 4) = trap_R_RegisterShader("bulletParticleTrail");
  GHIDRA_FIELD(cgs, 68876, 4) = trap_R_RegisterShader("smokeParticle");
  GHIDRA_FIELD(cgs, 68880, 4) = trap_R_RegisterShader("dirt_splash");
  GHIDRA_FIELD(cgs, 68884, 4) = trap_R_RegisterShader("water_splash");
  GHIDRA_FIELD(cgs, 68892, 4) = trap_R_RegisterShader("textures/sfx/construction");
  GHIDRA_FIELD(cgs, 68896, 4) = trap_R_RegisterShader("sprites/uniform_allied");
  GHIDRA_FIELD(cgs, 68900, 4) = trap_R_RegisterShader("sprites/uniform_axis");
  GHIDRA_FIELD(cgs, 69668, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/filter_axis");
  GHIDRA_FIELD(cgs, 69672, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/filter_allied");
  GHIDRA_FIELD(cgs, 69676, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/filter_spawn");
  GHIDRA_FIELD(cgs, 69680, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/filter_bo");
  GHIDRA_FIELD(cgs, 69684, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/filter_healthammo");
  GHIDRA_FIELD(cgs, 69688, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/filter_construction");
  GHIDRA_FIELD(cgs, 69692, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/filter_destruction");
  GHIDRA_FIELD(cgs, 69696, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/filter_objective");
  GHIDRA_FIELD(cgs, 69708, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/filter_back_on");
  GHIDRA_FIELD(cgs, 69712, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/filter_back_off");
  GHIDRA_FIELD(cgs, 69660, 4) = trap_R_RegisterShaderNoMip("ui/assets2/stamp_complete");
  GHIDRA_FIELD(cgs, 69664, 4) = trap_R_RegisterShaderNoMip("ui/assets2/stamp_failed");
  GHIDRA_FIELD(cgs, 69716, 4) = trap_R_RegisterShaderNoMip("ui/assets/mp_player_highlight.tga");
  GHIDRA_FIELD(cgs, 69720, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_constaxis");
  GHIDRA_FIELD(cgs, 69724, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_constallied");
  GHIDRA_FIELD(cgs, 69736, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_axisgren");
  GHIDRA_FIELD(cgs, 69740, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_alliedgren");
  GHIDRA_FIELD(cgs, 69744, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_satchel");
  GHIDRA_FIELD(cgs, 69748, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_satchel");
  GHIDRA_FIELD(cgs, 69752, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_dynamite");
  GHIDRA_FIELD(cgs, 69756, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_dynamite");
  GHIDRA_FIELD(cgs, 69760, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_churchill");
  GHIDRA_FIELD(cgs, 69728, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_bo_axis");
  GHIDRA_FIELD(cgs, 69732, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cm_bo_allied");
  GHIDRA_FIELD(cgs, 69792, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/mort_hit");
  GHIDRA_FIELD(cgs, 69796, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/mort_target");
  GHIDRA_FIELD(cgs, 69800, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/mort_targetarrow");
  GHIDRA_FIELD(cgs, 69764, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_battlesense");
  GHIDRA_FIELD(cgs, 69784, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_soldier");
  GHIDRA_FIELD(cgs, 69772, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_medic");
  GHIDRA_FIELD(cgs, 69768, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_engineer");
  GHIDRA_FIELD(cgs, 69776, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_fieldops");
  GHIDRA_FIELD(cgs, 69788, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_covertops");
  GHIDRA_FIELD(cgs, 69780, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_lightweap");
  GHIDRA_FIELD(cgs, 68904, 4) = trap_R_RegisterShader("models/players/common/specGlow");
  CG_LoadRankIcons();
  CG_LimboPanel_Init();
  CG_ChatPanel_Setup();
  CG_Fireteams_Setup();
  GHIDRA_FIELD(cgs, 67956, 4) = trap_R_RegisterShaderNoMip("railCore");
  GHIDRA_FIELD(cgs, 67960, 4) = trap_R_RegisterShader("textures/props/cable_m01");
  GHIDRA_FIELD(cgs, 68828, 4) = trap_R_RegisterModel("models/multiplayer/binocs/binocs.md3");
  GHIDRA_FIELD(cgs, 68812, 4) = trap_R_RegisterModel("models/furniture/barrel/barrel_a.md3");
  GHIDRA_FIELD(cgs, 68816, 4) = trap_R_RegisterModel("models/weapons2/machinegun/mg42_flash.md3");
  GHIDRA_FIELD(cgs, 68636, 4) = trap_R_RegisterModel("models/shards/glass1.md3");
  GHIDRA_FIELD(cgs, 68640, 4) = trap_R_RegisterModel("models/shards/glass2.md3");
  GHIDRA_FIELD(cgs, 68644, 4) = trap_R_RegisterModel("models/shards/wood1.md3");
  tmp_i7 = 0;
  GHIDRA_FIELD(cgs, 68648, 4) = trap_R_RegisterModel("models/shards/wood2.md3");
  GHIDRA_FIELD(cgs, 68652, 4) = trap_R_RegisterModel("models/shards/metal1.md3");
  GHIDRA_FIELD(cgs, 68656, 4) = trap_R_RegisterModel("models/shards/metal2.md3");
  GHIDRA_FIELD(cgs, 68660, 4) = trap_R_RegisterModel("models/mapobjects/debris/brick000.md3");
  GHIDRA_FIELD(cgs, 68664, 4) = trap_R_RegisterModel("models/mapobjects/debris/brick001.md3");
  GHIDRA_FIELD(cgs, 68668, 4) = trap_R_RegisterModel("models/mapobjects/debris/brick002.md3");
  do {
    tmp_i7 = tmp_i7 + 1;
    Com_sprintf(local_41c,0x400,"models/mapobjects/debris/personal%i.md3",tmp_i7);
    tmp_u4 = trap_R_RegisterModel(local_41c);
    *(uint32_t *)(cgs + tmp_i7 * 4 + 0x10c3c) = tmp_u4;
  } while (tmp_i7 != 5);
  tmp_pu2 = &cg_items;
  for (tmp_i7 = 0x800; tmp_i7 != 0; tmp_i7 = tmp_i7 + -1) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + (uint)tmp_b13 * -2 + 1;
  }
  memset(cg_weapons,0,0x5eb00);
  CG_LoadingString(":weapons:");
  tmp_pu14 = tmp_pu16;
  tmp_u4 = Info_ValueForKey(tmp_pu16 + GHIDRA_FIELD(cgs, 144, 4) + 0x1000,"W");
  Q_strncpyz(tmp_pu16 + 0x2038d58,tmp_u4,0x100);
  tmp_i7 = 0;
  do {
    tmp_i8 = BG_WeaponInWolfMP(tmp_i7);
    if ((tmp_i8 != 0) || (tmp_i7 == 0)) {
      CG_RegisterWeapon(tmp_i7,0);
      BG_RegisterWeapon(tmp_i7,0);
    }
    tmp_i7 = tmp_i7 + 1;
  } while (tmp_i7 != 0x34);
  tmp_i7 = 1;
  CG_LoadingString(":items:");
  if (1 < bg_numItems) {
    do {
      tmp_i8 = tmp_i7 + 1;
      CG_RegisterItemVisuals(tmp_i7);
      tmp_i7 = tmp_i8;
    } while (tmp_i8 < bg_numItems);
  }
  GHIDRA_FIELD(cgs, 68832, 4) = trap_R_RegisterShader("rocketExplosion");
  GHIDRA_FIELD(cgs, 69812, 4) = trap_S_RegisterSound("sound/weapons/mg42/mg42_fire.wav",0);
  GHIDRA_FIELD(cgs, 69816, 4) = trap_S_RegisterSound("sound/weapons/mg42/mg42_far.wav",0);
  GHIDRA_FIELD(cgs, 69820, 4) = trap_S_RegisterSound("sound/weapons/mg42/mg42_heat.wav",0);
  GHIDRA_FIELD(cgs, 69824, 4) = trap_S_RegisterSound("sound/weapons/browning/browning_fire.wav",0);
  tmp_i7 = 0;
  GHIDRA_FIELD(cgs, 69828, 4) = trap_S_RegisterSound("sound/weapons/browning/browning_far.wav",0);
  GHIDRA_FIELD(cgs, 69832, 4) = trap_S_RegisterSound("sound/weapons/browning/browning_heat.wav",0);
  GHIDRA_FIELD(cgs, 68792, 4) = trap_R_RegisterShaderNoMip("gfx/damage/bullet_mrk");
  GHIDRA_FIELD(cgs, 68808, 4) = trap_R_RegisterShaderNoMip("gfx/damage/burn_med_mrk");
  GHIDRA_FIELD(cgs, 68736, 4) = trap_R_RegisterShaderNoMip("markShadowFoot");
  GHIDRA_FIELD(cgs, 68740, 4) = trap_R_RegisterShaderNoMip("markShadowTorso");
  GHIDRA_FIELD(cgs, 68744, 4) = trap_R_RegisterShaderNoMip(&g_unk_001184c0);
  GHIDRA_FIELD(cgs, 68748, 4) = trap_R_RegisterShaderNoMip("wakeAnim");
  GHIDRA_FIELD(cgs, 68796, 4) = trap_R_RegisterShaderNoMip("gfx/damage/metal_mrk");
  GHIDRA_FIELD(cgs, 68800, 4) = trap_R_RegisterShaderNoMip("gfx/damage/wood_mrk");
  GHIDRA_FIELD(cgs, 68804, 4) = trap_R_RegisterShaderNoMip("gfx/damage/glass_mrk");
  do {
    tmp_i7 = tmp_i7 + 1;
    Com_sprintf(local_41c,0x400,"blood_dot%i",tmp_i7);
    tmp_u4 = trap_R_RegisterShader(local_41c);
    *(uint32_t *)(cgs + tmp_i7 * 4 + 0x10ca0) = tmp_u4;
  } while (tmp_i7 != 5);
  CG_LoadingString(":inline models:");
  GHIDRA_FIELD(cgs, 33800, 4) = trap_CM_NumInlineModels();
  if (0x100 < (int)GHIDRA_FIELD(cgs, 33800, 4)) {
    CG_Error("CG_RegisterGraphics: Too many inline models: %i\n",GHIDRA_FIELD(cgs, 33800, 4));
  }
  if ((int)GHIDRA_FIELD(cgs, 33800, 4) < 2) {
    pfVar17 = &local_55c;
    tmp_ppu18 = &local_568;
  }
  else {
    tmp_i7 = 1;
    pfVar17 = &local_55c;
    tmp_ppu18 = &local_568;
    pfVar10 = (float *)(cgs + 0x8818);
    do {
      Com_sprintf(local_41c,0x400,&g_unk_00118ae5,tmp_i7,tmp_pu14,pfVar17,tmp_ppu18);
      tmp_u4 = trap_R_RegisterModel(local_41c);
      *(uint32_t *)(cgs + tmp_i7 * 4 + 0x840c) = tmp_u4;
      tmp_i7 = tmp_i7 + 1;
      trap_R_ModelBounds(tmp_u4,tmp_ppu18,pfVar17);
      *pfVar10 = (local_55c - (float)local_568) * 0.5 + (float)local_568;
      pfVar10[1] = (local_558 - local_564) * 0.5 + local_564;
      pfVar10[2] = (local_554 - local_560) * 0.5 + local_560;
      pfVar10 = pfVar10 + 3;
    } while (tmp_i7 < (int)GHIDRA_FIELD(cgs, 33800, 4));
  }
  CG_LoadingString(":server models:");
  CG_LoadingString(":particles:");
  CG_ClearParticles();
  InitSmokeSprites();
  CG_LoadingString(":classes:");
  CG_RegisterPlayerClasses();
  CG_InitPMGraphics();
  GHIDRA_FIELD(cgs, 131844, 4) = trap_R_RegisterShaderNoMip("icons/iconw_browning_1_select");
  GHIDRA_FIELD(cgs, 69836, 4) = trap_R_RegisterModel("models/mapobjects/tanks_sd/mg42nestbase.md3");
  GHIDRA_FIELD(cgs, 69840, 4) = trap_R_RegisterModel("models/mapobjects/tanks_sd/mg42nest.md3");
  GHIDRA_FIELD(cgs, 69844, 4) = trap_R_RegisterModel("models/mapobjects/tanks_sd/mg42.md3");
  GHIDRA_FIELD(cgs, 69848, 4) = trap_R_RegisterModel("models/multiplayer/browning/thirdperson.md3");
  GHIDRA_FIELD(cgs, 69852, 4) = trap_R_RegisterModel("models/multiplayer/mg42/v_mg42.md3");
  GHIDRA_FIELD(cgs, 69856, 4) = trap_R_RegisterModel("models/multiplayer/browning/tankmounted.md3");
  GHIDRA_FIELD(cgs, 69804, 4) = trap_R_RegisterShaderNoMip("sprites/voiceMedic_cm");
  GHIDRA_FIELD(cgs, 69808, 4) = trap_R_RegisterShaderNoMip("sprites/voiceMedic");
  trap_R_RegisterFont("ariblk",0x1b,0x1100f64);
  trap_R_RegisterFont("ariblk",0x10,0x1105fa8);
  trap_R_RegisterFont("courbd",0x1e,0x110afec);
  GHIDRA_FIELD(cgs, 69888, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/medal_back");
  GHIDRA_FIELD(cgs, 131536, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/number_roll");
  GHIDRA_FIELD(cgs, 131540, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/number_back");
  GHIDRA_FIELD(cgs, 131544, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/skill_roll");
  GHIDRA_FIELD(cgs, 131548, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/skill_back");
  GHIDRA_FIELD(cgs, 131584, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/redlight_on");
  GHIDRA_FIELD(cgs, 131588, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/redlight_on02");
  GHIDRA_FIELD(cgs, 131592, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/redlight_off");
  GHIDRA_FIELD(cgs, 131552, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/but_weap_off");
  GHIDRA_FIELD(cgs, 131556, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/but_weap_on");
  GHIDRA_FIELD(cgs, 131560, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/weap_card");
  GHIDRA_FIELD(cgs, 131564, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/butsur_hor");
  GHIDRA_FIELD(cgs, 131568, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/butsur_vert");
  GHIDRA_FIELD(cgs, 131572, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/butsur_corn");
  GHIDRA_FIELD(cgs, 131576, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/outofstock");
  GHIDRA_FIELD(cgs, 131580, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/nadesoutofstock");
  GHIDRA_FIELD(cgs, 131604, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_engineer");
  GHIDRA_FIELD(cgs, 131596, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_soldier");
  GHIDRA_FIELD(cgs, 131612, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_covertops");
  GHIDRA_FIELD(cgs, 131608, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_fieldops");
  GHIDRA_FIELD(cgs, 131600, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_medic");
  GHIDRA_FIELD(cgs, 131692, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_battlesense");
  GHIDRA_FIELD(cgs, 131688, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/ic_lightweap");
  GHIDRA_FIELD(cgs, 131616, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/skill_back_on");
  GHIDRA_FIELD(cgs, 131620, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/skill_back_off");
  GHIDRA_FIELD(cgs, 131628, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/skill_4pieces_off");
  GHIDRA_FIELD(cgs, 131624, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/skill_4pieces_on");
  GHIDRA_FIELD(cgs, 131652, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/sk_5_on.tga");
  GHIDRA_FIELD(cgs, 131656, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/sk_5_off.tga");
  GHIDRA_FIELD(cgs, 131640, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/skill_engineer");
  GHIDRA_FIELD(cgs, 131632, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/skill_soldier");
  GHIDRA_FIELD(cgs, 131648, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/skill_covops");
  GHIDRA_FIELD(cgs, 131644, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/skill_fieldops");
  GHIDRA_FIELD(cgs, 131636, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/skill_medic");
  GHIDRA_FIELD(cgs, 131884, 4) = trap_R_RegisterShaderNoMip("gfx/flakjacket_axis");
  GHIDRA_FIELD(cgs, 131888, 4) = trap_R_RegisterShaderNoMip("ui/assets/filter_lives.tga");
  GHIDRA_FIELD(cgs, 131892, 4) = trap_R_RegisterShaderNoMip("icons/iconw_syringe2_1_select.tga");
  GHIDRA_FIELD(cgs, 131896, 4) = trap_R_RegisterShaderNoMip("icons/iconw_binoculars_1_select.tga");
  GHIDRA_FIELD(cgs, 131660, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/but_team_on");
  GHIDRA_FIELD(cgs, 131664, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/but_team_off");
  GHIDRA_FIELD(cgs, 131668, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/but_team_allied");
  GHIDRA_FIELD(cgs, 131672, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/but_team_axis");
  GHIDRA_FIELD(cgs, 131676, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/but_team_spec");
  GHIDRA_FIELD(cgs, 131680, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/cc_blend");
  GHIDRA_FIELD(cgs, 131684, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/weap_blend");
  GHIDRA_FIELD(cgs, 131696, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/number_border");
  GHIDRA_FIELD(cgs, 131756, 4) = trap_R_RegisterShaderNoMip("gfx/hud/ic_power");
  GHIDRA_FIELD(cgs, 131760, 4) = trap_R_RegisterShaderNoMip("gfx/hud/ic_stamina");
  tmp_i7 = 0;
  GHIDRA_FIELD(cgs, 131764, 4) = trap_R_RegisterShaderNoMip("gfx/hud/ic_health");
  GHIDRA_FIELD(cgs, 131700, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/weaponcard01");
  GHIDRA_FIELD(cgs, 131704, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/weaponcard02");
  GHIDRA_FIELD(cgs, 131708, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/weap_dnarrow.tga");
  GHIDRA_FIELD(cgs, 131712, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/objective_back_axis");
  GHIDRA_FIELD(cgs, 131716, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/objective_back_allied");
  GHIDRA_FIELD(cgs, 131720, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/objective_back");
  GHIDRA_FIELD(cgs, 131724, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/lightup_bar");
  GHIDRA_FIELD(cgs, 131728, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/but_play_on");
  GHIDRA_FIELD(cgs, 131732, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/but_play_off");
  GHIDRA_FIELD(cgs, 131736, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/but_stop_on");
  GHIDRA_FIELD(cgs, 131740, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/but_stop_off");
  GHIDRA_FIELD(cgs, 131744, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/spectator");
  GHIDRA_FIELD(cgs, 131748, 4) = trap_R_RegisterShaderNoMip("ui/assets/radio_tower");
  GHIDRA_FIELD(cgs, 131752, 4) = trap_R_RegisterShaderNoMip("ui/assets/3_cursor3");
  GHIDRA_FIELD(cgs, 131828, 4) = trap_R_RegisterSkin("models/players/hud/damagedskins/blood01.skin");
  GHIDRA_FIELD(cgs, 131832, 4) = trap_R_RegisterSkin("models/players/hud/damagedskins/blood02.skin");
  GHIDRA_FIELD(cgs, 131836, 4) = trap_R_RegisterSkin("models/players/hud/damagedskins/blood03.skin");
  GHIDRA_FIELD(cgs, 131840, 4) = trap_R_RegisterSkin("models/players/hud/damagedskins/blood04.skin");
  GHIDRA_FIELD(cgs, 131848, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/flag_axis");
  GHIDRA_FIELD(cgs, 131852, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/flag_allied");
  GHIDRA_FIELD(cgs, 131856, 4) = trap_R_RegisterShaderNoMip("gfx/2d/net");
  GHIDRA_FIELD(cgs, 131900, 4) = trap_R_RegisterShaderNoMip("gfx/misc/overlay");
  GHIDRA_FIELD(cgs, 131912, 4) = trap_R_RegisterShader("textures/sfx/transgunWhite");
  GHIDRA_FIELD(cgs, 131916, 4) = trap_R_RegisterShader("textures/sfx/transgunRed");
  GHIDRA_FIELD(cgs, 131920, 4) = trap_R_RegisterShader("textures/sfx/transgunGreen");
  GHIDRA_FIELD(cgs, 131924, 4) = trap_R_RegisterShader("textures/sfx/transgunBlue");
  do {
    tmp_u4 = va("gfx/awards/%i",tmp_i7);
    tmp_u4 = trap_R_RegisterShaderNoMip(tmp_u4);
    *(uint32_t *)(cgs + tmp_i7 * 4 + 0x20358) = tmp_u4;
    tmp_i7 = tmp_i7 + 1;
  } while (tmp_i7 != 0x10);
  tmp_i7 = 6;
  GHIDRA_FIELD(cgs, 131992, 4) = trap_R_RegisterShaderNoMip("gfx/2d/objArrow");
  GHIDRA_FIELD(cgs, 132392, 4) = trap_R_RegisterShaderNoMip("ui/assets/portraits/allies_win_flag.tga");
  GHIDRA_FIELD(cgs, 132396, 4) = trap_R_RegisterShaderNoMip("ui/assets/portraits/text_allies.tga");
  GHIDRA_FIELD(cgs, 132400, 4) = trap_R_RegisterShaderNoMip("ui/assets/portraits/axis_win_flag.tga");
  GHIDRA_FIELD(cgs, 132404, 4) = trap_R_RegisterShaderNoMip("ui/assets/portraits/text_axis.tga");
  GHIDRA_FIELD(cgs, 132408, 4) = trap_R_RegisterShaderNoMip("ui/assets/portraits/text_win.tga");
  do {
    tmp_u4 = va("gfx/hud/fireteam/fireteam%i",tmp_i7);
    tmp_u4 = trap_R_RegisterShaderNoMip(tmp_u4);
    *(uint32_t *)(cgs + tmp_i7 * 4 + 0x20310) = tmp_u4;
    tmp_i7 = tmp_i7 + -1;
  } while (tmp_i7 != 0);
  GHIDRA_FIELD(cgs, 132412, 4) = trap_R_RegisterShaderNoMip("gfx/hr/hr");
  GHIDRA_FIELD(cgs, 132416, 4) = trap_R_RegisterShaderNoMip("gfx/hr/head");
  GHIDRA_FIELD(cgs, 132420, 4) = trap_R_RegisterShaderNoMip("gfx/hr/rarm");
  GHIDRA_FIELD(cgs, 132424, 4) = trap_R_RegisterShaderNoMip("gfx/hr/larm");
  GHIDRA_FIELD(cgs, 132428, 4) = trap_R_RegisterShaderNoMip("gfx/hr/torso");
  GHIDRA_FIELD(cgs, 132432, 4) = trap_R_RegisterShaderNoMip("gfx/hr/legs");
  CG_LoadingString(":game media done:");
  CG_InitFlameChunks();
  if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
    tmp_i7 = 0x2b1;
    tmp_i8 = 0;
LAB_00095f30:
    if (tmp_pu14[*(int *)(cgs + tmp_i7 * 4) + 0x1000] == '\0') {
      if ((int)GHIDRA_FIELD(cgs, 27400, 4) <= tmp_i8 + 1) goto LAB_00095f91;
    }
    else {
      CG_NewClientInfo(tmp_i8,tmp_pu14 + *(int *)(cgs + tmp_i7 * 4) + 0x1000);
      if ((int)GHIDRA_FIELD(cgs, 27400, 4) <= tmp_i8 + 1) goto LAB_00095f91;
    }
    tmp_i8 = tmp_i8 + 1;
    tmp_i7 = tmp_i7 + 1;
    if (tmp_i7 == 0x400) {
      CG_Error_constprop_3("CG_ConfigString: bad index: %i",0x400);
    }
    goto LAB_00095f30;
  }
LAB_00095f91:
  g_unk_01047af0 = 0;
  CG_InitLocalEntities();
  BG_BuildSplinePaths();
  CG_InitMarkPolys();
  g_unk_01091a7c = 0;
  CG_SetConfigValues();
  local_568 = tmp_pu14 + GHIDRA_FIELD(cgs, 8, 4) + 0x1000;
  tmp_u4 = COM_Parse(tmp_ppu18);
  Q_strncpyz(pfVar17,tmp_u4,0x40);
  tmp_u4 = COM_Parse(tmp_ppu18);
  Q_strncpyz(local_41c,tmp_u4,0x40);
  if (GHIDRA_FIELD(local_55c, 0, 1) != '\0') {
    trap_S_StartBackgroundTrack(pfVar17,local_41c,0);
  }
  g_unk_01092cfc = 0;
  CG_LoadingString(&g_unk_0011d841);
  trap_S_ClearLoopingSounds();
  trap_S_ClearSounds(0);
  g_unk_010aabf4 = strtol(tmp_pu14 + GHIDRA_FIELD(cgs, 92, 4) + 0x1000,(char **)0x0,10);
  g_unk_010aabf0 = strtol(tmp_pu14 + GHIDRA_FIELD(cgs, 96, 4) + 0x1000,(char **)0x0,10);
  CG_ParseFireteams();
  CG_ParseOIDInfos();
  CG_InitPM();
  CG_ParseSpawns();
  CG_ParseTagConnects();
  CG_ParseSkyBox();
  CG_SetupCabinets();
  trap_S_FadeAllSound(0x3f800000,0,0);
  GHIDRA_FIELD(cgs, 33576008, 4) = 0;
  GHIDRA_FIELD(cgs, 33576016, 4) = 0;
  g_unk_01093560 = 0xffffffff;
  g_unk_010aabd0 = 0xffffffff;
  CG_LoadLocations();
  CG_ParseInfo();
  CG_UpdateSvCvars();
  tmp_u12 = g_unk_010bde48 == 0;
  if (0 < g_unk_010bde48) {
    tmp_pc3 = "server forcing cvar %s to %s\n";
    g_unk_010b5e44 = 1;
    tmp_pu9 = &g_unk_010b5e48;
    tmp_i8 = 0;
    tmp_i7 = 0xf09e7c;
    do {
      tmp_u5 = 0;
      do {
        tmp_pc11 = local_41c + tmp_u5;
        tmp_pc11[0] = '\0';
        tmp_pc11[1] = '\0';
        tmp_pc11[2] = '\0';
        tmp_pc11[3] = '\0';
        *(uint32_t *)((int)auStack_418 + tmp_u5) = 0;
        tmp_u5 = tmp_u5 + 8;
      } while (tmp_u5 < 0x80);
      trap_Cvar_VariableStringBuffer(tmp_pu9,local_41c,0x80);
      tmp_pc11 = tmp_pu9 + 0x100;
      tmp_i6 = strcmp(tmp_pc11,local_41c);
      if (tmp_i6 != 0) {
        CG_Printf(tmp_pc3,tmp_pu9,tmp_pc11);
        trap_Cvar_Register(0,tmp_pu9,tmp_pc11,0);
        trap_Cvar_Set(tmp_pu9,tmp_pc11);
      }
      tmp_i8 = tmp_i8 + 1;
      tmp_pu9 = tmp_pu9 + 0x200;
      tmp_u12 = *(int *)(tmp_i7 + 0x1b3fcc) == tmp_i8;
    } while (!(bool)tmp_u12 && tmp_i8 <= *(int *)(tmp_i7 + 0x1b3fcc));
  }
  CG_RestoreProfile();
  tmp_pc3 = (char *)BindingFromName("weapalt");
  tmp_i7 = 10;
  tmp_pc11 = "[weapalt]";
  do {
    if (tmp_i7 == 0) break;
    tmp_i7 = tmp_i7 + -1;
    tmp_u12 = *tmp_pc3 == *tmp_pc11;
    tmp_pc3 = tmp_pc3 + (uint)tmp_b13 * -2 + 1;
    tmp_pc11 = tmp_pc11 + (uint)tmp_b13 * -2 + 1;
  } while ((bool)tmp_u12);
  if (!(bool)tmp_u12) {
    tmp_u4 = BindingFromName("weapalt");
    tmp_u4 = va("bind %s +attack2\n",tmp_u4);
    trap_SendConsoleCommand(tmp_u4);
  }
  nitmod_ClientCheck();
  GHIDRA_FIELD(cgs, 33823048, 4) = 0;
  return;
}

uint vmMain(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
           uint32_t param_5,uint32_t param_6)

{
  uint tmp_u1;
  
  switch(param_1) {
  case 0:
    EnableStackTrace();
    CG_Init(param_2,param_3,param_4,param_5,param_6);
    GHIDRA_FIELD(cgs, 33703444, 4) = 0;
    tmp_u1 = 0;
    break;
  case 1:
    nitrox_TCPSend(&g_unk_00118bb6);
    nitrox_FreeScreenshot();
    nitrox_TCPClose();
    CG_EventHandling(0,1);
    if (g_unk_01047aec != 0) {
      trap_Cvar_Set("timescale",&g_unk_0011e9db);
    }
    if (g_unk_010eecc8 != 0) {
      trap_FS_FCloseFile(g_unk_010eecc8);
      g_unk_010eecc8 = 0;
    }
    DisableStackTrace();
    tmp_u1 = 0;
    break;
  case 2:
    tmp_u1 = CG_ConsoleCommand();
    break;
  case 3:
    CG_DrawActiveFrame(param_2,param_3,param_4);
    tmp_u1 = 0;
    break;
  case 4:
    tmp_u1 = 0xffffffff;
    if (g_unk_010906e0 <= g_unk_0109355c + 1000) {
      tmp_u1 = g_unk_01093558;
    }
    break;
  case 5:
  case 0xc:
    tmp_u1 = 0xffffffff;
    break;
  case 6:
    CG_KeyEvent(param_2,param_3);
    tmp_u1 = 0;
    break;
  case 7:
    g_unk_010261a4 = GHIDRA_FIELD(cgs, 67776, 4);
    g_unk_010261a8 = GHIDRA_FIELD(cgs, 67780, 4);
    CG_MouseEvent(param_2,param_3);
    tmp_u1 = 0;
    break;
  case 8:
    CG_EventHandling(param_2,1);
    tmp_u1 = 0;
    break;
  case 9:
    tmp_u1 = CG_GetTag(param_2,param_3,param_4);
    break;
  case 10:
    tmp_u1 = 0;
    if (g_unk_010abd7c != 0) {
      tmp_u1 = CG_FireteamCheckExecKey(param_2,0);
    }
    break;
  case 0xb:
    tmp_u1 = 0;
    if (g_waitingForKey != 0) {
      tmp_u1 = (uint)(g_bindItem != 0);
    }
    break;
  default:
    CG_Error("vmMain: unknown command %li",param_1);
    tmp_u1 = 0xffffffff;
  }
  return tmp_u1;
}

void CG_CheckExecKey(uint32_t param_1)
{
  if (g_unk_010abd7c != 0) {
    CG_FireteamCheckExecKey(param_1,0);
  }
  return;
}

uint32_t CG_GetGameModel(int param_1)
{
  return *(uint32_t *)(cgs + param_1 * 4 + 0x6f48);
}

void CG_GetRealTime(void)
{
  uint8_t *tmp_pu1;
  uint8_t *tmp_pu2;
  int local_30;
  int local_2c;
  uint32_t local_28;
  uint32_t uStack_c;
  
  uStack_c = 0x970b7;
  trap_RealTime(&local_30);
  if (local_30 < 10) {
    tmp_pu1 = &g_unk_0011e957;
  }
  else {
    tmp_pu1 = &g_unk_0011d841;
  }
  if (local_2c < 10) {
    tmp_pu2 = &g_unk_0011e957;
  }
  else {
    tmp_pu2 = &g_unk_0011d841;
  }
  va(&g_unk_00118c81,local_28,tmp_pu2,local_2c,tmp_pu1,local_30);
  return;
}

void CG_WriteToLog(char *param_1)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  uint tmp_u3;
  uint8_t *tmp_pu4;
  int tmp_i5;
  uint *tmp_pu6;
  uint *tmp_pu7;
  uint8_t *tmp_pu8;
  char acStack_40f [3];
  uint local_40c [256];
  
  if (g_unk_010eecc8 != 0) {
    trap_RealTime(local_40c);
    if ((int)local_40c[0] < 10) {
      tmp_pu8 = &g_unk_0011e957;
    }
    else {
      tmp_pu8 = &g_unk_0011d841;
    }
    if ((int)local_40c[1] < 10) {
      tmp_pu4 = &g_unk_0011e957;
    }
    else {
      tmp_pu4 = &g_unk_0011d841;
    }
    tmp_u1 = va(&g_unk_00118c81,local_40c[2],tmp_pu4,local_40c[1],tmp_pu8,local_40c[0]);
    Com_sprintf(local_40c,0x400,&g_unk_00120aeb,tmp_u1);
    tmp_pu7 = local_40c;
    do {
      tmp_pu6 = tmp_pu7;
      tmp_u2 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
      tmp_u3 = tmp_u2 & 0x80808080;
      tmp_pu7 = tmp_pu6 + 1;
    } while (tmp_u3 == 0);
    if ((tmp_u2 & 0x8080) == 0) {
      tmp_pu7 = (uint *)((int)tmp_pu6 + 6);
      tmp_u3 = tmp_u3 >> 0x10;
    }
    tmp_i5 = (int)tmp_pu7 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_40c);
    vsnprintf((char *)(tmp_i5 + (int)local_40c),0x400 - tmp_i5,param_1,&stack0x00000008);
    tmp_pu7 = local_40c;
    do {
      tmp_pu6 = tmp_pu7;
      tmp_u2 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
      tmp_u3 = tmp_u2 & 0x80808080;
      tmp_pu7 = tmp_pu6 + 1;
    } while (tmp_u3 == 0);
    if ((tmp_u2 & 0x8080) == 0) {
      tmp_pu7 = (uint *)((int)tmp_pu6 + 6);
      tmp_u3 = tmp_u3 >> 0x10;
    }
    trap_FS_Write(local_40c,
                  (int)tmp_pu7 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_40c),
                  g_unk_010eecc8);
  }
  return;
}

void CG_FreeMarkPoly(int *param_1)
{
  int tmp_i1;
  
  tmp_i1 = *param_1;
  if (tmp_i1 == 0) {
    CG_Error("CG_FreeLocalEntity: not active");
    tmp_i1 = *param_1;
  }
  *(int *)(tmp_i1 + 4) = param_1[1];
  *(int *)param_1[1] = *param_1;
  tmp_i1 = (int)cg_freeMarkPolys;
  cg_freeMarkPolys = param_1;
  param_1[1] = tmp_i1;
  return;
}

int * CG_AllocMark(void)
{
  int tmp_i1;
  int *tmp_pi2;
  uint tmp_u3;
  int tmp_i4;
  int *tmp_pi5;
  uint tmp_u6;
  uint32_t *tmp_pu7;
  int *tmp_pi8;
  int *tmp_pi9;
  bool tmp_b10;
  
  if (cg_freeMarkPolys == (int *)0x0) {
    tmp_i1 = cg_activeMarkPolys[2];
    tmp_pi8 = cg_activeMarkPolys;
    do {
      tmp_pi9 = tmp_pi8;
      tmp_i4 = *tmp_pi9;
      if (tmp_i4 == 0) {
        CG_Error("CG_FreeLocalEntity: not active");
        tmp_i4 = *tmp_pi9;
      }
      *(int *)(tmp_i4 + 4) = tmp_pi9[1];
      *(int *)tmp_pi9[1] = *tmp_pi9;
      tmp_pi8 = cg_activeMarkPolys;
      tmp_pi5 = cg_freeMarkPolys;
      tmp_b10 = cg_activeMarkPolys != (int *)0x0;
      tmp_pi2 = tmp_pi9;
      tmp_pi9[1] = (int)cg_freeMarkPolys;
      cg_freeMarkPolys = tmp_pi2;
    } while ((tmp_b10) && (tmp_pi8[2] == tmp_i1));
  }
  else {
    tmp_pi5 = (int *)cg_freeMarkPolys[1];
    tmp_pi9 = cg_freeMarkPolys;
  }
  tmp_b10 = ((uint)tmp_pi9 & 1) != 0;
  tmp_u6 = 0x124;
  tmp_pi8 = tmp_pi9;
  cg_freeMarkPolys = tmp_pi5;
  if (tmp_b10) {
    tmp_u6 = 0x123;
    *(uint8_t *)tmp_pi9 = 0;
    tmp_pi8 = (int *)((int)tmp_pi9 + 1);
  }
  if (((uint)tmp_pi8 & 2) != 0) {
    *(uint16_t *)tmp_pi8 = 0;
    tmp_u6 = tmp_u6 - 2;
    tmp_pi8 = (int *)((int)tmp_pi8 + 2);
  }
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)tmp_pi8 + tmp_u3) = 0;
    *(uint32_t *)((int)tmp_pi8 + tmp_u3 + 4) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < (tmp_u6 & 0xfffffff8));
  tmp_pu7 = (uint32_t *)((int)tmp_pi8 + tmp_u3);
  if ((tmp_u6 & 4) != 0) {
    *tmp_pu7 = 0;
    tmp_pu7 = tmp_pu7 + 1;
  }
  if ((tmp_u6 & 2) != 0) {
    *(uint16_t *)tmp_pu7 = 0;
    tmp_pu7 = (uint32_t *)((int)tmp_pu7 + 2);
  }
  if (tmp_b10) {
    *(uint8_t *)tmp_pu7 = 0;
  }
  tmp_pi9[1] = (int)g_unk_03404da4;
  *tmp_pi9 = (int)&cg_activeMarkPolys;
  *g_unk_03404da4 = (int)tmp_pi9;
  g_unk_03404da4 = tmp_pi9;
  return tmp_pi9;
}

void CG_ImpactMark(uint32_t param_1,float *param_2,float *param_3,float param_4,float param_5,
                  uint32_t param_6,uint32_t param_7,uint32_t param_8,uint32_t param_9,
                  int param_10)

{
  uint32_t local_80;
  uint32_t local_7c;
  uint32_t local_78;
  uint32_t local_74;
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
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  if (param_10 != 0) {
    local_70 = *param_3;
    local_6c = param_3[1];
    local_68 = param_3[2];
    PerpendicularVector(&local_64,&local_70);
    RotatePointAroundVector(&local_58,&local_70,&local_64,-param_5);
    CrossProduct(&local_70,&local_58,&local_64);
    local_38 = (param_2[2] - local_68) - param_4 * local_5c;
    local_50 = param_4 * local_50;
    local_44 = local_38 - local_50;
    local_38 = local_38 + local_50;
    local_20 = (param_2[2] - local_68) + param_4 * local_5c;
    local_2c = local_50 + local_20;
    local_20 = local_20 - local_50;
    local_3c = (param_2[1] - local_6c) - param_4 * local_60;
    local_54 = param_4 * local_54;
    local_48 = local_3c - local_54;
    local_3c = local_3c + local_54;
    local_24 = (param_2[1] - local_6c) + param_4 * local_60;
    local_30 = local_54 + local_24;
    local_24 = local_24 - local_54;
    local_40 = (*param_2 - local_70) - param_4 * local_64;
    local_58 = param_4 * local_58;
    local_4c = local_40 - local_58;
    local_40 = local_40 + local_58;
    local_28 = param_4 * local_64 + (*param_2 - local_70);
    local_34 = local_58 + local_28;
    local_28 = local_28 - local_58;
    local_80 = param_6;
    local_7c = param_7;
    local_78 = param_8;
    local_74 = param_9;
    trap_R_ProjectDecal(param_1,4,&local_4c,param_3,&local_80,param_10,param_10 >> 4);
  }
  return;
}

uint32_t CG_DescriptionForCampaign(void)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 0x30e90c0;
  if (GHIDRA_FIELD(cgs, 33526364, 4) == 0) {
    tmp_u1 = 0;
  }
  return tmp_u1;
}

uint32_t CG_NameForCampaign(void)
{
  uint32_t tmp_u1;
  
  tmp_u1 = 0x30e98c0;
  if (GHIDRA_FIELD(cgs, 33526364, 4) == 0) {
    tmp_u1 = 0;
  }
  return tmp_u1;
}

uint32_t CG_FindCampaignInFile(uint32_t param_1,uint32_t param_2,int param_3)
{
  bool tmp_b1;
  bool tmp_b2;
  char tmp_c3;
  int tmp_i4;
  int tmp_i5;
  uint32_t tmp_u6;
  char *tmp_pc7;
  char *tmp_pc9;
  char local_4b4 [128];
  uint8_t local_434 [12];
  float local_428;
  char local_424;
  char local_423 [1043];
  char *tmp_pc8;
  
  *(uint32_t *)(param_3 + 0xb0a0) = 0;
  tmp_i4 = trap_PC_LoadSource(param_1);
  if (tmp_i4 == 0) {
    tmp_u6 = va("^1file not found: %s\n",param_1);
    trap_Print(tmp_u6);
    return 0;
  }
  tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
  if ((tmp_i5 == 0) || (tmp_b2 = false, local_424 != '{')) {
LAB_00097c40:
    trap_PC_FreeSource(tmp_i4);
  }
  else {
LAB_00097bd0:
    do {
      tmp_b1 = tmp_b2;
      tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
      while( true ) {
        if (tmp_i5 == 0) goto LAB_00097c40;
        if (local_424 != '}') break;
        if (tmp_b1) {
          trap_PC_FreeSource(tmp_i4);
          return 1;
        }
        tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
        if (tmp_i5 == 0) goto LAB_00097c40;
        if (local_424 != '{') {
          tmp_u6 = va("^1unexpected token \'%s\' inside: %s\n",&local_424,param_1);
          goto LAB_00097d09;
        }
        *(uint32_t *)(param_3 + 0xb0a0) = 0;
        tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
      }
      tmp_pc9 = &local_424;
      tmp_i5 = Q_stricmp(tmp_pc9,"shortname");
      tmp_b2 = tmp_b1;
      if (tmp_i5 == 0) {
        tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
        if (tmp_i5 == 0) break;
        tmp_i5 = Q_stricmp(tmp_pc9,param_2);
        tmp_b2 = true;
        if (tmp_i5 != 0) {
          tmp_b2 = tmp_b1;
        }
        goto LAB_00097bd0;
      }
      tmp_i5 = Q_stricmp(tmp_pc9,"next");
      if ((tmp_i5 != 0) && (tmp_i5 = Q_stricmp(tmp_pc9,"image"), tmp_i5 != 0)) {
        tmp_i5 = Q_stricmp(tmp_pc9,"description");
        if (tmp_i5 == 0) {
          tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
          if (tmp_i5 == 0) break;
          Q_strncpyz(param_3,tmp_pc9,0x800);
        }
        else {
          tmp_i5 = Q_stricmp(tmp_pc9,"name");
          if (tmp_i5 == 0) {
            tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
            if (tmp_i5 == 0) break;
            Q_strncpyz(param_3 + 0x800,tmp_pc9,0x80);
          }
          else {
            tmp_i5 = Q_stricmp(tmp_pc9,"maps");
            if (tmp_i5 == 0) {
              tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
              if (tmp_i5 == 0) break;
              tmp_c3 = local_424;
              while (tmp_c3 != '\0') {
                tmp_pc8 = local_4b4;
                tmp_pc7 = local_4b4;
                if (tmp_c3 == ';') {
LAB_00097ec0:
                  tmp_pc9 = tmp_pc9 + 1;
                }
                else {
                  do {
                    tmp_pc7 = tmp_pc8 + 1;
                    tmp_pc9 = tmp_pc9 + 1;
                    *tmp_pc8 = tmp_c3;
                    tmp_c3 = *tmp_pc9;
                    if (tmp_c3 == ';') break;
                    tmp_pc8 = tmp_pc7;
                  } while (tmp_c3 != '\0');
                  if (tmp_c3 != '\0') goto LAB_00097ec0;
                }
                tmp_i5 = *(int *)(param_3 + 0xb0a0);
                *tmp_pc7 = '\0';
                if (9 < tmp_i5) {
                  tmp_u6 = va("^1too many maps for a campaign inside: %s\n",param_1);
                  trap_Print(tmp_u6);
                  trap_PC_FreeSource(tmp_i4);
                  break;
                }
                *(int *)(param_3 + 0xb0a0) = tmp_i5 + 1;
                Q_strncpyz((tmp_i5 + 0x22) * 0x40 + param_3,local_4b4,0x40);
                tmp_c3 = *tmp_pc9;
              }
            }
            else {
              tmp_i5 = Q_stricmp(tmp_pc9,"maptc");
              if (tmp_i5 == 0) {
                tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
                if (tmp_i5 == 0) break;
                *(float *)(param_3 + 0xb0a8) = local_428;
                tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
                if (tmp_i5 == 0) break;
                *(float *)(param_3 + 0xb0ac) = local_428;
                *(float *)(param_3 + 0xb0b0) = *(float *)(param_3 + 0xb0a8) + 650.0;
                *(float *)(param_3 + 0xb0b4) = local_428 + 650.0;
              }
            }
          }
        }
        goto LAB_00097bd0;
      }
      tmp_i5 = trap_PC_ReadToken(tmp_i4,local_434);
    } while (tmp_i5 != 0);
    tmp_u6 = va("^1unexpected end of file inside: %s\n",param_1);
LAB_00097d09:
    trap_Print(tmp_u6);
    trap_PC_FreeSource(tmp_i4);
  }
  return 0;
}

uint32_t CG_FindArenaInfo(uint32_t param_1,uint32_t param_2,int param_3)
{
  bool tmp_b1;
  bool tmp_b2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  uint32_t local_438;
  uint8_t local_434 [12];
  uint32_t local_428;
  char local_424 [1044];
  
  tmp_i3 = trap_PC_LoadSource(param_1);
  if (tmp_i3 == 0) {
    tmp_u5 = va("^1file not found: %s\n",param_1);
    trap_Print(tmp_u5);
    return 0;
  }
  tmp_i4 = trap_PC_ReadToken(tmp_i3,local_434);
  if ((tmp_i4 == 0) || (tmp_b2 = false, local_424[0] != '{')) {
LAB_000980b0:
    trap_PC_FreeSource(tmp_i3);
  }
  else {
LAB_00098040:
    while( true ) {
      tmp_b1 = tmp_b2;
      tmp_i4 = trap_PC_ReadToken(tmp_i3,local_434);
      if (tmp_i4 == 0) goto LAB_000980b0;
      tmp_b2 = tmp_b1;
      if (local_424[0] != '}') break;
      if (tmp_b1) {
        trap_PC_FreeSource(tmp_i3);
        return 1;
      }
      tmp_i4 = trap_PC_ReadToken(tmp_i3,local_434);
      if (tmp_i4 == 0) goto LAB_000980b0;
      if (local_424[0] != '{') {
        tmp_u5 = va("^1unexpected token \'%s\' inside: %s\n",local_424,param_1);
LAB_0009809b:
        trap_Print(tmp_u5);
        trap_PC_FreeSource(tmp_i3);
        return 0;
      }
    }
    tmp_i4 = Q_stricmp(local_424,"objectives");
    if (((tmp_i4 == 0) || (tmp_i4 = Q_stricmp(local_424,"description"), tmp_i4 == 0)) ||
       (tmp_i4 = Q_stricmp(local_424,"type"), tmp_i4 == 0)) {
      tmp_i4 = PC_String_Parse(tmp_i3,&local_438);
      if (tmp_i4 == 0) goto LAB_0009811a;
      goto LAB_00098040;
    }
    tmp_i4 = Q_stricmp(local_424,"longname");
    if (tmp_i4 == 0) {
      tmp_i4 = PC_String_Parse(tmp_i3,&local_438);
      if (tmp_i4 == 0) goto LAB_0009811a;
      Q_strncpyz(param_3 + 0x1000,local_438,0x80);
      goto LAB_00098040;
    }
    tmp_i4 = Q_stricmp(local_424,"map");
    if (tmp_i4 == 0) {
      tmp_i4 = PC_String_Parse(tmp_i3,&local_438);
      if (tmp_i4 == 0) goto LAB_0009811a;
      tmp_i4 = Q_stricmp(local_438,param_2);
      tmp_b2 = true;
      if (tmp_i4 != 0) {
        tmp_b2 = tmp_b1;
      }
      goto LAB_00098040;
    }
    tmp_i4 = Q_stricmp(local_424,"Timelimit");
    if (((tmp_i4 != 0) && (tmp_i4 = Q_stricmp(local_424,"AxisRespawnTime"), tmp_i4 != 0)) &&
       (tmp_i4 = Q_stricmp(local_424,"AlliedRespawnTime"), tmp_i4 != 0)) {
      tmp_i4 = Q_stricmp(local_424,"lmsbriefing");
      if (tmp_i4 == 0) {
        tmp_i4 = PC_String_Parse(tmp_i3,&local_438);
        if (tmp_i4 == 0) goto LAB_0009811a;
        Q_strncpyz(param_3,local_438,0x400);
      }
      else {
        tmp_i4 = Q_stricmp(local_424,"briefing");
        if (tmp_i4 == 0) {
          tmp_i4 = PC_String_Parse(tmp_i3,&local_438);
          if (tmp_i4 == 0) goto LAB_0009811a;
          Q_strncpyz(param_3 + 0x400,local_438,0x400);
        }
        else {
          tmp_i4 = Q_stricmp(local_424,"alliedwintext");
          if (tmp_i4 != 0) {
            tmp_i4 = Q_stricmp(local_424,"axiswintext");
            if (tmp_i4 == 0) {
              tmp_i4 = PC_String_Parse(tmp_i3,&local_438);
              if (tmp_i4 == 0) goto LAB_0009811a;
              Q_strncpyz(param_3 + 0x800,local_438,0x400);
              goto LAB_00098040;
            }
            tmp_i4 = Q_stricmp(local_424,"mapposition_x");
            if (tmp_i4 == 0) {
              tmp_i4 = trap_PC_ReadToken(tmp_i3,local_434);
              if (tmp_i4 != 0) {
                *(uint32_t *)(param_3 + 0x1080) = local_428;
                goto LAB_00098040;
              }
            }
            else {
              tmp_i4 = Q_stricmp(local_424,"mapposition_y");
              if (tmp_i4 != 0) goto LAB_00098040;
              tmp_i4 = trap_PC_ReadToken(tmp_i3,local_434);
              if (tmp_i4 != 0) {
                *(uint32_t *)(param_3 + 0x1084) = local_428;
                goto LAB_00098040;
              }
            }
            tmp_u5 = va("^1unexpected end of file inside: %s\n",param_1);
            goto LAB_0009809b;
          }
          tmp_i4 = PC_String_Parse(tmp_i3,&local_438);
          if (tmp_i4 == 0) goto LAB_0009811a;
          Q_strncpyz(param_3 + 0xc00,local_438,0x400);
        }
      }
      goto LAB_00098040;
    }
    tmp_i4 = PC_Int_Parse(tmp_i3,&local_438);
    if (tmp_i4 != 0) goto LAB_00098040;
LAB_0009811a:
    tmp_u5 = va("^1unexpected end of file inside: %s\n",param_1);
    trap_Print(tmp_u5);
    trap_PC_FreeSource(tmp_i3);
  }
  return 0;
}

void CG_LocateCampaign(void)
{
  int tmp_i1;
  size_t tmp_s2;
  int tmp_i3;
  int tmp_i4;
  char *__s;
  int local_470;
  uint8_t local_45c [64];
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x984de;
  __s = local_41c;
  tmp_i1 = trap_FS_GetFileList("scripts",".campaign",__s,0x400);
  if (0 < tmp_i1) {
    tmp_i4 = 0;
    while( true ) {
      tmp_s2 = strlen(__s);
      Q_strncpyz(local_45c,"scripts/",0x40);
      Q_strcat(local_45c,0x40,__s);
      tmp_i3 = CG_FindCampaignInFile(local_45c,0x30e8cd0,0x30e90c0);
      if (tmp_i3 != 0) break;
      tmp_i4 = tmp_i4 + 1;
      __s = __s + tmp_s2 + 1;
      if (tmp_i4 == tmp_i1) {
        return;
      }
    }
    if ((int)GHIDRA_FIELD(cgs, 33571584, 4) < 1) {
      GHIDRA_FIELD(cgs, 33526364, 4) = 1;
      return;
    }
    local_470 = 0x30e9c10;
    tmp_i4 = 0;
    tmp_i1 = 0x30e9940;
    while( true ) {
      Com_sprintf(local_45c,0x40,"scripts/%s.arena",tmp_i1);
      tmp_i3 = CG_FindArenaInfo(local_45c,tmp_i1,local_470);
      if (tmp_i3 == 0) break;
      tmp_i1 = tmp_i1 + 0x40;
      local_470 = local_470 + 0x1088;
      tmp_i4 = tmp_i4 + 1;
      if ((int)GHIDRA_FIELD(cgs, 33571584, 4) <= tmp_i4) {
        GHIDRA_FIELD(cgs, 33526364, 4) = 1;
        return;
      }
    }
  }
  return;
}

void CG_LocateArena(void)
{
  int tmp_i1;
  uint8_t local_5c [76];
  
  Com_sprintf(local_5c,0x40,"scripts/%s.arena",0x10f69ac);
  tmp_i1 = CG_FindArenaInfo(local_5c,0x10f69ac,0x30f417c);
  if (tmp_i1 != 0) {
    GHIDRA_FIELD(cgs, 33571608, 4) = 1;
  }
  return;
}

void CG_FitTextToWidth_Ext
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
      tmp_i4 = CG_Text_Width_Ext(param_1,param_2,0,param_5);
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

long double CG_GetValue(void)
{
  return -(long double)1;
}

void CG_MouseEvent(int param_1,int param_2)
{
  uint tmp_u1;
  
  if (GHIDRA_FIELD(cgs, 67784, 4) == 4) {
    GHIDRA_FIELD(cgs, 67776, 4) = param_1 + GHIDRA_FIELD(cgs, 67776, 4);
    if ((int)GHIDRA_FIELD(cgs, 67776, 4) < 0) {
      GHIDRA_FIELD(cgs, 67776, 4) = 0;
    }
    else if (0x280 < (int)GHIDRA_FIELD(cgs, 67776, 4)) {
      GHIDRA_FIELD(cgs, 67776, 4) = 0x280;
    }
    GHIDRA_FIELD(cgs, 67780, 4) = param_2 + GHIDRA_FIELD(cgs, 67780, 4);
    if ((int)GHIDRA_FIELD(cgs, 67780, 4) < 0) {
      GHIDRA_FIELD(cgs, 67780, 4) = 0;
    }
    else if (0x1e0 < (int)GHIDRA_FIELD(cgs, 67780, 4)) {
      GHIDRA_FIELD(cgs, 67780, 4) = 0x1e0;
    }
    if (param_1 == 0 && param_2 == 0) {
      return;
    }
    GHIDRA_FIELD(cgs, 33576004, 4) = g_unk_010906e0 + 5000;
    return;
  }
  if ((int)GHIDRA_FIELD(cgs, 67784, 4) < 5) {
    if ((int)GHIDRA_FIELD(cgs, 67784, 4) < 1) {
LAB_0009943d:
      if (*(int *)(g_unk_01047b00 + 0x30) == 5) {
        CG_Debriefing_MouseEvent(param_1,param_2);
        return;
      }
      if ((g_unk_01090700 & 0xfffffffd) != 0) {
        return;
      }
      if (g_unk_010928a4 != 0) {
        return;
      }
      tmp_u1 = trap_Key_GetCatcher();
      trap_Key_SetCatcher(tmp_u1 & 0xfffffff7);
      return;
    }
  }
  else if (GHIDRA_FIELD(cgs, 67784, 4) != 5) goto LAB_0009943d;
  GHIDRA_FIELD(cgs, 67776, 4) = param_1 + GHIDRA_FIELD(cgs, 67776, 4);
  if ((int)GHIDRA_FIELD(cgs, 67776, 4) < 0) {
    GHIDRA_FIELD(cgs, 67776, 4) = 0;
  }
  else if (0x280 < (int)GHIDRA_FIELD(cgs, 67776, 4)) {
    GHIDRA_FIELD(cgs, 67776, 4) = 0x280;
  }
  GHIDRA_FIELD(cgs, 67780, 4) = param_2 + GHIDRA_FIELD(cgs, 67780, 4);
  if ((int)GHIDRA_FIELD(cgs, 67780, 4) < 0) {
    GHIDRA_FIELD(cgs, 67780, 4) = 0;
  }
  else if (0x1e0 < (int)GHIDRA_FIELD(cgs, 67780, 4)) {
    GHIDRA_FIELD(cgs, 67780, 4) = 0x1e0;
  }
  if (GHIDRA_FIELD(cgs, 67784, 4) == 2) {
    CG_SpeakerEditorMouseMove_Handling(param_1,param_2);
  }
  return;
}

void CG_EventHandling(int param_1,int param_2)
{
  uint tmp_u1;
  
  if (((g_unk_01047aec == 0) || (param_1 != 0)) || (param_2 != 0)) {
    if ((param_1 != 0) && (trap_Cvar_Set("cl_bypassMouseInput",0), param_1 == 4)) goto LAB_000995c3;
    if (GHIDRA_FIELD(cgs, 67784, 4) != 1) {
      if (GHIDRA_FIELD(cgs, 67784, 4) == 2) {
        if (param_1 == -2) {
          GHIDRA_FIELD(cgs, 67784, 4) = 0;
          goto LAB_000996f9;
        }
        goto LAB_000995fd;
      }
      if (GHIDRA_FIELD(cgs, 67784, 4) != 3) {
        if (GHIDRA_FIELD(cgs, 67784, 4) == 5) {
          g_unk_010abd7c = 0;
          trap_Cvar_Set("cl_bypassmouseinput",&g_unk_0011e957);
        }
        else if (((g_unk_01047b00 != 0) && (param_2 != 0)) && (*(int *)(g_unk_01047b00 + 0x30) == 5)) {
          trap_UI_Popup(2);
        }
        goto LAB_00099680;
      }
      GHIDRA_FIELD(cgs, 67784, 4) = 1;
      goto LAB_000995f0;
    }
    g_unk_010abd78 = 0;
    trap_S_StopStreamingSound(0xffffffff);
    g_unk_010b3b28 = 0;
    if ((param_2 != 0) && (GHIDRA_FIELD(cgs, 33701712, 4) != 0)) {
      trap_SendClientCommand("rs");
      GHIDRA_FIELD(cgs, 33701708, 4) = 0;
    }
LAB_00099680:
    GHIDRA_FIELD(cgs, 67784, 4) = param_1;
    if (param_1 == 0) {
LAB_000996f9:
      tmp_u1 = trap_Key_GetCatcher();
      trap_Key_SetCatcher(tmp_u1 & 0xfffffff7);
      ccInitial = 0;
      if (g_unk_01047aec == 0) {
        ccInitial = 0;
        return;
      }
      if (g_unk_010afbc8 == 0) {
        ccInitial = 0;
        return;
      }
      CG_ShowHelp_Off(&g_unk_010afbc8);
      return;
    }
    if (param_1 != 1) {
      if (param_1 == 5) {
        GHIDRA_FIELD(cgs, 33701696, 4) = 0xffffffff;
        GHIDRA_FIELD(cgs, 33701700, 4) = 0;
        g_unk_010abd7c = 1;
        trap_Cvar_Set("cl_bypassmouseinput",&g_unk_0011e9db);
        trap_Key_SetCatcher(8);
        return;
      }
      goto LAB_000995fd;
    }
  }
  else {
    trap_Cvar_Set("cl_bypassMouseInput",0);
LAB_000995c3:
    GHIDRA_FIELD(cgs, 33576004, 4) = g_unk_010906e0 + 10000;
    GHIDRA_FIELD(cgs, 33599876, 4) = g_unk_010906e0 + 4000;
    CG_ScoresUp_f();
    GHIDRA_FIELD(cgs, 67784, 4) = 4;
LAB_000995f0:
    if (GHIDRA_FIELD(cgs, 67784, 4) != 1) goto LAB_000995fd;
  }
  g_unk_010abd78 = 1;
  CG_LimboPanel_Setup();
LAB_000995fd:
  trap_Key_SetCatcher(8);
  return;
}

void CG_KeyEvent(uint32_t param_1,int param_2)
{
  switch(GHIDRA_FIELD(cgs, 67784, 4)) {
  default:
    if (*(int *)(g_unk_01047b00 + 0x30) == 5) {
      CG_Debriefing_KeyEvent(param_1,param_2);
    }
    else if ((param_2 != 0) && ((g_unk_01090700 == 0 || ((g_unk_01090700 == 2 && (g_unk_010928a4 == 0)))))
            ) {
      CG_EventHandling();
      return;
    }
    break;
  case 1:
    CG_LimboPanel_KeyHandling(param_1,param_2);
    return;
  case 2:
    CG_SpeakerEditor_KeyHandling(param_1,param_2);
    return;
  case 3:
    CG_LoadPanel_KeyHandling(param_1,param_2);
    return;
  case 4:
    CG_DemoClick(param_1,param_2);
    return;
  case 5:
    CG_Fireteams_KeyHandling(param_1,param_2);
  }
  return;
}

int CG_ClientNumFromName(uint32_t param_1)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i2 = 0;
  tmp_i3 = 0x10f9274;
  tmp_i1 = GHIDRA_FIELD(cgs, 27400, 4);
  if (0 < (int)GHIDRA_FIELD(cgs, 27400, 4)) {
    do {
      while (*(int *)(tmp_i3 + -8) == 0) {
        tmp_i2 = tmp_i2 + 1;
        tmp_i3 = tmp_i3 + 0x1a4;
        if (tmp_i1 <= tmp_i2) {
          return -1;
        }
      }
      tmp_i1 = Q_stricmp(tmp_i3,param_1);
      if (tmp_i1 == 0) {
        return tmp_i2;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_i3 = tmp_i3 + 0x1a4;
      tmp_i1 = GHIDRA_FIELD(cgs, 27400, 4);
    } while (tmp_i2 < (int)GHIDRA_FIELD(cgs, 27400, 4));
  }
  return -1;
}

void CG_GetTeamColor(uint32_t *param_1)
{
  if (*(int *)(g_unk_01047b00 + 0x158) == 1) {
    *param_1 = 0x3f800000;
    param_1[3] = 0x3e800000;
    param_1[2] = 0;
    param_1[1] = 0;
    return;
  }
  if (*(int *)(g_unk_01047b00 + 0x158) != 2) {
    param_1[2] = 0;
    *param_1 = 0;
    param_1[1] = 0x3e2e147b;
    param_1[3] = 0x3e800000;
    return;
  }
  param_1[1] = 0;
  *param_1 = 0;
  param_1[2] = 0x3f800000;
  param_1[3] = 0x3e800000;
  return;
}

void CG_ParticleBubble_part_0
          (int param_1,float *param_2,int param_3,int param_4,float param_5,uint32_t param_6)

{
  float tmp_f1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint tmp_u5;
  uint32_t tmp_u6;
  uint local_3c;
  
  if (param_1 == 0) {
    CG_Printf("CG_ParticleSnow pshader == ZERO!\n");
  }
  tmp_pu3 = free_particles;
  if (free_particles != (uint32_t *)0x0) {
    tmp_pu4 = (uint32_t *)*free_particles;
    *free_particles = active_particles;
    free_particles = tmp_pu4;
    active_particles = tmp_pu3;
    tmp_f1 = (float)g_unk_010906e0;
    tmp_pu3[0xc] = 0;
    tmp_pu3[0xe] = 0x3ecccccd;
    tmp_pu3[0xf] = 0;
    tmp_pu3[1] = tmp_f1;
    tmp_pu3[0x16] = param_2[2];
    tmp_u6 = *(uint32_t *)(param_3 + 8);
    tmp_pu3[0x11] = param_1;
    tmp_pu3[0x17] = tmp_u6;
    tmp_u5 = rand();
    tmp_f1 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
    tmp_f1 = (tmp_f1 + tmp_f1) * 0.5 + 1.0;
    tmp_pu3[0x12] = tmp_f1;
    tmp_pu3[0x13] = tmp_f1;
    local_3c = rand();
    if (param_4 == 0) {
      local_3c = local_3c & 0x7fff;
      tmp_u6 = 0xd;
      tmp_f1 = (float)local_3c / 32767.0 - 0.5;
      tmp_pu3[8] = (tmp_f1 + tmp_f1) * 10.0 + 50.0;
    }
    else {
      tmp_pu3[8] = 0x42820000;
      tmp_u6 = 0xe;
    }
    tmp_pu3[0x10] = tmp_u6;
    tmp_f1 = *param_2;
    tmp_pu3[3] = tmp_f1;
    tmp_pu3[4] = param_2[1];
    tmp_pu3[5] = param_2[2];
    tmp_u5 = rand();
    tmp_f2 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu3[3] = tmp_f1 + (tmp_f2 + tmp_f2) * param_5;
    tmp_f1 = (float)tmp_pu3[4];
    tmp_u5 = rand();
    tmp_f2 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu3[4] = param_5 * (tmp_f2 + tmp_f2) + tmp_f1;
    tmp_f1 = (float)tmp_pu3[5];
    tmp_u5 = rand();
    tmp_f2 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
    tmp_pu3[5] = ((float)tmp_pu3[0x16] - (float)tmp_pu3[0x17]) * (tmp_f2 + tmp_f2) + tmp_f1;
    tmp_pu3[7] = 0;
    tmp_pu3[6] = 0;
    tmp_pu3[0xb] = 0;
    tmp_pu3[10] = 0;
    tmp_pu3[9] = 0;
    if (param_4 != 0) {
      local_3c = rand();
      local_3c = local_3c & 0x7fff;
      tmp_f1 = (float)local_3c / 32767.0 - 0.5;
      tmp_pu3[6] = (tmp_f1 + tmp_f1) * 4.0;
      tmp_u5 = rand();
      tmp_f1 = (float)(tmp_u5 & 0x7fff) / 32767.0 - 0.5;
      tmp_pu3[7] = (tmp_f1 + tmp_f1) * 4.0;
    }
    tmp_pu3[0x1b] = 1;
    tmp_pu3[0x1a] = param_6;
  }
  return;
}

void CG_ClearParticles(void)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  char *tmp_pc7;
  uint32_t *tmp_pu8;
  int local_24;
  
  memset(particles,0,0xf8000);
  free_particles = particles;
  active_particles = 0;
  tmp_i1 = cl_numparticles + -1;
  if (cl_numparticles != 0) {
    tmp_pu2 = particles + cl_numparticles * 0x7c;
    do {
      *(uint32_t *)(tmp_pu2 + -0x3c) = 0;
      *(uint8_t **)(tmp_pu2 + -0x7c) = tmp_pu2;
      tmp_pu2 = tmp_pu2 + -0x7c;
    } while (tmp_pu2 != particles);
  }
  *(uint32_t *)(particles + tmp_i1 * 0x7c) = 0;
  tmp_pu8 = &shaderAnims;
  tmp_pc7 = "explode1";
  oldtime = (float)g_unk_010906e0;
  local_24 = 0;
  do {
    tmp_i3 = local_24 * 4;
    tmp_i1 = *(int *)(shaderAnimCounts + tmp_i3);
    if (0 < tmp_i1) {
      tmp_i5 = 0;
      do {
        tmp_i6 = tmp_i5 + 1;
        tmp_u4 = va(&g_unk_00118c8a,tmp_pc7,tmp_i6);
        tmp_u4 = trap_R_RegisterShader(tmp_u4);
        tmp_pu8[tmp_i5] = tmp_u4;
        tmp_i5 = tmp_i6;
      } while (tmp_i6 != tmp_i1);
    }
    tmp_pu8 = tmp_pu8 + 0x40;
    local_24 = local_24 + 1;
    tmp_pc7 = *(char **)(shaderAnimNames + tmp_i3 + 4);
  } while (tmp_pc7 != (char *)0x0);
  initparticles = 1;
  numShaderAnims = local_24;
  return;
}

uint32_t CG_NewParticleArea(uint32_t param_1)
{
  float *pfVar1;
  char *tmp_pc2;
  long tmp_l3;
  long tmp_l4;
  long tmp_l5;
  int tmp_i6;
  double tmp_d7;
  uint32_t local_48;
  char *local_38;
  float local_34 [9];
  
  local_38 = (char *)CG_ConfigString(param_1);
  if (*local_38 != '\0') {
    tmp_pc2 = (char *)COM_Parse(&local_38);
    tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    if (tmp_l3 == 1) {
      local_48 = 0x43000000;
    }
    else if (tmp_l3 == 2) {
      local_48 = 0x42800000;
    }
    else if (tmp_l3 == 3) {
      local_48 = 0x42000000;
    }
    else if (tmp_l3 == 0) {
      local_48 = 0x43800000;
    }
    else if (tmp_l3 == 4) {
      local_48 = 0x41000000;
    }
    else if (tmp_l3 == 5) {
      local_48 = 0x41800000;
    }
    else if (tmp_l3 == 6) {
      local_48 = 0x42000000;
    }
    else if (tmp_l3 == 7) {
      local_48 = 0x42800000;
    }
    else {
      local_48 = 0;
    }
    pfVar1 = local_34 + 3;
    tmp_i6 = 0;
    do {
      tmp_pc2 = (char *)COM_Parse(&local_38);
      tmp_d7 = strtod(tmp_pc2,(char **)0x0);
      local_34[tmp_i6] = (float)tmp_d7;
      tmp_d7 = strtod(tmp_pc2,(char **)0x0);
      pfVar1[tmp_i6] = (float)tmp_d7;
      tmp_i6 = tmp_i6 + 1;
    } while (tmp_i6 != 3);
    tmp_pc2 = (char *)COM_Parse(&local_38);
    tmp_i6 = strtol(tmp_pc2,(char **)0x0,10);
    tmp_pc2 = (char *)COM_Parse(&local_38);
    tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
    tmp_pc2 = (char *)COM_Parse(&local_38);
    tmp_l5 = strtol(tmp_pc2,(char **)0x0,10);
    if (tmp_l3 < 4) {
      for (; tmp_i6 != 0; tmp_i6 = tmp_i6 + -1) {
        CG_ParticleSnow(GHIDRA_FIELD(cgs, 68512, 4),local_34,pfVar1,tmp_l4,local_48,tmp_l5);
      }
    }
    else {
      for (; tmp_i6 != 0; tmp_i6 = tmp_i6 + -1) {
        if (GHIDRA_FIELD(cg_trailparticles, 12, 4) != 0) {
          CG_ParticleBubble_part_0(pfVar1,tmp_l4,local_48,tmp_l5);
        }
      }
    }
    return 1;
  }
  return 0;
}

void CG_SnowLink(int param_1,int param_2)
{
  int tmp_i1;
  uint tmp_u2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint32_t *tmp_pu5;
  
  tmp_i1 = *(int *)(param_1 + 0xb0);
  if (active_particles != (uint32_t *)0x0) {
    tmp_pu5 = active_particles;
    if (param_2 == 0) {
      tmp_u2 = active_particles[0x10];
      tmp_pu3 = (uint32_t *)*active_particles;
      while( true ) {
        tmp_pu4 = tmp_pu3;
        if (((tmp_u2 & 0xfffffffb) == 1) && (tmp_pu5[0x1a] == tmp_i1)) {
          tmp_pu5[0x1b] = 0;
        }
        if (tmp_pu4 == (uint32_t *)0x0) break;
        tmp_u2 = tmp_pu4[0x10];
        tmp_pu3 = (uint32_t *)*tmp_pu4;
        tmp_pu5 = tmp_pu4;
      }
    }
    else {
      do {
        tmp_pu3 = (uint32_t *)*tmp_pu5;
        if (((tmp_pu5[0x10] & 0xfffffffb) == 1) && (tmp_pu5[0x1a] == tmp_i1)) {
          tmp_pu5[0x1b] = 1;
        }
        tmp_pu5 = tmp_pu3;
      } while (tmp_pu3 != (uint32_t *)0x0);
    }
  }
  return;
}

void CG_ParticleImpactSmokePuffExtended
               (int param_1,uint32_t *param_2,int param_3,int param_4,int param_5,int param_6,
               uint32_t param_7,float param_8)

{
  uint32_t tmp_u1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  uint tmp_u5;
  
  if (GHIDRA_FIELD(cg_smokeparticles, 12, 4) != 0) {
    tmp_pu3 = free_particles;
    if (param_1 == 0) {
      CG_Printf("CG_ParticleImpactSmokePuff pshader == ZERO!\n");
      tmp_pu3 = free_particles;
    }
    free_particles = tmp_pu3;
    if (tmp_pu3 != (uint32_t *)0x0) {
      free_particles = (uint32_t *)*tmp_pu3;
      *tmp_pu3 = active_particles;
      tmp_f2 = (float)g_unk_010906e0;
      tmp_pu3[0xf] = 0;
      active_particles = tmp_pu3;
      tmp_pu3[1] = tmp_f2;
      tmp_pu3[0xe] = param_7;
      tmp_i4 = rand();
      tmp_pu3[0x1d] = tmp_i4 % (param_6 * 2) - param_6;
      tmp_pu3[0x11] = param_1;
      tmp_pu3[2] = (float)(param_3 + g_unk_010906e0);
      tmp_pu3[0x18] = (float)(g_unk_010906e0 + 100);
      tmp_u5 = rand();
      tmp_pu3[0x13] = (((float)(tmp_u5 & 0x7fff) / 32767.0) * 0.5 + 1.0) * param_8;
      tmp_u5 = rand();
      param_8 = (((float)(tmp_u5 & 0x7fff) / 32767.0) * 0.5 + 1.0) * param_8;
      tmp_pu3[0x10] = 0xc;
      tmp_pu3[0x12] = param_8;
      tmp_pu3[0x14] = param_8 + param_8;
      tmp_pu3[0x15] = (float)tmp_pu3[0x13] + (float)tmp_pu3[0x13];
      tmp_pu3[3] = *param_2;
      tmp_pu3[4] = param_2[1];
      tmp_u1 = param_2[2];
      tmp_pu3[6] = 0;
      tmp_pu3[5] = tmp_u1;
      tmp_pu3[7] = 0;
      tmp_pu3[9] = 0;
      tmp_pu3[10] = 0;
      tmp_pu3[0x19] = 1;
      tmp_pu3[8] = (float)param_4;
      tmp_pu3[0xb] = (float)param_5;
    }
  }
  return;
}

void CG_OilSlickRemove(int param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  int tmp_i3;
  int *tmp_pi4;
  
  tmp_i1 = *(int *)(param_1 + 0xf4);
  tmp_i3 = g_unk_010906e0;
  tmp_pi4 = active_particles;
  if (tmp_i1 == 0) {
    CG_Printf("CG_OilSlickRevove NULL id\n");
    tmp_i3 = g_unk_010906e0;
    tmp_pi4 = active_particles;
  }
  do {
    if (tmp_pi4 == (int *)0x0) {
      g_unk_010906e0 = tmp_i3;
      return;
    }
    while ((tmp_pi2 = (int *)*tmp_pi4, tmp_pi4[0x10] != 9 || (tmp_pi4[0x1a] != tmp_i1))) {
      tmp_pi4 = tmp_pi2;
      if (tmp_pi2 == (int *)0x0) {
        g_unk_010906e0 = tmp_i3;
        return;
      }
    }
    g_unk_010906e0 = tmp_i3;
    tmp_pi4[0x10] = 10;
    tmp_pi4[2] = (int)(float)(tmp_i3 + 100);
    tmp_pi4[0x18] = (int)(float)(tmp_i3 + 100);
    tmp_i3 = g_unk_010906e0;
    tmp_pi4 = tmp_pi2;
  } while( true );
}

void CG_SwingAngles(float *param_1,int *param_2,float param_3,float param_4,float param_5,float param_6)
{
  int tmp_i1;
  long double tmp_l2;
  long double tmp_l3;
  
  if (*param_2 == 0) {
    tmp_l2 = (long double)AngleSubtract(param_3,*param_1);
    if (((long double)param_4 <= tmp_l2) || (tmp_l2 < -(long double)param_4)) {
      *param_2 = 1;
    }
    else if (*param_2 == 0) {
      return;
    }
  }
  tmp_l2 = (long double)AngleSubtract(param_3,*param_1);
  tmp_l3 = (long double)0.5;
  if ((long double)0.5 <= (long double)(float)((long double)0.05 * ABS(tmp_l2))) {
    tmp_l3 = (long double)(float)((long double)0.05 * ABS(tmp_l2));
  }
  if (tmp_l2 < (long double)0) {
    if ((long double)0 <= tmp_l2) {
      tmp_l2 = (long double)*param_1;
      goto LAB_0009f2fe;
    }
    tmp_i1 = 0;
    tmp_l3 = -(long double)param_6 * (long double)g_unk_010906dc * tmp_l3;
    if (tmp_l2 < tmp_l3) {
      tmp_i1 = 1;
      tmp_l2 = tmp_l3;
    }
  }
  else {
    tmp_i1 = 0;
    tmp_l3 = (long double)g_unk_010906dc * tmp_l3 * (long double)param_6;
    if (tmp_l3 < tmp_l2) {
      tmp_i1 = 2;
      tmp_l2 = tmp_l3;
    }
  }
  *param_2 = tmp_i1;
  tmp_l2 = (long double)AngleMod((float)(tmp_l2 + (long double)*param_1));
  *param_1 = (float)tmp_l2;
LAB_0009f2fe:
  tmp_l2 = (long double)AngleSubtract(param_3,(float)tmp_l2);
  if ((long double)param_5 < tmp_l2) {
    tmp_l2 = (long double)
            AngleMod((float)((long double)param_3 - ((long double)param_5 - (long double)1)));
    *param_1 = (float)tmp_l2;
  }
  else if (tmp_l2 < -(long double)param_5) {
    tmp_l2 = (long double)AngleMod((param_5 - 1.0) + param_3);
    *param_1 = (float)tmp_l2;
    return;
  }
  return;
}

bool CG_EntOnFire(int *param_1)
{
  int tmp_i1;
  bool tmp_b2;
  
  if ((*param_1 == *(int *)(g_unk_01047b00 + 0xcc)) && (param_1[1] != 0x26)) {
    tmp_i1 = *(int *)(g_unk_01047b00 + 0x450);
    tmp_b2 = false;
    if ((tmp_i1 != 0) && (tmp_i1 < g_unk_010906e0)) {
      tmp_b2 = g_unk_010906e0 <= tmp_i1 + 1999;
    }
  }
  else {
    tmp_b2 = false;
    if (param_1[0x3f] < g_unk_010906e0) {
      tmp_b2 = g_unk_010906e0 < param_1[0x40];
    }
  }
  return tmp_b2;
}

bool CG_IsCrouchingAnim(uint32_t param_1,uint param_2)
{
  int tmp_i1;
  
  tmp_i1 = BG_GetAnimationForIndex(param_1,param_2 & 0xfffffdff);
  return (*(byte *)(tmp_i1 + 0x6c) & 100) != 0;
}

void CG_RunLerpFrame(uint32_t param_1,int param_2,uint32_t *param_3,uint param_4,float param_5)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint tmp_u7;
  int local_30;
  int local_2c;
  
  if (GHIDRA_FIELD(cg_animSpeed, 12, 4) == 0) {
    param_3[6] = 0;
    param_3[3] = 0;
    *param_3 = 0;
    return;
  }
  if ((param_2 == 0) ||
     (((param_3[0xb] == param_4 && (param_3[0xd] != 0)) ||
      (tmp_i4 = CG_CharacterForClientinfo(param_2,param_1), tmp_i4 == 0)))) {
LAB_0009f79b:
    tmp_i6 = param_3[4];
  }
  else {
    tmp_u7 = param_4 & 0xfffffdff;
    param_3[0xb] = param_4;
    if (((int)tmp_u7 < 0) || (tmp_i5 = *(int *)(tmp_i4 + 0x7f0), *(int *)(tmp_i5 + 0x89c) <= (int)tmp_u7)
       ) {
      CG_Error("CG_SetLerpFrameAnimation: Bad animation number: %i",tmp_u7);
      tmp_i5 = *(int *)(tmp_i4 + 0x7f0);
    }
    tmp_i5 = *(int *)(tmp_i5 + 0xc + (tmp_u7 + 0x24) * 4);
    tmp_i6 = param_3[4];
    param_3[0xd] = tmp_i5;
    tmp_u3 = GHIDRA_FIELD(cg_debugAnim, 12, 4);
    param_3[0xe] = *(int *)(tmp_i5 + 0x54) + tmp_i6;
    if (tmp_u3 != 0) {
      CG_Printf("Anim: %i, %s\n",tmp_u7,
                *(int *)(*(int *)(tmp_i4 + 0x7f0) + 0xc + (tmp_u7 + 0x24) * 4) + 4);
      goto LAB_0009f79b;
    }
  }
  if (tmp_i6 <= g_unk_010906e0) {
    tmp_pu1 = (uint32_t *)param_3[0xd];
    param_3[1] = tmp_i6;
    *param_3 = param_3[3];
    param_3[2] = param_3[5];
    if (tmp_pu1[0x14] == 0) {
      return;
    }
    tmp_i4 = param_3[0xe];
    local_2c = 0;
    local_30 = tmp_i4;
    if (tmp_i4 <= g_unk_010906e0) {
      local_30 = tmp_pu1[0x14] + tmp_i6;
      local_2c = local_30 - tmp_i4;
    }
    param_3[4] = local_30;
    tmp_i4 = (int)ROUND((float)(local_2c / (int)tmp_pu1[0x14]) * param_5);
    tmp_i5 = tmp_pu1[0x12];
    if (tmp_i5 <= tmp_i4) {
      tmp_i2 = tmp_pu1[0x13];
      if (tmp_i2 == 0) {
        local_30 = g_unk_010906e0;
        tmp_i4 = tmp_i5 + -1;
        param_3[4] = g_unk_010906e0;
      }
      else {
        tmp_i4 = (tmp_i5 - tmp_i2) + (tmp_i4 - tmp_i5) % tmp_i2;
      }
    }
    param_3[3] = tmp_i4 + tmp_pu1[0x11];
    param_3[5] = *tmp_pu1;
    tmp_i4 = g_unk_010906e0;
    if ((g_unk_010906e0 <= local_30) ||
       (param_3[4] = g_unk_010906e0, local_30 = tmp_i4, GHIDRA_FIELD(cg_debugAnim, 12, 4) == 0)) goto LAB_0009f8c3;
    CG_Printf("Clamp lf->frameTime\n");
    tmp_i6 = param_3[4];
  }
  local_30 = tmp_i6;
  tmp_i6 = param_3[1];
LAB_0009f8c3:
  tmp_i4 = g_unk_010906e0;
  if (g_unk_010906e0 + 200 < local_30) {
    param_3[4] = g_unk_010906e0;
    local_30 = tmp_i4;
  }
  tmp_i4 = g_unk_010906e0;
  if (g_unk_010906e0 < tmp_i6) {
    param_3[1] = g_unk_010906e0;
    tmp_i6 = tmp_i4;
  }
  if (local_30 == tmp_i6) {
    param_3[6] = 0;
  }
  else {
    param_3[6] = 1.0 - (float)(g_unk_010906e0 - tmp_i6) / (float)(local_30 - tmp_i6);
  }
  return;
}

void CG_SetLerpFrameAnimationRate(int param_1,uint32_t param_2,int param_3,uint param_4)
{
  uint tmp_u1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  int tmp_i5;
  int local_28;
  
  tmp_i4 = CG_CharacterForClientinfo(param_2,param_1);
  if (tmp_i4 == 0) {
    return;
  }
  tmp_u1 = *(uint *)(param_3 + 0x2c);
  *(uint *)(param_3 + 0x2c) = param_4;
  param_4 = param_4 & 0xfffffdff;
  tmp_i2 = *(int *)(param_3 + 0x34);
  if (((int)param_4 < 0) ||
     (tmp_i5 = *(int *)(tmp_i4 + 0x7f0), *(int *)(tmp_i5 + 0x89c) <= (int)param_4)) {
    CG_Error("CG_SetLerpFrameAnimationRate: Bad animation number: %i",param_4);
    tmp_i5 = *(int *)(tmp_i4 + 0x7f0);
  }
  tmp_pu3 = *(uint32_t **)(tmp_i5 + 0xc + (param_4 + 0x24) * 4);
  local_28 = *(int *)(param_3 + 0x10);
  *(uint32_t **)(param_3 + 0x34) = tmp_pu3;
  *(int *)(param_3 + 0x38) = tmp_pu3[0x15] + local_28;
  if (((*(byte *)(tmp_pu3 + 0x1a) & 2) != 0) && (param_3 == param_1 + 700)) goto LAB_0009fa7b;
  if (param_3 == param_1 + 0x268) {
    tmp_i5 = BG_GetAnimationForIndex(*(uint32_t *)(tmp_i4 + 0x7f0),param_4);
    if ((*(byte *)(tmp_i5 + 0x6c) & 100) == 0) {
      tmp_i5 = BG_GetAnimationForIndex(*(uint32_t *)(tmp_i4 + 0x7f0),tmp_u1 & 0xfffffdff);
      if ((*(byte *)(tmp_i5 + 0x6c) & 100) == 0) {
LAB_0009fc1d:
        local_28 = *(int *)(param_1 + 0x278);
        goto LAB_0009fa48;
      }
    }
    else {
      tmp_i5 = BG_GetAnimationForIndex(*(uint32_t *)(tmp_i4 + 0x7f0),tmp_u1 & 0xfffffdff);
      if ((*(byte *)(tmp_i5 + 0x6c) & 100) != 0) goto LAB_0009fc1d;
    }
    if (tmp_pu3[0x16] == 0) {
      if ((tmp_pu3[0x1b] & 0x6000) == 0) {
        local_28 = *(int *)(param_1 + 0x278) + 0x15e;
        goto LAB_0009fa5c;
      }
      local_28 = *(int *)(param_1 + 0x278) + 200;
      if (tmp_i2 == 0) goto LAB_0009fa6b;
    }
    else {
      local_28 = *(int *)(param_1 + 0x278) + 200;
      if (tmp_i2 == 0) goto LAB_0009fb9b;
    }
    tmp_i5 = *(int *)(tmp_i2 + 0x5c);
    if (tmp_i5 == 0) {
      if (tmp_pu3[0x16] != 0) goto LAB_0009fb9b;
LAB_0009fa6b:
      tmp_i5 = *(int *)(param_3 + 0x38);
LAB_0009fa6e:
      if (tmp_i5 < local_28) {
        *(int *)(param_3 + 0x38) = local_28;
      }
      goto LAB_0009fa7b;
    }
  }
  else {
LAB_0009fa48:
    if (tmp_pu3[0x16] == 0) {
      local_28 = local_28 + 0xaa;
LAB_0009fa5c:
      if ((tmp_i2 == 0) || (tmp_i5 = *(int *)(tmp_i2 + 0x5c), tmp_i5 == 0)) goto LAB_0009fa6b;
    }
    else {
      local_28 = local_28 + 0x78;
      if ((tmp_i2 == 0) || (tmp_i5 = *(int *)(tmp_i2 + 0x5c), tmp_i5 == 0)) {
LAB_0009fb9b:
        if (1.0 <= *(float *)(param_3 + 0x4c)) goto LAB_0009fa6b;
        tmp_i5 = tmp_pu3[0x15] + *(int *)(param_3 + 0x38);
        *(int *)(param_3 + 0x38) = tmp_i5;
        goto LAB_0009fa6e;
      }
    }
  }
  *(int *)(param_3 + 0x38) = tmp_i5 + *(int *)(param_3 + 0x10);
LAB_0009fa7b:
  if (tmp_i2 == 0) {
    *(int *)(param_3 + 0x10) = g_unk_010906e0 + -1;
    *(int *)(param_3 + 0x38) = g_unk_010906e0 + -1;
    *(uint32_t *)(param_3 + 0xc) = tmp_pu3[0x11];
    *(uint32_t *)(param_3 + 0x14) = *tmp_pu3;
  }
  if (GHIDRA_FIELD(cg_debugAnim, 12, 4) == 1) {
    CG_Printf("Anim: %i, %s\n",param_4,
              *(int *)(*(int *)(tmp_i4 + 0x7f0) + 0xc + (param_4 + 0x24) * 4) + 4);
  }
  return;
}

void CG_RunLerpFrameRate_part_2(uint32_t param_1,int *param_2,int param_3,int *param_4,int param_5)
{
  float tmp_f1;
  int *tmp_pi2;
  uint tmp_u3;
  int *tmp_pi4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  bool tmp_b8;
  long double tmp_l9;
  int local_38;
  uint local_34;
  
  tmp_pi2 = (int *)param_2[0xd];
  tmp_b8 = false;
  if (tmp_pi2 == (int *)0x0) {
    local_34 = 0;
LAB_0009ff96:
    CG_SetLerpFrameAnimationRate(param_4,param_1,param_2,param_3);
    tmp_i7 = param_4[1];
    tmp_pi4 = (int *)param_2[0xd];
  }
  else {
    local_34 = tmp_pi2[0x1a] & 1;
    tmp_b8 = local_34 != 0;
    if (tmp_b8) {
      local_34 = 1;
    }
    if (param_2[0xb] != param_3) goto LAB_0009ff96;
    tmp_i7 = param_4[1];
    tmp_pi4 = tmp_pi2;
  }
  if (tmp_i7 == 0x26) {
    tmp_i7 = tmp_pi4[0x12] + tmp_pi4[0x11] + -1;
    param_2[3] = tmp_i7;
    *param_2 = tmp_i7;
    tmp_i7 = *tmp_pi4;
    param_2[6] = 0;
    param_2[5] = tmp_i7;
    param_2[2] = tmp_i7;
    return;
  }
  if ((tmp_pi4[0x16] == 0) || (param_2[0x14] == 0)) {
    tmp_f1 = 1.0;
    param_2[0x13] = 0x3f800000;
    param_2[0x14] = g_unk_01047afc;
  }
  else if ((param_2[0x14] == g_unk_01047afc) || (g_unk_01047b04 == 0)) {
    tmp_f1 = (float)param_2[0x13];
  }
  else {
    if (*param_4 == *(int *)(g_unk_01047b00 + 0xcc)) {
      if (local_34 == 0) {
        param_2[0x12] = param_4[0x1e7];
      }
      else {
        param_2[0x10] = param_4[0x1e5];
        param_2[0x11] = param_4[0x1e6];
      }
    }
    else if (local_34 != 0) {
      param_2[0x10] = param_4[6];
      param_2[0x11] = param_4[7];
    }
    tmp_l9 = (long double)Distance(param_4 + 0x1e5,param_2 + 0x10);
    tmp_i6 = g_unk_010906e0 - param_2[1];
    tmp_i7 = tmp_pi4[0x16];
    param_2[0x14] = g_unk_01047afc;
    tmp_f1 = (float)(tmp_l9 / ((long double)tmp_i6 / (long double)1000.0)) / (float)tmp_i7;
    param_2[0x13] = (int)tmp_f1;
  }
  tmp_i7 = param_2[4];
  tmp_f1 = tmp_f1 * (float)param_4[0x1d0];
  param_2[0x13] = (int)tmp_f1;
  if (g_unk_010906e0 < tmp_i7) goto LAB_0009ff32;
  tmp_i6 = param_2[3];
  param_2[1] = tmp_i7;
  *param_2 = tmp_i6;
  param_2[2] = param_2[5];
  param_2[0x10] = param_4[0x1e5];
  param_2[0x11] = param_4[0x1e6];
  param_2[0x12] = param_4[0x1e7];
  if (0.25 <= tmp_f1) {
    if (1.1 < tmp_f1) {
      if ((*(byte *)(tmp_pi4 + 0x1a) & 1) == 0) {
        tmp_i5 = tmp_pi4[0x16];
        if (tmp_i5 < 0x65) {
          if (tmp_i5 < 0x14) {
            if (1.6 < tmp_f1) {
              param_2[0x13] = 0x3fcccccd;
              tmp_f1 = 1.6;
            }
          }
          else {
            tmp_f1 = 1.6 - ((float)(tmp_i5 + -0x14) * 0.5) / 80.0;
            param_2[0x13] = (int)tmp_f1;
          }
        }
        else {
          param_2[0x13] = 0x3f8ccccd;
          tmp_f1 = 1.1;
        }
      }
      else if (4.0 < tmp_f1) {
        param_2[0x13] = 0x40800000;
        tmp_f1 = 4.0;
      }
    }
  }
  else if ((0.01 <= tmp_f1) || (!tmp_b8)) {
    param_2[0x13] = 0x3e800000;
    tmp_f1 = 0.25;
  }
  else {
    param_2[0x13] = 0;
    tmp_f1 = 0.0;
  }
  if (param_2 == param_4 + 0x9a) {
    local_38 = param_4[0xbc];
  }
  else {
    local_38 = 0;
    if (param_2 == param_4 + 0xaf) {
      local_38 = param_4[0xa7];
    }
  }
  if (tmp_f1 == 0.0) {
    tmp_i5 = tmp_i6 - tmp_pi4[0x11];
    param_2[4] = tmp_i7 + tmp_pi4[0x14];
    tmp_i7 = tmp_pi4[0x12];
  }
  else {
    tmp_u3 = param_2[0xb];
    if ((param_2[0xc] == tmp_u3) ||
       (((tmp_pi4[0x16] != 0 && (tmp_pi4[0x11] <= tmp_i6)) && (tmp_i6 < tmp_pi4[0x11] + tmp_pi4[0x12]))))
    {
      if (local_38 != 0) {
        if (param_2 == param_4 + 0x9a) {
          if ((*(byte *)(tmp_pi4 + 0x1a) & 2) == 0) {
            if ((((tmp_u3 ^ param_4[0xba]) & 0xfffffdff) == 0) && (tmp_pi4[0x16] == 0)) {
              tmp_i5 = param_4[0xb2] - *(int *)(local_38 + 0x44);
              if ((tmp_pi4[0x12] <= tmp_i5) || (tmp_i5 < 0)) {
                tmp_i5 = 0;
              }
              param_2[4] = param_4[0xb3];
              goto LAB_000a02d0;
            }
            if (param_2 == param_4 + 0xaf) goto LAB_000a032c;
          }
        }
        else if ((param_2 == param_4 + 0xaf) && ((*(byte *)(tmp_pi4 + 0x1a) & 2) == 0)) {
LAB_000a032c:
          if ((((tmp_u3 ^ param_4[0xa5]) & 0xfffffdff) == 0) && (*(int *)(local_38 + 0x58) != 0)) {
            tmp_i5 = param_4[0x9d] - *(int *)(local_38 + 0x44);
            if ((tmp_pi4[0x12] <= tmp_i5) || (tmp_i5 < 0)) {
              tmp_i5 = 0;
            }
            param_2[4] = param_4[0x9e];
            tmp_i7 = tmp_pi4[0x12];
            goto LAB_0009feaa;
          }
        }
      }
      tmp_i7 = tmp_i7 + (int)ROUND((float)tmp_pi4[0x14] * (1.0 / tmp_f1));
      param_2[4] = tmp_i7;
      tmp_i5 = g_unk_010906e0;
      if (tmp_i7 < g_unk_010906e0) {
        param_2[4] = g_unk_010906e0;
        if ((*(byte *)(tmp_pi4 + 0x1a) & 4) == 0) {
          if ((g_unk_010906e0 <= tmp_i5) || (tmp_pi4[0x16] != 0)) goto LAB_000a0426;
          tmp_i5 = (tmp_i6 - tmp_pi4[0x11]) + 1 + (g_unk_010906e0 - tmp_i5) / tmp_pi4[0x14];
          tmp_i7 = tmp_pi4[0x12];
        }
        else {
          if ((g_unk_010906e0 <= tmp_i5) || (tmp_pi4[0x16] != 0)) goto LAB_000a0438;
          tmp_i7 = tmp_pi4[0x12];
          tmp_i5 = tmp_i7 + (tmp_pi4[0x11] - tmp_i6) + (g_unk_010906e0 - tmp_i5) / tmp_pi4[0x14];
        }
      }
      else if ((*(byte *)(tmp_pi4 + 0x1a) & 4) == 0) {
LAB_000a0426:
        tmp_i7 = tmp_pi4[0x12];
        tmp_i5 = (tmp_i6 - tmp_pi4[0x11]) + 1;
      }
      else {
LAB_000a0438:
        tmp_i7 = tmp_pi4[0x12];
        tmp_i5 = (tmp_i7 - tmp_i6) + tmp_pi4[0x11];
      }
      if (tmp_i5 < 0) {
        tmp_i5 = 0;
      }
    }
    else {
      param_2[4] = param_2[0xe];
      tmp_i5 = 0;
      if (tmp_pi2 == (int *)0x0) {
LAB_000a02d0:
        tmp_i7 = tmp_pi4[0x12];
      }
      else if (tmp_pi4[0x16] == 0) {
        tmp_i7 = tmp_pi4[0x12];
        tmp_i5 = 0;
      }
      else {
        tmp_i7 = tmp_pi4[0x12];
        for (tmp_i5 = (tmp_i6 - tmp_pi2[0x11]) + 1; (tmp_i5 < 0 && (tmp_i5 = tmp_i5 + tmp_i7, tmp_i5 < 0));
            tmp_i5 = tmp_i5 + tmp_i7) {
        }
      }
    }
  }
LAB_0009feaa:
  if (tmp_i7 <= tmp_i5) {
    tmp_i6 = tmp_pi4[0x13];
    if (tmp_i6 == 0) {
      tmp_i5 = tmp_i7 + -1;
      param_2[4] = g_unk_010906e0;
    }
    else {
      tmp_i5 = (tmp_i7 - tmp_i6) + (tmp_i5 - tmp_i7) % tmp_i6;
    }
  }
  if ((*(byte *)(tmp_pi4 + 0x1a) & 4) == 0) {
    param_2[3] = tmp_i5 + tmp_pi4[0x11];
    param_2[5] = *tmp_pi4;
  }
  else {
    param_2[3] = (tmp_pi4[0x12] + tmp_pi4[0x11] + -1) - tmp_i5;
    param_2[5] = *tmp_pi4;
  }
  tmp_i7 = param_2[4];
  if (tmp_i7 < g_unk_010906e0) {
    if (param_5 < 5) {
      if (GHIDRA_FIELD(cg_animSpeed, 12, 4) == 0) {
        param_2[6] = 0;
        param_2[3] = 0;
        *param_2 = 0;
      }
      else {
        CG_RunLerpFrameRate_part_2(param_3,param_4,param_5 + 1);
      }
    }
    else {
      param_2[4] = g_unk_010906e0;
    }
    if ((int)GHIDRA_FIELD(cg_debugAnim, 12, 4) < 4) {
      tmp_i7 = param_2[4];
    }
    else {
      CG_Printf("Clamp lf->frameTime\n");
      tmp_i7 = param_2[4];
    }
  }
  param_2[0xc] = param_2[0xb];
LAB_0009ff32:
  tmp_i6 = g_unk_010906e0;
  if (g_unk_010906e0 + 5000 < tmp_i7) {
    param_2[4] = g_unk_010906e0;
    tmp_i7 = tmp_i6;
  }
  tmp_i5 = g_unk_010906e0;
  tmp_i6 = param_2[1];
  if (g_unk_010906e0 < tmp_i6) {
    param_2[1] = g_unk_010906e0;
    tmp_i6 = tmp_i5;
  }
  if (tmp_i6 != tmp_i7) {
    param_2[6] = (int)(1.0 - (float)(g_unk_010906e0 - tmp_i6) / (float)(tmp_i7 - tmp_i6));
    return;
  }
  param_2[6] = 0;
  return;
}

void CG_RunLerpFrameRate(uint32_t param_1,int *param_2,int param_3,int *param_4,int param_5)
{
  float tmp_f1;
  int *tmp_pi2;
  uint tmp_u3;
  int *tmp_pi4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  bool tmp_b8;
  long double tmp_l9;
  int local_38;
  uint local_34;
  
  if (GHIDRA_FIELD(cg_animSpeed, 12, 4) == 0) {
    param_2[6] = 0;
    param_2[3] = 0;
    *param_2 = 0;
    return;
  }
  tmp_pi2 = (int *)param_2[0xd];
  tmp_b8 = false;
  if (tmp_pi2 == (int *)0x0) {
    local_34 = 0;
LAB_000a0866:
    CG_SetLerpFrameAnimationRate(param_4,param_1,param_2,param_3);
    tmp_i7 = param_4[1];
    tmp_pi4 = (int *)param_2[0xd];
  }
  else {
    local_34 = tmp_pi2[0x1a] & 1;
    tmp_b8 = local_34 != 0;
    if (tmp_b8) {
      local_34 = 1;
    }
    if (param_3 != param_2[0xb]) goto LAB_000a0866;
    tmp_i7 = param_4[1];
    tmp_pi4 = tmp_pi2;
  }
  if (tmp_i7 == 0x26) {
    tmp_i7 = tmp_pi4[0x12] + tmp_pi4[0x11] + -1;
    param_2[3] = tmp_i7;
    *param_2 = tmp_i7;
    tmp_i7 = *tmp_pi4;
    param_2[6] = 0;
    param_2[5] = tmp_i7;
    param_2[2] = tmp_i7;
    return;
  }
  if ((tmp_pi4[0x16] == 0) || (param_2[0x14] == 0)) {
    tmp_f1 = 1.0;
    param_2[0x13] = 0x3f800000;
    param_2[0x14] = g_unk_01047afc;
  }
  else if ((param_2[0x14] == g_unk_01047afc) || (g_unk_01047b04 == 0)) {
    tmp_f1 = (float)param_2[0x13];
  }
  else {
    if (*param_4 == *(int *)(g_unk_01047b00 + 0xcc)) {
      if (local_34 == 0) {
        param_2[0x12] = param_4[0x1e7];
      }
      else {
        param_2[0x10] = param_4[0x1e5];
        param_2[0x11] = param_4[0x1e6];
      }
    }
    else if (local_34 != 0) {
      param_2[0x10] = param_4[6];
      param_2[0x11] = param_4[7];
    }
    tmp_l9 = (long double)Distance(param_4 + 0x1e5,param_2 + 0x10);
    tmp_i6 = g_unk_010906e0 - param_2[1];
    tmp_i7 = tmp_pi4[0x16];
    param_2[0x14] = g_unk_01047afc;
    tmp_f1 = (float)(tmp_l9 / ((long double)tmp_i6 / (long double)1000.0)) / (float)tmp_i7;
    param_2[0x13] = (int)tmp_f1;
  }
  tmp_i7 = param_2[4];
  tmp_f1 = tmp_f1 * (float)param_4[0x1d0];
  param_2[0x13] = (int)tmp_f1;
  if (g_unk_010906e0 < tmp_i7) goto LAB_000a07e2;
  tmp_i6 = param_2[3];
  param_2[1] = tmp_i7;
  *param_2 = tmp_i6;
  param_2[2] = param_2[5];
  param_2[0x10] = param_4[0x1e5];
  param_2[0x11] = param_4[0x1e6];
  param_2[0x12] = param_4[0x1e7];
  if (0.25 <= tmp_f1) {
    if (1.1 < tmp_f1) {
      if ((*(byte *)(tmp_pi4 + 0x1a) & 1) == 0) {
        tmp_i5 = tmp_pi4[0x16];
        if (tmp_i5 < 0x65) {
          if (tmp_i5 < 0x14) {
            if (1.6 < tmp_f1) {
              param_2[0x13] = 0x3fcccccd;
              tmp_f1 = 1.6;
            }
          }
          else {
            tmp_f1 = 1.6 - ((float)(tmp_i5 + -0x14) * 0.5) / 80.0;
            param_2[0x13] = (int)tmp_f1;
          }
        }
        else {
          param_2[0x13] = 0x3f8ccccd;
          tmp_f1 = 1.1;
        }
      }
      else if (4.0 < tmp_f1) {
        param_2[0x13] = 0x40800000;
        tmp_f1 = 4.0;
      }
    }
  }
  else if ((0.01 <= tmp_f1) || (!tmp_b8)) {
    param_2[0x13] = 0x3e800000;
    tmp_f1 = 0.25;
  }
  else {
    param_2[0x13] = 0;
    tmp_f1 = 0.0;
  }
  if (param_2 == param_4 + 0x9a) {
    local_38 = param_4[0xbc];
  }
  else {
    local_38 = 0;
    if (param_2 == param_4 + 0xaf) {
      local_38 = param_4[0xa7];
    }
  }
  if (tmp_f1 == 0.0) {
    tmp_i5 = tmp_i6 - tmp_pi4[0x11];
    param_2[4] = tmp_i7 + tmp_pi4[0x14];
    tmp_i7 = tmp_pi4[0x12];
  }
  else {
    tmp_u3 = param_2[0xb];
    if ((param_2[0xc] == tmp_u3) ||
       (((tmp_pi4[0x16] != 0 && (tmp_pi4[0x11] <= tmp_i6)) && (tmp_i6 < tmp_pi4[0x11] + tmp_pi4[0x12]))))
    {
      if (local_38 != 0) {
        if (param_2 == param_4 + 0x9a) {
          if ((*(byte *)(tmp_pi4 + 0x1a) & 2) == 0) {
            if ((((tmp_u3 ^ param_4[0xba]) & 0xfffffdff) == 0) && (tmp_pi4[0x16] == 0)) {
              tmp_i5 = param_4[0xb2] - *(int *)(local_38 + 0x44);
              if ((tmp_pi4[0x12] <= tmp_i5) || (tmp_i5 < 0)) {
                tmp_i5 = 0;
              }
              param_2[4] = param_4[0xb3];
              goto LAB_000a09c0;
            }
            if (param_2 == param_4 + 0xaf) goto LAB_000a0adb;
          }
        }
        else if ((param_2 == param_4 + 0xaf) && ((*(byte *)(tmp_pi4 + 0x1a) & 2) == 0)) {
LAB_000a0adb:
          if ((((tmp_u3 ^ param_4[0xa5]) & 0xfffffdff) == 0) && (*(int *)(local_38 + 0x58) != 0)) {
            tmp_i5 = param_4[0x9d] - *(int *)(local_38 + 0x44);
            if ((tmp_pi4[0x12] <= tmp_i5) || (tmp_i5 < 0)) {
              tmp_i5 = 0;
            }
            param_2[4] = param_4[0x9e];
            tmp_i7 = tmp_pi4[0x12];
            goto LAB_000a075a;
          }
        }
      }
      tmp_i7 = tmp_i7 + (int)ROUND((float)tmp_pi4[0x14] * (1.0 / tmp_f1));
      param_2[4] = tmp_i7;
      tmp_i5 = g_unk_010906e0;
      if (tmp_i7 < g_unk_010906e0) {
        param_2[4] = g_unk_010906e0;
        if ((*(byte *)(tmp_pi4 + 0x1a) & 4) == 0) {
          if ((g_unk_010906e0 <= tmp_i5) || (tmp_pi4[0x16] != 0)) goto LAB_000a0cbe;
          tmp_i5 = (tmp_i6 - tmp_pi4[0x11]) + 1 + (g_unk_010906e0 - tmp_i5) / tmp_pi4[0x14];
          tmp_i7 = tmp_pi4[0x12];
        }
        else {
          if ((g_unk_010906e0 <= tmp_i5) || (tmp_pi4[0x16] != 0)) goto LAB_000a0ca0;
          tmp_i7 = tmp_pi4[0x12];
          tmp_i5 = tmp_i7 + (tmp_pi4[0x11] - tmp_i6) + (g_unk_010906e0 - tmp_i5) / tmp_pi4[0x14];
        }
      }
      else if ((*(byte *)(tmp_pi4 + 0x1a) & 4) == 0) {
LAB_000a0cbe:
        tmp_i7 = tmp_pi4[0x12];
        tmp_i5 = (tmp_i6 - tmp_pi4[0x11]) + 1;
      }
      else {
LAB_000a0ca0:
        tmp_i7 = tmp_pi4[0x12];
        tmp_i5 = (tmp_i7 - tmp_i6) + tmp_pi4[0x11];
      }
      if (tmp_i5 < 0) {
        tmp_i5 = 0;
      }
    }
    else {
      param_2[4] = param_2[0xe];
      tmp_i5 = 0;
      if (tmp_pi2 == (int *)0x0) {
LAB_000a09c0:
        tmp_i7 = tmp_pi4[0x12];
      }
      else if (tmp_pi4[0x16] == 0) {
        tmp_i7 = tmp_pi4[0x12];
        tmp_i5 = 0;
      }
      else {
        tmp_i7 = tmp_pi4[0x12];
        for (tmp_i5 = (tmp_i6 - tmp_pi2[0x11]) + 1; tmp_i5 < 0; tmp_i5 = tmp_i5 + tmp_i7) {
        }
      }
    }
  }
LAB_000a075a:
  if (tmp_i7 <= tmp_i5) {
    tmp_i6 = tmp_pi4[0x13];
    if (tmp_i6 == 0) {
      tmp_i5 = tmp_i7 + -1;
      param_2[4] = g_unk_010906e0;
    }
    else {
      tmp_i5 = (tmp_i7 - tmp_i6) + (tmp_i5 - tmp_i7) % tmp_i6;
    }
  }
  if ((*(byte *)(tmp_pi4 + 0x1a) & 4) == 0) {
    param_2[3] = tmp_i5 + tmp_pi4[0x11];
    param_2[5] = *tmp_pi4;
  }
  else {
    param_2[3] = (tmp_pi4[0x12] + tmp_pi4[0x11] + -1) - tmp_i5;
    param_2[5] = *tmp_pi4;
  }
  tmp_i7 = param_2[4];
  if (tmp_i7 < g_unk_010906e0) {
    if (param_5 < 5) {
      if (GHIDRA_FIELD(cg_animSpeed, 12, 4) == 0) {
        param_2[6] = 0;
        param_2[3] = 0;
        *param_2 = 0;
      }
      else {
        CG_RunLerpFrameRate_part_2(param_3,param_4,param_5 + 1);
      }
    }
    else {
      param_2[4] = g_unk_010906e0;
    }
    if ((int)GHIDRA_FIELD(cg_debugAnim, 12, 4) < 4) {
      tmp_i7 = param_2[4];
    }
    else {
      CG_Printf("Clamp lf->frameTime\n");
      tmp_i7 = param_2[4];
    }
  }
  param_2[0xc] = param_2[0xb];
LAB_000a07e2:
  tmp_i6 = g_unk_010906e0;
  if (g_unk_010906e0 + 5000 < tmp_i7) {
    param_2[4] = g_unk_010906e0;
    tmp_i7 = tmp_i6;
  }
  tmp_i6 = g_unk_010906e0;
  tmp_i5 = param_2[1];
  if (g_unk_010906e0 < param_2[1]) {
    param_2[1] = g_unk_010906e0;
    tmp_i5 = tmp_i6;
  }
  if (tmp_i5 == tmp_i7) {
    param_2[6] = 0;
  }
  else {
    param_2[6] = (int)(1.0 - (float)(g_unk_010906e0 - tmp_i5) / (float)(tmp_i7 - tmp_i5));
  }
  return;
}

void CG_ClearLerpFrameRate(int param_1,uint32_t param_2,uint32_t *param_3,uint param_4)
{
  uint tmp_u1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  int local_28;
  
  tmp_i5 = g_unk_010906e0;
  param_3[1] = g_unk_010906e0;
  param_3[4] = tmp_i5;
  tmp_i5 = CG_CharacterForClientinfo(param_2,param_1);
  if (tmp_i5 == 0) goto LAB_000a0ee4;
  tmp_u1 = param_3[0xb];
  param_3[0xb] = param_4;
  param_4 = param_4 & 0xfffffdff;
  tmp_i2 = param_3[0xd];
  if (((int)param_4 < 0) ||
     (tmp_i7 = *(int *)(tmp_i5 + 0x7f0), *(int *)(tmp_i7 + 0x89c) <= (int)param_4)) {
    CG_Error("CG_SetLerpFrameAnimationRate: Bad animation number: %i",param_4);
    tmp_i7 = *(int *)(tmp_i5 + 0x7f0);
  }
  tmp_pu3 = *(uint32_t **)(tmp_i7 + 0xc + (param_4 + 0x24) * 4);
  tmp_i7 = param_3[4];
  param_3[0xd] = tmp_pu3;
  param_3[0xe] = tmp_pu3[0x15] + tmp_i7;
  if (((*(byte *)(tmp_pu3 + 0x1a) & 2) == 0) || (param_3 != (uint32_t *)(param_1 + 700))) {
    if (param_3 == (uint32_t *)(param_1 + 0x268)) {
      tmp_i7 = BG_GetAnimationForIndex(*(uint32_t *)(tmp_i5 + 0x7f0),param_4);
      if ((*(byte *)(tmp_i7 + 0x6c) & 100) == 0) {
        tmp_i7 = BG_GetAnimationForIndex(*(uint32_t *)(tmp_i5 + 0x7f0),tmp_u1 & 0xfffffdff);
        if ((*(byte *)(tmp_i7 + 0x6c) & 100) == 0) {
LAB_000a105d:
          tmp_i7 = param_3[4];
          goto LAB_000a0e6d;
        }
      }
      else {
        tmp_i7 = BG_GetAnimationForIndex(*(uint32_t *)(tmp_i5 + 0x7f0),tmp_u1 & 0xfffffdff);
        if ((*(byte *)(tmp_i7 + 0x6c) & 100) != 0) goto LAB_000a105d;
      }
      if (tmp_pu3[0x16] == 0) {
        tmp_i7 = param_3[4];
        if ((tmp_pu3[0x1b] & 0x6000) == 0) {
          local_28 = tmp_i7 + 0x15e;
          goto LAB_000a0e82;
        }
        local_28 = tmp_i7 + 200;
        if (tmp_i2 == 0) goto LAB_000a0e91;
      }
      else {
        tmp_i7 = param_3[4];
        local_28 = tmp_i7 + 200;
        if (tmp_i2 == 0) goto LAB_000a0fd4;
      }
      tmp_i6 = *(int *)(tmp_i2 + 0x5c);
      if (tmp_i6 == 0) {
        if (tmp_pu3[0x16] != 0) goto LAB_000a0fd4;
LAB_000a0e91:
        tmp_i7 = param_3[0xe];
LAB_000a0e94:
        if (tmp_i7 < local_28) {
          param_3[0xe] = local_28;
        }
        goto LAB_000a0ea1;
      }
    }
    else {
LAB_000a0e6d:
      if (tmp_pu3[0x16] == 0) {
        local_28 = tmp_i7 + 0xaa;
LAB_000a0e82:
        if ((tmp_i2 == 0) || (tmp_i6 = *(int *)(tmp_i2 + 0x5c), tmp_i6 == 0)) goto LAB_000a0e91;
      }
      else {
        local_28 = tmp_i7 + 0x78;
        if ((tmp_i2 == 0) || (tmp_i6 = *(int *)(tmp_i2 + 0x5c), tmp_i6 == 0)) {
LAB_000a0fd4:
          if (1.0 <= (float)param_3[0x13]) goto LAB_000a0e91;
          tmp_i7 = tmp_pu3[0x15] + param_3[0xe];
          param_3[0xe] = tmp_i7;
          goto LAB_000a0e94;
        }
      }
    }
    param_3[0xe] = tmp_i6 + tmp_i7;
  }
LAB_000a0ea1:
  if (tmp_i2 == 0) {
    param_3[4] = g_unk_010906e0 + -1;
    param_3[0xe] = g_unk_010906e0 + -1;
    param_3[3] = tmp_pu3[0x11];
    param_3[5] = *tmp_pu3;
  }
  if (GHIDRA_FIELD(cg_debugAnim, 12, 4) == 1) {
    CG_Printf("Anim: %i, %s\n",param_4,
              *(int *)(*(int *)(tmp_i5 + 0x7f0) + 0xc + (param_4 + 0x24) * 4) + 4);
  }
LAB_000a0ee4:
  tmp_pu3 = (uint32_t *)param_3[0xd];
  if (tmp_pu3 != (uint32_t *)0x0) {
    tmp_u4 = tmp_pu3[0x11];
    param_3[3] = tmp_u4;
    *param_3 = tmp_u4;
    tmp_u4 = *tmp_pu3;
    param_3[5] = tmp_u4;
    param_3[2] = tmp_u4;
  }
  return;
}

void CG_SetLerpFrameAnimationRateCorpse(int param_1,int param_2,uint param_3)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  if (*(int *)(param_1 + 0xfc) < 0) {
    tmp_i3 = *(int *)(param_1 + 0xa4);
    if (tmp_i3 < 4) {
      tmp_i3 = BG_GetCharacter(tmp_i3,*(uint32_t *)(param_1 + 0xa8));
    }
    else {
      tmp_i3 = BG_GetCharacter(tmp_i3 + -4,*(uint32_t *)(param_1 + 0xa8));
    }
  }
  else {
    tmp_i3 = *(int *)(cgs + *(int *)(param_1 + 0xfc) * 4 + 0x7fc8);
  }
  if (tmp_i3 != 0) {
    *(uint *)(param_2 + 0x2c) = param_3;
    param_3 = param_3 & 0xfffffdff;
    if (((int)param_3 < 0) ||
       (tmp_i2 = *(int *)(tmp_i3 + 0x7f0), *(int *)(tmp_i2 + 0x89c) <= (int)param_3)) {
      CG_Error("CG_SetLerpFrameAnimationRate: Bad animation number: %i",param_3);
      tmp_i2 = *(int *)(tmp_i3 + 0x7f0);
    }
    tmp_pu1 = *(uint32_t **)(tmp_i2 + 0xc + (param_3 + 0x24) * 4);
    tmp_i4 = *(int *)(param_1 + 0x10c) - g_unk_010906e0;
    tmp_i2 = 0;
    if (-1 < tmp_i4) {
      tmp_i2 = tmp_i4;
    }
    tmp_i4 = tmp_pu1[0x18];
    *(uint32_t **)(param_2 + 0x34) = tmp_pu1;
    if (tmp_i2 <= tmp_i4) {
      tmp_i4 = tmp_i2;
    }
    *(int *)(param_2 + 0xc) = (tmp_pu1[0x18] - tmp_i4) / (int)tmp_pu1[0x14] + tmp_pu1[0x11];
    *(int *)(param_2 + 0x10) = g_unk_010906e0 + -1;
    *(int *)(param_2 + 0x38) = (tmp_i4 + g_unk_010906e0) - tmp_pu1[0x18];
    *(uint32_t *)(param_2 + 0x14) = *tmp_pu1;
    if (GHIDRA_FIELD(cg_debugAnim, 12, 4) != 0) {
      CG_Printf("Anim: %i, %s\n",param_3,
                *(int *)(*(int *)(tmp_i3 + 0x7f0) + 0xc + (param_3 + 0x24) * 4) + 4);
    }
  }
  return;
}

void CG_RunLerpFrameRateCorpse(uint32_t param_1,int *param_2,uint param_3,int param_4)
{
  int tmp_i1;
  int tmp_i2;
  int *tmp_pi3;
  int tmp_i4;
  int local_28;
  int local_24;
  
  if ((param_2[0xb] != param_3) || (tmp_pi3 = (int *)param_2[0xd], tmp_pi3 == (int *)0x0)) {
    if (*(int *)(param_4 + 0xfc) < 0) {
      tmp_i2 = *(int *)(param_4 + 0xa4);
      if (3 < tmp_i2) {
        tmp_i2 = tmp_i2 + -4;
      }
      local_28 = BG_GetCharacter(tmp_i2,*(uint32_t *)(param_4 + 0xa8));
    }
    else {
      local_28 = *(int *)(cgs + *(int *)(param_4 + 0xfc) * 4 + 0x7fc8);
    }
    if (local_28 == 0) {
      tmp_pi3 = (int *)param_2[0xd];
    }
    else {
      param_2[0xb] = param_3;
      param_3 = param_3 & 0xfffffdff;
      if (((int)param_3 < 0) ||
         (tmp_i2 = *(int *)(local_28 + 0x7f0), *(int *)(tmp_i2 + 0x89c) <= (int)param_3)) {
        CG_Error("CG_SetLerpFrameAnimationRate: Bad animation number: %i",param_3);
        tmp_i2 = *(int *)(local_28 + 0x7f0);
      }
      tmp_pi3 = *(int **)(tmp_i2 + 0xc + (param_3 + 0x24) * 4);
      tmp_i4 = *(int *)(param_4 + 0x10c) - g_unk_010906e0;
      tmp_i2 = 0;
      if (-1 < tmp_i4) {
        tmp_i2 = tmp_i4;
      }
      tmp_i4 = tmp_pi3[0x18];
      param_2[0xd] = (int)tmp_pi3;
      if (tmp_i2 <= tmp_i4) {
        tmp_i4 = tmp_i2;
      }
      param_2[3] = (tmp_pi3[0x18] - tmp_i4) / tmp_pi3[0x14] + tmp_pi3[0x11];
      param_2[4] = g_unk_010906e0 + -1;
      param_2[0xe] = (tmp_i4 + g_unk_010906e0) - tmp_pi3[0x18];
      param_2[5] = *tmp_pi3;
      if (GHIDRA_FIELD(cg_debugAnim, 12, 4) != 0) {
        CG_Printf("Anim: %i, %s\n",param_3,
                  *(int *)(*(int *)(local_28 + 0x7f0) + 0xc + (param_3 + 0x24) * 4) + 4);
        tmp_pi3 = (int *)param_2[0xd];
      }
    }
  }
  if (*(int *)(param_4 + 0x10c) < g_unk_010906e0) {
    tmp_i2 = tmp_pi3[0x12] + tmp_pi3[0x11] + -1;
    param_2[3] = tmp_i2;
    *param_2 = tmp_i2;
    tmp_i2 = *tmp_pi3;
    param_2[6] = 0;
    param_2[5] = tmp_i2;
    param_2[2] = tmp_i2;
    return;
  }
  tmp_i2 = param_2[4];
  local_28 = tmp_i2;
  if (tmp_i2 <= g_unk_010906e0) {
    param_2[1] = tmp_i2;
    *param_2 = param_2[3];
    param_2[2] = param_2[5];
    if (tmp_pi3[0x14] == 0) {
      return;
    }
    tmp_i4 = param_2[0xe];
    local_24 = 0;
    local_28 = tmp_i4;
    if (tmp_i4 <= g_unk_010906e0) {
      local_28 = tmp_pi3[0x14] + tmp_i2;
      local_24 = local_28 - tmp_i4;
    }
    param_2[4] = local_28;
    local_24 = local_24 / tmp_pi3[0x14];
    tmp_i4 = tmp_pi3[0x12];
    if (tmp_i4 <= local_24) {
      tmp_i1 = tmp_pi3[0x13];
      if (tmp_i1 == 0) {
        local_28 = g_unk_010906e0;
        local_24 = tmp_i4 + -1;
        param_2[4] = g_unk_010906e0;
      }
      else {
        local_24 = (tmp_i4 - tmp_i1) + (local_24 - tmp_i4) % tmp_i1;
      }
    }
    param_2[3] = local_24 + tmp_pi3[0x11];
    param_2[5] = *tmp_pi3;
    tmp_i4 = g_unk_010906e0;
    if ((g_unk_010906e0 <= local_28) ||
       (param_2[4] = g_unk_010906e0, local_28 = tmp_i4, GHIDRA_FIELD(cg_debugAnim, 12, 4) == 0)) goto LAB_000a1493;
    CG_Printf("Clamp lf->frameTime\n");
    local_28 = param_2[4];
  }
  tmp_i2 = param_2[1];
LAB_000a1493:
  tmp_i4 = g_unk_010906e0;
  if (g_unk_010906e0 + 200 < local_28) {
    param_2[4] = g_unk_010906e0;
    local_28 = tmp_i4;
  }
  tmp_i4 = g_unk_010906e0;
  if (g_unk_010906e0 < tmp_i2) {
    param_2[1] = g_unk_010906e0;
    tmp_i2 = tmp_i4;
  }
  if (tmp_i2 == local_28) {
    param_2[6] = 0;
  }
  else {
    param_2[6] = (int)(1.0 - (float)(g_unk_010906e0 - tmp_i2) / (float)(local_28 - tmp_i2));
  }
  return;
}

bool CG_WorldCoordToScreenCoordFloat(float *param_1,float *param_2,float *param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_10 = 9.30361e-40;
  AngleVectors(&g_unk_01091a54,&local_30,&local_24,&local_18);
  tmp_f1 = *param_1 - g_unk_010918c0;
  tmp_f4 = param_1[1] - g_unk_010918c4;
  tmp_f3 = param_1[2] - g_unk_010918c8;
  tmp_f2 = local_28 * tmp_f3 + local_2c * tmp_f4 + local_30 * tmp_f1;
  if (0.01 <= tmp_f2) {
    tmp_f5 = 102.0 / g_unk_010918bc;
    *param_2 = (96.0 / g_unk_010918b8) * (320.0 / tmp_f2) *
               (local_20 * tmp_f4 + local_24 * tmp_f1 + local_1c * tmp_f3) + 320.0;
    *param_3 = 240.0 - tmp_f5 * (240.0 / tmp_f2) *
                       (local_10 * tmp_f3 + tmp_f4 * local_14 + local_18 * tmp_f1);
  }
  return 0.01 <= tmp_f2;
}

void CG_WoundedPlayerFloatName(int *param_1,uint32_t param_2,int param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  int tmp_i9;
  int tmp_i10;
  int tmp_i11;
  int tmp_i12;
  long double tmp_l13;
  float local_50;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  if ((((GHIDRA_FIELD(cg_draw2D, 12, 4) != 0) && (GHIDRA_FIELD(cg_woundedNames, 12, 4) != 0)) && (g_unk_01047aec == 0)) &&
     (*param_1 != *(int *)(g_unk_01047b00 + 0xcc))) {
    tmp_f1 = (float)param_1[0x1e5];
    tmp_f2 = (float)param_1[0x1e6];
    local_50 = (float)param_1[0x1e7];
    if (param_3 == 0) {
      tmp_l13 = (long double)Distance(&g_unk_01090710,param_1 + 0x1e5);
      if (tmp_l13 < (long double)64.0) {
        return;
      }
      if ((long double)1600.0 < tmp_l13) {
        return;
      }
      local_50 = local_50 - 6.0;
    }
    else {
      local_50 = local_50 + 48.0;
    }
    if (g_unk_010eecc4 < 0x20) {
      AngleVectors(&g_unk_01091a54,&local_30,&local_24,&local_18);
      tmp_f3 = tmp_f1 - g_unk_010918c0;
      tmp_f6 = tmp_f2 - g_unk_010918c4;
      tmp_f5 = local_50 - g_unk_010918c8;
      tmp_f4 = local_28 * tmp_f5 + local_2c * tmp_f6 + local_30 * tmp_f3;
      if (0.01 <= tmp_f4) {
        tmp_f7 = 96.0 / g_unk_010918b8;
        tmp_f8 = 102.0 / g_unk_010918bc;
        tmp_i10 = CG_Text_Width_Ext(param_2,0x3e3851ec,0,0x110afec);
        tmp_i11 = CG_Text_Height_Ext(param_2,0x3e3851ec,0,0x110afec);
        tmp_i9 = g_unk_010eecc4;
        tmp_i12 = g_unk_010eecc4 * 0x2c;
        *(float *)(&g_unk_010ee744 + tmp_i12) =
             (tmp_f7 * (320.0 / tmp_f4) * (local_1c * tmp_f5 + local_20 * tmp_f6 + local_24 * tmp_f3) +
             320.0) - (float)tmp_i10 * 0.5;
        *(uint32_t *)((int)&g_unk_010ee749 + tmp_i12 + 3) = 0x3e3851ec;
        g_unk_010eecc4 = g_unk_010eecc4 + 1;
        *(float *)((int)&g_unk_010ee745 + tmp_i12 + 3) =
             (240.0 - tmp_f8 * (240.0 / tmp_f4) *
                      (tmp_f5 * local_10 + tmp_f6 * local_14 + tmp_f3 * local_18)) -
             (float)tmp_i11 * 0.5;
        (&g_unk_010ee754)[tmp_i9 * 0xb] = param_2;
        *(float *)(&g_unk_010ee758 + tmp_i9 * 0x16) = tmp_f1 - (float)tmp_i11 * 0.5;
        *(float *)(&g_unk_010ee75c + tmp_i12) = tmp_f2 - (float)tmp_i10 * 0.5;
        *(float *)(&g_unk_010ee760 + tmp_i12) = local_50;
      }
    }
  }
  return;
}

void CG_AddRefEntityWithPowerups
               (int param_1,uint32_t param_2,int param_3,int *param_4,uint32_t *param_5)

{
  float tmp_f1;
  int tmp_i2;
  uint32_t tmp_u3;
  bool tmp_b4;
  uint8_t tmp_u5;
  uint tmp_u6;
  uint tmp_u7;
  int tmp_i8;
  int tmp_i9;
  uint32_t local_108 [62];
  
  tmp_i2 = *param_4;
  *(int *)(param_1 + 0xe8) = tmp_i2;
  tmp_u6 = 0;
  do {
    tmp_u7 = tmp_u6;
    tmp_u3 = *(uint32_t *)(param_1 + 4 + tmp_u7);
    *(uint32_t *)((int)local_108 + tmp_u7) = *(uint32_t *)(param_1 + tmp_u7);
    *(uint32_t *)((int)local_108 + tmp_u7 + 4) = tmp_u3;
    tmp_u6 = tmp_u7 + 8;
  } while (tmp_u6 < 0xe8);
  *(uint32_t *)((int)local_108 + tmp_u7 + 8) = *(uint32_t *)(param_1 + tmp_u6);
  trap_R_AddRefEntityToScene(param_1);
  if ((*(byte *)(param_4 + 2) & 0x40) != 0) {
    if (((cg_entities[tmp_i2 * 0xaf8 + 0xe4] & 0x80) == 0) ||
       (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3)) {
      if (param_3 == 1) goto LAB_000a2f89;
LAB_000a2fc2:
      *(uint32_t *)(param_1 + 0xb4) = 0xffff0000;
    }
    else {
      if (param_3 == 1) goto LAB_000a2fc2;
LAB_000a2f89:
      *(uint32_t *)(param_1 + 0xb4) = 0xff0000ff;
    }
    *(uint32_t *)(param_1 + 0xb0) = GHIDRA_FIELD(cgs, 68904, 4);
    trap_R_AddRefEntityToScene(param_1);
  }
  tmp_i9 = *param_4 * 0xaf8;
  if ((*(int *)(cg_entities + tmp_i9) == *(int *)(g_unk_01047b00 + 0xcc)) &&
     (*(int *)(cg_entities + tmp_i9 + 4) != 0x26)) {
    tmp_i9 = *(int *)(g_unk_01047b00 + 0x450);
    if ((tmp_i9 == 0) || (g_unk_010906e0 <= tmp_i9)) goto LAB_000a2ecf;
    tmp_b4 = g_unk_010906e0 <= tmp_i9 + 1999;
  }
  else {
    tmp_i9 = *param_4 * 0xaf8;
    if (g_unk_010906e0 <= *(int *)(cg_entities + tmp_i9 + 0xfc)) goto LAB_000a2ecf;
    tmp_b4 = g_unk_010906e0 < *(int *)(cg_entities + tmp_i9 + 0x100);
  }
  if (tmp_b4) {
    if (*(int *)(param_1 + 0xe8) == *(int *)(g_unk_01047b00 + 0xcc)) {
      tmp_i9 = *(int *)(g_unk_01047b00 + 0x450);
      tmp_i8 = tmp_i9 + 0x5dc;
    }
    else {
      tmp_i9 = param_4[0x3f];
      tmp_i8 = param_4[0x40];
    }
    tmp_f1 = ((float)g_unk_010906e0 - (float)tmp_i9) / 1500.0;
    if ((tmp_f1 <= 1.0) || (tmp_f1 = ((float)tmp_i8 - (float)g_unk_010906e0) / 1500.0, tmp_f1 <= 1.0)) {
      if (tmp_f1 < 0.0) {
        tmp_u5 = 0;
        tmp_f1 = 0.0;
      }
      else {
        tmp_f1 = tmp_f1 * 255.0;
        tmp_u5 = (uint8_t)(short)ROUND(tmp_f1);
      }
    }
    else {
      tmp_f1 = 255.0;
      tmp_u5 = 0xff;
    }
    *(uint8_t *)(param_1 + 0xb7) = tmp_u5;
    *(uint32_t *)(param_1 + 0xcc) = *param_5;
    *(uint32_t *)(param_1 + 0xd0) = param_5[1];
    *(uint32_t *)(param_1 + 0xd4) = param_5[2];
    tmp_i9 = VectorCompare(param_1 + 0xcc,&vec3_origin);
    if (tmp_i9 != 0) {
      *(uint32_t *)(param_1 + 0xcc) = 0;
      *(uint32_t *)(param_1 + 0xd0) = 0;
      *(uint32_t *)(param_1 + 0xd4) = 0x3f800000;
    }
    *(uint32_t *)(param_1 + 0xb0) = GHIDRA_FIELD(cgs, 68852, 4);
    trap_R_AddRefEntityToScene(param_1);
    *(uint32_t *)(param_1 + 0xb0) = GHIDRA_FIELD(cgs, 68856, 4);
    trap_R_AddRefEntityToScene(param_1);
    if (*(int *)(param_1 + 8) == *(int *)(cg_entities + tmp_i2 * 0xaf8 + 0x480)) {
      trap_S_AddLoopingSound(param_1 + 0x68,&vec3_origin,GHIDRA_FIELD(cgs, 69532, 4),(int)ROUND(tmp_f1),0);
    }
  }
LAB_000a2ecf:
  tmp_u6 = 0;
  do {
    tmp_u7 = tmp_u6;
    tmp_u3 = *(uint32_t *)((int)local_108 + tmp_u7 + 4);
    *(uint32_t *)(param_1 + tmp_u7) = *(uint32_t *)((int)local_108 + tmp_u7);
    *(uint32_t *)(param_1 + 4 + tmp_u7) = tmp_u3;
    tmp_u6 = tmp_u7 + 8;
  } while (tmp_u6 < 0xe8);
  *(uint32_t *)(param_1 + tmp_u6) = *(uint32_t *)((int)local_108 + tmp_u7 + 8);
  return;
}

void CG_AnimPlayerConditions(int param_1,int *param_2)
{
  int tmp_i1;
  
  if ((param_1 != 0) &&
     (((g_unk_01047b00 == 0 || (*(int *)(g_unk_01047b00 + 0xcc) != *param_2)) || (g_unk_010906f4 != 0))))
  {
    if ((*(byte *)((int)param_2 + 10) & 4) == 0) {
      BG_UpdateConditionValue(param_2[0x2b],0,param_2[0x3a],1);
    }
    else {
      BG_UpdateConditionValue(param_2[0x2b],0,0x13,1);
    }
    if ((param_2[2] & 0x8020U) == 0) {
      BG_UpdateConditionValue(param_2[0x2b],4,0,1);
    }
    else {
      BG_UpdateConditionValue(param_2[0x2b],4,1,1);
    }
    BG_UpdateConditionValue
              (param_2[0x2b],0x10,*(uint32_t *)(cgs + param_2[0x2b] * 0x1a4 + 0x94b8),1);
    if (param_2[0x27] < 0x42) {
      if (param_2[0x27] < 0x21) {
        BG_UpdateConditionValue(param_2[0x2b],0x11,1,1);
      }
      else {
        BG_UpdateConditionValue(param_2[0x2b],0x11,2,1);
      }
    }
    else {
      BG_UpdateConditionValue(param_2[0x2b],0x11,3,1);
    }
    if ((*(byte *)(param_2 + 2) & 0x10) == 0) {
      BG_UpdateConditionValue(param_2[0x2b],9,0,1);
    }
    else {
      BG_UpdateConditionValue(param_2[0x2b],9,1,1);
    }
    if ((*(byte *)(param_2 + 2) & 0x80) == 0) {
      BG_UpdateConditionValue(param_2[0x2b],0xb,0,1);
    }
    else {
      BG_UpdateConditionValue(param_2[0x2b],0xb,1,1);
    }
    tmp_i1 = *(int *)(*(int *)(*(int *)(param_1 + 0x7f0) + 0x9c + (param_2[0x3b] & 0xfffffdffU) * 4)
                    + 0x6c);
    if (tmp_i1 != 0) {
      BG_UpdateConditionValue(param_2[0x2b],5,tmp_i1,0);
    }
  }
  return;
}

void CG_ResetPlayerEntity(uint32_t *param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  uint tmp_u6;
  uint tmp_u7;
  bool tmp_b8;
  
  tmp_u1 = g_unk_010906e0;
  if ((*(byte *)(param_1 + 2) & 1) == 0) {
    tmp_pu3 = param_1 + 0x9a;
    param_1[0x9b] = g_unk_010906e0;
    param_1[0x9e] = tmp_u1;
    CG_SetLerpFrameAnimationRate(param_1,param_1[0x2b] * 0x1a4 + 0x10f926c,tmp_pu3,param_1[0x3b]);
    tmp_pu4 = (uint32_t *)param_1[0xa7];
    if (tmp_pu4 != (uint32_t *)0x0) {
      tmp_u1 = tmp_pu4[0x11];
      param_1[0x9d] = tmp_u1;
      param_1[0x9a] = tmp_u1;
      tmp_u1 = *tmp_pu4;
      param_1[0x9f] = tmp_u1;
      param_1[0x9c] = tmp_u1;
    }
    tmp_u1 = g_unk_010906e0;
    tmp_pu4 = param_1 + 0xaf;
    tmp_u7 = param_1[0x3c];
    param_1[0xb0] = g_unk_010906e0;
    param_1[0xb3] = tmp_u1;
    tmp_i2 = CG_CharacterForClientinfo(param_1[0x2b] * 0x1a4 + 0x10f926c,param_1);
    if (tmp_i2 != 0) {
      param_1[0xba] = tmp_u7;
      tmp_u7 = tmp_u7 & 0xfffffdff;
      if (((int)tmp_u7 < 0) ||
         (tmp_i5 = *(int *)(tmp_i2 + 0x7f0), *(int *)(tmp_i5 + 0x89c) <= (int)tmp_u7)) {
        CG_Error("CG_SetLerpFrameAnimation: Bad animation number: %i",tmp_u7);
        tmp_i5 = *(int *)(tmp_i2 + 0x7f0);
      }
      tmp_i5 = *(int *)(tmp_i5 + 0xc + (tmp_u7 + 0x24) * 4);
      param_1[0xbc] = tmp_i5;
      param_1[0xbd] = *(int *)(tmp_i5 + 0x54) + param_1[0xb3];
      if (GHIDRA_FIELD(cg_debugAnim, 12, 4) != 0) {
        CG_Printf("Anim: %i, %s\n",tmp_u7,
                  *(int *)(*(int *)(tmp_i2 + 0x7f0) + 0xc + (tmp_u7 + 0x24) * 4) + 4);
      }
    }
    tmp_u7 = 0x54;
    tmp_b8 = ((uint)tmp_pu3 & 1) != 0;
    if (tmp_b8) {
      *(uint8_t *)(param_1 + 0x9a) = 0;
      tmp_pu3 = (uint32_t *)((int)param_1 + 0x269);
      tmp_u7 = 0x53;
    }
    if (((uint)tmp_pu3 & 2) != 0) {
      *(uint16_t *)tmp_pu3 = 0;
      tmp_u7 = tmp_u7 - 2;
      tmp_pu3 = (uint32_t *)((int)tmp_pu3 + 2);
    }
    tmp_u6 = 0;
    do {
      *(uint32_t *)((int)tmp_pu3 + tmp_u6) = 0;
      *(uint32_t *)((int)tmp_pu3 + tmp_u6 + 4) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < (tmp_u7 & 0xfffffff8));
    tmp_pu3 = (uint32_t *)((int)tmp_pu3 + tmp_u6);
    if ((tmp_u7 & 4) != 0) {
      *tmp_pu3 = 0;
      tmp_pu3 = tmp_pu3 + 1;
    }
    if ((tmp_u7 & 2) != 0) {
      *(uint16_t *)tmp_pu3 = 0;
      tmp_pu3 = (uint32_t *)((int)tmp_pu3 + 2);
    }
    if (tmp_b8) {
      *(uint8_t *)tmp_pu3 = 0;
    }
    tmp_u1 = param_1[0x1e3];
    param_1[0xa2] = 0;
    tmp_u7 = 0x54;
    param_1[0xa1] = tmp_u1;
    param_1[0xa3] = 0;
    param_1[0xa4] = 0;
    tmp_b8 = ((uint)tmp_pu4 & 1) != 0;
    if (tmp_b8) {
      *(uint8_t *)(param_1 + 0xaf) = 0;
      tmp_pu4 = (uint32_t *)((int)param_1 + 0x2bd);
      tmp_u7 = 0x53;
    }
    if (((uint)tmp_pu4 & 2) != 0) {
      *(uint16_t *)tmp_pu4 = 0;
      tmp_u7 = tmp_u7 - 2;
      tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
    }
    tmp_u6 = 0;
    do {
      *(uint32_t *)((int)tmp_pu4 + tmp_u6) = 0;
      *(uint32_t *)((int)tmp_pu4 + tmp_u6 + 4) = 0;
      tmp_u6 = tmp_u6 + 8;
    } while (tmp_u6 < (tmp_u7 & 0xfffffff8));
    tmp_pu4 = (uint32_t *)((int)tmp_pu4 + tmp_u6);
    if ((tmp_u7 & 4) != 0) {
      *tmp_pu4 = 0;
      tmp_pu4 = tmp_pu4 + 1;
    }
    if ((tmp_u7 & 2) != 0) {
      *(uint16_t *)tmp_pu4 = 0;
      tmp_pu4 = (uint32_t *)((int)tmp_pu4 + 2);
    }
    if (tmp_b8) {
      *(uint8_t *)tmp_pu4 = 0;
    }
    param_1[0xb6] = tmp_u1;
    param_1[0xb7] = 0;
    param_1[0xb8] = param_1[0x1e2];
    param_1[0xb9] = 0;
  }
  BG_EvaluateTrajectory(param_1 + 3,g_unk_010906e0,param_1 + 0x1e5,0,param_1[0x44]);
  BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0,param_1 + 0x1e8,1,param_1[0x44]);
  tmp_u1 = GHIDRA_FIELD(cg_debugPosition, 12, 4);
  param_1[0x1df] = param_1[0x1e5];
  param_1[0x1e0] = param_1[0x1e6];
  param_1[0x1e1] = param_1[0x1e7];
  param_1[0x1e2] = param_1[0x1e8];
  param_1[0x1e3] = param_1[0x1e9];
  param_1[0x1e4] = param_1[0x1ea];
  if (tmp_u1 != 0) {
    CG_Printf("%i ResetPlayerEntity yaw=%i\n",*param_1,(double)(float)param_1[0xb6]);
  }
  param_1[0x11c] = 0xffffffff;
  param_1[0x11b] = 0xffffffff;
  param_1[0x1d0] = 0x3f800000;
  return;
}

void CG_GetBleedOrigin(uint32_t *param_1,uint32_t *param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  int tmp_i5;
  int tmp_i6;
  uint tmp_u7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  uint32_t *tmp_pu11;
  int tmp_i12;
  uint32_t *tmp_pu13;
  byte tmp_b14;
  int local_cec [16];
  uint8_t local_cac [40];
  uint32_t local_c84;
  uint32_t local_c80;
  uint32_t local_c7c;
  uint32_t local_c78;
  uint32_t local_c74;
  uint32_t local_c70;
  uint32_t local_c6c;
  uint32_t local_c68;
  uint32_t local_c64;
  uint32_t local_c60;
  uint32_t local_c5c;
  uint32_t local_c58;
  uint32_t local_c54;
  uint32_t local_c50;
  uint32_t local_c4c;
  uint32_t local_c48;
  int local_c00 [7];
  uint8_t local_be4 [76];
  uint32_t local_b98;
  uint32_t local_b94;
  uint32_t local_b90;
  uint32_t local_b14;
  uint32_t local_b10 [704];
  
  tmp_b14 = 0;
  if (*(int *)(cgs + param_3 * 0x1a4 + 0x940c) != 0) {
    tmp_i2 = CG_CharacterForClientinfo(param_3 * 0x1a4 + 0x10f926c,0);
    tmp_u7 = 0xaf8;
    tmp_i3 = param_3 * 0xaf8;
    tmp_pu4 = (uint32_t *)(cg_entities + tmp_i3);
    tmp_pu11 = tmp_pu4;
    tmp_pu13 = &local_b14;
    if (((uint)&local_b14 & 4) != 0) {
      local_b14 = *tmp_pu4;
      tmp_pu13 = local_b10;
      tmp_u7 = 0xaf4;
      tmp_pu11 = (uint32_t *)(cg_entities + tmp_i3 + 4);
    }
    for (tmp_u7 = tmp_u7 >> 2; tmp_u7 != 0; tmp_u7 = tmp_u7 - 1) {
      *tmp_pu13 = *tmp_pu11;
      tmp_pu11 = tmp_pu11 + (uint)tmp_b14 * -2 + 1;
      tmp_pu13 = tmp_pu13 + (uint)tmp_b14 * -2 + 1;
    }
    tmp_u7 = 0;
    do {
      *(uint32_t *)((int)local_cec + tmp_u7) = 0;
      *(uint32_t *)((int)local_cec + tmp_u7 + 4) = 0;
      tmp_u7 = tmp_u7 + 8;
    } while (tmp_u7 < 0xe8);
    *(uint32_t *)((int)local_cec + tmp_u7) = 0;
    tmp_u7 = 0;
    do {
      *(uint32_t *)((int)local_c00 + tmp_u7) = 0;
      *(uint32_t *)((int)local_c00 + tmp_u7 + 4) = 0;
      tmp_u7 = tmp_u7 + 8;
    } while (tmp_u7 < 0xe8);
    *(uint32_t *)((int)local_c00 + tmp_u7) = 0;
    CG_PlayerAngles(local_cac,local_be4);
    tmp_i10 = param_3 * 0xaf8;
    tmp_i6 = *(int *)(cg_entities + tmp_i10 + 0xac);
    tmp_i1 = tmp_i6 * 0x1a4 + 0x10f926c;
    tmp_i5 = CG_CharacterForClientinfo(tmp_i1,tmp_pu4);
    tmp_i9 = g_unk_010906e0;
    if (tmp_i5 != 0) {
      if (GHIDRA_FIELD(cg_noPlayerAnims, 12, 4) == 0) {
        tmp_i12 = *(int *)(cg_entities + tmp_i10 + 0xec);
        if ((cg_entities[tmp_i10 + 10] & 0x80) == 0) {
          tmp_i8 = *(int *)(cg_entities + tmp_i10 + 0x778);
        }
        else {
          tmp_i8 = g_unk_010906e0 + 0x6d6;
          *(int *)(cg_entities + tmp_i10 + 0x778) = tmp_i8;
        }
        if ((((tmp_i8 < tmp_i9) &&
             (tmp_i9 = param_3 * 0xaf8, (*(uint *)(cg_entities + tmp_i9 + 8) & 0x808001) == 0)) &&
            (*(int *)(cg_entities + tmp_i9 + 0x288) != 0)) &&
           (tmp_i6 = BG_GetAnimScriptAnimation
                              (tmp_i6,*(uint32_t *)(tmp_i5 + 0x7f0),
                               *(uint32_t *)(cg_entities + tmp_i9 + 0x118),
                               (*(int *)(cg_entities + tmp_i9 + 0x288) != 1) + '\r'), -1 < tmp_i6)) {
          tmp_i12 = tmp_i6;
        }
        if (*(int *)(cg_entities + param_3 * 0xaf8 + 4) == 0x26) {
          CG_RunLerpFrameRateCorpse(tmp_i1,param_3 * 0xaf8 + 0x31340a8,tmp_i12,tmp_pu4,0);
        }
        else if (GHIDRA_FIELD(cg_animSpeed, 12, 4) == 0) {
          *(uint32_t *)(cg_entities + tmp_i3 + 0x280) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x274) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x268) = 0;
        }
        else {
          CG_RunLerpFrameRate_part_2(tmp_i12,tmp_pu4,0);
        }
        tmp_i6 = param_3 * 0xaf8;
        local_c5c = *(uint32_t *)(cg_entities + tmp_i6 + 0x268);
        local_c78 = *(uint32_t *)(cg_entities + tmp_i6 + 0x274);
        local_c58 = *(uint32_t *)(cg_entities + tmp_i6 + 0x270);
        local_c4c = *(uint32_t *)(cg_entities + tmp_i6 + 0x280);
        local_c74 = *(uint32_t *)(cg_entities + tmp_i6 + 0x27c);
        if (*(int *)(cg_entities + tmp_i6 + 4) == 0x26) {
          CG_RunLerpFrameRateCorpse
                    (tmp_i1,tmp_i6 + 0x31340fc,*(uint32_t *)(cg_entities + tmp_i6 + 0xf0),tmp_pu4,0);
        }
        else if (GHIDRA_FIELD(cg_animSpeed, 12, 4) == 0) {
          *(uint32_t *)(cg_entities + tmp_i3 + 0x2d4) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x2c8) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 700) = 0;
        }
        else {
          CG_RunLerpFrameRate_part_2(*(uint32_t *)(cg_entities + tmp_i6 + 0xf0),tmp_pu4,0);
        }
        tmp_i3 = param_3 * 0xaf8;
        local_c54 = *(uint32_t *)(cg_entities + tmp_i3 + 700);
        local_c48 = *(uint32_t *)(cg_entities + tmp_i3 + 0x2d4);
        local_c6c = *(uint32_t *)(cg_entities + tmp_i3 + 0x2d0);
        local_c70 = *(uint32_t *)(cg_entities + tmp_i3 + 0x2c8);
        local_c50 = *(uint32_t *)(cg_entities + tmp_i3 + 0x2c4);
      }
      else {
        local_c54 = 0;
        local_c70 = 0;
        local_c5c = 0;
        local_c78 = 0;
        local_c74 = **(uint32_t **)(*(int *)(tmp_i5 + 0x7f0) + 0x9c);
        local_c6c = local_c74;
        local_c58 = local_c74;
        local_c50 = local_c74;
      }
    }
    local_cec[2] = *(int *)(tmp_i2 + 0x40);
    if ((local_cec[2] != 0) && (local_c00[2] = *(int *)(tmp_i2 + 0xa0), local_c00[2] != 0)) {
      param_3 = param_3 * 0xaf8;
      local_c84 = *(uint32_t *)(cg_entities + param_3 + 0x794);
      local_c80 = *(uint32_t *)(cg_entities + param_3 + 0x798);
      local_c7c = *(uint32_t *)(cg_entities + param_3 + 0x79c);
      tmp_pu11 = &local_b14;
      tmp_pu13 = (uint32_t *)(cg_entities + param_3);
      for (tmp_i2 = 0x2be; tmp_i2 != 0; tmp_i2 = tmp_i2 + -1) {
        *tmp_pu13 = *tmp_pu11;
        tmp_pu11 = tmp_pu11 + (uint)tmp_b14 * -2 + 1;
        tmp_pu13 = tmp_pu13 + (uint)tmp_b14 * -2 + 1;
      }
      local_c68 = local_c84;
      local_c64 = local_c80;
      local_c60 = local_c7c;
      CG_PositionRotatedEntityOnTag(local_c00,local_cec,"tag_head");
      *param_1 = local_b98;
      param_1[1] = local_b94;
      param_1[2] = local_b90;
      *param_2 = local_c84;
      param_2[1] = local_c80;
      param_2[2] = local_c7c;
    }
  }
  return;
}

uint32_t CG_GetTag(int param_1,uint32_t param_2,float *param_3)
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
  uint32_t tmp_u12;
  int tmp_i13;
  uint tmp_u14;
  uint tmp_u15;
  float *pfVar16;
  float *pfVar17;
  uint32_t *tmp_pu18;
  uint8_t *tmp_pu19;
  bool tmp_b20;
  uint8_t local_40;
  uint32_t auStack_3f [11];
  
  if (((g_unk_01047b00 == 0) || (*(int *)(g_unk_01047b00 + 0xcc) != param_1)) || (g_unk_010906f4 == 0)) {
    tmp_pu19 = cg_entities + *(int *)(cgs + param_1 * 0x1a4 + 0x9410) * 0xaf8;
    if (*(int *)(cg_entities + *(int *)(cgs + param_1 * 0x1a4 + 0x9410) * 0xaf8 + 0x244) == 0) {
      return 0;
    }
  }
  else {
    tmp_pu19 = &g_unk_01090ca8;
  }
  tmp_i13 = trap_R_LerpTag(param_3,tmp_pu19 + 0x478,param_2,0);
  if (tmp_i13 < 0) {
    return 0;
  }
  tmp_f1 = param_3[2];
  pfVar16 = param_3 + 3;
  tmp_pu18 = (uint32_t *)&local_40;
  tmp_f2 = *(float *)(tmp_pu19 + 0x4b0);
  tmp_f3 = *(float *)(tmp_pu19 + 0x4e4);
  tmp_f4 = *(float *)(tmp_pu19 + 0x4b4);
  tmp_f5 = *(float *)(tmp_pu19 + 0x4e8);
  tmp_f6 = param_3[1];
  tmp_f7 = *(float *)(tmp_pu19 + 0x4a4);
  tmp_f8 = *(float *)(tmp_pu19 + 0x4a8);
  tmp_f9 = *param_3;
  tmp_f10 = *(float *)(tmp_pu19 + 0x498);
  tmp_f11 = *(float *)(tmp_pu19 + 0x49c);
  *param_3 = tmp_f9 * *(float *)(tmp_pu19 + 0x494) +
             *(float *)(tmp_pu19 + 0x4a0) * tmp_f6 +
             *(float *)(tmp_pu19 + 0x4ac) * tmp_f1 + *(float *)(tmp_pu19 + 0x4e0);
  param_3[1] = tmp_f10 * tmp_f9 + tmp_f7 * tmp_f6 + tmp_f2 * tmp_f1 + tmp_f3;
  param_3[2] = tmp_f11 * tmp_f9 + tmp_f6 * tmp_f8 + tmp_f5 + tmp_f1 * tmp_f4;
  MatrixMultiply(tmp_pu19 + 0x494,pfVar16,tmp_pu18);
  tmp_u15 = 0x24;
  tmp_b20 = ((uint)pfVar16 & 1) != 0;
  if (tmp_b20) {
    pfVar16 = (float *)((int)param_3 + 0xd);
    tmp_u15 = 0x23;
    tmp_pu18 = auStack_3f;
    *(uint8_t *)(param_3 + 3) = local_40;
  }
  pfVar17 = pfVar16;
  if (((uint)pfVar16 & 2) != 0) {
    tmp_u12 = *tmp_pu18;
    pfVar17 = (float *)((int)pfVar16 + 2);
    tmp_pu18 = (uint32_t *)((int)tmp_pu18 + 2);
    tmp_u15 = tmp_u15 - 2;
    *(short *)pfVar16 = (short)tmp_u12;
  }
  tmp_u14 = 0;
  do {
    *(uint32_t *)((int)pfVar17 + tmp_u14) = *(uint32_t *)((int)tmp_pu18 + tmp_u14);
    tmp_u14 = tmp_u14 + 4;
  } while (tmp_u14 < (tmp_u15 & 0xfffffffc));
  tmp_i13 = 0;
  if ((tmp_u15 & 2) != 0) {
    *(uint16_t *)((int)pfVar17 + tmp_u14) = (short)*(uint32_t *)((int)tmp_pu18 + tmp_u14);
    tmp_i13 = 2;
  }
  if (tmp_b20) {
    *(uint8_t *)((int)((int)pfVar17 + tmp_u14) + tmp_i13) =
         *(uint8_t *)((int)((int)tmp_pu18 + tmp_u14) + tmp_i13);
  }
  return 1;
}

uint32_t CG_GetWeaponTag(int param_1,uint32_t param_2,float *param_3)
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
  uint32_t tmp_u12;
  int tmp_i13;
  uint tmp_u14;
  uint tmp_u15;
  float *pfVar16;
  float *pfVar17;
  uint32_t *tmp_pu18;
  uint8_t *tmp_pu19;
  bool tmp_b20;
  uint8_t local_40;
  uint32_t auStack_3f [11];
  
  if (((g_unk_01047b00 == 0) || (*(int *)(g_unk_01047b00 + 0xcc) != param_1)) || (g_unk_010906f4 == 0)) {
    tmp_pu19 = cg_entities + *(int *)(cgs + param_1 * 0x1a4 + 0x9410) * 0xaf8;
    if (*(int *)(cg_entities + *(int *)(cgs + param_1 * 0x1a4 + 0x9410) * 0xaf8 + 0x244) == 0) {
      return 0;
    }
  }
  else {
    tmp_pu19 = &g_unk_01090ca8;
  }
  if ((cg + -1 <= *(int *)(tmp_pu19 + 0x73c)) &&
     (tmp_i13 = trap_R_LerpTag(param_3,tmp_pu19 + 0x650,param_2,0), -1 < tmp_i13)) {
    tmp_f1 = param_3[2];
    pfVar16 = param_3 + 3;
    tmp_pu18 = (uint32_t *)&local_40;
    tmp_f2 = *(float *)(tmp_pu19 + 0x688);
    tmp_f3 = *(float *)(tmp_pu19 + 0x6bc);
    tmp_f4 = *(float *)(tmp_pu19 + 0x68c);
    tmp_f5 = *(float *)(tmp_pu19 + 0x6c0);
    tmp_f6 = param_3[1];
    tmp_f7 = *(float *)(tmp_pu19 + 0x67c);
    tmp_f8 = *(float *)(tmp_pu19 + 0x680);
    tmp_f9 = *param_3;
    tmp_f10 = *(float *)(tmp_pu19 + 0x670);
    tmp_f11 = *(float *)(tmp_pu19 + 0x674);
    *param_3 = tmp_f9 * *(float *)(tmp_pu19 + 0x66c) +
               *(float *)(tmp_pu19 + 0x678) * tmp_f6 +
               *(float *)(tmp_pu19 + 0x684) * tmp_f1 + *(float *)(tmp_pu19 + 0x6b8);
    param_3[1] = tmp_f10 * tmp_f9 + tmp_f7 * tmp_f6 + tmp_f2 * tmp_f1 + tmp_f3;
    param_3[2] = tmp_f11 * tmp_f9 + tmp_f6 * tmp_f8 + tmp_f5 + tmp_f1 * tmp_f4;
    MatrixMultiply(tmp_pu19 + 0x66c,pfVar16,tmp_pu18);
    tmp_u15 = 0x24;
    tmp_b20 = ((uint)pfVar16 & 1) != 0;
    if (tmp_b20) {
      pfVar16 = (float *)((int)param_3 + 0xd);
      tmp_u15 = 0x23;
      tmp_pu18 = auStack_3f;
      *(uint8_t *)(param_3 + 3) = local_40;
    }
    pfVar17 = pfVar16;
    if (((uint)pfVar16 & 2) != 0) {
      tmp_u12 = *tmp_pu18;
      pfVar17 = (float *)((int)pfVar16 + 2);
      tmp_pu18 = (uint32_t *)((int)tmp_pu18 + 2);
      tmp_u15 = tmp_u15 - 2;
      *(short *)pfVar16 = (short)tmp_u12;
    }
    tmp_u14 = 0;
    do {
      *(uint32_t *)((int)pfVar17 + tmp_u14) = *(uint32_t *)((int)tmp_pu18 + tmp_u14);
      tmp_u14 = tmp_u14 + 4;
    } while (tmp_u14 < (tmp_u15 & 0xfffffffc));
    tmp_i13 = 0;
    if ((tmp_u15 & 2) != 0) {
      *(uint16_t *)((int)pfVar17 + tmp_u14) = (short)*(uint32_t *)((int)tmp_pu18 + tmp_u14);
      tmp_i13 = 2;
    }
    if (tmp_b20) {
      *(uint8_t *)((int)((int)pfVar17 + tmp_u14) + tmp_i13) =
           *(uint8_t *)((int)((int)tmp_pu18 + tmp_u14) + tmp_i13);
    }
    return 1;
  }
  return 0;
}

void CG_SetHudHeadLerpFrameAnimation(int param_1,int param_2,uint param_3)
{
  *(uint *)(param_2 + 0x2c) = param_3;
  param_3 = param_3 & 0xfffffdff;
  if (0xf < param_3) {
    CG_Error("Bad animation number (CG_SetHudHeadLerpFrameAnimation): %i",param_3);
  }
  *(uint *)(param_2 + 0x34) = param_1 + 0xa8 + param_3 * 0x70;
  *(int *)(param_2 + 0x38) = *(int *)(param_1 + 0xfc + param_3 * 0x70) + *(int *)(param_2 + 0x10);
  return;
}

void CG_ClearHudHeadLerpFrame(int param_1,uint32_t *param_2,uint param_3)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i4 = g_unk_010906e0;
  param_2[0xb] = param_3;
  param_3 = param_3 & 0xfffffdff;
  param_2[1] = tmp_i4;
  param_2[4] = tmp_i4;
  if (0xf < param_3) {
    CG_Error("Bad animation number (CG_SetHudHeadLerpFrameAnimation): %i",param_3);
    tmp_i4 = param_2[4];
  }
  tmp_i3 = param_3 * 0x70;
  tmp_i1 = param_1 + 0xa0 + tmp_i3;
  param_2[0xd] = tmp_i1 + 8;
  param_2[0xe] = tmp_i4 + *(int *)(param_1 + 0xfc + tmp_i3);
  tmp_u2 = *(uint32_t *)(param_1 + 0xec + tmp_i3);
  param_2[3] = tmp_u2;
  *param_2 = tmp_u2;
  tmp_u2 = *(uint32_t *)(tmp_i1 + 8);
  param_2[5] = tmp_u2;
  param_2[2] = tmp_u2;
  return;
}

void CG_RunHudHeadLerpFrame(int param_1,uint32_t *param_2,uint param_3,float param_4)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  int tmp_i6;
  int local_30;
  int local_2c;
  
  tmp_i6 = g_unk_010906e0;
  tmp_pu5 = (uint32_t *)param_2[0xd];
  if (tmp_pu5 == (uint32_t *)0x0) {
    param_2[0xb] = param_3;
    param_3 = param_3 & 0xfffffdff;
    param_2[1] = tmp_i6;
    param_2[4] = tmp_i6;
    if (0xf < param_3) {
      CG_Error("Bad animation number (CG_SetHudHeadLerpFrameAnimation): %i",param_3);
      tmp_i6 = param_2[4];
    }
    tmp_i1 = param_3 * 0x70;
    tmp_i4 = param_1 + 0xa0 + tmp_i1;
    tmp_pu5 = (uint32_t *)(tmp_i4 + 8);
    param_2[0xd] = tmp_pu5;
    param_2[0xe] = *(int *)(param_1 + 0xfc + tmp_i1) + tmp_i6;
    tmp_u3 = *(uint32_t *)(param_1 + 0xec + tmp_i1);
    param_2[3] = tmp_u3;
    *param_2 = tmp_u3;
    tmp_u3 = *(uint32_t *)(tmp_i4 + 8);
    param_2[5] = tmp_u3;
    param_2[2] = tmp_u3;
  }
  else if (param_2[0xb] == param_3) {
    tmp_i6 = param_2[4];
  }
  else {
    param_2[0xb] = param_3;
    param_3 = param_3 & 0xfffffdff;
    if (0xf < param_3) {
      CG_Error("Bad animation number (CG_SetHudHeadLerpFrameAnimation): %i",param_3);
    }
    tmp_i6 = param_2[4];
    tmp_pu5 = (uint32_t *)(param_1 + 0xa8 + param_3 * 0x70);
    param_2[0xd] = tmp_pu5;
    param_2[0xe] = *(int *)(param_1 + 0xfc + param_3 * 0x70) + tmp_i6;
  }
  if (g_unk_010906e0 < tmp_i6) {
    local_30 = tmp_i6;
    tmp_i6 = param_2[1];
  }
  else {
    param_2[1] = tmp_i6;
    *param_2 = param_2[3];
    param_2[2] = param_2[5];
    if (tmp_pu5[0x14] == 0) {
      return;
    }
    tmp_i4 = param_2[0xe];
    local_2c = 0;
    local_30 = tmp_i4;
    if (tmp_i4 <= g_unk_010906e0) {
      local_30 = tmp_pu5[0x14] + tmp_i6;
      local_2c = local_30 - tmp_i4;
    }
    param_2[4] = local_30;
    tmp_i4 = (int)ROUND((float)(local_2c / (int)tmp_pu5[0x14]) * param_4);
    tmp_i1 = tmp_pu5[0x12];
    if (tmp_i1 <= tmp_i4) {
      tmp_i2 = tmp_pu5[0x13];
      if (tmp_i2 == 0) {
        local_30 = g_unk_010906e0;
        tmp_i4 = tmp_i1 + -1;
        param_2[4] = g_unk_010906e0;
      }
      else {
        tmp_i4 = (tmp_i1 - tmp_i2) + (tmp_i4 - tmp_i1) % tmp_i2;
      }
    }
    param_2[3] = tmp_i4 + tmp_pu5[0x11];
    param_2[5] = *tmp_pu5;
    tmp_i4 = g_unk_010906e0;
    if (local_30 < g_unk_010906e0) {
      param_2[4] = g_unk_010906e0;
      local_30 = tmp_i4;
    }
  }
  tmp_i4 = g_unk_010906e0;
  if (g_unk_010906e0 + 200 < local_30) {
    param_2[4] = g_unk_010906e0;
    local_30 = tmp_i4;
  }
  tmp_i4 = g_unk_010906e0;
  if (g_unk_010906e0 < tmp_i6) {
    param_2[1] = g_unk_010906e0;
    tmp_i6 = tmp_i4;
  }
  if (tmp_i6 == local_30) {
    param_2[6] = 0;
  }
  else {
    param_2[6] = 1.0 - (float)(g_unk_010906e0 - tmp_i6) / (float)(local_30 - tmp_i6);
  }
  return;
}

void CG_CheckAmmo(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  
  tmp_i1 = *(int *)(g_unk_01047b00 + 0x400);
  if ((tmp_i1 == 0) && (*(int *)(g_unk_01047b00 + 0x404) == 0)) {
    return;
  }
  tmp_i4 = 0x33;
  tmp_i5 = 0;
  do {
    tmp_i2 = g_unk_01047b00;
    if ((tmp_i1 >> ((byte)tmp_i4 & 0x1f) & 1U) != 0) {
      tmp_i3 = BG_FindAmmoForWeapon(tmp_i4);
      tmp_i5 = tmp_i5 + *(int *)(tmp_i2 + 0x1bc + tmp_i3 * 4) * 1000;
      if (4999 < tmp_i5) {
        g_unk_01093554 = 0;
        return;
      }
    }
    tmp_i4 = tmp_i4 + -1;
  } while (tmp_i4 != -1);
  if (g_unk_01093554 == 0) {
    trap_S_StartLocalSound(GHIDRA_FIELD(cgs, 69412, 4),6);
  }
  g_unk_01093554 = ~-(uint)(tmp_i5 == 0) + 2;
  return;
}

void CG_DamageFeedback(int param_1,int param_2,int param_3)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  uint tmp_u7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  long double tmp_l11;
  float local_60;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  tmp_i9 = g_unk_010906e0;
  tmp_i8 = g_unk_01047b00;
  uStack_14 = 0xa7ed9;
  g_unk_010aac18 = g_unk_010906e0;
  if (*(int *)(g_unk_01047b00 + 0xfc) < 0x28) {
    tmp_f1 = 1.0;
  }
  else {
    tmp_f1 = 40.0 / (float)*(int *)(g_unk_01047b00 + 0xfc);
  }
  tmp_f1 = (float)param_3 * tmp_f1;
  if (tmp_f1 < 5.0) {
    tmp_f1 = 5.0;
  }
  else if (10.0 < tmp_f1) {
    tmp_f1 = 10.0;
  }
  if (g_unk_010aac44 + g_unk_010aac40 < g_unk_010906e0) {
    tmp_i10 = 0;
  }
  else if (g_unk_010aac58 + g_unk_010aac54 < g_unk_010906e0) {
    tmp_i10 = 1;
  }
  else if (g_unk_010aac6c + g_unk_010aac68 < g_unk_010906e0) {
    tmp_i10 = 2;
  }
  else if (g_unk_010aac80 + g_unk_010aac7c < g_unk_010906e0) {
    tmp_i10 = 3;
  }
  else if (g_unk_010aac94 + g_unk_010aac90 < g_unk_010906e0) {
    tmp_i10 = 4;
  }
  else if (g_unk_010aaca8 + g_unk_010aaca4 < g_unk_010906e0) {
    tmp_i10 = 5;
  }
  else if (g_unk_010aacbc + g_unk_010aacb8 < g_unk_010906e0) {
    tmp_i10 = 6;
  }
  else {
    if (g_unk_010906e0 <= g_unk_010aacd0 + g_unk_010aaccc) {
      return;
    }
    tmp_i10 = 7;
  }
  if ((param_1 == 0xff) && (param_2 == 0xff)) {
    g_unk_010aad44 = -tmp_f1;
    (&g_unk_010aac48)[tmp_i10 * 5] = 0;
    (&g_unk_010aac4c)[tmp_i10 * 5] = 0;
    g_unk_010aad48 = 0.0;
  }
  else {
    local_20 = 0;
    local_28 = ((float)param_2 / 255.0) * 360.0;
    local_24 = ((float)param_1 / 255.0) * 360.0;
    AngleVectors(&local_28,&local_34,0,0);
    local_34 = vec3_origin - local_34;
    local_30 = g_unk_00c22b14 - local_30;
    tmp_f3 = g_unk_00c22b18 - local_2c;
    local_2c = 0.0;
    local_60 = g_unk_010918d4 * tmp_f3 + g_unk_010918d0 * local_30 + g_unk_010918cc * local_34;
    tmp_f4 = g_unk_010918e0 * tmp_f3 + g_unk_010918dc * local_30 + g_unk_010918d8 * local_34;
    tmp_f2 = local_34 * g_unk_010918e4;
    tmp_f5 = local_30 * g_unk_010918e8;
    tmp_f3 = tmp_f3 * g_unk_010918ec;
    local_34 = local_60;
    local_30 = tmp_f4;
    tmp_l11 = (long double)VectorLength(&local_34);
    if (tmp_l11 < (long double)0.1) {
      tmp_l11 = (long double)0.1;
    }
    g_unk_010aad48 = tmp_f4 * tmp_f1;
    g_unk_010aad44 = -tmp_f1 * local_60;
    if (local_60 <= 0.1) {
      local_60 = 0.1;
    }
    tmp_u7 = rand();
    tmp_f6 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
    (&g_unk_010aac48)[tmp_i10 * 5] = -tmp_f4 / local_60 + (tmp_f6 + tmp_f6) * 0.3;
    tmp_u7 = rand();
    tmp_i9 = g_unk_010906e0;
    tmp_i8 = g_unk_01047b00;
    tmp_f4 = (float)(tmp_u7 & 0x7fff) / 32767.0 - 0.5;
    (&g_unk_010aac4c)[tmp_i10 * 5] = (tmp_f3 + tmp_f5 + tmp_f2) / (float)tmp_l11 + (tmp_f4 + tmp_f4) * 0.3;
  }
  if ((float)(&g_unk_010aac48)[tmp_i10 * 5] <= 1.0) {
    if ((float)(&g_unk_010aac48)[tmp_i10 * 5] < -1.0) {
      (&g_unk_010aac48)[tmp_i10 * 5] = 0xbf800000;
    }
  }
  else {
    (&g_unk_010aac48)[tmp_i10 * 5] = 0x3f800000;
  }
  if ((float)(&g_unk_010aac4c)[tmp_i10 * 5] <= 1.0) {
    if ((float)(&g_unk_010aac4c)[tmp_i10 * 5] < -1.0) {
      (&g_unk_010aac4c)[tmp_i10 * 5] = 0xbf800000;
    }
  }
  else {
    (&g_unk_010aac4c)[tmp_i10 * 5] = 0x3f800000;
  }
  if (10.0 < tmp_f1) {
    tmp_f2 = 500.0;
    tmp_f1 = 10.0;
  }
  else {
    tmp_f2 = tmp_f1 * 50.0;
  }
  (&g_unk_010aac50)[tmp_i10 * 5] = tmp_f1;
  g_unk_010aad40 = (float)(tmp_i9 + 500);
  (&g_unk_010aac40)[tmp_i10 * 5] = *(uint32_t *)(tmp_i8 + 8);
  if (((float)(&g_unk_010aac48)[tmp_i10 * 5] == 0.0) && ((float)(&g_unk_010aac4c)[tmp_i10 * 5] == 0.0)) {
    tmp_f1 = 3.0;
  }
  else {
    tmp_f1 = 1.0;
  }
  (&g_unk_010aac44)[tmp_i10 * 5] = (int)ROUND(tmp_f1 * tmp_f2);
  g_unk_010aace4 = tmp_i10;
  g_unk_010aace0 = (float)*(int *)(tmp_i8 + 8);
  return;
}

char * CG_TeamnameForNumber(int param_1)
{
  if (param_1 == 1) {
    return "axis";
  }
  if (param_1 == 0) {
    return "free";
  }
  if (param_1 == 2) {
    return "allies";
  }
  if (param_1 == 3) {
    return "spectator";
  }
  return "^1ERROR";
}

void CG_Respawn(int param_1)
{
  uint tmp_u1;
  int tmp_i2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  uint tmp_u5;
  
  g_unk_010906d4 = 1;
  g_unk_010b4558 = 0;
  tmp_u5 = ~g_unk_01090b7c;
  tmp_u1 = PM_IdleAnimForWeapon(*(uint32_t *)(g_unk_01047b00 + 0xd0));
  g_unk_010aaecc = 0;
  g_unk_01090b7c = tmp_u5 & 0x200 | tmp_u1;
  g_unk_010907a4 = 0;
  g_unk_010aac34 = g_unk_010906e0;
  g_unk_010aac08 = 0;
  g_unk_010aac0c = 0;
  g_unk_010ef670 = 0;
  g_unk_010ef66c = 0;
  g_unk_01091814 = *(uint32_t *)(g_unk_01047b00 + 0xd0);
  g_unk_01091a64 = 0;
  g_unk_01091a68 = 0;
  g_unk_01091a74 = 0;
  g_unk_01091a6c = 0;
  g_unk_01091a78 = 0;
  g_unk_010aad14 = 0;
  g_unk_010aad0c = 0;
  g_unk_010aad04 = 0;
  trap_SendConsoleCommand("-zoom\n");
  g_unk_010b3b24 = 0;
  tmp_u1 = 0;
  g_unk_010ee05c = 0;
  do {
    *(uint32_t *)((int)&g_unk_010b1668 + tmp_u1) = 0;
    *(uint32_t *)((int)&g_unk_010b166c + tmp_u1) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x90);
  g_unk_010b1668 = (uint)(0 < (int)GHIDRA_FIELD(cg_autoReload, 12, 4));
  g_unk_010b16e8 = (uint)(0 < (int)GHIDRA_FIELD(cg_weapAltReloads, 12, 4));
  g_unk_010b1678 = 20000;
  if (param_1 == 0) {
    GHIDRA_FIELD(cgs, 33701708, 4) = 0;
    if (g_unk_010907e0 != 4) goto LAB_000a8639;
  }
  else if (g_unk_010907e0 != 4) {
    g_unk_010b3b2c = 0;
    trap_R_SetFog(10,4,0x14,0,0,0,0);
    return;
  }
  g_unk_010b1674 = 1;
LAB_000a8639:
  g_unk_010b3b2c = 0;
  trap_R_SetFog(10,4,0x14,0,0,0,0);
  if ((param_1 == 0) && (g_unk_01047aec == 0)) {
    tmp_i2 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
    if ((tmp_i2 - 1U < 2) && (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94b8) != oldCls_12006)) {
      tmp_u4 = BG_ClassnameForNumber_Filename(*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94b8));
      tmp_u4 = va("autoexec_%s",tmp_u4);
      CG_execFile(tmp_u4);
      oldCls_12006 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x94b8);
      tmp_i2 = *(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
    }
    if (tmp_i2 != oldTeam_12005) {
      if (tmp_i2 == 1) {
        tmp_pc3 = "axis";
      }
      else if (tmp_i2 == 0) {
        tmp_pc3 = "free";
      }
      else if (tmp_i2 == 2) {
        tmp_pc3 = "allies";
      }
      else if (tmp_i2 == 3) {
        tmp_pc3 = "spectator";
      }
      else {
        tmp_pc3 = "^1ERROR";
      }
      tmp_u4 = va("autoexec_%s",tmp_pc3);
      CG_execFile(tmp_u4);
      oldTeam_12005 = *(uint32_t *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494);
      return;
    }
  }
  return;
}

void CG_CheckPlayerstateEvents(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  int local_24;
  uint local_20;
  
  local_24 = *(int *)(param_1 + 0x6c);
  tmp_u3 = local_24 - 4;
  do {
    if ((int)tmp_u3 < *(int *)(param_2 + 0x6c)) {
      if (*(int *)(param_2 + 0x6c) + -3 <= (int)tmp_u3) {
        tmp_i1 = (tmp_u3 & 3) + 0x1c;
        tmp_i2 = *(int *)(param_1 + tmp_i1 * 4);
        if (tmp_i2 != *(int *)(param_2 + tmp_i1 * 4)) goto LAB_000a8881;
      }
    }
    else {
      tmp_i2 = *(int *)(param_1 + ((tmp_u3 & 3) + 0x1c) * 4);
LAB_000a8881:
      local_20 = tmp_u3 & 3;
      g_unk_01090d64 = *(uint32_t *)(param_1 + (local_20 + 0x20) * 4);
      g_unk_01090d60 = tmp_i2;
      CG_EntityEvent(&g_unk_01090ca8,&g_unk_0109143c);
      g_unk_010917b4 = g_unk_010917b4 + 1;
      *(int *)(&g_unk_010917b8 + (tmp_u3 & 0xf) * 4) = tmp_i2;
      local_24 = *(int *)(param_1 + 0x6c);
    }
    tmp_u3 = tmp_u3 + 1;
    if (local_24 <= (int)tmp_u3) {
      return;
    }
  } while( true );
}

void CG_CheckChangedPredictableEvents(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  
  tmp_i4 = *(int *)(param_1 + 0x6c);
  tmp_u6 = tmp_i4 - 4;
  do {
    if (((int)tmp_u6 < g_unk_010917b4) && (g_unk_010917b4 + -0xf <= (int)tmp_u6)) {
      tmp_i5 = (tmp_u6 & 0xf) + 0x1273c;
      tmp_i1 = param_1 + (tmp_u6 & 3) * 4;
      tmp_i2 = *(int *)(tmp_i1 + 0x70);
      if (tmp_i2 != (&g_unk_01047ac8)[tmp_i5]) {
        g_unk_01090d64 = *(uint32_t *)(tmp_i1 + 0x80);
        g_unk_01090d60 = tmp_i2;
        CG_EntityEvent(&g_unk_01090ca8,&g_unk_0109143c);
        tmp_u3 = GHIDRA_FIELD(cg_showmiss, 12, 4);
        (&g_unk_01047ac8)[tmp_i5] = tmp_i2;
        if (tmp_u3 != 0) {
          CG_Printf("WARNING: changed predicted event\n");
        }
        tmp_i4 = *(int *)(param_1 + 0x6c);
      }
    }
    tmp_u6 = tmp_u6 + 1;
  } while ((int)tmp_u6 < tmp_i4);
  return;
}

void CG_CheckLocalSounds(int param_1,int param_2)
{
  float tmp_f1;
  int tmp_i2;
  int tmp_i3;
  
  if (GHIDRA_FIELD(cg_hitSounds, 12, 4) != 0) {
    if (*(int *)(param_2 + 0x118) < *(int *)(param_1 + 0x118)) {
      trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),3,GHIDRA_FIELD(cgs, 132004, 4));
    }
    if (*(int *)(param_2 + 0x114) < *(int *)(param_1 + 0x114)) {
      trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),3,GHIDRA_FIELD(cgs, 131996, 4));
    }
  }
  if (GHIDRA_FIELD(cgs, 27388, 4) - 7 < 2) {
    return;
  }
  if ((float)GHIDRA_FIELD(cgs, 27396, 4) <= 0.0) {
    return;
  }
  if (GHIDRA_FIELD(cgs, 33525356, 4) != 0) {
    return;
  }
  tmp_i2 = g_unk_010906e0 - GHIDRA_FIELD(cgs, 28480, 4);
  if ((5.0 < (float)GHIDRA_FIELD(cgs, 27396, 4)) && ((g_unk_010906ec & 1) == 0)) {
    tmp_f1 = ((float)GHIDRA_FIELD(cgs, 27396, 4) - 5.0) * 60.0 * 1000.0;
    if ((tmp_f1 < (float)tmp_i2) && ((float)tmp_i2 < tmp_f1 + 1000.0)) {
      g_unk_010906ec = g_unk_010906ec | 1;
      if (*(int *)(param_1 + 300) == 1) {
        tmp_i3 = GHIDRA_FIELD(cgs, 69452, 4);
        if (GHIDRA_FIELD(cgs, 69452, 4) == -1) {
          CG_SoundPlaySoundScript(&g_unk_010b14e8,0,0xffffffff,1);
        }
        else {
LAB_000a8aef:
          if (tmp_i3 != 0) {
            trap_S_StartLocalSound(tmp_i3,7);
          }
        }
      }
      else if (*(int *)(param_1 + 300) == 2) {
        tmp_i3 = GHIDRA_FIELD(cgs, 69456, 4);
        if (GHIDRA_FIELD(cgs, 69456, 4) != -1) goto LAB_000a8aef;
        CG_SoundPlaySoundScript(&g_unk_010b1528,0,0xffffffff,1);
      }
    }
  }
  if ((2.0 < (float)GHIDRA_FIELD(cgs, 27396, 4)) && ((g_unk_010906ec & 2) == 0)) {
    tmp_f1 = ((float)GHIDRA_FIELD(cgs, 27396, 4) - 2.0) * 60.0 * 1000.0;
    if ((tmp_f1 < (float)tmp_i2) && ((float)tmp_i2 < tmp_f1 + 1000.0)) {
      g_unk_010906ec = g_unk_010906ec | 2;
      if (*(int *)(param_1 + 300) == 1) {
        tmp_i3 = GHIDRA_FIELD(cgs, 69460, 4);
        if (GHIDRA_FIELD(cgs, 69460, 4) == -1) {
          CG_SoundPlaySoundScript(&g_unk_010b1568,0,0xffffffff,1);
          goto LAB_000a8be0;
        }
      }
      else {
        if (*(int *)(param_1 + 300) != 2) goto LAB_000a8be0;
        tmp_i3 = GHIDRA_FIELD(cgs, 69464, 4);
        if (GHIDRA_FIELD(cgs, 69464, 4) == -1) {
          CG_SoundPlaySoundScript(&g_unk_010b15a8,0,0xffffffff,1);
          goto LAB_000a8be0;
        }
      }
      if (tmp_i3 != 0) {
        trap_S_StartLocalSound(tmp_i3,7);
      }
    }
  }
LAB_000a8be0:
  if ((g_unk_010906ec & 4) == 0) {
    tmp_f1 = (float)GHIDRA_FIELD(cgs, 27396, 4) * 60.0 * 1000.0;
    if ((tmp_f1 - 30000.0 < (float)tmp_i2) && ((float)tmp_i2 < tmp_f1 - 29000.0)) {
      g_unk_010906ec = g_unk_010906ec | 4;
      if (*(int *)(param_1 + 300) == 1) {
        tmp_i2 = GHIDRA_FIELD(cgs, 69468, 4);
        if (GHIDRA_FIELD(cgs, 69468, 4) == -1) {
          CG_SoundPlaySoundScript(&g_unk_010b15e8,0,0xffffffff,1);
          return;
        }
      }
      else {
        if (*(int *)(param_1 + 300) != 2) {
          return;
        }
        tmp_i2 = GHIDRA_FIELD(cgs, 69472, 4);
        if (GHIDRA_FIELD(cgs, 69472, 4) == -1) {
          CG_SoundPlaySoundScript(&g_unk_010b1628,0,0xffffffff,1);
          return;
        }
      }
      if (tmp_i2 != 0) {
        trap_S_StartLocalSound(tmp_i2,7);
      }
    }
  }
  return;
}

uint8_t * CG_PB_FindFreePolyBuffer(int param_1,int param_2,int param_3)
{
  int *tmp_pi1;
  int tmp_i2;
  
  tmp_i2 = 0;
  tmp_pi1 = (int *)(cg_polyBuffers + 0xd03c);
  while ((((*tmp_pi1 != param_1 || ((&cg_polyBuffersInuse)[tmp_i2] == 0)) ||
          (0x1805 < tmp_pi1[-1] + param_3)) || (0x400 < tmp_pi1[-0x1808] + param_2))) {
    tmp_i2 = tmp_i2 + 1;
    tmp_pi1 = tmp_pi1 + 0x3410;
    if (tmp_i2 == 0x80) {
      tmp_i2 = 0;
      do {
        if ((&cg_polyBuffersInuse)[tmp_i2] == 0) {
          (&cg_polyBuffersInuse)[tmp_i2] = 1;
          tmp_i2 = tmp_i2 * 0xd040;
          *(int *)(cg_polyBuffers + tmp_i2 + 0xd03c) = param_1;
          *(uint32_t *)(cg_polyBuffers + tmp_i2 + 0xd038) = 0;
          *(uint32_t *)(cg_polyBuffers + tmp_i2 + 0x701c) = 0;
          return cg_polyBuffers + tmp_i2;
        }
        tmp_i2 = tmp_i2 + 1;
      } while (tmp_i2 != 0x80);
      return (uint8_t *)0x0;
    }
  }
  (&cg_polyBuffersInuse)[tmp_i2] = 1;
  *(int *)(cg_polyBuffers + tmp_i2 * 0xd040 + 0xd03c) = param_1;
  return cg_polyBuffers + tmp_i2 * 0xd040;
}

void CG_PB_ClearPolyBuffers(void)
{
  uint tmp_u1;
  
  tmp_u1 = 0;
  do {
    *(uint32_t *)((int)&cg_polyBuffersInuse + tmp_u1) = 0;
    *(uint32_t *)((int)&g_unk_034fcf64 + tmp_u1) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x200);
  return;
}

void CG_PB_RenderPolyBuffers(void)
{
  uint32_t *tmp_pu1;
  uint32_t *tmp_pu2;
  int *tmp_pi3;
  
  tmp_pi3 = &cg_polyBuffersInuse;
  tmp_pu1 = (uint32_t *)cg_polyBuffers;
  do {
    while (*tmp_pi3 != 0) {
      tmp_pu2 = tmp_pu1 + 0x3410;
      tmp_pi3 = tmp_pi3 + 1;
      trap_R_AddPolyBufferToScene(tmp_pu1);
      tmp_pu1 = tmp_pu2;
      if (tmp_pu2 == &cg_pmOldList) {
        return;
      }
    }
    tmp_pu1 = tmp_pu1 + 0x3410;
    tmp_pi3 = tmp_pi3 + 1;
  } while (tmp_pu1 != &cg_pmOldList);
  return;
}

void CG_UpdatePMLists(void)
{
  int *tmp_pi1;
  int *tmp_pi2;
  int tmp_i3;
  int tmp_i4;
  uint32_t tmp_u5;
  int tmp_i6;
  
  tmp_i4 = cg_pmWaitingList;
  if ((cg_pmWaitingList == 0) || (g_unk_010906e0 <= *(int *)(cg_pmWaitingList + 8))) {
LAB_000a96f2:
    if (cg_pmOldList == 0) goto LAB_000a974f;
    tmp_i6 = *(int *)(cg_pmOldList + 0x124);
    tmp_i4 = cg_pmOldList;
  }
  else {
    tmp_i3 = *(int *)(cg_pmWaitingList + 0x124);
    if (tmp_i3 == 0) {
      if (*(int *)(cg_pmWaitingList + 8) + GHIDRA_FIELD(cg_popupFadeTime, 12, 4) + 0x5dc < g_unk_010906e0) {
        cg_pmWaitingList = 0;
        *(uint32_t *)(tmp_i4 + 4) = 0;
        *(uint32_t *)(tmp_i4 + 0x124) = 0;
      }
      goto LAB_000a96f2;
    }
    *(int *)(tmp_i3 + 8) = g_unk_010906e0;
    tmp_i6 = cg_pmOldList;
    cg_pmOldList = cg_pmWaitingList;
    tmp_pi1 = (int *)(cg_pmWaitingList + 0x124);
    cg_pmWaitingList = tmp_i3;
    *tmp_pi1 = tmp_i6;
  }
  if (*(int *)(tmp_i4 + 8) + GHIDRA_FIELD(cg_popupFadeTime, 12, 4) + 0x5dc < g_unk_010906e0) {
    cg_pmOldList = 0;
LAB_000a9858:
    while( true ) {
      *(uint32_t *)(tmp_i4 + 0x124) = 0;
      *(uint32_t *)(tmp_i4 + 4) = 0;
      if (tmp_i6 == 0) break;
      tmp_i4 = tmp_i6;
      tmp_i6 = *(int *)(tmp_i6 + 0x124);
    }
  }
  else {
    while (tmp_i3 = tmp_i6, tmp_i3 != 0) {
      if (*(int *)(tmp_i3 + 8) + GHIDRA_FIELD(cg_popupFadeTime, 12, 4) + 0x5dc < g_unk_010906e0) {
        *(uint32_t *)(tmp_i4 + 0x124) = 0;
        tmp_i4 = tmp_i3;
        tmp_i6 = *(int *)(tmp_i3 + 0x124);
        goto LAB_000a9858;
      }
      tmp_i4 = tmp_i3;
      tmp_i6 = *(int *)(tmp_i3 + 0x124);
    }
  }
LAB_000a974f:
  tmp_pi1 = cg_pmWaitingListBig;
  if ((cg_pmWaitingListBig != (int *)0x0) && (cg_pmWaitingListBig[2] < g_unk_010906e0)) {
    tmp_pi2 = (int *)cg_pmWaitingListBig[0x27];
    if (tmp_pi2 == (int *)0x0) {
      if (cg_pmWaitingListBig[2] + 0x1964 < g_unk_010906e0) {
        cg_pmWaitingListBig = (int *)0x0;
        tmp_pi1[1] = 0;
        tmp_pi1[0x27] = 0;
      }
    }
    else {
      tmp_pi2[2] = g_unk_010906e0;
      cg_pmWaitingListBig = tmp_pi2;
      if ((g_unk_01047b00 != 0) &&
         ((tmp_u5 = GHIDRA_FIELD(cgs, 69644, 4), *tmp_pi2 == 0 || (tmp_u5 = GHIDRA_FIELD(cgs, 69640, 4), *tmp_pi2 == 1)))) {
        trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),0,tmp_u5);
      }
      tmp_pi1[1] = 0;
      tmp_pi1[0x27] = 0;
    }
  }
  return;
}

uint32_t * CG_FindFreePMItem2(void)
{
  int tmp_i1;
  
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
    if (_DAT_03b81b04 != 0) {
      return (uint32_t *)0x0;
    }
    tmp_i1 = 7;
  }
  return &cg_pmStackBig + tmp_i1 * 0x28;
}

uint32_t * CG_FindFreePMItem(void)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  uint32_t *tmp_pu4;
  int *tmp_pi5;
  
  tmp_i2 = 0;
  tmp_pi5 = &g_unk_03b7f184;
  do {
    if (*tmp_pi5 == 0) {
      return &cg_pmStack + tmp_i2 * 0x4a;
    }
    tmp_i2 = tmp_i2 + 1;
    tmp_pi5 = tmp_pi5 + 0x4a;
  } while (tmp_i2 != 0x20);
  tmp_pu1 = cg_pmOldList;
  tmp_pu3 = cg_pmOldList;
  if (cg_pmOldList == (uint32_t *)0x0) {
    return (uint32_t *)0x0;
  }
  do {
    tmp_pu4 = tmp_pu3;
    tmp_pu3 = tmp_pu1;
    tmp_pu1 = (uint32_t *)tmp_pu3[0x49];
  } while ((uint32_t *)tmp_pu3[0x49] != (uint32_t *)0x0);
  if (cg_pmOldList == tmp_pu4) {
    cg_pmOldList = (uint32_t *)0x0;
  }
  else {
    tmp_pu4[0x49] = 0;
  }
  tmp_pu3[1] = 0;
  return tmp_pu3;
}

void CG_PMItemBigSound(int *param_1)
{
  uint32_t tmp_u1;
  
  if ((g_unk_01047b00 != 0) &&
     ((tmp_u1 = GHIDRA_FIELD(cgs, 69644, 4), *param_1 == 0 || (tmp_u1 = GHIDRA_FIELD(cgs, 69640, 4), *param_1 == 1)))) {
    trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),0,tmp_u1);
  }
  return;
}

uint32_t CG_GetPMItemText(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  int tmp_i4;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  switch(*(uint32_t *)(param_1 + 0x10c)) {
  case 0:
    if (*(int *)(param_1 + 0x110) == 0) {
      tmp_u1 = nitrox_ConfigString(*(int *)(param_1 + 0x114) + 0x261);
      tmp_u1 = Info_ValueForKey(tmp_u1,&g_unk_0010d2bf);
      tmp_u1 = va("Planted at %s.",tmp_u1);
      return tmp_u1;
    }
    if (*(int *)(param_1 + 0x110) == 1) {
      tmp_u1 = nitrox_ConfigString(*(int *)(param_1 + 0x114) + 0x261);
      tmp_u1 = Info_ValueForKey(tmp_u1,&g_unk_0010d2bf);
      tmp_u1 = va("Defused at %s.",tmp_u1);
      return tmp_u1;
    }
    break;
  case 1:
    if (*(int *)(param_1 + 0x110) == -1) {
      tmp_u1 = CG_ConfigString(*(int *)(param_1 + 0x114) + 0x350);
      return tmp_u1;
    }
    if (*(int *)(param_1 + 0x110) == 0) {
      tmp_u1 = nitrox_ConfigString(*(int *)(param_1 + 0x114) + 0x261);
      tmp_u1 = Info_ValueForKey(tmp_u1,&g_unk_0010d2bf);
      tmp_u1 = va("%s has been constructed.",tmp_u1);
      return tmp_u1;
    }
    break;
  case 2:
    if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == 3) {
      return 0;
    }
    if (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) == *(int *)(param_1 + 0x110)) {
      return 0;
    }
    local_30 = *(uint32_t *)(param_1 + 0x5c);
    local_2c = *(uint32_t *)(param_1 + 0x60);
    if ((GHIDRA_FIELD(cg_locations, 12, 4) & 4) != 0) {
      local_20 = *(uint32_t *)(param_1 + 100);
      local_28 = local_30;
      local_24 = local_2c;
      tmp_u1 = CG_GetLocationMsg(&local_28);
      if (((GHIDRA_FIELD(cg_locations, 12, 4) & 8) != 0) || (tmp_i4 = Q_stricmp(tmp_u1,"Unknown"), tmp_i4 != 0)) {
        if ((GHIDRA_FIELD(cg_locations, 12, 4) & 0x10) != 0) {
          tmp_u2 = BG_GetLocationString(&local_30);
          tmp_u2 = va(&g_unk_0011d97d,tmp_u2);
          Q_strcat(tmp_u1,0x40,tmp_u2);
        }
        goto LAB_000aa8b0;
      }
    }
    BG_GetLocationString(&local_30);
LAB_000aa8b0:
    tmp_u1 = BG_GetLocationString(param_1 + 0x5c);
    tmp_u1 = va("Spotted by %s^7 at %s",*(int *)(param_1 + 0x114) * 0x1a4 + 0x10f9274,tmp_u1);
    return tmp_u1;
  case 5:
    if (*(int *)(param_1 + 0xf4) == 0) {
      if ((*(int *)(param_1 + 0xac) != -1) &&
         (cgs[*(int *)(param_1 + 0xac) * 0x1a4 + 0x9414] != '\0')) {
        tmp_u1 = CG_ConfigString(*(int *)(param_1 + 0x114) + 0x350);
        tmp_u1 = va("%s ^ghas stolen %s!",*(int *)(param_1 + 0xac) * 0x1a4 + 0x10f9274,tmp_u1);
        return tmp_u1;
      }
      tmp_u1 = CG_ConfigString(*(int *)(param_1 + 0x114) + 0x350);
      if (*(int *)(param_1 + 0x110) == 2) {
        tmp_pc3 = "Allies";
      }
      else {
        tmp_pc3 = "Axis";
      }
      tmp_u1 = va("%s have stolen %s!",tmp_pc3,tmp_u1);
      return tmp_u1;
    }
    if (*(int *)(param_1 + 0xf4) == 1) {
      if ((*(int *)(param_1 + 0xac) != -1) &&
         (cgs[*(int *)(param_1 + 0xac) * 0x1a4 + 0x9414] != '\0')) {
        tmp_u1 = CG_ConfigString(*(int *)(param_1 + 0x114) + 0x350);
        tmp_u1 = va("%s ^ghas returned %s!",*(int *)(param_1 + 0xac) * 0x1a4 + 0x10f9274,tmp_u1);
        return tmp_u1;
      }
      tmp_u1 = CG_ConfigString(*(int *)(param_1 + 0x114) + 0x350);
      if (*(int *)(param_1 + 0x110) == 2) {
        tmp_pc3 = "Allies";
      }
      else {
        tmp_pc3 = "Axis";
      }
      tmp_u1 = va("%s have returned %s!",tmp_pc3,tmp_u1);
      return tmp_u1;
    }
    break;
  case 6:
    if (*(int *)(param_1 + 0xf4) == 0) {
      if (*(int *)(param_1 + 0x110) == 1) {
        tmp_pc3 = "Axis team";
      }
      else if (*(int *)(param_1 + 0x110) == 2) {
        tmp_pc3 = "Allied team";
      }
      else {
        tmp_pc3 = "Spectators";
      }
      tmp_u1 = va("%s^7 has joined the %s^7!",*(int *)(param_1 + 0x114) * 0x1a4 + 0x10f9274,tmp_pc3);
      return tmp_u1;
    }
    if (*(int *)(param_1 + 0xf4) == 1) {
      tmp_u1 = va("%s^7 disconnected",*(int *)(param_1 + 0x114) * 0x1a4 + 0x10f9274);
      return tmp_u1;
    }
  }
  return 0;
}

uint32_t CG_GetPMItemIcon(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = *(int *)(param_1 + 0x10c);
  if (tmp_i1 == 1) {
    if (*(int *)(param_1 + 0xf4) != 1) {
      return GHIDRA_FIELD(cgs, 131812, 4);
    }
    return GHIDRA_FIELD(cgs, 131816, 4);
  }
  if (tmp_i1 == 2) {
    if (*(int *)(param_1 + 0x110) != 1) {
      return GHIDRA_FIELD(cgs, 131824, 4);
    }
    return GHIDRA_FIELD(cgs, 131820, 4);
  }
  return *(uint32_t *)(cgs + tmp_i1 * 4 + 0x202b8);
}

void nitrox_AddGraphicObituary
               (char *param_1,uint32_t param_2,char *param_3,uint32_t *param_4,
               uint32_t param_5)

{
  char *__s;
  uint32_t *tmp_pu1;
  int tmp_i2;
  size_t tmp_s3;
  char *tmp_pc4;
  int *tmp_pi5;
  uint32_t *tmp_pu6;
  uint32_t *tmp_pu7;
  uint32_t *tmp_pu8;
  
  if ((((param_1 != (char *)0x0) && (*param_1 != '\0')) && (param_3 != (char *)0x0)) &&
     (*param_3 != '\0')) {
    tmp_pi5 = &g_unk_03b7f184;
    tmp_i2 = 0;
    do {
      if (*tmp_pi5 == 0) {
        tmp_pu8 = &cg_pmStack + tmp_i2 * 0x4a;
        goto LAB_000aaf33;
      }
      tmp_i2 = tmp_i2 + 1;
      tmp_pi5 = tmp_pi5 + 0x4a;
    } while (tmp_i2 != 0x20);
    tmp_pu1 = cg_pmOldList;
    tmp_pu6 = cg_pmOldList;
    if (cg_pmOldList != (uint32_t *)0x0) {
      do {
        tmp_pu8 = tmp_pu6;
        tmp_pu7 = tmp_pu1;
        tmp_pu1 = tmp_pu8;
        tmp_pu6 = (uint32_t *)tmp_pu8[0x49];
      } while ((uint32_t *)tmp_pu8[0x49] != (uint32_t *)0x0);
      if (cg_pmOldList == tmp_pu7) {
        cg_pmOldList = (uint32_t *)0x0;
      }
      else {
        tmp_pu7[0x49] = 0;
      }
      tmp_pu8[1] = 0;
LAB_000aaf33:
      tmp_pu8[0x45] = 0;
      __s = (char *)(tmp_pu8 + 3);
      tmp_pu8[1] = 1;
      tmp_pu8[0x48] = 0x3f800000;
      tmp_pu8[0x47] = 0x3f800000;
      tmp_pu8[0x43] = param_2;
      tmp_pu8[0x46] = 0x3f800000;
      tmp_pu8[0x44] = param_5;
      Q_strncpyz(__s,param_1,0x80);
      Q_strncpyz(tmp_pu8 + 0x23,param_3,0x80);
      if (param_4 != (uint32_t *)0x0) {
        tmp_pu8[0x46] = *param_4;
        tmp_pu8[0x47] = param_4[1];
        tmp_pu8[0x48] = param_4[2];
      }
      tmp_s3 = strlen(__s);
      if (*(char *)((int)tmp_pu8 + tmp_s3 + 0xb) == '\n') {
        *(uint8_t *)((int)tmp_pu8 + tmp_s3 + 0xb) = 0;
        tmp_s3 = strlen(__s);
      }
      if (*(char *)((int)tmp_pu8 + tmp_s3 + 0x8b) == '\n') {
        tmp_s3 = strlen((char *)(tmp_pu8 + 0x23));
        *(uint8_t *)((int)tmp_pu8 + tmp_s3 + 0x8b) = 0;
      }
      while (tmp_pc4 = strchr(__s,10), tmp_pc4 != (char *)0x0) {
        *tmp_pc4 = '\0';
      }
      if (*(char *)(tmp_pu8 + 3) != '\0') {
        tmp_pu1 = cg_pmWaitingList;
        if (cg_pmWaitingList == (uint32_t *)0x0) {
          cg_pmWaitingList = tmp_pu8;
          tmp_pu8[2] = g_unk_010906e0;
        }
        else {
          do {
            tmp_pu6 = tmp_pu1;
            tmp_pu1 = (uint32_t *)tmp_pu6[0x49];
          } while (tmp_pu1 != (uint32_t *)0x0);
          tmp_pu6[0x49] = tmp_pu8;
        }
      }
    }
  }
  return;
}

void CG_TraceCapsule_World
               (int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  uint tmp_u1;
  float local_44 [16];
  
  trap_CM_CapsuleTrace(local_44,param_2,param_5,param_3,param_4,0,param_7);
  if (local_44[2] == 1.0) {
    local_44[0xd] = 1.43353e-42;
  }
  else {
    local_44[0xd] = 1.43213e-42;
  }
  tmp_u1 = 0;
  do {
    *(uint32_t *)(param_1 + tmp_u1) = *(uint32_t *)((int)local_44 + tmp_u1);
    tmp_u1 = tmp_u1 + 4;
  } while (tmp_u1 < 0x38);
  return;
}

uint CG_SortPlayersByKD(int *param_1,int *param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  
  tmp_i1 = *(int *)(&g_unk_01091ec4 + *param_2 * 0x28);
  tmp_i2 = *(int *)(&g_unk_01091ec4 + *param_1 * 0x28);
  if (tmp_i2 == tmp_i1 || tmp_i2 < tmp_i1) {
    tmp_u3 = 1;
    if ((tmp_i2 < tmp_i1) || (tmp_u3 = 0, tmp_i2 != tmp_i1)) {
      return tmp_u3;
    }
    if (*(int *)(&g_unk_01091ec8 + *param_2 * 0x28) <= *(int *)(&g_unk_01091ec8 + *param_1 * 0x28)) {
      return (uint)(*(int *)(&g_unk_01091ec8 + *param_2 * 0x28) <
                   *(int *)(&g_unk_01091ec8 + *param_1 * 0x28));
    }
  }
  return 0xffffffff;
}

void CG_printFile_part_0(uint32_t param_1)
{
  uint tmp_u1;
  uint tmp_u2;
  uint *tmp_pu3;
  uint *tmp_pu4;
  uint local_40c [256];
  uint32_t uStack_c;
  
  uStack_c = 0xb1791;
  BG_cleanName(param_1,local_40c,0x400,1);
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
                GHIDRA_FIELD(cgs, 33576008, 4));
  return;
}

void CG_printFile(uint32_t param_1)
{
  CG_Printf(param_1);
  if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
    CG_printFile_part_0();
    return;
  }
  return;
}

void CG_parseWeaponStats_cmd_constprop_5(void)
{
  int tmp_i1;
  float tmp_f2;
  bool tmp_b3;
  char *tmp_pc4;
  long tmp_l5;
  long tmp_l6;
  uint tmp_u7;
  uint32_t tmp_u8;
  uint tmp_u9;
  uint tmp_u10;
  char *tmp_pc11;
  char *tmp_pc12;
  long tmp_l13;
  char *__nptr;
  long tmp_l14;
  uint8_t *tmp_pu15;
  int tmp_i16;
  uint *tmp_pu17;
  uint *tmp_pu18;
  int tmp_i19;
  int *tmp_pi20;
  uint32_t *tmp_pu21;
  int tmp_i22;
  uint *local_84c;
  uint8_t local_81c [1024];
  uint local_41c [258];
  uint32_t uStack_14;
  
  uStack_14 = 0xb1d2e;
  tmp_pc4 = (char *)CG_Argv(1);
  tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
  tmp_pc4 = (char *)CG_Argv(2);
  tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
  tmp_pc4 = (char *)CG_Argv(3);
  tmp_u7 = strtol(tmp_pc4,(char **)0x0,10);
  tmp_i16 = tmp_l5 * 0x1a4 + 0x10f9274;
  Q_strncpyz(local_81c,tmp_i16);
  BG_cleanName(tmp_i16,local_81c,0x400,0);
  tmp_pc4 = "s";
  if (tmp_l6 == 1) {
    tmp_pc4 = "";
  }
  tmp_u8 = va("^7Overall stats for: ^3%s ^7(^2%d^7 Round%s)\n\n",local_81c,tmp_l6,tmp_pc4);
  CG_Printf(tmp_u8);
  if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
    tmp_pc4 = (char *)0x1;
    BG_cleanName(tmp_u8,local_41c,0x400,1);
    tmp_pu18 = local_41c;
    do {
      tmp_pu17 = tmp_pu18;
      tmp_u9 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
      tmp_u10 = tmp_u9 & 0x80808080;
      tmp_pu18 = tmp_pu17 + 1;
    } while (tmp_u10 == 0);
    if ((tmp_u9 & 0x8080) == 0) {
      tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
      tmp_u10 = tmp_u10 >> 0x10;
    }
    trap_FS_Write(local_41c,
                  (int)tmp_pu18 + ((-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)) - (int)local_41c));
  }
  CG_Printf("Weapon     Acrcy Hits/Atts Kills Deaths Headshots\n");
  if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
    tmp_pc4 = (char *)0x1;
    BG_cleanName("Weapon     Acrcy Hits/Atts Kills Deaths Headshots\n",local_41c,0x400,1);
    tmp_pu18 = local_41c;
    do {
      tmp_pu17 = tmp_pu18;
      tmp_u9 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
      tmp_u10 = tmp_u9 & 0x80808080;
      tmp_pu18 = tmp_pu17 + 1;
    } while (tmp_u10 == 0);
    if ((tmp_u9 & 0x8080) == 0) {
      tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
      tmp_u10 = tmp_u10 >> 0x10;
    }
    trap_FS_Write(local_41c,
                  (int)tmp_pu18 + ((-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)) - (int)local_41c));
  }
  CG_Printf("-------------------------------------------------\n");
  if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
    tmp_pc4 = (char *)0x1;
    BG_cleanName("-------------------------------------------------\n",local_41c,0x400,1);
    tmp_pu18 = local_41c;
    do {
      tmp_pu17 = tmp_pu18;
      tmp_u9 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
      tmp_u10 = tmp_u9 & 0x80808080;
      tmp_pu18 = tmp_pu17 + 1;
    } while (tmp_u10 == 0);
    if ((tmp_u9 & 0x8080) == 0) {
      tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
      tmp_u10 = tmp_u10 >> 0x10;
    }
    trap_FS_Write(local_41c,
                  (int)tmp_pu18 + ((-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)) - (int)local_41c));
  }
  if (tmp_u7 == 0) {
    CG_Printf("^3No weapon info available.\n");
    if ((int)GHIDRA_FIELD(cgs, 33576008, 4) < 1) {
      tmp_i19 = 4;
      tmp_i16 = 5;
    }
    else {
      tmp_pc4 = (char *)0x1;
      BG_cleanName("^3No weapon info available.\n",local_41c,0x400,1);
      tmp_pu18 = local_41c;
      do {
        tmp_pu17 = tmp_pu18;
        tmp_u10 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
        tmp_u7 = tmp_u10 & 0x80808080;
        tmp_pu18 = tmp_pu17 + 1;
      } while (tmp_u7 == 0);
      tmp_i16 = 5;
      if ((tmp_u10 & 0x8080) == 0) {
        tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
        tmp_u7 = tmp_u7 >> 0x10;
      }
      trap_FS_Write(local_41c,
                    (int)tmp_pu18 + ((-3 - (uint)CARRY1((byte)tmp_u7,(byte)tmp_u7)) - (int)local_41c));
      tmp_i19 = 4;
    }
  }
  else {
    tmp_pi20 = &aWeaponInfo;
    tmp_i16 = 0;
    tmp_b3 = false;
    tmp_i22 = 4;
    do {
      while ((tmp_u7 & 1 << ((byte)tmp_i16 & 0x1f)) == 0) {
LAB_000b2000:
        tmp_i16 = tmp_i16 + 1;
        tmp_pi20 = tmp_pi20 + 3;
        if (tmp_i16 == 0x1a) goto LAB_000b22a0;
      }
      tmp_pc11 = (char *)CG_Argv(tmp_i22);
      tmp_pc11 = (char *)strtol(tmp_pc11,(char **)0x0,10);
      tmp_pc12 = (char *)CG_Argv(tmp_i22 + 1);
      tmp_l6 = strtol(tmp_pc12,(char **)0x0,10);
      tmp_pc12 = (char *)CG_Argv(tmp_i22 + 2);
      tmp_l13 = strtol(tmp_pc12,(char **)0x0,10);
      tmp_i19 = tmp_i22 + 4;
      tmp_i1 = tmp_i22 + 3;
      tmp_i22 = tmp_i22 + 5;
      tmp_pc12 = (char *)CG_Argv(tmp_i1);
      tmp_pc12 = (char *)strtol(tmp_pc12,(char **)0x0,10);
      __nptr = (char *)CG_Argv(tmp_i19);
      tmp_l14 = strtol(__nptr,(char **)0x0,10);
      tmp_u8 = va("^3%-9s: ",tmp_pi20[2]);
      Q_strncpyz(local_81c,tmp_u8);
      if (((int)tmp_pc11 < 1) && (tmp_l6 < 1)) {
        tmp_u8 = va(&g_unk_0011d7e7);
        Q_strcat(local_81c,0x400);
        if ((0 < (int)tmp_pc12) || (0 < tmp_l13)) {
          tmp_b3 = true;
        }
      }
      else {
        if (tmp_l6 == 0) {
          tmp_f2 = 0.0;
        }
        else {
          tmp_f2 = ((float)(int)tmp_pc11 * 100.0) / (float)tmp_l6;
        }
        tmp_u8 = va("^7%5.1f ^5%4d/%-4d ",(double)tmp_f2,tmp_pc11,tmp_l6);
        Q_strcat(local_81c,0x400);
        tmp_b3 = true;
        tmp_pc4 = tmp_pc11;
      }
      tmp_pu15 = &g_unk_0011d841;
      if (*tmp_pi20 != 0) {
        tmp_pu15 = (uint8_t *)va(" ^3%9d",tmp_l14,tmp_u8,tmp_pc4);
      }
      tmp_u8 = va("%s^2%5d ^1%6d%s\n",local_81c,tmp_l13,tmp_pc12,tmp_pu15);
      CG_Printf(tmp_u8);
      tmp_pc4 = tmp_pc12;
      if ((int)GHIDRA_FIELD(cgs, 33576008, 4) < 1) goto LAB_000b2000;
      tmp_pc4 = (char *)0x1;
      BG_cleanName(tmp_u8,local_41c);
      tmp_pu18 = local_41c;
      do {
        tmp_pu17 = tmp_pu18;
        tmp_u9 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
        tmp_u10 = tmp_u9 & 0x80808080;
        tmp_pu18 = tmp_pu17 + 1;
      } while (tmp_u10 == 0);
      local_84c = local_41c;
      if ((tmp_u9 & 0x8080) == 0) {
        tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
        tmp_u10 = tmp_u10 >> 0x10;
      }
      tmp_pi20 = tmp_pi20 + 3;
      trap_FS_Write(local_84c,
                    (int)tmp_pu18 + ((-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)) - (int)local_84c)
                   );
      tmp_i16 = tmp_i16 + 1;
    } while (tmp_i16 != 0x1a);
LAB_000b22a0:
    if (tmp_b3) {
      tmp_pc11 = (char *)CG_Argv(tmp_i22);
      tmp_l6 = strtol(tmp_pc11,(char **)0x0,10);
      tmp_pc11 = (char *)CG_Argv(tmp_i22 + 1);
      tmp_l13 = strtol(tmp_pc11,(char **)0x0,10);
      tmp_i19 = tmp_i22 + 3;
      tmp_pc11 = (char *)CG_Argv(tmp_i22 + 2);
      strtol(tmp_pc11,(char **)0x0,10);
      tmp_u8 = va("\n^3Damage Given: ^7%-6d  ^3Team Damage: ^7%d\n",tmp_l6);
      CG_Printf(tmp_u8);
      if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
        tmp_pc4 = (char *)0x1;
        BG_cleanName(tmp_u8,local_41c,0x400,1);
        tmp_pu18 = local_41c;
        do {
          tmp_pu17 = tmp_pu18;
          tmp_u10 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
          tmp_u7 = tmp_u10 & 0x80808080;
          tmp_pu18 = tmp_pu17 + 1;
        } while (tmp_u7 == 0);
        if ((tmp_u10 & 0x8080) == 0) {
          tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
          tmp_u7 = tmp_u7 >> 0x10;
        }
        trap_FS_Write(local_41c,
                      (int)tmp_pu18 + ((-3 - (uint)CARRY1((byte)tmp_u7,(byte)tmp_u7)) - (int)local_41c)
                     );
      }
      tmp_u8 = va("^3Damage Recvd: ^7%d\n",tmp_l13);
      CG_Printf(tmp_u8);
      if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
        tmp_pc4 = (char *)0x1;
        BG_cleanName(tmp_u8,local_41c,0x400,1);
        tmp_pu18 = local_41c;
        do {
          tmp_pu17 = tmp_pu18;
          tmp_u10 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
          tmp_u7 = tmp_u10 & 0x80808080;
          tmp_pu18 = tmp_pu17 + 1;
        } while (tmp_u7 == 0);
        if ((tmp_u10 & 0x8080) == 0) {
          tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
          tmp_u7 = tmp_u7 >> 0x10;
        }
        trap_FS_Write(local_41c,
                      (int)tmp_pu18 + ((-3 - (uint)CARRY1((byte)tmp_u7,(byte)tmp_u7)) - (int)local_41c)
                     );
      }
      tmp_i16 = tmp_i22 + 4;
    }
    else {
      tmp_i16 = tmp_i22 + 1;
      tmp_i19 = tmp_i22;
    }
  }
  tmp_pc11 = (char *)CG_Argv(tmp_i19);
  tmp_l6 = 0;
  tmp_u7 = strtol(tmp_pc11,(char **)0x0,10);
  tmp_i19 = tmp_i16;
  if ((tmp_u7 & 1) != 0) {
    tmp_i19 = tmp_i16 + 1;
    tmp_pc11 = (char *)CG_Argv(tmp_i16);
    tmp_l6 = strtol(tmp_pc11,(char **)0x0,10);
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9500) = tmp_l6;
  }
  tmp_i16 = tmp_i19;
  if ((tmp_u7 & 2) != 0) {
    tmp_i16 = tmp_i19 + 1;
    tmp_pc11 = (char *)CG_Argv(tmp_i19);
    tmp_l13 = strtol(tmp_pc11,(char **)0x0,10);
    tmp_l6 = tmp_l6 + tmp_l13;
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9504) = tmp_l13;
  }
  tmp_i19 = tmp_i16;
  if ((tmp_u7 & 4) != 0) {
    tmp_i19 = tmp_i16 + 1;
    tmp_pc11 = (char *)CG_Argv(tmp_i16);
    tmp_l13 = strtol(tmp_pc11,(char **)0x0,10);
    tmp_l6 = tmp_l6 + tmp_l13;
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9508) = tmp_l13;
  }
  tmp_i16 = tmp_i19;
  if ((tmp_u7 & 8) != 0) {
    tmp_i16 = tmp_i19 + 1;
    tmp_pc11 = (char *)CG_Argv(tmp_i19);
    tmp_l13 = strtol(tmp_pc11,(char **)0x0,10);
    tmp_l6 = tmp_l6 + tmp_l13;
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x950c) = tmp_l13;
  }
  tmp_i19 = tmp_i16;
  if ((tmp_u7 & 0x10) != 0) {
    tmp_i19 = tmp_i16 + 1;
    tmp_pc11 = (char *)CG_Argv(tmp_i16);
    tmp_l13 = strtol(tmp_pc11,(char **)0x0,10);
    tmp_l6 = tmp_l6 + tmp_l13;
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9510) = tmp_l13;
  }
  tmp_i16 = tmp_i19;
  if ((tmp_u7 & 0x20) != 0) {
    tmp_i16 = tmp_i19 + 1;
    tmp_pc11 = (char *)CG_Argv(tmp_i19);
    tmp_l13 = strtol(tmp_pc11,(char **)0x0,10);
    tmp_l6 = tmp_l6 + tmp_l13;
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9514) = tmp_l13;
  }
  if ((tmp_u7 & 0x40) != 0) {
    tmp_pc11 = (char *)CG_Argv(tmp_i16);
    tmp_l13 = strtol(tmp_pc11,(char **)0x0,10);
    tmp_l6 = tmp_l6 + tmp_l13;
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9518) = tmp_l13;
  }
  if (*(int *)(cgs + tmp_l5 * 0x1a4 + 0x9494) == 1) {
    tmp_pu15 = rankNames_Axis;
  }
  else {
    tmp_pu15 = rankNames_Allies;
  }
  tmp_u8 = va("\n^2Rank: ^7%s (%d XP)\n",
             *(uint32_t *)(tmp_pu15 + *(int *)(cgs + tmp_l5 * 0x1a4 + 0x94c0) * 4),tmp_l6);
  CG_Printf(tmp_u8);
  if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
    tmp_pc4 = (char *)0x1;
    BG_cleanName(tmp_u8,local_41c,0x400,1);
    tmp_pu18 = local_41c;
    do {
      tmp_pu17 = tmp_pu18;
      tmp_u9 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
      tmp_u10 = tmp_u9 & 0x80808080;
      tmp_pu18 = tmp_pu17 + 1;
    } while (tmp_u10 == 0);
    if ((tmp_u9 & 0x8080) == 0) {
      tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
      tmp_u10 = tmp_u10 >> 0x10;
    }
    trap_FS_Write(local_41c,
                  (int)tmp_pu18 + ((-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)) - (int)local_41c),
                  GHIDRA_FIELD(cgs, 33576008, 4));
  }
  if (GHIDRA_FIELD(cgs, 27388, 4) == 4) {
    tmp_pc11 = "  Medals";
  }
  else {
    tmp_pc11 = "";
  }
  tmp_u8 = va("Skills         Level/Points%s\n",tmp_pc11);
  CG_Printf(tmp_u8);
  if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
    tmp_pc4 = (char *)0x1;
    BG_cleanName(tmp_u8,local_41c,0x400,1);
    tmp_pu18 = local_41c;
    do {
      tmp_pu17 = tmp_pu18;
      tmp_u9 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
      tmp_u10 = tmp_u9 & 0x80808080;
      tmp_pu18 = tmp_pu17 + 1;
    } while (tmp_u10 == 0);
    if ((tmp_u9 & 0x8080) == 0) {
      tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
      tmp_u10 = tmp_u10 >> 0x10;
    }
    trap_FS_Write(local_41c,
                  (int)tmp_pu18 + ((-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)) - (int)local_41c),
                  GHIDRA_FIELD(cgs, 33576008, 4));
  }
  if (GHIDRA_FIELD(cgs, 27388, 4) == 4) {
    tmp_pc11 = "--------";
  }
  else {
    tmp_pc11 = "";
  }
  tmp_u8 = va("---------------------------%s\n",tmp_pc11);
  CG_Printf(tmp_u8);
  if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
    tmp_pc4 = (char *)0x1;
    BG_cleanName(tmp_u8,local_41c,0x400,1);
    tmp_pu18 = local_41c;
    do {
      tmp_pu17 = tmp_pu18;
      tmp_u9 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
      tmp_u10 = tmp_u9 & 0x80808080;
      tmp_pu18 = tmp_pu17 + 1;
    } while (tmp_u10 == 0);
    if ((tmp_u9 & 0x8080) == 0) {
      tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
      tmp_u10 = tmp_u10 >> 0x10;
    }
    trap_FS_Write(local_41c,
                  (int)tmp_pu18 + ((-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)) - (int)local_41c),
                  GHIDRA_FIELD(cgs, 33576008, 4));
  }
  if (tmp_u7 == 0) {
    CG_Printf("^3No skills acquired!\n");
    if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
      BG_cleanName("^3No skills acquired!\n",local_41c,0x400,1);
      tmp_pu18 = local_41c;
      do {
        tmp_pu17 = tmp_pu18;
        tmp_u10 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
        tmp_u7 = tmp_u10 & 0x80808080;
        tmp_pu18 = tmp_pu17 + 1;
      } while (tmp_u7 == 0);
      if ((tmp_u10 & 0x8080) == 0) {
        tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
        tmp_u7 = tmp_u7 >> 0x10;
      }
      trap_FS_Write(local_41c,
                    (int)tmp_pu18 + ((-3 - (uint)CARRY1((byte)tmp_u7,(byte)tmp_u7)) - (int)local_41c),
                    GHIDRA_FIELD(cgs, 33576008, 4));
    }
  }
  else {
    tmp_i16 = 0;
    tmp_pu21 = (uint32_t *)(cgs + tmp_l5 * 0x1a4 + 0x9500);
    do {
      while ((tmp_u7 & 1 << ((byte)tmp_i16 & 0x1f)) != 0) {
        tmp_i19 = tmp_pu21[-7];
        if (tmp_i19 < 5) {
          tmp_pc4 = *(char **)(skillLevels + (tmp_i19 + 1 + tmp_i16 * 6) * 4);
          tmp_u8 = va("%d (%d/%d)",tmp_i19,*tmp_pu21,tmp_pc4);
        }
        else {
          tmp_u8 = va("%d (%d)",tmp_i19,*tmp_pu21,tmp_pc4);
        }
        if (GHIDRA_FIELD(cgs, 27388, 4) != 4) {
          tmp_u8 = va("%-14s ^3%-12s\n",(&skillNames)[tmp_i16],tmp_u8,tmp_pc4);
          CG_Printf(tmp_u8);
          if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
            tmp_pc4 = (char *)0x1;
            BG_cleanName(tmp_u8,local_41c);
            tmp_pu18 = local_41c;
            do {
              tmp_pu17 = tmp_pu18;
              tmp_u9 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
              tmp_u10 = tmp_u9 & 0x80808080;
              tmp_pu18 = tmp_pu17 + 1;
            } while (tmp_u10 == 0);
            if ((tmp_u9 & 0x8080) == 0) {
              tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
              tmp_u10 = tmp_u10 >> 0x10;
            }
            trap_FS_Write(local_41c,
                          (int)tmp_pu18 +
                          ((-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)) - (int)local_41c));
          }
          break;
        }
        tmp_pc4 = (char *)tmp_pu21[-0xe];
        tmp_u8 = va("%-14s ^3%-12s  ^2%6d\n",(&skillNames)[tmp_i16],tmp_u8,tmp_pc4);
        CG_Printf(tmp_u8);
        if ((int)GHIDRA_FIELD(cgs, 33576008, 4) < 1) break;
        tmp_pc4 = (char *)0x1;
        BG_cleanName(tmp_u8,local_41c);
        tmp_pu18 = local_41c;
        do {
          tmp_pu17 = tmp_pu18;
          tmp_u9 = *tmp_pu17 + 0xfefefeff & ~*tmp_pu17;
          tmp_u10 = tmp_u9 & 0x80808080;
          tmp_pu18 = tmp_pu17 + 1;
        } while (tmp_u10 == 0);
        if ((tmp_u9 & 0x8080) == 0) {
          tmp_pu18 = (uint *)((int)tmp_pu17 + 6);
          tmp_u10 = tmp_u10 >> 0x10;
        }
        tmp_pu21 = tmp_pu21 + 1;
        trap_FS_Write(local_41c,
                      (int)tmp_pu18 +
                      ((-3 - (uint)CARRY1((byte)tmp_u10,(byte)tmp_u10)) - (int)local_41c));
        tmp_i16 = tmp_i16 + 1;
        if (tmp_i16 == 7) {
          return;
        }
      }
      tmp_i16 = tmp_i16 + 1;
      tmp_pu21 = tmp_pu21 + 1;
    } while (tmp_i16 != 7);
  }
  return;
}

void CG_UpdateSkills(uint32_t param_1)
{
  uint32_t tmp_u1;
  
  tmp_u1 = Info_ValueForKey(param_1,&g_unk_00121e10);
  Q_strncpyz(0x31284b8,tmp_u1,0x100);
  tmp_u1 = Info_ValueForKey(param_1,"M");
  Q_strncpyz(0x31285b8,tmp_u1,0x100);
  tmp_u1 = Info_ValueForKey(param_1,"E");
  Q_strncpyz(0x31286b8,tmp_u1,0x100);
  tmp_u1 = Info_ValueForKey(param_1,"F");
  Q_strncpyz(0x31287b8,tmp_u1,0x100);
  tmp_u1 = Info_ValueForKey(param_1,&g_unk_00116f00);
  Q_strncpyz(0x31288b8,tmp_u1,0x100);
  tmp_u1 = Info_ValueForKey(param_1,"B");
  Q_strncpyz(0x31289b8,tmp_u1,0x100);
  tmp_u1 = Info_ValueForKey(param_1,"L");
  Q_strncpyz(0x3128ab8,tmp_u1,0x100);
  InitSkillLevelStructure(5);
  InitSkillLevelStructure(2);
  InitSkillLevelStructure(1);
  InitSkillLevelStructure(3);
  InitSkillLevelStructure(6);
  InitSkillLevelStructure(0);
  InitSkillLevelStructure();
  return;
}

int CG_OIDInfoForEntityNum(int param_1)
{
  int tmp_i1;
  int *tmp_pi2;
  
  tmp_i1 = 0;
  tmp_pi2 = (int *)(cgs + 0x2023f60);
  do {
    if (*tmp_pi2 == param_1) {
      return tmp_i1 * 0x60 + 0x3113db4;
    }
    tmp_i1 = tmp_i1 + 1;
    tmp_pi2 = tmp_pi2 + 0x18;
  } while (tmp_i1 != 0x12);
  return 0;
}

void CG_SetConfigValues(void)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  
  tmp_pc1 = (char *)CG_ConfigString(0xb);
  GHIDRA_FIELD(cgs, 28480, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_ConfigString(0x21);
  GHIDRA_FIELD(cgs, 28484, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_ConfigString(5);
  g_unk_010aac20 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_ConfigString(6);
  GHIDRA_FIELD(cgs, 27664, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_ConfigString(8);
  GHIDRA_FIELD(cgs, 27668, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_ConfigString(9);
  GHIDRA_FIELD(cgs, 27672, 4) = strtol(tmp_pc1,(char **)0x0,10);
  tmp_u2 = CG_ConfigString(7);
  Q_strncpyz(0x10f6a80,tmp_u2,0x100);
  tmp_pc1 = (char *)CG_ConfigString(0x16);
  g_unk_010aabec = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_ConfigString(0x17);
  g_unk_010aabf4 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_ConfigString(0x18);
  g_unk_010aabf0 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_u2 = CG_ConfigString(0x1c);
  CG_ParseReinforcementTimes(tmp_u2);
  return;
}

void CG_ShaderStateChanged(void)
{
  char *tmp_pc1;
  char *tmp_pc2;
  long tmp_l3;
  long tmp_l4;
  char *tmp_pc5;
  char local_ac [16];
  char local_9c [64];
  char local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0xb4709;
  tmp_pc1 = (char *)nitrox_ConfigString(0x220);
  while( true ) {
    if ((tmp_pc1 == (char *)0x0) || (*tmp_pc1 == '\0')) {
      return;
    }
    tmp_pc2 = strchr(tmp_pc1,0x3d);
    if (tmp_pc2 == (char *)0x0) {
      return;
    }
    if (*tmp_pc2 == '\0') break;
    tmp_pc5 = tmp_pc2 + 1;
    strncpy(local_9c,tmp_pc1,(int)tmp_pc2 - (int)tmp_pc1);
    local_9c[(int)tmp_pc2 - (int)tmp_pc1] = '\0';
    tmp_pc1 = strchr(tmp_pc5,0x3a);
    if (tmp_pc1 == (char *)0x0) {
      return;
    }
    if (*tmp_pc1 == '\0') {
      return;
    }
    tmp_pc2 = tmp_pc1 + 1;
    strncpy(local_5c,tmp_pc5,(int)tmp_pc1 - (int)tmp_pc5);
    local_5c[(int)tmp_pc1 - (int)tmp_pc5] = '\0';
    tmp_pc5 = strchr(tmp_pc2,0x40);
    if (tmp_pc5 == (char *)0x0) {
      return;
    }
    tmp_pc1 = tmp_pc5 + 1;
    strncpy(local_ac,tmp_pc2,(int)tmp_pc5 - (int)tmp_pc2);
    local_ac[(int)tmp_pc5 - (int)tmp_pc2] = '\0';
    tmp_l3 = strtol(local_5c,(char **)0x0,10);
    tmp_l4 = strtol(local_9c,(char **)0x0,10);
    trap_R_RemapShader((tmp_l4 + 0x1cd) * 0x40 + 0x10efe68,(tmp_l3 + 0x1cd) * 0x40 + 0x10efe68,
                       local_ac);
  }
  return;
}

void CG_LoadVoiceChats(void)
{
  int tmp_i1;
  
  GHIDRA_FIELD(voiceChatLists, 68, 4) = 0;
  GHIDRA_FIELD(voiceChatLists, 645324, 4) = 0;
  CG_ParseVoiceChats_constprop_4();
  CG_ParseVoiceChats_constprop_4();
  CG_Printf("Axis voice chat count = %i\n",GHIDRA_FIELD(voiceChatLists, 68, 4));
  CG_Printf("Allies voice chat count = %i\n",GHIDRA_FIELD(voiceChatLists, 645324, 4));
  tmp_i1 = trap_MemoryRemaining();
  if (tmp_i1 < 0) {
    tmp_i1 = tmp_i1 + 0x1fff;
  }
  CG_Printf("Voice chat memory remaining = %d kb\n",tmp_i1 >> 0xd);
  return;
}

uint32_t CG_GetVoiceChat(int param_1,uint32_t param_2,uint32_t *param_3,uint32_t *param_4,int *param_5,
               float param_6)

{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i3 = 0;
  tmp_i2 = param_1 + 0x48;
  if (0 < *(int *)(param_1 + 0x44)) {
    do {
      tmp_i1 = Q_stricmp(param_2,tmp_i2);
      if (tmp_i1 == 0) {
        tmp_i1 = (int)ROUND((float)*(int *)(param_1 + 0x88 + tmp_i3 * 0x944) * param_6);
        tmp_i2 = param_1 + (tmp_i3 * 0x251 + tmp_i1) * 4;
        *param_3 = *(uint32_t *)(tmp_i2 + 0x8c);
        *param_4 = *(uint32_t *)(tmp_i2 + 0x90c);
        *param_5 = param_1 + tmp_i3 * 0x944 + 0x4c + (tmp_i1 + 3) * 0x40;
        return 1;
      }
      tmp_i3 = tmp_i3 + 1;
      tmp_i2 = tmp_i2 + 0x944;
    } while (tmp_i3 < *(int *)(param_1 + 0x44));
  }
  return 0;
}

uint8_t * CG_VoiceChatListForClient(int param_1)
{
  if (*(int *)(cgs + param_1 * 0x1a4 + 0x9494) != 1) {
    return (uint8_t *)0x3c25228;
  }
  return voiceChatLists;
}

void CG_VoiceChat(int param_1)
{
  char *tmp_pc1;
  long tmp_l2;
  long tmp_l3;
  long tmp_l4;
  long tmp_l5;
  double tmp_d6;
  uint32_t tmp_u7;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_pc1 = (char *)CG_Argv(1);
  tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(2);
  tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)CG_Argv(3);
  tmp_l4 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_u7 = 5;
  if (param_1 != 0) {
    tmp_pc1 = (char *)CG_Argv(5);
    tmp_l5 = strtol(tmp_pc1,(char **)0x0,10);
    local_28 = (float)tmp_l5;
    tmp_pc1 = (char *)CG_Argv(6);
    tmp_l5 = strtol(tmp_pc1,(char **)0x0,10);
    local_24 = (float)tmp_l5;
    tmp_pc1 = (char *)CG_Argv(7);
    tmp_l5 = strtol(tmp_pc1,(char **)0x0,10);
    tmp_u7 = 8;
    local_20 = (float)tmp_l5;
  }
  tmp_pc1 = (char *)CG_Argv(tmp_u7);
  tmp_d6 = strtod(tmp_pc1,(char **)0x0);
  tmp_u7 = CG_Argv(4);
  CG_VoiceChatLocal(param_1,tmp_l2,tmp_l3,tmp_l4,tmp_u7,&local_28,(float)tmp_d6);
  return;
}

uint32_t * CG_LocalizeServerCommand(char *param_1)
{
  char *tmp_pc1;
  char tmp_c2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  char *tmp_pc6;
  int tmp_i7;
  size_t __n;
  bool tmp_b8;
  char local_41c [4];
  uint32_t auStack_418 [257];
  uint32_t uStack_14;
  
  tmp_u3 = 0;
  uStack_14 = 0xb62fb;
  do {
    *(uint32_t *)((int)&token_12660 + tmp_u3) = 0;
    *(uint32_t *)((int)&g_unk_002f3344 + tmp_u3) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0x400);
  tmp_c2 = *param_1;
  if (tmp_c2 == '\0') {
    tmp_i5 = 0;
    __n = 0;
  }
  else {
    tmp_i5 = 0;
    tmp_i7 = 0;
    tmp_b8 = true;
    tmp_pc6 = param_1;
    do {
      while ((tmp_c2 != '[' ||
             ((tmp_i4 = Q_strncmp(tmp_pc6,"[lon]",5), tmp_i4 != 0 &&
              (tmp_i4 = Q_strncmp(tmp_pc6,"[lof]",5), tmp_i4 != 0))))) {
        tmp_c2 = tmp_pc6[1];
        tmp_i7 = tmp_i7 + 1;
        tmp_pc6 = tmp_pc6 + 1;
        if (tmp_c2 == '\0') goto LAB_000b6430;
      }
      if (tmp_b8) {
        tmp_u3 = 0;
        do {
          tmp_pc1 = local_41c + tmp_u3;
          tmp_pc1[0] = '\0';
          tmp_pc1[1] = '\0';
          tmp_pc1[2] = '\0';
          tmp_pc1[3] = '\0';
          *(uint32_t *)((int)auStack_418 + tmp_u3) = 0;
          tmp_u3 = tmp_u3 + 8;
        } while (tmp_u3 < 0x400);
        strncpy(local_41c,param_1 + tmp_i5,tmp_i7 - tmp_i5);
        strcat((char *)&token_12660,local_41c);
      }
      else {
        strncat((char *)&token_12660,param_1 + tmp_i5,tmp_i7 - tmp_i5);
      }
      tmp_c2 = tmp_pc6[6];
      tmp_b8 = tmp_pc6[3] == 'n';
      tmp_pc6 = tmp_pc6 + 6;
      tmp_i5 = tmp_i7 + 5;
      tmp_i7 = tmp_i7 + 6;
    } while (tmp_c2 != '\0');
LAB_000b6430:
    __n = tmp_i7 - tmp_i5;
    if (!tmp_b8) {
      strncat((char *)&token_12660,param_1 + tmp_i5,__n);
      goto LAB_000b6457;
    }
  }
  tmp_u3 = 0;
  do {
    tmp_pc6 = local_41c + tmp_u3;
    tmp_pc6[0] = '\0';
    tmp_pc6[1] = '\0';
    tmp_pc6[2] = '\0';
    tmp_pc6[3] = '\0';
    *(uint32_t *)((int)auStack_418 + tmp_u3) = 0;
    tmp_u3 = tmp_u3 + 8;
  } while (tmp_u3 < 0x400);
  strncpy(local_41c,param_1 + tmp_i5,__n);
  strcat((char *)&token_12660,local_41c);
LAB_000b6457:
  return &token_12660;
}

void CG_topshotsParse_cmd(void)
{
  int tmp_i1;
  float tmp_f2;
  char *tmp_pc3;
  int tmp_i4;
  long tmp_l5;
  long tmp_l6;
  long tmp_l7;
  long tmp_l8;
  uint32_t tmp_u9;
  int tmp_i10;
  uint8_t local_3c [40];
  uint32_t uStack_14;
  
  uStack_14 = 0xb69ab;
  tmp_pc3 = (char *)CG_Argv(1);
  tmp_i4 = strtol(tmp_pc3,(char **)0x0,10);
  GHIDRA_FIELD(cgs, 33598836, 4) = 0;
  tmp_i10 = 2;
  while (tmp_i4 != 0) {
    tmp_pc3 = (char *)CG_Argv(tmp_i10);
    tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_pc3 = (char *)CG_Argv(tmp_i10 + 1);
    tmp_l6 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_pc3 = (char *)CG_Argv(tmp_i10 + 2);
    tmp_l7 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_pc3 = (char *)CG_Argv(tmp_i10 + 3);
    tmp_l8 = strtol(tmp_pc3,(char **)0x0,10);
    if (tmp_l7 < 1) {
      tmp_f2 = 0.0;
    }
    else {
      tmp_f2 = (float)(tmp_l6 * 100) / (float)tmp_l7;
    }
    tmp_i1 = tmp_i10 + 5;
    if ((int)GHIDRA_FIELD(cgs, 33598836, 4) < 0x34) {
      BG_cleanName(tmp_l5 * 0x1a4 + 0x10f9274,local_3c,0x11,0);
      tmp_u9 = va("%-12s %5.1f %4d/%-4d %5d  %s",(&g_ptr_s_Knife_001152df_0xc_0013b0e8)[tmp_i4 * 3 + -3]
                 ,(double)tmp_f2,tmp_l6,tmp_l7,tmp_l8,local_3c);
      tmp_i4 = GHIDRA_FIELD(cgs, 33598836, 4) * 0x100;
      GHIDRA_FIELD(cgs, 33598836, 4) = GHIDRA_FIELD(cgs, 33598836, 4) + 1;
      Q_strncpyz(tmp_i4 + 0x30f77d4,tmp_u9,0x100);
    }
    tmp_i10 = tmp_i10 + 6;
    tmp_pc3 = (char *)CG_Argv(tmp_i1);
    tmp_i4 = strtol(tmp_pc3,(char **)0x0,10);
  }
  return;
}

void CG_parseWeaponStatsGS_cmd(void)
{
  int tmp_i1;
  float tmp_f2;
  char *tmp_pc3;
  long tmp_l4;
  long tmp_l5;
  long tmp_l6;
  long tmp_l7;
  long tmp_l8;
  long tmp_l9;
  long tmp_l10;
  uint32_t tmp_u11;
  int tmp_i12;
  uint tmp_u13;
  uint8_t *tmp_pu14;
  int tmp_i15;
  int *tmp_pi16;
  int tmp_i17;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xb6d50;
  tmp_pc3 = (char *)CG_Argv(1);
  tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
  tmp_pc3 = (char *)CG_Argv(2);
  tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
  tmp_pc3 = (char *)CG_Argv(3);
  tmp_l6 = strtol(tmp_pc3,(char **)0x0,10);
  GHIDRA_FIELD(cgs, 33585492, 4) = 0;
  GHIDRA_FIELD(cgs, 33585496, 4) = 0;
  GHIDRA_FIELD(cgs, 33585500, 4) = 0;
  GHIDRA_FIELD(cgs, 33585504, 4) = tmp_l4;
  GHIDRA_FIELD(cgs, 33585508, 4) = tmp_l5;
  if (tmp_l6 == 0) {
    tmp_i15 = 5;
    tmp_i12 = 4;
  }
  else {
    tmp_pi16 = &aWeaponInfo;
    tmp_i17 = 4;
    tmp_i15 = 0;
    do {
      while ((tmp_l6 >> ((byte)tmp_i15 & 0x1f) & 1U) == 0) {
LAB_000b6e18:
        tmp_i15 = tmp_i15 + 1;
        tmp_pi16 = tmp_pi16 + 3;
        if (tmp_i15 == 0x1a) goto LAB_000b7038;
      }
      tmp_pc3 = (char *)CG_Argv(tmp_i17);
      tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pc3 = (char *)CG_Argv(tmp_i17 + 1);
      tmp_l7 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pc3 = (char *)CG_Argv(tmp_i17 + 2);
      tmp_l8 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_i12 = tmp_i17 + 4;
      tmp_i1 = tmp_i17 + 3;
      tmp_i17 = tmp_i17 + 5;
      tmp_pc3 = (char *)CG_Argv(tmp_i1);
      tmp_l9 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pc3 = (char *)CG_Argv(tmp_i12);
      tmp_l10 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_u11 = va("%-12s  ",tmp_pi16[2]);
      Q_strncpyz(local_41c,tmp_u11);
      if ((tmp_l5 < 1) && (tmp_l7 < 1)) {
        va(&g_unk_0011d7e7);
        Q_strcat(local_41c,0x400);
        if (*tmp_pi16 == 0) {
          tmp_u11 = va("%s%5d %6d%s",local_41c,tmp_l8,tmp_l9,&g_unk_0011d841);
          tmp_i12 = GHIDRA_FIELD(cgs, 33585492, 4) * 0x100;
          GHIDRA_FIELD(cgs, 33585492, 4) = GHIDRA_FIELD(cgs, 33585492, 4) + 1;
          Q_strncpyz(tmp_i12 + 0x30f52b4,tmp_u11);
        }
        else {
          tmp_u11 = va(&g_unk_0011da60,tmp_l10);
          tmp_u11 = va("%s%5d %6d%s",local_41c,tmp_l8,tmp_l9,tmp_u11);
          tmp_i12 = GHIDRA_FIELD(cgs, 33585492, 4) * 0x100;
          GHIDRA_FIELD(cgs, 33585492, 4) = GHIDRA_FIELD(cgs, 33585492, 4) + 1;
          Q_strncpyz(tmp_i12 + 0x30f52b4,tmp_u11);
        }
        if ((tmp_l9 == 0) && (tmp_l8 < 1)) goto LAB_000b6e18;
      }
      else {
        if (tmp_l7 == 0) {
          tmp_f2 = 0.0;
        }
        else {
          tmp_f2 = ((float)tmp_l5 * 100.0) / (float)tmp_l7;
        }
        tmp_u11 = va("%5.1f %4d/%-4d ",(double)tmp_f2,tmp_l5,tmp_l7);
        Q_strcat(local_41c,0x400);
        if (*tmp_pi16 == 0) {
          tmp_u11 = va("%s%5d %6d%s",local_41c,tmp_l8,tmp_l9,&g_unk_0011d841);
          tmp_i12 = GHIDRA_FIELD(cgs, 33585492, 4) * 0x100;
          GHIDRA_FIELD(cgs, 33585492, 4) = GHIDRA_FIELD(cgs, 33585492, 4) + 1;
          Q_strncpyz(tmp_i12 + 0x30f52b4,tmp_u11);
        }
        else {
          tmp_u11 = va(&g_unk_0011da60,tmp_l10,tmp_u11,tmp_l5,tmp_l7);
          tmp_u11 = va("%s%5d %6d%s",local_41c,tmp_l8,tmp_l9,tmp_u11);
          tmp_i12 = GHIDRA_FIELD(cgs, 33585492, 4) * 0x100;
          GHIDRA_FIELD(cgs, 33585492, 4) = GHIDRA_FIELD(cgs, 33585492, 4) + 1;
          Q_strncpyz(tmp_i12 + 0x30f52b4,tmp_u11);
        }
      }
      GHIDRA_FIELD(cgs, 33585500, 4) = 1;
      tmp_i15 = tmp_i15 + 1;
      tmp_pi16 = tmp_pi16 + 3;
    } while (tmp_i15 != 0x1a);
LAB_000b7038:
    if (GHIDRA_FIELD(cgs, 33585500, 4) == 0) {
      tmp_i15 = tmp_i17 + 1;
      tmp_i12 = tmp_i17;
    }
    else {
      tmp_i12 = tmp_i17 + 3;
      tmp_pc3 = (char *)CG_Argv(tmp_i17);
      tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pc3 = (char *)CG_Argv(tmp_i17 + 1);
      tmp_l6 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pc3 = (char *)CG_Argv(tmp_i17 + 2);
      strtol(tmp_pc3,(char **)0x0,10);
      tmp_u11 = va("Damage Given: %-6d  Team Damage: %d",tmp_l5);
      Q_strncpyz(0x30f6cb4,tmp_u11);
      tmp_u11 = va("Damage Recvd: %d",tmp_l6);
      tmp_i15 = tmp_i17 + 4;
      Q_strncpyz(0x30f6db4,tmp_u11);
      tmp_u11 = BG_GetStatGoombas(g_unk_01047b00 + 0x2c);
      tmp_u11 = va("Goomba Kills: %d",tmp_u11);
      Q_strncpyz(0x30f6eb4,tmp_u11);
    }
  }
  tmp_pc3 = (char *)CG_Argv(tmp_i12);
  tmp_u13 = strtol(tmp_pc3,(char **)0x0,10);
  tmp_i12 = 0;
  if ((tmp_u13 & 1) != 0) {
    tmp_pc3 = (char *)CG_Argv(tmp_i15);
    tmp_i12 = strtol(tmp_pc3,(char **)0x0,10);
    *(int *)(cgs + tmp_l4 * 0x1a4 + 0x9500) = tmp_i12;
    tmp_i15 = tmp_i15 + 1;
  }
  if ((tmp_u13 & 2) != 0) {
    tmp_pc3 = (char *)CG_Argv(tmp_i15);
    tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_i12 = tmp_i12 + tmp_l5;
    *(long *)(cgs + tmp_l4 * 0x1a4 + 0x9504) = tmp_l5;
    tmp_i15 = tmp_i15 + 1;
  }
  if ((tmp_u13 & 4) != 0) {
    tmp_pc3 = (char *)CG_Argv(tmp_i15);
    tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_i12 = tmp_i12 + tmp_l5;
    *(long *)(cgs + tmp_l4 * 0x1a4 + 0x9508) = tmp_l5;
    tmp_i15 = tmp_i15 + 1;
  }
  if ((tmp_u13 & 8) != 0) {
    tmp_pc3 = (char *)CG_Argv(tmp_i15);
    tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_i12 = tmp_i12 + tmp_l5;
    *(long *)(cgs + tmp_l4 * 0x1a4 + 0x950c) = tmp_l5;
    tmp_i15 = tmp_i15 + 1;
  }
  if ((tmp_u13 & 0x10) != 0) {
    tmp_pc3 = (char *)CG_Argv(tmp_i15);
    tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_i12 = tmp_i12 + tmp_l5;
    *(long *)(cgs + tmp_l4 * 0x1a4 + 0x9510) = tmp_l5;
    tmp_i15 = tmp_i15 + 1;
  }
  if ((tmp_u13 & 0x20) != 0) {
    tmp_pc3 = (char *)CG_Argv(tmp_i15);
    tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_i12 = tmp_i12 + tmp_l5;
    *(long *)(cgs + tmp_l4 * 0x1a4 + 0x9514) = tmp_l5;
    tmp_i15 = tmp_i15 + 1;
  }
  if ((tmp_u13 & 0x40) != 0) {
    tmp_pc3 = (char *)CG_Argv(tmp_i15);
    tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
    tmp_i12 = tmp_i12 + tmp_l5;
    *(long *)(cgs + tmp_l4 * 0x1a4 + 0x9518) = tmp_l5;
  }
  if (*(int *)(cgs + tmp_l4 * 0x1a4 + 0x9494) == 1) {
    tmp_pu14 = rankNames_Axis;
  }
  else {
    tmp_pu14 = rankNames_Allies;
  }
  tmp_u11 = va("%-13s %d",*(uint32_t *)(tmp_pu14 + *(int *)(cgs + tmp_l4 * 0x1a4 + 0x94c0) * 4),
              tmp_i12);
  Q_strncpyz(0x30f6fb4,tmp_u11,0x100);
  if (tmp_u13 == 0) {
    return;
  }
  tmp_i15 = 0;
  tmp_pi16 = (int *)(cgs + tmp_l4 * 0x1a4 + 0x94e4);
  do {
    while (((int)tmp_u13 >> ((byte)tmp_i15 & 0x1f) & 1U) == 0) {
LAB_000b736c:
      tmp_i15 = tmp_i15 + 1;
      tmp_pi16 = tmp_pi16 + 1;
      if (tmp_i15 == 7) {
        return;
      }
    }
    if (*tmp_pi16 < 5) {
      tmp_u11 = va("%4d/%-4d",tmp_pi16[7],
                  *(uint32_t *)(skillLevels + (*tmp_pi16 + 1 + tmp_i15 * 6) * 4));
    }
    else {
      tmp_u11 = va("%d",tmp_pi16[7]);
    }
    if (GHIDRA_FIELD(cgs, 27388, 4) != 4) {
      va("%-15s %3d %s",(&skillNames)[tmp_i15],*tmp_pi16,tmp_u11);
      tmp_i12 = GHIDRA_FIELD(cgs, 33585496, 4) + 0x1e;
      GHIDRA_FIELD(cgs, 33585496, 4) = GHIDRA_FIELD(cgs, 33585496, 4) + 1;
      Q_strncpyz(tmp_i12 * 0x100 + 0x30f52b4);
      goto LAB_000b736c;
    }
    va("%-15s %3d %s %12d",(&skillNames)[tmp_i15],*tmp_pi16,tmp_u11,tmp_pi16[-7]);
    tmp_i12 = GHIDRA_FIELD(cgs, 33585496, 4) + 0x1e;
    GHIDRA_FIELD(cgs, 33585496, 4) = GHIDRA_FIELD(cgs, 33585496, 4) + 1;
    Q_strncpyz(tmp_i12 * 0x100 + 0x30f52b4);
    tmp_i15 = tmp_i15 + 1;
    tmp_pi16 = tmp_pi16 + 1;
    if (tmp_i15 == 7) {
      return;
    }
  } while( true );
}

void CG_parseWeaponStats_cmd(void *param_1)
{
  int tmp_i1;
  float tmp_f2;
  bool tmp_b3;
  char *tmp_pc4;
  long tmp_l5;
  long tmp_l6;
  uint tmp_u7;
  uint32_t tmp_u8;
  char *tmp_pc9;
  char *tmp_pc10;
  long tmp_l11;
  char *__nptr;
  long tmp_l12;
  uint8_t *tmp_pu13;
  int tmp_i14;
  int *tmp_pi15;
  uint32_t *tmp_pu16;
  int tmp_i17;
  int tmp_i18;
  bool tmp_b19;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xb780e;
  tmp_b19 = param_1 == CG_printWindow;
  tmp_pc4 = (char *)CG_Argv(1);
  tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
  tmp_pc4 = (char *)CG_Argv(2);
  tmp_l6 = strtol(tmp_pc4,(char **)0x0,10);
  tmp_pc4 = (char *)CG_Argv(3);
  tmp_u7 = strtol(tmp_pc4,(char **)0x0,10);
  tmp_i14 = tmp_l5 * 0x1a4 + 0x10f9274;
  Q_strncpyz(local_41c,tmp_i14);
  BG_cleanName(tmp_i14,local_41c,0x400,0);
  tmp_pc4 = "s";
  if (tmp_l6 == 1) {
    tmp_pc4 = "";
  }
  tmp_u8 = va("^7Overall stats for: ^3%s ^7(^2%d^7 Round%s)\n\n",local_41c,tmp_l6,tmp_pc4);
  (*param_1)(tmp_u8);
  if (tmp_b19) {
    CG_printWindow("Weapon     Acrcy Hits/Atts Kll Dth HS\n");
    CG_printWindow(&g_unk_0011d840);
  }
  else {
    (*param_1)("Weapon     Acrcy Hits/Atts Kills Deaths Headshots\n");
    (*param_1)("-------------------------------------------------\n");
  }
  if (tmp_u7 == 0) {
    tmp_i18 = 5;
    (*param_1)("^3No weapon info available.\n");
    tmp_i14 = 4;
  }
  else {
    tmp_pi15 = &aWeaponInfo;
    tmp_i17 = 4;
    tmp_b3 = false;
    tmp_i14 = 0;
    do {
      while ((tmp_u7 & 1 << ((byte)tmp_i14 & 0x1f)) != 0) {
        tmp_pc9 = (char *)CG_Argv(tmp_i17);
        tmp_pc9 = (char *)strtol(tmp_pc9,(char **)0x0,10);
        tmp_pc10 = (char *)CG_Argv(tmp_i17 + 1);
        tmp_l6 = strtol(tmp_pc10,(char **)0x0,10);
        tmp_pc10 = (char *)CG_Argv(tmp_i17 + 2);
        tmp_l11 = strtol(tmp_pc10,(char **)0x0,10);
        tmp_i18 = tmp_i17 + 4;
        tmp_i1 = tmp_i17 + 3;
        tmp_i17 = tmp_i17 + 5;
        tmp_pc10 = (char *)CG_Argv(tmp_i1);
        tmp_pc10 = (char *)strtol(tmp_pc10,(char **)0x0,10);
        __nptr = (char *)CG_Argv(tmp_i18);
        tmp_l12 = strtol(__nptr,(char **)0x0,10);
        tmp_u8 = va("^3%-9s: ",tmp_pi15[2]);
        Q_strncpyz(local_41c,tmp_u8);
        if (((int)tmp_pc9 < 1) && (tmp_l6 < 1)) {
          tmp_u8 = va(&g_unk_0011d7e7);
          Q_strcat(local_41c,0x400);
          if ((0 < (int)tmp_pc10) || (0 < tmp_l11)) {
            tmp_b3 = true;
          }
        }
        else {
          if (tmp_l6 == 0) {
            tmp_f2 = 0.0;
          }
          else {
            tmp_f2 = ((float)(int)tmp_pc9 * 100.0) / (float)tmp_l6;
          }
          tmp_u8 = va("^7%5.1f ^5%4d/%-4d ",(double)tmp_f2,tmp_pc9,tmp_l6);
          Q_strcat(local_41c,0x400);
          tmp_b3 = true;
          tmp_pc4 = tmp_pc9;
        }
        tmp_pu13 = &g_unk_0011d841;
        if (tmp_b19) {
          if (*tmp_pi15 != 0) {
            tmp_pu13 = (uint8_t *)va(" ^3%2d",tmp_l12,tmp_u8,tmp_pc4);
          }
          tmp_pc4 = "%s^2%3d ^1%3d%s\n";
        }
        else {
          if (*tmp_pi15 != 0) {
            tmp_pu13 = (uint8_t *)va(" ^3%9d",tmp_l12,tmp_u8,tmp_pc4);
          }
          tmp_pc4 = "%s^2%5d ^1%6d%s\n";
        }
        tmp_pi15 = tmp_pi15 + 3;
        tmp_u8 = va(tmp_pc4,CONCAT44(tmp_l11,local_41c),tmp_pc10,tmp_pu13);
        (*param_1)(tmp_u8);
        tmp_i14 = tmp_i14 + 1;
        tmp_pc4 = tmp_pc10;
        if (tmp_i14 == 0x1a) goto LAB_000b7b5c;
      }
      tmp_i14 = tmp_i14 + 1;
      tmp_pi15 = tmp_pi15 + 3;
    } while (tmp_i14 != 0x1a);
LAB_000b7b5c:
    if (tmp_b3) {
      tmp_pc9 = (char *)CG_Argv(tmp_i17);
      tmp_l6 = strtol(tmp_pc9,(char **)0x0,10);
      tmp_pc9 = (char *)CG_Argv(tmp_i17 + 1);
      tmp_l11 = strtol(tmp_pc9,(char **)0x0,10);
      tmp_i14 = tmp_i17 + 3;
      tmp_pc9 = (char *)CG_Argv(tmp_i17 + 2);
      strtol(tmp_pc9,(char **)0x0,10);
      if (tmp_b19) {
        CG_printWindow(&g_unk_0011d83f);
      }
      tmp_i18 = tmp_i17 + 4;
      tmp_u8 = va("\n^3Damage Given: ^7%-6d  ^3Team Damage: ^7%d\n",tmp_l6);
      (*param_1)(tmp_u8);
      tmp_u8 = va("^3Damage Recvd: ^7%d\n",tmp_l11);
      (*param_1)(tmp_u8);
    }
    else {
      tmp_i18 = tmp_i17 + 1;
      tmp_i14 = tmp_i17;
    }
  }
  if (tmp_b19) {
    CG_printWindow(&g_unk_0011d83e);
  }
  tmp_pc9 = (char *)CG_Argv(tmp_i14);
  tmp_l6 = 0;
  tmp_u7 = strtol(tmp_pc9,(char **)0x0,10);
  tmp_i14 = tmp_i18;
  if ((tmp_u7 & 1) != 0) {
    tmp_i14 = tmp_i18 + 1;
    tmp_pc9 = (char *)CG_Argv(tmp_i18);
    tmp_l6 = strtol(tmp_pc9,(char **)0x0,10);
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9500) = tmp_l6;
  }
  tmp_i17 = tmp_i14;
  if ((tmp_u7 & 2) != 0) {
    tmp_i17 = tmp_i14 + 1;
    tmp_pc9 = (char *)CG_Argv(tmp_i14);
    tmp_l11 = strtol(tmp_pc9,(char **)0x0,10);
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9504) = tmp_l11;
    tmp_l6 = tmp_l6 + tmp_l11;
  }
  tmp_i14 = tmp_i17;
  if ((tmp_u7 & 4) != 0) {
    tmp_i14 = tmp_i17 + 1;
    tmp_pc9 = (char *)CG_Argv(tmp_i17);
    tmp_l11 = strtol(tmp_pc9,(char **)0x0,10);
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9508) = tmp_l11;
    tmp_l6 = tmp_l6 + tmp_l11;
  }
  tmp_i17 = tmp_i14;
  if ((tmp_u7 & 8) != 0) {
    tmp_i17 = tmp_i14 + 1;
    tmp_pc9 = (char *)CG_Argv(tmp_i14);
    tmp_l11 = strtol(tmp_pc9,(char **)0x0,10);
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x950c) = tmp_l11;
    tmp_l6 = tmp_l6 + tmp_l11;
  }
  tmp_i14 = tmp_i17;
  if ((tmp_u7 & 0x10) != 0) {
    tmp_i14 = tmp_i17 + 1;
    tmp_pc9 = (char *)CG_Argv(tmp_i17);
    tmp_l11 = strtol(tmp_pc9,(char **)0x0,10);
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9510) = tmp_l11;
    tmp_l6 = tmp_l6 + tmp_l11;
  }
  tmp_i17 = tmp_i14;
  if ((tmp_u7 & 0x20) != 0) {
    tmp_i17 = tmp_i14 + 1;
    tmp_pc9 = (char *)CG_Argv(tmp_i14);
    tmp_l11 = strtol(tmp_pc9,(char **)0x0,10);
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9514) = tmp_l11;
    tmp_l6 = tmp_l6 + tmp_l11;
  }
  if ((tmp_u7 & 0x40) != 0) {
    tmp_pc9 = (char *)CG_Argv(tmp_i17);
    tmp_l11 = strtol(tmp_pc9,(char **)0x0,10);
    tmp_l6 = tmp_l6 + tmp_l11;
    *(long *)(cgs + tmp_l5 * 0x1a4 + 0x9518) = tmp_l11;
  }
  if (*(int *)(cgs + tmp_l5 * 0x1a4 + 0x9494) == 1) {
    tmp_pu13 = rankNames_Axis;
  }
  else {
    tmp_pu13 = rankNames_Allies;
  }
  tmp_u8 = va("\n^2Rank: ^7%s (%d XP)\n",
             *(uint32_t *)(tmp_pu13 + *(int *)(cgs + tmp_l5 * 0x1a4 + 0x94c0) * 4),tmp_l6);
  (*param_1)(tmp_u8);
  if (tmp_b19) {
    CG_printWindow(&g_unk_0011d83e);
    if (GHIDRA_FIELD(cgs, 27388, 4) == 4) {
      tmp_pc9 = "  Medals";
    }
    else {
      tmp_pc9 = "";
    }
    tmp_u8 = va("Skills         Level/Points%s\n",tmp_pc9);
    CG_printWindow(tmp_u8);
    CG_printWindow(&g_unk_0011d840);
  }
  else {
    if (GHIDRA_FIELD(cgs, 27388, 4) == 4) {
      tmp_pc9 = "  Medals";
    }
    else {
      tmp_pc9 = "";
    }
    tmp_u8 = va("Skills         Level/Points%s\n",tmp_pc9);
    (*param_1)(tmp_u8);
    if (GHIDRA_FIELD(cgs, 27388, 4) == 4) {
      tmp_pc9 = "--------";
    }
    else {
      tmp_pc9 = "";
    }
    tmp_u8 = va("---------------------------%s\n",tmp_pc9);
    (*param_1)(tmp_u8);
  }
  if (tmp_u7 != 0) {
    tmp_i14 = 0;
    tmp_pu16 = (uint32_t *)(cgs + tmp_l5 * 0x1a4 + 0x9500);
    do {
      if ((1 << ((byte)tmp_i14 & 0x1f) & tmp_u7) != 0) {
        tmp_i17 = tmp_pu16[-7];
        if (tmp_i17 < 5) {
          tmp_pc4 = *(char **)(skillLevels + (tmp_i17 + 1 + tmp_i14 * 6) * 4);
          tmp_u8 = va("%d (%d/%d)",tmp_i17,*tmp_pu16,tmp_pc4);
        }
        else {
          tmp_u8 = va("%d (%d)",tmp_i17,*tmp_pu16,tmp_pc4);
        }
        if (GHIDRA_FIELD(cgs, 27388, 4) == 4) {
          tmp_pc4 = (char *)tmp_pu16[-0xe];
          tmp_u8 = va("%-14s ^3%-12s  ^2%6d\n",(&skillNames)[tmp_i14],tmp_u8,tmp_pc4);
          (*param_1)(tmp_u8);
        }
        else {
          tmp_u8 = va("%-14s ^3%-12s\n",(&skillNames)[tmp_i14],tmp_u8,tmp_pc4);
          (*param_1)(tmp_u8);
        }
      }
      tmp_pu16 = tmp_pu16 + 1;
      tmp_i14 = tmp_i14 + 1;
    } while (tmp_i14 != 7);
    return;
  }
  (*param_1)("^3No skills acquired!\n");
  return;
}

void CG_wstatsParse_cmd(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  if (g_unk_010afbd0 == 0) {
    return;
  }
  if (((g_unk_010afbdc == 0) || (*(int *)(g_unk_010afbdc + 0x54) != 1)) ||
     (*(int *)(g_unk_010afbdc + 0x58) == 0)) {
    CG_createStatsWindow();
  }
  else {
    if (*(int *)(g_unk_010afbdc + 0x264) != 2) goto LAB_000b8349;
    *(uint32_t *)(g_unk_010afbdc + 0x264) = 1;
    tmp_i1 = g_unk_010afbdc;
    tmp_u2 = trap_Milliseconds();
    *(uint32_t *)(tmp_i1 + 0x268) = tmp_u2;
  }
  if (g_unk_010afbdc == 0) {
    g_unk_010afbd0 = 0;
    return;
  }
LAB_000b8349:
  *(uint *)(g_unk_010afbdc + 0x34) = *(uint *)(g_unk_010afbdc + 0x34) | 1;
  *(uint32_t *)(g_unk_010afbdc + 0x5c) = 0;
  g_unk_010afbe8 = g_unk_010afbdc;
  CG_parseWeaponStats_cmd(CG_printWindow);
  return;
}

void CG_parseBestShotsStats_cmd(int param_1,void *param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  long tmp_l3;
  uint32_t tmp_u4;
  long tmp_l5;
  long tmp_l6;
  long tmp_l7;
  long tmp_l8;
  long tmp_l9;
  int tmp_i10;
  float local_4c;
  uint8_t local_3c [40];
  uint32_t uStack_14;
  
  uStack_14 = 0xb83e9;
  tmp_pc2 = (char *)CG_Argv(1);
  tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
  if (tmp_l3 == 0) {
    if (param_1 == 0) {
      tmp_pc2 = "bottom";
    }
    else {
      tmp_pc2 = "top";
    }
    tmp_u4 = va("^3No qualifying %sshot info available.\n",tmp_pc2);
    (*param_2)(tmp_u4);
  }
  else {
    if (param_1 == 0) {
      tmp_pc2 = "WORST";
    }
    else {
      tmp_pc2 = "BEST";
    }
    tmp_u4 = va("^2%s Match Accuracies:\n",tmp_pc2);
    (*param_2)(tmp_u4);
    if (param_2 != CG_printWindow) {
      (*param_2)("\n^3WP   Acrcy Hits/Atts Kills Deaths\n");
      (*param_2)("-------------------------------------------------------------\n");
    }
    else {
      CG_printWindow("^3WP   Acrcy Hits/Atts Kll Dth\n");
      CG_printWindow(&g_unk_0011d840);
    }
    tmp_i10 = 2;
    do {
      tmp_pc2 = (char *)CG_Argv(tmp_i10);
      tmp_l5 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_pc2 = (char *)CG_Argv(tmp_i10 + 1);
      tmp_l6 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_pc2 = (char *)CG_Argv(tmp_i10 + 2);
      tmp_l7 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_pc2 = (char *)CG_Argv(tmp_i10 + 3);
      tmp_l8 = strtol(tmp_pc2,(char **)0x0,10);
      tmp_i1 = tmp_i10 + 5;
      tmp_pc2 = (char *)CG_Argv(tmp_i10 + 4);
      tmp_l9 = strtol(tmp_pc2,(char **)0x0,10);
      if (tmp_l7 < 1) {
        local_4c = 0.0;
      }
      else {
        local_4c = (float)(tmp_l6 * 100) / (float)tmp_l7;
      }
      if (param_2 != CG_printWindow) {
        BG_cleanName(tmp_l5 * 0x1a4 + 0x10f9274,local_3c,0x1e,0);
        tmp_u4 = va("^3%s ^7%5.1f ^5%4d/%-4d ^2%5d ^1%6d ^7%s\n",(&g_ptr_DAT_0013b0e4)[tmp_l3 * 3 + -3],
                   (double)local_4c,tmp_l6,tmp_l7,tmp_l8,tmp_l9,local_3c);
        (*param_2)(tmp_u4);
      }
      else {
        BG_cleanName(tmp_l5 * 0x1a4 + 0x10f9274,local_3c,0xc,0);
        tmp_u4 = va("^3%s ^7%5.1f ^5%4d/%-4d ^2%3d ^1%3d ^7%s\n",(&g_ptr_DAT_0013b0e4)[tmp_l3 * 3 + -3],
                   (double)local_4c,tmp_l6,tmp_l7,tmp_l8,tmp_l9,local_3c);
        CG_printWindow(tmp_u4);
      }
      tmp_i10 = tmp_i10 + 6;
      tmp_pc2 = (char *)CG_Argv(tmp_i1);
      tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
    } while (tmp_l3 != 0);
  }
  return;
}

void CG_parseTopShotsStats_cmd(int param_1,void *param_2)
{
  int tmp_i1;
  float tmp_f2;
  char *tmp_pc3;
  long tmp_l4;
  uint tmp_u5;
  long tmp_l6;
  uint32_t tmp_u7;
  long tmp_l8;
  long tmp_l9;
  long tmp_l10;
  long tmp_l11;
  long tmp_l12;
  int tmp_i13;
  int tmp_i14;
  uint8_t local_3c [40];
  uint32_t uStack_14;
  
  uStack_14 = 0xb8790;
  tmp_pc3 = (char *)CG_Argv(1);
  tmp_l4 = strtol(tmp_pc3,(char **)0x0,10);
  tmp_pc3 = (char *)CG_Argv(2);
  tmp_u5 = strtol(tmp_pc3,(char **)0x0,10);
  tmp_pc3 = (char *)CG_Argv(3);
  tmp_l6 = strtol(tmp_pc3,(char **)0x0,10);
  if (tmp_u5 < 0x1a) {
    tmp_pc3 = (&g_ptr_s_Knife_001152df_0xc_0013b0e8)[tmp_u5 * 3];
  }
  else {
    tmp_pc3 = "UNKNOWN";
  }
  tmp_u7 = va("Weapon accuracies for: ^3%s\n",tmp_pc3);
  (*param_2)(tmp_u7);
  (*param_2)("\n^3  Acc Hits/Atts Kills Deaths\n");
  (*param_2)("----------------------------------------------------------\n");
  if (tmp_l4 == 0) {
    (*param_2)("NO QUALIFYING WEAPON INFO AVAILABLE.\n");
  }
  else if (0 < tmp_l4) {
    tmp_i13 = 4;
    do {
      tmp_pc3 = (char *)CG_Argv(tmp_i13);
      tmp_i14 = tmp_i13 + 4;
      tmp_l8 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pc3 = (char *)CG_Argv(tmp_i13 + 1);
      tmp_l9 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pc3 = (char *)CG_Argv(tmp_i13 + 2);
      tmp_l10 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_i1 = tmp_i13 + 3;
      tmp_i13 = tmp_i13 + 5;
      tmp_pc3 = (char *)CG_Argv(tmp_i1);
      tmp_l11 = strtol(tmp_pc3,(char **)0x0,10);
      tmp_pc3 = (char *)CG_Argv(tmp_i14);
      tmp_l12 = strtol(tmp_pc3,(char **)0x0,10);
      if (tmp_l10 < 1) {
        tmp_f2 = 0.0;
      }
      else {
        tmp_f2 = (float)(tmp_l9 * 100) / (float)tmp_l10;
      }
      if (param_1 == 0) {
        if (tmp_f2 <= (float)tmp_l6 + 0.999) goto LAB_000b8a45;
LAB_000b88a8:
        tmp_pc3 = "^7";
      }
      else {
        if (tmp_f2 < (float)tmp_l6) goto LAB_000b88a8;
LAB_000b8a45:
        tmp_pc3 = "^3";
      }
      BG_cleanName(tmp_l8 * 0x1a4 + 0x10f9274,local_3c,0x1e,0);
      tmp_u7 = va("%s%5.1f ^5%4d/%-4d ^2%5d ^1%6d %s%s\n",tmp_pc3,(double)tmp_f2,tmp_l9,tmp_l10,tmp_l11,
                 tmp_l12,tmp_pc3,local_3c);
      (*param_2)(tmp_u7);
    } while (tmp_i13 != tmp_l4 * 5 + 4);
  }
  return;
}

void CG_scores_cmd(void)
{
  uint32_t tmp_u1;
  uint tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  char *__s;
  size_t tmp_s5;
  uint *tmp_pu6;
  uint *tmp_pu7;
  uint local_41c [4];
  int local_40c;
  int local_408;
  
  tmp_u1 = CG_Argv(1);
  CG_Printf("%s",tmp_u1);
  if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
    BG_cleanName(tmp_u1,local_41c,0x400,1);
    tmp_pu7 = local_41c;
    do {
      tmp_pu6 = tmp_pu7;
      tmp_u2 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6;
      tmp_u3 = tmp_u2 & 0x80808080;
      tmp_pu7 = tmp_pu6 + 1;
    } while (tmp_u3 == 0);
    if ((tmp_u2 & 0x8080) == 0) {
      tmp_pu7 = (uint *)((int)tmp_pu6 + 6);
      tmp_u3 = tmp_u3 >> 0x10;
    }
    trap_FS_Write(local_41c,
                  (int)tmp_pu7 + ((-3 - (uint)CARRY1((byte)tmp_u3,(byte)tmp_u3)) - (int)local_41c),
                  GHIDRA_FIELD(cgs, 33576008, 4));
  }
  tmp_i4 = trap_Argc();
  if (2 < tmp_i4) {
    if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
      trap_RealTime(local_41c);
      __s = (char *)va("\nStats recorded: %02d:%02d:%02d (%02d %s %d)\n\n\n",local_41c[2],
                       local_41c[1],local_41c[0],local_41c[3],
                       *(uint32_t *)(aMonths + local_40c * 4),local_408 + 0x76c);
      tmp_s5 = strlen(__s);
      trap_FS_Write(__s,tmp_s5,GHIDRA_FIELD(cgs, 33576008, 4));
      CG_Printf("[cgnotify]\n^3>>> Stats recorded to: ^7%s\n\n",GHIDRA_FIELD(cgs, 33576012, 4));
      trap_FS_FCloseFile(GHIDRA_FIELD(cgs, 33576008, 4));
      GHIDRA_FIELD(cgs, 33576008, 4) = 0;
    }
    GHIDRA_FIELD(cgs, 33576016, 4) = 0;
  }
  return;
}

void CG_dumpStats(void)
{
  bool tmp_b1;
  uint32_t tmp_u2;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  int local_30;
  int local_2c;
  
  tmp_b1 = false;
  tmp_u2 = Info_ValueForKey(CachedServerInfo,"mapname");
  tmp_u2 = va("^3>>> Map: ^2%s\n\n",tmp_u2);
  trap_RealTime(&local_40);
  if (GHIDRA_FIELD(cgs, 33576008, 4) == 0) {
    tmp_b1 = true;
    GHIDRA_FIELD(cgs, 33576012, 4) =
         va("stats/%d.%02d.%02d/%02d%02d%02d.txt",local_2c + 0x76c,local_30 + 1,local_34,local_38,
            local_3c,local_40);
    if (GHIDRA_FIELD(cgs, 33576008, 4) == 0) goto LAB_000b8cca;
  }
  trap_FS_FCloseFile(GHIDRA_FIELD(cgs, 33576008, 4));
LAB_000b8cca:
  trap_FS_FOpenFile(GHIDRA_FIELD(cgs, 33576012, 4),0x30f52a8,2);
  CG_Printf(tmp_u2);
  if (0 < (int)GHIDRA_FIELD(cgs, 33576008, 4)) {
    CG_printFile_part_0();
  }
  CG_parseWeaponStats_cmd_constprop_5();
  if (GHIDRA_FIELD(cgs, 33576008, 4) == 0) {
    CG_Printf("[cgnotify]\n^3>>> Could not create logfile: %s\n\n",GHIDRA_FIELD(cgs, 33576012, 4));
  }
  if (tmp_b1) {
    trap_SendClientCommand("scores");
  }
  return;
}

void CG_SpeakerEditor_NoiseEditFinish(int param_1)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  
  Q_strncpyz(editSpeaker,*(uint32_t *)(param_1 + 4),0x40);
  tmp_pc1 = editSpeaker;
  if (*editSpeaker == '\0') {
    tmp_pc1[0x40] = '\0';
    tmp_pc1[0x41] = '\0';
    tmp_pc1[0x42] = '\0';
    tmp_pc1[0x43] = '\0';
    return;
  }
  tmp_u2 = trap_S_RegisterSound(editSpeaker,0);
  *(uint32_t *)(tmp_pc1 + 0x40) = tmp_u2;
  return;
}

void CG_SpeakerEditor_TargetnameEditFinish(int param_1)
{
  Q_strncpyz(editSpeaker + 0x50,*(uint32_t *)(param_1 + 4),0x20);
  return;
}

void CG_SpeakerEditor_Back(int param_1)
{
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_10 = 0x3f000000;
  local_1c = colorMdBlue;
  local_18 = g_unk_0014a294;
  local_14 = g_unk_0014a298;
  CG_FillRect(*(float *)(param_1 + 8) - 2.0,*(float *)(param_1 + 0xc) - 2.0,
              *(float *)(param_1 + 0x10) + 4.0,*(float *)(param_1 + 0x14) + 4.0,&local_1c);
  local_1c = colorBlue;
  local_18 = g_unk_0014a384;
  local_14 = g_unk_0014a388;
  CG_DrawRect(*(float *)(param_1 + 8) - 2.0,*(float *)(param_1 + 0xc) - 2.0,
              *(float *)(param_1 + 0x10) + 4.0,*(float *)(param_1 + 0x14) + 4.0,0x3f800000,&local_1c
             );
  return;
}

void CG_SpeakerInfo_Text(int param_1)
{
  uint32_t *tmp_pu1;
  uint32_t *tmp_pu2;
  uint32_t *tmp_pu3;
  float tmp_f4;
  uint32_t *tmp_pu5;
  float tmp_f6;
  uint tmp_u7;
  float tmp_f8;
  uint tmp_u9;
  int tmp_i10;
  char *tmp_pc11;
  char tmp_c12;
  char *tmp_pc13;
  double tmp_d14;
  uint32_t tmp_u15;
  double tmp_d16;
  double tmp_d17;
  float local_214;
  uint32_t *local_1f0;
  uint32_t local_1e4;
  uint32_t local_1e0;
  uint32_t local_1dc;
  uint32_t local_1d8;
  uint8_t local_1d4 [32];
  uint8_t local_1b4 [32];
  uint32_t local_194;
  uint32_t local_190 [45];
  uint8_t local_dc [96];
  uint32_t local_7c;
  uint32_t local_78 [25];
  uint32_t uStack_14;
  
  uStack_14 = 0xbd3dd;
  local_7c = 0;
  tmp_u7 = 0;
  do {
    tmp_u9 = tmp_u7;
    *(uint32_t *)((int)local_78 + tmp_u9) = 0;
    *(uint32_t *)((int)local_78 + tmp_u9 + 4) = 0;
    tmp_u7 = tmp_u9 + 8;
  } while (tmp_u9 + 8 < 0x58);
  *(uint32_t *)((int)local_78 + tmp_u9 + 8) = 0;
  local_190[0x1f] = 0;
  tmp_u7 = 0;
  do {
    tmp_u9 = tmp_u7;
    *(uint32_t *)((int)local_190 + tmp_u9 + 0x80) = 0;
    *(uint32_t *)((int)local_190 + tmp_u9 + 0x84) = 0;
    tmp_u7 = tmp_u9 + 8;
  } while (tmp_u9 + 8 < 0x30);
  *(uint32_t *)((int)local_190 + tmp_u9 + 0x88) = 0;
  local_194 = 0;
  tmp_u7 = 0;
  do {
    tmp_u9 = tmp_u7;
    *(uint32_t *)((int)local_190 + tmp_u9) = 0;
    *(uint32_t *)((int)local_190 + tmp_u9 + 4) = 0;
    tmp_u7 = tmp_u9 + 8;
  } while (tmp_u9 + 8 < 0x18);
  *(uint32_t *)((int)local_190 + tmp_u9 + 8) = 0;
  local_190[7] = 0;
  tmp_u7 = 0;
  do {
    tmp_u9 = tmp_u7;
    *(uint32_t *)((int)local_190 + tmp_u9 + 0x20) = 0;
    *(uint32_t *)((int)local_190 + tmp_u9 + 0x24) = 0;
    tmp_u7 = tmp_u9 + 8;
  } while (tmp_u9 + 8 < 0x18);
  *(uint32_t *)((int)local_190 + tmp_u9 + 0x28) = 0;
  local_190[0xf] = 0;
  tmp_u7 = 0;
  do {
    tmp_u9 = tmp_u7;
    *(uint32_t *)((int)local_190 + tmp_u9 + 0x40) = 0;
    *(uint32_t *)((int)local_190 + tmp_u9 + 0x44) = 0;
    tmp_u7 = tmp_u9 + 8;
  } while (tmp_u9 + 8 < 0x18);
  *(uint32_t *)((int)local_190 + tmp_u9 + 0x48) = 0;
  local_190[0x17] = 0;
  tmp_u7 = 0;
  do {
    tmp_u9 = tmp_u7;
    *(uint32_t *)((int)local_190 + tmp_u9 + 0x60) = 0;
    *(uint32_t *)((int)local_190 + tmp_u9 + 100) = 0;
    tmp_u7 = tmp_u9 + 8;
  } while (tmp_u9 + 8 < 0x18);
  tmp_i10 = *(int *)(param_1 + 0x38);
  *(uint32_t *)((int)local_190 + tmp_u9 + 0x68) = 0;
  if (tmp_i10 != 0) {
    tmp_d17 = (double)*(float *)(editSpeaker + 0x4c);
    tmp_d16 = (double)*(float *)(editSpeaker + 0x48);
    tmp_d14 = (double)*(float *)(editSpeaker + 0x44);
    Com_sprintf(local_dc,0x60,"Speaker at %.2f %.2f %.2f\n",tmp_d14,tmp_d16,tmp_d17);
    tmp_u15 = (uint32_t)((ulonglong)tmp_d14 >> 0x20);
    tmp_i10 = CG_Text_Width_Ext(local_dc,**(uint32_t **)(param_1 + 0x38),0,
                               (*(uint32_t **)(param_1 + 0x38))[8]);
    tmp_f4 = (float)tmp_i10;
    if (*editSpeaker == '\0') {
      local_214 = 8.5;
      tmp_f6 = tmp_f4;
    }
    else {
      Com_sprintf(&local_7c,0x60,"noise: %s\n",editSpeaker,tmp_u15,tmp_d16,tmp_d17);
      tmp_i10 = CG_Text_Width_Ext(&local_7c,**(uint32_t **)(param_1 + 0x38),0,
                                 (*(uint32_t **)(param_1 + 0x38))[8]);
      tmp_f6 = (float)tmp_i10;
      if (tmp_f4 < tmp_f6) {
        local_214 = 17.0;
      }
      else {
        local_214 = 17.0;
        tmp_f6 = tmp_f4;
      }
    }
    local_1f0 = &local_7c;
    tmp_pu5 = local_190 + 0x1f;
    if (editSpeaker[0x50] != '\0') {
      Com_sprintf(tmp_pu5,0x38,"targetname: %s\n",editSpeaker + 0x50,tmp_u15,tmp_d16,tmp_d17);
      tmp_i10 = CG_Text_Width_Ext(tmp_pu5,**(uint32_t **)(param_1 + 0x38),0,
                                 (*(uint32_t **)(param_1 + 0x38))[8]);
      tmp_f4 = (float)tmp_i10;
      if ((float)tmp_i10 <= tmp_f6) {
        tmp_f4 = tmp_f6;
      }
      tmp_f6 = tmp_f4;
      local_214 = local_214 + 8.5;
    }
    Com_sprintf(local_1d4,0x20,"looped: %s\n",
                *(uint32_t *)(s_lt_string + *(int *)(editSpeaker + 0x74) * 4),tmp_u15,tmp_d16,tmp_d17
               );
    tmp_i10 = CG_Text_Width_Ext(local_1d4,**(uint32_t **)(param_1 + 0x38),0,
                               (*(uint32_t **)(param_1 + 0x38))[8]);
    tmp_f4 = (float)tmp_i10;
    if ((float)tmp_i10 <= tmp_f6) {
      tmp_f4 = tmp_f6;
    }
    Com_sprintf(local_1b4,0x20,"broadcast: %s\n",
                *(uint32_t *)(s_bt_string + *(int *)(editSpeaker + 0x78) * 4));
    tmp_i10 = CG_Text_Width_Ext(local_1b4,**(uint32_t **)(param_1 + 0x38),0,
                               (*(uint32_t **)(param_1 + 0x38))[8]);
    tmp_f6 = (float)tmp_i10;
    if ((float)tmp_i10 <= tmp_f4) {
      tmp_f6 = tmp_f4;
    }
    tmp_f4 = local_214 + 8.5 + 8.5;
    if (*(int *)(editSpeaker + 0x7c) != 0) {
      Com_sprintf(&local_194,0x20,"wait: %i\n",*(int *)(editSpeaker + 0x7c));
      tmp_i10 = CG_Text_Width_Ext(&local_194,**(uint32_t **)(param_1 + 0x38),0,
                                 (*(uint32_t **)(param_1 + 0x38))[8]);
      tmp_f8 = (float)tmp_i10;
      if ((float)tmp_i10 <= tmp_f6) {
        tmp_f8 = tmp_f6;
      }
      tmp_f6 = tmp_f8;
      tmp_f4 = tmp_f4 + 8.5;
    }
    tmp_pu1 = local_190 + 7;
    if (*(int *)(editSpeaker + 0x80) != 0) {
      Com_sprintf(tmp_pu1,0x20,"random: %i\n",*(int *)(editSpeaker + 0x80));
      tmp_i10 = CG_Text_Width_Ext(tmp_pu1,**(uint32_t **)(param_1 + 0x38),0,
                                 (*(uint32_t **)(param_1 + 0x38))[8]);
      tmp_f8 = (float)tmp_i10;
      if ((float)tmp_i10 <= tmp_f6) {
        tmp_f8 = tmp_f6;
      }
      tmp_f6 = tmp_f8;
      tmp_f4 = tmp_f4 + 8.5;
    }
    tmp_pu2 = local_190 + 0xf;
    if (*(int *)(editSpeaker + 0x84) != 0) {
      Com_sprintf(tmp_pu2,0x20,"volume: %i\n",*(int *)(editSpeaker + 0x84));
      tmp_i10 = CG_Text_Width_Ext(tmp_pu2,**(uint32_t **)(param_1 + 0x38),0,
                                 (*(uint32_t **)(param_1 + 0x38))[8]);
      tmp_f8 = (float)tmp_i10;
      if ((float)tmp_i10 <= tmp_f6) {
        tmp_f8 = tmp_f6;
      }
      tmp_f6 = tmp_f8;
      tmp_f4 = tmp_f4 + 8.5;
    }
    tmp_pu3 = local_190 + 0x17;
    if (*(int *)(editSpeaker + 0x88) != 0) {
      Com_sprintf(tmp_pu3,0x20,"range: %i\n",*(int *)(editSpeaker + 0x88));
      tmp_i10 = CG_Text_Width_Ext(tmp_pu3,**(uint32_t **)(param_1 + 0x38),0,
                                 (*(uint32_t **)(param_1 + 0x38))[8]);
      tmp_f8 = (float)tmp_i10;
      if ((float)tmp_i10 <= tmp_f6) {
        tmp_f8 = tmp_f6;
      }
      tmp_f6 = tmp_f8;
      tmp_f4 = tmp_f4 + 8.5;
    }
    local_1d8 = 0x3f000000;
    local_1e4 = colorMdBlue;
    local_1e0 = g_unk_0014a294;
    local_1dc = g_unk_0014a298;
    CG_FillRect(*(float *)(param_1 + 8) - 2.0,*(float *)(param_1 + 0xc) - 2.0,tmp_f6 + 4.0,
                tmp_f4 + 4.0,&local_1e4);
    local_1e4 = colorBlue;
    local_1e0 = g_unk_0014a384;
    local_1dc = g_unk_0014a388;
    CG_DrawRect(*(float *)(param_1 + 8) - 2.0,*(float *)(param_1 + 0xc) - 2.0,tmp_f6 + 4.0,
                tmp_f4 + 4.0,0x3f800000,&local_1e4);
    tmp_pc11 = (char *)va("%s%s%s%s%s%s%s%s%s",local_dc,local_1f0,tmp_pu5,local_1d4,local_1b4,
                         &local_194,tmp_pu1,tmp_pu2,tmp_pu3);
    tmp_f4 = *(float *)(param_1 + 0xc);
    tmp_c12 = *tmp_pc11;
    while (tmp_f4 = tmp_f4 + 8.0, tmp_pc13 = tmp_pc11, tmp_c12 != '\0') {
      while (tmp_pc13 = tmp_pc13 + 1, tmp_c12 != '\n') {
        tmp_c12 = *tmp_pc13;
        if (tmp_c12 == '\0') {
          return;
        }
      }
      tmp_pc13[-1] = '\0';
      tmp_pu5 = *(uint32_t **)(param_1 + 0x38);
      CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),tmp_f4,*tmp_pu5,tmp_pu5[1],tmp_pu5 + 2,tmp_pc11,0,0,
                        tmp_pu5[6],tmp_pu5[8]);
      tmp_pc11 = tmp_pc13;
      tmp_c12 = *tmp_pc13;
    }
  }
  return;
}

void CG_SpeakerEditor_LocInfo(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  uint32_t tmp_u4;
  
  tmp_u1 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x20);
  tmp_u2 = *(uint32_t *)(*(int *)(param_1 + 0x38) + 0x18);
  tmp_u4 = va("Speaker at %.2f %.2f %.2f",(double)*(float *)(editSpeaker + 0x44),
             (double)*(float *)(editSpeaker + 0x48),(double)*(float *)(editSpeaker + 0x4c));
  tmp_pu3 = *(uint32_t **)(param_1 + 0x38);
  CG_Text_Paint_Ext(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),*tmp_pu3,tmp_pu3[1],
                    tmp_pu3 + 2,tmp_u4,0,0,tmp_u2,tmp_u1);
  return;
}

void CG_SpeakerEditor_RenderEdit(int param_1)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  uint32_t uStack_c;
  
  uStack_c = 0xbdc77;
  tmp_i1 = BG_PanelButtons_GetFocusButton();
  if (tmp_i1 == param_1) {
    tmp_pu2 = &colorYellow;
  }
  else {
    tmp_pu2 = &colorWhite;
  }
  local_1c = *tmp_pu2;
  local_18 = tmp_pu2[1];
  local_14 = tmp_pu2[2];
  local_10 = 0x3e99999a;
  CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
              *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_1c);
  *(float *)(param_1 + 8) = *(float *)(param_1 + 8) + 2.0;
  *(float *)(param_1 + 0x14) = *(float *)(param_1 + 0x14) - 3.0;
  BG_PanelButton_RenderEdit(param_1);
  *(float *)(param_1 + 8) = *(float *)(param_1 + 8) - 2.0;
  *(float *)(param_1 + 0x14) = *(float *)(param_1 + 0x14) + 3.0;
  return;
}

void CG_SpeakerEditor_RenderButton(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  uint32_t *tmp_pu4;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t local_14;
  uint32_t local_10;
  
  local_10 = 0xbdd38;
  tmp_i3 = BG_PanelButtons_GetFocusButton();
  if (tmp_i3 == param_1) {
    tmp_pu4 = &colorMdBlue;
LAB_000bde6e:
    local_1c = *tmp_pu4;
    local_18 = tmp_pu4[1];
    local_14 = tmp_pu4[2];
    local_10 = 0x3f000000;
  }
  else {
    tmp_i3 = BG_PanelButtons_GetFocusButton();
    if (tmp_i3 == 0) {
      tmp_i3 = BG_CursorInRect(param_1 + 8);
      if (tmp_i3 != 0) {
        tmp_pu4 = &colorWhite;
        goto LAB_000bde6e;
      }
    }
    local_10 = 0x3e99999a;
    local_1c = colorWhite;
    local_18 = g_unk_0014a334;
    local_14 = g_unk_0014a338;
  }
  CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
              *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),&local_1c);
  local_1c = colorBlue;
  local_18 = g_unk_0014a384;
  local_14 = g_unk_0014a388;
  CG_DrawRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),
              *(uint32_t *)(param_1 + 0x10),*(uint32_t *)(param_1 + 0x14),0x3f800000,&local_1c);
  tmp_f1 = *(float *)(param_1 + 8);
  tmp_f2 = *(float *)(param_1 + 0x10);
  tmp_i3 = CG_Text_Width_Ext(*(uint32_t *)(param_1 + 4),**(uint32_t **)(param_1 + 0x38),0,
                            (*(uint32_t **)(param_1 + 0x38))[8]);
  *(float *)(param_1 + 8) = (tmp_f2 - (float)tmp_i3) * 0.5 + tmp_f1;
  *(float *)(param_1 + 0xc) = *(float *)(param_1 + 0xc) + 9.0;
  BG_PanelButtonsRender_Text(param_1);
  *(float *)(param_1 + 8) = tmp_f1;
  *(float *)(param_1 + 0xc) = *(float *)(param_1 + 0xc) - 9.0;
  return;
}

void CG_SpeakerEditor_RenderDropdown(int param_1)
{
  uint32_t tmp_u1;
  float tmp_f2;
  uint32_t tmp_u3;
  float tmp_f4;
  uint32_t *tmp_pu5;
  uint32_t tmp_u6;
  uint32_t tmp_u7;
  float tmp_f8;
  float tmp_f9;
  int tmp_i10;
  int tmp_i11;
  float *pfVar12;
  char *tmp_pc13;
  int tmp_i14;
  float local_3c;
  float local_38;
  float local_34;
  uint32_t local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_f8 = *(float *)(param_1 + 0x10) - *(float *)(param_1 + 0x14);
  local_28 = *(float *)(param_1 + 0xc);
  local_2c = *(float *)(param_1 + 8) + tmp_f8;
  local_24 = *(float *)(param_1 + 0x14);
  local_20 = local_24;
  tmp_i10 = BG_PanelButtons_GetFocusButton();
  if (tmp_i10 == param_1) {
    local_3c = colorYellow;
    local_38 = (float)g_unk_0014a374;
    local_34 = (float)g_unk_0014a378;
  }
  else {
    local_3c = colorWhite;
    local_38 = (float)g_unk_0014a334;
    local_34 = (float)g_unk_0014a338;
  }
  local_30 = 0x3e99999a;
  CG_FillRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),tmp_f8,
              *(uint32_t *)(param_1 + 0x14),&local_3c);
  local_3c = colorBlue;
  local_38 = (float)g_unk_0014a384;
  local_34 = (float)g_unk_0014a388;
  CG_DrawRect(*(uint32_t *)(param_1 + 8),*(uint32_t *)(param_1 + 0xc),tmp_f8,
              *(uint32_t *)(param_1 + 0x14),0x3f800000,&local_3c);
  tmp_i10 = BG_PanelButtons_GetFocusButton();
  if (tmp_i10 == param_1) {
    local_30 = 0x3e99999a;
    local_3c = colorYellow;
    local_38 = (float)g_unk_0014a374;
    local_34 = (float)g_unk_0014a378;
  }
  else {
    tmp_i10 = BG_PanelButtons_GetFocusButton();
    if (tmp_i10 == 0) {
      tmp_i10 = BG_CursorInRect(param_1 + 8);
      if (tmp_i10 != 0) {
        local_30 = 0x3f000000;
        local_3c = colorWhite;
        local_38 = (float)g_unk_0014a334;
        local_34 = (float)g_unk_0014a338;
        goto LAB_000bdfef;
      }
    }
    local_30 = 0x3e99999a;
    local_3c = colorWhite;
    local_38 = (float)g_unk_0014a334;
    local_34 = (float)g_unk_0014a338;
  }
LAB_000bdfef:
  CG_FillRect(local_2c,local_28,local_24,local_20,&local_3c);
  local_3c = colorBlue;
  local_38 = (float)g_unk_0014a384;
  local_34 = (float)g_unk_0014a388;
  CG_DrawRect(local_2c,local_28,local_24,local_20,0x3f800000,&local_3c);
  tmp_f9 = local_24;
  tmp_f4 = local_2c;
  tmp_pu5 = *(uint32_t **)(param_1 + 0x38);
  tmp_u6 = tmp_pu5[8];
  local_3c = (float)tmp_pu5[2];
  local_38 = (float)tmp_pu5[3];
  local_34 = (float)tmp_pu5[4];
  tmp_u1 = tmp_pu5[1];
  tmp_f2 = *(float *)(param_1 + 0xc);
  tmp_u3 = *tmp_pu5;
  tmp_i10 = CG_Text_Width_Ext(&g_unk_00111f46,tmp_u3,0,tmp_u6);
  CG_Text_Paint_Ext((tmp_f9 - (float)tmp_i10) * 0.5 + tmp_f4,tmp_f2 + 9.0,tmp_u3,tmp_u1,&local_3c,
                    &g_unk_00111f46,0,0,0,tmp_u6);
  tmp_pc13 = *(char **)(param_1 + 4);
  if (*(int *)(param_1 + 0x1c) != 0) {
    tmp_i10 = 0;
    do {
      for (; *tmp_pc13 != '\0'; tmp_pc13 = tmp_pc13 + 1) {
      }
      tmp_i10 = tmp_i10 + 1;
      tmp_pc13 = tmp_pc13 + 1;
    } while (tmp_i10 != *(int *)(param_1 + 0x1c));
  }
  tmp_pu5 = *(uint32_t **)(param_1 + 0x38);
  tmp_u1 = tmp_pu5[1];
  tmp_u6 = tmp_pu5[6];
  tmp_u7 = tmp_pu5[8];
  tmp_f2 = *(float *)(param_1 + 0xc);
  tmp_f4 = *(float *)(param_1 + 8);
  tmp_u3 = *tmp_pu5;
  tmp_i10 = CG_Text_Width_Ext(tmp_pc13,tmp_u3,0,tmp_u7);
  CG_Text_Paint_Ext((tmp_f8 - (float)tmp_i10) * 0.5 + tmp_f4,tmp_f2 + 9.0,tmp_u3,tmp_u1,tmp_pu5 + 2,tmp_pc13
                    ,0,0,tmp_u6,tmp_u7);
  tmp_i10 = BG_PanelButtons_GetFocusButton();
  if (tmp_i10 != param_1) {
    return;
  }
  local_2c = *(float *)(param_1 + 8);
  local_28 = *(float *)(param_1 + 0xc);
  local_24 = *(float *)(param_1 + 0x10);
  local_20 = *(float *)(param_1 + 0x14);
  tmp_i11 = *(int *)(param_1 + 0x18);
  tmp_i14 = 0;
  if (0 < tmp_i11) {
    do {
      if (*(int *)(tmp_i10 + 0x1c) != tmp_i14) {
        local_28 = local_28 + 12.0;
        tmp_i11 = BG_CursorInRect(&local_2c);
        if (tmp_i11 == 0) {
          pfVar12 = &colorWhite;
        }
        else {
          pfVar12 = &colorYellow;
        }
        local_3c = *pfVar12 * 0.3;
        local_38 = pfVar12[1] * 0.3;
        local_34 = pfVar12[2] * 0.3;
        local_30 = 0x3f800000;
        CG_FillRect(local_2c,local_28,local_24,local_20,&local_3c);
        tmp_f2 = local_2c;
        tmp_pc13 = *(char **)(tmp_i10 + 4);
        if (tmp_i14 != 0) {
          tmp_i11 = 0;
          do {
            for (; *tmp_pc13 != '\0'; tmp_pc13 = tmp_pc13 + 1) {
            }
            tmp_i11 = tmp_i11 + 1;
            tmp_pc13 = tmp_pc13 + 1;
          } while (tmp_i11 != tmp_i14);
        }
        tmp_pu5 = *(uint32_t **)(tmp_i10 + 0x38);
        tmp_u1 = tmp_pu5[1];
        tmp_u6 = tmp_pu5[6];
        tmp_u7 = tmp_pu5[8];
        tmp_f4 = local_28 + 9.0;
        tmp_u3 = *tmp_pu5;
        tmp_i11 = CG_Text_Width_Ext(tmp_pc13,tmp_u3,0,tmp_u7);
        CG_Text_Paint_Ext((tmp_f8 - (float)tmp_i11) * 0.5 + tmp_f2,tmp_f4,tmp_u3,tmp_u1,tmp_pu5 + 2,tmp_pc13
                          ,0,0,tmp_u6,tmp_u7);
        tmp_i11 = *(int *)(tmp_i10 + 0x18);
      }
      tmp_i14 = tmp_i14 + 1;
    } while (tmp_i14 < tmp_i11);
  }
  local_30 = 0x3e99999a;
  local_3c = colorBlue;
  local_38 = (float)g_unk_0014a384;
  local_34 = (float)g_unk_0014a388;
  CG_DrawRect(*(uint32_t *)(tmp_i10 + 8),*(float *)(tmp_i10 + 0xc) + 12.0,
              *(uint32_t *)(tmp_i10 + 0x10),local_28 - *(float *)(tmp_i10 + 0xc),0x3f800000,
              &local_3c);
  return;
}

uint32_t CG_SpeakerEditor_Dropdown_KeyDown(uint32_t param_1,int param_2)
{
  if (param_2 != 0xb2) {
    return 0;
  }
  BG_PanelButtons_SetFocusButton(param_1);
  return 1;
}

uint32_t CG_SpeakerEditor_Ok_KeyDown(uint32_t param_1,int param_2)
{
  if (param_2 != 0xb2) {
    return 0;
  }
  BG_PanelButtons_SetFocusButton(param_1);
  return 1;
}

uint32_t CG_SpeakerEditor_Cancel_KeyDown(uint32_t param_1,int param_2)
{
  if (param_2 != 0xb2) {
    return 0;
  }
  BG_PanelButtons_SetFocusButton(param_1);
  return 1;
}

uint32_t CG_SpeakerEditor_Delete_KeyDown(uint32_t param_1,int param_2)
{
  if (param_2 != 0xb2) {
    return 0;
  }
  BG_PanelButtons_SetFocusButton(param_1);
  return 1;
}

void CG_SpeakerEditor_WaitEditFinish(int param_1)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t tmp_u3;
  
  tmp_i1 = editSpeaker;
  if (**(char **)(param_1 + 4) == '\0') {
    *(uint32_t *)(editSpeaker + 0x7c) = 0;
    tmp_u3 = 0;
  }
  else {
    tmp_l2 = strtol(*(char **)(param_1 + 4),(char **)0x0,10);
    *(long *)(tmp_i1 + 0x7c) = tmp_l2;
    if (-1 < tmp_l2) {
      return;
    }
    tmp_u3 = *(uint32_t *)(tmp_i1 + 0x88);
    *(uint32_t *)(tmp_i1 + 0x7c) = 0;
  }
  Com_sprintf(*(uint32_t *)(param_1 + 4),4,"%i",tmp_u3);
  return;
}

void CG_SpeakerEditor_RandomEditFinish(int param_1)
{
  int tmp_i1;
  long tmp_l2;
  
  tmp_i1 = editSpeaker;
  if (**(char **)(param_1 + 4) == '\0') {
    *(uint32_t *)(editSpeaker + 0x80) = 0;
  }
  else {
    tmp_l2 = strtol(*(char **)(param_1 + 4),(char **)0x0,10);
    *(long *)(tmp_i1 + 0x80) = tmp_l2;
    if (-1 < tmp_l2) {
      return;
    }
    *(uint32_t *)(tmp_i1 + 0x80) = 0;
  }
  Com_sprintf(*(uint32_t *)(param_1 + 4),4,"%i",0);
  return;
}

void CG_SpeakerEditor_VolumeEditFinish(int param_1)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t tmp_u3;
  
  tmp_i1 = editSpeaker;
  if (**(char **)(param_1 + 4) == '\0') {
    *(uint32_t *)(editSpeaker + 0x84) = 0x7f;
    tmp_u3 = 0x7f;
  }
  else {
    tmp_l2 = strtol(*(char **)(param_1 + 4),(char **)0x0,10);
    if (tmp_l2 < 0) {
      *(uint32_t *)(tmp_i1 + 0x84) = 0;
      tmp_u3 = 0;
    }
    else {
      if (tmp_l2 < 0x10000) {
        *(long *)(tmp_i1 + 0x84) = tmp_l2;
        return;
      }
      *(uint32_t *)(tmp_i1 + 0x84) = 0xffff;
      tmp_u3 = 0xffff;
    }
  }
  Com_sprintf(*(uint32_t *)(param_1 + 4),4,"%i",tmp_u3);
  return;
}

void CG_SpeakerEditor_RangeEditFinish(int param_1)
{
  int tmp_i1;
  long tmp_l2;
  uint32_t tmp_u3;
  
  tmp_i1 = editSpeaker;
  if (**(char **)(param_1 + 4) == '\0') {
    *(uint32_t *)(editSpeaker + 0x88) = 0x4e2;
    tmp_u3 = 0x4e2;
  }
  else {
    tmp_l2 = strtol(*(char **)(param_1 + 4),(char **)0x0,10);
    *(long *)(tmp_i1 + 0x88) = tmp_l2;
    if (-1 < tmp_l2) {
      return;
    }
    *(uint32_t *)(tmp_i1 + 0x88) = 0;
    tmp_u3 = 0;
  }
  Com_sprintf(*(uint32_t *)(param_1 + 4),4,"%i",tmp_u3);
  return;
}

uint32_t CG_SpeakerEditor_NoiseEdit_KeyDown(int param_1,uint param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint tmp_u4;
  uint tmp_u5;
  int tmp_i6;
  size_t tmp_s7;
  int tmp_i8;
  uint *tmp_pu9;
  uint *tmp_pu10;
  uint8_t *__s;
  int local_e4;
  uint8_t local_dc [64];
  uint local_9c [16];
  uint8_t local_5c [76];
  
  tmp_i1 = BG_PanelButtons_GetFocusButton();
  if (tmp_i1 != param_1) {
LAB_000be916:
    tmp_u2 = BG_PanelButton_EditClick(param_1,param_2);
    return tmp_u2;
  }
  if (param_2 != 9) {
    if (((param_2 & 0x400) != 0) &&
       ((0x1f < (int)(param_2 & 0xfffffbff) || ((param_2 & 0xfffffbff) == 8)))) {
      noiseMatchString = '\0';
    }
    goto LAB_000be916;
  }
  COM_StripFilename(*(uint32_t *)(tmp_i1 + 4),local_dc);
  tmp_u2 = COM_SkipPath(*(uint32_t *)(tmp_i1 + 4));
  Q_strncpyz(local_9c,tmp_u2,0x40);
  tmp_i3 = Q_stricmp(*(uint32_t *)(tmp_i1 + 4),local_dc);
  if (tmp_i3 == 0) {
    return 1;
  }
  __s = bigTextBuffer;
  tmp_i3 = trap_FS_GetFileList(local_dc,&g_unk_0011d841,bigTextBuffer,100000);
  tmp_pu10 = (uint *)&noiseMatchString;
  if (noiseMatchString != '\0') {
    do {
      tmp_pu9 = tmp_pu10;
      tmp_u4 = *tmp_pu9 + 0xfefefeff & ~*tmp_pu9;
      tmp_u5 = tmp_u4 & 0x80808080;
      tmp_pu10 = tmp_pu9 + 1;
    } while (tmp_u5 == 0);
    if ((tmp_u4 & 0x8080) == 0) {
      tmp_pu10 = (uint *)((int)tmp_pu9 + 6);
      tmp_u5 = tmp_u5 >> 0x10;
    }
    tmp_i6 = Q_stricmpn(&noiseMatchString,local_9c,
                       (uint8_t *)
                       ((int)tmp_pu10 + (-0x2f47c3 - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5))));
    if (tmp_i6 == 0) {
      if (noiseMatchCount == 1) {
        return 1;
      }
      noiseMatchIndex = noiseMatchIndex + 1;
      if (noiseMatchCount == noiseMatchIndex) {
        noiseMatchIndex = 0;
      }
      if (0 < tmp_i3) {
        local_e4 = 0;
        tmp_i6 = 0;
        do {
          tmp_s7 = strlen(__s);
          tmp_pu10 = (uint *)&noiseMatchString;
          do {
            tmp_pu9 = tmp_pu10;
            tmp_u4 = *tmp_pu9 + 0xfefefeff & ~*tmp_pu9;
            tmp_u5 = tmp_u4 & 0x80808080;
            tmp_pu10 = tmp_pu9 + 1;
          } while (tmp_u5 == 0);
          if ((tmp_u4 & 0x8080) == 0) {
            tmp_pu10 = (uint *)((int)tmp_pu9 + 6);
            tmp_u5 = tmp_u5 >> 0x10;
          }
          tmp_i8 = Q_stricmpn(__s,&noiseMatchString,
                             (uint8_t *)
                             ((int)tmp_pu10 + (-0x2f47c3 - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5))));
          if (tmp_i8 == 0) {
            if (noiseMatchIndex == local_e4) {
              Q_strncpyz(local_5c,__s,0x40);
              break;
            }
            local_e4 = local_e4 + 1;
          }
          tmp_i6 = tmp_i6 + 1;
          __s = __s + tmp_s7 + 1;
        } while (tmp_i6 != tmp_i3);
      }
      goto LAB_000beb40;
    }
  }
  Q_strncpyz(&noiseMatchString,local_9c,0x40);
  noiseMatchCount = 0;
  noiseMatchIndex = 0;
  if (tmp_i3 < 1) {
    noiseMatchIndex = 0;
    noiseMatchCount = 0;
    noiseMatchString = 0;
    return 1;
  }
  tmp_i6 = 0;
  do {
    tmp_s7 = strlen(__s);
    tmp_pu10 = local_9c;
    do {
      tmp_pu9 = tmp_pu10;
      tmp_u4 = *tmp_pu9 + 0xfefefeff & ~*tmp_pu9;
      tmp_u5 = tmp_u4 & 0x80808080;
      tmp_pu10 = tmp_pu9 + 1;
    } while (tmp_u5 == 0);
    if ((tmp_u4 & 0x8080) == 0) {
      tmp_pu10 = (uint *)((int)tmp_pu9 + 6);
      tmp_u5 = tmp_u5 >> 0x10;
    }
    tmp_i8 = Q_stricmpn(__s,local_9c,
                       (int)tmp_pu10 + ((-3 - (uint)CARRY1((byte)tmp_u5,(byte)tmp_u5)) - (int)local_9c)
                      );
    if ((tmp_i8 == 0) && (noiseMatchCount = noiseMatchCount + 1, noiseMatchCount == 1)) {
      Q_strncpyz(local_5c,__s,0x40);
    }
    tmp_i6 = tmp_i6 + 1;
    __s = __s + tmp_s7 + 1;
  } while (tmp_i6 != tmp_i3);
LAB_000beb40:
  if (noiseMatchCount == 0) {
    noiseMatchString = 0;
    return 1;
  }
  Com_sprintf(*(uint32_t *)(tmp_i1 + 4),*(uint32_t *)(tmp_i1 + 0x18),"%s%s",local_dc,local_5c);
  return 1;
}

uint32_t CG_SpeakerEditor_Looped_KeyUp(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint32_t local_2c;
  float local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  if ((param_2 != 0xb2) || (tmp_i1 = BG_PanelButtons_GetFocusButton(), tmp_i1 != param_1)) {
    return 0;
  }
  local_2c = *(uint32_t *)(tmp_i1 + 8);
  tmp_i4 = 0;
  local_28 = *(float *)(tmp_i1 + 0xc);
  local_24 = *(uint32_t *)(tmp_i1 + 0x10);
  local_20 = *(uint32_t *)(tmp_i1 + 0x14);
  tmp_i2 = *(int *)(editSpeaker + 0x74);
  tmp_i3 = editSpeaker;
  do {
    if (tmp_i4 != tmp_i2) {
      local_28 = local_28 + 12.0;
      tmp_i2 = BG_CursorInRect(&local_2c);
      tmp_i3 = editSpeaker;
      if (tmp_i2 != 0) {
        *(int *)(editSpeaker + 0x74) = tmp_i4;
        *(int *)(tmp_i1 + 0x1c) = tmp_i4;
        tmp_i2 = *(int *)(tmp_i3 + 0x74);
        break;
      }
      tmp_i2 = *(int *)(editSpeaker + 0x74);
    }
    tmp_i4 = tmp_i4 + 1;
  } while (tmp_i4 != 3);
  *(uint *)(tmp_i3 + 0x8c) = (uint)(tmp_i2 == 1);
  BG_PanelButtons_SetFocusButton(0);
  return 1;
}

uint32_t CG_SpeakerEditor_Broadcast_KeyUp(int param_1,int param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  uint32_t local_2c;
  float local_28;
  uint32_t local_24;
  uint32_t local_20;
  
  if ((param_2 != 0xb2) || (tmp_i1 = BG_PanelButtons_GetFocusButton(), tmp_i1 != param_1)) {
    return 0;
  }
  local_2c = *(uint32_t *)(tmp_i1 + 8);
  tmp_i3 = 0;
  local_28 = *(float *)(tmp_i1 + 0xc);
  local_24 = *(uint32_t *)(tmp_i1 + 0x10);
  local_20 = *(uint32_t *)(tmp_i1 + 0x14);
  do {
    if (tmp_i3 != *(int *)(editSpeaker + 0x78)) {
      local_28 = local_28 + 12.0;
      tmp_i2 = BG_CursorInRect(&local_2c);
      if (tmp_i2 != 0) {
        *(int *)(editSpeaker + 0x78) = tmp_i3;
        *(int *)(tmp_i1 + 0x1c) = tmp_i3;
        break;
      }
    }
    tmp_i3 = tmp_i3 + 1;
  } while (tmp_i3 != 3);
  BG_PanelButtons_SetFocusButton(0);
  return 1;
}

uint32_t CG_SpeakerEditor_Cancel_KeyUp(int param_1,int param_2)
{
  uint16_t tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint tmp_u4;
  uint32_t *tmp_pu5;
  uint16_t *tmp_pu6;
  uint32_t *tmp_pu7;
  uint16_t *tmp_pu8;
  uint tmp_u9;
  bool tmp_b10;
  
  if ((param_2 == 0xb2) && (tmp_i3 = BG_PanelButtons_GetFocusButton(), tmp_i3 == param_1)) {
    BG_PanelButtons_SetFocusButton(0);
    tmp_i3 = BG_CursorInRect(tmp_i3 + 8);
    if (tmp_i3 == 0) {
      return 1;
    }
    tmp_pu5 = (uint32_t *)&undoSpeaker;
    tmp_u9 = 0x98;
    tmp_b10 = ((uint)editSpeaker & 1) != 0;
    tmp_pu8 = editSpeaker;
    if (tmp_b10) {
      tmp_pu8 = (uint16_t *)((int)editSpeaker + 1);
      tmp_pu5 = &g_unk_002f4841;
      tmp_u9 = 0x97;
      *(uint8_t *)editSpeaker = undoSpeaker;
    }
    tmp_pu6 = tmp_pu8;
    if (((uint)tmp_pu8 & 2) != 0) {
      tmp_u1 = *(uint16_t *)tmp_pu5;
      tmp_pu6 = tmp_pu8 + 1;
      tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
      tmp_u9 = tmp_u9 - 2;
      *tmp_pu8 = tmp_u1;
    }
    tmp_u4 = 0;
    do {
      tmp_u2 = *(uint32_t *)((int)tmp_pu5 + tmp_u4);
      *(uint32_t *)((int)tmp_pu6 + tmp_u4 + 4) = *(uint32_t *)((int)tmp_pu5 + tmp_u4 + 4);
      *(uint32_t *)((int)tmp_pu6 + tmp_u4) = tmp_u2;
      tmp_u4 = tmp_u4 + 8;
    } while (tmp_u4 < (tmp_u9 & 0xfffffff8));
    tmp_pu7 = (uint32_t *)((int)tmp_pu6 + tmp_u4);
    tmp_pu5 = (uint32_t *)((int)tmp_pu5 + tmp_u4);
    tmp_i3 = 0;
    if ((tmp_u9 & 4) != 0) {
      *tmp_pu7 = *tmp_pu5;
      tmp_i3 = 4;
    }
    if ((tmp_u9 & 2) != 0) {
      *(uint16_t *)((int)tmp_pu7 + tmp_i3) = *(uint16_t *)((int)tmp_pu5 + tmp_i3);
      tmp_i3 = tmp_i3 + 2;
    }
    if (tmp_b10) {
      *(uint8_t *)((int)tmp_pu7 + tmp_i3) = *(uint8_t *)((int)tmp_pu5 + tmp_i3);
    }
    undoSpeakerIndex = 0xfffffffe;
    editSpeaker = (uint16_t *)0x0;
    editSpeakerActive = 0;
    CG_EventHandling(0xfffffffe,1);
    return 1;
  }
  return 0;
}

void CG_RenderScriptSpeakers(void)
{
  float tmp_f1;
  uint8_t tmp_u2;
  uint8_t tmp_u3;
  uint8_t tmp_u4;
  uint8_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  uint tmp_u9;
  float *pfVar10;
  int tmp_i11;
  long double tmp_l12;
  float local_244;
  int local_23c;
  float local_210 [33];
  float local_18c;
  float local_188;
  float local_184;
  float local_170;
  float local_16c;
  float local_168;
  uint32_t local_144;
  uint32_t local_140;
  uint32_t local_130;
  float local_108 [45];
  uint8_t local_54;
  uint8_t local_53;
  uint8_t local_52;
  uint8_t local_51;
  uint32_t uStack_14;
  
  uStack_14 = 0xbefb2;
  local_23c = -1;
  local_244 = 64.0;
  numSpeakersInPvs = 0;
  tmp_i6 = BG_NumScriptSpeakers();
  if (0 < tmp_i6) {
    tmp_i6 = 0;
    do {
      tmp_i7 = BG_GetScriptSpeaker(tmp_i6);
      tmp_i8 = editSpeaker;
      if ((editSpeakerActive == 0) || (editSpeaker != tmp_i7)) {
        tmp_i8 = trap_R_inPVS(g_unk_010afbcc + 0x18,tmp_i7 + 0x44);
        if (tmp_i8 != 0) {
          numSpeakersInPvs = numSpeakersInPvs + 1;
          goto LAB_000bf044;
        }
      }
      else {
        pfVar10 = local_210 + 7;
        tmp_i11 = 0;
        do {
          local_210[5] = 0.0;
          local_210[4] = 0.0;
          local_210[3] = 0.0;
          local_210[6] = 1.0;
          if ((g_unk_002f481c < 0) || (tmp_i11 == g_unk_002f481c)) {
            local_210[tmp_i11 + 3] = 1.0;
          }
          else {
            local_210[tmp_i11 + 3] = 0.3;
          }
          tmp_u9 = 0;
          local_210[2] = 0.0;
          local_210[1] = 0.0;
          local_210[0] = 0.0;
          local_210[tmp_i11] = 1.0;
          local_210[0] = local_210[0] * 32.0 + editSpeakerHandle;
          local_210[1] = local_210[1] * 32.0 + g_unk_002f4808;
          local_210[2] = local_210[2] * 32.0 + g_unk_002f480c;
          do {
            *(uint32_t *)((int)local_108 + tmp_u9) = 0;
            *(uint32_t *)((int)local_108 + tmp_u9 + 4) = 0;
            tmp_u9 = tmp_u9 + 8;
          } while (tmp_u9 < 0xe8);
          *(uint32_t *)((int)local_108 + tmp_u9) = 0;
          local_108[0] = 7.00649e-45;
          local_108[0x2c] = (float)GHIDRA_FIELD(cgs, 67956, 4);
          tmp_u2 = (uint8_t)(short)ROUND(local_210[3] * 255.0);
          tmp_u3 = (uint8_t)(short)ROUND(local_210[4] * 255.0);
          tmp_u4 = (uint8_t)(short)ROUND(local_210[5] * 255.0);
          tmp_u5 = (uint8_t)(short)ROUND(local_210[6] * 255.0);
          local_108[0x1a] = editSpeakerHandle;
          local_108[0x1b] = g_unk_002f4808;
          local_108[0x1c] = g_unk_002f480c;
          local_108[0x21] = local_210[0];
          local_108[0x22] = local_210[1];
          local_108[0x23] = local_210[2];
          local_54 = tmp_u2;
          local_53 = tmp_u3;
          local_52 = tmp_u4;
          local_51 = tmp_u5;
          trap_R_AddRefEntityToScene(local_108);
          tmp_u9 = 0;
          do {
            *(uint32_t *)((int)pfVar10 + tmp_u9) = 0;
            *(uint32_t *)((int)local_210 + tmp_u9 + 0x20) = 0;
            tmp_u9 = tmp_u9 + 8;
          } while (tmp_u9 < 0xe8);
          tmp_i11 = tmp_i11 + 1;
          local_130 = 0x40400000;
          local_18c = local_210[0];
          *(uint32_t *)((int)pfVar10 + tmp_u9) = 0;
          local_210[7] = 2.8026e-45;
          local_188 = local_210[1];
          local_144 = GHIDRA_FIELD(cgs, 68096, 4);
          local_184 = local_210[2];
          local_170 = local_210[0];
          local_16c = local_210[1];
          local_168 = local_210[2];
          local_140 = CONCAT13(tmp_u5,CONCAT12(tmp_u4,CONCAT11(tmp_u3,tmp_u2)));
          trap_R_AddRefEntityToScene(pfVar10);
        } while (tmp_i11 != 3);
        tmp_i8 = trap_R_inPVS(g_unk_010afbcc + 0x18,tmp_i8 + 0x44);
        if (tmp_i8 != 0) {
          numSpeakersInPvs = numSpeakersInPvs + 1;
        }
LAB_000bf044:
        pfVar10 = local_210 + 7;
        tmp_u9 = 0;
        do {
          *(uint32_t *)((int)pfVar10 + tmp_u9) = 0;
          *(uint32_t *)((int)local_210 + tmp_u9 + 0x20) = 0;
          tmp_u9 = tmp_u9 + 8;
        } while (tmp_u9 < 0xe8);
        *(uint32_t *)((int)pfVar10 + tmp_u9) = 0;
        local_18c = *(float *)(tmp_i7 + 0x44);
        local_210[7] = 2.8026e-45;
        local_144 = speakerShader;
        local_188 = *(float *)(tmp_i7 + 0x48);
        local_184 = *(float *)(tmp_i7 + 0x4c);
        local_170 = *(float *)(tmp_i7 + 0x44);
        local_16c = *(float *)(tmp_i7 + 0x48);
        local_168 = *(float *)(tmp_i7 + 0x4c);
        local_130 = 0x41000000;
        if (editSpeaker == 0) {
          local_140 = 0xffffffff;
        }
        else {
          local_144 = speakerShaderGrayScale;
          local_140 = 0xff3f3f3f;
          if (tmp_i7 == editSpeaker) {
            local_140 = 0xffaaaaff;
          }
        }
        trap_R_AddRefEntityToScene(pfVar10);
        if (editSpeakerActive == 0) {
          tmp_f1 = (*(float *)(tmp_i7 + 0x4c) - *(float *)(g_unk_010afbcc + 0x20)) *
                  *(float *)(g_unk_010afbcc + 0x2c) +
                  (*(float *)(tmp_i7 + 0x48) - *(float *)(g_unk_010afbcc + 0x1c)) *
                  *(float *)(g_unk_010afbcc + 0x28) +
                  (*(float *)(tmp_i7 + 0x44) - *(float *)(g_unk_010afbcc + 0x18)) *
                  *(float *)(g_unk_010afbcc + 0x24);
          local_210[0] = *(float *)(tmp_i7 + 0x44) -
                         (*(float *)(g_unk_010afbcc + 0x24) * tmp_f1 + *(float *)(g_unk_010afbcc + 0x18))
          ;
          local_210[1] = *(float *)(tmp_i7 + 0x48) -
                         (*(float *)(g_unk_010afbcc + 0x28) * tmp_f1 + *(float *)(g_unk_010afbcc + 0x1c))
          ;
          local_210[2] = *(float *)(tmp_i7 + 0x4c) -
                         (tmp_f1 * *(float *)(g_unk_010afbcc + 0x2c) + *(float *)(g_unk_010afbcc + 0x20))
          ;
          tmp_l12 = (long double)VectorLengthSquared(local_210);
          if (tmp_l12 <= (long double)local_244) {
            local_244 = (float)tmp_l12;
            local_23c = tmp_i6;
          }
        }
      }
      tmp_i8 = BG_NumScriptSpeakers();
      tmp_i6 = tmp_i6 + 1;
    } while (tmp_i6 < tmp_i8);
  }
  if (editSpeakerActive == 0) {
    if (-1 < local_23c) {
      editSpeaker = BG_GetScriptSpeaker(local_23c);
      return;
    }
    editSpeaker = 0;
  }
  return;
}

void CG_UpdateBufferedSoundScripts(void)
{
  int tmp_i1;
  int tmp_i2;
  
  tmp_i1 = g_unk_010906e0;
  if ((g_unk_010b49bc != 0) && (g_unk_010b49b8 < g_unk_010906e0)) {
    tmp_i2 = g_unk_010b49bc + -1;
    memmove(&g_unk_010b4978,&g_unk_010b497c,0x3c);
    g_unk_010b49bc = tmp_i2;
    if (tmp_i2 != 0) {
      tmp_i2 = CG_SoundPickOldestRandomSound(g_unk_010b4978,0,0xffffffff);
      g_unk_010b49b8 = tmp_i1 + tmp_i2;
    }
  }
  return;
}

uint32_t CG_SaveSpeakersToScript(void)
{
  uint tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint tmp_u4;
  char *tmp_pc5;
  size_t tmp_s6;
  double tmp_d7;
  double tmp_d8;
  double tmp_d9;
  int local_1f4;
  uint32_t local_1d8;
  uint8_t local_1d4 [32];
  uint8_t local_1b4 [32];
  uint32_t local_194;
  uint32_t local_190 [69];
  uint8_t local_7c [104];
  uint32_t uStack_14;
  
  uStack_14 = 0xc0809;
  tmp_u2 = va("sound/maps/%s.sps",0x10f69ac);
  tmp_i3 = trap_FS_FOpenFile(tmp_u2,&local_1d8,1);
  if (tmp_i3 < 0) {
    CG_Printf("^1ERROR: failed to save speakers to \'sound/maps/%s.sps\'\n",0x10f69ac);
    return 0;
  }
  trap_FS_Write("speakerScript\n{",0xf,local_1d8);
  local_1f4 = 0;
  tmp_i3 = BG_NumScriptSpeakers();
  if (0 < tmp_i3) {
    do {
      local_190[0x2d] = 0;
      tmp_u1 = 0;
      do {
        tmp_u4 = tmp_u1;
        *(uint32_t *)((int)local_190 + tmp_u4 + 0xb8) = 0;
        *(uint32_t *)((int)local_190 + tmp_u4 + 0xbc) = 0;
        tmp_u1 = tmp_u4 + 8;
      } while (tmp_u4 + 8 < 0x58);
      *(uint32_t *)((int)local_190 + tmp_u4 + 0xc0) = 0;
      local_190[0x1f] = 0;
      tmp_u1 = 0;
      do {
        tmp_u4 = tmp_u1;
        *(uint32_t *)((int)local_190 + tmp_u4 + 0x80) = 0;
        *(uint32_t *)((int)local_190 + tmp_u4 + 0x84) = 0;
        tmp_u1 = tmp_u4 + 8;
      } while (tmp_u4 + 8 < 0x30);
      *(uint32_t *)((int)local_190 + tmp_u4 + 0x88) = 0;
      local_194 = 0;
      tmp_u1 = 0;
      do {
        tmp_u4 = tmp_u1;
        *(uint32_t *)((int)local_190 + tmp_u4) = 0;
        *(uint32_t *)((int)local_190 + tmp_u4 + 4) = 0;
        tmp_u1 = tmp_u4 + 8;
      } while (tmp_u4 + 8 < 0x18);
      *(uint32_t *)((int)local_190 + tmp_u4 + 8) = 0;
      local_190[7] = 0;
      tmp_u1 = 0;
      do {
        tmp_u4 = tmp_u1;
        *(uint32_t *)((int)local_190 + tmp_u4 + 0x20) = 0;
        *(uint32_t *)((int)local_190 + tmp_u4 + 0x24) = 0;
        tmp_u1 = tmp_u4 + 8;
      } while (tmp_u4 + 8 < 0x18);
      *(uint32_t *)((int)local_190 + tmp_u4 + 0x28) = 0;
      local_190[0xf] = 0;
      tmp_u1 = 0;
      do {
        tmp_u4 = tmp_u1;
        *(uint32_t *)((int)local_190 + tmp_u4 + 0x40) = 0;
        *(uint32_t *)((int)local_190 + tmp_u4 + 0x44) = 0;
        tmp_u1 = tmp_u4 + 8;
      } while (tmp_u4 + 8 < 0x18);
      *(uint32_t *)((int)local_190 + tmp_u4 + 0x48) = 0;
      local_190[0x17] = 0;
      tmp_u1 = 0;
      do {
        tmp_u4 = tmp_u1;
        *(uint32_t *)((int)local_190 + tmp_u4 + 0x60) = 0;
        *(uint32_t *)((int)local_190 + tmp_u4 + 100) = 0;
        tmp_u1 = tmp_u4 + 8;
      } while (tmp_u4 + 8 < 0x18);
      *(uint32_t *)((int)local_190 + tmp_u4 + 0x68) = 0;
      tmp_pc5 = (char *)BG_GetScriptSpeaker(local_1f4);
      if (*tmp_pc5 != '\0') {
        Com_sprintf(local_190 + 0x2d,0x60,"\t\tnoise \"%s\"\n",tmp_pc5);
      }
      tmp_d9 = (double)*(float *)(tmp_pc5 + 0x4c);
      tmp_d8 = (double)*(float *)(tmp_pc5 + 0x48);
      tmp_d7 = (double)*(float *)(tmp_pc5 + 0x44);
      Com_sprintf(local_7c,0x60,"\t\torigin %.2f %.2f %.2f\n",tmp_d7,tmp_d8,tmp_d9);
      tmp_u2 = (uint32_t)((ulonglong)tmp_d7 >> 0x20);
      if (tmp_pc5[0x50] != '\0') {
        Com_sprintf(local_190 + 0x1f,0x38,"\t\ttargetname \"%s\"\n",tmp_pc5 + 0x50,tmp_u2,tmp_d8,tmp_d9)
        ;
      }
      Com_sprintf(local_1d4,0x20,"\t\tlooped \"%s\"\n",
                  *(uint32_t *)(s_lt_string + *(int *)(tmp_pc5 + 0x74) * 4),tmp_u2,tmp_d8,tmp_d9);
      Com_sprintf(local_1b4,0x20,"\t\tbroadcast \"%s\"\n",
                  *(uint32_t *)(s_bt_string + *(int *)(tmp_pc5 + 0x78) * 4));
      if (*(int *)(tmp_pc5 + 0x7c) != 0) {
        Com_sprintf(&local_194,0x20,"\t\twait %i\n",*(int *)(tmp_pc5 + 0x7c),tmp_u2,tmp_d8,tmp_d9);
      }
      if (*(int *)(tmp_pc5 + 0x80) != 0) {
        Com_sprintf(local_190 + 7,0x20,"\t\trandom %i\n",*(int *)(tmp_pc5 + 0x80));
      }
      if (*(int *)(tmp_pc5 + 0x84) != 0) {
        Com_sprintf(local_190 + 0xf,0x20,"\t\tvolume %i\n",*(int *)(tmp_pc5 + 0x84));
      }
      if (*(int *)(tmp_pc5 + 0x88) != 0) {
        Com_sprintf(local_190 + 0x17,0x20,"\t\trange %i\n",*(int *)(tmp_pc5 + 0x88));
      }
      tmp_pc5 = (char *)va("\n\tspeakerDef {\n%s%s%s%s%s%s%s%s%s\t}\n",local_190 + 0x2d,local_7c,
                          local_190 + 0x1f,local_1d4,local_1b4,&local_194,local_190 + 7,
                          local_190 + 0xf,local_190 + 0x17);
      tmp_s6 = strlen(tmp_pc5);
      trap_FS_Write(tmp_pc5,tmp_s6,local_1d8);
      local_1f4 = local_1f4 + 1;
      tmp_i3 = BG_NumScriptSpeakers();
    } while (local_1f4 < tmp_i3);
  }
  trap_FS_Write(&g_unk_0011e3b6,2,local_1d8);
  trap_FS_FCloseFile(local_1d8);
  tmp_u2 = BG_NumScriptSpeakers();
  CG_Printf("Saved %i speakers to \'sound/maps/%s.sps\'\n",tmp_u2,0x10f69ac);
  return 1;
}

uint32_t CG_SpeakerEditor_Ok_KeyUp(int param_1,int param_2)
{
  int tmp_i1;
  
  if ((param_2 == 0xb2) && (tmp_i1 = BG_PanelButtons_GetFocusButton(), tmp_i1 == param_1)) {
    BG_PanelButtons_SetFocusButton(0);
    tmp_i1 = BG_CursorInRect(tmp_i1 + 8);
    if (tmp_i1 == 0) {
      return 1;
    }
    CG_SaveSpeakersToScript();
    editSpeakerActive = 0;
    CG_EventHandling(0xfffffffe,1);
    return 1;
  }
  return 0;
}

uint32_t CG_SpeakerEditor_Delete_KeyUp(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  if ((param_2 == 0xb2) && (tmp_i1 = BG_PanelButtons_GetFocusButton(), tmp_i1 == param_1)) {
    BG_PanelButtons_SetFocusButton(0);
    tmp_i1 = BG_CursorInRect(tmp_i1 + 8);
    if (tmp_i1 == 0) {
      return 1;
    }
    undoSpeakerIndex = 0xffffffff;
    tmp_u2 = BG_GetIndexForSpeaker(editSpeaker);
    BG_SS_DeleteSpeaker(tmp_u2);
    CG_SaveSpeakersToScript();
    editSpeaker = 0;
    editSpeakerActive = 0;
    CG_EventHandling(0xfffffffe,1);
    return 1;
  }
  return 0;
}

void CG_SetViewanglesForSpeakerEditor(void)
{
  float local_18;
  float local_14;
  float local_10;
  uint32_t uStack_8;
  
  uStack_8 = 0xc0fc6;
  if (editSpeakerActive == 0) {
    return;
  }
  local_18 = editSpeakerHandle - *(float *)(g_unk_010afbcc + 0x18);
  local_14 = g_unk_002f4808 - *(float *)(g_unk_010afbcc + 0x1c);
  local_10 = g_unk_002f480c - *(float *)(g_unk_010afbcc + 0x20);
  vectoangles(&local_18,&g_unk_01091a54);
  return;
}

void CG_GetStrFromStrArray(char *param_1,int param_2)
{
  int tmp_i1;
  
  if (param_2 != 0) {
    tmp_i1 = 0;
    do {
      for (; *param_1 != '\0'; param_1 = param_1 + 1) {
      }
      tmp_i1 = tmp_i1 + 1;
      param_1 = param_1 + 1;
    } while (tmp_i1 != param_2);
  }
  return;
}

void CG_SpeakerEditorDraw(void)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint8_t *tmp_pu3;
  uint8_t *tmp_pu4;
  char *tmp_pc5;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  int local_74;
  int local_70;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t local_64;
  uint32_t local_60;
  uint8_t local_5c [32];
  uint8_t local_3c [40];
  uint32_t uStack_14;
  
  tmp_u2 = numSpeakersInPvs;
  uStack_14 = 0xc1059;
  if (g_unk_010b4554 != 0) {
    if (editSpeakerActive != 0) {
      BG_PanelButtonsRender(speakerEditorButtons);
      trap_R_SetColor(0);
      CG_DrawPic((float)g_unk_010261a4,(float)g_unk_010261a8,0x42000000,0x42000000,GHIDRA_FIELD(cgs, 131752, 4));
      return;
    }
    local_60 = 0x3f4ccccd;
    local_6c = colorWhite;
    local_68 = g_unk_0014a334;
    local_64 = g_unk_0014a338;
    if (undoSpeakerIndex == -2) {
      local_80 = 452.0;
    }
    else {
      local_80 = 442.0;
    }
    tmp_u1 = BG_NumScriptSpeakers();
    tmp_u2 = va("Current amount of speakers in map: %i (inpvs: %i max in map: %i)",tmp_u1,tmp_u2,0x100)
    ;
    CG_Text_Paint_Ext(0x41000000,local_80,0x3e4ccccd,0x3e4ccccd,&local_6c,tmp_u2,0,0,3,0x110afec);
    trap_Key_KeysForBinding("dumpspeaker",&local_74,&local_70);
    trap_Key_KeynumToStringBuf(local_74,local_5c,0x20);
    trap_Key_KeynumToStringBuf(local_70,local_3c,0x20);
    Q_strupr(local_5c);
    Q_strupr(local_3c);
    if (local_70 == -1) {
      tmp_pu3 = &g_unk_0011d841;
    }
    else {
      tmp_pu3 = (uint8_t *)va(" or %s",local_3c);
    }
    tmp_pu4 = &g_unk_0011e3b9;
    if (local_74 != -1) {
      tmp_pu4 = local_5c;
    }
    tmp_u2 = va("Create new speaker: %s%s",tmp_pu4,tmp_pu3);
    CG_Text_Paint_Ext(0x41000000,local_80 + 10.0,0x3e4ccccd,0x3e4ccccd,&local_6c,tmp_u2,0,0,3,
                      0x110afec);
    trap_Key_KeysForBinding("modifyspeaker",&local_74,&local_70);
    trap_Key_KeynumToStringBuf(local_74,local_5c,0x20);
    trap_Key_KeynumToStringBuf(local_70,local_3c,0x20);
    Q_strupr(local_5c);
    Q_strupr(local_3c);
    if (local_70 == -1) {
      tmp_pu3 = &g_unk_0011d841;
    }
    else {
      tmp_pu3 = (uint8_t *)va(" or %s",local_3c);
    }
    tmp_pu4 = &g_unk_0011e3b9;
    if (local_74 != -1) {
      tmp_pu4 = local_5c;
    }
    tmp_u2 = va("Modify target speaker: %s%s",tmp_pu4,tmp_pu3);
    CG_Text_Paint_Ext(0x41000000,local_80 + 20.0,0x3e4ccccd,0x3e4ccccd,&local_6c,tmp_u2,0,0,3,
                      0x110afec);
    if (undoSpeakerIndex != -2) {
      trap_Key_KeysForBinding("undospeaker",&local_74,&local_70);
      trap_Key_KeynumToStringBuf(local_74,local_5c,0x20);
      trap_Key_KeynumToStringBuf(local_70,local_3c,0x20);
      Q_strupr(local_5c);
      Q_strupr(local_3c);
      if (local_70 == -1) {
        tmp_pu3 = &g_unk_0011d841;
      }
      else {
        tmp_pu3 = (uint8_t *)va(" or %s",local_3c);
      }
      tmp_pu4 = local_5c;
      if (local_74 == -1) {
        tmp_pu4 = &g_unk_0011e3b9;
      }
      if (undoSpeakerIndex == -1) {
        tmp_pc5 = "remove";
      }
      else {
        tmp_pc5 = "modify";
      }
      tmp_u2 = va("Undo %s speaker: %s%s",tmp_pc5,tmp_pu4,tmp_pu3);
      CG_Text_Paint_Ext(0x41000000,local_80 + 30.0,0x3e4ccccd,0x3e4ccccd,&local_6c,tmp_u2,0,0,3,
                        0x110afec);
    }
    local_84 = (float)(int)GHIDRA_FIELD(cg_crosshairX, 12, 4);
    local_80 = (float)(int)GHIDRA_FIELD(cg_crosshairY, 12, 4);
    local_7c = (float)GHIDRA_FIELD(cg_crosshairSize, 8, 4);
    local_78 = local_7c;
    CG_AdjustFrom640FullScreen(&local_84,&local_80,&local_7c,&local_78);
    trap_R_DrawStretchPic
              (((float)*(int *)(g_unk_010afbcc + 8) - local_7c) * 0.5 + local_84,
               ((float)*(int *)(g_unk_010afbcc + 0xc) - local_78) * 0.5 + local_80,local_7c,local_78,0
               ,0,0x3f800000,0x3f800000,
               *(uint32_t *)
                (cgs + (int)(&WORD_000109a8 + ((int)GHIDRA_FIELD(cg_drawCrosshair, 12, 4) % 0x10) * 2)));
    if ((&g_unk_010ab2f4)[(int)GHIDRA_FIELD(cg_drawCrosshair, 12, 4) % 0x10] != 0) {
      trap_R_DrawStretchPic
                (((float)*(int *)(g_unk_010afbcc + 8) - local_7c) * 0.5 + local_84,
                 ((float)*(int *)(g_unk_010afbcc + 0xc) - local_78) * 0.5 + local_80,local_7c,local_78
                 ,0,0,0x3f800000,0x3f800000,(&g_unk_010ab2f4)[(int)GHIDRA_FIELD(cg_drawCrosshair, 12, 4) % 0x10]);
    }
    if (editSpeaker != 0) {
      BG_PanelButtonsRender(&speakerInfoButtons);
    }
  }
  return;
}

void CG_SpeakerEditor_KeyHandling(int param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  long double tmp_l4;
  float local_5c;
  int local_54;
  float local_40 [4];
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i3 = BG_PanelButtonsKeyEvent(param_1,param_2,speakerEditorButtons);
  if (tmp_i3 == 0) {
    if (param_1 == 0x1b) {
      BG_PanelButtons_SetFocusButton(0);
      CG_SaveSpeakersToScript();
      editSpeakerActive = 0;
      CG_EventHandling(0xfffffffe,1);
    }
    else if (param_1 == 0xb2) {
      if (param_2 == 0) {
        g_unk_002f481c = -1;
      }
      else if (g_unk_002f481c == -1) {
        tmp_i3 = 0;
        tmp_f1 = ((float)(GHIDRA_FIELD(cgs, 67776, 4) + -0x140) * -(*(float *)(g_unk_010afbcc + 0x10) / 90.0)) /
                320.0;
        tmp_f2 = ((float)(GHIDRA_FIELD(cgs, 67780, 4) + -0xf0) * -(*(float *)(g_unk_010afbcc + 0x14) / 90.0)) / 240.0
        ;
        local_28 = *(float *)(g_unk_010afbcc + 0x3c) * tmp_f2 +
                   *(float *)(g_unk_010afbcc + 0x30) * tmp_f1 + *(float *)(g_unk_010afbcc + 0x24);
        local_24 = *(float *)(g_unk_010afbcc + 0x40) * tmp_f2 +
                   *(float *)(g_unk_010afbcc + 0x34) * tmp_f1 + *(float *)(g_unk_010afbcc + 0x28);
        local_20 = tmp_f2 * *(float *)(g_unk_010afbcc + 0x44) +
                   tmp_f1 * *(float *)(g_unk_010afbcc + 0x38) + *(float *)(g_unk_010afbcc + 0x2c);
        VectorNormalizeFast(&local_28);
        local_54 = -1;
        local_5c = 256.0;
        do {
          local_40[2] = 0.0;
          local_40[1] = 0.0;
          local_40[0] = 0.0;
          local_40[tmp_i3] = 1.0;
          local_40[3] = local_40[0] * 32.0 + editSpeakerHandle;
          local_30 = local_40[1] * 32.0 + g_unk_002f4808;
          local_2c = local_40[2] * 32.0 + g_unk_002f480c;
          tmp_f1 = (local_2c - *(float *)(g_unk_010afbcc + 0x20)) * local_20 +
                  (local_30 - *(float *)(g_unk_010afbcc + 0x1c)) * local_24 +
                  local_28 * (local_40[3] - *(float *)(g_unk_010afbcc + 0x18));
          local_40[0] = local_28 * tmp_f1 + *(float *)(g_unk_010afbcc + 0x18);
          local_40[1] = *(float *)(g_unk_010afbcc + 0x1c) + local_24 * tmp_f1;
          local_40[2] = tmp_f1 * local_20 + *(float *)(g_unk_010afbcc + 0x20);
          tmp_l4 = (long double)DistanceSquared(local_40 + 3,local_40);
          if (tmp_l4 <= (long double)local_5c) {
            local_5c = (float)tmp_l4;
            local_54 = tmp_i3;
          }
          tmp_i3 = tmp_i3 + 1;
        } while (tmp_i3 != 3);
        g_unk_002f481c = local_54;
        if (local_54 != -1) {
          g_unk_002f4810 = editSpeakerHandle;
          g_unk_002f4814 = g_unk_002f4808;
          g_unk_002f4818 = g_unk_002f480c;
        }
      }
    }
  }
  return;
}

void CG_SpeakerEditorMouseMove_Handling(int param_1,int param_2)
{
  int tmp_i1;
  
  tmp_i1 = editSpeaker;
  if (((g_unk_010b4554 != 0) && (editSpeakerActive != 0)) && (-1 < g_unk_002f481c)) {
    if (g_unk_002f481c == 0) {
      if (GHIDRA_FIELD(cgs, 67776, 4) - param_1 < 0x140) {
        *(float *)(editSpeaker + 0x44) = *(float *)(editSpeaker + 0x44) - (float)param_1;
      }
      else {
        *(float *)(editSpeaker + 0x44) = (float)param_1 + *(float *)(editSpeaker + 0x44);
      }
    }
    else if (g_unk_002f481c == 1) {
      if (GHIDRA_FIELD(cgs, 67776, 4) - param_1 < 0x140) {
        *(float *)(editSpeaker + 0x48) = *(float *)(editSpeaker + 0x48) - (float)param_1;
      }
      else {
        *(float *)(editSpeaker + 0x48) = (float)param_1 + *(float *)(editSpeaker + 0x48);
      }
    }
    else if (g_unk_002f481c == 2) {
      *(float *)(editSpeaker + 0x4c) = *(float *)(editSpeaker + 0x4c) - (float)param_2;
    }
    g_unk_002f4810 = editSpeakerHandle;
    GHIDRA_FIELD(cgs, 67776, 4) = GHIDRA_FIELD(cgs, 67776, 4) - param_1;
    g_unk_002f4814 = g_unk_002f4808;
    GHIDRA_FIELD(cgs, 67780, 4) = GHIDRA_FIELD(cgs, 67780, 4) - param_2;
    g_unk_002f4818 = g_unk_002f480c;
    editSpeakerHandle = *(uint32_t *)(tmp_i1 + 0x44);
    g_unk_002f4808 = *(uint32_t *)(tmp_i1 + 0x48);
    g_unk_002f480c = *(uint32_t *)(tmp_i1 + 0x4c);
  }
  return;
}

void CG_ActivateEditSoundMode(void)
{
  CG_Printf("Activating Speaker Edit mode.\n");
  editSpeaker = 0;
  g_unk_010b4554 = 1;
  editSpeakerActive = 0;
  g_unk_002f481c = 0xffffffff;
  undoSpeakerIndex = 0xfffffffe;
  if (speakerShader == 0) {
    speakerShader = trap_R_RegisterShader("gfx/misc/speaker");
    speakerShaderGrayScale = trap_R_RegisterShader("gfx/misc/speaker_gs");
    BG_PanelButtonsSetup(&speakerInfoButtons);
    BG_PanelButtonsSetup(speakerEditorButtons);
  }
  return;
}

void CG_DeActivateEditSoundMode(void)
{
  CG_Printf("De-activating Speaker Edit mode.\n");
  g_unk_010b4554 = 0;
  if (editSpeakerActive != 0) {
    CG_EventHandling(0xfffffffe,1);
  }
  editSpeaker = 0;
  editSpeakerActive = 0;
  g_unk_002f481c = 0xffffffff;
  undoSpeakerIndex = 0xfffffffe;
  return;
}

void CG_ModifyEditSpeaker(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  
  if ((editSpeaker != 0) && (editSpeakerActive == 0)) {
    CG_EventHandling(2,0);
    tmp_i2 = editSpeaker;
    editSpeakerActive = 1;
    tmp_u3 = 0;
    do {
      tmp_u1 = *(uint32_t *)(tmp_i2 + tmp_u3);
      *(uint32_t *)((int)&g_unk_002f4841 + tmp_u3 + 3) = *(uint32_t *)(tmp_i2 + 4 + tmp_u3);
      *(uint32_t *)(&undoSpeaker + tmp_u3) = tmp_u1;
      tmp_u3 = tmp_u3 + 8;
    } while (tmp_u3 < 0x98);
    undoSpeakerIndex = BG_GetIndexForSpeaker(tmp_i2);
    editSpeakerHandle = *(uint32_t *)(editSpeaker + 0x44);
    g_unk_002f4808 = *(uint32_t *)(editSpeaker + 0x48);
    g_unk_002f480c = *(uint32_t *)(editSpeaker + 0x4c);
    g_unk_002f4810 = editSpeakerHandle;
    g_unk_002f4814 = g_unk_002f4808;
    g_unk_002f4818 = g_unk_002f480c;
    Q_strncpyz(noiseEditBuffer,editSpeaker,0x40);
    Q_strncpyz(targetnameEditBuffer,editSpeaker + 0x50,0x20);
    GHIDRA_FIELD(speakerEditorLoopedDropdown, 28, 4) = *(uint32_t *)(editSpeaker + 0x74);
    GHIDRA_FIELD(speakerEditorBroadcastDropdown, 28, 4) = *(uint32_t *)(editSpeaker + 0x78);
    Com_sprintf(waitEditBuffer,0xc,"%i",*(uint32_t *)(editSpeaker + 0x7c));
    Com_sprintf(randomEditBuffer,0xc,"%i",*(uint32_t *)(editSpeaker + 0x80));
    Com_sprintf(volumeEditBuffer,0xc,"%i",*(uint32_t *)(editSpeaker + 0x84));
    Com_sprintf(rangeEditBuffer,0xc,"%i",*(uint32_t *)(editSpeaker + 0x88));
  }
  return;
}

void CG_UndoEditSpeaker(void)
{
  uint16_t tmp_u1;
  uint32_t tmp_u2;
  uint16_t *tmp_pu3;
  uint32_t *tmp_pu4;
  uint16_t *tmp_pu5;
  uint32_t *tmp_pu6;
  uint tmp_u7;
  int tmp_i8;
  uint tmp_u9;
  bool tmp_b10;
  
  if (undoSpeakerIndex != -2) {
    if (undoSpeakerIndex == -1) {
      tmp_i8 = BG_SS_StoreSpeaker(&undoSpeaker);
      if (tmp_i8 == 0) {
        CG_Printf("^3UNDO: restoring deleted speaker failed, no storage memory for speaker\n");
      }
      else {
        CG_Printf("UNDO: restored deleted speaker at %.2f %.2f %.2f.\n",(double)g_unk_002f4884,
                  (double)g_unk_002f4888,(double)g_unk_002f488c);
      }
    }
    else {
      tmp_u9 = 0x98;
      tmp_pu3 = (uint16_t *)BG_GetScriptSpeaker(undoSpeakerIndex);
      tmp_pu6 = (uint32_t *)&undoSpeaker;
      tmp_b10 = ((uint)tmp_pu3 & 1) != 0;
      tmp_pu5 = tmp_pu3;
      if (tmp_b10) {
        tmp_pu5 = (uint16_t *)((int)tmp_pu3 + 1);
        tmp_pu6 = &g_unk_002f4841;
        tmp_u9 = 0x97;
        *(uint8_t *)tmp_pu3 = undoSpeaker;
      }
      tmp_pu3 = tmp_pu5;
      if (((uint)tmp_pu5 & 2) != 0) {
        tmp_u1 = *(uint16_t *)tmp_pu6;
        tmp_pu3 = tmp_pu5 + 1;
        tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
        tmp_u9 = tmp_u9 - 2;
        *tmp_pu5 = tmp_u1;
      }
      tmp_u7 = 0;
      do {
        tmp_u2 = *(uint32_t *)((int)tmp_pu6 + tmp_u7);
        *(uint32_t *)((int)tmp_pu3 + tmp_u7 + 4) = *(uint32_t *)((int)tmp_pu6 + tmp_u7 + 4);
        *(uint32_t *)((int)tmp_pu3 + tmp_u7) = tmp_u2;
        tmp_u7 = tmp_u7 + 8;
      } while (tmp_u7 < (tmp_u9 & 0xfffffff8));
      tmp_pu4 = (uint32_t *)((int)tmp_pu3 + tmp_u7);
      tmp_pu6 = (uint32_t *)((int)tmp_pu6 + tmp_u7);
      tmp_i8 = 0;
      if ((tmp_u9 & 4) != 0) {
        *tmp_pu4 = *tmp_pu6;
        tmp_i8 = 4;
      }
      if ((tmp_u9 & 2) != 0) {
        *(uint16_t *)((int)tmp_pu4 + tmp_i8) = *(uint16_t *)((int)tmp_pu6 + tmp_i8);
        tmp_i8 = tmp_i8 + 2;
      }
      if (tmp_b10) {
        *(uint8_t *)((int)tmp_pu4 + tmp_i8) = *(uint8_t *)((int)tmp_pu6 + tmp_i8);
      }
      CG_Printf("UNDO: restoring modified settings of speaker at %.2f %.2f %.2f.\n",
                (double)g_unk_002f4884,(double)g_unk_002f4888,(double)g_unk_002f488c);
    }
    CG_SaveSpeakersToScript();
    undoSpeakerIndex = -2;
  }
  return;
}

void CG_ToggleActiveOnScriptSpeaker(uint32_t param_1)
{
  int tmp_i1;
  
  tmp_i1 = BG_GetScriptSpeaker(param_1);
  if (tmp_i1 != 0) {
    *(uint *)(tmp_i1 + 0x8c) = (uint)(*(int *)(tmp_i1 + 0x8c) == 0);
  }
  return;
}

void CG_UnsetActiveOnScriptSpeaker(uint32_t param_1)
{
  int tmp_i1;
  
  tmp_i1 = BG_GetScriptSpeaker(param_1);
  if (tmp_i1 != 0) {
    *(uint32_t *)(tmp_i1 + 0x8c) = 0;
  }
  return;
}

void CG_SetActiveOnScriptSpeaker(uint32_t param_1)
{
  int tmp_i1;
  
  tmp_i1 = BG_GetScriptSpeaker(param_1);
  if (tmp_i1 != 0) {
    *(uint32_t *)(tmp_i1 + 0x8c) = 1;
  }
  return;
}

uint32_t CG_SpawnString(char *param_1,uint32_t param_2,uint32_t *param_3)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (g_unk_010ab348 == 0) {
    *param_3 = param_2;
    CG_Error("CG_SpawnString() called while not spawning");
  }
  tmp_i1 = g_unk_010ab34c;
  if (0 < g_unk_010ab34c) {
    tmp_i3 = 0;
    do {
      tmp_i2 = strcmp(param_1,(char *)(&g_unk_010ab350)[tmp_i3 * 2]);
      if (tmp_i2 == 0) {
        *param_3 = (&g_unk_010ab354)[tmp_i3 * 2];
        return 1;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != tmp_i1);
  }
  *param_3 = param_2;
  return 0;
}

int CG_SpawnFloat(char *param_1,char *param_2,float *param_3)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  double tmp_d4;
  
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  tmp_i1 = g_unk_010ab34c;
  tmp_i3 = 0;
  if (0 < g_unk_010ab34c) {
    do {
      tmp_i2 = strcmp(param_1,(char *)(&g_unk_010ab350)[tmp_i3 * 2]);
      if (tmp_i2 == 0) {
        param_2 = (char *)(&g_unk_010ab354)[tmp_i3 * 2];
        tmp_i3 = 1;
        goto LAB_000c3bce;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != tmp_i1);
    tmp_i3 = 0;
  }
LAB_000c3bce:
  tmp_d4 = strtod(param_2,(char **)0x0);
  *param_3 = (float)tmp_d4;
  return tmp_i3;
}

int CG_SpawnInt(char *param_1,char *param_2,long *param_3)
{
  int tmp_i1;
  int tmp_i2;
  long tmp_l3;
  int tmp_i4;
  
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  tmp_i1 = g_unk_010ab34c;
  tmp_i4 = 0;
  if (0 < g_unk_010ab34c) {
    do {
      tmp_i2 = strcmp(param_1,(char *)(&g_unk_010ab350)[tmp_i4 * 2]);
      if (tmp_i2 == 0) {
        param_2 = (char *)(&g_unk_010ab354)[tmp_i4 * 2];
        tmp_i4 = 1;
        goto LAB_000c3c8e;
      }
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_i4 != tmp_i1);
    tmp_i4 = 0;
  }
LAB_000c3c8e:
  tmp_l3 = strtol(param_2,(char **)0x0,10);
  *param_3 = tmp_l3;
  return tmp_i4;
}

int CG_SpawnVector(char *param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  tmp_i1 = g_unk_010ab34c;
  tmp_i3 = 0;
  if (0 < g_unk_010ab34c) {
    do {
      tmp_i2 = strcmp(param_1,(char *)(&g_unk_010ab350)[tmp_i3 * 2]);
      if (tmp_i2 == 0) {
        param_2 = (&g_unk_010ab354)[tmp_i3 * 2];
        tmp_i3 = 1;
        goto LAB_000c3d4e;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != tmp_i1);
    tmp_i3 = 0;
  }
LAB_000c3d4e:
  __isoc99_sscanf(param_2,&g_unk_0011e959,param_3,param_3 + 4,param_3 + 8);
  return tmp_i3;
}

int CG_SpawnVector2D(char *param_1,uint32_t param_2,int param_3)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  tmp_i1 = g_unk_010ab34c;
  tmp_i3 = 0;
  if (0 < g_unk_010ab34c) {
    do {
      tmp_i2 = strcmp(param_1,(char *)(&g_unk_010ab350)[tmp_i3 * 2]);
      if (tmp_i2 == 0) {
        param_2 = (&g_unk_010ab354)[tmp_i3 * 2];
        tmp_i3 = 1;
        goto LAB_000c3e1e;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 != tmp_i1);
    tmp_i3 = 0;
  }
LAB_000c3e1e:
  __isoc99_sscanf(param_2,&g_unk_0011e95c,param_3,param_3 + 4);
  return tmp_i3;
}

void CG_LoadRankIcons(void)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  uint32_t *tmp_pu3;
  
  tmp_pu2 = (uint32_t *)(rankicons + 0x44);
  do {
    tmp_pu3 = tmp_pu2 + 0x10;
    tmp_u1 = trap_R_RegisterShaderNoMip(*tmp_pu2);
    tmp_pu2[-1] = tmp_u1;
    tmp_u1 = trap_R_RegisterShaderNoMip(tmp_pu2[8]);
    tmp_pu2[7] = tmp_u1;
    tmp_u1 = trap_R_RegisterShaderNoMip(tmp_pu2[4]);
    tmp_pu2[3] = tmp_u1;
    tmp_u1 = trap_R_RegisterShaderNoMip(tmp_pu2[0xc]);
    tmp_pu2[0xb] = tmp_u1;
    tmp_pu2 = tmp_pu3;
  } while (tmp_pu3 != (uint32_t *)&g_unk_001497a4);
  return;
}

void CG_ClearTrails(void)
{
  uint32_t *tmp_pu1;
  int tmp_i2;
  
  memset(&trailJuncs,0,0x84000);
  tmp_i2 = 0;
  activeTrails = 0;
  headTrails = 0;
  freeTrails = &trailJuncs;
  tmp_pu1 = &g_unk_04073f44;
  do {
    tmp_pu1[-0x21] = tmp_pu1;
    if (tmp_i2 == 0) {
      g_unk_04073ec4 = 0;
    }
    else {
      tmp_pu1[-0x20] = tmp_pu1 + -0x42;
    }
    tmp_i2 = tmp_i2 + 1;
    tmp_pu1[-0x1b] = 0;
    tmp_pu1 = tmp_pu1 + 0x21;
  } while (tmp_i2 != 0x1000);
  g_unk_040f7e3c = 0;
  initTrails = 1;
  numTrailsInuse = 0;
  return;
}

int * CG_SpawnTrailJunc(int *param_1)
{
  int *tmp_pi1;
  
  tmp_pi1 = freeTrails;
  if (freeTrails != (int *)0x0) {
    if (GHIDRA_FIELD(cg_paused, 12, 4) == 0) {
      freeTrails = (int *)*freeTrails;
      if (freeTrails != (int *)0x0) {
        freeTrails[1] = 0;
      }
      *tmp_pi1 = (int)activeTrails;
      if (activeTrails != (int *)0x0) {
        activeTrails[1] = (int)tmp_pi1;
      }
      activeTrails = tmp_pi1;
      tmp_pi1[1] = 0;
      tmp_pi1[6] = 1;
      tmp_pi1[7] = 0;
      if (param_1 != (int *)0x0) {
        if (param_1 == headTrails) {
          headTrails = (int *)param_1[3];
          if (headTrails != (int *)0x0) {
            headTrails[4] = 0;
          }
        }
        else {
          if (param_1[3] != 0) {
            *(int *)(param_1[3] + 0x10) = param_1[4];
          }
          if (param_1[4] != 0) {
            *(int *)(param_1[4] + 0xc) = param_1[3];
          }
        }
        param_1[4] = 0;
        param_1[3] = 0;
      }
      if (headTrails != (int *)0x0) {
        headTrails[4] = (int)tmp_pi1;
      }
      numTrailsInuse = numTrailsInuse + 1;
      tmp_pi1[3] = (int)headTrails;
      tmp_pi1[4] = 0;
      headTrails = tmp_pi1;
      tmp_pi1[2] = (int)param_1;
    }
    else {
      tmp_pi1 = (int *)0x0;
    }
  }
  return tmp_pi1;
}

int CG_AddTrailJunc(uint param_1,int param_2,uint32_t param_3,int param_4,int param_5,
                   uint32_t *param_6,int param_7,float param_8,float param_9,uint32_t param_10,
                   uint32_t param_11,uint32_t param_12,uint32_t *param_13,uint32_t *param_14
                   ,float param_15,float param_16)

{
  uint32_t tmp_u1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  long double tmp_l6;
  
  tmp_pu3 = freeTrails;
  tmp_i4 = 0;
  if (param_1 < 0x1000) {
    if (param_1 == 0) {
      tmp_pu5 = (uint32_t *)0x0;
    }
    else {
      tmp_i4 = param_1 - 1;
      tmp_pu5 = (uint32_t *)0x0;
      if (((&g_unk_04073ed8)[tmp_i4 * 0x21] != 0) &&
         (*(int *)(&g_unk_04073ed4 + tmp_i4 * 0x84) == param_2)) {
        tmp_pu5 = &trailJuncs + tmp_i4 * 0x21;
      }
    }
    if ((freeTrails == (uint32_t *)0x0) || (GHIDRA_FIELD(cg_paused, 12, 4) != 0)) {
      tmp_i4 = 0;
    }
    else {
      freeTrails = (uint32_t *)*freeTrails;
      if (freeTrails != (uint32_t *)0x0) {
        freeTrails[1] = 0;
      }
      *tmp_pu3 = activeTrails;
      if (activeTrails != (uint32_t *)0x0) {
        activeTrails[1] = tmp_pu3;
      }
      activeTrails = tmp_pu3;
      tmp_pu3[1] = 0;
      tmp_pu3[6] = 1;
      tmp_pu3[7] = 0;
      if (tmp_pu5 != (uint32_t *)0x0) {
        if (tmp_pu5 == headTrails) {
          headTrails = (uint32_t *)tmp_pu5[3];
          if (headTrails != (uint32_t *)0x0) {
            headTrails[4] = 0;
          }
        }
        else {
          if (tmp_pu5[3] != 0) {
            *(uint32_t *)(tmp_pu5[3] + 0x10) = tmp_pu5[4];
          }
          if (tmp_pu5[4] != 0) {
            *(uint32_t *)(tmp_pu5[4] + 0xc) = tmp_pu5[3];
          }
        }
        tmp_pu5[4] = 0;
        tmp_pu5[3] = 0;
      }
      if (headTrails != (uint32_t *)0x0) {
        headTrails[4] = tmp_pu3;
      }
      tmp_pu3[3] = headTrails;
      numTrailsInuse = numTrailsInuse + 1;
      tmp_pu3[4] = 0;
      headTrails = tmp_pu3;
      tmp_pu3[2] = tmp_pu5;
      tmp_pu3[5] = param_2;
      if (param_8 <= 1.0) {
        if (param_8 < 0.0) {
          param_8 = 0.0;
        }
      }
      else {
        param_8 = 1.0;
      }
      if (param_9 <= 1.0) {
        if (param_9 < 0.0) {
          param_9 = 0.0;
        }
      }
      else {
        param_9 = 1.0;
      }
      tmp_pu3[9] = param_3;
      tmp_pu3[10] = param_5;
      tmp_pu3[0xd] = *param_6;
      tmp_pu3[0xe] = param_6[1];
      tmp_u1 = param_6[2];
      tmp_pu3[0xb] = param_12;
      tmp_pu3[0xf] = tmp_u1;
      tmp_pu3[0x10] = param_4;
      tmp_pu3[0x11] = param_4 + param_7;
      tmp_pu3[0x14] = *param_13;
      tmp_pu3[0x15] = param_13[1];
      tmp_pu3[0x16] = param_13[2];
      tmp_pu3[0x17] = *param_14;
      tmp_pu3[0x18] = param_14[1];
      tmp_pu3[0x19] = param_14[2];
      tmp_pu3[0x12] = param_8;
      tmp_pu3[0x13] = param_9;
      tmp_pu3[0x1a] = param_10;
      tmp_pu3[0x1b] = param_11;
      if (param_5 == 1) {
        if (tmp_pu5 == (uint32_t *)0x0) {
          tmp_pu3[0xc] = ((1.0 - (float)(g_unk_010906e0 % 1000) / 1000.0) * param_16) / param_15;
        }
        else {
          tmp_f2 = (float)tmp_pu5[0xc];
          tmp_l6 = (long double)Distance(tmp_pu5 + 0xd,param_6);
          tmp_pu3[0xc] = (float)((tmp_l6 / (long double)param_15) / (long double)(float)tmp_pu3[0x1b] +
                               (long double)tmp_f2);
        }
      }
      tmp_i4 = ((int)(tmp_pu3 + -0x101cfb0) >> 2) * 0x3e0f83e1 + 1;
    }
  }
  return tmp_i4;
}

int CG_AddSparkJunc(uint param_1,int param_2,uint32_t param_3,uint32_t *param_4,int param_5,
                   float param_6,float param_7,uint32_t param_8,uint32_t param_9)

{
  uint32_t *tmp_pu1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  
  tmp_pu1 = freeTrails;
  tmp_i2 = 0;
  if (param_1 < 0x1000) {
    if (param_1 == 0) {
      tmp_pu3 = (uint32_t *)0x0;
    }
    else {
      tmp_i2 = param_1 - 1;
      tmp_pu3 = (uint32_t *)0x0;
      if (((&g_unk_04073ed8)[tmp_i2 * 0x21] != 0) &&
         (*(int *)(&g_unk_04073ed4 + tmp_i2 * 0x84) == param_2)) {
        tmp_pu3 = &trailJuncs + tmp_i2 * 0x21;
      }
    }
    if ((freeTrails == (uint32_t *)0x0) || (GHIDRA_FIELD(cg_paused, 12, 4) != 0)) {
      tmp_i2 = 0;
    }
    else {
      freeTrails = (uint32_t *)*freeTrails;
      if (freeTrails != (uint32_t *)0x0) {
        freeTrails[1] = 0;
      }
      *tmp_pu1 = activeTrails;
      if (activeTrails != (uint32_t *)0x0) {
        activeTrails[1] = tmp_pu1;
      }
      activeTrails = tmp_pu1;
      tmp_pu1[1] = 0;
      tmp_pu1[6] = 1;
      tmp_pu1[7] = 0;
      if (tmp_pu3 != (uint32_t *)0x0) {
        if (tmp_pu3 == headTrails) {
          headTrails = (uint32_t *)tmp_pu3[3];
          if (headTrails != (uint32_t *)0x0) {
            headTrails[4] = 0;
          }
        }
        else {
          if (tmp_pu3[3] != 0) {
            *(uint32_t *)(tmp_pu3[3] + 0x10) = tmp_pu3[4];
          }
          if (tmp_pu3[4] != 0) {
            *(uint32_t *)(tmp_pu3[4] + 0xc) = tmp_pu3[3];
          }
        }
        tmp_pu3[4] = 0;
        tmp_pu3[3] = 0;
      }
      if (headTrails != (uint32_t *)0x0) {
        headTrails[4] = tmp_pu1;
      }
      tmp_pu1[2] = tmp_pu3;
      numTrailsInuse = numTrailsInuse + 1;
      tmp_pu1[3] = headTrails;
      tmp_pu1[4] = 0;
      tmp_pu1[5] = param_2;
      tmp_pu1[9] = param_3;
      tmp_pu1[10] = 0;
      headTrails = tmp_pu1;
      tmp_pu1[0xd] = *param_4;
      tmp_pu1[0xe] = param_4[1];
      tmp_pu1[0xf] = param_4[2];
      tmp_pu1[0xb] = 4;
      tmp_pu1[0x10] = g_unk_010906e0;
      tmp_i2 = g_unk_010906e0;
      tmp_pu1[0x14] = 0x3f800000;
      tmp_pu1[0x11] = param_5 + tmp_i2;
      tmp_pu1[0x15] = param_6 * 0.2 + 0.8;
      tmp_pu1[0x16] = param_6 * 0.4 + 0.4;
      tmp_pu1[0x17] = 0x3f800000;
      tmp_pu1[0x18] = param_7 * 0.2 + 0.8;
      tmp_pu1[0x19] = param_7 * 0.4 + 0.4;
      tmp_pu1[0x12] = param_6 + param_6;
      tmp_pu1[0x13] = param_7 + param_7;
      tmp_pu1[0x1a] = param_8;
      tmp_pu1[0x1b] = param_9;
      tmp_i2 = ((int)(tmp_pu1 + -0x101cfb0) >> 2) * 0x3e0f83e1 + 1;
    }
  }
  return tmp_i2;
}

int CG_AddSmokeJunc(uint param_1,int param_2,uint32_t param_3,uint32_t *param_4,int param_5,
                   uint32_t param_6,uint32_t param_7,uint32_t param_8)

{
  uint32_t tmp_u1;
  float tmp_f2;
  uint32_t *tmp_pu3;
  int tmp_i4;
  uint32_t *tmp_pu5;
  long double tmp_l6;
  
  tmp_pu3 = freeTrails;
  tmp_i4 = 0;
  if (param_1 < 0x1000) {
    if (param_1 == 0) {
      tmp_pu5 = (uint32_t *)0x0;
    }
    else {
      tmp_i4 = param_1 - 1;
      tmp_pu5 = (uint32_t *)0x0;
      if (((&g_unk_04073ed8)[tmp_i4 * 0x21] != 0) &&
         (*(int *)(&g_unk_04073ed4 + tmp_i4 * 0x84) == param_2)) {
        tmp_pu5 = &trailJuncs + tmp_i4 * 0x21;
      }
    }
    if ((freeTrails == (uint32_t *)0x0) || (GHIDRA_FIELD(cg_paused, 12, 4) != 0)) {
      tmp_i4 = 0;
    }
    else {
      freeTrails = (uint32_t *)*freeTrails;
      if (freeTrails != (uint32_t *)0x0) {
        freeTrails[1] = 0;
      }
      *tmp_pu3 = activeTrails;
      if (activeTrails != (uint32_t *)0x0) {
        activeTrails[1] = tmp_pu3;
      }
      activeTrails = tmp_pu3;
      tmp_pu3[1] = 0;
      tmp_pu3[6] = 1;
      tmp_pu3[7] = 0;
      if (tmp_pu5 != (uint32_t *)0x0) {
        if (tmp_pu5 == headTrails) {
          headTrails = (uint32_t *)tmp_pu5[3];
          if (headTrails != (uint32_t *)0x0) {
            headTrails[4] = 0;
          }
        }
        else {
          if (tmp_pu5[3] != 0) {
            *(uint32_t *)(tmp_pu5[3] + 0x10) = tmp_pu5[4];
          }
          if (tmp_pu5[4] != 0) {
            *(uint32_t *)(tmp_pu5[4] + 0xc) = tmp_pu5[3];
          }
        }
        tmp_pu5[4] = 0;
        tmp_pu5[3] = 0;
      }
      if (headTrails != (uint32_t *)0x0) {
        headTrails[4] = tmp_pu3;
      }
      tmp_pu3[3] = headTrails;
      numTrailsInuse = numTrailsInuse + 1;
      tmp_pu3[5] = param_2;
      tmp_pu3[4] = 0;
      tmp_pu3[2] = tmp_pu5;
      tmp_pu3[9] = param_3;
      tmp_pu3[10] = 1;
      headTrails = tmp_pu3;
      tmp_pu3[0xd] = *param_4;
      tmp_pu3[0xe] = param_4[1];
      tmp_u1 = param_4[2];
      tmp_pu3[0xb] = 1;
      tmp_pu3[0xf] = tmp_u1;
      tmp_pu3[0x10] = g_unk_010906e0;
      tmp_i4 = g_unk_010906e0;
      tmp_pu3[0x12] = param_6;
      tmp_pu3[0x14] = 0x3f333333;
      tmp_pu3[0x15] = 0x3f333333;
      tmp_pu3[0x16] = 0x3f333333;
      tmp_pu3[0x11] = param_5 + tmp_i4;
      tmp_pu3[0x17] = 0;
      tmp_pu3[0x18] = 0;
      tmp_pu3[0x19] = 0;
      tmp_pu3[0x13] = 0;
      tmp_pu3[0x1a] = param_7;
      tmp_pu3[0x1b] = param_8;
      if (tmp_pu5 == (uint32_t *)0x0) {
        tmp_pu3[0xc] = 0;
        tmp_pu3[0x12] = 0;
      }
      else {
        tmp_f2 = (float)tmp_pu5[0xc];
        tmp_l6 = (long double)Distance(tmp_pu5 + 0xd,param_4);
        tmp_pu3[0xc] = (float)((tmp_l6 * (long double)0.25) / (long double)(float)tmp_pu3[0x1b] +
                             (long double)tmp_f2);
      }
      tmp_i4 = ((int)(tmp_pu3 + -0x101cfb0) >> 2) * 0x3e0f83e1 + 1;
    }
  }
  return tmp_i4;
}

void CG_FreeTrailJunc(int *param_1)
{
  uint32_t *tmp_pu1;
  int *tmp_pi2;
  void *tmp_pc3;
  int tmp_i4;
  
  tmp_pu1 = (uint32_t *)param_1[2];
  if ((tmp_pu1 != (uint32_t *)0x0) && ((param_1[6] != 0 || (param_1[7] == 0)))) {
    if ((tmp_pu1 < &trailJuncs) || ((uint32_t *)0x40f7ebf < tmp_pu1)) {
      param_1[2] = 0;
      tmp_pc3 = (void *)invalidInstructionException();
      (*tmp_pc3)();
    }
    param_1[2] = 0;
    if (((int *)tmp_pu1[2] != (int *)0x0) && (param_1 == (int *)tmp_pu1[2])) {
      tmp_pu1[2] = 0;
    }
    CG_FreeTrailJunc(tmp_pu1);
  }
  param_1[6] = 0;
  param_1[7] = 1;
  if (*param_1 != 0) {
    *(int *)(*param_1 + 4) = param_1[1];
  }
  if ((int *)param_1[1] != (int *)0x0) {
    *(int *)param_1[1] = *param_1;
  }
  if (param_1 == activeTrails) {
    activeTrails = (int *)*param_1;
  }
  tmp_pi2 = (int *)param_1[3];
  if (param_1 == headTrails) {
    headTrails = tmp_pi2;
  }
  if (tmp_pi2 != (int *)0x0) {
    tmp_pi2[4] = param_1[4];
  }
  if (param_1[4] != 0) {
    *(int *)(param_1[4] + 0xc) = param_1[3];
  }
  tmp_i4 = (int)freeTrails;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[1] = 0;
  *param_1 = tmp_i4;
  if (freeTrails != (int *)0x0) {
    *(int **)((int)freeTrails + 4) = param_1;
  }
  freeTrails = param_1;
  numTrailsInuse = numTrailsInuse + -1;
  return;
}

void CG_KillTrail(uint32_t *param_1)
{
  int *tmp_pi1;
  uint32_t *tmp_pu2;
  int *tmp_pi3;
  void *tmp_pc4;
  
  if ((param_1[6] != 0) || (param_1[7] == 0)) {
    tmp_pi1 = (int *)param_1[2];
    if ((tmp_pi1 < &trailJuncs) || ((int *)0x40f7ebf < tmp_pi1)) {
      param_1[2] = 0;
      tmp_pc4 = (void *)invalidInstructionException();
      (*tmp_pc4)();
    }
    param_1[2] = 0;
    tmp_pu2 = (uint32_t *)tmp_pi1[2];
    if (tmp_pu2 != (uint32_t *)0x0) {
      if (param_1 == tmp_pu2) {
        tmp_pi1[2] = 0;
      }
      else if ((tmp_pi1[6] != 0) || (tmp_pi1[7] == 0)) {
        if ((tmp_pu2 < &trailJuncs) || ((uint32_t *)0x40f7ebf < tmp_pu2)) {
          tmp_pi1[2] = 0;
          tmp_pc4 = (void *)invalidInstructionException();
          (*tmp_pc4)();
        }
        tmp_pi1[2] = 0;
        if (((int *)tmp_pu2[2] != (int *)0x0) && (tmp_pi1 == (int *)tmp_pu2[2])) {
          tmp_pu2[2] = 0;
        }
        CG_FreeTrailJunc(tmp_pu2);
      }
    }
    tmp_pi1[6] = 0;
    tmp_pi1[7] = 1;
    if (*tmp_pi1 != 0) {
      *(int *)(*tmp_pi1 + 4) = tmp_pi1[1];
    }
    if ((int *)tmp_pi1[1] != (int *)0x0) {
      *(int *)tmp_pi1[1] = *tmp_pi1;
    }
    if (tmp_pi1 == activeTrails) {
      activeTrails = (int *)*tmp_pi1;
    }
    tmp_pi3 = (int *)tmp_pi1[3];
    if (tmp_pi1 == headTrails) {
      headTrails = tmp_pi3;
    }
    if (tmp_pi3 != (int *)0x0) {
      tmp_pi3[4] = tmp_pi1[4];
    }
    if (tmp_pi1[4] != 0) {
      *(int *)(tmp_pi1[4] + 0xc) = tmp_pi1[3];
    }
    tmp_pi3 = freeTrails;
    tmp_pi1[3] = 0;
    tmp_pi1[4] = 0;
    tmp_pi1[1] = 0;
    *tmp_pi1 = (int)tmp_pi3;
    if (freeTrails != (int *)0x0) {
      freeTrails[1] = (int)tmp_pi1;
    }
    numTrailsInuse = numTrailsInuse + -1;
    freeTrails = tmp_pi1;
  }
  return;
}

void CG_TestModel_f(void)
{
  uint tmp_u1;
  uint tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint32_t local_18;
  float local_14;
  uint32_t local_10;
  
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)&g_unk_010aad7c + tmp_u2) = 0;
    *(uint32_t *)((int)&g_unk_010aad80 + tmp_u2) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xe8);
  *(uint32_t *)((int)&g_unk_010aad84 + tmp_u2) = 0;
  tmp_i3 = trap_Argc();
  if (tmp_i3 == 0) {
    tmp_u4 = CG_Argv(1);
    Q_strncpyz(&g_unk_010aae68,tmp_u4,0x40);
    g_unk_010aad84 = trap_R_RegisterModel(&g_unk_010aae68);
    if (g_unk_010aad84 != 0) {
      g_unk_010aade4 = g_unk_010918cc * 100.0 + g_unk_010918c0;
      local_18 = 0;
      local_10 = 0;
      g_unk_010aade8 = g_unk_010918d0 * 100.0 + g_unk_010918c4;
      g_unk_010aadec = g_unk_010918d4 * 100.0 + g_unk_010918c8;
      local_14 = g_unk_01091a58 + 180.0;
      AnglesToAxis(&local_18,&g_unk_010aad98);
      g_unk_010aaea8 = 0;
      return;
    }
    CG_Printf("Can\'t register model\n");
  }
  return;
}

void CG_TestGun_f(void)
{
  uint tmp_u1;
  uint tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint32_t local_18;
  float local_14;
  uint32_t local_10;
  
  tmp_u1 = 0;
  do {
    tmp_u2 = tmp_u1;
    *(uint32_t *)((int)&g_unk_010aad7c + tmp_u2) = 0;
    *(uint32_t *)((int)&g_unk_010aad80 + tmp_u2) = 0;
    tmp_u1 = tmp_u2 + 8;
  } while (tmp_u2 + 8 < 0xe8);
  *(uint32_t *)((int)&g_unk_010aad84 + tmp_u2) = 0;
  tmp_i3 = trap_Argc();
  if (tmp_i3 == 0) {
    tmp_u4 = CG_Argv(1);
    Q_strncpyz(&g_unk_010aae68,tmp_u4,0x40);
    g_unk_010aad84 = trap_R_RegisterModel(&g_unk_010aae68);
    if (g_unk_010aad84 == 0) {
      CG_Printf("Can\'t register model\n");
    }
    else {
      g_unk_010aade4 = g_unk_010918cc * 100.0 + g_unk_010918c0;
      local_18 = 0;
      local_10 = 0;
      g_unk_010aade8 = g_unk_010918d0 * 100.0 + g_unk_010918c4;
      g_unk_010aadec = g_unk_010918d4 * 100.0 + g_unk_010918c8;
      local_14 = g_unk_01091a58 + 180.0;
      AnglesToAxis(&local_18,&g_unk_010aad98);
    }
  }
  g_unk_010aaea8 = 1;
  g_unk_010aad80 = 0xd;
  return;
}

void CG_TestModelNextFrame_f(void)
{
  g_unk_010aadf0 = g_unk_010aadf0 + 1;
  CG_Printf("frame %i\n",g_unk_010aadf0);
  return;
}

void CG_TestModelPrevFrame_f(void)
{
  g_unk_010aadf0 = g_unk_010aadf0 + -1;
  if (g_unk_010aadf0 < 0) {
    g_unk_010aadf0 = 0;
  }
  CG_Printf("frame %i\n",g_unk_010aadf0);
  return;
}

void CG_TestModelNextSkin_f(void)
{
  g_unk_010aae24 = g_unk_010aae24 + 1;
  CG_Printf("skin %i\n",g_unk_010aae24);
  return;
}

void CG_TestModelPrevSkin_f(void)
{
  g_unk_010aae24 = g_unk_010aae24 + -1;
  if (g_unk_010aae24 < 0) {
    g_unk_010aae24 = 0;
  }
  CG_Printf("skin %i\n",g_unk_010aae24);
  return;
}

void CG_Letterbox(float param_1,float param_2,int param_3)
{
  g_unk_010918b0 = (int)ROUND(((float)(int)GHIDRA_FIELD(cgs, 27336, 4) * param_1) / 100.0) & 0xfffffffe;
  g_unk_010918b4 = (int)ROUND(((float)(int)GHIDRA_FIELD(cgs, 27340, 4) * param_2) / 100.0) & 0xfffffffe;
  if (param_3 != 0) {
    g_unk_010918a8 = (int)(GHIDRA_FIELD(cgs, 27336, 4) - g_unk_010918b0) / 2;
    g_unk_010918ac = (int)(GHIDRA_FIELD(cgs, 27340, 4) - g_unk_010918b4) / 2;
  }
  return;
}

void CG_OffsetThirdPersonView(void)
{
  float tmp_f1;
  float tmp_f2;
  double tmp_d3;
  float tmp_f4;
  float local_c8;
  float local_c4;
  float local_c0;
  double local_b4;
  double local_ac;
  float local_a0;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  uint32_t local_58;
  uint8_t local_54 [8];
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  uint32_t uStack_14;
  
  uStack_14 = 0xcaf99;
  *(float *)(g_unk_010afbcc + 0x20) = (float)g_unk_010907b8 + *(float *)(g_unk_010afbcc + 0x20);
  local_60 = g_unk_01091a54;
  local_58 = g_unk_01091a5c;
  if ((g_unk_010907cc < 1) && (*(int *)(g_unk_01047b00 + 0x43c) != 7)) {
    local_a0 = (float)g_unk_010907d4 * 0.005493164;
    g_unk_01091a58 = local_a0;
  }
  if (45.0 < g_unk_01091a54) {
    local_60 = 45.0;
  }
  local_5c = g_unk_01091a58;
  AngleVectors(&local_60,&local_90,0);
  if (GHIDRA_FIELD(cg_thirdPerson, 12, 4) == 2) {
    local_c8 = g_unk_01090710;
    local_c4 = g_unk_01090714;
    local_c0 = g_unk_01090718;
    local_6c = *(float *)(g_unk_010afbcc + 0x18);
    local_68 = *(float *)(g_unk_010afbcc + 0x1c);
    local_64 = *(float *)(g_unk_010afbcc + 0x20);
  }
  else {
    local_6c = *(float *)(g_unk_010afbcc + 0x18);
    local_c8 = local_90 * 400.0 + local_6c;
    local_68 = *(float *)(g_unk_010afbcc + 0x1c);
    local_c4 = local_8c * 400.0 + local_68;
    local_64 = *(float *)(g_unk_010afbcc + 0x20);
    local_c0 = local_88 * 400.0 + local_64;
  }
  local_64 = local_64 + 8.0;
  g_unk_01091a54 = g_unk_01091a54 * 0.5;
  AngleVectors(&g_unk_01091a54,&local_90,&local_84);
  sincos((double)(((float)GHIDRA_FIELD(cg_thirdPersonAngle, 8, 4) / 180.0) * 3.1415927),&local_ac,&local_b4);
  tmp_f1 = (float)local_b4 * -(float)GHIDRA_FIELD(cg_thirdPersonRange, 8, 4);
  local_a0 = (float)local_ac;
  tmp_f2 = local_a0 * -(float)GHIDRA_FIELD(cg_thirdPersonRange, 8, 4);
  local_6c = local_84 * tmp_f2 + tmp_f1 * local_90 + local_6c;
  local_68 = local_80 * tmp_f2 + local_8c * tmp_f1 + local_68;
  local_64 = tmp_f2 * local_7c + local_64 + local_88 * tmp_f1;
  CG_Trace(local_54,g_unk_010afbcc + 0x18,mins_11986,maxs_11987,&local_6c,g_unk_0109079c,1);
  if (local_4c != 1.0) {
    local_6c = local_48;
    local_68 = local_44;
    local_64 = (1.0 - local_4c) * 32.0 + local_40;
    CG_Trace(local_54,g_unk_010afbcc + 0x18,mins_11986,maxs_11987,&local_6c,g_unk_0109079c,1);
    local_6c = local_48;
    local_68 = local_44;
    local_64 = local_40;
  }
  *(float *)(g_unk_010afbcc + 0x18) = local_6c;
  *(float *)(g_unk_010afbcc + 0x1c) = local_68;
  *(float *)(g_unk_010afbcc + 0x20) = local_64;
  local_c8 = local_c8 - *(float *)(g_unk_010afbcc + 0x18);
  local_c4 = local_c4 - *(float *)(g_unk_010afbcc + 0x1c);
  tmp_f1 = *(float *)(g_unk_010afbcc + 0x20);
  tmp_f2 = local_c4 * local_c4 + local_c8 * local_c8;
  tmp_f4 = SQRT(tmp_f2);
  if (NAN(tmp_f4)) {
    tmp_f4 = sqrtf(tmp_f2);
  }
  if (tmp_f4 < 1.0) {
    tmp_f4 = 1.0;
  }
  tmp_d3 = atan2((double)(local_c0 - tmp_f1),(double)tmp_f4);
  g_unk_01091a54 = (float)((long double)tmp_d3 * (long double)-57.29577951308232);
  g_unk_01091a58 = g_unk_01091a58 - (float)GHIDRA_FIELD(cg_thirdPersonAngle, 8, 4);
  return;
}

void CG_KickAngles(void)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  bool tmp_b4;
  int tmp_i5;
  uint32_t tmp_u6;
  int tmp_i7;
  double tmp_d8;
  float local_80;
  float local_7c;
  float local_78;
  float local_70;
  float local_68;
  char local_3c [40];
  uint32_t uStack_14;
  
  uStack_14 = 0xcb3e9;
  g_unk_010aaec8 = 0.0;
  if (0 < g_unk_010906dc) {
    local_68 = g_unk_010aaec4;
    local_80 = g_unk_010aaeac;
    local_78 = g_unk_010aaeb0;
    local_70 = 0.0;
    local_7c = g_unk_010aaeb4;
    tmp_i5 = g_unk_010906dc;
    do {
      tmp_i7 = 0x14;
      if (tmp_i5 < 0x15) {
        tmp_i7 = tmp_i5;
      }
      tmp_f3 = (float)tmp_i7 / 1000.0;
      if (local_80 == 0.0) {
        if (g_unk_010aaeb8 != 0.0) {
LAB_000cb6f9:
          tmp_f2 = 1.0;
          if (0.0 < g_unk_010aaeb8) {
            tmp_f2 = -1.0;
          }
          if (tmp_f2 * 2400.0 != 0.0) {
            local_80 = tmp_f2 * 2400.0 * tmp_f3 + local_80;
          }
          tmp_f2 = local_80 * tmp_f3;
          tmp_b4 = g_unk_010aaeb8 < 0.0;
          if (tmp_b4 != tmp_f2 < 0.0) {
            tmp_f2 = tmp_f2 * 0.06;
          }
          g_unk_010aaeb8 = tmp_f2 + g_unk_010aaeb8;
          if (0.0 <= g_unk_010aaeb8 != tmp_b4) goto LAB_000cb4b4;
          local_80 = 0.0;
          g_unk_010aaeb8 = 0.0;
        }
      }
      else {
        if (g_unk_010aaeb8 != 0.0) goto LAB_000cb6f9;
        g_unk_010aaeb8 = local_80 * tmp_f3 + g_unk_010aaeb8;
LAB_000cb4b4:
        if (g_unk_010aaeb8 == 0.0) {
          local_80 = 0.0;
        }
        else if (10.0 < ABS(g_unk_010aaeb8)) {
          tmp_f2 = 1.0;
          if (g_unk_010aaeb8 <= 0.0) {
            tmp_f2 = -1.0;
          }
          g_unk_010aaeb8 = tmp_f2 * 10.0;
          local_80 = 0.0;
        }
      }
      if (local_78 == 0.0) {
        if (g_unk_010aaebc == 0.0) goto LAB_000cb540;
LAB_000cb7b0:
        tmp_f2 = 1.0;
        if (0.0 < g_unk_010aaebc) {
          tmp_f2 = -1.0;
        }
        if (tmp_f2 * 2400.0 != 0.0) {
          local_78 = tmp_f2 * 2400.0 * tmp_f3 + local_78;
        }
        tmp_f2 = local_78 * tmp_f3;
        tmp_b4 = g_unk_010aaebc < 0.0;
        if (tmp_b4 != tmp_f2 < 0.0) {
          tmp_f2 = tmp_f2 * 0.06;
        }
        g_unk_010aaebc = tmp_f2 + g_unk_010aaebc;
        if (0.0 <= g_unk_010aaebc != tmp_b4) goto LAB_000cb500;
        g_unk_010aaebc = 0.0;
        local_78 = 0.0;
        if (!NAN(local_7c)) goto LAB_000cb540;
        g_unk_010aaebc = 0.0;
LAB_000cb852:
        if (g_unk_010aaec0 == 0.0) {
          g_unk_010aaec0 = local_7c * tmp_f3 + g_unk_010aaec0;
        }
        else {
LAB_000cb554:
          tmp_f2 = 1.0;
          if (0.0 < g_unk_010aaec0) {
            tmp_f2 = -1.0;
          }
          if (tmp_f2 * 2400.0 != 0.0) {
            local_7c = tmp_f2 * 2400.0 * tmp_f3 + local_7c;
          }
          tmp_f2 = local_7c * tmp_f3;
          tmp_b4 = g_unk_010aaec0 < 0.0;
          if (tmp_b4 != tmp_f2 < 0.0) {
            tmp_f2 = tmp_f2 * 0.06;
          }
          g_unk_010aaec0 = tmp_f2 + g_unk_010aaec0;
          if (tmp_b4 == 0.0 <= g_unk_010aaec0) {
            local_7c = 0.0;
            g_unk_010aaec0 = 0.0;
            goto LAB_000cb5f5;
          }
        }
        if (g_unk_010aaec0 == 0.0) {
          local_7c = 0.0;
        }
        else if (10.0 < ABS(g_unk_010aaec0)) {
          tmp_f2 = 1.0;
          if (g_unk_010aaec0 <= 0.0) {
            tmp_f2 = -1.0;
          }
          g_unk_010aaec0 = tmp_f2 * 10.0;
          local_7c = 0.0;
        }
      }
      else {
        if (g_unk_010aaebc != 0.0) goto LAB_000cb7b0;
        g_unk_010aaebc = local_78 * tmp_f3 + g_unk_010aaebc;
LAB_000cb500:
        if (g_unk_010aaebc == 0.0) {
          local_78 = 0.0;
        }
        else if (10.0 < ABS(g_unk_010aaebc)) {
          tmp_f2 = 1.0;
          if (g_unk_010aaebc <= 0.0) {
            tmp_f2 = -1.0;
          }
          g_unk_010aaebc = tmp_f2 * 10.0;
          local_78 = 0.0;
        }
LAB_000cb540:
        if (local_7c != 0.0) goto LAB_000cb852;
        if (g_unk_010aaec0 != 0.0) goto LAB_000cb554;
      }
LAB_000cb5f5:
      if (g_unk_010aaec4 == 0.0) {
        tmp_f2 = ABS(g_unk_010aaec4);
LAB_000cb690:
        if (15.0 < tmp_f2) {
          local_70 = tmp_f3 * g_unk_010aaec4 + local_70;
        }
      }
      else {
        tmp_f2 = ABS(g_unk_010aaec4);
        if (tmp_f2 <= 50.0) {
          if (g_unk_010aaec4 <= 0.0) goto LAB_000cb95e;
          tmp_f1 = -200.0;
        }
        else if (g_unk_010aaec4 <= 0.0) {
          g_unk_010aaec4 = -50.0;
          tmp_f2 = 50.0;
          local_68 = g_unk_010aaec4;
LAB_000cb95e:
          tmp_f1 = 200.0;
        }
        else {
          g_unk_010aaec4 = 50.0;
          tmp_f1 = -200.0;
          tmp_f2 = g_unk_010aaec4;
          local_68 = g_unk_010aaec4;
        }
        tmp_f1 = tmp_f1 * tmp_f3;
        if (tmp_f1 == 0.0) goto LAB_000cb690;
        if (ABS(tmp_f1) < tmp_f2) {
          g_unk_010aaec4 = tmp_f1 + g_unk_010aaec4;
          tmp_f2 = ABS(g_unk_010aaec4);
          local_68 = g_unk_010aaec4;
          goto LAB_000cb690;
        }
        local_68 = 0.0;
        g_unk_010aaec4 = 0.0;
      }
      tmp_i5 = tmp_i5 + -0x14;
    } while (0 < tmp_i5);
    g_unk_010aaeac = local_80;
    g_unk_010aaeb0 = local_78;
    g_unk_010aaeb4 = local_7c;
    g_unk_010aaec4 = local_68;
    g_unk_010aaec8 = local_70;
  }
  trap_Cvar_VariableStringBuffer("cg_recoilPitch",local_3c);
  tmp_d8 = strtod(local_3c,(char **)0x0);
  if ((double)g_unk_010aaec8 == tmp_d8) {
    return;
  }
  tmp_u6 = va(&g_unk_0011e95f,(double)g_unk_010aaec8);
  trap_Cvar_Set("cg_recoilPitch",tmp_u6);
  return;
}

void CG_ZoomIn_f(void)
{
  if (((*(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xe8) == 0x27) ||
      (*(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xe8) == 0x28)) ||
     (g_unk_01091a64 != 0)) {
    g_unk_01091a74 = g_unk_01091a74 - (float)GHIDRA_FIELD(cg_zoomStepSniper, 8, 4);
    if ((float)GHIDRA_FIELD(zoomTable, 16, 4) < g_unk_01091a74) {
      g_unk_01091a74 = (float)GHIDRA_FIELD(zoomTable, 16, 4);
    }
    if (g_unk_01091a74 < (float)GHIDRA_FIELD(zoomTable, 20, 4)) {
      g_unk_01091a74 = (float)GHIDRA_FIELD(zoomTable, 20, 4);
    }
  }
  return;
}

void CG_ZoomOut_f(void)
{
  if (*(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xe8) == 0x27) {
    g_unk_01091a74 = (float)GHIDRA_FIELD(cg_zoomStepSniper, 8, 4) + g_unk_01091a74;
    if ((float)GHIDRA_FIELD(zoomTable, 16, 4) < g_unk_01091a74) {
      g_unk_01091a74 = (float)GHIDRA_FIELD(zoomTable, 16, 4);
    }
  }
  else {
    if ((*(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xe8) != 0x28) &&
       (g_unk_01091a64 == 0)) {
      return;
    }
    g_unk_01091a74 = g_unk_01091a74 + (float)GHIDRA_FIELD(cg_zoomStepSniper, 8, 4);
    if ((float)GHIDRA_FIELD(zoomTable, 16, 4) < g_unk_01091a74) {
      g_unk_01091a74 = (float)GHIDRA_FIELD(zoomTable, 16, 4);
    }
  }
  if (g_unk_01091a74 < (float)GHIDRA_FIELD(zoomTable, 20, 4)) {
    g_unk_01091a74 = (float)GHIDRA_FIELD(zoomTable, 20, 4);
  }
  return;
}

void CG_Zoom(void)
{
  if (((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) != 0) || (g_unk_01047aec != 0)) {
    _DAT_01090764 = *(uint *)(g_unk_01047b00 + 0x94);
    g_unk_010907a0 = *(int *)(g_unk_01047b00 + 0xd0);
    if ((g_unk_010907a0 != 0x29) && ((g_unk_010907a0 != 0x27 && (g_unk_010907a0 != 0x28)))) {
      if ((_DAT_01090764 & 0x40000) == 0) {
        g_unk_01091a74 = 0.0;
        goto LAB_000cbd35;
      }
      goto LAB_000cbcb7;
    }
    if (g_unk_01091a74 == 0.0) {
      g_unk_01091a74 = (float)GHIDRA_FIELD(cg_zoomDefaultSniper, 8, 4);
    }
  }
  if ((_DAT_01090764 & 0x40000) == 0) {
LAB_000cbd35:
    if (g_unk_01091a64 != 0) {
      g_unk_01091a64 = 0;
      g_unk_01091a6c = g_unk_010906e0;
      if (2 < g_unk_01091814 - 0x27U) {
        g_unk_01091a64 = 0;
        g_unk_01091a74 = 0.0;
        return;
      }
      g_unk_01091a74 = (float)GHIDRA_FIELD(cg_zoomDefaultSniper, 8, 4);
      return;
    }
    if ((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) != 0) {
      return;
    }
    if (g_unk_01047aec != 0) {
      return;
    }
    if (g_unk_01091814 - 0x27U < 3) {
      return;
    }
    g_unk_01091a74 = 0.0;
    return;
  }
LAB_000cbcb7:
  if (g_unk_01091a64 == 0) {
    g_unk_01091a64 = 1;
    g_unk_01091a6c = g_unk_010906e0;
    g_unk_01091a74 = (float)GHIDRA_FIELD(cg_zoomDefaultSniper, 8, 4);
  }
  return;
}

bool CG_CalcFov(void)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  uint tmp_u5;
  bool tmp_b6;
  bool tmp_b7;
  double tmp_d8;
  float local_18;
  
  CG_Zoom();
  tmp_i4 = g_unk_01047b00;
  if ((g_unk_010907cc < 1) && ((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) == 0)) {
    g_unk_01091a64 = 0;
    g_unk_01091a6c = 0;
    g_unk_01091a74 = 0.0;
  }
  if (g_unk_01090700 == 5) {
    tmp_f2 = 90.0;
  }
  else {
    tmp_f1 = (float)GHIDRA_FIELD(cg_fov, 8, 4);
    if (GHIDRA_FIELD(developer, 12, 4) == 0) {
      tmp_f1 = 90.0;
      if ((90.0 <= (float)GHIDRA_FIELD(cg_fov, 8, 4)) &&
         (tmp_f1 = (float)GHIDRA_FIELD(cg_fov, 8, 4), 160.0 < (float)GHIDRA_FIELD(cg_fov, 8, 4))) {
        tmp_f1 = 160.0;
      }
      tmp_f2 = tmp_f1;
      if (g_unk_010906f4 != 0) goto LAB_000cbede;
    }
    if (g_unk_01091a74 == 0.0) {
      if (g_unk_01091a64 == 0) {
        tmp_f3 = (float)(g_unk_010906e0 - g_unk_01091a6c) / 150.0;
        tmp_f2 = tmp_f1;
        if (tmp_f3 < 1.0) {
          tmp_f2 = lastfov_12070 + (tmp_f1 - lastfov_12070) * tmp_f3;
        }
        goto LAB_000cbede;
      }
    }
    else {
      if (g_unk_01091a74 < 1.0) {
        lastfov_12070 = 1.0;
      }
      else {
        lastfov_12070 = 160.0;
        if (g_unk_01091a74 <= 160.0) {
          lastfov_12070 = g_unk_01091a74;
        }
      }
      if (g_unk_01091a64 == 0) {
        lastfov_12070 = g_unk_01091a74;
        tmp_f2 = g_unk_01091a74;
        goto LAB_000cbede;
      }
    }
    tmp_f3 = (float)(g_unk_010906e0 - g_unk_01091a6c) / 150.0;
    tmp_f2 = lastfov_12070;
    if (tmp_f3 <= 1.0) {
      lastfov_12070 = (lastfov_12070 - tmp_f1) * tmp_f3 + tmp_f1;
      tmp_f2 = lastfov_12070;
    }
  }
LAB_000cbede:
  *(uint *)(g_unk_010afbcc + 0x4c) = *(uint *)(g_unk_010afbcc + 0x4c) & 0xffffffbf;
  if ((*(int *)(tmp_i4 + 0x16c) == 0) && (*(int *)(tmp_i4 + 0xd0) != 0x2e)) {
    if ((*(byte *)(tmp_i4 + 0x95) & 0x80) != 0) {
      tmp_f2 = 75.0;
    }
  }
  else {
    tmp_f2 = 55.0;
  }
  if (g_unk_010abd78 == 0) {
    tmp_d8 = tan((double)((tmp_f2 / 360.0) * 3.1415927));
  }
  else {
    tmp_d8 = 0.5773502899955719;
    tmp_f2 = 60.0;
  }
  tmp_d8 = atan2((double)*(int *)(g_unk_010afbcc + 0xc),
                (double)((float)*(int *)(g_unk_010afbcc + 8) / (float)tmp_d8));
  local_18 = ((float)tmp_d8 * 360.0) / 3.1415927;
  tmp_u5 = CG_PointContents(&g_unk_010918c0,0xffffffff);
  tmp_b6 = (tmp_u5 & 0x38) == 0;
  if (tmp_b6) {
    *(uint *)(g_unk_010afbcc + 0x4c) = *(uint *)(g_unk_010afbcc + 0x4c) & 0xffffffef;
  }
  else {
    tmp_f1 = ((float)g_unk_010906e0 / 1000.0) * 0.4 * 3.1415927;
    tmp_d8 = sin((double)(tmp_f1 + tmp_f1));
    tmp_f2 = tmp_f2 + (float)tmp_d8;
    *(uint *)(g_unk_010afbcc + 0x4c) = *(uint *)(g_unk_010afbcc + 0x4c) | 0x10;
    local_18 = local_18 - (float)tmp_d8;
  }
  tmp_b7 = (g_unk_01090766 & 0x20) != 0;
  if (tmp_b7) {
    tmp_f1 = ((float)g_unk_010906e0 / 1000.0) * 0.3 * 3.1415927;
    tmp_d8 = sin((double)(tmp_f1 + tmp_f1));
    tmp_f2 = tmp_f2 + (float)tmp_d8 * 12.0;
    *(uint *)(g_unk_010afbcc + 0x4c) = *(uint *)(g_unk_010afbcc + 0x4c) | 0x10;
    local_18 = local_18 - (float)tmp_d8 * 12.0;
  }
  tmp_b7 = tmp_b7 || !tmp_b6;
  *(float *)(g_unk_010afbcc + 0x10) = tmp_f2;
  *(float *)(g_unk_010afbcc + 0x14) = local_18;
  if ((*(int *)(g_unk_01047b00 + 0x30) == 4) ||
     (((*(int *)(g_unk_01047b00 + 0x30) == 3 && ((*(uint *)(g_unk_01047b00 + 0x38) & 0x4000) != 0)) ||
      ((*(uint *)(g_unk_01047b00 + 0x38) & 0x8000) != 0)))) {
    g_unk_01091a70 = 0.0;
    return tmp_b7;
  }
  if (g_unk_01091a64 != 0) {
    g_unk_01091a70 = *(float *)(g_unk_010afbcc + 0x14) / 75.0;
    return tmp_b7;
  }
  if (g_unk_01091a74 == 0.0) {
    g_unk_01091a70 = 1.0;
    return tmp_b7;
  }
  g_unk_01091a70 = (g_unk_01091a74 / 90.0) * 0.6;
  return tmp_b7;
}

void CG_CalcViewValues(void)
{
  uint32_t tmp_u1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint tmp_u6;
  uint tmp_u7;
  uint16_t *tmp_pu8;
  uint32_t *tmp_pu9;
  int tmp_i10;
  int tmp_i11;
  bool tmp_b12;
  double tmp_d13;
  float tmp_f14;
  uint local_64;
  uint32_t local_4c;
  float local_34;
  float local_30 [4];
  float local_20;
  uint32_t uStack_14;
  
  tmp_pu8 = g_unk_010afbcc;
  tmp_u7 = 0x1ac;
  uStack_14 = 0xcc2be;
  tmp_b12 = ((uint)g_unk_010afbcc & 1) != 0;
  if (tmp_b12) {
    *(uint8_t *)g_unk_010afbcc = 0;
    tmp_u7 = 0x1ab;
    tmp_pu8 = (uint16_t *)((int)tmp_pu8 + 1);
  }
  if (((uint)tmp_pu8 & 2) != 0) {
    *tmp_pu8 = 0;
    tmp_u7 = tmp_u7 - 2;
    tmp_pu8 = tmp_pu8 + 1;
  }
  tmp_u6 = 0;
  do {
    *(uint32_t *)((int)tmp_pu8 + tmp_u6) = 0;
    *(uint32_t *)((int)tmp_pu8 + tmp_u6 + 4) = 0;
    tmp_u6 = tmp_u6 + 8;
  } while (tmp_u6 < (tmp_u7 & 0xfffffff8));
  tmp_pu9 = (uint32_t *)((int)tmp_pu8 + tmp_u6);
  if ((tmp_u7 & 4) != 0) {
    *tmp_pu9 = 0;
    tmp_pu9 = tmp_pu9 + 1;
  }
  if ((tmp_u7 & 2) != 0) {
    *(uint16_t *)tmp_pu9 = 0;
    tmp_pu9 = (uint32_t *)((int)tmp_pu9 + 2);
  }
  if (tmp_b12) {
    *(uint8_t *)tmp_pu9 = 0;
  }
  if (g_unk_010abd78 == 0) {
    g_unk_010918b0 = (int)ROUND(((float)(int)GHIDRA_FIELD(cgs, 27336, 4) * 100.0) / 100.0) & 0xfffffffe;
    g_unk_010918b4 = (int)ROUND(((float)(int)GHIDRA_FIELD(cgs, 27340, 4) * 100.0) / 100.0) & 0xfffffffe;
    g_unk_010918a8 = (int)(GHIDRA_FIELD(cgs, 27336, 4) - g_unk_010918b0) / 2;
    g_unk_010918ac = (int)(GHIDRA_FIELD(cgs, 27340, 4) - g_unk_010918b4) / 2;
  }
  else {
    local_34 = 287.0;
    local_30[0] = 382.0;
    local_30[1] = 128.0;
    local_30[2] = 96.0;
    CG_AdjustFrom640(&local_34,local_30,local_30 + 1,local_30 + 2);
    g_unk_010918a8 = (int)ROUND(local_34);
    g_unk_010918ac = (int)ROUND(local_30[0]);
    g_unk_010918b0 = (int)ROUND(((float)(int)GHIDRA_FIELD(cgs, 27336, 4) * 20.0) / 100.0) & 0xfffffffe;
    g_unk_010918b4 = (int)ROUND(((float)(int)GHIDRA_FIELD(cgs, 27340, 4) * 20.0) / 100.0) & 0xfffffffe;
  }
  if (g_unk_01090700 == 5) {
    *(uint32_t *)(g_unk_010afbcc + 0xc) = g_unk_01090710;
    *(uint32_t *)(g_unk_010afbcc + 0xe) = g_unk_01090714;
    *(uint32_t *)(g_unk_010afbcc + 0x10) = g_unk_01090718;
    g_unk_01091a54 = g_unk_010907ac;
    g_unk_01091a58 = g_unk_010907b0;
    g_unk_01091a5c = g_unk_010907b4;
    AnglesToAxis(&g_unk_01091a54,g_unk_010afbcc + 0x12);
    CG_CalcFov();
    return;
  }
  if ((0.0 < g_unk_010aad68) && (g_unk_01090704 == 0)) {
    g_unk_010aad70 = g_unk_010aad68;
    g_unk_010aad74 = g_unk_010aad6c;
  }
  g_unk_010aad6c = (int)(g_unk_01090704 & 0x80) >> 7;
  tmp_d13 = sin((double)(((float)(g_unk_01090704 & 0x7f) / 127.0) * 3.1415927));
  g_unk_010aad68 = ABS((float)tmp_d13);
  tmp_f2 = g_unk_01090720 * g_unk_01090720 + g_unk_0109071c * g_unk_0109071c;
  tmp_f14 = SQRT(tmp_f2);
  if (NAN(tmp_f14)) {
    tmp_f14 = sqrtf(tmp_f2);
  }
  tmp_i10 = g_unk_01090b10;
  g_unk_010aad78 = tmp_f14;
  if (g_unk_010abd78 == 0) {
    if ((g_unk_010906f4 == 0) || ((_DAT_01090764 & 0x20) == 0)) {
      if ((_DAT_01090764 & 0x8000) == 0) {
        *(uint32_t *)(g_unk_010afbcc + 0xc) = g_unk_01090710;
        *(uint32_t *)(g_unk_010afbcc + 0xe) = g_unk_01090714;
        *(uint32_t *)(g_unk_010afbcc + 0x10) = g_unk_01090718;
      }
      else {
        tmp_i10 = *(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xab4) * 0xaf8;
        *(uint32_t *)(g_unk_010afbcc + 0xc) = *(uint32_t *)(cg_entities + tmp_i10 + 0xa50);
        *(uint32_t *)(g_unk_010afbcc + 0xe) = *(uint32_t *)(cg_entities + tmp_i10 + 0xa54);
        *(uint32_t *)(g_unk_010afbcc + 0x10) = *(uint32_t *)(cg_entities + tmp_i10 + 0xa58);
      }
      g_unk_01091a54 = g_unk_010907ac;
      g_unk_01091a58 = g_unk_010907b0;
      g_unk_01091a5c = g_unk_010907b4;
    }
    else {
      AngleVectors(&g_unk_010907ac,local_30 + 2,0,0);
      tmp_i10 = tmp_i10 * 0xaf8;
      *(float *)(g_unk_010afbcc + 0xc) = local_30[2] * -36.0 + *(float *)(cg_entities + tmp_i10 + 0x18)
      ;
      *(float *)(g_unk_010afbcc + 0xe) = local_30[3] * -36.0 + *(float *)(cg_entities + tmp_i10 + 0x1c)
      ;
      *(float *)(g_unk_010afbcc + 0x10) = local_20 * -36.0 + *(float *)(cg_entities + tmp_i10 + 0x20);
      *(uint32_t *)(g_unk_010afbcc + 0x10) = g_unk_01090718;
      g_unk_01091a54 = g_unk_010907ac;
      g_unk_01091a58 = g_unk_010907b0;
      g_unk_01091a5c = g_unk_010907b4;
    }
  }
  else {
    *(uint32_t *)(g_unk_010afbcc + 0xc) = GHIDRA_FIELD(cgs, 33685936, 4);
    *(uint32_t *)(g_unk_010afbcc + 0xe) = GHIDRA_FIELD(cgs, 33685940, 4);
    *(uint32_t *)(g_unk_010afbcc + 0x10) = GHIDRA_FIELD(cgs, 33685944, 4);
    if ((g_unk_010abd78 == 0) || (GHIDRA_FIELD(cgs, 33685960, 4) == -1)) {
      g_unk_01091a54 = (float)GHIDRA_FIELD(cgs, 33685948, 4);
      g_unk_01091a58 = (float)GHIDRA_FIELD(cgs, 33685952, 4);
      g_unk_01091a5c = (float)GHIDRA_FIELD(cgs, 33685956, 4);
    }
    else {
      tmp_i10 = GHIDRA_FIELD(cgs, 33685960, 4) * 0xaf8;
      local_30[2] = *(float *)(cg_entities + tmp_i10 + 0x794) - *(float *)(g_unk_010afbcc + 0xc);
      local_30[3] = *(float *)(cg_entities + tmp_i10 + 0x798) - *(float *)(g_unk_010afbcc + 0xe);
      local_20 = *(float *)(cg_entities + tmp_i10 + 0x79c) - *(float *)(g_unk_010afbcc + 0x10);
      vectoangles(local_30 + 2,&g_unk_01091a54);
    }
  }
  if (g_unk_010abd78 != 0) goto LAB_000cc640;
  if (0.0 < (float)GHIDRA_FIELD(cg_errorDecay, 8, 4)) {
    tmp_f2 = 500.0;
    if ((float)GHIDRA_FIELD(cg_errorDecay, 8, 4) <= 500.0) {
      tmp_f2 = (float)GHIDRA_FIELD(cg_errorDecay, 8, 4);
    }
    tmp_f2 = ((float)GHIDRA_FIELD(cg_errorDecay, 8, 4) - (float)(g_unk_010906e0 - g_unk_010917a4)) / tmp_f2;
    if ((tmp_f2 <= 0.0) || (1.0 <= tmp_f2)) {
      g_unk_010917a4 = 0;
    }
    else {
      *(float *)(g_unk_010afbcc + 0xc) = g_unk_010917a8 * tmp_f2 + *(float *)(g_unk_010afbcc + 0xc);
      *(float *)(g_unk_010afbcc + 0xe) = g_unk_010917ac * tmp_f2 + *(float *)(g_unk_010afbcc + 0xe);
      *(float *)(g_unk_010afbcc + 0x10) = tmp_f2 * g_unk_010917b0 + *(float *)(g_unk_010afbcc + 0x10);
    }
  }
  if (g_unk_01090b0c != 0) {
    if ((1 < g_unk_01090b0c - 2U) && (g_unk_01090b0c != 7)) {
      BG_EvaluateTrajectory
                (g_unk_01090b10 * 0xaf8 + 0x3133e70,g_unk_010906e0,&g_unk_01091a54,1,
                 *(uint32_t *)(cg_entities + g_unk_01090b10 * 0xaf8 + 0x110));
    }
    if (g_unk_01090b0c == 2) {
      local_64 = rand();
      local_64 = local_64 & 0x7fff;
      tmp_f2 = (float)local_64 / 32767.0 - 0.5;
      g_unk_01091a54 = tmp_f2 + tmp_f2 + g_unk_01091a54;
      local_64 = rand();
      local_64 = local_64 & 0x7fff;
      tmp_f2 = (float)local_64 / 32767.0 - 0.5;
      g_unk_01091a58 = tmp_f2 + tmp_f2 + g_unk_01091a58;
    }
  }
  tmp_pu8 = g_unk_010afbcc;
  if (g_unk_010906f4 == 0) {
    if (*(int *)(g_unk_01047b00 + 0x30) != 5) {
      if (*(int *)(g_unk_01047b00 + 0xd0) == 0x2e) {
        local_4c = *(uint32_t *)(g_unk_010afbcc + 0x10);
        AngleVectors(&g_unk_010b16a4,local_30 + 2,0,0);
        tmp_f2 = local_30[2] * 31.0 + *(float *)(tmp_pu8 + 0xc);
        tmp_f14 = *(float *)(tmp_pu8 + 0xe) + local_30[3] * 31.0;
LAB_000cd26b:
        AngleVectors(&g_unk_01091a54,local_30 + 2,0,0);
        *(float *)(tmp_pu8 + 0xc) = tmp_f2 + local_30[2] * -32.0;
        *(float *)(tmp_pu8 + 0xe) = local_30[3] * -32.0 + tmp_f14;
        *(uint32_t *)(tmp_pu8 + 0x10) = local_4c;
      }
      else if (*(int *)(g_unk_01047b00 + 0xd0) == 0x2a) {
        local_4c = *(uint32_t *)(g_unk_010afbcc + 0x10);
        AngleVectors(&g_unk_010b16a4,local_30 + 2,0,0);
        tmp_f2 = local_30[2] * 31.0 + *(float *)(tmp_pu8 + 0xc);
        tmp_f14 = *(float *)(tmp_pu8 + 0xe) + local_30[3] * 31.0;
        goto LAB_000cd26b;
      }
      if (((*(byte *)(g_unk_01047b00 + 0x39) & 0x40) == 0) && (*(int *)(g_unk_01047b00 + 0xfc) < 1)) {
        g_unk_01091a5c = 40.0;
        g_unk_01091a54 = -15.0;
        if (*(int *)(g_unk_01047b00 + 0x43c) == 7) {
          g_unk_01091a58 = 0.0;
        }
        else {
          g_unk_01091a58 = (float)*(int *)(g_unk_01047b00 + 0x104) * 0.005493164;
        }
        *(float *)(tmp_pu8 + 0x10) = (float)g_unk_010907b8 + *(float *)(tmp_pu8 + 0x10);
      }
      else if ((*(byte *)(g_unk_01047b00 + 0x96) & 0x80) == 0) {
        CG_KickAngles();
        tmp_f2 = g_unk_01091a54 + g_unk_010aaeb8;
        g_unk_01091a58 = g_unk_01091a58 + g_unk_010aaebc;
        tmp_f14 = g_unk_01091a5c + g_unk_010aaec0;
        if (g_unk_010aace0 != 0.0) {
          tmp_f4 = (float)g_unk_010906e0 - g_unk_010aace0;
          if (100.0 <= tmp_f4) {
            tmp_f4 = 1.0 - (tmp_f4 - 100.0) / 400.0;
            if (tmp_f4 <= 0.0) goto LAB_000ccd32;
          }
          else {
            tmp_f4 = tmp_f4 / 100.0;
          }
          tmp_f2 = g_unk_010aad44 * tmp_f4 + tmp_f2;
          tmp_f14 = tmp_f4 * g_unk_010aad48 + tmp_f14;
        }
LAB_000ccd32:
        tmp_f4 = g_unk_010aad78;
        if (g_unk_010aad78 <= 200.0) {
          tmp_f4 = 200.0;
        }
        if ((g_unk_010aad68 != 0.0) || (g_unk_010aad70 <= 0.0)) {
          tmp_f3 = (float)GHIDRA_FIELD(cg_bobpitch, 8, 4) * g_unk_010aad68 * tmp_f4;
          if ((g_unk_01090708 & 1) == 0) {
            tmp_f4 = tmp_f4 * (float)GHIDRA_FIELD(cg_bobroll, 8, 4) * g_unk_010aad68;
          }
          else {
            tmp_f3 = tmp_f3 * 3.0;
            tmp_f4 = g_unk_010aad68 * (float)GHIDRA_FIELD(cg_bobroll, 8, 4) * tmp_f4 * 3.0;
          }
          tmp_f5 = -tmp_f4;
          if ((g_unk_010aad6c & 1) == 0) {
            tmp_f5 = tmp_f4;
          }
        }
        else {
          g_unk_010aad70 = g_unk_010aad70 - (float)g_unk_010906dc * 0.005;
          tmp_f3 = (float)GHIDRA_FIELD(cg_bobpitch, 8, 4) * g_unk_010aad70 * tmp_f4;
          if ((g_unk_01090708 & 1) == 0) {
            tmp_f4 = tmp_f4 * (float)GHIDRA_FIELD(cg_bobroll, 8, 4) * g_unk_010aad70;
          }
          else {
            tmp_f3 = tmp_f3 * 3.0;
            tmp_f4 = g_unk_010aad70 * (float)GHIDRA_FIELD(cg_bobroll, 8, 4) * tmp_f4 * 3.0;
          }
          tmp_f5 = -tmp_f4;
          if ((g_unk_010aad74 & 1) == 0) {
            tmp_f5 = tmp_f4;
          }
        }
        g_unk_01091a54 = tmp_f3 + (g_unk_01090724 * *(float *)(g_unk_010afbcc + 0x16) +
                               g_unk_01090720 * *(float *)(g_unk_010afbcc + 0x14) +
                               g_unk_0109071c * *(float *)(g_unk_010afbcc + 0x12)) *
                               (float)GHIDRA_FIELD(cg_runpitch, 8, 4) + tmp_f2;
        g_unk_01091a5c = tmp_f5 + (tmp_f14 - (g_unk_01090724 * *(float *)(g_unk_010afbcc + 0x1c) +
                                         g_unk_01090720 * *(float *)(g_unk_010afbcc + 0x1a) +
                                         g_unk_0109071c * *(float *)(g_unk_010afbcc + 0x18)) *
                                         (float)GHIDRA_FIELD(cg_runroll, 8, 4));
        tmp_f2 = (float)g_unk_010907b8 + *(float *)(tmp_pu8 + 0x10);
        *(float *)(tmp_pu8 + 0x10) = tmp_f2;
        tmp_i10 = g_unk_010906e0 - g_unk_01091804;
        if ((_DAT_01090764 & 0x80000) == 0) {
          if (g_unk_01091808 == 0) {
            if (tmp_i10 < 0) {
              g_unk_01091804 = g_unk_010906e0 + -100;
            }
            else if (99 < tmp_i10) goto LAB_000cce7c;
            *(float *)(g_unk_010afbcc + 0x10) =
                 *(float *)(g_unk_010afbcc + 0x10) - ((float)(100 - tmp_i10) * g_unk_01091800) / 100.0;
            tmp_f2 = *(float *)(tmp_pu8 + 0x10);
          }
          else {
            if (tmp_i10 < 0) {
              g_unk_01091804 = g_unk_010906e0 + -0x2ee;
            }
            else if (0x2ed < tmp_i10) goto LAB_000cce7c;
            *(float *)(g_unk_010afbcc + 0x10) =
                 *(float *)(g_unk_010afbcc + 0x10) - ((float)(0x2ee - tmp_i10) * g_unk_01091800) / 750.0;
            tmp_f2 = *(float *)(tmp_pu8 + 0x10);
          }
        }
        else {
          if (tmp_i10 < 0) {
            g_unk_01091804 = g_unk_010906e0 + -500;
          }
          else if (499 < tmp_i10) goto LAB_000cce7c;
          *(float *)(g_unk_010afbcc + 0x10) =
               *(float *)(g_unk_010afbcc + 0x10) - ((float)(500 - tmp_i10) * g_unk_01091800) / 500.0;
          tmp_f2 = *(float *)(tmp_pu8 + 0x10);
        }
LAB_000cce7c:
        tmp_f14 = g_unk_010aad68 * g_unk_010aad78 * (float)GHIDRA_FIELD(cg_bobup, 8, 4);
        if (6.0 < tmp_f14) {
          tmp_f14 = 6.0;
        }
        *(float *)(tmp_pu8 + 0x10) = tmp_f14 + tmp_f2;
        tmp_f2 = (float)(g_unk_010906e0 - g_unk_01091810);
        if (tmp_f2 < 0.0) {
          g_unk_01091810 = g_unk_010906e0 + -0x1c2;
        }
        if (150.0 <= tmp_f2) {
          if (tmp_f2 < 450.0) {
            *(float *)(g_unk_010afbcc + 0x10) =
                 (1.0 - (tmp_f2 - 150.0) / 300.0) * g_unk_0109180c + *(float *)(g_unk_010afbcc + 0x10);
          }
        }
        else {
          *(float *)(g_unk_010afbcc + 0x10) =
               (tmp_f2 / 150.0) * g_unk_0109180c + *(float *)(g_unk_010afbcc + 0x10);
        }
        tmp_i11 = g_unk_010906e0 - g_unk_010917fc;
        tmp_i10 = g_unk_010906e0;
        if ((tmp_i11 < 0) || (tmp_i10 = g_unk_010917fc, tmp_i11 < 200)) {
          g_unk_010917fc = tmp_i10;
          *(float *)(g_unk_010afbcc + 0x10) =
               *(float *)(g_unk_010afbcc + 0x10) - ((float)(200 - tmp_i11) * g_unk_010917f8) / 200.0;
        }
        if ((g_unk_01091a74 != 0.0) && ((*(byte *)(g_unk_01047b00 + 0x94) & 0x20) == 0)) {
          if (*(int *)(g_unk_01047b00 + 0xd0) == 0x29) {
            tmp_f2 = 0.8;
            tmp_f14 = 0.4;
          }
          else {
            tmp_f2 = 0.2;
            tmp_f14 = 0.1;
          }
          tmp_f4 = (float)*(int *)(g_unk_01047b00 + 0x4b8) / 255.0;
          tmp_f5 = (float)g_unk_010906e0;
          tmp_f3 = (tmp_f5 / 1000.0) * 0.24 * 3.1415927;
          tmp_d13 = sin((double)(tmp_f3 + tmp_f3));
          g_unk_01091a54 = (tmp_f14 + tmp_f4) * (float)tmp_d13 * 0.13 + g_unk_01091a54;
          tmp_f14 = (tmp_f5 / 1000.0) * 0.12 * 3.1415927;
          tmp_d13 = sin((double)(tmp_f14 + tmp_f14));
          g_unk_01091a58 = (tmp_f4 + tmp_f2) * (float)tmp_d13 * 0.7 + g_unk_01091a58;
        }
        if ((_DAT_01090764 & 0x200000) != 0) {
          tmp_f2 = ((float)g_unk_010906e0 / 1000.0) * 0.3 * 3.1415927;
          tmp_d13 = sin((double)tmp_f2);
          g_unk_01091a5c = (float)tmp_d13 * 36.0 + g_unk_01091a5c;
          g_unk_01091a58 = (float)tmp_d13 * 24.0 + g_unk_01091a58;
          tmp_d13 = sin((double)tmp_f2 * 2.5);
          g_unk_01091a54 = (float)tmp_d13 * 12.0 + g_unk_01091a54;
        }
        if (g_unk_01090738 != 0.0) {
          if ((cgs[0x2038e69] & 1) == 0) {
            tmp_f2 = g_unk_01090738 * 0.5;
          }
          else {
            tmp_f2 = g_unk_01090738 / 3.2;
          }
          g_unk_01091a5c = tmp_f2 + g_unk_01091a5c;
          AngleVectors(&g_unk_01091a54,0,local_30 + 2,0);
          *(float *)(g_unk_010afbcc + 0xc) =
               local_30[2] * g_unk_01090738 + *(float *)(g_unk_010afbcc + 0xc);
          *(float *)(g_unk_010afbcc + 0xe) =
               local_30[3] * g_unk_01090738 + *(float *)(g_unk_010afbcc + 0xe);
          *(float *)(g_unk_010afbcc + 0x10) =
               local_20 * g_unk_01090738 + *(float *)(g_unk_010afbcc + 0x10);
        }
      }
      else {
        tmp_i10 = g_unk_010906e0 - g_unk_01091804;
        if (tmp_i10 < 0) {
          g_unk_01091804 = g_unk_010906e0 + -0x2ee;
LAB_000ccbc3:
          *(float *)(g_unk_010afbcc + 0x10) =
               *(float *)(g_unk_010afbcc + 0x10) - ((float)(0x2ee - tmp_i10) * g_unk_01091800) / 750.0;
        }
        else if (tmp_i10 < 0x2ee) goto LAB_000ccbc3;
        g_unk_01091a58 = (float)g_unk_010907d4 * 0.005493164 + g_unk_01091a58;
      }
    }
    if (g_unk_010b4554 != 0) {
      CG_SetViewanglesForSpeakerEditor();
    }
  }
  else {
    CG_OffsetThirdPersonView();
  }
  if (g_unk_01090b0c == 7) {
    tmp_i10 = g_unk_01090b10 * 0xaf8;
    local_30[2] = *(float *)(cg_entities + tmp_i10 + 0x794) - *(float *)(g_unk_010afbcc + 0xc);
    local_30[3] = *(float *)(cg_entities + tmp_i10 + 0x798) - *(float *)(g_unk_010afbcc + 0xe);
    local_20 = *(float *)(cg_entities + tmp_i10 + 0x79c) - *(float *)(g_unk_010afbcc + 0x10);
    vectoangles(local_30 + 2,&g_unk_01091a54);
  }
  else if (g_unk_01090b0c == 4) {
    AngleVectors(&g_unk_01091a54,local_30 + 2,0,0);
    *(float *)(g_unk_010afbcc + 0xc) =
         local_30[2] * 16.0 + *(float *)(cg_entities + g_unk_01090b10 * 0xaf8 + 0x794);
    *(float *)(g_unk_010afbcc + 0xe) =
         local_30[3] * 16.0 + *(float *)(cg_entities + g_unk_01090b10 * 0xaf8 + 0x798);
    *(float *)(g_unk_010afbcc + 0x10) =
         local_20 * 16.0 + *(float *)(cg_entities + g_unk_01090b10 * 0xaf8 + 0x79c);
  }
  else if ((g_unk_01090b0c != 0) && (g_unk_010906f4 == 0)) {
    tmp_u1 = *(uint32_t *)(g_unk_010afbcc + 0x10);
    AngleVectors(&g_unk_01091a54,local_30 + 2,0,0);
    *(float *)(g_unk_010afbcc + 0xc) =
         local_30[2] * -34.0 + *(float *)(cg_entities + g_unk_01090b10 * 0xaf8 + 0x794);
    *(float *)(g_unk_010afbcc + 0xe) =
         local_30[3] * -34.0 + *(float *)(cg_entities + g_unk_01090b10 * 0xaf8 + 0x798);
    *(float *)(g_unk_010afbcc + 0x10) =
         local_20 * -34.0 + *(float *)(cg_entities + g_unk_01090b10 * 0xaf8 + 0x79c);
    *(uint32_t *)(g_unk_010afbcc + 0x10) = tmp_u1;
  }
LAB_000cc640:
  AnglesToAxis(&g_unk_01091a54,g_unk_010afbcc + 0x12);
  if (g_unk_010906f8 != 0) {
    g_unk_010918f4 = g_unk_010918f4 | 5;
  }
  CG_CalcFov();
  return;
}

char * CG_MustParse(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  
  tmp_pc1 = (char *)COM_Parse(param_1);
  if (*tmp_pc1 == '\0') {
    CG_Error(param_2);
  }
  return tmp_pc1;
}

void CG_SetupFrustum(void)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  float tmp_f6;
  float tmp_f7;
  int tmp_i8;
  double local_2c;
  double local_24 [2];
  uint32_t uStack_14;
  
  tmp_i8 = g_unk_010afbcc;
  uStack_14 = 0xcdc59;
  sincos((double)((*(float *)(g_unk_010afbcc + 0x10) / 180.0) * 3.1415927 * 0.5),local_24,&local_2c);
  tmp_f4 = (float)local_24[0];
  tmp_f7 = (float)local_2c;
  tmp_f1 = *(float *)(tmp_i8 + 0x24);
  tmp_f5 = tmp_f1 * tmp_f4;
  tmp_f2 = *(float *)(tmp_i8 + 0x28);
  tmp_f6 = tmp_f2 * tmp_f4;
  tmp_f3 = *(float *)(tmp_i8 + 0x2c);
  tmp_f4 = tmp_f3 * tmp_f4;
  frustum = *(float *)(tmp_i8 + 0x30) * tmp_f7 + tmp_f5;
  g_unk_00c21aa4 = *(float *)(tmp_i8 + 0x34) * tmp_f7 + tmp_f6;
  g_unk_00c21aa8 = *(float *)(tmp_i8 + 0x38) * tmp_f7 + tmp_f4;
  tmp_f7 = -tmp_f7;
  g_unk_00c21ab0 = *(float *)(tmp_i8 + 0x30) * tmp_f7 + tmp_f5;
  g_unk_00c21ab4 = *(float *)(tmp_i8 + 0x34) * tmp_f7 + tmp_f6;
  g_unk_00c21ab8 = tmp_f7 * *(float *)(tmp_i8 + 0x38) + tmp_f4;
  sincos((double)((g_unk_010918bc / 180.0) * 3.1415927 * 0.5),local_24,&local_2c);
  tmp_f4 = (float)local_24[0];
  tmp_f5 = (float)local_2c;
  tmp_f1 = tmp_f1 * tmp_f4;
  tmp_f2 = tmp_f2 * tmp_f4;
  tmp_f4 = tmp_f4 * tmp_f3;
  g_unk_00c21ac0 = *(float *)(tmp_i8 + 0x3c) * tmp_f5 + tmp_f1;
  g_unk_00c21ac4 = *(float *)(tmp_i8 + 0x40) * tmp_f5 + tmp_f2;
  g_unk_00c21ac8 = *(float *)(tmp_i8 + 0x44) * tmp_f5 + tmp_f4;
  tmp_f5 = -tmp_f5;
  g_unk_00c21ad0 = *(float *)(tmp_i8 + 0x3c) * tmp_f5 + tmp_f1;
  g_unk_00c21ad4 = *(float *)(tmp_i8 + 0x40) * tmp_f5 + tmp_f2;
  g_unk_00c21ad8 = tmp_f5 * *(float *)(tmp_i8 + 0x44) + tmp_f4;
  tmp_f1 = *(float *)(tmp_i8 + 0x18);
  tmp_f2 = *(float *)(tmp_i8 + 0x1c);
  tmp_f3 = *(float *)(tmp_i8 + 0x20);
  g_unk_00c21aac = g_unk_00c21aa8 * tmp_f3 + g_unk_00c21aa4 * tmp_f2 + frustum * tmp_f1;
  g_unk_00c21abc = g_unk_00c21ab8 * tmp_f3 + g_unk_00c21ab4 * tmp_f2 + g_unk_00c21ab0 * tmp_f1;
  g_unk_00c21acc = g_unk_00c21ac8 * tmp_f3 + g_unk_00c21ac4 * tmp_f2 + g_unk_00c21ac0 * tmp_f1;
  g_unk_00c21adc = tmp_f3 * g_unk_00c21ad8 + tmp_f2 * g_unk_00c21ad4 + tmp_f1 * g_unk_00c21ad0;
  return;
}

bool CG_CullPoint(float *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  
  tmp_f1 = *param_1;
  tmp_f2 = param_1[1];
  tmp_f3 = param_1[2];
  if (((0.0 <= (g_unk_00c21aa8 * tmp_f3 + g_unk_00c21aa4 * tmp_f2 + frustum * tmp_f1) - g_unk_00c21aac) &&
      (0.0 <= (g_unk_00c21ab8 * tmp_f3 + g_unk_00c21ab4 * tmp_f2 + g_unk_00c21ab0 * tmp_f1) - g_unk_00c21abc))
     && (0.0 <= (g_unk_00c21ac8 * tmp_f3 + g_unk_00c21ac4 * tmp_f2 + g_unk_00c21ac0 * tmp_f1) - g_unk_00c21acc)
     ) {
    return (tmp_f3 * g_unk_00c21ad8 + tmp_f2 * g_unk_00c21ad4 + tmp_f1 * g_unk_00c21ad0) - g_unk_00c21adc < 0.0
    ;
  }
  return true;
}

bool CG_CullPointAndRadius(float *param_1,float param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  
  tmp_f1 = *param_1;
  tmp_f2 = param_1[1];
  tmp_f3 = param_1[2];
  param_2 = -param_2;
  if (((param_2 <= (g_unk_00c21aa8 * tmp_f3 + g_unk_00c21aa4 * tmp_f2 + frustum * tmp_f1) - g_unk_00c21aac)
      && (param_2 <=
          (g_unk_00c21ab8 * tmp_f3 + g_unk_00c21ab4 * tmp_f2 + g_unk_00c21ab0 * tmp_f1) - g_unk_00c21abc)) &&
     (param_2 <= (g_unk_00c21ac8 * tmp_f3 + g_unk_00c21ac4 * tmp_f2 + g_unk_00c21ac0 * tmp_f1) - g_unk_00c21acc
     )) {
    return (tmp_f3 * g_unk_00c21ad8 + tmp_f2 * g_unk_00c21ad4 + tmp_f1 * g_unk_00c21ad0) - g_unk_00c21adc <
           param_2;
  }
  return true;
}

void CG_PanzerFaustEjectBrass(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  float tmp_f3;
  float tmp_f4;
  int tmp_i5;
  int tmp_i6;
  uint tmp_u7;
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
  
  uStack_14 = 0xcf319;
  tmp_i6 = CG_AllocLocalEntity();
  *(uint32_t *)(tmp_i6 + 8) = 3;
  tmp_i5 = g_unk_010906e0;
  *(int *)(tmp_i6 + 0x10) = g_unk_010906e0;
  tmp_u2 = GHIDRA_FIELD(cg_brassTime, 12, 4);
  tmp_u7 = rand();
  *(int *)(tmp_i6 + 0x14) =
       (int)ROUND(((float)(tmp_u7 & 0x7fff) / 32767.0) * (float)(int)tmp_u2 +
                  (float)(tmp_i5 + tmp_u2 * 8));
  *(uint32_t *)(tmp_i6 + 0x20) = 6;
  tmp_i5 = g_unk_010906e0;
  tmp_u7 = rand();
  *(uint *)(tmp_i6 + 0x24) = tmp_i5 - (tmp_u7 & 0xf);
  AnglesToAxis(param_1 + 0x7a0,&local_40);
  tmp_f1 = local_28 * 24.0 + local_34 * -4.0 + local_40 * -24.0 + *(float *)(param_1 + 0x794);
  *(float *)(tmp_i6 + 0x100) = tmp_f1;
  tmp_f4 = local_24 * 24.0 + local_30 * -4.0 + local_3c * -24.0 + *(float *)(param_1 + 0x798);
  *(float *)(tmp_i6 + 0x104) = tmp_f4;
  tmp_f3 = local_20 * 24.0 + local_2c * -4.0 + local_38 * -24.0 + *(float *)(param_1 + 0x79c);
  *(float *)(tmp_i6 + 0x108) = tmp_f3;
  *(float *)(tmp_i6 + 0x2c) = tmp_f1;
  *(float *)(tmp_i6 + 0x30) = tmp_f4;
  *(float *)(tmp_i6 + 0x34) = tmp_f3;
  tmp_u7 = CG_PointContents(tmp_i6 + 0x100,0xffffffff);
  if ((tmp_u7 & 0x30) == 0) {
    tmp_f1 = 1.0;
  }
  else {
    tmp_f1 = 0.1;
  }
  *(float *)(tmp_i6 + 0x38) = (local_28 * 0.0 + local_34 * -200.0 + local_40 * 16.0) * tmp_f1;
  *(float *)(tmp_i6 + 0x3c) = (local_24 * 0.0 + local_30 * -200.0 + local_3c * 16.0) * tmp_f1;
  *(float *)(tmp_i6 + 0x40) = (local_20 * 0.0 + local_2c * -200.0 + local_38 * 16.0) * tmp_f1;
  AxisCopy(axisDefault,tmp_i6 + 0xb4);
  *(uint32_t *)(tmp_i6 + 0x1b0) = 0x40400000;
  *(uint32_t *)(tmp_i6 + 0xa0) = GHIDRA_FIELD(cgs, 67944, 4);
  *(float *)(tmp_i6 + 0x68) = tmp_f1 * 0.4;
  *(uint32_t *)(tmp_i6 + 0x44) = 2;
  tmp_i5 = g_unk_010906e0;
  *(uint32_t *)(tmp_i6 + 0x50) = 0;
  *(int *)(tmp_i6 + 0x48) = tmp_i5;
  tmp_u2 = *(uint32_t *)(param_1 + 0x40);
  *(uint32_t *)(tmp_i6 + 0xc) = 10;
  *(uint32_t *)(tmp_i6 + 0x54) = tmp_u2;
  *(uint32_t *)(tmp_i6 + 0x58) = 0;
  *(uint32_t *)(tmp_i6 + 0x5c) = 0;
  *(uint32_t *)(tmp_i6 + 0x60) = 0;
  *(uint32_t *)(tmp_i6 + 100) = 0;
  *(uint32_t *)(tmp_i6 + 0x94) = 0;
  *(uint32_t *)(tmp_i6 + 0x90) = 0;
  return;
}

void CG_CalculateWeaponPosition(float *param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  int tmp_i3;
  uint tmp_u4;
  double tmp_d5;
  float tmp_f6;
  float tmp_f7;
  float *pfVar8;
  float local_34;
  float local_30;
  float local_2c;
  uint8_t local_28 [20];
  uint32_t uStack_14;
  
  uStack_14 = 0xcf59d;
  *param_1 = *(float *)(g_unk_010afbcc + 0x18);
  param_1[1] = *(float *)(g_unk_010afbcc + 0x1c);
  param_1[2] = *(float *)(g_unk_010afbcc + 0x20);
  *param_2 = g_unk_01091a54;
  param_2[1] = g_unk_01091a58;
  param_2[2] = g_unk_01091a5c;
  if ((g_unk_01090765 & 0x80) != 0) {
    *param_2 = g_unk_01091a54 / 1.2;
  }
  if (((g_unk_010906f4 == 0) && ((g_unk_010907a0 & 0xfffffffb) == 0x2a)) && (g_unk_010907a4 != 1)) {
    *param_2 = g_unk_010b16a4;
  }
  if ((g_unk_01090766 & 0x10) == 0) {
    tmp_i3 = g_unk_010b3b2c + g_unk_010906e0;
    if (tmp_i3 < 200) {
      if (tmp_i3 == 0) {
        tmp_f7 = 3.0;
        tmp_f6 = -20.0;
      }
      else {
        tmp_f7 = 1.0 - 1.0 / (200.0 / (float)tmp_i3);
        tmp_f6 = tmp_f7 * -20.0;
        tmp_f7 = tmp_f7 * 3.0;
      }
      tmp_f2 = *(float *)(g_unk_010afbcc + 0x24) * tmp_f6 + *param_1;
      *param_1 = tmp_f2;
      tmp_f1 = *(float *)(g_unk_010afbcc + 0x28) * tmp_f6 + param_1[1];
      param_1[1] = tmp_f1;
      tmp_f6 = tmp_f6 * *(float *)(g_unk_010afbcc + 0x2c) + param_1[2];
      param_1[2] = tmp_f6;
      *param_1 = *(float *)(g_unk_010afbcc + 0x30) * tmp_f7 + tmp_f2;
      param_1[1] = *(float *)(g_unk_010afbcc + 0x34) * tmp_f7 + tmp_f1;
      param_1[2] = tmp_f7 * *(float *)(g_unk_010afbcc + 0x38) + tmp_f6;
    }
  }
  else {
    tmp_i3 = g_unk_010906e0 - g_unk_010b3b2c;
    if (0 < tmp_i3) {
      if (tmp_i3 < 0xc9) {
        tmp_f7 = 1.0 / (200.0 / (float)tmp_i3);
        tmp_f6 = tmp_f7 * -20.0;
        tmp_f7 = tmp_f7 * 3.0;
      }
      else {
        tmp_f7 = 3.0;
        tmp_f6 = -20.0;
      }
      tmp_f2 = *(float *)(g_unk_010afbcc + 0x24) * tmp_f6 + *param_1;
      *param_1 = tmp_f2;
      tmp_f1 = *(float *)(g_unk_010afbcc + 0x28) * tmp_f6 + param_1[1];
      param_1[1] = tmp_f1;
      tmp_f6 = tmp_f6 * *(float *)(g_unk_010afbcc + 0x2c) + param_1[2];
      param_1[2] = tmp_f6;
      *param_1 = *(float *)(g_unk_010afbcc + 0x30) * tmp_f7 + tmp_f2;
      param_1[1] = *(float *)(g_unk_010afbcc + 0x34) * tmp_f7 + tmp_f1;
      param_1[2] = tmp_f7 * *(float *)(g_unk_010afbcc + 0x38) + tmp_f6;
    }
  }
  tmp_f7 = g_unk_01090738;
  if ((g_unk_01090738 != 0.0) && (g_unk_010907a4 != 6)) {
    if (g_unk_010907a0 - 6 < 0x20) {
      tmp_u4 = 1 << ((byte)(g_unk_010907a0 - 6) & 0x1f);
      if ((tmp_u4 & 0xc1030001) == 0) {
        if ((tmp_u4 & 0x40000) == 0) goto LAB_000cf8b0;
        tmp_f6 = 6.0;
      }
      else {
        tmp_f6 = 4.0;
      }
    }
    else {
LAB_000cf8b0:
      tmp_f6 = 2.0;
    }
    if ((cgs[0x2038e69] & 1) == 0) {
      pfVar8 = &local_34;
      param_2[2] = param_2[2] - g_unk_01090738 / tmp_f6;
      AngleVectors(param_2,0,pfVar8,local_28,tmp_f7,pfVar8);
      *param_1 = local_34 * param_2[2] + *param_1;
      param_1[1] = local_30 * param_2[2] + param_1[1];
      param_1[2] = local_2c * param_2[2] + param_1[2];
      *param_2 = ABS(tmp_f7) * 0.5 + *param_2;
      AngleVectors(&g_unk_01091a54,0,pfVar8,0);
      tmp_f7 = -tmp_f7 * 0.25;
    }
    else {
      AngleVectors(&g_unk_01091a54,0,&local_34,0);
      tmp_f7 = tmp_f7 * 0.125;
    }
    *param_1 = local_34 * tmp_f7 + *param_1;
    param_1[1] = local_30 * tmp_f7 + param_1[1];
    param_1[2] = tmp_f7 * local_2c + param_1[2];
  }
  tmp_f7 = g_unk_010aad78;
  if (((byte)g_unk_010aad6c & 1) != 0) {
    tmp_f7 = -g_unk_010aad78;
  }
  tmp_f6 = g_unk_010aad68 * tmp_f7 * 0.005 + param_2[2];
  param_2[2] = tmp_f6;
  tmp_f7 = tmp_f7 * g_unk_010aad68 * 0.01 + param_2[1];
  param_2[1] = tmp_f7;
  tmp_f1 = g_unk_010aad78 * g_unk_010aad68 * 0.005 + *param_2;
  *param_2 = tmp_f1;
  tmp_i3 = g_unk_010906e0 - g_unk_01091810;
  if (tmp_i3 < 0x96) {
    tmp_f7 = ((float)tmp_i3 * g_unk_0109180c * 0.25) / 150.0;
  }
  else {
    if (0x1c1 < tmp_i3) goto LAB_000cf7a4;
    tmp_f7 = ((float)(0x1c2 - tmp_i3) * g_unk_0109180c * 0.25) / 300.0;
  }
  param_1[2] = tmp_f7 + param_1[2];
  tmp_f6 = param_2[2];
  tmp_f7 = param_2[1];
  tmp_f1 = *param_2;
LAB_000cf7a4:
  if (((g_unk_01090765 & 0x80) == 0) && ((g_unk_010907a0 & 0xfffffffb) != 0x2a)) {
    tmp_d5 = sin((double)g_unk_010906e0 * 0.001);
    tmp_f2 = (float)tmp_d5 * 80.0 * 0.01;
    tmp_f6 = tmp_f6 + tmp_f2;
    param_2[2] = tmp_f6;
    tmp_f7 = tmp_f7 + tmp_f2;
    param_2[1] = tmp_f7;
    tmp_f1 = tmp_f1 + tmp_f2;
    *param_2 = tmp_f1;
  }
  *param_2 = tmp_f1 - g_unk_010aaeb8;
  param_2[1] = tmp_f7 - g_unk_010aaebc;
  param_2[2] = tmp_f6 - g_unk_010aaec0;
  return;
}

void CG_RocketTrail(int param_1)
{
  int tmp_i1;
  float tmp_f2;
  float tmp_f3;
  uint tmp_u4;
  uint tmp_u5;
  int tmp_i6;
  int tmp_i7;
  int tmp_i8;
  int tmp_i9;
  uint32_t tmp_u10;
  int local_60;
  uint8_t local_4c [12];
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0xcfb59;
  if (GHIDRA_FIELD(cg_trailparticles, 12, 4) != 0) {
    if (*(int *)(param_1 + 4) == 0x14) {
      local_60 = 0x1e;
    }
    else {
      local_60 = 10;
      if (*(int *)(param_1 + 4) == 0x15) {
        local_60 = 0x32;
      }
    }
    tmp_i6 = *(int *)(param_1 + 0x25c);
    tmp_i1 = param_1 + 0xc;
    BG_EvaluateTrajectory(tmp_i1,g_unk_010906e0,local_4c,0,*(uint32_t *)(param_1 + 0x110));
    tmp_u4 = CG_PointContents(local_4c,0xffffffff);
    if ((*(int *)(param_1 + 4) == 0x18) || (*(int *)(param_1 + 0xc) != 0)) {
      BG_EvaluateTrajectory
                (tmp_i1,*(uint32_t *)(param_1 + 0x25c),&local_40,0,*(uint32_t *)(param_1 + 0x110)
                );
      tmp_u5 = CG_PointContents(&local_40,0xffffffff);
      tmp_i7 = g_unk_010906e0;
      *(int *)(param_1 + 0x25c) = g_unk_010906e0;
      if ((tmp_u4 & 0x38) == 0) {
        tmp_i6 = ((tmp_i6 + local_60) / local_60) * local_60;
        if (tmp_i6 - tmp_i7 == 0 || tmp_i6 < tmp_i7) {
          do {
            BG_EvaluateTrajectory(tmp_i1,tmp_i6,&local_40,0,*(uint32_t *)(param_1 + 0x110));
            tmp_u4 = rand();
            tmp_i7 = *(int *)(param_1 + 4);
            tmp_f2 = (float)(tmp_u4 & 0x7fff) / 32767.0;
            if ((tmp_i7 == 0x14) || (tmp_i7 == 0x15)) {
              tmp_i7 = rand();
              if (0x32 < tmp_i7 % 100) {
                CG_ParticleExplosionTrail
                          ("twiltb2",&local_40,&vec3_origin,(int)ROUND(tmp_f2 * 400.0) + 100,5,
                           (int)ROUND(tmp_f2 * 10.0) + 7,0);
              }
              goto LAB_000cfcb0;
            }
            if (tmp_i7 == 0x18) {
              local_40 = *(float *)(param_1 + 0x794);
              local_3c = *(float *)(param_1 + 0x798);
              local_38 = *(float *)(param_1 + 0x79c);
              CG_ParticleExplosionTrail
                        ("twiltb2",&local_40,&vec3_origin,(int)ROUND(tmp_f2 * 100.0) + 100,5,
                         (int)ROUND(tmp_f2 * 10.0) + 5,0);
              tmp_i7 = (int)ROUND(tmp_f2 * 30.0) + 0x18;
              tmp_u10 = 0xc;
              tmp_i8 = (int)ROUND(tmp_f2 * 750.0) + 400;
LAB_000cfd0b:
              CG_ParticleExplosionTrail
                        ("blacksmokeanim",&local_40,&vec3_origin,tmp_i8,tmp_u10,tmp_i7,0);
            }
            else {
              if (1 < tmp_i7 - 0x16U) {
LAB_000cfcb0:
                tmp_u10 = 5;
                tmp_i7 = (int)ROUND(tmp_f2 * 30.0) + 0xc;
                tmp_i8 = (int)ROUND(tmp_f2 * 1500.0) + 800;
                goto LAB_000cfd0b;
              }
              if (*(int *)(param_1 + 0xf4) != 0) {
                local_28 = *(uint32_t *)(param_1 + 0x3c);
                local_24 = *(uint32_t *)(param_1 + 0x40);
                local_20 = (float)(g_unk_010906e0 % 0x168) + *(float *)(param_1 + 0x44);
                AngleVectors(&local_28,0,&local_34,0);
                tmp_f3 = (float)*(int *)(param_1 + 0xf4);
                local_40 = local_34 * tmp_f3 + local_40;
                local_3c = local_30 * tmp_f3 + local_3c;
                local_38 = tmp_f3 * local_2c + local_38;
              }
              tmp_i7 = (int)ROUND(*(float *)(param_1 + 0x74));
              tmp_i8 = (int)ROUND(*(float *)(param_1 + 0x78));
              if (tmp_i7 == 0) {
                tmp_i7 = 100;
              }
              if (tmp_i8 == 0) {
                tmp_i8 = 5;
              }
              tmp_i9 = 7;
              if ((int)ROUND(*(float *)(param_1 + 0x7c)) != 0) {
                tmp_i9 = (int)ROUND(*(float *)(param_1 + 0x7c));
              }
              CG_ParticleExplosionTrail
                        ("twiltb2",&local_40,&vec3_origin,tmp_i7 + (int)ROUND(tmp_f2 * 400.0),tmp_i8,
                         (int)ROUND(tmp_f2 * 10.0) + tmp_i9,0);
              if ((*(int *)(param_1 + 4) == 0x17) && (tmp_i7 = rand(), 0x32 < tmp_i7 % 100))
              goto LAB_000cfcb0;
            }
            tmp_i6 = tmp_i6 + local_60;
          } while (tmp_i6 <= *(int *)(param_1 + 0x25c));
        }
      }
      else if ((tmp_u4 & 0x20 & tmp_u5) != 0) {
        CG_BubbleTrail(&local_40,local_4c,0x40400000,0x41000000);
      }
    }
    else {
      *(int *)(param_1 + 0x25c) = g_unk_010906e0;
    }
  }
  return;
}

void CG_DynamiteTrail(int param_1)
{
  float tmp_f1;
  double tmp_d2;
  uint8_t local_28 [24];
  
  BG_EvaluateTrajectory(param_1 + 0xc,g_unk_010906e0,local_28,0,*(uint32_t *)(param_1 + 0x110));
  if (*(int *)(param_1 + 0x108) < 4) {
    tmp_f1 = (float)(g_unk_010906e0 - *(int *)(param_1 + 0x10c));
    tmp_d2 = sin((double)(((tmp_f1 * 0.004) / (float)*(int *)(param_1 + 0x58)) * tmp_f1));
    trap_R_AddLightToScene(local_28,0x43a00000,ABS((float)tmp_d2),0x3f800000,0,0,0,0x80000000);
  }
  else {
    trap_R_AddLightToScene
              (local_28,0x43a00000,1.0 - (float)(g_unk_010906e0 - *(int *)(param_1 + 0x25c)) / 15500.0
               ,0x3f800000,0x3f800000,0,0,0x80000000);
  }
  return;
}

void CG_GrenadeTrail(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  uint tmp_u3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint8_t local_34 [12];
  uint8_t local_28 [24];
  
  if (GHIDRA_FIELD(cg_trailparticles, 12, 4) != 0) {
    tmp_i5 = *(int *)(param_1 + 0x25c);
    tmp_i1 = param_1 + 0xc;
    BG_EvaluateTrajectory(tmp_i1,g_unk_010906e0,local_34,0,*(uint32_t *)(param_1 + 0x110));
    tmp_u2 = CG_PointContents(local_34,0xffffffff);
    if (*(int *)(param_1 + 0xc) == 0) {
      *(int *)(param_1 + 0x25c) = g_unk_010906e0;
    }
    else {
      BG_EvaluateTrajectory
                (tmp_i1,*(uint32_t *)(param_1 + 0x25c),local_28,0,*(uint32_t *)(param_1 + 0x110))
      ;
      tmp_u3 = CG_PointContents(local_28,0xffffffff);
      tmp_i6 = g_unk_010906e0;
      *(int *)(param_1 + 0x25c) = g_unk_010906e0;
      if ((tmp_u2 & 0x38) == 0) {
        tmp_i5 = ((tmp_i5 + 0xf) / 0xf) * 0xf;
        if (tmp_i5 <= tmp_i6) {
          do {
            tmp_i6 = tmp_i5 + 0xf;
            BG_EvaluateTrajectory(tmp_i1,tmp_i5,local_34,0,*(uint32_t *)(param_1 + 0x110));
            tmp_u4 = CG_AddSmokeJunc(*(uint32_t *)(param_1 + 0x7c4),param_1,GHIDRA_FIELD(cgs, 68844, 4),local_34,
                                    1000,0x3e99999a,0x40000000,0x41a00000);
            *(uint32_t *)(param_1 + 0x7c4) = tmp_u4;
            *(int *)(param_1 + 0x7cc) = g_unk_010906e0;
            tmp_i5 = tmp_i6;
          } while (tmp_i6 <= *(int *)(param_1 + 0x25c));
        }
      }
      else if ((tmp_u2 & 0x20 & tmp_u3) != 0) {
        CG_BubbleTrail(local_28,local_34,0x40000000,0x41000000);
      }
    }
  }
  return;
}

uint32_t CG_RW_ParseError(uint32_t param_1,char *param_2)
{
  uint32_t local_a0;
  uint8_t local_9c [140];
  
  vsnprintf(string_12140,0x1000,param_2,&stack0x0000000c);
  local_a0 = 0;
  local_9c[0] = 0;
  trap_PC_SourceFileAndLine(param_1,local_9c,&local_a0);
  Com_Printf("^1ERROR: %s, line %d: %s\n",local_9c,local_a0,string_12140);
  trap_PC_FreeSource(param_1);
  return 0;
}

void CG_PyroSmokeTrail(uint32_t *param_1)
{
  uint32_t *tmp_pu1;
  float tmp_f2;
  uint32_t tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  double tmp_d7;
  float tmp_f8;
  float tmp_f9;
  float tmp_f10;
  int local_90;
  int local_70;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  
  tmp_i6 = param_1[0x3a];
  if ((tmp_i6 == 0x33) || (tmp_i6 == 0x19)) {
    if ((int)param_1[0x42] < 8) {
      param_1[0x98] = 0;
      return;
    }
    tmp_i5 = param_1[0x98];
    if (((int)param_1[0x42] < 0xc) && (tmp_i5 == 0)) {
      param_1[0x97] = g_unk_010906e0;
      tmp_i5 = g_unk_010906e0;
      param_1[0x98] = g_unk_010906e0;
      if (tmp_i6 != 0x33) {
        trap_S_StartSound(0,*param_1,2,GHIDRA_FIELD(cgs, 33787824, 4));
        tmp_i5 = param_1[0x98];
      }
    }
    if (1000 < g_unk_010906e0 - tmp_i5) {
      return;
    }
    local_70 = ~-(uint)(param_1[0x24] == 0) + 2;
  }
  else {
    local_70 = param_1[0x42];
  }
  tmp_i6 = ((param_1[0x97] + 0x1e) / 0x1e) * 0x1e;
  tmp_pu1 = param_1 + 3;
  BG_EvaluateTrajectory(tmp_pu1,g_unk_010906e0,&local_58,0,param_1[0x44]);
  CG_PointContents(&local_58,0xffffffff);
  BG_EvaluateTrajectory(tmp_pu1,param_1[0x97],&local_4c,0,param_1[0x44]);
  CG_PointContents(&local_4c,0xffffffff);
  tmp_i5 = g_unk_010906e0;
  param_1[0x97] = g_unk_010906e0;
  if (tmp_i6 <= tmp_i5) {
    do {
      BG_EvaluateTrajectory(tmp_pu1,tmp_i6,&local_4c,0,param_1[0x44]);
      rand();
      if (param_1[0x3d] != 0) {
        local_28 = param_1[0xf];
        local_24 = param_1[0x10];
        local_20 = (float)(g_unk_010906e0 % 0x168) + (float)param_1[0x11];
        AngleVectors(&local_28,0,&local_34,0);
        tmp_f2 = (float)(int)param_1[0x3d];
        local_4c = local_34 * tmp_f2 + local_4c;
        local_48 = local_30 * tmp_f2 + local_48;
        local_44 = tmp_f2 * local_2c + local_44;
      }
      tmp_u4 = rand();
      tmp_f2 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
      local_40 = (tmp_f2 + tmp_f2) * 5.0;
      tmp_u4 = rand();
      tmp_f2 = (float)(tmp_u4 & 0x7fff) / 32767.0 - 0.5;
      local_3c = (tmp_f2 + tmp_f2) * 5.0;
      local_38 = 0.0;
      local_58 = local_4c + local_40;
      local_54 = local_3c + local_48;
      local_50 = local_44 + 0.0;
      tmp_u4 = rand();
      tmp_f2 = (float)(tmp_u4 & 0x7fff) / 32767.0;
      tmp_u4 = rand();
      local_40 = ((float)(tmp_u4 & 0x7fff) / 32767.0) * 0.25;
      tmp_d7 = sin((double)g_unk_010906e0 * 1e-05);
      local_3c = (float)tmp_d7;
      tmp_u4 = rand();
      local_38 = (float)(tmp_u4 & 0x7fff) / 32767.0;
      VectorNormalize(&local_40);
      tmp_u3 = GHIDRA_FIELD(cgs, 68088, 4);
      if ((param_1[0x3a] == 0x33) || (param_1[0x3a] == 0x19)) {
        tmp_f10 = 45.0;
      }
      else {
        tmp_f10 = 65.0;
      }
      local_40 = local_40 * tmp_f10;
      local_3c = local_3c * tmp_f10;
      local_38 = tmp_f10 * local_38;
      if (local_70 == 2) {
        tmp_i5 = rand();
        tmp_f10 = 1.0;
        tmp_f8 = tmp_f2 * 0.5 + 0.5;
        tmp_f9 = tmp_f8;
      }
      else {
        tmp_i5 = rand();
        tmp_f8 = 1.0;
        tmp_f10 = tmp_f2 * 0.5 + 0.5;
        tmp_f9 = tmp_f10;
      }
      local_90 = tmp_i5 % 0xaf0 + 0x12c0;
      tmp_i5 = tmp_i6 + 0x1e;
      CG_SmokePuff(&local_58,&local_40,tmp_f2 * 110.0 + 25.0,tmp_f8,tmp_f9,tmp_f10,0x3f000000,
                   (float)local_90,tmp_i6,0,0,tmp_u3);
      tmp_i6 = tmp_i5;
    } while (tmp_i5 <= (int)param_1[0x97]);
  }
  return;
}

void CG_MachineGunEjectBrassNew(int param_1)
{
  uint32_t tmp_u1;
  uint32_t tmp_u2;
  uint32_t tmp_u3;
  float tmp_f4;
  int tmp_i5;
  float tmp_f6;
  float tmp_f7;
  float tmp_f8;
  int tmp_i9;
  uint tmp_u10;
  int tmp_i11;
  int tmp_i12;
  uint local_64;
  uint32_t local_4c;
  uint32_t local_48;
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
  
  uStack_14 = 0xd30a9;
  tmp_i5 = *(int *)(param_1 + 0xe8);
  if (0 < (int)GHIDRA_FIELD(cg_brassTime, 12, 4)) {
    tmp_i9 = CG_AllocLocalEntity();
    tmp_u10 = rand();
    tmp_f6 = (float)(tmp_u10 & 0x7fff) / 32767.0 - 0.5;
    tmp_f6 = (tmp_f6 + tmp_f6) * 25.0 - 50.0;
    tmp_u10 = rand();
    tmp_f7 = (float)(tmp_u10 & 0x7fff) / 32767.0 - 0.5;
    tmp_f7 = (tmp_f7 + tmp_f7) * 40.0 - 100.0;
    local_64 = rand();
    *(uint32_t *)(tmp_i9 + 8) = 3;
    tmp_i11 = g_unk_010906e0;
    tmp_u1 = GHIDRA_FIELD(cg_brassTime, 12, 4);
    local_64 = local_64 & 0x7fff;
    *(int *)(tmp_i9 + 0x10) = g_unk_010906e0;
    tmp_f8 = ((float)local_64 / 32767.0) * 50.0 + 200.0;
    tmp_u10 = rand();
    tmp_i12 = tmp_u1;
    if ((int)tmp_u1 < 0) {
      tmp_i12 = tmp_u1 + 3;
    }
    *(int *)(tmp_i9 + 0x14) =
         (int)ROUND(((float)(tmp_u10 & 0x7fff) / 32767.0) * (float)(tmp_i12 >> 2) +
                    (float)(tmp_i11 + tmp_u1));
    *(uint32_t *)(tmp_i9 + 0x20) = 6;
    tmp_i11 = g_unk_010906e0;
    tmp_u10 = rand();
    *(uint *)(tmp_i9 + 0x24) = tmp_i11 - (tmp_u10 & 0xf);
    AnglesToAxis(param_1 + 0x7a0,&local_40);
    tmp_u1 = *(uint32_t *)(param_1 + 0x758);
    *(uint32_t *)(tmp_i9 + 0x100) = tmp_u1;
    tmp_u2 = *(uint32_t *)(param_1 + 0x75c);
    *(uint32_t *)(tmp_i9 + 0x104) = tmp_u2;
    tmp_u3 = *(uint32_t *)(param_1 + 0x760);
    *(uint32_t *)(tmp_i9 + 0x108) = tmp_u3;
    *(uint32_t *)(tmp_i9 + 0x2c) = tmp_u1;
    *(uint32_t *)(tmp_i9 + 0x30) = tmp_u2;
    *(uint32_t *)(tmp_i9 + 0x34) = tmp_u3;
    tmp_u10 = CG_PointContents(tmp_i9 + 0x100,0xffffffff);
    if ((tmp_u10 & 0x30) == 0) {
      tmp_f4 = 1.0;
    }
    else {
      tmp_f4 = 0.1;
    }
    *(float *)(tmp_i9 + 0x38) = (tmp_f8 * local_28 + tmp_f6 * local_40 + local_34 * tmp_f7) * tmp_f4;
    *(float *)(tmp_i9 + 0x3c) = (local_24 * tmp_f8 + local_30 * tmp_f7 + local_3c * tmp_f6) * tmp_f4;
    *(float *)(tmp_i9 + 0x40) = (local_20 * tmp_f8 + local_2c * tmp_f7 + local_38 * tmp_f6) * tmp_f4;
    AxisCopy(axisDefault,tmp_i9 + 0xb4);
    tmp_i11 = *(int *)(cg_weapons + tmp_i5 * 0x17ac + 0x178c);
    if (((*(int *)(cg_weapons + tmp_i5 * 0x17ac + 0x178c) == 0) &&
        (tmp_u10 = *(int *)(param_1 + 0xe8) - 0x16, tmp_i11 = GHIDRA_FIELD(cgs, 67948, 4), tmp_u10 < 0x19)) &&
       ((1 << ((byte)tmp_u10 & 0x1f) & 0x10e0387U) != 0)) {
      *(uint32_t *)(tmp_i9 + 0xa0) = GHIDRA_FIELD(cgs, 67940, 4);
    }
    else {
      *(int *)(tmp_i9 + 0xa0) = tmp_i11;
    }
    *(float *)(tmp_i9 + 0x68) = tmp_f4 * 0.4;
    *(uint32_t *)(tmp_i9 + 0x44) = 2;
    *(int *)(tmp_i9 + 0x48) = g_unk_010906e0;
    tmp_u10 = rand();
    *(float *)(tmp_i9 + 0x50) = (float)((tmp_u10 & 0x1f) + 0x3c);
    tmp_u10 = rand();
    *(float *)(tmp_i9 + 0x54) = (float)(tmp_u10 & 0xff);
    tmp_u10 = rand();
    *(uint32_t *)(tmp_i9 + 0xc) = 2;
    *(uint32_t *)(tmp_i9 + 0x5c) = 0x40000000;
    *(uint32_t *)(tmp_i9 + 0x60) = 0x3f800000;
    *(uint32_t *)(tmp_i9 + 100) = 0;
    *(float *)(tmp_i9 + 0x58) = (float)(tmp_u10 & 0x1f);
    local_4c = *(uint32_t *)(param_1 + 0x794);
    local_48 = *(uint32_t *)(param_1 + 0x798);
    local_44 = *(float *)(param_1 + 0x79c) - 24.0;
    tmp_u10 = CG_PointContents(&local_4c,0);
    *(uint *)(tmp_i9 + 0x94) = -(uint)((tmp_u10 & 0x38) == 0) & 4;
    *(uint32_t *)(tmp_i9 + 0x90) = 0;
  }
  return;
}

void CG_MachineGunEjectBrass(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  float tmp_f5;
  uint32_t tmp_u6;
  int tmp_i7;
  int tmp_i8;
  uint tmp_u9;
  int tmp_i10;
  float local_70;
  float local_64;
  uint32_t local_4c;
  uint32_t local_48;
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
  
  uStack_14 = 0xd3439;
  if (0 < (int)GHIDRA_FIELD(cg_brassTime, 12, 4)) {
    if ((*(int *)(g_unk_01047b00 + 0x16c) == 0) && ((*(byte *)(param_1 + 8) & 0x20) == 0)) {
      CG_MachineGunEjectBrassNew(param_1);
      return;
    }
    tmp_i8 = CG_AllocLocalEntity();
    *(uint32_t *)(tmp_i8 + 8) = 3;
    tmp_i7 = g_unk_010906e0;
    tmp_u6 = GHIDRA_FIELD(cg_brassTime, 12, 4);
    *(int *)(tmp_i8 + 0x10) = g_unk_010906e0;
    tmp_u9 = rand();
    tmp_i10 = tmp_u6;
    if ((int)tmp_u6 < 0) {
      tmp_i10 = tmp_u6 + 3;
    }
    *(int *)(tmp_i8 + 0x14) =
         (int)ROUND(((float)(tmp_u9 & 0x7fff) / 32767.0) * (float)(tmp_i10 >> 2) +
                    (float)(tmp_i7 + tmp_u6));
    *(uint32_t *)(tmp_i8 + 0x20) = 6;
    tmp_i7 = g_unk_010906e0;
    tmp_u9 = rand();
    *(uint *)(tmp_i8 + 0x24) = tmp_i7 - (tmp_u9 & 0xf);
    AnglesToAxis(param_1 + 0x7a0,&local_40);
    if ((*(byte *)(param_1 + 8) & 0x20) == 0) {
      *(uint32_t *)(tmp_i8 + 0xa0) = GHIDRA_FIELD(cgs, 67948, 4);
      switch(*(uint32_t *)(param_1 + 0xe8)) {
      case 2:
      case 7:
      case 0xe:
      case 0x26:
        tmp_f1 = 36.0;
        tmp_f2 = 24.0;
        break;
      case 0x16:
      case 0x17:
      case 0x1e:
        *(uint32_t *)(tmp_i8 + 0xa0) = GHIDRA_FIELD(cgs, 67940, 4);
      default:
        tmp_f1 = 24.0;
        tmp_f2 = 16.0;
        break;
      case 0x1d:
      case 0x2e:
        tmp_f1 = 24.0;
        tmp_f2 = 12.0;
        *(uint32_t *)(tmp_i8 + 0xa0) = GHIDRA_FIELD(cgs, 67940, 4);
      }
      tmp_u9 = rand();
      tmp_f3 = (float)(tmp_u9 & 0x7fff) / 32767.0 - 0.5;
      local_70 = (tmp_f3 + tmp_f3) * 25.0 - 50.0;
      tmp_u9 = rand();
      tmp_f3 = (float)(tmp_u9 & 0x7fff) / 32767.0 - 0.5;
      local_64 = (tmp_f3 + tmp_f3) * 40.0 - 100.0;
      tmp_u9 = rand();
      tmp_f3 = ((float)(tmp_u9 & 0x7fff) / 32767.0) * 50.0 + 200.0;
      tmp_u9 = rand();
      *(float *)(tmp_i8 + 0x50) = (float)((tmp_u9 & 0xf) + 0x52);
      tmp_u9 = rand();
      *(float *)(tmp_i8 + 0x54) = (float)(tmp_u9 & 0xff);
      tmp_u9 = rand();
      *(uint32_t *)(tmp_i8 + 0x5c) = 0x40000000;
      *(uint32_t *)(tmp_i8 + 0x60) = 0x3f800000;
      *(uint32_t *)(tmp_i8 + 100) = 0;
      *(float *)(tmp_i8 + 0x58) = (float)(tmp_u9 & 0x1f);
    }
    else {
      tmp_u9 = rand();
      tmp_f1 = (float)(tmp_u9 & 0x7fff) / 32767.0 - 0.5;
      local_70 = (tmp_f1 + tmp_f1) * 40.0 - 20.0;
      tmp_u9 = rand();
      tmp_f1 = (float)(tmp_u9 & 0x7fff) / 32767.0 - 0.5;
      local_64 = (tmp_f1 + tmp_f1) * 40.0 - 150.0;
      tmp_u9 = rand();
      tmp_u6 = GHIDRA_FIELD(cgs, 67940, 4);
      tmp_f1 = (float)(tmp_u9 & 0x7fff) / 32767.0 - 0.5;
      tmp_f3 = (tmp_f1 + tmp_f1) * 50.0 + 100.0;
      *(uint32_t *)(tmp_i8 + 0x50) = 0x42b40000;
      *(uint32_t *)(tmp_i8 + 0xa0) = tmp_u6;
      tmp_u9 = rand();
      *(float *)(tmp_i8 + 0x54) = (float)(tmp_u9 & 0xff);
      tmp_u9 = rand();
      *(uint32_t *)(tmp_i8 + 0x5c) = 0x40000000;
      *(uint32_t *)(tmp_i8 + 0x60) = 0x3f800000;
      *(uint32_t *)(tmp_i8 + 100) = 0;
      *(float *)(tmp_i8 + 0x58) = (float)(tmp_u9 & 0x1f);
      tmp_f1 = 28.0;
      tmp_f2 = 25.0;
    }
    tmp_f4 = tmp_f1 * local_28 + local_34 * -4.0 + tmp_f2 * local_40 + *(float *)(param_1 + 0x794);
    *(float *)(tmp_i8 + 0x100) = tmp_f4;
    tmp_f5 = local_24 * tmp_f1 + local_30 * -4.0 + local_3c * tmp_f2 + *(float *)(param_1 + 0x798);
    *(float *)(tmp_i8 + 0x104) = tmp_f5;
    tmp_f1 = local_20 * tmp_f1 + local_2c * -4.0 + local_38 * tmp_f2 + *(float *)(param_1 + 0x79c);
    *(float *)(tmp_i8 + 0x108) = tmp_f1;
    *(float *)(tmp_i8 + 0x2c) = tmp_f4;
    *(float *)(tmp_i8 + 0x30) = tmp_f5;
    *(float *)(tmp_i8 + 0x34) = tmp_f1;
    tmp_u9 = CG_PointContents(tmp_i8 + 0x100,0xffffffff);
    if ((tmp_u9 & 0x30) == 0) {
      tmp_f1 = 1.0;
    }
    else {
      tmp_f1 = 0.1;
    }
    *(float *)(tmp_i8 + 0x38) =
         (local_28 * tmp_f3 + local_70 * local_40 + local_34 * local_64) * tmp_f1;
    *(float *)(tmp_i8 + 0x3c) =
         (local_24 * tmp_f3 + local_30 * local_64 + local_3c * local_70) * tmp_f1;
    *(float *)(tmp_i8 + 0x40) =
         (local_20 * tmp_f3 + local_2c * local_64 + local_38 * local_70) * tmp_f1;
    AxisCopy(axisDefault,tmp_i8 + 0xb4);
    *(float *)(tmp_i8 + 0x68) = tmp_f1 * 0.4;
    *(uint32_t *)(tmp_i8 + 0x44) = 2;
    tmp_i7 = g_unk_010906e0;
    *(uint32_t *)(tmp_i8 + 0xc) = 2;
    *(int *)(tmp_i8 + 0x48) = tmp_i7;
    local_4c = *(uint32_t *)(param_1 + 0x794);
    local_48 = *(uint32_t *)(param_1 + 0x798);
    local_44 = *(float *)(param_1 + 0x79c) - 24.0;
    tmp_u9 = CG_PointContents(&local_4c,0);
    *(uint *)(tmp_i8 + 0x94) = -(uint)((tmp_u9 & 0x38) == 0) & 4;
    *(uint32_t *)(tmp_i8 + 0x90) = 0;
  }
  return;
}

void CG_GetWindVector(float *param_1)
{
  uint tmp_u1;
  double tmp_d2;
  
  tmp_u1 = rand();
  *param_1 = ((float)(tmp_u1 & 0x7fff) / 32767.0) * 0.25;
  tmp_d2 = sin((double)g_unk_010906e0 * 1e-05);
  param_1[1] = (float)tmp_d2;
  tmp_u1 = rand();
  param_1[2] = (float)(tmp_u1 & 0x7fff) / 32767.0;
  VectorNormalize(param_1);
  return;
}

void CG_RailTrail2(uint32_t *param_1,uint32_t *param_2,uint32_t *param_3,int param_4,
                  uint32_t param_5)

{
  uint32_t tmp_u1;
  float tmp_f2;
  int tmp_i3;
  int tmp_i4;
  
  if (param_4 == 0) {
    tmp_i4 = CG_AllocLocalEntity();
  }
  else {
    tmp_i4 = CG_FindLocalEntity(param_4,param_5);
    if (tmp_i4 == 0) {
      tmp_i4 = CG_AllocLocalEntity();
    }
    *(int *)(tmp_i4 + 0x1b4) = param_4;
    *(uint32_t *)(tmp_i4 + 0x1b8) = param_5;
  }
  *(uint32_t *)(tmp_i4 + 8) = 6;
  tmp_i3 = g_unk_010906e0;
  *(int *)(tmp_i4 + 0x10) = g_unk_010906e0;
  tmp_f2 = (float)g_unk_010906e0 + (float)GHIDRA_FIELD(cg_railTrailTime, 8, 4);
  *(int *)(tmp_i4 + 0x14) = (int)ROUND(tmp_f2);
  *(float *)(tmp_i4 + 0x1c) = 1.0 / (float)((int)ROUND(tmp_f2) - tmp_i3);
  tmp_f2 = (float)g_unk_010906e0;
  *(uint32_t *)(tmp_i4 + 0x98) = 5;
  *(float *)(tmp_i4 + 0x158) = tmp_f2 / 1000.0;
  *(uint32_t *)(tmp_i4 + 0x148) = GHIDRA_FIELD(cgs, 67956, 4);
  *(uint32_t *)(tmp_i4 + 0x100) = *param_2;
  *(uint32_t *)(tmp_i4 + 0x104) = param_2[1];
  *(uint32_t *)(tmp_i4 + 0x108) = param_2[2];
  *(uint32_t *)(tmp_i4 + 0x11c) = *param_3;
  *(uint32_t *)(tmp_i4 + 0x120) = param_3[1];
  *(uint32_t *)(tmp_i4 + 0x124) = param_3[2];
  *(uint32_t *)(tmp_i4 + 0x6c) = *param_1;
  *(uint32_t *)(tmp_i4 + 0x70) = param_1[1];
  tmp_u1 = param_1[2];
  *(uint32_t *)(tmp_i4 + 0x78) = 0x3f800000;
  *(uint32_t *)(tmp_i4 + 0x74) = tmp_u1;
  AxisClear(tmp_i4 + 0xb4);
  return;
}

void CG_RegisterItemVisuals(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  
  if ((&cg_items)[param_1 * 8] == 0) {
    (&cg_items)[param_1 * 8] = 0;
    if (*(int *)(bg_itemlist + param_1 * 0x38 + 0x24) != 1) {
      tmp_i2 = 0;
      do {
        tmp_i3 = tmp_i2 + 1;
        tmp_u1 = trap_R_RegisterModel(*(uint32_t *)(param_1 * 0x38 + 0x13ed08 + tmp_i2 * 4));
        (&g_unk_010202a4)[param_1 * 8 + tmp_i2] = tmp_u1;
        tmp_i2 = tmp_i3;
      } while (tmp_i3 != 3);
      if (*(int *)(bg_itemlist + param_1 * 0x38 + 0x14) != 0) {
        tmp_u1 = trap_R_RegisterShader(*(int *)(bg_itemlist + param_1 * 0x38 + 0x14));
        *(uint32_t *)(&g_unk_010202b0 + param_1 * 0x20) = tmp_u1;
      }
      (&cg_items)[param_1 * 8] = 1;
    }
  }
  return;
}

uint64_t CG_GetPartFramesFromWeap(int param_1,int param_2,int param_3,int param_4,int param_5)
{
  int tmp_i1;
  byte tmp_b2;
  uint32_t tmp_u3;
  uint tmp_u4;
  uint tmp_u5;
  int tmp_i6;
  uint32_t local_10;
  
  tmp_i1 = *(int *)(param_1 + 0x398);
  tmp_b2 = (byte)param_4;
  if ((param_4 == 0x10) || (tmp_u3 = 0, (*(int *)(tmp_i1 + 0x58) >> (tmp_b2 + 8 & 0x1f) & 1U) == 0)) {
    tmp_u4 = *(uint *)(param_1 + 0x390) & 0xfffffdff;
    if ((int)tmp_u4 < 1) {
      tmp_i6 = 0;
    }
    else {
      tmp_u5 = 1 << (tmp_b2 & 0x1f);
      tmp_i6 = 0;
      if ((*(uint *)(param_5 + 0x5c) & tmp_u5) != 0) {
        tmp_i6 = *(int *)(param_5 + 0x4c);
      }
      if (tmp_u4 != 1) {
        if ((*(uint *)(param_5 + 0xcc) & tmp_u5) != 0) {
          tmp_i6 = tmp_i6 + *(int *)(param_5 + 0xbc);
        }
        if (tmp_u4 != 2) {
          if ((*(uint *)(param_5 + 0x13c) & tmp_u5) != 0) {
            tmp_i6 = tmp_i6 + *(int *)(param_5 + 300);
          }
          if (tmp_u4 != 3) {
            if ((*(uint *)(param_5 + 0x1ac) & tmp_u5) != 0) {
              tmp_i6 = tmp_i6 + *(int *)(param_5 + 0x19c);
            }
            if (tmp_u4 != 4) {
              if ((*(uint *)(param_5 + 0x21c) & tmp_u5) != 0) {
                tmp_i6 = tmp_i6 + *(int *)(param_5 + 0x20c);
              }
              if (tmp_u4 != 5) {
                if ((*(uint *)(param_5 + 0x28c) & tmp_u5) != 0) {
                  tmp_i6 = tmp_i6 + *(int *)(param_5 + 0x27c);
                }
                if (tmp_u4 != 6) {
                  if ((*(uint *)(param_5 + 0x2fc) & tmp_u5) != 0) {
                    tmp_i6 = tmp_i6 + *(int *)(param_5 + 0x2ec);
                  }
                  if (tmp_u4 != 7) {
                    if ((*(uint *)(param_5 + 0x36c) & tmp_u5) != 0) {
                      tmp_i6 = tmp_i6 + *(int *)(param_5 + 0x35c);
                    }
                    if (tmp_u4 != 8) {
                      if ((*(uint *)(param_5 + 0x3dc) & tmp_u5) != 0) {
                        tmp_i6 = tmp_i6 + *(int *)(param_5 + 0x3cc);
                      }
                      if (tmp_u4 != 9) {
                        if ((*(uint *)(param_5 + 0x44c) & tmp_u5) != 0) {
                          tmp_i6 = tmp_i6 + *(int *)(param_5 + 0x43c);
                        }
                        if (tmp_u4 != 10) {
                          if ((*(uint *)(param_5 + 0x4bc) & tmp_u5) != 0) {
                            tmp_i6 = tmp_i6 + *(int *)(param_5 + 0x4ac);
                          }
                          if (tmp_u4 != 0xb) {
                            if ((*(uint *)(param_5 + 0x52c) & tmp_u5) != 0) {
                              tmp_i6 = tmp_i6 + *(int *)(param_5 + 0x51c);
                            }
                            if ((tmp_u4 != 0xc) && ((*(uint *)(param_5 + 0x59c) & tmp_u5) != 0)) {
                              tmp_i6 = tmp_i6 + *(int *)(param_5 + 0x58c);
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
    tmp_u3 = 1;
    if ((*(int *)(tmp_i1 + 0x58) >> (tmp_b2 & 0x1f) & 1U) != 0) {
      local_10 = *(uint32_t *)(param_3 + 0xa0);
      *(uint32_t *)(param_2 + 0xa0) = local_10;
      *(int *)(param_2 + 0x90) = (*(int *)(param_3 + 0x90) + tmp_i6) - *(int *)(tmp_i1 + 0x44);
      *(int *)(param_2 + 0x74) = (tmp_i6 + *(int *)(param_3 + 0x74)) - *(int *)(tmp_i1 + 0x44);
    }
  }
  return CONCAT44(local_10,tmp_u3);
}

void CG_ClearWeapLerpFrame(int param_1,uint32_t *param_2,uint param_3)
{
  uint32_t tmp_u1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  
  tmp_i3 = g_unk_010906e0;
  param_2[0xb] = param_3;
  param_3 = param_3 & 0xfffffdff;
  param_2[1] = tmp_i3;
  param_2[4] = tmp_i3;
  if (0xd < param_3 + 1) {
    CG_Error("Bad animation number (CG_SWLFA): %i",param_3);
    tmp_i3 = param_2[4];
  }
  tmp_pu2 = (uint32_t *)(param_1 + 4 + param_3 * 0x70);
  param_2[0xd] = tmp_pu2;
  param_2[0xe] = tmp_i3 + *(int *)(param_1 + 0x58 + param_3 * 0x70);
  if ((cg_debugAnim[0xc] & 2) != 0) {
    CG_Printf("Weap Anim: %d\n",param_3);
    tmp_pu2 = (uint32_t *)param_2[0xd];
  }
  tmp_u1 = tmp_pu2[0x11];
  param_2[3] = tmp_u1;
  *param_2 = tmp_u1;
  tmp_u1 = *tmp_pu2;
  param_2[5] = tmp_u1;
  param_2[2] = tmp_u1;
  return;
}

void CG_SetSniperZoom(int param_1,int param_2)
{
  if (param_1 == param_2) {
    return;
  }
  if ((g_unk_01090766 & 4) == 0) {
    g_unk_01091a74 = 0.0;
  }
  if (param_2 != 0x28) {
    if (param_2 == 0x29) {
      g_unk_01091a68 = 1;
      goto LAB_000d517a;
    }
    if (param_2 != 0x27) {
      g_unk_01091a68 = 0;
      return;
    }
  }
  g_unk_01091a68 = 900;
LAB_000d517a:
  g_unk_01091a74 = (float)GHIDRA_FIELD(cg_zoomDefaultSniper, 8, 4);
  if ((float)GHIDRA_FIELD(zoomTable, 16, 4) < (float)GHIDRA_FIELD(cg_zoomDefaultSniper, 8, 4)) {
    g_unk_01091a74 = (float)GHIDRA_FIELD(zoomTable, 16, 4);
  }
  if (g_unk_01091a74 < (float)GHIDRA_FIELD(zoomTable, 20, 4)) {
    g_unk_01091a74 = (float)GHIDRA_FIELD(zoomTable, 20, 4);
  }
  g_unk_01091a6c = g_unk_010906e0;
  return;
}

void CG_FinishWeaponChange(int param_1,int param_2)
{
  int *tmp_pi1;
  uint32_t tmp_u2;
  uint tmp_u3;
  
  if (g_unk_010b3b24 != 0) {
    return;
  }
  g_unk_010b4564 = 0xfffffffe;
  switch(param_2) {
  default:
    tmp_u3 = param_2 - 1;
    break;
  case 2:
    if (((byte)g_unk_010b1674 & 1) == 0) {
      tmp_u3 = 1;
      break;
    }
    if (param_1 != 0xe) {
      tmp_u3 = 0xd;
      g_unk_01091814 = 0xe;
      param_2 = 0xe;
      break;
    }
    tmp_u3 = 1;
LAB_000d5a00:
    g_unk_010aac34 = g_unk_010906e0;
    if (g_unk_010ab2f0 == 0) goto LAB_000d5553;
    tmp_u2 = va("%d",g_unk_010ab2f0 + -1);
    trap_Cvar_Set("cg_drawCrossHair",tmp_u2);
    g_unk_010ab2f0 = 0;
    goto LAB_000d555c;
  case 7:
    if (((byte)g_unk_010b1674 & 1) == 0) {
      tmp_u3 = 6;
    }
    else {
      if (param_1 == 0x26) {
        tmp_u3 = 6;
        goto LAB_000d5a00;
      }
      tmp_u3 = 0x25;
      g_unk_01091814 = 0x26;
      param_2 = 0x26;
    }
    break;
  case 0xe:
    if (((byte)g_unk_010b1674 & 1) == 0) {
      if (param_1 == 2) {
        tmp_u3 = 0xd;
        goto LAB_000d5a00;
      }
      tmp_u3 = 1;
      g_unk_01091814 = 2;
      param_2 = 2;
    }
    else {
      tmp_u3 = 0xd;
    }
    break;
  case 0x16:
    if (((byte)g_unk_010b1674 & 2) == 0) {
      tmp_u3 = 0x15;
    }
    else {
      if (param_1 == 0x24) {
        tmp_u3 = 0x15;
        goto LAB_000d5a00;
      }
      tmp_u3 = 0x23;
      g_unk_01091814 = 0x24;
      param_2 = 0x24;
    }
    break;
  case 0x17:
    if (((byte)g_unk_010b1674 & 2) == 0) {
      tmp_u3 = 0x16;
    }
    else {
      if (param_1 == 0x25) {
        tmp_u3 = 0x16;
        goto LAB_000d5a00;
      }
      tmp_u3 = 0x24;
      g_unk_01091814 = 0x25;
      param_2 = 0x25;
    }
    break;
  case 0x24:
    if (((byte)g_unk_010b1674 & 2) == 0) {
      if (param_1 == 0x16) {
        tmp_u3 = 0x23;
        goto LAB_000d5a00;
      }
      tmp_u3 = 0x15;
      g_unk_01091814 = 0x16;
      param_2 = 0x16;
    }
    else {
      tmp_u3 = 0x23;
    }
    break;
  case 0x25:
    if (((byte)g_unk_010b1674 & 2) == 0) {
      if (param_1 == 0x17) {
        tmp_u3 = 0x24;
        goto LAB_000d5a00;
      }
      param_2 = 0x17;
      g_unk_01091814 = 0x17;
      tmp_u3 = 0x16;
    }
    else {
      tmp_u3 = 0x24;
    }
    break;
  case 0x26:
    if (((byte)g_unk_010b1674 & 1) == 0) {
      if (param_1 == 7) {
        tmp_u3 = 0x25;
        goto LAB_000d5a00;
      }
      tmp_u3 = 6;
      g_unk_01091814 = 7;
      param_2 = 7;
    }
    else {
      tmp_u3 = 0x25;
    }
  }
  if ((param_1 == 0x13) && ((*(byte *)(g_unk_01047b00 + 0x96) & 4) != 0)) {
    trap_SendConsoleCommand("-zoom\n");
  }
  g_unk_010aac34 = g_unk_010906e0;
  if (g_unk_010ab2f0 != 0) {
    tmp_u2 = va("%d",g_unk_010ab2f0 + -1);
    trap_Cvar_Set("cg_drawCrossHair",tmp_u2);
    g_unk_010ab2f0 = 0;
  }
LAB_000d5553:
  if (tmp_u3 < 0x33) {
LAB_000d555c:
    bnk_12439 = 0;
    tmp_pi1 = &weapBanksMultiPlayer;
    do {
      cyc_12440 = 0;
      if (*tmp_pi1 != 0) {
        if (param_2 == *tmp_pi1) {
          cyc_12440 = 0;
LAB_000d5880:
          (&g_unk_010aad18)[bnk_12439] = param_2;
          goto LAB_000d5680;
        }
        if (tmp_pi1[1] == 0) {
          cyc_12440 = 1;
        }
        else {
          if (param_2 == tmp_pi1[1]) {
            cyc_12440 = 1;
            goto LAB_000d5880;
          }
          if (tmp_pi1[2] == 0) {
            cyc_12440 = 2;
          }
          else {
            if (param_2 == tmp_pi1[2]) {
              cyc_12440 = 2;
              goto LAB_000d5880;
            }
            if (tmp_pi1[3] == 0) {
              cyc_12440 = 3;
            }
            else {
              if (param_2 == tmp_pi1[3]) {
                cyc_12440 = 3;
                goto LAB_000d5880;
              }
              if (tmp_pi1[4] == 0) {
                cyc_12440 = 4;
              }
              else {
                if (param_2 == tmp_pi1[4]) {
                  cyc_12440 = 4;
                  goto LAB_000d5880;
                }
                if (tmp_pi1[5] == 0) {
                  cyc_12440 = 5;
                }
                else {
                  if (param_2 == tmp_pi1[5]) {
                    cyc_12440 = 5;
                    goto LAB_000d5880;
                  }
                  if (tmp_pi1[6] == 0) {
                    cyc_12440 = 6;
                  }
                  else {
                    if (param_2 == tmp_pi1[6]) {
                      cyc_12440 = 6;
                      goto LAB_000d5880;
                    }
                    if (tmp_pi1[7] == 0) {
                      cyc_12440 = 7;
                    }
                    else {
                      if (param_2 == tmp_pi1[7]) {
                        cyc_12440 = 7;
                        goto LAB_000d5880;
                      }
                      if (tmp_pi1[8] == 0) {
                        cyc_12440 = 8;
                      }
                      else {
                        if (param_2 == tmp_pi1[8]) {
                          cyc_12440 = 8;
                          goto LAB_000d5880;
                        }
                        if (tmp_pi1[9] == 0) {
                          cyc_12440 = 9;
                        }
                        else {
                          if (param_2 == tmp_pi1[9]) {
                            cyc_12440 = 9;
                            goto LAB_000d5880;
                          }
                          if (tmp_pi1[10] == 0) {
                            cyc_12440 = 10;
                          }
                          else {
                            if (param_2 == tmp_pi1[10]) {
                              cyc_12440 = 10;
                              goto LAB_000d5880;
                            }
                            if (tmp_pi1[0xb] == 0) {
                              cyc_12440 = 0xb;
                            }
                            else {
                              if (param_2 == tmp_pi1[0xb]) {
                                cyc_12440 = 0xb;
                                goto LAB_000d5880;
                              }
                              cyc_12440 = 0xc;
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
      bnk_12439 = bnk_12439 + 1;
      tmp_pi1 = tmp_pi1 + 0xc;
    } while (bnk_12439 != 10);
    bnk_12439 = 10;
  }
LAB_000d5680:
  if (param_1 == param_2) {
    return;
  }
  if (((param_1 - 1U < 0x33) && (*(int *)(weapAlts + param_1 * 4) == param_2)) &&
     (*(int *)(weapAlts + param_1 * 4) != 0)) {
    switch(param_2) {
    default:
      goto _L955;
    case 2:
    case 7:
    case 0xe:
    case 0x1d:
    case 0x21:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x2a:
    case 0x2e:
_L1035:
      tmp_u2 = *(uint32_t *)(cg_weapons + param_2 * 0x17ac + 0x176c);
      break;
    case 0x16:
    case 0x17:
      tmp_u2 = GHIDRA_FIELD(cgs, 68952, 4);
      if (*(int *)(&g_unk_0109098c + param_1 * 4) != 0) goto _L1035;
    }
    trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),2,tmp_u2);
  }
_L955:
  if ((g_unk_01090766 & 4) == 0) {
    g_unk_01091a74 = 0.0;
  }
  g_unk_01091a68 = 0;
  if (param_2 == 0x28) {
LAB_000d5760:
    g_unk_01091a68 = 900;
  }
  else {
    if (param_2 != 0x29) {
      if (param_2 != 0x27) goto LAB_000d536b;
      goto LAB_000d5760;
    }
    g_unk_01091a68 = 1;
  }
  g_unk_01091a74 = (float)GHIDRA_FIELD(cg_zoomDefaultSniper, 8, 4);
  if ((float)GHIDRA_FIELD(zoomTable, 16, 4) < (float)GHIDRA_FIELD(cg_zoomDefaultSniper, 8, 4)) {
    g_unk_01091a74 = (float)GHIDRA_FIELD(zoomTable, 16, 4);
  }
  if (g_unk_01091a74 < (float)GHIDRA_FIELD(zoomTable, 20, 4)) {
    g_unk_01091a74 = (float)GHIDRA_FIELD(zoomTable, 20, 4);
  }
  g_unk_01091a6c = g_unk_010906e0;
LAB_000d536b:
  if (g_unk_010aacfc == param_1) {
    if (param_1 - 0x27U < 3) {
      g_unk_01091814 = param_2;
      return;
    }
  }
  else if (g_unk_010aacf8 != param_2) {
    g_unk_01091814 = param_2;
    return;
  }
  g_unk_010aacf8 = param_1;
  g_unk_01091814 = param_2;
  return;
}

void CG_AltWeapon_f(void)
{
  CG_Printf("weapAlt is obsolete, please use +attack2.\n");
  return;
}

void CG_NextWeap(int param_1)
{
  uint tmp_u1;
  uint *tmp_pu2;
  int *tmp_pi3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  int tmp_i7;
  uint tmp_u8;
  uint local_3c;
  uint local_38;
  int local_34;
  int local_30;
  uint local_2c;
  uint local_20;
  
  if ((g_unk_01091814 & 0xfffffffb) == 0x2a) {
    return;
  }
  switch(g_unk_01091814) {
  case 0xe:
    tmp_u8 = 0xffffffde;
    local_20 = 2;
    break;
  default:
    local_20 = g_unk_01091814;
    if (g_unk_01091814 - 1 < 0x33) {
      tmp_u8 = g_unk_01091814 - 0x24;
      break;
    }
    local_30 = 0;
    local_2c = 0;
    tmp_u6 = g_unk_01091814;
    goto joined_r0x000d5ff2;
  case 0x24:
    tmp_u8 = 0xfffffff2;
    local_20 = 0x16;
    break;
  case 0x25:
    tmp_u8 = 0xfffffff3;
    local_20 = 0x17;
    break;
  case 0x26:
    tmp_u8 = 0xffffffe3;
    local_20 = 7;
    break;
  case 0x2a:
    tmp_u8 = 0xfffffffd;
    local_20 = 0x21;
  }
  tmp_pu2 = &weapBanksMultiPlayer;
  local_30 = 0;
  do {
    cyc_12440 = 0;
    if (*tmp_pu2 != 0) {
      bnk_12439 = local_30;
      if (local_20 == *tmp_pu2) {
        cyc_12440 = 0;
        local_2c = 0;
        goto LAB_000d5c60;
      }
      if (tmp_pu2[1] == 0) {
        cyc_12440 = 1;
      }
      else {
        if (local_20 == tmp_pu2[1]) {
          local_2c = 1;
LAB_000d6c10:
          cyc_12440 = local_2c;
          goto LAB_000d5c60;
        }
        if (tmp_pu2[2] == 0) {
          cyc_12440 = 2;
        }
        else {
          if (local_20 == tmp_pu2[2]) {
            local_2c = 2;
            goto LAB_000d6c10;
          }
          if (tmp_pu2[3] == 0) {
            cyc_12440 = 3;
          }
          else {
            if (local_20 == tmp_pu2[3]) {
              local_2c = 3;
              goto LAB_000d6c10;
            }
            if (tmp_pu2[4] == 0) {
              cyc_12440 = 4;
            }
            else {
              if (local_20 == tmp_pu2[4]) {
                local_2c = 4;
                goto LAB_000d6c10;
              }
              if (tmp_pu2[5] == 0) {
                cyc_12440 = 5;
              }
              else {
                if (local_20 == tmp_pu2[5]) {
                  local_2c = 5;
                  goto LAB_000d6c10;
                }
                if (tmp_pu2[6] == 0) {
                  cyc_12440 = 6;
                }
                else {
                  if (local_20 == tmp_pu2[6]) {
                    local_2c = 6;
                    goto LAB_000d6c10;
                  }
                  if (tmp_pu2[7] == 0) {
                    cyc_12440 = 7;
                  }
                  else {
                    if (local_20 == tmp_pu2[7]) {
                      local_2c = 7;
                      goto LAB_000d6c10;
                    }
                    if (tmp_pu2[8] == 0) {
                      cyc_12440 = 8;
                    }
                    else {
                      if (local_20 == tmp_pu2[8]) {
                        local_2c = 8;
                        goto LAB_000d6c10;
                      }
                      if (tmp_pu2[9] == 0) {
                        cyc_12440 = 9;
                      }
                      else {
                        if (local_20 == tmp_pu2[9]) {
                          local_2c = 9;
                          goto LAB_000d6c10;
                        }
                        if (tmp_pu2[10] == 0) {
                          cyc_12440 = 10;
                        }
                        else {
                          if (local_20 == tmp_pu2[10]) {
                            local_2c = 10;
                            goto LAB_000d6c10;
                          }
                          if (tmp_pu2[0xb] == 0) {
                            cyc_12440 = 0xb;
                          }
                          else {
                            if (local_20 == tmp_pu2[0xb]) {
                              local_2c = 0xb;
                              goto LAB_000d6c10;
                            }
                            cyc_12440 = 0xc;
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
    local_30 = local_30 + 1;
    tmp_pu2 = tmp_pu2 + 0xc;
  } while (local_30 != 10);
  local_2c = 0;
  bnk_12439 = 10;
  local_30 = 0;
LAB_000d5c60:
  tmp_u6 = local_20;
  if (tmp_u8 < 3) {
    if (*(uint *)(weapAlts + local_20 * 4) != 0) {
      tmp_u6 = *(uint *)(weapAlts + local_20 * 4);
    }
    if ((((_DAT_01090764 & 0x8020) == 0) && (tmp_i5 = COM_BitCheck(&g_unk_01090ad0,tmp_u6), tmp_i5 != 0))
       && ((tmp_u6 == 0x14 ||
           (((tmp_u6 == 1 ||
             (tmp_i5 = BG_FindAmmoForWeapon(tmp_u6), *(int *)(&g_unk_0109088c + tmp_i5 * 4) != 0)) ||
            (tmp_i5 = BG_FindClipForWeapon(tmp_u6), *(int *)(&g_unk_0109098c + tmp_i5 * 4) != 0))))))
    goto LAB_000d5b10;
  }
joined_r0x000d5ff2:
  if ((param_1 == 0) || (GHIDRA_FIELD(cg_cycleAllWeaps, 12, 4) != 0)) {
    tmp_u8 = tmp_u6 - 1;
    local_34 = 0xc;
    local_3c = 0;
    local_38 = tmp_u6;
    if (0x32 < tmp_u8) goto LAB_000d5f62;
    do {
      bnk_12439 = 0;
      tmp_pu2 = &weapBanksMultiPlayer;
      do {
        local_38 = *tmp_pu2;
        cyc_12440 = 0;
        if (local_38 != 0) {
          if (tmp_u6 == local_38) {
            tmp_u8 = 1;
            cyc_12440 = 0;
LAB_000d66f0:
            tmp_u1 = (&weapBanksMultiPlayer)[tmp_u8 + bnk_12439 * 0xc];
            if (tmp_u1 == 0) {
              tmp_u8 = local_38 - 1;
            }
            else {
              tmp_u8 = tmp_u1 - 1;
              tmp_u6 = tmp_u1;
              local_38 = tmp_u1;
            }
            goto LAB_000d5dc0;
          }
          if (tmp_pu2[1] == 0) {
            cyc_12440 = 1;
          }
          else {
            if (tmp_u6 == tmp_pu2[1]) {
              cyc_12440 = 1;
LAB_000d67c0:
              tmp_u8 = (cyc_12440 + 1) % 0xc;
              tmp_u6 = local_38;
              goto LAB_000d66f0;
            }
            if (tmp_pu2[2] == 0) {
              cyc_12440 = 2;
            }
            else {
              if (tmp_u6 == tmp_pu2[2]) {
                cyc_12440 = 2;
                goto LAB_000d67c0;
              }
              if (tmp_pu2[3] == 0) {
                cyc_12440 = 3;
              }
              else {
                if (tmp_u6 == tmp_pu2[3]) {
                  cyc_12440 = 3;
                  goto LAB_000d67c0;
                }
                if (tmp_pu2[4] == 0) {
                  cyc_12440 = 4;
                }
                else {
                  if (tmp_u6 == tmp_pu2[4]) {
                    cyc_12440 = 4;
                    goto LAB_000d67c0;
                  }
                  if (tmp_pu2[5] == 0) {
                    cyc_12440 = 5;
                  }
                  else {
                    if (tmp_u6 == tmp_pu2[5]) {
                      cyc_12440 = 5;
                      goto LAB_000d67c0;
                    }
                    if (tmp_pu2[6] == 0) {
                      cyc_12440 = 6;
                    }
                    else {
                      if (tmp_u6 == tmp_pu2[6]) {
                        cyc_12440 = 6;
                        goto LAB_000d67c0;
                      }
                      if (tmp_pu2[7] == 0) {
                        cyc_12440 = 7;
                      }
                      else {
                        if (tmp_u6 == tmp_pu2[7]) {
                          cyc_12440 = 7;
                          goto LAB_000d67c0;
                        }
                        if (tmp_pu2[8] == 0) {
                          cyc_12440 = 8;
                        }
                        else {
                          if (tmp_u6 == tmp_pu2[8]) {
                            cyc_12440 = 8;
                            goto LAB_000d67c0;
                          }
                          if (tmp_pu2[9] == 0) {
                            cyc_12440 = 9;
                          }
                          else {
                            if (tmp_u6 == tmp_pu2[9]) {
                              cyc_12440 = 9;
                              goto LAB_000d67c0;
                            }
                            if (tmp_pu2[10] == 0) {
                              cyc_12440 = 10;
                            }
                            else {
                              if (tmp_u6 == tmp_pu2[10]) {
                                cyc_12440 = 10;
                                goto LAB_000d67c0;
                              }
                              if (tmp_pu2[0xb] == 0) {
                                cyc_12440 = 0xb;
                              }
                              else {
                                if (tmp_u6 == tmp_pu2[0xb]) {
                                  cyc_12440 = 0xb;
                                  goto LAB_000d67c0;
                                }
                                cyc_12440 = 0xc;
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
        bnk_12439 = bnk_12439 + 1;
        tmp_pu2 = tmp_pu2 + 0xc;
      } while (bnk_12439 != 10);
      bnk_12439 = 10;
      local_38 = tmp_u6;
LAB_000d5dc0:
      if (0x32 < tmp_u8) goto LAB_000d5f62;
      bnk_12439 = 0;
      tmp_pu2 = &weapBanksMultiPlayer;
      do {
        cyc_12440 = 0;
        if (*tmp_pu2 != 0) {
          if (tmp_u6 == *tmp_pu2) {
            cyc_12440 = 0;
            local_3c = 0;
            goto LAB_000d5ef0;
          }
          if (tmp_pu2[1] == 0) {
            cyc_12440 = 1;
          }
          else {
            if (tmp_u6 == tmp_pu2[1]) {
              local_3c = 1;
LAB_000d6790:
              cyc_12440 = local_3c;
              goto LAB_000d5ef0;
            }
            if (tmp_pu2[2] == 0) {
              cyc_12440 = 2;
            }
            else {
              if (tmp_u6 == tmp_pu2[2]) {
                local_3c = 2;
                goto LAB_000d6790;
              }
              if (tmp_pu2[3] == 0) {
                cyc_12440 = 3;
              }
              else {
                if (tmp_u6 == tmp_pu2[3]) {
                  local_3c = 3;
                  goto LAB_000d6790;
                }
                if (tmp_pu2[4] == 0) {
                  cyc_12440 = 4;
                }
                else {
                  if (tmp_u6 == tmp_pu2[4]) {
                    local_3c = 4;
                    goto LAB_000d6790;
                  }
                  if (tmp_pu2[5] == 0) {
                    cyc_12440 = 5;
                  }
                  else {
                    if (tmp_u6 == tmp_pu2[5]) {
                      local_3c = 5;
                      goto LAB_000d6790;
                    }
                    if (tmp_pu2[6] == 0) {
                      cyc_12440 = 6;
                    }
                    else {
                      if (tmp_u6 == tmp_pu2[6]) {
                        local_3c = 6;
                        goto LAB_000d6790;
                      }
                      if (tmp_pu2[7] == 0) {
                        cyc_12440 = 7;
                      }
                      else {
                        if (tmp_u6 == tmp_pu2[7]) {
                          local_3c = 7;
                          goto LAB_000d6790;
                        }
                        if (tmp_pu2[8] == 0) {
                          cyc_12440 = 8;
                        }
                        else {
                          if (tmp_u6 == tmp_pu2[8]) {
                            local_3c = 8;
                            goto LAB_000d6790;
                          }
                          if (tmp_pu2[9] == 0) {
                            cyc_12440 = 9;
                          }
                          else {
                            if (tmp_u6 == tmp_pu2[9]) {
                              local_3c = 9;
                              goto LAB_000d6790;
                            }
                            if (tmp_pu2[10] == 0) {
                              cyc_12440 = 10;
                            }
                            else {
                              if (tmp_u6 == tmp_pu2[10]) {
                                local_3c = 10;
                                goto LAB_000d6790;
                              }
                              if (tmp_pu2[0xb] == 0) {
                                cyc_12440 = 0xb;
                              }
                              else {
                                if (tmp_u6 == tmp_pu2[0xb]) {
                                  local_3c = 0xb;
                                  goto LAB_000d6790;
                                }
                                cyc_12440 = 0xc;
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
        bnk_12439 = bnk_12439 + 1;
        tmp_pu2 = tmp_pu2 + 0xc;
      } while (bnk_12439 != 10);
      bnk_12439 = 10;
LAB_000d5ef0:
      if (param_1 == 0) goto LAB_000d6218;
      tmp_i5 = GHIDRA_FIELD(cg_cycleAllWeaps, 12, 4);
      if (local_3c <= local_2c) goto LAB_000d6015;
      while( true ) {
        if ((tmp_u6 == 0) ||
           ((((_DAT_01090764 & 0x8020) == 0 &&
             (tmp_i5 = COM_BitCheck(&g_unk_01090ad0,tmp_u6), tmp_i5 != 0)) &&
            ((tmp_u6 == 0x14 ||
             (((tmp_u6 == 1 ||
               (tmp_i5 = BG_FindAmmoForWeapon(local_38), *(int *)(&g_unk_0109088c + tmp_i5 * 4) != 0))
              || (tmp_i5 = BG_FindClipForWeapon(local_38), *(int *)(&g_unk_0109098c + tmp_i5 * 4) != 0))
             )))))) goto LAB_000d5b10;
        if (tmp_u6 == 0x16) {
          if ((((_DAT_01090764 & 0x8020) == 0) &&
              (tmp_i5 = COM_BitCheck(&g_unk_01090ad0,0x24), tmp_i5 != 0)) &&
             ((tmp_i5 = BG_FindAmmoForWeapon(0x24), *(int *)(&g_unk_0109088c + tmp_i5 * 4) != 0 ||
              (tmp_i5 = BG_FindClipForWeapon(0x24), *(int *)(&g_unk_0109098c + tmp_i5 * 4) != 0))))
          goto LAB_000d6290;
        }
        else if ((((tmp_u6 == 0x17) && ((_DAT_01090764 & 0x8020) == 0)) &&
                 (tmp_i5 = COM_BitCheck(&g_unk_01090ad0,0x25), tmp_i5 != 0)) &&
                ((tmp_i5 = BG_FindAmmoForWeapon(0x25), *(int *)(&g_unk_0109088c + tmp_i5 * 4) != 0 ||
                 (tmp_i5 = BG_FindClipForWeapon(0x25), *(int *)(&g_unk_0109098c + tmp_i5 * 4) != 0))))
        goto LAB_000d63a0;
        local_34 = local_34 + -1;
        if (local_34 == 0) goto LAB_000d5b10;
        tmp_u8 = tmp_u6 - 1;
        local_38 = tmp_u6;
        if (tmp_u8 < 0x33) break;
LAB_000d5f62:
        local_3c = 0;
        tmp_i5 = GHIDRA_FIELD(cg_cycleAllWeaps, 12, 4);
        if (param_1 != 0) goto LAB_000d6015;
LAB_000d6218:
        if (local_20 == tmp_u6) {
          return;
        }
      }
    } while( true );
  }
  local_3c = 0;
  tmp_i5 = 0;
LAB_000d6015:
  local_34 = 0;
  tmp_i7 = local_30 + 1;
LAB_000d6072:
  if (tmp_i5 == 0) {
    tmp_i5 = (&g_unk_010aad18)[tmp_i7];
    if (tmp_i5 == 0) {
      tmp_i5 = (&weapBanksMultiPlayer)[local_2c + (tmp_i7 % 10) * 0xc];
      if (tmp_i5 == 0) {
        tmp_i5 = (&weapBanksMultiPlayer)[(tmp_i7 % 10) * 0xc];
        goto LAB_000d605c;
      }
    }
LAB_000d608b:
    if ((((_DAT_01090764 & 0x8020) == 0) && (tmp_i4 = COM_BitCheck(&g_unk_01090ad0,tmp_i5), tmp_i4 != 0))
       && ((tmp_i5 == 0x14 ||
           (((tmp_i5 == 1 ||
             (tmp_i4 = BG_FindAmmoForWeapon(tmp_i5), *(int *)(&g_unk_0109088c + tmp_i4 * 4) != 0)) ||
            (tmp_i4 = BG_FindClipForWeapon(tmp_i5), *(int *)(&g_unk_0109098c + tmp_i4 * 4) != 0))))))
    goto LAB_000d6200;
    if (tmp_i5 == 0x16) {
      if ((((_DAT_01090764 & 0x8020) == 0) && (tmp_i4 = COM_BitCheck(&g_unk_01090ad0,0x24), tmp_i4 != 0)
          ) && ((tmp_i4 = BG_FindAmmoForWeapon(0x24), *(int *)(&g_unk_0109088c + tmp_i4 * 4) != 0 ||
                (tmp_i4 = BG_FindClipForWeapon(0x24), *(int *)(&g_unk_0109098c + tmp_i4 * 4) != 0))))
      goto LAB_000d6290;
LAB_000d60c9:
      tmp_pi3 = &weapBanksMultiPlayer;
      bnk_12439 = 0;
      do {
        cyc_12440 = 0;
        if (*tmp_pi3 != 0) {
          if (tmp_i5 == *tmp_pi3) {
            cyc_12440 = 0;
            local_3c = 0;
            tmp_u8 = local_3c;
            local_34 = bnk_12439;
            goto LAB_000d63e1;
          }
          if (tmp_pi3[1] == 0) {
            cyc_12440 = 1;
          }
          else {
            if (tmp_i5 == tmp_pi3[1]) {
              local_3c = 1;
LAB_000d6b60:
              cyc_12440 = local_3c;
              local_34 = bnk_12439;
              goto LAB_000d61f0;
            }
            if (tmp_pi3[2] == 0) {
              cyc_12440 = 2;
            }
            else {
              if (tmp_i5 == tmp_pi3[2]) {
                local_3c = 2;
                goto LAB_000d6b60;
              }
              if (tmp_pi3[3] == 0) {
                cyc_12440 = 3;
              }
              else {
                if (tmp_i5 == tmp_pi3[3]) {
                  local_3c = 3;
                  goto LAB_000d6b60;
                }
                if (tmp_pi3[4] == 0) {
                  cyc_12440 = 4;
                }
                else {
                  if (tmp_i5 == tmp_pi3[4]) {
                    local_3c = 4;
                    goto LAB_000d6b60;
                  }
                  if (tmp_pi3[5] == 0) {
                    cyc_12440 = 5;
                  }
                  else {
                    if (tmp_i5 == tmp_pi3[5]) {
                      local_3c = 5;
                      goto LAB_000d6b60;
                    }
                    if (tmp_pi3[6] == 0) {
                      cyc_12440 = 6;
                    }
                    else {
                      if (tmp_i5 == tmp_pi3[6]) {
                        local_3c = 6;
                        goto LAB_000d6b60;
                      }
                      if (tmp_pi3[7] == 0) {
                        cyc_12440 = 7;
                      }
                      else {
                        if (tmp_i5 == tmp_pi3[7]) {
                          local_3c = 7;
                          goto LAB_000d6b60;
                        }
                        if (tmp_pi3[8] == 0) {
                          cyc_12440 = 8;
                        }
                        else {
                          if (tmp_i5 == tmp_pi3[8]) {
                            local_3c = 8;
                            goto LAB_000d6b60;
                          }
                          if (tmp_pi3[9] == 0) {
                            cyc_12440 = 9;
                          }
                          else {
                            if (tmp_i5 == tmp_pi3[9]) {
                              local_3c = 9;
                              goto LAB_000d6b60;
                            }
                            if (tmp_pi3[10] == 0) {
                              cyc_12440 = 10;
                            }
                            else {
                              if (tmp_i5 == tmp_pi3[10]) {
                                local_3c = 10;
                                goto LAB_000d6b60;
                              }
                              if (tmp_pi3[0xb] == 0) {
                                cyc_12440 = 0xb;
                              }
                              else {
                                if (tmp_i5 == tmp_pi3[0xb]) {
                                  local_3c = 0xb;
                                  goto LAB_000d6b60;
                                }
                                cyc_12440 = 0xc;
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
        bnk_12439 = bnk_12439 + 1;
        tmp_pi3 = tmp_pi3 + 0xc;
      } while (bnk_12439 != 10);
      bnk_12439 = 10;
LAB_000d61f0:
      tmp_u8 = local_3c;
      if (0xb < local_3c) {
LAB_000d6200:
        CG_FinishWeaponChange(local_20,tmp_i5);
        return;
      }
    }
    else {
      if (tmp_i5 == 0x17) {
        if ((((_DAT_01090764 & 0x8020) != 0) ||
            (tmp_i4 = COM_BitCheck(&g_unk_01090ad0,0x25), tmp_i4 == 0)) ||
           ((tmp_i4 = BG_FindAmmoForWeapon(0x25), *(int *)(&g_unk_0109088c + tmp_i4 * 4) == 0 &&
            (tmp_i4 = BG_FindClipForWeapon(0x25), *(int *)(&g_unk_0109098c + tmp_i4 * 4) == 0))))
        goto LAB_000d60c9;
LAB_000d63a0:
        tmp_u6 = 0x25;
        goto LAB_000d5b10;
      }
      if (tmp_i5 - 1U < 0x33) goto LAB_000d60c9;
      local_3c = 0;
      local_34 = 0;
      tmp_u8 = local_3c;
    }
LAB_000d63e1:
    do {
      tmp_u8 = tmp_u8 + 1;
      tmp_i5 = (&weapBanksMultiPlayer)[(int)tmp_u8 % 0xc + local_34 * 0xc];
      if ((tmp_i5 == 0) && (tmp_i5 = (&weapBanksMultiPlayer)[local_34 * 0xc], tmp_i5 == 0)) break;
      if ((((_DAT_01090764 & 0x8020) == 0) &&
          (tmp_i4 = COM_BitCheck(&g_unk_01090ad0,tmp_i5), tmp_i4 != 0)) &&
         ((((tmp_i5 == 0x14 || (tmp_i5 == 1)) ||
           (tmp_i4 = BG_FindAmmoForWeapon(tmp_i5), *(int *)(&g_unk_0109088c + tmp_i4 * 4) != 0)) ||
          (tmp_i4 = BG_FindClipForWeapon(tmp_i5), *(int *)(&g_unk_0109098c + tmp_i4 * 4) != 0)))) {
        if (tmp_i5 != 0) goto LAB_000d6200;
        break;
      }
      if (tmp_i5 == 0x16) {
        if ((((_DAT_01090764 & 0x8020) == 0) &&
            (tmp_i5 = COM_BitCheck(&g_unk_01090ad0,0x24), tmp_i5 != 0)) &&
           ((tmp_i5 = BG_FindAmmoForWeapon(0x24), *(int *)(&g_unk_0109088c + tmp_i5 * 4) != 0 ||
            (tmp_i5 = BG_FindClipForWeapon(0x24), *(int *)(&g_unk_0109098c + tmp_i5 * 4) != 0))))
        goto LAB_000d6290;
      }
      else if (((tmp_i5 == 0x17) && ((_DAT_01090764 & 0x8020) == 0)) &&
              ((tmp_i5 = COM_BitCheck(&g_unk_01090ad0,0x25), tmp_i5 != 0 &&
               ((tmp_i5 = BG_FindAmmoForWeapon(0x25), *(int *)(&g_unk_0109088c + tmp_i5 * 4) != 0 ||
                (tmp_i5 = BG_FindClipForWeapon(0x25), *(int *)(&g_unk_0109098c + tmp_i5 * 4) != 0))))))
      goto LAB_000d63a0;
    } while ((int)tmp_u8 < 0xc);
  }
  else {
    tmp_i5 = (&weapBanksMultiPlayer)[(tmp_i7 % 10) * 0xc];
LAB_000d605c:
    if (tmp_i5 != 0) goto LAB_000d608b;
  }
  tmp_i7 = tmp_i7 + 1;
  tmp_i5 = GHIDRA_FIELD(cg_cycleAllWeaps, 12, 4);
  if (tmp_i7 == local_30 + 0xb) goto LAB_000d5b00;
  goto LAB_000d6072;
LAB_000d6290:
  tmp_u6 = 0x24;
  goto LAB_000d5b10;
LAB_000d5b00:
  tmp_u6 = 0;
LAB_000d5b10:
  CG_FinishWeaponChange(local_20,tmp_u6);
  return;
}

void CG_PrevWeap(int param_1)
{
  int tmp_i1;
  int tmp_i2;
  uint tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint *tmp_pu7;
  uint tmp_u8;
  int tmp_i9;
  uint local_44;
  uint local_40;
  int local_3c;
  uint local_38;
  int local_34;
  uint local_2c;
  
  local_2c = g_unk_01091814;
  if ((g_unk_01091814 & 0xfffffffb) == 0x2a) {
    return;
  }
  switch(g_unk_01091814) {
  case 0xe:
    tmp_u4 = 0xffffffde;
    local_2c = 2;
    break;
  default:
    tmp_u4 = g_unk_01091814 - 1;
    if (tmp_u4 < 0x33) {
      tmp_u4 = g_unk_01091814 - 0x24;
      break;
    }
    if ((param_1 == 0) || (GHIDRA_FIELD(cg_cycleAllWeaps, 12, 4) != 0)) {
      local_34 = 0;
      local_38 = 0;
      tmp_u8 = g_unk_01091814;
      goto LAB_000d7880;
    }
    local_38 = 0;
    local_34 = 0;
    tmp_i6 = 0;
    goto LAB_000d7130;
  case 0x24:
    tmp_u4 = 0xfffffff2;
    local_2c = 0x16;
    break;
  case 0x25:
    tmp_u4 = 0xfffffff3;
    local_2c = 0x17;
    break;
  case 0x26:
    tmp_u4 = 0xffffffe3;
    local_2c = 7;
    break;
  case 0x2a:
    tmp_u4 = 0xfffffffd;
    local_2c = 0x21;
  }
  tmp_pu7 = &weapBanksMultiPlayer;
  local_34 = 0;
  do {
    cyc_12440 = 0;
    if (*tmp_pu7 != 0) {
      bnk_12439 = local_34;
      if (local_2c == *tmp_pu7) {
        cyc_12440 = 0;
        local_38 = 0;
        goto LAB_000d7020;
      }
      if (tmp_pu7[1] == 0) {
        cyc_12440 = 1;
      }
      else {
        if (local_2c == tmp_pu7[1]) {
          local_38 = 1;
LAB_000d8370:
          cyc_12440 = local_38;
          goto LAB_000d7020;
        }
        if (tmp_pu7[2] == 0) {
          cyc_12440 = 2;
        }
        else {
          if (local_2c == tmp_pu7[2]) {
            local_38 = 2;
            goto LAB_000d8370;
          }
          if (tmp_pu7[3] == 0) {
            cyc_12440 = 3;
          }
          else {
            if (local_2c == tmp_pu7[3]) {
              local_38 = 3;
              goto LAB_000d8370;
            }
            if (tmp_pu7[4] == 0) {
              cyc_12440 = 4;
            }
            else {
              if (local_2c == tmp_pu7[4]) {
                local_38 = 4;
                goto LAB_000d8370;
              }
              if (tmp_pu7[5] == 0) {
                cyc_12440 = 5;
              }
              else {
                if (local_2c == tmp_pu7[5]) {
                  local_38 = 5;
                  goto LAB_000d8370;
                }
                if (tmp_pu7[6] == 0) {
                  cyc_12440 = 6;
                }
                else {
                  if (local_2c == tmp_pu7[6]) {
                    local_38 = 6;
                    goto LAB_000d8370;
                  }
                  if (tmp_pu7[7] == 0) {
                    cyc_12440 = 7;
                  }
                  else {
                    if (local_2c == tmp_pu7[7]) {
                      local_38 = 7;
                      goto LAB_000d8370;
                    }
                    if (tmp_pu7[8] == 0) {
                      cyc_12440 = 8;
                    }
                    else {
                      if (local_2c == tmp_pu7[8]) {
                        local_38 = 8;
                        goto LAB_000d8370;
                      }
                      if (tmp_pu7[9] == 0) {
                        cyc_12440 = 9;
                      }
                      else {
                        if (local_2c == tmp_pu7[9]) {
                          local_38 = 9;
                          goto LAB_000d8370;
                        }
                        if (tmp_pu7[10] == 0) {
                          cyc_12440 = 10;
                        }
                        else {
                          if (local_2c == tmp_pu7[10]) {
                            local_38 = 10;
                            goto LAB_000d8370;
                          }
                          if (tmp_pu7[0xb] == 0) {
                            cyc_12440 = 0xb;
                          }
                          else {
                            if (local_2c == tmp_pu7[0xb]) {
                              local_38 = 0xb;
                              goto LAB_000d8370;
                            }
                            cyc_12440 = 0xc;
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
    local_34 = local_34 + 1;
    tmp_pu7 = tmp_pu7 + 0xc;
  } while (local_34 != 10);
  local_38 = 0;
  bnk_12439 = 10;
  local_34 = 0;
LAB_000d7020:
  tmp_u8 = local_2c;
  if (tmp_u4 < 3) {
    tmp_u8 = *(uint *)(weapAlts + local_2c * 4);
    if (*(uint *)(weapAlts + local_2c * 4) == 0) {
      tmp_u8 = local_2c;
    }
    if ((((_DAT_01090764 & 0x8020) == 0) && (tmp_i6 = COM_BitCheck(&g_unk_01090ad0,tmp_u8), tmp_i6 != 0))
       && ((tmp_u8 == 0x14 ||
           (((tmp_u8 == 1 ||
             (tmp_i6 = BG_FindAmmoForWeapon(tmp_u8), *(int *)(&g_unk_0109088c + tmp_i6 * 4) != 0)) ||
            (tmp_i6 = BG_FindClipForWeapon(tmp_u8), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0))))))
    goto LAB_000d6ec0;
    if ((param_1 == 0) || (GHIDRA_FIELD(cg_cycleAllWeaps, 12, 4) != 0)) {
      tmp_u4 = tmp_u8 - 1;
      goto LAB_000d7880;
    }
    tmp_i6 = 0;
  }
  else {
    if (param_1 == 0) {
      tmp_u4 = local_2c - 1;
LAB_000d7880:
      local_40 = 0;
      local_44 = local_38;
      if (0x32 < tmp_u4) goto LAB_000d7b4c;
LAB_000d789d:
      bnk_12439 = 0;
      tmp_pu7 = &weapBanksMultiPlayer;
      do {
        tmp_u3 = *tmp_pu7;
        cyc_12440 = 0;
        if (tmp_u3 != 0) {
          if (tmp_u8 == tmp_u3) {
            tmp_i6 = 0xb;
            cyc_12440 = 0;
LAB_000d7cd0:
            tmp_i2 = bnk_12439 * 0xc;
            goto LAB_000d7dc8;
          }
          if (tmp_pu7[1] == 0) {
            cyc_12440 = 1;
          }
          else {
            if (tmp_u8 == tmp_pu7[1]) {
              cyc_12440 = 1;
LAB_000d7ec0:
              tmp_i6 = cyc_12440 - 1;
              goto LAB_000d7cd0;
            }
            if (tmp_pu7[2] == 0) {
              cyc_12440 = 2;
            }
            else {
              if (tmp_u8 == tmp_pu7[2]) {
                cyc_12440 = 2;
                goto LAB_000d7ec0;
              }
              if (tmp_pu7[3] == 0) {
                cyc_12440 = 3;
              }
              else {
                if (tmp_u8 == tmp_pu7[3]) {
                  cyc_12440 = 3;
                  goto LAB_000d7ec0;
                }
                if (tmp_pu7[4] == 0) {
                  cyc_12440 = 4;
                }
                else {
                  if (tmp_u8 == tmp_pu7[4]) {
                    cyc_12440 = 4;
                    goto LAB_000d7ec0;
                  }
                  if (tmp_pu7[5] == 0) {
                    cyc_12440 = 5;
                  }
                  else {
                    if (tmp_u8 == tmp_pu7[5]) {
                      cyc_12440 = 5;
                      goto LAB_000d7ec0;
                    }
                    if (tmp_pu7[6] == 0) {
                      cyc_12440 = 6;
                    }
                    else {
                      if (tmp_u8 == tmp_pu7[6]) {
                        cyc_12440 = 6;
                        goto LAB_000d7ec0;
                      }
                      if (tmp_pu7[7] == 0) {
                        cyc_12440 = 7;
                      }
                      else {
                        if (tmp_u8 == tmp_pu7[7]) {
                          cyc_12440 = 7;
                          goto LAB_000d7ec0;
                        }
                        if (tmp_pu7[8] == 0) {
                          cyc_12440 = 8;
                        }
                        else {
                          if (tmp_u8 == tmp_pu7[8]) {
                            cyc_12440 = 8;
                            goto LAB_000d7ec0;
                          }
                          if (tmp_pu7[9] == 0) {
                            cyc_12440 = 9;
                          }
                          else {
                            if (tmp_u8 == tmp_pu7[9]) {
                              cyc_12440 = 9;
                              goto LAB_000d7ec0;
                            }
                            if (tmp_pu7[10] == 0) {
                              cyc_12440 = 10;
                            }
                            else {
                              if (tmp_u8 == tmp_pu7[10]) {
                                cyc_12440 = 10;
                                goto LAB_000d7ec0;
                              }
                              if (tmp_pu7[0xb] == 0) {
                                cyc_12440 = 0xb;
                              }
                              else {
                                if (tmp_u8 == tmp_pu7[0xb]) {
                                  cyc_12440 = 0xb;
                                  goto LAB_000d7ec0;
                                }
                                cyc_12440 = 0xc;
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
        bnk_12439 = bnk_12439 + 1;
        tmp_pu7 = tmp_pu7 + 0xc;
      } while (bnk_12439 != 10);
      bnk_12439 = 10;
      goto LAB_000d79c0;
    }
    tmp_i6 = 0;
    if (GHIDRA_FIELD(cg_cycleAllWeaps, 12, 4) != 0) {
      tmp_u4 = local_2c - 1;
      goto LAB_000d7880;
    }
  }
LAB_000d7130:
  tmp_i2 = local_34;
  local_34 = 0;
  local_3c = tmp_i2;
LAB_000d7160:
  tmp_i9 = local_3c;
  if (tmp_i6 == 0) {
    do {
      tmp_i6 = tmp_i9 + -1;
      if (tmp_i9 + -1 < 0) {
        tmp_i6 = tmp_i9 + 9;
      }
      tmp_i9 = tmp_i6 % 10;
      tmp_u8 = (&weapBanksMultiPlayer)[local_38 + tmp_i9 * 0xc];
    } while ((((((((tmp_u8 == 0) && (tmp_u8 = (&g_unk_0013e7cc)[tmp_i9 * 0xc], tmp_u8 == 0)) &&
                 (tmp_u8 = (&g_unk_0013e7c8)[tmp_i9 * 0xc], tmp_u8 == 0)) &&
                ((tmp_u8 = (&g_unk_0013e7c4)[tmp_i9 * 0xc], tmp_u8 == 0 &&
                 (tmp_u8 = (&g_unk_0013e7c0)[tmp_i9 * 0xc], tmp_u8 == 0)))) &&
               ((tmp_u8 = (&g_unk_0013e7bc)[tmp_i9 * 0xc], tmp_u8 == 0 &&
                ((tmp_u8 = (&g_unk_0013e7b8)[tmp_i9 * 0xc], tmp_u8 == 0 &&
                 (tmp_u8 = (&g_unk_0013e7b4)[tmp_i9 * 0xc], tmp_u8 == 0)))))) &&
              (tmp_u8 = (&g_unk_0013e7b0)[tmp_i9 * 0xc], tmp_u8 == 0)) &&
             (((tmp_u8 = (&g_unk_0013e7ac)[tmp_i9 * 0xc], tmp_u8 == 0 &&
               (tmp_u8 = (&g_unk_0013e7a8)[tmp_i9 * 0xc], tmp_u8 == 0)) &&
              (tmp_u8 = (&g_unk_0013e7a4)[tmp_i9 * 0xc], tmp_u8 == 0)))) &&
            (tmp_u8 = (&weapBanksMultiPlayer)[tmp_i9 * 0xc], tmp_u8 == 0));
  }
  else {
    do {
      tmp_i6 = tmp_i9 + -1;
      if (tmp_i9 + -1 < 0) {
        tmp_i6 = tmp_i9 + 9;
      }
      tmp_i9 = tmp_i6 % 10;
      tmp_u8 = (&g_unk_0013e7cc)[tmp_i9 * 0xc];
    } while ((((tmp_u8 == 0) && (tmp_u8 = (&g_unk_0013e7c8)[tmp_i9 * 0xc], tmp_u8 == 0)) &&
             (((tmp_u8 = (&g_unk_0013e7c4)[tmp_i9 * 0xc], tmp_u8 == 0 &&
               ((tmp_u8 = (&g_unk_0013e7c0)[tmp_i9 * 0xc], tmp_u8 == 0 &&
                (tmp_u8 = (&g_unk_0013e7bc)[tmp_i9 * 0xc], tmp_u8 == 0)))) &&
              (tmp_u8 = (&g_unk_0013e7b8)[tmp_i9 * 0xc], tmp_u8 == 0)))) &&
            ((((tmp_u8 = (&g_unk_0013e7b4)[tmp_i9 * 0xc], tmp_u8 == 0 &&
               (tmp_u8 = (&g_unk_0013e7b0)[tmp_i9 * 0xc], tmp_u8 == 0)) &&
              (tmp_u8 = (&g_unk_0013e7ac)[tmp_i9 * 0xc], tmp_u8 == 0)) &&
             (((tmp_u8 = (&g_unk_0013e7a8)[tmp_i9 * 0xc], tmp_u8 == 0 &&
               (tmp_u8 = (&g_unk_0013e7a4)[tmp_i9 * 0xc], tmp_u8 == 0)) &&
              (tmp_u8 = (&weapBanksMultiPlayer)[tmp_i9 * 0xc], tmp_u8 == 0))))));
  }
  tmp_u4 = _DAT_01090764 & 0x8020;
  if (tmp_u4 == 0) {
    tmp_i6 = COM_BitCheck(&g_unk_01090ad0,tmp_u8);
    if (tmp_i6 == 0) {
      tmp_u4 = _DAT_01090764 & 0x8020;
    }
    else {
      if (((tmp_u8 == 0x14) || (tmp_u8 == 1)) ||
         ((tmp_i6 = BG_FindAmmoForWeapon(tmp_u8), *(int *)(&g_unk_0109088c + tmp_i6 * 4) != 0 ||
          (tmp_i6 = BG_FindClipForWeapon(tmp_u8), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0))))
      goto LAB_000d6ec0;
      tmp_u4 = _DAT_01090764 & 0x8020;
    }
  }
  if (tmp_u8 == 0x16) {
    if (((tmp_u4 == 0) && (tmp_i6 = COM_BitCheck(&g_unk_01090ad0,0x24), tmp_i6 != 0)) &&
       ((tmp_i6 = BG_FindAmmoForWeapon(0x24), *(int *)(&g_unk_0109088c + tmp_i6 * 4) != 0 ||
        (tmp_i6 = BG_FindClipForWeapon(0x24), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0))))
    goto LAB_000d6eac;
LAB_000d7246:
    bnk_12439 = 0;
    tmp_pu7 = &weapBanksMultiPlayer;
    do {
      cyc_12440 = 0;
      if (*tmp_pu7 != 0) {
        if (tmp_u8 == *tmp_pu7) {
          cyc_12440 = 0;
          local_34 = bnk_12439;
          goto LAB_000d745e;
        }
        if (tmp_pu7[1] == 0) {
          cyc_12440 = 1;
        }
        else {
          if (tmp_u8 == tmp_pu7[1]) {
            cyc_12440 = 1;
            local_34 = bnk_12439;
            goto LAB_000d745e;
          }
          if (tmp_pu7[2] == 0) {
            cyc_12440 = 2;
          }
          else {
            if (tmp_u8 == tmp_pu7[2]) {
              cyc_12440 = 2;
              local_34 = bnk_12439;
              goto LAB_000d745e;
            }
            if (tmp_pu7[3] == 0) {
              cyc_12440 = 3;
            }
            else {
              if (tmp_u8 == tmp_pu7[3]) {
                cyc_12440 = 3;
                local_34 = bnk_12439;
                goto LAB_000d745e;
              }
              if (tmp_pu7[4] == 0) {
                cyc_12440 = 4;
              }
              else {
                if (tmp_u8 == tmp_pu7[4]) {
                  cyc_12440 = 4;
                  local_34 = bnk_12439;
                  goto LAB_000d745e;
                }
                if (tmp_pu7[5] == 0) {
                  cyc_12440 = 5;
                }
                else {
                  if (tmp_u8 == tmp_pu7[5]) {
                    cyc_12440 = 5;
                    local_34 = bnk_12439;
                    goto LAB_000d745e;
                  }
                  if (tmp_pu7[6] == 0) {
                    cyc_12440 = 6;
                  }
                  else {
                    if (tmp_u8 == tmp_pu7[6]) {
                      cyc_12440 = 6;
                      local_34 = bnk_12439;
                      goto LAB_000d745e;
                    }
                    if (tmp_pu7[7] == 0) {
                      cyc_12440 = 7;
                    }
                    else {
                      if (tmp_u8 == tmp_pu7[7]) {
                        cyc_12440 = 7;
                        local_34 = bnk_12439;
                        goto LAB_000d745e;
                      }
                      if (tmp_pu7[8] == 0) {
                        cyc_12440 = 8;
                      }
                      else {
                        if (tmp_u8 == tmp_pu7[8]) {
                          cyc_12440 = 8;
                          local_34 = bnk_12439;
                          goto LAB_000d745e;
                        }
                        if (tmp_pu7[9] == 0) {
                          cyc_12440 = 9;
                        }
                        else {
                          if (tmp_u8 == tmp_pu7[9]) {
                            cyc_12440 = 9;
                            local_34 = bnk_12439;
                            goto LAB_000d745e;
                          }
                          if (tmp_pu7[10] == 0) {
                            cyc_12440 = 10;
                          }
                          else {
                            if (tmp_u8 == tmp_pu7[10]) {
                              cyc_12440 = 10;
                              local_34 = bnk_12439;
                              goto LAB_000d745e;
                            }
                            if (tmp_pu7[0xb] == 0) {
                              cyc_12440 = 0xb;
                            }
                            else {
                              if (tmp_u8 == tmp_pu7[0xb]) {
                                cyc_12440 = 0xb;
                                local_34 = bnk_12439;
                                goto LAB_000d745e;
                              }
                              cyc_12440 = 0xc;
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
      bnk_12439 = bnk_12439 + 1;
      tmp_pu7 = tmp_pu7 + 0xc;
    } while (bnk_12439 != 10);
    bnk_12439 = 10;
  }
  else {
    if (tmp_u8 == 0x17) {
      if (((tmp_u4 != 0) || (tmp_i6 = COM_BitCheck(&g_unk_01090ad0,0x25), tmp_i6 == 0)) ||
         ((tmp_i6 = BG_FindAmmoForWeapon(0x25), *(int *)(&g_unk_0109088c + tmp_i6 * 4) == 0 &&
          (tmp_i6 = BG_FindClipForWeapon(0x25), *(int *)(&g_unk_0109098c + tmp_i6 * 4) == 0))))
      goto LAB_000d7246;
LAB_000d76c6:
      tmp_u8 = 0x25;
      goto LAB_000d6ec0;
    }
    if (tmp_u8 - 1 < 0x33) goto LAB_000d7246;
    local_34 = 0;
  }
LAB_000d745e:
  local_44 = 0xc;
  do {
    local_44 = local_44 + -1;
    tmp_i6 = local_34 * 0xc;
    tmp_i9 = local_44;
    do {
      do {
        do {
          do {
            do {
              do {
                do {
                  do {
                    tmp_i5 = tmp_i9;
                    tmp_u8 = (&weapBanksMultiPlayer)[local_34 * 0xc + tmp_i5];
                    if (tmp_u8 != 0) goto LAB_000d75b0;
                    if (tmp_i5 + -1 < 0) {
                      tmp_u8 = (&g_unk_0013e7cc)[local_34 * 0xc];
                      if (((tmp_u8 != 0) || (tmp_u8 = (&g_unk_0013e7c8)[local_34 * 0xc], tmp_u8 != 0)) ||
                         (tmp_u8 = (&weapBanksMultiPlayer)[local_34 * 0xc + 9], tmp_u8 != 0))
                      goto LAB_000d75b0;
                      tmp_i5 = 8;
                      goto LAB_000d74bc;
                    }
                    tmp_u8 = (&weapBanksMultiPlayer)[tmp_i5 + -1 + local_34 * 0xc];
                    if (tmp_u8 != 0) goto LAB_000d75b0;
                    tmp_i9 = 0xb;
                  } while (tmp_i5 + -2 == -1);
                  tmp_u8 = (&weapBanksMultiPlayer)[tmp_i6 + tmp_i5 + -2];
                  if (tmp_u8 != 0) goto LAB_000d75b0;
                  tmp_i5 = tmp_i5 + -3;
                } while (tmp_i5 == -1);
LAB_000d74bc:
                tmp_i1 = local_34 * 0xc;
                tmp_u8 = (&weapBanksMultiPlayer)[tmp_i1 + tmp_i5];
                if (tmp_u8 != 0) goto LAB_000d75b0;
                tmp_i9 = 0xb;
              } while (tmp_i5 + -1 == -1);
              tmp_u8 = (&weapBanksMultiPlayer)[tmp_i5 + -1 + tmp_i6];
              if (tmp_u8 != 0) goto LAB_000d75b0;
            } while (tmp_i5 + -2 == -1);
            tmp_u8 = (&weapBanksMultiPlayer)[tmp_i5 + -2 + tmp_i1];
            if (tmp_u8 != 0) goto LAB_000d75b0;
          } while (tmp_i5 + -3 == -1);
          tmp_u8 = (&weapBanksMultiPlayer)[tmp_i5 + -3 + tmp_i1];
          if (tmp_u8 != 0) goto LAB_000d75b0;
        } while (tmp_i5 + -4 == -1);
        tmp_u8 = (&weapBanksMultiPlayer)[tmp_i1 + tmp_i5 + -4];
        if (tmp_u8 != 0) goto LAB_000d75b0;
      } while (tmp_i5 + -5 == -1);
      tmp_u8 = (&weapBanksMultiPlayer)[local_34 * 0xc + tmp_i5 + -5];
      if (tmp_u8 != 0) break;
      tmp_i9 = 0xb;
    } while ((tmp_i5 + -6 == -1) ||
            ((tmp_u8 = (&weapBanksMultiPlayer)[tmp_i5 + -6 + tmp_i6], tmp_u8 == 0 &&
             ((tmp_i5 = tmp_i5 + -7, tmp_i5 == -1 ||
              ((tmp_u8 = (&weapBanksMultiPlayer)[local_34 * 0xc + tmp_i5], tmp_u8 == 0 &&
               ((tmp_i5 == 0 || (tmp_u8 = (&weapBanksMultiPlayer)[local_34 * 0xc], tmp_u8 == 0)))))))))
            );
LAB_000d75b0:
    if (((_DAT_01090764 & 0x8020) == 0) &&
       ((tmp_i6 = COM_BitCheck(&g_unk_01090ad0,tmp_u8), tmp_i6 != 0 &&
        (((tmp_u8 == 0x14 || (tmp_u8 == 1)) ||
         ((tmp_i6 = BG_FindAmmoForWeapon(tmp_u8), *(int *)(&g_unk_0109088c + tmp_i6 * 4) != 0 ||
          (tmp_i6 = BG_FindClipForWeapon(tmp_u8), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0))))))))
    goto LAB_000d6ec0;
    if (tmp_u8 == 0x16) {
      if ((((_DAT_01090764 & 0x8020) == 0) && (tmp_i6 = COM_BitCheck(&g_unk_01090ad0,0x24), tmp_i6 != 0)
          ) && ((tmp_i6 = BG_FindAmmoForWeapon(0x24), *(int *)(&g_unk_0109088c + tmp_i6 * 4) != 0 ||
                (tmp_i6 = BG_FindClipForWeapon(0x24), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0))))
      goto LAB_000d6eac;
    }
    else if ((((tmp_u8 == 0x17) && ((_DAT_01090764 & 0x8020) == 0)) &&
             (tmp_i6 = COM_BitCheck(&g_unk_01090ad0,0x25), tmp_i6 != 0)) &&
            ((tmp_i6 = BG_FindAmmoForWeapon(0x25), *(int *)(&g_unk_0109088c + tmp_i6 * 4) != 0 ||
             (tmp_i6 = BG_FindClipForWeapon(0x25), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0))))
    goto LAB_000d76c6;
  } while (local_44 != 0);
  local_3c = local_3c + -1;
  tmp_i6 = GHIDRA_FIELD(cg_cycleAllWeaps, 12, 4);
  if (local_3c == tmp_i2 + -10) goto LAB_000d7710;
  goto LAB_000d7160;
  while( true ) {
    tmp_i6 = 0xb;
    if ((tmp_i9 + -1 != -1) &&
       ((tmp_u8 = (&weapBanksMultiPlayer)[tmp_i9 + -1 + tmp_i2],
        (&weapBanksMultiPlayer)[tmp_i9 + -1 + tmp_i2] != 0 ||
        ((tmp_i9 + -2 != -1 &&
         ((tmp_u8 = (&weapBanksMultiPlayer)[tmp_i9 + -2 + tmp_i5],
          (&weapBanksMultiPlayer)[tmp_i9 + -2 + tmp_i5] != 0 ||
          ((tmp_i9 + -3 != -1 &&
           ((tmp_u8 = (&weapBanksMultiPlayer)[tmp_i9 + -3 + tmp_i5],
            (&weapBanksMultiPlayer)[tmp_i9 + -3 + tmp_i5] != 0 ||
            ((tmp_i9 + -4 != -1 &&
             ((tmp_u8 = (&weapBanksMultiPlayer)[tmp_i9 + -4 + tmp_i5],
              (&weapBanksMultiPlayer)[tmp_i9 + -4 + tmp_i5] != 0 ||
              ((tmp_i9 + -5 != -1 &&
               ((tmp_u8 = (&weapBanksMultiPlayer)[tmp_i5 + tmp_i9 + -5],
                (&weapBanksMultiPlayer)[tmp_i5 + tmp_i9 + -5] != 0 ||
                ((tmp_i9 + -6 != -1 &&
                 ((tmp_u8 = (&weapBanksMultiPlayer)[tmp_i9 + -6 + tmp_i2],
                  (&weapBanksMultiPlayer)[tmp_i9 + -6 + tmp_i2] != 0 ||
                  ((tmp_i9 = tmp_i9 + -7, tmp_i9 != -1 &&
                   ((tmp_u8 = (&weapBanksMultiPlayer)[tmp_i5 + tmp_i9],
                    (&weapBanksMultiPlayer)[tmp_i5 + tmp_i9] != 0 ||
                    ((tmp_i9 != 0 && (tmp_u8 = tmp_u3, tmp_u3 != 0)))))))))))))))))))))))))))))) break;
LAB_000d7dc8:
    do {
      do {
        tmp_i9 = tmp_i6;
        tmp_u8 = (&weapBanksMultiPlayer)[bnk_12439 * 0xc + tmp_i9];
        if ((&weapBanksMultiPlayer)[bnk_12439 * 0xc + tmp_i9] != 0) goto LAB_000d7df2;
        if (tmp_i9 + -1 == -1) {
          tmp_u8 = (&g_unk_0013e7cc)[bnk_12439 * 0xc];
          if ((((&g_unk_0013e7cc)[bnk_12439 * 0xc] != 0) ||
              (tmp_u8 = (&g_unk_0013e7c8)[bnk_12439 * 0xc], (&g_unk_0013e7c8)[bnk_12439 * 0xc] != 0)) ||
             (tmp_u8 = (&weapBanksMultiPlayer)[bnk_12439 * 0xc + 9],
             (&weapBanksMultiPlayer)[bnk_12439 * 0xc + 9] != 0)) goto LAB_000d7df2;
          tmp_i9 = 8;
          goto LAB_000d7d14;
        }
        tmp_u8 = (&weapBanksMultiPlayer)[tmp_i9 + -1 + bnk_12439 * 0xc];
        if ((&weapBanksMultiPlayer)[tmp_i9 + -1 + bnk_12439 * 0xc] != 0) goto LAB_000d7df2;
        tmp_i6 = 0xb;
      } while (tmp_i9 + -2 == -1);
      tmp_u8 = (&weapBanksMultiPlayer)[tmp_i2 + tmp_i9 + -2];
      if ((&weapBanksMultiPlayer)[tmp_i2 + tmp_i9 + -2] != 0) goto LAB_000d7df2;
      tmp_i9 = tmp_i9 + -3;
    } while (tmp_i9 == -1);
LAB_000d7d14:
    tmp_i5 = bnk_12439 * 0xc;
    tmp_u8 = (&weapBanksMultiPlayer)[tmp_i5 + tmp_i9];
    if ((&weapBanksMultiPlayer)[tmp_i5 + tmp_i9] != 0) break;
  }
LAB_000d7df2:
  tmp_u4 = tmp_u8 - 1;
LAB_000d79c0:
  if (0x32 < tmp_u4) goto LAB_000d7b4c;
  bnk_12439 = 0;
  tmp_pu7 = &weapBanksMultiPlayer;
  do {
    cyc_12440 = 0;
    if (*tmp_pu7 != 0) {
      if (tmp_u8 == *tmp_pu7) {
        cyc_12440 = 0;
        local_40 = 0;
        goto LAB_000d7ae0;
      }
      if (tmp_pu7[1] == 0) {
        cyc_12440 = 1;
      }
      else {
        if (tmp_u8 == tmp_pu7[1]) {
          local_40 = 1;
LAB_000d7e80:
          cyc_12440 = local_40;
          goto LAB_000d7ae0;
        }
        if (tmp_pu7[2] == 0) {
          cyc_12440 = 2;
        }
        else {
          if (tmp_u8 == tmp_pu7[2]) {
            local_40 = 2;
            goto LAB_000d7e80;
          }
          if (tmp_pu7[3] == 0) {
            cyc_12440 = 3;
          }
          else {
            if (tmp_u8 == tmp_pu7[3]) {
              local_40 = 3;
              goto LAB_000d7e80;
            }
            if (tmp_pu7[4] == 0) {
              cyc_12440 = 4;
            }
            else {
              if (tmp_u8 == tmp_pu7[4]) {
                local_40 = 4;
                goto LAB_000d7e80;
              }
              if (tmp_pu7[5] == 0) {
                cyc_12440 = 5;
              }
              else {
                if (tmp_u8 == tmp_pu7[5]) {
                  local_40 = 5;
                  goto LAB_000d7e80;
                }
                if (tmp_pu7[6] == 0) {
                  cyc_12440 = 6;
                }
                else {
                  if (tmp_u8 == tmp_pu7[6]) {
                    local_40 = 6;
                    goto LAB_000d7e80;
                  }
                  if (tmp_pu7[7] == 0) {
                    cyc_12440 = 7;
                  }
                  else {
                    if (tmp_u8 == tmp_pu7[7]) {
                      local_40 = 7;
                      goto LAB_000d7e80;
                    }
                    if (tmp_pu7[8] == 0) {
                      cyc_12440 = 8;
                    }
                    else {
                      if (tmp_u8 == tmp_pu7[8]) {
                        local_40 = 8;
                        goto LAB_000d7e80;
                      }
                      if (tmp_pu7[9] == 0) {
                        cyc_12440 = 9;
                      }
                      else {
                        if (tmp_u8 == tmp_pu7[9]) {
                          local_40 = 9;
                          goto LAB_000d7e80;
                        }
                        if (tmp_pu7[10] == 0) {
                          cyc_12440 = 10;
                        }
                        else {
                          if (tmp_u8 == tmp_pu7[10]) {
                            local_40 = 10;
                            goto LAB_000d7e80;
                          }
                          if (tmp_pu7[0xb] == 0) {
                            cyc_12440 = 0xb;
                          }
                          else {
                            if (tmp_u8 == tmp_pu7[0xb]) {
                              local_40 = 0xb;
                              goto LAB_000d7e80;
                            }
                            cyc_12440 = 0xc;
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
    bnk_12439 = bnk_12439 + 1;
    tmp_pu7 = tmp_pu7 + 0xc;
  } while (bnk_12439 != 10);
  bnk_12439 = 10;
LAB_000d7ae0:
  if (param_1 == 0) goto LAB_000d7b5a;
  while (tmp_i6 = GHIDRA_FIELD(cg_cycleAllWeaps, 12, 4), local_40 < local_38) {
    while( true ) {
      if ((tmp_u8 == 0) ||
         ((((_DAT_01090764 & 0x8020) == 0 && (tmp_i6 = COM_BitCheck(&g_unk_01090ad0,tmp_u8), tmp_i6 != 0)
           ) && ((tmp_u8 == 0x14 ||
                 (((tmp_u8 == 1 ||
                   (tmp_i6 = BG_FindAmmoForWeapon(tmp_u8), *(int *)(&g_unk_0109088c + tmp_i6 * 4) != 0))
                  || (tmp_i6 = BG_FindClipForWeapon(tmp_u8), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0)
                  ))))))) goto LAB_000d6ec0;
      if (tmp_u8 == 0x16) {
        if ((((_DAT_01090764 & 0x8020) == 0) &&
            (tmp_i6 = COM_BitCheck(&g_unk_01090ad0,0x24), tmp_i6 != 0)) &&
           ((tmp_i6 = BG_FindAmmoForWeapon(0x24), *(int *)(&g_unk_0109088c + tmp_i6 * 4) != 0 ||
            (tmp_i6 = BG_FindClipForWeapon(0x24), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0))))
        goto LAB_000d6eac;
      }
      else if ((((tmp_u8 == 0x17) && ((_DAT_01090764 & 0x8020) == 0)) &&
               (tmp_i6 = COM_BitCheck(&g_unk_01090ad0,0x25), tmp_i6 != 0)) &&
              ((tmp_i6 = BG_FindAmmoForWeapon(0x25), *(int *)(&g_unk_0109088c + tmp_i6 * 4) != 0 ||
               (tmp_i6 = BG_FindClipForWeapon(0x25), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0))))
      goto LAB_000d76c6;
      local_44 = local_44 - 1;
      if (local_44 == 0xffffffff) goto LAB_000d6ec0;
      if (tmp_u4 < 0x33) goto LAB_000d789d;
LAB_000d7b4c:
      local_40 = 0;
      if (param_1 != 0) break;
LAB_000d7b5a:
      if (local_2c == tmp_u8) {
        return;
      }
    }
  }
  goto LAB_000d7130;
LAB_000d6eac:
  tmp_u8 = 0x24;
  goto LAB_000d6ec0;
LAB_000d7710:
  tmp_u8 = 0;
LAB_000d6ec0:
  CG_FinishWeaponChange(local_2c,tmp_u8);
  return;
}

void CG_LastWeaponUsed_f(void)
{
  uint tmp_u1;
  int tmp_i2;
  
  tmp_u1 = g_unk_010aacf8;
  if ((((*(int *)(g_unk_01047b00 + 0x30) != 4) &&
       ((int)GHIDRA_FIELD(cg_weaponCycleDelay, 12, 4) <= g_unk_010906e0 - g_unk_010aac34)) &&
      ((g_unk_01091814 & 0xfffffffb) != 0x2a)) &&
     (g_unk_010aac34 = g_unk_010906e0, *(int *)(g_unk_01047b00 + 0xd4) != 7)) {
    if (g_unk_010aacf8 == 0) {
      g_unk_010aacf8 = g_unk_01091814;
    }
    else if ((((_DAT_01090764 & 0x8020) == 0) &&
             (tmp_i2 = COM_BitCheck(&g_unk_01090ad0,g_unk_010aacf8), tmp_i2 != 0)) &&
            (((tmp_u1 == 0x14 ||
              ((tmp_u1 == 1 ||
               (tmp_i2 = BG_FindAmmoForWeapon(tmp_u1), *(int *)(&g_unk_0109088c + tmp_i2 * 4) != 0)))) ||
             (tmp_i2 = BG_FindClipForWeapon(tmp_u1), *(int *)(&g_unk_0109098c + tmp_i2 * 4) != 0)))) {
      CG_FinishWeaponChange(g_unk_01091814,g_unk_010aacf8);
    }
    else {
      g_unk_010aacf8 = 0;
    }
  }
  return;
}

void CG_NextWeaponInBank_f(void)
{
  if (*(int *)(g_unk_01047b00 + 0x30) == 4) {
    return;
  }
  if (g_unk_010906e0 - g_unk_010aac34 < (int)GHIDRA_FIELD(cg_weaponCycleDelay, 12, 4)) {
    return;
  }
  if (g_unk_01091a74 != 0.0) {
    if (GHIDRA_FIELD(cg_useWeapsForZoom, 12, 4) == 1) {
      CG_ZoomIn_f();
      return;
    }
    if (GHIDRA_FIELD(cg_useWeapsForZoom, 12, 4) == 2) {
      CG_ZoomOut_f();
      return;
    }
  }
  g_unk_010aac34 = g_unk_010906e0;
  CG_NextWeap(0);
  return;
}

void CG_PrevWeaponInBank_f(void)
{
  if (*(int *)(g_unk_01047b00 + 0x30) == 4) {
    return;
  }
  if (g_unk_010906e0 - g_unk_010aac34 < (int)GHIDRA_FIELD(cg_weaponCycleDelay, 12, 4)) {
    return;
  }
  if (g_unk_01091a74 != 0.0) {
    if (GHIDRA_FIELD(cg_useWeapsForZoom, 12, 4) == 2) {
      CG_ZoomIn_f();
      return;
    }
    if (GHIDRA_FIELD(cg_useWeapsForZoom, 12, 4) == 1) {
      CG_ZoomOut_f();
      return;
    }
  }
  g_unk_010aac34 = g_unk_010906e0;
  CG_PrevWeap(0);
  return;
}

void CG_NextWeapon_f(void)
{
  if (g_unk_01047b00 == 0) {
    return;
  }
  if (*(int *)(g_unk_01047b00 + 0x30) == 4) {
    return;
  }
  if ((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) != 0) {
    return;
  }
  if (g_unk_01091a74 != 0.0) {
    if (GHIDRA_FIELD(cg_useWeapsForZoom, 12, 4) == 1) {
      CG_ZoomIn_f();
      return;
    }
    if (GHIDRA_FIELD(cg_useWeapsForZoom, 12, 4) == 2) {
      CG_ZoomOut_f();
      return;
    }
  }
  if (((int)GHIDRA_FIELD(cg_weaponCycleDelay, 12, 4) <= g_unk_010906e0 - g_unk_010aac34) &&
     (g_unk_010aac34 = g_unk_010906e0, *(int *)(g_unk_01047b00 + 0xd4) != 7)) {
    CG_NextWeap(1);
  }
  return;
}

void CG_PrevWeapon_f(void)
{
  if (g_unk_01047b00 == 0) {
    return;
  }
  if (*(int *)(g_unk_01047b00 + 0x30) == 4) {
    return;
  }
  if ((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) != 0) {
    return;
  }
  if (g_unk_01091a74 != 0.0) {
    if (GHIDRA_FIELD(cg_useWeapsForZoom, 12, 4) == 1) {
      CG_ZoomOut_f();
      return;
    }
    if (GHIDRA_FIELD(cg_useWeapsForZoom, 12, 4) == 2) {
      CG_ZoomIn_f();
      return;
    }
  }
  if (((int)GHIDRA_FIELD(cg_weaponCycleDelay, 12, 4) <= g_unk_010906e0 - g_unk_010aac34) &&
     (g_unk_010aac34 = g_unk_010906e0, *(int *)(g_unk_01047b00 + 0xd4) != 7)) {
    CG_PrevWeap(1);
  }
  return;
}

void CG_OutOfAmmoChange(int param_1)
{
  uint *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  uint tmp_u5;
  int tmp_i6;
  uint32_t tmp_u7;
  int local_2c;
  int local_20;
  
  if (g_unk_01091814 == 0x14) {
    return;
  }
  if (g_unk_01091814 == 0x1b) {
    if (g_unk_010908f8 != 0) {
      return;
    }
    if (param_1 != 0) {
LAB_000d934e:
      tmp_i4 = 0;
      do {
        tmp_i6 = (&g_unk_0013e830)[tmp_i4];
        if (tmp_i6 != 5) {
          if (tmp_i6 == 0) {
            tmp_u7 = 0;
            goto LAB_000d939c;
          }
          if ((((_DAT_01090764 & 0x8020) == 0) &&
              (tmp_i3 = COM_BitCheck(&g_unk_01090ad0,tmp_i6), tmp_i3 != 0)) &&
             ((tmp_i6 == 0x14 ||
              (((tmp_i6 == 1 ||
                (tmp_i3 = BG_FindAmmoForWeapon(tmp_i6), *(int *)(&g_unk_0109088c + tmp_i3 * 4) != 0)) ||
               (tmp_i6 = BG_FindClipForWeapon(tmp_i6), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0))))))
          {
            tmp_u7 = (&weapBanksMultiPlayer)[tmp_i4 + 0x24];
            goto LAB_000d939c;
          }
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 != 0xc);
      tmp_i4 = 0;
      do {
        tmp_i6 = (&g_unk_0013e800)[tmp_i4];
        tmp_u7 = 0;
        if (tmp_i6 == 0) goto LAB_000d939c;
        if ((((_DAT_01090764 & 0x8020) == 0) &&
            (tmp_i3 = COM_BitCheck(&g_unk_01090ad0,tmp_i6), tmp_i3 != 0)) &&
           (((tmp_i6 == 0x14 ||
             ((tmp_i6 == 1 ||
              (tmp_i3 = BG_FindAmmoForWeapon(tmp_i6), *(int *)(&g_unk_0109088c + tmp_i3 * 4) != 0)))) ||
            (tmp_i6 = BG_FindClipForWeapon(tmp_i6), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0)))) {
          tmp_u7 = (&weapBanksMultiPlayer)[tmp_i4 + 0x18];
          goto LAB_000d939c;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 != 0xc);
      tmp_i4 = 0;
      do {
        tmp_i6 = (&g_unk_0013e860)[tmp_i4];
        tmp_u7 = 0;
        if (tmp_i6 == 0) {
LAB_000d939c:
          g_unk_01091814 = tmp_u7;
          CG_FinishWeaponChange(g_unk_010907a0,tmp_u7);
          return;
        }
        if ((((_DAT_01090764 & 0x8020) == 0) &&
            (tmp_i3 = COM_BitCheck(&g_unk_01090ad0,tmp_i6), tmp_i3 != 0)) &&
           ((tmp_i6 == 0x14 ||
            (((tmp_i6 == 1 ||
              (tmp_i3 = BG_FindAmmoForWeapon(tmp_i6), *(int *)(&g_unk_0109088c + tmp_i3 * 4) != 0)) ||
             (tmp_i6 = BG_FindClipForWeapon(tmp_i6), *(int *)(&g_unk_0109098c + tmp_i6 * 4) != 0)))))) {
          tmp_u7 = (&weapBanksMultiPlayer)[tmp_i4 + 0x30];
          goto LAB_000d939c;
        }
        tmp_i4 = tmp_i4 + 1;
      } while (tmp_i4 != 0xc);
      goto LAB_000d9292;
    }
LAB_000d93cc:
    tmp_pu1 = &weapBanksMultiPlayer;
    local_2c = 0;
    do {
      cyc_12440 = 0;
      if (*tmp_pu1 != 0) {
        local_20 = local_2c;
        if (g_unk_01091814 == *tmp_pu1) {
          cyc_12440 = 0;
          tmp_i4 = 0;
          bnk_12439 = local_2c;
          goto LAB_000d92da;
        }
        if (tmp_pu1[1] == 0) {
          cyc_12440 = 1;
        }
        else {
          if (g_unk_01091814 == tmp_pu1[1]) {
            tmp_i4 = 1;
LAB_000d9b30:
            bnk_12439 = local_2c;
            cyc_12440 = tmp_i4;
            goto LAB_000d92da;
          }
          if (tmp_pu1[2] == 0) {
            cyc_12440 = 2;
          }
          else {
            if (g_unk_01091814 == tmp_pu1[2]) {
              tmp_i4 = 2;
              goto LAB_000d9b30;
            }
            if (tmp_pu1[3] == 0) {
              cyc_12440 = 3;
            }
            else {
              if (g_unk_01091814 == tmp_pu1[3]) {
                tmp_i4 = 3;
                goto LAB_000d9b30;
              }
              if (tmp_pu1[4] == 0) {
                cyc_12440 = 4;
              }
              else {
                if (g_unk_01091814 == tmp_pu1[4]) {
                  tmp_i4 = 4;
                  goto LAB_000d9b30;
                }
                if (tmp_pu1[5] == 0) {
                  cyc_12440 = 5;
                }
                else {
                  if (g_unk_01091814 == tmp_pu1[5]) {
                    tmp_i4 = 5;
                    goto LAB_000d9b30;
                  }
                  if (tmp_pu1[6] == 0) {
                    cyc_12440 = 6;
                  }
                  else {
                    if (g_unk_01091814 == tmp_pu1[6]) {
                      tmp_i4 = 6;
                      goto LAB_000d9b30;
                    }
                    if (tmp_pu1[7] == 0) {
                      cyc_12440 = 7;
                    }
                    else {
                      if (g_unk_01091814 == tmp_pu1[7]) {
                        tmp_i4 = 7;
                        goto LAB_000d9b30;
                      }
                      if (tmp_pu1[8] == 0) {
                        cyc_12440 = 8;
                      }
                      else {
                        if (g_unk_01091814 == tmp_pu1[8]) {
                          tmp_i4 = 8;
                          goto LAB_000d9b30;
                        }
                        if (tmp_pu1[9] == 0) {
                          cyc_12440 = 9;
                        }
                        else {
                          if (g_unk_01091814 == tmp_pu1[9]) {
                            tmp_i4 = 9;
                            goto LAB_000d9b30;
                          }
                          if (tmp_pu1[10] == 0) {
                            cyc_12440 = 10;
                          }
                          else {
                            if (g_unk_01091814 == tmp_pu1[10]) {
                              tmp_i4 = 10;
                              goto LAB_000d9b30;
                            }
                            if (tmp_pu1[0xb] == 0) {
                              cyc_12440 = 0xb;
                            }
                            else {
                              if (g_unk_01091814 == tmp_pu1[0xb]) {
                                tmp_i4 = 0xb;
                                goto LAB_000d9b30;
                              }
                              cyc_12440 = 0xc;
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
      local_2c = local_2c + 1;
      tmp_pu1 = tmp_pu1 + 0xc;
    } while (local_2c != 10);
    bnk_12439 = 10;
  }
  else {
    if (param_1 != 0) {
      if ((g_unk_01091814 == 0x32) || (g_unk_01091814 == 0x1c)) {
        if ((_DAT_01090764 & 0x8020) == 0) {
          tmp_i4 = COM_BitCheck(&g_unk_01090ad0,2);
          if ((tmp_i4 != 0) &&
             ((tmp_i4 = BG_FindAmmoForWeapon(2), *(int *)(&g_unk_0109088c + tmp_i4 * 4) != 0 ||
              (tmp_i4 = BG_FindClipForWeapon(2), *(int *)(&g_unk_0109098c + tmp_i4 * 4) != 0)))) {
            g_unk_01091814 = 2;
            CG_FinishWeaponChange(g_unk_010907a0,2);
            return;
          }
          if ((((_DAT_01090764 & 0x8020) == 0) &&
              (tmp_i4 = COM_BitCheck(&g_unk_01090ad0,7), tmp_i4 != 0)) &&
             ((tmp_i4 = BG_FindAmmoForWeapon(7), *(int *)(&g_unk_0109088c + tmp_i4 * 4) != 0 ||
              (tmp_i4 = BG_FindClipForWeapon(7), *(int *)(&g_unk_0109098c + tmp_i4 * 4) != 0)))) {
            g_unk_01091814 = 7;
            CG_FinishWeaponChange(g_unk_010907a0,7);
            return;
          }
        }
      }
      else if ((g_unk_01091814 == 0xf || g_unk_01091814 == 0x19) ||
              ((g_unk_01091814 & 0xfffffffd) == 0x31)) {
        if (((_DAT_01090764 & 0x8020) == 0) &&
           (tmp_i4 = COM_BitCheck(&g_unk_01090ad0,0x14), tmp_i4 != 0)) {
          g_unk_01091814 = 0x14;
          CG_FinishWeaponChange(g_unk_010907a0,0x14);
          return;
        }
      }
      else if (g_unk_01091814 == 0x1a) {
        if ((((_DAT_01090764 & 0x8020) == 0) &&
            (tmp_i4 = COM_BitCheck(&g_unk_01090ad0,0x1b), tmp_i4 != 0)) &&
           ((tmp_i4 = BG_FindAmmoForWeapon(0x1b), *(int *)(&g_unk_0109088c + tmp_i4 * 4) != 0 ||
            (tmp_i4 = BG_FindClipForWeapon(0x1b), *(int *)(&g_unk_0109098c + tmp_i4 * 4) != 0)))) {
          g_unk_01091814 = 0x1b;
          return;
        }
      }
      else {
        if (g_unk_01091814 == 0x2a) {
          g_unk_01091814 = 0x21;
          return;
        }
        if (g_unk_01091814 == 0x2e) {
          g_unk_01091814 = 0x1d;
          return;
        }
      }
      if ((g_unk_01091814 == 0x1b) || (g_unk_01091814 == 5)) goto LAB_000d934e;
LAB_000d9292:
      if (g_unk_01091814 - 0x24 < 3) {
        tmp_u5 = g_unk_01091814;
        if (*(uint *)(weapAlts + g_unk_01091814 * 4) != 0) {
          tmp_u5 = *(uint *)(weapAlts + g_unk_01091814 * 4);
        }
        g_unk_01091814 = tmp_u5;
        if ((((_DAT_01090764 & 0x8020) == 0) &&
            (tmp_i4 = COM_BitCheck(&g_unk_01090ad0,tmp_u5), tmp_i4 != 0)) &&
           (((tmp_u5 == 0x14 ||
             ((tmp_u5 == 1 ||
              (tmp_i4 = BG_FindAmmoForWeapon(tmp_u5), *(int *)(&g_unk_0109088c + tmp_i4 * 4) != 0)))) ||
            (tmp_i4 = BG_FindClipForWeapon(tmp_u5), *(int *)(&g_unk_0109098c + tmp_i4 * 4) != 0)))) {
          CG_FinishWeaponChange(g_unk_010907a0,g_unk_01091814);
          return;
        }
      }
    }
    if (g_unk_01091814 - 1 < 0x33) goto LAB_000d93cc;
  }
  tmp_i4 = 0;
  local_20 = 0;
LAB_000d92da:
  tmp_i6 = 0;
  do {
    tmp_i3 = (&g_unk_0013e830)[tmp_i6];
    if (tmp_i3 == 0) goto LAB_000d9315;
    if ((((_DAT_01090764 & 0x8020) == 0) && (tmp_i2 = COM_BitCheck(&g_unk_01090ad0,tmp_i3), tmp_i2 != 0))
       && ((tmp_i3 == 0x14 ||
           (((tmp_i3 == 1 ||
             (tmp_i2 = BG_FindAmmoForWeapon(tmp_i3), *(int *)(&g_unk_0109088c + tmp_i2 * 4) != 0)) ||
            (tmp_i3 = BG_FindClipForWeapon(tmp_i3), *(int *)(&g_unk_0109098c + tmp_i3 * 4) != 0)))))) {
      tmp_i6 = (&weapBanksMultiPlayer)[tmp_i6 + 0x24];
      goto LAB_000d9317;
    }
    tmp_i6 = tmp_i6 + 1;
  } while (tmp_i6 != 0xc);
  tmp_i6 = 0;
  do {
    tmp_i3 = (&g_unk_0013e800)[tmp_i6];
    if (tmp_i3 == 0) goto LAB_000d9315;
    if ((((_DAT_01090764 & 0x8020) == 0) && (tmp_i2 = COM_BitCheck(&g_unk_01090ad0,tmp_i3), tmp_i2 != 0))
       && (((tmp_i3 == 0x14 ||
            ((tmp_i3 == 1 ||
             (tmp_i2 = BG_FindAmmoForWeapon(tmp_i3), *(int *)(&g_unk_0109088c + tmp_i2 * 4) != 0)))) ||
           (tmp_i3 = BG_FindClipForWeapon(tmp_i3), *(int *)(&g_unk_0109098c + tmp_i3 * 4) != 0)))) {
      tmp_i6 = (&weapBanksMultiPlayer)[tmp_i6 + 0x18];
      goto LAB_000d9317;
    }
    tmp_i6 = tmp_i6 + 1;
  } while (tmp_i6 != 0xc);
  do {
    if (tmp_i4 == 0xc) {
      CG_NextWeap();
      return;
    }
    tmp_i4 = tmp_i4 + 1;
    tmp_i6 = (&weapBanksMultiPlayer)[tmp_i4 % 0xc + local_20 * 0xc];
  } while (((tmp_i6 != 0) || (tmp_i6 = (&weapBanksMultiPlayer)[local_20 * 0xc], tmp_i6 != 0)) &&
          ((((_DAT_01090764 & 0x8020) != 0 ||
            (tmp_i3 = COM_BitCheck(&g_unk_01090ad0,tmp_i6), tmp_i3 == 0)) ||
           ((((tmp_i6 != 0x14 && (tmp_i6 != 1)) &&
             (tmp_i3 = BG_FindAmmoForWeapon(tmp_i6), *(int *)(&g_unk_0109088c + tmp_i3 * 4) == 0)) &&
            (tmp_i3 = BG_FindClipForWeapon(tmp_i6), *(int *)(&g_unk_0109098c + tmp_i3 * 4) == 0))))));
LAB_000d9317:
  g_unk_01091814 = tmp_i6;
  CG_FinishWeaponChange(g_unk_010907a0,tmp_i6);
  return;
LAB_000d9315:
  tmp_i6 = 0;
  goto LAB_000d9317;
}

void CG_MG42EFX(int *param_1)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int *tmp_pi4;
  uint tmp_u5;
  int tmp_i6;
  int tmp_i7;
  float local_114;
  float local_110;
  float local_10c;
  uint32_t local_108 [7];
  uint8_t local_ec [76];
  float local_a0;
  float local_9c;
  float local_98;
  uint32_t uStack_14;
  
  uStack_14 = 0xd9d09;
  if (0 < *(int *)(g_unk_01047b00 + 0x5d8)) {
    tmp_pi4 = (int *)(g_unk_01047b00 + 0x5dc);
    tmp_i7 = 0;
    do {
      tmp_i6 = *tmp_pi4 * 0xaf8;
      if ((*(int *)(cg_entities + tmp_i6 + 4) == 0x29) &&
         (*(int *)(cg_entities + tmp_i6 + 0x8c) == *param_1)) {
        tmp_f1 = *(float *)(cg_entities + tmp_i6 + 0x18);
        tmp_f2 = *(float *)(cg_entities + tmp_i6 + 0x1c);
        tmp_f3 = *(float *)(cg_entities + tmp_i6 + 0x20);
        AngleVectors(param_1 + 0x1e8,&local_114,0,0);
        tmp_u5 = 0;
        do {
          *(uint32_t *)((int)local_108 + tmp_u5) = 0;
          *(uint32_t *)((int)local_108 + tmp_u5 + 4) = 0;
          tmp_u5 = tmp_u5 + 8;
        } while (tmp_u5 < 0xe8);
        *(uint32_t *)((int)local_108 + tmp_u5) = 0;
        local_108[1] = 0x20;
        local_108[2] = GHIDRA_FIELD(cgs, 68816, 4);
        local_a0 = tmp_f1 + local_114 * 40.0;
        local_9c = local_110 * 40.0 + tmp_f2;
        local_98 = local_10c * 40.0 + tmp_f3;
        AnglesToAxis(param_1 + 0x1e8,local_ec);
        trap_R_AddRefEntityToScene(local_108);
        rand();
        trap_R_AddLightToScene(&local_a0,0x43a00000,0x3fa00000,0x3f800000,0x3f19999a,0x3e6b851f,0,0)
        ;
        return;
      }
      tmp_i7 = tmp_i7 + 1;
      tmp_pi4 = tmp_pi4 + 0x48;
    } while (tmp_i7 != *(int *)(g_unk_01047b00 + 0x5d8));
  }
  return;
}

void CG_MortarEFX(int param_1)
{
  uint tmp_u1;
  uint32_t local_f8 [7];
  uint8_t local_dc [76];
  uint32_t local_90;
  uint32_t local_8c;
  uint32_t local_88;
  
  tmp_u1 = *(uint *)(param_1 + 0xf4);
  if (((tmp_u1 & 1) != 0) && (GHIDRA_FIELD(cg_smokeparticles, 12, 4) != 0)) {
    CG_ParticleImpactSmokePuff(GHIDRA_FIELD(cgs, 68088, 4),param_1 + 0x5c);
    tmp_u1 = *(uint *)(param_1 + 0xf4);
  }
  if ((tmp_u1 & 2) != 0) {
    tmp_u1 = rand();
    trap_R_AddLightToScene
              (param_1 + 0x5c,0x43800000,8.0 / (float)(tmp_u1 & 0x1f) + 0.75,0x3f800000,0x3f800000,
               0x3f800000,0,0);
    tmp_u1 = 0;
    do {
      *(uint32_t *)((int)local_f8 + tmp_u1) = 0;
      *(uint32_t *)((int)local_f8 + tmp_u1 + 4) = 0;
      tmp_u1 = tmp_u1 + 8;
    } while (tmp_u1 < 0xe8);
    *(uint32_t *)((int)local_f8 + tmp_u1) = 0;
    local_90 = *(uint32_t *)(param_1 + 0x5c);
    local_f8[1] = 0x20;
    local_8c = *(uint32_t *)(param_1 + 0x60);
    local_f8[2] = GHIDRA_FIELD(cgs, 68816, 4);
    local_88 = *(uint32_t *)(param_1 + 100);
    AnglesToAxis(&g_unk_01091a54,local_dc);
    trap_R_AddRefEntityToScene(local_f8);
  }
  return;
}

void CG_SpawnTracer(int param_1,float *param_2,float *param_3)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  long double tmp_l5;
  long double tmp_l6;
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
  
  local_64 = *param_2;
  local_60 = param_2[1];
  local_5c = param_2[2];
  local_58 = *param_3;
  local_54 = param_3[1];
  local_50 = param_3[2];
  if ((cg_entities[param_1 * 0xaf8 + 8] & 0x20) != 0) {
    local_5c = local_5c - 42.0;
  }
  local_7c = local_58 - local_64;
  local_78 = local_54 - local_60;
  local_74 = local_50 - local_5c;
  tmp_l5 = (long double)VectorNormalize(&local_7c);
  tmp_l6 = (long double)(float)GHIDRA_FIELD(cg_tracerLength, 8, 4);
  if (tmp_l6 + tmp_l6 <= tmp_l5) {
    if ((param_1 < (int)GHIDRA_FIELD(cgs, 27400, 4)) && ((cg_entities[param_1 * 0xaf8 + 8] & 0x20) == 0)) {
      tmp_i4 = CG_GetWeaponTag(param_1,"tag_flash",&local_4c);
      if (tmp_i4 != 0) {
        local_70 = local_4c - local_64;
        local_6c = local_48 - local_60;
        local_68 = local_44 - local_5c;
        tmp_l5 = (long double)VectorLength(&local_70);
        if (tmp_l5 < (long double)64.0) {
          local_64 = local_64 + local_70;
          local_60 = local_60 + local_6c;
          local_5c = local_5c + local_68;
        }
      }
      tmp_l6 = (long double)(float)GHIDRA_FIELD(cg_tracerLength, 8, 4);
    }
    tmp_l6 = -tmp_l6;
    local_58 = (float)((long double)local_7c * tmp_l6 + (long double)local_58);
    local_54 = (float)((long double)local_78 * tmp_l6 + (long double)local_54);
    local_50 = (float)(tmp_l6 * (long double)local_74 + (long double)local_50);
    tmp_l5 = (long double)VectorDistance(&local_64,&local_58);
    tmp_i2 = CG_AllocLocalEntity();
    *(uint32_t *)(tmp_i2 + 8) = 0xd;
    tmp_i3 = g_unk_010906e0;
    tmp_i4 = 0;
    if (g_unk_010906dc != 0) {
      tmp_i4 = rand();
      tmp_i4 = (tmp_i4 % g_unk_010906dc) / 2;
    }
    tmp_i3 = tmp_i3 - tmp_i4;
    *(int *)(tmp_i2 + 0x10) = tmp_i3;
    tmp_u1 = GHIDRA_FIELD(cg_tracerSpeed, 8, 4);
    *(int *)(tmp_i2 + 0x14) =
         (int)ROUND(((float)tmp_l5 * 1000.0) / (float)GHIDRA_FIELD(cg_tracerSpeed, 8, 4) + (float)tmp_i3);
    *(uint32_t *)(tmp_i2 + 0x20) = 2;
    *(int *)(tmp_i2 + 0x24) = tmp_i3;
    *(float *)(tmp_i2 + 0x2c) = local_64;
    *(float *)(tmp_i2 + 0x30) = local_60;
    *(float *)(tmp_i2 + 0x34) = local_5c;
    *(float *)(tmp_i2 + 0x38) = local_7c * (float)tmp_u1;
    *(float *)(tmp_i2 + 0x3c) = local_78 * (float)tmp_u1;
    *(float *)(tmp_i2 + 0x40) = (float)tmp_u1 * local_74;
  }
  return;
}

uint32_t CG_CalcMuzzlePoint(int param_1,float *param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  int tmp_i4;
  float local_68;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  uint8_t local_40 [12];
  uint8_t local_34 [12];
  float local_28;
  float local_24;
  float local_20;
  
  if (*(int *)(g_unk_01047b00 + 0xcc) == param_1) {
    if ((*(uint *)(g_unk_01047b00 + 0x94) & 0x20) != 0) {
      tmp_i4 = *(int *)(g_unk_01047b00 + 0x440) * 0xaf8;
      AngleVectors(g_unk_01047b00 + 0xdc,&local_28,0,0);
      *param_2 = local_28 * 40.0 + *(float *)(cg_entities + tmp_i4 + 0x18);
      param_2[1] = local_24 * 40.0 + *(float *)(cg_entities + tmp_i4 + 0x1c);
      tmp_f1 = local_20 * 40.0 + *(float *)(cg_entities + tmp_i4 + 0x20);
      param_2[2] = tmp_f1;
      param_2[2] = (float)*(int *)(g_unk_01047b00 + 0xe8) + tmp_f1;
      return 1;
    }
    if ((*(uint *)(g_unk_01047b00 + 0x94) & 0x8000) != 0) {
      if (g_unk_010906f4 != 0) {
        tmp_i4 = *(int *)(cg_entities + *(int *)(g_unk_01047b00 + 0xcc) * 0xaf8 + 0xab4) * 0xaf8;
        *param_2 = *(float *)(cg_entities + tmp_i4 + 0xa80);
        param_2[1] = *(float *)(cg_entities + tmp_i4 + 0xa84);
        param_2[2] = *(float *)(cg_entities + tmp_i4 + 0xa88);
        AngleVectors(g_unk_01047b00 + 0xdc,&local_58,0,0);
        *param_2 = local_58 * 14.0 + *param_2;
        param_2[1] = local_54 * 14.0 + param_2[1];
        param_2[2] = local_50 * 14.0 + param_2[2];
        return 1;
      }
      if (GHIDRA_FIELD(cg_drawGun, 12, 4) != 0) {
        *param_2 = g_unk_010b4548;
        param_2[1] = g_unk_010b454c;
        param_2[2] = g_unk_010b4550;
        return 1;
      }
      *param_2 = *(float *)(g_unk_01047b00 + 0x40);
      param_2[1] = *(float *)(g_unk_01047b00 + 0x44);
      param_2[2] = *(float *)(g_unk_01047b00 + 0x48);
      AngleVectors(g_unk_01047b00 + 0xdc,&local_58,&local_4c,local_40);
      tmp_f3 = local_58 * 48.0 + *param_2;
      *param_2 = tmp_f3;
      tmp_f2 = local_54 * 48.0 + param_2[1];
      param_2[1] = tmp_f2;
      tmp_f1 = local_50 * 48.0 + param_2[2];
      param_2[2] = tmp_f1;
      tmp_i4 = *(int *)(g_unk_01047b00 + 0xe8);
      *param_2 = local_4c * 8.0 + tmp_f3;
      param_2[1] = local_48 * 8.0 + tmp_f2;
      param_2[2] = local_44 * 8.0 + (float)tmp_i4 + tmp_f1;
      return 1;
    }
    *param_2 = *(float *)(g_unk_01047b00 + 0x40);
    param_2[1] = *(float *)(g_unk_01047b00 + 0x44);
    tmp_f1 = *(float *)(g_unk_01047b00 + 0x48);
    param_2[2] = tmp_f1;
    param_2[2] = (float)*(int *)(g_unk_01047b00 + 0xe8) + tmp_f1;
    AngleVectors(g_unk_01047b00 + 0xdc,&local_58,0,0);
    if (*(int *)(g_unk_01047b00 + 0xd0) == 0x2e) {
      tmp_f1 = 36.0;
    }
    else {
      tmp_f1 = 14.0;
    }
    *param_2 = local_58 * tmp_f1 + *param_2;
    param_2[1] = local_54 * tmp_f1 + param_2[1];
    param_2[2] = tmp_f1 * local_50 + param_2[2];
    local_68 = *(float *)(g_unk_01047b00 + 0x68);
    if (local_68 == 0.0) {
      return 1;
    }
    tmp_i4 = g_unk_01047b00 + 0xdc;
  }
  else {
    tmp_i4 = param_1 * 0xaf8;
    if ((*(uint *)(cg_entities + tmp_i4 + 8) & 0x20) != 0) {
      if (*(int *)(cg_entities + tmp_i4 + 4) != 0x29) {
        return 1;
      }
      *param_2 = *(float *)(cg_entities + tmp_i4 + 0x18);
      param_2[1] = *(float *)(cg_entities + tmp_i4 + 0x1c);
      param_2[2] = *(float *)(cg_entities + tmp_i4 + 0x20);
      AngleVectors(tmp_i4 + 0x31345e0,&local_28,0,0);
      *param_2 = local_28 * 40.0 + *param_2;
      param_2[1] = local_24 * 40.0 + param_2[1];
      param_2[2] = local_20 * 40.0 + param_2[2] + 40.0;
      return 1;
    }
    if ((*(uint *)(cg_entities + tmp_i4 + 8) & 0x8000) != 0) {
      tmp_i4 = *(int *)(cg_entities + tmp_i4 + 0xab4) * 0xaf8;
      *param_2 = *(float *)(cg_entities + tmp_i4 + 0xa80);
      param_2[1] = *(float *)(cg_entities + tmp_i4 + 0xa84);
      param_2[2] = *(float *)(cg_entities + tmp_i4 + 0xa88);
      return 1;
    }
    *param_2 = *(float *)(cg_entities + tmp_i4 + 0x18);
    param_2[1] = *(float *)(cg_entities + tmp_i4 + 0x1c);
    param_2[2] = *(float *)(cg_entities + tmp_i4 + 0x20);
    AngleVectors(tmp_i4 + 0x3133e7c,&local_58,&local_4c,local_40);
    if ((cg_entities[tmp_i4 + 10] & 8) != 0) {
      tmp_f1 = param_2[2];
      param_2[2] = tmp_f1 - 8.0;
      if (*(int *)(cg_entities + tmp_i4 + 0xe8) == 0x2e) {
        tmp_f2 = 36.0;
      }
      else {
        tmp_f2 = 14.0;
      }
      *param_2 = local_58 * tmp_f2 + *param_2;
      param_2[1] = local_54 * tmp_f2 + param_2[1];
      param_2[2] = tmp_f2 * local_50 + (tmp_f1 - 8.0);
      return 1;
    }
    *param_2 = local_58 * 14.0 + *param_2;
    param_2[1] = local_54 * 14.0 + param_2[1];
    param_2[2] = local_50 * 14.0 + param_2[2] + 40.0;
    local_68 = *(float *)(cg_entities + tmp_i4 + 0x750);
    if (local_68 == 0.0) {
      return 1;
    }
    tmp_i4 = param_1 * 0xaf8 + 0x31345e0;
  }
  AngleVectors(tmp_i4,local_34,&local_28,0);
  *param_2 = local_28 * local_68 + *param_2;
  param_2[1] = local_24 * local_68 + param_2[1];
  param_2[2] = (local_20 * local_68 + param_2[2]) - ABS(local_68 / 3.5);
  return 1;
}

void CG_createStatsWindow(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  int tmp_i3;
  
  if (g_unk_010afc14 == 10) {
LAB_000e3b8a:
    g_unk_010afbdc = (uint8_t *)0x0;
  }
  else {
    if (g_unk_010afc70 == 0) {
      tmp_i3 = 0;
    }
    else if (g_unk_010afee8 == 0) {
      tmp_i3 = 1;
    }
    else if (g_unk_010b0160 == 0) {
      tmp_i3 = 2;
    }
    else if (g_unk_010b03d8 == 0) {
      tmp_i3 = 3;
    }
    else if (g_unk_010b0650 == 0) {
      tmp_i3 = 4;
    }
    else if (g_unk_010b08c8 == 0) {
      tmp_i3 = 5;
    }
    else if (g_unk_010b0b40 == 0) {
      tmp_i3 = 6;
    }
    else if (g_unk_010b0db8 == 0) {
      tmp_i3 = 7;
    }
    else if (g_unk_010b1030 == 0) {
      tmp_i3 = 8;
    }
    else {
      tmp_i3 = 9;
      if (g_unk_010b12a8 != 0) goto LAB_000e3b8a;
    }
    tmp_i2 = tmp_i3 * 0x278;
    (&g_unk_010afc4c)[tmp_i3 * 0x9e] = 0x15;
    (&g_unk_010afc5c)[tmp_i3 * 0x9e] = 0x3e800000;
    (&g_unk_010afc60)[tmp_i3 * 0x9e] = 0x3e800000;
    (&g_unk_010afc54)[tmp_i3 * 0x9e] = 1000;
    *(uint32_t *)(&g_unk_010afc50 + tmp_i2) = 500;
    (&g_unk_010afc70)[tmp_i3 * 0x9e] = 1;
    *(uint32_t *)(tmp_i2 + 0x10afc6c) = 0;
    *(uint32_t *)(&g_unk_010afc74 + tmp_i2) = 0;
    *(uint32_t *)(&g_unk_010afe7c + tmp_i2) = 1;
    *(uint32_t *)(&g_unk_010afe78 + tmp_i2) = 0x6e;
    tmp_u1 = trap_Milliseconds();
    *(uint32_t *)(&g_unk_010afe80 + tmp_i2) = tmp_u1;
    *(uint32_t *)(&g_unk_010afe88 + tmp_i2) = 0;
    *(uint32_t *)(&g_unk_010afe8c + tmp_i2) = 0;
    *(uint32_t *)(&g_unk_010afc18 + tmp_i2) = 0x3f000000;
    *(uint32_t *)(&g_unk_010afc1c + tmp_i2) = 0x3eb33333;
    *(uint32_t *)(&g_unk_010afc20 + tmp_i2) = 0x3e800000;
    *(uint32_t *)(&g_unk_010afc24 + tmp_i2) = 0x3f000000;
    *(uint32_t *)(&g_unk_010afc28 + tmp_i2) = 0x3e99999a;
    *(uint32_t *)(&g_unk_010afc2c + tmp_i2) = 0x3ee66666;
    *(uint32_t *)(&g_unk_010afc30 + tmp_i2) = 0x3e99999a;
    *(uint32_t *)(&g_unk_010afc34 + tmp_i2) = 0x3f000000;
    g_unk_010afbdc = &g_unk_010afc18 + tmp_i2;
    (&g_unk_010afbec)[g_unk_010afc14] = tmp_i3;
    *(uint32_t *)(tmp_i2 + 0x10afc6c) = 1;
    g_unk_010afc14 = g_unk_010afc14 + 1;
    (&g_unk_010afc5c)[tmp_i3 * 0x9e] = 0x3e4ccccd;
    (&g_unk_010afc60)[tmp_i3 * 0x9e] = 0x3e4ccccd;
    tmp_i2 = g_unk_01047b00;
    if (*(int *)(g_unk_01047b00 + 0x30) == 5) {
      tmp_u1 = 0x41200000;
    }
    else {
      tmp_u1 = 0x40800000;
    }
    *(uint32_t *)(&g_unk_010afe88 + tmp_i3 * 0x278) = tmp_u1;
    if (*(int *)(tmp_i2 + 0x30) == 5) {
      tmp_u1 = 0xc1a00000;
    }
    else {
      tmp_u1 = 0xc2c80000;
    }
    *(uint32_t *)(&g_unk_010afe8c + tmp_i3 * 0x278) = tmp_u1;
  }
  return;
}

void CG_windowInit(void)
{
  g_unk_010afc14 = 0;
  g_unk_010afc70 = 0;
  g_unk_010afee8 = 0;
  g_unk_010b0160 = 0;
  g_unk_010b03d8 = 0;
  g_unk_010b0650 = 0;
  g_unk_010b08c8 = 0;
  g_unk_010b0b40 = 0;
  g_unk_010b0db8 = 0;
  g_unk_010b1030 = 0;
  g_unk_010b12a8 = 0;
  g_unk_010afbdc = 0;
  g_unk_010afbe4 = 0;
  return;
}

void CG_windowReset(uint32_t *param_1,int param_2,int param_3)
{
  uint32_t tmp_u1;
  
  param_1[0xd] = param_2;
  param_1[0x99] = (uint)(0xf < param_2);
  if (param_3 < 0) {
    param_3 = 0;
  }
  param_1[0xf] = 1000;
  param_1[0x11] = 0x3e800000;
  param_1[0x12] = 0x3e800000;
  param_1[0xe] = 500;
  param_1[0x15] = 0;
  param_1[0x16] = 1;
  param_1[0x17] = 0;
  param_1[0x98] = param_3;
  tmp_u1 = trap_Milliseconds();
  param_1[4] = 0x3e99999a;
  param_1[0x9a] = tmp_u1;
  param_1[5] = 0x3ee66666;
  param_1[0x9c] = 0;
  param_1[0x9d] = 0;
  *param_1 = 0x3f000000;
  param_1[6] = 0x3e99999a;
  param_1[1] = 0x3eb33333;
  param_1[7] = 0x3f000000;
  param_1[2] = 0x3e800000;
  param_1[3] = 0x3f000000;
  return;
}

uint8_t * CG_windowAlloc(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  int local_48;
  
  if (g_unk_010afc14 == 10) {
    tmp_pu3 = (uint8_t *)0x0;
  }
  else {
    if (g_unk_010afc70 == 0) {
      local_48 = 0;
    }
    else if (g_unk_010afee8 == 0) {
      local_48 = 1;
    }
    else if (g_unk_010b0160 == 0) {
      local_48 = 2;
    }
    else if (g_unk_010b03d8 == 0) {
      local_48 = 3;
    }
    else if (g_unk_010b0650 == 0) {
      local_48 = 4;
    }
    else if (g_unk_010b08c8 == 0) {
      local_48 = 5;
    }
    else if (g_unk_010b0b40 == 0) {
      local_48 = 6;
    }
    else if (g_unk_010b0db8 == 0) {
      local_48 = 7;
    }
    else if (g_unk_010b1030 == 0) {
      local_48 = 8;
    }
    else {
      if (g_unk_010b12a8 != 0) {
        return (uint8_t *)0x0;
      }
      local_48 = 9;
    }
    tmp_i4 = local_48 * 0x278;
    (&g_unk_010afc4c)[local_48 * 0x9e] = param_1;
    (&g_unk_010afc5c)[local_48 * 0x9e] = 0x3e800000;
    tmp_pu3 = &g_unk_010afc18 + tmp_i4;
    (&g_unk_010afc60)[local_48 * 0x9e] = 0x3e800000;
    (&g_unk_010afc54)[local_48 * 0x9e] = 1000;
    *(uint32_t *)(&g_unk_010afc50 + tmp_i4) = 500;
    *(uint32_t *)(tmp_i4 + 0x10afc6c) = 0;
    (&g_unk_010afc70)[local_48 * 0x9e] = 1;
    *(uint32_t *)(&g_unk_010afc74 + tmp_i4) = 0;
    *(uint *)(&g_unk_010afe7c + tmp_i4) = (uint)(0xf < param_1);
    tmp_i1 = 0;
    if (-1 < param_2) {
      tmp_i1 = param_2;
    }
    *(int *)(&g_unk_010afe78 + tmp_i4) = tmp_i1;
    tmp_u2 = trap_Milliseconds();
    *(uint32_t *)(&g_unk_010afe80 + tmp_i4) = tmp_u2;
    *(uint32_t *)(&g_unk_010afe88 + tmp_i4) = 0;
    *(uint32_t *)(&g_unk_010afe8c + tmp_i4) = 0;
    *(uint32_t *)(&g_unk_010afc18 + tmp_i4) = 0x3f000000;
    *(uint32_t *)(&g_unk_010afc1c + tmp_i4) = 0x3eb33333;
    *(uint32_t *)(&g_unk_010afc20 + tmp_i4) = 0x3e800000;
    *(uint32_t *)(&g_unk_010afc24 + tmp_i4) = 0x3f000000;
    *(uint32_t *)(&g_unk_010afc28 + tmp_i4) = 0x3e99999a;
    *(uint32_t *)(&g_unk_010afc2c + tmp_i4) = 0x3ee66666;
    *(uint32_t *)(&g_unk_010afc30 + tmp_i4) = 0x3e99999a;
    *(uint32_t *)(&g_unk_010afc34 + tmp_i4) = 0x3f000000;
    (&g_unk_010afbec)[g_unk_010afc14] = local_48;
    g_unk_010afc14 = g_unk_010afc14 + 1;
  }
  return tmp_pu3;
}

void CG_windowFree(uint8_t *param_1)
{
  uint32_t tmp_u1;
  uint8_t *tmp_pu2;
  size_t __n;
  int tmp_i3;
  int tmp_i4;
  
  if (param_1 != (uint8_t *)0x0) {
    if (((*(int *)(param_1 + 0x34) < 0x10) || (*(int *)(param_1 + 0x264) == 4)) ||
       (*(int *)(param_1 + 0x58) != 1)) {
      if (0 < g_unk_010afc14) {
        if (param_1 == &g_unk_010afc18 + g_unk_010afbec * 0x278) {
          tmp_i4 = 0;
        }
        else {
          if (g_unk_010afc14 == 1) {
            return;
          }
          if (param_1 == &g_unk_010afc18 + g_unk_010afbf0 * 0x278) {
            tmp_i4 = 1;
          }
          else {
            if (g_unk_010afc14 == 2) {
              return;
            }
            if (param_1 == &g_unk_010afc18 + g_unk_010afbf4 * 0x278) {
              tmp_i4 = 2;
            }
            else {
              if (g_unk_010afc14 == 3) {
                return;
              }
              if (param_1 == &g_unk_010afc18 + g_unk_010afbf8 * 0x278) {
                tmp_i4 = 3;
              }
              else {
                if (g_unk_010afc14 == 4) {
                  return;
                }
                if (param_1 == &g_unk_010afc18 + g_unk_010afbfc * 0x278) {
                  tmp_i4 = 4;
                }
                else {
                  if (g_unk_010afc14 == 5) {
                    return;
                  }
                  if (param_1 == &g_unk_010afc18 + g_unk_010afc00 * 0x278) {
                    tmp_i4 = 5;
                  }
                  else {
                    if (g_unk_010afc14 == 6) {
                      return;
                    }
                    if (param_1 == &g_unk_010afc18 + g_unk_010afc04 * 0x278) {
                      tmp_i4 = 6;
                    }
                    else {
                      if (g_unk_010afc14 == 7) {
                        return;
                      }
                      if (param_1 == &g_unk_010afc18 + g_unk_010afc08 * 0x278) {
                        tmp_i4 = 7;
                      }
                      else {
                        if (g_unk_010afc14 == 8) {
                          return;
                        }
                        if (param_1 == &g_unk_010afc18 + g_unk_010afc0c * 0x278) {
                          tmp_i4 = 8;
                        }
                        else {
                          if (g_unk_010afc14 == 9) {
                            return;
                          }
                          if (param_1 != &g_unk_010afc18 + g_unk_010afc10 * 0x278) {
                            return;
                          }
                          tmp_i4 = 9;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        __n = (g_unk_010afc14 - tmp_i4) * 4 - 4;
        if (g_unk_010afc14 <= tmp_i4) {
          __n = 0;
        }
        memmove(&g_unk_010afbec + tmp_i4,&g_unk_010afbf0 + tmp_i4,__n);
        *(uint32_t *)(param_1 + 0x54) = 0;
        *(uint32_t *)(param_1 + 0x58) = 0;
        *(uint32_t *)(param_1 + 0x264) = 4;
        if (0 < *(int *)(param_1 + 0x5c)) {
          tmp_i4 = 0;
          do {
            tmp_pu2 = &g_unk_010ad28c;
            tmp_i3 = 0;
            do {
              if ((*(int *)(tmp_pu2 + -4) != 0) &&
                 (*(uint8_t **)(param_1 + tmp_i4 * 4 + 0x160) == tmp_pu2)) {
                *(uint32_t *)(param_1 + tmp_i4 * 4 + 0x160) = 0;
                (&g_unk_010ad288)[tmp_i3 * 0x21] = 0;
                (&g_unk_010ad28c)[tmp_i3 * 0x84] = 0;
                break;
              }
              tmp_i3 = tmp_i3 + 1;
              tmp_pu2 = tmp_pu2 + 0x84;
            } while (tmp_i3 != 0x50);
            tmp_i4 = tmp_i4 + 1;
          } while (tmp_i4 < *(int *)(param_1 + 0x5c));
        }
        g_unk_010afc14 = g_unk_010afc14 + -1;
        return;
      }
    }
    else {
      *(uint32_t *)(param_1 + 0x264) = 2;
      tmp_u1 = trap_Milliseconds();
      *(uint32_t *)(param_1 + 0x268) = tmp_u1;
    }
  }
  return;
}

void CG_windowCleanup(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_i3 = 0;
  tmp_i2 = g_unk_010afc14;
  if (0 < g_unk_010afc14) {
    do {
      while( true ) {
        tmp_i1 = (&g_unk_010afbec)[tmp_i3];
        if (((&g_unk_010afc70)[tmp_i1 * 0x9e] != 0) && (*(int *)(&g_unk_010afe7c + tmp_i1 * 0x278) != 4))
        break;
        CG_windowFree(&g_unk_010afc18 + tmp_i1 * 0x278);
        tmp_i2 = g_unk_010afc14;
        if (g_unk_010afc14 <= tmp_i3) {
          return;
        }
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 < tmp_i2);
  }
  return;
}

void CG_demoAviFPSDraw(void)
{
  char *tmp_pc1;
  
  if (((((GHIDRA_FIELD(cgs, 33599436, 4) != 0 || GHIDRA_FIELD(cgs, 33599432, 4) != 0) || GHIDRA_FIELD(cgs, 33599440, 4) != 0) ||
       GHIDRA_FIELD(cgs, 33599444, 4) != 0) || GHIDRA_FIELD(cgs, 33599448, 4) != 0) && (g_unk_01047aec != 0)) {
    if (-1 < (int)GHIDRA_FIELD(cgs, 33575984, 4)) {
      if (GHIDRA_FIELD(cgs, 33575984, 4) == 0) {
        tmp_pc1 = "^1Stop AVI Recording";
      }
      else {
        tmp_pc1 = (char *)va("^3Record AVI @ ^7%d^2fps",GHIDRA_FIELD(cgs, 33575984, 4));
      }
      CG_DrawStringExt(0x2a,0x1a9,tmp_pc1,&colorWhite,0,0,8,0xe,0);
    }
  }
  return;
}

void CG_demoTimescaleDraw(void)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int tmp_i3;
  
  if (((g_unk_01047aec != 0) && (g_unk_010906e0 < (int)GHIDRA_FIELD(cgs, 33599876, 4))) &&
     (GHIDRA_FIELD(demo_drawTimeScale, 12, 4) != 0)) {
    tmp_u2 = va("^3TimeScale: ^7%.1f",(double)(float)GHIDRA_FIELD(cg_timescale, 8, 4));
    tmp_i3 = CG_DrawStrlen(tmp_u2);
    tmp_f1 = (float)(tmp_i3 * 8 + 5);
    CG_FillRect(0x42200000,0x43c80000,tmp_f1,0x41980000,colorDkGreen);
    CG_DrawRect(0x42200000,0x43c80000,tmp_f1,0x41980000,0x3f800000,colorMdYellow);
    CG_DrawStringExt(0x2a,400,tmp_u2,&colorWhite,0,1,8,0x10,0);
    return;
  }
  return;
}

void CG_windowNormalizeOnText(int param_1)
{
  float tmp_f1;
  float tmp_f2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int *tmp_pi6;
  int local_24;
  
  if (param_1 != 0) {
    tmp_u3 = *(uint *)(param_1 + 0x34);
    *(uint32_t *)(param_1 + 0x26c) = 0;
    *(uint32_t *)(param_1 + 0x50) = 0;
    if ((tmp_u3 & 4) == 0) {
      *(int *)(param_1 + 0x4c) = (int)ROUND(*(float *)(param_1 + 0x44) * 8.0);
      *(int *)(param_1 + 0x40) = (int)ROUND(*(float *)(param_1 + 0x48) * 8.0);
    }
    if (*(int *)(param_1 + 0x5c) < 1) {
      tmp_f2 = 3.0;
      tmp_f1 = 10.0;
    }
    else {
      tmp_i5 = 0;
      while( true ) {
        if ((tmp_u3 & 4) == 0) {
          local_24 = CG_DrawStrlen(*(uint32_t *)(param_1 + 0x160 + tmp_i5 * 4));
          local_24 = local_24 * *(int *)(param_1 + 0x4c);
        }
        else {
          local_24 = CG_Text_Width_Ext(*(uint32_t *)(param_1 + 0x160 + tmp_i5 * 4),
                                       *(uint32_t *)(param_1 + 0x44),0,0x110afec);
        }
        tmp_f2 = (float)local_24;
        tmp_f1 = *(float *)(param_1 + 0x26c);
        if (tmp_f1 < tmp_f2) {
          *(float *)(param_1 + 0x26c) = tmp_f2;
          tmp_f1 = tmp_f2;
        }
        tmp_i5 = tmp_i5 + 1;
        if (*(int *)(param_1 + 0x5c) <= tmp_i5) break;
        tmp_u3 = *(uint *)(param_1 + 0x34);
      }
      if (*(int *)(param_1 + 0x5c) < 1) {
        tmp_f1 = tmp_f1 + 10.0;
        tmp_f2 = *(float *)(param_1 + 0x50) + 3.0;
      }
      else {
        tmp_pi6 = (int *)(param_1 + 0x60);
        tmp_i5 = 0;
        do {
          if ((*(byte *)(param_1 + 0x34) & 4) == 0) {
            tmp_i4 = *(int *)(param_1 + 0x40);
            *tmp_pi6 = tmp_i4;
          }
          else {
            tmp_i4 = CG_Text_Height_Ext(tmp_pi6[0x40],*(uint32_t *)(param_1 + 0x48),0,0x110afec);
            *tmp_pi6 = tmp_i4;
          }
          tmp_i5 = tmp_i5 + 1;
          tmp_pi6 = tmp_pi6 + 1;
          tmp_f2 = (float)(tmp_i4 + 3) + *(float *)(param_1 + 0x50);
          *(float *)(param_1 + 0x50) = tmp_f2;
        } while (tmp_i5 < *(int *)(param_1 + 0x5c));
        tmp_f1 = *(float *)(param_1 + 0x26c) + 10.0;
        tmp_f2 = tmp_f2 + 3.0;
      }
    }
    *(float *)(param_1 + 0x26c) = tmp_f1;
    *(float *)(param_1 + 0x50) = tmp_f2;
    if (*(float *)(param_1 + 0x270) < 0.0) {
      *(float *)(param_1 + 0x270) = (640.0 - tmp_f1) + *(float *)(param_1 + 0x270);
    }
    if (*(float *)(param_1 + 0x274) < 0.0) {
      *(float *)(param_1 + 0x274) = (480.0 - tmp_f2) + *(float *)(param_1 + 0x274);
    }
  }
  return;
}

void CG_windowDraw(void)
{
  float tmp_f1;
  int tmp_i2;
  float tmp_f3;
  bool tmp_b4;
  int tmp_i5;
  int tmp_i6;
  int tmp_i7;
  char *tmp_pc8;
  int tmp_i9;
  int tmp_i10;
  uint tmp_u11;
  int tmp_i12;
  int tmp_i13;
  uint32_t *tmp_pu14;
  int local_8c;
  int local_88;
  uint local_80;
  int local_70;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  float local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_34;
  float local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  float local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0xe4a49;
  if (g_unk_010afc14 == 0) {
    if ((((((GHIDRA_FIELD(cgs, 33599436, 4) != 0 || GHIDRA_FIELD(cgs, 33599432, 4) != 0) || GHIDRA_FIELD(cgs, 33599440, 4) != 0) ||
          GHIDRA_FIELD(cgs, 33599444, 4) != 0) || GHIDRA_FIELD(cgs, 33599448, 4) != 0) && (g_unk_01047aec != 0)) &&
       (-1 < (int)GHIDRA_FIELD(cgs, 33575984, 4))) {
      if (GHIDRA_FIELD(cgs, 33575984, 4) == 0) {
        tmp_pc8 = "^1Stop AVI Recording";
      }
      else {
        tmp_pc8 = (char *)va("^3Record AVI @ ^7%d^2fps",GHIDRA_FIELD(cgs, 33575984, 4));
      }
      CG_DrawStringExt(0x2a,0x1a9,tmp_pc8,&colorWhite,0,0,8,0xe,0);
    }
    CG_demoTimescaleDraw();
    return;
  }
  tmp_i5 = trap_Milliseconds();
  tmp_b4 = false;
  local_4c = colorWhite;
  local_48 = g_unk_0014a334;
  local_44 = g_unk_0014a338;
  local_40 = g_unk_0014a33c;
  if (0 < g_unk_010afc14) {
    local_70 = 0;
    tmp_i7 = g_unk_010afc14;
    do {
      while( true ) {
        tmp_i2 = (&g_unk_010afbec)[local_70];
        tmp_i6 = tmp_i2 * 0x278;
        if (((&g_unk_010afc70)[tmp_i2 * 0x9e] != 0) &&
           (local_8c = *(int *)(&g_unk_010afe7c + tmp_i6), local_8c != 4)) break;
LAB_000e4ee9:
        tmp_b4 = true;
        local_70 = local_70 + 1;
        if (tmp_i7 <= local_70) goto LAB_000e4e8b;
      }
      local_80 = (&g_unk_010afc4c)[tmp_i2 * 0x9e];
      if ((local_80 & 1) != 0) {
        CG_windowNormalizeOnText(&g_unk_010afc18 + tmp_i6);
        local_80 = (&g_unk_010afc4c)[tmp_i2 * 0x9e] & 0xfffffffe;
        (&g_unk_010afc4c)[tmp_i2 * 0x9e] = local_80;
        local_8c = *(int *)(&g_unk_010afe7c + tmp_i6);
      }
      tmp_i7 = g_unk_010afc14;
      if ((local_80 & 2) == 0) {
LAB_000e4b66:
        tmp_i13 = tmp_i2 * 0x278 + 0x68168;
      }
      else {
        tmp_i13 = tmp_i2 * 0x278 + 0x68178;
        if (tmp_i5 % (int)(&g_unk_010afc54)[tmp_i2 * 0x9e] <= *(int *)(&g_unk_010afc50 + tmp_i2 * 0x278))
        goto LAB_000e4b66;
      }
      tmp_i10 = tmp_i2 * 0x278;
      local_40 = 1.0;
      tmp_i12 = (int)ROUND(*(float *)(&g_unk_010afc68 + tmp_i10));
      tmp_f1 = *(float *)(&g_unk_010afe88 + tmp_i10);
      tmp_i9 = tmp_i5 - *(int *)(&g_unk_010afe80 + tmp_i10);
      local_88 = (int)ROUND(*(float *)(&g_unk_010afe8c + tmp_i10));
      local_3c = *(uint32_t *)(&g_unk_010afc18 + tmp_i6);
      local_38 = *(uint32_t *)(&g_unk_010afc1c + tmp_i6);
      local_34 = *(uint32_t *)(&g_unk_010afc20 + tmp_i6);
      local_30 = *(float *)(&g_unk_010afc24 + tmp_i6);
      local_2c = *(uint32_t *)((int)&cg + tmp_i13);
      local_28 = *(uint32_t *)((int)&g_unk_01047ac4 + tmp_i13);
      local_24 = *(uint32_t *)((int)&g_unk_01047ac8 + tmp_i13);
      local_20 = *(float *)((int)&g_unk_01047acc + tmp_i13);
      if (local_8c == 1) {
        tmp_i7 = *(int *)(&g_unk_010afe78 + tmp_i10);
        tmp_i6 = tmp_i7 - tmp_i9;
        if ((local_80 & 0x20) != 0) {
          if (tmp_i6 < 1) {
            *(uint32_t *)(&g_unk_010afe7c + tmp_i10) = 0;
          }
          else {
            local_88 = local_88 + ((0x1e0 - local_88) * tmp_i6) / tmp_i7;
          }
          *(int *)(&g_unk_010afc48 + tmp_i2 * 0x278) = local_88;
        }
        if ((local_80 & 0x10) != 0) {
          if (tmp_i6 < 1) {
            *(uint32_t *)(&g_unk_010afe7c + tmp_i2 * 0x278) = 0;
          }
          else {
            local_40 = (float)tmp_i9 / (float)tmp_i7;
          }
        }
      }
      else if (local_8c == 2) {
        tmp_i6 = *(int *)(&g_unk_010afe78 + tmp_i10);
        tmp_i13 = tmp_i6 - tmp_i9;
        if ((local_80 & 0x20) != 0) {
          if (0 < tmp_i13) {
            local_88 = (int)ROUND(((float)tmp_i9 * (480.0 - *(float *)(&g_unk_010afe8c + tmp_i10))) /
                                  (float)tmp_i6 + (float)*(int *)(&g_unk_010afc48 + tmp_i10));
          }
          if ((0x1df < local_88) || (tmp_i13 < 0)) {
            *(uint32_t *)(&g_unk_010afe7c + tmp_i2 * 0x278) = 4;
            goto LAB_000e4ee9;
          }
        }
        if ((local_80 & 0x10) != 0) {
          if (tmp_i13 < 1) {
            local_40 = 0.0;
            *(uint32_t *)(&g_unk_010afe7c + tmp_i2 * 0x278) = 4;
          }
          else {
            local_40 = 1.0 - (float)tmp_i9 / (float)tmp_i6;
          }
        }
      }
      local_30 = local_30 * local_40;
      tmp_i13 = tmp_i2 * 0x278;
      local_20 = local_40 * local_20;
      tmp_f3 = (float)(int)ROUND(tmp_f1);
      CG_FillRect(tmp_f3,(float)local_88,*(uint32_t *)(&g_unk_010afe84 + tmp_i13),(float)tmp_i12,
                  &local_2c);
      CG_DrawRect(tmp_f3,(float)local_88,*(uint32_t *)(&g_unk_010afe84 + tmp_i13),(float)tmp_i12,
                  0x3f800000,&local_3c);
      tmp_u11 = (&g_unk_010afc4c)[tmp_i2 * 0x9e];
      tmp_i6 = (int)ROUND(tmp_f1) + 5;
      tmp_i7 = 0;
      if ((tmp_u11 & 4) != 0) {
        tmp_i7 = 3;
      }
      tmp_i9 = *(int *)(&g_unk_010afc74 + tmp_i13) + -1;
      if (-1 < tmp_i9) {
        tmp_pu14 = &cg + *(int *)(&g_unk_010afc74 + tmp_i13) + 0x1a0ad + tmp_i2 * 0x9e;
        do {
          if ((tmp_u11 & 4) == 0) {
            tmp_i12 = (tmp_i12 + -3) - tmp_pu14[-0x40];
LAB_000e4d5b:
            CG_DrawStringExt2(tmp_i6,(local_88 - tmp_i7) + tmp_i12,*tmp_pu14,&local_4c,0,1,
                              *(uint32_t *)(&g_unk_010afc64 + tmp_i13),
                              *(uint32_t *)(&g_unk_010afc58 + tmp_i13),0);
          }
          else {
            CG_Text_Paint_Ext((float)tmp_i6,(float)((local_88 - tmp_i7) + tmp_i12),
                              (&g_unk_010afc5c)[tmp_i2 * 0x9e],(&g_unk_010afc60)[tmp_i2 * 0x9e],&local_4c,
                              *tmp_pu14,0,0,0,0x110afec);
            tmp_i12 = (tmp_i12 + -3) - tmp_pu14[-0x40];
            if ((*(byte *)(&g_unk_010afc4c + tmp_i2 * 0x9e) & 4) == 0) goto LAB_000e4d5b;
          }
          if (tmp_i9 == 0) break;
          tmp_i9 = tmp_i9 + -1;
          tmp_pu14 = tmp_pu14 + -1;
          tmp_u11 = (&g_unk_010afc4c)[tmp_i2 * 0x9e];
        } while( true );
      }
      local_70 = local_70 + 1;
      tmp_i7 = g_unk_010afc14;
    } while (local_70 < g_unk_010afc14);
  }
LAB_000e4e8b:
  if ((((((GHIDRA_FIELD(cgs, 33599436, 4) != 0 || GHIDRA_FIELD(cgs, 33599432, 4) != 0) || GHIDRA_FIELD(cgs, 33599440, 4) != 0) ||
        GHIDRA_FIELD(cgs, 33599444, 4) != 0) || GHIDRA_FIELD(cgs, 33599448, 4) != 0) && (g_unk_01047aec != 0)) &&
     (-1 < (int)GHIDRA_FIELD(cgs, 33575984, 4))) {
    if (GHIDRA_FIELD(cgs, 33575984, 4) == 0) {
      tmp_pc8 = "^1Stop AVI Recording";
    }
    else {
      tmp_pc8 = (char *)va("^3Record AVI @ ^7%d^2fps",GHIDRA_FIELD(cgs, 33575984, 4));
    }
    CG_DrawStringExt(0x2a,0x1a9,tmp_pc8,&colorWhite,0,0,8,0xe,0);
  }
  CG_demoTimescaleDraw();
  if ((tmp_b4) && (0 < g_unk_010afc14)) {
    tmp_i7 = 0;
    tmp_i5 = g_unk_010afc14;
    do {
      tmp_i2 = (&g_unk_010afbec)[tmp_i7];
      if (((&g_unk_010afc70)[tmp_i2 * 0x9e] == 0) || (*(int *)(&g_unk_010afe7c + tmp_i2 * 0x278) == 4)) {
        tmp_i7 = tmp_i7 + -1;
        CG_windowFree(&g_unk_010afc18 + tmp_i2 * 0x278);
        tmp_i5 = g_unk_010afc14;
      }
      tmp_i7 = tmp_i7 + 1;
    } while (tmp_i7 < tmp_i5);
  }
  return;
}

void CG_printWindow(uint32_t param_1)
{
  char tmp_c1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  uint8_t *tmp_pu4;
  uint8_t *tmp_pu5;
  uint8_t *tmp_pu6;
  int tmp_i7;
  int tmp_i8;
  int *tmp_pi9;
  int tmp_i10;
  int local_428;
  uint32_t local_420;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  tmp_i3 = g_unk_010afbe8;
  uStack_14 = 0xe5249;
  if (g_unk_010afbe8 != 0) {
    Q_strncpyz(local_41c,param_1,0x400);
    local_420 = &g_unk_0011d7f6;
    local_428 = 0;
    tmp_i7 = 1;
    while( true ) {
      tmp_i10 = tmp_i7;
      tmp_c1 = local_41c[tmp_i10 + -1];
      if ((tmp_c1 < '\x01') || (tmp_i7 = *(int *)(tmp_i3 + 0x5c), 0x3f < tmp_i7)) break;
      if (tmp_c1 == '\n') {
        if (local_428 == tmp_i10 + -1) {
          tmp_pu2 = *(uint8_t **)(tmp_i3 + (tmp_i7 + 0x58) * 4);
          if (tmp_pu2 != (uint8_t *)0x0) {
            tmp_i8 = 0;
            tmp_pu5 = &g_unk_010ad28c;
            do {
              if ((*(int *)(tmp_pu5 + -4) != 0) && (tmp_pu2 == tmp_pu5)) {
                *(int *)(tmp_i3 + 0x5c) = tmp_i7 + 1;
                (&g_unk_010ad288)[tmp_i8 * 0x21] = 1;
                Q_strncpyz(tmp_pu2,local_420,0x80);
                goto LAB_000e5371;
              }
              tmp_i8 = tmp_i8 + 1;
              tmp_pu5 = tmp_pu5 + 0x84;
            } while (tmp_i8 != 0x50);
          }
          tmp_pi9 = &g_unk_010ad288;
          tmp_i7 = 0;
          while (*tmp_pi9 != 0) {
            tmp_i7 = tmp_i7 + 1;
            tmp_pi9 = tmp_pi9 + 0x21;
            if (tmp_i7 == 0x50) {
              return;
            }
          }
          (&g_unk_010ad288)[tmp_i7 * 0x21] = 1;
          tmp_pu4 = local_420;
        }
        else {
          local_41c[tmp_i10 + -1] = '\0';
          tmp_pu4 = local_41c + local_428;
          tmp_pu2 = *(uint8_t **)(tmp_i3 + (*(int *)(tmp_i3 + 0x5c) + 0x58) * 4);
          if (tmp_pu2 != (uint8_t *)0x0) {
            tmp_i7 = 0;
            tmp_pu5 = &g_unk_010ad28c;
            do {
              if ((*(int *)(tmp_pu5 + -4) != 0) && (tmp_pu2 == tmp_pu5)) {
                *(int *)(tmp_i3 + 0x5c) = *(int *)(tmp_i3 + 0x5c) + 1;
                (&g_unk_010ad288)[tmp_i7 * 0x21] = 1;
                Q_strncpyz(tmp_pu2,tmp_pu4,0x80);
                goto LAB_000e5371;
              }
              tmp_i7 = tmp_i7 + 1;
              tmp_pu5 = tmp_pu5 + 0x84;
            } while (tmp_i7 != 0x50);
          }
          tmp_pi9 = &g_unk_010ad288;
          tmp_i7 = 0;
          while (*tmp_pi9 != 0) {
            tmp_i7 = tmp_i7 + 1;
            tmp_pi9 = tmp_pi9 + 0x21;
            if (tmp_i7 == 0x50) {
              return;
            }
          }
          (&g_unk_010ad288)[tmp_i7 * 0x21] = 1;
        }
        Q_strncpyz(&g_unk_010ad28c + tmp_i7 * 0x84,tmp_pu4,0x80);
        tmp_i8 = *(int *)(tmp_i3 + 0x5c);
        *(int *)(tmp_i3 + 0x5c) = tmp_i8 + 1;
        *(uint8_t **)(tmp_i3 + 0x160 + tmp_i8 * 4) = &g_unk_010ad28c + tmp_i7 * 0x84;
LAB_000e5371:
        tmp_i7 = tmp_i10 + 1;
        local_428 = tmp_i10;
      }
      else {
        tmp_i7 = tmp_i10 + 1;
      }
    }
    if (local_428 < tmp_i10 + -1) {
      tmp_pu5 = local_41c + local_428;
      tmp_pu2 = *(uint8_t **)(tmp_i3 + (*(int *)(tmp_i3 + 0x5c) + 0x58) * 4);
      if (tmp_pu2 != (uint8_t *)0x0) {
        tmp_i7 = 0;
        tmp_pu6 = &g_unk_010ad28c;
        do {
          if ((*(int *)(tmp_pu6 + -4) != 0) && (tmp_pu2 == tmp_pu6)) {
            *(int *)(tmp_i3 + 0x5c) = *(int *)(tmp_i3 + 0x5c) + 1;
            (&g_unk_010ad288)[tmp_i7 * 0x21] = 1;
            Q_strncpyz(tmp_pu2,tmp_pu5,0x80);
            return;
          }
          tmp_i7 = tmp_i7 + 1;
          tmp_pu6 = tmp_pu6 + 0x84;
        } while (tmp_i7 != 0x50);
      }
      tmp_pi9 = &g_unk_010ad288;
      tmp_i7 = 0;
      do {
        if (*tmp_pi9 == 0) {
          (&g_unk_010ad288)[tmp_i7 * 0x21] = 1;
          Q_strncpyz(&g_unk_010ad28c + tmp_i7 * 0x84,tmp_pu5,0x80);
          tmp_i10 = *(int *)(tmp_i3 + 0x5c);
          *(int *)(tmp_i3 + 0x5c) = tmp_i10 + 1;
          *(uint8_t **)(tmp_i3 + 0x160 + tmp_i10 * 4) = &g_unk_010ad28c + tmp_i7 * 0x84;
          return;
        }
        tmp_i7 = tmp_i7 + 1;
        tmp_pi9 = tmp_pi9 + 0x21;
      } while (tmp_i7 != 0x50);
    }
  }
  return;
}

void CG_initStrings(void)
{
  uint32_t *tmp_pu1;
  uint32_t *tmp_pu2;
  
  tmp_pu1 = &g_unk_010ad288;
  do {
    *tmp_pu1 = 0;
    tmp_pu2 = tmp_pu1 + 0x21;
    *(uint8_t *)(tmp_pu1 + 1) = 0;
    tmp_pu1 = tmp_pu2;
  } while (tmp_pu2 != &g_unk_010afbc8);
  return;
}

uint32_t CG_addString(int param_1,uint32_t param_2)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  int *tmp_pi5;
  
  tmp_pu1 = *(uint8_t **)(param_1 + (*(int *)(param_1 + 0x5c) + 0x58) * 4);
  if (tmp_pu1 != (uint8_t *)0x0) {
    tmp_pu3 = &g_unk_010ad28c;
    tmp_i4 = 0;
    do {
      if ((*(int *)(tmp_pu3 + -4) != 0) && (tmp_pu1 == tmp_pu3)) {
        *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + 1;
        (&g_unk_010ad288)[tmp_i4 * 0x21] = 1;
        Q_strncpyz(tmp_pu1,param_2,0x80);
        return 1;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu3 = tmp_pu3 + 0x84;
    } while (tmp_i4 != 0x50);
  }
  tmp_pi5 = &g_unk_010ad288;
  tmp_i4 = 0;
  do {
    if (*tmp_pi5 == 0) {
      (&g_unk_010ad288)[tmp_i4 * 0x21] = 1;
      Q_strncpyz(&g_unk_010ad28c + tmp_i4 * 0x84,param_2,0x80);
      tmp_i2 = *(int *)(param_1 + 0x5c);
      *(int *)(param_1 + 0x5c) = tmp_i2 + 1;
      *(uint8_t **)(param_1 + 0x160 + tmp_i2 * 4) = &g_unk_010ad28c + tmp_i4 * 0x84;
      return 1;
    }
    tmp_i4 = tmp_i4 + 1;
    tmp_pi5 = tmp_pi5 + 0x21;
  } while (tmp_i4 != 0x50);
  return 0;
}

void CG_removeStrings(int param_1)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  
  if (0 < *(int *)(param_1 + 0x5c)) {
    tmp_i3 = 0;
    do {
      tmp_pu1 = &g_unk_010ad28c;
      tmp_i2 = 0;
      do {
        if ((*(int *)(tmp_pu1 + -4) != 0) &&
           (*(uint8_t **)(param_1 + 0x160 + tmp_i3 * 4) == tmp_pu1)) {
          *(uint32_t *)(param_1 + 0x160 + tmp_i3 * 4) = 0;
          (&g_unk_010ad288)[tmp_i2 * 0x21] = 0;
          (&g_unk_010ad28c)[tmp_i2 * 0x84] = 0;
          break;
        }
        tmp_i2 = tmp_i2 + 1;
        tmp_pu1 = tmp_pu1 + 0x84;
      } while (tmp_i2 != 0x50);
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 < *(int *)(param_1 + 0x5c));
  }
  return;
}

void CG_UpdateSvCvars(void)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  long tmp_l4;
  uint8_t *tmp_pu5;
  int local_28;
  
  tmp_u1 = CG_ConfigString(0x26);
  if (g_unk_01047aec == 0) {
    g_unk_010ee050 = 0;
    tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"N");
    g_unk_010d604c = strtol(tmp_pc2,(char **)0x0,10);
    if (0 < g_unk_010d604c) {
      local_28 = 0;
      tmp_pu5 = &g_unk_010bde4c;
      do {
        tmp_u3 = va(&g_unk_00121652,local_28);
        tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,tmp_u3);
        tmp_pc2 = strtok(tmp_pc2," ");
        tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
        *(long *)(tmp_pu5 + 0x100) = tmp_l4;
        tmp_pc2 = strtok((char *)0x0," ");
        Q_strncpyz(tmp_pu5,tmp_pc2,0x100);
        tmp_pc2 = strtok((char *)0x0," ");
        Q_strncpyz(tmp_pu5 + 0x104,tmp_pc2,0x100);
        tmp_pc2 = strtok((char *)0x0," ");
        if (tmp_pc2 != (char *)0x0) {
          Q_strncpyz(tmp_pu5 + 0x204,tmp_pc2,0x100);
        }
        Q_strncpyz(&g_unk_010d6050 + g_unk_010ee050 * 0x200,tmp_pu5,0x100);
        trap_Cvar_VariableStringBuffer(tmp_pu5,&g_unk_010d6150 + g_unk_010ee050 * 0x200,0x100);
        local_28 = local_28 + 1;
        g_unk_010ee050 = g_unk_010ee050 + 1;
        tmp_pu5 = tmp_pu5 + 0x304;
      } while (local_28 < g_unk_010d604c);
      return;
    }
  }
  return;
}

void CG_Debreifing2_Awards_Parse(void)
{
  char *tmp_pc1;
  size_t tmp_s2;
  long tmp_l3;
  int tmp_i4;
  int *tmp_pi5;
  int *tmp_pi6;
  int local_438;
  char *local_420;
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0x1060ee;
  local_420 = (char *)CG_ConfigString(0x22);
  Q_strncpyz(local_41c,local_420,0x400);
  local_420 = local_41c;
  while( true ) {
    tmp_pc1 = strchr(local_420,0x3b);
    if (tmp_pc1 == (char *)0x0) break;
    *tmp_pc1 = '\"';
  }
  local_438 = 0x400;
  tmp_i4 = 0x31101d8;
  tmp_pi5 = (int *)(cgs + 0x20202f8);
  do {
    tmp_pi6 = tmp_pi5 + 1;
    tmp_pc1 = (char *)COM_Parse(&local_420);
    Q_strncpyz(tmp_i4,tmp_pc1,local_438);
    *tmp_pi5 = tmp_i4;
    tmp_s2 = strlen(tmp_pc1);
    local_438 = local_438 - tmp_s2;
    tmp_i4 = tmp_i4 + 1 + tmp_s2;
    tmp_pc1 = (char *)COM_Parse(&local_420);
    tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
    tmp_pi5[0x10] = tmp_l3;
    tmp_pi5 = tmp_pi6;
  } while (tmp_pi6 != (int *)(cgs + 0x2020338));
  GHIDRA_FIELD(cgs, 33686260, 4) = 1;
  return;
}

void CG_Debreifing2_Awards_Draw(int param_1)
{
  float tmp_f1;
  uint32_t tmp_u2;
  int *tmp_pi3;
  int *tmp_pi4;
  uint8_t **tmp_ppu5;
  float local_40;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20;
  uint32_t uStack_14;
  
  uStack_14 = 0x106209;
  local_2c = 0x3f19999a;
  local_28 = 0x3f19999a;
  local_24 = 0x3f19999a;
  tmp_f1 = *(float *)(param_1 + 0xc);
  local_20 = 0x3f800000;
  if (GHIDRA_FIELD(cgs, 33686260, 4) == 0) {
    CG_Debreifing2_Awards_Parse();
  }
  tmp_ppu5 = &awardNames;
  tmp_pi3 = (int *)(cgs + 0x2020338);
  local_40 = tmp_f1 + 1.0;
  do {
    while (*tmp_pi3 == 0) {
      tmp_pi3 = tmp_pi3 + 1;
      tmp_ppu5 = tmp_ppu5 + 1;
      if (tmp_pi3 == (int *)(cgs + 0x2020378)) {
        return;
      }
    }
    CG_DrawPic(*(float *)(param_1 + 8) + 4.0,local_40 + 2.0,0x41400000,0x41400000,tmp_pi3[-0x7ffff8])
    ;
    tmp_f1 = local_40 + 12.0;
    CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 20.0,tmp_f1,0x3e3851ec,0x3e3851ec,&local_2c,*tmp_ppu5,
                      0,0,0,0x110afec);
    tmp_u2 = GHIDRA_FIELD(cgs, 131852, 4);
    if (*tmp_pi3 == 1) {
      tmp_u2 = GHIDRA_FIELD(cgs, 131848, 4);
    }
    tmp_pi4 = tmp_pi3 + 1;
    tmp_ppu5 = tmp_ppu5 + 1;
    CG_DrawPic(*(float *)(param_1 + 8) + 28.0 + 180.0,local_40 + 4.0,0x41500000,0x41100000,tmp_u2);
    CG_Text_Paint_Ext(*(float *)(param_1 + 8) + 28.0 + 180.0 + 18.0,tmp_f1,0x3e3851ec,0x3e3851ec,
                      &local_2c,tmp_pi3[-0x10],0,0,0,0x110afec);
    tmp_pi3 = tmp_pi4;
    local_40 = tmp_f1;
  } while (tmp_pi4 != (int *)(cgs + 0x2020378));
  return;
}

void CG_UpdateClassesMaxHP(void)
{
  uint32_t tmp_u1;
  char *tmp_pc2;
  
  tmp_u1 = CG_ConfigString(0x27);
  tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,&g_unk_00121e10);
  GHIDRA_FIELD(cgs, 33823084, 4) = strtol(tmp_pc2,(char **)0x0,10);
  tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"M");
  GHIDRA_FIELD(cgs, 33823088, 4) = strtol(tmp_pc2,(char **)0x0,10);
  tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"E");
  GHIDRA_FIELD(cgs, 33823092, 4) = strtol(tmp_pc2,(char **)0x0,10);
  tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,"F");
  GHIDRA_FIELD(cgs, 33823096, 4) = strtol(tmp_pc2,(char **)0x0,10);
  tmp_pc2 = (char *)Info_ValueForKey(tmp_u1,&g_unk_00116f00);
  GHIDRA_FIELD(cgs, 33823100, 4) = strtol(tmp_pc2,(char **)0x0,10);
  return;
}

