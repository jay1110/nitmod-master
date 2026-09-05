extern void UI_FeederSelection(float, int);
static int selectionReads, selectionWrites, selectionShaders, selectionMissing;
static int QDECL SelectionSyscall(int command, ...) {
    va_list args;
    int result = 0;
    va_start(args, command);
    if(command == UI_LAN_GETSERVERINFO) {
        char *out; int size;
        (void)va_arg(args, int);
        if(va_arg(args, int) != 42) exit(2);
        out = va_arg(args, char *); size = va_arg(args, int);
        Q_strncpyz(out, "\\mapname\\oasis", size); ++selectionReads;
    } else if(command == UI_R_REGISTERSHADERNOMIP) {
        const char *path = va_arg(args, const char *);
        if(!strcmp(path, "levelshots/oasis")) result = selectionMissing ? 0 : 71;
        else if(!strcmp(path, "levelshots/unknownmap")) result = 72;
        else exit(2);
        ++selectionShaders;
    } else if(command == UI_CVAR_SET) ++selectionWrites;
    else exit(2);
    va_end(args); return result;
}
static int CheckSelectionBounds(void) {
    static uiInfo_t saved;
    static const float feeders[] = { FEEDER_SERVERS, FEEDER_PLAYER_LIST, FEEDER_TEAM_LIST,
        FEEDER_HEADS, FEEDER_Q3HEADS };
    static const int limits[] = { MAX_DISPLAY_SERVERS, MAX_CLIENTS, MAX_CLIENTS,
        MAX_HEADS, MAX_PLAYERMODELS };
    static const int indices[] = { -1, 0, 1, 0x7fffffff };
    int f, c, i, missing, errors = 0;
    saved = uiInfo; dllEntry(SelectionSyscall);
    for(f = 0; f < 5; ++f) for(c = 0; c < 4; ++c)
    for(i = 0; i < 4; ++i) for(missing = 0; missing < 2; ++missing) {
        int count = c == 0 ? 1 : c == 1 ? 0 : c == 2 ? -1 : limits[f] + 1;
        int valid = c == 0 && indices[i] == 0;
        uiInfo.serverStatus.numDisplayServers = uiInfo.playerCount = uiInfo.myTeamCount =
            uiInfo.characterCount = uiInfo.q3HeadCount = count;
        uiInfo.serverStatus.displayServers[0] = 42;
        uiInfo.serverStatus.currentServer = uiInfo.playerIndex = uiInfo.teamIndex = 7;
        uiInfo.serverStatus.currentServerPreview = 99;
        uiInfo.characterList[0].name = "test";
        Q_strncpyz(uiInfo.q3HeadNames[0], "test", sizeof(uiInfo.q3HeadNames[0]));
        selectionReads = selectionWrites = selectionShaders = 0; selectionMissing = missing;
        UI_FeederSelection(feeders[f], indices[i]);
        if(selectionReads != (valid && f == 0) ||
           selectionWrites != (valid && f >= 3 ? 2 : 0) ||
           selectionShaders != (valid && f == 0 ? 1 + missing : 0)) ++errors;
        if(uiInfo.serverStatus.currentServer != (valid && f == 0 ? 0 : 7) ||
           uiInfo.playerIndex != (valid && f == 1 ? 0 : 7) ||
           uiInfo.teamIndex != (valid && f == 2 ? 0 : 7) ||
           uiInfo.serverStatus.currentServerPreview != (valid && f == 0 ? (missing ? 72 : 71) : 99)) ++errors;
    }
    uiInfo.serverStatus.numDisplayServers = 1;
    uiInfo.serverStatus.displayServers[0] = -1;
    selectionReads = selectionShaders = 0;
    UI_FeederSelection(FEEDER_SERVERS, 0);
    if(selectionReads || selectionShaders) ++errors;
    uiInfo = saved;
    return errors;
}
