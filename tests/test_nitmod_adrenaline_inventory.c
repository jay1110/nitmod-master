#include "g_local.h"
#include "g_nitmod_abilities.h"

static gclient_t client, expected;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    int type, owned, changed, bit = 1 << (WP_MEDIC_ADRENALINE % 32);
    unsigned int unlocks, classes;
    int word = WP_MEDIC_ADRENALINE / 32;
    for( type = PC_SOLDIER; type <= PC_COVERTOPS; type++ )
    for( classes = 0; classes < 32; classes++ )
    for( unlocks = 0; unlocks < 64; unlocks++ )
    for( owned = 0; owned < 2; owned++ ) {
        memset(&client, 0, sizeof(client));
        client.sess.playerType = type;
        /* Other inventory bits, ammo, selected weapon, timed effect and
         * numeric level must survive even when eligibility is revoked. */
        client.ps.weapons[0] = -1;
        client.ps.weapons[word] = owned ? -1 : ~bit;
        client.ps.weapon = WP_MEDIC_ADRENALINE;
        client.ps.ammo[WP_MEDIC_ADRENALINE] = 37;
        client.ps.ammoclip[WP_MEDIC_ADRENALINE] = 9;
        client.ps.powerups[PW_ADRENALINE] = 123456;
        client.sess.skill[SK_FIRST_AID] = 5;
        expected = client;
        changed = owned && (!(unlocks & 16u) || !(classes & (1u << type)));
        if( changed ) expected.ps.weapons[word] &= ~bit;
        CHECK( G_NITMOD_ReconcileAdrenaline(&client, unlocks, classes) == changed );
        CHECK( !memcmp(&client, &expected, sizeof(client)) );
        CHECK( !G_NITMOD_ReconcileAdrenaline(&client, unlocks, classes) );
        CHECK( !memcmp(&client, &expected, sizeof(client)) );
    }
    /* Loss and subsequent restoration never auto-grant the weapon. */
    client.sess.playerType = PC_MEDIC;
    client.ps.weapons[word] |= bit;
    CHECK( !G_NITMOD_ReconcileAdrenaline(&client, 16, 2) );
    client.sess.playerType = PC_SOLDIER;
    CHECK( G_NITMOD_ReconcileAdrenaline(&client, 16, 2) );
    client.sess.playerType = PC_MEDIC;
    CHECK( !G_NITMOD_ReconcileAdrenaline(&client, 16, 2) );
    CHECK( !(client.ps.weapons[word] & bit) );
    client.ps.weapons[word] |= bit;
    CHECK( G_NITMOD_ReconcileAdrenaline(&client, 32, 2) );
    CHECK( !G_NITMOD_ReconcileAdrenaline(NULL, 0, 0) );
    return 0;
}
