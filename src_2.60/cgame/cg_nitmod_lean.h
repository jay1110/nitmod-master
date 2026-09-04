#ifndef CG_NITMOD_LEAN_H
#define CG_NITMOD_LEAN_H

/* Typed pose operation; network flags are supplied by the player adapter. */
void CG_NitmodPredictLean(centity_t *cent, vec3_t torso, vec3_t head,
                         int viewheight, int weapons, int misc);
void CG_NitmodPlayerLean(centity_t *cent, vec3_t torso, vec3_t head);

#endif
