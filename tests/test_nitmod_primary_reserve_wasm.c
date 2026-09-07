#define main poison_spawn_fixture_main
#include "test_nitmod_poison_spawn_wasm.c"
#undef main
int main(void) {
    static gclient_t client;
    static const weapon_t rows[]={WP_MP40,WP_THOMPSON,WP_STEN};
    static const int reserves[]={0,7,53};
    ammotable_t saved[3];
    int cls,team,mask,numeric,dual,custom,secondary,i,count=0;
    for(i=0;i<3;++i) saved[i]=*GetAmmoTableData(rows[i]);
    for(cls=0;cls<2;++cls)
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team)
    for(mask=0;mask<64;++mask)
    for(numeric=0;numeric<2;++numeric)
    for(dual=0;dual<2;++dual)
    for(custom=0;custom<3;++custom)
    for(secondary=0;secondary<3;++secondary) {
        weapon_t primary=cls ? WP_STEN : team==TEAM_AXIS ? WP_MP40 : WP_THOMPSON;
        int expected=reserves[custom]+((mask&2) ? 11 : 0);
        memset(&client,0,sizeof(client));
        client.sess.playerType=cls ? PC_COVERTOPS : PC_SOLDIER;
        client.sess.sessionTeam=team;
        client.sess.playerWeapon=primary;
        client.sess.playerWeapon2=secondary==0 ? WP_NONE : secondary==1 ? primary :
            team==TEAM_AXIS ? WP_AKIMBO_LUGER : WP_AKIMBO_COLT;
        client.sess.nitmodSkillMasks[SK_LIGHT_WEAPONS]=mask;
        client.sess.nitmodSkillMasks[SK_HEAVY_WEAPONS]=16;
        client.sess.skill[SK_LIGHT_WEAPONS]=numeric ? 5 : 0;
        client.sess.skill[SK_HEAVY_WEAPONS]=numeric ? 5 : 0;
        g_dualSMG.integer=dual;
        for(i=0;i<3;++i) {
            GetAmmoTableData(rows[i])->defaultStartingAmmo=reserves[custom];
            GetAmmoTableData(rows[i])->defaultStartingClip=9;
            GetAmmoTableData(rows[i])->maxclip=11;
        }
        SetWolfSpawnWeapons(&client);
        assert(client.ps.weapon==primary);
        assert(COM_BitCheck(client.ps.weapons,primary));
        assert(client.ps.ammo[BG_FindAmmoForWeapon(primary)]==expected);
        assert(client.ps.ammoclip[BG_FindClipForWeapon(primary)]==9);
        if(dual && !cls) {
            weapon_t other=primary==WP_MP40 ? WP_THOMPSON : WP_MP40;
            assert(COM_BitCheck(client.ps.weapons,other));
            assert(client.ps.ammo[BG_FindAmmoForWeapon(other)]==expected);
        }
        ++count;
    }
    for(i=0;i<3;++i) *GetAmmoTableData(rows[i])=saved[i];
    printf("Primary SMG reserve: %d actual spawn cases passed\n",count);
    return 0;
}
