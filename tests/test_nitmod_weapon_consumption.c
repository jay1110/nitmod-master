#include "nitmod_weapon_consumption.h"
#include <limits.h>
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    playerState_t state, baseline, expected;
    ammotable_t ammo;
    unsigned int flags[] = { 0, 1, 2, 3, 0x100, 0x101, UINT_MAX };
    int weapon, war, f, amount, rounds;
    memset(&baseline, 0x35, sizeof(baseline));
    memset(&ammo, 0, sizeof(ammo));
    ammo.defaultStartingClip = 7;
    ammo.maxclip = 99; /* refill uses starting clip, not capacity */
    for( weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon )
    for( war = -1; war <= 4; ++war )
    for( f = 0; f < 7; ++f )
    for( rounds = 0; rounds <= 3; ++rounds )
    for( amount = 0; amount <= rounds; ++amount ) {
        state = expected = baseline;
        state.ammoclip[WP_LUGER] = rounds;
        expected.ammoclip[WP_LUGER] = rounds - amount;
        if( rounds == amount && ((flags[f] & 1u) || (weapon == WP_PANZERFAUST && war == 1)) )
            expected.ammoclip[WP_LUGER] = 7;
        CHECK( NITMOD_ConsumeWeaponClip(&state, weapon, WP_LUGER, amount, war, flags[f], &ammo) );
        CHECK( !memcmp(&state, &expected, sizeof(state)) );
    }
    state = baseline; state.ammoclip[WP_LUGER] = INT_MAX; expected = state;
    CHECK( NITMOD_ConsumeWeaponClip(&state, WP_LUGER, WP_LUGER, INT_MAX, 0, 0, &ammo) );
    expected.ammoclip[WP_LUGER] = 0;
    CHECK( !memcmp(&state, &expected, sizeof(state)) );
    baseline.ammoclip[WP_LUGER] = 2; state = baseline;
    CHECK( !NITMOD_ConsumeWeaponClip(&state, WP_LUGER, WP_LUGER, 3, 0, 1, &ammo) );
    CHECK( !NITMOD_ConsumeWeaponClip(&state, WP_LUGER, WP_LUGER, -1, 0, 1, &ammo) );
    CHECK( !NITMOD_ConsumeWeaponClip(&state, WP_LUGER, WP_LUGER, INT_MIN, 0, 1, &ammo) );
    CHECK( !NITMOD_ConsumeWeaponClip(&state, WP_NONE, WP_LUGER, 1, 0, 1, &ammo) );
    CHECK( !NITMOD_ConsumeWeaponClip(&state, WP_NUM_WEAPONS, WP_LUGER, 1, 0, 1, &ammo) );
    CHECK( !NITMOD_ConsumeWeaponClip(&state, WP_LUGER, -1, 1, 0, 1, &ammo) );
    CHECK( !NITMOD_ConsumeWeaponClip(&state, WP_LUGER, WP_NUM_WEAPONS, 1, 0, 1, &ammo) );
    CHECK( !NITMOD_ConsumeWeaponClip(NULL, WP_LUGER, WP_LUGER, 1, 0, 1, &ammo) );
    CHECK( !NITMOD_ConsumeWeaponClip(&state, WP_LUGER, WP_LUGER, 1, 0, 1, NULL) );
    ammo.defaultStartingClip = -1;
    CHECK( !NITMOD_ConsumeWeaponClip(&state, WP_LUGER, WP_LUGER, 2, 0, 1, &ammo) );
    CHECK( !memcmp(&state, &baseline, sizeof(state)) );
    /* Bad refill defaults are irrelevant unless the refill branch executes. */
    CHECK( NITMOD_ConsumeWeaponClip(&state, WP_LUGER, WP_LUGER, 1, 0, 1, &ammo) );
    CHECK( state.ammoclip[WP_LUGER] == 1 );
    state = baseline; state.ammoclip[WP_LUGER] = -1; expected = state;
    CHECK( !NITMOD_ConsumeWeaponClip(&state, WP_LUGER, WP_LUGER, 1, 0, 1, &ammo) );
    CHECK( !memcmp(&state, &expected, sizeof(state)) );
    state = baseline; ammo.defaultStartingClip = 0;
    CHECK( NITMOD_ConsumeWeaponClip(&state, WP_LUGER, WP_LUGER, 2, 0, 1, &ammo) );
    CHECK( !state.ammoclip[WP_LUGER] );
    return 0;
}
