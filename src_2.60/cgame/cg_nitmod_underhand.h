#ifndef CG_NITMOD_UNDERHAND_H
#define CG_NITMOD_UNDERHAND_H
/* Original CG_FireWeapon: wire 4,9,15,21,25,26,28,48..51.
 * Called after muzzle/recoil bookkeeping, before firing sound and brass. */
static qboolean CG_NitmodSuppressUnderhandEffects(int weapon, float pitch) {
    if(!(pitch > 0.0f)) return qfalse;
    switch(weapon) {
    case WP_GRENADE_LAUNCHER: case WP_GRENADE_PINEAPPLE:
    case WP_DYNAMITE: case WP_SMOKE_MARKER: case WP_LANDMINE:
    case WP_SATCHEL: case WP_SMOKE_BOMB: case WP_BOMB:
    case WP_TRIPMINE: case WP_POISON_BOMB: case WP_POISON_MINE:
        return qtrue;
    default: return qfalse;
    }
}
#endif
