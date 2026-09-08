#include "g_local.h"
#include "g_nitmod_nxac.h"
#include "g_nitmod_accounts.h"
#include "g_nitmod_nxac_transfer.h"
#include "nitmod_nxac_tcp.h"
#include "nitmod_md5.h"
#include <stdlib.h>

#define NX_CONNECTIONS 64
#define NX_MEMORY_LIMIT (64*1024*1024)
typedef struct {
    nitmodSocket_t socket;
    int slot,peerPort,state,length,received,headerLength,progress,quiet,start;
    char ip[16],header[128],ext[4],md5[33];
    unsigned char *data;
} nxConnection_t;
static nxConnection_t nxConnections[NX_CONNECTIONS];
static struct { qboolean active,automatic; int time; char ip[16],guid[64]; } nxRequests[MAX_CLIENTS];
static nitmodSocket_t nxListener=NITMOD_SOCKET_INVALID;
static qboolean nxInitialized;
static unsigned int nxFilename;
static int nxAllocated;
static int Elapsed(int a,int b){return (int)((unsigned int)a-(unsigned int)b);}
static qboolean Player(int n) {
    return n>=0 && n<level.maxclients && n<MAX_CLIENTS && g_entities[n].client &&
        g_entities[n].client->pers.connected==CON_CONNECTED && !(g_entities[n].r.svFlags&SVF_BOT);
}
static void Identity(int n,char ip[16],char guid[64],int *port) {
    char info[MAX_INFO_STRING],value[64],*colon;trap_GetUserinfo(n,info,sizeof(info));
    Q_strncpyz(value,Info_ValueForKey(info,"ip"),sizeof(value));colon=strchr(value,':');if(colon)*colon=0;
    if(!strcmp(value,"localhost"))Q_strncpyz(value,"127.0.0.1",sizeof(value));
    Q_strncpyz(ip,value,16);Q_strncpyz(guid,Info_ValueForKey(info,"n_guid"),64);
    if(!guid[0])Q_strncpyz(guid,Info_ValueForKey(info,"cl_guid"),64);
    if(port)*port=atoi(Info_ValueForKey(info,"cnport"));
}
static qboolean SamePlayer(int n) {
    char ip[16],guid[64];if(!Player(n) || !nxRequests[n].active)return qfalse;
    Identity(n,ip,guid,NULL);return !strcmp(ip,nxRequests[n].ip) && !strcmp(guid,nxRequests[n].guid);
}
static void CloseConnection(nxConnection_t *c) {
    NITMOD_TCPClose(&c->socket);if(c->data){free(c->data);nxAllocated-=c->length;}
    memset(c,0,sizeof(*c));c->socket=NITMOD_SOCKET_INVALID;c->slot=-1;
}
void G_NITMOD_NxACTransferResetClient(int n) {
    int i;if(n<0 || n>=MAX_CLIENTS)return;
    memset(&nxRequests[n],0,sizeof(nxRequests[n]));
    for(i=0;i<NX_CONNECTIONS;++i)if(nxConnections[i].state && nxConnections[i].slot==n)CloseConnection(&nxConnections[i]);
}
void G_NITMOD_NxACTransferShutdown(void) {
    int i;if(nxInitialized){for(i=0;i<NX_CONNECTIONS;++i)CloseConnection(&nxConnections[i]);NITMOD_TCPClose(&nxListener);NITMOD_TCPShutdown();}
    nxInitialized=qfalse;nxAllocated=0;memset(nxRequests,0,sizeof(nxRequests));
}
void G_NITMOD_NxACTransferInit(void) {
    char ip[64],port[32];int actual=0,i;
    G_NITMOD_NxACTransferShutdown();
    for(i=0;i<NX_CONNECTIONS;++i){nxConnections[i].socket=NITMOD_SOCKET_INVALID;nxConnections[i].slot=-1;}
    trap_Cvar_Register(NULL,"nport","0",CVAR_SERVERINFO|CVAR_ROM);
    trap_Cvar_Set("nport","0");
    if(!NITMOD_TCPInit()) {
        G_LogPrintf("[NxAC] Screenshot TCP listener unavailable: this browser/VM host requires an external NxAC listener and game-session adapter.\n");return;
    }
    nxInitialized=qtrue;
    trap_Cvar_VariableStringBuffer("net_ip",ip,sizeof(ip));
    trap_Cvar_VariableStringBuffer("net_port",port,sizeof(port));
    nxListener=NITMOD_TCPListen(ip,atoi(port),&actual);
    if(nxListener==NITMOD_SOCKET_INVALID){G_LogPrintf("[NxAC] Cannot bind native screenshot TCP listener on net_port.\n");return;}
    Com_sprintf(port,sizeof(port),"%d",actual);trap_Cvar_Set("nport",port);
#if defined(__EMSCRIPTEN__) || defined(NITMOD_NXAC_HOST_TEST)
    G_LogPrintf("[NxAC] Host screenshot channel ready on port %d.\n",actual);
#else
    G_LogPrintf("[NxAC] Native screenshot TCP listener ready on port %d.\n",actual);
#endif
}
static qboolean Request(int n,int quality,qboolean automatic) {
    if(!Player(n))return qfalse;
    if(nxListener==NITMOD_SOCKET_INVALID){G_LogPrintf("[NxAC] Screenshot request for slot %d unavailable: no native TCP listener.\n",n);return qfalse;}
    G_NITMOD_NxACTransferResetClient(n);
    nxRequests[n].active=qtrue;nxRequests[n].automatic=automatic;nxRequests[n].time=trap_Milliseconds();
    Identity(n,nxRequests[n].ip,nxRequests[n].guid,NULL);
    trap_SendServerCommand(n,va("getss %d",quality));return qtrue;
}
qboolean G_NITMOD_NxACTransferRequest(int n){return Request(n,80,qtrue);}
qboolean G_NITMOD_NxACTransferConsoleCommand(const char *cmd) {
    char query[MAX_NAME_LENGTH],clean[MAX_NAME_LENGTH],name[MAX_NAME_LENGTH],qualityText[16],*end;
    int quality=70,n,match=-1,count=0;long numeric;
    if(strcmp(cmd,"getss"))return qfalse;
    if(g_gamestate.integer!=GS_PLAYING){G_Printf("/!\\ NxAC: Can't query screenshots during Warmup/Intermission\n");return qtrue;}
    if(trap_Argc()<2){G_Printf("usage: getss [name|slot#] (JPEG Quality)\n");return qtrue;}
    trap_Argv(1,query,sizeof(query));if(trap_Argc()>2){trap_Argv(2,qualityText,sizeof(qualityText));quality=atoi(qualityText);if(quality<10)quality=10;if(quality>100)quality=100;}
    numeric=strtol(query,&end,10);
    if(query[0] && !*end && numeric>=0 && numeric<MAX_CLIENTS && Player((int)numeric)){match=(int)numeric;count=1;}
    else {
        Q_strncpyz(clean,query,sizeof(clean));Q_CleanStr(clean);Q_strlwr(clean);
        for(n=0;n<level.maxclients && n<MAX_CLIENTS;++n)if(Player(n)) {
            Q_strncpyz(name,g_entities[n].client->pers.netname,sizeof(name));Q_CleanStr(name);Q_strlwr(name);
            if(clean[0] && strstr(name,clean)){match=n;++count;}
        }
    }
    if(count!=1)G_Printf("getss: expected exactly one matching connected player (got %d)\n",count);
    else if(Request(match,quality,qfalse))G_LogPrintf("[NxAC] Screenshot requested by server console for slot %d.\n",match);
    return qtrue;
}
static void Fail(nxConnection_t *c,const char *reason) {
    if(c->slot>=0){G_LogPrintf("[NxAC] Screenshot slot %d rejected: %s\n",c->slot,reason);nxRequests[c->slot].active=qfalse;}
    CloseConnection(c);
}
static int MatchPeer(nxConnection_t *c,int heartbeat,qboolean completeBoundary) {
    int n,port,found=-1;char ip[16],guid[64];
    for(n=0;n<level.maxclients && n<MAX_CLIENTS;++n)if(SamePlayer(n)) {
        Identity(n,ip,guid,&port);
        if(port>0 && port<=65535 && !strcmp(ip,c->ip) && (port==heartbeat || (completeBoundary && port==c->peerPort))) {
            if(found!=-1)return -1;found=n;
        }
    }return found;
}
static qboolean Exists(const char *path) {
    fileHandle_t f=0;int n=trap_FS_FOpenFile(path,&f,FS_READ);if(f)trap_FS_FCloseFile(f);return f || n>=0;
}
static qboolean WriteVerified(const char *path,const void *data,int size) {
    fileHandle_t f=0;int n;unsigned char *check;char expected[33],actual[33];
    if(Exists(path))return qfalse;
    trap_FS_FOpenFile(path,&f,FS_WRITE);if(!f)return qfalse;
    /* Some legacy engines expose this trap as void. Read back actual bytes;
     * never infer successful persistence from a syscall's return convention. */
    trap_FS_Write(data,size,f);trap_FS_FCloseFile(f);f=0;
    n=trap_FS_FOpenFile(path,&f,FS_READ);if(!f || n!=size){if(f)trap_FS_FCloseFile(f);return qfalse;}
    check=(unsigned char *)malloc(size);if(!check){trap_FS_FCloseFile(f);return qfalse;}
    memset(check,0,size);trap_FS_Read(check,size,f);trap_FS_FCloseFile(f);
    NITMOD_MD5Hex(data,size,expected);NITMOD_MD5Hex(check,size,actual);free(check);return !strcmp(expected,actual);
}
static void MetadataValue(char *text){int i;for(i=0;text[i];++i)if(text[i]=='\n' || text[i]=='\r')text[i]=' ';}
static qboolean Store(nxConnection_t *c) {
    char hash[33],base[MAX_QPATH],image[MAX_QPATH],metadata[MAX_QPATH],text[1024],name[MAX_NAME_LENGTH];
    int i; qtime_t now; nitmodDatabaseAccount_t account;
    char info[MAX_INFO_STRING],version[128],build[128],guid[64],mac[64];
    NITMOD_MD5Hex(c->data,c->length,hash);if(strcmp(hash,c->md5))return qfalse;
    if(!strcmp(c->ext,"jpg")) {
        if(c->data[0]!=0xff || c->data[1]!=0xd8 || c->data[c->length-2]!=0xff || c->data[c->length-1]!=0xd9)return qfalse;
    } else {
        static const unsigned char signature[8]={137,80,78,71,13,10,26,10};
        if(c->length<8 || memcmp(c->data,signature,8))return qfalse;
    }
    for(i=0;i<100;++i) {
        /* Never append to, replace or remove any previous capture. */
        Com_sprintf(base,sizeof(base),"NxAC/screenshots/%s_%08x",hash,++nxFilename);
        Com_sprintf(image,sizeof(image),"%s.%s",base,c->ext);Com_sprintf(metadata,sizeof(metadata),"%s.txt",base);
        if(!Exists(image) && !Exists(metadata))break;
    }
    if(i==100 || !WriteVerified(image,c->data,c->length))return qfalse;
    memset(&now,0,sizeof(now));trap_RealTime(&now);
    Q_strncpyz(name,g_entities[c->slot].client->pers.netname,sizeof(name));Q_CleanStr(name);
    for(i=0;name[i];++i)if(name[i]=='\n' || name[i]=='\r')name[i]=' ';
    memset(&account,0,sizeof(account));G_NITMOD_ClientAccount(c->slot,&account);
    trap_GetUserinfo(c->slot,info,sizeof(info));
    Q_strncpyz(version,Info_ValueForKey(info,"etVersion"),sizeof(version));Q_strncpyz(build,Info_ValueForKey(info,"build"),sizeof(build));
    Q_strncpyz(guid,account.user.guid[0]?account.user.guid:nxRequests[c->slot].guid,sizeof(guid));Q_strncpyz(mac,account.mac,sizeof(mac));
    MetadataValue(version);MetadataValue(build);MetadataValue(guid);MetadataValue(mac);
    Com_sprintf(text,sizeof(text),"Date: %04d-%02d-%02d %02d:%02d:%02d\nFile: %s\nSlot: %d\nPlayer: %s\nIP: %s\nNGUID: %s\nMAC: %s\nClient: %s\nBuild: %s\nReason: %s\nCode: 0x%04X\nBytes: %d\nMD5: %s\n",
        now.tm_year+1900,now.tm_mon+1,now.tm_mday,now.tm_hour,now.tm_min,now.tm_sec,image,c->slot,name,c->ip,guid,mac,version,build,
        nxRequests[c->slot].automatic?"NXAC_AUTOSCREENSHOT [GAMEHACK]":"Requested by admin",
        nxRequests[c->slot].automatic?G_NITMOD_NxACScreenshotFlags(c->slot):0U,c->length,hash);
    if(!WriteVerified(metadata,text,(int)strlen(text)))return qfalse;
    G_LogPrintf("[NxAC] Screenshot slot %d verified and stored: %s (%d bytes).\n",c->slot,image,c->length);return qtrue;
}
static void ProcessHeader(nxConnection_t *c,int now) {
    int i,port=0,result,slot,j;
    if(c->state==1) {
        if(c->headerLength<3)return;
        if(memcmp(c->header,"hb ",3)){Fail(c,"invalid heartbeat");return;}
        for(i=3;i<c->headerLength && c->header[i]>='0' && c->header[i]<='9';++i){port=port*10+c->header[i]-'0';if(port>65535){Fail(c,"invalid heartbeat port");return;}}
        if(i==3 || port<1){Fail(c,"invalid heartbeat port");return;}
        /* hb has no terminator in the original protocol. An idle gap, or the
         * next ift token, terminates it; fragmentation never blocks a frame. */
        if(i==c->headerLength && Elapsed(now,c->quiet)<=100)return;
        if(i<c->headerLength && c->header[i]!='i'){Fail(c,"unexpected heartbeat suffix");return;}
        slot=MatchPeer(c,port,i<c->headerLength);if(slot<0)return; /* cnport may arrive next game packet */
        for(j=0;j<NX_CONNECTIONS;++j)if(&nxConnections[j]!=c && nxConnections[j].state && nxConnections[j].slot==slot){Fail(c,"duplicate connection");return;}
        c->slot=slot;c->state=2;memmove(c->header,c->header+i,c->headerLength-i);c->headerLength-=i;
    }
    if(c->state!=2)return;
    result=NITMOD_NxACParseHeader(c->header,c->headerLength,&c->length,c->ext,c->md5);
    if(result<0){Fail(c,"invalid or oversized metadata");return;}if(!result)return;
    if(!SamePlayer(c->slot) || nxAllocated>NX_MEMORY_LIMIT-c->length){Fail(c,"request identity or memory limit");return;}
    c->data=(unsigned char *)malloc(c->length);if(!c->data){Fail(c,"allocation failed");return;}
    nxAllocated+=c->length;c->state=3;c->progress=now;
    trap_SendServerCommand(c->slot,"fta");
}
void G_NITMOD_NxACTransferRunFrame(void) {
    int i,j,n,now=trap_Milliseconds();char ip[16];int port;nitmodSocket_t socket;
    if(nxListener==NITMOD_SOCKET_INVALID)return;
    for(i=0;i<MAX_CLIENTS;++i)if(nxRequests[i].active && (!SamePlayer(i) || Elapsed(now,nxRequests[i].time)>60000)) {
        G_LogPrintf("[NxAC] Screenshot request slot %d expired or player identity changed.\n",i);G_NITMOD_NxACTransferResetClient(i);
    }
    /* Bounded accepts and per-connection reads; no blocking recv loops. */
    for(j=0;j<8;++j) {
        socket=NITMOD_TCPAccept(nxListener,ip,&port);if(socket==NITMOD_SOCKET_INVALID)break;
        for(i=0;i<NX_CONNECTIONS && nxConnections[i].state;++i){}
        if(i==NX_CONNECTIONS){NITMOD_TCPClose(&socket);break;}
        nxConnections[i].socket=socket;nxConnections[i].state=1;nxConnections[i].slot=-1;
        nxConnections[i].peerPort=port;Q_strncpyz(nxConnections[i].ip,ip,sizeof(nxConnections[i].ip));
        nxConnections[i].progress=nxConnections[i].quiet=nxConnections[i].start=now;
    }
    for(i=0;i<NX_CONNECTIONS;++i) {
        nxConnection_t *c=&nxConnections[i];if(!c->state)continue;
        if(Elapsed(now,c->start)>60000 || Elapsed(now,c->progress)>10000 || (c->state<3 && Elapsed(now,c->start)>10000) || (c->slot>=0 && c->state<4 && !SamePlayer(c->slot))) {Fail(c,"deadline or identity changed");continue;}
        if(c->state<3) {
            if(c->headerLength>=127){Fail(c,"header limit");continue;}
            n=NITMOD_TCPRecv(c->socket,c->header+c->headerLength,127-c->headerLength);
            if(n<0){Fail(c,"connection closed before data");continue;}
            if(n>0){c->headerLength+=n;c->progress=c->quiet=now;}
            ProcessHeader(c,now);
        } else if(c->state==3) {
            unsigned char chunk[NITMOD_NXAC_CHUNK];n=NITMOD_TCPRecv(c->socket,chunk,sizeof(chunk));
            if(n<0){Fail(c,"connection closed during data");continue;}
            if(!n)continue;if(n>c->length-c->received){Fail(c,"bytes exceed declared length");continue;}
            memcpy(c->data+c->received,chunk,n);c->received+=n;c->progress=now;
            if(c->received==c->length) {
                int slot=c->slot; qboolean automatic=nxRequests[slot].automatic;
                if(!Store(c)){Fail(c,"checksum, image or persistent write verification failed");continue;}
                /* Confirm only verified persistent bytes; Original confirms earlier. */
                trap_SendServerCommand(slot,"ftc");nxRequests[slot].active=qfalse;
                free(c->data);c->data=NULL;nxAllocated-=c->length;c->state=4;c->headerLength=0;
                if(automatic)G_NITMOD_NxACScreenshotStored(slot);
            }
        } else if(c->state==4) {
            n=NITMOD_TCPRecv(c->socket,c->header+c->headerLength,2-c->headerLength);
            if(n<0){CloseConnection(c);continue;}
            if(n>0)c->headerLength+=n;
            if(c->headerLength==2){if(memcmp(c->header,"fl",2))G_LogPrintf("[NxAC] Unexpected post-transfer bytes for slot %d.\n",c->slot);CloseConnection(c);}
        }
    }
}
