#ifndef NITMOD_REWARD_TABLE_H
#define NITMOD_REWARD_TABLE_H
/* Original BG_GrenadesForClass: a reward selects its table entry only when
 * it differs from the PREVIOUS table entry, not the previously selected one.
 * This matters for sparse masks and repeated configured values.
 * Caller supplies a validated six-entry configuration row. */
static float NITMOD_RewardTableValue(const float values[6], unsigned int mask) {
    float value = values[0];
    int level;
    for(level = 1; level < 6; ++level)
        if((mask & (1u << level)) && values[level] != values[level-1])
            value = values[level];
    return value;
}
#endif
