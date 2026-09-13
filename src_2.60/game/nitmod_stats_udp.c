#include "nitmod_stats_udp.h"
#include <string.h>
#include <stdio.h>
#ifdef __EMSCRIPTEN__
int NITMOD_StatsUDPInit(const char *address) { return 0; }
int NITMOD_StatsUDPStart(int client,const char *guid) { return 0; }
int NITMOD_StatsUDPUpload(const char *packet) { return 0; }
void NITMOD_StatsUDPPoll(void) {}
int NITMOD_StatsUDPRead(int client,char *out,int size) { return 0; }
void NITMOD_StatsUDPCancel(int client) {}
void NITMOD_StatsUDPShutdown(void) {}
#else
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET statsSocket_t;
#define STATS_INVALID INVALID_SOCKET
#define StatsClose closesocket
static int winsockStarted;
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
typedef int statsSocket_t;
#define STATS_INVALID (-1)
#define StatsClose close
#endif
static statsSocket_t masterSocket=STATS_INVALID;
static struct sockaddr_in masterAddress;
static struct { char guid[33],reply[1401]; int pending,ready; } requests[64];
static int EqualASCII(const char *a,const char *b,int length) {
    int i;for(i=0;i<length;i++) {
        unsigned char x=(unsigned char)a[i],y=(unsigned char)b[i];
        if(x>='A'&&x<='Z')x+='a'-'A';
        if(y>='A'&&y<='Z')y+='a'-'A';
        if(x!=y)return 0;
    }return 1;
}
void NITMOD_StatsUDPCancel(int client) {
    if(client>=0&&client<64)memset(&requests[client],0,sizeof(requests[client]));
}
void NITMOD_StatsUDPShutdown(void) {
    if(masterSocket!=STATS_INVALID)StatsClose(masterSocket);
    masterSocket=STATS_INVALID;
    memset(requests,0,sizeof(requests));
#ifdef _WIN32
    if(winsockStarted)WSACleanup();
    winsockStarted=0;
#endif
}
int NITMOD_StatsUDPInit(const char *bindAddress) {
    struct sockaddr_in localAddress;
    struct hostent *host;
#ifdef _WIN32
    WSADATA data;u_long nonblocking=1;
#else
    int nonblocking=1;
#endif
    NITMOD_StatsUDPShutdown();
#ifdef _WIN32
    if(WSAStartup(MAKEWORD(2,2),&data))return 0;
    winsockStarted=1;
#endif
    masterSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(masterSocket==STATS_INVALID)goto failed;
#ifdef _WIN32
    if(ioctlsocket(masterSocket,FIONBIO,&nonblocking))goto failed;
#else
    if(ioctl(masterSocket,FIONBIO,&nonblocking))goto failed;
#endif
    memset(&localAddress,0,sizeof(localAddress));
    localAddress.sin_family=AF_INET;
    /* Original net_ip localhost/127.0.0.1 binds the wildcard, port zero. */
    if(bindAddress&&*bindAddress&&!(strlen(bindAddress)==9&&EqualASCII(bindAddress,"localhost",9))&&strcmp(bindAddress,"127.0.0.1"))
        localAddress.sin_addr.s_addr=inet_addr(bindAddress);
    if(bind(masterSocket,(struct sockaddr *)&localAddress,sizeof(localAddress)))goto failed;
    host=gethostbyname("master.etmods.net");
    if(!host||host->h_addrtype!=AF_INET||host->h_length!=4||!host->h_addr_list[0])goto failed;
    memset(&masterAddress,0,sizeof(masterAddress));
    masterAddress.sin_family=AF_INET;
    masterAddress.sin_port=htons(8475);
    memcpy(&masterAddress.sin_addr,host->h_addr_list[0],4);
    return 1;
failed:
    NITMOD_StatsUDPShutdown();return 0;
}
static int SendPacket(const char *payload) {
    char wire[256];size_t length;
    if(masterSocket==STATS_INVALID||!payload)return 0;
    wire[0]=(char)0xb0;
    length=strlen(payload);if(length>254)length=254;
    memcpy(wire+1,payload,length);wire[length+1]=0;
    return sendto(masterSocket,wire,(int)length+1,0,(struct sockaddr *)&masterAddress,sizeof(masterAddress))==(int)length+1;
}
int NITMOD_StatsUDPUpload(const char *packet) { return SendPacket(packet); }
int NITMOD_StatsUDPStart(int client,const char *guid) {
    char query[40];
    if(client<0||client>=64||!guid||strlen(guid)!=32)return 0;
    NITMOD_StatsUDPCancel(client);
    snprintf(query,sizeof(query),"gsg %s",guid);
    if(!SendPacket(query))return 0;
    memcpy(requests[client].guid,guid,33);requests[client].pending=1;return 1;
}
void NITMOD_StatsUDPPoll(void) {
    char wire[1401];int length,i;
    if(masterSocket==STATS_INVALID)return;
    /* Original frame receives one datagram and dispatches ps to the GUID parser. */
    length=(int)recv(masterSocket,wire,1400,0);
    if(length<36)return;
    wire[length]=0;
    if((wire[0]!='p'&&wire[0]!='P')||(wire[1]!='s'&&wire[1]!='S')||wire[2]!=' ')return;
    for(i=0;i<64;i++)if(requests[i].pending&&EqualASCII(wire+3,requests[i].guid,32)) {
        memcpy(requests[i].reply,wire+3,(size_t)length-2);
        requests[i].ready=1;
    }
}
int NITMOD_StatsUDPRead(int client,char *out,int size) {
    size_t length;
    if(client<0||client>=64||!requests[client].ready)return 0;
    length=strlen(requests[client].reply);
    if(size<=0||length>=(size_t)size){NITMOD_StatsUDPCancel(client);return -1;}
    memcpy(out,requests[client].reply,length+1);requests[client].ready=0;return 1;
}
#endif
