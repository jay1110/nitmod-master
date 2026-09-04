#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_hud.h"
#include "cg_nitmod_hints.h"

vmCvar_t cg_objectiveHints, cg_artilleryHints;

/* Receives typed hint IDs: wire IDs are normalized at snapshot ingestion,
 * while the fallback trace already produces native IDs. */
void CG_NitmodDrawCursorHint(const rectDef_t *rect) {
    qhandle_t icon;
    vec4_t color;
    float *fade, pulse = 0, half;
    nitmodHudAnchor_t previous;
    if(!rect || !cg.snap || !cg_cursorHints.integer) return;
    switch(cg.cursorHintIcon) {
    case HINT_NONE: case HINT_FORCENONE: return;
    case HINT_DOOR: icon = cgs.media.doorHintShader; break;
    case HINT_DOOR_ROTATING: icon = cgs.media.doorRotateHintShader; break;
    case HINT_DOOR_LOCKED: icon = cgs.media.doorLockHintShader; break;
    case HINT_DOOR_ROTATING_LOCKED: icon = cgs.media.doorRotateLockHintShader; break;
    case HINT_MG42: icon = cgs.media.mg42HintShader; break;
    case HINT_BREAKABLE: icon = cgs.media.breakableHintShader; break;
    case HINT_BREAKABLE_DYNAMITE: case HINT_DYNAMITE: icon = cgs.media.dynamiteHintShader; break;
    case HINT_CHAIR: icon = cgs.media.notUsableHintShader; break;
    case HINT_ALARM: icon = cgs.media.alarmHintShader; break;
    case HINT_HEALTH: icon = cgs.media.healthHintShader; break;
    case HINT_KNIFE: icon = cgs.media.knifeHintShader; break;
    case HINT_LADDER: icon = cgs.media.ladderHintShader; break;
    case HINT_BUTTON: icon = cgs.media.buttonHintShader; break;
    case HINT_WATER: icon = cgs.media.waterHintShader; break;
    case HINT_WEAPON: icon = cgs.media.weaponHintShader; break;
    case HINT_AMMO: icon = cgs.media.ammoHintShader; break;
    case HINT_POWERUP: icon = cgs.media.powerupHintShader; break;
    case HINT_INVENTORY: icon = cgs.media.inventoryHintShader; break;
    case HINT_BUILD: case HINT_CONSTRUCTIBLE: icon = cgs.media.buildHintShader; break;
    case HINT_DISARM: icon = cgs.media.disarmHintShader; break;
    case HINT_REVIVE: icon = cgs.media.reviveHintShader; break;
    case HINT_UNIFORM: icon = cgs.media.uniformHintShader; break;
    case HINT_LANDMINE: icon = cgs.media.landmineHintShader; break;
    case HINT_TANK: icon = cgs.media.tankHintShader; break;
    case HINT_SATCHELCHARGE: icon = cgs.media.satchelchargeHintShader; break;
    case HINT_PLYR_FRIEND: icon = cgs.media.friendShader; break;
    default: icon = cgs.media.usableHintShader; break;
    }
    if(icon <= 0 || !(fade = CG_FadeColor(cg.cursorHintTime, cg.cursorHintFade))) return;
    Vector4Copy(fade, color);
    if(cg_cursorHints.integer == 3) color[3] *= .5f + .5f * sin(cg.time / 150.0f);
    else if(cg_cursorHints.integer < 3)
        pulse = cg_cursorHints.integer == 2 ? (cg.cursorHintTime % 1000) / 100.0f :
            10 * (.5f + .5f * sin(cg.time / 150.0f));
    half = pulse * .5f;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    trap_R_SetColor(color);
    if(cg.cursorHintIcon == HINT_WEAPON || cg.cursorHintIcon == HINT_AMMO) {
        int weapon = cg.cursorHintValue;
        if(weapon > WP_NONE && weapon < WP_NUM_WEAPONS && cg_weapons[weapon].weaponIcon[1] > 0) {
            int width = CG_NitmodWeaponIconScale(weapon);
            CG_DrawPic(rect->x - width * half, rect->y - half,
                (rect->w + pulse) * width, rect->h + pulse, cg_weapons[weapon].weaponIcon[1]);
        }
        if(cg.cursorHintIcon == HINT_AMMO)
            CG_DrawPic(rect->x - half, rect->y - half, rect->w + pulse, rect->h + pulse, icon);
    } else {
        CG_DrawPic(rect->x - half, rect->y - half, rect->w + pulse, rect->h + pulse, icon);
        if(cg.cursorHintValue) {
            Vector4Set(color, 0, 0, 1, .5f);
            CG_FilledBar(rect->x, rect->y + rect->h + 4, rect->w, 8, color, NULL, NULL,
                cg.cursorHintValue / 255.0f, 0);
        }
    }
    trap_R_SetColor(NULL);
    CG_NitmodHudAnchor(previous);
}
static qhandle_t arrowShader, buildShader, artilleryShader;
static int artilleryPeriod;
static qboolean HintClient(int *client);
static struct { entityState_t state; int observed; qboolean active; } dynamiteHint;
static int mineOwner = -1, mineObserved;

const char *CG_NitmodCrosshairEntityName(int entity, qboolean construction) {
    int index;
    if(entity < MAX_CLIENTS || entity >= ENTITYNUM_WORLD) return "";
    index = construction ? CS_CONSTRUCTION_NAMES : CS_SCRIPT_MOVER_NAMES;
    return Info_ValueForKey(CG_ConfigString(index), va("%i", entity));
}

void CG_NitmodDrawCrosshairLabel(const char *text, const vec4_t color) {
    vec4_t tint;
    nitmodHudAnchor_t previous;
    if(!text || !*text || !color || !NITMOD_UsesOriginalProtocol()) return;
    Vector4Copy(color, tint);
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    CG_Text_Paint_Ext(320 - CG_Text_Width_Ext(text, .2f, 0, &cgs.media.limboFont2) * .5f,
        182, .2f, .2f, tint, text, 0, 0, 7, &cgs.media.limboFont2);
    CG_NitmodHudAnchor(previous);
}

void CG_NitmodDrawCrosshairHealth(int health, int maxHealth, const vec4_t color) {
    float fraction;
    vec4_t fill, background;
    nitmodHudAnchor_t previous;
    if(!color || !NITMOD_UsesOriginalProtocol() || maxHealth <= 0) return;
    fraction = health <= 0 ? 0 : health >= maxHealth ? 1 : (float)health / maxHealth;
    Vector4Set(fill, 1, fraction, fraction, (.25f + fraction * .5f) * color[3]);
    Vector4Set(background, 1, 1, 1, .25f * color[3]);
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    CG_FilledBar(270, 190, 100, 10, fill, NULL, background, fraction, 16);
    CG_NitmodHudAnchor(previous);
}

qboolean CG_NitmodDrawCrosshairPlayer(int client, qboolean disguised, int health, int maxHealth, const vec4_t color) {
    const clientInfo_t *ci;
    const char *name;
    int cls, rank, skill, width;
    qhandle_t icon;
    vec4_t tint;
    nitmodHudAnchor_t previous;
    if(!NITMOD_UsesOriginalProtocol() || client < 0 || client >= MAX_CLIENTS ||
       !color || !cg_drawCrosshairNames.integer) return qfalse;
    ci = &cgs.clientinfo[client];
    if(!ci->infoValid) return qfalse;
    name = disguised ? ci->disguiseName : ci->name;
    cls = disguised ? ((cg_entities[client].currentState.powerups >> 8) & 7) : ci->cls;
    rank = disguised ? ci->disguiseRank : ci->rank;
    if(!*name || cls < PC_SOLDIER || cls > PC_COVERTOPS) return qfalse;
    skill = BG_ClassSkillForClass(cls);
    if(skill < 0 || skill >= SK_NUM_SKILLS) return qfalse;
    Vector4Copy(color, tint);
    width = CG_Text_Width_Ext(name, .2f, 0, &cgs.media.limboFont2);
    icon = cgs.media.skillPics[skill];
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    trap_R_SetColor(color);
    /* Original HUD rank shaders are identical in the two team banks;
     * the native second slot is helmet media and must not be used here. */
    if((cg_drawCrosshairNames.integer & 2) && rank > 0 && rank < NUM_EXPERIENCE_LEVELS) {
        if(icon > 0) CG_DrawPic(304 - width * .5f, 170, 14, 14, icon);
        icon = rankicons[rank][0].shader;
    }
    if(icon > 0) CG_DrawPic(320 - width * .5f, 170, 14, 14, icon);
    trap_R_SetColor(NULL);
    CG_Text_Paint_Ext(336 - width * .5f, 182, .2f, .2f, tint, name, 0, 0, 7, &cgs.media.limboFont2);
    CG_NitmodDrawCrosshairHealth(health, maxHealth, color);
    CG_NitmodHudAnchor(previous);
    return qtrue;
}
enum { ORIGINAL_EXPLOSIVE_HINT = 13, ORIGINAL_BUILD_HINT = 31, ORIGINAL_ARTILLERY_HINT = 58 };

void CG_NitmodRegisterHintMedia(void) {
    arrowShader = trap_R_RegisterShaderNoMip("gfx/2d/objArrow");
    /* Original cgs+0x20358 award table entries 12 and 13. */
    artilleryShader = trap_R_RegisterShaderNoMip("gfx/awards/12");
    buildShader = trap_R_RegisterShaderNoMip("gfx/awards/13");
}
void CG_NitmodHintsReset(void) { artilleryPeriod = 0; mineOwner = -1; memset(&dynamiteHint, 0, sizeof(dynamiteHint)); }

qboolean CG_NitmodScanMine(const centity_t *cent) {
    const entityState_t *es;
    vec3_t end;
    trace_t trace;
    int client, i;
    if(!cent || !NITMOD_UsesOriginalProtocol() || !HintClient(&client) ||
       !cg.refdef_current || cg.renderingThirdPerson || cgs.gametype == 8) return qfalse;
    es = &cent->currentState;
    if(es->weapon != WP_LANDMINE || es->eType != ET_MISSILE ||
       es->teamNum < 0 || es->teamNum >= 4 ||
       cgs.clientinfo[client].team != (es->otherEntityNum2 ? TEAM_AXIS : TEAM_ALLIES)) return qfalse;
    VectorMA(cg.refdef_current->vieworg, 512, cg.refdef_current->viewaxis[0], end);
    CG_Trace(&trace, cg.refdef_current->vieworg, NULL, NULL, end, -1, CONTENTS_SOLID);
    for(i = 0; i < 3; ++i) {
        float delta = trace.endpos[i] - es->pos.trBase[i];
        if(!(delta * delta < 256)) return qfalse;
    }
    /* Original owner is otherEntityNum, not clientNum or spotting density. */
    mineOwner = es->otherEntityNum >= 0 && es->otherEntityNum < MAX_CLIENTS ? es->otherEntityNum : -1;
    mineObserved = cg.time;
    return mineOwner >= 0;
}

qboolean CG_NitmodDrawMineHint(void) {
    char text[MAX_NAME_LENGTH + 32];
    vec4_t color = {1,1,1,1};
    nitmodHudAnchor_t previous;
    int owner = mineOwner;
    mineOwner = -1; /* The original consumes the candidate once per frame. */
    if(owner < 0 || owner >= MAX_CLIENTS || !NITMOD_UsesOriginalProtocol() ||
       !cg.snap || cg.renderingThirdPerson || cgs.gametype == 8 || cg_drawCrosshair.integer < 0 ||
       mineObserved != cg.time || !cgs.clientinfo[owner].infoValid) return qfalse;
    Com_sprintf(text, sizeof(text), "%s^7's landmine", cgs.clientinfo[owner].name);
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    CG_Text_Paint_Ext(320 - CG_Text_Width_Ext(text, .18f, 0, &cgs.media.limboFont2) * .5f,
        182, .18f, .18f, color, text, 0, 0, 7, &cgs.media.limboFont2);
    CG_NitmodHudAnchor(previous);
    return qtrue;
}

/* Original CG_Missile / Nit_SpecMines: hidden, mine model, or marker flag.
 * Never grant spectator visibility without the server-supplied caster bit. */
qboolean CG_NitmodPrepareMine(const centity_t *cent, refEntity_t *ent, qboolean *marker) {
    const entityState_t *es;
    int viewer, localTeam, team;
    qboolean caster;
    if(marker) *marker = qfalse;
    if(!cent || !ent || !marker || !NITMOD_UsesOriginalProtocol() ||
       !cg.snap || cg.clientNum < 0 || cg.clientNum >= MAX_CLIENTS) return qfalse;
    viewer = cg.snap->ps.clientNum;
    if(viewer < 0 || viewer >= MAX_CLIENTS) return qfalse;
    es = &cent->currentState;
    if(es->weapon != WP_LANDMINE || es->eType != ET_MISSILE || es->teamNum < 0) return qfalse;
    localTeam = cgs.clientinfo[cg.clientNum].team;
    caster = localTeam == TEAM_SPECTATOR && cgs.clientinfo[cg.clientNum].nitmodShoutcaster;
    if(localTeam == TEAM_SPECTATOR && !caster) return qfalse;
    VectorCopy(ent->origin, ent->lightingOrigin);
    ent->renderfx |= RF_LIGHTING_ORIGIN;
    if(es->teamNum < 4) {
        ent->origin[2] -= 8; ent->oldorigin[2] -= 8;
        team = es->otherEntityNum2 ? TEAM_AXIS : TEAM_ALLIES;
        if(cgs.clientinfo[viewer].team == team && !caster) {
            CG_NitmodScanMine(cent);
            *marker = qtrue;
        } else if(cgs.clientinfo[viewer].team != team && (double)es->density - 1 == viewer) {
            ent->customShader = cgs.media.genericConstructionShader;
        } else if(caster) {
            int pulse = (int)(255.0 - fabs(sin((double)cg.time * .001)) * 255.0);
            ent->customShader = trap_R_RegisterShader("nitmod/SpecMines");
            ent->origin[2] -= 2; ent->oldorigin[2] -= 2;
            ent->shaderRGBA[0] = es->teamNum % 4 == TEAM_AXIS ? 255 : pulse;
            ent->shaderRGBA[1] = pulse;
            ent->shaderRGBA[2] = es->teamNum % 4 == TEAM_AXIS ? pulse : 255;
            ent->shaderRGBA[3] = 255;
        } else if(es->modelindex2) {
            *marker = qtrue;
        } else {
            /* Original private skill/colored-mine masks are not yet mapped.
             * Keep the existing ET battle-sense threshold and shader here. */
            if(cgs.clientinfo[viewer].skill[SK_BATTLE_SENSE] < 4 ||
               !(DistanceSquared(cent->lerpOrigin, cg.predictedPlayerEntity.lerpOrigin) <= 65536)) return qfalse;
            ent->customShader = cgs.media.genericConstructionShader;
        }
    } else if(es->teamNum >= 8) {
        ent->origin[2] -= 8; ent->oldorigin[2] -= 8;
    }
    return qtrue;
}

/* Original CG_ScanForCrosshairDynamite tests a 16-unit axis-aligned box
 * around pos.trBase against a 512-unit solid trace, not a missile hit test. */
qboolean CG_NitmodScanDynamite(const centity_t *cent) {
    const entityState_t *es;
    int client, team, i;
    vec3_t end;
    trace_t trace;
    if(!cent || !NITMOD_UsesOriginalProtocol() || !HintClient(&client) ||
       !cg.refdef_current || cg.renderingThirdPerson || cgs.gametype == 8) return qfalse;
    es = &cent->currentState; team = cgs.clientinfo[client].team;
    if((team != TEAM_AXIS && team != TEAM_ALLIES) || es->eType != ET_MISSILE ||
       es->weapon != WP_DYNAMITE || es->number < MAX_CLIENTS || es->number >= ENTITYNUM_WORLD ||
       es->teamNum < 0 || es->teamNum % 4 != team ||
       es->clientNum < 0 || es->clientNum >= MAX_CLIENTS) return qfalse;
    VectorMA(cg.refdef_current->vieworg, 512, cg.refdef_current->viewaxis[0], end);
    CG_Trace(&trace, cg.refdef_current->vieworg, NULL, NULL, end, -1, CONTENTS_SOLID);
    for(i = 0; i < 3; ++i) {
        float delta = trace.endpos[i] - es->pos.trBase[i];
        if(!(delta * delta < 256)) return qfalse;
    }
    dynamiteHint.state = *es; dynamiteHint.observed = cg.time; dynamiteHint.active = qtrue;
    cg.crosshairClientNum = es->number; cg.crosshairClientTime = cg.time;
    return qtrue;
}

qboolean CG_NitmodDrawDynamiteHint(void) {
    const entityState_t *es = &dynamiteHint.state;
    char text[MAX_NAME_LENGTH + 32];
    vec4_t color = {1,1,1,1}, fill = {1,1,1,.3f}, background = {1,1,1,.125f};
    nitmodHudAnchor_t previous;
    double remaining;
    float fraction;
    int client;
    if(!dynamiteHint.active || !NITMOD_UsesOriginalProtocol() || !HintClient(&client) ||
       cg.renderingThirdPerson || cgs.gametype == 8 || cg_drawCrosshair.integer < 0 ||
       cg.crosshairClientNum != es->number || (double)cg.time - dynamiteHint.observed < 0 ||
       (double)cg.time - dynamiteHint.observed >= 1000 ||
       cgs.clientinfo[client].team != es->teamNum % 4) return qfalse;
    if(!cgs.clientinfo[es->clientNum].infoValid ||
       !(Distance(cg.predictedPlayerState.origin, es->pos.trBase) <= 4096)) return qfalse;
    remaining = 1000 - ((double)cg.time - dynamiteHint.observed);
    if(remaining < FADE_TIME) color[3] = (float)(remaining / FADE_TIME);
    Com_sprintf(text, sizeof(text), "%s^7's dynamite", cgs.clientinfo[es->clientNum].name);
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    CG_Text_Paint_Ext(320 - CG_Text_Width_Ext(text, .18f, 0, &cgs.media.limboFont2) * .5f,
        182, .18f, .18f, color, text, 0, 0, 7, &cgs.media.limboFont2);
    if(es->teamNum < 4 && es->time2 > 0 && cg_drawCrosshairNames.integer) {
        remaining = (double)es->effect1Time + es->time2 - cg.time;
        fraction = remaining <= 0 ? 0 : remaining >= es->time2 ? 1 : (float)(remaining / es->time2);
        fill[3] *= color[3]; background[3] *= color[3];
        CG_FilledBar(290, 193, 60, 7, fill, NULL, background, fraction, 0x10);
    }
    if(es->teamNum < 4) dynamiteHint.active = qfalse;
    CG_NitmodHudAnchor(previous);
    return qtrue;
}

static qboolean HintClient(int *client) {
    if(!cg.snap || !cg_draw2D.integer || cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR) return qfalse;
    *client = cg.snap->ps.clientNum;
    return *client >= 0 && *client < MAX_CLIENTS;
}

qboolean CG_NitmodHintEntity(centity_t *cent) {
    const entityState_t *es = &cent->currentState;
    refEntity_t arrow, icon;
    vec3_t delta;
    float distance, wave;
    int client, team, alpha;
    if(!NITMOD_UsesOriginalProtocol()) return qfalse;
    if(es->eType != ORIGINAL_EXPLOSIVE_HINT && es->eType != ORIGINAL_BUILD_HINT &&
       es->eType != ORIGINAL_ARTILLERY_HINT) return qfalse;
    if(!HintClient(&client)) return qtrue;
    team = cgs.clientinfo[client].team;
    if(team != TEAM_AXIS && team != TEAM_ALLIES) return qtrue;
    if(es->eType == ORIGINAL_ARTILLERY_HINT) {
        if(!cg_artilleryHints.integer || es->teamNum != team) return qtrue;
        VectorSubtract(cg.predictedPlayerState.origin, es->pos.trBase, delta);
        distance = VectorLength(delta);
        artilleryPeriod = distance < 400 ? 150 : distance < 576 ? 300 : 0;
        return qtrue;
    }
    if(!cg_objectiveHints.integer || !es->teamNum || !cg.refdef_current ||
       cgs.clientinfo[client].cls != PC_ENGINEER) return qtrue;
    if(es->eType == ORIGINAL_BUILD_HINT) {
        if(es->teamNum != TEAM_SPECTATOR && es->teamNum != cg.snap->ps.persistant[PERS_TEAM]) return qtrue;
    } else if(es->teamNum == team) return qtrue;
    if(!trap_R_inPVS(cg.refdef_current->vieworg, es->pos.trBase)) return qtrue;
    memset(&arrow, 0, sizeof(arrow)); memset(&icon, 0, sizeof(icon));
    arrow.reType = icon.reType = RT_SPRITE;
    arrow.radius = 10; icon.radius = 16;
    arrow.customShader = arrowShader;
    icon.customShader = es->eType == ORIGINAL_BUILD_HINT ? buildShader : cgs.media.dynamiteHintShader;
    if(icon.customShader <= 0) return qtrue;
    wave = (float)sin((double)cg.time / 250.0);
    alpha = (int)floor((.8 - wave * .5) * 130 + .5);
    arrow.shaderRGBA[team == TEAM_AXIS ? 0 : 2] = 255;
    icon.shaderRGBA[0] = icon.shaderRGBA[1] = icon.shaderRGBA[2] = 255;
    VectorCopy(es->pos.trBase, arrow.origin);
    arrow.origin[2] += 50 + (int)floor((wave * .5 + .5) * 10 + .5);
    VectorCopy(arrow.origin, icon.origin); icon.origin[2] += 24;
    VectorSubtract(cg.predictedPlayerState.origin, arrow.origin, delta);
    distance = VectorLength(delta);
    if(distance < 256) alpha = (int)floor(alpha * (.5 - sin((double)cg.time / 100.0) * .5) + .5);
    arrow.shaderRGBA[3] = icon.shaderRGBA[3] = (byte)alpha;
    if(distance < 2304) icon.renderfx |= RF_DEPTHHACK;
    if(distance < 784) {
        arrow.renderfx |= RF_DEPTHHACK;
        if(arrow.customShader > 0) trap_R_AddRefEntityToScene(&arrow);
    }
    trap_R_AddRefEntityToScene(&icon);
    return qtrue;
}

void CG_NitmodDrawArtilleryHint(void) {
    int period = artilleryPeriod;
    nitmodHudAnchor_t previous;
    vec4_t color = {1, 1, 1, 0};
    artilleryPeriod = 0;
    if(!NITMOD_UsesOriginalProtocol() || !cg_artilleryHints.integer || !period || !cg.time || artilleryShader <= 0) return;
    color[3] = ((float)sin((double)cg.time / period) * .5f + .5f) * .5f;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    trap_R_SetColor(color);
    CG_DrawPic(302, 320, 36, 36, artilleryShader);
    trap_R_SetColor(NULL);
    CG_NitmodHudAnchor(previous);
}
