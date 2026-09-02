#include "g_local.h"
#include "g_nitmod_weapons.h"
static gclient_t client, expected;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    int weapon, keep;
    unsigned int words[2], expectedWords[2];
    CHECK( sizeof(client.ps.weapons) == sizeof(words) );
    for( weapon = 0; weapon < 64; weapon++ ) {
        memset(&client, 0, sizeof(client));
        words[0] = words[1] = 0;
        words[weapon / 32] = 1u << (weapon % 32);
        memcpy(client.ps.weapons, words, sizeof(words));
        client.ps.weapon = WP_MORTAR;
        client.ps.ammo[WP_MORTAR] = 123;
        client.ps.ammoclip[WP_MORTAR] = 2;
        client.ps.stats[STAT_KEYS] = 64;
        expected = client;
        /* Independent complement of the recovered native removal set. */
        keep = weapon >= WP_NUM_WEAPONS || weapon == WP_NONE || weapon == WP_KNIFE ||
            weapon == WP_SMOKETRAIL || weapon == WP_MAPMORTAR || weapon == VERYBIGEXPLOSION ||
            weapon == WP_SATCHEL_DET || weapon == WP_DUMMY_MG42 || weapon == WP_LOCKPICK;
        expectedWords[0] = keep ? words[0] : 0;
        expectedWords[1] = keep ? words[1] : 0;
        memcpy(expected.ps.weapons, expectedWords, sizeof(expectedWords));
        G_NITMOD_RemoveWeapons(&client);
        CHECK( !memcmp(&client, &expected, sizeof(client)) );
        G_NITMOD_RemoveWeapons(&client);
        CHECK( !memcmp(&client, &expected, sizeof(client)) );
    }
    G_NITMOD_RemoveWeapons(NULL);
    return 0;
}
