#include "g_local.h"
#include "g_nitmod_mapvote.h"
#include "g_nitmod_legacy_cvars.h"
#include "nitmod_protocol.h"
#include "nitmod_mapvote_order.h"

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
	int randomOrder;
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

/* Original G_mapvoteinfo_read ELF 0x79590 uses case-sensitive map identity. */
static int G_NITMOD_MapVoteFind( const char *name ) {
	int i;
	for( i = 0; i < mapVoteCount; ++i ) if( !strcmp(mapVoteMaps[i].name, name) ) return i;
	return -1;
}

static void G_NITMOD_MapVoteReadHistory( void ) {
	char *contents;
	fileHandle_t file;
	char *cursor, *token;
	int length, current = -1;

	length = trap_FS_FOpenFile( "mapvoteinfo.cfg", &file, FS_READ );
	if( length < 0 ) return;
	/* Original G_mapvoteinfo_read (0x89400) reads the complete VFS file.
	 * Keep the allocation base separate from COM_Parse's moving cursor. */
	contents = (char *)malloc( (size_t)length + 1 );
	if( !contents ) {
		trap_FS_FCloseFile( file );
		G_Printf( "mapvoteinfo: could not allocate history buffer\n" );
		return;
	}
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
	free( contents );
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
	char pattern[MAX_QPATH + 2];
	/* Original BeginIntermission ELF 0x799e6..0x79a0f searches the
	 * case-sensitive, colon-delimited name, including both colons. */
	Com_sprintf( pattern, sizeof(pattern), ":%s:", name );
	return strstr( g_excludedMaps.string, pattern ) != NULL;
}

static void G_NITMOD_MapVoteLoad( void ) {
	char serverInfo[MAX_INFO_STRING];
	char files[8192];
	char current[MAX_QPATH];
	char *file;
	int total, index;

	trap_GetServerinfo( serverInfo, sizeof(serverInfo) );
	Q_strncpyz( current, Info_ValueForKey(serverInfo, "mapname"), sizeof(current) );
	if( mapVoteMapName[0] && !strcmp(mapVoteMapName, current) ) return;

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
		/* Never index the shortened local copy with the VFS name length. */
		if( length >= sizeof(name) ) {
			file += length + 1;
			continue;
		}
		Q_strncpyz( name, file, sizeof(name) );
		if( length > 4 && !Q_stricmp(name + length - 4, ".bsp") ) name[length - 4] = 0;
		file += length + 1;
		if( !G_NITMOD_MapNameSafe(name) ) continue;
		Q_strncpyz( mapVoteMaps[mapVoteCount].name, name,
			sizeof(mapVoteMaps[mapVoteCount].name) );
		mapVoteMaps[mapVoteCount].id = mapVoteCount;
		mapVoteMaps[mapVoteCount].lastPlayed = -1;
		mapVoteMaps[mapVoteCount].randomOrder = rand();
		mapVoteMaps[mapVoteCount].available = qtrue;
		++mapVoteCount;
	}
	G_NITMOD_MapVoteReadHistory();
	for( index = 0; index < mapVoteCount; ++index ) {
		nitmodMapVoteEntry_t *entry = &mapVoteMaps[index];
		if( G_NITMOD_MapExcluded(entry->name) ) entry->available = qfalse;
		if( !strcmp(entry->name, current) ) {
			++entry->timesPlayed;
			entry->lastPlayed = 0;
			if( g_minMapAge.integer >= 0 ) entry->available = qfalse;
		}
		if( entry->lastPlayed >= 0 && entry->lastPlayed <= g_minMapAge.integer ) entry->available = qfalse;
		/* Original BeginIntermission ages rejected maps here, not at exit. */
		if( !entry->available && entry->lastPlayed >= 0 ) ++entry->lastPlayed;
		if( entry->available ) {
			int position = mapVoteVisibleCount++;
			/* Original G_SortMapsByzOrder returns equality for flag bit 8,
			 * retaining the engine VFS enumeration order. */
			while( position > 0 && NITMOD_MapVoteOrderCompare(g_mapVoteFlags.integer,
				mapVoteMaps[mapVoteVisible[position - 1]].randomOrder, entry->randomOrder) > 0 ) {
				mapVoteVisible[position] = mapVoteVisible[position - 1];
				--position;
			}
			mapVoteVisible[position] = index;
		}
	}
	for( index = 0; index < G_NITMOD_MapVoteVisibleCount(); ++index )
		++mapVoteMaps[mapVoteVisible[index]].voteEligible;
}

void G_NITMOD_MapVoteBeginIntermission( void ) {
	if( !G_NITMOD_MapVoteActive() ) return;
	/* Original BeginIntermission fixes candidate eligibility before the
	 * intermission starts, including a new round on the same map. */
	mapVoteMapName[0] = 0;
	G_NITMOD_MapVoteLoad();
}

static int G_NITMOD_MapVoteVisibleCount( void ) {
	int count = g_maxMapsVotedFor.integer;
	int i, used = (int)strlen("immaplist 0");
	char record[MAX_QPATH + 48];
	if( count < 0 ) count = 0;
	if( count > mapVoteVisibleCount ) count = mapVoteVisibleCount;
	/* List, tally, eligibility accounting and exit selection must agree on
	 * the same complete records that fit the reliable command buffer. */
	for( i = 0; i < count; ++i ) {
		nitmodMapVoteEntry_t *entry = &mapVoteMaps[mapVoteVisible[i]];
		Com_sprintf(record, sizeof(record), " %s %d %d %d", entry->name,
			entry->id, entry->lastPlayed, entry->totalVotes);
		if( used + (int)strlen(record) >= MAX_STRING_CHARS ) return i;
		used += (int)strlen(record);
	}
	return count;
}

void G_NITMOD_MapVoteSendList( gentity_t *ent ) {
	char message[MAX_STRING_CHARS];
	char record[MAX_QPATH + 48];
	int count, i;

	if( !ent || !ent->client || !level.intermissiontime || !G_NITMOD_MapVoteActive() ) return;
	G_NITMOD_MapVoteLoad();
	count = G_NITMOD_MapVoteVisibleCount();
	Com_sprintf( message, sizeof(message), "immaplist %d", g_mapVoteFlags.integer & 4 );
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
	int id, slot = 1, old, argc;

	if( !ent || !ent->client || !level.intermissiontime || !G_NITMOD_MapVoteActive() ) return;
	G_NITMOD_MapVoteLoad();
	/* G_IntermissionMapVote selects single/weighted voting by argument
	 * count, independently of the menu's g_mapVoteFlags setting. */
	argc = trap_Argc();
	if( argc != 2 && argc != 3 ) return;
	trap_Argv( 1, argument, sizeof(argument) );
	if( !NITMOD_ParseProtocolInteger(argument, &id) ) return;
	if( argc == 3 ) {
		trap_Argv( 2, argument, sizeof(argument) );
		if( !NITMOD_ParseProtocolInteger(argument, &slot) ) return;
	}
	if( slot < 1 || slot > NITMOD_MAPVOTE_CHOICES || id < 0 || id >= mapVoteCount ||
		!mapVoteMaps[id].available ) return;
	for( old = 0; old < NITMOD_MAPVOTE_CHOICES; ++old ) {
		if( argc == 3 && old != slot - 1 && ent->client->pers.nitmodMapVotes[old] == id + 1 ) {
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
	int visible, winner, i;

	if( !G_NITMOD_MapVoteActive() ) return qfalse;
	G_NITMOD_MapVoteLoad();
	visible = G_NITMOD_MapVoteVisibleCount();
	if( visible <= 0 ) {
		G_NITMOD_MapVoteWriteHistory();
		return qfalse;
	}
	winner = mapVoteVisible[0];
	for( i = 1; i < visible; ++i ) {
		int candidate = mapVoteVisible[i];
		if( mapVoteMaps[candidate].votes > mapVoteMaps[winner].votes ||
			(mapVoteMaps[candidate].votes == mapVoteMaps[winner].votes &&
			 G_NITMOD_MapVoteTiePreferred(&mapVoteMaps[candidate], &mapVoteMaps[winner])) )
			winner = candidate;
	}
	/* ExitLevel ages only the offered prefix. Eligible maps beyond the
	 * voting limit retain their age; rejected maps were aged during load. */
	for( i = 0; i < visible; ++i ) {
		nitmodMapVoteEntry_t *entry = &mapVoteMaps[mapVoteVisible[i]];
		if( entry->lastPlayed >= 0 ) ++entry->lastPlayed;
	}
	G_NITMOD_MapVoteWriteHistory();
	/* Original ExitLevel (0x8ae72): only a positive winning tally overrides
	 * nextmap. Return to the caller's normal rotation when nobody voted. */
	if( mapVoteMaps[winner].votes <= 0 ) return qfalse;
	/* ExitLevel ELF 0x7ae7a (Ghidra 0x8ae7a) passes g_nextmap.string
	 * to the trailing set: the engine's map command can replace nextmap. */
	trap_SendConsoleCommand( EXEC_APPEND,
		va("map %s;set nextmap %s\n", mapVoteMaps[winner].name, g_nextmap.string) );
	return qtrue;
}

/* Original CheckIntermissionExit: flag bit 2 requires the same percentage
 * used by intermission readiness to have submitted a map vote. Bots do not
 * participate in either side of the ratio. */
qboolean G_NITMOD_MapVoteExitReady( void ) {
	int i, humans = 0, voters = 0;

	/* Original CheckIntermissionExit ELF 0x7bd9e..0x7bdc9 applies this
	 * voted-status gate in every gametype, before ready/timeout checks. */
	if( !(g_mapVoteFlags.integer & 2) ) return qtrue;
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
	/* Original x87 comparison has no Float32 ratio store. The blocking
	 * comparison is strictly less; an unordered threshold does not block. */
	return !((double)voters / (double)humans * 100.0 < (double)g_intermissionReadyPercent.value);
}
