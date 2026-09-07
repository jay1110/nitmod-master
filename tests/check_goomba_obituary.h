static char goombaObituaryText[1024];
static int QDECL GoombaObituarySyscall(int command, ...) {
    va_list args;
    va_start(args,command);
    if(command == CG_PRINT) Q_strncpyz(goombaObituaryText,va_arg(args,const char *),sizeof(goombaObituaryText));
    else if(command == CG_TRANSLATE_STRING) {
        const char *input=va_arg(args,const char *);
        char *out=va_arg(args,char *); strcpy(out,input);
    } else { fprintf(stderr,"goomba obituary syscall %d\n",command); exit(2); }
    va_end(args); return 0;
}
static int CheckGoombaObituary(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    static snapshot_t snap;
    centity_t cent;
    vec3_t position={0,0,0};
    int marker, errors=0, savedDebug=cg_debugEvents.integer;
    savedCg=cg; savedCgs=cgs;
    memset(&cent,0,sizeof(cent)); memset(&snap,0,sizeof(snap));
    cg.snap=&snap; snap.ps.clientNum=3;
    cgs.gameState.stringOffsets[CS_SERVERINFO]=1;
    strcpy(cgs.gameState.stringData+1,"\\gamename\\etmain");
    strcpy(cgs.clientinfo[1].name,"Victim"); strcpy(cgs.clientinfo[2].name,"Attacker");
    cgs.clientinfo[1].team=TEAM_AXIS; cgs.clientinfo[2].team=TEAM_ALLIES;
    cg_debugEvents.integer=0;
    cent.currentState.number=100; cent.currentState.event=EV_OBITUARY;
    cent.currentState.eventParm=MOD_CRUSH;
    cent.currentState.otherEntityNum=1; cent.currentState.otherEntityNum2=2;
    dllEntry(GoombaObituarySyscall);
    for(marker=0;marker<4;++marker) {
        const char *expected=marker<2?(marker?"was stomped by":"was crushed"):(marker==3?"was pushed too far by":"fell to his death");
        CG_InitPM(); goombaObituaryText[0]=0;
        cent.currentState.eventParm=marker<2?MOD_CRUSH:MOD_FALLING;
        cent.currentState.effect3Time=marker==1?NITMOD_OBITUARY_GOOMBA:marker==3?NITMOD_OBITUARY_SHOVE:0;
        CG_EntityEvent(&cent,position);
        if(!strstr(goombaObituaryText,expected) ||
           !strstr(goombaObituaryText,"Victim") ||
           ((marker&1) && !strstr(goombaObituaryText,"Attacker"))) {
            fprintf(stderr,"goomba obituary marker=%d text=[%s]\n",marker,goombaObituaryText); ++errors;
        }
    }
    if(CG_NitmodDeathCause(62)!=MOD_SHOVE) ++errors;
    for(marker=0;marker<4;++marker) {
        static const char *expected[]={"was scared to death by","was killed (Censor)","Throwing Knife","gibbed himself"};
        CG_InitPM();goombaObituaryText[0]=0;
        cent.currentState.eventParm=MOD_UNKNOWN;
        cent.currentState.effect3Time=NITMOD_OBITUARY_EXTRA+marker;
        cent.currentState.otherEntityNum2=(marker&1)?1:2;
        CG_EntityEvent(&cent,position);
        if(!strstr(goombaObituaryText,expected[marker])) {
            fprintf(stderr,"extended obituary %d text=[%s]\n",marker,goombaObituaryText);++errors;
        }
    }
    /* Lua event identity must also select original damage causes on ET servers. */
    CG_InitPM();goombaObituaryText[0]=0;
    cent.currentState.event=EV_NITMOD_LUA_FIRST+56;
    cent.currentState.eventParm=63;cent.currentState.effect3Time=0;
    cent.currentState.otherEntityNum2=2;
    CG_NativeEntityEvent(&cent,position);
    if(!strstr(goombaObituaryText,"Throwing Knife") || cent.currentState.event!=EV_NITMOD_LUA_FIRST+56) ++errors;
    CG_InitPM(); cg=savedCg; cgs=savedCgs; cg_debugEvents.integer=savedDebug;
    dllEntry(Engine);
    return errors;
}
