#include "g_local.h"
#include "g_nitmod_abilities.h"
#include <limits.h>
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    gclient_t client, before, expected;
    int playerClass, war, eligible, count;
    unsigned int unlocks, classes, options;
    ammotable_t defaults;
    memset(&defaults, 0, sizeof(defaults));
    defaults.defaultStartingAmmo = 7;
    defaults.defaultStartingClip = 9;
    memset(&before, 0x35, sizeof(before));
    before.ps.weapons[WP_MEDIC_ADRENALINE / 32] &= ~(1 << (WP_MEDIC_ADRENALINE % 32));
    before.ps.ammo[WP_MEDIC_SYRINGE] = 19;
    before.ps.ammoclip[WP_MEDIC_SYRINGE] = 23;
    for( playerClass = 0; playerClass < 5; ++playerClass )
    for( unlocks = 0; unlocks < 32; ++unlocks )
    for( classes = 0; classes < 32; ++classes )
    for( options = 0; options < 8; ++options )
    for( war = -1; war <= 5; ++war ) {
        before.sess.playerType = playerClass;
        client = expected = before;
        eligible = (unlocks & 16u) && (classes & (1u << playerClass));
        if( eligible ) {
            count = options & 4u ? 1 : (options & 1u ? 0 : 12);
            if( (war < 1 || war > 4) && (unlocks & 4u) ) count += 2;
            expected.ps.weapons[WP_MEDIC_ADRENALINE / 32] |= 1 << (WP_MEDIC_ADRENALINE % 32);
            expected.ps.ammo[WP_MEDIC_ADRENALINE] = 0;
            expected.ps.ammoclip[WP_MEDIC_ADRENALINE] = count;
        }
        CHECK( G_NITMOD_GrantAdrenalineUpgrade(&client, unlocks, classes, options, war) == !!eligible );
        CHECK( !memcmp(&client, &expected, sizeof(client)) );
        client = expected = before;
        eligible = eligible && (war < 1 || war > 4);
        if( eligible ) {
            count = options & 4u ? 1 : (options & 1u ? 0 : 9);
            if( unlocks & 4u ) count += 2;
            expected.ps.weapons[WP_MEDIC_ADRENALINE / 32] |= 1 << (WP_MEDIC_ADRENALINE % 32);
            expected.ps.ammo[WP_MEDIC_ADRENALINE] = 7;
            expected.ps.ammoclip[WP_MEDIC_ADRENALINE] = count;
        }
        CHECK( G_NITMOD_GrantAdrenalineSpawn(&client, unlocks, classes, options, war, &defaults) == !!eligible );
        CHECK( !memcmp(&client, &expected, sizeof(client)) );
    }
    client = before; client.sess.playerType = PC_MEDIC;
    CHECK( G_NITMOD_GrantAdrenalineUpgrade(&client, 20, 2, 0, 0) );
    CHECK( client.ps.ammoclip[WP_MEDIC_ADRENALINE] == 14 );
    expected = client;
    CHECK( G_NITMOD_GrantAdrenalineUpgrade(&client, 20, 2, 0, 0) );
    CHECK( !memcmp(&client, &expected, sizeof(client)) ); /* assignment, not addition */
    CHECK( G_NITMOD_GrantAdrenalineUpgrade(&client, 20, 2, 5, 0) );
    CHECK( client.ps.ammoclip[WP_MEDIC_ADRENALINE] == 3 ); /* bit 4 precedence plus bonus */
    CHECK( G_NITMOD_GrantAdrenalineUpgrade(&client, 20, 2, 5, 1) );
    CHECK( client.ps.ammoclip[WP_MEDIC_ADRENALINE] == 1 );
    CHECK( client.ps.ammo[WP_MEDIC_SYRINGE] == 19 && client.ps.ammoclip[WP_MEDIC_SYRINGE] == 23 );
    client.sess.playerType = -1; expected = client;
    CHECK( !G_NITMOD_GrantAdrenalineUpgrade(&client, ~0u, ~0u, 0, 0) );
    CHECK( !memcmp(&client, &expected, sizeof(client)) );
    client.sess.playerType = 5; expected = client;
    CHECK( !G_NITMOD_GrantAdrenalineUpgrade(&client, ~0u, ~0u, 0, 0) );
    CHECK( !memcmp(&client, &expected, sizeof(client)) );
    CHECK( !G_NITMOD_GrantAdrenalineUpgrade(NULL, ~0u, ~0u, 0, 0) );
    client = before; client.sess.playerType = PC_MEDIC; expected = client;
    defaults.defaultStartingClip = INT_MAX;
    CHECK( G_NITMOD_GrantAdrenalineSpawn(&client, 20, 2, 0, 0, &defaults) == -1 );
    CHECK( G_NITMOD_GrantAdrenalineSpawn(&client, 20, 2, 0, 0, NULL) == -1 );
    defaults.defaultStartingAmmo = -1;
    CHECK( G_NITMOD_GrantAdrenalineSpawn(&client, 20, 2, 4, 0, &defaults) == -1 );
    CHECK( !memcmp(&client, &expected, sizeof(client)) );
    defaults.defaultStartingAmmo = 7; defaults.defaultStartingClip = -1;
    CHECK( G_NITMOD_GrantAdrenalineSpawn(&client, 20, 2, 0, 0, &defaults) == -1 );
    CHECK( !G_NITMOD_GrantAdrenalineSpawn(&client, 20, 2, 0, 1, NULL) );
    CHECK( !G_NITMOD_GrantAdrenalineSpawn(&client, 0, 2, 0, 0, NULL) );
    CHECK( !memcmp(&client, &expected, sizeof(client)) );
    CHECK( G_NITMOD_GrantAdrenalineSpawn(&client, 20, 2, 4, 0, &defaults) == 1 );
    CHECK( client.ps.ammoclip[WP_MEDIC_ADRENALINE] == 3 && client.ps.ammo[WP_MEDIC_ADRENALINE] == 7 );
    expected = client;
    CHECK( G_NITMOD_GrantAdrenalineSpawn(&client, 20, 2, 4, 0, &defaults) == 1 );
    CHECK( !memcmp(&client, &expected, sizeof(client)) );
    CHECK( !G_NITMOD_GrantAdrenalineSpawn(NULL, 20, 2, 4, 0, &defaults) );
    return 0;
}
