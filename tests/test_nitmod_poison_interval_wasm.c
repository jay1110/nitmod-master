#include "../src_2.60/game/g_nitmod_weapon_definition.c"
#include <assert.h>
#include <stdio.h>
int main(void) {
    int i;
    static const int values[] = {0, 50, 750, 1500, 2001};
    assert(G_NITMOD_PoisonInterval(50) == 50);
    for(i = 0; i < 5; ++i) {
        weaponOptions[WP_POISON_SYRINGE].spread = values[i];
        pickupDefinitionState[WP_POISON_SYRINGE] = 1;
        assert(G_NITMOD_PoisonInterval(1500) == (values[i] ? values[i] : 1500));
        pickupDefinitionState[WP_POISON_SYRINGE] = -1;
        assert(G_NITMOD_PoisonInterval(50) == 50);
    }
    puts("WASM poison interval: cached spread override, zero fallback and failed records passed");
    return 0;
}
