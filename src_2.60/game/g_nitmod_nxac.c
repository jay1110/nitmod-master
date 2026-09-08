#include "g_local.h"
#include "g_nitmod_nxac.h"
#include "g_nitmod_nxac_transfer.h"
#include "g_nitmod_legacy_cvars.h"
#include "g_nitmod_accounts.h"
#include "g_nitmod_database.h"
#include "g_nitmod_admin.h"
#include "nitmod_lua_events.h"

/* Original table ELF0x2a7d80: {mask,action,index}. Original IDs3/4
 * disagree with the four-element name/action arrays. Never dereference ID4. */
static const struct { unsigned int mask; int action,index; } nxacTable[]={
    {0xffffffffU,0,0},{0x20,2,1},{0x40,0,3},{0x80,0,4}
};
static const char *nxacNames[]={"","GAMEHACK","SCREENSHOT FAILURE","FILETRANSFER CONNECTION FAILED"};
static struct { unsigned int flags,seen; int current,enforce,screenshot,banPending; } nxacClients[MAX_CLIENTS];

static qboolean NxACClient(int n) {
    return n>=0 && n<MAX_CLIENTS && g_entities[n].client && !(g_entities[n].r.svFlags&SVF_BOT);
}
void G_NITMOD_NxACResetClient(int n) {
    if(n>=0 && n<MAX_CLIENTS) memset(&nxacClients[n],0,sizeof(nxacClients[n]));
}
void G_NITMOD_NxACReset(void) {
    memset(nxacClients,0,sizeof(nxacClients));
    trap_Cvar_Set("sv_NxAC",G_NITMOD_LegacyCvarInteger("n_NxAC",2)>0?"1":"0");
}
void G_NITMOD_NxACUsercmd(int n,const usercmd_t *cmd) {
    /* ClientThink 0x41870..0x418ed, before antiwarp and independent of mode. */
    if(cmd && NxACClient(n)) nxacClients[n].flags|=((unsigned int)cmd->flags)&~1U;
}
static void NxACLog(int n,const char *reason) {
    char text[1024],plain[1024],userinfo[MAX_INFO_STRING],ip[64];
    fileHandle_t file=0; qtime_t now; int i;
    trap_GetUserinfo(n,userinfo,sizeof(userinfo));
    Q_strncpyz(ip,Info_ValueForKey(userinfo,"ip"),sizeof(ip));
    /* Sanitize command delimiters from player-controlled identity fields. */
    Com_sprintf(text,sizeof(text),"^1[VIOLATION::%s]^5 0x%04X - Slot #%i ^7%s ^5(%s)",reason,nxacClients[n].flags,n,g_entities[n].client->pers.netname,ip);
    for(i=0;text[i];++i) if(text[i]=='\"' || text[i]=='\n' || text[i]=='\r') text[i]=' ';
    Q_strncpyz(plain,text,sizeof(plain)); Q_CleanStr(plain);
    G_LogPrintf("[NxAC] %s\n",plain);
    trap_RealTime(&now);
    if(trap_FS_FOpenFile("NxAC/NxAC_Violations.log",&file,FS_APPEND)>=0 && file) {
        char line[1200];
        Com_sprintf(line,sizeof(line),"[%02d-%02d-%02d %02d:%02d:%02d] %s\n",now.tm_mon+1,now.tm_mday,(now.tm_year+1900)%100,now.tm_hour,now.tm_min,now.tm_sec,plain);
        trap_FS_Write(line,strlen(line),file);trap_FS_FCloseFile(file);
    }
    for(i=0;i<level.maxclients;++i) if(i!=n && NxACClient(i) && g_entities[i].client->pers.connected==CON_CONNECTED && G_NITMOD_AdminPrivilege(i,"adminchat")) {
        trap_SendServerCommand(i,"pop \"^8/!\\ ^9Nx^7AC ^3WARNING!\"");
        trap_SendServerCommand(i,va("lc \"^9Nx^7AC %s\" -2",text));
        G_AddEvent(&g_entities[i],NITMOD_LuaEventEncode(98),0);
    }
}
typedef struct {
    int client;
    unsigned int generation;
    char guid[33],reason[256];
} nxacBanCommit_t;
static void NxACBanCommitted(int success,const void *context) {
    const nxacBanCommit_t *ban=context;
    nitmodDatabaseAccount_t account;
    int n=ban->client;
    qboolean same=NxACClient(n) && nxacClients[n].banPending &&
        G_NITMOD_AccountConnectionGeneration(n)==ban->generation;
    if(same) nxacClients[n].banPending=0;
    if(!success) {
        G_LogPrintf("[NxAC] GAMEHACK: permanent ban could not be persisted for slot %i\n",n);
        return;
    }
    /* The durable penalty survives a disconnect. A reused slot must never
     * receive the original player's drop or violation identity. */
    if(!same || g_entities[n].client->pers.connected!=CON_CONNECTED ||
       !G_NITMOD_ClientAccount(n,&account) || Q_stricmp(account.user.guid,ban->guid)) {
        G_LogPrintf("[NxAC] GAMEHACK: permanent ban persisted for disconnected account %s\n",ban->guid);
        return;
    }
    NxACLog(n,"AUTOBAN: Banned permanently - GAMEHACK");
    trap_DropClient(n,va("^9Nx^7AC: You have been banned.\n%s",ban->reason),0);
    G_NITMOD_NxACResetClient(n);
}
static void NxACBan(int n) {
    nitmodDatabaseAccount_t account; nitmodDatabasePenalty_t penalty;
    qtime_t now; int length; void *before; nxacBanCommit_t commit;
    if(nxacClients[n].banPending) return;
    if(!G_NITMOD_ClientAccount(n,&account) || !trap_RealTime(&now)) {
        G_LogPrintf("[NxAC] GAMEHACK: cannot persist ban for slot %i (account/time unavailable)\n",n); return;
    }
    memset(&penalty,0,sizeof(penalty));
    Q_strncpyz(penalty.name,account.user.name,sizeof(penalty.name));
    Q_strncpyz(penalty.guid,account.user.guid,sizeof(penalty.guid));
    Q_strncpyz(penalty.ip,account.ip,sizeof(penalty.ip));
    Q_strncpyz(penalty.mac,account.mac,sizeof(penalty.mac));
    Q_strncpyz(penalty.actor,"NxAC_AutoBan",sizeof(penalty.actor));
    Q_strncpyz(penalty.reason,"^9Nx^7AC ^5VIOLATION: ^5[GAMEHACK]",sizeof(penalty.reason));
    Com_sprintf(penalty.made,sizeof(penalty.made),"%02d/%02d/%02d %02d:%02d:%02d",now.tm_mon+1,now.tm_mday,(now.tm_year+1900)%100,now.tm_hour,now.tm_min,now.tm_sec);
    before=NITMOD_DBExport(&length); if(!before) return;
    if(NITMOD_DBPenaltySave(0,&penalty,1)<=0) {
        if(!NITMOD_DBInstallWorking(before,length)) G_Error("SQLite cannot restore failed NxAC ban preparation");
        NITMOD_DBFreeExport(before);
        G_LogPrintf("[NxAC] GAMEHACK: permanent ban could not be prepared for slot %i\n",n);
        return;
    }
    memset(&commit,0,sizeof(commit)); commit.client=n;
    commit.generation=G_NITMOD_AccountConnectionGeneration(n);
    Q_strncpyz(commit.guid,penalty.guid,sizeof(commit.guid));
    Q_strncpyz(commit.reason,penalty.reason,sizeof(commit.reason));
    /* Completion can run inline on native hosts, so publish pending first.
     * The queue owns BEFORE on every result, including submission failure. */
    nxacClients[n].banPending=1;
    G_NITMOD_DatabaseCommit(before,length,NxACBanCommitted,&commit,sizeof(commit));
}
void G_NITMOD_NxACRunFrame(void) {
    int n,i,index,mode=G_NITMOD_LegacyCvarInteger("n_NxAC",2);
    char status[16];
    trap_Cvar_VariableStringBuffer("sv_NxAC",status,sizeof(status));
    if(strcmp(status,mode>0?"1":"0")) trap_Cvar_Set("sv_NxAC",mode>0?"1":"0");
    if(mode<=0) return;
    for(n=0;n<level.maxclients && n<MAX_CLIENTS;++n) {
        unsigned int flags,seen;
        if(!NxACClient(n) || g_entities[n].client->pers.connected!=CON_CONNECTED) continue;
        flags=nxacClients[n].flags; seen=nxacClients[n].seen;
        if(!flags || flags==seen) continue;
        index=-1;
        for(i=1;i<4;++i) if((flags&nxacTable[i].mask) && !(seen&nxacTable[i].mask)) { index=nxacTable[i].index;break; }
        nxacClients[n].seen=flags; /* Original processes only the first new row. */
        if(index<0 || index>=4) {
            nxacClients[n].enforce=-1;
            if(index>=4) NxACLog(n,"UNSUPPORTED ORIGINAL VIOLATION INDEX 4");
            continue;
        }
        if(index<=1) nxacClients[n].enforce=index;
        if(index<1 || nxacClients[n].current==index) continue;
        nxacClients[n].current=index;
        NxACLog(n,nxacNames[index]);
        { char name[MAX_NAME_LENGTH],userinfo[MAX_INFO_STRING],ip[64];int c;
          Q_strncpyz(name,g_entities[n].client->pers.netname,sizeof(name));
          trap_GetUserinfo(n,userinfo,sizeof(userinfo));Q_strncpyz(ip,Info_ValueForKey(userinfo,"ip"),sizeof(ip));
          for(c=0;name[c];++c) if(name[c]=='\"' || name[c]=='\n' || name[c]=='\r')name[c]=' ';
          for(c=0;ip[c];++c) if(ip[c]=='\"' || ip[c]=='\n' || ip[c]=='\r')ip[c]=' ';
          trap_SendServerCommand(-1,va("cpm \"^9Nx^7AC ^5Server - Slot #%i ^7%s^5 (%s) - [%s]\n\"",n,name,ip,nxacNames[index]));
        }
        if(mode==1 && nxacClients[n].enforce==1) NxACBan(n);
        else if(mode==2 && nxacClients[n].enforce==1 && !nxacClients[n].screenshot)
            nxacClients[n].screenshot=G_NITMOD_NxACTransferRequest(n);
    }
}

void G_NITMOD_NxACScreenshotStored(int n) {
    if(NxACClient(n) && nxacClients[n].screenshot && nxacClients[n].enforce==1 && G_NITMOD_LegacyCvarInteger("n_NxAC",2)==2) {
        nxacClients[n].screenshot=0;NxACBan(n);
    }
}

unsigned int G_NITMOD_NxACScreenshotFlags(int n) { return NxACClient(n)?nxacClients[n].flags:0U; }
