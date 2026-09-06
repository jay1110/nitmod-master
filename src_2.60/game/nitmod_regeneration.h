#ifndef NITMOD_REGENERATION_H
#define NITMOD_REGENERATION_H

/* ClientTimerActions' eligibility only; outer war/medic gates and rates stay
 * with the server. The sixth-reward route also applies in Deathmatch. */
static int NITMOD_RegenerationEligible(int deathmatch, unsigned int dmOptions,
    unsigned int medicOptions, int livingUnpoisonedMedic, unsigned int firstAid) {
    return (deathmatch ? !!(dmOptions & 2u) : !!livingUnpoisonedMedic) ||
        ((medicOptions & 16u) && (firstAid & 32u));
}
#endif
