extern void CG_Debriefing_InfoRequests(void);
extern qboolean CG_Debriefing_NextButton_KeyDown(panel_button_t *, int);
static char debriefCommands[4][64];
static int debriefCommandCount;
static int QDECL DebriefEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command != CG_SENDCLIENTCOMMAND || debriefCommandCount >= 4) {
        fprintf(stderr, "Unexpected debrief syscall %d\n", command); exit(2);
    }
    Q_strncpyz(debriefCommands[debriefCommandCount++], va_arg(args, const char *), 64);
    va_end(args); return 0;
}
static int CheckDebriefPages(void) {
    static cgs_t saved;
    /* The underlying module object is mutable; save/restore only in this
     * fixture, without exposing a new production state-mutation API. */
    nitmodGameState_t *state = (nitmodGameState_t *)NITMOD_GameState();
    nitmodGameState_t savedState = *state;
    panel_button_t focus;
    panel_button_t *savedFocus = BG_PanelButtons_GetFocusButton();
    int protocol, game, options, flags, step, expected, count, enabled, errors = 0, oldTime = cg.time;
    const int pages[] = {3,1,2,0};
    saved = cgs; memset(&focus, 0, sizeof(focus)); dllEntry(DebriefEngine);
    cgs.gameState.stringOffsets[CS_SERVERINFO] = 1;
    for(protocol = 0; protocol < 2; ++protocol) for(game = 3; game <= 8; ++game)
    for(options = 0; options < 4; ++options) {
        strcpy(cgs.gameState.stringData + 1, protocol ? "\\gamename\\nitmod" : "\\gamename\\etmain");
        cgs.gametype = game;
        state->tdmOptions = options & 1 ? 8 : 0;
        state->dmOptions = options & 2 ? 0x4000 : 0;
        enabled = protocol && (game == 6 || (game == 7 && (options & 1)) || (game == 8 && (options & 2)));
        if(CG_NitmodMapVoteEnabled() != enabled) ++errors;
        cgs.dbMode = 0;
        for(step = 0; step < 12; ++step) {
            expected = enabled ? pages[step % 4] : (step + 1) % 3;
            BG_PanelButtons_SetFocusButton(&focus);
            if(CG_Debriefing_NextButton_KeyDown(NULL, K_ENTER) || BG_PanelButtons_GetFocusButton() != &focus) ++errors;
            if(!CG_Debriefing_NextButton_KeyDown(NULL, K_MOUSE1) || cgs.dbMode != expected || BG_PanelButtons_GetFocusButton()) ++errors;
        }
        for(flags = 0; flags < 32; ++flags) {
            cg.time = 10000;
            cgs.dbSelectedClient = 7;
            cgs.nitmodMapVoteListReceived = (flags & 1) != 0;
            cgs.dbPlayerKillsDeathsRecieved = (flags & 2) != 0;
            cgs.dbAccuraciesRecieved = (flags & 4) != 0;
            cgs.dbWeaponStatsRecieved = (flags & 8) != 0;
            cgs.dbHitRegionsRecieved = (flags & 16) != 0;
            cgs.dbLastRequestTime = cgs.dbLastScoreRequest = cgs.nitmodMapVoteRequestTime = 0;
            debriefCommandCount = 0;
            CG_Debriefing_InfoRequests();
            count = protocol && !(flags & 8) && !(flags & 16) ? 2 : 1;
            if(enabled && !(flags & 1)) { expected = 0; count = 1; }
            else if(!(flags & 2)) { expected = 1; count = 1; }
            else if(!(flags & 4)) { expected = 2; count = 1; }
            else if(!(flags & 8)) expected = 3;
            else { expected = 4; count = 1; }
            if(debriefCommandCount != count || strcmp(debriefCommands[0],
                expected == 0 ? "immaplist" : expected == 1 ? "impkd" : expected == 2 ? "imwa" : expected == 3 ? "imws 7" : "score") ||
                (count == 2 && strcmp(debriefCommands[1], "imhr 7"))) ++errors;
            cg.time += 999; CG_Debriefing_InfoRequests();
            if(debriefCommandCount != count) ++errors;
        }
    }
    strcpy(cgs.gameState.stringData + 1, "\\gamename\\nitmod");
    cgs.gametype = 6; cg.time = 5;
    cgs.nitmodMapVoteListReceived = qtrue;
    cgs.dbPlayerKillsDeathsRecieved = cgs.dbAccuraciesRecieved = cgs.dbWeaponStatsRecieved = qtrue;
    cgs.dbLastRequestTime = cgs.dbLastScoreRequest = INT_MAX;
    debriefCommandCount = 0; CG_Debriefing_InfoRequests();
    if(debriefCommandCount != 1 || strcmp(debriefCommands[0], "score")) ++errors;
    cgs.nitmodMapVoteTallyTime = INT_MAX;
    debriefCommandCount = 0; CG_NitmodMapVoteRequest();
    if(debriefCommandCount != 1 || strcmp(debriefCommands[0], "imvotetally")) ++errors;
    cgs.nitmodMapVoteListReceived = qfalse; cgs.nitmodMapVoteRequestTime = INT_MAX;
    debriefCommandCount = 0; CG_NitmodMapVoteRequest();
    if(debriefCommandCount != 1 || strcmp(debriefCommands[0], "immaplist")) ++errors;
    cgs.nitmodMapVoteListReceived = qtrue; cgs.dbWeaponStatsRecieved = qfalse;
    cgs.dbSelectedClient = MAX_CLIENTS; cgs.dbLastRequestTime = 0;
    debriefCommandCount = 0; CG_Debriefing_InfoRequests();
    if(debriefCommandCount) ++errors;
    cgs = saved; *state = savedState; cg.time = oldTime;
    BG_PanelButtons_SetFocusButton(savedFocus); dllEntry(Engine);
    if(errors) fprintf(stderr, "debrief page/request failures: %d\n", errors);
    return errors;
}
