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
int main( void ) {
    nitmodSkillThresholds_t state, before;
    char rows[7][64];
    const char *bad[] = { NULL, "", "1 2 3 4", "1 2 3 4 5 6", "1 2 bad 4 5",
        "1 2 3 4 999999999999999999999", "1 2 3 4 5junk" };
    int i, j;
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
