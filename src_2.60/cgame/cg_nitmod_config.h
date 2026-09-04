/* Nitmod's extended ("ncs") configstring transport. */

#ifndef CG_NITMOD_CONFIG_H
#define CG_NITMOD_CONFIG_H

/* Original playerState eFlags only; do not reinterpret native ET flags. */
#define NITMOD_EF_BLINDED 0x00400000

#include "../game/q_shared.h"
#include "../game/nitmod_protocol.h"
#include "../game/nitmod_snapshots.h"



void NITMOD_ClearConfigStrings( void );
extern vmCvar_t cg_markDistance, cg_projectileNudge, nitmod_sv_fps;
extern vmCvar_t cg_countryflags, cg_optimizePrediction, cg_locations;
extern vmCvar_t cg_logFile, cg_clientLog, cg_drawCam, cg_locationMaxChars;
extern vmCvar_t cg_TDMScorePos, cg_earlyTransition;
qboolean CG_NitmodEarlyTransitionEnabled(void);
qboolean CG_NitmodTransitionEarlyEntity(int snapshotIndex);
qboolean CG_NitmodBulletImpactVisible(int weapon, const vec3_t origin);
int CG_NitmodProjectileTime(const entityState_t *state);
qboolean CG_NitmodProjectileLerp(centity_t *cent);
void NITMOD_AdvertiseCapabilities( void );
void NITMOD_BeginOriginalSession(void);
qboolean NITMOD_OriginalSessionCommand(const char *command);
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
void NITMOD_TDMScoreLimitCommand( void );
void NITMOD_TDMInfo_f( void );
void NITMOD_DMWinnerCommand( void );
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
int CG_NitmodEventDispatch(int wireEvent);
/* Private dispatch result: original-only death4 handled before native switch. */
#define NITMOD_EVENT_DEATH4 (-2)
qboolean NITMOD_DecodeNKey(const char *encoded, int length, char guid[33]);
qboolean NITMOD_CreateNKey(const qtime_t *time, const unsigned int choices[4], char encoded[45]);
qboolean NITMOD_GenerateMissingNKey(char guid[33]);
void NITMOD_ReadNKey(void);
int NITMOD_WeaponFromWire(int weapon);
int NITMOD_EntityTypeFromWire(int type);
int NITMOD_ItemFromWire(int item);
int NITMOD_CoreConfigToWire(int index);
int NITMOD_CoreConfigFromWire(int index);
void CG_NitmodRegisterPrivateWeaponMedia(void);
const weaponInfo_t *CG_NitmodPrivateWeaponMedia(int wireWeapon);
int NITMOD_HintFromWire(int hint);
bg_playerclass_t *CG_NitmodPlayerClass(int team, int cls);
int NITMOD_WeaponToWire(int weapon);
void NITMOD_NormalizePredictedEvents(playerState_t *state);
void NITMOD_TranslateSnapshotPersistant(snapshot_t *snapshot);
typedef enum {
    NITMOD_WIRE_PERS_SCORE, NITMOD_WIRE_PERS_HITS, NITMOD_WIRE_PERS_BODYHITS,
    NITMOD_WIRE_PERS_KILLS, NITMOD_WIRE_PERS_DEATHS, NITMOD_WIRE_PERS_HEADSHOTS,
    NITMOD_WIRE_PERS_BODYSHOTS, NITMOD_WIRE_PERS_TEAM, NITMOD_WIRE_PERS_SPAWN_COUNT,
    NITMOD_WIRE_PERS_RESPAWNS_LEFT, NITMOD_WIRE_PERS_RESPAWNS_PENALTY,
    NITMOD_WIRE_PERS_REVIVE_COUNT, NITMOD_WIRE_PERS_HWEAPON_USE,
    NITMOD_WIRE_PERS_GOOMBAS, NITMOD_WIRE_PERS_BESTSPREE, NITMOD_WIRE_PERS_KILLSPREE
} nitmodWirePersistantIndex_t;
const int *NITMOD_WirePersistant(const playerState_t *state);
void NITMOD_ResetSnapshotPersistant(void);
void NITMOD_SnapshotHitSounds(const playerState_t *oldState, const playerState_t *newState);
int NITMOD_PredictedEventId(int event);
const char *NITMOD_PlayerConfigString(int clientNum);
extern vmCvar_t cg_pmSounds;
extern vmCvar_t n_forceSinglePistol, cg_FTAutoSelect;
unsigned int NITMOD_ClientPreferenceFlags(unsigned int flags, int fixedMove, int singlePistol);
int CG_NitmodAutoSelectFireteam(void);
extern vmCvar_t cg_limbo_secondary;
extern vmCvar_t cg_shoveSounds;
extern vmCvar_t cg_noGreetingSounds;
void NITMOD_ShoveSound(int entityNum);
void NITMOD_ShoveSoundCommand(void);
extern vmCvar_t cg_drawBanners;
void NITMOD_FormatBanner(const char *text, char *out, int size);
extern vmCvar_t nitmodHitSounds;
qboolean NITMOD_DisplayCommand(const char *command);
void NITMOD_DrawBanner(void);
int NITMOD_ParseLatchedClass(const char *info, int currentClass);
int NITMOD_ParseCountryCode(const char *value);
void NITMOD_ParseClientExtras(const char *info, clientInfo_t *client);
qboolean NITMOD_DecodeClientSkills(const char *text, int *nativeLevels, int *displayLevels);
const char *CG_NitmodSpectatorLabel(const clientInfo_t *client, int ping);
qboolean NITMOD_ClassIsDisabled(int team, int playerClass);
qboolean NITMOD_WeaponQuotaDisabled(int weapon, int playerClass, int teamCount, int weaponCount);
void NITMOD_ApplyForcedCvars(void);
void CG_AddToTeamChat(const char *str, int clientnum);
void NITMOD_PrivateMessageSound(int clientNum);
#endif
