#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_lean.h"
#include <float.h>
#include <limits.h>

/* CG_PredictLean: original entityState.constantLight carries the signed lean
 * command, not a light intensity for players. Private state is not wire ABI. */
void CG_NitmodPredictLean(centity_t *cent, vec3_t torso, vec3_t head,
                         int viewheight, int weapons, int misc) {
    int direction, elapsed;
    double delta;
    float amount;
    if(!cent) return;
    direction = (cent->currentState.constantLight > 0) - (cent->currentState.constantLight < 0);
    if((cent->currentState.eFlags & (EF_MG42_ACTIVE | EF_MOUNTEDTANK | EF_FIRING |
         EF_DEAD | EF_SPARE0 | EF_PRONE)) || cent->currentState.weapon == WP_MORTAR_SET) direction = 0;
    if(direction != cent->nitmodLean.direction) {
        cent->nitmodLean.direction = direction;
        cent->nitmodLean.time = cg.time;
    }
    delta = (double)cg.time - cent->nitmodLean.time;
    elapsed = delta < 1 ? 1 : delta > 200 ? 200 : (int)delta;
    cent->nitmodLean.time = cg.time;
    amount = cent->nitmodLean.amount;
    if(!(amount >= -28 && amount <= 28)) amount = 0;
    if(!direction) {
        float step = (elapsed / 300.0f) * 28.0f;
        if(amount > 0) { amount -= step; if(amount < 0) amount = 0; }
        else if(amount < 0) { amount += step; if(amount > 0) amount = 0; }
    } else {
        vec3_t eye, end, angles, right;
        vec3_t mins = {-8,-8,-7}, maxs = {8,8,4};
        trace_t trace;
        int axis;
        amount += direction * (elapsed / 200.0f) * 28.0f;
        if(amount > 28) amount = 28;
        if(amount < -28) amount = -28;
        VectorCopy(cent->lerpOrigin, eye); eye[2] += viewheight;
        VectorCopy(cent->lerpAngles, angles); angles[ROLL] += amount * .5f;
        for(axis = 0; axis < 3; ++axis) {
            if(!(eye[axis] >= -FLT_MAX && eye[axis] <= FLT_MAX) ||
               !(angles[axis] >= -FLT_MAX && angles[axis] <= FLT_MAX)) {
                cent->nitmodLean.amount = 0; return;
            }
        }
        AngleVectors(angles, NULL, right, NULL);
        VectorMA(eye, amount, right, end);
        CG_Trace(&trace, eye, mins, maxs, end, cent->currentState.clientNum, MASK_PLAYERSOLID);
        /* A broken engine result must not poison persistent pose state. */
        amount *= trace.fraction >= 0 && trace.fraction <= 1 ? trace.fraction : 0;
    }
    cent->nitmodLean.amount = amount;
    if(weapons & 256) {
        if(torso) {
            torso[ROLL] += amount * (direction == 1 ? 1.9f : 2.35f);
            if(head) head[ROLL] += amount;
        }
    } else if(misc & 32) {
        if(torso) torso[ROLL] += amount * 1.25f;
        if(head) head[ROLL] += amount;
    }
}

void CG_NitmodPlayerLean(centity_t *cent, vec3_t torso, vec3_t head) {
    int height;
    float remoteHeight;
    if(!cent || !cg.snap || !NITMOD_UsesOriginalProtocol()) return;
    if(cent->currentState.clientNum == cg.snap->ps.clientNum) height = cg.snap->ps.viewheight;
    else {
        /* Original +0x5d4 is headRefEnt.origin[2], not an invented stance
         * constant. Keep that original (world-space) value for parity. */
        remoteHeight = cent->pe.headRefEnt.origin[2];
        if(!((double)remoteHeight >= INT_MIN && (double)remoteHeight <= INT_MAX)) return;
        height = (int)remoteHeight;
    }
    CG_NitmodPredictLean(cent, torso, head, height,
        NITMOD_GameState()->weapons, NITMOD_SimpleConfig()->misc);
}
