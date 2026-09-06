/* Compile the actual static spawn routine, not a copied implementation. */
#include "../src_2.60/game/g_client.c"
#include <assert.h>
#include <stdio.h>
vmCvar_t ui_gameType;
static int testWar;
int G_NITMOD_ConfiguredWarMode(void) { return testWar; }
int main(void) {
    static gclient_t client;
    int w, cls, mask, level, war, count = 0;
    for(w = 0; w < WP_NUM_WEAPONS; ++w)
    for(cls = 0; cls < 5; ++cls)
    for(mask = 0; mask < 8; ++mask)
    for(level = 0; level < 2; ++level)
    for(war = 0; war < 6; ++war) {
        int s, ammo = 0, clip = 0;
        memset(&client, 0, sizeof(client));
        client.sess.playerType = cls;
        for(s = 0; s < SK_NUM_SKILLS; ++s) {
            client.sess.skill[s] = level ? 5 : 0;
            client.sess.nitmodSkillMasks[s] = mask;
        }
        testWar = war;
        if(war == 0 || war == 5) switch(w) {
        case WP_LUGER: case WP_COLT: case WP_STEN: case WP_SILENCER:
        case WP_CARBINE: case WP_KAR98: case WP_SILENCED_COLT:
        case WP_MP40: case WP_THOMPSON: case WP_GARAND: case WP_K43:
        case WP_FG42: case WP_GARAND_SCOPE: case WP_K43_SCOPE: case WP_FG42SCOPE:
            if(mask & 2) ammo = GetAmmoTableData(w)->maxclip;
            break;
        case WP_M7: case WP_GPG40: if(mask & 2) ammo = 4; break;
        case WP_GRENADE_LAUNCHER: case WP_GRENADE_PINEAPPLE:
            if(mask & 2) clip = cls == PC_ENGINEER ? 4 : cls == PC_MEDIC ? 1 : 0;
            break;
        case WP_MEDIC_SYRINGE: case WP_MEDIC_ADRENALINE:
            if(mask & 4) clip = 2;
            break;
        }
        AddExtraSpawnAmmo(&client, w);
        assert(client.ps.ammo[BG_FindAmmoForWeapon(w)] == ammo);
        assert(client.ps.ammoclip[BG_FindAmmoForWeapon(w)] == clip);
        ++count;
    }
    /* Scoped weapons accept Light Weapons alone, independent of numeric level. */
    memset(&client, 0, sizeof(client));
    testWar = 0;
    client.sess.nitmodSkillMasks[SK_LIGHT_WEAPONS] = 2;
    AddExtraSpawnAmmo(&client, WP_K43_SCOPE);
    assert(client.ps.ammo[BG_FindAmmoForWeapon(WP_K43_SCOPE)] == GetAmmoTableData(WP_K43_SCOPE)->maxclip);
    printf("Spawn reward WASM: %d weapon/class/mask/level/war cases passed\n", count);
    return 0;
}
