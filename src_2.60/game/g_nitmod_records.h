#ifndef G_NITMOD_RECORDS_H
#define G_NITMOD_RECORDS_H
#include "nitmod_database.h"
int G_NITMOD_BestKillSpree(int clientNum);
void G_NITMOD_SaveMapRecords(void);
void G_NITMOD_PrintMapRecords(const nitmodDatabaseRecords_t *record,int flags);
#endif
