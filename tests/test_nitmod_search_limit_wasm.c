#include "ui_local.h"
#include <assert.h>
#include <stdio.h>

uiInfo_t uiInfo;
vmCvar_t ui_serverStatusTimeOut, ui_netSource;
void QDECL Com_Printf(const char *fmt, ...) { (void)fmt; }
void QDECL Com_Error(int code, const char *fmt, ...) { (void)code; (void)fmt; assert(0); }
void trap_Cvar_VariableStringBuffer(const char *name,char *out,int size) {
    Q_strncpyz(out,"Alice",size);
}
void trap_Cvar_Set(const char *name,const char *value) { }
int trap_LAN_ServerStatus(const char *address,char *out,int size) { return 0; }
void trap_LAN_GetServerAddressString(int source,int n,char *out,int size) {
    Com_sprintf(out,size,"s%d",n);
}
void trap_LAN_GetServerInfo(int source,int n,char *out,int size) {
    Q_strncpyz(out,"\\hostname\\test",size);
}
int UI_QueryServerStatus(const char *address,serverStatusInfo_t *info) {
    if(!info) return 0;
    memset(info,0,sizeof(*info));
    info->numLines=1;
    info->lines[0][0]="0"; info->lines[0][1]="1";
    info->lines[0][2]="20"; info->lines[0][3]="^1Alice";
    return 1;
}
void UI_FeederSelection(float feeder,int index) { }
int main(void) {
    int total,i,tick;
    for(total=0;total<=40;++total) {
        memset(&uiInfo,0,sizeof(uiInfo));
        ui_serverStatusTimeOut.integer=100;
        uiInfo.serverStatus.numDisplayServers=total;
        for(i=0;i<total;++i) uiInfo.serverStatus.displayServers[i]=i;
        uiInfo.uiDC.realTime=1000;
        UI_BuildFindPlayerList(qtrue);
        for(tick=0;tick<100 && uiInfo.nextFindPlayerRefresh;++tick) {
            uiInfo.uiDC.realTime+=25;
            UI_BuildFindPlayerList(qfalse);
        }
        assert(!uiInfo.nextFindPlayerRefresh);
        assert(uiInfo.numFoundPlayerServers==(total<14?total:14)+1);
        assert(!uiInfo.foundPlayerServerAddresses[uiInfo.numFoundPlayerServers-1][0]);
        for(i=0;i<MAX_SERVERSTATUSREQUESTS;++i)
            assert(!uiInfo.pendingServerStatus.server[i].valid);
    }
    puts("Actual UI search: 41 server-count cases passed");
    return 0;
}
