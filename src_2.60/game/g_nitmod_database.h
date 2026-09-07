#ifndef G_NITMOD_DATABASE_H
#define G_NITMOD_DATABASE_H
void G_NITMOD_LoadDatabase(void);
void G_NITMOD_DatabaseStatus(void);
int G_NITMOD_DatabaseSaveAs(const char *path);
int G_NITMOD_DatabaseMigrateLevel(int from,int to,const char *newPath);
int G_NITMOD_DatabaseFlush(void);
void G_NITMOD_DatabaseShutdown(void);
#endif
