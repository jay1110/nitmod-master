#include "ui_local.h"
#include <float.h>
#include <limits.h>

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

qboolean UI_NitmodRedirectAddress(const char *text, char *out, int size) {
	int length;
	if(!text || !out || size <= 1) return qfalse;
	if(!Q_stricmpn(text, "ET://", 5)) text += 5;
	for(length = 0; text[length]; ++length) {
		unsigned char c = text[length];
		if(length >= size - 1 || !((c >= 'a' && c <= 'z') ||
		   (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ||
		   c == '.' || c == '-' || c == ':' || c == '[' || c == ']')) return qfalse;
	}
	if(!length) return qfalse;
	memmove(out, text, length + 1); /* Also supports stripping the prefix in place. */
	return qtrue;
}

qboolean UI_NitmodFoundPlayerAddress(char *out, int size) {
	int row = uiInfo.currentFoundPlayerServer;
	if(uiInfo.numFoundPlayerServers < 2 || uiInfo.numFoundPlayerServers > MAX_FOUNDPLAYER_SERVERS ||
	   row < 0 || row >= uiInfo.numFoundPlayerServers - 1) return qfalse;
	return UI_NitmodRedirectAddress(uiInfo.foundPlayerServerAddresses[row], out,
		size < MAX_ADDRESSLENGTH ? size : MAX_ADDRESSLENGTH);
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
	if(!Q_stricmp(name, "voteMap") || !Q_stricmp(name, "refMap")) {
		int game, index = ui_currentNetMap.integer;
		const char *verb = !Q_stricmp(name, "voteMap") ? "callvote" : "ref";
		if(!UI_SelectedNetGameType(&game)) return qtrue;
		if(game == GT_WOLF_CAMPAIGN) {
			if(index >= 0 && index < uiInfo.campaignCount)
				Com_sprintf(command, sizeof(command), "%s campaign %s\n", verb,
					uiInfo.campaignList[index].campaignShortName);
			else return qtrue;
		} else {
			if(index >= 0 && index < uiInfo.mapCount)
				Com_sprintf(command, sizeof(command), "%s map %s\n", verb,
					uiInfo.mapList[index].mapLoadName);
			else return qtrue;
		}
		trap_Cmd_ExecuteText(EXEC_APPEND, command);
		return qtrue;
	}
	if(!Q_stricmp(name, "rconMap")) {
		int index = ui_currentNetMap.integer;
		if(index >= 0 && index < uiInfo.mapCount) {
			Com_sprintf(command, sizeof(command), "rcon map %s\n", uiInfo.mapList[index].mapLoadName);
			trap_Cmd_ExecuteText(EXEC_APPEND, command);
		}
		return qtrue;
	}
	if(!Q_stricmp(name, "voteGame") || !Q_stricmp(name, "refGame")) {
		float raw = trap_Cvar_VariableValue("ui_voteGameType");
		int game;
		if((double)raw >= INT_MIN && (double)raw <= INT_MAX &&
			UI_GameTypeForCatalogRow((int)raw, &game) && game != GT_WOLF_CAMPAIGN) {
			Com_sprintf(command, sizeof(command), "%s gametype %i\n",
				!Q_stricmp(name, "voteGame") ? "callvote" : "ref", game);
			trap_Cmd_ExecuteText(EXEC_APPEND, command);
		}
		return qtrue;
	}
	if(!Q_stricmp(name, "rconGame")) {
		int game;
		if(UI_SelectedNetGameType(&game)) {
			Com_sprintf(command, sizeof(command), "rcon g_gametype %i\n", game);
			trap_Cmd_ExecuteText(EXEC_APPEND, command);
		}
		return qtrue;
	}
	if(!Q_stricmp(name, "voteTimelimit") || !Q_stricmp(name, "refTimelimit")) {
		float limit = trap_Cvar_VariableValue("ui_voteTimelimit");
		if(limit >= -FLT_MAX && limit <= FLT_MAX) {
			Com_sprintf(command, sizeof(command), "%s timelimit %f\n",
				!Q_stricmp(name, "voteTimelimit") ? "callvote" : "ref", limit);
			trap_Cmd_ExecuteText(EXEC_APPEND, command);
		}
		return qtrue;
	}
	if(!Q_stricmp(name, "voteWarmupDamage") || !Q_stricmp(name, "refWarmupDamage")) {
		float raw = trap_Cvar_VariableValue("ui_voteWarmupDamage");
		if((double)raw >= INT_MIN && (double)raw <= INT_MAX) {
			Com_sprintf(command, sizeof(command), "%s warmupdamage %d\n",
				!Q_stricmp(name, "voteWarmupDamage") ? "callvote" : "ref", (int)raw);
			trap_Cmd_ExecuteText(EXEC_APPEND, command);
		}
		return qtrue;
	}
	if(!Q_stricmp(name, "voteInitToggles")) {
		char info[MAX_INFO_STRING];
		trap_GetConfigString(CS_SERVERTOGGLES, info, sizeof(info));
		trap_Cvar_Set("ui_voteWarmupDamage", va("%d", (atoi(info) & CV_SVS_WARMUPDMG) >> 2));
		trap_GetConfigString(CS_SERVERINFO, info, sizeof(info));
		trap_Cvar_Set("ui_voteTimelimit", va("%i", atoi(Info_ValueForKey(info, "timelimit"))));
		trap_Cvar_Set("ui_poll", "");
		return qtrue;
	}
	if(!Q_stricmp(name, "clientCheckVote")) {
		int flags = (int)trap_Cvar_VariableValue("cg_ui_voteFlags");
		trap_Cvar_SetValue("cg_ui_novote",
			flags == VOTING_DISABLED || flags == ET_VOTING_DISABLED ? 1 : 0);
		return qtrue;
	}
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
