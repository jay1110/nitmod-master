#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_hud.h"
#include "cg_nitmod_debug.h"
#include "cg_nitmod_autoexec.h"
#include "cg_nitmod_animation.h"
#include "cg_nitmod_ammo.h"
#include "cg_nitmod_lean.h"
#include "cg_nitmod_weapon_pose.h"
#include "cg_nitmod_view.h"
#include "cg_nitmod_hints.h"
#include "cg_nitmod_names.h"
#include "cg_nitmod_events.h"
#include "cg_nitmod_log.h"
#include "cg_nitmod_locations.h"
#include "cg_nitmod_stats.h"
#include "nitmod_weapon_paths.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "check_doublejump.h"
#include "check_lean.h"
#include "check_reload_runtime.h"
extern void dllEntry(int (QDECL *)(int, ...));
extern panel_button_text_t weaponPanelNameFont;
extern void CG_LimboPanel_WeaponPanel_DrawWeapon(rectDef_t *, weapon_t, qboolean, const char *, qboolean);
extern void CG_LimboPanel_SendSetupMsg(qboolean);
extern void CG_LimboPanel_RestoreSecondaryPreference(void);
extern qboolean CG_LimboPanel_TeamButton_KeyDown(panel_button_t *, int);
extern qboolean CG_LimboPanel_ClassButton_KeyDown(panel_button_t *, int);
extern void CG_LimboPanel_RenderTeamButton(panel_button_t *);
extern bg_character_t *CG_LimboPanel_GetCharacter(void);
extern void CG_ClearParticles(void);
extern void CG_DrawMapEntity(mapEntityData_t *, float, float, float, float, int, mapScissor_t *, qboolean, snapshot_t *, int);
extern void CG_ParticleBubble(qhandle_t, vec3_t, vec3_t, int, float, int);
extern void CG_RocketTrail(centity_t *, const weaponInfo_t *);
extern struct particle_s *free_particles, *active_particles;
static int particleInit;
static int particleTrailTest, particleTrailContents;
static int projectileTest, projectileTraces;
static int leanTest, leanTraces, leanTraceErrors;
static int leanLights;
static float leanFraction;
static vec3_t leanStart, leanEnd;
static int locationTest, locationPvsCalls;
static int centerRenderTest, centerGlyphs;
static float centerRects[8][4];
static int crosshairRenderTest, crosshairDraws, crosshairShaders[32];
static float crosshairRects[32][4];
static int CheckCrosshairPresentation(void) {
    static cgs_t savedCgs;
    int savedFlags = cg_drawCrosshairNames.integer, savedPowerups = cg_entities[2].currentState.powerups;
    qhandle_t savedRank[NUM_EXPERIENCE_LEVELS];
    vec4_t color = {1,1,1,.5f};
    int mode, flags, cls, rank, disguise, i, errors = 0;
    savedCgs = cgs;
    memset(&cgs.media.limboFont2, 0, sizeof(cgs.media.limboFont2));
    cgs.media.limboFont2.glyphScale = 1;
    for(i = 0; i < 256; ++i) {
        glyphInfo_t *g = &cgs.media.limboFont2.glyphs[i];
        g->xSkip = 10; g->height = g->imageHeight = 20; g->imageWidth = 10; g->glyph = i + 1000;
    }
    for(i = 0; i < SK_NUM_SKILLS; ++i) cgs.media.skillPics[i] = 2000 + i;
    for(i = 0; i < NUM_EXPERIENCE_LEVELS; ++i) {
        savedRank[i] = rankicons[i][0].shader; rankicons[i][0].shader = 3000 + i;
    }
    cgs.screenXScale = cgs.screenYScale = 1;
    cgs.glconfig.vidWidth = 640; cgs.glconfig.vidHeight = 480;
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    cgs.clientinfo[2].infoValid = qtrue;
    strcpy(cgs.clientinfo[2].name, "A"); strcpy(cgs.clientinfo[2].disguiseName, "B");
    crosshairRenderTest = 1;
    for(mode = 0; mode < 2; ++mode) for(flags = 0; flags < 4; ++flags)
    for(cls = PC_SOLDIER; cls <= PC_COVERTOPS; ++cls)
    for(rank = -1; rank <= NUM_EXPERIENCE_LEVELS; ++rank) for(disguise = 0; disguise < 2; ++disguise) {
        int ranked = (flags & 2) && rank > 0 && rank < NUM_EXPERIENCE_LEVELS;
        int expected = mode && flags ? 5 + ranked : 0;
        strcpy(cgs.gameState.stringData + 1, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        cg_drawCrosshairNames.integer = flags;
        cgs.clientinfo[2].cls = cls; cgs.clientinfo[2].rank = cgs.clientinfo[2].disguiseRank = rank;
        cg_entities[2].currentState.powerups = 0x80 | (cls << 8);
        crosshairDraws = 0;
        if(CG_NitmodDrawCrosshairPlayer(2, disguise, 50, 100, color) != !!expected || crosshairDraws != expected) { ++errors; continue; }
        if(expected && (crosshairShaders[0] != 2000 + BG_ClassSkillForClass(cls) ||
           (ranked && crosshairShaders[1] != 3000 + rank) ||
           crosshairShaders[1 + ranked] != 1000 + (disguise ? 'B' : 'A') ||
           fabs(crosshairRects[2 + ranked][0] - 335) > .01f ||
           fabs(crosshairRects[2 + ranked][1] - 182) > .01f ||
           fabs(crosshairRects[expected - 1][2] - 48) > .01f)) ++errors;
    }
    cg_drawCrosshairNames.integer = 3; crosshairDraws = 0;
    if(CG_NitmodDrawCrosshairPlayer(-1, 0, 1, 100, color) ||
       CG_NitmodDrawCrosshairPlayer(MAX_CLIENTS, 0, 1, 100, color)) ++errors;
    cgs.clientinfo[2].cls = 5;
    if(CG_NitmodDrawCrosshairPlayer(2, 0, 1, 100, color)) ++errors;
    cg_entities[2].currentState.powerups = 7 << 8;
    if(CG_NitmodDrawCrosshairPlayer(2, 1, 1, 100, color) || crosshairDraws) ++errors;
    crosshairDraws = 0; CG_NitmodDrawCrosshairLabel("A", color);
    if(crosshairDraws != 2 || fabs(crosshairRects[1][0] - 319) > .01f || crosshairRects[1][1] != 182) ++errors;
    crosshairDraws = 0; CG_NitmodDrawCrosshairHealth(INT_MAX, 100, color);
    if(crosshairDraws != 2 || crosshairRects[1][2] != 96) ++errors;
    crosshairDraws = 0; CG_NitmodDrawCrosshairHealth(INT_MIN, 100, color);
    if(crosshairDraws != 2 || crosshairRects[1][2] != 0) ++errors;
    crosshairDraws = 0; CG_NitmodDrawCrosshairHealth(1, 0, color);
    if(crosshairDraws) ++errors;
    cgs.gameState.stringOffsets[26] = 2000; strcpy(cgs.gameState.stringData + 2000, "\\64\\original mover");
    cgs.gameState.stringOffsets[27] = 2100; strcpy(cgs.gameState.stringData + 2100, "\\64\\original construction");
    cgs.gameState.stringOffsets[CS_SCRIPT_MOVER_NAMES] = 2200; strcpy(cgs.gameState.stringData + 2200, "\\64\\native mover");
    cgs.gameState.stringOffsets[CS_CONSTRUCTION_NAMES] = 2300; strcpy(cgs.gameState.stringData + 2300, "\\64\\native construction");
    for(mode = 0; mode < 2; ++mode) {
        strcpy(cgs.gameState.stringData + 1, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        if(strcmp(CG_NitmodCrosshairEntityName(64, qfalse), mode ? "original mover" : "native mover") ||
           strcmp(CG_NitmodCrosshairEntityName(64, qtrue), mode ? "original construction" : "native construction") ||
           *CG_NitmodCrosshairEntityName(63, qfalse) || *CG_NitmodCrosshairEntityName(ENTITYNUM_WORLD, qtrue) ||
           *CG_NitmodCrosshairEntityName(65, qfalse)) ++errors;
    }
    crosshairRenderTest = 0; cgs = savedCgs;
    cg_drawCrosshairNames.integer = savedFlags; cg_entities[2].currentState.powerups = savedPowerups;
    for(i = 0; i < NUM_EXPERIENCE_LEVELS; ++i) rankicons[i][0].shader = savedRank[i];
    if(errors) fprintf(stderr, "crosshair presentation: %d failures\n", errors);
    return errors;
}
static int dynamiteTest, dynamiteTraces, dynamiteDraws;
static vec3_t dynamiteEnd;
static float dynamiteLastRect[4];
static int CheckDynamiteDisplay(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    snapshot_t snapshot;
    centity_t cent;
    int mode, team, role, armed, i, errors = 0;
    int savedDraw = cg_draw2D.integer, savedCrosshair = cg_drawCrosshair.integer;
    int savedNames = cg_drawCrosshairNames.integer;
    savedCg = cg; savedCgs = cgs;
    memset(&snapshot, 0, sizeof(snapshot)); memset(&cent, 0, sizeof(cent));
    cg.snap = &snapshot; cg.nextSnap = NULL; cg.clientNum = snapshot.ps.clientNum = 1;
    CG_BuildSolidList(); cg.refdef_current = &cg.refdef;
    VectorClear(cg.refdef.vieworg); VectorClear(cg.refdefViewAngles);
    VectorClear(cg.predictedPlayerState.origin); AxisClear(cg.refdef.viewaxis);
    cg.refdef.fov_x = 96; cg.refdef.fov_y = 102;
    cg.renderingThirdPerson = qfalse; cg_draw2D.integer = 1; cg_drawCrosshair.integer = 0;
    cg_drawCrosshairNames.integer = 1; cgs.gametype = 2;
    cgs.screenXScale = cgs.screenYScale = 1;
    cgs.glconfig.vidWidth = 640; cgs.glconfig.vidHeight = 480;
    cent.currentState.number = MAX_CLIENTS; cent.currentState.clientNum = 2;
    cent.currentState.eType = ET_MISSILE; cent.currentState.weapon = WP_DYNAMITE;
    cent.currentState.effect1Time = 1000; cent.currentState.time2 = 30000;
    cent.currentState.pos.trBase[0] = cent.lerpOrigin[0] = 512;
    cgs.clientinfo[2].infoValid = qtrue; strcpy(cgs.clientinfo[2].name, "Owner");
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    VectorSet(dynamiteEnd, 512, 0, 0); dynamiteTest = 1; cg.time = 16000;
    for(mode = 0; mode < 2; ++mode) for(team = TEAM_AXIS; team <= TEAM_SPECTATOR; ++team)
    for(role = 0; role < 2; ++role) for(armed = -1; armed <= 7; ++armed) {
        strcpy(cgs.gameState.stringData + 1, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        snapshot.ps.persistant[PERS_TEAM] = cgs.clientinfo[1].team = team;
        cgs.clientinfo[1].nitmodShoutcaster = role; cent.currentState.teamNum = armed;
        CG_NitmodNamesReset(); CG_NitmodHintsReset();
        if(CG_NitmodQueueDynamiteName(&cent) != !!(mode && team == TEAM_SPECTATOR && role && armed >= 1 && armed <= 3)) ++errors;
        if(CG_NitmodScanDynamite(&cent) != !!(mode && team != TEAM_SPECTATOR && armed >= 0 && armed % 4 == team)) ++errors;
    }
    snapshot.ps.persistant[PERS_TEAM] = cgs.clientinfo[1].team = TEAM_AXIS;
    cent.currentState.teamNum = TEAM_AXIS;
    for(i = 0; i < 3; ++i) {
        dynamiteEnd[i] += 16;
        if(CG_NitmodScanDynamite(&cent)) ++errors;
        dynamiteEnd[i] -= .01f;
        if(!CG_NitmodScanDynamite(&cent)) ++errors;
        dynamiteEnd[i] -= 15.99f;
    }
    memset(&cgs.media.limboFont2, 0, sizeof(cgs.media.limboFont2));
    cgs.media.limboFont2.glyphScale = 1;
    for(i = 0; i < 256; ++i) {
        cgs.media.limboFont2.glyphs[i].xSkip = 10;
        cgs.media.limboFont2.glyphs[i].height = 10;
        cgs.media.limboFont2.glyphs[i].imageWidth = 10;
        cgs.media.limboFont2.glyphs[i].imageHeight = 10;
        cgs.media.limboFont2.glyphs[i].glyph = i + 1000;
    }
    cgs.media.limboFont1 = cgs.media.limboFont2;
    CG_NitmodScanDynamite(&cent); dynamiteDraws = 0;
    if(!CG_NitmodDrawDynamiteHint() || !dynamiteDraws ||
       fabs(dynamiteLastRect[2] - 28) > .01f || CG_NitmodDrawDynamiteHint()) ++errors;
    CG_NitmodScanDynamite(&cent); cg.crosshairClientNum = 2;
    if(CG_NitmodDrawDynamiteHint()) ++errors;
    CG_NitmodScanDynamite(&cent); cg.time += 1000;
    if(CG_NitmodDrawDynamiteHint()) ++errors;
    cent.currentState.time2 = 0; CG_NitmodScanDynamite(&cent);
    if(!CG_NitmodDrawDynamiteHint()) ++errors;
    cent.currentState.clientNum = MAX_CLIENTS;
    if(CG_NitmodScanDynamite(&cent) || CG_NitmodScanDynamite(NULL)) ++errors;
    cent.currentState.clientNum = 2;
    snapshot.ps.persistant[PERS_TEAM] = cgs.clientinfo[1].team = TEAM_SPECTATOR;
    cgs.clientinfo[1].nitmodShoutcaster = qtrue;
    CG_NitmodNamesReset(); cg.time = 1500;
    CG_NitmodQueueDynamiteName(&cent); CG_NitmodDrawSpectatorNames();
    cg.time = 2000; CG_NitmodNamesBeginFrame(); dynamiteDraws = 0;
    CG_NitmodQueueDynamiteName(&cent); CG_NitmodDrawSpectatorNames();
    if(dynamiteDraws != 4) ++errors; /* "29", two glyphs plus shadows; ticking must not reset fade. */
    CG_NitmodNamesBeginFrame();
    for(i = 0; i < 18; ++i) if(CG_NitmodQueueDynamiteName(&cent) != (i < 16)) ++errors;
    cent.currentState.number = ENTITYNUM_WORLD;
    CG_NitmodNamesBeginFrame();
    if(CG_NitmodQueueDynamiteName(&cent) || CG_NitmodQueueDynamiteName(NULL)) ++errors;
    dynamiteTest = 0; CG_NitmodNamesReset(); CG_NitmodHintsReset();
    cg = savedCg; cgs = savedCgs; cg_draw2D.integer = savedDraw;
    cg_drawCrosshair.integer = savedCrosshair; cg_drawCrosshairNames.integer = savedNames;
    if(cg.snap) CG_BuildSolidList();
    if(errors) fprintf(stderr, "dynamite display: %d failures\n", errors);
    return errors;
}
static int CheckCenterChannels(void) {
    static cg_t savedCg;
    static fontInfo_t savedFont;
    gameState_t savedGame = cgs.gameState;
    float savedDuration = cg_centertime.value, sx = cgs.screenXScale, sy = cgs.screenYScale, bias = cgs.screenXBias;
    int width = cgs.glconfig.vidWidth, height = cgs.glconfig.vidHeight, errors = 0;
    savedCg = cg; savedFont = cgs.media.limboFont2;
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cgs.screenXScale = cgs.screenYScale = 1; cgs.screenXBias = 0;
    cgs.glconfig.vidWidth = 640; cgs.glconfig.vidHeight = 480;
    memset(&cgs.media.limboFont2, 0, sizeof(cgs.media.limboFont2));
    cgs.media.limboFont2.glyphScale = 1;
    cgs.media.limboFont2.glyphs['A'].xSkip = 12;
    cgs.media.limboFont2.glyphs['A'].height = 16;
    cgs.media.limboFont2.glyphs['A'].imageWidth = 12;
    cgs.media.limboFont2.glyphs['A'].imageHeight = 16;
    cgs.media.limboFont2.glyphs['A'].glyph = 4242;
    cg_centertime.value = 3; cg.time = 1000; cg.centerPrintPriority = 0;
    CG_CenterPrint("A\nA", 200, 8);
    centerRenderTest = 1; centerGlyphs = 0;
    CG_NitmodDrawCenterPrint();
    if(centerGlyphs != 4 || fabs(centerRects[0][0] - centerRects[1][0] - .75f) > .01f ||
       fabs(centerRects[0][1] - centerRects[1][1] - .75f) > .01f ||
       fabs(centerRects[1][0] - 318.5f) > .01f ||
       fabs(centerRects[1][1] - 184) > .01f || fabs(centerRects[3][1] - 190) > .01f) {
        fprintf(stderr, "center glyphs=%d x=%g y=%g next=%g\n", centerGlyphs,
            centerRects[1][0], centerRects[1][1], centerRects[3][1]); ++errors;
    }
    CG_NitmodPrintAnnouncement("first", 200, 8, 5);
    if(strcmp(cg.centerPrint, "A\nA") || strcmp(CG_NitmodAnnouncementText(), "first")) ++errors;
    CG_NitmodPrintAnnouncement("blocked", 200, 8, -1);
    if(strcmp(CG_NitmodAnnouncementText(), "first")) ++errors;
    CG_NitmodPrintAnnouncement("replace", 200, 8, 0);
    if(strcmp(CG_NitmodAnnouncementText(), "replace")) ++errors;
    CG_NitmodPrintAnnouncement(NULL, 200, 8, 0);
    CG_NitmodPrintAnnouncement("invalid", 200, 0, 0);
    if(strcmp(CG_NitmodAnnouncementText(), "replace")) ++errors;
    cg.time = 4000; centerGlyphs = 0; CG_NitmodDrawCenterPrint();
    if(centerGlyphs || cg.centerPrintTime || strcmp(CG_NitmodAnnouncementText(), "replace")) ++errors;
    cg.time = 6000;
    if(CG_NitmodAnnouncementText()[0]) ++errors;
    CG_NitmodPrintAnnouncement("new", 200, 8, -1);
    if(strcmp(CG_NitmodAnnouncementText(), "new")) ++errors;
    cg_centertime.value = 0;
    if(CG_NitmodAnnouncementText()[0]) ++errors;
    cg_centertime.value = 3;
    CG_NitmodPrintAnnouncement("reset", 200, 8, 0); CG_NitmodHudReset();
    if(CG_NitmodAnnouncementText()[0]) ++errors;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\etmain");
    CG_CenterPrint("A", 200, 8); centerGlyphs = 0; CG_NitmodDrawCenterPrint();
    if(centerGlyphs) ++errors;
    centerRenderTest = 0; cg = savedCg; cgs.gameState = savedGame; cgs.media.limboFont2 = savedFont;
    cg_centertime.value = savedDuration; cgs.screenXScale = sx; cgs.screenYScale = sy; cgs.screenXBias = bias;
    cgs.glconfig.vidWidth = width; cgs.glconfig.vidHeight = height;
    return errors;
}
static int locationMarkerTest, locationMarkerPvs, locationMarkers, locationMarkerErrors, locationMarkerTraces;
static int CheckLocationMarkers(void) {
    static cg_t savedCg;
    gameState_t savedGame = cgs.gameState;
    snapshot_t snap;
    char records[] = "100 0 0 Near\n3000 0 0 Edge\n3001 0 0 Far\n-100 0 0 Behind\n100 500 0 Side\n";
    char invalid[][32] = {"nan 1 2 Bad", "inf 1 2 Bad", "1e400 1 2 Bad", "1e39 1 2 Bad"};
    int savedFlags = cg_locations.integer, savedDraw = cg_draw2D.integer, savedShader = cgs.media.waterBubbleShader;
    int mode, flags, pvs, i, errors = 0;
    float x, y;
    vec3_t origin = {100, 0, 0};
    savedCg = cg;
    for(i = 0; i < 4; ++i) if(CG_NitmodParseLocations(invalid[i])) ++errors;
    if(CG_NitmodParseLocations(records) != 5) ++errors;
    memset(&snap, 0, sizeof(snap)); cg.snap = &snap; cg.nextSnap = NULL;
    CG_BuildSolidList(); cg.refdef_current = &cg.refdef;
    VectorClear(cg.refdef.vieworg); VectorClear(cg.refdefViewAngles); AxisClear(cg.refdef.viewaxis);
    cg.refdef.fov_x = 96; cg.refdef.fov_y = 102; cg_draw2D.integer = 1;
    if(!CG_NitmodProjectName(origin, &x, &y) || x != 320 || y != 240) ++errors;
    origin[0] = -100;
    if(CG_NitmodProjectName(origin, &x, &y)) ++errors;
    cgs.media.waterBubbleShader = 923;
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    locationMarkerTest = 1;
    for(mode = 0; mode < 2; ++mode) for(flags = 0; flags < 4; ++flags) for(pvs = 0; pvs < 2; ++pvs) {
        int expected = mode && (flags & 2) && pvs ? 2 : 0;
        strcpy(cgs.gameState.stringData + 1, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        cg_locations.integer = (flags & 2 ? 512 : 0) | (flags & 1);
        locationMarkerPvs = pvs; locationMarkers = locationMarkerErrors = locationMarkerTraces = 0;
        CG_NitmodNamesBeginFrame();
        if(CG_NitmodAddLocationMarkers() != expected || locationMarkers != expected || locationMarkerErrors) ++errors;
        CG_NitmodDrawSpectatorNames();
        if(locationMarkerTraces != expected) ++errors; /* Location labels do not require spectator rights. */
    }
    if(CG_NitmodQueueLocationName(-1, "bad", origin) ||
       CG_NitmodQueueLocationName(NITMOD_MAX_LOCATIONS, "bad", origin)) ++errors;
    locationMarkerTest = 0; CG_NitmodParseLocations(NULL);
    cg = savedCg; cgs.gameState = savedGame; cg_locations.integer = savedFlags;
    cg_draw2D.integer = savedDraw; cgs.media.waterBubbleShader = savedShader;
    if(cg.snap) CG_BuildSolidList();
    return errors;
}
static int fireteamRenderTest, fireteamRenderIcons, fireteamRenderErrors;
static int statusRenderTest, statusFrames, statusIcons, statusRenderErrors, statusUnderwater;
static float statusScale, statusRightOffset;
static int CheckStatusBarRendering(void) {
    snapshot_t snapshot, *savedSnap = cg.snap;
    gameState_t savedGame = cgs.gameState;
    int *handles[] = {&cgs.media.hudSprintBar, &cgs.media.hudHealthIcon,
        &cgs.media.hudSprintIcon, &cgs.media.waterHintShader, &cgs.media.hudPowerIcon};
    int savedHandles[5], i, wide, water, errors = 0, savedClass = cgs.clientinfo[0].cls;
    int savedWidth = cgs.glconfig.vidWidth, savedHeight = cgs.glconfig.vidHeight;
    int savedCondition = BG_GetConditionValue(0, ANIM_COND_UNDERWATER, qtrue);
    float sx = cgs.screenXScale, sy = cgs.screenYScale, bias = cgs.screenXBias;
    memset(&snapshot, 0, sizeof(snapshot)); cg.snap = &snapshot;
    snapshot.ps.persistant[PERS_TEAM] = TEAM_AXIS;
    snapshot.ps.stats[STAT_MAX_HEALTH] = 100; snapshot.ps.stats[STAT_HEALTH] = 50;
    snapshot.ps.stats[6] = 10000; cgs.clientinfo[0].cls = PC_SOLDIER;
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    for(i = 0; i < 5; ++i) { savedHandles[i] = *handles[i]; *handles[i] = 7101 + i; }
    statusRenderTest = 1;
    for(wide = 0; wide < 2; ++wide) for(water = 0; water < 2; ++water) {
        cgs.glconfig.vidWidth = wide ? 1920 : 640; cgs.glconfig.vidHeight = wide ? 1080 : 480;
        cgs.screenXScale = cgs.glconfig.vidWidth / 640.f;
        cgs.screenYScale = statusScale = cgs.glconfig.vidHeight / 480.f;
        cgs.screenXBias = 0; statusRightOffset = wide ? 480 : 0;
        statusUnderwater = water;
        BG_UpdateConditionValue(0, ANIM_COND_UNDERWATER, water, qtrue);
        statusFrames = statusIcons = statusRenderErrors = 0;
        CG_NitmodDrawStatusBars();
        if(statusFrames != 3 || statusIcons != 3 || statusRenderErrors) ++errors;
    }
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\etmain");
    statusFrames = statusIcons = 0; CG_NitmodDrawStatusBars();
    if(statusFrames || statusIcons) ++errors;
    statusRenderTest = 0;
    for(i = 0; i < 5; ++i) *handles[i] = savedHandles[i];
    BG_UpdateConditionValue(0, ANIM_COND_UNDERWATER, savedCondition, qtrue);
    cgs.glconfig.vidWidth = savedWidth; cgs.glconfig.vidHeight = savedHeight;
    cgs.screenXScale = sx; cgs.screenYScale = sy; cgs.screenXBias = bias;
    cgs.clientinfo[0].cls = savedClass; cgs.gameState = savedGame; cg.snap = savedSnap;
    return errors;
}
static int CheckOriginalStatusBars(void) {
    playerState_t state;
    nitmodStatusBars_t bars, sentinel;
    int *times[] = {cg.soldierChargeTime, cg.medicChargeTime, cg.engineerChargeTime,
        cg.ltChargeTime, cg.covertopsChargeTime};
    int saved[5][2], cls, team, i, n, errors = 0, savedType = cgs.gametype;
    const int samples[] = {-100, 0, 1000, 10000, 20000, 40000};
    memset(&state, 0, sizeof(state));
    for(cls = 0; cls < 5; ++cls) for(team = 0; team < 2; ++team) {
        saved[cls][team] = times[cls][team]; times[cls][team] = 10000 * (cls + 1) + 1000 * team;
    }
    cgs.gametype = GT_WOLF;
    state.stats[STAT_HEALTH] = 75; state.stats[STAT_MAX_HEALTH] = 100; state.stats[9] = 150;
    for(cls = 0; cls < 5; ++cls) for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team) {
        state.stats[STAT_PLAYER_CLASS] = cls; state.persistant[PERS_TEAM] = team;
        for(n = 0; n < 6; ++n) {
            float expected = samples[n] <= 0 ? 0 : samples[n] >= 20000 ? 1 : samples[n] / 20000.f;
            state.stats[6] = samples[n];
            if(!CG_NitmodStatusBars(&state, cls, qfalse, times[cls][team - 1] / 2, 0, &bars) ||
               fabs(bars.stamina - expected) > .00001f || fabs(bars.charge - .5f) > .00001f ||
               fabs(bars.health - (cls == PC_MEDIC && !NITMOD_SimpleConfig()->war ? .5f : .75f)) > .00001f ||
               bars.chargeColor[3] != .5f) ++errors;
            if(bars.staminaColor[0] != (expected < .25f ? 1 : .1f)) ++errors;
        }
    }
    state.persistant[PERS_TEAM] = TEAM_AXIS; state.stats[STAT_PLAYER_CLASS] = PC_FIELDOPS;
    for(i = 0; i < 8; ++i) {
        state.ammo[WP_ARTY] = i;
        if(!CG_NitmodStatusBars(&state, PC_FIELDOPS, qtrue, 1000, 7000, &bars) ||
           bars.stamina != .5f || !bars.underwater ||
           bars.powerColor[1] != ((i & 3) == 2 ? .5f : (i & 3) == 3 ? 0 : 1) ||
           bars.powerColor[2] != ((i & 3) ? 0 : 1)) ++errors;
    }
    state.stats[STAT_PLAYER_CLASS] = PC_SOLDIER; state.stats[6] = 20000;
    state.powerups[11] = 1000;
    if(!CG_NitmodStatusBars(&state, PC_SOLDIER, qfalse, 1000, 0, &bars) ||
       fabs(bars.staminaColor[0] - .55f) > .00001f || bars.staminaColor[3] != .75f) ++errors;
    state.powerups[11] = 999;
    CG_NitmodStatusBars(&state, PC_SOLDIER, qfalse, 1000, 0, &bars);
    if(bars.staminaColor[0] != .1f || bars.staminaColor[3] != .5f) ++errors;
    state.classWeaponTime = INT_MAX;
    CG_NitmodStatusBars(&state, PC_SOLDIER, qtrue, INT_MIN, INT_MAX, &bars);
    if(bars.charge != 0 || bars.stamina != 1) ++errors;
    state.classWeaponTime = INT_MIN;
    CG_NitmodStatusBars(&state, PC_SOLDIER, qtrue, INT_MAX, INT_MIN, &bars);
    if(bars.charge != 1 || bars.stamina != 0) ++errors;
    state.stats[STAT_MAX_HEALTH] = 0; times[PC_SOLDIER][0] = 0;
    CG_NitmodStatusBars(&state, PC_SOLDIER, qfalse, 0, 0, &bars);
    if(bars.charge != 0 || bars.health != 0) ++errors;
    memset(&sentinel, 0x55, sizeof(sentinel)); bars = sentinel;
    state.persistant[PERS_TEAM] = TEAM_SPECTATOR;
    if(CG_NitmodStatusBars(&state, 0, qfalse, 0, 0, &bars) || memcmp(&bars, &sentinel, sizeof(bars)) ||
       CG_NitmodStatusBars(NULL, 0, qfalse, 0, 0, &bars) ||
       CG_NitmodStatusBars(&state, -1, qfalse, 0, 0, &bars)) ++errors;
    for(cls = 0; cls < 5; ++cls) for(team = 0; team < 2; ++team) times[cls][team] = saved[cls][team];
    cgs.gametype = savedType;
    return errors;
}
static int CheckClientLogFormatting(void) {
    qtime_t time;
    char line[64], tiny[8];
    int errors = 0;
    memset(&time, 0, sizeof(time));
    time.tm_hour = 4; time.tm_min = 5; time.tm_sec = 6;
    CG_NitmodLogLine(line, sizeof(line), &time, "hello\n");
    if(strcmp(line, "[04:05:06] hello\n")) ++errors;
    CG_NitmodLogLine(tiny, sizeof(tiny), &time, "long message");
    if(tiny[sizeof(tiny) - 1] != '\0') ++errors;
    strcpy(line, "dirty"); CG_NitmodLogLine(line, sizeof(line), NULL, "x");
    if(line[0]) ++errors;
    strcpy(line, "dirty"); CG_NitmodLogLine(line, sizeof(line), &time, NULL);
    if(line[0]) ++errors;
    CG_NitmodLogLine(NULL, 0, &time, "x");
    return errors;
}
static int CheckLocationParsing(void) {
    char valid[] = "// comment\n100 200 300 \"Axis Spawn\"\n-50 25 1 Tunnel\n0 0 0 ignored\n";
    char truncated[] = "1 2 3 \"Valid\"\n4 5";
    char empty[] = "// only comments\n";
    int errors = 0;
    if(CG_NitmodParseLocations(valid) != 2 || CG_NitmodLocationCount() != 2) ++errors;
    {
        vec3_t nearSecond = {-40, 25, 1};
        locationTest = 1; locationPvsCalls = 0;
        if(strcmp(CG_NitmodLocation(nearSecond), "Tunnel") || locationPvsCalls != 2) ++errors;
        locationTest = 0;
    }
    if(CG_NitmodParseLocations(truncated) != 1 || CG_NitmodLocationCount() != 1) ++errors;
    if(CG_NitmodParseLocations(empty) != 0 || CG_NitmodLocationCount() != 0) ++errors;
    if(CG_NitmodParseLocations(NULL) != 0) ++errors;
    return errors;
}
static int CheckProjectileOptions(void) {
    static cg_t savedCg;
    static gameState_t savedGame;
    snapshot_t snap;
    centity_t cent;
    entityState_t before;
    vec3_t origin = {384,0,0};
    const int modes[] = {-1,0,1,2,150};
    const int fps[] = {0,-1,20,40,1001};
    const int pings[] = {-1,0,80};
    int protocol, m, f, p, own, errors = 0;
    vmCvar_t savedMark = cg_markDistance, savedNudge = cg_projectileNudge, savedFPS = nitmod_sv_fps;
    savedCg = cg; savedGame = cgs.gameState;
    memset(&cg, 0, sizeof(cg)); memset(&snap, 0, sizeof(snap)); memset(&cent, 0, sizeof(cent));
    cg.snap = &snap; cg.time = 1000; cg.clientNum = 1; cg.refdef_current = &cg.refdef;
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    cent.currentState.eType = ET_MISSILE; cent.currentState.number = 100;
    cent.currentState.pos.trType = TR_LINEAR; cent.currentState.pos.trDelta[0] = 100;
    cent.currentState.apos.trType = TR_LINEAR; cent.currentState.apos.trDelta[1] = 50;
    for(protocol = 0; protocol < 3; ++protocol) {
        strcpy(cgs.gameState.stringData + 1, protocol == 1 ? "\\gamename\\nitmod" :
            protocol == 2 ? "\\gamename\\nitmod\\nitmod_csLayout\\et260" : "\\gamename\\etmain");
        cg_markDistance.integer = 385;
        if(CG_NitmodBulletImpactVisible(WP_MP40, origin) != (protocol == 1)) ++errors;
        cg_markDistance.integer = 384;
        if(CG_NitmodBulletImpactVisible(WP_MP40, origin)) ++errors;
        cg_markDistance.integer = -1;
        if(!CG_NitmodBulletImpactVisible(WP_GARAND_SCOPE, origin) ||
           !CG_NitmodBulletImpactVisible(WP_K43_SCOPE, origin) ||
           !CG_NitmodBulletImpactVisible(WP_FG42SCOPE, origin)) ++errors;
        for(m = 0; m < 5; ++m) for(f = 0; f < 5; ++f) for(p = 0; p < 3; ++p) for(own = 0; own < 2; ++own) {
            int expected = cg.time, extra = own ? 0 : (modes[m] == 1 ? pings[p] : modes[m]);
            cg_projectileNudge.integer = modes[m]; nitmod_sv_fps.integer = fps[f]; snap.ping = pings[p];
            cent.currentState.clientNum = own ? 1 : 2;
            if(protocol == 1 && modes[m] > 0 && fps[f] > 0 && extra >= 0) expected += 1000 / fps[f] + extra;
            if(CG_NitmodProjectileTime(&cent.currentState) != expected) ++errors;
            before = cent.currentState;
            projectileTraces = 0; projectileTest = 1;
            if(CG_NitmodProjectileLerp(&cent) != (protocol == 1 && modes[m] > 0)) ++errors;
            projectileTest = 0;
            if(protocol == 1 && modes[m] > 0) {
                if(fabs(cent.lerpOrigin[0] - expected * .1f) > .001f ||
                   fabs(cent.lerpAngles[1] - expected * .05f) > .001f ||
                   projectileTraces != (expected != cg.time)) ++errors;
            }
            if(memcmp(&before, &cent.currentState, sizeof(before))) ++errors;
        }
    }
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    nitmod_sv_fps.integer = 20; cg_projectileNudge.integer = INT_MAX;
    cent.currentState.clientNum = 2;
    if(CG_NitmodProjectileTime(&cent.currentState) != cg.time) ++errors;
    cg_projectileNudge.integer = 1; cg.time = INT_MAX; snap.ping = 80;
    if(CG_NitmodProjectileTime(&cent.currentState) != cg.time) ++errors;
    cent.currentState.eType = ET_PLAYER;
    if(CG_NitmodProjectileLerp(&cent)) ++errors;
    cg.snap = NULL;
    if(CG_NitmodProjectileLerp(&cent) || CG_NitmodProjectileTime(NULL) != cg.time) ++errors;
    cg = savedCg; cgs.gameState = savedGame;
    cg_markDistance = savedMark; cg_projectileNudge = savedNudge; nitmod_sv_fps = savedFPS;
    return errors;
}
static int zoomTest, zoomWrites;
static float zoomWritten;
static int CheckMapAndPing(void) {
    const int pings[] = {-1, 0, 100, 101, 200, 201, 350, 351, 999};
    const int colors[] = {2, 2, 2, 3, 3, 8, 8, 1, 1};
    const float zooms[] = {-1, 1, 2, 5.159f, 7.43f, 100};
    int mode, i, direction, errors = 0;
    for(mode = -1; mode <= 2; ++mode) {
        cg_pingColors.integer = mode;
        for(i = 0; i < 9; ++i) {
            char expected[32];
            if(CG_NitmodPingColor(pings[i]) != (mode ? colors[i] : 7)) ++errors;
            if(pings[i] == -1) Q_strncpyz(expected, "^2CONN.^7", sizeof(expected));
            else Com_sprintf(expected, sizeof(expected), "^%i%4i^7", mode ? colors[i] : 7, pings[i]);
            if(strcmp(CG_NitmodPingText(pings[i]), expected)) ++errors;
        }
    }
    zoomTest = 1;
    for(i = 0; i < 6; ++i) for(direction = 0; direction < 2; ++direction) {
        float expected = zooms[i] < 1 ? 1 : zooms[i] > 7.43f ? 7.43f : zooms[i];
        cg_automapZoom.value = zooms[i]; zoomWrites = 0;
        if(CG_NitmodAutomapZoom() != expected) ++errors;
        expected = direction ? expected * 1.2f : expected / 1.2f;
        if(expected < 1) expected = 1;
        if(expected > 7.43f) expected = 7.43f;
        CG_AdjustAutomapZoom(direction);
        if(zoomWrites != 1 || fabs(CG_NitmodAutomapZoom() - expected) > .00001) ++errors;
    }
    zoomTest = 0;
    cg_pingColors.integer = 1; cg_automapZoom.value = 5.159f;
    return errors;
}
static int CheckAnnouncerModes(void) {
    int mode, step, errors = 0;
    float scale; vec4_t color;
    char text[1100];
    cg_announcer.integer = 1; cg.time = 1000;
    for(mode = 0; mode <= 4; ++mode) {
        CG_NitmodAddAnnouncer("CUSTOM", 0, .75f, 2000, .2f, .4f, .6f, mode, 40);
        for(step = 0; step < 8; ++step) {
            double remaining = 1.0 - step / 8.0;
            double expected = mode == 2 ? 1.1 - sin(remaining * 3.1415927) :
                mode == 3 ? .1 + sin(remaining * 3.1415927) : 1.1 - remaining;
            if(!CG_NitmodAnnouncerFrame(1000 + step * 250, &scale, color) ||
               fabs(scale - expected * .75) > .00001 ||
               fabs(color[0] - .2) > .00001 || fabs(color[1] - .4) > .00001 ||
               fabs(color[2] - .6) > .00001 || color[3] != 1) ++errors;
        }
        if(CG_NitmodAnnouncerFrame(3000, &scale, color)) ++errors;
    }
    memset(text, 'A', sizeof(text)); text[sizeof(text) - 1] = 0;
    CG_NitmodAddAnnouncer(text, 0, 1, 1000, 1, 1, 1, 1, 0);
    text[0] = 'B';
    if(strlen(CG_NitmodAnnouncerText()) != 1023 || CG_NitmodAnnouncerText()[0] != 'A') ++errors;
    CG_NitmodAddAnnouncer(NULL, 0, 1, 1000, 1, 1, 1, 1, 0);
    if(CG_NitmodAnnouncerText()[0] != 'A') ++errors;
    CG_NitmodAddAnnouncer("INVALID", 0, 0, 1000, 1, 1, 1, 1, 0);
    CG_NitmodAddAnnouncer("INVALID", 0, 1, 0, 1, 1, 1, 1, 0);
    CG_NitmodAddAnnouncer("INVALID", 0, 1, 1000, -1, 1, 1, 1, 0);
    if(CG_NitmodAnnouncerText()[0] != 'A') ++errors;
    if(CG_NitmodAnnouncerFrame(1000, NULL, color) || CG_NitmodAnnouncerFrame(1000, &scale, NULL)) ++errors;
    cg_announcer.integer = 0;
    CG_NitmodAddAnnouncer("DISABLED", 0, 1, 1000, 1, 1, 1, 1, 0);
    if(CG_NitmodAnnouncerText()[0] != 'A' || CG_NitmodAnnouncerFrame(1000, &scale, color)) ++errors;
    cg_announcer.integer = 1;
    CG_NitmodHudReset();
    if(CG_NitmodAnnouncerText()[0] || CG_NitmodAnnouncerFrame(1000, &scale, color)) ++errors;
    return errors;
}
static int CheckOriginalSkillPresentation(void) {
    int n, i, errors = 0, native[7], shown[7];
    playerState_t state;
    char digits[8];
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    memset(&state, 0, sizeof(state));
    state.stats[3] = 2; state.stats[STAT_XP] = 17;
    if(CG_NitmodDisplayXP(&state) != 65553 || CG_NitmodDisplayXP(NULL) != 0) ++errors;
    state.stats[3] = 0x7fffffff;
    if(CG_NitmodDisplayXP(&state) != 0x7fffffff) ++errors;
    for(n = PC_SOLDIER; n <= PC_COVERTOPS; ++n) {
        state.persistant[PERS_HWEAPON_USE] = 0;
        state.eFlags = 0;
        if(CG_NitmodHudSkill(n, 0, &state) != SK_LIGHT_WEAPONS ||
           CG_NitmodHudSkill(n, 1, &state) != SK_BATTLE_SENSE ||
           CG_NitmodHudSkill(n, 2, &state) != BG_ClassSkillForClass(n)) ++errors;
        state.persistant[PERS_HWEAPON_USE] = 1;
        if(CG_NitmodHudSkill(n, 0, &state) != (n == PC_SOLDIER ? SK_LIGHT_WEAPONS : SK_HEAVY_WEAPONS)) ++errors;
        state.persistant[PERS_HWEAPON_USE] = 0;
        state.eFlags = EF_MOUNTEDTANK;
        if(CG_NitmodHudSkill(n, 0, &state) != (n == PC_SOLDIER ? SK_LIGHT_WEAPONS : SK_HEAVY_WEAPONS)) ++errors;
    }
    if(CG_NitmodHudSkill(-1, 0, &state) != -1 || CG_NitmodHudSkill(0, 3, &state) != -1) ++errors;
    digits[7] = 0;
    for(n = 0; n < 279936; ++n) {
        int value = n;
        for(i = 0; i < 7; ++i) { digits[i] = '0' + value % 6; value /= 6; }
        if(!NITMOD_DecodeClientSkills(digits, native, shown)) { ++errors; break; }
        for(i = 0; i < 7; ++i)
            if(shown[i] != digits[i] - '0' || native[i] != (shown[i] > 4 ? 4 : shown[i])) ++errors;
    }
    for(i = 0; i < 7; ++i) native[i] = shown[i] = 99;
    if(NITMOD_DecodeClientSkills("1234560", native, shown) ||
       NITMOD_DecodeClientSkills("123", native, shown) ||
       NITMOD_DecodeClientSkills("12345001", native, shown)) ++errors;
    for(i = 0; i < 7; ++i) if(native[i] != 99 || shown[i] != 99) ++errors;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\etmain");
    if(CG_NitmodDisplayXP(&state) != 17) ++errors;
    if(NITMOD_DecodeClientSkills("1234500", native, shown)) ++errors;
    if(!NITMOD_DecodeClientSkills("1234400", native, shown)) ++errors;
    for(i = 0; i < 7; ++i) if(native[i] != shown[i]) ++errors;
    if(NITMOD_DecodeClientSkills(NULL, native, shown) || NITMOD_DecodeClientSkills("0000000", NULL, shown)) ++errors;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    return errors;
}
extern int QDECL CG_SortFireTeam(const void *, const void *);
static int CheckFireteamRoster(void) {
    static clientInfo_t savedClients[MAX_CLIENTS];
    static gameState_t savedGame;
    fireteamData_t decoded, sentinel, team;
    int errors = 0, mode, i, j, a, b, savedClient = cg.clientNum, savedType = cgs.gametype;
    char text[128], mask[17];
    memcpy(savedClients, cgs.clientinfo, sizeof(savedClients)); savedGame = cgs.gameState;
    memset(&sentinel, 0x55, sizeof(sentinel));
    for(mode = 0; mode < 2; ++mode) {
        for(i = 0; i < 64; ++i) {
            memset(mask, '0', 16); mask[16] = 0;
            mask[15 - i / 4] = "1248"[i % 4];
            Com_sprintf(text, sizeof(text), "\\%s\\5\\l\\%d\\c\\%s", mode ? "n" : "id", i, mask);
            if(!CG_DecodeFireteam(text, mode, &decoded) || decoded.ident != 5 ||
               decoded.leader != i || !decoded.inuse) ++errors;
            for(j = 0; j < 64; ++j) if(decoded.joinOrder[j] != (i == j)) ++errors;
        }
        Com_sprintf(text, sizeof(text), "\\%s\\0\\l\\0\\c\\aAbBcCdDeEfF0011", mode ? "n" : "id");
        if(!CG_DecodeFireteam(text, mode, &decoded)) ++errors;
    }
    {
        const char *invalid[] = {"", "\\n\\-1", "\\n\\6\\l\\0\\c\\0000000000000001",
            "\\n\\0\\l\\64\\c\\ffffffffffffffff", "\\n\\0\\l\\-1\\c\\ffffffffffffffff",
            "\\n\\0\\l\\0\\c\\0000000000000000", "\\n\\0\\l\\0\\c\\000000000000000g",
            "\\n\\0\\l\\0\\c\\1", "\\n\\0junk\\l\\0\\c\\ffffffffffffffff"};
        for(i = 0; i < sizeof(invalid) / sizeof(invalid[0]); ++i) {
            decoded = sentinel;
            if(CG_DecodeFireteam(invalid[i], qtrue, &decoded) || memcmp(&decoded, &sentinel, sizeof(decoded))) ++errors;
        }
    }
    memset(cgs.clientinfo, 0, sizeof(cgs.clientinfo)); memset(&team, 0, sizeof(team));
    cg.clientNum = 0; cgs.gametype = GT_WOLF;
    team.inuse = qtrue; team.leader = 1;
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    for(i = 0; i < 4; ++i) {
        cgs.clientinfo[i].fireteamData = &team;
        cgs.clientinfo[i].rank = i;
        cgs.clientinfo[i].team = TEAM_AXIS;
    }
    for(i = 0; i < 64; ++i) for(j = 0; j < 64; ++j) {
        a = CG_SortFireTeam(&i, &j); b = CG_SortFireTeam(&j, &i);
        if((a < 0) != (b > 0) || (a > 0) != (b < 0) || (i == j && a != 0)) ++errors;
    }
    CG_SortClientFireteam();
    if(CG_SortedFireTeamPlayerForPosition(0, 6) != &cgs.clientinfo[1] ||
       CG_SortedFireTeamPlayerForPosition(1, 6) != &cgs.clientinfo[3] ||
       CG_SortedFireTeamPlayerForPosition(4, 6) || CG_SortedFireTeamPlayerForPosition(-1, 6) ||
       CG_IsOnFireteam(-1) || CG_IsOnFireteam(64)) ++errors;
    {
        rectDef_t rect = {10, 20, 0, 0};
        int savedIcons[SK_NUM_SKILLS], savedWidth = cgs.glconfig.vidWidth, savedHeight = cgs.glconfig.vidHeight;
        float savedX = cgs.screenXScale, savedY = cgs.screenYScale, savedBias = cgs.screenXBias;
        memcpy(savedIcons, cgs.media.skillPics, sizeof(savedIcons));
        for(i = 0; i < SK_NUM_SKILLS; ++i) cgs.media.skillPics[i] = 9000 + i;
        cgs.glconfig.vidWidth = 640; cgs.glconfig.vidHeight = 480;
        cgs.screenXScale = cgs.screenYScale = 1; cgs.screenXBias = 0;
        fireteamRenderTest = 1; fireteamRenderIcons = fireteamRenderErrors = 0;
        CG_DrawFireTeamOverlay(&rect);
        if(fireteamRenderIcons != 4 || fireteamRenderErrors) ++errors;
        cgs.clientinfo[0].team = TEAM_SPECTATOR;
        CG_DrawFireTeamOverlay(&rect);
        if(fireteamRenderIcons != 4) ++errors;
        cgs.clientinfo[0].team = TEAM_AXIS;
        team.ident = MAX_FIRETEAMS;
        CG_DrawFireTeamOverlay(&rect);
        if(fireteamRenderIcons != 4) ++errors;
        team.ident = 0; fireteamRenderTest = 0;
        memcpy(cgs.media.skillPics, savedIcons, sizeof(savedIcons));
        cgs.glconfig.vidWidth = savedWidth; cgs.glconfig.vidHeight = savedHeight;
        cgs.screenXScale = savedX; cgs.screenYScale = savedY; cgs.screenXBias = savedBias;
    }
    cgs.clientinfo[0].team = TEAM_SPECTATOR;
    if(CG_IsOnFireteam(0) || CG_IsOnSameFireteam(0, 1)) ++errors;
    cgs.clientinfo[0].team = TEAM_AXIS; cgs.gametype = 8;
    if(CG_IsOnFireteam(0)) ++errors;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\etmain");
    if(CG_IsOnFireteam(0) != &team) ++errors;
    {
        int *ends[] = {&cgs.applicationEndTime, &cgs.invitationEndTime, &cgs.propositionEndTime};
        int *clients[] = {&cgs.applicationClient, &cgs.invitationClient, &cgs.propositionClient};
        int savedEnds[3], savedIDs[3], savedSecond = cgs.propositionClient2, savedTime = cg.time;
        for(i = 0; i < 3; ++i) { savedEnds[i] = *ends[i]; savedIDs[i] = *clients[i]; *ends[i] = 0; }
        cg.time = 100; cgs.propositionClient2 = 0;
        for(i = 0; i < 3; ++i) {
            *ends[i] = 200; *clients[i] = MAX_CLIENTS;
            if(CG_FireteamGetBoxNeedsButtons() || CG_FireteamGetBoxText()) ++errors;
            *clients[i] = 0;
            if(!CG_FireteamGetBoxNeedsButtons() || !CG_FireteamGetBoxText()) ++errors;
            for(j = -4; j <= -1; ++j) {
                *clients[i] = j;
                if(CG_FireteamGetBoxNeedsButtons() || !CG_FireteamGetBoxText()) ++errors;
            }
            *ends[i] = 0;
        }
        cgs.propositionEndTime = 200; cgs.propositionClient = 0; cgs.propositionClient2 = MAX_CLIENTS;
        if(CG_FireteamGetBoxNeedsButtons() || CG_FireteamGetBoxText()) ++errors;
        for(i = 0; i < 3; ++i) { *ends[i] = savedEnds[i]; *clients[i] = savedIDs[i]; }
        cgs.propositionClient2 = savedSecond; cg.time = savedTime;
    }
    memcpy(cgs.clientinfo, savedClients, sizeof(savedClients)); cgs.gameState = savedGame;
    cg.clientNum = savedClient; cgs.gametype = savedType; CG_SortClientFireteam();
    return errors;
}
static int CheckScoreboardPlans(void) {
    int gametype, intermission, errors = 0;
    for(gametype = 0; gametype <= 9; ++gametype) for(intermission = 0; intermission < 2; ++intermission) {
        nitmodScoreboardPlan_t plan = CG_NitmodScoreboardPlan(gametype, intermission);
        int rows = intermission ? 20 : 25;
        if(gametype == GT_WOLF_STOPWATCH && intermission) rows = 15;
        if(plan.axisRows != rows || plan.alliedRows != rows || plan.deathmatch != (gametype == 8)) ++errors;
    }
    return errors;
}
static int CheckScoreboardOrder(void) {
    int errors = 0, i, protocol, order[MAX_CLIENTS], count;
    score_t before[MAX_CLIENTS];
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    cg.numScores = 5;
    for(i = 0; i < 5; ++i) {
        cg.scores[i].client = i;
        cg.scores[i].kills = i ? 20 : 10;
        cg.scores[i].deaths = i == 2 ? 1 : 5;
        /* Userinfo replacement must not own scoreboard counters. */
        cgs.clientinfo[i].kills = cgs.clientinfo[i].deaths = 0;
    }
    cg.scores[4].client = MAX_CLIENTS;
    memcpy(before, cg.scores, sizeof(before));
    for(protocol = 0; protocol < 2; ++protocol) {
        strcpy(cgs.gameState.stringData + 1, protocol ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        cg.nitmodScoreSortKD = qtrue;
        count = CG_NitmodScoreOrder(order, MAX_CLIENTS);
        if(count != 4) ++errors;
        for(i = 0; i < count; ++i) {
            const int expected[] = {2, 1, 3, 0};
            if(order[i] != (protocol ? expected[i] : i)) ++errors;
        }
        if(memcmp(before, cg.scores, sizeof(before))) ++errors;
    }
    cg.nitmodScoreSortKD = qfalse;
    if(CG_NitmodScoreOrder(order, 2) != 2 || order[0] != 0 || order[1] != 1) ++errors;
    if(CG_NitmodScoreOrder(NULL, 2) || CG_NitmodScoreOrder(order, 0)) ++errors;
    cg.numScores = -1;
    if(CG_NitmodScoreOrder(order, MAX_CLIENTS)) ++errors;
    cg.numScores = INT_MAX;
    for(i = 0; i < MAX_CLIENTS; ++i) cg.scores[i].client = i;
    if(CG_NitmodScoreOrder(order, MAX_CLIENTS) != MAX_CLIENTS) ++errors;
    /* Exact original press/cooldown boundaries, held key and rollback. */
    cg.showScores = qfalse; cg.nitmodScorePressSeen = qfalse;
    cg.nitmodScoreLastToggle = 0; cg.nitmodScoreSortKD = qfalse;
    cg.time = 1000; CG_NitmodScoreKeyDown();
    if(cg.nitmodScoreSortKD) ++errors;
    cg.time = 1249; CG_NitmodScoreKeyDown();
    if(!cg.nitmodScoreSortKD) ++errors;
    cg.time = 1500; CG_NitmodScoreKeyDown();
    cg.time = 1749; CG_NitmodScoreKeyDown(); /* cooldown exactly 500 */
    if(!cg.nitmodScoreSortKD) ++errors;
    cg.time = 1750; CG_NitmodScoreKeyDown();
    if(cg.nitmodScoreSortKD) ++errors;
    cg.time = 2400; CG_NitmodScoreKeyDown();
    cg.showScores = qtrue; cg.time = 2500; CG_NitmodScoreKeyDown();
    if(cg.nitmodScoreSortKD) ++errors;
    cg.showScores = qfalse; cg.time = 2000; CG_NitmodScoreKeyDown();
    if(cg.nitmodScoreSortKD) ++errors;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\etmain");
    cg.time = 2100; CG_NitmodScoreKeyDown();
    if(cg.nitmodScoreSortKD || cg.nitmodScoreLastPress != 2000) ++errors;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cg.nitmodScorePressSeen = cg.nitmodScoreSortKD = qfalse;
    cg.numScores = 0;
    return errors;
}
static int CheckClientExtras(void) {
    clientInfo_t client;
    int errors = 0, i, sc, tv, connecting;
    char info[128];
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    memset(&client, 0, sizeof(client));
    for(sc = 0; sc < 2; ++sc) for(tv = 0; tv < 2; ++tv) {
        Com_sprintf(info, sizeof(info), "\\sc\\%d\\tv\\%d\\xp\\1 2 3 4 5 6 7", sc, tv);
        NITMOD_ParseClientExtras(info, &client);
        if(client.nitmodTV != tv || client.nitmodShoutcaster != sc) ++errors;
        for(i = 0; i < SK_NUM_SKILLS; ++i) if(client.skillpoints[i] != i + 1) ++errors;
        for(connecting = 0; connecting < 2; ++connecting) {
            const char *expected = connecting ? "^3CONNECTING" :
                tv ? (sc ? "^5TV^7|^3SHOUTCASTER" : "^5TV^7|^3SPECTATOR") :
                sc ? "^3SHOUTCASTER" : "^3SPECTATOR";
            if(strcmp(CG_NitmodSpectatorLabel(&client, connecting ? -1 : 50), expected)) ++errors;
        }
    }
    NITMOD_ParseClientExtras("\\sc\\-1\\tv\\1bad\\xp\\  -5  20 ", &client);
    if(!client.nitmodShoutcaster || client.nitmodTV || client.skillpoints[0] != -5 || client.skillpoints[1] != 20) ++errors;
    for(i = 2; i < SK_NUM_SKILLS; ++i) if(client.skillpoints[i]) ++errors;
    {
        const char *invalid[] = {"1 2 bad", "2147483648", "1 2 3 4 5 6 7 8", "1\t2"};
        int k;
        for(k = 0; k < 4; ++k) {
            Com_sprintf(info, sizeof(info), "\\xp\\%s", invalid[k]);
            NITMOD_ParseClientExtras(info, &client);
            for(i = 0; i < SK_NUM_SKILLS; ++i) if(client.skillpoints[i]) ++errors;
            if(client.nitmodTV || client.nitmodShoutcaster) ++errors;
        }
    }
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\etmain");
    client.skillpoints[0] = 88;
    NITMOD_ParseClientExtras("\\sc\\1\\tv\\1\\xp\\99", &client);
    if(client.skillpoints[0] != 88 || client.nitmodTV || client.nitmodShoutcaster) ++errors;
    if(strcmp(CG_NitmodSpectatorLabel(&client, 20), "^3SPECTATOR")) ++errors;
    NITMOD_ParseClientExtras(NULL, NULL);
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    return errors;
}
static int CheckCountryFlagAtlas(void) {
    int code, errors = 0;
    for(code = -1; code <= 255; ++code) {
        float s0 = -1, t0 = -1, s1 = -1, t1 = -1;
        qboolean valid = CG_NitmodCountryFlagUV(code, &s0, &t0, &s1, &t1);
        if(valid != (code >= 0 && code < 255)) { ++errors; continue; }
        if(valid && (fabs(s0 - (code & 15) / 16.f) > .0001f ||
           fabs(t0 - (code >> 4) / 16.f) > .0001f ||
           fabs(s1 - s0 - 1.f / 16.f) > .0001f || fabs(t1 - t0 - 1.f / 16.f) > .0001f)) ++errors;
    }
    if(CG_NitmodCountryFlagUV(1, NULL, NULL, NULL, NULL)) ++errors;
    for(code = 0; code < 255; ++code) {
        char value[8]; Com_sprintf(value, sizeof(value), "%i", code);
        if(NITMOD_ParseCountryCode(value) != code) ++errors;
    }
    if(NITMOD_ParseCountryCode("") != 255 || NITMOD_ParseCountryCode("-1") != 255 ||
       NITMOD_ParseCountryCode("255") != 255 || NITMOD_ParseCountryCode("1x") != 255 ||
       NITMOD_ParseCountryCode("2147483648") != 255) ++errors;
    return errors;
}
static int popupTest, popupIcons, popupErrors, popupDraws;
static int grenadeCardTest, grenadeCardDraws;
static float grenadeCardRect[4];
static int timerTest, timerWrites;
static int classTest, classSends;
static int preferenceTest, preferenceWrites, preferenceValue;
static char classCommand[128];
static char timerPeriod[32], timerStart[32];
static float popupFirstY;
static int ammoTest, ammoBars;
static vec4_t ammoColor, ammoColors[300];
static float ammoRects[300][4];
static int CheckModernAmmo(void) {
    int savedFlags = cg_HUDFlags.integer, savedShader = cgs.media.whiteShader;
    int savedCapacity = GetAmmoTableData(WP_MP40)->maxclip;
    float sx = cgs.screenXScale, sy = cgs.screenYScale, bias = cgs.screenXBias;
    int caps[] = {1, 8, 30, 50, 51, 100, 101, 150};
    int flags, c, clip, dual, i, errors = 0;
    ammoTest = 1; cgs.media.whiteShader = 9876;
    cgs.screenXScale = 2; cgs.screenYScale = 1.5f; cgs.screenXBias = 0;
    for(flags = 0; flags < 32; ++flags) for(c = 0; c < 8; ++c)
    for(clip = 0; clip <= caps[c] + 1; ++clip) for(dual = 0; dual < 2; ++dual) {
        int capacity = caps[c], second = capacity - clip;
        if(second < 0) second = 0;
        cg_HUDFlags.integer = flags; GetAmmoTableData(WP_MP40)->maxclip = capacity;
        ammoBars = 0;
        if(CG_NitmodDrawAmmo(WP_MP40, clip, 90, dual ? second : -1) != !!(flags & 16)) ++errors;
        if(ammoBars != ((flags & 16) ? capacity * (dual + 1) : 0)) ++errors;
        for(i = 0; i < ammoBars; ++i) {
            int hand = i / capacity, index = i % capacity;
            int count = dual && !hand ? second : clip;
            float x = 1180 - 3 * (dual ? index : index % 50);
            float y = dual ? (hand ? 696 : 687) : 687 + (index / 50) * 7.5f;
            if(ammoRects[i][0] != x || ammoRects[i][1] != y ||
               ammoRects[i][2] != 2 || ammoRects[i][3] != 6 ||
               ammoColors[i][0] != 1 || ammoColors[i][1] != (count <= capacity / 4 ? 0 : 1) ||
               ammoColors[i][2] != ammoColors[i][1] ||
               fabs(ammoColors[i][3] - (index >= count ? .35f : 1)) > .00001) ++errors;
        }
    }
    ammoBars = 0; cg_HUDFlags.integer = 16;
    if(CG_NitmodDrawAmmo(-1, 1, 1, -1) || CG_NitmodDrawAmmo(WP_NUM_WEAPONS, 1, 1, -1) ||
       CG_NitmodDrawAmmo(WP_MP40, -1, 1, -1) || CG_NitmodDrawAmmo(WP_MP40, 1, -1, -1)) ++errors;
    GetAmmoTableData(WP_MP40)->maxclip = 151;
    if(CG_NitmodDrawAmmo(WP_MP40, 1, 1, -1)) ++errors;
    GetAmmoTableData(WP_MP40)->maxclip = 0;
    if(CG_NitmodDrawAmmo(WP_MP40, 1, 1, -1) || ammoBars) ++errors;
    ammoTest = 0; GetAmmoTableData(WP_MP40)->maxclip = savedCapacity;
    cg_HUDFlags.integer = savedFlags; cgs.media.whiteShader = savedShader;
    cgs.screenXScale = sx; cgs.screenYScale = sy; cgs.screenXBias = bias;
    return errors;
}
static int CheckKillNotification(void) {
    int flags, team, errors = 0, savedFlags = cg_HUDFlags.integer, savedTime = cg.time;
    char text[256];
    memset(text, 'A', sizeof(text)); text[255] = 0;
    for(flags = 0; flags < 32; ++flags) for(team = 0; team <= 1; ++team) {
        int expected = (flags & 4) && !team;
        CG_NitmodHudReset(); cg_HUDFlags.integer = flags;
        if(CG_NitmodKillPrint("You killed target", team, 100) != expected) ++errors;
        if(CG_NitmodKillPrintAlpha(100) != (expected ? 1 : 0)) ++errors;
        if(CG_NitmodKillPrintAlpha(1025) != (expected ? .5f : 0)) ++errors;
        if(CG_NitmodKillPrintAlpha(1950) || *CG_NitmodKillPrintText()) ++errors;
    }
    cg_HUDFlags.integer = 4;
    CG_NitmodKillPrint(text, qfalse, 0);
    if(strlen(CG_NitmodKillPrintText()) != 63) ++errors;
    CG_NitmodKillPrint("replacement", qfalse, 1000);
    if(strcmp(CG_NitmodKillPrintText(), "replacement") || CG_NitmodKillPrintAlpha(1000) != 1) ++errors;
    if(CG_NitmodKillPrint("team warning", qtrue, 1100) || strcmp(CG_NitmodKillPrintText(), "replacement")) ++errors;
    CG_NitmodKillPrint("draw", qfalse, 1000);
    popupTest = 1; popupDraws = 0; cg.time = 1100;
    CG_NitmodDrawKillPrint();
    if(!popupDraws) ++errors;
    popupDraws = 0; cg.time = 2850;
    CG_NitmodDrawKillPrint();
    if(popupDraws) ++errors;
    popupTest = 0;
    CG_NitmodKillPrint("reset", qfalse, 0); CG_NitmodHudReset();
    if(*CG_NitmodKillPrintText() || CG_NitmodKillPrintAlpha(0)) ++errors;
    cg_HUDFlags.integer = savedFlags; cg.time = savedTime;
    return errors;
}
static int CheckNotification(void) {
    int errors = 0, savedTime = cg.time, hold, fade;
    int flags, savedFlags = cg_HUDFlags.integer;
    char large[2048];
    for(flags = 0; flags < 32; ++flags) {
        cg_HUDFlags.integer = flags;
        CG_NitmodHudReset();
        if(CG_NitmodSpreeUsesLeft() != !!(flags & 8)) ++errors;
        CG_NitmodNotificationStart("notice", 100);
        if(!CG_NitmodSpreeUsesLeft()) ++errors;
        CG_NitmodNotificationAlpha(225, 1500, 250);
        if(!CG_NitmodSpreeUsesLeft()) ++errors;
        CG_NitmodNotificationAlpha(350, 1500, 250);
        if(!CG_NitmodSpreeUsesLeft()) ++errors;
        CG_NitmodNotificationAlpha(1975, 1500, 250);
        if(!CG_NitmodSpreeUsesLeft()) ++errors;
        CG_NitmodNotificationAlpha(2100, 1500, 250);
        if(CG_NitmodSpreeUsesLeft() != !!(flags & 8)) ++errors;
        CG_NitmodNotificationStart("disabled fade", 100);
        CG_NitmodNotificationAlpha(2100, 1500, 0);
        /* Original zero fade returns before clearing the active state. */
        if(!CG_NitmodSpreeUsesLeft()) ++errors;
        CG_NitmodNotificationStart("", 100);
        if(CG_NitmodSpreeUsesLeft() != !!(flags & 8)) ++errors;
        CG_NitmodNotificationStart("reset", 100); CG_NitmodHudReset();
        if(CG_NitmodSpreeUsesLeft() != !!(flags & 8)) ++errors;
    }
    cg_HUDFlags.integer = savedFlags;
    for(hold = 0; hold <= 12000; hold += 1500) for(fade = 50; fade <= 300; fade += 50) {
        int h = hold < 1500 ? 1500 : hold > 10000 ? 10000 : hold;
        int f = fade > 250 ? 250 : fade;
        CG_NitmodNotificationStart("notice", 100);
        if(CG_NitmodNotificationAlpha(100, (float)hold, (float)fade) != 0 ||
           CG_NitmodNotificationAlpha(100 + f/2, (float)hold, (float)fade) != .5f ||
           CG_NitmodNotificationAlpha(100 + f, (float)hold, (float)fade) != 1 ||
           CG_NitmodNotificationAlpha(100 + f + h, (float)hold, (float)fade) != 1 ||
           CG_NitmodNotificationAlpha(100 + f + h + f/2, (float)hold, (float)fade) != .5f ||
           CG_NitmodNotificationAlpha(100 + f + h + f, (float)hold, (float)fade) != 0) ++errors;
    }
    CG_NitmodNotificationStart("disabled", 0);
    if(CG_NitmodNotificationAlpha(100, 8000, 0) || CG_NitmodNotificationAlpha(100, 8000, -1)) ++errors;
    memset(large, 'x', sizeof(large)); large[sizeof(large)-1] = 0;
    CG_NitmodNotificationStart(large, 100);
    if(strlen(CG_NitmodNotificationText()) != MAX_STRING_CHARS - 1) ++errors;
    CG_NitmodNotificationStart("replacement", 100);
    if(strcmp(CG_NitmodNotificationText(), "replacement")) ++errors;
    cg_notificationTime.value = 8000; cg_notificationFadeTime.value = 250;
    popupTest = 1; popupDraws = popupErrors = 0; cg.time = 225;
    CG_NitmodDrawNotification();
    if(!popupDraws || popupErrors) ++errors;
    CG_NitmodHudReset(); popupDraws = 0;
    CG_NitmodDrawNotification();
    if(popupDraws || *CG_NitmodNotificationText()) ++errors;
    popupTest = 0; cg.time = savedTime;
    return errors;
}
extern struct pmStackItem_s *cg_pmWaitingList, *cg_pmOldList;
static int graphicPopupTest, graphicFirstGlyph, graphicIcons, graphicPrints;
static float graphicIconWidth;
static int CheckGraphicPopups(void) {
    static cgs_t savedCgs;
    static weaponInfo_t savedWeapon;
    weaponInfo_t savedKnife = cg_weapons[WP_KNIFE];
    entityState_t es;
    int mode, cause, i, errors = 0, oldMode = cg_obituary.integer, oldTime = cg.time;
    int oldCount = cg_numPopups.integer, oldFlags = cg_HUDFlags.integer;
    savedCgs = cgs; savedWeapon = cg_weapons[WP_MP40];
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    strcpy(cgs.clientinfo[1].name, "A"); strcpy(cgs.clientinfo[2].name, "B");
    cgs.clientinfo[1].team = TEAM_AXIS; cgs.clientinfo[2].team = TEAM_ALLIES;
    cgs.glconfig.vidWidth = 640; cgs.glconfig.vidHeight = 480;
    cgs.screenXScale = cgs.screenYScale = 1;
    memset(&cgs.media.limboFont1, 0, sizeof(cgs.media.limboFont1));
    cgs.media.limboFont1.glyphScale = 1;
    for(i = 'A'; i <= 'B'; ++i) {
        glyphInfo_t *glyph = &cgs.media.limboFont1.glyphs[i];
        glyph->glyph = 700 + i - 'A'; glyph->height = glyph->xSkip = 10;
        glyph->imageHeight = glyph->imageWidth = 10;
    }
    cg_weapons[WP_MP40].weaponIcon[0] = 901; cg_weapons[WP_MP40].weaponIconScale = 2;
    cg_weapons[WP_KNIFE].weaponIcon[0] = 901; cg_weapons[WP_KNIFE].weaponIconScale = 2;
    memset(&es, 0, sizeof(es)); es.otherEntityNum = 1; es.otherEntityNum2 = 2; es.eventParm = 8;
    graphicPopupTest = 1; cg.time = 100; cg_numPopups.integer = 6; cg_HUDFlags.integer = 0;
    for(cause = 0; cause < 2; ++cause) for(mode = 3; mode <= 4; ++mode) {
        es.eventParm = cause ? 63 : 8;
        CG_InitPM(); cg_obituary.integer = mode;
        graphicPrints = graphicIcons = graphicFirstGlyph = 0;
        CG_NitmodObituaryPrint("test kill", 789, &es);
        CG_DrawPMItems();
        if(graphicPrints != 1 || graphicIcons != 1 || graphicIconWidth != 32 ||
           graphicFirstGlyph != (mode == 3 ? 701 : 700)) ++errors;
    }
    CG_InitPM();
    for(mode = 3; mode <= 4; ++mode) for(cause = 0; cause < 3; ++cause) {
        CG_InitPM(); cg_obituary.integer = mode;
        es.eventParm = cause == 2 ? 65 : 26;
        es.otherEntityNum2 = cause == 0 ? ENTITYNUM_WORLD : cause == 1 ? 1 : 2;
        graphicPrints = graphicIcons = graphicFirstGlyph = 0;
        CG_NitmodObituaryPrint("world/self/private", 789, &es);
        CG_DrawPMItems();
        if(graphicPrints != 1 || graphicIcons != 1 || graphicIconWidth != 16 ||
           graphicFirstGlyph != (cause == 2 && mode == 3 ? 701 : 700)) ++errors;
    }
    CG_InitPM();
    if(CG_NitmodAddGraphicObituary("", "B", 901, 2, colorWhite) ||
       CG_NitmodAddGraphicObituary("A", "B", 0, 2, colorWhite) ||
       CG_NitmodAddGraphicObituary("A", "B", 901, 5, colorWhite)) ++errors;
    for(i = 0; i < 33; ++i)
        if(CG_NitmodAddGraphicObituary("A", "B", 901, 2, colorWhite) != (i < 32)) ++errors;
    ++cg.time; CG_UpdatePMLists();
    ++cg.time; CG_UpdatePMLists();
    {
        struct pmStackItem_s *retained = cg_pmOldList;
        if(!retained || !CG_NitmodAddGraphicObituary("A", "B", 901, 2, colorWhite) ||
           cg_pmOldList != retained) ++errors; /* recycling the oldest must not orphan its predecessor */
    }
    CG_InitPM();
    CG_AddPMItem(PM_DEATH, "ordinary", 789);
    graphicFirstGlyph = graphicIcons = 0; CG_DrawPMItems();
    if(graphicFirstGlyph || graphicIcons != 1 || graphicIconWidth != 12) ++errors;
    graphicPopupTest = 0; CG_InitPM(); cgs = savedCgs; cg_weapons[WP_MP40] = savedWeapon;
    cg_weapons[WP_KNIFE] = savedKnife;
    cg_obituary.integer = oldMode; cg.time = oldTime; cg_numPopups.integer = oldCount; cg_HUDFlags.integer = oldFlags;
    return errors;
}

static int CheckPopupOptions(void) {
    int n, flags, i, expected, errors = 0, savedTime = cg.time;
    float savedX = cgs.screenXScale, savedY = cgs.screenYScale;
    cgs.screenXScale = cgs.screenYScale = 1;
    cg_popupFadeTime.integer = 6000;
    CG_InitPM(); cg.time = 100;
    for(i = 0; i < 9; ++i) CG_AddPMItem(PM_MESSAGE, "popup", 123);
    CG_UpdatePMLists();
    if(cg_pmOldList) ++errors; /* no queue advance in the same millisecond */
    for(i = 0; i < 8; ++i) { ++cg.time; CG_UpdatePMLists(); }
    popupTest = 1; popupErrors = 0;
    for(n = -1; n <= 10; ++n) for(flags = 0; flags < 4; ++flags) {
        cg_numPopups.integer = n; cg_HUDFlags.integer = flags;
        popupIcons = 0;
        CG_DrawPMItems();
        expected = n <= 0 ? 0 : flags & 2 ? 5 : n > 8 ? 8 : n;
        if(popupIcons != expected) ++errors;
        if(expected && popupFirstY != (flags & 2 ? 70 : flags & 1 ? 310 : 360)) ++errors;
    }
    popupTest = 0; errors += popupErrors;
    cg.time = 7608; CG_UpdatePMLists();
    if(!cg_pmWaitingList || cg_pmOldList) ++errors;
    cg.time++; CG_UpdatePMLists();
    if(cg_pmWaitingList || cg_pmOldList) ++errors;
    if(CG_NitmodPopupAlpha(100, 1600, 6000) != 1 ||
       CG_NitmodPopupAlpha(100, 4600, 6000) != .5f ||
       CG_NitmodPopupAlpha(100, 7600, 6000) != 0 ||
       CG_NitmodPopupAlpha(100, 1601, 0) != 0 ||
       CG_NitmodPopupAlpha(100, 1601, -1) != 0 ||
       CG_NitmodPopupAlpha(100, 50, 6000) != 1) ++errors;
    CG_InitPM(); cg.time = savedTime;
    cgs.screenXScale = savedX; cgs.screenYScale = savedY;
    cg_numPopups.integer = 6; cg_HUDFlags.integer = 4;
    return errors;
}

static int CheckParticleOptions(void) {
    static const int values[] = {-1, 0, 1, 2};
    int smoke, trail, impact, kind, errors = 0;
    for(smoke = 0; smoke < 4; ++smoke) for(trail = 0; trail < 4; ++trail)
    for(impact = 0; impact < 4; ++impact) for(kind = 0; kind < 8; ++kind) {
        centity_t cent;
        vec3_t origin = {0,0,0}, end = {0,0,10}, dir = {1,0,0};
        struct particle_s *before;
        int enabled = kind == 0 ? values[trail] : (kind == 4 || kind >= 6) ? values[impact] : values[smoke];
        memset(&cent, 0, sizeof(cent));
        cg_smokeparticles.integer = values[smoke];
        cg_trailparticles.integer = values[trail];
        cg_impactparticles.integer = values[impact];
        particleInit = 1; CG_ClearParticles(); particleInit = 0;
        before = free_particles;
        switch(kind) {
        case 0: CG_ParticleBubble(1, origin, end, 0, 10, 0); break;
        case 1: CG_ParticleSmoke(1, &cent); break;
        case 2: CG_ParticleImpactSmokePuff(1, origin); break;
        case 3: CG_ParticleImpactSmokePuffExtended(1, origin, 500, 20, 20, 30, .25f, 8); break;
        case 4: CG_ParticleSparks(origin, dir, 500, 1, 1, 10); break;
        case 5: CG_ParticleDust(&cent, origin, dir); break;
        case 6: CG_AddBulletParticles(origin, dir, 20, 500, 3, 1); break;
        case 7: CG_AddDirtBulletParticles(origin, dir, 20, 500, 3, 1, 8, 8, .5f, 1); break;
        }
        if(enabled) { if(!active_particles || free_particles == before) ++errors; }
        else if(active_particles || free_particles != before || dir[0] != 1 || dir[1] || dir[2]) ++errors;
    }
    {
        int wolf, trail, kind, savedWolf = cg_wolfparticles.integer;
        for(wolf = 0; wolf < 4; ++wolf) for(trail = 0; trail < 4; ++trail)
        for(kind = 0; kind < 2; ++kind) {
            vec3_t origin = {1,2,3}, velocity = {4,5,6};
            struct particle_s *before;
            int enabled = kind ? values[trail] : values[wolf];
            int expectedRandom, actualRandom;
            cg_wolfparticles.integer = values[wolf];
            cg_trailparticles.integer = values[trail];
            particleInit = 1; CG_ClearParticles(); particleInit = 0;
            before = free_particles;
            srand(123); expectedRandom = rand(); srand(123);
            /* Negative duration avoids roll RNG, as in the original. Disabled
             * calls must not even dereference their animation/position inputs. */
            if(kind) CG_ParticleExplosionTrail(enabled ? "twiltb2" : NULL,
                enabled ? origin : NULL, enabled ? velocity : NULL, -100, 5, 12, qfalse);
            else CG_ParticleExplosion(enabled ? "explode1" : NULL,
                enabled ? origin : NULL, enabled ? velocity : NULL, -100, 5, 12, qtrue);
            actualRandom = rand();
            if(actualRandom != expectedRandom) ++errors;
            if(enabled) {
                if(active_particles != before || free_particles == before) ++errors;
            } else if(active_particles || free_particles != before) ++errors;
        }
        cg_wolfparticles.integer = savedWolf;
    }
    {
        static const int types[] = {ET_MISSILE, ET_FLAMEBARREL, ET_FP_PARTS,
            ET_RAMJET, ET_FIRE_COLUMN, ET_FIRE_COLUMN_SMOKE};
        int type, wolf, liquid, savedTime = cg.time;
        int savedWolf = cg_wolfparticles.integer;
        cg_trailparticles.integer = 1;
        particleTrailTest = 1;
        for(type = 0; type < 6; ++type) for(wolf = 0; wolf < 2; ++wolf)
        for(liquid = 0; liquid < 2; ++liquid) {
            centity_t cent;
            memset(&cent, 0, sizeof(cent));
            cent.currentState.eType = types[type];
            cent.currentState.pos.trType = TR_LINEAR;
            cent.currentState.pos.trDelta[0] = 100;
            cent.trailTime = 100;
            cg.time = 200;
            cg_wolfparticles.integer = wolf;
            particleTrailContents = liquid ? CONTENTS_SLIME : 0;
            particleInit = 1; CG_ClearParticles(); particleInit = 0;
            CG_RocketTrail(&cent, NULL);
            if(cent.trailTime != cg.time || (!!active_particles) != !liquid) ++errors;
        }
        particleTrailTest = 0;
        cg.time = savedTime;
        cg_wolfparticles.integer = savedWolf;
    }
    cg_trailparticles.integer = 0;
    /* Disabled trail must return before entity dereferences or engine traces. */
    CG_RocketTrail(NULL, NULL);
    cg_smokeparticles.integer = cg_trailparticles.integer = cg_impactparticles.integer = 1;
    {
        playerState_t ps;
        int mode, flesh, source, viewed;
        memset(&ps, 0, sizeof(ps));
        for(mode = -1; mode <= 3; ++mode) {
            if(!CG_NitmodMuzzleFlashEnabled(mode, NULL) ||
               CG_NitmodMuzzleFlashEnabled(mode, &ps) != (mode != 0)) ++errors;
            for(flesh = 0; flesh <= 1; ++flesh) for(source = 0; source < 4; ++source)
            for(viewed = 0; viewed < 4; ++viewed) {
                int expected = flesh ? mode != 0 : mode == 1 || (mode == 2 && source != viewed);
                if(CG_NitmodTracerEnabled(mode, flesh, source, viewed) != expected) ++errors;
            }
        }
    }
    return errors;
}
extern animStringItem_t weaponStrings[];
extern qboolean BG_ParseConditions(char **, animScriptItem_t *);
extern qboolean BG_EvaluateConditions(int, animScriptItem_t *);
static int CheckOriginalAnimationConditions(const char *path) {
    static animModelInfo_t model;
    static animScriptData_t scripts;
    static animation_t animationStubs[MAX_MODEL_ANIMATIONS];
    const char *extra[] = {"Poison Syringe", "Bomb", "Poison Bomb", "Poison Landmine"};
    char *text, *end, *line;
    long size;
    FILE *file = fopen(path, "rb");
    int i, count = 0, errors = 0;
    if(!file) return 1;
    fseek(file, 0, SEEK_END); size = ftell(file); rewind(file);
    if(size <= 0 || size > 1024 * 1024) { fclose(file); return 1; }
    text = malloc(size + 1);
    if(!text) { fclose(file); return 1; }
    if(fread(text, 1, size, file) != (size_t)size) { fclose(file); free(text); return 1; }
    fclose(file); text[size] = 0;
    /* Supply only synthetic model metadata for script-referenced names.
     * This exercises the full script grammar, not real MDX/model loading. */
    {
        char *cursor = text, *token;
        while(*(token = COM_Parse(&cursor))) {
            if(!Q_stricmp(token, "both") || !Q_stricmp(token, "legs") || !Q_stricmp(token, "torso")) {
                token = COM_Parse(&cursor);
                for(i = 0; i < model.numAnimations; ++i)
                    if(!Q_stricmp(animationStubs[i].name, token)) break;
                if(i == model.numAnimations) {
                    if(!*token || i >= MAX_MODEL_ANIMATIONS) { free(text); return 1; }
                    Q_strncpyz(animationStubs[i].name, token, sizeof(animationStubs[i].name));
                    animationStubs[i].nameHash = BG_StringHashValue(token);
                    animationStubs[i].duration = 100;
                    animationStubs[i].numFrames = 1;
                    model.animations[model.numAnimations++] = &animationStubs[i];
                }
            }
        }
    }
    BG_InitWeaponStrings();
    for(i = 1; i < WP_NUM_WEAPONS; ++i) {
        gitem_t *item;
        for(item = bg_itemlist + 1; item->classname; ++item)
            if(item->giType == IT_WEAPON && item->giTag == i) break;
        if(item->classname && BG_IndexForString(item->pickup_name, weaponStrings, qfalse) != i) ++errors;
    }
    for(i = 0; i < 4; ++i) {
        char condition[128], *cursor = condition;
        animScriptItem_t item;
        int bit;
        memset(&item, 0, sizeof(item));
        Com_sprintf(condition, sizeof(condition), "weapons %s\n", extra[i]);
        BG_ParseConditions(&cursor, &item);
        if(item.numConditions != 1) ++errors;
        for(bit = 0; bit < 64; ++bit)
            if(!!COM_BitCheck(item.conditions[0].value, bit) != (bit == WP_NUM_WEAPONS + i)) ++errors;
    }
    if(BG_IndexForString("not-a-weapon", weaponStrings, qtrue) != -1) ++errors;
    end = strstr(text, "\nANIMATIONS");
    if(!end) { free(text); return 1; }
    *end = 0;
    /* Execute the original definitions, not rewritten/filtered operands. */
    BG_AnimParseAnimScript(&model, &scripts, path, text);
    *end = '\n';
    BG_AnimParseAnimScript(&model, &scripts, path, text);
    if(model.numScriptItems < 50 || model.numAnimations < 50) ++errors;
    {
        int extraIndex, candidate, client, evaluated = 0;
        for(extraIndex = 0; extraIndex < 4; ++extraIndex) {
            char expression[128], *cursor = expression;
            animScriptItem_t item;
            memset(&item, 0, sizeof(item));
            Com_sprintf(expression, sizeof(expression), "weapons %s\n", extra[extraIndex]);
            BG_ParseConditions(&cursor, &item);
            for(client = 0; client < MAX_CLIENTS; ++client) {
                for(candidate = 0; candidate < WP_NUM_WEAPONS + 4; ++candidate) {
                    BG_UpdateConditionValue(client, ANIM_COND_WEAPON, candidate, qtrue);
                    if(!!BG_EvaluateConditions(client, &item) !=
                       (candidate == WP_NUM_WEAPONS + extraIndex)) ++errors;
                    ++evaluated;
                }
            }
        }
        printf("Animation-only condition separation: %d evaluations\n", evaluated);
    }
    {
        struct { const char *weapon; const char *animation; } cases[] = {
            {"Poison Syringe", "stand_knife"},
            {"Bomb", "stand_grenade"},
            {"Poison Bomb", "stand_grenade"},
            {"Poison Landmine", "stand_medpack"},
            {"Tripmine", "stand_grenade"},
            {"Smoke Bomb", "stand_grenade"},
            {"Landmine", "stand_medpack"}
        };
        int test;
        for(test = 0; test < sizeof(cases) / sizeof(cases[0]); ++test) {
            int selected, weapon = BG_IndexForString((char *)cases[test].weapon, weaponStrings, qfalse);
            memset(scripts.clientConditions[0], 0, sizeof(scripts.clientConditions[0]));
            BG_UpdateConditionValue(0, ANIM_COND_WEAPON, weapon, qtrue);
            selected = BG_GetAnimScriptAnimation(0, &model, AISTATE_COMBAT, ANIM_MT_IDLE);
            if(selected < 0 || selected >= model.numAnimations ||
               strcmp(model.animations[selected]->name, cases[test].animation)) ++errors;
        }
    }
    {
        int itemIndex, commandIndex, part, commands = 0;
        for(itemIndex = 0; itemIndex < model.numScriptItems; ++itemIndex) {
            animScriptItem_t *item = &model.scriptItems[itemIndex];
            for(commandIndex = 0; commandIndex < item->numCommands; ++commandIndex) {
                animScriptCommand_t *command = &item->commands[commandIndex];
                ++commands;
                for(part = 0; part < 2; ++part) {
                    if(command->bodyPart[part] > 0 &&
                       (command->animIndex[part] < 0 || command->animIndex[part] >= model.numAnimations)) ++errors;
                }
            }
        }
        if(commands < 50) ++errors;
        printf("Original script parsed: %d model-name stubs, %d items, %d commands (not MDX validation)\n",
               model.numAnimations, model.numScriptItems, commands);
    }
    line = end + 1;
    while(line && *line) {
        char *next = strchr(line, '\n'), *cursor = line;
        if(next) *next = 0;
        while(*cursor == ' ' || *cursor == '\t') ++cursor;
        if(!strncmp(cursor, "weapons ", 8)) {
            animScriptItem_t item;
            memset(&item, 0, sizeof(item));
            BG_ParseConditions(&cursor, &item);
            if(!item.numConditions) ++errors;
            ++count;
        }
        line = next ? next + 1 : NULL;
    }
    free(text);
    return errors + (count < 50);
}
static const char *fields[21] = {"ct", "11", "22", "33", "44", "55", "66", "77", "88", "99", "110", "121"};
static int argcValue = 11, prints;
static int fogCalls;
static int spreeSoundTest, spreeRegistrations, spreePlays, spreeLastSound, spreeSoundFailure;
static int announcerTest, announcerLoads, announcerPlays, announcerHandle, announcerMissing;
static int CheckAnnouncer(void) {
    int mode, type, i, errors = 0, oldTime = cg.time, oldCvar = cg_announcer.integer;
    int oldArgc = argcValue;
    const char *savedFields[21];
    const int times[] = {-1, 0, 500, 999, 1000};
    gameState_t savedGame = cgs.gameState;
    float scale;
    vec4_t color;
    memcpy(savedFields, fields, sizeof(fields));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    announcerTest = 1; announcerLoads = announcerMissing = 0;
    CG_NitmodRegisterAnnouncerSounds(); if(announcerLoads != 2) ++errors;
    popupTest = 1;
    for(mode = -1; mode <= 2; ++mode) for(type = -1; type <= 0; ++type) {
        CG_NitmodHudReset(); cg.time = 1000; cg_announcer.integer = mode;
        fields[0] = "an"; fields[1] = type ? "-1" : "0"; argcValue = 2;
        announcerPlays = 0;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(announcerPlays != !!mode || (mode && announcerHandle != (type ? 302 : 301))) ++errors;
        if(strcmp(CG_NitmodAnnouncerText(), !mode ? "" : type ? "PREPARE TO FIGHT!" : "FIGHT!")) ++errors;
        for(i = 0; i < 5; ++i) {
            float expected = (.1f + (times[i] < 0 ? 0 : times[i]) / 1000.0f) * (type ? .85f : 1.1f);
            int active = mode && times[i] < 1000;
            if(CG_NitmodAnnouncerFrame(1000 + times[i], &scale, color) != !!active) ++errors;
            if(active && (fabs(scale - expected) > .00001 || color[0] != 1 ||
                color[1] != !!type || color[2] != 0 || color[3] != 1)) ++errors;
            cg.time = 1000 + times[i]; popupDraws = 0; CG_NitmodDrawAnnouncer();
            if(!!popupDraws != !!active) ++errors;
        }
    }
    {
        int protocol, previous, enabled, repeat;
        int savedState = cgs.gamestate, savedRound = cgs.currentRound;
        int savedMap = cgs.currentCampaignMap;
        float savedLimit = cgs.nextTimeLimit;
        const char *savedCampaign = cgs.currentCampaign;
        qboolean savedLocal = cgs.localServer;
        cgs.localServer = qtrue;
        cgs.gameState.stringOffsets[CS_WOLFINFO] = 100;
        for(protocol = 0; protocol < 2; ++protocol)
        for(previous = GS_PLAYING; previous <= GS_RESET; ++previous)
        for(enabled = 0; enabled < 2; ++enabled) {
            int expected = protocol && enabled && previous != GS_PLAYING;
            strcpy(cgs.gameState.stringData + 1, protocol ? "\\gamename\\nitmod" : "\\gamename\\etmain");
            strcpy(cgs.gameState.stringData + 100, "\\gamestate\\0");
            cgs.gamestate = previous; cg_announcer.integer = enabled;
            CG_NitmodHudReset(); announcerPlays = 0;
            for(repeat = 0; repeat < 3; ++repeat) {
                CG_ParseWolfinfo();
                if(cgs.gamestate != GS_PLAYING || announcerPlays != expected ||
                   !!CG_NitmodAnnouncerText()[0] != expected) ++errors;
            }
            /* A non-playing update must not enqueue a second announcement. */
            strcpy(cgs.gameState.stringData + 100, "\\gamestate\\2");
            CG_ParseWolfinfo();
            if(announcerPlays != expected) ++errors;
        }
        strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
        cgs.localServer = savedLocal; cgs.gamestate = savedState;
        cgs.currentRound = savedRound; cgs.nextTimeLimit = savedLimit;
        cgs.currentCampaignMap = savedMap; cgs.currentCampaign = savedCampaign;
    }
    cg_announcer.integer = 1; cg.time = 2000; CG_NitmodAnnounce(-1);
    cg.time = 2200; CG_NitmodAnnounce(0);
    if(strcmp(CG_NitmodAnnouncerText(), "FIGHT!")) ++errors;
    cg_announcer.integer = 0;
    if(CG_NitmodAnnouncerFrame(2300, &scale, color)) ++errors;
    CG_NitmodAnnounce(-1);
    cg_announcer.integer = 1;
    if(!CG_NitmodAnnouncerFrame(2300, &scale, color) || strcmp(CG_NitmodAnnouncerText(), "FIGHT!")) ++errors;
    announcerLoads = announcerPlays = 0; announcerMissing = 1;
    CG_NitmodRegisterAnnouncerSounds(); CG_NitmodAnnounce(0); CG_NitmodAnnounce(-1);
    if(announcerLoads != 2 || announcerPlays) ++errors;
    CG_NitmodHudReset();
    if(CG_NitmodAnnouncerFrame(cg.time, &scale, color)) ++errors;
    announcerTest = popupTest = 0; cg.time = oldTime; cg_announcer.integer = oldCvar;
    argcValue = oldArgc; memcpy(fields, savedFields, sizeof(fields)); cgs.gameState = savedGame;
    return errors;
}
static int CheckSpecialPrint(void) {
    const char *labels[] = {"REVENGE!", "KILL ASSISTANCE!", "SUICIDE HELPER!",
        "TEAMKILL ASSISTANCE!", "FIRST BLOOD!", "FIRST HEADSHOT!"};
    const int types[] = {-2, 1, 2, 3, 4, 5};
    const int times[] = {0, 100, 143, 144, 200, 1399, 1400};
    const char *bad[] = {"", "-", "1x", "1.5", "2147483648", "-2147483649"};
    const char *savedFields[21];
    gameState_t savedGame = cgs.gameState;
    int savedTime = cg.time, savedArgc = argcValue, i, j, errors = 0;
    vec4_t color;
    float scale;
    char type[16];
    memcpy(savedFields, fields, sizeof(fields));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    popupTest = 1;
    for(i = 0; i < 6; ++i) {
        cg.time = 1000;
        Com_sprintf(type, sizeof(type), "%i", types[i]);
        fields[0] = "an"; fields[1] = type; fields[2] = "-5"; argcValue = 3;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(strcmp(CG_NitmodSpecialText(), labels[i])) ++errors;
        for(j = 0; j < 7; ++j) {
            float expected = times[j] < 144 ? (200 - times[j]) / 200.0f : .28f;
            qboolean active = CG_NitmodSpecialFrame(1000 + times[j], &scale, color);
            if(active != (times[j] < 1400)) ++errors;
            if(active && (fabs(scale - expected) > .00001 || color[0] != 1 ||
                color[1] != (i == 1 || i == 2 ? 1 : 0) || color[1] != color[2] ||
                fabs(color[3] - (times[j] < 144 ? 0 : .7f)) > .00001)) ++errors;
        }
        if(CG_NitmodSpecialText()[0]) ++errors;
    }
    cg.time = 1000; CG_NitmodSpecialAnnouncement(4, 0);
    for(i = 0; i < 6; ++i) {
        fields[0] = "an"; fields[1] = "1"; fields[2] = bad[i]; argcValue = 3;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(strcmp(CG_NitmodSpecialText(), "FIRST BLOOD!")) ++errors;
        fields[1] = bad[i]; fields[2] = "1";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(strcmp(CG_NitmodSpecialText(), "FIRST BLOOD!")) ++errors;
    }
    if(CG_NitmodSpecialAnnouncement(0, 5) || CG_NitmodSpecialAnnouncement(-1, 5) ||
       CG_NitmodSpecialAnnouncement(6, 5)) ++errors;
    fields[0] = "hpb"; fields[1] = "25"; argcValue = 2;
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(strcmp(CG_NitmodSpecialText(), "+25 HP") ||
       !CG_NitmodSpecialFrame(1200, &scale, color) || color[0] || color[1] != 1 || color[2]) ++errors;
    cg.time = 1200; popupDraws = 0; CG_NitmodDrawSpecial();
    if(!popupDraws) ++errors;
    for(i = -1; i <= 1; ++i) {
        int withoutXP;
        cg.time = 1000; CG_NitmodSpecialAnnouncement(1, i);
        cg.time = 1200; popupDraws = 0; CG_NitmodDrawSpecial(); withoutXP = popupDraws;
        cg.time = 1000; CG_NitmodSpecialAnnouncement(1, 0);
        cg.time = 1200; popupDraws = 0; CG_NitmodDrawSpecial();
        if(i ? withoutXP <= popupDraws : withoutXP != popupDraws) ++errors;
    }
    CG_NitmodHudReset(); popupDraws = 0; CG_NitmodDrawSpecial(); if(popupDraws) ++errors;
    popupTest = 0; cg.time = savedTime; argcValue = savedArgc;
    memcpy(fields, savedFields, sizeof(fields)); cgs.gameState = savedGame;
    return errors;
}
static int CheckBannerFormatting(void) {
    char input[2048], expected[2048], output[2048];
    int count, color, size, errors = 0;
    NITMOD_FormatBanner("first\\n^1second\nthird", output, sizeof(output));
    if(strcmp(output, "first\n^1second\nthird")) ++errors;
    NITMOD_FormatBanner(NULL, output, sizeof(output)); if(*output) ++errors;
    NITMOD_FormatBanner("", output, sizeof(output)); if(*output) ++errors;
    for(count = 1; count <= 130; ++count) for(color = 0; color < 2; ++color) {
        int i, in = 0, out = 0, visible = 0;
        for(i = 0; i < count; ++i) {
            if(color) { input[in++] = '^'; input[in++] = '1'; expected[out++] = '^'; expected[out++] = '1'; }
            if(visible == 65) { expected[out++] = '\n'; visible = 0; }
            input[in++] = 'a'; expected[out++] = 'a'; ++visible;
        }
        input[in++] = ' '; input[in++] = 'b'; input[in] = 0;
        expected[out++] = visible >= 55 ? '\n' : ' ';
        expected[out++] = 'b'; expected[out] = 0;
        NITMOD_FormatBanner(input, output, sizeof(output));
        if(strcmp(output, expected)) ++errors;
    }
    memset(input, 'x', sizeof(input)); input[sizeof(input) - 1] = 0;
    for(size = 1; size <= 1024; ++size) {
        memset(output, 0x5a, sizeof(output));
        NITMOD_FormatBanner(input, output, size);
        if(!memchr(output, 0, size) || output[size] != 0x5a) ++errors;
    }
    memset(output, 0x5a, sizeof(output));
    NITMOD_FormatBanner("ignored", output, 0); if(output[0] != 0x5a) ++errors;
    NITMOD_FormatBanner("^1hello", output, 2); if(output[0]) ++errors;
    NITMOD_FormatBanner("^1hello", output, 3); if(strcmp(output, "^1")) ++errors;
    return errors;
}
static int CheckSpree(void) {
    static const int sizes[] = {0, 6, 3, 5, 0, 4};
    int type, detail, flags, errors = 0, savedTime = cg.time, savedFlags = cg_HUDFlags.integer;
    int oldArgc = argcValue, oldPrints;
    const char *savedFields[21];
    clientInfo_t savedClient = cgs.clientinfo[1];
    gameState_t savedGame = cgs.gameState;
    centity_t cent;
    snapshot_t snapshot;
    snapshot_t *savedSnap = cg.snap;
    memcpy(savedFields, fields, sizeof(fields));
    memset(&cent, 0, sizeof(cent));
    memset(&snapshot, 0, sizeof(snapshot)); snapshot.ps.clientNum = 3; cg.snap = &snapshot;
    spreeSoundTest = 1; spreeRegistrations = spreeSoundFailure = 0;
    CG_NitmodRegisterSpreeSounds();
    if(spreeRegistrations != 15) ++errors;
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cgs.clientinfo[1].infoValid = qtrue;
    strcpy(cgs.clientinfo[1].name, "Spree tester");
    popupTest = 1;
    for(type = 0; type <= 5; ++type) for(detail = -1; detail <= 7; ++detail) {
        int valid = detail >= 0 && detail < sizes[type];
        if(!!CG_NitmodSpreeLabel(type, detail) != valid) ++errors;
        if(type == 4) continue;
        cg.time = 1000; CG_NitmodHudReset();
        spreePlays = 0;
        if(CG_NitmodSpreeStart(1, detail, type) != valid) ++errors;
        if(spreePlays != (valid && type != 2)) ++errors;
        if(spreePlays && spreeLastSound != (type == 1 ? 110 : type == 3 ? 101 : 106) + detail) ++errors;
        for(flags = 0; flags < 32; ++flags) {
            cg_HUDFlags.integer = flags; popupDraws = 0;
            CG_NitmodDrawSpree();
            if(!!popupDraws != valid) ++errors;
        }
        cg.time = 5250; popupDraws = 0; CG_NitmodDrawSpree();
        if(popupDraws) ++errors;
    }
    cg.time = 1000;
    if(CG_NitmodSpreeStart(-1, 0, 1) || CG_NitmodSpreeStart(MAX_CLIENTS, 0, 1) ||
       CG_NitmodSpreeStart(1, 0x7fffffff, 3)) ++errors;
    cgs.clientinfo[1].infoValid = qfalse;
    if(CG_NitmodSpreeStart(1, 0, 1)) ++errors;
    cgs.clientinfo[1].infoValid = qtrue;
    /* Verify the original event's payload uses the three effect fields. */
    oldPrints = prints;
    if(!CG_NitmodSpreeStart(1, 5, 4) || prints != oldPrints + 1 ||
       CG_NitmodSpreeStart(1, 6, 4) || CG_NitmodSpreeStart(1, -5, 4)) ++errors;
    popupDraws = 0; CG_NitmodDrawSpree(); if(popupDraws) ++errors;
    if(offsetof(entityState_t, effect1Time) != 0x10c ||
       offsetof(entityState_t, effect2Time) != 0x110 ||
       offsetof(entityState_t, effect3Time) != 0x114) ++errors;
    cent.currentState.event = 101; cent.currentState.effect1Time = 1;
    cent.currentState.effect2Time = 5; cent.currentState.effect3Time = 1;
    oldPrints = prints; CG_EntityEvent(&cent, cent.lerpOrigin);
    if(prints != oldPrints + 1) ++errors;
    CG_NitmodHudReset(); popupDraws = 0; CG_NitmodDrawSpree();
    if(popupDraws) ++errors;
    fields[0] = "z2"; fields[1] = "1"; fields[2] = "4"; argcValue = 3;
    oldPrints = prints; CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(prints != oldPrints + 1) ++errors;
    popupDraws = 0; CG_NitmodDrawSpree(); if(!popupDraws) ++errors;
    fields[1] = "-1"; oldPrints = prints;
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(prints != oldPrints) ++errors;
    fields[1] = "1"; fields[2] = "5";
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(prints != oldPrints) ++errors;
    fields[2] = "4"; argcValue = 2;
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(prints != oldPrints) ++errors;
    fields[0] = "nsp"; fields[1] = "1"; fields[2] = "0"; fields[3] = "5"; argcValue = 4;
    oldPrints = prints; NITMOD_SpreeEventCommand();
    if(prints != oldPrints + 1) ++errors;
    CG_NitmodHudReset(); popupTest = 0;
    /* Missing handles and a missing snapshot must never reach StartSound. */
    spreeSoundFailure = -1; spreeRegistrations = 0; spreePlays = 0;
    CG_NitmodRegisterSpreeSounds();
    for(type = 1; type <= 5; ++type) if(type != 4)
        for(detail = 0; detail < sizes[type]; ++detail) CG_NitmodSpreeStart(1, detail, type);
    if(spreeRegistrations != 15 || spreePlays) ++errors;
    spreeSoundFailure = 0; spreeRegistrations = 0; CG_NitmodRegisterSpreeSounds();
    cg.snap = NULL; CG_NitmodSpreeStart(1, 0, 1); if(spreePlays) ++errors;
    /* Clear cached test handles before other fixture scenarios. */
    spreeSoundFailure = -1; spreeRegistrations = 0; CG_NitmodRegisterSpreeSounds();
    CG_NitmodHudReset(); spreeSoundTest = 0; cg.snap = savedSnap;
    cgs.clientinfo[1] = savedClient; cgs.gameState = savedGame;
    memcpy(fields, savedFields, sizeof(fields)); argcValue = oldArgc;
    cg.time = savedTime; cg_HUDFlags.integer = savedFlags;
    return errors;
}
static int keyTest, keyLength, keyReads, keyCloses, keySets;
static int deathTest, deathNear, deathFar, deathNearHandle, deathFarHandle;
static int wireTest, wireCommand, fireTest, fireSounds, fireBrass, fireHandle;
static void TestBrass(centity_t *cent) {
    if(cent->currentState.weapon != WP_MP40) exit(2);
    ++fireBrass;
}
static const char keyData[] = "QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBS0s=";
static char keyValue[33];
static int CheckOriginalWireBatch(void) {
    static const int expected[] = {0,
#define X(id, name, handler) handler,
#include "cg_nitmod_eventmap.h"
#undef X
    };
    static const char *portal[] = {"z5", "3", "-100", "200", "300", "-90", "180", "0", "1023"};
    static const char *bad[] = {"", "x", "2147483648", "-2147483649", "1.5"};
    centity_t cent;
    snapshot_t snapshot;
    snapshot_t *savedSnap = cg.snap;
    char guid[33], encoded[45];
    int errors = 0, i, j, bits;
    memset(&snapshot, 0, sizeof(snapshot));
    cg.snap = &snapshot;
    memset(&cent, 0, sizeof(cent));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    for(i = 0; i <= 93; ++i) if(CG_NitmodEventDispatch(i) != expected[i]) ++errors;
    cg.predictedPlayerState.clientNum = 0;
    cg.demoPlayback = qfalse; cg_nopredict.integer = 0;
    cg.time = 1000;
    cent.currentState.dl_intensity = -1; /* Explicit no sound, zero debris mass. */
    for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1) {
        for(i = 0; i <= 40; ++i) {
            cent.currentState.event = 11 | bits;
            cent.currentState.eventParm = i;
            cg.stepTime = 0; cg.stepChange = 0;
            CG_EntityEvent(&cent, cent.lerpOrigin);
            if(cg.stepChange != (i > MAX_STEP_CHANGE ? MAX_STEP_CHANGE : i) ||
               cg.stepTime != cg.time || cent.currentState.event != (11 | bits)) ++errors;
        }
        for(i = 63; i <= 64; ++i) {
            cent.currentState.event = i | bits;
            CG_EntityEvent(&cent, cent.lerpOrigin);
            if(cent.currentState.event != (i | bits)) ++errors;
        }
        cent.currentState.event = 59 | bits; cent.currentState.loopSound = 77;
        CG_EntityEvent(&cent, cent.lerpOrigin);
        if(cent.currentState.loopSound) ++errors;
    }
    for(i = 0; i < 9; ++i) fields[i] = portal[i];
    argcValue = 9;
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(cgs.ccCurrentCamObjective != 3 || cgs.ccPortalEnt != 1023 ||
       cgs.ccPortalPos[0] != -100 || cgs.ccPortalPos[2] != 300 || cgs.ccPortalAngles[0] != -90) ++errors;
    for(i = 1; i < 9; ++i) for(j = 0; j < 5; ++j) {
        fields[i] = bad[j];
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.ccCurrentCamObjective != 3 || cgs.ccPortalEnt != 1023 || cgs.ccPortalPos[0] != -100) ++errors;
        fields[i] = portal[i];
    }
    fields[8] = "1024";
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(cgs.ccPortalEnt != 1023) ++errors;
    fields[8] = "-1";
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(cgs.ccPortalEnt != -1) ++errors;
    if(!NITMOD_DecodeNKey(keyData, 44, guid) || strcmp(guid, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKK")) ++errors;
    for(i = 0; i < 44; ++i) {
        strcpy(encoded, keyData); encoded[i] = '!'; strcpy(guid, "unchanged");
        if(NITMOD_DecodeNKey(encoded, 44, guid) || strcmp(guid, "unchanged")) ++errors;
    }
    if(NITMOD_DecodeNKey(keyData, 43, guid) || NITMOD_DecodeNKey(keyData, 45, guid)) ++errors;
    keyTest = 1;
    fields[0] = "getnguid"; fields[1] = "2";
    for(argcValue = 1; argcValue <= 2; ++argcValue) {
        keyLength = 44; keyReads = keyCloses = keySets = 0;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(keyReads != 1 || keyCloses != 1 || keySets != 2 || strcmp(keyValue, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKK")) ++errors;
        keyLength = -1; keyReads = keyCloses = keySets = 0;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(keyReads || keyCloses || keySets != 1 || keyValue[0]) ++errors;
    }
    keyTest = 0;
    fields[0] = "ob"; fields[1] = "4"; fields[2] = "2";
    fields[3] = "0"; fields[4] = "5"; fields[5] = "0"; argcValue = 6;
    Q_strncpyz(cgs.clientinfo[5].name, "Builder", sizeof(cgs.clientinfo[5].name));
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(NITMOD_LastObjectiveEvent()->type != 4 || NITMOD_LastObjectiveEvent()->detail != 2 ||
       NITMOD_LastObjectiveEvent()->actor != 5 || NITMOD_ServerSupports(NITMOD_FEATURE_OBJECTIVES)) ++errors;
    cg.snap = savedSnap;
    return errors;
}
static int CheckOriginalDeathEvents(void) {
    const float distances[] = {0, 512, 513, 4095, 4096};
    centity_t cent;
    refdef_t view;
    refdef_t *saved = cg.refdef_current;
    weaponInfo_t savedWeapon = cg_weapons[WP_MP40];
    int nearCount, farCount, variant, bits, i, j, errors = 0;
    memset(&cent, 0, sizeof(cent)); memset(&view, 0, sizeof(view));
    cg.refdef_current = &view;
    cent.currentState.weapon = WP_MP40;
    cent.currentState.number = 5; cent.currentState.otherEntityNum2 = 6;
    cg.time = 2000;
    deathTest = 1;
    for(nearCount = 0; nearCount <= 4; ++nearCount) for(farCount = 0; farCount <= 4; ++farCount) {
        weaponInfo_t *weapon = &cg_weapons[WP_MP40];
        weapon->deathBySoundCount = nearCount; weapon->deathBySoundFarCount = farCount;
        for(j = 0; j < 4; ++j) {
            weapon->deathBySound[j] = j < nearCount ? 100 + j : 0;
            weapon->deathBySoundFar[j] = j < farCount ? 200 + j : 0;
        }
        for(variant = 0; variant < 4; ++variant) for(i = 0; i < 5; ++i)
            for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1) {
                cent.currentState.event = (52 + variant) | bits;
                cent.currentState.pos.trBase[0] = distances[i];
                deathNear = deathFar = 0;
                cg_entities[6].pe.painTime = 0;
                CG_EntityEvent(&cent, cent.lerpOrigin);
                if(deathNear != !!nearCount || deathFar != (nearCount && farCount && i >= 2 && i <= 3) ||
                   (deathNear && deathNearHandle != 100 + variant % nearCount) ||
                   (deathFar && deathFarHandle != 200 + variant % farCount) ||
                   cg_entities[6].pe.painTime != cg.time || cent.currentState.event != ((52 + variant) | bits)) ++errors;
            }
    }
    deathTest = 0; cg.refdef_current = saved; cg_weapons[WP_MP40] = savedWeapon;
    return errors;
}
static int CheckWeaponWireAndPrediction(void) {
    static snapshot_t snap;
    snapshot_t *saved = cg.snap;
    weaponInfo_t savedWeapon = cg_weapons[WP_MP40];
    playerState_t ring;
    usercmd_t cmd;
    int i, native, errors = 0;
    const int wireIds[] = {17, 18, 19, 20, 21, 22, 23, 24, 28, 29, 31, 33, 34, 35, 39, 43, 46, 49};
    const int typedIds[] = {VERYBIGEXPLOSION, WP_MEDKIT, WP_BINOCULARS, WP_PLIERS, WP_SMOKE_MARKER,
        WP_KAR98, WP_CARBINE, WP_GARAND, WP_SMOKE_BOMB, WP_MOBILE_MG42, WP_FG42, WP_MORTAR,
        WP_AKIMBO_COLT, WP_AKIMBO_LUGER, WP_GARAND_SCOPE, WP_MEDIC_ADRENALINE, WP_MOBILE_MG42_SET, WP_TRIPMINE};
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cgs.gameState.stringOffsets[CS_PLAYERS + 5] = 100;
    strcpy(cgs.gameState.stringData + 100, "\\n\\OriginalPlayer");
    if(strcmp(NITMOD_PlayerConfigString(5), "\\n\\OriginalPlayer")) ++errors;
    if(CS_PLAYERS != 689) ++errors;
    for(i = 0; i < sizeof(wireIds)/sizeof(wireIds[0]); ++i)
        if(NITMOD_WeaponFromWire(wireIds[i]) != typedIds[i] || NITMOD_WeaponToWire(typedIds[i]) != wireIds[i]) ++errors;
    wireTest = 1;
    for(i = -1; i <= 10; ++i) {
        static const int mapped[] = { WEAPON_FIRING, WEAPON_FIRINGALT, WEAPON_RELOADING };
        memset(&snap, 0, sizeof(snap)); snap.ps.weaponstate = i;
        NITMOD_TranslateSnapshotWeapons(&snap);
        if(snap.ps.weaponstate != (i >= 5 && i <= 7 ? mapped[i - 5] : i)) ++errors;
    }
    for(i = 0; i < 52; ++i) {
        memset(&snap, 0, sizeof(snap));
        native = NITMOD_WeaponFromWire(i);
        if(!native && i) continue; /* Explicitly unimplemented new weapons. */
        snap.ps.weapon = snap.ps.nextWeapon = i;
        snap.ps.weapons[i / 32] = (int)(1u << (i % 32));
        snap.ps.ammo[i] = 123; snap.ps.ammoclip[i] = 17; snap.ps.weapHeat[i] = 99;
        snap.numEntities = 2;
        snap.entities[0].eType = ET_PLAYER; snap.entities[0].weapon = i;
        snap.entities[1].eType = 59 + 63; snap.entities[1].weapon = 22; /* gravity, not KAR98 */
        NITMOD_TranslateSnapshotWeapons(&snap);
        if(snap.ps.weapon != native || snap.ps.nextWeapon != native ||
           !((unsigned int)snap.ps.weapons[native / 32] & (1u << (native % 32))) ||
           snap.ps.ammo[native] != 123 || snap.ps.ammoclip[native] != 17 || snap.ps.weapHeat[native] != 99 ||
           snap.entities[0].weapon != native || snap.entities[1].weapon != 22) ++errors;
        trap_SetUserCmdValue(native, 0, 1, 0);
        if(wireCommand != i) ++errors;
        if(!trap_GetUserCmd(1, &cmd) || cmd.weapon != native) ++errors;
    }
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod\\nitmod_csLayout\\et260");
    trap_SetUserCmdValue(WP_MEDIC_ADRENALINE, 0, 1, 0);
    if(wireCommand != WP_MEDIC_ADRENALINE || !trap_GetUserCmd(1, &cmd) || cmd.weapon != WP_MEDIC_ADRENALINE) ++errors;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    wireTest = 0;
    memset(&snap, 0, sizeof(snap)); cg.snap = &snap;
    snap.ps.clientNum = 5;
    memset(&cg.predictedPlayerEntity, 0, sizeof(cg.predictedPlayerEntity));
    cg.predictedPlayerEntity.currentState.clientNum = 5;
    cg.predictedPlayerEntity.currentState.number = 5;
    cg.predictedPlayerEntity.currentState.weapon = WP_MP40;
    memset(&cg_weapons[WP_MP40], 0, sizeof(cg_weapons[WP_MP40]));
    cg_weapons[WP_MP40].flashSound[0] = 601;
    cg_weapons[WP_MP40].lastShotSound[0] = 602;
    cg_weapons[WP_MP40].reloadSound = 603;
    cg_weapons[WP_MP40].ejectBrassFunc = TestBrass;
    cg_brassTime.integer = 2500;
    cg.eventSequence = 1;
    fireTest = 1;
    for(i = 33; i <= 35; ++i) {
        memset(&ring, 0, sizeof(ring)); ring.events[0] = i; ring.eventSequence = 1;
        ring.externalEvent = 40;
        NITMOD_NormalizePredictedEvents(&ring);
        if(ring.events[0] != CG_NitmodEventDispatch(i) || ring.externalEvent != 40) ++errors;
        cg.predictedPlayerEntity.currentState.event = ring.events[0];
        fireSounds = fireBrass = 0;
        CG_NativeEntityEvent(&cg.predictedPlayerEntity, cg.predictedPlayerEntity.lerpOrigin);
        cg.predictableEvents[0] = ring.events[0]; cg.predictableEvents[15] = 0;
        ring.events[0] = i;
        CG_CheckChangedPredictableEvents(&ring);
        CG_CheckChangedPredictableEvents(&ring);
        if(fireSounds != 1 || fireBrass != 1 || fireHandle != (i == 35 ? 602 : 601)) ++errors;
        cg.predictedPlayerEntity.currentState.event = i;
        CG_EntityEvent(&cg.predictedPlayerEntity, cg.predictedPlayerEntity.lerpOrigin);
        if(fireSounds != 2 || fireBrass != 2 || fireHandle != (i == 35 ? 602 : 601)) ++errors;
    }
    fireTest = 0;
    cgs.media.smallgunBrassModel = 700; cgs.media.machinegunBrassModel = 701; cgs.media.panzerfaustBrassModel = 702;
    if(CG_NitmodBrassModel(WP_MP40) != 700) ++errors;
    cg_weapons[WP_MP40].brassModel = 703;
    if(CG_NitmodBrassModel(WP_MP40) != 703) ++errors;
    cg.snap = saved; cg_weapons[WP_MP40] = savedWeapon;
    return errors;
}
static int bannerValue;
static int bannerRender, bannerGlyphs, bannerRenderErrors;
static vec4_t bannerDrawColor;
static float bannerExpectedAlpha, bannerExpectedStep;
static int CheckBannerLayout(void) {
    fontInfo_t savedFont = cgs.media.limboFont1;
    gameState_t savedGame = cgs.gameState;
    float sx = cgs.screenXScale, sy = cgs.screenYScale;
    int oldTime = cg.time, oldArgc = argcValue, oldValue = bannerValue;
    int oldDraw = cg_drawBanners.integer, i, height, errors = 0;
    const char *savedFields[21];
    memcpy(savedFields, fields, sizeof(fields));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    memset(&cgs.media.limboFont1, 0, sizeof(cgs.media.limboFont1));
    cgs.media.limboFont1.glyphScale = 1;
    for(i = 0; i < 256; ++i) {
        cgs.media.limboFont1.glyphs[i].glyph = 812;
        cgs.media.limboFont1.glyphs[i].xSkip = 10;
    }
    cgs.screenXScale = cgs.screenYScale = 1;
    bannerRender = bannerValue = 1; bannerRenderErrors = 0;
    fields[0] = "bp"; fields[1] = "2"; fields[2] = "^1A\\nB"; argcValue = 3;
    for(height = 50; height <= 75; height += 25) {
        cgs.media.limboFont1.glyphs['A'].height = height;
        bannerExpectedStep = (int)((int)(height * .2f) * 1.5f);
        cg.time = 1000; CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        bannerExpectedAlpha = 1; bannerGlyphs = 0; NITMOD_DrawBanner();
        if(bannerGlyphs != 2) ++errors;
        cg.time = 10900; bannerExpectedAlpha = .5f; bannerGlyphs = 0; NITMOD_DrawBanner();
        if(bannerGlyphs != 2) ++errors;
        cg.time = 11000; bannerGlyphs = 0; NITMOD_DrawBanner(); if(bannerGlyphs) ++errors;
    }
    bannerRender = 0; errors += bannerRenderErrors;
    cgs.media.limboFont1 = savedFont; cgs.gameState = savedGame;
    cgs.screenXScale = sx; cgs.screenYScale = sy;
    cg.time = oldTime; argcValue = oldArgc; bannerValue = oldValue; cg_drawBanners.integer = oldDraw;
    memcpy(fields, savedFields, sizeof(fields));
    return errors;
}
static int ncsTest, ncsAssets;
static int hitTest, hitValue, hitPlays, hitSound;
static int obituaryAudioTest, obituaryAudioCount, obituaryAudioHandles[3], obituaryAudioEntities[3];
static int CheckObituaryAudio(void) {
    static cg_t savedCg;
    static gameState_t savedGame;
    static snapshot_t snap;
    entityState_t es;
    int protocol, cause, flags, team, listener, game, i, expected, errors = 0;
    int savedGoat = cg_goatSound.integer, savedTK = cg_tkSounds.integer, savedType = cgs.gametype;
    int savedTeam1 = cgs.clientinfo[1].team, savedTeam2 = cgs.clientinfo[2].team;
    const int causes[] = {5,21,23,57,58,61,63,64,68,69,-1};
    savedCg = cg; savedGame = cgs.gameState;
    memset(&snap, 0, sizeof(snap)); memset(&es, 0, sizeof(es));
    cg.snap = &snap; es.otherEntityNum = 1; es.otherEntityNum2 = 2;
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    CG_NitmodObituaryReset(); obituaryAudioTest = 1;
    for(protocol = 0; protocol < 2; ++protocol) for(cause = 0; cause < 11; ++cause)
    for(flags = 0; flags < 4; ++flags) for(team = 0; team < 2; ++team)
    for(listener = 1; listener <= 3; ++listener) for(game = 0; game < 2; ++game) {
        int goat, gib, tk;
        strcpy(cgs.gameState.stringData + 1, protocol ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        cg_goatSound.integer = flags; cg_tkSounds.integer = flags & 1;
        cgs.gametype = game ? 8 : 2;
        cgs.clientinfo[1].team = TEAM_AXIS; cgs.clientinfo[2].team = team ? TEAM_AXIS : TEAM_ALLIES;
        snap.ps.clientNum = listener; es.eventParm = causes[cause];
        goat = protocol && listener != 3 && ((es.eventParm == 5 && (flags & 1)) || (es.eventParm == 63 && (flags & 2)));
        gib = protocol && listener != 3 && es.eventParm == 58;
        tk = protocol && (flags & 1) && team && !game &&
            (es.eventParm == 5 || es.eventParm == 21 || es.eventParm == 58 || es.eventParm == 63 || es.eventParm == 68);
        obituaryAudioCount = 0; CG_NitmodObituarySounds(&es);
        expected = goat * 2 + gib + tk;
        if(obituaryAudioCount != expected) ++errors;
        i = 0;
        if(gib && (obituaryAudioHandles[i++] != 902 || obituaryAudioEntities[0] != listener)) ++errors;
        if(goat) {
            if(obituaryAudioHandles[i] != 901 || obituaryAudioEntities[i++] != 1) ++errors;
            if(obituaryAudioHandles[i] != 901 || obituaryAudioEntities[i++] != 2) ++errors;
        }
        if(tk && (obituaryAudioHandles[i] != 903 || obituaryAudioEntities[i] != listener)) ++errors;
    }
    if(CG_NitmodDeathCause(5) != MOD_KNIFE || CG_NitmodDeathCause(57) != MOD_SWITCHTEAM ||
       CG_NitmodDeathCause(66) != MOD_TRIPMINE || CG_NitmodDeathCause(-1) != MOD_UNKNOWN ||
       CG_NitmodDeathCause(69) != MOD_UNKNOWN) ++errors;
    obituaryAudioTest = 0; CG_NitmodObituaryReset(); cg = savedCg; cgs.gameState = savedGame;
    cg_goatSound.integer = savedGoat; cg_tkSounds.integer = savedTK; cgs.gametype = savedType;
    cgs.clientinfo[1].team = savedTeam1; cgs.clientinfo[2].team = savedTeam2;
    return errors;
}
static int userinfoTest, userinfoWrites;
static unsigned int preferenceFlags;
static int CheckClientPreferences(void) {
    static gameState_t savedGame;
    static clientInfo_t savedClients[MAX_CLIENTS];
    fireteamData_t fireteam;
    const int values[] = {-1,0,1,2};
    int mode, fixed, single, base, enabled, count, i, errors = 0;
    int savedClient = cg.clientNum, savedAuto = cg_FTAutoSelect.integer;
    int savedFixed = pmove_fixed.integer, savedSingle = n_forceSinglePistol.integer;
    qboolean savedDemo = cg.demoPlayback;
    savedGame = cgs.gameState;
    memcpy(savedClients, cgs.clientinfo, sizeof(savedClients));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    for(mode = 0; mode < 3; ++mode) {
        strcpy(cgs.gameState.stringData + 1, mode == 1 ? "\\gamename\\nitmod" :
            mode == 2 ? "\\gamename\\nitmod\\nitmod_csLayout\\et260" : "\\gamename\\etmain");
        userinfoTest = 1; cg.demoPlayback = qfalse;
        for(fixed = 0; fixed < 4; ++fixed) for(single = 0; single < 4; ++single) {
            pmove_fixed.integer = values[fixed]; n_forceSinglePistol.integer = values[single];
            userinfoWrites = 0; CG_setClientFlags();
            if(userinfoWrites != 1 || (preferenceFlags & 0x60u) !=
               (mode == 1 ? (values[fixed] > 0 ? 32u : 0u) | (values[single] > 0 ? 64u : 0u) : 0u)) ++errors;
        }
        cg.demoPlayback = qtrue; userinfoWrites = 0; CG_setClientFlags();
        if(userinfoWrites) ++errors;
        userinfoTest = 0;
        for(base = 0; base < 256; ++base) for(fixed = 0; fixed < 4; ++fixed) for(single = 0; single < 4; ++single) {
            unsigned int flags = 0x80000000u | base;
            unsigned int expected = mode == 1 ? (flags & ~0x60u) |
                (values[fixed] > 0 ? 32u : 0u) | (values[single] > 0 ? 64u : 0u) : flags;
            if(NITMOD_ClientPreferenceFlags(flags, values[fixed], values[single]) != expected) ++errors;
        }
        for(enabled = 0; enabled < 2; ++enabled) for(count = 0; count <= 8; ++count) {
            memset(cgs.clientinfo, 0, sizeof(cgs.clientinfo));
            memset(&fireteam, 0, sizeof(fireteam)); fireteam.inuse = qtrue; fireteam.leader = 0;
            cg.clientNum = 0; cg_FTAutoSelect.integer = enabled;
            for(i = 0; i < count; ++i) {
                cgs.clientinfo[i].fireteamData = &fireteam;
                cgs.clientinfo[i].infoValid = qtrue;
                cgs.clientinfo[i].rank = i;
            }
            cgs.clientinfo[63].selected = qtrue; /* untouched manual state outside fireteam */
            CG_SortClientFireteam();
            if(CG_NitmodAutoSelectFireteam() != (mode == 1 && enabled ? (count < 6 ? count : 6) : 0)) ++errors;
            for(i = 0; i < 63; ++i) {
                int expected = mode == 1 && enabled && i < count &&
                    (count <= 6 || i == 0 || i >= count - 5);
                if(cgs.clientinfo[i].selected != expected) ++errors;
            }
            if(!cgs.clientinfo[63].selected) ++errors;
        }
    }
    cg.clientNum = savedClient; cg_FTAutoSelect.integer = savedAuto;
    pmove_fixed.integer = savedFixed; n_forceSinglePistol.integer = savedSingle; cg.demoPlayback = savedDemo;
    memcpy(cgs.clientinfo, savedClients, sizeof(savedClients)); cgs.gameState = savedGame;
    CG_SortClientFireteam();
    return errors;
}
static int snapshotHitTest, snapshotHitPlays, snapshotHitSamples[2], snapshotHitLoads;
static int CheckSnapshotHitSounds(void) {
    static cg_t savedCg;
    static gameState_t savedGame;
    const int deltas[] = {-10,-1,0,1,5};
    int mode, enabled, same, team, b, h, i, expected, errors = 0;
    int savedHit = nitmodHitSounds.integer;
    float savedLimit = cgs.timelimit;
    savedCg = cg; savedGame = cgs.gameState;
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    snapshotHitTest = 1; snapshotHitLoads = 0;
    for(mode = 0; mode < 2; ++mode) for(enabled = 0; enabled < 2; ++enabled)
    for(same = 0; same < 2; ++same) for(team = TEAM_AXIS; team <= TEAM_SPECTATOR; ++team)
    for(b = 0; b < 5; ++b) for(h = 0; h < 5; ++h) {
        strcpy(cgs.gameState.stringData + 1, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        nitmodHitSounds.integer = enabled;
        for(i = 0; i < 2; ++i) {
            snapshot_t *snap = &cg.activeSnapshots[i];
            memset(snap, 0, sizeof(*snap)); snap->serverTime = 1000 + i;
            snap->ps.clientNum = (i == 0 && !same) ? 4 : 5;
            snap->ps.persistant[1] = 10 + (i ? deltas[h] : 0);
            snap->ps.persistant[2] = 10 + (i ? deltas[b] : 0);
            snap->ps.persistant[mode ? 7 : PERS_TEAM] = team;
            NITMOD_TranslateSnapshotPersistant(snap);
        }
        snapshotHitPlays = 0;
        NITMOD_SnapshotHitSounds(&cg.activeSnapshots[0].ps, &cg.activeSnapshots[1].ps);
        expected = mode && enabled && same && team != TEAM_SPECTATOR ? (deltas[b] > 0) + (deltas[h] > 0) : 0;
        if(snapshotHitPlays != expected) ++errors;
        if(expected) {
            if(snapshotHitSamples[0] != (deltas[b] > 0 ? 801 : 802)) ++errors;
            if(expected == 2 && snapshotHitSamples[1] != 802) ++errors;
        }
    }
    if(snapshotHitLoads != 2) ++errors; /* cache registrations, not per shot */
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cgs.timelimit = 0; cg.painTime = 17; cg.time = 1000;
    cg.activeSnapshots[0].ps.stats[STAT_HEALTH] = 100;
    cg.activeSnapshots[1].ps.stats[STAT_HEALTH] = 50;
    CG_CheckLocalSounds(&cg.activeSnapshots[1].ps, &cg.activeSnapshots[0].ps);
    if(cg.painTime != 17) ++errors; /* no extra native pain on the original protocol */
    snapshotHitTest = 0; NITMOD_ResetSnapshotPersistant();
    cg = savedCg; cgs.gameState = savedGame; nitmodHitSounds.integer = savedHit; cgs.timelimit = savedLimit;
    return errors;
}
static int shoveTest, shoveValue, shovePlays, shoveEntity;
static int greetingTest, greetingValue, greetingLoads, greetingPlays, greetingHandle;
static int forceTest, forceSets, forceRegisters;
static char forceCurrent[256], forceLastName[256], forceLastValue[256];
static vmCvar_t *hitCvar;
static char *weaponCursor;
static const char *expectedWeaponPath;
static int teamMediaTest, teamMediaRegistrations;
static int sourceLoads, sourceFrees, mediaSounds, sentCapabilities;
static int medicSounds, medicEntity, medicHandle;
static int landingTest, landingPlays, hurtPlays;
static int waterTest, waterSounds[4];
static int extendedTest, extendedPlays, extendedEntity, extendedChannel, extendedHandle, extendedVolume;
static qboolean extendedPosition;
static int nameTest, nameBlocked, nameTraces, nameDraws, nameShader;
static int CheckSnapshotPersistant(void) {
    static cg_t savedCg;
    static gameState_t savedGame;
    static snapshot_t expected;
    const int map[MAX_PERSISTANT] = {0,1,-1,7,8,-1,4,9,10,11,-1,-1,12,-1,-1,-1};
    int mode, buffer, slot, i, errors = 0;
    char text[64];
    savedCg = cg; savedGame = cgs.gameState;
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    NITMOD_ResetSnapshotPersistant();
    for(mode = 0; mode < 2; ++mode) for(buffer = 0; buffer < 2; ++buffer)
    for(slot = 0; slot < MAX_PERSISTANT; ++slot) {
        snapshot_t *snap = &cg.activeSnapshots[buffer];
        strcpy(cgs.gameState.stringData + 1, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        memset(snap, 0, sizeof(*snap)); snap->serverTime = 1000 + slot;
        snap->ps.clientNum = 2; snap->ps.weapon = WP_MP40;
        snap->ps.origin[0] = 123; snap->numEntities = 1;
        snap->entities[0].weapon = WP_COLT;
        snap->ps.persistant[slot] = 101 + slot;
        expected = *snap;
        if(mode) for(i = 0; i < MAX_PERSISTANT; ++i)
            expected.ps.persistant[i] = i == PERS_ATTACKER ? -1 : map[i] == slot ? 101 + slot : 0;
        NITMOD_TranslateSnapshotPersistant(snap);
        if(memcmp(snap, &expected, sizeof(expected))) ++errors;
        if(mode) for(i = 0; i < MAX_PERSISTANT; ++i)
            if(NITMOD_WirePersistant(&snap->ps)[i] != (i == slot ? 101 + slot : 0)) ++errors;
    }
    /* Both buffers coexist: the future frame must not overwrite current HUD counters. */
    for(buffer = 0; buffer < 2; ++buffer) {
        snapshot_t *snap = &cg.activeSnapshots[buffer];
        memset(snap, 0, sizeof(*snap)); snap->serverTime = 2000 + buffer;
        snap->ps.clientNum = 1;
        snap->ps.persistant[3] = 17 + buffer; snap->ps.persistant[7] = TEAM_ALLIES;
        snap->ps.persistant[6] = 30 + buffer; snap->ps.persistant[15] = 4 + buffer;
        NITMOD_TranslateSnapshotPersistant(snap);
    }
    for(buffer = 0; buffer < 2; ++buffer) {
        CG_NitmodLiveStatsText(&cg.activeSnapshots[buffer].ps, 3, 10000, text, sizeof(text));
        if(strcmp(text, buffer ? "^7K: ^f18" : "^7K: ^f17")) ++errors;
        if(cg.activeSnapshots[buffer].ps.persistant[PERS_TEAM] != TEAM_ALLIES) ++errors;
    }
    cg.time = 5000;
    CG_NitmodLiveStatsTransition(&cg.activeSnapshots[0].ps, &cg.activeSnapshots[1].ps);
    CG_NitmodLiveStatsText(&cg.activeSnapshots[1].ps, 1, 5000, text, sizeof(text));
    if(strcmp(text, "^7BS: ^231")) ++errors;
    /* Reusing a buffer for a native server invalidates its wire copy. */
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\etmain");
    cg.activeSnapshots[0].ps.persistant[3] = TEAM_AXIS;
    expected = cg.activeSnapshots[0];
    NITMOD_TranslateSnapshotPersistant(&cg.activeSnapshots[0]);
    if(memcmp(&expected, &cg.activeSnapshots[0], sizeof(expected)) ||
       NITMOD_WirePersistant(&cg.activeSnapshots[0].ps) != cg.activeSnapshots[0].ps.persistant) ++errors;
    NITMOD_ResetSnapshotPersistant();
    if(NITMOD_WirePersistant(NULL)) ++errors;
    NITMOD_TranslateSnapshotPersistant(NULL);
    CG_NitmodHudReset(); cg = savedCg; cgs.gameState = savedGame;
    return errors;
}
static int CheckLiveStats(void) {
    static gameState_t savedGame;
    static cg_t savedCg;
    static snapshot_t snapshot;
    static fontInfo_t savedFont;
    playerState_t oldState;
    const int slots[] = {15,6,5,3,4};
    const char *labels[] = {"Spree","BS","HS","K","D"};
    const int ages[] = {-1,0,1,99,100,101,1000};
    int row, i, mode, side, tv, enabled, errors = 0;
    int savedDraw = cg_draw2D.integer, savedStats = cg_drawHUDStats.integer, savedFlags = cg_HUDFlags.integer;
    qboolean savedTV = cgs.clientinfo[1].nitmodTV;
    char text[64], expected[64];
    savedGame = cgs.gameState; savedCg = cg; savedFont = cgs.media.limboFont1;
    /* The snapshot offsets in Nit_LiveStats must map to these typed slots. */
    if(offsetof(snapshot_t, ps) + offsetof(playerState_t, persistant) + 3*sizeof(int) != 0x148 ||
       offsetof(playerState_t, persistant) + 15*sizeof(int) != 0x14c) ++errors;
    memset(&snapshot, 0, sizeof(snapshot)); memset(&oldState, 0, sizeof(oldState));
    cg.snap = &snapshot; cg.clientNum = snapshot.ps.clientNum = oldState.clientNum = 1;
    for(i = 0; i < MAX_PERSISTANT; ++i) snapshot.ps.persistant[i] = 100 + i;
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    CG_NitmodHudReset(); cg.time = 1000;
    CG_NitmodLiveStatsTransition(&oldState, &snapshot.ps);
    for(row = 0; row < 5; ++row) for(i = 0; i < 7; ++i) {
        char color = (row == 1 || row == 2) && ages[i] >= 0 && ages[i] < 100 ? '2' : 'f';
        Com_sprintf(expected, sizeof(expected), "^7%s: ^%c%d", labels[row], color, 100 + slots[row]);
        if(!CG_NitmodLiveStatsText(&snapshot.ps, row, 1000 + ages[i], text, sizeof(text)) || strcmp(text, expected)) ++errors;
    }
    oldState = snapshot.ps; cg.time = 5000;
    CG_NitmodLiveStatsTransition(&oldState, &snapshot.ps);
    CG_NitmodLiveStatsText(&snapshot.ps, 1, 5000, text, sizeof(text));
    if(strcmp(text, "^7BS: ^f106")) ++errors; /* unchanged counters don't flash */
    snapshot.ps.persistant[6] = 0;
    CG_NitmodLiveStatsTransition(&oldState, &snapshot.ps);
    CG_NitmodLiveStatsText(&snapshot.ps, 1, 5000, text, sizeof(text));
    if(strcmp(text, "^7BS: ^f0")) ++errors;
    CG_NitmodHudReset();
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\etmain");
    snapshot.ps.persistant[6] = 200;
    CG_NitmodLiveStatsTransition(&oldState, &snapshot.ps);
    CG_NitmodLiveStatsText(&snapshot.ps, 1, 5000, text, sizeof(text));
    if(strcmp(text, "^7BS: ^f200")) ++errors; /* native snapshots cannot arm flashes */
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    CG_NitmodLiveStatsTransition(&oldState, &snapshot.ps);
    CG_NitmodLiveStatsText(&snapshot.ps, 1, 5000, text, sizeof(text));
    if(strcmp(text, "^7BS: ^2200")) ++errors;
    oldState.clientNum = 2;
    CG_NitmodLiveStatsTransition(&oldState, &snapshot.ps);
    CG_NitmodLiveStatsText(&snapshot.ps, 1, 5000, text, sizeof(text));
    if(strcmp(text, "^7BS: ^f200")) ++errors; /* following another player clears flashes */
    if(CG_NitmodLiveStatsText(NULL, 0, 0, text, sizeof(text)) ||
       CG_NitmodLiveStatsText(&snapshot.ps, 5, 0, text, sizeof(text)) || text[0]) ++errors;
    memset(&cgs.media.limboFont1, 0, sizeof(cgs.media.limboFont1));
    cgs.media.limboFont1.glyphScale = 1;
    for(i = 0; i < 256; ++i) {
        cgs.media.limboFont1.glyphs[i].xSkip = 10;
        cgs.media.limboFont1.glyphs[i].height = 10;
        cgs.media.limboFont1.glyphs[i].imageWidth = cgs.media.limboFont1.glyphs[i].imageHeight = 10;
        cgs.media.limboFont1.glyphs[i].glyph = 777;
    }
    nameTest = 1; cg_draw2D.integer = 1;
    for(mode = 0; mode < 2; ++mode) for(side = 0; side < 2; ++side)
    for(tv = 0; tv < 2; ++tv) for(enabled = 0; enabled < 2; ++enabled) {
        strcpy(cgs.gameState.stringData + 1, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        cg_HUDFlags.integer = side; cgs.clientinfo[1].nitmodTV = tv;
        cg_drawHUDStats.integer = enabled; nameDraws = 0;
        CG_NitmodDrawLiveStats();
        if((nameDraws > 0) != (mode && !tv && enabled)) ++errors;
    }
    nameTest = 0; CG_NitmodHudReset(); cg = savedCg; cgs.gameState = savedGame;
    cgs.media.limboFont1 = savedFont; cgs.clientinfo[1].nitmodTV = savedTV;
    cg_draw2D.integer = savedDraw; cg_drawHUDStats.integer = savedStats; cg_HUDFlags.integer = savedFlags;
    return errors;
}
static int CheckWoundedNames(void) {
    static cg_t savedCg;
    static gameState_t savedGame;
    static snapshot_t snapshot;
    static fontInfo_t savedFont;
    clientInfo_t savedClient = cgs.clientinfo[2];
    centity_t cent;
    const int ranges[] = {0,63,64,100,1600,1601,-100};
    int mode, alive, cls, targetAlive, team, dead, r, i, errors = 0;
    int oldDraw = cg_draw2D.integer, oldNames = cg_woundedNames.integer, oldGame = cgs.gametype;
    savedCg = cg; savedGame = cgs.gameState; savedFont = cgs.media.limboFont1;
    memset(&snapshot, 0, sizeof(snapshot)); cg.snap = &snapshot; cg.nextSnap = NULL;
    CG_BuildSolidList();
    snapshot.ps.clientNum = 1; snapshot.ps.persistant[PERS_TEAM] = TEAM_AXIS;
    cg.demoPlayback = qfalse; cg.refdef_current = &cg.refdef;
    VectorClear(cg.refdef.vieworg); VectorClear(cg.refdefViewAngles); VectorClear(cg.predictedPlayerState.origin);
    cg.refdef.fov_x = 96; cg.refdef.fov_y = 102;
    cg_draw2D.integer = cg_woundedNames.integer = 1; cgs.gametype = 3;
    memset(&cgs.media.limboFont1, 0, sizeof(cgs.media.limboFont1));
    cgs.media.limboFont1.glyphScale = 1;
    cgs.media.limboFont1.glyphs['A'].xSkip = 10;
    cgs.media.limboFont1.glyphs['A'].height = 10;
    cgs.media.limboFont1.glyphs['A'].imageWidth = 10;
    cgs.media.limboFont1.glyphs['A'].imageHeight = 10;
    cgs.media.limboFont1.glyphs['A'].glyph = 777;
    nameTest = 1;
    for(mode = 0; mode < 2; ++mode) {
        memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
        strcpy(cgs.gameState.stringData + 1, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        for(alive = 0; alive < 2; ++alive) for(cls = 0; cls < 5; ++cls)
        for(targetAlive = 0; targetAlive < 2; ++targetAlive) for(team = 1; team <= 2; ++team)
        for(dead = 0; dead < 2; ++dead) for(r = 0; r < 7; ++r) {
            int expected = mode && team == 1 && ranges[r] > 0 &&
                (alive ? (cls == PC_MEDIC && dead && ranges[r] >= 64 && ranges[r] <= 1600) :
                         (cls == PC_MEDIC && targetAlive));
            memset(&cent, 0, sizeof(cent)); cent.currentState.number = cent.currentState.clientNum = 2;
            cent.currentState.eFlags = dead ? EF_DEAD : 0; cent.lerpOrigin[0] = (float)ranges[r];
            cgs.clientinfo[2].team = team; cgs.clientinfo[2].cls = cls;
            cgs.clientinfo[2].health = targetAlive * 100; strcpy(cgs.clientinfo[2].name, "A");
            snapshot.ps.stats[STAT_HEALTH] = alive * 100; snapshot.ps.stats[STAT_PLAYER_CLASS] = cls;
            CG_NitmodNamesReset();
            if(CG_NitmodQueueWoundedName(&cent) != expected) ++errors;
        }
    }
    cent.lerpOrigin[0] = 100; cent.currentState.eFlags = EF_DEAD;
    cgs.clientinfo[2].team = TEAM_AXIS;
    snapshot.ps.stats[STAT_HEALTH] = 100; snapshot.ps.stats[STAT_PLAYER_CLASS] = PC_MEDIC;
    for(nameBlocked = 0; nameBlocked < 2; ++nameBlocked) {
        CG_NitmodNamesReset(); strcpy(cgs.clientinfo[2].name, "A");
        for(i = 0; i < 34; ++i) if(CG_NitmodQueueWoundedName(&cent) != (i < 32)) ++errors;
        strcpy(cgs.clientinfo[2].name, "B"); /* Queue owns the original text. */
        nameTraces = nameDraws = 0;
        CG_NitmodDrawWoundedNames();
        if(nameTraces != 32 || (!nameBlocked && (!nameDraws || nameShader != 777)) ||
           (nameBlocked && nameDraws)) ++errors;
        CG_NitmodDrawWoundedNames(); if(nameTraces != 32) ++errors;
    }
    nameTest = 0; CG_NitmodNamesReset();
    cg = savedCg; cgs.gameState = savedGame; cgs.media.limboFont1 = savedFont;
    cgs.clientinfo[2] = savedClient; cgs.gametype = oldGame;
    cg_draw2D.integer = oldDraw; cg_woundedNames.integer = oldNames;
    if(cg.snap) CG_BuildSolidList();
    return errors;
}
static int CheckFloatingNames(void) {
    static cg_t savedCg;
    static fontInfo_t savedFont;
    gameState_t savedGame = cgs.gameState;
    clientInfo_t savedLocal = cgs.clientinfo[1], savedTarget = cgs.clientinfo[2];
    snapshot_t snapshot;
    centity_t cent;
    nitmodNameFade_t fade;
    int mode, team, role, draw, i, errors = 0, savedDraw = cg_draw2D.integer;
    savedCg = cg; savedFont = cgs.media.limboFont1;
    memset(&fade, 0, sizeof(fade));
    if(CG_NitmodNameFade(&fade, qtrue, 1000) != 0 ||
       CG_NitmodNameFade(&fade, qtrue, 1125) != .5f ||
       CG_NitmodNameFade(&fade, qtrue, 1250) != 1 ||
       CG_NitmodNameFade(&fade, qfalse, 1375) != .5f ||
       CG_NitmodNameFade(&fade, qfalse, 1500) != 0 ||
       CG_NitmodNameFade(&fade, qtrue, 1625) != .5f ||
       CG_NitmodNameFade(&fade, qtrue, 1750) != 1 ||
       CG_NitmodNameFade(&fade, qtrue, 50) != 0) ++errors;
    if(CG_NitmodFloatNameScale(0) != .5f || CG_NitmodFloatNameScale(750) != .25f ||
       CG_NitmodFloatNameScale(1125) != .125f || CG_NitmodFloatNameScale(1600) != .125f) ++errors;
    memset(&snapshot, 0, sizeof(snapshot)); memset(&cent, 0, sizeof(cent));
    cg.snap = &snapshot; cg.nextSnap = NULL; cg.clientNum = snapshot.ps.clientNum = 1;
    CG_BuildSolidList(); cg.refdef_current = &cg.refdef;
    VectorClear(cg.refdef.vieworg); VectorClear(cg.refdefViewAngles);
    cg.refdef.fov_x = 96; cg.refdef.fov_y = 102;
    cent.currentState.number = cent.currentState.clientNum = 2;
    cent.currentState.eType = ET_PLAYER; cent.lerpOrigin[0] = 100;
    cgs.clientinfo[2].infoValid = qtrue; cgs.clientinfo[2].team = TEAM_AXIS;
    strcpy(cgs.clientinfo[2].name, "A");
    memset(&cgs.media.limboFont1, 0, sizeof(cgs.media.limboFont1));
    cgs.media.limboFont1.glyphScale = 1;
    cgs.media.limboFont1.glyphs['A'].xSkip = 10;
    cgs.media.limboFont1.glyphs['A'].height = 10;
    cgs.media.limboFont1.glyphs['A'].imageWidth = 10;
    cgs.media.limboFont1.glyphs['A'].imageHeight = 10;
    cgs.media.limboFont1.glyphs['A'].glyph = 777;
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    for(mode = 0; mode < 2; ++mode) for(team = TEAM_AXIS; team <= TEAM_SPECTATOR; ++team)
    for(role = 0; role < 2; ++role) for(draw = 0; draw < 2; ++draw) {
        strcpy(cgs.gameState.stringData + 1, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        snapshot.ps.persistant[PERS_TEAM] = team; cgs.clientinfo[1].nitmodShoutcaster = role;
        cg_draw2D.integer = draw; CG_NitmodNamesReset();
        if(CG_NitmodQueueSpectatorName(&cent) !=
           !!(mode && team == TEAM_SPECTATOR && draw && (role || NITMOD_SimpleConfig()->spectatorNames))) ++errors;
    }
    cg_draw2D.integer = 1; nameTest = 1; nameBlocked = 0; cg.time = 1000;
    CG_NitmodNamesReset(); CG_NitmodQueueSpectatorName(&cent); CG_NitmodDrawSpectatorNames();
    cg.time = 1250; CG_NitmodNamesBeginFrame();
    for(i = 0; i < 18; ++i) if(CG_NitmodQueueSpectatorName(&cent) != (i < 16)) ++errors;
    strcpy(cgs.clientinfo[2].name, "B");
    nameTraces = nameDraws = 0;
    CG_NitmodDrawSpectatorNames();
    if(nameTraces != 16 || !nameDraws || nameShader != 777) ++errors;
    CG_NitmodDrawSpectatorNames(); if(nameTraces != 16) ++errors;
    strcpy(cgs.clientinfo[2].name, "A");
    cg.time = 1500; nameBlocked = 1; CG_NitmodNamesBeginFrame();
    CG_NitmodQueueSpectatorName(&cent); nameDraws = 0; CG_NitmodDrawSpectatorNames();
    if(nameDraws) ++errors;
    cent.lerpOrigin[0] = -100;
    if(CG_NitmodQueueSpectatorName(&cent) || CG_NitmodQueueSpectatorName(NULL)) ++errors;
    cent.lerpOrigin[0] = 100; cent.currentState.clientNum = MAX_CLIENTS;
    if(CG_NitmodQueueSpectatorName(&cent)) ++errors;
    nameTest = 0; CG_NitmodNamesReset();
    cg = savedCg; cgs.gameState = savedGame; cgs.media.limboFont1 = savedFont;
    cgs.clientinfo[1] = savedLocal; cgs.clientinfo[2] = savedTarget; cg_draw2D.integer = savedDraw;
    if(cg.snap) CG_BuildSolidList();
    return errors;
}
static int hintTest, hintVisible, hintRefs, hintPics;
static refEntity_t hintEntities[2];
static int CheckHints(void) {
    static cg_t savedCg;
    static gameState_t savedGame;
    static snapshot_t snapshot;
    const int distances[] = {255,256,783,784,2303,2304};
    centity_t cent;
    int mode, team, cls, target, type, d, pvs, errors = 0;
    int savedDraw = cg_draw2D.integer, savedObj = cg_objectiveHints.integer, savedArt = cg_artilleryHints.integer;
    int savedTeam = cgs.clientinfo[1].team, savedClass = cgs.clientinfo[1].cls;
    int savedDynamite = cgs.media.dynamiteHintShader;
    savedCg = cg; savedGame = cgs.gameState;
    memset(&snapshot, 0, sizeof(snapshot)); snapshot.ps.clientNum = 1; cg.snap = &snapshot;
    cg.refdef_current = &cg.refdef; cg.time = 0;
    cg_draw2D.integer = cg_objectiveHints.integer = cg_artilleryHints.integer = 1;
    cgs.media.dynamiteHintShader = 813;
    hintTest = 1; CG_NitmodRegisterHintMedia();
    for(mode = 0; mode < 2; ++mode) {
        memset(&cgs.gameState, 0, sizeof(cgs.gameState));
        cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
        strcpy(cgs.gameState.stringData + 1, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        for(team = 1; team <= 2; ++team) for(cls = 0; cls < 5; ++cls)
        for(target = 0; target <= 3; ++target) for(type = 0; type < 2; ++type)
        for(d = 0; d < 6; ++d) for(pvs = 0; pvs < 2; ++pvs) {
            int valid = mode && cls == PC_ENGINEER && target && pvs &&
                (type ? (target == team || target == 3) : target != team);
            int refs = valid ? (distances[d] < 784 ? 2 : 1) : 0;
            memset(&cent, 0, sizeof(cent)); cent.currentState.eType = type ? 31 : 13;
            cent.currentState.teamNum = target;
            cgs.clientinfo[1].team = team; cgs.clientinfo[1].cls = cls;
            snapshot.ps.persistant[PERS_TEAM] = team;
            VectorSet(cg.predictedPlayerState.origin, distances[d], 0, 55);
            hintVisible = pvs; hintRefs = 0;
            if(CG_NitmodHintEntity(&cent) != mode || hintRefs != refs) ++errors;
            if(refs) {
                refEntity_t *icon = &hintEntities[refs-1];
                if(icon->reType != RT_SPRITE || icon->radius != 16 || icon->origin[2] != 79 ||
                   icon->customShader != (type ? 812 : 813) ||
                   !!(icon->renderfx & RF_DEPTHHACK) != (distances[d] < 2304)) ++errors;
                if(refs == 2 && (hintEntities[0].customShader != 810 || hintEntities[0].radius != 10 ||
                   hintEntities[0].shaderRGBA[team == 1 ? 0 : 2] != 255)) ++errors;
            }
        }
    }
    cg.time = 1000; VectorClear(cg.predictedPlayerState.origin);
    for(d = 399; d <= 576; ++d) {
        memset(&cent, 0, sizeof(cent)); cent.currentState.eType = 58;
        cent.currentState.teamNum = 2; cent.currentState.pos.trBase[0] = (float)d;
        CG_NitmodHintsReset(); CG_NitmodHintEntity(&cent);
        hintPics = 0; CG_NitmodDrawArtilleryHint();
        if(hintPics != (d < 576)) ++errors;
        CG_NitmodDrawArtilleryHint();
        if(hintPics != (d < 576)) ++errors;
    }
    hintTest = 0; CG_NitmodHintsReset(); cg = savedCg; cgs.gameState = savedGame;
    cg_draw2D.integer = savedDraw; cg_objectiveHints.integer = savedObj; cg_artilleryHints.integer = savedArt;
    cgs.clientinfo[1].team = savedTeam; cgs.clientinfo[1].cls = savedClass;
    cgs.media.dynamiteHintShader = savedDynamite;
    return errors;
}
static int anchorRender, anchorDraws;
static float anchorRect[4];
static int CheckHudAnchors(void) {
    static gameState_t saved;
    const int sizes[][2] = {{640,480},{1280,720},{1920,1080},{3440,1440},{1280,1024},{480,640},{0,0}};
    int mode, size, anchor, errors = 0;
    int width = cgs.glconfig.vidWidth, height = cgs.glconfig.vidHeight;
    float oldX = cgs.screenXScale, oldY = cgs.screenYScale;
    nitmodHudAnchor_t oldAnchor = CG_NitmodHudAnchor(NITMOD_HUD_STRETCH);
    saved = cgs.gameState;
    for(mode = 0; mode < 2; ++mode) for(size = 0; size < 7; ++size) {
        float sx, sy, bias;
        memset(&cgs.gameState, 0, sizeof(cgs.gameState));
        cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
        strcpy(cgs.gameState.stringData + 1, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        cgs.glconfig.vidWidth = sizes[size][0]; cgs.glconfig.vidHeight = sizes[size][1];
        cgs.screenXScale = sizes[size][0] / 640.f; cgs.screenYScale = sizes[size][1] / 480.f;
        for(anchor = -1; anchor <= 2; ++anchor) {
            float x = 320, y = 240, w = 100, h = 20, offset = 0;
            sx = cgs.screenXScale; sy = cgs.screenYScale;
            bias = 0;
            if(mode && anchor != -1 && sx > sy) { sx = sy; bias = (sizes[size][0] - 640 * sx) * .5f; }
            if(anchor == 0) offset = bias;
            if(anchor == 2) offset = 2 * bias;
            CG_NitmodHudAnchor((nitmodHudAnchor_t)anchor);
            CG_AdjustFrom640(&x, &y, &w, &h);
            if(fabs(x - (320 * sx + offset)) > .001f || fabs(y - 240 * sy) > .001f ||
               fabs(w - 100 * sx) > .001f || fabs(h - 20 * sy) > .001f) ++errors;
            anchorRender = 1; anchorDraws = 0;
            CG_DrawPic(320, 240, 100, 20, 123);
            anchorRender = 0;
            if(anchorDraws != 1 || fabs(anchorRect[0] - x) > .001f || fabs(anchorRect[1] - y) > .001f ||
               fabs(anchorRect[2] - w) > .001f || fabs(anchorRect[3] - h) > .001f) ++errors;
            if(CG_NitmodHudAnchor(NITMOD_HUD_STRETCH) != anchor) ++errors;
            x = 320; y = 240; w = 100; h = 20;
            CG_AdjustFrom640(&x, &y, &w, &h);
            if(x != 320 * cgs.screenXScale || w != 100 * cgs.screenXScale) ++errors;
        }
    }
    /* Original 1920x1080 reference: lower-left ring, not the ET portrait. */
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cgs.glconfig.vidWidth = 1920; cgs.glconfig.vidHeight = 1080;
    cgs.screenXScale = 3; cgs.screenYScale = 2.25f;
    CG_NitmodHudAnchor(NITMOD_HUD_LEFT);
    anchorRender = 1; anchorDraws = 0;
    CG_DrawPic(50, 386, 78, 78, 123);
    anchorRender = 0;
    if(anchorDraws != 1 || anchorRect[0] != 112.5f || anchorRect[1] != 868.5f ||
       anchorRect[2] != 175.5f || anchorRect[3] != 175.5f) ++errors;
    CG_NitmodHudAnchor(NITMOD_HUD_RIGHT); CG_NitmodHudReset();
    if(CG_NitmodHudAnchor(oldAnchor) != NITMOD_HUD_STRETCH) ++errors;
    cgs.gameState = saved; cgs.glconfig.vidWidth = width; cgs.glconfig.vidHeight = height;
    cgs.screenXScale = oldX; cgs.screenYScale = oldY;
    return errors;
}
static int CheckExtendedEvents(void) {
    static gameState_t gameState;
    static cg_t savedCg;
    static snapshot_t snapshot;
    centity_t cent;
    int bits, global, slot, errors = 0;
    const int slots[] = {-1, 0, MAX_SOUNDS - 1, MAX_SOUNDS, 2147483647};
    int savedFirst = cgs.gameSounds[0], savedLast = cgs.gameSounds[MAX_SOUNDS - 1];
    int savedSlap = cgs.media.nitmodSlapSound, savedThrow = cgs.media.nitmodThrowKnifeSound;
    gameState = cgs.gameState; savedCg = cg;
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    memset(&snapshot, 0, sizeof(snapshot)); snapshot.ps.clientNum = 1;
    cg.snap = &snapshot; cg.time = 1000;
    memset(&cent, 0, sizeof(cent)); cent.currentState.number = 5;
    cgs.gameSounds[0] = 301; cgs.gameSounds[MAX_SOUNDS - 1] = 302;
    extendedTest = 1;
    for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1)
    for(global = 0; global < 2; ++global) for(slot = 0; slot < 5; ++slot) {
        entityState_t before;
        cent.currentState.event = (global ? 103 : 100) | bits;
        cent.currentState.eventParm = slots[slot]; before = cent.currentState;
        extendedPlays = 0;
        CG_EntityEvent(&cent, cent.lerpOrigin);
        if(extendedPlays != (slot == 1 || slot == 2)) ++errors;
        if(extendedPlays && (extendedEntity != (global ? 1 : 5) || extendedChannel != CHAN_AUTO ||
           extendedHandle != (slot == 1 ? 301 : 302) || extendedVolume != 255 || extendedPosition)) ++errors;
        if(memcmp(&before, &cent.currentState, sizeof(before))) ++errors;
    }
    cgs.media.nitmodSlapSound = 303;
    for(slot = -1; slot <= 0; ++slot) {
        cgs.gameSounds[0] = slot;
        cent.currentState.event = 100; cent.currentState.eventParm = 0;
        extendedPlays = 0; CG_EntityEvent(&cent, cent.lerpOrigin);
        if(extendedPlays) ++errors;
    }
    for(slot = 0; slot < 4; ++slot) {
        cent.currentState.event = 102; cent.currentState.onFireStart = slot == 3 ? 0 : 100;
        cent.lerpOrigin[0] = slot * 50.0f;
        cg.cameraShakeScale = 0; extendedPlays = 0;
        CG_EntityEvent(&cent, cent.lerpOrigin);
        if(extendedPlays != 1 || extendedEntity != 1 || extendedChannel != CHAN_ANNOUNCER ||
           extendedHandle != 303 || extendedVolume != 127 || !extendedPosition ||
           cg.cameraShakeScale != (slot == 0 ? 1.0f : slot == 1 ? .5f : 0)) ++errors;
    }
    cent.currentState.event = 95; cent.currentState.weapon = WP_KNIFE;
    cgs.media.nitmodThrowKnifeSound = 304; extendedPlays = 0;
    CG_EntityEvent(&cent, cent.lerpOrigin);
    if(extendedPlays != 1 || extendedHandle != 304 || extendedChannel != CHAN_WEAPON ||
       extendedEntity != 5 || extendedVolume != 127 || cent.muzzleFlashTime != cg.time) ++errors;
    cent.currentState.event = 97; cent.currentState.number = 1;
    cg.weaponSelect = WP_MP40; cg.binocZoomTime = 0; cg.newCrosshairIndex = 0;
    cent.currentState.eventParm = 31; /* Original FG42, not native weapon 31. */
    CG_EntityEvent(&cent, cent.lerpOrigin);
    if(cg.weaponSelect != WP_FG42 || cg.weaponSelectTime != cg.time) ++errors;
    cent.currentState.eventParm = -1;
    CG_EntityEvent(&cent, cent.lerpOrigin);
    if(cg.weaponSelect != WP_FG42) ++errors;
    cent.currentState.number = 5; cent.currentState.eventParm = 3;
    CG_EntityEvent(&cent, cent.lerpOrigin);
    if(cg.weaponSelect != WP_FG42) ++errors;
    for(global = 0; global < 2; ++global) for(slot = -1; slot <= 3; ++slot) {
        int expected = slot >= 0 && slot <= 2 && (!global || slot != 2);
        int height = cg_teamChatHeight.integer, duration = cg_teamChatTime.integer;
        cg_teamChatHeight.integer = TEAMCHAT_HEIGHT; cg_teamChatTime.integer = 1000;
        cgs.teamChatPos = cgs.teamLastChatPos = 0;
        cent.currentState.density = slot;
        CG_NitmodFireSupportChat(&cent.currentState, global);
        if(cgs.teamChatPos != expected) ++errors;
        if(expected && (!strstr(cgs.teamChatMsgs[0], global ? (slot ? "Pilot:" : "HQ:") : "Fire Mission:") ||
           cgs.teamChatMsgTimes[0] != cg.time)) ++errors;
        cg_teamChatHeight.integer = height; cg_teamChatTime.integer = duration;
    }
    extendedTest = 0; cgs.gameSounds[0] = savedFirst; cgs.gameSounds[MAX_SOUNDS - 1] = savedLast;
    cgs.media.nitmodSlapSound = savedSlap; cgs.media.nitmodThrowKnifeSound = savedThrow;
    cgs.gameState = gameState; cg = savedCg;
    return errors;
}
static int materialTest, materialPlays, materialExpected;
static const char *materialPaths[] = {
    "sound/world/boardbreak.wav", "sound/world/glassbreak1.wav",
    "sound/world/glassbreak2.wav", "sound/world/glassbreak3.wav",
    "sound/world/metalbreak.wav", "sound/world/gibsplit1.wav",
    "sound/world/debris1.wav", "sound/world/stonefall.wav"
};
static int CheckEventPayloadBounds(void) {
    static gameState_t saved;
    static snapshot_t snapshot;
    snapshot_t *savedSnapshot = cg.snap;
    centity_t cent;
    const struct { int wire, native, limit, weapon; } cases[] = {
        {40, EV_GENERAL_SOUND, MAX_SOUNDS, 0},
        {41, EV_GENERAL_SOUND_VOLUME, MAX_SOUNDS, 0},
        {42, EV_GLOBAL_SOUND, MAX_SOUNDS, 0},
        {43, EV_GLOBAL_CLIENT_SOUND, MAX_SOUNDS, 0},
        {44, EV_GLOBAL_TEAM_SOUND, MAX_SOUNDS, 0},
        {45, EV_FX_SOUND, 6, 0},
        {39, EV_GRENADE_BOUNCE, FOOTSTEP_TOTAL + 1, 0},
        {28, EV_FILL_CLIP, WP_NUM_WEAPONS, 1},
        {30, EV_WEAP_OVERHEAT, WP_NUM_WEAPONS, 1},
        {67, EV_SPINUP, WP_NUM_WEAPONS, 1},
        {33, EV_FIRE_WEAPON, WP_NUM_WEAPONS, 1},
        {34, EV_FIRE_WEAPONB, WP_NUM_WEAPONS, 1},
        {35, EV_FIRE_WEAPON_LASTSHOT, WP_NUM_WEAPONS, 1}
    };
    int mode, i, j, errors = 0;
    saved = cgs.gameState;
    cg.snap = &snapshot;
    for(mode = 0; mode < 3; ++mode) {
        memset(&cgs.gameState, 0, sizeof(cgs.gameState));
        cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
        strcpy(cgs.gameState.stringData + 1, mode == 1 ? "\\gamename\\etmain" : "\\gamename\\nitmod");
        for(i = 0; i < sizeof(cases)/sizeof(cases[0]); ++i) for(j = 0; j < 4; ++j) {
            int bad = j == 0 ? -1 : j == 1 ? cases[i].limit : j == 2 ? 2147483647 : (-2147483647 - 1);
            entityState_t before;
            memset(&cent, 0, sizeof(cent));
            cent.currentState.number = cent.currentState.clientNum = 5;
            cent.currentState.event = (mode == 0 ? cases[i].wire : cases[i].native) | EV_EVENT_BITS;
            if(cases[i].weapon) cent.currentState.weapon = bad;
            else cent.currentState.eventParm = bad;
            before = cent.currentState;
            /* Invalid payloads must not reach the strict engine sound stubs. */
            if(mode == 2) CG_NativeEntityEvent(&cent, cent.lerpOrigin);
            else CG_EntityEvent(&cent, cent.lerpOrigin);
            if(memcmp(&before, &cent.currentState, sizeof(before))) ++errors;
        }
        for(i = 0; i < 2; ++i) for(j = 0; j < 6; ++j) {
            memset(&cent, 0, sizeof(cent));
            cent.currentState.event = mode == 0 ? 63 + i : (i ? EV_RUBBLE : EV_EXPLODE);
            if(j < 2) cent.currentState.frame = j ? 6 : -1;
            else if(j < 4) cent.currentState.dl_intensity = j == 2 ? -2 : MAX_SOUNDS;
            else {
                cent.currentState.eFlags = EF_INHERITSHADER;
                cent.currentState.modelindex = j == 4 ? -1 : MAX_MODELS;
            }
            if(mode == 2) CG_NativeEntityEvent(&cent, cent.lerpOrigin);
            else CG_EntityEvent(&cent, cent.lerpOrigin);
        }
    }
    memset(&cent, 0, sizeof(cent));
    cent.currentState.weapon = -1;
    CG_FireWeapon(&cent, EV_FIRE_WEAPON);
    cent.currentState.weapon = WP_NUM_WEAPONS;
    CG_FireWeapon(&cent, EV_FIRE_WEAPON);
    {
        int savedParent = cg_entities[5].tagParent, savedTank = cg_entities[6].tankparent;
        int savedDensity = cg_entities[7].currentState.density;
        cent.currentState.number = 5;
        cg_entities[5].tagParent = -1;
        if(CG_MountedTankIsBrowning(&cent)) ++errors;
        cg_entities[5].tagParent = MAX_GENTITIES;
        if(CG_MountedTankIsBrowning(&cent)) ++errors;
        cg_entities[5].tagParent = 6;
        cg_entities[6].tankparent = -1;
        if(CG_MountedTankIsBrowning(&cent)) ++errors;
        cg_entities[6].tankparent = MAX_GENTITIES;
        if(CG_MountedTankIsBrowning(&cent)) ++errors;
        cg_entities[6].tankparent = 7; cg_entities[7].currentState.density = 8;
        if(!CG_MountedTankIsBrowning(&cent)) ++errors;
        cg_entities[7].currentState.density = 0;
        if(CG_MountedTankIsBrowning(&cent)) ++errors;
        cg_entities[5].tagParent = savedParent; cg_entities[6].tankparent = savedTank;
        cg_entities[7].currentState.density = savedDensity;
    }
    {
        static snapshot_t wire;
        const int ids[] = {67, 70, 71, 95, 82, 86};
        const int converted = NITMOD_WeaponFromWire(31);
        for(i = 0; i < 6; ++i) for(j = 0; j < 2; ++j) {
            memset(&wire, 0, sizeof(wire));
            wire.numEntities = 1;
            wire.entities[0].eType = j ? 59 + ids[i] : ET_GENERAL;
            wire.entities[0].event = ids[i] | EV_EVENT_BIT1;
            wire.entities[0].weapon = wire.entities[0].nextWeapon = 31;
            NITMOD_TranslateSnapshotWeapons(&wire);
            if(wire.entities[0].weapon != (i < 4 ? converted : 31) ||
               wire.entities[0].nextWeapon != (i < 4 ? converted : 31) ||
               wire.entities[0].event != (ids[i] | EV_EVENT_BIT1)) ++errors;
        }
    }
    materialTest = 1; materialPlays = 0;
    /* All materials, including three glass variants, must stay within their
     * own registered sound set. Exercise enough draws to hit random()'s old
     * inclusive upper endpoint on the native deterministic PRNG. */
    srand(1);
    CG_PrecacheFXSounds();
    for(i = 0; i < 6; ++i) {
        materialExpected = i;
        memset(&cent, 0, sizeof(cent));
        cent.currentState.number = 5; cent.currentState.eventParm = i;
        cent.currentState.event = EV_FX_SOUND;
        for(j = 0; j < 65536; ++j) CG_NativeEntityEvent(&cent, cent.lerpOrigin);
    }
    if(materialPlays != 6 * 65536) ++errors;
    {
        int savedSound = cg_weapons[WP_PANZERFAUST].spinupSound;
        cg_weapons[WP_PANZERFAUST].spinupSound = 200;
        materialExpected = -1;
        memset(&cent, 0, sizeof(cent));
        cent.currentState.number = 5; cent.currentState.weapon = WP_PANZERFAUST;
        cent.currentState.event = 67;
        CG_EntityEvent(&cent, cent.lerpOrigin);
        cent.currentState.event = EV_SPINUP;
        CG_NativeEntityEvent(&cent, cent.lerpOrigin);
        if(materialPlays != 6 * 65536 + 2) ++errors;
        cg_weapons[WP_PANZERFAUST].spinupSound = savedSound;
    }
    materialTest = 0;
    cg.snap = savedSnapshot; cgs.gameState = saved;
    return errors;
}
static int CheckWaterEvents(void) {
    static gameState_t saved;
    centity_t cent;
    const int nativeEvents[] = {EV_WATER_TOUCH, EV_WATER_LEAVE, EV_WATER_UNDER, EV_WATER_CLEAR};
    int mode, kind, parm, bits, i, errors = 0;
    int savedClient = cg.clientNum;
    saved = cgs.gameState;
    memset(&cent, 0, sizeof(cent));
    cent.currentState.number = cent.currentState.clientNum = 5;
    cg.clientNum = 5;
    cgs.media.watrInSound = 101; cgs.media.watrOutSound = 102;
    cgs.media.watrUnSound = 103; cgs.media.watrGaspSound = 104;
    waterTest = 1;
    for(mode = 0; mode < 3; ++mode) {
        memset(&cgs.gameState, 0, sizeof(cgs.gameState));
        cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
        strcpy(cgs.gameState.stringData + 1, mode == 1 ? "\\gamename\\etmain" : "\\gamename\\nitmod");
        for(kind = 0; kind < 4; ++kind) for(parm = 0; parm < 2; ++parm)
        for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1) {
            int event = (mode == 0 ? 18 + kind : nativeEvents[kind]) | bits;
            cent.currentState.event = event; cent.currentState.eventParm = parm;
            cg.waterundertime = 0;
            memset(waterSounds, 0, sizeof(waterSounds));
            if(mode == 2) CG_NativeEntityEvent(&cent, cent.lerpOrigin);
            else CG_EntityEvent(&cent, cent.lerpOrigin);
            for(i = 0; i < 4; ++i) {
                int expected = i == 0 ? kind == 0 : i == 1 ? kind == 1 || kind == 3 :
                    i == 2 ? kind == 2 && (mode != 0 || parm) : kind == 3 && parm;
                if(waterSounds[i] != expected) ++errors;
            }
            if(cent.currentState.event != event || cent.currentState.eventParm != parm ||
               cg.waterundertime != (kind == 2 ? cg.time + HOLDBREATHTIME : 0)) ++errors;
        }
    }
    waterTest = 0; cg.clientNum = savedClient; cgs.gameState = saved;
    return errors;
}
static int CheckNitmodHudText(void) {
    qtime_t time;
    char text[96], expected[96];
    vec3_t velocity = {300, 400, 0};
    int hour, mode, seconds, errors = 0;
    memset(&time, 0, sizeof(time));
    {
        const char *valid[] = {".16 .2 .17", ".16  .2 .17 .99", ".16,.2,.17", " .16\t.2 .17"};
        const char *invalid[] = {"", "RED", "1 2", "nan 0 0", "0 inf 0", "0 0 1e999", "1x 0 0"};
        static const struct { const char *name; float r, g, b; } presets[] = {
            {"default", .5f, .5f, .5f}, {"def", .5f, .5f, .5f},
            {"red", .75f, 0, 0}, {"green", 0, .75f, 0}, {"blue", 0, 0, .75f},
            {"black", 0, 0, 0}, {"white", 1, 1, 1},
            {"dkgrey", .25f, .25f, .25f}, {"darkgrey", .25f, .25f, .25f},
            {"dkgray", .25f, .25f, .25f}, {"darkgray", .25f, .25f, .25f},
            {"grey", .5f, .5f, .5f}, {"gray", .5f, .5f, .5f},
            {"cthulhu", 0, .25f, .25f}, {"cthulhu_green", 0, .25f, .25f}
        };
        vec4_t color, before;
        int i, a;
        for(i = 0; i < sizeof(presets) / sizeof(presets[0]); ++i) for(a = -1; a <= 2; ++a) {
            if(!CG_NitmodParseHudColor(presets[i].name, (float)a, color) ||
               color[0] != presets[i].r || color[1] != presets[i].g || color[2] != presets[i].b ||
               color[3] != (a < 0 ? 0 : a > 1 ? 1 : a)) ++errors;
        }
        {
            vmCvar_t savedBackground = cg_HUDBackgroundColor, savedBorder = cg_HUDBorderColor;
            vmCvar_t savedAlpha = cg_HUDAlpha;
            vec4_t background, border;
            Q_strncpyz(cg_HUDBackgroundColor.string, "cthulhu", sizeof(cg_HUDBackgroundColor.string));
            Q_strncpyz(cg_HUDBorderColor.string, "red", sizeof(cg_HUDBorderColor.string));
            cg_HUDAlpha.value = .4f;
            CG_NitmodHudColors(background, border);
            if(background[0] != 0 || background[1] != .25f || background[2] != .25f ||
               border[0] != .75f || border[1] != 0 || border[2] != 0 ||
               background[3] != .4f || border[3] != .4f) ++errors;
            if(strcmp(cg_HUDBackgroundColor.string, "cthulhu") || strcmp(cg_HUDBorderColor.string, "red")) ++errors;
            Q_strncpyz(cg_HUDBackgroundColor.string, "invalid", sizeof(cg_HUDBackgroundColor.string));
            CG_NitmodHudColors(background, border);
            if(fabs(background[0] - .16f) > .0001 || fabs(background[1] - .2f) > .0001 ||
               fabs(background[2] - .17f) > .0001 || border[0] != .75f) ++errors;
            cg_HUDBackgroundColor = savedBackground; cg_HUDBorderColor = savedBorder; cg_HUDAlpha = savedAlpha;
        }
        for(i = 0; i < 4; ++i) for(a = -1; a <= 2; ++a) {
            if(!CG_NitmodParseHudColor(valid[i], (float)a, color) ||
               fabs(color[0] - .16f) > .0001 || fabs(color[1] - .2f) > .0001 ||
               fabs(color[2] - .17f) > .0001 || color[3] != (a < 0 ? 0 : a > 1 ? 1 : a)) ++errors;
        }
        memset(before, 0x33, sizeof(before));
        for(i = 0; i < 7; ++i) {
            memcpy(color, before, sizeof(color));
            if(CG_NitmodParseHudColor(invalid[i], .8f, color) || memcmp(color, before, sizeof(color))) ++errors;
        }
        if(!CG_NitmodParseHudColor("-1 2 .5", .8f, color) || color[0] != 0 || color[1] != 1) ++errors;
    }
    {
        const int pings[] = {-1, 0, 1, 51, 999, 1000, 2001};
        const char *raw[] = {"Ping -1", "Ping 0", "Ping 1", "Ping 51", "Ping 999", "Ping 999", "Ping 999"};
        const char *avg[] = {"Avg Ping -0.50", "Avg Ping 0.00", "Avg Ping 0.50", "Avg Ping 25.50", "Avg Ping 499.50", "Avg Ping 500.00", "Avg Ping 1000.50"};
        int i, pass;
        for(pass = 0; pass < 2; ++pass) for(i = 0; i < 7; ++i)
        for(mode = -1; mode <= 3; ++mode) {
            CG_NitmodHudPingText(text, sizeof(text), pings[pass ? 6-i : i], mode);
            if(strcmp(text, !mode ? "" : mode == 1 ? raw[pass ? 6-i : i] : avg[pass ? 6-i : i])) ++errors;
        }
        CG_NitmodHudPingText(NULL, 0, 100, 2);
        text[0] = 'x'; CG_NitmodHudPingText(text, 0, 100, 2);
        if(text[0] != 'x') ++errors;
        {
            static snapshot_t pingSnapshot;
            snapshot_t *oldSnap = cg.snap;
            int oldPing = cg_drawPing.integer, oldTime = cg_drawTime.integer;
            int oldSpeed = cg_drawspeed.integer;
            cg.snap = &pingSnapshot; pingSnapshot.ping = 51;
            cg_drawTime.integer = cg_drawspeed.integer = 0;
            popupTest = 1; popupErrors = 0;
            for(mode = -1; mode <= 3; ++mode) {
                cg_drawPing.integer = mode; popupDraws = 0;
                if(CG_NitmodHud(20) != (mode ? 36 : 20) || !!popupDraws != !!mode) ++errors;
            }
            cg.snap = NULL; popupDraws = 0;
            if(CG_NitmodHud(20) != 20 || popupDraws) ++errors;
            errors += popupErrors; popupTest = 0;
            cg.snap = oldSnap; cg_drawPing.integer = oldPing;
            cg_drawTime.integer = oldTime; cg_drawspeed.integer = oldSpeed;
        }
    }
    {
        int samples, frame, count;
        for(samples = -1; samples <= 501; ++samples) {
            if(!samples) continue;
            count = samples < 4 ? 4 : samples > 500 ? 500 : samples;
            CG_NitmodHudReset();
            for(frame = 1; frame <= count + 2; ++frame) {
                CG_NitmodFPSText(text, sizeof(text), frame * 10, samples);
                if(strcmp(text, frame <= count ? "estimating" : "100 FPS")) ++errors;
            }
        }
        CG_NitmodHudReset();
        for(frame = 1; frame <= 5; ++frame) CG_NitmodFPSText(text, sizeof(text), frame * 10, 4);
        CG_NitmodFPSText(text, sizeof(text), 70, 4);
        if(strcmp(text, "80 FPS")) ++errors; /* 10+10+10+20 ms */
        CG_NitmodFPSText(text, sizeof(text), 80, 5);
        if(strcmp(text, "estimating")) ++errors;
        CG_NitmodFPSText(text, sizeof(text), 90, 0);
        if(*text) ++errors;
        CG_NitmodFPSText(text, sizeof(text), -1, 5);
        if(strcmp(text, "estimating")) ++errors;
        CG_NitmodHudReset();
        for(frame = 0; frame < 5; ++frame) CG_NitmodFPSText(text, sizeof(text), 0, 4);
        if(strcmp(text, "4000 FPS")) ++errors;
        CG_NitmodHudReset();
        CG_NitmodFPSText(text, sizeof(text), 50, 4);
        if(strcmp(text, "estimating")) ++errors;
    }
    {
        int period, elapsed;
        const int remaining[] = {-1, 0, 999, 1000, 59999, 60000, 3599999, 3600000, 3661000, 86399999, 86400000, 90061000};
        const char *labels[] = {"^N0:00", "^F20 ^70:00", "^F20 ^70:00", "^F20 ^70:01", "^F20 ^70:59", "^F20 ^71:00", "^F20 ^759:59", "^F20 ^71:0:00", "^F20 ^71:1:01", "^F20 ^723:59:59", "^F20 ^71d0:0:00", "^F20 ^71d1:1:01"};
        static snapshot_t timerSnapshot;
        snapshot_t *oldSnap = cg.snap;
        int oldTime = cg.time, oldStart = cgs.levelStartTime;
        float oldLimit = cgs.timelimit;
        for(elapsed = 0; elapsed < 12; ++elapsed) {
            int playing, limited;
            for(playing = 0; playing < 2; ++playing) for(limited = 0; limited < 2; ++limited) {
                CG_NitmodMatchTimerText(text, sizeof(text), remaining[elapsed], limited, playing, "^F20 ");
                if(strcmp(text, !playing ? "^7WARMUP" : !limited ? "^F20 " : labels[elapsed])) ++errors;
            }
        }
        CG_NitmodMatchTimerText(text, sizeof(text), 1000, qtrue, qtrue, NULL);
        if(strcmp(text, "^70:01")) ++errors;
        for(period = 1; period <= 60; ++period) for(elapsed = 0; elapsed <= 180; ++elapsed) {
            CG_NitmodSpawnTimerText(text, sizeof(text), 600-elapsed, 600, period, "10:00");
            Com_sprintf(expected, sizeof(expected), "^1%d 10:00", period - elapsed % period);
            if(strcmp(text, expected)) ++errors;
        }
        CG_NitmodSpawnTimerText(text, sizeof(text), 600, -1, 30, "10:00");
        if(strcmp(text, "10:00")) ++errors;
        CG_NitmodSpawnTimerText(text, sizeof(text), 600, 600, 0, "10:00");
        if(strcmp(text, "10:00")) ++errors;
        timerTest = 1; cg.snap = &timerSnapshot;
        cg.time = 11000; cgs.levelStartTime = 1000; cgs.timelimit = 10;
        fields[0] = "timerSet"; fields[1] = "30"; argcValue = 2; timerWrites = 0;
        if(!CG_ConsoleCommand() || timerWrites != 2 || strcmp(timerPeriod, "30") || strcmp(timerStart, "590")) ++errors;
        argcValue = 1; timerWrites = 0;
        if(!CG_ConsoleCommand() || timerWrites != 1 || strcmp(timerStart, "-1")) ++errors;
        fields[0] = "resetTimer"; timerWrites = 0;
        if(!CG_ConsoleCommand() || timerWrites != 1 || strcmp(timerStart, "590")) ++errors;
        fields[0] = "timerSet"; fields[1] = "61"; argcValue = 2; timerWrites = 0;
        if(!CG_ConsoleCommand() || timerWrites) ++errors;
        timerTest = 0; cg.snap = oldSnap;
        cg.time = oldTime; cgs.levelStartTime = oldStart; cgs.timelimit = oldLimit;
    }
    {
        static snapshot_t classSnapshot;
        static gameState_t oldState;
        snapshot_t *oldSnap = cg.snap;
        int oldClient = cg.clientNum, oldTeam = cgs.clientinfo[0].team;
        int oldSelection = cgs.ccSelectedWeapon, oldLoadout = cgs.limboLoadoutSelected;
        int oldMenuTeam = cgs.ccSelectedTeam, oldMenuClass = cgs.ccSelectedClass;
        int oldModified = cgs.limboLoadoutModified, oldSecondarySelection = cgs.ccSelectedWeapon2;
        const char *classes[] = {"s", "m", "e", "f", "c"};
        const int originalWeapons[2][5][6] = {
            {{3,29,6,5,33,0},{3,8,10,0,0,0},{3,8,22,0,0,0},{3,8,10,0,0,0},{10,31,30,0,0,0}},
            {{8,29,6,5,33,0},{8,3,10,0,0,0},{8,3,23,0,0,0},{8,3,10,0,0,0},{10,31,24,0,0,0}}
        };
        int original, team, cls, choice;
        oldState = cgs.gameState; cg.snap = &classSnapshot; cg.clientNum = 0;
        classTest = 1;
        for(original = 0; original < 2; ++original) {
            memset(&cgs.gameState, 0, sizeof(cgs.gameState));
            if(original) {
                cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
                strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
            }
            for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team)
            for(cls = 0; cls < 5; ++cls) for(choice = 0; choice <= 7; ++choice) {
                bg_playerclass_t *info = BG_GetPlayerClassInfo(team, cls);
                char number[8], command[128];
                int selected = choice >= 1 && choice <= 6 && info->classWeapons[choice-1] ? choice-1 : 0;
                int weapon = info->classWeapons[selected];
                if(original) {
                    const int *list = originalWeapons[team - TEAM_AXIS][cls];
                    selected = choice >= 1 && choice <= 6 && list[choice-1] ? choice-1 : 0;
                    weapon = list[selected];
                }
                cgs.clientinfo[0].team = team;
                cgs.ccSelectedTeam = team == TEAM_AXIS ? 1 : 0;
                cgs.ccSelectedClass = cls;
                if(choice == 0) {
                    int i, count = 0;
                    int heavy, light, row;
                    int oldHeavy = cgs.clientinfo[0].skill[SK_HEAVY_WEAPONS];
                    int oldLight = cgs.clientinfo[0].skill[SK_LIGHT_WEAPONS];
                    int oldSecondary = cgs.ccSelectedWeapon2, oldSlot = cgs.ccSelectedWeaponNumber;
                    int oldPreference = cg_limbo_secondary.integer, oldSelectedFlag = cgs.limboLoadoutSelected;
                    bg_playerclass_t savedBase = *info;
                    for(i = 0; i < MAX_WEAPS_PER_CLASS; ++i) {
                        int expectedWeapon = original ? (i < 6 ? originalWeapons[team - TEAM_AXIS][cls][i] : 0) : info->classWeapons[i];
                        int actual = CG_LimboPanel_GetWeaponForNumber(i, 1, qtrue);
                        if(expectedWeapon) ++count;
                        if((original ? NITMOD_WeaponToWire(actual) : actual) != expectedWeapon) ++errors;
                        if(!expectedWeapon && !CG_LimboPanel_WeaponIsDisabled(i)) ++errors;
                    }
                    if(CG_LimboPanel_WeaponCount_ForSlot(1) != count || memcmp(info, &savedBase, sizeof(savedBase))) ++errors;
                    if(CG_LimboPanel_GetWeaponForNumber(-1, 1, qtrue) != WP_NONE ||
                       CG_LimboPanel_GetWeaponForNumber(MAX_WEAPS_PER_CLASS, 1, qtrue) != WP_NONE ||
                       !CG_LimboPanel_WeaponIsDisabled(-1) || !CG_LimboPanel_WeaponIsDisabled(MAX_WEAPS_PER_CLASS)) ++errors;
                    for(heavy = 0; heavy <= 4; ++heavy) for(light = 0; light <= 4; ++light) {
                        int choices[3], n = 1;
                        choices[0] = cls == PC_COVERTOPS ? (team == TEAM_AXIS ? WP_SILENCER : WP_SILENCED_COLT) :
                            (team == TEAM_AXIS ? WP_LUGER : WP_COLT);
                        if(light == 4) choices[n++] = cls == PC_COVERTOPS ?
                            (team == TEAM_AXIS ? WP_AKIMBO_SILENCEDLUGER : WP_AKIMBO_SILENCEDCOLT) :
                            (team == TEAM_AXIS ? WP_AKIMBO_LUGER : WP_AKIMBO_COLT);
                        if(heavy == 4 && cls == PC_SOLDIER) choices[n++] = team == TEAM_AXIS ? WP_MP40 : WP_THOMPSON;
                        cgs.clientinfo[0].skill[SK_HEAVY_WEAPONS] = heavy;
                        cgs.clientinfo[0].skill[SK_LIGHT_WEAPONS] = light;
                        cgs.ccSelectedWeaponNumber = 0;
                        if(CG_LimboPanel_WeaponCount_ForSlot(0) != n) ++errors;
                        for(row = -1; row <= 3; ++row) {
                            cg_limbo_secondary.integer = row; cgs.limboLoadoutSelected = qfalse;
                            cgs.ccSelectedWeapon2 = 99;
                            CG_LimboPanel_RestoreSecondaryPreference();
                            if(cgs.ccSelectedWeapon2 != (row < 0 ? 0 : row >= n ? n-1 : row) ||
                               cg_limbo_secondary.integer != row) ++errors;
                            cgs.limboLoadoutSelected = qtrue; cgs.ccSelectedWeapon2 = 99;
                            CG_LimboPanel_RestoreSecondaryPreference();
                            if(cgs.ccSelectedWeapon2 != 99) ++errors;
                        }
                        for(row = -1; row <= 3; ++row) {
                            int valid = row >= 0 && row < n;
                            if(CG_LimboPanel_GetWeaponForNumber(row, 0, qtrue) != (valid ? choices[row] : WP_NONE)) ++errors;
                            cgs.ccSelectedWeapon2 = row;
                            if(CG_LimboPanel_GetSelectedWeaponNum() != (valid ? row : 0)) ++errors;
                            cgs.ccSelectedWeapon2 = row;
                            if(CG_LimboPanel_GetSelectedWeaponForSlot(0) != choices[valid ? row : 0]) ++errors;
                        }
                    }
                    cgs.clientinfo[0].skill[SK_HEAVY_WEAPONS] = oldHeavy;
                    cgs.clientinfo[0].skill[SK_LIGHT_WEAPONS] = oldLight;
                    cgs.ccSelectedWeapon2 = oldSecondary; cgs.ccSelectedWeaponNumber = oldSlot;
                    cg_limbo_secondary.integer = oldPreference; cgs.limboLoadoutSelected = oldSelectedFlag;
                }
                Com_sprintf(number, sizeof(number), "%d", choice);
                fields[0] = "class"; fields[1] = classes[cls]; fields[2] = number;
                argcValue = choice ? 3 : 2; classSends = 0; cgs.limboLoadoutSelected = qfalse;
                Com_sprintf(command, sizeof(command), "team %s %i %i \n", team == TEAM_AXIS ? "r" : "b",
                    cls, weapon);
                if(!CG_ConsoleCommand() || classSends != 1 || strcmp(classCommand, command) ||
                   cgs.ccSelectedWeapon != selected || !cgs.limboLoadoutSelected) ++errors;
                if(choice == 0) {
                    int pistol = cls == PC_COVERTOPS ? (team == TEAM_AXIS ? WP_SILENCER : WP_SILENCED_COLT) :
                        (team == TEAM_AXIS ? WP_LUGER : WP_COLT);
                    Com_sprintf(command, sizeof(command), "team %s %i %i %i\n", team == TEAM_AXIS ? "r" : "b",
                        cls, weapon, original ? NITMOD_WeaponToWire(pistol) : pistol);
                    cgs.ccSelectedWeapon = 0x7fffffff; cgs.ccSelectedWeapon2 = -1;
                    cgs.limboLoadoutSelected = cgs.limboLoadoutModified = qfalse;
                    classSends = 0;
                    CG_LimboPanel_SendSetupMsg(qfalse);
                    if(classSends != 1 || strcmp(classCommand, command) || cgs.ccSelectedWeapon ||
                       cgs.ccSelectedWeapon2 || !cgs.limboLoadoutSelected || !cgs.limboLoadoutModified) ++errors;
                }
            }
        }
        cgs.clientinfo[0].team = TEAM_SPECTATOR; classSends = 0;
        preferenceTest = 1; preferenceWrites = 0;
        CG_LimboPanel_SetSelectedWeaponNumForSlot(0, 0);
        if(preferenceWrites) ++errors;
        CG_LimboPanel_SetSelectedWeaponNumForSlot(1, 1);
        if(preferenceWrites != 1 || preferenceValue != 1 || cgs.ccSelectedWeapon2 != 1) ++errors;
        {
            int oldSlot = cgs.ccSelectedWeaponNumber;
            cgs.ccSelectedWeaponNumber = 0; preferenceWrites = 0;
            CG_LimboPanel_SetSelectedWeaponNum(0);
            if(preferenceWrites != 1 || preferenceValue != 0) ++errors;
            preferenceWrites = 0;
            CG_LimboPanel_SetSelectedWeaponNum(-1);
            if(preferenceWrites) ++errors;
            cgs.ccSelectedWeaponNumber = oldSlot;
        }
        preferenceTest = 0; classSends = 0;
        if(!CG_ConsoleCommand() || classSends) ++errors;
        cgs.clientinfo[0].team = TEAM_AXIS; argcValue = 1;
        if(!CG_ConsoleCommand() || classSends) ++errors;
        cgs.ccSelectedTeam = -1; classSends = 0; CG_LimboPanel_SendSetupMsg(qfalse);
        cgs.ccSelectedTeam = 3; CG_LimboPanel_SendSetupMsg(qfalse);
        cgs.ccSelectedTeam = 1; cgs.ccSelectedClass = -1; CG_LimboPanel_SendSetupMsg(qfalse);
        cgs.ccSelectedClass = NUM_PLAYER_CLASSES; CG_LimboPanel_SendSetupMsg(qfalse);
        cgs.ccSelectedClass = PC_MEDIC; cg.snap = NULL; CG_LimboPanel_SendSetupMsg(qfalse);
        if(classSends) ++errors;
        {
            const int invalid[] = {-1, 0x7fffffff};
            panel_button_t button;
            int i;
            memset(&button, 0, sizeof(button));
            for(i = 0; i < 2; ++i) {
                cgs.ccSelectedTeam = invalid[i]; cgs.ccSelectedClass = invalid[i];
                if(CG_LimboPanel_GetTeam() != TEAM_SPECTATOR || CG_LimboPanel_GetClass() != PC_SOLDIER ||
                   CG_LimboPanel_GetCharacter() != BG_GetCharacter(TEAM_SPECTATOR, PC_SOLDIER)) ++errors;
                if(cgs.ccSelectedTeam != invalid[i] || cgs.ccSelectedClass != invalid[i]) ++errors;
                button.data[0] = button.data[1] = invalid[i];
                if(CG_LimboPanel_TeamButton_KeyDown(&button, K_MOUSE1) ||
                   CG_LimboPanel_ClassButton_KeyDown(&button, K_MOUSE1)) ++errors;
                CG_LimboPanel_RenderTeamButton(&button);
                cg.clientNum = invalid[i];
                if(CG_LimboPanel_GetRealTeam() != TEAM_SPECTATOR || CG_LimboPanel_WeaponCount_ForSlot(0)) ++errors;
            }
            button.data[0] = 3; button.data[1] = NUM_PLAYER_CLASSES;
            if(CG_LimboPanel_TeamButton_KeyDown(&button, K_MOUSE1) ||
               CG_LimboPanel_ClassButton_KeyDown(&button, K_MOUSE1) ||
               CG_LimboPanel_TeamButton_KeyDown(NULL, K_MOUSE1) ||
               CG_LimboPanel_ClassButton_KeyDown(NULL, K_MOUSE1)) ++errors;
            CG_LimboPanel_RenderTeamButton(&button); CG_LimboPanel_RenderTeamButton(NULL);
            if(CG_LimboPanel_WeaponCount_ForSlot(-1) || CG_LimboPanel_WeaponCount_ForSlot(2)) ++errors;
        }
        cg.snap = oldSnap; cg.clientNum = oldClient; cgs.clientinfo[0].team = oldTeam;
        cgs.ccSelectedWeapon = oldSelection; cgs.limboLoadoutSelected = oldLoadout;
        cgs.ccSelectedTeam = oldMenuTeam; cgs.ccSelectedClass = oldMenuClass;
        cgs.limboLoadoutModified = oldModified; cgs.ccSelectedWeapon2 = oldSecondarySelection;
        cgs.gameState = oldState; classTest = 0;
    }
    time.tm_min = 7; time.tm_sec = 9;
    for(hour = 0; hour < 24; ++hour) for(mode = 1; mode <= 2; ++mode)
    for(seconds = 0; seconds < 2; ++seconds) {
        time.tm_hour = hour;
        Com_sprintf(expected, sizeof(expected), "%d:07%s%s", mode == 1 ? hour : hour % 12 ? hour % 12 : 12,
            seconds ? ":09" : "", mode == 1 ? "" : hour < 12 ? " am" : " pm");
        CG_NitmodClockText(text, sizeof(text), &time, mode, seconds);
        if(strcmp(text, expected)) ++errors;
    }
    CG_NitmodClockText(text, sizeof(text), &time, 0, 0); if(*text) ++errors;
    time.tm_hour = 24;
    CG_NitmodClockText(text, sizeof(text), &time, 1, 0); if(*text) ++errors;
    CG_NitmodHudReset();
    CG_NitmodSpeedText(text, sizeof(text), velocity, 100, 2, 0, 100);
    if(strcmp(text, "0.0 UPS (0.0 MAX)")) ++errors;
    CG_NitmodSpeedText(text, sizeof(text), velocity, 101, 2, 0, 100);
    if(strcmp(text, "500.0 UPS (500.0 MAX)")) ++errors;
    CG_NitmodSpeedText(text, sizeof(text), velocity, 101, 1, 1, 100);
    if(strcmp(text, "32.1 KPH")) ++errors;
    CG_NitmodSpeedText(text, sizeof(text), velocity, 101, 1, 2, 100);
    if(strcmp(text, "21.3 MPH")) ++errors;
    VectorSet(velocity, 0, 0, 100);
    CG_NitmodSpeedText(text, sizeof(text), velocity, 202, 2, 0, 100);
    if(strcmp(text, "100.0 UPS (500.0 MAX)")) ++errors;
    CG_NitmodResetMaxSpeed();
    CG_NitmodSpeedText(text, sizeof(text), velocity, 202, 2, 0, 100);
    if(strcmp(text, "100.0 UPS (0.0 MAX)")) ++errors;
    CG_NitmodSpeedText(text, sizeof(text), velocity, 303, 2, 0, 100);
    if(strcmp(text, "100.0 UPS (100.0 MAX)")) ++errors;
    CG_NitmodSpeedText(text, sizeof(text), velocity, 303, 2, 3, 100); if(*text) ++errors;
    CG_NitmodHudReset();
    return errors;
}

static int CheckOriginalLanding(void) {
    centity_t cent;
    int surface, bits, errors = 0;
    memset(&cent, 0, sizeof(cent));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cgs.media.landHurt = 81;
    for(surface = 0; surface < FOOTSTEP_TOTAL; ++surface) cgs.media.landSound[surface] = 82;
    cent.currentState.number = 5;
    cent.currentState.clientNum = 5;
    cg.predictedPlayerState.clientNum = 5;
    cg.time = 12345;
    landingTest = 1;
    for(surface = -1; surface <= 255; ++surface) for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1) {
        cent.currentState.event = 17 | bits;
        cent.currentState.eventParm = surface;
        cent.pe.painTime = 0; cg.landTime = 0; cg.landChange = 0;
        landingPlays = hurtPlays = 0;
        CG_EntityEvent(&cent, cent.lerpOrigin);
        if(hurtPlays != 1 || cent.pe.painTime != cg.time || cg.landTime != cg.time || cg.landChange != -24 ||
           cent.currentState.event != (17 | bits) || cent.currentState.eventParm != surface) ++errors;
        if(surface && landingPlays != (surface > 0 && surface < FOOTSTEP_TOTAL)) ++errors;
    }
    landingTest = 0;
    return errors;
}
static int pmTest, pmValue, pmPlays, pmLoads;
static int CheckPrivateMessageSound(void) {
    centity_t cent;
    int value, target, bits, errors = 0;
    memset(&cent, 0, sizeof(cent));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cg.clientNum = 5;
    pmTest = 1; pmLoads = 0;
    NITMOD_ClearConfigStrings();
    for(value = -1; value <= 1; ++value) for(target = 4; target <= 5; ++target)
        for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1) {
            pmValue = value; pmPlays = 0;
            cent.currentState.number = target;
            cent.currentState.event = 98 | bits;
            CG_EntityEvent(&cent, cent.lerpOrigin);
            if(pmPlays != (value != 0 && target == 5) || cent.currentState.event != (98 | bits)) ++errors;
        }
    if(pmLoads != 1) ++errors;
    NITMOD_ClearConfigStrings();
    CG_EntityEvent(&cent, cent.lerpOrigin);
    if(pmLoads != 2) ++errors;
    pmTest = 0;
    return errors;
}
static int CheckMedicEvents(void) {
    static gameState_t saved;
    centity_t cent;
    int mode, team, bits, errors = 0;
    const char *info[] = {"\\gamename\\etmain", "\\gamename\\nitmod", "\\gamename\\nitmod\\nitmod_csLayout\\et260"};
    saved = cgs.gameState;
    cgs.media.sndMedicCall[0] = 71;
    cgs.media.sndMedicCall[1] = 72;
    for(mode = 0; mode < 3; ++mode) {
        memset(&cgs.gameState, 0, sizeof(cgs.gameState));
        cgs.gameState.dataCount = 1;
        /* Same synthetic serverinfo format as the TAGCONNECT fixture. */
        cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
        strcpy(cgs.gameState.stringData + 1, info[mode]);
        if(!!NITMOD_UsesOriginalProtocol() != (mode == 1)) ++errors;
        for(team = TEAM_FREE; team <= TEAM_SPECTATOR; ++team) {
            for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1) {
                entityState_t before;
                memset(&cent, 0, sizeof(cent));
                cent.currentState.number = MAX_CLIENTS - 1;
                cent.currentState.event = (mode == 1 ? 93 : EV_MEDIC_CALL) | bits;
                cgs.clientinfo[MAX_CLIENTS - 1].team = team;
                before = cent.currentState;
                medicSounds = 0;
                CG_EntityEvent(&cent, cent.lerpOrigin);
                if(memcmp(&before, &cent.currentState, sizeof(before))) ++errors;
                if(medicSounds != (team == TEAM_AXIS || team == TEAM_ALLIES)) ++errors;
                if(medicSounds && (medicEntity != MAX_CLIENTS - 1 ||
                   medicHandle != (team == TEAM_AXIS ? 71 : 72))) ++errors;
            }
        }
        cent.currentState.number = MAX_CLIENTS;
        medicSounds = 0;
        CG_EntityEvent(&cent, cent.lerpOrigin);
        if(medicSounds) ++errors;
        cent.currentState.number = -1;
        CG_EntityEvent(&cent, cent.lerpOrigin);
        if(medicSounds) ++errors;
    }
    cgs.gameState = saved;
    return errors;
}
static int CheckSharedWeaponDefinitions(void) {
    struct { const char *text; int valid; } cases[] = {
        {"weaponDef { both { damage 18 } client { readySound test.wav } }", 1},
        {"weaponDef { both_altweap { damage 20 } client { readySound test.wav } }", 1},
        {"weaponDef { both { nested { value 1 } } both_altweap { } client { readySound test.wav } }", 1},
        {"weaponDef { client { readySound test.wav } }", 1},
        {"weaponDef { client { readySound test.wav brassModel shell.md3 } }", 1},
        {"weaponDef { both damage 18 }", 0},
        {"weaponDef { both { damage 18", 0},
        {"weaponDef { both_altweap { damage 18", 0},
        {"weaponDef { unsupported { } }", 0},
        {"weaponDef { client { offset 1 2", 0},
        {"weaponDef { client { offset invalid", 0},
        {"weaponDef { client { flashSmokeLife invalid", 0},
        {"weaponDef { client { flashSmokeLife", 0},
        {"weaponDef { client { flashSmokeAlpha invalid", 0},
        {"weaponDef { client { flashSmokeSize invalid", 0},
        {"weaponDef { client { flashSmokeShader", 0}
    };
    int i, repeat, errors = 0;
    for(repeat = 0; repeat < 100; ++repeat) for(i = 0; i < sizeof(cases)/sizeof(cases[0]); ++i) {
        int oldPrints = prints;
        weaponCursor = (char *)cases[i].text;
        sourceLoads = sourceFrees = mediaSounds = 0;
        CG_RegisterWeapon(WP_MP40, qtrue);
        if(i == 4 && cg_weapons[WP_MP40].brassModel != 777) ++errors;
        if(sourceLoads != 1 || sourceFrees != 1 || mediaSounds != cases[i].valid ||
           (cases[i].valid && prints != oldPrints) ||
           (!cases[i].valid && prints == oldPrints)) ++errors;
    }
    for(i = 1; i <= 4; ++i) {
        char text[1024] = "weaponDef { client { ";
        int j;
        for(j = 0; j < i; ++j) strcat(text, "deathBySound test.wav deathBySoundFar test.wav ");
        strcat(text, "} }");
        weaponCursor = text;
        sourceLoads = sourceFrees = mediaSounds = 0;
        CG_RegisterWeapon(WP_MP40, qtrue);
        if(mediaSounds != 2 * i || sourceFrees != 1 ||
           cg_weapons[WP_MP40].deathBySoundCount != i || cg_weapons[WP_MP40].deathBySoundFarCount != i) ++errors;
    }
    return errors;
}
static int CheckViewTeamModels(void) {
    static weaponInfo_t saved, beforeFailure;
    weaponInfo_t *weapon = &cg_weapons[WP_MP40];
    const int views[] = {W_FP_MODEL, W_TP_MODEL};
    int v, team, mask, errors = 0, oldPrints = prints;
    saved = *weapon; teamMediaTest = 1; teamMediaRegistrations = 0;
    weaponCursor = "weaponDef { client { firstPerson { model m1 axisModel m2 alliedModel m3 skin s1 axisSkin s2 alliedSkin s3 } thirdPerson { model m3 axisModel m1 alliedModel missing skin s3 axisSkin s1 alliedSkin s2 } } }";
    sourceLoads = sourceFrees = 0;
    CG_RegisterWeapon(WP_MP40, qtrue);
    if(sourceLoads != 1 || sourceFrees != 1 || prints != oldPrints || teamMediaRegistrations != 12 ||
       weapon->viewTeamModel[W_FP_MODEL][TEAM_AXIS] != 102 ||
       weapon->viewTeamModel[W_FP_MODEL][TEAM_ALLIES] != 103 ||
       weapon->viewTeamModel[W_TP_MODEL][TEAM_AXIS] != 101 ||
       weapon->viewTeamModel[W_TP_MODEL][TEAM_ALLIES] != 0) ++errors;
    for(v = 0; v < 2; ++v) for(team = -1; team <= TEAM_SPECTATOR + 1; ++team) for(mask = 0; mask < 4; ++mask) {
        refEntity_t actual, expected;
        int view = views[v];
        memset(&actual, 0x5a, sizeof(actual)); expected = actual;
        expected.hModel = weapon->weaponModel[view].model;
        expected.customSkin = weapon->weaponModel[view].skin[0];
        if(team == TEAM_AXIS || team == TEAM_ALLIES) {
            weapon->viewTeamModel[view][team] = mask & 1 ? 900 + v : 0;
            weapon->weaponModel[view].skin[team] = mask & 2 ? 800 + v : 0;
            if(mask & 1) expected.hModel = 900 + v;
            if(mask & 2) expected.customSkin = 800 + v;
        }
        CG_NitmodViewMedia(weapon, view, team, &actual);
        if(memcmp(&actual, &expected, sizeof(actual))) ++errors;
    }
    /* Forced registration replaces stale per-team handles; malformed files
     * must not leave a half-loaded view definition behind. */
    weaponCursor = "weaponDef { client { firstPerson { axisModel m2 alliedModel";
    beforeFailure = *weapon;
    CG_RegisterWeapon(WP_MP40, qtrue);
    if(memcmp(weapon, &beforeFailure, sizeof(*weapon))) ++errors;
    weaponCursor = "weaponDef { client { firstPerson { model m1 } thirdPerson { model m3 } } }";
    CG_RegisterWeapon(WP_MP40, qtrue);
    for(v = 0; v < W_NUM_TYPES; ++v) for(team = 0; team < 3; ++team)
        if(weapon->viewTeamModel[v][team]) ++errors;
    *weapon = saved; teamMediaTest = 0;
    return errors;
}
static int CheckPartTeamModels(void) {
    static weaponInfo_t saved, baseline;
    weaponInfo_t *weapon = &cg_weapons[WP_MP40];
    int view, part, team, mask, errors = 0;
    saved = *weapon; teamMediaTest = 1;
    for(view = W_TP_MODEL; view <= W_FP_MODEL; ++view) for(part = 0; part < W_MAX_PARTS; ++part) {
        char text[512];
        partModel_t *model;
        int oldPrints = prints;
        Com_sprintf(text, sizeof(text), "weaponDef { client { %s { weaponLink { part %d { tag tag_test model m1 axisModel m2 alliedModel m3 skin s1 axisSkin s2 alliedSkin s3 } } } } }",
            view == W_FP_MODEL ? "firstPerson" : "thirdPerson", part);
        weaponCursor = text; sourceLoads = sourceFrees = teamMediaRegistrations = 0;
        CG_RegisterWeapon(WP_MP40, qtrue);
        model = &weapon->partModels[view][part];
        if(prints != oldPrints || sourceLoads != 1 || sourceFrees != 1 || teamMediaRegistrations != 6 ||
           model->model != 101 || model->teamModel[1] != 102 || model->teamModel[2] != 103 ||
           strcmp(model->tagName, "tag_test")) ++errors;
        for(team = -1; team <= TEAM_SPECTATOR + 1; ++team) for(mask = 0; mask < 4; ++mask) {
            refEntity_t actual, expected;
            memset(&actual, 0x5a, sizeof(actual)); expected = actual;
            expected.hModel = 101; expected.customSkin = 201;
            if(team == TEAM_AXIS || team == TEAM_ALLIES) {
                model->teamModel[team] = mask & 1 ? 901 : 0;
                model->skin[team] = mask & 2 ? 801 : 0;
                if(mask & 1) expected.hModel = 901;
                if(mask & 2) expected.customSkin = 801;
            }
            CG_NitmodPartMedia(model, team, &actual);
            if(memcmp(&actual, &expected, sizeof(actual))) ++errors;
        }
    }
    baseline = *weapon;
    weaponCursor = "weaponDef { client { firstPerson { weaponLink { part 0 { axisModel";
    CG_RegisterWeapon(WP_MP40, qtrue);
    if(memcmp(weapon, &baseline, sizeof(*weapon))) ++errors;
    weaponCursor = "weaponDef { client { firstPerson { weaponLink { part 0 { axisModel m2 } part 0 { model m1 } } } } }";
    CG_RegisterWeapon(WP_MP40, qtrue);
    if(weapon->partModels[W_FP_MODEL][0].teamModel[1] || weapon->partModels[W_FP_MODEL][0].model != 101) ++errors;
    *weapon = saved; teamMediaTest = 0;
    return errors;
}
extern qboolean CG_GetPartFramesFromWeap(centity_t *, refEntity_t *, refEntity_t *, int, weaponInfo_t *);
static int CheckPartAnimationFrames(void) {
    static weaponInfo_t weapon;
    centity_t cent;
    refEntity_t part, parent, expected;
    int slot, sequence, toggle, mode, i, errors = 0;
    memset(&cent, 0, sizeof(cent)); memset(&parent, 0, sizeof(parent));
    parent.frame = 102; parent.oldframe = 101; parent.backlerp = .25f;
    for(slot = 0; slot <= 16; ++slot) for(sequence = 0; sequence < MAX_WP_ANIMATIONS; ++sequence)
    for(toggle = 0; toggle < 2; ++toggle) for(mode = 0; mode < 4; ++mode) {
        unsigned int mask = (mode & 1 ? 1u << slot : 0) | (mode & 2 ? 1u << (slot + 8) : 0);
        int shown = slot == 16 || !(mask & (1u << (slot + 8)));
        memset(&weapon, 0, sizeof(weapon));
        for(i = 0; i < sequence; ++i) {
            weapon.weapAnimations[i].moveSpeed = (int)(1u << slot);
            weapon.weapAnimations[i].numFrames = 3;
        }
        cent.pe.weap.animationNumber = sequence | (toggle ? ANIM_TOGGLEBIT : 0);
        cent.pe.weap.animation = &weapon.weapAnimations[sequence];
        cent.pe.weap.animation->firstFrame = 100;
        cent.pe.weap.animation->moveSpeed = (int)mask;
        memset(&part, 0x5a, sizeof(part)); expected = part;
        if(shown && (mode & 1)) {
            expected.frame = sequence * 3 + 2; expected.oldframe = sequence * 3 + 1;
            expected.backlerp = parent.backlerp;
        }
        if(CG_GetPartFramesFromWeap(&cent, &part, &parent, slot, &weapon) != shown ||
           memcmp(&part, &expected, sizeof(part))) ++errors;
    }
    cent.pe.weap.animationNumber = MAX_WP_ANIMATIONS;
    if(CG_GetPartFramesFromWeap(&cent, &part, &parent, 0, &weapon)) ++errors;
    cent.pe.weap.animationNumber = 0;
    if(CG_GetPartFramesFromWeap(&cent, &part, &parent, -1, &weapon) ||
       CG_GetPartFramesFromWeap(&cent, &part, &parent, 17, &weapon)) ++errors;
    cent.pe.weap.animation = &weapon.weapAnimations[0];
    cent.pe.weap.animation->moveSpeed = 1;
    cent.pe.weap.animation->firstFrame = -2147483647;
    parent.frame = 2147483647; expected = part;
    if(CG_GetPartFramesFromWeap(&cent, &part, &parent, 0, &weapon) ||
       memcmp(&part, &expected, sizeof(part))) ++errors;
    return errors;
}
static int CheckRecoilDefinitionFields(void) {
    static weaponInfo_t saved, baseline;
    weaponInfo_t *weapon = &cg_weapons[WP_MP40];
    const char *fields[] = {"recoil_pitchAdd", "recoil_yawRandom", "recoil_pitchAddRandom"};
    int i, errors = 0, oldPrints = prints;
    saved = *weapon;
    weaponCursor = "weaponDef { client { recoil_pitchAdd 7 recoil_yawRandom 9 recoil_pitchAddRandom 11 } }";
    sourceLoads = sourceFrees = 0;
    CG_RegisterWeapon(WP_MP40, qtrue);
    if(prints != oldPrints || sourceLoads != 1 || sourceFrees != 1 ||
       weapon->recoilPitchAdd != 7 || weapon->recoilYawRandom != 9 || weapon->recoilPitchAddRandom != 11) ++errors;
    baseline = *weapon;
    for(i = 0; i < 3; ++i) {
        char text[256];
        Com_sprintf(text, sizeof(text), "weaponDef { client { %s", fields[i]);
        weaponCursor = text; sourceLoads = sourceFrees = 0;
        CG_RegisterWeapon(WP_MP40, qtrue);
        if(sourceLoads != 1 || sourceFrees != 1 || memcmp(weapon, &baseline, sizeof(*weapon))) ++errors;
    }
    weaponCursor = "weaponDef { client { } }";
    CG_RegisterWeapon(WP_MP40, qtrue);
    if(weapon->recoilPitchAdd || weapon->recoilYawRandom || weapon->recoilPitchAddRandom) ++errors;
    *weapon = saved;
    return errors;
}
static int CheckWeaponParseRollback(void) {
    static weaponInfo_t saved, baseline, empty;
    weaponInfo_t *weapon = &cg_weapons[WP_MP40];
    const char *prefix = "weaponDef { client { readySound test.wav firstPerson { weaponLink { part 0 { model shell.md3 tag tag_test ";
    char definition[512];
    int closings, cached, repeat, j, errors = 0;
    saved = *weapon;
    weaponCursor = "weaponDef { client { readySound test.wav brassModel shell.md3 } }";
    CG_RegisterWeapon(WP_MP40, qtrue);
    baseline = *weapon;
    empty.registered = qtrue;
    for(repeat = 0; repeat < 20; ++repeat) for(cached = 0; cached <= 1; ++cached)
    for(closings = 0; closings <= 5; ++closings) {
        int oldPrints = prints;
        if(cached) *weapon = baseline;
        else memset(weapon, 0, sizeof(*weapon));
        Q_strncpyz(definition, prefix, sizeof(definition));
        for(j = 0; j < closings; ++j) Q_strcat(definition, sizeof(definition), "} ");
        weaponCursor = definition;
        sourceLoads = sourceFrees = mediaSounds = 0;
        CG_RegisterWeapon(WP_MP40, qtrue);
        if(sourceLoads != 1 || sourceFrees != 1 || mediaSounds != 1) ++errors;
        if(closings >= 4) {
            if(prints != oldPrints || weapon->readySound != 42 || weapon->brassModel ||
               weapon->partModels[W_FP_MODEL][0].model != 777 ||
               strcmp(weapon->partModels[W_FP_MODEL][0].tagName, "tag_test")) ++errors;
        } else if(prints == oldPrints || memcmp(weapon, cached ? &baseline : &empty, sizeof(*weapon))) ++errors;
        // Failed first registration is cached to avoid a retry storm every frame.
        CG_RegisterWeapon(WP_MP40, qfalse);
        if(sourceLoads != 1 || sourceFrees != 1) ++errors;
    }
    *weapon = saved;
    return errors;
}
static int CheckWeaponRegistrationAndSelection(void) {
    static playerState_t savedState;
    weaponInfo_t savedWeapon;
    char filename[MAX_QPATH];
    int weapon, owned, ammo, clip, mounted, errors = 0, count = 0;
    savedState = cg.predictedPlayerState;
    for(weapon = 1; weapon < WP_NUM_WEAPONS; ++weapon) {
        const nitmodWeaponPath_t *path = NITMOD_WeaponPath(weapon);
        int oldPrints = prints;
        if(!path && weapon != WP_MAPMORTAR) continue;
        if(path) ++count;
        savedWeapon = cg_weapons[weapon];
        Com_sprintf(filename, sizeof(filename), "weapons/%s", path ? path->filename : "mapmortar.weap");
        expectedWeaponPath = filename;
        weaponCursor = "weaponDef { client { readySound test.wav } }";
        sourceLoads = sourceFrees = mediaSounds = 0;
        CG_RegisterWeapon(weapon, qtrue);
        CG_RegisterWeapon(weapon, qfalse);
        if(sourceLoads != 1 || sourceFrees != 1 || mediaSounds != 1 || prints != oldPrints ||
           cg_weapons[weapon].readySound != 42) ++errors;
        cg_weapons[weapon] = savedWeapon;
        if(!path) continue;
        for(owned = 0; owned <= 1; ++owned) for(ammo = 0; ammo <= 1; ++ammo)
        for(clip = 0; clip <= 1; ++clip) for(mounted = 0; mounted <= 2; ++mounted) {
            int expected = owned && !mounted && (ammo || clip || weapon == WP_KNIFE || weapon == WP_PLIERS);
            memset(&cg.predictedPlayerState, 0, sizeof(cg.predictedPlayerState));
            if(owned) COM_BitSet(cg.predictedPlayerState.weapons, weapon);
            cg.predictedPlayerState.ammo[BG_FindAmmoForWeapon(weapon)] = ammo;
            cg.predictedPlayerState.ammoclip[BG_FindClipForWeapon(weapon)] = clip;
            cg.predictedPlayerState.eFlags = mounted == 1 ? EF_MG42_ACTIVE : mounted == 2 ? EF_MOUNTEDTANK : 0;
            if(CG_WeaponSelectable(weapon) != expected) ++errors;
        }
    }
    if(count != 44) ++errors;
    expectedWeaponPath = NULL;
    sourceLoads = 0;
    CG_RegisterWeapon(-1, qtrue); CG_RegisterWeapon(WP_NUM_WEAPONS, qtrue);
    CG_RegisterWeapon(0x7fffffff, qtrue);
    if(sourceLoads || CG_WeaponSelectable(-1) || CG_WeaponSelectable(WP_NUM_WEAPONS) ||
       CG_WeaponSelectable(0x7fffffff)) ++errors;
    cg.predictedPlayerState = savedState;
    return errors;
}
static int CheckWeaponCommandGuards(void) {
    static cg_t saved, expected;
    static snapshot_t snapshot;
    void (*commands[])(void) = {CG_AltWeapon_f, CG_LastWeaponUsed_f, CG_NextWeaponInBank_f,
        CG_PrevWeaponInBank_f, CG_NextWeapon_f, CG_PrevWeapon_f, CG_WeaponBank_f, CG_Weapon_f};
    const char *badBanks[] = {"-1", "0", "10", "11", "2147483647", "not-a-bank"};
    const char *savedArg = fields[1];
    int i, errors = 0, savedDelay = cg_weaponCycleDelay.integer;
    saved = cg;
    memset(&cg, 0, sizeof(cg));
    cg.time = 500; cg.weaponSelectTime = 100; cg.weaponSelect = WP_KNIFE;
    cg_weaponCycleDelay.integer = 0;
    expected = cg;
    for(i = 0; i < sizeof(commands)/sizeof(commands[0]); ++i) {
        commands[i]();
        if(memcmp(&cg, &expected, sizeof(cg))) ++errors;
    }
    memset(&snapshot, 0, sizeof(snapshot));
    snapshot.ps.pm_type = PM_FREEZE; cg.snap = &snapshot;
    expected = cg;
    for(i = 0; i < sizeof(commands)/sizeof(commands[0]); ++i) {
        commands[i]();
        if(memcmp(&cg, &expected, sizeof(cg))) ++errors;
    }
    snapshot.ps.pm_type = PM_NORMAL;
    for(i = 0; i < sizeof(badBanks)/sizeof(badBanks[0]); ++i) {
        fields[1] = badBanks[i]; cg.weaponSelectTime = 100;
        expected = cg; expected.weaponSelectTime = cg.time;
        CG_WeaponBank_f();
        if(memcmp(&cg, &expected, sizeof(cg))) ++errors;
    }
    // A legitimate bank remains usable; selecting the current knife needs no sound syscall.
    COM_BitSet(cg.predictedPlayerState.weapons, WP_KNIFE);
    fields[1] = "1";
    CG_WeaponBank_f();
    if(cg.weaponSelect != WP_KNIFE || cg.lastWeapSelInBank[1] != WP_KNIFE) ++errors;
    {
        const int bank7[] = {WP_LANDMINE, WP_TRIPMINE, WP_MEDIC_ADRENALINE};
        int step;
        for(step = 0; step < 3; ++step) {
            COM_BitSet(cg.predictedPlayerState.weapons, bank7[step]);
            cg.predictedPlayerState.ammoclip[BG_FindClipForWeapon(bank7[step])] = 1;
        }
        fields[1] = "7";
        for(step = 0; step < 9; ++step) {
            ++cg.time;
            CG_WeaponBank_f();
            if(cg.weaponSelect != bank7[step % 3] || cg.lastWeapSelInBank[7] != bank7[step % 3]) ++errors;
        }
        // With no Tripmine ammunition the same bank must skip it, not become stuck.
        cg.predictedPlayerState.ammoclip[BG_FindClipForWeapon(WP_TRIPMINE)] = 0;
        ++cg.time; CG_WeaponBank_f();
        if(cg.weaponSelect != WP_LANDMINE) ++errors;
        ++cg.time; CG_WeaponBank_f();
        if(cg.weaponSelect != WP_MEDIC_ADRENALINE) ++errors;
    }
    fields[1] = savedArg; cg = saved; cg_weaponCycleDelay.integer = savedDelay;
    return errors;
}
static int CheckAnimationCacheReset(void) {
    static animModelInfo_t saved, zero, populated;
    animModelInfo_t *slot = &cgs.animScriptData.modelInfo[0], *result = NULL;
    int errors = 0;
    saved = *slot;
    memset(slot, 0x5a, sizeof(*slot));
    slot->animationGroup[0] = slot->animationScript[0] = 0;
    if(CG_CheckForExistingAnimModelInfo("test-cache.group", "test-cache.script", &result) ||
       result != slot || memcmp(slot, &zero, sizeof(*slot))) ++errors;
    Q_strncpyz(slot->animationGroup, "test-cache.group", sizeof(slot->animationGroup));
    Q_strncpyz(slot->animationScript, "test-cache.script", sizeof(slot->animationScript));
    populated = *slot;
    if(!CG_CheckForExistingAnimModelInfo("TEST-CACHE.GROUP", "TEST-CACHE.SCRIPT", &result) ||
       result != slot || memcmp(slot, &populated, sizeof(*slot))) ++errors;
    // Partially failed registration is a free slot, not a usable cached model.
    slot->animationScript[0] = 0;
    if(CG_CheckForExistingAnimModelInfo("test-cache.group", "test-cache.script", &result) ||
       result != slot || memcmp(slot, &zero, sizeof(*slot))) ++errors;
    *slot = saved;
    return errors;
}
static int CheckTeamWeaponMedia(void) {
    static weaponInfo_t saved;
    const char *definition = "weaponDef { client { pickupModel m1 axisPickupModel m2 alliedPickupModel m3 "
        "pickupSkin s1 axisPickupSkin s2 alliedPickupSkin s3 missileModel m1 "
        "AxisMissileModel m2 AlliedMissileModel missing missileAxisSkin s2 missileAlliedSkin s3 "
        "weaponIconScale 1 foreShorten 0.5 offset 1 2.5 3 "
        "flashSmokeShader p1 flashSmokeAlpha 0.6 flashSmokeSize 12 flashSmokeLife 750 } }";
    weaponInfo_t *weapon = &cg_weapons[WP_MP40];
    refEntity_t ent;
    int team, mask, errors = 0, oldPrints = prints;
    // A reused item slot must lose every old model/icon, not just sizeof(pointer).
    for(team = 1; team < bg_numItems; ++team) if(bg_itemlist[team].giType == IT_WEAPON) {
        itemInfo_t oldItem = cg_items[team], empty;
        memset(&empty, 0, sizeof(empty));
        memset(&cg_items[team], 0x5a, sizeof(cg_items[team]));
        cg_items[team].registered = qfalse;
        CG_RegisterItemVisuals(team);
        if(memcmp(&cg_items[team], &empty, sizeof(empty))) ++errors;
        cg_items[team] = oldItem;
    }
    saved = *weapon;
    teamMediaTest = 1; teamMediaRegistrations = 0;
    weaponCursor = (char *)definition;
    sourceLoads = sourceFrees = 0;
    CG_RegisterWeapon(WP_MP40, qtrue);
    if(sourceLoads != 1 || sourceFrees != 1 || prints != oldPrints || teamMediaRegistrations != 12 ||
       weapon->pickupTeamModel[1] != 102 || weapon->pickupTeamModel[2] != 103 ||
       weapon->weaponModel[W_PU_MODEL].skin[0] != 201 ||
       weapon->weaponModel[W_PU_MODEL].skin[1] != 202 || weapon->weaponModel[W_PU_MODEL].skin[2] != 203 ||
       !weapon->missileTeamModelDefined[1] || !weapon->missileTeamModelDefined[2]) ++errors;
    memset(&ent, 0, sizeof(ent));
    {
        nitmodWeaponSmoke_t smoke;
        vec3_t offset = {10, -4, 5};
        CG_NitmodWeaponOffset(weapon, offset, offset);
        if(offset[0] != 11 || offset[1] != -1.5f || offset[2] != 8) ++errors;
        if(!CG_NitmodFlashSmokeParams(weapon, WP_MP40, 0, &smoke) || smoke.shader != 301 ||
           smoke.life != 750 || smoke.alpha != .6f || smoke.size != 12) ++errors;
    }
    AxisClear(ent.axis);
    CG_NitmodShortenWeapon(weapon, &ent);
    if(weapon->foreShorten != 0.5f || ent.axis[0][0] != 0.5f || ent.axis[1][1] != 1 ||
       ent.axis[2][2] != 1 || !ent.nonNormalizedAxes || CG_NitmodWeaponIconScale(WP_MP40) != 1) ++errors;
    weapon->weaponIconScale = 3;
    if(CG_NitmodWeaponIconScale(WP_MP40) != 3) ++errors;
    weapon->weaponIconScale = 0;
    if(CG_NitmodWeaponIconScale(WP_MP40) != 2 || CG_NitmodWeaponIconScale(-1) != 1 ||
       CG_NitmodWeaponIconScale(WP_NUM_WEAPONS) != 1) ++errors;
    for(team = -2; team <= 11; ++team) {
        int valid = team == TEAM_AXIS || team == TEAM_ALLIES;
        CG_NitmodPickupMedia(weapon, team, &ent);
        if(ent.hModel != (valid ? 101 + team : 101) || ent.customSkin != (valid ? 201 + team : 201)) ++errors;
        CG_NitmodMissileMedia(weapon, WP_MP40, team, &ent);
        if(ent.hModel != (team == 1 ? 102 : team == 2 ? 0 : 101) ||
           ent.customSkin != (valid ? 201 + team : 0)) ++errors;
        CG_NitmodMissileMedia(weapon, WP_DYNAMITE, team, &ent);
        if(ent.hModel != (team % 4 == 1 ? 102 : team % 4 == 2 ? 0 : 101)) ++errors;
        CG_NitmodMissileMedia(weapon, WP_LANDMINE, team, &ent);
        if(ent.customSkin != (team % 4 == 1 ? 202 : team % 4 == 2 ? 203 : 0)) ++errors;
    }
    for(mask = 0; mask < 4; ++mask) for(team = 1; team <= 2; ++team) {
        weapon->pickupTeamModel[team] = mask & 1 ? 900 : 0;
        weapon->weaponModel[W_PU_MODEL].skin[team] = mask & 2 ? 901 : 0;
        CG_NitmodPickupMedia(weapon, team, &ent);
        if(ent.hModel != (mask & 1 ? 900 : 101) || ent.customSkin != (mask & 2 ? 901 : 201)) ++errors;
    }
    weapon->missileTeamModelDefined[2] = qfalse;
    CG_NitmodMissileMedia(weapon, WP_MP40, TEAM_ALLIES, &ent);
    if(ent.hModel != 101 || ent.customSkin != 203) ++errors;
    // Re-registration must clear both team handles and explicit-override flags.
    weaponCursor = "weaponDef { client { pickupModel m1 missileModel m1 } }";
    CG_RegisterWeapon(WP_MP40, qtrue);
    if(weapon->pickupTeamModel[1] || weapon->pickupTeamModel[2] ||
       weapon->missileTeamModelDefined[1] || weapon->missileTeamModelDefined[2] ||
       weapon->foreShorten || weapon->weaponIconScale || weapon->offset[0] || weapon->offset[1] || weapon->offset[2] ||
       weapon->flashSmoke.shader || weapon->flashSmoke.life || weapon->flashSmoke.alpha || weapon->flashSmoke.size) ++errors;
    memset(&ent, 0, sizeof(ent)); AxisClear(ent.axis);
    CG_NitmodShortenWeapon(weapon, &ent);
    if(ent.axis[0][0] != 1 || ent.nonNormalizedAxes) ++errors;
    *weapon = saved; teamMediaTest = 0;
    return errors;
}
static int CheckFlashSmoke(void) {
    static weaponInfo_t weapon;
    nitmodWeaponSmoke_t smoke;
    int mask, sten, shader, age, enabled, errors = 0;
    qhandle_t savedShader = cgs.media.smokeParticleShader;
    vec3_t origin = {1, 2, 3};
    cgs.media.smokeParticleShader = 888;
    memset(&weapon, 0, sizeof(weapon));
    particleInit = 1; CG_ClearParticles(); particleInit = 0;
    for(mask = 0; mask < 8; ++mask) for(sten = 0; sten <= 1; ++sten)
    for(shader = 0; shader <= 1; ++shader) for(age = 99; age <= 101; ++age) {
        int expected = shader || (sten && age < 100);
        weapon.flashSmoke.shader = shader ? 777 : 0;
        weapon.flashSmoke.life = mask & 1 ? 750 : 0;
        weapon.flashSmoke.alpha = mask & 2 ? .6f : 0;
        weapon.flashSmoke.size = mask & 4 ? 12 : 0;
        if(CG_NitmodFlashSmokeParams(&weapon, sten ? WP_STEN : WP_MP40, age, &smoke) != expected) ++errors;
        if(expected && (smoke.shader != (shader ? 777 : 888) ||
           smoke.life != (shader && (mask & 1) ? 750 : 500) ||
           smoke.alpha != (shader && (mask & 2) ? .6f : .25f) ||
           smoke.size != (shader && (mask & 4) ? 12 : 8))) ++errors;
        for(enabled = 0; enabled <= 1; ++enabled) {
            struct particle_s *before = free_particles, *activeBefore = active_particles;
            cg_smokeparticles.integer = enabled;
            CG_NitmodEmitFlashSmoke(&weapon, sten ? WP_STEN : WP_MP40, age, origin);
            if(expected && enabled) {
                if(free_particles == before || active_particles != before) ++errors;
            } else if(free_particles != before || active_particles != activeBefore) ++errors;
        }
    }
    cg_smokeparticles.integer = 1;
    cgs.media.smokeParticleShader = savedShader;
    return errors;
}
static void SetTestConfig(int index, const char *value) {
    int length = (int)strlen(value) + 1;
    if(cgs.gameState.dataCount + length >= MAX_GAMESTATE_CHARS) exit(2);
    cgs.gameState.stringOffsets[index] = cgs.gameState.dataCount;
    memcpy(cgs.gameState.stringData + cgs.gameState.dataCount, value, length);
    cgs.gameState.dataCount += length;
}
static int CheckTagConnectLayouts(void) {
    static gameState_t saved;
    const char *info[] = {"\\gamename\\etmain", "\\gamename\\nitmod", "\\gamename\\nitmod\\nitmod_csLayout\\et260"};
    int mode, errors = 0;
    saved = cgs.gameState;
    for(mode = 0; mode < 3; ++mode) {
        int base = mode == 1 ? 777 : CS_TAGCONNECTS;
        char number[16];
        memset(&cgs.gameState, 0, sizeof(cgs.gameState));
        cgs.gameState.dataCount = 1;
        SetTestConfig(CS_SERVERINFO, info[mode]);
        sentCapabilities = 0;
        cg.demoPlayback = qfalse;
        NITMOD_AdvertiseCapabilities();
        if(sentCapabilities != (mode == 2)) ++errors;
        cg.demoPlayback = qtrue;
        NITMOD_AdvertiseCapabilities();
        if(sentCapabilities != (mode == 2)) ++errors;
        cg.demoPlayback = qfalse;
        SetTestConfig(base, "1 3 tag_origin");
        SetTestConfig(base + 63, "2 4 tag_head");
        SetTestConfig(mode == 1 ? 841 : 777, "not a tag attachment");
        if(NITMOD_TagConnectBase() != base) ++errors;
        CG_ParseTagConnects();
        if(cg_entities[1].tagParent != 3 || strcmp(cg_entities[1].tagName, "tag_origin") ||
           cg_entities[2].tagParent != 4 || strcmp(cg_entities[2].tagName, "tag_head")) ++errors;
        SetTestConfig(base + 63, "2 9 tag_changed");
        fields[0] = "cs"; fields[1] = number; argcValue = 2;
        Com_sprintf(number, sizeof(number), "%d", base + 63);
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cg_entities[2].tagParent != 9 || strcmp(cg_entities[2].tagName, "tag_changed")) ++errors;
        if(mode == 1) {
            Com_sprintf(number, sizeof(number), "%d", 841);
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(cg_entities[2].tagParent != 9) ++errors;
        }
    }
    cgs.gameState = saved;
    return errors;
}
static int mapRenderTest, mapRenderPics, mapRenderArrows;
static float mapRenderRect[4], mapRenderAlpha;

#include "check_weapon_pose.h"
#include "check_view.h"
#include "check_scope_view.h"
#include "check_overlays.h"
static int CheckPlayerLean(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    snapshot_t snap;
    centity_t cent;
    vec3_t torso, head;
    int mode, direction, fraction, step, flags, errors = 0;
    const int blocked[] = {EF_MG42_ACTIVE, EF_MOUNTEDTANK, EF_FIRING, EF_DEAD, EF_SPARE0, EF_PRONE};
    savedCg = cg; savedCgs = cgs;
    memset(&snap, 0, sizeof(snap)); cg.snap = &snap; cg.nextSnap = NULL;
    CG_BuildSolidList();
    leanTest = 1; leanTraceErrors = 0;
    /* Timeline matrix: three presentation modes, both directions, four walls.
     * Independent scalar recurrence checks every sample through release. */
    for(mode = 0; mode < 3; ++mode) for(direction = -1; direction <= 1; direction += 2)
    for(fraction = 0; fraction < 4; ++fraction) {
        float expected = 0;
        memset(&cent, 0, sizeof(cent)); cent.currentState.clientNum = 2;
        cent.currentState.constantLight = direction;
        leanFraction = fraction / 3.0f;
        for(step = 0; step < 45; ++step) {
            int dt = step == 0 || step == 25 ? 1 : 16;
            float factor = mode == 2 ? (step < 25 && direction == 1 ? 1.9f : 2.35f) : 1.25f;
            VectorClear(torso); VectorClear(head); leanTraces = 0;
            cg.time = 1000 + step * 16;
            if(step < 25) {
                expected += direction * (dt / 200.0f) * 28;
                if(expected > 28) expected = 28;
                if(expected < -28) expected = -28;
                expected *= leanFraction;
            } else {
                float decay = (dt / 300.0f) * 28;
                cent.currentState.constantLight = 0;
                if(expected > 0) { expected -= decay; if(expected < 0) expected = 0; }
                else if(expected < 0) { expected += decay; if(expected > 0) expected = 0; }
            }
            CG_NitmodPredictLean(&cent, torso, head, 48, mode == 2 ? 256 : 0, mode == 1 ? 32 : 0);
            if(fabs(cent.nitmodLean.amount - expected) > .0001f || leanTraces != (step < 25) ||
               fabs(torso[ROLL] - (mode ? expected * factor : 0)) > .0001f ||
               fabs(head[ROLL] - (mode ? expected : 0)) > .0001f) ++errors;
        }
    }
    for(flags = 0; flags < 7; ++flags) for(direction = -1; direction <= 1; direction += 2) {
        memset(&cent, 0, sizeof(cent)); cent.currentState.clientNum = 2;
        cent.nitmodLean.amount = direction * 14.0f;
        cent.nitmodLean.direction = direction;
        cent.currentState.constantLight = direction;
        if(flags < 6) cent.currentState.eFlags = blocked[flags];
        else cent.currentState.weapon = WP_MORTAR_SET;
        VectorClear(torso); VectorClear(head); leanTraces = 0;
        CG_NitmodPredictLean(&cent, torso, head, 48, 256, 32);
        if(leanTraces || cent.nitmodLean.direction ||
           fabs(cent.nitmodLean.amount - direction * (14 - 28/300.0f)) > .0001f) ++errors;
    }
    memset(&cent, 0, sizeof(cent)); cent.currentState.clientNum = 2;
    cent.currentState.constantLight = cent.nitmodLean.direction = 1;
    cent.nitmodLean.time = INT_MIN; cg.time = INT_MAX; leanFraction = 1;
    VectorClear(torso); VectorClear(head);
    CG_NitmodPredictLean(&cent, torso, head, 48, 256, 32);
    if(cent.nitmodLean.amount != 28 || fabs(torso[ROLL] - 53.2f) > .0001f) ++errors;
    cg.time = INT_MIN;
    cent.nitmodLean.amount = 0;
    CG_NitmodPredictLean(&cent, NULL, NULL, 48, 256, 0);
    if(fabs(cent.nitmodLean.amount - .14f) > .0001f) ++errors;
    /* Actual config-reading adapter: original trace view origin, native bypass. */
    memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
    cent.nitmodLean.amount = 0; cent.nitmodLean.time = cg.time;
    VectorSet(cent.lerpOrigin, 10, 20, 30); cent.pe.headRefEnt.origin[2] = 91.9f;
    VectorSet(cent.lerpAngles, 0, 90, 0); snap.ps.clientNum = 2; snap.ps.viewheight = 48;
    CG_NitmodPlayerLean(&cent, torso, head);
    if(leanStart[0] != 10 || leanStart[1] != 20 || leanStart[2] != 78 || leanEnd[0] <= leanStart[0]) ++errors;
    snap.ps.clientNum = 0; CG_NitmodPlayerLean(&cent, torso, head);
    if(leanStart[2] != 121) ++errors;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\etmain"); leanTraces = 0;
    CG_NitmodPlayerLean(&cent, torso, head);
    if(leanTraces) ++errors;
    /* Exercise the real entity-effects path: -1 is a lean direction, not a
     * white 1020-unit light. General entities and native ET keep their lights. */
    leanTest = 2; cg.time = 1000;
    for(mode = 0; mode < 2; ++mode) for(flags = 0; flags < 2; ++flags)
    for(direction = -1; direction <= 1; ++direction) {
        memset(&cent, 0, sizeof(cent));
        cent.currentState.number = cent.currentState.clientNum = 2;
        cent.currentState.eType = flags ? ET_PLAYER : ET_GENERAL;
        cent.currentState.eFlags = EF_NODRAW; cent.currentState.constantLight = direction;
        SetTestConfig(CS_SERVERINFO, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        leanLights = 0; CG_AddCEntity(&cent);
        if(leanLights != (direction != 0 && !(mode && flags))) ++errors;
    }
    errors += leanTraceErrors; leanTest = 0;
    cg = savedCg; cgs = savedCgs;
    if(errors) fprintf(stderr, "%d player lean failures\n", errors);
    return errors;
}

static int CheckAmmoSelection(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    int errors = 0, mask, force, pistol, i, choice;
    const struct { int current, target; nitmodAmmoAction_t action; } special[] = {
        {WP_PLIERS, WP_PLIERS, NITMOD_AMMO_KEEP},
        {WP_SMOKE_BOMB, WP_LUGER, NITMOD_AMMO_FINISH},
        {WP_DYNAMITE, WP_PLIERS, NITMOD_AMMO_FINISH},
        {WP_LANDMINE, WP_PLIERS, NITMOD_AMMO_FINISH},
        {WP_TRIPMINE, WP_PLIERS, NITMOD_AMMO_FINISH},
        {WP_SATCHEL, WP_SATCHEL_DET, NITMOD_AMMO_SELECT},
        {WP_MORTAR_SET, WP_MORTAR, NITMOD_AMMO_SELECT},
        {WP_MOBILE_MG42_SET, WP_MOBILE_MG42, NITMOD_AMMO_SELECT},
        {WP_GPG40, WP_KAR98, NITMOD_AMMO_FINISH},
        {WP_M7, WP_CARBINE, NITMOD_AMMO_FINISH},
        {WP_SILENCED_COLT, WP_COLT, NITMOD_AMMO_FINISH}
    };
    savedCg = cg; savedCgs = cgs;
    memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
    cg.binocZoomTime = 1; /* Finish side effects are covered elsewhere; inspect dispatch selection. */
    for(mask = 0; mask < 4096; ++mask) for(force = 0; force < 2; ++force) for(pistol = 0; pistol < 2; ++pistol) {
        int expected = pistol ? WP_LUGER : WP_NONE;
        memset(&cg.predictedPlayerState, 0, sizeof(cg.predictedPlayerState));
        for(i = 0; i < MAX_WEAPS_IN_BANK_MP; ++i) if(mask & (1 << i)) {
            int weapon = weapBanksMultiPlayer[3][i];
            COM_BitSet(cg.predictedPlayerState.weapons, weapon);
            cg.predictedPlayerState.ammoclip[BG_FindClipForWeapon(weapon)] = 1;
        }
        if(pistol) {
            COM_BitSet(cg.predictedPlayerState.weapons, WP_LUGER);
            cg.predictedPlayerState.ammoclip[BG_FindClipForWeapon(WP_LUGER)] = 1;
        }
        for(i = 0; i < MAX_WEAPS_IN_BANK_MP; ++i) if((mask & (1 << i)) && (!force || weapBanksMultiPlayer[3][i] != WP_PANZERFAUST)) {
            expected = weapBanksMultiPlayer[3][i]; break;
        }
        cg.weaponSelect = WP_PANZERFAUST;
        if(CG_NitmodAmmoSelection(force, &choice) != NITMOD_AMMO_FINISH || choice != expected) ++errors;
        CG_OutOfAmmoChange(force);
        if(cg.weaponSelect != expected) ++errors;
    }
    for(i = 0; i < sizeof(special)/sizeof(special[0]); ++i) {
        memset(&cg.predictedPlayerState, 0, sizeof(cg.predictedPlayerState));
        COM_BitSet(cg.predictedPlayerState.weapons, special[i].target);
        cg.predictedPlayerState.ammo[BG_FindAmmoForWeapon(special[i].target)] = 1;
        cg.weaponSelect = special[i].current;
        if(CG_NitmodAmmoSelection(qtrue, &choice) != special[i].action || choice != special[i].target) ++errors;
        CG_OutOfAmmoChange(qtrue);
        if(cg.weaponSelect != special[i].target) ++errors;
    }
    memset(&cg.predictedPlayerState, 0, sizeof(cg.predictedPlayerState));
    cg.weaponSelect = WP_SATCHEL_DET; cg.predictedPlayerState.ammo[WP_SATCHEL_DET] = 1;
    if(CG_NitmodAmmoSelection(qtrue, &choice) != NITMOD_AMMO_KEEP) ++errors;
    cg.predictedPlayerState.ammo[WP_SATCHEL_DET] = 0;
    if(CG_NitmodAmmoSelection(qtrue, &choice) != NITMOD_AMMO_FINISH || choice != WP_NONE) ++errors;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod\\nitmod_csLayout\\et260");
    choice = -123;
    if(CG_NitmodAmmoSelection(qtrue, &choice) != NITMOD_AMMO_NATIVE || choice != -123) ++errors;
    cg = savedCg; cgs = savedCgs;
    if(errors) fprintf(stderr, "%d ammo selection failures\n", errors);
    return errors;
}

static int CheckCommandMapPresentation(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    centity_t savedEntity = cg_entities[3];
    snapshot_t snap;
    mapEntityData_t marker;
    mapScissor_t scissor;
    int mode, game, limbo, self, type, zoom, errors = 0, oldPrints = prints;
    int savedInterval = cg_redlimbotime.integer;
    const char *infos[] = {"\\gamename\\etmain", "\\gamename\\nitmod", "\\gamename\\nitmod\\nitmod_csLayout\\et260"};
    const float zooms[] = {1, 5.159f, 7.43f};
    savedCg = cg; savedCgs = cgs;
    memset(&snap, 0, sizeof(snap)); cg.snap = &snap;
    cgs.screenXScale = cgs.screenYScale = 1; cgs.screenXBias = 0;
    cgs.glconfig.vidWidth = 640; cgs.glconfig.vidHeight = 480;
    cgs.ccLayers = 0; cg.time = 1234;
    cg.mapcoordsMins[0] = cg.mapcoordsMins[1] = 0;
    cg.mapcoordsScale[0] = cg.mapcoordsScale[1] = 1.0f / 128;
    cg.predictedPlayerEntity.lerpOrigin[0] = cg.predictedPlayerEntity.lerpOrigin[1] = 100;
    cg.predictedPlayerEntity.voiceChatSpriteTime = 0;
    memset(&cg_entities[3], 0, sizeof(cg_entities[3])); cg_entities[3].currentValid = qtrue;
    cg_entities[3].lerpOrigin[0] = cg_entities[3].lerpOrigin[1] = 100;
    cg_entities[3].currentState.powerups = 1 << PW_OPS_DISGUISED;
    memset(&cgs.clientinfo[0], 0, sizeof(cgs.clientinfo[0]));
    memset(&cgs.clientinfo[3], 0, sizeof(cgs.clientinfo[3]));
    cgs.clientinfo[0].team = cgs.clientinfo[3].team = TEAM_AXIS;
    cgs.clientinfo[3].infoValid = qtrue;
    snap.ps.persistant[PERS_TEAM] = TEAM_AXIS; snap.ps.clientNum = 0;
    cg_redlimbotime.integer = 30000;
    memset(&scissor, 0, sizeof(scissor)); scissor.br[0] = scissor.br[1] = 1000;
    mapRenderTest = 1;
    for(mode = 0; mode < 3; ++mode) for(game = 6; game <= 8; ++game)
    for(limbo = 0; limbo < 2; ++limbo) for(self = 0; self < 2; ++self)
    for(type = ME_PLAYER; type <= ME_PLAYER_DISGUISED; ++type) for(zoom = 0; zoom < 3; ++zoom) {
        int hidden = mode == 1 && (game == 8 || (limbo && self));
        float half = 5 * zooms[zoom] / 5.159f;
        float x = 100 * zooms[zoom] + 10 - (mode == 1 ? half : 5);
        float y = 100 * zooms[zoom] + 20 - (mode == 1 ? half : 5);
        memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
        SetTestConfig(CS_SERVERINFO, infos[mode]); cgs.gametype = game;
        cg.clientNum = self ? 3 : 0; snap.ps.pm_flags = limbo ? PMF_LIMBO : 0;
        memset(&marker, 0, sizeof(marker)); marker.type = type; marker.data = 3;
        scissor.zoomFactor = zooms[zoom]; mapRenderPics = mapRenderArrows = 0;
        CG_DrawMapEntity(&marker, 10, 20, 128, 128, 0, &scissor, qfalse, &snap, 5);
        if(hidden) { if(mapRenderPics || mapRenderArrows) ++errors; continue; }
        if(type == ME_PLAYER_REVIVE) { x += 3; y += 3; }
        if(!mapRenderPics || mapRenderArrows != (type != ME_PLAYER_REVIVE) ||
           fabs(mapRenderRect[0] - x) > .001 || fabs(mapRenderRect[1] - y) > .001 ||
           fabs(mapRenderRect[2] - fabs(2 * half - (type == ME_PLAYER_REVIVE ? 3 : 0))) > .001) ++errors;
        if(type == ME_PLAYER_REVIVE && fabs(mapRenderAlpha - CG_MapReviveAlpha(cg.time, 30000)) > .00001) ++errors;
    }
    mapRenderTest = 0;
    if(errors) fprintf(stderr, "map draw failures: %d\n", errors);
    for(game = 0; game <= 30000; game += 125) {
        float phase = (30000 - game % 30000) / 30000.0f;
        float expected = .5f + .25f * (sin(sqrt(phase) * 50 * M_PI) + 1);
        if(fabs(CG_MapReviveAlpha(game, 30000) - expected) > .00001) ++errors;
    }
    if(CG_MapReviveAlpha(INT_MIN, 0) != .75f || CG_MapReviveAlpha(INT_MAX, -1) != .75f ||
       CG_MapReviveAlpha(INT_MIN, INT_MAX) < .5f || CG_MapReviveAlpha(INT_MAX, 1) > 1) ++errors;
    cgs.ccLayers = sizeof(cgs.ccLayerCeils) / sizeof(cgs.ccLayerCeils[0]);
    for(game = 0; game < cgs.ccLayers; ++game) cgs.ccLayerCeils[game] = game * 100;
    for(game = 0; game < cgs.ccLayers; ++game) if(CG_CurLayerForZ(game * 100) != game) ++errors;
    if(CG_CurLayerForZ(INT_MAX) != 0) ++errors;
    cgs.ccLayers = INT_MAX; if(CG_CurLayerForZ(1) != 0) ++errors;
    cg_redlimbotime.integer = savedInterval; cg_entities[3] = savedEntity;
    cg = savedCg; cgs = savedCgs; prints = oldPrints;
    if(errors) fprintf(stderr, "%d command map presentation failures\n", errors);
    return errors;
}

static int CheckCommandMapProtocol(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    const char *savedFields[21];
    const char *infos[] = {"\\gamename\\etmain", "\\gamename\\nitmod", "\\gamename\\nitmod\\nitmod_csLayout\\et260"};
    char typeText[16];
    snapshot_t snap;
    centity_t savedEntity = cg_entities[3];
    mapEntityData_t before, marker;
    int errors = 0, mode, type, layers, offset, cut, full, savedArgc = argcValue;
    vmCvar_t savedZoom = cg_automapZoom;
    savedCg = cg; savedCgs = cgs; memcpy(savedFields, fields, sizeof(fields));
    cg.mapcoordsMins[0] = cg.mapcoordsMins[1] = 0;
    cg.mapcoordsScale[0] = cg.mapcoordsScale[1] = 1.0f / 128;
    cg_automapZoom.value = 5.159f;
    for(mode = 0; mode < 3; ++mode) for(layers = 0; layers < 2; ++layers) for(type = 0; type < 10; ++type) {
        const mapEntityData_t *ent;
        int original = mode == 1;
        int oldErrors = errors;
        int coordinates = original || type <= ME_PLAYER_DISGUISED || type == ME_LANDMINE || type == ME_TANK || type == ME_TANK_DEAD;
        int yaw = type <= ME_PLAYER_DISGUISED || type == ME_LANDMINE;
        memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
        SetTestConfig(CS_SERVERINFO, infos[mode]); cgs.ccLayers = layers;
        fields[0] = "entnfo"; fields[1] = "1"; fields[2] = "1";
        Com_sprintf(typeText, sizeof(typeText), "%d", type); fields[3] = typeText; offset = 4;
        if(coordinates) {
            fields[offset++] = "-2"; fields[offset++] = "3";
            if(layers) fields[offset++] = "4";
        }
        if(yaw) fields[offset++] = "270";
        fields[offset++] = "1";
        /* A following player entry detects field-alignment errors in every type. */
        fields[offset++] = "0"; fields[offset++] = "5"; fields[offset++] = "6";
        if(layers) fields[offset++] = "7";
        fields[offset++] = "90"; fields[offset++] = "3";
        argcValue = full = offset;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        ent = CG_MapEntityAt(0);
        if(!ent || ent->type != type || ent->data != 1 || ent->team != TEAM_AXIS ||
           (coordinates && (ent->x != -256 || ent->y != 384 || (layers && ent->z != 512))) ||
           (yaw && ent->yaw != 270)) ++errors;
        ent = CG_MapEntityAt(1);
        if(!ent || ent->type != ME_PLAYER || ent->data != 3 || ent->team != TEAM_ALLIES ||
           ent->x != 640 || ent->y != 768 || ent->yaw != 90 || CG_MapEntityAt(2) || CG_MapEntityAt(-1)) ++errors;
        if(original && ent) {
            before = *ent;
            for(cut = 0; cut < full; ++cut) {
                argcValue = cut;
                if(CG_ParseOriginalMapEntityInfo() || memcmp(CG_MapEntityAt(1), &before, sizeof(before))) ++errors;
            }
            argcValue = full + 1; fields[full] = "extra";
            if(CG_ParseOriginalMapEntityInfo()) ++errors;
            argcValue = full; fields[4] = "16777216";
            if(CG_ParseOriginalMapEntityInfo()) ++errors;
            fields[4] = "000000000000000000000000000000000000000001";
            if(CG_ParseOriginalMapEntityInfo()) ++errors;
            fields[4] = "-2"; fields[full - 1] = "64";
            if(CG_ParseOriginalMapEntityInfo()) ++errors;
            fields[full - 1] = "3";
            fields[4] = "-2"; fields[1] = "2147483647";
            if(CG_ParseOriginalMapEntityInfo()) ++errors;
            fields[1] = "1junk";
            if(CG_ParseOriginalMapEntityInfo()) ++errors;
        }
        if(errors != oldErrors) fprintf(stderr, "map mode=%d layers=%d type=%d failures=%d\n", mode, layers, type, errors-oldErrors);
    }
    memset(&snap, 0, sizeof(snap)); cg.snap = &snap;
    memset(&marker, 0, sizeof(marker)); marker.data = 3;
    cgs.clientinfo[3].infoValid = qtrue;
    memset(&cg_entities[3], 0, sizeof(cg_entities[3]));
    for(type = 0; type < 2; ++type) for(offset = 510; offset <= 514; ++offset) {
        cg_entities[3].currentState.powerups = type ? (1 << PW_OPS_DISGUISED) : 0;
        cg_entities[3].lerpOrigin[0] = offset;
        if(CG_DisguiseMapCheck(&marker) != (type && offset >= 512)) ++errors;
    }
    marker.data = MAX_CLIENTS; if(CG_DisguiseMapCheck(&marker)) ++errors;
    marker.data = -1; if(CG_DisguiseMapCheck(&marker) || CG_DisguiseMapCheck(NULL)) ++errors;
    {
        mapScissor_t scissor;
        int team, valid, distance;
        memset(&scissor, 0, sizeof(scissor)); scissor.zoomFactor = 1;
        scissor.tl[0] = scissor.tl[1] = 100000;
        scissor.br[0] = scissor.br[1] = 200000; /* Cull after position update, before rendering. */
        cgs.ccLayers = 0; cg.clientNum = 0; snap.ps.persistant[PERS_TEAM] = TEAM_AXIS;
        cgs.clientinfo[3].cls = PC_SOLDIER;
        for(mode = 0; mode < 3; ++mode) for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team)
        for(valid = 0; valid < 2; ++valid) for(distance = 511; distance <= 512; ++distance) {
            int refresh = mode == 1 ? (team == TEAM_AXIS || distance >= 512) : (team == TEAM_AXIS && valid);
            memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
            SetTestConfig(CS_SERVERINFO, infos[mode]);
            memset(&marker, 0, sizeof(marker)); marker.type = ME_PLAYER_DISGUISED; marker.data = 3;
            marker.automapTransformed[0] = marker.automapTransformed[1] = -99;
            cgs.clientinfo[3].team = team; cg_entities[3].currentValid = valid;
            cg_entities[3].currentState.powerups = 1 << PW_OPS_DISGUISED;
            cg_entities[3].lerpOrigin[0] = distance; cg_entities[3].lerpAngles[YAW] = 45;
            CG_DrawMapEntity(&marker, 0, 0, 128, 128, 0, &scissor, qfalse, &snap, 5);
            if(marker.automapTransformed[0] != (refresh ? distance : -99) || marker.yaw != (refresh ? 45 : 0)) ++errors;
        }
    }
    fields[0] = "entnfo"; fields[1] = fields[2] = "0"; argcValue = 3;
    if(!CG_ParseOriginalMapEntityInfo() || CG_MapEntityAt(0)) ++errors;
    cg_entities[3] = savedEntity;
    memcpy(fields, savedFields, sizeof(fields)); argcValue = savedArgc;
    cg = savedCg; cgs = savedCgs;
    cg_automapZoom = savedZoom;
    if(errors) fprintf(stderr, "%d command map protocol failures\n", errors);
    return errors;
}

static int CheckCorpseAnimation(void) {
    extern void CG_RunLerpFrameRate(clientInfo_t *, lerpFrame_t *, int, centity_t *, int);
    static cgs_t savedCgs;
    static animModelInfo_t model;
    bg_character_t character;
    animation_t anim, replacement;
    centity_t cent;
    lerpFrame_t frame, before;
    int savedTime = cg.time, savedSpeed = cg_animSpeed.integer;
    int t, loop, errors = 0;
    savedCgs = cgs;
    memset(&model, 0, sizeof(model)); memset(&character, 0, sizeof(character));
    memset(&anim, 0, sizeof(anim)); memset(&cent, 0, sizeof(cent));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
    character.animModelInfo = &model; cgs.gameCharacters[0] = &character;
    model.numAnimations = 1; model.animations[0] = &anim;
    anim.firstFrame = 100; anim.numFrames = 10; anim.frameLerp = 100;
    anim.duration = 1000; anim.mdxFile = 37;
    cent.currentState.eType = ET_CORPSE; cent.currentState.effect1Time = 2000;
    for(loop = 0; loop <= 10; ++loop) for(t = 0; t <= 2200; t += 25) {
        int expectedOld, expectedFrame, expectedTime;
        float expectedBack;
        memset(&frame, 0, sizeof(frame)); anim.loopFrames = loop; cg.time = t;
        if(!CG_NitmodCorpseAnimation(&cent, &frame, 0)) ++errors;
        /* Fresh late-join timelines with hand-derived 100ms frame cadence. */
        if(t > 2000) { expectedOld = expectedFrame = 109; expectedTime = t-1; expectedBack = 0; }
        else {
            int remaining = 2000-t, offset;
            if(remaining > 1000) remaining = 1000;
            expectedOld = 100 + (1000-remaining)/100;
            if(expectedOld > 109) expectedOld = 109;
            offset = (1099-remaining)/100;
            expectedTime = t+99;
            if(offset >= 10) {
                if(loop) offset = 10-loop+(offset-10)%loop;
                else { offset = 9; expectedTime = t; }
            }
            expectedFrame = 100+offset;
            expectedBack = expectedTime == t ? 0 : .99f;
        }
        if(frame.oldFrame != expectedOld || frame.frame != expectedFrame ||
           frame.frameTime != expectedTime || fabs(frame.backlerp-expectedBack) > .00001 ||
           frame.frameModel != 37 || frame.oldFrameModel != 37) ++errors;
    }
    anim.loopFrames = 0; memset(&frame, 0, sizeof(frame)); cg.time = 1000;
    cg_animSpeed.integer = 0;
    CG_RunLerpFrameRate(NULL, &frame, 0, &cent, 0);
    if(frame.frame != 100 || fabs(frame.backlerp-.99f) > .00001) ++errors;
    cg.time = 1050; CG_RunLerpFrameRate(NULL, &frame, 0, &cent, 0);
    if(frame.frame != 100 || frame.oldFrame != 100 || fabs(frame.backlerp-.49f) > .00001) ++errors;
    cg.time = 1100; CG_RunLerpFrameRate(NULL, &frame, 0, &cent, 0);
    if(frame.frame != 101 || frame.oldFrame != 100 || fabs(frame.backlerp-.99f) > .00001) ++errors;
    cg.time = 2001; CG_RunLerpFrameRate(NULL, &frame, 0, &cent, 0);
    if(frame.frame != 109 || frame.oldFrame != 109 || frame.backlerp) ++errors;
    /* A newly resolved animation asset also invalidates a cached pointer. */
    replacement = anim; replacement.firstFrame = 200; model.animations[0] = &replacement;
    CG_NitmodCorpseAnimation(&cent, &frame, ANIM_TOGGLEBIT);
    if(frame.frame != 209 || frame.animation != &replacement || frame.animationNumber != ANIM_TOGGLEBIT) ++errors;
    model.animations[0] = &anim;
    for(t = 0; t < 8; ++t) {
        animation_t savedAnim = anim;
        memset(&frame, 0, sizeof(frame));
        if(t == 0) anim.frameLerp = 0;
        if(t == 1) anim.frameLerp = -1;
        if(t == 2) anim.numFrames = 0;
        if(t == 3) anim.loopFrames = 11;
        if(t == 4) anim.duration = -1;
        if(t == 5) anim.firstFrame = INT_MAX;
        if(t == 6) model.numAnimations = MAX_MODEL_ANIMATIONS + 1;
        if(t == 7) model.animations[0] = NULL;
        if(!CG_NitmodCorpseAnimation(&cent, &frame, 0) || frame.animation || frame.frame || frame.backlerp) ++errors;
        anim = savedAnim; model.numAnimations = 1; model.animations[0] = &anim;
    }
    memset(&frame, 0, sizeof(frame)); cg.time = INT_MIN; cent.currentState.effect1Time = INT_MAX;
    CG_NitmodCorpseAnimation(&cent, &frame, 0);
    if(frame.frame < 100 || frame.frame > 109 || !(frame.backlerp >= 0 && frame.backlerp <= 1)) ++errors;
    cent.currentState.onFireStart = MAX_CHARACTERS;
    if(CG_CharacterForClientinfo(NULL, &cent)) ++errors;
    CG_NitmodCorpseAnimation(&cent, &frame, 0); if(frame.animation) ++errors;
    cent.currentState.onFireStart = -1; cent.currentState.modelindex = 9;
    if(CG_CharacterForClientinfo(NULL, &cent)) ++errors;
    cent.currentState.modelindex = TEAM_AXIS; cent.currentState.modelindex2 = NUM_PLAYER_CLASSES;
    if(CG_CharacterForClientinfo(NULL, &cent)) ++errors;
    before = frame; SetTestConfig(CS_SERVERINFO, "\\gamename\\etmain");
    if(CG_NitmodCorpseAnimation(&cent, &frame, 0) || memcmp(&frame, &before, sizeof(frame))) ++errors;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod"); cent.currentState.eType = ET_PLAYER;
    if(CG_NitmodCorpseAnimation(&cent, &frame, 0) || memcmp(&frame, &before, sizeof(frame))) ++errors;
    cgs = savedCgs; cg.time = savedTime; cg_animSpeed.integer = savedSpeed;
    if(errors) fprintf(stderr, "%d corpse-animation failures\n", errors);
    return errors;
}
static int autoexecTest, autoexecPresent, autoexecLoads, autoexecFrees, autoexecSends, autoexecZooms, autoexecFogs;
static int autoexecMapMode = -1;
static char autoexecPaths[4][MAX_QPATH], autoexecCommands[4][MAX_QPATH + 8];
static int CheckAutoexec(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    snapshot_t snap;
    const char *infos[] = {"\\gamename\\etmain", "\\gamename\\nitmod", "\\gamename\\nitmod\\nitmod_csLayout\\et260"};
    const char *classes[] = {"Soldier", "Medic", "Engineer", "Fieldops", "Covertops"};
    const char *teams[] = {"free", "axis", "allies", "spectator"};
    int mode, demo, revive, team, cls, present, errors = 0;
    savedCg = cg; savedCgs = cgs;
    memset(&snap, 0, sizeof(snap)); cg.snap = &snap; cg.clientNum = 3;
    memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
    autoexecTest = 1;
    for(mode = 0; mode < 3; ++mode) for(demo = 0; demo < 2; ++demo)
    for(revive = 0; revive < 2; ++revive) for(team = -1; team <= 4; ++team)
    for(cls = -1; cls <= NUM_PLAYER_CLASSES; ++cls) for(present = 0; present < 2; ++present) {
        int active = mode == 1 && !demo && !revive && team >= 0 && team <= 3;
        int classConfig = active && (team == TEAM_AXIS || team == TEAM_ALLIES) && cls >= 0 && cls < NUM_PLAYER_CLASSES;
        int probes = active + classConfig, i;
        char expected[MAX_QPATH + 8];
        memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
        SetTestConfig(CS_SERVERINFO, infos[mode]); cg.demoPlayback = demo;
        cgs.clientinfo[3].team = team; cgs.clientinfo[3].cls = cls;
        CG_NitmodResetAutoexec(); autoexecPresent = present;
        autoexecLoads = autoexecFrees = autoexecSends = 0;
        CG_NitmodRespawnAutoexec(revive);
        if(autoexecLoads != probes || autoexecFrees != probes * present || autoexecSends != probes * present) ++errors;
        for(i = 0; i < probes; ++i) {
            const char *stem = classConfig && i == 0 ? classes[cls] : teams[team];
            Com_sprintf(expected, sizeof(expected), "autoexec_%s.cfg", stem);
            if(strcmp(autoexecPaths[i], expected)) ++errors;
            Com_sprintf(expected, sizeof(expected), "exec autoexec_%s.cfg\n", stem);
            if(present && strcmp(autoexecCommands[i], expected)) ++errors;
        }
        /* Missing files are not probed on every subsequent same-class spawn. */
        CG_NitmodRespawnAutoexec(revive);
        if(autoexecLoads != probes || autoexecSends != probes * present) ++errors;
    }
    SetTestConfig(CS_SERVERINFO, infos[1]); cg.demoPlayback = qfalse;
    cgs.clientinfo[3].team = TEAM_AXIS; cgs.clientinfo[3].cls = PC_MEDIC;
    snap.ps.weapon = WP_KNIFE; CG_NitmodResetAutoexec(); autoexecPresent = 1;
    autoexecLoads = autoexecFrees = autoexecSends = autoexecZooms = autoexecFogs = 0;
    CG_Respawn(qfalse);
    if(autoexecLoads != 2 || autoexecSends != 2 || autoexecZooms != 1 || autoexecFogs != 1) ++errors;
    /* A revive must not consume a pending class/team change. */
    cgs.clientinfo[3].team = TEAM_ALLIES; cgs.clientinfo[3].cls = PC_ENGINEER;
    autoexecLoads = autoexecFrees = autoexecSends = 0;
    CG_Respawn(qtrue); if(autoexecLoads || autoexecSends) ++errors;
    CG_Respawn(qfalse);
    if(autoexecSends != 2 || strcmp(autoexecCommands[0], "exec autoexec_Engineer.cfg\n") ||
       strcmp(autoexecCommands[1], "exec autoexec_allies.cfg\n")) ++errors;
    autoexecLoads = autoexecFrees = autoexecSends = 0;
    cgs.clientinfo[3].team = TEAM_SPECTATOR; CG_NitmodRespawnAutoexec(qfalse);
    cgs.clientinfo[3].team = TEAM_AXIS; CG_NitmodRespawnAutoexec(qfalse);
    if(autoexecSends != 2 || strcmp(autoexecCommands[0], "exec autoexec_spectator.cfg\n") ||
       strcmp(autoexecCommands[1], "exec autoexec_axis.cfg\n")) ++errors;
    CG_NitmodResetAutoexec(); autoexecLoads = autoexecFrees = autoexecSends = 0;
    cg.clientNum = -1; CG_NitmodRespawnAutoexec(qfalse);
    cg.clientNum = MAX_CLIENTS; CG_NitmodRespawnAutoexec(qfalse);
    cg.clientNum = 3; cg.snap = NULL; CG_NitmodRespawnAutoexec(qfalse);
    if(autoexecLoads || autoexecSends) ++errors;
    {
        const char *maps[] = {"oasis", "goldrush-ga", "mml_minastirith_fp3", "evil;quit", "../oasis", "", "Oasis.v2"};
        int map;
        for(mode = 0; mode < 3; ++mode) for(demo = 0; demo < 2; ++demo)
        for(map = 0; map < 7; ++map) for(present = 0; present < 4; ++present) {
            int valid = map < 3 || map == 6;
            int active = mode == 1;
            int foundMap = valid && (present & 1);
            char expected[MAX_QPATH + 8];
            SetTestConfig(CS_SERVERINFO, infos[mode]); cg.demoPlayback = demo;
            Q_strncpyz(cgs.rawmapname, maps[map], sizeof(cgs.rawmapname));
            autoexecMapMode = present; autoexecLoads = autoexecFrees = autoexecSends = 0;
            CG_NitmodMapAutoexec();
            if(autoexecLoads != (active ? valid + !foundMap : 0) ||
               autoexecSends != (active && (foundMap || (present & 2))) || autoexecFrees != autoexecSends) ++errors;
            if(active && valid) {
                Com_sprintf(expected, sizeof(expected), "autoexec_%s.cfg", maps[map]);
                if(strcmp(autoexecPaths[0], expected)) ++errors;
            }
            if(active && !foundMap && strcmp(autoexecPaths[autoexecLoads-1], "autoexec_default.cfg")) ++errors;
            if(autoexecSends) {
                Com_sprintf(expected, sizeof(expected), "exec autoexec_%s.cfg\n", foundMap ? maps[map] : "default");
                if(strcmp(autoexecCommands[0], expected)) ++errors;
            }
        }
        SetTestConfig(CS_SERVERINFO, infos[1]); autoexecMapMode = 3;
        memset(cgs.rawmapname, 'x', sizeof(cgs.rawmapname));
        autoexecLoads = autoexecFrees = autoexecSends = 0;
        CG_NitmodMapAutoexec();
        if(autoexecLoads != 1 || autoexecSends != 1 || strcmp(autoexecPaths[0], "autoexec_default.cfg")) ++errors;
    }
    autoexecMapMode = -1;
    autoexecTest = 0; CG_NitmodResetAutoexec(); cg = savedCg; cgs = savedCgs;
    if(errors) fprintf(stderr, "%d autoexec failures\n", errors);
    return errors;
}
static int debugTest, debugLines, debugTags, debugMissingTag, debugRegistrations, debugMissingShader;
static refEntity_t debugCaptured[51];
static int CheckPlayerDebug(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    centity_t cent, before;
    refEntity_t body;
    nitmodDebugGeometry_t geometry;
    int savedFlags = cg_drawHitbox.integer, savedDemoFlag = demo_wallHack.integer;
    int mode, stance, flags, errors = 0;
    savedCg = cg; savedCgs = cgs;
    memset(&cent, 0, sizeof(cent)); memset(&body, 0, sizeof(body));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
    VectorSet(cent.lerpOrigin, 10, 20, 30);
    cent.currentState.solid = 16 | (24 << 8) | (80 << 16);
    VectorSet(cg.predictedPlayerState.mins, -16, -16, -24);
    VectorSet(cg.predictedPlayerState.maxs, 16, 16, 48);
    cg.predictedPlayerState.standViewHeight = 40;
    cg.predictedPlayerState.crouchMaxZ = 24; cg.pmext.proneLegsOffset = 3;
    body.hModel = 1; VectorSet(body.origin, 100, 200, 300); AxisClear(body.axis);
    cgs.media.railCoreShader = 987; debugTest = 1; before = cent;
    for(mode = 0; mode < 2; ++mode) for(stance = 0; stance < 3; ++stance)
    for(flags = 0; flags < 16; ++flags) {
        int boxes = ((flags & 4) ? 1 : 0) + ((flags & 1) ? (stance == 2 ? 3 : 1) : 0);
        int i, j;
        SetTestConfig(CS_SERVERINFO, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        cg_drawHitbox.integer = flags;
        cg.predictedPlayerState.pm_flags = stance == 1 ? PMF_DUCKED : 0;
        cg.predictedPlayerState.eFlags = stance == 2 ? EF_PRONE : 0;
        CG_NitmodDebugGeometry(&cent, &cg.predictedPlayerState, &cg.pmext, flags, &geometry);
        if(geometry.count != boxes) ++errors;
        if(flags & 4) {
            if(geometry.boxes[0].mins[0] != -6 || geometry.boxes[0].mins[2] != 6 ||
               geometry.boxes[0].maxs[1] != 36 || geometry.boxes[0].maxs[2] != 78) ++errors;
        }
        if(flags & 1) {
            int index = (flags & 4) ? 1 : 0;
            if(geometry.boxes[index].maxs[2] != (stance == 0 ? 78 : stance == 1 ? 54 : 22)) ++errors;
            if(stance == 2 && (fabs(geometry.boxes[index+1].mins[0] - (-35.5f)) > .1f ||
               geometry.boxes[index+1].mins[2] != 9 || geometry.boxes[index+2].maxs[2] != 20)) ++errors;
        }
        debugLines = debugTags = 0;
        CG_NitmodDrawPlayerDebug(&cent, &body);
        if(debugLines != (mode ? 12 * boxes + ((flags & 2) ? 3 : 0) : 0) ||
           debugTags != (mode && (flags & 2) ? 1 : 0)) ++errors;
        for(i = 0; mode && i < boxes * 12; ++i) {
            int changes = 0;
            for(j = 0; j < 3; ++j) {
                float lo = geometry.boxes[i/12].mins[j], hi = geometry.boxes[i/12].maxs[j];
                float start = debugCaptured[i].origin[j], end = debugCaptured[i].oldorigin[j];
                if((start != lo && start != hi) || (end != lo && end != hi)) ++errors;
                if(start != end) ++changes;
            }
            if(changes != 1) ++errors;
        }
        for(i = 0; mode && (flags & 2) && i < 3; ++i) for(j = 0; j < 3; ++j) {
            float start = (j + 1) * 101.0f;
            if(debugCaptured[boxes*12+i].origin[j] != start ||
               debugCaptured[boxes*12+i].oldorigin[j] != start + (i == j ? 32 : 0)) ++errors;
        }
        if(memcmp(&cent, &before, sizeof(cent))) ++errors;
    }
    cg_drawHitbox.integer = 2; debugMissingTag = 1; debugLines = debugTags = 0;
    CG_NitmodDrawPlayerDebug(&cent, &body);
    if(debugLines || debugTags != 1) ++errors;
    debugMissingTag = 0; body.hModel = 0; debugTags = 0;
    CG_NitmodDrawPlayerDebug(&cent, &body); if(debugLines || debugTags) ++errors;
    cent.currentState.solid = SOLID_BMODEL;
    CG_NitmodDebugGeometry(&cent, NULL, NULL, 4, &geometry); if(geometry.count) ++errors;
    cent.currentState.solid = 0;
    CG_NitmodDebugGeometry(&cent, NULL, NULL, 4, &geometry); if(geometry.count) ++errors;
    cent.lerpOrigin[0] = HUGE_VAL;
    CG_NitmodDebugGeometry(&cent, &cg.predictedPlayerState, &cg.pmext, 7, &geometry);
    if(geometry.count) ++errors;
    for(mode = 0; mode < 2; ++mode) {
        int demo, enabled, team;
        SetTestConfig(CS_SERVERINFO, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        debugRegistrations = 0; CG_NitmodRegisterDebugMedia();
        if(debugRegistrations != (mode ? 2 : 0)) ++errors;
        for(demo = 0; demo < 2; ++demo) for(enabled = -1; enabled <= 1; ++enabled)
        for(team = TEAM_FREE; team <= TEAM_SPECTATOR; ++team) {
            cg.demoPlayback = demo; demo_wallHack.integer = enabled;
            if(CG_NitmodDemoPlayerShader(team) !=
               (mode && demo && enabled ? (team == TEAM_AXIS ? 801 : 802) : 0)) ++errors;
        }
    }
    debugMissingShader = 1; CG_NitmodRegisterDebugMedia();
    if(CG_NitmodDemoPlayerShader(TEAM_AXIS) || CG_NitmodDemoPlayerShader(TEAM_ALLIES)) ++errors;
    debugMissingShader = 0;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\etmain"); CG_NitmodRegisterDebugMedia();
    debugTest = 0; cg_drawHitbox.integer = savedFlags; demo_wallHack.integer = savedDemoFlag;
    cg = savedCg; cgs = savedCgs;
    if(errors) fprintf(stderr, "%d player-debug failures\n", errors);
    return errors;
}
static int CheckRoundTimer(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    snapshot_t snap;
    int savedRed = cg_redlimbotime.integer, savedBlue = cg_bluelimbotime.integer;
    int savedDraw = cg_drawReinforcementTime.integer, savedSet = cg_spawnTimer_set.integer;
    int savedPeriod = cg_spawnTimer_period.integer;
    int game, team, follow, playing, limited, elapsed, errors = 0;
    char text[128], expected[128], prefix[32]; float alpha;
    savedCg = cg; savedCgs = cgs; memset(&snap, 0, sizeof(snap));
    cg.snap = &snap; cg.clientNum = 0; snap.ps.clientNum = 1;
    cgs.clientinfo[1].team = TEAM_AXIS; cgs.levelStartTime = 0;
    cgs.aReinfOffset[TEAM_AXIS] = 0; cgs.aReinfOffset[TEAM_ALLIES] = 0;
    cg_redlimbotime.integer = 30000; cg_bluelimbotime.integer = 20000;
    cg_drawReinforcementTime.integer = 1; cg_spawnTimer_set.integer = -1;
    cg_spawnTimer_period.integer = 0;
    for(game = 2; game <= 8; ++game) for(team = TEAM_AXIS; team <= TEAM_SPECTATOR; ++team)
    for(follow = 0; follow < 2; ++follow) for(playing = 0; playing < 2; ++playing)
    for(limited = 0; limited < 2; ++limited) for(elapsed = 0; elapsed < 2; ++elapsed) {
        int show = game != GT_WOLF_LMS && (team != TEAM_SPECTATOR || follow);
        int special = game == 7 || game == 8;
        cgs.gametype = game; cgs.clientinfo[0].team = team;
        snap.ps.pm_flags = follow ? PMF_FOLLOW : 0;
        cgs.gamestate = playing ? GS_PLAYING : GS_WARMUP;
        cgs.timelimit = limited ? 1 : 0; cg.time = elapsed ? 61000 : 1000;
        Q_strncpyz(prefix, show ? (limited ? "^F30 " : "^F30") : "", sizeof(prefix));
        if(!playing) Q_strncpyz(expected, "^7WARMUP", sizeof(expected));
        else if(special) Com_sprintf(expected, sizeof(expected), " %s", prefix);
        else if(!limited) Q_strncpyz(expected, prefix, sizeof(expected));
        else if(elapsed) Q_strncpyz(expected, "^N0:00", sizeof(expected));
        else Com_sprintf(expected, sizeof(expected), "%s^70:59", prefix);
        CG_NitmodRoundTimerText(text, sizeof(text), &alpha);
        if(strcmp(text, expected) || fabs(alpha - (!playing || (!special && limited && elapsed) ?
           fabs(sin(cg.time * 0.002)) : 1.0)) > .00001) ++errors;
    }
    cgs.gametype = 7; cgs.gamestate = GS_PLAYING; cgs.timelimit = 1; cg.time = 1000;
    cg_spawnTimer_set.integer = 60; cg_spawnTimer_period.integer = 30;
    CG_NitmodRoundTimerText(text, sizeof(text), NULL);
    if(strcmp(text, "^129  ^F30 ")) ++errors;
    cg_spawnTimer_set.integer = -1;
    for(team = -1; team <= TEAM_SPECTATOR + 1; ++team) {
        cgs.clientinfo[1].team = team;
        for(elapsed = -1; elapsed <= 1; ++elapsed) {
            cg_redlimbotime.integer = cg_bluelimbotime.integer = elapsed * 10000;
            if(CG_CalculateReinfTime(qfalse) !=
               (elapsed > 0 && (team == TEAM_AXIS || team == TEAM_ALLIES) ? 10 : 0)) ++errors;
        }
    }
    snap.ps.clientNum = MAX_CLIENTS; if(CG_CalculateReinfTime(qfalse)) ++errors;
    snap.ps.clientNum = -1; if(CG_CalculateReinfTime(qfalse)) ++errors;
    cg.snap = NULL; if(CG_CalculateReinfTime(qfalse)) ++errors;
    cg.clientNum = -1; if(CG_CalculateReinfTime(qtrue)) ++errors;
    cg.clientNum = 0; cgs.clientinfo[0].team = TEAM_SPECTATOR;
    cg_redlimbotime.integer = 30000; cg_bluelimbotime.integer = 20000;
    cgs.ccSelectedTeam = 0; if(CG_CalculateReinfTime(qtrue) != 30) ++errors;
    cgs.ccSelectedTeam = 1; if(CG_CalculateReinfTime(qtrue) != 20) ++errors;
    cgs.clientinfo[1].team = TEAM_AXIS; snap.ps.clientNum = 1; cg.snap = &snap;
    cg.time = INT_MAX; cgs.levelStartTime = INT_MIN; cgs.aReinfOffset[TEAM_AXIS] = INT_MAX;
    if(CG_CalculateReinfTime(qfalse) != (int)(1 + (float)(30000 - fmod(6442450942.0,30000))*.001f)) ++errors;
    cgs.timelimit = HUGE_VAL; CG_NitmodRoundTimerText(text, sizeof(text), &alpha);
    if(alpha < 0 || alpha > 1) ++errors;
    cg = savedCg; cgs = savedCgs; cg_redlimbotime.integer = savedRed; cg_bluelimbotime.integer = savedBlue;
    cg_drawReinforcementTime.integer = savedDraw; cg_spawnTimer_set.integer = savedSet;
    cg_spawnTimer_period.integer = savedPeriod;
    if(errors) fprintf(stderr, "%d round-timer failures\n", errors);
    return errors;
}
static int cvarScanTest, cvarScanReads, cvarScanSends;
static const char *cvarScanValue;
static char cvarScanReply[1024];
static int CheckCvarScan(void) {
    const char *values[] = {"", "0", "2", "-1.5", "O", "two words", "bad\"quote", "bad\\slash", "bad\rreturn", "bad\nline"};
    const char *requests[] = {"0", "19", "2147483647", "-1", "2147483648", "1x", ""};
    const char *names[] = {"r_primitives", "cg_pmColor", "g_soldierChargeTime", "", "x y", "x;quit", "x\"y", "x\\y"};
    const char *savedFields[3];
    char expected[1024], longValue[300];
    int savedArgc = argcValue, savedSequence = cgs.serverCommandSequence;
    int demo, v, r, n, errors = 0;
    qboolean savedDemo = cg.demoPlayback;
    memcpy(savedFields, fields, sizeof(savedFields));
    cvarScanTest = 1; argcValue = 3; fields[0] = "cvs";
    for(demo = 0; demo < 2; ++demo) for(v = 0; v < 10; ++v)
    for(r = 0; r < 7; ++r) for(n = 0; n < 8; ++n) {
        int reads = !demo && r < 3 && n < 3;
        int sends = reads && v < 6;
        cg.demoPlayback = demo; fields[1] = requests[r]; fields[2] = names[n];
        cvarScanValue = values[v]; cvarScanReads = cvarScanSends = 0;
        if(!NITMOD_DisplayCommand("cvs")) ++errors;
        Com_sprintf(expected, sizeof(expected), "cvs %s %s \"%s\"\n", requests[r], names[n], values[v]);
        if(cvarScanReads != reads || cvarScanSends != sends ||
           (sends && strcmp(cvarScanReply, expected))) ++errors;
    }
    /* Original reads a 256-byte value. Exercise that boundary through the
     * actual command dispatcher, not only the leaf handler. */
    memset(longValue, 'a', sizeof(longValue)); longValue[299] = 0;
    cg.demoPlayback = qfalse; fields[1] = "7"; fields[2] = "r_primitives";
    cvarScanValue = longValue; cvarScanReads = cvarScanSends = 0;
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    longValue[255] = 0;
    Com_sprintf(expected, sizeof(expected), "cvs 7 r_primitives \"%s\"\n", longValue);
    if(cvarScanReads != 1 || cvarScanSends != 1 || strcmp(cvarScanReply, expected)) ++errors;
    for(n = 0; n < 5; ++n) if(n != 3) {
        argcValue = n; cvarScanReads = cvarScanSends = 0;
        if(!NITMOD_DisplayCommand("cvs") || cvarScanReads || cvarScanSends) ++errors;
    }
    cvarScanTest = 0; argcValue = savedArgc; cg.demoPlayback = savedDemo;
    cgs.serverCommandSequence = savedSequence; memcpy(fields, savedFields, sizeof(savedFields));
    if(errors) fprintf(stderr, "%d cvar-scan failures\n", errors);
    return errors;
}
static int sessionTest, sessionSends;
static const char *sessionGame;
static char sessionCommands[8][16];
static int CheckOriginalSession(void) {
    static gameState_t savedGame;
    const char *infos[] = {"\\gamename\\etmain", "\\gamename\\nitmod", "\\gamename\\nitmod\\nitmod_csLayout\\et260"};
    const char *games[] = {"nitmod", "NITMOD", "etmain", ""};
    qboolean savedDemo = cg.demoPlayback;
    int savedArgc = argcValue, savedPrints = prints, mode, demo, folder, args, errors = 0;
    int savedSequence = cgs.serverCommandSequence;
    const char *savedCommand = fields[0];
    savedGame = cgs.gameState;
    memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
    sessionTest = keyTest = 1; keyLength = 44;
    for(mode = 0; mode < 3; ++mode) for(demo = 0; demo < 2; ++demo) for(folder = 0; folder < 4; ++folder) {
        int active = mode == 1 && !demo && folder < 2;
        SetTestConfig(CS_SERVERINFO, infos[mode]); cg.demoPlayback = demo;
        sessionGame = games[folder]; sessionSends = keyReads = keyCloses = 0;
        NITMOD_BeginOriginalSession();
        if(sessionSends != active || keyReads != active || keyCloses != active ||
           (active && strcmp(sessionCommands[0], "imhere"))) ++errors;
        for(args = 0; args < 3; ++args) {
            argcValue = args; sessionSends = 0;
            if(NITMOD_OriginalSessionCommand("handshake") != (mode == 1)) ++errors;
            if(sessionSends != (mode == 1 && !demo && args == 1 ? 3 : 0)) ++errors;
            if(sessionSends && (strcmp(sessionCommands[0],"rhs") ||
               strcmp(sessionCommands[1],"handshake") || strcmp(sessionCommands[2],"getdata"))) ++errors;
        }
    }
    SetTestConfig(CS_SERVERINFO, infos[1]); cg.demoPlayback = qfalse; argcValue = 1;
    sessionGame = "nitmod"; sessionSends = 0; fields[0] = "handshake";
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(sessionSends != 3 || strcmp(sessionCommands[0],"rhs") || strcmp(sessionCommands[2],"getdata")) ++errors;
    /* Repeated server requests deliberately re-run the reset/ack/data order. */
    sessionSends = 0; CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(sessionSends != 3) ++errors;
    sessionSends = 0;
    if(NITMOD_OriginalSessionCommand(NULL) || NITMOD_OriginalSessionCommand("Handshake") ||
       NITMOD_OriginalSessionCommand("handshake extra") || sessionSends) ++errors;
    sessionTest = keyTest = 0; cgs.gameState = savedGame; cg.demoPlayback = savedDemo;
    argcValue = savedArgc; fields[0] = savedCommand; prints = savedPrints;
    cgs.serverCommandSequence = savedSequence;
    if(errors) fprintf(stderr,"%d original-session failures\n",errors);
    return errors;
}
static int keyGenerationTest, generatedExists, generatedWrites, generatedReads;
static char generatedFile[44];
static int CheckKeyGeneration(void) {
    qtime_t time;
    unsigned int choices[4];
    char encoded[45], guid[33];
    int day, seed, i, mode, errors=0, savedPrints=prints;
    memset(&time,0,sizeof(time));
    time.tm_sec=1; time.tm_min=2; time.tm_mday=1; time.tm_wday=1; time.tm_hour=3;
    memset(choices,0,sizeof(choices));
    if(!NITMOD_CreateNKey(&time,choices,encoded) || !NITMOD_DecodeNKey(encoded,44,guid) ||
       strncmp(guid+2,"FC2895320AC2DA45DA49A8A68452B4",28)) ++errors;
    for(day=0;day<366;++day) for(seed=0;seed<8;++seed) {
        time.tm_yday=day; time.tm_wday=day%7; time.tm_sec=day%61;
        for(i=0;i<4;++i) choices[i]=seed == 7 ? ~0u : (unsigned int)(day*137+seed*71+i*101);
        if(!NITMOD_CreateNKey(&time,choices,encoded) || strlen(encoded)!=44 ||
           !NITMOD_DecodeNKey(encoded,44,guid)) ++errors;
        for(i=0;i<32;++i) {
            if(i<2 || i>=30) { if(guid[i]<'A' || guid[i]>'Z') ++errors; }
            else if(!strchr("0123456789ABCDEF",guid[i])) ++errors;
        }
    }
    strcpy(encoded,"unchanged"); time.tm_yday=366;
    if(NITMOD_CreateNKey(&time,choices,encoded) || strcmp(encoded,"unchanged") ||
       NITMOD_CreateNKey(NULL,choices,encoded)) ++errors;
    for(mode=1;mode<=7;++mode) {
        keyGenerationTest=mode; generatedExists=mode>=6;
        generatedWrites=generatedReads=0; keyValue[0]=0;
        memcpy(generatedFile,keyData,44);
        if(mode==7) generatedFile[0]='!';
        NITMOD_ReadNKey();
        if(generatedWrites != (mode==1 || mode==4 || mode==5)) ++errors;
        if(mode==1 || mode==6) {
            if(!NITMOD_DecodeNKey(generatedFile,44,guid) || strcmp(guid,keyValue)) ++errors;
        } else if(keyValue[0]) ++errors;
        if(mode==1) {
            NITMOD_ReadNKey();
            if(generatedWrites!=1 || strcmp(guid,keyValue)) ++errors;
        }
        if(mode>=6) {
            strcpy(guid,"unchanged");
            if(NITMOD_GenerateMissingNKey(guid) || generatedWrites || strcmp(guid,"unchanged")) ++errors;
        }
    }
    keyGenerationTest=0;
    prints=savedPrints;
    if(errors) fprintf(stderr,"%d NKey generation failures\n",errors);
    return errors;
}
static int weaponHudTest, weaponHudDraws, weaponHudSounds, weaponHudShader;
static float weaponHudRect[4], weaponHudColor[4];
static int CheckCursorHintProtocol(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    static snapshot_t snap;
    static const int expected[] = {
        HINT_NONE,HINT_FORCENONE,HINT_PLAYER,HINT_ACTIVATE,HINT_DOOR,HINT_DOOR_ROTATING,
        HINT_DOOR_LOCKED,HINT_DOOR_ROTATING_LOCKED,HINT_MG42,HINT_BREAKABLE,HINT_BREAKABLE_DYNAMITE,
        HINT_CHAIR,HINT_ALARM,HINT_HEALTH,HINT_KNIFE,HINT_LADDER,HINT_BUTTON,HINT_WATER,
        HINT_WEAPON,HINT_AMMO,HINT_POWERUP,HINT_INVENTORY,HINT_ACTIVATE,HINT_ACTIVATE,HINT_ACTIVATE,
        HINT_FORCENONE,HINT_FORCENONE,HINT_ACTIVATE,HINT_FORCENONE,HINT_BUILD,HINT_DISARM,HINT_REVIVE,
        HINT_DYNAMITE,HINT_CONSTRUCTIBLE,HINT_UNIFORM,HINT_LANDMINE,HINT_TANK,HINT_SATCHELCHARGE,HINT_PLYR_FRIEND
    };
    qhandle_t *handles[] = {
        &cgs.media.usableHintShader,&cgs.media.doorHintShader,&cgs.media.doorRotateHintShader,
        &cgs.media.doorLockHintShader,&cgs.media.doorRotateLockHintShader,&cgs.media.mg42HintShader,
        &cgs.media.breakableHintShader,&cgs.media.dynamiteHintShader,&cgs.media.notUsableHintShader,
        &cgs.media.alarmHintShader,&cgs.media.healthHintShader,&cgs.media.knifeHintShader,
        &cgs.media.ladderHintShader,&cgs.media.buttonHintShader,&cgs.media.waterHintShader,
        &cgs.media.weaponHintShader,&cgs.media.ammoHintShader,&cgs.media.powerupHintShader,
        &cgs.media.inventoryHintShader,&cgs.media.buildHintShader,&cgs.media.disarmHintShader,
        &cgs.media.reviveHintShader,&cgs.media.uniformHintShader,&cgs.media.landmineHintShader,
        &cgs.media.tankHintShader,&cgs.media.satchelchargeHintShader,&cgs.media.friendShader
    };
    int mode, wire, v, i, errors = 0, oldMode = cg_cursorHints.integer;
    int values[] = {0,31,255};
    weaponInfo_t savedWeapon = cg_weapons[WP_FG42];
    rectDef_t rect = {296,260,48,48};
    nitmodHudAnchor_t anchor;
    savedCg = cg; savedCgs = cgs;
    memset(&cg,0,sizeof(cg)); memset(&cgs.gameState,0,sizeof(cgs.gameState));
    cgs.gameState.dataCount = 1; SetTestConfig(CS_SERVERINFO,"\\gamename\\nitmod");
    cg.snap = &snap; cg.time = 1500;
    cgs.glconfig.vidWidth = 1280; cgs.glconfig.vidHeight = 720;
    cgs.screenXScale = 2; cgs.screenYScale = 1.5f;
    anchor = CG_NitmodHudAnchor(NITMOD_HUD_STRETCH);
    for(i = 0; i < sizeof(handles)/sizeof(handles[0]); ++i) *handles[i] = 111;
    cg_weapons[WP_FG42].weaponIcon[1] = 222; cg_weapons[WP_FG42].weaponIconScale = 2;
    weaponHudTest = 1;
    for(wire = 0; wire <= 64; ++wire) for(mode = 0; mode <= 4; ++mode) for(v = 0; v < 3; ++v) {
        int typed = wire < 39 ? expected[wire] : HINT_ACTIVATE;
        int pickup = wire == 18 || wire == 19;
        int draws = !mode || typed == HINT_NONE || typed == HINT_FORCENONE ? 0 :
            pickup ? (v == 1) + (wire == 19) : 1 + (v != 0);
        memset(&snap,0,sizeof(snap)); snap.ps.serverCursorHint = wire; snap.ps.serverCursorHintVal = values[v];
        NITMOD_TranslateSnapshotWeapons(&snap);
        if(snap.ps.serverCursorHint != typed || snap.ps.serverCursorHintVal !=
           (pickup ? (v == 1 ? WP_FG42 : WP_NONE) : values[v])) ++errors;
        cg.cursorHintIcon = snap.ps.serverCursorHint; cg.cursorHintValue = snap.ps.serverCursorHintVal;
        cg.cursorHintTime = cg.time; cg.cursorHintFade = 500; cg_cursorHints.integer = mode;
        weaponHudDraws = weaponHudSounds = 0;
        if(wire && mode) CG_DrawCursorhint(&rect); else CG_NitmodDrawCursorHint(&rect);
        if(weaponHudDraws != draws || weaponHudSounds) ++errors;
        if(draws && mode == 4 && wire == 18 && v == 1 &&
           (weaponHudShader != 222 || weaponHudRect[0] != 604 || weaponHudRect[2] != 144)) ++errors;
    }
    if(NITMOD_HintFromWire(-1) != HINT_ACTIVATE || NITMOD_HintFromWire(2147483647) != HINT_ACTIVATE) ++errors;
    cg.cursorHintIcon = HINT_WEAPON; cg.cursorHintValue = WP_NUM_WEAPONS;
    weaponHudDraws = 0; CG_NitmodDrawCursorHint(&rect); if(weaponHudDraws) ++errors;
    cg.cursorHintIcon = HINT_HEALTH; cg.time += 501;
    weaponHudDraws = 0; CG_NitmodDrawCursorHint(&rect); if(weaponHudDraws) ++errors;
    weaponHudTest = 0; cg = savedCg; cgs = savedCgs; cg_cursorHints.integer = oldMode;
    cg_weapons[WP_FG42] = savedWeapon; CG_NitmodHudAnchor(anchor);
    if(errors) fprintf(stderr,"%d cursor hint protocol failures\n",errors);
    return errors;
}
static int CheckWeaponHud(void) {
    static cg_t oldCg;
    static cgs_t oldCgs;
    static weaponInfo_t oldWeapons[3];
    int weapons[3] = {WP_KNIFE, WP_MP40, WP_MOBILE_MG42};
    int times[5] = {0, 1, 500, 1500, -1};
    int mode, wi, ti, align, i, errors = 0, oldSpread = cg_drawSpreadScale.integer;
    int oldGame = cg_gameType.integer;
    int oldTag = cg_entities[0].tagParent, oldTank = cg_entities[100].tankparent;
    int oldDensity = cg_entities[101].currentState.density;
    snapshot_t snap;
    rectDef_t rect = {500, 400, 80, 40};
    vec4_t color = {.2f, .4f, .6f, .3f};
    nitmodHudAnchor_t oldAnchor;
    oldCg = cg; oldCgs = cgs;
    memset(&cg, 0, sizeof(cg)); memset(&snap, 0, sizeof(snap));
    cg.snap = &snap; cgs.screenXScale = cgs.screenYScale = 1;
    cgs.glconfig.vidWidth = 640; cgs.glconfig.vidHeight = 480;
    memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
    for(i = 0; i < 3; ++i) {
        oldWeapons[i] = cg_weapons[weapons[i]];
        cg_weapons[weapons[i]].weaponIconScale = 0;
        cg_weapons[weapons[i]].weaponIcon[1] = 991 + i;
    }
    oldAnchor = CG_NitmodHudAnchor(NITMOD_HUD_STRETCH); weaponHudTest = 1;
    for(mode = 0; mode < 2; ++mode) for(wi = 0; wi < 3; ++wi)
    for(ti = 0; ti < 5; ++ti) for(align = 0; align < 3; ++align) {
        float pulse, expectedX, expectedW;
        SetTestConfig(CS_SERVERINFO, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        cg.predictedPlayerState.weapon = weapons[wi];
        cg.predictedPlayerState.grenadeTimeLeft = times[ti]; cg.grenLastTime = 0;
        weaponHudDraws = weaponHudSounds = 0;
        CG_DrawPlayerWeaponIcon(&rect, qfalse, align, &color);
        pulse = mode && times[ti] < 0 ? 0 : mode && wi == 0 ? times[ti] / 50.f : times[ti] % 1000 / 100.f;
        expectedX = rect.x - pulse * .5f + (wi == 0 ? (align == 1 ? 20 : align == 2 ? 40 : 0) : 0);
        expectedW = (wi == 0 ? 40 : 80) + pulse;
        if(weaponHudDraws != 1 || weaponHudShader != 991 + wi ||
           fabs(weaponHudRect[0] - expectedX) > .01 || fabs(weaponHudRect[2] - expectedW) > .01 ||
           fabs(weaponHudRect[1] - (400 - pulse * .5f)) > .01 ||
           fabs(weaponHudRect[3] - (40 + pulse)) > .01 || weaponHudColor[3] != 1 ||
           (mode && weaponHudSounds) || (!mode && times[ti] > 0 && times[ti] % 1000 && weaponHudSounds != 1)) ++errors;
    }
    SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
    cg.predictedPlayerState.weapon = WP_NUM_WEAPONS; weaponHudDraws = 0;
    CG_DrawPlayerWeaponIcon(&rect, qfalse, 0, &color);
    if(weaponHudDraws) ++errors;
    cg.predictedPlayerEntity.currentState.eFlags = EF_MOUNTEDTANK;
    cg.predictedPlayerState.grenadeTimeLeft = 0;
    cg_entities[0].tagParent = ENTITYNUM_NONE;
    CG_DrawPlayerWeaponIcon(&rect, qfalse, 0, &color);
    if(weaponHudDraws != 1 || weaponHudShader != 993) ++errors;
    cg_entities[0].tagParent = 100; cg_entities[100].tankparent = 101;
    cg_entities[101].currentState.density = 8; cgs.media.browningIcon = 994;
    weaponHudDraws = 0; CG_DrawPlayerWeaponIcon(&rect, qfalse, 0, &color);
    if(weaponHudDraws != 1 || weaponHudShader != 994) ++errors;
    cg_entities[100].tankparent = MAX_GENTITIES;
    weaponHudDraws = 0; CG_DrawPlayerWeaponIcon(&rect, qfalse, 0, &color);
    if(weaponHudDraws != 1 || weaponHudShader != 993) ++errors;
    cgs.glconfig.vidWidth = 1280; cgs.glconfig.vidHeight = 720;
    for(i = -1; i <= 256; ++i) {
        float fraction = i < 0 ? 0 : i > 255 ? 1 : i / 255.f;
        snap.ps.curWeapHeat = i; weaponHudDraws = 0;
        CG_DrawWeapHeat(&rect, HUD_VERTICAL);
        if(weaponHudDraws != (i != 0)) ++errors;
        if(i && (fabs(weaponHudRect[0] - 1070) > .01 ||
           fabs(weaponHudRect[2] - 120 * fraction) > .01 ||
           weaponHudRect[3] != 60 || fabs(weaponHudColor[3] - .2f) > .001)) ++errors;
    }
    rect.x = 50; rect.y = 208; rect.w = 10; rect.h = 64;
    cg_drawSpreadScale.integer = 2; cg.predictedPlayerState.weaponstate = WEAPON_READY;
    snap.ps.aimSpreadScale = 255; weaponHudDraws = 0;
    CG_DrawWeapStability(&rect);
    if(weaponHudDraws != 1 || weaponHudRect[0] != 75 || weaponHudRect[3] != 96) ++errors;
    cg.renderingThirdPerson = qtrue; weaponHudDraws = 0; CG_DrawWeapStability(&rect);
    if(weaponHudDraws) ++errors;
    cg_gameType.integer = GT_WOLF; snap.ps.persistant[PERS_RESPAWNS_LEFT] = 12;
    weaponHudDraws = 0; CG_DrawLivesLeft();
    if(weaponHudDraws != 3 || weaponHudRect[0] != 87 || weaponHudRect[3] != 30) ++errors;
    weaponHudTest = 0;
    for(i = 0; i < 3; ++i) cg_weapons[weapons[i]] = oldWeapons[i];
    cg = oldCg; cgs = oldCgs; cg_drawSpreadScale.integer = oldSpread; cg_gameType.integer = oldGame;
    cg_entities[0].tagParent = oldTag; cg_entities[100].tankparent = oldTank;
    cg_entities[101].currentState.density = oldDensity;
    CG_NitmodHudAnchor(oldAnchor);
    if(errors) fprintf(stderr, "%d weapon HUD failures\n", errors);
    return errors;
}
static int mineRenderTest, mineShaderLoads;
static int CheckMineDisplay(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    snapshot_t snapshot;
    centity_t cent;
    refEntity_t ent;
    qboolean marker;
    int mode, team, caster, state, spotted, skill, errors = 0, i;
    int oldCrosshair = cg_drawCrosshair.integer, oldDraw = cg_draw2D.integer;
    savedCg = cg; savedCgs = cgs;
    memset(&cg, 0, sizeof(cg)); memset(&snapshot, 0, sizeof(snapshot));
    memset(&cent, 0, sizeof(cent));
    cg.snap = &snapshot; cg.clientNum = snapshot.ps.clientNum = 1;
    cg.refdef_current = &cg.refdef; AxisClear(cg.refdef.viewaxis);
    CG_BuildSolidList(); cg.time = 1000; cgs.gametype = 2;
    cg_drawCrosshair.integer = 0; cg_draw2D.integer = 1;
    cgs.clientinfo[2].infoValid = qtrue; strcpy(cgs.clientinfo[2].name, "Owner");
    cgs.media.genericConstructionShader = 501;
    memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
    cent.currentState.eType = ET_MISSILE; cent.currentState.weapon = WP_LANDMINE;
    cent.currentState.number = 64; cent.currentState.otherEntityNum = 2;
    cent.currentState.otherEntityNum2 = 1;
    VectorClear(dynamiteEnd); mineRenderTest = dynamiteTest = 1;
    for(mode = 0; mode < 2; ++mode) for(team = 1; team <= 3; ++team)
    for(caster = 0; caster < 2; ++caster) for(state = 0; state < 12; ++state)
    for(spotted = 0; spotted < 2; ++spotted) for(skill = 3; skill <= 4; ++skill) {
        int visible = mode && (team != 3 || caster) &&
            (state >= 4 || team == 1 || caster && team == 3 || spotted || skill >= 4);
        int flag = visible && state < 4 && team != 3 && (team == 1 || spotted);
        SetTestConfig(CS_SERVERINFO, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        snapshot.ps.persistant[PERS_TEAM] = cgs.clientinfo[1].team = team;
        cgs.clientinfo[1].nitmodShoutcaster = caster;
        cgs.clientinfo[1].skill[SK_BATTLE_SENSE] = skill;
        cent.currentState.teamNum = state; cent.currentState.modelindex2 = spotted;
        memset(&ent, 0, sizeof(ent)); ent.origin[2] = ent.oldorigin[2] = 100;
        CG_NitmodHintsReset(); mineShaderLoads = 0;
        if(CG_NitmodPrepareMine(&cent, &ent, &marker) != visible || marker != flag) ++errors;
        if(visible && ent.lightingOrigin[2] != 100) ++errors;
        if(visible && state < 4 && team == 3) {
            int pulse = (int)(255 - fabs(sin(1.0)) * 255);
            if(mineShaderLoads != 1 || ent.customShader != 502 || ent.origin[2] != 90 ||
               ent.shaderRGBA[1] != pulse || ent.shaderRGBA[3] != 255 ||
               ent.shaderRGBA[state % 4 == 1 ? 0 : 2] != 255) ++errors;
        }
    }
    SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
    cgs.clientinfo[1].team = snapshot.ps.persistant[PERS_TEAM] = TEAM_AXIS;
    cent.currentState.teamNum = 1;
    /* Enemy, unspotted: existing native skill fallback has an inclusive
     * 256-unit radius; spotting by this client takes precedence over it. */
    cent.currentState.otherEntityNum2 = 0; cent.currentState.modelindex2 = 0;
    cgs.clientinfo[1].skill[SK_BATTLE_SENSE] = 4;
    cent.lerpOrigin[0] = 256;
    memset(&ent, 0, sizeof(ent));
    if(!CG_NitmodPrepareMine(&cent, &ent, &marker) || marker || ent.customShader != 501) ++errors;
    cent.lerpOrigin[0] = 257;
    if(CG_NitmodPrepareMine(&cent, &ent, &marker)) ++errors;
    cent.currentState.density = 2; cgs.clientinfo[1].skill[SK_BATTLE_SENSE] = 0;
    if(!CG_NitmodPrepareMine(&cent, &ent, &marker) || marker) ++errors;
    cent.currentState.density = 0; cent.currentState.otherEntityNum2 = 1;
    cent.lerpOrigin[0] = 0;
    memset(&cgs.media.limboFont2, 0, sizeof(cgs.media.limboFont2));
    cgs.media.limboFont2.glyphScale = 1;
    for(i = 0; i < 256; ++i) {
        cgs.media.limboFont2.glyphs[i].xSkip = 10;
        cgs.media.limboFont2.glyphs[i].imageWidth = 10;
        cgs.media.limboFont2.glyphs[i].imageHeight = 10;
    }
    for(i = 0; i < 3; ++i) {
        VectorClear(dynamiteEnd); dynamiteEnd[i] = 16;
        if(CG_NitmodScanMine(&cent)) ++errors;
        dynamiteEnd[i] = 15.9f;
        if(!CG_NitmodScanMine(&cent) || !CG_NitmodDrawMineHint() || CG_NitmodDrawMineHint()) ++errors;
    }
    VectorClear(dynamiteEnd); cent.currentState.otherEntityNum = ENTITYNUM_WORLD;
    if(CG_NitmodScanMine(&cent) || CG_NitmodDrawMineHint()) ++errors;
    cent.currentState.otherEntityNum = 2;
    if(!CG_NitmodScanMine(&cent)) ++errors;
    CG_NitmodHintsReset(); if(CG_NitmodDrawMineHint()) ++errors;
    if(!CG_NitmodScanMine(&cent)) ++errors;
    ++cg.time; if(CG_NitmodDrawMineHint()) ++errors;
    cg.clientNum = MAX_CLIENTS;
    if(CG_NitmodPrepareMine(&cent, &ent, &marker)) ++errors;
    cg.clientNum = 1; snapshot.ps.clientNum = -1;
    if(CG_NitmodPrepareMine(&cent, &ent, &marker) || CG_NitmodScanMine(&cent)) ++errors;
    mineRenderTest = dynamiteTest = 0; cg = savedCg; cgs = savedCgs;
    cg_drawCrosshair.integer = oldCrosshair; cg_draw2D.integer = oldDraw;
    if(errors) fprintf(stderr, "%d mine display failures\n", errors);
    return errors;
}
static int earlyTransitionTest;
static int CheckEarlyTransition(void) {
    static cg_t saved;
    static gameState_t savedGameState;
    static snapshot_t current, next;
    centity_t savedEntity = cg_entities[100];
    centity_t *cent = &cg_entities[100];
    int savedCvar = cg_earlyTransition.integer, errors = 0, type;
    saved = cg; savedGameState = cgs.gameState;
    memset(&cg, 0, sizeof(cg));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState));
    cgs.gameState.dataCount = 1;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
    memset(&current, 0, sizeof(current)); memset(&next, 0, sizeof(next));
    current.serverTime = 100; next.serverTime = 150; next.numEntities = 1;
    next.entities[0].number = 100;
    cg.snap = &current; cg.nextSnap = &next; cg.time = 125;
    cg_earlyTransition.integer = 1; earlyTransitionTest = 1;
    for(type = 0; type < ET_EVENTS; ++type) {
        int expected = type == ET_GENERAL || type == ET_MISSILE;
        memset(cent, 0, sizeof(*cent));
        cent->nextState.number = 100; cent->nextState.eType = type;
        cent->nextState.pos.trBase[0] = 42;
        cent->nextState.eventSequence = 1;
        cent->nextState.events[0] = 59; /* Original stop-looping-sound event. */
        cent->nextState.loopSound = 77;
        cent->interpolate = qtrue;
        if(CG_NitmodTransitionEarlyEntity(0) != expected) ++errors;
        if(expected) {
            if(!cent->currentValid || !cent->interpolate || cent->lerpOrigin[0] != 42 ||
               cent->previousEventSequence != 1 || cent->currentState.loopSound != 0) ++errors;
            /* Copy the same state again: event must NOT execute again. */
            if(!CG_NitmodTransitionEarlyEntity(0) || cent->currentState.loopSound != 77) ++errors;
            CG_CheckEvents(cent);
            if(cent->currentState.loopSound != 77) ++errors;
            cent->processedFrame = cg.clientFrame;
            if(!CG_AddCEntity_Filter(cent)) ++errors; /* No renderer syscall. */
        } else if(cent->currentValid) ++errors;
    }
    cent->nextState.eType = ET_MISSILE;
    if(CG_NitmodTransitionEarlyEntity(-1) || CG_NitmodTransitionEarlyEntity(1)) ++errors;
    next.entities[0].number = MAX_GENTITIES;
    if(CG_NitmodTransitionEarlyEntity(0)) ++errors;
    next.entities[0].number = 100; cent->nextState.number = 101;
    if(CG_NitmodTransitionEarlyEntity(0)) ++errors;
    cent->nextState.number = 100;
    cg_earlyTransition.integer = 0;
    if(CG_NitmodEarlyTransitionEnabled()) ++errors;
    cg_earlyTransition.integer = 1; cg.nextFrameTeleport = qtrue;
    if(CG_NitmodEarlyTransitionEnabled()) ++errors;
    cg.nextFrameTeleport = qfalse; cg.mvTotalClients = 2;
    if(CG_NitmodEarlyTransitionEnabled()) ++errors;
    cg.mvTotalClients = 0; next.numEntities = MAX_ENTITIES_IN_SNAPSHOT + 1;
    if(CG_NitmodEarlyTransitionEnabled()) ++errors;
    next.numEntities = 1; next.serverTime = current.serverTime;
    if(CG_NitmodEarlyTransitionEnabled()) ++errors;
    next.serverTime = 150;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\etmain");
    if(CG_NitmodEarlyTransitionEnabled()) ++errors;
    earlyTransitionTest = 0; cg = saved; cgs.gameState = savedGameState;
    cg_entities[100] = savedEntity; cg_earlyTransition.integer = savedCvar;
    if(errors) fprintf(stderr, "%d early transition failures\n", errors);
    return errors;
}
static int QDECL Engine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(overlayTest && command == CG_R_DRAWSTRETCHPIC) {
        int i;
        for(i=0;i<8;++i) { int bits = va_arg(args,int); memcpy(&overlayRect[i], &bits, sizeof(bits)); }
        overlayShader = va_arg(args,int); ++overlayDraws; va_end(args); return 0;
    }
    if(overlayTest && command == CG_R_SETCOLOR) { ++overlayColors; va_end(args); return 0; }
    if(overlayTest && command == CG_CVAR_SET) {
        if(strcmp(va_arg(args,const char *), "ui_blackout")) exit(2);
        Q_strncpyz(overlayValue,va_arg(args,const char *),sizeof(overlayValue));
        ++overlaySets; va_end(args); return 0;
    }
    if(viewTest && command == CG_CM_POINTCONTENTS) {
        if(va_arg(args, const float *) != cg.refdef.vieworg || va_arg(args, int) != 0) exit(2);
        ++viewQueries; va_end(args); return viewContents;
    }
    if(mapRenderTest && (command == CG_R_DRAWSTRETCHPIC || command == CG_R_DRAWROTATEDPIC || command == CG_R_SETCOLOR)) {
        if(command == CG_R_SETCOLOR) {
            const float *color = va_arg(args, const float *);
            if(color) mapRenderAlpha = color[3];
        } else if(command == CG_R_DRAWROTATEDPIC) ++mapRenderArrows;
        else {
            int bits[4], i;
            for(i = 0; i < 4; ++i) bits[i] = va_arg(args, int);
            if(!mapRenderPics++) memcpy(mapRenderRect, bits, sizeof(mapRenderRect));
        }
        va_end(args); return 0;
    }
    if(autoexecTest && command == CG_PC_LOAD_SOURCE) {
        int found = autoexecPresent;
        if(autoexecLoads >= 4) exit(2);
        Q_strncpyz(autoexecPaths[autoexecLoads++], va_arg(args, const char *), MAX_QPATH);
        if(autoexecMapMode >= 0) found = autoexecMapMode &
            (!strcmp(autoexecPaths[autoexecLoads-1], "autoexec_default.cfg") ? 2 : 1);
        va_end(args); return found ? 41 : 0;
    }
    if(autoexecTest && command == CG_PC_FREE_SOURCE) {
        if(va_arg(args, int) != 41) exit(2);
        ++autoexecFrees; va_end(args); return 0;
    }
    if(autoexecTest && command == CG_SENDCONSOLECOMMAND) {
        const char *commandText = va_arg(args, const char *);
        if(!strcmp(commandText, "-zoom\n")) ++autoexecZooms;
        else {
            if(autoexecSends >= 4 || autoexecFrees != autoexecSends + 1) exit(2);
            Q_strncpyz(autoexecCommands[autoexecSends++], commandText, sizeof(autoexecCommands[0]));
        }
        va_end(args); return 0;
    }
    if(autoexecTest && command == CG_R_SETFOG) {
        if(va_arg(args, int) != FOG_CMD_SWITCHFOG || va_arg(args, int) != FOG_MAP || va_arg(args, int) != 20) exit(2);
        ++autoexecFogs; va_end(args); return 0;
    }
    if(debugTest && command == CG_R_REGISTERSHADER) {
        const char *path = va_arg(args, const char *);
        int shader;
        if(!strcmp(path, "textures/sfx/transgunRed")) shader = 801;
        else if(!strcmp(path, "textures/sfx/transgunBlue")) shader = 802;
        else exit(2);
        ++debugRegistrations; va_end(args); return debugMissingShader ? 0 : shader;
    }
    if(debugTest && command == CG_R_ADDREFENTITYTOSCENE) {
        const refEntity_t *line = va_arg(args, const refEntity_t *);
        if(debugLines >= 51 || line->reType != RT_RAIL_CORE || line->customShader != 987 ||
           line->shaderRGBA[0] != 63 || line->shaderRGBA[1] != 127 ||
           line->shaderRGBA[2] != 255 || line->shaderRGBA[3] != 255) exit(2);
        debugCaptured[debugLines++] = *line; va_end(args); return 0;
    }
    if(debugTest && command == CG_R_LERPTAG) {
        orientation_t *tag = va_arg(args, orientation_t *);
        const refEntity_t *body = va_arg(args, const refEntity_t *);
        if(!body->hModel || strcmp(va_arg(args, const char *), "tag_head") || va_arg(args, int)) exit(2);
        VectorSet(tag->origin, 1, 2, 3); AxisClear(tag->axis); ++debugTags;
        va_end(args); return debugMissingTag ? -1 : 0;
    }
    if(cvarScanTest && command == CG_CVAR_VARIABLESTRINGBUFFER) {
        const char *name = va_arg(args, const char *);
        char *out = va_arg(args, char *);
        int size = va_arg(args, int);
        if(strcmp(name, fields[2]) || size != 256) exit(2);
        Q_strncpyz(out, cvarScanValue, size); ++cvarScanReads;
        va_end(args); return 0;
    }
    if(cvarScanTest && command == CG_SENDCLIENTCOMMAND) {
        Q_strncpyz(cvarScanReply, va_arg(args, const char *), sizeof(cvarScanReply));
        ++cvarScanSends; va_end(args); return 0;
    }
    if(sessionTest && command == CG_CVAR_VARIABLESTRINGBUFFER) {
        char *out; int size;
        if(strcmp(va_arg(args,const char *),"fs_game")) exit(2);
        out = va_arg(args,char *); size = va_arg(args,int);
        Q_strncpyz(out,sessionGame,size); va_end(args); return 0;
    }
    if(sessionTest && command == CG_SENDCLIENTCOMMAND) {
        const char *text = va_arg(args,const char *);
        if(sessionSends >= 8 || strlen(text) >= sizeof(sessionCommands[0])) exit(2);
        Q_strncpyz(sessionCommands[sessionSends++],text,sizeof(sessionCommands[0]));
        va_end(args); return 0;
    }
    if(keyGenerationTest) {
        if(command==CG_REAL_TIME) {
            qtime_t *time=va_arg(args,qtime_t *);
            memset(time,0,sizeof(*time)); time->tm_mday=1;
            va_end(args); return keyGenerationTest==2 ? 0 : 1700000000;
        }
        if(command==CG_FS_FOPENFILE) {
            fileHandle_t *file;
            int mode;
            if(strcmp(va_arg(args,const char *),"nkey.dat")) exit(2);
            file=va_arg(args,fileHandle_t *); mode=va_arg(args,int);
            if(mode==FS_READ) {
                *file=generatedExists ? 19 : 0; va_end(args);
                return generatedExists ? (keyGenerationTest==4 ? 43 : 44) : -1;
            }
            if(mode!=FS_WRITE || generatedExists) exit(2);
            *file=keyGenerationTest==3 ? 0 : 19; va_end(args); return 0;
        }
        if(command==CG_FS_WRITE || command==CG_FS_READ) {
            void *data=va_arg(args,void *);
            if(va_arg(args,int)!=44 || va_arg(args,int)!=19) exit(2);
            if(command==CG_FS_WRITE) {
                memcpy(generatedFile,data,44); generatedExists=1; ++generatedWrites;
            } else {
                memcpy(data,generatedFile,44); ++generatedReads;
                if(keyGenerationTest==5) ((char *)data)[0]='!';
            }
            va_end(args); return 0;
        }
        if(command==CG_FS_FCLOSEFILE) {
            if(va_arg(args,int)!=19) exit(2);
            va_end(args); return 0;
        }
        if(command==CG_CVAR_SET) {
            if(strcmp(va_arg(args,const char *),"n_guid")) exit(2);
            Q_strncpyz(keyValue,va_arg(args,const char *),sizeof(keyValue)); va_end(args); return 0;
        }
    }
    if(keyTest && command==CG_REAL_TIME) { va_end(args); return 0; }
    if(weaponHudTest) {
        if(command == CG_R_DRAWSTRETCHPIC) {
            int bits[8], i;
            for(i = 0; i < 8; ++i) bits[i] = va_arg(args, int);
            memcpy(weaponHudRect, bits, sizeof(weaponHudRect));
            weaponHudShader = va_arg(args, int); ++weaponHudDraws;
        } else if(command == CG_R_SETCOLOR) {
            const float *color = va_arg(args, const float *);
            if(color) memcpy(weaponHudColor, color, sizeof(weaponHudColor));
        } else if(command == CG_S_STARTLOCALSOUND) ++weaponHudSounds;
        else { fprintf(stderr, "Unexpected weapon HUD syscall %d\n", command); exit(2); }
        va_end(args); return 0;
    }
    if(mineRenderTest && command == CG_MILLISECONDS) { va_end(args); return 1000; }
    if(mineRenderTest && command == CG_R_REGISTERSHADER) {
        if(strcmp(va_arg(args, const char *), "nitmod/SpecMines")) exit(2);
        ++mineShaderLoads; va_end(args); return 502;
    }
    if(earlyTransitionTest && command == CG_S_UPDATEENTITYPOSITION) {
        va_end(args); return 0;
    }
    if(centerRenderTest) {
        if(command == CG_R_DRAWSTRETCHPIC) {
            int bits[8], shader, i;
            for(i = 0; i < 8; ++i) bits[i] = va_arg(args, int);
            shader = va_arg(args, int);
            if(shader == 4242) {
                if(centerGlyphs < 8) memcpy(centerRects[centerGlyphs], bits, sizeof(centerRects[0]));
                ++centerGlyphs;
            }
        } else if(command != CG_R_SETCOLOR) { fprintf(stderr, "Unexpected center syscall %d\n", command); exit(2); }
        va_end(args); return 0;
    }
    if(locationMarkerTest) {
        int result = 0;
        if(command == CG_R_INPVS) result = locationMarkerPvs;
        else if(command == CG_R_ADDREFENTITYTOSCENE) {
            const refEntity_t *marker = va_arg(args, const refEntity_t *);
            if(marker->reType != RT_SPRITE || marker->customShader != 923 || marker->radius != 12 ||
               marker->origin[0] != (locationMarkers ? 3000 : 100) || marker->shaderRGBA[3] != 255)
                ++locationMarkerErrors;
            ++locationMarkers;
        } else if(command == CG_CM_BOXTRACE) {
            trace_t *trace = va_arg(args, trace_t *);
            memset(trace, 0, sizeof(*trace)); trace->fraction = 1; ++locationMarkerTraces;
        } else if(command != CG_R_SETCOLOR && command != CG_R_DRAWSTRETCHPIC) {
            fprintf(stderr, "Unexpected marker syscall %d\n", command); exit(2);
        }
        va_end(args); return result;
    }
    if(locationTest) {
        if(command != CG_R_INPVS) { fprintf(stderr, "Unexpected location syscall %d\n", command); exit(2); }
        (void)va_arg(args, const float *); (void)va_arg(args, const float *);
        ++locationPvsCalls; va_end(args); return qtrue;
    }
    if(projectileTest) {
        trace_t *trace;
        const float *start, *end, *mins, *maxs;
        if(command != CG_CM_BOXTRACE) { fprintf(stderr, "Unexpected projectile syscall %d\n", command); exit(2); }
        trace = va_arg(args, trace_t *);
        start = va_arg(args, const float *); end = va_arg(args, const float *);
        mins = va_arg(args, const float *); maxs = va_arg(args, const float *);
        if(!VectorCompare(start, end) || !VectorCompare(mins, vec3_origin) || !VectorCompare(maxs, vec3_origin) ||
           va_arg(args, int) != 0 || va_arg(args, int) != MASK_SHOT) exit(2);
        memset(trace, 0, sizeof(*trace)); trace->fraction = .5f;
        ++projectileTraces; va_end(args); return 0;
    }
    if(leanTest) {
        trace_t *trace;
        const float *start, *end, *mins, *maxs;
        if(leanTest == 2 && command == CG_S_UPDATEENTITYPOSITION) { va_end(args); return 0; }
        if(leanTest == 2 && command == CG_R_ADDLIGHTTOSCENE) { ++leanLights; va_end(args); return 0; }
        if(command != CG_CM_BOXTRACE) { fprintf(stderr, "Unexpected lean syscall %d\n", command); exit(2); }
        trace = va_arg(args, trace_t *);
        start = va_arg(args, const float *); end = va_arg(args, const float *);
        mins = va_arg(args, const float *); maxs = va_arg(args, const float *);
        if(mins[0] != -8 || mins[1] != -8 || mins[2] != -7 || maxs[0] != 8 || maxs[1] != 8 || maxs[2] != 4 ||
           va_arg(args, int) != 0 || va_arg(args, int) != MASK_PLAYERSOLID) ++leanTraceErrors;
        VectorCopy(start, leanStart); VectorCopy(end, leanEnd);
        memset(trace, 0, sizeof(*trace)); trace->fraction = leanFraction;
        ++leanTraces; va_end(args); return 0;
    }
    if(graphicPopupTest) {
        if(command == CG_PRINT) { ++graphicPrints; va_end(args); return 0; }
        if(command == CG_R_SETCOLOR) { va_end(args); return 0; }
        if(command == CG_R_DRAWSTRETCHPIC) {
            int i, bits[8], shader;
            for(i = 0; i < 8; ++i) bits[i] = va_arg(args, int);
            shader = va_arg(args, int);
            if(!graphicFirstGlyph && (shader == 700 || shader == 701)) graphicFirstGlyph = shader;
            if(shader == 901 || shader == 789) {
                ++graphicIcons; memcpy(&graphicIconWidth, &bits[2], sizeof(float));
            }
            va_end(args); return 0;
        }
        fprintf(stderr, "Unexpected graphic popup syscall %d\n", command); exit(2);
    }
    if(obituaryAudioTest) {
        if(command == CG_MILLISECONDS || command == CG_PUMPEVENTLOOP) { va_end(args); return 0; }
        if(command == CG_S_REGISTERSOUND) {
            const char *path = va_arg(args, const char *);
            int handle = !strcmp(path, "sound/nit/goat.wav") ? 901 : !strcmp(path, "sound/player/gib.wav") ? 902 :
                !strcmp(path, "sound/nit/tk.wav") ? 903 : 0;
            if(!handle || va_arg(args, int) != qfalse) exit(2);
            va_end(args); return handle;
        }
        if(command == CG_S_STARTSOUND) {
            const float *origin = va_arg(args, const float *);
            int entity = va_arg(args, int), channel = va_arg(args, int), handle = va_arg(args, int);
            if(obituaryAudioCount >= 3 || va_arg(args, int) != 127 ||
               channel != (handle == 901 ? CHAN_WEAPON : CHAN_AUTO) ||
               (handle == 903 ? origin != NULL : origin != cg.snap->ps.origin)) exit(2);
            obituaryAudioEntities[obituaryAudioCount] = entity;
            obituaryAudioHandles[obituaryAudioCount++] = handle;
            va_end(args); return 0;
        }
        fprintf(stderr, "Unexpected obituary syscall %d\n", command); exit(2);
    }
    if(userinfoTest) {
        const char *value;
        const char *name = command == CG_CVAR_SET ? va_arg(args, const char *) : "not-cvar-set";
        int nudge, packets;
        if(command != CG_CVAR_SET || strcmp(name, "cg_uinfo")) {
            fprintf(stderr, "Unexpected preference syscall %d %s\n", command, name); exit(2);
        }
        value = va_arg(args, const char *);
        if(sscanf(value, "%u %d %d", &preferenceFlags, &nudge, &packets) != 3) {
            fprintf(stderr, "Invalid preference payload: %s\n", value); exit(2);
        }
        ++userinfoWrites; va_end(args); return 0;
    }
    if(snapshotHitTest) {
        if(command == CG_MILLISECONDS || command == CG_PUMPEVENTLOOP) {
            va_end(args); return 0;
        }
        if(command == CG_S_REGISTERSOUND) {
            const char *path = va_arg(args, const char *);
            int sound = !strcmp(path, "sound/hitsounds/body.wav") ? 801 :
                !strcmp(path, "sound/hitsounds/head.wav") ? 802 : 0;
            if(!sound || va_arg(args, int) != qfalse) exit(2);
            ++snapshotHitLoads; va_end(args); return sound;
        }
        if(command == CG_S_STARTSOUND) {
            if(va_arg(args, const float *) != NULL || va_arg(args, int) != 5 ||
               va_arg(args, int) != CHAN_VOICE || snapshotHitPlays >= 2) exit(2);
            snapshotHitSamples[snapshotHitPlays++] = va_arg(args, int);
            if(va_arg(args, int) != 127) exit(2);
            va_end(args); return 0;
        }
        fprintf(stderr, "Unexpected snapshot hit syscall %d\n", command); exit(2);
    }
    if(crosshairRenderTest) {
        if(command == CG_R_DRAWSTRETCHPIC) {
            int bits[4], i;
            if(crosshairDraws >= 32) exit(2);
            for(i = 0; i < 4; ++i) bits[i] = va_arg(args, int);
            memcpy(crosshairRects[crosshairDraws], bits, sizeof(bits));
            for(i = 0; i < 4; ++i) (void)va_arg(args, int);
            crosshairShaders[crosshairDraws++] = va_arg(args, int);
        } else if(command != CG_R_SETCOLOR) { fprintf(stderr, "Unexpected crosshair syscall %d\n", command); exit(2); }
        va_end(args); return 0;
    }
    if(dynamiteTest) {
        if(command == CG_CM_BOXTRACE) {
            trace_t *trace = va_arg(args, trace_t *);
            const float *start = va_arg(args, const float *), *end = va_arg(args, const float *);
            (void)va_arg(args, const float *); (void)va_arg(args, const float *);
            if(va_arg(args, int) != 0 || va_arg(args, int) != CONTENTS_SOLID) exit(2);
            (void)start; (void)end;
            memset(trace, 0, sizeof(*trace)); trace->fraction = 1;
            VectorCopy(dynamiteEnd, trace->endpos); ++dynamiteTraces;
        } else if(command == CG_R_DRAWSTRETCHPIC) {
            int bits[4], i;
            for(i = 0; i < 4; ++i) bits[i] = va_arg(args, int);
            memcpy(dynamiteLastRect, bits, sizeof(bits)); ++dynamiteDraws;
        } else if(command != CG_R_SETCOLOR) { fprintf(stderr, "Unexpected dynamite syscall %d\n", command); exit(2); }
        va_end(args); return 0;
    }
    if(nameTest) {
        if(command == CG_CM_BOXTRACE) {
            trace_t *trace = va_arg(args, trace_t *);
            const float *start = va_arg(args, const float *), *end = va_arg(args, const float *);
            const float *mins = va_arg(args, const float *), *maxs = va_arg(args, const float *);
            if(mins[0] != -1 || maxs[0] != 1 || va_arg(args, int) != 0 || va_arg(args, int) != CONTENTS_SOLID) exit(2);
            (void)start; (void)end;
            memset(trace, 0, sizeof(*trace)); trace->fraction = nameBlocked ? .5f : 1;
            ++nameTraces;
        } else if(command == CG_R_DRAWSTRETCHPIC) {
            int i;
            for(i = 0; i < 8; ++i) (void)va_arg(args, int);
            nameShader = va_arg(args, int); ++nameDraws;
        } else if(command != CG_R_SETCOLOR) { fprintf(stderr, "Unexpected name syscall %d\n", command); exit(2); }
        va_end(args); return 0;
    }
    if(hintTest) {
        int result = 0;
        if(command == CG_R_REGISTERSHADERNOMIP) {
            const char *path = va_arg(args, const char *);
            result = !strcmp(path, "gfx/2d/objArrow") ? 810 : !strcmp(path, "gfx/awards/12") ? 811 :
                !strcmp(path, "gfx/awards/13") ? 812 : 0;
            if(!result) exit(2);
        } else if(command == CG_MILLISECONDS || command == CG_PUMPEVENTLOOP) result = 0;
        else if(command == CG_R_INPVS) result = hintVisible;
        else if(command == CG_R_ADDREFENTITYTOSCENE) {
            if(hintRefs >= 2) exit(2);
            hintEntities[hintRefs++] = *va_arg(args, const refEntity_t *);
        } else if(command == CG_R_DRAWSTRETCHPIC) ++hintPics;
        else if(command != CG_R_SETCOLOR) { fprintf(stderr, "Unexpected hint syscall %d\n", command); exit(2); }
        va_end(args); return result;
    }
    if(anchorRender && command == CG_R_DRAWSTRETCHPIC) {
        int bits[4], i;
        for(i = 0; i < 4; ++i) bits[i] = va_arg(args, int);
        memcpy(anchorRect, bits, sizeof(anchorRect));
        ++anchorDraws; va_end(args); return 0;
    }
    if(extendedTest && command == CG_S_STARTSOUND) {
        extendedPosition = va_arg(args, const float *) != NULL;
        extendedEntity = va_arg(args, int); extendedChannel = va_arg(args, int);
        extendedHandle = va_arg(args, int); extendedVolume = va_arg(args, int);
        ++extendedPlays; va_end(args); return 0;
    }
    if(materialTest && command == CG_S_REGISTERSOUND) {
        const char *path = va_arg(args, const char *);
        int i;
        if(!path || va_arg(args, int) != qfalse) exit(2);
        for(i = 0; i < 8; ++i) if(!strcmp(path, materialPaths[i])) {
            va_end(args); return 200 + i;
        }
        fprintf(stderr, "Unexpected material sound: %s\n", path); exit(2);
    }
    if(materialTest && command == CG_S_STARTSOUND) {
        int sound, first = materialExpected <= 0 ? 200 : materialExpected == 1 ? 201 : materialExpected + 202;
        int last = materialExpected == 1 ? 203 : first;
        if(va_arg(args, const float *) != NULL || va_arg(args, int) != 5 ||
           va_arg(args, int) != (materialExpected == -1 ? CHAN_AUTO : CHAN_VOICE)) exit(2);
        sound = va_arg(args, int);
        if(sound < first || sound > last || va_arg(args, int) != (materialExpected == -1 ? 127 : 255)) exit(2);
        ++materialPlays; va_end(args); return 0;
    }
    if(preferenceTest && command == CG_CVAR_SET) {
        if(strcmp(va_arg(args, const char *), "cg_limbo_secondary")) exit(2);
        preferenceValue = atoi(va_arg(args, const char *)); ++preferenceWrites;
        va_end(args); return 0;
    }
    if(classTest && command == CG_SENDCLIENTCOMMAND) {
        Q_strncpyz(classCommand, va_arg(args, const char *), sizeof(classCommand));
        ++classSends; va_end(args); return 0;
    }
    if(timerTest && command == CG_CVAR_SET) {
        const char *name = va_arg(args, const char *), *value = va_arg(args, const char *);
        if(!strcmp(name, "cg_spawnTimer_set")) Q_strncpyz(timerStart, value, sizeof(timerStart));
        else if(!strcmp(name, "cg_spawnTimer_period")) Q_strncpyz(timerPeriod, value, sizeof(timerPeriod));
        else exit(2);
        ++timerWrites; va_end(args); return 0;
    }
    if(bannerRender && command == CG_R_SETCOLOR) {
        const float *color = va_arg(args, const float *);
        if(color) memcpy(bannerDrawColor, color, sizeof(bannerDrawColor));
        va_end(args); return 0;
    }
    if(bannerRender && command == CG_R_DRAWSTRETCHPIC) {
        int values[8], shader, i;
        float x, y;
        for(i = 0; i < 8; ++i) values[i] = va_arg(args, int);
        shader = va_arg(args, int);
        if(shader != 812) ++bannerRenderErrors;
        if(bannerDrawColor[0] || bannerDrawColor[1] || bannerDrawColor[2]) {
            memcpy(&x, values, sizeof(x)); memcpy(&y, values + 1, sizeof(y));
            ++bannerGlyphs;
            if(x != 319 || y != bannerExpectedStep * bannerGlyphs ||
               bannerDrawColor[0] != 1 || bannerDrawColor[1] || bannerDrawColor[2] ||
               fabs(bannerDrawColor[3] - bannerExpectedAlpha) > .00001) ++bannerRenderErrors;
        }
        va_end(args); return 0;
    }
    if(announcerTest && command == CG_S_REGISTERSOUND) {
        const char *expected = announcerLoads ? "sound/nit/prepare.wav" : "sound/nit/fight.wav";
        if(announcerLoads >= 2 || strcmp(va_arg(args, const char *), expected) || va_arg(args, int) != qfalse) exit(2);
        ++announcerLoads; va_end(args); return announcerMissing ? 0 : 300 + announcerLoads;
    }
    if(announcerTest && command == CG_S_STARTLOCALSOUND) {
        announcerHandle = va_arg(args, int);
        if((announcerHandle != 301 && announcerHandle != 302) || va_arg(args, int) != CHAN_ANNOUNCER) exit(2);
        ++announcerPlays; va_end(args); return 0;
    }
    if(spreeSoundTest && command == CG_S_REGISTERSOUND) {
        char expected[MAX_QPATH];
        int index = spreeRegistrations++;
        const char *prefix = index < 5 ? "mk" : index < 9 ? "mr" : "ks";
        int number = index < 5 ? index + 1 : index < 9 ? index - 4 : index - 8;
        Com_sprintf(expected, sizeof(expected), "sound/nit/%s%i.wav", prefix, number);
        if(index >= 15 || strcmp(va_arg(args, const char *), expected) || va_arg(args, int) != qfalse) exit(2);
        va_end(args); return spreeSoundFailure ? spreeSoundFailure : 101 + index;
    }
    if(spreeSoundTest && command == CG_S_STARTSOUND) {
        if(va_arg(args, const float *) != NULL || va_arg(args, int) != 3 ||
           va_arg(args, int) != CHAN_AUTO) exit(2);
        spreeLastSound = va_arg(args, int);
        if(spreeLastSound < 101 || spreeLastSound > 115) exit(2);
        ++spreePlays; va_end(args); return 0;
    }
    if(teamMediaTest && (command == CG_R_REGISTERMODEL || command == CG_R_REGISTERSKIN || command == CG_R_REGISTERSHADER)) {
        const char *path = va_arg(args, const char *);
        int result;
        ++teamMediaRegistrations;
        if(!strcmp(path, "missing")) result = 0;
        else {
            char prefix = command == CG_R_REGISTERMODEL ? 'm' : command == CG_R_REGISTERSKIN ? 's' : 'p';
            if(path[0] != prefix || path[1] < '1' || path[1] > '3' || path[2]) exit(2);
            result = (prefix == 'm' ? 100 : prefix == 's' ? 200 : 300) + path[1] - '0';
        }
        va_end(args); return result;
    }
    if(!ncsTest && command == CG_R_REGISTERMODEL) {
        if(strcmp(va_arg(args, const char *), "shell.md3")) exit(2);
        va_end(args); return 777;
    }
    if(wireTest && command == CG_SETUSERCMDVALUE) {
        wireCommand = va_arg(args, int); va_end(args); return 0;
    }
    if(wireTest && command == CG_GETUSERCMD) {
        usercmd_t *cmd;
        (void)va_arg(args, int); cmd = va_arg(args, usercmd_t *);
        memset(cmd, 0, sizeof(*cmd)); cmd->weapon = wireCommand;
        va_end(args); return 1;
    }
    if(fireTest && command == CG_S_STARTSOUND) {
        if(va_arg(args, const void *) || va_arg(args, int) != 5 || va_arg(args, int) != CHAN_WEAPON) exit(2);
        fireHandle = va_arg(args, int); ++fireSounds; va_end(args); return 0;
    }
    if(deathTest && (command == CG_S_STARTSOUND || command == CG_S_STARTSOUNDEX)) {
        const float *origin = va_arg(args, const float *);
        int entity = va_arg(args, int), channel = va_arg(args, int), sound = va_arg(args, int);
        if(entity != 5 || channel != CHAN_VOICE) exit(2);
        if(command == CG_S_STARTSOUNDEX) {
            if(!origin || origin[0] != 64 || origin[1] || origin[2] || va_arg(args, int) != SND_NOCUT) exit(2);
            ++deathFar; deathFarHandle = sound;
        } else {
            if(origin) exit(2);
            ++deathNear; deathNearHandle = sound;
        }
        va_end(args); return 0;
    }
    if(keyTest && command == CG_FS_FOPENFILE) {
        fileHandle_t *file;
        if(strcmp(va_arg(args, const char *), "nkey.dat")) exit(2);
        file = va_arg(args, fileHandle_t *);
        if(va_arg(args, int) != FS_READ) exit(2);
        *file = keyLength < 0 ? 0 : 19;
        va_end(args); return keyLength;
    }
    if(keyTest && command == CG_FS_READ) {
        void *dest = va_arg(args, void *);
        if(va_arg(args, int) != 44 || va_arg(args, int) != 19) exit(2);
        memcpy(dest, keyData, 44); ++keyReads; va_end(args); return 0;
    }
    if(keyTest && command == CG_FS_FCLOSEFILE) {
        if(va_arg(args, int) != 19) exit(2);
        ++keyCloses; va_end(args); return 0;
    }
    if(keyTest && command == CG_CVAR_SET) {
        if(strcmp(va_arg(args, const char *), "n_guid")) exit(2);
        Q_strncpyz(keyValue, va_arg(args, const char *), sizeof(keyValue));
        ++keySets; va_end(args); return 0;
    }
    if(zoomTest && command == CG_CVAR_SET) {
        if(strcmp(va_arg(args, const char *), "cg_automapZoom")) exit(2);
        zoomWritten = (float)atof(va_arg(args, const char *));
        ++zoomWrites; va_end(args); return 0;
    }
    if(zoomTest && command == CG_CVAR_UPDATE) {
        vmCvar_t *cv = va_arg(args, vmCvar_t *);
        if(cv != &cg_automapZoom) exit(2);
        cv->value = zoomWritten; ++cv->modificationCount;
        va_end(args); return 0;
    }
    if(ammoTest && command == CG_R_SETCOLOR) {
        const float *color = va_arg(args, const float *);
        if(color) memcpy(ammoColor, color, sizeof(ammoColor));
        va_end(args); return 0;
    }
    if(ammoTest && command == CG_R_DRAWSTRETCHPIC) {
        int fields[8], shader, i;
        for(i = 0; i < 8; ++i) fields[i] = va_arg(args, int);
        shader = va_arg(args, int);
        if(shader == 9876) {
            if(ammoBars >= 300) exit(2);
            memcpy(ammoRects[ammoBars], fields, sizeof(ammoRects[0]));
            memcpy(ammoColors[ammoBars], ammoColor, sizeof(ammoColor));
            ++ammoBars;
        }
        va_end(args); return 0;
    }
    if(popupTest && command == CG_R_SETCOLOR) {
        const float *color = va_arg(args, const float *);
        if(color && !(color[3] >= 0 && color[3] <= 1)) ++popupErrors;
        va_end(args); return 0;
    }
    if(statusRenderTest && command == CG_R_SETCOLOR) { va_end(args); return 0; }
    if(statusRenderTest && command == CG_R_DRAWSTRETCHPIC) {
        int fields[8], shader, i;
        float rect[4], expectedX;
        for(i = 0; i < 8; ++i) fields[i] = va_arg(args, int);
        shader = va_arg(args, int); memcpy(rect, fields, sizeof(rect));
        if(shader == 7101) {
            expectedX = (statusFrames == 0 ? 18 : statusFrames == 1 ? 4 : 624) * statusScale;
            if(statusFrames == 2) expectedX += statusRightOffset;
            if(fabs(rect[0] - expectedX) > .01f || fabs(rect[1] - 388 * statusScale) > .01f ||
               fabs(rect[2] - 12 * statusScale) > .01f || fabs(rect[3] - 72 * statusScale) > .01f) ++statusRenderErrors;
            ++statusFrames;
        } else if(shader >= 7102 && shader <= 7105) {
            if((shader == 7103 && statusUnderwater) || (shader == 7104 && !statusUnderwater)) ++statusRenderErrors;
            ++statusIcons;
        }
        va_end(args); return 0;
    }
    if(fireteamRenderTest && command == CG_R_SETCOLOR) { va_end(args); return 0; }
    if(fireteamRenderTest && command == CG_R_DRAWSTRETCHPIC) {
        int fields[8], shader, i;
        float rect[4];
        for(i = 0; i < 8; ++i) fields[i] = va_arg(args, int);
        shader = va_arg(args, int);
        memcpy(rect, fields, sizeof(rect));
        if(shader >= 9000 && shader < 9000 + SK_NUM_SKILLS) {
            if(rect[0] != 14 || rect[1] != 37 + 12 * fireteamRenderIcons || rect[2] != 10 || rect[3] != 10)
                ++fireteamRenderErrors;
            ++fireteamRenderIcons;
        }
        va_end(args); return 0;
    }
    if(popupTest && command == CG_R_DRAWSTRETCHPIC) {
        int fields[8], shader, i;
        float y;
        for(i = 0; i < 8; ++i) fields[i] = va_arg(args, int);
        shader = va_arg(args, int);
        ++popupDraws;
        if(grenadeCardTest && shader == 777) {
            float actual[4];
            memcpy(actual, fields, sizeof(actual));
            for(i = 0; i < 4; ++i) if(actual[i] != grenadeCardRect[i]) ++popupErrors;
            ++grenadeCardDraws;
        }
        if(shader == 123) {
            memcpy(&y, &fields[1], sizeof(y));
            if(!popupIcons) popupFirstY = y;
            ++popupIcons;
        }
        va_end(args); return 0;
    }
    if(particleTrailTest && command == CG_CM_POINTCONTENTS) {
        va_end(args); return particleTrailContents;
    }
    if(particleInit && command == CG_R_REGISTERSHADER) {
        const char *shader = va_arg(args, const char *);
        if(!*shader) exit(2);
        va_end(args); return 1;
    }
    if(forceTest && command == CG_CVAR_VARIABLESTRINGBUFFER) {
        const char *name = va_arg(args, const char *);
        char *value = va_arg(args, char *);
        int size = va_arg(args, int);
        if(!*name) exit(2);
        Q_strncpyz(value, forceCurrent, size);
        va_end(args); return 0;
    }
    if(forceTest && command == CG_CVAR_REGISTER) {
        if(va_arg(args, vmCvar_t *) != NULL) exit(2);
        Q_strncpyz(forceLastName, va_arg(args, const char *), sizeof(forceLastName));
        Q_strncpyz(forceLastValue, va_arg(args, const char *), sizeof(forceLastValue));
        if(va_arg(args, int) != 0) exit(2);
        ++forceRegisters; va_end(args); return 0;
    }
    if(forceTest && command == CG_CVAR_SET) {
        if(strcmp(va_arg(args, const char *), forceLastName) ||
           strcmp(va_arg(args, const char *), forceLastValue)) exit(2);
        ++forceSets; va_end(args); return 0;
    }
    if(ncsTest && (command == CG_R_REGISTERMODEL || command == CG_R_REGISTERSKIN ||
       command == CG_R_REGISTERSHADER || command == CG_R_REGISTERSHADERNOMIP || command == CG_S_REGISTERSOUND)) {
        const char *path = va_arg(args, const char *);
        if(!*path) exit(2);
        ++ncsAssets; va_end(args); return 123;
    }
    if(command == CG_TRANSLATE_STRING) {
        const char *source = va_arg(args, const char *);
        char *target = va_arg(args, char *);
        Q_strncpyz(target, source, MAX_STRING_CHARS);
        va_end(args); return 0;
    }
    if(command == CG_S_STARTSOUND) {
        if(va_arg(args, const float *) != NULL) exit(2);
        if(waterTest) {
            int sound;
            if(va_arg(args, int) != 5 || va_arg(args, int) != CHAN_AUTO) exit(2);
            sound = va_arg(args, int);
            if(sound < 101 || sound > 104) exit(2);
            ++waterSounds[sound - 101]; va_end(args); return 0;
        }
        if(greetingTest) {
            if(va_arg(args, int) != 5 || va_arg(args, int) != CHAN_VOICE ||
               va_arg(args, int) != 95) exit(2);
            ++greetingPlays; va_end(args); return 0;
        }
        if(shoveTest) {
            if(va_arg(args, int) != shoveEntity || va_arg(args, int) != CHAN_AUTO ||
               va_arg(args, int) != 94 || va_arg(args, int) != 255) exit(2);
            ++shovePlays; va_end(args); return 0;
        }
        if(hitTest) {
            if(va_arg(args, int) != 5 || va_arg(args, int) != CHAN_VOICE) exit(2);
            hitSound = va_arg(args, int); ++hitPlays;
            va_end(args); return 0;
        }
        if(landingTest) {
            int sound;
            if(va_arg(args, int) != 5 || va_arg(args, int) != CHAN_AUTO) exit(2);
            sound = va_arg(args, int);
            if(sound == 81) ++hurtPlays;
            else if(sound == 82) ++landingPlays;
            else exit(2);
            va_end(args); return 0;
        }
        if(pmTest) {
            if(va_arg(args, int) != 5 || va_arg(args, int) != CHAN_VOICE ||
               va_arg(args, int) != 73 || va_arg(args, int) != 255) exit(2);
            ++pmPlays; va_end(args); return 0;
        }
        medicEntity = va_arg(args, int);
        if(va_arg(args, int) != CHAN_AUTO) exit(2);
        medicHandle = va_arg(args, int);
        ++medicSounds; va_end(args); return 0;
    }
    if(command == CG_MILLISECONDS) { va_end(args); return 1000; }
    if(command == CG_SENDCLIENTCOMMAND) {
        const char *text = va_arg(args, const char *);
        if(strncmp(text, "nitcap ", 7)) exit(2);
        ++sentCapabilities; va_end(args); return 0;
    }
    if(command == CG_PC_LOAD_SOURCE) {
        if(strcmp(va_arg(args, const char *), expectedWeaponPath ? expectedWeaponPath : "weapons/mp40.weap")) exit(2);
        ++sourceLoads; va_end(args); return 17;
    }
    if(command == CG_PC_READ_TOKEN) {
        pc_token_t *token;
        char *text;
        if(va_arg(args, int) != 17) exit(2);
        token = va_arg(args, pc_token_t *);
        text = COM_Parse(&weaponCursor);
        memset(token, 0, sizeof(*token));
        Q_strncpyz(token->string, text, sizeof(token->string));
        if(text[0] >= '0' && text[0] <= '9') {
            char *end;
            double number = strtod(text, &end);
            if(!*end) {
                token->type = TT_NUMBER;
                token->intvalue = (int)number;
                token->floatvalue = (float)number;
            }
        }
        va_end(args); return !!*text;
    }
    if(command == CG_PC_FREE_SOURCE) {
        if(va_arg(args, int) != 17) exit(2);
        ++sourceFrees; va_end(args); return 0;
    }
    if(command == CG_PC_SOURCE_FILE_AND_LINE) {
        char *filename; int *line;
        if(va_arg(args, int) != 17) exit(2);
        filename = va_arg(args, char *); line = va_arg(args, int *);
        strcpy(filename, "weapons/mp40.weap"); *line = 4;
        va_end(args); return 1;
    }
    if(command == CG_S_REGISTERSOUND) {
        if(greetingTest) {
            if(strcmp(va_arg(args, const char *), "sound/test.wav") || va_arg(args, int) != qfalse) exit(2);
            ++greetingLoads; va_end(args); return greetingHandle;
        }
        if(hitTest) {
            const char *path = va_arg(args, const char *);
            int handle = !strcmp(path, "sound/nit/hs.wav") ? 91 : !strcmp(path, "sound/hitsounds/team.wav") ? 92 : 0;
            if(!handle) exit(2);
            va_end(args); return handle;
        }
        if(pmTest) {
            if(strcmp(va_arg(args, const char *), "sound/nit/pm.wav") || va_arg(args, int) != qfalse) exit(2);
            ++pmLoads; va_end(args); return 73;
        }
        if(strcmp(va_arg(args, const char *), "test.wav")) exit(2);
        ++mediaSounds; va_end(args); return 42;
    }
    if(command == CG_ARGC) { va_end(args); return argcValue; }
    if(command == CG_CVAR_REGISTER && hitTest) {
        hitCvar = va_arg(args, vmCvar_t *);
        if(strcmp(va_arg(args, const char *), "cg_hitSounds") || strcmp(va_arg(args, const char *), "1") ||
           va_arg(args, int) != CVAR_ARCHIVE) exit(2);
        va_end(args); return 0;
    }
    if(command == CG_CVAR_UPDATE && greetingTest) {
        if(va_arg(args, vmCvar_t *) != &cg_noGreetingSounds) exit(2);
        cg_noGreetingSounds.integer = greetingValue;
        va_end(args); return 0;
    }
    if(command == CG_CVAR_UPDATE && shoveTest) {
        if(va_arg(args, vmCvar_t *) != &cg_shoveSounds) exit(2);
        cg_shoveSounds.integer = shoveValue;
        va_end(args); return 0;
    }
    if(command == CG_CVAR_UPDATE && hitTest) {
        if(va_arg(args, vmCvar_t *) != hitCvar) exit(2);
        hitCvar->integer = hitValue;
        va_end(args); return 0;
    }
    if(command == CG_CVAR_UPDATE && pmTest) {
        if(va_arg(args, vmCvar_t *) != &cg_pmSounds) exit(2);
        cg_pmSounds.integer = pmValue;
        va_end(args); return 0;
    }
    if(command == CG_CVAR_UPDATE) {
        if(va_arg(args, vmCvar_t *) != &cg_drawBanners) exit(2);
        cg_drawBanners.integer = bannerValue;
        va_end(args); return 0;
    }
    if(command == CG_GETSERVERCOMMAND) { va_end(args); return 1; }
    if(command == CG_R_SETGLOBALFOG) { ++fogCalls; va_end(args); return 0; }
    if(command == CG_GETGAMESTATE) {
        if(va_arg(args, gameState_t *) != &cgs.gameState) exit(2);
        /* Fixture already installed the exact updated engine gamestate. */
        va_end(args); return 0;
    }
    if(command == CG_ARGV) {
        int index = va_arg(args, int);
        char *buffer = va_arg(args, char *);
        int size = va_arg(args, int);
        if(index < 0 || index >= 21) exit(2);
        Q_strncpyz(buffer, fields[index], size);
        va_end(args); return 0;
    }
    if(command == CG_PRINT) { ++prints; va_end(args); return 0; }
    if(command == CG_ERROR) {
        fprintf(stderr, "Client parser error: %s\n", va_arg(args, const char *));
        va_end(args); exit(2);
    }
    fprintf(stderr, "Unexpected syscall %d\n", command); exit(2);
}
#include "check_ammo_warning.h"
#include "check_weapon_config.h"
#include "check_weapon_assets.h"
#include "check_entity_wire.h"
#include "check_intermission_fog.h"
#include "check_adrenaline_inventory.h"
#include "check_mortar_bipod.h"
#include "check_score_rows.h"
#include "check_weapon_lerp.h"
#include "check_accessory.h"
#include "check_missile_presentation.h"
#include "check_entity_sound.h"
#include "check_original_obituary.h"
#include "check_obituary_plan.h"
#include "check_mapvote_presentation.h"
#include "check_mapcycle.h"
#include "check_debrief_pages.h"
#include "check_map_coronas.h"
#include "check_debug_events.h"
#include "check_keyed_rails.h"
int main(int argc, char **argv) {
    int index, errors = 0;
    static cg_t before;
    dllEntry(Engine);
    errors += CheckEarlyTransition();
    errors += CheckMineDisplay();
    errors += CheckWeaponHud();
    errors += CheckCursorHintProtocol();
    errors += CheckKeyGeneration();
    errors += CheckOriginalSession();
    errors += CheckCvarScan();
    errors += CheckRoundTimer();
    errors += CheckPlayerDebug();
    errors += CheckAutoexec();
    errors += CheckCorpseAnimation();
    errors += CheckCommandMapProtocol();
    errors += CheckCommandMapPresentation();
    errors += CheckAmmoSelection();
    errors += CheckPlayerLean();
    errors += CheckWeaponPose();
    errors += CheckNitmodView();
    errors += CheckScopeView();
    errors += CheckOverlays();
	{
		const char *savedFields[21];
		int savedArgc = argcValue, values[NITMOD_GLOBAL_STAT_COUNT], old[NITMOD_GLOBAL_STAT_COUNT];
		qboolean failed = qfalse;
		int i;
		memcpy(savedFields, fields, sizeof(savedFields));
		fields[0] = "glstats"; fields[1] = "0";
		for(i = 0; i < NITMOD_GLOBAL_STAT_COUNT; ++i) {
			static char numbers[NITMOD_GLOBAL_STAT_COUNT][12];
			Com_sprintf(numbers[i], sizeof(numbers[i]), "%d", i - 7);
			fields[i + 2] = numbers[i];
		}
		argcValue = NITMOD_GLOBAL_STAT_COUNT + 2;
		if(!CG_NitmodParseGlobalStats(argcValue, CG_Argv, values, &failed) || failed) ++errors;
		for(i = 0; i < NITMOD_GLOBAL_STAT_COUNT; ++i) if(values[i] != i - 7) ++errors;
		memcpy(old, values, sizeof(old)); fields[8] = "bad";
		if(CG_NitmodParseGlobalStats(argcValue, CG_Argv, values, &failed) || memcmp(old, values, sizeof(old))) ++errors;
		fields[2] = "-"; argcValue = 3; failed = qfalse;
		if(!CG_NitmodParseGlobalStats(argcValue, CG_Argv, values, &failed) || !failed) ++errors;
		memcpy(fields, savedFields, sizeof(savedFields)); argcValue = savedArgc;
	}
	{
		int i;
		static const char *titles[] = {"THE BEGINNING", "100 KILLS!", "NEED A MEDIC?",
			"WATCH YOUR STEP!", "FAT ASS!", "BOOM HEADSHOT!", "ROASTER!",
			"I'M AN ENGINEER!", "DESTROYER", "REMOTE KILLER", "BUTCHER"};
		for(i = 0; i < 11; ++i)
			if(!CG_NitmodGlobalAwardTitle(i) || strcmp(CG_NitmodGlobalAwardTitle(i), titles[i]) ||
			   !CG_NitmodGlobalAwardDescription(i)) ++errors;
		if(CG_NitmodGlobalAwardTitle(-1) || CG_NitmodGlobalAwardTitle(11) ||
		   CG_NitmodGlobalAwardDescription(-1) || CG_NitmodGlobalAwardDescription(11)) ++errors;
	}
    errors += CheckDoubleJump();
    errors += CheckLeanMovement();
    errors += CheckReloadRuntime();
    errors += CheckAmmoWarning();
    dllEntry(Engine);
    {
        int cls, maximum, i;
        char number[16];
        const char *savedFields[21];
        int savedArgc = argcValue;
        memcpy(savedFields, fields, sizeof(savedFields));
        NITMOD_ClearConfigStrings();
        if(NITMOD_ClassIsDisabled(TEAM_AXIS, PC_SOLDIER)) ++errors;
        if(NITMOD_ParseLatchedClass("\\lc\\4", 1) != 4 ||
           NITMOD_ParseLatchedClass("\\c\\2", 2) != 2 ||
           NITMOD_ParseLatchedClass("\\lc\\5", 2) != 2 ||
           NITMOD_ParseLatchedClass("\\lc\\bad", 2) != 2) ++errors;
        cg.clientNum = 0; cgs.maxclients = 5;
        for(i = 0; i < 5; ++i) {
            memset(&cgs.clientinfo[i], 0, sizeof(cgs.clientinfo[i]));
            cgs.clientinfo[i].infoValid = i != 4;
            cgs.clientinfo[i].team = i == 3 ? TEAM_ALLIES : TEAM_AXIS;
        }
        for(cls = 0; cls < 5; ++cls) for(maximum = -2; maximum <= 3; ++maximum) {
            for(i = 0; i < 5; ++i) {
                cgs.clientinfo[i].cls = cls; cgs.clientinfo[i].latchedClass = cls;
            }
            cgs.clientinfo[2].cls = (cls + 1) % 5;
            fields[0] = "#"; for(i = 1; i < 21; ++i) fields[i] = "0";
            for(i = 9; i <= 13; ++i) fields[i] = "-1";
            Com_sprintf(number, sizeof(number), "%d", maximum); fields[9 + cls] = number;
            argcValue = 21; NITMOD_GameStateCommand();
            if(NITMOD_ClassIsDisabled(TEAM_AXIS, cls) != (maximum != -1 && maximum <= 2)) ++errors;
            if(NITMOD_ClassIsDisabled(TEAM_SPECTATOR, cls)) ++errors;
        }
        NITMOD_ClearConfigStrings();
        if(NITMOD_ClassIsDisabled(TEAM_AXIS, PC_SOLDIER)) ++errors;
        {
            static gameState_t savedState;
            const int weapons[] = {WP_PANZERFAUST, WP_MOBILE_MG42, WP_FLAMETHROWER, WP_MORTAR, WP_GPG40, WP_M7};
            int w, n, oldMenuTeam = cgs.ccSelectedTeam, oldMenuClass = cgs.ccSelectedClass;
            float oldRestriction = cgs.weaponRestrictions;
            savedState = cgs.gameState;
            memset(&cgs.gameState, 0, sizeof(cgs.gameState));
            cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
            strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
            cgs.ccSelectedTeam = 1; cgs.ccSelectedClass = PC_SOLDIER; cgs.weaponRestrictions = 1;
            for(w = 0; w < 6; ++w) for(maximum = -2; maximum <= 3; ++maximum) {
                fields[0] = "#"; for(i = 1; i < 21; ++i) fields[i] = "0";
                for(i = 2; i <= 6; ++i) fields[i] = "-1";
                Com_sprintf(number, sizeof(number), "%d", maximum); fields[w < 5 ? w+2 : 6] = number;
                argcValue = 21; NITMOD_GameStateCommand();
                for(n = 0; n <= 2; ++n) {
                    cgs.clientinfo[1].weapon = n ? weapons[w] : WP_NONE;
                    cgs.clientinfo[1].latchedweapon = cgs.clientinfo[1].weapon;
                    cgs.clientinfo[2].weapon = WP_NONE;
                    cgs.clientinfo[2].latchedweapon = n == 2 ? weapons[w] : WP_NONE;
                    if(CG_LimboPanel_RealWeaponIsDisabled(weapons[w]) != (maximum != -1 && n >= maximum)) ++errors;
                }
            }
            fields[1] = "0"; for(i = 2; i <= 6; ++i) fields[i] = "-1";
            fields[14] = "0"; NITMOD_GameStateCommand();
            for(cls = 0; cls < 5; ++cls) {
                cgs.ccSelectedClass = cls;
                if(CG_LimboPanel_RealWeaponIsDisabled(WP_STEN) != (cls != PC_COVERTOPS)) ++errors;
                if(CG_LimboPanel_WeaponCount_ForSlot(1) != (cls == PC_SOLDIER ? 5 : cls == PC_ENGINEER || cls == PC_COVERTOPS ? 3 : 2)) ++errors;
            }
            fields[14] = "512"; NITMOD_GameStateCommand();
            cgs.ccSelectedClass = PC_MEDIC;
            if(CG_LimboPanel_WeaponCount_ForSlot(1) != 3) ++errors;
            if(CG_LimboPanel_WeaponIsDisabled(2) || CG_LimboPanel_RealWeaponIsDisabled(WP_MP40)) ++errors;
            fields[1] = "100"; NITMOD_GameStateCommand();
            if(!NITMOD_WeaponQuotaDisabled(WP_PANZERFAUST, PC_SOLDIER, 2, 0) ||
                NITMOD_WeaponQuotaDisabled(WP_PANZERFAUST, PC_SOLDIER, 3, 0)) ++errors;
            {
                int mask, pos, slot = cgs.ccSelectedWeaponNumber;
                const int quotaSlots[] = {3, 4, 2, 5}; /* MG42, flamer, panzer, mortar */
                cgs.ccSelectedClass = PC_SOLDIER; cgs.ccSelectedWeaponNumber = 1;
                fields[1] = "0";
                for(mask = 0; mask < 16; ++mask) {
                    int visible[5] = {0}, count = 1;
                    for(i = 0; i < 4; ++i) {
                        fields[quotaSlots[i]] = mask & (1 << i) ? "0" : "-1";
                        if(!(mask & (1 << i))) visible[count++] = i+1;
                    }
                    NITMOD_GameStateCommand();
                    for(pos = -1; pos <= 6; ++pos) {
                        int expected = pos >= 0 && pos < count ? visible[pos] : 0;
                        if(CG_LimboPanel_GetWeaponNumberForPos(pos) != expected) ++errors;
                    }
                }
                cgs.ccSelectedTeam = 2;
                if(CG_LimboPanel_GetWeaponNumberForPos(0) != 0) ++errors;
                cgs.ccSelectedTeam = 1; cgs.ccSelectedWeaponNumber = 0;
                for(pos = -1; pos < 5; ++pos) {
                    int count = CG_LimboPanel_WeaponCount_ForSlot(0);
                    if(CG_LimboPanel_GetWeaponNumberForPos(pos) != (pos >= 0 && pos < count ? pos : 0)) ++errors;
                    if((pos < 0 || pos >= count) && CG_LimboPanel_GetWeaponForNumber(pos, 0, qtrue) != WP_NONE) ++errors;
                }
                if(CG_LimboPanel_GetWeaponForNumber(0, 2, qtrue) != WP_NONE) ++errors;
                cgs.ccSelectedWeaponNumber = slot;
            }
            {
                rectDef_t rect = {10, 20, 100, 60};
                fontInfo_t *oldFont = weaponPanelNameFont.font;
                qhandle_t oldShader = cgs.media.limboWeaponCardNadesOOS;
                const int rifles[] = {WP_KAR98, WP_CARBINE, WP_GARAND, WP_K43, WP_MP40};
                const int handles[] = {-1, 0, 777};
                int limit, r, h;
                grenadeCardRect[0] = rect.x; grenadeCardRect[1] = rect.y;
                grenadeCardRect[2] = rect.w; grenadeCardRect[3] = rect.h;
                CG_AdjustFrom640(&grenadeCardRect[0], &grenadeCardRect[1], &grenadeCardRect[2], &grenadeCardRect[3]);
                weaponPanelNameFont.font = &cgs.media.limboFont1;
                cgs.ccSelectedTeam = 1; cgs.ccSelectedClass = PC_ENGINEER;
                popupTest = grenadeCardTest = 1; popupErrors = 0;
                for(limit = 0; limit < 2; ++limit) {
                    fields[6] = limit ? "-1" : "0"; NITMOD_GameStateCommand();
                    for(r = 0; r < 5; ++r) for(h = 0; h < 3; ++h) {
                        cgs.media.limboWeaponCardNadesOOS = handles[h]; grenadeCardDraws = 0;
                        CG_LimboPanel_WeaponPanel_DrawWeapon(&rect, rifles[r], qfalse, "1of3", qfalse);
                        if(grenadeCardDraws != (!limit && r < 2 && h == 2)) ++errors;
                        if(r < 2 && CG_LimboPanel_RealWeaponIsDisabled(rifles[r])) ++errors;
                    }
                }
                popupTest = grenadeCardTest = 0; errors += popupErrors;
                weaponPanelNameFont.font = oldFont; cgs.media.limboWeaponCardNadesOOS = oldShader;
            }
            NITMOD_ClearConfigStrings();
            if(NITMOD_WeaponQuotaDisabled(WP_STEN, PC_MEDIC, 3, 0)) ++errors;
            cgs.gameState = savedState; cgs.ccSelectedTeam = oldMenuTeam;
            cgs.ccSelectedClass = oldMenuClass; cgs.weaponRestrictions = oldRestriction;
        }
        memcpy(fields, savedFields, sizeof(savedFields)); argcValue = savedArgc;
        memset(cgs.clientinfo, 0, sizeof(cgs.clientinfo)); cgs.maxclients = 0;
    }
    NITMOD_ClearConfigStrings();
    CG_ExecuteNewServerCommands(1);
    if(cg.soldierChargeTime[0] != 11 || cg.soldierChargeTime[1] != 22 ||
       cg.medicChargeTime[0] != 33 || cg.medicChargeTime[1] != 44 ||
       cg.engineerChargeTime[0] != 55 || cg.engineerChargeTime[1] != 66 ||
       cg.ltChargeTime[0] != 77 || cg.ltChargeTime[1] != 88 ||
       cg.covertopsChargeTime[0] != 99 || cg.covertopsChargeTime[1] != 110 || prints) ++errors;
    before = cg;
    for(index = 1; index <= 10; ++index) {
        const char *saved = fields[index];
        fields[index] = "999999999999999999999";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(memcmp(&cg, &before, sizeof(cg))) ++errors;
        fields[index] = saved;
    }
    argcValue = 10;
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(memcmp(&cg, &before, sizeof(cg)) || prints != 1) ++errors;
    if(NITMOD_ServerSupports(NITMOD_FEATURE_CHARGE_TIMES) || NITMOD_ServerSupports(NITMOD_FEATURE_NCS)) ++errors;
    {
        nitmodGameState_t previous;
        const char *bad[] = {"", "1junk", "2147483648", "-2147483649"};
        int slot, badIndex;
        fields[0] = "tsc"; fields[1] = "-2147483648"; fields[2] = "2147483647";
        argcValue = 3;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(NITMOD_GameState()->teamScoreAxis != (-2147483647 - 1) ||
           NITMOD_GameState()->teamScoreAllies != 2147483647) ++errors;
        previous = *NITMOD_GameState();
        for(slot = 1; slot <= 2; ++slot) for(badIndex = 0; badIndex < 4; ++badIndex) {
            const char *saved = fields[slot];
            fields[slot] = bad[badIndex];
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(memcmp(NITMOD_GameState(), &previous, sizeof(previous))) ++errors;
            fields[slot] = saved;
        }
        for(argcValue = 2; argcValue <= 4; argcValue += 2) {
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(memcmp(NITMOD_GameState(), &previous, sizeof(previous))) ++errors;
        }
        argcValue = 3; fields[1] = "0"; fields[2] = "-7";
        previous.teamScoreAxis = 0; previous.teamScoreAllies = -7;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(memcmp(NITMOD_GameState(), &previous, sizeof(previous)) ||
           memcmp(&cg, &before, sizeof(cg)) || NITMOD_ServerSupports(NITMOD_FEATURE_TEAM_SCORES)) ++errors;
    }
    if(argc != 3) ++errors;
    else errors += CheckOriginalAnimationConditions(argv[1]);
    errors += CheckTagConnectLayouts();
    errors += CheckSharedWeaponDefinitions();
    errors += CheckTeamWeaponMedia();
    errors += CheckWeaponRegistrationAndSelection();
    errors += CheckWeaponParseRollback();
    errors += CheckViewTeamModels();
    errors += CheckPartTeamModels();
    errors += CheckPartAnimationFrames();
    errors += CheckRecoilDefinitionFields();
    errors += CheckWeaponConfig();
    if(argc < 3) ++errors;
    else errors += CheckWeaponAssets(argv[2]);
    errors += CheckEntityWire();
    errors += CheckIntermissionFog();
    errors += CheckAdrenalineInventory();
    errors += CheckMortarBipod();
    errors += CheckWeaponLerp();
    errors += CheckAccessory();
    errors += CheckWeaponCommandGuards();
    errors += CheckAnimationCacheReset();
    errors += CheckFlashSmoke();
    errors += CheckMedicEvents();
    errors += CheckPrivateMessageSound();
    errors += CheckOriginalLanding();
    errors += CheckNitmodHudText();
    errors += CheckParticleOptions();
    errors += CheckPopupOptions();
    errors += CheckGraphicPopups();
    errors += CheckProjectileOptions();
    errors += CheckMissilePresentation();
    errors += CheckEntitySound();
    errors += CheckOriginalObituary();
    errors += CheckObituaryPlan();
    errors += CheckMapVotePresentation();
    errors += CheckMapCycle();
    errors += CheckDebriefPages();
    errors += CheckMapCoronas();
    errors += CheckDebugEvents();
    errors += CheckKeyedRails();
    errors += CheckClientLogFormatting();
    errors += CheckLocationParsing();
    errors += CheckLocationMarkers();
    errors += CheckNotification();
    errors += CheckKillNotification();
    errors += CheckModernAmmo();
    errors += CheckSpree();
    errors += CheckSpecialPrint();
    errors += CheckBannerFormatting();
    errors += CheckBannerLayout();
    errors += CheckAnnouncer();
    errors += CheckAnnouncerModes();
    errors += CheckMapAndPing();
    errors += CheckScoreboardPlans();
    errors += CheckNitmodScoreRows();
    errors += CheckOriginalSkillPresentation();
    errors += CheckCenterChannels();
    errors += CheckOriginalStatusBars();
    errors += CheckStatusBarRendering();
    errors += CheckFireteamRoster();
    errors += CheckScoreboardOrder();
    errors += CheckCountryFlagAtlas();
    errors += CheckClientExtras();
    errors += CheckWaterEvents();
    errors += CheckEventPayloadBounds();
    errors += CheckExtendedEvents();
    errors += CheckHudAnchors();
    errors += CheckHints();
    errors += CheckWoundedNames();
    errors += CheckFloatingNames();
    errors += CheckDynamiteDisplay();
    errors += CheckCrosshairPresentation();
    errors += CheckLiveStats();
    errors += CheckSnapshotPersistant();
    errors += CheckSnapshotHitSounds();
    errors += CheckClientPreferences();
    errors += CheckObituaryAudio();
    errors += CheckOriginalWireBatch();
    errors += CheckOriginalDeathEvents();
    errors += CheckWeaponWireAndPrediction();
    {
        const char *valid[] = {"scs", "2", "1", "0", "1", "1", "0", "7", "800", "1", "200", "300"};
        const char *bad[] = {"", "1junk", "2147483648", "-2147483649"};
        nitmodSimpleConfig_t expected = {2, 1, 0, 1, 1, 0, 7, 800, 1, 200, 300};
        int slot, test;
        NITMOD_ClearConfigStrings();
        for(slot = 0; slot < 12; ++slot) fields[slot] = valid[slot];
        argcValue = 12;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(memcmp(NITMOD_SimpleConfig(), &expected, sizeof(expected)) || !cg.filtercams) ++errors;
        for(slot = 1; slot < 12; ++slot) for(test = 0; test < 4; ++test) {
            fields[slot] = bad[test];
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(memcmp(NITMOD_SimpleConfig(), &expected, sizeof(expected)) || !cg.filtercams) ++errors;
            fields[slot] = valid[slot];
        }
        for(argcValue = 11; argcValue <= 13; argcValue += 2) {
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(memcmp(NITMOD_SimpleConfig(), &expected, sizeof(expected))) ++errors;
        }
        argcValue = 12; fields[1] = "0"; fields[5] = "0";
        expected.doubleJump = expected.filterCams = 0;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(memcmp(NITMOD_SimpleConfig(), &expected, sizeof(expected)) || cg.filtercams ||
           NITMOD_ServerSupports(NITMOD_FEATURE_SIMPLE_CS)) ++errors;
    }
    {
        nitmodGameState_t beforeState;
        const char *bad[] = {"nan", "inf", "1.4oops", "1e99"};
        int j;
        fields[0] = "#";
        for(j = 1; j < 21; ++j) fields[j] = "0";
        fields[15] = "1.4"; argcValue = 21;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(fabs(NITMOD_GameState()->doubleJumpHeight - 1.4f) > 0.0001f) ++errors;
        beforeState = *NITMOD_GameState();
        for(j = 0; j < 4; ++j) {
            fields[15] = bad[j];
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(memcmp(&beforeState, NITMOD_GameState(), sizeof(beforeState))) ++errors;
        }
        if(NITMOD_ServerSupports(NITMOD_FEATURE_SIMPLE_CS)) ++errors;
    }
    {
        int previousPrints = prints;
        cg.numScores = 3;
        cg.scores[0].client = 7; cg.scores[1].client = 2; cg.scores[2].client = 9;
        fields[0] = "kd0"; fields[1] = "2";
        fields[2] = "7"; fields[3] = "20"; fields[4] = "4";
        fields[5] = "2"; fields[6] = "30"; fields[7] = "5"; argcValue = 8;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.clientinfo[7].kills != 20 || cgs.clientinfo[7].deaths != 4 ||
           cgs.clientinfo[2].kills != 30 || cgs.clientinfo[2].deaths != 5 || cg.numScores != 3) ++errors;
        if(cg.scores[0].kills != 20 || cg.scores[0].deaths != 4 ||
           cg.scores[1].kills != 30 || cg.scores[1].deaths != 5) ++errors;
        cg.scores[2].kills = 123; cg.scores[2].deaths = 456;
        fields[0] = "kd1"; fields[1] = "1"; fields[2] = "9";
        fields[3] = "40"; fields[4] = "invalid"; argcValue = 5;
        cgs.clientinfo[9].kills = 0;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.clientinfo[9].kills) ++errors;
        if(cg.scores[2].kills != 123 || cg.scores[2].deaths != 456) ++errors;
        fields[4] = "6";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.clientinfo[9].kills != 40 || cgs.clientinfo[9].deaths != 6) ++errors;
        if(cg.scores[2].kills != 40 || cg.scores[2].deaths != 6) ++errors;
        /* Reject an append past the existing scoreboard and malicious counts. */
        fields[3] = "99";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.clientinfo[9].kills != 40) ++errors;
        fields[0] = "kd0"; fields[1] = "2147483647";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.clientinfo[7].kills != 20 || prints != previousPrints) ++errors;
        /* Same-row score refresh preserves K/D; a reassigned row must not
         * briefly display another player's counters. */
        fields[0] = "sc0"; fields[1] = "1"; fields[2] = "7";
        fields[3] = "100"; fields[4] = "50"; fields[5] = "0";
        fields[6] = "0"; fields[7] = "6"; fields[8] = "0"; argcValue = 9;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cg.numScores != 1 || cg.scores[0].kills != 20 || cg.scores[0].deaths != 4) ++errors;
        if(cg.scores[0].nitmodFlags != 6) ++errors;
        fields[2] = "9";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cg.scores[0].client != 9 || cg.scores[0].kills || cg.scores[0].deaths) ++errors;
        fields[0] = "bp"; fields[1] = "1"; fields[2] = "Test banner"; argcValue = 3;
        bannerValue = 0;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(prints != previousPrints) ++errors;
        bannerValue = 1;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(prints != previousPrints + 1) ++errors;
        fields[1] = "2";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(prints != previousPrints + 1) ++errors;
        fields[0] = "pop"; fields[1] = "Server notice"; argcValue = 2;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(strcmp(CG_NitmodNotificationText(), "Server notice") || prints != previousPrints + 2) ++errors;
        fields[1] = "invalid"; argcValue = 3;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(strcmp(CG_NitmodNotificationText(), "Server notice") || prints != previousPrints + 2) ++errors;
        CG_NitmodHudReset();
        {
            const char *colors[] = {"^1", "", "invalid", "^7"};
            int c, oldHeight = cg_teamChatHeight.integer, oldTime = cg_teamChatTime.integer;
            cg_teamChatHeight.integer = TEAMCHAT_HEIGHT; cg_teamChatTime.integer = 8000;
            for(c = 0; c < 4; ++c) {
                cgs.teamChatPos = cgs.teamLastChatPos = 0;
                Q_strncpyz(cg_pmColor.string, colors[c], sizeof(cg_pmColor.string));
                fields[0] = "lc"; fields[1] = "hello\x19 there"; argcValue = 2;
                CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
                if(cgs.teamChatPos != 1 || strcmp(cgs.teamChatMsgs[0], c == 0 ? "^1hello there" : "^7hello there") ||
                   cgs.teamChatMsgTeams[0] != TEAM_FREE) ++errors;
            }
            fields[1] = "bad"; argcValue = 3;
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(cgs.teamChatPos != 1) ++errors;
            cg_teamChatHeight.integer = oldHeight; cg_teamChatTime.integer = oldTime;
        }
    }
    {
        int mode, j;
        const char *rows[] = {"7", "42", "50", "12", "0", "1", "-1"};
        for(mode = 0; mode < 2; ++mode) {
            score_t beforeScore;
            int offset = mode ? 2 : 4;
            memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
            SetTestConfig(CS_SERVERINFO, mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
            fields[0] = "sc0"; fields[1] = "100"; fields[2] = "200";
            fields[offset - 1] = "1";
            for(j = 0; j < 7; ++j) fields[offset + j] = rows[j];
            argcValue = offset + 7;
            cg.teamScores[0] = 88; cg.teamScores[1] = 99;
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(cg.numScores != 1 || cg.scores[0].client != 7 || cg.scores[0].score != 42 ||
               cg.teamScores[0] != (mode ? 88 : 100) || cg.teamScores[1] != (mode ? 99 : 200)) ++errors;
            beforeScore = cg.scores[0];
            fields[offset - 1] = "2147483647";
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(cg.numScores != 1 || memcmp(&beforeScore, &cg.scores[0], sizeof(beforeScore))) ++errors;
            fields[0] = "sc1"; fields[1] = "1";
            for(j = 0; j < 7; ++j) fields[2 + j] = rows[j];
            fields[2] = "9"; argcValue = 9;
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(cg.numScores != 2 || cg.scores[1].client != 9) ++errors;
        }
    }
    {
        int id;
        char number[16];
        fields[0] = "ncp"; fields[1] = number; argcValue = 2;
        for(id = 0; id < 58; ++id) {
            char rendered[1024];
            int k;
            Com_sprintf(number, sizeof(number), "%d", id);
            cg.centerPrintPriority = 0;
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            Q_strncpyz(rendered, cg.centerPrint, sizeof(rendered));
            for(k = 0; rendered[k]; ++k) if(rendered[k] == '\n') rendered[k] = ' ';
            if(id != 7 && strcmp(rendered, NITMOD_ServerMessageText(id))) ++errors;
        }
        if(NITMOD_ServerMessageText(-1) || NITMOD_ServerMessageText(58)) ++errors;
    }
    {
        static snapshot_t snapshot;
        centity_t cent;
        int enabled, type, bits;
        memset(&cent, 0, sizeof(cent));
        memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
        SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
        NITMOD_ClearConfigStrings();
        cg.snap = &snapshot; snapshot.ps.clientNum = 5;
        hitTest = 1;
        for(enabled = 0; enabled < 2; ++enabled) for(type = 2; type <= 5; ++type)
            for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1) {
                hitValue = enabled; hitPlays = 0;
                cent.currentState.event = 99 | bits; cent.currentState.eventParm = type;
                CG_EntityEvent(&cent, cent.lerpOrigin);
                if(hitPlays != (enabled && (type == 3 || type == 4))) ++errors;
                if(hitPlays && hitSound != (type == 3 ? 92 : 91)) ++errors;
            }
        hitTest = 0; cg.snap = NULL;
    }
    {
        centity_t cent;
        int enabled, bits, entity, sound;
        const int entities[] = {-1, 0, 5, MAX_GENTITIES - 1, MAX_GENTITIES};
        const int handles[] = {-1, 0, 94};
        memset(&cent, 0, sizeof(cent));
        shoveTest = 1;
        for(enabled = -1; enabled <= 1; ++enabled)
            for(bits = 0; bits <= EV_EVENT_BITS; bits += EV_EVENT_BIT1)
                for(entity = 0; entity < 5; ++entity) for(sound = 0; sound < 3; ++sound) {
                    shoveValue = enabled; shovePlays = 0; shoveEntity = entities[entity];
                    cgs.media.sfx_bullet_fleshhit[0] = handles[sound];
                    cent.currentState.number = shoveEntity;
                    cent.currentState.event = 96 | bits;
                    CG_EntityEvent(&cent, cent.lerpOrigin);
                    if(shovePlays != (enabled != 0 && shoveEntity >= 0 &&
                       shoveEntity < MAX_GENTITIES && handles[sound] > 0)) ++errors;
                    if(cent.currentState.event != (96 | bits)) ++errors;
                }
        {
            const char *values[] = {"5", "-1", "1024", "oops", "2147483648"};
            int value, count;
            fields[0] = "nsh"; shoveEntity = 5; shoveValue = 1;
            cgs.media.sfx_bullet_fleshhit[0] = 94;
            for(value = 0; value < 5; ++value) for(count = 1; count <= 3; ++count) {
                fields[1] = values[value]; argcValue = count; shovePlays = 0;
                NITMOD_ShoveSoundCommand();
                if(shovePlays != (value == 0 && count == 2)) ++errors;
            }
        }
        shoveTest = 0;
    }
    {
        static snapshot_t snapshot;
        int disabled, valid, handle, malformed;
        char oversized[MAX_QPATH + 1];
        memset(oversized, 'a', sizeof(oversized) - 1); oversized[sizeof(oversized) - 1] = 0;
        greetingTest = 1; fields[0] = "gsnd";
        for(disabled = -1; disabled <= 1; ++disabled) for(valid = 0; valid < 4; ++valid)
            for(handle = 0; handle < 3; ++handle) for(malformed = 0; malformed < 4; ++malformed) {
                int expected;
                cg.snap = valid ? &snapshot : NULL;
                snapshot.ps.clientNum = valid == 1 ? -1 : valid == 2 ? MAX_CLIENTS : 5;
                greetingValue = disabled; greetingHandle = handle == 2 ? 95 : handle - 1;
                greetingPlays = greetingLoads = 0;
                fields[1] = malformed == 1 ? "" : malformed == 2 ? oversized : "sound/test.wav";
                argcValue = malformed == 3 ? 1 : 2;
                CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
                expected = disabled == 0 && valid == 3 && malformed == 0;
                if(greetingLoads != expected || greetingPlays != (expected && handle == 2)) ++errors;
            }
        greetingTest = 0; cg.snap = NULL;
    }
    {
        const char *blocked[] = {"cl_profile", "X", "NAME", "Sensitivity", "N_GUID", "", "bad;name", "bad name"};
        char name[32], oversized[257];
        int i;
        forceTest = 1; forceCurrent[0] = 0; forceSets = forceRegisters = 0;
        NITMOD_ClearConfigStrings(); fields[0] = "fc"; fields[2] = "1"; argcValue = 3;
        for(i = 0; i < sizeof(blocked)/sizeof(blocked[0]); ++i) {
            fields[1] = blocked[i]; CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        }
        memset(oversized, 'a', sizeof(oversized) - 1); oversized[256] = 0;
        fields[1] = oversized; CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        fields[1] = "r_test"; fields[2] = oversized; CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        fields[2] = "1"; cg.demoPlayback = qtrue;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1); cg.demoPlayback = qfalse;
        argcValue = 2; CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1); argcValue = 3;
        NITMOD_ApplyForcedCvars(); if(forceSets) ++errors;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(forceSets) ++errors; /* Reception is deferred. */
        NITMOD_ApplyForcedCvars(); if(forceSets != 1 || strcmp(forceLastValue, "1")) ++errors;
        fields[1] = "R_TEST"; fields[2] = "VALUE";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        strcpy(forceCurrent, "value"); NITMOD_ApplyForcedCvars(); if(forceSets != 1) ++errors;
        forceCurrent[0] = 0; NITMOD_ApplyForcedCvars(); if(forceSets != 2) ++errors;
        cg.demoPlayback = qtrue; NITMOD_ApplyForcedCvars(); cg.demoPlayback = qfalse;
        if(forceSets != 2) ++errors;
        NITMOD_ClearConfigStrings(); forceSets = forceRegisters = 0; fields[2] = "1";
        for(i = 0; i < 65; ++i) {
            Com_sprintf(name, sizeof(name), "test_%d", i); fields[1] = name;
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        }
        fields[1] = "test_0"; fields[2] = "2";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        NITMOD_ApplyForcedCvars();
        if(forceSets != 64 || forceRegisters != 64 || strcmp(forceLastValue, "1")) ++errors;
        NITMOD_ClearConfigStrings(); NITMOD_ApplyForcedCvars(); if(forceSets != 64) ++errors;
        forceTest = 0;
    }
    {
        struct { int wire, native; const char *text; } assets[] = {
            {0, CS_MODELS, "models/test.md3"}, {255, CS_MODELS + 255, "models/last.md3"},
            {256, CS_SOUNDS, "sound/test.wav"}, {511, CS_SOUNDS + 255, "sound/last.wav"},
            {512, CS_SHADERS, "test/shader"}, {543, CS_SHADERS + 31, "*test/mip"},
            {545, CS_SKINS, "test.skin"}, {608, CS_SKINS + 63, "last.skin"}
        };
        char number[16];
        int i;
        memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
        SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
        NITMOD_ClearConfigStrings(); ncsTest = 1; ncsAssets = 0;
        fields[0] = "ncs"; fields[1] = number; argcValue = 3;
        for(i = 0; i < sizeof(assets)/sizeof(assets[0]); ++i) {
            Com_sprintf(number, sizeof(number), "%d", assets[i].wire); fields[2] = assets[i].text;
            CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
            if(strcmp(NITMOD_AssetConfigString(assets[i].native), assets[i].text)) ++errors;
        }
        if(ncsAssets != 8 || cgs.gameModels[255] != 123 || cgs.gameSounds[255] != 123 ||
           cgs.gameShaders[31] != 123 || cgs.gameModelSkins[63] != 123) ++errors;
        Com_sprintf(number, sizeof(number), "%d", NITMOD_NCS_OBJECTIVES);
        fields[2] = "\\s\\3\\b\\31\\r\\999999\\n\\Bridge\\x\\12\\y\\34\\z\\56";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(strcmp(cgs.oidInfo[0].name, "Bridge") || cgs.oidInfo[0].customimageallies != 123 ||
           cgs.oidInfo[0].customimageaxis || cgs.oidInfo[0].origin[2] != 56) ++errors;
        Com_sprintf(number, sizeof(number), "%d", NITMOD_NCS_FIRETEAMS);
        fields[2] = "\\n\\-1";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cg.fireTeams[0].inuse) ++errors;
        fields[2] = "\\n\\2\\l\\0\\c\\0000000000000001";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(!cg.fireTeams[0].inuse || cgs.clientinfo[0].fireteamData != &cg.fireTeams[0]) ++errors;
        SetTestConfig(CS_MULTI_INFO, "\\n\\1");
        Com_sprintf(number, sizeof(number), "%d", NITMOD_NCS_SPAWNS);
        fields[2] = "\\s\\AxisSpawn\\x\\12\\y\\34\\t\\1\\c\\2";
        cgs.ccLayers = 0;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cg.spawnCount != 2 || strcmp(cg.spawnPoints[1], "AxisSpawn") ||
           cg.spawnCoordsUntransformed[1][0] != 12 || cg.spawnTeams[1] != 1 || cg.spawnPlayerCounts[1] != 2) ++errors;
        strcpy(number, "655"); fields[2] = "invalid";
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(ncsAssets != 8 || NITMOD_ServerSupports(NITMOD_FEATURE_NCS)) ++errors;
        ncsTest = 0;
    }
    if(errors) fprintf(stderr, "%d original protocol/animation failures\n", errors);
    return errors != 0;
}
