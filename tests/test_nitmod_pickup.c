#include "g_local.h"
#include "g_nitmod_restrictions.h"
static gentity_t entity;
static gclient_t client, before;
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    static const int base[5][6] = {
        {WP_PANZERFAUST, WP_FLAMETHROWER, WP_MOBILE_MG42, WP_MORTAR, WP_MP40, WP_THOMPSON},
        {WP_MP40, WP_THOMPSON, WP_STEN, -1, -1, -1},
        {WP_MP40, WP_THOMPSON, WP_KAR98, WP_CARBINE, -1, -1},
        {WP_MP40, WP_THOMPSON, WP_STEN, -1, -1, -1},
        {WP_STEN, WP_FG42, WP_GARAND, WP_K43, -1, -1}
    };
    int cls, weapon, mode, any, mask, medic, expected, i;
    entity.client = &client;
    for( cls = 0; cls < 5; cls++ ) for( weapon = 0; weapon < WP_NUM_WEAPONS; weapon++ )
    for( mode = 0; mode <= 5; mode++ ) for( any = 0; any < 2; any++ )
    for( mask = 0; mask < 32; mask++ ) for( medic = 0; medic < 2; medic++ ) {
        client.sess.playerType = cls; before = client;
        expected = weapon == WP_KNIFE || any || (mask & (1 << cls));
        if( !expected ) for( i = 0; i < 6; i++ )
            if( base[cls][i] == weapon && !(cls == PC_MEDIC && medic) ) expected = 1;
        if( mode == 1 ) expected = weapon == WP_PANZERFAUST;
        if( mode == 2 ) expected = weapon == WP_GARAND || weapon == WP_K43;
        if( mode == 3 ) expected = weapon == WP_KAR98 || weapon == WP_CARBINE;
        if( mode == 4 ) expected = weapon == WP_KNIFE;
        CHECK( G_NITMOD_PickupPolicy(&entity, weapon, NITMOD_WEAPON_ALLOW, mode, any, mask, medic ? 4 : 0) == !!expected );
        CHECK( !G_NITMOD_PickupPolicy(&entity, weapon, NITMOD_WEAPON_DENY, mode, any, mask, 0) );
        CHECK( !G_NITMOD_PickupPolicy(&entity, weapon, NITMOD_WEAPON_DEFER, mode, any, mask, 0) );
        CHECK( !memcmp(&before, &client, sizeof(client)) );
    }
    CHECK( !G_NITMOD_PickupPolicy(NULL, WP_KNIFE, NITMOD_WEAPON_ALLOW, 0, 1, 31, 0) );
    CHECK( !G_NITMOD_PickupPolicy(&entity, WP_NUM_WEAPONS, NITMOD_WEAPON_ALLOW, 0, 1, 31, 0) );
    client.sess.playerType = -1;
    CHECK( !G_NITMOD_PickupPolicy(&entity, WP_MP40, NITMOD_WEAPON_ALLOW, 0, 0, 31, 0) );
    return 0;
}
