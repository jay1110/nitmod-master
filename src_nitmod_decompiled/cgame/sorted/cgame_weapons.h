#ifndef CGAME_WEAPONS_H
#define CGAME_WEAPONS_H

/* Client weapon presentation and selection */

#include "nitmod_types.h"
#include "nitmod_globals.h"

uint32_t CG_RegisterWeaponFromWeaponFile(int param_1,int param_2);
void CG_RegisterWeapon(uint param_1,int param_2);
uint32_t CG_WeaponSelectable(int param_1);
uint32_t CG_WeaponIndex(int param_1,int *param_2,uint32_t *param_3);
void CG_WeaponBank_f(void);
void CG_Weapon_f(void);
void CG_WeaponFireRecoil(uint32_t param_1);
void CG_FireWeapon(int *param_1,int param_2);

#endif

