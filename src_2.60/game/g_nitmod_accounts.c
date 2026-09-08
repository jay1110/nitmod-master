#include "nitmod_xp_snapshot.h"
#include "g_local.h"
#include "g_nitmod_restrictions.h"
#include "g_nitmod_accounts.h"
#include "g_nitmod_database.h"
#include "g_nitmod_config.h"
#include "g_nitmod_admin.h"
#include "g_nitmod_legacy_cvars.h"
#include "nitmod_database.h"
#include "nitmod_sha1.h"
#include "nitmod_xp.h"
static struct {
    char guid[33],login[33],userinfo[MAX_INFO_STRING];
    int loggedIn,requested,xpLoaded,secureShrub,begun,greeted;
    int userinfoPending,userinfoDirty,registerPending,resetPending,waitingMap;
    unsigned int epoch;
} identities[MAX_CLIENTS];
/* Independent of SQLite image epochs: reconnecting with the same GUID must
 * never inherit the completion of an earlier occupant of this slot. */
static unsigned int connectionGeneration[MAX_CLIENTS],mapGeneration;
static int mapResetPending;
typedef struct { int client; unsigned int generation; char guid[33]; } accountGuard_t;
unsigned int G_NITMOD_AccountConnectionGeneration(int n) {
    return n>=0 && n<MAX_CLIENTS?connectionGeneration[n]:0;
}
unsigned int G_NITMOD_AccountsMapGeneration(void) { return mapGeneration; }
void G_NITMOD_AccountReset(int n) {
    if(n<0 || n>=MAX_CLIENTS) return;
    if(!++connectionGeneration[n]) ++connectionGeneration[n];
    memset(&identities[n],0,sizeof(identities[n]));
}
static void AccountGuard(int n,accountGuard_t *guard) {
    memset(guard,0,sizeof(*guard)); guard->client=n;
    if(n<0 || n>=MAX_CLIENTS) return;
    guard->generation=connectionGeneration[n];
    Q_strncpyz(guard->guid,identities[n].guid,sizeof(guard->guid));
}
static int AccountCurrent(const accountGuard_t *guard) {
    int n=guard->client;
    return n>=0 && n<MAX_CLIENTS && connectionGeneration[n]==guard->generation &&
        *guard->guid && !Q_stricmp(guard->guid,identities[n].guid) && g_entities[n].client &&
        g_entities[n].client->pers.connected!=CON_DISCONNECTED && !(g_entities[n].r.svFlags&SVF_BOT);
}
void G_NITMOD_AccountBegin(int n) {
    nitmodDatabaseAccount_t account;
    if(n<0 || n>=MAX_CLIENTS) return;
    identities[n].begun=1;
    if(!identities[n].greeted && identities[n].xpLoaded && !identities[n].userinfoPending &&
       G_NITMOD_DatabaseReady() && G_NITMOD_ClientAccount(n,&account)) {
        identities[n].greeted=1; G_NITMOD_AdminGreeting(n);
    }
}
static void Print(int n,const char *message) { NITMOD_SendChunkedPrint(n,message); }
int G_NITMOD_SecureShrubAllowed(int n) {
    char password[256];
    if(n<0) return 1;
    G_NITMOD_LegacyCvarString("g_secureShrubPassword",password,sizeof(password),"");
    return !*password || !strcmp(password,"none") || (n<MAX_CLIENTS && identities[n].secureShrub);
}
static int SecureShrubCommand(int n,const char *command) {
    char expected[256],supplied[1024];
    if(strcmp(command,"sslogin") && strcmp(command,"sslogout")) return 0;
    if(n<0 || n>=MAX_CLIENTS || !g_entities[n].client || (g_entities[n].r.svFlags&SVF_BOT)) return 1;
    if(!strcmp(command,"sslogout")) {
        if(!identities[n].secureShrub) Print(n,"^1SecureShrubLogin: ^gYou are not logged in.\n");
        else { identities[n].secureShrub=0; Print(n,"^xSecureShrubLogin: ^gLogged out.\n"); ClientUserinfoChanged(n); }
        return 1;
    }
    if(identities[n].secureShrub) { Print(n,"^1SecureShrubLogin: ^gYou are already logged in.\n"); return 1; }
    G_NITMOD_LegacyCvarString("g_secureShrubPassword",expected,sizeof(expected),"");
    if(!*expected || !strcmp(expected,"none")) Print(n,"^1SecureShrubLogin: ^gSecure Shrubbot Login is disabled on this server.\n");
    else if(trap_Argc()<2) Print(n,"^xusage: ^gsslogin [password]\n");
    else {
        trap_Argv(1,supplied,sizeof(supplied));
        if(strcmp(expected,supplied)) Print(n,"^1SecureShrubLogin error: ^9Invalid Password.\n");
        else { identities[n].secureShrub=1; Print(n,"^xSecureShrubLogin: ^gLogin successful.\n"); ClientUserinfoChanged(n); }
    }
    return 1;
}
static int CompleteFailed(nitmodDbCompletion_t done,const void *context) {
    if(done) done(0,context);
    return 0;
}
static int CommitChanged(void *before,int length,int changed,nitmodDbCompletion_t done,const void *context,int contextLength) {
    if(changed<=0) {
        if(before && !NITMOD_DBInstallWorking(before,length)) G_LogPrintf("[SQLite] Failed to restore account transaction\n");
        NITMOD_DBFreeExport(before);
        return CompleteFailed(done,context);
    }
    /* DatabaseCommit owns BEFORE on every path, including inline failure. */
    return G_NITMOD_DatabaseCommit(before,length,done,context,contextLength);
}
int G_NITMOD_StoreAccountAsync(const nitmodDatabaseAccount_t *account,int mode,nitmodDbCompletion_t done,const void *context,int contextLength) {
    int length; void *before;
    if(!account || !G_NITMOD_DatabaseReady() || contextLength<0 || contextLength>65536 || (contextLength && !context)) return CompleteFailed(done,context);
    before=NITMOD_DBExport(&length);
    if(!before) return CompleteFailed(done,context);
    return CommitChanged(before,length,NITMOD_DBSaveAccount(account,mode),done,context,contextLength);
}
int G_NITMOD_StoreAccount(const nitmodDatabaseAccount_t *account,int mode) {
    return G_NITMOD_StoreAccountAsync(account,mode,NULL,NULL,0);
}
int G_NITMOD_ClientAccount(int n,nitmodDatabaseAccount_t *account) {
    if(n<0 || n>=MAX_CLIENTS || !*identities[n].guid || !g_entities[n].client ||
       (g_entities[n].r.svFlags&SVF_BOT)) return 0;
    return NITMOD_DBAccount(identities[n].guid,account)==1;
}
static int expirationPending[2];
static void ExpirationComplete(int success,const void *opaque) {
    int mute=*(const int *)opaque;
    expirationPending[mute]=0;
    if(!success) G_LogPrintf("[SQLite] Failed to persist expired %s\n",mute?"mutes":"bans");
}
static int PenaltyCheck(int mute,const char *ip,const char *guid,int time,nitmodDatabasePenalty_t *penalty) {
    nitmodDatabasePenalty_t row; int i,rc,mayExpire=0,expired=0,length=0; void *before=NULL;
    /* Most checks are read-only. Obtain a BEFORE image only when the original
     * checker can remove a row, so an async write never leaks into the cache. */
    for(i=0;i<1024;++i) {
        rc=NITMOD_DBPenaltyAt(mute,i,&row); if(rc<0) return -1; if(!rc) break;
        if(row.expires && row.expires<=time && (!mute || !Q_stricmp(guid,row.guid))) { mayExpire=1; break; }
    }
    if(mayExpire) { before=NITMOD_DBExport(&length); if(!before) return -1; }
    rc=NITMOD_DBPenaltyCheck(mute,ip,guid,"",time,penalty,&expired);
    if(before) {
        if(rc>=0 && expired && !expirationPending[mute]) {
            expirationPending[mute]=1;
            G_NITMOD_DatabaseCommit(before,length,ExpirationComplete,&mute,sizeof(mute));
        } else {
            if(!NITMOD_DBInstallWorking(before,length)) G_LogPrintf("[SQLite] Failed to restore penalty check\n");
            NITMOD_DBFreeExport(before);
        }
    }
    return rc;
}
const char *G_NITMOD_DatabaseBanReason(const char *userinfo) {
    static char reason[1024]; char guid[64],ip[64],duration[64]; nitmodDatabasePenalty_t penalty;
    qtime_t now; int rc,time;
    if(NITMOD_DBUserCount()<0) return NULL;
    Q_strncpyz(guid,Info_ValueForKey(userinfo,"n_guid"),sizeof(guid));
    Q_strncpyz(ip,Info_ValueForKey(userinfo,"ip"),sizeof(ip));
    time=trap_RealTime(&now)-946490400;
    rc=PenaltyCheck(0,ip,guid,time,&penalty);
    if(rc<0) return "Database ban check failed";
    if(!rc) return NULL;
    { unsigned int remaining=(unsigned int)penalty.expires-(unsigned int)time;
      if(remaining>=0x5dfc0f01U) Q_strncpyz(duration,"PERMANENT",sizeof(duration));
      else {
          static const unsigned int divisors[]={1,60,3600,86400,604800,2592000,31536000};
          static const char *units[]={"secs","mins","hours","days","weeks","months","years"}; int unit=0;
          while(unit<6 && remaining>=divisors[unit+1]) ++unit;
          Com_sprintf(duration,sizeof(duration),"%u %s",remaining/divisors[unit],units[unit]);
      }
    }
    Com_sprintf(reason,sizeof(reason),"^7Reason: %s\n^7Expires in: %s.^7",penalty.reason,duration);
    return reason;
}
int G_NITMOD_AccountMuted(int n) {
    nitmodDatabasePenalty_t penalty; qtime_t now; int rc;
    if(n<0 || n>=MAX_CLIENTS || !*identities[n].guid || NITMOD_DBUserCount()<0) return 0;
    rc=PenaltyCheck(1,"",identities[n].guid,trap_RealTime(&now)-946490400,&penalty);
    return rc!=0;
}
static void RestoreXP(int n,const nitmodDatabaseAccount_t *account) {
    float skills[7]; double total=0; qtime_t now; int age,i; long long elapsed;
    if(identities[n].xpLoaded) return;
    identities[n].xpLoaded=1;
    if(!(g_XPSave.integer&1) || !account->timestamp || !*account->user.xp) return;
    elapsed=(long long)trap_RealTime(&now)-account->timestamp;
    age=elapsed>2147483647?2147483647:elapsed<(-2147483647LL-1)?(-2147483647-1):(int)elapsed;
    if(!(g_XPSave.integer&4) && age>g_XPSaveMaxAge.integer) return;
    if(!NITMOD_XPDecode(account->user.xp,skills)) { G_LogPrintf("[SQLite] Invalid saved XP for client %d\n",n); return; }
    for(i=0;i<7;++i) { g_entities[n].client->sess.skillpoints[i]=skills[i]; total+=skills[i]; }
    g_entities[n].client->sess.startxptotal=(float)total;
    NITMOD_SetSnapshotXP(&g_entities[n].client->ps,NITMOD_XPInteger(total));
    if((G_NITMOD_LegacyCvarInteger("g_XPDecay",0)&3)==1 && age>0)
        G_NITMOD_XPDecay(&g_entities[n],age,qtrue);
    G_CalcRank(g_entities[n].client);
}
static int UpdateXP(int n) {
    nitmodDatabaseAccount_t account; qtime_t now;
    if(n<0 || n>=MAX_CLIENTS || !g_entities[n].client || (g_entities[n].r.svFlags&SVF_BOT) ||
       g_entities[n].client->pers.nitmodDemoClient || !*identities[n].guid ||
       !identities[n].xpLoaded || identities[n].resetPending) return 1;
    { int rc=NITMOD_DBAccount(identities[n].guid,&account); if(rc!=1) return rc==0; }
    if((g_XPSave.integer&1) && !NITMOD_XPEncode(g_entities[n].client->sess.skillpoints,account.user.xp)) return 0;
    account.timestamp=trap_RealTime(&now);
    Q_strncpyz(account.user.name,g_entities[n].client->pers.netname,sizeof(account.user.name));
    return NITMOD_DBSaveAccount(&account,2);
}
typedef struct {
    accountGuard_t guard;
    nitmodDbCompletion_t done;
    size_t contextLength;
} resetXPContext_t;
static void ResetXPComplete(int success,const void *opaque) {
    const resetXPContext_t *context=opaque; int n=context->guard.client;
    if(AccountCurrent(&context->guard)) {
        identities[n].resetPending=0;
        if(success) {
            gclient_t *client=g_entities[n].client; int war;
            memset(client->sess.skillpoints,0,sizeof(client->sess.skillpoints));
            memset(client->sess.skill,0,sizeof(client->sess.skill)); client->sess.startxptotal=0;
            G_CalcRank(client); NITMOD_SetSnapshotXP(&client->ps,0); client->ps.persistant[PERS_SCORE]=0;
            war=G_NITMOD_ConfiguredWarMode();
            if(war<1 || war>4) {
                int ammo[MAX_WEAPONS],clip[MAX_WEAPONS];
                memcpy(ammo,client->ps.ammo,sizeof(ammo)); memcpy(clip,client->ps.ammoclip,sizeof(clip));
                SetWolfSpawnWeapons(client);
                memcpy(client->ps.ammo,ammo,sizeof(ammo)); memcpy(client->ps.ammoclip,clip,sizeof(clip));
            }
            ClientUserinfoChanged(n);
        }
    }
    if(context->done) context->done(success,context->contextLength?(const void *)(context+1):NULL);
}
int G_NITMOD_AccountResetXPAsync(int n,nitmodDbCompletion_t done,const void *opaque,int contextLength) {
    nitmodDatabaseAccount_t account; resetXPContext_t *context;
    float zero[7]={0}; qtime_t now; int result;
    if(contextLength<0 || contextLength>(int)(65536-sizeof(*context)) || (contextLength && !opaque) ||
       !G_NITMOD_ClientAccount(n,&account) || identities[n].resetPending || !identities[n].xpLoaded)
        return CompleteFailed(done,opaque);
    if(!NITMOD_XPEncode(zero,account.user.xp)) return CompleteFailed(done,opaque);
    context=malloc(sizeof(*context)+contextLength);
    if(!context) return CompleteFailed(done,opaque);
    memset(context,0,sizeof(*context)); AccountGuard(n,&context->guard);
    context->done=done; context->contextLength=contextLength;
    if(contextLength) memcpy(context+1,opaque,contextLength);
    account.timestamp=trap_RealTime(&now); identities[n].resetPending=1;
    result=G_NITMOD_StoreAccountAsync(&account,2,ResetXPComplete,context,(int)sizeof(*context)+contextLength);
    free(context); return result;
}
int G_NITMOD_AccountResetXP(int n) { return G_NITMOD_AccountResetXPAsync(n,NULL,NULL,0); }
static void SaveXPComplete(int success,const void *opaque) {
    const int *client=opaque;
    if(!success) {
        if(client && *client>=0) G_LogPrintf("[SQLite] Failed to persist XP for client %d\n",*client);
        else G_LogPrintf("[SQLite] Failed to persist player XP batch\n");
    }
}
void G_NITMOD_AccountSaveXP(int n) {
    int length; void *before;
    if(!G_NITMOD_DatabaseReady() || NITMOD_DBUserCount()<0) return;
    before=NITMOD_DBExport(&length); if(!before) { SaveXPComplete(0,&n); return; }
    CommitChanged(before,length,UpdateXP(n),SaveXPComplete,&n,sizeof(n));
}
void G_NITMOD_AccountsSaveAllXP(void) {
    int i,length,ok=1; void *before;
    if(!G_NITMOD_DatabaseReady() || NITMOD_DBUserCount()<0) return;
    before=NITMOD_DBExport(&length); if(!before) { SaveXPComplete(0,NULL); return; }
    for(i=0;i<MAX_CLIENTS && ok;++i) ok=UpdateXP(i);
    /* One immutable batch is submitted before shutdown starts draining. This
     * callback neither reads client slots nor submits a later save. */
    CommitChanged(before,length,ok,SaveXPComplete,NULL,0);
}
static void MapXPComplete(int success,const void *opaque) {
    const unsigned int *generation=opaque; int n;
    if(generation && *generation!=mapGeneration) return;
    mapResetPending=0;
    if(!success) G_LogPrintf("[SQLite] Failed to persist map-start XP reset\n");
    for(n=0;n<MAX_CLIENTS;++n) if(identities[n].waitingMap) {
        char userinfo[MAX_INFO_STRING]; identities[n].waitingMap=0;
        Q_strncpyz(userinfo,identities[n].userinfo,sizeof(userinfo));
        if(g_entities[n].client && g_entities[n].client->pers.connected!=CON_DISCONNECTED)
            G_NITMOD_AccountUserinfo(n,userinfo);
    }
}
static void MapXPReady(int success,const void *opaque) {
    const unsigned int *generation=opaque; int length; void *before;
    if(*generation!=mapGeneration) return;
    if(!success || NITMOD_DBUserCount()<0) { MapXPComplete(0,opaque); return; }
    before=NITMOD_DBExport(&length); if(!before) { MapXPComplete(0,opaque); return; }
    CommitChanged(before,length,NITMOD_DBClearXP(),MapXPComplete,opaque,sizeof(*generation));
}
void G_NITMOD_AccountsMapStart(void) {
    if(!++mapGeneration) ++mapGeneration;
    mapResetPending=0;
    if(g_XPSave.integer&4) return;
    if(g_gametype.integer==GT_WOLF_CAMPAIGN && level.currentCampaign>=0 &&
       level.currentCampaign<MAX_CAMPAIGNS && g_campaigns[level.currentCampaign].current!=0 && !level.newCampaign) return;
    if((g_gametype.integer==GT_WOLF_STOPWATCH || g_gametype.integer==GT_WOLF_LMS) && g_currentRound.integer!=0) return;
    if((g_gametype.integer==GT_WOLF_MAPVOTE ||
       (g_gametype.integer==GT_WOLF_TDM && (G_NITMOD_LegacyCvarInteger("g_TDMOptions",0)&8)) ||
       (g_gametype.integer==GT_WOLF_DM && (g_DMOptions.integer&0x4000))) && !G_NITMOD_MapCycleResetsXP()) return;
    if(!G_NITMOD_DatabaseReady() || NITMOD_DBUserCount()>=0) mapResetPending=1;
    if(!G_NITMOD_DatabaseReady())
        G_NITMOD_DatabaseSyncUserAsync("map-start-xp",MapXPReady,&mapGeneration,sizeof(mapGeneration));
    else if(NITMOD_DBUserCount()>=0) MapXPReady(1,&mapGeneration);
}
typedef struct {
    accountGuard_t guard;
    int previousTimestamp;
    char previousXP[1024];
} userinfoContext_t;
static void UserinfoReady(int success,const void *opaque);
static void UserinfoStored(int success,const void *opaque) {
    const userinfoContext_t *context=opaque; int n=context->guard.client,dirty;
    nitmodDatabaseAccount_t account;
    if(!AccountCurrent(&context->guard)) return;
    dirty=identities[n].userinfoDirty;
    identities[n].userinfoPending=identities[n].userinfoDirty=0;
    if(!success || !G_NITMOD_ClientAccount(n,&account)) {
        G_LogPrintf("[SQLite] Failed to persist client account %d\n",n); return;
    }
    /* Metadata stores update last-seen time. XP age still belongs to the
     * durable pre-login value, unless another committed operation changed XP. */
    if(!strcmp(account.user.xp,context->previousXP)) account.timestamp=context->previousTimestamp;
    RestoreXP(n,&account);
    if(identities[n].begun) G_NITMOD_AccountBegin(n);
    if(dirty) {
        char userinfo[MAX_INFO_STRING]; Q_strncpyz(userinfo,identities[n].userinfo,sizeof(userinfo));
        G_NITMOD_AccountUserinfo(n,userinfo);
    }
}
static void UserinfoReady(int success,const void *opaque) {
    const accountGuard_t *guard=opaque; userinfoContext_t context;
    nitmodDatabaseAccount_t account,previous; char userinfo[MAX_INFO_STRING],ip[64],*port;
    int n=guard->client,rc;
    if(!AccountCurrent(guard)) return;
    if(!success || NITMOD_DBUserCount()<0) {
        identities[n].userinfoPending=identities[n].userinfoDirty=0;
        G_LogPrintf("[SQLite] Failed to load client account %d\n",n); return;
    }
    Q_strncpyz(userinfo,identities[n].userinfo,sizeof(userinfo));
    if(Q_stricmp(guard->guid,Info_ValueForKey(userinfo,"n_guid"))) {
        G_NITMOD_AccountReset(n); trap_DropClient(n,"Your NGUID has changed",0); return;
    }
    { const char *ban=G_NITMOD_DatabaseBanReason(userinfo);
      if(ban) { G_NITMOD_AccountReset(n); trap_DropClient(n,ban,0); return; } }
    rc=NITMOD_DBAccount(guard->guid,&account);
    if(rc<0) { identities[n].userinfoPending=0; G_LogPrintf("[SQLite] Failed to read client account %d\n",n); return; }
    if(!rc) { memset(&account,0,sizeof(account)); Q_strncpyz(account.user.guid,guard->guid,sizeof(account.user.guid)); }
    previous=account; memset(&context,0,sizeof(context)); context.guard=*guard;
    context.previousTimestamp=account.timestamp; Q_strncpyz(context.previousXP,account.user.xp,sizeof(context.previousXP));
    Q_strncpyz(account.user.name,g_entities[n].client->pers.netname,sizeof(account.user.name));
    Q_strncpyz(ip,Info_ValueForKey(userinfo,"ip"),sizeof(ip)); port=strchr(ip,':'); if(port) *port=0;
    Q_strncpyz(account.ip,ip,sizeof(account.ip));
    if(!rc || memcmp(&previous,&account,sizeof(account))) {
        qtime_t now; account.timestamp=trap_RealTime(&now);
        G_NITMOD_StoreAccountAsync(&account,rc?2:1,UserinfoStored,&context,sizeof(context));
    } else UserinfoStored(1,&context);
}
int G_NITMOD_AccountUserinfo(int n,const char *userinfo) {
    gentity_t *ent; accountGuard_t guard; char guid[64],reason[128];
    int i;
    if(n<0 || n>=MAX_CLIENTS || !userinfo) return 0;
    ent=&g_entities[n]; if(!ent->client || (ent->r.svFlags&SVF_BOT)) return 1;
    Q_strncpyz(guid,Info_ValueForKey(userinfo,"n_guid"),sizeof(guid));
    if(!*guid) {
        if(*identities[n].guid) { G_NITMOD_AccountReset(n); trap_DropClient(n,"Your NGUID has changed",0); return 0; }
        if(!identities[n].requested) { trap_SendServerCommand(n,"getnguid"); identities[n].requested=1; }
        return 1;
    }
    if(strlen(guid)!=32) { G_NITMOD_AccountReset(n); trap_DropClient(n,"Invalid NGUID length",0); return 0; }
    if(*identities[n].guid && Q_stricmp(identities[n].guid,guid)) {
        G_NITMOD_AccountReset(n); trap_DropClient(n,"Your NGUID has changed",0); return 0;
    }
    if(G_NITMOD_LegacyCvarInteger("g_GUIDChecks",1) && !NITMOD_ValidateNGuid(guid,reason,sizeof(reason))) {
        G_NITMOD_AccountReset(n); trap_DropClient(n,reason,0); return 0;
    }
    if(g_XPSave.integer&8) for(i=0;i<MAX_CLIENTS;++i) {
        if(i!=n && *identities[i].guid && !Q_stricmp(guid,identities[i].guid)) {
            G_NITMOD_AccountReset(i); trap_DropClient(i,"Duplicate NGUID detected on the server",0);
        }
    }
    if(!*identities[n].guid) Q_strncpyz(identities[n].guid,guid,sizeof(identities[n].guid));
    Q_strncpyz(identities[n].userinfo,userinfo,sizeof(identities[n].userinfo));
    if(mapResetPending) { identities[n].waitingMap=1; return 1; }
    if(identities[n].userinfoPending) { identities[n].userinfoDirty=1; return 1; }
    AccountGuard(n,&guard); identities[n].userinfoPending=1;
    /* The first existing-user refresh, and initial host open, finish before
     * any XP restore or account-success effect. Queued callbacks own a copy. */
    if(!identities[n].xpLoaded || !G_NITMOD_DatabaseReady())
        G_NITMOD_DatabaseSyncUserAsync(guid,UserinfoReady,&guard,sizeof(guard));
    else UserinfoReady(1,&guard);
    return AccountCurrent(&guard);
}
static int AlphaNumeric(const char *text) {
    for(;*text;++text) if(!((*text>='0' && *text<='9') || (*text>='A' && *text<='Z') || (*text>='a' && *text<='z'))) return 0;
    return 1;
}
typedef struct { int client,count; } mailboxContext_t;
static void Mail(void *context,int id,const char *sender,const char *message) {
    mailboxContext_t *box=context;
    if(!box->count++) Print(box->client,"^7N^1!^7tmod ^xMailer\n^9-----------------------------------------------\n ^xID ^9| ^xFROM                             ^9| ^xMESSAGE\n^9-----------------------------------------------\n");
    Print(box->client,va(" ^x%-2i ^9| ^7%-32s ^9| ^7%s\n^9-----------------------------------------------\n",id,sender,message));
}
typedef struct {
    accountGuard_t guard;
    int kind,id;
    char username[33],password[33];
} accountCommandContext_t;
enum { ACCOUNT_REGISTER=1,ACCOUNT_MAIL_SEND,ACCOUNT_MAIL_DELETE };
static void AccountCommandComplete(int success,const void *opaque) {
    const accountCommandContext_t *context=opaque; int n=context->guard.client;
    if(!AccountCurrent(&context->guard)) return;
    if(context->kind==ACCOUNT_REGISTER) {
        identities[n].registerPending=0;
        if(!success) Print(n,"^1Register: ^gDatabase write failed.\n");
        else Print(n,va("^xRegister: ^gYou are now registered on this server.\n^gYour username is: ^7%s\n^gYour password is: ^7%s\n",context->username,context->password));
    } else if(context->kind==ACCOUNT_MAIL_SEND) {
        if(!success) Print(n,"^xMail: ^1Internal SQLite error. Message could not be sent.\n");
        else Print(n,va("^xMail: ^gYour message has been sent to user ^7%s^g.\n",context->username));
    } else {
        if(!success) Print(n,"^1Deletemail: ^gInternal SQLite error.\n");
        else Print(n,va("^xDeletemail: ^gSucessfully deleted message #%i\n",context->id));
    }
}
int G_NITMOD_AccountCommand(int n,const char *command) {
    nitmodDatabaseAccount_t account; char username[33],password[33],hash[41],message[1022]; int rc;
    if(SecureShrubCommand(n,command)) return 1;
    if(strcmp(command,"register") && strcmp(command,"login") && strcmp(command,"mailto") &&
       strcmp(command,"checkmails") && strcmp(command,"deletemail")) return 0;
    if(n<0 || n>=MAX_CLIENTS || !g_entities[n].client || (g_entities[n].r.svFlags&SVF_BOT) ||
       NITMOD_DBUserCount()<0 || !G_NITMOD_LegacyCvarInteger("n_userMail",1)) return 1;
    if(!G_NITMOD_DatabaseReady() || !identities[n].xpLoaded || identities[n].userinfoPending) { Print(n,"^1Account: ^gDatabase operation is pending.\n"); return 1; }
    if(strlen(identities[n].guid)!=32) { Print(n,"^1Account: ^gYou have an invalid NGUID.\n"); return 1; }
    if(!strcmp(command,"register") || !strcmp(command,"login")) {
        int registering=!strcmp(command,"register");
        if(trap_Argc()<3) { Print(n,registering?"^9usage: ^gregister [username(32 char max)] [password(32 char max)]\n":"^9usage: ^glogin [username] [password]\n"); return 1; }
        trap_Argv(1,username,sizeof(username)); trap_Argv(2,password,sizeof(password));
        if(registering && !AlphaNumeric(username)) { Print(n,"^1Register: ^gUsername can only contain letters and numbers.\n"); return 1; }
        if(registering && !AlphaNumeric(password)) { Print(n,"^1Register: ^gPassword can only contain letters and numbers.\n"); return 1; }
        if(NITMOD_DBAccount(identities[n].guid,&account)!=1) return 1;
        NITMOD_SHA1Text(password,hash);
        if(registering) {
            if(*account.login) { Print(n,va("^1Register: ^gYou are already registered as '^7%s^g' on this server.\n",account.login)); return 1; }
            accountCommandContext_t context;
            if(identities[n].registerPending) { Print(n,"^1Register: ^gDatabase operation is pending.\n"); return 1; }
            memset(&context,0,sizeof(context)); AccountGuard(n,&context.guard); context.kind=ACCOUNT_REGISTER;
            Q_strncpyz(context.username,username,sizeof(context.username)); Q_strncpyz(context.password,password,sizeof(context.password));
            Q_strncpyz(account.login,username,sizeof(account.login)); Q_strncpyz(account.password,hash,sizeof(account.password));
            identities[n].registerPending=1;
            G_NITMOD_StoreAccountAsync(&account,2,AccountCommandComplete,&context,sizeof(context));
        } else {
            if(strcmp(username,account.login)) { Print(n,"^1Login: ^gUsername doesn't match your NGUID\n"); return 1; }
            if(strcmp(hash,account.password)) { Print(n,"^1Login: ^gInvalid password\n"); return 1; }
            identities[n].loggedIn=1; Q_strncpyz(identities[n].login,username,sizeof(identities[n].login));
            identities[n].epoch=NITMOD_DBEpoch();
            Print(n,"^xLogin: ^gYou have successfully logged in to your account\n");
        }
        return 1;
    }
    if(identities[n].epoch!=NITMOD_DBEpoch() || !G_NITMOD_ClientAccount(n,&account) ||
       strcmp(account.login,identities[n].login)) identities[n].loggedIn=0;
    if(!identities[n].loggedIn) { Print(n,"^1Mail: ^gYou have to login first.\n"); return 1; }
    if(!strcmp(command,"checkmails")) {
        mailboxContext_t context={n,0}; rc=NITMOD_DBMails(identities[n].login,Mail,&context);
        if(rc==0) Print(n,"^xMail: ^gEmpty mailbox.\n"); else if(rc<0) Print(n,"^1Mail: ^gInternal SQLite error.\n");
    } else if(!strcmp(command,"mailto")) {
        int i,length; void *before; char part[MAX_STRING_CHARS]; accountCommandContext_t context;
        if(trap_Argc()<3) { Print(n,"^9usage: ^gmailto [username] [message]\n"); return 1; }
        trap_Argv(1,username,sizeof(username)); message[0]=0;
        for(i=2;i<trap_Argc();++i) { trap_Argv(i,part,sizeof(part)); if(i>2) Q_strcat(message,sizeof(message)," "); Q_strcat(message,sizeof(message),part); }
        before=NITMOD_DBExport(&length); if(!before) { Print(n,"^1Mail: ^gInternal SQLite error.\n"); return 1; }
        rc=NITMOD_DBMailSend(identities[n].login,username,message);
        if(rc>0) {
            memset(&context,0,sizeof(context)); AccountGuard(n,&context.guard); context.kind=ACCOUNT_MAIL_SEND;
            Q_strncpyz(context.username,username,sizeof(context.username));
            G_NITMOD_DatabaseCommit(before,length,AccountCommandComplete,&context,sizeof(context));
        } else {
            NITMOD_DBInstallWorking(before,length); NITMOD_DBFreeExport(before);
            if(rc==0) Print(n,va("^1MailTo: ^gUnknown user: '^7%s^g'.\n",username));
            else Print(n,"^xMail: ^1Internal SQLite error. Message could not be sent.\n");
        }
    } else {
        char *end; long id; int length; void *before; accountCommandContext_t context;
        trap_Argv(1,username,sizeof(username)); id=strtol(username,&end,10);
        if(!*username || *end || id<1 || id>2147483647L) { Print(n,"^1Deletemail: ^gNo such mail\n"); return 1; }
        before=NITMOD_DBExport(&length); if(!before) { Print(n,"^1Mail: ^gInternal SQLite error.\n"); return 1; }
        rc=NITMOD_DBMailDelete(identities[n].login,(int)id);
        if(rc>0) {
            memset(&context,0,sizeof(context)); AccountGuard(n,&context.guard); context.kind=ACCOUNT_MAIL_DELETE; context.id=(int)id;
            G_NITMOD_DatabaseCommit(before,length,AccountCommandComplete,&context,sizeof(context));
        } else {
            NITMOD_DBInstallWorking(before,length); NITMOD_DBFreeExport(before);
            if(rc==0) Print(n,"^1Deletemail: ^gNo such mail\n");
            else Print(n,"^1Deletemail: ^gInternal SQLite error.\n");
        }
    }
    return 1;
}
