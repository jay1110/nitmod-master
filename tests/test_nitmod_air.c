#include <limits.h>
#include <stdio.h>
#include "nitmod_air.h"
#include "nitmod_skills.h"
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
int main( void ) {
    nitmodAirState_t air;
    nitmodSkillThresholds_t thresholds;
    nitmodSkillProgress_t progress;
    int i;
    CHECK( NITMOD_AirDeadline(100, 0) == 12100 );
    CHECK( NITMOD_AirDeadline(100, 32) == 15100 );
    CHECK( NITMOD_AirDeadline(INT_MIN, 0) == INT_MIN + 12000 );
    CHECK( NITMOD_AirDeadline(INT_MAX, 32) == INT_MAX );
    CHECK( NITMOD_ShiftAirDeadline(12000, 500) == 12500 );
    CHECK( NITMOD_AirRemaining(12500, 500) == 12000 );
    CHECK( NITMOD_ShiftAirDeadline(100, -200) == -100 );
    CHECK( NITMOD_ShiftAirDeadline(INT_MIN, -1) == INT_MIN );
    CHECK( NITMOD_ShiftAirDeadline(INT_MAX, 1) == INT_MAX );
    CHECK( NITMOD_AirRemaining(100, 101) == -1 );
    CHECK( NITMOD_AirRemaining(100, 100) == 0 );
    CHECK( NITMOD_AirRemaining(INT_MAX, INT_MIN) == INT_MAX );
    CHECK( NITMOD_AirRemaining(INT_MIN, INT_MAX) == INT_MIN );
    for( i = 0; i < 64; i++ ) CHECK( NITMOD_BreathDuration(i) == (i & 32 ? 15000 : 12000) );
    NITMOD_DefaultSkillThresholds(&thresholds);
    CHECK( NITMOD_EvaluateSkill(&thresholds, 0, 200, 6, 0, &progress) );
    air.deadline = 0; air.drowningDamage = 10;
    CHECK( !NITMOD_UpdateAir(&air, 100, 0, 0, 100, progress.unlocked) );
    CHECK( air.deadline == 15100 && air.drowningDamage == 2 );
    CHECK( !NITMOD_UpdateAir(&air, 15100, 3, 0, 100, 0) );
    CHECK( air.deadline == 15100 );
    CHECK( NITMOD_UpdateAir(&air, 15101, 3, 0, 100, 32) == 4 );
    CHECK( air.deadline == 16100 );
    for( i = 0; i < 10; i++ ) {
        int damage = NITMOD_UpdateAir(&air, air.deadline + 1, 3, 0, 100, 32);
        CHECK( damage >= 6 && damage <= 15 );
    }
    CHECK( air.drowningDamage == 15 );
    CHECK( !NITMOD_UpdateAir(&air, 30000, 2, 0, 100, 0) );
    CHECK( air.deadline == 42000 && air.drowningDamage == 2 );
    air.drowningDamage = 8;
    CHECK( !NITMOD_UpdateAir(&air, 40000, 3, 1, 100, 32) );
    CHECK( air.deadline == 55000 && air.drowningDamage == 8 );
    CHECK( !NITMOD_UpdateAir(&air, 55001, 3, 0, 0, 32) );
    CHECK( air.deadline == 56000 && air.drowningDamage == 8 );
    air.deadline = 0;
    CHECK( NITMOD_UpdateAir(&air, 10000, 3, 0, 100, 0) == 10 );
    CHECK( air.deadline == 1000 );
    CHECK( !NITMOD_UpdateAir(&air, 100, 4, 0, 100, 0) );
    CHECK( air.deadline == 1000 && air.drowningDamage == 10 );
    CHECK( !NITMOD_UpdateAir(NULL, 0, 0, 0, 100, 0) );
    CHECK( !NITMOD_UpdateAir(&air, INT_MAX, 0, 0, 100, 32) );
    CHECK( air.deadline == INT_MAX );
    CHECK( NITMOD_EvaluateSkill(&thresholds, 0, 200, 5, 0, &progress) );
    CHECK( NITMOD_BreathDuration(progress.unlocked) == 12000 );
    return 0;
}
