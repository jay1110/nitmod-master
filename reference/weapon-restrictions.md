# Weapon restriction precedence

## Numeric limit reconstruction

nitmod_weapon_limits.c now implements the ordered numeric subset: heavy
percentage, then panzer minimum team share, then a supplied fixed cap. The
result is a reason or NONE, not unconditional permission: class/pickup and
notification policy still belong to the caller. The helper is not active yet.

ELF 0x55fe7 multiplies team size and percentage as integers. At 0x55ff2 the
result is multiplied by float constant 0x3c23d70a (0.01f), stored at 0x22e03c.
The control word is set to round upward at 0x56001..0x56014 before frndint.
Thus rejection is weaponCount >= ceil(product * 0.01f). Since the count is
integer, the helper compares count directly with the unrounded threshold.
This avoids dependence on the host rounding mode while preserving the test.

The panzer branch at 0x56081..0x560ad rejects when teamSize/(maxClients*0.5)
is <= panzerPercent*0.01f. The float coefficient is deliberately retained:
teamSize=1, maxClients=10, percentage=20 passes this comparison; 21 rejects.
Replacing it with exact decimal integer ratios would change that boundary.
For the following fixed cap, only -1 means unlimited, not every negative value.
Rifle-grenade combined-family counts must still be supplied by the caller.

Tests cover 426725 heavy-limit cases (sizes/counts 0..64, percentages 0..100),
4420 fixed-cap cases (-3..64), branch precedence and selected panzer/overflow
boundaries. Out-of-range integer products, negative counts and invalid
panzer denominators reject as INVALID when their branch is reached. This
is deliberate hardening rather than original overflow/division behavior.
Double arithmetic is used instead of x87 extended precision; unusual large
configuration values still require native-i386 edge comparisons.

Original qagame SHA-256:
`84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49`.
G_IsWeaponDisabled begins at ELF 0x55af0. Original class/team primary-weapon
classification is called at 0x55b2f and used later for notification policy.
The extracted precheck does not call or implement that classification.

At 0x55b4c and 0x55c28 the original rejects team 3 unless entity svFlags
contains bit 8. These map to sess.sessionTeam == TEAM_SPECTATOR and SVF_BOT.
This rejection precedes war-mode exemptions: a human spectator cannot use
the exemptions; a bot spectator continues through ordinary checks.

The war-mode early returns are explicit ALLOW results (original false
meaning not disabled). Original IDs are mapped via the ELF item identities:

| Mode | Original IDs | Native symbols allowed before team limits |
| --- | --- | --- |
| 1 | 5 | WP_PANZERFAUST |
| 2 | 24, 30 | WP_GARAND, WP_K43 |
| 3 | 36, 37, 22, 23 | WP_GPG40, WP_M7, WP_KAR98, WP_CARBINE |
| 4 | 1 | WP_KNIFE |

Other weapons do NOT return disabled merely because a war mode is active.
They fall through to G_TeamCount at 0x55b9b and then heavy limits, per-weapon
caps, class/pickup policy and rifle-grenade accounting. Scoped rifle variants
are not covered by the mode-2 early return. Naming a mode is insufficient
evidence for a blanket allowlist.

G_NITMOD_WeaponPrecheck uses a tri-state result: ALLOW, DENY or DEFER.
DEFER requires the later checks; it must not be converted to permission.
Invalid native weapon values and null pointers deliberately deny safely.
Tests cover all 50 native weapons, seven mode values, four teams and bot/non-
bot state (2800 cases), exact exemptions, rejection precedence and no mutation.

The precheck is compiled but not gameplay-active. Existing native
G_IsWeaponDisabled is unchanged. Its G_TeamCount dependency now has active
ordinary team-equivalent counting; see reference/team-weapon-count.md.
Separate tested helpers now cover rifle-grenade counts/revocation, numeric
limits, STEN eligibility and notification selection. Missing work remains:
bind the composed decision tree to class-primary classification,
per-weapon Cvar ownership, counts and configuration lifecycle, then integrate
the guarded caller and message transport. Integrating only early returns into native
ET would not complete Nitmod's weapon restriction contract.

## STEN and notification policy

G_NITMOD_StenAllowed permits Covert Ops, the conjunction of pickup context
and g_pickAnyWeapon, or g_weapons integer bit 0x200. At ELF 0x55f32 the
original tests byte offset 13 of vmCvar_t with mask 2: integer begins at
offset 12, so this is bit 9, not integer bit 1. Tests cover 20480 combinations
of five classes, pickup/override states and option values 0..1023.

G_NITMOD_LimitMessage selects an original nitmod_cp reason only when the
weapon is class-primary, the caller is not silent and PMF_LIMBO is clear.
PMF_FOLLOW alone does not suppress this notification. Primary classification
is an explicit input, not inferred from weapon ownership. Reasons are 0x13
(heavy), 0x14 (panzer team), then fixed-cap reasons 0x15 panzer, 0x16 flame,
0x17 mobile MG42, 0x18 mortar and 0x19 either rifle grenade. These are NOT
native engine event IDs. No message is sent by this helper. ELF examples:
0x56052 heavy, 0x560d9 panzer team, 0x55f9e panzer cap, 0x561ea rifle cap.
The original STEN denial does not enter these cap notification branches.

4000 notification cases cover all 50 native weapon values, primary/silent
states, limbo/follow combinations and five limit results. Both helpers are
read-only and compiled but not gameplay-active. These are deterministic
rule tests backed by disassembly, not original-module runtime comparisons.

## Composed read-only decision

g_nitmod_weapon_policy.c now composes spectator/war early decisions, heavy
percentage, panzer team threshold, STEN eligibility, per-weapon caps and
notification selection for mapped native weapons. Explicit input snapshots
carry configuration and original count values. Class-primary classification
is now derived internally from typed session class/team and pickup options.
No Cvars are registered, inventory changed or messages emitted by this code.
Native G_IsWeaponDisabled remains active until the engine adapter is ready.

The original six-entry heavy table at ELF 0x2a5144 contains IDs
6,29,46,5,33,42: flame, MG42, deployed MG42, panzer, mortar, deployed mortar.
The switch adds individual caps only for base MG42/mortar, not their deployed
forms. The test checks all 50 native weapons with unlimited caps, zero caps
and zero heavy percentage, including priority of heavy over fixed caps.

For GPG40/M7 the caller supplies equipment-qualified own-family and opposite-
family counts. ELF 0x561b4..0x561ba adds these before the shared cap comparison.
An unlimited cap (-1) returns before requiring those counts. 3240 combinations
cover both weapons, family counts 0..8 and caps -2..17. Additional tests cover
overflow, negative counts, early war exemption, spectator/bot precedence,
panzer branch ordering, suppressed messages and STEN pickup override.
All checks verify input, entity and client state remain unchanged.

Invalid required counts and overflowing sums return DENY/INVALID without
a player-facing cap reason, a deliberate safety difference from integer wrap.
The function never returns DEFER; ALLOW assumes its supplied snapshot is
correct, not that the not-yet-connected engine has been checked. Host tests
do not replace original-i386 runtime or browser parity evidence.

## Connected original primary classification

G_NITMOD_IsClassPrimary reconstructs qagame BG_WeaponIsPrimaryForClassAndTeam
(ELF 0x32470). The two five-record tables start at 0x2a79c0 (Axis) and
0x2a7ac0 (Allies), record size 48, six weapon slots at byte 16. Original
IDs are mapped to native symbols. Soldier and Covert Ops match native ET;
Medic/Field Ops additionally accept the opposite MP and STEN, and Engineer
accepts the opposite MP. Native ET tables therefore cannot stand in for this
classifier. They remain unchanged; this is not loadout/menu activation.

Only Axis/Allies qualify. The pickup-context plus g_pickAnyWeapon override
precedes weapon-zero rejection and class lookup (ELF 0x32508 and 0x32570).
Consequently WP_NONE qualifies under that override, but never by matching
zero-filled slots. Invalid native weapon IDs reject safely; invalid classes
reject before indexing unless the original override already applies.

4000 combinations cover five classes, four teams, all 50 native weapons and
both pickup/override booleans. Additional cases exercise invalid class/weapon,
null entity/client and override order. Tests verify no client mutation.
G_NITMOD_EvaluateWeaponPolicy now calls this classifier instead of trusting
an externally supplied isClassPrimary flag. Gameplay activation still awaits
Cvar/count snapshot and message integration; no protocol change is introduced.

## Existing-Cvar reader

g_nitmod_weapon_config.c atomically reads the eleven existing engine Cvars
used by the mapped restriction inputs: g_war, g_pickAnyWeapon, g_weapons,
g_heavyWeaponRestriction, sv_maxclients (the g_maxclients registration name),
team_panzerRestriction and the five fixed caps. Counts, pickup context and
silent mode remain unchanged. Signed g_weapons values preserve their bit
pattern through unsigned conversion; only -1 retains the numeric cap's
unlimited meaning. No default is invented and no Cvar is registered or set.

The reader rejects missing, truncated, nondecimal and out-of-int-range
values without partial changes. This is intentional hardening compared with
the original vmCvar integer conversion. Tests inject six invalid values at
each of eleven positions, an oversized value with a valid-looking prefix,
and check exact field mapping, -1/512 option bits, negative caps and null input.
This tests an engine trap double, not live engine Cvar timing. Cvar defaults,
flags and update/latched semantics still require recovery before activation.

### Registration defaults recovered and activated

The above missing-default limitation is now resolved for these eleven Cvars.
tools/extract_weapon_cvars.py reads hash-pinned gameCvarTable at ELF
0x2a7e20, length 0x2514: 339 seven-word/28-byte records. G_RegisterCvars
passes words 0..3 to trap_Cvar_Register and advances seven words per record.
The extractor reports original record and vmCvar addresses for review.

Eight previously absent Cvars are now registered from G_RegisterCvars:
g_war, g_pickAnyWeapon, g_weapons and team_panzerRestriction default to 0;
team_maxFlamers, team_maxMG42s, team_maxMortars and team_maxriflegrenades
default to -1. All have flags=0, trackChange=0 and reset=0 in the original.
Native sv_maxclients (20, flags 37), g_heavyWeaponRestriction (100, flags 5)
and team_maxPanzers (-1, flags 0) already match and are not re-registered.

Registration uses NULL vmCvar destinations, as supported by ET's trap:
the new reader fetches current engine strings and does not maintain mirrored
vmCvar objects. No trap_Cvar_Set is used, preserving configured values under
engine registration semantics. The eight entries require no latch/archive/
reset flags. Mirrored-value update timing for original gameplay consumers
is still not reproduced, and weapon-policy activation remains pending.

The executable trap test checks both first and repeated registration calls.
test_weapon_cvars_reference.py compares all eight source registrations with
the original ELF and checks the registration hook plus the three existing
original defaults/flags. This is host/reference evidence, not a live-engine
test of map restart or user configuration persistence.

## Server adapter composition

G_NITMOD_EvaluateServerWeaponPolicy now connects existing engine Cvar reads,
the explicit population cache, live weapon counts and the typed evaluator.
It does not refresh the cache, change inventory or transmit reason IDs.
Precheck ALLOW/DENY skips count reads, preserving war/spectator decisions
even before cache initialization. A DEFER requires a valid cached snapshot.
Missing/malformed configuration returns DENY/INVALID before evaluation, a
deliberate safety rule rather than original permissive conversion behavior.

The executable integration test links the actual config, counting and policy
implementations with Cvar trap doubles. It covers unavailable cache, war
bypass, cache refresh, cross-family rifle cap/status transitions, class-based
STEN decisions, missing configuration and spectator precedence, checking that
clients remain unchanged. Native G_IsWeaponDisabled is still not replaced:
bot/class-command refreshes and message transport remain incomplete.

## Weapon-limit ncp transport subset

Original nitmod_cp at qagame ELF 0x10bdf0 sends `ncp %i` (format at
0x24ebb4), targeted to an entity slot or broadcast for null. Original cgame
indexes SrvMsgs (ELF 0x138ac0, 58 pointers) and center-prints at y=384, width=8.
Only weapon reasons 19..25 are reconstructed here; special dynamite reason 7
and all other messages are deliberately outside this transport capability.
tools/extract_weapon_messages.py extracts the seven strings from hash-pinned
cgame; the reference test compares them with the shared bounded text table.

Feature bit 10, NITMOD_FEATURE_WEAPON_MESSAGES, is advertised by both rebuilt
modules. NITMOD_SendWeaponLimitMessage sends only supported reason IDs to an
individual capability-negotiated client. No null/broadcast API is provided.
The cgame ncp branch requires that feature, exactly two command arguments,
strict integer parsing and a known reason before CG_CenterPrint. Invalid IDs
cannot index outside the recovered table, unlike the original unchecked read.
No UI protocol path is needed: this command is consumed entirely by cgame.

Bounds/capability-mask tests and source checks cover the subset transport;
the original text comparison is hash pinned. End-to-end engine transcripts
are still pending. The server adapter does not yet invoke the sender, and
native weapon restrictions remain active. No gameplay completion is claimed.

## Decision-to-notification transaction

G_NITMOD_CheckWeaponAndNotify now wraps the read-only server evaluator and
invokes the capability-gated sender at most once for a denied result with a
nonzero message reason. It validates entity-slot membership and matching
level.clients ownership before any notification, without pointer subtraction.
The result describes policy, not delivery; unsupported clients remain silent
through the existing sender gate. No inventory mutation or cache refresh is
introduced, and native G_IsWeaponDisabled still has not been replaced.

The adapter test uses a sender spy to verify target/reason and one invocation,
with no client mutation. Silent, limbo, non-primary, allowed and invalid-config
paths produce no invocation, nor do null/detached/mismatched-client inputs.
Capability gating itself is covered separately by transport source checks;
this spy test is not a live network or browser delivery test. Remaining work
includes class/Omni-bot cache paths and final gameplay-callsite integration.

## Reconstructed setclass handler, dispatch still disabled

Cmd_SetClass_f now lives in g_nitmod_class_command.c rather than the empty
g_cmds.c stub. Original nitmod_cmds.c supplies query text, current-team name,
optional latchPlayerType update and the false-SetTeam branch ordering:
refresh population, then set weapons/update clientinfo. This implementation
uses native enum arguments and the existing native G_SetClientWeapons;
the command remains commented out in g_cmds_ext.c until restriction activation.

Intentional safety differences: spectator/free input returns after the error
instead of passing an uninitialized team buffer; weapon tuples are strictly
validated before state mutation, with no original four-byte truncation.
Missing weapons remain WP_NONE; invalid class input preserves the old latch.
Malformed numeric class input is not coerced to soldier. Entity/client slot
identity is checked. Original numeric weapon IDs must not be sent to this
native-enum handler. Active UI/loadout tables are unchanged.

Tests use engine/game spies for class queries, both teams, SetTeam true/false,
refresh-before-weapon ordering, missing weapons, invalid weapon/class input,
spectator rejection and null input. Native weapon restriction behavior is
still delegated unchanged; this is not a completed Nitmod loadout port.

## Typed loadout transaction

G_NITMOD_SetClientWeapons in g_nitmod_loadout.c reconstructs the mapped
G_SetClientWeapons transaction: retain requested secondary, accept primary
or clear it to WP_NONE on denial, publish only when either latch changed and
updateClient is enabled. It calls the composed policy/notification adapter.
It is compiled but not yet substituted for the active native setter.

Invalid/unavailable policy, invalid native weapon IDs and invalid client
ownership return -1 without latch changes. This deliberately hardens original
behavior. Evaluation/notification occurs before both latch writes, whereas
the original wrote secondary before checking primary; this avoids partial
mutation on configuration failure. No ammo, inventory or current weapon is
modified. Tests compare the entire client structure and check publication
ordering, accepted/denied branches, repeated calls and invalid inputs using
policy/publication spies. They do not prove engine runtime parity.

Remaining bot paths are ETInterface_ChangeClass and ETInterface_ChangeTeam
in original nitmod_runtime.c. They depend on Omni-bot C++ MessageHelper,
bot/game enum conversion and weapon-choice callbacks absent from this native
ET tree. They must not be wired to the unrelated built-in ET bot AI merely
because both handle bots. The shared typed loadout transaction is prepared;
Omni-bot ABI and lifecycle reconstruction remains a separate unfinished area.

## Class-handler loadout connection and integration test

The false-SetTeam branch of the disabled Cmd_SetClass_f now calls
G_NITMOD_SetClientWeapons after population refresh instead of the native
setter. The SetTeam implementation itself is unchanged and still uses native
weapon handling internally; dispatch therefore remains disabled. This is not
a claim that every class-change branch is migrated. Class latch mutation
precedes this call as in the original; atomic loadout failure applies to the
weapon latches, not to the entire class/team command.

test_nitmod_weapon_adapter now links real configuration parsing, cached/live
counting, classification, numeric policy, notification transaction and loadout
implementation together. Engine Cvar reads, sender and clientinfo publication
remain test doubles. Scenarios include accepted selection/repeat, denied
selection/repeat, missing configuration and invalidated map cache. Denied
repeats still request a notification on every check while unchanged latches
do not republish clientinfo, matching the original setter's conditional update.
No network or engine-session parity is inferred from this host integration test.

## Active weapon-settings snapshot correction

Original nitmod_SendNCS in nitmod_core.c sends team_panzerRestriction as the
first # field, not g_heavyWeaponRestriction. The earlier native port used the
wrong source. G_NITMOD_RefreshWeaponSnapshot now maps that field, all five
weapon caps and g_weapons from the registered/validated Cvars into the
existing snapshot; nitmod_RefreshBaseSettings uses it on its existing refresh
path. The client parser and wire field order are unchanged. Other settings
and gameplay state are preserved. This advertises configuration, not proof
that every related gameplay path is already activated.

Tests distinguish panzer=20 from heavy=100, compare all preserved fields,
exercise -1 and 512 weapon-option representations, and inject malformed data
at every input position. Mapping failure preserves the previous weapon
snapshot atomically. This intentionally retains last-known-good values for
malformed Cvars; the restriction evaluator separately reports invalid input.
The source hook test prevents reintroducing the heavy/panzer mix-up. Runtime
client/server transcripts remain pending.

## Pickup-specific policy

g_nitmod_pickup.c reconstructs the post-restriction G_CanPickupWeapon
decision from sorted nitmod_weapons.c. It requires an explicit ALLOW from
the earlier restriction check (pickupContext=1); DENY and DEFER never permit
pickup. Unlike the restriction precheck, war modes return final allowlists:
panzer; base Garand/K43; base KAR98/Carbine; knife, respectively. Rifle-grenade
IDs are not allowed by the mode-3 pickup branch. War rules precede pickAny,
knife and class-mask overrides.

Outside war modes, knife/pickAny bypass class policy. An explicit matching
per-weapon class-mask bit overrides default class lists and the Medic option.
Otherwise Medic bit 4 disallows MP40/Thompson/STEN; other mapped classes use
the original default weapon sets. STEN eligibility from G_IsWeaponDisabled
still applies first and must not be bypassed by calling only this helper.
The original per-weapon mask at BG_Weapons record +0x6ac and g_medics ownership
are not yet reconstructed; they remain explicit inputs. Native pickup code
is unchanged and no new protocol is introduced.

192000 combinations cover five classes, fifty native weapons, six mode
values, pickAny, all five-bit masks and Medic option on/off. Each also checks
DENY/DEFER rejection and no client mutation. Boundary/null tests are included.
These deterministic rule tests are not original-engine pickup replay proof.

### Pickup configuration ownership

Original BG_RegisterWeapon zeroes its 0x6b0-byte record before parsing.
The BG weapon parser recognizes `classes` via PC_Int_Parse into +0x6ac;
this is the permission mask consumed by G_CanPickupWeapon, not a player
skill mask. Missing classes therefore starts at zero on record registration,
but parser/reload failure semantics and the complete .weap parser remain
unported. Do not substitute a constant zero for configured weapon records.

The original gameCvarTable registers g_medics with default 0, flags 0,
trackChange 0 and reset 0. It is now the ninth missing Cvar registered by
G_NITMOD_RegisterWeaponConfiguration; existing configured values are not set
or overwritten. G_NITMOD_ReadMedicOptions validates its signed decimal value
before unsigned bitmask conversion and preserves output on failure. Tests
cover 0, 4, -1, malformed/overflow/missing/truncated input and null output.
The ELF registration test now verifies all nine registrations. No Medic
gameplay behavior is activated by registration alone; pickup still requires
the typed policy and original weapon-mask owner to be connected.

## Composed pickup adapter

G_NITMOD_CanPickupWeapon connects a single validated configuration snapshot,
Medic options, explicit population cache and live counts to restriction and
pickup policy. It returns 1/0/-1 for allow/deny/unavailable, sends at most one
gated restriction message and never grants/drops an item. The caller must
supply a validated class mask; the native item pickup path is unchanged.
Integration tests cover STEN restriction before class-mask override, Medic
default versus explicit mask, pickAny versus final war allowlist, heavy denial
notification, missing config/cache and no client mutation. Output remains
stubbed, not an actual network or gameplay replay.

BG_RegisterWeaponFromWeaponFile selects `both` for normal definitions and
`both_altweap` for alternate definitions. A global textual search for classes
cannot safely populate masks. BG_RegisterWeapon first attempts the configured
directory then weapons/ fallback, and zeroes records before reading. Full
parse success, failed reload handling and section selection remain unported;
the adapter intentionally does not pretend a mask of zero is verified data.

### Strict mask-definition subset

nitmod_weapon_definition.c now parses an engine-tokenized weaponDef envelope,
selecting both or both_altweap and ignoring balanced client/unselected blocks.
Selected blocks currently accept only classes integer assignments; other
attributes fail rather than risk treating their values as keys. Missing classes
in an otherwise accepted envelope yields zero; repeated selected assignments
use the last value. The result is committed only after the outer closing brace.
Unclosed blocks, bad/overflowing integers and unknown selected fields preserve
the caller output. Nested skipped blocks are bounded to depth 64 and total
reads to 65536. This is a strict subset, not a complete .weap validator.

Tests cover section selection, nested client blocks, repeated values,
negative masks, empty definitions, truncation at every token boundary and
malformed/unknown fields. Unary minus may be a separate engine token;
the split-token INT_MIN spelling is now supported by unsigned-magnitude
conversion; repeated signs are rejected. At this initial stage file loading, token-reader
adapter, parse-error reporting and reload ownership remain unconnected.

### Engine source adapter for the strict subset

g_nitmod_weapon_definition.c now supplies engine pc_token_t strings to the
subset parser. G_NITMOD_LoadWeaponClassMask takes explicit preferred/fallback
paths and normal/alternate selection. It attempts fallback only if opening
the preferred source fails, not if contents are invalid. Each acquired source
is freed once on either parse success or failure; output changes only on
success. Identical fallback paths are not opened twice. It does not publish
weapon state or implement registration/reload ownership.

Quoted strings are opaque data, so quoted braces in client blocks cannot
close structural blocks. Quoted selected keys/numbers reject deliberately;
unterminated engine token buffers fail safely. Tests with engine-token doubles
cover preferred/fallback open outcomes, parse truncation, normal/alternate
selection, quoted braces/numbers, null inputs and resource accounting. A real
engine lexer/file transcript and full .weap grammar are still pending.

Lifecycle review confirms original ClientBegin, ClientDisconnect and the
successful ClientConnect tail call CalculateRanks followed by
G_TeamCountPlayers. Bot/team-command paths also refresh explicitly. Those
hooks remain unmodified until the cache consumer and configuration lifecycle
can be connected together; recomputed snapshots alone do not prove parity.
