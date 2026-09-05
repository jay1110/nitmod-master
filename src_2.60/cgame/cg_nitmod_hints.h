#ifndef CG_NITMOD_HINTS_H
#define CG_NITMOD_HINTS_H
extern vmCvar_t cg_objectiveHints, cg_artilleryHints;
void CG_NitmodHintsReset(void);
qboolean CG_NitmodHintEntity(centity_t *cent);
void CG_NitmodDrawArtilleryHint(void);
void CG_NitmodRegisterHintMedia(void);
void CG_NitmodDrawCursorHint(const rectDef_t *rect);
qboolean CG_NitmodScanDynamite(const centity_t *cent);
qboolean CG_NitmodDrawDynamiteHint(void);
qboolean CG_NitmodPrepareMine(const centity_t *cent, refEntity_t *ent, qboolean *marker);
qboolean CG_NitmodScanMine(const centity_t *cent);
qboolean CG_NitmodDrawMineHint(void);
qboolean CG_NitmodDrawCrosshairPlayer(int client, qboolean disguised, int health, int maxHealth, const vec4_t color);
int CG_NitmodCrosshairMaxHealth(int client);
qboolean CG_NitmodCanIdentifyDisguise(int client);
/* 0 hidden, 1 model only, 2 model and beam. */
int CG_NitmodTripminePresentation(const entityState_t *state, byte rgba[4]);
void CG_NitmodDrawCrosshairLabel(const char *text, const vec4_t color);
void CG_NitmodDrawCrosshairHealth(int health, int maxHealth, const vec4_t color);
const char *CG_NitmodCrosshairEntityName(int entity, qboolean construction);
#endif
