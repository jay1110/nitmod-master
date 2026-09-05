/* Exercise actual warmup glyph draws, not just the coordinate helper. */
static int CheckWidescreenText(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    float baseline[256][4];
    const int sizes[][2] = {{640,480},{1280,720},{1920,1080},{3440,1440}};
    int mode, size, i, component, count = 0, errors = 0;
    int paused = cg_paused.integer;
    nitmodHudAnchor_t savedAnchor = CG_NitmodHudAnchor(NITMOD_HUD_STRETCH);
    savedCg = cg; savedCgs = cgs;
    memset(&cg, 0, sizeof(cg)); memset(&cgs, 0, sizeof(cgs));
    cg.time = 1000; cg.warmup = 11000;
    for(mode = 0; mode < 3; ++mode) for(size = 0; size < 4; ++size) {
        float sy = sizes[size][1] / 480.f;
        float sx = mode ? sy : sizes[size][0] / 640.f;
        float offset = mode ? (sizes[size][0] - 640 * sx) * .5f : 0;
        cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
        strcpy(cgs.gameState.stringData + 1, mode == 2 ?
            "\\gamename\\nitmod\\nitmod_csLayout\\et260" : mode ?
            "\\gamename\\nitmod" : "\\gamename\\etmain");
        cgs.glconfig.vidWidth = sizes[size][0]; cgs.glconfig.vidHeight = sizes[size][1];
        cgs.screenXScale = sizes[size][0] / 640.f; cgs.screenYScale = sy;
        CG_NitmodHudAnchor(NITMOD_HUD_RIGHT);
        anchorRender = 2; anchorDraws = 0;
        CG_DrawWarmup();
        anchorRender = 0;
        if(CG_NitmodHudAnchor(NITMOD_HUD_STRETCH) != NITMOD_HUD_RIGHT) ++errors;
        if(!size) {
            count = anchorDraws;
            memcpy(baseline, widescreenRects, sizeof(baseline));
            if(count <= 0 || count > 256) ++errors;
        } else {
            if(anchorDraws != count) ++errors;
            for(i = 0; i < count && i < 256; ++i) for(component = 0; component < 4; ++component) {
                float expected = baseline[i][component] * (component % 2 ? sy : sx);
                if(component == 0) expected += offset;
                if(fabs(widescreenRects[i][component] - expected) > .002f) ++errors;
            }
        }
        /* Hidden scoreboard must restore its caller's coordinate domain too. */
        cg_paused.integer = 1;
        CG_NitmodHudAnchor(NITMOD_HUD_LEFT);
        if(CG_DrawScoreboard()) ++errors;
        if(CG_NitmodHudAnchor(NITMOD_HUD_STRETCH) != NITMOD_HUD_LEFT) ++errors;
        /* Vertical border thickness must use the active horizontal scale. */
        CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
        anchorRender = 1; anchorDraws = 0;
        CG_DrawSides(10, 20, 100, 40, 2);
        anchorRender = 0;
        if(anchorDraws != 2 || fabs(anchorRect[2] - 2 * sx) > .002f) ++errors;
    }
    cg = savedCg; cgs = savedCgs; cg_paused.integer = paused;
    CG_NitmodHudAnchor(savedAnchor);
    if(errors) fprintf(stderr, "widescreen text/border checks: %d errors\n", errors);
    return errors;
}
