#ifndef CG_NITMOD_STATS_H
#define CG_NITMOD_STATS_H

#define NITMOD_GLOBAL_STAT_COUNT 15

void CG_NitmodGlobalStatsReset(void);
void CG_NitmodGlobalStats_f(void);
qboolean CG_NitmodGlobalStatsCommand(void);
qboolean CG_NitmodDrawGlobalStats(void);
qboolean CG_NitmodGlobalAwardCommand(void);
void CG_NitmodDrawGlobalAward(void);
void CG_NitmodGlobalAwardClear(void);
const char *CG_NitmodGlobalAwardTitle(int award);
const char *CG_NitmodGlobalAwardDescription(int award);
qboolean CG_NitmodParseGlobalStats(int argc, const char *(*argv)(int),
	int values[NITMOD_GLOBAL_STAT_COUNT], qboolean *failed);

#endif
