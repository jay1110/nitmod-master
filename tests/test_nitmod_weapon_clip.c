#include "nitmod_weapon_clip.h"
#include <limits.h>
static int aliases[WP_NUM_WEAPONS];
weapon_t BG_FindClipForWeapon( weapon_t weapon ) { return (weapon_t)aliases[weapon]; }
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    int weapons[] = { WP_AKIMBO_COLT, WP_AKIMBO_LUGER, WP_AKIMBO_SILENCEDCOLT, WP_AKIMBO_SILENCEDLUGER };
    int sides[] = { WP_COLT, WP_LUGER, WP_COLT, WP_LUGER };
    playerState_t state, expected, before;
    ammotable_t ammo[WP_NUM_WEAPONS];
    int i, a, b, selected, want;
    memset(ammo, 0, sizeof(ammo));
    for( i = 0; i < WP_NUM_WEAPONS; ++i ) {
        aliases[i] = i;
        ammo[i].defaultStartingClip = i;
    }
    memset(&before, 0, sizeof(before));
    for( i = 0; i < 4; ++i ) {
        CHECK( BG_AkimboSidearm(weapons[i]) == sides[i] && BG_IsAkimboWeapon(weapons[i]) );
        for( a = 0; a <= 16; ++a ) for( b = 0; b <= 16; ++b ) {
            state = before; state.ammoclip[weapons[i]] = a; state.ammoclip[sides[i]] = b;
            want = a && (!b || (a + b) % 2 == 0) ? weapons[i] : sides[i];
            expected = state;
            CHECK( NITMOD_SelectWeaponClip(&state, weapons[i], &selected) && selected == want );
            CHECK( !memcmp(&state, &expected, sizeof(state)) );
            if( a || b ) {
                if( --expected.ammoclip[want] == 0 ) expected.ammoclip[want] = ammo[want].defaultStartingClip;
                CHECK( NITMOD_ConsumeSelectedWeaponClip(&state, weapons[i], 1, 0, 1, ammo, WP_NUM_WEAPONS) );
                CHECK( !memcmp(&state, &expected, sizeof(state)) );
            }
        }
        CHECK( BG_AkimboFireSequence(weapons[i], INT_MAX, INT_MAX) );
        CHECK( !BG_AkimboFireSequence(weapons[i], INT_MAX, INT_MAX - 1) );
        CHECK( BG_AkimboFireSequence(weapons[i], INT_MIN, INT_MIN) );
    }
    CHECK( !BG_IsAkimboWeapon(WP_COLT) && BG_AkimboSidearm(WP_COLT) == WP_NONE );
    CHECK( !BG_AkimboFireSequence(WP_COLT, 2, 2) );
    state = before; state.ammoclip[WP_GARAND] = 3;
    aliases[WP_GARAND_SCOPE] = WP_GARAND;
    CHECK( NITMOD_SelectWeaponClip(&state, WP_GARAND_SCOPE, &selected) && selected == WP_GARAND );
    expected = state; expected.ammoclip[WP_GARAND] = 2;
    CHECK( NITMOD_ConsumeSelectedWeaponClip(&state, WP_GARAND_SCOPE, 1, 0, 0, ammo, WP_NUM_WEAPONS) );
    CHECK( !memcmp(&state, &expected, sizeof(state)) );
    before = state; selected = 77;
    CHECK( !NITMOD_SelectWeaponClip(NULL, WP_COLT, &selected) );
    CHECK( !NITMOD_SelectWeaponClip(&state, -1, &selected) );
    CHECK( !NITMOD_SelectWeaponClip(&state, WP_NUM_WEAPONS, &selected) );
    CHECK( !NITMOD_SelectWeaponClip(&state, WP_COLT, NULL) );
    CHECK( selected == 77 );
    aliases[WP_COLT] = WP_NUM_WEAPONS;
    CHECK( !NITMOD_SelectWeaponClip(&state, WP_COLT, &selected) && selected == 77 );
    aliases[WP_COLT] = WP_COLT;
    state.ammoclip[WP_COLT] = -1; before = state;
    CHECK( !NITMOD_SelectWeaponClip(&state, WP_AKIMBO_COLT, &selected) && selected == 77 );
    CHECK( !NITMOD_ConsumeSelectedWeaponClip(&state, WP_GARAND_SCOPE, 1, 0, 0, ammo, WP_GARAND) );
    CHECK( !NITMOD_ConsumeSelectedWeaponClip(&state, WP_GARAND_SCOPE, 1, 0, 0, NULL, WP_NUM_WEAPONS) );
    CHECK( !memcmp(&state, &before, sizeof(state)) );
    return 0;
}
