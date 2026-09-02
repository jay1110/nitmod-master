#include <limits.h>
#include <stdio.h>
#include "nitmod_protocol.h"

#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    const char *invalid[] = { "", "-1", "+1", " 1", "1 ", "1xyz", "1 1023",
        "0x10", "1.5", "1e3", "1\n", "99999999999999999999999999999999999" };
    int i;
    int signedValue;
    unsigned int unsignedValue;
    char boundary[64];
    for( i = 0; i < (int)( sizeof(invalid) / sizeof(invalid[0]) ); i++ ) {
        signedValue = 77;
        unsignedValue = 77;
        CHECK( !NITMOD_ParseProtocolInteger( invalid[i], &signedValue ) );
        CHECK( !NITMOD_ParseProtocolUnsigned( invalid[i], &unsignedValue ) );
        CHECK( signedValue == 77 && unsignedValue == 77 );
    }
    CHECK( !NITMOD_ParseProtocolInteger( NULL, &signedValue ) );
    CHECK( !NITMOD_ParseProtocolUnsigned( NULL, &unsignedValue ) );
    CHECK( !NITMOD_ParseProtocolInteger( "1", NULL ) );
    CHECK( !NITMOD_ParseProtocolUnsigned( "1", NULL ) );
    CHECK( NITMOD_ParseProtocolInteger( "000654", &signedValue ) && signedValue == 654 );
    CHECK( NITMOD_ParseProtocolUnsigned( "0", &unsignedValue ) && unsignedValue == 0 );
    sprintf( boundary, "%d", INT_MAX );
    CHECK( NITMOD_ParseProtocolInteger( boundary, &signedValue ) && signedValue == INT_MAX );
    sprintf( boundary, "%u", (unsigned int)INT_MAX + 1u );
    CHECK( !NITMOD_ParseProtocolInteger( boundary, &signedValue ) && signedValue == INT_MAX );
    CHECK( NITMOD_ParseProtocolUnsigned( boundary, &unsignedValue ) );
    sprintf( boundary, "%u", UINT_MAX );
    CHECK( NITMOD_ParseProtocolUnsigned( boundary, &unsignedValue ) && unsignedValue == UINT_MAX );
    sprintf( boundary, "%u0", UINT_MAX );
    CHECK( !NITMOD_ParseProtocolUnsigned( boundary, &unsignedValue ) && unsignedValue == UINT_MAX );
    sprintf( boundary, "%u", NITMOD_FEATURES_CLIENT );
    CHECK( NITMOD_ParseProtocolUnsigned( boundary, &unsignedValue ) && unsignedValue == NITMOD_FEATURES_CLIENT );
    return 0;
}
