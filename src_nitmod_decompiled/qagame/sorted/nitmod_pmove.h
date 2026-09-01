#ifndef NITMOD_PMOVE_H
#define NITMOD_PMOVE_H

/* Player movement (Pmove / PM_*) */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void PM_ReloadClip(void);
void PM_StartWeaponAnim(uint param_1);
void PM_DropTimers(void);
void PM_Friction(void);
void PM_SetWaterLevel(void);
void PM_SetMovementDir(void);
void PM_FootstepForSurface(void);
long double PM_CmdScale_isra_0(char param_1,char param_2,char param_3);
void PM_TraceAllLegs_constprop_8(int param_1,float *param_2,float *param_3);
void PM_CheckDuck(void);
void PM_WaterMove(void);
void PM_AirMove(void);
void PM_BeginWeaponReload(int param_1);
void PM_AddEvent(uint32_t param_1);
void PM_AddEventExt(uint32_t param_1,uint32_t param_2);
bool PM_IdleAnimForWeapon(int param_1);
uint32_t PM_AltSwitchFromForWeapon(void);
int PM_AltSwitchToForWeapon(int param_1);
int PM_AttackAnimForWeapon(int param_1);
uint32_t PM_LastAttackAnimForWeapon(int param_1);
int PM_ReloadAnimForWeapon(int param_1);
uint32_t PM_RaiseAnimForWeapon(int param_1);
uint32_t PM_DropAnimForWeapon(int param_1);
void PM_AddTouchEnt(int param_1);
void PM_ContinueWeaponAnim(uint param_1);
void PM_ClipVelocity(float *param_1,float *param_2,float *param_3,float param_4);
void PM_TraceAllLegs(int param_1,uint32_t param_2,float *param_3,float *param_4);
void PM_GroundTrace(void);
void PM_TraceAll(int param_1,float *param_2,float *param_3);
void PM_BeginWeaponChange(int param_1,int param_2,int param_3);
void PM_CheckForReload(int param_1);
void PM_WeaponUseAmmo(int param_1,int param_2);
uint32_t PM_WeaponAmmoAvailable(int param_1);
bool PM_WeaponClipEmpty(uint32_t param_1);
void PM_CoolWeapons(void);
void PM_AdjustAimSpreadScale(void);
uint PM_AltFire(void);
void PM_Weapon(void);
bool PM_AltFiring(int param_1);
void PM_UpdateLean(int param_1,int param_2,int param_3);
void PM_UpdateFlyLean(int param_1,float param_2);
void PM_UpdateViewAngles(int param_1,int param_2,int param_3,uint32_t param_4,uint32_t param_5);
void PM_CheckLadderMove(void);
void PM_LadderMove(void);
void PM_Sprint(void);
void PM_CheckAttack(void);
void PmoveSingle(int *param_1);
uint Pmove(int *param_1);
void PmovePredict(int *param_1,uint32_t param_2);
bool PM_SlideMove(int param_1);
void PM_StepSlideMove(uint32_t param_1);

#endif

