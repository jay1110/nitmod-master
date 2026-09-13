#include "ui_local.h"
#include <limits.h>

static int searchReplies, searchLastTime;
/* Original UI_BuildFindPlayerList accepts while total rows < 0xf.
 * One row is reserved for progress, leaving fourteen server matches. */
#define NITMOD_FINDPLAYER_ROWS 15

static int UI_StatusPlayerMatches(const serverStatusInfo_t *info, const char *needle) {
    int row, matches=0;
    for(row=0; row<info->numLines; ++row) {
        char name[MAX_NAME_LENGTH+2], *p;
        /* Original 0x19ea3 checks only the populated ping column; this
         * intentionally includes the status header when its name matches. */
        if(!info->lines[row][2] || !info->lines[row][2][0]) continue;
        Q_strncpyz(name,info->lines[row][3],sizeof(name)); Q_CleanStr(name);
        for(p=name; *p; ++p) if(!Q_stricmpn(p,needle,strlen(needle))) { ++matches; break; }
    }
    return matches;
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
    int now = uiInfo.uiDC.realTime, i, total, active = 0;
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
                {
                    int matches=UI_StatusPlayerMatches(&info,uiInfo.findPlayerName);
                    /* Original 0x1a128-0x1a1c6 appends once per matching
                     * player row, including repeated server addresses. */
                    while(matches > 0 && uiInfo.numFoundPlayerServers < NITMOD_FINDPLAYER_ROWS) {
                        int count=uiInfo.numFoundPlayerServers-1;
                        --matches;
                        Q_strncpyz(uiInfo.foundPlayerServerAddresses[count],slot->adrstr,MAX_ADDRESSLENGTH);
                        Q_strncpyz(uiInfo.foundPlayerServerNames[count],slot->name,MAX_ADDRESSLENGTH);
                        ++uiInfo.numFoundPlayerServers;
                    }
                    /* Original 0x1a133-0x1a151 stops assigning new servers
                     * only when another match exceeds capacity. Existing
                     * requests still finish or expire normally. */
                    if(matches > 0) uiInfo.pendingServerStatus.num=total;
                }
                UI_QueryServerStatus(slot->adrstr,NULL); slot->valid=qfalse;
            } else if((double)now-slot->startTime > timeout) {
                UI_QueryServerStatus(slot->adrstr,NULL); slot->valid=qfalse;
            }
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
