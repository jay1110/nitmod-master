#include "g_local.h"

qboolean G_NITMOD_CanVoteSurrender(const gentity_t *ent) {
    team_t team = level.voteInfo.surrenderTeam;
    return ent && ent->client && (team == TEAM_AXIS || team == TEAM_ALLIES) &&
        ent->client->sess.sessionTeam == team;
}

int G_NITMOD_SurrenderVoters(void) {
    team_t team = level.voteInfo.surrenderTeam;
    int count;
    if(team != TEAM_AXIS && team != TEAM_ALLIES) return 0;
    count = level.voteInfo.numVotingTeamClients[team == TEAM_AXIS ? 0 : 1];
    return count < 0 ? 0 : count > MAX_CLIENTS ? MAX_CLIENTS : count;
}

/* Original G_Surrender_v: a playing team's vote declares its opponent the
 * winner and goes through normal LogExit. Private Nitmod winner key 'w'
 * becomes the typed ET configstring's 'winner', consumed by our cgame. */
int G_NITMOD_SurrenderVote(gentity_t *ent, unsigned int index, char *arg,
    char *arg2, qboolean referee) {
    team_t team;
    char info[MAX_INFO_STRING];
    (void)index; (void)referee;
    if(arg) {
        if(!ent || !ent->client || !arg2 || !vote_allow_surrender.integer ||
           g_gamestate.integer != GS_PLAYING) return G_INVALID;
        team = ent->client->sess.sessionTeam;
        if(team != TEAM_AXIS && team != TEAM_ALLIES) return G_INVALID;
        Q_strncpyz(arg2, team == TEAM_AXIS ? "[AXIS]" : "[ALLIES]", VOTE_MAXSTRING);
        level.voteInfo.surrenderTeam = team;
        return G_OK;
    }
    if(g_gamestate.integer != GS_PLAYING) return G_OK;
    team = level.voteInfo.surrenderTeam;
    if(team != TEAM_AXIS && team != TEAM_ALLIES) return G_INVALID;
    trap_GetConfigstring(CS_MULTI_MAPWINNER, info, sizeof(info));
    Info_SetValueForKey(info, "winner", team == TEAM_AXIS ? "1" : "0");
    trap_SetConfigstring(CS_MULTI_MAPWINNER, info);
    LogExit(team == TEAM_AXIS ? "Axis Surrender\n" : "Allies Surrender\n");
    trap_SendServerCommand(-1, team == TEAM_AXIS ?
        "chat \"^1AXIS^7 have surrendered!\" -2" : "chat \"^4ALLIES^7 have surrendered!\" -2");
    return G_OK;
}
