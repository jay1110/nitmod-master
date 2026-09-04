#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_hud.h"
#include "cg_nitmod_names.h"
#include "cg_nitmod_locations.h"
#include <float.h>

vmCvar_t cg_woundedNames;
typedef struct {
    float x, y;
    vec3_t traceOrigin;
    char name[MAX_NAME_LENGTH];
} woundedName_t;
static woundedName_t names[32];
static int nameCount;

typedef struct {
    float x, y, scale;
    vec3_t origin;
    int client;
    char text[96];
} floatingName_t;
static floatingName_t floatingNames[16];
static int floatingCount;
enum { DYNAMITE_NAME_BASE = MAX_CLIENTS + NITMOD_MAX_LOCATIONS,
       WORLD_NAME_KEYS = DYNAMITE_NAME_BASE + MAX_GENTITIES };
static nitmodNameFade_t nameFades[WORLD_NAME_KEYS];
static char fadeNames[WORLD_NAME_KEYS][96];
static int dynamiteStarts[MAX_GENTITIES];

qboolean CG_NitmodProjectName(const vec3_t origin, float *x, float *y) {
    vec3_t delta, forward, right, up;
    float depth, screenX, screenY;
    int i;
    if(!origin || !x || !y || !cg.refdef_current ||
       !(cg.refdef_current->fov_x > 0 && cg.refdef_current->fov_x < 180) ||
       !(cg.refdef_current->fov_y > 0 && cg.refdef_current->fov_y < 180)) return qfalse;
    VectorSubtract(origin, cg.refdef_current->vieworg, delta);
    for(i = 0; i < 3; ++i) if(!(fabs(delta[i]) <= FLT_MAX)) return qfalse;
    AngleVectors(cg.refdefViewAngles, forward, right, up);
    depth = DotProduct(delta, forward);
    if(!(depth >= .01f && depth <= FLT_MAX)) return qfalse;
    screenX = 320 + (96 / cg.refdef_current->fov_x) * (320 / depth) * DotProduct(delta, right);
    screenY = 240 - (102 / cg.refdef_current->fov_y) * (240 / depth) * DotProduct(delta, up);
    if(!(fabs(screenX) <= FLT_MAX) || !(fabs(screenY) <= FLT_MAX)) return qfalse;
    *x = screenX; *y = screenY;
    return qtrue;
}

static qboolean CG_NitmodQueueWorldName(int key, const char *text, const vec3_t origin) {
    floatingName_t *entry;
    float x, y, scale;
    if(key < 0 || key >= WORLD_NAME_KEYS || !text || !*text ||
       floatingCount >= 16 || !CG_NitmodProjectName(origin, &x, &y)) return qfalse;
    scale = CG_NitmodFloatNameScale(Distance(origin, cg.refdef_current->vieworg));
    entry = &floatingNames[floatingCount++];
    Q_strncpyz(entry->text, text, sizeof(entry->text));
    entry->x = x - CG_Text_Width_Ext(entry->text, scale, 0, &cgs.media.limboFont1) * .5f;
    entry->y = y - CG_Text_Height_Ext(entry->text, scale, 0, &cgs.media.limboFont1) * .5f;
    entry->scale = scale; entry->client = key; VectorCopy(origin, entry->origin);
    if(key < DYNAMITE_NAME_BASE && strcmp(fadeNames[key], entry->text)) {
        memset(&nameFades[key], 0, sizeof(nameFades[key]));
        Q_strncpyz(fadeNames[key], entry->text, sizeof(fadeNames[key]));
    }
    return qtrue;
}

qboolean CG_NitmodQueueLocationName(int index, const char *text, const vec3_t origin) {
    if(!NITMOD_UsesOriginalProtocol() || !cg.snap || !cg_draw2D.integer ||
       !(cg_locations.integer & 512) || index < 0 || index >= NITMOD_MAX_LOCATIONS) return qfalse;
    return CG_NitmodQueueWorldName(MAX_CLIENTS + index, text, origin);
}

void CG_NitmodNamesBeginFrame(void) { nameCount = floatingCount = 0; }

/* Original CG_DrawOnScreenNames uses last-visible and last-hidden timestamps,
 * and prevents reversals from jumping past the current alpha. */
float CG_NitmodNameFade(nitmodNameFade_t *fade, qboolean visible, int now) {
    double elapsed;
    float alpha;
    if(!fade) return 0;
    if(!fade->initialized || now < fade->lastTime) {
        memset(fade, 0, sizeof(*fade));
        fade->visibleTime = fade->hiddenTime = now;
        fade->initialized = qtrue;
    }
    fade->lastTime = now;
    if(visible) {
        fade->visibleTime = now;
        elapsed = (double)now - fade->hiddenTime;
        alpha = elapsed >= 250 ? 1 : (float)(elapsed / 250);
        if(alpha > fade->alpha) fade->alpha = alpha;
    } else {
        fade->hiddenTime = now;
        elapsed = (double)now - fade->visibleTime;
        alpha = elapsed >= 250 ? 0 : 1 - (float)(elapsed / 250);
        if(alpha < fade->alpha) fade->alpha = alpha;
    }
    return fade->alpha;
}

float CG_NitmodFloatNameScale(float distance) {
    float scale;
    if(!(distance >= 0)) return .125f;
    scale = .5f - distance / 3000.f;
    return scale < .125f ? .125f : scale;
}

static qboolean CG_NitmodSpectatorNamesEnabled(void) {
    return NITMOD_UsesOriginalProtocol() && cg.snap && cg_draw2D.integer &&
        cg.clientNum >= 0 && cg.clientNum < MAX_CLIENTS &&
        cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR &&
        (cgs.clientinfo[cg.clientNum].nitmodShoutcaster || NITMOD_SimpleConfig()->spectatorNames);
}

static qboolean CG_NitmodDynamiteNamesEnabled(void) {
    return NITMOD_UsesOriginalProtocol() && cg.snap && cg_draw2D.integer &&
        cg.clientNum >= 0 && cg.clientNum < MAX_CLIENTS &&
        cgs.clientinfo[cg.clientNum].team == TEAM_SPECTATOR &&
        cgs.clientinfo[cg.clientNum].nitmodShoutcaster;
}

qboolean CG_NitmodQueueDynamiteName(const centity_t *cent) {
    const entityState_t *es;
    vec3_t origin;
    char text[32];
    double elapsed;
    int key;
    if(!cent || !CG_NitmodDynamiteNamesEnabled()) return qfalse;
    es = &cent->currentState;
    if(es->eType != ET_MISSILE || es->weapon != WP_DYNAMITE ||
       es->number < MAX_CLIENTS || es->number >= ENTITYNUM_WORLD ||
       es->teamNum < 1 || es->teamNum > 3) return qfalse;
    elapsed = ((double)cg.time - es->effect1Time) / 1000;
    /* Original displays 30 - trunc(elapsed), not the crosshair's time2 duration. */
    Com_sprintf(text, sizeof(text), "^1%i", 30 - (int)elapsed);
    VectorCopy(cent->lerpOrigin, origin); origin[2] += 20;
    if(es->clientNum == cg.snap->ps.clientNum ? (cg.snap->ps.pm_flags & PMF_DUCKED) : es->animMovetype)
        origin[2] -= 18;
    key = DYNAMITE_NAME_BASE + es->number;
    if(dynamiteStarts[es->number] != es->effect1Time) {
        memset(&nameFades[key], 0, sizeof(nameFades[key]));
        dynamiteStarts[es->number] = es->effect1Time;
    }
    return CG_NitmodQueueWorldName(key, text, origin);
}

qboolean CG_NitmodQueueSpectatorName(const centity_t *cent) {
    const clientInfo_t *ci;
    const entityState_t *es;
    vec3_t origin;
    int client;
    if(!cent || !CG_NitmodSpectatorNamesEnabled() || !cg.refdef_current || floatingCount >= 16) return qfalse;
    es = &cent->currentState; client = es->clientNum;
    if(es->eType != ET_PLAYER || client < 0 || client >= MAX_CLIENTS || es->number != client) return qfalse;
    ci = &cgs.clientinfo[client];
    if(!ci->infoValid || !ci->name[0] || (ci->team != TEAM_AXIS && ci->team != TEAM_ALLIES)) return qfalse;
    VectorCopy(cent->lerpOrigin, origin);
    origin[2] += es->eFlags & (EF_DEAD | EF_PRONE) ? 8 : 48;
    if(client == cg.snap->ps.clientNum ? (cg.snap->ps.pm_flags & PMF_DUCKED) : es->animMovetype)
        origin[2] -= 18;
    return CG_NitmodQueueWorldName(client, ci->name, origin);
}

void CG_NitmodDrawSpectatorNames(void) {
    int i, count = floatingCount;
    vec3_t mins = {-1,-1,-1}, maxs = {1,1,1};
    vec4_t color = {1,1,1,1};
    nitmodHudAnchor_t previous;
    floatingCount = 0;
    if(!NITMOD_UsesOriginalProtocol() || !cg.snap || !cg_draw2D.integer || !cg.refdef_current) return;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    for(i = 0; i < count; ++i) {
        trace_t trace;
        floatingName_t *entry = &floatingNames[i];
        if(entry->client >= DYNAMITE_NAME_BASE) {
            if(!CG_NitmodDynamiteNamesEnabled()) continue;
        } else if(entry->client < MAX_CLIENTS ? !CG_NitmodSpectatorNamesEnabled() : !(cg_locations.integer & 512)) continue;
        CG_Trace(&trace, cg.refdef_current->vieworg, mins, maxs, entry->origin, -1, CONTENTS_SOLID);
        color[3] = CG_NitmodNameFade(&nameFades[entry->client], trace.fraction >= 1, cg.time);
        if(color[3] > 0) CG_Text_Paint_Ext(entry->x, entry->y, entry->scale, entry->scale,
            color, entry->text, 0, 0, 7, &cgs.media.limboFont1);
    }
    CG_NitmodHudAnchor(previous);
}

void CG_NitmodNamesReset(void) {
    CG_NitmodNamesBeginFrame();
    memset(nameFades, 0, sizeof(nameFades));
    memset(fadeNames, 0, sizeof(fadeNames));
    memset(dynamiteStarts, 0, sizeof(dynamiteStarts));
}

qboolean CG_NitmodQueueWoundedName(const centity_t *cent) {
    const entityState_t *es = &cent->currentState;
    const clientInfo_t *ci;
    vec3_t position, delta, forward, right, up;
    float depth, distance, width, height;
    int client = es->clientNum;
    qboolean medic;
    woundedName_t *entry;
    if(!NITMOD_UsesOriginalProtocol() || !cg.snap || !cg.refdef_current ||
       !cg_draw2D.integer || !cg_woundedNames.integer || cg.demoPlayback ||
       client < 0 || client >= MAX_CLIENTS || es->number != client ||
       client == cg.snap->ps.clientNum || nameCount >= 32) return qfalse;
    ci = &cgs.clientinfo[client];
    if(ci->team != cg.snap->ps.persistant[PERS_TEAM] ||
       (ci->team != TEAM_AXIS && ci->team != TEAM_ALLIES) || !ci->name[0]) return qfalse;
    medic = cg.snap->ps.stats[STAT_HEALTH] <= 0;
    if(medic) {
        if(ci->cls != PC_MEDIC || ci->health <= 0) return qfalse;
    } else if(!(es->eFlags & EF_DEAD) || cg.snap->ps.stats[STAT_PLAYER_CLASS] != PC_MEDIC ||
              cgs.gametype == 8) return qfalse;
    VectorCopy(cent->lerpOrigin, position);
    if(!medic) {
        VectorSubtract(cg.predictedPlayerState.origin, position, delta);
        distance = VectorLength(delta);
        if(distance < 64 || distance > 1600) return qfalse;
        position[2] -= 6;
    } else position[2] += 48;
    if(!(cg.refdef_current->fov_x > 0) || !(cg.refdef_current->fov_y > 0)) return qfalse;
    AngleVectors(cg.refdefViewAngles, forward, right, up);
    VectorSubtract(position, cg.refdef_current->vieworg, delta);
    depth = DotProduct(delta, forward);
    if(!(depth >= .01f)) return qfalse;
    width = CG_Text_Width_Ext(ci->name, .18f, 0, &cgs.media.limboFont1);
    height = CG_Text_Height_Ext(ci->name, .18f, 0, &cgs.media.limboFont1);
    entry = &names[nameCount++];
    /* Original projection constants, not a replacement tan(FOV/2) formula. */
    entry->x = 320 + (96 / cg.refdef_current->fov_x) * (320 / depth) * DotProduct(delta, right) - width * .5f;
    entry->y = 240 - (102 / cg.refdef_current->fov_y) * (240 / depth) * DotProduct(delta, up) - height * .5f;
    VectorCopy(position, entry->traceOrigin);
    entry->traceOrigin[0] -= height * .5f;
    entry->traceOrigin[1] -= width * .5f;
    Q_strncpyz(entry->name, ci->name, sizeof(entry->name));
    return qtrue;
}

void CG_NitmodDrawWoundedNames(void) {
    int i, count = nameCount;
    vec3_t mins = {-1,-1,-1}, maxs = {1,1,1};
    vec4_t color = {1,1,1,.75f};
    nitmodHudAnchor_t previous;
    nameCount = 0;
    if(!cg.refdef_current || !cg_draw2D.integer || !cg_woundedNames.integer || cg.demoPlayback ||
       !NITMOD_UsesOriginalProtocol()) return;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    for(i = 0; i < count; ++i) {
        trace_t trace;
        CG_Trace(&trace, cg.refdef_current->vieworg, mins, maxs, names[i].traceOrigin, -1, CONTENTS_SOLID);
        if(trace.fraction >= 1)
            CG_Text_Paint_Ext(names[i].x, names[i].y, .18f, .18f, color, names[i].name,
                0, 0, 7, &cgs.media.limboFont1);
    }
    CG_NitmodHudAnchor(previous);
}
