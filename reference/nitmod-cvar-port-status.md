# Nitmod Cvar port status

The SHA-256-pinned original tables contain 749 static registrations: 200
cgame, 339 qagame and 210 ui. `original-cvar-inventory.csv` is the complete
row-by-row list with original address, default and flags.

As of this pass every static name is registered in `src_2.60`; none remains
wholly absent. The 148 qagame entries that were missing are now backed by
typed `vmCvar_t` storage, registered at startup and updated while the server
runs. `mod_build` intentionally reports `wasm32` in Emscripten builds.

Runtime-semantic work still required is grouped as follows:

- progression: remaining database/GUID-backed `g_XPSave` modes. The reconnect
  cache now consumes enable bit 1, permanent bit 4 and `g_XPSaveMaxAge`;
  the seven `skill_*` thresholds, seven `g_maxLevel*` controls, `n_noSkillUpgrades`,
  `g_XPDecay`, `g_XPDecayRate`, `g_XPDecayFloor` and `g_maxXP` now have
  runtime consumers;
- player rules: `g_playDead` (runtime ported), `g_classChange` (runtime ported),
  `n_proneDelay`, `n_crouchStandDelay` and `n_standCrouchDelay` (runtime
  ported), `g_slashKill` bits 1/2/4/8/16/64 (runtime ported). `g_realHead`
  and all four `g_realBody` body-bound bits are runtime ported; `g_hitboxes`
  now drives the recovered prone/dead height policy, while its separate debug
  visualization remains outstanding;
- communication/moderation: greeting, mail and GUID/IP controls.
  `n_minNameLength`, `g_floodprotect`, `g_floodthreshold` and
  `g_floodWait` are runtime ported;
- voting/map flow: remaining `g_mapVoteFlags` policies,
  `g_resetXPMapCount`, campaign paths and vote time-limit policy.
  `g_maxMapsVotedFor`, persistent `g_minMapAge` filtering,
  `g_excludedMaps`, and `g_mapVoteFlags` bits 1/2/4/8/16 are runtime ported;
- combat/special weapons: `g_weaponItems` bits 1/2/4/8/16/32 are runtime
  ported; `g_poison` damage/interval and cure bits 2/4/8 are runtime ported;
  `g_rockets`, `g_missileCams`,
  missile speed/health/gravity, throw distance, mortar bounds, adrenaline,
  tripmine limits and artillery controls;
- modes: remaining weapon/charge-related `g_TDMOptions` rules (bits 1, 2, 4,
  8 and 16 are runtime ported),
  remaining `g_misc` bits. Sniper-war damage option bit 2 and crazy gravity
  now have runtime consumers.
  All four `g_war` spawn loadouts and `n_sniperWarOptions` spawn bits 1/4 are
  runtime ported;
- integrations: Omni-bot, Lua, SQLite/user database, map records, ETTV,
  logging and NxAC controls.

The recovered `panzerwar` and `sniperwar` state transitions now complete the
existing war-mode spawn loadouts. Server-console commands accept the original
`1|on|0|off` forms, update `g_war`, touch every connected client with the
original unprotected/knockback-free damage call and broadcast through the
Nitmod center-print path already consumed by cgame. Shrubbot permission and
chat dispatch remain a separate administration-layer task.

`g_teamChangeKills` is the first setting from this recovered batch with a
completed runtime consumer: value zero now suppresses the forced
`MOD_SWITCHTEAM` death, while the original default one preserves it.

Additional completed consumers are `g_msgs`/`g_msgpos` (rotating
`g_msg1`...`g_msg9` delivery), `g_noCharge` (zero class-charge gates in shared
movement), and `g_instantSpawn` (reinforce after the normal death delay without
waiting for the next reinforcement wave).

`g_truePing` now owns the original 64-sample per-client latency ring in
`ClientEndFrame`. Enabled mode publishes its arithmetic mean through
`playerState_t::ping`; disabled mode preserves the engine-provided value.

`g_drawAttackerHP` now sends the original post-death attacker-health chat line
to human victims, including the original live-attacker and tank-death guards.

`g_voting` bits 1/2/4 now follow the original vote lifecycle: after thirty
seconds bit 1 excludes abstentions, bit 2 refunds a successful caller's vote
slot, and bit 4 publishes the caller suffix in `CS_VOTE_STRING`. Cgame strips
that suffix only while resolving a kick target, while retaining it for display.

`g_revenge` now uses typed per-client kill history. A hostile kill records both
sides; killing the player who last killed you emits Nitmod's existing revenge
announcement, awards one Battle Sense point and consumes the revenge target.

`g_misc` bits 4 and 8 now wrap the original Medic health-pack and Field Ops
ammo-pack reward blocks. They suppress periodic score and the corresponding
First Aid/Signals XP/debug awards without suppressing health/ammo transfer,
assist ownership or corrupting the per-client pickup counter.

`g_misc` bit 64 is mapped from the original numeric death cause `0x1a` to the
typed `MOD_DYNAMITE` enum. Dynamite victims enter limbo immediately through the
normal death lifecycle instead of remaining revivable.

The UI runtime now also covers the original profile/rate/redirect controls:
`ui_rate` derives packet settings, `ui_handedness` and
`ui_profile_mousePitch` apply the profile controls, and `ui_autoredirect`
selects automatic reconnect versus the confirmation popup after validating the
redirect address.

`ui_profile` is now audited through its complete selection, create/rename and
`profiles/<name>/profile.dat` persistence path. `ui_showtooltips` is consumed
directly by the shared menu renderer and is likewise no longer registration
only.

The client-control audit now covers compass/notify drawing, alternate quick
messages, limbo and wounded help, announcer text, auto reload/switch,
objective prints and JPEG screenshots. Flame-chunk adjacency also keeps engine
millisecond timestamps in integer arithmetic on WASM instead of converting the
difference through `fabs`.

Original `fc` forced-cvar commands now retain the first local value for every
accepted cvar and restore those values during cgame shutdown. Repeated forces
in one connection update only the server value, while protected names and
malformed identifiers remain rejected. This closes the normal disconnect,
map-change and cgame-restart lifecycle without writing into the shipped pak or
the player's profile files.

`g_dropObj` now gates the original client `dropobj` command and its per-life
drop counter. Red/blue objectives use the original item fallback, forward
offset, velocity and carried model/name transfer through typed ET fields.

`g_maxXP` is now enforced in the authoritative skill-award path. Its original
strict ceiling semantics are preserved: `-1` is unlimited, reaching the limit
resets all skills/XP/rank, and zero performs the reset without the center-print.

`g_privateMessages` now controls the direct `m`/`pm` command path. Delivery
uses Nitmod's original `chat` plus `lc` wire messages, honors mute and receiver
ignore state, strips command-breaking characters and logs successful messages.
The original `/m` and `/pm` prefixes are also intercepted before public,
team or fireteam chat delivery, preventing private text leaking into chat.

The typed `g_slashKill` subset now honors bit 8 (disable selfkill), bit 16
(block while poisoned), bit 64 (block for three seconds after enemy damage),
and the original wounded-player behavior that sends `/kill` directly to limbo.
Respawn-related flags whose source fields are not yet safely identified remain
explicitly open.

The original mode-specific selfkill restrictions are connected as well:
`g_DMOptions` bit 4 blocks it in Deathmatch and `g_TDMOptions` bit 2 blocks it
in Team Deathmatch. TDM bit 1 selects one-team-point-per-hostile-kill scoring
without disabling personal skill progression, bit 4 disables artillery before
charge consumption, bit 8 selects the map-vote cycle, and bit 16 enables
timelimit termination. DM bit 32 applies the matching artillery restriction.
DM bits 1, 2, 4, 32, 128 and 16384 now also have typed runtime consumers:
kill-health bonus, medic regeneration, selfkill blocking, artillery blocking,
supply-cabinet removal and map voting respectively. Other mode bits remain
under semantic audit.

`g_teamChangeDelay` now consumes the original millisecond value against ET's
typed `client->switchTeamTime`. It gates repeated player-requested team
changes, reports rounded-up remaining seconds, and deliberately exempts first
join and forced server/admin moves.

`g_classChange` now consumes the original corpse progress, class and ownership
fields through ET's `BODY_*` macros. A completed steal replaces only
class-specific tools and class identity, preserving the live primary loadout;
the body cannot be reused.

The extended gametype catalog is now shared by qagame, cgame and ui, including
map-vote 6, TDM 7 and DM 8. `g_TDMScore`, `g_TDMObjBonus` and `g_DMFragLimit`
drive typed score, script-endround and intermission paths; DM publishes the
original winner command already handled by cgame.

`g_fear` now credits a selfkill to the most recent living enemy attacker while
the configured millisecond window is active. Bounds, connection, team, health
and timestamp checks are performed before the recovered `MOD_SWAP_PLACES`
attribution; expired, friendly and invalid attackers retain `MOD_SUICIDE`.

`g_defaultMute` now supplies the original vote-mute duration (with the original
60-second minimum). Timed mute state expires through the shared chat/PM guard,
updates userinfo and notifies the client; referee mute remains session-long.

Registration parity does not imply behavioral parity. A Cvar moves out of the
groups above only after its original reads have been mapped to typed engine
state and covered by a deterministic test.

`g_constructiblexpsharing` now follows the recovered authoritative construction
path.  Enabled mode awards each engineer the XP fraction for every progress
step they contribute and suppresses the normal full finisher bonus; default
zero retains ET's full completion award.

`team_airstrikeTime` and `team_artyTime` now control four independent typed
team cooldowns.  Axis and Allies no longer share state, and an artillery call
no longer consumes or checks the airstrike timer.  Successful calls add the
configured seconds; the authoritative frame loop decays and clamps each timer.

`g_XPSave` bit 1 and `g_XPSaveMaxAge` now control the existing typed reconnect
XP cache instead of the inherited hard-coded five-minute timeout. Bit 4 keeps
entries indefinitely, matching the recovered original expiry branch. The
lookup is bounded to its actual `MAX_CLIENTS` allocation and copies the parsed
address without an unaligned integer load, closing two WASM-unsafe paths.
Database/GUID identity and the unassigned mode bits remain under audit.

The localhost map-vote protocol is now closed end to end. Qagame answers the
existing cgame `immaplist` and `imvotetally` requests, validates `mapvote`
updates, supports the recovered three-choice bit and enumerates maps through
the engine VFS. The list respects `g_maxMapsVotedFor`, `g_excludedMaps` and
the persistent map age. `mapvoteinfo.cfg` retains times played, last played,
accumulated votes and fair-selection counts in the original format. ExitLevel
updates that history and launches the weighted vote winner. Remaining flag
policies are still explicitly open. Bit 8 retains VFS map order instead of
fairness sorting; bit 16 routes a successful nextmap vote through intermission
and map selection. The persisted XP-cycle also selects the recovered
`g_mapConfigs/vote_N.cfg` sequence.

`n_minNameLength` now rejects human connections whose cleaned name contains
fewer visible non-space characters than configured. Colour escape pairs are
ignored exactly like the recovered original loop; bots remain exempt.

The three flood controls now guard public, team, fireteam and voice chat with
the recovered 30-second accounting window. Referees bypass the guard; normal
clients use the configured threshold and inter-message delay.

`g_shortcuts` now expands all eleven original placeholders in every text-chat
mode. Typed persistent client history records the last ammo/health provider,
killer, victim and reviver; `[p]` only exposes a currently identified teammate.
Expansion is bounded to `MAX_SAY_TEXT`; unknown syntax remains untouched and
unavailable player history becomes the original `*unknown*` fallback.

`g_censor` now parses its comma-delimited word list and masks case-insensitive
matches before every text-chat delivery. Penalty bit 8 uses the shared timed
mute backend and `g_censorMuteTime`; bit 16 removes ten points from the
player's class skill. Chat penalties 1/4/32/64 now use typed damage, burn and
poison state, with gib taking precedence over the non-gib kill.
`g_censorNames` shares the bounded comma-list matcher: censored spans are
masked, while penalty bit 2 rejects the name both during connection and on a
later rename.

`g_throwDistance` now drives both ordinary health-pack and ammo-pack launch
velocity paths, matching the two original qagame consumers and default 75.

`g_fieldOps` bits 2 and 4 now control full and half charge restoration for
rejected airstrike/artillery requests. Default zero consumes the complete
support cost as in the original. Bit 1 replaces the unconditional Field Ops
binocular grant with the recovered Battle Sense/Signals first-unlock rule.

`n_dynamiteTimer` now uses the original 5000..60000 ms clamp, controls the
armed entity deadline, is published to cgame and supplies the displayed arming
message. Authoritative and client-visible countdowns therefore share one value.

`n_tripmineTimeout` now removes a player's planted tripmines on disconnect and
actual team changes. The typed scan matches only owned `WP_TRIPMINE` entities;
poison mines and ordinary landmines keep their independent lifecycle policy.

`team_maxTripmines` now limits the live `WP_TRIPMINE` entities owned by each
team before a new mine is spawned. Placed mines carry their typed ET team in
`entityState_t.teamNum`, which also restores the original counting contract.

`g_missileSpeed`, `g_missileHealth` and `g_missileGravity` now drive the
authoritative Panzerfaust entity. The original 2500-unit speed fallback,
linear/normal/low/floating gravity modes and positive-health damageable rocket
bounds are mapped to typed ET fields. Guided/homing `g_rockets` modes remain
linear in entity trajectory type but now run their recovered steering Think
routines. Bit 1 follows the owner's view and bit 2 acquires visible enemies in
the original range/cone. `g_missileCams` bits 1, 2 and 4 now create the
recovered owner-only portal for Panzerfaust, mortar and rifle-grenade
projectiles. Bit 1 also controls guided aiming.

The client half of `g_missileCams` is now connected as well. Cgame tracks the
local player's typed Panzerfaust, mortar and rifle-grenade missile states,
applies the original 1/2/4 mask, and renders the recovered `(16,160,160,120)`
secondary viewport. It requires no reconstructed-only snapshot marker and is
therefore compatible with original Nitmod dedicated-server binaries.

`g_mortarBBox` now switches mortar projectiles from the original point trace
to the recovered symmetric `(-2,-2,-2)` / `(2,2,2)` collision bounds. The
default zero leaves the entity bounds untouched.

`g_adrenClasses` and `g_adrenaline` now drive the actual spawn loadout through
the recovered typed adrenaline grant. Class bits, First Aid unlocks, resource
bonus, option-dependent clip count and war-mode suppression are applied.

The qagame-owned legacy Cvar registry now tracks engine modification counts.
Runtime changes refresh and rebroadcast the original `$` and `#` snapshots
instead of leaving an already connected cgame on stale values. The snapshots
now include `g_missileCams`, `g_misc`, all three typed stance delays,
`g_TDMOptions`, `g_adrenaline` and `jp_keepAwards`; these fields previously
existed on the wire but were left at their zero-initialized defaults.

`g_misc` bit 1 now rejects attempts to disarm a teammate's armed dynamite
before changing its health, progress or lifetime. The planter can still
recover their own charge, matching the original owner exception.

Legacy Cvar modification tracking distinguishes the nine `$`/`#` producers
from registration-only gameplay and administration controls. Every handle is
still refreshed, but unrelated changes no longer emit redundant reliable
snapshot commands to every connected client.

`n_voteMaxTimelimit` now clamps a validated `timelimit` vote to the configured
positive maximum before publishing or executing it, matching original
`Cmd_CallVote_f` at `0x69679`. Other vote types and the zero/unlimited setting
are unchanged.

`n_tankMountDelay` now has a typed per-player entity deadline. A positioned
tank dismount starts the configured seconds-long delay, cursor-hint scans test
it silently, and an actual activation attempt receives the original centre
print while the deadline is active.

`n_killAssistances` now consumes typed per-attacker damage totals recorded by
the authoritative damage path. Bits 1, 2 and 4 respectively award enemy-kill
assists, penalize suicide helpers and penalize teamkill helpers; all three use
the original `an` client messages and Battle Sense adjustments. Contribution
slots are cleared on death. `g_multikillTime` also drives the hostile-kill
chain and emits the bounded original `z2` presentation tiers when announcer
bit 4 is enabled.

`n_reviveSpreeOptions` and `n_multiReviveTime` now maintain typed per-client
revive-series state. Five-revive tiers use the existing cgame announcement
contract, multi-revives emit the original type-5 tiers, and option bit 8 emits
and clears the recovered death message. Best-series state remains available
for later persistent-stat reconstruction.

`n_crazyGravity`, its minimum/maximum/interval controls, and
`g_autoQuitDelay` now run from the authoritative qagame frame. Gravity values
are bounded exactly as in the recovered routine, broadcast through the
existing center-print path, and reset to 800 when the mode is disabled. The
auto-quit condition preserves Nitmod's original minute-of-hour calculation.
The recovered strict `0|1` crazy-gravity toggle is also available as the
qagame console command `crazygravity`; its state transition and broadcasts are
kept reusable for the later shrubbot dispatcher reconstruction.

`g_flushItems` now replaces ET's flat-only item settling path. Dropped items
on sufficiently steep surfaces are aligned to the typed collision-plane axis,
traced back toward the supporting surface, snapped and assigned their actual
ground entity. Disabled, non-item and horizontal cases retain the original ET
upright settling behavior.

Custom `recoilDuration`, `recoilYaw` and `recoilPitch` values are now active
in the shared movement firing path. qagame obtains its transactional values
from the map-owned `g_weaponScriptsDir` registry, while cgame parses the same
shared fields from its mounted weapon definition and feeds them into predicted
movement. Invalid durations fall through to the existing native recoil.

The bare custom-definition flag `noMidclipReload` now follows the same active
qagame/cgame path. Both movement callers provide the selected weapon's parsed
flag to shared Pmove, whose existing transactional reload starter rejects a
partially filled magazine while still permitting an empty-clip reload.

The recovered custom-spread group is active in shared Pmove as well:
`SpreadScaleAdd`, `SpreadScaleAddRand`, `spreadRatio`, `velocity2spread` and
`viewchange2spread`. Server movement and client prediction use the same values,
including Nitmod's zero sentinel and scoped/unscoped tri-state defaults.

`limboKill` now sends player-attributed custom-weapon deaths directly to limbo.
On the client, mounted weapon definitions may override both halves of an
original-protocol obituary through `KillMessage` and `KillMessage2`; missing
values retain the recovered built-in obituary table.
