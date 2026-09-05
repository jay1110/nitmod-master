#include "g_local.h"

/* Original G_NextCampaign_v / G_RestartCampaign_v. Permission-6 bypass
 * remains denied for players until the Nitmod permission owner is ported. */
static int CampaignVoteRequest(gentity_t *ent, int allowed) {
    return ((!ent || allowed) && g_gametype.integer == GT_WOLF_CAMPAIGN) ? G_OK : G_INVALID;
}

int G_NITMOD_NextCampaignVote(gentity_t *ent, unsigned int index,
    char *arg, char *arg2, qboolean referee) {
    char next[MAX_STRING_CHARS];
    (void)index; (void)arg2; (void)referee;
    if(arg) return CampaignVoteRequest(ent, vote_allow_nextcampaign.integer);
    trap_Cvar_VariableStringBuffer("nextcampaign", next, sizeof(next));
    if(next[0]) trap_SendConsoleCommand(EXEC_APPEND, "vstr nextcampaign\n");
    return G_OK;
}

int G_NITMOD_RestartCampaignVote(gentity_t *ent, unsigned int index,
    char *arg, char *arg2, qboolean referee) {
    char next[MAX_STRING_CHARS], command[MAX_STRING_CHARS + 320];
    const char *name;
    size_t i;
    (void)index; (void)arg2; (void)referee;
    if(arg) return CampaignVoteRequest(ent, vote_allow_restartcampaign.integer);
    /* Validate the typed catalog before dereferencing the selected entry. */
    if(level.campaignCount <= 0 || level.campaignCount > MAX_CAMPAIGNS ||
       level.currentCampaign < 0 || level.currentCampaign >= level.campaignCount) return G_INVALID;
    name = g_campaigns[level.currentCampaign].shortname;
    for(i = 0; i < sizeof(g_campaigns[0].shortname) && name[i]; ++i) {
        unsigned char c = (unsigned char)name[i];
        if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || c == '_' || c == '-')) return G_INVALID;
    }
    if(!i || i == sizeof(g_campaigns[0].shortname)) return G_INVALID;
    trap_Cvar_VariableStringBuffer("nextcampaign", next, sizeof(next));
    /* Retain server-authored script separators inside the quoted value,
     * but never permit a value to escape the enclosing console command. */
    for(i = 0; next[i]; ++i) {
        unsigned char c = (unsigned char)next[i];
        if(c < 32 || c == 127 || c == '"' || c == '\\') return G_INVALID;
    }
    if(i == sizeof(next) - 1) return G_INVALID;
    if(next[0]) Com_sprintf(command, sizeof(command), "campaign %s; set nextcampaign \"%s\"\n", name, next);
    else Com_sprintf(command, sizeof(command), "campaign %s\n", name);
    trap_SendConsoleCommand(EXEC_APPEND, command);
    return G_OK;
}
