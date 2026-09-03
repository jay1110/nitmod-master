#include "g_local.h"
#include <limits.h>

/* Original fire_grenade kick branch, independent of damageability. The
 * engine computes world abs bounds when linking the initialized missile. */
void G_NITMOD_ConfigureCanisterKick(gentity_t *missile) {
    if(!missile || !g_canisterKick.integer) return;
    switch(missile->s.weapon) {
    case WP_GRENADE_LAUNCHER: case WP_GRENADE_PINEAPPLE:
    case WP_SMOKE_MARKER: case WP_SMOKE_BOMB:
        missile->r.contents = CONTENTS_CORPSE;
        VectorSet(missile->r.mins, -4, -4, 0);
        VectorSet(missile->r.maxs, 4, 4, 6);
        VectorCopy(missile->r.mins, missile->r.absmin);
        VectorCopy(missile->r.maxs, missile->r.absmax);
        break;
    default: break;
    }
}

static float KickRound(float value) {
    double rounded = value < 0 ? ceil((double)value) : floor((double)value);
    /* 0xfd44a sets x87 RC=11: truncate toward zero, despite Ghidra's ROUND.
     * Avoid overflowing float-to-int conversion for extreme Cvar settings. */
    if(rounded > INT_MAX) rounded = INT_MAX;
    if(rounded < INT_MIN) rounded = INT_MIN;
    return (float)rounded;
}

/* Original G_CanisterKick 0xfd070. Only mapped native projectile IDs;
 * poison weapons remain unreconstructed. */
void G_CanisterKick(gentity_t *actor) {
    vec3_t angles, forward, center, mins, maxs;
    int entities[MAX_GENTITIES], count, i;
    gentity_t *missile;
    if(!g_canisterKick.integer || !actor || !actor->client ||
       (actor->client->ps.pm_flags & PMF_LIMBO) ||
       actor->client->ps.pm_type == PM_DEAD ||
       (actor->client->ps.eFlags & EF_PRONE)) return;
    VectorSet(angles, 0, actor->client->ps.viewangles[YAW], 0);
    AngleVectors(angles, forward, NULL, NULL);
    VectorMA(actor->r.currentOrigin, 24, forward, center);
    VectorSet(mins, center[0] - 32, center[1] - 32, center[2] - 24);
    VectorSet(maxs, center[0] + 32, center[1] + 32, center[2] + 8);
    count = trap_EntitiesInBox(mins, maxs, entities, MAX_GENTITIES);
    if(count > MAX_GENTITIES) count = MAX_GENTITIES;
    for(i = 0; i < count; ++i) {
        if(entities[i] < 0 || entities[i] >= MAX_GENTITIES) continue;
        missile = &g_entities[entities[i]];
        if(missile->s.eType != ET_MISSILE) continue;
        /* Original stops at the first missile, even if it cannot be kicked. */
        switch(missile->s.weapon) {
        case WP_GRENADE_LAUNCHER: case WP_GRENADE_PINEAPPLE:
        case WP_SMOKE_MARKER: case WP_SMOKE_BOMB:
            break;
        default: return;
        }
        VectorCopy(actor->client->ps.viewangles, angles);
        if(angles[PITCH] > -15) angles[PITCH] = -15;
        AngleVectors(angles, forward, NULL, NULL);
        missile->s.pos.trType = TR_GRAVITY;
        missile->s.pos.trTime = level.time < INT_MIN + 50 ? INT_MIN : level.time - 50;
        missile->s.pos.trBase[2] += 30;
        VectorCopy(missile->s.pos.trBase, missile->r.currentOrigin);
        VectorScale(forward, (float)g_canisterKick.integer * 10, missile->s.pos.trDelta);
        missile->s.pos.trDelta[2] += (float)g_canisterKick.integer * 2;
        missile->s.pos.trDelta[0] = KickRound(missile->s.pos.trDelta[0]);
        missile->s.pos.trDelta[1] = KickRound(missile->s.pos.trDelta[1]);
        missile->s.pos.trDelta[2] = KickRound(missile->s.pos.trDelta[2]);
        /* Original +0x368 is active (set by weapon_callAirStrike, cleared
         * on denial). Never reassign an already activated strike's owner. */
        if(g_canisterKickOwner.integer &&
           (missile->s.weapon != WP_SMOKE_MARKER || !missile->active)) {
            missile->parent = actor;
            missile->r.ownerNum = actor->s.number;
            missile->s.teamNum = actor->client->sess.sessionTeam;
        }
        return;
    }
}
