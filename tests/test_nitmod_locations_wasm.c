#include "cg_local.h"
#include "cg_nitmod_locations.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void QDECL Com_Error(int level, const char *format, ...) { abort(); }
void QDECL Com_Printf(const char *format, ...) {}
#undef vsnprintf
int Q_vsnprintf(char *out, int size, const char *format, va_list args) {
    return vsnprintf(out, size, format, args);
}
vmCvar_t cg_locations;
vmCvar_t cg_draw2D;
cg_t cg;
cgs_t cgs;
static int markers, labels;
static qboolean visible = qtrue;
qboolean CG_NitmodProjectName(const vec3_t origin, float *x, float *y) {
    *x = 320; *y = 240; return qtrue;
}
void trap_R_AddRefEntityToScene(const refEntity_t *marker) {
    assert(marker->reType == RT_SPRITE);
    assert(marker->radius == 12); /* Near + 8 */
    ++markers;
}
qboolean CG_NitmodQueueLocationName(int index, const char *text, const vec3_t origin) {
    assert(index == 0 && !strcmp(text, "0:Near"));
    ++labels; return qtrue;
}
static qboolean nitmodServer = qtrue;
qboolean NITMOD_UsesNitmodHud(void) { return nitmodServer; }
char *BG_GetLocationString(vec3_t origin) { return "D4"; }

void CG_NitmodNamesReset(void) {}
qboolean trap_R_inPVS(const vec3_t a, const vec3_t b) { return visible; }

int main(void) {
    char records[] = "// locations\n0 0 0 Allied Command Post\n10 20 30 @\n40 50 60 \"Upper Tunnel\"\n70 80 90 @\n";
    char bad[] = "1\n2 3 Name\n";
    char shortName[] = "1 2 3 A\n";
    char noPrevious[] = "1 2 3 @\n";
    char invalid[] = "nan 2 3 Invalid\n";
    vec3_t first = {10, 20, 30}, last = {70, 80, 90};
    char formatted[128];
    assert(CG_NitmodParseLocations(records) == 3);
    assert(!strcmp(CG_NitmodLocation(first), "Allied Command Post"));
    assert(!strcmp(CG_NitmodLocation(last), "Upper Tunnel"));
    cg_locations.integer = 2 | 16;
    CG_NitmodLocationText(formatted, sizeof(formatted), last, 2);
    assert(!strcmp(formatted, "Upper Tunnel ^3(D4)"));
    cg_locations.integer = 0;
    CG_NitmodLocationText(formatted, sizeof(formatted), last, 2);
    assert(!strcmp(formatted, "D4"));
    cg_locations.integer = 2;
    CG_NitmodLocationText(formatted, sizeof(formatted), last, 2);
    assert(!strcmp(formatted, "Upper Tunnel"));
    nitmodServer = qfalse;
    CG_NitmodLocationText(formatted, sizeof(formatted), last, 2);
    assert(!strcmp(formatted, "D4"));
    nitmodServer = qtrue;
    assert(CG_NitmodParseLocations(bad) == 0);
    assert(CG_NitmodParseLocations(shortName) == 1);
    assert(!strcmp(CG_NitmodLocation(first), "Unknown"));
    assert(CG_NitmodParseLocations(noPrevious) == 0);
    assert(CG_NitmodParseLocations(invalid) == 0);
    assert(CG_NitmodParseLocations(NULL) == 0);
    {
        char points[] = "100 0 0 Near\n3001 0 0 Far\n-100 0 0 Behind\n";
        static snapshot_t snapshot;
        static refdef_t view;
        assert(CG_NitmodParseLocations(points) == 3);
        cg.snap = &snapshot; cg.refdef_current = &view;
        view.viewaxis[0][0] = 1;
        cg_draw2D.integer = 1; cg_locations.integer = 512;
        assert(CG_NitmodAddLocationMarkers() == 1);
        assert(markers == 1 && labels == 1);
        visible = qfalse;
        assert(CG_NitmodAddLocationMarkers() == 0);
        visible = qtrue; nitmodServer = qfalse;
        assert(CG_NitmodAddLocationMarkers() == 0);
        nitmodServer = qtrue; cg_locations.integer = 0;
        assert(CG_NitmodAddLocationMarkers() == 0);
        cg_locations.integer = 512; cg.snap = NULL;
        assert(CG_NitmodAddLocationMarkers() == 0);
    }
    puts("WASM location parser: original names/repetition and bounds cases passed");
    return 0;
}
