#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_ammo.h"

extern int CG_WeaponIndex(int weapon, int *bank, int *cycle);

/* Original warning thresholds: five reserve rounds clear the warning;
 * empty reserve is state 2, a low nonzero reserve state 1. Do not include
 * magazines or deduplicate aliases: the original counts each owned weapon.
 * Unlike its masked x86 shift, inspect both native ownership words. */
void CG_CheckAmmo(void) {
    int weapon, reserve, total=0;
    qboolean owned=qfalse;
    if(!cg.snap) return;
    for(weapon=0;weapon<WP_NUM_WEAPONS;++weapon) {
        if(!((unsigned int)cg.snap->ps.weapons[weapon/32] & (1u<<(weapon%32)))) continue;
        owned=qtrue;
        reserve=cg.snap->ps.ammo[BG_FindAmmoForWeapon(weapon)];
        if(reserve<=0) continue;
        /* Saturate before adding: large server values cannot overflow. */
        if(reserve>=5-total) { cg.lowAmmoWarning=0; return; }
        total+=reserve;
    }
    if(!owned) return;
    if(!cg.lowAmmoWarning && cgs.media.noAmmoSound>0)
        trap_S_StartLocalSound(cgs.media.noAmmoSound,CHAN_LOCAL_SOUND);
    cg.lowAmmoWarning=total ? 1 : 2;
}

/* Original zero entries end the decision with WP_NONE, not just the scan.
 * Verified at ELF 0xc9396..0xc93af and 0xc9311..0xc932a. */
static qboolean ScanBank(int bank, int excluded, int *choice) {
    int i;
    for(i = 0; i < MAX_WEAPS_IN_BANK_MP; ++i) {
        int weapon = weapBanksMultiPlayer[bank][i];
        if(weapon == excluded && weapon != WP_NONE) continue;
        if(weapon == WP_NONE || CG_WeaponSelectable(weapon)) {
            *choice = weapon;
            return qtrue;
        }
    }
    return qfalse;
}

/* Original CG_OutOfAmmoChange (ELF 0xc91f0), using normalized ET weapon IDs.
 * Keep selection decisions separate from sound/zoom/weapon-history effects. */
nitmodAmmoAction_t CG_NitmodAmmoSelection(qboolean force, int *choice) {
    int current = cg.weaponSelect, bank = 0, cycle = 0, i;
    if(!choice || !NITMOD_UsesOriginalProtocol()) return NITMOD_AMMO_NATIVE;
    *choice = current;
    if(current == WP_PLIERS || (current == WP_SATCHEL_DET && cg.predictedPlayerState.ammo[WP_SATCHEL_DET]))
        return NITMOD_AMMO_KEEP;
    if(force) {
        if(current == WP_SMOKE_BOMB) {
            if(CG_WeaponSelectable(WP_LUGER)) { *choice = WP_LUGER; return NITMOD_AMMO_FINISH; }
            if(CG_WeaponSelectable(WP_COLT)) { *choice = WP_COLT; return NITMOD_AMMO_FINISH; }
        } else if(current == WP_DYNAMITE || current == WP_LANDMINE ||
                  current == WP_TRIPMINE || current == WP_POISON_MINE) {
            if(CG_WeaponSelectable(WP_PLIERS)) { *choice = WP_PLIERS; return NITMOD_AMMO_FINISH; }
        } else if(current == WP_SATCHEL && CG_WeaponSelectable(WP_SATCHEL_DET)) {
            *choice = WP_SATCHEL_DET; return NITMOD_AMMO_SELECT;
        } else if(current == WP_MORTAR_SET) {
            *choice = WP_MORTAR; return NITMOD_AMMO_SELECT;
        } else if(current == WP_MOBILE_MG42_SET) {
            *choice = WP_MOBILE_MG42; return NITMOD_AMMO_SELECT;
        }
        if(current == WP_PANZERFAUST || current == WP_SATCHEL_DET) {
            if(ScanBank(3, WP_PANZERFAUST, choice) || ScanBank(2, WP_NONE, choice) || ScanBank(4, WP_NONE, choice))
                return NITMOD_AMMO_FINISH;
        }
        /* Original IDs 36..38 only: rifle grenades and silenced Colt.
         * There is no ET-style opposite-team equivalent preference here. */
        if(current == WP_GPG40 || current == WP_M7 || current == WP_SILENCED_COLT) {
            current = weapAlts[current] ? weapAlts[current] : current;
            *choice = current;
            if(CG_WeaponSelectable(current)) return NITMOD_AMMO_FINISH;
        }
    }
    if(ScanBank(3, WP_NONE, choice) || ScanBank(2, WP_NONE, choice)) return NITMOD_AMMO_FINISH;
    CG_WeaponIndex(current, &bank, &cycle);
    if(bank < 0 || bank >= MAX_WEAP_BANKS_MP || cycle < 0 || cycle >= MAX_WEAPS_IN_BANK_MP) bank = cycle = 0;
    for(i = cycle + 1; i <= MAX_WEAPS_IN_BANK_MP; ++i) {
        int weapon = weapBanksMultiPlayer[bank][i % MAX_WEAPS_IN_BANK_MP];
        if(!weapon) weapon = weapBanksMultiPlayer[bank][0];
        if(!weapon || CG_WeaponSelectable(weapon)) { *choice = weapon; return NITMOD_AMMO_FINISH; }
    }
    return NITMOD_AMMO_NEXT;
}
