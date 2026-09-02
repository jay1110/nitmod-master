#include "g_local.h"
#include "g_nitmod_restrictions.h"
static gentity_t entity;
static gclient_t client, before;
static int ExpectedPrimary( int cls, int team, int weapon ) {
    if( team != TEAM_AXIS && team != TEAM_ALLIES ) return 0;
    switch( cls ) {
    case PC_SOLDIER:
        return weapon == (team == TEAM_AXIS ? WP_MP40 : WP_THOMPSON) ||
            weapon == WP_MOBILE_MG42 || weapon == WP_FLAMETHROWER ||
            weapon == WP_PANZERFAUST || weapon == WP_MORTAR;
    case PC_MEDIC:
    case PC_FIELDOPS:
        return weapon == WP_MP40 || weapon == WP_THOMPSON || weapon == WP_STEN;
    case PC_ENGINEER:
        return weapon == WP_MP40 || weapon == WP_THOMPSON ||
            weapon == (team == TEAM_AXIS ? WP_KAR98 : WP_CARBINE);
    case PC_COVERTOPS:
        return weapon == WP_STEN || weapon == WP_FG42 ||
            weapon == (team == TEAM_AXIS ? WP_K43 : WP_GARAND);
    default: return 0;
    }
}
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
int main( void ) {
    int cls, pickup, any, options, primary, silent, flags, reason, weapon, expected, team;
    entity.client = &client;
    for( cls = PC_SOLDIER; cls <= PC_COVERTOPS; cls++ )
    for( team = TEAM_FREE; team <= TEAM_SPECTATOR; team++ )
    for( weapon = 0; weapon < WP_NUM_WEAPONS; weapon++ )
    for( pickup = 0; pickup < 2; pickup++ ) for( any = 0; any < 2; any++ ) {
        client.sess.playerType = cls; client.sess.sessionTeam = (team_t)team;
        expected = ExpectedPrimary(cls, team, weapon);
        if( (team == TEAM_AXIS || team == TEAM_ALLIES) && pickup && any ) expected = 1;
        before = client;
        CHECK( G_NITMOD_IsClassPrimary(&entity, weapon, pickup, any) == expected );
        CHECK( !memcmp(&client, &before, sizeof(client)) );
    }
    client.sess.sessionTeam = TEAM_AXIS;
    client.sess.playerType = -1;
    CHECK( !G_NITMOD_IsClassPrimary(&entity, WP_MP40, 0, 0) );
    CHECK( G_NITMOD_IsClassPrimary(&entity, WP_NONE, 1, 1) );
    client.sess.playerType = PC_COVERTOPS + 1;
    CHECK( !G_NITMOD_IsClassPrimary(&entity, WP_STEN, 0, 0) );
    CHECK( !G_NITMOD_IsClassPrimary(&entity, -1, 1, 1) );
    CHECK( !G_NITMOD_IsClassPrimary(&entity, WP_NUM_WEAPONS, 1, 1) );
    CHECK( !G_NITMOD_IsClassPrimary(NULL, WP_STEN, 1, 1) );
    for( cls = PC_SOLDIER; cls <= PC_COVERTOPS; cls++ )
    for( pickup = 0; pickup < 2; pickup++ ) for( any = 0; any < 2; any++ )
    for( options = 0; options < 1024; options++ ) {
        client.sess.playerType = cls; before = client;
        expected = cls == PC_COVERTOPS || (pickup && any) || options >= 512;
        CHECK( G_NITMOD_StenAllowed(&entity, pickup, any, options) == expected );
        CHECK( !memcmp(&client, &before, sizeof(client)) );
    }
    for( weapon = 0; weapon < WP_NUM_WEAPONS; weapon++ )
    for( primary = 0; primary < 2; primary++ ) for( silent = 0; silent < 2; silent++ )
    for( flags = 0; flags < 4; flags++ ) for( reason = -1; reason <= 3; reason++ ) {
        client.ps.pm_flags = (flags & 1 ? PMF_LIMBO : 0) | (flags & 2 ? PMF_FOLLOW : 0);
        expected = 0;
        if( primary && !silent && !(flags & 1) ) {
            if( reason == NITMOD_LIMIT_HEAVY ) expected = 19;
            if( reason == NITMOD_LIMIT_PANZER_TEAM ) expected = 20;
            if( reason == NITMOD_LIMIT_FIXED ) {
                if( weapon == WP_PANZERFAUST ) expected = 21;
                if( weapon == WP_FLAMETHROWER ) expected = 22;
                if( weapon == WP_MOBILE_MG42 ) expected = 23;
                if( weapon == WP_MORTAR ) expected = 24;
                if( weapon == WP_GPG40 || weapon == WP_M7 ) expected = 25;
            }
        }
        before = client;
        CHECK( G_NITMOD_LimitMessage(&entity, weapon, (nitmodWeaponLimit_t)reason, primary, silent) == expected );
        CHECK( !memcmp(&client, &before, sizeof(client)) );
    }
    CHECK( !G_NITMOD_StenAllowed(NULL, 1, 1, ~0u) );
    CHECK( !G_NITMOD_LimitMessage(NULL, WP_MORTAR, NITMOD_LIMIT_FIXED, 1, 0) );
    entity.client = NULL;
    CHECK( !G_NITMOD_IsClassPrimary(&entity, WP_STEN, 1, 1) );
    return 0;
}
