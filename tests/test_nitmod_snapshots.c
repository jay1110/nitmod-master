#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "nitmod_protocol.h"
#include "nitmod_snapshots.h"

#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

static const char *fields[21] = { "ct", "11", "22", "33", "44", "55", "66", "77", "88", "99", "110" };
/* Mimic CG_Argv's reusable buffer; decoders must consume each value before
 * requesting the next argument. */
static const char *Argument( int index ) {
    static char buffer[128];
    strcpy( buffer, fields[index] );
    return buffer;
}

static int SettingsTests( void ) {
    nitmodSimpleConfig_t simple, oldSimple;
    nitmodGameState_t state, oldState;
    nitmodObjectiveEvent_t objective, oldObjective;
    char numbers[21][16];
    const char *saved;
    const char *invalidFloats[] = { "", "-", ".", "1e", "1e+", "nan", "inf",
        "0x1p2", " 1", "1 ", "1,5", "1junk", "1e999", "-1e999", "1e-999", "1e100", "1e-100" };
    float value;
    int i;
    memset( &simple, 0, sizeof(simple) );
    memset( &state, 0, sizeof(state) );
    memset( &objective, 0, sizeof(objective) );
    for( i = 0; i <= 20; i++ ) {
        sprintf( numbers[i], "%d", i );
        fields[i] = numbers[i];
    }
    CHECK( NITMOD_ParseSimpleConfigSnapshot( 12, Argument, &simple ) );
    CHECK( simple.doubleJump == 1 );
    CHECK( simple.missileCams == 2 );
    CHECK( simple.war == 3 );
    CHECK( simple.noReload == 4 );
    CHECK( simple.filterCams == 5 );
    CHECK( simple.spectatorNames == 6 );
    CHECK( simple.misc == 7 );
    CHECK( simple.proneDelay == 8 );
    CHECK( simple.dynamiteTimer == 9 );
    CHECK( simple.crouchStandDelay == 10 );
    CHECK( simple.standCrouchDelay == 11 );
    oldSimple = simple;
    for( i = 1; i <= 11; i++ ) {
        saved = fields[i]; fields[i] = "999999999999999999999999999999999999999999999999999";
        CHECK( !NITMOD_ParseSimpleConfigSnapshot( 12, Argument, &simple ) );
        CHECK( !memcmp( &simple, &oldSimple, sizeof(simple) ) );
        fields[i] = saved;
    }
    CHECK( !NITMOD_ParseSimpleConfigSnapshot( 11, Argument, &simple ) );
    CHECK( !NITMOD_ParseSimpleConfigSnapshot( 13, Argument, &simple ) );
    CHECK( !NITMOD_ParseSimpleConfigSnapshot( 12, NULL, &simple ) );
    CHECK( !NITMOD_ParseSimpleConfigSnapshot( 12, Argument, NULL ) );
    fields[15] = "1.25";
    state.teamScoreAxis = -7; state.teamScoreAllies = 42;
    CHECK( NITMOD_ParseGameStateSnapshot( 21, Argument, &state ) );
    CHECK( state.teamScoreAxis == -7 && state.teamScoreAllies == 42 );
    CHECK( state.panzerRestriction == 1 );
    CHECK( state.maxPanzers == 2 );
    CHECK( state.maxMG42s == 3 );
    CHECK( state.maxFlamers == 4 );
    CHECK( state.maxMortars == 5 );
    CHECK( state.maxRifleGrenades == 6 );
    CHECK( state.adrenaline == 7 );
    CHECK( state.keepAwards == 8 );
    CHECK( state.maxSoldiers == 9 );
    CHECK( state.maxMedics == 10 );
    CHECK( state.maxEngineers == 11 );
    CHECK( state.maxFieldops == 12 );
    CHECK( state.maxCovertops == 13 );
    CHECK( state.weapons == 14 );
    CHECK( state.doubleJumpHeight == 1.25f );
    CHECK( state.tdmOptions == 16 );
    CHECK( state.dmOptions == 17 );
    CHECK( state.gravity == 18 );
    CHECK( state.mapCount == 19 );
    CHECK( state.resetXPMapCount == 20 );
    oldState = state;
    for( i = 1; i <= 20; i++ ) {
        saved = fields[i]; fields[i] = "999999999999999999999999999999999999999999999999999";
        CHECK( !NITMOD_ParseGameStateSnapshot( 21, Argument, &state ) );
        CHECK( !memcmp( &state, &oldState, sizeof(state) ) );
        fields[i] = saved;
    }
    CHECK( !NITMOD_ParseGameStateSnapshot( 20, Argument, &state ) );
    CHECK( !NITMOD_ParseGameStateSnapshot( 22, Argument, &state ) );
    CHECK( !NITMOD_ParseGameStateSnapshot( 21, NULL, &state ) );
    CHECK( !NITMOD_ParseGameStateSnapshot( 21, Argument, NULL ) );
    fields[2] = "-1";
    CHECK( NITMOD_ParseGameStateSnapshot( 21, Argument, &state ) && state.maxPanzers == -1 );
    fields[11] = "-1";
    CHECK( NITMOD_ParseSimpleConfigSnapshot( 12, Argument, &simple ) && simple.standCrouchDelay == -1 );
    fields[1] = "4"; fields[2] = "3"; fields[3] = "-1"; fields[4] = "63"; fields[5] = "7";
    CHECK( NITMOD_ParseObjectiveSnapshot( 6, Argument, 64, &objective ) );
    CHECK( objective.type == 4 && objective.detail == 3 && objective.objective == -1 );
    CHECK( objective.actor == 63 && objective.meansOfDeath == 7 );
    oldObjective = objective;
    for( i = 1; i <= 5; i++ ) {
        saved = fields[i]; fields[i] = "bad";
        CHECK( !NITMOD_ParseObjectiveSnapshot( 6, Argument, 64, &objective ) );
        CHECK( !memcmp( &objective, &oldObjective, sizeof(objective) ) );
        fields[i] = saved;
    }
    fields[4] = "-1";
    CHECK( !NITMOD_ParseObjectiveSnapshot( 6, Argument, 64, &objective ) );
    CHECK( !memcmp( &objective, &oldObjective, sizeof(objective) ) );
    fields[4] = "64";
    CHECK( !NITMOD_ParseObjectiveSnapshot( 6, Argument, 64, &objective ) );
    CHECK( !memcmp( &objective, &oldObjective, sizeof(objective) ) );
    fields[4] = "0";
    CHECK( NITMOD_ParseObjectiveSnapshot( 6, Argument, 64, &objective ) && objective.actor == 0 );
    CHECK( !NITMOD_ParseObjectiveSnapshot( 6, Argument, 0, &objective ) );
    CHECK( !NITMOD_ParseObjectiveSnapshot( 5, Argument, 64, &objective ) );
    CHECK( !NITMOD_ParseObjectiveSnapshot( 7, Argument, 64, &objective ) );
    CHECK( !NITMOD_ParseObjectiveSnapshot( 6, NULL, 64, &objective ) );
    CHECK( !NITMOD_ParseObjectiveSnapshot( 6, Argument, 64, NULL ) );
    value = 7.0f;
    for( i = 0; i < sizeof(invalidFloats)/sizeof(invalidFloats[0]); i++ ) {
        CHECK( !NITMOD_ParseProtocolFloat( invalidFloats[i], &value ) && value == 7.0f );
        fields[15] = invalidFloats[i];
        oldState = state;
        CHECK( !NITMOD_ParseGameStateSnapshot( 21, Argument, &state ) );
        CHECK( !memcmp( &state, &oldState, sizeof(state) ) );
    }
    CHECK( !NITMOD_ParseProtocolFloat( NULL, &value ) );
    CHECK( !NITMOD_ParseProtocolFloat( "1", NULL ) );
    CHECK( NITMOD_ParseProtocolFloat( "-1.25", &value ) && value == -1.25f );
    CHECK( NITMOD_ParseProtocolFloat( ".5", &value ) && value == 0.5f );
    CHECK( NITMOD_ParseProtocolFloat( "1.25e+2", &value ) && value == 125.0f );
    CHECK( NITMOD_ParseProtocolFloat( "-0", &value ) && value == 0.0f );
    return 0;
}

int main( void ) {
    nitmodChargeTimes_t charge, oldCharge;
    nitmodTeamScores_t score, oldScore;
    nitmodMapEndStats_t stats, oldStats;
    const char *saved;
    char number[64];
    int i, parsed;
    memset( &charge, 0, sizeof(charge) );
    memset( &score, 0, sizeof(score) );
    memset( &stats, 0, sizeof(stats) );
    CHECK( NITMOD_ParseChargeSnapshot( 11, Argument, &charge ) );
    CHECK( charge.soldier[0] == 11 && charge.soldier[1] == 22 );
    CHECK( charge.medic[0] == 33 && charge.medic[1] == 44 );
    CHECK( charge.engineer[0] == 55 && charge.engineer[1] == 66 );
    CHECK( charge.fieldops[0] == 77 && charge.fieldops[1] == 88 );
    CHECK( charge.covertops[0] == 99 && charge.covertops[1] == 110 );
    oldCharge = charge;
    for( i = 1; i <= 10; i++ ) {
        saved = fields[i]; fields[i] = "999999999999999999999";
        CHECK( !NITMOD_ParseChargeSnapshot( 11, Argument, &charge ) );
        CHECK( !memcmp( &charge, &oldCharge, sizeof(charge) ) );
        fields[i] = saved;
    }
    CHECK( !NITMOD_ParseChargeSnapshot( 10, Argument, &charge ) );
    CHECK( !NITMOD_ParseChargeSnapshot( 12, Argument, &charge ) );
    fields[1] = "-5"; fields[2] = "8";
    CHECK( NITMOD_ParseTeamScoreSnapshot( 3, Argument, &score ) );
    CHECK( score.axis == -5 && score.allies == 8 );
    oldScore = score;
    fields[1] = "100"; fields[2] = "8junk";
    CHECK( !NITMOD_ParseTeamScoreSnapshot( 3, Argument, &score ) );
    CHECK( !memcmp( &score, &oldScore, sizeof(score) ) );
    sprintf( number, "%u", UINT_MAX );
    fields[1] = number; fields[2] = "22"; fields[3] = "33"; fields[4] = "44"; fields[5] = "55";
    CHECK( NITMOD_ParseMapStatsSnapshot( 6, Argument, &stats ) );
    CHECK( stats.bodyshots == UINT_MAX && stats.headshots == 22 );
    CHECK( stats.kills == 33 && stats.deaths == 44 && stats.revives == 55 );
    oldStats = stats;
    for( i = 1; i <= 5; i++ ) {
        saved = fields[i]; fields[i] = "bad";
        CHECK( !NITMOD_ParseMapStatsSnapshot( 6, Argument, &stats ) );
        CHECK( !memcmp( &stats, &oldStats, sizeof(stats) ) );
        fields[i] = saved;
    }
    fields[5] = "-1";
    CHECK( !NITMOD_ParseMapStatsSnapshot( 6, Argument, &stats ) );
    CHECK( !memcmp( &stats, &oldStats, sizeof(stats) ) );
    CHECK( !NITMOD_ParseMapStatsSnapshot( 5, Argument, &stats ) );
    CHECK( !NITMOD_ParseTeamScoreSnapshot( 4, Argument, &score ) );
    CHECK( !NITMOD_ParseChargeSnapshot( 11, NULL, &charge ) );
    CHECK( !NITMOD_ParseTeamScoreSnapshot( 3, Argument, NULL ) );
    sprintf( number, "%d", INT_MIN );
    CHECK( NITMOD_ParseProtocolSigned( number, &parsed ) && parsed == INT_MIN );
    sprintf( number, "%d0", INT_MIN );
    CHECK( !NITMOD_ParseProtocolSigned( number, &parsed ) && parsed == INT_MIN );
    CHECK( !NITMOD_ParseProtocolSigned( "--1", &parsed ) );
    CHECK( !NITMOD_ParseProtocolSigned( "-", &parsed ) );
    CHECK( !NITMOD_ParseProtocolSigned( "+1", &parsed ) );
    CHECK( NITMOD_ParseProtocolSigned( "-0", &parsed ) && parsed == 0 );
    CHECK( !SettingsTests() );
    return 0;
}
