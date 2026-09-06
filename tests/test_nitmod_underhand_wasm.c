#include "cg_local.h"
#include "cg_nitmod_underhand.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    const int suppressed[] = {
        WP_GRENADE_LAUNCHER, WP_GRENADE_PINEAPPLE, WP_DYNAMITE,
        WP_SMOKE_MARKER, WP_LANDMINE, WP_SATCHEL, WP_SMOKE_BOMB,
        WP_BOMB, WP_TRIPMINE, WP_POISON_BOMB, WP_POISON_MINE
    };
    const float pitches[] = {-90.0f, -0.01f, 0.0f, 0.01f, 90.0f};
    int weapon, p, i, cases = 0;
    for(weapon = 0; weapon < WP_NUM_WEAPONS; ++weapon) {
        int member = 0;
        for(i = 0; i < sizeof(suppressed)/sizeof(suppressed[0]); ++i)
            if(weapon == suppressed[i]) member = 1;
        for(p = 0; p < sizeof(pitches)/sizeof(pitches[0]); ++p) {
            assert(CG_NitmodSuppressUnderhandEffects(weapon, pitches[p]) ==
                   (member && pitches[p] > 0.0f));
            ++cases;
        }
    }
    printf("Underhand weapon/pitch cases: %d passed\n", cases);
    return 0;
}
