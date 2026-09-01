/* NxAC anti-cheat — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_anticheat.h"

uint32_t NxAC_ViolationStringForIndex(int param_1)
{
  return *(uint32_t *)(NxAC_ViolationNames + param_1 * 4);
}

uint32_t NxAC_FlagToIndex(uint param_1,uint param_2)
{
  int tmp_i1;
  
  if (NxAC_ViolationsCount < 2) {
    return 0xffffffff;
  }
  if (((param_1 & GHIDRA_FIELD(NxAC_Violations, 12, 4)) == 0) || ((param_2 & GHIDRA_FIELD(NxAC_Violations, 12, 4)) != 0)) {
    if (NxAC_ViolationsCount == 2) {
      return 0xffffffff;
    }
    if (((param_1 & GHIDRA_FIELD(NxAC_Violations, 24, 4)) == 0) || ((param_2 & GHIDRA_FIELD(NxAC_Violations, 24, 4)) != 0)) {
      if (NxAC_ViolationsCount == 3) {
        return 0xffffffff;
      }
      if (((param_1 & GHIDRA_FIELD(NxAC_Violations, 36, 4)) == 0) || ((param_2 & GHIDRA_FIELD(NxAC_Violations, 36, 4)) != 0)) {
        return 0xffffffff;
      }
      tmp_i1 = 3;
    }
    else {
      tmp_i1 = 2;
    }
  }
  else {
    tmp_i1 = 1;
  }
  return *(uint32_t *)(NxAC_Violations + tmp_i1 * 0xc + 8);
}

void NxAC_BanClient(int param_1)
{
  uint tmp_u1;
  uint tmp_u2;
  time_t tVar3;
  int tmp_i4;
  tm *__tp;
  time_t *ptVar5;
  int tmp_i6;
  time_t local_220 [132];
  
  tmp_i4 = *(int *)(param_1 + 400);
  tmp_i6 = *(int *)(tmp_i4 + 0xb30);
  if (*(int *)(NxAC_Violations + tmp_i6 * 0xc + 4) == 1) {
    local_220[1] = 0;
    tmp_u1 = 0;
    do {
      tmp_u2 = tmp_u1;
      *(uint32_t *)((int)local_220 + tmp_u2 + 8) = 0;
      *(uint32_t *)((int)local_220 + tmp_u2 + 0xc) = 0;
      tmp_u1 = tmp_u2 + 8;
    } while (tmp_u2 + 8 < 0x1f8);
    *(uint32_t *)((int)local_220 + tmp_u2 + 0x10) = 0;
    ptVar5 = local_220 + 1;
    Com_sprintf(ptVar5,0x200,"^9Nx^7AC ^5VIOLATION: ^5[%s]",
                *(uint32_t *)(NxAC_ViolationNames + tmp_i6 * 4));
  }
  else {
    if (*(int *)(NxAC_Violations + *(int *)(tmp_i4 + 0xb34) * 0xc + 4) != 2) goto LAB_00051068;
    local_220[1] = 0;
    tmp_u1 = 0;
    do {
      tmp_u2 = tmp_u1;
      *(uint32_t *)((int)local_220 + tmp_u2 + 8) = 0;
      *(uint32_t *)((int)local_220 + tmp_u2 + 0xc) = 0;
      tmp_u1 = tmp_u2 + 8;
    } while (tmp_u2 + 8 < 0x1f8);
    *(uint32_t *)((int)local_220 + tmp_u2 + 0x10) = 0;
    tVar3 = time(local_220);
    if (tVar3 == 0) {
      return;
    }
    tmp_i4 = AllocBan(1);
    if (tmp_i4 == 0) {
      return;
    }
    Q_strncpyz(tmp_i4,*(int *)(param_1 + 400) + 0x5f8,0x24);
    Q_strncpyz(tmp_i4 + 0x24,*(int *)(param_1 + 400) + 0x61c,0x21);
    Q_strncpyz(tmp_i4 + 0x4b4,*(int *)(param_1 + 400) + 0xaf4,0x12);
    Q_strncpyz(tmp_i4 + 0x45,*(int *)(param_1 + 400) + 0x653,0x12);
    __tp = localtime(local_220);
    strftime((char *)(tmp_i4 + 0x457),0x32,"%m/%d/%y %H:%M:%S",__tp);
    Q_strncpyz(tmp_i4 + 0x490,"NxAC_AutoBan",0x24);
    *(uint32_t *)(tmp_i4 + 0x48c) = 0;
    ptVar5 = local_220 + 1;
    Com_sprintf(ptVar5,0x200,"^9Nx^7AC ^5VIOLATION: ^5[%s]",
                *(uint32_t *)(NxAC_ViolationNames + *(int *)(*(int *)(param_1 + 400) + 0xb34) * 4)
               );
    tmp_i6 = 0;
    Q_strncpyz(tmp_i4 + 0x57,ptVar5,0x400);
    if (Bans != 0) {
      tmp_i6 = 0;
      do {
        tmp_i6 = tmp_i6 + 1;
      } while ((&Bans)[tmp_i6] != 0);
    }
    nitrox_SaveSingleBan(tmp_i4,1);
    (&Bans)[tmp_i6] = tmp_i4;
    NxAC_Log(param_1,1,1,"AUTOBAN]^5 Banned permanently - %s",
             *(uint32_t *)(NxAC_ViolationNames + *(int *)(*(int *)(param_1 + 400) + 0xb34) * 4));
    ptVar5 = (time_t *)va("^9Nx^7AC: You have been banned.\n%s",ptVar5);
  }
  trap_DropClient((param_1 + -0x93e4a0 >> 9) * -0x55555555,ptVar5,0);
  tmp_i4 = *(int *)(param_1 + 400);
LAB_00051068:
  *(uint32_t *)(tmp_i4 + 0xb3c) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb44) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb40) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb2c) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb38) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb30) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb34) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xf44) = 0;
  return;
}

void NxAC_CheckClient(int param_1)
{
  uint *tmp_pu1;
  uint tmp_u2;
  uint32_t tmp_u3;
  uint tmp_u4;
  int tmp_i5;
  int tmp_i6;
  char *tmp_pc7;
  int tmp_i8;
  uint32_t tmp_u9;
  uint32_t local_61c;
  uint32_t local_618 [386];
  
  tmp_u3 = GHIDRA_FIELD(n_NxAC, 12, 4);
  local_618[0x7f] = 0;
  tmp_u2 = 0;
  do {
    tmp_u4 = tmp_u2;
    *(uint32_t *)((int)local_618 + tmp_u4 + 0x200) = 0;
    *(uint32_t *)((int)local_618 + tmp_u4 + 0x204) = 0;
    tmp_u2 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0x3f8);
  *(uint32_t *)((int)local_618 + tmp_u4 + 0x208) = 0;
  local_61c = 0;
  tmp_u2 = 0;
  do {
    tmp_u4 = tmp_u2;
    *(uint32_t *)((int)local_618 + tmp_u4) = 0;
    *(uint32_t *)((int)local_618 + tmp_u4 + 4) = 0;
    tmp_u2 = tmp_u4 + 8;
  } while (tmp_u4 + 8 < 0x1f8);
  *(uint32_t *)((int)local_618 + tmp_u4 + 8) = 0;
  tmp_i5 = *(int *)(param_1 + 400);
  tmp_u2 = *(uint *)(tmp_i5 + 0xb2c);
  if (tmp_u2 == 0) {
    return;
  }
  tmp_u4 = *(uint *)(tmp_i5 + 0xb38);
  if (tmp_u2 == tmp_u4) {
    return;
  }
  if (NxAC_ViolationsCount < 2) {
LAB_000516b7:
    *(uint *)(tmp_i5 + 0xb38) = tmp_u2;
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xb34) = 0xffffffff;
  }
  else {
    if (((GHIDRA_FIELD(NxAC_Violations, 12, 4) & tmp_u2) == 0) || ((GHIDRA_FIELD(NxAC_Violations, 12, 4) & tmp_u4) != 0)) {
      if (NxAC_ViolationsCount == 2) goto LAB_000516b7;
      if (((GHIDRA_FIELD(NxAC_Violations, 24, 4) & tmp_u2) == 0) || ((GHIDRA_FIELD(NxAC_Violations, 24, 4) & tmp_u4) != 0)) {
        if ((NxAC_ViolationsCount == 3) ||
           (((GHIDRA_FIELD(NxAC_Violations, 36, 4) & tmp_u2) == 0 || ((GHIDRA_FIELD(NxAC_Violations, 36, 4) & tmp_u4) != 0))))
        goto LAB_000516b7;
        tmp_i6 = 3;
      }
      else {
        tmp_i6 = 2;
      }
    }
    else {
      tmp_i6 = 1;
    }
    tmp_i6 = *(int *)(NxAC_Violations + tmp_i6 * 0xc + 8);
    *(uint *)(tmp_i5 + 0xb38) = tmp_u2;
    if (((1 < tmp_i6) || (*(int *)(*(int *)(param_1 + 400) + 0xb34) = tmp_i6, tmp_i6 == 1)) &&
       (*(int *)(*(int *)(param_1 + 400) + 0xb30) != tmp_i6)) {
      *(int *)(*(int *)(param_1 + 400) + 0xb30) = tmp_i6;
      if (tmp_u3 == 2) {
        tmp_i5 = *(int *)(param_1 + 400);
        if (*(int *)(tmp_i5 + 0xb3c) == 0) {
          tmp_i6 = *(int *)(tmp_i5 + 0xb30);
          tmp_i8 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
          if (*(int *)(NxAC_Violations + tmp_i6 * 0xc + 4) != 0) {
            trap_SendServerCommand(tmp_i8,"getss 80");
            *(uint32_t *)(*(int *)(param_1 + 400) + 0xb40) =
                 *(uint32_t *)(*(int *)(param_1 + 400) + 0xb30);
            *(uint32_t *)(*(int *)(param_1 + 400) + 0xb44) =
                 *(uint32_t *)(*(int *)(param_1 + 400) + 0xb2c);
            *(uint32_t *)(*(int *)(param_1 + 400) + 0xb3c) = 1;
            tmp_i5 = *(int *)(param_1 + 400);
            tmp_i6 = *(int *)(tmp_i5 + 0xb30);
          }
        }
        else {
          tmp_i6 = *(int *)(tmp_i5 + 0xb30);
          tmp_i8 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        }
      }
      else {
        tmp_i5 = *(int *)(param_1 + 400);
        tmp_i8 = (param_1 + -0x93e4a0 >> 9) * -0x55555555;
        tmp_i6 = *(int *)(tmp_i5 + 0xb30);
      }
      tmp_u9 = *(uint32_t *)(NxAC_ViolationNames + tmp_i6 * 4);
      tmp_i6 = tmp_i5 + 0x634;
      Com_sprintf(&local_61c,0x200,"cpm \"^9Nx^7AC ^5Server - Slot #%i ^7%s^5 (%s) - [%s]\n\"",tmp_i8
                  ,tmp_i5 + 0x5f8,tmp_i6,tmp_u9);
      if (*(int *)(*(int *)(param_1 + 400) + 0xb3c) == 0) {
        tmp_pc7 = "";
      }
      else {
        tmp_pc7 = " (Screenshot requested)";
      }
      Com_sprintf(local_618 + 0x7f,0x400,"%s]^5%s",
                  *(uint32_t *)
                   (NxAC_ViolationNames + *(int *)(*(int *)(param_1 + 400) + 0xb30) * 4),tmp_pc7,
                  tmp_i6,tmp_u9);
      tmp_i5 = *(int *)(*(int *)(param_1 + 400) + 0xb30) * 0xc;
      if (*(int *)(NxAC_Violations + tmp_i5 + 4) != 0) {
        tmp_pu1 = (uint *)(*(int *)(param_1 + 400) + 0xf44);
        *tmp_pu1 = *tmp_pu1 | *(uint *)(NxAC_Violations + tmp_i5);
      }
      NxAC_Log(param_1,1,1,local_618 + 0x7f);
      trap_SendServerCommand(0xffffffff,&local_61c);
      if (((tmp_u3 == 2) <
           (0 < *(int *)(NxAC_Violations + *(int *)(*(int *)(param_1 + 400) + 0xb34) * 0xc + 4))) &&
         (GHIDRA_FIELD(n_NxAC, 12, 4) == 1)) {
        NxAC_BanClient(param_1);
      }
    }
  }
  return;
}

void NxAC_Log(int param_1,int param_2,int param_3,char *param_4)
{
  int tmp_i1;
  time_t tVar2;
  tm *__tp;
  uint tmp_u3;
  uint tmp_u4;
  uint32_t tmp_u5;
  uint *tmp_pu6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  int tmp_i9;
  uint *tmp_pu10;
  uint32_t local_820;
  uint local_81c [255];
  uint8_t auStack_41f [3];
  uint local_41c [258];
  uint32_t uStack_14;
  
  uStack_14 = 0x9167d;
  local_81c[0] = 0;
  tmp_u4 = 0;
  do {
    tmp_u3 = tmp_u4;
    *(uint32_t *)((int)local_81c + tmp_u3 + 4) = 0;
    *(uint32_t *)((int)local_81c + tmp_u3 + 8) = 0;
    tmp_u4 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0x3f8);
  *(uint32_t *)((int)local_81c + tmp_u3 + 0xc) = 0;
  local_41c[0] = 0;
  tmp_u4 = 0;
  do {
    tmp_u3 = tmp_u4;
    *(uint32_t *)((int)local_41c + tmp_u3 + 4) = 0;
    *(uint32_t *)((int)local_41c + tmp_u3 + 8) = 0;
    tmp_u4 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0x3f8);
  *(uint32_t *)((int)local_41c + tmp_u3 + 0xc) = 0;
  tVar2 = time(&local_820);
  tmp_pu7 = &g_unk_0026ea14;
  if (tVar2 != 0) {
    tmp_pu7 = tstr_14553;
    __tp = localtime(&local_820);
    strftime(tstr_14553,0x32,"%m-%d-%y %H:%M:%S",__tp);
  }
  Com_sprintf(local_81c,0x400,&g_unk_00249b72,tmp_pu7);
  tmp_pu6 = local_81c;
  do {
    tmp_pu10 = tmp_pu6;
    tmp_u3 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
    tmp_u4 = tmp_u3 & 0x80808080;
    tmp_pu6 = tmp_pu10 + 1;
  } while (tmp_u4 == 0);
  if ((tmp_u3 & 0x8080) == 0) {
    tmp_pu6 = (uint *)((int)tmp_pu10 + 6);
    tmp_u4 = tmp_u4 >> 0x10;
  }
  tmp_i8 = (int)tmp_pu6 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_81c);
  tmp_i9 = tmp_i8;
  if (param_3 != 0) {
    Q_strcat((int)local_81c + tmp_i8,0x400 - tmp_i8,"^1[VIOLATION::");
    tmp_pu6 = local_81c;
    do {
      tmp_pu10 = tmp_pu6;
      tmp_u3 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
      tmp_u4 = tmp_u3 & 0x80808080;
      tmp_pu6 = tmp_pu10 + 1;
    } while (tmp_u4 == 0);
    if ((tmp_u3 & 0x8080) == 0) {
      tmp_pu6 = (uint *)((int)tmp_pu10 + 6);
      tmp_u4 = tmp_u4 >> 0x10;
    }
    tmp_i9 = (int)tmp_pu6 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_81c);
  }
  vsnprintf((char *)(tmp_i9 + (int)local_81c),0x400 - tmp_i9,param_4,&stack0x00000014);
  tmp_pu6 = local_81c;
  do {
    tmp_pu10 = tmp_pu6;
    tmp_u3 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
    tmp_u4 = tmp_u3 & 0x80808080;
    tmp_pu6 = tmp_pu10 + 1;
  } while (tmp_u4 == 0);
  if ((tmp_u3 & 0x8080) == 0) {
    tmp_pu6 = (uint *)((int)tmp_pu10 + 6);
    tmp_u4 = tmp_u4 >> 0x10;
  }
  tmp_i9 = (int)tmp_pu6 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_81c);
  if (param_1 == 0) goto LAB_000918e7;
  tmp_i1 = *(int *)(param_1 + 400);
  tmp_pu6 = local_81c;
  if (tmp_i1 == 0) {
LAB_000919c4:
    do {
      tmp_pu10 = tmp_pu6 + 1;
      tmp_u4 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6 & 0x80808080;
      tmp_pu6 = tmp_pu10;
    } while (tmp_u4 == 0);
  }
  else {
    if (param_3 == 0) {
      tmp_u5 = va(" - Slot #%i ^7%s ^5(%s)",(param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_i1 + 0x5f8,
                 tmp_i1 + 0x634);
      Q_strcat(tmp_i9 + (int)local_81c,0x400 - tmp_i9,tmp_u5);
      goto LAB_000919c4;
    }
    tmp_u5 = va(" 0x%04X - Slot #%i ^7%s ^5(%s)",*(uint32_t *)(tmp_i1 + 0xb2c),
               (param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_i1 + 0x5f8,tmp_i1 + 0x634);
    Q_strcat(tmp_i9 + (int)local_81c,0x400 - tmp_i9,tmp_u5);
    if (*(int *)(param_1 + 400) == 0) {
      do {
        tmp_pu10 = tmp_pu6 + 1;
        tmp_u4 = *tmp_pu6 + 0xfefefeff & ~*tmp_pu6 & 0x80808080;
        tmp_pu6 = tmp_pu10;
      } while (tmp_u4 == 0);
    }
    else {
      NxAC_ReportToAdminchat(param_1,(int)local_81c + tmp_i8);
      tmp_pu10 = local_81c;
      do {
        tmp_u4 = *tmp_pu10;
        tmp_pu10 = tmp_pu10 + 1;
        tmp_u4 = tmp_u4 + 0xfefefeff & ~tmp_u4 & 0x80808080;
      } while (tmp_u4 == 0);
    }
  }
  if ((tmp_u4 & 0x8080) == 0) {
    tmp_pu10 = (uint *)((int)tmp_pu10 + 2);
    tmp_u4 = tmp_u4 >> 0x10;
  }
  tmp_i9 = (int)tmp_pu10 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_81c);
LAB_000918e7:
  if (*(char *)((int)&local_820 + tmp_i9 + 3) != '\n') {
    Q_strcat(local_81c,0x400,"\n");
  }
  DecolorString(local_81c,local_41c);
  if ((param_2 != 0) && (GHIDRA_FIELD(g_dedicated, 12, 4) != 0)) {
    G_Printf("[NxAC] %s",(int)local_41c + tmp_i8);
  }
  DecolorString(local_81c,local_41c);
  if (param_3 != 0) {
    tmp_i9 = trap_FS_FOpenFile("NxAC/NxAC_Violations.log",&local_820,2);
    tmp_pu6 = local_41c;
    if (tmp_i9 < 0) {
      return;
    }
    do {
      tmp_pu10 = tmp_pu6;
      tmp_u3 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
      tmp_u4 = tmp_u3 & 0x80808080;
      tmp_pu6 = tmp_pu10 + 1;
    } while (tmp_u4 == 0);
    if ((tmp_u3 & 0x8080) == 0) {
      tmp_pu6 = (uint *)((int)tmp_pu10 + 6);
      tmp_u4 = tmp_u4 >> 0x10;
    }
    trap_FS_Write(local_41c,
                  (int)tmp_pu6 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_41c),
                  local_820);
    trap_FS_FCloseFile(local_820);
  }
  tmp_pu6 = local_41c;
  if (g_unk_00abe8bc != 0) {
    do {
      tmp_pu10 = tmp_pu6;
      tmp_u3 = *tmp_pu10 + 0xfefefeff & ~*tmp_pu10;
      tmp_u4 = tmp_u3 & 0x80808080;
      tmp_pu6 = tmp_pu10 + 1;
    } while (tmp_u4 == 0);
    if ((tmp_u3 & 0x8080) == 0) {
      tmp_pu6 = (uint *)((int)tmp_pu10 + 6);
      tmp_u4 = tmp_u4 >> 0x10;
    }
    trap_FS_Write(local_41c,
                  (int)tmp_pu6 + ((-3 - (uint)CARRY1((byte)tmp_u4,(byte)tmp_u4)) - (int)local_41c),
                  g_unk_00abe8bc);
  }
  return;
}

void NxAC_CvarScanViolation(int param_1,int param_2,int param_3,uint32_t param_4)
{
  int *tmp_pi1;
  char tmp_c2;
  int tmp_i3;
  uint tmp_u4;
  uint tmp_u5;
  uint32_t tmp_u6;
  char *tmp_pc7;
  char *tmp_pc8;
  char *tmp_pc9;
  int local_420;
  uint32_t local_41c;
  uint32_t local_418 [257];
  uint32_t uStack_14;
  
  uStack_14 = 0x11effd;
  local_41c = 0;
  tmp_u4 = 0;
  do {
    tmp_u5 = tmp_u4;
    *(uint32_t *)((int)local_418 + tmp_u5) = 0;
    *(uint32_t *)((int)local_418 + tmp_u5 + 4) = 0;
    tmp_u4 = tmp_u5 + 8;
  } while (tmp_u5 + 8 < 0x3f8);
  *(uint32_t *)((int)local_418 + tmp_u5 + 8) = 0;
  tmp_i3 = (&CvarChecks)[param_3];
  if (*(char *)(tmp_i3 + 100) == '\0') {
    tmp_c2 = *(char *)(tmp_i3 + 0x44);
    tmp_pc7 = "";
  }
  else {
    tmp_c2 = *(char *)(tmp_i3 + 0x44);
    tmp_pc7 = "\'";
  }
  if (tmp_c2 == '\0') {
    tmp_pc9 = "";
  }
  else {
    tmp_pc9 = "\'";
  }
  Com_sprintf(&local_41c,0x400,"CVARSCAN]^5 \'%s\' IS \'%s\' SHOULD BE %s %s%s%s%s%s%s",tmp_i3,
              param_4,*(uint32_t *)(NxAC_CvarRulesStr + *(int *)(tmp_i3 + 0x40) * 4),tmp_pc9,
              tmp_i3 + 0x44,tmp_pc9,tmp_pc7,tmp_i3 + 100,tmp_pc7);
  NxAC_Log(param_1,1,1,&local_41c);
  tmp_i3 = (&CvarChecks)[param_3];
  if (param_2 == 0) {
    if (*(char *)(tmp_i3 + 100) == '\0') {
      tmp_pc7 = "";
    }
    else {
      tmp_pc7 = "\'";
    }
    if (*(char *)(tmp_i3 + 0x44) == '\0') {
      tmp_pc9 = "";
    }
    else {
      tmp_pc9 = "\'";
    }
    tmp_u6 = va("cpm \"^9Nx^7AC: ^1CVAR_VIOLATION ^7\'%s\' IS \'%s\' SHOULD BE %s %s%s%s%s%s%s\n\"",
               tmp_i3,param_4,*(uint32_t *)(NxAC_CvarRulesStr + *(int *)(tmp_i3 + 0x40) * 4),tmp_pc9,
               tmp_i3 + 0x44,tmp_pc9,tmp_pc7,tmp_i3 + 100,tmp_pc7);
    trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6);
    tmp_pi1 = (int *)(*(int *)(param_1 + 400) + 0xb28);
    *tmp_pi1 = *tmp_pi1 + 1;
    return;
  }
  if (*(char *)(tmp_i3 + 100) == '\0') {
    tmp_pc7 = "";
    tmp_pc9 = tmp_pc7;
  }
  else {
    tmp_pc7 = "\'";
    tmp_pc9 = " \'";
  }
  local_420 = tmp_i3 + 100;
  if (*(char *)(tmp_i3 + 0x44) == '\0') {
    tmp_pc8 = "";
  }
  else {
    tmp_pc8 = "\'";
  }
  tmp_u6 = va("\n^7^9Nx^7AC: CVAR_VIOLATION\n\'%s\' IS \'%s\' SHOULD BE %s %s%s%s%s%s%s\n\"",tmp_i3,
             param_4,*(uint32_t *)(NxAC_CvarRulesStr + *(int *)(tmp_i3 + 0x40) * 4),tmp_pc8,
             tmp_i3 + 0x44,tmp_pc8,tmp_pc9,local_420,tmp_pc7);
  trap_DropClient((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u6,0);
  nitrox_NxAC_ReportCvarViolationToMaster(param_1,param_3,param_4);
  return;
}

void NxAC_ReportToAdminchat(uint8_t *param_1,uint32_t param_2)
{
  uint8_t *tmp_pu1;
  uint tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  uint32_t *tmp_pu6;
  int tmp_i7;
  char *tmp_pc8;
  uint32_t local_21c;
  uint32_t local_218 [129];
  uint32_t uStack_14;
  
  uStack_14 = 0x11f2fd;
  local_21c = 0;
  tmp_u2 = 0;
  do {
    tmp_u3 = tmp_u2;
    *(uint32_t *)((int)local_218 + tmp_u3) = 0;
    *(uint32_t *)((int)local_218 + tmp_u3 + 4) = 0;
    tmp_u2 = tmp_u3 + 8;
  } while (tmp_u3 + 8 < 0x1f8);
  *(uint32_t *)((int)local_218 + tmp_u3 + 8) = 0;
  tmp_pc8 = "lc \"^9Nx^7AC %s\" -2";
  Com_sprintf(&local_21c,0x200,"lc \"^9Nx^7AC %s\" -2",param_2);
  tmp_pu6 = &level;
  if (0 < g_unk_00abe938) {
    tmp_i7 = 0;
    tmp_i5 = g_unk_00abe938;
    do {
      tmp_i4 = tmp_pu6[tmp_i7 + 0x29] * 0x600;
      if (((g_entities[tmp_i4 + 0x128] & 8) == 0) && (*(int *)(g_entities + tmp_i4 + 400) != 0)) {
        if (*(int *)(*(int *)(g_entities + tmp_i4 + 400) + 0x54d8) != 0) {
          return;
        }
        tmp_pu1 = g_entities + tmp_i4;
        if (tmp_pu1 != param_1) {
          tmp_i5 = nitrox_CheckPermission(tmp_pu1,0xd);
          if (tmp_i5 != 0) {
            tmp_i5 = (tmp_i4 >> 9) * -0x55555555;
            trap_SendServerCommand(tmp_i5,"pop \"^8/!\\ ^9Nx^7AC ^3WARNING!\"",tmp_pc8,param_2,tmp_i5);
            trap_SendServerCommand(tmp_i5,&local_21c);
            tmp_pc8 = (char *)0x0;
            G_AddEvent(tmp_pu1,0x62);
          }
          tmp_i5 = tmp_pu6[0x26];
        }
      }
      tmp_i7 = tmp_i7 + 1;
    } while (tmp_i7 < tmp_i5);
  }
  return;
}

int NxAC_LoadChecksums(void)
{
  bool tmp_b1;
  int tmp_i2;
  char *tmp_pc3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  uint8_t *tmp_pu6;
  uint32_t local_24;
  void *local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0x12149d;
  CheckSumsCount = 0;
  tmp_i2 = trap_FS_FOpenFile("NxAC/checksums.cfg",&local_24,0);
  if (tmp_i2 < 0) {
    NxAC_Log(0,1,0,"/!\\ [LoadChecksumList] Couldn\'t open \"NxAC/checksums.cfg\" file.");
    return 0;
  }
  local_20[0] = malloc(tmp_i2 + 1);
  trap_FS_Read(local_20[0],tmp_i2,local_24);
  *(uint8_t *)((int)local_20[0] + tmp_i2) = 0;
  tmp_pc3 = (char *)COM_Parse(local_20);
  if (*tmp_pc3 == '\0') {
LAB_0012167c:
    free(local_20[0]);
    trap_FS_FCloseFile(local_24);
  }
  else {
    if (CheckSumsCount < 0x40) {
      do {
        if (CheckSumsCount < 1) {
LAB_00121650:
          Q_strncpyz(&CheckSums + CheckSumsCount * 0x29,tmp_pc3,0x29);
          CheckSumsCount = CheckSumsCount + 1;
        }
        else {
          tmp_i2 = 0;
          tmp_b1 = false;
          tmp_pu6 = &CheckSums;
          do {
            while( true ) {
              tmp_i4 = Q_stricmp(tmp_pu6,tmp_pc3);
              if (tmp_i4 != 0) break;
              tmp_i2 = tmp_i2 + 1;
              tmp_pu6 = tmp_pu6 + 0x29;
              NxAC_Log(0,1,0,
                       "/!\\ [LoadChecksumList] WARNING - SHA1 Checksum \'%s\' already loaded\n",
                       tmp_pc3);
              tmp_b1 = true;
              if (CheckSumsCount <= tmp_i2) goto LAB_001215bc;
            }
            tmp_i2 = tmp_i2 + 1;
            tmp_pu6 = tmp_pu6 + 0x29;
          } while (tmp_i2 < CheckSumsCount);
LAB_001215bc:
          if (!tmp_b1) goto LAB_00121650;
        }
        tmp_pc3 = (char *)COM_Parse(local_20);
        if (*tmp_pc3 == '\0') goto LAB_0012167c;
      } while (CheckSumsCount < 0x40);
    }
    NxAC_Log(0,1,0,"/!\\ [LoadChecksumList] MAX_CHECKSUMS(64) EXCEEDED");
  }
  tmp_pu5 = &g_unk_0024e6ea;
  if (CheckSumsCount < 2) {
    tmp_pu5 = &g_unk_0026ea14;
  }
  G_LogPrintf("| [NxAC::LoadChecksums] Loaded %d allowed client SHA1 checksum%s\n",CheckSumsCount,
              tmp_pu5);
  return CheckSumsCount;
}

void NxAC_ClearChecksumList(void)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  
  if (0 < CheckSumsCount) {
    tmp_pu2 = &CheckSums;
    tmp_i1 = CheckSumsCount * 0x29;
    do {
      *tmp_pu2 = 0;
      tmp_pu2 = tmp_pu2 + 0x29;
    } while (tmp_pu2 != &CheckSums + tmp_i1);
  }
  return;
}

uint32_t NxAC_VerifyChecksum(char *param_1)
{
  size_t tmp_s1;
  int tmp_i2;
  uint8_t *tmp_pu3;
  int tmp_i4;
  
  tmp_s1 = strlen(param_1);
  if ((tmp_s1 == 0x28) && (0 < CheckSumsCount)) {
    tmp_pu3 = &CheckSums;
    tmp_i4 = 0;
    do {
      tmp_i2 = Q_stricmp(tmp_pu3,param_1);
      if (tmp_i2 == 0) {
        return 1;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_pu3 = tmp_pu3 + 0x29;
    } while (tmp_i4 < CheckSumsCount);
  }
  return 0;
}

int NxAC_LoadCvarList(void)
{
  char tmp_c1;
  bool tmp_b2;
  void *__ptr;
  int tmp_i3;
  char *tmp_pc4;
  int tmp_i5;
  uint8_t *__ptr_00;
  uint32_t tmp_u6;
  uint8_t *tmp_pu7;
  int *tmp_pi8;
  uint32_t local_24;
  void *local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0x1217ab;
  CvarChecksCount = 0;
  if (CvarChecks != (void *)0x0) {
    __ptr = CvarChecks;
    tmp_pi8 = (int *)&CvarChecks;
    do {
      free(__ptr);
      *tmp_pi8 = 0;
      __ptr = (void *)tmp_pi8[1];
      tmp_pi8 = tmp_pi8 + 1;
    } while (__ptr != (void *)0x0);
  }
  tmp_i3 = trap_FS_FOpenFile("NxAC/cvarlist.cfg",&local_24,0);
  if (tmp_i3 < 0) {
    NxAC_Log(0,1,0,"/!\\ [LoadCvarList] Couldn\'t open \"NxAC/cvarlist.cfg\" file.");
    return 0;
  }
  local_20[0] = malloc(tmp_i3 + 1);
  trap_FS_Read(local_20[0],tmp_i3,local_24);
  *(uint8_t *)((int)local_20[0] + tmp_i3) = 0;
  tmp_pc4 = (char *)COM_Parse(local_20);
LAB_00121851:
  tmp_c1 = *tmp_pc4;
joined_r0x00121854:
  if (tmp_c1 == '\0') {
    free(local_20[0]);
    trap_FS_FCloseFile(local_24);
    tmp_pu7 = &g_unk_0024e6ea;
    if (CvarChecksCount < 2) {
      tmp_pu7 = &g_unk_0026ea14;
    }
    G_LogPrintf("| [NxAC::LoadCvarList] Loaded %d cvar restriction%s\n",CvarChecksCount,tmp_pu7);
    return CvarChecksCount;
  }
  if (0x1ff < CvarChecksCount) {
    NxAC_Log(0,1,0,"/!\\ [LoadCvarList] NXAC_MAX_CVARCHECKS EXCEEDED");
    tmp_pu7 = &g_unk_0024e6ea;
    if (CvarChecksCount < 2) {
      tmp_pu7 = &g_unk_0026ea14;
    }
    G_LogPrintf("| [NxAC::LoadCvarList] Loaded %d cvar restriction%s\n",CvarChecksCount,tmp_pu7);
    return 0;
  }
  if (0 < CvarChecksCount) {
    tmp_i3 = 0;
    tmp_b2 = false;
    do {
      while (tmp_i5 = Q_stricmp((&CvarChecks)[tmp_i3],tmp_pc4), tmp_i5 != 0) {
        tmp_i3 = tmp_i3 + 1;
        if (CvarChecksCount <= tmp_i3) goto LAB_001218e1;
      }
      tmp_i3 = tmp_i3 + 1;
      NxAC_Log(0,1,0,"/!\\ [LoadCvarList] restriction already loaded for cvar %s\n",tmp_pc4);
      SkipRestOfLine(local_20);
      tmp_b2 = true;
    } while (tmp_i3 < CvarChecksCount);
LAB_001218e1:
    if (!tmp_b2) goto LAB_001218ed;
    goto LAB_0012196d;
  }
LAB_001218ed:
  __ptr_00 = malloc(0x84);
  *__ptr_00 = 0;
  __ptr_00[0x44] = 0;
  __ptr_00[100] = 0;
  *(uint32_t *)(__ptr_00 + 0x40) = 10;
  Q_strncpyz(__ptr_00,tmp_pc4,0x40);
  tmp_u6 = COM_ParseExt(local_20,0);
  tmp_i3 = Q_stricmp(tmp_u6,"NULL");
  if (tmp_i3 == 0) {
    *(uint32_t *)(__ptr_00 + 0x40) = 0;
  }
  else {
    tmp_i3 = Q_stricmp(tmp_u6,&g_unk_00258bdd);
    if (tmp_i3 == 0) {
      *(uint32_t *)(__ptr_00 + 0x40) = 1;
LAB_001219f9:
      tmp_u6 = COM_ParseExt(local_20,0);
      Q_strncpyz(__ptr_00 + 0x44,tmp_u6,0x20);
    }
    else {
      tmp_i3 = Q_stricmp(tmp_u6,&g_unk_0023ae6b);
      if (tmp_i3 == 0) {
        *(uint32_t *)(__ptr_00 + 0x40) = 2;
      }
      else {
        tmp_i3 = Q_stricmp(tmp_u6,&g_unk_00258c0d);
        if (tmp_i3 != 0) {
          tmp_i3 = Q_stricmp(tmp_u6,"G");
          if (tmp_i3 == 0) {
            *(uint32_t *)(__ptr_00 + 0x40) = 4;
          }
          else {
            tmp_i3 = Q_stricmp(tmp_u6,"GE");
            if (tmp_i3 == 0) {
              *(uint32_t *)(__ptr_00 + 0x40) = 5;
            }
            else {
              tmp_i3 = Q_stricmp(tmp_u6,"L");
              if (tmp_i3 == 0) {
                *(uint32_t *)(__ptr_00 + 0x40) = 6;
              }
              else {
                tmp_i3 = Q_stricmp(tmp_u6,&g_unk_00261b56);
                if (tmp_i3 == 0) {
                  *(uint32_t *)(__ptr_00 + 0x40) = 7;
                  goto LAB_001219f9;
                }
                tmp_i3 = Q_stricmp(tmp_u6,&g_unk_00258c19);
                if (tmp_i3 == 0) {
                  *(uint32_t *)(__ptr_00 + 0x40) = 8;
                }
                else {
                  tmp_i3 = Q_stricmp(tmp_u6,&g_unk_00258c25);
                  if (tmp_i3 != 0) goto LAB_00121c6c;
                  *(uint32_t *)(__ptr_00 + 0x40) = 9;
                }
              }
            }
          }
          goto LAB_001219f9;
        }
        *(uint32_t *)(__ptr_00 + 0x40) = 3;
      }
      tmp_u6 = COM_ParseExt(local_20,0);
      Q_strncpyz(__ptr_00 + 0x44,tmp_u6,0x20);
      tmp_u6 = COM_ParseExt(local_20,0);
      Q_strncpyz(__ptr_00 + 100,tmp_u6,0x20);
    }
  }
  (&CvarChecks)[CvarChecksCount] = __ptr_00;
  CvarChecksCount = CvarChecksCount + 1;
LAB_0012196d:
  tmp_pc4 = (char *)COM_Parse(local_20);
  tmp_c1 = *tmp_pc4;
  goto joined_r0x00121854;
LAB_00121c6c:
  NxAC_Log(0,1,0,"/!\\ [LoadCvarList] WARNING - Invalid cvar rule (%s) for cvar \"%s\"\n",tmp_u6,
           __ptr_00);
  free(__ptr_00);
  SkipRestOfLine(local_20);
  tmp_pc4 = (char *)COM_Parse(local_20);
  goto LAB_00121851;
}

void NxAC_ClearCvarList(void)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (0 < CvarChecksCount) {
    tmp_i2 = 0;
    do {
      tmp_i3 = tmp_i2 + 1;
      free((void *)(&CvarChecks)[tmp_i2]);
      tmp_i1 = CvarChecksCount;
      (&CvarChecks)[tmp_i2] = 0;
      tmp_i2 = tmp_i3;
    } while (tmp_i3 < tmp_i1);
  }
  return;
}

void NxAC_ScanClientCvars(int param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_i2 = CvarChecksCount;
  if ((GHIDRA_FIELD(n_NxAC_CvarScan, 12, 4) != 0) && (CvarChecksCount != 0)) {
    if (param_2 == 0) {
      *(uint32_t *)(*(int *)(param_1 + 400) + 0xb14) = 0;
      *(int *)(*(int *)(param_1 + 400) + 0xb18) = tmp_i2;
      *(uint32_t *)(*(int *)(param_1 + 400) + 0xb24) = 0;
      *(uint32_t *)(*(int *)(param_1 + 400) + 0xb20) = 0;
    }
    *(uint32_t *)(*(int *)(param_1 + 400) + 0xb10) = 0;
    tmp_i2 = *(int *)(param_1 + 400);
    if (param_2 < *(int *)(tmp_i2 + 0xb18)) {
      tmp_u1 = va("cvs %i %s\n",param_2,(&CvarChecks)[param_2]);
      trap_SendServerCommand((param_1 + -0x93e4a0 >> 9) * -0x55555555,tmp_u1);
      tmp_i2 = *(int *)(param_1 + 400);
    }
    *(uint32_t *)(tmp_i2 + 0xb1c) = g_unk_00abe908;
    return;
  }
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb14) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb18) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb24) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb20) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb10) = 0;
  *(uint32_t *)(*(int *)(param_1 + 400) + 0xb1c) = 0;
  return;
}

void NxAC_Init(void)
{
  int tmp_i1;
  
  G_LogPrintf("-----------------------------------\n");
  G_LogPrintf("| [NxAC::Initialize] Initializing...\n");
  tmp_i1 = nitrox_CreateDirectory(&g_unk_0024ae16);
  if (tmp_i1 == 0) {
    G_LogPrintf("! [NxAC::Initialize] NxAC Initialization failed!\n");
    g_unk_02b9a330 = 0;
    return;
  }
  trap_FS_FOpenFile("NxAC/NxAC.log",&g_unk_00abe8bc,3);
  if (g_unk_00abe8bc == 0) {
    G_LogPrintf("! [NxAC::Initialize] WARNING: Couldn\'t open logfile \'NxAC/NxAC.log\'\n");
  }
  NxAC_LoadCvarList();
  NxAC_LoadChecksums();
  tmp_i1 = nitrox_CreateScreenshotsFolder();
  if (tmp_i1 == 0) {
    G_LogPrintf("! [NxAC::Initialize] WARNING: Couldn\'t create/read \'NxAC\\screenshots\' folder\n"
               );
    G_LogPrintf("! [NxAC::Initialize] Remote screenshots disabled for the current game session.\n");
  }
  g_unk_02b9a334 = (uint)(tmp_i1 != 0);
  G_LogPrintf("| [NxAC::Initialize] Done!\n");
  g_unk_02b9a330 = 1;
  return;
}

bool NxAC_ClientActiveFileTransfer(int param_1)
{
  return 0 < (int)(&g_unk_02e62630)[param_1 * 0x1058];
}

void NxAC_ClearClientFileHandle(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  
  tmp_i1 = param_1 * 0x4160;
  tmp_u2 = 0;
  do {
    *(uint32_t *)(&g_unk_02e62624 + tmp_u2 + tmp_i1) = 0;
    *(uint32_t *)(tmp_i1 + 0x2e62628 + tmp_u2) = 0;
    tmp_u2 = tmp_u2 + 8;
  } while (tmp_u2 < 0x138);
  *(uint32_t *)(&g_unk_02e62624 + tmp_u2 + tmp_i1) = 0;
  *(uint8_t *)(&g_unk_02e62638 + param_1 * 0x20b0) = 0;
  (&g_unk_02e6265d)[param_1 * 0x4160] = 0;
  if (*(void **)(&g_unk_02e62624 + param_1 * 0x4160) != (void *)0x0) {
    free(*(void **)(&g_unk_02e62624 + param_1 * 0x4160));
  }
  *(uint32_t *)(&g_unk_02e62624 + param_1 * 0x4160) = 0;
  return;
}

uint NxAC_UpdateClientFileHandleBuffer(int param_1,uint32_t *param_2,uint param_3)
{
  uint8_t tmp_u1;
  uint16_t tmp_u2;
  uint32_t tmp_u3;
  int tmp_i4;
  void *pvVar5;
  uint32_t *tmp_pu6;
  uint tmp_u7;
  uint32_t *tmp_pu8;
  uint32_t *tmp_pu9;
  byte tmp_b10;
  
  tmp_b10 = 0;
  tmp_i4 = param_1 * 0x4160;
  pvVar5 = realloc(*(void **)(&g_unk_02e62624 + tmp_i4),
                   param_3 + 1 + *(int *)((int)&g_unk_02e62625 + tmp_i4 + 3));
  *(void **)(&g_unk_02e62624 + tmp_i4) = pvVar5;
  if (pvVar5 == (void *)0x0) {
    param_3 = 0;
  }
  else {
    tmp_pu6 = (uint32_t *)((int)pvVar5 + *(int *)((int)&g_unk_02e62625 + tmp_i4 + 3));
    tmp_u7 = param_3;
    if (7 < param_3) {
      tmp_pu8 = tmp_pu6;
      if (((uint)tmp_pu6 & 1) != 0) {
        tmp_u1 = *(uint8_t *)param_2;
        tmp_pu8 = (uint32_t *)((int)tmp_pu6 + 1);
        param_2 = (uint32_t *)((int)param_2 + 1);
        tmp_u7 = param_3 - 1;
        *(uint8_t *)tmp_pu6 = tmp_u1;
      }
      tmp_pu9 = tmp_pu8;
      if (((uint)tmp_pu8 & 2) != 0) {
        tmp_u2 = *(uint16_t *)param_2;
        tmp_pu9 = (uint32_t *)((int)tmp_pu8 + 2);
        param_2 = (uint32_t *)((int)param_2 + 2);
        tmp_u7 = tmp_u7 - 2;
        *(uint16_t *)tmp_pu8 = tmp_u2;
      }
      tmp_pu6 = tmp_pu9;
      if (((uint)tmp_pu9 & 4) != 0) {
        tmp_u3 = *param_2;
        tmp_pu6 = tmp_pu9 + 1;
        param_2 = param_2 + 1;
        tmp_u7 = tmp_u7 - 4;
        *tmp_pu9 = tmp_u3;
      }
    }
    for (; tmp_u7 != 0; tmp_u7 = tmp_u7 - 1) {
      *(uint8_t *)tmp_pu6 = *(uint8_t *)param_2;
      param_2 = (uint32_t *)((int)param_2 + (uint)tmp_b10 * -2 + 1);
      tmp_pu6 = (uint32_t *)((int)tmp_pu6 + (uint)tmp_b10 * -2 + 1);
    }
    param_1 = param_1 * 0x4160;
    tmp_i4 = *(int *)((int)&g_unk_02e62625 + param_1 + 3) + param_3;
    *(int *)((int)&g_unk_02e62625 + param_1 + 3) = tmp_i4;
    *(uint8_t *)(*(int *)(&g_unk_02e62624 + param_1) + tmp_i4) = 0;
  }
  return param_3;
}

