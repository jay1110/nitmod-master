#include "ui_local.h"
#include "../game/nitmod_protocol.h"
#include <limits.h>

static int browserHumans[MAX_GLOBAL_SERVERS];
static qboolean browserHumanKnown[MAX_GLOBAL_SERVERS];
static int browserHumanStarted[MAX_GLOBAL_SERVERS];
static qboolean browserHumanPending[MAX_GLOBAL_SERVERS];
/* Retain the requested address: engine indices may belong to another source
 * or change during a master refresh before its pending request is released. */
static char browserStatusAddress[MAX_GLOBAL_SERVERS][MAX_ADDRESSLENGTH];

static int UI_ServerGametype( const char *info ) {
	int gametype;
	if( !NITMOD_ParseProtocolInteger(Info_ValueForKey(info ? info : "", "gametype"), &gametype) ||
		gametype >= GT_MAX_GAME_TYPE ) return -1;
	return gametype;
}

/* Original population precedence: status humans, ET Legacy master humans,
 * otherwise positive-ping player records. No player name is parsed as a key. */
int UI_ServerHumanCount(const char *status, const char *master) {
    serverStatusInfo_t parsed;
    const char *value;
    int row, humans=0;
    qboolean authoritative;
    value=Info_ValueForKey(status ? status : "", "humans");
    authoritative = *value != 0;
    if(!authoritative && master && strstr(Info_ValueForKey(master,"version"),"ET Legacy")) {
        value=Info_ValueForKey(master,"humans");
        /* Original LAB_000245f7 treats an empty Legacy count as zero too. */
        authoritative=qtrue;
    }
    if(authoritative) {
        long count=strtol(value,NULL,10);
        return count<0 ? 0 : count>MAX_CLIENTS ? MAX_CLIENTS : (int)count;
    }
    memset(&parsed,0,sizeof(parsed));
    Q_strncpyz(parsed.text,status ? status : "",sizeof(parsed.text));
    UI_ParseServerStatus(&parsed,"");
    for(row=0;row<parsed.numLines;++row)
        if(parsed.lines[row][0][0]>='0' && parsed.lines[row][0][0]<='9' &&
           parsed.lines[row][1][0] && atoi(parsed.lines[row][2])>0) ++humans;
    return humans;
}

int UI_CompareBrowserServers(int first,int second) {
    if(uiInfo.serverStatus.sortKey==SORT_CLIENTS && first>=0 && first<MAX_GLOBAL_SERVERS &&
       second>=0 && second<MAX_GLOBAL_SERVERS) {
        /* One comparator domain, as in original UI_ServersQsortCompare_bis.
         * Unknown entries must not reuse counts from an earlier refresh. */
        int a=browserHumanKnown[first] ? browserHumans[first] : 0;
        int b=browserHumanKnown[second] ? browserHumans[second] : 0;
        int order=(a>b)-(a<b);
        return uiInfo.serverStatus.sortDir ? -order : order;
    }
    return trap_LAN_CompareServers(ui_netSource.integer,uiInfo.serverStatus.sortKey,
        uiInfo.serverStatus.sortDir,first,second);
}

/*
==================
UI_InsertServerIntoDisplayList
==================
*/
static void UI_InsertServerIntoDisplayList(int num, int position) {
	int i;

	if (num < 0 || uiInfo.serverStatus.numDisplayServers < 0 ||
		position < 0 || position > uiInfo.serverStatus.numDisplayServers ||
		uiInfo.serverStatus.numDisplayServers >= MAX_DISPLAY_SERVERS) {
		return;
	}
	//
	for (i = uiInfo.serverStatus.numDisplayServers; i > position; i--) {
		uiInfo.serverStatus.displayServers[i] = uiInfo.serverStatus.displayServers[i-1];
	}
	uiInfo.serverStatus.displayServers[position] = num;
	uiInfo.serverStatus.numDisplayServers++;
}

/*
==================
UI_RemoveServerFromDisplayList
==================
*/
static void UI_RemoveServerFromDisplayList(int num) {
	int i, j;
	if(uiInfo.serverStatus.numDisplayServers < 0 ||
		uiInfo.serverStatus.numDisplayServers > MAX_DISPLAY_SERVERS) return;

	for (i = 0; i < uiInfo.serverStatus.numDisplayServers; i++) {
		if (uiInfo.serverStatus.displayServers[i] == num) {
			uiInfo.serverStatus.numDisplayServers--;
			for (j = i; j < uiInfo.serverStatus.numDisplayServers; j++) {
				uiInfo.serverStatus.displayServers[j] = uiInfo.serverStatus.displayServers[j+1];
			}
			return;
		}
	}
}

/*
==================
UI_BinaryServerInsertion
==================
*/
static void UI_BinaryServerInsertion(int num) {
	int mid, offset, res, len;

	// use binary search to insert server
	len = uiInfo.serverStatus.numDisplayServers;
	if(len < 0 || len >= MAX_DISPLAY_SERVERS || num < 0) return;
	mid = len;
	offset = 0;
	res = 0;
	while(mid > 0) {
		mid = len >> 1;
		//
		res = UI_CompareBrowserServers(num, uiInfo.serverStatus.displayServers[offset+mid]);
		// if equal
		if (res == 0) {
			UI_InsertServerIntoDisplayList(num, offset+mid);
			return;
		}
		// if larger
		else if (res > 0) {
			offset += mid;
			len -= mid;
		}
		// if smaller
		else {
			len -= mid;
		}
	}
	if (res > 0) {
		offset++;
	}
	UI_InsertServerIntoDisplayList(num, offset);
}

/*
==================
UI_BuildServerDisplayList
==================
*/
/* NxAC is announced only through a server-status reply (`sv_NxAC`), not the
 * master-server info string.  -1 means that an asynchronous query is still
 * outstanding, 0 that it is absent, and 1 that it is present. */
static int nitmodNxacStatus[MAX_GLOBAL_SERVERS];
static int nitmodNxacStatusSource = -1;
/* Original feeder filter column consumes resolved sv_NxAC, without opening
 * another request while painting. Unknown/expired source data has no icon. */
qboolean UI_ServerHasNxac(int server) {
    return nitmodNxacStatusSource == ui_netSource.integer &&
        server >= 0 && server < MAX_GLOBAL_SERVERS && nitmodNxacStatus[server] > 0;
}

/* Original UI_FeederItemText case 2: humans(+bots)/capacity. Rendering must
 * not allocate status requests; consume only this source's resolved cache. */
void UI_ServerPopulationText(int server, const char *master, char *out, int size) {
    int clients = atoi(Info_ValueForKey(master, "clients"));
    int capacity = atoi(Info_ValueForKey(master, "sv_maxclients"));
    int humans;
    clients = clients < 0 ? 0 : clients > MAX_CLIENTS ? MAX_CLIENTS : clients;
    capacity = capacity < 0 ? 0 : capacity > MAX_CLIENTS ? MAX_CLIENTS : capacity;
    humans = clients;
    if(nitmodNxacStatusSource == ui_netSource.integer && server >= 0 &&
       server < MAX_GLOBAL_SERVERS && browserHumanKnown[server]) {
        humans = browserHumans[server];
    } else if(strstr(Info_ValueForKey(master, "version"), "ET Legacy") &&
              *Info_ValueForKey(master, "humans")) {
        humans = UI_ServerHumanCount("", master);
    }
    /* Status and master replies can describe different instants. */
    humans = humans < 0 ? 0 : humans > clients ? clients : humans;
    if(humans != clients)
        Com_sprintf(out, size, "^7%i^9(+%i)/%i", humans, clients - humans, capacity);
    else
        Com_sprintf(out, size, "^7%i^9/%i", clients, capacity);
}
/* One contribution per engine server index, including filtered servers as in
 * the original total. Favorites and pending replies can revisit an index. */
static int nitmodBrowserPlayers[MAX_GLOBAL_SERVERS];

static void UI_ReleaseBrowserStatus(int server) {
    if(browserStatusAddress[server][0]) {
        trap_LAN_ServerStatus(browserStatusAddress[server],NULL,0);
        browserStatusAddress[server][0]=0;
    }
    browserHumanPending[server]=qfalse;
}

void UI_CancelBrowserStatusRequests(void) {
    int server;
    for(server=0;server<MAX_GLOBAL_SERVERS;++server)
        if(browserHumanPending[server]) UI_ReleaseBrowserStatus(server);
}

qboolean UI_BrowserStatusPending(void) {
    int server;
    for(server=0;server<MAX_GLOBAL_SERVERS;++server)
        if(browserHumanPending[server]) return qtrue;
    return qfalse;
}

/* Original full refresh clears the engine status cache as well as both local
 * caches. Address-specific release alone leaves old replies cached in ET. */
static void UI_ResetBrowserStatusCache(int source) {
    UI_CancelBrowserStatusRequests();
    trap_LAN_ServerStatus(NULL,NULL,0);
    memset(nitmodNxacStatus,0xff,sizeof(nitmodNxacStatus));
    memset(nitmodBrowserPlayers,0,sizeof(nitmodBrowserPlayers));
    memset(browserHumans,0,sizeof(browserHumans));
    memset(browserHumanKnown,0,sizeof(browserHumanKnown));
    memset(browserHumanPending,0,sizeof(browserHumanPending));
    memset(browserHumanStarted,0,sizeof(browserHumanStarted));
    nitmodNxacStatusSource=source;
}

static int UI_NitmodNxacStatus( int serverNum, const char *master ) {
	char address[MAX_ADDRESSLENGTH];
	char status[MAX_SERVERSTATUS_TEXT];

	if( serverNum < 0 || serverNum >= MAX_GLOBAL_SERVERS ) {
		return 0;
	}
	if( nitmodNxacStatus[serverNum] >= 0 ) {
		return nitmodNxacStatus[serverNum];
	}

	trap_LAN_GetServerAddressString( ui_netSource.integer, serverNum,
		address, sizeof( address ) );
	address[sizeof(address)-1]=0;
	if(strcmp(address,browserStatusAddress[serverNum])) {
		if(browserStatusAddress[serverNum][0])
			trap_LAN_ServerStatus(browserStatusAddress[serverNum],NULL,0);
		Q_strncpyz(browserStatusAddress[serverNum],address,sizeof(browserStatusAddress[serverNum]));
	}
	if( !address[0] || !trap_LAN_ServerStatus( address, status, sizeof( status ) ) ) {
		return -1;
	}
	status[sizeof(status)-1]=0;
	nitmodNxacStatus[serverNum] = atoi( Info_ValueForKey( status, "sv_NxAC" ) ) ? 1 : 0;
	browserHumans[serverNum]=UI_ServerHumanCount(status,master);
	browserHumanKnown[serverNum]=qtrue;
	/* The value is cached locally; release the engine's finite request slot. */
	UI_ReleaseBrowserStatus(serverNum);
	return nitmodNxacStatus[serverNum];
}

void UI_BuildServerDisplayList(qboolean force) {
	int i, count, clients, maxClients, ping, game, len, visible, friendlyFire, maxlives, punkbuster, antilag, password, weaponrestricted, balancedteams, nxacStatus;
	char info[MAX_STRING_CHARS];
	//qboolean startRefresh = qtrue; // TTimo: unused
	static int numinvisible;

	game = 0;		// NERVE - SMF - shut up compiler warning

	if( !(force || uiInfo.uiDC.realTime > uiInfo.serverStatus.nextDisplayRefresh) ) {
		return;
	}

	// if we shouldn't reset
	if ( force == 2 ) {
		force = 0;
	}
	if(nitmodNxacStatusSource != ui_netSource.integer) force = qtrue;
	if( force ) {
		UI_ResetBrowserStatusCache(ui_netSource.integer);
	}

	// do motd updates here too
	trap_Cvar_VariableStringBuffer( "cl_motdString", uiInfo.serverStatus.motd, sizeof(uiInfo.serverStatus.motd) );
	len = strlen(uiInfo.serverStatus.motd);
	if (len == 0) {
		strcpy(uiInfo.serverStatus.motd, va( "Enemy Territory - Version: %s", Q3_VERSION ) );
		len = strlen(uiInfo.serverStatus.motd);
	} 
	if (len != uiInfo.serverStatus.motdLen) {
		uiInfo.serverStatus.motdLen = len;
		uiInfo.serverStatus.motdWidth = -1;
	} 

	if (force) {
		numinvisible = 0;
		// clear number of displayed servers
		uiInfo.serverStatus.numDisplayServers = 0;
		uiInfo.serverStatus.numPlayersOnServers = 0;
		uiInfo.serverStatus.currentServer = 0;
		// set list box index to zero
		Menu_SetFeederSelection(NULL, FEEDER_SERVERS, 0, NULL);
		// mark all servers as visible so we store ping updates for them
		trap_LAN_MarkServerVisible(ui_netSource.integer, -1, qtrue);
	}

	// get the server count (comes from the master)
	count = trap_LAN_GetServerCount(ui_netSource.integer);
	if (count < 0 || (ui_netSource.integer == AS_LOCAL && count == 0) ) {
		// still waiting on a response from the master
		UI_ResetBrowserStatusCache(ui_netSource.integer);
		uiInfo.serverStatus.numDisplayServers = 0;
		uiInfo.serverStatus.numPlayersOnServers = 0;
		uiInfo.serverStatus.nextDisplayRefresh = uiInfo.uiDC.realTime > INT_MAX - 500 ?
			INT_MAX : uiInfo.uiDC.realTime + 500;
		uiInfo.serverStatus.currentServerPreview = 0;
		return;
	}
	if(count > MAX_GLOBAL_SERVERS) count = MAX_GLOBAL_SERVERS;
	/* Entries removed while refreshing cannot retain engine request slots. */
	for(i=count;i<MAX_GLOBAL_SERVERS;++i)
		if(browserHumanPending[i]) UI_ReleaseBrowserStatus(i);

	if( !uiInfo.serverStatus.numDisplayServers ) {
		uiInfo.serverStatus.currentServerPreview = 0;
	}

	visible = qfalse;
	for (i = 0; i < count; i++) {
		// if we already got info for this server
		if( !trap_LAN_ServerIsVisible(ui_netSource.integer, i) ) {
			if(browserHumanPending[i]) UI_ReleaseBrowserStatus(i);
			continue;
		}
		visible = qtrue;
		// get the ping for this server
		ping = trap_LAN_GetServerPing(ui_netSource.integer, i);
		if (ping >/*=*/ 0 || ui_netSource.integer == AS_FAVORITES) {

			trap_LAN_GetServerInfo( ui_netSource.integer, i, info, MAX_STRING_CHARS );

			clients = atoi(Info_ValueForKey(info, "clients"));
			clients = clients < 0 ? 0 : clients > MAX_CLIENTS ? MAX_CLIENTS : clients;
			uiInfo.serverStatus.numPlayersOnServers += clients - nitmodBrowserPlayers[i];
			nitmodBrowserPlayers[i] = clients;

			trap_Cvar_Update( &ui_browserShowEmptyOrFull );
			if( ui_browserShowEmptyOrFull.integer ) {
				maxClients = atoi(Info_ValueForKey(info, "sv_maxclients"));

				if( clients != maxClients && (
					( !clients && ui_browserShowEmptyOrFull.integer == 2 ) ||
					( clients && ui_browserShowEmptyOrFull.integer == 1 ) ) ) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}

				if( clients && (
					( clients == maxClients && ui_browserShowEmptyOrFull.integer == 2 ) ||
					( clients != maxClients && ui_browserShowEmptyOrFull.integer == 1 ) ) ) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}

			trap_Cvar_Update( &ui_browserShowPasswordProtected );
			if( ui_browserShowPasswordProtected.integer ) {
				password = atoi(Info_ValueForKey( info, "needpass" ) );
				if( ( password && ui_browserShowPasswordProtected.integer == 2 ) ||
					( !password && ui_browserShowPasswordProtected.integer == 1 ) ) {
					trap_LAN_MarkServerVisible( ui_netSource.integer, i, qfalse );
					continue;
				}
			}

			trap_Cvar_Update( &ui_browserShowFriendlyFire );
			if ( ui_browserShowFriendlyFire.integer ) {
				/* Original UI_BuildServerDisplayList 0x148eb tests bit 1. */
				friendlyFire = atoi(Info_ValueForKey(info, "friendlyFire")) & 1;

				if( ( friendlyFire && ui_browserShowFriendlyFire.integer == 2 ) ||
					( !friendlyFire && ui_browserShowFriendlyFire.integer == 1 ) ) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}

			trap_Cvar_Update( &ui_browserShowMaxlives );
			if ( ui_browserShowMaxlives.integer ) {
				maxlives = atoi(Info_ValueForKey(info, "maxlives"));
				if( ( maxlives && ui_browserShowMaxlives.integer == 2 ) ||
					( !maxlives && ui_browserShowMaxlives.integer == 1 ) ) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}

			trap_Cvar_Update( &ui_browserShowPunkBuster );
			if ( ui_browserShowPunkBuster.integer ) {
				punkbuster = atoi(Info_ValueForKey(info, "punkbuster"));

				if( ( punkbuster && ui_browserShowPunkBuster.integer == 2 ) ||
					( !punkbuster && ui_browserShowPunkBuster.integer == 1 ) ) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}

			trap_Cvar_Update( &ui_browserShowAntilag );
			if ( ui_browserShowAntilag.integer ) {
				antilag = atoi(Info_ValueForKey(info, "g_antilag"));
				
				if( ( antilag && ui_browserShowAntilag.integer == 2 ) ||
					( !antilag && ui_browserShowAntilag.integer == 1 ) ) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}

			trap_Cvar_Update( &ui_browserShowWeaponsRestricted );
			if ( ui_browserShowWeaponsRestricted.integer ) {
				weaponrestricted = atoi(Info_ValueForKey(info, "weaprestrict"));
				
				if( ( weaponrestricted != 100 && ui_browserShowWeaponsRestricted.integer == 2 ) ||
					( weaponrestricted == 100 && ui_browserShowWeaponsRestricted.integer == 1 ) ) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}

			trap_Cvar_Update( &ui_browserShowTeamBalanced );
			if ( ui_browserShowTeamBalanced.integer ) {
				balancedteams = atoi(Info_ValueForKey(info, "balancedteams"));
				
				if( ( balancedteams && ui_browserShowTeamBalanced.integer == 2 ) ||
					( !balancedteams && ui_browserShowTeamBalanced.integer == 1 ) ) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}

			trap_Cvar_Update( &ui_joinGameType );
			if( ui_joinGameType.integer != -1 ) {
				game = UI_ServerGametype(info);
				if( game != ui_joinGameType.integer ) {
					trap_LAN_MarkServerVisible( ui_netSource.integer, i, qfalse );
					continue;
				}
			}

			/* Original: 0 = all, 1 = Nitmod only, 2 = exclude Nitmod. */
			trap_Cvar_Update( &ui_browserNitmodonly );
			if( ui_browserNitmodonly.integer ) {
				qboolean isNitmod = !Q_stricmp( Info_ValueForKey( info, "game" ), "nitmod" );
				if( ( ui_browserNitmodonly.integer == 1 && !isNitmod ) ||
					( ui_browserNitmodonly.integer == 2 && isNitmod ) ) {
					trap_LAN_MarkServerVisible( ui_netSource.integer, i, qfalse );
					continue;
				}
			}

			/* Resolve status before applying either NxAC filter, so every request
			 * shares the bounded lifetime. Original refresh waits for status work
			 * independently of pings and eventually drops unanswered requests.
			 * Retain this port's documented 5-second master-population fallback
			 * for unfiltered rows; an unknown NxAC status never passes a filter. */
			if(!browserHumanKnown[i]) {
				if(!browserHumanPending[i]) {
					browserHumanPending[i]=qtrue;
					browserHumanStarted[i]=uiInfo.uiDC.realTime;
				}
				if(UI_NitmodNxacStatus(i,info)<0) {
					double elapsed=(double)uiInfo.uiDC.realTime-browserHumanStarted[i];
					if(elapsed<0) browserHumanStarted[i]=uiInfo.uiDC.realTime;
					if(elapsed<5000) {
						uiInfo.serverStatus.numPlayersOnServers-=clients;
						nitmodBrowserPlayers[i]=0;
						continue;
					}
					UI_ReleaseBrowserStatus(i);
					browserHumans[i]=clients;
					browserHumanKnown[i]=qtrue;
				}
			}
			trap_Cvar_Update( &ui_browserNxAConly );
			if( ui_browserNitmodonly.integer == 1 &&
				(ui_browserNxAConly.integer == 1 || ui_browserNxAConly.integer == 2) ) {
				nxacStatus = nitmodNxacStatus[i];
				if( nxacStatus < 0 ||
					( ui_browserNxAConly.integer == 1 && !nxacStatus ) ||
					( ui_browserNxAConly.integer == 2 && nxacStatus ) ) {
					trap_LAN_MarkServerVisible( ui_netSource.integer, i, qfalse );
					continue;
				}
			}

			/*trap_Cvar_Update( &ui_serverFilterType );
			if (ui_serverFilterType.integer > 0) {
				if (Q_stricmp(Info_ValueForKey(info, "game"), serverFilters[ui_serverFilterType.integer].basedir) != 0) {
					trap_LAN_MarkServerVisible(ui_netSource.integer, i, qfalse);
					continue;
				}
			}*/

			// make sure we never add a favorite server twice
			if (ui_netSource.integer == AS_FAVORITES) {
				UI_RemoveServerFromDisplayList(i);
			}
			// insert the server into the list
			if( uiInfo.serverStatus.numDisplayServers == 0 ) {
				char *s = Info_ValueForKey( info, "mapname" );

				if( s && *s ) {
					uiInfo.serverStatus.currentServerPreview = trap_R_RegisterShaderNoMip( va( "levelshots/%s", Info_ValueForKey( info, "mapname" ) ) );
				} else {
					uiInfo.serverStatus.currentServerPreview = trap_R_RegisterShaderNoMip( "levelshots/unknownmap" );
				}
			}

			UI_BinaryServerInsertion(i);
			// done with this server
			if( ping >/*=*/ 0 ) {
				trap_LAN_MarkServerVisible( ui_netSource.integer, i, qfalse );
				numinvisible++;
			}
		}
	}

	uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime;

	// if there were no servers visible for ping updates
	if (!visible) {
//		UI_StopServerRefresh();
//		uiInfo.serverStatus.nextDisplayRefresh = 0;
	}
}
