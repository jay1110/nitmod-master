#include <limits.h>
#include "nitmod_weapon_limits.h"

nitmodWeaponLimit_t NITMOD_EvaluateWeaponLimits( const nitmodWeaponLimitInput_t *input ) {
    double product, threshold, share;
    if( !input || input->teamSize < 0 || input->weaponCount < 0 ||
        (input->isPanzer && !input->isHeavy) ) return NITMOD_LIMIT_INVALID;
    if( input->isHeavy ) {
        /* Original integer multiplication precedes x87 scaling. Reject its
         * overflowing domain deliberately instead of reproducing wrapping. */
        product = (double)input->teamSize * input->heavyPercent;
        if( product < INT_MIN || product > INT_MAX ) return NITMOD_LIMIT_INVALID;
        threshold = product * (double)0.01f;
        /* For integer weaponCount, count >= ceil(x) iff count >= x.
         * Avoid dependence on host floating-point rounding modes. */
        if( (double)input->weaponCount >= threshold ) return NITMOD_LIMIT_HEAVY;
        if( input->isPanzer ) {
            if( input->maxClients <= 0 ) return NITMOD_LIMIT_INVALID;
            share = (double)input->teamSize / ((double)input->maxClients * 0.5);
            if( share <= (double)input->panzerPercent * (double)0.01f )
                return NITMOD_LIMIT_PANZER_TEAM;
        }
    }
    if( input->fixedCap != -1 && input->weaponCount >= input->fixedCap ) return NITMOD_LIMIT_FIXED;
    return NITMOD_LIMIT_NONE;
}
