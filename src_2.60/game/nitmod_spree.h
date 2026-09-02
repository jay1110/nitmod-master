/* Positive kill-spree subset of the recovered G_UpdateKillingSpree.
 * Per-client ownership and death/connection lifecycle belong to qagame. */
#ifndef NITMOD_SPREE_H
#define NITMOD_SPREE_H

typedef struct {
	int kills;
} nitmodKillSpree_t;

void NITMOD_ResetKillSpree( nitmodKillSpree_t *state );
/* Records one qualifying enemy kill. Returns announcement detail 0..5,
 * or -1 when this kill should not produce an announcement. */
int NITMOD_RecordSpreeKill( nitmodKillSpree_t *state, int announcerFlags );

#endif
