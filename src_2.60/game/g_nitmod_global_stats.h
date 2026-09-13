#ifndef G_NITMOD_GLOBAL_STATS_H
#define G_NITMOD_GLOBAL_STATS_H
void G_NITMOD_GlobalStatsInit(void);
int G_NITMOD_GlobalStatsKillDeath(int client,int *kills,int *deaths);
void G_NITMOD_GlobalStatsShutdown(void);
void G_NITMOD_GlobalStatsReset(int client);
void G_NITMOD_GlobalStatsRequest(int client,const char *guid);
void G_NITMOD_GlobalStatsFrame(void);
void G_NITMOD_GlobalStatsEvent(int client,int statistic);
void G_NITMOD_GlobalStatsDeath(int victim,int attacker,int mod);
void G_NITMOD_GlobalStatsUpload(int client);
int G_NITMOD_GlobalStatsCommand(int client,const char *command);
#endif
