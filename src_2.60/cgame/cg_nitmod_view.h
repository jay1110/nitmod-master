#ifndef CG_NITMOD_VIEW_H
#define CG_NITMOD_VIEW_H

/* NITMOD_EF_POISONED is declared once in the shared protocol header. */
int CG_CalcFov(void);
void CG_ZoomSway(void);
void CG_NitmodZoomSway(int time, float zoom, const playerState_t *state, vec3_t angles);
void CG_NitmodLetterbox(refdef_t *view, int width, int height, float xpercent, float ypercent, qboolean center);
void CG_NitmodViewOffsets(int time, int flags, int weapons, float lean,
                         vec3_t angles, vec3_t origin);
void CG_NitmodMissileCameraBeginFrame(void);
void CG_NitmodMissileCameraTrack(centity_t *cent);
void CG_NitmodDrawMissileCamera(void);
#endif
