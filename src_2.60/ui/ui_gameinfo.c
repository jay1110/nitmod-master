// Copyright (C) 1999-2000 Id Software, Inc.
//
//
// gameinfo.c
//

#include "ui_local.h"


//
// arena and bot info
//


int				ui_numBots;
static char		*ui_botInfos[MAX_BOTS];

static int		ui_numArenas;
//static char		*ui_arenaInfos[MAX_ARENAS];

//static int		ui_numSinglePlayerArenas; // TTimo: unused
//static int		ui_numSpecialSinglePlayerArenas; // TTimo: unused

/*
===============
UI_ParseInfos
===============
*/
int UI_ParseInfos( char *buf, int max, char *infos[], int totalmax ) {
	char	*token;
	int		count;
	char	key[MAX_TOKEN_CHARS];
	char	info[MAX_INFO_STRING];

	count = 0;

	while ( 1 ) {
		token = COM_Parse( &buf );
		if ( !token[0] ) {
			break;
		}
		if ( strcmp( token, "{" ) ) {
			Com_Printf( "Missing { in info file\n" );
			break;
		}

		if ( count == max ) {
			Com_Printf( "Max infos exceeded\n" );
			break;
		}

		info[0] = '\0';
		while ( 1 ) {
			token = COM_ParseExt( &buf, qtrue );
			if ( !token[0] ) {
				Com_Printf( "Unexpected end of info file\n" );
				break;
			}
			if ( !strcmp( token, "}" ) ) {
				break;
			}
			Q_strncpyz( key, token, sizeof( key ) );

			token = COM_ParseExt( &buf, qfalse );
			if ( !token[0] ) {
				strcpy( token, "<NULL>" );
			}
			Info_SetValueForKey( info, key, token );
		}
		//NOTE: extra space for arena number
		infos[count] = UI_Alloc(strlen(info) + strlen("\\num\\") + strlen(va("%d", totalmax)) + 1);
		if (infos[count]) {
			strcpy(infos[count], info);
			count++;
		}
	}
	return count;
}

/*
===============
UI_LoadArenasFromFile
===============
*/
static void UI_LoadArenasFromFile( char *filename ) {
/*	int				len;
	fileHandle_t	f;
	char			buf[MAX_ARENAS_TEXT];

	len = trap_FS_FOpenFile( filename, &f, FS_READ );
	if ( !f ) {
		trap_Print( va( S_COLOR_RED "file not found: %s\n", filename ) );
		return;
	}
	if ( len >= MAX_ARENAS_TEXT ) {
		trap_Print( va( S_COLOR_RED "file too large: %s is %i, max allowed is %i", filename, len, MAX_ARENAS_TEXT ) );
		trap_FS_FCloseFile( f );
		return;
	}

	trap_FS_Read( buf, len, f );
	buf[len] = 0;
	trap_FS_FCloseFile( f );

	ui_numArenas += UI_ParseInfos( buf, MAX_ARENAS - ui_numArenas, &ui_arenaInfos[ui_numArenas], MAX_ARENAS );*/

	int handle;
	pc_token_t token;

	handle = trap_PC_LoadSource( filename );

	if( !handle ) {
		trap_Print( va( S_COLOR_RED "file not found: %s\n", filename ) );
		return;
	}

	if( !trap_PC_ReadToken( handle, &token ) ) {
		trap_PC_FreeSource( handle );
		return;
	}

	if( *token.string != '{' ) {
		trap_PC_FreeSource( handle );
		return;
	}

	uiInfo.mapList[uiInfo.mapCount].cinematic = -1;
	uiInfo.mapList[uiInfo.mapCount].levelShot = -1;
	uiInfo.mapList[uiInfo.mapCount].typeBits = 0;

	while( trap_PC_ReadToken( handle, &token ) ) {
		if( *token.string == '}' ) {

			if( !uiInfo.mapList[uiInfo.mapCount].typeBits ) {
				uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_WOLF);
			}

			uiInfo.mapCount++;
			if( uiInfo.mapCount >= MAX_MAPS ) {
				break;
			}

			if( !trap_PC_ReadToken( handle, &token ) ) {
				// eof
				trap_PC_FreeSource( handle );
				return;
			}

			if( *token.string != '{' ) {
				trap_Print( va( S_COLOR_RED "unexpected token '%s' inside: %s\n", token.string, filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "map" ) ) {
			if( !PC_String_Parse( handle, &uiInfo.mapList[uiInfo.mapCount].mapLoadName ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "longname" ) ) {
			if( !PC_String_Parse( handle, &uiInfo.mapList[uiInfo.mapCount].mapName ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "briefing" ) ) {
			if( !PC_String_Parse( handle, &uiInfo.mapList[uiInfo.mapCount].briefing ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "lmsbriefing" ) ) {
			if( !PC_String_Parse( handle, &uiInfo.mapList[uiInfo.mapCount].lmsbriefing ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		/*} else if( !Q_stricmp( token.string, "objectives" ) ) {
			if( !PC_String_Parse( handle, &uiInfo.mapList[uiInfo.mapCount].objectives ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}*/
		} else if( !Q_stricmp( token.string, "timelimit" ) ) {
			if( !PC_Int_Parse( handle, &uiInfo.mapList[uiInfo.mapCount].Timelimit ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "axisrespawntime" ) ) {
			if( !PC_Int_Parse( handle, &uiInfo.mapList[uiInfo.mapCount].AxisRespawnTime ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "alliedrespawntime" ) ) {
			if( !PC_Int_Parse( handle, &uiInfo.mapList[uiInfo.mapCount].AlliedRespawnTime ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "type" ) ) {
			if( !trap_PC_ReadToken( handle, &token ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			} else {
				if( strstr( token.string, "wolfsp" ) ) {
					uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_SINGLE_PLAYER);
				}
				if( strstr( token.string, "wolflms" ) ) {
					uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_WOLF_LMS);
				}
				if( strstr( token.string, "wolfmp" ) ) {
					uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_WOLF);
				}
				if( strstr( token.string, "wolfsw" ) ) {
					uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_WOLF_STOPWATCH);
				}
			}
		} else if( !Q_stricmp( token.string, "mapposition_x" ) ) {
			if( !PC_Float_Parse( handle, &uiInfo.mapList[uiInfo.mapCount].mappos[0] ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "mapposition_y" ) ) {
			if( !PC_Float_Parse( handle, &uiInfo.mapList[uiInfo.mapCount].mappos[1] ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		}
	}

	trap_PC_FreeSource( handle );
	return;
}

/*
===============
UI_LoadArenas
===============
*/
void UI_LoadArenas( void ) {
	int			numdirs;
//	vmCvar_t	arenasFile;
	char		filename[128];
	char		dirlist[1024];
	const char *dirptr;
	int			i/*, n*/;
	int offset = 0;
	//char		*type, *str;

	ui_numArenas = 0;
	uiInfo.mapCount = 0;

/*	NERVE - SMF - commented out
	trap_Cvar_Register( &arenasFile, "g_arenasFile", "", CVAR_INIT|CVAR_ROM );
	if( *arenasFile.string ) {
		UI_LoadArenasFromFile(arenasFile.string);
	}
	else {
		UI_LoadArenasFromFile("scripts/arenas.txt");
	}
*/
	// get all arenas from .arena files
	memset(dirlist, 0, sizeof(dirlist));
	numdirs = trap_FS_GetFileList("scripts", ".arena", dirlist, 1024 );
	for (i = 0; i < numdirs && uiInfo.mapCount < MAX_MAPS; i++) {
		dirptr = UI_CatalogNextString(dirlist, sizeof(dirlist), &offset);
		if(!dirptr || !*dirptr) break;
		if(!UI_CatalogScriptPath(dirptr, filename, sizeof(filename))) continue;
		UI_LoadArenasFromFile(filename);
	}
	/* Sort before campaign parsing takes pointers into mapList. */
	UI_SortCatalog(UI_CATALOG_MAPS);
//	trap_DPrint( va( "%i arenas parsed\n", ui_numArenas ) ); // JPW NERVE pulled per atvi req
/*	if (UI_OutOfMemory()) {
		trap_Print(S_COLOR_YELLOW"WARNING: not anough memory in pool to load all arenas\n");
	}*/

/*	for( n = 0; n < ui_numArenas; n++ ) {
		// determine type

		uiInfo.mapList[uiInfo.mapCount].cinematic = -1;
		uiInfo.mapList[uiInfo.mapCount].mapLoadName = String_Alloc(Info_ValueForKey(ui_arenaInfos[n], "map"));
		uiInfo.mapList[uiInfo.mapCount].mapName = String_Alloc(Info_ValueForKey(ui_arenaInfos[n], "longname"));
		uiInfo.mapList[uiInfo.mapCount].levelShot = -1;
		uiInfo.mapList[uiInfo.mapCount].imageName = String_Alloc(va("levelshots/%s", uiInfo.mapList[uiInfo.mapCount].mapLoadName));
		uiInfo.mapList[uiInfo.mapCount].typeBits = 0;

		uiInfo.mapList[uiInfo.mapCount].briefing = String_Alloc(Info_ValueForKey(ui_arenaInfos[n], "briefing"));
		uiInfo.mapList[uiInfo.mapCount].lmsbriefing = String_Alloc(Info_ValueForKey(ui_arenaInfos[n], "lmsbriefing"));
//		uiInfo.mapList[uiInfo.mapCount].objectives = String_Alloc(Info_ValueForKey(ui_arenaInfos[n], "objectives"));*/
		// Gordon: cant use "\" in a key/pair translating * to \n for the moment, reeally should be using PC_ parsing stuff for this too
		// eek, no ; either.....

		// Arnout: THIS IS BAD DO NOT MODIFY A STRING AFTER IT IS ALLOCATED
		/*{
			char* p;
			while(p = strchr(uiInfo.mapList[uiInfo.mapCount].description, '*')) {
				*p = '\n';
			}

			while(p = strchr(uiInfo.mapList[uiInfo.mapCount].objectives, '*')) {
				*p = '\n';
			}
		}*/

		// NERVE - SMF
		// set timelimit
/*		str = Info_ValueForKey( ui_arenaInfos[n], "Timelimit" );
		if ( *str )
			uiInfo.mapList[uiInfo.mapCount].Timelimit = atoi( str );
		else
			uiInfo.mapList[uiInfo.mapCount].Timelimit = 0;

		// set axis respawn time
		str = Info_ValueForKey( ui_arenaInfos[n], "AxisRespawnTime" );
		if ( *str )
			uiInfo.mapList[uiInfo.mapCount].AxisRespawnTime = atoi( str );
		else
			uiInfo.mapList[uiInfo.mapCount].AxisRespawnTime = 0;

		// set allied respawn time
		str = Info_ValueForKey( ui_arenaInfos[n], "AlliedRespawnTime" );
		if ( *str )
			uiInfo.mapList[uiInfo.mapCount].AlliedRespawnTime = atoi( str );
		else
			uiInfo.mapList[uiInfo.mapCount].AlliedRespawnTime = 0;
		// -NERVE - SMF

		type = Info_ValueForKey( ui_arenaInfos[n], "type" );
		if( *type ) {
			// NERVE - SMF
			if( strstr( type, "wolfsp" ) ) {
				uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_SINGLE_PLAYER);
			}
			if( strstr( type, "wolflms" ) ) {
				uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_WOLF_LMS);
			}
			if( strstr( type, "wolfmp" ) ) {
				uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_WOLF);
			}
			if( strstr( type, "wolfsw" ) ) {
				uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_WOLF_STOPWATCH);
			}
			// -NERVE - SMF
		} else { // Gordon: default is wolf now
			uiInfo.mapList[uiInfo.mapCount].typeBits |= (1 << GT_WOLF);
		}

		str = Info_ValueForKey( ui_arenaInfos[n], "mapposition_x" );
		if ( *str ) {
			uiInfo.mapList[uiInfo.mapCount].mappos[0] = atof(str);
		} else {
			uiInfo.mapList[uiInfo.mapCount].mappos[0] = 0.f;
		}

		str = Info_ValueForKey( ui_arenaInfos[n], "mapposition_y" );
		if ( *str ) {
			uiInfo.mapList[uiInfo.mapCount].mappos[1] = atof(str);
		} else {
			uiInfo.mapList[uiInfo.mapCount].mappos[1] = 0.f;
		}

		uiInfo.mapCount++;
		if (uiInfo.mapCount >= MAX_MAPS) {
			break;
		}
	}*/
}

mapInfo* UI_FindMapInfoByMapname( const char* name ) {
	int i;

	if(uiInfo.mapCount == 0) {
		UI_LoadArenas();
	}

	for( i = 0; i < uiInfo.mapCount; i++ ) {
		if(!Q_stricmp(uiInfo.mapList[i].mapLoadName, name)) {
			return &uiInfo.mapList[i];
		}
	}

	return NULL;
}

// Campaign files
/*
===============
UI_LoadCampaignsFromFile
===============
*/
/*static void UI_LoadCampaignsFromFile( const char *filename, campaignInfo_t *campaignList, int *campaignCount, int maxCampaigns ) {
	int handle, i;
	pc_token_t token;

	handle = trap_PC_LoadSource( filename );

	if( !handle ) {
		trap_Print( va( S_COLOR_RED "file not found: %s\n", filename ) );
		return;
	}

	if( !trap_PC_ReadToken( handle, &token ) )
		return;
	if( *token.string != '{' )
		return;

	while ( trap_PC_ReadToken( handle, &token ) ) {
		if( *token.string == '}' ) {
			if( campaignList[*campaignCount].initial ) {
				campaignList[*campaignCount].unlocked = qtrue;
				// Always unlock the initial campaign
			}

			*campaignCount++;

			if( *campaignCount >= maxCampaigns || !trap_PC_ReadToken( handle, &token ) ) {
				// eof or max campaigns reached
				trap_PC_FreeSource( handle );
				return;
			}

			if( *token.string != '{' ) {
				//campaignList[*campaignCount].order = -1;

				trap_Print( va( S_COLOR_RED "unexpected token '%s' inside: %s\n", token.string, filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "shortname" ) ) {
			if( !PC_String_Parse( handle, &campaignList[*campaignCount].campaignShortName ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "name" ) ) {
			if( !PC_String_Parse( handle, &campaignList[*campaignCount].campaignName ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "description" ) ) {
			if( !PC_String_Parse( handle, &campaignList[*campaignCount].campaignDescription ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "image" ) ) {
			if( !PC_String_Parse( handle, &campaignList[*campaignCount].campaignShotName ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			} else {
				campaignList[*campaignCount].campaignShot = -1;
			}
		} else if( !Q_stricmp( token.string, "initial" ) ) {
			campaignList[*campaignCount].initial = qtrue;
		} else if( !Q_stricmp( token.string, "next" ) ) {
			if( !PC_String_Parse( handle, &campaignList[*campaignCount].nextCampaignShortName ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		} else if( !Q_stricmp( token.string, "type" ) ) {
			if( !trap_PC_ReadToken( handle, &token ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}

			if( strstr( token.string, "wolfsp" ) ) {
				campaignList[*campaignCount].typeBits |= (1 << GT_SINGLE_PLAYER);
			}
			if( strstr( token.string, "wolfmp" ) ) {
				campaignList[*campaignCount].typeBits |= (1 << GT_WOLF);
			}
			if( strstr( token.string, "wolfsw" ) ) {
				campaignList[*campaignCount].typeBits |= (1 << GT_WOLF_STOPWATCH);
			}
			if( strstr( token.string, "wolflms" ) ) {
				campaignList[*campaignCount].typeBits |= (1 << GT_WOLF_LMS);
			}
		} else if( !Q_stricmp( token.string, "maps" ) ) {
			if( !PC_String_Parse( handle, &campaignList[*campaignCount].maps ) ) {
				trap_Print( va( S_COLOR_RED "unexpected end of file inside: %s\n", filename ) );
				trap_PC_FreeSource( handle );
				return;
			}
		}
	}

	trap_PC_FreeSource( handle );
}

static void UI_LinkCampaignsToArenas( void ) {
	int i;

	for( i = 0; i < uiInfo.campaignCount; i++ ) {
		char *ptr, mapname[128], *mapnameptr;

		// find the mapInfo's that match our mapnames
		uiInfo.campaignList[i].mapCount = 0;

		ptr = uiInfo.campaignList[i].maps;
		while( *ptr ) {
			mapnameptr = mapname;
			while( *ptr && *ptr != ';' ) {
				*mapnameptr++ = *ptr++;
			}
			if( *ptr )
				ptr++;
			*mapnameptr = '\0';
			for( i = 0; i < uiInfo.mapCount; i++ ) {
				if( !Q_stricmp( uiInfo.mapList[i].mapLoadName, mapname ) ) {
					campaignList[*campaignCount].mapInfos[campaignList[*campaignCount].mapCount++] = &uiInfo.mapList[i];
					break;
				}
			}
		}
	}
}*/


/*
===============
UI_LoadCampaigns
===============
*/
void UI_LoadCampaigns( void ) {
	int			numdirs;
	char		filename[128];
	char		dirlist[1024];
	const char *dirptr;
	int			i, j;
	int offset = 0;
	long		hash;
	char		*ch;

	uiInfo.campaignCount = 0;
	memset( &uiInfo.campaignList, 0, sizeof(uiInfo.campaignList) );

	// get all campaigns from .campaign files
	memset(dirlist, 0, sizeof(dirlist));
	numdirs = trap_FS_GetFileList( "scripts", ".campaign", dirlist, 1024 );
	for (i = 0; i < numdirs && uiInfo.campaignCount < MAX_CAMPAIGNS; i++) {
		dirptr = UI_CatalogNextString(dirlist, sizeof(dirlist), &offset);
		if(!dirptr || !*dirptr) break;
		if(!UI_CatalogScriptPath(dirptr, filename, sizeof(filename))) continue;
		UI_LoadCampaignsFromFile(filename);
		//UI_LoadCampaignsFromFile( filename, uiInfo.campaignList, &uiInfo.campaignCount, MAX_CAMPAIGNS );
		//UI_LinkCampaignsToArenas();
	}
//	trap_DPrint( va( "%i campaigns parsed\n", ui_numCampaigns ) ); // JPW NERVE pulled per atvi req
	if (UI_OutOfMemory()) {
		trap_Print( S_COLOR_YELLOW"WARNING: not anough memory in pool to load all campaigns\n" );
	}

	UI_OrderCampaigns();

	// Load the campaign save
	BG_LoadCampaignSave( va( "profiles/%s/campaign.dat", cl_profile.string ), &uiInfo.campaignStatus, cl_profile.string );

	for( i = 0; i < uiInfo.campaignCount; i++ ) {
		// generate hash for campaign shortname
		for( hash = 0, ch = (char *)uiInfo.campaignList[i].campaignShortName; *ch != '\0'; ch++ ) {
			hash += (long)(tolower((unsigned char)*ch))*((ch-uiInfo.campaignList[i].campaignShortName)+119);
		}

		// find the entry in the campaignsave
		for( j = 0; j < uiInfo.campaignStatus.header.numCampaigns; j++ ) {
			if( hash == uiInfo.campaignStatus.campaigns[j].shortnameHash ) {
				uiInfo.campaignList[i].unlocked = qtrue;
				uiInfo.campaignList[i].progress = uiInfo.campaignStatus.campaigns[j].progress;
				uiInfo.campaignList[i].cpsCampaign = &uiInfo.campaignStatus.campaigns[j];
			}
		}

		/*if( !uiInfo.campaignStatus.header.numCampaigns ||
			j == uiInfo.campaignStatus.header.numCampaigns ) {
			// not found, so not unlocked
			uiInfo.campaignList[i].unlocked = qfalse;
			uiInfo.campaignList[i].progress = 0;
			uiInfo.campaignList[i].cpsCampaign = NULL;
		}*/
	}
	UI_SortCatalog(UI_CATALOG_CAMPAIGNS);
}

/*
===============
UI_LoadBotsFromFile
===============
*/
static void UI_LoadBotsFromFile( char *filename ) {
	int				len;
	fileHandle_t	f;
	char			buf[MAX_BOTS_TEXT];

	len = trap_FS_FOpenFile( filename, &f, FS_READ );
	if ( !f ) {
		trap_Print( va( S_COLOR_RED "file not found: %s\n", filename ) );
		return;
	}
	if ( len >= MAX_BOTS_TEXT ) {
		trap_Print( va( S_COLOR_RED "file too large: %s is %i, max allowed is %i", filename, len, MAX_BOTS_TEXT ) );
		trap_FS_FCloseFile( f );
		return;
	}

	trap_FS_Read( buf, len, f );
	buf[len] = 0;
	trap_FS_FCloseFile( f );

	COM_Compress(buf);

	ui_numBots += UI_ParseInfos( buf, MAX_BOTS - ui_numBots, &ui_botInfos[ui_numBots], MAX_BOTS );
}

/*
===============
UI_LoadBots
===============
*/
void UI_LoadBots( void ) {
	vmCvar_t	botsFile;
	int			numdirs;
	char		filename[128];
	char		dirlist[1024];
	char*		dirptr;
	int			i;
	int			dirlen;

	ui_numBots = 0;

	trap_Cvar_Register( &botsFile, "g_botsFile", "", CVAR_INIT|CVAR_ROM );
	if( *botsFile.string ) {
		UI_LoadBotsFromFile(botsFile.string);
	}
	else {
		UI_LoadBotsFromFile("scripts/bots.txt");
	}

	// get all bots from .bot files
	numdirs = trap_FS_GetFileList("scripts", ".bot", dirlist, 1024 );
	dirptr  = dirlist;
	for (i = 0; i < numdirs; i++, dirptr += dirlen+1) {
		dirlen = strlen(dirptr);
		strcpy(filename, "scripts/");
		strcat(filename, dirptr);
		UI_LoadBotsFromFile(filename);
	}
	trap_Print( va( "%i bots parsed\n", ui_numBots ) );
}


/*
===============
UI_GetBotInfoByNumber
===============
*/
char *UI_GetBotInfoByNumber( int num ) {
	if( num < 0 || num >= ui_numBots ) {
		trap_Print( va( S_COLOR_RED "Invalid bot number: %i\n", num ) );
		return NULL;
	}
	return ui_botInfos[num];
}


/*
===============
UI_GetBotInfoByName
===============
*/
char *UI_GetBotInfoByName( const char *name ) {
	int		n;
	char	*value;

	for ( n = 0; n < ui_numBots ; n++ ) {
		value = Info_ValueForKey( ui_botInfos[n], "name" );
		if ( !Q_stricmp( value, name ) ) {
			return ui_botInfos[n];
		}
	}

	return NULL;
}

int UI_GetNumBots() {
	return ui_numBots;
}


char *UI_GetBotNameByNumber( int num ) {
	char *info = UI_GetBotInfoByNumber(num);
	if (info) {
		return Info_ValueForKey( info, "name" );
	}
	return "Sarge";
}
