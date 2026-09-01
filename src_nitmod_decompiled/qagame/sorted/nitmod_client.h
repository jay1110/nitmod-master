#ifndef NITMOD_CLIENT_H
#define NITMOD_CLIENT_H

/* Client think, connect, spectator, revive */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void ClientImpacts(int param_1,int param_2);
void SpectatorThink(int param_1,int param_2);
uint32_t ClientInactivityTimer(int param_1);
void ClientTimerActions(int param_1,int param_2);
void ClientIntermissionThink(int param_1);
void ClientEvents(uint32_t *param_1,uint param_2);
void ClientThink_checkWeapons(int param_1);
void ClientThink_doPmove(int param_1,int param_2);
void ClientThink_real(uint32_t *param_1);
void ClientThink_cmd(int param_1,int param_2);
void ClientThink(int param_1);
void SpectatorClientEndFrame(int param_1);
uint32_t StuckInClient(uint8_t *param_1);
void WolfRevivePushEnt(int param_1,int param_2);
void WolfReviveBbox(int *param_1);
void ClientEndFrame(uint *param_1);
void BodySink(int param_1);
void BodySink2(int param_1);
void CopyToBodyQue(int param_1);
void SetClientViewAngle(int param_1,float *param_2);
void ClientCleanName(char *param_1,char *param_2,int param_3);
void ClientUserinfoChanged(int param_1);
int ClientVisibleNameLength(char *param_1);
void ClientSpawn(int param_1,int param_2,int param_3,int param_4);
void ClientBegin(int param_1);
void ClientDisconnect(int param_1);
uint32_t ClientConnect(int param_1,int param_2,int param_3);
void ClientStoreSurfaceFlags(int param_1,uint32_t param_2);
int ClientNumbersFromString(char *param_1,long *param_2);
char * ClientNumberFromString(int param_1,char *param_2);
uint32_t ClientIsFlooding(int param_1,int param_2);
void ClientCommand(int param_1);
void player_die(uint *param_1,int param_2,uint *param_3,uint32_t param_4,uint param_5);
uint ClientHasAdren(int param_1);
char * ClientName_part_9(int param_1,char *param_2,int param_3);
char * ClientName(uint param_1);
int ClientForString(char *param_1);

#endif

