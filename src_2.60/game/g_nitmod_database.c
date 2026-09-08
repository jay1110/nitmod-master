#include "g_local.h"
#include "g_nitmod_legacy_cvars.h"
#include "g_nitmod_database.h"
#include "g_nitmod_database_async.h"
#include "nitmod_database.h"
#ifndef __EMSCRIPTEN__
#include <fcntl.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#endif
static char databaseRoot[MAX_QPATH],loadedPath[MAX_QPATH],nativePath[MAX_OSPATH];
static void *cacheBase,*sourceBase;
static int cacheLength,sourceLength,nativeStorage;
static unsigned int cacheGeneration;
static void CacheBaseline(void) {
    void *next; int length;
    next=NITMOD_DBExport(&length);
    if(next) { NITMOD_DBFreeExport(cacheBase); cacheBase=next; cacheLength=length; cacheGeneration=NITMOD_DBWorkingGeneration(); }
}
static void *ReadImage(const char *path,int *length) {
    fileHandle_t file=0; void *bytes=0; int n=trap_FS_FOpenFile(path,&file,FS_READ);
    *length=n;
    if(file && n>=100 && n<=64*1024*1024 && (bytes=malloc(n))) trap_FS_Read(bytes,n,file);
    if(file) trap_FS_FCloseFile(file);
    return bytes;
}
static int ValidRoot(const char *path) {
    return path && *path && strlen(path)<MAX_QPATH-20 && !strstr(path,"..") &&
        !strchr(path,':') && !strchr(path,'\\') && *path!='/' && strstr(path,".sqlite");
}
/* Immutable generations retain the imported database and every committed
 * version. A .pending image is never selected by the loader. */
static int Generation(char *latest,int *next) {
    static char list[65536]; /* qagame is single threaded; keep this off VM stack */
    char directory[MAX_QPATH],*p,*end; int count,i,max=0,committed=0;
    Com_sprintf(directory,sizeof(directory),"%s.d",databaseRoot);
    memset(list,0,sizeof(list)); count=trap_FS_GetFileList(directory,"",list,sizeof(list));
    p=list; end=list+sizeof(list); latest[0]=0;
    for(i=0;i<count;++i) {
        int n=0,j; size_t length;
        if(p>=end || !memchr(p,0,end-p)) return 0;
        length=strlen(p);
        if(length==15 || length==16) {
            for(j=0;j<8 && p[j]>='0' && p[j]<='9';++j) n=n*10+p[j]-'0';
            if(j==8 && (!strcmp(p+8,".sqlite") || !strcmp(p+8,".pending"))) {
                if(n>max) max=n;
                if(!strcmp(p+8,".sqlite") && n>committed) {
                    committed=n; Com_sprintf(latest,MAX_QPATH,"%s/%s",directory,p);
                }
            }
        }
        p+=length+1;
    }
    /* Refuse to save when the file list might have been truncated. */
    if(end-p<MAX_QPATH || max>=99999999) return 0;
    *next=max+1; return 1;
}
static int Matches(const char *path,const void *bytes,int length) {
    fileHandle_t file=0; int size=trap_FS_FOpenFile(path,&file,FS_READ),ok=0; void *check=0;
    if(file && size==length && (check=malloc(length))) {
        trap_FS_Read(check,length,file); ok=!memcmp(bytes,check,length);
    }
    if(file) trap_FS_FCloseFile(file); free(check); return ok;
}

/* A retained source image lets a later generation incorporate edits made to
 * the configured import file, even after a map/module restart. */
typedef struct {
    char path[MAX_QPATH]; void *head,*source; int headLength,sourceLength,sourceTracked;
} storageRead_t;
static void FreeRead(storageRead_t *read) { free(read->head); free(read->source); memset(read,0,sizeof(*read)); }
static void *ReadCurrent(storageRead_t *read,int *length) {
    int next,originLength=-1,headLength,baseLength,changedLength; void *origin=0,*out=0,*base=0,*changed=0,*normalized=0;
    memset(read,0,sizeof(*read)); read->sourceTracked=1;
    if(nativeStorage) return NITMOD_DBStorageRead(length);
    if(!Generation(read->path,&next)) return 0;
    read->source=ReadImage(databaseRoot,&read->sourceLength);
    if(!read->source && read->sourceLength>=0) goto done;
    if(!*read->path) Q_strncpyz(read->path,databaseRoot,sizeof(read->path));
    read->head=ReadImage(read->path,&read->headLength);
    if(!read->head) {
        if(read->headLength<0 && !read->source) out=NITMOD_DBExport(length);
        goto done;
    }
    normalized=NITMOD_DBImageInitialize(read->head,read->headLength,
        G_NITMOD_LegacyCvarInteger("n_userMail",0),G_NITMOD_LegacyCvarInteger("n_mapRecords",0),&headLength);
    if(!normalized) goto done;
    origin=NITMOD_DBImageOrigin(read->head,read->headLength,&originLength);
    if(originLength==0 && strcmp(read->path,databaseRoot)) {
        /* This database was created in the generation store without an
         * imported root.  A later same-named file is an independent database,
         * not an ancestor to merge silently into the active one. */
        read->sourceTracked=0; out=normalized; normalized=0; *length=headLength; goto done;
    }
    if(originLength<0) { originLength=sourceLength; }
    /* Old generation files have no ancestry.  Their first imported root is
     * retained from this load; future commits persist it in the generation. */
    { const void *old=origin?origin:sourceBase;
      int sourceNow=read->source?read->sourceLength:0;
      if(originLength!=sourceNow || (sourceNow && (!old || memcmp(old,read->source,sourceNow)))) {
          if(!old || !originLength || !read->source) {
              G_LogPrintf("[SQLite] Sync refused: source was removed or independently created\n"); goto done;
          }
          base=NITMOD_DBImageInitialize(old,originLength,G_NITMOD_LegacyCvarInteger("n_userMail",0),G_NITMOD_LegacyCvarInteger("n_mapRecords",0),&baseLength);
          changed=NITMOD_DBImageInitialize(read->source,read->sourceLength,G_NITMOD_LegacyCvarInteger("n_userMail",0),G_NITMOD_LegacyCvarInteger("n_mapRecords",0),&changedLength);
          if(base && changed) out=NITMOD_DBMergeImages(base,baseLength,changed,changedLength,normalized,headLength,length);
      } else { out=normalized; normalized=0; *length=headLength; }
    }
done:
    NITMOD_DBFreeExport(origin); NITMOD_DBFreeExport(normalized); NITMOD_DBFreeExport(base); NITMOD_DBFreeExport(changed);
    return out;
}
static int ReadUnchanged(const storageRead_t *read) {
    char latest[MAX_QPATH]; int next,length; void *probe;
    if(!Generation(latest,&next)) return 0;
    if(!*latest) Q_strncpyz(latest,databaseRoot,sizeof(latest));
    if(strcmp(latest,read->path)) return 0;
    if(read->head) { if(!Matches(read->path,read->head,read->headLength)) return 0; }
    else { probe=ReadImage(read->path,&length); free(probe); if(length>=0) return 0; }
    if(read->source) return Matches(databaseRoot,read->source,read->sourceLength);
    probe=ReadImage(databaseRoot,&length); free(probe); return length<0;
}
#ifndef __EMSCRIPTEN__
static int NativeFile(const char *relative,char *out,int size) {
    char home[MAX_OSPATH],game[MAX_QPATH]; int needed;
    trap_Cvar_VariableStringBuffer("fs_homepath",home,sizeof(home));
    trap_Cvar_VariableStringBuffer("fs_game",game,sizeof(game));
    if(!*home || strstr(game,"..") || strchr(game,':') || strchr(game,'/') || strchr(game,'\\')) return 0;
    if(!*game) Q_strncpyz(game,"etmain",sizeof(game));
    needed=strlen(home)+strlen(game)+strlen(relative)+3;
    if(needed>size) return 0;
    Com_sprintf(out,size,"%s/%s/%s",home,game,relative); return 1;
}
/* Exclusive creation prevents two native servers from truncating each
 * other's initial shared image.  Existing source/generation files are never
 * opened for writing during migration.  Subsequent writes are SQLite-owned. */
static int CreateNativeImage(const char *path,const void *bytes,int length) {
    int fd,ok;
#ifdef _WIN32
    fd=_open(path,_O_WRONLY|_O_CREAT|_O_EXCL|_O_BINARY,_S_IREAD|_S_IWRITE);
    if(fd<0) return 0;
    ok=_write(fd,bytes,length)==length && _commit(fd)==0;
    if(_close(fd)!=0) ok=0;
#else
    fd=open(path,O_WRONLY|O_CREAT|O_EXCL,0600);
    if(fd<0) return 0;
    ok=write(fd,bytes,length)==length && fsync(fd)==0;
    if(close(fd)!=0) ok=0;
#endif
    return ok;
}
static int NativeImageMatches(const char *path,const void *bytes,int length) {
    unsigned char buffer[4096]; int offset=0,ok=1; FILE *file=fopen(path,"rb");
    if(!file) return 0;
    while(offset<length) {
        int n=length-offset; if(n>(int)sizeof(buffer)) n=sizeof(buffer);
        if(fread(buffer,1,n,file)!=(size_t)n || memcmp(buffer,(const unsigned char *)bytes+offset,n)) { ok=0; break; }
        offset+=n;
    }
    if(ok && fgetc(file)!=EOF) ok=0;
    fclose(file); return ok;
}
static int EnableNative(void) {
    char target[MAX_QPATH],ospath[MAX_OSPATH]; void *disk=0,*physical=0,*bytes=0;
    int diskLength,physicalLength,length,created=0; fileHandle_t file=0;
    Q_strncpyz(target,databaseRoot,sizeof(target));
    if(strcmp(loadedPath,databaseRoot)) {
        Com_sprintf(target,sizeof(target),"%s.d/shared.sqlite",databaseRoot); created=1;
    }
    if(!NativeFile(target,ospath,sizeof(ospath))) return 0;
    disk=ReadImage(target,&diskLength);
    if(!disk && diskLength<0 && created) {
        bytes=NITMOD_DBExport(&length); if(!bytes) goto done;
        if(!CreateNativeImage(ospath,bytes,length)) {
            /* Another process may have completed the same migration. */
            disk=ReadImage(target,&diskLength); if(!disk) goto done;
        } else disk=ReadImage(target,&diskLength);
    }
    if(!disk || !NativeImageMatches(ospath,disk,diskLength) || !NITMOD_DBStorageOpen(ospath)) goto done;
    physical=NITMOD_DBStorageRead(&physicalLength);
    /* A pk3/basepath shadow is not the native writable homepath file. */
    if(!physical || physicalLength!=diskLength || memcmp(physical,disk,diskLength) ||
       !NITMOD_DBStorageInitSchema(G_NITMOD_LegacyCvarInteger("n_userMail",0),G_NITMOD_LegacyCvarInteger("n_mapRecords",0))) {
        NITMOD_DBStorageClose(); goto done;
    }
    nativeStorage=1; Q_strncpyz(nativePath,ospath,sizeof(nativePath));
    if(created) {
        trap_Cvar_Set("n_SQLiteDBPath",ValidRoot(target)?target:ospath);
        Q_strncpyz(databaseRoot,target,sizeof(databaseRoot)); Q_strncpyz(loadedPath,target,sizeof(loadedPath));
        G_LogPrintf("[SQLite] Migrated snapshots to live SQLite %s; earlier files retained\n",target);
    }
done:
    free(disk); NITMOD_DBFreeExport(physical); NITMOD_DBFreeExport(bytes); return nativeStorage;
}
#endif
void G_NITMOD_LoadDatabase(void) {
    char path[MAX_OSPATH],shared[MAX_QPATH]; fileHandle_t file=0; int length,next,asyncWanted; void *bytes=0;
    if(G_NITMOD_DatabasePending()) { G_LogPrintf("[SQLite] Reload refused while database operations are pending\n"); return; }
    G_NITMOD_DBAsyncReset(); asyncWanted=G_NITMOD_DBAsyncSupported();
    NITMOD_DBStorageClose(); nativeStorage=0; nativePath[0]=0;
    NITMOD_DBClose(); NITMOD_DBFreeExport(cacheBase); cacheBase=0; cacheLength=0;
    free(sourceBase); sourceBase=0; sourceLength=0; databaseRoot[0]=loadedPath[0]=0;
    G_NITMOD_LegacyCvarString("n_SQLiteDBPath",path,sizeof(path),"");
    if(!*path || !Q_stricmp(path,"none")) { G_LogPrintf("[SQLite] Database disabled (n_SQLiteDBPath)\n"); return; }
#ifndef __EMSCRIPTEN__
    /* Original nitrox_SQLite_init passes an explicitly configured OS path to
     * sqlite3_open; fs_homepath/fs_game is its default-path construction. */
    if(strstr(path,".sqlite") && (path[0]=='/' || path[0]=='\\' || (path[0] && path[1]==':'))) {
        if(NITMOD_DBStorageOpen(path) &&
           NITMOD_DBStorageInitSchema(G_NITMOD_LegacyCvarInteger("n_userMail",0),G_NITMOD_LegacyCvarInteger("n_mapRecords",0)) &&
           (bytes=NITMOD_DBStorageRead(&length)) && NITMOD_DBOpenWorking(bytes,length)) {
            nativeStorage=1; Q_strncpyz(nativePath,path,sizeof(nativePath)); CacheBaseline();
        } else { NITMOD_DBClose(); NITMOD_DBStorageClose(); G_LogPrintf("[SQLite] Native open failed: %s\n",NITMOD_DBError()); }
        NITMOD_DBFreeExport(bytes); G_NITMOD_DatabaseStatus(); return;
    }
#endif
    if(!strstr(path,".sqlite")) { Q_strncpyz(path,"NITMOD_DB.sqlite",sizeof(path)); trap_Cvar_Set("n_SQLiteDBPath",path); }
    if(!ValidRoot(path)) { G_LogPrintf("[SQLite] Database path must be an engine-relative .sqlite path\n"); return; }
    Com_sprintf(shared,sizeof(shared),"%s.d/shared.sqlite",path);
    length=trap_FS_FOpenFile(shared,&file,FS_READ); if(file) trap_FS_FCloseFile(file);
    if(length>=100) { Q_strncpyz(path,shared,sizeof(path)); trap_Cvar_Set("n_SQLiteDBPath",path); }
    Q_strncpyz(databaseRoot,path,sizeof(databaseRoot));
    sourceBase=ReadImage(databaseRoot,&sourceLength); if(!sourceBase) sourceLength=0;
    if(!Generation(loadedPath,&next)) { G_LogPrintf("[SQLite] Cannot enumerate database generations\n"); return; }
    if(!*loadedPath) Q_strncpyz(loadedPath,path,sizeof(loadedPath));
    if(sourceBase && !strcmp(loadedPath,databaseRoot)) {
        length=sourceLength; bytes=malloc(length); if(bytes) memcpy(bytes,sourceBase,length);
    } else bytes=ReadImage(loadedPath,&length);
    if(!bytes && length<0 && !strcmp(loadedPath,databaseRoot)) {
        if(!NITMOD_DBOpenWorking(NULL,0) || !NITMOD_DBInitSchema(G_NITMOD_LegacyCvarInteger("n_userMail",0),G_NITMOD_LegacyCvarInteger("n_mapRecords",0))) goto failed;
        CacheBaseline(); if(!asyncWanted && !G_NITMOD_DatabaseFlush()) goto failed;
    } else {
        if(!bytes || !NITMOD_DBOpenWorking(bytes,length) || !NITMOD_DBInitSchema(G_NITMOD_LegacyCvarInteger("n_userMail",0),G_NITMOD_LegacyCvarInteger("n_mapRecords",0))) goto failed;
        CacheBaseline();
    }
    free(bytes);
#ifndef __EMSCRIPTEN__
    EnableNative();
#endif
    if(asyncWanted) {
        bytes=NITMOD_DBExport(&length);
        if(!G_NITMOD_DBAsyncStart(databaseRoot,bytes,length)) G_LogPrintf("[SQLite] Cannot start atomic host database\n");
    }
    G_NITMOD_DatabaseStatus(); return;
failed:
    free(bytes); G_LogPrintf("[SQLite] Cannot load database: %s\n",NITMOD_DBError()); NITMOD_DBClose();
}
int G_NITMOD_DatabaseFlush(void) {
    char latest[MAX_QPATH],pending[MAX_QPATH],destination[MAX_QPATH]; storageRead_t read;
    fileHandle_t file=0; void *working=0,*current=0,*merged=0,*bytes=0; int workingLength,currentLength,mergedLength,length,next,size,ok=0;
    if(NITMOD_DBUserCount()<0) return 1;
    if(G_NITMOD_DBAsyncActive()) { G_LogPrintf("[SQLite] Synchronous flush refused: use commit completion\n"); return 0; }
    if(!cacheBase) CacheBaseline(); if(!cacheBase) return 0;
    if(cacheGeneration!=NITMOD_DBWorkingGeneration()) {
        G_LogPrintf("[SQLite] Commit refused: new working image needs load or SaveAs\n"); return 0;
    }
    if(nativeStorage) {
        ok=NITMOD_DBStorageCommit(cacheBase,cacheLength); if(ok) CacheBaseline();
        else G_LogPrintf("[SQLite] Live commit failed: %s\n",NITMOD_DBError()); return ok;
    }
    memset(&read,0,sizeof(read));
    if(!ValidRoot(databaseRoot) || !Generation(latest,&next)) return 0;
    working=NITMOD_DBExport(&workingLength); current=ReadCurrent(&read,&currentLength);
    if(!working || !current) goto done;
    merged=NITMOD_DBMergeImages(cacheBase,cacheLength,working,workingLength,current,currentLength,&mergedLength);
    if(!merged) goto done;
    bytes=NITMOD_DBImageSetOrigin(merged,mergedLength,read.sourceTracked?read.source:0,read.sourceTracked&&read.source?read.sourceLength:0,&length);
    if(!bytes || !ReadUnchanged(&read)) goto done;
    if(read.head && Matches(read.path,bytes,length)) { ok=1; goto done; }
    Com_sprintf(pending,sizeof(pending),"%s.d/%08d.pending",databaseRoot,next);
    Com_sprintf(destination,sizeof(destination),"%s.d/%08d.sqlite",databaseRoot,next);
    size=trap_FS_FOpenFile(pending,&file,FS_READ); if(file) trap_FS_FCloseFile(file);
    if(file || size>=0) goto done;
    file=0; size=trap_FS_FOpenFile(destination,&file,FS_READ); if(file) trap_FS_FCloseFile(file);
    if(file || size>=0) goto done;
    file=0; trap_FS_FOpenFile(pending,&file,FS_WRITE); if(!file) goto done;
    size=trap_FS_Write(bytes,length,file); trap_FS_FCloseFile(file);
    if(size!=length || !Matches(pending,bytes,length) || !ReadUnchanged(&read)) goto done;
    file=0; size=trap_FS_FOpenFile(destination,&file,FS_READ); if(file) trap_FS_FCloseFile(file);
    if(file || size>=0) goto done;
    trap_FS_Rename(pending,destination);
    if(!Matches(destination,bytes,length)) goto done;
    Q_strncpyz(loadedPath,destination,sizeof(loadedPath));
    G_LogPrintf("[SQLite] Committed database generation %d\n",next); ok=1;
done:
    if(ok) CacheBaseline(); else G_LogPrintf("[SQLite] Snapshot commit refused: %s\n",NITMOD_DBError());
    FreeRead(&read); NITMOD_DBFreeExport(working); NITMOD_DBFreeExport(current); NITMOD_DBFreeExport(merged); NITMOD_DBFreeExport(bytes); return ok;
}
int G_NITMOD_DatabaseSyncUser(const char *guid) {
    storageRead_t read; nitmodDatabaseAccount_t account; void *current=0,*working=0,*merged=0,*nextBase=0;
    int currentLength,workingLength,mergedLength,nextLength,ok=0;
    if(G_NITMOD_DBAsyncActive()) return 0;
    if(!G_NITMOD_LegacyCvarInteger("n_UserDBSync",0) || NITMOD_DBUserCount()<0) return 1;
    if(NITMOD_DBAccount(guid,&account)!=1) return 1;
    if(!cacheBase || cacheGeneration!=NITMOD_DBWorkingGeneration()) return 0;
    memset(&read,0,sizeof(read)); current=ReadCurrent(&read,&currentLength); working=NITMOD_DBExport(&workingLength);
    if(!current || !working) goto done;
    merged=NITMOD_DBMergeUserImages(cacheBase,cacheLength,working,workingLength,current,currentLength,guid,&mergedLength);
    if(!merged) goto done;
    nextBase=NITMOD_DBImageSyncUser(cacheBase,cacheLength,current,currentLength,guid,&nextLength);
    if(!nextBase || NITMOD_DBSyncUser(merged,mergedLength,guid)<0) goto done;
    NITMOD_DBFreeExport(cacheBase); cacheBase=nextBase; cacheLength=nextLength; nextBase=0; ok=1;
done:
    if(!ok) G_LogPrintf("[SQLite] LoadSingleUser failed: %s\n",NITMOD_DBError());
    FreeRead(&read); NITMOD_DBFreeExport(current); NITMOD_DBFreeExport(working); NITMOD_DBFreeExport(merged); NITMOD_DBFreeExport(nextBase); return ok;
}
void G_NITMOD_DatabaseShutdown(void) {
    if(G_NITMOD_DBAsyncActive()) {
        if(G_NITMOD_DatabasePending()) { G_LogPrintf("[SQLite] Shutdown retains pending transactions; host must drain before VM unload\n"); return; }
        G_NITMOD_DBAsyncReset();
    } else if(!G_NITMOD_DatabaseFlush()) G_LogPrintf("[SQLite] ERROR: shutdown persistence failed\n");
    NITMOD_DBStorageClose(); nativeStorage=0;
    NITMOD_DBClose();
}
void G_NITMOD_DatabaseStatus(void) {
    G_Printf("[SQLite] working image=%s users=%d schema=%d; root=%s; committed=%s\n",
        NITMOD_DBUserCount()<0 ? "closed" : "open",NITMOD_DBUserCount(),NITMOD_DBVersion(),
        *databaseRoot?databaseRoot:"none",nativeStorage?nativePath:*loadedPath?loadedPath:"none");
}
int G_NITMOD_DatabaseSaveAs(const char *path) {
    static char generations[65536];
    char directory[MAX_QPATH];
    fileHandle_t file=0;
    int length,written,readLength;
    void *bytes,*check;
    /* qpaths only: FS namespace is owned by the engine. Existing files,
     * including empty ones, are never opened with FS_WRITE. */
    if(G_NITMOD_DBAsyncActive() || !ValidRoot(path)) return 0;
    /* A root without a file can still own committed generations. Reload would
     * prefer those to the new export, so reserve the entire destination. */
    Com_sprintf(directory,sizeof(directory),"%s.d",path);
    if(trap_FS_GetFileList(directory,"",generations,sizeof(generations))!=0) {
        G_LogPrintf("[SQLite] Save refused: destination generations exist or cannot be listed\n"); return 0;
    }
    readLength=trap_FS_FOpenFile(path,&file,FS_READ);
    if(file) trap_FS_FCloseFile(file);
    if(file || readLength>=0) { G_LogPrintf("[SQLite] Save refused: destination exists\n"); return 0; }
    bytes=NITMOD_DBExport(&length); if(!bytes) return 0;
    if(cacheBase && cacheGeneration==NITMOD_DBWorkingGeneration() && (nativeStorage || *databaseRoot)) {
        storageRead_t read; int currentLength,mergedLength; void *current,*merged;
        memset(&read,0,sizeof(read)); current=ReadCurrent(&read,&currentLength);
        merged=current?NITMOD_DBMergeImages(cacheBase,cacheLength,bytes,length,current,currentLength,&mergedLength):0;
        FreeRead(&read); NITMOD_DBFreeExport(current); NITMOD_DBFreeExport(bytes);
        if(!merged) return 0; bytes=merged; length=mergedLength;
    }
#ifndef __EMSCRIPTEN__
    { char ospath[MAX_OSPATH];
      if(NativeFile(path,ospath,sizeof(ospath))) written=CreateNativeImage(ospath,bytes,length)?length:0;
      else {
#endif
        file=0; trap_FS_FOpenFile(path,&file,FS_WRITE);
        if(!file) { NITMOD_DBFreeExport(bytes); return 0; }
        written=trap_FS_Write(bytes,length,file); trap_FS_FCloseFile(file);
#ifndef __EMSCRIPTEN__
      }
    }
#endif
    if(written!=length) { NITMOD_DBFreeExport(bytes); G_LogPrintf("[SQLite] Save failed: short write\n"); return 0; }
    file=0; readLength=trap_FS_FOpenFile(path,&file,FS_READ);
    check=readLength==length && file ? malloc(length) : NULL;
    if(check) trap_FS_Read(check,length,file);
    if(file) trap_FS_FCloseFile(file);
    written=check && !memcmp(bytes,check,length);
    free(check); NITMOD_DBFreeExport(bytes);
    if(!written) { G_LogPrintf("[SQLite] Save failed: readback mismatch\n"); return 0; }
    trap_Cvar_Set("n_SQLiteDBPath",path);
    if(ValidRoot(path)) { Q_strncpyz(databaseRoot,path,sizeof(databaseRoot)); Q_strncpyz(loadedPath,path,sizeof(loadedPath)); }
    NITMOD_DBStorageClose(); nativeStorage=0; CacheBaseline();
    free(sourceBase); sourceBase=ReadImage(path,&sourceLength); if(!sourceBase) sourceLength=0;
#ifndef __EMSCRIPTEN__
    EnableNative();
#endif
    G_LogPrintf("[SQLite] Saved and verified new database %s\n",path); return 1;
}
int G_NITMOD_DatabaseMigrateLevel(int from,int to,const char *newPath) {
    int length; void *before=NITMOD_DBExport(&length);
    if(!before) return 0;
    if(!NITMOD_DBMigrateUserLevel(from,to) || !G_NITMOD_DatabaseSaveAs(newPath)) {
        if(!NITMOD_DBRestoreWorking(before,length)) G_LogPrintf("[SQLite] Failed to restore working image\n");
        NITMOD_DBFreeExport(before); return 0;
    }
    NITMOD_DBFreeExport(before); return 1;
}

/* Confirmed host results are installed without manufacturing a new account
 * epoch. Allocate/validate the new baseline before replacing either pointer. */
int G_NITMOD_DatabaseAcceptImage(const void *image,int length) {
    int nextLength; void *next=NITMOD_DBImageInitialize(image,length,
        G_NITMOD_LegacyCvarInteger("n_userMail",0),G_NITMOD_LegacyCvarInteger("n_mapRecords",0),&nextLength);
    if(!next) return 0;
    if(!NITMOD_DBInstallWorking(next,nextLength)) { NITMOD_DBFreeExport(next); return 0; }
    NITMOD_DBFreeExport(cacheBase); cacheBase=next; cacheLength=nextLength;
    cacheGeneration=NITMOD_DBWorkingGeneration(); return 1;
}
int G_NITMOD_DatabaseAcceptUser(const void *current,int currentLength,const char *guid) {
    void *working=0,*merged=0,*nextBase=0; int workingLength,mergedLength,nextLength,ok=0;
    if(!cacheBase || cacheGeneration!=NITMOD_DBWorkingGeneration()) return 0;
    working=NITMOD_DBExport(&workingLength);
    if(working) merged=NITMOD_DBMergeUserImages(cacheBase,cacheLength,working,workingLength,current,currentLength,guid,&mergedLength);
    if(!merged) goto done;
    nextBase=NITMOD_DBImageSyncUser(cacheBase,cacheLength,current,currentLength,guid,&nextLength);
    if(!nextBase || NITMOD_DBSyncUser(merged,mergedLength,guid)<0) goto done;
    NITMOD_DBFreeExport(cacheBase); cacheBase=nextBase; cacheLength=nextLength; nextBase=0; ok=1;
done:
    NITMOD_DBFreeExport(working); NITMOD_DBFreeExport(merged); NITMOD_DBFreeExport(nextBase); return ok;
}
void G_NITMOD_DatabaseAcceptPath(const char *path) {
    trap_Cvar_Set("n_SQLiteDBPath",path); Q_strncpyz(databaseRoot,path,sizeof(databaseRoot));
    Q_strncpyz(loadedPath,path,sizeof(loadedPath)); free(sourceBase); sourceBase=0; sourceLength=0;
}
static int Completion(int success,nitmodDbCompletion_t done,const void *context) {
    if(done) done(success,context); return success?1:0;
}
int G_NITMOD_DatabaseCommit(void *before,int length,nitmodDbCompletion_t done,const void *context,int contextLength) {
    void *after=0; int afterLength=0,ok;
    if(!before || length<100) { NITMOD_DBFreeExport(before); return Completion(0,done,context); }
    if(G_NITMOD_DBAsyncActive()) {
        after=NITMOD_DBExport(&afterLength);
        if(!NITMOD_DBInstallWorking(before,length)) Com_Error(ERR_FATAL,"SQLite cannot restore pending operation's before-image");
        if(!after) { NITMOD_DBFreeExport(before); return Completion(0,done,context); }
        return G_NITMOD_DBAsyncSubmit(before,length,after,afterLength,done,context,contextLength);
    }
    ok=G_NITMOD_DatabaseFlush();
    if(!ok && !NITMOD_DBInstallWorking(before,length)) Com_Error(ERR_FATAL,"SQLite cannot restore failed operation");
    NITMOD_DBFreeExport(before); return Completion(ok,done,context);
}
int G_NITMOD_DatabaseSubmitImages(void *base,int baseLength,void *changed,int changedLength,
    nitmodDbCompletion_t done,const void *context,int contextLength) {
    void *before=0,*merged=0; int length=0,mergedLength,ok=0;
    if(G_NITMOD_DBAsyncActive()) return G_NITMOD_DBAsyncSubmit(base,baseLength,changed,changedLength,done,context,contextLength);
    before=NITMOD_DBExport(&length);
    if(before) merged=NITMOD_DBMergeImages(base,baseLength,changed,changedLength,before,length,&mergedLength);
    if(merged && NITMOD_DBInstallWorking(merged,mergedLength)) {
        ok=G_NITMOD_DatabaseFlush();
        if(!ok && !NITMOD_DBInstallWorking(before,length)) Com_Error(ERR_FATAL,"SQLite cannot restore failed image transaction");
    }
    NITMOD_DBFreeExport(base); NITMOD_DBFreeExport(changed); NITMOD_DBFreeExport(before); NITMOD_DBFreeExport(merged);
    return Completion(ok,done,context);
}
int G_NITMOD_DatabaseSyncUserAsync(const char *guid,nitmodDbCompletion_t done,const void *context,int contextLength) {
    if(G_NITMOD_DBAsyncActive()) return G_NITMOD_DBAsyncUser(guid,G_NITMOD_LegacyCvarInteger("n_UserDBSync",0),done,context,contextLength);
    return Completion(G_NITMOD_DatabaseSyncUser(guid),done,context);
}
static int SaveAsAvailable(const char *path) {
    static char files[65536]; char directory[MAX_QPATH]; fileHandle_t file=0; int length;
    if(!ValidRoot(path)) return 0;
    Com_sprintf(directory,sizeof(directory),"%s.d",path);
    if(trap_FS_GetFileList(directory,"",files,sizeof(files))!=0) return 0;
    length=trap_FS_FOpenFile(path,&file,FS_READ); if(file) trap_FS_FCloseFile(file);
    return !file && length<0;
}
int G_NITMOD_DatabaseSaveAsAsync(const char *path,nitmodDbCompletion_t done,const void *context,int contextLength) {
    void *base=0,*changed=0; int baseLength,changedLength;
    if(!G_NITMOD_DBAsyncActive()) return Completion(G_NITMOD_DatabaseSaveAs(path),done,context);
    if(!G_NITMOD_DatabaseReady() || G_NITMOD_DatabasePending() || !SaveAsAvailable(path)) return Completion(0,done,context);
    changed=NITMOD_DBExport(&changedLength);
    base=cacheBase?NITMOD_DBImageInitialize(cacheBase,cacheLength,G_NITMOD_LegacyCvarInteger("n_userMail",0),
        G_NITMOD_LegacyCvarInteger("n_mapRecords",0),&baseLength):0;
    if(!base || !changed) { NITMOD_DBFreeExport(base); NITMOD_DBFreeExport(changed); return Completion(0,done,context); }
    return G_NITMOD_DBAsyncSaveAs(path,base,baseLength,changed,changedLength,done,context,contextLength);
}
int G_NITMOD_DatabaseMigrateLevelAsync(int from,int to,const char *path,nitmodDbCompletion_t done,const void *context,int contextLength) {
    void *before,*after=0; int length,afterLength;
    if(!G_NITMOD_DBAsyncActive()) return Completion(G_NITMOD_DatabaseMigrateLevel(from,to,path),done,context);
    if(!G_NITMOD_DatabaseReady() || G_NITMOD_DatabasePending() || !SaveAsAvailable(path)) return Completion(0,done,context);
    before=NITMOD_DBExport(&length); if(!before) return Completion(0,done,context);
    if(NITMOD_DBMigrateUserLevel(from,to)) after=NITMOD_DBExport(&afterLength);
    if(!NITMOD_DBInstallWorking(before,length)) Com_Error(ERR_FATAL,"SQLite cannot restore pending level migration");
    if(!after) { NITMOD_DBFreeExport(before); return Completion(0,done,context); }
    return G_NITMOD_DBAsyncSaveAs(path,before,length,after,afterLength,done,context,contextLength);
}
