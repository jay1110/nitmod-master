#include "../src_2.60/cgame/cg_nitmod_coronas.h"
extern void CG_ParseEntityFromSpawnVars(void);
static int coronaPVS, coronaBlocked, coronaTraces, coronaDraws, coronaErrors;
static int QDECL CoronaEngine(int command, ...) {
    va_list args;
    int result = 0;
    va_start(args, command);
    if(command == CG_R_INPVS) result = coronaPVS;
    else if(command == CG_CM_BOXTRACE) {
        trace_t *trace = va_arg(args, trace_t *);
        int i;
        for(i = 0; i < 4; ++i) (void)va_arg(args, const float *);
        if(va_arg(args, int) != 0 || va_arg(args, int) != (MASK_SOLID | CONTENTS_BODY)) ++coronaErrors;
        memset(trace, 0, sizeof(*trace)); trace->fraction = coronaBlocked ? .5f : 1;
        ++coronaTraces;
    } else if(command == CG_R_ADDCORONATOSCENE) {
        const float *origin = va_arg(args, const float *);
        const float expected[] = {.2f, .4f, .6f, 2};
        int i;
        if(origin[0] != 100 || origin[1] || origin[2]) ++coronaErrors;
        for(i = 0; i < 4; ++i) {
            union { int bits; float value; } arg;
            arg.bits = va_arg(args, int);
            if(fabs(arg.value - expected[i]) > .00001f) ++coronaErrors;
        }
        if(va_arg(args, int) != 0 || va_arg(args, int) != !coronaBlocked) ++coronaErrors;
        ++coronaDraws;
    } else if(command != CG_PRINT) { fprintf(stderr, "Unexpected corona syscall %d\n", command); exit(2); }
    va_end(args); return result;
}
static void CoronaSpawnVar(char *key, char *value) {
    cg.spawnVars[cg.numSpawnVars][0] = key;
    cg.spawnVars[cg.numSpawnVars++][1] = value;
}
static int CheckMapCoronas(void) {
    static cg_t savedCg;
    static snapshot_t emptySnapshot;
    gameState_t savedGame = cgs.gameState;
    vmCvar_t savedMode = cg_coronas, savedDistance = cg_coronafardist;
    refdef_t view;
    const nitmodMapCorona_t *value;
    char *excluded[] = {"targetname", "scriptname", "spawnflags"};
    char *bad[] = {"", "1 2", "1 2 3 trailing", "nan 2 3", "1e99 2 3"};
    int i, mode, angle, far, pvs, blocked, expected, errors = 0;
    savedCg = cg; cg.snap = &emptySnapshot; cg.nextSnap = NULL; CG_BuildSolidList();
    dllEntry(CoronaEngine); CG_NitmodResetCoronas();
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cg.spawning = qtrue;
    cg.numSpawnVars = 0; CoronaSpawnVar("classname", "corona");
    CG_ParseEntityFromSpawnVars();
    value = CG_NitmodCorona(0);
    if(CG_NitmodCoronaCount() != 1 || !value || value->scale != 1 ||
       VectorLength(value->origin) || VectorLength(value->color)) ++errors;
    for(i = 0; i < 3; ++i) {
        CG_NitmodResetCoronas(); cg.numSpawnVars = 1; CoronaSpawnVar(excluded[i], "0");
        CG_ParseEntityFromSpawnVars(); if(CG_NitmodCoronaCount()) ++errors;
    }
    for(i = 0; i < 5; ++i) {
        cg.numSpawnVars = 1; CoronaSpawnVar("origin", bad[i]);
        CG_ParseEntityFromSpawnVars(); if(CG_NitmodCoronaCount()) ++errors;
    }
    cg.numSpawnVars = 1; CoronaSpawnVar("origin", "100 0 0");
    CoronaSpawnVar("scale", "2"); CoronaSpawnVar("color", "1 1 1");
    CoronaSpawnVar("_color", ".2 .4 .6"); CG_ParseEntityFromSpawnVars();
    value = CG_NitmodCorona(0);
    if(!value || value->color[0] != .2f || CG_NitmodCorona(-1) || CG_NitmodCorona(1)) ++errors;
    memset(&view, 0, sizeof(view)); cg.refdef_current = &view;
    for(mode = 0; mode < 4; ++mode) for(angle = 0; angle < 3; ++angle)
    for(far = 0; far < 2; ++far) for(pvs = 0; pvs < 2; ++pvs) for(blocked = 0; blocked < 2; ++blocked) {
        cg_coronas.integer = mode; cg_coronafardist.integer = far ? 99 : 100;
        VectorSet(view.viewaxis[0], angle == 0 ? 1 : angle == 1 ? 0 : -1, 0, 0);
        coronaPVS = pvs; coronaBlocked = blocked; coronaTraces = coronaDraws = coronaErrors = 0;
        CG_NitmodDrawCoronas();
        expected = mode && pvs && (mode == 2 || (!angle && !far));
        if(coronaErrors || coronaTraces != expected || coronaDraws != expected) ++errors;
    }
    for(i = 1; i < NITMOD_MAX_MAP_CORONAS + 2; ++i) CG_ParseEntityFromSpawnVars();
    if(CG_NitmodCoronaCount() != NITMOD_MAX_MAP_CORONAS || !CG_NitmodCorona(1023) || CG_NitmodCorona(1024)) ++errors;
    CG_NitmodResetCoronas(); if(CG_NitmodCoronaCount() || CG_NitmodCorona(0)) ++errors;
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\etmain");
    CG_ParseEntityFromSpawnVars(); if(CG_NitmodCoronaCount()) ++errors;
    cg = savedCg; cgs.gameState = savedGame; cg_coronas = savedMode; cg_coronafardist = savedDistance;
    if(cg.snap) CG_BuildSolidList();
    dllEntry(Engine);
    if(errors) fprintf(stderr, "Map corona failures: %d\n", errors);
    return errors;
}
