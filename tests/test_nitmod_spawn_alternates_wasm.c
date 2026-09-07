#define main poison_spawn_fixture_main
#include "test_nitmod_poison_spawn_wasm.c"
#undef main
int main(void) {
    static gclient_t client;
    static const weapon_t bases[]={WP_MOBILE_MG42,WP_MORTAR,WP_FG42,WP_K43,WP_GARAND,WP_KAR98,WP_CARBINE};
    static const weapon_t alts[]={WP_MOBILE_MG42_SET,WP_MORTAR_SET,WP_FG42SCOPE,WP_K43_SCOPE,WP_GARAND_SCOPE,WP_GPG40,WP_M7};
    int pair,blocked,reward,custom,repeat,count=0;
    for(pair=0;pair<7;++pair) {
        weapon_t base=bases[pair],alt=alts[pair];
        ammotable_t baseSaved=*GetAmmoTableData(base),altSaved=*GetAmmoTableData(alt);
        for(reward=0;reward<2;++reward)
        for(custom=0;custom<2;++custom) {
            if(custom) {
                GetAmmoTableData(base)->defaultStartingAmmo=7;
                GetAmmoTableData(base)->defaultStartingClip=9;
                GetAmmoTableData(alt)->defaultStartingAmmo=13;
                GetAmmoTableData(alt)->defaultStartingClip=15;
            } else {
                *GetAmmoTableData(base)=baseSaved; *GetAmmoTableData(alt)=altSaved;
            }
            for(blocked=0;blocked<2;++blocked)
            for(repeat=0;repeat<2;++repeat) {
                int expectedBase=GetAmmoTableData(base)->defaultStartingAmmo;
                if(reward && pair>=2) expectedBase+=GetAmmoTableData(base)->maxclip;
                memset(&client,0,sizeof(client));
                client.sess.playerType=pair<2 ? PC_SOLDIER : pair<5 ? PC_COVERTOPS : PC_ENGINEER;
                client.sess.sessionTeam=base==WP_GARAND || base==WP_CARBINE ? TEAM_ALLIES : TEAM_AXIS;
                client.sess.playerWeapon=base;
                client.sess.nitmodSkillMasks[SK_LIGHT_WEAPONS]=reward ? 2 : 0;
                client.sess.rifleGrenadeStatus=1;
                deniedWeapon=blocked ? alt : WP_NONE;
                SetWolfSpawnWeapons(&client);
                if(repeat) SetWolfSpawnWeapons(&client);
                assert(client.ps.weapon==base && COM_BitCheck(client.ps.weapons,base));
                assert(!!COM_BitCheck(client.ps.weapons,alt)==!blocked);
                assert(client.sess.rifleGrenadeStatus==(pair>=5 && !blocked));
                if(blocked) {
                    assert(client.ps.ammo[BG_FindAmmoForWeapon(base)]==expectedBase);
                    assert(client.ps.ammoclip[BG_FindClipForWeapon(base)]==GetAmmoTableData(base)->defaultStartingClip);
                } else {
                    assert(client.ps.ammoclip[BG_FindClipForWeapon(alt)]==GetAmmoTableData(alt)->defaultStartingClip);
                }
                ++count;
            }
        }
        *GetAmmoTableData(base)=baseSaved; *GetAmmoTableData(alt)=altSaved;
    }
    printf("Alternate spawn gates: %d actual spawn cases passed\n",count);
    return 0;
}
