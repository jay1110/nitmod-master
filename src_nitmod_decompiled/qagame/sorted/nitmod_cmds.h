#ifndef NITMOD_CMDS_H
#define NITMOD_CMDS_H

/* Client and server console commands */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void Cmd_SetViewpos_f_part_9(uint32_t param_1);
void Cmd_IntermissionPlayerKillsDeaths_f_part_18(int param_1);
void Cmd_IntermissionWeaponAccuracies_f_part_19(int param_1);
void Cmd_Score_f(int param_1);
void Cmd_GiveDisguise_f(int param_1,int param_2);
void Cmd_Give_f(int param_1);
void Cmd_God_f(int param_1);
void Cmd_Nofatigue_f(int param_1);
void Cmd_Notarget_f(int param_1);
void Cmd_Noclip_f(int param_1);
void Cmd_Kill_f(int param_1);
void Cmd_ResetSetup_f(int param_1);
void Cmd_Say_f(uint32_t param_1,uint32_t param_2,int param_3);
void Cmd_Where_f(int param_1);
uint32_t Cmd_CallVote_f(uint32_t *param_1,uint32_t param_2,int param_3);
void Cmd_Vote_f(int param_1);
void Cmd_SetViewpos_f(int param_1);
void Cmd_Activate_f(int *param_1);
void Cmd_Activate2_f(uint32_t *param_1);
void Cmd_Team_f(int param_1);
void Cmd_SetClass_f(int param_1);
void Cmd_FollowCycle_f(int param_1,int param_2);
void Cmd_Follow_f(int param_1);
void Cmd_SetSpawnPoint_f_part_17(int param_1);
void Cmd_SetSpawnPoint_f(void);
void Cmd_WeaponStat_f(int param_1);
void Cmd_IntermissionWeaponStats_f(int param_1);
void Cmd_IntermissionReady_f(int param_1);
void Cmd_IntermissionPlayerKillsDeaths_f(int param_1);
void Cmd_IntermissionWeaponAccuracies_f(int param_1);
void Cmd_IntermissionHitRegions_f(int param_1);
void Cmd_SelectedObjective_f(int param_1);
void Cmd_Ignore_f(int param_1);
void Cmd_UnIgnore_f(int param_1);
void Cmd_DropObj(uint32_t *param_1);
void Cmd_FireTeam_MP_f(int param_1);
void Svcmd_GameMem_f(void);
void Cmd_AuthRcon_f(int param_1);
void Svcmd_AddIP_f(void);
void Svcmd_RemoveIP_f(void);
void Svcmd_EntityList_f(void);
void Svcmd_ForceTeam_f(void);
void Svcmd_ResetMatch_f(int param_1,int param_2);
void Svcmd_SwapTeams_f(void);
void Svcmd_ShuffleTeams_f(int param_1);
void Svcmd_Campaign_f(void);
void Svcmd_ListCampaigns_f(void);
void Svcmd_RevivePlayer(uint32_t param_1);

#endif

