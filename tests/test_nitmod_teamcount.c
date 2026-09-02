#include "g_local.h"
#include "g_nitmod_teamcount.h"
level_locals_t level;
gentity_t g_entities[MAX_GENTITIES];
static gclient_t clients[MAX_CLIENTS];
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    static const weapon_t pairs[][2] = {
        {WP_LUGER, WP_COLT}, {WP_MP40, WP_THOMPSON},
        {WP_GRENADE_LAUNCHER, WP_GRENADE_PINEAPPLE}, {WP_SILENCER, WP_SILENCED_COLT},
        {WP_KAR98, WP_CARBINE}, {WP_GARAND, WP_K43}, {WP_AKIMBO_COLT, WP_AKIMBO_LUGER},
        {WP_GARAND_SCOPE, WP_K43_SCOPE}, {WP_AKIMBO_SILENCEDCOLT, WP_AKIMBO_SILENCEDLUGER}
    };
    int i, pair, side;
    nitmodWeaponPolicyInput_t input, expected;
    level.clients = clients;
    g_entities[0].client = &clients[0];
    for( i = 0; i < 4; i++ ) {
        clients[i].sess.sessionTeam = TEAM_AXIS;
        level.sortedClients[i] = 3 - i;
    }
    CHECK( G_TeamCount(&g_entities[0], (weapon_t)-1) == 1 );
    CHECK( G_TeamCount(&g_entities[0], WP_MP40) == 0 );
    level.numConnectedClients = 4;
    level.numNonSpectatorClients = 4;
    clients[3].sess.sessionTeam = TEAM_ALLIES;
    CHECK( G_TeamCount(&g_entities[0], (weapon_t)-1) == 3 );
    for( pair = 0; pair < sizeof(pairs) / sizeof(pairs[0]); pair++ ) for( side = 0; side < 2; side++ ) {
        clients[0].sess.playerWeapon = pairs[pair][side]; /* excluded */
        clients[1].sess.playerWeapon = pairs[pair][side];
        clients[1].sess.latchPlayerWeapon = pairs[pair][!side]; /* one client, not two */
        clients[2].sess.playerWeapon = WP_NONE;
        clients[2].sess.latchPlayerWeapon = pairs[pair][!side];
        clients[3].sess.playerWeapon = pairs[pair][side]; /* other team */
        CHECK( G_TeamCount(&g_entities[0], pairs[pair][side]) == 2 );
        memset(&input, 0x5a, sizeof(input)); expected = input;
        expected.weaponCount = 2; expected.oppositeRifleCount = 0;
        expected.teamSize = 3;
        CHECK( G_NITMOD_ReadWeaponCounts(&g_entities[0], pairs[pair][side], &input) );
        CHECK( !memcmp(&input, &expected, sizeof(input)) );
    }
    clients[1].sess.playerWeapon = WP_PANZERFAUST;
    clients[1].sess.latchPlayerWeapon = WP_PANZERFAUST;
    clients[2].sess.latchPlayerWeapon = WP_NONE;
    CHECK( G_TeamCount(&g_entities[0], WP_PANZERFAUST) == 1 );
    CHECK( G_NITMOD_ReadWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( input.weaponCount == 1 && input.oppositeRifleCount == 0 );
    clients[1].sess.playerWeapon = WP_GPG40;
    clients[1].sess.latchPlayerWeapon = WP_NONE;
    clients[2].sess.playerWeapon = WP_M7;
    CHECK( G_TeamCount(&g_entities[0], WP_GPG40) == 1 ); /* retained ET special case */
    CHECK( G_NITMOD_ReadWeaponCounts(&g_entities[0], WP_GPG40, &input) );
    CHECK( input.weaponCount == 0 && input.oppositeRifleCount == 0 ); /* no granted base rifles */
    /* Original weapon count scans the non-spectator LENGTH prefix, whereas
     * the team population scans all connected slots, including connecting. */
    for( i = 0; i < 4; i++ ) {
        level.sortedClients[i] = i;
        clients[i].sess.sessionTeam = TEAM_AXIS;
        clients[i].sess.playerWeapon = WP_PANZERFAUST;
        clients[i].sess.latchPlayerWeapon = WP_NONE;
        clients[i].pers.connected = CON_CONNECTING;
    }
    level.numNonSpectatorClients = 2;
    CHECK( G_NITMOD_ReadWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( input.teamSize == 4 && input.weaponCount == 1 );
    clients[0].sess.sessionTeam = clients[1].sess.sessionTeam = TEAM_SPECTATOR;
    CHECK( G_NITMOD_ReadWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( input.teamSize == 2 && input.weaponCount == 1 );
    clients[2].sess.sessionTeam = TEAM_SPECTATOR; /* outside counted prefix */
    CHECK( G_NITMOD_ReadWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( input.teamSize == 2 && input.weaponCount == 1 );
    expected = input;
    level.numNonSpectatorClients = 5;
    CHECK( !G_NITMOD_ReadWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( !memcmp(&input, &expected, sizeof(input)) );
    level.numConnectedClients = 0;
    level.numNonSpectatorClients = 0;
    CHECK( G_TeamCount(&g_entities[0], WP_GPG40) == 0 );
    CHECK( G_TeamCount(&g_entities[0], (weapon_t)-1) == 1 );
    return 0;
}
