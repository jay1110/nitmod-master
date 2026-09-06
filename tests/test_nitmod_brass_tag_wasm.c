#include "cg_local.h"
#include "cg_nitmod_brass.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
int main(void) {
    int view, dual, predicted, entity, cases = 0;
    for(view=0; view<2; ++view)
    for(dual=0; dual<2; ++dual)
    for(predicted=0; predicted<2; ++predicted)
    for(entity=0; entity<2; ++entity) {
        const char *expected;
        if(view) expected = dual && predicted ? "tag_brass2" : "tag_brass";
        else expected = dual && !entity ? "tag_weapon2" : "tag_weapon";
        assert(!strcmp(expected, CG_NitmodBrassTag(view,dual,predicted,entity)));
        ++cases;
    }
    printf("Brass tag routing: %d cases passed\n", cases);
    {
        int nitmod, local, heavy, f;
        const int flags[] = {0, EF_MG42_ACTIVE, EF_AAGUN_ACTIVE,
                             EF_MG42_ACTIVE | EF_AAGUN_ACTIVE, EF_FIRING};
        cases = 0;
        for(nitmod=0; nitmod<2; ++nitmod)
        for(local=0; local<2; ++local)
        for(heavy=0; heavy<2; ++heavy)
        for(f=0; f<5; ++f) {
            int expected = !heavy && (f == 0 || f == 4) && (nitmod || local);
            assert(CG_NitmodUseTagBrass(nitmod,local,heavy,flags[f]) == expected);
            ++cases;
        }
        printf("Brass dispatch routing: %d cases passed\n", cases);
    }
    return 0;
}
