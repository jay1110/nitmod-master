#include "nitmod_weapon_recoil.h"
#include <float.h>

int NITMOD_ApplyWeaponRecoil( pmoveExt_t *state, int serverTime,
    const nitmodWeaponRecoil_t *recoil ) {
    double phase;
    if( !state || !recoil ) return -1;
    if( !recoil->enabled ) return 0;
    /* Invalid duration would reach division by zero/negative recoil windows
     * in native PM_Weapon. Reject it here, without changing parser semantics. */
    if( recoil->duration <= 0 ||
        !(recoil->yaw >= -FLT_MAX && recoil->yaw <= FLT_MAX) ||
        !(recoil->pitch >= -FLT_MAX && recoil->pitch <= FLT_MAX) ) return -1;
    phase = cos((double)serverTime);
    state->weapRecoilTime = serverTime;
    state->weapRecoilDuration = recoil->duration;
    /* Original x87 multiplies before storing float: do not round cos first. */
    state->weapRecoilYaw = (float)(phase * recoil->yaw);
    state->weapRecoilPitch = (float)(fabs(phase) * recoil->pitch);
    state->lastRecoilDeltaTime = 0;
    return 1;
}
