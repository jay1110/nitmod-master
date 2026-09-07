#include "nitmod_database.h"
#include "../sqlite/sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>

static sqlite3 *database;
static char lastError[256];
static int users,version;
static int writable;
static unsigned int epoch;
unsigned int NITMOD_DBEpoch(void) { return epoch; }
static void Error(const char *text) {
    size_t n=strlen(text); if(n>=sizeof(lastError)) n=sizeof(lastError)-1;
    memcpy(lastError,text,n); lastError[n]=0;
}
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
const char *NITMOD_DBError(void) { return lastError; }
void NITMOD_DBClose(void) {
    ++epoch;
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
int NITMOD_DBPenaltyCheck(int mute,const char *ip,const char *guid,const char *mac,
    int now,nitmodDatabasePenalty_t *result,int *expired) {
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
            if(!NITMOD_DBPenaltySave(mute,p,0)) goto failed;
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
