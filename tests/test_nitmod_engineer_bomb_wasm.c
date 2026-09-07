#define main poison_spawn_fixture_main
#include "test_nitmod_poison_spawn_wasm.c"
#undef main
int main(void) {
    static gclient_t client, baseline;
    ammotable_t saved = *GetAmmoTableData(WP_BOMB);
    int cls, team, dm, mask, numeric, enabled, dmEnabled, knife, custom, count=0;
    for(cls=0;cls<5;++cls)
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team)
    for(dm=0;dm<2;++dm)
    for(mask=0;mask<64;++mask)
    for(numeric=0;numeric<2;++numeric)
    for(enabled=0;enabled<2;++enabled)
    for(dmEnabled=0;dmEnabled<2;++dmEnabled)
    for(knife=0;knife<2;++knife)
    for(custom=0;custom<2;++custom)
    for(war=0;war<=5;++war) {
        int expected=cls==PC_ENGINEER && (mask&32) && enabled &&
            (!dm || dmEnabled) && !knife && (war==0 || war==5);
        memset(&client,0,sizeof(client));
        client.sess.playerType=cls; client.sess.sessionTeam=team;
        client.sess.nitmodSkillMasks[SK_EXPLOSIVES_AND_CONSTRUCTION]=mask;
        client.sess.skill[SK_EXPLOSIVES_AND_CONSTRUCTION]=numeric ? 5 : 0;
        baseline=client;
        g_gametype.integer=dm ? GT_WOLF_DM : GT_WOLF;
        g_DMOptions.integer=dmEnabled ? 0x2000 : 0;
        g_knifeonly.integer=knife;
        GetAmmoTableData(WP_BOMB)->defaultStartingAmmo=custom ? 7 : saved.defaultStartingAmmo;
        GetAmmoTableData(WP_BOMB)->defaultStartingClip=custom ? 9 : saved.defaultStartingClip;
        weaponOptions=0;
        SetWolfSpawnWeapons(&baseline);
        weaponOptions=enabled ? 4 : 0;
        SetWolfSpawnWeapons(&client);
        assert(!!COM_BitCheck(client.ps.weapons,WP_BOMB)==!!expected);
        if(expected) {
            COM_BitSet(baseline.ps.weapons,WP_BOMB);
            baseline.ps.ammo[BG_FindAmmoForWeapon(WP_BOMB)]=GetAmmoTableData(WP_BOMB)->defaultStartingAmmo;
            baseline.ps.ammoclip[BG_FindClipForWeapon(WP_BOMB)]=GetAmmoTableData(WP_BOMB)->defaultStartingClip;
        }
        assert(!memcmp(&client,&baseline,sizeof(client)));
        ++count;
    }
    *GetAmmoTableData(WP_BOMB)=saved;
    printf("Engineer bomb: %d actual spawn cases passed\n",count);
    return 0;
}
