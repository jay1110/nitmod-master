/* Server half of Nitmod's extended ("ncs") configstring protocol. */

#include <string.h>
#include <limits.h>

#include "g_local.h"
#include "g_nitmod_config.h"
#include "g_nitmod_abilities.h"
#include "g_nitmod_hudstats.h"
#include "g_nitmod_restrictions.h"
#include "g_nitmod_legacy_cvars.h"
#include "nitmod_announcements.h"
#include "nitmod_spree.h"
#include "nitmod_config_store.h"
#include "nitmod_clamp.h"
#include "nitmod_lua_events.h"

static nitmodConfigStore_t nitmodConfigStore;
static unsigned int nitmodClientCapabilities[MAX_CLIENTS];
/* Original local session latches are independent of native port features. */
static qboolean nitmodLegacyHandshake[MAX_CLIENTS];
static qboolean nitmodLegacyStateReady[MAX_CLIENTS];
static nitmodSimpleConfig_t nitmodSimpleConfig;
static nitmodGameState_t nitmodGameState;
static int nitmodMapCycleCount;
static nitmodKillSpree_t nitmodKillSpree[MAX_CLIENTS];
static int nitmodBestKillSpree[MAX_CLIENTS];
int G_NITMOD_CurrentKillSpree(int clientNum) { return clientNum>=0 && clientNum<MAX_CLIENTS?nitmodKillSpree[clientNum].kills:0; }
int G_NITMOD_BestKillSpree(int clientNum) {
    gclient_t *client;
    if(clientNum<0 || clientNum>=MAX_CLIENTS || !(client=g_entities[clientNum].client)) return 0;
    return client->nitmodLuaPersistant[14]>client->nitmodLuaPersistant[15]?
        client->nitmodLuaPersistant[14]:client->nitmodLuaPersistant[15];
}

static void G_NITMOD_SendConfigString( int clientNum, int index, qboolean sendEmpty );

int G_NITMOD_DynamiteTimer( void ) {
	int timer = G_NITMOD_LegacyCvarInteger("n_dynamiteTimer", 30000);
	nitrox_ClampInt(&timer, 5000.0f, 60000.0f);
	return timer;
}

static qboolean G_NITMOD_IsValidClient( int clientNum ) {
	return clientNum >= 0 && clientNum < MAX_CLIENTS;
}

static void NITMOD_SetValidationReason( char *reason, int reasonSize, const char *message ) {
	if( reason && reasonSize > 0 ) {
		Q_strncpyz( reason, message, reasonSize );
	}
}

void G_NITMOD_ClearConfigStrings( void ) {
	G_NITMOD_ResetHudStats(-1);
	NITMOD_ClearConfigStore( &nitmodConfigStore );
	memset( nitmodClientCapabilities, 0, sizeof( nitmodClientCapabilities ) );
	memset( nitmodLegacyHandshake, 0, sizeof( nitmodLegacyHandshake ) );
	memset( nitmodLegacyStateReady, 0, sizeof( nitmodLegacyStateReady ) );
	memset( &nitmodSimpleConfig, 0, sizeof( nitmodSimpleConfig ) );
	memset( &nitmodGameState, 0, sizeof( nitmodGameState ) );
	memset( nitmodKillSpree, 0, sizeof( nitmodKillSpree ) );
	memset( nitmodBestKillSpree, 0, sizeof( nitmodBestKillSpree ) );
}

/* Gameplay resets happen on ClientBegin/team changes as well as reconnects.
 * Transport negotiation belongs to the connection and survives those begins. */
void G_NITMOD_ResetGameplayClient( int clientNum ) {
	if( G_NITMOD_IsValidClient(clientNum) ) {
		NITMOD_ResetKillSpree(&nitmodKillSpree[clientNum]);
		nitmodBestKillSpree[clientNum]=0;
	}
}
void G_NITMOD_ResetClient( int clientNum ) {
	G_NITMOD_ResetHudStats(clientNum);
	if( G_NITMOD_IsValidClient(clientNum) ) {
		nitmodClientCapabilities[clientNum]=0;
		nitmodLegacyHandshake[clientNum]=nitmodLegacyStateReady[clientNum]=qfalse;
		G_NITMOD_ResetGameplayClient(clientNum);
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

/* Original ClientConnect IP gate and IsFakepConnection (ELF 0x4ce20).
 * Retain the original digit/dot and pre-port comparison rules. */
const char *G_NITMOD_CheckConnection(int clientNum, const char *userinfo,
    qboolean isBot) {
    char address[MAX_INFO_STRING], host[16], *port;
    int i, dots = 0, count = 1, limit;
    if (isBot || G_NITMOD_IsDemoClient(clientNum,
        trap_Cvar_VariableIntegerValue("sv_demoState"),
        trap_Cvar_VariableIntegerValue("sv_demoClients"))) return NULL;
    Q_strncpyz(address, Info_ValueForKey(userinfo, "ip"), sizeof(address));
    Q_strncpyz(host, address, sizeof(host));
    port = strchr(host, ':');
    if (port) *port = '\0';
    if (G_NITMOD_LegacyCvarInteger("g_IPChecks", 1) && strcmp(host, "localhost")) {
        for (i = 0; host[i]; ++i) {
            if (host[i] == '.') ++dots;
            else if (host[i] < '0' || host[i] > '9') break;
        }
        if (!host[0] || host[i] || dots != 3) {
            G_LogPrintf("[DROPCLIENT] Client %d Invalid IP Address (%s)\n", clientNum, host);
            return va("Invalid IP Address (%s)", host);
        }
    }
    if (!Info_ValueForKey(userinfo, "rate")[0]) {
        G_LogPrintf("[DROPCLIENT] Client %d Invalid connection\n", clientNum);
        return "Invalid connection!";
    }
    if (!strcmp(address, "localhost")) return NULL;
    limit = trap_Cvar_VariableIntegerValue("ip_max_clients");
    if (limit <= 0) limit = 3;
    for (i = 0; i < level.maxclients; ++i) {
        const char *other, *leftPort, *rightPort;
        size_t length;
        if (i == clientNum || !g_entities[i].client ||
            g_entities[i].client->pers.connected == CON_DISCONNECTED) continue;
        other = g_entities[i].client->pers.nitmodAddress.address;
        leftPort = strchr(address, ':');
        rightPort = strchr(other, ':');
        if (leftPort || rightPort) {
            length = leftPort ? (size_t)(leftPort - address) : strlen(address) + 1;
            if (rightPort && (size_t)(rightPort - other) < length)
                length = (size_t)(rightPort - other);
            if (strncmp(address, other, length)) continue;
        } else if (strcmp(address, other)) continue;
        if (++count > limit) {
            G_LogPrintf("[DROPCLIENT] Too many connections from %s\n", address);
            return va("Only %d connection%s per IP %s allowed on this server!",
                limit, limit == 1 ? "" : "s", limit == 1 ? "is" : "are");
        }
    }
    return NULL;
}

/* ClientUserinfoChanged requires 32 characters. The original checksum reads
 * 33 bytes INCLUDING the terminating zero, not 33 identifier characters. */
qboolean NITMOD_ValidateNGuid( const char *nguid, char *reason, int reasonSize ) {
	int checksum = 0;
	int index;
	unsigned char character;

	if( !nguid || strlen( nguid ) != 32 ) {
		NITMOD_SetValidationReason( reason, reasonSize, "Invalid NGUID length" );
		return qfalse;
	}

	for( index = 0; index < 32; index++ ) checksum += (unsigned char)nguid[index];
	if( checksum % 100 != 0 ) {
		NITMOD_SetValidationReason( reason, reasonSize, "Corrupted NGUID" );
		return qfalse;
	}
	for( index = 0; index < 32; index++ ) {
		character = (unsigned char)nguid[index];
		if( !( ( character >= '0' && character <= '9' ) ||
			( character >= 'A' && character <= 'Z' ) ||
			( character >= 'a' && character <= 'z' ) ) ) {
			NITMOD_SetValidationReason( reason, reasonSize, "NGUID contains invalid characters" );
			return qfalse;
		}
	}

	if( reason && reasonSize > 0 ) {
		reason[0] = '\0';
	}
	return qtrue;
}

/* The engine's quoted command arguments preserve literal newlines and
 * backslashes; they do not decode C-style escapes. Keep print payloads literal.
 * Quotes cannot be escaped in this protocol, so display them as apostrophes. */
void NITMOD_SendChunkedPrint( int clientNum, const char *text ) {
    char command[MAX_STRING_CHARS];
    int used = 7;
    if(!text || !*text) return;
    memcpy(command, "print \"", 7);
    while(*text) {
        if(used >= (int)sizeof(command) - 2) {
            command[used++] = '"'; command[used] = 0;
            trap_SendServerCommand(clientNum, command); used = 7;
        }
        command[used++] = *text == '"' ? '\'' : *text;
        ++text;
    }
    command[used++] = '"'; command[used] = 0;
    trap_SendServerCommand(clientNum, command);
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
	NITMOD_ClampFloating(value, minimum, maximum);
}

void nitrox_ClampInt( int *value, float minimum, float maximum ) {
	NITMOD_ClampInteger(value, minimum, maximum);
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

/* Original nitmod_SoundEvent uses private wire event 100, whose eventParm
 * addresses the original fixed 84-sound bank. Keep the shared source tree ABI-safe by
 * emitting a named internal event; cgame accepts both this event from the
 * reconstructed qagame and wire 100 from an original Nitmod server. */
void NITMOD_PlaySoundEvent( gentity_t *source, int soundIndex ) {
	gentity_t *event;

	if( !source || soundIndex <= 0 ) {
		return;
	}
	event = G_TempEntity( source->r.currentOrigin, EV_NITMOD_SOUND );
	event->s.eventParm = soundIndex;
}

/* Original event 103 plays at each recipient's client, without attenuation.
 * Use the existing encoded-event envelope to keep eType within eight bits. */
void nitmod_Sound_Global( int soundIndex ) {
	gentity_t *event;

	if( soundIndex <= 0 ) {
		return;
	}
	event = G_TempEntity( vec3_origin, EV_NITMOD_LUA_FIRST );
	event->s.event = NITMOD_LuaEventEncode(103);
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

/* Original persistent spree transitions, including negative death sequences.
 * Existing positive announcement transport stays at tiers 5..30. */
void NITMOD_UpdateKillSpree( gentity_t *victim, gentity_t *attacker ) {
	int victimNum;
	int attackerNum;
	int detail;
	int flags = trap_Cvar_VariableIntegerValue("g_announcer");

	if( !victim || !victim->client ) {
		return;
	}
	victimNum = victim->s.number;
	if( !G_NITMOD_IsValidClient( victimNum ) ) {
		return;
	}
    {
        int previous=victim->client->nitmodLuaPersistant[15];
        int next=previous>0?0:(int)((unsigned int)previous-1u);
        if(previous>=5 && (flags&32)) {
            if(attacker && attacker->client && attacker!=victim)
                trap_SendServerCommand(-1,va("chat \"%s^g's killing spree ended by %s%s ^gafter ^2%d ^gkills!\" -2",
                    victim->client->pers.netname,OnSameTeam(victim,attacker)?"^1TEAMMATE ^7":"^7",attacker->client->pers.netname,previous));
            else trap_SendServerCommand(-1,va("chat \"%s ^gended his own killing spree after ^2%d ^gkills!\" -2",victim->client->pers.netname,previous));
        }
        if((flags&2) && next>=-30 && next<=-10 && next%10==0)
            nitmod_Announce(victimNum,-next/10-1,2);
        victim->client->nitmodLuaPersistant[15]=next;
        if(previous>0 && previous>victim->client->nitmodLuaPersistant[14]) victim->client->nitmodLuaPersistant[14]=previous;
    }
	NITMOD_ResetKillSpree( &nitmodKillSpree[victimNum] );

	if( !attacker || !attacker->client || attacker == victim || OnSameTeam( victim, attacker ) ) {
		return;
	}
	attackerNum = attacker->s.number;
	if( !G_NITMOD_IsValidClient( attackerNum ) ) {
		return;
	}
    if(attacker->client->nitmodLuaPersistant[15]<=-10 && (flags&64)) {
        /* Unsigned magnitude also preserves the original INT_MIN edge. */
        trap_SendServerCommand(-1,va("chat \"%s^g's death spree ended after ^1%d ^gdeaths!\" -2",
            attacker->client->pers.netname,(int)(0u-(unsigned int)attacker->client->nitmodLuaPersistant[15])));
    }
    /* Lua can modify the original persistent spree directly. */
    nitmodKillSpree[attackerNum].kills=attacker->client->nitmodLuaPersistant[15];
    if(nitmodKillSpree[attackerNum].kills<0) nitmodKillSpree[attackerNum].kills=0;
	detail = NITMOD_RecordSpreeKill( &nitmodKillSpree[attackerNum],
		flags );
	attacker->client->nitmodLuaPersistant[15]=nitmodKillSpree[attackerNum].kills;
	if(nitmodKillSpree[attackerNum].kills>nitmodBestKillSpree[attackerNum])
		nitmodBestKillSpree[attackerNum]=nitmodKillSpree[attackerNum].kills;
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

/* Only recovered text protocols may use the legacy session. In particular,
 * this never grants NITMOD_ClientSupports for native-only extensions. */
static qboolean G_NITMOD_ReceivesOriginalState(int clientNum,unsigned int feature) {
	if(G_NITMOD_ClientSupports(clientNum,feature)) return qtrue;
	if(!G_NITMOD_IsValidClient(clientNum) || !g_entities[clientNum].client ||
	   g_entities[clientNum].client->pers.connected!=CON_CONNECTED ||
	   (g_entities[clientNum].r.svFlags&SVF_BOT) ||
	   g_entities[clientNum].client->pers.nitmodDemoClient) return qfalse;
	if(feature==NITMOD_FEATURE_NCS) return nitmodLegacyHandshake[clientNum];
	return nitmodLegacyStateReady[clientNum] &&
		(feature==NITMOD_FEATURE_SIMPLE_CS || feature==NITMOD_FEATURE_CHARGE_TIMES ||
		 feature==NITMOD_FEATURE_TEAM_SCORES);
}

/* Original ClientCommand local exchange: imhere -> handshake, followed by
 * rhs/handshake/getdata. No remote registration or capability attestation. */
int G_NITMOD_LegacySessionCommand(int clientNum,const char *command) {
	int i;
	if(!command || (strcmp(command,"imhere") && strcmp(command,"rhs") &&
	   strcmp(command,"handshake") && strcmp(command,"getdata"))) return 0;
	if(!G_NITMOD_IsValidClient(clientNum) || !g_entities[clientNum].client ||
	   g_entities[clientNum].client->pers.connected!=CON_CONNECTED ||
	   (g_entities[clientNum].r.svFlags&SVF_BOT) ||
	   g_entities[clientNum].client->pers.nitmodDemoClient) return 1;
	if(!strcmp(command,"imhere")) {
		trap_SendServerCommand(clientNum,"handshake"); return 1;
	}
	if(!strcmp(command,"rhs")) { nitmodLegacyHandshake[clientNum]=qfalse; return 1; }
	if(!strcmp(command,"handshake")) {
		if(!nitmodLegacyHandshake[clientNum]) {
			nitmodLegacyHandshake[clientNum]=qtrue;
			G_NITMOD_SendConfigStrings(clientNum);
		}
		return 1;
	}
	/* getdata is valid independently of the ncs handshake latch. */
	nitmodLegacyStateReady[clientNum]=qtrue;
	if(g_gametype.integer==GT_WOLF_TDM) {
		for(i=0;i<MAX_CLIENTS;++i) if(nitmodLegacyStateReady[i] &&
			G_NITMOD_ReceivesOriginalState(i,NITMOD_FEATURE_TEAM_SCORES))
			nitmod_SendTDMScoreLimit(i);
	}
	nitmod_SimpleCS(clientNum);
	nitmod_SendNCS(clientNum);
	nitmod_SendSkillLevels(clientNum);
	nitmod_SendChargeTimes(clientNum);
	nitmod_TeamScores();
	return 1;
}

void G_NITMOD_ClientCapabilities( int clientNum, int protocolVersion, unsigned int capabilities ) {
	if ( !G_NITMOD_IsValidClient( clientNum ) ) {
		return;
	}
	nitmodLegacyHandshake[clientNum] = nitmodLegacyStateReady[clientNum] = qfalse;
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
	if(g_gametype.integer == GT_WOLF_TDM) nitmod_SendTDMScoreLimit(clientNum);
	nitmod_SendSkillLevels( clientNum );
	nitmod_SendClassHealth( clientNum );
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
		if ( G_NITMOD_ReceivesOriginalState( clientNum, NITMOD_FEATURE_NCS ) ) {
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

	if ( !G_NITMOD_ReceivesOriginalState( clientNum, NITMOD_FEATURE_NCS ) ) {
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
			if ( G_NITMOD_ReceivesOriginalState( clientNum, NITMOD_FEATURE_NCS ) ) {
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
		if(G_NITMOD_ClientSupports(i,NITMOD_FEATURE_PACK_CHARGE)) {
			/* Original noCharge/war affect payment, never the prediction gate. */
			trap_SendServerCommand(i,"npcc 0");
		}
		if( G_NITMOD_ReceivesOriginalState( i, NITMOD_FEATURE_CHARGE_TIMES ) ) {
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
	/* Publish the negotiated prediction inputs. Original noCharge
	 * suppresses payment only; it does not alter charge times or this gate. */
	nitmod_SendChargeTimes(-1);

	simple.filterCams = g_filtercams.integer;
	simple.spectatorNames = g_spectatorNames.integer;
	simple.doubleJump = g_doubleJump.integer;
	simple.missileCams = G_NITMOD_LegacyCvarInteger( "g_missileCams", 0 );
	simple.war = G_NITMOD_ConfiguredWarMode();
	simple.noReload = G_NITMOD_ConfiguredNoReload();
	simple.misc = G_NITMOD_LegacyCvarInteger( "g_misc", 0 );
	simple.proneDelay = G_NITMOD_LegacyCvarInteger( "n_proneDelay", 0 );
	simple.dynamiteTimer = G_NITMOD_DynamiteTimer();
	simple.crouchStandDelay = G_NITMOD_LegacyCvarInteger( "n_crouchStandDelay", 0 );
	simple.standCrouchDelay = G_NITMOD_LegacyCvarInteger( "n_standCrouchDelay", 0 );
	state.doubleJumpHeight = g_DJHeight.value;
	G_NITMOD_RefreshWeaponSnapshot( &state );
	state.gravity = g_gravity.integer;
	state.mapCount = G_NITMOD_MapCyclePresentedCount();
	state.resetXPMapCount = (g_XPSave.integer & 4) ? 0 : g_resetXPMapCount.integer;
	state.dmOptions = g_DMOptions.integer;
	state.tdmOptions = G_NITMOD_LegacyCvarInteger( "g_TDMOptions", 0 );
	state.adrenaline = G_NITMOD_LegacyCvarInteger( "g_adrenaline", 0 );
	state.keepAwards = G_NITMOD_LegacyCvarInteger( "g_skills", 0 );
	state.maxSoldiers = team_maxSoldiers.integer;
	state.maxMedics = team_maxMedics.integer;
	state.maxEngineers = team_maxEngineers.integer;
	state.maxFieldops = team_maxFieldops.integer;
	state.maxCovertops = team_maxCovertops.integer;
	nitmod_SetSimpleConfig( &simple );
	nitmod_SetGameState( &state );
}

/* Original ExitLevel permits a nonzero limit, including negative values,
 * in the three modes that actually run map voting. */
qboolean G_NITMOD_MapCycleEnabled( void ) {
	return g_resetXPMapCount.integer != 0 &&
		(g_gametype.integer == GT_WOLF_MAPVOTE ||
		 (g_gametype.integer == GT_WOLF_TDM &&
		  (G_NITMOD_LegacyCvarInteger("g_TDMOptions", 0) & 8)) ||
		 (g_gametype.integer == GT_WOLF_DM && (g_DMOptions.integer & 0x4000)));
}

/* Original G_InitWorldSession 0xb8305 / G_WriteSessionData preserve the
 * signed raw counter. Initialization decides when it is actually reset. */
void G_NITMOD_SetMapCycleCount( int count ) {
	nitmodMapCycleCount = count;
}

int G_NITMOD_MapCycleCount( void ) {
	return nitmodMapCycleCount;
}

/* Original nitmod_SendNCS 0x10cef0 normalizes only the presented value,
 * independently of gametype and XPSave bit 4 (which hides only the limit). */
int G_NITMOD_MapCyclePresentedCount( void ) {
	return nitmodMapCycleCount >= g_resetXPMapCount.integer ? 0 : nitmodMapCycleCount;
}

/* Original G_InitGame 0x7fd3d..0x7fd5a: this XP exception belongs only to
 * GT_WOLF_MAPVOTE. Merely checking it must not reset the raw counter. */
qboolean G_NITMOD_MapCycleResetsXP( void ) {
	return g_gametype.integer == GT_WOLF_MAPVOTE && !(g_XPSave.integer & 4) &&
		g_resetXPMapCount.integer != 0 &&
		(nitmodMapCycleCount == 0 || nitmodMapCycleCount >= g_resetXPMapCount.integer);
}

void G_NITMOD_AdvanceMapCycle( void ) {
	if(!G_NITMOD_MapCycleEnabled()) return;
	/* Match the original 32-bit increment without signed C overflow. */
	if(nitmodMapCycleCount == INT_MAX) nitmodMapCycleCount = INT_MIN;
	else ++nitmodMapCycleCount;
	nitmod_RefreshBaseSettings();
}

void nitmod_SimpleCS( int clientNum ) {
	int i;

	if ( clientNum >= 0 ) {
		if ( !G_NITMOD_ReceivesOriginalState( clientNum, NITMOD_FEATURE_SIMPLE_CS ) ) {
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
		if ( !G_NITMOD_ReceivesOriginalState( clientNum, NITMOD_FEATURE_SIMPLE_CS ) ) {
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

/* z1 is independent from # and tsc. Native clients receive the original
 * text format under the existing team-score capability. */
void nitmod_SendTDMScoreLimit(int clientNum) {
	int i;
	if(clientNum == -1) {
		for(i = 0; i < MAX_CLIENTS; ++i) nitmod_SendTDMScoreLimit(i);
		return;
	}
	if(!G_NITMOD_ReceivesOriginalState(clientNum, NITMOD_FEATURE_TEAM_SCORES)) return;
	trap_SendServerCommand(clientNum, va("z1 %i", G_NITMOD_LegacyCvarInteger("g_TDMScore", 500)));
}

void nitmod_SendTeamScores( int clientNum ) {
	if ( !G_NITMOD_ReceivesOriginalState( clientNum, NITMOD_FEATURE_TEAM_SCORES ) ) {
		return;
	}
	trap_SendServerCommand( clientNum, va( "tsc %i %i",
		level.teamScores[TEAM_AXIS], level.teamScores[TEAM_ALLIES] ) );
}

void nitmod_SendSkillLevels( int clientNum ) {
	static const char *keys[SK_NUM_SKILLS] = { "B", "E", "M", "F", "L", "S", "C" };
	static const char *names[SK_NUM_SKILLS] = {
		"skill_battlesense", "skill_engineer", "skill_medic", "skill_fieldops",
		"skill_lightweapons", "skill_soldier", "skill_covertops"
	};
	char info[MAX_INFO_STRING] = "";
	char value[MAX_CVAR_VALUE_STRING];
	int skill;
	if(!G_NITMOD_ReceivesOriginalState(clientNum, NITMOD_FEATURE_SIMPLE_CS)) return;
	for(skill = 0; skill < SK_NUM_SKILLS; ++skill) {
		trap_Cvar_VariableStringBuffer(names[skill], value, sizeof(value));
		Info_SetValueForKey(info, keys[skill], value);
	}
	trap_SendServerCommand(clientNum, va("sl %s", info));
}

/* Original Nitmod publishes this table through private configstring 39.
 * Native ET 2.60 owns that slot as CS_FILTERCAMS, so reconstructed peers use
 * a negotiated command and leave the engine configstring namespace intact. */
void nitmod_SendClassHealth( int clientNum ) {
	int i;

	if( clientNum < 0 ) {
		for( i = 0; i < MAX_CLIENTS; ++i ) {
			nitmod_SendClassHealth( i );
		}
		return;
	}
	if( !G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_CLASS_HEALTH ) ) {
		return;
	}
	trap_SendServerCommand( clientNum, va( "nch %i %i %i %i %i",
		G_NITMOD_ClassMaxHealth( PC_SOLDIER ),
		G_NITMOD_ClassMaxHealth( PC_MEDIC ),
		G_NITMOD_ClassMaxHealth( PC_ENGINEER ),
		G_NITMOD_ClassMaxHealth( PC_FIELDOPS ),
		G_NITMOD_ClassMaxHealth( PC_COVERTOPS ) ) );
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
	/* Original 0x10c3ba..0x10c46c: objective actions count independently
	 * of recipients, skill XP and g_misc. Original MOD21/22/25 are native
	 * DYNAMITE/AIRSTRIKE/ARTY. Preserve the separate two pers counters. */
	if ( (type == 0 || type == 4) && detail >= 0 && detail <= 4 &&
		g_entities[actor].client ) {
		int *counter = NULL;
		if ( detail <= 2 || meansOfDeath == MOD_DYNAMITE ) {
			counter = &g_entities[actor].client->pers.nitmodEngineerObjectives;
		} else if ( meansOfDeath == MOD_AIRSTRIKE || meansOfDeath == MOD_ARTY ) {
			counter = &g_entities[actor].client->pers.nitmodAmmoSupplied;
		}
		if ( counter ) {
			*counter = *counter == INT_MAX ? INT_MIN : *counter + 1;
		}
	}
	for ( clientNum = 0; clientNum < MAX_CLIENTS; clientNum++ ) {
		if ( G_NITMOD_ClientSupports( clientNum, NITMOD_FEATURE_OBJECTIVES ) ) {
			trap_SendServerCommand( clientNum, va( "ob %i %i %i %i %i",
				type, detail, objective, actor, meansOfDeath ) );
		}
	}
}
