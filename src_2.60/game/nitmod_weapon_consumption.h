#ifndef NITMOD_WEAPON_CONSUMPTION_H
#define NITMOD_WEAPON_CONSUMPTION_H
#include "q_shared.h"
#include "bg_public.h"
/* Apply the original subtraction/exact-zero refill to a resolved native
 * clip slot. The caller owns BG_FindClipForWeapon/Akimbo selection and the
 * corresponding ammo record; this helper does not infer aliases or amount.
 * Returns 1 on success, 0 on invalid input (no mutation). Negative/infinite
 * clips, negative amounts, overspending and negative refill values reject.
 * No Cvar access, ammoTableMP mutation, inventory changes or events. */
int NITMOD_ConsumeWeaponClip( playerState_t *state, int weapon, int clip,
    int amount, int warMode, unsigned int noReload,
    const ammotable_t *clipAmmo );
#endif
