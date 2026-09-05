#include <limits.h>
#include <stdio.h>
#include "nitmod_skills.h"
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    /* Independent total-to-rank oracle, including both sides of every step. */
    static const int expected[36] = {
        0,1,2,3,4,5,5,6,6,7,7,8,8,8,9,9,9,
        10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
    };
    int levels[7], code, rest, skill, total, rank, count = 1;
    {
        const char *invalid[] = {"", "-1", "11", "2147483648", "abc", "1x", NULL};
        char text[16]; int i;
        for(i = 0; i < 11; ++i) {
            sprintf(text, "%d", i); rank = 99;
            CHECK(NITMOD_ParseRank(text, &rank) && rank == i);
        }
        for(i = 0; i < sizeof(invalid)/sizeof(invalid[0]); ++i) {
            rank = 99; CHECK(!NITMOD_ParseRank(invalid[i], &rank) && rank == 99);
        }
        CHECK(!NITMOD_ParseRank("1", NULL));
    }
    for( skill = 0; skill < 7; skill++ ) count *= 6;
    for( code = 0; code < count; code++ ) {
        rest = code;
        total = 0;
        for( skill = 0; skill < 7; skill++ ) {
            levels[skill] = rest % 6;
            rest /= 6;
            total += levels[skill];
        }
        CHECK( NITMOD_CalculateRank(levels, &rank) );
        CHECK( rank == expected[total] );
    }
    for( skill = 0; skill < 7; skill++ ) {
        rank = 123;
        levels[skill] = -1;
        CHECK( !NITMOD_CalculateRank(levels, &rank) && rank == 123 );
        levels[skill] = 6;
        CHECK( !NITMOD_CalculateRank(levels, &rank) && rank == 123 );
        levels[skill] = INT_MAX;
        CHECK( !NITMOD_CalculateRank(levels, &rank) && rank == 123 );
        levels[skill] = 0;
    }
    CHECK( !NITMOD_CalculateRank(NULL, &rank) && rank == 123 );
    CHECK( !NITMOD_CalculateRank(levels, NULL) );
    /* Emit one result per possible total for the original-ELF table check. */
    for( total = 0; total <= 35; total++ ) {
        rest = total;
        for( skill = 0; skill < 7; skill++ ) {
            levels[skill] = rest > 5 ? 5 : rest;
            rest -= levels[skill];
        }
        CHECK( NITMOD_CalculateRank(levels, &rank) );
        printf("%d\n", rank);
    }
    return 0;
}
