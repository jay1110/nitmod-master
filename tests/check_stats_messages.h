static char statsMessage[MAX_STRING_CHARS * 2];
static int statsMessages;
static int QDECL StatsMessageEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == G_ARGC) { va_end(args); return 2; }
    if(command == G_ARGV) {
        char *out; int size;
        if(va_arg(args, int) != 1) exit(2);
        out = va_arg(args, char *); size = va_arg(args, int); Q_strncpyz(out, "1", size);
    } else if(command == G_SEND_SERVER_COMMAND) {
        if(va_arg(args, int) != 3) exit(2);
        Q_strncpyz(statsMessage, va_arg(args, const char *), sizeof(statsMessage)); ++statsMessages;
    } else exit(2);
    va_end(args); return 0;
}
static int CheckStatsMessages(void) {
    static gclient_t clients[MAX_CLIENTS];
    gclient_t *savedClients = level.clients;
    int savedCount = level.numConnectedClients, savedSorted[MAX_CLIENTS], savedStats[MAX_CLIENTS];
    int count, i, weapon, mode, errors = 0;
    memcpy(savedSorted, level.sortedClients, sizeof(savedSorted));
    memcpy(savedStats, level.sortedStats, sizeof(savedStats));
    memset(clients, 0, sizeof(clients)); level.clients = clients;
    for(i = 0; i < MAX_CLIENTS; ++i) {
        level.sortedClients[i] = i; clients[i].pers.connected = CON_CONNECTED;
        clients[i].sess.sessionTeam = TEAM_AXIS;
        for(weapon = 0; weapon < WS_MAX; ++weapon) {
            clients[i].sess.aWeaponStats[weapon].atts = 2147483647;
            clients[i].sess.aWeaponStats[weapon].hits = 2147483647;
            clients[i].sess.aWeaponStats[weapon].kills = 2147483647;
            clients[i].sess.aWeaponStats[weapon].deaths = 2147483647;
        }
    }
    dllEntry(StatsMessageEngine);
    for(count = 0; count <= MAX_CLIENTS; ++count) for(mode = 0; mode < 4; ++mode) {
        const char *cursor; int rows = 0, consumed, a,b,c,d,e,f;
        level.numConnectedClients = count; statsMessages = 0;
        if(mode < 2) G_weaponStatsLeaders_cmd(&g_entities[3], qtrue, mode);
        else G_weaponRankings_cmd(&g_entities[3], 0, mode == 2);
        if(statsMessages != 1 || strlen(statsMessage) >= MAX_STRING_CHARS) { ++errors; continue; }
        cursor = strchr(statsMessage, ' ');
        if(!cursor) { ++errors; continue; }
        if(mode < 2) {
            for(;;) {
                if(sscanf(cursor, "%d%n", &a, &consumed) != 1) { ++errors; break; }
                if(a == 0) { cursor += consumed; break; }
                if(sscanf(cursor, "%d %d %d %d %d %d%n", &a,&b,&c,&d,&e,&f,&consumed) != 6 ||
                   a < 1 || a > WS_MAX || b < 0 || b >= count || c != 2147483647 ||
                   d != c || e != c || f != c) { ++errors; break; }
                cursor += consumed; ++rows;
            }
        } else {
            int advertised;
            if(sscanf(cursor, "%d %d %d%n", &advertised,&weapon,&a,&consumed) != 3) { ++errors; continue; }
            cursor += consumed;
            while(sscanf(cursor, "%d %d %d %d %d%n", &a,&b,&c,&d,&e,&consumed) == 5) {
                if(a < 0 || a >= count || b != 2147483647 || c != b || d != b || e != b) ++errors;
                cursor += consumed; ++rows;
            }
            if(rows != advertised || weapon != 1) ++errors;
        }
        while(*cursor == ' ') ++cursor;
        if(*cursor || (count && !rows)) ++errors;
    }
    level.numConnectedClients = 1;
    clients[0].sess.aWeaponStats[1].atts = 100;
    statsMessages = 0; G_weaponRankings_cmd(&g_entities[3], 0, qtrue);
    if(statsMessages != 1 || strncmp(statsMessage, "astats 1 1 2147483647 ", 22)) ++errors;
    level.clients = savedClients; level.numConnectedClients = savedCount;
    memcpy(level.sortedClients, savedSorted, sizeof(savedSorted)); memcpy(level.sortedStats, savedStats, sizeof(savedStats));
    dllEntry(EngineCallback);
    if(errors) printf("Stats message boundaries: %d errors\n", errors);
    return errors;
}
