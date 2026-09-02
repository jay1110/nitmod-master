#include "g_local.h"
#include "g_nitmod_restrictions.h"
#include "nitmod_protocol.h"
#include <limits.h>

int G_NITMOD_ReadMedicOptions( unsigned int *options ) {
    char text[MAX_CVAR_VALUE_STRING];
    int value;
    if( !options ) return 0;
    memset(text, 0, sizeof(text));
    trap_Cvar_VariableStringBuffer("g_medics", text, sizeof(text));
    text[sizeof(text) - 1] = 0;
    if( strlen(text) == sizeof(text) - 1 || !NITMOD_ParseProtocolSigned(text, &value) ) return 0;
    *options = (unsigned int)value;
    return 1;
}

int G_NITMOD_RefreshWeaponSnapshot( nitmodGameState_t *state ) {
    nitmodWeaponPolicyInput_t input;
    nitmodGameState_t next;
    if( !state ) return 0;
    memset(&input, 0, sizeof(input));
    if( !G_NITMOD_ReadWeaponConfiguration(&input) ) return 0;
    next = *state;
    next.panzerRestriction = input.panzerPercent;
    next.maxPanzers = input.maxPanzers;
    next.maxMG42s = input.maxMG42s;
    next.maxFlamers = input.maxFlamers;
    next.maxMortars = input.maxMortars;
    next.maxRifleGrenades = input.maxRifleGrenades;
    next.weapons = input.weaponsOptions <= INT_MAX ? (int)input.weaponsOptions :
        -1 - (int)(UINT_MAX - input.weaponsOptions);
    *state = next;
    return 1;
}

void G_NITMOD_RegisterWeaponConfiguration( void ) {
    /* Original gameCvarTable entries, verified by extract_weapon_cvars.py.
     * Existing native sv_maxclients/heavy restriction/maxPanzers stay owned
     * by gameCvarTable. These flags are all zero (no latch/reset). */
    static const struct { const char *name; const char *value; int flags; } defaults[] = {
        { "g_war", "0", 0 },
        { "g_pickAnyWeapon", "0", 0 },
        { "g_weapons", "0", 0 },
        { "team_panzerRestriction", "0", 0 },
        { "team_maxFlamers", "-1", 0 },
        { "team_maxMG42s", "-1", 0 },
        { "team_maxMortars", "-1", 0 },
        { "team_maxriflegrenades", "-1", 0 },
        { "g_medics", "0", 0 }
    };
    int i;
    for( i = 0; i < sizeof(defaults) / sizeof(defaults[0]); i++ )
        trap_Cvar_Register(NULL, defaults[i].name, defaults[i].value, defaults[i].flags);
}

int G_NITMOD_ReadWeaponConfiguration( nitmodWeaponPolicyInput_t *input ) {
    static const char *names[] = {
        "g_war", "g_pickAnyWeapon", "g_weapons", "g_heavyWeaponRestriction",
        "sv_maxclients", "team_panzerRestriction", "team_maxPanzers",
        "team_maxFlamers", "team_maxMG42s", "team_maxMortars", "team_maxriflegrenades"
    };
    char text[MAX_CVAR_VALUE_STRING];
    int values[11], i;
    nitmodWeaponPolicyInput_t next;
    if( !input ) return 0;
    for( i = 0; i < 11; i++ ) {
        memset(text, 0, sizeof(text));
        trap_Cvar_VariableStringBuffer(names[i], text, sizeof(text));
        /* Zero/missing and malformed are different: never invent defaults.
         * Decimal validation is deliberately stricter than vmCvar atoi. */
        text[sizeof(text) - 1] = '\0';
        if( strlen(text) == sizeof(text) - 1 ) return 0;
        if( !NITMOD_ParseProtocolSigned(text, &values[i]) ) return 0;
    }
    next = *input;
    next.warMode = values[0];
    next.pickAnyWeapon = values[1];
    next.weaponsOptions = (unsigned int)values[2];
    next.heavyPercent = values[3];
    next.maxClients = values[4];
    next.panzerPercent = values[5];
    next.maxPanzers = values[6];
    next.maxFlamers = values[7];
    next.maxMG42s = values[8];
    next.maxMortars = values[9];
    next.maxRifleGrenades = values[10];
    *input = next;
    return 1;
}
