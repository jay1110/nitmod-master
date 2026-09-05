/* Exercise the real StartServer dispatcher, not an isolated string helper. */
static int hostExecs, hostWrites, hostErrors, hostOverrides, hostRequested;
static const char *hostExpected;
static int QDECL HostSyscall(int command, ...) {
    va_list args;
    int result = 0;
    va_start(args, command);
    if(command == UI_CVAR_VARIABLEVALUE) {
        const char *name = va_arg(args, const char *);
        union { float f; int i; } value;
        if(!strcmp(name, "sv_punkbuster") || !strcmp(name, "cl_punkbuster")) value.f = 0;
        else if(!strcmp(name, "ui_userTimelimit") || !strcmp(name, "ui_userAxisRespawnTime") ||
                !strcmp(name, "ui_userAlliedRespawnTime")) value.f = (float)hostRequested;
        else exit(2);
        result = value.i;
    } else if(command == UI_CVAR_SET) {
        const char *name = va_arg(args, const char *), *value = va_arg(args, const char *);
        if(!strcmp(name, "com_errorMessage")) ++hostErrors;
        else {
            ++hostWrites;
            if(!strncmp(name, "g_user", 6)) {
                int expected = hostRequested == 20 ? 0 : hostRequested;
                if(atoi(value) != expected) exit(2);
                ++hostOverrides;
            }
        }
    } else if(command == UI_CVAR_SETVALUE) {
        (void)va_arg(args, const char *); (void)va_arg(args, int); ++hostWrites;
    } else if(command == UI_CMD_EXECUTETEXT) {
        if(va_arg(args, int) != EXEC_APPEND || strcmp(va_arg(args, const char *), hostExpected) ||
           hostOverrides != 3) exit(2);
        ++hostExecs;
    } else exit(2);
    va_end(args);
    return result;
}
static int CheckHostStart(void) {
    static uiInfo_t saved;
    vmCvar_t savedMap = ui_currentNetMap, savedType = ui_netGameType, savedDedicated = ui_dedicated;
    int state, mode, request, dedicated, errors = 0;
    saved = uiInfo;
    dllEntry(HostSyscall);
    for(mode = 0; mode <= 8; ++mode) for(state = 0; state < 13; ++state)
    for(request = 0; request < 3; ++request) for(dedicated = 0; dedicated < 3; ++dedicated) {
        char script[] = "StartServer", *cursor = script;
        int valid = state == 0;
        uiInfo.mapCount = 2; uiInfo.campaignCount = 1;
        ui_currentNetMap.integer = mode == GT_WOLF_CAMPAIGN ? 0 : 1;
        ui_netGameType.integer = mode; ui_dedicated.integer = dedicated;
        uiInfo.mapList[0].mapLoadName = "wrong_map";
        uiInfo.mapList[0].Timelimit = 99;
        uiInfo.mapList[1].mapLoadName = "goldrush-ga";
        uiInfo.mapList[1].Timelimit = uiInfo.mapList[1].AxisRespawnTime =
            uiInfo.mapList[1].AlliedRespawnTime = 20;
        uiInfo.campaignList[0].mapCount = 1;
        uiInfo.campaignList[0].mapInfos[0] = &uiInfo.mapList[1];
        switch(state) {
        case 1: ui_currentNetMap.integer = -1; break;
        case 2: ui_currentNetMap.integer = 0x7fffffff; break;
        case 3: uiInfo.mapCount = 0; break;
        case 4: uiInfo.mapCount = MAX_MAPS + 1; break;
        case 5: uiInfo.mapList[1].mapLoadName = NULL; break;
        case 6: uiInfo.mapList[1].mapLoadName = ""; break;
        case 7: uiInfo.mapList[1].mapLoadName = "oasis;quit"; break;
        case 8: uiInfo.mapList[1].mapLoadName = "oasis\nquit"; break;
        case 9: ui_netGameType.integer = 9; break;
        case 10: uiInfo.campaignList[0].mapCount = 0; valid = mode != GT_WOLF_CAMPAIGN; break;
        case 11: uiInfo.campaignList[0].mapInfos[0] = NULL; valid = mode != GT_WOLF_CAMPAIGN; break;
        case 12: uiInfo.campaignCount = MAX_CAMPAIGNS + 1; valid = mode != GT_WOLF_CAMPAIGN; break;
        }
        hostRequested = request == 0 ? 0 : request == 1 ? 20 : 35;
        hostExpected = "wait ; wait ; map goldrush-ga\n";
        hostExecs = hostWrites = hostErrors = hostOverrides = 0;
        UI_RunMenuScript(&cursor);
        if(hostExecs != valid || hostErrors != !valid || hostWrites != (valid ? 9 : 0)) ++errors;
    }
    uiInfo = saved; ui_currentNetMap = savedMap; ui_netGameType = savedType; ui_dedicated = savedDedicated;
    return errors;
}
