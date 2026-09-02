#include "g_local.h"
#include "g_nitmod_teamcount.h"
level_locals_t level;
gentity_t g_entities[MAX_GENTITIES];
static gclient_t clients[MAX_CLIENTS];
static unsigned char granted[MAX_CLIENTS];
static nitmodWeaponPolicyInput_t input, expectedInput, beforeInput;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    static const weapon_t primaries[] = { WP_NONE, WP_KAR98, WP_CARBINE, WP_GPG40, WP_M7 };
    int side, selected, latched, grant, team, expected, i;
    level.clients = clients;
    g_entities[0].client = &clients[0];
    clients[0].sess.sessionTeam = TEAM_AXIS;
    level.numConnectedClients = 2;
    level.numNonSpectatorClients = 2;
    level.sortedClients[0] = 1;
    level.sortedClients[1] = 0;
    for( side = 0; side < 2; side++ ) for( selected = 0; selected < 5; selected++ )
    for( latched = 0; latched < 5; latched++ ) for( grant = 0; grant < 3; grant++ )
    for( team = TEAM_AXIS; team <= TEAM_SPECTATOR; team++ ) {
        int query = side ? WP_M7 : WP_GPG40;
        weapon_t base = side ? WP_CARBINE : WP_KAR98;
        clients[0].sess.playerWeapon = base;
        granted[0] = 1; /* Requester always excluded, even when matching. */
        clients[1].sess.sessionTeam = (team_t)team;
        clients[1].sess.playerWeapon = primaries[selected];
        clients[1].sess.latchPlayerWeapon = primaries[latched];
        granted[1] = (unsigned char)grant;
        clients[0].sess.rifleGrenadeStatus = 1;
        clients[1].sess.rifleGrenadeStatus = grant == 2 ? -1 : grant;
        clients[1].ps.ammo[query] = grant ? 0 : 99; /* Ammo is not eligibility. */
        expected = team == TEAM_AXIS && grant && (primaries[selected] == base || primaries[latched] == base);
        CHECK( G_NITMOD_CountRifleGrenades(&g_entities[0], query, granted, MAX_CLIENTS) == expected );
        CHECK( G_NITMOD_CountSessionRifleGrenades(&g_entities[0], query) == expected );
        memset(&input, 0x5a, sizeof(input));
        expectedInput = input;
        expectedInput.teamSize = team == TEAM_AXIS ? 2 : 1;
        expectedInput.weaponCount = expected;
        base = side ? WP_KAR98 : WP_CARBINE;
        expectedInput.oppositeRifleCount = team == TEAM_AXIS && grant &&
            (primaries[selected] == base || primaries[latched] == base);
        CHECK( G_NITMOD_ReadWeaponCounts(&g_entities[0], query, &input) );
        CHECK( !memcmp(&input, &expectedInput, sizeof(input)) );
    }
    /* Both rifle families can contribute to a shared cap; count once per
     * family, even when both selected and latched fields match. */
    level.numConnectedClients = 3;
    level.numNonSpectatorClients = 3;
    for( i = 0; i < 3; i++ ) {
        level.sortedClients[i] = i;
        clients[i].sess.sessionTeam = TEAM_AXIS;
        granted[i] = 1;
    }
    clients[1].sess.playerWeapon = clients[1].sess.latchPlayerWeapon = WP_KAR98;
    clients[2].sess.playerWeapon = clients[2].sess.latchPlayerWeapon = WP_CARBINE;
    CHECK( G_NITMOD_CountRifleGrenades(&g_entities[0], WP_GPG40, granted, MAX_CLIENTS) == 1 );
    CHECK( G_NITMOD_CountRifleGrenades(&g_entities[0], WP_M7, granted, MAX_CLIENTS) == 1 );
    level.numNonSpectatorClients = 2;
    CHECK( G_NITMOD_CountRifleGrenades(&g_entities[0], WP_M7, granted, MAX_CLIENTS) == 0 );
    CHECK( G_NITMOD_CountSessionRifleGrenades(&g_entities[0], WP_M7) == 0 );
    level.numNonSpectatorClients = 3;
    CHECK( G_NITMOD_CountRifleGrenades(&g_entities[0], WP_GPG40, granted, 2) == -1 );
    level.sortedClients[2] = -1;
    beforeInput = input;
    CHECK( !G_NITMOD_ReadWeaponCounts(&g_entities[0], WP_GPG40, &input) );
    CHECK( !memcmp(&input, &beforeInput, sizeof(input)) );
    CHECK( G_NITMOD_CountSessionRifleGrenades(&g_entities[0], WP_GPG40) == -1 );
    CHECK( G_NITMOD_CountRifleGrenades(&g_entities[0], WP_GPG40, granted, MAX_CLIENTS) == -1 );
    level.numConnectedClients = 0;
    level.numNonSpectatorClients = 0;
    CHECK( G_NITMOD_ReadWeaponCounts(&g_entities[0], WP_GPG40, &input) );
    CHECK( input.weaponCount == 0 && input.oppositeRifleCount == 0 );
    beforeInput = input;
    CHECK( !G_NITMOD_ReadWeaponCounts(NULL, WP_GPG40, &input) );
    CHECK( !G_NITMOD_ReadWeaponCounts(&g_entities[0], -1, &input) );
    CHECK( !G_NITMOD_ReadWeaponCounts(&g_entities[0], WP_NUM_WEAPONS, &input) );
    CHECK( !G_NITMOD_ReadWeaponCounts(&g_entities[0], WP_GPG40, NULL) );
    g_entities[0].client = &clients[1];
    CHECK( !G_NITMOD_ReadWeaponCounts(&g_entities[0], WP_GPG40, &input) );
    g_entities[0].client = &clients[0];
    CHECK( !memcmp(&input, &beforeInput, sizeof(input)) );
    CHECK( G_NITMOD_CountSessionRifleGrenades(&g_entities[0], WP_GPG40) == 0 );
    CHECK( G_NITMOD_CountRifleGrenades(&g_entities[0], WP_GPG40, granted, 0) == 0 );
    CHECK( G_NITMOD_CountRifleGrenades(&g_entities[0], WP_KAR98, granted, MAX_CLIENTS) == -1 );
    CHECK( G_NITMOD_CountRifleGrenades(NULL, WP_GPG40, granted, MAX_CLIENTS) == -1 );
    CHECK( G_NITMOD_CountRifleGrenades(&g_entities[0], WP_GPG40, NULL, MAX_CLIENTS) == -1 );
    CHECK( G_NITMOD_CountSessionRifleGrenades(NULL, WP_GPG40) == -1 );
    CHECK( G_NITMOD_CountSessionRifleGrenades(&g_entities[0], WP_KAR98) == -1 );
    level.numConnectedClients = MAX_CLIENTS + 1;
    CHECK( G_NITMOD_CountSessionRifleGrenades(&g_entities[0], WP_GPG40) == -1 );
    level.numConnectedClients = 0; level.clients = NULL;
    CHECK( G_NITMOD_CountSessionRifleGrenades(&g_entities[0], WP_GPG40) == -1 );
    return 0;
}
