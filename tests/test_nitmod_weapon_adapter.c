#include "g_local.h"
#include "g_nitmod_teamcount.h"
level_locals_t level;
gentity_t g_entities[MAX_GENTITIES];
static gclient_t clients[MAX_CLIENTS], before[MAX_CLIENTS];
static int war, missing;
static int pickAny, medicRestricted, stenOverride;
static int heavyZero, sendCount, sentSlot, sentReason;
static int publications, badPublication, expectedLatch;
void ClientUserinfoChanged( int slot ) {
    publications++;
    if( slot != 0 || clients[0].sess.latchPlayerWeapon != expectedLatch ||
        clients[0].sess.latchPlayerWeapon2 != WP_LUGER ) badPublication = 1;
}
void NITMOD_SendWeaponLimitMessage( int slot, int reason ) {
    sendCount++; sentSlot = slot; sentReason = reason;
}
void trap_Cvar_Register( vmCvar_t *cvar, const char *name, const char *value, int flags ) { }
void trap_Cvar_Update(vmCvar_t *cvar) { fprintf(stderr, "unexpected Cvar update in read-only adapter test\n"); exit(2); }
void trap_Cvar_VariableStringBuffer( const char *name, char *buffer, int size ) {
    const char *value = "0";
    if( !strcmp(name, "g_heavyWeaponRestriction") ) value = heavyZero ? "0" : "100";
    else if( !strcmp(name, "sv_maxclients") ) value = "20";
    else if( !strcmp(name, "g_war") ) value = war ? "1" : "0";
    else if( !strcmp(name, "g_pickAnyWeapon") ) value = pickAny ? "1" : "0";
    else if( !strcmp(name, "g_medics") ) value = medicRestricted ? "4" : "0";
    else if( !strcmp(name, "g_weapons") ) value = stenOverride ? "512" : "0";
    else if( !strcmp(name, "team_maxriflegrenades") ) value = "1";
    else if( !strncmp(name, "team_max", 8) ) value = "-1";
    if( missing && !strcmp(name, "g_weapons") ) value = "";
    strncpy(buffer, value, size - 1); buffer[size - 1] = '\0';
}
#define CHECK(x) do { if( !(x) ) { fprintf(stderr, "line %d: %s\n", __LINE__, #x); return 1; } } while(0)
static int CheckDecision( int weapon, int pickup, int silent, int decision, int limit, int message ) {
    nitmodWeaponPolicyResult_t result;
    memcpy(before, clients, sizeof(clients));
    result = G_NITMOD_EvaluateServerWeaponPolicy(&g_entities[0], weapon, pickup, silent);
    CHECK( result.decision == decision && result.limit == limit && result.messageReason == message );
    CHECK( !memcmp(before, clients, sizeof(clients)) );
    return 0;
}
int main( void ) {
    nitmodWeaponPolicyResult_t result;
    gentity_t detached;
    level.clients = clients;
    level.numConnectedClients = level.numNonSpectatorClients = 2;
    level.sortedClients[0] = 0; level.sortedClients[1] = 1;
    g_entities[0].client = &clients[0];
    clients[0].sess.sessionTeam = clients[1].sess.sessionTeam = TEAM_AXIS;
    clients[0].sess.playerType = PC_SOLDIER;
    G_NITMOD_ResetTeamPopulation();
    CHECK( !CheckDecision(WP_PANZERFAUST, 0, 0, NITMOD_WEAPON_DENY, NITMOD_LIMIT_INVALID, 0) );
    war = 1;
    CHECK( !CheckDecision(WP_PANZERFAUST, 0, 0, NITMOD_WEAPON_ALLOW, NITMOD_LIMIT_NONE, 0) );
    war = 0;
    CHECK( G_NITMOD_RefreshTeamPopulation() );
    CHECK( !CheckDecision(WP_PANZERFAUST, 0, 0, NITMOD_WEAPON_ALLOW, NITMOD_LIMIT_NONE, 0) );
    clients[1].sess.playerWeapon = WP_CARBINE;
    clients[1].sess.rifleGrenadeStatus = 1;
    CHECK( !CheckDecision(WP_GPG40, 0, 0, NITMOD_WEAPON_DENY, NITMOD_LIMIT_FIXED, 0) );
    clients[1].sess.rifleGrenadeStatus = 0;
    CHECK( !CheckDecision(WP_GPG40, 0, 0, NITMOD_WEAPON_ALLOW, NITMOD_LIMIT_NONE, 0) );
    CHECK( !CheckDecision(WP_STEN, 1, 0, NITMOD_WEAPON_DENY, NITMOD_LIMIT_NONE, 0) );
    clients[0].sess.playerType = PC_COVERTOPS;
    CHECK( !CheckDecision(WP_STEN, 0, 0, NITMOD_WEAPON_ALLOW, NITMOD_LIMIT_NONE, 0) );
    missing = 1;
    CHECK( !CheckDecision(WP_STEN, 0, 0, NITMOD_WEAPON_DENY, NITMOD_LIMIT_INVALID, 0) );
    missing = 0; clients[0].sess.sessionTeam = TEAM_SPECTATOR;
    G_NITMOD_ResetTeamPopulation();
    CHECK( !CheckDecision(WP_PANZERFAUST, 0, 0, NITMOD_WEAPON_DENY, NITMOD_LIMIT_NONE, 0) );
    clients[0].sess.sessionTeam = TEAM_AXIS;
    clients[0].sess.playerType = PC_SOLDIER;
    CHECK( G_NITMOD_RefreshTeamPopulation() );
    heavyZero = 1;
    memcpy(before, clients, sizeof(clients));
    result = G_NITMOD_CheckWeaponAndNotify(&g_entities[0], WP_PANZERFAUST, 0, 0);
    CHECK( result.decision == NITMOD_WEAPON_DENY && result.messageReason == 19 );
    CHECK( sendCount == 1 && sentSlot == 0 && sentReason == 19 );
    CHECK( !memcmp(before, clients, sizeof(clients)) );
    result = G_NITMOD_CheckWeaponAndNotify(&g_entities[0], WP_PANZERFAUST, 0, 1);
    CHECK( result.decision == NITMOD_WEAPON_DENY && !result.messageReason && sendCount == 1 );
    clients[0].ps.pm_flags = PMF_LIMBO;
    result = G_NITMOD_CheckWeaponAndNotify(&g_entities[0], WP_PANZERFAUST, 0, 0);
    CHECK( !result.messageReason && sendCount == 1 );
    clients[0].ps.pm_flags = 0;
    clients[0].sess.playerType = PC_MEDIC;
    result = G_NITMOD_CheckWeaponAndNotify(&g_entities[0], WP_PANZERFAUST, 0, 0);
    CHECK( !result.messageReason && sendCount == 1 );
    war = 1;
    result = G_NITMOD_CheckWeaponAndNotify(&g_entities[0], WP_PANZERFAUST, 0, 0);
    CHECK( result.decision == NITMOD_WEAPON_ALLOW && sendCount == 1 );
    missing = 1;
    result = G_NITMOD_CheckWeaponAndNotify(&g_entities[0], WP_PANZERFAUST, 0, 0);
    CHECK( result.limit == NITMOD_LIMIT_INVALID && sendCount == 1 );
    detached = g_entities[0];
    result = G_NITMOD_CheckWeaponAndNotify(&detached, WP_PANZERFAUST, 0, 0);
    CHECK( result.limit == NITMOD_LIMIT_INVALID && sendCount == 1 );
    result = G_NITMOD_CheckWeaponAndNotify(NULL, WP_PANZERFAUST, 0, 0);
    CHECK( result.limit == NITMOD_LIMIT_INVALID && sendCount == 1 );
    g_entities[0].client = &clients[1];
    result = G_NITMOD_CheckWeaponAndNotify(&g_entities[0], WP_PANZERFAUST, 0, 0);
    CHECK( result.limit == NITMOD_LIMIT_INVALID && sendCount == 1 );
    /* Complete real Cvar -> counts -> policy -> notification -> latch path. */
    g_entities[0].client = &clients[0];
    clients[0].sess.sessionTeam = TEAM_AXIS;
    clients[0].sess.playerType = PC_SOLDIER;
    clients[0].sess.latchPlayerWeapon = WP_MP40;
    clients[0].sess.latchPlayerWeapon2 = WP_COLT;
    missing = war = heavyZero = 0;
    CHECK( G_NITMOD_RefreshTeamPopulation() );
    expectedLatch = WP_PANZERFAUST;
    sendCount = 0;
    CHECK( G_NITMOD_SetClientWeapons(&g_entities[0], WP_PANZERFAUST, WP_LUGER, 1) == 1 );
    CHECK( publications == 1 && !badPublication && !sendCount );
    memcpy(before, clients, sizeof(clients));
    CHECK( G_NITMOD_SetClientWeapons(&g_entities[0], WP_PANZERFAUST, WP_LUGER, 1) == 0 );
    CHECK( publications == 1 && !memcmp(before, clients, sizeof(clients)) );
    heavyZero = 1; expectedLatch = WP_NONE;
    CHECK( G_NITMOD_SetClientWeapons(&g_entities[0], WP_PANZERFAUST, WP_LUGER, 1) == 1 );
    CHECK( publications == 2 && sendCount == 1 && sentReason == 19 && !badPublication );
    CHECK( G_NITMOD_SetClientWeapons(&g_entities[0], WP_PANZERFAUST, WP_LUGER, 1) == 0 );
    CHECK( publications == 2 && sendCount == 2 ); /* original repeats denial, not clientinfo */
    missing = 1;
    memcpy(before, clients, sizeof(clients));
    CHECK( G_NITMOD_SetClientWeapons(&g_entities[0], WP_PANZERFAUST, WP_COLT, 1) == -1 );
    CHECK( publications == 2 && sendCount == 2 && !memcmp(before, clients, sizeof(clients)) );
    /* SetTeam assigns the new team before refresh, using the existing
     * sorted list until ClientBegin/CalculateRanks rebuilds it. */
    missing = heavyZero = 0;
    clients[0].sess.sessionTeam = TEAM_AXIS;
    clients[1].sess.sessionTeam = TEAM_ALLIES;
    clients[1].sess.playerWeapon = WP_PANZERFAUST;
    CHECK( G_NITMOD_RefreshTeamPopulation() );
    clients[0].sess.sessionTeam = TEAM_ALLIES;
    CHECK( !CheckDecision(WP_PANZERFAUST, 0, 0, NITMOD_WEAPON_DENY, NITMOD_LIMIT_HEAVY, 19) );
    CHECK( G_NITMOD_RefreshTeamPopulation() );
    CHECK( !CheckDecision(WP_PANZERFAUST, 0, 0, NITMOD_WEAPON_ALLOW, NITMOD_LIMIT_NONE, 0) );
    expectedLatch = WP_PANZERFAUST;
    CHECK( G_NITMOD_SetClientWeapons(&g_entities[0], WP_PANZERFAUST, WP_LUGER, 0) == 1 );
    CHECK( publications == 2 && sendCount == 2 && !badPublication );
    missing = heavyZero = 0;
    memcpy(before, clients, sizeof(clients));
    G_NITMOD_ResetTeamPopulation();
    CHECK( G_NITMOD_SetClientWeapons(&g_entities[0], WP_PANZERFAUST, WP_LUGER, 1) == -1 );
    CHECK( publications == 2 && sendCount == 2 && !memcmp(before, clients, sizeof(clients)) );
    CHECK( G_NITMOD_CanPickupWeapon(&g_entities[0], WP_STEN, 0) == -1 );
    CHECK( G_NITMOD_RefreshTeamPopulation() );
    clients[0].sess.playerType = PC_MEDIC;
    CHECK( G_NITMOD_CanPickupWeapon(&g_entities[0], WP_STEN, 2) == 0 ); /* mask cannot bypass restriction */
    stenOverride = 1;
    CHECK( G_NITMOD_CanPickupWeapon(&g_entities[0], WP_STEN, 0) == 1 );
    medicRestricted = 1;
    CHECK( G_NITMOD_CanPickupWeapon(&g_entities[0], WP_STEN, 0) == 0 );
    CHECK( G_NITMOD_CanPickupWeapon(&g_entities[0], WP_STEN, 2) == 1 );
    pickAny = 1; stenOverride = 0;
    CHECK( G_NITMOD_CanPickupWeapon(&g_entities[0], WP_STEN, 0) == 1 );
    war = 1;
    CHECK( G_NITMOD_CanPickupWeapon(&g_entities[0], WP_STEN, 31) == 0 );
    CHECK( G_NITMOD_CanPickupWeapon(&g_entities[0], WP_PANZERFAUST, 0) == 1 );
    war = 0; heavyZero = 1;
    clients[0].sess.playerType = PC_SOLDIER;
    sendCount = 0; memcpy(before, clients, sizeof(clients));
    CHECK( G_NITMOD_CanPickupWeapon(&g_entities[0], WP_PANZERFAUST, 31) == 0 );
    CHECK( sendCount == 1 && sentReason == 19 && !memcmp(before, clients, sizeof(clients)) );
    missing = 1;
    CHECK( G_NITMOD_CanPickupWeapon(&g_entities[0], WP_PANZERFAUST, 31) == -1 && sendCount == 1 );
    CHECK( G_NITMOD_CanPickupWeapon(NULL, WP_STEN, 0) == -1 );
    return 0;
}
