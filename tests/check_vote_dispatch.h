/* Exercise the command-table indirect call, not just Cmd_CallVote_f. */
static int voteDispatchCalls;
static const char *voteDispatchExpected;
static int QDECL VoteDispatchEngine(int command, ...) {
    va_list args;
    if(command == G_ARGV) {
        char *out;
        va_start(args, command);
        if(va_arg(args, int) != 1) exit(2);
        out = va_arg(args, char *);
        if(va_arg(args, int) < 1) exit(2);
        out[0] = 0;
        va_end(args); return 0;
    }
    if(command != G_SEND_SERVER_COMMAND) exit(2);
    va_start(args, command);
    if(va_arg(args, int) != 3 || strcmp(va_arg(args, const char *), voteDispatchExpected)) exit(2);
    va_end(args); ++voteDispatchCalls;
    return 0;
}
static int CheckVoteDispatch(void) {
    int savedVoteTime = level.voteInfo.voteTime;
    int savedIntermission = level.intermissiontime;
    int errors = 0, phase;
    dllEntry(VoteDispatchEngine);
    for(phase = 0; phase < 2; ++phase) {
        level.voteInfo.voteTime = phase ? 0 : 1;
        level.intermissiontime = phase ? 1 : 0;
        voteDispatchExpected = phase ? "cpm \"Cannot callvote during intermission.\n\"" :
            "cpm \"A vote is already in progress.\n\"";
        voteDispatchCalls = 0;
        if(G_commandCheck(&g_entities[3], "callvote", qfalse) || voteDispatchCalls) ++errors;
        if(!G_commandCheck(&g_entities[3], "callvote", qtrue) || voteDispatchCalls != 1) ++errors;
        if(!G_commandCheck(&g_entities[3], "CALLVOTE", qtrue) || voteDispatchCalls != 2) ++errors;
    }
    level.voteInfo.voteTime = savedVoteTime;
    level.intermissiontime = savedIntermission;
    dllEntry(EngineCallback);
    return errors;
}
