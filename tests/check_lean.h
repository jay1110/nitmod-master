/* Exercise the same PM_UpdateLean implementation in cgame and qagame. */
#include "bg_local.h"
#include <stddef.h>
extern void PM_UpdateLean(playerState_t *, usercmd_t *, pmove_t *);
static int leanMoveTraces, leanMoveErrors;
static void LeanMoveTrace(trace_t *result, const vec3_t start, const vec3_t mins,
    const vec3_t maxs, const vec3_t end, int client, int mask) {
    if(client != 3 || mask != MASK_PLAYERSOLID || start[2] != 48 ||
       mins[0] != -8 || mins[2] != -7 || maxs[2] != 4) ++leanMoveErrors;
    memset(result, 0, sizeof(*result)); result->fraction = .5f; ++leanMoveTraces;
}
static int CheckLeanMovement(void) {
    pmove_t move, *savedPm = pm;
    pml_t savedPml = pml;
    playerState_t ps;
    const int flags[] = {0, EF_MG42_ACTIVE, EF_MOUNTEDTANK, EF_FIRING, EF_DEAD, EF_SPARE0, EF_PRONE, EF_AAGUN_ACTIVE};
    int mode, options, buttons, spectator, forward, up, flag, errors = 0;
    leanMoveErrors = 0;
    if(offsetof(playerState_t, holdable) + 2 * sizeof(int) != 0x398 ||
       offsetof(entityState_t, constantLight) != 0x98) ++errors;
    for(mode = 0; mode < 2; ++mode) for(options = 0; options < 2; ++options)
    for(buttons = 0; buttons < 4; ++buttons) for(spectator = 0; spectator < 2; ++spectator)
    for(forward = 0; forward < 2; ++forward) for(up = 0; up < 2; ++up) for(flag = 0; flag < 8; ++flag) {
        int direction = (buttons & 2 ? 1 : 0) - (buttons & 1 ? 1 : 0);
        memset(&move, 0, sizeof(move)); memset(&ps, 0, sizeof(ps));
        move.ps = &ps; move.trace = LeanMoveTrace; move.nitmodLeanEnabled = mode;
        move.nitmodWeaponFlags = options ? 256 : 0;
        ps.pm_type = spectator ? PM_SPECTATOR : PM_NORMAL;
        ps.clientNum = 3; ps.viewheight = 48; ps.eFlags = flags[flag];
        ps.holdable[NITMOD_HOLDABLE_LEAN_DIRECTION] = 777;
        move.cmd.wbuttons = (buttons & 1 ? WBUTTON_LEANLEFT : 0) | (buttons & 2 ? WBUTTON_LEANRIGHT : 0);
        move.cmd.forwardmove = forward * 127; move.cmd.upmove = up * 127; move.cmd.rightmove = 127;
        if(!(mode && spectator) && (forward || up)) direction = 0;
        if(flags[flag] & (EF_MG42_ACTIVE | EF_MOUNTEDTANK | EF_PRONE)) direction = 0;
        if((flags[flag] & EF_FIRING) && !(mode && options)) direction = 0;
        if(mode && (flags[flag] & (EF_DEAD | EF_SPARE0))) direction = 0;
        if(!mode && (flags[flag] & EF_AAGUN_ACTIVE)) direction = 0;
        pm = &move; pml.msec = 10; leanMoveTraces = 0;
        PM_UpdateLean(&ps, &move.cmd, &move);
        if(mode) {
            entityState_t state;
            memset(&state, 0, sizeof(state)); state.weapon = WP_MP40;
            BG_NITMOD_CopyLeanState(&ps, &state);
            if(state.constantLight != (spectator ? 0 : direction) || state.weapon != WP_MP40) ++errors;
        }
        if(leanMoveTraces != !!direction || fabs(ps.leanf - direction * .7f) > .0001f ||
           ps.holdable[NITMOD_HOLDABLE_LEAN_DIRECTION] != (mode ? direction : 777) ||
           move.cmd.rightmove != (direction && !(mode && spectator) ? 0 : 127)) ++errors;
    }
    pm = savedPm; pml = savedPml;
    errors += leanMoveErrors;
    if(errors) fprintf(stderr, "%d lean movement failures\n", errors);
    return errors;
}
