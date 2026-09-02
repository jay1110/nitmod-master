#include "q_shared.h"
#include "bg_public.h"
#include "nitmod_weapon_definition.h"
#include <limits.h>

typedef struct {
    const char **tokens;
    int count, reads, fill, depth;
    char borrowed[64];
} input_t;
static const char *Next( void *context ) {
    input_t *input = context;
    const char *token;
    int index = input->reads++;
    if( input->tokens ) {
        if( index >= input->count ) return NULL;
        token = input->tokens[index];
    } else {
        /* Generate large streams without a large stack or token allocation. */
        if( index == 0 ) token = "weaponDef";
        else if( index == 1 ) token = "{";
        else if( index == 2 ) token = "client";
        else if( index < 3 + input->depth ) token = "{";
        else if( index < 3 + input->depth + input->fill ) token = "opaque";
        else if( index < 4 + 2 * input->depth + input->fill ) token = "}";
        else return NULL;
    }
    strcpy(input->borrowed, token);
    return input->borrowed;
}
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    const char *tokens[] = { "weaponDef", "{", "both", "{", "classes", "-", "2147483648", "}", "}" };
    const char *bad[] = { "2147483649", "4294967295", "4294967296", "-0", "-1", "+0", "-", "", "1.0", "0x1" };
    const char *keys[] = { "maxammo", "maxclip", "defaultStartingAmmo", "defaultStartingClip",
        "reloadTime", "fireDelayTime", "nextShotTime", "maxHeat", "coolRate" };
    input_t input;
    ammotable_t ammo, baseline = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    unsigned int mask;
    int i, j;
    memset(&input, 0, sizeof(input)); input.tokens = tokens; input.count = 9;
    mask = 77;
    CHECK( NITMOD_ParseWeaponClassMask(Next, &input, 0, &mask) );
    CHECK( mask == (unsigned int)INT_MIN && input.reads == 9 );
    for( i = 0; i < 10; ++i ) {
        tokens[6] = bad[i]; input.reads = 0; mask = 77;
        CHECK( !NITMOD_ParseWeaponClassMask(Next, &input, 0, &mask) && mask == 77 );
    }
    tokens[6] = "0002147483648";
    for( i = 0; i < 9; ++i ) {
        tokens[4] = keys[i]; input.reads = 0; ammo = baseline; mask = 77;
        CHECK( NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
        CHECK( !mask && ammo.uses == 2 && ammo.mod == 11 );
        switch( i ) {
        case 0: CHECK(ammo.maxammo == INT_MIN); break;
        case 1: CHECK(ammo.maxclip == INT_MIN); break;
        case 2: CHECK(ammo.defaultStartingAmmo == INT_MIN); break;
        case 3: CHECK(ammo.defaultStartingClip == INT_MIN); break;
        case 4: CHECK(ammo.reloadTime == INT_MIN); break;
        case 5: CHECK(ammo.fireDelayTime == INT_MIN); break;
        case 6: CHECK(ammo.nextShotTime == INT_MIN); break;
        case 7: CHECK(ammo.maxHeat == INT_MIN); break;
        case 8: CHECK(ammo.coolRate == INT_MIN); break;
        }
        for( j = 0; j < 9; ++j ) {
            input.reads = 0; input.count = j; ammo = baseline; mask = 77;
            CHECK( !NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
            CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 77 );
        }
        input.count = 9;
    }
    input.tokens = NULL; input.depth = 64; input.fill = 0; input.reads = 0;
    CHECK( NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
    CHECK( input.reads == 132 && !mask );
    input.depth = 65; input.reads = 0; mask = 77;
    CHECK( !NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
    CHECK( mask == 77 && input.reads == 68 );
    input.depth = 1; input.fill = 65530; input.reads = 0;
    CHECK( NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
    CHECK( input.reads == 65536 && !mask );
    input.fill = 65531; input.reads = 0; mask = 77;
    CHECK( !NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
    CHECK( input.reads == 65536 && mask == 77 );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) );
    return 0;
}
