static int overlayTest, overlayDraws, overlayColors, overlaySets;
static float overlayRect[8];
static int overlayShader;
static char overlayValue[16];
static int CheckOverlays(void) {
    static cgs_t savedCgs;
    static cg_t savedCg;
    static snapshot_t snap;
    const int sizes[][2] = {{640,480},{1280,720},{1920,1080},{3440,1440},{800,1200}};
    const char *infos[] = {"\\gamename\\nitmod", "\\gamename\\etmain", "\\gamename\\nitmod\\nitmod_csLayout\\et260"};
    int p, size, anchor, flip, solid, axis, power, blackout, mv, blind, errors = 0;
    vmCvar_t savedBlackout = int_ui_blackout, savedDraw = cg_draw2D;
    vmCvar_t savedGameType = cg_gameType;
    nitmodHudAnchor_t oldAnchor = CG_NitmodHudAnchor(NITMOD_HUD_STRETCH);
    vec4_t color = {0,0,0,.5f};
    savedCgs = cgs; savedCg = cg; overlayTest = 1;
    for(p = 0; p < 3; ++p) {
        memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
        SetTestConfig(CS_SERVERINFO, infos[p]);
        for(size = 0; size < 5; ++size)
        for(anchor = -1; anchor < 3; ++anchor)
        for(flip = 0; flip < 4; ++flip)
        for(solid = 0; solid < 2; ++solid) {
            float w = (flip&1) ? -640.f : 640.f, h = (flip&2) ? -480.f : 480.f;
            float expected[] = {0,0,0,0,0,0,0,1};
            cgs.glconfig.vidWidth = sizes[size][0]; cgs.glconfig.vidHeight = sizes[size][1];
            cgs.screenXScale = sizes[size][0]/640.f; cgs.screenYScale = sizes[size][1]/480.f;
            cgs.media.whiteShader = 73;
            CG_NitmodHudAnchor((nitmodHudAnchor_t)anchor);
            overlayDraws = overlayColors = 0;
            if(solid) CG_NitmodFillOverlay(0,0,w,h,color);
            else CG_NitmodDrawOverlay(0,0,w,h,91,qfalse);
            expected[2] = sizes[size][0] * (solid && (flip&1) ? -1.f : 1.f);
            expected[3] = sizes[size][1] * (solid && (flip&2) ? -1.f : 1.f);
            if(!solid) {
                expected[4] = !!(flip&1); expected[5] = !!(flip&2);
                expected[6] = !(flip&1); expected[7] = !(flip&2);
            }
            if(overlayDraws != 1 || overlayColors != (solid ? 2 : 0) || overlayShader != (solid ? 73 : 91)) ++errors;
            for(axis = 0; axis < 8; ++axis) if(fabs(overlayRect[axis]-expected[axis]) > .001) ++errors;
        }
        memset(&snap, 0, sizeof(snap)); cg.snap = &snap; cg.clientNum = 0;
        cg.time = 1000; cgs.fadeStartTime = cgs.fadeDuration = 0;
        cgs.fadeAlpha = cgs.fadeAlphaCurrent = 0;
        cgs.clientinfo[0].team = TEAM_SPECTATOR; cg_draw2D.integer = 0;
        cgs.gametype = GT_WOLF;
        cg_gameType.integer = GT_WOLF;
        for(power = 0; power < 4; ++power)
        for(blackout = 0; blackout < 2; ++blackout)
        for(mv = 0; mv < 2; ++mv)
        for(blind = 0; blind < 2; ++blind) {
            int set = !blackout ? power && (!p || !mv) : !power || (p && mv);
            int forced = !p && blind;
            snap.ps.powerups[PW_BLACKOUT] = power; int_ui_blackout.integer = blackout;
            snap.ps.eFlags = blind ? NITMOD_EF_BLINDED : 0;
            cg.mvTotalClients = mv; overlaySets = overlayDraws = overlayColors = 0;
            CG_DrawFlashFade();
            if(overlaySets != (!!set + forced) || overlayDraws != blackout || overlayColors != blackout*2) ++errors;
            if((set || forced) && atoi(overlayValue) != (forced ? 1 : !blackout ? power : 0)) ++errors;
        }
    }
    overlayTest = 0; cgs = savedCgs; cg = savedCg;
    int_ui_blackout = savedBlackout; cg_draw2D = savedDraw;
    cg_gameType = savedGameType;
    CG_NitmodHudAnchor(oldAnchor);
    if(errors) fprintf(stderr,"%d overlay failures\n",errors);
    return errors;
}
