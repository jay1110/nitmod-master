#ifndef G_NITMOD_RESTRICTIONS_H
#define G_NITMOD_RESTRICTIONS_H
#include "nitmod_weapon_limits.h"
#include "nitmod_snapshots.h"
struct gentity_s;
/* A tri-state result is essential: DEFER is not permission. */
typedef enum {
    NITMOD_WEAPON_DEFER,
    NITMOD_WEAPON_ALLOW,
    NITMOD_WEAPON_DENY
} nitmodWeaponDecision_t;
nitmodWeaponDecision_t G_NITMOD_WeaponPrecheck( const struct gentity_s *entity,
    int nativeWeapon, int warMode );
int G_NITMOD_StenAllowed( const struct gentity_s *entity, int pickupContext,
    int pickAnyWeapon, unsigned int weaponsOptions );
int G_NITMOD_IsClassPrimary( const struct gentity_s *entity, int nativeWeapon,
    int pickupContext, int pickAnyWeapon );
/* Original nitmod_cp reason ID, or zero for a deliberately silent denial.
 * No command is sent: exact message text/transport remains caller-owned. */
int G_NITMOD_LimitMessage( const struct gentity_s *entity, int nativeWeapon,
    nitmodWeaponLimit_t limit, int isClassPrimary, int silent );

/* Read-only snapshot supplied by the engine adapter. Counts exclude
 * the requester. For rifle grenades weaponCount is the matching base-rifle
 * family with equipment status; oppositeRifleCount is the other family.
 * teamSize is the original team population, not a weapon count. */
typedef struct {
    int warMode, pickupContext, pickAnyWeapon;
    unsigned int weaponsOptions;
    int silent;
    int teamSize, weaponCount, oppositeRifleCount;
    int heavyPercent, maxClients, panzerPercent;
    int maxPanzers, maxFlamers, maxMG42s, maxMortars, maxRifleGrenades;
} nitmodWeaponPolicyInput_t;
/* Read existing engine Cvars atomically. Registers no defaults and preserves
 * counts, pickup context and silent mode. Zero means incomplete/invalid. */
int G_NITMOD_ReadWeaponConfiguration( nitmodWeaponPolicyInput_t *input );
int G_NITMOD_ReadMedicOptions( unsigned int *options );
/* 1 allowed, 0 denied, -1 unavailable/invalid. Caller supplies the mask from
 * the correctly selected, validated weapon definition. Does not grant items. */
int G_NITMOD_CanPickupWeapon( struct gentity_s *entity, int nativeWeapon,
    unsigned int classMask );
/* 0/1 final decision, -1 means retain native class policy or unavailable
 * configuration. Does not assume a missing original class mask is zero. */
int G_NITMOD_PickupPrecheck( struct gentity_s *entity, int nativeWeapon );
/* Atomic mapping to the existing # snapshot; unrelated fields preserved. */
int G_NITMOD_RefreshWeaponSnapshot( nitmodGameState_t *state );
/* Register only recovered Cvars absent from native ET; existing
 * engine values are preserved by registration, never overwritten by Set. */
void G_NITMOD_RegisterWeaponConfiguration( void );
int G_NITMOD_UpdateWeaponConfiguration(void);
int G_NITMOD_ConfiguredWarMode(void);
int G_NITMOD_ConfiguredNoReload(void);
unsigned int G_NITMOD_ConfiguredMedicOptions(void);
int G_NITMOD_ConfiguredWeaponFlags(void);
typedef struct {
    nitmodWeaponDecision_t decision;
    nitmodWeaponLimit_t limit;
    int messageReason; /* original nitmod_cp ID, NOT a native event */
} nitmodWeaponPolicyResult_t;
/* Decision composition used by the active native spawn/loadout adapter.
 * INVALID denies safely; it is never converted into a player cap message. */
nitmodWeaponPolicyResult_t G_NITMOD_EvaluateWeaponPolicy(
    const struct gentity_s *entity, int nativeWeapon,
    const nitmodWeaponPolicyInput_t *input );
/* Read-only server composition: existing Cvars + explicit population cache +
 * live weapon counts. No message/event/inventory mutation or cache refresh. */
nitmodWeaponPolicyResult_t G_NITMOD_EvaluateServerWeaponPolicy(
    struct gentity_s *entity, int nativeWeapon, int pickupContext, int silent );
/* At most one targeted capability-gated message; no inventory mutation.
 * Result reports the decision/reason, not whether transport delivered it. */
nitmodWeaponPolicyResult_t G_NITMOD_CheckWeaponAndNotify(
    struct gentity_s *entity, int nativeWeapon, int pickupContext, int silent );
/* 1 changed, 0 unchanged, -1 invalid/unavailable (native setter falls back).
 * Uses native weapon IDs and may send a capability-gated denial message. */
int G_NITMOD_SetClientWeapons( struct gentity_s *entity, int primary, int secondary,
    int updateClient );
/* Post-restriction pickup decision; caller must evaluate limits with pickup=1.
 * classMask is original per-weapon BG_Weapons permission data, supplied
 * explicitly until its owner is reconstructed. No inventory mutation. */
int G_NITMOD_PickupPolicy( const struct gentity_s *entity, int weapon,
    nitmodWeaponDecision_t restriction, int warMode, int pickAnyWeapon,
    unsigned int classMask, unsigned int medicOptions );
#endif
