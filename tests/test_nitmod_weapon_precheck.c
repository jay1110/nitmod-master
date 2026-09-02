#include <limits.h>
#include "g_local.h"
#include "g_nitmod_restrictions.h"
static gentity_t entity, originalEntity;
static gclient_t client, originalClient;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    int mode, weapon, team, bot, i, expected;
    static const int exemptions[][2] = {
        { 1, WP_PANZERFAUST }, { 2, WP_GARAND }, { 2, WP_K43 },
        { 3, WP_GPG40 }, { 3, WP_M7 }, { 3, WP_KAR98 }, { 3, WP_CARBINE }, { 4, WP_KNIFE }
    };
    entity.client = &client;
    for( mode = -1; mode <= 5; mode++ ) for( weapon = 0; weapon < WP_NUM_WEAPONS; weapon++ )
    for( team = TEAM_FREE; team <= TEAM_SPECTATOR; team++ ) for( bot = 0; bot <= 1; bot++ ) {
        client.sess.sessionTeam = (team_t)team;
        entity.r.svFlags = bot ? SVF_BOT : 0;
        originalEntity = entity;
        originalClient = client;
        expected = NITMOD_WEAPON_DEFER;
        for( i = 0; i < sizeof(exemptions) / sizeof(exemptions[0]); i++ ) {
            if( mode == exemptions[i][0] && weapon == exemptions[i][1] ) expected = NITMOD_WEAPON_ALLOW;
        }
        if( team == TEAM_SPECTATOR && !bot ) expected = NITMOD_WEAPON_DENY;
        CHECK( G_NITMOD_WeaponPrecheck(&entity, weapon, mode) == expected );
        CHECK( !memcmp(&entity, &originalEntity, sizeof(entity)) );
        CHECK( !memcmp(&client, &originalClient, sizeof(client)) );
    }
    CHECK( G_NITMOD_WeaponPrecheck(&entity, INT_MIN, 4) == NITMOD_WEAPON_DENY );
    CHECK( G_NITMOD_WeaponPrecheck(&entity, WP_NUM_WEAPONS, 4) == NITMOD_WEAPON_DENY );
    CHECK( G_NITMOD_WeaponPrecheck(NULL, WP_KNIFE, 4) == NITMOD_WEAPON_DENY );
    entity.client = NULL;
    CHECK( G_NITMOD_WeaponPrecheck(&entity, WP_KNIFE, 4) == NITMOD_WEAPON_DENY );
    return 0;
}
