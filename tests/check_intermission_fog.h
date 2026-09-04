static int CheckIntermissionFog(void) {
    static gameState_t saved;
    const char *savedFields[21];
    const char *bad[] = {"", "628150", "1", "0 100 1 0 0", "0 -1 1 0 0 100",
        "0 100 nan 0 0 100", "0 100 2 0 0 100", "0 100 1 0 0 0", "1 2 junk", "0 100 1 0 0 1e-99"};
    int i, errors = 0, oldArgc = argcValue, oldTime = cgs.intermissionStartTime;
    saved = cgs.gameState; memcpy(savedFields, fields, sizeof(fields));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
    fields[0] = "cs"; fields[1] = "33"; argcValue = 2; fogCalls = 0;
    SetTestConfig(33, "628150");
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(fogCalls || cgs.intermissionStartTime != 628150 || strcmp(CG_ConfigString(CS_INTERMISSION_START_TIME), "628150")) ++errors;
    fields[1] = "30";
    for(i = 0; i < sizeof(bad)/sizeof(bad[0]); ++i) {
        SetTestConfig(30, bad[i]);
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(fogCalls) ++errors;
    }
    SetTestConfig(30, "0 100 0.2 0.3 0.4 1000");
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(fogCalls != 1) ++errors;
    SetTestConfig(30, "1 100 0 0 0 0");
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(fogCalls != 2) ++errors;
    fields[0] = "mes"; argcValue = 6;
    for(i = 1; i < 6; ++i) fields[i] = "7";
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(NITMOD_MapEndStats()->kills != 7 || NITMOD_MapEndStats()->deaths != 7 ||
       NITMOD_MapEndStats()->bodyshots != 7 || NITMOD_MapEndStats()->headshots != 7 ||
       NITMOD_MapEndStats()->revives != 7) ++errors;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\etmain");
    fields[0] = "cs"; fields[1] = "33"; argcValue = 2;
    SetTestConfig(33, "0 0 0.1 0.2 0.3 200");
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(fogCalls != 3) ++errors;
    cgs.gameState = saved; memcpy(fields, savedFields, sizeof(fields));
    argcValue = oldArgc; cgs.intermissionStartTime = oldTime;
    if(errors) fprintf(stderr, "intermission fog: %d failures (calls %d)\n", errors, fogCalls);
    return errors;
}
