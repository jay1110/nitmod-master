#include "nitmod_weapon_reload.h"
#include <limits.h>
#include <stdio.h>
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "begin reload check %d\n", __LINE__); return 1; } } while(0)
static animModelInfo_t model;
static int calls, scriptResult, badCall, proneExpected;
static playerState_t *expectedPlayer;
static int switches, switchOld, switchNew, switchReload;
static void *switchContext;
static void RecordSwitch( void *context, int oldWeapon, int newWeapon, qboolean reload ) {
    ++switches; switchContext = context; switchOld = oldWeapon;
    switchNew = newWeapon; switchReload = reload;
}
/* Animation-system boundary double; real event-ring helper remains linked.
 * Do not claim this verifies model script execution or visible animation. */
int BG_AnimScriptEvent( playerState_t *ps, animModelInfo_t *info,
    scriptAnimEventTypes_t event, qboolean isContinue, qboolean force ) {
    ++calls;
    if( ps != expectedPlayer || info != &model || isContinue || !force ||
        event != (proneExpected ? ANIM_ET_RELOADPRONE : ANIM_ET_RELOAD) || ps->weaponstate != WEAPON_READY ) badCall = 1;
    if( scriptResult >= 0 ) ps->torsoTimer = 123;
    return scriptResult;
}
int TestRecoveredReloadBegin( void ) {
    pmove_t move, expectedMove;
    pmoveExt_t ext;
    bg_character_t character;
    playerState_t state, expected;
    ammotable_t ammo;
    nitmodWeaponOptions_t options;
    nitmodWeaponInventorySlots_t slots;
    int weapon, prone, missing, body, result, duration;
    memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
    memset(&character, 0, sizeof(character)); memset(&ammo, 0, sizeof(ammo));
    move.ps = &state; move.pmext = &ext; move.character = &character;
    move.cmd.weapon = WP_COLT; character.animModelInfo = &model;
    ammo.reloadTime = 20; options.noMidclipReload = 0;
    expectedPlayer = &state;
    for( weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon ) {
        if( !NITMOD_WeaponInventorySlots(weapon, &slots) ) continue;
        for( prone = 0; prone < 2; ++prone ) for( missing = 0; missing < 2; ++missing ) {
            memset(&state, 0, sizeof(state));
            state.weapon = WP_COLT; state.weaponstate = WEAPON_READY;
            state.ammo[WP_COLT] = 99; state.eFlags = prone ? EF_PRONE : 0;
            expected = state; expectedMove = move; expectedMove.ps = &expected;
            body = weapon != WP_GRENADE_LAUNCHER && weapon != WP_GRENADE_PINEAPPLE &&
                weapon != WP_DYNAMITE && weapon != WP_SMOKE_BOMB && weapon != WP_TRIPMINE;
            calls = badCall = 0; proneExpected = prone; scriptResult = missing ? -1 : 0;
            result = NITMOD_ReloadWeaponEligible(weapon) ? NITMOD_RELOAD_START_INVENTORY_ALLOWED : NITMOD_RELOAD_START_BLOCKED;
            if( result == NITMOD_RELOAD_START_INVENTORY_ALLOWED ) {
                if( body && !missing ) expected.torsoTimer = 123;
                CHECK(NITMOD_ReloadDuration(weapon, 20, 4, &duration));
                CHECK(NITMOD_ApplyReloadFeedback(&expectedMove, weapon, duration, 4));
            }
            CHECK(NITMOD_BeginWeaponReload(&move, weapon, &ammo, &options, 0, 4) == result);
            CHECK(calls == (body && result == NITMOD_RELOAD_START_INVENTORY_ALLOWED) && !badCall);
            CHECK(!memcmp(&state, &expected, sizeof(state)));
        }
    }
    memset(&state, 0, sizeof(state)); state.weapon = WP_COLT; state.ammo[WP_COLT] = 1;
    move.character = NULL; calls = 0; expected = state;
    CHECK(NITMOD_BeginWeaponReload(&move, WP_COLT, &ammo, &options, 0, 0) == NITMOD_RELOAD_START_INVALID);
    CHECK(!calls && !memcmp(&state, &expected, sizeof(state)));
    CHECK(NITMOD_BeginWeaponReload(&move, WP_DYNAMITE, &ammo, &options, 0, 0) == NITMOD_RELOAD_START_INVENTORY_ALLOWED);
    CHECK(!calls);
    state.weaponstate = WEAPON_FIRING; state.ammo[WP_COLT] = 0;
    CHECK(NITMOD_BeginWeaponReload(&move, WP_COLT, NULL, &options, 0, 0) == NITMOD_RELOAD_START_EMPTY_RESERVE);
    CHECK(state.weaponstate == WEAPON_READY && !calls);
    move.character = &character; state.ammo[WP_COLT] = 1; state.weaponTime = INT_MAX;
    expected = state;
    CHECK(NITMOD_BeginWeaponReload(&move, WP_COLT, &ammo, &options, 0, 0) == NITMOD_RELOAD_START_INVALID);
    CHECK(!calls && !memcmp(&state, &expected, sizeof(state)));
    return 0;
}

int TestRecoveredReloadDispatch( void ) {
    pmove_t move;
    pmoveExt_t ext;
    bg_character_t character;
    playerState_t state, before;
    ammotable_t table[WP_NUM_WEAPONS];
    nitmodReloadPolicy_t policy;
    nitmodWeaponOptions_t options;
    int scoped[] = { WP_GARAND_SCOPE, WP_K43_SCOPE, WP_FG42SCOPE };
    int base[] = { WP_GARAND, WP_K43, WP_FG42 };
    int i, direct, expectedResult;
    memset(&move, 0, sizeof(move)); memset(&ext, 0, sizeof(ext));
    memset(&character, 0, sizeof(character)); memset(table, 0, sizeof(table));
    memset(&policy, 0, sizeof(policy)); options.noMidclipReload = 0;
    move.ps = &state; move.pmext = &ext; move.character = &character;
    character.animModelInfo = &model; move.cmd.weapon = WP_COLT;
    expectedPlayer = &state; proneExpected = 0; scriptResult = -1;
    policy.manualRequested = 1;
    for( i = 0; i < 3; ++i ) for( direct = 0; direct < 3; ++direct ) {
        memset(&state, 0, sizeof(state));
        state.weapon = scoped[i]; state.weaponstate = WEAPON_READY;
        state.ammo[base[i]] = 5; state.weaponTime = 11;
        table[scoped[i]].maxclip = 3; table[scoped[i]].reloadTime = 20;
        policy.scopedAbilityBits = direct == 1 ? 0x20u : 0;
        policy.warMode = direct == 2 ? 2 : 0;
        before = state; switches = calls = badCall = 0;
        expectedResult = direct ? NITMOD_RELOAD_DISPATCH_STARTED : NITMOD_RELOAD_DISPATCH_SWITCH_REQUESTED;
        CHECK(NITMOD_ProcessReloadRequest(&move, scoped[i], &policy, table, WP_NUM_WEAPONS,
            &options, 0, 0, RecordSwitch, &move) == expectedResult);
        CHECK(!badCall);
        if( !direct ) {
            CHECK(switches == 1 && !calls && switchContext == &move);
            CHECK(switchOld == scoped[i] && switchNew == base[i] && switchReload == qtrue);
            CHECK(!memcmp(&state, &before, sizeof(state)));
            CHECK(NITMOD_ProcessReloadRequest(&move, scoped[i], &policy, table, WP_NUM_WEAPONS,
                &options, 0, 0, NULL, NULL) == NITMOD_RELOAD_DISPATCH_INVALID);
            CHECK(!memcmp(&state, &before, sizeof(state)));
        } else {
            CHECK(!switches && calls == 1 && state.weaponstate == WEAPON_RELOADING && state.weaponTime == 31);
            before = state;
            CHECK(NITMOD_ProcessReloadRequest(&move, scoped[i], &policy, table, WP_NUM_WEAPONS,
                &options, 0, 0, RecordSwitch, &move) == NITMOD_RELOAD_DISPATCH_NONE);
            CHECK(calls == 1 && !switches && !memcmp(&state, &before, sizeof(state)));
        }
    }
    switches = calls = 0;
    CHECK(NITMOD_ProcessReloadRequest(NULL, WP_COLT, &policy, table, WP_NUM_WEAPONS,
        &options, 0, 0, RecordSwitch, NULL) == NITMOD_RELOAD_DISPATCH_INVALID);
    CHECK(NITMOD_ProcessReloadRequest(&move, WP_COLT, &policy, table, WP_COLT,
        &options, 0, 0, RecordSwitch, NULL) == NITMOD_RELOAD_DISPATCH_INVALID);
    CHECK(!switches && !calls);
    return 0;
}
