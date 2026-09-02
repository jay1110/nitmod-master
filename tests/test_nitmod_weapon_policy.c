#include <limits.h>
#include "g_local.h"
#include "g_nitmod_restrictions.h"
static gentity_t entity, savedEntity;
static gclient_t client, savedClient;
static nitmodWeaponPolicyInput_t input, savedInput;
#define CHECK(test) do { if( !(test) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
static void Reset( void ) {
    memset(&entity, 0, sizeof(entity));
    memset(&client, 0, sizeof(client));
    memset(&input, 0, sizeof(input));
    entity.client = &client;
    client.sess.sessionTeam = TEAM_AXIS;
    client.sess.playerType = PC_COVERTOPS;
    input.teamSize = 10; input.maxClients = 20; input.heavyPercent = 100;
    input.maxPanzers = input.maxFlamers = input.maxMG42s = -1;
    input.maxMortars = input.maxRifleGrenades = -1;
    input.pickupContext = input.pickAnyWeapon = 1;
}
static int Verify( int weapon, int decision, int limit, int message ) {
    nitmodWeaponPolicyResult_t result;
    savedEntity = entity; savedClient = client; savedInput = input;
    result = G_NITMOD_EvaluateWeaponPolicy(&entity, weapon, &input);
    CHECK( result.decision == decision && result.limit == limit && result.messageReason == message );
    CHECK( !memcmp(&savedEntity, &entity, sizeof(entity)) );
    CHECK( !memcmp(&savedClient, &client, sizeof(client)) );
    CHECK( !memcmp(&savedInput, &input, sizeof(input)) );
    return 0;
}
int main( void ) {
    int weapon, count, opposite, cap, reason, heavy;
    nitmodWeaponPolicyResult_t result;
    Reset();
    for( weapon = 0; weapon < WP_NUM_WEAPONS; weapon++ ) {
        CHECK( !Verify(weapon, NITMOD_WEAPON_ALLOW, NITMOD_LIMIT_NONE, 0) );
        input.maxPanzers = input.maxFlamers = input.maxMG42s = 0;
        input.maxMortars = input.maxRifleGrenades = 0;
        reason = 0;
        if( weapon == WP_PANZERFAUST ) reason = 21;
        if( weapon == WP_FLAMETHROWER ) reason = 22;
        if( weapon == WP_MOBILE_MG42 ) reason = 23;
        if( weapon == WP_MORTAR ) reason = 24;
        if( weapon == WP_GPG40 || weapon == WP_M7 ) reason = 25;
        CHECK( !Verify(weapon, reason ? NITMOD_WEAPON_DENY : NITMOD_WEAPON_ALLOW,
            reason ? NITMOD_LIMIT_FIXED : NITMOD_LIMIT_NONE, reason) );
        input.heavyPercent = 0;
        heavy = weapon == WP_PANZERFAUST || weapon == WP_FLAMETHROWER ||
            weapon == WP_MOBILE_MG42 || weapon == WP_MOBILE_MG42_SET ||
            weapon == WP_MORTAR || weapon == WP_MORTAR_SET;
        CHECK( !Verify(weapon, (heavy || reason) ? NITMOD_WEAPON_DENY : NITMOD_WEAPON_ALLOW,
            heavy ? NITMOD_LIMIT_HEAVY : (reason ? NITMOD_LIMIT_FIXED : NITMOD_LIMIT_NONE),
            heavy ? 19 : reason) );
        Reset();
    }
    for( weapon = 0; weapon < 2; weapon++ )
    for( count = 0; count <= 8; count++ )
    for( opposite = 0; opposite <= 8; opposite++ )
    for( cap = -2; cap <= 17; cap++ ) {
        input.weaponCount = count; input.oppositeRifleCount = opposite;
        input.maxRifleGrenades = cap;
        reason = cap != -1 && count + opposite >= cap;
        CHECK( !Verify(weapon ? WP_M7 : WP_GPG40,
            reason ? NITMOD_WEAPON_DENY : NITMOD_WEAPON_ALLOW,
            reason ? NITMOD_LIMIT_FIXED : NITMOD_LIMIT_NONE, reason ? 25 : 0) );
    }
    Reset(); input.weaponCount = INT_MAX; input.oppositeRifleCount = 1;
    input.maxRifleGrenades = 2;
    CHECK( !Verify(WP_M7, NITMOD_WEAPON_DENY, NITMOD_LIMIT_INVALID, 0) );
    input.maxRifleGrenades = -1;
    CHECK( !Verify(WP_M7, NITMOD_WEAPON_ALLOW, NITMOD_LIMIT_NONE, 0) );
    input.maxRifleGrenades = 2; input.weaponCount = -1;
    CHECK( !Verify(WP_M7, NITMOD_WEAPON_DENY, NITMOD_LIMIT_INVALID, 0) );
    input.weaponCount = 0; input.oppositeRifleCount = -1;
    CHECK( !Verify(WP_GPG40, NITMOD_WEAPON_DENY, NITMOD_LIMIT_INVALID, 0) );
    input.maxRifleGrenades = 0; input.warMode = 3;
    CHECK( !Verify(WP_M7, NITMOD_WEAPON_ALLOW, NITMOD_LIMIT_NONE, 0) );
    client.sess.sessionTeam = TEAM_SPECTATOR;
    CHECK( !Verify(WP_M7, NITMOD_WEAPON_DENY, NITMOD_LIMIT_NONE, 0) );
    entity.r.svFlags = SVF_BOT;
    CHECK( !Verify(WP_M7, NITMOD_WEAPON_ALLOW, NITMOD_LIMIT_NONE, 0) );
    Reset(); input.panzerPercent = 101; input.maxPanzers = 0;
    CHECK( !Verify(WP_PANZERFAUST, NITMOD_WEAPON_DENY, NITMOD_LIMIT_PANZER_TEAM, 20) );
    input.silent = 1;
    CHECK( !Verify(WP_PANZERFAUST, NITMOD_WEAPON_DENY, NITMOD_LIMIT_PANZER_TEAM, 0) );
    input.silent = 0; client.ps.pm_flags = PMF_LIMBO;
    CHECK( !Verify(WP_PANZERFAUST, NITMOD_WEAPON_DENY, NITMOD_LIMIT_PANZER_TEAM, 0) );
    client.ps.pm_flags = 0; input.pickupContext = 0;
    CHECK( !Verify(WP_PANZERFAUST, NITMOD_WEAPON_DENY, NITMOD_LIMIT_PANZER_TEAM, 0) );
    input.pickupContext = 1; input.maxClients = 0;
    CHECK( !Verify(WP_PANZERFAUST, NITMOD_WEAPON_DENY, NITMOD_LIMIT_INVALID, 0) );
    input.heavyPercent = 0;
    CHECK( !Verify(WP_PANZERFAUST, NITMOD_WEAPON_DENY, NITMOD_LIMIT_HEAVY, 19) );
    Reset(); client.sess.playerType = PC_SOLDIER;
    input.pickupContext = 0;
    CHECK( !Verify(WP_STEN, NITMOD_WEAPON_DENY, NITMOD_LIMIT_NONE, 0) );
    input.pickupContext = input.pickAnyWeapon = 1;
    CHECK( !Verify(WP_STEN, NITMOD_WEAPON_ALLOW, NITMOD_LIMIT_NONE, 0) );
    CHECK( !Verify(-1, NITMOD_WEAPON_DENY, NITMOD_LIMIT_INVALID, 0) );
    CHECK( !Verify(WP_NUM_WEAPONS, NITMOD_WEAPON_DENY, NITMOD_LIMIT_INVALID, 0) );
    result = G_NITMOD_EvaluateWeaponPolicy(&entity, WP_STEN, NULL);
    CHECK( result.decision == NITMOD_WEAPON_DENY && result.limit == NITMOD_LIMIT_INVALID );
    result = G_NITMOD_EvaluateWeaponPolicy(NULL, WP_STEN, &input);
    CHECK( result.decision == NITMOD_WEAPON_DENY && result.limit == NITMOD_LIMIT_INVALID );
    entity.client = NULL;
    result = G_NITMOD_EvaluateWeaponPolicy(&entity, WP_STEN, &input);
    CHECK( result.decision == NITMOD_WEAPON_DENY && result.limit == NITMOD_LIMIT_INVALID );
    return 0;
}
