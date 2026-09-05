#include "nitmod_weapon_reload.h"
#include "nitmod_weapon_defaults.h"
#include <limits.h>
#include <stdio.h>
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "reload check failed at %d\n", __LINE__); return 1; } } while(0)

static int TestStartInventory( void ) {
    playerState_t state, before;
    nitmodWeaponInventorySlots_t currentSlots, targetSlots;
    nitmodWeaponOptions_t options;
    int current, target, reserve, clip, flag, ability, expected, midclip;
    for( current = 1; current < WP_NUM_WEAPONS; ++current ) {
        if( !NITMOD_WeaponInventorySlots(current, &currentSlots) ) continue;
        for( target = 1; target < WP_NUM_WEAPONS; ++target ) {
            if( !NITMOD_WeaponInventorySlots(target, &targetSlots) ) continue;
            for( reserve = -1; reserve <= 1; ++reserve ) for( clip = 0; clip < 2; ++clip )
            for( flag = 0; flag < 2; ++flag ) for( ability = 0; ability < 2; ++ability ) {
                memset(&state, 0x25, sizeof(state));
                state.weapon = current;
                state.ammo[targetSlots.ammo] = 0;
                state.ammo[currentSlots.ammo] = reserve;
                state.ammoclip[targetSlots.clip] = clip;
                options.noMidclipReload = flag;
                before = state;
                midclip = (target == WP_MOBILE_MG42 || target == WP_MOBILE_MG42_SET)
                    ? (!clip || ability) : (!clip || !flag);
                if( reserve < 0 ) expected = NITMOD_RELOAD_START_INVALID;
                else if( !reserve ) expected = NITMOD_RELOAD_START_EMPTY_RESERVE;
                else if( !midclip || !NITMOD_ReloadWeaponEligible(target) ) expected = NITMOD_RELOAD_START_BLOCKED;
                else expected = NITMOD_RELOAD_START_INVENTORY_ALLOWED;
                CHECK(NITMOD_CheckReloadStartInventory(&state, target, &options, ability ? 0x20u : 0) == expected);
                CHECK(!memcmp(&state, &before, sizeof(state)));
            }
        }
    }
    memset(&state, 0, sizeof(state));
    state.weapon = WP_COLT;
    options.noMidclipReload = 1;
    state.ammoclip[WP_K43] = -1;
    CHECK(NITMOD_CheckReloadStartInventory(&state, WP_K43, &options, 0) == NITMOD_RELOAD_START_EMPTY_RESERVE);
    state.ammo[WP_COLT] = 1;
    CHECK(NITMOD_CheckReloadStartInventory(&state, WP_K43, &options, 0) == NITMOD_RELOAD_START_INVALID);
    before = state;
    CHECK(NITMOD_CheckReloadStartInventory(NULL, WP_K43, &options, 0) == NITMOD_RELOAD_START_INVALID);
    CHECK(NITMOD_CheckReloadStartInventory(&state, WP_K43, NULL, 0) == NITMOD_RELOAD_START_INVALID);
    CHECK(NITMOD_CheckReloadStartInventory(&state, WP_NONE, &options, 0) == NITMOD_RELOAD_START_INVALID);
    CHECK(NITMOD_CheckReloadStartInventory(&state, INT_MAX, &options, 0) == NITMOD_RELOAD_START_INVALID);
    CHECK(!memcmp(&state, &before, sizeof(state)));
    state.weapon = WP_NONE;
    CHECK(NITMOD_CheckReloadStartInventory(&state, WP_COLT, &options, 0) == NITMOD_RELOAD_START_INVALID);
    return 0;
}

static int TestWeaponChangeRaise( void ) {
    playerState_t state;
    int oldWeapon, newWeapon, reload, owned, result;
    for( oldWeapon = 0; oldWeapon < WP_NUM_WEAPONS; ++oldWeapon )
    for( newWeapon = 0; newWeapon < WP_NUM_WEAPONS; ++newWeapon ) {
        CHECK(NITMOD_WeaponChangeNeedsRaise(oldWeapon, newWeapon) ==
            (oldWeapon != newWeapon || newWeapon == WP_KNIFE || newWeapon == WP_SMOKE_BOMB));
        /* The real caller tests the committed (possibly NONE) target, not
         * nextWeapon. Cover lost ownership and both reload-intent paths. */
        for( reload = 0; reload < 2; ++reload ) for( owned = 0; owned < 2; ++owned ) {
            memset(&state, 0, sizeof(state));
            memset(state.weapons, owned ? 0xff : 0, sizeof(state.weapons));
            state.weapon = oldWeapon;
            state.nextWeapon = newWeapon;
            state.weaponstate = reload ? WEAPON_DROPPING_TORELOAD : WEAPON_DROPPING;
            result = NITMOD_CommitWeaponChange(&state);
            CHECK(result == (owned ? newWeapon : WP_NONE));
            CHECK(NITMOD_WeaponChangeNeedsRaise(oldWeapon, result) ==
                (oldWeapon != result || result == WP_KNIFE || result == WP_SMOKE_BOMB));
            CHECK(state.weaponstate == (reload ? WEAPON_RAISING_TORELOAD : WEAPON_RAISING));
        }
    }
    return 0;
}

static int TestDeploySwitch( void ) {
    static const int cases[][5] = {
        { WP_MOBILE_MG42, WP_MOBILE_MG42_SET, 1250, qfalse, qtrue },
        { WP_MOBILE_MG42_SET, WP_MOBILE_MG42, 1722, qfalse, qfalse },
        { WP_MORTAR, WP_MORTAR_SET, 1667, qtrue, qtrue },
        { WP_MORTAR_SET, WP_MORTAR, 1000, qtrue, qfalse }
    };
    nitmodDeploySwitch_t result, sentinel;
    int oldWeapon, newWeapon, i, match;
    for( oldWeapon = -1; oldWeapon <= WP_NUM_WEAPONS; ++oldWeapon )
    for( newWeapon = -1; newWeapon <= WP_NUM_WEAPONS; ++newWeapon ) {
        match = -1;
        for( i = 0; i < 4; ++i )
            if( oldWeapon == cases[i][0] && newWeapon == cases[i][1] ) match = i;
        memset(&result, 0x25, sizeof(result));
        sentinel = result;
        CHECK(NITMOD_DeploySwitch(oldWeapon, newWeapon, &result) == (match >= 0));
        if( match >= 0 ) {
            CHECK(weapAlts[oldWeapon] == newWeapon);
            CHECK(result.raiseTime == cases[match][2]);
            CHECK(result.raiseAltAnimation == cases[match][3]);
            CHECK(result.captureDirection == cases[match][4]);
        } else CHECK(!memcmp(&result, &sentinel, sizeof(result)));
        CHECK(!NITMOD_DeploySwitch(oldWeapon, newWeapon, NULL));
    }
    result = sentinel;
    CHECK(!NITMOD_DeploySwitch(INT_MIN, WP_MORTAR_SET, &result));
    CHECK(!NITMOD_DeploySwitch(WP_MORTAR, INT_MAX, &result));
    CHECK(!memcmp(&result, &sentinel, sizeof(result)));
    return 0;
}

static int TestRifleGrenadeSwitch( void ) {
    playerState_t state, before;
    nitmodRifleGrenadeRaise_t result, sentinel;
    int oldWeapon, newWeapon, attaching, removing, c, r, requested, i, expected;
    int clips[] = { INT_MIN, -1, 0, 1, 2, INT_MAX };
    int flags[] = { INT_MIN, -1, 0, 1, 2, 3, 4, 5, INT_MAX };
    for( oldWeapon = 0; oldWeapon < WP_NUM_WEAPONS; ++oldWeapon )
    for( newWeapon = 0; newWeapon < WP_NUM_WEAPONS; ++newWeapon )
    for( c = 0; c < 6; ++c ) for( r = -1; r <= 1; ++r ) {
        attaching = (oldWeapon == WP_CARBINE && newWeapon == WP_M7) ||
            (oldWeapon == WP_KAR98 && newWeapon == WP_GPG40);
        removing = (oldWeapon == WP_M7 && newWeapon == WP_CARBINE) ||
            (oldWeapon == WP_GPG40 && newWeapon == WP_KAR98);
        memset(&state, 0x25, sizeof(state));
        state.weapon = newWeapon; /* Finish has already committed this. */
        state.ammoclip[newWeapon] = clips[c];
        state.ammo[newWeapon] = r;
        if( removing ) {
            /* Independent native alias lookup, not the recovered helper. */
            state.ammoclip[BG_FindAmmoForWeapon(oldWeapon)] = clips[c];
            state.ammo[BG_FindAmmoForWeapon(oldWeapon)] = r;
        }
        before = state;
        memset(&result, 0x25, sizeof(result));
        sentinel = result;
        CHECK(NITMOD_RifleGrenadeRaise(&state, oldWeapon, newWeapon, &result) == (attaching || removing));
        if( attaching || removing ) {
            CHECK(result.duration == (attaching ? 2350 : clips[c] ? 1347 : 0));
            CHECK(result.animate == (attaching || clips[c] != 0 ? qtrue : qfalse));
        } else CHECK(!memcmp(&result, &sentinel, sizeof(result)));
        requested = -17;
        CHECK(NITMOD_RifleGrenadeDrop(&state, oldWeapon, newWeapon, &requested) == (attaching || removing));
        CHECK(requested == (attaching || removing ? attaching && !clips[c] && r ? newWeapon : WP_NONE : -17));
        CHECK(!memcmp(&state, &before, sizeof(state)));
    }
    for( newWeapon = -1; newWeapon <= WP_NUM_WEAPONS; ++newWeapon )
    for( i = 0; i < sizeof(flags) / sizeof(flags[0]); ++i ) {
        expected = flags[i];
        if( newWeapon == WP_CARBINE || newWeapon == WP_KAR98 ) expected &= ~2;
        if( newWeapon == WP_M7 || newWeapon == WP_GPG40 ) expected |= 2;
        CHECK(NITMOD_RifleGrenadeModeFlags(newWeapon, flags[i]) == expected);
        CHECK(NITMOD_RifleGrenadeModeFlags(newWeapon, expected) == expected);
        CHECK(NITMOD_PistolModeFlags(newWeapon, expected) ==
            NITMOD_RifleGrenadeModeFlags(newWeapon, NITMOD_PistolModeFlags(newWeapon, flags[i])));
    }
    result = sentinel;
    requested = -17;
    CHECK(!NITMOD_RifleGrenadeRaise(NULL, WP_M7, WP_CARBINE, &result));
    CHECK(!NITMOD_RifleGrenadeRaise(&state, WP_M7, WP_CARBINE, NULL));
    CHECK(!NITMOD_RifleGrenadeRaise(&state, INT_MIN, INT_MAX, &result));
    CHECK(!memcmp(&result, &sentinel, sizeof(result)));
    CHECK(!NITMOD_RifleGrenadeDrop(NULL, WP_CARBINE, WP_M7, &requested));
    CHECK(!NITMOD_RifleGrenadeDrop(&state, WP_CARBINE, WP_M7, NULL));
    CHECK(!NITMOD_RifleGrenadeDrop(&state, INT_MIN, INT_MAX, &requested));
    CHECK(requested == -17);
    return 0;
}

static int TestPistolSwitch( void ) {
    nitmodPistolSwitch_t result, before;
    int oldWeapon, newWeapon, i, attaching, removing, expected;
    int flags[] = { INT_MIN, INT_MIN + 1, -1, 0, 1, 2, 3, 4, 5, 0x55555555, INT_MAX };
    for( oldWeapon = -1; oldWeapon <= WP_NUM_WEAPONS; ++oldWeapon )
    for( newWeapon = -1; newWeapon <= WP_NUM_WEAPONS; ++newWeapon ) {
        attaching = (oldWeapon == WP_LUGER && newWeapon == WP_SILENCER) ||
            (oldWeapon == WP_COLT && newWeapon == WP_SILENCED_COLT);
        removing = (oldWeapon == WP_SILENCER && newWeapon == WP_LUGER) ||
            (oldWeapon == WP_SILENCED_COLT && newWeapon == WP_COLT);
        memset(&result, 0x25, sizeof(result));
        before = result;
        CHECK(NITMOD_PistolSwitch(oldWeapon, newWeapon, &result) == (attaching || removing));
        if( attaching || removing ) {
            CHECK(result.dropTime == (attaching ? 0 : 1000));
            CHECK(result.raiseTime == (attaching ? 1190 : 0));
            CHECK(result.dropAltAnimation == (removing ? qtrue : qfalse));
            CHECK(result.raiseAltAnimation == qtrue);
        } else CHECK(!memcmp(&result, &before, sizeof(result)));
        CHECK(!NITMOD_PistolSwitch(oldWeapon, newWeapon, NULL));
    }
    for( newWeapon = -1; newWeapon <= WP_NUM_WEAPONS; ++newWeapon )
    for( i = 0; i < sizeof(flags) / sizeof(flags[0]); ++i ) {
        expected = flags[i];
        if( newWeapon == WP_LUGER || newWeapon == WP_COLT ) expected &= ~1;
        if( newWeapon == WP_SILENCER || newWeapon == WP_SILENCED_COLT ) expected |= 1;
        CHECK(NITMOD_PistolModeFlags(newWeapon, flags[i]) == expected);
        CHECK(NITMOD_PistolModeFlags(newWeapon, expected) == expected);
    }
    result = before;
    CHECK(!NITMOD_PistolSwitch(INT_MIN, WP_SILENCER, &result));
    CHECK(!NITMOD_PistolSwitch(WP_LUGER, INT_MAX, &result));
    CHECK(!memcmp(&result, &before, sizeof(result)));
    return 0;
}

static int TestScopeSwitchBoundaries( void ) {
    int duration, i, j;
    int invalid[] = { INT_MIN, -1, WP_NUM_WEAPONS, INT_MAX };
    for( i = 0; i < 4; ++i ) for( j = 0; j < WP_NUM_WEAPONS; ++j ) {
        duration = -23;
        CHECK(!NITMOD_ScopeSwitchDuration(invalid[i], j, &duration));
        CHECK(duration == -23);
        CHECK(!NITMOD_ScopeSwitchDuration(j, invalid[i], &duration));
        CHECK(duration == -23);
    }
    for( i = 0; i < WP_NUM_WEAPONS; ++i ) for( j = 0; j < WP_NUM_WEAPONS; ++j )
        CHECK(!NITMOD_ScopeSwitchDuration(i, j, NULL));
    return 0;
}

static int TestWeaponChangeCommit( void ) {
    playerState_t state, expected;
    int target, phase, owned, selected, bit;
    int boundaries[] = { INT_MIN, -1, WP_NUM_WEAPONS, INT_MAX };
    for( target = 0; target < WP_NUM_WEAPONS + 4; ++target ) {
        int request = target < WP_NUM_WEAPONS ? target : boundaries[target - WP_NUM_WEAPONS];
        for( phase = -1; phase <= WEAPON_RELOADING + 1; ++phase )
        for( owned = 0; owned < 4; ++owned ) {
            memset(&state, 0x25, sizeof(state));
            state.nextWeapon = request;
            state.weaponstate = phase;
            memset(state.weapons, owned >= 2 ? 0xff : 0, sizeof(state.weapons));
            /* Independent arithmetic mask construction, including bit 31 and
             * the next inventory word. No host byte-order assumption. */
            if( (owned == 1 || owned == 3) && request >= WP_NONE && request < WP_NUM_WEAPONS ) {
                unsigned int mask = 1, word;
                for( bit = 0; bit < request % 32; ++bit ) mask *= 2;
                word = owned == 1 ? mask : ~mask;
                memcpy(&state.weapons[request / 32], &word, sizeof(word));
            }
            expected = state;
            selected = request >= WP_NONE && request < WP_NUM_WEAPONS && (owned == 1 || owned == 2) ? request : WP_NONE;
            expected.weapon = selected;
            expected.weaponstate = phase == WEAPON_DROPPING_TORELOAD ? WEAPON_RAISING_TORELOAD : WEAPON_RAISING;
            CHECK(NITMOD_CommitWeaponChange(&state) == selected);
            CHECK(!memcmp(&state, &expected, sizeof(state)));
        }
    }
    CHECK(NITMOD_CommitWeaponChange(NULL) == -1);
    return 0;
}

static int TestReloadStates( void ) {
    playerState_t state, expected;
    nitmodWeaponOptions_t options;
    int phase, t, d, reserve, allowed, success, result;
    int times[] = { INT_MIN, -1, 0, 1, 99, INT_MAX - 1, INT_MAX };
    int durations[] = { -1, 0, 1, 100, INT_MAX };
    options.noMidclipReload = 0;
    for( phase = -1; phase <= WEAPON_RELOADING + 1; ++phase ) {
        allowed = phase == WEAPON_READY || phase == WEAPON_FIRING || phase == WEAPON_FIRINGALT;
        CHECK(NITMOD_ReloadStateAllowed(phase) == allowed);
        CHECK(NITMOD_WeaponChangeStateAllowed(phase) ==
            (phase != WEAPON_DROPPING && phase != WEAPON_DROPPING_TORELOAD && phase != WEAPON_RELOADING));
        for( t = 0; t < 7; ++t ) for( d = 0; d < 5; ++d ) {
            memset(&state, 0x25, sizeof(state));
            state.weaponstate = phase;
            state.weaponTime = times[t];
            expected = state;
            success = allowed && durations[d] >= 0;
            if( success && phase == WEAPON_READY && times[t] > INT_MAX - durations[d] ) success = 0;
            if( success ) {
                expected.weaponstate = WEAPON_RELOADING;
                expected.weaponTime = phase == WEAPON_READY ? times[t] + durations[d] :
                    (times[t] > durations[d] ? times[t] : durations[d]);
            }
            CHECK(NITMOD_ApplyReloadTiming(&state, durations[d]) == success);
            CHECK(!memcmp(&state, &expected, sizeof(state)));
        }
        for( reserve = -1; reserve <= 1; ++reserve ) {
            memset(&state, 0x25, sizeof(state));
            state.weapon = WP_COLT;
            state.weaponstate = phase;
            state.ammo[WP_COLT] = reserve;
            state.ammoclip[WP_COLT] = 0;
            expected = state;
            result = !allowed ? NITMOD_RELOAD_START_BLOCKED : reserve < 0 ? NITMOD_RELOAD_START_INVALID :
                reserve == 0 ? NITMOD_RELOAD_START_EMPTY_RESERVE : NITMOD_RELOAD_START_INVENTORY_ALLOWED;
            if( result == NITMOD_RELOAD_START_EMPTY_RESERVE ) expected.weaponstate = WEAPON_READY;
            CHECK(NITMOD_PrepareReloadInventory(&state, WP_COLT, &options, 0) == result);
            CHECK(!memcmp(&state, &expected, sizeof(state)));
        }
    }
    CHECK(!NITMOD_ReloadStateAllowed(INT_MAX) && !NITMOD_ReloadStateAllowed(INT_MIN));
    CHECK(!NITMOD_ApplyReloadTiming(NULL, 1));
    CHECK(NITMOD_PrepareReloadInventory(NULL, WP_COLT, &options, 0) == NITMOD_RELOAD_START_INVALID);
    return 0;
}

static int TestReloadDuration( void ) {
    nitmodWeaponInventorySlots_t slots;
    playerState_t state, expected;
    int weapon, base, bits, value, want, fast, i;
    int edges[] = { 0, 1, 19, 20, 21, 100, 1000, 8388608, INT_MAX };
    for( weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon ) {
        if( !NITMOD_WeaponInventorySlots(weapon, &slots) ) continue;
        for( bits = 0; bits < 8; ++bits ) for( base = 0; base <= 1000; ++base ) {
            fast = BG_isLightWeaponSupportingFastReload(weapon) && (bits & 4);
            /* Products in this range are exact in binary64, independent of
             * the production integer implementation. */
            want = fast ? (int)((double)base * (double)0.65f) : base;
            value = -17;
            CHECK(NITMOD_ReloadDuration(weapon, base, (unsigned int)bits, &value));
            CHECK(value == want);
        }
    }
    for( i = 0; i < 9; ++i ) {
        base = edges[i];
        CHECK(NITMOD_ReloadDuration(WP_COLT, base, ~0u, &value));
        /* Split the product into quotient/remainder to avoid rounded large
         * floating multiplication in the independent boundary oracle. */
        want = (base / 8388608) * 5452595 +
            (int)((double)(base % 8388608) * (double)0.65f);
        CHECK(value == want);
        memset(&state, 0x25, sizeof(state));
        state.weaponstate = WEAPON_FIRINGALT;
        state.weaponTime = 3;
        expected = state;
        expected.weaponstate = WEAPON_RELOADING;
        expected.weaponTime = value > 3 ? value : 3;
        CHECK(NITMOD_ApplyReloadTiming(&state, value));
        CHECK(!memcmp(&state, &expected, sizeof(state)));
    }
    CHECK(NITMOD_ReloadDuration(WP_COLT, 20, 4, &value) && value == 12);
    CHECK(NITMOD_ReloadDuration(WP_COLT, 20, ~4u, &value) && value == 20);
    value = -17;
    CHECK(!NITMOD_ReloadDuration(WP_COLT, -1, 4, &value) && value == -17);
    CHECK(!NITMOD_ReloadDuration(WP_NONE, 20, 4, &value) && value == -17);
    CHECK(!NITMOD_ReloadDuration(INT_MAX, 20, 4, &value) && value == -17);
    CHECK(!NITMOD_ReloadDuration(WP_COLT, 20, 4, NULL));
    return 0;
}

static int TestReloadFinish( void ) {
    pmove_t move, moveBefore;
    pmoveExt_t ext, extBefore;
    playerState_t state, expected;
    ammotable_t table[WP_NUM_WEAPONS];
    nitmodWeaponInventorySlots_t slots;
    int weapon, type, timer, command, toggle, animation;
    memset(&move, 0, sizeof(move));
    memset(&ext, 0, sizeof(ext));
    memset(table, 0, sizeof(table));
    for( weapon = 0; weapon < WP_NUM_WEAPONS; ++weapon ) table[weapon].maxclip = 3;
    move.ps = &state;
    move.pmext = &ext;
    for( weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon ) {
        if( !NITMOD_WeaponInventorySlots(weapon, &slots) ) continue;
        for( type = PM_NORMAL; type <= PM_INTERMISSION; ++type )
        for( timer = -1; timer <= 1; ++timer ) for( command = 0; command < 2; ++command )
        for( toggle = 0; toggle < 2; ++toggle ) {
            memset(&state, 0, sizeof(state));
            state.weapon = weapon;
            state.weaponstate = WEAPON_RELOADING;
            state.pm_type = type;
            state.ammo[slots.ammo] = 9;
            state.weapAnim = 123 | (toggle ? ANIM_TOGGLEBIT : 0);
            expected = state;
            CHECK(NITMOD_ReloadWeaponClips(&expected, weapon, table, WP_NUM_WEAPONS));
            expected.weaponstate = WEAPON_READY;
            ext.weapAnimTimer = timer;
            move.cmd.weapon = command ? WP_COLT : WP_NONE;
            moveBefore = move;
            extBefore = ext;
            if( type < PM_DEAD && timer <= 0 && command ) {
                animation = weapon == WP_GPG40 || weapon == WP_M7 || weapon == WP_SATCHEL_DET ||
                    weapon == WP_MORTAR_SET || weapon == WP_MEDIC_ADRENALINE || weapon == WP_MOBILE_MG42_SET
                    ? WEAP_IDLE2 : WEAP_IDLE1;
                expected.weapAnim = (toggle ? 0 : ANIM_TOGGLEBIT) | animation;
            }
            CHECK(NITMOD_FinishWeaponReload(&move, table, WP_NUM_WEAPONS) == 1);
            CHECK(!memcmp(&state, &expected, sizeof(state)));
            CHECK(!memcmp(&move, &moveBefore, sizeof(move)) && !memcmp(&ext, &extBefore, sizeof(ext)));
            CHECK(NITMOD_FinishWeaponReload(&move, table, WP_NUM_WEAPONS) == 0);
            CHECK(!memcmp(&state, &expected, sizeof(state)));
        }
    }
    state.weapon = WP_COLT;
    state.weaponstate = WEAPON_RELOADING;
    state.weaponTime = 1;
    state.weaponDelay = 0;
    expected = state;
    CHECK(NITMOD_FinishWeaponReload(&move, table, WP_NUM_WEAPONS) == 0);
    CHECK(!memcmp(&state, &expected, sizeof(state)));
    state.weaponTime = 0;
    state.weaponDelay = 1;
    expected = state;
    CHECK(NITMOD_FinishWeaponReload(&move, table, WP_NUM_WEAPONS) == 0);
    CHECK(!memcmp(&state, &expected, sizeof(state)));
    state.weaponDelay = 0;
    state.ammo[WP_COLT] = -1;
    expected = state;
    CHECK(NITMOD_FinishWeaponReload(&move, table, WP_NUM_WEAPONS) == -1);
    CHECK(!memcmp(&state, &expected, sizeof(state)));
    CHECK(NITMOD_FinishWeaponReload(NULL, table, WP_NUM_WEAPONS) == -1);
    CHECK(NITMOD_FinishWeaponReload(&move, NULL, WP_NUM_WEAPONS) == -1);
    move.pmext = NULL;
    CHECK(NITMOD_FinishWeaponReload(&move, table, WP_NUM_WEAPONS) == -1);
    move.ps = NULL;
    CHECK(NITMOD_FinishWeaponReload(&move, table, WP_NUM_WEAPONS) == -1);
    return 0;
}

static int TestReloadFeedback( void ) {
    pmove_t move, moveBefore;
    pmoveExt_t ext, extBefore;
    playerState_t state, expected;
    nitmodWeaponInventorySlots_t slots;
    int targets[] = { WP_COLT, WP_MORTAR, WP_MORTAR_SET };
    int weapon, t, fast, same, gate, toggle, animation, index;
    memset(&move, 0, sizeof(move));
    memset(&ext, 0, sizeof(ext));
    move.ps = &state;
    move.pmext = &ext;
    for( weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon ) {
        if( !NITMOD_WeaponInventorySlots(weapon, &slots) ) continue;
        for( t = 0; t < 3; ++t ) for( fast = 0; fast < 2; ++fast )
        for( same = 0; same < 2; ++same ) for( gate = 0; gate < 4; ++gate )
        for( toggle = 0; toggle < 2; ++toggle ) {
            memset(&state, 0x25, sizeof(state));
            state.weapon = weapon;
            state.weaponstate = WEAPON_READY;
            state.weaponTime = 50;
            state.pm_type = gate == 1 ? PM_DEAD : PM_NORMAL;
            ext.weapAnimTimer = gate == 2 ? 1 : 0;
            move.cmd.weapon = gate == 3 ? WP_NONE : WP_COLT;
            animation = weapon == WP_GPG40 || weapon == WP_M7 ? WEAP_RELOAD2 :
                weapon == WP_MOBILE_MG42_SET ? WEAP_RELOAD3 :
                fast && BG_isLightWeaponSupportingFastReload(weapon) ? WEAP_RELOAD2 : WEAP_RELOAD1;
            state.weapAnim = (same ? animation : WEAP_IDLE1) | (toggle ? ANIM_TOGGLEBIT : 0);
            state.eventSequence = 2 * MAX_EVENTS - 1 + toggle;
            expected = state;
            expected.weaponstate = WEAPON_RELOADING;
            expected.weaponTime = 150;
            if( !t && !same && !gate ) expected.weapAnim = animation | (toggle ? 0 : ANIM_TOGGLEBIT);
            index = expected.eventSequence & (MAX_EVENTS - 1);
            expected.events[index] = EV_FILL_CLIP;
            expected.eventParms[index] = 0;
            ++expected.eventSequence;
            moveBefore = move; extBefore = ext;
            CHECK(NITMOD_ApplyReloadFeedback(&move, targets[t], 100, fast ? 4u : 0));
            CHECK(!memcmp(&state, &expected, sizeof(state)));
            CHECK(!memcmp(&move, &moveBefore, sizeof(move)) && !memcmp(&ext, &extBefore, sizeof(ext)));
            CHECK(!NITMOD_ApplyReloadFeedback(&move, targets[t], 100, 0));
            CHECK(!memcmp(&state, &expected, sizeof(state)));
        }
    }
    state.weaponstate = WEAPON_READY;
    state.eventSequence = INT_MAX;
    expected = state;
    CHECK(!NITMOD_ApplyReloadFeedback(&move, WP_COLT, 100, 0));
    CHECK(!memcmp(&state, &expected, sizeof(state)));
    state.eventSequence = 0;
    state.weaponTime = INT_MAX;
    expected = state;
    CHECK(!NITMOD_ApplyReloadFeedback(&move, WP_COLT, 1, 0));
    CHECK(!NITMOD_ApplyReloadFeedback(&move, WP_COLT, -1, 0));
    CHECK(!NITMOD_ApplyReloadFeedback(&move, WP_NONE, 0, 0));
    CHECK(!NITMOD_ApplyReloadFeedback(NULL, WP_COLT, 0, 0));
    CHECK(!memcmp(&state, &expected, sizeof(state)));
    return 0;
}

static int TestReloadDecision( void ) {
    playerState_t state, before;
    ammotable_t table[WP_NUM_WEAPONS];
    nitmodWeaponInventorySlots_t slots, sideSlots;
    nitmodReloadPolicy_t policy;
    nitmodReloadDecision_t decision, expected;
    int phases[] = { WEAPON_READY, WEAPON_FIRINGALT, WEAPON_RELOADING };
    int weapon, timer, manual, automatic, scope, war, inventory, phase, unscoped, count;
    memset(table, 0, sizeof(table));
    for( weapon = 0; weapon < WP_NUM_WEAPONS; ++weapon ) table[weapon].maxclip = 3;
    count = 0;
    for( weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon ) {
        if( !NITMOD_WeaponInventorySlots(weapon, &slots) ) continue;
        unscoped = weapon == WP_GARAND_SCOPE ? WP_GARAND : weapon == WP_K43_SCOPE ? WP_K43 :
            weapon == WP_FG42SCOPE ? WP_FG42 : WP_NONE;
        for( timer = -1; timer <= 1; ++timer ) for( manual = 0; manual < 2; ++manual )
        for( automatic = 0; automatic < 2; ++automatic ) for( scope = 0; scope < 2; ++scope )
        for( war = 1; war <= 3; ++war ) for( inventory = 0; inventory < 3; ++inventory )
        for( phase = 0; phase < 3; ++phase ) {
            memset(&state, 0, sizeof(state));
            state.weapon = weapon; state.weaponstate = phases[phase]; state.weaponTime = timer;
            state.ammo[slots.ammo] = 1;
            state.ammoclip[slots.clip] = inventory == 2 ? 3 : inventory;
            if( BG_IsAkimboWeapon(weapon) ) {
                CHECK(NITMOD_WeaponInventorySlots(BG_AkimboSidearm(weapon), &sideSlots));
                state.ammoclip[sideSlots.clip] = state.ammoclip[slots.clip];
            }
            before = state;
            policy.manualRequested = manual; policy.automaticAllowed = automatic;
            policy.scopedAbilityBits = scope ? 0x20u : 0; policy.warMode = war;
            expected.action = NITMOD_RELOAD_ACTION_NONE; expected.weapon = WP_NONE;
            if( phase != 2 && weapon != WP_GPG40 && weapon != WP_M7 ) {
                if( unscoped != WP_NONE ) {
                    if( manual && inventory != 2 ) {
                        expected.action = scope || war == 2 ? NITMOD_RELOAD_ACTION_BEGIN : NITMOD_RELOAD_ACTION_UNSCOPE;
                        expected.weapon = scope || war == 2 ? weapon : unscoped;
                    }
                } else if( timer <= 0 && (manual ? inventory != 2 : automatic && inventory == 0) ) {
                    expected.action = NITMOD_RELOAD_ACTION_BEGIN; expected.weapon = weapon;
                }
            }
            CHECK(NITMOD_DecideReload(&state, weapon, &policy, table, WP_NUM_WEAPONS, &decision));
            CHECK(decision.action == expected.action && decision.weapon == expected.weapon);
            CHECK(!memcmp(&state, &before, sizeof(state)));
            ++count;
        }
    }
    CHECK(count == 31104);
    decision.action = NITMOD_RELOAD_ACTION_UNSCOPE; decision.weapon = -17;
    CHECK(!NITMOD_DecideReload(NULL, WP_COLT, &policy, table, WP_NUM_WEAPONS, &decision));
    CHECK(!NITMOD_DecideReload(&state, WP_COLT, NULL, table, WP_NUM_WEAPONS, &decision));
    CHECK(!NITMOD_DecideReload(&state, WP_COLT, &policy, NULL, WP_NUM_WEAPONS, &decision));
    CHECK(!NITMOD_DecideReload(&state, WP_COLT, &policy, table, WP_COLT, &decision));
    CHECK(!NITMOD_DecideReload(&state, WP_NONE, &policy, table, WP_NUM_WEAPONS, &decision));
    CHECK(!NITMOD_DecideReload(&state, WP_COLT, &policy, table, WP_NUM_WEAPONS, NULL));
    CHECK(decision.action == NITMOD_RELOAD_ACTION_UNSCOPE && decision.weapon == -17);
    return 0;
}

static int TestReloadInput( void ) {
    pmove_t move, beforeMove;
    pmoveExt_t ext, beforeExt;
    playerState_t state;
    ammotable_t table[WP_NUM_WEAPONS];
    nitmodReloadPolicy_t policy, sentinel;
    nitmodReloadDecision_t decision;
    int buttons, attack, automatic, flag, weapon, required, supported, exempt;
    memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
    move.pmext = &ext;
    for( buttons = 0; buttons < 256; ++buttons ) for( attack = -1; attack <= 1; ++attack )
    for( automatic = -1; automatic <= 1; ++automatic ) for( flag = -1; flag <= 1; ++flag ) {
        move.cmd.wbuttons = (byte)buttons;
        move.cmd.buttons = 255;
        ext.bAutoReload = automatic;
        beforeMove = move; beforeExt = ext;
        CHECK(NITMOD_BuildReloadPolicy(&move, attack, flag, 0x80000020u, -7, &policy));
        CHECK(policy.manualRequested == ((buttons & 8) != 0 || ((buttons & 1) != 0 && attack != 0)));
        CHECK(policy.automaticAllowed == (automatic != 0 || flag == 0));
        CHECK(policy.scopedAbilityBits == 0x80000020u && policy.warMode == -7);
        CHECK(!memcmp(&move, &beforeMove, sizeof(move)) && !memcmp(&ext, &beforeExt, sizeof(ext)));
    }
    memset(&state, 0, sizeof(state)); memset(table, 0, sizeof(table));
    move.ps = &state; move.cmd.buttons = BUTTON_ATTACK; move.cmd.wbuttons = 0;
    ext.bAutoReload = qfalse;
    state.weapon = WP_COLT; state.weaponstate = WEAPON_READY;
    state.ammo[WP_COLT] = 2; state.ammoclip[WP_COLT] = 1; table[WP_COLT].maxclip = 3;
    CHECK(NITMOD_BuildReloadPolicy(&move, 1, 1, 0, 0, &policy));
    CHECK(NITMOD_DecideReload(&state, WP_COLT, &policy, table, WP_NUM_WEAPONS, &decision));
    CHECK(decision.action == NITMOD_RELOAD_ACTION_NONE);
    move.cmd.wbuttons = WBUTTON_ATTACK2;
    CHECK(NITMOD_BuildReloadPolicy(&move, 1, 1, 0, 0, &policy));
    CHECK(NITMOD_DecideReload(&state, WP_COLT, &policy, table, WP_NUM_WEAPONS, &decision));
    CHECK(decision.action == NITMOD_RELOAD_ACTION_BEGIN);
    move.cmd.wbuttons = 0; state.ammoclip[WP_COLT] = 0;
    CHECK(NITMOD_BuildReloadPolicy(&move, 0, 0, 0, 0, &policy));
    CHECK(NITMOD_DecideReload(&state, WP_COLT, &policy, table, WP_NUM_WEAPONS, &decision));
    CHECK(decision.action == NITMOD_RELOAD_ACTION_BEGIN);
    sentinel = policy;
    CHECK(!NITMOD_BuildReloadPolicy(NULL, 0, 0, 0, 0, &policy));
    CHECK(!NITMOD_BuildReloadPolicy(&move, 0, 0, 0, 0, NULL));
    move.pmext = NULL;
    CHECK(!NITMOD_BuildReloadPolicy(&move, 0, 0, 0, 0, &policy));
    CHECK(!memcmp(&policy, &sentinel, sizeof(policy)));
    move.pmext = &ext; move.cmd.wbuttons = 0;
    supported = exempt = 0;
    for( weapon = 0; weapon < WP_NUM_WEAPONS; ++weapon ) {
        if( !NITMOD_WeaponAutoReloadDefault(weapon, &required) ) continue;
        ++supported; exempt += !required;
        for( automatic = 0; automatic < 2; ++automatic ) {
            ext.bAutoReload = automatic;
            CHECK(NITMOD_BuildReloadPolicy(&move, 0, required, 0, 0, &policy));
            CHECK(policy.automaticAllowed == (automatic || !required));
            CHECK(!policy.manualRequested);
        }
    }
    CHECK(supported == 48 && exempt == 27);
    return 0;
}

static int TestReloadPreferences( void ) {
    pmove_t move;
    pmoveExt_t ext;
    nitmodReloadPolicy_t fromFlags, fromLocal, fromPmove;
    nitmodReloadPreferences_t prefs;
    unsigned int flags, encoded, untouched;
    int values[] = { INT_MIN, -1, 0, 1, INT_MAX };
    int a, b, buttons, required;
    memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext)); move.pmext = &ext;
    for( flags = 0; flags < 128; ++flags ) for( a = 0; a < 5; ++a ) for( b = 0; b < 5; ++b ) {
        untouched = (flags | 0x80000000u) & ~0x11u;
        encoded = NITMOD_EncodeReloadPreferences(flags | 0x80000000u, values[a], values[b]);
        CHECK((encoded & ~0x11u) == untouched);
        CHECK(NITMOD_DecodeReloadPreferences(encoded, &prefs));
        CHECK(prefs.autoReload == (values[a] > 0) && prefs.attack2Reload == (values[b] > 0));
        CHECK(NITMOD_EncodeReloadPreferences(encoded, values[a], values[b]) == encoded);
        ext.bAutoReload = prefs.autoReload;
        for( buttons = 0; buttons < 16; ++buttons ) for( required = 0; required < 2; ++required ) {
            move.cmd.wbuttons = (byte)buttons;
            CHECK(NITMOD_BuildReloadPolicyFromFlags(&move.cmd, encoded, required, 0x20u, 2, &fromFlags));
            CHECK(NITMOD_BuildReloadPolicy(&move, prefs.attack2Reload, required, 0x20u, 2, &fromLocal));
            CHECK(!memcmp(&fromFlags, &fromLocal, sizeof(fromFlags)));
            move.nitmodReloadPreferenceFlags = encoded;
            CHECK(NITMOD_BuildPmoveReloadPolicy(&move, required, 0x20u, 2, &fromPmove));
            CHECK(!memcmp(&fromPmove, &fromFlags, sizeof(fromFlags)));
        }
    }
    fromLocal = fromFlags;
    CHECK(!NITMOD_BuildReloadPolicyFromFlags(NULL, 0, 0, 0, 0, &fromFlags));
    CHECK(!NITMOD_BuildReloadPolicyFromFlags(&move.cmd, 0, 0, 0, 0, NULL));
    CHECK(!memcmp(&fromFlags, &fromLocal, sizeof(fromFlags)));
    CHECK(!NITMOD_DecodeReloadPreferences(0, NULL));
    CHECK(!NITMOD_BuildPmoveReloadPolicy(NULL, 0, 0, 0, &fromFlags));
    CHECK(!memcmp(&fromFlags, &fromLocal, sizeof(fromFlags)));
    /* Clearing/replacing pmext cannot erase the per-call preferences. */
    move.nitmodReloadPreferenceFlags = CGF_AUTORELOAD | NITMOD_CGF_ALT_RELOAD;
    move.cmd.wbuttons = WBUTTON_ATTACK2;
    memset(&ext, 0, sizeof(ext)); move.pmext = NULL;
    CHECK(NITMOD_BuildPmoveReloadPolicy(&move, 1, 0, 0, &fromPmove));
    CHECK(fromPmove.manualRequested && fromPmove.automaticAllowed);
    return 0;
}

int TestRecoveredWeaponReload( void ) {
    playerState_t state, expected;
    ammotable_t table[WP_NUM_WEAPONS];
    nitmodWeaponInventorySlots_t slots;
    nitmodWeaponOptions_t options;
    int weapon, a, b, reserve, i, move, side, capacity, mode, want;
    int akimbo[] = { WP_AKIMBO_COLT, WP_AKIMBO_LUGER, WP_AKIMBO_SILENCEDCOLT, WP_AKIMBO_SILENCEDLUGER };
    int sidearms[] = { WP_COLT, WP_LUGER, WP_COLT, WP_LUGER };
    int left[] = { WP_AKIMBO_COLT, WP_AKIMBO_LUGER, WP_AKIMBO_COLT, WP_AKIMBO_LUGER };
    CHECK(!TestStartInventory());
    CHECK(!TestReloadStates());
    CHECK(!TestWeaponChangeCommit());
    CHECK(!TestWeaponChangeRaise());
    CHECK(!TestScopeSwitchBoundaries());
    CHECK(!TestPistolSwitch());
    CHECK(!TestRifleGrenadeSwitch());
    CHECK(!TestDeploySwitch());
    CHECK(!TestReloadDuration());
    CHECK(!TestReloadFinish());
    CHECK(!TestReloadFeedback());
    CHECK(!TestReloadDecision());
    CHECK(!TestReloadInput());
    CHECK(!TestReloadPreferences());
    memset(table, 0, sizeof(table));
    for( weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon ) {
        if( !NITMOD_WeaponInventorySlots(weapon, &slots) ) continue;
        for( a = 0; a <= 16; ++a ) for( b = 0; b < 64; ++b ) for( mode = 0; mode < 2; ++mode ) {
            memset(&state, 0x25, sizeof(state));
            state.ammoclip[slots.clip] = a;
            expected = state;
            options.noMidclipReload = mode;
            if( weapon == WP_MOBILE_MG42 || weapon == WP_MOBILE_MG42_SET )
                want = !a || b >= 32;
            else want = !a || !mode;
            CHECK(NITMOD_MidclipReloadAllowed(&state, weapon, &options, (unsigned int)b) == want);
            CHECK(!memcmp(&state, &expected, sizeof(state)));
        }
    }
    memset(&state, 0, sizeof(state));
    options.noMidclipReload = 1;
    state.ammoclip[WP_MOBILE_MG42] = -1;
    expected = state;
    CHECK(!NITMOD_MidclipReloadAllowed(&state, WP_MOBILE_MG42_SET, &options, ~0u));
    CHECK(!NITMOD_MidclipReloadAllowed(NULL, WP_COLT, &options, 0));
    CHECK(!NITMOD_MidclipReloadAllowed(&state, WP_COLT, NULL, 0));
    CHECK(!NITMOD_MidclipReloadAllowed(&state, WP_NONE, &options, 0));
    CHECK(!NITMOD_MidclipReloadAllowed(&state, INT_MAX, &options, 0));
    CHECK(!memcmp(&state, &expected, sizeof(state)));
    state.ammoclip[WP_MOBILE_MG42] = INT_MAX;
    CHECK(NITMOD_MidclipReloadAllowed(&state, WP_MOBILE_MG42_SET, &options, ~0u));
    CHECK(!NITMOD_MidclipReloadAllowed(&state, WP_MOBILE_MG42_SET, &options, ~0x20u));
    /* Different capacities for weapon and clip alias catch incorrect indexing. */
    for( weapon = 0; weapon < WP_NUM_WEAPONS; ++weapon ) table[weapon].maxclip = 1 + weapon % 9;
    for( weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon ) {
        if( BG_IsAkimboWeapon(weapon) || !NITMOD_WeaponInventorySlots(weapon, &slots) ) continue;
        for( a = 0; a <= 16; ++a ) for( reserve = 0; reserve <= 16; ++reserve ) {
            memset(&state, 0x25, sizeof(state));
            state.ammo[slots.ammo] = reserve;
            state.ammoclip[slots.clip] = a;
            expected = state;
            capacity = table[weapon].maxclip;
            for( mode = 0; mode < 2; ++mode ) {
                want = reserve > 0 && (mode ? a < capacity : a == 0);
                CHECK(NITMOD_ReloadInventoryReady(&state, weapon, (nitmodReloadRequest_t)mode,
                    table, WP_NUM_WEAPONS) == want);
                CHECK(!memcmp(&state, &expected, sizeof(state)));
            }
            /* Independent closed-form expectation, including overfull clips. */
            expected.ammoclip[slots.clip] = a + reserve < capacity ? a + reserve : capacity;
            expected.ammo[slots.ammo] = reserve + a - expected.ammoclip[slots.clip];
            CHECK(NITMOD_ReloadWeaponClips(&state, weapon, table, WP_NUM_WEAPONS));
            CHECK(!memcmp(&state, &expected, sizeof(state)));
        }
    }
    for( i = 0; i < 4; ++i ) for( a = 0; a <= 8; ++a )
    for( b = 0; b <= 8; ++b ) for( reserve = 0; reserve <= 16; ++reserve ) {
        memset(&state, 0x25, sizeof(state));
        side = sidearms[i];
        state.ammo[side] = reserve;
        state.ammoclip[left[i]] = a;
        state.ammoclip[side] = b;
        expected = state;
        capacity = table[akimbo[i]].maxclip;
        for( mode = 0; mode < 2; ++mode ) {
            want = reserve > 0 && (mode ? (a < capacity || b < table[side].maxclip) : (!a && !b));
            CHECK(NITMOD_ReloadInventoryReady(&state, akimbo[i], (nitmodReloadRequest_t)mode,
                table, WP_NUM_WEAPONS) == want);
            CHECK(!memcmp(&state, &expected, sizeof(state)));
        }
        move = a + reserve < capacity ? reserve : capacity - a;
        expected.ammoclip[left[i]] += move;
        expected.ammo[side] -= move;
        capacity = table[side].maxclip;
        move = b + expected.ammo[side] < capacity ? expected.ammo[side] : capacity - b;
        expected.ammoclip[side] += move;
        expected.ammo[side] -= move;
        CHECK(NITMOD_ReloadWeaponClips(&state, akimbo[i], table, WP_NUM_WEAPONS));
        CHECK(!memcmp(&state, &expected, sizeof(state)));
    }
    memset(&state, 0, sizeof(state));
    state.ammo[WP_COLT] = 10;
    table[WP_COLT].maxclip = -1; /* Second hand fails after first staged a transfer. */
    expected = state;
    CHECK(!NITMOD_ReloadInventoryReady(&state, WP_AKIMBO_COLT, NITMOD_RELOAD_MANUAL, table, WP_NUM_WEAPONS));
    CHECK(!NITMOD_ReloadWeaponClips(&state, WP_AKIMBO_COLT, table, WP_NUM_WEAPONS));
    CHECK(!memcmp(&state, &expected, sizeof(state)));
    table[WP_COLT].maxclip = 0;
    state.ammo[WP_COLT] = INT_MAX;
    state.ammoclip[WP_COLT] = 1;
    expected = state;
    CHECK(!NITMOD_ReloadInventoryReady(NULL, WP_COLT, NITMOD_RELOAD_MANUAL, table, WP_NUM_WEAPONS));
    CHECK(!NITMOD_ReloadInventoryReady(&state, WP_COLT, NITMOD_RELOAD_MANUAL, NULL, WP_NUM_WEAPONS));
    CHECK(!NITMOD_ReloadInventoryReady(&state, WP_COLT, NITMOD_RELOAD_MANUAL, table, WP_COLT));
    CHECK(!NITMOD_ReloadInventoryReady(&state, WP_COLT, NITMOD_RELOAD_MANUAL, table, -1));
    CHECK(!NITMOD_ReloadInventoryReady(&state, WP_NONE, NITMOD_RELOAD_MANUAL, table, WP_NUM_WEAPONS));
    CHECK(!NITMOD_ReloadInventoryReady(&state, WP_COLT, (nitmodReloadRequest_t)-1, table, WP_NUM_WEAPONS));
    CHECK(!NITMOD_ReloadInventoryReady(&state, WP_COLT, (nitmodReloadRequest_t)2, table, WP_NUM_WEAPONS));
    CHECK(!NITMOD_ReloadWeaponClips(&state, WP_COLT, table, WP_NUM_WEAPONS));
    CHECK(!memcmp(&state, &expected, sizeof(state)));
    state.ammoclip[WP_COLT] = 0;
    table[WP_COLT].maxclip = INT_MAX;
    CHECK(NITMOD_ReloadWeaponClips(&state, WP_COLT, table, WP_NUM_WEAPONS));
    CHECK(state.ammo[WP_COLT] == 0 && state.ammoclip[WP_COLT] == INT_MAX);
    expected = state;
    CHECK(!NITMOD_ReloadWeaponClips(NULL, WP_COLT, table, WP_NUM_WEAPONS));
    CHECK(!NITMOD_ReloadWeaponClips(&state, WP_COLT, NULL, WP_NUM_WEAPONS));
    CHECK(!NITMOD_ReloadWeaponClips(&state, WP_COLT, table, WP_COLT));
    CHECK(!NITMOD_ReloadWeaponClips(&state, WP_COLT, table, -1));
    CHECK(!NITMOD_ReloadWeaponClips(&state, WP_NONE, table, WP_NUM_WEAPONS));
    CHECK(!NITMOD_ReloadWeaponClips(&state, INT_MAX, table, WP_NUM_WEAPONS));
    CHECK(!memcmp(&state, &expected, sizeof(state)));
    state.ammo[WP_COLT] = -1;
    expected = state;
    CHECK(!NITMOD_ReloadInventoryReady(&state, WP_COLT, NITMOD_RELOAD_AUTOMATIC, table, WP_NUM_WEAPONS));
    CHECK(!NITMOD_ReloadWeaponClips(&state, WP_COLT, table, WP_NUM_WEAPONS));
    CHECK(!memcmp(&state, &expected, sizeof(state)));
    state.ammo[WP_COLT] = 1;
    state.ammoclip[WP_COLT] = -1;
    expected = state;
    CHECK(!NITMOD_ReloadInventoryReady(&state, WP_COLT, NITMOD_RELOAD_MANUAL, table, WP_NUM_WEAPONS));
    CHECK(!NITMOD_ReloadWeaponClips(&state, WP_COLT, table, WP_NUM_WEAPONS));
    CHECK(!memcmp(&state, &expected, sizeof(state)));
    return 0;
}
