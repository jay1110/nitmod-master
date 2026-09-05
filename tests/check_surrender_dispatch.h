static int surrenderMessages, surrenderWrites;
static int surrenderCheckingMajority;
extern void CheckVote(void);
static int QDECL SurrenderDispatchEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == G_SEND_SERVER_COMMAND) {
        if(va_arg(args, int) != (surrenderCheckingMajority ? -1 : 3)) exit(2);
        (void)va_arg(args, const char *); ++surrenderMessages;
    } else if(command == G_ARGV) {
        char *out; int size;
        if(va_arg(args, int) != 1) exit(2);
        out = va_arg(args, char *); size = va_arg(args, int); Q_strncpyz(out, "yes", size);
    } else if(command == G_SET_CONFIGSTRING) {
        if(va_arg(args, int) != (surrenderCheckingMajority ? CS_VOTE_TIME : CS_VOTE_YES) ||
           strcmp(va_arg(args, const char *), surrenderCheckingMajority ? "" : "2")) exit(2);
        ++surrenderWrites;
    } else exit(2);
    va_end(args); return 0;
}
static int CheckSurrenderDispatch(void) {
    static gclient_t fixtureClient;
    voteInfo_t savedVote = level.voteInfo;
    vmCvar_t savedState = g_gamestate, savedAllow = vote_allow_surrender;
    int savedTime = level.time, team, voter, errors = 0;
    char command[VOTE_MAXSTRING], value[VOTE_MAXSTRING];
    gclient_t *savedClient = g_entities[3].client;
    gclient_t *client = &fixtureClient;
    g_entities[3].client = client; level.time = 1000;
    g_gamestate.integer = GS_PLAYING; vote_allow_surrender.integer = 1;
    dllEntry(SurrenderDispatchEngine);
    for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team) {
        memset(client, 0, sizeof(*client)); client->sess.sessionTeam = team;
        strcpy(command, "surrender"); value[0] = 0;
        if(G_voteCmdCheck(&g_entities[3], command, value, qfalse) != G_OK ||
           level.voteInfo.vote_fn != G_NITMOD_SurrenderVote || level.voteInfo.surrenderTeam != team) ++errors;
        for(voter = TEAM_AXIS; voter <= TEAM_SPECTATOR; ++voter) {
            memset(client, 0, sizeof(*client)); client->sess.sessionTeam = voter;
            level.voteInfo.voteTime = 1; level.voteInfo.voteYes = 1; level.voteInfo.voteNo = 0;
            surrenderMessages = surrenderWrites = 0;
            Cmd_Vote_f(&g_entities[3]);
            if(surrenderMessages != 1 || surrenderWrites != (voter == team) ||
               level.voteInfo.voteYes != 1 + (voter == team) || level.voteInfo.voteNo ||
               !!(client->ps.eFlags & EF_VOTED) != (voter == team)) ++errors;
        }
    }
    {
        vmCvar_t savedPercent = vote_percent, savedDedicated = g_dedicated;
        fileHandle_t savedLog = level.logFile;
        int result;
        vote_percent.integer = 50; g_dedicated.integer = 0; level.logFile = 0;
        /* A round ending while voting is pending suppresses surrender's
         * side effects, but still allows observing the real vote tally. */
        g_gamestate.integer = GS_WARMUP; level.time = 2000;
        surrenderCheckingMajority = 1;
        for(team = TEAM_AXIS; team <= TEAM_ALLIES; ++team) for(result = 0; result < 3; ++result) {
            level.voteInfo.surrenderTeam = team;
            level.voteInfo.numVotingClients = 64;
            level.voteInfo.numVotingTeamClients[team == TEAM_AXIS ? 0 : 1] = 2;
            level.voteInfo.numVotingTeamClients[team == TEAM_AXIS ? 1 : 0] = 62;
            level.voteInfo.voteTime = 1;
            level.voteInfo.voteYes = result == 1 ? 2 : 0;
            level.voteInfo.voteNo = result == 2 ? 1 : 0;
            surrenderMessages = surrenderWrites = 0; CheckVote();
            if(surrenderMessages != (result != 0) || surrenderWrites != (result != 0) ||
               level.voteInfo.voteTime != (result ? 0 : 1)) ++errors;
        }
        surrenderCheckingMajority = 0;
        vote_percent = savedPercent; g_dedicated = savedDedicated; level.logFile = savedLog;
    }
    g_entities[3].client = savedClient; level.voteInfo = savedVote; level.time = savedTime;
    g_gamestate = savedState; vote_allow_surrender = savedAllow;
    dllEntry(EngineCallback);
    return errors;
}
