#ifndef G_NITMOD_DATABASE_H
#define G_NITMOD_DATABASE_H
void G_NITMOD_LoadDatabase(void);
void G_NITMOD_DatabaseStatus(void);
int G_NITMOD_DatabaseSaveAs(const char *path);
int G_NITMOD_DatabaseMigrateLevel(int from,int to,const char *newPath);
int G_NITMOD_DatabaseFlush(void);
int G_NITMOD_DatabaseSyncUser(const char *guid);
void G_NITMOD_DatabaseShutdown(void);
/* Completion is called exactly once, including synchronous failure/native
 * completion. Context bytes are copied for queued calls. Return: 0 failed,
 * 1 completed successfully, 2 pending. Side effects belong in completion. */
typedef void (*nitmodDbCompletion_t)(int success,const void *context);
/* Always consumes the SQLite-export BEFORE, captures current AFTER itself,
 * and immediately restores BEFORE while the host commit is pending. */
int G_NITMOD_DatabaseCommit(void *before,int length,nitmodDbCompletion_t done,const void *context,int contextLength);
/* Consumes both SQLite-export images. Useful for a targeted inverse change:
 * submit the original AFTER as base and original BEFORE as changed. */
int G_NITMOD_DatabaseSubmitImages(void *base,int baseLength,void *changed,int changedLength,nitmodDbCompletion_t done,const void *context,int contextLength);
int G_NITMOD_DatabaseSyncUserAsync(const char *guid,nitmodDbCompletion_t done,const void *context,int contextLength);
int G_NITMOD_DatabaseSaveAsAsync(const char *path,nitmodDbCompletion_t done,const void *context,int contextLength);
int G_NITMOD_DatabaseMigrateLevelAsync(int from,int to,const char *path,nitmodDbCompletion_t done,const void *context,int contextLength);
void G_NITMOD_DatabaseThink(void);
int G_NITMOD_DatabasePending(void);
int G_NITMOD_DatabaseReady(void);
/* Stops new submissions; 1 means drained, 2 means still pending. */
int G_NITMOD_DatabaseDrain(void);
#endif
