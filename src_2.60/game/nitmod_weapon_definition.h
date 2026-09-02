#ifndef NITMOD_WEAPON_DEFINITION_H
#define NITMOD_WEAPON_DEFINITION_H
/* Caller supplies engine-tokenized strings (comments removed). Returned
 * pointer is borrowed until the next call; NULL means EOF/read failure.
 * This strict subset accepts only classes fields in selected both blocks;
 * it is NOT a validator for all weapon-definition attributes. */
typedef const char *(*nitmodWeaponTokenReader_t)( void *context );
int NITMOD_ParseWeaponClassMask( nitmodWeaponTokenReader_t readToken,
    void *context, int alternate, unsigned int *mask );
struct ammotable_s;
/* Adds the nine recovered ammo/timing integer attributes to the strict
 * subset. Starts from caller-owned ammo defaults; missing attributes, uses
 * and mod stay unchanged. Mask starts at zero. Both outputs commit only on
 * success. This does not mutate the global ammo table or load client assets. */
int NITMOD_ParseWeaponAmmo( nitmodWeaponTokenReader_t readToken,
    void *context, int alternate, struct ammotable_s *ammo, unsigned int *mask );
struct nitmodWeaponRecoil_s;
typedef struct nitmodWeaponOptions_s {
    int noMidclipReload;
} nitmodWeaponOptions_t;
/* Ammo/classes subset plus recoilDuration, recoilYaw, recoilPitch. Recoil
 * starts zeroed like the original private record; any recoil key enables it.
 * All outputs commit together, even across repeated selected blocks. */
int NITMOD_ParseWeaponRecoil( nitmodWeaponTokenReader_t readToken,
    void *context, int alternate, struct ammotable_s *ammo, unsigned int *mask,
    struct nitmodWeaponRecoil_s *recoil );
/* Extended strict subset: noMidclipReload is a bare flag, not an integer.
 * Options start zeroed; all four outputs commit together on success. */
int NITMOD_ParseWeaponOptions( nitmodWeaponTokenReader_t readToken,
    void *context, int alternate, struct ammotable_s *ammo, unsigned int *mask,
    struct nitmodWeaponRecoil_s *recoil, nitmodWeaponOptions_t *options );
#endif
