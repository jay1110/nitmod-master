#include "g_local.h"
#include "g_nitmod_weapon_definition.h"
#include "nitmod_weapon_definition.h"
#include "nitmod_weapon_paths.h"
#include "nitmod_weapon_recoil.h"
#include <limits.h>

static signed char pickupDefinitionState[WP_NUM_WEAPONS];
static unsigned int pickupDefinitionMask[WP_NUM_WEAPONS];
static nitmodWeaponOptions_t weaponOptions[WP_NUM_WEAPONS];
static nitmodWeaponRecoil_t weaponRecoil[WP_NUM_WEAPONS];

/* Original g_weaponScriptsDir is qagame-only: the engine VFS resolves this
 * relative directory identically from loose mod files or any mounted PK3.
 * An empty/unsafe value deliberately falls back to the stock weapons dir. */
static const char *G_NITMOD_WeaponScriptsDirectory(void) {
    static char directory[MAX_QPATH];
    size_t i;
    trap_Cvar_VariableStringBuffer("g_weaponScriptsDir", directory, sizeof(directory));
    directory[sizeof(directory) - 1] = 0;
    if(!directory[0]) return "weapons";
    if(directory[0] == '/' || directory[0] == '\\' || strstr(directory, "..")) return "weapons";
    for(i = 0; directory[i]; ++i) {
        if(directory[i] == '\\' || directory[i] == ':') return "weapons";
    }
    while(i && directory[i - 1] == '/') directory[--i] = 0;
    return i ? directory : "weapons";
}

void G_NITMOD_ResetPickupDefinitions(void) {
    memset(pickupDefinitionState, 0, sizeof(pickupDefinitionState));
    memset(pickupDefinitionMask, 0, sizeof(pickupDefinitionMask));
    memset(weaponOptions, 0, sizeof(weaponOptions));
    memset(weaponRecoil, 0, sizeof(weaponRecoil));
}

int G_NITMOD_PickupClassMask(int weapon, unsigned int *mask) {
    ammotable_t parsedAmmo;
    nitmodWeaponRecoil_t parsedRecoil;
    nitmodWeaponOptions_t ignoredOptions;
    unsigned int next;
    if(weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS || !mask) return 0;
    if(!pickupDefinitionState[weapon]) {
        /* Begin with native defaults so omitted keys retain their values.
         * Commit the complete record only after the whole file parsed. */
        parsedAmmo = ammoTableMP[weapon];
        pickupDefinitionState[weapon] = -1;
        if(G_NITMOD_LoadNativeWeaponOptions(weapon, G_NITMOD_WeaponScriptsDirectory(), &parsedAmmo,
            &next, &parsedRecoil, &ignoredOptions)) {
            ammoTableMP[weapon] = parsedAmmo;
            pickupDefinitionMask[weapon] = next;
            weaponRecoil[weapon] = parsedRecoil;
            weaponOptions[weapon] = ignoredOptions;
            pickupDefinitionState[weapon] = 1;
        }
    }
    if(pickupDefinitionState[weapon] < 0) return 0;
    *mask = pickupDefinitionMask[weapon];
    return 1;
}

void G_NITMOD_LoadMapWeaponDefinitions(void) {
    int weapon;
    unsigned int mask;
    for(weapon=WP_NONE+1; weapon<WP_NUM_WEAPONS; ++weapon)
        G_NITMOD_PickupClassMask(weapon, &mask);
}

/* No file I/O in damage callbacks. Startup owns loading; failed records
 * keep defaults, and map reset invalidates the complete record together. */
void G_NITMOD_WeaponDamageOverrides(int weapon, int *damage, int *splash, int *radius) {
    const nitmodWeaponOptions_t *options;
    if(weapon<=WP_NONE || weapon>=WP_NUM_WEAPONS || pickupDefinitionState[weapon]!=1) return;
    options=&weaponOptions[weapon];
    if(damage && options->damage) *damage=options->damage;
    if(splash && options->splashDamage) *splash=options->splashDamage;
    if(radius && options->splashRadius) *radius=options->splashRadius;
}

int G_NITMOD_WeaponSpreadOverride(int weapon, float *spread) {
    if(!spread || weapon<=WP_NONE || weapon>=WP_NUM_WEAPONS ||
       pickupDefinitionState[weapon]!=1 || !weaponOptions[weapon].spread) return 0;
    *spread=(float)weaponOptions[weapon].spread;
    return 1;
}

float G_NITMOD_WeaponMovementScale(int weapon) {
    if(weapon<=WP_NONE || weapon>=WP_NUM_WEAPONS ||
       pickupDefinitionState[weapon]!=1) return 0.f;
    return weaponOptions[weapon].movementSpeedScale;
}

int G_NITMOD_WeaponFalloffMode(int weapon, int fallback) {
    int mode;
    /* Original MG branches force zero instead of consulting this field. */
    if(weapon<=WP_NONE || weapon>=WP_NUM_WEAPONS ||
       weapon==WP_MOBILE_MG42 || weapon==WP_MOBILE_MG42_SET ||
       pickupDefinitionState[weapon]!=1) return fallback;
    mode=weaponOptions[weapon].distanceFalloff;
    return mode==1 || mode==2 ? mode : fallback;
}

int G_NITMOD_WeaponHeadshotAllowed(int weapon, int fallback) {
    int choice;
    if(weapon<=WP_NONE || weapon>=WP_NUM_WEAPONS || pickupDefinitionState[weapon]!=1) return fallback;
    choice=weaponOptions[weapon].headshotWeapon;
    return choice==1 ? 1 : choice==2 ? 0 : fallback;
}

int G_NITMOD_HeadshotDamage(int weapon, int damage) {
    float ratio=2.f;
    int minimum=50, scaled;
    double product;
    if(weapon>WP_NONE && weapon<WP_NUM_WEAPONS && pickupDefinitionState[weapon]==1) {
        if(weaponOptions[weapon].headshotRatio) ratio=weaponOptions[weapon].headshotRatio;
        if(weaponOptions[weapon].minHeadshotDamage) minimum=weaponOptions[weapon].minHeadshotDamage;
    }
    product=(float)damage*ratio;
    /* Keep conversion defined for extreme parsed settings. */
    scaled=product>=INT_MAX ? INT_MAX : product<=INT_MIN ? INT_MIN : (int)product;
    return scaled<minimum ? minimum : scaled;
}

int G_NITMOD_WeaponGibAllowed(int weapon, int fallback) {
    int choice;
    if(weapon<=WP_NONE || weapon>=WP_NUM_WEAPONS || pickupDefinitionState[weapon]!=1) return fallback;
    choice=weaponOptions[weapon].gibbingWeapon;
    return choice==1 ? 1 : choice==2 ? 0 : fallback;
}

int G_NITMOD_WeaponRecoil(int weapon, nitmodWeaponRecoil_t *recoil) {
    if(!recoil || weapon<=WP_NONE || weapon>=WP_NUM_WEAPONS ||
       pickupDefinitionState[weapon]!=1 || !weaponRecoil[weapon].enabled) return 0;
    *recoil=weaponRecoil[weapon];
    return 1;
}

int G_NITMOD_WeaponNoMidclipReload(int weapon) {
    if(weapon<=WP_NONE || weapon>=WP_NUM_WEAPONS || pickupDefinitionState[weapon]!=1) return 0;
    return weaponOptions[weapon].noMidclipReload != 0;
}

int G_NITMOD_WeaponSpreadOptions(int weapon, nitmodWeaponOptions_t *options) {
    if(!options || weapon<=WP_NONE || weapon>=WP_NUM_WEAPONS || pickupDefinitionState[weapon]!=1) return 0;
    options->spreadScaleAdd = weaponOptions[weapon].spreadScaleAdd;
    options->spreadScaleAddRand = weaponOptions[weapon].spreadScaleAddRand;
    options->spreadRatio = weaponOptions[weapon].spreadRatio;
    options->velocityToSpread = weaponOptions[weapon].velocityToSpread;
    options->viewChangeToSpread = weaponOptions[weapon].viewChangeToSpread;
    return 1;
}

int G_NITMOD_WeaponForcesLimbo(int weapon) {
    if(weapon<=WP_NONE || weapon>=WP_NUM_WEAPONS || pickupDefinitionState[weapon]!=1) return 0;
    return weaponOptions[weapon].limboKill != 0;
}

typedef struct {
    int handle;
    pc_token_t token;
    char quoted[sizeof(((pc_token_t *)0)->string) + 1];
} weaponSource_t;

static const char *ReadWeaponToken( void *context ) {
    weaponSource_t *source = context;
    memset(&source->token, 0, sizeof(source->token));
    if( !trap_PC_ReadToken(source->handle, &source->token) ) return NULL;
    if( !memchr(source->token.string, 0, sizeof(source->token.string)) ) return NULL;
    /* Quoted braces are data, not block delimiters. In selected numeric
     * blocks quoted keys/numbers intentionally fail strict parsing. */
    if( source->token.type == TT_STRING ) {
        source->quoted[0] = '\1';
        memcpy(source->quoted + 1, source->token.string, strlen(source->token.string) + 1);
        return source->quoted;
    }
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
