#ifndef CG_NITMOD_SKILL_REWARDS_H
#define CG_NITMOD_SKILL_REWARDS_H

/* Original Nitmod strings, levels 1..5; NULL for unsupported indices.
 * Used for both Nitmod layouts; presentation does not grant abilities. */
const char *CG_NITMOD_SkillRewardText( int skill, int level );
void CG_NitmodSkillLoadoutUpgrade(int skill, int oldMask, int newMask, int playerClass);

#endif
