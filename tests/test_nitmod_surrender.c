#include "g_local.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

level_locals_t level;
vmCvar_t g_gamestate, vote_allow_surrender;
static int stage;
static const char *expectedWinner, *expectedReason, *expectedChat;
void Q_strncpyz(char *out, const char *text, int size) {
    if(size < 1) exit(2); strncpy(out, text, size - 1); out[size - 1] = 0;
}
void trap_GetConfigstring(int index, char *out, int size) {
    if(stage++ != 0 || index != CS_MULTI_MAPWINNER) exit(2);
    Q_strncpyz(out, "\\other\\kept\\winner\\-1", size);
}
void Info_SetValueForKey(char *info, const char *key, const char *value) {
    if(stage++ != 1 || strcmp(key, "winner") || strcmp(value, expectedWinner) ||
       strcmp(info, "\\other\\kept\\winner\\-1")) exit(2);
    sprintf(info, "\\other\\kept\\winner\\%s", value);
}
void trap_SetConfigstring(int index, const char *value) {
    char expected[64]; sprintf(expected, "\\other\\kept\\winner\\%s", expectedWinner);
    if(stage++ != 2 || index != CS_MULTI_MAPWINNER || strcmp(value, expected)) exit(2);
}
void LogExit(const char *reason) { if(stage++ != 3 || strcmp(reason, expectedReason)) exit(2); }
void trap_SendServerCommand(int client, const char *text) {
    if(stage++ != 4 || client != -1 || strcmp(text, expectedChat)) exit(2);
}
int main(void) {
    static gclient_t client;
    gentity_t entity;
    int state, team, allowed, referee, voter, count, errors = 0;
    char arg[] = "surrender", value[VOTE_MAXSTRING];
    memset(&entity, 0, sizeof(entity)); entity.client = &client;
    for(state = -1; state <= 5; ++state) for(team = 0; team < TEAM_NUM_TEAMS; ++team)
    for(allowed = 0; allowed < 2; ++allowed) for(referee = 0; referee < 2; ++referee) {
        int valid = state == GS_PLAYING && allowed && (team == TEAM_AXIS || team == TEAM_ALLIES);
        g_gamestate.integer = state; vote_allow_surrender.integer = allowed;
        client.sess.sessionTeam = team; level.voteInfo.surrenderTeam = TEAM_FREE;
        strcpy(value, "unchanged"); stage = 0;
        if(G_NITMOD_SurrenderVote(&entity, 0, arg, value, referee) != (valid ? G_OK : G_INVALID) || stage) ++errors;
        if(valid) {
            if(level.voteInfo.surrenderTeam != team || strcmp(value, team == TEAM_AXIS ? "[AXIS]" : "[ALLIES]")) ++errors;
        } else if(level.voteInfo.surrenderTeam != TEAM_FREE || strcmp(value, "unchanged")) ++errors;
    }
    vote_allow_surrender.integer = 1; g_gamestate.integer = GS_PLAYING;
    if(G_NITMOD_SurrenderVote(NULL, 0, arg, value, qfalse) != G_INVALID) ++errors;
    for(team = 0; team < TEAM_NUM_TEAMS; ++team) {
        level.voteInfo.surrenderTeam = team;
        for(voter = 0; voter < TEAM_NUM_TEAMS; ++voter) {
            client.sess.sessionTeam = voter;
            if(G_NITMOD_CanVoteSurrender(&entity) !=
               ((team == TEAM_AXIS || team == TEAM_ALLIES) && voter == team)) ++errors;
        }
        if(G_NITMOD_CanVoteSurrender(NULL)) ++errors;
        for(count = -1; count <= MAX_CLIENTS + 1; ++count) {
            level.voteInfo.numVotingTeamClients[0] = count;
            level.voteInfo.numVotingTeamClients[1] = MAX_CLIENTS;
            if(G_NITMOD_SurrenderVoters() != (team == TEAM_AXIS ?
                (count < 0 ? 0 : count > MAX_CLIENTS ? MAX_CLIENTS : count) :
                team == TEAM_ALLIES ? MAX_CLIENTS : 0)) ++errors;
        }
        for(state = -1; state <= 5; ++state) {
            int validTeam = team == TEAM_AXIS || team == TEAM_ALLIES;
            g_gamestate.integer = state; stage = 0;
            expectedWinner = team == TEAM_AXIS ? "1" : "0";
            expectedReason = team == TEAM_AXIS ? "Axis Surrender\n" : "Allies Surrender\n";
            expectedChat = team == TEAM_AXIS ? "chat \"^1AXIS^7 have surrendered!\" -2" :
                "chat \"^4ALLIES^7 have surrendered!\" -2";
            if(G_NITMOD_SurrenderVote(NULL, 0, NULL, NULL, qfalse) !=
               (state == GS_PLAYING && !validTeam ? G_INVALID : G_OK) ||
               stage != (state == GS_PLAYING && validTeam ? 5 : 0)) ++errors;
        }
    }
    printf("Surrender request, electorate, winner and lifecycle: %d errors\n", errors);
    return errors != 0;
}
