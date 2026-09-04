#include "ui_local.h"

/* Original UI_RunMenuScript (ELF 0x210d0). Command strings and quoted
 * player names are preserved; malformed selections/text never reach exec. */
static qboolean UI_ActionText(const char *text, int capacity) {
	int i;
	if(!text || !text[0]) return qfalse;
	for(i = 0; i < capacity; ++i) {
		unsigned char c = (unsigned char)text[i];
		if(!c) return qtrue;
		if(c < 32 || c == 127 || c == '"' || c == ';' || c == '\\') return qfalse;
	}
	return qfalse;
}
qboolean UI_NitmodPlayerSelectionValid(void) {
	return uiInfo.playerCount > 0 && uiInfo.playerCount <= MAX_CLIENTS &&
		uiInfo.playerIndex >= 0 && uiInfo.playerIndex < uiInfo.playerCount;
}

qboolean UI_NitmodMenuAction(const char *name) {
	static const struct { const char *name, *command; } players[] = {
	{ "voteKick", "callvote kick" },
	{ "voteMute", "callvote mute" },
	{ "voteUnMute", "callvote unmute" },
	{ "voteReferee", "callvote referee" },
	{ "voteUnReferee", "callvote unreferee" },
	{ "rconKick", "rcon kick" },
	{ "refKick", "ref kick" },
	{ "rconBan", "rcon ban" },
	{ "refMute", "ref mute" },
	{ "refUnMute", "ref unmute" },
	{ "refMakeAxis", "ref putaxis" },
	{ "refMakeAllied", "ref putallies" },
	{ "refMakeSpec", "ref remove" },
	{ "refUnReferee", "ref unreferee" },
	{ "refMakeReferee", "ref referee" },
	{ "rconMakeReferee", "rcon makeReferee" },
	{ "rconRemoveReferee", "rcon removeReferee" },
	{ "rconMute", "rcon mute" },
	{ "rconUnMute", "rcon unmute" },
	{ "ignorePlayer", "ignore" },
	{ "unIgnorePlayer", "unignore" },
	};
	char value[256], command[512];
	const char *player;
	int i;
	if(!name) return qfalse;
	for(i = 0; i < (int)(sizeof(players) / sizeof(players[0])); ++i) {
		if(Q_stricmp(name, players[i].name)) continue;
		if(!UI_NitmodPlayerSelectionValid()) return qtrue;
		player = uiInfo.playerNames[uiInfo.playerIndex];
		if(!UI_ActionText(player, sizeof(uiInfo.playerNames[0]))) return qtrue;
		Com_sprintf(command, sizeof(command), "%s \"%s\"\n", players[i].command, player);
		trap_Cmd_ExecuteText(EXEC_APPEND, command);
		return qtrue;
	}
	if(!Q_stricmp(name, "votePoll")) {
		/* Original 0x23119 retains the player-list selection guard even
		 * though the poll itself does not interpolate a player name. */
		if(!UI_NitmodPlayerSelectionValid()) return qtrue;
		trap_Cvar_VariableStringBuffer("ui_poll", value, sizeof(value));
		if(!UI_ActionText(value, sizeof(value))) return qtrue;
		Com_sprintf(command, sizeof(command), "callvote poll \"%s\"\n", value);
	} else if(!Q_stricmp(name, "refWarning")) {
		if(!UI_NitmodPlayerSelectionValid()) return qtrue;
		player = uiInfo.playerNames[uiInfo.playerIndex];
		if(!UI_ActionText(player, sizeof(uiInfo.playerNames[0]))) return qtrue;
		trap_Cvar_VariableStringBuffer("ui_warnreason", value, 128);
		if(!UI_ActionText(value, 128)) return qtrue;
		Com_sprintf(command, sizeof(command), "ref warn \"%s\" \"%s\"\n", player, value);
	} else if(!Q_stricmp(name, "refWarmup")) {
		trap_Cvar_VariableStringBuffer("ui_warmup", value, 128);
		if(!UI_ActionText(value, 128)) return qtrue;
		Com_sprintf(command, sizeof(command), "ref warmup \"%s\"\n", value);
	} else return qfalse;
	trap_Cmd_ExecuteText(EXEC_APPEND, command);
	return qtrue;
}
