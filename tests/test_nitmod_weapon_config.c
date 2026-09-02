#include "g_local.h"
#include "g_nitmod_restrictions.h"
static const char *names[] = {
    "g_war", "g_pickAnyWeapon", "g_weapons", "g_heavyWeaponRestriction",
    "sv_maxclients", "team_panzerRestriction", "team_maxPanzers",
    "team_maxFlamers", "team_maxMG42s", "team_maxMortars", "team_maxriflegrenades"
};
static const char *values[] = { "3", "1", "-1", "100", "32", "20", "-1", "2", "3", "4", "5" };
static int badIndex = -1, calls, unknown;
static const char *badValue;
static const char *medicValue = "0";
static int registrations, badRegistration;
void trap_Cvar_Register( vmCvar_t *cvar, const char *name, const char *value, int flags ) {
    int i;
    registrations++;
    if( !strcmp(name, "g_medics") ) {
        if( cvar || flags || strcmp(value, "0") ) badRegistration = 1;
        return;
    }
    for( i = 0; i < 11; i++ ) if( !strcmp(name, names[i]) ) {
        if( cvar || flags || i == 3 || i == 4 || i == 6 ||
            strcmp(value, i >= 7 ? "-1" : "0") ) badRegistration = 1;
        return;
    }
    badRegistration = 1;
}
void trap_Cvar_VariableStringBuffer( const char *name, char *buffer, int size ) {
    int i;
    calls++;
    if( !strcmp(name, "g_medics") ) {
        strncpy(buffer, medicValue, size - 1); buffer[size - 1] = 0; return;
    }
    for( i = 0; i < 11; i++ ) if( !strcmp(name, names[i]) ) {
        strncpy(buffer, i == badIndex ? badValue : values[i], size - 1);
        buffer[size - 1] = '\0';
        return;
    }
    unknown = 1; buffer[0] = '\0';
}
#define CHECK(test) do { if( !(test) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
int main( void ) {
    static const char *invalid[] = { "", "1x", " 1", "1.0", "2147483648", "-2147483649" };
    nitmodWeaponPolicyInput_t input, expected, before;
    nitmodGameState_t state, expectedState;
    int i, j;
    char oversized[MAX_CVAR_VALUE_STRING + 8];
    unsigned int medicOptions;
    G_NITMOD_RegisterWeaponConfiguration();
    CHECK( registrations == 9 && !badRegistration );
    G_NITMOD_RegisterWeaponConfiguration();
    CHECK( registrations == 18 && !badRegistration );
    memset(&input, 0x5a, sizeof(input)); expected = input;
    expected.warMode = 3; expected.pickAnyWeapon = 1; expected.weaponsOptions = ~0u;
    expected.heavyPercent = 100; expected.maxClients = 32; expected.panzerPercent = 20;
    expected.maxPanzers = -1; expected.maxFlamers = 2; expected.maxMG42s = 3;
    expected.maxMortars = 4; expected.maxRifleGrenades = 5;
    CHECK( G_NITMOD_ReadWeaponConfiguration(&input) );
    CHECK( calls == 11 && !unknown && !memcmp(&input, &expected, sizeof(input)) );
    memset(&state, 0x5a, sizeof(state)); expectedState = state;
    expectedState.panzerRestriction = 20; /* NOT the heavy percentage 100 */
    expectedState.maxPanzers = -1; expectedState.maxMG42s = 3;
    expectedState.maxFlamers = 2; expectedState.maxMortars = 4;
    expectedState.maxRifleGrenades = 5; expectedState.weapons = -1;
    CHECK( G_NITMOD_RefreshWeaponSnapshot(&state) );
    CHECK( !memcmp(&state, &expectedState, sizeof(state)) );
    for( i = 0; i < 11; i++ ) for( j = 0; j < 6; j++ ) {
        badIndex = i; badValue = invalid[j]; before = input;
        CHECK( !G_NITMOD_ReadWeaponConfiguration(&input) );
        CHECK( !memcmp(&input, &before, sizeof(input)) );
        CHECK( !G_NITMOD_RefreshWeaponSnapshot(&state) );
        CHECK( !memcmp(&state, &expectedState, sizeof(state)) );
    }
    memset(oversized, '0', sizeof(oversized));
    oversized[sizeof(oversized) - 2] = 'x'; oversized[sizeof(oversized) - 1] = '\0';
    badIndex = 0; badValue = oversized; before = input;
    CHECK( !G_NITMOD_ReadWeaponConfiguration(&input) );
    CHECK( !memcmp(&input, &before, sizeof(input)) );
    badIndex = -1; values[2] = "512";
    CHECK( G_NITMOD_ReadWeaponConfiguration(&input) && input.weaponsOptions == 512u );
    expectedState.weapons = 512;
    CHECK( G_NITMOD_RefreshWeaponSnapshot(&state) && !memcmp(&state, &expectedState, sizeof(state)) );
    values[0] = "0"; values[6] = "-2";
    CHECK( G_NITMOD_ReadWeaponConfiguration(&input) && input.warMode == 0 && input.maxPanzers == -2 );
    calls = 0;
    CHECK( !G_NITMOD_ReadWeaponConfiguration(NULL) && calls == 0 );
    CHECK( !G_NITMOD_RefreshWeaponSnapshot(NULL) && calls == 0 );
    CHECK( G_NITMOD_ReadMedicOptions(&medicOptions) && medicOptions == 0 );
    medicValue = "4";
    CHECK( G_NITMOD_ReadMedicOptions(&medicOptions) && medicOptions == 4 );
    medicValue = "-1";
    CHECK( G_NITMOD_ReadMedicOptions(&medicOptions) && medicOptions == ~0u );
    for( j = 0; j < 6; j++ ) {
        medicValue = invalid[j];
        CHECK( !G_NITMOD_ReadMedicOptions(&medicOptions) && medicOptions == ~0u );
    }
    medicValue = oversized;
    CHECK( !G_NITMOD_ReadMedicOptions(&medicOptions) && medicOptions == ~0u );
    CHECK( !G_NITMOD_ReadMedicOptions(NULL) );
    return 0;
}
