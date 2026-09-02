#include <stdio.h>
#include <string.h>
#include "nitmod_skills.h"
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)
int main( void ) {
    int result[7], before[7];
    char text[9] = "0123401";
    const char *invalid = "56789x- ";
    int i, j;
    CHECK( NITMOD_ParseSkillDigits(text, 4, result) );
    for( i = 0; i < 7; i++ ) CHECK( result[i] == text[i] - '0' );
    memcpy(before, result, sizeof(result));
    for( i = 0; i < 7; i++ ) {
        char saved = text[i];
        for( j = 0; invalid[j]; j++ ) {
            text[i] = invalid[j];
            CHECK( !NITMOD_ParseSkillDigits(text, 4, result) );
            CHECK( !memcmp(before, result, sizeof(result)) );
        }
        text[i] = '\0';
        CHECK( !NITMOD_ParseSkillDigits(text, 4, result) );
        CHECK( !memcmp(before, result, sizeof(result)) );
        text[i] = saved;
    }
    CHECK( !NITMOD_ParseSkillDigits("01234010", 4, result) );
    CHECK( !NITMOD_ParseSkillDigits(NULL, 4, result) );
    CHECK( !NITMOD_ParseSkillDigits(text, -1, result) );
    CHECK( !NITMOD_ParseSkillDigits(text, 10, result) );
    CHECK( !NITMOD_ParseSkillDigits(text, 4, NULL) );
    CHECK( !memcmp(before, result, sizeof(result)) );
    CHECK( NITMOD_ParseSkillDigits("0000000", 0, result) );
    CHECK( NITMOD_ParseSkillDigits("5555555", 5, result) );
    for( i = 0; i < 7; i++ ) CHECK( result[i] == 5 );
    CHECK( !NITMOD_ParseSkillDigits("5555555", 4, result) );
    return 0;
}
