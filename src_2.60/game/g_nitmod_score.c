#include "g_local.h"
#include "nitmod_score.h"

typedef char nitmodScoreSkillCountCheck[(SK_NUM_SKILLS == NITMOD_SKILL_COUNT) ? 1 : -1];

void G_SetPlayerScore( gclient_t *client ) {
	int score;
	if( client && NITMOD_CalculateScore(client->sess.skillpoints, &score) ) {
		client->ps.persistant[PERS_SCORE] = score;
	}
}
