static const char *searchNeedle;
static int searchMode, searchPolls, searchCancels, searchStarts, searchLinkWrites, searchResend;
static int QDECL SearchSyscall(int command, ...) {
    va_list args;
    int result=0;
    va_start(args,command);
    if(command == UI_CVAR_VARIABLESTRINGBUFFER) {
        char *out; int size;
        if(strcmp(va_arg(args,const char *),"ui_findPlayer")) exit(2);
        out=va_arg(args,char *); size=va_arg(args,int); Q_strncpyz(out,searchNeedle,size);
    } else if(command == UI_CVAR_SET) {
        const char *key=va_arg(args,const char *), *value=va_arg(args,const char *);
        if(!strcmp(key,"cl_serverStatusResendTime")) searchResend=atoi(value);
        else if(!strcmp(key,"ui_URL") || !strcmp(key,"ui_modURL")) ++searchLinkWrites;
        else exit(2);
    } else if(command == UI_LAN_GETSERVERADDRESSSTRING || command == UI_LAN_GETSERVERINFO) {
        int index,size; char *out;
        if(va_arg(args,int) != 0) exit(2);
        index=va_arg(args,int); out=va_arg(args,char *); size=va_arg(args,int);
        if(index < 0 || index >= 40) exit(2);
        if(command == UI_LAN_GETSERVERADDRESSSTRING) { Com_sprintf(out,size,"s%d",searchMode==2 ? 0 : index); ++searchStarts; }
        else Com_sprintf(out,size,"\\hostname\\Server%d",index);
    } else if(command == UI_LAN_SERVERSTATUS) {
        const char *address=va_arg(args,const char *);
        char *out=va_arg(args,char *); int size=va_arg(args,int);
        if(!out) { if(size) exit(2); ++searchCancels; }
        else {
            if(!address || address[0]!='s' || size!=MAX_SERVERSTATUS_TEXT) exit(2);
            ++searchPolls;
            if(searchMode!=1) {
                Q_strncpyz(out,"\\sv_hostname\\Server\\url\\https://search\\\\1 20 ^1Alice\\2 30 ALICE",size);
                result=1;
            }
        }
    } else if(command == UI_GETCLIENTSTATE) {
        uiClientState_t *state=va_arg(args,uiClientState_t *);
        memset(state,0,sizeof(*state)); state->connState=CA_CONNECTED;
    } else { fprintf(stderr,"unexpected search syscall %d\n",command); exit(2); }
    va_end(args); return result;
}
static int CheckPlayerSearch(void) {
    static uiInfo_t saved;
    vmCvar_t savedTimeout=ui_serverStatusTimeOut, savedSource=ui_netSource;
    int oldMenus=menuCount, errors=0, mode, count, tick, i;
    saved=uiInfo; menuCount=0; dllEntry(SearchSyscall);
    ui_netSource.integer=0; ui_serverStatusTimeOut.integer=100;
    for(mode=0;mode<4;++mode) for(count=0;count<=40;count+=5) {
        memset(&uiInfo,0,sizeof(uiInfo));
        uiInfo.serverStatus.numDisplayServers=count;
        for(i=0;i<count;++i) uiInfo.serverStatus.displayServers[i]=i;
        searchMode=mode; searchNeedle=mode==3 ? "name" : "^2aLiCe";
        searchPolls=searchStarts=searchCancels=searchLinkWrites=searchResend=0;
        uiInfo.uiDC.realTime=1000; UI_BuildFindPlayerList(qtrue);
        if(searchLinkWrites || searchResend!=50) ++errors;
        for(tick=1;tick<200 && uiInfo.nextFindPlayerRefresh;++tick) {
            int previous=searchPolls;
            uiInfo.uiDC.realTime += 10;
            if(uiInfo.uiDC.realTime < uiInfo.nextFindPlayerRefresh) {
                UI_BuildFindPlayerList(qfalse); if(searchPolls!=previous) ++errors;
            } else UI_BuildFindPlayerList(qfalse);
            if(uiInfo.nextFindPlayerRefresh && searchLinkWrites) ++errors;
        }
        i=mode==1 || mode==3 ? 0 : mode==2 ? !!count : count<15 ? count : 15;
        if(uiInfo.nextFindPlayerRefresh || uiInfo.numFoundPlayerServers!=i+1 ||
           uiInfo.foundPlayerServerAddresses[i][0] || searchLinkWrites!=(i ? 2 : 0)) ++errors;
        for(i=0;i<MAX_SERVERSTATUSREQUESTS;++i) if(uiInfo.pendingServerStatus.server[i].valid) ++errors;
    }
    memset(&uiInfo,0,sizeof(uiInfo)); uiInfo.serverStatus.numDisplayServers=1;
    searchMode=1; searchNeedle="Alice"; uiInfo.uiDC.realTime=2000;
    UI_BuildFindPlayerList(qtrue);
    uiInfo.uiDC.realTime=500; UI_BuildFindPlayerList(qfalse);
    if(!uiInfo.pendingServerStatus.server[0].valid || uiInfo.pendingServerStatus.server[0].startTime!=500) ++errors;
    searchNeedle="^1"; i=searchCancels; UI_BuildFindPlayerList(qtrue);
    if(searchCancels!=i+1 || uiInfo.nextFindPlayerRefresh || uiInfo.numFoundPlayerServers) ++errors;
    for(i=0;i<MAX_SERVERSTATUSREQUESTS;++i) if(uiInfo.pendingServerStatus.server[i].valid) ++errors;
    uiInfo=saved; menuCount=oldMenus; ui_serverStatusTimeOut=savedTimeout; ui_netSource=savedSource;
    if(errors) fprintf(stderr,"%d player search failures\n",errors);
    return errors;
}
