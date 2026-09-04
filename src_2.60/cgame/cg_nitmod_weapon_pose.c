#include "cg_local.h"
#include "cg_nitmod_weapon_pose.h"

/* Original cgame ELF 0xbf590. Keep visual offsets out of player movement. */
void CG_NitmodCalculateWeaponPosition(const cg_t *view, int weapons,
                                    vec3_t origin, vec3_t angles) {
    const playerState_t *ps = &view->predictedPlayerState;
    float factor, scale, drift, divisor;
    double elapsed;
    vec3_t right;
    VectorCopy(view->refdef_current->vieworg, origin);
    VectorCopy(view->refdefViewAngles, angles);
    if(ps->eFlags & EF_MOUNTEDTANK) angles[PITCH] /= 1.2f;
    if(!view->renderingThirdPerson &&
       (ps->weapon == WP_MORTAR_SET || ps->weapon == WP_MOBILE_MG42_SET) &&
       ps->weaponstate != WEAPON_RAISING)
        angles[PITCH] = view->pmext.mountedWeaponAngles[PITCH];

    /* Widen before arithmetic; a restarted clock must not extrapolate pose. */
    factor = 0;
    if(ps->eFlags & EF_PRONE_MOVING) {
        elapsed = (double)view->time - view->proneMovingTime;
        if(elapsed > 0) factor = elapsed >= 200 ? 1 : (float)(elapsed / 200);
    } else {
        elapsed = (double)view->time + view->proneMovingTime;
        if(elapsed >= 0 && elapsed < 200) factor = 1 - (float)(elapsed / 200);
    }
    VectorMA(origin, -20 * factor, view->refdef_current->viewaxis[0], origin);
    VectorMA(origin, 3 * factor, view->refdef_current->viewaxis[1], origin);

    if(ps->leanf != 0 && ps->weaponstate != WEAPON_FIRINGALT) {
        if(weapons & 256) {
            AngleVectors(view->refdefViewAngles, NULL, right, NULL);
            VectorMA(origin, ps->leanf * .125f, right, origin);
        } else {
            switch(ps->weapon) {
            case WP_FLAMETHROWER: case WP_KAR98: case WP_CARBINE:
            case WP_K43: case WP_GPG40: case WP_M7: divisor = 4; break;
            case WP_GARAND: divisor = 6; break;
            default: divisor = 2; break;
            }
            angles[ROLL] -= ps->leanf / divisor;
            AngleVectors(angles, NULL, right, NULL);
            VectorMA(origin, angles[ROLL], right, origin);
            angles[PITCH] += (float)fabs(ps->leanf) * .5f;
            AngleVectors(view->refdefViewAngles, NULL, right, NULL);
            VectorMA(origin, -ps->leanf * .25f, right, origin);
        }
    }
    scale = (view->bobcycle & 1) ? -view->xyspeed : view->xyspeed;
    angles[ROLL] += scale * view->bobfracsin * .005f;
    angles[YAW] += scale * view->bobfracsin * .01f;
    angles[PITCH] += view->xyspeed * view->bobfracsin * .005f;
    elapsed = (double)view->time - view->landTime;
    if(elapsed >= 0 && elapsed < 150)
        origin[2] += (float)elapsed * view->landChange * .25f / 150;
    else if(elapsed >= 150 && elapsed < 450)
        origin[2] += (float)(450 - elapsed) * view->landChange * .25f / 300;
    if(!(ps->eFlags & EF_MOUNTEDTANK) && ps->weapon != WP_MORTAR_SET &&
       ps->weapon != WP_MOBILE_MG42_SET) {
        drift = (float)sin(view->time * .001) * 80 * .01f;
        angles[PITCH] += drift; angles[YAW] += drift; angles[ROLL] += drift;
    }
    VectorSubtract(angles, view->kickAngles, angles);
}
