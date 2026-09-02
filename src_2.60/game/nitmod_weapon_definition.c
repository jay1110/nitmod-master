#include <string.h>
#include <limits.h>
#include "q_shared.h"
#include "bg_public.h"
#include "nitmod_protocol.h"
#include "nitmod_weapon_definition.h"
#include "nitmod_weapon_recoil.h"

typedef struct {
    nitmodWeaponTokenReader_t read;
    void *context;
    int remaining;
} tokenStream_t;

static const char *Next( tokenStream_t *stream ) {
    if( stream->remaining-- <= 0 ) return 0;
    return stream->read(stream->context);
}

static int ReadInteger( tokenStream_t *stream, int *value ) {
    const char *token = Next(stream);
    unsigned int magnitude;
    unsigned int minimumMagnitude = (unsigned int)( -(INT_MIN + 1) ) + 1u;
    if( !token ) return 0;
    if( strcmp(token, "-") ) return NITMOD_ParseProtocolSigned(token, value);
    token = Next(stream);
    /* Parse the magnitude unsigned: INT_MIN has no positive int counterpart.
     * Also reject a second sign, including negative zero. */
    if( !NITMOD_ParseProtocolUnsigned(token, &magnitude) || magnitude > minimumMagnitude ) return 0;
    *value = magnitude == minimumMagnitude ? INT_MIN : -(int)magnitude;
    return 1;
}

static int ReadFloat( tokenStream_t *stream, float *value ) {
    const char *token = Next(stream);
    int negative;
    if( !token ) return 0;
    negative = !strcmp(token, "-");
    if( negative ) {
        token = Next(stream);
        if( !token || *token == '-' || *token == '+' ) return 0;
    }
    if( !NITMOD_ParseProtocolFloat(token, value) ) return 0;
    if( negative ) *value = -*value;
    return 1;
}

/* BG_RW_ParseDefinition's ammo destination is a separate object from the
 * private weapon record. Use native members, never original byte offsets. */
static int *AmmoField( ammotable_t *ammo, const char *name ) {
    if( !ammo ) return NULL;
    if( !strcmp(name, "maxammo") ) return &ammo->maxammo;
    if( !strcmp(name, "maxclip") ) return &ammo->maxclip;
    if( !strcmp(name, "defaultStartingAmmo") ) return &ammo->defaultStartingAmmo;
    if( !strcmp(name, "defaultStartingClip") ) return &ammo->defaultStartingClip;
    if( !strcmp(name, "reloadTime") ) return &ammo->reloadTime;
    if( !strcmp(name, "fireDelayTime") ) return &ammo->fireDelayTime;
    if( !strcmp(name, "nextShotTime") ) return &ammo->nextShotTime;
    if( !strcmp(name, "maxHeat") ) return &ammo->maxHeat;
    if( !strcmp(name, "coolRate") ) return &ammo->coolRate;
    return NULL;
}

static int Block( tokenStream_t *stream, int selected, unsigned int *mask,
    ammotable_t *ammo, nitmodWeaponRecoil_t *recoil, nitmodWeaponOptions_t *options ) {
    const char *token = Next(stream);
    int depth = 1, value, isMask, *field;
    if( !token || strcmp(token, "{") ) return 0;
    while( (token = Next(stream)) != 0 ) {
        if( !strcmp(token, "}") ) {
            if( --depth == 0 ) return 1;
        } else if( !strcmp(token, "{") ) {
            if( selected || ++depth > 64 ) return 0;
        } else if( selected ) {
            if( options && !strcmp(token, "noMidclipReload") ) {
                options->noMidclipReload = 1;
                continue;
            }
            if( recoil && !strcmp(token, "recoilDuration") ) {
                if( !ReadInteger(stream, &recoil->duration) ) return 0;
                recoil->enabled = 1;
                continue;
            }
            if( recoil && (!strcmp(token, "recoilYaw") || !strcmp(token, "recoilPitch")) ) {
                float *angle = !strcmp(token, "recoilYaw") ? &recoil->yaw : &recoil->pitch;
                if( !ReadFloat(stream, angle) ) return 0;
                recoil->enabled = 1;
                continue;
            }
            /* Resolve the borrowed key before reading the next token. */
            isMask = !strcmp(token, "classes");
            field = AmmoField(ammo, token);
            if( !isMask && !field ) return 0;
            if( !ReadInteger(stream, &value) ) return 0;
            if( isMask ) *mask = (unsigned int)value;
            else *field = value;
        }
    }
    return 0;
}

static int ParseDefinition( nitmodWeaponTokenReader_t readToken,
    void *context, int alternate, unsigned int *mask, ammotable_t *ammo,
    nitmodWeaponRecoil_t *recoil, nitmodWeaponOptions_t *options ) {
    tokenStream_t stream;
    const char *token;
    unsigned int nextMask = 0;
    int selected;
    if( !readToken || !mask ) return 0;
    stream.read = readToken; stream.context = context; stream.remaining = 65536;
    token = Next(&stream);
    if( !token || strcmp(token, "weaponDef") ) return 0;
    token = Next(&stream);
    if( !token || strcmp(token, "{") ) return 0;
    while( (token = Next(&stream)) != 0 ) {
        if( !strcmp(token, "}") ) {
            *mask = nextMask;
            return 1;
        }
        if( !strcmp(token, "client") ) selected = 0;
        else if( !strcmp(token, "both") ) selected = !alternate;
        else if( !strcmp(token, "both_altweap") ) selected = !!alternate;
        else return 0;
        if( !Block(&stream, selected, &nextMask, ammo, recoil, options) ) return 0;
    }
    return 0;
}

int NITMOD_ParseWeaponClassMask( nitmodWeaponTokenReader_t readToken,
    void *context, int alternate, unsigned int *mask ) {
    return ParseDefinition(readToken, context, alternate, mask, NULL, NULL, NULL);
}

int NITMOD_ParseWeaponAmmo( nitmodWeaponTokenReader_t readToken,
    void *context, int alternate, ammotable_t *ammo, unsigned int *mask ) {
    ammotable_t nextAmmo;
    unsigned int nextMask;
    if( !ammo || !mask ) return 0;
    nextAmmo = *ammo;
    if( !ParseDefinition(readToken, context, alternate, &nextMask, &nextAmmo, NULL, NULL) ) return 0;
    *ammo = nextAmmo;
    *mask = nextMask;
    return 1;
}

int NITMOD_ParseWeaponRecoil( nitmodWeaponTokenReader_t readToken,
    void *context, int alternate, ammotable_t *ammo, unsigned int *mask,
    nitmodWeaponRecoil_t *recoil ) {
    ammotable_t nextAmmo;
    unsigned int nextMask;
    nitmodWeaponRecoil_t nextRecoil;
    if( !ammo || !mask || !recoil ) return 0;
    nextAmmo = *ammo;
    memset(&nextRecoil, 0, sizeof(nextRecoil));
    if( !ParseDefinition(readToken, context, alternate, &nextMask, &nextAmmo, &nextRecoil, NULL) ) return 0;
    *ammo = nextAmmo;
    *mask = nextMask;
    *recoil = nextRecoil;
    return 1;
}

int NITMOD_ParseWeaponOptions( nitmodWeaponTokenReader_t readToken,
    void *context, int alternate, ammotable_t *ammo, unsigned int *mask,
    nitmodWeaponRecoil_t *recoil, nitmodWeaponOptions_t *options ) {
    ammotable_t nextAmmo;
    unsigned int nextMask;
    nitmodWeaponRecoil_t nextRecoil;
    nitmodWeaponOptions_t nextOptions;
    if( !ammo || !mask || !recoil || !options ) return 0;
    nextAmmo = *ammo;
    memset(&nextRecoil, 0, sizeof(nextRecoil));
    memset(&nextOptions, 0, sizeof(nextOptions));
    if( !ParseDefinition(readToken, context, alternate, &nextMask, &nextAmmo, &nextRecoil, &nextOptions) ) return 0;
    *ammo = nextAmmo;
    *mask = nextMask;
    *recoil = nextRecoil;
    *options = nextOptions;
    return 1;
}
