#include "nitmod_database.h"
#include "../sqlite/sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>

static sqlite3 *database;
static char lastError[256];
static int users,version;
static int writable;
static unsigned int epoch,workingGeneration;
unsigned int NITMOD_DBWorkingGeneration(void) { return workingGeneration; }
unsigned int NITMOD_DBEpoch(void) { return epoch; }
static void Error(const char *text) {
    size_t n=strlen(text); if(n>=sizeof(lastError)) n=sizeof(lastError)-1;
    memcpy(lastError,text,n); lastError[n]=0;
}
#ifdef __EMSCRIPTEN__
/* No host filesystem access. Existing DB bytes arrive through engine VFS.
 * This base VFS only allows SQLite's in-memory/deserialize implementation. */
static int NoOpen(sqlite3_vfs *v,const char *n,sqlite3_file *f,int flags,int *out) { return SQLITE_CANTOPEN; }
static int NoDelete(sqlite3_vfs *v,const char *n,int sync) { return SQLITE_READONLY; }
static int NoAccess(sqlite3_vfs *v,const char *n,int flags,int *out) { *out=0; return SQLITE_OK; }
static int FullPath(sqlite3_vfs *v,const char *n,int size,char *out) {
    if((int)strlen(n)>=size) return SQLITE_CANTOPEN;
    strcpy(out,n); return SQLITE_OK;
}
static int RandomBytes(sqlite3_vfs *v,int n,char *out) { memset(out,0,n); return n; }
static int Sleep(sqlite3_vfs *v,int us) { return us; }
static int CurrentTime(sqlite3_vfs *v,double *out) { *out=2440587.5; return SQLITE_OK; }
static sqlite3_vfs memoryVfs={1,sizeof(sqlite3_file),1024,0,"nitmod-snapshot",0,
    NoOpen,NoDelete,NoAccess,FullPath,0,0,0,0,RandomBytes,Sleep,CurrentTime,0};
int sqlite3_os_init(void) { return sqlite3_vfs_register(&memoryVfs,1); }
int sqlite3_os_end(void) { return SQLITE_OK; }
#endif
const char *NITMOD_DBError(void) { return lastError; }
void NITMOD_DBClose(void) {
    ++epoch; ++workingGeneration;
    if(database) sqlite3_close(database);
    database=0; users=version=0; writable=0;
}
int NITMOD_DBUserCount(void) { return database ? users : -1; }
int NITMOD_DBVersion(void) { return database ? version : -1; }
static int Exec(const char *sql) {
    if(sqlite3_exec(database,sql,0,0,0)==SQLITE_OK) return 1;
    Error(sqlite3_errmsg(database)); return 0;
}
static int Scalar(const char *sql,int *value) {
    sqlite3_stmt *s=0;
    int ok=sqlite3_prepare_v2(database,sql,-1,&s,0)==SQLITE_OK && sqlite3_step(s)==SQLITE_ROW;
    if(ok) *value=sqlite3_column_int(s,0); else Error(sqlite3_errmsg(database));
    sqlite3_finalize(s); return ok;
}
int NITMOD_DBClearXP(void) {
    return database && writable && Exec("UPDATE users SET xp='UzBcMFxTMVwwXFMyXDBcUzNcMFxTNFwwXFM1XDBcUzZcMFw='");
}
int NITMOD_DBOpenWorking(const void *bytes,int length) {
    unsigned char *copy;
    sqlite3_stmt *check=0; int tableExists;
    NITMOD_DBClose(); lastError[0]=0;
    if((!bytes && length) || (bytes && (length<100 || length>64*1024*1024 || memcmp(bytes,"SQLite format 3\000",16)))) {
        Error("Invalid SQLite working image"); return 0;
    }
    if(sqlite3_open(":memory:",&database)!=SQLITE_OK) goto failed;
    if(bytes) {
        copy=sqlite3_malloc(length);
        if(!copy) { Error("SQLite allocation failed"); NITMOD_DBClose(); return 0; }
        memcpy(copy,bytes,length);
        if(sqlite3_deserialize(database,"main",copy,length,length,
            SQLITE_DESERIALIZE_FREEONCLOSE|SQLITE_DESERIALIZE_RESIZEABLE)!=SQLITE_OK) goto failed;
    }
    if(sqlite3_prepare_v2(database,"PRAGMA quick_check",-1,&check,0)!=SQLITE_OK ||
       sqlite3_step(check)!=SQLITE_ROW || !sqlite3_column_text(check,0) ||
       strcmp((const char *)sqlite3_column_text(check,0),"ok") || sqlite3_step(check)!=SQLITE_DONE) {
        sqlite3_finalize(check); Error("SQLite integrity check failed"); NITMOD_DBClose(); return 0;
    }
    sqlite3_finalize(check);
    if(!Scalar("PRAGMA user_version",&version)) goto failed;
    /* A working image may be fresh. Existing user counts must survive reopen. */
    if(!Scalar("SELECT COUNT(*) FROM sqlite_master WHERE name='users'",&tableExists)) goto failed;
    if(tableExists && !Scalar("SELECT COUNT(*) FROM users",&users)) goto failed;
    writable=1; return 1;
failed:
    Error(database?sqlite3_errmsg(database):"SQLite open failed"); NITMOD_DBClose(); return 0;
}
int NITMOD_DBRestoreWorking(const void *bytes,int length) {
    unsigned int sameDatabase=workingGeneration;
    if(!NITMOD_DBOpenWorking(bytes,length)) return 0;
    workingGeneration=sameDatabase; return 1;
}
int NITMOD_DBInstallWorking(const void *bytes,int length) {
    sqlite3 *old=database; int oldUsers=users,oldVersion=version,oldWritable=writable,ok;
    unsigned int oldEpoch=epoch,oldGeneration=workingGeneration;
    /* OpenWorking operates on an isolated handle until validation succeeds. */
    database=0; users=version=writable=0;
    ok=NITMOD_DBOpenWorking(bytes,length);
    if(ok) { if(old) sqlite3_close(old); }
    else { database=old; users=oldUsers; version=oldVersion; writable=oldWritable; }
    epoch=oldEpoch; workingGeneration=oldGeneration; return ok;
}
void *NITMOD_DBExport(int *length) {
    sqlite3_int64 size=0;
    unsigned char *bytes;
    if(length) *length=0;
    if(!database || !length || !sqlite3_get_autocommit(database)) return 0;
    bytes=sqlite3_serialize(database,"main",&size,0);
    if(!bytes || size<100 || size>64*1024*1024) {
        sqlite3_free(bytes); Error("SQLite export failed or exceeds 64 MiB"); return 0;
    }
    *length=(int)size; return bytes;
}
void NITMOD_DBFreeExport(void *bytes) { sqlite3_free(bytes); }
int NITMOD_DBInitSchema(int mailEnabled,int recordsEnabled) {
    int oldVersion,recordTable,updatedVersion,updatedUsers;
    if(!database || !writable) { Error("Database is not writable"); return 0; }
    if(!Scalar("PRAGMA user_version",&oldVersion) || !Exec("BEGIN TRANSACTION")) return 0;
    /* Preserve the original migration SQL, including its scalar duplicate
     * deletion. More complex duplicate sets fail the UNIQUE copy atomically. */
    if(oldVersion==1 && !Exec(
        "CREATE TABLE users_tmp (id INTEGER PRIMARY KEY AUTOINCREMENT,name char(64),guid varchar(33),ip char(15),level INT,flags varchar(1024),gtext varchar(128),gsound varchar(64),mac char(17),xp varchar(1024),timestamp INT,login char(32),password char(40));"
        "INSERT INTO users_tmp(flags,gsound,gtext,guid,ip,level,login,mac,name,password,timestamp,xp) SELECT flags,gsound,gtext,guid,ip,level,login,mac,name,password,timestamp,xp FROM users;"
        "DELETE FROM users_tmp WHERE id = (SELECT min(id) FROM users_tmp GROUP BY guid HAVING count(*) > 1);"
        "DROP TABLE users; ALTER TABLE users_tmp RENAME TO users;"
        "CREATE TABLE users_tmp2 (id INTEGER PRIMARY KEY AUTOINCREMENT,name char(64),guid varchar(33) UNIQUE,ip char(15),level INT,flags varchar(1024),gtext varchar(128),gsound varchar(64),mac char(17),xp varchar(1024),timestamp INT,login char(32),password char(40));"
        "INSERT INTO users_tmp2(flags,gsound,gtext,guid,ip,level,login,mac,name,password,timestamp,xp) SELECT flags,gsound,gtext,guid,ip,level,login,mac,name,password,timestamp,xp FROM users;"
        "DROP TABLE users; ALTER TABLE users_tmp2 RENAME TO users;"
        "CREATE INDEX users_guid ON users(guid); PRAGMA user_version=2;")) goto failed;
    if(!Exec(
        "CREATE TABLE IF NOT EXISTS users(name char(64),guid varchar(33),ip char(15),level INT,flags varchar(1024),gtext varchar(128),gsound varchar(64),mac char(17),xp varchar(255),timestamp INT,login char(32),password char(40));"
        "CREATE TABLE IF NOT EXISTS bans(name char(64),guid char(34),ip char(18),mac char(18),reason varchar(128),made char(20),expires char(20),banner char(64));"
        "CREATE TABLE IF NOT EXISTS mutes(name char(64),guid char(34),ip char(18),mac char(18),reason varchar(128),made char(20),expires char(20),muter char(64));")) goto failed;
    if(mailEnabled && !Exec("CREATE TABLE IF NOT EXISTS mails(id INTEGER PRIMARY KEY,sent_by char(32),sent_to char(32),message varchar(1022));")) goto failed;
    if(recordsEnabled) {
        if(!Scalar("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='records'",&recordTable)) goto failed;
        if(!recordTable) {
            if(!Exec("CREATE TABLE records(map varchar(64),maxspreeholder varchar(64),maxspree INT,maxspreedate varchar(32),maxfragsholder varchar(64),maxfrags INT,maxfragsdate varchar(32),maxrspreeholder varchar(64),maxrspree INT,maxrspreedate varchar(32)); PRAGMA user_version=1;")) goto failed;
        } else if(oldVersion==0 && !Exec("PRAGMA user_version=1; ALTER TABLE records ADD COLUMN maxrspreeholder varchar(64); ALTER TABLE records ADD COLUMN maxrspree INT DEFAULT 0; ALTER TABLE records ADD COLUMN maxrspreedate varchar(32);")) goto failed;
    }
    if(!Scalar("PRAGMA user_version",&updatedVersion) || !Scalar("SELECT COUNT(*) FROM users",&updatedUsers) || !Exec("COMMIT")) goto failed;
    version=updatedVersion; users=updatedUsers; return 1;
failed:
    /* Do not replace the useful error with a successful ROLLBACK message. */
    sqlite3_exec(database,"ROLLBACK",0,0,0); return 0;
}
int NITMOD_DBOpenSnapshot(const void *bytes,int length) {
    unsigned char *copy;
    sqlite3_stmt *statement=0;
    int rc;
    NITMOD_DBClose(); lastError[0]=0;
    if(!bytes || length<100 || length>64*1024*1024 || memcmp(bytes,"SQLite format 3\000",16)) {
        Error("Invalid SQLite snapshot header/size"); return 0;
    }
    if(sqlite3_open(":memory:",&database)!=SQLITE_OK) goto fail;
    copy=(unsigned char *)sqlite3_malloc(length);
    if(!copy) { Error("SQLite snapshot allocation failed"); NITMOD_DBClose(); return 0; }
    memcpy(copy,bytes,length);
    rc=sqlite3_deserialize(database,"main",copy,length,length,SQLITE_DESERIALIZE_FREEONCLOSE|SQLITE_DESERIALIZE_READONLY);
    if(rc!=SQLITE_OK) goto fail; /* FREEONCLOSE also frees failed deserialize input */
    /* A named-column query accepts both original legacy and migrated users
     * layouts without assigning privileges or modifying their schema. */
    if(sqlite3_prepare_v2(database,"SELECT name,guid,level,flags,xp FROM users LIMIT 0",-1,&statement,0)!=SQLITE_OK) goto fail;
    sqlite3_finalize(statement); statement=0;
    if(sqlite3_prepare_v2(database,"SELECT COUNT(*) FROM users",-1,&statement,0)!=SQLITE_OK || sqlite3_step(statement)!=SQLITE_ROW) goto fail;
    if(sqlite3_column_int64(statement,0)>INT_MAX) goto fail;
    users=sqlite3_column_int(statement,0); sqlite3_finalize(statement); statement=0;
    if(sqlite3_prepare_v2(database,"PRAGMA user_version",-1,&statement,0)!=SQLITE_OK || sqlite3_step(statement)!=SQLITE_ROW) goto fail;
    version=sqlite3_column_int(statement,0); sqlite3_finalize(statement);
    return 1;
fail:
    Error(database ? sqlite3_errmsg(database) : "SQLite open failed");
    if(statement) sqlite3_finalize(statement);
    NITMOD_DBClose(); return 0;
}
static int TextColumn(sqlite3_stmt *statement,int column,char *out,int size) {
    const unsigned char *text=sqlite3_column_text(statement,column);
    int length=sqlite3_column_bytes(statement,column);
    if(!text) { out[0]=0; return 1; }
    if(length>=size || (int)strlen((const char *)text)!=length) return 0;
    memcpy(out,text,length+1); return 1;
}
int NITMOD_DBUser(const char *guid,nitmodDatabaseUser_t *result) {
    sqlite3_stmt *statement=0;
    nitmodDatabaseUser_t next;
    sqlite3_int64 level;
    int rc;
    if(!database || !guid || !result) return -1;
    if(sqlite3_prepare_v2(database,"SELECT name,guid,level,flags,xp FROM users WHERE guid = ?1 COLLATE BINARY LIMIT 2",-1,&statement,0)!=SQLITE_OK) return -1;
    sqlite3_bind_text(statement,1,guid,-1,SQLITE_TRANSIENT);
    rc=sqlite3_step(statement);
    if(rc==SQLITE_DONE) { sqlite3_finalize(statement); return 0; }
    memset(&next,0,sizeof(next));
    if(rc!=SQLITE_ROW) goto fail;
    level=sqlite3_column_int64(statement,2);
    if(level<0 || level>INT_MAX || sqlite3_column_type(statement,2)!=SQLITE_INTEGER) goto fail;
    next.level=(int)level;
    if(!TextColumn(statement,0,next.name,sizeof(next.name)) || !TextColumn(statement,1,next.guid,sizeof(next.guid)) ||
       !TextColumn(statement,3,next.flags,sizeof(next.flags)) || !TextColumn(statement,4,next.xp,sizeof(next.xp))) goto fail;
    /* Ambiguous legacy identities never receive arbitrary first-row rights. */
    if(sqlite3_step(statement)!=SQLITE_DONE) goto fail;
    sqlite3_finalize(statement); *result=next; return 1;
fail:
    sqlite3_finalize(statement); Error("Invalid or ambiguous user record"); return -1;
}
int NITMOD_DBAccount(const char *guid,nitmodDatabaseAccount_t *result) {
    sqlite3_stmt *s=0;
    nitmodDatabaseAccount_t next;
    sqlite3_int64 timestamp;
    int rc;
    if(!database || !guid || !result) return -1;
    memset(&next,0,sizeof(next));
    rc=NITMOD_DBUser(guid,&next.user); if(rc!=1) return rc;
    if(sqlite3_prepare_v2(database,"SELECT ip,gtext,gsound,mac,timestamp,login,password FROM users WHERE guid=?1 COLLATE BINARY LIMIT 2",-1,&s,0)!=SQLITE_OK) goto failed;
    if(sqlite3_bind_text(s,1,guid,-1,SQLITE_TRANSIENT)!=SQLITE_OK || sqlite3_step(s)!=SQLITE_ROW) goto failed;
    timestamp=sqlite3_column_int64(s,4);
    if(timestamp<INT_MIN || timestamp>INT_MAX || sqlite3_column_type(s,4)!=SQLITE_INTEGER) goto failed;
    next.timestamp=(int)timestamp;
    if(!TextColumn(s,0,next.ip,sizeof(next.ip)) || !TextColumn(s,1,next.gtext,sizeof(next.gtext)) ||
       !TextColumn(s,2,next.gsound,sizeof(next.gsound)) || !TextColumn(s,3,next.mac,sizeof(next.mac)) ||
       !TextColumn(s,5,next.login,sizeof(next.login)) || !TextColumn(s,6,next.password,sizeof(next.password)) ||
       sqlite3_step(s)!=SQLITE_DONE) goto failed;
    sqlite3_finalize(s); *result=next; return 1;
failed:
    Error("Invalid or ambiguous account record"); sqlite3_finalize(s); return -1;
}
static int AccountLookup(const char *sql,const char *id,int index,nitmodDatabaseAccount_t *result) {
    sqlite3_stmt *s=0; char guid[34]; int rc;
    if(!database || !result || sqlite3_prepare_v2(database,sql,-1,&s,0)!=SQLITE_OK) goto failed;
    rc=id?sqlite3_bind_text(s,1,id,-1,SQLITE_TRANSIENT):sqlite3_bind_int(s,1,index);
    if(rc!=SQLITE_OK) goto failed;
    rc=sqlite3_step(s);
    if(rc==SQLITE_DONE) { sqlite3_finalize(s); return 0; }
    if(rc!=SQLITE_ROW || !TextColumn(s,0,guid,sizeof(guid)) || sqlite3_step(s)!=SQLITE_DONE) goto failed;
    sqlite3_finalize(s); return NITMOD_DBAccount(guid,result);
failed:
    sqlite3_finalize(s); Error("Invalid or ambiguous user ID"); return -1;
}
int NITMOD_DBAccountAt(int index,nitmodDatabaseAccount_t *result) {
    if(index<0) return -1;
    return AccountLookup("SELECT guid FROM users ORDER BY rowid LIMIT 1 OFFSET ?1",NULL,index,result);
}
int NITMOD_DBAccountByID(const char *id,nitmodDatabaseAccount_t *result) {
    if(!id || strlen(id)!=8) return 0;
    return AccountLookup("SELECT guid FROM users WHERE length(guid)=32 AND substr(guid,25,8)=?1 COLLATE NOCASE LIMIT 2",id,0,result);
}
static int Bounded(const char *s,size_t size) { return memchr(s,0,size)!=NULL; }
static int BindText(sqlite3_stmt *s,int column,const char *text) {
    return sqlite3_bind_text(s,column,text,-1,SQLITE_TRANSIENT)==SQLITE_OK;
}
int NITMOD_DBSaveAccount(const nitmodDatabaseAccount_t *a,int mode) {
    sqlite3_stmt *s=0;
    int exists,nextUsers;
    const char *sql;
    if(!database || !writable || !a || mode<0 || mode>2 ||
       !Bounded(a->user.guid,sizeof(a->user.guid)) || !a->user.guid[0]) return 0;
    if(mode && (a->user.level<0 || !Bounded(a->user.name,sizeof(a->user.name)) ||
       !Bounded(a->user.flags,sizeof(a->user.flags)) || !Bounded(a->user.xp,sizeof(a->user.xp)) ||
       !Bounded(a->ip,sizeof(a->ip)) || !Bounded(a->gtext,sizeof(a->gtext)) ||
       !Bounded(a->gsound,sizeof(a->gsound)) || !Bounded(a->mac,sizeof(a->mac)) ||
       !Bounded(a->login,sizeof(a->login)) || !Bounded(a->password,sizeof(a->password)))) return 0;
    if(!Exec("BEGIN TRANSACTION")) return 0;
    if(sqlite3_prepare_v2(database,"SELECT count(*) FROM users WHERE guid=?1 COLLATE BINARY",-1,&s,0)!=SQLITE_OK ||
       !BindText(s,1,a->user.guid) || sqlite3_step(s)!=SQLITE_ROW) goto failed;
    exists=sqlite3_column_int(s,0); sqlite3_finalize(s); s=0;
    sql=mode==0 ? "DELETE FROM users WHERE guid=?1 COLLATE BINARY" : exists ?
        "UPDATE users SET name=?2,ip=?3,level=?4,flags=?5,gtext=?6,gsound=?7,mac=?8,xp=?9,timestamp=?10,login=?11,password=?12 WHERE guid=?1 COLLATE BINARY" :
        "INSERT INTO users(guid,name,ip,level,flags,gtext,gsound,mac,xp,timestamp,login,password) VALUES(?1,?2,?3,?4,?5,?6,?7,?8,?9,?10,?11,?12)";
    if(sqlite3_prepare_v2(database,sql,-1,&s,0)!=SQLITE_OK || !BindText(s,1,a->user.guid)) goto failed;
    if(mode && (!BindText(s,2,a->user.name) || !BindText(s,3,a->ip) ||
       sqlite3_bind_int(s,4,a->user.level)!=SQLITE_OK || !BindText(s,5,a->user.flags) ||
       !BindText(s,6,a->gtext) || !BindText(s,7,a->gsound) || !BindText(s,8,a->mac) ||
       !BindText(s,9,a->user.xp) || sqlite3_bind_int(s,10,a->timestamp)!=SQLITE_OK ||
       !BindText(s,11,a->login) || !BindText(s,12,a->password))) goto failed;
    if(sqlite3_step(s)!=SQLITE_DONE) goto failed;
    sqlite3_finalize(s); s=0;
    if(!Scalar("SELECT COUNT(*) FROM users",&nextUsers) || !Exec("COMMIT")) goto rollback;
    users=nextUsers; return 1;
failed:
    Error(sqlite3_errmsg(database)); sqlite3_finalize(s);
rollback:
    sqlite3_exec(database,"ROLLBACK",0,0,0); return 0;
}
int NITMOD_DBMigrateUserLevel(int from,int to) {
    sqlite3_stmt *s=0;
    int ok;
    if(!database || !writable || from<0 || to<0) return 0;
    ok=sqlite3_prepare_v2(database,"UPDATE users SET level=?2 WHERE level=?1",-1,&s,0)==SQLITE_OK &&
       sqlite3_bind_int(s,1,from)==SQLITE_OK && sqlite3_bind_int(s,2,to)==SQLITE_OK && sqlite3_step(s)==SQLITE_DONE;
    if(!ok) Error(sqlite3_errmsg(database)); sqlite3_finalize(s); return ok;
}
int NITMOD_DBMailSend(const char *sender,const char *recipient,const char *message) {
    sqlite3_stmt *s=0; int rc;
    if(!database || !writable || !sender || !recipient || !message || strlen(sender)>32 ||
       strlen(recipient)>32 || strlen(message)>1021) return -1;
    if(sqlite3_prepare_v2(database,"SELECT count(*) FROM users WHERE login=?1 COLLATE BINARY",-1,&s,0)!=SQLITE_OK ||
       !BindText(s,1,recipient) || sqlite3_step(s)!=SQLITE_ROW) goto failed;
    rc=sqlite3_column_int(s,0); sqlite3_finalize(s); s=0; if(!rc) return 0;
    if(sqlite3_prepare_v2(database,"INSERT INTO mails(sent_by,sent_to,message) VALUES(?1,?2,?3)",-1,&s,0)!=SQLITE_OK ||
       !BindText(s,1,sender) || !BindText(s,2,recipient) || !BindText(s,3,message) || sqlite3_step(s)!=SQLITE_DONE) goto failed;
    sqlite3_finalize(s); return 1;
failed:
    Error(sqlite3_errmsg(database)); sqlite3_finalize(s); return -1;
}
int NITMOD_DBMailDelete(const char *recipient,int id) {
    sqlite3_stmt *s=0; int changed;
    if(!database || !writable || !recipient) return -1;
    if(sqlite3_prepare_v2(database,"DELETE FROM mails WHERE id=?1 AND sent_to=?2 COLLATE BINARY",-1,&s,0)!=SQLITE_OK ||
       sqlite3_bind_int(s,1,id)!=SQLITE_OK || !BindText(s,2,recipient) || sqlite3_step(s)!=SQLITE_DONE) {
        Error(sqlite3_errmsg(database)); sqlite3_finalize(s); return -1;
    }
    changed=sqlite3_changes(database); sqlite3_finalize(s); return changed?1:0;
}
int NITMOD_DBMails(const char *recipient,nitmodMailVisitor_t visit,void *context) {
    sqlite3_stmt *s=0; int count=0,rc; char sender[33],message[1022]; sqlite3_int64 id;
    if(!database || !recipient || !visit) return -1;
    if(sqlite3_prepare_v2(database,"SELECT id,sent_by,message FROM mails WHERE sent_to=?1 COLLATE BINARY",-1,&s,0)!=SQLITE_OK ||
       !BindText(s,1,recipient)) goto failed;
    while((rc=sqlite3_step(s))==SQLITE_ROW) {
        id=sqlite3_column_int64(s,0);
        if(id<INT_MIN || id>INT_MAX || !TextColumn(s,1,sender,sizeof(sender)) || !TextColumn(s,2,message,sizeof(message))) goto failed;
        visit(context,(int)id,sender,message); ++count;
    }
    if(rc!=SQLITE_DONE) goto failed;
    sqlite3_finalize(s); return count;
failed:
    Error("Cannot read mailbox"); sqlite3_finalize(s); return -1;
}
int NITMOD_DBPenaltySave(int mute,const nitmodDatabasePenalty_t *p,int add) {
    sqlite3_stmt *s=0; const char *sql; int exists;
    if(!database || !writable || !p || (mute!=0 && mute!=1) || (add!=0 && add!=1) ||
       !Bounded(p->guid,sizeof(p->guid))) return 0;
    if(add && (!Bounded(p->name,sizeof(p->name)) || !Bounded(p->ip,sizeof(p->ip)) ||
       !Bounded(p->mac,sizeof(p->mac)) || !Bounded(p->reason,sizeof(p->reason)) ||
       !Bounded(p->made,sizeof(p->made)) || !Bounded(p->actor,sizeof(p->actor)))) return 0;
    if(add) {
        sql=mute?"SELECT count(*) FROM mutes WHERE guid=?1 COLLATE NOCASE":"SELECT count(*) FROM bans WHERE guid=?1 COLLATE NOCASE";
        if(sqlite3_prepare_v2(database,sql,-1,&s,0)!=SQLITE_OK || !BindText(s,1,p->guid) || sqlite3_step(s)!=SQLITE_ROW) goto failed;
        exists=sqlite3_column_int(s,0); sqlite3_finalize(s); s=0;
        if(exists) return 1; /* original bulk saver does not duplicate existing GUIDs */
        if(!Scalar(mute?"SELECT count(*) FROM mutes":"SELECT count(*) FROM bans",&exists) || exists>=1024) { Error("Maximum penalties exceeded"); return 0; }
    }
    sql=add?(mute?"INSERT INTO mutes(name,guid,ip,mac,reason,made,expires,muter) VALUES(?2,?1,?3,?4,?5,?6,?7,?8)":
                    "INSERT INTO bans(name,guid,ip,mac,reason,made,expires,banner) VALUES(?2,?1,?3,?4,?5,?6,?7,?8)"):
             (mute?"DELETE FROM mutes WHERE guid=?1 COLLATE BINARY":"DELETE FROM bans WHERE guid=?1 COLLATE BINARY");
    if(sqlite3_prepare_v2(database,sql,-1,&s,0)!=SQLITE_OK || !BindText(s,1,p->guid)) goto failed;
    if(add && (!BindText(s,2,p->name) || !BindText(s,3,p->ip) || !BindText(s,4,p->mac) || !BindText(s,5,p->reason) ||
       !BindText(s,6,p->made) || sqlite3_bind_int(s,7,p->expires)!=SQLITE_OK || !BindText(s,8,p->actor))) goto failed;
    if(sqlite3_step(s)!=SQLITE_DONE) goto failed;
    sqlite3_finalize(s); return 1;
failed:
    Error(sqlite3_errmsg(database)); sqlite3_finalize(s); return 0;
}
static int PenaltyIP(const char *value,const char *ip) {
    int dots=0; size_t i,n=strlen(value);
    if(n<7 || n>17 || n==16) return 0;
    for(i=0;i<n;++i) { if(value[i]=='.') ++dots; else if(value[i]<'0' || value[i]>'9') return 0; }
    return dots==3 && strstr(ip,value)!=NULL; /* original substring, not CIDR */
}
int NITMOD_DBPenaltyAt(int mute,int index,nitmodDatabasePenalty_t *result) {
    nitmodDatabasePenalty_t p; sqlite3_stmt *s=0; int rc; sqlite3_int64 expires;
    if(!database || !result || index<0 || index>=1024 || (mute!=0 && mute!=1)) return -1;
    if(sqlite3_prepare_v2(database,mute?"SELECT name,guid,ip,mac,reason,made,expires,muter FROM mutes LIMIT 1 OFFSET ?1":
        "SELECT name,guid,ip,mac,reason,made,expires,banner FROM bans LIMIT 1 OFFSET ?1",-1,&s,0)!=SQLITE_OK || sqlite3_bind_int(s,1,index)!=SQLITE_OK) goto failed;
    rc=sqlite3_step(s); if(rc==SQLITE_DONE) { sqlite3_finalize(s); return 0; }
    memset(&p,0,sizeof(p)); if(rc!=SQLITE_ROW) goto failed;
    expires=sqlite3_column_int64(s,6);
    if(expires<INT_MIN || expires>INT_MAX || !TextColumn(s,0,p.name,sizeof(p.name)) || !TextColumn(s,1,p.guid,sizeof(p.guid)) ||
       !TextColumn(s,2,p.ip,sizeof(p.ip)) || !TextColumn(s,3,p.mac,sizeof(p.mac)) || !TextColumn(s,4,p.reason,sizeof(p.reason)) ||
       !TextColumn(s,5,p.made,sizeof(p.made)) || !TextColumn(s,7,p.actor,sizeof(p.actor))) goto failed;
    p.expires=(int)expires; sqlite3_finalize(s); *result=p; return 1;
failed:
    Error("Invalid penalty record"); sqlite3_finalize(s); return -1;
}
static int PenaltyCheck(int mute,const char *ip,const char *guid,const char *mac,
    int now,nitmodDatabasePenalty_t *result,int *expired,int removeExpired) {
    sqlite3_stmt *s=0; nitmodDatabasePenalty_t *rows; int count=0,rc,i,found=0;
    if(expired) *expired=0;
    if(!database || !ip || !guid || !mac || !result || !expired || (mute!=0 && mute!=1)) return -1;
    rows=calloc(1024,sizeof(*rows)); if(!rows) return -1;
    if(sqlite3_prepare_v2(database,mute?"SELECT name,guid,ip,mac,reason,made,expires,muter FROM mutes":
        "SELECT name,guid,ip,mac,reason,made,expires,banner FROM bans",-1,&s,0)!=SQLITE_OK) goto failed;
    while((rc=sqlite3_step(s))==SQLITE_ROW) {
        nitmodDatabasePenalty_t *p; sqlite3_int64 time;
        if(count==1024) goto failed; p=&rows[count++]; time=sqlite3_column_int64(s,6);
        if(time<INT_MIN || time>INT_MAX || !TextColumn(s,0,p->name,sizeof(p->name)) ||
           !TextColumn(s,1,p->guid,sizeof(p->guid)) || !TextColumn(s,2,p->ip,sizeof(p->ip)) ||
           !TextColumn(s,3,p->mac,sizeof(p->mac)) || !TextColumn(s,4,p->reason,sizeof(p->reason)) ||
           !TextColumn(s,5,p->made,sizeof(p->made)) || !TextColumn(s,7,p->actor,sizeof(p->actor))) goto failed;
        p->expires=(int)time;
    }
    if(rc!=SQLITE_DONE) goto failed;
    sqlite3_finalize(s); s=0;
    for(i=0;i<count;++i) {
        nitmodDatabasePenalty_t *p=&rows[i];
        int guidEqual=!sqlite3_stricmp(guid,p->guid),macEqual=*mac && !sqlite3_stricmp(mac,p->mac);
        if(p->expires && p->expires<=now && (!mute || guidEqual || macEqual)) {
            if(removeExpired && !NITMOD_DBPenaltySave(mute,p,0)) goto failed;
            ++*expired; if(mute) { free(rows); return 0; } continue;
        }
        if(!found && ((strlen(guid)==32 && guidEqual) ||
           (macEqual && sqlite3_stricmp(mac,"00-00-00-00-00-00")) || (!mute && PenaltyIP(p->ip,ip)))) {
            *result=*p; found=1; if(mute) break;
        }
    }
    free(rows); return found;
failed:
    Error("Invalid penalty table or operation failed"); sqlite3_finalize(s); free(rows); return -1;
}
int NITMOD_DBPenaltyCheck(int mute,const char *ip,const char *guid,const char *mac,
    int now,nitmodDatabasePenalty_t *result,int *expired) {
    return PenaltyCheck(mute,ip,guid,mac,now,result,expired,1);
}
int NITMOD_DBPenaltyPeek(int mute,const char *ip,const char *guid,const char *mac,
    int now,nitmodDatabasePenalty_t *result,int *expired) {
    return PenaltyCheck(mute,ip,guid,mac,now,result,expired,0);
}
int NITMOD_DBRecords(const char *map,nitmodDatabaseRecords_t *result) {
    sqlite3_stmt *s=0; nitmodDatabaseRecords_t next; int i,rc;
    if(!database || !map || !result) return -1;
    if(sqlite3_prepare_v2(database,"SELECT map,maxspreeholder,maxspree,maxspreedate,maxfragsholder,maxfrags,maxfragsdate,maxrspreeholder,maxrspree,maxrspreedate FROM records WHERE map=?1 COLLATE BINARY LIMIT 2",-1,&s,0)!=SQLITE_OK || !BindText(s,1,map)) goto failed;
    rc=sqlite3_step(s); if(rc==SQLITE_DONE) { sqlite3_finalize(s); return 0; }
    memset(&next,0,sizeof(next));
    if(rc!=SQLITE_ROW || !TextColumn(s,0,next.map,sizeof(next.map))) goto failed;
    for(i=0;i<3;++i) {
        sqlite3_int64 value=sqlite3_column_int64(s,2+i*3);
        if(value<0 || value>INT_MAX || !TextColumn(s,1+i*3,next.holder[i],sizeof(next.holder[i])) ||
           !TextColumn(s,3+i*3,next.date[i],sizeof(next.date[i]))) goto failed;
        next.value[i]=(int)value;
    }
    if(sqlite3_step(s)!=SQLITE_DONE) goto failed;
    sqlite3_finalize(s); *result=next; return 1;
failed:
    Error("Invalid or ambiguous map record"); sqlite3_finalize(s); return -1;
}
int NITMOD_DBUpdateRecords(const nitmodDatabaseRecords_t *p) {
    nitmodDatabaseRecords_t next; sqlite3_stmt *s=0; int rc,i,changes=0; const char *sql;
    if(!database || !writable || !p || !Bounded(p->map,sizeof(p->map)) || !*p->map) return -1;
    for(i=0;i<3;++i) if(p->value[i]<0 || !Bounded(p->holder[i],sizeof(p->holder[i])) || !Bounded(p->date[i],sizeof(p->date[i]))) return -1;
    if(!Exec("BEGIN TRANSACTION")) return -1;
    rc=NITMOD_DBRecords(p->map,&next); if(rc<0) goto failed;
    if(!rc) { next=*p; changes=7; }
    else for(i=0;i<3;++i) if(p->value[i]>next.value[i]) {
        next.value[i]=p->value[i]; strcpy(next.holder[i],p->holder[i]); strcpy(next.date[i],p->date[i]); changes|=1<<i;
    }
    sql=rc?"UPDATE records SET maxspreeholder=?2,maxspree=?3,maxspreedate=?4,maxfragsholder=?5,maxfrags=?6,maxfragsdate=?7,maxrspreeholder=?8,maxrspree=?9,maxrspreedate=?10 WHERE map=?1 COLLATE BINARY":
        "INSERT INTO records(map,maxspreeholder,maxspree,maxspreedate,maxfragsholder,maxfrags,maxfragsdate,maxrspreeholder,maxrspree,maxrspreedate) VALUES(?1,?2,?3,?4,?5,?6,?7,?8,?9,?10)";
    if(changes) {
        if(sqlite3_prepare_v2(database,sql,-1,&s,0)!=SQLITE_OK || !BindText(s,1,next.map)) goto failed;
        for(i=0;i<3;++i) if(!BindText(s,2+i*3,next.holder[i]) || sqlite3_bind_int(s,3+i*3,next.value[i])!=SQLITE_OK || !BindText(s,4+i*3,next.date[i])) goto failed;
        if(sqlite3_step(s)!=SQLITE_DONE) goto failed;
        sqlite3_finalize(s); s=0;
    }
    if(!Exec("COMMIT")) goto failed; return changes;
failed:
    sqlite3_finalize(s); sqlite3_exec(database,"ROLLBACK",0,0,0); return -1;
}
int NITMOD_DBClearRecords(const char *map) {
    sqlite3_stmt *s=0; int ok;
    if(!database || !writable) return 0;
    if(!map) return Exec("DELETE FROM records");
    ok=sqlite3_prepare_v2(database,"DELETE FROM records WHERE map=?1 COLLATE BINARY",-1,&s,0)==SQLITE_OK &&
       BindText(s,1,map) && sqlite3_step(s)==SQLITE_DONE;
    if(!ok) Error(sqlite3_errmsg(database)); sqlite3_finalize(s); return ok;
}

/* Synchronization operates on rows inside the destination transaction.  It
 * deliberately does not replace a live SQLite file with a serialized image.
 * Independent column edits merge; a changed common column is a conflict. */
static sqlite3 *storage;
static sqlite3 *SyncImage(const void *bytes,int length) {
    sqlite3 *db=0; unsigned char *copy; sqlite3_stmt *s=0;
    if(!bytes || length<100 || length>64*1024*1024 || memcmp(bytes,"SQLite format 3\000",16)) {
        Error("Invalid synchronization image"); return 0;
    }
    if(sqlite3_open(":memory:",&db)!=SQLITE_OK) goto failed;
    sqlite3_db_config(db,SQLITE_DBCONFIG_DQS_DML,0,0);
    copy=sqlite3_malloc(length); if(!copy) goto failed;
    memcpy(copy,bytes,length);
    if(sqlite3_deserialize(db,"main",copy,length,length,
        SQLITE_DESERIALIZE_FREEONCLOSE|SQLITE_DESERIALIZE_RESIZEABLE)!=SQLITE_OK) goto failed;
    if(sqlite3_prepare_v2(db,"PRAGMA quick_check",-1,&s,0)!=SQLITE_OK ||
       sqlite3_step(s)!=SQLITE_ROW || strcmp((const char *)sqlite3_column_text(s,0),"ok") ||
       sqlite3_step(s)!=SQLITE_DONE) goto failed;
    sqlite3_finalize(s); return db;
failed:
    Error(db?sqlite3_errmsg(db):"Synchronization allocation failed");
    sqlite3_finalize(s); if(db) sqlite3_close(db); return 0;
}
static void *SyncExport(sqlite3 *db,int *length) {
    sqlite3_int64 n=0; void *out=sqlite3_serialize(db,"main",&n,0);
    if(!out || n<100 || n>64*1024*1024) {
        sqlite3_free(out); Error("Synchronization image exceeds 64 MiB"); return 0;
    }
    *length=(int)n; return out;
}
static int SyncPrepare(sqlite3 *db,sqlite3_stmt **s,char *sql) {
    int rc=sql && sqlite3_prepare_v2(db,sql,-1,s,0)==SQLITE_OK;
    if(!rc) Error(sql?sqlite3_errmsg(db):"Synchronization allocation failed");
    sqlite3_free(sql); return rc;
}
static int SyncSame(sqlite3_stmt *a,int i,sqlite3_stmt *b,int j) {
    int type=sqlite3_column_type(a,i),size;
    if(type!=sqlite3_column_type(b,j)) return 0;
    if(type==SQLITE_NULL) return 1;
    if(type==SQLITE_INTEGER) return sqlite3_column_int64(a,i)==sqlite3_column_int64(b,j);
    if(type==SQLITE_FLOAT) return sqlite3_column_double(a,i)==sqlite3_column_double(b,j);
    size=sqlite3_column_bytes(a,i);
    return size==sqlite3_column_bytes(b,j) &&
        (!size || !memcmp(sqlite3_column_blob(a,i),sqlite3_column_blob(b,j),size));
}
static int SyncRowSame(sqlite3_stmt *a,sqlite3_stmt *b,int n) {
    int i; for(i=1;i<n;++i) if(!SyncSame(a,i,b,i)) return 0; return 1;
}
static int SyncFind(sqlite3_stmt *s,sqlite3_stmt *row) {
    int rc;
    sqlite3_reset(s); sqlite3_clear_bindings(s);
    if(sqlite3_bind_value(s,1,sqlite3_column_value(row,0))!=SQLITE_OK) return -1;
    rc=sqlite3_step(s); return rc==SQLITE_ROW?1:rc==SQLITE_DONE?0:-1;
}
static int SyncConflict(const char *table,const char *column) {
    char text[256]; sqlite3_snprintf(sizeof(text),text,"SQLite sync conflict in %s.%s",table,column);
    Error(text); return 0;
}
static int SyncTable(sqlite3 *base,sqlite3 *local,sqlite3 *remote,const char *table,const char *onlyGuid) {
    const char *key=!strcmp(table,"users")?"guid":!strcmp(table,"records")?"map":!strcmp(table,"mails")?"id":"rowid";
    sqlite3_stmt *b=0,*l=0,*r=0,*all=0,*lookup=0,*s=0;
    sqlite3_str *columns=0,*sql=0; char *projection=0; int n,i,rc,lr,rr,ok=0,exists;
    if(!SyncPrepare(local,&s,sqlite3_mprintf("SELECT sql FROM sqlite_master WHERE type='table' AND name=%Q",table))) goto done;
    rc=sqlite3_step(s); if(rc==SQLITE_DONE) { ok=1; goto done; } if(rc!=SQLITE_ROW) goto done;
    if(!SyncPrepare(remote,&lookup,sqlite3_mprintf("SELECT count(*) FROM sqlite_master WHERE type='table' AND name=%Q",table)) || sqlite3_step(lookup)!=SQLITE_ROW) goto done;
    exists=sqlite3_column_int(lookup,0); sqlite3_finalize(lookup); lookup=0;
    if(!exists && sqlite3_exec(remote,(const char *)sqlite3_column_text(s,0),0,0,0)!=SQLITE_OK) goto sqlError;
    sqlite3_finalize(s); s=0;
    if(!SyncPrepare(local,&all,sqlite3_mprintf("SELECT \"%w\",* FROM \"%w\"",key,table))) goto done;
    n=sqlite3_column_count(all); columns=sqlite3_str_new(0);
    sqlite3_str_appendf(columns,"\"%w\"",key);
    for(i=1;i<n;++i) sqlite3_str_appendf(columns,",\"%w\"",sqlite3_column_name(all,i));
    projection=sqlite3_str_finish(columns); columns=0; if(!projection) goto done;
    if(!SyncPrepare(base,&s,sqlite3_mprintf("SELECT count(*) FROM sqlite_master WHERE type='table' AND name=%Q",table)) || sqlite3_step(s)!=SQLITE_ROW) goto done;
    exists=sqlite3_column_int(s,0); sqlite3_finalize(s); s=0;
    /* No original mutator drops tables or removes columns.  Such a concurrent
     * schema change is rejected by preparation, rather than guessed around. */
    if(!SyncPrepare(base,&b,exists?sqlite3_mprintf("SELECT %s FROM \"%w\"",projection,table):sqlite3_mprintf("SELECT NULL WHERE 0")) ||
       !SyncPrepare(local,&l,sqlite3_mprintf("SELECT %s FROM \"%w\" WHERE \"%w\" IS ?1",projection,table,key)) ||
       !SyncPrepare(remote,&r,sqlite3_mprintf("SELECT %s FROM \"%w\" WHERE \"%w\" IS ?1",projection,table,key))) goto done;
    /* Natural keys in old databases are not necessarily declared UNIQUE. */
    for(i=0;i<3;++i) {
        sqlite3 *db=i==0?base:i==1?local:remote;
        if(i==0 && !exists) continue;
        if(!SyncPrepare(db,&s,sqlite3_mprintf("SELECT 1 FROM \"%w\" GROUP BY \"%w\" HAVING count(*)>1 OR \"%w\" IS NULL LIMIT 1",table,key,key))) goto done;
        rc=sqlite3_step(s); sqlite3_finalize(s); s=0;
        if(rc!=SQLITE_DONE) { SyncConflict(table,"ambiguous key"); goto done; }
    }
    while((rc=sqlite3_step(b))==SQLITE_ROW) {
        int changed=0;
        if(onlyGuid && strcmp((const char *)sqlite3_column_text(b,0),onlyGuid)) continue;
        lr=SyncFind(l,b); rr=SyncFind(r,b); if(lr<0 || rr<0) goto sqlError;
        if(!lr) {
            if(!rr) continue;
            if(!SyncRowSame(b,r,n)) { SyncConflict(table,"delete/update"); goto done; }
            if(!SyncPrepare(remote,&s,sqlite3_mprintf("DELETE FROM \"%w\" WHERE \"%w\" IS ?1",table,key))) goto done;
            sqlite3_bind_value(s,1,sqlite3_column_value(b,0));
        } else {
            for(i=1;i<n;++i) if(!SyncSame(b,i,l,i)) ++changed;
            if(!changed) continue;
            if(!rr) { SyncConflict(table,"update/delete"); goto done; }
            sql=sqlite3_str_new(0); sqlite3_str_appendf(sql,"UPDATE \"%w\" SET ",table); changed=0;
            for(i=1;i<n;++i) if(!SyncSame(b,i,l,i)) {
                if(!SyncSame(b,i,r,i) && !SyncSame(l,i,r,i)) { SyncConflict(table,sqlite3_column_name(l,i)); goto done; }
                sqlite3_str_appendf(sql,"%s\"%w\"=?%d",changed++?",":"",sqlite3_column_name(l,i),i+1);
            }
            sqlite3_str_appendf(sql," WHERE \"%w\" IS ?1",key);
            { char *query=sqlite3_str_finish(sql); sql=0; if(!SyncPrepare(remote,&s,query)) goto done; }
            sqlite3_bind_value(s,1,sqlite3_column_value(b,0));
            for(i=1;i<n;++i) if(!SyncSame(b,i,l,i)) sqlite3_bind_value(s,i+1,sqlite3_column_value(l,i));
        }
        if(sqlite3_step(s)!=SQLITE_DONE) goto sqlError;
        sqlite3_finalize(s); s=0;
    }
    if(rc!=SQLITE_DONE) goto sqlError;
    if(exists && !SyncPrepare(base,&lookup,sqlite3_mprintf("SELECT %s FROM \"%w\" WHERE \"%w\" IS ?1",projection,table,key))) goto done;
    while((rc=sqlite3_step(all))==SQLITE_ROW) {
        int first=1;
        if(onlyGuid && strcmp((const char *)sqlite3_column_text(all,0),onlyGuid)) continue;
        lr=exists?SyncFind(lookup,all):0; if(lr<0) goto sqlError; if(lr) continue;
        rr=SyncFind(r,all); if(rr<0) goto sqlError;
        if(rr) { if(SyncRowSame(all,r,n)) continue; SyncConflict(table,"insert/insert"); goto done; }
        sql=sqlite3_str_new(0); sqlite3_str_appendf(sql,"INSERT INTO \"%w\" (",table);
        /* User IDs are SQLite allocation details; the original GUID is the
         * stable key.  Concurrent unrelated user inserts may reuse an ID. */
        for(i=0;i<n;++i) {
            const char *name=i?sqlite3_column_name(all,i):key;
            if((!strcmp(table,"users") && !strcmp(name,"id")) || (i==0 && strcmp(key,"rowid"))) continue;
            sqlite3_str_appendf(sql,"%s\"%w\"",first?"":",",name); first=0;
        }
        sqlite3_str_appendall(sql,") VALUES ("); first=1;
        for(i=0;i<n;++i) {
            const char *name=i?sqlite3_column_name(all,i):key;
            if((!strcmp(table,"users") && !strcmp(name,"id")) || (i==0 && strcmp(key,"rowid"))) continue;
            sqlite3_str_appendf(sql,"%s?%d",first?"":",",i+1); first=0;
        }
        sqlite3_str_appendall(sql,")");
        { char *query=sqlite3_str_finish(sql); sql=0; if(!SyncPrepare(remote,&s,query)) goto done; }
        for(i=0;i<n;++i) sqlite3_bind_value(s,i+1,sqlite3_column_value(all,i));
        if(sqlite3_step(s)!=SQLITE_DONE) goto sqlError;
        sqlite3_finalize(s); s=0;
    }
    if(rc!=SQLITE_DONE) goto sqlError; ok=1; goto done;
sqlError:
    Error(sqlite3_errmsg(remote));
done:
    sqlite3_finalize(b); sqlite3_finalize(l); sqlite3_finalize(r); sqlite3_finalize(all); sqlite3_finalize(lookup); sqlite3_finalize(s);
    sqlite3_free(projection); if(columns) sqlite3_free(sqlite3_str_finish(columns)); if(sql) sqlite3_free(sqlite3_str_finish(sql));
    return ok;
}
static int SyncSchema(sqlite3 *base,sqlite3 *local,sqlite3 *remote) {
    sqlite3_stmt *rows=0,*b=0,*r=0,*d=0; int rc,br,rr,ok=0;
    const char *query="SELECT name,sql FROM sqlite_master WHERE sql IS NOT NULL AND name NOT LIKE 'sqlite_%' AND name!='nitmod_storage_origin' ORDER BY type='trigger',type='view',type='index'";
    if(!SyncPrepare(local,&rows,sqlite3_mprintf("%s",query)) ||
       !SyncPrepare(base,&b,sqlite3_mprintf("SELECT sql FROM sqlite_master WHERE name=?1")) ||
       !SyncPrepare(remote,&r,sqlite3_mprintf("SELECT sql FROM sqlite_master WHERE name=?1"))) goto done;
    while((rc=sqlite3_step(rows))==SQLITE_ROW) {
        const char *name=(const char *)sqlite3_column_text(rows,0),*sql=(const char *)sqlite3_column_text(rows,1);
        br=SyncFind(b,rows); rr=SyncFind(r,rows); if(br<0||rr<0) goto done;
        if(br && !strcmp(sql,(const char *)sqlite3_column_text(b,0))) continue;
        if(rr && !strcmp(sql,(const char *)sqlite3_column_text(r,0))) continue;
        if(br || rr) { SyncConflict(name,"schema change"); goto done; }
        if(sqlite3_exec(remote,sql,0,0,0)!=SQLITE_OK) { Error(sqlite3_errmsg(remote)); goto done; }
    }
    if(rc!=SQLITE_DONE) goto done;
    sqlite3_finalize(rows); rows=0;
    if(!SyncPrepare(base,&rows,sqlite3_mprintf("%s",query)) || !SyncPrepare(local,&d,sqlite3_mprintf("SELECT sql FROM sqlite_master WHERE name=?1"))) goto done;
    while((rc=sqlite3_step(rows))==SQLITE_ROW) {
        br=SyncFind(d,rows); rr=SyncFind(r,rows);
        if(br<0||rr<0) goto done;
        if(!br && rr) { SyncConflict((const char *)sqlite3_column_text(rows,0),"schema removal"); goto done; }
    }
    ok=rc==SQLITE_DONE;
done:
    sqlite3_finalize(rows); sqlite3_finalize(b); sqlite3_finalize(r); sqlite3_finalize(d); return ok;
}
static int SyncMerge(sqlite3 *base,sqlite3 *local,sqlite3 *remote,const char *guid) {
    sqlite3_stmt *rows=0; int rc,ok=0;
    if(guid) return SyncTable(base,local,remote,"users",guid);
    if(!SyncSchema(base,local,remote)) return 0;
    if(!SyncPrepare(local,&rows,sqlite3_mprintf("SELECT name FROM sqlite_master WHERE type='table' AND name NOT LIKE 'sqlite_%%' AND name!='nitmod_storage_origin'"))) return 0;
    while((rc=sqlite3_step(rows))==SQLITE_ROW)
        if(!SyncTable(base,local,remote,(const char *)sqlite3_column_text(rows,0),0)) goto done;
    ok=rc==SQLITE_DONE;
done:
    sqlite3_finalize(rows); return ok;
}
void *NITMOD_DBMergeImages(const void *before,int beforeLength,const void *changed,int changedLength,
                         const void *current,int currentLength,int *length) {
    sqlite3 *base=0,*local=0,*remote=0; void *out=0;
    *length=0;
    base=SyncImage(before,beforeLength); local=SyncImage(changed,changedLength); remote=SyncImage(current,currentLength);
    if(base && local && remote && sqlite3_exec(remote,"BEGIN IMMEDIATE",0,0,0)==SQLITE_OK &&
       SyncMerge(base,local,remote,0) && sqlite3_exec(remote,"COMMIT",0,0,0)==SQLITE_OK) out=SyncExport(remote,length);
    if(base) sqlite3_close(base); if(local) sqlite3_close(local); if(remote) sqlite3_close(remote); return out;
}
/* Copy a single existing cached row.  Missing persistent rows retain the
 * cached entry, matching callback_loadsingleuser's no-result behavior. */
int NITMOD_DBSyncUser(const void *current,int length,const char *guid) {
    sqlite3 *source=SyncImage(current,length),*save; nitmodDatabaseAccount_t account; int rc;
    if(!source) return -1;
    save=database; database=source; rc=NITMOD_DBAccount(guid,&account); database=save; sqlite3_close(source);
    if(rc==1) return NITMOD_DBSaveAccount(&account,2)?1:-1;
    return rc;
}
void NITMOD_DBStorageClose(void) { if(storage) sqlite3_close(storage); storage=0; }
int NITMOD_DBStorageOpen(const char *path) {
#ifndef __EMSCRIPTEN__
    NITMOD_DBStorageClose();
    if(sqlite3_open_v2(path,&storage,SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE,0)!=SQLITE_OK) {
        Error(storage?sqlite3_errmsg(storage):"Cannot open live SQLite database"); NITMOD_DBStorageClose(); return 0;
    }
    sqlite3_db_config(storage,SQLITE_DBCONFIG_DQS_DML,0,0);
    sqlite3_busy_timeout(storage,250); return 1;
#else
    (void)path; Error("Engine VFS has no SQLite locking interface"); return 0;
#endif
}
void *NITMOD_DBStorageRead(int *length) {
    void *out=0; *length=0;
    if(storage && sqlite3_exec(storage,"BEGIN",0,0,0)==SQLITE_OK) {
        out=SyncExport(storage,length); sqlite3_exec(storage,"ROLLBACK",0,0,0);
    } else Error(storage?sqlite3_errmsg(storage):"Live storage is closed");
    return out;
}
int NITMOD_DBStorageCommit(const void *before,int length) {
    sqlite3 *base=SyncImage(before,length); int ok=0;
    if(base && storage) {
        if(sqlite3_exec(storage,"BEGIN IMMEDIATE",0,0,0)!=SQLITE_OK) Error(sqlite3_errmsg(storage));
        else {
            ok=SyncMerge(base,database,storage,0);
            if(ok && sqlite3_exec(storage,"COMMIT",0,0,0)!=SQLITE_OK) { Error(sqlite3_errmsg(storage)); ok=0; }
            if(!ok) sqlite3_exec(storage,"ROLLBACK",0,0,0);
        }
    }
    if(base) sqlite3_close(base); return ok;
}

void *NITMOD_DBImageSyncUser(const void *cache,int cacheLength,const void *current,int currentLength,const char *guid,int *length) {
    sqlite3 *db=SyncImage(cache,cacheLength),*save=database; int saveUsers=users,saveVersion=version,saveWritable=writable; void *out=0;
    *length=0; if(!db) return 0;
    database=db; writable=1;
    if(NITMOD_DBSyncUser(current,currentLength,guid)>=0) out=SyncExport(db,length);
    database=save; users=saveUsers; version=saveVersion; writable=saveWritable; sqlite3_close(db); return out;
}
void *NITMOD_DBImageOrigin(const void *image,int imageLength,int *length) {
    sqlite3 *db=SyncImage(image,imageLength); sqlite3_stmt *s=0; void *out=0; int n;
    *length=-1; if(!db) return 0;
    if(sqlite3_prepare_v2(db,"SELECT image FROM nitmod_storage_origin WHERE id=1",-1,&s,0)==SQLITE_OK && sqlite3_step(s)==SQLITE_ROW) {
        n=sqlite3_column_bytes(s,0); *length=n;
        if(n && (out=sqlite3_malloc(n))) memcpy(out,sqlite3_column_blob(s,0),n);
        if(n && !out) *length=-1;
    }
    sqlite3_finalize(s); sqlite3_close(db); return out;
}
void *NITMOD_DBImageSetOrigin(const void *image,int imageLength,const void *origin,int originLength,int *length) {
    sqlite3 *db=SyncImage(image,imageLength); sqlite3_stmt *s=0; void *out=0;
    *length=0; if(!db) return 0;
    if(sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS nitmod_storage_origin(id INTEGER PRIMARY KEY CHECK(id=1),image BLOB)",0,0,0)==SQLITE_OK &&
       sqlite3_prepare_v2(db,"INSERT INTO nitmod_storage_origin VALUES(1,?1) ON CONFLICT(id) DO UPDATE SET image=excluded.image WHERE image IS NOT excluded.image",-1,&s,0)==SQLITE_OK &&
       sqlite3_bind_blob(s,1,origin,originLength,SQLITE_STATIC)==SQLITE_OK && sqlite3_step(s)==SQLITE_DONE)
        out=SyncExport(db,length);
    if(!out) Error(sqlite3_errmsg(db)); sqlite3_finalize(s); sqlite3_close(db); return out;
}
int NITMOD_DBStorageInitSchema(int mail,int records) {
    sqlite3 *save=database; int saveUsers=users,saveVersion=version,saveWritable=writable,ok;
    if(!storage) return 0;
    database=storage; writable=1; ok=NITMOD_DBInitSchema(mail,records);
    database=save; users=saveUsers; version=saveVersion; writable=saveWritable; return ok;
}

void *NITMOD_DBImageInitialize(const void *image,int imageLength,int mail,int records,int *length) {
    sqlite3 *db=SyncImage(image,imageLength),*save=database; int saveUsers=users,saveVersion=version,saveWritable=writable; void *out=0;
    *length=0; if(!db) return 0;
    database=db; writable=1;
    if(NITMOD_DBInitSchema(mail,records)) out=SyncExport(db,length);
    database=save; users=saveUsers; version=saveVersion; writable=saveWritable; sqlite3_close(db); return out;
}
void *NITMOD_DBMergeUserImages(const void *before,int beforeLength,const void *changed,int changedLength,
                         const void *current,int currentLength,const char *guid,int *length) {
    sqlite3 *base=0,*local=0,*remote=0; void *out=0;
    *length=0;
    base=SyncImage(before,beforeLength); local=SyncImage(changed,changedLength); remote=SyncImage(current,currentLength);
    if(base && local && remote && sqlite3_exec(remote,"BEGIN IMMEDIATE",0,0,0)==SQLITE_OK &&
       SyncMerge(base,local,remote,guid) && sqlite3_exec(remote,"COMMIT",0,0,0)==SQLITE_OK) out=SyncExport(remote,length);
    if(base) sqlite3_close(base); if(local) sqlite3_close(local); if(remote) sqlite3_close(remote); return out;
}
