static int CheckCameraShake(void) {
    static cg_t saved;
    const float strengths[] = { 0, .25f, .5f, 1, 2, -1 };
    int s, elapsed, errors = 0;
    saved = cg;
    for(s = 0; s < 6; ++s) {
        float duration = strengths[s] * strengths[s] * 1000;
        if(duration > 1000) duration = 1000;
        cg.time = 1000;
        CG_StartShakeCamera(strengths[s]);
        if(cg.cameraShakeLength != duration ||
           cg.cameraShakeTime != (duration ? 1000 + (int)duration : 0)) ++errors;
        for(elapsed = 0; elapsed <= 1100; elapsed += 25) {
            float fraction, expected;
            cg.time = 1000; CG_StartShakeCamera(strengths[s]);
            cg.time += elapsed;
            expected = duration > 0 && elapsed <= (int)duration ? ((int)duration - elapsed) / duration : 0;
            fraction = CG_CameraShakeFraction();
            if(fabs(fraction - expected) > .0001f) ++errors;
            VectorSet(cg.refdef.vieworg, 10, 20, 30);
            VectorClear(cg.refdefViewAngles);
            CG_ShakeCamera();
            if(!(cg.refdef.vieworg[0] >= -100 && cg.refdef.vieworg[0] <= 100) ||
               !(cg.refdef.vieworg[1] >= -100 && cg.refdef.vieworg[1] <= 100) ||
               !(cg.refdef.vieworg[2] >= -100 && cg.refdef.vieworg[2] <= 100)) ++errors;
            if(!expected && (cg.refdef.vieworg[0] != 10 || cg.refdef.vieworg[1] != 20 || cg.refdef.vieworg[2] != 30)) ++errors;
        }
    }
    cg.time = 100; CG_StartShakeCamera(1); cg.time = -100;
    if(CG_CameraShakeFraction() != 1) ++errors;
    cg.time = 1200;
    if(CG_CameraShakeFraction() || cg.cameraShakeScale || cg.cameraShakeTime ||
       cg.cameraShakePhase || cg.cameraShakeLength) ++errors;
    cg.time = 0; cg.cameraShakeTime = 0; cg.cameraShakeLength = 0;
    if(CG_CameraShakeFraction()) ++errors;
    cg.time = 0x7fffffff - 10; CG_StartShakeCamera(2);
    if(cg.cameraShakeTime != 0x7fffffff || cg.cameraShakeLength != 1000) ++errors;
    cg = saved;
    return errors;
}
