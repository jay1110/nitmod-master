#include "g_local.h"
#include "g_nitmod_legacy_cvars.h"
#include "g_nitmod_database.h"
#include "nitmod_database.h"
static char databaseRoot[MAX_QPATH],loadedPath[MAX_QPATH];
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
void G_NITMOD_LoadDatabase(void) {
    char path[MAX_OSPATH];
    fileHandle_t file=0;
    int length,next;
    void *bytes;
    NITMOD_DBClose();
    databaseRoot[0]=loadedPath[0]=0;
    G_NITMOD_LegacyCvarString("n_SQLiteDBPath",path,sizeof(path),"");
    if(!*path || !Q_stricmp(path,"none")) { G_LogPrintf("[SQLite] Database disabled (n_SQLiteDBPath)\n"); return; }
    if(!strstr(path,".sqlite")) { Q_strncpyz(path,"NITMOD_DB.sqlite",sizeof(path)); trap_Cvar_Set("n_SQLiteDBPath",path); }
    if(!ValidRoot(path)) { G_LogPrintf("[SQLite] Database path must be an engine-relative .sqlite path\n"); return; }
    Q_strncpyz(databaseRoot,path,sizeof(databaseRoot));
    if(!Generation(loadedPath,&next)) { G_LogPrintf("[SQLite] Cannot enumerate database generations\n"); return; }
    if(!*loadedPath) Q_strncpyz(loadedPath,path,sizeof(loadedPath));
    /* Migration acts on a private working image, never on the source file. */
    length=trap_FS_FOpenFile(loadedPath,&file,FS_READ);
    if(length<0 && !file && !strcmp(loadedPath,databaseRoot)) {
        if(!NITMOD_DBOpenWorking(NULL,0) || !NITMOD_DBInitSchema(
            G_NITMOD_LegacyCvarInteger("n_userMail",0),G_NITMOD_LegacyCvarInteger("n_mapRecords",0)) ||
            !G_NITMOD_DatabaseFlush()) {
            G_LogPrintf("[SQLite] Cannot create database\n"); NITMOD_DBClose();
        }
        return;
    }
    if(length<100 || length>64*1024*1024 || !file) {
        if(file) trap_FS_FCloseFile(file);
        G_LogPrintf("[SQLite] Cannot read database through engine VFS\n"); return;
    }
    bytes=malloc(length);
    if(!bytes) { trap_FS_FCloseFile(file); return; }
    trap_FS_Read(bytes,length,file); trap_FS_FCloseFile(file);
    if(!NITMOD_DBOpenWorking(bytes,length) ||
       !NITMOD_DBInitSchema(G_NITMOD_LegacyCvarInteger("n_userMail",0),
                           G_NITMOD_LegacyCvarInteger("n_mapRecords",0))) {
        G_LogPrintf("[SQLite] %s\n",NITMOD_DBError()); NITMOD_DBClose();
    }
    free(bytes);
    G_NITMOD_DatabaseStatus();
}
int G_NITMOD_DatabaseFlush(void) {
    char latest[MAX_QPATH],pending[MAX_QPATH],destination[MAX_QPATH];
    fileHandle_t file=0; void *bytes; int length,next,size,written;
    if(NITMOD_DBUserCount()<0) return 1;
    if(!ValidRoot(databaseRoot) || !Generation(latest,&next)) return 0;
    bytes=NITMOD_DBExport(&length); if(!bytes) return 0;
    if(*loadedPath && Matches(loadedPath,bytes,length)) { NITMOD_DBFreeExport(bytes); return 1; }
    Com_sprintf(pending,sizeof(pending),"%s.d/%08d.pending",databaseRoot,next);
    Com_sprintf(destination,sizeof(destination),"%s.d/%08d.sqlite",databaseRoot,next);
    size=trap_FS_FOpenFile(pending,&file,FS_READ);
    if(file) trap_FS_FCloseFile(file);
    if(file || size>=0) { NITMOD_DBFreeExport(bytes); return 0; }
    file=0; size=trap_FS_FOpenFile(destination,&file,FS_READ);
    if(file) trap_FS_FCloseFile(file);
    if(file || size>=0) { NITMOD_DBFreeExport(bytes); return 0; }
    file=0; trap_FS_FOpenFile(pending,&file,FS_WRITE);
    if(!file) { NITMOD_DBFreeExport(bytes); return 0; }
    written=trap_FS_Write(bytes,length,file); trap_FS_FCloseFile(file);
    if(written!=length || !Matches(pending,bytes,length)) { NITMOD_DBFreeExport(bytes); return 0; }
    trap_FS_Rename(pending,destination);
    written=Matches(destination,bytes,length); NITMOD_DBFreeExport(bytes);
    if(!written) return 0;
    Q_strncpyz(loadedPath,destination,sizeof(loadedPath));
    G_LogPrintf("[SQLite] Committed database generation %d\n",next); return 1;
}
void G_NITMOD_DatabaseShutdown(void) {
    if(!G_NITMOD_DatabaseFlush()) G_LogPrintf("[SQLite] ERROR: shutdown persistence failed\n");
    NITMOD_DBClose();
}
void G_NITMOD_DatabaseStatus(void) {
    G_Printf("[SQLite] working image=%s users=%d schema=%d; root=%s; committed=%s\n",
        NITMOD_DBUserCount()<0 ? "closed" : "open",NITMOD_DBUserCount(),NITMOD_DBVersion(),
        *databaseRoot?databaseRoot:"none",*loadedPath?loadedPath:"none");
}
int G_NITMOD_DatabaseSaveAs(const char *path) {
    static char generations[65536];
    char directory[MAX_QPATH];
    fileHandle_t file=0;
    int length,written,readLength;
    void *bytes,*check;
    /* qpaths only: FS namespace is owned by the engine. Existing files,
     * including empty ones, are never opened with FS_WRITE. */
    if(!ValidRoot(path)) return 0;
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
    file=0; trap_FS_FOpenFile(path,&file,FS_WRITE);
    if(!file) { NITMOD_DBFreeExport(bytes); return 0; }
    written=trap_FS_Write(bytes,length,file); trap_FS_FCloseFile(file);
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
    G_LogPrintf("[SQLite] Saved and verified new database %s\n",path); return 1;
}
int G_NITMOD_DatabaseMigrateLevel(int from,int to,const char *newPath) {
    int length; void *before=NITMOD_DBExport(&length);
    if(!before) return 0;
    if(!NITMOD_DBMigrateUserLevel(from,to) || !G_NITMOD_DatabaseSaveAs(newPath)) {
        if(!NITMOD_DBOpenWorking(before,length)) G_LogPrintf("[SQLite] Failed to restore working image\n");
        NITMOD_DBFreeExport(before); return 0;
    }
    NITMOD_DBFreeExport(before); return 1;
}
