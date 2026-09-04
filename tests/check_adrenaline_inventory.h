extern pmove_t *pm;
extern int PM_WeaponAmmoAvailable(int);
extern void PM_WeaponUseAmmo(int, int);
static int CheckAdrenalineInventory(void) {
    static playerState_t state;
    static cg_t saved;
    pmove_t move, *savedPm = pm;
    int mode, count, errors = 0;
    saved = cg;
    memset(&move, 0, sizeof(move)); move.ps = &state; pm = &move;
    if(BG_FindAmmoForWeapon(WP_MEDIC_ADRENALINE) != WP_MEDIC_ADRENALINE ||
       BG_FindClipForWeapon(WP_MEDIC_ADRENALINE) != WP_MEDIC_ADRENALINE) ++errors;
    for(mode = 0; mode < 2; ++mode) for(count = 0; count < 11; ++count) {
        memset(&state, 0, sizeof(state));
        move.noWeapClips = mode;
        state.ammo[WP_MEDIC_ADRENALINE] = state.ammoclip[WP_MEDIC_ADRENALINE] = count;
        state.ammo[WP_MEDIC_SYRINGE] = state.ammoclip[WP_MEDIC_SYRINGE] = 19;
        if(PM_WeaponAmmoAvailable(WP_MEDIC_ADRENALINE) != count) ++errors;
        if(count) PM_WeaponUseAmmo(WP_MEDIC_ADRENALINE, 1);
        if(PM_WeaponAmmoAvailable(WP_MEDIC_ADRENALINE) != (count ? count-1 : 0) ||
           state.ammo[WP_MEDIC_SYRINGE] != 19 || state.ammoclip[WP_MEDIC_SYRINGE] != 19) ++errors;
    }
    memset(&cg.predictedPlayerState, 0, sizeof(cg.predictedPlayerState));
    COM_BitSet(cg.predictedPlayerState.weapons, WP_MEDIC_ADRENALINE);
    cg.predictedPlayerState.ammoclip[WP_MEDIC_ADRENALINE] = 1;
    if(!CG_WeaponSelectable(WP_MEDIC_ADRENALINE)) ++errors;
    cg.predictedPlayerState.ammoclip[WP_MEDIC_ADRENALINE] = 0;
    cg.predictedPlayerState.ammoclip[WP_MEDIC_SYRINGE] = 19;
    if(CG_WeaponSelectable(WP_MEDIC_ADRENALINE)) ++errors;
    pm = savedPm; cg = saved; return errors;
}
