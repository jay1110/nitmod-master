#include "nitmod_script_bits.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
int main(void) {
    int bit;
    assert(sizeof(unsigned int) == 4);
    assert(NITMOD_ScriptBitMask(31) == 0x80000000u);
    assert(NITMOD_ScriptBitMask(-1) == 0x80000000u);
    assert(NITMOD_ScriptBitMask(32) == 1u);
    assert(NITMOD_ScriptBitMask(INT_MIN) == 1u);
    for(bit = -128; bit <= 128; ++bit) {
        unsigned int mask = NITMOD_ScriptBitMask(bit);
        unsigned int expected = 1u;
        int i, count = bit % 32;
        if(count < 0) count += 32;
        for(i = 0; i < count; ++i) expected *= 2u;
        assert(mask == expected);
        assert((mask & ~mask) == 0);
    }
    puts("WASM script bit masks: signed endpoints and 257 shift cases passed");
    return 0;
}
