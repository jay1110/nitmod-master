#ifndef CG_NITMOD_HUDSTATS_H
#define CG_NITMOD_HUDSTATS_H
void CG_NitmodResetNativeHudStats(void);
qboolean CG_NitmodNativeHudStatsCommand(const char *command);
void CG_NitmodCaptureNativeHudStats(const snapshot_t *snapshot);
qboolean CG_NitmodNativeHudStat(const playerState_t *state,int row,int *value);
#endif
