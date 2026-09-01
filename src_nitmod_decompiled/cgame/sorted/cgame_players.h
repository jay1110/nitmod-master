#ifndef CGAME_PLAYERS_H
#define CGAME_PLAYERS_H

/* Client/player model and character information */

#include "nitmod_types.h"
#include "nitmod_globals.h"

uint32_t CG_PlayerSelected(void);
bool CG_PlayerSeesItem(int param_1,int param_2,uint32_t param_3);
uint32_t CG_CustomSound(int param_1);
int CG_PlayerSFFromPos(int param_1,int *param_2);
int CG_PlayerNFFromPos(int param_1,int *param_2);
void CG_PlayerFloatSprite(int *param_1,uint32_t param_2,int param_3,int param_4);
void CG_PlayerClassForClientinfo(int param_1,int param_2);
void CG_PlayerAngles(uint8_t *param_1,uint32_t *param_2,uint32_t *param_3,uint32_t param_4);
void CG_PlayerFloatText(int param_1,uint32_t param_2,int param_3);
void CG_NewClientInfo(int param_1,char *param_2);
void CG_Player(uint *param_1);

#endif

