#ifndef CG_NITMOD_LOCATIONS_H
#define CG_NITMOD_LOCATIONS_H
#define NITMOD_MAX_LOCATIONS 1024

void CG_NitmodLoadLocations(void);
int CG_NitmodParseLocations(char *text);
const char *CG_NitmodLocation(const vec3_t origin);
void CG_NitmodLocationText(char *out, int size, const vec3_t origin, int enableBit);
int CG_NitmodLocationCount(void);
int CG_NitmodAddLocationMarkers(void);

#endif
