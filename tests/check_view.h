static int viewTest, viewContents, viewQueries;
static int CheckNitmodView(void) {
    static cg_t saved;
    static gameState_t savedState;
    static snapshot_t snap;
    vmCvar_t savedFov = cg_fov, savedDeveloper = developer;
    const int liquids[] = {0, CONTENTS_WATER, CONTENTS_SLIME, CONTENTS_LAVA};
    const char *protocols[] = {"\\gamename\\nitmod", "\\gamename\\etmain",
                              "\\gamename\\nitmod\\nitmod_csLayout\\et260"};
    int errors = 0, protocol, poison, liquid, tick, mode, lean, axis;
    saved = cg; savedState = cgs.gameState;
    memset(&cg, 0, sizeof(cg)); memset(&snap, 0, sizeof(snap));
    cg.snap = &snap; cg.refdef_current = &cg.refdef;
    CG_BuildSolidList();
    cg.refdef.width = 1280; cg.refdef.height = 720;
    cg.predictedPlayerState.stats[STAT_HEALTH] = 100;
    cg_fov.value = 120; developer.integer = 0;
    viewTest = 1;
    for(protocol = 0; protocol < 3; ++protocol) {
        memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
        SetTestConfig(CS_SERVERINFO, protocols[protocol]);
        for(poison = 0; poison < 2; ++poison)
        for(liquid = 0; liquid < 4; ++liquid)
        for(tick = 0; tick < 21; ++tick)
        for(mode = 0; mode < 6; ++mode) {
            float x = 120, y, warp = 0, sensitivity = 1;
            int wet = liquid || (!protocol && poison);
            cg.time = 1000 + tick * 125; cg.zoomTime = cg.time - 150;
            cg.zoomedBinoc = qfalse; cg.zoomval = 0; cg.showGameView = qfalse;
            cg.weaponSelect = WP_MP40;
            cg.predictedPlayerState.eFlags = poison ? NITMOD_EF_POISONED : 0;
            snap.ps.eFlags = 0; snap.ps.weapon = WP_MP40;
            snap.ps.persistant[PERS_HWEAPON_USE] = 0;
            if(mode == 1) { cg.weaponSelect = WP_GARAND_SCOPE; cg.zoomval = x = 10; sensitivity = .6f * 10/90; }
            if(mode == 2) { cg.predictedPlayerState.eFlags |= EF_ZOOMING; cg.zoomedBinoc = qtrue; cg.zoomval = x = 20; }
            if(mode == 3) { snap.ps.eFlags = EF_MOUNTEDTANK; x = 75; }
            if(mode == 4) { snap.ps.persistant[PERS_HWEAPON_USE] = 1; x = 55; }
            if(mode == 5) { cg.showGameView = qtrue; x = 60; }
            y = (float)(atan2(720, 1280 / tan(x / 360 * M_PI)) * 360 / M_PI);
            if(liquid) warp += (float)sin((float)(cg.time/1000.0 * .4 * M_PI * 2));
            if(!protocol && poison) warp += 12 * (float)sin((float)(cg.time/1000.0 * .3 * M_PI * 2));
            x += warp; y -= warp;
            if(mode == 2) sensitivity = y/75;
            cg.refdef.rdflags = RDF_SNOOPERVIEW;
            viewContents = liquids[liquid]; viewQueries = 0;
            if(!!CG_CalcFov() != !!wet || viewQueries != 1 ||
               fabs(cg.refdef.fov_x-x) > .0001 || fabs(cg.refdef.fov_y-y) > .0001 ||
               fabs(cg.zoomSensitivity-sensitivity) > .0001 ||
               !!(cg.refdef.rdflags & RDF_UNDERWATER) != !!wet ||
               (cg.refdef.rdflags & RDF_SNOOPERVIEW)) ++errors;
        }
    }
    /* The same poison/lean angles feed camera axes and the lean displacement. */
    for(poison = 0; poison < 2; ++poison)
    for(mode = 0; mode < 2; ++mode)
    for(lean = -1; lean <= 1; ++lean)
    for(tick = 0; tick < 41; ++tick) {
        vec3_t angles = {3, 17, -2}, origin = {10, 20, 30}, expected, right;
        float amount = lean * 14.5f, phase = (float)(tick * .125 * .3 * M_PI);
        VectorCopy(angles, expected);
        if(poison) {
            expected[PITCH] += (float)sin(phase*2.5)*12;
            expected[YAW] += (float)sin(phase)*24;
            expected[ROLL] += (float)sin(phase)*36;
        }
        expected[ROLL] += amount/(mode ? 3.2f : 2.f);
        AngleVectors(expected, NULL, right, NULL);
        CG_NitmodViewOffsets(tick*125, poison ? NITMOD_EF_POISONED : 0, mode*256, amount, angles, origin);
        for(axis = 0; axis < 3; ++axis)
            if(fabs(angles[axis]-expected[axis]) > .0001 ||
               fabs(origin[axis] - ((axis+1)*10 + amount*right[axis])) > .0001) ++errors;
    }
    viewTest = 0; cg = saved; cgs.gameState = savedState;
    cg_fov = savedFov; developer = savedDeveloper;
    if(cg.snap) CG_BuildSolidList();
    if(errors) fprintf(stderr, "%d view/FOV failures\n", errors);
    return errors;
}
