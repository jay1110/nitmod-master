#include "g_local.h"
#include "g_nitmod_database_async.h"
#include "g_nitmod_legacy_cvars.h"
#include "nitmod_database.h"
/* Only the active operation owns a host request. Later operations retain
 * immutable base/change images and copied callback data, never client pointers. */
typedef struct dbAsyncOp_s {
    struct dbAsyncOp_s *next;
    int kind,phase,token,revision,retries,sync;
    void *base,*changed,*merged,*context;
    int baseLength,changedLength,mergedLength,contextLength;
    char path[MAX_QPATH],guid[64];
    nitmodDbCompletion_t done;
} dbAsyncOp_t;
static dbAsyncOp_t *first,*last;
static char activePath[MAX_QPATH];
static int active,ready,draining,count,inCallback,pathChanging;
static unsigned int queuedBytes;
/* Two account operations per slot plus boot/map-clear work; byte-budget
 * remains independent so 64 simultaneous joins fit without unbounded images. */
enum { DB_BOOT=1,DB_COMMIT,DB_USER,DB_SAVEAS };
#if defined(__EMSCRIPTEN__) || defined(NITMOD_DATABASE_ASYNC_TEST)
int trap_NITMOD_DatabaseStorage(int op,int token,const char *path,int revision,void *buffer,int length);
#define Host trap_NITMOD_DatabaseStorage
#else
static int Host(int op,int token,const char *path,int revision,void *buffer,int length) { return op==0?0:-1; }
#endif
static int CompleteNow(int success,nitmodDbCompletion_t done,const void *context) {
    if(done) { ++inCallback; done(success,context); --inCallback; }
    return success?1:0;
}
static void FreeOp(dbAsyncOp_t *op) {
    NITMOD_DBFreeExport(op->base); NITMOD_DBFreeExport(op->changed); NITMOD_DBFreeExport(op->merged);
    free(op->context); free(op);
}
static void Finish(int success) {
    dbAsyncOp_t *op=first; nitmodDbCompletion_t done; void *context;
    if(!op) return;
    if(op->token) { Host(5,op->token,0,0,0,0); op->token=0; }
    first=op->next; if(!first) last=0; --count;
    queuedBytes-=(unsigned int)op->baseLength+(unsigned int)op->changedLength;
    done=op->done; context=op->context; op->context=0;
    if(op->kind==DB_BOOT) ready=success?1:-1;
    if(op->kind==DB_SAVEAS) pathChanging=0;
    FreeOp(op);
    CompleteNow(success,done,context); free(context);
}
static dbAsyncOp_t *NewOp(int kind,void *base,int baseLength,void *changed,int changedLength,
    nitmodDbCompletion_t done,const void *context,int contextLength) {
    dbAsyncOp_t *op=0;
    if(!active || ready<0 || pathChanging || (draining && !inCallback) || count>=2*MAX_CLIENTS+16 || contextLength<0 || contextLength>65536 ||
       (contextLength && !context) || baseLength<0 || changedLength<0 ||
       (baseLength && !base) || (changedLength && !changed) ||
       (unsigned int)baseLength+(unsigned int)changedLength>128U*1024U*1024U-queuedBytes) goto failed;
    op=calloc(1,sizeof(*op)); if(!op) goto failed;
    if(contextLength) { op->context=malloc(contextLength); if(!op->context) goto failed; memcpy(op->context,context,contextLength); }
    op->kind=kind; op->base=base; op->baseLength=baseLength; op->changed=changed;
    op->changedLength=changedLength; op->done=done; op->contextLength=contextLength;
    if(last) last->next=op; else first=op; last=op; ++count;
    queuedBytes+=(unsigned int)baseLength+(unsigned int)changedLength;
    return op;
failed:
    if(op) { free(op->context); free(op); }
    NITMOD_DBFreeExport(base); NITMOD_DBFreeExport(changed);
    CompleteNow(0,done,context); return 0;
}
int G_NITMOD_DBAsyncSupported(void) { return Host(0,0,0,0,0,0)==1; }
int G_NITMOD_DBAsyncActive(void) { return active; }
void G_NITMOD_DBAsyncReset(void) {
    if(first) { G_LogPrintf("[SQLite] Refusing reset with pending database operations\n"); return; }
    active=ready=draining=count=pathChanging=0; queuedBytes=0; activePath[0]=0;
}
int G_NITMOD_DBAsyncStart(const char *path,void *initial,int length) {
    dbAsyncOp_t *op;
    if(first || !path || !*path || !initial || length<100) { NITMOD_DBFreeExport(initial); return 0; }
    active=1; ready=draining=0; Q_strncpyz(activePath,path,sizeof(activePath));
    op=NewOp(DB_BOOT,0,0,initial,length,0,0,0);
    if(!op) { ready=-1; return 0; }
    return 2;
}
int G_NITMOD_DBAsyncSubmit(void *base,int baseLength,void *changed,int changedLength,
    nitmodDbCompletion_t done,const void *context,int contextLength) {
    return NewOp(DB_COMMIT,base,baseLength,changed,changedLength,done,context,contextLength)?2:0;
}
int G_NITMOD_DBAsyncUser(const char *guid,int sync,nitmodDbCompletion_t done,const void *context,int contextLength) {
    dbAsyncOp_t *op;
    if(!guid || !*guid || strlen(guid)>=64) return CompleteNow(0,done,context);
    op=NewOp(DB_USER,0,0,0,0,done,context,contextLength);
    if(!op) return 0; Q_strncpyz(op->guid,guid,sizeof(op->guid)); op->sync=sync; return 2;
}
int G_NITMOD_DBAsyncSaveAs(const char *path,void *base,int baseLength,void *changed,int changedLength,
    nitmodDbCompletion_t done,const void *context,int contextLength) {
    dbAsyncOp_t *op;
    if(first) { NITMOD_DBFreeExport(base); NITMOD_DBFreeExport(changed); return CompleteNow(0,done,context); }
    op=NewOp(DB_SAVEAS,base,baseLength,changed,changedLength,done,context,contextLength);
    if(!op) return 0; pathChanging=1; Q_strncpyz(op->path,path,sizeof(op->path)); return 2;
}
int G_NITMOD_DatabasePending(void) { return count; }
int G_NITMOD_DatabaseReady(void) { return active?ready==1:1; }
int G_NITMOD_DatabaseDrain(void) { draining=1; return first?2:1; }
static void *HostImage(dbAsyncOp_t *op,int length) {
    void *bytes;
    if(length<100 || length>64*1024*1024) return 0;
    bytes=malloc(length); if(!bytes) return 0;
    if(Host(4,op->token,0,0,bytes,length)!=length) { free(bytes); return 0; }
    return bytes;
}
void G_NITMOD_DatabaseThink(void) {
    dbAsyncOp_t *op=first; int meta[2]={0,0},status,length; void *image=0,*normalized=0;
    nitmodDatabaseAccount_t account;
    if(!active || !op) return;
    if(ready<0) { Finish(0); return; }
    if(!op->token) {
        if(op->kind==DB_USER && (!op->sync || NITMOD_DBAccount(op->guid,&account)!=1)) { Finish(1); return; }
        op->token=Host(1,0,activePath,0,0,0);
        if(op->token<=0) { op->token=0; G_LogPrintf("[SQLite] Host read could not start\n"); Finish(0); }
        return;
    }
    status=Host(3,op->token,0,0,meta,sizeof(meta));
    if(status==0) return;
    if(status<0) { G_LogPrintf("[SQLite] Host transaction failed (%d)\n",status); Finish(0); return; }
    image=HostImage(op,meta[1]);
    if(status==2) {
        int ok=image && G_NITMOD_DatabaseAcceptImage(image,meta[1]);
        if(!ok) Com_Error(ERR_FATAL,"SQLite committed image cannot be installed; refusing divergent gameplay");
        if(op->kind==DB_SAVEAS && ok) {
            Q_strncpyz(activePath,op->path,sizeof(activePath)); G_NITMOD_DatabaseAcceptPath(activePath);
        }
        free(image); Finish(ok); return;
    }
    if(status==3) {
        free(image); Host(5,op->token,0,0,0,0); op->token=0;
        if(op->kind==DB_SAVEAS || ++op->retries>8) {
            G_LogPrintf("[SQLite] Host revision conflict; operation refused\n"); Finish(0);
        }
        return;
    }
    if(status!=1) { free(image); Finish(0); return; }
    op->revision=meta[0];
    if(op->kind==DB_USER) {
        int ok=image && G_NITMOD_DatabaseAcceptUser(image,meta[1],op->guid);
        free(image); Finish(ok); return;
    }
    NITMOD_DBFreeExport(op->merged); op->merged=0; op->mergedLength=0;
    if(op->kind==DB_BOOT && meta[0]==0 && meta[1]==0) {
        op->merged=NITMOD_DBImageInitialize(op->changed,op->changedLength,
            G_NITMOD_LegacyCvarInteger("n_userMail",0),G_NITMOD_LegacyCvarInteger("n_mapRecords",0),&op->mergedLength);
    } else if(image && meta[0]>0) {
        normalized=NITMOD_DBImageInitialize(image,meta[1],G_NITMOD_LegacyCvarInteger("n_userMail",0),
            G_NITMOD_LegacyCvarInteger("n_mapRecords",0),&length);
        if(op->kind==DB_BOOT) {
            if(normalized && length==meta[1] && !memcmp(normalized,image,length)) {
                int ok=G_NITMOD_DatabaseAcceptImage(normalized,length);
                NITMOD_DBFreeExport(normalized); free(image); Finish(ok); return;
            }
            op->merged=normalized; op->mergedLength=length; normalized=0;
        } else if(normalized) op->merged=NITMOD_DBMergeImages(op->base,op->baseLength,
            op->changed,op->changedLength,normalized,length,&op->mergedLength);
    }
    free(image); NITMOD_DBFreeExport(normalized);
    Host(5,op->token,0,0,0,0); op->token=0;
    if(!op->merged) { G_LogPrintf("[SQLite] Async merge refused: %s\n",NITMOD_DBError()); Finish(0); return; }
    op->token=Host(2,0,op->kind==DB_SAVEAS?op->path:activePath,
        op->kind==DB_SAVEAS?0:op->revision,op->merged,op->mergedLength);
    if(op->token<=0) { op->token=0; G_LogPrintf("[SQLite] Host commit could not start\n"); Finish(0); }
}
