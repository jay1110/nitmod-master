#define main poison_spawn_fixture_main
#include "test_nitmod_poison_spawn_wasm.c"
#undef main
/* Independent recovered class-list expectations, not the product lookup. */
static int expectedPrimary(int team,int cls,int request,int blocked) {
    int smg=team==TEAM_AXIS ? WP_MP40 : WP_THOMPSON;
    int rifle=team==TEAM_AXIS ? WP_KAR98 : WP_CARBINE;
    int covert=team==TEAM_AXIS ? WP_K43 : WP_GARAND;
    int fallback=cls==PC_COVERTOPS ? WP_STEN : smg;
    int member=0;
    switch(cls) {
    case PC_SOLDIER: member=request==smg || request==WP_MOBILE_MG42 || request==WP_FLAMETHROWER || request==WP_PANZERFAUST || request==WP_MORTAR; break;
    case PC_MEDIC: case PC_FIELDOPS: member=request==WP_MP40 || request==WP_THOMPSON || request==WP_STEN; break;
    case PC_ENGINEER: member=request==WP_MP40 || request==WP_THOMPSON || request==rifle; break;
    case PC_COVERTOPS: member=request==WP_STEN || request==WP_FG42 || request==covert; break;
    }
    return member && !blocked ? request : fallback;
}
int main(void) {
    static gclient_t client;
    int team,cls,request,blocked,reward,mode,count=0;
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team)
    for(cls=PC_SOLDIER;cls<=PC_COVERTOPS;++cls)
    for(request=-1;request<=WP_NUM_WEAPONS;++request)
    for(blocked=0;blocked<2;++blocked)
    for(reward=0;reward<2;++reward)
    for(mode=0;mode<2;++mode) {
        int expected=mode ? WP_KNIFE : expectedPrimary(team,cls,request,blocked);
        memset(&client,0,sizeof(client));
        client.sess.playerType=cls; client.sess.sessionTeam=team;
        client.sess.playerWeapon=request;
        client.sess.latchPlayerWeapon=WP_KNIFE;
        client.sess.nitmodSkillMasks[SK_LIGHT_WEAPONS]=reward ? 2 : 0;
        deniedWeapon=blocked ? request : -99;
        war=mode ? 4 : 0;
        SetWolfSpawnWeapons(&client);
        assert(client.ps.weapon==expected);
        assert(COM_BitCheck(client.ps.weapons,expected));
        assert(client.sess.playerWeapon==request && client.sess.latchPlayerWeapon==WP_KNIFE);
        if(!mode && (cls==PC_MEDIC || cls==PC_FIELDOPS)) {
            int reserve=cls==PC_MEDIC ? 0 : GetAmmoTableData(expected)->defaultStartingAmmo;
            if(reward) reserve+=GetAmmoTableData(expected)->maxclip;
            assert(client.ps.ammo[BG_FindAmmoForWeapon(expected)]==reserve);
            assert(client.ps.ammoclip[BG_FindClipForWeapon(expected)]==GetAmmoTableData(expected)->defaultStartingClip);
        }
        ++count;
    }
    printf("Primary selection: %d actual spawn cases passed\n",count);
    war=0; deniedWeapon=-99; medicOptions=4;
    for(team=TEAM_AXIS;team<=TEAM_ALLIES;++team)
    for(request=0;request<3;++request)
    for(blocked=0;blocked<2;++blocked) {
        static const weapon_t choices[]={WP_MP40,WP_THOMPSON,WP_STEN};
        weapon_t primary=choices[request];
        weapon_t extra=primary==WP_MP40 ? WP_THOMPSON : primary==WP_THOMPSON ? WP_MP40 :
            team==TEAM_AXIS ? WP_MP40 : WP_THOMPSON;
        int i;
        memset(&client,0,sizeof(client));
        client.sess.playerType=PC_MEDIC; client.sess.sessionTeam=team;
        client.sess.playerWeapon=primary; g_dualSMG.integer=blocked;
        SetWolfSpawnWeapons(&client);
        assert(client.ps.weapon==(team==TEAM_AXIS ? WP_LUGER : WP_COLT));
        for(i=0;i<3;++i) assert(!!COM_BitCheck(client.ps.weapons,choices[i])==(blocked && choices[i]==extra));
    }
    puts("Medic primary suppression: 12 dual-SMG selection cases passed");
    return 0;
}
