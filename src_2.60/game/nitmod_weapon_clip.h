#ifndef NITMOD_WEAPON_CLIP_H
#define NITMOD_WEAPON_CLIP_H
#include "q_shared.h"
#include "bg_public.h"
/* Clip-mode adapter only: noWeapClips/reserve-ammo mode is not handled.
 * Uses native item aliases and akimbo selection. Invalid/negative counts
 * reject without changing the state or output. */
int NITMOD_SelectWeaponClip( const playerState_t *state, int weapon, int *clip );
int NITMOD_ConsumeSelectedWeaponClip( playerState_t *state, int weapon,
    int amount, int warMode, unsigned int noReload,
    const ammotable_t *ammoTable, int ammoSlots );
#endif
