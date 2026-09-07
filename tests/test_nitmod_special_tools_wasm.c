#define main poison_spawn_fixture_main
#include "test_nitmod_poison_spawn_wasm.c"
#undef main
int main(void) {
    static gclient_t client, baseline;
    static const weapon_t weapons[] = { WP_TRIPMINE, WP_POISON_MINE, WP_POISON_BOMB };
    static const unsigned normalBits[] = { 0x8000, 0x4000, 0x2000 };
    static const unsigned dmBits[] = { 0x800, 0x200, 0x400 };
    ammotable_t saved[3];
    int cls, team, dm, normal, death, knife, custom, i, count = 0;
    for(i=0;i<3;++i) saved[i] = *GetAmmoTableData(weapons[i]);
    for(cls=0;cls<5;++cls)
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team)
    for(dm=0;dm<2;++dm)
    for(normal=0;normal<8;++normal)
    for(death=0;death<8;++death)
    for(knife=0;knife<2;++knife)
    for(custom=0;custom<2;++custom)
    for(war=0;war<=5;++war) {
        int opts=0, dmopts=0;
        memset(&client,0,sizeof(client));
        client.sess.playerType=cls; client.sess.sessionTeam=team;
        baseline=client;
        g_gametype.integer=dm ? GT_WOLF_DM : GT_WOLF;
        g_knifeonly.integer=knife;
        for(i=0;i<3;++i) {
            if(normal & (1<<i)) opts |= normalBits[i];
            if(death & (1<<i)) dmopts |= dmBits[i];
            GetAmmoTableData(weapons[i])->defaultStartingAmmo=custom ? 7 : saved[i].defaultStartingAmmo;
            GetAmmoTableData(weapons[i])->defaultStartingClip=custom ? 9 : saved[i].defaultStartingClip;
        }
        /* Keep pliers' DM option side effects identical in the baseline. */
        weaponOptions=0; g_DMOptions.integer=dmopts;
        SetWolfSpawnWeapons(&baseline);
        weaponOptions=opts;
        SetWolfSpawnWeapons(&client);
        for(i=0;i<3;++i) {
            int grant=!knife && (war==0 || war==5) &&
                cls==(i==2 ? PC_COVERTOPS : PC_ENGINEER) &&
                ((dm ? death : normal) & (1<<i));
            assert(!!COM_BitCheck(client.ps.weapons,weapons[i])==!!grant);
            if(grant) {
                assert(client.ps.ammo[BG_FindAmmoForWeapon(weapons[i])]==GetAmmoTableData(weapons[i])->defaultStartingAmmo);
                assert(client.ps.ammoclip[BG_FindClipForWeapon(weapons[i])]==GetAmmoTableData(weapons[i])->defaultStartingClip);
            }
            /* Exclude only these three slots from the unrelated-state check. */
            COM_BitClear(client.ps.weapons,weapons[i]); COM_BitClear(baseline.ps.weapons,weapons[i]);
            client.ps.ammo[BG_FindAmmoForWeapon(weapons[i])]=baseline.ps.ammo[BG_FindAmmoForWeapon(weapons[i])]=0;
            client.ps.ammoclip[BG_FindClipForWeapon(weapons[i])]=baseline.ps.ammoclip[BG_FindClipForWeapon(weapons[i])]=0;
        }
        assert(!memcmp(&client,&baseline,sizeof(client)));
        ++count;
    }
    for(i=0;i<3;++i) *GetAmmoTableData(weapons[i])=saved[i];
    printf("Special class tools: %d actual spawn cases passed\n",count);
    return 0;
}
