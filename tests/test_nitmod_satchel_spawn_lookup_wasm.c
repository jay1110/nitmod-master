#define main poison_spawn_fixture_main
#include "test_nitmod_poison_spawn_wasm.c"
#undef main
int main(void) {
    static gclient_t client;
    int team, cls, dm, allow, noise, knife, count=0;
    for(team=TEAM_AXIS; team<=TEAM_ALLIES; ++team)
    for(cls=PC_SOLDIER; cls<=PC_COVERTOPS; ++cls)
    for(dm=0; dm<2; ++dm)
    for(allow=0; allow<2; ++allow)
    for(noise=0; noise<2; ++noise)
    for(knife=0; knife<2; ++knife)
    for(war=0; war<=5; ++war)
    for(satchelPresent=0; satchelPresent<2; ++satchelPresent) {
        int granted=cls==PC_COVERTOPS && !knife && (war==0 || war==5) && (!dm || allow);
        memset(&client,0,sizeof(client));
        client.sess.sessionTeam=team;
        client.sess.playerType=cls;
        g_gametype.integer=dm ? GT_WOLF_DM : GT_WOLF;
        g_DMOptions.integer=(allow ? 0x1000u : 0) | (noise ? 0xffffefffu : 0);
        g_knifeonly.integer=knife;
        satchelLookups=0;
        SetWolfSpawnWeapons(&client);
        assert(satchelLookups==granted);
        assert(!!COM_BitCheck(client.ps.weapons,WP_SATCHEL)==granted);
        assert(!!COM_BitCheck(client.ps.weapons,WP_SATCHEL_DET)==granted);
        if(granted) {
            assert(client.ps.ammoclip[BG_FindClipForWeapon(WP_SATCHEL)]==!satchelPresent);
            assert(client.ps.ammoclip[BG_FindClipForWeapon(WP_SATCHEL_DET)]==satchelPresent);
            assert(client.ps.ammo[BG_FindAmmoForWeapon(WP_SATCHEL)]==0);
            assert(client.ps.ammo[BG_FindAmmoForWeapon(WP_SATCHEL_DET)]==0);
        }
        ++count;
    }
    printf("Satchel spawn lookup: %d gate/inventory cases passed\n",count);
    return 0;
}
