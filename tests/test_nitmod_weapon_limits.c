#include <limits.h>
#include <stdio.h>
#include "nitmod_weapon_limits.h"
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
int main( void ) {
    nitmodWeaponLimitInput_t input = {0};
    int size, percent, count, cap, expected;
    input.isHeavy = 1; input.fixedCap = -1;
    for( size = 0; size <= 64; size++ ) for( percent = 0; percent <= 100; percent++ )
    for( count = 0; count <= 64; count++ ) {
        input.teamSize = size; input.heavyPercent = percent; input.weaponCount = count;
        expected = count >= (size * percent + 99) / 100 ? NITMOD_LIMIT_HEAVY : NITMOD_LIMIT_NONE;
        CHECK( NITMOD_EvaluateWeaponLimits(&input) == expected );
    }
    input.isHeavy = 0;
    for( cap = -3; cap <= 64; cap++ ) for( count = 0; count <= 64; count++ ) {
        input.fixedCap = cap; input.weaponCount = count;
        expected = cap != -1 && count >= cap ? NITMOD_LIMIT_FIXED : NITMOD_LIMIT_NONE;
        CHECK( NITMOD_EvaluateWeaponLimits(&input) == expected );
    }
    input.isHeavy = input.isPanzer = 1;
    input.teamSize = 1; input.weaponCount = 0; input.heavyPercent = 100;
    input.maxClients = 10; input.panzerPercent = 20; input.fixedCap = -1;
    /* Original 0.01f is slightly below 1/100: exact mathematical equality
     * here does NOT deny the panzer. Do not replace it with integer ratios. */
    CHECK( NITMOD_EvaluateWeaponLimits(&input) == NITMOD_LIMIT_NONE );
    input.panzerPercent = 21;
    CHECK( NITMOD_EvaluateWeaponLimits(&input) == NITMOD_LIMIT_PANZER_TEAM );
    input.fixedCap = 0;
    CHECK( NITMOD_EvaluateWeaponLimits(&input) == NITMOD_LIMIT_PANZER_TEAM );
    input.heavyPercent = 0;
    CHECK( NITMOD_EvaluateWeaponLimits(&input) == NITMOD_LIMIT_HEAVY );
    input.heavyPercent = 100; input.panzerPercent = 0;
    CHECK( NITMOD_EvaluateWeaponLimits(&input) == NITMOD_LIMIT_FIXED );
    input.maxClients = 0;
    CHECK( NITMOD_EvaluateWeaponLimits(&input) == NITMOD_LIMIT_INVALID );
    input.teamSize = INT_MAX; input.heavyPercent = 2;
    CHECK( NITMOD_EvaluateWeaponLimits(&input) == NITMOD_LIMIT_INVALID );
    input.teamSize = -1;
    CHECK( NITMOD_EvaluateWeaponLimits(&input) == NITMOD_LIMIT_INVALID );
    CHECK( NITMOD_EvaluateWeaponLimits(NULL) == NITMOD_LIMIT_INVALID );
    return 0;
}
