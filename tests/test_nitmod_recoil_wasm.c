#include "cg_local.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
cg_t cg;
void CG_WeaponFireRecoil(int weapon);
int main(void) {
    int weapon, seed, count = 0;
    for(weapon = 0; weapon < WP_NUM_WEAPONS; ++weapon)
    for(seed = 0; seed < 16; ++seed) {
        float pitch = 0, yaw = 0, expected;
        int handled = 1, next;
        srand(seed);
        switch(weapon) {
        case WP_LUGER: case WP_COLT: case WP_SILENCER: case WP_SILENCED_COLT:
        case WP_AKIMBO_LUGER: case WP_AKIMBO_COLT:
        case WP_AKIMBO_SILENCEDLUGER: case WP_AKIMBO_SILENCEDCOLT: case WP_PANZERFAUST: break;
        case WP_GARAND: case WP_KAR98: case WP_CARBINE: case WP_K43: pitch = -2; yaw = 1; break;
        case WP_GARAND_SCOPE: case WP_K43_SCOPE: pitch = -.3f; break;
        case WP_MP40: case WP_THOMPSON: case WP_STEN: case WP_FG42: case WP_FG42SCOPE:
        case WP_MOBILE_MG42: case WP_MOBILE_MG42_SET: pitch = -(rand() % 3 + 1) * .3f; yaw = .6f; break;
        default: handled = 0;
        }
        expected = handled ? (((rand() & 32767) / 32767.0f - .5f) * 2) * yaw * 30 : 22;
        next = rand();
        srand(seed);
        cg.kickAVel[0] = 11; cg.kickAVel[1] = 22; cg.kickAVel[2] = 33;
        cg.recoilPitch = 7;
        CG_WeaponFireRecoil(weapon);
        assert(fabsf(cg.kickAVel[0] - (handled ? pitch * 30 : 11)) < .0001f);
        assert(fabsf(cg.kickAVel[1] - expected) < .0001f);
        assert(fabsf(cg.kickAVel[2] - (handled ? -expected : 33)) < .0001f);
        assert(cg.recoilPitch == 7);
        assert(rand() == next);
        ++count;
    }
    printf("Recoil: %d weapon/seed cases passed\n", count);
    return 0;
}
