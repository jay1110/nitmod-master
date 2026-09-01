#ifndef CGAME_ENTS_H
#define CGAME_ENTS_H

/* Client entity placement and scene submission */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void CG_ItemPickup(int param_1);
void CG_AddAtmosphericEffects(void);
void CG_AdjustAutomapZoom(int param_1);
void CG_AddLagometerFrameInfo(void);
void CG_AddLagometerSnapshotInfo(uint32_t *param_1);
void CG_AdjustFrom640(float *param_1,float *param_2,float *param_3,float *param_4);
void CG_AdjustFrom640FullScreen(float *param_1,float *param_2,float *param_3,float *param_4);
void CG_AddSmokeSprites(void);
void CG_EntityEffects(uint32_t *param_1);
void CG_PositionRotatedEntityOnTag(int param_1,int param_2,uint32_t param_3);
void CG_AddLightstyle(uint32_t *param_1);
void CG_Item(int param_1);
void CG_Beam_2(int param_1);
void CG_Beam(int param_1);
uint32_t CG_AddLinkedEntity(int param_1,int param_2,int param_3);
void CG_CalcEntityLerpPositions(int *param_1);
void CG_AddCEntity(int *param_1);
uint32_t CG_AddCEntity_Filter(int param_1);
uint32_t CG_AddEntityToTag_part_10(int *param_1);
uint32_t CG_AddEntityToTag(int param_1);
void CG_Mover_PostProcess_part_11(int param_1);
void CG_Mover_PostProcess(int param_1);
void CG_AddPacketEntities(void);
void CG_AddFlameSpriteToScene(int param_1,float param_2,float param_3);
void CG_AddFlameToScene(int param_1);
void CG_AddFlameChunks(void);
void CG_AddEmitter(int param_1);
void CG_AddFragment(int *param_1);
void CG_AddMovingTracer(int param_1);
void CG_AddSparkElements(int *param_1);
void CG_AddFuseSparkElements(int param_1);
void CG_AddBloodElements(int param_1);
void CG_AddDebrisElements(int *param_1);
void CG_AddFadeRGB(int param_1);
void CG_AddConstRGB(int param_1);
void CG_AddLocalEntities(void);
void CG_AddToTeamChat(char *param_1,int param_2);
void CG_AddMarks(void);
void CG_AddParticleToScene(int param_1,float *param_2);
void CG_AddParticles(void);
void CG_AddParticleShrapnel(void);
void CG_AddOnScreenText(uint32_t param_1,float *param_2);
void CG_AddWoundedPlayer(uint32_t param_1,float *param_2);
void CG_AddToListFront(int *param_1,int param_2);
void CG_AddPMItem(uint param_1,char *param_2,uint param_3,uint *param_4);
void CG_AddPMItemBig(int param_1,uint32_t param_2,int param_3,uint32_t *param_4);
void CG_AddToNotify(char *param_1);
void CG_AddBufferedVoiceChat(int param_1);
void CG_AddBufferedSoundScript(uint32_t param_1);
void CG_AddLineToScene(uint32_t *param_1,uint32_t *param_2,float *param_3);
void CG_AddScriptSpeakers(void);
void CG_AddSpawnVarToken(char *param_1);
void CG_AddTrailToScene(int param_1,int param_2,int param_3);
void CG_AddTrails(void);
void CG_AdjustZoomVal(float param_1,int param_2);
void CG_AddWeaponWithPowerups_isra_1(int param_1);
void CG_AddBulletParticles_part_13(float *param_1,float *param_2,int param_3,int param_4,float param_5);
void CG_AddPlayerWeapon(float *param_1,int param_2,int *param_3);
void CG_AddViewWeapon(int param_1);
uint32_t CG_AddSparks(uint32_t param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4);
uint32_t CG_AddBulletParticles(uint32_t param_1);
void CG_AddDirtBulletParticles(void);
void CG_AddDebris(uint32_t *param_1,float *param_2,int param_3,int param_4,int param_5);

#endif

