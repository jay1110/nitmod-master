extern void CG_Debreifing2_Awards_Parse(void);
static int CheckIntermissionFog(void) {
    static gameState_t saved;
    const char *savedFields[21];
    const char *bad[] = {"", "628150", "1", "0 100 1 0 0", "0 -1 1 0 0 100",
        "0 100 nan 0 0 100", "0 100 2 0 0 100", "0 100 1 0 0 0", "1 2 junk", "0 100 1 0 0 1e-99"};
    int i, errors = 0, oldArgc = argcValue, oldTime = cgs.intermissionStartTime;
    saved = cgs.gameState; memcpy(savedFields, fields, sizeof(fields));
    memset(&cgs.gameState, 0, sizeof(cgs.gameState)); cgs.gameState.dataCount = 1;
    SetTestConfig(CS_SERVERINFO, "\\gamename\\nitmod");
    {
        char awards[1024] = "", truncated[1024];
        int row, team;
        const char *winner;
        qboolean savedParsed = cgs.dbAwardsParsed;
        for(row = 0; row < 16; ++row) Q_strcat(awards, sizeof(awards), va(";^1Player %d; %d ", row, row % 3));
        if(!CG_NitmodParseRoundAwards(awards)) ++errors;
        for(row = 0; row < 16; ++row) {
            if(!CG_NitmodRoundAward(row, &winner, &team) || team != row % 3 || strcmp(winner, va("^1Player %d", row))) ++errors;
        }
        if(strcmp(CG_NitmodRoundAward(15, NULL, NULL), "Best FieldOps") || CG_NitmodRoundAward(16, NULL, NULL)) ++errors;
        for(row = 0; row < (int)strlen(awards) - 2; ++row) {
            memcpy(truncated, awards, row); truncated[row] = 0;
            if(CG_NitmodParseRoundAwards(truncated)) ++errors;
            CG_NitmodRoundAward(0, &winner, &team);
            if(team || *winner) ++errors;
        }
        Q_strcat(awards, sizeof(awards), "extra");
        if(CG_NitmodParseRoundAwards(awards)) ++errors;
        SetTestConfig(34, "round awards");
        if(strcmp(CG_ConfigString(CS_ENDGAME_STATS), "round awards")) ++errors;
        fields[0] = "cs"; fields[1] = "34"; argcValue = 2; cgs.dbAwardsParsed = qtrue;
        CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
        if(cgs.dbAwardsParsed) ++errors;
        cgs.dbAwardsParsed = savedParsed;
    }
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
    {
        char awards[1024] = "", prefix[1024];
        int row, cut, dataStart = cgs.gameState.dataCount;
        for(row = 0; row < NUM_ENDGAME_AWARDS; ++row)
            Q_strcat(awards, sizeof(awards), va(";Player %d; %d ", row, row % 2 ? TEAM_AXIS : -1));
        SetTestConfig(CS_ENDGAME_STATS, awards); CG_Debreifing2_Awards_Parse();
        for(row = 0; row < NUM_ENDGAME_AWARDS; ++row)
            if(strcmp(cgs.dbAwardNames[row], va("Player %d", row)) ||
               cgs.dbAwardTeams[row] != (row % 2 ? TEAM_AXIS : -1)) ++errors;
        for(cut = 0; cut < (int)strlen(awards) - 2; ++cut) {
            memcpy(prefix, awards, cut); prefix[cut] = 0;
            cgs.gameState.dataCount = dataStart;
            SetTestConfig(CS_ENDGAME_STATS, prefix); CG_Debreifing2_Awards_Parse();
            for(row = 0; row < NUM_ENDGAME_AWARDS; ++row)
                if(cgs.dbAwardTeams[row] != -1 || *cgs.dbAwardNames[row]) ++errors;
        }
        memset(prefix, 'x', sizeof(prefix) - 1); prefix[sizeof(prefix) - 1] = 0;
        cgs.gameState.dataCount = dataStart;
        SetTestConfig(CS_ENDGAME_STATS, prefix); CG_Debreifing2_Awards_Parse();
        for(row = 0; row < NUM_ENDGAME_AWARDS; ++row)
            if(cgs.dbAwardTeams[row] != -1 || cgs.dbAwardNames[row] != cgs.dbAwardNamesBuffer) ++errors;
        cgs.dbAwardsParsed = qfalse;
    }
    fields[0] = "cs"; fields[1] = "33"; argcValue = 2;
    SetTestConfig(33, "0 0 0.1 0.2 0.3 200");
    CG_ExecuteNewServerCommands(cgs.serverCommandSequence + 1);
    if(fogCalls != 3) ++errors;
    cgs.gameState = saved; memcpy(fields, savedFields, sizeof(fields));
    argcValue = oldArgc; cgs.intermissionStartTime = oldTime;
    if(errors) fprintf(stderr, "intermission fog: %d failures (calls %d)\n", errors, fogCalls);
    return errors;
}
