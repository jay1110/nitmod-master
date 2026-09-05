/* Server half of Nitmod's extended configstring protocol. */

#ifndef G_NITMOD_CONFIG_H
#define G_NITMOD_CONFIG_H

#include "q_shared.h"
#include "nitmod_protocol.h"

#include "nitmod_snapshots.h"

void G_NITMOD_ClearConfigStrings( void );
void G_NITMOD_ResetClient( int clientNum );
void G_NITMOD_CacheClientAddress( gentity_t *ent, const char *address );
qboolean NITMOD_ValidateNGuid( const char *nguid, char *reason, int reasonSize );
void NITMOD_SendChunkedPrint( int clientNum, const char *text );
qboolean NITMOD_BuildFilePath( const char *directory, const char *name,
	const char *extension, char *path, int pathSize );
void nitrox_ClampFloat( float *value, float minimum, float maximum );
void nitrox_ClampInt( int *value, float minimum, float maximum );
int G_NITMOD_DynamiteTimer( void );
void nitrox_stripLeadingSpaces( char *text );
/* Spatial one-shot sound used by recovered Nitmod gameplay call sites. */
void NITMOD_PlaySoundEvent( gentity_t *source, int soundIndex );
void nitmod_Sound_Global( int soundIndex );
/* Recovered nitmod_Announce tuple: actor client number, message tier, kind. */
void nitmod_Announce( int actor, int detail, int type );
void NITMOD_SendHitSound( int clientNum, int hitType );
void NITMOD_SendWeaponLimitMessage( int clientNum, int reason );
/* Typed subset of G_UpdateKillingSpree: enemy kills advance the actor's
 * positive streak; every five kills through 30 emits announcement type 1. */
void NITMOD_UpdateKillSpree( gentity_t *victim, gentity_t *attacker );
void G_NITMOD_ClientCapabilities( int clientNum, int protocolVersion, unsigned int capabilities );
qboolean G_NITMOD_ClientSupports( int clientNum, unsigned int feature );
const char *G_NITMOD_ConfigString( int index );
void G_NITMOD_SetConfigString( int index, const char *value );
void G_NITMOD_MirrorEngineConfigString( int index, const char *value );
void G_NITMOD_ResyncEngineConfigStrings( void );
void G_NITMOD_SendConfigStrings( int clientNum );
void nitrox_SetConfigstring( int index, const char *value );
void nitrox_GetConfigstring( int index, char *buffer, int bufferSize );
void nitrox_UpdateConfigstrings( void );
int nitrox_CSIndex( const char *name, int start, int count, qboolean create );
void nitmod_SendChargeTimes( int clientNum );
void nitmod_SendMapEndStats( int clientNum );
void nitmod_SetSimpleConfig( const nitmodSimpleConfig_t *config );
void nitmod_SetGameState( const nitmodGameState_t *state );
void nitmod_RefreshBaseSettings( void );
void G_NITMOD_SetMapCycleCount( int count );
int G_NITMOD_MapCycleCount( void );
qboolean G_NITMOD_MapCycleEnabled( void );
qboolean G_NITMOD_MapCycleResetsXP( void );
void G_NITMOD_AdvanceMapCycle( void );
void nitmod_SimpleCS( int clientNum );
void nitmod_SendNCS( int clientNum );
void nitmod_SendTeamScores( int clientNum );
void nitmod_SendSkillLevels( int clientNum );
void nitmod_SendClassHealth( int clientNum );
void nitmod_TeamScores( void );
/* The final wire field is means-of-death (MOD_*), as in the reference ob
 * command; it is zero when an event has no weapon attribution. */
void nitmod_ObjectiveEvent( int type, int detail, int objective, int actor, int meansOfDeath );

#endif
