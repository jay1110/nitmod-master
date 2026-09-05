extern void CG_CheckLocalSounds(playerState_t *, playerState_t *);
static int roundSoundCount, roundSoundHandle;
static int QDECL RoundAnnouncementEngine(int command, ...) {
    va_list args;
    if(command!=CG_S_STARTLOCALSOUND) { fprintf(stderr,"unexpected round announcement syscall %d\n",command); exit(2); }
    va_start(args,command);
    roundSoundHandle=va_arg(args,int);
    if(va_arg(args,int)!=CHAN_ANNOUNCER) exit(2);
    ++roundSoundCount; va_end(args); return 0;
}
static int CheckRoundAnnouncements(void) {
    static cg_t savedCg;
    static cgs_t savedCgs;
    playerState_t ps;
    const int offsets[]={0,1,500,999,1000};
    const int times[]={300000,480000,570000};
    int mode,state,team,warning,edge,expected,errors=0;
    savedCg=cg; savedCgs=cgs; memset(&ps,0,sizeof(ps));
    dllEntry(RoundAnnouncementEngine);
    cgs.timelimit=10; cgs.levelStartTime=1000;
    cgs.media.fiveMinuteSound_g=11; cgs.media.fiveMinuteSound_a=12;
    cgs.media.twoMinuteSound_g=21; cgs.media.twoMinuteSound_a=22;
    cgs.media.thirtySecondSound_g=31; cgs.media.thirtySecondSound_a=32;
    for(mode=0;mode<=8;++mode) for(state=0;state<=5;++state)
    for(team=TEAM_FREE;team<=TEAM_SPECTATOR;++team) for(warning=0;warning<3;++warning)
    for(edge=0;edge<5;++edge) {
        int eligible=mode!=7 && mode!=8 && state==GS_PLAYING && edge>0 && edge<4;
        cgs.gametype=mode; cgs.gamestate=state; ps.persistant[PERS_TEAM]=team;
        cg.time=1000+times[warning]+offsets[edge]; cg.timelimitWarnings=0;
        roundSoundCount=roundSoundHandle=0;
        CG_CheckLocalSounds(&ps,&ps);
        expected=eligible && (team==TEAM_AXIS || team==TEAM_ALLIES);
        if(roundSoundCount!=expected || cg.timelimitWarnings!=(eligible ? 1<<warning : 0) ||
           (expected && roundSoundHandle!=(warning+1)*10+team)) ++errors;
        CG_CheckLocalSounds(&ps,&ps);
        if(roundSoundCount!=expected) ++errors;
    }
    cg=savedCg; cgs=savedCgs; dllEntry(Engine);
    if(errors) fprintf(stderr,"round announcements: %d failures\n",errors);
    return errors;
}
