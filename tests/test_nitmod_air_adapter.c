#include <limits.h>
#include "g_local.h"
#include "g_nitmod_air.h"
#include "nitmod_air.h"

static gentity_t entity;
static gclient_t client;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

/* Numeric reference of the pre-adapter ET branch, for ordinary clock values. */
static int NativeAir( int now, int water, int noclip, int health,
    int *deadline, int *damage, int *breather ) {
    if( noclip ) { *deadline = now + 12000; return 0; }
    if( water != 3 ) { *deadline = now + 12000; *damage = 2; return 0; }
    if( *deadline >= now ) return 0;
    if( *breather ) {
        *breather -= now - *deadline;
        *deadline = now + (now - *deadline);
        return 0;
    }
    *deadline += 1000;
    if( health <= 0 ) return 0;
    *damage += 2;
    if( *damage > 15 ) *damage = 15;
    return *damage;
}

int main( void ) {
    int water, noclip, health, b, tick, expected, deadline, damage, breather;
    static const int reserves[] = { 0, 1, 100, -5 };
    entity.client = &client;
    for( water = 0; water <= 3; water++ ) for( noclip = 0; noclip <= 1; noclip++ )
    for( health = 0; health <= 100; health += 100 ) for( b = 0; b < 4; b++ ) {
        deadline = client.airOutTime = 1000;
        damage = entity.damage = 2;
        breather = client.ps.powerups[PW_BREATHER] = reserves[b];
        entity.waterlevel = water;
        entity.health = health;
        client.noclip = noclip;
        for( tick = 1000; tick < 12000; tick += 101 ) {
            expected = NativeAir(tick, water, noclip, health, &deadline, &damage, &breather);
            CHECK( G_NITMOD_UpdateClientAir(&entity, tick, 0) == expected );
            CHECK( client.airOutTime == deadline && entity.damage == damage );
            CHECK( client.ps.powerups[PW_BREATHER] == breather );
        }
    }
    /* Spawn then pause preserves the remaining reserve; resuming at the
     * exact deadline does not cause damage until the next tick. */
    client.noclip = 0; entity.waterlevel = 3; entity.health = 100;
    client.ps.powerups[PW_BREATHER] = 0; entity.damage = 2;
    client.airOutTime = NITMOD_AirDeadline(100, 0);
    client.airOutTime = NITMOD_ShiftAirDeadline(client.airOutTime, 5000);
    CHECK( NITMOD_AirRemaining(client.airOutTime, 5100) == 12000 );
    CHECK( !G_NITMOD_UpdateClientAir(&entity, 17100, 0) );
    CHECK( G_NITMOD_UpdateClientAir(&entity, 17101, 0) == 4 );
    /* Respawn only changes the deadline, just like the original callsite. */
    client.airOutTime = NITMOD_AirDeadline(20000, 0);
    CHECK( client.airOutTime == 32000 && entity.damage == 4 );
    client.noclip = 0; entity.waterlevel = 0; entity.damage = 10;
    CHECK( !G_NITMOD_UpdateClientAir(&entity, 1000, 32) );
    CHECK( client.airOutTime == 16000 && entity.damage == 2 );
    CHECK( !G_NITMOD_UpdateClientAir(&entity, INT_MAX, 0) );
    CHECK( client.airOutTime == INT_MAX );
    entity.waterlevel = 3; client.airOutTime = INT_MIN;
    client.ps.powerups[PW_BREATHER] = 1;
    CHECK( !G_NITMOD_UpdateClientAir(&entity, INT_MAX, 0) );
    CHECK( client.airOutTime == INT_MAX && client.ps.powerups[PW_BREATHER] == INT_MIN );
    CHECK( !G_NITMOD_UpdateClientAir(NULL, 0, 0) );
    entity.client = NULL;
    CHECK( !G_NITMOD_UpdateClientAir(&entity, 0, 0) );
    return 0;
}
