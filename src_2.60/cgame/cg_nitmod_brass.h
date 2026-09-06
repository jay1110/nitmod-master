#ifndef CG_NITMOD_BRASS_H
#define CG_NITMOD_BRASS_H
/* Original CG_MachineGunEjectBrass has no local-client comparison.
 * Native AA handling is retained alongside the original MG42 exclusion. */
static qboolean CG_NitmodUseTagBrass(qboolean nitmod, qboolean localPlayer,
                                    int heavyWeaponUse, int flags) {
    return !heavyWeaponUse && !(flags & (EF_MG42_ACTIVE | EF_AAGUN_ACTIVE)) &&
           (nitmod || localPlayer);
}
/* Original CG_AddPlayerWeapon: first-person brass tags, otherwise hand tags.
 * World akimbo side comes from the entity event state, not predicted ammo. */
static const char *CG_NitmodBrassTag(qboolean firstPerson, qboolean akimbo,
                                   qboolean predictedSide, qboolean entitySide) {
    if(firstPerson) return akimbo && predictedSide ? "tag_brass2" : "tag_brass";
    return akimbo && !entitySide ? "tag_weapon2" : "tag_weapon";
}
#endif
