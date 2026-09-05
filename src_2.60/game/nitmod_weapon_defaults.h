#ifndef NITMOD_WEAPON_DEFAULTS_H
#define NITMOD_WEAPON_DEFAULTS_H
#include "q_shared.h"
#include "bg_public.h"
/* Copy ten hash-verified original ammo/timing/consumption defaults.
 * Native mod remains caller-owned and unchanged. Returns 1 on success,
 * 0 for unsupported identity/null output, without changing the output.
 * Does not mutate ammoTableMP or register a weapon. */
int NITMOD_WeaponAmmoDefaults( int weapon, ammotable_t *ammo );
/* Original ammo-record +0x38, kept outside native ammotable_t. */
int NITMOD_WeaponAutoReloadDefault( int weapon, int *requiresSetting );
/* Original +40/+44/+48, separate from native ammo record layout. */
int NITMOD_WeaponBlastDefaults(int weapon, int *damage, int *splash, int *radius);
#endif
