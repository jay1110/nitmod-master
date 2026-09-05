#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_hud.h"
#include "cg_nitmod_stats.h"

typedef struct {
	qboolean visible;
	qboolean received;
	qboolean failed;
	qboolean requested;
	int player;
	int opened;
	int transition;
	double deadline;
	int lastUpdate;
	int values[NITMOD_GLOBAL_STAT_COUNT];
} nitmodGlobalStatsState_t;

static nitmodGlobalStatsState_t globalStats;
static const char *const globalStatNames[13] = {
	"Kills", "Deaths", "Team", "Time", "Revives", "Tripmine", "Goomba",
	"Scoped", "Fthrower", "Objs.", "Objs.", "Rounds", "Satchel"
};
static const char *const globalStatNames2[13] = {
	"", "", "kills", "played", "", "kills", "kills", "HS", "kills",
	"const.", "dest.", "played", "kills"
};
static const int globalStatPositions[13] = {
	0, 44, 88, 132, 176, 220, 264, 308, 352, 396, 440, 484, 528
};
typedef struct { const char *title, *description; } nitmodGlobalAward_t;
static const nitmodGlobalAward_t globalAwards[] = {
	{"THE BEGINNING", "Made his first kill!"},
	{"100 KILLS!", ""},
	{"NEED A MEDIC?", "Made his first revive!"},
	{"WATCH YOUR STEP!", "First Tripmine Kill"},
	{"FAT ASS!", "First Goomba Kill"},
	{"BOOM HEADSHOT!", "First scoped headshot"},
	{"ROASTER!", "First Flamethrower kill"},
	{"I'M AN ENGINEER!", "Constructed his first objective"},
	{"DESTROYER", "Destroyed his first objective"},
	{"REMOTE KILLER", "First satchel kill"},
	{"BUTCHER", "100 Backstabs"}
};
static int awardClient = -1, awardIndex = -1;
static qboolean awardLogged;

void CG_NitmodGlobalAwardClear(void) {
	if(awardIndex >= 0) CG_NitmodNotificationStart("", 0);
	awardClient = awardIndex = -1;
	awardLogged = qfalse;
}

qboolean CG_NitmodGlobalAwardActive(void) { return awardIndex >= 0; }

float CG_NitmodGlobalAwardAlpha(int now, float hold, float fade) {
	float alpha;
	if(!CG_NitmodGlobalAwardActive()) return 0;
	alpha = CG_NitmodNotificationAlpha(now, hold, fade);
	/* Zero fade pauses the original notification; do not discard the award. */
	if(alpha <= 0 && !CG_NitmodNotificationActive()) CG_NitmodGlobalAwardClear();
	return alpha;
}

const char *CG_NitmodGlobalAwardTitle(int award) {
	return award >= 0 && award < (int)(sizeof(globalAwards) / sizeof(globalAwards[0]))
		? globalAwards[award].title : NULL;
}
const char *CG_NitmodGlobalAwardDescription(int award) {
	return award >= 0 && award < (int)(sizeof(globalAwards) / sizeof(globalAwards[0]))
		? globalAwards[award].description : NULL;
}

void CG_NitmodGlobalStatsReset(void) {
	memset(&globalStats, 0, sizeof(globalStats));
	globalStats.player = -1;
	CG_NitmodGlobalAwardClear();
}

qboolean CG_NitmodGlobalAwardCommand(void) {
	int client, award;
	if(trap_Argc() != 3 || !NITMOD_ParseProtocolInteger(CG_Argv(1), &client) ||
	   !NITMOD_ParseProtocolInteger(CG_Argv(2), &award) || client < 0 ||
	   client >= MAX_CLIENTS || !CG_NitmodGlobalAwardTitle(award)) return qtrue;
	awardClient = client;
	awardIndex = award;
	awardLogged = qfalse;
	CG_NitmodNotificationStart(CG_NitmodGlobalAwardTitle(award), cg.time);
	return qtrue;
}

void CG_NitmodDrawGlobalAward(void) {
	vec4_t background = {0, 0, .5f, .5f}, border = {1, 1, 1, 1};
	float hold = cg_notificationTime.value, fade = cg_notificationFadeTime.value;
	float alpha, width, height, x;
	const char *title, *description, *name;
	nitmodHudAnchor_t previous;
	alpha = CG_NitmodGlobalAwardAlpha(cg.time, hold, fade);
	if(alpha <= 0) return;
	if(awardClient < 0 || awardClient >= MAX_CLIENTS || !cgs.clientinfo[awardClient].infoValid) return;
	title = CG_NitmodGlobalAwardTitle(awardIndex);
	description = CG_NitmodGlobalAwardDescription(awardIndex);
	if(!title) return;
	name = cgs.clientinfo[awardClient].name;
	/* Original panel width and baseline offset derive from the description. */
	width = CG_Text_Width_Ext(description, .2f, 0, &cgs.media.limboFont2);
	height = CG_Text_Height_Ext(description, .2f, 0, &cgs.media.limboFont2) * .5f;
	width += 20; x = 639 - width * alpha;
	background[3] *= alpha; border[3] = alpha;
	previous = CG_NitmodHudAnchor(NITMOD_HUD_RIGHT);
	CG_FillRect(x, 0, width, 50, background);
	CG_DrawRect_FixedBorder(x, 0, width, 50, 1, border);
	CG_Text_Paint_Centred_Ext(x + width * .5f, 12.5f + height, .2f, .2f, border, name, 0, 0, 7, &cgs.media.limboFont2);
	CG_Text_Paint_Centred_Ext(x + width * .5f, 25 + height, .2f, .2f, border, title, 0, 0, 7, &cgs.media.limboFont2);
	CG_Text_Paint_Centred_Ext(x + width * .5f, 37.5f + height, .2f, .2f, border, description, 0, 0, 7, &cgs.media.limboFont2);
	CG_NitmodHudAnchor(previous);
	if(!awardLogged) {
		CG_Printf("^7N^1!^7tmod ^5Global Awards ^g[^7%s^g] ^3%s ^7- ^8%s^7\n",
			name, title, description);
		awardLogged = qtrue;
	}
}

qboolean CG_NitmodParseGlobalStats(int argc, const char *(*argv)(int),
	int values[NITMOD_GLOBAL_STAT_COUNT], qboolean *failed) {
	int next[NITMOD_GLOBAL_STAT_COUNT], i;
	if(!argv || !values || !failed || argc < 3) return qfalse;
	if(!strcmp(argv(2), "-")) {
		*failed = qtrue;
		return qtrue;
	}
	if(argc != NITMOD_GLOBAL_STAT_COUNT + 2) return qfalse;
	for(i = 0; i < NITMOD_GLOBAL_STAT_COUNT; ++i)
		if(!NITMOD_ParseProtocolSigned(argv(i + 2), &next[i])) return qfalse;
	memcpy(values, next, sizeof(next));
	*failed = qfalse;
	return qtrue;
}

void CG_NitmodGlobalStats_f(void) {
	if(!NITMOD_UsesOriginalProtocol() || !cg.snap || cg.demoPlayback) {
		globalStats.visible = qfalse;
		return;
	}
	if(globalStats.visible) {
		if(globalStats.transition != 2) {
			globalStats.transition = 2;
			if((double)cg.time - globalStats.opened > 450 || cg.time < globalStats.opened)
				globalStats.opened = cg.time;
		}
		return;
	}
	globalStats.visible = qtrue;
	globalStats.opened = cg.time;
	globalStats.transition = 1;
}

qboolean CG_NitmodGlobalStatsCommand(void) {
	qboolean failed = qfalse;
	int values[NITMOD_GLOBAL_STAT_COUNT];
	if(!CG_NitmodParseGlobalStats(trap_Argc(), CG_Argv, values, &failed)) return qtrue;
	if(!globalStats.visible) return qtrue;
	globalStats.failed = failed;
	globalStats.received = qtrue;
	globalStats.requested = qfalse;
	if(failed) globalStats.deadline = (double)cg.time + 5000;
	if(!failed) memcpy(globalStats.values, values, sizeof(values));
	return qtrue;
}

static void CG_NitmodStatsColumn(float x, float y, float scale, const vec4_t color, const char *text) {
	/* Original measures at .18 but paints at .19; the animated centering
	 * additionally multiplies the measured width by the panel scale. */
	float width = CG_Text_Width_Ext(text, .18f * scale, 0, &cgs.media.limboFont2);
	CG_Text_Paint_Ext(x - width * .5f * scale, y, .19f * scale, .19f * scale,
		color, text, 0, 0, 7, &cgs.media.limboFont2);
}

qboolean CG_NitmodDrawGlobalStats(void) {
	vec4_t panel = {0, 0, 0, .8f}, border = {1, 1, 1, 1};
	char text[128];
	float x = 20, y = 240, width = 600, height = 120, scale = 1;
	double elapsed;
	int i;
	nitmodHudAnchor_t previous;
	/* Original globalstats command is disabled during demo playback.
	 * Also close an already-open window when playback starts. */
	if(cg.demoPlayback) { globalStats.visible = qfalse; return qfalse; }
	if(!globalStats.visible || !cg.snap || cg.snap->ps.clientNum < 0 ||
	   cg.snap->ps.clientNum >= MAX_CLIENTS) return qfalse;
	if(globalStats.player != cg.snap->ps.clientNum || cg.time < globalStats.lastUpdate ||
	   (double)cg.time > globalStats.deadline) {
		globalStats.player = cg.snap->ps.clientNum;
		globalStats.received = globalStats.requested = globalStats.failed = qfalse;
	}
	globalStats.lastUpdate = cg.time;
	elapsed = (double)cg.time - globalStats.opened;
	if(elapsed < 0) elapsed = 0;
	if(globalStats.transition == 1) {
		scale = (float)(elapsed / 250.0);
		if(scale >= 1) { scale = 1; globalStats.transition = 0; }
		panel[3] = scale < .8f ? scale : .8f;
		width = scale * 600; height = scale * 120;
		x = 320 - width * .5f; y = 300 - height * .5f;
	} else if(globalStats.transition == 2) {
		scale = .8f - (float)(elapsed / 250.0);
		if(scale <= 0) {
			globalStats.visible = qfalse;
			globalStats.transition = 0;
			globalStats.opened = 0;
			return qfalse;
		}
		panel[3] = scale; border[3] = scale;
		width = scale * 600; height = scale * 120;
		x = 320 - width * .5f; y = 300 - height * .5f;
	}
	if(!globalStats.requested && !globalStats.received) {
		trap_SendClientCommand(va("ggs %i", globalStats.player));
		globalStats.requested = qtrue;
		globalStats.deadline = (double)cg.time + 15000;
	}
	previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
	CG_FillRect(x, y, width, height, panel);
	CG_DrawRect_FixedBorder(x, y, width, height, 1, border);
	CG_Text_Paint_Centred_Ext(320, y + 20 * scale, .22f * scale, .22f * scale, border,
		"^7N^1!^7tmod ^5Global Player Stats^7", 0, 0, 3, &cgs.media.limboFont1);
	Com_sprintf(text, sizeof(text), "Displaying stats for player ^7%s^7",
		cgs.clientinfo[globalStats.player].name);
	CG_Text_Paint_Centred_Ext(320, y + 30 * scale, .21f * scale, .21f * scale, border,
		text, 0, 0, 3, &cgs.media.limboFont1);
	if(globalStats.failed) {
		CG_Text_Paint_Centred_Ext(320, y + 60 * scale, .19f * scale, .19f * scale, border,
			"^1ERROR: ^7Unable to retrieve stats!^7", 0, 0, 3, &cgs.media.limboFont1);
		CG_Text_Paint_Centred_Ext(320, y + 70 * scale, .19f * scale, .19f * scale, border,
			"Contact admin@etmods.net if problem persists.^7", 0, 0, 3, &cgs.media.limboFont1);
	} else if(!globalStats.received) {
		CG_Text_Paint_Centred_Ext(320, y + 65 * scale, .2f * scale, .2f * scale, border,
			"^7Please wait while updating your stats...^7", 0, 0, 3, &cgs.media.limboFont1);
	} else {
		/* ELF tables at 0x133e60/0x133f00/0x133f40 describe 13 visible
		 * columns. All 15 wire values remain retained; the last two are not
		 * rendered because the original table has no labels or positions. */
		for(i = 0; i < 13; ++i) {
			float column = x + (30 + globalStatPositions[i]) * scale;
			CG_NitmodStatsColumn(column, y + (globalStatNames2[i][0] ? 50 : 55) * scale,
				scale, border, globalStatNames[i]);
			if(globalStatNames2[i][0])
				CG_NitmodStatsColumn(column, y + 60 * scale, scale, border, globalStatNames2[i]);
			Com_sprintf(text, sizeof(text), "%d", globalStats.values[i]);
			CG_NitmodStatsColumn(column, y + 80 * scale, scale, border, text);
		}
		Com_sprintf(text, sizeof(text), "^7Stats will be updated in %i seconds.^7",
			(int)((globalStats.deadline - cg.time) / 1000) + 1);
		CG_Text_Paint_Centred_Ext(320, y + height - 15 * scale, .2f * scale,
			.2f * scale, border, text, 0, 0, 7, &cgs.media.limboFont1);
	}
	CG_Text_Paint_Centred_Ext(320, y + height - 5 * scale, .2f * scale,
		.2f * scale, border,
		"^7Use globalstats again to close.^7", 0, 0, 3, &cgs.media.limboFont1);
	CG_NitmodHudAnchor(previous);
	return qtrue;
}
