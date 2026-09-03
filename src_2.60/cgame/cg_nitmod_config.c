/* Client half of Nitmod's extended configstring protocol. */

#include <string.h>
#include <stdlib.h>

#include "cg_local.h"
#include "cg_nitmod_config.h"
#include "../game/nitmod_announcements.h"

static char nitmodConfigStrings[NITMOD_MAX_CONFIGSTRINGS][NITMOD_CONFIGSTRING_CHARS];
static unsigned int nitmodServerCapabilities;
static nitmodSimpleConfig_t nitmodSimpleConfig;
static nitmodGameState_t nitmodGameState;
static qboolean nitmodClassLimitsReceived;

int NITMOD_ParseLatchedClass(const char *info, int currentClass) {
	int value;
	const char *text = Info_ValueForKey(info, "lc");
	if(!NITMOD_ParseProtocolSigned(text, &value) || value < PC_SOLDIER || value > PC_COVERTOPS)
		return currentClass;
	return value;
}

qboolean NITMOD_ClassIsDisabled(int team, int playerClass) {
	int limits[5], i, count = 0, maximum;
	if(!nitmodClassLimitsReceived || team == TEAM_SPECTATOR ||
		playerClass < PC_SOLDIER || playerClass > PC_COVERTOPS) return qfalse;
	limits[0] = nitmodGameState.maxSoldiers; limits[1] = nitmodGameState.maxMedics;
	limits[2] = nitmodGameState.maxEngineers; limits[3] = nitmodGameState.maxFieldops;
	limits[4] = nitmodGameState.maxCovertops;
	maximum = limits[playerClass];
	if(maximum == -1) return qfalse;
	for(i = 0; i < cgs.maxclients && i < MAX_CLIENTS; ++i) {
		const clientInfo_t *client = &cgs.clientinfo[i];
		if(i == cg.clientNum || !client->infoValid || client->team != team) continue;
		if(client->cls == playerClass || client->latchedClass == playerClass) ++count;
	}
	return count >= maximum;
}
static nitmodMapEndStats_t nitmodMapEndStats;
static nitmodObjectiveEvent_t nitmodLastObjectiveEvent;
vmCvar_t nitmodHitSounds;
vmCvar_t cg_pmSounds;
vmCvar_t cg_shoveSounds;
vmCvar_t cg_noGreetingSounds;
vmCvar_t cg_drawBanners;
static char nitmodBanner[MAX_STRING_CHARS];
static int nitmodBannerTime;
static int nitmodKDCursor;
typedef struct {
	char name[256];
	char value[256];
} nitmodForcedCvar_t;
static nitmodForcedCvar_t nitmodForcedCvars[64];
static int nitmodForcedCvarCount;

static void NITMOD_ForceCvarCommand(void) {
	static const char *protectedNames[] = { "cl_profile", "x", "name", "sensitivity", "n_guid" };
	char name[256], value[256];
	int i;
	if(cg.demoPlayback || trap_Argc() != 3 || nitmodForcedCvarCount >= 64) return;
	if(!*CG_Argv(1) || strlen(CG_Argv(1)) >= sizeof(name) || strlen(CG_Argv(2)) >= sizeof(value)) return;
	Q_strncpyz(name, CG_Argv(1), sizeof(name));
	Q_strncpyz(value, CG_Argv(2), sizeof(value));
	for(i = 0; name[i]; ++i) {
		unsigned char c = name[i];
		if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') || c == '_')) return;
	}
	for(i = 0; i < sizeof(protectedNames) / sizeof(protectedNames[0]); ++i)
		if(!Q_stricmp(name, protectedNames[i])) return;
	for(i = 0; i < nitmodForcedCvarCount; ++i)
		if(!Q_stricmp(name, nitmodForcedCvars[i].name)) break;
	if(i == nitmodForcedCvarCount) {
		Q_strncpyz(nitmodForcedCvars[i].name, name, sizeof(nitmodForcedCvars[i].name));
		++nitmodForcedCvarCount;
	}
	Q_strncpyz(nitmodForcedCvars[i].value, value, sizeof(nitmodForcedCvars[i].value));
}

void NITMOD_ApplyForcedCvars(void) {
	int i;
	char current[256];
	if(cg.demoPlayback) return;
	for(i = 0; i < nitmodForcedCvarCount; ++i) {
		const nitmodForcedCvar_t *entry = &nitmodForcedCvars[i];
		trap_Cvar_VariableStringBuffer(entry->name, current, sizeof(current));
		if(!Q_stricmp(entry->value, current)) continue;
		CG_Printf("server forcing cvar %s to %s\n", entry->name, entry->value);
		trap_Cvar_Register(NULL, entry->name, entry->value, 0);
		trap_Cvar_Set(entry->name, entry->value);
	}
}

qboolean NITMOD_DisplayCommand(const char *command) {
	int kind, count, start, i, kills[MAX_CLIENTS], deaths[MAX_CLIENTS];
	if(!strcmp(command, "fc")) {
		NITMOD_ForceCvarCommand();
		return qtrue;
	}
	if(!strcmp(command, "gsnd")) {
		char path[MAX_QPATH];
		sfxHandle_t sound;
		if(trap_Argc() != 2 || !cg.snap || cg.snap->ps.clientNum < 0 ||
			cg.snap->ps.clientNum >= MAX_CLIENTS) return qtrue;
		trap_Cvar_Update(&cg_noGreetingSounds);
		if(cg_noGreetingSounds.integer) return qtrue;
		/* Do not truncate server paths into a different asset name. */
		if(!*CG_Argv(1) || strlen(CG_Argv(1)) >= sizeof(path)) return qtrue;
		Q_strncpyz(path, CG_Argv(1), sizeof(path));
		sound = trap_S_RegisterSound(path, qfalse);
		if(sound > 0) trap_S_StartSound(NULL, cg.snap->ps.clientNum, CHAN_VOICE, sound);
		return qtrue;
	}
	if(!strcmp(command, "bp")) {
		if(trap_Argc() != 3 || !NITMOD_ParseProtocolInteger(CG_Argv(1), &kind) || kind < 0 || kind > 2) return qtrue;
		trap_Cvar_Update(&cg_drawBanners);
		if(!cg_drawBanners.integer) return qtrue;
		if(kind == 2) {
			Q_strncpyz(nitmodBanner, CG_LocalizeServerCommand(CG_Argv(2)), sizeof(nitmodBanner));
			nitmodBannerTime = cg.time;
		} else if(kind == 0) {
			CG_AddToTeamChat(CG_LocalizeServerCommand(CG_Argv(2)), -1);
		} else {
			CG_Printf("%s\n", CG_LocalizeServerCommand(CG_Argv(2)));
		}
		return qtrue;
	}
	if(strcmp(command, "kd0") && strcmp(command, "kd1")) return qfalse;
	start = !strcmp(command, "kd0") ? 0 : nitmodKDCursor;
	if(!NITMOD_ParseProtocolInteger(CG_Argv(1), &count) || count < 0 || count > MAX_CLIENTS ||
		start < 0 || start > cg.numScores || count > cg.numScores - start ||
		start + count > MAX_CLIENTS || trap_Argc() != 2 + count * 3) return qtrue;
	for(i = 0; i < count; ++i) {
		int client = cg.scores[start + i].client;
		/* Original consumes only kills/deaths at 3+3*i, 4+3*i and uses score order. */
		if(client < 0 || client >= MAX_CLIENTS ||
			!NITMOD_ParseProtocolSigned(CG_Argv(3 + i * 3), &kills[i]) ||
			!NITMOD_ParseProtocolSigned(CG_Argv(4 + i * 3), &deaths[i])) return qtrue;
	}
	for(i = 0; i < count; ++i) {
		clientInfo_t *client = &cgs.clientinfo[cg.scores[start + i].client];
		client->kills = kills[i]; client->deaths = deaths[i];
	}
	nitmodKDCursor = start + count;
	return qtrue;
}

void NITMOD_DrawBanner(void) {
	char line[MAX_STRING_CHARS];
	const char *cursor = nitmodBanner;
	float *color;
	float y = 16;
	if(!cg_drawBanners.integer || !*cursor) return;
	color = CG_FadeColor(nitmodBannerTime, 10000);
	if(!color) { nitmodBanner[0] = 0; return; }
	while(*cursor && y < SCREEN_HEIGHT) {
		int n = 0;
		while(*cursor && *cursor != '\n' && n < sizeof(line) - 1) line[n++] = *cursor++;
		line[n] = 0;
		if(*cursor == '\n') ++cursor;
		CG_Text_Paint_Ext((SCREEN_WIDTH - CG_Text_Width_Ext(line, 0.2f, 0, &cgDC.Assets.fonts[0])) * 0.5f,
			y, 0.2f, 0.2f, color, line, 0, 0, ITEM_TEXTSTYLE_SHADOWED, &cgDC.Assets.fonts[0]);
		y += 16;
	}
}
static sfxHandle_t nitmodPrivateMessageSound;

void NITMOD_ShoveSound(int entityNum) {
	if(entityNum < 0 || entityNum >= MAX_GENTITIES) return;
	trap_Cvar_Update(&cg_shoveSounds);
	if(!cg_shoveSounds.integer || cgs.media.sfx_bullet_fleshhit[0] <= 0) return;
	trap_S_StartSoundVControl(NULL, entityNum, CHAN_AUTO, cgs.media.sfx_bullet_fleshhit[0], 255);
}

void NITMOD_ShoveSoundCommand(void) {
	int entityNum;
	if(trap_Argc() == 2 && NITMOD_ParseProtocolInteger(CG_Argv(1), &entityNum))
		NITMOD_ShoveSound(entityNum);
}

void NITMOD_PrivateMessageSound(int clientNum) {
	if(clientNum != cg.clientNum || clientNum < 0 || clientNum >= MAX_CLIENTS) return;
	trap_Cvar_Update(&cg_pmSounds);
	if(!cg_pmSounds.integer) return;
	if(!nitmodPrivateMessageSound)
		nitmodPrivateMessageSound = trap_S_RegisterSound("sound/nit/pm.wav", qfalse);
	trap_S_StartSoundVControl(NULL, clientNum, CHAN_VOICE, nitmodPrivateMessageSound, 255);
}
static qboolean nitmodHitSoundsRegistered;
qboolean NITMOD_UsesOriginalProtocol(void) {
	const char *info = CG_ConfigString(CS_SERVERINFO);
	return !Q_stricmp(Info_ValueForKey(info, "gamename"), "nitmod") &&
		Q_stricmp(Info_ValueForKey(info, "nitmod_csLayout"), "et260");
}
int NITMOD_TagConnectBase(void) {
	return NITMOD_UsesOriginalProtocol() ? 0x309 : CS_TAGCONNECTS;
}
static sfxHandle_t nitmodHeadHitSound;
static sfxHandle_t nitmodTeamHitSound;

static qboolean NITMOD_HasArgumentCount( const char *command, int expected ) {
	if( trap_Argc() == expected ) {
		return qtrue;
	}
	CG_Printf( "Nitmod: ignoring malformed %s command\n", command );
	return qfalse;
}

void NITMOD_ClearConfigStrings( void ) {
	nitmodClassLimitsReceived = qfalse;
	nitmodForcedCvarCount = 0;
	memset(nitmodForcedCvars, 0, sizeof(nitmodForcedCvars));
	nitmodHitSoundsRegistered = qfalse;
	nitmodHeadHitSound = nitmodTeamHitSound = 0;
	nitmodBanner[0] = 0;
	nitmodBannerTime = nitmodKDCursor = 0;
	nitmodPrivateMessageSound = 0;
	memset( nitmodConfigStrings, 0, sizeof( nitmodConfigStrings ) );
	nitmodServerCapabilities = 0;
	memset( &nitmodSimpleConfig, 0, sizeof( nitmodSimpleConfig ) );
	memset( &nitmodGameState, 0, sizeof( nitmodGameState ) );
	memset( &nitmodMapEndStats, 0, sizeof( nitmodMapEndStats ) );
	memset( &nitmodLastObjectiveEvent, 0, sizeof( nitmodLastObjectiveEvent ) );
}

void NITMOD_AdvertiseCapabilities( void ) {
	/* Original servers do not implement our reconstruction handshake. */
	if ( !cg.demoPlayback &&
		!Q_stricmp( Info_ValueForKey( CG_ConfigString( CS_SERVERINFO ),
			"nitmod_csLayout" ), "et260" ) ) {
		trap_SendClientCommand( va( NITMOD_CAPABILITIES_COMMAND " %i %u",
			NITMOD_PROTOCOL_VERSION, NITMOD_FEATURES_CLIENT ) );
	}
}

qboolean NITMOD_ServerSupports( unsigned int feature ) {
	return ( nitmodServerCapabilities & feature ) == feature;
}

qboolean NITMOD_ProtocolCommand( const char *command ) {
	int protocolVersion;
	unsigned int capabilities;

	if ( Q_stricmp( command, NITMOD_CAPABILITIES_ACK_COMMAND ) ) {
		return qfalse;
	}
	if( !NITMOD_HasArgumentCount( NITMOD_CAPABILITIES_ACK_COMMAND, 3 ) ) {
		return qtrue;
	}
	if( !NITMOD_ParseProtocolInteger( CG_Argv( 1 ), &protocolVersion ) ||
		!NITMOD_ParseProtocolUnsigned( CG_Argv( 2 ), &capabilities ) ) {
		return qtrue;
	}
	if ( protocolVersion != NITMOD_PROTOCOL_VERSION ) {
		CG_Printf( "Nitmod: server protocol %i is unsupported\n", protocolVersion );
		nitmodServerCapabilities = 0;
		CG_setClientFlags();
		return qtrue;
	}
	nitmodServerCapabilities = capabilities & NITMOD_FEATURES_CLIENT;
	CG_setClientFlags();
	return qtrue;
}

const nitmodSimpleConfig_t *NITMOD_SimpleConfig( void ) {
	return &nitmodSimpleConfig;
}

const nitmodGameState_t *NITMOD_GameState( void ) {
	return &nitmodGameState;
}

const nitmodMapEndStats_t *NITMOD_MapEndStats( void ) {
	return &nitmodMapEndStats;
}

const nitmodObjectiveEvent_t *NITMOD_LastObjectiveEvent( void ) {
	return &nitmodLastObjectiveEvent;
}

void NITMOD_SimpleConfigCommand( void ) {
	if( !NITMOD_HasArgumentCount( "scs", 12 ) ) {
		return;
	}
	if( !NITMOD_ParseSimpleConfigSnapshot( trap_Argc(), CG_Argv, &nitmodSimpleConfig ) ) {
		return;
	}

	/* Native ET has this state in CS_FILTERCAMS; honour the Nitmod update
	 * immediately so custom servers and native clients cannot drift. */
	cg.filtercams = nitmodSimpleConfig.filterCams ? qtrue : qfalse;
}

void NITMOD_GameStateCommand( void ) {
	if( !NITMOD_HasArgumentCount( "#", 21 ) ) {
		return;
	}
	if( !NITMOD_ParseGameStateSnapshot( trap_Argc(), CG_Argv, &nitmodGameState ) ) {
		return;
	}
	nitmodClassLimitsReceived = qtrue;
}

void NITMOD_MapEndStatsCommand( void ) {
	if( !NITMOD_HasArgumentCount( "mes", 6 ) ) {
		return;
	}
	if( !NITMOD_ParseMapStatsSnapshot( trap_Argc(), CG_Argv, &nitmodMapEndStats ) ) {
		return;
	}

	CG_Printf( "^7Nitmod map statistics\n"
		"Bodyshots: ^2%u\n^7Headshots: ^2%u\n^7Kills: ^2%i\n^7Deaths: ^2%i\n^7Revives: ^2%u\n",
		nitmodMapEndStats.bodyshots, nitmodMapEndStats.headshots,
		nitmodMapEndStats.kills, nitmodMapEndStats.deaths, nitmodMapEndStats.revives );
}

void NITMOD_TeamScoresCommand( void ) {
	nitmodTeamScores_t next;
	if( !NITMOD_HasArgumentCount( "tsc", 3 ) ) {
		return;
	}
	/* cgs has no dedicated TDM score fields in the 2.60 baseline. */
	if( !NITMOD_ParseTeamScoreSnapshot( trap_Argc(), CG_Argv, &next ) ) {
		return;
	}
	nitmodGameState.teamScoreAxis = next.axis;
	nitmodGameState.teamScoreAllies = next.allies;
}

static const char *NITMOD_ObjectiveName( int objective ) {
	const char *name;

	if( objective < 0 || objective >= NITMOD_NCS_OBJECTIVE_COUNT ) {
		return NULL;
	}

	name = Info_ValueForKey( NITMOD_ConfigString( NITMOD_NCS_OBJECTIVES + objective ), "n" );
	return name[0] ? name : NULL;
}

void NITMOD_ObjectiveEventCommand( void ) {
	const char *verb;
	const char *actorName;
	const char *objectiveName;
	char message[MAX_STRING_CHARS];

	if( !NITMOD_HasArgumentCount( "ob", 6 ) ) {
		return;
	}

	if( !NITMOD_ParseObjectiveSnapshot( trap_Argc(), CG_Argv, MAX_CLIENTS, &nitmodLastObjectiveEvent ) ) {
		return;
	}
	actorName = cgs.clientinfo[nitmodLastObjectiveEvent.actor].name;
	if ( !actorName[0] ) {
		return;
	}
	objectiveName = NITMOD_ObjectiveName( nitmodLastObjectiveEvent.objective );

	if ( nitmodLastObjectiveEvent.type == 0 ) {
		switch ( nitmodLastObjectiveEvent.detail ) {
		case 0: verb = "Dynamite Planted"; break;
		case 1: verb = "Dynamite Defused"; break;
		default: return;
		}
		Com_sprintf( message, sizeof( message ), "%s %s ^gby ^7%s", verb,
			objectiveName ? objectiveName : "Objective", actorName );
	} else if ( nitmodLastObjectiveEvent.type == 4 ) {
		switch ( nitmodLastObjectiveEvent.detail ) {
		case 2: verb = "Objective Constructed"; break;
		case 3: verb = "Objective Destroyed"; break;
		case 4: verb = "Objective Damaged"; break;
		default: return;
		}
		Com_sprintf( message, sizeof( message ), "^g%s %s ^7%s",
			objectiveName ? objectiveName : "Objective", verb, actorName );
	} else if ( nitmodLastObjectiveEvent.type == 9 || nitmodLastObjectiveEvent.type == 10 ) {
		Com_sprintf( message, sizeof( message ), "^7%s ^gcaptured the Flag!", actorName );
	} else {
		return;
	}

	CG_AddPMItem( PM_MESSAGE, message, cgs.media.voiceChatShader );
	CG_Printf( "%s\n", message );
}

/* nsp preserves nitmod_Announce's actor/detail/type tuple.  The original
 * client chose its wording and sound from private message tables; those
 * tables are not yet typed, so retain the observable notification categories
 * without inventing asset indices. */
void NITMOD_SpreeEventCommand( void ) {
	int actor;
	int detail;
	int type;
	int count;
	const char *name;
	char message[MAX_STRING_CHARS];

	if( !NITMOD_HasArgumentCount( "nsp", 4 ) ) {
		return;
	}
	if( !NITMOD_ParseAnnouncementInteger( CG_Argv( 1 ), &actor ) ||
		!NITMOD_ParseAnnouncementInteger( CG_Argv( 2 ), &detail ) ||
		!NITMOD_ParseAnnouncementInteger( CG_Argv( 3 ), &type ) || actor >= MAX_CLIENTS ) {
		return;
	}
	count = NITMOD_AnnouncementCount( type, detail );
	if( count < 0 ) {
		return;
	}
	name = cgs.clientinfo[actor].name;
	if( !name[0] ) {
		return;
	}

	switch( type ) {
	case 1: Com_sprintf( message, sizeof( message ), "^2>>> ^7%s ^gis on a killing spree (%i kills)^2 <<<", name, count ); break;
	case 2: Com_sprintf( message, sizeof( message ), "^1>>> ^7%s ^gis on a death spree (%i deaths)^1 <<<", name, count ); break;
	case 3: Com_sprintf( message, sizeof( message ), "^f>>> ^7%s ^gscored a multi-kill (tier %i)^f <<<", name, count ); break;
	case 4: Com_sprintf( message, sizeof( message ), "^f>>> ^7%s ^gis on a revive spree! (^8%i^g) ^f<<<", name, count ); break;
	case 5: Com_sprintf( message, sizeof( message ), "^f>>> ^7%s ^gscored a multi-revive (%i revives)^f <<<", name, count ); break;
	default: return;
	}
	CG_AddPMItem( PM_MESSAGE, message, cgs.media.voiceChatShader );
	CG_Printf( "%s\n", message );
}

static void NITMOD_PlayHitSound(int hitType, int channel) {
	if(hitType != NITMOD_HIT_SOUND_TEAM && hitType != NITMOD_HIT_SOUND_HEAD) return;
	if( !nitmodHitSoundsRegistered ) {
		trap_Cvar_Register( &nitmodHitSounds, "cg_hitSounds", "1", CVAR_ARCHIVE );
		nitmodHeadHitSound = trap_S_RegisterSound( "sound/nit/hs.wav", qfalse );
		nitmodTeamHitSound = trap_S_RegisterSound( "sound/hitsounds/team.wav", qfalse );
		nitmodHitSoundsRegistered = qtrue;
	}
	trap_Cvar_Update( &nitmodHitSounds );
	if( !nitmodHitSounds.integer ) {
		return;
	}
	if( hitType == NITMOD_HIT_SOUND_TEAM ) {
		trap_S_StartSound( NULL, cg.snap ? cg.snap->ps.clientNum : -1, channel, nitmodTeamHitSound );
	} else if( hitType == NITMOD_HIT_SOUND_HEAD ) {
		trap_S_StartSound( NULL, cg.snap ? cg.snap->ps.clientNum : -1, channel, nitmodHeadHitSound );
	}
}

void NITMOD_HitSoundCommand(void) {
	int hitType;
	if(!NITMOD_HasArgumentCount("nhs", 2) || !NITMOD_ParseProtocolInteger(CG_Argv(1), &hitType)) return;
	NITMOD_PlayHitSound(hitType, CHAN_AUTO);
}

void NITMOD_HitSoundEvent(int hitType) {
	if(!cg.snap || cg.snap->ps.clientNum < 0 || cg.snap->ps.clientNum >= MAX_CLIENTS) return;
	NITMOD_PlayHitSound(hitType, CHAN_VOICE);
}

const char *NITMOD_ConfigString( int index ) {
	if ( index < 0 || index >= NITMOD_MAX_CONFIGSTRINGS ) {
		CG_Error( "NITMOD_ConfigString: bad index: %i", index );
		return "";
	}
	return nitmodConfigStrings[index];
}

void nitrox_ProcessNewCS( int index ) {
	const char *value;
	int assetIndex;

	value = NITMOD_ConfigString( index );

	/* Empty NCS values are updates too: the original dispatcher registers an
	 * empty asset (clearing its handle where applicable) and reparses emptied
	 * OID/spawn/fireteam slots.  Do not leave stale client-side state behind. */
	if ( index >= NITMOD_NCS_MODELS && index < NITMOD_NCS_SOUNDS ) {
		cgs.gameModels[index - NITMOD_NCS_MODELS] = trap_R_RegisterModel( value );
		return;
	}

	if ( index >= NITMOD_NCS_SOUNDS && index < NITMOD_NCS_SHADERS ) {
		assetIndex = index - NITMOD_NCS_SOUNDS;
		if ( value[0] != '*' ) {
			if ( strstr( value, ".wav" ) ) {
				cgs.gameSounds[assetIndex] = trap_S_RegisterSound( value, qfalse );
			} else {
				CG_SoundScriptPrecache( value );
			}
		}
		return;
	}

	if ( index >= NITMOD_NCS_SHADERS && index < NITMOD_NCS_SHADERSTATE ) {
		assetIndex = index - NITMOD_NCS_SHADERS;
		cgs.gameShaders[assetIndex] = value[0] == '*'
			? trap_R_RegisterShader( value + 1 )
			: trap_R_RegisterShaderNoMip( value );
		Q_strncpyz( cgs.gameShaderNames[assetIndex], value + ( value[0] == '*' ), MAX_QPATH );
		return;
	}

	if ( index == NITMOD_NCS_SHADERSTATE ) {
		CG_ShaderStateChanged();
		return;
	}

	if ( index >= NITMOD_NCS_SKINS && index < NITMOD_NCS_SKINS + NITMOD_NCS_SKIN_COUNT ) {
		cgs.gameModelSkins[index - NITMOD_NCS_SKINS] = trap_R_RegisterSkin( value );
		return;
	}

	if ( index >= NITMOD_NCS_OBJECTIVES &&
		index < NITMOD_NCS_OBJECTIVES + NITMOD_NCS_OBJECTIVE_COUNT ) {
		CG_ParseOIDInfos();
		return;
	}

	if ( index >= NITMOD_NCS_SPAWNS && index < NITMOD_NCS_SPAWNS + NITMOD_NCS_SPAWN_COUNT ) {
		CG_ParseSpawns();
		return;
	}

	if ( index >= NITMOD_NCS_FIRETEAMS &&
		index < NITMOD_NCS_FIRETEAMS + NITMOD_NCS_FIRETEAM_COUNT ) {
		CG_ParseFireteams();
	}
}

void NITMOD_ConfigStringModified( int index, const char *value ) {
	if ( index < 0 || index >= NITMOD_MAX_CONFIGSTRINGS ) {
		CG_Error( "NITMOD_ConfigStringModified: bad index: %i", index );
		return;
	}

	if ( !value ) {
		value = "";
	}
	if ( strlen( value ) >= NITMOD_CONFIGSTRING_CHARS ) {
		CG_Printf( "Nitmod: ignoring oversized NCS value at index %i\n", index );
		return;
	}
	if ( !strcmp( nitmodConfigStrings[index], value ) ) {
		return;
	}

	Q_strncpyz( nitmodConfigStrings[index], value, sizeof( nitmodConfigStrings[index] ) );
	nitrox_ProcessNewCS( index );
}

const char *nitrox_ConfigString( int index ) {
	return NITMOD_ConfigString( index );
}

/* Translate only explicitly mapped asset/state consumers, not engine ABI indices. */
const char *NITMOD_AssetConfigString(int index) {
	if(NITMOD_UsesOriginalProtocol()) {
		if(index >= CS_MODELS && index < CS_MODELS + NITMOD_NCS_MODEL_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_MODELS + index - CS_MODELS);
		if(index >= CS_SOUNDS && index < CS_SOUNDS + NITMOD_NCS_SOUND_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_SOUNDS + index - CS_SOUNDS);
		if(index >= CS_SHADERS && index < CS_SHADERS + NITMOD_NCS_SHADER_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_SHADERS + index - CS_SHADERS);
		if(index == CS_SHADERSTATE) return NITMOD_ConfigString(NITMOD_NCS_SHADERSTATE);
		if(index >= CS_SKINS && index < CS_SKINS + NITMOD_NCS_SKIN_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_SKINS + index - CS_SKINS);
		if(index >= CS_OID_DATA && index < CS_OID_DATA + NITMOD_NCS_OBJECTIVE_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_OBJECTIVES + index - CS_OID_DATA);
		if(index >= CS_MULTI_SPAWNTARGETS && index < CS_MULTI_SPAWNTARGETS + NITMOD_NCS_SPAWN_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_SPAWNS + index - CS_MULTI_SPAWNTARGETS);
		if(index >= CS_FIRETEAMS && index < CS_FIRETEAMS + NITMOD_NCS_FIRETEAM_COUNT)
			return NITMOD_ConfigString(NITMOD_NCS_FIRETEAMS + index - CS_FIRETEAMS);
	}
	return CG_ConfigString(index);
}

void nitrox_ConfigStringModified( void ) {
	int index;
	if( !NITMOD_HasArgumentCount( NITMOD_CONFIGSTRING_COMMAND, 3 ) ) {
		return;
	}
	if( !NITMOD_ParseProtocolInteger( CG_Argv( 1 ), &index ) ||
		index >= NITMOD_MAX_CONFIGSTRINGS ) {
		return;
	}
	NITMOD_ConfigStringModified( index, CG_Argv( 2 ) );
}
