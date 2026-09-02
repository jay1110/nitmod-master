#include "g_local.h"
#include "g_nitmod_restrictions.h"
level_locals_t level;
gentity_t g_entities[MAX_GENTITIES];
static gclient_t clients[MAX_CLIENTS], expected;
static nitmodWeaponPolicyResult_t result;
static int checks, publications, bad, expectedPrimary;
nitmodWeaponPolicyResult_t G_NITMOD_CheckWeaponAndNotify( gentity_t *entity, int weapon, int pickup, int silent ) {
    checks++;
    if( entity != &g_entities[3] || weapon != WP_PANZERFAUST || pickup || silent ) bad = 1;
    return result;
}
void ClientUserinfoChanged( int slot ) {
    publications++;
    if( slot != 3 || clients[3].sess.latchPlayerWeapon != expectedPrimary ||
        clients[3].sess.latchPlayerWeapon2 != WP_LUGER ) bad = 1;
}
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
int main( void ) {
    int allow, update, repeat;
    level.clients = clients; g_entities[3].client = &clients[3];
    for( allow = 0; allow < 2; allow++ ) for( update = 0; update < 2; update++ ) {
        memset(&clients[3], 0x5a, sizeof(clients[3]));
        clients[3].sess.latchPlayerWeapon = WP_MP40;
        clients[3].sess.latchPlayerWeapon2 = WP_COLT;
        expected = clients[3];
        expectedPrimary = allow ? WP_PANZERFAUST : WP_NONE;
        expected.sess.latchPlayerWeapon = expectedPrimary;
        expected.sess.latchPlayerWeapon2 = WP_LUGER;
        result.decision = allow ? NITMOD_WEAPON_ALLOW : NITMOD_WEAPON_DENY;
        result.limit = allow ? NITMOD_LIMIT_NONE : NITMOD_LIMIT_FIXED;
        publications = checks = 0;
        for( repeat = 0; repeat < 2; repeat++ ) {
            CHECK( G_NITMOD_SetClientWeapons(&g_entities[3], WP_PANZERFAUST, WP_LUGER, update) == !repeat );
            CHECK( !memcmp(&clients[3], &expected, sizeof(expected)) );
            CHECK( publications == update && checks == repeat + 1 && !bad );
        }
    }
    expected = clients[3]; publications = checks = 0;
    result.limit = NITMOD_LIMIT_INVALID;
    CHECK( G_NITMOD_SetClientWeapons(&g_entities[3], WP_PANZERFAUST, WP_LUGER, 1) == -1 );
    CHECK( !memcmp(&clients[3], &expected, sizeof(expected)) && !publications );
    result.limit = NITMOD_LIMIT_NONE; result.decision = NITMOD_WEAPON_DEFER;
    CHECK( G_NITMOD_SetClientWeapons(&g_entities[3], WP_PANZERFAUST, WP_LUGER, 1) == -1 );
    checks = 0;
    CHECK( G_NITMOD_SetClientWeapons(NULL, WP_PANZERFAUST, WP_LUGER, 1) == -1 );
    CHECK( G_NITMOD_SetClientWeapons(&g_entities[3], WP_PANZERFAUST, WP_NUM_WEAPONS, 1) == -1 );
    CHECK( G_NITMOD_SetClientWeapons(&g_entities[3], -1, WP_LUGER, 1) == -1 );
    CHECK( !checks && !publications && !memcmp(&clients[3], &expected, sizeof(expected)) );
    return 0;
}
