#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "nitmod_protocol.h"
int main( void ) {
    int i;
    for( i = -100; i <= 100; i++ ) {
        const char *text = NITMOD_WeaponLimitText(i);
        if( (text != 0) != (i >= 19 && i <= 25) ) return 1;
        if( text && (strncmp(text, "^1", 2) || strlen(text) >= 128) ) return 1;
    }
    if( NITMOD_WeaponLimitText(INT_MIN) || NITMOD_WeaponLimitText(INT_MAX) ) return 1;
    if( !(NITMOD_FEATURES_CLIENT & NITMOD_FEATURE_WEAPON_MESSAGES) ||
        !(NITMOD_FEATURES_SERVER & NITMOD_FEATURE_WEAPON_MESSAGES) ) return 1;
    return 0;
}
