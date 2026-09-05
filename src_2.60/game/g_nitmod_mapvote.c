#include "g_local.h"
#include "g_nitmod_mapvote.h"
#include "g_nitmod_legacy_cvars.h"

#define NITMOD_MAPVOTE_MAX_MAPS 64
#define NITMOD_MAPVOTE_CHOICES 3

typedef struct {
	char name[MAX_QPATH];
	int id;
	int votes;
	int lastPlayed;
	int timesPlayed;
	int totalVotes;
	int voteEligible;
	qboolean available;
} nitmodMapVoteEntry_t;

static nitmodMapVoteEntry_t mapVoteMaps[NITMOD_MAPVOTE_MAX_MAPS];
static int mapVoteCount;
static int mapVoteVisible[NITMOD_MAPVOTE_MAX_MAPS];
static int mapVoteVisibleCount;
static char mapVoteMapName[MAX_QPATH];
static int G_NITMOD_MapVoteVisibleCount( void );

static int G_NITMOD_MapVoteAge( const nitmodMapVoteEntry_t *entry ) {
	return entry->lastPlayed < 0 ? 9999 : entry->lastPlayed + 1;
}

static qboolean G_NITMOD_MapVoteTiePreferred( const nitmodMapVoteEntry_t *candidate,
	const nitmodMapVoteEntry_t *winner ) {
	int candidateAge = G_NITMOD_MapVoteAge(candidate);
	int winnerAge = G_NITMOD_MapVoteAge(winner);
	/* Original ExitLevel: bit 1 reverses the age comparison used after
	 * equal weighted tallies. */
	return (g_mapVoteFlags.integer & 1) ? candidateAge > winnerAge : candidateAge < winnerAge;
}

static qboolean G_NITMOD_MapNameSafe( const char *name ) {
	int i;
	if( !name || !*name ) return qfalse;
	for( i = 0; name[i]; ++i ) {
		unsigned char c = (unsigned char)name[i];
		if( i >= MAX_QPATH - 1 || !( Q_isalphanumeric(c) || c == '_' || c == '-' || c == '.' ) )
			return qfalse;
	}
	return qtrue;
}

static int G_NITMOD_MapVoteFind( const char *name ) {
	int i;
	for( i = 0; i < mapVoteCount; ++i ) if( !Q_stricmp(mapVoteMaps[i].name, name) ) return i;
	return -1;
}

static void G_NITMOD_MapVoteReadHistory( void ) {
	static char contents[16384];
	fileHandle_t file;
	char *cursor, *token;
	int length, current = -1;

	length = trap_FS_FOpenFile( "mapvoteinfo.cfg", &file, FS_READ );
	if( length <= 0 ) return;
	if( length >= (int)sizeof(contents) ) length = sizeof(contents) - 1;
	trap_FS_Read( contents, length, file );
	trap_FS_FCloseFile( file );
	contents[length] = 0;
	cursor = contents;
	while( *(token = COM_Parse(&cursor)) ) {
		char key[32];
		char *value;
		if( !Q_stricmp(token, "[mapvoteinfo]") ) { current = -1; continue; }
		Q_strncpyz( key, token, sizeof(key) );
		if( *COM_Parse(&cursor) == 0 ) break; /* '=' */
		value = COM_Parse(&cursor);
		if( !*value ) break;
		if( !Q_stricmp(key, "name") ) current = G_NITMOD_MapVoteFind(value);
		else if( current >= 0 && !Q_stricmp(key, "times_played") ) mapVoteMaps[current].timesPlayed = atoi(value);
		else if( current >= 0 && !Q_stricmp(key, "last_played") ) mapVoteMaps[current].lastPlayed = atoi(value);
		else if( current >= 0 && !Q_stricmp(key, "total_votes") ) mapVoteMaps[current].totalVotes = atoi(value);
		else if( current >= 0 && !Q_stricmp(key, "vote_eligible") ) mapVoteMaps[current].voteEligible = atoi(value);
	}
}

static void G_NITMOD_MapVoteWriteHistory( void ) {
	fileHandle_t file;
	char line[256];
	int i;

	trap_FS_FOpenFile( "mapvoteinfo.cfg", &file, FS_WRITE );
	if( !file ) return;
	for( i = 0; i < mapVoteCount; ++i ) {
		Com_sprintf( line, sizeof(line),
			"[mapvoteinfo]\nname             = %s\ntimes_played     = %d\nlast_played      = %d\n"
			"total_votes      = %d\nvote_eligible    = %d\n\n",
			mapVoteMaps[i].name, mapVoteMaps[i].timesPlayed, mapVoteMaps[i].lastPlayed,
			mapVoteMaps[i].totalVotes, mapVoteMaps[i].voteEligible );
		trap_FS_Write( line, strlen(line), file );
	}
	trap_FS_FCloseFile( file );
}

qboolean G_NITMOD_MapVoteActive( void ) {
	return g_gametype.integer == GT_WOLF_MAPVOTE ||
		(g_gametype.integer == GT_WOLF_TDM && (G_NITMOD_LegacyCvarInteger("g_TDMOptions", 0) & 8)) ||
		(g_gametype.integer == GT_WOLF_DM && (g_DMOptions.integer & 0x4000));
}

static qboolean G_NITMOD_MapExcluded( const char *name ) {
	const char *scan = g_excludedMaps.string;
	char token[MAX_QPATH];

	while( *scan ) {
		int length = 0;
		while( *scan == ' ' || *scan == ',' || *scan == ';' ) ++scan;
		while( scan[length] && scan[length] != ' ' && scan[length] != ',' &&
			scan[length] != ';' && length < (int)sizeof(token) - 1 ) ++length;
		if( length ) {
			Q_strncpyz( token, scan, length + 1 );
			if( !Q_stricmp( token, name ) ) return qtrue;
		}
		scan += length;
		if( *scan && length == 0 ) ++scan;
	}
	return qfalse;
}

static void G_NITMOD_MapVoteLoad( void ) {
	char serverInfo[MAX_INFO_STRING];
	char files[8192];
	char current[MAX_QPATH];
	char *file;
	int total, index;

	trap_GetServerinfo( serverInfo, sizeof(serverInfo) );
	Q_strncpyz( current, Info_ValueForKey(serverInfo, "mapname"), sizeof(current) );
	if( mapVoteMapName[0] && !Q_stricmp(mapVoteMapName, current) ) return;

	memset( mapVoteMaps, 0, sizeof(mapVoteMaps) );
	mapVoteCount = 0;
	mapVoteVisibleCount = 0;
	Q_strncpyz( mapVoteMapName, current, sizeof(mapVoteMapName) );
	total = trap_FS_GetFileList( "maps", ".bsp", files, sizeof(files) );
	file = files;
	for( index = 0; index < total && mapVoteCount < NITMOD_MAPVOTE_MAX_MAPS; ++index ) {
		char name[MAX_QPATH];
		int length = strlen(file);
		if( !length ) break;
		Q_strncpyz( name, file, sizeof(name) );
		if( length > 4 && !Q_stricmp(name + length - 4, ".bsp") ) name[length - 4] = 0;
		file += length + 1;
		if( !G_NITMOD_MapNameSafe(name) ) continue;
		Q_strncpyz( mapVoteMaps[mapVoteCount].name, name,
			sizeof(mapVoteMaps[mapVoteCount].name) );
		mapVoteMaps[mapVoteCount].id = mapVoteCount;
		mapVoteMaps[mapVoteCount].lastPlayed = -1;
		mapVoteMaps[mapVoteCount].available = qtrue;
		++mapVoteCount;
	}
	G_NITMOD_MapVoteReadHistory();
	for( index = 0; index < mapVoteCount; ++index ) {
		nitmodMapVoteEntry_t *entry = &mapVoteMaps[index];
		if( G_NITMOD_MapExcluded(entry->name) ) entry->available = qfalse;
		if( !Q_stricmp(entry->name, current) ) {
			entry->lastPlayed = 0;
			if( g_minMapAge.integer >= 0 ) entry->available = qfalse;
		}
		if( entry->lastPlayed >= 0 && entry->lastPlayed <= g_minMapAge.integer ) entry->available = qfalse;
		if( entry->available ) {
			int position = mapVoteVisibleCount++;
			/* Original G_SortMapsByzOrder returns equality for flag bit 8,
			 * retaining the engine VFS enumeration order. */
			while( !(g_mapVoteFlags.integer & 8) && position > 0 &&
				mapVoteMaps[mapVoteVisible[position - 1]].voteEligible > entry->voteEligible ) {
				mapVoteVisible[position] = mapVoteVisible[position - 1];
				--position;
			}
			mapVoteVisible[position] = index;
		}
	}
	for( index = 0; index < G_NITMOD_MapVoteVisibleCount(); ++index )
		++mapVoteMaps[mapVoteVisible[index]].voteEligible;
}

static int G_NITMOD_MapVoteVisibleCount( void ) {
	int count = g_maxMapsVotedFor.integer;
	if( count < 0 ) count = 0;
	if( count > mapVoteVisibleCount ) count = mapVoteVisibleCount;
	return count;
}

void G_NITMOD_MapVoteSendList( gentity_t *ent ) {
	char message[MAX_STRING_CHARS];
	char record[MAX_QPATH + 48];
	int count, i;

	if( !ent || !ent->client || !level.intermissiontime || !G_NITMOD_MapVoteActive() ) return;
	G_NITMOD_MapVoteLoad();
	count = G_NITMOD_MapVoteVisibleCount();
	Com_sprintf( message, sizeof(message), "immaplist %d", (g_mapVoteFlags.integer & 4) != 0 );
	for( i = 0; i < count; ++i ) {
		nitmodMapVoteEntry_t *entry = &mapVoteMaps[mapVoteVisible[i]];
		Com_sprintf( record, sizeof(record), " %s %d %d %d", entry->name,
			entry->id, entry->lastPlayed, entry->totalVotes );
		/* Never emit a truncated record: cgame derives record count from argc. */
		if( strlen(message) + strlen(record) >= sizeof(message) ) break;
		Q_strcat( message, sizeof(message), record );
	}
	trap_SendServerCommand( ent - g_entities, message );
}

void G_NITMOD_MapVoteSendTally( gentity_t *ent ) {
	char message[MAX_STRING_CHARS];
	int count, i;

	if( !ent || !ent->client || !level.intermissiontime || !G_NITMOD_MapVoteActive() ) return;
	G_NITMOD_MapVoteLoad();
	count = G_NITMOD_MapVoteVisibleCount();
	Q_strncpyz( message, "imvotetally", sizeof(message) );
	for( i = 0; i < count; ++i ) Q_strcat( message, sizeof(message), va(" %d", mapVoteMaps[mapVoteVisible[i]].votes) );
	trap_SendServerCommand( ent - g_entities, message );
}

void G_NITMOD_MapVoteCast( gentity_t *ent ) {
	char argument[MAX_TOKEN_CHARS];
	int id, slot = 1, old;

	if( !ent || !ent->client || !level.intermissiontime || !G_NITMOD_MapVoteActive() ) return;
	G_NITMOD_MapVoteLoad();
	if( trap_Argc() < 2 ) return;
	trap_Argv( 1, argument, sizeof(argument) );
	if( !NITMOD_ParseProtocolInteger(argument, &id) ) return;
	if( g_mapVoteFlags.integer & 4 ) {
		if( trap_Argc() < 3 ) return;
		trap_Argv( 2, argument, sizeof(argument) );
		if( !NITMOD_ParseProtocolInteger(argument, &slot) ) return;
	}
	if( slot < 1 || slot > NITMOD_MAPVOTE_CHOICES || id < 0 || id >= mapVoteCount ||
		!mapVoteMaps[id].available ) return;
	for( old = 0; old < NITMOD_MAPVOTE_CHOICES; ++old ) {
		if( old != slot - 1 && ent->client->pers.nitmodMapVotes[old] == id + 1 ) {
			trap_SendServerCommand( ent - g_entities, "print \"^3Can't vote for the same map twice\n\"" );
			return;
		}
	}
	old = ent->client->pers.nitmodMapVotes[slot - 1] - 1;
	if( old >= 0 && old < mapVoteCount ) {
		if( mapVoteMaps[old].votes >= slot ) mapVoteMaps[old].votes -= slot;
		if( mapVoteMaps[old].totalVotes >= slot ) mapVoteMaps[old].totalVotes -= slot;
	}
	ent->client->pers.nitmodMapVotes[slot - 1] = id + 1;
	mapVoteMaps[id].votes += slot;
	mapVoteMaps[id].totalVotes += slot;
	ent->client->ps.eFlags |= EF_VOTED;
}

qboolean G_NITMOD_MapVoteExitLevel( void ) {
	int visible, winner, i, current;

	if( !G_NITMOD_MapVoteActive() ) return qfalse;
	G_NITMOD_MapVoteLoad();
	visible = G_NITMOD_MapVoteVisibleCount();
	if( visible <= 0 ) return qfalse;
	winner = mapVoteVisible[0];
	for( i = 1; i < visible; ++i ) {
		int candidate = mapVoteVisible[i];
		if( mapVoteMaps[candidate].votes > mapVoteMaps[winner].votes ||
			(mapVoteMaps[candidate].votes == mapVoteMaps[winner].votes &&
			 G_NITMOD_MapVoteTiePreferred(&mapVoteMaps[candidate], &mapVoteMaps[winner])) )
			winner = candidate;
	}
	for( i = 0; i < mapVoteCount; ++i ) if( mapVoteMaps[i].lastPlayed >= 0 ) ++mapVoteMaps[i].lastPlayed;
	current = G_NITMOD_MapVoteFind(mapVoteMapName);
	if( current >= 0 ) {
		++mapVoteMaps[current].timesPlayed;
		mapVoteMaps[current].lastPlayed = 0;
	}
	G_NITMOD_MapVoteWriteHistory();
	trap_SendConsoleCommand( EXEC_APPEND, va("map %s\n", mapVoteMaps[winner].name) );
	return qtrue;
}

/* Original CheckIntermissionExit: flag bit 2 requires the same percentage
 * used by intermission readiness to have submitted a map vote. Bots do not
 * participate in either side of the ratio. */
qboolean G_NITMOD_MapVoteExitReady( void ) {
	int i, humans = 0, voters = 0;

	if( !G_NITMOD_MapVoteActive() || !(g_mapVoteFlags.integer & 2) ) return qtrue;
	for( i = 0; i < level.numConnectedClients && i < MAX_CLIENTS; ++i ) {
		int clientNum = level.sortedClients[i];
		gclient_t *client;
		if( clientNum < 0 || clientNum >= MAX_CLIENTS ) continue;
		client = &level.clients[clientNum];
		if( client->pers.connected != CON_CONNECTED || (g_entities[clientNum].r.svFlags & SVF_BOT) ) continue;
		++humans;
		if( client->ps.eFlags & EF_VOTED ) ++voters;
	}
	if( !humans ) return qtrue;
	return (float)voters / (float)humans * 100.0f >= g_intermissionReadyPercent.value;
}
