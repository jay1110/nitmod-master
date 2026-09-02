#include "g_local.h"
#include "g_nitmod_entities.h"

static gentity_t items[8], owners[2];
static int released[8], releaseCount, errors;
void QDECL G_Error( const char *fmt, ... ) { (void)fmt; errors++; }
static void Release( gentity_t *entity ) {
    if( entity->parent || entity->r.ownerNum != ENTITYNUM_NONE ) errors++;
    released[releaseCount++] = (int)(entity - items);
    /* G_FreeEntity repeats these removals; they must be harmless. */
    G_NITMOD_UnregisterLandmine( entity );
    G_NITMOD_UnregisterSatchel( entity );
    entity->inuse = qfalse;
}
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    int i;
    for( i = 0; i < 8; i++ ) {
        items[i].parent = &owners[0];
        items[i].inuse = qtrue;
        items[i].s.teamNum = TEAM_AXIS;
    }
    items[1].parent = &owners[1];
    items[4].parent = NULL; /* map mine */
    items[5].inuse = qfalse;
    G_NITMOD_ResetEntityLists();
    for( i = 0; i < 6; i++ ) G_NITMOD_RegisterLandmine( &items[i] );
    G_NITMOD_RegisterSatchel( &items[6] );
    G_NITMOD_RegisterSatchel( &items[7] );
    G_NITMOD_FadeLandmines( NULL, Release );
    G_NITMOD_FadeLandmines( &owners[0], NULL );
    CHECK( releaseCount == 0 );
    G_NITMOD_FadeLandmines( &owners[0], Release );
    CHECK( releaseCount == 3 );
    CHECK( released[0] == 3 && released[1] == 2 && released[2] == 0 );
    CHECK( items[1].parent == &owners[1] && items[1].inuse );
    CHECK( !items[4].parent && items[4].inuse );
    CHECK( items[5].parent == &owners[0] );
    CHECK( G_NITMOD_CountTeamLandmines( TEAM_AXIS, 10 ) == 3 );
    CHECK( G_NITMOD_FindSatchel( &owners[0] ) == &items[6] );
    G_NITMOD_FadeLandmines( &owners[0], Release );
    CHECK( releaseCount == 3 );
    G_NITMOD_FadeSatchels( &owners[0], Release );
    CHECK( releaseCount == 5 && released[3] == 7 && released[4] == 6 );
    CHECK( !G_NITMOD_FindSatchel( &owners[0] ) );
    G_NITMOD_FadeLandmines( &owners[1], Release );
    CHECK( releaseCount == 6 && released[5] == 1 );
    /* Slot reuse does not inherit the former owner's cleanup membership. */
    items[0].parent = &owners[1]; items[0].inuse = qtrue;
    G_NITMOD_RegisterLandmine( &items[0] );
    G_NITMOD_FadeLandmines( &owners[0], Release );
    CHECK( releaseCount == 6 && items[0].inuse );
    G_NITMOD_FadeLandmines( &owners[1], Release );
    CHECK( releaseCount == 7 && released[6] == 0 );
    CHECK( errors == 0 );
    return 0;
}
