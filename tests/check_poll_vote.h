/* UI sends callvote poll; exercise the actual server dispatcher/callback. */
static const char *pollArgs[8];
static int pollArgc, pollMessages, pollDisabled, pollFlagWrites, pollFlags;
static unsigned int pollAllowedMask;
static int QDECL PollEngine(int command, ...) {
    va_list args;
    int result = 0;
    va_start(args, command);
    if(command == G_ARGC) result = pollArgc;
    else if(command == G_ARGV) {
        int index = va_arg(args, int);
        char *out = va_arg(args, char *);
        int size = va_arg(args, int);
        if(index < 0 || index >= pollArgc) exit(2);
        Q_strncpyz(out, pollArgs[index], size);
    } else if(command == G_SEND_SERVER_COMMAND) {
        if(va_arg(args, int) != 3) exit(2);
        if(!strstr(va_arg(args, const char *), "voting has been disabled")) exit(2);
        ++pollMessages;
    } else if(command == G_CVAR_VARIABLE_INTEGER_VALUE) {
        const char *name = va_arg(args, const char *);
        int i;
        for(i = 0; i < numVotesAvailable; ++i)
            if(!strcmp(name, voteToggles[i].pszCvar)) result = !!(pollAllowedMask & voteToggles[i].flag);
    } else if(command == G_CVAR_SET) {
        if(strcmp(va_arg(args, const char *), "voteFlags")) exit(2);
        pollFlags = atoi(va_arg(args, const char *)); ++pollFlagWrites;
    } else exit(2);
    va_end(args); return result;
}
static int CheckPollVote(void) {
    static const char *questions[] = { "", "a", "ab", "Play another map?", "^2GG?",
        "bad\"text", "bad;text", "bad\\text", "bad\ntext", "bad\rtext", "bad\ttext" };
    voteInfo_t saved = level.voteInfo;
    vmCvar_t savedAllow = vote_allow_poll, savedFlags = voteFlags;
    vmCvar_t savedRestart = vote_allow_maprestart;
    char command[VOTE_MAXSTRING], output[VOTE_MAXSTRING], longQuestion[VOTE_MAXSTRING + 2];
    int i, disabled, ref, errors = 0;
    dllEntry(PollEngine);
    pollArgs[0] = "callvote"; pollArgs[1] = "poll"; pollArgc = 3;
    for(disabled = 0; disabled < 2; ++disabled) for(ref = 0; ref < 2; ++ref)
    for(i = 0; i < (int)(sizeof(questions)/sizeof(questions[0])); ++i) {
        int valid = !disabled && i >= 2 && i <= 4;
        vote_allow_poll.integer = !disabled;
        pollArgs[2] = questions[i]; pollMessages = 0;
        strcpy(command, "PoLl"); strcpy(output, "unchanged");
        if(G_voteCmdCheck(&g_entities[3], command, output, ref) != (valid ? G_OK : G_INVALID)) ++errors;
        if(pollMessages != disabled) ++errors;
        if(valid) {
            voteInfo_t before = level.voteInfo;
            if(strcmp(command, "[poll]") || strcmp(output, questions[i]) || !level.voteInfo.vote_fn) ++errors;
            else if(level.voteInfo.vote_fn(NULL, 0, NULL, NULL, qfalse) != G_OK ||
                memcmp(&before, &level.voteInfo, sizeof(before))) ++errors;
        } else if(strcmp(output, "unchanged") || level.voteInfo.vote_fn) ++errors;
    }
    vote_allow_poll.integer = 1;
    pollArgs[2] = "Play"; pollArgs[3] = "another map?"; pollArgc = 4;
    strcpy(command, "poll");
    if(G_voteCmdCheck(&g_entities[3], command, output, qfalse) != G_OK ||
       strcmp(output, "Play another map?")) ++errors;
    pollArgc = 3;
    for(i = 254; i <= 257; ++i) {
        memset(longQuestion, 'a', i); longQuestion[i] = 0; pollArgs[2] = longQuestion;
        strcpy(command, "poll");
        if(G_voteCmdCheck(&g_entities[3], command, output, qfalse) !=
           (i < VOTE_MAXSTRING ? G_OK : G_INVALID)) ++errors;
    }
    pollArgc = 4; pollArgs[2] = "Valid prefix"; pollArgs[3] = longQuestion;
    strcpy(command, "poll"); strcpy(output, "unchanged");
    if(G_voteCmdCheck(&g_entities[3], command, output, qfalse) != G_INVALID ||
       strcmp(output, "unchanged")) ++errors;
    pollArgc = 3; pollArgs[2] = "Console poll?"; vote_allow_poll.integer = 0;
    strcpy(command, "poll"); pollMessages = 0;
    if(G_voteCmdCheck(NULL, command, output, qfalse) != G_OK || pollMessages ||
       strcmp(output, "Console poll?")) ++errors;
    strcpy(command, "unknown_vote");
    if(G_voteCmdCheck(&g_entities[3], command, output, qfalse) != G_NOTFOUND) ++errors;
    {
        const char *names[] = {"shuffleteams", "shuffleteams_norestart", "swapteams", "swapteamsrestart"};
        int (*handlers[])(gentity_t *, unsigned int, char *, char *, qboolean) = {
            G_NITMOD_ShuffleVote, G_NITMOD_ShuffleNoRestartVote, G_NITMOD_SwapVote, G_NITMOD_SwapRestartVote};
        pollArgc = 2;
        for(i = 0; i < 4; ++i) {
            strcpy(command, names[i]); output[0] = 0;
            if(G_voteCmdCheck(NULL, command, output, qfalse) != G_OK || level.voteInfo.vote_fn != handlers[i]) ++errors;
        }
    }
    pollArgc = 2;
    for(disabled = 0; disabled < 2; ++disabled) for(ref = 0; ref < 2; ++ref) {
        vote_allow_maprestart.integer = !disabled; pollMessages = 0;
        strcpy(command, "maprestart"); output[0] = 0;
        if(G_voteCmdCheck(&g_entities[3], command, output, ref) != (disabled ? G_INVALID : G_OK) ||
           pollMessages != disabled || (!disabled && level.voteInfo.vote_fn != G_MapRestart_v)) ++errors;
    }
    for(pollDisabled = 0; pollDisabled < 2; ++pollDisabled) {
        pollAllowedMask = pollDisabled ? 0 : 1048576;
        voteFlags.integer = 0; pollFlagWrites = 0; G_voteFlags();
        if(pollFlagWrites != 1 || pollFlags != (VOTING_DISABLED ^ (pollDisabled ? 0 : 1048576))) ++errors;
        voteFlags.integer = pollFlags; G_voteFlags();
        if(pollFlagWrites != 1) ++errors;
    }
    for(i = 0; i < numVotesAvailable; ++i) {
        pollAllowedMask = voteToggles[i].flag;
        voteFlags.integer = 0; pollFlagWrites = 0; G_voteFlags();
        if(pollFlagWrites != 1 || pollFlags != (VOTING_DISABLED ^ voteToggles[i].flag)) ++errors;
    }
    level.voteInfo = saved; vote_allow_poll = savedAllow; voteFlags = savedFlags;
    vote_allow_maprestart = savedRestart;
    dllEntry(EngineCallback);
    if(errors) printf("Poll vote: %d errors\n", errors);
    return errors;
}
