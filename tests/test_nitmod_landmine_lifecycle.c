#include "g_local.h"
#include "g_nitmod_entities.h"
#include "nitmod_entity_array.h"
static gentity_t mines[1025], satchel, owner;
static int errors;
void QDECL G_Error( const char *fmt, ... ) { (void)fmt; errors++; }
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
int main( void ) {
    int i;
    G_NITMOD_ResetEntityLists();
    satchel.parent = &owner;
    G_NITMOD_RegisterSatchel( &satchel );
    mines[0].s.teamNum = TEAM_AXIS + 4;
    mines[1].s.teamNum = TEAM_ALLIES;
    G_NITMOD_RegisterLandmine( &mines[0] );
    G_NITMOD_RegisterLandmine( &mines[1] );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_AXIS, 10 ) == 0 );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_ALLIES, 10 ) == 1 );
    mines[0].s.teamNum = TEAM_AXIS;
    G_NITMOD_RegisterLandmine( &mines[0] );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_AXIS, 10 ) == 1 );
    mines[0].s.teamNum = TEAM_ALLIES;
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_AXIS, 10 ) == 0 );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_ALLIES, 10 ) == 2 );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_ALLIES, 1 ) == 1 );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_ALLIES, 0 ) == 0 );
    mines[0].s.teamNum = TEAM_ALLIES + 4;
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_ALLIES, 10 ) == 1 );
    G_NITMOD_UnregisterLandmine( &mines[1] );
    G_NITMOD_UnregisterLandmine( &mines[1] );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_ALLIES, 10 ) == 0 );
    G_NITMOD_UnregisterLandmine( &satchel );
    G_NITMOD_UnregisterSatchel( &mines[0] );
    CHECK( G_NITMOD_FindSatchel( &owner ) == &satchel );
    mines[1].s.teamNum = TEAM_AXIS;
    G_NITMOD_RegisterLandmine( &mines[1] );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_AXIS, 10 ) == 1 );
    G_NITMOD_ResetEntityLists();
    CHECK( !G_NITMOD_FindSatchel( &owner ) );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_AXIS, 10 ) == 0 );
    for( i = 0; i < 1024; i++ ) {
        mines[i].s.teamNum = TEAM_AXIS;
        G_NITMOD_RegisterLandmine( &mines[i] );
    }
    CHECK( errors == 0 );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_AXIS, 1024 ) == 1024 );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_AXIS, MAX_TEAM_LANDMINES ) == MAX_TEAM_LANDMINES );
    G_NITMOD_RegisterLandmine( &mines[0] );
    G_NITMOD_RegisterLandmine( &mines[1024] );
    CHECK( errors == 2 );
    G_NITMOD_ResetEntityLists();
    G_NITMOD_RegisterLandmine( NULL );
    CHECK( errors == 3 );
    return 0;
}
