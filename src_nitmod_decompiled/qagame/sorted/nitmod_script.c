/* Entity scripting — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_script.h"

void script_mover_think(int param_1)
{
  int tmp_i1;
  
  if (((*(byte *)(param_1 + 0x1a8) & 0x80) != 0) && (*(int *)(param_1 + 0x444) == 0)) {
    if (*(int *)(param_1 + 0x4d4) != 0) {
      tmp_i1 = (int)ROUND((float)*(int *)(param_1 + 0x4d4) - 30.0);
      if (tmp_i1 < 0) {
        tmp_i1 = 0;
      }
      *(int *)(param_1 + 0x4d4) = tmp_i1;
    }
    if (*(int *)(param_1 + 0x4d0) != 0) {
      tmp_i1 = *(int *)(param_1 + 0x4d0) + -100;
      if (tmp_i1 < 0) {
        tmp_i1 = 0;
      }
      *(int *)(param_1 + 0x4d0) = tmp_i1;
    }
  }
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return;
}

bool G_Script_EventMatch_StringEqual(int param_1,int param_2)
{
  int tmp_i1;
  
  if (param_2 != 0) {
    tmp_i1 = Q_stricmp(*(uint32_t *)(param_1 + 4),param_2);
    return tmp_i1 == 0;
  }
  return false;
}

bool G_Script_EventMatch_IntInRange(int param_1,int param_2)
{
  char *tmp_pc1;
  long tmp_l2;
  long tmp_l3;
  long tmp_l4;
  int local_20 [4];
  
  local_20[0] = param_2;
  tmp_pc1 = (char *)COM_ParseExt(local_20,0);
  tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)COM_ParseExt(local_20,0);
  tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_l4 = strtol(*(char **)(param_1 + 4),(char **)0x0,10);
  return (tmp_l4 <= tmp_l3 && tmp_l2 < tmp_l4) && param_2 != 0;
}

void script_mover_spawn(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  bool tmp_b4;
  
  tmp_u3 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u3 & 0x80) != 0) {
    tmp_u1 = BG_StringHashValue(param_1 + 0x4c0);
    tmp_i2 = G_FindByTargetnameFast(0,param_1 + 0x4c0,tmp_u1);
    if (tmp_i2 == 0) {
      tmp_i2 = param_1;
    }
    *(int *)(param_1 + 0x21c) = tmp_i2;
    *(int *)(param_1 + 0x114) = (tmp_i2 + -0x93e4a0 >> 9) * -0x55555555;
    tmp_u3 = *(uint *)(param_1 + 0x1a8);
  }
  tmp_b4 = (tmp_u3 & 2) != 0;
  if (!tmp_b4) {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 2;
  }
  tmp_u3 = (uint)tmp_b4;
  *(uint *)(param_1 + 0x14c) = tmp_u3;
  *(uint *)(param_1 + 0x1d4) = tmp_u3;
  trap_LinkEntity(param_1);
  *(void **)(param_1 + 0x2a4) = script_mover_think;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 200;
  return;
}

void script_mover_blocked(uint32_t param_1,int param_2)
{
  if ((*(int *)(param_2 + 400) == 0) && (*(int *)(param_2 + 4) != 0x26)) {
    if ((*(int *)(param_2 + 4) != 2) || (*(int *)(*(int *)(param_2 + 0x33c) + 0x24) != 5)) {
      G_FreeEntity(param_2);
      return;
    }
    Team_DroppedFlagThink(param_2);
  }
  else {
    G_Damage(param_2,param_1,param_1,0,0,0,0x20,0x1d);
  }
  return;
}

void script_model_med_use(int param_1)
{
  uint32_t tmp_u1;
  
  if ((*(byte *)(param_1 + 0x1a8) & 2) != 0) {
    *(uint32_t *)(param_1 + 0x1d4) = 1;
    *(uint32_t *)(param_1 + 0x14c) = 1;
  }
  *(uint32_t *)(param_1 + 4) = 0;
  tmp_u1 = G_ModelIndex(*(uint32_t *)(param_1 + 0x1b4));
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u1;
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0xb0) = 0;
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  trap_LinkEntity(param_1);
  return;
}

int G_Script_EventForString(uint32_t param_1)
{
  uint8_t **tmp_ppu1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  uint8_t **tmp_ppu4;
  
  tmp_pu2 = (uint8_t *)nitrox_GetTokenForString(param_1);
  if (gScriptEvents == (uint8_t *)0x0) {
    return -1;
  }
  if (g_unk_002ba4a8 == tmp_pu2) {
    tmp_i3 = 0;
  }
  else {
    tmp_i3 = 0;
    tmp_ppu4 = &g_ptr_s_trigger_00257751_0xe_002ba4ac;
    do {
      tmp_i3 = tmp_i3 + 1;
      if (*tmp_ppu4 == (uint8_t *)0x0) {
        return -1;
      }
      tmp_ppu1 = tmp_ppu4 + 2;
      tmp_ppu4 = tmp_ppu4 + 3;
    } while (*tmp_ppu1 != tmp_pu2);
  }
  return tmp_i3;
}

uint8_t ** G_Script_ActionForString(uint32_t param_1)
{
  uint8_t **tmp_ppu1;
  uint8_t *tmp_pu2;
  int tmp_i3;
  uint8_t **tmp_ppu4;
  
  tmp_pu2 = (uint8_t *)nitrox_GetTokenForString(param_1);
  if (gScriptActions == (uint8_t *)0x0) {
    return (uint8_t **)0x0;
  }
  if (g_unk_002ba5a8 == tmp_pu2) {
    tmp_i3 = 0;
  }
  else {
    tmp_i3 = 0;
    tmp_ppu4 = &g_ptr_s_playsound_002ba5ac;
    do {
      tmp_i3 = tmp_i3 + 1;
      if (*tmp_ppu4 == (uint8_t *)0x0) {
        return (uint8_t **)0x0;
      }
      tmp_ppu1 = tmp_ppu4 + 2;
      tmp_ppu4 = tmp_ppu4 + 3;
    } while (*tmp_ppu1 != tmp_pu2);
  }
  return &gScriptActions + tmp_i3 * 3;
}

void G_Script_ScriptLoad(void)
{
  int tmp_i1;
  uint32_t tmp_u2;
  uint8_t *tmp_pu3;
  uint8_t *tmp_pu4;
  uint32_t *tmp_pu5;
  char *tmp_pc6;
  uint32_t local_170;
  char local_16c [64];
  uint8_t local_12c [16];
  uint8_t local_11c [264];
  uint32_t uStack_14;
  
  uStack_14 = 0xba98b;
  local_170 = 0;
  trap_Cvar_Register(g_scriptDebug,"g_scriptDebug",&g_unk_0024bfa6,0);
  g_unk_00abfa9c = 0;
  trap_Cvar_VariableStringBuffer("g_scriptName",local_16c,0x40);
  if (local_16c[0] == '\0') {
    tmp_u2 = 0x44;
    trap_Cvar_Register(local_12c,"mapname",&g_unk_0026ea14,0x44);
    if (g_mapScriptDirectory[0x10] != '\0') goto LAB_000bab39;
LAB_000baa2e:
    tmp_pu4 = local_11c;
    tmp_pu3 = g_gametype;
    tmp_pc6 = ".script";
    tmp_pu5 = &local_170;
  }
  else {
    tmp_u2 = 0x200;
    trap_Cvar_Register(local_12c,"g_scriptName",&g_unk_0026ea14,0x200);
    if (g_mapScriptDirectory[0x10] == '\0') goto LAB_000baa2e;
LAB_000bab39:
    Q_strncpyz(local_16c,0x2e5dcf0,0x40);
    Q_strcat(local_16c,0x40,&g_unk_0024ed91);
    tmp_pu4 = local_11c;
    Q_strcat(local_16c,0x40,tmp_pu4);
    tmp_pu3 = g_gametype;
    tmp_i1 = GHIDRA_FIELD(g_gametype, 12, 4);
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
      Q_strcat(local_16c,0x40,&g_unk_0024ed7c);
      tmp_i1 = *(int *)(tmp_pu3 + 0xc);
    }
    if (tmp_i1 == 8) {
      Q_strcat(local_16c,0x40,&g_unk_0024ed81);
    }
    tmp_pc6 = ".script";
    Q_strcat(local_16c,0x40,".script");
    tmp_pu5 = &local_170;
    tmp_i1 = trap_FS_FOpenFile(local_16c,tmp_pu5,0);
    if (0 < tmp_i1) {
      trap_Cvar_Set("g_scriptName",&g_unk_0026ea14);
      goto LAB_000bac00;
    }
  }
  Q_strncpyz(local_16c,&g_unk_0024ed8d,0x40,tmp_u2,tmp_pu3,tmp_pu4,tmp_pu5,tmp_pc6);
  Q_strcat(local_16c,0x40,tmp_pu4);
  tmp_i1 = *(int *)(tmp_pu3 + 0xc);
  if (tmp_i1 == 5) {
    Q_strcat(local_16c,0x40,&g_unk_0024ed7c);
    tmp_i1 = *(int *)(tmp_pu3 + 0xc);
  }
  if (tmp_i1 == 8) {
    Q_strcat(local_16c,0x40,&g_unk_0024ed81);
  }
  Q_strcat(local_16c,0x40,tmp_pc6);
  tmp_i1 = trap_FS_FOpenFile(local_16c,tmp_pu5,0);
  trap_Cvar_Set("g_scriptName",&g_unk_0026ea14);
  if (tmp_i1 < 0) {
    return;
  }
LAB_000bac00:
  g_unk_00abfa9c = G_Alloc(tmp_i1 + 1);
  trap_FS_Read(g_unk_00abfa9c,tmp_i1,local_170);
  *(uint8_t *)(g_unk_00abfa9c + tmp_i1) = 0;
  trap_FS_FCloseFile(local_170);
  return;
}

void G_Script_ScriptParse(int param_1)
{
  uint8_t **tmp_ppu1;
  char tmp_c2;
  uint16_t tmp_u3;
  void *tmp_pc4;
  bool tmp_b5;
  bool tmp_b6;
  int tmp_i7;
  char *tmp_pc8;
  uint32_t tmp_u9;
  uint8_t *tmp_pu10;
  uint tmp_u11;
  uint32_t *tmp_pu12;
  int tmp_i13;
  uint tmp_u14;
  int tmp_i15;
  int tmp_i16;
  uint8_t *tmp_pu17;
  uint *tmp_pu18;
  uint *tmp_pu19;
  uint8_t **tmp_ppu20;
  uint32_t *__s;
  uint32_t *tmp_pu21;
  uint32_t *tmp_pu22;
  byte tmp_b23;
  char *tmp_pc24;
  int iStack_4be00;
  int iStack_4bdf8;
  int iStack_4bdd0;
  uint auStack_4bdcc [256];
  uint8_t auStack_4b9cc [4];
  int aiStack_4b9c8 [393];
  int aiStack_4b3a4 [77029];
  
  tmp_b23 = 0;
  if ((*(int *)(param_1 + 0x3ac) != 0) && (g_unk_00abfa9c != 0)) {
    tmp_i7 = trap_Cvar_VariableIntegerValue("com_buildScript");
    iStack_4bdd0 = g_unk_00abfa9c;
    COM_BeginParseSession("G_Script_ScriptParse");
    __s = (uint32_t *)auStack_4b9cc;
    tmp_pc24 = (char *)0x4b9b0;
    memset(__s,0,0x4b9b0);
    iStack_4bdf8 = 0;
    tmp_b6 = false;
    tmp_b5 = true;
    iStack_4be00 = 0;
LAB_000badc0:
    tmp_pc8 = (char *)COM_Parse(&iStack_4bdd0);
    tmp_c2 = *tmp_pc8;
    if (tmp_c2 != '\0') {
      if (tmp_c2 == '}') {
        if (tmp_b6) goto LAB_000bb03d;
        if (tmp_b5) {
          tmp_u9 = COM_GetCurrentParseLine();
          G_Error("G_Script_ScriptParse(), Error (line %d): \'}\' found, but not expected.\n",tmp_u9)
          ;
          tmp_b5 = true;
        }
        else {
          tmp_b5 = true;
        }
      }
      else if (tmp_c2 == '{') {
        if (tmp_b5) {
          tmp_u9 = COM_GetCurrentParseLine();
          G_Error("G_Script_ScriptParse(), Error (line %d): \'{\' found, NAME expected.\n",tmp_u9);
          tmp_b5 = true;
        }
      }
      else if (tmp_b5) {
        tmp_i16 = Q_stricmp(tmp_pc8,"bot");
        if (tmp_i16 == 0) {
          SkipRestOfLine(&iStack_4bdd0);
          SkipBracedSection(&iStack_4bdd0);
          tmp_b5 = true;
        }
        else {
          tmp_i16 = Q_stricmp(tmp_pc8,"entity");
          tmp_b5 = true;
          if (tmp_i16 != 0) {
            tmp_i13 = Q_stricmp(*(uint32_t *)(param_1 + 0x3ac),tmp_pc8);
            tmp_i16 = 0;
            tmp_b5 = true;
            if (tmp_i13 != 0) {
              tmp_i16 = iStack_4bdf8;
              tmp_b5 = tmp_b6;
            }
            tmp_b6 = tmp_b5;
            iStack_4bdf8 = tmp_i16;
            tmp_b5 = false;
          }
        }
      }
      else if (tmp_b6) {
        Q_strlwr(tmp_pc8);
        tmp_pu10 = (uint8_t *)nitrox_GetTokenForString(tmp_pc8);
        if (gScriptEvents == (uint8_t *)0x0) {
LAB_000baf3d:
          tmp_u9 = COM_GetCurrentParseLine();
          tmp_i16 = -1;
          G_Error("G_Script_ScriptParse(), Error (line %d): unknown event: %s.\n",tmp_u9,tmp_pc8);
          tmp_pc24 = tmp_pc8;
        }
        else if (tmp_pu10 == g_unk_002ba4a8) {
          tmp_i16 = 0;
        }
        else {
          tmp_i16 = 0;
          tmp_ppu20 = &g_ptr_s_trigger_00257751_0xe_002ba4ac;
          do {
            tmp_i16 = tmp_i16 + 1;
            if (*tmp_ppu20 == (uint8_t *)0x0) goto LAB_000baf3d;
            tmp_ppu1 = tmp_ppu20 + 2;
            tmp_ppu20 = tmp_ppu20 + 3;
          } while (tmp_pu10 != *tmp_ppu1);
        }
        if (0xc3 < iStack_4bdf8) {
          tmp_u9 = COM_GetCurrentParseLine();
          tmp_pc24 = (char *)0xc4;
          G_Error("G_Script_ScriptParse(), Error (line %d): G_MAX_SCRIPT_STACK_ITEMS reached (%d)\n"
                  ,tmp_u9,0xc4);
        }
        *(int *)(auStack_4b9cc + iStack_4bdf8 * 0x62c) = tmp_i16;
        tmp_u11 = 0;
        do {
          *(uint32_t *)((int)auStack_4bdcc + tmp_u11) = 0;
          *(uint32_t *)((int)auStack_4bdcc + tmp_u11 + 4) = 0;
          tmp_u11 = tmp_u11 + 8;
        } while (tmp_u11 < 0x400);
        while ((tmp_pc8 = (char *)COM_Parse(&iStack_4bdd0), tmp_pc8 != (char *)0x0 && (*tmp_pc8 != '{')
               )) {
          if (*tmp_pc8 == '\0') {
            tmp_u9 = COM_GetCurrentParseLine();
            G_Error("G_Script_ScriptParse(), Error (line %d): \'}\' expected, end of script found.\n"
                    ,tmp_u9);
          }
          if ((char)auStack_4bdcc[0] != '\0') {
            Q_strcat(auStack_4bdcc,0x400,&g_unk_002612df);
          }
          Q_strcat(auStack_4bdcc,0x400);
          tmp_pc24 = tmp_pc8;
        }
        tmp_pu19 = auStack_4bdcc;
        if ((char)auStack_4bdcc[0] != '\0') {
          do {
            tmp_pu18 = tmp_pu19;
            tmp_u14 = *tmp_pu18 + 0xfefefeff & ~*tmp_pu18;
            tmp_u11 = tmp_u14 & 0x80808080;
            tmp_pu19 = tmp_pu18 + 1;
          } while (tmp_u11 == 0);
          if ((tmp_u14 & 0x8080) == 0) {
            tmp_pu19 = (uint *)((int)tmp_pu18 + 6);
            tmp_u11 = tmp_u11 >> 0x10;
          }
          tmp_i16 = G_Alloc((int)tmp_pu19 +
                           (-(int)auStack_4bdcc - (uint)CARRY1((byte)tmp_u11,(byte)tmp_u11)) + -2);
          aiStack_4b9c8[iStack_4bdf8 * 0x18b] = tmp_i16;
          tmp_pu19 = auStack_4bdcc;
          do {
            tmp_pu18 = tmp_pu19;
            tmp_u14 = *tmp_pu18 + 0xfefefeff & ~*tmp_pu18;
            tmp_u11 = tmp_u14 & 0x80808080;
            tmp_pu19 = tmp_pu18 + 1;
          } while (tmp_u11 == 0);
          if ((tmp_u14 & 0x8080) == 0) {
            tmp_pu19 = (uint *)((int)tmp_pu18 + 6);
            tmp_u11 = tmp_u11 >> 0x10;
          }
          tmp_pc24 = (char *)((int)tmp_pu19 +
                            (-(int)auStack_4bdcc - (uint)CARRY1((byte)tmp_u11,(byte)tmp_u11)) + -2);
          Q_strncpyz(tmp_i16,auStack_4bdcc,tmp_pc24);
        }
        while ((tmp_pc8 = (char *)COM_Parse(&iStack_4bdd0), tmp_pc8 != (char *)0x0 && (*tmp_pc8 != '}')
               )) {
          if (*tmp_pc8 == '\0') {
            tmp_u9 = COM_GetCurrentParseLine();
            G_Error("G_Script_ScriptParse(), Error (line %d): \'}\' expected, end of script found.\n"
                    ,tmp_u9,tmp_pc24);
          }
          tmp_pu10 = (uint8_t *)nitrox_GetTokenForString(tmp_pc8);
          if (gScriptActions == (uint8_t *)0x0) {
LAB_000bb229:
            tmp_u9 = COM_GetCurrentParseLine();
            G_Error("G_Script_ScriptParse(), Error (line %d): unknown action: %s.\n",tmp_u9,tmp_pc8);
            aiStack_4b9c8[aiStack_4b3a4[iStack_4bdf8 * 0x18b] * 2 + iStack_4bdf8 * 0x18b + 1] = 0;
            tmp_u11 = 0;
            do {
              *(uint32_t *)((int)auStack_4bdcc + tmp_u11) = 0;
              *(uint32_t *)((int)auStack_4bdcc + tmp_u11 + 4) = 0;
              tmp_u11 = tmp_u11 + 8;
            } while (tmp_u11 < 0x400);
            tmp_pc4 = (void *)invalidInstructionException();
            (*tmp_pc4)();
          }
          if (tmp_pu10 == g_unk_002ba5a8) {
            tmp_i16 = 0;
            tmp_pu17 = gScriptActions;
          }
          else {
            tmp_i16 = 0;
            tmp_ppu20 = &g_ptr_s_playsound_002ba5ac;
            do {
              tmp_i16 = tmp_i16 + 1;
              if (*tmp_ppu20 == (uint8_t *)0x0) goto LAB_000bb229;
              tmp_ppu1 = tmp_ppu20 + 2;
              tmp_pu17 = *tmp_ppu20;
              tmp_ppu20 = tmp_ppu20 + 3;
            } while (tmp_pu10 != *tmp_ppu1);
          }
          aiStack_4b9c8[aiStack_4b3a4[iStack_4bdf8 * 0x18b] * 2 + iStack_4bdf8 * 0x18b + 1] =
               (int)(&gScriptActions + tmp_i16 * 3);
          tmp_u11 = 0;
          do {
            *(uint32_t *)((int)auStack_4bdcc + tmp_u11) = 0;
            *(uint32_t *)((int)auStack_4bdcc + tmp_u11 + 4) = 0;
            tmp_u11 = tmp_u11 + 8;
          } while (tmp_u11 < 0x400);
          tmp_i13 = Q_stricmp(tmp_pu17,"set");
          if (tmp_i13 == 0) {
LAB_000bb309:
            tmp_pc8 = (char *)COM_Parse(&iStack_4bdd0);
            if (*tmp_pc8 != '{') {
              COM_ParseError("\'{\' expected, found: %s.\n",tmp_pc8);
            }
            while ((tmp_pc8 = (char *)COM_Parse(&iStack_4bdd0), tmp_pc8 != (char *)0x0 &&
                   (*tmp_pc8 != '}'))) {
              if ((char)auStack_4bdcc[0] != '\0') {
                Q_strcat(auStack_4bdcc,0x400,&g_unk_002612df);
              }
              tmp_pc24 = strrchr(tmp_pc8,0x20);
              if (tmp_pc24 != (char *)0x0) {
                Q_strcat(auStack_4bdcc,0x400,&g_unk_002480c8);
              }
              tmp_pc24 = tmp_pc8;
              Q_strcat(auStack_4bdcc,0x400);
              tmp_pc8 = strrchr(tmp_pc8,0x20);
              if (tmp_pc8 != (char *)0x0) {
                tmp_pc24 = "\"";
                Q_strcat(auStack_4bdcc,0x400);
              }
            }
          }
          else {
            tmp_i13 = Q_stricmp((&gScriptActions)[tmp_i16 * 3],"delete");
            if ((tmp_i13 == 0) ||
               (tmp_i13 = Q_stricmp((&gScriptActions)[tmp_i16 * 3],"create"), tmp_i13 == 0))
            goto LAB_000bb309;
            tmp_i13 = Q_stricmp(tmp_pc8,"spawnbot");
            if ((tmp_i13 != 0) && (tmp_pc8 = (char *)COM_ParseExt(&iStack_4bdd0,0), *tmp_pc8 != '\0'))
            {
              tmp_i13 = 0;
              do {
                if ((char)auStack_4bdcc[0] == '\0') {
                  if (tmp_i13 != 0) goto LAB_000bb57a;
LAB_000bb642:
                  tmp_ppu20 = &gScriptActions + tmp_i16 * 3;
                  tmp_i15 = Q_stricmp(*tmp_ppu20,"playsound");
                  if (tmp_i15 == 0) {
                    G_SoundIndex(tmp_pc8);
                  }
                  else {
                    tmp_i15 = Q_stricmp(*tmp_ppu20,"changemodel");
                    if (tmp_i15 == 0) {
                      G_ModelIndex(tmp_pc8);
                    }
                    else if (((tmp_i7 != 0) &&
                             ((((tmp_i15 = Q_stricmp(*tmp_ppu20,"mu_start"), tmp_i15 == 0 ||
                                (tmp_i15 = Q_stricmp(*tmp_ppu20,"mu_play"), tmp_i15 == 0)) ||
                               (tmp_i15 = Q_stricmp(*tmp_ppu20,"mu_queue"), tmp_i15 == 0)) ||
                              (tmp_i15 = Q_stricmp(*tmp_ppu20,"startcam"), tmp_i15 == 0)))) &&
                            (*tmp_pc8 != '\0')) {
                      tmp_u9 = va("addToBuild %s\n",tmp_pc8);
                      trap_SendServerCommand(0xffffffff,tmp_u9);
                    }
                  }
LAB_000bb678:
                  tmp_i15 = Q_stricmp((&gScriptActions)[tmp_i16 * 3],"remapshader");
                  if (tmp_i15 == 0) {
                    G_ShaderIndex(tmp_pc8);
                  }
                }
                else {
                  Q_strcat(auStack_4bdcc,0x400,&g_unk_002612df);
                  if (tmp_i13 == 0) goto LAB_000bb642;
LAB_000bb57a:
                  if (tmp_i13 == 1) goto LAB_000bb678;
                }
                tmp_pc24 = strrchr(tmp_pc8,0x20);
                if (tmp_pc24 != (char *)0x0) {
                  Q_strcat(auStack_4bdcc,0x400,&g_unk_002480c8);
                }
                tmp_pc24 = tmp_pc8;
                Q_strcat(auStack_4bdcc,0x400);
                tmp_pc8 = strrchr(tmp_pc8,0x20);
                if (tmp_pc8 != (char *)0x0) {
                  tmp_pc24 = "\"";
                  Q_strcat(auStack_4bdcc,0x400);
                }
                tmp_i13 = tmp_i13 + 1;
                tmp_pc8 = (char *)COM_ParseExt(&iStack_4bdd0,0);
              } while (*tmp_pc8 != '\0');
            }
          }
          if ((char)auStack_4bdcc[0] == '\0') {
            tmp_i16 = aiStack_4b3a4[iStack_4bdf8 * 0x18b];
          }
          else {
            tmp_i16 = aiStack_4b3a4[iStack_4bdf8 * 0x18b];
            tmp_pu19 = auStack_4bdcc;
            do {
              tmp_pu18 = tmp_pu19;
              tmp_u14 = *tmp_pu18 + 0xfefefeff & ~*tmp_pu18;
              tmp_u11 = tmp_u14 & 0x80808080;
              tmp_pu19 = tmp_pu18 + 1;
            } while (tmp_u11 == 0);
            if ((tmp_u14 & 0x8080) == 0) {
              tmp_pu19 = (uint *)((int)tmp_pu18 + 6);
              tmp_u11 = tmp_u11 >> 0x10;
            }
            tmp_i13 = G_Alloc((int)tmp_pu19 +
                             (-(int)auStack_4bdcc - (uint)CARRY1((byte)tmp_u11,(byte)tmp_u11)) + -2);
            aiStack_4b9c8[tmp_i16 * 2 + iStack_4bdf8 * 0x18b + 2] = tmp_i13;
            tmp_pu19 = auStack_4bdcc;
            do {
              tmp_pu18 = tmp_pu19;
              tmp_u14 = *tmp_pu18 + 0xfefefeff & ~*tmp_pu18;
              tmp_u11 = tmp_u14 & 0x80808080;
              tmp_pu19 = tmp_pu18 + 1;
            } while (tmp_u11 == 0);
            if ((tmp_u14 & 0x8080) == 0) {
              tmp_pu19 = (uint *)((int)tmp_pu18 + 6);
              tmp_u11 = tmp_u11 >> 0x10;
            }
            tmp_pc24 = (char *)((int)tmp_pu19 +
                              (-(int)auStack_4bdcc - (uint)CARRY1((byte)tmp_u11,(byte)tmp_u11)) + -2);
            Q_strncpyz(tmp_i13,auStack_4bdcc);
          }
          aiStack_4b3a4[iStack_4bdf8 * 0x18b] = tmp_i16 + 1;
          if (0xc3 < tmp_i16 + 1) {
            tmp_pc24 = (char *)COM_GetCurrentParseLine();
            G_Error("G_Script_ScriptParse(): script exceeded G_MAX_SCRIPT_STACK_ITEMS (%d), line %d\n"
                    ,0xc4,tmp_pc24);
          }
        }
        iStack_4bdf8 = iStack_4bdf8 + 1;
      }
      else {
        do {
          while( true ) {
            while( true ) {
              tmp_pc8 = (char *)COM_Parse(&iStack_4bdd0);
              if (tmp_pc8 == (char *)0x0) goto LAB_000badc0;
              tmp_c2 = *tmp_pc8;
              if (tmp_c2 != '\0') break;
              tmp_u9 = COM_GetCurrentParseLine();
              G_Error("G_Script_ScriptParse(), Error (line %d): \'}\' expected, end of script found.\n"
                      ,tmp_u9);
            }
            if (tmp_c2 != '{') break;
            iStack_4be00 = iStack_4be00 + 1;
          }
        } while ((tmp_c2 != '}') || (iStack_4be00 = iStack_4be00 + -1, iStack_4be00 != 0));
      }
      goto LAB_000badc0;
    }
    if (!tmp_b5) {
      tmp_u9 = COM_GetCurrentParseLine();
      G_Error("G_Script_ScriptParse(), Error (line %d): \'}\' expected, end of script found.\n",
              tmp_u9);
    }
LAB_000bb03d:
    if (iStack_4bdf8 != 0) {
      tmp_u11 = iStack_4bdf8 * 0x62c;
      tmp_pu12 = (uint32_t *)G_Alloc(tmp_u11);
      *(uint32_t **)(param_1 + 0x3b4) = tmp_pu12;
      if (7 < tmp_u11) {
        tmp_pu22 = tmp_pu12;
        if (((uint)tmp_pu12 & 1) != 0) {
          tmp_pu22 = (uint32_t *)((int)tmp_pu12 + 1);
          tmp_u11 = tmp_u11 - 1;
          __s = (uint32_t *)(auStack_4b9cc + 1);
          *(uint8_t *)tmp_pu12 = auStack_4b9cc[0];
        }
        tmp_pu21 = tmp_pu22;
        if (((uint)tmp_pu22 & 2) != 0) {
          tmp_u3 = *(uint16_t *)__s;
          tmp_pu21 = (uint32_t *)((int)tmp_pu22 + 2);
          __s = (uint32_t *)((int)__s + 2);
          tmp_u11 = tmp_u11 - 2;
          *(uint16_t *)tmp_pu22 = tmp_u3;
        }
        tmp_pu12 = tmp_pu21;
        if (((uint)tmp_pu21 & 4) != 0) {
          tmp_u9 = *__s;
          tmp_pu12 = tmp_pu21 + 1;
          __s = __s + 1;
          tmp_u11 = tmp_u11 - 4;
          *tmp_pu21 = tmp_u9;
        }
      }
      for (; tmp_u11 != 0; tmp_u11 = tmp_u11 - 1) {
        *(uint8_t *)tmp_pu12 = *(uint8_t *)__s;
        __s = (uint32_t *)((int)__s + (uint)tmp_b23 * -2 + 1);
        tmp_pu12 = (uint32_t *)((int)tmp_pu12 + (uint)tmp_b23 * -2 + 1);
      }
      *(int *)(param_1 + 0x3b0) = iStack_4bdf8;
    }
  }
  return;
}

void G_Script_ScriptChange(int param_1,uint32_t param_2)
{
  uint16_t tmp_u1;
  uint tmp_u2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  uint32_t *tmp_pu9;
  int tmp_i10;
  uint16_t *tmp_pu11;
  uint16_t *tmp_pu12;
  int tmp_i13;
  bool tmp_b14;
  uint8_t local_38 [12];
  int local_2c;
  
  tmp_pu12 = (uint16_t *)(param_1 + 0x3b8);
  tmp_pu9 = (uint32_t *)local_38;
  tmp_u2 = 0;
  do {
    *(uint32_t *)((int)tmp_pu9 + tmp_u2) = *(uint32_t *)((int)tmp_pu12 + tmp_u2);
    tmp_u2 = tmp_u2 + 4;
  } while (tmp_u2 < 0x1c);
  tmp_u2 = *(uint *)(param_1 + 0x3c8);
  *(uint32_t *)(param_1 + 0x3b8) = 0;
  *(uint32_t *)(param_1 + 0x3c0) = param_2;
  *(int *)(param_1 + 0x3bc) = g_unk_00abe908;
  *(int *)(param_1 + 0x3c4) = local_2c + 1;
  tmp_u3 = tmp_u2 | 4;
  *(uint *)(param_1 + 0x3c8) = tmp_u3;
  if (*(int *)(param_1 + 0x3b4) == 0) goto LAB_000bba3f;
  if ((tmp_u2 & 1) != 0) {
    G_ScriptAction_GotoMarker(param_1,0);
    tmp_u3 = *(uint *)(param_1 + 0x3c8);
  }
  if ((tmp_u3 & 2) == 0) {
    tmp_i5 = *(int *)(param_1 + 0x3c0);
    if (tmp_i5 < 0) goto LAB_000bbae0;
LAB_000bb902:
    tmp_i4 = tmp_i5 * 0x62c + *(int *)(param_1 + 0x3b4);
    tmp_i5 = *(int *)(tmp_i4 + 0x628);
    if (tmp_i5 == 0) {
      tmp_i10 = *(int *)(param_1 + 0x3c4);
      *(uint32_t *)(param_1 + 0x3c0) = 0xffffffff;
    }
    else {
      if (GHIDRA_FIELD(g_scriptDebug, 12, 4) == 0) {
        tmp_i6 = *(int *)(param_1 + 0x3b8);
      }
      else {
        tmp_i6 = *(int *)(param_1 + 0x3b8);
        if ((*(int *)(param_1 + 0x3bc) == g_unk_00abe908) && (tmp_i6 < tmp_i5)) {
          tmp_i5 = tmp_i4 + tmp_i6 * 8;
          tmp_pu7 = *(uint8_t **)(tmp_i5 + 0xc);
          if (tmp_pu7 == (uint8_t *)0x0) {
            tmp_pu7 = &g_unk_0026ea14;
          }
          G_Printf("%i : (%s) GScript command: %s %s\n",*(int *)(param_1 + 0x3bc),
                   *(uint32_t *)(param_1 + 0x3ac),**(uint32_t **)(tmp_i5 + 8),tmp_pu7);
          tmp_i6 = *(int *)(param_1 + 0x3b8);
          tmp_i5 = *(int *)(tmp_i4 + 0x628);
        }
      }
      tmp_i10 = *(int *)(param_1 + 0x3c4);
      tmp_i13 = tmp_i10;
      if (tmp_i6 < tmp_i5) {
        do {
          tmp_i5 = tmp_i4 + tmp_i6 * 8;
          tmp_i5 = (**(void **)(*(int *)(tmp_i5 + 8) + 4))(param_1,*(uint32_t *)(tmp_i5 + 0xc));
          if (tmp_i5 == 0) goto LAB_000bbab0;
          tmp_i10 = *(int *)(param_1 + 0x3c4);
          if (tmp_i10 != tmp_i13) {
            return;
          }
          tmp_i5 = *(int *)(param_1 + 0x3b8);
          *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) | 4;
          tmp_i13 = g_unk_00abe908;
          tmp_i6 = tmp_i5 + 1;
          tmp_b14 = GHIDRA_FIELD(g_scriptDebug, 12, 4) != 0;
          *(int *)(param_1 + 0x3b8) = tmp_i6;
          *(int *)(param_1 + 0x3bc) = tmp_i13;
          tmp_i8 = *(int *)(tmp_i4 + 0x628);
          if ((tmp_b14) && (tmp_i6 < tmp_i8)) {
            tmp_i5 = tmp_i4 + tmp_i5 * 8;
            tmp_pu7 = *(uint8_t **)(tmp_i5 + 0x14);
            if (tmp_pu7 == (uint8_t *)0x0) {
              tmp_pu7 = &g_unk_0026ea14;
            }
            G_Printf("%i : (%s) GScript command: %s %s\n",tmp_i13,*(uint32_t *)(param_1 + 0x3ac),
                     **(uint32_t **)(tmp_i5 + 0x10),tmp_pu7);
            tmp_i10 = *(int *)(param_1 + 0x3c4);
            tmp_i6 = *(int *)(param_1 + 0x3b8);
            tmp_i8 = *(int *)(tmp_i4 + 0x628);
          }
          tmp_i13 = tmp_i10;
        } while (tmp_i6 < tmp_i8);
      }
      *(uint32_t *)(param_1 + 0x3c0) = 0xffffffff;
    }
  }
  else {
    G_ScriptAction_PlayAnim(param_1,*(uint32_t *)(param_1 + 0x3d0));
    tmp_i5 = *(int *)(param_1 + 0x3c0);
    if (-1 < tmp_i5) goto LAB_000bb902;
LAB_000bbae0:
    tmp_i10 = *(int *)(param_1 + 0x3c4);
  }
  if (local_2c + 1 != tmp_i10) {
    return;
  }
LAB_000bba3f:
  tmp_u2 = 0x1c;
  tmp_b14 = ((uint)tmp_pu12 & 1) != 0;
  if (tmp_b14) {
    tmp_pu12 = (uint16_t *)(param_1 + 0x3b9);
    tmp_u2 = 0x1b;
    tmp_pu9 = (uint32_t *)((int)local_38 + 1);
    *(uint8_t *)(param_1 + 0x3b8) = local_38[0];
  }
  tmp_pu11 = tmp_pu12;
  if (((uint)tmp_pu12 & 2) != 0) {
    tmp_u1 = *(uint16_t *)tmp_pu9;
    tmp_pu11 = tmp_pu12 + 1;
    tmp_pu9 = (uint32_t *)((int)tmp_pu9 + 2);
    tmp_u2 = tmp_u2 - 2;
    *tmp_pu12 = tmp_u1;
  }
  tmp_u3 = 0;
  do {
    *(uint32_t *)((int)tmp_pu11 + tmp_u3) = *(uint32_t *)((int)tmp_pu9 + tmp_u3);
    tmp_u3 = tmp_u3 + 4;
  } while (tmp_u3 < (tmp_u2 & 0xfffffffc));
  tmp_i5 = 0;
  if ((tmp_u2 & 2) != 0) {
    tmp_i5 = 2;
    *(uint16_t *)((int)tmp_pu11 + tmp_u3) = *(uint16_t *)((int)tmp_pu9 + tmp_u3);
  }
  if (tmp_b14) {
    *(uint8_t *)((int)((int)tmp_pu11 + tmp_u3) + tmp_i5) =
         *(uint8_t *)((int)((int)tmp_pu9 + tmp_u3) + tmp_i5);
  }
LAB_000bbab0:
  *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) & 0xfffffffb;
  return;
}

void G_Script_EventStringInit(void)
{
  return;
}

int G_Script_GetEventIndex(int param_1,uint32_t param_2,uint8_t *param_3)
{
  uint8_t **tmp_ppu1;
  void *tmp_pc2;
  uint8_t *tmp_pu3;
  int *tmp_pi4;
  int tmp_i5;
  uint8_t **tmp_ppu6;
  uint8_t *tmp_pu7;
  int tmp_i8;
  int tmp_i9;
  int tmp_i10;
  
  tmp_pu3 = (uint8_t *)nitrox_GetTokenForString(param_2);
  if (gScriptEvents == (uint8_t *)0x0) {
LAB_000bbc20:
    if (GHIDRA_FIELD(g_cheats, 12, 4) != 0) {
      G_Printf("devmode-> G_Script_GetEventIndex(), unknown event: %s\n",param_2);
    }
  }
  else {
    if (g_unk_002ba4a8 == tmp_pu3) {
      tmp_i8 = 0;
    }
    else {
      tmp_i8 = 0;
      tmp_ppu6 = &g_ptr_s_trigger_00257751_0xe_002ba4ac;
      do {
        tmp_i8 = tmp_i8 + 1;
        if (*tmp_ppu6 == (uint8_t *)0x0) goto LAB_000bbc20;
        tmp_ppu1 = tmp_ppu6 + 2;
        tmp_ppu6 = tmp_ppu6 + 3;
      } while (*tmp_ppu1 != tmp_pu3);
    }
    if (GHIDRA_FIELD(g_scriptDebug, 12, 4) != 0) {
      tmp_pu7 = param_3;
      if (param_3 == (uint8_t *)0x0) {
        tmp_pu7 = &g_unk_0026ea14;
      }
      tmp_pu3 = *(uint8_t **)(param_1 + 0x3ac);
      if (*(uint8_t **)(param_1 + 0x3ac) == (uint8_t *)0x0) {
        tmp_pu3 = &g_unk_0024ee2f;
      }
      G_Printf("%i : (%s) GScript event: %s %s\n",g_unk_00abe908,tmp_pu3,param_2,tmp_pu7);
    }
    tmp_i5 = *(int *)(param_1 + 0x3b0);
    tmp_i10 = 0;
    tmp_i9 = 0;
    if (0 < tmp_i5) {
      do {
        tmp_pi4 = (int *)(*(int *)(param_1 + 0x3b4) + tmp_i10);
        if (*tmp_pi4 == tmp_i8) {
          if (((tmp_pi4[1] == 0) ||
              (tmp_pc2 = *(void **)(tmp_i8 * 0xc + 0x2ba4a4), tmp_pc2 == (void *)0x0)) ||
             (tmp_i5 = (*tmp_pc2)(tmp_pi4,param_3), tmp_i5 != 0)) {
            return tmp_i9;
          }
          tmp_i5 = *(int *)(param_1 + 0x3b0);
        }
        tmp_i9 = tmp_i9 + 1;
        tmp_i10 = tmp_i10 + 0x62c;
      } while (tmp_i9 < tmp_i5);
    }
  }
  return -1;
}

uint32_t G_Script_ScriptRun(int param_1)
{
  int tmp_i1;
  uint tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint8_t *tmp_pu5;
  uint32_t *tmp_pu6;
  int tmp_i7;
  int tmp_i8;
  bool tmp_b9;
  
  if (*(int *)(param_1 + 0x3b4) != 0) {
    tmp_u2 = *(uint *)(param_1 + 0x3c8);
    if ((tmp_u2 & 1) != 0) {
      G_ScriptAction_GotoMarker(param_1,0);
      tmp_u2 = *(uint *)(param_1 + 0x3c8);
    }
    if ((tmp_u2 & 2) == 0) {
      tmp_i4 = *(int *)(param_1 + 0x3c0);
    }
    else {
      G_ScriptAction_PlayAnim(param_1,*(uint32_t *)(param_1 + 0x3d0));
      tmp_i4 = *(int *)(param_1 + 0x3c0);
    }
    if (tmp_i4 < 0) {
      return 1;
    }
    tmp_i8 = tmp_i4 * 0x62c + *(int *)(param_1 + 0x3b4);
    tmp_i4 = *(int *)(tmp_i8 + 0x628);
    if (tmp_i4 != 0) {
      if (GHIDRA_FIELD(g_scriptDebug, 12, 4) == 0) {
        tmp_i3 = *(int *)(param_1 + 0x3b8);
      }
      else {
        tmp_i7 = *(int *)(param_1 + 0x3bc);
        tmp_i3 = *(int *)(param_1 + 0x3b8);
        if ((tmp_i7 == g_unk_00abe908) && (tmp_i3 < tmp_i4)) {
          tmp_i4 = tmp_i8 + tmp_i3 * 8;
          tmp_pu5 = *(uint8_t **)(tmp_i4 + 0xc);
          if (tmp_pu5 == (uint8_t *)0x0) {
            tmp_pu5 = &g_unk_0026ea14;
          }
          tmp_pu6 = *(uint32_t **)(tmp_i4 + 8);
          goto LAB_000bbe57;
        }
      }
      while (tmp_i3 < tmp_i4) {
        while( true ) {
          tmp_i4 = tmp_i8 + tmp_i3 * 8;
          tmp_i3 = *(int *)(param_1 + 0x3c4);
          tmp_i4 = (**(void **)(*(int *)(tmp_i4 + 8) + 4))(param_1,*(uint32_t *)(tmp_i4 + 0xc));
          if (tmp_i4 == 0) {
            *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) & 0xfffffffb;
            return 0;
          }
          if (*(int *)(param_1 + 0x3c4) != tmp_i3) {
            return 0;
          }
          tmp_i1 = *(int *)(param_1 + 0x3b8);
          *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) | 4;
          tmp_i7 = g_unk_00abe908;
          tmp_b9 = GHIDRA_FIELD(g_scriptDebug, 12, 4) == 0;
          tmp_i3 = tmp_i1 + 1;
          *(int *)(param_1 + 0x3b8) = tmp_i3;
          *(int *)(param_1 + 0x3bc) = tmp_i7;
          tmp_i4 = *(int *)(tmp_i8 + 0x628);
          if ((tmp_b9) || (tmp_i4 <= tmp_i3)) break;
          tmp_i4 = tmp_i8 + tmp_i1 * 8;
          tmp_pu5 = *(uint8_t **)(tmp_i4 + 0x14);
          if (tmp_pu5 == (uint8_t *)0x0) {
            tmp_pu5 = &g_unk_0026ea14;
          }
          tmp_pu6 = *(uint32_t **)(tmp_i4 + 0x10);
LAB_000bbe57:
          G_Printf("%i : (%s) GScript command: %s %s\n",tmp_i7,*(uint32_t *)(param_1 + 0x3ac),
                   *tmp_pu6,tmp_pu5);
          tmp_i3 = *(int *)(param_1 + 0x3b8);
          if (*(int *)(tmp_i8 + 0x628) <= tmp_i3) goto LAB_000bbe90;
        }
      }
    }
  }
LAB_000bbe90:
  *(uint32_t *)(param_1 + 0x3c0) = 0xffffffff;
  return 1;
}

void G_Script_ScriptEvent(int param_1,uint32_t param_2,uint32_t param_3)
{
  uint16_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  uint32_t tmp_u4;
  char *tmp_pc5;
  uint32_t *tmp_pu6;
  uint tmp_u7;
  uint16_t *tmp_pu8;
  uint16_t *tmp_pu9;
  bool tmp_b10;
  uint8_t local_38 [12];
  int local_2c;
  
  tmp_i2 = G_Script_GetEventIndex(param_1,param_2,param_3);
  if (-1 < tmp_i2) {
    tmp_pu9 = (uint16_t *)(param_1 + 0x3b8);
    tmp_u7 = 0;
    tmp_pu6 = (uint32_t *)local_38;
    do {
      *(uint32_t *)((int)tmp_pu6 + tmp_u7) = *(uint32_t *)((int)tmp_pu9 + tmp_u7);
      tmp_u7 = tmp_u7 + 4;
    } while (tmp_u7 < 0x1c);
    *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) | 4;
    *(int *)(param_1 + 0x3c0) = tmp_i2;
    *(uint32_t *)(param_1 + 0x3b8) = 0;
    *(uint32_t *)(param_1 + 0x3bc) = g_unk_00abe908;
    *(int *)(param_1 + 0x3c4) = local_2c + 1;
    tmp_i2 = G_Script_ScriptRun(param_1);
    if ((tmp_i2 != 0) && (local_2c + 1 == *(int *)(param_1 + 0x3c4))) {
      tmp_b10 = ((uint)tmp_pu9 & 1) != 0;
      tmp_u7 = 0x1c;
      if (tmp_b10) {
        tmp_pu9 = (uint16_t *)(param_1 + 0x3b9);
        tmp_u7 = 0x1b;
        tmp_pu6 = (uint32_t *)((int)local_38 + 1);
        *(uint8_t *)(param_1 + 0x3b8) = local_38[0];
      }
      tmp_pu8 = tmp_pu9;
      if (((uint)tmp_pu9 & 2) != 0) {
        tmp_u1 = *(uint16_t *)tmp_pu6;
        tmp_pu8 = tmp_pu9 + 1;
        tmp_pu6 = (uint32_t *)((int)tmp_pu6 + 2);
        tmp_u7 = tmp_u7 - 2;
        *tmp_pu9 = tmp_u1;
      }
      tmp_u3 = 0;
      do {
        *(uint32_t *)((int)tmp_pu8 + tmp_u3) = *(uint32_t *)((int)tmp_pu6 + tmp_u3);
        tmp_u3 = tmp_u3 + 4;
      } while (tmp_u3 < (tmp_u7 & 0xfffffffc));
      tmp_i2 = 0;
      if ((tmp_u7 & 2) != 0) {
        *(uint16_t *)((int)tmp_pu8 + tmp_u3) = *(uint16_t *)((int)tmp_pu6 + tmp_u3);
        tmp_i2 = 2;
      }
      if (tmp_b10) {
        *(uint8_t *)((int)((int)tmp_pu8 + tmp_u3) + tmp_i2) =
             *(uint8_t *)((int)((int)tmp_pu6 + tmp_u3) + tmp_i2);
      }
      *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) & 0xfffffffb;
    }
  }
  tmp_u4 = nitrox_GetTokenForString(param_2);
  switch(tmp_u4) {
  case 0xaf:
    if (*(int *)(param_1 + 0x218) == 0) {
      tmp_u4 = *(uint32_t *)(param_1 + 0x3a8);
    }
    else {
      tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x3a8);
    }
    tmp_u4 = va("Defused at %s.",tmp_u4);
    Bot_Util_SendTrigger(param_1,0,tmp_u4,param_2);
    if (*(int *)(param_1 + 0x218) == 0) {
      tmp_u4 = *(uint32_t *)(param_1 + 0x3a8);
    }
    else {
      tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x3a8);
    }
    G_LogPrintf("nitmod popup: %s defused \"%s\"\n",param_3,tmp_u4);
    break;
  case 0xb0:
    if (*(int *)(param_1 + 0x218) == 0) {
      tmp_u4 = *(uint32_t *)(param_1 + 0x3a8);
    }
    else {
      tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x3a8);
    }
    tmp_u4 = va("Planted at %s.",tmp_u4);
    Bot_Util_SendTrigger(param_1,0,tmp_u4,param_2);
    if (*(int *)(param_1 + 0x218) == 0) {
      tmp_u4 = *(uint32_t *)(param_1 + 0x3a8);
    }
    else {
      tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x3a8);
    }
    G_LogPrintf("nitmod popup: %s planted \"%s\"\n",param_3,tmp_u4);
    break;
  case 0xb3:
    tmp_i2 = Q_stricmp(param_3,"stolen");
    if (tmp_i2 == 0) {
      if (*(int *)(param_1 + 0x5c0) == 0x36af1) {
        tmp_pc5 = "putaxis";
      }
      else {
        tmp_pc5 = "putallies";
      }
      G_LogPrintf("nitmod popup: %s stole \"%s\"\n",tmp_pc5 + 3,*(uint32_t *)(param_1 + 0x248));
    }
    else {
      tmp_i2 = Q_stricmp(param_3,"returned");
      if (tmp_i2 == 0) {
        if (*(int *)(param_1 + 0x5c0) == 0x36af1) {
          tmp_pc5 = "putallies";
        }
        else {
          tmp_pc5 = "putaxis";
        }
        G_LogPrintf("nitmod popup: %s returned \"%s\"\n",tmp_pc5 + 3,*(uint32_t *)(param_1 + 0x248)
                   );
      }
      else {
        tmp_i2 = Q_stricmp(param_3,"dropped");
        if (tmp_i2 == 0) {
          if (*(int *)(param_1 + 0x5c0) == 0x36af1) {
            tmp_pc5 = "putaxis";
          }
          else {
            tmp_pc5 = "putallies";
          }
          G_LogPrintf("nitmod popup: %s dropped \"%s\"\n",tmp_pc5 + 3,
                      *(uint32_t *)(param_1 + 0x248));
        }
      }
    }
    break;
  case 0xba:
    if (*(int *)(param_1 + 0x218) == 0) {
      tmp_u4 = *(uint32_t *)(param_1 + 0x3a8);
    }
    else {
      tmp_u4 = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x3a8);
    }
    tmp_pc5 = "%s Destroyed.";
    goto LAB_000bc166;
  case 0xbb:
    tmp_u4 = _GetEntityName(param_1);
    tmp_pc5 = "Explode_%s Exploded.";
LAB_000bc166:
    tmp_u4 = va(tmp_pc5,tmp_u4);
    Bot_Util_SendTrigger(param_1,0,tmp_u4,param_2);
  }
  return;
}

void script_mover_use(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  bool tmp_b4;
  
  tmp_u3 = *(uint *)(param_1 + 0x1a8);
  if ((tmp_u3 & 8) == 0) {
    if ((tmp_u3 & 0x80) != 0) {
      tmp_u1 = BG_StringHashValue(param_1 + 0x4c0);
      tmp_i2 = G_FindByTargetnameFast(0,param_1 + 0x4c0,tmp_u1);
      if (tmp_i2 == 0) {
        tmp_i2 = param_1;
      }
      *(int *)(param_1 + 0x21c) = tmp_i2;
      *(int *)(param_1 + 0x114) = (tmp_i2 + -0x93e4a0 >> 9) * -0x55555555;
      tmp_u3 = *(uint *)(param_1 + 0x1a8);
    }
    tmp_b4 = (tmp_u3 & 2) != 0;
    if (!tmp_b4) {
      *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 2;
    }
    tmp_u3 = (uint)tmp_b4;
    *(uint *)(param_1 + 0x14c) = tmp_u3;
    *(uint *)(param_1 + 0x1d4) = tmp_u3;
    trap_LinkEntity(param_1);
    *(void **)(param_1 + 0x2a4) = script_mover_think;
    *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 200;
    return;
  }
  tmp_i2 = *(int *)(param_1 + 0x2e4);
  if (tmp_i2 != 0) {
    *(int *)(param_1 + 0x2c8) = tmp_i2;
    *(int *)(param_1 + 0x9c) = tmp_i2;
    G_Script_ScriptEvent(param_1,"rebirth",&g_unk_0026ea14);
    *(void **)(param_1 + 700) = script_mover_die;
    return;
  }
  return;
}

void script_mover_die(int param_1)
{
  uint16_t tmp_u1;
  int tmp_i2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  uint32_t *tmp_pu5;
  uint tmp_u6;
  uint16_t *tmp_pu7;
  uint16_t *tmp_pu8;
  bool tmp_b9;
  uint local_48;
  uint8_t local_38 [12];
  int local_2c;
  
  tmp_i2 = G_Script_GetEventIndex(param_1,"death",&g_unk_0026ea14);
  if (-1 < tmp_i2) {
    tmp_pu5 = (uint32_t *)local_38;
    tmp_pu8 = (uint16_t *)(param_1 + 0x3b8);
    tmp_u6 = 0;
    do {
      *(uint32_t *)((int)tmp_pu5 + tmp_u6) = *(uint32_t *)((int)tmp_pu8 + tmp_u6);
      tmp_u6 = tmp_u6 + 4;
    } while (tmp_u6 < 0x1c);
    *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) | 4;
    *(int *)(param_1 + 0x3c0) = tmp_i2;
    *(uint32_t *)(param_1 + 0x3b8) = 0;
    *(uint32_t *)(param_1 + 0x3bc) = g_unk_00abe908;
    *(int *)(param_1 + 0x3c4) = local_2c + 1;
    tmp_i2 = G_Script_ScriptRun(param_1);
    if ((tmp_i2 != 0) && (local_2c + 1 == *(int *)(param_1 + 0x3c4))) {
      tmp_b9 = ((uint)tmp_pu8 & 1) != 0;
      local_48 = 0x1c;
      if (tmp_b9) {
        tmp_pu8 = (uint16_t *)(param_1 + 0x3b9);
        tmp_pu5 = (uint32_t *)((int)local_38 + 1);
        *(uint8_t *)(param_1 + 0x3b8) = local_38[0];
        local_48 = 0x1b;
      }
      tmp_pu7 = tmp_pu8;
      if (((uint)tmp_pu8 & 2) != 0) {
        tmp_u1 = *(uint16_t *)tmp_pu5;
        tmp_pu7 = tmp_pu8 + 1;
        tmp_pu5 = (uint32_t *)((int)tmp_pu5 + 2);
        *tmp_pu8 = tmp_u1;
        local_48 = local_48 - 2;
      }
      tmp_u6 = 0;
      do {
        *(uint32_t *)((int)tmp_pu7 + tmp_u6) = *(uint32_t *)((int)tmp_pu5 + tmp_u6);
        tmp_u6 = tmp_u6 + 4;
      } while (tmp_u6 < (local_48 & 0xfffffffc));
      tmp_i2 = 0;
      if ((local_48 & 2) != 0) {
        *(uint16_t *)((int)tmp_pu7 + tmp_u6) = *(uint16_t *)((int)tmp_pu5 + tmp_u6);
        tmp_i2 = 2;
      }
      if (tmp_b9) {
        *(uint8_t *)((int)((int)tmp_pu7 + tmp_u6) + tmp_i2) =
             *(uint8_t *)((int)((int)tmp_pu5 + tmp_u6) + tmp_i2);
      }
      *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) & 0xfffffffb;
    }
  }
  tmp_u3 = nitrox_GetTokenForString("death");
  switch(tmp_u3) {
  case 0xaf:
    if (*(int *)(param_1 + 0x218) == 0) {
      tmp_u3 = *(uint32_t *)(param_1 + 0x3a8);
    }
    else {
      tmp_u3 = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x3a8);
    }
    tmp_u3 = va("Defused at %s.",tmp_u3);
    Bot_Util_SendTrigger(param_1,0,tmp_u3,"death");
    if (*(int *)(param_1 + 0x218) == 0) {
      tmp_u3 = *(uint32_t *)(param_1 + 0x3a8);
    }
    else {
      tmp_u3 = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x3a8);
    }
    G_LogPrintf("nitmod popup: %s defused \"%s\"\n",&g_unk_0026ea14,tmp_u3);
    break;
  case 0xb0:
    if (*(int *)(param_1 + 0x218) == 0) {
      tmp_u3 = *(uint32_t *)(param_1 + 0x3a8);
    }
    else {
      tmp_u3 = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x3a8);
    }
    tmp_u3 = va("Planted at %s.",tmp_u3);
    Bot_Util_SendTrigger(param_1,0,tmp_u3,"death");
    if (*(int *)(param_1 + 0x218) == 0) {
      tmp_u3 = *(uint32_t *)(param_1 + 0x3a8);
    }
    else {
      tmp_u3 = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x3a8);
    }
    G_LogPrintf("nitmod popup: %s planted \"%s\"\n",&g_unk_0026ea14,tmp_u3);
    break;
  case 0xb3:
    tmp_i2 = Q_stricmp(&g_unk_0026ea14,"stolen");
    if (tmp_i2 == 0) {
      if (*(int *)(param_1 + 0x5c0) == 0x36af1) {
        tmp_pc4 = "putaxis";
      }
      else {
        tmp_pc4 = "putallies";
      }
      G_LogPrintf("nitmod popup: %s stole \"%s\"\n",tmp_pc4 + 3,*(uint32_t *)(param_1 + 0x248));
    }
    else {
      tmp_i2 = Q_stricmp(&g_unk_0026ea14,"returned");
      if (tmp_i2 == 0) {
        if (*(int *)(param_1 + 0x5c0) == 0x36af1) {
          tmp_pc4 = "putallies";
        }
        else {
          tmp_pc4 = "putaxis";
        }
        G_LogPrintf("nitmod popup: %s returned \"%s\"\n",tmp_pc4 + 3,*(uint32_t *)(param_1 + 0x248)
                   );
      }
      else {
        tmp_i2 = Q_stricmp(&g_unk_0026ea14,"dropped");
        if (tmp_i2 == 0) {
          if (*(int *)(param_1 + 0x5c0) == 0x36af1) {
            tmp_pc4 = "putaxis";
          }
          else {
            tmp_pc4 = "putallies";
          }
          G_LogPrintf("nitmod popup: %s dropped \"%s\"\n",tmp_pc4 + 3,
                      *(uint32_t *)(param_1 + 0x248));
        }
      }
    }
    break;
  case 0xba:
    if (*(int *)(param_1 + 0x218) == 0) {
      tmp_u3 = *(uint32_t *)(param_1 + 0x3a8);
    }
    else {
      tmp_u3 = *(uint32_t *)(*(int *)(param_1 + 0x218) + 0x3a8);
    }
    tmp_pc4 = "%s Destroyed.";
    goto LAB_000bc76e;
  case 0xbb:
    tmp_u3 = _GetEntityName(param_1);
    tmp_pc4 = "Explode_%s Exploded.";
LAB_000bc76e:
    tmp_u3 = va(tmp_pc4,tmp_u3);
    Bot_Util_SendTrigger(param_1,0,tmp_u3,"death");
  }
  if ((*(byte *)(param_1 + 0x1a8) & 8) == 0) {
    G_FreeEntity(param_1);
  }
  if (*(int *)(param_1 + 0x444) != 0) {
    G_LeaveTank(*(int *)(param_1 + 0x444),1,0);
  }
  *(uint32_t *)(param_1 + 700) = 0;
  return;
}

void script_linkentity(uint32_t param_1)
{
  trap_LinkEntity(param_1);
  return;
}

void script_model_med_spawn(int param_1)
{
  uint32_t tmp_u1;
  
  if ((*(byte *)(param_1 + 0x1a8) & 2) != 0) {
    *(uint32_t *)(param_1 + 0x1d4) = 1;
    *(uint32_t *)(param_1 + 0x14c) = 1;
  }
  *(uint32_t *)(param_1 + 4) = 0;
  tmp_u1 = G_ModelIndex(*(uint32_t *)(param_1 + 0x1b4));
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(uint32_t *)(param_1 + 0xa4) = tmp_u1;
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0xb0) = 0;
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  trap_LinkEntity(param_1);
  return;
}

uint32_t G_ScriptAction_SetModelFromBrushmodel(int param_1,uint32_t param_2)
{
  bool tmp_b1;
  bool tmp_b2;
  char *tmp_pc3;
  int tmp_i4;
  int tmp_i5;
  uint32_t tmp_u6;
  uint8_t *tmp_pu7;
  uint32_t local_60;
  uint8_t local_5c;
  char local_5b;
  
  local_60 = param_2;
  tmp_pc3 = (char *)COM_ParseExt(&local_60,0);
  if (*tmp_pc3 == '\0') {
    G_Error("G_Scripting: setmodelfrombrushmodel must have an targetname\n");
  }
  Q_strncpyz(&local_5c,tmp_pc3,0x40);
  *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) & 0xffffbfff;
  if (*tmp_pc3 == '\0') {
    if (local_5b != '*') {
      tmp_b1 = true;
      goto LAB_000bd513;
    }
    trap_SetBrushModel(param_1,&local_5c);
  }
  else {
    tmp_b2 = true;
    do {
      tmp_i4 = Q_stricmp(tmp_pc3,"useoriginforpvs");
      if (tmp_i4 == 0) {
        *(uint *)(param_1 + 0x128) = *(uint *)(param_1 + 0x128) | 0x4000;
        tmp_b1 = tmp_b2;
      }
      else {
        tmp_i4 = Q_stricmp(tmp_pc3,"nonsolid");
        tmp_b1 = false;
        if (tmp_i4 != 0) {
          tmp_b1 = tmp_b2;
        }
      }
      tmp_pc3 = (char *)COM_ParseExt(&local_60,0);
      tmp_b2 = tmp_b1;
    } while (*tmp_pc3 != '\0');
    if (local_5b != '*') {
LAB_000bd513:
      tmp_i4 = 0;
      tmp_pu7 = &g_unk_02a98498;
      if (0 < g_unk_02a99698) {
        do {
          tmp_i5 = Q_stricmp(tmp_pu7,&local_5c);
          if (tmp_i5 == 0) {
            tmp_u6 = va(&g_unk_0024d859,(&g_unk_02a984b8)[tmp_i4 * 9]);
            trap_SetBrushModel(param_1,tmp_u6);
            goto joined_r0x000bd59e;
          }
          tmp_i4 = tmp_i4 + 1;
          tmp_pu7 = tmp_pu7 + 0x24;
        } while (tmp_i4 < g_unk_02a99698);
      }
      G_Error("G_Scripting: setmodelfrombrushmodel target not found %s\n",&local_5c);
      return 1;
    }
    trap_SetBrushModel(param_1,&local_5c);
joined_r0x000bd59e:
    if (!tmp_b1) {
      *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 2;
      *(uint32_t *)(param_1 + 0x1d4) = 0;
      *(uint32_t *)(param_1 + 0x14c) = 0;
      trap_LinkEntity(param_1);
      return 1;
    }
  }
  return 1;
}

uint32_t G_ScriptAction_SetPosition(int param_1,uint32_t param_2)
{
  char *tmp_pc1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint32_t local_20 [4];
  
  local_20[0] = param_2;
  tmp_pc1 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: setposition must have an targetname\n");
    tmp_i2 = BG_Find_PathCorner(tmp_pc1);
  }
  else {
    tmp_i2 = BG_Find_PathCorner(tmp_pc1);
  }
  if (tmp_i2 == 0) {
    tmp_u3 = BG_StringHashValue(tmp_pc1);
    tmp_i2 = G_FindByTargetnameFast(0,tmp_pc1,tmp_u3);
    if (tmp_i2 == 0) {
      G_Error("G_Scripting: can\'t find entity with \"targetname\" = \"%s\"\n",tmp_pc1);
    }
    G_SetOrigin(param_1,tmp_i2 + 0x168);
    if (*(int *)(param_1 + 400) != 0) {
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x14) = *(uint32_t *)(tmp_i2 + 0x168);
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x18) = *(uint32_t *)(tmp_i2 + 0x16c);
      *(uint32_t *)(*(int *)(param_1 + 400) + 0x1c) = *(uint32_t *)(tmp_i2 + 0x170);
    }
  }
  else {
    G_SetOrigin(param_1,tmp_i2 + 0x40);
  }
  return 1;
}

uint32_t G_ScriptAction_SetAutoSpawn(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  long tmp_l2;
  int tmp_i3;
  uint32_t tmp_u4;
  int *local_70;
  uint32_t local_60;
  uint8_t local_5c [76];
  
  local_60 = param_2;
  tmp_pc1 = (char *)COM_ParseExt(&local_60,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: setautospawn must have a target spawn\n");
  }
  Q_strncpyz(local_5c,tmp_pc1,0x40);
  tmp_pc1 = (char *)COM_ParseExt(&local_60,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: setautospawn must have a target team\n");
  }
  tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
  if (tmp_l2 == 0) {
    local_70 = &g_unk_02aa29b8;
  }
  else {
    local_70 = &g_unk_02aa29bc;
  }
  tmp_i3 = G_Find(0,0x248,local_5c);
  if (tmp_i3 == 0) {
    G_Error("G_Scripting: setautospawn, couldn\'t find target\n");
  }
  tmp_u4 = 0;
  if (*(int *)(tmp_i3 + 0x2e4) != 0) {
    if (tmp_l2 == 0) {
      tmp_pc1 = "Axis";
    }
    else {
      tmp_pc1 = "Allied";
    }
    G_Printf("Setting %s autospawn to %s\n",tmp_pc1,local_5c);
    *local_70 = *(int *)(tmp_i3 + 0x2e4) + -0x273;
    G_UpdateSpawnCounts();
    tmp_u4 = 1;
  }
  return tmp_u4;
}

uint32_t G_ScriptAction_ChangeModel(int param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t local_60;
  uint8_t local_5c [76];
  
  local_60 = param_2;
  tmp_pc1 = (char *)COM_ParseExt(&local_60,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: changemodel must have a target model name\n");
  }
  COM_StripExtension(tmp_pc1,local_5c);
  Q_strcat(local_5c,0x40,&g_unk_0024c792);
  tmp_u2 = trap_LoadTag(local_5c);
  *(uint32_t *)(param_1 + 0x498) = tmp_u2;
  tmp_u2 = G_ModelIndex(tmp_pc1);
  *(uint32_t *)(param_1 + 0xa8) = tmp_u2;
  return 1;
}

uint32_t G_ScriptAction_ShaderRemap(uint32_t param_1,uint32_t param_2)
{
  float tmp_f1;
  char *tmp_pc2;
  uint32_t local_210;
  uint8_t local_20c [256];
  uint8_t local_10c [256];
  
  tmp_f1 = (float)g_unk_00abe908;
  local_210 = param_2;
  tmp_pc2 = (char *)COM_ParseExt(&local_210,0);
  if (*tmp_pc2 == '\0') {
    G_Error("G_Scripting: remapshader must have a target shader name\n");
  }
  Q_strncpyz(local_20c,tmp_pc2,0x100);
  tmp_pc2 = (char *)COM_ParseExt(&local_210,0);
  if (*tmp_pc2 == '\0') {
    G_Error("G_Scripting: remapshader must have a new shader name\n");
  }
  Q_strncpyz(local_10c,tmp_pc2,0x100);
  AddRemap(local_20c,local_10c,tmp_f1 * 0.001);
  return 1;
}

uint32_t G_ScriptAction_ShaderRemapFlush(void)
{
  uint32_t tmp_u1;
  
  tmp_u1 = BuildShaderStateConfig();
  nitrox_SetConfigstring(0x220,tmp_u1);
  return 1;
}

uint32_t G_ScriptAction_FollowPath(int param_1,int param_2)
{
  bool tmp_b1;
  bool tmp_b2;
  char tmp_c3;
  char *tmp_pc4;
  long tmp_l5;
  int tmp_i6;
  long tmp_l7;
  int tmp_i8;
  uint tmp_u9;
  double tmp_d10;
  float local_48;
  int local_20 [4];
  
  if (param_2 == 0) {
    tmp_i8 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x10);
  }
  else {
    if ((*(byte *)(param_1 + 0x3c8) & 1) != 0) {
      return 0;
    }
    if (g_unk_00abe908 <= *(int *)(param_1 + 0x3bc)) {
      local_20[0] = param_2;
      tmp_pc4 = (char *)COM_ParseExt(local_20,0);
      if (*tmp_pc4 == '\0') {
        G_Error("G_Scripting: followpath must have a direction\n");
      }
      tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
      tmp_pc4 = (char *)COM_ParseExt(local_20,0);
      if (*tmp_pc4 == '\0') {
        G_Error("G_Scripting: followpath must have an targetname\n");
      }
      tmp_i8 = BG_Find_Spline(tmp_pc4);
      if (tmp_i8 == 0) {
        G_Error("G_Scripting: can\'t find spline with \"targetname\" = \"%s\"\n",tmp_pc4);
      }
      tmp_pc4 = (char *)COM_ParseExt(local_20,0);
      if (*tmp_pc4 == '\0') {
        G_Error("G_Scripting: followpath must have a speed\n");
      }
      tmp_d10 = strtod(tmp_pc4,(char **)0x0);
      tmp_b1 = false;
      tmp_c3 = *tmp_pc4;
      local_48 = 0.0;
      while ((tmp_c3 != '\0' && (tmp_pc4 = (char *)COM_ParseExt(local_20,0), *tmp_pc4 != '\0'))) {
        tmp_i6 = Q_stricmp(tmp_pc4,&g_unk_0023f11d);
        tmp_b2 = true;
        if (tmp_i6 != 0) {
          tmp_b2 = tmp_b1;
        }
        tmp_b1 = tmp_b2;
        tmp_i6 = Q_stricmp(tmp_pc4,"length");
        if (tmp_i6 == 0) {
          tmp_pc4 = (char *)COM_ParseExt(local_20,0);
          if (*tmp_pc4 == '\0') {
            G_Error("G_Scripting: length must have a value\n");
          }
          tmp_l7 = strtol(tmp_pc4,(char **)0x0,10);
          local_48 = (float)tmp_l7;
          tmp_c3 = *tmp_pc4;
        }
        else {
          tmp_c3 = *tmp_pc4;
        }
      }
      *(uint32_t *)(param_1 + 0xc) = 0xd;
      *(uint32_t *)(param_1 + 0x30) = 0xd;
      tmp_i6 = g_unk_00abe908;
      *(float *)(param_1 + 0x3c) = local_48;
      *(int *)(param_1 + 0x10) = tmp_i6;
      *(int *)(param_1 + 0x34) = tmp_i6;
      tmp_u9 = (tmp_i8 + -0x8b3540 >> 2) * 0x478bbced;
      if (tmp_l5 == 0) {
        tmp_u9 = tmp_u9 + 1;
      }
      else {
        tmp_u9 = ~tmp_u9;
      }
      *(uint *)(param_1 + 0x110) = tmp_u9;
      *(uint32_t *)(param_1 + 0x2c) = 0;
      *(uint32_t *)(param_1 + 0x28) = 0;
      *(uint32_t *)(param_1 + 0x24) = 0;
      tmp_i8 = (int)ROUND(((*(float *)(tmp_i8 + 0x1e0) + 0.0 + *(float *)(tmp_i8 + 0x1fc) +
                           *(float *)(tmp_i8 + 0x218) + *(float *)(tmp_i8 + 0x234) +
                           *(float *)(tmp_i8 + 0x250) + *(float *)(tmp_i8 + 0x26c) +
                           *(float *)(tmp_i8 + 0x288) + *(float *)(tmp_i8 + 0x2a4) +
                           *(float *)(tmp_i8 + 0x2c0) + *(float *)(tmp_i8 + 0x2dc) +
                           *(float *)(tmp_i8 + 0x2f8) + *(float *)(tmp_i8 + 0x314) +
                           *(float *)(tmp_i8 + 0x330) + *(float *)(tmp_i8 + 0x34c) +
                           *(float *)(tmp_i8 + 0x368) + *(float *)(tmp_i8 + 900)) / (float)tmp_d10) *
                         1000.0);
      *(int *)(param_1 + 0x14) = tmp_i8;
      *(int *)(param_1 + 0x38) = tmp_i8;
      if (!tmp_b1) {
        if ((tmp_i8 != (tmp_i8 / 0x32) * 0x32) &&
           (tmp_i6 = ((tmp_i8 / 0x32) * 5 + 5) * 10,
           (long double)(tmp_i6 - tmp_i8) / (long double)tmp_i8 < (long double)1)) {
          *(int *)(param_1 + 0x14) = tmp_i6;
          *(int *)(param_1 + 0x38) = tmp_i6;
        }
        *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) | 1;
        return 1;
      }
      goto LAB_000bdbb2;
    }
    tmp_i8 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x10);
  }
  if (tmp_i8 <= g_unk_00abe908) {
    *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) & 0xfffffffe;
    BG_EvaluateTrajectory
              (param_1 + 0x30,*(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x34),param_1 + 0x74,1,
               *(uint32_t *)(param_1 + 0x110));
    *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
    tmp_i8 = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x174) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x178) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x17c) = *(uint32_t *)(param_1 + 0x7c);
    *(uint32_t *)(param_1 + 0x38) = 0;
    *(int *)(param_1 + 0x34) = tmp_i8;
    *(uint32_t *)(param_1 + 0x30) = 0;
    *(uint32_t *)(param_1 + 0x50) = 0;
    *(uint32_t *)(param_1 + 0x4c) = 0;
    *(uint32_t *)(param_1 + 0x48) = 0;
    BG_EvaluateTrajectory
              (param_1 + 0xc,g_unk_00abe908,param_1 + 0x5c,0,*(uint32_t *)(param_1 + 0x110));
    *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
    tmp_i8 = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
    *(uint32_t *)(param_1 + 0x14) = 0;
    *(int *)(param_1 + 0x10) = tmp_i8;
    *(uint32_t *)(param_1 + 0xc) = 0;
    *(uint32_t *)(param_1 + 0x2c) = 0;
    *(uint32_t *)(param_1 + 0x28) = 0;
    *(uint32_t *)(param_1 + 0x24) = 0;
    script_linkentity(param_1);
    return 1;
  }
  tmp_u9 = *(uint *)(param_1 + 0x110);
LAB_000bdbb2:
  BG_EvaluateTrajectory(param_1 + 0xc,g_unk_00abe908,param_1 + 0x168,0,tmp_u9);
  BG_EvaluateTrajectory
            (param_1 + 0x30,g_unk_00abe908,param_1 + 0x174,1,*(uint32_t *)(param_1 + 0x110));
  script_linkentity(param_1);
  return 0;
}

uint32_t G_ScriptAction_AttatchToTrain(int param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t *tmp_pu3;
  long tmp_l4;
  uint32_t local_20 [4];
  
  local_20[0] = param_2;
  tmp_pc1 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: attatchtotrain must have a target\n");
  }
  tmp_u2 = BG_StringHashValue(tmp_pc1);
  tmp_pu3 = (uint32_t *)G_FindByTargetnameFast(0,tmp_pc1,tmp_u2);
  if (tmp_pu3 == (uint32_t *)0x0) {
    G_Error("G_Scripting: can\'t find entity with \"targetname\" = \"%s\"\n",tmp_pc1);
  }
  *(uint32_t *)(param_1 + 0xf0) = *tmp_pu3;
  tmp_pc1 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: attatchtotrain must have a length\n");
  }
  tmp_l4 = strtol(tmp_pc1,(char **)0x0,10);
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x20000;
  *(float *)(param_1 + 0x80) = (float)tmp_l4;
  return 1;
}

uint32_t G_ScriptAction_FreezeAnimation(int param_1)
{
  *(uint32_t *)(param_1 + 0xa0) = 1;
  return 1;
}

uint32_t G_ScriptAction_UnFreezeAnimation(int param_1)
{
  *(uint32_t *)(param_1 + 0xa0) = 0;
  return 1;
}

uint32_t G_ScriptAction_StartAnimation(int param_1,uint32_t param_2)
{
  bool tmp_b1;
  bool tmp_b2;
  bool tmp_b3;
  char tmp_c4;
  char *tmp_pc5;
  long tmp_l6;
  int tmp_i7;
  uint32_t local_34;
  uint32_t local_20 [3];
  uint32_t uStack_14;
  
  uStack_14 = 0xbe26b;
  local_20[0] = param_2;
  tmp_pc5 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc5 == '\0') {
    G_Error("G_Scripting: startanimation must have a start frame\n");
  }
  tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
  *(long *)(param_1 + 0xec) = tmp_l6;
  tmp_pc5 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc5 == '\0') {
    G_Error("G_Scripting: startanimation must have a frame count\n");
  }
  tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
  *(long *)(param_1 + 0xf0) = tmp_l6;
  tmp_pc5 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc5 == '\0') {
    G_Error("G_Scripting: startanimation must have an fps count\n");
  }
  tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
  local_34 = 0;
  tmp_b2 = false;
  *(int *)(param_1 + 0xe8) = (int)ROUND(1000.0 / (float)tmp_l6);
  tmp_c4 = *tmp_pc5;
  tmp_b1 = false;
  while (tmp_c4 != '\0') {
    tmp_pc5 = (char *)COM_ParseExt(local_20,0);
    if (*tmp_pc5 == '\0') break;
    tmp_i7 = Q_stricmp(tmp_pc5,"norandom");
    if (tmp_i7 == 0) {
      tmp_b1 = true;
    }
    tmp_i7 = Q_stricmp(tmp_pc5,"nolerp");
    tmp_b3 = true;
    if (tmp_i7 != 0) {
      tmp_b3 = tmp_b2;
    }
    tmp_b2 = tmp_b3;
    tmp_i7 = Q_stricmp(tmp_pc5,"noloop");
    tmp_c4 = *tmp_pc5;
    if (tmp_i7 == 0) {
      local_34 = 1;
    }
  }
  if (tmp_b1) {
    *(uint32_t *)(param_1 + 0xb0) = 0;
  }
  else {
    tmp_i7 = rand();
    *(int *)(param_1 + 0xb0) = tmp_i7 % *(int *)(param_1 + 0xf0);
  }
  *(uint32_t *)(param_1 + 0xac) = local_34;
  if (tmp_b2) {
    *(int *)(param_1 + 0x11c) = *(int *)(param_1 + 0x11c) + 1;
  }
  return 1;
}

uint32_t G_ScriptAction_SetSpeed(int param_1,uint32_t param_2)
{
  bool tmp_b1;
  bool tmp_b2;
  uint32_t tmp_u3;
  bool tmp_b4;
  char *tmp_pc5;
  long tmp_l6;
  int tmp_i7;
  uint32_t local_2c;
  float local_28 [6];
  
  tmp_i7 = 0;
  BG_EvaluateTrajectory
            (param_1 + 0xc,g_unk_00abe908,param_1 + 0x168,1,*(uint32_t *)(param_1 + 0x110));
  local_2c = param_2;
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x168);
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x16c);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 0x170);
  do {
    tmp_pc5 = (char *)COM_Parse(&local_2c);
    if ((tmp_pc5 == (char *)0x0) || (*tmp_pc5 == '\0')) {
      G_Error("G_Scripting: syntax: setspeed <x> <y> <z> [gravity|lowgravity]\n");
    }
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    local_28[tmp_i7] = (float)tmp_l6;
    tmp_i7 = tmp_i7 + 1;
  } while (tmp_i7 != 3);
  tmp_b1 = false;
  tmp_b4 = false;
  while ((tmp_b2 = tmp_b4, tmp_pc5 = (char *)COM_Parse(&local_2c), tmp_pc5 != (char *)0x0 &&
         (*tmp_pc5 != '\0'))) {
    tmp_i7 = Q_stricmp(tmp_pc5,"gravity");
    if (tmp_i7 == 0) {
      tmp_b1 = true;
      tmp_b4 = tmp_b2;
    }
    else {
      tmp_i7 = Q_stricmp(tmp_pc5,"lowgravity");
      tmp_b4 = true;
      if (tmp_i7 != 0) {
        tmp_b4 = tmp_b2;
      }
    }
  }
  if (tmp_b1) {
    *(uint32_t *)(param_1 + 0xc) = 6;
  }
  else {
    *(uint *)(param_1 + 0xc) = (-(uint)!tmp_b2 & 0xfffffffb) + 7;
  }
  tmp_u3 = g_unk_00abe908;
  *(float *)(param_1 + 0x24) = local_28[0];
  *(float *)(param_1 + 0x28) = local_28[1];
  *(uint32_t *)(param_1 + 0x10) = tmp_u3;
  *(float *)(param_1 + 0x2c) = local_28[2];
  script_linkentity(param_1);
  return 1;
}

uint32_t G_ScriptAction_SetRotation(int param_1,uint32_t param_2)
{
  char *__nptr;
  long tmp_l1;
  int tmp_i2;
  uint32_t local_2c;
  float local_28 [6];
  
  BG_EvaluateTrajectory
            (param_1 + 0x30,g_unk_00abe908,param_1 + 0x174,1,*(uint32_t *)(param_1 + 0x110));
  *(uint32_t *)(param_1 + 0x30) = 2;
  *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x174);
  *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x178);
  *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x17c);
  tmp_i2 = 0;
  *(uint32_t *)(param_1 + 0x34) = g_unk_00abe908;
  local_2c = param_2;
  do {
    __nptr = (char *)COM_Parse(&local_2c);
    if ((__nptr == (char *)0x0) || (*__nptr == '\0')) {
      G_Error("G_Scripting: syntax: setrotation <pitchspeed> <yawspeed> <rollspeed>\n");
    }
    tmp_l1 = strtol(__nptr,(char **)0x0,10);
    local_28[tmp_i2] = (float)tmp_l1;
    tmp_i2 = tmp_i2 + 1;
  } while (tmp_i2 != 3);
  *(float *)(param_1 + 0x48) = local_28[0];
  *(float *)(param_1 + 0x4c) = local_28[1];
  *(float *)(param_1 + 0x50) = local_28[2];
  script_linkentity(param_1);
  return 1;
}

uint32_t G_ScriptAction_StopRotation(int param_1)
{
  uint32_t tmp_u1;
  
  BG_EvaluateTrajectory
            (param_1 + 0x30,g_unk_00abe908,param_1 + 0x174,1,*(uint32_t *)(param_1 + 0x110));
  *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x174);
  *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x178);
  *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x17c);
  tmp_u1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0x38) = 0;
  *(uint32_t *)(param_1 + 0x50) = 0;
  *(uint32_t *)(param_1 + 0x4c) = 0;
  *(uint32_t *)(param_1 + 0x34) = tmp_u1;
  *(uint32_t *)(param_1 + 0x48) = 0;
  *(uint32_t *)(param_1 + 0x30) = 0;
  return 1;
}

uint32_t G_ScriptAction_FollowSpline(int param_1,int param_2)
{
  float tmp_f1;
  bool tmp_b2;
  bool tmp_b3;
  char *tmp_pc4;
  uint tmp_u5;
  int tmp_i6;
  long tmp_l7;
  int tmp_i8;
  double tmp_d9;
  float local_5c;
  float local_50;
  float local_4c;
  uint local_40;
  int local_20 [4];
  
  if (param_2 == 0) {
    tmp_i8 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x10);
  }
  else {
    if ((*(byte *)(param_1 + 0x3c8) & 1) != 0) {
      return 0;
    }
    if (g_unk_00abe908 <= *(int *)(param_1 + 0x3bc)) {
      local_20[0] = param_2;
      tmp_pc4 = (char *)COM_ParseExt(local_20,0);
      if (*tmp_pc4 == '\0') {
        G_Error("G_Scripting: followspline must have a direction\n");
      }
      tmp_i8 = Q_stricmp(tmp_pc4,"accum");
      if (tmp_i8 == 0) {
        tmp_pc4 = (char *)COM_ParseExt(local_20,0);
        if (*tmp_pc4 == '\0') {
          G_Error("G_Scripting: accum without a buffer index\n");
        }
        tmp_u5 = strtol(tmp_pc4,(char **)0x0,10);
        if (9 < tmp_u5) {
          G_Error("G_Scripting: accum buffer is outside range (0 - %i)\n",9);
        }
        local_40 = (uint)(*(int *)(param_1 + 0x3d4 + tmp_u5 * 4) != 0);
      }
      else {
        tmp_i8 = Q_stricmp(tmp_pc4,"globalaccum");
        if (tmp_i8 == 0) {
          tmp_pc4 = (char *)COM_ParseExt(local_20,0);
          if (*tmp_pc4 == '\0') {
            G_Error("G_Scripting: globalaccum without a buffer index\n");
          }
          tmp_u5 = strtol(tmp_pc4,(char **)0x0,10);
          if (9 < tmp_u5) {
            G_Error("G_Scripting: globalaccum buffer is outside range (0 - %i)\n",9);
          }
          local_40 = (uint)(*(int *)(&g_unk_02a983bc + tmp_u5 * 4) != 0);
        }
        else {
          local_40 = strtol(tmp_pc4,(char **)0x0,10);
        }
      }
      tmp_pc4 = (char *)COM_ParseExt(local_20,0);
      if (*tmp_pc4 == '\0') {
        G_Error("G_Scripting: followspline must have an targetname\n");
      }
      tmp_i8 = BG_Find_Spline(tmp_pc4);
      if (tmp_i8 == 0) {
        G_Error("G_Scripting: can\'t find spline with \"targetname\" = \"%s\"\n",tmp_pc4);
      }
      tmp_pc4 = (char *)COM_ParseExt(local_20,0);
      if (*tmp_pc4 == '\0') {
        G_Error("G_Scripting: followspline must have a speed\n");
      }
      tmp_d9 = strtod(tmp_pc4,(char **)0x0);
      tmp_f1 = (float)tmp_d9 * (float)GHIDRA_FIELD(g_moverScale, 8, 4);
      tmp_b2 = false;
      local_4c = 0.0;
      local_5c = 0.0;
      local_50 = 0.0;
      while ((*tmp_pc4 != '\0' && (tmp_pc4 = (char *)COM_ParseExt(local_20,0), *tmp_pc4 != '\0'))) {
        tmp_i6 = Q_stricmp(tmp_pc4,&g_unk_0023f11d);
        tmp_b3 = true;
        if (tmp_i6 != 0) {
          tmp_b3 = tmp_b2;
        }
        tmp_b2 = tmp_b3;
        tmp_i6 = Q_stricmp(tmp_pc4,"length");
        if (tmp_i6 == 0) {
          tmp_pc4 = (char *)COM_ParseExt(local_20,0);
          if (*tmp_pc4 == '\0') {
            G_Error("G_Scripting: length must have a value\n");
          }
          tmp_l7 = strtol(tmp_pc4,(char **)0x0,10);
          local_50 = (float)tmp_l7;
        }
        tmp_i6 = Q_stricmp(tmp_pc4,&g_unk_0024c7c8);
        if (tmp_i6 == 0) {
          tmp_pc4 = (char *)COM_ParseExt(local_20,0);
          if (*tmp_pc4 == '\0') {
            G_Error("G_Scripting: roll must have a start angle\n");
          }
          tmp_l7 = strtol(tmp_pc4,(char **)0x0,10);
          local_5c = (float)tmp_l7;
          tmp_pc4 = (char *)COM_ParseExt(local_20,0);
          if (*tmp_pc4 == '\0') {
            G_Error("G_Scripting: roll must have an end angle\n");
          }
          tmp_l7 = strtol(tmp_pc4,(char **)0x0,10);
          local_4c = (float)tmp_l7;
        }
        tmp_i6 = Q_stricmp(tmp_pc4,"dampin");
        if (tmp_i6 == 0) {
          if (local_5c < 0.0) {
            local_5c = local_5c - 1000.0;
          }
          else {
            local_5c = local_5c + 1000.0;
          }
        }
        tmp_i6 = Q_stricmp(tmp_pc4,"dampout");
        if (tmp_i6 == 0) {
          if (local_5c < 0.0) {
            local_5c = local_5c - 10000.0;
          }
          else {
            local_5c = local_5c + 10000.0;
          }
        }
      }
      *(uint32_t *)(param_1 + 0xc) = 0xc;
      *(uint32_t *)(param_1 + 0x30) = 0xc;
      tmp_i6 = g_unk_00abe908;
      *(float *)(param_1 + 0x3c) = local_50;
      *(int *)(param_1 + 0x10) = tmp_i6;
      *(float *)(param_1 + 0x40) = local_5c;
      *(int *)(param_1 + 0x34) = tmp_i6;
      *(float *)(param_1 + 0x44) = local_4c;
      tmp_u5 = (tmp_i8 + -0x8b3540 >> 2) * 0x478bbced;
      if (local_40 == 0) {
        tmp_u5 = tmp_u5 + 1;
      }
      else {
        tmp_u5 = ~tmp_u5;
      }
      *(uint *)(param_1 + 0x110) = tmp_u5;
      *(uint32_t *)(param_1 + 0x2c) = 0;
      *(uint32_t *)(param_1 + 0x28) = 0;
      *(uint32_t *)(param_1 + 0x24) = 0;
      tmp_i8 = (int)ROUND((*(float *)(tmp_i8 + 0x388) / tmp_f1) * 1000.0);
      *(int *)(param_1 + 0x14) = tmp_i8;
      *(int *)(param_1 + 0x38) = tmp_i8;
      if (!tmp_b2) {
        if ((tmp_i8 != (tmp_i8 / 0x32) * 0x32) &&
           (tmp_i6 = ((tmp_i8 / 0x32) * 5 + 5) * 10,
           (long double)(tmp_i6 - tmp_i8) / (long double)tmp_i8 < (long double)1)) {
          *(int *)(param_1 + 0x14) = tmp_i6;
          *(int *)(param_1 + 0x38) = tmp_i6;
        }
        *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) | 1;
        return 1;
      }
      goto LAB_000be892;
    }
    tmp_i8 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x10);
  }
  if (tmp_i8 <= g_unk_00abe908) {
    *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) & 0xfffffffe;
    BG_EvaluateTrajectory
              (param_1 + 0x30,*(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x34),param_1 + 0x74,1,
               *(uint32_t *)(param_1 + 0x110));
    *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
    tmp_i8 = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x174) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x178) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x17c) = *(uint32_t *)(param_1 + 0x7c);
    *(uint32_t *)(param_1 + 0x38) = 0;
    *(int *)(param_1 + 0x34) = tmp_i8;
    *(uint32_t *)(param_1 + 0x30) = 0;
    *(uint32_t *)(param_1 + 0x50) = 0;
    *(uint32_t *)(param_1 + 0x4c) = 0;
    *(uint32_t *)(param_1 + 0x48) = 0;
    BG_EvaluateTrajectory
              (param_1 + 0xc,g_unk_00abe908,param_1 + 0x5c,0,*(uint32_t *)(param_1 + 0x110));
    *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
    tmp_i8 = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
    *(uint32_t *)(param_1 + 0x14) = 0;
    *(int *)(param_1 + 0x10) = tmp_i8;
    *(uint32_t *)(param_1 + 0xc) = 0;
    *(uint32_t *)(param_1 + 0x2c) = 0;
    *(uint32_t *)(param_1 + 0x28) = 0;
    *(uint32_t *)(param_1 + 0x24) = 0;
    script_linkentity(param_1);
    return 1;
  }
  tmp_u5 = *(uint *)(param_1 + 0x110);
LAB_000be892:
  BG_EvaluateTrajectory(param_1 + 0xc,g_unk_00abe908,param_1 + 0x168,0,tmp_u5);
  BG_EvaluateTrajectory
            (param_1 + 0x30,g_unk_00abe908,param_1 + 0x174,1,*(uint32_t *)(param_1 + 0x110));
  script_linkentity(param_1);
  return 0;
}

uint32_t G_ScriptAction_AbortMove(int param_1)
{
  uint32_t tmp_u1;
  
  *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) & 0xfffffffe;
  BG_EvaluateTrajectory
            (param_1 + 0x30,*(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x34),param_1 + 0x74,1,
             *(uint32_t *)(param_1 + 0x110));
  *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
  *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
  *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
  tmp_u1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0x174) = *(uint32_t *)(param_1 + 0x74);
  *(uint32_t *)(param_1 + 0x178) = *(uint32_t *)(param_1 + 0x78);
  *(uint32_t *)(param_1 + 0x17c) = *(uint32_t *)(param_1 + 0x7c);
  *(uint32_t *)(param_1 + 0x34) = tmp_u1;
  *(uint32_t *)(param_1 + 0x50) = 0;
  *(uint32_t *)(param_1 + 0x4c) = 0;
  *(uint32_t *)(param_1 + 0x48) = 0;
  *(uint32_t *)(param_1 + 0x38) = 0;
  *(uint32_t *)(param_1 + 0x30) = 0;
  BG_EvaluateTrajectory
            (param_1 + 0xc,g_unk_00abe908,param_1 + 0x5c,0,*(uint32_t *)(param_1 + 0x110));
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
  tmp_u1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x10) = tmp_u1;
  *(uint32_t *)(param_1 + 0x2c) = 0;
  *(uint32_t *)(param_1 + 0x28) = 0;
  *(uint32_t *)(param_1 + 0x14) = 0;
  *(uint32_t *)(param_1 + 0x24) = 0;
  *(uint32_t *)(param_1 + 0xc) = 0;
  script_linkentity(param_1);
  return 1;
}

uint32_t G_ScriptAction_SetChargeTimeFactor(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  long tmp_l2;
  int tmp_i3;
  double tmp_d4;
  float local_78;
  uint32_t local_60;
  uint8_t local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0xbf1ab;
  local_60 = param_2;
  tmp_pc1 = (char *)COM_ParseExt(&local_60,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: setchargetimefactor must have a team\n");
  }
  tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)COM_ParseExt(&local_60,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: setchargetimefactor must have a class name\n");
  }
  Q_strncpyz(local_5c,tmp_pc1,0x40);
  tmp_pc1 = (char *)COM_ParseExt(&local_60,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: setchargetimefactor must have a factor\n");
  }
  tmp_d4 = strtod(tmp_pc1,(char **)0x0);
  local_78 = (float)tmp_d4;
  if (local_78 < 0.0) {
    G_Printf("^3WARNING: setchargetimefactor with factor < 0, clamped to 0\n");
    local_78 = 0.0;
  }
  else if (1.0 < local_78) {
    G_Printf("^3WARNING: setchargetimefactor with factor > 1, clamped to 1\n");
    local_78 = 1.0;
  }
  tmp_i3 = Q_stricmp(local_5c,"soldier");
  if (tmp_i3 == 0) {
    (&g_unk_02a98458)[tmp_l2] = local_78;
    (&g_unk_02a983e4)[tmp_l2] = (int)ROUND((float)(int)GHIDRA_FIELD(g_soldierChargeTime, 12, 4) * local_78);
  }
  else {
    tmp_i3 = Q_stricmp(local_5c,"medic");
    if (tmp_i3 == 0) {
      (&g_unk_02a98460)[tmp_l2] = local_78;
      (&g_unk_02a983ec)[tmp_l2] = (int)ROUND((float)(int)GHIDRA_FIELD(g_medicChargeTime, 12, 4) * local_78);
    }
    else {
      tmp_i3 = Q_stricmp(local_5c,"engineer");
      if (tmp_i3 == 0) {
        (&g_unk_02a98468)[tmp_l2] = local_78;
        (&g_unk_02a983f4)[tmp_l2] = (int)ROUND((float)(int)GHIDRA_FIELD(g_engineerChargeTime, 12, 4) * local_78);
      }
      else {
        tmp_i3 = Q_stricmp(local_5c,"fieldops");
        if (tmp_i3 != 0) {
          tmp_i3 = Q_stricmp(local_5c,"lieutenant");
          if (tmp_i3 != 0) {
            tmp_i3 = Q_stricmp(local_5c,"covertops");
            if (tmp_i3 == 0) {
              (&g_unk_02a98478)[tmp_l2] = local_78;
              (&g_unk_02a98404)[tmp_l2] =
                   (int)ROUND((float)(int)GHIDRA_FIELD(g_covertopsChargeTime, 12, 4) * local_78);
            }
            goto LAB_000bf2d5;
          }
        }
        (&g_unk_02a98470)[tmp_l2] = local_78;
        (&g_unk_02a983fc)[tmp_l2] = (int)ROUND((float)(int)GHIDRA_FIELD(g_LTChargeTime, 12, 4) * local_78);
      }
    }
  }
LAB_000bf2d5:
  nitmod_SendChargeTimes(0);
  return 1;
}

uint32_t G_ScriptAction_SpawnRubble(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  uint8_t *tmp_pu2;
  uint8_t *tmp_pu3;
  
  tmp_pu2 = &g_unk_02a9a6d4;
  do {
    while (tmp_i1 = Q_stricmp(tmp_pu2,param_2), tmp_i1 != 0) {
      tmp_pu2 = tmp_pu2 + 0x5c;
      if (tmp_pu2 == &g_unk_02aa02d4) {
        return 1;
      }
    }
    tmp_pu3 = tmp_pu2 + 0x5c;
    tmp_i1 = nitrox_TempEventFromQueue(tmp_pu2 + -0x3c,0x58);
    *(uint32_t *)(tmp_i1 + 0x68) = *(uint32_t *)(tmp_pu2 + -0x2c);
    *(uint32_t *)(tmp_i1 + 0x6c) = *(uint32_t *)(tmp_pu2 + -0x28);
    *(uint32_t *)(tmp_i1 + 0x70) = *(uint32_t *)(tmp_pu2 + -0x24);
    *(uint32_t *)(tmp_i1 + 0xa4) = *(uint32_t *)(tmp_pu2 + -0x30);
    tmp_pu2 = tmp_pu3;
  } while (tmp_pu3 != &g_unk_02aa02d4);
  return 1;
}

uint32_t G_ScriptAction_AllowTankExit(uint32_t param_1,uint32_t param_2)
{
  char *__nptr;
  int tmp_i1;
  long tmp_l2;
  uint32_t local_10 [2];
  
  local_10[0] = param_2;
  __nptr = (char *)COM_ParseExt(local_10,0);
  if (*__nptr == '\0') {
    G_Error("G_Scripting: allowtankexit must have a enable value\n");
  }
  tmp_i1 = Q_stricmp(__nptr,&g_unk_00251ae1);
  if (((tmp_i1 != 0) && (tmp_i1 = Q_stricmp(__nptr,"on"), tmp_i1 != 0)) &&
     (tmp_l2 = strtol(__nptr,(char **)0x0,10), tmp_l2 == 0)) {
    g_unk_02aa29a0 = 1;
    return 1;
  }
  g_unk_02aa29a0 = 0;
  return 1;
}

uint32_t G_ScriptAction_AllowTankEnter(uint32_t param_1,uint32_t param_2)
{
  char *__nptr;
  int tmp_i1;
  long tmp_l2;
  uint32_t local_10 [2];
  
  local_10[0] = param_2;
  __nptr = (char *)COM_ParseExt(local_10,0);
  if (*__nptr == '\0') {
    G_Error("G_Scripting: allowtankenter must have a enable value\n");
  }
  tmp_i1 = Q_stricmp(__nptr,&g_unk_00251ae1);
  if (((tmp_i1 != 0) && (tmp_i1 = Q_stricmp(__nptr,"on"), tmp_i1 != 0)) &&
     (tmp_l2 = strtol(__nptr,(char **)0x0,10), tmp_l2 == 0)) {
    g_unk_02aa29a4 = 1;
    return 1;
  }
  g_unk_02aa29a4 = 0;
  return 1;
}

uint32_t G_ScriptAction_SetTankAmmo(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  long tmp_l4;
  char *tmp_pc5;
  uint32_t local_20 [4];
  
  local_20[0] = param_2;
  tmp_pc1 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: settankammo must have a target\n");
  }
  tmp_u2 = BG_StringHashValue(tmp_pc1);
  tmp_pc5 = tmp_pc1;
  tmp_i3 = G_FindByTargetnameFast(0,tmp_pc1,tmp_u2);
  if (tmp_i3 == 0) {
    G_Error("G_Scripting: settankammo, failed to find target (%s)\n",tmp_pc1);
    tmp_pc5 = tmp_pc1;
  }
  if (*(int *)(tmp_i3 + 4) != 4) {
    G_Error("G_Scripting: settankammo, must target a mover\n",tmp_pc5);
  }
  tmp_pc1 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: settankammo must have an amount\n");
  }
  tmp_l4 = strtol(tmp_pc1,(char **)0x0,10);
  *(long *)(tmp_i3 + 0x10c) = tmp_l4;
  return 1;
}

uint32_t G_ScriptAction_AddTankAmmo(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  int tmp_i4;
  long tmp_l5;
  char *tmp_pc6;
  uint32_t local_20 [4];
  
  local_20[0] = param_2;
  tmp_pc2 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc2 == '\0') {
    G_Error("G_Scripting: addtankammo must have a target\n");
  }
  tmp_u3 = BG_StringHashValue(tmp_pc2);
  tmp_pc6 = tmp_pc2;
  tmp_i4 = G_FindByTargetnameFast(0,tmp_pc2,tmp_u3);
  if (tmp_i4 == 0) {
    G_Error("G_Scripting: addtankammo, failed to find target (%s)\n",tmp_pc2);
    tmp_pc6 = tmp_pc2;
  }
  if (*(int *)(tmp_i4 + 4) != 4) {
    G_Error("G_Scripting: addtankammo, must target a mover\n",tmp_pc6);
  }
  tmp_pc2 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc2 == '\0') {
    G_Error("G_Scripting: addtankammo must have an amount\n");
  }
  tmp_i1 = *(int *)(tmp_i4 + 0x10c);
  tmp_l5 = strtol(tmp_pc2,(char **)0x0,10);
  *(long *)(tmp_i4 + 0x10c) = tmp_l5 + tmp_i1;
  tmp_pc2 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc2 != '\0') {
    tmp_i1 = *(int *)(tmp_i4 + 0x10c);
    tmp_l5 = strtol(tmp_pc2,(char **)0x0,10);
    if (tmp_l5 < tmp_i1) {
      tmp_l5 = strtol(tmp_pc2,(char **)0x0,10);
      *(long *)(tmp_i4 + 0x10c) = tmp_l5;
    }
  }
  return 1;
}

uint32_t G_ScriptAction_DisableMessage(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t local_10;
  
  local_10 = param_2;
  tmp_pc1 = (char *)COM_ParseExt(&local_10,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: disablemessage must have an targetname\n");
  }
  tmp_u2 = BG_StringHashValue(tmp_pc1);
  tmp_i3 = 0;
  while( true ) {
    tmp_i3 = G_FindByTargetnameFast(tmp_i3,tmp_pc1,tmp_u2);
    if (tmp_i3 == 0) break;
    *(uint32_t *)(tmp_i3 + 0x118) = 1;
  }
  return 1;
}

uint32_t G_ScriptAction_Kill(int param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t local_10 [2];
  
  local_10[0] = param_2;
  tmp_pc1 = (char *)COM_ParseExt(local_10,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: kill must have a target\n");
  }
  G_KillEnts(tmp_pc1,0,*(uint32_t *)(param_1 + 0x2ec),*(uint32_t *)(param_1 + 0x2fc));
  return 1;
}

uint32_t G_ScriptAction_SetGlobalFog(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  long tmp_l2;
  long tmp_l3;
  uint32_t tmp_u4;
  double tmp_d5;
  uint32_t local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  local_2c = param_2;
  tmp_pc1 = (char *)COM_ParseExt(&local_2c,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: setglobalfog must have a restore value\n");
  }
  tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)COM_ParseExt(&local_2c,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: setglobalfog must have a duration value\n");
  }
  tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
  if (tmp_l2 == 0) {
    Parse1DMatrix(&local_2c,3,&local_28);
    tmp_pc1 = (char *)COM_ParseExt(&local_2c,0);
    if (*tmp_pc1 == '\0') {
      G_Error("G_Scripting: setglobalfog without restore flag must have a depth for opaque value\n")
      ;
    }
    tmp_d5 = strtod(tmp_pc1,(char **)0x0);
    tmp_u4 = va("0 %i %f %f %f %f",tmp_l3,(double)local_28,(double)local_24,(double)local_20,
               (double)(float)tmp_d5);
    trap_SetConfigstring(0x1e,tmp_u4);
  }
  else {
    tmp_u4 = va("1 %i 0 0 0 0",tmp_l3);
    trap_SetConfigstring(0x1e,tmp_u4);
  }
  return 1;
}

uint32_t G_ScriptAction_GotoMarker(int param_1,int param_2)
{
  float tmp_f1;
  float tmp_f2;
  float tmp_f3;
  float tmp_f4;
  bool tmp_b5;
  bool tmp_b6;
  char tmp_c7;
  char *tmp_pc8;
  uint32_t tmp_u9;
  uint32_t tmp_u10;
  int tmp_i11;
  int tmp_i12;
  long double tmp_l13;
  long double tmp_l14;
  double tmp_d15;
  double tmp_d16;
  double tmp_d17;
  int local_70;
  int local_5c;
  int local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34 [4];
  uint32_t local_24;
  uint32_t local_20;
  
  if (param_2 == 0) {
    tmp_i11 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x10);
  }
  else {
    if ((*(byte *)(param_1 + 0x3c8) & 1) != 0) {
      return 0;
    }
    if (g_unk_00abe908 <= *(int *)(param_1 + 0x3bc)) {
      local_44 = param_2;
      tmp_pc8 = (char *)COM_ParseExt(&local_44,0);
      if (*tmp_pc8 == '\0') {
        G_Error("G_Scripting: gotomarker must have an targetname\n");
      }
      tmp_i11 = BG_Find_PathCorner(tmp_pc8);
      if (tmp_i11 == 0) {
        BG_StringHashValue(tmp_pc8);
        local_5c = G_FindByTargetnameFast(0,tmp_pc8);
        if (local_5c == 0) {
          G_Error("G_Scripting: can\'t find entity with \"targetname\" = \"%s\"\n",tmp_pc8);
        }
        local_40 = *(float *)(local_5c + 0x168) - *(float *)(param_1 + 0x168);
        local_3c = *(float *)(local_5c + 0x16c) - *(float *)(param_1 + 0x16c);
        local_38 = *(float *)(local_5c + 0x170) - *(float *)(param_1 + 0x170);
      }
      else {
        local_40 = *(float *)(tmp_i11 + 0x40) - *(float *)(param_1 + 0x168);
        local_3c = *(float *)(tmp_i11 + 0x44) - *(float *)(param_1 + 0x16c);
        local_5c = 0;
        local_38 = *(float *)(tmp_i11 + 0x48) - *(float *)(param_1 + 0x170);
      }
      tmp_pc8 = (char *)COM_ParseExt(&local_44,0);
      if (*tmp_pc8 == '\0') {
        G_Error("G_Scripting: gotomarker must have a speed\n");
      }
      tmp_d15 = strtod(tmp_pc8,(char **)0x0);
      tmp_f4 = (float)tmp_d15;
      local_70 = 3;
      tmp_b5 = false;
      tmp_b6 = false;
      tmp_c7 = *tmp_pc8;
      while ((tmp_c7 != '\0' && (tmp_pc8 = (char *)COM_ParseExt(&local_44,0), *tmp_pc8 != '\0'))) {
        tmp_i12 = Q_stricmp(tmp_pc8,"accel");
        if (tmp_i12 == 0) {
          tmp_c7 = *tmp_pc8;
          local_70 = 10;
        }
        else {
          tmp_i12 = Q_stricmp(tmp_pc8,"deccel");
          if (tmp_i12 == 0) {
            tmp_c7 = *tmp_pc8;
            local_70 = 0xb;
          }
          else {
            tmp_i12 = Q_stricmp(tmp_pc8,&g_unk_0023f11d);
            if (tmp_i12 == 0) {
              tmp_c7 = *tmp_pc8;
              tmp_b5 = true;
            }
            else {
              tmp_i12 = Q_stricmp(tmp_pc8,"turntotarget");
              if (tmp_i12 == 0) {
                tmp_c7 = *tmp_pc8;
                tmp_b6 = true;
              }
              else {
                tmp_i12 = Q_stricmp(tmp_pc8,"relative");
                if (tmp_i12 == 0) {
                  tmp_pc8 = (char *)COM_ParseExt(&local_44,0);
                  tmp_i12 = BG_Find_PathCorner(tmp_pc8);
                  if (tmp_i12 == 0) {
                    BG_StringHashValue(tmp_pc8);
                    tmp_i12 = G_FindByTargetnameFast(0,tmp_pc8);
                    if (tmp_i12 == 0) {
                      G_Error("Target for relative gotomarker not found: %s\n",tmp_pc8);
                      return 0;
                    }
                    tmp_f1 = *(float *)(tmp_i12 + 0x168);
                    tmp_f2 = *(float *)(tmp_i12 + 0x16c);
                    tmp_f3 = *(float *)(tmp_i12 + 0x170);
                  }
                  else {
                    tmp_f1 = *(float *)(tmp_i12 + 0x40);
                    tmp_f2 = *(float *)(tmp_i12 + 0x44);
                    tmp_f3 = *(float *)(tmp_i12 + 0x48);
                  }
                  local_40 = (local_40 + *(float *)(param_1 + 0x168)) - tmp_f1;
                  local_3c = (local_3c + *(float *)(param_1 + 0x16c)) - tmp_f2;
                  local_38 = (local_38 + *(float *)(param_1 + 0x170)) - tmp_f3;
                  tmp_c7 = *tmp_pc8;
                }
                else {
                  tmp_c7 = *tmp_pc8;
                }
              }
            }
          }
        }
      }
      if (*(int *)(param_1 + 4) == 4) {
        *(float *)(param_1 + 0x270) = local_40;
        *(float *)(param_1 + 0x274) = local_3c;
        *(float *)(param_1 + 0x278) = local_38;
        *(float *)(param_1 + 0x224) = *(float *)(param_1 + 0x168);
        *(float *)(param_1 + 0x228) = *(float *)(param_1 + 0x16c);
        *(float *)(param_1 + 0x22c) = *(float *)(param_1 + 0x170);
        *(float *)(param_1 + 0x230) = local_40 + *(float *)(param_1 + 0x168);
        *(float *)(param_1 + 0x234) = local_3c + *(float *)(param_1 + 0x16c);
        *(float *)(param_1 + 0x238) = *(float *)(param_1 + 0x170) + local_38;
        *(float *)(param_1 + 0x268) = tmp_f4 * (float)GHIDRA_FIELD(g_moverScale, 8, 4);
        tmp_l13 = (long double)VectorDistance(param_1 + 0x224,param_1 + 0x230);
        InitMover(param_1);
        if ((*(int *)(param_1 + 4) == 4) && ((*(byte *)(param_1 + 0x1a8) & 8) != 0)) {
          *(void **)(param_1 + 0x2b4) = script_mover_use;
        }
        SetMoverState(param_1,3,g_unk_00abe908);
        if (local_70 != 3) {
          *(int *)(param_1 + 0x14) = (int)ROUND(((float)tmp_l13 * 1000.0) / (tmp_f4 * 0.5));
          *(int *)(param_1 + 0xc) = local_70;
        }
        *(uint32_t *)(param_1 + 0x2a8) = 0;
        tmp_pc8 = (char *)_GetEntityName(param_1);
        tmp_d15 = (double)*(float *)(param_1 + 0x2c);
        tmp_d17 = (double)*(float *)(param_1 + 0x28);
        tmp_d16 = (double)*(float *)(param_1 + 0x24);
        tmp_u9 = va("%.2f %.2f %.2f",tmp_d16,tmp_d17,tmp_d15);
        if (tmp_pc8 == (char *)0x0) {
          tmp_pc8 = "<unknown>";
        }
        tmp_u10 = va("%s_goto",tmp_pc8,(int)((ulonglong)tmp_d16 >> 0x20),tmp_d17,tmp_d15);
        Bot_Util_SendTrigger(param_1,0,tmp_u10,tmp_u9);
        if ((tmp_b6) && (tmp_i11 == 0)) {
          tmp_i11 = *(int *)(param_1 + 0x14);
          tmp_i12 = 0;
          local_34[3] = (float)*(uint32_t *)(local_5c + 0x74);
          local_24 = *(uint32_t *)(local_5c + 0x78);
          local_20 = *(uint32_t *)(local_5c + 0x7c);
          do {
            tmp_l14 = (long double)
                     AngleDifference(local_34[tmp_i12 + 3],
                                     *(uint32_t *)(param_1 + 0x74 + tmp_i12 * 4));
            local_34[tmp_i12] = (float)tmp_l14;
            if ((long double)180.0 < tmp_l14) {
              do {
                tmp_l14 = tmp_l14 - (long double)360.0;
              } while ((long double)180.0 < tmp_l14);
              local_34[tmp_i12] = (float)tmp_l14;
            }
            if (tmp_l14 < (long double)-180.0) {
              do {
                tmp_l14 = tmp_l14 + (long double)360.0;
              } while (tmp_l14 < (long double)-180.0);
              local_34[tmp_i12] = (float)tmp_l14;
            }
            tmp_i12 = tmp_i12 + 1;
          } while (tmp_i12 != 3);
          *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
          *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
          *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
          if (tmp_i11 == 0) {
            *(uint32_t *)(param_1 + 0x50) = 0;
            *(uint32_t *)(param_1 + 0x4c) = 0;
            *(uint32_t *)(param_1 + 0x48) = 0;
          }
          else {
            tmp_f1 = 1000.0 / (float)tmp_i11;
            *(float *)(param_1 + 0x48) = tmp_f1 * local_34[0];
            *(float *)(param_1 + 0x4c) = tmp_f1 * local_34[1];
            *(float *)(param_1 + 0x50) = tmp_f1 * local_34[2];
          }
          *(int *)(param_1 + 0x38) = tmp_i11;
          tmp_i11 = g_unk_00abe908;
          *(uint32_t *)(param_1 + 0x30) = 3;
          *(int *)(param_1 + 0x34) = tmp_i11;
          if (local_70 != 3) {
            *(int *)(param_1 + 0x14) = (int)ROUND(((float)tmp_l13 * 1000.0) / (tmp_f4 * 0.5));
            *(int *)(param_1 + 0xc) = local_70;
          }
        }
      }
      else {
        *(uint32_t *)(param_1 + 0xc) = 3;
        tmp_i12 = g_unk_00abe908;
        *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x168);
        *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x16c);
        *(int *)(param_1 + 0x10) = tmp_i12;
        *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 0x170);
        tmp_l13 = (long double)VectorNormalize(&local_40);
        tmp_l14 = (long double)tmp_f4;
        *(float *)(param_1 + 0x24) = (float)((long double)local_40 * tmp_l14);
        *(float *)(param_1 + 0x28) = (float)((long double)local_3c * tmp_l14);
        *(float *)(param_1 + 0x2c) = (float)((long double)local_38 * tmp_l14);
        tmp_i12 = (int)ROUND((tmp_l13 / tmp_l14) * (long double)1000.0);
        *(int *)(param_1 + 0x14) = tmp_i12;
        if ((tmp_b6) && (tmp_i11 == 0)) {
          tmp_i11 = 0;
          local_34[3] = (float)*(uint32_t *)(local_5c + 0x74);
          local_24 = *(uint32_t *)(local_5c + 0x78);
          local_20 = *(uint32_t *)(local_5c + 0x7c);
          do {
            tmp_l13 = (long double)
                     AngleDifference(local_34[tmp_i11 + 3],
                                     *(uint32_t *)(param_1 + 0x74 + tmp_i11 * 4));
            local_34[tmp_i11] = (float)tmp_l13;
            if ((long double)180.0 < tmp_l13) {
              do {
                tmp_l13 = tmp_l13 - (long double)360.0;
              } while ((long double)180.0 < tmp_l13);
              local_34[tmp_i11] = (float)tmp_l13;
            }
            if (tmp_l13 < (long double)-180.0) {
              do {
                tmp_l13 = tmp_l13 + (long double)360.0;
              } while (tmp_l13 < (long double)-180.0);
              local_34[tmp_i11] = (float)tmp_l13;
            }
            tmp_i11 = tmp_i11 + 1;
          } while (tmp_i11 != 3);
          *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
          *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
          *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
          if (tmp_i12 == 0) {
            *(uint32_t *)(param_1 + 0x50) = 0;
            *(uint32_t *)(param_1 + 0x4c) = 0;
            *(uint32_t *)(param_1 + 0x48) = 0;
          }
          else {
            tmp_f4 = 1000.0 / (float)tmp_i12;
            *(float *)(param_1 + 0x48) = tmp_f4 * local_34[0];
            *(float *)(param_1 + 0x4c) = tmp_f4 * local_34[1];
            *(float *)(param_1 + 0x50) = tmp_f4 * local_34[2];
          }
          *(int *)(param_1 + 0x38) = tmp_i12;
          tmp_i11 = g_unk_00abe908;
          *(uint32_t *)(param_1 + 0x30) = 3;
          *(int *)(param_1 + 0x34) = tmp_i11;
        }
      }
      if (!tmp_b5) {
        tmp_i11 = *(int *)(param_1 + 0x14);
        if (tmp_i11 != (tmp_i11 / 0x32) * 0x32) {
          tmp_i12 = ((tmp_i11 / 0x32) * 5 + 5) * 10;
          tmp_f4 = (float)(tmp_i12 - tmp_i11) / (float)tmp_i11;
          if (tmp_f4 < 1.0) {
            tmp_f4 = 1.0 / (tmp_f4 + 1.0);
            *(float *)(param_1 + 0x24) = tmp_f4 * *(float *)(param_1 + 0x24);
            *(float *)(param_1 + 0x28) = tmp_f4 * *(float *)(param_1 + 0x28);
            *(float *)(param_1 + 0x2c) = tmp_f4 * *(float *)(param_1 + 0x2c);
            *(int *)(param_1 + 0x14) = tmp_i12;
          }
        }
        *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) | 1;
        return 1;
      }
      goto LAB_000bfcbf;
    }
    tmp_i11 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x10);
  }
  if (tmp_i11 <= g_unk_00abe908) {
    *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) & 0xfffffffe;
    BG_EvaluateTrajectory
              (param_1 + 0x30,*(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x34),param_1 + 0x74,1,
               *(uint32_t *)(param_1 + 0x110));
    *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
    tmp_i11 = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x174) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x178) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x17c) = *(uint32_t *)(param_1 + 0x7c);
    *(uint32_t *)(param_1 + 0x38) = 0;
    *(int *)(param_1 + 0x34) = tmp_i11;
    *(uint32_t *)(param_1 + 0x30) = 0;
    *(uint32_t *)(param_1 + 0x50) = 0;
    *(uint32_t *)(param_1 + 0x4c) = 0;
    *(uint32_t *)(param_1 + 0x48) = 0;
    BG_EvaluateTrajectory
              (param_1 + 0xc,g_unk_00abe908,param_1 + 0x5c,0,*(uint32_t *)(param_1 + 0x110));
    *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
    tmp_i11 = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
    *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
    *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
    *(uint32_t *)(param_1 + 0x14) = 0;
    *(int *)(param_1 + 0x10) = tmp_i11;
    *(uint32_t *)(param_1 + 0xc) = 0;
    *(uint32_t *)(param_1 + 0x2c) = 0;
    *(uint32_t *)(param_1 + 0x28) = 0;
    *(uint32_t *)(param_1 + 0x24) = 0;
    script_linkentity(param_1);
    return 1;
  }
LAB_000bfcbf:
  BG_EvaluateTrajectory
            (param_1 + 0xc,g_unk_00abe908,param_1 + 0x168,0,*(uint32_t *)(param_1 + 0x110));
  BG_EvaluateTrajectory
            (param_1 + 0x30,g_unk_00abe908,param_1 + 0x174,1,*(uint32_t *)(param_1 + 0x110));
  script_linkentity(param_1);
  return 0;
}

bool G_ScriptAction_Wait(int param_1,uint32_t param_2)
{
  char *tmp_pc1;
  int tmp_i2;
  long tmp_l3;
  long tmp_l4;
  bool tmp_b5;
  uint32_t local_20 [4];
  
  local_20[0] = param_2;
  tmp_pc1 = (char *)COM_ParseExt(local_20,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: wait must have a duration\n");
  }
  tmp_i2 = Q_stricmp(tmp_pc1,"random");
  if (tmp_i2 == 0) {
    tmp_pc1 = (char *)COM_ParseExt(local_20,0);
    if (*tmp_pc1 == '\0') {
      G_Error("G_Scripting: wait random must have a min duration\n");
    }
    tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
    tmp_pc1 = (char *)COM_ParseExt(local_20,0);
    if (*tmp_pc1 == '\0') {
      G_Error("G_Scripting: wait random must have a max duration\n");
    }
    tmp_l4 = strtol(tmp_pc1,(char **)0x0,10);
    tmp_b5 = false;
    if ((*(int *)(param_1 + 0x3bc) + tmp_l3 <= g_unk_00abe908) &&
       (tmp_b5 = true, g_unk_00abe908 <= *(int *)(param_1 + 0x3bc) + tmp_l4)) {
      tmp_i2 = rand();
      tmp_b5 = tmp_i2 % (int)ROUND((float)(tmp_l4 - tmp_l3) * 0.02) == 0;
    }
  }
  else {
    tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
    tmp_b5 = tmp_l3 + *(int *)(param_1 + 0x3bc) < g_unk_00abe908;
  }
  return tmp_b5;
}

bool G_ScriptAction_Trigger(uint8_t *param_1,uint32_t param_2)
{
  int tmp_i1;
  bool tmp_b2;
  bool tmp_b3;
  uint32_t tmp_u4;
  int tmp_i5;
  int tmp_i6;
  uint8_t *tmp_pu7;
  uint32_t local_a0;
  char local_9c [64];
  char local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0xc0990;
  local_a0 = param_2;
  tmp_u4 = COM_ParseExt(&local_a0,0);
  Q_strncpyz(local_9c,tmp_u4,0x40);
  if (local_9c[0] == '\0') {
    G_Error("G_Scripting: trigger must have a name and an identifier: %s\n",param_2);
  }
  tmp_u4 = COM_ParseExt(&local_a0,0);
  Q_strncpyz(local_5c,tmp_u4,0x40);
  if (local_5c[0] == '\0') {
    G_Error("G_Scripting: trigger must have a name and an identifier: %s\n",param_2);
  }
  tmp_i5 = Q_stricmp(local_9c,&g_unk_00251b47);
  if (tmp_i5 == 0) {
    tmp_i5 = *(int *)(param_1 + 0x3c4);
    G_Script_ScriptEvent(param_1,"trigger",local_5c);
    return tmp_i5 == *(int *)(param_1 + 0x3c4);
  }
  tmp_i5 = Q_stricmp(local_9c,"global");
  if (tmp_i5 == 0) {
    if (0 < g_unk_00abe8a8) {
      tmp_pu7 = g_entities;
      tmp_b3 = false;
      tmp_b2 = false;
      tmp_i6 = 0;
      tmp_i5 = g_unk_00abe8a8;
      do {
        if ((((*(int *)(tmp_pu7 + 0x194) != 0) && (*(char **)(tmp_pu7 + 0x3ac) != (char *)0x0)) &&
            (**(char **)(tmp_pu7 + 0x3ac) != '\0')) && (tmp_b3 = true, (tmp_pu7[0x128] & 8) == 0)) {
          tmp_i1 = *(int *)(tmp_pu7 + 0x3c4);
          G_Script_ScriptEvent(tmp_pu7,"trigger",local_5c);
          tmp_i5 = g_unk_00abe8a8;
          if ((tmp_pu7 == param_1) && (*(int *)(tmp_pu7 + 0x3c4) != tmp_i1)) {
            tmp_b2 = true;
          }
        }
        tmp_i6 = tmp_i6 + 1;
        tmp_pu7 = tmp_pu7 + 0x600;
      } while (tmp_i6 < tmp_i5);
      if (tmp_b2) {
        return false;
      }
      if (tmp_b3) {
        return true;
      }
    }
LAB_000c0b1f:
    G_Printf("G_Scripting: trigger has unknown name: %s\n",local_9c);
    return true;
  }
  tmp_i5 = Q_stricmp(local_9c,"player");
  if (tmp_i5 == 0) {
    tmp_pu7 = g_entities;
    tmp_i5 = 0;
    do {
      if (*(int *)(level + 0x5ac + tmp_i5) == 2) {
        G_Script_ScriptEvent(tmp_pu7,"trigger",local_5c);
      }
      tmp_i5 = tmp_i5 + 0x54dc;
      tmp_pu7 = tmp_pu7 + 0x600;
    } while (tmp_i5 != 0x153700);
  }
  else {
    tmp_i5 = Q_stricmp(local_9c,"activator");
    if (tmp_i5 != 0) {
      tmp_b2 = false;
      tmp_u4 = BG_StringHashValue(local_9c);
      tmp_b3 = false;
      tmp_pu7 = (uint8_t *)0x0;
      while (tmp_pu7 = (uint8_t *)nitrox_FindByScriptNameHash(tmp_pu7,tmp_u4),
            tmp_pu7 != (uint8_t *)0x0) {
        tmp_b2 = tmp_b3;
        if ((tmp_pu7[0x128] & 8) == 0) {
          tmp_i5 = *(int *)(tmp_pu7 + 0x3c4);
          G_Script_ScriptEvent(tmp_pu7,"trigger",local_5c);
          if ((tmp_pu7 == param_1) && (tmp_b2 = true, *(int *)(tmp_pu7 + 0x3c4) == tmp_i5)) {
            tmp_b2 = tmp_b3;
          }
        }
        tmp_b3 = tmp_b2;
        tmp_b2 = true;
      }
      if (tmp_b3) {
        return false;
      }
      if (!tmp_b2) goto LAB_000c0b1f;
    }
  }
  return true;
}

uint32_t G_ScriptAction_PlaySound(int param_1,int param_2)
{
  bool tmp_b1;
  uint32_t tmp_u2;
  char *tmp_pc3;
  int tmp_i4;
  long tmp_l5;
  int local_74;
  int local_60;
  uint8_t local_5c [76];
  
  if (param_2 == 0) {
    G_Error("G_Scripting: syntax error\n\nplaysound <soundname OR scriptname>\n");
  }
  local_60 = param_2;
  tmp_u2 = COM_ParseExt(&local_60,0);
  Q_strncpyz(local_5c,tmp_u2,0x40);
  tmp_pc3 = (char *)COM_ParseExt(&local_60,0);
  if (*tmp_pc3 != '\0') {
    tmp_b1 = false;
    local_74 = 0xff;
    do {
      tmp_i4 = Q_stricmp(tmp_pc3,"looping");
      if (tmp_i4 == 0) {
        tmp_b1 = true;
      }
      else {
        tmp_i4 = Q_stricmp(tmp_pc3,"volume");
        if (tmp_i4 == 0) {
          tmp_pc3 = (char *)COM_ParseExt(&local_60,0);
          tmp_l5 = strtol(tmp_pc3,(char **)0x0,10);
          local_74 = 0xff;
          if (tmp_l5 != 0) {
            local_74 = tmp_l5;
          }
        }
      }
      tmp_pc3 = (char *)COM_ParseExt(&local_60,0);
    } while (*tmp_pc3 != '\0');
    if (tmp_b1) {
      tmp_u2 = G_SoundIndex(local_5c);
      *(uint32_t *)(param_1 + 0xa0) = tmp_u2;
      *(int *)(param_1 + 0xfc) = local_74 >> 1;
      return 1;
    }
    if (local_74 != 0xff) {
      tmp_u2 = G_SoundIndex(local_5c);
      G_AddEvent(param_1,0x29,tmp_u2);
      *(int *)(param_1 + 0xfc) = local_74 >> 1;
      return 1;
    }
  }
  tmp_u2 = G_SoundIndex(local_5c);
  G_AddEvent(param_1,0x28,tmp_u2);
  return 1;
}

uint32_t G_ScriptAction_FadeAllSounds(uint32_t param_1,int param_2)
{
  uint64_t tmp_u1;
  uint32_t tmp_u2;
  int tmp_i3;
  char *tmp_pc4;
  long tmp_l5;
  int local_20 [4];
  
  if (param_2 == 0) {
    G_Error("G_Scripting: usage: FadeAllSounds [up|down] time\n");
  }
  local_20[0] = param_2;
  tmp_u2 = COM_ParseExt(local_20,0);
  tmp_i3 = Q_stricmp(tmp_u2,"up");
  if (tmp_i3 == 0) {
    tmp_pc4 = (char *)COM_ParseExt(local_20,0);
    tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
    if (tmp_l5 == 0) {
      G_Error("G_Scripting: FadeAllSounds found \'%s\' when expecting \'time\'\n",tmp_pc4);
    }
    tmp_u2 = 0;
    tmp_u1 = 0x3ff0000000000000;
  }
  else {
    tmp_i3 = Q_stricmp(tmp_u2,"down");
    if (tmp_i3 != 0) {
      G_Error("G_Scripting: FadeAllSounds found \'%s\' when expecting [up|down]\n",tmp_u2);
    }
    tmp_pc4 = (char *)COM_ParseExt(local_20,0);
    tmp_l5 = strtol(tmp_pc4,(char **)0x0,10);
    if (tmp_l5 == 0) {
      G_Error("G_Scripting: FadeAllSounds found \'%s\' when expecting \'time\'\n",tmp_pc4);
    }
    tmp_u2 = 1;
    tmp_u1 = 0;
  }
  tmp_u2 = va("snd_fade %f %d %i",tmp_u1,tmp_l5,tmp_u2);
  trap_SendServerCommand(0xffffffff,tmp_u2);
  return 1;
}

uint32_t G_ScriptAction_MusicStart(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  long tmp_l3;
  uint32_t local_50;
  uint8_t local_4c [64];
  
  local_50 = param_2;
  tmp_pc1 = (char *)COM_ParseExt(&local_50,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: syntax: mu_start <musicfile> <fadeuptime>");
  }
  Q_strncpyz(local_4c,tmp_pc1,0x40);
  tmp_pc1 = (char *)COM_ParseExt(&local_50,0);
  tmp_l3 = 0;
  if (*tmp_pc1 != '\0') {
    tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
  }
  tmp_u2 = va("mu_start %s %d",local_4c,tmp_l3);
  trap_SendServerCommand(0xffffffff,tmp_u2);
  return 1;
}

uint32_t G_ScriptAction_MusicPlay(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t local_50;
  uint8_t local_4c [68];
  
  local_50 = param_2;
  tmp_pc1 = (char *)COM_ParseExt(&local_50,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: syntax: mu_play <musicfile> [fadeup time]");
  }
  Q_strncpyz(local_4c,tmp_pc1,0x40);
  tmp_u2 = va("mu_play %s %d",local_4c,0);
  trap_SendServerCommand(0xffffffff,tmp_u2);
  return 1;
}

uint32_t G_ScriptAction_MusicStop(uint32_t param_1,uint32_t param_2)
{
  char *__nptr;
  uint32_t tmp_u1;
  long tmp_l2;
  uint32_t local_10 [3];
  
  local_10[0] = param_2;
  __nptr = (char *)COM_ParseExt(local_10,0);
  tmp_l2 = 0;
  if (*__nptr != '\0') {
    tmp_l2 = strtol(__nptr,(char **)0x0,10);
  }
  tmp_u1 = va("mu_stop %i\n",tmp_l2);
  trap_SendServerCommand(0xffffffff,tmp_u1);
  return 1;
}

uint32_t G_ScriptAction_MusicQueue(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t local_50;
  uint8_t local_4c [68];
  
  local_50 = param_2;
  tmp_pc1 = (char *)COM_ParseExt(&local_50,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: syntax: mu_queue <musicfile>");
  }
  Q_strncpyz(local_4c,tmp_pc1,0x40);
  trap_SetConfigstring(0x19,local_4c);
  return 1;
}

uint32_t G_ScriptAction_MusicFade(uint32_t param_1,uint32_t param_2)
{
  float tmp_f1;
  char *tmp_pc2;
  long tmp_l3;
  uint32_t tmp_u4;
  double tmp_d5;
  uint32_t local_10;
  uint32_t uStack_c;
  
  uStack_c = 0xc1369;
  local_10 = param_2;
  tmp_pc2 = (char *)COM_ParseExt(&local_10,0);
  if (*tmp_pc2 == '\0') {
    G_Error("G_Scripting: syntax: mu_fade <target volume 0.0-1.0> <fadeout time>");
  }
  tmp_d5 = strtod(tmp_pc2,(char **)0x0);
  tmp_f1 = (float)tmp_d5;
  if ((tmp_f1 < 0.0) || (1.0 <= tmp_f1)) {
    G_Error("G_Scripting: syntax: mu_fade <target volume 0.0-1.0> <fadeout time>");
  }
  tmp_pc2 = (char *)COM_ParseExt(&local_10,0);
  if (9 < (byte)(*tmp_pc2 - 0x30U)) {
    G_Error("G_Scripting: syntax: mu_fade <target volume 0.0-1.0> <fadeout time>");
  }
  tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
  tmp_u4 = va("mu_fade %f %i\n",(double)tmp_f1,tmp_l3);
  trap_SendServerCommand(0xffffffff,tmp_u4);
  return 1;
}

bool G_ScriptAction_PlayAnim(int param_1,uint32_t param_2)
{
  float tmp_f1;
  bool tmp_b2;
  char *tmp_pc3;
  long tmp_l4;
  long tmp_l5;
  char *tmp_pc6;
  int tmp_i7;
  long tmp_l8;
  int tmp_i9;
  char *tmp_pc10;
  double tmp_d11;
  int local_c0;
  int local_bc;
  uint32_t local_a0;
  char local_9c [64];
  char local_5c [64];
  char local_1c [12];
  
  if (((*(uint *)(param_1 + 0x3c8) & 2) != 0) && (*(int *)(param_1 + 0x3bc) == g_unk_00abe908)) {
    *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) & 0xfffffffd;
  }
  local_a0 = param_2;
  tmp_pc6 = local_9c;
  do {
    tmp_pc3 = (char *)COM_ParseExt(&local_a0);
    if ((tmp_pc3 == (char *)0x0) || (*tmp_pc3 == '\0')) goto LAB_000c167d;
    tmp_pc10 = tmp_pc6 + 0x40;
    Q_strncpyz(tmp_pc6,tmp_pc3,0x40);
    tmp_pc6 = tmp_pc10;
  } while (tmp_pc10 != local_1c);
  tmp_l4 = strtol(local_9c,(char **)0x0,10);
  tmp_l5 = strtol(local_5c,(char **)0x0,10);
  tmp_pc6 = (char *)COM_ParseExt(&local_a0);
  if (*tmp_pc6 == '\0') {
    tmp_f1 = 50.0;
    local_bc = 0;
    tmp_i7 = *(int *)(param_1 + 0x3bc);
  }
  else {
    tmp_i7 = Q_stricmp(tmp_pc6);
    if (tmp_i7 == 0) {
      tmp_pc6 = (char *)COM_ParseExt(&local_a0);
      if ((tmp_pc6 == (char *)0x0) || (*tmp_pc6 == '\0')) {
LAB_000c167d:
        G_Printf(
                "G_Scripting: syntax error\n\nplayanim <startframe> <endframe> [LOOPING <duration>]\n"
                );
        return true;
      }
      tmp_i7 = Q_stricmp(tmp_pc6);
      if (tmp_i7 == 0) {
        if (g_unk_00abe908 < *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x10)) {
          local_bc = g_unk_00abe908 + 100;
          tmp_b2 = false;
        }
        else {
          tmp_b2 = false;
          local_bc = 0;
        }
      }
      else {
        tmp_i7 = Q_stricmp(tmp_pc6);
        if (tmp_i7 == 0) {
          *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) | 2;
          *(uint32_t *)(param_1 + 0x3d0) = param_2;
          local_bc = g_unk_00abe908 + 100;
          tmp_b2 = true;
        }
        else {
          local_bc = *(int *)(param_1 + 0x3bc);
          tmp_l8 = strtol(tmp_pc6,(char **)0x0,10);
          tmp_b2 = false;
          local_bc = tmp_l8 + local_bc;
        }
      }
      tmp_pc6 = (char *)COM_ParseExt(&local_a0);
      if ((*tmp_pc6 == '\0') || (tmp_i7 = Q_stricmp(tmp_pc6), tmp_i7 != 0)) {
        tmp_f1 = 50.0;
        tmp_i7 = *(int *)(param_1 + 0x3bc);
      }
      else {
        tmp_pc6 = (char *)COM_ParseExt(&local_a0);
        if (*tmp_pc6 == '\0') {
          G_Error("G_Scripting: playanim has RATE parameter without an actual rate specified");
          local_c0 = strtol(tmp_pc6,(char **)0x0,10);
        }
        else {
          local_c0 = strtol(tmp_pc6,(char **)0x0,10);
        }
        tmp_i7 = *(int *)(param_1 + 0x3bc);
        tmp_f1 = 1000.0 / (float)local_c0;
      }
      tmp_i9 = g_unk_00abe908;
      tmp_d11 = floor((double)((float)(g_unk_00abe908 - tmp_i7) / tmp_f1));
      *(int *)(param_1 + 0xb0) = (int)ROUND(tmp_d11) % (tmp_l5 - tmp_l4) + tmp_l4;
      if (tmp_b2) {
        return true;
      }
      goto LAB_000c15e5;
    }
    if ((*tmp_pc6 == '\0') || (tmp_i7 = Q_stricmp(tmp_pc6), tmp_i7 != 0)) {
      tmp_f1 = 50.0;
    }
    else {
      tmp_pc6 = (char *)COM_ParseExt(&local_a0);
      if (*tmp_pc6 == '\0') {
        G_Error("G_Scripting: playanim has RATE parameter without an actual rate specified");
        local_c0 = strtol(tmp_pc6,(char **)0x0,10);
      }
      else {
        local_c0 = strtol(tmp_pc6,(char **)0x0,10);
      }
      tmp_f1 = 1000.0 / (float)local_c0;
    }
    tmp_i7 = *(int *)(param_1 + 0x3bc);
    local_bc = tmp_i7 + (tmp_l5 - tmp_l4) * 0x32;
  }
  tmp_i9 = g_unk_00abe908;
  tmp_d11 = floor((double)((float)(g_unk_00abe908 - tmp_i7) / tmp_f1));
  tmp_i7 = tmp_l4 + (int)ROUND(tmp_d11);
  if (tmp_l5 < tmp_l4 + (int)ROUND(tmp_d11)) {
    tmp_i7 = tmp_l5;
  }
  *(int *)(param_1 + 0xb0) = tmp_i7;
LAB_000c15e5:
  return local_bc <= tmp_i9;
}

uint32_t G_ScriptAction_AlertEntity(uint32_t param_1,char *param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  void *tmp_pc3;
  
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    G_Error("G_Scripting: alertentity without targetname\n");
  }
  tmp_u1 = BG_StringHashValue(param_2);
  tmp_i2 = G_FindByTargetnameFast(0,param_2,tmp_u1);
  if (tmp_i2 == 0) {
    G_Error("G_Scripting: alertentity cannot find targetname \"%s\"\n",param_2);
  }
  do {
    if (*(int *)(tmp_i2 + 400) == 0) {
      if (*(int *)(tmp_i2 + 0x2b4) == 0) {
        G_Error("G_Scripting: alertentity \"%s\" (classname = %s) doesn\'t have a \"use\" function\n"
                ,param_2,*(uint32_t *)(tmp_i2 + 0x1a4));
      }
      G_UseEntity(tmp_i2,0,0);
    }
    else {
      tmp_pc3 = *(void **)(tmp_i2 + 0x344);
      if (tmp_pc3 == (void *)0x0) {
        G_Error("G_Scripting: alertentity \"%s\" (classname = %s) doesn\'t have an \"AIScript_AlertEntity\" function\n"
                ,param_2,*(uint32_t *)(tmp_i2 + 0x1a4));
        tmp_pc3 = *(void **)(tmp_i2 + 0x344);
      }
      (*tmp_pc3)(tmp_i2);
    }
    tmp_i2 = G_FindByTargetnameFast(tmp_i2,param_2,tmp_u1);
  } while (tmp_i2 != 0);
  return 1;
}

uint32_t G_ScriptAction_ToggleSpeaker(uint32_t param_1,char *param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    G_Error("G_Scripting: togglespeaker without targetname\n");
  }
  tmp_i4 = 0;
  tmp_i1 = BG_StringHashValue(param_2);
  tmp_i2 = BG_NumScriptSpeakers();
  if (0 < tmp_i2) {
    do {
      tmp_i2 = BG_GetScriptSpeaker(tmp_i4);
      if (*(int *)(tmp_i2 + 0x70) == tmp_i1) {
LAB_000c1af6:
        tmp_i2 = nitrox_TempEventFromQueue(tmp_i2 + 0x44,0x59);
        *(uint32_t *)(tmp_i2 + 0x128) = 0x20;
        *(int *)(tmp_i2 + 0x8c) = tmp_i4;
        *(uint32_t *)(tmp_i2 + 0x90) = 0;
      }
      else {
        tmp_i3 = Q_stricmp(param_2,tmp_i2 + 0x50);
        if (tmp_i3 == 0) goto LAB_000c1af6;
      }
      tmp_i2 = BG_NumScriptSpeakers();
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_i4 < tmp_i2);
  }
  return 1;
}

uint32_t G_ScriptAction_DisableSpeaker(uint32_t param_1,char *param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    G_Error("G_Scripting: disablespeaker without targetname\n");
  }
  tmp_i4 = 0;
  tmp_i1 = BG_StringHashValue(param_2);
  tmp_i2 = BG_NumScriptSpeakers();
  if (0 < tmp_i2) {
    do {
      tmp_i2 = BG_GetScriptSpeaker(tmp_i4);
      if (*(int *)(tmp_i2 + 0x70) == tmp_i1) {
LAB_000c1bc6:
        tmp_i2 = nitrox_TempEventFromQueue(tmp_i2 + 0x44,0x59);
        *(uint32_t *)(tmp_i2 + 0x128) = 0x20;
        *(int *)(tmp_i2 + 0x8c) = tmp_i4;
        *(uint32_t *)(tmp_i2 + 0x90) = 1;
      }
      else {
        tmp_i3 = Q_stricmp(param_2,tmp_i2 + 0x50);
        if (tmp_i3 == 0) goto LAB_000c1bc6;
      }
      tmp_i2 = BG_NumScriptSpeakers();
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_i4 < tmp_i2);
  }
  return 1;
}

uint32_t G_ScriptAction_EnableSpeaker(uint32_t param_1,char *param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    G_Error("G_Scripting: enablespeaker without targetname\n");
  }
  tmp_i4 = 0;
  tmp_i1 = BG_StringHashValue(param_2);
  tmp_i2 = BG_NumScriptSpeakers();
  if (0 < tmp_i2) {
    do {
      tmp_i2 = BG_GetScriptSpeaker(tmp_i4);
      if (*(int *)(tmp_i2 + 0x70) == tmp_i1) {
LAB_000c1c96:
        tmp_i2 = nitrox_TempEventFromQueue(tmp_i2 + 0x44,0x59);
        *(uint32_t *)(tmp_i2 + 0x128) = 0x20;
        *(int *)(tmp_i2 + 0x8c) = tmp_i4;
        *(uint32_t *)(tmp_i2 + 0x90) = 2;
      }
      else {
        tmp_i3 = Q_stricmp(param_2,tmp_i2 + 0x50);
        if (tmp_i3 == 0) goto LAB_000c1c96;
      }
      tmp_i2 = BG_NumScriptSpeakers();
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_i4 < tmp_i2);
  }
  return 1;
}

bool G_ScriptAction_Accum(int param_1,uint32_t param_2)
{
  uint tmp_u1;
  byte tmp_b2;
  bool tmp_b3;
  bool tmp_b4;
  char *tmp_pc5;
  long tmp_l6;
  uint32_t tmp_u7;
  int tmp_i8;
  uint8_t *tmp_pu9;
  long tmp_l10;
  int tmp_i11;
  int tmp_i12;
  uint32_t local_a0;
  char local_9c [64];
  char local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0xc1d0b;
  local_a0 = param_2;
  tmp_pc5 = (char *)COM_ParseExt(&local_a0,0);
  if (*tmp_pc5 == '\0') {
    G_Error("G_Scripting: accum without a buffer index\n");
  }
  tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
  if (9 < tmp_l6) {
    G_Error("G_Scripting: accum buffer is outside range (0 - %i)\n",9);
  }
  tmp_pc5 = (char *)COM_ParseExt(&local_a0,0);
  if (*tmp_pc5 == '\0') {
    G_Error("G_Scripting: accum without a command\n");
  }
  Q_strncpyz(local_9c,tmp_pc5,0x40);
  tmp_pc5 = (char *)COM_ParseExt(&local_a0,0);
  tmp_u7 = nitrox_GetTokenForString(local_9c);
  switch(tmp_u7) {
  case 0x9a:
    param_1 = param_1 + tmp_l6 * 4;
    tmp_i12 = *(int *)(param_1 + 0x3d4);
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    *(long *)(param_1 + 0x3d4) = tmp_l6 + tmp_i12;
    return true;
  case 0x9b:
    tmp_i12 = *(int *)(param_1 + 0x3d4 + tmp_l6 * 4);
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    if (tmp_l6 <= tmp_i12) {
      return true;
    }
    break;
  case 0x9c:
    tmp_i12 = *(int *)(param_1 + 0x3d4 + tmp_l6 * 4);
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    if (tmp_i12 <= tmp_l6) {
      return true;
    }
    break;
  case 0x9d:
    tmp_i12 = *(int *)(param_1 + 0x3d4 + tmp_l6 * 4);
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    if (tmp_i12 == tmp_l6) {
      return true;
    }
    break;
  case 0x9e:
    tmp_i12 = *(int *)(param_1 + 0x3d4 + tmp_l6 * 4);
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    if (tmp_i12 != tmp_l6) {
      return true;
    }
    break;
  case 0x9f:
    tmp_l10 = strtol(tmp_pc5,(char **)0x0,10);
    *(long *)(param_1 + 0x3d4 + tmp_l6 * 4) = tmp_l10;
    return true;
  case 0xa0:
    tmp_i12 = rand();
    tmp_l10 = strtol(tmp_pc5,(char **)0x0,10);
    *(int *)(param_1 + 0x3d4 + tmp_l6 * 4) = tmp_i12 % tmp_l10;
    return true;
  case 0xa1:
    param_1 = param_1 + tmp_l6 * 4;
    tmp_u1 = *(uint *)(param_1 + 0x3d4);
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    *(uint *)(param_1 + 0x3d4) = tmp_u1 | 1 << ((byte)tmp_l6 & 0x1f);
    return true;
  case 0xa2:
    param_1 = param_1 + tmp_l6 * 4;
    tmp_u1 = *(uint *)(param_1 + 0x3d4);
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    tmp_b2 = (byte)tmp_l6 & 0x1f;
    *(uint *)(param_1 + 0x3d4) = tmp_u1 & (-2 << tmp_b2 | 0xfffffffeU >> 0x20 - tmp_b2);
    return true;
  case 0xa3:
    tmp_i12 = *(int *)(param_1 + 0x3d4 + tmp_l6 * 4);
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    if ((tmp_i12 >> ((byte)tmp_l6 & 0x1f) & 1U) == 0) {
      return true;
    }
    break;
  case 0xa4:
    tmp_i12 = *(int *)(param_1 + 0x3d4 + tmp_l6 * 4);
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    if ((tmp_i12 >> ((byte)tmp_l6 & 0x1f) & 1U) != 0) {
      return true;
    }
    break;
  case 0xa5:
    tmp_i12 = *(int *)(param_1 + 0x3d4 + tmp_l6 * 4);
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    if (tmp_i12 != tmp_l6) {
      return true;
    }
    tmp_u7 = COM_ParseExt(&local_a0,0);
    Q_strncpyz(local_9c,tmp_u7,0x40);
    if (local_9c[0] == '\0') {
      G_Error("G_Scripting: trigger must have a name and an identifier: %s\n",param_2);
    }
    tmp_u7 = COM_ParseExt(&local_a0,0);
    Q_strncpyz(local_5c,tmp_u7,0x40);
    if (local_5c[0] == '\0') {
      G_Error("G_Scripting: trigger must have a name and an identifier: %s\n",param_2);
    }
    tmp_b3 = false;
    tmp_u7 = BG_StringHashValue(local_9c);
    tmp_b4 = false;
    tmp_i12 = 0;
    while (tmp_i12 = nitrox_FindByScriptNameHash(tmp_i12,tmp_u7), tmp_i12 != 0) {
      tmp_i8 = *(int *)(tmp_i12 + 0x3c4);
      G_Script_ScriptEvent(tmp_i12,"trigger",local_5c);
      tmp_b3 = tmp_b4;
      if ((tmp_i12 == param_1) && (tmp_b3 = true, *(int *)(tmp_i12 + 0x3c4) == tmp_i8)) {
        tmp_b3 = tmp_b4;
      }
      tmp_b4 = tmp_b3;
      tmp_b3 = true;
    }
    if (tmp_b4) {
      return false;
    }
    if (!tmp_b3) {
      G_Printf("G_Scripting: trigger has unknown name: %s\n",local_5c);
      return true;
    }
    return true;
  case 0xa6:
    tmp_i12 = *(int *)(param_1 + 0x3d4 + tmp_l6 * 4);
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    return tmp_i12 != tmp_l6;
  case 0xa7:
    if (*tmp_pc5 == '\0') {
      G_Error("Scripting: accum %s requires a parameter\n",local_9c);
    }
    tmp_u7 = BG_StringHashValue(tmp_pc5);
    tmp_i8 = G_FindByTargetnameFast(0,tmp_pc5,tmp_u7);
    if (tmp_i8 == 0) {
      G_Error("Scripting: accum %s could not find target\n",local_9c);
    }
    if (g_unk_00abe8a8 < 0x41) {
      tmp_i12 = 0;
    }
    else {
      tmp_pu9 = g_entities;
      tmp_i12 = 0;
      tmp_i11 = 0x40;
      do {
        if ((*(byte *)((int)&__DT_REL[0x7f8].r_info + (int)tmp_pu9) & 1) != 0) {
          tmp_i12 = tmp_i12 + (uint)(*(int *)((int)&__DT_REL[0x7f9].r_offset + (int)tmp_pu9) ==
                                  (tmp_i8 + -0x93e4a0 >> 9) * -0x55555555);
        }
        tmp_i11 = tmp_i11 + 1;
        tmp_pu9 = tmp_pu9 + 0x600;
      } while (tmp_i11 != g_unk_00abe8a8);
    }
    *(int *)(param_1 + 0x3d4 + tmp_l6 * 4) = tmp_i12;
    goto LAB_000c1ed6;
  case 0xa8:
    tmp_i12 = *(int *)(param_1 + 0x3d4 + tmp_l6 * 4);
LAB_000c1ed6:
    tmp_l6 = strtol(tmp_pc5,(char **)0x0,10);
    if (tmp_l6 == tmp_i12) {
      return true;
    }
    break;
  default:
    G_Error("Scripting: accum %s: unknown command\nPlease Report this error to N!tmod team > etmods.net"
            ,param_2);
    return true;
  }
  *(uint32_t *)(param_1 + 0x3b8) =
       *(uint32_t *)(*(int *)(param_1 + 0x3c0) * 0x62c + *(int *)(param_1 + 0x3b4) + 0x628);
  return true;
}

bool G_ScriptAction_GlobalAccum(int param_1,uint32_t param_2)
{
  uint tmp_u1;
  int tmp_i2;
  byte tmp_b3;
  bool tmp_b4;
  bool tmp_b5;
  char *tmp_pc6;
  long tmp_l7;
  uint32_t tmp_u8;
  long tmp_l9;
  int tmp_i10;
  bool tmp_b11;
  uint32_t local_a0;
  char local_9c [64];
  char local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0xc245b;
  local_a0 = param_2;
  tmp_pc6 = (char *)COM_ParseExt(&local_a0,0);
  if (*tmp_pc6 == '\0') {
    G_Error("G_Scripting: globalaccum without a buffer index\n");
  }
  tmp_l7 = strtol(tmp_pc6,(char **)0x0,10);
  if (9 < tmp_l7) {
    G_Error("G_Scripting: globalaccum buffer is outside range (0 - %i)\n",9);
  }
  tmp_pc6 = (char *)COM_ParseExt(&local_a0,0);
  if (*tmp_pc6 == '\0') {
    G_Error("G_Scripting: globalaccum without a command\n");
  }
  Q_strncpyz(local_9c,tmp_pc6,0x40);
  tmp_pc6 = (char *)COM_ParseExt(&local_a0,0);
  if (*tmp_pc6 == '\0') {
    G_Error("Scripting: globalaccum %s requires a parameter\n",local_9c);
  }
  tmp_u8 = nitrox_GetTokenForString(local_9c);
  switch(tmp_u8) {
  case 0x9a:
    tmp_i10 = (&g_unk_00abe8ac)[(int)(&g_unk_007f66c4 + tmp_l7)];
    tmp_l9 = strtol(tmp_pc6,(char **)0x0,10);
    (&g_unk_00abe8ac)[(int)(&g_unk_007f66c4 + tmp_l7)] = tmp_l9 + tmp_i10;
    tmp_b11 = true;
    break;
  case 0x9b:
    tmp_i10 = *(int *)(&g_unk_02a983bc + tmp_l7 * 4);
    tmp_l7 = strtol(tmp_pc6,(char **)0x0,10);
    if (tmp_l7 <= tmp_i10) {
      return true;
    }
    goto LAB_000c26a8;
  case 0x9c:
    tmp_i10 = *(int *)(&g_unk_02a983bc + tmp_l7 * 4);
    tmp_l7 = strtol(tmp_pc6,(char **)0x0,10);
    if (tmp_i10 <= tmp_l7) {
      return true;
    }
    goto LAB_000c26a8;
  case 0x9d:
  case 0xa8:
    tmp_i10 = *(int *)(&g_unk_02a983bc + tmp_l7 * 4);
    tmp_l7 = strtol(tmp_pc6,(char **)0x0,10);
    if (tmp_i10 == tmp_l7) {
      return true;
    }
    goto LAB_000c26a8;
  case 0x9e:
    tmp_i10 = *(int *)(&g_unk_02a983bc + tmp_l7 * 4);
    tmp_l7 = strtol(tmp_pc6,(char **)0x0,10);
    if (tmp_i10 != tmp_l7) {
      return true;
    }
    goto LAB_000c26a8;
  case 0x9f:
    tmp_l9 = strtol(tmp_pc6,(char **)0x0,10);
    *(long *)(&g_unk_02a983bc + tmp_l7 * 4) = tmp_l9;
    tmp_b11 = true;
    break;
  case 0xa0:
    tmp_i10 = rand();
    tmp_l9 = strtol(tmp_pc6,(char **)0x0,10);
    tmp_b11 = true;
    *(int *)(&g_unk_02a983bc + tmp_l7 * 4) = tmp_i10 % tmp_l9;
    break;
  case 0xa1:
    tmp_u1 = (&g_unk_00abe8ac)[(int)(&g_unk_007f66c4 + tmp_l7)];
    tmp_l9 = strtol(tmp_pc6,(char **)0x0,10);
    tmp_b11 = true;
    (&g_unk_00abe8ac)[(int)(&g_unk_007f66c4 + tmp_l7)] = tmp_u1 | 1 << ((byte)tmp_l9 & 0x1f);
    break;
  case 0xa2:
    tmp_u1 = (&g_unk_00abe8ac)[(int)(&g_unk_007f66c4 + tmp_l7)];
    tmp_l9 = strtol(tmp_pc6,(char **)0x0,10);
    tmp_b11 = true;
    tmp_b3 = (byte)tmp_l9 & 0x1f;
    (&g_unk_00abe8ac)[(int)(&g_unk_007f66c4 + tmp_l7)] =
         tmp_u1 & (-2 << tmp_b3 | 0xfffffffeU >> 0x20 - tmp_b3);
    break;
  case 0xa3:
    tmp_i10 = *(int *)(&g_unk_02a983bc + tmp_l7 * 4);
    tmp_l7 = strtol(tmp_pc6,(char **)0x0,10);
    if ((tmp_i10 >> ((byte)tmp_l7 & 0x1f) & 1U) == 0) {
      return true;
    }
    goto LAB_000c26a8;
  case 0xa4:
    tmp_i10 = *(int *)(&g_unk_02a983bc + tmp_l7 * 4);
    tmp_l7 = strtol(tmp_pc6,(char **)0x0,10);
    if ((tmp_i10 >> ((byte)tmp_l7 & 0x1f) & 1U) != 0) {
      return true;
    }
LAB_000c26a8:
    *(uint32_t *)(param_1 + 0x3b8) =
         *(uint32_t *)(*(int *)(param_1 + 0x3c0) * 0x62c + *(int *)(param_1 + 0x3b4) + 0x628);
    return true;
  case 0xa5:
    tmp_i10 = *(int *)(&g_unk_02a983bc + tmp_l7 * 4);
    tmp_l7 = strtol(tmp_pc6,(char **)0x0,10);
    if (tmp_i10 != tmp_l7) {
      return true;
    }
    tmp_u8 = COM_ParseExt(&local_a0,0);
    Q_strncpyz(local_9c,tmp_u8,0x40);
    if (local_9c[0] == '\0') {
      G_Error("G_Scripting: trigger must have a name and an identifier: %s\n",param_2);
    }
    tmp_u8 = COM_ParseExt(&local_a0,0);
    Q_strncpyz(local_5c,tmp_u8,0x40);
    if (local_5c[0] == '\0') {
      G_Error("G_Scripting: trigger must have a name and an identifier: %s\n",param_2);
    }
    tmp_u8 = BG_StringHashValue(local_9c);
    tmp_b5 = false;
    tmp_b4 = false;
    tmp_i10 = 0;
    while (tmp_i10 = nitrox_FindByScriptNameHash(tmp_i10,tmp_u8), tmp_i10 != 0) {
      tmp_i2 = *(int *)(tmp_i10 + 0x3c4);
      G_Script_ScriptEvent(tmp_i10,"trigger",local_5c);
      tmp_b11 = tmp_b5;
      if ((tmp_i10 == param_1) && (tmp_b11 = true, *(int *)(tmp_i10 + 0x3c4) == tmp_i2)) {
        tmp_b11 = tmp_b5;
      }
      tmp_b5 = tmp_b11;
      tmp_b4 = true;
    }
    tmp_b11 = false;
    if (!tmp_b5) {
      if (tmp_b4) {
        return true;
      }
      G_Printf("G_Scripting: trigger has unknown name: %s\n",local_5c);
      tmp_b11 = true;
    }
    break;
  case 0xa6:
    tmp_i10 = *(int *)(&g_unk_02a983bc + tmp_l7 * 4);
    tmp_l7 = strtol(tmp_pc6,(char **)0x0,10);
    tmp_b11 = tmp_i10 != tmp_l7;
    break;
  default:
    G_Error("Scripting: globalaccum %s: unknown command\n",param_2);
    return true;
  }
  return tmp_b11;
}

uint32_t G_ScriptAction_Print(int param_1,char *param_2)
{
  char *tmp_pc1;
  long tmp_l2;
  char *local_10 [2];
  
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    G_Error("G_Scripting: print requires some text\n");
  }
  local_10[0] = param_2;
  tmp_pc1 = (char *)COM_ParseExt(local_10,0);
  tmp_l2 = 0;
  if ((tmp_pc1 != (char *)0x0) && (*tmp_pc1 == '/')) {
    tmp_l2 = strtol(tmp_pc1 + 1,(char **)0x0,10);
    param_2 = local_10[0];
  }
  if (tmp_l2 <= (int)GHIDRA_FIELD(g_scriptDebugLevel, 12, 4)) {
    G_Printf("(G_Script) %s-> %s\n",*(uint32_t *)(param_1 + 0x3ac),param_2);
  }
  return 1;
}

uint32_t G_ScriptAction_FaceAngles(int param_1,char *param_2)
{
  float tmp_f1;
  long tmp_l2;
  char *tmp_pc3;
  uint32_t tmp_u4;
  uint32_t tmp_u5;
  int tmp_i6;
  int tmp_i7;
  long double tmp_l8;
  double tmp_d9;
  double tmp_d10;
  double tmp_d11;
  int local_48;
  int local_44;
  char *local_38;
  float local_34 [9];
  
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    G_Error("G_Scripting: syntax: faceangles <pitch> <yaw> <roll> <duration/GOTOTIME>\n");
  }
  if (*(int *)(param_1 + 0x3bc) == g_unk_00abe908) {
    local_38 = param_2;
    tmp_i7 = 0;
    do {
      tmp_pc3 = (char *)COM_Parse(&local_38);
      if ((tmp_pc3 == (char *)0x0) || (*tmp_pc3 == '\0')) {
        G_Error("G_Scripting: syntax: faceangles <pitch> <yaw> <roll> <duration/GOTOTIME>\n");
      }
      tmp_l2 = strtol(tmp_pc3,(char **)0x0,10);
      local_34[tmp_i7 + 3] = (float)tmp_l2;
      tmp_i7 = tmp_i7 + 1;
    } while (tmp_i7 != 3);
    tmp_pc3 = (char *)COM_Parse(&local_38);
    if ((tmp_pc3 == (char *)0x0) || (*tmp_pc3 == '\0')) {
      G_Error("G_Scripting: faceangles requires a <pitch> <yaw> <roll> <duration/GOTOTIME>\n");
    }
    tmp_i7 = Q_stricmp(tmp_pc3,"gototime");
    if (tmp_i7 == 0) {
      local_48 = *(int *)(param_1 + 0x14);
    }
    else {
      local_48 = strtol(tmp_pc3,(char **)0x0,10);
    }
    tmp_pc3 = (char *)COM_Parse(&local_38);
    local_44 = 3;
    if ((tmp_pc3 != (char *)0x0) && (*tmp_pc3 != '\0')) {
      tmp_i7 = Q_stricmp(tmp_pc3,"accel");
      tmp_i6 = Q_stricmp(tmp_pc3,"deccel");
      local_44 = 0xb;
      if (tmp_i6 != 0) {
        local_44 = (-(uint)(tmp_i7 == 0) & 7) + 3;
      }
    }
    tmp_i7 = 0;
    do {
      tmp_l8 = (long double)
              AngleDifference(local_34[tmp_i7 + 3],*(uint32_t *)(param_1 + 0x74 + tmp_i7 * 4));
      local_34[tmp_i7] = (float)tmp_l8;
      if ((long double)180.0 < tmp_l8) {
        do {
          tmp_l8 = tmp_l8 - (long double)360.0;
        } while ((long double)180.0 < tmp_l8);
        local_34[tmp_i7] = (float)tmp_l8;
      }
      if (tmp_l8 < (long double)-180.0) {
        do {
          tmp_l8 = tmp_l8 + (long double)360.0;
        } while (tmp_l8 < (long double)-180.0);
        local_34[tmp_i7] = (float)tmp_l8;
      }
      tmp_i7 = tmp_i7 + 1;
    } while (tmp_i7 != 3);
    *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
    *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
    *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
    if (local_48 == 0) {
      *(uint32_t *)(param_1 + 0x50) = 0;
      *(uint32_t *)(param_1 + 0x4c) = 0;
      *(uint32_t *)(param_1 + 0x48) = 0;
    }
    else {
      tmp_f1 = 1000.0 / (float)local_48;
      *(float *)(param_1 + 0x48) = tmp_f1 * local_34[0];
      *(float *)(param_1 + 0x4c) = tmp_f1 * local_34[1];
      *(float *)(param_1 + 0x50) = tmp_f1 * local_34[2];
    }
    *(int *)(param_1 + 0x38) = local_48;
    tmp_i7 = g_unk_00abe908;
    *(uint32_t *)(param_1 + 0x30) = 3;
    *(int *)(param_1 + 0x34) = tmp_i7;
    if (local_44 != 3) {
      tmp_f1 = (float)local_48;
      *(float *)(param_1 + 0x48) = (local_34[0] * 2000.0) / tmp_f1;
      *(float *)(param_1 + 0x4c) = (local_34[1] * 2000.0) / tmp_f1;
      *(float *)(param_1 + 0x50) = (local_34[2] * 2000.0) / tmp_f1;
      *(int *)(param_1 + 0x30) = local_44;
    }
    tmp_pc3 = (char *)_GetEntityName(param_1);
    tmp_d11 = (double)*(float *)(param_1 + 0x50);
    tmp_d10 = (double)*(float *)(param_1 + 0x4c);
    tmp_d9 = (double)*(float *)(param_1 + 0x48);
    tmp_u4 = va("%.2f %.2f %.2f",tmp_d9,tmp_d10,tmp_d11);
    if (tmp_pc3 == (char *)0x0) {
      tmp_pc3 = "<unknown>";
    }
    tmp_u5 = va("%s_start",tmp_pc3,(int)((ulonglong)tmp_d9 >> 0x20),tmp_d10,tmp_d11);
    Bot_Util_SendTrigger(param_1,0,tmp_u5,tmp_u4);
  }
  else {
    tmp_i7 = *(int *)(param_1 + 0x38) + *(int *)(param_1 + 0x34);
    if (tmp_i7 <= g_unk_00abe908) {
      BG_EvaluateTrajectory(param_1 + 0x30,tmp_i7,param_1 + 0x74,1,*(uint32_t *)(param_1 + 0x110));
      *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
      *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
      *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
      tmp_i7 = g_unk_00abe908;
      *(uint32_t *)(param_1 + 0x174) = *(uint32_t *)(param_1 + 0x74);
      *(uint32_t *)(param_1 + 0x178) = *(uint32_t *)(param_1 + 0x78);
      *(uint32_t *)(param_1 + 0x17c) = *(uint32_t *)(param_1 + 0x7c);
      *(uint32_t *)(param_1 + 0x38) = 0;
      *(int *)(param_1 + 0x34) = tmp_i7;
      *(uint32_t *)(param_1 + 0x30) = 0;
      *(uint32_t *)(param_1 + 0x50) = 0;
      *(uint32_t *)(param_1 + 0x4c) = 0;
      *(uint32_t *)(param_1 + 0x48) = 0;
      tmp_pc3 = (char *)_GetEntityName(param_1);
      tmp_d11 = (double)*(float *)(param_1 + 0x50);
      tmp_d10 = (double)*(float *)(param_1 + 0x4c);
      tmp_d9 = (double)*(float *)(param_1 + 0x48);
      tmp_u4 = va("%.2f %.2f %.2f",tmp_d9,tmp_d10,tmp_d11);
      if (tmp_pc3 == (char *)0x0) {
        tmp_pc3 = "<unknown>";
      }
      tmp_u5 = va("%s_stop",tmp_pc3,(int)((ulonglong)tmp_d9 >> 0x20),tmp_d10,tmp_d11);
      Bot_Util_SendTrigger(param_1,0,tmp_u5,tmp_u4);
      script_linkentity(param_1);
      return 1;
    }
  }
  BG_EvaluateTrajectory
            (param_1 + 0x30,g_unk_00abe908,param_1 + 0x174,1,*(uint32_t *)(param_1 + 0x110));
  script_linkentity(param_1);
  return 0;
}

bool G_ScriptAction_ResetScript(int param_1)
{
  return g_unk_00abe908 != *(int *)(param_1 + 0x3bc);
}

uint32_t G_ScriptAction_TagConnect(int param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  int tmp_i3;
  char *tmp_pc4;
  uint32_t local_20 [4];
  
  local_20[0] = param_2;
  tmp_pc1 = (char *)COM_Parse(local_20);
  if (*tmp_pc1 == '\0') {
    G_Error("G_ScriptAction_TagConnect: syntax: attachtotag <targetname> <tagname>\n");
  }
  tmp_u2 = BG_StringHashValue(tmp_pc1);
  tmp_pc4 = tmp_pc1;
  tmp_i3 = G_FindByTargetnameFast(0,tmp_pc1,tmp_u2);
  if (tmp_i3 == 0) {
    tmp_pc4 = (char *)BG_StringHashValue(tmp_pc1);
    tmp_i3 = nitrox_FindByScriptNameHash(0,tmp_pc4);
    if (tmp_i3 == 0) {
      G_Error("G_ScriptAction_TagConnect: unable to find entity with targetname \"%s\"",tmp_pc1);
      tmp_pc4 = tmp_pc1;
    }
  }
  tmp_pc1 = (char *)COM_Parse(local_20);
  if (*tmp_pc1 == '\0') {
    G_Error("G_ScriptAction_TagConnect: syntax: attachtotag <targetname> <tagname>\n",tmp_pc4);
  }
  *(int *)(param_1 + 0x440) = tmp_i3;
  Q_strncpyz(param_1 + 0x400,tmp_pc1,0x40);
  G_ProcessTagConnect(param_1,1);
  *(uint32_t *)(param_1 + 0x3c) = 0;
  *(uint32_t *)(param_1 + 0x40) = 0;
  *(uint32_t *)(param_1 + 0x44) = 0;
  tmp_u2 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0x7c) = 0;
  *(uint32_t *)(param_1 + 0x78) = 0;
  *(uint32_t *)(param_1 + 0x74) = 0;
  *(uint32_t *)(param_1 + 0x34) = tmp_u2;
  *(uint32_t *)(param_1 + 0x38) = 0;
  *(uint32_t *)(param_1 + 0x30) = 0;
  *(uint32_t *)(param_1 + 0x50) = 0;
  *(uint32_t *)(param_1 + 0x4c) = 0;
  *(uint32_t *)(param_1 + 0x48) = 0;
  return 1;
}

uint32_t G_ScriptAction_Halt(int param_1)
{
  int tmp_i1;
  
  tmp_i1 = g_unk_00abe908;
  if (g_unk_00abe908 != *(int *)(param_1 + 0x3bc)) {
    return 1;
  }
  *(uint *)(param_1 + 0x3c8) = *(uint *)(param_1 + 0x3c8) & 0xfffffffe;
  BG_EvaluateTrajectory(param_1 + 0x30,tmp_i1,param_1 + 0x74,1,*(uint32_t *)(param_1 + 0x110));
  *(uint32_t *)(param_1 + 0x3c) = *(uint32_t *)(param_1 + 0x74);
  *(uint32_t *)(param_1 + 0x40) = *(uint32_t *)(param_1 + 0x78);
  *(uint32_t *)(param_1 + 0x44) = *(uint32_t *)(param_1 + 0x7c);
  tmp_i1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0x174) = *(uint32_t *)(param_1 + 0x74);
  *(uint32_t *)(param_1 + 0x178) = *(uint32_t *)(param_1 + 0x78);
  *(uint32_t *)(param_1 + 0x17c) = *(uint32_t *)(param_1 + 0x7c);
  *(uint32_t *)(param_1 + 0x38) = 0;
  *(int *)(param_1 + 0x34) = tmp_i1;
  *(uint32_t *)(param_1 + 0x30) = 0;
  *(uint32_t *)(param_1 + 0x50) = 0;
  *(uint32_t *)(param_1 + 0x4c) = 0;
  *(uint32_t *)(param_1 + 0x48) = 0;
  BG_EvaluateTrajectory
            (param_1 + 0xc,g_unk_00abe908,param_1 + 0x5c,0,*(uint32_t *)(param_1 + 0x110));
  *(uint32_t *)(param_1 + 0x18) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x1c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x20) = *(uint32_t *)(param_1 + 100);
  tmp_i1 = g_unk_00abe908;
  *(uint32_t *)(param_1 + 0x168) = *(uint32_t *)(param_1 + 0x5c);
  *(uint32_t *)(param_1 + 0x16c) = *(uint32_t *)(param_1 + 0x60);
  *(uint32_t *)(param_1 + 0x170) = *(uint32_t *)(param_1 + 100);
  *(uint32_t *)(param_1 + 0x14) = 0;
  *(int *)(param_1 + 0x10) = tmp_i1;
  *(uint32_t *)(param_1 + 0xc) = 0;
  *(uint32_t *)(param_1 + 0x2c) = 0;
  *(uint32_t *)(param_1 + 0x28) = 0;
  *(uint32_t *)(param_1 + 0x24) = 0;
  script_linkentity(param_1);
  return 0;
}

uint32_t G_ScriptAction_StopSound(int param_1)
{
  *(uint32_t *)(param_1 + 0xa0) = 0;
  return 1;
}

uint32_t G_ScriptAction_EntityScriptName(uint32_t param_1,uint32_t param_2)
{
  trap_Cvar_Set("g_scriptName",param_2);
  return 1;
}

uint32_t G_ScriptAction_AIScriptName(void)
{
  return 1;
}

uint32_t G_ScriptAction_AxisRespawntime(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  uint32_t local_10 [3];
  
  local_10[0] = param_2;
  tmp_pc1 = (char *)COM_Parse(local_10);
  if (*tmp_pc1 == '\0') {
    G_Error("G_ScriptAction_AxisRespawntime: time parameter required\n");
  }
  if (GHIDRA_FIELD(g_userAxisRespawnTime, 12, 4) == 0) {
    tmp_pc2 = "%s000";
  }
  else {
    tmp_pc1 = (char *)(GHIDRA_FIELD(g_userAxisRespawnTime, 12, 4) * 1000);
    tmp_pc2 = "%i";
  }
  tmp_u3 = va(tmp_pc2,tmp_pc1);
  trap_Cvar_Set("g_redlimbotime",tmp_u3);
  return 1;
}

uint32_t G_ScriptAction_AlliedRespawntime(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  char *tmp_pc2;
  uint32_t tmp_u3;
  uint32_t local_10 [3];
  
  local_10[0] = param_2;
  tmp_pc1 = (char *)COM_Parse(local_10);
  if (*tmp_pc1 == '\0') {
    G_Error("G_ScriptAction_AlliedRespawntime: time parameter required\n");
  }
  if (GHIDRA_FIELD(g_userAlliedRespawnTime, 12, 4) == 0) {
    tmp_pc2 = "%s000";
  }
  else {
    tmp_pc1 = (char *)(GHIDRA_FIELD(g_userAlliedRespawnTime, 12, 4) * 1000);
    tmp_pc2 = "%i";
  }
  tmp_u3 = va(tmp_pc2,tmp_pc1);
  trap_Cvar_Set("g_bluelimbotime",tmp_u3);
  return 1;
}

uint32_t G_ScriptAction_NumberofObjectives(uint32_t param_1,uint32_t param_2)
{
  char *__nptr;
  long tmp_l1;
  uint32_t local_410;
  uint8_t local_40c [1024];
  
  local_410 = param_2;
  __nptr = (char *)COM_Parse(&local_410);
  if (*__nptr == '\0') {
    G_Error("G_ScriptAction_NumberofObjectives: number parameter required\n");
  }
  tmp_l1 = strtol(__nptr,(char **)0x0,10);
  if (7 < tmp_l1 - 1U) {
    G_Error("G_ScriptAction_NumberofObjectives: Invalid number of objectives\n");
  }
  trap_GetConfigstring(0xd,local_40c,0x400);
  Info_SetValueForKey(local_40c,&g_unk_0024d8f6,__nptr);
  trap_SetConfigstring(0xd,local_40c);
  return 1;
}

uint32_t G_ScriptAction_SetMainObjective(void)
{
  return 1;
}

uint32_t G_ScriptAction_ObjectiveStatus(uint32_t param_1,uint32_t param_2)
{
  char tmp_c1;
  char *tmp_pc2;
  long tmp_l3;
  long tmp_l4;
  char *__nptr;
  uint32_t tmp_u5;
  uint32_t local_420;
  uint8_t local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xc3589;
  local_420 = param_2;
  tmp_pc2 = (char *)COM_Parse(&local_420);
  if (*tmp_pc2 == '\0') {
    G_Error("G_ScriptAction_ObjectiveImage: number parameter required\n");
  }
  tmp_l3 = strtol(tmp_pc2,(char **)0x0,10);
  if (7 < tmp_l3 - 1U) {
    G_Error("G_ScriptAction_ObjectiveImage: Invalid objective number\n");
  }
  tmp_pc2 = (char *)COM_Parse(&local_420);
  if (*tmp_pc2 == '\0') {
    G_Error("G_ScriptAction_ObjectiveImage: team parameter required\n");
  }
  tmp_l4 = strtol(tmp_pc2,(char **)0x0,10);
  if (tmp_l4 == 0) {
    tmp_pc2 = "x";
    __nptr = (char *)COM_Parse(&local_420);
    tmp_c1 = *__nptr;
  }
  else {
    tmp_pc2 = "a";
    __nptr = (char *)COM_Parse(&local_420);
    tmp_c1 = *__nptr;
  }
  if (tmp_c1 == '\0') {
    G_Error("G_ScriptAction_ObjectiveImage: status parameter required\n");
  }
  tmp_l4 = strtol(__nptr,(char **)0x0,10);
  if (((tmp_l4 != 0) && (tmp_l4 = strtol(__nptr,(char **)0x0,10), tmp_l4 != 1)) &&
     (tmp_l4 = strtol(__nptr,(char **)0x0,10), tmp_l4 != 2)) {
    G_Error(
           "G_ScriptAction_ObjectiveImage: status parameter must be 0 (default), 1 (complete) or 2 (failed)\n"
           );
  }
  trap_GetConfigstring(0xf,local_41c,0x400);
  tmp_u5 = va(&g_unk_00249b6d,tmp_pc2,tmp_l3);
  Info_SetValueForKey(local_41c,tmp_u5,__nptr);
  trap_SetConfigstring(0xf,local_41c);
  tmp_u5 = _GetEntityName(param_1);
  tmp_l3 = strtol(__nptr,(char **)0x0,10);
  if (tmp_l3 == 1) {
    if (*tmp_pc2 == 'x') {
      tmp_pc2 = "axis_complete";
    }
    else {
      tmp_pc2 = "allied_complete";
    }
  }
  else if (tmp_l3 == 2) {
    if (*tmp_pc2 == 'x') {
      tmp_pc2 = "axis_failed";
    }
    else {
      tmp_pc2 = "allied_failed";
    }
  }
  else {
    if (tmp_l3 != 0) {
      return 1;
    }
    if (*tmp_pc2 == 'x') {
      tmp_pc2 = "axis_default";
    }
    else {
      tmp_pc2 = "allied_default";
    }
  }
  Bot_Util_SendTrigger(param_1,0,tmp_u5,tmp_pc2);
  return 1;
}

uint32_t G_ScriptAction_SetDebugLevel(uint32_t param_1,char *param_2)
{
  char *__nptr;
  long tmp_l1;
  uint32_t tmp_u2;
  char *local_10 [2];
  
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    G_Error("G_ScriptAction_SetDebugLevel: requires integer level\n");
  }
  local_10[0] = param_2;
  __nptr = (char *)COM_ParseExt(local_10,0);
  if ((__nptr != (char *)0x0) && (*__nptr != '\0')) {
    tmp_l1 = strtol(__nptr,(char **)0x0,10);
    tmp_u2 = va("%i",tmp_l1);
    trap_Cvar_Set("g_scriptDebugLevel",tmp_u2);
  }
  return 1;
}

uint32_t G_ScriptAction_VoiceAnnounce(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint tmp_u2;
  uint32_t local_10 [2];
  
  if (GHIDRA_FIELD(g_gamestate, 12, 4) != 3) {
    local_10[0] = param_2;
    tmp_pc1 = (char *)COM_Parse(local_10);
    if (*tmp_pc1 == '\0') {
      G_Error("G_ScriptAction_VoiceAnnounce: team parameter required\n");
    }
    tmp_u2 = strtol(tmp_pc1,(char **)0x0,10);
    if (1 < tmp_u2) {
      G_Error("G_ScriptAction_VoiceAnnounce: Invalid team number\n");
    }
    tmp_pc1 = (char *)COM_Parse(local_10);
    if (*tmp_pc1 == '\0') {
      G_Error("G_ScriptAction_VoiceAnnounce: system message parameter required\n");
    }
  }
  return 1;
}

uint32_t G_ScriptAction_SetWinner(uint32_t param_1,uint32_t param_2)
{
  char *__nptr;
  long tmp_l1;
  uint32_t local_410;
  uint8_t local_40c [1024];
  
  if (GHIDRA_FIELD(g_gamestate, 12, 4) != 3) {
    local_410 = param_2;
    __nptr = (char *)COM_Parse(&local_410);
    if (*__nptr == '\0') {
      G_Error("G_ScriptAction_SetWinner: number parameter required\n");
    }
    tmp_l1 = strtol(__nptr,(char **)0x0,10);
    if (2 < tmp_l1 + 1U) {
      G_Error("G_ScriptAction_SetWinner: Invalid team number\n");
    }
    trap_GetConfigstring(0xe,local_40c,0x400);
    Info_SetValueForKey(local_40c,"w",__nptr);
    trap_SetConfigstring(0xe,local_40c);
  }
  return 1;
}

uint32_t G_ScriptAction_SetDefendingTeam(uint32_t param_1,uint32_t param_2)
{
  char *__nptr;
  uint tmp_u1;
  uint32_t local_410;
  uint8_t local_40c [1024];
  
  if (GHIDRA_FIELD(g_gamestate, 12, 4) != 3) {
    local_410 = param_2;
    __nptr = (char *)COM_Parse(&local_410);
    if (*__nptr == '\0') {
      G_Error("G_ScriptAction_SetDefendingTeam: number parameter required\n");
    }
    tmp_u1 = strtol(__nptr,(char **)0x0,10);
    if (1 < tmp_u1) {
      G_Error("G_ScriptAction_SetDefendingTeam: Invalid team number\n");
    }
    trap_GetConfigstring(0xd,local_40c,0x400);
    Info_SetValueForKey(local_40c,&g_unk_00245eea,__nptr);
    trap_SetConfigstring(0xd,local_40c);
  }
  return 1;
}

uint32_t G_ScriptAction_AddTeamVoiceAnnounce(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  long tmp_l2;
  uint tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  uint32_t local_20 [4];
  
  if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
    local_20[0] = param_2;
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      G_Error("G_ScriptAction_AddTeamVoiceAnnounce: team parameter required\n");
    }
    tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
    tmp_u3 = (uint)(tmp_l2 != 0);
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      G_Error("G_ScriptAction_AddTeamVoiceAnnounce: sound parameter required\n");
    }
    tmp_i4 = G_SoundIndex(tmp_pc1);
    tmp_i5 = tmp_u3 * 0x40;
    tmp_i4 = tmp_i4 + 1;
    if (((((*(int *)(&g_unk_02aa2f0c + tmp_i5) != tmp_i4) && (*(int *)(&g_unk_02aa2f10 + tmp_i5) != tmp_i4))
         && (*(int *)(&g_unk_02aa2f14 + tmp_i5) != tmp_i4)) &&
        (((*(int *)(&g_unk_02aa2f18 + tmp_i5) != tmp_i4 && (*(int *)(&g_unk_02aa2f1c + tmp_i5) != tmp_i4))
         && ((*(int *)(&g_unk_02aa2f20 + tmp_i5) != tmp_i4 &&
             ((*(int *)(&g_unk_02aa2f24 + tmp_i5) != tmp_i4 &&
              (*(int *)(&g_unk_02aa2f28 + tmp_i5) != tmp_i4)))))))) &&
       (((&g_unk_00abe8ac)[(tmp_u3 + 0x7f91a) * 0x10] != tmp_i4 &&
        (*(int *)(&g_unk_02aa2f30 + tmp_i5) != tmp_i4)))) {
      tmp_i6 = tmp_u3 * 0x40;
      if (((((*(int *)(&g_unk_02aa2f34 + tmp_i6) != tmp_i4) &&
            (*(int *)(&g_unk_02aa2f38 + tmp_i6) != tmp_i4)) &&
           (*(int *)(&g_unk_02aa2f3c + tmp_i6) != tmp_i4)) &&
          ((*(int *)(&g_unk_02aa2f40 + tmp_i6) != tmp_i4 && (*(int *)(&g_unk_02aa2f44 + tmp_i6) != tmp_i4)))
          ) && (*(int *)(&g_unk_02aa2f48 + tmp_i6) != tmp_i4)) {
        if (*(int *)(&g_unk_02aa2f0c + tmp_i5) == 0) {
          tmp_i5 = 0;
        }
        else if (*(int *)(&g_unk_02aa2f10 + tmp_i5) == 0) {
          tmp_i5 = 1;
        }
        else if (*(int *)(&g_unk_02aa2f14 + tmp_i5) == 0) {
          tmp_i5 = 2;
        }
        else if (*(int *)(&g_unk_02aa2f18 + tmp_i5) == 0) {
          tmp_i5 = 3;
        }
        else if (*(int *)(&g_unk_02aa2f1c + tmp_i5) == 0) {
          tmp_i5 = 4;
        }
        else if (*(int *)(&g_unk_02aa2f20 + tmp_i5) == 0) {
          tmp_i5 = 5;
        }
        else if (*(int *)(&g_unk_02aa2f24 + tmp_i5) == 0) {
          tmp_i5 = 6;
        }
        else if (*(int *)(&g_unk_02aa2f28 + tmp_i5) == 0) {
          tmp_i5 = 7;
        }
        else if ((&g_unk_00abe8ac)[(tmp_u3 + 0x7f91a) * 0x10] == 0) {
          tmp_i5 = 8;
        }
        else if (*(int *)(&g_unk_02aa2f30 + tmp_i5) == 0) {
          tmp_i5 = 9;
        }
        else if (*(int *)(&g_unk_02aa2f34 + tmp_i6) == 0) {
          tmp_i5 = 10;
        }
        else if (*(int *)(&g_unk_02aa2f38 + tmp_i6) == 0) {
          tmp_i5 = 0xb;
        }
        else if (*(int *)(&g_unk_02aa2f3c + tmp_i6) == 0) {
          tmp_i5 = 0xc;
        }
        else if (*(int *)(&g_unk_02aa2f40 + tmp_i6) == 0) {
          tmp_i5 = 0xd;
        }
        else if (*(int *)(&g_unk_02aa2f44 + tmp_i6) == 0) {
          tmp_i5 = 0xe;
        }
        else {
          if (*(int *)(&g_unk_02aa2f48 + tmp_i6) != 0) {
            return 1;
          }
          tmp_i5 = 0xf;
        }
        (&g_unk_00abe8ac)[(int)(&g_unk_007f9198 + tmp_u3 * 0x10 + tmp_i5)] = tmp_i4;
      }
    }
  }
  return 1;
}

uint32_t G_ScriptAction_RemoveTeamVoiceAnnounce(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  long tmp_l2;
  int tmp_i3;
  uint tmp_u4;
  uint32_t local_10;
  
  local_10 = param_2;
  tmp_pc1 = (char *)COM_Parse(&local_10);
  if (*tmp_pc1 == '\0') {
    G_Error("G_ScriptAction_RemoveTeamVoiceAnnounce: team parameter required\n");
  }
  tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_u4 = (uint)(tmp_l2 != 0);
  tmp_pc1 = (char *)COM_Parse(&local_10);
  if (*tmp_pc1 == '\0') {
    G_Error("G_ScriptAction_RemoveTeamVoiceAnnounce: sound parameter required\n");
  }
  tmp_i3 = G_SoundIndex(tmp_pc1);
  tmp_i3 = tmp_i3 + 1;
  if (tmp_i3 == *(int *)(&g_unk_02aa2f0c + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f0c + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f10 + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f10 + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f14 + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f14 + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f18 + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f18 + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f1c + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f1c + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f20 + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f20 + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f24 + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f24 + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f28 + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f28 + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == (&g_unk_00abe8ac)[(tmp_u4 + 0x7f91a) * 0x10]) {
    (&g_unk_00abe8ac)[(tmp_u4 + 0x7f91a) * 0x10] = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f30 + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f30 + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f34 + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f34 + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f38 + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f38 + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f3c + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f3c + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f40 + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f40 + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 == *(int *)(&g_unk_02aa2f44 + tmp_u4 * 0x40)) {
    *(uint32_t *)(&g_unk_02aa2f44 + tmp_u4 * 0x40) = 0;
  }
  if (tmp_i3 != *(int *)(&g_unk_02aa2f48 + tmp_u4 * 0x40)) {
    return 1;
  }
  *(uint32_t *)(&g_unk_02aa2f48 + tmp_u4 * 0x40) = 0;
  return 1;
}

uint32_t G_ScriptAction_TeamVoiceAnnounce(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  long tmp_l2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint32_t local_20 [4];
  
  if (GHIDRA_FIELD(g_gamestate, 12, 4) == 0) {
    local_20[0] = param_2;
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      G_Error("G_ScriptAction_TeamVoiceAnnounce: team parameter required\n");
    }
    tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
    tmp_pc1 = (char *)COM_Parse(local_20);
    if (*tmp_pc1 == '\0') {
      G_Error("G_ScriptAction_TeamVoiceAnnounce: sound parameter required\n");
    }
    tmp_i3 = nitrox_TempEventFromQueue(0,0x2c);
    *(uint *)(tmp_i3 + 0x108) = 2 - (uint)(tmp_l2 == 0);
    tmp_u4 = G_SoundIndex(tmp_pc1);
    *(uint32_t *)(tmp_i3 + 0x128) = 0x20;
    *(uint32_t *)(tmp_i3 + 0xbc) = tmp_u4;
    Bot_Util_SendTrigger(param_1,0,tmp_pc1,"team_announce");
  }
  return 1;
}

uint32_t G_ScriptAction_Announce_Icon(uint32_t param_1,uint32_t param_2)
{
  char tmp_c1;
  char *tmp_pc2;
  uint tmp_u3;
  uint32_t tmp_u4;
  uint tmp_u5;
  uint32_t local_10;
  
  if (GHIDRA_FIELD(g_gamestate, 12, 4) != 3) {
    local_10 = param_2;
    tmp_pc2 = (char *)COM_Parse(&local_10);
    if (*tmp_pc2 == '\0') {
      G_Error("G_ScriptAction_Announce_Icon: icon index parameter required\n");
    }
    tmp_u5 = 0;
    tmp_u3 = strtol(tmp_pc2,(char **)0x0,10);
    if (tmp_u3 < 0xb) {
      tmp_pc2 = (char *)COM_Parse(&local_10);
      tmp_c1 = *tmp_pc2;
    }
    else {
      tmp_u5 = tmp_u3;
      G_Error("G_ScriptAction_Announce_Icon: icon index parameter out of range %i\n",tmp_u3);
      tmp_pc2 = (char *)COM_Parse(&local_10);
      tmp_c1 = *tmp_pc2;
    }
    if (tmp_c1 == '\0') {
      G_Error("G_ScriptAction_Announce_Icon: statement parameter required\n",tmp_u5);
    }
    tmp_u4 = va("cpmi %i \"%s\"",tmp_u3,tmp_pc2);
    trap_SendServerCommand(0xffffffff,tmp_u4);
    Bot_Util_SendTrigger(param_1,0,tmp_pc2,"announce_icon");
    G_LogPrintf("nitmod announce: \"%s\"\n",tmp_pc2);
  }
  return 1;
}

uint32_t G_ScriptAction_Announce(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t local_10;
  uint32_t uStack_c;
  
  uStack_c = 0xc4507;
  if (GHIDRA_FIELD(g_gamestate, 12, 4) != 3) {
    local_10 = param_2;
    tmp_pc1 = (char *)COM_Parse(&local_10);
    if (*tmp_pc1 == '\0') {
      G_Error("G_ScriptAction_Announce: statement parameter required\n");
    }
    tmp_u2 = va("cpm_map \"%s\"",tmp_pc1);
    trap_SendServerCommand(0xffffffff,tmp_u2);
    Bot_Util_SendTrigger(param_1,0,tmp_pc1,"announce");
    G_LogPrintf("nitmod announce: \"%s\"\n",tmp_pc1);
  }
  return 1;
}

uint32_t G_ScriptAction_EndRound(void)
{
  char *__nptr;
  long tmp_l1;
  uint8_t local_40c [1024];
  
  if (GHIDRA_FIELD(g_gamestate, 12, 4) != 3) {
    if (GHIDRA_FIELD(g_gametype, 12, 4) == 7) {
      if (0 < (int)GHIDRA_FIELD(g_TDMObjBonus, 12, 4)) {
        trap_GetConfigstring(0xe,local_40c,0x400);
        __nptr = (char *)Info_ValueForKey(local_40c,"w");
        tmp_l1 = strtol(__nptr,(char **)0x0,10);
        if (tmp_l1 == 1) {
          g_unk_00abe924 = g_unk_00abe924 + GHIDRA_FIELD(g_TDMObjBonus, 12, 4);
        }
        else if (tmp_l1 == 0) {
          g_unk_00abe920 = g_unk_00abe920 + GHIDRA_FIELD(g_TDMObjBonus, 12, 4);
        }
      }
    }
    else {
      LogExit("Wolf EndRound.");
    }
  }
  return 1;
}

uint32_t G_ScriptAction_SetRoundTimelimit(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  uint32_t tmp_u2;
  uint32_t local_10 [3];
  
  local_10[0] = param_2;
  tmp_pc1 = (char *)COM_Parse(local_10);
  if (*tmp_pc1 == '\0') {
    G_Error("G_ScriptAction_SetRoundTimelimit: number parameter required\n");
  }
  tmp_u2 = GHIDRA_FIELD(g_userTimeLimit, 12, 4);
  if (GHIDRA_FIELD(g_gametype, 12, 4) == 3) {
    if ((float)GHIDRA_FIELD(g_nextTimeLimit, 8, 4) != 0.0) {
      tmp_u2 = va("%f",(double)(float)GHIDRA_FIELD(g_nextTimeLimit, 8, 4));
      trap_Cvar_Set("timelimit",tmp_u2);
      return 1;
    }
  }
  else if (GHIDRA_FIELD(g_gametype, 12, 4) == 5) {
    if (GHIDRA_FIELD(g_userTimeLimit, 12, 4) != 0) {
      if ((int)GHIDRA_FIELD(g_userTimeLimit, 12, 4) < 3) {
        tmp_u2 = 3;
      }
      goto LAB_000c4748;
    }
    goto LAB_000c470f;
  }
  if (GHIDRA_FIELD(g_userTimeLimit, 12, 4) != 0) {
LAB_000c4748:
    tmp_u2 = va("%i",tmp_u2);
    trap_Cvar_Set("timelimit",tmp_u2);
    return 1;
  }
LAB_000c470f:
  trap_Cvar_Set("timelimit",tmp_pc1);
  return 1;
}

uint32_t G_ScriptAction_RemoveEntity(int param_1)
{
  *(void **)(param_1 + 0x2a4) = G_FreeEntity;
  *(int *)(param_1 + 0x29c) = g_unk_00abe908 + 100;
  return 1;
}

uint32_t G_ScriptAction_SetDamagable(uint32_t param_1,uint32_t param_2)
{
  uint32_t tmp_u1;
  long tmp_l2;
  int tmp_i3;
  uint32_t local_a0;
  char local_9c [64];
  char local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0xc482b;
  local_a0 = param_2;
  tmp_u1 = COM_ParseExt(&local_a0,0);
  Q_strncpyz(local_9c,tmp_u1,0x40);
  if (local_9c[0] == '\0') {
    G_Error("G_Scripting: setdamagable must have a name and an state\n");
  }
  tmp_u1 = COM_ParseExt(&local_a0,0);
  Q_strncpyz(local_5c,tmp_u1,0x40);
  if (local_5c[0] == '\0') {
    G_Error("G_Scripting: setdamagable must have a name and an state\n");
  }
  tmp_l2 = strtol(local_5c,(char **)0x0,10);
  tmp_u1 = BG_StringHashValue(local_9c);
  tmp_i3 = 0x955ea0;
  while( true ) {
    tmp_i3 = G_FindByTargetnameFast(tmp_i3,local_9c,tmp_u1);
    if (tmp_i3 == 0) break;
    *(uint *)(tmp_i3 + 0x2cc) = (uint)(tmp_l2 == 1);
  }
  return 1;
}

uint32_t G_ScriptAction_SetState(uint32_t param_1,uint32_t param_2)
{
  bool tmp_b1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t tmp_u4;
  uint32_t local_a0;
  char local_9c [64];
  char local_5c [72];
  uint32_t uStack_14;
  
  uStack_14 = 0xc4950;
  local_a0 = param_2;
  tmp_u2 = COM_ParseExt(&local_a0,0);
  Q_strncpyz(local_9c,tmp_u2,0x40);
  if (local_9c[0] == '\0') {
    G_Error("G_Scripting: setstate must have a name and an state\n");
  }
  tmp_u2 = COM_ParseExt(&local_a0,0);
  Q_strncpyz(local_5c,tmp_u2,0x40);
  if (local_5c[0] == '\0') {
    G_Error("G_Scripting: setstate must have a name and an state\n");
  }
  tmp_u2 = 0;
  tmp_i3 = Q_stricmp(local_5c,"default");
  if (tmp_i3 != 0) {
    tmp_u2 = 1;
    tmp_i3 = Q_stricmp(local_5c,"invisible");
    if (tmp_i3 != 0) {
      tmp_u2 = 2;
      tmp_i3 = Q_stricmp(local_5c,"underconstruction");
      if (tmp_i3 != 0) {
        tmp_u2 = 0;
        G_Error("G_Scripting: setstate with invalid state \'%s\'\n",local_5c);
      }
    }
  }
  tmp_u4 = BG_StringHashValue(local_9c);
  tmp_b1 = false;
  tmp_i3 = 0x955ea0;
  while( true ) {
    tmp_i3 = G_FindByTargetnameFast(tmp_i3,local_9c,tmp_u4);
    if (tmp_i3 == 0) break;
    G_SetEntState(tmp_i3,tmp_u2);
    tmp_b1 = true;
  }
  if (tmp_b1) {
    return 1;
  }
  G_Printf("^1Warning: setstate called and no entities found\n");
  return 1;
}

uint32_t G_ScriptAction_RepairMG42(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  uint32_t local_60;
  char local_5c [76];
  
  local_60 = param_2;
  tmp_u2 = COM_ParseExt(&local_60,0);
  Q_strncpyz(local_5c,tmp_u2,0x40);
  if (local_5c[0] == '\0') {
    G_Error("G_Scripting: repairmg42 must have a target\n");
  }
  if (0 < MG42Entities) {
    tmp_i4 = 0;
    tmp_i3 = MG42Entities;
    do {
      tmp_i1 = (&g_unk_0087a9c4)[tmp_i4];
      if (*(int *)(tmp_i1 + 0x2cc) == 0) {
        *(uint32_t *)(tmp_i1 + 0xb0) = 0;
        if (*(int *)(tmp_i1 + 0x388) < 1) {
          *(uint32_t *)(tmp_i1 + 0x2c8) = 0x15e;
        }
        else {
          *(uint32_t *)(g_entities + *(int *)(tmp_i1 + 0x388) * 0x600 + 0x2c8) = 0x15e;
          *(uint32_t *)(g_entities + *(int *)(tmp_i1 + 0x388) * 0x600 + 0x2cc) = 1;
          *(uint32_t *)(tmp_i1 + 0x2c8) = 0;
        }
        *(uint32_t *)(tmp_i1 + 0x2cc) = 1;
        *(uint *)(tmp_i1 + 8) = *(uint *)(tmp_i1 + 8) & 0xffffdfff;
        Bot_Util_SendTrigger(param_1,0,local_5c,"repair_mg42");
        tmp_i3 = MG42Entities;
      }
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_i4 < tmp_i3);
  }
  return 1;
}

uint32_t G_ScriptAction_SetHQStatus(uint32_t param_1,uint32_t param_2)
{
  char *tmp_pc1;
  long tmp_l2;
  long tmp_l3;
  uint32_t local_10;
  
  local_10 = param_2;
  tmp_pc1 = (char *)COM_ParseExt(&local_10,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: sethqstatus must have a team\n");
  }
  tmp_l2 = strtol(tmp_pc1,(char **)0x0,10);
  tmp_pc1 = (char *)COM_ParseExt(&local_10,0);
  if (*tmp_pc1 == '\0') {
    G_Error("G_Scripting: sethqstatus must have a status\n");
  }
  tmp_l3 = strtol(tmp_pc1,(char **)0x0,10);
  if (g_unk_02a9969c != 0) {
    if (tmp_l2 == 0) {
      *(long *)(g_unk_02a9969c + 0xa4) = tmp_l3;
    }
    else if (tmp_l2 == 1) {
      *(long *)(g_unk_02a9969c + 0xa8) = tmp_l3;
    }
    else {
      G_Error("G_Scripting: sethqstatus with bad team set");
    }
  }
  return 1;
}

uint32_t G_ScriptAction_PrintAccum(int param_1,char *param_2)
{
  char *__nptr;
  uint tmp_u1;
  char *local_10;
  
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    G_Error("G_ScriptAction_PrintAccum: syntax: PrintAccum <accumNumber>\n");
  }
  local_10 = param_2;
  __nptr = (char *)COM_ParseExt(&local_10,0);
  if (*__nptr == '\0') {
    G_Error("G_ScriptAction_PrintAccum: syntax: PrintAccum <accumNumber>\n");
  }
  tmp_u1 = strtol(__nptr,(char **)0x0,10);
  if (9 < tmp_u1) {
    G_Error("G_ScriptAction_PrintAccum: buffer is outside range (0 - %i)",9);
  }
  G_Printf("(G_Script) %s: Accum[%i] = %d\n",*(uint32_t *)(param_1 + 0x3ac),tmp_u1,
           *(uint32_t *)(param_1 + 0x3d4 + tmp_u1 * 4));
  return 1;
}

uint32_t G_ScriptAction_PrintGlobalAccum(uint32_t param_1,char *param_2)
{
  char *__nptr;
  uint tmp_u1;
  char *local_10 [2];
  
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    G_Error("G_ScriptAction_PrintGlobalAccum: syntax: PrintGlobalAccum <globalAccumNumber>\n");
  }
  local_10[0] = param_2;
  __nptr = (char *)COM_ParseExt(local_10,0);
  if (*__nptr == '\0') {
    G_Error("G_ScriptAction_PrintGlobalAccum: syntax: PrintGlobalAccum <globalAccumNumber>\n");
  }
  tmp_u1 = strtol(__nptr,(char **)0x0,10);
  if (9 < tmp_u1) {
    G_Error("PrintGlobalAccum: buffer is outside range (0 - %i)",9);
  }
  G_Printf("(G_Script) GlobalAccum[%i] = %d\n",tmp_u1,*(uint32_t *)(&g_unk_02a983bc + tmp_u1 * 4));
  return 1;
}

uint32_t G_ScriptAction_SetAASState(void)
{
  return 1;
}

uint32_t G_ScriptAction_Construct(uint32_t param_1,uint32_t param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  uint32_t local_10;
  
  local_10 = param_2;
  tmp_i1 = COM_ParseExt(&local_10,0);
  if (tmp_i1 == 0) {
    G_Error("G_Scripting: \"construct\" must have a targetname\n");
  }
  tmp_u2 = BG_StringHashValue(tmp_i1);
  tmp_i3 = G_FindByTargetnameFast(0,tmp_i1,tmp_u2);
  if (((tmp_i3 == 0) || (*(int *)(tmp_i3 + 0x194) == 0)) || (*(int *)(tmp_i3 + 4) != 0x20)) {
    G_Error("G_Scripting: \"construct\" could not find entity with targetname: %s\n",tmp_i1);
  }
  AutoBuildConstruction(tmp_i3);
  return 1;
}

uint32_t G_ScriptAction_ConstructibleClass(int param_1,uint32_t param_2)
{
  char *__nptr;
  long tmp_l1;
  uint tmp_u2;
  uint32_t local_10;
  
  local_10 = param_2;
  __nptr = (char *)COM_ParseExt(&local_10,0);
  if (__nptr == (char *)0x0) {
    G_Error("G_Scripting: \"constructible_class\" must have a class value\n");
  }
  tmp_l1 = strtol(__nptr,(char **)0x0,10);
  if (2 < tmp_l1 - 1U) {
    G_Error("G_Scripting: \"constructible_class\" has a bad value %i\n",tmp_l1);
  }
  tmp_u2 = 0;
  do {
    *(uint32_t *)(param_1 + 0x4e4 + tmp_u2) =
         *(uint32_t *)(g_constructible_classes + tmp_u2 + (tmp_l1 - 1U) * 0x18);
    tmp_u2 = tmp_u2 + 4;
  } while (tmp_u2 < 0x18);
  *(int *)(param_1 + 0x4f4) = *(int *)(param_1 + 0x4f4) + -1;
  *(uint32_t *)(param_1 + 0x2c8) = *(uint32_t *)(param_1 + 0x4f0);
  return 1;
}

uint32_t G_ScriptAction_ConstructibleChargeBarReq(int param_1,uint32_t param_2)
{
  float tmp_f1;
  char *__nptr;
  double tmp_d2;
  uint32_t local_10 [3];
  
  local_10[0] = param_2;
  __nptr = (char *)COM_ParseExt(local_10,0);
  if (__nptr == (char *)0x0) {
    G_Error("G_Scripting: \"constructible_chargebarreq\" must have a fraction value\n");
  }
  tmp_d2 = strtod(__nptr,(char **)0x0);
  tmp_f1 = (float)tmp_d2;
  if (tmp_f1 < 0.0) {
    G_Error("G_Scripting: \"constructible_chargebarreq\" has a bad value %f\n",(double)tmp_f1);
  }
  *(float *)(param_1 + 0x4e4) = tmp_f1;
  return 1;
}

uint32_t G_ScriptAction_ConstructibleConstructXPBonus(int param_1,uint32_t param_2)
{
  char *__nptr;
  long tmp_l1;
  uint32_t local_10 [3];
  
  local_10[0] = param_2;
  __nptr = (char *)COM_ParseExt(local_10,0);
  if (__nptr == (char *)0x0) {
    G_Error("G_Scripting: \"constructible_constructxpbonus\" must have a xppoints value\n");
  }
  tmp_l1 = strtol(__nptr,(char **)0x0,10);
  if (tmp_l1 < 0) {
    G_Error("G_Scripting: \"constructible_constructxpbonus\" has a bad value %i\n",tmp_l1);
  }
  *(float *)(param_1 + 0x4e8) = (float)tmp_l1;
  return 1;
}

uint32_t G_ScriptAction_ConstructibleDestructXPBonus(int param_1,uint32_t param_2)
{
  char *__nptr;
  long tmp_l1;
  uint32_t local_10 [3];
  
  local_10[0] = param_2;
  __nptr = (char *)COM_ParseExt(local_10,0);
  if (__nptr == (char *)0x0) {
    G_Error("G_Scripting: \"constructible_destructxpbonus\" must have a xppoints value\n");
  }
  tmp_l1 = strtol(__nptr,(char **)0x0,10);
  if (tmp_l1 < 0) {
    G_Error("G_Scripting: \"constructible_destructxpbonus\" has a bad value %i\n",tmp_l1);
  }
  *(float *)(param_1 + 0x4ec) = (float)tmp_l1;
  return 1;
}

uint32_t G_ScriptAction_ConstructibleHealth(int param_1,uint32_t param_2)
{
  char *__nptr;
  long tmp_l1;
  uint32_t local_10 [2];
  
  local_10[0] = param_2;
  __nptr = (char *)COM_ParseExt(local_10,0);
  if (__nptr == (char *)0x0) {
    G_Error("G_Scripting: \"constructible_health\" must have a health value\n");
  }
  tmp_l1 = strtol(__nptr,(char **)0x0,10);
  if (tmp_l1 < 1) {
    G_Error("G_Scripting: \"constructible_health\" has a bad value %i\n",tmp_l1);
  }
  *(long *)(param_1 + 0x4f0) = tmp_l1;
  *(long *)(param_1 + 0x2c8) = tmp_l1;
  return 1;
}

uint32_t G_ScriptAction_ConstructibleWeaponclass(int param_1,uint32_t param_2)
{
  char *__nptr;
  long tmp_l1;
  uint32_t local_10 [2];
  
  local_10[0] = param_2;
  __nptr = (char *)COM_ParseExt(local_10,0);
  if (__nptr == (char *)0x0) {
    G_Error("G_Scripting: \"constructible_weaponclass\" must have a weapon class value\n");
  }
  tmp_l1 = strtol(__nptr,(char **)0x0,10);
  if (2 < tmp_l1 - 1U) {
    G_Error("G_Scripting: \"constructible_weaponclass\" has a bad value %i\n",tmp_l1);
  }
  *(uint *)(param_1 + 0x4f4) = tmp_l1 - 1U;
  return 1;
}

uint32_t G_ScriptAction_ConstructibleDuration(int param_1,uint32_t param_2)
{
  char *__nptr;
  long tmp_l1;
  uint32_t local_10 [3];
  
  local_10[0] = param_2;
  __nptr = (char *)COM_ParseExt(local_10,0);
  if (__nptr == (char *)0x0) {
    G_Error("G_Scripting: \"constructible_duration\" must have a duration value\n");
  }
  tmp_l1 = strtol(__nptr,(char **)0x0,10);
  if (tmp_l1 < 0) {
    G_Error("G_Scripting: \"constructible_duration\" has a bad value %i\n",tmp_l1);
  }
  *(long *)(param_1 + 0x4f8) = tmp_l1;
  return 1;
}

bool G_ScriptAction_Cvar(int param_1,uint32_t param_2)
{
  int tmp_i1;
  byte tmp_b2;
  bool tmp_b3;
  bool tmp_b4;
  char *tmp_pc5;
  uint tmp_u6;
  int tmp_i7;
  uint32_t tmp_u8;
  uint tmp_u9;
  long tmp_l10;
  uint32_t local_e0;
  char local_dc [64];
  char local_9c [64];
  uint8_t local_5c [76];
  
  local_e0 = param_2;
  tmp_pc5 = (char *)COM_ParseExt(&local_e0,0);
  if (*tmp_pc5 == '\0') {
    G_Error("G_Scripting: cvar without a cvar name\n");
  }
  Q_strncpyz(local_5c,tmp_pc5,0x40);
  tmp_u6 = trap_Cvar_VariableIntegerValue(local_5c);
  tmp_pc5 = (char *)COM_ParseExt(&local_e0,0);
  if (*tmp_pc5 == '\0') {
    G_Error("G_Scripting: cvar without a command\n");
  }
  Q_strncpyz(local_dc,tmp_pc5,0x40);
  tmp_pc5 = (char *)COM_ParseExt(&local_e0,0);
  if (*tmp_pc5 == '\0') {
    G_Error("G_Scripting: cvar %s requires a parameter\n",local_dc);
  }
  tmp_i7 = Q_stricmp(local_dc,"abort_if_equals");
  if ((tmp_i7 == 0) && (tmp_u9 = strtol(tmp_pc5,(char **)0x0,10), tmp_u6 == tmp_u9)) {
    *(uint32_t *)(param_1 + 0x3b8) =
         *(uint32_t *)(*(int *)(param_1 + 0x3c0) * 0x62c + *(int *)(param_1 + 0x3b4) + 0x628);
  }
  tmp_u8 = nitrox_GetTokenForString(local_dc);
  switch(tmp_u8) {
  case 0x9a:
    tmp_u6 = tmp_u6 + 1;
    break;
  case 0x9b:
    tmp_l10 = strtol(tmp_pc5,(char **)0x0,10);
    if ((int)tmp_u6 < tmp_l10) {
      *(uint32_t *)(param_1 + 0x3b8) =
           *(uint32_t *)(*(int *)(param_1 + 0x3c0) * 0x62c + *(int *)(param_1 + 0x3b4) + 0x628);
      return true;
    }
    return true;
  case 0x9c:
    tmp_l10 = strtol(tmp_pc5,(char **)0x0,10);
    if ((int)tmp_u6 <= tmp_l10) {
      return true;
    }
    goto LAB_000c5715;
  case 0x9d:
  case 0xa8:
    tmp_u9 = strtol(tmp_pc5,(char **)0x0,10);
    if (tmp_u6 != tmp_u9) {
      *(uint32_t *)(param_1 + 0x3b8) =
           *(uint32_t *)(*(int *)(param_1 + 0x3c0) * 0x62c + *(int *)(param_1 + 0x3b4) + 0x628);
      return true;
    }
    return true;
  case 0x9e:
    tmp_u9 = strtol(tmp_pc5,(char **)0x0,10);
    if (tmp_u6 != tmp_u9) {
      return true;
    }
    goto LAB_000c5715;
  case 0x9f:
    tmp_u6 = strtol(tmp_pc5,(char **)0x0,10);
    break;
  case 0xa0:
    tmp_i7 = rand();
    tmp_l10 = strtol(tmp_pc5,(char **)0x0,10);
    tmp_u6 = tmp_i7 % tmp_l10;
    break;
  case 0xa1:
    tmp_l10 = strtol(tmp_pc5,(char **)0x0,10);
    tmp_u6 = 1 << ((byte)tmp_l10 & 0x1f) | tmp_u6;
    break;
  case 0xa2:
    tmp_l10 = strtol(tmp_pc5,(char **)0x0,10);
    tmp_b2 = (byte)tmp_l10 & 0x1f;
    tmp_u6 = (-2 << tmp_b2 | 0xfffffffeU >> 0x20 - tmp_b2) & tmp_u6;
    break;
  case 0xa3:
    tmp_l10 = strtol(tmp_pc5,(char **)0x0,10);
    if (((int)tmp_u6 >> ((byte)tmp_l10 & 0x1f) & 1U) == 0) {
      return true;
    }
    goto LAB_000c5715;
  case 0xa4:
    tmp_l10 = strtol(tmp_pc5,(char **)0x0,10);
    if (((int)tmp_u6 >> ((byte)tmp_l10 & 0x1f) & 1U) != 0) {
      return true;
    }
LAB_000c5715:
    *(uint32_t *)(param_1 + 0x3b8) =
         *(uint32_t *)(*(int *)(param_1 + 0x3c0) * 0x62c + *(int *)(param_1 + 0x3b4) + 0x628);
    return true;
  case 0xa5:
    tmp_u9 = strtol(tmp_pc5,(char **)0x0,10);
    if (tmp_u6 != tmp_u9) {
      return true;
    }
    tmp_u8 = COM_ParseExt(&local_e0,0);
    Q_strncpyz(local_dc,tmp_u8,0x40);
    if (local_dc[0] == '\0') {
      G_Error("G_Scripting: trigger must have a name and an identifier: %s\n",param_2);
    }
    tmp_u8 = COM_ParseExt(&local_e0,0);
    Q_strncpyz(local_9c,tmp_u8,0x40);
    if (local_9c[0] == '\0') {
      G_Error("G_Scripting: trigger must have a name and an identifier: %s\n",param_2);
    }
    tmp_u8 = BG_StringHashValue(tmp_u8);
    tmp_b4 = false;
    tmp_b3 = false;
    tmp_i7 = 0;
    while (tmp_i7 = nitrox_FindByScriptNameHash(tmp_i7,tmp_u8), tmp_i7 != 0) {
      tmp_i1 = *(int *)(tmp_i7 + 0x3c4);
      G_Script_ScriptEvent(tmp_i7,"trigger",local_9c);
      tmp_b3 = tmp_b4;
      if ((tmp_i7 == param_1) && (tmp_b3 = true, *(int *)(tmp_i7 + 0x3c4) == tmp_i1)) {
        tmp_b3 = tmp_b4;
      }
      tmp_b4 = tmp_b3;
      tmp_b3 = true;
    }
    if (tmp_b4) {
      return false;
    }
    if (!tmp_b3) {
      G_Printf("G_Scripting: trigger has unknown name: %s\n",local_9c);
      return true;
    }
    return true;
  case 0xa6:
    tmp_u9 = strtol(tmp_pc5,(char **)0x0,10);
    return tmp_u6 != tmp_u9;
  default:
    G_Error("G_Scripting: cvar %s: unknown command\n",param_2);
    return true;
  }
  tmp_u8 = va("%i",tmp_u6);
  trap_Cvar_Set(local_5c,tmp_u8);
  return true;
}

uint32_t G_ScriptAction_AbortIfWarmup(int param_1)
{
  if (g_unk_00abe8ac != 0) {
    *(uint32_t *)(param_1 + 0x3b8) =
         *(uint32_t *)(*(int *)(param_1 + 0x3c0) * 0x62c + *(int *)(param_1 + 0x3b4) + 0x628);
  }
  return 1;
}

uint32_t G_ScriptAction_AbortIfNotSinglePlayer(int param_1)
{
  *(uint32_t *)(param_1 + 0x3b8) =
       *(uint32_t *)(*(int *)(param_1 + 0x3c0) * 0x62c + *(int *)(param_1 + 0x3b4) + 0x628);
  return 1;
}

uint32_t G_ScriptAction_Create(int param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  uint32_t tmp_u3;
  char *tmp_pc4;
  uint32_t local_820;
  char local_81c [1024];
  char local_41c [1032];
  uint32_t uStack_14;
  
  uStack_14 = 0xc656d;
  local_820 = param_2;
  g_unk_00abf18c = 0;
  g_unk_00abef88 = 0;
  do {
    tmp_pc4 = (char *)COM_ParseExt(&local_820,0);
    if (*tmp_pc4 == '\0') {
LAB_000c66c2:
      tmp_u3 = G_SpawnGEntityFromSpawnVars();
      trap_LinkEntity(tmp_u3);
      return 1;
    }
    strcpy(local_81c,tmp_pc4);
    tmp_pc4 = (char *)COM_ParseExt(&local_820,0);
    if (*tmp_pc4 == '\0') {
      G_Error("key \"%s\" has no value",local_81c);
      goto LAB_000c66c2;
    }
    strcpy(local_41c,tmp_pc4);
    if (GHIDRA_FIELD(g_scriptDebug, 12, 4) != 0) {
      G_Printf("%d : (%s): set [%s] [%s] [%s]\n",g_unk_00abe908,*(uint32_t *)(param_1 + 0x3ac),
               *(uint32_t *)(param_1 + 0x3ac),local_81c,local_41c);
    }
    if (g_unk_00abef88 == 0x40) {
      G_Error("G_ScriptAction_Create: MAX_SPAWN_VARS");
    }
    tmp_i1 = g_unk_00abef88;
    tmp_u3 = G_AddSpawnVarToken(local_81c);
    tmp_i2 = g_unk_00abef88;
    (&g_unk_00abef8c)[tmp_i1 * 2] = tmp_u3;
    tmp_u3 = G_AddSpawnVarToken(local_41c);
    g_unk_00abef88 = g_unk_00abef88 + 1;
    (&g_unk_00abef90)[tmp_i2 * 2] = tmp_u3;
  } while( true );
}

