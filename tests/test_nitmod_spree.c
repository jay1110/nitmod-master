#include <limits.h>
#include <stdio.h>
#include "nitmod_spree.h"

#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    nitmodKillSpree_t attacker;
    nitmodKillSpree_t other;
    int kill;
    int detail;
    int announcements = 0;

    NITMOD_ResetKillSpree( &attacker );
    NITMOD_ResetKillSpree( &other );
    for( kill = 1; kill <= 100; kill++ ) {
        detail = NITMOD_RecordSpreeKill( &attacker, 1 );
        if( kill == 5 || kill == 10 || kill == 15 || kill == 20 || kill == 25 || kill == 30 ) {
            CHECK( detail == announcements );
            announcements++;
        } else {
            CHECK( detail == -1 );
        }
        CHECK( attacker.kills == kill );
    }
    CHECK( announcements == 6 );
    CHECK( other.kills == 0 );

    /* Death/team/connection resets restart the positive series at zero. */
    NITMOD_ResetKillSpree( &attacker );
    CHECK( attacker.kills == 0 );
    for( kill = 1; kill <= 4; kill++ ) {
        CHECK( NITMOD_RecordSpreeKill( &attacker, 1 ) == -1 );
    }
    CHECK( NITMOD_RecordSpreeKill( &attacker, 1 ) == 0 );

    /* Disabling announcements must not stop accounting. Other option bits
     * cannot enable kill-spree messages. Re-enabling emits only new tiers. */
    NITMOD_ResetKillSpree( &attacker );
    for( kill = 1; kill <= 5; kill++ ) {
        CHECK( NITMOD_RecordSpreeKill( &attacker, 0 ) == -1 );
    }
    for( kill = 6; kill <= 10; kill++ ) {
        CHECK( NITMOD_RecordSpreeKill( &attacker, 0x7e ) == -1 );
    }
    CHECK( attacker.kills == 10 );
    for( kill = 11; kill < 15; kill++ ) {
        CHECK( NITMOD_RecordSpreeKill( &attacker, 0x7f ) == -1 );
    }
    CHECK( NITMOD_RecordSpreeKill( &attacker, 0x7f ) == 2 );

    attacker.kills = INT_MAX - 1;
    CHECK( NITMOD_RecordSpreeKill( &attacker, 1 ) == -1 );
    CHECK( attacker.kills == INT_MAX );
    CHECK( NITMOD_RecordSpreeKill( &attacker, 1 ) == -1 );
    CHECK( attacker.kills == INT_MAX );
    NITMOD_ResetKillSpree( &attacker );
    CHECK( attacker.kills == 0 );
    return 0;
}
