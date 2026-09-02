#include "q_shared.h"
#include "bg_public.h"
#include "nitmod_weapon_paths.h"
#include <limits.h>
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    const nitmodWeaponPath_t *path;
    int weapon, count = 0, alternatives = 0;
    for( weapon = WP_NONE; weapon < WP_NUM_WEAPONS; ++weapon ) {
        path = NITMOD_WeaponPath(weapon);
        if( weapon == WP_NONE || weapon == WP_ARTY || weapon == WP_MAPMORTAR ||
            weapon == VERYBIGEXPLOSION || weapon == WP_DUMMY_MG42 || weapon == WP_LOCKPICK ) {
            CHECK( !path );
            continue;
        }
        CHECK( path && path == NITMOD_WeaponPath(weapon) );
        CHECK( strstr(path->filename, ".weap") && !strchr(path->filename, '/') );
        CHECK( path->alternate == (weapon == WP_GARAND_SCOPE || weapon == WP_K43_SCOPE ||
            weapon == WP_FG42SCOPE || weapon == WP_MOBILE_MG42_SET) );
        ++count;
        alternatives += path->alternate;
    }
    CHECK( count == 44 && alternatives == 4 );
    CHECK( !NITMOD_WeaponPath(-1) && !NITMOD_WeaponPath(INT_MIN) );
    CHECK( !NITMOD_WeaponPath(WP_NUM_WEAPONS) && !NITMOD_WeaponPath(INT_MAX) );
    CHECK( !strcmp(NITMOD_WeaponPath(WP_MORTAR_SET)->filename, "mortar_set.weap") );
    CHECK( !strcmp(NITMOD_WeaponPath(WP_CARBINE)->filename, "m1_garand.weap") );
    CHECK( !strcmp(NITMOD_WeaponPath(WP_GARAND_SCOPE)->filename,
                   NITMOD_WeaponPath(WP_GARAND)->filename) );
    return 0;
}
