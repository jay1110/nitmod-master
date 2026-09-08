#ifndef NITMOD_DATABASE_H
#define NITMOD_DATABASE_H
typedef struct {
    char name[64], guid[34], flags[1024], xp[1024];
    int level;
} nitmodDatabaseUser_t;
typedef struct {
    nitmodDatabaseUser_t user;
    char ip[19], gtext[1024], gsound[1024], mac[19], login[33], password[41];
    int timestamp;
} nitmodDatabaseAccount_t;
int NITMOD_DBOpenSnapshot(const void *bytes, int length);
int NITMOD_DBOpenWorking(const void *bytes, int length);
/* Roll back this cache without attaching a newly imported database to its old storage. */
int NITMOD_DBRestoreWorking(const void *bytes,int length);
/* Validates the replacement first; keeps account/session identity on success and failure. */
int NITMOD_DBInstallWorking(const void *bytes,int length);
unsigned int NITMOD_DBWorkingGeneration(void);
int NITMOD_DBInitSchema(int mailEnabled, int recordsEnabled);
/* Caller owns exported bytes and releases them with NITMOD_DBFreeExport. */
void *NITMOD_DBExport(int *length);
void NITMOD_DBFreeExport(void *bytes);
void NITMOD_DBClose(void);
int NITMOD_DBUser(const char *guid,nitmodDatabaseUser_t *result);
int NITMOD_DBAccount(const char *guid,nitmodDatabaseAccount_t *result);
int NITMOD_DBAccountAt(int index,nitmodDatabaseAccount_t *result);
/* Original UserID is the final eight NGUID characters. Ambiguity is an error. */
int NITMOD_DBAccountByID(const char *id,nitmodDatabaseAccount_t *result);
/* Original save modes: 0 delete, 1 add/update, 2 update/add. */
int NITMOD_DBSaveAccount(const nitmodDatabaseAccount_t *account,int mode);
int NITMOD_DBMigrateUserLevel(int from,int to);
int NITMOD_DBClearXP(void);
/* Mail results: 1 success, 0 recipient/mail missing, -1 database error. */
int NITMOD_DBMailSend(const char *sender,const char *recipient,const char *message);
int NITMOD_DBMailDelete(const char *recipient,int id);
typedef void (*nitmodMailVisitor_t)(void *context,int id,const char *sender,const char *message);
int NITMOD_DBMails(const char *recipient,nitmodMailVisitor_t visit,void *context);
typedef struct {
    char name[64],guid[34],ip[19],mac[19],reason[1024],made[50],actor[64];
    int expires; /* original ban/mute time base: Unix seconds - 946490400 */
} nitmodDatabasePenalty_t;
int NITMOD_DBPenaltySave(int mute,const nitmodDatabasePenalty_t *penalty,int add);
int NITMOD_DBPenaltyAt(int mute,int index,nitmodDatabasePenalty_t *penalty);
int NITMOD_DBPenaltyCheck(int mute,const char *ip,const char *guid,const char *mac,
    int now,nitmodDatabasePenalty_t *result,int *expired);
/* Same match/expiry rules as Check, without mutating expired rows. */
int NITMOD_DBPenaltyPeek(int mute,const char *ip,const char *guid,const char *mac,
    int now,nitmodDatabasePenalty_t *result,int *expired);
typedef struct {
    char map[65],holder[3][64],date[3][32];
    int value[3]; /* spree, frags, revive spree */
} nitmodDatabaseRecords_t;
int NITMOD_DBRecords(const char *map,nitmodDatabaseRecords_t *result);
/* Returns changed-category bits, or -1 on failure. New maps insert all fields. */
int NITMOD_DBUpdateRecords(const nitmodDatabaseRecords_t *records);
int NITMOD_DBClearRecords(const char *map); /* NULL clears all maps */
int NITMOD_DBUserCount(void);
int NITMOD_DBVersion(void);
unsigned int NITMOD_DBEpoch(void);
void *NITMOD_DBMergeImages(const void *before,int beforeLength,const void *changed,int changedLength,
                         const void *current,int currentLength,int *length);
int NITMOD_DBSyncUser(const void *current,int length,const char *guid);
int NITMOD_DBStorageOpen(const char *path);
void NITMOD_DBStorageClose(void);
void *NITMOD_DBStorageRead(int *length);
int NITMOD_DBStorageCommit(const void *before,int length);
void *NITMOD_DBImageSyncUser(const void *cache,int cacheLength,const void *current,int currentLength,const char *guid,int *length);
void *NITMOD_DBImageOrigin(const void *image,int imageLength,int *length);
void *NITMOD_DBImageSetOrigin(const void *image,int imageLength,const void *origin,int originLength,int *length);
int NITMOD_DBStorageInitSchema(int mail,int records);
void *NITMOD_DBImageInitialize(const void *image,int imageLength,int mail,int records,int *length);
void *NITMOD_DBMergeUserImages(const void *before,int beforeLength,const void *changed,int changedLength,
                         const void *current,int currentLength,const char *guid,int *length);
const char *NITMOD_DBError(void);
#endif
