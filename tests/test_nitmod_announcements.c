/* Executable cases derived from original G_UpdateKillingSpree and
 * ReviveEntity producer payloads, linked against the production decoder. */
#include <limits.h>
#include <stdio.h>
#include "nitmod_announcements.h"

#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    int i;
    int value;
    char maximum[64];
    const char *invalid[] = { "", "-1", "+1", " 1", "1 ", "1x", "1.0",
        "9999999999999999999999999999999999999999999999" };
    /* A five-kill tier and a ten-death tier have different meanings. */
    for( i = 0; i < 6; i++ ) {
        CHECK( NITMOD_AnnouncementCount( 1, i ) == 5 * ( i + 1 ) );
    }
    for( i = 0; i < 3; i++ ) {
        CHECK( NITMOD_AnnouncementCount( 2, i ) == 10 * ( i + 1 ) );
    }
    for( i = 0; i < 4; i++ ) {
        CHECK( NITMOD_AnnouncementCount( 5, i ) == i + 2 );
    }
    CHECK( NITMOD_AnnouncementCount( 1, 6 ) == -1 );
    CHECK( NITMOD_AnnouncementCount( 2, 3 ) == -1 );
    CHECK( NITMOD_AnnouncementCount( 4, 5 ) == 5 );
    CHECK( NITMOD_AnnouncementCount( 4, 35 ) == 35 );
    CHECK( NITMOD_AnnouncementCount( 4, 0 ) == -1 );
    CHECK( NITMOD_AnnouncementCount( 4, 6 ) == -1 );
    CHECK( NITMOD_AnnouncementCount( 5, 4 ) == -1 );
    CHECK( NITMOD_AnnouncementCount( 0, 0 ) == -1 );
    CHECK( NITMOD_AnnouncementCount( 6, 0 ) == -1 );
    for( i = 1; i <= 5; i++ ) {
        CHECK( NITMOD_AnnouncementCount( i, -1 ) == -1 );
        CHECK( NITMOD_AnnouncementCount( i, INT_MAX ) == -1 );
    }
    /* Unknown multi-kill table retains a tier, not an invented kill count. */
    CHECK( NITMOD_AnnouncementCount( 3, 2 ) == 3 );
    CHECK( NITMOD_AnnouncementCount( 3, INT_MAX - 1 ) == INT_MAX );
    for( i = 0; i < (int)( sizeof(invalid) / sizeof(invalid[0]) ); i++ ) {
        value = 77;
        CHECK( !NITMOD_ParseAnnouncementInteger( invalid[i], &value ) );
        CHECK( value == 77 );
    }
    CHECK( !NITMOD_ParseAnnouncementInteger( NULL, &value ) );
    CHECK( !NITMOD_ParseAnnouncementInteger( "1", NULL ) );
    CHECK( NITMOD_ParseAnnouncementInteger( "0", &value ) && value == 0 );
    CHECK( NITMOD_ParseAnnouncementInteger( "00030", &value ) && value == 30 );
    sprintf( maximum, "%d", INT_MAX );
    CHECK( NITMOD_ParseAnnouncementInteger( maximum, &value ) && value == INT_MAX );
    return 0;
}
