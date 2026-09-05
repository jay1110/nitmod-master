extern void Script_Exec(itemDef_t *, qboolean *, char **);
static int campaignMenuExecs;
static char campaignMenuCommand[256];
static void CampaignMenuExecute(int mode, const char *text) {
    if(mode != EXEC_APPEND) exit(2);
    Q_strncpyz(campaignMenuCommand, text, sizeof(campaignMenuCommand)); ++campaignMenuExecs;
}
static int CheckCampaignMenuVote(displayContextDef_t *dc) {
    static const char *commands[] = { "cmd callvote restartcamaign", "CMD CALLVOTE RESTARTCAMAIGN",
        "cmd callvote restartcampaign", "cmd callvote nextcampaign", "echo restartcamaign" };
    void (*savedExecute)(int, const char *) = dc->executeText;
    int i, errors = 0;
    dc->executeText = CampaignMenuExecute;
    for(i = 0; i < 5; ++i) {
        char script[256], expected[256], *cursor = script;
        Com_sprintf(script, sizeof(script), "\"%s\"", commands[i]);
        Com_sprintf(expected, sizeof(expected), "%s ; ", i < 2 ? "cmd callvote restartcampaign" : commands[i]);
        campaignMenuExecs = 0; Script_Exec(NULL, NULL, &cursor);
        if(campaignMenuExecs != 1 || strcmp(expected, campaignMenuCommand)) ++errors;
    }
    dc->executeText = savedExecute;
    return errors;
}
