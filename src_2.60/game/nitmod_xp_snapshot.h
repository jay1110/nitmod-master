#ifndef NITMOD_XP_SNAPSHOT_H
#define NITMOD_XP_SNAPSHOT_H
#include "q_shared.h"
#include "bg_public.h"
#include <limits.h>
/* Original ClientEndFrame: signed quotient/remainder, base 32768.
 * STAT_CLIENTS_READY has no remaining multiplayer owner in this mod. */
#define STAT_NITMOD_XP_HIGH STAT_CLIENTS_READY
static inline int NITMOD_XPInteger(double value) {
    if(value >= INT_MAX) return INT_MAX;
    if(value <= INT_MIN) return INT_MIN;
    if(value != value) return 0;
    return (int)value;
}
static inline void NITMOD_SetSnapshotXP(playerState_t *state, int total) {
    state->stats[STAT_NITMOD_XP_HIGH] = total / 32768;
    state->stats[STAT_XP] = total % 32768;
}
static inline int NITMOD_SnapshotXP(const playerState_t *state) {
    return NITMOD_XPInteger((double)state->stats[STAT_NITMOD_XP_HIGH] * 32768.0 + state->stats[STAT_XP]);
}
#endif
