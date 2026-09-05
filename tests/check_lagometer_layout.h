static float lagometerFirstRect[4];
static int lagometerDraws, lagometerFirstShader;
static int QDECL LagometerEngine(int command, ...) {
    va_list args;
    va_start(args,command);
    if(command == CG_R_DRAWSTRETCHPIC) {
        int i,bits;
        float rect[4];
        for(i=0;i<8;++i) {
            bits=va_arg(args,int);
            if(i<4) memcpy(&rect[i],&bits,sizeof(bits));
        }
        bits=va_arg(args,int);
        if(!lagometerDraws) { memcpy(lagometerFirstRect,rect,sizeof(rect)); lagometerFirstShader=bits; }
        ++lagometerDraws;
    } else if(command != CG_R_SETCOLOR) {
        fprintf(stderr,"lagometer: unexpected syscall %d\n",command); exit(2);
    }
    va_end(args); return 0;
}
static int CheckLagometerLayout(void) {
    static cg_t oldCg;
    static cgs_t oldCgs;
    vmCvar_t oldLag=cg_lagometer, oldPredict=cg_nopredict;
    nitmodHudAnchor_t oldAnchor=CG_NitmodHudAnchor(NITMOD_HUD_STRETCH);
    const int sizes[][2]={{640,480},{1280,720},{1920,1080},{3440,1440}};
    int mode,size,local,enabled,errors=0;
    CG_NitmodSnapshotRateReset();
    CG_NitmodSnapshotRateUpdate(1000,100,150,1);
    if(CG_NitmodSnapshotRate()!=0) ++errors;
    CG_NitmodSnapshotRateUpdate(1001,150,200,1);
    if(CG_NitmodSnapshotRate()!=20) ++errors;
    CG_NitmodSnapshotRateUpdate(2002,200,240,1);
    if(CG_NitmodSnapshotRate()!=25) ++errors;
    CG_NitmodSnapshotRateUpdate(3003,240,240,1);
    if(CG_NitmodSnapshotRate()!=0) ++errors;
    CG_NitmodSnapshotRateUpdate(4004,240,230,1);
    if(CG_NitmodSnapshotRate()!=0) ++errors;
    CG_NitmodSnapshotRateUpdate(0,100,101,1);
    if(CG_NitmodSnapshotRate()!=0) ++errors;
    CG_NitmodSnapshotRateUpdate(1001,101,102,1);
    if(CG_NitmodSnapshotRate()!=1000) ++errors;
    CG_NitmodSnapshotRateUpdate(2002,102,103,0);
    if(CG_NitmodSnapshotRate()!=0) ++errors;
    CG_NitmodSnapshotRateReset();
    oldCg=cg; oldCgs=cgs;
    memset(&cg,0,sizeof(cg)); memset(&cgs,0,sizeof(cgs));
    cg.serverRespawning=qtrue; cg_nopredict.integer=0;
    dllEntry(LagometerEngine);
    for(mode=0;mode<3;++mode) for(size=0;size<4;++size)
    for(local=0;local<2;++local) for(enabled=0;enabled<2;++enabled) {
        float sy=sizes[size][1]/480.f, sx=mode ? sy : sizes[size][0]/640.f;
        float offset=mode ? sizes[size][0]-640*sx : 0;
        cgs.gameState.stringOffsets[CS_SERVERINFO]=1;
        strcpy(cgs.gameState.stringData+1,mode==2 ? "\\gamename\\nitmod\\nitmod_csLayout\\et260" :
            mode ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        cgs.glconfig.vidWidth=sizes[size][0]; cgs.glconfig.vidHeight=sizes[size][1];
        cgs.screenXScale=sizes[size][0]/640.f; cgs.screenYScale=sy;
        cgs.localServer=local; cgs.media.whiteShader=51; cgs.media.lagometerShader=52;
        cg_lagometer.integer=enabled; lagometerDraws=0;
        CG_NitmodHudAnchor(NITMOD_HUD_LEFT);
        CG_DrawLagometer(211);
        if(CG_NitmodHudAnchor(NITMOD_HUD_STRETCH)!=NITMOD_HUD_LEFT) ++errors;
        if(!enabled || (!mode && local)) { if(lagometerDraws) ++errors; continue; }
        if(!lagometerDraws || lagometerFirstShader!=(mode ? 51 : 52) ||
           fabs(lagometerFirstRect[0]-(592*sx+offset))>.01f ||
           fabs(lagometerFirstRect[1]-(mode ? 211 : 280)*sy)>.01f ||
           fabs(lagometerFirstRect[2]-48*sx)>.01f || fabs(lagometerFirstRect[3]-48*sy)>.01f) ++errors;
    }
    cg=oldCg; cgs=oldCgs; cg_lagometer=oldLag; cg_nopredict=oldPredict;
    CG_NitmodHudAnchor(oldAnchor); dllEntry(Engine);
    if(errors) fprintf(stderr,"lagometer layout: %d errors\n",errors);
    return errors;
}
