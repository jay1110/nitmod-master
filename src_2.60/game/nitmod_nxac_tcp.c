#include "nitmod_nxac_tcp.h"
#include <string.h>
#include <stdlib.h>
#if defined(__EMSCRIPTEN__) || defined(NITMOD_NXAC_HOST_TEST)
#include "nitmod_nxac_host.h"
static int nxHostReferences;
int NITMOD_TCPInit(void){if(!trap_NITMOD_NxACTransport(NXHOST_CAPS,0,NULL,0,0))return 0;++nxHostReferences;return 1;}
void NITMOD_TCPShutdown(void){if(nxHostReferences>0 && --nxHostReferences==0)trap_NITMOD_NxACTransport(NXHOST_RESET,0,NULL,0,0);}
void NITMOD_TCPClose(nitmodSocket_t *s){if(*s!=NITMOD_SOCKET_INVALID)trap_NITMOD_NxACTransport(NXHOST_CLOSE,(int)*s,NULL,0,0);*s=NITMOD_SOCKET_INVALID;}
nitmodSocket_t NITMOD_TCPListen(const char *ip,int port,int *actual){
    nitmodNxACHostInfo_t info;int h;(void)ip;
    h=trap_NITMOD_NxACTransport(NXHOST_LISTEN,0,NULL,0,port);if(h<1)return NITMOD_SOCKET_INVALID;
    if(trap_NITMOD_NxACTransport(NXHOST_INFO,h,&info,sizeof(info),0)!=1 || info.localPort<1 || info.localPort>65535){trap_NITMOD_NxACTransport(NXHOST_CLOSE,h,NULL,0,0);return NITMOD_SOCKET_INVALID;}
    *actual=info.localPort;return h;
}
nitmodSocket_t NITMOD_TCPConnect(const char *ip,int port,const char *bindIp,int *actual){int h;(void)ip;(void)bindIp;*actual=0;h=trap_NITMOD_NxACTransport(NXHOST_CONNECT,0,NULL,0,port);return h>0?h:NITMOD_SOCKET_INVALID;}
int NITMOD_TCPConnected(nitmodSocket_t s){nitmodNxACHostInfo_t info;return trap_NITMOD_NxACTransport(NXHOST_INFO,(int)s,&info,sizeof(info),0);}
int NITMOD_TCPLocalPort(nitmodSocket_t s){nitmodNxACHostInfo_t info;return trap_NITMOD_NxACTransport(NXHOST_INFO,(int)s,&info,sizeof(info),0)==1?info.localPort:0;}
nitmodSocket_t NITMOD_TCPAccept(nitmodSocket_t listener,char ip[16],int *port){
    nitmodNxACHostInfo_t info;int h=trap_NITMOD_NxACTransport(NXHOST_ACCEPT,(int)listener,NULL,0,0);if(h<1)return NITMOD_SOCKET_INVALID;
    if(trap_NITMOD_NxACTransport(NXHOST_INFO,h,&info,sizeof(info),0)!=1){trap_NITMOD_NxACTransport(NXHOST_CLOSE,h,NULL,0,0);return NITMOD_SOCKET_INVALID;}
    memcpy(ip,info.peerIp,16);ip[15]=0;*port=info.peerPort;return h;
}
int NITMOD_TCPSend(nitmodSocket_t s,const void *p,int n){return trap_NITMOD_NxACTransport(NXHOST_SEND,(int)s,(void *)p,n,0);}
int NITMOD_TCPRecv(nitmodSocket_t s,void *p,int n){return trap_NITMOD_NxACTransport(NXHOST_RECV,(int)s,p,n,0);}
#elif defined(Q3_VM)
int NITMOD_TCPInit(void){return 0;}
void NITMOD_TCPShutdown(void){}
void NITMOD_TCPClose(nitmodSocket_t *s){*s=NITMOD_SOCKET_INVALID;}
nitmodSocket_t NITMOD_TCPListen(const char *a,int b,int *c){(void)a;(void)b;(void)c;return NITMOD_SOCKET_INVALID;}
nitmodSocket_t NITMOD_TCPConnect(const char *a,int b,const char *c,int *d){(void)a;(void)b;(void)c;(void)d;return NITMOD_SOCKET_INVALID;}
int NITMOD_TCPConnected(nitmodSocket_t s){(void)s;return -1;}
nitmodSocket_t NITMOD_TCPAccept(nitmodSocket_t s,char ip[16],int *p){(void)s;(void)ip;(void)p;return NITMOD_SOCKET_INVALID;}
int NITMOD_TCPSend(nitmodSocket_t s,const void *p,int n){(void)s;(void)p;(void)n;return -1;}
int NITMOD_TCPRecv(nitmodSocket_t s,void *p,int n){(void)s;(void)p;(void)n;return -1;}
int NITMOD_TCPLocalPort(nitmodSocket_t s){(void)s;return 0;}
#else
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
typedef int nxSocklen_t;
#define NX_CLOSE closesocket
#define NX_ERROR() WSAGetLastError()
#define NX_WOULDBLOCK WSAEWOULDBLOCK
#define NX_PROGRESS WSAEINPROGRESS
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
typedef socklen_t nxSocklen_t;
#define NX_CLOSE close
#define NX_ERROR() errno
#define NX_WOULDBLOCK EWOULDBLOCK
#define NX_PROGRESS EINPROGRESS
#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif
#endif
static int initialized;
int NITMOD_TCPInit(void){
#ifdef _WIN32
    WSADATA data;if(!initialized && WSAStartup(MAKEWORD(2,2),&data))return 0;
#endif
    ++initialized;return 1;
}
void NITMOD_TCPShutdown(void){
#ifdef _WIN32
    if(initialized==1)WSACleanup();
#endif
    if(initialized>0)--initialized;
}
void NITMOD_TCPClose(nitmodSocket_t *s){if(*s!=NITMOD_SOCKET_INVALID)NX_CLOSE(*s);*s=NITMOD_SOCKET_INVALID;}
static int Nonblocking(nitmodSocket_t s){
#if defined(SO_NOSIGPIPE) && !defined(_WIN32)
    int one=1;if(setsockopt(s,SOL_SOCKET,SO_NOSIGPIPE,&one,sizeof(one)))return 0;
#endif
#ifdef _WIN32
    u_long one=1;return ioctlsocket(s,FIONBIO,&one)==0;
#else
    int flags=fcntl(s,F_GETFL,0);return flags>=0 && fcntl(s,F_SETFL,flags|O_NONBLOCK)==0;
#endif
}
static int Address(struct sockaddr_in *address,const char *ip,int port,int local){
    memset(address,0,sizeof(*address));address->sin_family=AF_INET;address->sin_port=htons((unsigned short)port);
    if(port<0 || port>65535)return 0;
    if(ip && !strcmp(ip,"localhost")){address->sin_addr.s_addr=htonl(INADDR_LOOPBACK);return 1;}
    if(!ip || !ip[0]){address->sin_addr.s_addr=htonl(local?INADDR_ANY:INADDR_LOOPBACK);return 1;}
    /* cl_currentServerIP is already resolved by the engine: no blocking DNS. */
    return inet_pton(AF_INET,ip,&address->sin_addr)==1;
}
static int LocalPort(nitmodSocket_t s,int *port){struct sockaddr_in a;nxSocklen_t n=sizeof(a);if(getsockname(s,(struct sockaddr *)&a,&n))return 0;*port=ntohs(a.sin_port);return 1;}
int NITMOD_TCPLocalPort(nitmodSocket_t s){int p=0;return LocalPort(s,&p)?p:0;}
nitmodSocket_t NITMOD_TCPListen(const char *ip,int port,int *actual){
    struct sockaddr_in a;nitmodSocket_t s;int one=1;
    if(!initialized || !Address(&a,ip,port,1))return NITMOD_SOCKET_INVALID;
    s=(nitmodSocket_t)socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);if(s==NITMOD_SOCKET_INVALID)return s;
#ifndef _WIN32
    setsockopt(s,SOL_SOCKET,SO_REUSEADDR,(const char *)&one,sizeof(one));
#else
    /* Prevent a second process hijacking a live Windows listener. */
    setsockopt(s,SOL_SOCKET,SO_EXCLUSIVEADDRUSE,(const char *)&one,sizeof(one));
#endif
    if(!Nonblocking(s) || bind(s,(struct sockaddr *)&a,sizeof(a)) || listen(s,64) || !LocalPort(s,actual)){NITMOD_TCPClose(&s);return NITMOD_SOCKET_INVALID;}return s;
}
nitmodSocket_t NITMOD_TCPConnect(const char *ip,int port,const char *bindIp,int *localPort){
    struct sockaddr_in a,b;nitmodSocket_t s;int error;
    if(!initialized || !Address(&a,ip,port,0) || port==0 || !Address(&b,bindIp,0,1))return NITMOD_SOCKET_INVALID;
    s=(nitmodSocket_t)socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);if(s==NITMOD_SOCKET_INVALID)return s;
    if(!Nonblocking(s) || bind(s,(struct sockaddr *)&b,sizeof(b)) || !LocalPort(s,localPort)){NITMOD_TCPClose(&s);return NITMOD_SOCKET_INVALID;}
    if(connect(s,(struct sockaddr *)&a,sizeof(a))){error=NX_ERROR();if(error!=NX_WOULDBLOCK && error!=NX_PROGRESS){NITMOD_TCPClose(&s);return NITMOD_SOCKET_INVALID;}}return s;
}
int NITMOD_TCPConnected(nitmodSocket_t s){
    fd_set wr,ex;struct timeval timeout={0,0};int error=0,result;nxSocklen_t n=sizeof(error);
    if(s==NITMOD_SOCKET_INVALID)return -1;
#ifndef _WIN32
    if(s<0 || s>=FD_SETSIZE)return -1;
#endif
    FD_ZERO(&wr);FD_ZERO(&ex);FD_SET(s,&wr);FD_SET(s,&ex);result=select((int)s+1,NULL,&wr,&ex,&timeout);
    if(result<0){
#ifndef _WIN32
        if(errno==EINTR)return 0;
#endif
        return -1;}if(!result)return 0;
    if(getsockopt(s,SOL_SOCKET,SO_ERROR,(char *)&error,&n) || error)return -1;return FD_ISSET(s,&wr)?1:-1;
}
nitmodSocket_t NITMOD_TCPAccept(nitmodSocket_t listener,char ip[16],int *port){
    struct sockaddr_in a;nxSocklen_t n=sizeof(a);nitmodSocket_t s=(nitmodSocket_t)accept(listener,(struct sockaddr *)&a,&n);
    if(s==NITMOD_SOCKET_INVALID)return s;
    if(!Nonblocking(s) || !inet_ntop(AF_INET,&a.sin_addr,ip,16)){NITMOD_TCPClose(&s);return NITMOD_SOCKET_INVALID;}*port=ntohs(a.sin_port);return s;
}
int NITMOD_TCPSend(nitmodSocket_t s,const void *data,int length){
    int n,error;if(length<=0)return 0;
#ifdef _WIN32
    n=send(s,(const char *)data,length,0);
#else
    n=(int)send(s,data,(size_t)length,MSG_NOSIGNAL);
#endif
    if(n>=0)return n;error=NX_ERROR();
#ifndef _WIN32
    if(error==EAGAIN || error==EINTR)return 0;
#endif
    return error==NX_WOULDBLOCK?0:-1;
}
int NITMOD_TCPRecv(nitmodSocket_t s,void *data,int capacity){
    int n,error;if(capacity<=0)return -1;n=(int)recv(s,(char *)data,capacity,0);if(n>0)return n;if(!n)return -2;error=NX_ERROR();
#ifndef _WIN32
    if(error==EAGAIN || error==EINTR)return 0;
#endif
    return error==NX_WOULDBLOCK?0:-1;
}
#endif
int NITMOD_NxACParseHeader(const char *text,int length,int *size,char ext[4],char md5[33]) {
    const char *p=text,*end=text+length,*mark;int n=0,i;const char *prefix="ift \\fs\\";
    if(length<0 || length>127)return -1;
    for(i=0;prefix[i];++i){if(p==end)return 0;if(*p++!=prefix[i])return -1;}
    mark=p;while(p<end && *p>='0' && *p<='9'){if(n>NITMOD_NXAC_MAX_FILE/10)return -1;n=n*10+(*p++-'0');}
    if(p==end)return 0;if(p==mark || n<4 || n>NITMOD_NXAC_MAX_FILE)return -1;
    prefix="\\ext\\";for(i=0;prefix[i];++i){if(p==end)return 0;if(*p++!=prefix[i])return -1;}
    if(end-p<3)return 0;if(strncmp(p,"jpg",3) && strncmp(p,"png",3))return -1;memcpy(ext,p,3);ext[3]=0;p+=3;
    prefix="\\csm\\";for(i=0;prefix[i];++i){if(p==end)return 0;if(*p++!=prefix[i])return -1;}
    for(i=0;i<32;++i){char c;if(p==end)return 0;c=*p++;if(c>='A' && c<='F')c+=(char)('a'-'A');if(!((c>='0' && c<='9')||(c>='a' && c<='f')))return -1;md5[i]=c;}
    if(p==end)return 0;if(*p++!='\\' || p!=end)return -1;md5[32]=0;*size=n;return 1;
}
