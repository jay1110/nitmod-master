#ifndef NITMOD_SKILLS_H
#define NITMOD_SKILLS_H

/* Original Nitmod matrix, deliberately separate from ET's five-level ABI. */
#define NITMOD_SKILL_COUNT 7
#define NITMOD_SKILL_LEVEL_COUNT 6
#define NITMOD_RANK_COUNT 11
/* Original six-entry gameplay tables. These use independent unlock bits,
 * never a numeric ET skill level. Shared by future server/prediction adapters. */
typedef enum {
	NITMOD_TABLE_TRIPMINE, NITMOD_TABLE_MORTAR, NITMOD_TABLE_PANZER,
	NITMOD_TABLE_ARTILLERY, NITMOD_TABLE_ADRENALINE, NITMOD_TABLE_AMMO,
	NITMOD_TABLE_HEALTH, NITMOD_TABLE_SMOKE, NITMOD_TABLE_SATCHEL,
	NITMOD_TABLE_RIFLENADE, NITMOD_TABLE_DYNAMITE, NITMOD_TABLE_LANDMINE,
	NITMOD_TABLE_CONSTRUCT, NITMOD_TABLE_REPAIR, NITMOD_TABLE_DISARM_SATCHEL,
	NITMOD_TABLE_ARTILLERY_BOMBS, NITMOD_TABLE_DISARM_LANDMINE,
	NITMOD_TABLE_DISARM_DYNAMITE, NITMOD_TABLE_ARM_DYNAMITE,
	NITMOD_TABLE_ARM_LANDMINE, NITMOD_TABLE_COUNT
} nitmodSkillTable_t;
/* Atomic on invalid arguments/non-finite data. Bits outside 1..5 are ignored.
 * An unlocked row only takes effect if it differs from the PREVIOUS ROW,
 * not from the accumulated result (original BG_GetFromTable semantics). */
int NITMOD_SelectSkillTable( const float row[NITMOD_SKILL_LEVEL_COUNT],
	unsigned int unlocked, float *output );
int NITMOD_GameplayTableValue( nitmodSkillTable_t table,
	unsigned int unlocked, float *output );
/* Wire/player-info rank. Invalid text leaves the destination unchanged. */
int NITMOD_ParseRank(const char *text, int *output);
/* Numeric section shared by original G_CalcRank/G_UpgradeSkill.
 * Does not recalculate XP, invoke Lua or award abilities. Atomic on error. */
int NITMOD_CalculateRank( const int levels[NITMOD_SKILL_COUNT], int *output );
typedef struct {
	int threshold[NITMOD_SKILL_COUNT][NITMOD_SKILL_LEVEL_COUNT];
} nitmodSkillThresholds_t;
typedef struct {
	int level;
	unsigned int unlocked;
} nitmodSkillProgress_t;
typedef struct {
	float points;
	float removed;
	nitmodSkillProgress_t progress;
} nitmodSkillLoss_t;
/* Numeric Nitmod loss transaction: unlike ET, does not retain the old level.
 * Caller owns gamestate/team guards, Lua hooks and score/team-XP updates. */
int NITMOD_CalculateSkillLoss( const nitmodSkillThresholds_t *thresholds, int skill,
	float currentPoints, float loss, int maxLevels, int upgradesDisabled,
	nitmodSkillLoss_t *output );
/* maxLevels counts level zero: 1 disables upgrades, 6 permits level five.
 * Negative thresholds disable individual bits, not later levels. */
int NITMOD_EvaluateSkill( const nitmodSkillThresholds_t *thresholds, int skill,
	float points, int maxLevels, int upgradesDisabled, nitmodSkillProgress_t *output );
typedef const char *(*nitmodSkillValue_t)( void *context, const char *key );

void NITMOD_DefaultSkillThresholds( nitmodSkillThresholds_t *output );
int NITMOD_ParseSkillThresholdRow( const char *text,
	int row[NITMOD_SKILL_LEVEL_COUNT] );
/* Native CS_PLAYERS s field: exactly seven one-digit levels. The caller
 * supplies its supported maximum; rejection leaves all output unchanged. */
int NITMOD_ParseSkillDigits( const char *text, int maxLevel, int output[NITMOD_SKILL_COUNT] );
/* Reader consumes sl Info-string keys. All seven rows must be valid before
 * output changes. No native playerState/UI level arrays are modified. */
int NITMOD_ParseSkillThresholds( nitmodSkillValue_t read, void *context,
	nitmodSkillThresholds_t *output );

#endif
