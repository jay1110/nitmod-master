#include "cg_local.h"
#include "cg_nitmod_hud.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_hints.h"
#include "cg_nitmod_names.h"
#include "cg_nitmod_stats.h"
#include <float.h>
#include <limits.h>

void CG_NitmodDrawSpectatorInstruction(int row, const char *text) {
    nitmodHudAnchor_t previous;
    if(row < 0 || row > 1 || !text || !NITMOD_UsesOriginalProtocol()) return;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_LEFT);
    CG_Text_Paint_Ext(8, 150 + row * 8, .2f, .2f, colorWhite, text, 0, 0, 7, &cgs.media.limboFont2);
    CG_NitmodHudAnchor(previous);
}

void CG_NitmodDrawWoundedInstruction(int row, const char *text) {
    nitmodHudAnchor_t previous;
    if(row < 0 || row > 2 || !text || !NITMOD_UsesOriginalProtocol()) return;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_LEFT);
    CG_Text_Paint_Ext(8, 118 + row * 12, .2f, .2f, colorWhite, text, 0, 0, 7, &cgs.media.limboFont2);
    CG_NitmodHudAnchor(previous);
}

static struct {
    char text[MAX_STRING_CHARS];
    double start;
    int y, charWidth, lines;
    qboolean active;
} nitmodAnnouncement;

static float CG_NitmodMessageAlpha(double start) {
    double duration = (double)cg_centertime.value * 1000;
    double remaining = duration - ((double)cg.time - start);
    if(!(duration > 0 && duration <= INT_MAX) || !(remaining > 0)) return 0;
    return remaining >= FADE_TIME ? 1 : (float)(remaining / FADE_TIME);
}

const char *CG_NitmodAnnouncementText(void) {
    if(nitmodAnnouncement.active && !CG_NitmodMessageAlpha(nitmodAnnouncement.start))
        nitmodAnnouncement.active = qfalse;
    return nitmodAnnouncement.active ? nitmodAnnouncement.text : "";
}

void CG_NitmodPrintAnnouncement(const char *text, int y, int charWidth, int priority) {
    int i;
    qboolean wrap = qfalse;
    if(!text || charWidth < 1 || charWidth > 64) return;
    CG_NitmodAnnouncementText();
    if(priority < 0 && nitmodAnnouncement.active) return;
    Q_strncpyz(nitmodAnnouncement.text, text, sizeof(nitmodAnnouncement.text));
    nitmodAnnouncement.lines = 1;
    for(i = 0; nitmodAnnouncement.text[i]; ++i) {
        if(i > 0 && i % 36 == 0) wrap = qtrue;
        if(wrap && nitmodAnnouncement.text[i] == ' ') { nitmodAnnouncement.text[i] = '\n'; wrap = qfalse; }
        if(nitmodAnnouncement.text[i] == '\n') ++nitmodAnnouncement.lines;
    }
    nitmodAnnouncement.y = y; nitmodAnnouncement.charWidth = charWidth;
    nitmodAnnouncement.start = (double)cg.time + 2000;
    nitmodAnnouncement.active = qtrue;
}

/* Two distinct original channels. Never let announce replace a centerprint. */
void CG_NitmodDrawAnnouncement(void) {
    const char *cursor = CG_NitmodAnnouncementText();
    char line[57];
    float y, x;
    int length;
    vec4_t color = {1, 1, 1, 1};
    nitmodHudAnchor_t previous;
    if(!NITMOD_UsesOriginalProtocol() || !*cursor) return;
    color[3] = CG_NitmodMessageAlpha(nitmodAnnouncement.start);
    y = nitmodAnnouncement.y - nitmodAnnouncement.lines * 8.f;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    do {
        for(length = 0; length < 56 && cursor[length] && cursor[length] != '\n'; ++length) line[length] = cursor[length];
        line[length] = 0;
        x = (640 - CG_DrawStrlen(line) * nitmodAnnouncement.charWidth) * .5f;
        CG_DrawStringExt((int)x, (int)y, line, color, qfalse, qtrue,
            nitmodAnnouncement.charWidth, (int)(nitmodAnnouncement.charWidth * 1.5f), 0);
        y += nitmodAnnouncement.charWidth * 1.5f;
        while(*cursor && *cursor != '\n') ++cursor;
        if(!*cursor) break;
        ++cursor;
    } while(1);
    trap_R_SetColor(NULL);
    CG_NitmodHudAnchor(previous);
}

void CG_NitmodDrawCenterPrint(void) {
    const char *cursor = cg.centerPrint;
    char line[57];
    int length;
    float y;
    vec4_t color = {1, 1, 1, 1};
    nitmodHudAnchor_t previous;
    if(!NITMOD_UsesOriginalProtocol() || !cg.centerPrintTime) return;
    color[3] = CG_NitmodMessageAlpha(cg.centerPrintTime);
    if(!color[3]) { cg.centerPrintTime = cg.centerPrintPriority = 0; return; }
    y = (float)((double)cg.centerPrintY - cg.centerPrintLines * 8.0);
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    do {
        for(length = 0; length < 56 && cursor[length] && cursor[length] != '\n'; ++length) line[length] = cursor[length];
        line[length] = 0;
        CG_Text_Paint_Ext(320 - CG_Text_Width_Ext(line, .25f, 0, &cgs.media.limboFont2) * .5f,
            y, .25f, .25f, color, line, 0, 0, 7, &cgs.media.limboFont2);
        y += 2 + CG_Text_Height_Ext(line, .25f, 0, &cgs.media.limboFont2);
        while(*cursor && *cursor != '\n') ++cursor;
        if(!*cursor) break;
        ++cursor;
    } while(1);
    trap_R_SetColor(NULL);
    CG_NitmodHudAnchor(previous);
}

static float CG_NitmodBarFraction(double value, double maximum) {
    if(maximum <= 0 || value <= 0) return 0;
    if(value >= maximum) return 1;
    return (float)(value / maximum);
}

/* Original CG_DrawPlayerStatus snapshot offsets:
 * 0x114 = stats[6] (stamina), 0x120 = stats[9] (medic max health),
 * 0x1a8 = powerups[11] (adrenaline). Do not use native aliases here. */
qboolean CG_NitmodStatusBars(const playerState_t *state, int playerClass,
    qboolean underwater, int now, int breathDeadline, nitmodStatusBars_t *out) {
    nitmodStatusBars_t bars;
    int maximum, team, chargeTime, i, support;
    double remaining;
    float pulse;
    if(!state || !out || playerClass < PC_SOLDIER || playerClass > PC_COVERTOPS) return qfalse;
    team = state->persistant[PERS_TEAM];
    if(team != TEAM_AXIS && team != TEAM_ALLIES) return qfalse;
    memset(&bars, 0, sizeof(bars));
    maximum = state->stats[STAT_MAX_HEALTH];
    if(playerClass == PC_MEDIC && cgs.gametype != 8 && !NITMOD_SimpleConfig()->war)
        maximum = state->stats[9];
    bars.health = CG_NitmodBarFraction(state->stats[STAT_HEALTH], maximum);
    bars.underwater = underwater;
    bars.stamina = underwater ? CG_NitmodBarFraction((double)breathDeadline - now, 12000) :
        CG_NitmodBarFraction(state->stats[6], 20000);
    bars.staminaColor[0] = .1f; bars.staminaColor[1] = 1;
    bars.staminaColor[2] = .1f; bars.staminaColor[3] = .5f;
    if(!state->powerups[11]) {
        if(bars.stamina < .25f) { bars.staminaColor[0] = 1; bars.staminaColor[1] = .1f; }
    } else {
        remaining = (double)state->powerups[11] - now;
        if(remaining >= 0) {
            pulse = .5f + .5f * sin(.4f * sqrt(remaining) * M_PI);
            for(i = 0; i < 4; ++i) bars.staminaColor[i] =
                (1 - pulse) * bars.staminaColor[i] + pulse;
        }
    }
    switch(state->stats[STAT_PLAYER_CLASS]) {
        case PC_ENGINEER: chargeTime = cg.engineerChargeTime[team - 1]; break;
        case PC_MEDIC: chargeTime = cg.medicChargeTime[team - 1]; break;
        case PC_FIELDOPS: chargeTime = cg.ltChargeTime[team - 1]; break;
        case PC_COVERTOPS: chargeTime = cg.covertopsChargeTime[team - 1]; break;
        default: chargeTime = cg.soldierChargeTime[team - 1]; break;
    }
    bars.charge = CG_NitmodBarFraction((double)now - state->classWeaponTime, chargeTime);
    bars.chargeColor[0] = 1;
    bars.chargeColor[1] = bars.chargeColor[2] = bars.charge;
    bars.chargeColor[3] = .25f + .5f * bars.charge;
    for(i = 0; i < 4; ++i) bars.powerColor[i] = 1;
    /* Original ammo[13] survives weapon normalization at native WP_ARTY. */
    support = state->ammo[WP_ARTY] & 3;
    if(state->stats[STAT_PLAYER_CLASS] == PC_FIELDOPS && support) {
        bars.powerColor[2] = 0;
        bars.powerColor[1] = support == 1 ? 1 : support == 2 ? .5f : 0;
    }
    *out = bars;
    return qtrue;
}

void CG_NitmodDrawStatusBars(void) {
    nitmodStatusBars_t bars;
    vec4_t healthColor, background = {1, 1, 1, .3f};
    nitmodHudAnchor_t previous;
    int client;
    playerState_t nativeDisplay;
    const playerState_t *display;
    if(!NITMOD_UsesNitmodHud() || !cg.snap) return;
    display = &cg.snap->ps;
    if(!NITMOD_UsesOriginalProtocol()) {
        /* Presentation-only adapter: never reinterpret or rewrite the
         * ET260 snapshot as an original Nitmod network state. */
        nativeDisplay = *display;
        nativeDisplay.stats[6] = cg.pmext.sprintTime;
        nativeDisplay.stats[9] = BG_EffectiveMaxHealth(display);
        nativeDisplay.powerups[11] = display->powerups[PW_ADRENALINE];
        nativeDisplay.ammo[WP_ARTY] = 0; /* No native support-availability mask. */
        display = &nativeDisplay;
    }
    client = cg.snap->ps.clientNum;
    if(client < 0 || client >= MAX_CLIENTS ||
       !CG_NitmodStatusBars(display, cgs.clientinfo[client].cls,
           BG_GetConditionValue(client, ANIM_COND_UNDERWATER, qtrue) != 0,
           cg.time, cg.waterundertime, &bars)) return;
    CG_ColorForHealth(healthColor); healthColor[3] = .5f;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_LEFT);
    CG_FilledBar(18, 395.2f, 12, 60.48f, healthColor, NULL, background, bars.health, 0x55);
    trap_R_SetColor(NULL);
    CG_DrawPic(18, 388, 12, 72, cgs.media.hudSprintBar);
    CG_DrawPic(18, 464, 12, 12, cgs.media.hudHealthIcon);
    CG_FilledBar(4, 395.2f, 12, 60.48f, bars.underwater ? healthColor : bars.staminaColor,
        NULL, background, bars.stamina, 0x55);
    trap_R_SetColor(NULL);
    CG_DrawPic(4, 388, 12, 72, cgs.media.hudSprintBar);
    CG_DrawPic(4, 464, 12, 12, bars.underwater ? cgs.media.waterHintShader : cgs.media.hudSprintIcon);
    CG_NitmodHudAnchor(NITMOD_HUD_RIGHT);
    background[3] = .25f;
    CG_FilledBar(624, 395.2f, 12, 60.48f, bars.chargeColor, NULL, background, bars.charge, 0x55);
    trap_R_SetColor(NULL);
    CG_DrawPic(624, 388, 12, 72, cgs.media.hudSprintBar);
    trap_R_SetColor(bars.powerColor);
    CG_DrawPic(626, 464, 8, 14, cgs.media.hudPowerIcon);
    trap_R_SetColor(NULL);
    CG_NitmodHudAnchor(previous);
}

/* Original CG_DrawSkillLevels: snapshot+0x108 is the high XP word,
 * snapshot+0x11c the low word. These are stats, not persistant slots. */
int CG_NitmodDisplayXP(const playerState_t *state) {
    double value;
    if(!state) return 0;
    if(!NITMOD_UsesOriginalProtocol()) return state->stats[STAT_XP];
    value = (double)state->stats[3] * 32768.0 + state->stats[STAT_XP];
    if(value > INT_MAX) return INT_MAX;
    if(value < INT_MIN) return INT_MIN;
    return (int)value;
}

int CG_NitmodHudSkill(int playerClass, int row, const playerState_t *state) {
    if(playerClass < PC_SOLDIER || playerClass > PC_COVERTOPS || row < 0 || row > 2) return -1;
    if(row == 2) return BG_ClassSkillForClass(playerClass);
    if(row == 1) return SK_BATTLE_SENSE;
    if(state && (state->persistant[PERS_HWEAPON_USE] || (state->eFlags & EF_MOUNTEDTANK)) &&
       playerClass != PC_SOLDIER) return SK_HEAVY_WEAPONS;
    return SK_LIGHT_WEAPONS;
}

void CG_NitmodDrawSkillLevels(void) {
    clientInfo_t *ci;
    int row, skill, level;
    char text[64];
    vec4_t healthColor;
    nitmodHudAnchor_t previous;
    if(!NITMOD_UsesNitmodHud() || !cg.snap || cgs.gametype == GT_WOLF_LMS ||
       cg.snap->ps.clientNum < 0 || cg.snap->ps.clientNum >= MAX_CLIENTS) return;
    ci = &cgs.clientinfo[cg.snap->ps.clientNum];
    previous = CG_NitmodHudAnchor(NITMOD_HUD_LEFT);
    Com_sprintf(text, sizeof(text), "%sXP %i^7",
        (double)cg.time - cg.xpChangeTime >= 0 && (double)cg.time - cg.xpChangeTime < 1000 ? "^3" : "^7",
        CG_NitmodDisplayXP(&cg.snap->ps));
    CG_Text_Paint_Ext(75, 474, .2f, .2f, colorWhite, text, 0, 0, 3, &cgs.media.limboFont1);
    for(row = 0; row < 3; ++row) {
        /* Use the normalized snapshot, not the original global pm pointer. */
        skill = CG_NitmodHudSkill(ci->cls, row, &cg.snap->ps);
        if(skill < 0 || skill >= SK_NUM_SKILLS) continue;
        level = NITMOD_UsesOriginalProtocol() ? ci->nitmodSkillLevels[skill] : ci->skill[skill];
        if(level < 0) level = 0;
        if(level > 5) level = 5;
        trap_R_SetColor(colorBlack);
        CG_DrawPic(33, 388 + 24 * row, 13, 13, cgs.media.skillPics[skill]);
        trap_R_SetColor(NULL);
        CG_DrawPic(32, 387 + 24 * row, 13, 13, cgs.media.skillPics[skill]);
        Com_sprintf(text, sizeof(text), "^7%d", level);
        CG_Text_Paint_Ext(35, 411 + 23 * row, .2f, .2f, colorWhite, text, 0, 0, 3, &cgs.media.limboFont1);
    }
    CG_ColorForHealth(healthColor);
    Com_sprintf(text, sizeof(text), "%i^7HP", cg.snap->ps.stats[STAT_HEALTH]);
    CG_Text_Paint_Ext(34, 474, .2f, .2f, healthColor, text, 0, 0, 3, &cgs.media.limboFont1);
    trap_R_SetColor(NULL);
    CG_NitmodHudAnchor(previous);
}

vmCvar_t cg_drawPing, cg_drawTime, cg_drawTimeSeconds;
vmCvar_t cg_spawnTimer_set, cg_spawnTimer_period;
vmCvar_t cg_drawHUDStats;
static int bodyshotTime, headshotTime;
static qboolean bodyshotChanged, headshotChanged;

void CG_NitmodLiveStatsTransition(const playerState_t *oldState, const playerState_t *newState) {
    const int *oldValues, *newValues;
    if(!NITMOD_UsesOriginalProtocol() || !oldState || !newState) return;
    oldValues = NITMOD_WirePersistant(oldState);
    newValues = NITMOD_WirePersistant(newState);
    if(oldState->clientNum != newState->clientNum) {
        bodyshotChanged = headshotChanged = qfalse;
        return;
    }
    if(newValues[NITMOD_PERS_BODYSHOTS] > oldValues[NITMOD_PERS_BODYSHOTS]) {
        bodyshotTime = cg.time; bodyshotChanged = qtrue;
    }
    if(newValues[NITMOD_PERS_HEADSHOTS] > oldValues[NITMOD_PERS_HEADSHOTS]) {
        headshotTime = cg.time; headshotChanged = qtrue;
    }
}

qboolean CG_NitmodLiveStatsText(const playerState_t *state, int row, int now, char *out, int size) {
    static const int slots[] = {NITMOD_PERS_KILLSPREE, NITMOD_PERS_BODYSHOTS,
        NITMOD_PERS_HEADSHOTS, NITMOD_PERS_KILLS, NITMOD_PERS_DEATHS};
    static const char *labels[] = {"Spree", "BS", "HS", "K", "D"};
    char color = 'f';
    double age;
    if(!out || size <= 0) return qfalse;
    out[0] = 0;
    if(!state || row < 0 || row >= 5) return qfalse;
    age = (double)now - (row == 1 ? bodyshotTime : headshotTime);
    if(((row == 1 && bodyshotChanged) || (row == 2 && headshotChanged)) && age >= 0 && age < 100)
        color = '2';
    Com_sprintf(out, size, "^7%s: ^%c%d", labels[row], color, NITMOD_WirePersistant(state)[slots[row]]);
    return qtrue;
}

void CG_NitmodDrawLiveStats(void) {
    char text[64];
    vec4_t background, border;
    float width, x;
    int row;
    nitmodHudAnchor_t previous;
    if(!cg.snap || !NITMOD_UsesOriginalProtocol() || !cg_draw2D.integer || !cg_drawHUDStats.integer ||
       cg.clientNum < 0 || cg.clientNum >= MAX_CLIENTS || cgs.clientinfo[cg.clientNum].nitmodTV) return;
    CG_NitmodLiveStatsText(&cg.snap->ps, 0, cg.time, text, sizeof(text));
    width = CG_Text_Width_Ext(text, .17f, 0, &cgs.media.limboFont1);
    x = (cg_HUDFlags.integer & 1) ? 5 : 624 - width;
    previous = CG_NitmodHudAnchor((cg_HUDFlags.integer & 1) ? NITMOD_HUD_LEFT : NITMOD_HUD_RIGHT);
    CG_NitmodHudColors(background, border);
    CG_FillRect(x, 335, width + 10, 50, background);
    CG_DrawRect_FixedBorder(x, 335, width + 10, 50, 1, border);
    for(row = 0; row < 5; ++row) {
        CG_NitmodLiveStatsText(&cg.snap->ps, row, cg.time, text, sizeof(text));
        CG_Text_Paint_Ext(x + 3, 343 + row * 10, .17f, .17f, colorWhite, text, 0, 0, 3, &cgs.media.limboFont1);
    }
    CG_NitmodHudAnchor(previous);
}

static nitmodHudAnchor_t hudAnchor = NITMOD_HUD_STRETCH;
static float hudScaleX, hudScaleY, hudOffset;
static qboolean hudTransform;
nitmodHudAnchor_t CG_NitmodHudAnchor(nitmodHudAnchor_t anchor) {
    nitmodHudAnchor_t previous = hudAnchor;
    float bias = 0;
    hudAnchor = anchor >= NITMOD_HUD_STRETCH && anchor <= NITMOD_HUD_RIGHT ? anchor : NITMOD_HUD_STRETCH;
    hudTransform = hudAnchor != NITMOD_HUD_STRETCH && NITMOD_UsesNitmodHud() &&
        cgs.glconfig.vidWidth > 0 && cgs.glconfig.vidHeight > 0;
    if(hudTransform) {
        hudScaleX = cgs.glconfig.vidWidth / 640.f;
        hudScaleY = cgs.glconfig.vidHeight / 480.f;
        if(hudScaleX > hudScaleY) {
            hudScaleX = hudScaleY;
            bias = (cgs.glconfig.vidWidth - 640.f * hudScaleX) * .5f;
        }
        hudOffset = hudAnchor == NITMOD_HUD_LEFT ? 0 : hudAnchor == NITMOD_HUD_RIGHT ? 2 * bias : bias;
    }
    return previous;
}

/* Original CG_AdjustFrom640/CG_Init: preserve 4:3 geometry on wide displays.
 * Scope this transform to ported HUD widgets; don't shift fullscreen/menu
 * consumers that have not yet been migrated to original HUD placement. */
qboolean CG_NitmodAdjustHud(float *x, float *y, float *w, float *h) {
    if(!hudTransform) return qfalse;
    *x = *x * hudScaleX + hudOffset;
    *y *= hudScaleY; *w *= hudScaleX; *h *= hudScaleY;
    return qtrue;
}

void CG_NitmodResetTimer(void) {
    float elapsed = (float)((double)cg.time - cgs.levelStartTime);
    float msec = cgs.timelimit * 60.f * 1000.f - elapsed;
    if(!(msec >= -2147483648.0 && msec < 2147483648.0)) return;
    trap_Cvar_Set("cg_spawnTimer_set", va("%d", (int)msec / 1000));
}

void CG_NitmodTimerSet(void) {
    char argument[32];
    long seconds;
    if(trap_Argc() == 1) {
        trap_Cvar_Set("cg_spawnTimer_set", "-1");
        return;
    }
    if(trap_Argc() != 2) {
        CG_Printf("^9usage: ^gtimerSet [seconds]\n");
        return;
    }
    trap_Argv(1, argument, sizeof(argument));
    seconds = strtol(argument, NULL, 10);
    if(seconds < 1 || seconds > 60) {
        CG_Printf("Argument must be a number between 1 and 60.\n");
        return;
    }
    trap_Cvar_Set("cg_spawnTimer_period", argument);
    CG_NitmodResetTimer();
}

void CG_NitmodSpawnTimerText(char *out, int size, int seconds, int start, int period, const char *timer) {
    if(!out || size <= 0) return;
    if(!timer) timer = "";
    if(start == -1 || period <= 0) Q_strncpyz(out, timer, size);
    else Com_sprintf(out, size, "^1%.0f %s", fmod((double)seconds - start, period) + period, timer);
}

void CG_NitmodMatchTimerText(char *out, int size, int msec, qboolean limited, qboolean playing, const char *reinforcement) {
    int seconds, minutes, hours, days;
    if(!out || size <= 0) return;
    if(!reinforcement) reinforcement = "";
    if(!playing) { Q_strncpyz(out, "^7WARMUP", size); return; }
    if(!limited) { Q_strncpyz(out, reinforcement, size); return; }
    if(msec < 0) { Q_strncpyz(out, "^N0:00", size); return; }
    seconds = msec / 1000;
    minutes = seconds / 60;
    hours = minutes / 60;
    days = hours / 24;
    if(days) Com_sprintf(out, size, "%s^7%dd%d:%d:%02d", reinforcement, days, hours % 24, minutes % 60, seconds % 60);
    else if(hours) Com_sprintf(out, size, "%s^7%d:%d:%02d", reinforcement, hours, minutes % 60, seconds % 60);
    else Com_sprintf(out, size, "%s^7%d:%02d", reinforcement, minutes, seconds % 60);
}
/* Original CG_DrawUpperRight: free spectators have no reinforcement prefix;
 * modes 7/8 keep that prefix but omit the ordinary match countdown. */
void CG_NitmodRoundTimerText(char *out, int size, float *alpha) {
    char reinforcement[32] = "", match[96];
    double remaining = (double)cgs.timelimit * 60000.0 - ((double)cg.time - cgs.levelStartTime);
    int msec, client = cg.clientNum;
    qboolean limited = cgs.timelimit > 0.0f;
    qboolean playing = cgs.gamestate == GS_PLAYING;
    qboolean special = cgs.gametype == 7 || cgs.gametype == 8;
    if(!out || size <= 0) return;
    /* Keep all float-to-int conversions defined for malformed server data. */
    if(remaining != remaining) remaining = 0;
    msec = remaining >= INT_MAX ? INT_MAX : remaining <= INT_MIN ? INT_MIN : (int)remaining;
    if(cg.snap && client >= 0 && client < MAX_CLIENTS &&
       cgs.gametype != GT_WOLF_LMS && cg_drawReinforcementTime.integer > 0 &&
       (cgs.clientinfo[client].team != TEAM_SPECTATOR || (cg.snap->ps.pm_flags & PMF_FOLLOW))) {
        int viewed = cg.snap->ps.clientNum;
        if(viewed >= 0 && viewed < MAX_CLIENTS &&
           (cgs.clientinfo[viewed].team == TEAM_AXIS || cgs.clientinfo[viewed].team == TEAM_ALLIES)) {
            int seconds = CG_CalculateReinfTime(qfalse);
            if(seconds > 0) Com_sprintf(reinforcement, sizeof(reinforcement), "^F%d%s", seconds, limited ? " " : "");
        }
    }
    if(playing && special) Com_sprintf(match, sizeof(match), " %s", reinforcement);
    else CG_NitmodMatchTimerText(match, sizeof(match), msec, limited, playing, reinforcement);
    if(alpha) *alpha = !playing || (!special && msec < 0 && limited) ?
        (float)fabs(sin(cg.time * 0.002)) : 1.0f;
    CG_NitmodSpawnTimerText(out, size, msec / 1000,
        cg_spawnTimer_set.integer, cg_spawnTimer_period.integer, match);
}
vmCvar_t cg_drawspeed, cg_speedunit, cg_speedinterval;
vmCvar_t cg_HUDBackgroundColor, cg_HUDBorderColor, cg_HUDAlpha;
vmCvar_t cg_notificationTime, cg_notificationFadeTime;
static char notificationText[MAX_STRING_CHARS];
static int notificationStage;
static double notificationTime;
static char killPrintText[64];
static double killPrintEnd;
static int spreeActor = -1;
static const char *spreeLabel;
static double spreeEnd;
static char announcerText[1024];
static double announcerStart;
static int announcerDuration, announcerAnimation, announcerYOffset;
static float announcerScale;
static vec4_t announcerColor;
static sfxHandle_t announcerFightSound, announcerPrepareSound;

void CG_NitmodRegisterAnnouncerSounds(void) {
    announcerFightSound = trap_S_RegisterSound("sound/nit/fight.wav", qfalse);
    announcerPrepareSound = trap_S_RegisterSound("sound/nit/prepare.wav", qfalse);
}

/* CG_DrawActivePowerups: original snapshot offsets minus the 44-byte
 * snapshot header map to these typed arrays. These are WIRE indices,
 * intentionally not native PW_* aliases. No player state is rewritten. */
static qhandle_t statusShield, statusFlak, statusHelmet, statusBinoculars;
static qhandle_t statusUniformAxis, statusUniformAllies;

void CG_NitmodRegisterPowerupMedia(void) {
    statusShield = trap_R_RegisterShader("sprites/shield");
    statusFlak = trap_R_RegisterShaderNoMip("gfx/flakjacket_axis");
    statusHelmet = trap_R_RegisterShaderNoMip("ui/assets/filter_lives.tga");
    statusBinoculars = trap_R_RegisterShaderNoMip("icons/iconw_binoculars_1_select.tga");
    statusUniformAxis = trap_R_RegisterShader("sprites/uniform_axis");
    statusUniformAllies = trap_R_RegisterShader("sprites/uniform_allied");
}

void CG_NitmodDrawActivePowerups(void) {
    const playerState_t *ps;
    nitmodHudAnchor_t previous;
    int disguiseClass;
    if(!cg.snap || !NITMOD_UsesOriginalProtocol()) return;
    ps = &cg.snap->ps;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_RIGHT);
    trap_R_SetColor(NULL);
    if(ps->powerups[5] || ps->powerups[6]) {
        CG_DrawPic(600, 390, 15, 15, cgs.media.objectiveShader);
    } else if(ps->powerups[7]) {
        CG_DrawPic(580, 390, 15, 15,
            ps->persistant[7] == TEAM_AXIS ? statusUniformAllies : statusUniformAxis);
        disguiseClass = (ps->powerups[8] != 0) | ((ps->powerups[9] != 0) << 1) |
            ((ps->powerups[10] != 0) << 2);
        if(disguiseClass < NUM_PLAYER_CLASSES)
            CG_DrawStringExt(578, 390, BG_ShortClassnameForNumber(disguiseClass),
                colorWhite, qfalse, qtrue, 4, 12, 0);
    }
    if(ps->stats[1] & 64) CG_DrawPic(560, 409, 15, 15, statusBinoculars);
    if(!(ps->eFlags & EF_HEADSHOT)) CG_DrawPic(580, 410, 15, 15, statusHelmet);
    if(ps->powerups[1] || ps->powerups[2])
        CG_DrawPic(600, 409, 15, 15, ps->powerups[1] ? statusShield : statusFlak);
    trap_R_SetColor(NULL);
    CG_NitmodHudAnchor(previous);
}

void CG_NitmodAddAnnouncer(const char *text, sfxHandle_t sound, float scale,
    int duration, float red, float green, float blue, int animation, int yOffset) {
    if(!cg_announcer.integer) return;
    /* The original permits sound-only calls without replacing the text slot. */
    if(sound > 0) trap_S_StartLocalSound(sound, CHAN_ANNOUNCER);
    if(!text) return;
    /* Reject non-finite renderer inputs and zero divisors. */
    if(duration <= 0 || !(scale > 0 && scale <= 100) ||
       !(red >= 0 && red <= 1) || !(green >= 0 && green <= 1) ||
       !(blue >= 0 && blue <= 1)) return;
    Q_strncpyz(announcerText, text, sizeof(announcerText));
    announcerStart = cg.time;
    announcerDuration = duration;
    announcerAnimation = animation;
    announcerYOffset = yOffset;
    announcerScale = scale;
    Vector4Set(announcerColor, red, green, blue, 1);
}

void CG_NitmodAnnounce(int type) {
    if(type != 0 && type != -1) return;
    CG_NitmodAddAnnouncer(type ? "PREPARE TO FIGHT!" : "FIGHT!",
        type ? announcerPrepareSound : announcerFightSound,
        type ? .85f : 1.1f, 1000, 1, type ? 1 : 0, 0, 1, 0);
}

const char *CG_NitmodAnnouncerText(void) { return announcerText; }

qboolean CG_NitmodAnnouncerFrame(int now, float *scale, vec4_t color) {
    double elapsed = (double)now - announcerStart;
    double remaining, factor;
    if(!scale || !color || !announcerText[0] || !cg_announcer.integer ||
       announcerDuration <= 0 || elapsed >= announcerDuration) return qfalse;
    if(elapsed < 0) elapsed = 0;
    remaining = 1.0 - elapsed / announcerDuration;
    if(announcerAnimation == 2) factor = 1.1 - sin(remaining * 3.1415927);
    else if(announcerAnimation == 3) factor = .1 + sin(remaining * 3.1415927);
    else factor = 1.1 - remaining;
    *scale = (float)(factor * announcerScale);
    Vector4Copy(announcerColor, color);
    return qtrue;
}

void CG_NitmodDrawAnnouncer(void) {
    float scale;
    vec4_t color;
    if(CG_NitmodAnnouncerFrame(cg.time, &scale, color)) {
        nitmodHudAnchor_t previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
        CG_Text_Paint_Centred_Ext(320, 240.f - (float)announcerYOffset, scale, scale, color, announcerText,
            0, 0, 3, &cgs.media.limboFont1);
        CG_NitmodHudAnchor(previous);
    }
}
static char specialText[128];
static vec4_t specialColor;
static double specialStart;
static int specialXP;

static void SpecialStart(const char *text, float r, float g, float b, int xp) {
    Q_strncpyz(specialText, text, sizeof(specialText));
    Vector4Set(specialColor, r, g, b, 1);
    specialStart = cg.time; specialXP = xp;
}

qboolean CG_NitmodSpecialAnnouncement(int type, int xp) {
    const char *text;
    switch(type) {
    case 1: text = "KILL ASSISTANCE!"; break;
    case 2: text = "SUICIDE HELPER!"; break;
    case 3: text = "TEAMKILL ASSISTANCE!"; break;
    case 4: text = "FIRST BLOOD!"; break;
    case 5: text = "FIRST HEADSHOT!"; break;
    case -2: text = "REVENGE!"; break;
    default: return qfalse;
    }
    SpecialStart(text, 1, type == 1 || type == 2 ? 1 : 0,
        type == 1 || type == 2 ? 1 : 0, xp);
    return qtrue;
}

void CG_NitmodHealthBonus(int amount) {
    char text[32];
    Com_sprintf(text, sizeof(text), "+%i HP", amount);
    SpecialStart(text, 0, 1, 0, 0);
}

const char *CG_NitmodSpecialText(void) { return specialText; }

qboolean CG_NitmodSpecialFrame(int now, float *scale, vec4_t color) {
    double elapsed = (double)now - specialStart;
    float pulse;
    if(!specialText[0]) return qfalse;
    if(elapsed >= 1400) { specialText[0] = 0; specialXP = 0; return qfalse; }
    if(elapsed < 0) elapsed = 0;
    pulse = (float)((200 - elapsed) / 200);
    *scale = pulse > .28f ? pulse : .28f;
    Vector4Copy(specialColor, color);
    /* The original sets negative alpha during the initial pulse. Clamp to
     * the renderer's effective zero instead of submitting invalid alpha. */
    color[3] = pulse > .28f ? 0 : .7f;
    return qtrue;
}

void CG_NitmodDrawSpecial(void) {
    float scale;
    vec4_t color;
    char xp[32];
    nitmodHudAnchor_t previous;
    if(!CG_NitmodSpecialFrame(cg.time, &scale, color)) return;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    CG_Text_Paint_Centred_Ext(320, 90, scale, scale, color, specialText,
        0, 0, 3, &cgs.media.limboFont1);
    if(scale <= .28f && specialXP) {
        Com_sprintf(xp, sizeof(xp), "%s%iXP", specialXP > 0 ? "+" : "", specialXP);
        CG_Text_Paint_Centred_Ext(320, 100, .2f, .2f, color, xp,
            0, 0, 3, &cgs.media.limboFont1);
    }
    CG_NitmodHudAnchor(previous);
}
static sfxHandle_t spreeSounds[6], multiKillSounds[5], multiReviveSounds[4];

void CG_NitmodRegisterSpreeSounds(void) {
    int i;
    char path[MAX_QPATH];
    for(i = 0; i < 5; ++i) {
        Com_sprintf(path, sizeof(path), "sound/nit/mk%i.wav", i + 1);
        multiKillSounds[i] = trap_S_RegisterSound(path, qfalse);
    }
    for(i = 0; i < 4; ++i) {
        Com_sprintf(path, sizeof(path), "sound/nit/mr%i.wav", i + 1);
        multiReviveSounds[i] = trap_S_RegisterSound(path, qfalse);
    }
    for(i = 0; i < 6; ++i) {
        Com_sprintf(path, sizeof(path), "sound/nit/ks%i.wav", i + 1);
        spreeSounds[i] = trap_S_RegisterSound(path, qfalse);
    }
}

/* Original ELF message tables: KSpreeMsg, LSpreeMsg, MKName, MRName. */
const char *CG_NitmodSpreeLabel(int type, int detail) {
    static const char *kills[] = {"^2Killing Spree!", "^2Rampage!", "^2Dominating!",
        "^2Unstoppable!", "^2Godlike!", "^2Wicked Sick!"};
    static const char *losses[] = {"^1Losing Spree!", "^1Ass Kicked!!", "^1Go get skills!!!"};
    static const char *multi[] = {"^fDouble Kill", "^fTriple Kill", "^fMultikill",
        "^fMonster Kill", "^fHoly Shit"};
    static const char *revives[] = {"^fDouble Revive", "^fTriple Revive",
        "^fMulti Revive", "^fMonster Revive"};
    if(detail < 0) return NULL;
    switch(type) {
    case 1: return detail < 6 ? kills[detail] : NULL;
    case 2: return detail < 3 ? losses[detail] : NULL;
    case 3: return detail < 5 ? multi[detail] : NULL;
    case 5: return detail < 4 ? revives[detail] : NULL;
    default: return NULL;
    }
}

qboolean CG_NitmodSpreeStart(int actor, int detail, int type) {
    const char *label = CG_NitmodSpreeLabel(type, detail);
    clientInfo_t *ci;
    char message[MAX_STRING_CHARS];
    sfxHandle_t sound = 0;
    if(actor < 0 || actor >= MAX_CLIENTS) return qfalse;
    ci = &cgs.clientinfo[actor];
    if(!ci->infoValid || !ci->name[0]) return qfalse;
    if(type == 4) {
        if(detail < 5 || detail % 5) return qfalse;
        Com_sprintf(message, sizeof(message), "^f>>> ^7%s ^gis on a revive spree ! (^8%d^g) ^f<<<", ci->name, detail);
        CG_AddToTeamChat(message, -1);
        CG_Printf("%s\n", message);
        return qtrue;
    }
    if(!label) return qfalse;
    spreeActor = actor; spreeLabel = label; spreeEnd = (double)cg.time + 4250;
    CG_Printf("^%c>>> ^7%s^7:%s <<<^7\n", type == 1 ? '2' : type == 2 ? '1' : 'f', ci->name, label);
    /* Original uses the snapshot client's entity, not the announced actor. */
    if(type == 1) sound = spreeSounds[detail];
    else if(type == 3) sound = multiKillSounds[detail];
    else if(type == 5) sound = multiReviveSounds[detail];
    if(sound > 0 && cg.snap && cg.snap->ps.clientNum >= 0 && cg.snap->ps.clientNum < MAX_CLIENTS)
        trap_S_StartSound(NULL, cg.snap->ps.clientNum, CHAN_AUTO, sound);
    return qtrue;
}

qboolean CG_NitmodSpreeUsesLeft(void) {
    /* Original g_unk_010ef260 is the notification transition state. */
    return (cg_HUDFlags.integer & 8) || notificationStage != 0;
}

void CG_NitmodDrawSpree(void) {
    float scale, x, y;
    nitmodHudAnchor_t previous;
    double remaining = spreeEnd - cg.time;
    if(!spreeLabel || spreeActor < 0 || remaining <= 0 ||
       !cgs.clientinfo[spreeActor].infoValid || !cgs.clientinfo[spreeActor].name[0]) return;
    if(remaining > 4250) remaining = 4250;
    scale = (float)((remaining / 4250 + .5 + sin((double)cg.time / 150) * .5) * .1 + .1);
    x = CG_NitmodSpreeUsesLeft() ? 10 : 520;
    y = CG_NitmodSpreeUsesLeft() ? 200 : 15;
    previous = CG_NitmodHudAnchor(CG_NitmodSpreeUsesLeft() ? NITMOD_HUD_LEFT : NITMOD_HUD_RIGHT);
    CG_Text_Paint_Ext(x, y, scale, scale, colorWhite, spreeLabel, 0, 0, 3, &cgs.media.limboFont1);
    CG_Text_Paint_Ext(x, y + 10, .2f, .2f, colorWhite,
        cgs.clientinfo[spreeActor].name, 0, 16, 3, &cgs.media.limboFont1);
    CG_NitmodHudAnchor(previous);
}

/* Original HUD bit 16. Coordinates are adjusted before the three-pixel step. */
qboolean CG_NitmodDrawAmmo(int weapon, int clip, int reserve, int akimbo) {
    float x = 590, y = 458, w = 1, h = 4;
    float rowX, rowY;
    nitmodHudAnchor_t previous;
    vec4_t color;
    char text[32];
    int capacity, hand, i, rows = 0, count;
    if(!(cg_HUDFlags.integer & 16) || weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS ||
       clip < 0 || reserve < 0) return qfalse;
    capacity = GetAmmoTableData(weapon)->maxclip;
    /* Invalid/custom oversized capacities retain the bounded numeric display. */
    if(capacity < 1 || capacity > 150) return qfalse;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_RIGHT);
    CG_AdjustFrom640(&x, &y, &w, &h);
    rowX = x; rowY = y;
    for(hand = 0; hand < (akimbo >= 0 ? 2 : 1); ++hand) {
        count = akimbo >= 0 && hand == 0 ? akimbo : clip;
        Vector4Set(color, 1, count <= capacity / 4 ? 0 : 1,
                   count <= capacity / 4 ? 0 : 1, 1);
        if(hand) {
            x = rowX;
            y = rowY + h * 1.5f;
        }
        for(i = 0; i < capacity; ++i) {
            if(akimbo < 0 && (i == 50 || i == 100)) {
                ++rows;
                x = rowX;
                y += h * 1.25f;
            }
            if(i >= count) color[3] = .35f;
            trap_R_SetColor(color);
            trap_R_DrawStretchPic(x, y, w, h, 0, 0, 0, 1, cgs.media.whiteShader);
            trap_R_SetColor(NULL);
            x -= 3;
        }
    }
    Com_sprintf(text, sizeof(text), "%i", reserve);
    CG_Text_Paint_Centred_Ext(606, akimbo >= 0 ? 466 : 463 + rows * 2.5f,
        .2f, .2f, colorWhite, text, 0, 0, 3, &cgs.media.limboFont1);
    CG_NitmodHudAnchor(previous);
    return qtrue;
}

qboolean CG_NitmodKillPrint(const char *text, qboolean teammate, int now) {
    if(teammate || !(cg_HUDFlags.integer & 4)) return qfalse;
    Q_strncpyz(killPrintText, text ? text : "", sizeof(killPrintText));
    killPrintEnd = (double)now + 1850;
    return qtrue;
}

const char *CG_NitmodKillPrintText(void) { return killPrintText; }

float CG_NitmodKillPrintAlpha(int now) {
    double alpha;
    if(!*killPrintText) return 0;
    alpha = (killPrintEnd - now) / 1850.0;
    if(alpha <= 0) { killPrintText[0] = 0; return 0; }
    return alpha > 1 ? 1 : (float)alpha;
}

void CG_NitmodDrawKillPrint(void) {
    vec4_t color = {1, 1, 1, 1};
    float scale;
    nitmodHudAnchor_t previous;
    color[3] = CG_NitmodKillPrintAlpha(cg.time);
    if(color[3] <= 0) return;
    scale = ((float)sin(color[3] * 1.1) + .7f) * .2f;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
    CG_Text_Paint_Centred_Ext(320, 120, scale, scale, color, killPrintText,
        0, 0, 3, &cgs.media.limboFont1);
    CG_NitmodHudAnchor(previous);
}

void CG_NitmodNotificationStart(const char *text, int now) {
    Q_strncpyz(notificationText, text ? text : "", sizeof(notificationText));
    notificationTime = now;
    notificationStage = *notificationText ? 1 : 0;
}

const char *CG_NitmodNotificationText(void) { return notificationText; }
qboolean CG_NitmodNotificationActive(void) { return notificationStage != 0; }

float CG_NitmodNotificationAlpha(int now, float hold, float fade) {
    double alpha;
    if(!(hold >= -FLT_MAX && hold <= FLT_MAX)) hold = 8000;
    if(!(fade >= -FLT_MAX && fade <= FLT_MAX)) fade = 250;
    hold = hold < 1500 ? 1500 : hold > 10000 ? 10000 : hold;
    fade = fade < 0 ? 0 : fade > 250 ? 250 : fade;
    if(!notificationStage || !fade) return 0;
    if(notificationStage == 1) {
        alpha = ((double)now - notificationTime) / fade;
        if(alpha >= 1) {
            notificationStage = 2;
            notificationTime = (double)now + hold;
            return 1;
        }
    } else {
        alpha = 1 - ((double)now - notificationTime) / fade;
        if(alpha <= 0) { notificationStage = 0; return 0; }
    }
    return alpha < 0 ? 0 : alpha > 1 ? 1 : (float)alpha;
}

void CG_NitmodDrawNotification(void) {
    vec4_t background, border, white = {1, 1, 1, 1};
    float width, height, x;
    nitmodHudAnchor_t previous;
    if(CG_NitmodGlobalAwardActive()) return;
    white[3] = CG_NitmodNotificationAlpha(cg.time, cg_notificationTime.value, cg_notificationFadeTime.value);
    if(white[3] <= 0) return;
    CG_NitmodHudColors(background, border);
    background[3] = white[3] * .5f;
    width = CG_Text_Width_Ext(notificationText, .2f, 0, &cgs.media.limboFont2) + 20;
    height = CG_Text_Height_Ext(notificationText, .2f, 0, &cgs.media.limboFont2);
    x = 639 - width * white[3];
    previous = CG_NitmodHudAnchor(NITMOD_HUD_RIGHT);
    CG_FillRect(x, 0, width, 24, background);
    CG_DrawRect_FixedBorder(x, 0, width, 24, 1, white);
    CG_Text_Paint_Ext(x + 10, 12 + height * .5f, .2f, .2f, white,
        notificationText, 0, 0, 7, &cgs.media.limboFont2);
    CG_NitmodHudAnchor(previous);
}

qboolean CG_NitmodParseHudColor(const char *text, float alpha, vec4_t color) {
    /* jP_SetHUDColors, original ELF32 VA 0x86770. Match aliases exactly. */
    static const struct { const char *name, *rgb; } presets[] = {
        {"default", ".5 .5 .5"}, {"def", ".5 .5 .5"},
        {"red", ".75 0 0"}, {"green", "0 .75 0"}, {"blue", "0 0 .75"},
        {"black", "0 0 0"}, {"white", "1 1 1"},
        {"dkgrey", ".25 .25 .25"}, {"darkgrey", ".25 .25 .25"},
        {"dkgray", ".25 .25 .25"}, {"darkgray", ".25 .25 .25"},
        {"grey", ".5 .5 .5"}, {"gray", ".5 .5 .5"},
        {"cthulhu", "0 .25 .25"}, {"cthulhu_green", "0 .25 .25"}
    };
    vec4_t next;
    char *end;
    double value;
    int i;
    if(!text || !color || !(alpha >= -FLT_MAX && alpha <= FLT_MAX)) return qfalse;
    for(i = 0; i < sizeof(presets) / sizeof(presets[0]); ++i) {
        if(!strcmp(text, presets[i].name)) { text = presets[i].rgb; break; }
    }
    for(i = 0; i < 3; ++i) {
        while(*text == ' ' || *text == '\t' || *text == ',') ++text;
        value = strtod(text, &end);
        if(end == text || !(value >= -FLT_MAX && value <= FLT_MAX) ||
           (*end && *end != ' ' && *end != '\t' && *end != ',')) return qfalse;
        next[i] = value < 0 ? 0 : value > 1 ? 1 : (float)value;
        text = end;
    }
    /* Original uses only RGB: a fourth menu component never overrides HUDAlpha. */
    next[3] = alpha < 0 ? 0 : alpha > 1 ? 1 : alpha;
    memcpy(color, next, sizeof(next));
    return qtrue;
}

void CG_NitmodHudColors(vec4_t background, vec4_t border) {
    float alpha = cg_HUDAlpha.value;
    if(!(alpha >= -FLT_MAX && alpha <= FLT_MAX)) alpha = .8f;
    CG_NitmodParseHudColor(".16 .2 .17", alpha, background);
    CG_NitmodParseHudColor(".5 .5 .5", alpha, border);
    CG_NitmodParseHudColor(cg_HUDBackgroundColor.string, alpha, background);
    CG_NitmodParseHudColor(cg_HUDBorderColor.string, alpha, border);
}
static float speed, highestSpeed;
static int lastSample;
static int fpsTimes[500], fpsPrevious, fpsSamples, fpsCursor, fpsCount;
static int tdmAxisScore, tdmAlliesScore;
static int tdmAxisChanged, tdmAlliesChanged;
static qboolean tdmAxisIncreased, tdmAlliesIncreased;
void CG_NitmodResetMaxSpeed(void) { highestSpeed = 0; }

void CG_NitmodHudReset(void) {
	CG_NitmodSnapshotRateReset();
    memset(&nitmodAnnouncement, 0, sizeof(nitmodAnnouncement));
    NITMOD_ResetSnapshotPersistant();
    bodyshotChanged = headshotChanged = qfalse;
    bodyshotTime = headshotTime = 0;
	CG_NitmodHintsReset();
	CG_NitmodNamesReset();
    hudAnchor = NITMOD_HUD_STRETCH;
    hudTransform = qfalse;
    announcerText[0] = 0; announcerStart = 0; announcerDuration = 0;
    announcerAnimation = announcerYOffset = 0; announcerScale = 0;
    memset(announcerColor, 0, sizeof(announcerColor));
    specialText[0] = 0; specialXP = 0; specialStart = 0;
    spreeActor = -1; spreeLabel = NULL; spreeEnd = 0;
    CG_NitmodNotificationStart("", 0);
    killPrintText[0] = 0;
    killPrintEnd = 0;
    speed = highestSpeed = 0;
    lastSample = 0;
    fpsPrevious = fpsSamples = fpsCursor = fpsCount = 0;
	tdmAxisScore = tdmAlliesScore = 0;
	tdmAxisChanged = tdmAlliesChanged = 0;
	tdmAxisIncreased = tdmAlliesIncreased = qfalse;
}

float CG_NitmodTDMProgress(int score, int limit) {
	float fraction;
	if(limit <= 0 || score <= 0) return 0;
	fraction = (float)score / (float)limit;
	return fraction > 1 ? 1 : fraction;
}

void CG_NitmodTDMScoreChanged(int axis, int allies, int now) {
	if(axis != tdmAxisScore) {
		tdmAxisIncreased = axis > tdmAxisScore;
		tdmAxisChanged = now;
		tdmAxisScore = axis;
	}
	if(allies != tdmAlliesScore) {
		tdmAlliesIncreased = allies > tdmAlliesScore;
		tdmAlliesChanged = now;
		tdmAlliesScore = allies;
	}
}

static float *TDMScoreColor(int changed, qboolean increased) {
	if((double)cg.time - changed >= 0 && (double)cg.time - changed < 750)
		return increased ? colorGreen : colorRed;
	return colorWhite;
}

float CG_NitmodDrawTDMScore(float y) {
	const nitmodGameState_t *state = NITMOD_GameState();
	vec4_t background, border, textColor = {.625f, .625f, .6f, 1};
	char axis[32], allies[32], limit[16];
	float x;
	int width;
	nitmodHudAnchor_t previous;
	if(!NITMOD_UsesOriginalProtocol() || cgs.gametype != 7 ||
	   cgs.gamestate != GS_PLAYING || state->tdmScoreLimit <= 0) return y;
	CG_NitmodHudColors(background, border);
	if(cg_TDMScorePos.integer == 1) {
		previous = CG_NitmodHudAnchor(NITMOD_HUD_RIGHT);
		Com_sprintf(axis, sizeof(axis), "^_Axis ^7%d", state->teamScoreAxis);
		width = CG_Text_Width_Ext(axis, .19f, 0, &cgs.media.limboFont1);
		x = 632 - width;
		CG_FillRect(x, y, width + 5, 14, background);
		CG_DrawRect_FixedBorder(x, y, width + 5, 14, 1, border);
		CG_Text_Paint_Ext(x + 2, y + 11, .19f, .19f, textColor, axis, 0, 0, 0, &cgs.media.limboFont1);
		Com_sprintf(allies, sizeof(allies), "^4Allies ^7%d", state->teamScoreAllies);
		width = CG_Text_Width_Ext(allies, .19f, 0, &cgs.media.limboFont1);
		x = 632 - width;
		CG_FillRect(x, y + 16, width + 5, 14, background);
		CG_DrawRect_FixedBorder(x, y + 16, width + 5, 14, 1, border);
		CG_Text_Paint_Ext(x + 2, y + 27, .19f, .19f, textColor, allies, 0, 0, 0, &cgs.media.limboFont1);
		CG_NitmodHudAnchor(previous);
		return y + 32;
	}
	if(cg.showScores) return y;
	previous = CG_NitmodHudAnchor(NITMOD_HUD_CENTER);
	Com_sprintf(axis, sizeof(axis), "%d", state->teamScoreAxis);
	Com_sprintf(allies, sizeof(allies), "%d", state->teamScoreAllies);
	Com_sprintf(limit, sizeof(limit), "%d", state->tdmScoreLimit);
	CG_FillRect(240, 35, 160, 30, background);
	CG_DrawRect_FixedBorder(240, 35, 160, 35, 1, border);
	CG_Text_Paint_Ext(255, 45, .2f, .2f, colorMdRed, "Axis", 0, 0, 3, &cgs.media.limboFont1);
	CG_Text_Paint_Ext(385 - CG_Text_Width_Ext("Allies", .2f, 0, &cgs.media.limboFont1), 45,
		.2f, .2f, colorMdBlue, "Allies", 0, 0, 3, &cgs.media.limboFont1);
	CG_Text_Paint_Ext(255 + CG_Text_Width_Ext("Axis", .2f, 0, &cgs.media.limboFont1) * .5f -
		CG_Text_Width_Ext(axis, .2f, 0, &cgs.media.limboFont1) * .5f, 55, .2f, .2f,
		TDMScoreColor(tdmAxisChanged, tdmAxisIncreased), axis, 0, 0, 3, &cgs.media.limboFont1);
	CG_Text_Paint_Ext(385 - CG_Text_Width_Ext("Allies", .2f, 0, &cgs.media.limboFont1) * .5f -
		CG_Text_Width_Ext(allies, .2f, 0, &cgs.media.limboFont1) * .5f, 55, .2f, .2f,
		TDMScoreColor(tdmAlliesChanged, tdmAlliesIncreased), allies, 0, 0, 3, &cgs.media.limboFont1);
	CG_FilledBar(240, 65, 80, 4, colorMdRed, NULL, NULL,
		CG_NitmodTDMProgress(state->teamScoreAxis, state->tdmScoreLimit), 0x51);
	CG_FilledBar(320, 65, 80, 4, colorMdBlue, NULL, NULL,
		CG_NitmodTDMProgress(state->teamScoreAllies, state->tdmScoreLimit), 0x50);
	CG_Text_Paint_Ext(320 - CG_Text_Width_Ext(limit, .2f, 0, &cgs.media.limboFont1) * .5f,
		60, .2f, .2f, colorWhite, limit, 0, 0, 3, &cgs.media.limboFont1);
	CG_NitmodHudAnchor(previous);
	return y;
}

void CG_NitmodFPSText(char *out, int size, int now, int samples) {
    int i;
    double delta, total = 0;
    if(!out || size <= 0) return;
    out[0] = 0;
    if(!samples) return;
    samples = samples < 4 ? 4 : samples > 500 ? 500 : samples;
    delta = (double)now - fpsPrevious;
    if(samples != fpsSamples || delta < 0 || delta > 2147483647.0) {
        fpsCursor = fpsCount = 0;
        fpsSamples = samples;
    }
    fpsPrevious = now;
    fpsTimes[fpsCursor] = delta < 0 || delta > 2147483647.0 ? 0 : (int)delta;
    fpsCursor = (fpsCursor + 1) % samples;
    if(fpsCount <= samples) ++fpsCount;
    if(fpsCount <= samples) {
        Q_strncpyz(out, "estimating", size);
        return;
    }
    for(i = 0; i < samples; ++i) total += fpsTimes[i];
    if(!total) total = 1;
    Com_sprintf(out, size, "%i FPS", (int)(samples * 1000 / total));
}

void CG_NitmodHudPingText(char *out, int size, int ping, int mode) {
    float displayed;
    if(!out || size <= 0) return;
    out[0] = 0;
    if(!mode) return;
    if(mode == 1) {
        Com_sprintf(out, size, "Ping %d", ping > 999 ? 999 : ping);
    } else {
        /* Original ELF 0x44e25..0x44e59: no persistent averaging state. */
        displayed = ((float)ping + 0.0f) * .5f;
        Com_sprintf(out, size, "Avg Ping %0.2f", (double)displayed);
    }
}

void CG_NitmodClockText(char *out, int size, const qtime_t *time, int mode, int seconds) {
    char suffix[8];
    int hour;
    if(!out || size <= 0) return;
    out[0] = 0;
    if(!time || !mode || time->tm_hour < 0 || time->tm_hour > 23 ||
       time->tm_min < 0 || time->tm_min > 59 || time->tm_sec < 0 || time->tm_sec > 60) return;
    suffix[0] = 0;
    if(seconds) Com_sprintf(suffix, sizeof(suffix), ":%02d", time->tm_sec);
    hour = time->tm_hour;
    if(mode != 1) { hour %= 12; if(!hour) hour = 12; }
    Com_sprintf(out, size, "%d:%02d%s%s", hour, time->tm_min, suffix,
        mode == 1 ? "" : time->tm_hour < 12 ? " am" : " pm");
}

void CG_NitmodSpeedText(char *out, int size, const vec3_t velocity, int now, int mode, int unit, int interval) {
    static const char *units[] = {"UPS", "KPH", "MPH"};
    double divisor;
    if(!out || size <= 0) return;
    out[0] = 0;
    if(!mode || !velocity) return;
    if(now < lastSample || (double)now - lastSample > interval) {
        speed = VectorLength(velocity);
        if(speed > highestSpeed) highestSpeed = speed;
        lastSample = now;
    }
    if(unit < 0 || unit > 2 || (mode != 1 && mode != 2)) return;
    divisor = unit == 1 ? 15.58 : unit == 2 ? 23.44 : 1;
    if(mode == 2) Com_sprintf(out, size, "%.1f %s (%.1f MAX)", speed / divisor, units[unit], highestSpeed / divisor);
    else Com_sprintf(out, size, "%.1f %s", speed / divisor, units[unit]);
}

static float DrawLine(float y, const char *text) {
    vec4_t background = { .16f, .2f, .17f, .8f }, border = { .5f, .5f, .5f, .5f };
    vec4_t color = { .625f, .625f, .6f, 1 };
    int width;
    if(!*text) return y;
    CG_NitmodHudColors(background, border);
    width = CG_Text_Width_Ext(text, .19f, 0, &cgs.media.limboFont1);
    CG_FillRect(632 - width, y, width + 5, 14, background);
    CG_DrawRect_FixedBorder(632 - width, y, width + 5, 14, 1, border);
    CG_Text_Paint_Ext(634 - width, y + 11, .19f, .19f, color, text, 0, 0, 0, &cgs.media.limboFont1);
    return y + 16;
}

float CG_NitmodHud(float y) {
    char text[96];
    qtime_t time;
    nitmodHudAnchor_t previous;
    if(!cg.snap) return y;
    previous = CG_NitmodHudAnchor(NITMOD_HUD_RIGHT);
    if(cg_drawPing.integer) {
        CG_NitmodHudPingText(text, sizeof(text), cg.snap->ping, cg_drawPing.integer);
        y = DrawLine(y, text);
    }
	y = CG_NitmodDrawTDMScore(y);
    if(cg_drawTime.integer) {
        memset(&time, 0, sizeof(time));
        trap_RealTime(&time);
        CG_NitmodClockText(text, sizeof(text), &time, cg_drawTime.integer, cg_drawTimeSeconds.integer);
        y = DrawLine(y, text);
    }
    if(cg_drawspeed.integer) {
        CG_NitmodSpeedText(text, sizeof(text), cg.predictedPlayerState.velocity, trap_Milliseconds(),
            cg_drawspeed.integer, cg_speedunit.integer, cg_speedinterval.integer);
        y = DrawLine(y, text);
    }
    CG_NitmodHudAnchor(previous);
    return y;
}
