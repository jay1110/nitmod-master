#include <stdlib.h>
#include <float.h>
#include <errno.h>
#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_locations.h"
#include "cg_nitmod_names.h"

#define NITMOD_LOCATION_FILE_SIZE 32768

typedef struct {
    vec3_t origin;
    char name[64];
} nitmodLocation_t;

static nitmodLocation_t locations[NITMOD_MAX_LOCATIONS];
static int locationCount;

static qboolean CG_NitmodLocationNumber(const char *token, float *value) {
    char *end;
    double number;
    if(!token || !token[0]) return qfalse;
    errno = 0;
    number = strtod(token, &end);
    if(*end || end == token || errno == ERANGE || !(number >= -FLT_MAX && number <= FLT_MAX)) return qfalse;
    *value = (float)number;
    return qtrue;
}

int CG_NitmodParseLocations(char *text) {
    char *cursor = text;
    const char *token;
    locationCount = 0;
    CG_NitmodNamesReset();
    while(cursor && locationCount < NITMOD_MAX_LOCATIONS) {
        nitmodLocation_t entry;
        token = COM_ParseExt(&cursor, qtrue);
        if(!token || !token[0]) break;
        if(!CG_NitmodLocationNumber(token, &entry.origin[0])) break;
        token = COM_ParseExt(&cursor, qtrue);
        if(!CG_NitmodLocationNumber(token, &entry.origin[1])) break;
        token = COM_ParseExt(&cursor, qtrue);
        if(!CG_NitmodLocationNumber(token, &entry.origin[2])) break;
        token = COM_ParseExt(&cursor, qtrue);
        if(!token || !token[0]) break;
        if(VectorCompare(entry.origin, vec3_origin)) continue;
        Q_strncpyz(entry.name, token, sizeof(entry.name));
        if(entry.name[0]) locations[locationCount++] = entry;
    }
    return locationCount;
}

void CG_NitmodLoadLocations(void) {
    char buffer[NITMOD_LOCATION_FILE_SIZE + 1];
    char filename[MAX_QPATH];
    fileHandle_t file = 0;
    int length;
    locationCount = 0;
    if(!NITMOD_UsesOriginalProtocol() || !cgs.rawmapname[0]) return;
    Com_sprintf(filename, sizeof(filename), "maps/%s_loc_override.dat", cgs.rawmapname);
    length = trap_FS_FOpenFile(filename, &file, FS_READ);
    if(length < 0) {
        Com_sprintf(filename, sizeof(filename), "maps/%s_loc.dat", cgs.rawmapname);
        length = trap_FS_FOpenFile(filename, &file, FS_READ);
    }
    if(length < 0 || !file) return;
    if(length > NITMOD_LOCATION_FILE_SIZE) {
        CG_Printf("^3Location file too large: %s (max %i bytes)\n", filename, NITMOD_LOCATION_FILE_SIZE);
        trap_FS_FCloseFile(file);
        return;
    }
    trap_FS_Read(buffer, length, file);
    trap_FS_FCloseFile(file);
    buffer[length] = '\0';
    CG_NitmodParseLocations(buffer);
}

int CG_NitmodLocationCount(void) { return locationCount; }

/* Original CG_DrawActiveFrame location-debug branch: cg_locations bit 512,
 * 3000-unit range, PVS, forward cone and screen bounds. */
int CG_NitmodAddLocationMarkers(void) {
    int i, count = 0;
    vec3_t direction;
    float distance, x, y;
    char text[96];
    if(!NITMOD_UsesOriginalProtocol() || !cg.snap || !cg.refdef_current ||
       !cg_draw2D.integer || !(cg_locations.integer & 512)) return 0;
    for(i = 0; i < locationCount; ++i) {
        refEntity_t marker;
        VectorSubtract(locations[i].origin, cg.refdef_current->vieworg, direction);
        distance = VectorNormalize(direction);
        if(!(distance > 0 && distance <= 3000) ||
           DotProduct(direction, cg.refdef_current->viewaxis[0]) <= .6f ||
           !trap_R_inPVS(cg.refdef_current->vieworg, locations[i].origin) ||
           !CG_NitmodProjectName(locations[i].origin, &x, &y) || x < 0 || x > 640 || y < 0 || y > 480) continue;
        memset(&marker, 0, sizeof(marker));
        marker.reType = RT_SPRITE;
        VectorCopy(locations[i].origin, marker.origin);
        VectorCopy(marker.origin, marker.oldorigin);
        marker.customShader = cgs.media.waterBubbleShader;
        marker.radius = strlen(locations[i].name) + 8;
        memset(marker.shaderRGBA, 255, sizeof(marker.shaderRGBA));
        trap_R_AddRefEntityToScene(&marker);
        Com_sprintf(text, sizeof(text), "%i:%s", i, locations[i].name);
        CG_NitmodQueueLocationName(i, text, locations[i].origin);
        ++count;
    }
    return count;
}

const char *CG_NitmodLocation(const vec3_t origin) {
    int i, best = -1;
    float bestDistance = 200000000.0f;
    for(i = 0; i < locationCount; ++i) {
        float distance = Distance(origin, locations[i].origin);
        if(distance <= bestDistance && trap_R_inPVS(origin, locations[i].origin)) {
            bestDistance = distance;
            best = i;
        }
    }
    return best >= 0 && locations[best].name[0] ? locations[best].name : "Unknown";
}

void CG_NitmodLocationText(char *out, int size, const vec3_t origin, int enableBit) {
    const char *custom = "Unknown", *grid;
    if(!out || size <= 0) return;
    grid = BG_GetLocationString((vec_t *)origin);
    if(NITMOD_UsesOriginalProtocol() && (cg_locations.integer & enableBit))
        custom = CG_NitmodLocation(origin);
    if(!(cg_locations.integer & enableBit) || (!(cg_locations.integer & 8) && !Q_stricmp(custom, "Unknown")))
        Q_strncpyz(out, grid ? grid : " ", size);
    else if(cg_locations.integer & 16)
        Com_sprintf(out, size, "%s %s", custom, grid ? grid : "");
    else Q_strncpyz(out, custom, size);
    if(!out[0]) Q_strncpyz(out, " ", size);
}
