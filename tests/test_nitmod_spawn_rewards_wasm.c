/* Compile the actual static spawn routine, not a copied implementation. */
#include "../src_2.60/game/g_client.c"
#include <assert.h>
#include <stdio.h>
vmCvar_t ui_gameType;
static int testWar;
int G_NITMOD_ConfiguredWarMode(void) { return testWar; }
int main(void) {
    static gclient_t client;
    static gclient_t expected;
    static const int wars[] = { -1, 0, 1, 2, 3, 4, 5, INT_MAX, INT_MIN };
    int w, cls, mask, level, wi, count = 0;
    for(w = 0; w < WP_NUM_WEAPONS; ++w)
    for(cls = 0; cls < 5; ++cls)
    /* Independent Light, First Aid, Engineering and Covert reward gates. */
    for(mask = 0; mask < 32; ++mask)
    for(level = 0; level < 2; ++level)
    for(wi = 0; wi < sizeof(wars)/sizeof(wars[0]); ++wi) {
        int war = wars[wi];
        int s, ammo = 0, clip = 0;
        memset(&client, 0, sizeof(client));
        client.sess.playerType = cls;
        for(s = 0; s < SK_NUM_SKILLS; ++s) {
            client.sess.skill[s] = level ? 5 : 0;
            client.sess.nitmodSkillMasks[s] = 0xffffffF9u;
        }
        client.sess.nitmodSkillMasks[SK_LIGHT_WEAPONS] |= (mask & 1) ? 2u : 0;
        client.sess.nitmodSkillMasks[SK_FIRST_AID] |= ((mask & 2) ? 2u : 0) | ((mask & 4) ? 4u : 0);
        client.sess.nitmodSkillMasks[SK_EXPLOSIVES_AND_CONSTRUCTION] |= (mask & 8) ? 2u : 0;
        client.sess.nitmodSkillMasks[SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS] |= (mask & 16) ? 2u : 0;
        for(s = 0; s < MAX_WEAPONS; ++s) {
            client.ps.ammo[s] = 100 + s;
            client.ps.ammoclip[s] = 200 + s;
        }
        expected = client;
        testWar = war;
        if(war < 1 || war > 4) switch(w) {
        case WP_LUGER: case WP_COLT: case WP_STEN: case WP_SILENCER:
        case WP_CARBINE: case WP_KAR98: case WP_SILENCED_COLT:
            if(mask & 1) ammo = GetAmmoTableData(w)->maxclip;
            break;
        case WP_MP40: case WP_THOMPSON:
            if((mask & 1) || (cls == PC_MEDIC && (mask & 2))) ammo = GetAmmoTableData(w)->maxclip;
            break;
        case WP_GARAND: case WP_K43: case WP_FG42:
        case WP_GARAND_SCOPE: case WP_K43_SCOPE: case WP_FG42SCOPE:
            if(mask & 17) ammo = GetAmmoTableData(w)->maxclip;
            break;
        case WP_M7: case WP_GPG40: if(mask & 8) ammo = 4; break;
        case WP_GRENADE_LAUNCHER: case WP_GRENADE_PINEAPPLE:
            if(cls == PC_ENGINEER && (mask & 8)) clip = 4;
            if(cls == PC_MEDIC && (mask & 2)) clip = 1;
            break;
        case WP_MEDIC_SYRINGE: case WP_MEDIC_ADRENALINE:
            if(mask & 4) clip = 2;
            break;
        }
        expected.ps.ammo[BG_FindAmmoForWeapon(w)] += ammo;
        expected.ps.ammoclip[BG_FindAmmoForWeapon(w)] += clip;
        AddExtraSpawnAmmo(&client, w);
        assert(!memcmp(&client, &expected, sizeof(client)));
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
