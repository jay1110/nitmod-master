#ifndef CG_NITMOD_VIEW_H
#define CG_NITMOD_VIEW_H

/* Original-protocol player flag, NOT the native ET camera meaning. */
#define NITMOD_EF_POISONED 0x00200000
int CG_CalcFov(void);
void CG_ZoomSway(void);
void CG_NitmodZoomSway(int time, float zoom, const playerState_t *state, vec3_t angles);
void CG_NitmodLetterbox(refdef_t *view, int width, int height, float xpercent, float ypercent, qboolean center);
void CG_NitmodViewOffsets(int time, int flags, int weapons, float lean,
                         vec3_t angles, vec3_t origin);
#endif
