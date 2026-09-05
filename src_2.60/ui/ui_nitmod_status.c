#include "ui_local.h"

/* Original UI_GetServerStatusInfo: borrowed pointers remain inside info. */
void UI_ParseServerStatus(serverStatusInfo_t *info, const char *address) {
    char *p, *key, *value, *end, *players = NULL;
    int count = 0, used = 0;
    info->numLines = 0;
    memset(info->lines, 0, sizeof(info->lines));
    memset(info->pings, 0, sizeof(info->pings));
    info->text[sizeof(info->text)-1] = 0;
    Q_strncpyz(info->address, address ? address : "", sizeof(info->address));
    info->lines[0][0] = "Address"; info->lines[0][1] = info->lines[0][2] = "";
    info->lines[0][3] = info->address; info->numLines = 1;
    p = strchr(info->text, '\\');
    if(p) ++p;
    while(p && *p && info->numLines < MAX_SERVERSTATUS_LINES) {
        int row = info->numLines;
        if(*p == '\\') { players = p+1; break; }
        key = p; end = strchr(key, '\\');
        if(!end) break;
        *end = 0; value = end+1;
        end = strchr(value, '\\');
        if(end) { *end = 0; p = end+1; } else p = NULL;
        info->lines[row][0] = key;
        info->lines[row][1] = info->lines[row][2] = "";
        info->lines[row][3] = value; ++info->numLines;
    }
    if(info->numLines >= MAX_SERVERSTATUS_LINES-3) return;
    {
        int row = info->numLines++;
        info->lines[row][0] = info->lines[row][1] = info->lines[row][2] = info->lines[row][3] = "";
        row = info->numLines++;
        info->lines[row][0] = "num"; info->lines[row][1] = "score";
        info->lines[row][2] = "ping"; info->lines[row][3] = "name";
    }
    p = players;
    while(p && *p && count < MAX_CLIENTS && info->numLines < MAX_SERVERSTATUS_LINES) {
        char *score = p, *ping, *name;
        int row = info->numLines, length;
        /* Delimit the record BEFORE looking for its fields. */
        end = strchr(p, '\\');
        if(end) *end++ = 0;
        ping = strchr(score, ' '); if(!ping) break;
        *ping++ = 0;
        name = strchr(ping, ' '); if(!name) break;
        *name++ = 0;
        if(!*score || !*ping || !*name) break;
        length = count < 10 ? 2 : 3;
        if(length > (int)sizeof(info->pings)-used) break;
        Com_sprintf(info->pings+used, sizeof(info->pings)-used, "%d", count);
        info->lines[row][0] = info->pings+used;
        info->lines[row][1] = score; info->lines[row][2] = ping; info->lines[row][3] = name;
        used += length; ++count; ++info->numLines; p = end;
    }
}

static void UI_StatusLinks(serverStatusInfo_t *info) {
    static const char *keys[] = {"url", "mod_url"};
    static const char *cvars[] = {"ui_URL", "ui_modURL"};
    static const char *buttons[] = {"serverURL", "modURL"};
    menuDef_t *menus[2];
    int link, row, m;
    menus[0] = Menus_FindByName("serverinfo_popmenu");
    menus[1] = Menus_FindByName("popupError");
    for(link = 0; link < 2; ++link) {
        const char *value = "";
        for(row = 1; row < info->numLines; ++row)
            if(!info->lines[row][1][0] && !Q_stricmp(info->lines[row][0], keys[link]))
                value = info->lines[row][3];
        trap_Cvar_Set(cvars[link], value);
        for(m = 0; m < 2; ++m)
            if(menus[m]) Menu_ShowItemByName(menus[m], buttons[link], *value ? qtrue : qfalse);
    }
}

static void UI_SortServerStatusInfo(serverStatusInfo_t *info) {
    static const char *names[][2] = {
        {"sv_hostname","Name"}, {"Address",""}, {"gamename","Game name"},
        {"g_gametype","Game type"}, {"mapname","Map"}, {"version",""},
        {"protocol",""}, {"timelimit",""}, {"fraglimit",""}
    };
    int i, j, index = 0;
    for(i=0; i<sizeof(names)/sizeof(names[0]); ++i)
        for(j=index; j<info->numLines && index<info->numLines; ++j) {
            char *key, *value;
            if(info->lines[j][1][0] || Q_stricmp(info->lines[j][0],names[i][0])) continue;
            key = info->lines[index][0]; value = info->lines[index][3];
            info->lines[index][0] = *names[i][1] ? (char *)names[i][1] : info->lines[j][0];
            info->lines[index][3] = info->lines[j][3];
			if(!Q_stricmp(names[i][0], "g_gametype")) {
				int gametype;
				if(NITMOD_ParseProtocolInteger(info->lines[index][3], &gametype) &&
				   gametype >= 0 && gametype < GT_MAX_GAME_TYPE) {
					Com_sprintf(info->gameTypeName, sizeof(info->gameTypeName), "%s (%d)",
						BG_NitmodGametypeName(gametype, qfalse), gametype);
					info->lines[index][3] = info->gameTypeName;
				}
			}
            if(j != index) { info->lines[j][0] = key; info->lines[j][3] = value; }
            ++index;
        }
}

int UI_QueryServerStatus(const char *serverAddress, serverStatusInfo_t *info) {
    if(!info) { trap_LAN_ServerStatus(serverAddress, NULL, 0); return qfalse; }
    memset(info, 0, sizeof(*info));
    if(!trap_LAN_ServerStatus(serverAddress, info->text, sizeof(info->text))) return qfalse;
    UI_ParseServerStatus(info, serverAddress);
    UI_SortServerStatusInfo(info);
    return qtrue;
}

int UI_GetServerStatusInfo(const char *address, serverStatusInfo_t *info) {
    int ready = UI_QueryServerStatus(address, info);
    if(ready) UI_StatusLinks(info);
    return ready;
}

/* Browser localhost has no independent UDP LAN-status round trip. Once the
 * client is connected the authoritative server info is already available as
 * CS_SERVERINFO, so use it only for the local in-game dialog fallback. */
int UI_GetConnectedLocalServerStatus(const char *address, serverStatusInfo_t *info) {
    char serverInfo[MAX_INFO_STRING];
    uiClientState_t state;
    const char *shownAddress;
    if(!info) return qfalse;
    trap_GetClientState(&state);
    if(state.connState < CA_CONNECTED) return qfalse;
    if(address && *address && Q_stricmp(address, "localhost") &&
       Q_stricmp(address, "loopback") && Q_stricmp(address, "127.0.0.1") &&
       Q_stricmpn(address, "localhost:", 10) &&
       Q_stricmpn(address, "127.0.0.1:", 10) && Q_stricmpn(address, "[::1]", 5)) return qfalse;
    memset(serverInfo, 0, sizeof(serverInfo));
    if(!trap_GetConfigString(CS_SERVERINFO, serverInfo, sizeof(serverInfo)) || !serverInfo[0])
        return qfalse;
    memset(info, 0, sizeof(*info));
    Q_strncpyz(info->text, serverInfo, sizeof(info->text));
    shownAddress = address && *address ? address : "localhost";
    UI_ParseServerStatus(info, shownAddress);
    UI_SortServerStatusInfo(info);
    UI_StatusLinks(info);
    return qtrue;
}
