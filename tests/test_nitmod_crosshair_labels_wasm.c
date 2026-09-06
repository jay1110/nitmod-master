#include "cg_local.h"
#include "cg_nitmod_hud.h"
#include "cg_nitmod_hints.h"
#include <assert.h>
#include <stdio.h>
cgs_t cgs;
centity_t cg_entities[MAX_GENTITIES];
vmCvar_t cg_drawCrosshairNames;
rankicon_t rankicons[NUM_EXPERIENCE_LEVELS][2];
static int player;
qboolean NITMOD_UsesOriginalProtocol(void);
static int mod, labels, bars;
static float expectedFraction;
static nitmodHudAnchor_t anchor = NITMOD_HUD_RIGHT;
qboolean NITMOD_UsesNitmodHud(void) { return mod != 0; }
qboolean NITMOD_UsesOriginalProtocol(void) { return mod == 2; }
skillType_t BG_ClassSkillForClass(int cls) { return SK_HEAVY_WEAPONS; }
void trap_R_SetColor(const float *color) { }
void CG_DrawPic(float x, float y, float w, float h, qhandle_t shader) {
    assert(anchor == NITMOD_HUD_CENTER && x == 300 && y == 170);
    assert(w == 14 && h == 14 && shader == 42);
}
nitmodHudAnchor_t CG_NitmodHudAnchor(nitmodHudAnchor_t value) {
    nitmodHudAnchor_t old = anchor; anchor = value; return old;
}
int CG_Text_Width_Ext(const char *text, float scale, int limit, fontInfo_t *font) { return 40; }
void CG_Text_Paint_Ext(float x, float y, float sx, float sy, vec4_t color,
    const char *text, float adjust, int limit, int style, fontInfo_t *font) {
    assert(anchor == NITMOD_HUD_CENTER && x == (player ? 316 : 300) && y == 182);
    assert(!strcmp(text, "Tank") && style == 7 && sx == .2f && sy == .2f);
    ++labels;
}
void CG_FilledBar(float x, float y, float w, float h, float *start,
    float *end, const float *background, float fraction, int flags) {
    assert(anchor == NITMOD_HUD_CENTER && x == 270 && y == 190 && w == 100 && h == 10);
    assert(fraction == expectedFraction && flags == 16); ++bars;
}
int main(void) {
    vec4_t color = {1, 1, 1, 1};
    int i;
    static const int health[] = {-1, 0, 50, 100, 200};
    for(mod = 0; mod < 3; ++mod) {
        labels = bars = 0;
        CG_NitmodDrawCrosshairLabel("Tank", color);
        assert(labels == (mod != 0) && anchor == NITMOD_HUD_RIGHT);
        for(i = 0; i < 5; ++i) {
            expectedFraction = health[i] <= 0 ? 0 : health[i] >= 100 ? 1 : .5f;
            CG_NitmodDrawCrosshairHealth(health[i], 100, color);
            assert(anchor == NITMOD_HUD_RIGHT);
        }
        assert(bars == (mod ? 5 : 0));
        CG_NitmodDrawCrosshairLabel(NULL, color);
        CG_NitmodDrawCrosshairHealth(50, 0, color);
        assert(labels == (mod != 0) && bars == (mod ? 5 : 0));
        player = 1;
        cg_drawCrosshairNames.integer = 1;
        cgs.clientinfo[0].infoValid = qtrue;
        cgs.clientinfo[0].cls = PC_SOLDIER;
        strcpy(cgs.clientinfo[0].name, "Tank");
        cgs.media.skillPics[SK_HEAVY_WEAPONS] = 42;
        expectedFraction = .5f;
        assert(CG_NitmodDrawCrosshairPlayer(0, qfalse, 50, 100, color) == (mod != 0));
        assert(anchor == NITMOD_HUD_RIGHT);
        assert(!CG_NitmodDrawCrosshairPlayer(MAX_CLIENTS, qfalse, 50, 100, color));
        if(mod != 2) assert(!CG_NitmodDrawCrosshairPlayer(0, qtrue, 50, 100, color));
        player = 0;
    }
    puts("WASM crosshair labels: Nitmod gate, placement, bar bounds and anchor restoration passed");
    return 0;
}
