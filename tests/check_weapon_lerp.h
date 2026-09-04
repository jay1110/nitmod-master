extern void CG_RunWeapLerpFrame(clientInfo_t *, weaponInfo_t *, lerpFrame_t *, int, float);
static int CheckWeaponLerp(void) {
    static weaponInfo_t weapon;
    lerpFrame_t lf, before;
    snapshot_t *savedSnap = cg.snap;
    int savedTime = cg.time, savedSpeed = cg_animSpeed.integer, savedDebug = cg_debugAnim.integer;
    int loop, tick, errors = 0;
    cg.snap = NULL; cg_animSpeed.integer = 1; cg_debugAnim.integer = 0;
    for(loop = 0; loop <= 4; ++loop) {
        memset(&weapon, 0, sizeof(weapon)); memset(&lf, 0, sizeof(lf));
        lf.animation = &weapon.weapAnimations[0];
        lf.animation->firstFrame = 10; lf.animation->numFrames = 4;
        lf.animation->frameLerp = 50; lf.animation->loopFrames = loop;
        for(tick = 0; tick < 20; ++tick) {
            int frame = tick + 1;
            if(frame >= 4) frame = loop ? (frame - 4) % loop + 4 - loop : 3;
            cg.time = tick * 50;
            CG_RunWeapLerpFrame(NULL, &weapon, &lf, 0, 1);
            if(lf.frame != 10 + frame || !(lf.backlerp >= 0 && lf.backlerp <= 1)) ++errors;
        }
    }
    memset(&lf, 0, sizeof(lf)); lf.animation = &weapon.weapAnimations[0];
    lf.oldFrameTime = 0; lf.frameTime = 50; lf.oldFrame = 10; lf.frame = 11;
    cg.time = 25;
    CG_RunWeapLerpFrame(NULL, &weapon, &lf, 0, 1);
    if(lf.oldFrame != 10 || lf.frame != 11 || lf.backlerp != .5f) ++errors;
    before = lf;
    CG_RunWeapLerpFrame(NULL, &weapon, &lf, MAX_WP_ANIMATIONS, 1);
    CG_RunWeapLerpFrame(NULL, &weapon, &lf, -1, 1);
    CG_RunWeapLerpFrame(NULL, &weapon, &lf, 0, -1);
    if(memcmp(&lf, &before, sizeof(lf))) ++errors;
    for(tick = 0; tick < 3; ++tick) {
        memset(&lf, 0, sizeof(lf)); lf.animation = &weapon.weapAnimations[0];
        lf.animation->numFrames = tick == 0 ? 0 : 4;
        lf.animation->frameLerp = tick == 1 ? 0 : tick == 2 ? -1 : 50;
        cg.time = 100;
        CG_RunWeapLerpFrame(NULL, &weapon, &lf, 0, 1);
        if(lf.frame != 10 || lf.oldFrame != 10 || lf.backlerp || lf.frameTime != 100) ++errors;
    }
    memset(&lf, 0, sizeof(lf));
    weapon.weapAnimations[1].firstFrame = 30;
    weapon.weapAnimations[1].numFrames = 4;
    weapon.weapAnimations[1].frameLerp = 50;
    weapon.weapAnimations[1].initialLerp = 50;
    cg.time = 2147483647;
    CG_RunWeapLerpFrame(NULL, &weapon, &lf, 1 | ANIM_TOGGLEBIT, 1);
    if(lf.animationNumber != (1 | ANIM_TOGGLEBIT) || lf.animationTime != 2147483647 ||
       lf.frame < 30 || lf.frame > 33 || !(lf.backlerp >= 0 && lf.backlerp <= 1)) ++errors;
    cg.snap = savedSnap; cg.time = savedTime; cg_animSpeed.integer = savedSpeed; cg_debugAnim.integer = savedDebug;
    return errors;
}
