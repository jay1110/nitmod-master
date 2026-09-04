/* Full cgame fixture: independently calculated pose components and RNG stream. */
static int CheckWeaponPose(void) {
    static cg_t view;
    static refdef_t ref;
    static gameState_t savedGameState;
    vec3_t origin, angles, expected, right, savedKick;
    float savedPitch = cg.recoilPitch;
    int errors = 0, weapon, mode, state, lean, i, axis, seed;
    const int times[] = { -1, 0, 1, 75, 149, 150, 199, 200, 201, 300, 449, 450, 1000 };
    memset(&view, 0, sizeof(view)); memset(&ref, 0, sizeof(ref));
    view.refdef_current = &ref; AxisClear(ref.viewaxis);
    VectorSet(ref.vieworg, 10, 20, 30);
    view.proneMovingTime = 1000; /* No return transition at time zero. */
    for(weapon = 0; weapon < WP_NUM_WEAPONS; ++weapon)
    for(mode = 0; mode < 2; ++mode)
    for(state = 0; state <= WEAPON_RELOADING; ++state)
    for(lean = -1; lean <= 1; ++lean) {
        float amount = lean * 13.75f, divisor = 2;
        view.predictedPlayerState.weapon = weapon;
        view.predictedPlayerState.weaponstate = state;
        view.predictedPlayerState.leanf = amount;
        CG_NitmodCalculateWeaponPosition(&view, mode * 256, origin, angles);
        VectorCopy(ref.vieworg, expected);
        if(amount && state != WEAPON_FIRINGALT) {
            if(mode) expected[1] -= amount * .125f;
            else {
                if(weapon == WP_FLAMETHROWER || weapon == WP_KAR98 || weapon == WP_CARBINE ||
                   weapon == WP_K43 || weapon == WP_GPG40 || weapon == WP_M7) divisor = 4;
                if(weapon == WP_GARAND) divisor = 6;
                VectorSet(right, 0, 0, -amount / divisor);
                AngleVectors(right, NULL, right, NULL);
                VectorMA(expected, -amount / divisor, right, expected);
                expected[1] += amount * .25f;
            }
        }
        for(axis = 0; axis < 3; ++axis) {
            float wanted = 0;
            if(!mode && amount && state != WEAPON_FIRINGALT)
                wanted = axis == PITCH ? (float)fabs(amount) * .5f : axis == ROLL ? -amount/divisor : 0;
            if(fabs(origin[axis] - expected[axis]) > .0001 || fabs(angles[axis] - wanted) > .0001) ++errors;
        }
    }
    view.predictedPlayerState.weapon = WP_MP40;
    view.predictedPlayerState.leanf = 0;
    view.predictedPlayerState.weaponstate = WEAPON_READY;
    view.proneMovingTime = 0; view.landTime = 0; view.landChange = -16;
    view.xyspeed = 160; view.bobfracsin = .5f;
    VectorSet(view.kickAngles, 1, 2, 3);
    for(mode = 0; mode < 2; ++mode)
    for(state = 0; state < 2; ++state)
    for(i = 0; i < sizeof(times)/sizeof(times[0]); ++i) {
        float t = (float)times[i], factor = 0, land = 0, drift = (float)sin(t*.001)*.8f;
        view.time = times[i]; view.bobcycle = state;
        view.predictedPlayerState.eFlags = mode ? EF_PRONE_MOVING : 0;
        if(mode && t > 0) factor = t >= 200 ? 1 : t / 200;
        if(!mode && t >= 0 && t < 200) factor = 1 - t / 200;
        if(t >= 0 && t < 150) land = t * -4 / 150;
        else if(t >= 150 && t < 450) land = (450-t) * -4 / 300;
        CG_NitmodCalculateWeaponPosition(&view, 0, origin, angles);
        if(fabs(origin[0] - (10-20*factor)) > .0001 ||
           fabs(origin[1] - (20+3*factor)) > .0001 || fabs(origin[2]-(30+land)) > .0001 ||
           fabs(angles[PITCH] - (.4f+drift-1)) > .0001 ||
           fabs(angles[YAW] - ((state ? -.8f : .8f)+drift-2)) > .0001 ||
           fabs(angles[ROLL] - ((state ? -.4f : .4f)+drift-3)) > .0001) ++errors;
    }
    view.xyspeed = 0; view.time = 1000; view.proneMovingTime = 0;
    VectorClear(view.kickAngles); view.refdefViewAngles[PITCH] = 24;
    view.pmext.mountedWeaponAngles[PITCH] = 13;
    for(mode = 0; mode < 2; ++mode)
    for(state = 0; state < 2; ++state)
    for(i = 0; i < 3; ++i) {
        view.renderingThirdPerson = mode;
        view.predictedPlayerState.eFlags = i == 2 ? EF_MOUNTEDTANK : 0;
        view.predictedPlayerState.weapon = i == 0 ? WP_MORTAR_SET : i == 1 ? WP_MOBILE_MG42_SET : WP_MP40;
        view.predictedPlayerState.weaponstate = state ? WEAPON_RAISING : WEAPON_READY;
        CG_NitmodCalculateWeaponPosition(&view, 0, origin, angles);
        if(fabs(angles[PITCH] - (i == 2 ? 20 : !mode && !state ? 13 : 24)) > .0001) ++errors;
    }
    savedGameState = cgs.gameState; VectorCopy(cg.kickAVel, savedKick);
    memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
    for(weapon = 0; weapon < WP_NUM_WEAPONS; ++weapon)
    for(seed = 0; seed < 32; ++seed) {
        float pitch = 0, spread = 0, yaw = 0;
        int supported = 1, next;
        srand(seed);
        switch(weapon) {
        case WP_LUGER: case WP_COLT: case WP_SILENCER: case WP_SILENCED_COLT:
        case WP_AKIMBO_LUGER: case WP_AKIMBO_COLT: case WP_AKIMBO_SILENCEDLUGER:
        case WP_AKIMBO_SILENCEDCOLT: case WP_PANZERFAUST: break;
        case WP_MP40: case WP_THOMPSON: case WP_STEN: case WP_FG42: case WP_FG42SCOPE:
        case WP_MOBILE_MG42: case WP_MOBILE_MG42_SET:
            pitch = -(rand()%3+1)*.3f; spread = .6f; break;
        case WP_KAR98: case WP_CARBINE: case WP_GARAND: case WP_K43:
            pitch = -2; spread = 1; break;
        case WP_GARAND_SCOPE: case WP_K43_SCOPE: pitch = -.3f; break;
        default: supported = 0; break;
        }
        if(supported) yaw = ((rand()&32767)/32767.0f-.5f)*2*spread;
        next = rand(); srand(seed);
        VectorSet(cg.kickAVel, 11, 12, 13); cg.recoilPitch = 17;
        CG_WeaponFireRecoil(weapon);
        if(rand() != next || cg.recoilPitch != 17 ||
           fabs(cg.kickAVel[0] - (supported ? pitch*30 : 11)) > .0001 ||
           fabs(cg.kickAVel[1] - (supported ? yaw*30 : 12)) > .0001 ||
           fabs(cg.kickAVel[2] - (supported ? -yaw*30 : 13)) > .0001) ++errors;
    }
    cgs.gameState = savedGameState; VectorCopy(savedKick, cg.kickAVel); cg.recoilPitch = savedPitch;
    if(errors) fprintf(stderr, "%d weapon pose/recoil failures\n", errors);
    return errors;
}
