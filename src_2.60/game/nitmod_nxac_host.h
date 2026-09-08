#ifndef NITMOD_NXAC_HOST_H
#define NITMOD_NXAC_HOST_H
/* Negotiated engine extension trap_NitmodNxACTransport1. No fixed trap ID.
 * Host determines caller VM and binds endpoints to its real game session. */
enum { NXHOST_CAPS, NXHOST_LISTEN, NXHOST_CONNECT, NXHOST_INFO, NXHOST_ACCEPT,
       NXHOST_SEND, NXHOST_RECV, NXHOST_CLOSE, NXHOST_RESET };
#define NXHOST_CLIENT_RELAY 1
#define NXHOST_LOCAL_STREAM 2
#define NXHOST_SERVER_EXTERNAL 4
typedef struct { int localPort,peerPort; char peerIp[16]; } nitmodNxACHostInfo_t;
typedef char nitmodNxACInfoSizeCheck[sizeof(nitmodNxACHostInfo_t)==24?1:-1];
int trap_NITMOD_NxACTransport(int operation,int handle,void *buffer,int length,int value);
#endif
