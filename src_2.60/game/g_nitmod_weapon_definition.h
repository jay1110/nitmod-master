#ifndef G_NITMOD_WEAPON_DEFINITION_H
#define G_NITMOD_WEAPON_DEFINITION_H
struct nitmodWeaponOptions_s;
struct nitmodWeaponRecoil_s;
/* Map-owned class and damage metadata. Failed loads are cached too, preventing an
 * unreadable definition from being reopened on every item touch. */
void G_NITMOD_ResetPickupDefinitions(void);
void G_NITMOD_LoadMapWeaponDefinitions(void);
void G_NITMOD_WeaponDamageOverrides(int weapon, int *damage, int *splash, int *radius);
int G_NITMOD_WeaponSpreadOverride(int weapon, float *spread);
float G_NITMOD_WeaponMovementScale(int weapon);
int G_NITMOD_WeaponFalloffMode(int weapon, int fallback);
int G_NITMOD_WeaponHeadshotAllowed(int weapon, int fallback);
int G_NITMOD_WeaponGibAllowed(int weapon, int fallback);
int G_NITMOD_HeadshotDamage(int weapon, int damage);
int G_NITMOD_WeaponRecoil(int weapon, struct nitmodWeaponRecoil_s *recoil);
int G_NITMOD_WeaponNoMidclipReload(int weapon);
int G_NITMOD_WeaponSpreadOptions(int weapon, struct nitmodWeaponOptions_s *options);
int G_NITMOD_WeaponForcesLimbo(int weapon);
int G_NITMOD_PickupClassMask(int weapon, unsigned int *mask);
/* Exact engine-relative paths supplied by the future weapon registry.
 * Fallback is attempted only on open failure, never on malformed contents.
 * This loads the strict mask-only subset, not complete weapon metadata. */
int G_NITMOD_LoadWeaponClassMask( const char *preferred, const char *fallback,
    int alternate, unsigned int *mask );
/* Native weapon identity selects filename and both/both_altweap. Directory
 * comes from the caller, fallback is weapons/. No registry is mutated;
 * unsupported identities, overlong paths and parse errors leave mask intact. */
int G_NITMOD_LoadNativeWeaponClassMask( int weapon, const char *directory,
    unsigned int *mask );
struct ammotable_s;
/* Same path/section policy, with recovered ammo fields. Caller supplies
 * defaults in ammo; neither output changes on open/parse/path failure. */
int G_NITMOD_LoadNativeWeaponAmmo( int weapon, const char *directory,
    struct ammotable_s *ammo, unsigned int *mask );
/* Includes recovered recoil fields. Ammo defaults are retained; mask and
 * recoil start zeroed. All three outputs remain unchanged on failure.
 * This is still a strict subset, not full weapon registration. */
int G_NITMOD_LoadNativeWeaponRecoil( int weapon, const char *directory,
    struct ammotable_s *ammo, unsigned int *mask, struct nitmodWeaponRecoil_s *recoil );
int G_NITMOD_LoadNativeWeaponOptions( int weapon, const char *directory,
    struct ammotable_s *ammo, unsigned int *mask, struct nitmodWeaponRecoil_s *recoil,
    struct nitmodWeaponOptions_s *options );
#endif
