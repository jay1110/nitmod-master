extern void Reached_Train(gentity_t *ent);
extern void Reached_Train_rotating(gentity_t *ent);
extern qboolean G_ScriptAction_FollowSpline(gentity_t *ent, char *params);
static int moverLinks;
static int QDECL MoverScaleSyscall(int command, ...) {
    if(command == G_LINKENTITY) { ++moverLinks; return 0; }
    fprintf(stderr,"unexpected mover syscall %d\n",command); exit(2);
    return 0;
}
static int CheckMoverScale(void) {
    gentity_t train, first, second;
    vmCvar_t savedScale=g_moverScale;
    int savedTime=level.time, rotating, override, scale, explicitTime, errors=0;
    const float scales[]={0.5f,1.0f,2.0f,4.0f};
    dllEntry(MoverScaleSyscall); level.time=1000;
    for(rotating=0;rotating<2;++rotating) for(override=0;override<2;++override)
    for(scale=0;scale<4;++scale) for(explicitTime=0;explicitTime<2;++explicitTime) {
        int expected;
        memset(&train,0,sizeof(train)); memset(&first,0,sizeof(first)); memset(&second,0,sizeof(second));
        train.classname="func_train";
        train.s.eType=ET_MOVER; train.speed=100; train.nextTrain=&first;
        first.nextTrain=&second; first.speed=override ? 100 : 0;
        first.duration=explicitTime ? 3 : 0; first.soundLoop=71;
        second.s.origin[0]=100;
        g_moverScale.value=scales[scale]; moverLinks=0;
        expected=rotating && explicitTime ? 3000 : (int)(1000/(override ? scales[scale] : 1));
        if(rotating) Reached_Train_rotating(&train); else Reached_Train(&train);
        if(train.s.pos.trDuration!=expected || train.nextTrain!=&second ||
           train.s.pos.trTime!=1000 || train.s.loopSound!=71 || moverLinks!=1 ||
           train.s.pos.trType!=TR_LINEAR_STOP || fabs(train.s.pos.trDelta[0]-100000.0f/expected)>0.01f) ++errors;
    }
    {
        splinePath_t savedPath=splinePaths[0];
        int savedCount=numSplinePaths;
        vec3_t origin={0,0,0};
        numSplinePaths=0;
        BG_AddSplinePath("scale_test","",origin);
        splinePaths[0].length=100;
        for(scale=0;scale<4;++scale) {
            char command[]="0 scale_test 100";
            memset(&train,0,sizeof(train));
            train.scriptStatus.scriptStackChangeTime=level.time;
            g_moverScale.value=scales[scale];
            if(!G_ScriptAction_FollowSpline(&train,command) ||
               train.s.pos.trDuration!=(int)(1000/scales[scale]) ||
               train.s.apos.trDuration!=train.s.pos.trDuration ||
               train.s.pos.trType!=TR_SPLINE || train.s.effect2Time!=1 ||
               !(train.scriptStatus.scriptFlags & SCFL_GOING_TO_MARKER)) ++errors;
        }
        splinePaths[0]=savedPath; numSplinePaths=savedCount;
    }
    g_moverScale=savedScale; level.time=savedTime;
    if(errors) fprintf(stderr,"mover scale: %d failures\n",errors);
    return errors;
}
