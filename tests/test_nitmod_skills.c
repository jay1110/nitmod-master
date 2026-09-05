#include <stdio.h>
#include <string.h>
#include "nitmod_skills.h"
static const char *values[7];
static const char *Read( void *context, const char *key ) {
    const char *keys = "BEMFLSC";
    const char *found = strchr(keys, *key);
    static char buffer[256];
    const char *value;
    (void)context;
    if( !found || key[1] ) return NULL;
    value = values[found - keys];
    if( !value ) return NULL;
    strcpy(buffer, value);
    return buffer;
}
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
static int CheckGameplayTables( void ) {
    static const float base[] = {
        .75f, .5f, 1, 1, 1, .25f, .25f, 1, 1, .5f,
        1, .5f, 1, 1, 3, 5, 3, 3, 7, 12
    };
    static const float changed[] = {
        .75f, .33f, .66f, .66f, 1, .15f, .15f, .66f, .66f, .5f,
        .66f, .33f, .66f, .66f, 3, 9, 6, 6, 14, 24
    };
    static const unsigned int changeBit[] = {
        0, 2, 2, 4, 0, 2, 2, 4, 4, 0, 8, 8, 4, 8, 0, 8, 4, 4, 4, 4
    };
    const float synthetic[6] = { 1, 2, 2, 3, 3, 4 };
    unsigned int mask;
    int table;
    float value = -123;
    CHECK( sizeof(base) / sizeof(base[0]) == NITMOD_TABLE_COUNT );
    for( table = 0; table < NITMOD_TABLE_COUNT; table++ ) {
        for( mask = 0; mask < 64; mask++ ) {
            float expected = mask & changeBit[table] ? changed[table] : base[table];
            CHECK( NITMOD_GameplayTableValue((nitmodSkillTable_t)table, mask, &value) );
            CHECK( value == expected );
            CHECK( NITMOD_GameplayTableValue((nitmodSkillTable_t)table,
                mask | ~63u, &value) && value == expected );
        }
    }
    for( mask = 0; mask < 64; mask++ ) {
        float expected = mask & 32 ? 4.0f : (mask & 8 ? 3.0f : (mask & 2 ? 2.0f : 1.0f));
        CHECK( NITMOD_SelectSkillTable(synthetic, mask, &value) && value == expected );
    }
    value = -123;
    CHECK( !NITMOD_GameplayTableValue((nitmodSkillTable_t)-1, 62, &value) );
    CHECK( !NITMOD_GameplayTableValue(NITMOD_TABLE_COUNT, 62, &value) );
    CHECK( !NITMOD_SelectSkillTable(NULL, 62, &value) && value == -123 );
    CHECK( !NITMOD_SelectSkillTable(synthetic, 62, NULL) );
    {
        static const unsigned int invalid[] = { 0x7f800000u, 0xff800000u, 0x7fc00000u };
        float row[6];
        int bad, position;
        CHECK( sizeof(float) == sizeof(unsigned int) );
        for( bad = 0; bad < 3; bad++ ) for( position = 0; position < 6; position++ ) {
            memcpy(row, synthetic, sizeof(row));
            memcpy(&row[position], &invalid[bad], sizeof(float));
            CHECK( !NITMOD_SelectSkillTable(row, 0, &value) && value == -123 );
            CHECK( !NITMOD_SelectSkillTable(row, 62, &value) && value == -123 );
        }
    }
    return 0;
}
int main( void ) {
    nitmodSkillThresholds_t state, before;
    char rows[7][64];
    const char *bad[] = { NULL, "", "1 2 3 4", "1 2 3 4 5 6", "1 2 bad 4 5",
        "1 2 3 4 999999999999999999999", "1 2 3 4 5junk" };
    int i, j;
    CHECK( !CheckGameplayTables() );
    NITMOD_DefaultSkillThresholds(&state);
    for( i = 0; i < 7; i++ ) {
        CHECK( state.threshold[i][0] == 0 && state.threshold[i][1] == 20 );
        CHECK( state.threshold[i][2] == 50 && state.threshold[i][3] == 90 );
        CHECK( state.threshold[i][4] == 140 && state.threshold[i][5] == 200 );
        sprintf(rows[i], "%d %d,%d, %d %d", i+1, i+2, i+3, i+4, i+5);
        values[i] = rows[i];
    }
    CHECK( NITMOD_ParseSkillThresholds(Read, NULL, &state) );
    for( i = 0; i < 7; i++ ) for( j = 1; j < 6; j++ ) CHECK( state.threshold[i][j] == i+j );
    before = state;
    for( i = 0; i < 7; i++ ) {
        for( j = 0; j < sizeof(bad)/sizeof(bad[0]); j++ ) {
            values[i] = bad[j];
            CHECK( !NITMOD_ParseSkillThresholds(Read, NULL, &state) );
            CHECK( !memcmp(&state, &before, sizeof(state)) );
        }
        values[i] = rows[i];
    }
    values[0] = "-1 0 1 2 3";
    CHECK( NITMOD_ParseSkillThresholds(Read, NULL, &state) && state.threshold[0][1] == -1 );
    CHECK( !NITMOD_ParseSkillThresholds(NULL, NULL, &state) );
    CHECK( !NITMOD_ParseSkillThresholds(Read, NULL, NULL) );
    return 0;
}
