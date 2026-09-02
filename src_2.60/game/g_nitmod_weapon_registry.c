#include "g_nitmod_weapon_registry.h"
#include "g_nitmod_weapon_definition.h"
#include "nitmod_weapon_paths.h"

void G_NITMOD_ResetWeaponRegistry( nitmodWeaponRegistry_t *registry ) {
    if( registry ) memset(registry, 0, sizeof(*registry));
}

const nitmodWeaponRecord_t *G_NITMOD_RegisteredWeapon(
    const nitmodWeaponRegistry_t *registry, int weapon ) {
    if( !registry || !NITMOD_WeaponPath(weapon) ) return NULL;
    return registry->weapons[weapon].registered ? &registry->weapons[weapon] : NULL;
}

int G_NITMOD_RegisterWeapon( nitmodWeaponRegistry_t *registry, int weapon,
    const char *directory, const ammotable_t *defaults, int force ) {
    nitmodWeaponRecord_t next;
    if( !registry || !NITMOD_WeaponPath(weapon) ) return -1;
    if( !force && registry->weapons[weapon].registered ) return 0;
    if( !defaults ) return -1;
    memset(&next, 0, sizeof(next));
    next.ammo = *defaults;
    if( !G_NITMOD_LoadNativeWeaponOptions(weapon, directory, &next.ammo,
        &next.classMask, &next.recoil, &next.options) ) return -1;
    next.registered = 1;
    registry->weapons[weapon] = next;
    return 1;
}
