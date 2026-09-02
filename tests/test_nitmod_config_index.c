#include <stdio.h>
#include "nitmod_config_index.h"

#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

typedef struct {
    const char *slots[4];
    int reads;
    int badIndex;
} fixture_t;

static const char *ReadSlot( void *context, int index ) {
    fixture_t *fixture = (fixture_t *)context;
    fixture->reads++;
    if( index < 1 || index >= 4 ) {
        fixture->badIndex = 1;
        return NULL;
    }
    return fixture->slots[index];
}

int main( void ) {
    fixture_t fixture = { { "reserved", "first", "", "later" }, 0, 0 };
    int write = 99;
    int index;
    CHECK( NITMOD_FindConfigIndex( NULL, 4, 1, ReadSlot, &fixture, &write ) == 0 );
    CHECK( write == 0 && fixture.reads == 0 );
    CHECK( NITMOD_FindConfigIndex( "", 4, 1, ReadSlot, &fixture, &write ) == 0 );
    CHECK( NITMOD_FindConfigIndex( "first", 4, 1, ReadSlot, &fixture, &write ) == 1 );
    CHECK( write == 0 );
    /* A hole ends the search, even if the same name appears beyond it. */
    CHECK( NITMOD_FindConfigIndex( "later", 4, 0, ReadSlot, &fixture, &write ) == 0 );
    CHECK( write == 0 );
    index = NITMOD_FindConfigIndex( "later", 4, 1, ReadSlot, &fixture, &write );
    CHECK( index == 2 && write == 1 );
    /* The owner performs the write. Repeating allocation finds that slot. */
    fixture.slots[index] = "later";
    CHECK( NITMOD_FindConfigIndex( "later", 4, 1, ReadSlot, &fixture, &write ) == 2 );
    CHECK( write == 0 );
    CHECK( NITMOD_FindConfigIndex( "FIRST", 4, 0, ReadSlot, &fixture, &write ) == 0 );
    CHECK( NITMOD_FindConfigIndex( "missing", 4, 0, ReadSlot, &fixture, &write ) == 0 );
    CHECK( NITMOD_FindConfigIndex( "missing", 4, 1, ReadSlot, &fixture, &write ) == -1 );
    CHECK( write == 0 );
    fixture.slots[3] = "";
    CHECK( NITMOD_FindConfigIndex( "last", 4, 1, ReadSlot, &fixture, &write ) == 3 );
    CHECK( write == 1 );
    CHECK( NITMOD_FindConfigIndex( "first", 1, 1, ReadSlot, &fixture, &write ) == -1 );
    CHECK( NITMOD_FindConfigIndex( "first", 1, 0, ReadSlot, &fixture, &write ) == 0 );
    CHECK( NITMOD_FindConfigIndex( "first", 0, 1, ReadSlot, &fixture, &write ) == -2 );
    CHECK( NITMOD_FindConfigIndex( "first", -1, 1, ReadSlot, &fixture, &write ) == -2 );
    CHECK( NITMOD_FindConfigIndex( "first", 4, 1, NULL, &fixture, &write ) == -2 );
    CHECK( NITMOD_FindConfigIndex( "first", 4, 1, ReadSlot, &fixture, NULL ) == -2 );
    CHECK( !fixture.badIndex );
    return 0;
}
