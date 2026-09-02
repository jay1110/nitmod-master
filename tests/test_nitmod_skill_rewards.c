#include <limits.h>
#include <stdio.h>
#include "cg_nitmod_skill_rewards.h"

int main( void ) {
    int skill, level;
    if( CG_NITMOD_SkillRewardText(-1, 1) || CG_NITMOD_SkillRewardText(7, 1) ||
        CG_NITMOD_SkillRewardText(0, 0) || CG_NITMOD_SkillRewardText(0, 6) ||
        CG_NITMOD_SkillRewardText(INT_MAX, 1) || CG_NITMOD_SkillRewardText(0, INT_MIN) ) return 1;
    for( skill = 0; skill < 7; skill++ ) {
        for( level = 1; level < 6; level++ ) {
            const char *text = CG_NITMOD_SkillRewardText(skill, level);
            if( !text || !*text ) return 1;
            puts(text);
        }
    }
    return 0;
}
