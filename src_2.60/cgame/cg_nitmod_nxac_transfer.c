#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "cg_nitmod_nxac.h"
#include "cg_nitmod_nxac_transfer.h"
#include "../game/nitmod_nxac_tcp.h"
#include "../game/nitmod_md5.h"
#include <stdlib.h>

enum { NX_IDLE, NX_CAPTURE, NX_CONNECT, NX_HEARTBEAT, NX_METADATA, NX_APPROVAL, NX_SEND, NX_CONFIRM, NX_CLOSE };
static struct {
    int state,deadline,start,progress,port,length,offset,textLength,textOffset;
    nitmodSocket_t socket;
    char path[MAX_QPATH],text[128];
    unsigned char *bytes;
    qboolean initialized;
} nxTransfer={0,0,0,0,0,0,0,0,0,NITMOD_SOCKET_INVALID};
static unsigned int nxSequence;
static int Elapsed(int now,int before){return (int)((unsigned int)now-(unsigned int)before);}
static void Finish(void) {
    NITMOD_TCPClose(&nxTransfer.socket);
    if(nxTransfer.path[0])trap_FS_Delete(nxTransfer.path);
    if(nxTransfer.bytes)free(nxTransfer.bytes);
    if(nxTransfer.initialized)NITMOD_TCPShutdown();
    memset(&nxTransfer,0,sizeof(nxTransfer));nxTransfer.socket=NITMOD_SOCKET_INVALID;
    trap_Cvar_Set("cnport","0");
}
void CG_NITMOD_NxACTransferReset(void){Finish();}
static void Failure(const char *reason,int flag) {
    CG_Printf("^1NxAC screenshot: %s\n",reason);
    CG_NITMOD_NxACTransferFailure(flag);Finish();
}
qboolean CG_NITMOD_NxACTransferCommand(const char *command) {
    int now=trap_Milliseconds();
    if(strcmp(command,"getss") && strcmp(command,"fta") && strcmp(command,"ftc"))return qfalse;
    if(!NITMOD_UsesNitmodHud() || cg.demoPlayback)return qtrue;
    if(!strcmp(command,"getss")) {
        Finish();
        trap_Cvar_Register(NULL,"cnport","0",CVAR_USERINFO|CVAR_ROM|CVAR_NORESTART);
        if(!NITMOD_TCPInit()) {
            Failure("raw TCP is unavailable in this host; the browser requires an NxAC WebSocket-to-TCP adapter",0x80);return qtrue;
        }
        nxTransfer.initialized=qtrue;nxTransfer.state=NX_CAPTURE;
        nxTransfer.deadline=(int)((unsigned int)cg.time+100U);nxTransfer.start=nxTransfer.progress=now;
    } else if(!strcmp(command,"fta") && nxTransfer.state==NX_APPROVAL) {
        nxTransfer.state=NX_SEND;nxTransfer.deadline=(int)((unsigned int)cg.time+100U);nxTransfer.progress=now;
    } else if(!strcmp(command,"ftc") && nxTransfer.state==NX_CONFIRM) {
        /* Original state7 sends fl only after the server's ftc acknowledgement. */
        nxTransfer.state=NX_CLOSE;nxTransfer.textLength=2;nxTransfer.textOffset=0;
        memcpy(nxTransfer.text,"fl",3);nxTransfer.deadline=(int)((unsigned int)cg.time+100U);nxTransfer.progress=now;
    }
    return qtrue;
}
static qboolean Capture(void) {
    int i,length;fileHandle_t file=0;char basename[48];
    for(i=0;i<100;++i) {
        Com_sprintf(basename,sizeof(basename),"nxac_%08x_%08x",(unsigned int)trap_Milliseconds(),++nxSequence);
        Com_sprintf(nxTransfer.path,sizeof(nxTransfer.path),"screenshots/%s.jpg",basename);
        length=trap_FS_FOpenFile(nxTransfer.path,&file,FS_READ);if(file)trap_FS_FCloseFile(file);
        if(length<0 && !file)break;file=0;
    }
    if(i==100){nxTransfer.path[0]=0;Failure("cannot allocate a new screenshot filename",0x40);return qfalse;}
    /* Uses the actual renderer command. Original quality argument is stored but
     * not applied by nitrox_Screenshot; do not invent a persistent cvar override. */
    trap_SendConsoleCommand(va("screenshotJPEG %s\n",basename));
    nxTransfer.state=NX_CONNECT;nxTransfer.deadline=(int)((unsigned int)cg.time+500U);return qtrue;
}
static qboolean ConnectAndRead(void) {
    char server[128],bindIp[64],number[32],*colon;fileHandle_t file=0;int length,result;
    if(nxTransfer.socket==NITMOD_SOCKET_INVALID) {
        trap_Cvar_VariableStringBuffer("cl_currentServerIP",server,sizeof(server));
        colon=strchr(server,':');if(colon)*colon=0;
        trap_Cvar_VariableStringBuffer("net_ip",bindIp,sizeof(bindIp));
        Q_strncpyz(number,Info_ValueForKey(CG_ConfigString(CS_SERVERINFO),"nport"),sizeof(number));
        nxTransfer.socket=NITMOD_TCPConnect(server,atoi(number),bindIp,&nxTransfer.port);
        if(nxTransfer.socket==NITMOD_SOCKET_INVALID){Failure("connection to the server's nport failed",0x80);return qfalse;}
    }
    result=NITMOD_TCPConnected(nxTransfer.socket);if(result<0){Failure("TCP connection failed",0x80);return qfalse;}if(!result)return qfalse;
    nxTransfer.port=NITMOD_TCPLocalPort(nxTransfer.socket);
    if(nxTransfer.port<1 || nxTransfer.port>65535){Failure("host did not confirm the TCP source port",0x80);return qfalse;}
    Com_sprintf(number,sizeof(number),"%d",nxTransfer.port);trap_Cvar_Set("cnport",number);
    length=trap_FS_FOpenFile(nxTransfer.path,&file,FS_READ);
    if(length<0 || !file){if(file)trap_FS_FCloseFile(file);return qfalse;}
    if(length<4 || length>NITMOD_NXAC_MAX_FILE){trap_FS_FCloseFile(file);Failure("captured JPEG is empty or exceeds the 8 MiB limit",0x40);return qfalse;}
    nxTransfer.bytes=(unsigned char *)malloc(length);if(!nxTransfer.bytes){trap_FS_FCloseFile(file);Failure("screenshot allocation failed",0x40);return qfalse;}
    /* FS_Read has no result in this module ABI; the exact reopened length and
     * JPEG markers guard against a missing or incomplete renderer file. */
    memset(nxTransfer.bytes,0,length);trap_FS_Read(nxTransfer.bytes,length,file);trap_FS_FCloseFile(file);
    if(nxTransfer.bytes[0]!=0xff || nxTransfer.bytes[1]!=0xd8 || nxTransfer.bytes[length-2]!=0xff || nxTransfer.bytes[length-1]!=0xd9) {
        free(nxTransfer.bytes);nxTransfer.bytes=NULL;return qfalse;
    }
    nxTransfer.length=length;Com_sprintf(nxTransfer.text,sizeof(nxTransfer.text),"hb %d",nxTransfer.port);
    nxTransfer.textLength=(int)strlen(nxTransfer.text);nxTransfer.textOffset=0;nxTransfer.state=NX_HEARTBEAT;return qtrue;
}
static int SendText(void) {
    int n=NITMOD_TCPSend(nxTransfer.socket,nxTransfer.text+nxTransfer.textOffset,nxTransfer.textLength-nxTransfer.textOffset);
    if(n<0){Failure("TCP control send failed",0x80);return -1;}
    if(n>0){nxTransfer.textOffset+=n;nxTransfer.progress=trap_Milliseconds();}
    return nxTransfer.textOffset==nxTransfer.textLength;
}
void CG_NITMOD_NxACTransferFrame(void) {
    int now,n;char md5[33];
    if(nxTransfer.state==NX_IDLE)return;
    if(!NITMOD_UsesNitmodHud() || cg.demoPlayback){Finish();return;}
    now=trap_Milliseconds();
    if(Elapsed(now,nxTransfer.start)>60000 || Elapsed(now,nxTransfer.progress)>10000){Failure("transfer timed out without confirmed server storage",0x80);return;}
    if(nxTransfer.deadline>=cg.time)return;
    switch(nxTransfer.state) {
    case NX_CAPTURE:Capture();break;
    case NX_CONNECT:ConnectAndRead();break;
    case NX_HEARTBEAT:
        if(SendText()==1){
            NITMOD_MD5Hex(nxTransfer.bytes,nxTransfer.length,md5);
            Com_sprintf(nxTransfer.text,sizeof(nxTransfer.text),"ift \\fs\\%d\\ext\\jpg\\csm\\%s\\",nxTransfer.length,md5);
            nxTransfer.textLength=(int)strlen(nxTransfer.text);nxTransfer.textOffset=0;nxTransfer.state=NX_METADATA;
            nxTransfer.deadline=(int)((unsigned int)cg.time+500U);
        }break;
    case NX_METADATA:if(SendText()==1)nxTransfer.state=NX_APPROVAL;break;
    case NX_SEND:
        n=nxTransfer.length-nxTransfer.offset;if(n>NITMOD_NXAC_CHUNK)n=NITMOD_NXAC_CHUNK;
        n=NITMOD_TCPSend(nxTransfer.socket,nxTransfer.bytes+nxTransfer.offset,n);
        if(n<0){Failure("TCP screenshot send failed",0x80);return;}
        if(n>0){nxTransfer.offset+=n;nxTransfer.progress=now;}
        if(nxTransfer.offset==nxTransfer.length)nxTransfer.state=NX_CONFIRM;
        nxTransfer.deadline=(int)((unsigned int)cg.time+50U);break;
    case NX_CLOSE:
        /* Original may immediately ban/disconnect after ftc; that cannot undo
         * the acknowledgement already received through the game channel. */
        NITMOD_TCPSend(nxTransfer.socket,"fl",2);
        CG_Printf("NxAC screenshot: server confirmed receipt.\n");Finish();break;
    default:break;
    }
}
