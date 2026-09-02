#include "g_local.h"

/* Original playerState eFlags mask 0x880001. ET 2.60 names the third bit
 * EF_SPARE0; preserve its tested bit without guessing a Nitmod stance name. */
#define NITMOD_MINE_BROAD_CONTACT_FLAGS (EF_DEAD | EF_PRONE | EF_SPARE0)

/* Initial-trigger eligibility only; does not replace Omni-bot event delivery. */
qboolean G_NITMOD_MineBotContact(gentity_t *candidate, team_t mineTeam,
                               qboolean spotted, int omniBotFlags) {
    if(!candidate || !candidate->client) return qfalse;
    if(!(omniBotFlags & 0x20) && (candidate->r.svFlags & SVF_BOT)) {
        if(candidate->client->sess.sessionTeam == mineTeam || spotted) return qfalse;
    }
    return qtrue;
}

/* Original G_LandmineThink friendly-fire bits 0x20/0x100. Owner identity is the
 * entityState client number, not pointer equality or entity number. */
qboolean G_NITMOD_MineTeamContact(gentity_t *candidate, gentity_t *owner,
                                team_t mineTeam, int friendlyFireFlags) {
    if(!candidate || !candidate->client) return qfalse;
    if(owner && (friendlyFireFlags & 0x20) &&
       candidate->client->sess.sessionTeam == mineTeam &&
       candidate->s.clientNum != owner->s.clientNum) return qfalse;
    /* Original weapon 0x14 resolves to pliers through BG_RegisterWeapon's
     * filename table. Use the native enum, and the original entityState field. */
    if(owner && (friendlyFireFlags & 0x100) &&
       candidate->s.clientNum == owner->s.clientNum &&
       candidate->s.weapon != WP_PLIERS) return qfalse;
    return qtrue;
}

qboolean sEntWillTriggerMine(gentity_t *ent, gentity_t *mine) {
    vec3_t distance;
    double delta;
    int axis;
    if(!ent || !mine || ent->s.eType != ET_PLAYER || !ent->client) return qfalse;
    if(!n_preciseLandmineTrigger.integer || mine->s.onFireStart ||
       (ent->client->ps.eFlags & NITMOD_MINE_BROAD_CONTACT_FLAGS)) {
        VectorSubtract(mine->r.currentOrigin, ent->r.currentOrigin, distance);
        return VectorLengthSquared(distance) <= 4096.0f && fabs(distance[2]) < 45.0f;
    }
    /* Original x87 conversion truncates toward zero, then accepts [-23,23].
     * For finite coordinates that is exactly (-24,24); comparisons also
     * reject NaN/infinity without an undefined out-of-range integer cast.
     * Keep the original subtract-min/subtract-max expression, not a center. */
    for(axis = 1; axis >= 0; --axis) {
        delta = ((double)mine->r.currentOrigin[axis] - (mine->r.mins[axis] + 3.0))
              - (mine->r.maxs[axis] - 3.0) - ent->r.currentOrigin[axis];
        if(!(delta > -24.0 && delta < 24.0)) return qfalse;
    }
    delta = ((double)mine->r.currentOrigin[2] - mine->r.mins[2])
          - mine->r.maxs[2] - ent->r.currentOrigin[2];
    return fabs(delta) < 45.0;
}
