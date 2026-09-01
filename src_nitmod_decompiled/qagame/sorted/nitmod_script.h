#ifndef NITMOD_SCRIPT_H
#define NITMOD_SCRIPT_H

/* Entity scripting */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void script_mover_think(int param_1);
bool G_Script_EventMatch_StringEqual(int param_1,int param_2);
bool G_Script_EventMatch_IntInRange(int param_1,int param_2);
void script_mover_spawn(int param_1);
void script_mover_blocked(uint32_t param_1,int param_2);
void script_model_med_use(int param_1);
int G_Script_EventForString(uint32_t param_1);
uint8_t ** G_Script_ActionForString(uint32_t param_1);
void G_Script_ScriptLoad(void);
void G_Script_ScriptParse(int param_1);
void G_Script_ScriptChange(int param_1,uint32_t param_2);
void G_Script_EventStringInit(void);
int G_Script_GetEventIndex(int param_1,uint32_t param_2,uint8_t *param_3);
uint32_t G_Script_ScriptRun(int param_1);
void G_Script_ScriptEvent(int param_1,uint32_t param_2,uint32_t param_3);
void script_mover_use(int param_1);
void script_mover_die(int param_1);
void script_linkentity(uint32_t param_1);
void script_model_med_spawn(int param_1);
uint32_t G_ScriptAction_SetModelFromBrushmodel(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetPosition(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetAutoSpawn(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_ChangeModel(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_ShaderRemap(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_ShaderRemapFlush(void);
uint32_t G_ScriptAction_FollowPath(int param_1,int param_2);
uint32_t G_ScriptAction_AttatchToTrain(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_FreezeAnimation(int param_1);
uint32_t G_ScriptAction_UnFreezeAnimation(int param_1);
uint32_t G_ScriptAction_StartAnimation(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetSpeed(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetRotation(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_StopRotation(int param_1);
uint32_t G_ScriptAction_FollowSpline(int param_1,int param_2);
uint32_t G_ScriptAction_AbortMove(int param_1);
uint32_t G_ScriptAction_SetChargeTimeFactor(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_SpawnRubble(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_AllowTankExit(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_AllowTankEnter(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetTankAmmo(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_AddTankAmmo(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_DisableMessage(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_Kill(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetGlobalFog(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_GotoMarker(int param_1,int param_2);
bool G_ScriptAction_Wait(int param_1,uint32_t param_2);
bool G_ScriptAction_Trigger(uint8_t *param_1,uint32_t param_2);
uint32_t G_ScriptAction_PlaySound(int param_1,int param_2);
uint32_t G_ScriptAction_FadeAllSounds(uint32_t param_1,int param_2);
uint32_t G_ScriptAction_MusicStart(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_MusicPlay(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_MusicStop(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_MusicQueue(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_MusicFade(uint32_t param_1,uint32_t param_2);
bool G_ScriptAction_PlayAnim(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_AlertEntity(uint32_t param_1,char *param_2);
uint32_t G_ScriptAction_ToggleSpeaker(uint32_t param_1,char *param_2);
uint32_t G_ScriptAction_DisableSpeaker(uint32_t param_1,char *param_2);
uint32_t G_ScriptAction_EnableSpeaker(uint32_t param_1,char *param_2);
bool G_ScriptAction_Accum(int param_1,uint32_t param_2);
bool G_ScriptAction_GlobalAccum(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_Print(int param_1,char *param_2);
uint32_t G_ScriptAction_FaceAngles(int param_1,char *param_2);
bool G_ScriptAction_ResetScript(int param_1);
uint32_t G_ScriptAction_TagConnect(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_Halt(int param_1);
uint32_t G_ScriptAction_StopSound(int param_1);
uint32_t G_ScriptAction_EntityScriptName(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_AIScriptName(void);
uint32_t G_ScriptAction_AxisRespawntime(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_AlliedRespawntime(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_NumberofObjectives(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetMainObjective(void);
uint32_t G_ScriptAction_ObjectiveStatus(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetDebugLevel(uint32_t param_1,char *param_2);
uint32_t G_ScriptAction_VoiceAnnounce(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetWinner(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetDefendingTeam(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_AddTeamVoiceAnnounce(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_RemoveTeamVoiceAnnounce(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_TeamVoiceAnnounce(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_Announce_Icon(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_Announce(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_EndRound(void);
uint32_t G_ScriptAction_SetRoundTimelimit(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_RemoveEntity(int param_1);
uint32_t G_ScriptAction_SetDamagable(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetState(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_RepairMG42(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_SetHQStatus(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_PrintAccum(int param_1,char *param_2);
uint32_t G_ScriptAction_PrintGlobalAccum(uint32_t param_1,char *param_2);
uint32_t G_ScriptAction_SetAASState(void);
uint32_t G_ScriptAction_Construct(uint32_t param_1,uint32_t param_2);
uint32_t G_ScriptAction_ConstructibleClass(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_ConstructibleChargeBarReq(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_ConstructibleConstructXPBonus(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_ConstructibleDestructXPBonus(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_ConstructibleHealth(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_ConstructibleWeaponclass(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_ConstructibleDuration(int param_1,uint32_t param_2);
bool G_ScriptAction_Cvar(int param_1,uint32_t param_2);
uint32_t G_ScriptAction_AbortIfWarmup(int param_1);
uint32_t G_ScriptAction_AbortIfNotSinglePlayer(int param_1);
uint32_t G_ScriptAction_Create(int param_1,uint32_t param_2);

#endif

