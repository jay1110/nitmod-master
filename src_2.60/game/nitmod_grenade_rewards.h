#ifndef NITMOD_GRENADE_REWARDS_H
#define NITMOD_GRENADE_REWARDS_H
#include "nitmod_reward_table.h"
/* Caller provides validated finite, int-range configuration rows.
 * Original class switch CSWTCH.87: soldier/heavy, medic/first aid,
 * engineer/engineering, fieldops/signals, covertops/covert. */
static int NITMOD_GrenadeRewardCount(int cls, const float rows[7][6],
                                   const unsigned int masks[7], int war) {
    int skill = SK_HEAVY_WEAPONS;
    if(war) return 0;
    switch(cls) {
    case PC_MEDIC: skill=SK_FIRST_AID; break;
    case PC_ENGINEER: skill=SK_EXPLOSIVES_AND_CONSTRUCTION; break;
    case PC_FIELDOPS: skill=SK_SIGNALS; break;
    case PC_COVERTOPS: skill=SK_MILITARY_INTELLIGENCE_AND_SCOPED_WEAPONS; break;
    }
    return (int)NITMOD_RewardTableValue(rows[skill],masks[skill]) +
           (int)NITMOD_RewardTableValue(rows[SK_LIGHT_WEAPONS],masks[SK_LIGHT_WEAPONS]);
}
#endif
