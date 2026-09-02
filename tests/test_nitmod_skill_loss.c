#include <float.h>
#include <stdio.h>
#include <string.h>
#include "nitmod_skills.h"
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
int main( void ) {
    nitmodSkillThresholds_t thresholds;
    nitmodSkillLoss_t result, before;
    int skill, level;
    NITMOD_DefaultSkillThresholds(&thresholds);
    memset(&result, 0, sizeof(result));
    for( skill = 0; skill < 7; skill++ ) for( level = 1; level < 6; level++ ) {
        float points = (float)thresholds.threshold[skill][level];
        CHECK( NITMOD_CalculateSkillLoss(&thresholds, skill, points, 0, 6, 0, &result) );
        CHECK( result.points == points && result.removed == 0 && result.progress.level == level );
        CHECK( NITMOD_CalculateSkillLoss(&thresholds, skill, points, 0.5f, 6, 0, &result) );
        CHECK( result.points == points - 0.5f && result.removed == 0.5f );
        CHECK( result.progress.level == level - 1 && result.progress.unlocked == (1u << level) - 2u );
    }
    CHECK( NITMOD_CalculateSkillLoss(&thresholds, 0, 20, 30, 6, 0, &result) );
    CHECK( result.points == -10 && result.removed == 30 && !result.progress.level );
    CHECK( NITMOD_CalculateSkillLoss(&thresholds, 0, 10, -190, 6, 0, &result) );
    CHECK( result.points == 200 && result.removed == -190 && result.progress.level == 5 );
    CHECK( NITMOD_CalculateSkillLoss(&thresholds, 0, 250, 1, 3, 0, &result) );
    CHECK( result.progress.level == 2 && result.progress.unlocked == 6 );
    CHECK( NITMOD_CalculateSkillLoss(&thresholds, 0, 250, 1, 6, 1, &result) );
    CHECK( result.points == 249 && !result.progress.level && !result.progress.unlocked );
    thresholds.threshold[0][4] = -1;
    CHECK( NITMOD_CalculateSkillLoss(&thresholds, 0, 200, 1, 6, 0, &result) );
    CHECK( result.progress.level == 3 && result.progress.unlocked == 14 );
    /* Team accounting uses actual rounded subtraction, not requested loss. */
    CHECK( NITMOD_CalculateSkillLoss(&thresholds, 0, FLT_MAX, 1, 6, 0, &result) );
    CHECK( result.points == FLT_MAX && result.removed == 0 );
    before = result;
    CHECK( !NITMOD_CalculateSkillLoss(&thresholds, 0, FLT_MAX, -FLT_MAX, 6, 0, &result) );
    CHECK( !NITMOD_CalculateSkillLoss(&thresholds, 7, 10, 1, 6, 0, &result) );
    CHECK( !NITMOD_CalculateSkillLoss(NULL, 0, 10, 1, 6, 0, &result) );
    CHECK( !memcmp(&before, &result, sizeof(result)) );
    CHECK( !NITMOD_CalculateSkillLoss(&thresholds, 0, 10, 1, 6, 0, NULL) );
    return 0;
}
