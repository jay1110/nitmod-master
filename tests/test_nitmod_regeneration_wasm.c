#include "nitmod_regeneration.h"
#include <assert.h>
#include <stdio.h>
int main(void) {
    int dm, flags, medics, eligibleMedic, skills, count = 0;
    for(dm = 0; dm < 2; ++dm)
    for(flags = 0; flags < 4; ++flags)
    for(medics = 0; medics < 32; ++medics)
    for(eligibleMedic = 0; eligibleMedic < 2; ++eligibleMedic)
    for(skills = 0; skills < 64; ++skills) {
        /* Original branches: normal medic / DM override, then reward route. */
        int expected = 0;
        if(dm) { if(flags & 2) expected = 1; }
        else if(eligibleMedic) expected = 1;
        if(!expected && (medics & 16) && (skills & 32)) expected = 1;
        assert(!!NITMOD_RegenerationEligible(dm, flags, medics, eligibleMedic, skills) == expected);
        ++count;
    }
    printf("WASM regeneration: %d eligibility combinations passed\n", count);
    return 0;
}
