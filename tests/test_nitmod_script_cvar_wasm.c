/* Real G_ScriptAction_Cvar; engine cvars and entity lookup are test sinks. */
#include "g_local.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <setjmp.h>
qboolean G_ScriptAction_Cvar(gentity_t *ent, char *params);
qboolean G_ScriptAction_GlobalAccum(gentity_t *ent, char *params);
qboolean G_ScriptAction_Accum(gentity_t *ent, char *params);
qboolean G_ScriptAction_PrintAccum(gentity_t *ent, char *params);
qboolean G_ScriptAction_PrintGlobalAccum(gentity_t *ent, char *params);
level_locals_t level;
gentity_t g_entities[MAX_GENTITIES];
gentity_t *G_FindByTargetnameFast(gentity_t *from, const char *name, int hash) {
    assert(!from && !strcmp(name, "event_name") && hash == 123);
    return &g_entities[100];
}

static int value, writes, events, changeCaller;
static const char *expectedHashName = "event_name";
static gentity_t entities[2];
static g_script_event_t scriptEvent;
int trap_Cvar_VariableIntegerValue(const char *name) {
    assert(!strcmp(name, "test")); return value;
}
void trap_Cvar_Set(const char *name, const char *text) {
    assert(!strcmp(name, "test")); value = atoi(text); ++writes;
}
long BG_StringHashValue(const char *name) {
    assert(!strcmp(name, expectedHashName)); return 123;
}
gentity_t *G_NITMOD_FindByScriptNameHash(gentity_t *from, int hash) {
    assert(hash == 123);
    return !from ? &entities[0] : from == &entities[0] ? &entities[1] : NULL;
}
void G_Script_ScriptEvent(gentity_t *ent, char *event, char *params) {
    assert(!strcmp(event, "trigger") && !strcmp(params, "event_name"));
    assert(ent == &entities[events]); ++events;
    if(changeCaller && ent == &entities[0]) ++ent->scriptStatus.scriptId;
}
static jmp_buf errorJump;
static const char *expectedError;
void QDECL G_Error(const char *format, ...) {
    char text[256];
    va_list args;
    if(!expectedError) abort();
    va_start(args, format);
    Q_vsnprintf(text, sizeof(text), format, args);
    va_end(args);
    assert(!strcmp(text, expectedError));
    longjmp(errorJump, 1);
}
void QDECL G_Printf(const char *format, ...) {}
void QDECL Com_Error(int level, const char *format, ...) { abort(); }
void QDECL Com_Printf(const char *format, ...) {}
#undef vsnprintf
int Q_vsnprintf(char *out, int size, const char *format, va_list args) {
    return vsnprintf(out, size, format, args);
}
static qboolean run(const char *command) {
    char params[128];
    strcpy(params, command); writes = events = 0;
    return G_ScriptAction_Cvar(&entities[0], params);
}
static void expectError(qboolean (*action)(gentity_t *, char *),
                        const char *command, const char *message) {
    char params[128];
    strcpy(params, command);
    expectedError = message;
    if(!setjmp(errorJump)) {
        action(&entities[0], params);
        assert(!"expected script error");
    }
    expectedError = NULL;
}
static void testAccumCommands(qboolean (*action)(gentity_t *, char *), int *store) {
    static const struct { const char *command; int initial, result, aborts, waits; } cases[] = {
        {"set -7", 0, -7, 0, 0}, {"inc -3", 8, 5, 0, 0},
        {"random 1", 99, 0, 0, 0},
        {"bitset 32", 0, 1, 0, 0}, {"bitreset -1", -1, INT_MAX, 0, 0},
        {"abort_if_less_than 3", 2, 2, 1, 0}, {"abort_if_less_than 3", 3, 3, 0, 0},
        {"abort_if_greater_than 3", 4, 4, 1, 0}, {"abort_if_greater_than 3", 3, 3, 0, 0},
        {"abort_if_equal 3", 3, 3, 1, 0}, {"abort_if_equal 3", 2, 2, 0, 0},
        {"abort_if_not_equal 3", 2, 2, 1, 0}, {"abort_if_not_equals 3", 3, 3, 0, 0},
        {"abort_if_bitset 32", 1, 1, 1, 0}, {"abort_if_bitset 32", 2, 2, 0, 0},
        {"abort_if_not_bitset 32", 2, 2, 1, 0}, {"abort_if_not_bitset 32", 1, 1, 0, 0},
        {"wait_while_equal 3", 3, 3, 0, 1}, {"wait_while_equal 3", 2, 2, 0, 0}
    };
    int i;
    char command[128];
    for(i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        store[9] = cases[i].initial;
        entities[0].scriptStatus.scriptStackHead = 0;
        sprintf(command, "9 %s", cases[i].command);
        assert(action(&entities[0], command) == !cases[i].waits);
        assert(store[9] == cases[i].result);
        assert(entities[0].scriptStatus.scriptStackHead == (cases[i].aborts ? 7 : 0));
    }
    expectedHashName = "target_name";
    store[9] = 3;
    for(i = 0; i < 2; ++i) {
        strcpy(command, "9 trigger_if_equal 3 target_name event_name");
        events = 0; changeCaller = i;
        assert(action(&entities[0], command) == !i);
        assert(events == 2); /* Finish fanout before returning on caller change. */
    }
    expectedHashName = "event_name";
    changeCaller = 0;
}
int main(void) {
    expectError(G_ScriptAction_GlobalAccum, "", "G_Scripting: globalaccum without a buffer index\n");
    expectError(G_ScriptAction_GlobalAccum, "9", "G_Scripting: globalaccum without a command\n");
    expectError(G_ScriptAction_GlobalAccum, "10 set 1", "G_Scripting: globalaccum buffer is outside range (0 - 9)\n");
    expectError(G_ScriptAction_GlobalAccum, "-1 set 1", "G_Scripting: globalaccum buffer is outside range (0 - 9)\n");
    expectError(G_ScriptAction_GlobalAccum, "9 set", "Scripting: globalaccum set requires a parameter\n");
    expectError(G_ScriptAction_GlobalAccum, "9 bogus", "Scripting: globalaccum bogus requires a parameter\n");
    expectError(G_ScriptAction_GlobalAccum, "9 bogus 1", "Scripting: globalaccum 9 bogus 1: unknown command\n");
    expectError(G_ScriptAction_Accum, "10 set 1", "G_Scripting: accum buffer is outside range (0 - 9)\n");
    expectError(G_ScriptAction_Accum, "-1 set 1", "G_Scripting: accum buffer is outside range (0 - 9)\n");
    char printLast[] = "9";
    assert(G_ScriptAction_PrintAccum(&entities[0], printLast));
    assert(G_ScriptAction_PrintGlobalAccum(&entities[0], printLast));
    entities[0].scriptEvents = &scriptEvent;
    scriptEvent.stack.numItems = 7;
    testAccumCommands(G_ScriptAction_Accum, entities[0].scriptAccumBuffer);
    testAccumCommands(G_ScriptAction_GlobalAccum, level.globalAccumBuffer);
    entities[0].scriptStatus.scriptStackHead = 0;
    value = 0; assert(run("test set 17") && value == 17 && writes == 1);
    assert(run("test inc 100") && value == 18 && writes == 1);
    assert(run("test bitset 32") && value == 19 && writes == 1);
    assert(run("test bitreset 0") && value == 18 && writes == 1);
    assert(run("test random 1") && value == 0 && writes == 1);
    assert(run("test abort_if_bitset 32") && writes == 0);
    assert(entities[0].scriptStatus.scriptStackHead == 0);
    assert(run("test abort_if_not_bitset 32") && writes == 0);
    assert(entities[0].scriptStatus.scriptStackHead == 7);
    assert(!run("test wait_while_equal 0") && writes == 0);
    assert(run("test trigger_if_equal 1 ignored event_name") && events == 0);
    assert(run("test trigger_if_equal 0 ignored event_name") && events == 2 && writes == 0);
    changeCaller = 1;
    assert(!run("test trigger_if_equal 0 ignored event_name") && events == 2 && writes == 0);
    value = INT_MAX;
    assert(run("test inc 99") && value == INT_MIN && writes == 1);
    {
        char set[] = "3 set 2147483647";
        char inc[] = "3 inc 1";
        char dec[] = "3 inc -1";
        char wait[] = "3 wait_while_equal 2147483647";
        level.globalAccumBuffer[2] = 99;
        assert(G_ScriptAction_GlobalAccum(&entities[0], set));
        assert(G_ScriptAction_GlobalAccum(&entities[0], inc));
        assert(level.globalAccumBuffer[3] == INT_MIN);
        assert(G_ScriptAction_GlobalAccum(&entities[0], dec));
        assert(level.globalAccumBuffer[3] == INT_MAX);
        assert(!G_ScriptAction_GlobalAccum(&entities[0], wait));
        assert(level.globalAccumBuffer[2] == 99);
        entities[0].scriptAccumBuffer[0] = 88;
        entities[0].scriptAccumBuffer[2] = 77;
        assert(G_ScriptAction_Accum(&entities[0], set));
        assert(G_ScriptAction_Accum(&entities[0], inc));
        assert(entities[0].scriptAccumBuffer[3] == INT_MIN);
        assert(G_ScriptAction_Accum(&entities[0], dec));
        assert(entities[0].scriptAccumBuffer[3] == INT_MAX);
        assert(entities[0].scriptAccumBuffer[0] == 88);
        assert(entities[0].scriptAccumBuffer[2] == 77);
    }
    puts("WASM script cvar: production write/compare/trigger paths passed");
    {
        char high[] = "9 set 42";
        assert(sizeof(level.globalAccumBuffer) / sizeof(int) == 10);
        assert(G_ScriptAction_GlobalAccum(&entities[0], high));
        assert(G_ScriptAction_Accum(&entities[0], high));
        assert(level.globalAccumBuffer[9] == 42 && entities[0].scriptAccumBuffer[9] == 42);
    }
    {
        char count[] = "3 set_to_dynamitecount event_name";
        level.num_entities = 101; g_entities[100].s.number = 100;
        g_entities[64].etpro_misc_1 = g_entities[65].etpro_misc_1 = 1;
        g_entities[64].nitmodDynamiteObjective = g_entities[65].nitmodDynamiteObjective = 100;
        g_entities[66].etpro_misc_1 = 1; g_entities[66].nitmodDynamiteObjective = 99;
        g_entities[63].etpro_misc_1 = 1; g_entities[63].nitmodDynamiteObjective = 100;
        entities[0].scriptStatus.scriptStackHead = 0;
        assert(G_ScriptAction_Accum(&entities[0], count));
        assert(entities[0].scriptAccumBuffer[3] == 2);
        assert(entities[0].scriptStatus.scriptStackHead == 7);
        g_entities[64].etpro_misc_1 = g_entities[65].etpro_misc_1 = 0;
        entities[0].scriptStatus.scriptStackHead = 0;
        assert(G_ScriptAction_Accum(&entities[0], count));
        assert(entities[0].scriptAccumBuffer[3] == 0);
        assert(entities[0].scriptStatus.scriptStackHead == 0);
        puts("WASM dynamite count: association, flag, scan bounds and abort behavior passed");
    }
    return 0;
}
