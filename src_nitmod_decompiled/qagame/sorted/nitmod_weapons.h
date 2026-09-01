#ifndef NITMOD_WEAPONS_H
#define NITMOD_WEAPONS_H

/* Weapons, ammo, missiles, fire logic */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void G_RemoveWeapons(int param_1);
void G_DropLimboAmmo(int param_1);
char G_CorrectSecondaryWeapon(uint32_t param_1,int param_2,int param_3,int param_4,int param_5);
void G_AddClassWeapons(int param_1);
bool G_IsHeavyWeapon(int param_1);
void G_TeamCountWeapons(void);
uint32_t G_IsWeaponDisabled(int param_1,int param_2,int param_3,int param_4);
void G_SetClientWeapons(int param_1,int param_2,int param_3,int param_4);
void G_weaponStats_cmd(uint32_t param_1);
void G_weaponStatsLeaders_cmd(int param_1,int param_2,int param_3);
void G_weaponRankings_cmd(int param_1,int param_2,int param_3);
bool G_WeaponCanGib(uint32_t param_1);
byte G_GetPrimaryWeaponForClient(int param_1);
bool G_CanPickupWeapon(uint param_1,int param_2);
uint32_t Pickup_Ammo(int param_1,int param_2);
void G_DropWeapon(uint32_t *param_1,int param_2);
uint32_t Pickup_Weapon(int param_1,int param_2);
bool G_EmplacedGunIsMountable(int param_1,int param_2);
bool G_EmplacedGunIsRepairable(int param_1,int param_2);
uint32_t G_weapStatIndex_MOD(int param_1);
void Nit_WeapDie(int param_1);
void G_ExplodeMissile(int param_1);
void G_FreeSatchel(int param_1);
void Nit_SatchelDie(int param_1);
void G_TripMineThink(uint32_t *param_1);
void G_LandmineThink(int param_1);
void G_MissileDie(int param_1,int param_2,int *param_3,uint32_t param_4,uint32_t param_5);
void G_MissileImpact(int param_1,int param_2,int param_3);
void G_MissileDownXPAward(int param_1,uint32_t param_2);
void G_RunMissile(uint32_t *param_1);
void G_FlameDamage(int param_1,uint8_t *param_2);
void G_RunFlamechunk(int param_1);
void nitrox_FadeLandmines(int param_1);
void nitrox_FadeSatchels(int param_1);
void nitrox_FadeAirstrikes(int param_1);
uint64_t G_CountTeamLandmines(int param_1);
uint32_t G_SweepForLandmines(float *param_1,float param_2);
int G_FindSatchel(int param_1);
uint32_t G_ExplodeSatchels(int param_1);
void G_TripMinePrime(int param_1);
void G_LandminePrime(int param_1);
bool G_LandmineSnapshotCallback(int param_1,int param_2);
void G_UpdateTeamMapData_LandMine(int param_1,int param_2,int param_3);
bool G_IsAllowedAmmo(int param_1);
void G_AirStrikeExplode(int param_1);
void nitrox_artillerySpotter_Think(int param_1);
void weapon_callSecondPlane(int param_1);
void weapon_smokeBombExplode(int param_1);
long double G_GetWeaponSpread_part_6(int param_1);
void weapon_checkAirStrikeThink1(int param_1);
void weapon_checkAirStrikeThink2(int param_1);
void weapon_callAirStrike(uint32_t *param_1);
uint G_WeaponIsExplosive(uint32_t param_1);
int G_GetWeaponClassForMOD(int param_1);
void Weapon_Knife(uint32_t *param_1);
void Weapon_Medic_Ext(uint32_t *param_1,float *param_2,float *param_3,uint32_t param_4);
void Weapon_Medic(int param_1);
void G_PlaceTripmine(uint32_t *param_1);
void Weapon_MagicAmmo_Ext(uint32_t *param_1,float *param_2,float *param_3,uint32_t param_4);
void Weapon_MagicAmmo(int param_1);
int Weapon_Syringe(uint32_t *param_1);
uint32_t Weapon_Poison(uint32_t *param_1);
bool G_LandmineTriggered(int param_1);
bool G_LandmineArmed(int param_1);
bool G_LandmineUnarmed(int param_1);
int G_LandmineTeam(int param_1);
bool G_LandmineSpotted(int param_1);
uint8_t * Weapon_Engineer(uint32_t *param_1);
bool G_AvailableAirstrikes(int param_1);
void G_AddAirstrikeToCounters(int param_1);
uint32_t weapon_checkAirStrike(int param_1);
void Weapon_Artillery(uint32_t *param_1);
int G_GetWeaponDamage(int param_1);
long double G_GetWeaponSpread(int param_1);
void Bullet_Fire(int param_1,float param_2,uint32_t param_3,uint32_t param_4);
void weapon_gpg40_fire(uint32_t *param_1,uint32_t param_2);
uint32_t weapon_mortar_fire(uint32_t *param_1,uint32_t param_2);
void weapon_grenadelauncher_fire(uint32_t *param_1,int param_2);
void Weapon_Panzerfaust_Fire(uint32_t param_1,float *param_2);
void Weapon_FlamethrowerFire(uint32_t *param_1);
void CalcMuzzlePointForActivate(int param_1);
void CalcMuzzlePoints(int param_1,uint param_2);
void nitrox_tripmine(int param_1);
void FireWeapon(int param_1);
int nitmod_CountTeamTripmines(int param_1);
void nitmod_PoisonGasThink(int param_1);
uint32_t nitmod_AddNewWeapon(uint32_t param_1,int param_2);
void nitrox_RemoveTripmines(int param_1);
int nitrox_GetWeaponSplashDamage(int param_1);
int nitrox_GetWeaponSplashDamageRadius(int param_1);

#endif

