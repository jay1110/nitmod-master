#include "g_local.h"
#include "g_nitmod_rifle.h"
static gentity_t entity;
static gclient_t client, expected;
static int publications, badPublication;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
void ClientUserinfoChanged( int number ) {
    publications++;
    if( number != 3 || memcmp(&client, &expected, sizeof(client)) ) badPublication = 1;
}
int main( void ) {
    int side, owned, status, query, word, bit, previous;
    entity.client = &client;
    for( side = 0; side < 2; side++ ) for( owned = 0; owned < 2; owned++ )
    for( status = -1; status <= 1; status++ ) {
        query = side ? WP_M7 : WP_GPG40;
        word = query / 32; bit = 1 << (query % 32);
        memset(&client, 0, sizeof(client));
        client.ps.clientNum = 3;
        client.ps.weapons[0] = -1;
        client.ps.weapons[1] = owned ? -1 : ~bit;
        client.ps.weapon = query;
        client.ps.ammo[query] = 9;
        client.sess.playerWeapon = WP_KAR98;
        client.sess.latchPlayerWeapon = WP_CARBINE;
        client.sess.rifleGrenadeStatus = status;
        expected = client;
        if( owned ) {
            expected.ps.weapons[word] &= ~bit;
            expected.sess.rifleGrenadeStatus = 0;
        }
        previous = publications;
        CHECK( G_NITMOD_RevokeRifleGrenade(&entity, query) == owned );
        CHECK( !memcmp(&client, &expected, sizeof(client)) );
        CHECK( publications == previous + (owned && status != 0) && !badPublication );
        CHECK( G_NITMOD_RevokeRifleGrenade(&entity, query) == 0 );
        CHECK( publications == previous + (owned && status != 0) );
    }
    CHECK( G_NITMOD_RevokeRifleGrenade(NULL, WP_GPG40) == -1 );
    CHECK( G_NITMOD_RevokeRifleGrenade(&entity, WP_KAR98) == -1 );
    client.ps.clientNum = MAX_CLIENTS;
    expected = client;
    CHECK( G_NITMOD_RevokeRifleGrenade(&entity, WP_GPG40) == -1 );
    CHECK( !memcmp(&client, &expected, sizeof(client)) );
    return 0;
}
