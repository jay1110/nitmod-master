#ifndef G_NITMOD_TEAMCOUNT_H
#define G_NITMOD_TEAMCOUNT_H
#include "g_nitmod_restrictions.h"
struct gentity_s;
/* Isolated original rifle-grenade count. granted has one entry per native
 * client slot. The session adapter below supplies persisted equipment state.
 * Returns -1 on invalid input. Does not inspect current ammo/weapon bits.
 * Ordinary active G_TeamCount still retains ET behavior for these queries. */
int G_NITMOD_CountRifleGrenades( const struct gentity_s *requester,
    int nativeWeapon, const unsigned char *granted, int slotCount );
/* Read the reconstructed spawn/session/rn status, never infer it from ammo. */
int G_NITMOD_CountSessionRifleGrenades( const struct gentity_s *requester,
    int nativeWeapon );
/* Atomically read teamSize/weaponCount/oppositeRifleCount. Recalculates the
 * team cache from the current connected list; original cache refresh timing
 * remains unhooked. Configuration is preserved; zero means unchanged/error. */
int G_NITMOD_ReadWeaponCounts( struct gentity_s *requester, int nativeWeapon,
    nitmodWeaponPolicyInput_t *input );
void G_NITMOD_ResetTeamPopulation( void );
int G_NITMOD_RefreshTeamPopulation( void );
/* Axis/Allies use the explicitly refreshed population cache; other teams
 * retain the original live fallback. Failure leaves input unchanged. */
int G_NITMOD_ReadCachedWeaponCounts( struct gentity_s *requester, int nativeWeapon,
    nitmodWeaponPolicyInput_t *input );
#endif
