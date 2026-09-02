#include <stdio.h>
#include "nitmod_skills.h"
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
int main( void ) {
    nitmodSkillThresholds_t thresholds;
    nitmodSkillProgress_t result;
    int skill, level, cap;
    NITMOD_DefaultSkillThresholds(&thresholds);
    for( skill = 0; skill < 7; skill++ ) {
        for( level = 1; level < 6; level++ ) {
            float points = (float)thresholds.threshold[skill][level];
            CHECK( NITMOD_EvaluateSkill(&thresholds, skill, points - 0.5f, 6, 0, &result) );
            CHECK( result.level == level - 1 && result.unlocked == (1u << level) - 2u );
            CHECK( NITMOD_EvaluateSkill(&thresholds, skill, points, 6, 0, &result) );
            CHECK( result.level == level && result.unlocked == (1u << (level + 1)) - 2u );
        }
    }
    for( cap = -1; cap <= 8; cap++ ) {
        int expected = cap < 2 ? 0 : cap > 6 ? 5 : cap - 1;
        CHECK( NITMOD_EvaluateSkill(&thresholds, 0, 1000, cap, 0, &result) );
        CHECK( result.level == expected && result.unlocked == (1u << (expected + 1)) - 2u );
    }
    CHECK( NITMOD_EvaluateSkill(&thresholds, 0, 1000, 6, 1, &result) );
    CHECK( !result.level && !result.unlocked );
    CHECK( NITMOD_EvaluateSkill(&thresholds, 0, -1, 6, 0, &result) );
    CHECK( !result.level && !result.unlocked );
    thresholds.threshold[0][1] = -1;
    thresholds.threshold[0][2] = 300;
    thresholds.threshold[0][3] = 0;
    thresholds.threshold[0][4] = -1;
    CHECK( NITMOD_EvaluateSkill(&thresholds, 0, 200, 6, 0, &result) );
    CHECK( result.level == 5 && result.unlocked == ((1u << 3) | (1u << 5)) );
    CHECK( !NITMOD_EvaluateSkill(&thresholds, -1, 0, 6, 0, &result) );
    CHECK( !NITMOD_EvaluateSkill(&thresholds, 7, 0, 6, 0, &result) );
    CHECK( !NITMOD_EvaluateSkill(NULL, 0, 0, 6, 0, &result) );
    CHECK( result.level == 5 && result.unlocked == 40u );
    CHECK( !NITMOD_EvaluateSkill(&thresholds, 0, 0, 6, 0, NULL) );
    return 0;
}
