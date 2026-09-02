#include "g_local.h"
#include "g_nitmod_teamcount.h"

static int teamPopulation[2];
static int teamPopulationValid;

void G_NITMOD_ResetTeamPopulation( void ) {
    teamPopulation[0] = teamPopulation[1] = 0;
    teamPopulationValid = 0;
}

int G_NITMOD_RefreshTeamPopulation( void ) {
    int next[2] = { 0, 0 }, i, number, team;
    teamPopulationValid = 0;
    if( !level.clients || level.numConnectedClients < 0 ||
        level.numConnectedClients > MAX_CLIENTS ) return 0;
    for( i = 0; i < level.numConnectedClients; i++ ) {
        number = level.sortedClients[i];
        if( number < 0 || number >= MAX_CLIENTS ) return 0;
        team = level.clients[number].sess.sessionTeam;
        if( team == TEAM_AXIS ) next[0]++;
        else if( team == TEAM_ALLIES ) next[1]++;
    }
    teamPopulation[0] = next[0]; teamPopulation[1] = next[1];
    teamPopulationValid = 1;
    return 1;
}

int G_NITMOD_ReadCachedWeaponCounts( gentity_t *requester, int nativeWeapon,
    nitmodWeaponPolicyInput_t *input ) {
    nitmodWeaponPolicyInput_t next;
    int team;
    if( !requester || !requester->client || !input ) return 0;
    team = requester->client->sess.sessionTeam;
    if( (team == TEAM_AXIS || team == TEAM_ALLIES) && !teamPopulationValid ) return 0;
    next = *input;
    if( !G_NITMOD_ReadWeaponCounts(requester, nativeWeapon, &next) ) return 0;
    if( team == TEAM_AXIS || team == TEAM_ALLIES )
        next.teamSize = teamPopulation[team == TEAM_ALLIES];
    *input = next;
    return 1;
}

int G_NITMOD_CountRifleGrenades( const gentity_t *requester,
    int nativeWeapon, const unsigned char *granted, int slotCount ) {
    weapon_t base;
    int i, number, count = 0;
    const gclient_t *other;
    if( !requester || !requester->client || !granted || slotCount < 0 ||
        slotCount > MAX_CLIENTS || !level.clients || level.numConnectedClients < 0 ||
        level.numConnectedClients > MAX_CLIENTS || level.numNonSpectatorClients < 0 ||
        level.numNonSpectatorClients > level.numConnectedClients ) return -1;
    if( nativeWeapon == WP_GPG40 ) base = WP_KAR98;
    else if( nativeWeapon == WP_M7 ) base = WP_CARBINE;
    else return -1;
    for( i = 0; i < level.numNonSpectatorClients; i++ ) {
        number = level.sortedClients[i];
        if( number < 0 || number >= slotCount ) return -1;
        if( &g_entities[number] == requester ) continue;
        other = &level.clients[number];
        if( other->sess.sessionTeam != requester->client->sess.sessionTeam || !granted[number] ) continue;
        if( other->sess.playerWeapon == base || other->sess.latchPlayerWeapon == base ) count++;
    }
    return count;
}

int G_NITMOD_CountSessionRifleGrenades( const gentity_t *requester,
    int nativeWeapon ) {
    unsigned char granted[MAX_CLIENTS];
    int i, number;
    if( !level.clients || level.numConnectedClients < 0 ||
        level.numConnectedClients > MAX_CLIENTS ) return -1;
    memset(granted, 0, sizeof(granted));
    for( i = 0; i < level.numConnectedClients; i++ ) {
        number = level.sortedClients[i];
        if( number < 0 || number >= MAX_CLIENTS ) return -1;
        granted[number] = level.clients[number].sess.rifleGrenadeStatus != 0;
    }
    return G_NITMOD_CountRifleGrenades(requester, nativeWeapon, granted, MAX_CLIENTS);
}

/* Original weapTeamConversion at ELF 0x2a5220, mapped by item identity. */
static weapon_t TeamEquivalent( weapon_t weapon ) {
    switch( weapon ) {
    case WP_LUGER: return WP_COLT;
    case WP_COLT: return WP_LUGER;
    case WP_MP40: return WP_THOMPSON;
    case WP_THOMPSON: return WP_MP40;
    case WP_GRENADE_LAUNCHER: return WP_GRENADE_PINEAPPLE;
    case WP_GRENADE_PINEAPPLE: return WP_GRENADE_LAUNCHER;
    case WP_SILENCER: return WP_SILENCED_COLT;
    case WP_SILENCED_COLT: return WP_SILENCER;
    case WP_KAR98: return WP_CARBINE;
    case WP_CARBINE: return WP_KAR98;
    case WP_GARAND: return WP_K43;
    case WP_K43: return WP_GARAND;
    case WP_AKIMBO_COLT: return WP_AKIMBO_LUGER;
    case WP_AKIMBO_LUGER: return WP_AKIMBO_COLT;
    case WP_GARAND_SCOPE: return WP_K43_SCOPE;
    case WP_K43_SCOPE: return WP_GARAND_SCOPE;
    case WP_AKIMBO_SILENCEDCOLT: return WP_AKIMBO_SILENCEDLUGER;
    case WP_AKIMBO_SILENCEDLUGER: return WP_AKIMBO_SILENCEDCOLT;
    /* GPG40/M7 use a separate original eligibility path, not this mapping.
     * Retain native exact-match behavior until that state is integrated. */
    default: return weapon;
    }
}

int G_NITMOD_ReadWeaponCounts( gentity_t *requester, int nativeWeapon,
    nitmodWeaponPolicyInput_t *input ) {
    int i, number, requesterSlot = -1, count = 0, opposite = 0, teamSize, rifle;
    weapon_t equivalent;
    const gclient_t *other;
    if( !requester || !requester->client || !input || !level.clients ||
        nativeWeapon < WP_NONE || nativeWeapon >= WP_NUM_WEAPONS ||
        level.numConnectedClients < 0 || level.numConnectedClients > MAX_CLIENTS ||
        level.numNonSpectatorClients < 0 ||
        level.numNonSpectatorClients > level.numConnectedClients ) return 0;
    /* Establish requester identity without subtracting unrelated pointers. */
    for( i = 0; i < MAX_CLIENTS; i++ )
        if( requester == &g_entities[i] ) { requesterSlot = i; break; }
    if( requesterSlot < 0 || requester->client != &level.clients[requesterSlot] ) return 0;
    teamSize = requester->client->sess.sessionTeam == TEAM_AXIS ||
        requester->client->sess.sessionTeam == TEAM_ALLIES ? 0 : 1;
    rifle = nativeWeapon == WP_GPG40 || nativeWeapon == WP_M7;
    equivalent = TeamEquivalent((weapon_t)nativeWeapon);
    for( i = 0; i < level.numConnectedClients; i++ ) {
        number = level.sortedClients[i];
        if( number < 0 || number >= MAX_CLIENTS ) return 0;
        other = &level.clients[number];
        if( other->sess.sessionTeam != requester->client->sess.sessionTeam ) continue;
        if( requester->client->sess.sessionTeam == TEAM_AXIS ||
            requester->client->sess.sessionTeam == TEAM_ALLIES ) teamSize++;
        else if( i < level.numNonSpectatorClients && number != requesterSlot ) teamSize++;
        if( i >= level.numNonSpectatorClients || number == requesterSlot ) continue;
        if( rifle ) {
            if( !other->sess.rifleGrenadeStatus ) continue;
            if( other->sess.playerWeapon == WP_KAR98 || other->sess.latchPlayerWeapon == WP_KAR98 )
                { if( nativeWeapon == WP_GPG40 ) count++; else opposite++; }
            if( other->sess.playerWeapon == WP_CARBINE || other->sess.latchPlayerWeapon == WP_CARBINE )
                { if( nativeWeapon == WP_M7 ) count++; else opposite++; }
        } else if( other->sess.playerWeapon == nativeWeapon ||
            other->sess.latchPlayerWeapon == nativeWeapon || other->sess.playerWeapon == equivalent ||
            other->sess.latchPlayerWeapon == equivalent ) count++;
    }
    input->teamSize = teamSize;
    input->weaponCount = count;
    input->oppositeRifleCount = opposite;
    return 1;
}

int G_TeamCount( gentity_t *ent, weapon_t weapon ) {
    int i, number, count = weapon == -1 ? 1 : 0;
    weapon_t equivalent = TeamEquivalent(weapon);
    gclient_t *other;
    for( i = 0; i < level.numConnectedClients; i++ ) {
        number = level.sortedClients[i];
        if( number == ent - g_entities ) continue;
        other = &level.clients[number];
        if( other->sess.sessionTeam != ent->client->sess.sessionTeam ) continue;
        if( weapon != -1 && other->sess.playerWeapon != weapon &&
            other->sess.latchPlayerWeapon != weapon && other->sess.playerWeapon != equivalent &&
            other->sess.latchPlayerWeapon != equivalent ) continue;
        count++;
    }
    return count;
}
