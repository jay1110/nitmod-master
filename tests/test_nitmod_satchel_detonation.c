#include "g_local.h"
#include "g_nitmod_entities.h"

static gentity_t charges[8], owner, other;
static int calls[8], count, mutate, errors;
void QDECL G_Error( const char *fmt, ... ) { (void)fmt; errors++; }
static void Explode( gentity_t *entity ) {
    calls[count++] = (int)(entity - charges);
    G_NITMOD_UnregisterSatchel( entity );
    entity->s.eType = ET_GENERAL;
    if( mutate && entity == &charges[0] ) {
        /* Removed, reused, transferred and newly-created entities must not
         * become accidental targets of this already-started command. */
        G_NITMOD_UnregisterSatchel( &charges[1] );
        G_NITMOD_UnregisterSatchel( &charges[2] );
        charges[2].spawnCount++;
        G_NITMOD_RegisterSatchel( &charges[2] );
        charges[3].parent = &other;
        G_NITMOD_RegisterSatchel( &charges[6] );
    }
}
static void Setup( int registered ) {
    int i;
    G_NITMOD_ResetEntityLists();
    memset( charges, 0, sizeof(charges) );
    memset( &owner, 0, sizeof(owner) );
    count = 0; mutate = 0;
    for( i = 0; i < 8; i++ ) {
        charges[i].parent = &owner;
        charges[i].inuse = qtrue;
        charges[i].s.eType = ET_MISSILE;
        charges[i].methodOfDeath = MOD_SATCHEL;
        charges[i].spawnCount = 1;
        if( i < registered ) G_NITMOD_RegisterSatchel( &charges[i] );
    }
}
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
int main( void ) {
    Setup( 3 );
    CHECK( G_NITMOD_ExplodeSatchels( &owner, Explode ) == 3 );
    CHECK( count == 3 && calls[0] == 0 && calls[1] == 1 && calls[2] == 2 );
    CHECK( !G_NITMOD_ExplodeSatchels( &owner, Explode ) );
    Setup( 8 );
    owner.r.currentOrigin[0] = 100;
    charges[0].r.currentOrigin[0] = 2100; /* inclusive boundary */
    charges[1].r.currentOrigin[0] = 2101;
    charges[2].r.currentOrigin[1] = 2000; /* diagonal is outside */
    charges[3].parent = &other;
    charges[4].inuse = qfalse;
    charges[5].s.eType = ET_GENERAL;
    charges[6].methodOfDeath = MOD_LANDMINE;
    charges[7].r.currentOrigin[0] = -1900;
    CHECK( G_NITMOD_ExplodeSatchels( &owner, Explode ) == 2 );
    CHECK( count == 2 && calls[0] == 0 && calls[1] == 7 );
    Setup( 6 );
    mutate = 1;
    CHECK( G_NITMOD_ExplodeSatchels( &owner, Explode ) == 3 );
    CHECK( count == 3 && calls[0] == 0 && calls[1] == 4 && calls[2] == 5 );
    CHECK( charges[2].s.eType == ET_MISSILE && charges[6].s.eType == ET_MISSILE );
    CHECK( !G_NITMOD_ExplodeSatchels( NULL, Explode ) );
    CHECK( !G_NITMOD_ExplodeSatchels( &owner, NULL ) );
    CHECK( errors == 0 );
    return 0;
}
