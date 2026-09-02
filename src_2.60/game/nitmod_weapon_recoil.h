#ifndef NITMOD_WEAPON_RECOIL_H
#define NITMOD_WEAPON_RECOIL_H
#include "q_shared.h"
#include "bg_public.h"
typedef struct nitmodWeaponRecoil_s {
    int enabled;
    int duration;
    float yaw;
    float pitch;
} nitmodWeaponRecoil_t;
/* Apply only the original custom-recoil branch to native movement state.
 * 1 = applied, 0 = disabled, -1 = invalid. Non-applied calls change nothing.
 * No random numbers, weapon lookup, clock access or gameplay hook. */
int NITMOD_ApplyWeaponRecoil( pmoveExt_t *state, int serverTime,
    const nitmodWeaponRecoil_t *recoil );
#endif
