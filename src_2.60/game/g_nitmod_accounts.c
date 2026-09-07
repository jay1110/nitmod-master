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
static struct { char guid[33],login[33]; int loggedIn,requested,xpLoaded,secureShrub,begun,greeted; unsigned int epoch; } identities[MAX_CLIENTS];
void G_NITMOD_AccountReset(int n) { if(n>=0 && n<MAX_CLIENTS) memset(&identities[n],0,sizeof(identities[n])); }
void G_NITMOD_AccountBegin(int n) {
    nitmodDatabaseAccount_t account;
    if(n<0 || n>=MAX_CLIENTS) return;
    identities[n].begun=1;
    if(!identities[n].greeted && G_NITMOD_ClientAccount(n,&account)) {
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
static int Commit(void *before,int length,int changed) {
    int ok=changed>0 && G_NITMOD_DatabaseFlush();
    if(!ok && changed>0 && before && !NITMOD_DBOpenWorking(before,length)) G_LogPrintf("[SQLite] Failed to restore account transaction\n");
    NITMOD_DBFreeExport(before); return ok;
}
int G_NITMOD_StoreAccount(const nitmodDatabaseAccount_t *account,int mode) {
    int length; void *before=NITMOD_DBExport(&length);
    if(!before) return 0;
    return Commit(before,length,NITMOD_DBSaveAccount(account,mode));
}
int G_NITMOD_ClientAccount(int n,nitmodDatabaseAccount_t *account) {
    if(n<0 || n>=MAX_CLIENTS || !*identities[n].guid || !g_entities[n].client ||
       (g_entities[n].r.svFlags&SVF_BOT)) return 0;
    return NITMOD_DBAccount(identities[n].guid,account)==1;
}
const char *G_NITMOD_DatabaseBanReason(const char *userinfo) {
    static char reason[1024]; char guid[64],ip[64],duration[64]; nitmodDatabasePenalty_t penalty;
    qtime_t now; int rc,expired,time;
    if(NITMOD_DBUserCount()<0) return NULL;
    Q_strncpyz(guid,Info_ValueForKey(userinfo,"n_guid"),sizeof(guid));
    Q_strncpyz(ip,Info_ValueForKey(userinfo,"ip"),sizeof(ip));
    time=trap_RealTime(&now)-946490400;
    rc=NITMOD_DBPenaltyCheck(0,ip,guid,"",time,&penalty,&expired);
    if(expired && !G_NITMOD_DatabaseFlush()) G_LogPrintf("[SQLite] Failed to persist expired bans\n");
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
    nitmodDatabasePenalty_t penalty; qtime_t now; int rc,expired;
    if(n<0 || n>=MAX_CLIENTS || !*identities[n].guid || NITMOD_DBUserCount()<0) return 0;
    rc=NITMOD_DBPenaltyCheck(1,"",identities[n].guid,"",trap_RealTime(&now)-946490400,&penalty,&expired);
    if(expired && !G_NITMOD_DatabaseFlush()) G_LogPrintf("[SQLite] Failed to persist expired mutes\n");
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
       g_entities[n].client->pers.nitmodDemoClient || !*identities[n].guid) return 1;
    { int rc=NITMOD_DBAccount(identities[n].guid,&account); if(rc!=1) return rc==0; }
    if((g_XPSave.integer&1) && !NITMOD_XPEncode(g_entities[n].client->sess.skillpoints,account.user.xp)) return 0;
    account.timestamp=trap_RealTime(&now);
    Q_strncpyz(account.user.name,g_entities[n].client->pers.netname,sizeof(account.user.name));
    return NITMOD_DBSaveAccount(&account,2);
}
int G_NITMOD_AccountResetXP(int n) {
    nitmodDatabaseAccount_t account; gclient_t *client; float zero[7]={0}; qtime_t now; int war;
    if(!G_NITMOD_ClientAccount(n,&account)) return 0;
    if(!NITMOD_XPEncode(zero,account.user.xp)) return 0;
    account.timestamp=trap_RealTime(&now);
    if(!G_NITMOD_StoreAccount(&account,2)) return 0;
    client=g_entities[n].client;
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
    ClientUserinfoChanged(n); return 1;
}
void G_NITMOD_AccountSaveXP(int n) {
    int length,ok; void *before;
    if(NITMOD_DBUserCount()<0) return;
    before=NITMOD_DBExport(&length); if(!before) return;
    ok=UpdateXP(n) && G_NITMOD_DatabaseFlush();
    if(!ok) { NITMOD_DBOpenWorking(before,length); G_LogPrintf("[SQLite] Failed to persist XP for client %d\n",n); }
    NITMOD_DBFreeExport(before);
}
void G_NITMOD_AccountsSaveAllXP(void) {
    int i,length,ok=1; void *before;
    if(NITMOD_DBUserCount()<0) return;
    before=NITMOD_DBExport(&length); if(!before) return;
    for(i=0;i<MAX_CLIENTS && ok;++i) ok=UpdateXP(i);
    if(ok) ok=G_NITMOD_DatabaseFlush();
    if(!ok) { NITMOD_DBOpenWorking(before,length); G_LogPrintf("[SQLite] Failed to persist player XP batch\n"); }
    NITMOD_DBFreeExport(before);
}
void G_NITMOD_AccountsMapStart(void) {
    int length; void *before;
    if(NITMOD_DBUserCount()<0 || (g_XPSave.integer&4)) return;
    if(g_gametype.integer==GT_WOLF_CAMPAIGN && g_campaigns[level.currentCampaign].current!=0 && !level.newCampaign) return;
    if((g_gametype.integer==GT_WOLF_STOPWATCH || g_gametype.integer==GT_WOLF_LMS) && g_currentRound.integer!=0) return;
    if((g_gametype.integer==GT_WOLF_MAPVOTE ||
       (g_gametype.integer==GT_WOLF_TDM && (G_NITMOD_LegacyCvarInteger("g_TDMOptions",0)&8)) ||
       (g_gametype.integer==GT_WOLF_DM && (g_DMOptions.integer&0x4000))) && !G_NITMOD_MapCycleResetsXP()) return;
    before=NITMOD_DBExport(&length); if(!before) return;
    if(!Commit(before,length,NITMOD_DBClearXP())) G_LogPrintf("[SQLite] Failed to persist map-start XP reset\n");
}
int G_NITMOD_AccountUserinfo(int n,const char *userinfo) {
    gentity_t *ent; nitmodDatabaseAccount_t account,before; char guid[64],reason[128],ip[64],*port;
    int rc,i;
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
    if(NITMOD_DBUserCount()<0) return 1;
    { const char *ban=G_NITMOD_DatabaseBanReason(userinfo); if(ban) { G_NITMOD_AccountReset(n); trap_DropClient(n,ban,0); return 0; } }
    rc=NITMOD_DBAccount(identities[n].guid,&account); if(rc<0) return 1;
    if(!rc) { memset(&account,0,sizeof(account)); Q_strncpyz(account.user.guid,identities[n].guid,sizeof(account.user.guid)); }
    if(rc) RestoreXP(n,&account); else identities[n].xpLoaded=1;
    before=account;
    Q_strncpyz(account.user.name,ent->client->pers.netname,sizeof(account.user.name));
    Q_strncpyz(ip,Info_ValueForKey(userinfo,"ip"),sizeof(ip)); port=strchr(ip,':'); if(port) *port=0;
    Q_strncpyz(account.ip,ip,sizeof(account.ip));
    if(!rc || memcmp(&before,&account,sizeof(account))) {
        qtime_t now; account.timestamp=trap_RealTime(&now);
        if(!G_NITMOD_StoreAccount(&account,rc?2:1))
            G_LogPrintf("[SQLite] Failed to persist client account %d\n",n);
    }
    if(identities[n].begun) G_NITMOD_AccountBegin(n);
    return 1;
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
int G_NITMOD_AccountCommand(int n,const char *command) {
    nitmodDatabaseAccount_t account; char username[33],password[33],hash[41],message[1022]; int rc;
    if(SecureShrubCommand(n,command)) return 1;
    if(strcmp(command,"register") && strcmp(command,"login") && strcmp(command,"mailto") &&
       strcmp(command,"checkmails") && strcmp(command,"deletemail")) return 0;
    if(n<0 || n>=MAX_CLIENTS || !g_entities[n].client || (g_entities[n].r.svFlags&SVF_BOT) ||
       NITMOD_DBUserCount()<0 || !G_NITMOD_LegacyCvarInteger("n_userMail",1)) return 1;
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
            Q_strncpyz(account.login,username,sizeof(account.login)); Q_strncpyz(account.password,hash,sizeof(account.password));
            if(!G_NITMOD_StoreAccount(&account,2)) { Print(n,"^1Register: ^gDatabase write failed.\n"); return 1; }
            Print(n,va("^xRegister: ^gYou are now registered on this server.\n^gYour username is: ^7%s\n^gYour password is: ^7%s\n",username,password));
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
        int i,length; void *before; char part[MAX_STRING_CHARS];
        if(trap_Argc()<3) { Print(n,"^9usage: ^gmailto [username] [message]\n"); return 1; }
        trap_Argv(1,username,sizeof(username)); message[0]=0;
        for(i=2;i<trap_Argc();++i) { trap_Argv(i,part,sizeof(part)); if(i>2) Q_strcat(message,sizeof(message)," "); Q_strcat(message,sizeof(message),part); }
        before=NITMOD_DBExport(&length); if(!before) { Print(n,"^1Mail: ^gInternal SQLite error.\n"); return 1; }
        rc=NITMOD_DBMailSend(identities[n].login,username,message);
        if(!Commit(before,length,rc) && rc>0) rc=-1;
        if(rc==0) Print(n,va("^1MailTo: ^gUnknown user: '^7%s^g'.\n",username));
        else if(rc<0) Print(n,"^xMail: ^1Internal SQLite error. Message could not be sent.\n");
        else Print(n,va("^xMail: ^gYour message has been sent to user ^7%s^g.\n",username));
    } else {
        char *end; long id; int length; void *before;
        trap_Argv(1,username,sizeof(username)); id=strtol(username,&end,10);
        if(!*username || *end || id<1 || id>2147483647L) { Print(n,"^1Deletemail: ^gNo such mail\n"); return 1; }
        before=NITMOD_DBExport(&length); if(!before) { Print(n,"^1Mail: ^gInternal SQLite error.\n"); return 1; }
        rc=NITMOD_DBMailDelete(identities[n].login,(int)id);
        if(!Commit(before,length,rc) && rc>0) rc=-1;
        if(rc==0) Print(n,"^1Deletemail: ^gNo such mail\n");
        else if(rc<0) Print(n,"^1Deletemail: ^gInternal SQLite error.\n");
        else Print(n,va("^xDeletemail: ^gSucessfully deleted message #%i\n",(int)id));
    }
    return 1;
}
