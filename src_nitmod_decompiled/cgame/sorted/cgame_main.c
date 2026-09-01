/* Client-game VM lifecycle and frame orchestration — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_main.h"

void CG_InitStatsDebug(void)
{
  uint tmp_u1;
  int tmp_i2;
  uint32_t *tmp_pu3;
  
  tmp_u1 = 0;
  tmp_pu3 = &statsDebugStrings;
  for (tmp_i2 = 0x300; tmp_i2 != 0; tmp_i2 = tmp_i2 + -1) {
    *tmp_pu3 = 0;
    tmp_pu3 = tmp_pu3 + 1;
  }
  do {
    *(uint32_t *)((int)&statsDebugTime + tmp_u1) = 0;
    *(uint32_t *)((int)&g_unk_002b2df4 + tmp_u1) = 0;
    tmp_u1 = tmp_u1 + 8;
  } while (tmp_u1 < 0x18);
  statsDebugPos = 0xffffffff;
  return;
}

void CG_InitFlameChunks(void)
{
  uint32_t *tmp_pu1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint8_t local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0x7fc90;
  memset(&flameChunks,0,0x27000);
  memset(centFlameInfo,0,0xd000);
  tmp_i3 = 0;
  activeFlameChunks = 0;
  headFlameChunks = 0;
  tmp_pu1 = &g_unk_002ca51c;
  freeFlameChunks = &flameChunks;
  do {
    tmp_pu1[-0x27] = tmp_pu1;
    if (tmp_i3 == 0) {
      g_unk_002ca484 = 0;
    }
    else {
      tmp_pu1[-0x26] = tmp_pu1 + -0x4e;
    }
    tmp_i3 = tmp_i3 + 1;
    tmp_pu1[-0x22] = 0;
    tmp_pu1 = tmp_pu1 + 0x27;
  } while (tmp_i3 != 0x400);
  g_unk_002f13e4 = 0;
  initFlameChunks = 1;
  numFlameChunksInuse = 0;
  tmp_i3 = 0;
  do {
    tmp_i3 = tmp_i3 + 1;
    Com_sprintf(local_5c,0x40,"flamethrowerFire%i",tmp_i3);
    tmp_u2 = trap_R_RegisterShader(local_5c);
    *(uint32_t *)(tmp_i3 * 4 + 0x2bb3bc) = tmp_u2;
  } while (tmp_i3 != 0x14);
  tmp_i3 = 0;
  do {
    tmp_i3 = tmp_i3 + 1;
    Com_sprintf(local_5c,0x40,"nozzleFlame%i",tmp_i3);
    tmp_u2 = trap_R_RegisterShader(local_5c);
    *(uint32_t *)(tmp_i3 * 4 + 0x2bb39c) = tmp_u2;
  } while (tmp_i3 != 8);
  initFlameShaders = 0;
  return;
}

void CG_InitLocalEntities(void)
{
  uint8_t *tmp_pu1;
  
  memset(cg_localEntities,0,0x53400);
  g_unk_00f69564 = &cg_activeLocalEntities;
  cg_activeLocalEntities = &cg_activeLocalEntities;
  tmp_pu1 = (uint8_t *)0xf698dc;
  cg_freeLocalEntities = cg_localEntities;
  do {
    *(uint8_t **)(tmp_pu1 + -0x1b8) = tmp_pu1;
    tmp_pu1 = tmp_pu1 + 0x1bc;
  } while (tmp_pu1 != cg_drawReinforcementTime);
  localEntCount = 0;
  return;
}

void CG_Shutdown(void)
{
  CG_EventHandling(0,1);
  if (g_unk_01047aec != 0) {
    trap_Cvar_Set("timescale",&g_unk_0011e9db);
  }
  if (g_unk_010eecc8 != 0) {
    trap_FS_FCloseFile(g_unk_010eecc8);
    g_unk_010eecc8 = 0;
  }
  return;
}

void CG_InitMarkPolys(void)
{
  uint32_t *tmp_pu1;
  
  memset(cg_markPolys,0,0x12400);
  g_unk_03404da4 = &cg_activeMarkPolys;
  cg_activeMarkPolys = &cg_activeMarkPolys;
  tmp_pu1 = (uint32_t *)0x33f2ac4;
  cg_freeMarkPolys = cg_markPolys;
  do {
    tmp_pu1[-0x48] = tmp_pu1;
    tmp_pu1 = tmp_pu1 + 0x49;
  } while ((uint32_t **)tmp_pu1 != &cg_activeMarkPolys);
  return;
}

void CG_InitPMGraphics(void)
{
  GHIDRA_FIELD(cgs, 131804, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/rflag");
  GHIDRA_FIELD(cgs, 131808, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/bflag");
  GHIDRA_FIELD(cgs, 131768, 4) = trap_R_RegisterShaderNoMip("gfx/limbo/dynamite");
  GHIDRA_FIELD(cgs, 131772, 4) = trap_R_RegisterShaderNoMip("sprites/voiceChat");
  GHIDRA_FIELD(cgs, 131776, 4) = trap_R_RegisterShaderNoMip("sprites/voiceChat");
  GHIDRA_FIELD(cgs, 131780, 4) = trap_R_RegisterShaderNoMip("gfx/hud/pm_death");
  GHIDRA_FIELD(cgs, 131784, 4) = trap_R_RegisterShaderNoMip("sprites/voiceChat");
  GHIDRA_FIELD(cgs, 131788, 4) = trap_R_RegisterShaderNoMip("sprites/objective");
  GHIDRA_FIELD(cgs, 131792, 4) = trap_R_RegisterShaderNoMip("sprites/voiceChat");
  GHIDRA_FIELD(cgs, 131796, 4) = trap_R_RegisterShaderNoMip("icons/iconw_ammopack_1_select");
  GHIDRA_FIELD(cgs, 131800, 4) = trap_R_RegisterShaderNoMip("icons/iconw_medheal_1_select");
  GHIDRA_FIELD(cgs, 131812, 4) = trap_R_RegisterShaderNoMip("gfx/hud/pm_constallied");
  GHIDRA_FIELD(cgs, 131816, 4) = trap_R_RegisterShaderNoMip("gfx/hud/pm_constaxis");
  GHIDRA_FIELD(cgs, 131820, 4) = trap_R_RegisterShaderNoMip("gfx/hud/pm_mineallied");
  GHIDRA_FIELD(cgs, 131824, 4) = trap_R_RegisterShaderNoMip("gfx/hud/pm_mineaxis");
  return;
}

void CG_InitPM(void)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  byte tmp_b3;
  
  tmp_b3 = 0;
  memset(&cg_pmStack,0,0x2500);
  tmp_pu2 = &cg_pmStackBig;
  for (tmp_i1 = 0x140; tmp_i1 != 0; tmp_i1 = tmp_i1 + -1) {
    *tmp_pu2 = 0;
    tmp_pu2 = tmp_pu2 + (uint)tmp_b3 * -2 + 1;
  }
  cg_pmOldList = 0;
  cg_pmWaitingList = 0;
  cg_pmWaitingListBig = 0;
  return;
}

