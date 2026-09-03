/* Nitmod's extended ("ncs") configstring transport. */

#ifndef CG_NITMOD_CONFIG_H
#define CG_NITMOD_CONFIG_H

#include "../game/q_shared.h"
#include "../game/nitmod_protocol.h"
#include "../game/nitmod_snapshots.h"



void NITMOD_ClearConfigStrings( void );
void NITMOD_AdvertiseCapabilities( void );
qboolean NITMOD_ProtocolCommand( const char *command );
qboolean NITMOD_ServerSupports( unsigned int feature );
const nitmodSimpleConfig_t *NITMOD_SimpleConfig( void );
const nitmodGameState_t *NITMOD_GameState( void );
const nitmodMapEndStats_t *NITMOD_MapEndStats( void );
const nitmodObjectiveEvent_t *NITMOD_LastObjectiveEvent( void );
void NITMOD_SimpleConfigCommand( void );
void NITMOD_GameStateCommand( void );
void NITMOD_MapEndStatsCommand( void );
void NITMOD_TeamScoresCommand( void );
void NITMOD_ObjectiveEventCommand( void );
void NITMOD_SpreeEventCommand( void );
void NITMOD_HitSoundCommand( void );
void NITMOD_HitSoundEvent(int hitType);
const char *NITMOD_ConfigString( int index );
const char *NITMOD_AssetConfigString(int nativeIndex);
void NITMOD_ConfigStringModified( int index, const char *value );
const char *nitrox_ConfigString( int index );
void nitrox_ProcessNewCS( int index );
void nitrox_ConfigStringModified( void );

/* TAGCONNECT wire range; original Nitmod differs from native ET 2.60. */
int NITMOD_TagConnectBase(void);
qboolean NITMOD_UsesOriginalProtocol(void);
extern vmCvar_t cg_pmSounds;
extern vmCvar_t cg_shoveSounds;
extern vmCvar_t cg_noGreetingSounds;
void NITMOD_ShoveSound(int entityNum);
void NITMOD_ShoveSoundCommand(void);
extern vmCvar_t cg_drawBanners;
extern vmCvar_t nitmodHitSounds;
qboolean NITMOD_DisplayCommand(const char *command);
void NITMOD_DrawBanner(void);
int NITMOD_ParseLatchedClass(const char *info, int currentClass);
qboolean NITMOD_ClassIsDisabled(int team, int playerClass);
void NITMOD_ApplyForcedCvars(void);
void CG_AddToTeamChat(const char *str, int clientnum);
void NITMOD_PrivateMessageSound(int clientNum);
#endif
