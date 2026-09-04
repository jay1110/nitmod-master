#ifndef CG_NITMOD_WEAPON_POSE_H
#define CG_NITMOD_WEAPON_POSE_H

/* Inputs use ET 2.60 weapon IDs/states, after snapshot normalization. */
void CG_NitmodCalculateWeaponPosition(const cg_t *view, int weapons,
                                    vec3_t origin, vec3_t angles);

#endif
