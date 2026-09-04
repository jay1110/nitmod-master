#include "ui_local.h"
#include <limits.h>

static int searchReplies, searchLastTime;

static qboolean UI_StatusHasPlayer(const serverStatusInfo_t *info, const char *needle) {
    int row;
    for(row=0; row<info->numLines; ++row) {
        char name[MAX_NAME_LENGTH+2], *p;
        /* Only numbered player rows, never the score/ping/name header. */
        if(info->lines[row][0][0] < '0' || info->lines[row][0][0] > '9' || !info->lines[row][2][0]) continue;
        Q_strncpyz(name,info->lines[row][3],sizeof(name)); Q_CleanStr(name);
        for(p=name; *p; ++p) if(!Q_stricmpn(p,needle,strlen(needle))) return qtrue;
    }
    return qfalse;
}

static void UI_SearchProgress(qboolean done) {
    int row = uiInfo.numFoundPlayerServers-1;
    if(done) Com_sprintf(uiInfo.foundPlayerServerNames[row],MAX_ADDRESSLENGTH,
        "%d server%s found with player %s",row,row==1 ? "" : "s",uiInfo.findPlayerName);
    else Com_sprintf(uiInfo.foundPlayerServerNames[row],MAX_ADDRESSLENGTH,
        "searching %d/%d...",uiInfo.pendingServerStatus.num,searchReplies);
    uiInfo.foundPlayerServerAddresses[row][0] = 0;
}

/* Original request-slot pipeline, separated from status-panel presentation. */
void UI_BuildFindPlayerList(qboolean force) {
    serverStatusInfo_t info;
    char serverInfo[MAX_STRING_CHARS];
    int now = uiInfo.uiDC.realTime, i, j, total, active = 0;
    int timeout = ui_serverStatusTimeOut.integer;
    if(timeout < 0) timeout = 0;
    if(force) {
        trap_LAN_ServerStatus(NULL,NULL,0);
        memset(&uiInfo.pendingServerStatus,0,sizeof(uiInfo.pendingServerStatus));
        memset(uiInfo.foundPlayerServerAddresses,0,sizeof(uiInfo.foundPlayerServerAddresses));
        memset(uiInfo.foundPlayerServerNames,0,sizeof(uiInfo.foundPlayerServerNames));
        uiInfo.numFoundPlayerServers = 0; uiInfo.currentFoundPlayerServer = 0;
        uiInfo.nextFindPlayerRefresh = 0; searchReplies = 0;
        trap_Cvar_VariableStringBuffer("ui_findPlayer",uiInfo.findPlayerName,sizeof(uiInfo.findPlayerName));
        Q_CleanStr(uiInfo.findPlayerName);
        if(!uiInfo.findPlayerName[0]) return;
        i = timeout/2-10; if(i<50) i=50;
        trap_Cvar_Set("cl_serverStatusResendTime",va("%d",i));
        uiInfo.numFoundPlayerServers = 1;
    } else {
        if(!uiInfo.nextFindPlayerRefresh) return;
        if(now >= searchLastTime && now < uiInfo.nextFindPlayerRefresh) return;
        if(now < searchLastTime) for(i=0;i<MAX_SERVERSTATUSREQUESTS;++i)
            uiInfo.pendingServerStatus.server[i].startTime = now;
        if(uiInfo.numFoundPlayerServers < 1 || uiInfo.numFoundPlayerServers > MAX_FOUNDPLAYER_SERVERS) {
            trap_LAN_ServerStatus(NULL,NULL,0); uiInfo.nextFindPlayerRefresh=0; return;
        }
    }
    searchLastTime = now;
    total = uiInfo.serverStatus.numDisplayServers;
    if(total < 0 || total > MAX_DISPLAY_SERVERS) total=0;
    for(i=0;i<MAX_SERVERSTATUSREQUESTS;++i) {
        pendingServer_t *slot = &uiInfo.pendingServerStatus.server[i];
        if(slot->valid) {
            if(UI_QueryServerStatus(slot->adrstr,&info)) {
                ++searchReplies;
                if(UI_StatusHasPlayer(&info,uiInfo.findPlayerName)) {
                    int count = uiInfo.numFoundPlayerServers-1;
                    for(j=0;j<count;++j) if(!Q_stricmp(uiInfo.foundPlayerServerAddresses[j],slot->adrstr)) break;
                    if(j==count && count < MAX_FOUNDPLAYER_SERVERS-1) {
                        Q_strncpyz(uiInfo.foundPlayerServerAddresses[count],slot->adrstr,MAX_ADDRESSLENGTH);
                        Q_strncpyz(uiInfo.foundPlayerServerNames[count],slot->name,MAX_ADDRESSLENGTH);
                        ++uiInfo.numFoundPlayerServers;
                    }
                }
                UI_QueryServerStatus(slot->adrstr,NULL); slot->valid=qfalse;
            } else if((double)now-slot->startTime > timeout) {
                UI_QueryServerStatus(slot->adrstr,NULL); slot->valid=qfalse;
            }
        }
        if(uiInfo.numFoundPlayerServers == MAX_FOUNDPLAYER_SERVERS) {
            if(slot->valid) UI_QueryServerStatus(slot->adrstr,NULL);
            slot->valid=qfalse; continue;
        }
        if(!slot->valid && uiInfo.pendingServerStatus.num >= 0 && uiInfo.pendingServerStatus.num < total) {
            int server = uiInfo.serverStatus.displayServers[uiInfo.pendingServerStatus.num++];
            trap_LAN_GetServerAddressString(ui_netSource.integer,server,slot->adrstr,sizeof(slot->adrstr));
            trap_LAN_GetServerInfo(ui_netSource.integer,server,serverInfo,sizeof(serverInfo));
            Q_strncpyz(slot->name,Info_ValueForKey(serverInfo,"hostname"),sizeof(slot->name));
            slot->startTime=now; slot->valid=slot->adrstr[0] ? qtrue : qfalse;
        }
        if(slot->valid) active=1;
    }
    if(uiInfo.numFoundPlayerServers == MAX_FOUNDPLAYER_SERVERS) {
        for(i=0;i<MAX_SERVERSTATUSREQUESTS;++i) if(uiInfo.pendingServerStatus.server[i].valid) {
            UI_QueryServerStatus(uiInfo.pendingServerStatus.server[i].adrstr,NULL);
            uiInfo.pendingServerStatus.server[i].valid=qfalse;
        }
        active=0; uiInfo.pendingServerStatus.num=total;
    }
    if(uiInfo.pendingServerStatus.num < total) active=1;
    UI_SearchProgress(!active);
    if(active) uiInfo.nextFindPlayerRefresh = now > INT_MAX-25 ? INT_MAX : now+25;
    else {
        uiInfo.nextFindPlayerRefresh=0;
        if(uiInfo.currentFoundPlayerServer < 0 || uiInfo.currentFoundPlayerServer >= uiInfo.numFoundPlayerServers)
            uiInfo.currentFoundPlayerServer=0;
        UI_FeederSelection(FEEDER_FINDPLAYER,uiInfo.currentFoundPlayerServer);
    }
}
