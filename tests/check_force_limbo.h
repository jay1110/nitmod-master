static int forceLimboUnlinks;
static int QDECL ForceLimboSyscall(int command, ...) {
    if(command==G_UNLINKENTITY) { ++forceLimboUnlinks; return 0; }
    if(command==G_POINT_CONTENTS) return CONTENTS_NODROP;
    fprintf(stderr,"unexpected force-limbo syscall %d\n",command); exit(2);
    return 0;
}
static int CheckForceLimbo(void) {
    static level_locals_t savedLevel;
    static gclient_t client;
    gentity_t savedEntity=g_entities[0], attacker;
    vmCvar_t savedSetting=g_forceLimboHealth, savedState=g_gamestate;
    const int settings[]={0,1,50,75,100,175,-50,-75,INT_MIN,INT_MAX};
    int i, health, expected, errors=0;
    savedLevel=level; memset(&level,0,sizeof(level));
    memset(&attacker,0,sizeof(attacker)); attacker.s.number=ENTITYNUM_WORLD;
    level.time=1000; level.maxclients=1; level.clients=&client;
    g_gamestate.integer=GS_PLAYING;
    dllEntry(ForceLimboSyscall);
    for(i=0;i<sizeof(settings)/sizeof(settings[0]);++i) {
        int threshold=settings[i]>0 ? -settings[i] : settings[i] ? settings[i] : -75;
        if(G_NITMOD_ForceLimboThreshold(settings[i])!=threshold) ++errors;
        g_forceLimboHealth.integer=settings[i];
        for(health=-173;health<0;++health) {
            memset(&g_entities[0],0,sizeof(g_entities[0])); memset(&client,0,sizeof(client));
            g_entities[0].client=&client; g_entities[0].inuse=qtrue;
            g_entities[0].s.eType=ET_PLAYER; g_entities[0].health=health;
            g_entities[0].takedamage=qtrue;
            client.ps.pm_type=PM_DEAD; client.sess.sessionTeam=TEAM_AXIS;
            client.sess.playerType=PC_SOLDIER;
            client.ps.persistant[PERS_RESPAWNS_LEFT]=-1;
            level.redNumWaiting=0; forceLimboUnlinks=0;
            expected=health-1<threshold && health-1>GIB_HEALTH;
            G_Damage(&g_entities[0],&attacker,&attacker,NULL,NULL,1,DAMAGE_NO_PROTECTION,MOD_UNKNOWN);
            if(!!(client.ps.pm_flags&PMF_LIMBO)!=expected || forceLimboUnlinks!=expected ||
               level.redNumWaiting!=expected || g_entities[0].health!=health-1) ++errors;
        }
    }
    g_entities[0]=savedEntity; level=savedLevel;
    g_forceLimboHealth=savedSetting; g_gamestate=savedState;
    if(errors) fprintf(stderr,"force limbo: %d failures\n",errors);
    return errors;
}
