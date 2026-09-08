#ifndef NITMOD_WEAPON_CHARGE_H
#define NITMOD_WEAPON_CHARGE_H
#include "nitmod_skills.h"

/* Original FireWeapon/BG_CheckCharge table selection. The server selects the
 * reward mask below; prediction selects it by the current player class. */
static int NITMOD_WeaponChargeTable(int weapon, nitmodSkillTable_t *table, int *skill) {
 switch(weapon) {
 case WP_PANZERFAUST: *table=NITMOD_TABLE_PANZER; *skill=SK_HEAVY_WEAPONS; break;
 case WP_MORTAR_SET: *table=NITMOD_TABLE_MORTAR; *skill=SK_HEAVY_WEAPONS; break;
 case WP_DYNAMITE: case WP_BOMB: *table=NITMOD_TABLE_DYNAMITE; *skill=SK_EXPLOSIVES_AND_CONSTRUCTION; break;
 case WP_LANDMINE: case WP_POISON_MINE: *table=NITMOD_TABLE_LANDMINE; *skill=SK_EXPLOSIVES_AND_CONSTRUCTION; break;
 case WP_TRIPMINE: *table=NITMOD_TABLE_TRIPMINE; *skill=SK_EXPLOSIVES_AND_CONSTRUCTION; break;
 case WP_GPG40: case WP_M7: *table=NITMOD_TABLE_RIFLENADE; *skill=SK_EXPLOSIVES_AND_CONSTRUCTION; break;
 case WP_SMOKE_MARKER: *table=NITMOD_TABLE_ARTILLERY; *skill=SK_SIGNALS; break;
 case WP_AMMO: *table=NITMOD_TABLE_AMMO; *skill=SK_SIGNALS; break;
 case WP_MEDKIT: *table=NITMOD_TABLE_HEALTH; *skill=SK_FIRST_AID; break;
 case WP_MEDIC_ADRENALINE: *table=NITMOD_TABLE_ADRENALINE; *skill=SK_FIRST_AID; break;
 case WP_SMOKE_BOMB: case WP_POISON_BOMB: *table=NITMOD_TABLE_SMOKE; *skill=SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS; break;
 case WP_SATCHEL: *table=NITMOD_TABLE_SATCHEL; *skill=SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS; break;
 default: return 0;
 }
 return 1;
}
#endif
