#ifndef CG_NITMOD_NAMES_H
#define CG_NITMOD_NAMES_H
extern vmCvar_t cg_woundedNames;
void CG_NitmodNamesReset(void);
void CG_NitmodNamesBeginFrame(void);
typedef struct { float alpha; int visibleTime, hiddenTime, lastTime; qboolean initialized; } nitmodNameFade_t;
float CG_NitmodNameFade(nitmodNameFade_t *fade, qboolean visible, int now);
float CG_NitmodFloatNameScale(float distance);
qboolean CG_NitmodQueueSpectatorName(const centity_t *cent);
qboolean CG_NitmodQueueDynamiteName(const centity_t *cent);
qboolean CG_NitmodProjectName(const vec3_t origin, float *x, float *y);
qboolean CG_NitmodQueueLocationName(int index, const char *text, const vec3_t origin);
void CG_NitmodDrawSpectatorNames(void);
qboolean CG_NitmodQueueWoundedName(const centity_t *cent);
void CG_NitmodDrawWoundedNames(void);
#endif
