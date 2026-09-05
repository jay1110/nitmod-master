#include "nitmod_weapon_reload.h"
#include <limits.h>
#include <stdint.h>

int NITMOD_AddWeaponTime32( int timer, int duration ) {
    int64_t sum = (int64_t)timer + duration;
    if( sum > INT32_MAX ) sum -= INT64_C(4294967296);
    else if( sum < INT32_MIN ) sum += INT64_C(4294967296);
    return (int)sum;
}

int NITMOD_ReloadAnimation( int weapon, int fastReloadEnabled ) {
    switch( weapon ) {
    case WP_GPG40: case WP_M7: return WEAP_RELOAD2;
    case WP_MOBILE_MG42_SET: return WEAP_RELOAD3;
    case WP_LUGER: case WP_MP40: case WP_COLT: case WP_THOMPSON:
    case WP_STEN: case WP_SILENCER: case WP_FG42: case WP_SILENCED_COLT:
        return fastReloadEnabled ? WEAP_RELOAD2 : WEAP_RELOAD1;
    default: return WEAP_RELOAD1;
    }
}

int NITMOD_ReloadBodyEventRequired( int weapon ) {
    switch( weapon ) {
    case WP_GRENADE_LAUNCHER: case WP_GRENADE_PINEAPPLE: case WP_DYNAMITE:
    case WP_SMOKE_BOMB: case WP_TRIPMINE: case WP_BOMB:
    case WP_POISON_BOMB:
        return 0;
    default: return 1;
    }
}

int NITMOD_ResetReloadWithoutReserve( playerState_t *state, int nativeAmmoSlot ) {
    nitmodWeaponInventorySlots_t slots;
    if( !state || !NITMOD_ReloadStateAllowed(state->weaponstate) ||
        !NITMOD_WeaponInventorySlots(state->weapon, &slots) || slots.ammo != nativeAmmoSlot ) return 0;
    if( state->ammo[slots.ammo] != 0 ) return 0;
    state->weaponstate = WEAPON_READY;
    return 1;
}

int NITMOD_DeploySwitch( int oldWeapon, int newWeapon, nitmodDeploySwitch_t *result ) {
    nitmodDeploySwitch_t next;
    if( !result ) return 0;
    if( oldWeapon == WP_MOBILE_MG42 && newWeapon == WP_MOBILE_MG42_SET ) {
        next.raiseTime = 1250;
        next.raiseAltAnimation = qfalse;
        next.captureDirection = qtrue;
    } else if( oldWeapon == WP_MOBILE_MG42_SET && newWeapon == WP_MOBILE_MG42 ) {
        next.raiseTime = 1722;
        next.raiseAltAnimation = qfalse;
        next.captureDirection = qfalse;
    } else if( oldWeapon == WP_MORTAR && newWeapon == WP_MORTAR_SET ) {
        next.raiseTime = 1667;
        next.raiseAltAnimation = qtrue;
        next.captureDirection = qtrue;
    } else if( oldWeapon == WP_MORTAR_SET && newWeapon == WP_MORTAR ) {
        next.raiseTime = 1000;
        next.raiseAltAnimation = qtrue;
        next.captureDirection = qfalse;
    } else return 0;
    *result = next;
    return 1;
}

int NITMOD_RifleGrenadeDrop( const playerState_t *state, int oldWeapon,
    int newWeapon, int *reloadWeapon ) {
    int attaching;
    if( !state || !reloadWeapon ) return 0;
    attaching = (oldWeapon == WP_CARBINE && newWeapon == WP_M7) ||
        (oldWeapon == WP_KAR98 && newWeapon == WP_GPG40);
    if( !attaching && !((oldWeapon == WP_M7 && newWeapon == WP_CARBINE) ||
        (oldWeapon == WP_GPG40 && newWeapon == WP_KAR98)) ) return 0;
    *reloadWeapon = attaching && !state->ammoclip[newWeapon] && state->ammo[newWeapon]
        ? newWeapon : WP_NONE;
    return 1;
}

int NITMOD_RifleGrenadeRaise( const playerState_t *state, int oldWeapon,
    int newWeapon, nitmodRifleGrenadeRaise_t *result ) {
    nitmodRifleGrenadeRaise_t next;
    nitmodWeaponInventorySlots_t slots;
    if( !state || !result ) return 0;
    if( (oldWeapon == WP_CARBINE && newWeapon == WP_M7) ||
        (oldWeapon == WP_KAR98 && newWeapon == WP_GPG40) ) {
        next.duration = 2350;
        next.animate = qtrue;
    } else if( (oldWeapon == WP_M7 && newWeapon == WP_CARBINE) ||
        (oldWeapon == WP_GPG40 && newWeapon == WP_KAR98) ) {
        if( !NITMOD_WeaponInventorySlots(oldWeapon, &slots) ) return 0;
        next.animate = state->ammoclip[slots.ammo] != 0 ? qtrue : qfalse;
        next.duration = next.animate ? 1347 : 0;
    } else return 0;
    *result = next;
    return 1;
}

int NITMOD_RifleGrenadeModeFlags( int weapon, int flags ) {
    switch( weapon ) {
        case WP_CARBINE: case WP_KAR98: return flags & ~2;
        case WP_M7: case WP_GPG40: return flags | 2;
        default: return flags;
    }
}

int NITMOD_PistolSwitch( int oldWeapon, int newWeapon, nitmodPistolSwitch_t *result ) {
    nitmodPistolSwitch_t next;
    int attaching;
    if( !result ) return 0;
    if( (oldWeapon == WP_LUGER && newWeapon == WP_SILENCER) ||
        (oldWeapon == WP_COLT && newWeapon == WP_SILENCED_COLT) ) attaching = 1;
    else if( (oldWeapon == WP_SILENCER && newWeapon == WP_LUGER) ||
        (oldWeapon == WP_SILENCED_COLT && newWeapon == WP_COLT) ) attaching = 0;
    else return 0;
    next.dropTime = attaching ? 0 : 1000;
    next.raiseTime = attaching ? 1190 : 0;
    next.dropAltAnimation = attaching ? qfalse : qtrue;
    next.raiseAltAnimation = qtrue;
    *result = next;
    return 1;
}

int NITMOD_PistolModeFlags( int weapon, int flags ) {
    switch( weapon ) {
        case WP_LUGER: case WP_COLT: return flags & ~1;
        case WP_SILENCER: case WP_SILENCED_COLT: return flags | 1;
        default: return flags;
    }
}

int NITMOD_ScopeSwitchDuration( int oldWeapon, int newWeapon, int *duration ) {
    if( !duration ) return 0;
    if( (oldWeapon == WP_FG42 && newWeapon == WP_FG42SCOPE) ||
        (oldWeapon == WP_FG42SCOPE && newWeapon == WP_FG42) ) {
        *duration = 50;
        return 1;
    }
    if( (oldWeapon == WP_GARAND && newWeapon == WP_GARAND_SCOPE) ||
        (oldWeapon == WP_GARAND_SCOPE && newWeapon == WP_GARAND) ||
        (oldWeapon == WP_K43 && newWeapon == WP_K43_SCOPE) ||
        (oldWeapon == WP_K43_SCOPE && newWeapon == WP_K43) ) {
        *duration = 250;
        return 1;
    }
    return 0;
}

int NITMOD_WeaponChangeNeedsRaise( int oldWeapon, int newWeapon ) {
    return oldWeapon != newWeapon || newWeapon == WP_KNIFE || newWeapon == WP_SMOKE_BOMB;
}

int NITMOD_CommitWeaponChange( playerState_t *state ) {
    int weapon;
    if( !state ) return -1;
    weapon = state->nextWeapon;
    if( weapon < WP_NONE || weapon >= WP_NUM_WEAPONS ) weapon = WP_NONE;
    /* Native inventory words are 32-bit. Unsigned shifting also covers bit 31
     * without the signed-left-shift undefined behavior of COM_BitCheck. */
    if( !((unsigned int)state->weapons[weapon >> 5] & (1u << (weapon & 31))) )
        weapon = WP_NONE;
    state->weapon = weapon;
    state->weaponstate = state->weaponstate == WEAPON_DROPPING_TORELOAD
        ? WEAPON_RAISING_TORELOAD : WEAPON_RAISING;
    return weapon;
}

unsigned int NITMOD_EncodeReloadPreferences( unsigned int clientFlags,
    int autoReloadCvar, int altReloadCvar ) {
    unsigned int flags = clientFlags & ~((unsigned int)CGF_AUTORELOAD | NITMOD_CGF_ALT_RELOAD);
    if( autoReloadCvar > 0 ) flags |= CGF_AUTORELOAD;
    if( altReloadCvar > 0 ) flags |= NITMOD_CGF_ALT_RELOAD;
    return flags;
}

int NITMOD_DecodeReloadPreferences( unsigned int clientFlags,
    nitmodReloadPreferences_t *preferences ) {
    if( !preferences ) return 0;
    preferences->autoReload = (clientFlags & CGF_AUTORELOAD) != 0;
    preferences->attack2Reload = (clientFlags & NITMOD_CGF_ALT_RELOAD) != 0;
    return 1;
}

int NITMOD_ManualReloadRequested( const usercmd_t *command, unsigned int clientFlags ) {
    return command && ((command->wbuttons & WBUTTON_RELOAD) != 0 ||
        ((command->wbuttons & WBUTTON_ATTACK2) != 0 && (clientFlags & NITMOD_CGF_ALT_RELOAD) != 0));
}

int NITMOD_BuildReloadPolicyFromFlags( const usercmd_t *command,
    unsigned int clientFlags, int weaponRequiresAutoReloadSetting,
    unsigned int scopedAbilityBits, int warMode, nitmodReloadPolicy_t *policy ) {
    nitmodReloadPreferences_t preferences;
    nitmodReloadPolicy_t next;
    if( !command || !policy ) return 0;
    NITMOD_DecodeReloadPreferences(clientFlags, &preferences);
    next.manualRequested = NITMOD_ManualReloadRequested(command, clientFlags);
    next.automaticAllowed = preferences.autoReload || !weaponRequiresAutoReloadSetting;
    next.scopedAbilityBits = scopedAbilityBits;
    next.warMode = warMode;
    *policy = next;
    return 1;
}

int NITMOD_BuildPmoveReloadPolicy( const pmove_t *move,
    int weaponRequiresAutoReloadSetting, unsigned int scopedAbilityBits,
    int warMode, nitmodReloadPolicy_t *policy ) {
    if( !move ) return 0;
    return NITMOD_BuildReloadPolicyFromFlags(&move->cmd, move->nitmodReloadPreferenceFlags,
        weaponRequiresAutoReloadSetting, scopedAbilityBits, warMode, policy);
}

int NITMOD_BuildReloadPolicy( const pmove_t *move, int attack2ReloadEnabled,
    int weaponRequiresAutoReloadSetting, unsigned int scopedAbilityBits,
    int warMode, nitmodReloadPolicy_t *policy ) {
    nitmodReloadPolicy_t next;
    if( !move || !move->pmext || !policy ) return 0;
    next.manualRequested = NITMOD_ManualReloadRequested(&move->cmd,
        attack2ReloadEnabled ? NITMOD_CGF_ALT_RELOAD : 0);
    next.automaticAllowed = move->pmext->bAutoReload != 0 || !weaponRequiresAutoReloadSetting;
    next.scopedAbilityBits = scopedAbilityBits;
    next.warMode = warMode;
    *policy = next;
    return 1;
}

int NITMOD_DecideReload( const playerState_t *state, int weapon,
    const nitmodReloadPolicy_t *policy, const ammotable_t *ammoTable,
    int ammoSlots, nitmodReloadDecision_t *decision ) {
    nitmodWeaponInventorySlots_t slots;
    nitmodReloadDecision_t next;
    int unscoped = WP_NONE;
    if( !state || !policy || !ammoTable || !decision ||
        !NITMOD_WeaponInventorySlots(weapon, &slots) || weapon >= ammoSlots ) return 0;
    next.action = NITMOD_RELOAD_ACTION_NONE;
    next.weapon = WP_NONE;
    if( weapon == WP_GPG40 || weapon == WP_M7 || !NITMOD_ReloadStateAllowed(state->weaponstate) ) {
        *decision = next;
        return 1;
    }
    switch( weapon ) {
    case WP_GARAND_SCOPE: unscoped = WP_GARAND; break;
    case WP_K43_SCOPE: unscoped = WP_K43; break;
    case WP_FG42SCOPE: unscoped = WP_FG42; break;
    }
    if( unscoped != WP_NONE ) {
        if( policy->manualRequested && NITMOD_ReloadInventoryReady(state, weapon,
            NITMOD_RELOAD_MANUAL, ammoTable, ammoSlots) ) {
            if( (policy->scopedAbilityBits & 0x20u) || policy->warMode == 2 ) {
                next.action = NITMOD_RELOAD_ACTION_BEGIN;
                next.weapon = weapon;
            } else {
                next.action = NITMOD_RELOAD_ACTION_UNSCOPE;
                next.weapon = unscoped;
            }
        }
    } else if( state->weaponTime <= 0 && (policy->manualRequested || policy->automaticAllowed) &&
        NITMOD_ReloadInventoryReady(state, weapon,
            policy->manualRequested ? NITMOD_RELOAD_MANUAL : NITMOD_RELOAD_AUTOMATIC,
            ammoTable, ammoSlots) ) {
        next.action = NITMOD_RELOAD_ACTION_BEGIN;
        next.weapon = weapon;
    }
    *decision = next;
    return 1;
}

int NITMOD_ScaleFastReloadDuration( int baseDuration ) {
    /* 0x3f266666 = 5452595 / 8388608. The signed product fits int64_t;
     * division truncates toward zero, including negative legacy inputs. */
    return (int)(((int64_t)baseDuration * 5452595) / 8388608);
}

int NITMOD_ReloadDuration( int weapon, int baseDuration,
    unsigned int lightWeaponAbilityBits, int *duration ) {
    nitmodWeaponInventorySlots_t slots;
    int fast = 0;
    if( !duration || baseDuration < 0 || !NITMOD_WeaponInventorySlots(weapon, &slots) ) return 0;
    switch( weapon ) {
    case WP_LUGER: case WP_MP40: case WP_COLT: case WP_THOMPSON:
    case WP_STEN: case WP_SILENCER: case WP_FG42: case WP_SILENCED_COLT:
        fast = (lightWeaponAbilityBits & NITMOD_FAST_RELOAD) != 0;
        break;
    }
    *duration = fast ? NITMOD_ScaleFastReloadDuration(baseDuration) : baseDuration;
    return 1;
}

int NITMOD_ReloadStateAllowed( int weaponState ) {
    return weaponState == WEAPON_READY || weaponState == WEAPON_FIRING ||
        weaponState == WEAPON_FIRINGALT;
}

int NITMOD_WeaponChangeStateAllowed( int weaponState ) {
    return weaponState != WEAPON_DROPPING && weaponState != WEAPON_DROPPING_TORELOAD &&
        weaponState != WEAPON_RELOADING;
}

int NITMOD_ApplyReloadTiming( playerState_t *state, int duration ) {
    int nextTime;
    if( !state || duration < 0 || !NITMOD_ReloadStateAllowed(state->weaponstate) ) return 0;
    nextTime = state->weaponTime;
    if( state->weaponstate == WEAPON_READY ) {
        if( nextTime > INT_MAX - duration ) return 0;
        nextTime += duration;
    } else if( nextTime < duration ) nextTime = duration;
    state->weaponTime = nextTime;
    state->weaponstate = WEAPON_RELOADING;
    return 1;
}

nitmodReloadStartInventory_t NITMOD_PrepareReloadInventory(
    playerState_t *state, int targetWeapon,
    const nitmodWeaponOptions_t *options, unsigned int reloadAbilityBits ) {
    nitmodReloadStartInventory_t result;
    if( !state ) return NITMOD_RELOAD_START_INVALID;
    if( !NITMOD_ReloadStateAllowed(state->weaponstate) ) return NITMOD_RELOAD_START_BLOCKED;
    result = NITMOD_CheckReloadStartInventory(state, targetWeapon, options, reloadAbilityBits);
    if( result == NITMOD_RELOAD_START_EMPTY_RESERVE ) state->weaponstate = WEAPON_READY;
    return result;
}

int NITMOD_ReloadWeaponEligible( int weapon ) {
    nitmodWeaponInventorySlots_t slots;
    if( !NITMOD_WeaponInventorySlots(weapon, &slots) ) return 0;
    switch( weapon ) {
    case WP_SMOKETRAIL: case WP_MEDKIT: case WP_BINOCULARS:
    case WP_PLIERS: case WP_SMOKE_MARKER:
        return 0;
    default:
        return 1;
    }
}

int NITMOD_ReloadUsesOuterClipGate( int weapon ) {
    switch( weapon ) {
    case WP_LUGER: case WP_COLT: case WP_SILENCER: case WP_SILENCED_COLT:
    case WP_MP40: case WP_THOMPSON: case WP_STEN: case WP_FG42:
    case WP_AKIMBO_LUGER: case WP_AKIMBO_COLT:
    case WP_AKIMBO_SILENCEDLUGER: case WP_AKIMBO_SILENCEDCOLT:
        return 1;
    default: return 0;
    }
}

nitmodReloadStartInventory_t NITMOD_CheckReloadStartInventory(
    const playerState_t *state, int targetWeapon,
    const nitmodWeaponOptions_t *options, unsigned int reloadAbilityBits ) {
    nitmodWeaponInventorySlots_t current, target;
    int reserve;
    if( !state || !options || !NITMOD_WeaponInventorySlots(state->weapon, &current) ||
        !NITMOD_WeaponInventorySlots(targetWeapon, &target) ) return NITMOD_RELOAD_START_INVALID;
    reserve = state->ammo[current.ammo];
    if( reserve < 0 ) return NITMOD_RELOAD_START_INVALID;
    if( !reserve ) return NITMOD_RELOAD_START_EMPTY_RESERVE;
    if( state->ammoclip[target.clip] < 0 ) return NITMOD_RELOAD_START_INVALID;
    if( !NITMOD_MidclipReloadAllowed(state, targetWeapon, options, reloadAbilityBits) ||
        !NITMOD_ReloadWeaponEligible(targetWeapon) ) return NITMOD_RELOAD_START_BLOCKED;
    return NITMOD_RELOAD_START_INVENTORY_ALLOWED;
}

int NITMOD_MidclipReloadAllowed( const playerState_t *state, int weapon,
    const nitmodWeaponOptions_t *options, unsigned int reloadAbilityBits ) {
    nitmodWeaponInventorySlots_t slots;
    int clip;
    if( !state || !options || !NITMOD_WeaponInventorySlots(weapon, &slots) ) return 0;
    clip = state->ammoclip[slots.clip];
    if( clip < 0 ) return 0;
    if( weapon == WP_MOBILE_MG42 || weapon == WP_MOBILE_MG42_SET )
        return clip == 0 || (reloadAbilityBits & NITMOD_MG42_MIDCLIP_RELOAD) != 0;
    return !options->noMidclipReload || clip == 0;
}

int NITMOD_ReloadInventoryReady( const playerState_t *state, int weapon,
    nitmodReloadRequest_t request, const ammotable_t *ammoTable, int ammoSlots ) {
    nitmodWeaponInventorySlots_t slots, sideSlots;
    int clip, sideClip, capacity, sideCapacity, sidearm;
    if( !state || !ammoTable ||
        (request != NITMOD_RELOAD_AUTOMATIC && request != NITMOD_RELOAD_MANUAL) ||
        !NITMOD_WeaponInventorySlots(weapon, &slots) || weapon >= ammoSlots ) return 0;
    clip = state->ammoclip[slots.clip];
    capacity = ammoTable[weapon].maxclip;
    if( state->ammo[slots.ammo] <= 0 || clip < 0 || capacity < 0 ) return 0;
    if( BG_IsAkimboWeapon(weapon) ) {
        sidearm = BG_AkimboSidearm(weapon);
        if( !NITMOD_WeaponInventorySlots(sidearm, &sideSlots) || sideSlots.clip >= ammoSlots ) return 0;
        sideClip = state->ammoclip[sideSlots.clip];
        /* PM_CheckForReload uses the SIDEARM CLIP alias for capacity, unlike
         * PM_ReloadClip's weapon-indexed capacity. Keep that distinction. */
        sideCapacity = ammoTable[sideSlots.clip].maxclip;
        if( sideClip < 0 || sideCapacity < 0 ) return 0;
        if( request == NITMOD_RELOAD_AUTOMATIC ) return clip == 0 && sideClip == 0;
        return clip < capacity || sideClip < sideCapacity;
    }
    return request == NITMOD_RELOAD_AUTOMATIC ? clip == 0 : clip < capacity;
}

int NITMOD_ReloadWeaponClips( playerState_t *state, int weapon,
    const ammotable_t *ammoTable, int ammoSlots ) {
    nitmodWeaponInventorySlots_t slots[2];
    int weapons[2], clips[2], hands, i, reserve, capacity, transfer;
    if( !state || !ammoTable || !NITMOD_WeaponInventorySlots(weapon, &slots[0]) ) return 0;
    weapons[0] = weapon;
    hands = BG_IsAkimboWeapon(weapon) ? 2 : 1;
    if( hands == 2 ) {
        weapons[1] = BG_AkimboSidearm(weapon);
        if( !NITMOD_WeaponInventorySlots(weapons[1], &slots[1]) ||
            slots[1].ammo != slots[0].ammo || slots[1].clip == slots[0].clip ) return 0;
    }
    reserve = state->ammo[slots[0].ammo];
    if( reserve < 0 ) return 0;
    /* Stage both hands before committing: a bad sidearm cannot partially
     * reload the first hand. The original mutates sequentially instead. */
    for( i = 0; i < hands; ++i ) {
        if( weapons[i] >= ammoSlots ) return 0;
        capacity = ammoTable[weapons[i]].maxclip;
        clips[i] = state->ammoclip[slots[i].clip];
        if( capacity < 0 || clips[i] < 0 ) return 0;
        transfer = capacity - clips[i];
        if( transfer > reserve ) transfer = reserve;
        if( transfer < 0 && reserve > INT_MAX + transfer ) return 0;
        reserve -= transfer;
        clips[i] += transfer;
    }
    state->ammo[slots[0].ammo] = reserve;
    for( i = 0; i < hands; ++i ) state->ammoclip[slots[i].clip] = clips[i];
    return 1;
}

int NITMOD_FinishWeaponReload( pmove_t *move,
    const ammotable_t *ammoTable, int ammoSlots ) {
    playerState_t *state;
    int animation = WEAP_IDLE1;
    if( !move || !move->ps || !move->pmext || !ammoTable ) return -1;
    state = move->ps;
    if( state->weaponstate != WEAPON_RELOADING || state->weaponTime > 0 || state->weaponDelay > 0 ) return 0;
    if( !NITMOD_ReloadWeaponClips(state, state->weapon, ammoTable, ammoSlots) ) return -1;
    state->weaponstate = WEAPON_READY;
    if( state->pm_type >= PM_DEAD || move->pmext->weapAnimTimer > 0 || move->cmd.weapon == WP_NONE ) return 1;
    switch( state->weapon ) {
    case WP_GPG40: case WP_M7: case WP_SATCHEL_DET: case WP_MORTAR_SET:
    case WP_MEDIC_ADRENALINE: case WP_MOBILE_MG42_SET:
        animation = WEAP_IDLE2;
        break;
    }
    state->weapAnim = ((state->weapAnim & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT) | animation;
    return 1;
}
