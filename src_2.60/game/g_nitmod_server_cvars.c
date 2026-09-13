#include "g_local.h"
#include "nitmod_support_time.h"
#include "g_nitmod_server_cvars.h"

/* Original ConsoleCommand 0xd4500 / G_UpdateSvCvars 0xd4170.
 * These are client-side restrictions, separate from NxAC's query/kick scan. */
#define MAX_SVCVARS 128
#define MAX_FORCECVARS 64

typedef struct {
    char name[256];
    int mode;
    char first[256], second[256];
} serverCvarRule_t;
typedef struct { char name[256], value[256]; } forcedCvar_t;
static serverCvarRule_t serverCvars[MAX_SVCVARS];
static forcedCvar_t forcedCvars[MAX_FORCECVARS];
static int serverCvarCount, forcedCvarCount;

static void PublishServerCvars(void) {
    char info[MAX_INFO_STRING];
    int i;
    info[0] = 0;
    for(i = 0; i < serverCvarCount; ++i) {
        serverCvarRule_t *rule = &serverCvars[i];
        Info_SetValueForKey(info, va("C%i", i),
            va("%i %s %s %s", rule->mode, rule->name, rule->first, rule->second));
    }
    Info_SetValueForKey(info, "N", va("%i", serverCvarCount));
    /* Original CS38 is native ET's charge-times slot. Use its reserved
     * native equivalent without shifting any existing configstring ranges. */
    trap_SetConfigstring(CS_NITMOD_SVCVARS, info);
}

void G_NITMOD_ResetServerCvars(void) {
    memset(serverCvars, 0, sizeof(serverCvars));
    memset(forcedCvars, 0, sizeof(forcedCvars));
    serverCvarCount = forcedCvarCount = 0;
    PublishServerCvars();
}

void G_NITMOD_SendForcedCvars(int clientNum) {
    int i;
    for(i = 0; i < forcedCvarCount; ++i)
        trap_SendServerCommand(clientNum, va("fc \"%s\" \"%s\"",
            forcedCvars[i].name, forcedCvars[i].value));
}

static int ServerCvarMode(const char *name) {
    static const char *const modes[9][2] = {
        {"EQ", "EQUAL"}, {"G", "GREATER"}, {"GE", "GREATEREQUAL"},
        {"L", "LOWER"}, {"LE", "LOWEREQUAL"}, {"IN", "INSIDE"},
        {"OUT", "OUTSIDE"}, {"INC", "INCLUDE"}, {"EXC", "EXCLUDE"}
    };
    int i;
    for(i = 0; i < 9; ++i)
        if(!Q_stricmp(name, modes[i][0]) || !Q_stricmp(name, modes[i][1])) return i;
    return -1;
}

qboolean G_NITMOD_ServerCvarCommand(const char *command) {
    int argc, index, mode;
    char name[256], first[256], second[256], modeName[16];
    if(!Q_stricmp(command, "sv_cvarempty")) {
        G_NITMOD_ResetServerCvars();
        return qtrue;
    }
    if(!Q_stricmp(command, "forcecvar")) {
        if(trap_Argc() != 3) {
            G_Printf("usage: forcecvar CVAR VALUE\n");
            return qtrue;
        }
        if(forcedCvarCount >= MAX_FORCECVARS) {
            G_Printf("forcecvar: MAX_FORCECVARS hit\n");
            return qtrue;
        }
        trap_Argv(1, name, sizeof(name));
        trap_Argv(2, first, sizeof(first));
        Q_strncpyz(forcedCvars[forcedCvarCount].name, name, sizeof(name));
        Q_strncpyz(forcedCvars[forcedCvarCount].value, first, sizeof(first));
        ++forcedCvarCount;
        /* Initial settings reach humans on ClientBegin. Later commands also
         * update connected clients, matching the original 600 ms boundary. */
        /* Original 0xd539e..0xd53af subtracts in signed 32-bit time. */
        if(NITMOD_SupportSignedTime((uint32_t)level.time - (uint32_t)level.startTime) > 600)
            trap_SendServerCommand(-1, va("fc \"%s\" \"%s\"", name, first));
        return qtrue;
    }
    if(Q_stricmp(command, "sv_cvar")) return qfalse;
    argc = trap_Argc();
    if(argc < 4) {
        G_Printf("usage: sv_cvar <cvar name> <mode> <value1> <value2>\n");
        return qtrue;
    }
    trap_Argv(1, name, sizeof(name));
    trap_Argv(2, modeName, sizeof(modeName));
    trap_Argv(3, first, sizeof(first));
    second[0] = 0;
    if(argc == 5) trap_Argv(4, second, sizeof(second));
    for(index = 0; index < serverCvarCount; ++index)
        if(!Q_stricmp(serverCvars[index].name, name)) break;
    if(index >= MAX_SVCVARS) {
        G_Printf("sv_cvar: MAX_SVCVARS hit\n");
        return qtrue;
    }
    mode = ServerCvarMode(modeName);
    if(mode < 0) {
        G_Printf("sv_cvar: invalid mode\n");
        return qtrue;
    }
    Q_strncpyz(serverCvars[index].name, name, sizeof(name));
    Q_strncpyz(serverCvars[index].first, first, sizeof(first));
    Q_strncpyz(serverCvars[index].second, second, sizeof(second));
    serverCvars[index].mode = mode;
    if(index == serverCvarCount) ++serverCvarCount;
    PublishServerCvars();
    return qtrue;
}
