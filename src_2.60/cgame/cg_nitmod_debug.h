#ifndef CG_NITMOD_DEBUG_H
#define CG_NITMOD_DEBUG_H

/* Internal diagnostic geometry, never an engine/network structure. */
typedef struct {
    vec3_t mins, maxs;
} nitmodDebugBox_t;
typedef struct {
    nitmodDebugBox_t boxes[4];
    int count;
} nitmodDebugGeometry_t;

extern vmCvar_t cg_drawHitbox;
typedef struct { vec3_t start, end, color; } nitmodDebugLine_t;
int CG_NitmodDebugEventLines(const entityState_t *es, int event, nitmodDebugLine_t lines[12]);
void CG_NitmodDebugEvent(const entityState_t *es, int event);
localEntity_t *CG_NitmodFindRailEntity(int group, int segment);
void CG_NitmodRailEvent(const entityState_t *es);
extern vmCvar_t demo_wallHack;
void CG_NitmodRegisterDebugMedia(void);
qhandle_t CG_NitmodViewWeaponShader(int drawGun);
qhandle_t CG_NitmodMineTeamShader(team_t team);
qhandle_t CG_NitmodDemoPlayerShader(team_t team);
void CG_NitmodDebugGeometry(const centity_t *cent, const playerState_t *ps,
    const pmoveExt_t *ext, int flags, nitmodDebugGeometry_t *out);
void CG_NitmodDrawPlayerDebug(const centity_t *cent, const refEntity_t *body);
#endif
