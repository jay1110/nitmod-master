#include "g_local.h"

/* Original qagame ELF 0x8dbe0: retain the box query, ignore its results,
 * return false. This governs the HQ proximity warning, not mine detonation.
 * The native team argument is retained for source compatibility. */
qboolean G_SweepForLandmines( vec3_t origin, float radius, int team ) {
    vec3_t mins, maxs;
    int entities[MAX_GENTITIES];
    int axis;
    (void)team;
    for( axis = 0; axis < 3; ++axis ) {
        mins[axis] = origin[axis] - radius;
        maxs[axis] = origin[axis] + radius;
    }
    trap_EntitiesInBox( mins, maxs, entities, MAX_GENTITIES );
    return qfalse;
}
