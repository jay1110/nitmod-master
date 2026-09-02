#include <stdio.h>
#include <string.h>
#include "nitmod_entity_array.h"

/* Complete the forward declaration without importing engine dependencies. */
struct gentity_s { int identity; };
static struct gentity_s entities[NITMOD_ENTITY_ARRAY_CAPACITY + 1];
static nitmodEntityArray_t array, before;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    int i;
    NITMOD_InitEntityArray( &array );
    CHECK( array.count == 0 );
    CHECK( NITMOD_RemoveEntityFromArray( &array, &entities[0] ) == NITMOD_ENTITY_ARRAY_UNCHANGED );
    for( i = 0; i < NITMOD_ENTITY_ARRAY_CAPACITY; i++ ) {
        CHECK( NITMOD_AddEntityToArray( &array, &entities[i] ) == NITMOD_ENTITY_ARRAY_CHANGED );
        CHECK( array.count == i + 1 && array.entities[i] == &entities[i] );
        if( i + 1 < NITMOD_ENTITY_ARRAY_CAPACITY ) {
            before = array;
            CHECK( NITMOD_AddEntityToArray( &array, &entities[i] ) == NITMOD_ENTITY_ARRAY_UNCHANGED );
            CHECK( !memcmp( &array, &before, sizeof(array) ) );
        }
    }
    before = array;
    CHECK( NITMOD_AddEntityToArray( &array, &entities[1024] ) == NITMOD_ENTITY_ARRAY_FULL );
    CHECK( NITMOD_AddEntityToArray( &array, &entities[0] ) == NITMOD_ENTITY_ARRAY_FULL );
    CHECK( !memcmp( &array, &before, sizeof(array) ) );
    CHECK( NITMOD_RemoveEntityFromArray( &array, &entities[512] ) == NITMOD_ENTITY_ARRAY_CHANGED );
    CHECK( array.count == 1023 );
    for( i = 0; i < array.count; i++ ) {
        CHECK( array.entities[i] == &entities[i < 512 ? i : i + 1] );
    }
    CHECK( NITMOD_RemoveEntityFromArray( &array, &entities[0] ) == NITMOD_ENTITY_ARRAY_CHANGED );
    CHECK( array.entities[0] == &entities[1] );
    CHECK( NITMOD_RemoveEntityFromArray( &array, &entities[1023] ) == NITMOD_ENTITY_ARRAY_CHANGED );
    CHECK( array.entities[array.count - 1] == &entities[1022] );
    before = array;
    CHECK( NITMOD_RemoveEntityFromArray( &array, &entities[512] ) == NITMOD_ENTITY_ARRAY_UNCHANGED );
    CHECK( !memcmp( &array, &before, sizeof(array) ) );
    NITMOD_InitEntityArray( &array );
    CHECK( array.count == 0 && array.entities[0] == before.entities[0] );
    /* The reference treats zero as a value too; no dereference is performed. */
    CHECK( NITMOD_AddEntityToArray( &array, NULL ) == NITMOD_ENTITY_ARRAY_CHANGED );
    CHECK( NITMOD_AddEntityToArray( &array, NULL ) == NITMOD_ENTITY_ARRAY_UNCHANGED );
    CHECK( NITMOD_RemoveEntityFromArray( &array, NULL ) == NITMOD_ENTITY_ARRAY_CHANGED );
    CHECK( array.count == 0 );
    array.count = -1; before = array;
    CHECK( NITMOD_AddEntityToArray( &array, &entities[0] ) == NITMOD_ENTITY_ARRAY_INVALID );
    CHECK( NITMOD_RemoveEntityFromArray( &array, &entities[0] ) == NITMOD_ENTITY_ARRAY_INVALID );
    CHECK( !memcmp( &array, &before, sizeof(array) ) );
    array.count = NITMOD_ENTITY_ARRAY_CAPACITY + 1; before = array;
    CHECK( NITMOD_AddEntityToArray( &array, NULL ) == NITMOD_ENTITY_ARRAY_INVALID );
    CHECK( NITMOD_RemoveEntityFromArray( &array, NULL ) == NITMOD_ENTITY_ARRAY_INVALID );
    CHECK( !memcmp( &array, &before, sizeof(array) ) );
    NITMOD_InitEntityArray( NULL );
    CHECK( NITMOD_AddEntityToArray( NULL, NULL ) == NITMOD_ENTITY_ARRAY_INVALID );
    CHECK( NITMOD_RemoveEntityFromArray( NULL, NULL ) == NITMOD_ENTITY_ARRAY_INVALID );
    return 0;
}
