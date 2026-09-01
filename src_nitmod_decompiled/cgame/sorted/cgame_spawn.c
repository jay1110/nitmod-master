/* Recovered map-entity spawn handlers — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_spawn.h"

void SP_trigger_objective_info(void)
{
  int tmp_i1;
  char *tmp_pc2;
  int tmp_i3;
  char *tmp_pc4;
  bool tmp_b5;
  byte tmp_b6;
  
  tmp_b6 = 0;
  if (GHIDRA_FIELD(cgs, 27388, 4) == 8) {
    return;
  }
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b5 = true;
    do {
      tmp_i3 = 0xb;
      tmp_pc2 = "infoAllied";
      tmp_pc4 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_b5 = *tmp_pc2 == *tmp_pc4;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b6 * -2 + 1;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
      } while (tmp_b5);
      if (tmp_b5) {
        tmp_pc2 = (char *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c23ce;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b5 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b5);
  }
  tmp_pc2 = "^1No Text Supplied";
LAB_000c23ce:
  Q_strncpyz(g_unk_010b16f8 * 0x100 + 0x10b16fc,tmp_pc2,0x100);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b5 = true;
    do {
      tmp_i3 = 9;
      tmp_pc2 = "infoAxis";
      tmp_pc4 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_b5 = *tmp_pc2 == *tmp_pc4;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b6 * -2 + 1;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b6 * -2 + 1;
      } while (tmp_b5);
      if (tmp_b5) {
        tmp_pc2 = (char *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c244e;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b5 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b5);
  }
  tmp_pc2 = "^1No Text Supplied";
LAB_000c244e:
  Q_strncpyz(g_unk_010b16f8 * 0x100 + 0x10b28fc,tmp_pc2,0x100);
  g_unk_010b16f8 = g_unk_010b16f8 + 1;
  return;
}

void SP_path_corner_2(void)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  char *tmp_pc4;
  char *tmp_pc5;
  bool tmp_b6;
  byte tmp_b7;
  char *local_38;
  float local_28;
  float local_24;
  float local_20 [3];
  uint32_t uStack_14;
  
  tmp_b7 = 0;
  uStack_14 = 0xc24c9;
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
    if (0 < g_unk_010ab34c) goto LAB_000c24fc;
    if (g_unk_010ab348 != 0) goto LAB_000c278e;
    local_38 = "";
LAB_000c25e6:
    CG_Error("CG_SpawnString() called while not spawning");
    if (0 < g_unk_010ab34c) goto LAB_000c2546;
  }
  else {
    if (g_unk_010ab34c < 1) {
LAB_000c278e:
      local_38 = "";
      tmp_pu2 = &g_unk_0011e953;
      goto LAB_000c257e;
    }
LAB_000c24fc:
    tmp_i1 = 0;
    tmp_b6 = true;
    do {
      tmp_i3 = 0xb;
      tmp_pc4 = "targetname";
      tmp_pc5 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_b6 = *tmp_pc4 == *tmp_pc5;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b7 * -2 + 1;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
      } while (tmp_b6);
      if (tmp_b6) {
        local_38 = (char *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c253a;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b6 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b6);
    local_38 = "";
LAB_000c253a:
    if (g_unk_010ab348 == 0) goto LAB_000c25e6;
LAB_000c2546:
    tmp_i1 = 0;
    tmp_b6 = true;
    do {
      tmp_i3 = 7;
      tmp_pc4 = "origin";
      tmp_pc5 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_b6 = *tmp_pc4 == *tmp_pc5;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b7 * -2 + 1;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
      } while (tmp_b6);
      if (tmp_b6) {
        tmp_pu2 = (uint8_t *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c257e;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b6 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b6);
  }
  tmp_pu2 = &g_unk_0011e953;
LAB_000c257e:
  __isoc99_sscanf(tmp_pu2,&g_unk_0011e959,&local_28,&local_24,local_20);
  if (*local_38 != '\0') {
LAB_000c25b9:
    if (numPathCorners < 0x200) {
      BG_AddPathCorner(local_38,&local_28);
      return;
    }
    CG_Error("Maximum path_corners hit\n");
    return;
  }
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b6 = true;
    do {
      tmp_i3 = 5;
      tmp_pc4 = "name";
      tmp_pc5 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i3 == 0) break;
        tmp_i3 = tmp_i3 + -1;
        tmp_b6 = *tmp_pc4 == *tmp_pc5;
        tmp_pc4 = tmp_pc4 + (uint)tmp_b7 * -2 + 1;
        tmp_pc5 = tmp_pc5 + (uint)tmp_b7 * -2 + 1;
      } while (tmp_b6);
      if (tmp_b6) {
        local_38 = (char *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c25b9;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b6 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b6);
  }
  tmp_i1 = index_11986 * 0x20;
  index_11986 = index_11986 + 1 & 7;
  Com_sprintf(str_11987 + tmp_i1,0x20,"(%i %i %i)",(int)ROUND(local_28),(int)ROUND(local_24),
              (int)ROUND(local_20[0]));
  CG_Error("path_corner_2 with no targetname at %s\n",str_11987 + tmp_i1);
  return;
}

void SP_info_train_spline_main(void)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  char *tmp_pc3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  char *tmp_pc7;
  bool tmp_b8;
  byte tmp_b9;
  uint8_t *tmp_pu10;
  int local_40;
  float *local_38;
  uint8_t *local_34;
  float local_28;
  float local_24;
  float local_20 [3];
  uint32_t uStack_14;
  
  tmp_b9 = 0;
  uStack_14 = 0xc27b9;
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b8 = true;
    do {
      tmp_i5 = 7;
      tmp_pc3 = "origin";
      tmp_pc7 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i5 == 0) break;
        tmp_i5 = tmp_i5 + -1;
        tmp_b8 = *tmp_pc3 == *tmp_pc7;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b9 * -2 + 1;
        tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
      } while (tmp_b8);
      if (tmp_b8) {
        tmp_pu10 = &g_unk_0011e959;
        __isoc99_sscanf((&g_unk_010ab354)[tmp_i1 * 2],&g_unk_0011e959,&local_28,&local_24,local_20);
        goto joined_r0x000c2928;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b8 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b8);
  }
  tmp_pu10 = &g_unk_0011e959;
  __isoc99_sscanf(&g_unk_0011e953,&g_unk_0011e959,&local_28,&local_24,local_20);
  CG_Error("info_train_spline_main with no origin\n");
joined_r0x000c2928:
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
    if (g_unk_010ab34c < 1) {
      if (g_unk_010ab348 != 0) goto LAB_000c2964;
LAB_000c2ccb:
      CG_Error("CG_SpawnString() called while not spawning");
      if (g_unk_010ab34c < 1) goto LAB_000c2964;
    }
    else {
LAB_000c2878:
      tmp_i1 = 0;
      tmp_b8 = true;
      do {
        tmp_i5 = 0xb;
        tmp_pc3 = "targetname";
        tmp_pc7 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
        do {
          if (tmp_i5 == 0) break;
          tmp_i5 = tmp_i5 + -1;
          tmp_b8 = *tmp_pc3 == *tmp_pc7;
          tmp_pc3 = tmp_pc3 + (uint)tmp_b9 * -2 + 1;
          tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
        } while (tmp_b8);
        if (tmp_b8) {
          local_34 = (uint8_t *)(&g_unk_010ab354)[tmp_i1 * 2];
          if (g_unk_010ab348 == 0) goto LAB_000c2a03;
          goto LAB_000c2a23;
        }
        tmp_i1 = tmp_i1 + 1;
        tmp_b8 = tmp_i1 == g_unk_010ab34c;
      } while (!tmp_b8);
      if (g_unk_010ab348 == 0) goto LAB_000c2ccb;
    }
    tmp_i1 = 0;
    tmp_b8 = true;
    do {
      tmp_i5 = 5;
      tmp_pc3 = "name";
      tmp_pc7 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i5 == 0) break;
        tmp_i5 = tmp_i5 + -1;
        tmp_b8 = *tmp_pc3 == *tmp_pc7;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b9 * -2 + 1;
        tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
      } while (tmp_b8);
      if (tmp_b8) {
        local_34 = (uint8_t *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c29ff;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b8 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b8);
  }
  else if (0 < g_unk_010ab34c) goto LAB_000c2878;
LAB_000c2964:
  tmp_pu10 = str_11987 + index_11986 * 0x20;
  index_11986 = index_11986 + 1 & 7;
  Com_sprintf(tmp_pu10,0x20,"(%i %i %i)",(int)ROUND(local_28),(int)ROUND(local_24),
              (int)ROUND(local_20[0]));
  CG_Error("info_train_spline_main with no targetname at %s\n",tmp_pu10);
  local_34 = &g_unk_0011d841;
LAB_000c29ff:
  if (g_unk_010ab348 == 0) {
LAB_000c2a03:
    CG_Error("CG_SpawnString() called while not spawning",tmp_pu10);
  }
  if (0 < g_unk_010ab34c) {
LAB_000c2a23:
    tmp_i1 = 0;
    tmp_b8 = true;
    do {
      tmp_i5 = 7;
      tmp_pc3 = "target";
      tmp_pc7 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i5 == 0) break;
        tmp_i5 = tmp_i5 + -1;
        tmp_b8 = *tmp_pc3 == *tmp_pc7;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b9 * -2 + 1;
        tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
      } while (tmp_b8);
      if (tmp_b8) {
        tmp_pu2 = (uint8_t *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c2a5e;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b8 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b8);
  }
  tmp_pu2 = &g_unk_0011d841;
LAB_000c2a5e:
  local_38 = &local_28;
  tmp_i1 = BG_AddSplinePath(local_34,tmp_pu2,local_38);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
    if (0 < g_unk_010ab34c) goto LAB_000c2a96;
    if (g_unk_010ab348 != 0) goto LAB_000c2ad6;
LAB_000c2c94:
    CG_Error("CG_SpawnString() called while not spawning");
    if (g_unk_010ab34c < 1) goto LAB_000c2ad6;
  }
  else {
    if (g_unk_010ab34c < 1) goto LAB_000c2ad6;
LAB_000c2a96:
    tmp_i5 = 0;
    tmp_b8 = true;
    do {
      tmp_i6 = 4;
      tmp_pc3 = "end";
      tmp_pc7 = (char *)(&g_unk_010ab350)[tmp_i5 * 2];
      do {
        if (tmp_i6 == 0) break;
        tmp_i6 = tmp_i6 + -1;
        tmp_b8 = *tmp_pc3 == *tmp_pc7;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b9 * -2 + 1;
        tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
      } while (tmp_b8);
      if (tmp_b8) {
        *(uint32_t *)(tmp_i1 + 0x390) = 1;
        goto LAB_000c2ad6;
      }
      tmp_i5 = tmp_i5 + 1;
      tmp_b8 = tmp_i5 == g_unk_010ab34c;
    } while (!tmp_b8);
    if (g_unk_010ab348 == 0) goto LAB_000c2c94;
  }
  tmp_i5 = 0;
  tmp_b8 = true;
  do {
    tmp_i6 = 6;
    tmp_pc3 = "start";
    tmp_pc7 = (char *)(&g_unk_010ab350)[tmp_i5 * 2];
    do {
      if (tmp_i6 == 0) break;
      tmp_i6 = tmp_i6 + -1;
      tmp_b8 = *tmp_pc3 == *tmp_pc7;
      tmp_pc3 = tmp_pc3 + (uint)tmp_b9 * -2 + 1;
      tmp_pc7 = tmp_pc7 + (uint)tmp_b9 * -2 + 1;
    } while (tmp_b8);
    if (tmp_b8) {
      *(uint32_t *)(tmp_i1 + 0x38c) = 1;
      break;
    }
    tmp_i5 = tmp_i5 + 1;
    tmp_b8 = tmp_i5 == g_unk_010ab34c;
  } while (!tmp_b8);
LAB_000c2ad6:
  local_40 = 1;
  while( true ) {
    if (local_40 == 1) {
      tmp_pc3 = (char *)va("control");
    }
    else {
      tmp_pc3 = (char *)va("control%i",local_40);
    }
    tmp_i5 = g_unk_010ab34c;
    if (g_unk_010ab348 == 0) {
      CG_Error("CG_SpawnString() called while not spawning");
      tmp_i5 = g_unk_010ab34c;
    }
    if (tmp_i5 < 1) break;
    tmp_i6 = 0;
    g_unk_010ab34c = tmp_i5;
    while (tmp_i4 = strcmp(tmp_pc3,(char *)(&g_unk_010ab350)[tmp_i6 * 2]), tmp_i4 != 0) {
      tmp_i6 = tmp_i6 + 1;
      if (tmp_i6 == tmp_i5) {
        return;
      }
    }
    BG_AddSplineControl(tmp_i1,(&g_unk_010ab354)[tmp_i6 * 2]);
    local_40 = local_40 + 1;
  }
  g_unk_010ab34c = tmp_i5;
  return;
}

void SP_corona(void)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  char *tmp_pc3;
  int tmp_i4;
  int tmp_i5;
  char *tmp_pc6;
  bool tmp_b7;
  byte tmp_b8;
  double tmp_d9;
  uint32_t *local_50;
  uint32_t *local_4c;
  uint32_t *local_48;
  uint32_t local_34;
  uint32_t local_30;
  uint32_t local_2c;
  uint32_t local_28;
  uint32_t local_24;
  uint32_t local_20 [3];
  uint32_t uStack_14;
  
  tmp_b8 = 0;
  uStack_14 = 0xc2d19;
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
    if (0 < g_unk_010ab34c) goto LAB_000c2d48;
    if (g_unk_010ab348 != 0) goto LAB_000c2e06;
LAB_000c3050:
    CG_Error("CG_SpawnString() called while not spawning");
    if (0 < g_unk_010ab34c) goto LAB_000c2d9c;
LAB_000c2e06:
    if (g_unk_010ab348 == 0) goto LAB_000c2e10;
  }
  else {
    if (g_unk_010ab34c < 1) goto LAB_000c2e06;
LAB_000c2d48:
    tmp_i1 = 0;
    tmp_b7 = true;
    do {
      tmp_i4 = 0xb;
      tmp_pc3 = "targetname";
      tmp_pc6 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b7 = *tmp_pc3 == *tmp_pc6;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) {
        return;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b7 = tmp_i1 == g_unk_010ab34c;
    } while (tmp_i1 < g_unk_010ab34c);
    if (g_unk_010ab348 == 0) goto LAB_000c3050;
LAB_000c2d9c:
    tmp_i1 = 0;
    tmp_b7 = true;
    do {
      tmp_i4 = 0xb;
      tmp_pc3 = "scriptname";
      tmp_pc6 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b7 = *tmp_pc3 == *tmp_pc6;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) {
        return;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b7 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b7);
    if (g_unk_010ab348 == 0) {
LAB_000c2e10:
      CG_Error("CG_SpawnString() called while not spawning");
      if (g_unk_010ab34c < 1) goto LAB_000c2e30;
    }
    tmp_i1 = 0;
    tmp_b7 = true;
    do {
      tmp_i4 = 0xb;
      tmp_pc3 = "spawnflags";
      tmp_pc6 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b7 = *tmp_pc3 == *tmp_pc6;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) {
        return;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b7 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b7);
  }
LAB_000c2e30:
  tmp_i1 = g_unk_010abd74;
  if (0x3ff < g_unk_010abd74) {
    CG_Error("^1MAX_GAMECORONAS(%i) hit",0x400);
    tmp_i1 = g_unk_010abd74;
  }
  g_unk_010abd74 = tmp_i1 + 1;
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i4 = 0;
    tmp_b7 = true;
    do {
      tmp_i5 = 7;
      tmp_pc3 = "origin";
      tmp_pc6 = (char *)(&g_unk_010ab350)[tmp_i4 * 2];
      do {
        if (tmp_i5 == 0) break;
        tmp_i5 = tmp_i5 + -1;
        tmp_b7 = *tmp_pc3 == *tmp_pc6;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) {
        tmp_pu2 = (uint8_t *)(&g_unk_010ab354)[tmp_i4 * 2];
        goto LAB_000c2ea6;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_b7 = tmp_i4 == g_unk_010ab34c;
    } while (!tmp_b7);
  }
  tmp_pu2 = &g_unk_0011e953;
LAB_000c2ea6:
  __isoc99_sscanf(tmp_pu2,&g_unk_0011e959,&local_28,&local_24,local_20);
  tmp_i4 = tmp_i1 * 0x1c;
  *(uint32_t *)(cgs + tmp_i4 + 0x2019190) = local_28;
  *(uint32_t *)(cgs + tmp_i4 + 0x2019194) = local_24;
  *(uint32_t *)(cgs + tmp_i4 + 0x2019198) = local_20[0];
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i4 = 0;
    tmp_b7 = true;
    do {
      tmp_i5 = 6;
      tmp_pc3 = "scale";
      tmp_pc6 = (char *)(&g_unk_010ab350)[tmp_i4 * 2];
      do {
        if (tmp_i5 == 0) break;
        tmp_i5 = tmp_i5 + -1;
        tmp_b7 = *tmp_pc3 == *tmp_pc6;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) {
        tmp_pc3 = (char *)(&g_unk_010ab354)[tmp_i4 * 2];
        goto LAB_000c2f66;
      }
      tmp_i4 = tmp_i4 + 1;
      tmp_b7 = tmp_i4 == g_unk_010ab34c;
    } while (!tmp_b7);
  }
  tmp_pc3 = "1";
LAB_000c2f66:
  tmp_d9 = strtod(tmp_pc3,(char **)0x0);
  *(float *)(cgs + tmp_i1 * 0x1c + 0x201918c) = (float)tmp_d9;
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i4 = 0;
    tmp_b7 = true;
    do {
      tmp_i5 = 7;
      tmp_pc3 = "_color";
      tmp_pc6 = (char *)(&g_unk_010ab350)[tmp_i4 * 2];
      do {
        if (tmp_i5 == 0) break;
        tmp_i5 = tmp_i5 + -1;
        tmp_b7 = *tmp_pc3 == *tmp_pc6;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) goto LAB_000c2ff7;
      tmp_i4 = tmp_i4 + 1;
      tmp_b7 = tmp_i4 == g_unk_010ab34c;
    } while (!tmp_b7);
  }
  __isoc99_sscanf(&g_unk_0011e953,&g_unk_0011e959,&local_34,&local_30,&local_2c);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  local_48 = &local_2c;
  local_4c = &local_30;
  local_50 = &local_34;
  if (0 < g_unk_010ab34c) {
    tmp_i4 = 0;
    tmp_b7 = true;
    do {
      tmp_i5 = 6;
      tmp_pc3 = "color";
      tmp_pc6 = (char *)(&g_unk_010ab350)[tmp_i4 * 2];
      do {
        if (tmp_i5 == 0) break;
        tmp_i5 = tmp_i5 + -1;
        tmp_b7 = *tmp_pc3 == *tmp_pc6;
        tmp_pc3 = tmp_pc3 + (uint)tmp_b8 * -2 + 1;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b8 * -2 + 1;
      } while (tmp_b7);
      if (tmp_b7) goto LAB_000c2ff7;
      tmp_i4 = tmp_i4 + 1;
      tmp_b7 = tmp_i4 == g_unk_010ab34c;
    } while (!tmp_b7);
  }
  __isoc99_sscanf(&g_unk_0011e953,&g_unk_0011e959,local_50,local_4c,local_48);
  tmp_i4 = tmp_i1 * 0x1c;
  *(uint32_t *)(cgs + tmp_i4 + 0x201919c) = 0x3f800000;
  *(uint32_t *)(cgs + tmp_i4 + 0x20191a0) = 0x3f800000;
  *(uint32_t *)(cgs + tmp_i4 + 0x20191a4) = 0x3f800000;
LAB_000c3014:
  tmp_i1 = tmp_i1 * 0x1c;
  *(uint32_t *)(cgs + tmp_i1 + 0x201919c) = local_34;
  *(uint32_t *)(cgs + tmp_i1 + 0x20191a0) = local_30;
  *(uint32_t *)(cgs + tmp_i1 + 0x20191a4) = local_2c;
  return;
LAB_000c2ff7:
  __isoc99_sscanf((&g_unk_010ab354)[tmp_i4 * 2],&g_unk_0011e959,&local_34,&local_30,&local_2c);
  goto LAB_000c3014;
}

void SP_misc_gamemodel(void)
{
  uint tmp_u1;
  uint8_t *tmp_pu2;
  uint32_t tmp_u3;
  int tmp_i4;
  byte *tmp_pb5;
  char *tmp_pc6;
  byte *tmp_pb7;
  char *tmp_pc8;
  bool tmp_b9;
  bool tmp_b10;
  byte tmp_b11;
  long double tmp_l12;
  double tmp_d13;
  uint8_t *local_68;
  uint8_t *local_64;
  uint8_t local_58 [4];
  float local_54;
  uint8_t local_50 [4];
  float local_4c;
  float local_48;
  float local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  uint32_t uStack_14;
  
  tmp_b11 = 0;
  uStack_14 = 0xc3269;
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
    if (0 < (int)g_unk_010ab34c) goto LAB_000c3297;
    if (g_unk_010ab348 != 0) goto LAB_000c3366;
LAB_000c3398:
    CG_Error("CG_SpawnString() called while not spawning");
    if (0 < (int)g_unk_010ab34c) goto LAB_000c32f4;
LAB_000c3366:
    if (g_unk_010ab348 == 0) goto LAB_000c340a;
    if (0x3ff < g_unk_010abd70) goto LAB_000c3751;
LAB_000c344c:
    if ((int)g_unk_010ab34c < 1) {
LAB_000c3965:
      local_68 = &g_unk_0011d841;
      tmp_pu2 = &g_unk_0011e953;
      goto LAB_000c34e6;
    }
LAB_000c345e:
    tmp_u1 = 0;
    tmp_b9 = true;
    do {
      tmp_i4 = 6;
      tmp_pc6 = "model";
      tmp_pc8 = (char *)(&g_unk_010ab350)[tmp_u1 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b11 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b11 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        local_68 = (uint8_t *)(&g_unk_010ab354)[tmp_u1 * 2];
        goto LAB_000c349a;
      }
      tmp_u1 = tmp_u1 + 1;
      tmp_b9 = tmp_u1 == g_unk_010ab34c;
    } while (!tmp_b9);
    local_68 = &g_unk_0011d841;
LAB_000c349a:
    if (g_unk_010ab348 == 0) goto LAB_000c38ef;
LAB_000c34ac:
    tmp_u1 = 0;
    tmp_b9 = true;
    do {
      tmp_i4 = 7;
      tmp_pc6 = "origin";
      tmp_pc8 = (char *)(&g_unk_010ab350)[tmp_u1 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b11 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b11 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pu2 = (uint8_t *)(&g_unk_010ab354)[tmp_u1 * 2];
        goto LAB_000c34e6;
      }
      tmp_u1 = tmp_u1 + 1;
      tmp_b9 = tmp_u1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  else {
    if ((int)g_unk_010ab34c < 1) goto LAB_000c3366;
LAB_000c3297:
    tmp_b9 = false;
    tmp_u1 = 0;
    tmp_b10 = true;
    do {
      tmp_i4 = 0xb;
      tmp_pb5 = (byte *)"targetname";
      tmp_pb7 = (byte *)(&g_unk_010ab350)[tmp_u1 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b9 = *tmp_pb5 < *tmp_pb7;
        tmp_b10 = *tmp_pb5 == *tmp_pb7;
        tmp_pb5 = tmp_pb5 + (uint)tmp_b11 * -2 + 1;
        tmp_pb7 = tmp_pb7 + (uint)tmp_b11 * -2 + 1;
      } while (tmp_b10);
      if ((!tmp_b9 && !tmp_b10) == tmp_b9) {
        return;
      }
      tmp_u1 = tmp_u1 + 1;
      tmp_b9 = tmp_u1 < g_unk_010ab34c;
      tmp_b10 = tmp_u1 == g_unk_010ab34c;
    } while ((int)tmp_u1 < (int)g_unk_010ab34c);
    if (g_unk_010ab348 == 0) goto LAB_000c3398;
LAB_000c32f4:
    tmp_b9 = false;
    tmp_u1 = 0;
    tmp_b10 = true;
    do {
      tmp_i4 = 0xb;
      tmp_pb5 = (byte *)0x1117b3;
      tmp_pb7 = (byte *)(&g_unk_010ab350)[tmp_u1 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b9 = *tmp_pb5 < *tmp_pb7;
        tmp_b10 = *tmp_pb5 == *tmp_pb7;
        tmp_pb5 = tmp_pb5 + (uint)tmp_b11 * -2 + 1;
        tmp_pb7 = tmp_pb7 + (uint)tmp_b11 * -2 + 1;
      } while (tmp_b10);
      if ((!tmp_b9 && !tmp_b10) == tmp_b9) {
        return;
      }
      tmp_u1 = tmp_u1 + 1;
      tmp_b9 = tmp_u1 < g_unk_010ab34c;
      tmp_b10 = tmp_u1 == g_unk_010ab34c;
    } while (!tmp_b10);
    if (g_unk_010ab348 == 0) {
LAB_000c340a:
      CG_Error("CG_SpawnString() called while not spawning");
      if (0 < (int)g_unk_010ab34c) goto LAB_000c33ca;
    }
    else {
LAB_000c33ca:
      tmp_b9 = false;
      tmp_u1 = 0;
      tmp_b10 = true;
      do {
        tmp_i4 = 0xb;
        tmp_pb5 = (byte *)"spawnflags";
        tmp_pb7 = (byte *)(&g_unk_010ab350)[tmp_u1 * 2];
        do {
          if (tmp_i4 == 0) break;
          tmp_i4 = tmp_i4 + -1;
          tmp_b9 = *tmp_pb5 < *tmp_pb7;
          tmp_b10 = *tmp_pb5 == *tmp_pb7;
          tmp_pb5 = tmp_pb5 + (uint)tmp_b11 * -2 + 1;
          tmp_pb7 = tmp_pb7 + (uint)tmp_b11 * -2 + 1;
        } while (tmp_b10);
        if ((!tmp_b9 && !tmp_b10) == tmp_b9) {
          return;
        }
        tmp_u1 = tmp_u1 + 1;
        tmp_b9 = tmp_u1 < g_unk_010ab34c;
        tmp_b10 = tmp_u1 == g_unk_010ab34c;
      } while (!tmp_b10);
    }
    if (0x3ff < g_unk_010abd70) {
LAB_000c3751:
      CG_Error("^1MAX_STATIC_GAMEMODELS(%i) hit",0x400);
    }
    if (g_unk_010ab348 != 0) goto LAB_000c344c;
    CG_Error("CG_SpawnString() called while not spawning");
    if (0 < (int)g_unk_010ab34c) goto LAB_000c345e;
    if (g_unk_010ab348 != 0) goto LAB_000c3965;
    local_68 = &g_unk_0011d841;
LAB_000c38ef:
    CG_Error("CG_SpawnString() called while not spawning");
    if (0 < (int)g_unk_010ab34c) goto LAB_000c34ac;
  }
  tmp_pu2 = &g_unk_0011e953;
LAB_000c34e6:
  __isoc99_sscanf(tmp_pu2,&g_unk_0011e959,&local_40,&local_3c,&local_38);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < (int)g_unk_010ab34c) {
    tmp_u1 = 0;
    tmp_b9 = true;
    do {
      tmp_i4 = 7;
      tmp_pc6 = "angles";
      tmp_pc8 = (char *)(&g_unk_010ab350)[tmp_u1 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b11 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b11 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        __isoc99_sscanf((&g_unk_010ab354)[tmp_u1 * 2],&g_unk_0011e959,local_58,&local_54,local_50);
        goto LAB_000c35ac;
      }
      tmp_u1 = tmp_u1 + 1;
      tmp_b9 = tmp_u1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  __isoc99_sscanf(&g_unk_0011e953,&g_unk_0011e959,local_58,&local_54,local_50);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < (int)g_unk_010ab34c) {
    tmp_u1 = 0;
    tmp_b9 = true;
    do {
      tmp_i4 = 6;
      tmp_pc6 = "angle";
      tmp_pc8 = (char *)(&g_unk_010ab350)[tmp_u1 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b11 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b11 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_d13 = strtod((char *)(&g_unk_010ab354)[tmp_u1 * 2],(char **)0x0);
        local_54 = (float)tmp_d13;
        goto LAB_000c35ac;
      }
      tmp_u1 = tmp_u1 + 1;
      tmp_b9 = tmp_u1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  strtod("0",(char **)0x0);
LAB_000c35ac:
  local_64 = local_58;
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < (int)g_unk_010ab34c) {
    tmp_u1 = 0;
    tmp_b9 = true;
    do {
      tmp_i4 = 0xf;
      tmp_pc6 = "modelscale_vec";
      tmp_pc8 = (char *)(&g_unk_010ab350)[tmp_u1 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b11 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b11 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        __isoc99_sscanf((&g_unk_010ab354)[tmp_u1 * 2],&g_unk_0011e959,&local_4c,&local_48,&local_44);
        goto LAB_000c3636;
      }
      tmp_u1 = tmp_u1 + 1;
      tmp_b9 = tmp_u1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  __isoc99_sscanf(&g_unk_0011e9d7,&g_unk_0011e959,&local_4c,&local_48,&local_44);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < (int)g_unk_010ab34c) {
    tmp_u1 = 0;
    tmp_b9 = true;
    do {
      tmp_i4 = 0xb;
      tmp_pc6 = "modelscale";
      tmp_pc8 = (char *)(&g_unk_010ab350)[tmp_u1 * 2];
      do {
        if (tmp_i4 == 0) break;
        tmp_i4 = tmp_i4 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc8;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b11 * -2 + 1;
        tmp_pc8 = tmp_pc8 + (uint)tmp_b11 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_d13 = strtod((char *)(&g_unk_010ab354)[tmp_u1 * 2],(char **)0x0);
        local_4c = (float)tmp_d13;
        local_48 = local_4c;
        local_44 = local_4c;
        goto LAB_000c3636;
      }
      tmp_u1 = tmp_u1 + 1;
      tmp_b9 = tmp_u1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  strtod("1",(char **)0x0);
LAB_000c3636:
  tmp_i4 = g_unk_010abd70;
  g_unk_010abd70 = g_unk_010abd70 + 1;
  tmp_u3 = trap_R_RegisterModel(local_68);
  tmp_i4 = tmp_i4 * 0x38;
  *(uint32_t *)(cgs + tmp_i4 + 0x200b18c) = tmp_u3;
  AnglesToAxis(local_64,tmp_i4 + 0x30faffc);
  *(float *)(cgs + tmp_i4 + 0x200b1b4) = *(float *)(cgs + tmp_i4 + 0x200b1b4) * local_44;
  *(float *)(cgs + tmp_i4 + 0x200b1b8) = *(float *)(cgs + tmp_i4 + 0x200b1b8) * local_44;
  *(float *)(cgs + tmp_i4 + 0x200b1bc) = local_44 * *(float *)(cgs + tmp_i4 + 0x200b1bc);
  *(float *)(cgs + tmp_i4 + 0x200b1a8) = *(float *)(cgs + tmp_i4 + 0x200b1a8) * local_48;
  *(float *)(cgs + tmp_i4 + 0x200b1ac) = *(float *)(cgs + tmp_i4 + 0x200b1ac) * local_48;
  *(float *)(cgs + tmp_i4 + 0x200b1b0) = local_48 * *(float *)(cgs + tmp_i4 + 0x200b1b0);
  *(float *)(cgs + tmp_i4 + 0x200b19c) = local_4c * *(float *)(cgs + tmp_i4 + 0x200b19c);
  *(float *)(cgs + tmp_i4 + 0x200b1a0) = *(float *)(cgs + tmp_i4 + 0x200b1a0) * local_4c;
  *(float *)(cgs + tmp_i4 + 0x200b1a4) = local_4c * *(float *)(cgs + tmp_i4 + 0x200b1a4);
  *(uint32_t *)(cgs + tmp_i4 + 0x200b190) = local_40;
  *(uint32_t *)(cgs + tmp_i4 + 0x200b194) = local_3c;
  *(uint32_t *)(cgs + tmp_i4 + 0x200b198) = local_38;
  if (*(int *)(cgs + tmp_i4 + 0x200b18c) == 0) {
    *(uint32_t *)(cgs + tmp_i4 + 0x200b1c0) = 0;
  }
  else {
    trap_R_ModelBounds(*(int *)(cgs + tmp_i4 + 0x200b18c),&local_34,&local_28);
    local_2c = local_2c * local_44;
    local_20 = local_20 * local_44;
    local_30 = local_30 * local_48;
    local_24 = local_24 * local_48;
    local_34 = local_34 * local_4c;
    local_28 = local_28 * local_4c;
    tmp_l12 = (long double)RadiusFromBounds(&local_34,&local_28);
    *(float *)(cgs + tmp_i4 + 0x200b1c0) = (float)tmp_l12;
  }
  return;
}

void SP_worldspawn(void)
{
  int tmp_i1;
  char *tmp_pc2;
  int tmp_i3;
  long tmp_l4;
  uint8_t *tmp_pu5;
  char *tmp_pc6;
  int tmp_i7;
  int tmp_i8;
  bool tmp_b9;
  byte tmp_b10;
  uint8_t *tmp_pu11;
  
  tmp_b10 = 0;
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 10;
      tmp_pc6 = "classname";
      tmp_pc2 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc2;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pu5 = (uint8_t *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c45c6;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  tmp_pu5 = &g_unk_0011d841;
LAB_000c45c6:
  tmp_i1 = Q_stricmp(tmp_pu5,"worldspawn");
  if (tmp_i1 != 0) {
    CG_Error("SP_worldspawn: The first entity isn\'t \'worldspawn\'");
  }
  GHIDRA_FIELD(cgs, 33575848, 4) = 0;
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 0xe;
      tmp_pc6 = "mapcoordsmins";
      tmp_pc2 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc2;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pu11 = &g_unk_0011e95c;
        __isoc99_sscanf((&g_unk_010ab354)[tmp_i1 * 2],&g_unk_0011e95c,&g_unk_010abd54,&g_unk_010abd58,
                        "mapcoordsmins",g_unk_010ab34c,&g_unk_0011e95c);
        if (g_unk_010ab348 == 0) {
          CG_Error("CG_SpawnString() called while not spawning");
        }
        if (g_unk_010ab34c < 1) goto LAB_000c5024;
        tmp_i1 = 0;
        tmp_b9 = true;
        goto LAB_000c46ab;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  __isoc99_sscanf("-128 128",&g_unk_0011e95c,&g_unk_010abd54,&g_unk_010abd58);
  goto LAB_000c4740;
  while( true ) {
    tmp_i1 = tmp_i1 + 1;
    tmp_b9 = false;
    if (tmp_i1 == g_unk_010ab34c) break;
LAB_000c46ab:
    tmp_i7 = 0xe;
    tmp_pc6 = "mapcoordsmaxs";
    tmp_pc2 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
    do {
      if (tmp_i7 == 0) break;
      tmp_i7 = tmp_i7 + -1;
      tmp_b9 = *tmp_pc6 == *tmp_pc2;
      tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
      tmp_pc2 = tmp_pc2 + (uint)tmp_b10 * -2 + 1;
    } while (tmp_b9);
    if (tmp_b9) {
      __isoc99_sscanf((&g_unk_010ab354)[tmp_i1 * 2],tmp_pu11,&g_unk_010abd5c,&g_unk_010abd60);
      g_unk_010abd6c = 1;
      CG_ParseSpawns();
      goto joined_r0x000c4755;
    }
  }
LAB_000c5024:
  __isoc99_sscanf("128 -128",tmp_pu11,&g_unk_010abd5c,&g_unk_010abd60);
LAB_000c4740:
  g_unk_010abd6c = 0;
  CG_ParseSpawns();
joined_r0x000c4755:
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 9;
      tmp_pc6 = "cclayers";
      tmp_pc2 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc2;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pc6 = (char *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c47a6;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  tmp_pc6 = "0";
LAB_000c47a6:
  GHIDRA_FIELD(cgs, 33575848, 4) = strtol(tmp_pc6,(char **)0x0,10);
  if (0 < (int)GHIDRA_FIELD(cgs, 33575848, 4)) {
    tmp_pc6 = "cclayerceil%i";
    tmp_i1 = 0;
    do {
      tmp_pc2 = (char *)va(tmp_pc6,tmp_i1);
      if (g_unk_010ab348 == 0) {
        CG_Error("CG_SpawnString() called while not spawning");
      }
      if (0 < g_unk_010ab34c) {
        tmp_i8 = 0;
        tmp_i7 = g_unk_010ab34c;
        do {
          tmp_i3 = strcmp(tmp_pc2,(char *)(&g_unk_010ab350)[tmp_i8 * 2]);
          if (tmp_i3 == 0) {
            tmp_pc2 = (char *)(&g_unk_010ab354)[tmp_i8 * 2];
            goto LAB_000c4859;
          }
          tmp_i8 = tmp_i8 + 1;
        } while (tmp_i8 != tmp_i7);
      }
      tmp_pc2 = "0";
LAB_000c4859:
      tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
      *(long *)(cgs + tmp_i1 * 4 + 0x20053ac) = tmp_l4;
      tmp_i1 = tmp_i1 + 1;
    } while (tmp_i1 < (int)GHIDRA_FIELD(cgs, 33575848, 4));
  }
  g_unk_010abd64 = 1.0 / (g_unk_010abd5c - g_unk_010abd54);
  g_unk_010abd68 = 1.0 / (g_unk_010abd60 - g_unk_010abd58);
  BG_InitLocations(&g_unk_010abd54,&g_unk_010abd5c);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 0xb;
      tmp_pc6 = "atmosphere";
      tmp_pc2 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc2;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pu5 = (uint8_t *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c492e;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  tmp_pu5 = &g_unk_0011d841;
LAB_000c492e:
  CG_EffectParse(tmp_pu5);
  g_unk_010b14e8 = '\0';
  g_unk_010b1528 = '\0';
  g_unk_010b1568 = '\0';
  g_unk_010b15a8 = '\0';
  g_unk_010b15e8 = '\0';
  g_unk_010b1628 = '\0';
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 0x15;
      tmp_pc6 = "fiveMinuteSound_axis";
      tmp_pc2 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc2;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pc6 = (char *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c49b6;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  tmp_pc6 = "axis_hq_5minutes";
LAB_000c49b6:
  Q_strncpyz(&g_unk_010b14e8,tmp_pc6,0x40);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 0x17;
      tmp_pc6 = "fiveMinuteSound_allied";
      tmp_pc2 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc2;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pc6 = (char *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c4a26;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  tmp_pc6 = "allies_hq_5minutes";
LAB_000c4a26:
  Q_strncpyz(&g_unk_010b1528,tmp_pc6,0x40);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 0x14;
      tmp_pc6 = "twoMinuteSound_axis";
      tmp_pc2 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc2;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pc6 = (char *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c4a96;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  tmp_pc6 = "axis_hq_2minutes";
LAB_000c4a96:
  Q_strncpyz(&g_unk_010b1568,tmp_pc6,0x40);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 0x16;
      tmp_pc6 = "twoMinuteSound_allied";
      tmp_pc2 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc2;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pc6 = (char *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c4b06;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  tmp_pc6 = "allies_hq_2minutes";
LAB_000c4b06:
  Q_strncpyz(&g_unk_010b15a8,tmp_pc6,0x40);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 0x17;
      tmp_pc6 = "thirtySecondSound_axis";
      tmp_pc2 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc2;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pc6 = (char *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c4b76;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  tmp_pc6 = "axis_hq_30seconds";
LAB_000c4b76:
  Q_strncpyz(&g_unk_010b15e8,tmp_pc6,0x40);
  if (g_unk_010ab348 == 0) {
    CG_Error("CG_SpawnString() called while not spawning");
  }
  if (0 < g_unk_010ab34c) {
    tmp_i1 = 0;
    tmp_b9 = true;
    do {
      tmp_i7 = 0x19;
      tmp_pc6 = "thirtySecondSound_allied";
      tmp_pc2 = (char *)(&g_unk_010ab350)[tmp_i1 * 2];
      do {
        if (tmp_i7 == 0) break;
        tmp_i7 = tmp_i7 + -1;
        tmp_b9 = *tmp_pc6 == *tmp_pc2;
        tmp_pc6 = tmp_pc6 + (uint)tmp_b10 * -2 + 1;
        tmp_pc2 = tmp_pc2 + (uint)tmp_b10 * -2 + 1;
      } while (tmp_b9);
      if (tmp_b9) {
        tmp_pc6 = (char *)(&g_unk_010ab354)[tmp_i1 * 2];
        goto LAB_000c4be6;
      }
      tmp_i1 = tmp_i1 + 1;
      tmp_b9 = tmp_i1 == g_unk_010ab34c;
    } while (!tmp_b9);
  }
  tmp_pc6 = "allies_hq_30seconds";
LAB_000c4be6:
  Q_strncpyz(&g_unk_010b1628,tmp_pc6,0x40);
  if (g_unk_010b14e8 == '\0') {
    GHIDRA_FIELD(cgs, 69452, 4) = 0;
  }
  else {
    tmp_pc6 = strstr(&g_unk_010b14e8,".wav");
    if (tmp_pc6 == (char *)0x0) {
      GHIDRA_FIELD(cgs, 69452, 4) = 0xffffffff;
    }
    else {
      GHIDRA_FIELD(cgs, 69452, 4) = trap_S_RegisterSound(&g_unk_010b14e8,1);
    }
  }
  if (g_unk_010b1528 == '\0') {
    GHIDRA_FIELD(cgs, 69456, 4) = 0;
  }
  else {
    tmp_pc6 = strstr(&g_unk_010b1528,".wav");
    if (tmp_pc6 == (char *)0x0) {
      GHIDRA_FIELD(cgs, 69456, 4) = 0xffffffff;
    }
    else {
      GHIDRA_FIELD(cgs, 69456, 4) = trap_S_RegisterSound(&g_unk_010b1528,1);
    }
  }
  if (g_unk_010b1568 == '\0') {
    GHIDRA_FIELD(cgs, 69460, 4) = 0;
  }
  else {
    tmp_pc6 = strstr(&g_unk_010b1568,".wav");
    if (tmp_pc6 == (char *)0x0) {
      GHIDRA_FIELD(cgs, 69460, 4) = 0xffffffff;
    }
    else {
      GHIDRA_FIELD(cgs, 69460, 4) = trap_S_RegisterSound(&g_unk_010b1568,1);
    }
  }
  if (g_unk_010b15a8 == '\0') {
    GHIDRA_FIELD(cgs, 69464, 4) = 0;
  }
  else {
    tmp_pc6 = strstr(&g_unk_010b15a8,".wav");
    if (tmp_pc6 == (char *)0x0) {
      GHIDRA_FIELD(cgs, 69464, 4) = 0xffffffff;
    }
    else {
      GHIDRA_FIELD(cgs, 69464, 4) = trap_S_RegisterSound(&g_unk_010b15a8,1);
    }
  }
  if (g_unk_010b15e8 == '\0') {
    GHIDRA_FIELD(cgs, 69468, 4) = 0;
  }
  else {
    tmp_pc6 = strstr(&g_unk_010b15e8,".wav");
    if (tmp_pc6 == (char *)0x0) {
      GHIDRA_FIELD(cgs, 69468, 4) = 0xffffffff;
    }
    else {
      GHIDRA_FIELD(cgs, 69468, 4) = trap_S_RegisterSound(&g_unk_010b15e8,1);
    }
  }
  if (g_unk_010b1628 != '\0') {
    tmp_pc6 = strstr(&g_unk_010b1628,".wav");
    if (tmp_pc6 != (char *)0x0) {
      GHIDRA_FIELD(cgs, 69472, 4) = trap_S_RegisterSound(&g_unk_010b1628,1);
      return;
    }
    GHIDRA_FIELD(cgs, 69472, 4) = 0xffffffff;
    return;
  }
  GHIDRA_FIELD(cgs, 69472, 4) = 0;
  return;
}

