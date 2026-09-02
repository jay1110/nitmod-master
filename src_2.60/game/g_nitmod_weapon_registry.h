#ifndef G_NITMOD_WEAPON_REGISTRY_H
#define G_NITMOD_WEAPON_REGISTRY_H
#include "nitmod_weapon_recoil.h"
#include "nitmod_weapon_definition.h"
typedef struct {
    int registered;
    ammotable_t ammo;
    unsigned int classMask;
    nitmodWeaponRecoil_t recoil;
    nitmodWeaponOptions_t options;
} nitmodWeaponRecord_t;
/* Caller-owned subset registry. Zero-initialize or Reset before any use.
 * No engine state/global ammo table is owned or mutated here. */
typedef struct {
    nitmodWeaponRecord_t weapons[WP_NUM_WEAPONS];
} nitmodWeaponRegistry_t;
void G_NITMOD_ResetWeaponRegistry( nitmodWeaponRegistry_t *registry );
/* 1 loaded, 0 already registered, -1 invalid/load failure. Nonzero force
 * reloads; failure preserves the old record. Defaults/directory are consumed
 * only when loading. Caller must provide explicit native ammo defaults. */
int G_NITMOD_RegisterWeapon( nitmodWeaponRegistry_t *registry, int weapon,
    const char *directory, const ammotable_t *defaults, int force );
/* Borrowed read-only pointer, valid until a reload/reset of this registry. */
const nitmodWeaponRecord_t *G_NITMOD_RegisteredWeapon(
    const nitmodWeaponRegistry_t *registry, int weapon );
#endif
