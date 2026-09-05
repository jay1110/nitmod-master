static char rosterAxis[256], rosterAllies[256];
static int rosterWrites;
static int QDECL RosterSyscall(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == G_CVAR_SET) {
        const char *name = va_arg(args, const char *), *value = va_arg(args, const char *);
        if(!strcmp(name, "Players_Axis")) Q_strncpyz(rosterAxis, value, sizeof(rosterAxis));
        else if(!strcmp(name, "Players_Allies")) Q_strncpyz(rosterAllies, value, sizeof(rosterAllies));
        else if(strcmp(name, "P")) exit(2);
        ++rosterWrites;
    } else if(command != G_SET_CONFIGSTRING) exit(2);
    va_end(args); return 0;
}
static int CheckTeamRosters(void) {
    static level_locals_t savedLevel;
    static gclient_t clients[MAX_CLIENTS];
    static gentity_t savedEntities[MAX_CLIENTS];
    vmCvar_t savedState = g_gamestate;
    const int slots[3] = { 0, 7, MAX_CLIENTS - 1 };
    int profile, i, errors = 0;
    savedLevel = level;
    memcpy(savedEntities, g_entities, sizeof(savedEntities));
    dllEntry(RosterSyscall);
    for(profile = 0; profile <= 1728; ++profile) {
        char axis[256] = "", allies[256] = "";
        int code = profile, connected = 0;
        memset(&level, 0, sizeof(level)); memset(clients, 0, sizeof(clients));
        memset(g_entities, 0, sizeof(savedEntities));
        level.maxclients = MAX_CLIENTS; level.clients = clients;
        g_gamestate.integer = GS_INTERMISSION;
        for(i = 0; i < (profile == 1728 ? MAX_CLIENTS : 3); ++i) {
            int slot = profile == 1728 ? i : slots[i];
            int state = profile == 1728 ? CON_CONNECTED : code % 3;
            int team = profile == 1728 ? TEAM_AXIS : (code / 3) % 4;
            char number[16];
            code /= 12;
            clients[slot].pers.connected = state;
            clients[slot].sess.sessionTeam = team;
            clients[slot].ps.persistant[PERS_SCORE] = MAX_CLIENTS - slot;
            g_entities[slot].client = &clients[slot];
            g_entities[slot].inuse = qtrue;
            if(state == CON_DISCONNECTED) continue;
            ++connected;
            Com_sprintf(number, sizeof(number), "%d ", connected);
            if(team == TEAM_AXIS) Q_strcat(axis, sizeof(axis), number);
            if(team == TEAM_ALLIES) Q_strcat(allies, sizeof(allies), number);
        }
        rosterWrites = 0; rosterAxis[0] = rosterAllies[0] = 0;
        CalculateRanks();
        if(rosterWrites != 3 || strcmp(rosterAxis, axis[0] ? axis : "(None)") ||
           strcmp(rosterAllies, allies[0] ? allies : "(None)") ||
           level.numConnectedClients != connected) ++errors;
    }
    level = savedLevel; g_gamestate = savedState;
    memcpy(g_entities, savedEntities, sizeof(savedEntities));
    return errors;
}
