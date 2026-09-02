#include "g_local.h"
#include <stdio.h>

static vec3_t expectedOrigin;
static float expectedRadius;
static int calls, errors, queryResult;
int trap_EntitiesInBox(const vec3_t mins, const vec3_t maxs, int *list, int capacity) {
    int axis;
    ++calls;
    if(!list || capacity != 1024) ++errors;
    for(axis = 0; axis < 3; ++axis) {
        if(mins[axis] != expectedOrigin[axis] - expectedRadius ||
           maxs[axis] != expectedOrigin[axis] + expectedRadius) ++errors;
    }
    if(list && capacity == 1024) { list[0] = 123; list[1023] = 456; }
    return queryResult;
}
int main(void) {
    static const float radii[] = {0, 1, 256, -16, 1024};
    static const int results[] = {0, 1, 1024, -1};
    int radius, result, team;
    expectedOrigin[0] = -128; expectedOrigin[1] = 32; expectedOrigin[2] = 512;
    for(radius = 0; radius < 5; ++radius) {
        expectedRadius = radii[radius];
        for(result = 0; result < 4; ++result) {
            queryResult = results[result];
            for(team = 0; team < 4; ++team) {
                int before = calls;
                if(G_SweepForLandmines(expectedOrigin, expectedRadius, team) != qfalse || calls != before + 1) ++errors;
            }
        }
    }
    printf("Mine sweep: %d cases, %d errors\n", calls, errors);
    return errors != 0;
}
