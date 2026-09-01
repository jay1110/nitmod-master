/* Engine trap_* syscalls — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "nitmod_traps.h"

int trap_R_RegisterModel(char *param_1)
{
  char *tmp_pc1;
  byte tmp_b2;
  byte tmp_b3;
  byte tmp_b4;
  byte tmp_b5;
  byte tmp_b6;
  byte tmp_b7;
  byte tmp_b8;
  byte tmp_b9;
  byte tmp_b10;
  byte tmp_b11;
  byte tmp_b12;
  byte tmp_b13;
  uint8_t tmp_u14;
  uint8_t tmp_u15;
  int tmp_i16;
  size_t tmp_s17;
  void *__s1;
  int tmp_i18;
  void *pvVar19;
  uint16_t *tmp_pu20;
  uint tmp_u21;
  uint tmp_u22;
  char *tmp_pc23;
  uint16_t *tmp_pu24;
  uint16_t *tmp_pu25;
  int tmp_i26;
  int local_48;
  int local_44;
  int local_40;
  uint32_t local_20 [3];
  uint32_t uStack_14;
  
  tmp_i18 = mdm_model_count;
  uStack_14 = 0x48129;
  if (0 < mdm_model_count) {
    tmp_i26 = 0;
    tmp_pc23 = mdm_models;
    do {
      tmp_i16 = strcmp(tmp_pc23,param_1);
      if (tmp_i16 == 0) goto LAB_0004816d;
      tmp_i26 = tmp_i26 + 1;
      tmp_pc23 = tmp_pc23 + 0xbc;
    } while (tmp_i26 != tmp_i18);
  }
  tmp_i18 = mdx_model_count;
  if (0 < mdx_model_count) {
    tmp_i26 = 0;
    tmp_pc23 = mdx_models;
    do {
      tmp_i16 = strcmp(tmp_pc23,param_1);
      if (tmp_i16 == 0) {
LAB_0004816d:
        return tmp_i26 + 1;
      }
      tmp_i26 = tmp_i26 + 1;
      tmp_pc23 = tmp_pc23 + 0x54;
    } while (tmp_i26 != tmp_i18);
  }
  tmp_s17 = trap_FS_FOpenFile(param_1,local_20,0);
  if ((int)tmp_s17 < 1) {
    G_Error("Enemy Territory MDX: File not found: %s\n",param_1);
  }
  __s1 = malloc(tmp_s17);
  trap_FS_Read(__s1,tmp_s17,local_20[0]);
  trap_FS_FCloseFile(local_20[0]);
  tmp_i18 = memcmp(__s1,&g_unk_002400d9,4);
  if (tmp_i18 == 0) {
    local_40 = mdx_model_count + 1;
    tmp_s17 = local_40 * 0x54;
    mdx_model_count = local_40;
    mdx_models = realloc(mdx_models,tmp_s17);
    tmp_u21 = 0;
    tmp_pc23 = mdx_models + (tmp_s17 - 0x54);
    do {
      tmp_pc1 = tmp_pc23 + tmp_u21;
      tmp_pc1[0] = '\0';
      tmp_pc1[1] = '\0';
      tmp_pc1[2] = '\0';
      tmp_pc1[3] = '\0';
      tmp_pc1 = tmp_pc23 + tmp_u21 + 4;
      tmp_pc1[0] = '\0';
      tmp_pc1[1] = '\0';
      tmp_pc1[2] = '\0';
      tmp_pc1[3] = '\0';
      tmp_u21 = tmp_u21 + 8;
    } while (tmp_u21 < 0x50);
    tmp_pc1 = tmp_pc23 + tmp_u21;
    tmp_pc1[0] = '\0';
    tmp_pc1[1] = '\0';
    tmp_pc1[2] = '\0';
    tmp_pc1[3] = '\0';
    Q_strncpyz(tmp_pc23,param_1,0x40);
    tmp_pc23 = mdx_models;
    tmp_u21 = mdx_bones_max;
    tmp_b2 = *(byte *)((int)__s1 + 0x51);
    tmp_b3 = *(byte *)((int)__s1 + 0x54);
    tmp_b4 = *(byte *)((int)__s1 + 0x52);
    tmp_b5 = *(byte *)((int)__s1 + 0x50);
    tmp_b6 = *(byte *)((int)__s1 + 0x53);
    tmp_b7 = *(byte *)((int)__s1 + 0x49);
    tmp_b8 = *(byte *)((int)__s1 + 0x4a);
    tmp_b9 = *(byte *)((int)__s1 + 0x48);
    tmp_b10 = *(byte *)((int)__s1 + 0x4b);
    tmp_b11 = *(byte *)((int)__s1 + 0x55);
    tmp_b12 = *(byte *)((int)__s1 + 0x56);
    tmp_b13 = *(byte *)((int)__s1 + 0x57);
    tmp_u22 = (uint)*(byte *)((int)__s1 + 0x4e) << 0x10 | (uint)*(byte *)((int)__s1 + 0x4d) << 8 |
             (uint)*(byte *)((int)__s1 + 0x4c) | (uint)*(byte *)((int)__s1 + 0x4f) << 0x18;
    *(uint *)(mdx_models + (tmp_s17 - 4)) =
         (uint)*(byte *)((int)__s1 + 0x5b) << 0x18 |
         (uint)*(byte *)((int)__s1 + 0x58) |
         (uint)*(byte *)((int)__s1 + 0x5a) << 0x10 | (uint)*(byte *)((int)__s1 + 0x59) << 8;
    if ((int)tmp_u21 < (int)tmp_u22) {
      free(mdx_bones);
      mdx_bones_max = tmp_u22;
      mdx_bones = malloc(tmp_u22 * 0xc);
    }
    *(uint *)(tmp_pc23 + (tmp_s17 - 0x14)) = tmp_u22;
    free(*(void **)(tmp_pc23 + (tmp_s17 - 0x10)));
    tmp_i18 = *(int *)(tmp_pc23 + (tmp_s17 - 0x14));
    pvVar19 = malloc(tmp_i18 * 0x4c);
    *(void **)(tmp_pc23 + (tmp_s17 - 0x10)) = pvVar19;
    if (0 < tmp_i18) {
      tmp_i26 = 0;
      tmp_i18 = (int)__s1 +
               ((uint)tmp_b12 << 0x10 | (uint)tmp_b11 << 8 | (uint)tmp_b3 | (uint)tmp_b13 << 0x18);
      while( true ) {
        pvVar19 = (void *)((int)pvVar19 + tmp_i26 * 0x4c);
        tmp_u21 = (uint)*(byte *)(tmp_i18 + 0x43) << 0x18 |
                 (uint)*(byte *)(tmp_i18 + 0x41) << 8 | (uint)*(byte *)(tmp_i18 + 0x42) << 0x10 |
                 (uint)*(byte *)(tmp_i18 + 0x40);
        *(uint *)((int)pvVar19 + 0x40) = tmp_u21;
        if (tmp_i26 <= (int)tmp_u21) {
          G_Error("Enemy Territory MDX: parent_index >= index\n");
        }
        tmp_i26 = tmp_i26 + 1;
        Q_strncpyz(pvVar19,tmp_i18,0x40);
        *(uint *)((int)pvVar19 + 0x44) =
             (uint)*(byte *)(tmp_i18 + 0x4b) << 0x18 |
             (uint)*(byte *)(tmp_i18 + 0x49) << 8 | (uint)*(byte *)(tmp_i18 + 0x4a) << 0x10 |
             (uint)*(byte *)(tmp_i18 + 0x48);
        *(uint *)((int)pvVar19 + 0x48) =
             (uint)*(byte *)(tmp_i18 + 0x47) << 0x18 |
             (uint)*(byte *)(tmp_i18 + 0x45) << 8 | (uint)*(byte *)(tmp_i18 + 0x46) << 0x10 |
             (uint)*(byte *)(tmp_i18 + 0x44);
        if (*(int *)(tmp_pc23 + (tmp_s17 - 0x14)) <= tmp_i26) break;
        pvVar19 = *(void **)(tmp_pc23 + (tmp_s17 - 0x10));
        tmp_i18 = tmp_i18 + 0x50;
      }
    }
    *(uint *)(tmp_pc23 + (tmp_s17 - 0xc)) =
         (uint)tmp_b8 << 0x10 | (uint)tmp_b7 << 8 | (uint)tmp_b9 | (uint)tmp_b10 << 0x18;
    free(*(void **)(tmp_pc23 + (tmp_s17 - 8)));
    tmp_i18 = *(int *)(tmp_pc23 + (tmp_s17 - 0xc));
    pvVar19 = malloc((*(int *)(tmp_pc23 + (tmp_s17 - 0x14)) * 10 + 0x14) * tmp_i18);
    *(void **)(tmp_pc23 + (tmp_s17 - 8)) = pvVar19;
    if (0 < tmp_i18) {
      local_44 = 0;
      local_48 = ((uint)tmp_b4 << 0x10 | (uint)tmp_b2 << 8 | (uint)tmp_b5 | (uint)tmp_b6 << 0x18) +
                 (int)__s1;
      tmp_pu24 = (uint16_t *)((int)pvVar19 + tmp_i18 * 0x14);
      while( true ) {
        tmp_i26 = local_44 * 0x14;
        *(uint16_t **)((int)pvVar19 + tmp_i26 + 0x10) = tmp_pu24;
        tmp_i18 = *(int *)(tmp_pc23 + (tmp_s17 - 0x14));
        *(uint *)(*(int *)(tmp_pc23 + (tmp_s17 - 8)) + tmp_i26) =
             (uint)*(byte *)(local_48 + 0x27) << 0x18 |
             (uint)*(byte *)(local_48 + 0x25) << 8 | (uint)*(byte *)(local_48 + 0x26) << 0x10 |
             (uint)*(byte *)(local_48 + 0x24);
        *(uint *)(*(int *)(tmp_pc23 + (tmp_s17 - 8)) + 4 + tmp_i26) =
             (uint)*(byte *)(local_48 + 0x2b) << 0x18 |
             (uint)*(byte *)(local_48 + 0x29) << 8 | (uint)*(byte *)(local_48 + 0x2a) << 0x10 |
             (uint)*(byte *)(local_48 + 0x28);
        *(uint *)(*(int *)(tmp_pc23 + (tmp_s17 - 8)) + 8 + tmp_i26) =
             (uint)*(byte *)(local_48 + 0x2f) << 0x18 |
             (uint)*(byte *)(local_48 + 0x2d) << 8 | (uint)*(byte *)(local_48 + 0x2e) << 0x10 |
             (uint)*(byte *)(local_48 + 0x2c);
        *(uint *)(*(int *)(tmp_pc23 + (tmp_s17 - 8)) + 0xc + tmp_i26) =
             (uint)*(byte *)(local_48 + 0x33) << 0x18 |
             (uint)*(byte *)(local_48 + 0x31) << 8 | (uint)*(byte *)(local_48 + 0x32) << 0x10 |
             (uint)*(byte *)(local_48 + 0x30);
        if (0 < *(int *)(tmp_pc23 + (tmp_s17 - 0x14))) {
          tmp_i26 = 0;
          tmp_pu20 = (uint16_t *)(local_48 + 0x34);
          tmp_pu25 = tmp_pu24;
          do {
            tmp_i26 = tmp_i26 + 1;
            tmp_u14 = *(uint8_t *)(tmp_pu20 + 1);
            *tmp_pu25 = *tmp_pu20;
            tmp_u15 = *(uint8_t *)(tmp_pu20 + 2);
            tmp_pu25[1] = CONCAT11(*(uint8_t *)((int)tmp_pu20 + 3),tmp_u14);
            tmp_u14 = *(uint8_t *)(tmp_pu20 + 4);
            tmp_pu25[2] = CONCAT11(*(uint8_t *)((int)tmp_pu20 + 5),tmp_u15);
            tmp_u15 = *(uint8_t *)(tmp_pu20 + 5);
            tmp_pu25[3] = CONCAT11(*(uint8_t *)((int)tmp_pu20 + 9),tmp_u14);
            tmp_pu25[4] = CONCAT11(*(uint8_t *)((int)tmp_pu20 + 0xb),tmp_u15);
            tmp_pu20 = tmp_pu20 + 6;
            tmp_pu25 = tmp_pu25 + 5;
          } while (tmp_i26 < *(int *)(tmp_pc23 + (tmp_s17 - 0x14)));
        }
        local_44 = local_44 + 1;
        local_48 = local_48 + tmp_u22 * 0xc + 0x34;
        if (*(int *)(tmp_pc23 + (tmp_s17 - 0xc)) <= local_44) break;
        pvVar19 = *(void **)(tmp_pc23 + (tmp_s17 - 8));
        tmp_pu24 = tmp_pu24 + tmp_i18 * 5;
      }
    }
  }
  else {
    tmp_i18 = memcmp(__s1,&g_unk_002400de,4);
    if (tmp_i18 == 0) {
      local_40 = mdm_model_count + 1;
      tmp_s17 = local_40 * 0xbc;
      mdm_model_count = local_40;
      mdm_models = realloc(mdm_models,tmp_s17);
      tmp_u21 = 0;
      tmp_pc23 = mdm_models + (tmp_s17 - 0xbc);
      do {
        tmp_pc1 = tmp_pc23 + tmp_u21;
        tmp_pc1[0] = '\0';
        tmp_pc1[1] = '\0';
        tmp_pc1[2] = '\0';
        tmp_pc1[3] = '\0';
        tmp_pc1 = tmp_pc23 + tmp_u21 + 4;
        tmp_pc1[0] = '\0';
        tmp_pc1[1] = '\0';
        tmp_pc1[2] = '\0';
        tmp_pc1[3] = '\0';
        tmp_u21 = tmp_u21 + 8;
      } while (tmp_u21 < 0xb8);
      tmp_pc1 = tmp_pc23 + tmp_u21;
      tmp_pc1[0] = '\0';
      tmp_pc1[1] = '\0';
      tmp_pc1[2] = '\0';
      tmp_pc1[3] = '\0';
      Q_strncpyz(tmp_pc23,param_1,0x40);
      tmp_pc1 = mdm_models;
      tmp_u21 = (uint)*(byte *)((int)__s1 + 0x5a) << 0x10 | (uint)*(byte *)((int)__s1 + 0x59) << 8 |
               (uint)*(byte *)((int)__s1 + 0x58) | (uint)*(byte *)((int)__s1 + 0x5b) << 0x18;
      tmp_i18 = ((uint)*(byte *)((int)__s1 + 0x5c) |
                (uint)*(byte *)((int)__s1 + 0x5e) << 0x10 | (uint)*(byte *)((int)__s1 + 0x5d) << 8 |
               (uint)*(byte *)((int)__s1 + 0x5f) << 0x18) + (int)__s1;
      free(*(void **)(mdm_models + (tmp_s17 - 0x78)));
      *(uint *)(tmp_pc1 + (tmp_s17 - 0x7c)) = tmp_u21;
      pvVar19 = malloc(tmp_u21 * 0x74);
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 0x48);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 0x4c);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 0x50);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 0x54);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 0x58);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      *(void **)(tmp_pc1 + (tmp_s17 - 0x78)) = pvVar19;
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 0x5c);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 0x60);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 100);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 0x68);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 0x6c);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 0x70);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      tmp_pc23 = tmp_pc1 + (tmp_s17 - 0x74);
      tmp_pc23[0] = -1;
      tmp_pc23[1] = -1;
      tmp_pc23[2] = -1;
      tmp_pc23[3] = -1;
      if (0 < (int)tmp_u21) {
        tmp_i26 = 0;
        tmp_u22 = 0;
        while( true ) {
          Q_strncpyz((int)pvVar19 + tmp_i26,tmp_i18,0x40);
          tmp_i16 = Q_stricmp(tmp_i18,"tag_head");
          if (tmp_i16 == 0) {
            *(uint *)(tmp_pc1 + (tmp_s17 - 0x74)) = tmp_u22;
            *(uint *)(tmp_pc1 + (tmp_s17 - 0x44)) = tmp_u22;
          }
          else {
            tmp_i16 = Q_stricmp(tmp_i18,"tag_mouth");
            if (tmp_i16 == 0) {
              *(uint *)(tmp_pc1 + (tmp_s17 - 0x40)) = tmp_u22;
            }
            else {
              tmp_i16 = Q_stricmp(tmp_i18,"tag_torso");
              if (tmp_i16 == 0) {
                *(uint *)(tmp_pc1 + (tmp_s17 - 0x6c)) = tmp_u22;
                *(uint *)(tmp_pc1 + (tmp_s17 - 0x3c)) = tmp_u22;
              }
              else {
                tmp_i16 = Q_stricmp(tmp_i18,"tag_back");
                if (tmp_i16 == 0) {
                  *(uint *)(tmp_pc1 + (tmp_s17 - 0x48)) = tmp_u22;
                  *(uint *)(tmp_pc1 + (tmp_s17 - 0x38)) = tmp_u22;
                }
                else {
                  tmp_i16 = Q_stricmp(tmp_i18,"tag_chest");
                  if (tmp_i16 == 0) {
                    *(uint *)(tmp_pc1 + (tmp_s17 - 0x70)) = tmp_u22;
                    *(uint *)(tmp_pc1 + (tmp_s17 - 0x34)) = tmp_u22;
                  }
                  else {
                    tmp_i16 = Q_stricmp(tmp_i18,"tag_bright");
                    if (tmp_i16 == 0) {
                      *(uint *)(tmp_pc1 + (tmp_s17 - 0x30)) = tmp_u22;
                    }
                    else {
                      tmp_i16 = Q_stricmp(tmp_i18,"tag_armright");
                      if (tmp_i16 == 0) {
                        *(uint *)(tmp_pc1 + (tmp_s17 - 100)) = tmp_u22;
                        *(uint *)(tmp_pc1 + (tmp_s17 - 0x2c)) = tmp_u22;
                      }
                      else {
                        tmp_i16 = Q_stricmp(tmp_i18,"tag_weapon");
                        if (tmp_i16 == 0) {
                          *(uint *)(tmp_pc1 + (tmp_s17 - 0x60)) = tmp_u22;
                          *(uint *)(tmp_pc1 + (tmp_s17 - 0x28)) = tmp_u22;
                        }
                        else {
                          tmp_i16 = Q_stricmp(tmp_i18,"tag_bleft");
                          if (tmp_i16 == 0) {
                            *(uint *)(tmp_pc1 + (tmp_s17 - 0x24)) = tmp_u22;
                          }
                          else {
                            tmp_i16 = Q_stricmp(tmp_i18,"tag_armleft");
                            if (tmp_i16 == 0) {
                              *(uint *)(tmp_pc1 + (tmp_s17 - 0x68)) = tmp_u22;
                              *(uint *)(tmp_pc1 + (tmp_s17 - 0x20)) = tmp_u22;
                            }
                            else {
                              tmp_i16 = Q_stricmp(tmp_i18,"tag_weapon2");
                              if (tmp_i16 == 0) {
                                *(uint *)(tmp_pc1 + (tmp_s17 - 0x5c)) = tmp_u22;
                                *(uint *)(tmp_pc1 + (tmp_s17 - 0x1c)) = tmp_u22;
                              }
                              else {
                                tmp_i16 = Q_stricmp(tmp_i18,"tag_lbelt");
                                if (tmp_i16 == 0) {
                                  *(uint *)(tmp_pc1 + (tmp_s17 - 0x18)) = tmp_u22;
                                }
                                else {
                                  tmp_i16 = Q_stricmp(tmp_i18,"tag_ubelt");
                                  if (tmp_i16 == 0) {
                                    *(uint *)(tmp_pc1 + (tmp_s17 - 0x14)) = tmp_u22;
                                  }
                                  else {
                                    tmp_i16 = Q_stricmp(tmp_i18,"tag_legright");
                                    if (tmp_i16 == 0) {
                                      *(uint *)(tmp_pc1 + (tmp_s17 - 0x54)) = tmp_u22;
                                      *(uint *)(tmp_pc1 + (tmp_s17 - 0x10)) = tmp_u22;
                                    }
                                    else {
                                      tmp_i16 = Q_stricmp(tmp_i18,"tag_footright");
                                      if (tmp_i16 == 0) {
                                        *(uint *)(tmp_pc1 + (tmp_s17 - 0x4c)) = tmp_u22;
                                        *(uint *)(tmp_pc1 + (tmp_s17 - 0xc)) = tmp_u22;
                                      }
                                      else {
                                        tmp_i16 = Q_stricmp(tmp_i18,"tag_legleft");
                                        if (tmp_i16 == 0) {
                                          *(uint *)(tmp_pc1 + (tmp_s17 - 0x58)) = tmp_u22;
                                          *(uint *)(tmp_pc1 + (tmp_s17 - 8)) = tmp_u22;
                                        }
                                        else {
                                          tmp_i16 = Q_stricmp(tmp_i18,"tag_footleft");
                                          if (tmp_i16 == 0) {
                                            *(uint *)(tmp_pc1 + (tmp_s17 - 0x50)) = tmp_u22;
                                            *(uint *)(tmp_pc1 + (tmp_s17 - 4)) = tmp_u22;
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
                }
              }
            }
          }
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x40 + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x43) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x41) << 8 | (uint)*(byte *)(tmp_i18 + 0x42) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x40);
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x44 + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x47) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x45) << 8 | (uint)*(byte *)(tmp_i18 + 0x46) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x44);
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x48 + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x4b) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x49) << 8 | (uint)*(byte *)(tmp_i18 + 0x4a) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x48);
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x4c + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x4f) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x4d) << 8 | (uint)*(byte *)(tmp_i18 + 0x4e) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x4c);
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x50 + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x53) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x51) << 8 | (uint)*(byte *)(tmp_i18 + 0x52) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x50);
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x54 + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x57) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x55) << 8 | (uint)*(byte *)(tmp_i18 + 0x56) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x54);
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x58 + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x5b) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x59) << 8 | (uint)*(byte *)(tmp_i18 + 0x5a) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x58);
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x5c + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x5f) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x5d) << 8 | (uint)*(byte *)(tmp_i18 + 0x5e) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x5c);
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x60 + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 99) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x61) << 8 | (uint)*(byte *)(tmp_i18 + 0x62) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x60);
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 100 + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x6b) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x69) << 8 | (uint)*(byte *)(tmp_i18 + 0x6a) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x68);
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x68 + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x6f) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x6d) << 8 | (uint)*(byte *)(tmp_i18 + 0x6e) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x6c);
          tmp_u22 = tmp_u22 + 1;
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x6c + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x73) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x71) << 8 | (uint)*(byte *)(tmp_i18 + 0x72) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 0x70);
          *(uint *)(*(int *)(tmp_pc1 + (tmp_s17 - 0x78)) + 0x70 + tmp_i26) =
               (uint)*(byte *)(tmp_i18 + 0x67) << 0x18 |
               (uint)*(byte *)(tmp_i18 + 0x65) << 8 | (uint)*(byte *)(tmp_i18 + 0x66) << 0x10 |
               (uint)*(byte *)(tmp_i18 + 100);
          tmp_i26 = tmp_i26 + 0x74;
          tmp_i18 = tmp_i18 + ((uint)*(byte *)(tmp_i18 + 0x7f) << 0x18 |
                            (uint)*(byte *)(tmp_i18 + 0x7d) << 8 |
                            (uint)*(byte *)(tmp_i18 + 0x7e) << 0x10 | (uint)*(byte *)(tmp_i18 + 0x7c))
          ;
          if (tmp_u22 == tmp_u21) break;
          pvVar19 = *(void **)(tmp_pc1 + (tmp_s17 - 0x78));
        }
      }
    }
    else {
      G_Error("Enemy Territory MDX: Not a model: %s\n",param_1);
      local_40 = 0;
    }
  }
  free(__s1);
  return local_40;
}

uint32_t trap_R_LerpTagNumber(float *param_1,int *param_2,int param_3)
{
  float *pfVar1;
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
  float tmp_f12;
  float tmp_f13;
  int tmp_i14;
  int tmp_i15;
  int tmp_i16;
  float tmp_f17;
  float tmp_f18;
  float tmp_f19;
  int tmp_i20;
  int tmp_i21;
  int tmp_i22;
  short *psVar23;
  short *psVar24;
  int local_c4;
  int local_c0;
  int local_b8;
  int local_ac;
  int local_a8;
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
  uint32_t local_60;
  uint32_t local_5c;
  uint32_t local_58;
  uint32_t local_54;
  uint32_t local_50;
  uint32_t local_4c;
  uint32_t local_48;
  uint32_t local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i22 = mdx_models;
  if (*param_2 < 1) {
    tmp_i20 = 0;
  }
  else {
    tmp_i20 = (*param_2 + -1) * 0xbc;
  }
  tmp_i20 = tmp_i20 + mdm_models;
  if ((-1 < param_3) && (param_3 < *(int *)(tmp_i20 + 0x40))) {
    param_3 = param_3 * 0x74;
    tmp_i14 = *(int *)(*(int *)(tmp_i20 + 0x44) + 0x70 + param_3);
    if (param_2[0x20] < 1) {
      tmp_i15 = param_2[0x27];
      local_b8 = mdx_models;
    }
    else {
      local_b8 = mdx_models + (param_2[0x20] + -1) * 0x54;
      tmp_i15 = param_2[0x27];
    }
    if (0 < tmp_i15) {
      local_b8 = mdx_models + (tmp_i15 + -1) * 0x54;
    }
    if (param_2[0x22] < 1) {
      tmp_i16 = param_2[0x29];
      tmp_i15 = mdx_models;
    }
    else {
      tmp_i15 = mdx_models + (param_2[0x22] + -1) * 0x54;
      tmp_i16 = param_2[0x29];
    }
    tmp_i21 = tmp_i15;
    if (0 < tmp_i16) {
      tmp_i21 = mdx_models + (tmp_i16 + -1) * 0x54;
    }
    mdx_calculate_bone_lerp_constprop_6(local_b8,tmp_i15,tmp_i21,tmp_i14);
    tmp_i15 = mdx_bones;
    if (param_2[0x20] < 1) {
      tmp_i21 = param_2[0x27];
      tmp_i16 = tmp_i22;
    }
    else {
      tmp_i16 = tmp_i22 + (param_2[0x20] + -1) * 0x54;
      tmp_i21 = param_2[0x27];
    }
    local_a8 = tmp_i16;
    if (0 < tmp_i21) {
      local_a8 = tmp_i22 + (tmp_i21 + -1) * 0x54;
    }
    if (param_2[0x22] < 1) {
      tmp_i21 = param_2[0x29];
      local_c0 = tmp_i22;
    }
    else {
      local_c0 = tmp_i22 + (param_2[0x22] + -1) * 0x54;
      tmp_i21 = param_2[0x29];
    }
    local_b8 = local_c0;
    if (0 < tmp_i21) {
      local_b8 = tmp_i22 + (tmp_i21 + -1) * 0x54;
    }
    local_c4 = *(int *)(tmp_i16 + 0x44) + tmp_i14 * 0x4c;
    if (*(float *)(local_c4 + 0x48) == 0.0) {
      local_ac = param_2[0x26];
      tmp_i22 = param_2[0x1f];
      tmp_f2 = (float)param_2[0x2a];
      local_b8 = local_a8;
      local_c0 = tmp_i16;
    }
    else {
      local_ac = param_2[0x28];
      tmp_i22 = param_2[0x21];
      tmp_f2 = (float)param_2[0x2b];
      local_c4 = tmp_i14 * 0x4c + *(int *)(local_c0 + 0x44);
    }
    psVar23 = (short *)(*(int *)(tmp_i22 * 0x14 + *(int *)(local_c0 + 0x4c) + 0x10) + tmp_i14 * 10);
    psVar24 = (short *)(*(int *)(local_ac * 0x14 + *(int *)(local_b8 + 0x4c) + 0x10) + tmp_i14 * 10);
    pfVar1 = (float *)(mdx_bones + tmp_i14 * 0xc);
    tmp_f3 = *pfVar1;
    *param_1 = tmp_f3;
    tmp_f4 = pfVar1[1];
    param_1[1] = tmp_f4;
    tmp_f5 = pfVar1[2];
    param_1[2] = tmp_f5;
    if (*(float *)(local_c4 + 0x48) != 0.0) {
      pfVar1 = (float *)(tmp_i15 + *(int *)(local_c0 + 0x50) * 0xc);
      tmp_f17 = tmp_f3 - *pfVar1;
      tmp_f6 = pfVar1[1];
      tmp_f19 = tmp_f4 - tmp_f6;
      tmp_f7 = pfVar1[2];
      tmp_f18 = tmp_f5 - tmp_f7;
      tmp_f8 = (float)param_2[0x14];
      tmp_f9 = (float)param_2[0x17];
      tmp_f10 = (float)param_2[0x1a];
      tmp_f11 = (float)param_2[0x15];
      tmp_f12 = (float)param_2[0x18];
      tmp_f13 = (float)param_2[0x1b];
      *param_1 = tmp_f3 + ((tmp_f18 * (float)param_2[0x19] +
                           tmp_f19 * (float)param_2[0x16] + tmp_f17 * (float)param_2[0x13] + *pfVar1)
                         - tmp_f3) * *(float *)(local_c4 + 0x48);
      param_1[1] = ((tmp_f18 * tmp_f10 + tmp_f9 * tmp_f19 + tmp_f17 * tmp_f8 + tmp_f6) - tmp_f4) *
                   *(float *)(local_c4 + 0x48) + tmp_f4;
      param_1[2] = ((tmp_f18 * tmp_f13 + tmp_f12 * tmp_f19 + tmp_f17 * tmp_f11 + tmp_f7) - tmp_f5) *
                   *(float *)(local_c4 + 0x48) + tmp_f5;
    }
    tmp_f3 = 1.0 - tmp_f2;
    local_94 = (float)*psVar23 * 0.005493164 * tmp_f3 + (float)*psVar24 * 0.005493164 * tmp_f2;
    local_90 = (float)psVar23[1] * 0.005493164 * tmp_f3 + (float)psVar24[1] * 0.005493164 * tmp_f2;
    local_8c = tmp_f3 * (float)psVar23[2] * 0.005493164 + (float)psVar24[2] * 0.005493164 * tmp_f2;
    AnglesToAxis(&local_94,&local_40);
    local_64 = local_40;
    local_60 = local_34;
    local_5c = local_28;
    local_58 = local_3c;
    local_54 = local_30;
    local_50 = local_24;
    local_4c = local_38;
    local_48 = local_2c;
    local_44 = local_20;
    tmp_f2 = *(float *)(local_c4 + 0x48);
    local_20 = 1.0 - tmp_f2;
    local_40 = (float)param_2[0x13] * tmp_f2 + local_20;
    local_3c = (float)param_2[0x14] * tmp_f2;
    local_38 = (float)param_2[0x15] * tmp_f2;
    local_34 = (float)param_2[0x16] * tmp_f2;
    local_30 = (float)param_2[0x17] * tmp_f2 + local_20;
    local_2c = (float)param_2[0x18] * tmp_f2;
    local_28 = (float)param_2[0x19] * tmp_f2;
    local_24 = (float)param_2[0x1a] * tmp_f2;
    local_20 = tmp_f2 * (float)param_2[0x1b] + local_20;
    MatrixMultiply(&local_64,&local_40,&local_88);
    tmp_i22 = *(int *)(tmp_i20 + 0x44) + param_3;
    tmp_f2 = *(float *)(tmp_i22 + 100);
    tmp_f3 = *(float *)(tmp_i22 + 0x68);
    tmp_f4 = *(float *)(tmp_i22 + 0x6c);
    *param_1 = tmp_f4 * local_70 + tmp_f3 * local_7c + tmp_f2 * local_88 + *param_1;
    param_1[1] = local_6c * tmp_f4 + local_78 * tmp_f3 + local_84 * tmp_f2 + param_1[1];
    param_1[2] = local_68 * tmp_f4 + local_74 * tmp_f3 + local_80 * tmp_f2 + param_1[2];
    MatrixMultiply(*(int *)(tmp_i20 + 0x44) + param_3 + 0x40,&local_88,param_1 + 3);
    return 0;
  }
  return 0xffffffff;
}

int trap_R_LookupTag(int *param_1,uint32_t param_2)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (*param_1 < 1) {
    tmp_i1 = 0;
  }
  else {
    tmp_i1 = (*param_1 + -1) * 0xbc;
  }
  tmp_i1 = mdm_models + tmp_i1;
  tmp_i3 = 0;
  if (0 < *(int *)(tmp_i1 + 0x40)) {
    do {
      tmp_i2 = Q_stricmp(tmp_i3 * 0x74 + *(int *)(tmp_i1 + 0x44),param_2);
      if (tmp_i2 == 0) {
        return tmp_i3;
      }
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 < *(int *)(tmp_i1 + 0x40));
  }
  return -1;
}

void trap_R_LerpTag(uint32_t param_1,int *param_2,uint32_t param_3,int param_4)
{
  int tmp_i1;
  int tmp_i2;
  int tmp_i3;
  
  if (param_4 != 0) {
    G_Error("Enemy Territory MDX: Huh?  What to do, what to do... (non-zero startIndex)\n");
  }
  if (*param_2 < 1) {
    tmp_i1 = 0;
  }
  else {
    tmp_i1 = (*param_2 + -1) * 0xbc;
  }
  tmp_i1 = mdm_models + tmp_i1;
  tmp_i3 = 0;
  if (0 < *(int *)(tmp_i1 + 0x40)) {
    do {
      tmp_i2 = Q_stricmp(tmp_i3 * 0x74 + *(int *)(tmp_i1 + 0x44),param_3);
      if (tmp_i2 == 0) break;
      tmp_i3 = tmp_i3 + 1;
    } while (tmp_i3 < *(int *)(tmp_i1 + 0x40));
  }
  trap_R_LerpTagNumber();
  return;
}

void trap_Printf(uint32_t param_1)
{
  (*syscall)(0,param_1,0xfffffac7);
  return;
}

void trap_Error(uint32_t param_1)
{
  (*syscall)(1,param_1,0xfffffac7);
  return;
}

void trap_Milliseconds(void)
{
  (*syscall)(2,0xfffffac7);
  return;
}

void trap_Argc(void)
{
  (*syscall)(9,0xfffffac7);
  return;
}

void trap_Argv(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(10,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_FS_FOpenFile(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0xb,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_FS_Read(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0xc,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_FS_Write(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0xd,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_FS_Rename(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0xe,param_1,param_2,0xfffffac7);
  return;
}

void trap_FS_FCloseFile(uint32_t param_1)
{
  (*syscall)(0xf,param_1,0xfffffac7);
  return;
}

void trap_FS_GetFileList(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        )

{
  (*syscall)(0x28,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_SendConsoleCommand(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x10,param_1,param_2,0xfffffac7);
  return;
}

void trap_Cvar_Update(uint32_t param_1)
{
  (*syscall)(4,param_1,0xfffffac7);
  return;
}

void trap_Cvar_Set(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(5,param_1,param_2,0xfffffac7);
  return;
}

void trap_Cvar_VariableIntegerValue(uint32_t param_1)
{
  (*syscall)(6,param_1,0xfffffac7);
  return;
}

void trap_Cvar_VariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(7,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_Cvar_LatchedVariableStringBuffer(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(8,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_LocateGameData(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4
                        ,uint32_t param_5)

{
  (*syscall)(0x11,param_1,param_2,param_3,param_4,param_5,0xfffffac7);
  return;
}

void trap_DropClient(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x12,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_SendServerCommand(int param_1,char *param_2)
{
  size_t tmp_s1;
  int tmp_i2;
  int tmp_i3;
  
  tmp_s1 = strlen(param_2);
  if (tmp_s1 < 0x3ff) {
    if (param_1 == -1) {
      if (0 < g_unk_00abe938) {
        tmp_i3 = 0;
        tmp_i2 = g_unk_00abe938;
        do {
          if ((g_entities[(&g_unk_00abe944)[tmp_i3] * 0x600 + 0x128] & 8) == 0) {
            (*syscall)(0x13,((&g_unk_00abe944)[tmp_i3] * 0x600 >> 9) * -0x55555555,param_2,0xfffffac7);
            tmp_i2 = g_unk_00abe938;
          }
          tmp_i3 = tmp_i3 + 1;
        } while (tmp_i3 < tmp_i2);
      }
    }
    else {
      (*syscall)(0x13,param_1,param_2,0xfffffac7);
    }
    return;
  }
  G_LogPrintf("N!tmod: trap_SendServerCommand( %d, ... ) length exceeds 1022.\n",param_1);
  G_LogPrintf("text [%.950s]... truncated\n",param_2);
  return;
}

void trap_SetConfigstring(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x14,param_1,param_2,0xfffffac7);
  return;
}

void trap_GetConfigstring(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x15,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_GetUserinfo(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x16,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_SetUserinfo(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x17,param_1,param_2,0xfffffac7);
  return;
}

void trap_GetServerinfo(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x18,param_1,param_2,0xfffffac7);
  return;
}

void trap_SetBrushModel(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x19,param_1,param_2,0xfffffac7);
  return;
}

void trap_Trace(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x1a,param_1,param_2,param_3,param_4,param_5,param_6,param_7,0xfffffac7);
  return;
}

void trap_TraceNoEnts(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
                     uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x1a,param_1,param_2,param_3,param_4,param_5,0xfffffffe,param_7,0xfffffac7);
  return;
}

void trap_TraceCapsule(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
                      uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x2d,param_1,param_2,param_3,param_4,param_5,param_6,param_7,0xfffffac7);
  return;
}

void trap_TraceCapsuleNoEnts
               (uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4,
               uint32_t param_5,uint32_t param_6,uint32_t param_7)

{
  (*syscall)(0x2d,param_1,param_2,param_3,param_4,param_5,0xfffffffe,param_7,0xfffffac7);
  return;
}

void trap_PointContents(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x1b,param_1,param_2,0xfffffac7);
  return;
}

void trap_InPVS(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x1c,param_1,param_2,0xfffffac7);
  return;
}

void trap_AdjustAreaPortalState(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x1e,param_1,param_2,0xfffffac7);
  return;
}

void trap_LinkEntity(uint32_t param_1)
{
  (*syscall)(0x20,param_1,0xfffffac7);
  return;
}

void trap_UnlinkEntity(uint32_t param_1)
{
  (*syscall)(0x21,param_1,0xfffffac7);
  return;
}

void trap_EntitiesInBox(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  (*syscall)(0x22,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_EntityContactCapsule(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x2e,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_BotAllocateClient(uint32_t param_1)
{
  (*syscall)(0x24,param_1,0xfffffac7);
  return;
}

void trap_RegisterSound(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x31,param_1,param_2,0xfffffac7);
  return;
}

void trap_GetUsercmd(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x26,param_1,param_2,0xfffffac7);
  return;
}

void trap_GetEntityToken(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x27,param_1,param_2,0xfffffac7);
  return;
}

void trap_DebugPolygonCreate(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x29,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_RealTime(uint32_t param_1)
{
  (*syscall)(0x2b,param_1,0xfffffac7);
  return;
}

void trap_SnapVector(uint32_t param_1)
{
  (*syscall)(0x2c,param_1,0xfffffac7);
  return;
}

void trap_GetTag(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4)
{
  (*syscall)(0x2f,param_1,param_2,param_3,param_4,0xfffffac7);
  return;
}

void trap_LoadTag(uint32_t param_1)
{
  (*syscall)(0x30,param_1,0xfffffac7);
  return;
}

void trap_PC_LoadSource(uint32_t param_1)
{
  (*syscall)(0x243,param_1,0xfffffac7);
  return;
}

void trap_PC_FreeSource(uint32_t param_1)
{
  (*syscall)(0x244,param_1,0xfffffac7);
  return;
}

void trap_PC_ReadToken(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x245,param_1,param_2,0xfffffac7);
  return;
}

void trap_PC_SourceFileAndLine(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x246,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_BotGetServerCommand(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0xd2,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_BotUserCommand(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0xd3,param_1,param_2,0xfffffac7);
  return;
}

void trap_EA_Command(uint32_t param_1,uint32_t param_2)
{
  (*syscall)(0x197,param_1,param_2,0xfffffac7);
  return;
}

void trap_PbStat(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x248,param_1,param_2,param_3,0xfffffac7);
  return;
}

void trap_SendMessage(uint32_t param_1,uint32_t param_2,uint32_t param_3)
{
  (*syscall)(0x249,param_1,param_2,param_3,0xfffffac7);
  return;
}

