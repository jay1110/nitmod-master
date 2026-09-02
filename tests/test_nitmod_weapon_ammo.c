#include "q_shared.h"
#include "bg_public.h"
#include "nitmod_weapon_definition.h"
#include <limits.h>
#include <stddef.h>

typedef struct { const char **tokens; int index, end; char borrowed[64]; } input_t;
static const char *Next( void *context ) {
    input_t *input = context;
    if( input->index >= input->end ) return NULL;
    /* Engine-style reusable token storage catches stale key pointers. */
    strcpy(input->borrowed, input->tokens[input->index++]);
    return input->borrowed;
}
typedef struct { const char *name; size_t offset; } field_t;
static const field_t fields[] = {
    { "maxammo", offsetof(ammotable_t, maxammo) },
    { "maxclip", offsetof(ammotable_t, maxclip) },
    { "defaultStartingAmmo", offsetof(ammotable_t, defaultStartingAmmo) },
    { "defaultStartingClip", offsetof(ammotable_t, defaultStartingClip) },
    { "reloadTime", offsetof(ammotable_t, reloadTime) },
    { "fireDelayTime", offsetof(ammotable_t, fireDelayTime) },
    { "nextShotTime", offsetof(ammotable_t, nextShotTime) },
    { "maxHeat", offsetof(ammotable_t, maxHeat) },
    { "coolRate", offsetof(ammotable_t, coolRate) }
};
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    const char *tokens[] = { "weaponDef", "{", "both", "{", "maxammo", "17",
        "classes", "3", "}", "both_altweap", "{", "maxammo", "29", "classes", "5", "}", "}" };
    const char *invalid[] = { "2147483648", "-2147483649", "1.5", "0x10", "--1", "word", "}", "{" };
    const char *empty[] = { "weaponDef", "{", "}" };
    const char *repeated[] = { "weaponDef", "{", "both", "{", "maxammo", "1", "}",
        "both", "{", "maxammo", "-", "7", "maxclip", "2147483647", "}", "}" };
    const char *all[] = { "weaponDef", "{", "both", "{", "maxammo", "10", "maxclip", "20",
        "defaultStartingAmmo", "30", "defaultStartingClip", "40", "reloadTime", "50",
        "fireDelayTime", "60", "nextShotTime", "70", "maxHeat", "80", "coolRate", "90", "}", "}" };
    ammotable_t baseline = { 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111 };
    ammotable_t ammo, expected;
    input_t input;
    unsigned int mask;
    int i, alt, length, bad;
    for( i = 0; i < 9; ++i ) {
        tokens[4] = tokens[11] = fields[i].name;
        for( alt = 0; alt < 2; ++alt ) {
            input.tokens = tokens; input.index = 0; input.end = 17;
            ammo = expected = baseline; mask = 77;
            *(int *)((char *)&expected + fields[i].offset) = alt ? 29 : 17;
            CHECK( NITMOD_ParseWeaponAmmo(Next, &input, alt, &ammo, &mask) );
            CHECK( !memcmp(&ammo, &expected, sizeof(ammo)) && mask == (alt ? 5u : 3u) );
            for( length = 0; length < 17; ++length ) {
                input.index = 0; input.end = length; ammo = baseline; mask = 77;
                CHECK( !NITMOD_ParseWeaponAmmo(Next, &input, alt, &ammo, &mask) );
                CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 77 );
            }
        }
        for( bad = 0; bad < 8; ++bad ) {
            tokens[12] = invalid[bad]; input.index = 0; input.end = 17;
            ammo = baseline; mask = 77;
            CHECK( !NITMOD_ParseWeaponAmmo(Next, &input, 1, &ammo, &mask) );
            CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 77 );
        }
        tokens[12] = "-2147483648"; input.index = 0;
        ammo = expected = baseline;
        *(int *)((char *)&expected + fields[i].offset) = INT_MIN;
        CHECK( NITMOD_ParseWeaponAmmo(Next, &input, 1, &ammo, &mask) );
        CHECK( !memcmp(&ammo, &expected, sizeof(ammo)) );
        tokens[12] = "29";
    }
    input.tokens = repeated; input.index = 0; input.end = 16;
    ammo = baseline;
    CHECK( NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
    CHECK( ammo.maxammo == -7 && ammo.maxclip == INT_MAX && ammo.uses == baseline.uses && !mask );
    input.tokens = all; input.index = 0; input.end = 24;
    ammo = expected = baseline;
    for( i = 0; i < 9; ++i ) *(int *)((char *)&expected + fields[i].offset) = (i + 1) * 10;
    CHECK( NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
    CHECK( !memcmp(&ammo, &expected, sizeof(ammo)) && !mask );
    input.tokens = empty; input.index = 0; input.end = 3;
    ammo = baseline; mask = 77;
    CHECK( NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && !mask );
    input.tokens = tokens; input.end = 17;
    tokens[4] = "damage"; input.index = 0; mask = 77;
    CHECK( !NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 77 );
    tokens[4] = "uses"; input.index = 0;
    CHECK( !NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
    tokens[4] = "mod"; input.index = 0;
    CHECK( !NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, &mask) );
    CHECK( !NITMOD_ParseWeaponAmmo(NULL, &input, 0, &ammo, &mask) );
    CHECK( !NITMOD_ParseWeaponAmmo(Next, &input, 0, NULL, &mask) );
    CHECK( !NITMOD_ParseWeaponAmmo(Next, &input, 0, &ammo, NULL) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 77 );
    return 0;
}
