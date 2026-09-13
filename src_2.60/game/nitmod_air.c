#include "nitmod_support_time.h"
#include "nitmod_air.h"

int NITMOD_BreathDuration( unsigned int battleSenseUnlocked ) {
	return battleSenseUnlocked & (1u << 5) ? 15000 : 12000;
}

/* Original deadlines and movement remainder use wrapping ADD/SUB. */
int NITMOD_ShiftAirDeadline( int deadline, int delta ) {
	return NITMOD_SupportSignedTime((uint32_t)deadline + (uint32_t)delta);
}

int NITMOD_AirRemaining( int deadline, int now ) {
	return NITMOD_SupportSignedTime((uint32_t)deadline - (uint32_t)now);
}

int NITMOD_AirDeadline( int now, unsigned int battleSenseUnlocked ) {
	return NITMOD_ShiftAirDeadline(now, NITMOD_BreathDuration(battleSenseUnlocked));
}

int NITMOD_UpdateAir( nitmodAirState_t *state, int now, int waterlevel,
	int noclip, int health, unsigned int battleSenseUnlocked ) {
	if( !state || waterlevel < 0 || waterlevel > 3 ) return 0;
	if( noclip || waterlevel != 3 ) {
		state->deadline = NITMOD_AirDeadline(now, battleSenseUnlocked);
		/* Reference noclip returns before resetting accumulated damage. */
		if( !noclip ) state->drowningDamage = 2;
		return 0;
	}
	if( state->deadline >= now ) return 0;
	/* One tick per invocation, incrementing the previous deadline rather
	 * than now: do not introduce a catch-up loop or refresh submerged air. */
	state->deadline = NITMOD_ShiftAirDeadline(state->deadline, 1000);
	if( health <= 0 ) return 0;
	state->drowningDamage = state->drowningDamage >= 13 ? 15 : state->drowningDamage + 2;
	return state->drowningDamage;
}
