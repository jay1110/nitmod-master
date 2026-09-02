#ifndef G_NITMOD_AIR_H
#define G_NITMOD_AIR_H
struct gentity_s;
/* Updates native fields; returns the drowning damage for this tick.
 * Callers still own sound, pain timer, damage dispatch and noclip return. */
int G_NITMOD_UpdateClientAir( struct gentity_s *entity, int now,
	unsigned int battleSenseUnlocked );
#endif
