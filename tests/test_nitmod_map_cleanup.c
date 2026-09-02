#include "g_local.h"
#include "g_nitmod_entities.h"

gentity_t g_entities[MAX_GENTITIES];
mapEntityData_Team_t mapEntityData[2];
static mapEntityData_t markers[2][2];
static int present[2][2], errors, lookups, frees, releases;
static int expectedSlot;

void QDECL G_Error( const char *fmt, ... ) { (void)fmt; errors++; }
mapEntityData_t *G_FindMapEntityData( mapEntityData_Team_t *list, int number ) {
    int team = (int)(list - mapEntityData);
    int i;
    if( team < 0 || team > 1 || number != expectedSlot ) { errors++; return NULL; }
    lookups++;
    for( i = 0; i < 2; i++ ) {
        if( present[team][i] && markers[team][i].entNum == number ) return &markers[team][i];
    }
    return NULL;
}
mapEntityData_t *G_FreeMapEntityData( mapEntityData_Team_t *list, mapEntityData_t *marker ) {
    int team = (int)(list - mapEntityData);
    if( team < 0 || team > 1 || marker != &markers[team][0] || !present[team][0] ) {
        errors++; return NULL;
    }
    present[team][0] = 0;
    frees++;
    return NULL;
}
void G_FreeEntity( gentity_t *entity ) {
    if( entity != &g_entities[expectedSlot] || present[0][0] || present[1][0] ||
        entity->parent || entity->r.ownerNum != ENTITYNUM_NONE ) errors++;
    releases++;
    G_NITMOD_UnregisterLandmine( entity );
    G_NITMOD_UnregisterSatchel( entity );
    entity->inuse = qfalse;
}
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    int mask, team;
    gentity_t *mine;
    for( mask = 0; mask < 4; mask++ ) {
        G_NITMOD_ResetEntityLists();
        expectedSlot = mask == 3 ? MAX_GENTITIES - 1 : MAX_CLIENTS + mask;
        mine = &g_entities[expectedSlot];
        mine->parent = &g_entities[0];
        mine->inuse = qtrue;
        mine->r.ownerNum = 0;
        mine->s.teamNum = TEAM_AXIS;
        lookups = frees = releases = 0;
        for( team = 0; team < 2; team++ ) {
            markers[team][0].entNum = expectedSlot;
            markers[team][1].entNum = expectedSlot - 1;
            present[team][0] = (mask >> team) & 1;
            present[team][1] = 1;
        }
        G_NITMOD_RegisterLandmine( mine );
        G_NITMOD_FadeLandmines( &g_entities[0], NITMOD_FreeFadedLandmine );
        CHECK( lookups == 2 && releases == 1 );
        CHECK( frees == ((mask & 1) != 0) + ((mask & 2) != 0) );
        CHECK( present[0][1] && present[1][1] );
        CHECK( !mine->inuse && !mine->parent && mine->r.ownerNum == ENTITYNUM_NONE );
        CHECK( G_NITMOD_CountTeamLandmines( TEAM_AXIS, MAX_TEAM_LANDMINES ) == 0 );
        G_NITMOD_FadeLandmines( &g_entities[0], NITMOD_FreeFadedLandmine );
        NITMOD_FreeFadedLandmine( NULL );
        CHECK( lookups == 2 && releases == 1 );
        CHECK( errors == 0 );
    }
    return 0;
}
