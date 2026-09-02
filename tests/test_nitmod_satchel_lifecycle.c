#include "g_local.h"
#include "g_nitmod_entities.h"
#include "nitmod_entity_array.h"

static gentity_t entities[NITMOD_ENTITY_ARRAY_CAPACITY + 1];
static gentity_t owners[2];
static int errors;

void QDECL G_Error( const char *fmt, ... ) {
    (void)fmt;
    errors++;
}

#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    int i;
    G_NITMOD_ResetEntityLists();
    CHECK( !G_NITMOD_FindSatchel( &owners[0] ) );
    entities[7].parent = &owners[0];
    entities[2].parent = &owners[0];
    entities[3].parent = &owners[1];
    G_NITMOD_RegisterSatchel( &entities[7] );
    G_NITMOD_RegisterSatchel( &entities[2] );
    G_NITMOD_RegisterSatchel( &entities[3] );
    G_NITMOD_RegisterSatchel( &entities[7] );
    /* Creation order, not entity slot order, determines the first match. */
    CHECK( G_NITMOD_FindSatchel( &owners[0] ) == &entities[7] );
    CHECK( G_NITMOD_FindSatchel( &owners[1] ) == &entities[3] );
    G_NITMOD_UnregisterSatchel( &entities[7] );
    CHECK( G_NITMOD_FindSatchel( &owners[0] ) == &entities[2] );
    /* Explosion followed by deferred free must be harmless. */
    G_NITMOD_UnregisterSatchel( &entities[7] );
    entities[7].parent = &owners[1];
    G_NITMOD_RegisterSatchel( &entities[7] );
    G_NITMOD_UnregisterSatchel( &entities[3] );
    CHECK( G_NITMOD_FindSatchel( &owners[1] ) == &entities[7] );
    G_NITMOD_ResetEntityLists();
    CHECK( !G_NITMOD_FindSatchel( &owners[0] ) );
    CHECK( !G_NITMOD_FindSatchel( &owners[1] ) );
    for( i = 0; i < NITMOD_ENTITY_ARRAY_CAPACITY; i++ ) {
        G_NITMOD_RegisterSatchel( &entities[i] );
    }
    CHECK( errors == 0 );
    G_NITMOD_RegisterSatchel( &entities[0] );
    CHECK( errors == 1 );
    G_NITMOD_RegisterSatchel( &entities[NITMOD_ENTITY_ARRAY_CAPACITY] );
    CHECK( errors == 2 );
    G_NITMOD_ResetEntityLists();
    G_NITMOD_RegisterSatchel( NULL );
    CHECK( errors == 3 );
    CHECK( !G_NITMOD_FindSatchel( &owners[0] ) );
    return 0;
}
