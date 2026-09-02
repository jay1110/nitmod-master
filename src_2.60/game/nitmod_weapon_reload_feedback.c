#include "nitmod_weapon_reload.h"
#include <limits.h>

nitmodReloadDispatch_t NITMOD_ProcessReloadRequest( pmove_t *move, int weapon,
    const nitmodReloadPolicy_t *policy, const ammotable_t *ammoTable, int ammoSlots,
    const nitmodWeaponOptions_t *options, unsigned int reloadAbilityBits,
    unsigned int lightWeaponAbilityBits, nitmodReloadWeaponChange_t changeWeapon,
    void *context ) {
    nitmodReloadDecision_t decision;
    nitmodReloadStartInventory_t result;
    if( !move || !NITMOD_DecideReload(move->ps, weapon, policy, ammoTable, ammoSlots, &decision) )
        return NITMOD_RELOAD_DISPATCH_INVALID;
    if( decision.action == NITMOD_RELOAD_ACTION_NONE ) return NITMOD_RELOAD_DISPATCH_NONE;
    if( decision.action == NITMOD_RELOAD_ACTION_UNSCOPE ) {
        if( !changeWeapon ) return NITMOD_RELOAD_DISPATCH_INVALID;
        changeWeapon(context, weapon, decision.weapon, qtrue);
        return NITMOD_RELOAD_DISPATCH_SWITCH_REQUESTED;
    }
    result = NITMOD_BeginWeaponReload(move, decision.weapon, &ammoTable[decision.weapon],
        options, reloadAbilityBits, lightWeaponAbilityBits);
    switch( result ) {
    case NITMOD_RELOAD_START_INVENTORY_ALLOWED: return NITMOD_RELOAD_DISPATCH_STARTED;
    case NITMOD_RELOAD_START_EMPTY_RESERVE: return NITMOD_RELOAD_DISPATCH_RESET_READY;
    case NITMOD_RELOAD_START_BLOCKED: return NITMOD_RELOAD_DISPATCH_NONE;
    default: return NITMOD_RELOAD_DISPATCH_INVALID;
    }
}

nitmodReloadStartInventory_t NITMOD_BeginWeaponReload( pmove_t *move,
    int targetWeapon, const ammotable_t *weaponAmmo,
    const nitmodWeaponOptions_t *options, unsigned int reloadAbilityBits,
    unsigned int lightWeaponAbilityBits ) {
    nitmodReloadStartInventory_t result;
    int duration, bodyEvent;
    playerState_t timingProbe;
    if( !move || !move->ps || !move->pmext ) return NITMOD_RELOAD_START_INVALID;
    if( !NITMOD_ReloadStateAllowed(move->ps->weaponstate) ) return NITMOD_RELOAD_START_BLOCKED;
    result = NITMOD_CheckReloadStartInventory(move->ps, targetWeapon, options, reloadAbilityBits);
    if( result == NITMOD_RELOAD_START_EMPTY_RESERVE ) {
        move->ps->weaponstate = WEAPON_READY;
        return result;
    }
    if( result != NITMOD_RELOAD_START_INVENTORY_ALLOWED ) return result;
    bodyEvent = NITMOD_ReloadBodyEventRequired(targetWeapon);
    if( !weaponAmmo || (bodyEvent && (!move->character || !move->character->animModelInfo)) ||
        move->ps->eventSequence < 0 || move->ps->eventSequence == INT_MAX ||
        !NITMOD_ReloadDuration(targetWeapon, weaponAmmo->reloadTime, lightWeaponAbilityBits, &duration) )
        return NITMOD_RELOAD_START_INVALID;
    /* Validate arithmetic before invoking the external animation system. */
    timingProbe = *move->ps;
    if( !NITMOD_ApplyReloadTiming(&timingProbe, duration) ) return NITMOD_RELOAD_START_INVALID;
    if( bodyEvent ) BG_AnimScriptEvent(move->ps, move->character->animModelInfo,
        (move->ps->eFlags & EF_PRONE) ? ANIM_ET_RELOADPRONE : ANIM_ET_RELOAD, qfalse, qtrue);
    /* Native BG_AnimScriptEvent changes body animations, not reload timing,
     * weaponstate or the predictable-event sequence validated above. */
    if( !NITMOD_ApplyReloadFeedback(move, targetWeapon, duration, lightWeaponAbilityBits) )
        return NITMOD_RELOAD_START_INVALID;
    return NITMOD_RELOAD_START_INVENTORY_ALLOWED;
}

/* PM_ContinueWeaponAnim semantics: do not restart the same animation. */
static void ContinueReloadAnimation( pmove_t *move, int targetWeapon, unsigned int lightBits ) {
    playerState_t *state = move->ps;
    int animation;
    if( targetWeapon == WP_MORTAR || targetWeapon == WP_MORTAR_SET ) return;
    animation = NITMOD_ReloadAnimation(state->weapon, (lightBits & NITMOD_FAST_RELOAD) != 0);
    if( move->cmd.weapon == WP_NONE || (state->weapAnim & ~ANIM_TOGGLEBIT) == animation ||
        move->pmext->weapAnimTimer > 0 || state->pm_type >= PM_DEAD ) return;
    state->weapAnim = ((state->weapAnim & ANIM_TOGGLEBIT) ^ ANIM_TOGGLEBIT) | animation;
}

int NITMOD_ApplyReloadFeedback( pmove_t *move, int targetWeapon,
    int duration, unsigned int lightWeaponAbilityBits ) {
    nitmodWeaponInventorySlots_t slots;
    if( !move || !move->ps || !move->pmext ||
        !NITMOD_WeaponInventorySlots(targetWeapon, &slots) ||
        !NITMOD_WeaponInventorySlots(move->ps->weapon, &slots) ||
        move->ps->eventSequence < 0 || move->ps->eventSequence == INT_MAX ) return 0;
    /* Validate/apply timing before any animation or event writes. Unlike the
     * original, invalid duration/overflow cannot leave partial feedback. */
    if( !NITMOD_ApplyReloadTiming(move->ps, duration) ) return 0;
    ContinueReloadAnimation(move, targetWeapon, lightWeaponAbilityBits);
    BG_AddPredictableEventToPlayerstate(EV_FILL_CLIP, 0, move->ps);
    return 1;
}
