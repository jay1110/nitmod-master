#include "nitmod_weapon_consumption.h"

int NITMOD_ConsumeWeaponClip( playerState_t *state, int weapon, int clip,
    int amount, int warMode, unsigned int noReload,
    const ammotable_t *clipAmmo ) {
    int remaining, refill;
    if( !state || !clipAmmo || weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS ||
        clip <= WP_NONE || clip >= WP_NUM_WEAPONS || amount < 0 ) return 0;
    if( state->ammoclip[clip] < 0 || amount > state->ammoclip[clip] ) return 0;
    remaining = state->ammoclip[clip] - amount;
    refill = (weapon == WP_PANZERFAUST && warMode == 1) || (noReload & 1u);
    if( remaining == 0 && refill ) {
        if( clipAmmo->defaultStartingClip < 0 ) return 0;
        remaining = clipAmmo->defaultStartingClip;
    }
    state->ammoclip[clip] = remaining;
    return 1;
}
