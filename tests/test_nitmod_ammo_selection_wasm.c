#include "cg_local.h"
#include "cg_nitmod_ammo.h"
#include <assert.h>
#include <stdio.h>
cg_t cg;
int weapBanksMultiPlayer[MAX_WEAP_BANKS_MP][MAX_WEAPS_IN_BANK_MP];
int weapAlts[WP_NUM_WEAPONS];
static int original, nitmod;
static int available[WP_NUM_WEAPONS];
qboolean NITMOD_UsesOriginalProtocol(void) { return original; }
qboolean NITMOD_UsesNitmodHud(void) { return nitmod; }
qboolean CG_WeaponSelectable(int weapon) { return available[weapon]; }
int CG_WeaponIndex(int weapon, int *bank, int *cycle) { (void)weapon; *bank = *cycle = 0; return 0; }
int main(void) {
    int protocol, weapon, mask, force, choice, cases = 0;
    const int grenades[] = {WP_SMOKE_BOMB, WP_POISON_BOMB, WP_BOMB};
    for(protocol = 0; protocol < 3; ++protocol)
    for(weapon = 0; weapon < 3; ++weapon)
    for(mask = 0; mask < 4; ++mask)
    for(force = 0; force < 2; ++force) {
        nitmodAmmoAction_t action;
        original = protocol == 1; nitmod = protocol == 2;
        available[WP_LUGER] = mask & 1;
        available[WP_COLT] = mask & 2;
        cg.weaponSelect = grenades[weapon];
        choice = -1;
        action = CG_NitmodAmmoSelection(force, &choice);
        if(!protocol) assert(action == NITMOD_AMMO_NATIVE);
        else {
            int expected = force && weapon < 2 && mask ? (mask & 1 ? WP_LUGER : WP_COLT) : WP_NONE;
            assert(action == NITMOD_AMMO_FINISH && choice == expected);
        }
        ++cases;
    }
    puts("Ammo selection: 72 protocol/grenade/pistol/force cases passed");
    {
        const int sources[] = {WP_DYNAMITE, WP_LANDMINE, WP_TRIPMINE, WP_POISON_MINE,
            WP_SATCHEL, WP_MORTAR_SET, WP_MOBILE_MG42_SET, WP_PLIERS, WP_SATCHEL_DET};
        int p, s, ready, forced, reserve, checked = 0;
        for(p = 1; p <= 2; ++p)
        for(s = 0; s < 9; ++s)
        for(ready = 0; ready < 2; ++ready)
        for(forced = 0; forced < 2; ++forced)
        for(reserve = 0; reserve < 2; ++reserve) {
            int expected = WP_NONE;
            nitmodAmmoAction_t expectedAction = NITMOD_AMMO_FINISH;
            memset(available, 0, sizeof(available));
            original = p == 1; nitmod = p == 2;
            cg.weaponSelect = sources[s];
            cg.predictedPlayerState.ammo[WP_SATCHEL_DET] = reserve;
            available[WP_PLIERS] = available[WP_SATCHEL_DET] = ready;
            if(s == 7 || (s == 8 && reserve)) {
                expected = sources[s]; expectedAction = NITMOD_AMMO_KEEP;
            } else if(forced) {
                if(s < 4 && ready) expected = WP_PLIERS;
                else if(s == 4 && ready) { expected = WP_SATCHEL_DET; expectedAction = NITMOD_AMMO_SELECT; }
                else if(s == 5) { expected = WP_MORTAR; expectedAction = NITMOD_AMMO_SELECT; }
                else if(s == 6) { expected = WP_MOBILE_MG42; expectedAction = NITMOD_AMMO_SELECT; }
            }
            assert(CG_NitmodAmmoSelection(forced, &choice) == expectedAction);
            assert(choice == expected);
            ++checked;
        }
        printf("Ammo special cases: %d protocol/force/availability/reserve cases passed\n", checked);
    }
    return 0;
}
