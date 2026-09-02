#include "nitmod_weapon_recoil.h"
#include "nitmod_weapon_definition.h"
#include <limits.h>

typedef struct { const char **tokens; int index, end; char borrowed[64]; } input_t;
static const char *Next( void *context ) {
    input_t *input = context;
    if( input->index >= input->end ) return NULL;
    strcpy(input->borrowed, input->tokens[input->index++]);
    return input->borrowed;
}
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    const char *tokens[] = { "weaponDef", "{", "both", "{", "classes", "3", "maxammo", "42",
        "recoilDuration", "250", "recoilYaw", "-", "0.5", "recoilPitch", "1.25", "}",
        "both_altweap", "{", "recoilDuration", "100", "recoilYaw", "0.25", "}", "}" };
    const char *bad[] = { "nan", "inf", "1e50", "--1", "0x1", "1x" };
    const char *only[] = { "weaponDef", "{", "both", "{", "recoilPitch", "0", "}", "}" };
    int times[] = { 0, 1, 2, 10, 1000, -1, INT_MIN, INT_MAX };
    nitmodWeaponRecoil_t recoil, saved = { 7, 19, 3.0f, 4.0f };
    ammotable_t ammo, baseline = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    pmoveExt_t state, before, expected;
    input_t input;
    unsigned int mask, bits;
    int i, alt;
    for( alt = 0; alt < 2; ++alt ) {
        input.tokens = tokens; input.index = 0; input.end = 24;
        ammo = baseline; recoil = saved; mask = 77;
        CHECK( NITMOD_ParseWeaponRecoil(Next, &input, alt, &ammo, &mask, &recoil) );
        CHECK( recoil.enabled == 1 && recoil.duration == (alt ? 100 : 250) );
        CHECK( recoil.yaw == (alt ? 0.25f : -0.5f) && recoil.pitch == (alt ? 0.0f : 1.25f) );
        CHECK( mask == (alt ? 0u : 3u) && ammo.maxammo == (alt ? 1 : 42) && ammo.mod == 11 );
        memset(&before, 0x35, sizeof(before));
        for( i = 0; i < 8; ++i ) {
            state = expected = before;
            expected.weapRecoilTime = times[i]; expected.weapRecoilDuration = recoil.duration;
            expected.weapRecoilYaw = (float)(cos((double)times[i]) * recoil.yaw);
            expected.weapRecoilPitch = (float)(fabs(cos((double)times[i])) * recoil.pitch);
            expected.lastRecoilDeltaTime = 0;
            CHECK( NITMOD_ApplyWeaponRecoil(&state, times[i], &recoil) == 1 );
            CHECK( !memcmp(&state, &expected, sizeof(state)) );
        }
        for( i = 0; i < 24; ++i ) {
            input.index = 0; input.end = i; ammo = baseline; recoil = saved; mask = 77;
            CHECK( !NITMOD_ParseWeaponRecoil(Next, &input, alt, &ammo, &mask, &recoil) );
            CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && !memcmp(&recoil, &saved, sizeof(recoil)) && mask == 77 );
        }
    }
    input.end = 24;
    for( i = 0; i < 6; ++i ) {
        tokens[14] = bad[i]; input.index = 0;
        CHECK( !NITMOD_ParseWeaponRecoil(Next, &input, 0, &ammo, &mask, &recoil) );
        CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && !memcmp(&recoil, &saved, sizeof(recoil)) && mask == 77 );
    }
    tokens[14] = "1.25"; tokens[12] = "-0"; input.index = 0;
    CHECK( !NITMOD_ParseWeaponRecoil(Next, &input, 0, &ammo, &mask, &recoil) );
    input.tokens = only; input.end = 8; input.index = 0;
    CHECK( NITMOD_ParseWeaponRecoil(Next, &input, 0, &ammo, &mask, &recoil) );
    CHECK( recoil.enabled == 1 && !recoil.duration && !recoil.yaw && !recoil.pitch );
    state = before;
    CHECK( NITMOD_ApplyWeaponRecoil(&state, 1, &recoil) == -1 );
    CHECK( !memcmp(&state, &before, sizeof(state)) );
    recoil.enabled = 1; recoil.duration = 100; recoil.yaw = 1; recoil.pitch = -2;
    CHECK( NITMOD_ApplyWeaponRecoil(&state, 0, &recoil) == 1 );
    CHECK( state.weapRecoilYaw == 1 && state.weapRecoilPitch == -2 );
    CHECK( NITMOD_ApplyWeaponRecoil(&state, 1, &recoil) == 1 );
    CHECK( fabs(state.weapRecoilYaw - 0.540302306f) < 0.000001 );
    CHECK( fabs(state.weapRecoilPitch + 1.080604612f) < 0.000001 );
    CHECK( NITMOD_ApplyWeaponRecoil(&state, 2, &recoil) == 1 );
    CHECK( fabs(state.weapRecoilYaw + 0.416146837f) < 0.000001 );
    CHECK( fabs(state.weapRecoilPitch + 0.832293673f) < 0.000001 );
    state = before;
    input.index = 0;
    CHECK( NITMOD_ParseWeaponRecoil(Next, &input, 1, &ammo, &mask, &recoil) );
    CHECK( !recoil.enabled && !recoil.duration && !recoil.yaw && !recoil.pitch );
    CHECK( !NITMOD_ApplyWeaponRecoil(&state, 1, &recoil) );
    CHECK( !memcmp(&state, &before, sizeof(state)) );
    recoil = saved; recoil.duration = -1;
    CHECK( NITMOD_ApplyWeaponRecoil(&state, 1, &recoil) == -1 );
    recoil.duration = 1; bits = 0x7fc00000u; memcpy(&recoil.yaw, &bits, sizeof(bits));
    CHECK( NITMOD_ApplyWeaponRecoil(&state, 1, &recoil) == -1 );
    recoil.yaw = 1; bits = 0x7f800000u; memcpy(&recoil.pitch, &bits, sizeof(bits));
    CHECK( NITMOD_ApplyWeaponRecoil(&state, 1, &recoil) == -1 );
    CHECK( NITMOD_ApplyWeaponRecoil(NULL, 1, &recoil) == -1 );
    CHECK( NITMOD_ApplyWeaponRecoil(&state, 1, NULL) == -1 );
    CHECK( !memcmp(&state, &before, sizeof(state)) );
    CHECK( !NITMOD_ParseWeaponRecoil(Next, &input, 0, NULL, &mask, &recoil) );
    CHECK( !NITMOD_ParseWeaponRecoil(Next, &input, 0, &ammo, NULL, &recoil) );
    CHECK( !NITMOD_ParseWeaponRecoil(Next, &input, 0, &ammo, &mask, NULL) );
    return 0;
}
