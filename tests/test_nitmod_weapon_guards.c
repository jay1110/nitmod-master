#include <limits.h>
#include "g_local.h"
#include "g_nitmod_abilities.h"

static gclient_t client, expected;
static gentity_t entity;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    int number, state, count, flags, demo, h, eligible;
    int word = WP_MEDIC_ADRENALINE / 32;
    int bit = 1 << (WP_MEDIC_ADRENALINE % 32);
    static const int health[] = { INT_MIN, 0, 1, INT_MAX };
    for( number = -1; number <= 65; number++ )
    for( state = -2; state <= 5; state++ )
    for( count = -1; count <= 65; count++ ) {
        CHECK( G_NITMOD_IsDemoClient(number, state, count) ==
            (number >= 0 && (state == 1 || state == 2 || state == 3) && number < count) );
    }
    CHECK( !G_NITMOD_IsDemoClient(0, INT_MIN, INT_MAX) );
    CHECK( !G_NITMOD_IsDemoClient(0, INT_MAX, INT_MAX) );
    CHECK( G_NITMOD_IsDemoClient(INT_MAX - 1, 3, INT_MAX) );
    CHECK( !G_NITMOD_IsDemoClient(INT_MAX, 3, INT_MAX) );
    entity.client = &client;
    client.sess.playerType = PC_MEDIC;
    /* Exhaust every 16-bit pm_flags value: only FOLLOW is relevant here,
     * particularly not LIMBO, RESPAWNED or TIME_LOCKPLAYER. */
    for( flags = 0; flags <= 65535; flags++ )
    for( demo = 0; demo <= 1; demo++ ) for( h = 0; h < 4; h++ ) {
        client.ps.pm_flags = flags;
        entity.health = health[h];
        client.ps.weapons[word] = -1;
        expected = client;
        eligible = !demo && !(flags & PMF_FOLLOW) && health[h] > 0;
        CHECK( G_NITMOD_CanCheckWeapons(&entity, demo) == eligible );
        if( eligible ) expected.ps.weapons[word] &= ~bit;
        CHECK( G_NITMOD_CheckAdrenaline(&entity, demo, 0, 2) == eligible );
        CHECK( !memcmp(&client, &expected, sizeof(client)) );
    }
    CHECK( !G_NITMOD_CheckAdrenaline(&entity, -1, 0, 0) );
    CHECK( !G_NITMOD_CheckAdrenaline(NULL, 0, 0, 0) );
    entity.client = NULL;
    CHECK( !G_NITMOD_CheckAdrenaline(&entity, 0, 0, 0) );
    return 0;
}
