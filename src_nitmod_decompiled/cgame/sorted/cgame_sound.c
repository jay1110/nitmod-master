/* Sound registration and playback — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_sound.h"

void CG_PlayCinematic(uint32_t param_1,float param_2,float param_3,float param_4,float param_5)
{
  trap_CIN_PlayCinematic
            (param_1,(int)ROUND(param_2),(int)ROUND(param_3),(int)ROUND(param_4),(int)ROUND(param_5)
             ,2);
  return;
}

void CG_PlayPMItemSound(int param_1)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = *(int *)(param_1 + 0x10c);
  if (tmp_i1 == 2) {
    if ((*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != 3) &&
       (*(int *)(cgs + g_unk_01047ac4 * 0x1a4 + 0x9494) != *(int *)(param_1 + 0x110))) {
      tmp_u2 = GHIDRA_FIELD(cgs, 132308, 4);
      if (*(int *)(param_1 + 0x110) != 1) {
        tmp_u2 = GHIDRA_FIELD(cgs, 132304, 4);
      }
      trap_S_StartSound(0,g_unk_01047ac4,3,tmp_u2);
      return;
    }
  }
  else if (tmp_i1 == 5) {
    if (*(int *)(param_1 + 0xf4) == 0) {
      if (*(int *)(param_1 + 0x110) == 1) {
        CG_SoundPlaySoundScript("axis_hq_objective_taken",0,0xffffffff,1);
      }
      else {
        CG_SoundPlaySoundScript("allies_hq_objective_taken",0,0xffffffff,1);
      }
    }
    else if (*(int *)(param_1 + 0xf4) == 1) {
      if (*(int *)(param_1 + 0x110) == 1) {
        CG_SoundPlaySoundScript("axis_hq_objective_secure",0,0xffffffff,1);
      }
      else {
        CG_SoundPlaySoundScript("allies_hq_objective_secure",0,0xffffffff,1);
      }
    }
  }
  else if (tmp_i1 == 0) {
    if (*(int *)(param_1 + 0x110) == 0) {
      if (*(int *)(param_1 + 0x108) == 1) {
        CG_SoundPlaySoundScript("axis_hq_dynamite_planted",0,0xffffffff,1);
      }
      else {
        CG_SoundPlaySoundScript("allies_hq_dynamite_planted",0,0xffffffff,1);
      }
    }
    else if (*(int *)(param_1 + 0x110) == 1) {
      if (*(int *)(param_1 + 0x108) == 1) {
        CG_SoundPlaySoundScript("axis_hq_dynamite_defused",0,0xffffffff,1);
      }
      else {
        CG_SoundPlaySoundScript("allies_hq_dynamite_defused",0,0xffffffff,1);
      }
    }
  }
  return;
}

void CG_PlayVoiceChat(int *param_1)
{
  int tmp_i1;
  
  if (GHIDRA_FIELD(cg_noVoiceChats, 12, 4) == 0) {
    trap_S_StartLocalSound(param_1[1],3);
    tmp_i1 = *param_1;
    if (tmp_i1 != -1) {
      if (tmp_i1 == *(int *)(g_unk_01047b00 + 0xcc)) {
        g_unk_01091634 = param_1[2];
        if (param_1[2] == GHIDRA_FIELD(cgs, 67984, 4)) {
          g_unk_01091638 = GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) + g_unk_010906e0;
        }
        else {
          g_unk_01091638 = g_unk_010906e0 + GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) * 2;
        }
      }
      else {
        *(int *)(cg_entities + tmp_i1 * 0xaf8 + 0x98c) = param_1[2];
        *(int *)(cg_entities + *param_1 * 0xaf8 + 0x794) = param_1[0x4f];
        *(int *)(cg_entities + *param_1 * 0xaf8 + 0x798) = param_1[0x50];
        *(int *)(cg_entities + *param_1 * 0xaf8 + 0x79c) = param_1[0x51];
        if (param_1[2] == GHIDRA_FIELD(cgs, 67984, 4)) {
          *(int *)(cg_entities + *param_1 * 0xaf8 + 0x990) =
               GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) + g_unk_010906e0;
        }
        else {
          *(int *)(cg_entities + *param_1 * 0xaf8 + 0x990) =
               g_unk_010906e0 + GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) * 2;
        }
      }
    }
  }
  if ((param_1[3] == 0) && (GHIDRA_FIELD(cg_noVoiceText, 12, 4) == 0)) {
    tmp_i1 = (int)param_1 + 0xa6;
    CG_AddToTeamChat(tmp_i1,*param_1);
    CG_Printf("[skipnotify]: %s\n",tmp_i1);
    if (GHIDRA_FIELD(cg_clientLog, 12, 4) != 0) {
      CG_WriteToLog(&g_unk_00121ff9,tmp_i1);
    }
  }
  (&g_unk_03b83fa4)[g_unk_010ab2ec * 0x52] = 0;
  return;
}

void CG_PlayBufferedVoiceChats(void)
{
  uint8_t *tmp_pu1;
  int tmp_i2;
  int tmp_i3;
  int tmp_i4;
  
  tmp_i3 = g_unk_010ab2ec;
  if ((g_unk_010ab2e4 < g_unk_010906e0) && (g_unk_010ab2ec != g_unk_010ab2e8)) {
    tmp_i4 = g_unk_010ab2ec * 0x52;
    if ((&g_unk_03b83fa4)[g_unk_010ab2ec * 0x52] != 0) {
      if (GHIDRA_FIELD(cg_noVoiceChats, 12, 4) == 0) {
        trap_S_StartLocalSound((&g_unk_03b83fa4)[g_unk_010ab2ec * 0x52],3);
        tmp_i4 = (&voiceChatBuffer)[tmp_i4];
        if (tmp_i4 != -1) {
          tmp_i2 = (&g_unk_03b83fa8)[tmp_i3 * 0x52];
          if (tmp_i4 == *(int *)(g_unk_01047b00 + 0xcc)) {
            g_unk_01091634 = tmp_i2;
            if (tmp_i2 == GHIDRA_FIELD(cgs, 67984, 4)) {
              g_unk_01091638 = GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) + g_unk_010906e0;
            }
            else {
              g_unk_01091638 = g_unk_010906e0 + GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) * 2;
            }
          }
          else {
            tmp_i4 = tmp_i4 * 0xaf8;
            *(int *)(cg_entities + tmp_i4 + 0x98c) = tmp_i2;
            *(uint32_t *)(cg_entities + tmp_i4 + 0x794) = (&g_unk_03b840dc)[tmp_i3 * 0x52];
            *(uint32_t *)(cg_entities + tmp_i4 + 0x798) = (&g_unk_03b840e0)[tmp_i3 * 0x52];
            *(uint32_t *)(cg_entities + tmp_i4 + 0x79c) = (&g_unk_03b840e4)[tmp_i3 * 0x52];
            if (tmp_i2 == GHIDRA_FIELD(cgs, 67984, 4)) {
              *(int *)(cg_entities + tmp_i4 + 0x990) = GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) + g_unk_010906e0;
            }
            else {
              *(int *)(cg_entities + tmp_i4 + 0x990) = g_unk_010906e0 + GHIDRA_FIELD(cg_voiceSpriteTime, 12, 4) * 2;
            }
          }
        }
      }
      if (((&g_unk_03b83fac)[tmp_i3 * 0x52] == 0) && (GHIDRA_FIELD(cg_noVoiceText, 12, 4) == 0)) {
        tmp_pu1 = &g_unk_03b84046 + tmp_i3 * 0x148;
        CG_AddToTeamChat(tmp_pu1,(&voiceChatBuffer)[tmp_i3 * 0x52]);
        CG_Printf("[skipnotify]: %s\n",tmp_pu1);
        if (GHIDRA_FIELD(cg_clientLog, 12, 4) != 0) {
          CG_WriteToLog(&g_unk_00121ff9,tmp_pu1);
        }
      }
      tmp_i3 = g_unk_010ab2ec + 1;
      (&g_unk_03b83fa4)[g_unk_010ab2ec * 0x52] = 0;
      if (tmp_i3 == 0x20) {
        tmp_i3 = 0;
      }
      g_unk_010ab2e4 = g_unk_010906e0 + 1000;
      g_unk_010ab2ec = tmp_i3;
    }
  }
  return;
}

void CG_SoundLoadSoundFiles(void)
{
  char tmp_c1;
  char tmp_c2;
  bool tmp_b3;
  bool tmp_b4;
  int tmp_i5;
  char *tmp_pc6;
  int tmp_i7;
  uint tmp_u8;
  __int32_t **pp_Var9;
  uint tmp_u10;
  uint32_t tmp_u11;
  char *tmp_pc12;
  uint8_t *tmp_pu13;
  uint8_t *local_2104;
  uint32_t local_20f4;
  int local_20f0;
  uint8_t *local_20ec;
  int local_20e8;
  uint32_t *local_20e4;
  int *local_20e0;
  int local_20dc;
  char *local_20d8;
  char *local_20d4;
  uint8_t **local_20d0;
  uint8_t *local_20cc;
  uint8_t *local_20c8;
  uint8_t *local_20c4;
  uint8_t local_20c0 [64];
  int local_2080;
  char local_207c;
  char acStack_207b [3];
  uint8_t *apuStack_2078 [23];
  uint8_t local_201c [8200];
  uint32_t uStack_14;
  
  uStack_14 = 0xbf549;
  local_20f4 = local_20c0;
  Com_sprintf(local_20c0,0x40,"sound/scripts/filelist.txt");
  local_20d0 = &local_20c8;
  tmp_i5 = trap_FS_FOpenFile(local_20c0,local_20d0,0);
  if (tmp_i5 < 1) {
    CG_Printf("^1WARNING: no sound files found (filelist.txt not found in sound/scripts)\n");
    return;
  }
  if (100000 < tmp_i5) {
    CG_Error("^1%s is too big, make it smaller (max = %i bytes)\n",local_20f4,100000);
  }
  trap_FS_Read(bigTextBuffer,tmp_i5,local_20c8);
  bigTextBuffer[tmp_i5] = 0;
  trap_FS_FCloseFile(local_20c8);
  local_20cc = bigTextBuffer;
  local_20e8 = 0;
  tmp_pu13 = local_201c;
  local_20ec = local_201c;
  while (tmp_pc6 = (char *)COM_ParseExt(&local_20cc,1), *tmp_pc6 != '\0') {
    local_20e8 = local_20e8 + 1;
    Com_sprintf(tmp_pu13,0x40,"%s",tmp_pc6);
    tmp_pu13 = tmp_pu13 + 0x40;
  }
  local_20dc = local_20e8 + 1;
  Com_sprintf(local_201c + local_20e8 * 0x40,0x40,"%s.sounds",0x10f69ac);
  local_20d8 = "sound/scripts/%s";
  local_20d4 = "... loading \'%s\'\n";
  local_20f0 = 0;
  do {
    tmp_pu13 = local_20f4;
    Com_sprintf(local_20f4,0x40,local_20d8,local_20ec);
    CG_Printf(local_20d4,tmp_pu13);
    tmp_i5 = 0;
    tmp_i7 = trap_FS_FOpenFile(tmp_pu13,local_20d0,0);
    if (tmp_i7 < 1) {
      if (local_20f0 != local_20e8) {
        CG_Error("^1Couldn\'t load %s",local_20f4);
      }
    }
    else {
      if (100000 < tmp_i7) {
        CG_Error("^1%s is too big, make it smaller (max = %i bytes)\n",local_20f4,100000);
      }
      memset(bigTextBuffer,0,100000);
      tmp_pu13 = local_20c8;
      trap_FS_Read(bigTextBuffer,tmp_i7,local_20c8);
      trap_FS_FCloseFile(local_20c8);
      local_20c4 = bigTextBuffer;
      local_20e0 = &local_2080;
      tmp_u8 = 0;
      do {
        *(uint32_t *)((int)local_20e0 + tmp_u8) = 0;
        *(uint32_t *)((int)apuStack_2078 + (tmp_u8 - 4)) = 0;
        tmp_u8 = tmp_u8 + 8;
      } while (tmp_u8 < 0x60);
      *(uint32_t *)((int)local_20e0 + tmp_u8) = 0;
      tmp_b4 = true;
      local_2104 = (uint8_t *)0x0;
      tmp_b3 = false;
LAB_000bf7b0:
      while (tmp_pc6 = (char *)COM_ParseExt(&local_20c4,1), *tmp_pc6 != '\0') {
        tmp_pc12 = "{";
        tmp_i5 = Q_stricmp(tmp_pc6,"{");
        if (tmp_i5 == 0) {
          if (tmp_b3) {
            tmp_pc12 = &local_207c;
            tmp_pu13 = local_20f4;
            CG_Error("^1No concluding \'}\' in sound %s, file %s\n",tmp_pc12,local_20f4);
          }
          if (tmp_b4) {
            tmp_pc12 = &local_207c;
            tmp_pu13 = local_20f4;
            CG_Error("^1\'{\' found but not expected, after %s, file %s\n",tmp_pc12,local_20f4);
          }
          tmp_i7 = numSoundScriptSounds;
          tmp_i5 = numSoundScriptSounds + 1;
          local_2104 = soundScriptSounds + numSoundScriptSounds * 0x44c;
          numSoundScriptSounds = tmp_i5;
          if (numSoundScripts == 0x2000) {
            CG_Error("^1MAX_SOUND_SCRIPT_SOUNDS exceeded.\nReduce number of sound scripts.\n",
                     tmp_pc12,tmp_pu13);
          }
          tmp_i7 = tmp_i7 * 0x44c;
          tmp_b3 = true;
          *(uint32_t *)(soundScriptSounds + tmp_i7 + 0x444) = 0;
          *(uint8_t **)(soundScriptSounds + tmp_i7 + 0x448) = apuStack_2078[0x15];
          *(uint32_t *)(soundScriptSounds + tmp_i7 + 0x440) = 0;
          apuStack_2078[0x15] = local_2104;
        }
        else {
          tmp_pc12 = "}";
          tmp_i5 = Q_stricmp(tmp_pc6,&g_unk_0010c012);
          if (tmp_i5 == 0) {
            if (!tmp_b3) {
              tmp_pc12 = &local_207c;
              tmp_pu13 = local_20f4;
              CG_Error("^1\'}\' unexpected after sound %s, file %s\n",tmp_pc12,local_20f4);
            }
            tmp_c2 = local_207c;
            if (local_207c == '\0') {
              apuStack_2078[0x16] = hashTable;
              tmp_u8 = 0;
              do {
                *(uint32_t *)(soundScripts + tmp_u8 + numSoundScripts * 100) =
                     *(uint32_t *)((int)&local_2080 + tmp_u8);
                tmp_u8 = tmp_u8 + 4;
              } while (tmp_u8 < 100);
              tmp_i5 = numSoundScripts + 1;
              hashTable = soundScripts + numSoundScripts * 100;
              numSoundScripts = tmp_i5;
              if (tmp_i5 == 0x1000) {
LAB_000bfc3f:
                CG_Error("^1MAX_SOUND_SCRIPTS exceeded.\nReduce number of sound scripts.\n",tmp_pc12,
                         tmp_pu13);
                tmp_c2 = local_207c;
                if (local_207c != '\0') goto LAB_000bf9ca;
              }
            }
            else {
              pp_Var9 = __ctype_tolower_loc();
              tmp_u8 = 0;
              tmp_i5 = 0x77;
              tmp_c1 = tmp_c2;
              do {
                tmp_c1 = (char)(*pp_Var9)[tmp_c1];
                if (tmp_c1 == '.') break;
                tmp_i7 = 0x2f;
                if (tmp_c1 != '\\') {
                  tmp_i7 = (int)tmp_c1;
                }
                tmp_u8 = tmp_u8 + tmp_i7 * tmp_i5;
                tmp_c1 = *(char *)((int)&local_20f4 + tmp_i5 + 2);
                tmp_i5 = tmp_i5 + 1;
              } while (tmp_c1 != '\0');
              local_20e4 = &hashTable;
              apuStack_2078[0x16] = (&hashTable)[tmp_u8 & 0x3ff];
              tmp_u10 = 0;
              do {
                *(uint32_t *)(soundScripts + tmp_u10 + numSoundScripts * 100) =
                     *(uint32_t *)((int)&local_2080 + tmp_u10);
                tmp_u10 = tmp_u10 + 4;
              } while (tmp_u10 < 100);
              tmp_i5 = numSoundScripts + 1;
              tmp_i7 = numSoundScripts * 100;
              numSoundScripts = tmp_i5;
              (&hashTable)[tmp_u8 & 0x3ff] = soundScripts + tmp_i7;
              if (tmp_i5 == 0x1000) goto LAB_000bfc3f;
LAB_000bf9ca:
              local_20e4 = &hashTable;
              pp_Var9 = __ctype_tolower_loc();
              tmp_u8 = 0;
              tmp_i5 = 0x77;
              do {
                tmp_c2 = (char)(*pp_Var9)[tmp_c2];
                if (tmp_c2 == '.') break;
                tmp_i7 = 0x2f;
                if (tmp_c2 != '\\') {
                  tmp_i7 = (int)tmp_c2;
                }
                tmp_u8 = tmp_u8 + tmp_i7 * tmp_i5;
                tmp_c2 = *(char *)((int)&local_20f4 + tmp_i5 + 2);
                tmp_i5 = tmp_i5 + 1;
              } while (tmp_c2 != '\0');
              tmp_i5 = local_20e4[tmp_u8 & 0x3ff];
              if (tmp_i5 != 0) {
                while (tmp_i7 = Q_stricmp(&local_207c,tmp_i5 + 4), tmp_i7 != 0) {
                  tmp_i5 = *(int *)(tmp_i5 + 0x60);
                  if (tmp_i5 == 0) goto LAB_000bfde0;
                }
                tmp_i7 = *(int *)(tmp_i5 + 0x5c);
                if (*(int *)(tmp_i5 + 0x4c) != 0) goto LAB_000bfb7e;
                for (; tmp_i7 != 0; tmp_i7 = *(int *)(tmp_i7 + 0x448)) {
                  tmp_i5 = *(int *)(tmp_i7 + 0x440);
                  if (((((0 < tmp_i5) && (*(uint32_t *)(tmp_i7 + 0x40) = 0, tmp_i5 != 1)) &&
                       (*(uint32_t *)(tmp_i7 + 0x84) = 0, tmp_i5 != 2)) &&
                      (((*(uint32_t *)(tmp_i7 + 200) = 0, tmp_i5 != 3 &&
                        (*(uint32_t *)(tmp_i7 + 0x10c) = 0, tmp_i5 != 4)) &&
                       ((*(uint32_t *)(tmp_i7 + 0x150) = 0, tmp_i5 != 5 &&
                        ((*(uint32_t *)(tmp_i7 + 0x194) = 0, tmp_i5 != 6 &&
                         (*(uint32_t *)(tmp_i7 + 0x1d8) = 0, tmp_i5 != 7)))))))) &&
                     ((*(uint32_t *)(tmp_i7 + 0x21c) = 0, tmp_i5 != 8 &&
                      (((((*(uint32_t *)(tmp_i7 + 0x260) = 0, tmp_i5 != 9 &&
                          (*(uint32_t *)(tmp_i7 + 0x2a4) = 0, tmp_i5 != 10)) &&
                         (*(uint32_t *)(tmp_i7 + 0x2e8) = 0, tmp_i5 != 0xb)) &&
                        ((*(uint32_t *)(tmp_i7 + 0x32c) = 0, tmp_i5 != 0xc &&
                         (*(uint32_t *)(tmp_i7 + 0x370) = 0, tmp_i5 != 0xd)))) &&
                       ((*(uint32_t *)(tmp_i7 + 0x3b4) = 0, tmp_i5 != 0xe &&
                        (*(uint32_t *)(tmp_i7 + 0x3f8) = 0, tmp_i5 != 0xf)))))))) {
                    *(uint32_t *)(tmp_i7 + 0x43c) = 0;
                  }
                }
              }
            }
            tmp_b3 = false;
            tmp_b4 = true;
          }
          else if (tmp_b3) {
            tmp_b3 = true;
            tmp_i5 = Q_stricmp(tmp_pc6,"channel");
            if (tmp_i5 != 0) {
              tmp_i5 = Q_stricmp(tmp_pc6,"local");
              if (tmp_i5 == 0) {
                apuStack_2078[0xf] = (uint8_t *)0x1;
              }
              else {
                tmp_i5 = Q_stricmp(tmp_pc6,"announcer");
                if (tmp_i5 == 0) {
                  apuStack_2078[0xf] = (uint8_t *)0x7;
                }
                else {
                  tmp_i5 = Q_stricmp(tmp_pc6,&g_unk_0011e2e0);
                  if (tmp_i5 == 0) {
                    apuStack_2078[0xf] = (uint8_t *)0x5;
                  }
                  else {
                    tmp_i5 = Q_stricmp(tmp_pc6,"voice");
                    if (tmp_i5 == 0) {
                      apuStack_2078[0xf] = (uint8_t *)0x3;
                    }
                    else {
                      tmp_i5 = Q_stricmp(tmp_pc6,"weapon");
                      if (tmp_i5 == 0) {
                        tmp_b3 = true;
                        apuStack_2078[0xf] = (uint8_t *)0x2;
                      }
                      else {
                        tmp_i5 = Q_stricmp(tmp_pc6,&g_unk_0011e2e5);
                        if (tmp_i5 == 0) {
                          tmp_b3 = true;
                          apuStack_2078[0xf] = (uint8_t *)0x4;
                        }
                        else {
                          tmp_i5 = Q_stricmp(tmp_pc6,&g_unk_0011e2ea);
                          if (tmp_i5 == 0) {
                            tmp_b3 = true;
                            apuStack_2078[0xf] = (uint8_t *)0x0;
                          }
                          else {
                            tmp_i5 = Q_stricmp(tmp_pc6,"global");
                            if (tmp_i5 == 0) {
                              tmp_b3 = true;
                              apuStack_2078[0x10] = (uint8_t *)0x0;
                            }
                            else {
                              tmp_i5 = Q_stricmp(tmp_pc6,"streaming");
                              if (tmp_i5 == 0) {
                                apuStack_2078[0x11] = (uint8_t *)0x1;
                                tmp_b3 = true;
                              }
                              else {
                                tmp_i5 = Q_stricmp(tmp_pc6,"looping");
                                if (tmp_i5 == 0) {
                                  tmp_b3 = true;
                                  apuStack_2078[0x12] = (uint8_t *)0x1;
                                }
                                else {
                                  tmp_b3 = true;
                                  tmp_i5 = Q_stricmp(tmp_pc6,"sound");
                                  if (tmp_i5 == 0) {
                                    if (0xf < *(int *)(local_2104 + 0x440)) {
                                      CG_Error("^1Too many sounds for soundscript %s\n");
                                    }
                                    tmp_b3 = true;
                                    tmp_u11 = COM_ParseExt(&local_20c4,1);
                                    tmp_pu13 = (uint8_t *)0x40;
                                    Q_strncpyz(local_2104 + *(int *)(local_2104 + 0x440) * 0x44,
                                               tmp_u11,0x40);
                                    *(int *)(local_2104 + 0x440) = *(int *)(local_2104 + 0x440) + 1;
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
          else {
            if (!tmp_b4) {
              CG_Error("^1\'%s\' unexpected after sound %s, file %s\n",tmp_pc6,&local_207c,local_20f4
                      );
            }
            tmp_u8 = 0;
            do {
              *(uint32_t *)((int)local_20e0 + tmp_u8) = 0;
              *(uint32_t *)((int)local_20e0 + tmp_u8 + 4) = 0;
              tmp_u8 = tmp_u8 + 8;
            } while (tmp_u8 < 0x60);
            *(uint32_t *)((int)local_20e0 + tmp_u8) = 0;
            tmp_pu13 = (uint8_t *)0x40;
            Q_strncpyz(&local_207c,tmp_pc6,0x40);
            local_2080 = numSoundScripts;
            apuStack_2078[0xf] = (uint8_t *)0x0;
            apuStack_2078[0x10] = (uint8_t *)0x1;
            tmp_b4 = false;
          }
        }
      }
      if (tmp_b3) {
        CG_Error("^1No concluding \'}\' in sound %s, file %s\n",&local_207c,local_20f4);
      }
      tmp_i5 = numSoundScripts;
      CG_Printf("...loading from file %s - total sounds now = %i\n",local_20f4,numSoundScripts);
    }
    local_20f0 = local_20f0 + 1;
    local_20ec = local_20ec + 0x40;
    if (local_20f0 == local_20dc) {
      CG_Printf("Sound files loaded = %i\n",local_20f0,tmp_i5);
      return;
    }
  } while( true );
LAB_000bfb7e:
  for (; tmp_i7 != 0; tmp_i7 = *(int *)(tmp_i7 + 0x448)) {
  }
  tmp_b3 = false;
  tmp_b4 = true;
  goto LAB_000bf7b0;
LAB_000bfde0:
  tmp_b4 = true;
  tmp_b3 = false;
  goto LAB_000bf7b0;
}

int CG_SoundScriptPrecache(char *param_1)
{
  char tmp_c1;
  int *tmp_pi2;
  __int32_t **pp_Var3;
  int tmp_i4;
  int tmp_i5;
  uint tmp_u6;
  
  if ((param_1 != (char *)0x0) && (tmp_c1 = *param_1, tmp_c1 != '\0')) {
    pp_Var3 = __ctype_tolower_loc();
    tmp_u6 = 0;
    tmp_i5 = 0x77;
    do {
      tmp_c1 = (char)(*pp_Var3)[tmp_c1];
      if (tmp_c1 == '.') break;
      tmp_i4 = 0x2f;
      if (tmp_c1 != '\\') {
        tmp_i4 = (int)tmp_c1;
      }
      tmp_c1 = param_1[tmp_i5 + -0x76];
      tmp_u6 = tmp_u6 + tmp_i4 * tmp_i5;
      tmp_i5 = tmp_i5 + 1;
    } while (tmp_c1 != '\0');
    for (tmp_pi2 = (int *)(&hashTable)[tmp_u6 & 0x3ff]; tmp_pi2 != (int *)0x0;
        tmp_pi2 = (int *)tmp_pi2[0x18]) {
      tmp_i5 = Q_stricmp(param_1,tmp_pi2 + 1);
      if (tmp_i5 == 0) {
        tmp_i5 = tmp_pi2[0x17];
        if (tmp_pi2[0x13] == 0) {
          for (; tmp_i5 != 0; tmp_i5 = *(int *)(tmp_i5 + 0x448)) {
            tmp_i4 = *(int *)(tmp_i5 + 0x440);
            if (((((0 < tmp_i4) && (*(uint32_t *)(tmp_i5 + 0x40) = 0, tmp_i4 != 1)) &&
                 (*(uint32_t *)(tmp_i5 + 0x84) = 0, tmp_i4 != 2)) &&
                (((*(uint32_t *)(tmp_i5 + 200) = 0, tmp_i4 != 3 &&
                  (*(uint32_t *)(tmp_i5 + 0x10c) = 0, tmp_i4 != 4)) &&
                 ((*(uint32_t *)(tmp_i5 + 0x150) = 0, tmp_i4 != 5 &&
                  ((*(uint32_t *)(tmp_i5 + 0x194) = 0, tmp_i4 != 6 &&
                   (*(uint32_t *)(tmp_i5 + 0x1d8) = 0, tmp_i4 != 7)))))))) &&
               ((*(uint32_t *)(tmp_i5 + 0x21c) = 0, tmp_i4 != 8 &&
                (((((*(uint32_t *)(tmp_i5 + 0x260) = 0, tmp_i4 != 9 &&
                    (*(uint32_t *)(tmp_i5 + 0x2a4) = 0, tmp_i4 != 10)) &&
                   (*(uint32_t *)(tmp_i5 + 0x2e8) = 0, tmp_i4 != 0xb)) &&
                  ((*(uint32_t *)(tmp_i5 + 0x32c) = 0, tmp_i4 != 0xc &&
                   (*(uint32_t *)(tmp_i5 + 0x370) = 0, tmp_i4 != 0xd)))) &&
                 ((*(uint32_t *)(tmp_i5 + 0x3b4) = 0, tmp_i4 != 0xe &&
                  (*(uint32_t *)(tmp_i5 + 0x3f8) = 0, tmp_i4 != 0xf)))))))) {
              *(uint32_t *)(tmp_i5 + 0x43c) = 0;
            }
          }
          tmp_i5 = *tmp_pi2;
        }
        else {
          for (; tmp_i5 != 0; tmp_i5 = *(int *)(tmp_i5 + 0x448)) {
          }
          tmp_i5 = *tmp_pi2;
        }
        return tmp_i5 + 1;
      }
    }
  }
  return 0;
}

uint32_t CG_SoundPickOldestRandomSound(int param_1,uint32_t param_2,uint32_t param_3)
{
  int *tmp_pi1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  int tmp_i5;
  int tmp_i6;
  
  tmp_i2 = *(int *)(param_1 + 0x5c);
  if (tmp_i2 == 0) {
    CG_Error("^1Unable to locate a valid sound for soundScript: %s\n",param_1 + 4);
    return 0;
  }
  tmp_i4 = 0;
  tmp_i6 = 0;
  do {
    if (tmp_i6 == 0) {
      tmp_i5 = *(int *)(tmp_i2 + 0x444);
LAB_000c0280:
      tmp_i4 = tmp_i5;
      tmp_i6 = tmp_i2;
    }
    else {
      tmp_i5 = *(int *)(tmp_i2 + 0x444);
      if (tmp_i5 < tmp_i4) goto LAB_000c0280;
    }
    tmp_i2 = *(int *)(tmp_i2 + 0x448);
    if (tmp_i2 == 0) {
      tmp_i2 = rand();
      tmp_i2 = tmp_i2 % *(int *)(tmp_i6 + 0x440);
      if (*(int *)(param_1 + 0x4c) == 0) {
        tmp_pi1 = (int *)(tmp_i6 + 0x40 + tmp_i2 * 0x44);
        tmp_i4 = *tmp_pi1;
        if (tmp_i4 == 0) {
          tmp_i4 = trap_S_RegisterSound(tmp_i2 * 0x44 + tmp_i6,0);
          *tmp_pi1 = tmp_i4;
        }
        trap_S_StartSound(param_2,param_3,*(uint32_t *)(param_1 + 0x44),tmp_i4);
        tmp_u3 = trap_S_GetSoundLength(*(uint32_t *)(tmp_i6 + tmp_i2 * 0x44 + 0x40));
        return tmp_u3;
      }
      if (*(int *)(param_1 + 0x50) == 0) {
        tmp_i4 = 0;
      }
      else {
        tmp_i4 = tmp_i6 + tmp_i2 * 0x44;
      }
      tmp_u3 = trap_S_StartStreamingSound
                        (tmp_i6 + tmp_i2 * 0x44,tmp_i4,param_3,*(uint32_t *)(param_1 + 0x44),
                         *(uint32_t *)(param_1 + 0x48));
      return tmp_u3;
    }
  } while( true );
}

uint32_t CG_SoundPlaySoundScript(char *param_1,uint32_t param_2,uint32_t param_3,int param_4)
{
  int *tmp_pi1;
  char tmp_c2;
  __int32_t **pp_Var3;
  int tmp_i4;
  int tmp_i5;
  uint32_t tmp_u6;
  uint tmp_u7;
  
  if ((param_1 != (char *)0x0) && (tmp_c2 = *param_1, tmp_c2 != '\0')) {
    pp_Var3 = __ctype_tolower_loc();
    tmp_u7 = 0;
    tmp_i4 = 0x77;
    do {
      tmp_c2 = (char)(*pp_Var3)[tmp_c2];
      if (tmp_c2 == '.') break;
      tmp_i5 = 0x2f;
      if (tmp_c2 != '\\') {
        tmp_i5 = (int)tmp_c2;
      }
      tmp_u7 = tmp_u7 + tmp_i5 * tmp_i4;
      tmp_c2 = param_1[tmp_i4 + -0x76];
      tmp_i4 = tmp_i4 + 1;
    } while (tmp_c2 != '\0');
    for (tmp_i4 = (&hashTable)[tmp_u7 & 0x3ff]; tmp_i4 != 0; tmp_i4 = *(int *)(tmp_i4 + 0x60)) {
      tmp_i5 = Q_stricmp(param_1,tmp_i4 + 4);
      if (tmp_i5 == 0) {
        if (param_4 == 0) {
          tmp_u6 = CG_SoundPickOldestRandomSound();
          return tmp_u6;
        }
        if (g_unk_010b49bc < 0x10) {
          tmp_i5 = g_unk_010b49bc + 1;
          tmp_pi1 = &g_unk_010b4978 + g_unk_010b49bc;
          g_unk_010b49bc = tmp_i5;
          *tmp_pi1 = tmp_i4;
          tmp_i4 = g_unk_010906e0;
          if (tmp_i5 == 1) {
            tmp_i5 = CG_SoundPickOldestRandomSound(g_unk_010b4978,0,0xffffffff);
            g_unk_010b49b8 = tmp_i5 + tmp_i4;
            return 1;
          }
        }
        return 1;
      }
    }
  }
  return 0;
}

void CG_SoundPlayIndexedScript(int param_1)
{
  if ((param_1 != 0) && (param_1 <= numSoundScripts)) {
    CG_SoundPickOldestRandomSound();
    return;
  }
  return;
}

void CG_SoundInit(void)
{
  int tmp_i1;
  uint32_t *tmp_pu2;
  int tmp_i3;
  
  if (numSoundScripts != 0) {
    if (0 < numSoundScriptSounds) {
      tmp_i3 = numSoundScriptSounds * 0x44c;
      tmp_pu2 = (uint32_t *)(soundScriptSounds + 0x444);
      do {
        tmp_i1 = tmp_pu2[-1];
        *tmp_pu2 = 0;
        if (((((0 < tmp_i1) && (tmp_pu2[-0x101] = 0, tmp_i1 != 1)) && (tmp_pu2[-0xf0] = 0, tmp_i1 != 2))
            && (((tmp_pu2[-0xdf] = 0, tmp_i1 != 3 && (tmp_pu2[-0xce] = 0, tmp_i1 != 4)) &&
                ((tmp_pu2[-0xbd] = 0, tmp_i1 != 5 &&
                 ((tmp_pu2[-0xac] = 0, tmp_i1 != 6 && (tmp_pu2[-0x9b] = 0, tmp_i1 != 7)))))))) &&
           ((tmp_pu2[-0x8a] = 0, tmp_i1 != 8 &&
            (((((tmp_pu2[-0x79] = 0, tmp_i1 != 9 && (tmp_pu2[-0x68] = 0, tmp_i1 != 10)) &&
               (tmp_pu2[-0x57] = 0, tmp_i1 != 0xb)) &&
              ((tmp_pu2[-0x46] = 0, tmp_i1 != 0xc && (tmp_pu2[-0x35] = 0, tmp_i1 != 0xd)))) &&
             ((tmp_pu2[-0x24] = 0, tmp_i1 != 0xe && (tmp_pu2[-0x13] = 0, tmp_i1 != 0xf)))))))) {
          tmp_pu2[-2] = 0;
        }
        tmp_pu2 = tmp_pu2 + 0x113;
      } while (tmp_pu2 != (uint32_t *)(soundScriptSounds + tmp_i3 + 0x444));
    }
    return;
  }
  CG_Printf("... initializing sound scripts\n");
  CG_SoundLoadSoundFiles();
  return;
}

void CG_PlaySwitchSound(int param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  
  tmp_i1 = param_1;
  if ((param_1 - 1U < 0x33) &&
     (tmp_i1 = *(int *)(weapAlts + param_1 * 4), *(int *)(weapAlts + param_1 * 4) == 0)) {
    tmp_i1 = param_1;
  }
  if (tmp_i1 != param_2) {
_L917:
    return;
  }
  switch(tmp_i1) {
  default:
    goto _L917;
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
    tmp_u2 = *(uint32_t *)(cg_weapons + tmp_i1 * 0x17ac + 0x176c);
    break;
  case 0x16:
  case 0x17:
    tmp_u2 = GHIDRA_FIELD(cgs, 68952, 4);
    if (*(int *)(&g_unk_0109098c + param_1 * 4) != 0) {
      tmp_u2 = *(uint32_t *)(cg_weapons + tmp_i1 * 0x17ac + 0x176c);
    }
  }
  trap_S_StartSound(0,*(uint32_t *)(g_unk_01047b00 + 0xcc),2,tmp_u2);
  return;
}

