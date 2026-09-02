#include <limits.h>
#include "nitmod_score.h"

int NITMOD_CalculateScore( const float points[NITMOD_SKILL_COUNT], int *output ) {
	int skill, score = 0;
	double next;
	if( !points || !output ) return 0;
	for( skill = 0; skill < NITMOD_SKILL_COUNT; skill++ ) {
		/* Keep the integer accumulator exact rather than first rounding it
		 * to float, as a native SSE/WASM compound assignment would do. */
		next = (double)score + points[skill];
		if( !(next >= INT_MIN && next <= INT_MAX) ) return 0;
		score = (int)next;
	}
	*output = score;
	return 1;
}
