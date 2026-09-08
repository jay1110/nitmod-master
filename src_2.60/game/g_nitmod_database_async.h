#ifndef G_NITMOD_DATABASE_ASYNC_H
#define G_NITMOD_DATABASE_ASYNC_H
#include "g_nitmod_database.h"
int G_NITMOD_DBAsyncSupported(void);
int G_NITMOD_DBAsyncActive(void);
int G_NITMOD_DBAsyncStart(const char *path,void *initial,int length);
void G_NITMOD_DBAsyncReset(void);
int G_NITMOD_DBAsyncSubmit(void *base,int baseLength,void *changed,int changedLength,nitmodDbCompletion_t done,const void *context,int contextLength);
int G_NITMOD_DBAsyncUser(const char *guid,int sync,nitmodDbCompletion_t done,const void *context,int contextLength);
int G_NITMOD_DBAsyncSaveAs(const char *path,void *base,int baseLength,void *changed,int changedLength,nitmodDbCompletion_t done,const void *context,int contextLength);
/* Owner adapter: preserve identity and update only acknowledged baselines. */
int G_NITMOD_DatabaseAcceptImage(const void *image,int length);
int G_NITMOD_DatabaseAcceptUser(const void *image,int length,const char *guid);
void G_NITMOD_DatabaseAcceptPath(const char *path);
#endif
