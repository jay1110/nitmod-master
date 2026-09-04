#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_coronas.h"
#include <float.h>

/* Original SP_corona: 1024 seven-float records, not network entities. */
static nitmodMapCorona_t coronas[NITMOD_MAX_MAP_CORONAS];
static int coronaCount;

void CG_NitmodResetCoronas(void) { coronaCount = 0; }
int CG_NitmodCoronaCount(void) { return coronaCount; }
const nitmodMapCorona_t *CG_NitmodCorona(int index) {
    return index >= 0 && index < coronaCount ? &coronas[index] : NULL;
}
static qboolean CoronaVector(const char *text, vec3_t vector) {
    char extra;
    int i;
    if(sscanf(text, "%f %f %f %c", &vector[0], &vector[1], &vector[2], &extra) != 3) return qfalse;
    for(i = 0; i < 3; ++i) if(!(vector[i] >= -FLT_MAX && vector[i] <= FLT_MAX)) return qfalse;
    return qtrue;
}
void CG_NitmodSpawnCorona(void) {
    nitmodMapCorona_t next;
    char *text, extra;
    if(!NITMOD_UsesOriginalProtocol()) return;
    /* Presence, not value: even spawnflags=0 belongs to the server path. */
    if(CG_SpawnString("targetname", "", &text) || CG_SpawnString("scriptname", "", &text) ||
       CG_SpawnString("spawnflags", "", &text)) return;
    if(coronaCount == NITMOD_MAX_MAP_CORONAS) {
        CG_Printf("^3Nitmod: map corona limit (%d) reached\n", NITMOD_MAX_MAP_CORONAS); return;
    }
    CG_SpawnString("origin", "0 0 0", &text);
    if(!CoronaVector(text, next.origin)) return;
    CG_SpawnString("scale", "1", &text);
    if(sscanf(text, "%f %c", &next.scale, &extra) != 1 ||
       !(next.scale >= -FLT_MAX && next.scale <= FLT_MAX)) return;
    /* Original _color takes precedence. The ELF default string is 0 0 0,
     * including the final assignment when neither color key is present. */
    if(!CG_SpawnString("_color", "0 0 0", &text)) CG_SpawnString("color", "0 0 0", &text);
    if(!CoronaVector(text, next.color)) return;
    coronas[coronaCount++] = next;
}

void CG_NitmodDrawCoronas(void) {
    int i;
    vec3_t direction;
    float distance;
    trace_t trace;
    const refdef_t *view = cg.refdef_current;
    if(!NITMOD_UsesOriginalProtocol() || !cg_coronas.integer || !view) return;
    for(i = 0; i < coronaCount; ++i) {
        const nitmodMapCorona_t *corona = &coronas[i];
        if(!trap_R_inPVS(view->vieworg, corona->origin)) continue;
        VectorSubtract(view->vieworg, corona->origin, direction);
        distance = VectorNormalize2(direction, direction);
        if(!(distance >= 0 && distance <= FLT_MAX)) continue;
        if(cg_coronas.integer != 2 && (distance > cg_coronafardist.integer ||
           DotProduct(direction, view->viewaxis[0]) >= -.6f)) continue;
        CG_Trace(&trace, view->vieworg, NULL, NULL, corona->origin, -1, MASK_SOLID | CONTENTS_BODY);
        trap_R_AddCoronaToScene(corona->origin, corona->color[0], corona->color[1],
            corona->color[2], corona->scale, i, trace.fraction == 1.f);
    }
}
