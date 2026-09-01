/* Snapshot processing and interpolation — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_snapshot.h"

void CG_ExecuteNewServerCommands(int param_1)
{
  int tmp_i1;
  
  while ((int)GHIDRA_FIELD(cgs, 27376, 4) < param_1) {
    GHIDRA_FIELD(cgs, 27376, 4) = GHIDRA_FIELD(cgs, 27376, 4) + 1;
    tmp_i1 = trap_GetServerCommand(GHIDRA_FIELD(cgs, 27376, 4));
    if (tmp_i1 != 0) {
      CG_ServerCommand();
    }
  }
  return;
}

void CG_SetInitialSnapshot(int param_1)
{
  uint8_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  long tmp_l7;
  int local_84;
  char local_6c [16];
  char local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0xbc3eb;
  g_unk_01047b00 = param_1;
  BG_PlayerStateToEntityState
            (param_1 + 0x2c,cg_entities + *(int *)(param_1 + 0xcc) * 0xaf8,g_unk_010906e0,0);
  CG_BuildSolidList();
  CG_ExecuteNewServerCommands(*(uint32_t *)(param_1 + 0x245e0));
  CG_Respawn(0);
  if (0 < *(int *)(g_unk_01047b00 + 0x5d8)) {
    local_84 = 0;
    do {
      tmp_i3 = g_unk_01047b00;
      tmp_i5 = g_unk_01047b00 + 0x5d0 + local_84 * 0x120;
      tmp_i6 = *(int *)(tmp_i5 + 0xc);
      tmp_pu1 = cg_entities + tmp_i6 * 0xaf8;
      tmp_u4 = 0;
      do {
        tmp_u2 = *(uint32_t *)(tmp_i5 + 0xc + tmp_u4);
        *(uint32_t *)(tmp_i6 * 0xaf8 + 0x3133e44 + tmp_u4) = *(uint32_t *)(tmp_i5 + 0x10 + tmp_u4);
        *(uint32_t *)(tmp_pu1 + tmp_u4) = tmp_u2;
        tmp_u4 = tmp_u4 + 8;
      } while (tmp_u4 < 0x120);
      tmp_i5 = tmp_i6 * 0xaf8;
      *(uint32_t *)(cg_entities + tmp_i5 + 0x244) = 1;
      *(uint32_t *)(cg_entities + tmp_i5 + 0x240) = 0;
      *(uint32_t *)(cg_entities + tmp_i5 + 0x250) = 0;
      *(uint32_t *)(cg_entities + tmp_i5 + 0x254) = *(uint32_t *)(cg_entities + tmp_i5 + 0xc0);
      tmp_u2 = *(uint32_t *)(tmp_i3 + 8);
      *(uint32_t *)(cg_entities + tmp_i5 + 0x794) = *(uint32_t *)(cg_entities + tmp_i5 + 0x5c);
      *(uint32_t *)(cg_entities + tmp_i5 + 0x798) = *(uint32_t *)(cg_entities + tmp_i5 + 0x60);
      *(uint32_t *)(cg_entities + tmp_i5 + 0x25c) = tmp_u2;
      *(uint32_t *)(cg_entities + tmp_i5 + 0x79c) = *(uint32_t *)(cg_entities + tmp_i5 + 100);
      *(uint32_t *)(cg_entities + tmp_i5 + 0x7c4) = 0;
      *(uint32_t *)(cg_entities + tmp_i5 + 0x7a0) = *(uint32_t *)(cg_entities + tmp_i5 + 0x74);
      *(uint32_t *)(cg_entities + tmp_i5 + 0x7c8) = 0;
      *(uint32_t *)(cg_entities + tmp_i5 + 0x7a4) = *(uint32_t *)(cg_entities + tmp_i5 + 0x78);
      *(uint32_t *)(cg_entities + tmp_i5 + 0x7a8) = *(uint32_t *)(cg_entities + tmp_i5 + 0x7c);
      if (*(int *)(cg_entities + tmp_i5 + 4) == 1) {
        CG_ResetPlayerEntity(tmp_pu1);
      }
      tmp_i6 = tmp_i6 * 0xaf8;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x248) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x24c) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x264) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x260) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x7dc) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0xab0) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x784) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x780) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x77c) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x790) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x78c) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x788) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x9b4) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x994) = 0;
      *(uint32_t *)(cg_entities + tmp_i6 + 0x998) = 0;
      CG_CheckEvents(tmp_pu1);
      local_84 = local_84 + 1;
    } while (local_84 < *(int *)(g_unk_01047b00 + 0x5d8));
  }
  trap_Cvar_VariableStringBuffer("r_oldMode",local_6c,0x10);
  tmp_l7 = strtol(local_6c,(char **)0x0,10);
  if (tmp_l7 == 0) {
    if (g_unk_01047aec != 0) {
      ccInitial = 1;
      goto LAB_000bc6f5;
    }
    trap_Cvar_VariableStringBuffer("mapname",local_5c,0x40);
    tmp_i5 = Q_stricmp(local_5c,prevmap_11958);
    if (((tmp_i5 != 0) && (strcpy(prevmap_11958,local_5c), GHIDRA_FIELD(cgs, 33526364, 4) != 0)) &&
       (g_unk_010abd78 == 0)) {
      CG_LimboMenu_f();
    }
  }
  else {
    trap_UI_Popup(2);
  }
  if (g_unk_01047aec == 0) {
    return;
  }
LAB_000bc6f5:
  CG_keyOn_f();
  if (0 < (int)GHIDRA_FIELD(demo_infoWindow, 12, 4)) {
    CG_ShowHelp_On(&g_unk_010afbc8);
  }
  return;
}

void CG_ProcessSnapshots(void)
{
  uint tmp_u1;
  bool tmp_b2;
  int tmp_i3;
  uint *tmp_pu4;
  uint *tmp_pu5;
  uint tmp_u6;
  uint *tmp_pu7;
  uint tmp_u8;
  uint tmp_u9;
  uint32_t *tmp_pu10;
  byte tmp_b11;
  int local_40;
  int local_20 [3];
  uint32_t uStack_14;
  
  tmp_b11 = 0;
  uStack_14 = 0xbc819;
  trap_GetCurrentSnapshotNumber(local_20,&g_unk_01047afc);
  tmp_i3 = g_unk_01047af8;
  if ((g_unk_01047af8 != local_20[0]) && (tmp_i3 = local_20[0], local_20[0] < g_unk_01047af8)) {
    CG_Error("CG_ProcessSnapshots: n < cg.latestSnapshotNum");
    tmp_i3 = local_20[0];
  }
  while (g_unk_01047af8 = tmp_i3, g_unk_01047b00 == (uint *)0x0) {
    if (GHIDRA_FIELD(cgs, 27380, 4) + 1000 < g_unk_01047af8) {
      CG_Printf("[skipnotify]WARNING: CG_ReadNextSnapshot: way out of range, %i > %i\n",g_unk_01047af8
                ,GHIDRA_FIELD(cgs, 27380, 4));
      if (g_unk_01047af8 <= (int)GHIDRA_FIELD(cgs, 27380, 4)) {
        return;
      }
    }
    else if (g_unk_01047af8 <= (int)GHIDRA_FIELD(cgs, 27380, 4)) {
      return;
    }
    while( true ) {
      tmp_pu7 = (uint *)&g_unk_0106c0ec;
      if (g_unk_01047b00 != &g_unk_01047b08) {
        tmp_pu7 = &g_unk_01047b08;
      }
      GHIDRA_FIELD(cgs, 27380, 4) = GHIDRA_FIELD(cgs, 27380, 4) + 1;
      tmp_i3 = trap_GetSnapshot(GHIDRA_FIELD(cgs, 27380, 4),tmp_pu7);
      if (tmp_i3 != 0) break;
      CG_AddLagometerSnapshotInfo(0);
      if (g_unk_01047af8 <= (int)GHIDRA_FIELD(cgs, 27380, 4)) {
        return;
      }
    }
    CG_AddLagometerSnapshotInfo(tmp_pu7);
    tmp_u8 = *tmp_pu7;
    if ((g_unk_01047b00 != (uint *)0x0) && (((*g_unk_01047b00 ^ tmp_u8) & 4) != 0)) {
      g_unk_01091804 = 0xffffffff;
      g_unk_010aace0 = 0;
      g_unk_01091810 = 0xffffffff;
      g_unk_010917fc = 0xffffffff;
      tmp_u8 = *tmp_pu7;
    }
    tmp_i3 = g_unk_01047af8;
    if ((tmp_u8 & 2) == 0) {
      CG_SetInitialSnapshot(tmp_pu7);
      tmp_i3 = g_unk_01047af8;
    }
  }
LAB_000bc9a5:
  if (g_unk_01047b04 == (uint *)0x0) goto LAB_000bcdf2;
LAB_000bc9b1:
  tmp_u8 = g_unk_01047b00[2];
LAB_000bc9bd:
  if (((int)tmp_u8 <= (int)g_unk_010906e0) && ((int)g_unk_010906e0 < (int)g_unk_01047b04[2])) {
    return;
  }
  if ((cg_lagometer[0xc] & 2) == 0) {
    if (1000 < (int)(g_unk_010906e0 - time_11997)) {
LAB_000bca22:
      g_unk_010ef1f0 = numSnapshots_11998;
      numSnapshots_11998 = 0;
      time_11997 = g_unk_010906e0;
    }
    if (g_unk_01047b04 == (uint *)0x0) {
LAB_000bd0a9:
      CG_Error("CG_TransitionSnapshot: NULL cg.nextSnap");
    }
  }
  else {
    if (g_unk_01047b04 == (uint *)0x0) {
      if (1000 < (int)(g_unk_010906e0 - time_11997)) goto LAB_000bca22;
      goto LAB_000bd0a9;
    }
    if ((int)(g_unk_01047b04[2] - tmp_u8) < 1) goto LAB_000bd149;
    numSnapshots_11998 = (uint32_t)(1000 / (longlong)(int)(g_unk_01047b04[2] - tmp_u8));
    if (1000 < (int)(g_unk_010906e0 - time_11997)) goto LAB_000bca22;
  }
  CG_ExecuteNewServerCommands(g_unk_01047b04[0x9178]);
  tmp_pu5 = g_unk_01047b04;
  tmp_pu7 = g_unk_01047b00;
  if (g_unk_01047b00 == (uint *)0x0) goto LAB_000bc9a5;
  if (g_unk_01047b04 != (uint *)0x0) {
    tmp_pu10 = &oldValid;
    for (tmp_i3 = 0x400; tmp_i3 != 0; tmp_i3 = tmp_i3 + -1) {
      *tmp_pu10 = 0;
      tmp_pu10 = tmp_pu10 + (uint)tmp_b11 * -2 + 1;
    }
    if (0 < (int)g_unk_01047b00[0x176]) {
      tmp_i3 = 0;
      tmp_pu4 = g_unk_01047b00 + 0x177;
      do {
        tmp_i3 = tmp_i3 + 1;
        *(uint32_t *)(cg_entities + *tmp_pu4 * 0xaf8 + 0x244) = 0;
        (&oldValid)[*tmp_pu4] = 1;
        tmp_pu4 = tmp_pu4 + 0x48;
      } while (tmp_i3 < (int)g_unk_01047b00[0x176]);
    }
    g_unk_01047b00 = tmp_pu5;
    if ((tmp_pu5[0x33] == g_unk_01047ac4) &&
       (tmp_u8 = tmp_pu5[0x47], tmp_b2 = (int)g_unk_01047ac8 < (int)tmp_u8, g_unk_01047ac8 = tmp_u8, tmp_b2))
    {
      g_unk_01047acc = g_unk_010906e0;
    }
    if ((int)tmp_pu7[0x55] < (int)tmp_pu5[0x55]) {
      g_unk_010ef674 = g_unk_010906e0;
    }
    if ((int)tmp_pu7[0x54] < (int)tmp_pu5[0x54]) {
      g_unk_010ef678 = g_unk_010906e0;
    }
    BG_PlayerStateToEntityState(tmp_pu5 + 0xb,cg_entities + tmp_pu5[0x33] * 0xaf8,g_unk_010906e0,0);
    tmp_pu5 = g_unk_01047b00;
    *(uint32_t *)(cg_entities + g_unk_01047b00[0x33] * 0xaf8 + 0x240) = 0;
    if (0 < (int)tmp_pu5[0x176]) {
      local_40 = 0;
      do {
        while( true ) {
          tmp_u8 = tmp_pu5[local_40 * 0x48 + 0x177];
          tmp_i3 = tmp_u8 * 0xaf8;
          CG_TransitionEntity(cg_entities + tmp_i3);
          if ((*(int *)(cg_entities + tmp_i3 + 0x244) != 0) || ((&oldValid)[tmp_u8] != 1)) break;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x250) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x254) = *(uint32_t *)(cg_entities + tmp_i3 + 0xc0)
          ;
          tmp_pu5 = g_unk_01047b00;
          tmp_u9 = g_unk_01047b00[2];
          *(uint32_t *)(cg_entities + tmp_i3 + 0x794) = *(uint32_t *)(cg_entities + tmp_i3 + 0x5c)
          ;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x798) = *(uint32_t *)(cg_entities + tmp_i3 + 0x60)
          ;
          *(uint *)(cg_entities + tmp_i3 + 0x25c) = tmp_u9;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x79c) = *(uint32_t *)(cg_entities + tmp_i3 + 100);
          *(uint32_t *)(cg_entities + tmp_i3 + 0x7c4) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x7a0) = *(uint32_t *)(cg_entities + tmp_i3 + 0x74)
          ;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x7a4) = *(uint32_t *)(cg_entities + tmp_i3 + 0x78)
          ;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x7c8) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x7a8) = *(uint32_t *)(cg_entities + tmp_i3 + 0x7c)
          ;
          if (*(int *)(cg_entities + tmp_i3 + 4) == 1) {
            CG_ResetPlayerEntity(cg_entities + tmp_i3);
            tmp_pu5 = g_unk_01047b00;
          }
          tmp_i3 = tmp_u8 * 0xaf8;
          local_40 = local_40 + 1;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x248) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x24c) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x264) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x260) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x7dc) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x9b4) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x784) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x780) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x77c) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x790) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x78c) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x788) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x994) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0x998) = 0;
          *(uint32_t *)(cg_entities + tmp_i3 + 0xab0) = 0;
          if ((int)tmp_pu5[0x176] <= local_40) goto LAB_000bcd70;
        }
        local_40 = local_40 + 1;
        tmp_pu5 = g_unk_01047b00;
      } while (local_40 < (int)g_unk_01047b00[0x176]);
    }
LAB_000bcd70:
    g_unk_01047b04 = (uint *)0x0;
    if (((tmp_pu7[0x25] ^ tmp_pu5[0x25]) & 4) != 0) {
      g_unk_010906d4 = 1;
    }
    if ((((g_unk_01047aec != 0) || ((*(byte *)((int)tmp_pu5 + 0x39) & 0x10) != 0)) ||
        (GHIDRA_FIELD(cg_nopredict, 12, 4) != 0)) &&
       (CG_TransitionPlayerState(tmp_pu5 + 0xb,tmp_pu7 + 0xb), g_unk_01047b04 != (uint *)0x0))
    goto LAB_000bc9b1;
  }
LAB_000bcdf2:
  if (GHIDRA_FIELD(cgs, 27380, 4) + 1000 < g_unk_01047af8) {
    CG_Printf("[skipnotify]WARNING: CG_ReadNextSnapshot: way out of range, %i > %i\n",g_unk_01047af8,
              GHIDRA_FIELD(cgs, 27380, 4));
    if ((int)GHIDRA_FIELD(cgs, 27380, 4) < g_unk_01047af8) goto LAB_000bce1d;
joined_r0x000bd1dd:
    if (g_unk_01047b00 == (uint *)0x0) {
      CG_Error("CG_ProcessSnapshots: cg.snap == NULL");
    }
LAB_000bd149:
    tmp_u8 = g_unk_01047b00[2];
    tmp_u9 = tmp_u8;
    if ((int)tmp_u8 <= (int)g_unk_010906e0) {
      tmp_u8 = g_unk_0102619c;
      tmp_u9 = g_unk_010906e0;
    }
    g_unk_010906e0 = tmp_u9;
    g_unk_0102619c = tmp_u8;
    if (g_unk_01047b04 == (uint *)0x0) {
      return;
    }
    if ((int)g_unk_010906e0 < (int)g_unk_01047b04[2]) {
      return;
    }
    CG_Error("CG_ProcessSnapshots: cg.nextSnap->serverTime <= cg.time");
    return;
  }
  if (g_unk_01047af8 <= (int)GHIDRA_FIELD(cgs, 27380, 4)) goto joined_r0x000bd1dd;
LAB_000bce1d:
  while( true ) {
    tmp_pu7 = (uint *)&g_unk_0106c0ec;
    if (g_unk_01047b00 != &g_unk_01047b08) {
      tmp_pu7 = &g_unk_01047b08;
    }
    GHIDRA_FIELD(cgs, 27380, 4) = GHIDRA_FIELD(cgs, 27380, 4) + 1;
    tmp_i3 = trap_GetSnapshot(GHIDRA_FIELD(cgs, 27380, 4),tmp_pu7);
    if (tmp_i3 != 0) break;
    CG_AddLagometerSnapshotInfo(0);
    if (g_unk_01047af8 <= (int)GHIDRA_FIELD(cgs, 27380, 4)) goto joined_r0x000bd1dd;
  }
  CG_AddLagometerSnapshotInfo(tmp_pu7);
  if ((g_unk_01047b00 != (uint *)0x0) && (((*g_unk_01047b00 ^ *tmp_pu7) & 4) != 0)) {
    g_unk_010aace0 = 0;
    g_unk_01091804 = 0xffffffff;
    g_unk_01091810 = 0xffffffff;
    g_unk_010917fc = 0xffffffff;
  }
  g_unk_01047b04 = tmp_pu7;
  BG_PlayerStateToEntityState(tmp_pu7 + 0xb,tmp_pu7[0x33] * 0xaf8 + 0x3133f60,g_unk_010906e0,0);
  tmp_pu5 = g_unk_01047b00;
  *(uint32_t *)(cg_entities + g_unk_01047b00[0x33] * 0xaf8 + 0x240) = 1;
  tmp_u8 = tmp_pu7[0x176];
  if (0 < (int)tmp_u8) {
    tmp_pu4 = tmp_pu7 + 0x177;
    tmp_u9 = 0;
    do {
      tmp_u1 = *tmp_pu4;
      tmp_u6 = 0;
      do {
        *(uint32_t *)(tmp_u1 * 0xaf8 + 0x3133f60 + tmp_u6) = *(uint32_t *)((int)tmp_pu4 + tmp_u6);
        *(uint32_t *)(tmp_u1 * 0xaf8 + 0x3133f64 + tmp_u6) =
             *(uint32_t *)((int)tmp_pu4 + tmp_u6 + 4);
        tmp_u6 = tmp_u6 + 8;
      } while (tmp_u6 < 0x120);
      tmp_u6 = 0;
      if (*(int *)(cg_entities + tmp_u1 * 0xaf8 + 0x244) != 0) {
        tmp_u6 = (uint)(((tmp_pu4[2] ^ *(uint *)(cg_entities + tmp_u1 * 0xaf8 + 8)) & 4) == 0);
      }
      tmp_u9 = tmp_u9 + 1;
      tmp_pu4 = tmp_pu4 + 0x48;
      *(uint *)(cg_entities + tmp_u1 * 0xaf8 + 0x240) = tmp_u6;
    } while (tmp_u9 != tmp_u8);
  }
  g_unk_010906d8 = (tmp_pu5[0x25] ^ tmp_pu7[0x25]) >> 2 & 1;
  if (g_unk_01047b04[0x33] != tmp_pu5[0x33]) {
    g_unk_010906d8 = 1;
  }
  if (((*tmp_pu5 ^ *g_unk_01047b04) & 4) != 0) {
    g_unk_010906d8 = 1;
  }
  CG_BuildSolidList();
  tmp_u8 = g_unk_01047b00[2];
  if ((int)g_unk_01047b04[2] < (int)tmp_u8) {
    CG_Error("CG_ProcessSnapshots: Server time went backwards");
    tmp_u8 = g_unk_01047b00[2];
  }
  goto LAB_000bc9bd;
}

