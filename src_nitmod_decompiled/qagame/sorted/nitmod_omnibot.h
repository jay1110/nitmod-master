#ifndef NITMOD_OMNIBOT_H
#define NITMOD_OMNIBOT_H

/* Omni-bot interface */

#include "nitmod_types.h"
#include "nitmod_globals.h"

uint IsBot(gentity_s *param_1);
uint8_t * INDEXENT(int param_1);
int ENTINDEX(gentity_s *param_1);
uint8_t * EntityFromHandle(int param_1);
void HandleFromEntity(gentity_s *param_1);
void SendDeferredGoals(void);
void GetEntityCenter(int param_1,float *param_2);
void UpdateMG42(gentity_s *param_1);
void CheckForMG42(gentity_s *param_1,char *param_2);
uint32_t Bot_TeamGameToBot(int param_1);
uint32_t Bot_PlayerClassGameToBot(uint param_1);
int Bot_WeaponGameToBot(int param_1);
bool Simple_EmplacedGunIsRepairable(gentity_s *param_1);
int Bot_EntInvisibleBySmokeBomb(float *param_1,float *param_2);
bool _TankIsMountable(gentity_s *param_1);
bool _EmplacedGunIsMountable(gentity_s *param_1);
void Omnibot_Load_PrintMsg(char *param_1);
void Omnibot_Load_PrintErr(char *param_1);
uint obUtilBotContentsFromGameContents(int param_1);
uint obUtilBotSurfaceFromGameSurface(int param_1);
void Bot_Interface_InitHandles(void);
bool Bot_Interface_Init(void);
uint32_t Bot_Interface_Shutdown(void);
void Bot_Interface_ConsoleCommand(void);
uint32_t Bot_Util_AllowPush(int param_1);
char * _GetEntityName(int param_1);
void GetMG42s(void);
void Bot_Util_CheckForGoalEntity(uint32_t param_1);
uint32_t Bot_Util_CheckForSuicide(int param_1);
void Bot_Event_ClientConnected(uint32_t param_1,int param_2);
void Bot_Event_ClientDisConnected(uint32_t param_1);
void Bot_Event_ResetWeapons(int param_1);
void Bot_Event_AddWeapon(int param_1,uint32_t param_2);
void Bot_Event_RemoveWeapon(int param_1,uint32_t param_2);
void Bot_Event_TakeDamage(int param_1);
void Bot_Event_Death(int param_1,uint32_t param_2,char *param_3);
void Bot_Event_Healed(int param_1);
void Bot_Event_RecievedAmmo(int param_1);
void Bot_Event_Revived(int param_1);
void Bot_Event_KilledSomeone(int param_1,uint32_t param_2,char *param_3);
void Bot_Event_FireWeapon(int param_1,uint32_t param_2);
void Bot_Event_PreTriggerMine(int param_1);
void Bot_Event_PostTriggerMine(int param_1);
void Bot_Event_MortarImpact(int param_1,uint32_t *param_2);
void Bot_Event_Spectated(int param_1,uint32_t param_2);
void Bot_Event_ChatMessage(int param_1,uint32_t param_2,int param_3,char *param_4);
void Bot_Event_VoiceMacro(int param_1,uint32_t param_2,int param_3,char *param_4);
void Bot_Event_Sound(uint32_t param_1,uint32_t param_2,char *param_3);
void Bot_Event_FireTeamCreated(int param_1,uint32_t param_2);
void Bot_Event_FireTeamDestroyed(int param_1);
void Bot_Event_JoinedFireTeam(int param_1);
void Bot_Event_LeftFireTeam(int param_1);
void Bot_Event_InviteFireTeam(uint32_t param_1,int param_2);
void Bot_Event_FireTeam_Proposal(int param_1);
void Bot_Event_FireTeam_Warn(int param_1,uint32_t param_2);
void Bot_Event_EntityCreated(gentity_s *param_1);
void Bot_Queue_EntityCreated(int param_1);
void Bot_Event_EntityDeleted(int param_1);
void Bot_Interface_Update(void);
void Bot_AddDynamiteGoal(gentity_s *param_1,int param_2,char *param_3);
void Bot_AddFallenTeammateGoals(gentity_s *param_1,int param_2);
uint8_t IsOmnibotLoaded(void);
uint32_t Omnibot_GetLibraryPath(void);
void Omnibot_strncpy(char *param_1,char *param_2,int param_3);
uint8_t * Omnibot_ErrorString(uint param_1);
uint8_t * Omnibot_FixPath(char *param_1);
char * OB_VA(char *param_1);
void OB_VA_OWNBUFFER(char *param_1,int param_2,char *param_3,...);
uint32_t OB_ShowLastError(char *param_1,char *param_2);
int Omnibot_LL(char *param_1);
int Omnibot_LoadLibrary(int param_1,char *param_2,char *param_3);
void Omnibot_FreeLibrary(void);

#endif

