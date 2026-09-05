static int entitySoundCalls, entitySoundClock, entitySoundKind;
static int entitySoundRange, entitySoundHandle, entitySoundVolume, entitySoundTime;
static vec3_t entitySoundOrigin;
static int QDECL EntitySoundEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == CG_S_GETCURRENTSOUNDTIME) { ++entitySoundClock; va_end(args); return 1234; }
    if(command == CG_S_ADDLOOPINGSOUND || command == CG_S_ADDREALLOOPINGSOUND) {
        const float *origin = va_arg(args, const float *);
        VectorCopy(origin, entitySoundOrigin);
        (void)va_arg(args, const float *);
        entitySoundRange = va_arg(args, int);
        entitySoundHandle = va_arg(args, int);
        entitySoundVolume = va_arg(args, int);
        entitySoundTime = va_arg(args, int);
    } else if(command == CG_S_STARTSOUND) {
        (void)va_arg(args, const float *); (void)va_arg(args, int); (void)va_arg(args, int);
        entitySoundHandle = va_arg(args, int);
    } else if(command == CG_S_UPDATEENTITYPOSITION) {
        const float *origin;
        (void)va_arg(args, int); origin = va_arg(args, const float *);
        VectorCopy(origin, entitySoundOrigin);
    } else { va_end(args); exit(2); }
    entitySoundKind = command; ++entitySoundCalls;
    va_end(args); return 0;
}

static int CheckEntitySound(void) {
    sfxHandle_t saved[MAX_SOUNDS];
    vec3_t midpoint;
    centity_t cent;
    int index, type, pass, errors = 0, savedTime = cg.time;
    memcpy(saved, cgs.gameSounds, sizeof(saved));
    VectorCopy(cgs.inlineModelMidpoints[1], midpoint);
    VectorSet(cgs.inlineModelMidpoints[1], 10, 20, 30);
    dllEntry(EntitySoundEngine);
    for(index = -1; index <= MAX_SOUNDS; ++index) for(type = 0; type < 4; ++type) {
        memset(&cent, 0, sizeof(cent));
        if(index >= 0 && index < MAX_SOUNDS) cgs.gameSounds[index] = 777;
        cent.currentState.loopSound = index;
        cent.currentState.eType = type == 0 ? ET_SPEAKER : type == 1 ? ET_MOVER : ET_GENERAL;
        cent.currentState.solid = type == 2 ? SOLID_BMODEL : 0;
        cent.currentState.modelindex = 1;
        cent.currentState.onFireStart = 99;
        VectorSet(cent.lerpOrigin, 1, 2, 3);
        entitySoundCalls = entitySoundClock = 0;
        for(pass = 0; pass < 2; ++pass) {
            cent.currentState.dmgFlags = pass ? 2000 : 0;
            CG_EntityLoopSound(&cent);
            if(index <= 0 || index >= MAX_SOUNDS) {
                if(entitySoundCalls || entitySoundClock || cent.soundTime) ++errors;
            } else if(entitySoundCalls != pass + 1 || entitySoundClock != 1 ||
                entitySoundHandle != 777 || entitySoundTime != 1234 ||
                entitySoundVolume != (type == 3 ? 255 : 99) ||
                entitySoundKind != (type == 0 ? CG_S_ADDREALLOOPINGSOUND : CG_S_ADDLOOPINGSOUND) ||
                entitySoundRange != (type == 0 && pass ? 2000 : 1250) ||
                entitySoundOrigin[0] != (type == 2 ? 11 : 1)) ++errors;
        }
        cent.currentState.loopSound = 0; CG_EntityLoopSound(&cent);
        if(cent.soundTime) ++errors;
    }
    memset(&cent, 0, sizeof(cent));
    cent.currentState.loopSound = 1; cent.currentState.solid = SOLID_BMODEL;
    cent.currentState.modelindex = MAX_MODELS; cent.soundTime = 99;
    entitySoundCalls = entitySoundClock = 0;
    CG_EntityLoopSound(&cent); CG_SetEntitySoundPosition(&cent);
    if(entitySoundCalls || entitySoundClock || cent.soundTime) ++errors;
    cent.currentState.solid = 0; cent.currentState.clientNum = 1;
    cent.currentState.frame = 10; cent.currentState.eventParm = 1;
    cg.time = 1000; CG_Speaker(&cent);
    if(entitySoundCalls != 1 || entitySoundHandle != 777 || cent.miscTime < 1900 || cent.miscTime > 2100) ++errors;
    CG_Speaker(&cent); if(entitySoundCalls != 1) ++errors;
    cent.miscTime = 0; cent.currentState.eventParm = MAX_SOUNDS;
    CG_Speaker(&cent); if(entitySoundCalls != 1) ++errors;
    cgs.gameSounds[1] = -1; if(CG_GetGameSound(1)) ++errors;
    CG_EntityLoopSound(NULL); CG_Speaker(NULL); CG_SetEntitySoundPosition(NULL);
    memcpy(cgs.gameSounds, saved, sizeof(saved));
    VectorCopy(midpoint, cgs.inlineModelMidpoints[1]); cg.time = savedTime;
    dllEntry(Engine);
    return errors;
}

static int nitmodEventSoundCalls, nitmodEventSoundEntity, nitmodEventSoundHandle;
static int QDECL NitmodEventSoundEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == CG_S_STARTSOUNDVCONTROL) {
        (void)va_arg(args, const float *);
        nitmodEventSoundEntity = va_arg(args, int);
        (void)va_arg(args, int);
        nitmodEventSoundHandle = va_arg(args, int);
        (void)va_arg(args, int);
        ++nitmodEventSoundCalls;
    } else { va_end(args); exit(2); }
    va_end(args); return 0;
}

static int CheckNitmodEventSound(void) {
    centity_t cent;
    sfxHandle_t saved = cgs.gameSounds[5];
    int errors = 0;
    memset(&cent, 0, sizeof(cent));
    cent.currentState.number = 17;
    cent.currentState.eventParm = 5;
    cgs.gameSounds[5] = 731;
    dllEntry(NitmodEventSoundEngine);
    nitmodEventSoundCalls = 0;
    if(!CG_NitmodExtendedEvent(&cent, 100) || nitmodEventSoundCalls != 1 ||
       nitmodEventSoundEntity != 17 || nitmodEventSoundHandle != 731) ++errors;
    if(!CG_NitmodExtendedEvent(&cent, EV_NITMOD_SOUND) || nitmodEventSoundCalls != 2) ++errors;
    cent.currentState.eventParm = MAX_SOUNDS;
    if(!CG_NitmodExtendedEvent(&cent, 100) || nitmodEventSoundCalls != 2) ++errors;
    cgs.gameSounds[5] = saved;
    dllEntry(Engine);
    if(errors) fprintf(stderr, "Nitmod event sound failures: %d\n", errors);
    return errors;
}
