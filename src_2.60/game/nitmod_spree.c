#include <limits.h>
#include "nitmod_spree.h"

void NITMOD_ResetKillSpree( nitmodKillSpree_t *state ) {
	state->kills = 0;
}

int NITMOD_RecordSpreeKill( nitmodKillSpree_t *state, int announcerFlags ) {
	/* Saturate outside the announcement range to avoid signed overflow. */
	if( state->kills < INT_MAX ) {
		state->kills++;
	}
	if( ( announcerFlags & 1 ) && state->kills >= 5 &&
		state->kills <= 30 && state->kills % 5 == 0 ) {
		return state->kills / 5 - 1;
	}
	return -1;
}
