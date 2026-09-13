#ifndef NITMOD_STATS_TRANSPORT_H
#define NITMOD_STATS_TRANSPORT_H
int NITMOD_StatsStart(int client,const char *url,const char *guid);
int NITMOD_StatsRead(int client,char *out,int size);
void NITMOD_StatsCancel(int client);
void NITMOD_StatsShutdown(void);
int NITMOD_StatsUpload(const char *url,const char *packet);
#endif
