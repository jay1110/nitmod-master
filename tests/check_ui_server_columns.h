extern const char *UI_FeederItemText(float, int, int, qhandle_t *, int *);
static int columnReads, columnNettype, columnGame = 8;
static int QDECL ColumnSyscall(int command, ...) {
    va_list args;
    int source, server, size;
    char *out;
    if(command != UI_LAN_GETSERVERINFO) exit(2);
    va_start(args, command);
    source = va_arg(args, int); server = va_arg(args, int);
    out = va_arg(args, char *); size = va_arg(args, int);
    Com_sprintf(out, size, "\\hostname\\server%d-%d\\ping\\2147483647\\nettype\\%d\\gametype\\%d\\mapname\\map%d",
        source, server, columnNettype, columnGame, server);
    ++columnReads;
    va_end(args);
    return 0;
}
static int CheckServerColumns(void) {
    static uiInfo_t saved;
    qhandle_t handles[8];
    int count, errors = 0, source = ui_netSource.integer, n;
    const char *text;
    saved = uiInfo;
    dllEntry(ColumnSyscall);
    ui_netSource.integer = AS_GLOBAL;
    uiInfo.uiDC.realTime = 12345;
    uiInfo.serverStatus.numDisplayServers = 2;
    uiInfo.serverStatus.displayServers[0] = 10;
    uiInfo.serverStatus.displayServers[1] = 20;
    columnReads = 0;
    UI_FeederItemText(FEEDER_SERVERS, 0, SORT_HOST, handles, &count);
    text = UI_FeederItemText(FEEDER_SERVERS, 1, SORT_HOST, handles, &count);
    if(!strstr(text, "-20") || columnReads != 2) ++errors;
    text = UI_FeederItemText(FEEDER_SERVERS, 1, SORT_MAP, handles, &count);
    if(strcmp(text, "map20") || columnReads != 2) ++errors;
    uiInfo.serverStatus.displayServers[1] = 30;
    text = UI_FeederItemText(FEEDER_SERVERS, 1, SORT_MAP, handles, &count);
    if(strcmp(text, "map30") || columnReads != 3) ++errors;
    ui_netSource.integer = AS_LOCAL;
    for(n = -1; n <= 4; ++n) {
        columnNettype = n; ++uiInfo.uiDC.realTime;
        text = UI_FeederItemText(FEEDER_SERVERS, 1, SORT_HOST, handles, &count);
        if(!strstr(text, n == 1 ? "[UDP]" : n == 2 ? "[IPX]" : "[???]")) ++errors;
    }
    uiInfo.numGameTypes = 1;
    uiInfo.gameTypes[0].gtEnum = 8;
    uiInfo.gameTypes[0].gameTypeShort = "DM";
    if(strcmp(UI_FeederItemText(FEEDER_SERVERS, 1, SORT_GAME, handles, &count), "DM")) ++errors;
    {
        static const char *labels[] = {"LMS", "Vote", "TDM", "DM"};
        uiInfo.numGameTypes = 0;
        for(n=0;n<4;++n) {
            columnGame=5+n; ++uiInfo.uiDC.realTime;
            if(strcmp(UI_FeederItemText(FEEDER_SERVERS,1,SORT_GAME,handles,&count),labels[n])) ++errors;
        }
        columnGame=4; ++uiInfo.uiDC.realTime;
        if(strcmp(UI_FeederItemText(FEEDER_SERVERS,1,SORT_GAME,handles,&count),"???")) ++errors;
        columnGame=8;
    }
    if(!strstr(UI_FeederItemText(FEEDER_SERVERS, 1, SORT_PING, handles, &count), "2147483647")) ++errors;
    n = columnReads; --uiInfo.uiDC.realTime;
    UI_FeederItemText(FEEDER_SERVERS, 1, SORT_MAP, handles, &count);
    if(columnReads != n + 1) ++errors;
    uiInfo = saved; ui_netSource.integer = source;
    return errors;
}
