#ifndef NITMOD_SCORE_H
#define NITMOD_SCORE_H

#include "nitmod_skills.h"
/* Original G_SetPlayerScore: truncate after EACH ordered addition.
 * Reject nonfinite/out-of-range intermediates without modifying output. */
int NITMOD_CalculateScore( const float points[NITMOD_SKILL_COUNT], int *output );

#endif
