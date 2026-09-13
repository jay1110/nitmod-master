#include "nitmod_spree.h"

void NITMOD_ResetKillSpree( nitmodKillSpree_t *state ) {
	state->kills = 0;
}

int NITMOD_RecordSpreeKill( nitmodKillSpree_t *state, int announcerFlags ) {
	/* Original i386 LEA increments modulo 2^32, including Lua-set values.
	 * Unsigned arithmetic preserves that transition without signed overflow. */
	state->kills = (int)( (unsigned int)state->kills + 1u );
	if( ( announcerFlags & 1 ) && state->kills >= 5 &&
		state->kills <= 30 && state->kills % 5 == 0 ) {
		return state->kills / 5 - 1;
	}
	return -1;
}
