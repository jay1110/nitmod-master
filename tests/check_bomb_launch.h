/* Real throw adapter, with only the engine collision query substituted. */
extern vec3_t forward, muzzleEffect;
static int bombTraceMode, bombTraceCount, bombTraceErrors, bombTraceWeapon;
static vec3_t bombTraceEnd;
static int QDECL BombLaunchSyscall(int command, ...) {
    va_list args;
    trace_t *trace;
    const float *start, *mins, *maxs, *end;
    int owner, mask, box = bombTraceWeapon == WP_BOMB ? 12 : 4;
    if(command != G_TRACE) { fprintf(stderr,"bomb launch syscall %d\n",command); exit(2); }
    va_start(args,command);
    trace=va_arg(args,trace_t *); start=va_arg(args,const float *);
    mins=va_arg(args,const float *); maxs=va_arg(args,const float *);
    end=va_arg(args,const float *); owner=va_arg(args,int); mask=va_arg(args,int);
    va_end(args);
    if(mins[0] != -box || mins[1] != -box || mins[2] != 0 ||
       maxs[0] != box || maxs[1] != box || maxs[2] != (box == 12 ? 20 : 6) ||
       owner != 3 || mask != MASK_MISSILESHOT) ++bombTraceErrors;
    memset(trace,0,sizeof(*trace));
    trace->fraction=1; VectorCopy(end,trace->endpos);
    if(bombTraceMode == 1 && !bombTraceCount) trace->startsolid=qtrue;
    if(bombTraceMode == 2 || (bombTraceMode == 1 && bombTraceCount)) {
        trace->fraction=.5f;
        VectorAdd(start,end,trace->endpos); VectorScale(trace->endpos,.5f,trace->endpos);
    }
    VectorCopy(trace->endpos,bombTraceEnd); ++bombTraceCount;
    return 0;
}
static int CheckBombLaunch(void) {
    static gclient_t client;
    gentity_t actor, saved=g_entities[MAX_CLIENTS], *missile;
    vec3_t savedForward, savedMuzzle, direction;
    const int pitches[]={-90,-30,-15,0,30,90};
    int oldTime=level.time, oldCount=level.num_entities, i, w, errors=0;
    vmCvar_t oldKick=g_canisterKick, oldDamage=g_damageweapons;
    VectorCopy(forward,savedForward); VectorCopy(muzzleEffect,savedMuzzle);
    memset(&client,0,sizeof(client)); memset(&actor,0,sizeof(actor));
    actor.client=&client; actor.s.number=3; actor.s.groundEntityNum=ENTITYNUM_NONE;
    client.sess.sessionTeam=TEAM_AXIS; client.ps.viewheight=40;
    VectorSet(actor.s.pos.trBase,100,200,300); VectorCopy(actor.s.pos.trBase,actor.r.currentOrigin);
    VectorSet(muzzleEffect,106,200,336);
    level.time=1000; level.num_entities=MAX_CLIENTS+1;
    g_canisterKick.integer=g_damageweapons.integer=0;
    dllEntry(BombLaunchSyscall); bombTraceErrors=0;
    for(w=0;w<2;++w) for(i=0;i<6;++i) for(bombTraceMode=0;bombTraceMode<3;++bombTraceMode) {
        float pitch=(float)pitches[i], boost, elevation, expectedSpeed;
        memset(&g_entities[MAX_CLIENTS],0,sizeof(gentity_t));
        actor.s.apos.trBase[PITCH]=pitch;
        AngleVectors(actor.s.apos.trBase,forward,NULL,NULL);
        if(pitch >= 0) boost=1.3f;
        else boost=1+(1-min(-pitch,30)/30)*.3f;
        elevation=max(.1f,(max(-50,min(-pitch,50)) / 100)+.5f);
        expectedSpeed=elevation*900*boost;
        bombTraceWeapon=w ? WP_BOMB : WP_GRENADE_LAUNCHER;
        bombTraceCount=0;
        missile=weapon_grenadelauncher_fire(&actor,bombTraceWeapon);
        VectorCopy(missile->s.pos.trDelta,direction);
        if(fabs(VectorLength(direction)-expectedSpeed)>3 ||
           bombTraceCount != (bombTraceMode == 1 ? 2 : 1) ||
           missile->damage || missile->s.effect1Time != w ||
           missile->s.weapon != bombTraceWeapon || missile->parent != &actor ||
           missile->think != G_ExplodeMissile || missile->nextthink != 3500) ++errors;
        if(bombTraceMode != 2 && !VectorCompare(missile->r.currentOrigin,bombTraceEnd)) ++errors;
    }
    errors+=bombTraceErrors;
    g_entities[MAX_CLIENTS]=saved; level.time=oldTime; level.num_entities=oldCount;
    g_canisterKick=oldKick; g_damageweapons=oldDamage;
    VectorCopy(savedForward,forward); VectorCopy(savedMuzzle,muzzleEffect);
    dllEntry(EngineCallback);
    printf("Bomb/grenade launch: 36 pitch/collision profiles, %d errors\n",errors);
    return errors;
}
