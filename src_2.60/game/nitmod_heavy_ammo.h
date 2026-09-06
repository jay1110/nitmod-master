#ifndef NITMOD_HEAVY_AMMO_H
#define NITMOD_HEAVY_AMMO_H

/* Original BG_MaxAmmoForWeapon: Heavy Weapons reward bit 32, not level.
 * Caller supplies typed weapon/table values; -1 denotes another weapon. */
static int NITMOD_HeavyAmmoCapacity(int weapon, unsigned int rewards, int base, int clip) {
    int bonus;
    switch(weapon) {
    case WP_FLAMETHROWER: bonus = 50; break;
    case WP_MOBILE_MG42:
    case WP_MOBILE_MG42_SET: bonus = clip; break;
    case WP_MORTAR:
    case WP_MORTAR_SET: bonus = 2; break;
    default: return -1;
    }
    return base + ((rewards & 32u) ? bonus : 0);
}
#endif
