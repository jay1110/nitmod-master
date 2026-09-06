#include "../src_2.60/game/g_client.c"
#include <assert.h>
#include <stdio.h>
vmCvar_t ui_gameType;
int G_NITMOD_ConfiguredWarMode(void) { return 0; }
int Bot_WeaponGameToBot(int weapon) { return weapon; }
void Bot_Event_AddWeapon(int client, int weapon) { (void)client; (void)weapon; }
int main(void) {
    static gclient_t client;
    int team, cls, level, request, count = 0;
    for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team)
    for(cls = 0; cls < 5; ++cls)
    for(level = 0; level <= 5; ++level)
    for(request = 0; request < WP_NUM_WEAPONS; ++request) {
        weapon_t result = NITMOD_CorrectSecondaryWeapon(request,team,level,level,cls,0,0);
        memset(&client, 0, sizeof(client));
        client.sess.sessionTeam = team;
        client.sess.playerType = cls;
        client.sess.playerWeapon2 = request;
        client.sess.skill[SK_LIGHT_WEAPONS] = level;
        client.sess.skill[SK_HEAVY_WEAPONS] = level;
        client.ps.weapon = WP_KNIFE;
        if(result == WP_NONE) result = team == TEAM_ALLIES ? WP_COLT : WP_LUGER;
        assert(G_NITMOD_GrantSelectedSecondary(&client,0,0));
        assert(client.ps.weapon == WP_KNIFE);
        if(result != WP_NONE) {
            assert(COM_BitCheck(client.ps.weapons,result));
            assert(client.ps.ammoclip[BG_FindClipForWeapon(result)] == GetAmmoTableData(result)->defaultStartingClip);
            if(BG_IsAkimboWeapon(result))
                assert(client.ps.ammoclip[BG_FindClipForWeapon(BG_AkimboSidearm(result))] == GetAmmoTableData(result)->defaultStartingClip);
        } else assert(!client.ps.weapons[0] && !client.ps.weapons[1]);
        ++count;
    }
    memset(&client, 0, sizeof(client));
    client.sess.sessionTeam = TEAM_AXIS;
    client.sess.playerType = PC_SOLDIER;
    client.sess.playerWeapon2 = WP_MP40;
    client.sess.skill[SK_HEAVY_WEAPONS] = 4;
    client.ps.weapon = WP_MP40;
    client.ps.ammo[BG_FindAmmoForWeapon(WP_MP40)] = 123;
    assert(G_NITMOD_GrantSelectedSecondary(&client,0,0));
    assert(client.ps.ammo[BG_FindAmmoForWeapon(WP_MP40)] == 123);
    printf("Secondary grant: %d actual adapter cases passed\n",count);
    return 0;
}
