#include "cg_local.h"
#include "cg_nitmod_projectiles.h"
#include <float.h>

/* Original CG_Missile: 5/42/36/37 use displacement, not launch velocity.
 * Call after wire weapon decoding; these are typed ET weapon identifiers. */
qboolean CG_NitmodMissileAxis(centity_t *cent, vec3_t axis[3], int time, qboolean original) {
    vec3_t direction, result[3], previous;
    int i, weapon;
    qboolean displacement;
    if(!cent || !axis) return qfalse;
    weapon = cent->currentState.weapon;
    if(weapon < 0 || weapon >= WP_NUM_WEAPONS) return qfalse;
    displacement = weapon == WP_MORTAR_SET || (original &&
        (weapon == WP_PANZERFAUST || weapon == WP_GPG40 || weapon == WP_M7));
    VectorCopy(cent->rawOrigin, previous);
    if(displacement) {
        if(VectorCompare(previous, vec3_origin)) {
            VectorSubtract(cent->lerpOrigin, cent->currentState.pos.trBase, direction);
            VectorCopy(cent->lerpOrigin, previous);
        } else {
            VectorSubtract(cent->lerpOrigin, previous, direction);
            if(!VectorCompare(cent->lerpOrigin, previous)) VectorCopy(cent->lerpOrigin, previous);
        }
    } else VectorCopy(cent->currentState.pos.trDelta, direction);
    for(i = 0; i < 3; ++i)
        if(!(direction[i] >= -FLT_MAX && direction[i] <= FLT_MAX)) return qfalse;
    memset(result, 0, sizeof(result));
    if(VectorNormalize2(direction, result[0]) == 0) result[0][2] = 1;
    if(displacement) VectorCopy(previous, cent->rawOrigin);
    /* Preserve the original pre-spin angle snapshot for other consumers.
     * ET protocol retains its previous lerpAngles behavior. */
    if(original) AxisToAngles(result, cent->lerpAngles);
    RotateAroundDirection(result, cent->currentState.pos.trType == TR_STATIONARY ?
        cent->currentState.time : time / 4);
    memcpy(axis, result, sizeof(result));
    return qtrue;
}
