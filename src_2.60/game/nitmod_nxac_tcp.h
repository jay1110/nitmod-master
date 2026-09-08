#ifndef NITMOD_NXAC_TCP_H
#define NITMOD_NXAC_TCP_H
#include <stdint.h>
typedef intptr_t nitmodSocket_t;
#define NITMOD_SOCKET_INVALID ((nitmodSocket_t)-1)
#define NITMOD_NXAC_MAX_FILE (8*1024*1024)
#define NITMOD_NXAC_CHUNK 16384
/* All operations are nonblocking. Recv: 0 would block, -1 error, -2 EOF.
 * Send: 0 would block, -1 error. Socket handles preserve Win64 SOCKET width. */
int NITMOD_TCPInit(void);
void NITMOD_TCPShutdown(void);
void NITMOD_TCPClose(nitmodSocket_t *s);
nitmodSocket_t NITMOD_TCPListen(const char *bindIp,int port,int *actualPort);
nitmodSocket_t NITMOD_TCPConnect(const char *ip,int port,const char *bindIp,int *localPort);
int NITMOD_TCPConnected(nitmodSocket_t s);
int NITMOD_TCPLocalPort(nitmodSocket_t s);
nitmodSocket_t NITMOD_TCPAccept(nitmodSocket_t listener,char ip[16],int *port);
int NITMOD_TCPSend(nitmodSocket_t s,const void *data,int length);
int NITMOD_TCPRecv(nitmodSocket_t s,void *data,int capacity);
/* Exact Original ift header; 1 complete, 0 incomplete, -1 invalid. */
int NITMOD_NxACParseHeader(const char *text,int length,int *size,char ext[4],char md5[33]);
#endif
