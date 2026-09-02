#ifndef NITMOD_WEAPON_INVENTORY_H
#define NITMOD_WEAPON_INVENTORY_H
#include "q_shared.h"
#include "bg_public.h"
typedef struct {
    int ammo;
    int clip;
} nitmodWeaponInventorySlots_t;
/* Original aliases translated to native ET identities. Only the 44 reviewed
 * weapons are supported; unknown IDs/null output return 0 without mutation.
 * Explicit opt-in: does not replace native BG_FindAmmo/ClipForWeapon. */
int NITMOD_WeaponInventorySlots( int weapon, nitmodWeaponInventorySlots_t *slots );
/* Clip mode only; original aliases and native akimbo parity. Negative counts
 * reject without mutation. Not used by active prediction/gameplay yet. */
int NITMOD_SelectRecoveredWeaponClip( const playerState_t *state, int weapon, int *clip );
#endif
