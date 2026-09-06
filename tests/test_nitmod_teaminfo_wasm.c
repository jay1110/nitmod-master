#include "g_local.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
level_locals_t level;
gentity_t g_entities[MAX_GENTITIES];
static gclient_t clients[3];
static int sends;
void TeamplayInfoMessage(team_t team);
void trap_SendServerCommand(int client, const char *text) {
    assert(client == sends++ && client < 2);
    assert(!strcmp(text, "tinfo 3 0 10 -20 100 0 1 11 -21 0 0 2 12 -22 -1 0"));
}
void QDECL Com_Error(int level, const char *format, ...) { abort(); }
void QDECL Com_Printf(const char *format, ...) { abort(); }
#undef vsnprintf
int Q_vsnprintf(char *out, int size, const char *format, va_list args) {
    return vsnprintf(out, size, format, args);
}
int main(void) {
    int i;
    level.numConnectedClients = 3;
    for(i = 0; i < 3; ++i) {
        level.sortedClients[i] = i;
        g_entities[i].inuse = qtrue; g_entities[i].client = &clients[i];
        clients[i].sess.sessionTeam = TEAM_AXIS; clients[i].pers.connected = CON_CONNECTED;
        clients[i].ps.stats[STAT_HEALTH] = i ? -10 : 100;
        g_entities[i].r.currentOrigin[0] = 10.75f + i;
        g_entities[i].r.currentOrigin[1] = -20.75f - i;
    }
    g_entities[1].r.svFlags = SVF_POW;
    g_entities[2].r.svFlags = SVF_BOT; clients[2].ps.pm_flags = PMF_LIMBO;
    TeamplayInfoMessage(TEAM_AXIS); assert(sends == 2);
    TeamplayInfoMessage(TEAM_AXIS); assert(sends == 2); /* Unchanged data cached. */
    puts("WASM teaminfo: live XY, health/limbo, POW inclusion, bot exclusion and cache passed");
    return 0;
}
