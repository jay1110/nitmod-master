#include "g_local.h"
#include "g_nitmod_teamcount.h"
level_locals_t level;
gentity_t g_entities[MAX_GENTITIES];
static gclient_t clients[MAX_CLIENTS];
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    nitmodWeaponPolicyInput_t input, before;
    int i;
    memset(&input, 0x5a, sizeof(input)); before = input;
    level.clients = clients;
    level.numConnectedClients = level.numNonSpectatorClients = 3;
    for( i = 0; i < 3; i++ ) {
        level.sortedClients[i] = i;
        g_entities[i].client = &clients[i];
        clients[i].sess.sessionTeam = TEAM_AXIS;
        clients[i].sess.playerWeapon = WP_PANZERFAUST;
        clients[i].pers.connected = CON_CONNECTING;
    }
    G_NITMOD_ResetTeamPopulation();
    CHECK( !G_NITMOD_ReadCachedWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( !memcmp(&input, &before, sizeof(input)) );
    CHECK( G_NITMOD_RefreshTeamPopulation() );
    CHECK( G_NITMOD_ReadCachedWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( input.teamSize == 3 && input.weaponCount == 2 );
    clients[1].sess.sessionTeam = TEAM_ALLIES;
    CHECK( G_NITMOD_ReadCachedWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( input.teamSize == 3 && input.weaponCount == 1 ); /* stale population, live weapons */
    CHECK( G_NITMOD_RefreshTeamPopulation() );
    CHECK( G_NITMOD_ReadCachedWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( input.teamSize == 2 && input.weaponCount == 1 );
    CHECK( G_NITMOD_ReadCachedWeaponCounts(&g_entities[1], WP_PANZERFAUST, &input) );
    CHECK( input.teamSize == 1 && input.weaponCount == 0 );
    level.numConnectedClients = level.numNonSpectatorClients = 1;
    CHECK( G_NITMOD_RefreshTeamPopulation() );
    CHECK( G_NITMOD_ReadCachedWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( input.teamSize == 1 && input.weaponCount == 0 );
    before = input; level.sortedClients[0] = MAX_CLIENTS;
    CHECK( !G_NITMOD_RefreshTeamPopulation() );
    level.sortedClients[0] = 0;
    CHECK( !G_NITMOD_ReadCachedWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( !memcmp(&input, &before, sizeof(input)) );
    clients[0].sess.sessionTeam = TEAM_SPECTATOR;
    CHECK( G_NITMOD_ReadCachedWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( input.teamSize == 1 ); /* fallback needs no Axis/Allies cache */
    level.numConnectedClients = level.numNonSpectatorClients = 0;
    CHECK( G_NITMOD_RefreshTeamPopulation() );
    clients[0].sess.sessionTeam = TEAM_AXIS;
    CHECK( G_NITMOD_ReadCachedWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    CHECK( input.teamSize == 0 );
    G_NITMOD_ResetTeamPopulation();
    CHECK( !G_NITMOD_ReadCachedWeaponCounts(&g_entities[0], WP_PANZERFAUST, &input) );
    return 0;
}
