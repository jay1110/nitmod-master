#ifndef CG_NITMOD_AMMO_H
#define CG_NITMOD_AMMO_H
void CG_CheckAmmo(void);
typedef enum {
    NITMOD_AMMO_NATIVE, NITMOD_AMMO_KEEP, NITMOD_AMMO_SELECT,
    NITMOD_AMMO_FINISH, NITMOD_AMMO_NEXT
} nitmodAmmoAction_t;
nitmodAmmoAction_t CG_NitmodAmmoSelection(qboolean force, int *choice);
#endif
