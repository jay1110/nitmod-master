extern int localEntCount;
static int debugEventDraws, debugEventErrors;
static int QDECL DebugEventEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == CG_R_ADDREFENTITYTOSCENE) {
        const refEntity_t *re = va_arg(args, const refEntity_t *);
        if(re->reType != RT_RAIL_CORE || re->customShader != 123 || re->shaderRGBA[3] != 127) ++debugEventErrors;
        ++debugEventDraws;
    } else if(command == CG_R_REGISTERSHADER) {
        if(strcmp(va_arg(args, const char *), "railCore")) ++debugEventErrors;
        va_end(args); return 123;
    } else if(command != CG_MILLISECONDS) { fprintf(stderr, "Unexpected debug event syscall %d\n", command); exit(2); }
    va_end(args); return 0;
}
static int CheckDebugEvents(void) {
    centity_t cent;
    nitmodDebugLine_t lines[12];
    int color, event, i, j, count, errors = 0, time = cg.time;
    qhandle_t shader = cgs.media.railCoreShader;
    vmCvar_t duration = cg_railTrailTime;
    memset(&cent, 0, sizeof(cent));
    VectorSet(cent.currentState.pos.trBase, 10, 20, 30);
    VectorSet(cent.currentState.origin2, 1, 0, 0);
    VectorSet(cent.currentState.angles, 0, 1, 0);
    VectorSet(cent.currentState.angles2, 0, 0, 1);
    cent.currentState.effect1Time = 5; cent.currentState.effect2Time = 7; cent.currentState.effect3Time = 9;
    for(color = -1; color <= 32; ++color) {
        cent.currentState.otherEntityNum = color;
        count = CG_NitmodDebugEventLines(&cent.currentState, 106, lines);
        if(count != 12) ++errors;
        for(i = 0; i < count; ++i) {
            int differences = 0;
            for(j = 0; j < 3; ++j) {
                float center = cent.currentState.pos.trBase[j], half = (float)(j + 2);
                if(lines[i].color[j] != g_color_table[color < 0 ? 0 : color > 31 ? 31 : color][j]) ++errors;
                if(fabs(lines[i].start[j] - center) != half || fabs(lines[i].end[j] - center) != half) ++errors;
                if(lines[i].start[j] != lines[i].end[j]) ++differences;
            }
            if(differences != 1) ++errors;
        }
    }
    count = CG_NitmodDebugEventLines(&cent.currentState, 105, lines);
    if(count != 3) ++errors;
    for(i = 0; i < 3; ++i) for(j = 0; j < 3; ++j)
        if(lines[i].start[j] != cent.currentState.pos.trBase[j] ||
           lines[i].end[j] != cent.currentState.pos.trBase[j] + (i == j ? 5 : 0) ||
           lines[i].color[j] != (i == j)) ++errors;
    if(CG_NitmodDebugEventLines(&cent.currentState, 104, lines) != 1 ||
       memcmp(lines[0].start, cent.currentState.origin2, sizeof(vec3_t)) ||
       memcmp(lines[0].end, cent.currentState.pos.trBase, sizeof(vec3_t))) ++errors;
    VectorSet(cent.currentState.origin2, 0, 1, 0);
    VectorSet(cent.currentState.angles, -1, 0, 0);
    count = CG_NitmodDebugEventLines(&cent.currentState, 106, lines);
    if(count != 12) ++errors;
    for(i = 0; i < count; ++i) for(j = 0; j < 3; ++j) {
        float half = j == 0 ? 3 : j == 1 ? 2 : 4;
        if(fabs(lines[i].start[j] - cent.currentState.pos.trBase[j]) != half ||
           fabs(lines[i].end[j] - cent.currentState.pos.trBase[j]) != half) ++errors;
    }
    dllEntry(DebugEventEngine); cg_railTrailTime.value = 100;
    cgs.media.railCoreShader = 0;
    for(event = 104; event <= 106; ++event) {
        CG_InitLocalEntities(); cg.time = 1000;
        count = event == 104 ? 1 : event == 105 ? 3 : 12;
        if(!CG_NitmodExtendedEvent(&cent, event) || localEntCount != count) ++errors;
        debugEventDraws = debugEventErrors = 0; cg.time = 1050; CG_AddLocalEntities();
        if(debugEventDraws != count || debugEventErrors) ++errors;
        cg.time = 1100; CG_AddLocalEntities(); if(localEntCount) ++errors;
    }
    cg_railTrailTime.value = 0; CG_NitmodDebugEvent(&cent.currentState, 106);
    if(localEntCount) ++errors;
    cent.currentState.effect1Time = -1;
    if(CG_NitmodDebugEventLines(&cent.currentState, 106, lines)) ++errors;
    if(CG_NitmodDebugEventLines(NULL, 104, lines) || CG_NitmodDebugEventLines(&cent.currentState, 103, lines)) ++errors;
    CG_InitLocalEntities(); cg.time = time; cg_railTrailTime = duration; cgs.media.railCoreShader = shader;
    dllEntry(Engine);
    if(errors) fprintf(stderr, "Debug event failures: %d\n", errors);
    return errors;
}
