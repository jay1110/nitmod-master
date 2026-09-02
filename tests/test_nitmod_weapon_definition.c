#include <stddef.h>
#include "nitmod_weapon_definition.h"
typedef struct { const char **tokens; int index, end; } input_t;
static const char *Next( void *context ) {
    input_t *input = context;
    return input->index < input->end ? input->tokens[input->index++] : NULL;
}
int main( void ) {
    const char *valid[] = { "weaponDef", "{", "client", "{", "classes", "99", "nested", "{", "x", "}", "}",
        "both", "{", "classes", "3", "classes", "5", "}", "both_altweap", "{", "classes", "-", "1", "}", "}" };
    const char *empty[] = { "weaponDef", "{", "}" };
    const char *unknown[] = { "weaponDef", "{", "both", "{", "name", "classes", "}", "}" };
    const char *overflow[] = { "weaponDef", "{", "both", "{", "classes", "2147483648", "}", "}" };
    const char *badSign[] = { "weaponDef", "{", "both", "{", "classes", "-", "-1", "}", "}" };
    input_t input;
    unsigned int mask;
    int i, alt;
    for( alt = 0; alt < 2; alt++ ) {
        input.tokens = valid; input.index = 0; input.end = 25; mask = 77;
        if( !NITMOD_ParseWeaponClassMask(Next, &input, alt, &mask) || mask != (alt ? ~0u : 5u) ) return 1;
        for( i = 0; i < 25; i++ ) {
            input.index = 0; input.end = i; mask = 77;
            if( NITMOD_ParseWeaponClassMask(Next, &input, alt, &mask) || mask != 77 ) return 2;
        }
    }
    input.tokens = empty; input.index = 0; input.end = 3;
    if( !NITMOD_ParseWeaponClassMask(Next, &input, 0, &mask) || mask ) return 3;
    input.tokens = unknown; input.index = 0; input.end = 8; mask = 77;
    if( NITMOD_ParseWeaponClassMask(Next, &input, 0, &mask) || mask != 77 ) return 4;
    input.tokens = overflow; input.index = 0; input.end = 8;
    if( NITMOD_ParseWeaponClassMask(Next, &input, 0, &mask) || mask != 77 ) return 5;
    input.tokens = badSign; input.index = 0; input.end = 9;
    if( NITMOD_ParseWeaponClassMask(Next, &input, 0, &mask) || mask != 77 ) return 6;
    if( NITMOD_ParseWeaponClassMask(NULL, &input, 0, &mask) ) return 7;
    if( NITMOD_ParseWeaponClassMask(Next, &input, 0, NULL) ) return 8;
    return 0;
}
