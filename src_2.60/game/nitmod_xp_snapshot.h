#ifndef NITMOD_XP_SNAPSHOT_H
#define NITMOD_XP_SNAPSHOT_H
#include "q_shared.h"
#include "bg_public.h"
#include <limits.h>
/* Original ClientEndFrame: signed quotient/remainder, base 32768.
 * STAT_CLIENTS_READY has no remaining multiplayer owner in this mod. */
#define STAT_NITMOD_XP_HIGH STAT_CLIENTS_READY
/* Original x87 FISTP with truncation returns integer-indefinite on overflow. */
static inline int NITMOD_OriginalXPInteger(double value) {
    return value >= -2147483648.0 && value < 2147483648.0 ?
        (int)value : (-2147483647 - 1);
}
/* Original G_SendScore_Add 0x51c07..0x51ca9: reload the integer after
 * each skill, add in x87 precision, then truncate to a signed 32-bit value. */
static inline int NITMOD_TotalSkillXP(const float *skills) {
    int total = 0, i;
    for(i = 0; i < SK_NUM_SKILLS; ++i) {
        double sum = (double)total + (double)skills[i];
        total = NITMOD_OriginalXPInteger(sum);
    }
    return total;
}

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
