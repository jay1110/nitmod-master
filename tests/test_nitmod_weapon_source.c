#include "g_local.h"
#include "g_nitmod_weapon_definition.h"
static const char *tokens[] = { "weaponDef", "{", "client", "{", "}", "}", "both", "{", "classes", "7", "}", "}", "}" };
static int opens, frees, reads, failOpens, count = 12, quoted = 4, badHandle;
static char opened[2][MAX_QPATH];
int trap_PC_LoadSource( const char *filename ) {
    if( opens < 2 ) {
        strncpy(opened[opens], filename, MAX_QPATH - 1);
        opened[opens][MAX_QPATH - 1] = 0;
    }
    opens++;
    if( opens <= failOpens ) return 0;
    return 23;
}
int trap_PC_FreeSource( int handle ) { frees++; if( handle != 23 ) badHandle = 1; return 1; }
int trap_PC_ReadToken( int handle, pc_token_t *token ) {
    if( handle != 23 ) badHandle = 1;
    if( reads >= count ) return 0;
    token->type = reads == 4 || reads == quoted ? TT_STRING : TT_NAME;
    strcpy(token->string, tokens[reads++]);
    return 1;
}
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
static void Reset( void ) { opens = frees = reads = 0; memset(opened, 0, sizeof(opened)); }
int main( void ) {
    unsigned int mask = 99;
    ammotable_t ammo, baseline = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    char directory[MAX_QPATH + 1];
    size_t limit;
    CHECK( G_NITMOD_LoadWeaponClassMask("custom/x.weap", "weapons/x.weap", 0, &mask) );
    CHECK( mask == 7 && opens == 1 && frees == 1 && !badHandle );
    Reset(); failOpens = 1;
    CHECK( G_NITMOD_LoadWeaponClassMask("custom/x.weap", "weapons/x.weap", 1, &mask) );
    CHECK( !mask && opens == 2 && frees == 1 );
    Reset(); failOpens = 2; mask = 99;
    CHECK( !G_NITMOD_LoadWeaponClassMask("custom/x.weap", "weapons/x.weap", 0, &mask) );
    CHECK( mask == 99 && opens == 2 && !frees );
    Reset(); failOpens = 0; count = 11;
    CHECK( !G_NITMOD_LoadWeaponClassMask("custom/x.weap", "weapons/x.weap", 0, &mask) );
    CHECK( mask == 99 && opens == 1 && frees == 1 ); /* no fallback on parse failure */
    Reset(); count = 12; quoted = 9;
    CHECK( !G_NITMOD_LoadWeaponClassMask("custom/x.weap", NULL, 0, &mask) );
    CHECK( mask == 99 && frees == 1 );
    Reset();
    CHECK( !G_NITMOD_LoadWeaponClassMask(NULL, "weapons/x.weap", 0, &mask) );
    CHECK( !G_NITMOD_LoadWeaponClassMask("x.weap", NULL, 0, NULL) );
    CHECK( !opens && !frees && !badHandle );
    Reset(); failOpens = 0; count = 13; quoted = 4;
    tokens[6] = "both_altweap"; tokens[8] = "maxclip";
    tokens[9] = "-"; tokens[10] = "2147483648";
    ammo = baseline; mask = 99;
    CHECK( G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( ammo.maxclip == (-2147483647 - 1) && !mask && frees == 1 );
    Reset(); tokens[10] = "-0"; ammo = baseline; mask = 99;
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 99 && frees == 1 );
    /* Restore fixtures for the remaining loader cases. */
    count = 12; tokens[6] = "both"; tokens[8] = "classes"; tokens[9] = "7"; tokens[10] = "}";
    Reset(); quoted = 4; mask = 99;
    CHECK( G_NITMOD_LoadNativeWeaponClassMask(WP_K43, "custom", &mask) );
    CHECK( mask == 7 && opens == 1 && frees == 1 );
    CHECK( !strcmp(opened[0], "custom/k43.weap") );
    Reset(); failOpens = 1;
    CHECK( G_NITMOD_LoadNativeWeaponClassMask(WP_K43_SCOPE, "custom", &mask) );
    CHECK( mask == 0 && opens == 2 && frees == 1 );
    CHECK( !strcmp(opened[0], "custom/k43.weap") && !strcmp(opened[1], "weapons/k43.weap") );
    Reset(); failOpens = 0; tokens[6] = "both_altweap";
    CHECK( G_NITMOD_LoadNativeWeaponClassMask(WP_MOBILE_MG42_SET, "custom", &mask) );
    CHECK( mask == 7 && !strcmp(opened[0], "custom/mg42.weap") );
    Reset();
    CHECK( G_NITMOD_LoadNativeWeaponClassMask(WP_MORTAR_SET, "custom", &mask) );
    CHECK( mask == 0 && !strcmp(opened[0], "custom/mortar_set.weap") );
    Reset(); failOpens = 1; mask = 99;
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, "weapons", &mask) );
    CHECK( mask == 99 && opens == 1 && !frees ); /* same path is not reopened */
    Reset(); failOpens = 0;
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_ARTY, "custom", &mask) );
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(-1, "custom", &mask) );
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, NULL, &mask) );
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, "", &mask) );
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, "custom", NULL) );
    memset(directory, 'x', sizeof(directory)); directory[MAX_QPATH] = 0;
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, directory, &mask) );
    CHECK( mask == 99 && !opens && !frees );
    limit = MAX_QPATH - strlen("k43.weap") - 2;
    directory[limit + 1] = 0;
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43, directory, &mask) );
    CHECK( mask == 99 && !opens );
    directory[limit] = 0;
    CHECK( G_NITMOD_LoadNativeWeaponClassMask(WP_K43, directory, &mask) );
    CHECK( strlen(opened[0]) == MAX_QPATH - 1 && frees == 1 );
    Reset(); count = 11; mask = 99;
    CHECK( !G_NITMOD_LoadNativeWeaponClassMask(WP_K43_SCOPE, "custom", &mask) );
    CHECK( mask == 99 && opens == 1 && frees == 1 && !badHandle );
    Reset(); count = 12; tokens[8] = "maxclip"; tokens[9] = "37";
    ammo = baseline; failOpens = 1;
    CHECK( G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( ammo.maxclip == 37 && ammo.uses == 2 && ammo.mod == 11 && !mask );
    CHECK( opens == 2 && frees == 1 && !strcmp(opened[1], "weapons/k43.weap") );
    Reset(); failOpens = 0; ammo = baseline; mask = 99;
    CHECK( G_NITMOD_LoadNativeWeaponAmmo(WP_K43, "custom", &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && !mask ); /* unselected block */
    Reset(); count = 11; mask = 99;
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 99 );
    CHECK( opens == 1 && frees == 1 ); /* rollback after a parsed ammo assignment */
    Reset(); count = 12; quoted = 9;
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 99 && frees == 1 );
    Reset(); quoted = 4; failOpens = 2;
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, &mask) );
    CHECK( !memcmp(&ammo, &baseline, sizeof(ammo)) && mask == 99 && opens == 2 && !frees );
    Reset();
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", NULL, &mask) );
    CHECK( !G_NITMOD_LoadNativeWeaponAmmo(WP_K43_SCOPE, "custom", &ammo, NULL) );
    CHECK( !opens && !frees && !badHandle );
    return 0;
}
