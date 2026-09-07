#include "g_local.h"
#include "nitmod_database.h"
#include "g_nitmod_database.h"
#include "g_nitmod_config.h"
#include "g_nitmod_accounts.h"
#include "nitmod_sha1.h"
#include "nitmod_xp.h"
#include "g_nitmod_records.h"
#include "g_nitmod_admin.h"
#include "../src_2.60/sqlite/sqlite3.h"
#include <assert.h>
static unsigned char *fixture;
static sqlite3_int64 fixtureLength;
static const char *configuredPath="sample.sqlite";
static int closes;
static unsigned char *saved;
static int savedLength,shortWrite,corruptReadback,writes;
static char selectedPath[MAX_QPATH];
static struct { char path[MAX_QPATH]; unsigned char *bytes; int length; } files[256];
static int fileCount,renameFailure;
gentity_t g_entities[MAX_GENTITIES];
level_locals_t level;
vmCvar_t g_XPSave;
vmCvar_t g_XPSaveMaxAge;
vmCvar_t g_gametype,g_currentRound,g_resetXPMapCount,g_DMOptions;
g_campaignInfo_t g_campaigns[1];
static int nowSeconds=1700000000,rankCalls,decaySeconds,decayEnabled;
void G_CalcRank(gclient_t *client) { ++rankCalls; }
void SetWolfSpawnWeapons(gclient_t *client) { memset(client->ps.ammo,0,sizeof(client->ps.ammo)); memset(client->ps.ammoclip,0,sizeof(client->ps.ammoclip)); }
void G_NITMOD_XPDecay(gentity_t *ent,int seconds,qboolean force) { assert(force); decaySeconds=seconds; }
static gclient_t clients[3];
static int mailEnabled,recordsEnabled,argumentCount,dropped;
static const char *arguments[5];
static const char *securePassword="";
static char messages[16384];
static const char *levelText="**********\nlevel = 0\nname = Guest\nflags = admintest records\n**********\nlevel = 1\nname = Moderator\nflags = records\n**********\nlevel = 2\nname = Master\nflags = all\n";
int trap_Argc(void) { return argumentCount; }
void trap_Argv(int i,char *out,int size) { Q_strncpyz(out,i<argumentCount?arguments[i]:"",size); }
void trap_SendServerCommand(int n,const char *text) { Q_strcat(messages,sizeof(messages),text); }
void trap_DropClient(int n,const char *reason,int banTime) { ++dropped; }
void ClientUserinfoChanged(int n) { }
int trap_RealTime(qtime_t *time) { memset(time,0,sizeof(*time)); return nowSeconds; }
int G_NITMOD_LegacyCvarInteger(const char *name,int fallback) {
    if(!strcmp(name,"n_userMail")) return mailEnabled;
    if(!strcmp(name,"n_mapRecords")) return recordsEnabled;
    if(!strcmp(name,"g_GUIDChecks")) return 1;
    if(!strcmp(name,"g_XPDecay")) return decayEnabled;
    return 0;
}
void trap_Cvar_Set(const char *name,const char *value) {
    assert(!strcmp(name,"n_SQLiteDBPath")); Q_strncpyz(selectedPath,value,sizeof(selectedPath)); configuredPath=selectedPath;
}
void G_NITMOD_LegacyCvarString(const char *name,char *out,int size,const char *fallback) {
    if(!strcmp(name,"g_secureShrubPassword")) { Q_strncpyz(out,securePassword,size); return; }
    assert(!strcmp(name,"n_SQLiteDBPath")); Q_strncpyz(out,configuredPath,size);
}
int trap_FS_FOpenFile(const char *name,fileHandle_t *file,fsMode_t mode) {
    if(!strcmp(name,"levels.db")) { assert(mode==FS_READ); *file=3; return strlen(levelText); }
    if(strstr(name,".d/")) {
        int i; for(i=0;i<fileCount;++i) if(!strcmp(files[i].path,name)) break;
        if(mode==FS_WRITE) {
            assert(i==fileCount && fileCount<256); Q_strncpyz(files[i].path,name,MAX_QPATH); ++fileCount;
        }
        *file=i<fileCount?i+10:0; return *file?files[i].length:-1;
    }
    if(!strcmp(name,"new.sqlite")) {
        if(mode==FS_WRITE) { assert(!saved); *file=2; ++writes; return 0; }
        *file=saved?2:0; return saved?savedLength:-1;
    }
    assert(!strcmp(name,"sample.sqlite") && mode==FS_READ);
    *file=fixture?1:0; return fixture?(int)fixtureLength:-1;
}
void trap_FS_Read(void *out,int length,fileHandle_t file) {
    if(file==3) { assert(length==(int)strlen(levelText)); memcpy(out,levelText,length); return; }
    if(file>=10) { assert(length==files[file-10].length); memcpy(out,files[file-10].bytes,length); return; }
    if(file==2) { assert(length==savedLength); memcpy(out,saved,length); if(corruptReadback) ((char *)out)[0]^=1; return; }
    assert(file==1 && length==fixtureLength); memcpy(out,fixture,length);
}
int trap_FS_Write(const void *bytes,int length,fileHandle_t file) {
    if(file>=10) {
        int i=file-10; assert(!files[i].bytes); files[i].length=length-(shortWrite?1:0);
        files[i].bytes=malloc(files[i].length); memcpy(files[i].bytes,bytes,files[i].length); return files[i].length;
    }
    assert(file==2 && !saved); savedLength=length-(shortWrite?1:0);
    saved=malloc(savedLength); memcpy(saved,bytes,savedLength); return savedLength;
}
void trap_FS_FCloseFile(fileHandle_t file) { assert(file==1 || file==2 || file==3 || file>=10); ++closes; }
int trap_FS_GetFileList(const char *path,const char *extension,char *list,int size) {
    int i,count=0,used=0; size_t prefix=strlen(path);
    for(i=0;i<fileCount;++i) if(!strncmp(path,files[i].path,prefix) && files[i].path[prefix]=='/') {
        const char *name=files[i].path+prefix+1; int n=strlen(name)+1;
        assert(used+n<size); memcpy(list+used,name,n); used+=n; ++count;
    }
    return count;
}
int trap_FS_Rename(const char *from,const char *to) {
    int i; if(renameFailure) return -1;
    for(i=0;i<fileCount;++i) assert(strcmp(files[i].path,to));
    for(i=0;i<fileCount;++i) if(!strcmp(files[i].path,from)) { Q_strncpyz(files[i].path,to,MAX_QPATH); return 0; }
    abort(); return -1;
}
void G_LogPrintf(const char *format,...) { }
void G_Printf(const char *format,...) { char text[2048]; va_list args; va_start(args,format); Q_vsnprintf(text,sizeof(text),format,args); va_end(args); Q_strcat(messages,sizeof(messages),text); }
void Com_Printf(const char *format,...) { }
void Com_Error(int code,const char *format,...) { abort(); }
#undef vsnprintf
int Q_vsnprintf(char *out,int size,const char *format,va_list args) { return vsnprintf(out,(size_t)size,format,args); }
static void Make(const char *sql) {
    sqlite3 *db=0;
    sqlite3_free(fixture); fixture=0;
    assert(sqlite3_open(":memory:",&db)==SQLITE_OK);
    assert(sqlite3_exec(db,sql,0,0,0)==SQLITE_OK);
    fixture=sqlite3_serialize(db,"main",&fixtureLength,0);
    assert(fixture && fixtureLength>=100); sqlite3_close(db);
}
static int ExportScalar(const char *sql) {
    sqlite3 *db=0; sqlite3_stmt *s=0; int length,value; void *bytes=NITMOD_DBExport(&length);
    assert(bytes && sqlite3_open(":memory:",&db)==SQLITE_OK);
    assert(sqlite3_deserialize(db,"main",bytes,length,length,SQLITE_DESERIALIZE_READONLY)==SQLITE_OK);
    assert(sqlite3_prepare_v2(db,sql,-1,&s,0)==SQLITE_OK && sqlite3_step(s)==SQLITE_ROW);
    value=sqlite3_column_int(s,0); sqlite3_finalize(s); sqlite3_close(db); NITMOD_DBFreeExport(bytes); return value;
}
static void SchemaChecks(void) {
    int length; void *bytes;
    assert(NITMOD_DBOpenWorking(NULL,0) && NITMOD_DBInitSchema(0,0));
    assert(NITMOD_DBVersion()==0 && NITMOD_DBUserCount()==0);
    assert(ExportScalar("SELECT count(*) FROM sqlite_master WHERE type='table'")==3);
    assert(NITMOD_DBInitSchema(1,1) && NITMOD_DBVersion()==1);
    assert(ExportScalar("SELECT count(*) FROM pragma_table_info('records')")==10);
    bytes=NITMOD_DBExport(&length); assert(NITMOD_DBOpenWorking(bytes,length)); NITMOD_DBFreeExport(bytes);
    assert(NITMOD_DBInitSchema(1,1) && NITMOD_DBVersion()==2);
    assert(ExportScalar("SELECT count(*) FROM pragma_table_info('users') WHERE name='id' AND pk=1")==1);
    assert(ExportScalar("SELECT count(*) FROM sqlite_master WHERE type='index' AND name='users_guid'")==1);
    assert(NITMOD_DBInitSchema(1,1) && NITMOD_DBVersion()==2);
    /* Original v0 record upgrade retains existing record values. */
    Make("CREATE TABLE records(map,maxspreeholder,maxspree,maxspreedate,maxfragsholder,maxfrags,maxfragsdate); INSERT INTO records VALUES('map','A',9,'date','B',12,'date');");
    assert(NITMOD_DBOpenWorking(fixture,(int)fixtureLength) && NITMOD_DBInitSchema(1,1));
    assert(NITMOD_DBVersion()==1 && ExportScalar("SELECT maxrspree FROM records")==0);
    assert(ExportScalar("SELECT maxfrags FROM records")==12);
    /* Use the exact complete legacy columns for migration and duplicate rule. */
    Make("CREATE TABLE users(name,guid,ip,level,flags,gtext,gsound,mac,xp,timestamp,login,password);"
         "INSERT INTO users VALUES('old','X','ip',1,'','','','','',0,'login','hash');"
         "INSERT INTO users VALUES('new','X','ip',7,'all','','','','',0,'login','hash'); PRAGMA user_version=1;");
    assert(NITMOD_DBOpenWorking(fixture,(int)fixtureLength) && NITMOD_DBInitSchema(1,1));
    assert(ExportScalar("SELECT count(*) FROM users")==1 && ExportScalar("SELECT level FROM users")==7);
    /* Original sets version back to 1 when records did not exist. */
    assert(NITMOD_DBVersion()==1);
    Make("CREATE TABLE users(name,guid,ip,level,flags,gtext,gsound,mac,xp,timestamp,login,password);"
         "INSERT INTO users VALUES('A','X','',1,'','','','','',0,'','');"
         "INSERT INTO users SELECT * FROM users; INSERT INTO users SELECT * FROM users; PRAGMA user_version=1;");
    assert(NITMOD_DBOpenWorking(fixture,(int)fixtureLength));
    assert(!NITMOD_DBInitSchema(1,1));
    assert(NITMOD_DBVersion()==1 && ExportScalar("SELECT count(*) FROM users")==4);
    assert(ExportScalar("SELECT count(*) FROM sqlite_master WHERE name IN ('users_tmp','users_tmp2','bans')")==0);
    /* Failure halfway through record ALTERs must roll back the earlier ALTER. */
    Make("CREATE TABLE records(map,maxrspree); INSERT INTO records VALUES('map',8);");
    assert(NITMOD_DBOpenWorking(fixture,(int)fixtureLength) && !NITMOD_DBInitSchema(1,1));
    assert(NITMOD_DBVersion()==0 && ExportScalar("SELECT count(*) FROM pragma_table_info('records')")==2);
    assert(ExportScalar("SELECT maxrspree FROM records")==8);
    NITMOD_DBClose();
    puts("SQLite schema: fresh DB, feature gates, v0 records, v1 users, duplicate semantics, reopen, idempotence and rollback: PASS");
}
static void AccountChecks(void) {
    nitmodDatabaseAccount_t a,b,before;
    int length; void *bytes;
    assert(NITMOD_DBOpenWorking(NULL,0) && NITMOD_DBInitSchema(1,1));
    memset(&a,0,sizeof(a)); strcpy(a.user.guid,"GUID"); strcpy(a.user.name,"quoted '\" account");
    strcpy(a.user.flags,"admintest help"); strcpy(a.user.xp,"1 2 3 4 5 6 7"); a.user.level=2;
    strcpy(a.ip,"127.0.0.1"); strcpy(a.mac,"01:02:03:04:05:06");
    strcpy(a.gtext,"welcome"); strcpy(a.gsound,"sound/test.wav"); strcpy(a.login,"alice");
    strcpy(a.password,"0123456789012345678901234567890123456789"); a.timestamp=123456;
    assert(NITMOD_DBSaveAccount(&a,2) && NITMOD_DBUserCount()==1); /* update inserts */
    assert(NITMOD_DBAccount("GUID",&b)==1 && !memcmp(&a,&b,sizeof(a)));
    a.user.level=8; assert(NITMOD_DBSaveAccount(&a,1) && NITMOD_DBUserCount()==1); /* add updates */
    assert(NITMOD_DBAccount("GUID",&b)==1 && b.user.level==8);
    before=b; assert(NITMOD_DBAccount("guid",&b)==0 && !memcmp(&before,&b,sizeof(b)));
    strcpy(a.user.guid,"' OR 1=1 --"); assert(NITMOD_DBSaveAccount(&a,1) && NITMOD_DBUserCount()==2);
    assert(NITMOD_DBMigrateUserLevel(8,4));
    assert(NITMOD_DBAccount("GUID",&b)==1 && b.user.level==4);
    assert(NITMOD_DBSaveAccount(&a,0) && NITMOD_DBUserCount()==1);
    assert(NITMOD_DBSaveAccount(&a,0) && NITMOD_DBUserCount()==1);
    memset(a.user.name,'X',sizeof(a.user.name)); assert(!NITMOD_DBSaveAccount(&a,1));
    bytes=NITMOD_DBExport(&length); assert(NITMOD_DBOpenWorking(bytes,length)); NITMOD_DBFreeExport(bytes);
    assert(NITMOD_DBInitSchema(1,1) && NITMOD_DBAccount("GUID",&b)==1 && b.user.level==4 && !strcmp(b.password,"0123456789012345678901234567890123456789"));
    /* A real SQLite constraint error leaves both count and existing row intact. */
    Make("CREATE TABLE users(name,guid UNIQUE,ip,level CHECK(level<5),flags,gtext,gsound,mac,xp,timestamp,login,password);"
         "INSERT INTO users VALUES('A','GUID','',1,'','','','','',0,'','');");
    assert(NITMOD_DBOpenWorking(fixture,(int)fixtureLength) && NITMOD_DBInitSchema(0,0));
    b.user.level=9; assert(!NITMOD_DBSaveAccount(&b,2));
    assert(NITMOD_DBUserCount()==1 && NITMOD_DBAccount("GUID",&a)==1 && a.user.level==1);
    NITMOD_DBClose();
    puts("SQLite accounts: all fields, add/update fallback, exact identity, level migration, delete, export/reopen, SQL constraint rollback: PASS");
}
static void PenaltyChecks(void) {
    nitmodDatabasePenalty_t p,result; int expired;
    assert(NITMOD_DBOpenWorking(NULL,0) && NITMOD_DBInitSchema(0,0));
    memset(&p,0,sizeof(p)); strcpy(p.guid,"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU"); strcpy(p.ip,"1.2.3.4");
    strcpy(p.mac,"AA-BB-CC-DD-EE-FF"); strcpy(p.reason,"Test reason"); p.expires=0;
    assert(NITMOD_DBPenaltySave(0,&p,1)); assert(NITMOD_DBPenaltySave(0,&p,1));
    assert(ExportScalar("SELECT count(*) FROM bans")==1);
    assert(NITMOD_DBPenaltyCheck(0,"","aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaau","",100,&result,&expired)==1 && !expired);
    assert(NITMOD_DBPenaltyCheck(0,"11.2.3.45:27960","","",100,&result,&expired)==1); /* original substring behavior */
    assert(NITMOD_DBPenaltyCheck(0,"","","aa-bb-cc-dd-ee-ff",100,&result,&expired)==1);
    assert(NITMOD_DBPenaltyCheck(0,"2.3.4.5","","00-00-00-00-00-00",100,&result,&expired)==0);
    assert(NITMOD_DBPenaltySave(0,&p,0)); assert(NITMOD_DBPenaltySave(0,&p,0));
    p.expires=100; assert(NITMOD_DBPenaltySave(0,&p,1));
    assert(NITMOD_DBPenaltyCheck(0,"","","",100,&result,&expired)==0 && expired==1);
    assert(ExportScalar("SELECT count(*) FROM bans")==0);
    assert(NITMOD_DBPenaltySave(1,&p,1));
    assert(NITMOD_DBPenaltyCheck(1,"1.2.3.4","","",99,&result,&expired)==0); /* mutes do not match IP */
    assert(NITMOD_DBPenaltyCheck(1,"",p.guid,"",99,&result,&expired)==1);
    assert(NITMOD_DBPenaltyCheck(1,"","","AA-BB-CC-DD-EE-FF",100,&result,&expired)==0 && expired==1);
    assert(ExportScalar("SELECT count(*) FROM mutes")==0);
    NITMOD_DBClose();
    puts("SQLite bans/mutes: original GUID/MAC/IP matching, duplicates, permanence, expiration boundary and removal: PASS");
}
static void RecordChecks(void) {
    nitmodDatabaseRecords_t a,b,before; int length; void *bytes;
    assert(NITMOD_DBOpenWorking(NULL,0) && NITMOD_DBInitSchema(0,1));
    memset(&a,0,sizeof(a)); strcpy(a.map,"Oasis"); strcpy(a.holder[0],"Alice"); strcpy(a.date[0],"06 September 2026 14:00");
    a.value[0]=8;a.value[1]=30;a.value[2]=4;
    assert(NITMOD_DBUpdateRecords(&a)==7 && NITMOD_DBRecords("Oasis",&b)==1 && !memcmp(&a,&b,sizeof(a)));
    before=b; assert(NITMOD_DBRecords("oasis",&b)==0 && !memcmp(&before,&b,sizeof(b)));
    strcpy(a.holder[0],"Tie"); a.value[1]=29; assert(NITMOD_DBUpdateRecords(&a)==0);
    assert(NITMOD_DBRecords("Oasis",&b)==1 && !strcmp(b.holder[0],"Alice") && b.value[1]==30);
    a.value[2]=5; assert(NITMOD_DBUpdateRecords(&a)==4);
    bytes=NITMOD_DBExport(&length); assert(NITMOD_DBOpenWorking(bytes,length)); NITMOD_DBFreeExport(bytes);
    assert(NITMOD_DBRecords("Oasis",&b)==1 && b.value[2]==5 && b.value[1]==30);
    assert(NITMOD_DBClearRecords("oasis") && NITMOD_DBRecords("Oasis",&b)==1);
    assert(NITMOD_DBClearRecords(NULL) && NITMOD_DBRecords("Oasis",&b)==0);
    NITMOD_DBClose(); puts("SQLite map records: original columns, exact maps, strict improvement, independent categories, reopen and clear: PASS");
}
#ifdef __EMSCRIPTEN__
static void Command(int client,const char *cmd,const char *a,const char *b) {
    arguments[0]=cmd; arguments[1]=a; arguments[2]=b; argumentCount=b?3:a?2:1; messages[0]=0;
    assert(G_NITMOD_AccountCommand(client,cmd));
}
static void AdminCommand(int client,const char *cmd,const char *a,const char *b) {
    arguments[0]=cmd; arguments[1]=a; arguments[2]=b; argumentCount=b?3:a?2:1; messages[0]=0;
    assert(G_NITMOD_AdminCommand(client,cmd));
}
static void ClientAccountChecks(void) {
    char info[150],guid[33],hash[41]; nitmodDatabaseAccount_t a;
    NITMOD_SHA1Text("",hash); assert(!strcmp(hash,"DA39A3EE5E6B4B0D3255BFEF95601890AFD80709"));
    NITMOD_SHA1Text("abc",hash); assert(!strcmp(hash,"A9993E364706816ABA3E25717850C26C9CD0D89D"));
    NITMOD_SHA1Text("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",hash);
    assert(!strcmp(hash,"84983E441C3BD26EBAAE4AA1F95129E5E54670F1"));
    mailEnabled=1; configuredPath="sample.sqlite";
    Make("CREATE TABLE unrelated(a);"); G_NITMOD_LoadDatabase();
    g_entities[0].client=&clients[0]; g_entities[1].client=&clients[1];
    clients[0].pers.connected=clients[1].pers.connected=CON_CONNECTED;
    strcpy(clients[0].pers.netname,"Alice"); strcpy(clients[1].pers.netname,"Bob");
    assert(G_NITMOD_AccountUserinfo(0,"\\ip\\127.0.0.1") && strstr(messages,"getnguid"));
    memset(guid,'A',31); guid[31]='U'; guid[32]=0;
    Com_sprintf(info,sizeof(info),"\\n_guid\\%s\\ip\\127.0.0.1:27960",guid);
    assert(G_NITMOD_AccountUserinfo(0,info) && NITMOD_DBAccount(guid,&a)==1 && !strcmp(a.ip,"127.0.0.1"));
    renameFailure=1; Command(0,"register","Alice","Secret123"); renameFailure=0;
    assert(strstr(messages,"write failed") && NITMOD_DBAccount(guid,&a)==1 && !*a.login);
    Command(0,"register","Alice","Secret123"); assert(strstr(messages,"now registered"));
    assert(NITMOD_DBAccount(guid,&a)==1); NITMOD_SHA1Text("Secret123",hash); assert(!strcmp(a.password,hash));
    Command(0,"mailto","Alice","hi"); assert(strstr(messages,"login first"));
    Command(0,"login","Alice","Wrong"); assert(strstr(messages,"Invalid password"));
    Command(0,"login","alice","Secret123"); assert(strstr(messages,"doesn't match"));
    Command(0,"login","Alice","Secret123"); assert(strstr(messages,"successfully logged"));
    memset(guid,'B',31);guid[31]='6';
    Com_sprintf(info,sizeof(info),"\\n_guid\\%s\\ip\\127.0.0.2",guid);
    assert(G_NITMOD_AccountUserinfo(1,info));
    Command(1,"login","Alice","Secret123"); assert(strstr(messages,"doesn't match"));
    Command(1,"register","Bob","Other123"); assert(strstr(messages,"now registered"));
    Command(1,"login","Bob","Other123"); assert(strstr(messages,"successfully logged"));
    Command(0,"mailto","bob","hello"); assert(strstr(messages,"Unknown user"));
    Command(0,"mailto","Bob","hello '\" ; DROP TABLE users;"); assert(strstr(messages,"has been sent"));
    Command(0,"deletemail","1",NULL); assert(strstr(messages,"No such mail"));
    G_NITMOD_DatabaseShutdown(); G_NITMOD_AccountReset(0); G_NITMOD_AccountReset(1);
    G_NITMOD_LoadDatabase(); assert(NITMOD_DBUserCount()==2);
    assert(G_NITMOD_AccountUserinfo(1,info));
    Command(1,"checkmails",NULL,NULL); assert(strstr(messages,"login first"));
    Command(1,"login","Bob","Other123"); Command(1,"checkmails",NULL,NULL); assert(strstr(messages,"DROP TABLE users"));
    Command(1,"deletemail","1",NULL); assert(strstr(messages,"Sucessfully deleted"));
    Command(1,"checkmails",NULL,NULL); assert(strstr(messages,"Empty mailbox"));
    { nitmodDatabasePenalty_t p; int now=nowSeconds-946490400;
      memset(&p,0,sizeof(p)); strcpy(p.guid,guid); strcpy(p.reason,"test penalty"); p.expires=now+60;
      assert(NITMOD_DBPenaltySave(0,&p,1) && G_NITMOD_DatabaseFlush());
      assert(strstr(G_NITMOD_DatabaseBanReason(info),"1 mins"));
      assert(NITMOD_DBPenaltySave(0,&p,0));
      assert(NITMOD_DBPenaltySave(1,&p,1) && G_NITMOD_AccountMuted(1));
      nowSeconds+=60; assert(!G_NITMOD_AccountMuted(1));
    }
    { nitmodDatabaseRecords_t record; int generations;
      recordsEnabled=1; G_NITMOD_LoadDatabase(); strcpy(level.rawmapname,"oasis");
      level.numPlayingClients=2; level.sortedClients[0]=0;level.sortedClients[1]=1;
      clients[0].sess.kills=20; clients[1].sess.kills=10; clients[1].nitmodBestReviveSpree=7;
      G_NITMOD_SaveMapRecords(); assert(NITMOD_DBRecords("oasis",&record)==1 && record.value[1]==20 && record.value[2]==7);
      assert(!strcmp(record.holder[1],"Alice") && !strcmp(record.holder[2],"Bob"));
      generations=fileCount; G_NITMOD_SaveMapRecords(); assert(fileCount==generations);
      messages[0]=0; clients[1].sess.kills=25; G_NITMOD_SaveMapRecords();
      assert(strstr(messages,"New Map Frag record: ^x25") && strstr(messages,"Previous Frag record: ^x20"));
      G_NITMOD_DatabaseShutdown(); G_NITMOD_LoadDatabase();
      assert(NITMOD_DBRecords("oasis",&record)==1 && record.value[1]==25 && !strcmp(record.holder[1],"Bob"));
      recordsEnabled=0;
    }
    { float original[7]={1.9f,2,3,4,5,6,7},decoded[7]; char encoded[1024]; int i;
      assert(NITMOD_XPEncode(original,encoded));
      assert(!strcmp(encoded,"UzBcMVxTMVwyXFMyXDNcUzNcNFxTNFw1XFM1XDZcUzZcN1w="));
      assert(NITMOD_XPDecode(encoded,decoded) && decoded[0]==1);
      memset(decoded,0,sizeof(decoded)); assert(!NITMOD_XPDecode("invalid",decoded) && decoded[0]==0);
      g_XPSave.integer=1; g_XPSaveMaxAge.integer=100;
      memcpy(clients[1].sess.skillpoints,original,sizeof(original)); G_NITMOD_AccountSaveXP(1);
      /* Recorded players must not overwrite real XP, on disconnect or batch save. */
      clients[1].pers.nitmodDemoClient=1;
      clients[1].sess.skillpoints[0]=999;
      G_NITMOD_AccountSaveXP(1); G_NITMOD_AccountsSaveAllXP();
      clients[1].pers.nitmodDemoClient=0;
      G_NITMOD_DatabaseShutdown(); G_NITMOD_AccountReset(1); memset(clients[1].sess.skillpoints,0,sizeof(original));
      nowSeconds+=30; decayEnabled=1; G_NITMOD_LoadDatabase(); assert(G_NITMOD_AccountUserinfo(1,info));
      for(i=0;i<7;++i) assert(clients[1].sess.skillpoints[i]==i+1);
      assert(clients[1].ps.stats[STAT_XP]==28 && rankCalls>0 && decaySeconds==30);
      G_NITMOD_AccountReset(1); memset(clients[1].sess.skillpoints,0,sizeof(original)); nowSeconds+=101;
      assert(G_NITMOD_AccountUserinfo(1,info) && clients[1].sess.skillpoints[0]==0); /* expired */
      G_NITMOD_AccountReset(1); g_XPSave.integer=5;
      assert(G_NITMOD_AccountUserinfo(1,info) && clients[1].sess.skillpoints[0]==1); /* never expires */
      g_XPSave.integer=0; decayEnabled=0;
    }
    { const char *savedLevels=levelText;
      assert(G_NITMOD_LoadAdminLevels());
      assert(G_NITMOD_AdminAllowed(1,"records") && !G_NITMOD_AdminAllowed(1,"setlevel"));
      AdminCommand(1,"!setlevel","1","2"); assert(strstr(messages,"Permission denied"));
      AdminCommand(-1,"setlevel","1","2"); assert(strstr(messages,"level set to"));
      assert(G_NITMOD_AdminAllowed(1,"setlevel") && G_NITMOD_ClientAccount(1,&a) && a.user.level==2);
      AdminCommand(1,"!setlevel","1","99"); assert(strstr(messages,"unknown level"));
      AdminCommand(1,"!setlevel","1","1"); assert(G_NITMOD_ClientAccount(1,&a) && a.user.level==1);
      strcpy(a.user.flags,"setlevel"); assert(G_NITMOD_StoreAccount(&a,2));
      assert(G_NITMOD_AdminAllowed(1,"setlevel"));
      AdminCommand(1,"!setlevel","1","2"); assert(strstr(messages,"can't setlevel higher"));
      levelText="**********\nlevel = 0\nflags = all\n**********\nlevel = 0\nflags = all\n";
      assert(!G_NITMOD_LoadAdminLevels() && !G_NITMOD_AdminAllowed(1,"setlevel"));
      levelText=savedLevels; assert(G_NITMOD_LoadAdminLevels());
      AdminCommand(-1,"mute","1","1m"); assert(strstr(messages,"has been muted") && G_NITMOD_AccountMuted(1));
      AdminCommand(-1,"unmute","1",NULL); assert(!G_NITMOD_AccountMuted(1));
      { nitmodDatabasePenalty_t p; int expired;
        memset(&p,0,sizeof(p)); strcpy(p.name,"Bob archived"); strcpy(p.guid,"11111111111111111111111111111111");
        assert(NITMOD_DBPenaltySave(1,&p,1));
        strcpy(p.name,"Bob second"); strcpy(p.guid,"22222222222222222222222222222222");
        assert(NITMOD_DBPenaltySave(1,&p,1));
        AdminCommand(-1,"unmute","Bob",NULL); assert(strstr(messages,"more than one"));
        AdminCommand(-1,"unmute","Bob","3"); assert(strstr(messages,"invalid number"));
        renameFailure=1; AdminCommand(-1,"unmute","Bob","2"); renameFailure=0;
        assert(strstr(messages,"write failed") && NITMOD_DBPenaltyCheck(1,"",p.guid,"",nowSeconds-946490400,&p,&expired)==1);
        AdminCommand(-1,"unmute","Bob","2"); assert(strstr(messages,"has been unmuted"));
        assert(NITMOD_DBPenaltyAt(1,1,&p)==0);
        AdminCommand(-1,"unmute","Bob",NULL); assert(strstr(messages,"has been unmuted"));
        AdminCommand(-1,"unmute","Bob",NULL); assert(strstr(messages,"no player"));
      }
      AdminCommand(-1,"ban","1","1h"); assert(strstr(messages,"has been banned") && G_NITMOD_DatabaseBanReason(info));
      AdminCommand(-1,"showbans",NULL,NULL); assert(strstr(messages,"Bob"));
      AdminCommand(-1,"showbans","find","bOb"); assert(strstr(messages,"Bob") && strstr(messages,"of ^g1"));
      AdminCommand(-1,"showbans","banner","CONSOLE"); assert(strstr(messages,"Bob"));
      AdminCommand(-1,"showbans","reason","no-such-reason"); assert(!strstr(messages,"Bob") && strstr(messages,"of ^g0"));
      AdminCommand(-1,"showbans","nonsense",NULL); assert(strstr(messages,"Invalid start"));

      AdminCommand(-1,"unban","1",NULL); assert(!G_NITMOD_DatabaseBanReason(info));
      { nitmodDatabasePenalty_t p; int k;
        memset(&p,0,sizeof(p)); strcpy(p.actor,"PagerAdmin"); strcpy(p.reason,"PagingReason");
        for(k=0;k<32;++k) {
            sprintf(p.guid,"%032d",k+100); sprintf(p.name,"Pager%02d",k);
            p.expires=k==31?nowSeconds-946490400:0;
            assert(NITMOD_DBPenaltySave(0,&p,1));
        }
        AdminCommand(-1,"showbans",NULL,NULL);
        assert(strstr(messages,"Pager00") && strstr(messages,"Pager29") && !strstr(messages,"Pager30") && !strstr(messages,"Pager31"));
        AdminCommand(-1,"showbans","next",NULL); assert(strstr(messages,"Pager30") && !strstr(messages,"Pager00"));
        AdminCommand(-1,"showbans","prev",NULL); assert(strstr(messages,"Pager00") && !strstr(messages,"Pager30"));
        AdminCommand(-1,"showbans","-1",NULL); assert(strstr(messages,"Pager30") && !strstr(messages,"Pager29"));
        AdminCommand(-1,"showbans","reason","pagingreason"); assert(strstr(messages,"Pager00") && strstr(messages,"of ^g31"));
        for(k=0;k<32;++k) { sprintf(p.guid,"%032d",k+100); assert(NITMOD_DBPenaltySave(0,&p,0)); }
      }
      assert(dropped==1); dropped=0;
      AdminCommand(-1,"setlevel","1","2");
      assert(G_NITMOD_ClientAccount(1,&a));
      assert(NITMOD_DBAccountByID(a.user.guid+24,&a)==1);
      AdminCommand(1,"!userinfo",a.user.guid+24,NULL); assert(strstr(messages,"Bob") && !strstr(messages,a.password));
      AdminCommand(-1,"userlist","name","bob"); assert(strstr(messages,"Bob") && strstr(messages,"1 matches"));
      securePassword="FixtureSecurePassword";
      arguments[0]="!useredit"; arguments[1]=a.user.guid+24; arguments[2]="grant"; arguments[3]="novote"; argumentCount=4;
      messages[0]=0; assert(G_NITMOD_AdminCommand(1,arguments[0]) && strstr(messages,"/sslogin"));
      Command(1,"sslogin","wrong",NULL); assert(strstr(messages,"Invalid Password") && !G_NITMOD_SecureShrubAllowed(1));
      Command(1,"sslogin",securePassword,NULL); assert(strstr(messages,"Login successful") && G_NITMOD_SecureShrubAllowed(1));
      arguments[0]="!useredit"; arguments[1]=a.user.guid+24; arguments[2]="grant"; arguments[3]="novote"; argumentCount=4;
      assert(G_NITMOD_AdminCommand(1,arguments[0]) && G_NITMOD_ClientAccount(1,&a) && strstr(a.user.flags,"novote"));
      arguments[2]="revoke"; renameFailure=1;
      assert(G_NITMOD_AdminCommand(1,arguments[0])); renameFailure=0;
      assert(G_NITMOD_ClientAccount(1,&a) && strstr(a.user.flags,"novote"));
      assert(G_NITMOD_AdminCommand(1,arguments[0]) && G_NITMOD_ClientAccount(1,&a) && !strstr(a.user.flags,"novote"));
      Command(1,"sslogout",NULL,NULL); assert(!G_NITMOD_SecureShrubAllowed(1));
      securePassword="";
      assert(!G_NITMOD_AdminPrivilege(1,"incognito") && G_NITMOD_AdminPrivilege(1,"permban"));
      assert(G_NITMOD_ClientAccount(1,&a)); strcpy(a.gtext,"Welcome [n]"); strcpy(a.gsound,"sound/test.wav");
      assert(G_NITMOD_StoreAccount(&a,2)); messages[0]=0; G_NITMOD_AccountBegin(1);
      assert(strstr(messages,"Welcome Bob") && strstr(messages,"gsnd sound/test.wav"));
      messages[0]=0; G_NITMOD_AccountBegin(1); assert(!*messages);
      { nitmodDatabaseAccount_t collision=a,unchanged=a;
        collision.user.guid[0]=collision.user.guid[0]=='Z'?'Y':'Z';
        assert(NITMOD_DBSaveAccount(&collision,1));
        assert(NITMOD_DBAccountByID(a.user.guid+24,&a)==-1 && !memcmp(&a,&unchanged,sizeof(a)));
        assert(NITMOD_DBSaveAccount(&collision,0));
      }
      AdminCommand(-1,"levadd","9",NULL); assert(strstr(messages,"successfully added"));
      assert(G_NITMOD_LoadAdminLevels());
      AdminCommand(-1,"levinfo","9",NULL); assert(!strstr(messages,"Unknown"));
      arguments[0]="levedit"; arguments[1]="9"; arguments[2]="grant"; arguments[3]="records"; argumentCount=4;
      assert(G_NITMOD_AdminCommand(-1,"levedit"));
      AdminCommand(-1,"setlevel","1","9"); assert(G_NITMOD_ClientAccount(1,&a) && a.user.level==9);
      assert(G_NITMOD_AdminAllowed(1,"records") && !G_NITMOD_AdminAllowed(1,"levdelete"));
      renameFailure=1; AdminCommand(-1,"levadd","10",NULL); renameFailure=0;
      assert(strstr(messages,"Persistence failed"));
      assert(G_NITMOD_LoadAdminLevels()); AdminCommand(-1,"levinfo","10",NULL); assert(strstr(messages,"Unknown"));
      AdminCommand(-1,"levdelete","0",NULL); assert(strstr(messages,"can not be deleted"));
      AdminCommand(-1,"levdelete","9","2"); assert(strstr(messages,"successfully deleted"));
      G_NITMOD_DatabaseShutdown(); G_NITMOD_LoadDatabase(); assert(G_NITMOD_LoadAdminLevels());
      assert(G_NITMOD_ClientAccount(1,&a) && a.user.level==2);
      AdminCommand(-1,"levinfo","9",NULL); assert(strstr(messages,"Unknown"));
      recordsEnabled=1;
      AdminCommand(-1,"delrecords","oasis",NULL); assert(strstr(messages,"successfully deleted"));
      { nitmodDatabaseRecords_t record; assert(NITMOD_DBRecords("oasis",&record)==0); }
      recordsEnabled=0;
      clients[1].sess.skillpoints[0]=50; clients[1].ps.ammo[1]=30; clients[1].ps.ammoclip[1]=7;
      renameFailure=1; AdminCommand(-1,"resetxp","1",NULL); renameFailure=0;
      assert(strstr(messages,"write failed") && clients[1].sess.skillpoints[0]==50);
      AdminCommand(-1,"resetxp","1",NULL); assert(strstr(messages,"XP has been reset"));
      assert(clients[1].sess.skillpoints[0]==0 && clients[1].ps.ammo[1]==30 && clients[1].ps.ammoclip[1]==7);
      { float xp[7]; assert(G_NITMOD_ClientAccount(1,&a) && NITMOD_XPDecode(a.user.xp,xp) && xp[0]==0); }
      { float xp[7]={40,0,0,0,0,0,0};
        assert(NITMOD_XPEncode(xp,a.user.xp) && G_NITMOD_StoreAccount(&a,2));
        g_gametype.integer=GT_WOLF_MAPVOTE; g_resetXPMapCount.integer=0;
        G_NITMOD_AccountsMapStart(); assert(G_NITMOD_ClientAccount(1,&a) && NITMOD_XPDecode(a.user.xp,xp) && xp[0]==40);
        g_resetXPMapCount.integer=3; G_NITMOD_SetMapCycleCount(1);
        G_NITMOD_AccountsMapStart(); assert(G_NITMOD_ClientAccount(1,&a) && NITMOD_XPDecode(a.user.xp,xp) && xp[0]==40);
        G_NITMOD_SetMapCycleCount(0); g_XPSave.integer=5;
        G_NITMOD_AccountsMapStart(); assert(G_NITMOD_ClientAccount(1,&a) && NITMOD_XPDecode(a.user.xp,xp) && xp[0]==40);
        g_XPSave.integer=1; G_NITMOD_AccountsMapStart();
        assert(G_NITMOD_ClientAccount(1,&a) && NITMOD_XPDecode(a.user.xp,xp) && xp[0]==0);
        g_XPSave.integer=0; g_resetXPMapCount.integer=0;
      }
    }
    assert(!G_NITMOD_AccountUserinfo(1,"\\n_guid\\bad") && dropped==1);
    G_NITMOD_DatabaseShutdown();
    puts("SQLite actual client hooks: NGUID, registration/login, SHA1, mail ownership, XP wire format/expiry/decay, durable reopen and rollback: PASS");
}
#endif
int main(void) {
    nitmodDatabaseUser_t user,before;
    nitmodDatabaseAccount_t account;
    unsigned char *original;
    Make("CREATE TABLE users(name char(64),guid varchar(33),level INT,flags varchar(1024),xp varchar(255));"
         "INSERT INTO users VALUES('Alice','GUID',7,'admintest','1 2 3 4 5 6 7'); PRAGMA user_version=2;");
    original=malloc((size_t)fixtureLength); memcpy(original,fixture,(size_t)fixtureLength);
    G_NITMOD_LoadDatabase(); assert(closes==1 && NITMOD_DBUserCount()==1 && NITMOD_DBVersion()==2);
    memset(&user,0x5a,sizeof(user)); before=user;
    assert(NITMOD_DBUser("missing",&user)==0 && !memcmp(&user,&before,sizeof(user)));
    assert(NITMOD_DBUser("' OR 1=1 --",&user)==0 && !memcmp(&user,&before,sizeof(user)));
    assert(NITMOD_DBUser("guid",&user)==0); /* original exact GUID identity */
    assert(NITMOD_DBUser("GUID",&user)==1 && user.level==7 && !strcmp(user.flags,"admintest"));
    assert(!memcmp(original,fixture,(size_t)fixtureLength)); free(original);
    configuredPath="none"; G_NITMOD_LoadDatabase(); assert(NITMOD_DBUserCount()==-1 && closes==1);
    configuredPath="sample.sqlite";
    Make("CREATE TABLE users(name,guid,level,flags,xp); INSERT INTO users VALUES('A','X',1,'',''); INSERT INTO users VALUES('B','X',9,'all','');");
    G_NITMOD_LoadDatabase(); before=user; assert(NITMOD_DBUser("X",&user)==-1 && !memcmp(&before,&user,sizeof(user)));
    Make("CREATE TABLE wrong(a);"); G_NITMOD_LoadDatabase(); assert(NITMOD_DBUserCount()==0);
    assert(!NITMOD_DBOpenSnapshot("bad",3));
    sqlite3_free(fixture); fixture=0; G_NITMOD_LoadDatabase(); assert(NITMOD_DBUserCount()==0 && fileCount==1);
    NITMOD_DBClose();
    puts("SQLite actual engine-VFS load, original-column query, disabled path, duplicate identity and nonmutation: PASS");
    SchemaChecks();
    AccountChecks();
    PenaltyChecks();
    RecordChecks();
    assert(NITMOD_DBOpenWorking(NULL,0) && NITMOD_DBInitSchema(1,1));
    memset(&account,0,sizeof(account)); strcpy(account.user.guid,"PERSIST"); account.user.level=2;
    assert(NITMOD_DBSaveAccount(&account,1));
    assert(!G_NITMOD_DatabaseSaveAs("../escape.sqlite") && writes==0);
    { int count=fileCount;
      strcpy(files[fileCount++].path,"new.sqlite.d/00000001.sqlite");
      assert(!G_NITMOD_DatabaseSaveAs("new.sqlite") && writes==0);
      assert(!G_NITMOD_DatabaseMigrateLevel(2,9,"new.sqlite"));
      assert(NITMOD_DBUser("PERSIST",&user)==1 && user.level==2);
      strcpy(files[count].path,"new.sqlite.d/00000001.pending");
      assert(!G_NITMOD_DatabaseSaveAs("new.sqlite") && writes==0);
      memset(&files[count],0,sizeof(files[count])); fileCount=count;
    }
    assert(G_NITMOD_DatabaseMigrateLevel(2,4,"new.sqlite") && writes==1 && !strcmp(configuredPath,"new.sqlite"));
    assert(!G_NITMOD_DatabaseSaveAs("new.sqlite") && writes==1);
    G_NITMOD_LoadDatabase(); assert(NITMOD_DBVersion()==2 && NITMOD_DBUserCount()==1);
    assert(NITMOD_DBUser("PERSIST",&user)==1 && user.level==4);
    free(saved); saved=0; configuredPath="sample.sqlite"; shortWrite=1;
    assert(!G_NITMOD_DatabaseMigrateLevel(4,9,"new.sqlite") && !strcmp(configuredPath,"sample.sqlite"));
    assert(NITMOD_DBUserCount()==1 && NITMOD_DBUser("PERSIST",&user)==1 && user.level==4);
    assert(!G_NITMOD_DatabaseSaveAs("new.sqlite")); /* preserve even an incomplete file */
    free(saved); saved=0; shortWrite=0; corruptReadback=1;
    assert(!G_NITMOD_DatabaseSaveAs("new.sqlite") && !strcmp(configuredPath,"sample.sqlite"));
    free(saved); saved=0; NITMOD_DBClose();
    puts("SQLite product persistence: new destination, verified readback, reload, collision, short-write and corruption: PASS");
    configuredPath="sample.sqlite"; shortWrite=corruptReadback=0;
    G_NITMOD_LoadDatabase(); assert(NITMOD_DBUserCount()==0);
    memset(&account,0,sizeof(account)); strcpy(account.user.guid,"AUTOSAVE"); account.user.level=3;
    assert(NITMOD_DBSaveAccount(&account,1)); G_NITMOD_DatabaseShutdown();
    G_NITMOD_LoadDatabase(); assert(NITMOD_DBAccount("AUTOSAVE",&account)==1 && account.user.level==3);
    { int count=fileCount; assert(G_NITMOD_DatabaseFlush() && count==fileCount); }
    account.user.level=5; assert(NITMOD_DBSaveAccount(&account,2)); renameFailure=1;
    assert(!G_NITMOD_DatabaseFlush()); NITMOD_DBClose(); renameFailure=0;
    G_NITMOD_LoadDatabase(); assert(NITMOD_DBAccount("AUTOSAVE",&account)==1 && account.user.level==3);
    account.user.level=7; assert(NITMOD_DBSaveAccount(&account,2)); G_NITMOD_DatabaseShutdown();
    G_NITMOD_LoadDatabase(); assert(NITMOD_DBAccount("AUTOSAVE",&account)==1 && account.user.level==7);
    G_NITMOD_DatabaseShutdown();
    { int i; for(i=0;i<fileCount;++i) free(files[i].bytes); }
    memset(files,0,sizeof(files)); fileCount=0;
#ifdef __EMSCRIPTEN__
    { char guid[34],reason[100]; memset(guid,'A',31); guid[31]='U'; guid[32]=0;
      assert(NITMOD_ValidateNGuid(guid,reason,sizeof(reason))); guid[32]='A';guid[33]=0;
      assert(!NITMOD_ValidateNGuid(guid,reason,sizeof(reason))); guid[32]=0;guid[0]='B';
      assert(!NITMOD_ValidateNGuid(guid,reason,sizeof(reason))); }
    ClientAccountChecks();
    { int i; for(i=0;i<fileCount;++i) free(files[i].bytes); }
#endif
    puts("SQLite automatic persistence: create, shutdown, generations, unchanged image, failed commit recovery and NGUID identity: PASS");
    sqlite3_free(fixture);
    return 0;
}
