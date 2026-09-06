#include "cg_local.h"
#include "cg_nitmod_config.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
cg_t cg;
cgs_t cgs;
static const char *args[8];
static int argc;
int trap_Argc(void) { return argc; }
const char *CG_Argv(int n) { assert(n >= 0 && n < argc); return args[n]; }
void QDECL Com_Error(int level, const char *format, ...) { abort(); }
int main(void) {
    cg.numScores = 3;
    cg.scores[0].client = 7; cg.scores[1].client = 2; cg.scores[2].client = 9;
    args[0] = "kd0"; args[1] = "2"; args[2] = "ignored";
    args[3] = "20"; args[4] = "4"; args[5] = "also ignored";
    args[6] = "30"; args[7] = "5"; argc = 8;
    assert(NITMOD_KDCommand(args[0]));
    assert(cg.scores[0].kills == 20 && cgs.clientinfo[7].deaths == 4);
    assert(cg.scores[1].kills == 30 && cgs.clientinfo[2].deaths == 5);
    args[0] = "kd1"; args[1] = "1"; args[2] = "9";
    args[3] = "40"; args[4] = "invalid"; argc = 5;
    assert(NITMOD_KDCommand(args[0])); assert(cg.scores[2].kills == 0);
    args[4] = "6";
    assert(NITMOD_KDCommand(args[0])); assert(cg.scores[2].kills == 40 && cgs.clientinfo[9].deaths == 6);
    args[3] = "99"; assert(NITMOD_KDCommand(args[0])); assert(cg.scores[2].kills == 40);
    args[0] = "kd0"; args[1] = "2147483647";
    assert(NITMOD_KDCommand(args[0])); assert(cg.scores[0].kills == 20);
    assert(!NITMOD_KDCommand(NULL) && !NITMOD_KDCommand("unknown"));
    puts("WASM KD receiver: positional mapping, append, atomic rejection and bounds passed");
    return 0;
}
