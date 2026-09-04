#ifndef CG_NITMOD_SCOREBOARD_H
#define CG_NITMOD_SCOREBOARD_H

/* Private presentation state, not a network or engine structure. */
typedef struct {
    int x, y, width, height, maxChars;
    char text[MAX_NAME_LENGTH + 64];
} nitmodScoreText_t;
typedef struct {
    float x, y, width, height;
    qhandle_t shader;
} nitmodScoreIcon_t;
typedef struct {
    nitmodScoreText_t text[5];
    nitmodScoreIcon_t icons[6];
    int textCount, iconCount;
    qboolean highlight, country;
    int countryCode;
    float countryX, countryY;
} nitmodScoreRow_t;

qboolean CG_NitmodScoreRow(int x, int y, const score_t *score,
    qboolean compact, qboolean lives, nitmodScoreRow_t *row);
void CG_NitmodDrawScoreRow(int x, int y, const score_t *score,
    float fade, qboolean compact, qboolean lives);
qboolean CG_NitmodDMScoreRow(int x, int y, const score_t *score, nitmodScoreRow_t *row);
void CG_NitmodDrawDMScoreRow(int x, int y, const score_t *score, float fade);
int CG_NitmodDMScoreboard(int x, int y, float fade, int maxrows, qboolean intermission);
#endif
