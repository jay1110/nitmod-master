static const char *campaignVoteNext;
static char campaignVoteCommand[2048];
static int campaignVoteReads, campaignVoteExecs;
static int QDECL CampaignVoteEngine(int command, ...) {
    va_list args;
    va_start(args, command);
    if(command == G_CVAR_VARIABLE_STRING_BUFFER) {
        char *out; int size;
        if(strcmp(va_arg(args, const char *), "nextcampaign")) exit(2);
        out = va_arg(args, char *); size = va_arg(args, int);
        Q_strncpyz(out, campaignVoteNext, size); ++campaignVoteReads;
    } else if(command == G_SEND_CONSOLE_COMMAND) {
        if(va_arg(args, int) != EXEC_APPEND) exit(2);
        Q_strncpyz(campaignVoteCommand, va_arg(args, const char *), sizeof(campaignVoteCommand));
        ++campaignVoteExecs;
    } else exit(2);
    va_end(args); return 0;
}
static int CheckCampaignVotes(void) {
    static const char *names[] = { "cmp_one-2", "", "bad name", "bad;quit", "bad\"name", "../bad" };
    static const char *nexts[] = { "", "vstr c2", "campaign cmp2; set nextcampaign vstr_c3", "bad\"text", "bad\ntext", "bad\\text" };
    voteInfo_t savedVote = level.voteInfo;
    vmCvar_t savedMode = g_gametype, savedNext = vote_allow_nextcampaign, savedRestart = vote_allow_restartcampaign;
    g_campaignInfo_t savedCampaign = g_campaigns[0];
    int savedCount = level.campaignCount, savedCurrent = level.currentCampaign;
    int mode, allow, caller, ref, kind, n, v, errors = 0;
    char arg[VOTE_MAXSTRING], arg2[VOTE_MAXSTRING], expected[2048];
    dllEntry(CampaignVoteEngine);
    campaignVoteReads = campaignVoteExecs = 0;
    for(mode = 0; mode <= 8; ++mode) for(allow = 0; allow < 2; ++allow)
    for(caller = 0; caller < 2; ++caller) for(ref = 0; ref < 2; ++ref) for(kind = 0; kind < 2; ++kind) {
        int valid = mode == GT_WOLF_CAMPAIGN && (!caller || allow);
        g_gametype.integer = mode;
        vote_allow_nextcampaign.integer = vote_allow_restartcampaign.integer = allow;
        strcpy(arg, kind ? "restartcampaign" : "nextcampaign"); strcpy(arg2, "");
        if(G_voteCmdCheck(caller ? &g_entities[3] : NULL, arg, arg2, ref) != (valid ? G_OK : G_INVALID)) ++errors;
        if(valid && strcmp(arg, kind ? "Restart Campaign" : "Next Campaign")) ++errors;
        if(!valid && level.voteInfo.vote_fn) ++errors;
        if(campaignVoteReads || campaignVoteExecs) ++errors;
    }
    for(v = 0; v < 6; ++v) {
        campaignVoteNext = nexts[v]; campaignVoteReads = campaignVoteExecs = 0;
        if(G_NITMOD_NextCampaignVote(NULL, 0, NULL, NULL, qfalse) != G_OK ||
           campaignVoteReads != 1 || campaignVoteExecs != (v != 0) ||
           (v && strcmp(campaignVoteCommand, "vstr nextcampaign\n"))) ++errors;
    }
    level.campaignCount = 1; level.currentCampaign = 0;
    for(n = 0; n < 6; ++n) for(v = 0; v < 6; ++v) {
        int valid = n == 0 && v < 3;
        strcpy(g_campaigns[0].shortname, names[n]); campaignVoteNext = nexts[v];
        campaignVoteReads = campaignVoteExecs = 0;
        if(G_NITMOD_RestartCampaignVote(NULL, 0, NULL, NULL, qfalse) != (valid ? G_OK : G_INVALID) ||
           campaignVoteExecs != valid || campaignVoteReads != (n == 0)) ++errors;
        if(valid) {
            if(v) Com_sprintf(expected, sizeof(expected), "campaign cmp_one-2; set nextcampaign \"%s\"\n", nexts[v]);
            else strcpy(expected, "campaign cmp_one-2\n");
            if(strcmp(campaignVoteCommand, expected)) ++errors;
        }
    }
    strcpy(g_campaigns[0].shortname, "valid"); campaignVoteNext = "";
    for(n = -1; n <= MAX_CAMPAIGNS + 1; ++n) {
        level.currentCampaign = n; campaignVoteReads = campaignVoteExecs = 0;
        if(G_NITMOD_RestartCampaignVote(NULL, 0, NULL, NULL, qfalse) != (n == 0 ? G_OK : G_INVALID) ||
           campaignVoteExecs != (n == 0)) ++errors;
    }
    level.currentCampaign = 0; memset(g_campaigns[0].shortname, 'x', sizeof(g_campaigns[0].shortname));
    campaignVoteReads = campaignVoteExecs = 0;
    if(G_NITMOD_RestartCampaignVote(NULL, 0, NULL, NULL, qfalse) != G_INVALID || campaignVoteReads || campaignVoteExecs) ++errors;
    level.voteInfo = savedVote; g_gametype = savedMode;
    vote_allow_nextcampaign = savedNext; vote_allow_restartcampaign = savedRestart;
    level.campaignCount = savedCount; level.currentCampaign = savedCurrent; g_campaigns[0] = savedCampaign;
    dllEntry(EngineCallback);
    if(errors) printf("Campaign votes: %d errors\n", errors);
    return errors;
}
