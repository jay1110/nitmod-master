/* Server half of Nitmod's extended ("ncs") configstring protocol. */

#include <string.h>

#include "g_local.h"
#include "g_nitmod_config.h"
#include "g_nitmod_restrictions.h"
#include "nitmod_announcements.h"
#include "nitmod_spree.h"
#include "nitmod_config_store.h"

static nitmodConfigStore_t nitmodConfigStore;
static unsigned int nitmodClientCapabilities[MAX_CLIENTS];
static nitmodSimpleConfig_t nitmodSimpleConfig;
static nitmodGameState_t nitmodGameState;
static nitmodKillSpree_t nitmodKillSpree[MAX_CLIENTS];

static void G_NITMOD_SendConfigString( int clientNum, int index, qboolean sendEmpty );

static qboolean G_NITMOD_IsValidClient( int clientNum ) {
	return clientNum >= 0 && clientNum < MAX_CLIENTS;
}

static void NITMOD_SetValidationReason( char *reason, int reasonSize, const char *message ) {
	if( reason && reasonSize > 0 ) {
		Q_strncpyz( reason, message, reasonSize );
	}
}

void G_NITMOD_ClearConfigStrings( void ) {
	NITMOD_ClearConfigStore( &nitmodConfigStore );
	memset( nitmodClientCapabilities, 0, sizeof( nitmodClientCapabilities ) );
	memset( &nitmodSimpleConfig, 0, sizeof( nitmodSimpleConfig ) );
	memset( &nitmodGameState, 0, sizeof( nitmodGameState ) );
	memset( nitmodKillSpree, 0, sizeof( nitmodKillSpree ) );
}

void G_NITMOD_ResetClient( int clientNum ) {
	if ( G_NITMOD_IsValidClient( clientNum ) ) {
		nitmodClientCapabilities[clientNum] = 0;
		NITMOD_ResetKillSpree( &nitmodKillSpree[clientNum] );
	}
}

void G_NITMOD_CacheClientAddress( gentity_t *ent, const char *address ) {
	char *portSeparator;
	nitmodClientAddress_t *cached;

	if( !ent || !ent->client ) {
		return;
	}
	cached = &ent->client->pers.nitmodAddress;
	if( !address || !address[0] ) {
		memset( cached, 0, sizeof( *cached ) );
		return;
	}
	Q_strncpyz( cached->address, address, sizeof( cached->address ) );
	Q_strncpyz( cached->host, address, sizeof( cached->host ) );
	portSeparator = strchr( cached->host, ':' );
	if( portSeparator ) {
		*portSeparator++ = '\0';
		cached->port = atoi( portSeparator );
	} else {
		cached->port = 0;
	}
}

/* The original NGUID guard sums exactly 33 identifier bytes, accepts only
 * ASCII alphanumerics, and requires the sum to be divisible by 100.  Keep
 * the same validation rule while rejecting short input before reading it. */
qboolean NITMOD_ValidateNGuid( const char *nguid, char *reason, int reasonSize ) {
	int checksum = 0;
	int index;
	unsigned char character;

	if( !nguid || strlen( nguid ) != 33 ) {
		NITMOD_SetValidationReason( reason, reasonSize, "Invalid NGUID length" );
		return qfalse;
	}

	for( index = 0; index < 33; index++ ) {
		character = (unsigned char)nguid[index];
		if( !( ( character >= '0' && character <= '9' ) ||
			( character >= 'A' && character <= 'Z' ) ||
			( character >= 'a' && character <= 'z' ) ) ) {
			NITMOD_SetValidationReason( reason, reasonSize, "NGUID contains invalid characters" );
			return qfalse;
		}
		checksum += character;
	}

	if( checksum % 100 != 0 ) {
		NITMOD_SetValidationReason( reason, reasonSize, "Corrupted NGUID" );
		return qfalse;
	}

	if( reason && reasonSize > 0 ) {
		reason[0] = '\0';
	}
	return qtrue;
}

/* Port of Nitmod's large-text delivery path.  The reference split its shared
 * text buffer into server-command-sized print messages.  This typed variant
 * accepts an explicit buffer and also escapes command delimiters. */
void NITMOD_SendChunkedPrint( int clientNum, const char *text ) {
	char command[MAX_STRING_CHARS];
	int used = 0;
	unsigned char character;

	if( !text || !text[0] ) {
		return;
	}

	command[used++] = 'p';
	command[used++] = 'r';
	command[used++] = 'i';
	command[used++] = 'n';
	command[used++] = 't';
	command[used++] = ' ';
	command[used++] = '"';

	while( ( character = (unsigned char)*text++ ) != '\0' ) {
		if( character == '\n' || character == '\r' || character == '"' || character == '\\' ) {
			if( used + 2 >= (int)sizeof( command ) - 2 ) {
				command[used++] = '"';
				command[used] = '\0';
				trap_SendServerCommand( clientNum, command );
				used = 7;
			}
			command[used++] = '\\';
			command[used++] = character == '\n' || character == '\r' ? 'n' : (char)character;
		} else {
			if( used + 1 >= (int)sizeof( command ) - 2 ) {
				command[used++] = '"';
				command[used] = '\0';
				trap_SendServerCommand( clientNum, command );
				used = 7;
			}
			command[used++] = (char)character;
		}
	}

	command[used++] = '"';
	command[used] = '\0';
	trap_SendServerCommand( clientNum, command );
}

/* Typed port of BG_BuildFilePath.  The original appends exactly one slash
 * only when the non-empty directory does not already end in a separator. */
qboolean NITMOD_BuildFilePath( const char *directory, const char *name,
	const char *extension, char *path, int pathSize ) {
	int directoryLength;
	int requiredLength;
	qboolean needsSeparator;

	if( !directory || !name || !extension || !path || pathSize < 2 ) {
		return qfalse;
	}
	directoryLength = strlen( directory );
	needsSeparator = directoryLength > 0 && directory[directoryLength - 1] != '/' &&
		directory[directoryLength - 1] != '\\';
	requiredLength = directoryLength + ( needsSeparator ? 1 : 0 ) + strlen( name ) + strlen( extension );
	if( requiredLength >= pathSize ) {
		path[0] = '\0';
		return qfalse;
	}
	path[0] = '\0';
	Q_strcat( path, pathSize, directory );
	if( needsSeparator ) {
		Q_strcat( path, pathSize, "/" );
	}
	Q_strcat( path, pathSize, name );
	Q_strcat( path, pathSize, extension );
	return qtrue;
}

void nitrox_ClampFloat( float *value, float minimum, float maximum ) {
	if( !value ) {
		return;
	}
	if( *value < minimum ) {
		*value = minimum;
	} else if( *value > maximum ) {
		*value = maximum;
	}
}

void nitrox_ClampInt( int *value, float minimum, float maximum ) {
	if( !value ) {
		return;
	}
	if( *value < minimum ) {
		*value = minimum >= 0.0f ? (int)( minimum + 0.5f ) : (int)( minimum - 0.5f );
	} else if( *value > maximum ) {
		*value = maximum >= 0.0f ? (int)( maximum + 0.5f ) : (int)( maximum - 0.5f );
	}
}

void nitrox_stripLeadingSpaces( char *text ) {
	char *first;

	if( !text ) {
		return;
	}
	first = text;
	while( *first == ' ' ) {
		first++;
	}
	if( first != text ) {
		memmove( text, first, strlen( first ) + 1 );
	}
}

/* nitmod_SoundEvent constructs an EV_GENERAL_SOUND temp entity at the source
 * gentity's current origin.  ET 2.60's G_Sound is that same typed primitive.
 * The original additionally recycled 32 entities when events were more than
 * 300 ms apart; that allocation optimization does not affect the wire event
 * and is intentionally left to the engine's normal temp-entity lifecycle. */
void NITMOD_PlaySoundEvent( gentity_t *source, int soundIndex ) {
	if( !source || soundIndex <= 0 ) {
		return;
	}
	G_Sound( source, soundIndex );
}

/* Typed port of nitmod_Sound_Global: an EV_GLOBAL_SOUND temp entity carries
 * a pre-registered sound index and is broadcast to every connected client. */
void nitmod_Sound_Global( int soundIndex ) {
	gentity_t *event;

	if( soundIndex <= 0 ) {
		return;
	}
	event = G_TempEntity( vec3_origin, EV_GLOBAL_SOUND );
	event->s.eventParm = soundIndex;
	event->r.svFlags |= SVF_BROADCAST;
}

/* The reference encodes this tuple in a custom event value that collides with
 * ET 2.60's EV_GENERAL_SOUND_VOLUME.  Use a negotiated server command
 * instead: stock clients cannot misinterpret it as a sound, while Nitmod
 * clients receive the same actor/detail/type payload. */
void nitmod_Announce( int actor, int detail, int type ) {
	int clientNum;

	if( actor < 0 || actor >= MAX_CLIENTS || detail < 0 || type < 1 || type > 5 ) {
		return;
	}
	if( NITMOD_AnnouncementCount( type, detail ) < 0 ) {
		return;
	}
	for( clientNum = 0; clientNum < MAX_CLIENTS; clientNum++ ) {
		if( G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_SPREE_EVENTS ) ) {
			trap_SendServerCommand( clientNum, va( "nsp %i %i %i", actor, detail, type ) );
		}
	}
}

/* The recovered G_UpdateKillingSpree advances a positive streak for enemy
 * kills, resets it on death, and emits type 1 on tiers 5, 10, ... 30.  Its
 * negative death-spree and revive-spree branches require custom option Cvars
 * that have no typed ET 2.60 owner, so they are deliberately not inferred. */
void NITMOD_UpdateKillSpree( gentity_t *victim, gentity_t *attacker ) {
	int victimNum;
	int attackerNum;
	int detail;

	if( !victim || !victim->client ) {
		return;
	}
	victimNum = victim->s.number;
	if( !G_NITMOD_IsValidClient( victimNum ) ) {
		return;
	}
	NITMOD_ResetKillSpree( &nitmodKillSpree[victimNum] );

	if( !attacker || !attacker->client || attacker == victim || OnSameTeam( victim, attacker ) ) {
		return;
	}
	attackerNum = attacker->s.number;
	if( !G_NITMOD_IsValidClient( attackerNum ) ) {
		return;
	}
	detail = NITMOD_RecordSpreeKill( &nitmodKillSpree[attackerNum],
		trap_Cvar_VariableIntegerValue( "g_announcer" ) );
	if( detail >= 0 ) {
		nitmod_Announce( attackerNum, detail, 1 );
	}
}

/* The original uses a private event number adjacent to native sound events.
 * A direct port would be unsafe for stock clients, so deliver the recovered
 * hit classifications (team=3, head=4) only after capability negotiation. */
void NITMOD_SendHitSound( int clientNum, int hitType ) {
	if( !G_NITMOD_IsValidClient( clientNum ) ||
		( hitType != NITMOD_HIT_SOUND_TEAM && hitType != NITMOD_HIT_SOUND_HEAD ) ) {
		return;
	}
	if( G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_HIT_SOUNDS ) ) {
		trap_SendServerCommand( clientNum, va( "nhs %i", hitType ) );
	}
}

void NITMOD_SendWeaponLimitMessage( int clientNum, int reason ) {
    if( NITMOD_WeaponLimitText(reason) &&
        G_NITMOD_ClientSupports(clientNum, NITMOD_FEATURE_WEAPON_MESSAGES) ) {
        trap_SendServerCommand(clientNum, va("ncp %i", reason));
    }
}

qboolean G_NITMOD_ClientSupports( int clientNum, unsigned int feature ) {
	return G_NITMOD_IsValidClient( clientNum ) &&
		( nitmodClientCapabilities[clientNum] & feature ) == feature;
}

void G_NITMOD_ClientCapabilities( int clientNum, int protocolVersion, unsigned int capabilities ) {
	if ( !G_NITMOD_IsValidClient( clientNum ) ) {
		return;
	}
	if ( protocolVersion != NITMOD_PROTOCOL_VERSION ) {
		G_DPrintf( "Nitmod: client %i uses unsupported protocol %i\n", clientNum, protocolVersion );
		/* Negotiation failure revokes extensions, not gameplay progress. */
		nitmodClientCapabilities[clientNum] = 0;
		return;
	}

	nitmodClientCapabilities[clientNum] = capabilities & NITMOD_FEATURES_SERVER;
	trap_SendServerCommand( clientNum, va( NITMOD_CAPABILITIES_ACK_COMMAND " %i %u",
		NITMOD_PROTOCOL_VERSION, nitmodClientCapabilities[clientNum] ) );
	G_NITMOD_SendConfigStrings( clientNum );
	nitmod_SimpleCS( clientNum );
	nitmod_SendNCS( clientNum );
	nitmod_SendChargeTimes( clientNum );
	nitmod_SendTeamScores( clientNum );
	if( level.intermissiontime ) {
		nitmod_SendMapEndStats( clientNum );
	}
}

const char *G_NITMOD_ConfigString( int index ) {
	if ( index < 0 || index >= NITMOD_MAX_CONFIGSTRINGS ) {
		G_Error( "G_NITMOD_ConfigString: bad index %i", index );
		return "";
	}
	return nitmodConfigStore.values[index];
}

/* Recovered asset ranges mapped onto ET's authoritative index allocator.
 * Its writer mirrors newly allocated names into NCS. Keeping one allocator
 * prevents native entity/model/sound fields from referring to different
 * assets on stock and negotiated clients. The private original sound +84
 * offset is not part of ET 2.60's native event/index contract. */
int nitrox_CSIndex( const char *name, int start, int count, qboolean create ) {
	if( !name || !name[0] ) {
		return 0;
	}
	if( start == NITMOD_NCS_MODELS && count == NITMOD_NCS_MODEL_COUNT ) {
		return G_FindConfigstringIndex( name, CS_MODELS, MAX_MODELS, create );
	}
	if( start == NITMOD_NCS_SOUNDS && count == NITMOD_NCS_SOUND_COUNT ) {
		return G_FindConfigstringIndex( name, CS_SOUNDS, MAX_SOUNDS, create );
	}
	if( start == NITMOD_NCS_SKINS && count == NITMOD_NCS_SKIN_COUNT ) {
		return G_FindConfigstringIndex( name, CS_SKINS, MAX_CS_SKINS, create );
	}
	if( start == NITMOD_NCS_SHADERS && count == NITMOD_NCS_SHADER_COUNT ) {
		return G_FindConfigstringIndex( name, CS_SHADERS, MAX_CS_SHADERS, create );
	}
	G_Error( "nitrox_CSIndex: unsupported asset range %i %i", start, count );
	return 0;
}

void G_NITMOD_SetConfigString( int index, const char *value ) {
	int clientNum;
	nitmodConfigResult_t result = NITMOD_StoreConfig( &nitmodConfigStore, index, value );
	if ( result == NITMOD_CONFIG_BAD_INDEX ) {
		G_Error( "G_NITMOD_SetConfigString: bad index %i", index );
		return;
	}

	if ( result == NITMOD_CONFIG_UNSAFE ) {
		G_Error( "G_NITMOD_SetConfigString: unsafe value for index %i", index );
		return;
	}
	if ( result == NITMOD_CONFIG_TOO_LONG ) {
		G_Error( "G_NITMOD_SetConfigString: value too long for index %i", index );
		return;
	}
	if ( result == NITMOD_CONFIG_UNCHANGED ) {
		return;
	}

	/* The original qagame transmits the update immediately and also retains a
	 * dirty bit for its end-of-frame recovery pass.  Preserve that observable
	 * behavior: the duplicate is intentional and protects late capability
	 * negotiation during the same server frame. */
	for ( clientNum = 0; clientNum < MAX_CLIENTS; clientNum++ ) {
		if ( G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_NCS ) ) {
			G_NITMOD_SendConfigString( clientNum, index, qtrue );
		}
	}
}

/* Preserve classic engine configstrings for stock clients while exposing
 * their Nitmod equivalents to clients that negotiated NCS. */
void G_NITMOD_MirrorEngineConfigString( int index, const char *value ) {
	int ncsIndex = -1;

	if( index > CS_MODELS && index < CS_MODELS + MAX_MODELS ) {
		ncsIndex = NITMOD_NCS_MODELS + index - CS_MODELS;
	} else if( index > CS_SOUNDS && index < CS_SOUNDS + MAX_SOUNDS ) {
		ncsIndex = NITMOD_NCS_SOUNDS + index - CS_SOUNDS;
	} else if( index > CS_SHADERS && index < CS_SHADERS + MAX_CS_SHADERS ) {
		ncsIndex = NITMOD_NCS_SHADERS + index - CS_SHADERS;
	} else if( index == CS_SHADERSTATE ) {
		ncsIndex = NITMOD_NCS_SHADERSTATE;
	} else if( index > CS_SKINS && index < CS_SKINS + MAX_CS_SKINS ) {
		ncsIndex = NITMOD_NCS_SKINS + index - CS_SKINS;
	} else if( index >= CS_OID_DATA && index < CS_OID_DATA + MAX_OID_TRIGGERS ) {
		ncsIndex = NITMOD_NCS_OBJECTIVES + index - CS_OID_DATA;
	} else if( index >= CS_MULTI_SPAWNTARGETS &&
		index < CS_MULTI_SPAWNTARGETS + MAX_MULTI_SPAWNTARGETS ) {
		ncsIndex = NITMOD_NCS_SPAWNS + index - CS_MULTI_SPAWNTARGETS;
	} else if( index >= CS_FIRETEAMS && index < CS_FIRETEAMS + MAX_FIRETEAMS ) {
		ncsIndex = NITMOD_NCS_FIRETEAMS + index - CS_FIRETEAMS;
	}

	if( ncsIndex >= 0 ) {
		G_NITMOD_SetConfigString( ncsIndex, value );
	}
}

/* Some map-start configstrings are populated by legacy paths that predate the
 * narrow writer hooks.  Take one snapshot after entity spawning so a client
 * negotiating NCS immediately after map load receives the complete baseline.
 * Native configstrings remain authoritative and are never modified here. */
void G_NITMOD_ResyncEngineConfigStrings( void ) {
	char value[MAX_STRING_CHARS];
	int index;

	for( index = 0; index < MAX_CONFIGSTRINGS; index++ ) {
		trap_GetConfigstring( index, value, sizeof( value ) );
		if( strlen( value ) >= NITMOD_CONFIGSTRING_CHARS ) {
			G_Printf( "Nitmod: skipping oversized engine configstring %i during NCS resync\n", index );
			continue;
		}
		G_NITMOD_MirrorEngineConfigString( index, value );
	}
}

static void G_NITMOD_SendConfigString( int clientNum, int index, qboolean sendEmpty ) {
	if ( !sendEmpty && !nitmodConfigStore.values[index][0] ) {
		return;
	}
	trap_SendServerCommand( clientNum, va( NITMOD_CONFIGSTRING_COMMAND " %i \"%s\"\n",
		index, nitmodConfigStore.values[index] ) );
}

void G_NITMOD_SendConfigStrings( int clientNum ) {
	int index;

	if ( !G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_NCS ) ) {
		return;
	}

	for ( index = 0; index < NITMOD_MAX_CONFIGSTRINGS; index++ ) {
		G_NITMOD_SendConfigString( clientNum, index, qfalse );
	}
}

void nitrox_SetConfigstring( int index, const char *value ) {
	G_NITMOD_SetConfigString( index, value );
}

void nitrox_GetConfigstring( int index, char *buffer, int bufferSize ) {
	if ( bufferSize < 1 ) {
		G_Error( "nitrox_GetConfigstring: bufferSize == %i", bufferSize );
		return;
	}
	Q_strncpyz( buffer, G_NITMOD_ConfigString( index ), bufferSize );
}

void nitrox_UpdateConfigstrings( void ) {
	int clientNum;
	int index;

	if ( !nitmodConfigStore.hasDirty ) {
		return;
	}
	for ( index = 0; index < NITMOD_MAX_CONFIGSTRINGS; index++ ) {
		if ( !nitmodConfigStore.dirty[index] ) {
			continue;
		}
		for ( clientNum = 0; clientNum < MAX_CLIENTS; clientNum++ ) {
			if ( G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_NCS ) ) {
				G_NITMOD_SendConfigString( clientNum, index, qtrue );
			}
		}
	}
	NITMOD_ClearConfigDirty( &nitmodConfigStore );
}

void nitmod_SendChargeTimes( int clientNum ) {
	int firstClient = clientNum;
	int lastClient = clientNum;
	int i;

	if( clientNum < 0 ) {
		firstClient = 0;
		lastClient = MAX_CLIENTS - 1;
	}

	for( i = firstClient; i <= lastClient; i++ ) {
		if( G_NITMOD_ClientSupports( i, NITMOD_FEATURE_CHARGE_TIMES ) ) {
			trap_SendServerCommand( i, va( "ct %i %i %i %i %i %i %i %i %i %i",
				level.soldierChargeTime[0], level.soldierChargeTime[1],
				level.medicChargeTime[0], level.medicChargeTime[1],
				level.engineerChargeTime[0], level.engineerChargeTime[1],
				level.lieutenantChargeTime[0], level.lieutenantChargeTime[1],
				level.covertopsChargeTime[0], level.covertopsChargeTime[1] ) );
		}
	}
}

void nitmod_SendMapEndStats( int clientNum ) {
	gclient_t *client;
	unsigned int hits = 0;
	unsigned int bodyshots;
	unsigned int headshots = 0;
	int i;

	if( !G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_MAP_END_STATS ) ) {
		return;
	}

	client = &level.clients[clientNum];
	for( i = 0; i <= WS_MAX; i++ ) {
		/* A syringe hit represents a revive, not a weapon body shot. */
		if( i != WS_SYRINGE ) {
			hits += client->sess.aWeaponStats[i].hits;
		}
		headshots += client->sess.aWeaponStats[i].headshots;
	}
	bodyshots = hits > headshots ? hits - headshots : 0;

	/* Nitmod kept distinct body/head counters.  The base's combat-weapon hit
	 * and headshot counters are maintained on the equivalent damage paths, so
	 * their difference is the portable bodyshot representation. */
	trap_SendServerCommand( clientNum, va( "mes %u %u %i %i %u", bodyshots, headshots,
		client->sess.kills, client->sess.deaths,
		client->sess.aWeaponStats[WS_SYRINGE].hits ) );
}

void nitmod_SetSimpleConfig( const nitmodSimpleConfig_t *config ) {
	if ( !config ) {
		return;
	}
	if ( !memcmp( &nitmodSimpleConfig, config, sizeof( nitmodSimpleConfig ) ) ) {
		return;
	}
	nitmodSimpleConfig = *config;
	nitmod_SimpleCS( -1 );
}

void nitmod_SetGameState( const nitmodGameState_t *state ) {
	if ( !state ) {
		return;
	}
	if ( !memcmp( &nitmodGameState, state, sizeof( nitmodGameState ) ) ) {
		return;
	}
	nitmodGameState = *state;
	nitmod_SendNCS( -1 );
}

/* The original has more custom cvars than the 2.60 base.  Map only the
 * values whose source semantics are known; remaining fields intentionally
 * stay neutral until their gameplay owners are reconstructed. */
void nitmod_RefreshBaseSettings( void ) {
	nitmodSimpleConfig_t simple = nitmodSimpleConfig;
	nitmodGameState_t state = nitmodGameState;

	simple.filterCams = g_filtercams.integer;
	simple.doubleJump = g_doubleJump.integer;
	state.doubleJumpHeight = g_DJHeight.value;
	G_NITMOD_RefreshWeaponSnapshot( &state );
	state.gravity = g_gravity.integer;
	state.maxSoldiers = team_maxSoldiers.integer;
	state.maxMedics = team_maxMedics.integer;
	state.maxEngineers = team_maxEngineers.integer;
	state.maxFieldops = team_maxFieldops.integer;
	state.maxCovertops = team_maxCovertops.integer;
	nitmod_SetSimpleConfig( &simple );
	nitmod_SetGameState( &state );
}

void nitmod_SimpleCS( int clientNum ) {
	int i;

	if ( clientNum >= 0 ) {
		if ( !G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_SIMPLE_CS ) ) {
			return;
		}
		trap_SendServerCommand( clientNum, va( "scs %i %i %i %i %i %i %i %i %i %i %i",
			nitmodSimpleConfig.doubleJump, nitmodSimpleConfig.missileCams,
			nitmodSimpleConfig.war, nitmodSimpleConfig.noReload,
			nitmodSimpleConfig.filterCams, nitmodSimpleConfig.spectatorNames,
			nitmodSimpleConfig.misc, nitmodSimpleConfig.proneDelay,
			nitmodSimpleConfig.dynamiteTimer, nitmodSimpleConfig.crouchStandDelay,
			nitmodSimpleConfig.standCrouchDelay ) );
		return;
	}
	for ( i = 0; i < MAX_CLIENTS; i++ ) {
		nitmod_SimpleCS( i );
	}
}

void nitmod_SendNCS( int clientNum ) {
	int i;

	if ( clientNum >= 0 ) {
		if ( !G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_SIMPLE_CS ) ) {
			return;
		}
		trap_SendServerCommand( clientNum, va( "# %i %i %i %i %i %i %i %i %i %i %i %i %i %i %.3f %i %i %i %i %i",
			nitmodGameState.panzerRestriction, nitmodGameState.maxPanzers,
			nitmodGameState.maxMG42s, nitmodGameState.maxFlamers,
			nitmodGameState.maxMortars, nitmodGameState.maxRifleGrenades,
			nitmodGameState.adrenaline, nitmodGameState.keepAwards,
			nitmodGameState.maxSoldiers, nitmodGameState.maxMedics,
			nitmodGameState.maxEngineers, nitmodGameState.maxFieldops,
			nitmodGameState.maxCovertops, nitmodGameState.weapons,
			nitmodGameState.doubleJumpHeight, nitmodGameState.tdmOptions,
			nitmodGameState.dmOptions, nitmodGameState.gravity,
			nitmodGameState.mapCount, nitmodGameState.resetXPMapCount ) );
		return;
	}
	for ( i = 0; i < MAX_CLIENTS; i++ ) {
		nitmod_SendNCS( i );
	}
}

void nitmod_SendTeamScores( int clientNum ) {
	if ( !G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_TEAM_SCORES ) ) {
		return;
	}
	trap_SendServerCommand( clientNum, va( "tsc %i %i",
		level.teamScores[TEAM_AXIS], level.teamScores[TEAM_ALLIES] ) );
}

void nitmod_TeamScores( void ) {
	int clientNum;

	for ( clientNum = 0; clientNum < MAX_CLIENTS; clientNum++ ) {
		nitmod_SendTeamScores( clientNum );
	}
}

void nitmod_ObjectiveEvent( int type, int detail, int objective, int actor, int meansOfDeath ) {
	int clientNum;

	if ( actor < 0 || actor >= MAX_CLIENTS ) {
		return;
	}
	for ( clientNum = 0; clientNum < MAX_CLIENTS; clientNum++ ) {
		if ( G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_OBJECTIVES ) ) {
			trap_SendServerCommand( clientNum, va( "ob %i %i %i %i %i",
				type, detail, objective, actor, meansOfDeath ) );
		}
	}
}
