#include "g_local.h"
#include "nitmod_protocol.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
level_locals_t level;
gentity_t g_entities[MAX_GENTITIES];
vmCvar_t g_gametype;
static gclient_t clients[MAX_CLIENTS];
static int seen[MAX_CLIENTS], packets, rows;
static int kdEnabled, kdRows;
static int teamUpdates;
static int scoreOrder[MAX_CLIENTS], teamScoreSent, kdPackets;
void TeamplayInfoMessage(team_t team) {
    assert(teamScoreSent && kdRows == rows);
    assert(team == (teamUpdates++ ? TEAM_ALLIES : TEAM_AXIS));
}
qboolean G_NITMOD_ClientSupports(int client, unsigned int feature) {
    assert(client == 0 && feature == NITMOD_FEATURE_SCORE_KD); return kdEnabled;
}
qboolean G_smvLocateEntityInMVList(gentity_t *ent, int client, qboolean remove) { return qfalse; }
void nitmod_TeamScores(void) {
    assert(packets > 0 && kdPackets == 0);
    teamScoreSent = 1;
}
void trap_SendServerCommand(int client, const char *text) {
    char copy[1024], *cursor, *token;
    int count, i, j, id;
    assert(client == 0 && strlen(text) < sizeof(copy));
    strcpy(copy, text); cursor = copy;
    token = COM_Parse(&cursor);
    if(!strcmp(token, "kd0") || !strcmp(token, "kd1")) {
        assert(teamScoreSent);
        assert(!strcmp(token, kdPackets++ ? "kd1" : "kd0"));
        count = atoi(COM_Parse(&cursor));
        assert(kdEnabled);
        for(i = 0; i < count; ++i) {
            id = atoi(COM_Parse(&cursor)); assert(id == scoreOrder[kdRows++] && seen[id] == 1);
            assert(atoi(COM_Parse(&cursor)) == clients[id].sess.kills);
            assert(atoi(COM_Parse(&cursor)) == clients[id].sess.deaths);
        }
        assert(!*COM_Parse(&cursor)); return;
    }
    assert(!strcmp(token, packets ? "sc1" : "sc0"));
    if(!packets) { teamScoreSent = kdPackets = 0; }
    if(!packets) { COM_Parse(&cursor); COM_Parse(&cursor); }
    count = atoi(COM_Parse(&cursor));
    for(i = 0; i < count; ++i) {
        id = atoi(COM_Parse(&cursor)); assert(id >= 0 && id < MAX_CLIENTS);
        assert(!seen[id]++); scoreOrder[rows++] = id;
        for(j = 0; j < 6; ++j) assert(*COM_Parse(&cursor));
    }
    assert(!*COM_Parse(&cursor)); ++packets;
}
void QDECL Com_Error(int level, const char *format, ...) { abort(); }
void QDECL Com_Printf(const char *format, ...) { abort(); }
#undef vsnprintf
int Q_vsnprintf(char *out, int size, const char *format, va_list args) { return vsnprintf(out, size, format, args); }
int main(void) {
    int n, i;
    level.clients = clients;
    for(i = 0; i < MAX_CLIENTS; ++i) {
        level.sortedClients[i] = i; g_entities[i].client = &clients[i];
        clients[i].pers.connected = CON_CONNECTED;
    }
    for(n = 0; n <= MAX_CLIENTS; ++n) {
        level.numConnectedClients = n; packets = rows = 0; memset(seen, 0, sizeof(seen));
        G_SendScore(&g_entities[0]);
        assert(rows == n);
        for(i = 0; i < n; ++i) assert(seen[i] == 1);
    }
    /* Force byte-capacity splitting before the 32-row limit. */
    level.numConnectedClients = 40; level.time = 600000000;
    for(i = 0; i < 40; ++i) {
        clients[i].sess.skillpoints[0] = 100000000;
        clients[i].ps.ping = 999;
        clients[i].ps.persistant[PERS_RESPAWNS_LEFT] = 9999;
        g_entities[i].s.powerups = 123456789;
    }
    packets = rows = 0; memset(seen, 0, sizeof(seen));
    G_SendScore(&g_entities[0]); assert(rows == 40 && packets == 2);
    kdEnabled = 1;
    for(i = 0; i < 40; ++i) { clients[i].sess.kills = 100 + i; clients[i].sess.deaths = i; }
    packets = rows = kdRows = 0; memset(seen, 0, sizeof(seen));
    G_SendScore(&g_entities[0]); assert(rows == 40 && kdRows == 40);
    packets = rows = kdRows = 0; memset(seen, 0, sizeof(seen));
    Cmd_FullUpdate_f(&g_entities[0]);
    assert(rows == 40 && kdRows == 40 && teamUpdates == 2);
    Cmd_FullUpdate_f(NULL); assert(teamUpdates == 2);
    /* Nontrivial sort order and filtered rows must not shift positional K/D. */
    memset(clients, 0, sizeof(clients));
    for(i = 0; i < MAX_CLIENTS; ++i) {
        level.sortedClients[i] = MAX_CLIENTS - 1 - i;
        g_entities[i].s.powerups = 0;
        g_entities[i].r.svFlags = i % 7 == 0 ? SVF_POW : 0;
        clients[i].sess.kills = INT_MAX; clients[i].sess.deaths = INT_MIN;
    }
    level.numConnectedClients = MAX_CLIENTS; level.time = 0;
    packets = rows = kdRows = 0; memset(seen, 0, sizeof(seen));
    G_SendScore(&g_entities[0]);
    assert(rows == 54 && kdRows == rows && kdPackets == 2);
    for(i = 0; i < MAX_CLIENTS; ++i) assert(seen[i] == (i % 7 != 0));
    puts("WASM score pagination: 0..64 players and byte-limit split delivered exactly once");
    return 0;
}
