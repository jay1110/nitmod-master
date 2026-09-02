#include <stdio.h>
#include <string.h>
#include "nitmod_config_store.h"

#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

/* The production store is static too; never put 650 KB on the VM stack. */
static nitmodConfigStore_t store;
static nitmodConfigStore_t before;

int main( void ) {
    char value[NITMOD_CONFIGSTRING_CHARS + 1];
    const char *unsafe[] = { "bad\"name", "bad\nname", "bad\rname" };
    int i;
    NITMOD_ClearConfigStore( &store );
    CHECK( !store.hasDirty );
    CHECK( NITMOD_StoreConfig( &store, 0, NULL ) == NITMOD_CONFIG_UNCHANGED );
    CHECK( !store.hasDirty );

    /* All 655 slots, including the endpoints, can change in one frame. */
    for( i = 0; i < NITMOD_MAX_CONFIGSTRINGS; i++ ) {
        sprintf( value, "asset-%d", i );
        CHECK( NITMOD_StoreConfig( &store, i, value ) == NITMOD_CONFIG_UPDATED );
        CHECK( store.dirty[i] && !strcmp( store.values[i], value ) );
    }
    CHECK( store.hasDirty );
    CHECK( NITMOD_StoreConfig( &store, 0, "asset-0" ) == NITMOD_CONFIG_UNCHANGED );
    CHECK( store.dirty[0] );
    NITMOD_ClearConfigDirty( &store );
    CHECK( !store.hasDirty );
    for( i = 0; i < NITMOD_MAX_CONFIGSTRINGS; i++ ) {
        CHECK( !store.dirty[i] && store.values[i][0] );
    }

    /* Failed writes preserve the entire store, not just the destination. */
    before = store;
    CHECK( NITMOD_StoreConfig( &store, -1, "invalid" ) == NITMOD_CONFIG_BAD_INDEX );
    CHECK( NITMOD_StoreConfig( &store, NITMOD_MAX_CONFIGSTRINGS, "invalid" ) == NITMOD_CONFIG_BAD_INDEX );
    for( i = 0; i < 3; i++ ) {
        CHECK( NITMOD_StoreConfig( &store, 0, unsafe[i] ) == NITMOD_CONFIG_UNSAFE );
    }
    memset( value, 'x', sizeof(value) );
    value[NITMOD_CONFIGSTRING_CHARS] = 0;
    CHECK( NITMOD_StoreConfig( &store, 0, value ) == NITMOD_CONFIG_TOO_LONG );
    CHECK( !memcmp( &store, &before, sizeof(store) ) );
    CHECK( NITMOD_StoreConfig( &store, 643, "\\id\\-1" ) == NITMOD_CONFIG_UPDATED );
    CHECK( !strcmp(store.values[643], "\\id\\-1") && store.dirty[643] );
    CHECK( NITMOD_StoreConfig( &store, 643, "\\id\\-1" ) == NITMOD_CONFIG_UNCHANGED );

    value[NITMOD_CONFIGSTRING_CHARS - 1] = 0;
    CHECK( NITMOD_StoreConfig( &store, 0, value ) == NITMOD_CONFIG_UPDATED );
    CHECK( strlen( store.values[0] ) == NITMOD_CONFIGSTRING_CHARS - 1 );
    CHECK( NITMOD_StoreConfig( &store, 0, store.values[0] ) == NITMOD_CONFIG_UNCHANGED );
    CHECK( store.dirty[0] );
    CHECK( NITMOD_StoreConfig( &store, 0, store.values[0] + 1 ) == NITMOD_CONFIG_UPDATED );
    CHECK( strlen( store.values[0] ) == NITMOD_CONFIGSTRING_CHARS - 2 );

    /* Clearing a previously populated slot must reach the dirty pass. */
    NITMOD_ClearConfigDirty( &store );
    CHECK( NITMOD_StoreConfig( &store, 0, NULL ) == NITMOD_CONFIG_UPDATED );
    CHECK( !store.values[0][0] && store.dirty[0] && store.hasDirty );
    CHECK( NITMOD_StoreConfig( &store, 0, "" ) == NITMOD_CONFIG_UNCHANGED );
    CHECK( store.dirty[0] );
    NITMOD_ClearConfigStore( &store );
    CHECK( !store.hasDirty );
    for( i = 0; i < NITMOD_MAX_CONFIGSTRINGS; i++ ) {
        CHECK( !store.values[i][0] && !store.dirty[i] );
    }
    return 0;
}
