#ifndef CGAME_SERVERCMDS_H
#define CGAME_SERVERCMDS_H

/* Server-command and config-string processing */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void CG_ParseMapEntity(int *param_1,int *param_2,uint32_t param_3);
void CG_ParseMapEntityInfo(int param_1,int param_2);
void CG_ParseFireteams(void);
void CG_ParseTeamXPs(int param_1);
uint32_t CG_ParseVoiceChats_constprop_4(uint32_t param_1,int param_2);
void CG_ParseServerinfo(char *param_1);
void CG_ParseOIDInfo(int param_1);
void CG_ParseOIDInfos(void);
void CG_ParseSpawns(void);
void CG_ParseReinforcementTimes(char *param_1);
uint32_t CG_ParseVoiceChats(uint32_t param_1,int param_2,int param_3);
void CG_ParseWarmup(void);
void CG_ParseWolfinfo(void);
void CG_ParseWeaponStats(void);
void CG_ParsePortalPos(void);
void CG_ServerCommand(void);
void CG_ParseEntityFromSpawnVars(void);
uint32_t CG_ParseSpawnVars(void);
void CG_ParseEntitiesFromString(void);
void CG_ParseSkyBox(void);
void CG_ParseTagConnects(void);
void CG_ParseTagConnect(uint32_t param_1);
uint32_t CG_ParseWeaponConfig(uint32_t param_1,int param_2);
void CG_ParseScore(int param_1);
void CG_ParseKD(int param_1);
void CG_ParseInfo(void);

#endif

