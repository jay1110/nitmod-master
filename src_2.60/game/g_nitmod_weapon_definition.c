#include "g_local.h"
#include "g_nitmod_weapon_definition.h"
#include "nitmod_weapon_definition.h"
#include "nitmod_weapon_paths.h"

typedef struct {
    int handle;
    pc_token_t token;
} weaponSource_t;

static const char *ReadWeaponToken( void *context ) {
    weaponSource_t *source = context;
    memset(&source->token, 0, sizeof(source->token));
    if( !trap_PC_ReadToken(source->handle, &source->token) ) return NULL;
    if( !memchr(source->token.string, 0, sizeof(source->token.string)) ) return NULL;
    /* Quoted braces are data, not block delimiters. In selected numeric
     * blocks quoted keys/numbers intentionally fail strict parsing. */
    if( source->token.type == TT_STRING ) return "<quoted-data>";
    return source->token.string;
}

static int LoadWeapon( const char *preferred, const char *fallback,
    int alternate, ammotable_t *ammo, unsigned int *mask, struct nitmodWeaponRecoil_s *recoil,
    nitmodWeaponOptions_t *options ) {
    weaponSource_t source;
    unsigned int next;
    int parsed;
    if( !preferred || !*preferred || !mask ) return 0;
    source.handle = trap_PC_LoadSource(preferred);
    if( !source.handle && fallback && *fallback && strcmp(preferred, fallback) )
        source.handle = trap_PC_LoadSource(fallback);
    if( !source.handle ) return 0;
    if( options ) parsed = NITMOD_ParseWeaponOptions(ReadWeaponToken, &source, alternate, ammo, &next, recoil, options);
    else if( recoil ) parsed = NITMOD_ParseWeaponRecoil(ReadWeaponToken, &source, alternate, ammo, &next, recoil);
    else if( ammo ) parsed = NITMOD_ParseWeaponAmmo(ReadWeaponToken, &source, alternate, ammo, &next);
    else parsed = NITMOD_ParseWeaponClassMask(ReadWeaponToken, &source, alternate, &next);
    trap_PC_FreeSource(source.handle);
    if( !parsed ) return 0;
    *mask = next;
    return 1;
}

int G_NITMOD_LoadWeaponClassMask( const char *preferred, const char *fallback,
    int alternate, unsigned int *mask ) {
    return LoadWeapon(preferred, fallback, alternate, NULL, mask, NULL, NULL);
}

static int LoadNativeWeapon( int weapon, const char *directory,
    ammotable_t *ammo, unsigned int *mask, struct nitmodWeaponRecoil_s *recoil,
    nitmodWeaponOptions_t *options ) {
    const nitmodWeaponPath_t *path = NITMOD_WeaponPath(weapon);
    char preferred[MAX_QPATH], fallback[MAX_QPATH];
    size_t directoryLength, filenameLength;
    if( !path || !directory || !*directory || !mask ) return 0;
    directoryLength = strlen(directory);
    filenameLength = strlen(path->filename);
    /* Subtraction avoids overflow from caller-controlled directory length. */
    if( filenameLength > sizeof(preferred) - 2 ||
        directoryLength > sizeof(preferred) - filenameLength - 2 ||
        filenameLength > sizeof(fallback) - sizeof("weapons/") ) return 0;
    memcpy(preferred, directory, directoryLength);
    preferred[directoryLength] = '/';
    memcpy(preferred + directoryLength + 1, path->filename, filenameLength + 1);
    memcpy(fallback, "weapons/", sizeof("weapons/") - 1);
    memcpy(fallback + sizeof("weapons/") - 1, path->filename, filenameLength + 1);
    return LoadWeapon(preferred, fallback, path->alternate, ammo, mask, recoil, options);
}

int G_NITMOD_LoadNativeWeaponClassMask( int weapon, const char *directory,
    unsigned int *mask ) {
    return LoadNativeWeapon(weapon, directory, NULL, mask, NULL, NULL);
}

int G_NITMOD_LoadNativeWeaponAmmo( int weapon, const char *directory,
    ammotable_t *ammo, unsigned int *mask ) {
    if( !ammo ) return 0;
    return LoadNativeWeapon(weapon, directory, ammo, mask, NULL, NULL);
}

int G_NITMOD_LoadNativeWeaponRecoil( int weapon, const char *directory,
    ammotable_t *ammo, unsigned int *mask, struct nitmodWeaponRecoil_s *recoil ) {
    if( !ammo || !recoil ) return 0;
    return LoadNativeWeapon(weapon, directory, ammo, mask, recoil, NULL);
}

int G_NITMOD_LoadNativeWeaponOptions( int weapon, const char *directory,
    ammotable_t *ammo, unsigned int *mask, struct nitmodWeaponRecoil_s *recoil,
    nitmodWeaponOptions_t *options ) {
    if( !ammo || !recoil || !options ) return 0;
    return LoadNativeWeapon(weapon, directory, ammo, mask, recoil, options);
}
