#include "ui_local.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
uiInfo_t uiInfo;
vmCvar_t ui_currentNetMap;
vmCvar_t ui_currentCampaign;
static float campaignMap;
static int campaignWrites;
static int game = GT_WOLF, sent;
static const char *expected;
qboolean UI_SelectedNetGameType(int *out) { *out = game; return qtrue; }
qboolean UI_GameTypeForCatalogRow(int row, int *out) { return qfalse; }
void trap_Cmd_ExecuteText(int when, const char *text) {
    assert(when == EXEC_APPEND && expected && !strcmp(text, expected)); ++sent;
}
float trap_Cvar_VariableValue(const char *name) { assert(!strcmp(name, "ui_campaignmap") || !strcmp(name, "cg_selectedPlayer")); return campaignMap; }
void trap_Cvar_VariableStringBuffer(const char *name, char *out, int size) { abort(); }
void trap_Cvar_Set(const char *name, const char *value) {
    assert(!strcmp(name, "ui_campaignmap") && !strcmp(value, "0")); ++campaignWrites;
}
void trap_Cvar_SetValue(const char *name, float value) { abort(); }
int trap_GetConfigString(int index, char *out, int size) { abort(); }
void QDECL Com_Error(int level, const char *format, ...) { abort(); }
void QDECL Com_Printf(const char *format, ...) { abort(); }
#undef vsnprintf
int Q_vsnprintf(char *out, int size, const char *format, va_list args) {
    return vsnprintf(out, size, format, args);
}
static void check(const char *action, const char *command) {
    sent = 0; expected = command;
    assert(UI_NitmodMenuAction(action));
    assert(sent == (command != NULL));
}
int main(void) {
    static const struct { const char *action, *command; } players[] = {
        {"voteKick", "callvote kick"}, {"voteMute", "callvote mute"},
        {"voteUnMute", "callvote unmute"}, {"voteReferee", "callvote referee"},
        {"voteUnReferee", "callvote unreferee"}, {"rconKick", "rcon kick"},
        {"refKick", "ref kick"}, {"rconBan", "rcon ban"},
        {"refMute", "ref mute"}, {"refUnMute", "ref unmute"},
        {"refMakeAxis", "ref putaxis"}, {"refMakeAllied", "ref putallies"},
        {"refMakeSpec", "ref remove"}, {"refUnReferee", "ref unreferee"},
        {"refMakeReferee", "ref referee"}, {"rconMakeReferee", "rcon makeReferee"},
        {"rconRemoveReferee", "rcon removeReferee"}, {"rconMute", "rcon mute"},
        {"rconUnMute", "rcon unmute"}, {"ignorePlayer", "ignore"},
        {"unIgnorePlayer", "unignore"}
    };
    static const char *bad[] = {"", "oasis;quit", "two maps", "oasis\nquit", "\"oasis\"", "bad\\map"};
    int i, j;
    char command[256];
    for(i = 0; i < sizeof(players)/sizeof(players[0]); ++i) {
        uiInfo.playerCount = 2; uiInfo.playerIndex = 1;
        strcpy(uiInfo.playerNames[0], "Wrong player");
        strcpy(uiInfo.playerNames[1], "^1Selected Player");
        sprintf(command, "%s \"^1Selected Player\"\n", players[i].command);
        check(players[i].action, command);
        uiInfo.playerIndex = -1; check(players[i].action, NULL);
        uiInfo.playerIndex = 2; check(players[i].action, NULL);
        uiInfo.playerIndex = 1;
        uiInfo.playerCount = MAX_CLIENTS + 1; check(players[i].action, NULL);
        uiInfo.playerCount = 2;
        for(j = 0; j < sizeof(bad)/sizeof(bad[0]); ++j) {
            /* Spaces are valid inside quoted player names, unlike map tokens. */
            if(j == 2) continue;
            strcpy(uiInfo.playerNames[1], bad[j]);
            check(players[i].action, NULL);
        }
        memset(uiInfo.playerNames[1], 'x', sizeof(uiInfo.playerNames[1]));
        check(players[i].action, NULL);
    }
    assert(!UI_NitmodMenuAction(NULL));
    assert(!UI_NitmodMenuAction("unknown-action"));
    uiInfo.mapCount = uiInfo.campaignCount = 1;
    uiInfo.mapList[0].mapLoadName = "oasis";
    uiInfo.campaignList[0].campaignShortName = "cmp_test";
    check("voteMap", "callvote map oasis\n");
    check("refMap", "ref map oasis\n");
    check("rconMap", "rcon map oasis\n");
    game = GT_WOLF_CAMPAIGN;
    check("voteMap", "callvote campaign cmp_test\n");
    check("refMap", "ref campaign cmp_test\n");
    for(i = 0; i < sizeof(bad)/sizeof(bad[0]); ++i) {
        uiInfo.campaignList[0].campaignShortName = bad[i];
        check("voteMap", NULL); check("refMap", NULL);
        game = GT_WOLF;
        uiInfo.mapList[0].mapLoadName = bad[i];
        check("voteMap", NULL); check("refMap", NULL); check("rconMap", NULL);
        game = GT_WOLF_CAMPAIGN;
    }
    uiInfo.mapCount = uiInfo.campaignCount = INT_MAX;
    ui_currentNetMap.integer = INT_MAX - 1;
    check("voteMap", NULL); check("refMap", NULL); check("rconMap", NULL);
    game = GT_WOLF;
    check("voteMap", NULL); check("refMap", NULL);
    ui_currentNetMap.integer = -1;
    check("voteMap", NULL); check("refMap", NULL); check("rconMap", NULL);
    uiInfo.campaignCount = 1;
    uiInfo.campaignList[0].mapCount = 2;
    uiInfo.campaignList[0].progress = 0;
    uiInfo.mapList[0].mapLoadName = "oasis";
    uiInfo.campaignList[0].mapInfos[0] = &uiInfo.mapList[0];
    uiInfo.campaignList[0].mapInfos[1] = &uiInfo.mapList[0];
    check("setupCampaign", NULL); assert(campaignWrites == 1);
    campaignMap = 0; check("playCampaign", "spmap \"oasis\"\n");
    campaignMap = 1; check("playCampaign", NULL);
    uiInfo.campaignList[0].progress = 1;
    check("playCampaign", "spmap \"oasis\"\n");
    campaignMap = -1; check("playCampaign", NULL);
    campaignMap = 2; check("playCampaign", NULL);
    campaignMap = 0; uiInfo.campaignList[0].mapInfos[0] = NULL;
    check("playCampaign", NULL);
    ui_currentCampaign.integer = MAX_CAMPAIGNS;
    check("setupCampaign", NULL); check("playCampaign", NULL);
    assert(campaignWrites == 1);
    for(i = 0; i <= MAX_CLIENTS; ++i) {
        int selected = -9;
        uiInfo.myTeamCount = i;
        campaignMap = i;
        assert(UI_NitmodTeamSelection(&selected) && selected == i);
        campaignMap = i + .5f;
        assert(UI_NitmodTeamSelection(&selected) && selected == i);
        campaignMap = i + 1;
        assert(!UI_NitmodTeamSelection(&selected));
        campaignMap = -1;
        assert(!UI_NitmodTeamSelection(&selected));
        campaignMap = NAN;
        assert(!UI_NitmodTeamSelection(&selected));
        campaignMap = INFINITY;
        assert(!UI_NitmodTeamSelection(&selected));
        assert(selected == i);
    }
    puts("WASM UI actions: player/map commands and campaign setup/play progression passed");
    return 0;
}
