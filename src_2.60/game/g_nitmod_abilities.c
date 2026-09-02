#include "g_local.h"
#include "g_nitmod_abilities.h"

int G_NITMOD_IsDemoClient( int clientNum, int demoState, int demoClients ) {
    return clientNum >= 0 && demoState >= 1 && demoState <= 3 && clientNum < demoClients;
}

int G_NITMOD_CanCheckWeapons( const gentity_t *entity, int isDemoClient ) {
    return entity && entity->client && !isDemoClient &&
        !(entity->client->ps.pm_flags & PMF_FOLLOW) && entity->health > 0;
}

int G_NITMOD_CheckAdrenaline( gentity_t *entity, int isDemoClient,
    unsigned int firstAidUnlocks, unsigned int allowedClasses ) {
    if( !G_NITMOD_CanCheckWeapons(entity, isDemoClient) ) return 0;
    return G_NITMOD_ReconcileAdrenaline(entity->client, firstAidUnlocks, allowedClasses);
}

int G_NITMOD_ClientHasAdrenaline( const gclient_t *client,
    unsigned int firstAidUnlocks, unsigned int allowedClasses ) {
    unsigned int classBit;
    if( !client || !(firstAidUnlocks & (1u << 4)) ) return 0;
    /* Keep the original explicit class mapping; reject invalid classes
     * before any shift. Extra configuration bits do not grant access. */
    switch( client->sess.playerType ) {
    case PC_SOLDIER: classBit = 1u; break;
    case PC_MEDIC: classBit = 2u; break;
    case PC_ENGINEER: classBit = 4u; break;
    case PC_FIELDOPS: classBit = 8u; break;
    case PC_COVERTOPS: classBit = 16u; break;
    default: return 0;
    }
    return (allowedClasses & classBit) != 0;
}

int G_NITMOD_EntityHasAdrenaline( const gentity_t *entity,
    unsigned int firstAidUnlocks, unsigned int allowedClasses ) {
    return entity && G_NITMOD_ClientHasAdrenaline(entity->client,
        firstAidUnlocks, allowedClasses);
}

int G_NITMOD_AdrenalineClip( unsigned int options ) {
    /* G_UpgradeSkill: option bit 2 takes precedence over bit 0. */
    if( options & 4u ) return 1;
    return options & 1u ? 0 : 12;
}

int G_NITMOD_ReconcileAdrenaline( gclient_t *client,
    unsigned int firstAidUnlocks, unsigned int allowedClasses ) {
    /* Same bit-array layout as COM_BitClear; this native weapon occupies
     * bit 14 of word 1 in ET (original Nitmod: bit 11). Keep shifts out
     * of the signed sign bit and use the native symbolic weapon value. */
    typedef char adrenalineBitCheck[(WP_MEDIC_ADRENALINE % 32 < 31) ? 1 : -1];
    int bit = 1 << (WP_MEDIC_ADRENALINE % 32);
    int *word;
    if( !client ) return 0;
    word = &client->ps.weapons[WP_MEDIC_ADRENALINE / 32];
    if( !(*word & bit) || G_NITMOD_ClientHasAdrenaline(client,
        firstAidUnlocks, allowedClasses) ) return 0;
    *word &= ~bit;
    return 1;
}
