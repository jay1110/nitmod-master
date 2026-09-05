static int mapConfigCommands, mapConfigWarnings;
static char mapConfigText[2][1024];
static int QDECL MapConfigSyscall(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == G_SEND_CONSOLE_COMMAND) {
        const char *text;
        if(va_arg(args, int) != EXEC_APPEND || mapConfigCommands >= 2) exit(2);
        text = va_arg(args, const char *);
        Q_strncpyz(mapConfigText[mapConfigCommands++], text, sizeof(mapConfigText[0]));
    } else if(command == G_PRINT) ++mapConfigWarnings;
    else exit(2);
    va_end(args); return 0;
}
static int CheckMapConfigs(void) {
    static const char *directories[] = { "configs", "nitmod/configs", "configs.v2", "",
        "../configs", "/configs", "configs/../other", "configs;quit", "configs\nquit",
        "C:\\configs", "configs//nested", "configs/", ".", "..", "configs/./nested" };
    static const char *maps[] = { "oasis", "goldrush-ga", "mml_minastirith_fp3", "",
        "../oasis", "oasis;quit", "oasis\nquit", "oasis\"", "oasis/other" };
    vmCvar_t savedSetting = g_mapConfigs;
    char savedMap[sizeof(level.rawmapname)];
    int d, m, errors = 0;
    memcpy(savedMap, level.rawmapname, sizeof(savedMap));
    dllEntry(MapConfigSyscall);
    for(d = 0; d < sizeof(directories)/sizeof(directories[0]); ++d)
    for(m = 0; m < sizeof(maps)/sizeof(maps[0]); ++m) {
        int valid = d < 3 && m < 3;
        char expected[1024];
        Q_strncpyz(g_mapConfigs.string, directories[d], sizeof(g_mapConfigs.string));
        Q_strncpyz(level.rawmapname, maps[m], sizeof(level.rawmapname));
        mapConfigCommands = mapConfigWarnings = 0;
        G_NITMOD_LoadMapConfigs();
        if(mapConfigCommands != (valid ? 2 : 0) || mapConfigWarnings != (!valid && d != 3)) ++errors;
        if(valid) {
            Com_sprintf(expected, sizeof(expected), "exec %s/default.cfg\n", directories[d]);
            if(strcmp(expected, mapConfigText[0])) ++errors;
            Com_sprintf(expected, sizeof(expected), "exec %s/%s.cfg\n", directories[d], maps[m]);
            if(strcmp(expected, mapConfigText[1])) ++errors;
        }
    }
    Q_strncpyz(level.rawmapname, "oasis", sizeof(level.rawmapname));
    memset(g_mapConfigs.string, 'a', sizeof(g_mapConfigs.string));
    mapConfigCommands = mapConfigWarnings = 0; G_NITMOD_LoadMapConfigs();
    if(mapConfigCommands || mapConfigWarnings != 1) ++errors;
    g_mapConfigs.string[sizeof(g_mapConfigs.string)-1] = 0;
    mapConfigCommands = mapConfigWarnings = 0; G_NITMOD_LoadMapConfigs();
    if(mapConfigCommands != 2 || mapConfigWarnings) ++errors;
    memset(level.rawmapname, 'a', sizeof(level.rawmapname));
    mapConfigCommands = mapConfigWarnings = 0; G_NITMOD_LoadMapConfigs();
    if(mapConfigCommands || mapConfigWarnings != 1) ++errors;
    g_mapConfigs = savedSetting; memcpy(level.rawmapname, savedMap, sizeof(savedMap));
    return errors;
}
