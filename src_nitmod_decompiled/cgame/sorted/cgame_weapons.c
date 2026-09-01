/* Client weapon presentation and selection — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_weapons.h"

uint32_t CG_RegisterWeaponFromWeaponFile(int param_1,int param_2)
{
  uint tmp_u1;
  int tmp_i2;
  uint32_t tmp_u3;
  uint local_8d0;
  uint8_t local_8cc [64];
  uint8_t local_88c [64];
  uint8_t local_84c [16];
  char local_83c [1032];
  uint8_t local_434 [16];
  char local_424 [1040];
  uint32_t uStack_14;
  
  if (param_1 == 0) {
    return 0;
  }
  uStack_14 = 0xd114b;
  tmp_i2 = trap_PC_ReadToken(param_1,local_84c);
  if (tmp_i2 != 0) {
    tmp_i2 = Q_stricmp(local_83c,"weaponDef");
    if (tmp_i2 == 0) {
      tmp_i2 = trap_PC_ReadToken(param_1,local_84c);
      if ((tmp_i2 == 0) || (tmp_i2 = Q_stricmp(local_83c,"{"), tmp_i2 != 0)) {
        tmp_u3 = CG_RW_ParseError(param_1,"expected \'{\'");
        return tmp_u3;
      }
LAB_000d1200:
      do {
        tmp_i2 = trap_PC_ReadToken(param_1,local_84c);
        if ((tmp_i2 == 0) || (local_83c[0] == '}')) {
          trap_PC_FreeSource(param_1);
          return 1;
        }
        tmp_i2 = Q_stricmp(local_83c,"client");
        if (tmp_i2 != 0) {
          tmp_i2 = Q_stricmp(local_83c,&g_unk_00110c1f);
          if (tmp_i2 == 0) {
            tmp_i2 = trap_PC_ReadToken(param_1,local_434);
            if (tmp_i2 == 0) {
              return 0;
            }
            tmp_i2 = Q_stricmp(local_424,"{");
            if (tmp_i2 != 0) {
              return 0;
            }
            do {
              tmp_i2 = trap_PC_ReadToken(param_1,local_434);
              if (tmp_i2 == 0) break;
            } while (local_424[0] != '}');
          }
          else {
            tmp_i2 = Q_stricmp(local_83c,"both_altweap");
            if (tmp_i2 != 0) {
              tmp_u3 = CG_RW_ParseError(param_1,"unknown token \'%s\'",local_83c);
              return tmp_u3;
            }
            tmp_i2 = trap_PC_ReadToken(param_1,local_434);
            if (tmp_i2 == 0) {
              return 0;
            }
            tmp_i2 = Q_stricmp(local_424,"{");
            if (tmp_i2 != 0) {
              return 0;
            }
            do {
              tmp_i2 = trap_PC_ReadToken(param_1,local_434);
              if (tmp_i2 == 0) break;
            } while (local_424[0] != '}');
          }
          goto LAB_000d1200;
        }
        tmp_i2 = trap_PC_ReadToken(param_1,local_434);
        if (tmp_i2 == 0) {
LAB_000d1460:
          tmp_i2 = CG_RW_ParseError(param_1,"expected \'{\'");
        }
        else {
          tmp_i2 = Q_stricmp(local_424,"{");
          if (tmp_i2 != 0) goto LAB_000d1460;
LAB_000d1290:
          while( true ) {
            tmp_i2 = trap_PC_ReadToken(param_1,local_434);
            while( true ) {
              if ((tmp_i2 == 0) || (local_424[0] == '}')) goto LAB_000d1200;
              tmp_i2 = Q_stricmp(local_424,"standModel");
              if (tmp_i2 != 0) break;
              tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
              if (tmp_i2 == 0) {
                tmp_i2 = CG_RW_ParseError(param_1,"expected standModel filename");
                goto LAB_000d1472;
              }
              tmp_u3 = trap_R_RegisterModel(local_8cc);
              *(uint32_t *)(param_2 + 0x5b8) = tmp_u3;
              tmp_i2 = trap_PC_ReadToken(param_1,local_434);
            }
            tmp_i2 = Q_stricmp(local_424,"droppedAnglesHack");
            if (tmp_i2 != 0) break;
            *(uint32_t *)(param_2 + 0x5bc) = 1;
          }
          tmp_i2 = Q_stricmp(local_424,"pickupModel");
          if (tmp_i2 == 0) {
            tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
            if (tmp_i2 == 0) {
LAB_000d1705:
              tmp_i2 = CG_RW_ParseError(param_1,"expected pickupModel filename");
              goto LAB_000d1472;
            }
            tmp_u3 = trap_R_RegisterModel(local_8cc);
            *(uint32_t *)(param_2 + 0x5f0) = tmp_u3;
            goto LAB_000d1290;
          }
          tmp_i2 = Q_stricmp(local_424,"axisPickupModel");
          if (tmp_i2 == 0) {
            tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
            if (tmp_i2 == 0) goto LAB_000d1705;
            tmp_u3 = trap_R_RegisterModel(local_8cc);
            *(uint32_t *)(param_2 + 0x5f4) = tmp_u3;
            goto LAB_000d1290;
          }
          tmp_i2 = Q_stricmp(local_424,"alliedPickupModel");
          if (tmp_i2 == 0) {
            tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
            if (tmp_i2 == 0) goto LAB_000d1705;
            tmp_u3 = trap_R_RegisterModel(local_8cc);
            *(uint32_t *)(param_2 + 0x5f8) = tmp_u3;
            goto LAB_000d1290;
          }
          tmp_i2 = Q_stricmp(local_424,"pickupSkin");
          if (tmp_i2 == 0) {
            tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
            if (tmp_i2 == 0) {
LAB_000d1833:
              tmp_i2 = CG_RW_ParseError(param_1,"expected pickupSkin filename");
              goto LAB_000d1472;
            }
            tmp_u3 = trap_R_RegisterSkin(local_8cc);
            *(uint32_t *)(param_2 + 0x5fc) = tmp_u3;
            goto LAB_000d1290;
          }
          tmp_i2 = Q_stricmp(local_424,"axisPickupSkin");
          if (tmp_i2 == 0) {
            tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
            if (tmp_i2 == 0) goto LAB_000d1833;
            tmp_u3 = trap_R_RegisterSkin(local_8cc);
            *(uint32_t *)(param_2 + 0x600) = tmp_u3;
            goto LAB_000d1290;
          }
          tmp_i2 = Q_stricmp(local_424,"alliedPickupSkin");
          if (tmp_i2 == 0) {
            tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
            if (tmp_i2 == 0) goto LAB_000d1833;
            tmp_u3 = trap_R_RegisterSkin(local_8cc);
            *(uint32_t *)(param_2 + 0x604) = tmp_u3;
            goto LAB_000d1290;
          }
          tmp_i2 = Q_stricmp(local_424,"pickupSound");
          if (tmp_i2 != 0) {
            tmp_i2 = Q_stricmp(local_424,"weaponConfig");
            if (tmp_i2 == 0) {
              tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
              if (tmp_i2 == 0) {
                tmp_i2 = CG_RW_ParseError(param_1,"expected weaponConfig filename");
                goto LAB_000d1472;
              }
              CG_ParseWeaponConfig();
            }
            else {
              tmp_i2 = Q_stricmp(local_424,"handsModel");
              if (tmp_i2 == 0) {
                tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                if (tmp_i2 == 0) {
                  tmp_i2 = CG_RW_ParseError(param_1,"expected handsModel filename");
                  goto LAB_000d1472;
                }
                tmp_u3 = trap_R_RegisterModel(local_8cc);
                *(uint32_t *)(param_2 + 0x5b4) = tmp_u3;
              }
              else {
                tmp_i2 = Q_stricmp(local_424,"flashDlightColor");
                if (tmp_i2 == 0) {
                  tmp_i2 = PC_Vec_Parse(param_1,param_2 + 0x16ac);
                  if (tmp_i2 == 0) {
                    tmp_i2 = CG_RW_ParseError(param_1,"expected flashDlightColor as r g b");
                    goto LAB_000d1472;
                  }
                  goto LAB_000d1290;
                }
                tmp_i2 = Q_stricmp(local_424,"flashSound");
                if (tmp_i2 == 0) {
                  tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                  if (tmp_i2 == 0) {
                    tmp_i2 = CG_RW_ParseError(param_1,"expected flashSound filename");
                    goto LAB_000d1472;
                  }
                  tmp_i2 = 0;
                  do {
                    if (*(int *)(param_2 + 0x16b8 + tmp_i2 * 4) == 0) {
                      tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                      *(uint32_t *)(param_2 + 0x16b8 + tmp_i2 * 4) = tmp_u3;
                      goto LAB_000d1290;
                    }
                    tmp_i2 = tmp_i2 + 1;
                  } while (tmp_i2 != 4);
                  CG_Printf("^3WARNING: only up to 4 flashSounds supported per weapon\n");
                }
                else {
                  tmp_i2 = Q_stricmp(local_424,"flashEchoSound");
                  if (tmp_i2 == 0) {
                    tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                    if (tmp_i2 == 0) {
                      tmp_i2 = CG_RW_ParseError(param_1,"expected flashEchoSound filename");
                      goto LAB_000d1472;
                    }
                    tmp_i2 = 0;
                    do {
                      if (*(int *)(param_2 + 0x16c8 + tmp_i2 * 4) == 0) {
                        tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                        *(uint32_t *)(param_2 + 0x16c8 + tmp_i2 * 4) = tmp_u3;
                        goto LAB_000d1290;
                      }
                      tmp_i2 = tmp_i2 + 1;
                    } while (tmp_i2 != 4);
                    CG_Printf("^3WARNING: only up to 4 flashEchoSounds supported per weapon\n");
                  }
                  else {
                    tmp_i2 = Q_stricmp(local_424,"lastShotSound");
                    if (tmp_i2 == 0) {
                      tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                      if (tmp_i2 == 0) {
                        tmp_i2 = CG_RW_ParseError(param_1,"expected lastShotSound filename");
                        goto LAB_000d1472;
                      }
                      tmp_i2 = 0;
                      do {
                        if (*(int *)(param_2 + 0x16d8 + tmp_i2 * 4) == 0) {
                          tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                          *(uint32_t *)(param_2 + 0x16d8 + tmp_i2 * 4) = tmp_u3;
                          goto LAB_000d1290;
                        }
                        tmp_i2 = tmp_i2 + 1;
                      } while (tmp_i2 != 4);
                      CG_Printf("^3WARNING: only up to 4 lastShotSound supported per weapon\n");
                    }
                    else {
                      tmp_i2 = Q_stricmp(local_424,"deathBySound");
                      if (tmp_i2 == 0) {
                        tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                        if (tmp_i2 == 0) {
                          tmp_i2 = CG_RW_ParseError(param_1,"expected deathBySound filename");
                          goto LAB_000d1472;
                        }
                        tmp_i2 = 0;
                        do {
                          if (*(int *)(param_2 + 0x16e8 + tmp_i2 * 4) == 0) {
                            tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                            *(uint32_t *)(param_2 + 0x16e8 + tmp_i2 * 4) = tmp_u3;
                            *(int *)(param_2 + 0x1708) = tmp_i2 + 1;
                            goto LAB_000d1290;
                          }
                          tmp_i2 = tmp_i2 + 1;
                        } while (tmp_i2 != 4);
                        CG_Printf("^3WARNING: only up to 4 deathBySound supported per weapon\n");
                      }
                      else {
                        tmp_i2 = Q_stricmp(local_424,"deathBySoundFar");
                        if (tmp_i2 == 0) {
                          tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                          if (tmp_i2 == 0) {
                            tmp_i2 = CG_RW_ParseError(param_1,"expected deathBySoundFar filename");
                            goto LAB_000d1472;
                          }
                          tmp_i2 = 0;
                          do {
                            if (*(int *)(param_2 + 0x16f8 + tmp_i2 * 4) == 0) {
                              tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                              *(uint32_t *)(param_2 + 0x16f8 + tmp_i2 * 4) = tmp_u3;
                              *(int *)(param_2 + 0x170c) = tmp_i2 + 1;
                              goto LAB_000d1290;
                            }
                            tmp_i2 = tmp_i2 + 1;
                          } while (tmp_i2 != 4);
                          CG_Printf("^3WARNING: only up to 4 deathBySoundFar supported per weapon\n"
                                   );
                        }
                        else {
                          tmp_i2 = Q_stricmp(local_424,"readySound");
                          if (tmp_i2 == 0) {
                            tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                            if (tmp_i2 == 0) {
                              tmp_i2 = CG_RW_ParseError(param_1,"expected readySound filename");
                              goto LAB_000d1472;
                            }
                            tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                            *(uint32_t *)(param_2 + 0x1750) = tmp_u3;
                          }
                          else {
                            tmp_i2 = Q_stricmp(local_424,"firingSound");
                            if (tmp_i2 == 0) {
                              tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                              if (tmp_i2 == 0) {
                                tmp_i2 = CG_RW_ParseError(param_1,"expected firingSound filename");
                                goto LAB_000d1472;
                              }
                              tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                              *(uint32_t *)(param_2 + 0x1754) = tmp_u3;
                            }
                            else {
                              tmp_i2 = Q_stricmp(local_424,"overheatSound");
                              if (tmp_i2 == 0) {
                                tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                                if (tmp_i2 == 0) {
                                  tmp_i2 = CG_RW_ParseError(param_1,"expected overheatSound filename"
                                                          );
                                  goto LAB_000d1472;
                                }
                                tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                                *(uint32_t *)(param_2 + 0x1758) = tmp_u3;
                              }
                              else {
                                tmp_i2 = Q_stricmp(local_424,"reloadSound");
                                if (tmp_i2 == 0) {
                                  tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                                  if (tmp_i2 == 0) {
                                    tmp_i2 = CG_RW_ParseError(param_1,"expected reloadSound filename"
                                                            );
                                    goto LAB_000d1472;
                                  }
                                  tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                                  *(uint32_t *)(param_2 + 0x175c) = tmp_u3;
                                }
                                else {
                                  tmp_i2 = Q_stricmp(local_424,"reloadFastSound");
                                  if (tmp_i2 == 0) {
                                    tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                                    if (tmp_i2 == 0) {
                                      tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected reloadFastSound filename");
                                      goto LAB_000d1472;
                                    }
                                    tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                                    *(uint32_t *)(param_2 + 0x1760) = tmp_u3;
                                  }
                                  else {
                                    tmp_i2 = Q_stricmp(local_424,"spinupSound");
                                    if (tmp_i2 == 0) {
                                      tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                                      if (tmp_i2 == 0) {
                                        tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected spinupSound filename");
                                        goto LAB_000d1472;
                                      }
                                      tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                                      *(uint32_t *)(param_2 + 0x1764) = tmp_u3;
                                    }
                                    else {
                                      tmp_i2 = Q_stricmp(local_424,"spindownSound");
                                      if (tmp_i2 == 0) {
                                        tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                                        if (tmp_i2 == 0) {
                                          tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected spindownSound filename");
                                          goto LAB_000d1472;
                                        }
                                        tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                                        *(uint32_t *)(param_2 + 0x1768) = tmp_u3;
                                      }
                                      else {
                                        tmp_i2 = Q_stricmp(local_424,"switchSound");
                                        if (tmp_i2 == 0) {
                                          tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                                          if (tmp_i2 == 0) {
                                            tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected switchSound filename");
                                            goto LAB_000d1472;
                                          }
                                          tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                                          *(uint32_t *)(param_2 + 0x176c) = tmp_u3;
                                        }
                                        else {
                                          tmp_i2 = Q_stricmp(local_424,"weaponIcon");
                                          if (tmp_i2 == 0) {
                                            tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                                            if (tmp_i2 == 0) {
                                              tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected weaponIcon filename");
                                              goto LAB_000d1472;
                                            }
                                            tmp_u3 = trap_R_RegisterShader(local_8cc);
                                            *(uint32_t *)(param_2 + 0x1710) = tmp_u3;
                                          }
                                          else {
                                            tmp_i2 = Q_stricmp(local_424,"weaponIconScale");
                                            if (tmp_i2 == 0) {
                                              tmp_i2 = PC_Int_Parse(param_1,param_2 + 0x1798);
                                              if (tmp_i2 == 0) {
                                                tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected weapon Icon Scale");
                                                goto LAB_000d1472;
                                              }
                                              goto LAB_000d1290;
                                            }
                                            tmp_i2 = Q_stricmp(local_424,"weaponSelectedIcon");
                                            if (tmp_i2 != 0) {
                                              tmp_i2 = Q_stricmp(local_424,"missileModel");
                                              if (tmp_i2 == 0) {
                                                tmp_i2 = PC_String_ParseNoAlloc
                                                                  (param_1,local_8cc,0x40);
                                                if (tmp_i2 != 0) {
                                                  tmp_u3 = trap_R_RegisterModel(local_8cc);
                                                  *(uint32_t *)(param_2 + 0x171c) = tmp_u3;
                                                  goto LAB_000d1290;
                                                }
                                              }
                                              else {
                                                tmp_i2 = Q_stricmp(local_424,"AxisMissileModel");
                                                if (tmp_i2 == 0) {
                                                  tmp_i2 = PC_String_ParseNoAlloc
                                                                    (param_1,local_8cc,0x40);
                                                  if (tmp_i2 != 0) {
                                                    tmp_u3 = trap_R_RegisterModel(local_8cc);
                                                    *(uint32_t *)(param_2 + 0x1794) = 1;
                                                    *(uint32_t *)(param_2 + 0x1720) = tmp_u3;
                                                    goto LAB_000d1290;
                                                  }
                                                }
                                                else {
                                                  tmp_i2 = Q_stricmp(local_424,"AlliedMissileModel");
                                                  if (tmp_i2 != 0) {
                                                    tmp_i2 = Q_stricmp(local_424,"missileAlliedSkin")
                                                    ;
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_String_ParseNoAlloc
                                                                        (param_1,local_8cc,0x40);
                                                      if (tmp_i2 != 0) {
                                                        tmp_u3 = trap_R_RegisterSkin(local_8cc);
                                                        *(uint32_t *)(param_2 + 0x1728) = tmp_u3;
                                                        goto LAB_000d1290;
                                                      }
                                                    }
                                                    else {
                                                      tmp_i2 = Q_stricmp(local_424,"missileAxisSkin")
                                                      ;
                                                      if (tmp_i2 != 0) {
                                                        tmp_i2 = Q_stricmp(local_424,"missileSound");
                                                        if (tmp_i2 == 0) {
                                                          tmp_i2 = PC_String_ParseNoAlloc
                                                                            (param_1,local_8cc,0x40)
                                                          ;
                                                          if (tmp_i2 == 0) {
                                                            tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected missileSound filename");
                                                  goto LAB_000d1472;
                                                  }
                                                  tmp_u3 = trap_S_RegisterSound(local_8cc,0);
                                                  *(uint32_t *)(param_2 + 0x1730) = tmp_u3;
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"missileTrailFunc");
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_String_ParseNoAlloc
                                                                        (param_1,local_8cc,0x40);
                                                      if (tmp_i2 == 0) {
                                                        tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected missileTrailFunc");
                                                  goto LAB_000d1472;
                                                  }
                                                  tmp_i2 = Q_stricmp(local_8cc,"GrenadeTrail");
                                                  if (tmp_i2 == 0) {
                                                    *(void **)(param_2 + 0x1734) = CG_GrenadeTrail;
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_8cc,"RocketTrail");
                                                    if (tmp_i2 == 0) {
                                                      *(void **)(param_2 + 0x1734) = CG_RocketTrail;
                                                    }
                                                    else {
                                                      tmp_i2 = Q_stricmp(local_8cc,"PyroSmokeTrail");
                                                      if (tmp_i2 == 0) {
                                                        *(void **)(param_2 + 0x1734) =
                                                             CG_PyroSmokeTrail;
                                                      }
                                                      else {
                                                        tmp_i2 = Q_stricmp(local_8cc,"DynamiteTrail")
                                                        ;
                                                        if (tmp_i2 == 0) {
                                                          *(void **)(param_2 + 0x1734) =
                                                               CG_DynamiteTrail;
                                                        }
                                                      }
                                                    }
                                                  }
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"missileDlight");
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_Float_Parse(param_1,param_2 + 
                                                  0x1738);
                                                  if (tmp_i2 == 0) {
                                                    tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected missileDlight value");
                                                  goto LAB_000d1472;
                                                  }
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"missileDlightColor"
                                                                     );
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_Vec_Parse(param_1,param_2 + 0x173c)
                                                      ;
                                                      if (tmp_i2 == 0) {
                                                        tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected missileDlightColor as r g b");
                                                  goto LAB_000d1472;
                                                  }
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"ejectBrassFunc");
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_String_ParseNoAlloc
                                                                        (param_1,local_8cc,0x40);
                                                      if (tmp_i2 == 0) {
                                                        tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected ejectBrassFunc");
                                                  goto LAB_000d1472;
                                                  }
                                                  tmp_i2 = Q_stricmp(local_8cc,"MachineGunEjectBrass"
                                                                   );
                                                  if (tmp_i2 == 0) {
                                                    *(void **)(param_2 + 0x174c) =
                                                         CG_MachineGunEjectBrass;
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_8cc,
                                                                      "PanzerFaustEjectBrass");
                                                    if (tmp_i2 == 0) {
                                                      *(void **)(param_2 + 0x174c) =
                                                           CG_PanzerFaustEjectBrass;
                                                    }
                                                  }
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"flashSmokeSize");
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_Float_Parse(param_1,param_2 + 
                                                  0x1780);
                                                  if (tmp_i2 == 0) {
                                                    tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected flashSmokeSize value");
                                                  goto LAB_000d1472;
                                                  }
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"flashSmokeAlpha");
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_Float_Parse(param_1,param_2 + 
                                                  0x1788);
                                                  if (tmp_i2 == 0) {
                                                    tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected flashSmokeAlpha value");
                                                  goto LAB_000d1472;
                                                  }
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"flashSmokeLife");
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_Int_Parse(param_1,param_2 + 0x1784)
                                                      ;
                                                      if (tmp_i2 == 0) {
                                                        tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected flashSmokeLife int");
                                                  goto LAB_000d1472;
                                                  }
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"flashSmokeShader");
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_String_ParseNoAlloc
                                                                        (param_1,local_8cc,0x40);
                                                      if (tmp_i2 == 0) {
                                                        tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected flashSmokeShader filename");
                                                  goto LAB_000d1472;
                                                  }
                                                  tmp_u3 = trap_R_RegisterShader(local_8cc);
                                                  *(uint32_t *)(param_2 + 0x177c) = tmp_u3;
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"recoil_pitchAdd");
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_Int_Parse(param_1,param_2 + 6000);
                                                      if (tmp_i2 == 0) {
                                                        tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected recoil_pitchAdd int");
                                                  goto LAB_000d1472;
                                                  }
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"recoil_yawRandom");
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_Int_Parse(param_1,param_2 + 0x1774)
                                                      ;
                                                      if (tmp_i2 == 0) {
                                                        tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected recoil_yawRandom int");
                                                  goto LAB_000d1472;
                                                  }
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,
                                                                      "recoil_pitchAddRandom");
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_Int_Parse(param_1,param_2 + 0x1778)
                                                      ;
                                                      if (tmp_i2 == 0) {
                                                        tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected recoil_pitchAddRandom int");
                                                  goto LAB_000d1472;
                                                  }
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"brassModel");
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = PC_String_ParseNoAlloc
                                                                        (param_1,local_8cc,0x40);
                                                      if (tmp_i2 == 0) {
                                                        tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected brassModel filename");
                                                  goto LAB_000d1472;
                                                  }
                                                  tmp_u3 = trap_R_RegisterModel(local_8cc);
                                                  *(uint32_t *)(param_2 + 0x178c) = tmp_u3;
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"offset");
                                                    if (tmp_i2 != 0) {
                                                      tmp_i2 = Q_stricmp(local_424,"foreShorten");
                                                      if (tmp_i2 == 0) {
                                                        tmp_i2 = PC_Float_Parse(param_1,param_2 + 
                                                  0x179c);
                                                  if (tmp_i2 == 0) {
                                                    tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected foreShorten value");
                                                  goto LAB_000d1472;
                                                  }
                                                  goto LAB_000d1290;
                                                  }
                                                  tmp_i2 = Q_stricmp(local_424,"modModel");
                                                  if (tmp_i2 == 0) {
                                                    tmp_i2 = PC_Int_Parse(param_1,&local_8d0);
                                                    if (tmp_i2 == 0) {
                                                      tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected mod index");
                                                  }
                                                  else if (local_8d0 < 6) {
                                                    tmp_i2 = PC_String_ParseNoAlloc
                                                                      (param_1,local_88c,0x40);
                                                    tmp_u1 = local_8d0;
                                                    if (tmp_i2 != 0) {
                                                      tmp_u3 = trap_R_RegisterModel(local_88c);
                                                      *(uint32_t *)(param_2 + 0x1694 + tmp_u1 * 4)
                                                           = tmp_u3;
                                                      tmp_i2 = param_2 + local_8d0 * 4;
                                                      if (*(int *)(tmp_i2 + 0x1694) == 0) {
                                                        tmp_u3 = trap_R_RegisterShader(local_88c);
                                                        *(uint32_t *)(tmp_i2 + 0x1694) = tmp_u3;
                                                      }
                                                      goto LAB_000d1290;
                                                    }
                                                    tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected model filename");
                                                  }
                                                  else {
                                                    tmp_i2 = CG_RW_ParseError(param_1,
                                                  "mod index out of bounds");
                                                  }
                                                  }
                                                  else {
                                                    tmp_i2 = Q_stricmp(local_424,"firstPerson");
                                                    if (tmp_i2 == 0) {
                                                      tmp_u3 = 1;
                                                    }
                                                    else {
                                                      tmp_i2 = Q_stricmp(local_424,"thirdPerson");
                                                      if (tmp_i2 != 0) {
                                                        tmp_i2 = CG_RW_ParseError(param_1,
                                                  "unknown token \'%s\'",local_424);
                                                  goto LAB_000d1472;
                                                  }
                                                  tmp_u3 = 0;
                                                  }
                                                  tmp_i2 = CG_RW_ParseViewType(tmp_u3);
                                                  }
                                                  if (tmp_i2 == 0) {
                                                    return 0;
                                                  }
                                                  goto LAB_000d1290;
                                                  }
                                                  tmp_i2 = PC_Vec_Parse(param_1,param_2 + 0x17a0);
                                                  if (tmp_i2 == 0) {
                                                    tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected offset as x y z");
                                                  goto LAB_000d1472;
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
                                                  goto LAB_000d1290;
                                                  }
                                                  tmp_i2 = PC_String_ParseNoAlloc
                                                                    (param_1,local_8cc,0x40);
                                                  if (tmp_i2 != 0) {
                                                    tmp_u3 = trap_R_RegisterSkin(local_8cc);
                                                    *(uint32_t *)(param_2 + 0x172c) = tmp_u3;
                                                    goto LAB_000d1290;
                                                  }
                                                  }
                                                  tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected skin filename");
                                                  goto LAB_000d1472;
                                                  }
                                                  tmp_i2 = PC_String_ParseNoAlloc
                                                                    (param_1,local_8cc,0x40);
                                                  if (tmp_i2 != 0) {
                                                    tmp_u3 = trap_R_RegisterModel(local_8cc);
                                                    *(uint32_t *)(param_2 + 0x1790) = 1;
                                                    *(uint32_t *)(param_2 + 0x1724) = tmp_u3;
                                                    goto LAB_000d1290;
                                                  }
                                                }
                                              }
                                              tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected missileModel filename");
                                              goto LAB_000d1472;
                                            }
                                            tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
                                            if (tmp_i2 == 0) {
                                              tmp_i2 = CG_RW_ParseError(param_1,
                                                  "expected weaponSelectedIcon filename");
                                              goto LAB_000d1472;
                                            }
                                            tmp_u3 = trap_R_RegisterShader(local_8cc);
                                            *(uint32_t *)(param_2 + 0x1714) = tmp_u3;
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
            goto LAB_000d1290;
          }
          tmp_i2 = PC_String_ParseNoAlloc(param_1,local_8cc,0x40);
          if (tmp_i2 != 0) goto LAB_000d1290;
          tmp_i2 = CG_RW_ParseError(param_1,"expected pickupSound filename");
        }
LAB_000d1472:
        if (tmp_i2 == 0) {
          return 0;
        }
      } while( true );
    }
  }
  tmp_u3 = CG_RW_ParseError(param_1,"expected \'weaponDef\'");
  return tmp_u3;
}

void CG_RegisterWeapon(uint param_1,int param_2)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint tmp_u3;
  char *tmp_pc4;
  uint32_t *tmp_pu5;
  char *tmp_pc6;
  
  if (0x33 < param_1) {
    return;
  }
  if ((param_2 == 0) && (*(int *)(cg_weapons + param_1 * 0x17ac) != 0)) {
    return;
  }
  tmp_pu5 = (uint32_t *)(cg_weapons + param_1 * 0x17ac);
  tmp_u3 = 0x17ac;
  if (((uint)tmp_pu5 & 4) != 0) {
    *tmp_pu5 = 0;
    tmp_u3 = 0x17a8;
    tmp_pu5 = (uint32_t *)(cg_weapons + param_1 * 0x17ac + 4);
  }
  for (tmp_u3 = tmp_u3 >> 2; tmp_u3 != 0; tmp_u3 = tmp_u3 - 1) {
    *tmp_pu5 = 0;
    tmp_pu5 = tmp_pu5 + 1;
  }
  *(uint32_t *)(cg_weapons + param_1 * 0x17ac) = 1;
  switch(param_1) {
  case 0:
  case 0xd:
    return;
  case 1:
    tmp_pc4 = "knife.weap";
    break;
  case 2:
    tmp_pc4 = "luger.weap";
    break;
  case 3:
    tmp_pc4 = "mp40.weap";
    break;
  case 4:
    tmp_pc4 = "grenade.weap";
    break;
  case 5:
    tmp_pc4 = "panzerfaust.weap";
    break;
  case 6:
    tmp_pc4 = "flamethrower.weap";
    break;
  case 7:
    tmp_pc4 = "colt.weap";
    break;
  case 8:
    tmp_pc4 = "thompson.weap";
    break;
  case 9:
    tmp_pc4 = "pineapple.weap";
    break;
  case 10:
    tmp_pc4 = "sten.weap";
    break;
  case 0xb:
    tmp_pc4 = "syringe.weap";
    break;
  case 0xc:
    tmp_pc4 = "ammopack.weap";
    break;
  case 0xe:
    tmp_pc4 = "silenced_luger.weap";
    break;
  case 0xf:
    tmp_pc4 = "dynamite.weap";
    break;
  case 0x10:
    tmp_pc4 = "smoketrail.weap";
    break;
  default:
    CG_Printf("^1WARNING: trying to register weapon %i but there is no weapon file entry for it.\n",
              param_1);
    return;
  case 0x12:
    tmp_pc4 = "medpack.weap";
    break;
  case 0x13:
    tmp_pc4 = "binocs.weap";
    break;
  case 0x14:
    tmp_pc4 = "pliers.weap";
    break;
  case 0x15:
    tmp_pc4 = "smokemarker.weap";
    break;
  case 0x16:
    tmp_pc4 = "kar98.weap";
    break;
  case 0x17:
    tmp_pc4 = "m1_garand.weap";
    break;
  case 0x18:
  case 0x27:
    tmp_pc4 = "m1_garand_s.weap";
    break;
  case 0x19:
    tmp_pc4 = "landmine.weap";
    break;
  case 0x1a:
    tmp_pc4 = "satchel.weap";
    break;
  case 0x1b:
    tmp_pc4 = "satchel_det.weap";
    break;
  case 0x1c:
    tmp_pc4 = "smokegrenade.weap";
    break;
  case 0x1d:
  case 0x2e:
    tmp_pc4 = "mg42.weap";
    break;
  case 0x1e:
  case 0x28:
    tmp_pc4 = "k43.weap";
    break;
  case 0x1f:
  case 0x29:
    tmp_pc4 = "fg42.weap";
    break;
  case 0x21:
    tmp_pc4 = "mortar.weap";
    break;
  case 0x22:
    tmp_pc4 = "akimbo_colt.weap";
    break;
  case 0x23:
    tmp_pc4 = "akimbo_luger.weap";
    break;
  case 0x24:
    tmp_pc4 = "gpg40.weap";
    break;
  case 0x25:
    tmp_pc4 = "m7.weap";
    break;
  case 0x26:
    tmp_pc4 = "silenced_colt.weap";
    break;
  case 0x2a:
    tmp_pc4 = "mortar_set.weap";
    break;
  case 0x2b:
    tmp_pc4 = "adrenaline.weap";
    break;
  case 0x2c:
    tmp_pc4 = "akimbo_silenced_colt.weap";
    break;
  case 0x2d:
    tmp_pc4 = "akimbo_silenced_luger.weap";
    break;
  case 0x2f:
    tmp_pc4 = "poison.weap";
    break;
  case 0x30:
    tmp_pc4 = "bomb.weap";
    break;
  case 0x31:
    tmp_pc4 = "tripmine.weap";
    break;
  case 0x32:
    tmp_pc4 = "poisongas.weap";
    break;
  case 0x33:
    tmp_pc4 = "landmine_pgas.weap";
  }
  tmp_pc6 = tmp_pc4;
  tmp_u1 = va("%s/%s",0x3128bb8,tmp_pc4);
  tmp_i2 = trap_PC_LoadSource(tmp_u1);
  if (tmp_i2 == 0) {
    tmp_u1 = va("weapons/%s",tmp_pc4,tmp_pc6);
    trap_PC_LoadSource(tmp_u1);
  }
  CG_RegisterWeaponFromWeaponFile();
  return;
}

uint32_t CG_WeaponSelectable(int param_1)
{
  uint32_t tmp_u1;
  int tmp_i2;
  
  tmp_u1 = 1;
  if (param_1 != 0) {
    if ((((_DAT_01090764 & 0x8020) == 0) &&
        (tmp_i2 = COM_BitCheck(&g_unk_01090ad0,param_1), tmp_i2 != 0)) &&
       ((param_1 == 0x14 ||
        (((param_1 == 1 ||
          (tmp_i2 = BG_FindAmmoForWeapon(param_1), *(int *)(&g_unk_0109088c + tmp_i2 * 4) != 0)) ||
         (tmp_i2 = BG_FindClipForWeapon(param_1), *(int *)(&g_unk_0109098c + tmp_i2 * 4) != 0)))))) {
      tmp_u1 = 1;
    }
    else {
      tmp_u1 = 0;
    }
  }
  return tmp_u1;
}

uint32_t CG_WeaponIndex(int param_1,int *param_2,uint32_t *param_3)
{
  uint32_t tmp_u1;
  int *tmp_pi2;
  
  if (param_1 - 1U < 0x33) {
    tmp_pi2 = &weapBanksMultiPlayer;
    bnk_12439 = 0;
    do {
      cyc_12440 = 0;
      if (*tmp_pi2 != 0) {
        if (param_1 == *tmp_pi2) {
          cyc_12440 = 0;
LAB_000d4f40:
          tmp_u1 = cyc_12440;
          if (param_2 != (int *)0x0) {
            *param_2 = bnk_12439;
          }
          if (param_3 == (uint32_t *)0x0) {
            return 1;
          }
          *param_3 = tmp_u1;
          return 1;
        }
        if (tmp_pi2[1] == 0) {
          cyc_12440 = 1;
        }
        else {
          if (param_1 == tmp_pi2[1]) {
            cyc_12440 = 1;
            goto LAB_000d4f40;
          }
          if (tmp_pi2[2] == 0) {
            cyc_12440 = 2;
          }
          else {
            if (param_1 == tmp_pi2[2]) {
              cyc_12440 = 2;
              goto LAB_000d4f40;
            }
            if (tmp_pi2[3] == 0) {
              cyc_12440 = 3;
            }
            else {
              if (param_1 == tmp_pi2[3]) {
                cyc_12440 = 3;
                goto LAB_000d4f40;
              }
              if (tmp_pi2[4] == 0) {
                cyc_12440 = 4;
              }
              else {
                if (param_1 == tmp_pi2[4]) {
                  cyc_12440 = 4;
                  goto LAB_000d4f40;
                }
                if (tmp_pi2[5] == 0) {
                  cyc_12440 = 5;
                }
                else {
                  if (param_1 == tmp_pi2[5]) {
                    cyc_12440 = 5;
                    goto LAB_000d4f40;
                  }
                  if (tmp_pi2[6] == 0) {
                    cyc_12440 = 6;
                  }
                  else {
                    if (param_1 == tmp_pi2[6]) {
                      cyc_12440 = 6;
                      goto LAB_000d4f40;
                    }
                    if (tmp_pi2[7] == 0) {
                      cyc_12440 = 7;
                    }
                    else {
                      if (param_1 == tmp_pi2[7]) {
                        cyc_12440 = 7;
                        goto LAB_000d4f40;
                      }
                      if (tmp_pi2[8] == 0) {
                        cyc_12440 = 8;
                      }
                      else {
                        if (param_1 == tmp_pi2[8]) {
                          cyc_12440 = 8;
                          goto LAB_000d4f40;
                        }
                        if (tmp_pi2[9] == 0) {
                          cyc_12440 = 9;
                        }
                        else {
                          if (param_1 == tmp_pi2[9]) {
                            cyc_12440 = 9;
                            goto LAB_000d4f40;
                          }
                          if (tmp_pi2[10] == 0) {
                            cyc_12440 = 10;
                          }
                          else {
                            if (param_1 == tmp_pi2[10]) {
                              cyc_12440 = 10;
                              goto LAB_000d4f40;
                            }
                            if (tmp_pi2[0xb] == 0) {
                              cyc_12440 = 0xb;
                            }
                            else {
                              if (param_1 == tmp_pi2[0xb]) {
                                cyc_12440 = 0xb;
                                goto LAB_000d4f40;
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
      tmp_pi2 = tmp_pi2 + 0xc;
    } while (bnk_12439 != 10);
    bnk_12439 = 10;
  }
  else {
    if (param_2 != (int *)0x0) {
      *param_2 = 0;
    }
    if (param_3 != (uint32_t *)0x0) {
      *param_3 = 0;
    }
  }
  return 0;
}

void CG_WeaponBank_f(void)
{
  uint tmp_u1;
  char *__nptr;
  long tmp_l2;
  int tmp_i3;
  int tmp_i4;
  int tmp_i5;
  uint *tmp_pu6;
  long tmp_l7;
  int tmp_i8;
  int *local_2c;
  int local_28;
  
  if (((((g_unk_01047b00 != 0) && (*(int *)(g_unk_01047b00 + 0x30) != 4)) &&
       ((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) == 0)) &&
      (((int)GHIDRA_FIELD(cg_weaponCycleDelay, 12, 4) <= g_unk_010906e0 - g_unk_010aac34 &&
       ((g_unk_01091814 & 0xfffffffb) != 0x2a)))) &&
     (g_unk_010aac34 = g_unk_010906e0, *(int *)(g_unk_01047b00 + 0xd4) != 7)) {
    __nptr = (char *)CG_Argv(1);
    tmp_l2 = strtol(__nptr,(char **)0x0,10);
    tmp_u1 = g_unk_01091814;
    if (tmp_l2 - 1U < 10) {
      if (g_unk_01091814 - 1 < 0x33) {
        tmp_pu6 = &weapBanksMultiPlayer;
        local_28 = 0;
        do {
          cyc_12440 = 0;
          if (*tmp_pu6 != 0) {
            bnk_12439 = local_28;
            if (g_unk_01091814 == *tmp_pu6) {
              cyc_12440 = 0;
              goto LAB_000d8a89;
            }
            if (tmp_pu6[1] == 0) {
              cyc_12440 = 1;
            }
            else {
              if (g_unk_01091814 == tmp_pu6[1]) {
                cyc_12440 = 1;
                goto LAB_000d8a89;
              }
              if (tmp_pu6[2] == 0) {
                cyc_12440 = 2;
              }
              else {
                if (g_unk_01091814 == tmp_pu6[2]) {
                  cyc_12440 = 2;
                  goto LAB_000d8a89;
                }
                if (tmp_pu6[3] == 0) {
                  cyc_12440 = 3;
                }
                else {
                  if (g_unk_01091814 == tmp_pu6[3]) {
                    cyc_12440 = 3;
                    goto LAB_000d8a89;
                  }
                  if (tmp_pu6[4] == 0) {
                    cyc_12440 = 4;
                  }
                  else {
                    if (g_unk_01091814 == tmp_pu6[4]) {
                      cyc_12440 = 4;
                      goto LAB_000d8a89;
                    }
                    if (tmp_pu6[5] == 0) {
                      cyc_12440 = 5;
                    }
                    else {
                      if (g_unk_01091814 == tmp_pu6[5]) {
                        cyc_12440 = 5;
                        goto LAB_000d8a89;
                      }
                      if (tmp_pu6[6] == 0) {
                        cyc_12440 = 6;
                      }
                      else {
                        if (g_unk_01091814 == tmp_pu6[6]) {
                          cyc_12440 = 6;
                          goto LAB_000d8a89;
                        }
                        if (tmp_pu6[7] == 0) {
                          cyc_12440 = 7;
                        }
                        else {
                          if (g_unk_01091814 == tmp_pu6[7]) {
                            cyc_12440 = 7;
                            goto LAB_000d8a89;
                          }
                          if (tmp_pu6[8] == 0) {
                            cyc_12440 = 8;
                          }
                          else {
                            if (g_unk_01091814 == tmp_pu6[8]) {
                              cyc_12440 = 8;
                              goto LAB_000d8a89;
                            }
                            if (tmp_pu6[9] == 0) {
                              cyc_12440 = 9;
                            }
                            else {
                              if (g_unk_01091814 == tmp_pu6[9]) {
                                cyc_12440 = 9;
                                goto LAB_000d8a89;
                              }
                              if (tmp_pu6[10] == 0) {
                                cyc_12440 = 10;
                              }
                              else {
                                if (g_unk_01091814 == tmp_pu6[10]) {
                                  cyc_12440 = 10;
                                  goto LAB_000d8a89;
                                }
                                if (tmp_pu6[0xb] == 0) {
                                  cyc_12440 = 0xb;
                                }
                                else {
                                  if (g_unk_01091814 == tmp_pu6[0xb]) {
                                    cyc_12440 = 0xb;
                                    goto LAB_000d8a89;
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
          local_28 = local_28 + 1;
          tmp_pu6 = tmp_pu6 + 0xc;
        } while (local_28 != 10);
        bnk_12439 = 10;
      }
      local_28 = 0;
LAB_000d8a89:
      local_2c = &weapBanksMultiPlayer;
      tmp_i8 = (&g_unk_010aad18)[tmp_l2];
      tmp_i5 = -1;
      tmp_l7 = tmp_l2;
      if (tmp_i8 != 0) {
        if (tmp_i8 - 1U < 0x33) {
          tmp_l7 = 0;
          do {
            cyc_12440 = 0;
            if (*local_2c != 0) {
              bnk_12439 = tmp_l7;
              if (tmp_i8 == *local_2c) {
                tmp_i5 = 0;
                cyc_12440 = 0;
                goto LAB_000d8eed;
              }
              if (local_2c[1] == 0) {
                cyc_12440 = 1;
              }
              else {
                if (tmp_i8 == local_2c[1]) {
                  tmp_i5 = 1;
                  cyc_12440 = tmp_i5;
                  goto LAB_000d8eed;
                }
                if (local_2c[2] == 0) {
                  cyc_12440 = 2;
                }
                else {
                  if (tmp_i8 == local_2c[2]) {
                    tmp_i5 = 2;
                    cyc_12440 = tmp_i5;
                    goto LAB_000d8eed;
                  }
                  if (local_2c[3] == 0) {
                    cyc_12440 = 3;
                  }
                  else {
                    if (tmp_i8 == local_2c[3]) {
                      tmp_i5 = 3;
                      cyc_12440 = tmp_i5;
                      goto LAB_000d8eed;
                    }
                    if (local_2c[4] == 0) {
                      cyc_12440 = 4;
                    }
                    else {
                      if (tmp_i8 == local_2c[4]) {
                        tmp_i5 = 4;
                        cyc_12440 = tmp_i5;
                        goto LAB_000d8eed;
                      }
                      if (local_2c[5] == 0) {
                        cyc_12440 = 5;
                      }
                      else {
                        if (tmp_i8 == local_2c[5]) {
                          tmp_i5 = 5;
                          cyc_12440 = tmp_i5;
                          goto LAB_000d8eed;
                        }
                        if (local_2c[6] == 0) {
                          cyc_12440 = 6;
                        }
                        else {
                          if (tmp_i8 == local_2c[6]) {
                            tmp_i5 = 6;
                            cyc_12440 = tmp_i5;
                            goto LAB_000d8eed;
                          }
                          if (local_2c[7] == 0) {
                            cyc_12440 = 7;
                          }
                          else {
                            if (tmp_i8 == local_2c[7]) {
                              tmp_i5 = 7;
                              cyc_12440 = tmp_i5;
                              goto LAB_000d8eed;
                            }
                            if (local_2c[8] == 0) {
                              cyc_12440 = 8;
                            }
                            else {
                              if (tmp_i8 == local_2c[8]) {
                                tmp_i5 = 8;
                                cyc_12440 = tmp_i5;
                                goto LAB_000d8eed;
                              }
                              if (local_2c[9] == 0) {
                                cyc_12440 = 9;
                              }
                              else {
                                if (tmp_i8 == local_2c[9]) {
                                  tmp_i5 = 9;
                                  cyc_12440 = tmp_i5;
                                  goto LAB_000d8eed;
                                }
                                if (local_2c[10] == 0) {
                                  cyc_12440 = 10;
                                }
                                else {
                                  if (tmp_i8 == local_2c[10]) {
                                    tmp_i5 = 10;
                                    cyc_12440 = tmp_i5;
                                    goto LAB_000d8eed;
                                  }
                                  if (local_2c[0xb] == 0) {
                                    cyc_12440 = 0xb;
                                  }
                                  else {
                                    if (tmp_i8 == local_2c[0xb]) {
                                      tmp_i5 = 0xb;
                                      cyc_12440 = tmp_i5;
                                      goto LAB_000d8eed;
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
            tmp_l7 = tmp_l7 + 1;
            local_2c = local_2c + 0xc;
          } while (tmp_l7 != 10);
          tmp_i5 = 0;
          bnk_12439 = 10;
          tmp_l7 = tmp_l2;
        }
        else {
          tmp_i5 = 0;
          tmp_l7 = 0;
        }
LAB_000d8eed:
        tmp_i5 = tmp_i5 - (uint)(tmp_l7 != local_28);
      }
      tmp_i8 = 0;
      do {
        tmp_i4 = (&weapBanksMultiPlayer)[(tmp_i5 + 1 + tmp_i8) % 0xc + tmp_l7 * 0xc];
        if (((tmp_i4 == 0) && (tmp_i4 = (&weapBanksMultiPlayer)[tmp_l7 * 0xc], tmp_i4 == 0)) ||
           ((((_DAT_01090764 & 0x8020) == 0 &&
             (tmp_i3 = COM_BitCheck(&g_unk_01090ad0,tmp_i4), tmp_i3 != 0)) &&
            ((((tmp_i4 == 0x14 || (tmp_i4 == 1)) ||
              (tmp_i3 = BG_FindAmmoForWeapon(tmp_i4), *(int *)(&g_unk_0109088c + tmp_i3 * 4) != 0)) ||
             (tmp_i3 = BG_FindClipForWeapon(tmp_i4), *(int *)(&g_unk_0109098c + tmp_i3 * 4) != 0))))))
        goto LAB_000d8aef;
        if (tmp_i4 == 0x16) {
          if ((((_DAT_01090764 & 0x8020) == 0) &&
              (tmp_i4 = COM_BitCheck(&g_unk_01090ad0,0x24), tmp_i4 != 0)) &&
             ((tmp_i4 = BG_FindAmmoForWeapon(0x24), *(int *)(&g_unk_0109088c + tmp_i4 * 4) != 0 ||
              (tmp_i4 = BG_FindClipForWeapon(0x24), *(int *)(&g_unk_0109098c + tmp_i4 * 4) != 0)))) {
            tmp_i4 = 0x24;
            goto LAB_000d8bdf;
          }
        }
        else if (((tmp_i4 == 0x17) && ((_DAT_01090764 & 0x8020) == 0)) &&
                ((tmp_i4 = COM_BitCheck(&g_unk_01090ad0,0x25), tmp_i4 != 0 &&
                 ((tmp_i4 = BG_FindAmmoForWeapon(0x25), *(int *)(&g_unk_0109088c + tmp_i4 * 4) != 0 ||
                  (tmp_i4 = BG_FindClipForWeapon(0x25), *(int *)(&g_unk_0109098c + tmp_i4 * 4) != 0)))))
                ) {
          tmp_i4 = 0x25;
LAB_000d8bdf:
          if (tmp_i8 == 0xc) {
            return;
          }
LAB_000d8aef:
          if ((*(uint *)(g_unk_01047b00 + 0xd4) & 0xfffffffd) == 1) {
            if (tmp_u1 - 0x24 < 3) {
              return;
            }
            if (tmp_i4 - 0x24U < 3) {
              return;
            }
            if (tmp_u1 == 0xe) {
              return;
            }
            if (tmp_i4 == 0xe) {
              return;
            }
            if (tmp_u1 == 0x2a) {
              return;
            }
            if (tmp_i4 == 0x2a) {
              return;
            }
          }
          CG_FinishWeaponChange(tmp_u1,tmp_i4);
          return;
        }
        tmp_i8 = tmp_i8 + 1;
      } while (tmp_i8 != 0xc);
    }
  }
  return;
}

void CG_Weapon_f(void)
{
  char *__nptr;
  long tmp_l1;
  
  if ((((g_unk_01047b00 != 0) && (*(int *)(g_unk_01047b00 + 0x30) != 4)) &&
      ((*(byte *)(g_unk_01047b00 + 0x39) & 0x10) == 0)) && ((g_unk_01091814 & 0xfffffffb) != 0x2a)) {
    __nptr = (char *)CG_Argv(1);
    tmp_l1 = strtol(__nptr,(char **)0x0,10);
    if (tmp_l1 < 10) {
      CG_WeaponBank_f();
      return;
    }
  }
  return;
}

void CG_WeaponFireRecoil(uint32_t param_1)
{
  float tmp_f1;
  float tmp_f2;
  uint tmp_u3;
  int tmp_i4;
  float local_1c;
  
  switch(param_1) {
  default:
    goto _L3224;
  case 2:
  case 5:
  case 7:
  case 0xe:
  case 0x22:
  case 0x23:
  case 0x26:
  case 0x2c:
  case 0x2d:
    local_1c = 0.0;
    tmp_f1 = -0.0;
    break;
  case 3:
  case 8:
  case 10:
  case 0x1d:
  case 0x1f:
  case 0x29:
  case 0x2e:
    tmp_i4 = rand();
    tmp_f1 = -((float)(tmp_i4 % 3 + 1) * 0.3);
    local_1c = 0.6;
    break;
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x1e:
    tmp_f1 = -2.0;
    local_1c = 1.0;
    break;
  case 0x27:
  case 0x28:
    tmp_f1 = -0.3;
    local_1c = 0.0;
  }
  tmp_u3 = rand();
  tmp_f2 = (float)(tmp_u3 & 0x7fff) / 32767.0 - 0.5;
  local_1c = (tmp_f2 + tmp_f2) * local_1c;
  g_unk_010aaeac = tmp_f1 * 30.0;
  g_unk_010aaeb0 = local_1c * 30.0;
  g_unk_010aaeb4 = -local_1c * 30.0;
_L3224:
  return;
}

void CG_FireWeapon(int *param_1,int param_2)
{
  int tmp_i1;
  uint32_t tmp_u2;
  int tmp_i3;
  int tmp_i4;
  int *tmp_pi5;
  long double tmp_l6;
  int *local_4c;
  int local_48;
  int local_44;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  
  tmp_i4 = g_unk_01047b00;
  if ((param_1[2] & 0x8000U) != 0) {
    tmp_u2 = GHIDRA_FIELD(cgs, 69824, 4);
    if ((cg_entities
         [*(int *)(cg_entities + *(int *)(cg_entities + *param_1 * 0xaf8 + 0xab4) * 0xaf8 + 0x9bc) *
          0xaf8 + 0xf4] & 8) == 0) {
      tmp_u2 = GHIDRA_FIELD(cgs, 69812, 4);
    }
    trap_S_StartSound(0,*param_1,2,tmp_u2);
LAB_000de029:
    param_1[0x92] = g_unk_010906e0;
    return;
  }
  if ((param_1[2] & 0x8020U) != 0) {
    trap_S_StartSound(0,*param_1,2,GHIDRA_FIELD(cgs, 69812, 4));
    if (0 < (int)GHIDRA_FIELD(cg_brassTime, 12, 4)) {
      CG_MachineGunEjectBrass(param_1);
    }
    goto LAB_000de029;
  }
  tmp_i1 = param_1[0x3a];
  if (tmp_i1 == 0) {
    return;
  }
  if (0x33 < tmp_i1) {
    CG_Error("CG_FireWeapon: ent->weapon >= WP_NUM_WEAPONS");
    return;
  }
  tmp_i3 = tmp_i1;
  if (param_1[0x2b] == *(int *)(g_unk_01047b00 + 0xcc)) {
    tmp_i3 = param_1[0x3a];
    g_unk_010aacfc = tmp_i1;
  }
  param_1[0x92] = g_unk_010906e0;
  if (*param_1 == *(int *)(tmp_i4 + 0xcc)) {
    CG_WeaponFireRecoil(tmp_i3);
    tmp_i3 = param_1[0x3a];
  }
  if (tmp_i3 == 0x2a) {
    if (param_1[0x2b] == *(int *)(g_unk_01047b00 + 0xcc)) {
      g_unk_010b455c = g_unk_010907ac;
      g_unk_010b4564 = 0xffffffff;
      g_unk_010b4560 = g_unk_010907b0;
      tmp_i3 = param_1[0x3a];
      goto LAB_000de0ae;
    }
  }
  else {
LAB_000de0ae:
    if (tmp_i3 == 6) {
      if (param_1[0x11d] != 0) {
        return;
      }
      goto LAB_000de120;
    }
  }
  if (((((((tmp_i3 == 4 || tmp_i3 == 9) || tmp_i3 == 0xf) || tmp_i3 == 0x15) || tmp_i3 == 0x1c) ||
        tmp_i3 - 0x19U < 2) || (tmp_i3 - 0x30U < 4)) && (0.0 < (float)param_1[0xf])) {
    return;
  }
  if (tmp_i3 == 0x24) {
    if (param_1[0x2b] == *(int *)(g_unk_01047b00 + 0xcc)) {
      g_unk_01091814 = 0x16;
    }
  }
  else if ((tmp_i3 == 0x25) && (param_1[0x2b] == *(int *)(g_unk_01047b00 + 0xcc))) {
    g_unk_01091814 = 0x17;
  }
LAB_000de120:
  if ((param_1[0x2e] & 0xfffffcffU) == 0x23) {
    tmp_i4 = tmp_i1 * 0x17ac;
    local_4c = (int *)(cg_weapons + tmp_i4 + 0x16b8);
    if (*(int *)(cg_weapons + tmp_i4 + 0x16d8) != 0) {
      local_4c = (int *)(cg_weapons + tmp_i4 + 0x16d8);
    }
  }
  else {
    local_4c = (int *)(cg_weapons + tmp_i1 * 0x17ac + 0x16b8);
  }
  local_48 = tmp_i1 * 0x17ac + 0xfbf988;
  if (param_2 == 0x5f) {
    trap_S_StartSound(0,*param_1,2,GHIDRA_FIELD(cgs, 131904, 4));
  }
  else if ((*(byte *)((int)param_1 + 10) & 4) == 0) {
    if (*local_4c != 0) {
      if (local_4c[1] == 0) {
        local_44 = 1;
      }
      else if (local_4c[2] == 0) {
        local_44 = 2;
      }
      else {
        local_44 = 4 - (uint)(local_4c[3] == 0);
      }
      tmp_i4 = rand();
      if (local_4c[tmp_i4 % local_44] != 0) {
        trap_S_StartSound(0,*param_1,2,local_4c[tmp_i4 % local_44]);
        tmp_pi5 = (int *)((tmp_i4 % local_44) * 4 + local_48);
        if (*tmp_pi5 != 0) {
          tmp_i4 = *param_1 * 0xaf8;
          local_34 = *(float *)(cg_entities + tmp_i4 + 0x18);
          local_30 = *(float *)(cg_entities + tmp_i4 + 0x1c);
          local_2c = *(float *)(cg_entities + tmp_i4 + 0x20);
          local_28 = local_34 - *(float *)(g_unk_010afbcc + 0x18);
          local_24 = local_30 - *(float *)(g_unk_010afbcc + 0x1c);
          local_20 = local_2c - *(float *)(g_unk_010afbcc + 0x20);
          tmp_l6 = (long double)VectorNormalize(&local_28);
          if (((long double)512.0 < tmp_l6) && (tmp_l6 < (long double)4096.0)) {
            local_34 = local_28 * 64.0 + *(float *)(g_unk_010afbcc + 0x18);
            local_30 = local_24 * 64.0 + *(float *)(g_unk_010afbcc + 0x1c);
            local_2c = local_20 * 64.0 + *(float *)(g_unk_010afbcc + 0x20);
            trap_S_StartSoundEx(&local_34,*param_1,2,*tmp_pi5,0x10);
          }
        }
      }
    }
    if ((0 < (int)GHIDRA_FIELD(cg_brassTime, 12, 4)) &&
       (*(void **)(cg_weapons + tmp_i1 * 0x17ac + 0x174c) != (void *)0x0)) {
      (**(void **)(cg_weapons + tmp_i1 * 0x17ac + 0x174c))(param_1);
    }
  }
  if (GHIDRA_FIELD(developer, 12, 4) == 0) {
    return;
  }
  if (*param_1 != g_unk_0109079c) {
    return;
  }
  CG_DrawHitBoxOnHit_part_11();
  return;
}

