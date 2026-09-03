/* Shared wire-level constants for recovered Nitmod extensions.  This header
 * intentionally has no engine dependency: it is the qagame/cgame/ui contract. */

#ifndef NITMOD_PROTOCOL_H
#define NITMOD_PROTOCOL_H

/* Strict nonnegative decimal fields. Failure leaves output unchanged.
 * Capabilities use the full unsigned range; indices fit a signed int. */
int NITMOD_ParseProtocolUnsigned( const char *text, unsigned int *value );
int NITMOD_ParseProtocolInteger( const char *text, int *value );
/* Signed decimal snapshots may contain negative team scores and settings. */
int NITMOD_ParseProtocolSigned( const char *text, int *value );
/* Finite decimal float; no whitespace, hexadecimal, NaN or infinity. */
int NITMOD_ParseProtocolFloat( const char *text, float *value );

#define NITMOD_MAX_CONFIGSTRINGS 655
#define NITMOD_CONFIGSTRING_CHARS 1018 /* original qagame slot size (0x3fa) */
#define NITMOD_CONFIGSTRING_COMMAND "ncs"
#define NITMOD_CAPABILITIES_COMMAND "nitcap"
#define NITMOD_CAPABILITIES_ACK_COMMAND "nitcaps"

#define NITMOD_PROTOCOL_VERSION 1

#define NITMOD_FEATURE_NCS             ( 1u << 0 )
#define NITMOD_FEATURE_CHARGE_TIMES    ( 1u << 1 )
#define NITMOD_FEATURE_SIMPLE_CS       ( 1u << 2 )
#define NITMOD_FEATURE_OBJECTIVES      ( 1u << 3 )
#define NITMOD_FEATURE_FIRETEAMS       ( 1u << 4 )
#define NITMOD_FEATURE_WEB_BRIDGE      ( 1u << 5 )
#define NITMOD_FEATURE_TEAM_SCORES     ( 1u << 6 )
#define NITMOD_FEATURE_MAP_END_STATS   ( 1u << 7 )
#define NITMOD_FEATURE_SPREE_EVENTS    ( 1u << 8 )
#define NITMOD_FEATURE_HIT_SOUNDS       ( 1u << 9 )
#define NITMOD_FEATURE_WEAPON_MESSAGES  ( 1u << 10 )
/* Preference transport only; does not advertise recovered reload gameplay. */
#define NITMOD_FEATURE_RELOAD_PREFS      ( 1u << 11 )
#define NITMOD_FEATURE_SHOVE_SOUND       ( 1u << 12 )

/* Complete original ncp/SrvMsgs table; out-of-range reasons return NULL. */
const char *NITMOD_ServerMessageText(int reason);
const char *NITMOD_WeaponLimitText( int reason );

/* Recovered Nit_HitSound eventParm values. */
#define NITMOD_HIT_SOUND_TEAM 3
#define NITMOD_HIT_SOUND_HEAD 4

#define NITMOD_FEATURES_CLIENT ( NITMOD_FEATURE_NCS | NITMOD_FEATURE_CHARGE_TIMES | \
	NITMOD_FEATURE_SIMPLE_CS | NITMOD_FEATURE_OBJECTIVES | NITMOD_FEATURE_FIRETEAMS | \
	NITMOD_FEATURE_TEAM_SCORES | NITMOD_FEATURE_MAP_END_STATS | NITMOD_FEATURE_SPREE_EVENTS | \
	NITMOD_FEATURE_HIT_SOUNDS | NITMOD_FEATURE_WEAPON_MESSAGES | NITMOD_FEATURE_RELOAD_PREFS | NITMOD_FEATURE_SHOVE_SOUND )
#define NITMOD_FEATURES_SERVER NITMOD_FEATURES_CLIENT

/* Recovered extended-configstring layout; this differs from native ET CS. */
#define NITMOD_NCS_MODELS       0
#define NITMOD_NCS_MODEL_COUNT  256
#define NITMOD_NCS_SOUNDS       ( NITMOD_NCS_MODELS + NITMOD_NCS_MODEL_COUNT )
#define NITMOD_NCS_SOUND_COUNT  256
#define NITMOD_NCS_SHADERS      ( NITMOD_NCS_SOUNDS + NITMOD_NCS_SOUND_COUNT )
#define NITMOD_NCS_SHADER_COUNT 32
#define NITMOD_NCS_SHADERSTATE  ( NITMOD_NCS_SHADERS + NITMOD_NCS_SHADER_COUNT )
#define NITMOD_NCS_SKINS        ( NITMOD_NCS_SHADERSTATE + 1 )
#define NITMOD_NCS_SKIN_COUNT   64
#define NITMOD_NCS_OBJECTIVES    ( NITMOD_NCS_SKINS + NITMOD_NCS_SKIN_COUNT )
#define NITMOD_NCS_OBJECTIVE_COUNT 18
#define NITMOD_NCS_SPAWNS        ( NITMOD_NCS_OBJECTIVES + NITMOD_NCS_OBJECTIVE_COUNT )
#define NITMOD_NCS_SPAWN_COUNT   16
#define NITMOD_NCS_FIRETEAMS     ( NITMOD_NCS_SPAWNS + NITMOD_NCS_SPAWN_COUNT )
#define NITMOD_NCS_FIRETEAM_COUNT 12

#endif
