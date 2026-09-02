#ifndef NITMOD_WEAPON_RELOAD_H
#define NITMOD_WEAPON_RELOAD_H
#include "nitmod_weapon_inventory.h"
#include "nitmod_weapon_definition.h"
/* Recovered ability bit, NOT an ET skill level. Caller must supply the
 * corresponding negotiated/reconstructed ability word explicitly. */
#define NITMOD_MG42_MIDCLIP_RELOAD 0x20u
#define NITMOD_FAST_RELOAD 0x4u
/* Animation selection only. Caller resolves its native skill or recovered
 * ability into enabled; only the eight supported light weapons use it.
 * Does not start animation, authorize reload or modify any state. */
int NITMOD_ReloadAnimation( int weapon, int fastReloadEnabled );
/* Arithmetic only: multiply by the original binary32 factor without a
 * binary32 intermediate product, truncate toward zero. All int32 inputs fit.
 * Does not determine whether a weapon/player receives fast reload. */
int NITMOD_ScaleFastReloadDuration( int baseDuration );
/* Active legacy weapon timer arithmetic: reproduce the original signed
 * 32-bit ADD result without signed overflow or out-of-range signed casts.
 * Does not validate reload eligibility or change the hardened opt-in API. */
int NITMOD_AddWeaponTime32( int timer, int duration );
/* Explicit ability word, not native skill level. Supported original light
 * weapons scale by the exact stored 0.65f factor, truncating toward zero.
 * Negative durations/unknown identities/null output reject without mutation. */
int NITMOD_ReloadDuration( int weapon, int baseDuration,
    unsigned int lightWeaponAbilityBits, int *duration );
/* Original ready/normal-fire/alternate-fire gate, expressed in native enums. */
int NITMOD_ReloadStateAllowed( int weaponState );
/* Body-script selection only, after eligibility/inventory gates. The five
 * mapped throwables/tripmine skip it; landmine does not. Other identities
 * retain native default selection; this does not authorize reloading. */
int NITMOD_ReloadBodyEventRequired( int weapon );
/* Empty CURRENT reserve resets READY before target-specific reload checks.
 * Active migration adapter: apply only when the caller's native ammo slot
 * agrees with the recovered alias. Mismatched/unmapped identities are left
 * unchanged until their full inventory lifecycle is ported (adrenaline).
 * Returns 1 when handled, 0 otherwise; only weaponstate may change. */
int NITMOD_ResetReloadWithoutReserve( playerState_t *state, int nativeAmmoSlot );
/* Original switch gate blocks dropping, dropping-to-reload AND reloading.
 * Other switch constraints remain the native caller's responsibility. */
int NITMOD_WeaponChangeStateAllowed( int weaponState );
/* Commit only the selected weapon and raising state after lowering completes.
 * Invalid/unowned targets become NONE; reload intent survives even that case.
 * Caller owns timers, animations and all remaining finish effects. Returns the
 * selected native weapon, or -1 for null state. nextWeapon is not rewritten. */
int NITMOD_CommitWeaponChange( playerState_t *state );
/* Finish-stage early-return predicate, AFTER target/state commit. Knife and
 * smoke bomb must still raise when reselected. Only mapped native identities
 * are covered; this does not authorize starting a weapon change. */
int NITMOD_WeaponChangeNeedsRaise( int oldWeapon, int newWeapon );
/* Exact six base/scope transitions, identical drop/raise duration. Returns 1
 * and writes milliseconds for a reviewed pair; 0 leaves output unchanged.
 * Other weapon families retain their existing per-phase timing/effects. */
int NITMOD_ScopeSwitchDuration( int oldWeapon, int newWeapon, int *duration );
typedef struct {
    int dropTime;
    int raiseTime;
    qboolean dropAltAnimation;
    qboolean raiseAltAnimation;
} nitmodPistolSwitch_t;
/* Four single-pistol/silencer transitions. Unsupported pairs/null reject
 * unchanged. No akimbo inference; body-event selection stays in Pmove. */
int NITMOD_PistolSwitch( int oldWeapon, int newWeapon, nitmodPistolSwitch_t *result );
/* Update only the remembered silencer bit for a committed single pistol.
 * Other weapon identities preserve every bit, including rifle-grenade mode. */
int NITMOD_PistolModeFlags( int weapon, int flags );
typedef struct {
    int duration;
    qboolean animate;
} nitmodRifleGrenadeRaise_t;
/* Four rifle/grenade pairs at finish, after weapon commit. Return reads the
 * OLD launcher's ammo-alias clip (not reserve); attachment does not read it.
 * Zero clip skips animation, any nonzero clip keeps it, as in the original.
 * No mutation of state; unsupported/null input leaves result unchanged. */
int NITMOD_RifleGrenadeRaise( const playerState_t *state, int oldWeapon,
    int newWeapon, nitmodRifleGrenadeRaise_t *result );
int NITMOD_RifleGrenadeModeFlags( int weapon, int flags );
/* Reviewed pairs always drop in 0 ms. On attachment, request native clip
 * transfer only when target clip is zero and target reserve is nonzero.
 * Returns 1 for a pair and writes target or NONE; no inventory mutation. */
int NITMOD_RifleGrenadeDrop( const playerState_t *state, int oldWeapon,
    int newWeapon, int *reloadWeapon );
typedef struct {
    int raiseTime;
    qboolean raiseAltAnimation;
    qboolean captureDirection;
} nitmodDeploySwitch_t;
/* Four MG42/mortar deployment transitions. Drop is always zero; direction
 * capture occurs only on deployment, not packing up. Pure plan, not permission
 * to deploy; existing prone/water and movement constraints stay in Pmove. */
int NITMOD_DeploySwitch( int oldWeapon, int newWeapon, nitmodDeploySwitch_t *result );
/* Isolated timing effect after all start checks and duration calculation.
 * READY adds duration; firing overlaps existing time via max(). Sets RELOADING
 * but emits no event/animation. Invalid duration/state/overflow rejects intact. */
int NITMOD_ApplyReloadTiming( playerState_t *state, int duration );
/* Effect bundle AFTER all start checks and duration calculation: timing,
 * gated first-person animation, native EV_FILL_CLIP. No body-script animation.
 * Returns 0 unchanged on invalid inputs/state/timing/event sequence overflow.
 * Animation uses current weapon, mortar suppression uses target weapon. */
int NITMOD_ApplyReloadFeedback( pmove_t *move, int targetWeapon,
    int duration, unsigned int lightWeaponAbilityBits );
/* Original begin-reload weapon-range test translated to reviewed identities.
 * This alone does not make a weapon reloadable in active gameplay. */
int NITMOD_ReloadWeaponEligible( int weapon );
/* Migration scope for the original absence of an inner full-magazine veto.
 * Twelve reviewed pistol/SMG/FG42 identities use the outer request gate.
 * Does not itself authorize a reload; other identities retain native policy. */
int NITMOD_ReloadUsesOuterClipGate( int weapon );
typedef enum {
    NITMOD_RELOAD_START_INVALID = -1,
    NITMOD_RELOAD_START_BLOCKED = 0,
    NITMOD_RELOAD_START_EMPTY_RESERVE,
    NITMOD_RELOAD_START_INVENTORY_ALLOWED
} nitmodReloadStartInventory_t;
/* Call only AFTER a separately established weapon-state gate. Original tests
 * reserve of state->weapon, then midclip/range restrictions of targetWeapon.
 * EMPTY_RESERVE reports the original ready-state reset intent; does not apply
 * it. No timer, animation, event or weaponstate is changed here. */
nitmodReloadStartInventory_t NITMOD_CheckReloadStartInventory(
    const playerState_t *state, int targetWeapon,
    const nitmodWeaponOptions_t *options, unsigned int reloadAbilityBits );
/* State-gated inventory check. EMPTY_RESERVE resets only weaponstate to READY;
 * other outcomes do not mutate. Does not apply timing or start animations. */
nitmodReloadStartInventory_t NITMOD_PrepareReloadInventory(
    playerState_t *state, int targetWeapon,
    const nitmodWeaponOptions_t *options, unsigned int reloadAbilityBits );
/* Opt-in begin adapter: state/inventory gate, calculated duration, native body
 * script event, first-person animation and predictable event. ALLOWED means
 * started; EMPTY_RESERVE resets READY. Outer PM_CheckForReload policy remains
 * caller-owned. Requires character animation data only when a body event is
 * selected. Missing animation script result is ignored, as in the original. */
nitmodReloadStartInventory_t NITMOD_BeginWeaponReload( pmove_t *move,
    int targetWeapon, const ammotable_t *weaponAmmo,
    const nitmodWeaponOptions_t *options, unsigned int reloadAbilityBits,
    unsigned int lightWeaponAbilityBits );
/* Midclip restriction only: MG42 variants ignore noMidclipReload and use the
 * ability bit instead. No reserve/state/time/weapon-range checks or mutation.
 * A true result alone is not permission to start a reload. */
int NITMOD_MidclipReloadAllowed( const playerState_t *state, int weapon,
    const nitmodWeaponOptions_t *options, unsigned int reloadAbilityBits );
/* Original clip transfer, main akimbo hand before sidearm. Capacity is keyed
 * by weapon identity, not clip alias. Caller supplies recovered ammo records.
 * Returns 1 even for a valid no-op; 0 rejects atomically. Negative inventories,
 * negative capacities and overflow reject. Overfull clips return excess to
 * reserve, as in the original. This does not initiate reloads or animations. */
int NITMOD_ReloadWeaponClips( playerState_t *state, int weapon,
    const ammotable_t *ammoTable, int ammoSlots );
/* Completes the reload after both timers expire: atomic inventory transfer,
 * READY, then gated idle animation. Returns 1 completed, 0 not ready, -1 invalid.
 * No new completion event is emitted by the original. Not an active hook. */
int NITMOD_FinishWeaponReload( pmove_t *move,
    const ammotable_t *ammoTable, int ammoSlots );
typedef enum {
    NITMOD_RELOAD_AUTOMATIC,
    NITMOD_RELOAD_MANUAL
} nitmodReloadRequest_t;
/* Inventory predicate ONLY, not permission to start reloading. The caller must
 * enforce weapon state/time, automatic-reload policy, scoped mode switching,
 * rifle-grenade exclusions and PM_BeginWeaponReload's weapon restrictions.
 * Manual: at least one magazine below capacity. Automatic: both empty.
 * Positive reserve required; invalid inputs return 0. No state is changed. */
int NITMOD_ReloadInventoryReady( const playerState_t *state, int weapon,
    nitmodReloadRequest_t request, const ammotable_t *ammoTable, int ammoSlots );
typedef struct {
    int manualRequested;
    int automaticAllowed;
    unsigned int scopedAbilityBits;
    int warMode;
} nitmodReloadPolicy_t;
#define NITMOD_CGF_ALT_RELOAD 0x10u
/* Request only, not permission: reload key OR enabled alternate-attack key.
 * Uses mod-local synchronized preference flags, never native skill levels. */
int NITMOD_ManualReloadRequested( const usercmd_t *command, unsigned int clientFlags );
typedef struct {
    int autoReload;
    int attack2Reload;
} nitmodReloadPreferences_t;
/* cg_autoReload/cg_weapAltReloads use >0, not generic nonzero truth. Only
 * these two flag bits are replaced; all unrelated cg_uinfo bits survive. */
unsigned int NITMOD_EncodeReloadPreferences( unsigned int clientFlags,
    int autoReloadCvar, int altReloadCvar );
int NITMOD_DecodeReloadPreferences( unsigned int clientFlags,
    nitmodReloadPreferences_t *preferences );
/* Shared projection for client cvars encoded above and received server flags.
 * Reads cmd only; does not overwrite pmext or change the wire format. */
int NITMOD_BuildReloadPolicyFromFlags( const usercmd_t *command,
    unsigned int clientFlags, int weaponRequiresAutoReloadSetting,
    unsigned int scopedAbilityBits, int warMode, nitmodReloadPolicy_t *policy );
/* Consumes the separate, per-call preference input from client/server Pmove. */
int NITMOD_BuildPmoveReloadPolicy( const pmove_t *move,
    int weaponRequiresAutoReloadSetting, unsigned int scopedAbilityBits,
    int warMode, nitmodReloadPolicy_t *policy );
/* Resolves original PM_CheckForReload inputs. attack2ReloadEnabled is the
 * Nitmod setting absent from stock pmoveExt. weaponRequiresAutoReloadSetting
 * is the recovered ammo-record +0x38 flag, NOT a stock ammotable member.
 * Uses native cmd.wbuttons and pmext.bAutoReload; unrelated buttons ignored.
 * Returns 0 on null input/output, leaving policy unchanged. */
int NITMOD_BuildReloadPolicy( const pmove_t *move, int attack2ReloadEnabled,
    int weaponRequiresAutoReloadSetting, unsigned int scopedAbilityBits,
    int warMode, nitmodReloadPolicy_t *policy );
typedef enum {
    NITMOD_RELOAD_ACTION_NONE,
    NITMOD_RELOAD_ACTION_BEGIN,
    NITMOD_RELOAD_ACTION_UNSCOPE
} nitmodReloadAction_t;
typedef struct {
    nitmodReloadAction_t action;
    int weapon;
} nitmodReloadDecision_t;
/* Read-only outer decision; request/automatic policy must already be resolved
 * from input and recovered definition/settings. Scoped bit 0x20 belongs to
 * the scoped ability word, NOT the MG42 word. UNSCOPE requires the existing
 * weapon-change adapter with reload intent; no state is changed here.
 * Returns 0 invalid (output unchanged), 1 evaluated (NONE uses WP_NONE). */
int NITMOD_DecideReload( const playerState_t *state, int weapon,
    const nitmodReloadPolicy_t *policy, const ammotable_t *ammoTable,
    int ammoSlots, nitmodReloadDecision_t *decision );
typedef void (*nitmodReloadWeaponChange_t)( void *context, int oldWeapon,
    int newWeapon, qboolean reload );
typedef enum {
    NITMOD_RELOAD_DISPATCH_INVALID = -1,
    NITMOD_RELOAD_DISPATCH_NONE,
    NITMOD_RELOAD_DISPATCH_STARTED,
    NITMOD_RELOAD_DISPATCH_SWITCH_REQUESTED,
    NITMOD_RELOAD_DISPATCH_RESET_READY
} nitmodReloadDispatch_t;
/* Recomputes the decision from current state, then dispatches once. Switch
 * callback owns native ownership/spinup/respawn/grenade restrictions; the
 * result means REQUESTED, not completed. Callback need only exist for UNSCOPE.
 * Options belong to the requested weapon. No global registry is installed. */
nitmodReloadDispatch_t NITMOD_ProcessReloadRequest( pmove_t *move, int weapon,
    const nitmodReloadPolicy_t *policy, const ammotable_t *ammoTable, int ammoSlots,
    const nitmodWeaponOptions_t *options, unsigned int reloadAbilityBits,
    unsigned int lightWeaponAbilityBits, nitmodReloadWeaponChange_t changeWeapon,
    void *context );
#endif
