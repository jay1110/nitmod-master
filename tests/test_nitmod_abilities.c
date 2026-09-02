#include <limits.h>
#include "g_local.h"
#include "g_nitmod_abilities.h"

static gclient_t client, before;
static gentity_t entity;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    static const int classes[] = { PC_SOLDIER, PC_MEDIC, PC_ENGINEER, PC_FIELDOPS, PC_COVERTOPS };
    static const int clips[] = { 12, 0, 12, 0, 1, 1, 1, 1 };
    unsigned int mask, unlocks;
    int index, level, expected;
    entity.client = &client;
    for( index = 0; index < 5; index++ ) for( mask = 0; mask < 64; mask++ )
    for( unlocks = 0; unlocks < 64; unlocks++ ) for( level = 0; level < 6; level++ ) {
        client.sess.playerType = classes[index];
        /* Numeric level deliberately varies independently of unlock bits. */
        client.sess.skill[SK_FIRST_AID] = level;
        before = client;
        expected = (unlocks & 16u) && (mask & (1u << index));
        CHECK( G_NITMOD_ClientHasAdrenaline(&client, unlocks, mask) == expected );
        CHECK( G_NITMOD_EntityHasAdrenaline(&entity, unlocks, mask) == expected );
        CHECK( !memcmp(&client, &before, sizeof(client)) );
    }
    client.sess.playerType = -1;
    CHECK( !G_NITMOD_EntityHasAdrenaline(&entity, ~0u, ~0u) );
    client.sess.playerType = INT_MAX;
    CHECK( !G_NITMOD_EntityHasAdrenaline(&entity, ~0u, ~0u) );
    entity.client = NULL;
    CHECK( !G_NITMOD_EntityHasAdrenaline(&entity, ~0u, ~0u) );
    CHECK( !G_NITMOD_EntityHasAdrenaline(NULL, ~0u, ~0u) );
    CHECK( !G_NITMOD_ClientHasAdrenaline(NULL, ~0u, ~0u) );
    for( mask = 0; mask < 256; mask++ ) {
        CHECK( G_NITMOD_AdrenalineClip(mask) == clips[mask & 7u] );
        CHECK( G_NITMOD_AdrenalineClip(mask | 0x80000000u) == clips[mask & 7u] );
    }
    return 0;
}
