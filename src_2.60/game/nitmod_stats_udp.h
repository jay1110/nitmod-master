#ifndef NITMOD_STATS_UDP_H
#define NITMOD_STATS_UDP_H
int NITMOD_StatsUDPInit(const char *bindAddress);
int NITMOD_StatsUDPStart(int client,const char *guid);
int NITMOD_StatsUDPUpload(const char *packet);
void NITMOD_StatsUDPPoll(void);
int NITMOD_StatsUDPRead(int client,char *out,int size);
void NITMOD_StatsUDPCancel(int client);
void NITMOD_StatsUDPShutdown(void);
#endif
