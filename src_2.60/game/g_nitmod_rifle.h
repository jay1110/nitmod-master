#ifndef G_NITMOD_RIFLE_H
#define G_NITMOD_RIFLE_H
struct gentity_s;
/* Original owned-and-disabled grenade branch only. Caller must first check
 * demo/follow/health and the complete restriction decision. No active hook.
 * Returns 1 removed, 0 not owned, -1 invalid. Does not drop a base rifle. */
int G_NITMOD_RevokeRifleGrenade( struct gentity_s *entity, int nativeWeapon );
#endif
