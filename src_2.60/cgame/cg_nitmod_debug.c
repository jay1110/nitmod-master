#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_debug.h"
#include <float.h>

vmCvar_t cg_drawHitbox;
vmCvar_t demo_wallHack;
static qhandle_t transGunWhiteShader, demoRedShader, transGunGreenShader,
    demoBlueShader, constructionShader;

void CG_NitmodRegisterDebugMedia(void) {
    transGunWhiteShader = demoRedShader = transGunGreenShader =
        demoBlueShader = constructionShader = 0;
    if(!NITMOD_UsesOriginalProtocol()) return;
    transGunWhiteShader = trap_R_RegisterShader("textures/sfx/transgunWhite");
    demoRedShader = trap_R_RegisterShader("textures/sfx/transgunRed");
    transGunGreenShader = trap_R_RegisterShader("textures/sfx/transgunGreen");
    demoBlueShader = trap_R_RegisterShader("textures/sfx/transgunBlue");
    constructionShader = trap_R_RegisterShader("textures/sfx/construction");
}

/* Original CG_AddPlayerWeapon/CG_AddViewWeapon draw-gun inspection modes.
 * Mode 1 is normal media; 2..6 replace every first-person weapon part. */
qhandle_t CG_NitmodViewWeaponShader(int drawGun) {
    qhandle_t shader;
    if(!NITMOD_UsesOriginalProtocol()) return 0;
    switch(drawGun) {
    case 2: shader = transGunWhiteShader; break;
    case 3: shader = demoRedShader; break;
    case 4: shader = transGunGreenShader; break;
    case 5: shader = demoBlueShader; break;
    case 6: shader = constructionShader; break;
    default: return 0;
    }
    return shader > 0 ? shader : 0;
}

qhandle_t CG_NitmodDemoPlayerShader(team_t team) {
    qhandle_t shader;
    /* Demo-only even when a modified engine fails to enforce CVAR_CHEAT. */
    if(!cg.demoPlayback || !demo_wallHack.integer || !NITMOD_UsesOriginalProtocol()) return 0;
    shader = team == TEAM_AXIS ? demoRedShader : demoBlueShader;
    return shader > 0 ? shader : 0;
}

/* Shared original transgun assets; this grants no entity visibility.
 * Only the already-authorized mine renderer consumes this accessor. */
qhandle_t CG_NitmodMineTeamShader(team_t team) {
    qhandle_t shader;
    if(!NITMOD_UsesOriginalProtocol() || !(NITMOD_SimpleConfig()->misc & 16)) return 0;
    if(team != TEAM_AXIS && team != TEAM_ALLIES) return 0;
    shader = team == TEAM_AXIS ? demoRedShader : demoBlueShader;
    return shader > 0 ? shader : 0;
}

static qboolean DebugVector(const vec3_t v) {
    int i;
    for(i = 0; i < 3; ++i) if(!(v[i] >= -FLT_MAX && v[i] <= FLT_MAX)) return qfalse;
    return qtrue;
}

/* Original CG_EntityEvent 104..106 and CG_BotDebugLine (ELF 0x5efe0).
 * These fields carry vectors, not player indices or weapon identifiers. */
int CG_NitmodDebugEventLines(const entityState_t *es, int event, nitmodDebugLine_t lines[12]) {
    vec3_t corners[8], half;
    const float *axes[3];
    int i, j, axis, count = 0, color;
    if(!es || !lines) return 0;
    memset(lines, 0, sizeof(*lines) * 12);
    if(!DebugVector(es->pos.trBase) || !DebugVector(es->origin2) ||
       !DebugVector(es->angles) || !DebugVector(es->angles2)) return 0;
    if(event == 104) {
        VectorCopy(es->origin2, lines[0].start);
        VectorCopy(es->pos.trBase, lines[0].end);
        VectorCopy(es->angles2, lines[0].color);
        count = 1;
    } else if(event == 105) {
        axes[0] = es->origin2; axes[1] = es->angles; axes[2] = es->angles2;
        for(i = 0; i < 3; ++i) {
            VectorCopy(es->pos.trBase, lines[i].start);
            VectorMA(es->pos.trBase, 5, axes[i], lines[i].end);
            lines[i].color[i] = 1;
        }
        count = 3;
    } else if(event == 106) {
        if(es->effect1Time < 0 || es->effect2Time < 0 || es->effect3Time < 0) return 0;
        /* Integer division before conversion is intentional in the original. */
        VectorSet(half, es->effect1Time / 2, es->effect2Time / 2, es->effect3Time / 2);
        axes[0] = es->origin2; axes[1] = es->angles; axes[2] = es->angles2;
        color = es->otherEntityNum < 0 ? 0 : es->otherEntityNum > 31 ? 31 : es->otherEntityNum;
        for(i = 0; i < 8; ++i) {
            VectorCopy(es->pos.trBase, corners[i]);
            for(axis = 0; axis < 3; ++axis)
                VectorMA(corners[i], i & (1 << axis) ? half[axis] : -half[axis], axes[axis], corners[i]);
        }
        for(i = 0; i < 8; ++i) for(axis = 0; axis < 3; ++axis) {
            if(i & (1 << axis)) continue;
            VectorCopy(corners[i], lines[count].start);
            VectorCopy(corners[i | (1 << axis)], lines[count].end);
            VectorCopy(g_color_table[color], lines[count].color);
            ++count;
        }
    }
    for(i = 0; i < count; ++i) {
        if(!DebugVector(lines[i].start) || !DebugVector(lines[i].end)) return 0;
        for(j = 0; j < 3; ++j) {
            if(lines[i].color[j] < 0) lines[i].color[j] = 0;
            if(lines[i].color[j] > 1) lines[i].color[j] = 1;
        }
    }
    return count;
}

void CG_NitmodDebugEvent(const entityState_t *es, int event) {
    nitmodDebugLine_t lines[12];
    double end = (double)cg.time + cg_railTrailTime.value;
    int i, count;
    localEntity_t *le;
    if(!(cg_railTrailTime.value > 0 && (double)cg_railTrailTime.value <= 2147483647.0) ||
       !(end > cg.time && end <= 2147483647.0) || (int)end <= cg.time) return;
    count = CG_NitmodDebugEventLines(es, event, lines);
    if(!count) return;
    if(!cgs.media.railCoreShader) cgs.media.railCoreShader = trap_R_RegisterShader("railCore");
    if(cgs.media.railCoreShader <= 0) return;
    for(i = 0; i < count; ++i) {
        le = CG_AllocLocalEntity();
        le->leType = LE_FADE_RGB; le->startTime = cg.time; le->endTime = (int)end;
        le->lifeRate = 1.f / (float)((double)le->endTime - le->startTime);
        le->refEntity.reType = RT_RAIL_CORE;
        le->refEntity.shaderTime = cg.time / 1000.f;
        le->refEntity.customShader = cgs.media.railCoreShader;
        VectorCopy(lines[i].start, le->refEntity.origin);
        VectorCopy(lines[i].end, le->refEntity.oldorigin);
        VectorCopy(lines[i].color, le->color); le->color[3] = 1;
        AxisClear(le->refEntity.axis);
    }
}

/* Original CG_RailTrail/CG_RailTrail2: stable group/segment IDs refresh
 * existing effects. Corner and edge order matches CG_RailTrail_part_5. */
void CG_NitmodRailEvent(const entityState_t *es) {
    static const int edges[12][2] = {
        {0,1},{0,2},{0,3},{7,4},{7,5},{7,6},
        {2,6},{6,1},{1,5},{2,4},{4,3},{3,5}
    };
    static const int masks[8] = {0,1,2,4,6,5,3,7};
    vec3_t corners[8], color;
    double end = (double)cg.time + cg_railTrailTime.value;
    int i, j, count;
    if(!es || !DebugVector(es->origin2) || !DebugVector(es->pos.trBase) ||
       !DebugVector(es->angles)) return;
    if(!(cg_railTrailTime.value > 0 && (double)cg_railTrailTime.value <= 2147483647.0) ||
       !(end > cg.time && end <= 2147483647.0) || (int)end <= cg.time) return;
    if(cgs.media.railCoreShader <= 0) return;
    for(j = 0; j < 3; ++j) {
        color[j] = es->angles[j] / 255.f;
        if(color[j] < 0) color[j] = 0;
        if(color[j] > 1) color[j] = 1;
        for(i = 0; i < 8; ++i)
            corners[i][j] = masks[i] & (1 << j) ? es->pos.trBase[j] : es->origin2[j];
    }
    count = es->dmgFlags ? 12 : 1;
    for(i = 0; i < count; ++i) {
        int segment = es->dmgFlags ? i + 1 : -1;
        localEntity_t *le = CG_NitmodFindRailEntity(es->effect1Time, segment);
        if(!le) le = CG_AllocLocalEntity();
        le->nitmodRailGroup = es->effect1Time;
        le->nitmodRailSegment = segment;
        le->leType = LE_FADE_RGB;
        le->startTime = cg.time; le->endTime = (int)end;
        le->lifeRate = 1.f / (float)((double)le->endTime - le->startTime);
        memset(&le->refEntity, 0, sizeof(le->refEntity));
        le->refEntity.reType = RT_RAIL_CORE;
        le->refEntity.shaderTime = cg.time / 1000.f;
        le->refEntity.customShader = cgs.media.railCoreShader;
        VectorCopy(corners[es->dmgFlags ? edges[i][0] : 0], le->refEntity.origin);
        VectorCopy(corners[es->dmgFlags ? edges[i][1] : 7], le->refEntity.oldorigin);
        VectorCopy(color, le->color); le->color[3] = 1;
        AxisClear(le->refEntity.axis);
    }
}

static void DebugBox(nitmodDebugGeometry_t *out, const vec3_t origin,
    const vec3_t mins, const vec3_t maxs) {
    nitmodDebugBox_t box;
    int i;
    if(out->count >= 4) return;
    VectorAdd(origin, mins, box.mins); VectorAdd(origin, maxs, box.maxs);
    if(!DebugVector(box.mins) || !DebugVector(box.maxs)) return;
    for(i = 0; i < 3; ++i) if(box.mins[i] > box.maxs[i]) return;
    out->boxes[out->count++] = box;
}

/* Original CG_Player (sorted cgame_players.c, 1656-1743). The predicted
 * bounds/stance are deliberately used for every displayed entity, as in
 * the reference; this is a diagnostic, not authoritative server hitboxes. */
void CG_NitmodDebugGeometry(const centity_t *cent, const playerState_t *ps,
    const pmoveExt_t *ext, int flags, nitmodDebugGeometry_t *out) {
    vec3_t mins, maxs, forward, origin;
    unsigned int solid;
    if(!out) return;
    memset(out, 0, sizeof(*out));
    if(!cent || !DebugVector(cent->lerpOrigin)) return;
    solid = (unsigned int)cent->currentState.solid;
    if((flags & 4) && solid && solid != SOLID_BMODEL) {
        float radius = (float)(solid & 255);
        VectorSet(mins, -radius, -radius, -(float)((solid >> 8) & 255));
        VectorSet(maxs, radius, radius, (float)((int)((solid >> 16) & 255) - 32));
        DebugBox(out, cent->lerpOrigin, mins, maxs);
    }
    if(!(flags & 1) || !ps) return;
    VectorCopy(ps->mins, mins); VectorCopy(ps->maxs, maxs);
    if(ps->eFlags & EF_PRONE) maxs[2] -= ps->standViewHeight - PRONE_VIEWHEIGHT + 8;
    else if(ps->pm_flags & PMF_DUCKED) maxs[2] = ps->crouchMaxZ;
    DebugBox(out, cent->lerpOrigin, mins, maxs);
    if(!(ps->eFlags & EF_PRONE) || !ext || !DebugVector(cent->lerpAngles)) return;
    AngleVectors(cent->lerpAngles, forward, NULL, NULL);
    forward[2] = 0; VectorNormalizeFast(forward);
    VectorMA(cent->lerpOrigin, -32, forward, origin);
    origin[2] += ext->proneLegsOffset;
    DebugBox(out, origin, playerlegsProneMins, playerlegsProneMaxs);
    VectorMA(cent->lerpOrigin, 12, forward, origin);
    VectorSet(mins, -6, -6, -22); VectorSet(maxs, 6, 6, -10);
    DebugBox(out, origin, mins, maxs);
}

static void DebugLine(const vec3_t start, const vec3_t end) {
    refEntity_t line;
    if(!DebugVector(start) || !DebugVector(end)) return;
    memset(&line, 0, sizeof(line));
    line.reType = RT_RAIL_CORE;
    line.customShader = cgs.media.railCoreShader;
    line.shaderRGBA[0] = 63; line.shaderRGBA[1] = 127;
    line.shaderRGBA[2] = line.shaderRGBA[3] = 255;
    VectorCopy(start, line.origin); VectorCopy(end, line.oldorigin);
    AxisClear(line.axis);
    trap_R_AddRefEntityToScene(&line);
}

void CG_NitmodDrawPlayerDebug(const centity_t *cent, const refEntity_t *body) {
    nitmodDebugGeometry_t geometry;
    int b, corner, axis, flags = cg_drawHitbox.integer & 7;
    if(!flags || !cent || !body || !body->hModel || !NITMOD_UsesOriginalProtocol() ||
       cgs.media.railCoreShader <= 0) return;
    CG_NitmodDebugGeometry(cent, &cg.predictedPlayerState, &cg.pmext, flags, &geometry);
    for(b = 0; b < geometry.count; ++b) {
        const nitmodDebugBox_t *box = &geometry.boxes[b];
        for(corner = 0; corner < 8; ++corner) for(axis = 0; axis < 3; ++axis) {
            vec3_t start, end;
            int i;
            if(corner & (1 << axis)) continue;
            for(i = 0; i < 3; ++i) start[i] = corner & (1 << i) ? box->maxs[i] : box->mins[i];
            VectorCopy(start, end); end[axis] = box->maxs[axis];
            DebugLine(start, end);
        }
    }
    if(flags & 2) {
        orientation_t tag;
        vec3_t start, end, axes[3], bodyAxis[3];
        memset(&tag, 0, sizeof(tag));
        if(trap_R_LerpTag(&tag, body, "tag_head", 0) < 0) return;
        VectorCopy(body->origin, start);
        for(axis = 0; axis < 3; ++axis) VectorMA(start, tag.origin[axis], body->axis[axis], start);
        memcpy(bodyAxis, body->axis, sizeof(bodyAxis));
        MatrixMultiply(tag.axis, bodyAxis, axes);
        for(axis = 0; axis < 3; ++axis) {
            VectorMA(start, 32, axes[axis], end); DebugLine(start, end);
        }
    }
}
