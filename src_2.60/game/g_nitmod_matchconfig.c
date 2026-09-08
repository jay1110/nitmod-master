/* Original G_LoadConfig / G_ConfigParse, qagame ELF 0x788e0 / 0x78480. */
#include "g_local.h"
#include "g_nitmod_matchconfig.h"
#include "g_nitmod_legacy_cvars.h"

#define MATCH_CONFIG_LOCKS 128

typedef struct { char name[256], value[256]; } matchConfigLock_t;
static struct {
    char name[256], version[256];
    matchConfigLock_t locks[MATCH_CONFIG_LOCKS];
    int count;
    qboolean loaded;
} matchConfig;
static matchConfigLock_t serverLocks[MATCH_CONFIG_LOCKS];
static int serverLockCount;

static qboolean MatchConfigError(int handle, const char *message) {
    char filename[128] = "";
    int line = 0;
    trap_PC_SourceFileAndLine(handle, filename, &line);
    G_Printf(S_COLOR_RED "ERROR: %s, line %d: %s\n", filename, line, message);
    return qfalse;
}

static void MatchConfigPublish(void) {
    char info[MAX_INFO_STRING];
    trap_GetConfigstring(CS_NITMOD_INFO, info, sizeof(info));
    /* W belongs to the weapon-script loader; Original G_UpdateInfo uses X. */
    Info_SetValueForKey(info, "X", matchConfig.name);
    trap_SetConfigstring(CS_NITMOD_INFO, info);
}

static qboolean MatchConfigBlock(int handle) {
    pc_token_t token;
    char name[256], value[256], negative[256];
    if(!trap_PC_ReadToken(handle, &token) || strcmp(token.string, "{"))
        return MatchConfigError(handle, "expected '{'");
    while(trap_PC_ReadToken(handle, &token)) {
        if(token.string[0] == '}') return qtrue;
        if(!strcmp(token.string, "set")) {
            if(!PC_String_ParseNoAlloc(handle, name, sizeof(name)))
                return MatchConfigError(handle, "expected cvar to set");
            if(!PC_String_ParseNoAlloc(handle, value, sizeof(value)))
                return MatchConfigError(handle, "expected cvar value");
            if(value[0] == '-') {
                /* Original 0x787b0 reads the suffix into the NAME buffer.
                 * Preserve this observable quirk; setl uses a separate buffer. */
                if(!PC_String_ParseNoAlloc(handle, name, sizeof(name)))
                    return MatchConfigError(handle, "expected value after '-'");
                Com_sprintf(value, sizeof(value), "-%s", name);
            }
            trap_Cvar_Set(name, value);
        } else if(!strcmp(token.string, "command")) {
            if(!PC_String_ParseNoAlloc(handle, name, sizeof(name)))
                return MatchConfigError(handle, "expected command to execute");
            trap_SendConsoleCommand(EXEC_APPEND, va("%s\n", name));
        } else if(!strcmp(token.string, "setl")) {
            matchConfigLock_t *entry;
            /* Original has no guard: cap writes to its smaller runtime table. */
            if(matchConfig.count >= MATCH_CONFIG_LOCKS || serverLockCount >= MATCH_CONFIG_LOCKS)
                return MatchConfigError(handle, "too many locked cvars");
            entry = &matchConfig.locks[matchConfig.count];
            if(!PC_String_ParseNoAlloc(handle, entry->name, sizeof(entry->name)))
                return MatchConfigError(handle, "expected name of cvar to set and lock");
            if(!PC_String_ParseNoAlloc(handle, entry->value, sizeof(entry->value)))
                return MatchConfigError(handle, "expected value of cvar to set and lock");
            if(entry->value[0] == '-') {
                if(!PC_String_ParseNoAlloc(handle, negative, sizeof(negative)))
                    return MatchConfigError(handle, "expected value after '-'");
                Com_sprintf(entry->value, sizeof(entry->value), "-%s", negative);
            }
            /* Original's saved index and runtime count are distinct. */
            serverLocks[matchConfig.count++] = *entry;
            ++serverLockCount;
        } else return MatchConfigError(handle, va("unknown token '%s'", token.string));
    }
    /* Original accepts EOF inside a block. */
    return qtrue;
}

qboolean G_NITMOD_LoadMatchConfig(const char *filename, qboolean reload) {
    char path[64], configured[MAX_CVAR_VALUE_STRING];
    pc_token_t token;
    int handle;
    qboolean ok = qtrue;
    if(!filename || !filename[0]) {
        G_NITMOD_LegacyCvarString("g_customConfig", configured, sizeof(configured), "");
        if(configured[0]) {
            Q_strncpyz(path, configured, sizeof(path));
            if(!matchConfig.loaded || reload) memset(&matchConfig, 0, sizeof(matchConfig));
        } else {
            Q_strncpyz(configured, g_mapConfigs.string, sizeof(configured));
            if(!configured[0]) return qfalse;
            Q_strncpyz(path, configured, sizeof(path));
            Q_strcat(path, sizeof(path), "/");
            Q_strcat(path, sizeof(path), level.rawmapname);
            Q_strcat(path, sizeof(path), ".config");
        }
    } else {
        Q_strncpyz(path, filename, sizeof(path));
        if(reload) memset(&matchConfig, 0, sizeof(matchConfig));
    }
    handle = trap_PC_LoadSource(path);
    if(!handle) {
        G_Printf("^3Warning: No config with filename '%s' found\n", path);
        return qfalse;
    }
    while(trap_PC_ReadToken(handle, &token)) {
        if(!strcmp(token.string, "configname")) {
            if(!PC_String_ParseNoAlloc(handle, matchConfig.name, sizeof(matchConfig.name))) {
                ok = MatchConfigError(handle, "expected config name"); break;
            }
        } else if(!strcmp(token.string, "version")) {
            if(!PC_String_ParseNoAlloc(handle, matchConfig.version, sizeof(matchConfig.version))) {
                ok = MatchConfigError(handle, "expected config version"); break;
            }
        } else if(!strcmp(token.string, "init") || !strcmp(token.string, "default") ||
                  !strcmp(token.string, level.rawmapname)) {
            char section[256];
            Q_strncpyz(section, token.string, sizeof(section));
            if(!MatchConfigBlock(handle)) {
                ok = MatchConfigError(handle, va("failed to load %s struct", section)); break;
            }
            if(!strcmp(section, "init") && matchConfig.name[0])
                trap_SendServerCommand(-1, va("cp \"'%s^7' config loaded\n\"", matchConfig.name));
        }
        /* Unrecognised outer tokens are ignored individually in the original. */
    }
    /* A failed block reports both errors, but closes the engine handle once. */
    trap_PC_FreeSource(handle);
    if(!ok) return qfalse;
    matchConfig.loaded = qtrue;
    MatchConfigPublish();
    return qtrue;
}

void G_NITMOD_InitMatchConfig(void) {
    /* G_InitGame preserves the saved config while clearing level's locks. */
    memset(serverLocks, 0, sizeof(serverLocks));
    serverLockCount = 0;
    MatchConfigPublish();
    G_NITMOD_LoadMatchConfig("", qfalse);
}

void G_NITMOD_EnforceMatchConfig(void) {
    int i;
    char value[128];
    for(i = 0; i < serverLockCount; ++i) {
        /* Original's sparse restart slots are empty; do not set an empty name. */
        if(!serverLocks[i].name[0]) continue;
        memset(value, 0, sizeof(value));
        trap_Cvar_VariableStringBuffer(serverLocks[i].name, value, sizeof(value));
        if(strcmp(value, serverLocks[i].value))
            trap_Cvar_Set(serverLocks[i].name, serverLocks[i].value);
    }
}

qboolean G_NITMOD_MatchConfigCommand(const char *command) {
    char path[64];
    if(!Q_stricmp(command, "reloadConfig")) {
        memset(&matchConfig, 0, sizeof(matchConfig));
        if(G_NITMOD_LoadMatchConfig("", qtrue))
            G_Printf("Reloaded config: %s\n", matchConfig.name);
        return qtrue;
    }
    if(Q_stricmp(command, "loadConfig")) return qfalse;
    if(trap_Argc() != 2) {
        G_Printf("usage: loadConfig <config name>\n");
        return qtrue;
    }
    trap_Argv(1, path, sizeof(path));
    memset(&matchConfig, 0, sizeof(matchConfig));
    if(G_NITMOD_LoadMatchConfig(path, qtrue)) {
        G_Printf("Loaded config: %s\n", matchConfig.name);
        trap_Cvar_Set("g_customConfig", path);
    }
    return qtrue;
}
