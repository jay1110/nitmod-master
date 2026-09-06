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

qboolean UI_NitmodTeamSelection(int *selection) {
	float value;
	if(!selection || uiInfo.myTeamCount < 0 || uiInfo.myTeamCount > MAX_CLIENTS) return qfalse;
	value = trap_Cvar_VariableValue("cg_selectedPlayer");
	/* count denotes the whole team. Compare before the WASM integer cast. */
	if(!(value >= 0 && value < uiInfo.myTeamCount + 1)) return qfalse;
	*selection = (int)value;
	return qtrue;
}

/* These identifiers are emitted unquoted by the original menu actions.
 * Preserve valid commands, but never interpret metadata as console syntax. */
static qboolean UI_ActionMapToken(const char *text) {
	int i;
	if(!UI_ActionText(text, MAX_QPATH)) return qfalse;
	for(i = 0; text[i]; ++i) if((unsigned char)text[i] <= 32) return qfalse;
	return qtrue;
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
	if(!Q_stricmp(name, "setupCampaign") || !Q_stricmp(name, "playCampaign")) {
		campaignInfo_t *campaign;
		float selected;
		int map, index = ui_currentCampaign.integer;
		if(uiInfo.campaignCount <= 0 || uiInfo.campaignCount > MAX_CAMPAIGNS ||
			index < 0 || index >= uiInfo.campaignCount) return qtrue;
		campaign = &uiInfo.campaignList[index];
		if(campaign->mapCount <= 0 || campaign->mapCount > MAX_MAPS_PER_CAMPAIGN ||
			campaign->progress < 0 || campaign->progress > MAX_MAPS_PER_CAMPAIGN) return qtrue;
		if(!Q_stricmp(name, "setupCampaign")) {
			trap_Cvar_Set("ui_campaignmap", va("%i", campaign->progress));
			return qtrue;
		}
		selected = trap_Cvar_VariableValue("ui_campaignmap");
		if(!(selected >= 0 && selected < campaign->mapCount)) return qtrue;
		map = (int)selected;
		if(map > campaign->progress || !campaign->mapInfos[map] ||
			!UI_ActionMapToken(campaign->mapInfos[map]->mapLoadName)) return qtrue;
		Com_sprintf(command, sizeof(command), "spmap \"%s\"\n", campaign->mapInfos[map]->mapLoadName);
		trap_Cmd_ExecuteText(EXEC_APPEND, command);
		return qtrue;
	}
	if(!Q_stricmp(name, "voteMap") || !Q_stricmp(name, "refMap")) {
		int game, index = ui_currentNetMap.integer;
		const char *verb = !Q_stricmp(name, "voteMap") ? "callvote" : "ref";
		if(!UI_SelectedNetGameType(&game)) return qtrue;
		if(game == GT_WOLF_CAMPAIGN) {
			if(index >= 0 && index < uiInfo.campaignCount &&
				index < (int)(sizeof(uiInfo.campaignList) / sizeof(uiInfo.campaignList[0])) &&
				UI_ActionMapToken(uiInfo.campaignList[index].campaignShortName))
				Com_sprintf(command, sizeof(command), "%s campaign %s\n", verb,
					uiInfo.campaignList[index].campaignShortName);
			else return qtrue;
		} else {
			if(index >= 0 && index < uiInfo.mapCount &&
				index < (int)(sizeof(uiInfo.mapList) / sizeof(uiInfo.mapList[0])) &&
				UI_ActionMapToken(uiInfo.mapList[index].mapLoadName))
				Com_sprintf(command, sizeof(command), "%s map %s\n", verb,
					uiInfo.mapList[index].mapLoadName);
			else return qtrue;
		}
		trap_Cmd_ExecuteText(EXEC_APPEND, command);
		return qtrue;
	}
	if(!Q_stricmp(name, "rconMap")) {
		int index = ui_currentNetMap.integer;
		if(index >= 0 && index < uiInfo.mapCount &&
			index < (int)(sizeof(uiInfo.mapList) / sizeof(uiInfo.mapList[0])) &&
			UI_ActionMapToken(uiInfo.mapList[index].mapLoadName)) {
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
		int toggles = CS_SERVERTOGGLES;
		/* UI_RunMenuScript ELF 0x2362b reads original slot 29.
		 * Match cgame's layout detection; reconstructed servers advertise
		 * nitmod_csLayout=et260 and retain the ET 2.60 slot. */
		trap_GetConfigString(CS_SERVERINFO, info, sizeof(info));
		if(!Q_stricmp(Info_ValueForKey(info, "gamename"), "nitmod") &&
			Q_stricmp(Info_ValueForKey(info, "nitmod_csLayout"), "et260")) toggles = 29;
		trap_GetConfigString(toggles, info, sizeof(info));
		trap_Cvar_Set("ui_voteWarmupDamage", va("%d", (atoi(info) & CV_SVS_WARMUPDMG) >> 2));
		trap_GetConfigString(CS_SERVERINFO, info, sizeof(info));
		trap_Cvar_Set("ui_voteTimelimit", va("%i", atoi(Info_ValueForKey(info, "timelimit"))));
		trap_Cvar_Set("ui_poll", "");
		return qtrue;
	}
	if(!Q_stricmp(name, "clientCheckVote")) {
		float raw = trap_Cvar_VariableValue("cg_ui_voteFlags");
		int flags;
		/* Keep the existing menu state for non-finite/out-of-range input.
		 * Compare in double: float(INT_MAX) rounds up to 2147483648. */
		if(!((double)raw >= INT_MIN && (double)raw <= INT_MAX)) return qtrue;
		flags = (int)raw;
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
