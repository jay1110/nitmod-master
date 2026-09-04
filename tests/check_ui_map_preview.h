extern void UI_DrawMapCinematic(rectDef_t *,float,vec4_t,qboolean);
extern void UI_DrawMapPreview(rectDef_t *,float,vec4_t,qboolean);
extern vmCvar_t ui_currentMap, ui_currentNetMap, ui_gameType, ui_netGameType;
static int mapStarts, mapRuns, mapDraws, mapExtents, mapFallback, mapWrites, mapFailure;
static int QDECL MapPreviewSyscall(int command, ...) {
    va_list args;
    int result=0,i;
    va_start(args,command);
    switch(command) {
    case UI_CIN_PLAYCINEMATIC:
        if(strcmp(va_arg(args,const char *),"oasis.roq")) exit(2);
        for(i=0;i<4;++i) if(va_arg(args,int)) exit(2);
        if(va_arg(args,int)!=(CIN_loop|CIN_silent)) exit(2);
        ++mapStarts; result=mapFailure ? -1 : 42; break;
    case UI_CIN_RUNCINEMATIC: if(va_arg(args,int)!=42) exit(2); ++mapRuns; break;
    case UI_CIN_DRAWCINEMATIC: if(va_arg(args,int)!=42) exit(2); ++mapDraws; break;
    case UI_CIN_SETEXTENTS:
        if(va_arg(args,int)!=42 || va_arg(args,int)!=10 || va_arg(args,int)!=20 ||
           va_arg(args,int)!=100 || va_arg(args,int)!=60) exit(2);
        ++mapExtents; break;
    case UI_R_REGISTERSHADERNOMIP:
        if(strcmp(va_arg(args,const char *),"levelshots/unknownmap")) exit(2);
        ++mapFallback; result=77; break;
    case UI_R_DRAWSTRETCHPIC: break;
    case UI_CVAR_SET:
        { const char *name=va_arg(args,const char *);
          if(strcmp(name,"ui_currentMap") && strcmp(name,"ui_currentNetMap")) exit(2);
          if(strcmp(va_arg(args,const char *),"0")) exit(2);
          ++mapWrites; } break;
    default: fprintf(stderr,"map preview syscall %d\n",command); exit(2);
    }
    va_end(args); return result;
}
static int CheckMapPreview(void) {
    static uiInfo_t saved;
    vmCvar_t local=ui_currentMap,netmap=ui_currentNetMap,game=ui_gameType,netgame=ui_netGameType;
    rectDef_t rect={10,20,100,60}; vec4_t color={1,1,1,1};
    int net,mode,frame,errors=0;
    saved=uiInfo; dllEntry(MapPreviewSyscall);
    for(net=0;net<2;++net) for(mode=0;mode<7;++mode) {
        memset(&uiInfo,0,sizeof(uiInfo));
        uiInfo.numGameTypes=1; uiInfo.gameTypes[0].gtEnum=GT_WOLF;
        uiInfo.mapCount=1; uiInfo.mapList[0].mapLoadName="oasis";
        uiInfo.mapList[0].cinematic=-1;
        ui_gameType.integer=0; ui_netGameType.integer=GT_WOLF;
        ui_currentMap.integer=ui_currentNetMap.integer=mode==2 ? 1 : 0;
        if(mode==3) uiInfo.mapCount=0;
        if(mode==4) uiInfo.mapCount=MAX_MAPS+1;
        if(mode==5) uiInfo.gameTypes[0].gtEnum=ui_netGameType.integer=GT_WOLF_CAMPAIGN;
        if(mode==6) ui_gameType.integer=MAX_GAMETYPES;
        mapFailure=mode==1;
        mapStarts=mapRuns=mapDraws=mapExtents=mapFallback=mapWrites=0;
        for(frame=0;frame<3;++frame) UI_DrawMapCinematic(&rect,1,color,net);
        if(mode==0 || mode==2 || (mode==6 && net)) {
            if(mapStarts!=1 || mapRuns!=3 || mapDraws!=3 || mapExtents!=3 || mapFallback || mapWrites!=(mode==2)) ++errors;
        } else if(mode==1) {
            if(mapStarts!=1 || mapRuns || mapDraws || mapFallback!=2 || uiInfo.mapList[0].cinematic!=-2) ++errors;
        } else if(mapStarts || mapRuns || mapFallback!=3 || mapWrites) ++errors;
    }
    memset(&uiInfo,0,sizeof(uiInfo)); uiInfo.campaignCount=1; uiInfo.mapCount=1;
    ui_currentNetMap.integer=0; ui_netGameType.integer=GT_WOLF_CAMPAIGN;
    uiInfo.campaignList[0].mapTC[0][0]=1; uiInfo.campaignList[0].mapTC[1][0]=650;
    uiInfo.campaignList[0].mapCount=MAX_MAPS_PER_CAMPAIGN+1;
    /* Null and non-catalog references must never be dereferenced. */
    uiInfo.campaignList[0].mapInfos[0]=&saved.mapList[0];
    mapStarts=mapRuns=mapDraws=mapFallback=0;
    UI_DrawMapPreview(&rect,1,color,qtrue);
    if(mapStarts || mapRuns || mapDraws || mapFallback) ++errors;
    uiInfo=saved; ui_currentMap=local; ui_currentNetMap=netmap; ui_gameType=game; ui_netGameType=netgame;
    return errors;
}
