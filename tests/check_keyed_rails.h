static int CheckKeyedRails(void) {
    entityState_t es;
    localEntity_t *saved[12], *line;
    int i, pass, errors = 0, time = cg.time;
    vmCvar_t duration = cg_railTrailTime;
    qhandle_t shader = cgs.media.railCoreShader;
    memset(&es, 0, sizeof(es));
    VectorSet(es.origin2, 1, 2, 3);
    VectorSet(es.pos.trBase, 11, 22, 33);
    VectorSet(es.angles, 255, 128, 0);
    cg.time = 1000; cg_railTrailTime.value = 100;
    cgs.media.railCoreShader = 123;
    CG_InitLocalEntities();
    es.effect1Time = -27; es.dmgFlags = 1;
    CG_NitmodRailEvent(&es);
    if(localEntCount != 12) ++errors;
    for(i = 0; i < 12; ++i) {
        saved[i] = CG_NitmodFindRailEntity(-27, i + 1);
        if(!saved[i]) ++errors;
    }
    for(pass = 0; pass < 100; ++pass) {
        cg.time++;
        CG_NitmodRailEvent(&es);
        if(localEntCount != 12) ++errors;
        for(i = 0; i < 12; ++i) {
            line = CG_NitmodFindRailEntity(-27, i + 1);
            if(!line || line != saved[i] || line->startTime != cg.time ||
               line->endTime != cg.time + 100 || line->color[0] != 1 ||
               fabs(line->color[1] - 128.f / 255.f) > .00001 || line->color[2] != 0) ++errors;
        }
    }
    es.dmgFlags = 0;
    CG_NitmodRailEvent(&es);
    line = CG_NitmodFindRailEntity(-27, -1);
    if(localEntCount != 13 || !line || !VectorCompare(line->refEntity.origin, es.origin2) ||
       !VectorCompare(line->refEntity.oldorigin, es.pos.trBase)) ++errors;
    CG_FreeLocalEntity(line);
    if(CG_NitmodFindRailEntity(-27, -1)) ++errors;
    line = CG_AllocLocalEntity();
    if(line->nitmodRailGroup || line->nitmodRailSegment) ++errors;
    CG_FreeLocalEntity(line);
    es.effect1Time = 0;
    for(i = 0; i < 3; ++i) CG_NitmodRailEvent(&es);
    if(localEntCount != 15 || CG_NitmodFindRailEntity(0, -1)) ++errors;
    dllEntry(DebugEventEngine);
    cg.time += 100;
    CG_AddLocalEntities();
    if(localEntCount || CG_NitmodFindRailEntity(-27, 1)) ++errors;
    dllEntry(Engine);
    CG_InitLocalEntities();
    cg.time = time; cg_railTrailTime = duration; cgs.media.railCoreShader = shader;
    return errors;
}
