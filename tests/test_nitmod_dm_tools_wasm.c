/* Reuse engine boundary stubs, execute the real spawn function. */
#define main poison_spawn_fixture_main
#include "test_nitmod_poison_spawn_wasm.c"
#undef main
int main(void) {
    static gclient_t client;
    static const weapon_t tools[] = { WP_DYNAMITE, WP_PLIERS, WP_LANDMINE,
        WP_AMMO, WP_SMOKE_MARKER, WP_MEDIC_SYRINGE, WP_MEDKIT,
        WP_SMOKE_BOMB, WP_SATCHEL, WP_SATCHEL_DET };
    int team, cls, dm, bits, i, defaults, noise, count = 0;
    ammotable_t saved[sizeof(tools)/sizeof(tools[0])];
    for(i = 0; i < sizeof(tools)/sizeof(tools[0]); ++i) saved[i] = *GetAmmoTableData(tools[i]);
    for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team)
    for(cls = PC_SOLDIER; cls <= PC_COVERTOPS; ++cls)
    for(dm = 0; dm < 2; ++dm)
    for(bits = 0; bits < 16; ++bits)
    for(satchelPresent = 0; satchelPresent < 2; ++satchelPresent)
    for(defaults = 0; defaults < 2; ++defaults)
    for(noise = 0; noise < 2; ++noise)
    for(war = 0; war <= 5; ++war) {
        unsigned options = ((bits & 1) ? 0x100 : 0) | ((bits & 2) ? 0x200 : 0) |
            ((bits & 4) ? 0x800 : 0) | ((bits & 8) ? 0x1000 : 0);
        memset(&client, 0, sizeof(client));
        client.sess.sessionTeam = team;
        client.sess.playerType = cls;
        g_gametype.integer = dm ? GT_WOLF_DM : GT_WOLF;
        g_DMOptions.integer = options | (noise ? 0xffffe4ffu : 0);
        for(i = 0; i < sizeof(tools)/sizeof(tools[0]); ++i) {
            GetAmmoTableData(tools[i])->defaultStartingAmmo = defaults ? 7 : saved[i].defaultStartingAmmo;
            GetAmmoTableData(tools[i])->defaultStartingClip = defaults ? 9 : saved[i].defaultStartingClip;
        }
        SetWolfSpawnWeapons(&client);
        for(i = 0; i < sizeof(tools)/sizeof(tools[0]); ++i) {
            weapon_t w = tools[i];
            int grant = 0;
            if(war == 0 || war == 5) switch(w) {
            case WP_DYNAMITE: grant = cls == PC_ENGINEER && !dm; break;
            case WP_PLIERS: grant = cls == PC_ENGINEER && (!dm || (options & 0xb00)); break;
            case WP_LANDMINE: grant = cls == PC_ENGINEER && (!dm || (options & 0x100)); break;
            case WP_AMMO: case WP_SMOKE_MARKER: grant = cls == PC_FIELDOPS && !dm; break;
            case WP_MEDIC_SYRINGE: case WP_MEDKIT: grant = cls == PC_MEDIC && !dm; break;
            case WP_SMOKE_BOMB: grant = cls == PC_COVERTOPS && !dm; break;
            case WP_SATCHEL: case WP_SATCHEL_DET:
                grant = cls == PC_COVERTOPS && (!dm || (options & 0x1000)); break;
            default: assert(0);
            }
            assert(!!COM_BitCheck(client.ps.weapons, w) == !!grant);
            if(grant) {
                int clip = w == WP_SATCHEL_DET ? satchelPresent : w == WP_SATCHEL ? !satchelPresent :
                    w == WP_DYNAMITE || w == WP_PLIERS || w == WP_AMMO ? 1 :
                    GetAmmoTableData(w)->defaultStartingClip;
                int reserve = w == WP_DYNAMITE || w == WP_PLIERS || w == WP_AMMO ||
                    w == WP_SATCHEL || w == WP_SATCHEL_DET ? 0 : GetAmmoTableData(w)->defaultStartingAmmo;
                assert(client.ps.ammoclip[BG_FindClipForWeapon(w)] == clip);
                assert(client.ps.ammo[BG_FindAmmoForWeapon(w)] == reserve);
            }
        }
        assert(COM_BitCheck(client.ps.weapons, WP_KNIFE));
        ++count;
    }
    for(i = 0; i < sizeof(tools)/sizeof(tools[0]); ++i) *GetAmmoTableData(tools[i]) = saved[i];
    printf("Deathmatch class tools: %d actual spawn cases passed\n", count);
    return 0;
}
