#include <stddef.h>
#include <string.h>
#include "q_shared.h"
#include "bg_public.h"
#include "nitmod_weapon_definition.h"
#include "nitmod_weapon_recoil.h"
typedef struct { const char **tokens; int index, end; } input_t;
static const char *Next( void *context ) {
    input_t *input = context;
    return input->index < input->end ? input->tokens[input->index++] : NULL;
}
static int CheckMetadata(void) {
    const char *tokens[] = {
        "weaponDef", "{", "both", "{", "name", "\1Poison Bomb",
        "damage", "18", "splashdamage", "20", "splashdamage_radius", "120",
        "spread", "400", "SpreadScaleAdd", "15", "SpreadScaleAddRand", "3",
        "minHeadshotDamage", "50", "movementSpeedScale", "0.75",
        "HeadshotRatio", "2.5", "spreadRatio", "-", "0.25",
        "HeadshotWeapon", "\1yes", "DistanceFalloff", "no", "GibbingWeapon", "invalid",
        "velocity2spread", "yes", "viewchange2spread", "no",
        "KillMessage", "\1was killed by", "KillMessage2", "\1}'s weapon {",
        "limboKill", "noMidclipReload", "classes", "31", "maxammo", "99",
        "}", "both_altweap", "{", "damage", "75", "name", "Scoped", "}", "}"
    };
    input_t input;
    ammotable_t ammo, oldAmmo;
    nitmodWeaponOptions_t options, oldOptions;
    nitmodWeaponRecoil_t recoil, oldRecoil;
    unsigned int mask;
    int alt, length = sizeof(tokens) / sizeof(tokens[0]), i;
    memset(&oldAmmo, 0x35, sizeof(oldAmmo));
    memset(&oldOptions, 0x35, sizeof(oldOptions));
    memset(&oldRecoil, 0x35, sizeof(oldRecoil));
    for(alt = 0; alt < 2; ++alt) {
        input.tokens = tokens; input.index = 0; input.end = length;
        ammo = oldAmmo;
        if(!NITMOD_ParseWeaponOptions(Next, &input, alt, &ammo, &mask, &recoil, &options)) return 10;
        if(alt) {
            if(options.damage != 75 || strcmp(options.name, "Scoped") || mask ||
               options.limboKill || options.killMessage[0] || memcmp(&ammo, &oldAmmo, sizeof(ammo))) return 11;
        } else {
            if(strcmp(options.name, "Poison Bomb") || strcmp(options.killMessage, "was killed by") ||
               strcmp(options.killMessage2, "}'s weapon {") || options.damage != 18 ||
               options.splashDamage != 20 || options.splashRadius != 120 || options.spread != 400 ||
               options.spreadScaleAdd != 15 || options.spreadScaleAddRand != 3 ||
               options.minHeadshotDamage != 50 || options.movementSpeedScale != .75f ||
               options.headshotRatio != 2.5f || options.spreadRatio != -.25f ||
               options.headshotWeapon != 1 || options.distanceFalloff != 2 || options.gibbingWeapon ||
               options.velocityToSpread != 1 || options.viewChangeToSpread != 2 ||
               !options.limboKill || !options.noMidclipReload || mask != 31 || ammo.maxammo != 99) return 12;
        }
        for(i = 0; i < length; ++i) {
            input.index = 0; input.end = i; ammo = oldAmmo; options = oldOptions; recoil = oldRecoil; mask = 77;
            if(NITMOD_ParseWeaponOptions(Next, &input, alt, &ammo, &mask, &recoil, &options) ||
               mask != 77 || memcmp(&ammo, &oldAmmo, sizeof(ammo)) ||
               memcmp(&options, &oldOptions, sizeof(options)) || memcmp(&recoil, &oldRecoil, sizeof(recoil))) return 13;
        }
    }
    /* Quoted numeric data cannot silently become a numeric grammar token. */
    tokens[7] = "\1" "18"; input.index = 0; input.end = length;
    if(NITMOD_ParseWeaponOptions(Next, &input, 0, &ammo, &mask, &recoil, &options)) return 14;
    return 0;
}
int main( void ) {
    const char *valid[] = { "weaponDef", "{", "client", "{", "classes", "99", "nested", "{", "x", "}", "}",
        "both", "{", "classes", "3", "classes", "5", "}", "both_altweap", "{", "classes", "-", "1", "}", "}" };
    const char *empty[] = { "weaponDef", "{", "}" };
    const char *unknown[] = { "weaponDef", "{", "both", "{", "name", "classes", "}", "}" };
    const char *overflow[] = { "weaponDef", "{", "both", "{", "classes", "2147483648", "}", "}" };
    const char *badSign[] = { "weaponDef", "{", "both", "{", "classes", "-", "-1", "}", "}" };
    input_t input;
    unsigned int mask;
    int i, alt;
    for( alt = 0; alt < 2; alt++ ) {
        input.tokens = valid; input.index = 0; input.end = 25; mask = 77;
        if( !NITMOD_ParseWeaponClassMask(Next, &input, alt, &mask) || mask != (alt ? ~0u : 5u) ) return 1;
        for( i = 0; i < 25; i++ ) {
            input.index = 0; input.end = i; mask = 77;
            if( NITMOD_ParseWeaponClassMask(Next, &input, alt, &mask) || mask != 77 ) return 2;
        }
    }
    input.tokens = empty; input.index = 0; input.end = 3;
    if( !NITMOD_ParseWeaponClassMask(Next, &input, 0, &mask) || mask ) return 3;
    input.tokens = unknown; input.index = 0; input.end = 8; mask = 77;
    if( NITMOD_ParseWeaponClassMask(Next, &input, 0, &mask) || mask != 77 ) return 4;
    input.tokens = overflow; input.index = 0; input.end = 8;
    if( NITMOD_ParseWeaponClassMask(Next, &input, 0, &mask) || mask != 77 ) return 5;
    input.tokens = badSign; input.index = 0; input.end = 9;
    if( NITMOD_ParseWeaponClassMask(Next, &input, 0, &mask) || mask != 77 ) return 6;
    if( NITMOD_ParseWeaponClassMask(NULL, &input, 0, &mask) ) return 7;
    if( NITMOD_ParseWeaponClassMask(Next, &input, 0, NULL) ) return 8;
    return CheckMetadata();
}
