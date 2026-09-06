#include "../src_2.60/cgame/cg_nitmod_hints.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
cg_t cg;
cgs_t cgs;
vmCvar_t cg_draw2D;
vmCvar_t cg_drawCrosshair, cg_drawCrosshairNames;
static int labels, bars;
static float expectedFraction;
static nitmodHudAnchor_t anchor = NITMOD_HUD_RIGHT;
nitmodHudAnchor_t CG_NitmodHudAnchor(nitmodHudAnchor_t next) {
    nitmodHudAnchor_t old = anchor; anchor = next; return old;
}
int CG_Text_Width_Ext(const char *text, float scale, int limit, fontInfo_t *font) { return 40; }
void CG_Text_Paint_Ext(float x, float y, float sx, float sy, vec4_t color,
    const char *text, float adjust, int limit, int style, fontInfo_t *font) {
    assert(anchor == NITMOD_HUD_CENTER && x == 300 && y == 182);
    assert(!strcmp(text, "Owner^7's dynamite")); ++labels;
}
void CG_FilledBar(float x, float y, float w, float h, float *start,
    float *end, const float *background, float fraction, int flags) {
    assert(anchor == NITMOD_HUD_CENTER && x == 290 && y == 193 && w == 60 && h == 7);
    assert(fabs(fraction - expectedFraction) < .0001f && flags == 16); ++bars;
}
void QDECL Com_Error(int level, const char *format, ...) { abort(); }
void QDECL Com_Printf(const char *format, ...) { abort(); }
#undef vsnprintf
int Q_vsnprintf(char *out, int size, const char *format, va_list args) { return vsnprintf(out, size, format, args); }
static int mode;
qboolean NITMOD_UsesNitmodHud(void) { return mode != 0; }
qboolean NITMOD_UsesOriginalProtocol(void) { return mode == 2; }
void CG_Trace(trace_t *t, const vec3_t start, const vec3_t mins, const vec3_t maxs,
    const vec3_t end, int skip, int mask) { VectorClear(t->endpos); }
int main(void) {
    static snapshot_t snap;
    static refdef_t view;
    static centity_t ent;
    cg.snap = &snap; cg.refdef_current = &view; cg_draw2D.integer = 1;
    cgs.clientinfo[0].team = TEAM_AXIS;
    ent.currentState.eType = ET_MISSILE; ent.currentState.weapon = WP_DYNAMITE;
    ent.currentState.number = MAX_CLIENTS; ent.currentState.teamNum = TEAM_AXIS;
    ent.currentState.clientNum = 7;
    ent.currentState.time = 45000; ent.currentState.time2 = 30000;
    cgs.clientinfo[7].infoValid = qtrue;
    strcpy(cgs.clientinfo[7].name, "Owner");
    cg_drawCrosshairNames.integer = 1;
    for(mode = 0; mode <= 2; ++mode) {
        CG_NitmodHintsReset();
        assert(!!CG_NitmodScanDynamite(&ent) == !!mode);
        if(mode) {
            assert(dynamiteHint.state.clientNum == 7);
            assert(dynamiteHint.state.time2 == (mode == 2 ? 30000 : 45000));
            assert(ent.currentState.time2 == 30000);
            expectedFraction = 1; labels = bars = 0;
            assert(CG_NitmodDrawDynamiteHint());
            assert(labels == 1 && bars == 1 && anchor == NITMOD_HUD_RIGHT);
            assert(!CG_NitmodDrawDynamiteHint());
            cg.time = mode == 2 ? 15000 : 22500;
            assert(CG_NitmodScanDynamite(&ent));
            expectedFraction = .5f;
            assert(CG_NitmodDrawDynamiteHint());
            assert(bars == 2 && anchor == NITMOD_HUD_RIGHT);
            ent.currentState.teamNum = TEAM_AXIS + 4;
            assert(CG_NitmodScanDynamite(&ent));
            assert(CG_NitmodDrawDynamiteHint() && bars == 2);
            cg.time += 1000;
            assert(!CG_NitmodDrawDynamiteHint());
            cg.time = 0; ent.currentState.teamNum = TEAM_AXIS;
        }
    }
    ent.currentState.weapon = WP_LANDMINE;
    ent.currentState.otherEntityNum = 9;
    ent.currentState.otherEntityNum2 = 1;
    for(mode = 0; mode <= 2; ++mode) {
        CG_NitmodHintsReset();
        assert(!!CG_NitmodScanMine(&ent) == !!mode);
        if(mode) assert(mineOwner == (mode == 2 ? 9 : 7));
        ent.currentState.teamNum = TEAM_AXIS + 4;
        assert(!CG_NitmodScanMine(&ent));
        ent.currentState.teamNum = TEAM_AXIS;
        cgs.clientinfo[0].team = TEAM_ALLIES;
        assert(!CG_NitmodScanMine(&ent));
        cgs.clientinfo[0].team = TEAM_AXIS;
    }
    puts("WASM explosive hints: fuse drawing, original/native mine owners and team/armed gates passed");
    return 0;
}
