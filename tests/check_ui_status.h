static const char *statusResponse;
static int statusReady, statusCancels, statusSets;
static char statusUrl[1024], statusModUrl[1024];
static int QDECL StatusSyscall(int command, ...) {
    va_list args;
    int result = 0;
    va_start(args, command);
    if(command == UI_LAN_SERVERSTATUS) {
        const char *address = va_arg(args, const char *);
        char *buffer = va_arg(args, char *);
        int size = va_arg(args, int);
        if(strcmp(address,"server:27960")) exit(2);
        if(!buffer) { if(size) exit(2); ++statusCancels; }
        else { if(size != MAX_SERVERSTATUS_TEXT) exit(2); Q_strncpyz(buffer,statusResponse,size); result = statusReady; }
    } else if(command == UI_CVAR_SET) {
        const char *name = va_arg(args,const char *), *value = va_arg(args,const char *);
        if(!strcmp(name,"ui_URL")) Q_strncpyz(statusUrl,value,sizeof(statusUrl));
        else if(!strcmp(name,"ui_modURL")) Q_strncpyz(statusModUrl,value,sizeof(statusModUrl));
        else exit(2);
        ++statusSets;
    } else { fprintf(stderr,"unexpected status syscall %d\n",command); exit(2); }
    va_end(args); return result;
}
static int CheckServerStatus(void) {
    extern menuDef_t Menus[MAX_MENUS];
    static menuDef_t savedMenus[2];
    static itemDef_t links[2][2];
    static serverStatusInfo_t info;
    char text[MAX_SERVERSTATUS_TEXT];
    int errors = 0, i, row, col, oldMenus = menuCount;
    const char *sample = "\\sv_hostname\\Test\\url\\https://host\\\\1 2 ^1One\\3 4 Two";
    Q_strncpyz(info.text,sample,sizeof(info.text));
    UI_ParseServerStatus(&info,"server:27960");
    if(info.numLines != 7 || strcmp(info.lines[5][0],"0") || strcmp(info.lines[5][3],"^1One") ||
       strcmp(info.lines[6][1],"3") || strcmp(info.lines[6][2],"4") || strcmp(info.lines[6][3],"Two")) ++errors;
    /* Every truncation must leave only complete rows with terminated fields. */
    for(i = 0; i <= strlen(sample); ++i) {
        memset(&info,0xa5,sizeof(info)); memcpy(info.text,sample,i); info.text[i] = 0;
        UI_ParseServerStatus(&info,"server:27960");
        if(info.numLines < 1 || info.numLines > MAX_SERVERSTATUS_LINES) { ++errors; continue; }
        for(row = 0; row < info.numLines; ++row) for(col = 0; col < 4; ++col)
            if(!info.lines[row][col] || strlen(info.lines[row][col]) >= MAX_SERVERSTATUS_TEXT) ++errors;
    }
    strcpy(text,"\\k\\v\\");
    for(i=0;i<100;++i) Q_strcat(text,sizeof(text),"\\1 2 p");
    Q_strncpyz(info.text,text,sizeof(info.text)); UI_ParseServerStatus(&info,"s");
    if(info.numLines != MAX_CLIENTS+4 || strcmp(info.lines[info.numLines-1][0],"63")) ++errors;
    Q_strncpyz(info.text,"\\k\\v\\\\broken\\1 2 must-not-merge",sizeof(info.text));
    UI_ParseServerStatus(&info,"s"); if(info.numLines != 4) ++errors;
    text[0] = 0;
    for(i=0;i<140;++i) Q_strcat(text,sizeof(text),"\\a\\b");
    Q_strncpyz(info.text,text,sizeof(info.text)); UI_ParseServerStatus(&info,"s");
    if(info.numLines != MAX_SERVERSTATUS_LINES) ++errors;
    memset(info.text,'x',sizeof(info.text)); UI_ParseServerStatus(&info,"s");
    if(info.numLines != 3) ++errors;
    memcpy(savedMenus,Menus,sizeof(savedMenus)); memset(Menus,0,sizeof(savedMenus));
    memset(links,0,sizeof(links)); menuCount = 2;
    for(i=0;i<2;++i) {
        Menus[i].window.name = i ? "popupError" : "serverinfo_popmenu";
        Menus[i].itemCount = 2;
        for(col=0;col<2;++col) {
            Menus[i].items[col] = &links[i][col];
            links[i][col].window.name = col ? "modURL" : "serverURL";
            links[i][col].window.cinematic = -1;
            links[i][col].window.flags = WINDOW_VISIBLE;
        }
    }
    dllEntry(StatusSyscall); statusReady = 1; statusSets = statusCancels = 0;
    statusResponse = sample;
    if(!UI_GetServerStatusInfo("server:27960",&info) || strcmp(statusUrl,"https://host") || *statusModUrl ||
       strcmp(info.lines[0][0],"Name") || strcmp(info.lines[1][0],"Address")) ++errors;
    for(i=0;i<2;++i) if(!(links[i][0].window.flags & WINDOW_VISIBLE) || (links[i][1].window.flags & WINDOW_VISIBLE)) ++errors;
    statusResponse = "\\mod_url\\https://mod";
    if(!UI_GetServerStatusInfo("server:27960",&info) || *statusUrl || strcmp(statusModUrl,"https://mod")) ++errors;
    for(i=0;i<2;++i) if((links[i][0].window.flags & WINDOW_VISIBLE) || !(links[i][1].window.flags & WINDOW_VISIBLE)) ++errors;
    statusResponse = "\\sv_hostname\\Other";
    if(!UI_GetServerStatusInfo("server:27960",&info) || *statusUrl || *statusModUrl || statusSets != 6) ++errors;
    for(i=0;i<2;++i) for(col=0;col<2;++col) if(links[i][col].window.flags & WINDOW_VISIBLE) ++errors;
    statusReady = 0;
    if(UI_GetServerStatusInfo("server:27960",&info) || info.numLines || statusSets != 6) ++errors;
    if(UI_GetServerStatusInfo("server:27960",NULL) || statusCancels != 1) ++errors;
    memcpy(Menus,savedMenus,sizeof(savedMenus)); menuCount = oldMenus;
    if(errors) fprintf(stderr,"%d server status failures\n",errors);
    return errors;
}
