/* Execute the production static parser without exposing it in the module API. */
#include "../src_2.60/cgame/cg_servercmds.c"
#include <assert.h>
#include <stdio.h>
cg_t cg;
cgs_t cgs;
static int original, negotiated, argc;
static const char *args[18];
qboolean NITMOD_UsesOriginalProtocol(void) { return original; }
qboolean NITMOD_ServerSupports(unsigned int feature) {
    assert(feature == NITMOD_FEATURE_SCORE_KD); return negotiated;
}
int trap_Argc(void) { return argc; }
const char *CG_Argv(int index) { return index < argc ? args[index] : ""; }
static void packet(int first, const char *client) {
    int offset = first && !original ? 4 : 2;
    args[0] = first ? "sc0" : "sc1";
    if(offset == 4) { args[1] = "12"; args[2] = "34"; }
    args[offset - 1] = "1";
    args[offset] = client; args[offset + 1] = "99";
    args[offset + 2] = "50"; args[offset + 3] = "10";
    args[offset + 4] = "0"; args[offset + 5] = "3"; args[offset + 6] = "-1";
    argc = offset + 7;
}
int main(void) {
    int same, tests = 0;
    for(original = 0; original < 2; ++original)
    for(negotiated = 0; negotiated < 2; ++negotiated)
    for(same = 0; same < 2; ++same) {
        cg.numScores = 1; cg.scores[0].client = same ? 7 : 2;
        cg.scores[0].kills = 20; cg.scores[0].deaths = 4;
        packet(1, "7"); CG_ParseScore(TEAM_AXIS);
        assert(cg.numScores == 1 && cg.scores[0].client == 7);
        assert(cg.scores[0].kills == (same && (original || negotiated) ? 20 : 0));
        assert(cg.scores[0].deaths == (same && (original || negotiated) ? 4 : 0));
        assert(cg.scores[0].nitmodFlags == (original ? 3 : 0));
        assert(cgs.clientinfo[7].score == 99);
        if(!original) assert(cg.teamScores[0] == 12 && cg.teamScores[1] == 34);
        packet(0, "9"); CG_ParseScore(TEAM_ALLIES);
        assert(cg.numScores == 2 && cg.scores[1].client == 9);
        /* Invalid last field must not partially change scores or team totals. */
        packet(1, "2"); args[argc - 1] = "bad";
        if(!original) args[1] = "999";
        CG_ParseScore(TEAM_AXIS);
        assert(cg.numScores == 2 && cg.scores[0].client == 7);
        if(!original) assert(cg.teamScores[0] == 12);
        packet(0, "64"); CG_ParseScore(TEAM_ALLIES); assert(cg.numScores == 2);
        packet(0, "9"); --argc; CG_ParseScore(TEAM_ALLIES); assert(cg.numScores == 2);
        ++tests;
    }
    puts("WASM score receiver: layout/capability/reassignment matrix and atomic rejection passed");
    return tests == 8 ? 0 : 1;
}
