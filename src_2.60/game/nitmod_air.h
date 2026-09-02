#ifndef NITMOD_AIR_H
#define NITMOD_AIR_H

typedef struct {
	int deadline;
	int drowningDamage;
} nitmodAirState_t;

int NITMOD_BreathDuration( unsigned int battleSenseUnlocked );
int NITMOD_AirDeadline( int now, unsigned int battleSenseUnlocked );
int NITMOD_ShiftAirDeadline( int deadline, int delta );
int NITMOD_AirRemaining( int deadline, int now );
/* Original P_WorldEffects air branch only. Returns damage to apply, zero
 * otherwise. No sounds, pain timer, lava, fire or native PW_BREATHER handling.
 * state must be initialized by the engine before use. Not yet gameplay-active. */
int NITMOD_UpdateAir( nitmodAirState_t *state, int now, int waterlevel,
	int noclip, int health, unsigned int battleSenseUnlocked );

#endif
