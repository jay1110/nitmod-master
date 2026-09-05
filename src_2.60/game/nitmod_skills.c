#include <string.h>
#include <float.h>
#include "nitmod_protocol.h"
#include "nitmod_skills.h"

int NITMOD_SelectSkillTable( const float row[NITMOD_SKILL_LEVEL_COUNT],
	unsigned int unlocked, float *output ) {
	float value;
	int level;
	if( !row || !output ) return 0;
	for( level = 0; level < NITMOD_SKILL_LEVEL_COUNT; level++ ) {
		if( !(row[level] >= -FLT_MAX && row[level] <= FLT_MAX) ) return 0;
	}
	value = row[0];
	for( level = 1; level < NITMOD_SKILL_LEVEL_COUNT; level++ ) {
		if( row[level] != row[level - 1] && (unlocked & (1u << level)) ) {
			value = row[level];
		}
	}
	*output = value;
	return 1;
}

int NITMOD_GameplayTableValue( nitmodSkillTable_t table,
	unsigned int unlocked, float *output ) {
	/* Read-only ELF data, qagame i386 0x2a4f64..0x2a5143.
	 * Keep decimal float literals: these reproduce the original binary32 bits. */
	static const float rows[NITMOD_TABLE_COUNT][NITMOD_SKILL_LEVEL_COUNT] = {
		{ .75f, .75f, .75f, .75f, .75f, .75f }, /* Tripmine */
		{ .5f, .33f, .33f, .33f, .33f, .33f }, /* Mortar */
		{ 1, .66f, .66f, .66f, .66f, .66f }, /* Panzer */
		{ 1, 1, .66f, .66f, .66f, .66f }, /* Artillery */
		{ 1, 1, 1, 1, 1, 1 }, /* Adrenaline */
		{ .25f, .15f, .15f, .15f, .15f, .15f }, /* Ammo */
		{ .25f, .15f, .15f, .15f, .15f, .15f }, /* Health */
		{ 1, 1, .66f, .66f, .66f, .66f }, /* Smoke */
		{ 1, 1, .66f, .66f, .66f, .66f }, /* Satchel */
		{ .5f, .5f, .5f, .5f, .5f, .5f }, /* Riflenade */
		{ 1, 1, 1, .66f, .66f, .66f }, /* Dynamite */
		{ .5f, .5f, .5f, .33f, .33f, .33f }, /* Landmine */
		{ 1, 1, .66f, .66f, .66f, .66f }, /* Construct */
		{ 1, 1, 1, .66f, .66f, .66f }, /* Repair */
		{ 3, 3, 3, 3, 3, 3 }, /* Disarm satchel */
		{ 5, 5, 5, 9, 9, 9 }, /* Artillery bombs */
		{ 3, 3, 6, 6, 6, 6 }, /* Disarm landmine */
		{ 3, 3, 6, 6, 6, 6 }, /* Disarm dynamite */
		{ 7, 7, 14, 14, 14, 14 }, /* Arm dynamite */
		{ 12, 12, 24, 24, 24, 24 } /* Arm landmine */
	};
	if( (int)table < 0 || table >= NITMOD_TABLE_COUNT ) return 0;
	return NITMOD_SelectSkillTable(rows[table], unlocked, output);
}

int NITMOD_ParseRank(const char *text, int *output) {
	int rank;
	if(!output || !NITMOD_ParseProtocolInteger(text, &rank) || rank >= NITMOD_RANK_COUNT) return 0;
	*output = rank;
	return 1;
}

int NITMOD_CalculateRank( const int levels[NITMOD_SKILL_COUNT], int *output ) {
	/* Original rankTable has eleven entries, but both functions read only
	 * indices 0..9. The trailing value 20 does NOT introduce rank eleven. */
	static const int thresholds[10] = { 1, 2, 3, 4, 5, 7, 9, 11, 14, 17 };
	int skill, total = 0, rank = 0;
	if( !levels || !output ) return 0;
	for( skill = 0; skill < NITMOD_SKILL_COUNT; skill++ ) {
		if( levels[skill] < 0 || levels[skill] >= NITMOD_SKILL_LEVEL_COUNT ) return 0;
		total += levels[skill];
	}
	while( rank < 10 && total >= thresholds[rank] ) rank++;
	*output = rank;
	return 1;
}

int NITMOD_CalculateSkillLoss( const nitmodSkillThresholds_t *thresholds, int skill,
	float currentPoints, float loss, int maxLevels, int upgradesDisabled,
	nitmodSkillLoss_t *output ) {
	nitmodSkillLoss_t next;
	double points, removed;
	/* Reject non-finite/overflowing transactions before changing any output.
	 * Negative loss remains supported: the original subtracts it as supplied. */
	if( !output || !(currentPoints >= -FLT_MAX && currentPoints <= FLT_MAX) ||
		!(loss >= -FLT_MAX && loss <= FLT_MAX) ) return 0;
	points = (double)currentPoints - loss;
	if( points < -FLT_MAX || points > FLT_MAX ) return 0;
	next.points = (float)points;
	removed = (double)currentPoints - next.points;
	if( removed < -FLT_MAX || removed > FLT_MAX ) return 0;
	next.removed = (float)removed;
	if( !NITMOD_EvaluateSkill(thresholds, skill, next.points, maxLevels,
		upgradesDisabled, &next.progress) ) return 0;
	*output = next;
	return 1;
}

int NITMOD_ParseSkillDigits( const char *text, int maxLevel, int output[NITMOD_SKILL_COUNT] ) {
	int next[NITMOD_SKILL_COUNT];
	int skill;
	if( !text || !output || maxLevel < 0 || maxLevel > 9 ) return 0;
	for( skill = 0; skill < NITMOD_SKILL_COUNT; skill++ ) {
		/* Stop at NUL immediately; short Info strings must not be overread. */
		if( text[skill] < '0' || text[skill] > '0' + maxLevel ) return 0;
		next[skill] = text[skill] - '0';
	}
	if( text[NITMOD_SKILL_COUNT] ) return 0;
	memcpy( output, next, sizeof(next) );
	return 1;
}

int NITMOD_EvaluateSkill( const nitmodSkillThresholds_t *thresholds, int skill,
	float points, int maxLevels, int upgradesDisabled, nitmodSkillProgress_t *output ) {
	nitmodSkillProgress_t next;
	int level;
	if( !thresholds || !output || skill < 0 || skill >= NITMOD_SKILL_COUNT ) return 0;
	next.level = 0;
	next.unlocked = 0;
	if( maxLevels > NITMOD_SKILL_LEVEL_COUNT ) maxLevels = NITMOD_SKILL_LEVEL_COUNT;
	if( !upgradesDisabled ) {
		for( level = 1; level < maxLevels; level++ ) {
			int threshold = thresholds->threshold[skill][level];
			if( threshold >= 0 && points >= (float)threshold ) {
				next.level = level;
				next.unlocked |= 1u << level;
			}
		}
	}
	*output = next;
	return 1;
}

void NITMOD_DefaultSkillThresholds( nitmodSkillThresholds_t *output ) {
	static const int defaults[NITMOD_SKILL_LEVEL_COUNT] = { 0, 20, 50, 90, 140, 200 };
	int skill;
	if( !output ) return;
	for( skill = 0; skill < NITMOD_SKILL_COUNT; skill++ ) {
		memcpy( output->threshold[skill], defaults, sizeof(defaults) );
	}
}

int NITMOD_ParseSkillThresholdRow( const char *text, int *row ) {
	char token[256];
	int next[NITMOD_SKILL_LEVEL_COUNT];
	int length = 0, position = 0, level, size;
	if( !text || !row ) return 0;
	while( length < 256 && text[length] ) length++;
	if( length == 256 ) return 0;
	next[0] = 0;
	for( level = 1; level < NITMOD_SKILL_LEVEL_COUNT; level++ ) {
		while( position < length && (text[position] == ' ' || text[position] == ',') ) position++;
		size = 0;
		while( position < length && text[position] != ' ' && text[position] != ',' ) {
			token[size++] = text[position++];
		}
		token[size] = '\0';
		if( !NITMOD_ParseProtocolSigned( token, &next[level] ) ) return 0;
	}
	while( position < length && (text[position] == ' ' || text[position] == ',') ) position++;
	if(position != length) return 0;
	memcpy(row, next, sizeof(next));
	return 1;
}

int NITMOD_ParseSkillThresholds( nitmodSkillValue_t read, void *context,
	nitmodSkillThresholds_t *output ) {
	/* Native skill enum order: battle sense, engineering, first aid,
	 * signals, light weapons, heavy weapons, covert ops. */
	static const char *keys[NITMOD_SKILL_COUNT] = { "B", "E", "M", "F", "L", "S", "C" };
	nitmodSkillThresholds_t next;
	int skill;
	if( !read || !output ) return 0;
	for( skill = 0; skill < NITMOD_SKILL_COUNT; skill++ ) {
		if( !NITMOD_ParseSkillThresholdRow( read(context, keys[skill]), next.threshold[skill] ) ) return 0;
	}
	*output = next;
	return 1;
}
