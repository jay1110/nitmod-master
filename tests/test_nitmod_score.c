#include <float.h>
#include <limits.h>
#include "g_local.h"
#include "nitmod_score.h"

static gclient_t client, before;
#define CHECK(test) do { if( !(test) ) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #test); return 1; } } while(0)

int main( void ) {
    static const float samples[] = { -10.75f, -1.5f, -0.75f, 0, 0.75f, 1.5f, 10.75f };
    int code, rest, skill, expected, actual, count = 1;
    static const unsigned int nonfinite[] = { 0x7fc00000u, 0x7f800000u, 0xff800000u };
    float points[7];
    for( skill = 0; skill < 7; skill++ ) count *= 7;
    /* Full cross product: in this range ET float and original x87 sums
     * are exact; compare both the helper and actual typed engine adapter. */
    for( code = 0; code < count; code++ ) {
        rest = code;
        expected = 0;
        for( skill = 0; skill < 7; skill++ ) {
            points[skill] = samples[rest % 7];
            rest /= 7;
            expected += points[skill];
        }
        CHECK( NITMOD_CalculateScore(points, &actual) && actual == expected );
        memcpy(client.sess.skillpoints, points, sizeof(points));
        client.ps.persistant[PERS_SCORE] = 999;
        before = client;
        before.ps.persistant[PERS_SCORE] = expected;
        G_SetPlayerScore(&client);
        CHECK( !memcmp(&client, &before, sizeof(client)) );
    }
    memset(points, 0, sizeof(points));
    points[0] = 16777216.0f;
    points[1] = 1.0f;
    points[2] = 1.0f;
    CHECK( NITMOD_CalculateScore(points, &actual) && actual == 16777218 );
    points[0] = -2147483648.0f;
    points[1] = points[2] = 0;
    CHECK( NITMOD_CalculateScore(points, &actual) && actual == INT_MIN );
    points[0] = 2147483520.0f;
    points[1] = 127;
    CHECK( NITMOD_CalculateScore(points, &actual) && actual == INT_MAX );
    points[1] = 128;
    CHECK( !NITMOD_CalculateScore(points, &actual) && actual == INT_MAX );
    points[0] = FLT_MAX;
    points[1] = -FLT_MAX; /* Later cancellation must not hide an invalid step. */
    CHECK( !NITMOD_CalculateScore(points, &actual) && actual == INT_MAX );
    memcpy(client.sess.skillpoints, points, sizeof(points));
    before = client;
    G_SetPlayerScore(&client);
    CHECK( !memcmp(&client, &before, sizeof(client)) );
    CHECK( sizeof(float) == sizeof(unsigned int) );
    for( code = 0; code < 3; code++ ) {
        memset(points, 0, sizeof(points));
        memcpy(&points[6], &nonfinite[code], sizeof(float));
        CHECK( !NITMOD_CalculateScore(points, &actual) && actual == INT_MAX );
        memcpy(client.sess.skillpoints, points, sizeof(points));
        before = client;
        G_SetPlayerScore(&client);
        CHECK( !memcmp(&client, &before, sizeof(client)) );
    }
    CHECK( !NITMOD_CalculateScore(NULL, &actual) && actual == INT_MAX );
    CHECK( !NITMOD_CalculateScore(points, NULL) );
    G_SetPlayerScore(NULL);
    return 0;
}
