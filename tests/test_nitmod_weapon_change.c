#include "nitmod_weapon_reload.h"
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#define CHECK(x) do { if(!(x)) { fprintf(stderr, "weapon change check %d\n", __LINE__); return 1; } } while(0)
static pmove_t *pm;
static struct { vec3_t forward, right; } pml;
static int bodyCalls, bodyEvent, bodyWeaponState, conditionCalls, conditionWeapon, badBoundary;
static animModelInfo_t model;
int BG_AnimScriptEvent(playerState_t *state, animModelInfo_t *info,
    scriptAnimEventTypes_t event, qboolean isContinue, qboolean force) {
    int reloadEvent = event == ANIM_ET_RELOAD || event == ANIM_ET_RELOADPRONE;
    if(state != pm->ps || info != &model || isContinue || force != (reloadEvent ? qtrue : qfalse) ||
        (reloadEvent && state->weaponstate != WEAPON_READY && state->weaponstate != WEAPON_FIRING &&
         state->weaponstate != WEAPON_FIRINGALT)) badBoundary = 1;
    bodyWeaponState = state->weaponstate;
    ++bodyCalls; bodyEvent = event;
    return -1; /* Missing model script must not cancel timing/state changes. */
}
void BG_UpdateConditionValue(int client, int condition, int value, qboolean convert) {
    if(client != pm->ps->clientNum || condition != ANIM_COND_WEAPON || !convert) badBoundary = 1;
    ++conditionCalls; conditionWeapon = value;
}
/* Actual product function bodies, including native clip transfer and
 * first-person animation gates. Only body-script/condition services doubled. */
#include "nitmod_weapon_change_bodies.h"

/* Independent transfer oracle. Capacity is keyed by weapon, inventory slots
 * come from the real native item table (also checked against original data). */
static void ExpectNativeTransfer(playerState_t *state, int weapon) {
    int ammo = BG_FindAmmoForWeapon(weapon), clip = BG_FindClipForWeapon(weapon);
    int transfer = GetAmmoTableData(weapon)->maxclip - state->ammoclip[clip];
    if(state->ammo[ammo] < transfer) transfer = state->ammo[ammo];
    state->ammo[ammo] -= transfer;
    state->ammoclip[clip] += transfer;
}

/* Metamorphic check: leaning must not change any reload result for mapped
 * identities, including paths still rejected by native inventory policy. */
static int TestLeaningReload(void) {
    static const int phases[] = { WEAPON_READY, WEAPON_FIRING, WEAPON_FIRINGALT };
    pmove_t move;
    pmoveExt_t ext, initialExt, expectedExt;
    playerState_t state, initial, expected;
    bg_character_t character;
    int skills[SK_NUM_SKILLS];
    int weapon, phase, inventory, entry, prone, lean, count = 0, started = 0;
    int expectedBody, expectedEvent, expectedPhase;
    pm = &move;
    for(weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon) {
        if(!NITMOD_ReloadWeaponEligible(weapon)) continue;
        for(phase = 0; phase < 3; ++phase) for(inventory = 0; inventory < 3; ++inventory)
        for(entry = 0; entry < 3; ++entry) for(prone = 0; prone < 2; ++prone) {
            memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
            memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
            memset(skills, 0, sizeof(skills));
            move.ps = &state; move.pmext = &ext; move.character = &character;
            move.skill = skills; character.animModelInfo = &model;
            move.cmd.weapon = weapon;
            move.cmd.wbuttons = entry == 1 ? WBUTTON_RELOAD : 0;
            ext.bAutoReload = qtrue;
            state.weapon = weapon; state.weaponstate = phases[phase];
            state.eFlags = prone ? EF_PRONE : 0;
            state.weapAnim = 123;
            state.ammo[BG_FindAmmoForWeapon(weapon)] = inventory == 1 ? 0 : 9;
            if(inventory == 2)
                state.ammoclip[BG_FindAmmoForWeapon(weapon)] = GetAmmoTableData(weapon)->maxclip;
            initial = state; initialExt = ext;
            bodyCalls = bodyEvent = bodyWeaponState = conditionCalls = badBoundary = 0;
            if(!entry) PM_BeginWeaponReload(weapon); else PM_CheckForReload(weapon);
            expected = state; expectedExt = ext;
            expectedBody = bodyCalls; expectedEvent = bodyEvent; expectedPhase = bodyWeaponState;
            CHECK(!badBoundary && !conditionCalls);
            if(state.weaponstate == WEAPON_RELOADING) ++started;
            for(lean = -1; lean <= 1; lean += 2) {
                state = initial; ext = initialExt; state.leanf = (float)(lean * 28);
                expected.leanf = state.leanf;
                bodyCalls = bodyEvent = bodyWeaponState = conditionCalls = badBoundary = 0;
                if(!entry) PM_BeginWeaponReload(weapon); else PM_CheckForReload(weapon);
                CHECK(!memcmp(&state, &expected, sizeof(state)));
                CHECK(!memcmp(&ext, &expectedExt, sizeof(ext)));
                CHECK(bodyCalls == expectedBody && bodyEvent == expectedEvent && bodyWeaponState == expectedPhase);
                CHECK(!badBoundary && !conditionCalls);
                ++count;
            }
        }
    }
    CHECK(count == 4212 && started > 0);
    return 0;
}

static int TestAkimboReloadRequests(void) {
    static const int weapons[] = { WP_AKIMBO_LUGER, WP_AKIMBO_COLT,
        WP_AKIMBO_SILENCEDLUGER, WP_AKIMBO_SILENCEDCOLT };
    static const int phases[] = { WEAPON_READY, WEAPON_FIRING, WEAPON_FIRINGALT };
    pmove_t move;
    pmoveExt_t ext;
    playerState_t state, before, expected;
    bg_character_t character;
    int skills[SK_NUM_SKILLS];
    int w, mainCase, sideCase, reserve, manual, phase, lean, side, mainClip, sideClip;
    int capacity, sideCapacity, allowed, count = 0;
    pm = &move;
    for(w = 0; w < 4; ++w) for(mainCase = 0; mainCase < 3; ++mainCase)
    for(sideCase = 0; sideCase < 3; ++sideCase) for(reserve = 0; reserve < 3; ++reserve)
    for(manual = 0; manual < 2; ++manual) for(phase = 0; phase < 3; ++phase)
    for(lean = 0; lean < 2; ++lean) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        memset(skills, 0, sizeof(skills));
        move.ps = &state; move.pmext = &ext; move.character = &character;
        move.skill = skills; character.animModelInfo = &model;
        move.cmd.weapon = weapons[w]; move.cmd.wbuttons = manual ? WBUTTON_RELOAD : 0;
        ext.bAutoReload = qtrue;
        state.weapon = weapons[w]; state.weaponstate = phases[phase];
        state.leanf = lean ? -28.0f : 0.0f;
        state.weapAnim = 123;
        side = w == 0 || w == 2 ? WP_LUGER : WP_COLT;
        mainClip = BG_FindClipForWeapon(weapons[w]); sideClip = BG_FindClipForWeapon(side);
        capacity = GetAmmoTableData(weapons[w])->maxclip;
        sideCapacity = GetAmmoTableData(sideClip)->maxclip;
        state.ammoclip[mainClip] = mainCase == 2 ? capacity : mainCase;
        state.ammoclip[sideClip] = sideCase == 2 ? sideCapacity : sideCase;
        state.ammo[BG_FindAmmoForWeapon(weapons[w])] = reserve == 2 ? 30 : reserve;
        allowed = reserve && (manual ? mainCase != 2 || sideCase != 2 : !mainCase && !sideCase);
        before = state;
        bodyCalls = conditionCalls = badBoundary = 0;
        PM_CheckForReload(weapons[w]);
        if(!allowed) {
            CHECK(!memcmp(&state, &before, sizeof(state)));
            CHECK(!bodyCalls && !conditionCalls && !badBoundary);
        } else {
            CHECK(state.weaponstate == WEAPON_RELOADING);
            CHECK(state.weaponTime == GetAmmoTableData(weapons[w])->reloadTime);
            CHECK(state.eventSequence == 1 && state.events[0] == EV_FILL_CLIP);
            CHECK(bodyCalls == 1 && !conditionCalls && !badBoundary);
            CHECK(!memcmp(state.ammo, before.ammo, sizeof(state.ammo)));
            CHECK(!memcmp(state.ammoclip, before.ammoclip, sizeof(state.ammoclip)));
            expected = state;
            ExpectNativeTransfer(&expected, weapons[w]); ExpectNativeTransfer(&expected, side);
            expected.weaponstate = WEAPON_READY;
            expected.weapAnim = ((state.weapAnim ^ ANIM_TOGGLEBIT) & ANIM_TOGGLEBIT) | WEAP_IDLE1;
            PM_FinishWeaponReload();
            CHECK(!memcmp(&state, &expected, sizeof(state)));
            CHECK(bodyCalls == 1 && !conditionCalls && !badBoundary);
        }
        ++count;
    }
    CHECK(count == 1296);
    return 0;
}

static int TestAlternateReloadInput(void) {
    static const int phases[] = { WEAPON_READY, WEAPON_FIRINGALT, WEAPON_RELOADING };
    pmove_t move;
    pmoveExt_t ext, initialExt, expectedExt;
    playerState_t state, initial, expected;
    bg_character_t character;
    nitmodWeaponInventorySlots_t slots;
    int skills[SK_NUM_SKILLS];
    int weapon, enabled, keys, inventory, phase, timer, requested, count = 0;
    int expectedBody, expectedEvent, expectedPhase, expectedCondition, expectedWeapon;
    pm = &move;
    CHECK(!NITMOD_ManualReloadRequested(NULL, ~0u));
    for(weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon) {
        if(!NITMOD_WeaponInventorySlots(weapon, &slots)) continue;
        for(enabled = 0; enabled < 2; ++enabled) for(keys = 0; keys < 4; ++keys)
        for(inventory = 0; inventory < 3; ++inventory) for(phase = 0; phase < 3; ++phase)
        for(timer = 0; timer < 2; ++timer) {
            memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
            memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
            memset(skills, 0, sizeof(skills));
            move.ps = &state; move.pmext = &ext; move.character = &character;
            move.skill = skills; character.animModelInfo = &model;
            move.cmd.weapon = weapon; move.cmd.buttons = BUTTON_ATTACK;
            state.weapon = weapon; state.weaponstate = phases[phase];
            state.weaponTime = timer ? 5 : 0; state.weapAnim = 123;
            memset(state.weapons, 0xff, sizeof(state.weapons));
            state.ammo[BG_FindAmmoForWeapon(weapon)] = inventory == 1 ? 0 : 9;
            state.ammoclip[BG_FindClipForWeapon(weapon)] = inventory == 2 ? GetAmmoTableData(weapon)->maxclip : 1;
            initial = state; initialExt = ext;
            /* Independent input oracle: key bit 1 is reload, bit 2 is alt.
             * Run ordinary reload as the reference, then the actual input. */
            requested = (keys & 1) != 0 || (enabled && (keys & 2) != 0);
            move.cmd.wbuttons = requested ? WBUTTON_RELOAD : 0;
            bodyCalls = bodyEvent = bodyWeaponState = conditionCalls = conditionWeapon = badBoundary = 0;
            PM_CheckForReload(weapon);
            expected = state; expectedExt = ext;
            expectedBody = bodyCalls; expectedEvent = bodyEvent; expectedPhase = bodyWeaponState;
            expectedCondition = conditionCalls; expectedWeapon = conditionWeapon;
            CHECK(!badBoundary);
            state = initial; ext = initialExt;
            move.nitmodReloadPreferenceFlags = 0x80000000u | (enabled ? NITMOD_CGF_ALT_RELOAD : 0);
            move.cmd.wbuttons = ((keys & 1) ? WBUTTON_RELOAD : 0) | ((keys & 2) ? WBUTTON_ATTACK2 : 0);
            CHECK(NITMOD_ManualReloadRequested(&move.cmd, move.nitmodReloadPreferenceFlags) == requested);
            bodyCalls = bodyEvent = bodyWeaponState = conditionCalls = conditionWeapon = badBoundary = 0;
            PM_CheckForReload(weapon);
            CHECK(!memcmp(&state, &expected, sizeof(state)));
            CHECK(!memcmp(&ext, &expectedExt, sizeof(ext)));
            CHECK(bodyCalls == expectedBody && bodyEvent == expectedEvent && bodyWeaponState == expectedPhase);
            CHECK(conditionCalls == expectedCondition && conditionWeapon == expectedWeapon && !badBoundary);
            ++count;
        }
    }
    CHECK(count == 6336);
    return 0;
}

static int TestTransitionCycles(void) {
    static const int weapons[] = { WP_LUGER, WP_AKIMBO_LUGER, WP_AKIMBO_COLT,
        WP_AKIMBO_SILENCEDLUGER, WP_AKIMBO_SILENCEDCOLT,
        WP_GARAND_SCOPE, WP_K43_SCOPE, WP_FG42SCOPE };
    static const int bases[] = { WP_GARAND, WP_K43, WP_FG42 };
    pmove_t move;
    pmoveExt_t ext;
    playerState_t state, before, expected;
    bg_character_t character;
    int skills[SK_NUM_SKILLS];
    int w, alt, lean, reserve, bodyBefore, sequence, side, count = 0;
    pm = &move;
    for(w = 0; w < 8; ++w) for(alt = 0; alt < 2; ++alt)
    for(lean = 0; lean < 2; ++lean) for(reserve = 0; reserve < 2; ++reserve) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        memset(skills, 0, sizeof(skills));
        move.ps = &state; move.pmext = &ext; move.character = &character;
        move.skill = skills; character.animModelInfo = &model;
        move.cmd.weapon = weapons[w];
        move.cmd.wbuttons = alt ? WBUTTON_ATTACK2 : WBUTTON_RELOAD;
        move.nitmodReloadPreferenceFlags = alt ? NITMOD_CGF_ALT_RELOAD : 0;
        state.weapon = weapons[w]; state.weaponstate = WEAPON_READY;
        state.leanf = lean ? 28.0f : 0.0f;
        state.weapAnim = 123;
        memset(state.weapons, 0xff, sizeof(state.weapons));
        state.ammo[BG_FindAmmoForWeapon(weapons[w])] = reserve ? 100 : 1;
        state.weaponDelay = 1;
        before = state; bodyCalls = conditionCalls = badBoundary = 0;
        CHECK(PM_ProcessWeaponTransitions() == 1);
        CHECK(!memcmp(&state, &before, sizeof(state)) && !bodyCalls && !conditionCalls);
        state.weaponDelay = 0;
        CHECK(PM_ProcessWeaponTransitions() == 1);
        if(w >= 5) {
            CHECK(state.weaponstate == WEAPON_DROPPING_TORELOAD);
            CHECK(state.nextWeapon == bases[w - 5]);
            before = state;
            CHECK(PM_ProcessWeaponTransitions() == 1);
            CHECK(!memcmp(&state, &before, sizeof(state)));
            state.weaponTime = 0; /* Caller has advanced the timer. */
            CHECK(PM_ProcessWeaponTransitions() == 1);
            CHECK(state.weaponstate == WEAPON_RAISING_TORELOAD && state.weapon == bases[w - 5]);
            move.cmd.weapon = state.weapon;
            before = state;
            CHECK(PM_ProcessWeaponTransitions() == 1);
            CHECK(!memcmp(&state, &before, sizeof(state)));
            state.weaponTime = 0;
            CHECK(PM_ProcessWeaponTransitions() == 1);
        }
        CHECK(state.weaponstate == WEAPON_RELOADING && state.weaponTime > 0);
        sequence = state.eventSequence; bodyBefore = bodyCalls;
        CHECK(state.events[(sequence - 1) & (MAX_EVENTS - 1)] == EV_FILL_CLIP);
        before = state;
        /* A held reload key must neither restart reload nor permit a switch. */
        CHECK(PM_ProcessWeaponTransitions() == 1);
        PM_BeginWeaponChange(state.weapon, WP_MP40, qfalse);
        CHECK(!memcmp(&state, &before, sizeof(state)));
        CHECK(bodyCalls == bodyBefore && !badBoundary);
        state.weaponTime = 0;
        expected = state;
        ExpectNativeTransfer(&expected, state.weapon);
        side = w == 1 || w == 3 ? WP_LUGER : w == 2 || w == 4 ? WP_COLT : WP_NONE;
        if(side) ExpectNativeTransfer(&expected, side);
        expected.weaponstate = WEAPON_READY;
        expected.weapAnim = ((state.weapAnim ^ ANIM_TOGGLEBIT) & ANIM_TOGGLEBIT) | WEAP_IDLE1;
        CHECK(PM_ProcessWeaponTransitions() == 0);
        CHECK(!memcmp(&state, &expected, sizeof(state)));
        CHECK(state.eventSequence == sequence && bodyCalls == bodyBefore && !badBoundary);
        before = state;
        CHECK(PM_ProcessWeaponTransitions() == 0);
        CHECK(!memcmp(&state, &before, sizeof(state)));
        CHECK(bodyCalls == bodyBefore && !badBoundary);
        ++count;
    }
    CHECK(count == 64);
    return 0;
}

static int TestTransitionTimerBoundaries(void) {
    pmove_t move;
    pmoveExt_t ext, extBefore;
    playerState_t state, expected;
    nitmodWeaponInventorySlots_t slots;
    int weapon, time, delay, gate, alt, side, idle, count = 0;
    pm = &move;
    for(weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon) {
        if(!NITMOD_WeaponInventorySlots(weapon, &slots)) continue;
        for(time = -1; time <= 1; ++time) for(delay = -1; delay <= 1; ++delay)
        for(gate = 0; gate < 4; ++gate) for(alt = 0; alt < 2; ++alt) {
            memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
            memset(&state, 0, sizeof(state));
            move.ps = &state; move.pmext = &ext;
            move.cmd.weapon = gate == 3 ? WP_NONE : weapon;
            move.cmd.wbuttons = alt ? WBUTTON_ATTACK2 : WBUTTON_RELOAD;
            move.nitmodReloadPreferenceFlags = alt ? NITMOD_CGF_ALT_RELOAD : 0;
            state.weapon = weapon; state.weaponstate = WEAPON_RELOADING;
            state.weaponTime = time; state.weaponDelay = delay;
            state.pm_type = gate == 1 ? PM_DEAD : PM_NORMAL;
            state.weapAnim = ANIM_TOGGLEBIT | WEAP_RELOAD1;
            ext.weapAnimTimer = gate == 2 ? 1 : 0;
            state.ammo[BG_FindAmmoForWeapon(weapon)] = 9;
            /* Existing ring entries must survive; completion emits no event. */
            state.eventSequence = MAX_EVENTS + 3;
            state.events[0] = EV_FILL_CLIP; state.eventParms[0] = 47;
            expected = state; extBefore = ext;
            bodyCalls = conditionCalls = badBoundary = 0;
            if(time > 0 || delay > 0) {
                CHECK(PM_ProcessWeaponTransitions() == 1);
            } else {
                ExpectNativeTransfer(&expected, weapon);
                side = WP_NONE;
                if(weapon == WP_AKIMBO_LUGER || weapon == WP_AKIMBO_SILENCEDLUGER) side = WP_LUGER;
                if(weapon == WP_AKIMBO_COLT || weapon == WP_AKIMBO_SILENCEDCOLT) side = WP_COLT;
                if(side) ExpectNativeTransfer(&expected, side);
                expected.weaponstate = WEAPON_READY;
                idle = weapon == WP_GPG40 || weapon == WP_M7 || weapon == WP_SATCHEL_DET ||
                    weapon == WP_MORTAR_SET || weapon == WP_MEDIC_ADRENALINE || weapon == WP_MOBILE_MG42_SET
                    ? WEAP_IDLE2 : WEAP_IDLE1;
                if(!gate) expected.weapAnim = idle;
                CHECK(PM_ProcessWeaponTransitions() == 0);
            }
            CHECK(!memcmp(&state, &expected, sizeof(state)));
            CHECK(!memcmp(&ext, &extBefore, sizeof(ext)));
            CHECK(!bodyCalls && !conditionCalls && !badBoundary);
            ++count;
        }
    }
    CHECK(count == 3168);
    return 0;
}

static int TestReloadAnimationSelection(void) {
    static const int levels[] = { -1, 0, 1, 2, 4 };
    static const int enabled[] = { 0, 1, -1, INT_MAX };
    pmove_t move;
    playerState_t state, before;
    int skills[SK_NUM_SKILLS];
    int weapon, i, fast, expected, count = 0;
    memset(&move, 0, sizeof(move)); memset(&state, 0x25, sizeof(state));
    memset(skills, 0, sizeof(skills));
    move.ps = &state; move.skill = skills; pm = &move; before = state;
    for(weapon = -1; weapon <= WP_NUM_WEAPONS; ++weapon) {
        fast = weapon == WP_LUGER || weapon == WP_COLT || weapon == WP_MP40 ||
            weapon == WP_THOMPSON || weapon == WP_STEN || weapon == WP_SILENCER ||
            weapon == WP_SILENCED_COLT || weapon == WP_FG42;
        for(i = 0; i < 5; ++i) {
            skills[SK_LIGHT_WEAPONS] = levels[i];
            expected = weapon == WP_GPG40 || weapon == WP_M7 ? WEAP_RELOAD2 :
                weapon == WP_MOBILE_MG42_SET ? WEAP_RELOAD3 :
                fast && levels[i] >= 2 ? WEAP_RELOAD2 : WEAP_RELOAD1;
            CHECK(PM_ReloadAnimForWeapon(weapon) == expected);
            CHECK(!memcmp(&state, &before, sizeof(state)));
            ++count;
        }
        for(i = 0; i < 4; ++i) {
            expected = weapon == WP_GPG40 || weapon == WP_M7 ? WEAP_RELOAD2 :
                weapon == WP_MOBILE_MG42_SET ? WEAP_RELOAD3 :
                fast && enabled[i] ? WEAP_RELOAD2 : WEAP_RELOAD1;
            CHECK(NITMOD_ReloadAnimation(weapon, enabled[i]) == expected);
            ++count;
        }
    }
    CHECK(count == (WP_NUM_WEAPONS + 2) * 9);
    return 0;
}

static int TestReloadTimerExtremes(void) {
    static const int values[] = { INT_MIN, -1, 0, 1, 20, 1000, INT_MAX };
    pmove_t move;
    pmoveExt_t ext, extBefore;
    playerState_t state, expected;
    bg_character_t character;
    int skills[SK_NUM_SKILLS];
    int t, d, phase, fast, duration, saved, count = 0;
    int64_t scaled;
    uint32_t sumBits;
    pm = &move;
    for(t = 0; t < 7; ++t) for(d = 0; d < 7; ++d)
    for(phase = 0; phase < 3; ++phase) for(fast = 0; fast < 2; ++fast) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        memset(skills, 0, sizeof(skills));
        move.ps = &state; move.pmext = &ext; move.character = &character;
        move.skill = skills; character.animModelInfo = &model;
        move.cmd.weapon = WP_LUGER; skills[SK_LIGHT_WEAPONS] = fast ? 2 : 0;
        state.weapon = WP_LUGER; state.weaponTime = values[t];
        state.weaponstate = phase == 0 ? WEAPON_READY : phase == 1 ? WEAPON_FIRING : WEAPON_FIRINGALT;
        state.ammo[WP_LUGER] = 9;
        expected = state; extBefore = ext;
        /* Exact integer oracle, independent of the product scaling helper. */
        scaled = (int64_t)values[d] * 5452595;
        duration = fast ? (int)(scaled / 8388608) : values[d];
        expected.weaponTime = values[t] < duration ? duration : values[t];
        if(phase == 0) {
            /* Independent modulo-32 oracle, with only in-range signed casts. */
            sumBits = (uint32_t)values[t] + (uint32_t)duration;
            expected.weaponTime = sumBits <= INT32_MAX ? (int)sumBits : -1 - (int)(UINT32_MAX - sumBits);
            CHECK(NITMOD_AddWeaponTime32(values[t], duration) == expected.weaponTime);
        }
        expected.weaponstate = WEAPON_RELOADING;
        expected.weapAnim = ANIM_TOGGLEBIT | (fast ? WEAP_RELOAD2 : WEAP_RELOAD1);
        expected.eventSequence = 1; expected.events[0] = EV_FILL_CLIP;
        saved = GetAmmoTableData(WP_LUGER)->reloadTime;
        GetAmmoTableData(WP_LUGER)->reloadTime = values[d];
        bodyCalls = conditionCalls = badBoundary = 0;
        PM_BeginWeaponReload(WP_LUGER);
        GetAmmoTableData(WP_LUGER)->reloadTime = saved;
        CHECK(!memcmp(&state, &expected, sizeof(state)));
        CHECK(!memcmp(&ext, &extBefore, sizeof(ext)));
        CHECK(bodyCalls == 1 && !conditionCalls && !badBoundary);
        ++count;
    }
    CHECK(count == 294);
    return 0;
}

static int TestNativeAmmoConsumption(void) {
    static const int counts[] = { -1, 0, 1, 2 };
    static const int amounts[] = { 0, 1, 3 };
    pmove_t move;
    pmoveExt_t ext, extBefore;
    playerState_t state, expected;
    nitmodWeaponInventorySlots_t slots;
    int weapon, main, sideIndex, noClips, amount, side, clip, selected, count = 0;
    pm = &move;
    for(weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon) {
        if(!NITMOD_WeaponInventorySlots(weapon, &slots)) continue;
        side = WP_NONE;
        if(weapon == WP_AKIMBO_LUGER || weapon == WP_AKIMBO_SILENCEDLUGER) side = WP_LUGER;
        if(weapon == WP_AKIMBO_COLT || weapon == WP_AKIMBO_SILENCEDCOLT) side = WP_COLT;
        for(main = 0; main < 4; ++main) for(sideIndex = 0; sideIndex < 4; ++sideIndex)
        for(noClips = 0; noClips < 2; ++noClips) for(amount = 0; amount < 3; ++amount) {
            memset(&move, 0, sizeof(move)); memset(&ext, 0x25, sizeof(ext));
            memset(&state, 0x25, sizeof(state));
            move.ps = &state; move.pmext = &ext; move.noWeapClips = noClips;
            state.weapon = weapon;
            clip = BG_FindClipForWeapon(weapon);
            state.ammoclip[clip] = counts[main];
            if(side) state.ammoclip[side] = counts[sideIndex];
            state.ammo[BG_FindAmmoForWeapon(weapon)] = 9;
            selected = clip;
            /* Independent zero-first/parity hand oracle; do not call the
             * product firing-sequence predicate to compute expectations. */
            if(side && (!counts[main] || (counts[sideIndex] &&
                (((unsigned int)counts[main] + (unsigned int)counts[sideIndex]) & 1u)))) selected = side;
            expected = state; extBefore = ext;
            bodyCalls = conditionCalls = badBoundary = 0;
            CHECK(PM_WeaponAmmoAvailable(weapon) == (noClips ? 9 : state.ammoclip[selected]));
            CHECK(!memcmp(&state, &expected, sizeof(state)));
            if(noClips) expected.ammo[BG_FindAmmoForWeapon(weapon)] -= amounts[amount];
            else expected.ammoclip[selected] -= amounts[amount];
            PM_WeaponUseAmmo(weapon, amounts[amount]);
            CHECK(!memcmp(&state, &expected, sizeof(state)));
            CHECK(!memcmp(&ext, &extBefore, sizeof(ext)));
            CHECK(!bodyCalls && !conditionCalls && !badBoundary);
            ++count;
        }
    }
    CHECK(count == 4224);
    return 0;
}

static int TestAkimboShootReloadCycles(void) {
    static const int weapons[] = { WP_AKIMBO_LUGER, WP_AKIMBO_COLT,
        WP_AKIMBO_SILENCEDLUGER, WP_AKIMBO_SILENCEDCOLT };
    static const int reserves[] = { 0, 1, 30 };
    pmove_t move;
    pmoveExt_t ext, extBefore;
    playerState_t state, expected;
    bg_character_t character;
    int skills[SK_NUM_SKILLS];
    int w, main, other, reserve, alt, round, side, clip, selected, total, shots, count = 0;
    pm = &move;
    for(w = 0; w < 4; ++w) for(main = 0; main <= 8; ++main)
    for(other = 0; other <= 8; ++other) for(reserve = 0; reserve < 3; ++reserve)
    for(alt = 0; alt < 2; ++alt) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        memset(skills, 0, sizeof(skills));
        move.ps = &state; move.pmext = &ext; move.character = &character;
        move.skill = skills; character.animModelInfo = &model;
        move.cmd.weapon = weapons[w];
        move.cmd.wbuttons = alt ? WBUTTON_ATTACK2 : WBUTTON_RELOAD;
        move.nitmodReloadPreferenceFlags = alt ? NITMOD_CGF_ALT_RELOAD : 0;
        state.weapon = weapons[w]; state.weaponstate = WEAPON_FIRING;
        side = w == 0 || w == 2 ? WP_LUGER : WP_COLT;
        clip = BG_FindClipForWeapon(weapons[w]);
        state.ammoclip[clip] = main; state.ammoclip[side] = other;
        state.ammo[side] = reserves[reserve];
        extBefore = ext; total = main + other + reserves[reserve]; shots = 0;
        bodyCalls = conditionCalls = badBoundary = 0;
        for(round = 0; round < 2; ++round) {
            while(state.ammoclip[clip] || state.ammoclip[side]) {
                selected = !state.ammoclip[clip] ? side : !state.ammoclip[side] ? clip :
                    ((state.ammoclip[clip] + state.ammoclip[side]) & 1) ? side : clip;
                expected = state;
                CHECK(PM_WeaponAmmoAvailable(weapons[w]) == state.ammoclip[selected]);
                CHECK(!memcmp(&state, &expected, sizeof(state)));
                --expected.ammoclip[selected];
                PM_WeaponUseAmmo(weapons[w], 1);
                CHECK(!memcmp(&state, &expected, sizeof(state)));
                ++shots;
                CHECK(shots + state.ammo[side] + state.ammoclip[clip] + state.ammoclip[side] == total);
            }
            CHECK(PM_WeaponAmmoAvailable(weapons[w]) == 0);
            if(round) break;
            expected = state;
            if(!reserves[reserve]) {
                CHECK(PM_ProcessWeaponTransitions() == 0);
                CHECK(!memcmp(&state, &expected, sizeof(state)));
                CHECK(!bodyCalls && !state.eventSequence);
            } else {
                CHECK(PM_ProcessWeaponTransitions() == 1);
                CHECK(state.weaponstate == WEAPON_RELOADING && state.weaponTime > 0);
                CHECK(!memcmp(state.ammo, expected.ammo, sizeof(state.ammo)));
                CHECK(!memcmp(state.ammoclip, expected.ammoclip, sizeof(state.ammoclip)));
                expected = state;
                CHECK(PM_ProcessWeaponTransitions() == 1);
                CHECK(!memcmp(&state, &expected, sizeof(state)));
                state.weaponTime = 0; /* Model the caller's timer expiry. */
                expected = state;
                ExpectNativeTransfer(&expected, weapons[w]); ExpectNativeTransfer(&expected, side);
                expected.weaponstate = WEAPON_READY;
                expected.weapAnim = ((state.weapAnim ^ ANIM_TOGGLEBIT) & ANIM_TOGGLEBIT) | WEAP_IDLE1;
                CHECK(PM_ProcessWeaponTransitions() == 0);
                CHECK(!memcmp(&state, &expected, sizeof(state)));
                CHECK(bodyCalls == 1 && state.eventSequence == 1 && state.events[0] == EV_FILL_CLIP);
            }
        }
        CHECK(shots + state.ammo[side] == total);
        CHECK(!memcmp(&ext, &extBefore, sizeof(ext)) && !conditionCalls && !badBoundary);
        ++count;
    }
    CHECK(count == 1944);
    return 0;
}

static int TestOuterClipGate(void) {
    static const int weapons[] = { WP_LUGER, WP_COLT, WP_SILENCER, WP_SILENCED_COLT,
        WP_MP40, WP_THOMPSON, WP_STEN, WP_FG42, WP_AKIMBO_LUGER, WP_AKIMBO_COLT,
        WP_AKIMBO_SILENCEDLUGER, WP_AKIMBO_SILENCEDCOLT };
    static const int phases[] = { WEAPON_READY, WEAPON_FIRING, WEAPON_FIRINGALT };
    pmove_t move;
    pmoveExt_t ext, extBefore;
    playerState_t state, before;
    bg_character_t character;
    int skills[SK_NUM_SKILLS];
    int w, phase, fill, outer, side, sideFill, reserve, gate, total, count = 0, completed = 0;
    pm = &move;
    for(w = 0; w < 12; ++w) for(phase = 0; phase < 3; ++phase)
    for(fill = 0; fill < 3; ++fill) for(outer = 0; outer < 2; ++outer)
    for(sideFill = 0; sideFill < 3; ++sideFill) for(reserve = 0; reserve < 3; ++reserve)
    for(gate = 0; gate < 4; ++gate) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        memset(skills, 0, sizeof(skills));
        move.ps = &state; move.pmext = &ext; move.character = &character;
        move.skill = skills; character.animModelInfo = &model;
        move.cmd.weapon = gate == 3 ? WP_NONE : weapons[w]; move.cmd.wbuttons = WBUTTON_RELOAD;
        state.pm_type = gate == 1 ? PM_DEAD : PM_NORMAL;
        ext.weapAnimTimer = gate == 2 ? 1 : 0;
        state.weapon = weapons[w]; state.weaponstate = phases[phase];
        state.ammo[BG_FindAmmoForWeapon(weapons[w])] = reserve == 0 ? 1 : reserve == 1 ? 9 : 100;
        state.ammoclip[BG_FindClipForWeapon(weapons[w])] = fill ? GetAmmoTableData(weapons[w])->maxclip + fill - 1 : 1;
        side = w == 8 || w == 10 ? WP_LUGER : w == 9 || w == 11 ? WP_COLT : WP_NONE;
        if(side) state.ammoclip[side] = sideFill ? GetAmmoTableData(side)->maxclip + sideFill - 1 : 1;
        total = state.ammo[BG_FindAmmoForWeapon(weapons[w])] + state.ammoclip[BG_FindClipForWeapon(weapons[w])];
        if(side) total += state.ammoclip[side];
        before = state; extBefore = ext; bodyCalls = conditionCalls = badBoundary = 0;
        CHECK(NITMOD_ReloadUsesOuterClipGate(weapons[w]));
        if(outer) PM_CheckForReload(weapons[w]); else PM_BeginWeaponReload(weapons[w]);
        if(outer && fill && (!side || sideFill)) {
            CHECK(!memcmp(&state, &before, sizeof(state)) && !bodyCalls);
        } else {
            CHECK(state.weaponstate == WEAPON_RELOADING && state.weaponTime == GetAmmoTableData(weapons[w])->reloadTime);
            CHECK(bodyCalls == 1 && state.eventSequence == 1 && state.events[0] == EV_FILL_CLIP);
            CHECK(!memcmp(state.ammo, before.ammo, sizeof(state.ammo)));
            CHECK(!memcmp(state.ammoclip, before.ammoclip, sizeof(state.ammoclip)));
            before = state;
            CHECK(PM_ProcessWeaponTransitions() == 1);
            CHECK(!memcmp(&state, &before, sizeof(state)));
            state.weaponTime = 0;
            before = state;
            ExpectNativeTransfer(&before, weapons[w]);
            if(side) ExpectNativeTransfer(&before, side);
            before.weaponstate = WEAPON_READY;
            if(!gate) before.weapAnim = ((state.weapAnim ^ ANIM_TOGGLEBIT) & ANIM_TOGGLEBIT) | WEAP_IDLE1;
            CHECK(PM_ProcessWeaponTransitions() == 0);
            CHECK(!memcmp(&state, &before, sizeof(state)));
            CHECK(bodyCalls == 1 && state.eventSequence == 1);
            CHECK(total == state.ammo[BG_FindAmmoForWeapon(weapons[w])] +
                state.ammoclip[BG_FindClipForWeapon(weapons[w])] + (side ? state.ammoclip[side] : 0));
            ++completed;
        }
        CHECK(!memcmp(&ext, &extBefore, sizeof(ext)));
        CHECK(!conditionCalls && !badBoundary);
        ++count;
    }
    CHECK(!NITMOD_ReloadUsesOuterClipGate(WP_GARAND) && !NITMOD_ReloadUsesOuterClipGate(WP_K43));
    CHECK(!NITMOD_ReloadUsesOuterClipGate(-1) && !NITMOD_ReloadUsesOuterClipGate(INT_MAX));
    CHECK(count == 7776 && completed == 5472);
    return 0;
}

static int TestNativeReloadFinish(void) {
    pmove_t move;
    pmoveExt_t ext, extBefore;
    playerState_t state, expected;
    nitmodWeaponInventorySlots_t recoveredSlots;
    int weapon, reserve, clipCase, sideCase, gate, side, clip, capacity, idle, count = 0;
    pm = &move;
    for(weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon) {
        if(!NITMOD_WeaponInventorySlots(weapon, &recoveredSlots)) continue;
        side = WP_NONE;
        if(weapon == WP_AKIMBO_COLT || weapon == WP_AKIMBO_SILENCEDCOLT) side = WP_COLT;
        if(weapon == WP_AKIMBO_LUGER || weapon == WP_AKIMBO_SILENCEDLUGER) side = WP_LUGER;
        for(reserve = 0; reserve < 3; ++reserve) for(clipCase = 0; clipCase < 4; ++clipCase)
        for(sideCase = 0; sideCase < 3; ++sideCase) for(gate = 0; gate < 4; ++gate) {
            ++count;
            memset(&move, 0, sizeof(move)); memset(&ext, 0x25, sizeof(ext));
            memset(&state, 0x25, sizeof(state));
            memset(state.ammo, 0, sizeof(state.ammo)); memset(state.ammoclip, 0, sizeof(state.ammoclip));
            move.ps = &state; move.pmext = &ext;
            state.weapon = weapon; state.weaponstate = WEAPON_RELOADING;
            state.pm_type = gate == 1 ? PM_DEAD : PM_NORMAL;
            state.weaponTime = state.weaponDelay = 0;
            state.weapAnim = ANIM_TOGGLEBIT | WEAP_RELOAD1;
            ext.weapAnimTimer = gate == 2 ? 1 : 0;
            move.cmd.weapon = gate == 3 ? WP_NONE : weapon;
            state.ammo[BG_FindAmmoForWeapon(weapon)] = reserve == 2 ? 9 : reserve;
            clip = BG_FindClipForWeapon(weapon); capacity = GetAmmoTableData(weapon)->maxclip;
            state.ammoclip[clip] = clipCase < 2 ? clipCase : capacity + clipCase - 2;
            if(side) state.ammoclip[BG_FindClipForWeapon(side)] = sideCase < 2 ? sideCase : GetAmmoTableData(side)->maxclip;
            expected = state; extBefore = ext;
            ExpectNativeTransfer(&expected, weapon);
            if(side) ExpectNativeTransfer(&expected, side);
            expected.weaponstate = WEAPON_READY;
            idle = weapon == WP_GPG40 || weapon == WP_M7 || weapon == WP_SATCHEL_DET ||
                weapon == WP_MORTAR_SET || weapon == WP_MEDIC_ADRENALINE || weapon == WP_MOBILE_MG42_SET
                ? WEAP_IDLE2 : WEAP_IDLE1;
            if(!gate) expected.weapAnim = idle;
            bodyCalls = conditionCalls = badBoundary = 0;
            PM_FinishWeaponReload();
            CHECK(!memcmp(&state, &expected, sizeof(state)));
            CHECK(!memcmp(&ext, &extBefore, sizeof(ext)));
            CHECK(!bodyCalls && !conditionCalls && !badBoundary);
        }
    }
    CHECK(count == 6336);
    return 0;
}

static int TestFastReloadArithmetic(void) {
    static const int weapons[] = { WP_LUGER, WP_MP40, WP_COLT, WP_THOMPSON,
        WP_STEN, WP_SILENCER, WP_FG42, WP_SILENCED_COLT, WP_AKIMBO_LUGER, WP_FG42SCOPE };
    static const int values[] = { INT_MIN, -20, -1, 0, 20, 1000, 1500, INT_MAX };
    static const int levels[] = { 0, 1, 2, 4 };
    static const int phases[] = { WEAPON_READY, WEAPON_FIRING, WEAPON_FIRINGALT };
    pmove_t move;
    pmoveExt_t ext;
    playerState_t state, before;
    bg_character_t character;
    int skills[SK_NUM_SKILLS];
    int i, v, l, p, saved, fast, expected;
    int64_t quotient, remainder;
    pm = &move;
    for(v = 0; v < 8; ++v) {
        quotient = values[v] / 8388608; remainder = values[v] % 8388608;
        expected = (int)(quotient * 5452595 + (remainder * 5452595) / 8388608);
        CHECK(NITMOD_ScaleFastReloadDuration(values[v]) == expected);
    }
    CHECK(NITMOD_ScaleFastReloadDuration(20) == 12);
    CHECK(NITMOD_ScaleFastReloadDuration(1000) == 649);
    for(i = 0; i < 10; ++i) for(v = 1; v < 8; ++v)
    for(l = 0; l < 4; ++l) for(p = 0; p < 3; ++p) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        memset(skills, 0, sizeof(skills));
        move.ps = &state; move.pmext = &ext; move.character = &character; move.skill = skills;
        character.animModelInfo = &model; move.cmd.weapon = weapons[i];
        skills[SK_LIGHT_WEAPONS] = levels[l];
        state.weapon = weapons[i]; state.weaponstate = phases[p];
        state.ammo[BG_FindAmmoForWeapon(weapons[i])] = 9;
        before = state; bodyCalls = conditionCalls = badBoundary = 0;
        saved = GetAmmoTableData(weapons[i])->reloadTime;
        GetAmmoTableData(weapons[i])->reloadTime = values[v];
        PM_BeginWeaponReload(weapons[i]);
        GetAmmoTableData(weapons[i])->reloadTime = saved;
        fast = i < 8 && levels[l] >= 2;
        quotient = values[v] / 8388608; remainder = values[v] % 8388608;
        expected = fast ? (int)(quotient * 5452595 + (remainder * 5452595) / 8388608) : values[v];
        if(p != 0 && expected < 0) expected = 0;
        CHECK(state.weaponTime == expected && state.weaponstate == WEAPON_RELOADING);
        CHECK((state.weapAnim & ~ANIM_TOGGLEBIT) == (fast ? WEAP_RELOAD2 : WEAP_RELOAD1));
        CHECK(bodyCalls == 1 && !badBoundary && state.eventSequence == 1 && state.events[0] == EV_FILL_CLIP);
        CHECK(!memcmp(state.ammo, before.ammo, sizeof(state.ammo)));
        CHECK(!memcmp(state.ammoclip, before.ammoclip, sizeof(state.ammoclip)));
        /* Complete the same reload with the real transfer and idle path.
         * Restored timing fixture above does not affect magazine capacity. */
        state.weaponTime = 0;
        before = state;
        ExpectNativeTransfer(&before, weapons[i]);
        if(weapons[i] == WP_AKIMBO_LUGER) ExpectNativeTransfer(&before, WP_LUGER);
        before.weaponstate = WEAPON_READY;
        before.weapAnim = ((before.weapAnim & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT) | WEAP_IDLE1;
        bodyCalls = conditionCalls = badBoundary = 0;
        PM_FinishWeaponReload();
        CHECK(!memcmp(&state, &before, sizeof(state)));
        CHECK(!bodyCalls && !conditionCalls && !badBoundary);
    }
    return 0;
}

static int TestReloadBodySelection(void) {
    static const int weapons[] = { WP_GRENADE_LAUNCHER, WP_GRENADE_PINEAPPLE,
        WP_DYNAMITE, WP_SMOKE_BOMB, WP_TRIPMINE, WP_LANDMINE, WP_LUGER };
    static const int phases[] = { WEAPON_READY, WEAPON_FIRING, WEAPON_FIRINGALT };
    pmove_t move;
    pmoveExt_t ext;
    playerState_t state, before;
    bg_character_t character;
    int skills[SK_NUM_SKILLS];
    int i, prone, gate, phase, weapon, duration, body;
    pm = &move;
    for(i = 0; i < 7; ++i) for(prone = 0; prone < 2; ++prone)
    for(gate = 0; gate < 4; ++gate) for(phase = 0; phase < 3; ++phase) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        memset(skills, 0, sizeof(skills));
        weapon = weapons[i]; body = i >= 5;
        move.ps = &state; move.pmext = &ext; move.skill = skills;
        /* Skipped body animation must not require a model or character. */
        move.character = body ? &character : NULL;
        character.animModelInfo = &model;
        state.weapon = weapon; state.weaponstate = phases[phase];
        state.ammo[BG_FindAmmoForWeapon(weapon)] = 9;
        state.weaponTime = 3; state.weapAnim = 123;
        state.eFlags = prone ? EF_PRONE : 0;
        state.pm_type = gate == 1 ? PM_DEAD : PM_NORMAL;
        ext.weapAnimTimer = gate == 2 ? 1 : 0;
        move.cmd.weapon = gate == 3 ? WP_NONE : weapon;
        before = state; bodyCalls = conditionCalls = badBoundary = 0;
        CHECK(NITMOD_ReloadBodyEventRequired(weapon) == body);
        PM_BeginWeaponReload(weapon);
        duration = GetAmmoTableData(weapon)->reloadTime;
        CHECK(state.weaponstate == WEAPON_RELOADING);
        CHECK(state.weaponTime == (phases[phase] == WEAPON_READY ? 3 + duration : duration > 3 ? duration : 3));
        CHECK(bodyCalls == body && !badBoundary && !conditionCalls);
        if(body) CHECK(bodyEvent == (prone ? ANIM_ET_RELOADPRONE : ANIM_ET_RELOAD) && bodyWeaponState == phases[phase]);
        CHECK(state.eventSequence == 1 && state.events[0] == EV_FILL_CLIP && state.eventParms[0] == 0);
        if(gate) CHECK(state.weapAnim == 123);
        else CHECK((state.weapAnim & ~ANIM_TOGGLEBIT) == WEAP_RELOAD1);
        CHECK(!memcmp(state.ammo, before.ammo, sizeof(state.ammo)));
        CHECK(!memcmp(state.ammoclip, before.ammoclip, sizeof(state.ammoclip)));
    }
    return 0;
}

static int TestEmptyReloadReserve(void) {
    pmove_t move;
    pmoveExt_t ext;
    playerState_t state, before, expected;
    bg_character_t character;
    nitmodWeaponInventorySlots_t slots;
    int weapon, phase, reserve, target, supported, handled, slot, skills[SK_NUM_SKILLS];
    pm = &move;
    memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
    memset(&character, 0, sizeof(character)); memset(skills, 0, sizeof(skills));
    move.ps = &state; move.pmext = &ext; move.character = &character; move.skill = skills;
    character.animModelInfo = &model;
    move.cmd.weapon = WP_COLT;
    for(weapon = 0; weapon < WP_NUM_WEAPONS; ++weapon)
    for(phase = -1; phase <= WEAPON_RELOADING + 1; ++phase)
    for(reserve = -1; reserve <= 1; ++reserve) {
        memset(&state, 0x25, sizeof(state));
        state.weapon = weapon; state.weaponstate = phase;
        slot = BG_FindAmmoForWeapon(weapon);
        state.ammo[slot] = reserve;
        supported = NITMOD_WeaponInventorySlots(weapon, &slots) && slots.ammo == slot;
        handled = supported && !reserve &&
            (phase == WEAPON_READY || phase == WEAPON_FIRING || phase == WEAPON_FIRINGALT);
        before = expected = state;
        if(handled) expected.weaponstate = WEAPON_READY;
        bodyCalls = conditionCalls = badBoundary = 0;
        /* Ineligible target: reserve reset must precede target eligibility. */
        PM_BeginWeaponReload(WP_BINOCULARS);
        CHECK(!memcmp(&state, &expected, sizeof(state)));
        CHECK(!bodyCalls && !conditionCalls && !badBoundary);
        state = before;
        CHECK(NITMOD_ResetReloadWithoutReserve(&state, slot) == handled);
        CHECK(!memcmp(&state, &expected, sizeof(state)));
        state = before;
        CHECK(!NITMOD_ResetReloadWithoutReserve(&state, -1));
        CHECK(!NITMOD_ResetReloadWithoutReserve(&state, WP_NUM_WEAPONS));
        CHECK(!memcmp(&state, &before, sizeof(state)));
    }
    /* Target reserve, full-magazine and lean constraints cannot hide current
     * reserve exhaustion. No model/event/animation/timer changes are allowed. */
    for(target = 0; target < WP_NUM_WEAPONS; ++target)
    for(phase = -1; phase <= WEAPON_RELOADING + 1; ++phase) {
        memset(&state, 0, sizeof(state));
        state.weapon = WP_LUGER; state.weaponstate = phase;
        state.weaponTime = 31; state.weaponDelay = 17; state.weapAnim = 123;
        state.ammo[target] = 9; state.ammo[WP_LUGER] = 0;
        state.ammoclip[target] = 999; state.leanf = 1;
        expected = state;
        if(phase == WEAPON_READY || phase == WEAPON_FIRING || phase == WEAPON_FIRINGALT)
            expected.weaponstate = WEAPON_READY;
        bodyCalls = conditionCalls = badBoundary = 0;
        PM_BeginWeaponReload(target);
        CHECK(!memcmp(&state, &expected, sizeof(state)));
        CHECK(!bodyCalls && !conditionCalls && !badBoundary);
    }
    CHECK(!NITMOD_ResetReloadWithoutReserve(NULL, WP_LUGER));
    return 0;
}

static int TestReloadFiringStates(void) {
    pmove_t move;
    pmoveExt_t ext;
    playerState_t state, before;
    bg_character_t character;
    int skills[SK_NUM_SKILLS];
    int phase, timeIndex, outer, blocked, allowed, duration, expectedTime;
    int times[] = { -1, 0, 1, 10000 };
    pm = &move;
    duration = GetAmmoTableData(WP_LUGER)->reloadTime;
    for(phase = -1; phase <= WEAPON_RELOADING + 1; ++phase)
    for(timeIndex = 0; timeIndex < 4; ++timeIndex)
    for(outer = 0; outer < 2; ++outer)
    for(blocked = 0; blocked < 3; ++blocked) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        memset(skills, 0, sizeof(skills));
        move.ps = &state; move.pmext = &ext; move.character = &character; move.skill = skills;
        character.animModelInfo = &model;
        state.weapon = WP_LUGER; state.weaponstate = phase;
        state.weaponTime = times[timeIndex]; state.weapAnim = 123;
        state.ammo[WP_LUGER] = 9;
        if(blocked == 1) state.ammoclip[WP_LUGER] = GetAmmoTableData(WP_LUGER)->maxclip;
        if(blocked == 2) state.leanf = 1;
        move.cmd.weapon = WP_LUGER; move.cmd.wbuttons = WBUTTON_RELOAD;
        before = state; bodyCalls = conditionCalls = badBoundary = 0;
        allowed = (phase == WEAPON_READY || phase == WEAPON_FIRING || phase == WEAPON_FIRINGALT) &&
            (!outer || blocked != 1) && (!outer || times[timeIndex] <= 0);
        if(outer) PM_CheckForReload(WP_LUGER);
        else PM_BeginWeaponReload(WP_LUGER);
        if(!allowed) {
            CHECK(!memcmp(&state, &before, sizeof(state)));
            CHECK(!bodyCalls && !conditionCalls && !badBoundary);
        } else {
            expectedTime = phase == WEAPON_READY ? times[timeIndex] + duration :
                (times[timeIndex] > duration ? times[timeIndex] : duration);
            CHECK(state.weaponstate == WEAPON_RELOADING && state.weaponTime == expectedTime);
            CHECK(bodyCalls == 1 && bodyEvent == ANIM_ET_RELOAD && bodyWeaponState == phase && !badBoundary);
            CHECK(state.eventSequence == 1 && state.events[0] == EV_FILL_CLIP && state.eventParms[0] == 0);
            CHECK((state.weapAnim & ~ANIM_TOGGLEBIT) == WEAP_RELOAD1);
            CHECK(!memcmp(state.ammo, before.ammo, sizeof(state.ammo)));
            CHECK(!memcmp(state.ammoclip, before.ammoclip, sizeof(state.ammoclip)));
        }
    }
    return 0;
}

static int TestScopeReloadCycle(void) {
    static const int bases[] = { WP_GARAND, WP_K43, WP_FG42 };
    static const int scopes[] = { WP_GARAND_SCOPE, WP_K43_SCOPE, WP_FG42SCOPE };
    pmove_t move;
    pmoveExt_t ext;
    playerState_t state, before;
    bg_character_t character;
    int skills[SK_NUM_SKILLS];
    int i, reload, prone, gate, blocked, sequence, phase, timer;
    pm = &move;
    for(i = 0; i < 3; ++i) for(reload = 0; reload < 2; ++reload)
    for(prone = 0; prone < 2; ++prone) for(gate = 0; gate < 4; ++gate)
    for(blocked = 0; blocked < 3; ++blocked) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        memset(skills, 0, sizeof(skills));
        move.ps = &state; move.pmext = &ext; move.character = &character; move.skill = skills;
        character.animModelInfo = &model;
        state.weapon = scopes[i]; state.weaponstate = WEAPON_READY;
        memset(state.weapons, 0xff, sizeof(state.weapons));
        state.eFlags = prone ? EF_PRONE : 0;
        state.ammo[BG_FindAmmoForWeapon(bases[i])] = 9;
        if(blocked == 1) state.ammoclip[BG_FindAmmoForWeapon(bases[i])] = GetAmmoTableData(bases[i])->maxclip;
        if(blocked == 2) state.leanf = 1;
        move.cmd.weapon = gate == 3 ? WP_NONE : bases[i];
        state.pm_type = gate == 1 ? PM_DEAD : PM_NORMAL;
        ext.weapAnimTimer = gate == 2 ? 1 : 0;
        bodyCalls = conditionCalls = badBoundary = 0;
        PM_BeginWeaponChange(scopes[i], bases[i], reload ? qtrue : qfalse);
        CHECK(state.weaponstate == (reload ? WEAPON_DROPPING_TORELOAD : WEAPON_DROPPING));
        state.weaponTime = 0;
        PM_FinishWeaponChange();
        CHECK(state.weapon == bases[i]);
        CHECK(state.weaponstate == (reload ? WEAPON_RAISING_TORELOAD : WEAPON_RAISING));
        /* Neither positive timer may complete the raise. */
        before = state;
        CHECK(!PM_FinishWeaponRaise());
        CHECK(!memcmp(&state, &before, sizeof(state)));
        state.weaponTime = 0; state.weaponDelay = 1; before = state;
        CHECK(!PM_FinishWeaponRaise());
        CHECK(!memcmp(&state, &before, sizeof(state)));
        state.weaponDelay = 0;
        before = state; sequence = state.eventSequence; bodyCalls = 0;
        CHECK(PM_FinishWeaponRaise());
        CHECK(!badBoundary);
        CHECK(!memcmp(state.ammo, before.ammo, sizeof(state.ammo)));
        CHECK(!memcmp(state.ammoclip, before.ammoclip, sizeof(state.ammoclip)));
        if(reload && (blocked != 1 || bases[i] == WP_FG42)) {
            CHECK(bodyWeaponState == WEAPON_READY);
            CHECK(state.weaponstate == WEAPON_RELOADING);
            CHECK(state.weaponTime == GetAmmoTableData(bases[i])->reloadTime);
            CHECK(state.eventSequence == sequence + 1);
            CHECK(state.events[sequence & (MAX_EVENTS - 1)] == EV_FILL_CLIP);
            CHECK(bodyCalls == 1 && bodyEvent == (prone ? ANIM_ET_RELOADPRONE : ANIM_ET_RELOAD));
            if(gate) CHECK(state.weapAnim == before.weapAnim);
            else CHECK((state.weapAnim & ~ANIM_TOGGLEBIT) == WEAP_RELOAD1);
        } else {
            CHECK(state.weaponstate == WEAPON_READY && state.weaponTime == 0);
            CHECK(state.eventSequence == sequence && !bodyCalls);
            if(gate || reload) CHECK(state.weapAnim == before.weapAnim);
            else CHECK((state.weapAnim & ~ANIM_TOGGLEBIT) == WEAP_IDLE1);
        }
        before = state;
        CHECK(!PM_FinishWeaponRaise());
        CHECK(!memcmp(&state, &before, sizeof(state)));
    }
    /* All non-raising phases are untouched, even with expired timers. */
    for(phase = -1; phase <= WEAPON_RELOADING + 1; ++phase) {
        if(phase == WEAPON_RAISING || phase == WEAPON_RAISING_TORELOAD) continue;
        for(timer = -1; timer <= 1; ++timer) {
            memset(&state, 0x25, sizeof(state));
            state.weaponstate = phase; state.weaponTime = timer; state.weaponDelay = 0;
            before = state;
            CHECK(!PM_FinishWeaponRaise());
            CHECK(!memcmp(&state, &before, sizeof(state)));
        }
    }
    return 0;
}

static int TestOrdinarySwitches(void) {
    pmove_t move;
    pmoveExt_t ext, extBefore;
    playerState_t state, before;
    bg_character_t character;
    int old, target, reload, prone, gate, resetTimer, fixedEvent, event, flags, count = 0;
    pm = &move;
    for(old = WP_NONE; old < WP_NUM_WEAPONS; ++old)
    for(target = 1; target < WP_NUM_WEAPONS; ++target) {
        if(old == target || weapAlts[old] == target) continue;
        for(reload = 0; reload < 2; ++reload) for(prone = 0; prone < 2; ++prone)
        for(gate = 0; gate < 4; ++gate) {
            ++count;
            memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
            memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
            move.ps = &state; move.pmext = &ext; move.character = &character;
            character.animModelInfo = &model;
            state.weapon = old; state.weaponstate = WEAPON_READY;
            state.weaponTime = 7; state.grenadeTimeLeft = -7;
            state.weapAnim = 123; state.eFlags = prone ? EF_PRONE : 0;
            state.pm_type = gate == 1 ? PM_DEAD : PM_NORMAL;
            state.aimSpreadScale = 17; state.aimSpreadScaleFloat = 19.0f;
            state.eventSequence = MAX_EVENTS - 1;
            memset(state.weapons, 0xff, sizeof(state.weapons));
            memset(state.ammo, 0x25, sizeof(state.ammo));
            memset(state.ammoclip, 0x35, sizeof(state.ammoclip));
            move.cmd.weapon = gate == 3 ? WP_NONE : target;
            ext.weapAnimTimer = gate == 2 ? 1 : 0;
            ext.silencedSideArm = 0x57;
            VectorSet(ext.mountedWeaponAngles, 17, 18, 19);
            before = state; extBefore = ext;
            bodyCalls = conditionCalls = badBoundary = 0;
            PM_BeginWeaponChange(old, target, reload ? qtrue : qfalse);
            if(target == WP_MORTAR_SET && prone) {
                before.nextWeapon = target;
                CHECK(!memcmp(&state, &before, sizeof(state)));
                CHECK(!memcmp(&ext, &extBefore, sizeof(ext)));
                CHECK(!bodyCalls && !conditionCalls && !badBoundary);
                continue;
            }
            resetTimer = target == WP_DYNAMITE || target == WP_GRENADE_LAUNCHER ||
                target == WP_GRENADE_PINEAPPLE || target == WP_SMOKE_BOMB;
            fixedEvent = resetTimer || target == WP_CARBINE || target == WP_KAR98 || target == WP_MORTAR_SET;
            event = fixedEvent || !reload ? EV_CHANGE_WEAPON : EV_CHANGE_WEAPON_2;
            CHECK(state.weapon == old && state.nextWeapon == target && state.weaponTime == 257);
            CHECK(state.weaponstate == (reload ? WEAPON_DROPPING_TORELOAD : WEAPON_DROPPING));
            CHECK(state.grenadeTimeLeft == (resetTimer ? 0 : -7));
            CHECK(state.eventSequence == MAX_EVENTS && state.events[MAX_EVENTS - 1] == event);
            CHECK(state.eventParms[MAX_EVENTS - 1] == 0 && state.events[0] == 0);
            CHECK(bodyCalls == 1 && bodyEvent == ANIM_ET_DROPWEAPON && !badBoundary);
            CHECK(!memcmp(&ext, &extBefore, sizeof(ext)));
            CHECK(!memcmp(state.ammo, before.ammo, sizeof(state.ammo)));
            CHECK(!memcmp(state.ammoclip, before.ammoclip, sizeof(state.ammoclip)));
            if(gate) CHECK(state.weapAnim == 123);
            else CHECK(state.weapAnim == (ANIM_TOGGLEBIT | PM_DropAnimForWeapon(old)));
            before = state; state.weaponTime = 0; bodyCalls = 0;
            PM_FinishWeaponChange();
            CHECK(state.weapon == target && state.weaponTime == 250);
            CHECK(state.weaponstate == (reload ? WEAPON_RAISING_TORELOAD : WEAPON_RAISING));
            CHECK(state.eventSequence == before.eventSequence);
            CHECK(!memcmp(state.events, before.events, sizeof(state.events)));
            CHECK(!memcmp(state.eventParms, before.eventParms, sizeof(state.eventParms)));
            CHECK(!memcmp(state.ammo, before.ammo, sizeof(state.ammo)));
            CHECK(!memcmp(state.ammoclip, before.ammoclip, sizeof(state.ammoclip)));
            CHECK(conditionCalls == 1 && conditionWeapon == target && bodyCalls == 1 && !badBoundary);
            CHECK(bodyEvent == (prone ? ANIM_ET_RAISEWEAPONPRONE : ANIM_ET_RAISEWEAPON));
            if(gate) CHECK(state.weapAnim == before.weapAnim);
            else CHECK(state.weapAnim == PM_RaiseAnimForWeapon(target));
            flags = 0x57;
            if(target == WP_COLT || target == WP_LUGER) flags &= ~1;
            if(target == WP_SILENCER || target == WP_SILENCED_COLT) flags |= 1;
            if(target == WP_CARBINE || target == WP_KAR98) flags &= ~2;
            if(target == WP_M7 || target == WP_GPG40) flags |= 2;
            extBefore.silencedSideArm = flags;
            CHECK(!memcmp(&ext, &extBefore, sizeof(ext)));
            if(target == WP_GARAND_SCOPE || target == WP_K43_SCOPE || target == WP_FG42SCOPE) {
                CHECK(state.aimSpreadScale == 255 && state.aimSpreadScaleFloat == 255.0f);
            } else CHECK(state.aimSpreadScale == 17 && state.aimSpreadScaleFloat == 19.0f);
        }
    }
    CHECK(count == 38128);
    return 0;
}

static int TestMortarWaterGate(void) {
    pmove_t move;
    pmoveExt_t ext, extBefore;
    playerState_t state, before;
    bg_character_t character;
    int water, prone, reload;
    pm = &move;
    for(water = 0; water <= 3; ++water) for(prone = 0; prone < 2; ++prone)
    for(reload = 0; reload < 2; ++reload) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        move.ps = &state; move.pmext = &ext; move.character = &character;
        character.animModelInfo = &model;
        state.weapon = WP_MORTAR; state.weaponstate = WEAPON_READY;
        state.eFlags = prone ? EF_PRONE : 0; state.weaponTime = 7;
        memset(state.weapons, 0xff, sizeof(state.weapons));
        move.cmd.weapon = WP_MORTAR_SET; move.waterlevel = water;
        VectorSet(ext.mountedWeaponAngles, 17, 18, 19);
        VectorSet(pml.forward, 1, 0, 0); VectorSet(pml.right, 0, -1, 0);
        before = state; extBefore = ext;
        bodyCalls = conditionCalls = badBoundary = 0;
        PM_BeginWeaponChange(WP_MORTAR, WP_MORTAR_SET, reload ? qtrue : qfalse);
        if(prone || water == 3) {
            /* Original/native late veto keeps nextWeapon, unlike early guards. */
            before.nextWeapon = WP_MORTAR_SET;
            CHECK(!memcmp(&state, &before, sizeof(state)));
            CHECK(!memcmp(&ext, &extBefore, sizeof(ext)));
            CHECK(!bodyCalls && !conditionCalls && !badBoundary);
        } else {
            CHECK(state.weaponstate == (reload ? WEAPON_DROPPING_TORELOAD : WEAPON_DROPPING));
            CHECK(state.weaponTime == 7 && state.nextWeapon == WP_MORTAR_SET);
            CHECK(state.eventSequence == 1 && state.events[0] == EV_CHANGE_WEAPON);
            CHECK(bodyCalls == 1 && !badBoundary && ext.mountedWeaponAngles[0] != 17);
        }
    }
    return 0;
}

static int TestSwitchTimerExtremes(const int pairs[][4], int pairCount) {
    static const int times[] = { INT_MIN, -1, 0, 1, INT_MAX - 250, INT_MAX - 1, INT_MAX };
    pmove_t move;
    pmoveExt_t ext, initialExt, expectedExt;
    playerState_t state, initial, expected;
    bg_character_t character;
    int i, t, reload, finish, slot, baselineBody, baselineCondition, count = 0;
    uint32_t sumBits;
    pm = &move;
    for(i = 0; i < pairCount; ++i) for(t = 0; t < 7; ++t)
    for(reload = 0; reload < 2; ++reload) for(finish = 0; finish < 2; ++finish) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        move.ps = &state; move.pmext = &ext; move.character = &character;
        character.animModelInfo = &model; move.cmd.weapon = pairs[i][1];
        state.weapon = pairs[i][0]; state.nextWeapon = pairs[i][1];
        state.weaponstate = finish ? (reload ? WEAPON_DROPPING_TORELOAD : WEAPON_DROPPING) : WEAPON_READY;
        memset(state.weapons, 0xff, sizeof(state.weapons));
        for(slot = 0; slot < MAX_WEAPONS; ++slot) state.ammoclip[slot] = 1;
        initial = state; initialExt = ext;
        bodyCalls = conditionCalls = badBoundary = 0;
        if(finish) PM_FinishWeaponChange();
        else PM_BeginWeaponChange(pairs[i][0], pairs[i][1], reload);
        CHECK(state.weaponTime == pairs[i][finish ? 3 : 2] && !badBoundary);
        expected = state; expectedExt = ext;
        baselineBody = bodyCalls; baselineCondition = conditionCalls;
        sumBits = (uint32_t)times[t] + (uint32_t)state.weaponTime;
        expected.weaponTime = sumBits <= INT32_MAX ? (int)sumBits : -1 - (int)(UINT32_MAX - sumBits);
        state = initial; ext = initialExt; state.weaponTime = times[t];
        bodyCalls = conditionCalls = badBoundary = 0;
        if(finish) PM_FinishWeaponChange();
        else PM_BeginWeaponChange(pairs[i][0], pairs[i][1], reload);
        CHECK(!memcmp(&state, &expected, sizeof(state)));
        CHECK(!memcmp(&ext, &expectedExt, sizeof(ext)));
        CHECK(bodyCalls == baselineBody && conditionCalls == baselineCondition && !badBoundary);
        ++count;
    }
    CHECK(count == pairCount * 28);
    return 0;
}

int main(void) {
    static const int pairs[][4] = {
        {WP_LUGER, WP_SILENCER, 0, 1190}, {WP_SILENCER, WP_LUGER, 1000, 0},
        {WP_COLT, WP_SILENCED_COLT, 0, 1190}, {WP_SILENCED_COLT, WP_COLT, 1000, 0},
        {WP_GARAND, WP_GARAND_SCOPE, 250, 250}, {WP_GARAND_SCOPE, WP_GARAND, 250, 250},
        {WP_K43, WP_K43_SCOPE, 250, 250}, {WP_K43_SCOPE, WP_K43, 250, 250},
        {WP_FG42, WP_FG42SCOPE, 50, 50}, {WP_FG42SCOPE, WP_FG42, 50, 50},
        {WP_CARBINE, WP_M7, 0, 2350}, {WP_M7, WP_CARBINE, 0, 1347},
        {WP_KAR98, WP_GPG40, 0, 2350}, {WP_GPG40, WP_KAR98, 0, 1347},
        {WP_MOBILE_MG42, WP_MOBILE_MG42_SET, 0, 1250},
        {WP_MOBILE_MG42_SET, WP_MOBILE_MG42, 0, 1722},
        {WP_MORTAR, WP_MORTAR_SET, 0, 1667}, {WP_MORTAR_SET, WP_MORTAR, 0, 1000}
    };
    pmove_t move;
    pmoveExt_t ext;
    playerState_t state, before;
    bg_character_t character;
    int i, reload, prone, gate, clip, old, target, returnRifle, duration, event, sequence, dropAnim, animate, alt;
    pm = &move;
    for(i = 0; i < 18; ++i) for(reload = 0; reload < 2; ++reload)
    for(prone = 0; prone < 2; ++prone) for(gate = 0; gate < 4; ++gate)
    for(clip = 0; clip < 2; ++clip) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state)); memset(&character, 0, sizeof(character));
        move.ps = &state; move.pmext = &ext; move.character = &character;
        character.animModelInfo = &model;
        old = pairs[i][0]; target = pairs[i][1];
        state.weapon = old; state.weaponstate = WEAPON_READY;
        state.eFlags = prone ? EF_PRONE : 0;
        state.weaponTime = 7;
        state.weapAnim = 123;
        memset(state.weapons, 0xff, sizeof(state.weapons));
        state.ammoclip[BG_FindAmmoForWeapon(old)] = clip;
        state.ammo[target] = 3;
        move.cmd.weapon = gate == 3 ? WP_NONE : target;
        state.pm_type = gate == 1 ? PM_DEAD : PM_NORMAL;
        ext.weapAnimTimer = gate == 2 ? 1 : 0;
        ext.silencedSideArm = 0x54;
        VectorSet(pml.forward, 1, 0, 0); VectorSet(pml.right, 0, -1, 0);
        VectorSet(ext.mountedWeaponAngles, 17, 18, 19);
        bodyCalls = conditionCalls = badBoundary = 0;
        PM_BeginWeaponChange(old, target, reload ? qtrue : qfalse);
        if(target == WP_MORTAR_SET && prone) {
            CHECK(state.weaponstate == WEAPON_READY && state.weaponTime == 7);
            CHECK(!bodyCalls && !state.eventSequence);
            continue;
        }
        CHECK(!badBoundary && bodyCalls == 1);
        CHECK(state.weapon == old && state.nextWeapon == target);
        CHECK(state.weaponstate == (reload ? WEAPON_DROPPING_TORELOAD : WEAPON_DROPPING));
        CHECK(state.weaponTime == 7 + pairs[i][2]);
        CHECK(bodyEvent == ((i == 1 || i == 3) ?
            (prone ? ANIM_ET_UNDO_ALT_WEAPON_MODE_PRONE : ANIM_ET_UNDO_ALT_WEAPON_MODE) : ANIM_ET_DROPWEAPON));
        CHECK(gate ? state.weapAnim == 123 : state.weapAnim != 123);
        if(i == 14 || i == 16) CHECK(ext.mountedWeaponAngles[0] != 17);
        else CHECK(ext.mountedWeaponAngles[0] == 17 && ext.mountedWeaponAngles[1] == 18 && ext.mountedWeaponAngles[2] == 19);
        returnRifle = i == 11 || i == 13;
        event = target == WP_MORTAR_SET ? EV_CHANGE_WEAPON : reload ? EV_CHANGE_WEAPON_2 : EV_CHANGE_WEAPON;
        CHECK(state.eventSequence == (returnRifle ? 0 : 1));
        if(!returnRifle) CHECK(state.events[0] == event && state.eventParms[0] == 0);
        if(i == 10 || i == 12) CHECK(state.ammoclip[target] == 1 && state.ammo[target] == 2);
        sequence = state.eventSequence; dropAnim = state.weapAnim;
        state.weaponTime = 0; bodyCalls = 0;
        PM_FinishWeaponChange();
        duration = returnRifle && !clip ? 0 : pairs[i][3];
        animate = !(returnRifle && !clip);
        alt = i < 4 || (i >= 10 && i <= 13) || i >= 16;
        CHECK(state.weapon == target && state.weaponTime == duration);
        CHECK(state.weaponstate == (reload ? WEAPON_RAISING_TORELOAD : WEAPON_RAISING));
        CHECK(state.eventSequence == sequence && conditionCalls == 1 && conditionWeapon == target);
        CHECK(bodyCalls == animate && !badBoundary);
        if(animate) CHECK(bodyEvent == (alt ? (prone ? ANIM_ET_DO_ALT_WEAPON_MODE_PRONE : ANIM_ET_DO_ALT_WEAPON_MODE) :
            (prone ? ANIM_ET_RAISEWEAPONPRONE : ANIM_ET_RAISEWEAPON)));
        if(gate || !animate) CHECK(state.weapAnim == dropAnim);
        else CHECK(state.weapAnim != dropAnim);
        CHECK(ext.silencedSideArm == NITMOD_RifleGrenadeModeFlags(target, NITMOD_PistolModeFlags(target, 0x54)));
    }
    /* Real begin guards must return before any player state/event mutation. */
    for(i = 0; i < 9; ++i) {
        memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
        memset(&state, 0, sizeof(state));
        move.ps = &state; move.pmext = &ext; move.character = &character;
        state.weapon = WP_LUGER; state.weaponstate = WEAPON_READY;
        memset(state.weapons, 0xff, sizeof(state.weapons));
        target = WP_SILENCER;
        switch(i) {
            case 0: state.pm_flags = PMF_RESPAWNED; break;
            case 1: target = WP_NONE; break;
            case 2: target = WP_NUM_WEAPONS; break;
            case 3: memset(state.weapons, 0, sizeof(state.weapons)); break;
            case 4: state.weaponstate = WEAPON_RELOADING; break;
            case 5: state.weaponstate = WEAPON_DROPPING; break;
            case 6: state.weaponstate = WEAPON_DROPPING_TORELOAD; break;
            case 7: state.weaponDelay = 1; break;
            case 8: state.grenadeTimeLeft = 1; break;
        }
        before = state; bodyCalls = conditionCalls = badBoundary = 0;
        PM_BeginWeaponChange(WP_LUGER, target, qtrue);
        CHECK(!memcmp(&state, &before, sizeof(state)));
        CHECK(!bodyCalls && !conditionCalls && !badBoundary);
    }
    /* Ownership can disappear between drop and finish. Commit NONE but
     * retain reload intent, without manufacturing a new switch event. */
    for(reload = 0; reload < 2; ++reload) {
        memset(&state, 0, sizeof(state)); memset(&ext, 0, sizeof(ext));
        state.weapon = WP_LUGER; state.nextWeapon = WP_SILENCER;
        state.weaponstate = reload ? WEAPON_DROPPING_TORELOAD : WEAPON_DROPPING;
        move.cmd.weapon = WP_SILENCER;
        bodyCalls = conditionCalls = badBoundary = 0;
        PM_FinishWeaponChange();
        CHECK(state.weapon == WP_NONE && state.nextWeapon == WP_SILENCER);
        CHECK(state.weaponstate == (reload ? WEAPON_RAISING_TORELOAD : WEAPON_RAISING));
        CHECK(state.weaponTime == 250 && !state.eventSequence);
        CHECK(bodyCalls == 1 && conditionCalls == 1 && !badBoundary);
    }
    /* Exercise the recovered same-weapon exceptions in the actual finish,
     * alongside a normal same-target return (which still commits raising). */
    for(i = 0; i < 3; ++i) {
        memset(&state, 0, sizeof(state)); memset(&ext, 0, sizeof(ext));
        state.weapon = i == 0 ? WP_KNIFE : i == 1 ? WP_SMOKE_BOMB : WP_COLT;
        state.nextWeapon = state.weapon;
        memset(state.weapons, 0xff, sizeof(state.weapons));
        state.weaponstate = WEAPON_DROPPING;
        bodyCalls = conditionCalls = badBoundary = 0;
        PM_FinishWeaponChange();
        CHECK(state.weaponstate == WEAPON_RAISING);
        CHECK(state.weaponTime == (i < 2 ? 250 : 0));
        CHECK(bodyCalls == (i < 2) && conditionCalls == (i < 2) && !badBoundary);
        CHECK(!state.eventSequence);
    }
    CHECK(!TestOrdinarySwitches());
    CHECK(!TestMortarWaterGate());
    CHECK(!TestScopeReloadCycle());
    CHECK(!TestReloadFiringStates());
    CHECK(!TestEmptyReloadReserve());
    CHECK(!TestReloadBodySelection());
    CHECK(!TestFastReloadArithmetic());
    CHECK(!TestNativeReloadFinish());
    CHECK(!TestLeaningReload());
    CHECK(!TestAkimboReloadRequests());
    CHECK(!TestAlternateReloadInput());
    CHECK(!TestTransitionCycles());
    CHECK(!TestTransitionTimerBoundaries());
    CHECK(!TestReloadAnimationSelection());
    CHECK(!TestReloadTimerExtremes());
    CHECK(!TestSwitchTimerExtremes(pairs, 18));
    CHECK(!TestNativeAmmoConsumption());
    CHECK(!TestAkimboShootReloadCycles());
    CHECK(!TestOuterClipGate());
    return 0;
}
