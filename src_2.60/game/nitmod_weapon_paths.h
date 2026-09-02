#ifndef NITMOD_WEAPON_PATHS_H
#define NITMOD_WEAPON_PATHS_H
/* Immutable descriptor for native ET weapon IDs. Filename is a basename;
 * alternate selects both_altweap, not necessarily a deployed weapon.
 * NULL means no verified native definition. No I/O or registration occurs. */
typedef struct {
    const char *filename;
    int alternate;
} nitmodWeaponPath_t;
const nitmodWeaponPath_t *NITMOD_WeaponPath( int weapon );
#endif
