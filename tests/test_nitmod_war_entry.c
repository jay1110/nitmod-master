#include "g_local.h"
#include "g_nitmod_war.h"
static gentity_t entity;
static gclient_t client, expected;
static nitmodWarState_t state;
static int events, badEvent;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

void G_AddEvent( gentity_t *ent, int event, int parm ) {
    events++;
    if( ent != &entity || event != EV_NOAMMO || parm != 0 || state.stripped ||
        ent->client->ps.weapon != WP_KNIFE ||
        (ent->client->ps.weapons[0] & (1 << WP_MP40)) ) badEvent = 1;
}

int main( void ) {
    int mode;
    entity.client = &client;
    entity.health = 100;
    client.ps.weapons[0] = (1 << WP_KNIFE) | (1 << WP_MP40);
    client.ps.weapon = WP_MP40;
    client.ps.ammo[WP_MP40] = 123;
    client.ps.ammoclip[WP_MP40] = 7;
    expected = client;
    for( mode = -2; mode < 9; mode++ ) if( mode != 4 ) {
        CHECK( !G_NITMOD_ApplyWarEntry(&entity, &state, mode, 0) );
        CHECK( !memcmp(&client, &expected, sizeof(client)) && !state.stripped && !events );
    }
    CHECK( !G_NITMOD_ApplyWarEntry(&entity, &state, 4, 1) );
    client.ps.pm_flags = PMF_FOLLOW;
    CHECK( !G_NITMOD_ApplyWarEntry(&entity, &state, 4, 0) );
    client.ps.pm_flags = 0;
    entity.health = 0;
    CHECK( !G_NITMOD_ApplyWarEntry(&entity, &state, 4, 0) );
    entity.health = 100;
    CHECK( !G_NITMOD_ApplyWarEntry(NULL, &state, 4, 0) );
    CHECK( !G_NITMOD_ApplyWarEntry(&entity, NULL, 4, 0) );
    CHECK( !events && !state.stripped && !memcmp(&client, &expected, sizeof(client)) );
    CHECK( G_NITMOD_ApplyWarEntry(&entity, &state, 4, 0) );
    expected.ps.weapons[0] &= ~(1 << WP_MP40);
    expected.ps.weapon = WP_KNIFE;
    CHECK( !memcmp(&client, &expected, sizeof(client)) && state.stripped && events == 1 && !badEvent );
    /* New weapons acquired later are not repeatedly stripped. Mode changes
     * alone do not reset the latch; the caller's spawn reset does. */
    client.ps.weapons[0] |= 1 << WP_MP40;
    expected = client;
    CHECK( !G_NITMOD_ApplyWarEntry(&entity, &state, 0, 0) );
    CHECK( !G_NITMOD_ApplyWarEntry(&entity, &state, 4, 0) );
    CHECK( !memcmp(&client, &expected, sizeof(client)) && events == 1 );
    G_NITMOD_ResetWarState(&state);
    CHECK( G_NITMOD_ApplyWarEntry(&entity, &state, 4, 0) && events == 2 && !badEvent );
    /* Selecting a knife does not grant a missing knife ownership bit. */
    G_NITMOD_ResetWarState(&state);
    client.ps.weapons[0] = 0;
    CHECK( G_NITMOD_ApplyWarEntry(&entity, &state, 4, 0) );
    CHECK( !client.ps.weapons[0] && events == 3 && !badEvent );
    G_NITMOD_ResetWarState(NULL);
    return 0;
}
