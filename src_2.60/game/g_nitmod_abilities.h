#ifndef G_NITMOD_ABILITIES_H
#define G_NITMOD_ABILITIES_H

struct gclient_s;
struct gentity_s;
/* Classification used by original connect/userinfo paths. No engine calls.
 * Invalid negative client numbers are rejected deliberately. */
int G_NITMOD_IsDemoClient( int clientNum, int demoState, int demoClients );
int G_NITMOD_CanCheckWeapons( const struct gentity_s *entity, int isDemoClient );
/* Adrenaline subset with original outer guards, not the complete original
 * weapon check (war mode and generic restrictions are separate). */
int G_NITMOD_CheckAdrenaline( struct gentity_s *entity, int isDemoClient,
    unsigned int firstAidUnlocks, unsigned int allowedClasses );
/* Explicit recovered unlock state, not a numeric skill >= 4 approximation.
 * Callers must supply negotiated/configured state before activating these. */
int G_NITMOD_ClientHasAdrenaline( const struct gclient_s *client,
    unsigned int firstAidUnlocks, unsigned int allowedClasses );
int G_NITMOD_EntityHasAdrenaline( const struct gentity_s *entity,
    unsigned int firstAidUnlocks, unsigned int allowedClasses );
int G_NITMOD_AdrenalineClip( unsigned int options );
/* Isolated G_UpgradeSkill adrenaline inventory effect after its early-return
 * branches. Uses original independent adrenaline slots, NOT native syringe
 * aliases. Caller owns upgrade dispatch and bot notification. Not gameplay-
 * active; returns 1 when eligible and assigned, 0 without mutation otherwise. */
int G_NITMOD_GrantAdrenalineUpgrade( struct gclient_s *client,
    unsigned int firstAidUnlocks, unsigned int allowedClasses,
    unsigned int adrenalineOptions, int warMode );
struct ammotable_s;
/* Adrenaline subset of class-tool spawn grant, including its war-mode gate.
 * Uses caller's loaded reserve/clip defaults, not upgrade's fixed 0/12.
 * 1 assigned, 0 skipped/ineligible, -1 invalid defaults; no writes on failure. */
int G_NITMOD_GrantAdrenalineSpawn( struct gclient_s *client,
    unsigned int firstAidUnlocks, unsigned int allowedClasses,
    unsigned int adrenalineOptions, int warMode, const struct ammotable_s *defaults );
/* Recovered inner inventory operation only. Caller owns ClientThink guards.
 * Returns one if the weapon was removed, zero otherwise. Does not grant it,
 * clear ammunition, change selected weapon or cancel active powerups. */
int G_NITMOD_ReconcileAdrenaline( struct gclient_s *client,
    unsigned int firstAidUnlocks, unsigned int allowedClasses );

#endif
