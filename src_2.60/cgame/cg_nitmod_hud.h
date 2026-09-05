#ifndef CG_NITMOD_HUD_H
#define CG_NITMOD_HUD_H

typedef enum { NITMOD_HUD_STRETCH = -1, NITMOD_HUD_CENTER, NITMOD_HUD_LEFT, NITMOD_HUD_RIGHT } nitmodHudAnchor_t;
nitmodHudAnchor_t CG_NitmodHudAnchor(nitmodHudAnchor_t anchor);
qboolean CG_NitmodAdjustHud(float *x, float *y, float *w, float *h);
extern vmCvar_t cg_drawPing, cg_drawTime, cg_drawTimeSeconds;
extern vmCvar_t cg_spawnTimer_set, cg_spawnTimer_period;
void CG_NitmodResetTimer(void);
void CG_NitmodTimerSet(void);
void CG_NitmodSpawnTimerText(char *out, int size, int seconds, int start, int period, const char *timer);
void CG_NitmodMatchTimerText(char *out, int size, int msec, qboolean limited, qboolean playing, const char *reinforcement);
void CG_NitmodRoundTimerText(char *out, int size, float *alpha);
extern vmCvar_t cg_drawspeed, cg_speedunit, cg_speedinterval;
extern vmCvar_t cg_HUDBackgroundColor, cg_HUDBorderColor, cg_HUDAlpha;
extern vmCvar_t cg_notificationTime, cg_notificationFadeTime;
void CG_NitmodNotificationStart(const char *text, int now);
const char *CG_NitmodNotificationText(void);
qboolean CG_NitmodNotificationActive(void);
float CG_NitmodNotificationAlpha(int now, float hold, float fade);
void CG_NitmodDrawNotification(void);
qboolean CG_NitmodKillPrint(const char *text, qboolean teammate, int now);
const char *CG_NitmodKillPrintText(void);
float CG_NitmodKillPrintAlpha(int now);
void CG_NitmodDrawKillPrint(void);
qboolean CG_NitmodDrawAmmo(int weapon, int clip, int reserve, int akimbo);
const char *CG_NitmodSpreeLabel(int type, int detail);
qboolean CG_NitmodSpreeStart(int actor, int detail, int type);
void CG_NitmodDrawSpree(void);
qboolean CG_NitmodSpreeUsesLeft(void);
void CG_NitmodRegisterSpreeSounds(void);
qboolean CG_NitmodSpecialAnnouncement(int type, int xp);
void CG_NitmodHealthBonus(int amount);
const char *CG_NitmodSpecialText(void);
qboolean CG_NitmodSpecialFrame(int now, float *scale, vec4_t color);
void CG_NitmodDrawSpecial(void);
extern vmCvar_t cg_announcer;
void CG_NitmodRegisterAnnouncerSounds(void);
void CG_NitmodAnnounce(int type);
void CG_NitmodAddAnnouncer(const char *text, sfxHandle_t sound, float scale,
    int duration, float red, float green, float blue, int animation, int yOffset);
qboolean CG_NitmodAnnouncerFrame(int now, float *scale, vec4_t color);
const char *CG_NitmodAnnouncerText(void);
void CG_NitmodDrawAnnouncer(void);
void CG_NitmodPrintAnnouncement(const char *text, int y, int charWidth, int priority);
const char *CG_NitmodAnnouncementText(void);
void CG_NitmodDrawAnnouncement(void);
void CG_NitmodDrawCenterPrint(void);
qboolean CG_NitmodParseHudColor(const char *text, float alpha, vec4_t color);
void CG_NitmodHudColors(vec4_t background, vec4_t border);
void CG_NitmodHudReset(void);
void CG_NitmodDrawSpectatorInstruction(int row, const char *text);
void CG_NitmodDrawWoundedInstruction(int row, const char *text);
qboolean CG_NitmodDrawFollow(void);
extern vmCvar_t cg_drawHUDStats;
/* Original wire persistant slots; never use these as native PERS_* aliases. */
enum { NITMOD_PERS_KILLS = 3, NITMOD_PERS_DEATHS = 4,
       NITMOD_PERS_HEADSHOTS = 5, NITMOD_PERS_BODYSHOTS = 6,
       NITMOD_PERS_KILLSPREE = 15 };
void CG_NitmodLiveStatsTransition(const playerState_t *oldState, const playerState_t *newState);
qboolean CG_NitmodLiveStatsText(const playerState_t *state, int row, int now, char *out, int size);
void CG_NitmodDrawLiveStats(void);
int CG_NitmodDisplayXP(const playerState_t *state);
int CG_NitmodHudSkill(int playerClass, int row, const playerState_t *state);
void CG_NitmodDrawSkillLevels(void);
typedef struct {
    float health, stamina, charge;
    vec4_t staminaColor, chargeColor, powerColor;
    qboolean underwater;
} nitmodStatusBars_t;
qboolean CG_NitmodStatusBars(const playerState_t *state, int playerClass,
    qboolean underwater, int now, int breathDeadline, nitmodStatusBars_t *out);
void CG_NitmodDrawStatusBars(void);
void CG_NitmodDrawActivePowerups(void);
void CG_NitmodRegisterPowerupMedia(void);
void CG_NitmodResetMaxSpeed(void);
void CG_NitmodHudPingText(char *out, int size, int ping, int mode);
void CG_NitmodFPSText(char *out, int size, int now, int samples);
void CG_NitmodClockText(char *out, int size, const qtime_t *time, int mode, int seconds);
void CG_NitmodSpeedText(char *out, int size, const vec3_t velocity, int now, int mode, int unit, int interval);
float CG_NitmodHud(float y);
void CG_NitmodTDMScoreChanged(int axis, int allies, int now);
float CG_NitmodTDMProgress(int score, int limit);
float CG_NitmodDrawTDMScore(float y);
#endif
