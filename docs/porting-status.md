# Nitmod reconstruction status

## Review 2026-09-06

Continuation worktree verified against the available source state: clean initial
Git status in this checkout and the origin checkout, all three original modules
present and SHA256 matching reference/original_nitmod_i386.sha256. Fresh local
Emscripten configuration and all three WASM module builds passed, including
vmMain/dllEntry/vmWasmAbi1 post-link checks. Existing compiler warnings remain.

Spawn reward verification now independently varies Light Weapons, First Aid
ammo/syringe, Engineering and Covert reward gates. Unlike the previous common
mask fixture, this detects wrong-skill reads and doubled OR bonuses. It also
preserves nonzero starting inventories and compares the entire gclient_t after
each call; irrelevant mask bits and negative/extreme war values are covered.
155,520 actual AddExtraSpawnAmmo WASM cases pass against the recovered switch
in sorted/nitmod_unknown.c. No production behavior changed in this block.

Reproduce the cohesive spawn adapter suite with an activated Emscripten SDK:
`python tools/run_wasm_spawn_checks.py`. All four fixtures pass: spawn rewards,
25,600 health cases, 480 secondary correction plus 81,920 fallback cases, and
3,240 actual secondary grant cases. These use engine boundary stubs; they are
not complete ClientSpawn execution, original-binary replay or browser parity.
User-confirmed knife throw/tripmine functionality supersedes older open entries.
The real uploaded nkey import retest remains pending. No pak, engine, original
module or external Omni-bot changes were made.

## Review 2026-09-05

User confirmed tripmine and knife throw working. Uploaded nkey screenshot
shows correct nitmod home path and FS_READ length=100: strict 44-byte file-size
gate was rejecting the file before decoding. Loader now reads only the first
44 bytes for lengths >=44, consistent with original decode64 padding stop;
strict prefix/checksum validation remains and no file is rewritten. Actual
loader WASM test covers sizes 0..100, arbitrary trailing bytes and invalid
prefix; all pass. cgame rebuilt/export checked. User's real key content was
not read; browser verification of that specific key remains pending.

OPEN user reports: tripmine cannot be wall-placed/armed; uploaded nkey.dat
not accepted. Need local-vs-original-server and upload destination to isolate.
Added secret-free nkey loader diagnostic distinguishing unavailable file,
wrong byte length and decoder/checksum rejection; no key/file mutation added.
cgame WASM rebuilt/export checked. Neither reported bug is claimed fixed.
Original decoder stops at padding, while current loader requires exactly
44 bytes; trailing-data compatibility is a candidate, not an established cause.

Reported +attack2 knife crash (Unknown event 131): PM_NitmodThrowKnife emits
EV_NITMOD_THROW_KNIFE; prediction calls CG_EntityEventForProtocol with original
false. Existing extended handler accepted 131 but was gated behind original,
so prediction reached the fatal default. Dispatch now admits this specific
internal event irrespective of protocol. Original wire event 95 retains its
existing handler; native ET 94..106 are not globally reinterpreted. Knife
emission/spawn/handler/prediction source regressions pass. cgame WASM rebuilt
and exports checked. Browser reproduction/retest still pending; qagame/ui
unchanged. This is a routing fix, not suppression of unknown events.

Preview lifecycle verification: executable ui_main.c WASM fixture covers start,
handle reuse, invalid-selection stop, failure latch and empty-list reset.
All assertions pass. This tests the existing safe adapter, not original binary
runtime parity: original ownerdraw 254 decompilation appears to call Play for
every handle >= -1; that behavior requires further disassembly/engine review
before any change. No production code changed during this verification.

Browser refresh ownerdraw 247: restored literal status messages instead of
ET translation calls, matching original ui_ui_draw.c case 0xf7 (waiting,
server count, refresh timestamp). Scoped change only; other translations
remain. Three-string reference/source regression passes; UI WASM rebuilt
and export checked. No rendered browser test; cgame/qagame unchanged.

UI ownerdraw 258 / UI_SAVEGAME_SHOT now matches original empty case 0x102
in ui_ui_draw.c. Removed obsolete ET savegame screenshot draw helper and its
unchecked selected-index access; savegame actions were not modified. Expanded
source-reference test verifies 17 no-op dispatches and retained active draws.
UI WASM rebuilt/export checked; cgame/qagame unchanged. No visual runtime
comparison performed for this change.

Crosshair health audit: original CG_CrosshairClientMaxHealth (cgame_client.c
around 6280) independently counts viewer-team medics, caps their bonus at 25,
then applies target Battle Sense bit 8 and medic multiplier. Existing cgame
adapter already follows this; deliberately did not replace it with server
war-mode rules. Actual cg_nitmod_hints.c WASM fixture now checks 48 additional
viewer/target-team, valid-entry, medic-count and reward cases, all passing
alongside existing override/capability tests. Verification-only change; no
production module rebuild or new feature claimed for this audit.

Health reward gate: G_NITMOD_SetHealthLimits now selects the +15 Battle Sense
bonus from reward bit 8, matching original AddMedicTeamBonus (nitmod_unknown.c
around 1567, client +0xed0). G_NITMOD_SpawnHealth uses the same gate when
subtracting that bonus; numeric levels no longer independently affect it.
Actual g_client.c WASM tests pass 25,600 independent mask/level/class/medic/
war/gametype/override combinations, including existing medic overhealth rules.
qagame rebuilt and export checked, cgame/ui unchanged. This verifies the
adapter and recovered gate, not a full original-module gameplay replay.

Secondary spawn cleanup: removed the unreachable legacy team/class switch
after the correction/default adapter became total. A single call now grants
secondary weapons; obsolete doubled-SMG ammo code is no longer retained.
Updated source-wiring test to check the unified path instead of eight legacy
conditions. Actual adapter's 3,240 WASM cases still pass; qagame rebuilt and
exports checked. This removes dead code, not a new gameplay parity claim.

Secondary fallback mapped: original client +0xb0c is cg_uinfo bit 6
(nitmod_client.c around 2603). Invalid requested weapons now select defaults
using Heavy/Light reward bit 16 and that opt-out, including covert silenced
Akimbo. Evidence: G_AddClassWeapons mask/fallback branches in nitmod_weapons.c.
81,920 independent fallback mask/team/class/opt-out combinations, 480 selector
combinations and 3,240 actual grant-adapter cases pass in WASM. qagame build
and exports checked. Legacy branch is now unreachable but retained pending
cleanup; no claim of complete class-loadout or browser parity. Respawn already
sets covert silencer mode in bg_pmove.c; no extra state override added.

Valid secondary selections now enter G_NITMOD_GrantSelectedSecondary during
spawn: calls the recovered correction, grants typed configured ammo, initializes
the Akimbo companion clip and adds covert alternate weapons. Adapter keeps
the existing primary selection because ET 2.60 grants primary first (original
G_AddClassWeapons grants it after secondary). When both selections resolve to
the same weapon, existing primary ammo wins. Invalid correction NONE retains
the existing selection path pending mapping of original fallback conditions.
Actual g_client.c WASM fixture passes 3,240 request/team/class/level cases and
same-primary ammo preservation. qagame rebuilt/export checked; cgame/ui current.
No full spawn/browser replay or complete secondary fallback parity claimed.

Secondary correction reconstructed as typed NITMOD_CorrectSecondaryWeapon
in nitmod_secondary_weapon.h. Source: original nitmod_weapons.c lines 102-136.
Preserves numeric-level tests in this function (distinct from later fallback
reward bits), team correction, dualSMG restriction, medic option 2, covert
silenced Akimbo and invalid-selection NONE. WASM executable: 480 combinations
with six assertions each pass. Not yet wired into spawn: selection order and
fallback semantics must be integrated together; production modules unchanged
by this preparatory step. No full original-binary runtime comparison claimed.

Secondary spawn reward gates: six Akimbo and two soldier secondary-SMG
branches now use Light/Heavy Weapons bit 16 instead of numeric level >= 4.
Evidence: original G_AddClassWeapons in nitmod_weapons.c, mask offsets
0xee0/0xee4 and 0x10 tests (around lines 175/231). This migrates the gates
only; the full original G_CorrectSecondaryWeapon selection/fallback path
and remaining class loadout differences are still open. Source-wiring test
checks all eight sites; this is not an executable full-spawn parity test.

Spawn binoculars: Engineer/Medic/Soldier grants now require Battle Sense
reward bit 2 rather than numeric level >= 1. Original evidence is
G_AddClassSpecificTools_part_3, nitmod_game.c around 2257: mask at 0xed0
shifted by 1 and masked with 1; Field Ops has its separate Signals/options
override (already present). Source-wiring regression passes; qagame WASM
rebuilt with export checks. This is not a live spawn test. cgame/ui unchanged.

Spawn reward parity: actual AddExtraSpawnAmmo now tests explicit reward bits
instead of numeric skill levels, suppresses bonuses in war modes 1..4, and
allows Light Weapons bit 2 for scoped rifles as in the original. Evidence:
qagame AddExtraSpawnAmmo ELF 0x476f0 (unsigned jbe war gate at 0x47717),
sorted nitmod_unknown.c line 897 onward. Original G_AddClassWeapons assigns
base grenade counts 4/1/4/1/2 for soldier/medic/engineer/fieldops/covert, then
adds the engineer/medic bonus; it does NOT use the refill maximum at spawn.
No blanket max-ammo spawn override was introduced. Executable WASM fixture
includes the actual g_client.c routine: 25,920 weapon/class/mask/level/war
combinations plus isolated scoped Light Weapons assertion pass. WASM targets
build successfully; qagame relinked and export-checked, cgame/ui up to date.
Browser gameplay parity remains untested for this change.

Grenade refill integration: BG_AddMagicAmmoWar and BG_CanItemBeGrabbedWar
now share the recovered reward-mask cap and explicit cached war mode in
qagame AddMagicAmmo/Touch_Item. This matches the inline table selection and
g_war guard in original nitmod_bg.c BG_AddMagicAmmo (around line 5044).
Compatibility entry points retain the legacy level path when rewards are NULL.
Actual bg_misc.c WASM execution passes 12,800 class/mask/war/team/clip cases
covering pickup eligibility, non-mutating ammo probes, grants and saturation;
existing syringe/poison/adrenaline/knife tests also pass. All three WASM
modules rebuilt successfully with export checks. No browser gameplay run.
Spawn quantities remain a separate open parity item: G_AddClassWeapons uses
its own class branches; no unverified spawn override was added. No pak or
engine changes, and no new network messages or cvars.

Shared grenade API added: BG_NitmodGrenadesForClass uses verified embedded
rows, explicit reward masks and war mode without engine calls. Executable WASM
fixture now links actual bg_misc.c and checks the API for 640 combinations.
Not yet called by spawn/refill; both must migrate consistently. Existing cached
G_NITMOD_ConfiguredWarMode can supply server state. No configuration writer
is assumed. This is shared-core implementation, not a completed gameplay port.

Grenade evidence follow-up: extractor now pins both cgame and qagame SHA-256
and verifies all seven embedded rows match (cgame table 0x12e4c0). Original
qagame BG_GrenadesForClass x87 sequence at 0x21533..0x215d1 sets truncation
control bits 0xc00, converts contributions separately, then adds integers.
Added positive/negative fractional tests; candidate calculator passes. No
runtime configuration writer has been established; earlier 'configurable'
wording was a hypothesis, not proven behavior. Gameplay integration remains
pending, production module behavior unchanged in this verification step.

Grenade reconstruction: hash-pinned ELF extractor now reads CSWTCH.87 class
mapping [5,2,1,3,6] and seven six-float jP_GrenadesPerLevel rows. Typed candidate
calculator includes class reward plus light-weapons reward and war suppression.
640 WASM class/mask/war tests plus additive reward pass. Not wired into live
BG_GrenadesForClass yet: configuration transport/loading and validated numeric
conversion ranges remain required. Existing gameplay is deliberately unchanged.
Reference table baseline: engineer 4->8; medic/signals 1->2->3; heavy 4->5;
covert 2->3, with transitions selected by changed entries and reward bits.

Grenade reward-table reconstruction started: typed NITMOD_RewardTableValue
implements original BG_GrenadesForClass adjacent-entry change test with sparse
reward masks. 46,656 WASM cases compare against the explicit original branch
sequence. Not yet connected to gameplay: jP_GrenadesPerLevel configuration,
class-to-skill mapping, light-weapons contribution, conversion and g_war gating
must be reconstructed before replacing BG_GrenadesForClass. No claim of working
new grenade limits. Original qagame symbols: table 0x2a5160, CSWTCH.87 0x22df90.

Server-status parser runtime audit: actual UI_ParseServerStatus tested in WASM
for each population 0..64 (all row numbers, score/ping/name values and non-null
columns checked), malformed row isolation, names with spaces, empty input and
maximum-size non-delimited input. All pass. Original UI_GetServerStatusInfo
player-row/column layout inspected; existing bounded parser retained. This turn
adds verification, no new production feature. Synthetic transcripts are not
original-binary replay or live engine testing.

Server status values: removed reconstructed g_gametype decoration. Original
UI_GetServerStatusInfo sorting at LAB_000254bf swaps value pointers unchanged
and only renames keys. Actual UI_QueryServerStatus WASM fixture verifies seven
values including known IDs, leading zeroes and unknown strings remain intact
under Game type. All pass; all WASM targets build, ui exports checked. Status
network response is stubbed; live panel comparison remains pending.

Human-count precedence: original LAB_000245f7 treats ET Legacy master humans
as authoritative even when empty (strtol yields zero). Port now does the same
instead of falling through to positive-ping player counting. Explicit status
humans still wins; non-Legacy master values remain ignored. Nine executable
WASM tests link actual counter/status parser and verify precedence, bots,
empty input and retained safety clamps. All pass; all WASM targets succeed,
ui exports checked. Live browser replay remains pending.

Browser refresh cache lifecycle: full refresh/source change now zeroes stored
human counts, matching original reset of g_dat_003e9078. Centralized all local
status cache resets, including timestamps, pending/known flags, population
contributions and NxAC unknown sentinel. WASM fixture dirties and verifies every
server slot after reset; comparator/transitivity checks still pass. All three
WASM targets succeed, ui exports checked. This tests local cache state, not
engine request cancellation or live asynchronous refresh parity.

Browser population comparator: original UI_ServersSort column 2 always chooses
UI_ServersQsortCompare_bis (stored counts). Removed mixed known/unknown engine
comparison from SORT_CLIENTS: unknown entries use zero, never stale prior-refresh
counts. Other sort keys retain engine comparison. WASM fixture executes actual
comparator, checks 32 directional comparisons, transitivity across mixed known
states, and delegation for host sorting. All pass; all WASM targets build, ui
exports validate. Unknown-zero policy is explicit; live async browser replay
and exact original cache-initialization parity remain pending.

Executable description-layout coverage: test_nitmod_description_wasm.c links
actual ui_nitmod_description.c with fixed glyph metrics/draw capture. Checks
three alignments, supplied offsets, blank lines, literal/single/double-star
handling, CR normalization, empty text, zero width and a 2500-byte word split
into bounded 1023/1023/454 chunks. All pass in WASM/Node. This turn adds runtime
coverage, no new production feature. Not an original-binary or pixel replay;
known layout differences documented below remain open.

Objectives text now uses bounded shared UI_DrawDescriptionText instead of a
second unbounded 1024-byte wrapping loop. Original UI_DrawMissionBriefingObjectives
reference: mapname lookup, nullable objectives, newline/tab boundaries, supplied
text offsets, alignment and height+5 leading. Uses stars=0 (literal asterisks).
Shared renderer safely splits oversized words and measures current line width
rather than the original lagging width; these are deliberate safety/layout
differences, not exact pixel parity. Source routing regression passes; all WASM
targets build and ui exports validate. Live text comparison remains pending.

Campaign map-shot follow-up corrects previous empty-slot early return: original
UI_OwnerDraw cases 263..268/LAB_000303f0 draw unknownmap for a NULL slot then
apply the same progress lock overlay as successful images. Slots past mapCount
now safely resolve to NULL without suppressing the image; invalid fixed-array
indices/counts remain rejected. Unified image/overlay drawing removes duplicate
branches. Source regression extended and passed; all WASM targets succeed.
This supersedes the prior empty-slot behavior; live visual comparison pending.

Campaign preview selection consolidated across name, shot, cinematic and map
shot. Original reset-to-zero for invalid selection with existing catalog is
retained; empty/oversized catalogs and index==count are now safely rejected or
normalized before access. Map-shot slot and mapCount bounds added. These are
deliberate safety differences, not new original features. Four-route source
regression passes; WASM ui rebuilt/export checked, all three targets succeed.
Live campaign preview parity remains pending; no pak or engine edits.

UI server filter: accepted keys now directly reset filter index to zero and
rebuild display list, matching original UI_OwnerDrawHandleKey case 0xde.
For valid state the previous single-entry cycling was equivalent; direct reset
also avoids integer overflow. Fixed index==count acceptance in filter drawing
and width calculation (safety difference). Original-source/reset/bounds checks
pass; WASM ui rebuilt/export checked and all targets succeed. Live UI testing
remains pending; no pak or engine changes.

UI ownerdraw key dispatch aligned for IDs 237,239,241,243: original
UI_OwnerDrawHandleKey has no cases for these (default returns 0). Removed
ET opponent/bot/red-blue/selected-player handler calls, retaining false return.
Team-slot handlers remain intentionally active despite draw no-ops, as original
explicitly handles 210..219. Source regression verifies original case inventory
and production routing. WASM ui rebuilt/export checked; all targets succeed.
Interactive keyboard/mouse replay remains pending; no pak/engine edits.

UI visibility: removed inherited ET leader/not-leader filtering. Original
UI_OwnerDrawVisible in ui_ui_misc.c never tests bits 1 or 2; production now
consumes them without changing visibility. This also eliminates selected-team
array access from this path. Other visibility rules remain unchanged. Source
regression verifies original tested masks and retained production rules.
WASM ui rebuilt/export validated; all three targets succeed. Interactive
menu comparison remains pending; no engine/pak changes.

UI ownerdraw no-op group aligned with original ui_ui_draw.c cases: 202,204,
210..219,236,239,243,256 (16 IDs). Removed inherited ET draw calls for player
model, clan logo, team slots, map selection captions, bot name and selected
player. Their input handlers/utilities are not removed; active team names,
map preview, MOTD and crosshair remain. Regression compares original empty
case group, original pak menudef IDs (read-only) and production dispatch.
All 16 checks pass; WASM ui rebuilt/export checked, all targets succeed.
This is source-reference parity evidence, not live menu/render replay.

UI clan cinematic ownerdraw aligned: original UI_OwnerDraw case 0xfb (251)
belongs to the no-op group in ui_ui_draw.c. Removed inherited ET playback
call and unused UI_DrawClanCinematic implementation; retained movie/map
preview dispatch and stop-handle support. Source regression compares original
no-op case and production routing. WASM ui rebuilt/export checked; all three
targets succeed. This is source-reference evidence, not live menu replay.

UI cinematic stop audit: original UI_StopCinematic (ui_ui_misc.c) uses direct
negative sentinel comparisons, and stops/resets map, network and clan handles.
Replaced abs(handle) with direct comparisons (avoids INT_MIN overflow), bounded
map index/count before mapList access and team count before name lookup. Valid
handle stop/reset behavior unchanged; invalid data guards are deliberate safety
differences from original. Source regression checks dispatch, bounds ordering
and all resets; WASM ui rebuilt/export checked, all three targets succeed.
No claim of live cinematic playback or original runtime parity testing.

UI find-player result ceiling aligned with original UI_BuildFindPlayerList
(ui_ui_misc.c LAB_0002a128): total rows < 0xf before insertion means 14
matches plus progress row, not 15 matches. Existing duplicate-address and
bounds protections retained. Updated broad search fixture expectation; new
standalone WASM fixture executes actual ui_nitmod_search.c for 0..40 servers
and verifies limit, status row, completion and cleared request slots (41 cases
passed). LAN/status responses are stubs, not live/original runtime replay.
All three WASM targets build; ui side-module framing/exports checked.

Brass dispatch follow-up: removed the local-client restriction for Nitmod
(original protocol or gamename nitmod), following original
CG_MachineGunEjectBrass at cgame_client.c:25457. Tag positions now populated
per entity are consumed for remote players too. Snapshot PERS_HWEAPON_USE gate
and MG42 exclusion retained; native AA exclusion intentionally retained as an
ET adapter difference. Non-Nitmod gamenames retain local-only dispatch.
Predicted event and hand render paths both use cg.predictedPlayerEntity.
WASM helper tests: 40 dispatch combinations and 16 tag combinations pass;
ownership source check passes; all three WASM build targets succeed. These
are fixture checks, not original runtime replay; live remote brass QA pending.

Brass tag producer follow-up: CG_AddPlayerWeapon now populates each rendered
entity's brass origin, including world/third-person weapons. First-person uses
tag_brass/tag_brass2 from ammo sequence; world view uses tag_weapon/tag_weapon2
from entity akimboFire (second tag when false). Reference cgame_ents.c
LAB_000dc221, LAB_000dba73, LAB_000dba7d, LAB_000da5f1; tmp_b3 is ps != NULL
on surviving render paths. Added 16-case executable WASM tag-helper fixture;
ownership source checks pass and all three WASM targets build successfully.
New-style brass dispatch still retains the existing local-player gate; do not
claim complete remote ejection parity. Live tag/render comparison pending.

Brass origin ownership: replaced global ejectBrassCasingOrigin with typed
centity nitmodBrassOrigin in existing tag producer and new-style brass consumer.
Original cgame_ents.c stores tag result in entity words 0x1d6..0x1d8;
CG_MachineGunEjectBrassNew reads entity +0x758..0x760. Source regression checks
both endpoints and removal of global. This does not yet change legacy routing
to new-style ejection or third-person tag selection; those need separate parity
work. Runtime renderer comparison remains pending. No engine/pak edits.

CG_FireWeapon underhand suppression now includes bomb, poison bomb and poison
mine alongside the existing eight weapons. Reference cgame_weapons.c original
branch after LAB_000de0ae: wire IDs 4,9,15,21,25,26,28,48..51 and positive pitch.
Typed helper preserves position after muzzle/recoil bookkeeping and before
firing sound/brass. Executable WASM helper fixture covers all 54 native weapon
IDs at five pitches (270 cases). All three WASM targets build successfully;
cgame side-module exports validated. Live effects comparison remains pending;
this fixture is not an original-binary replay. No pak or engine changes.

Weapon command/recoil audit: direct weapon command bank routing matches checked
original paths. Added executable WASM fixture linking actual cg_weapons.c recoil
function; 864 native weapon/seed cases verify pitch/yaw/roll, unchanged recoilPitch,
unsupported weapon no-op and exact rand consumption. Reference original
cgame_weapons.c CG_WeaponFireRecoil. No production discrepancy found here;
fixture is deterministic translated-behavior coverage, not original runtime replay.

CG_WeaponBank_f empty-bank sentinel now terminates Nitmod scan with WP_NONE,
matching original cgame_weapons.c bank loop at LAB_000d8eed/000d8aef (candidate
zero then first-entry zero). Other gamenames retain ET selection behavior.
Source routing test passes; cgame WASM rebuilt/export checked, all targets pass.
CG_LastWeaponUsed_f checked branches already agree; no extra mutation there.
Live empty-bank behavior remains pending; source regression is not replay parity.

Nitmod weapalt command now matches original CG_AltWeapon_f: prints obsolete
notice directing users to +attack2 and returns without ET local weapon swap.
Enabled for original protocol and reconstructed gamename=nitmod; other gamenames
retain ET route. Original hash/string and source routing test pass. cgame WASM
rebuilt/export validated; all build targets succeed. This does not change or
claim new verification of the separate +attack2 usercmd path. No pak/engine edits.

CG_OutOfAmmoChange dispatch/CG_FinishWeaponChange audited against original
cgame_client.c:25853 and 27861: KEEP/NEXT/select-only/finish dispatch, binocular
gate, equal-weapon early return, alternate switch sounds and scoped switchback
exclusions match checked paths. New source regression pins this wiring; not an
engine sound/zoom integration test. No production modification warranted by this
audit. Remaining original-server/local live transitions still need verification.

Ammo selection special-case audit: original pliers keep, detonator reserve keep,
four explosive->pliers branches, satchel select-only, mortar/MG42 unset select-only
match current code. Added 144 production-function WASM cases across original and
reconstructed Nitmod activation, force, availability and detonator reserve;
all pass alongside 72 grenade cases. Selection availability is stubbed; this
does not verify final engine-side transition effects. No production edit needed
for these audited branches. All build targets already up to date.

Forced poison-bomb ammo selection now shares smoke-bomb Luger-then-Colt
preference, matching original CG_OutOfAmmoChange wire50/28 branch in
cgame_client.c:28065. Bomb wire48 has no such special case and remains on bank
selection. Production decision-function WASM fixture passes 72 combinations of
protocol, grenade type, available pistols and force. Selection/engine services
are stubbed, so live behavior is still pending. All WASM targets build and cgame
exports validate; no pak/engine changes.

CG_NitmodAmmoSelection now activates for reconstructed gamename=nitmod as well
as original protocol. Existing normalized-ID decisions (mine->pliers,
satchel->detonator, bank scan) were previously unreachable on localhost.
Decision semantics unchanged; other gamenames retain native path. Source
activation checks pass and all WASM targets succeed (cgame rebuilt/export checked).
Live localhost selection still pending. Magazine-bar coordinates reviewed against
original cgame_ui.c:6084/6248; no unsubstantiated rendering change made.

Ammo HUD routes aligned with original cgame_ui.c:5970 switch: knife clip count
only with Light Weapons bit32; poison syringe clip-only; poison mine uses the
same team remaining-slot counter as landmine; bomb/poison bomb hide counts.
Native client skill adapter remains in NITMOD_ClientSkillUnlocked; original
protocol reads independent masks. Source routing regression passes, cgame WASM
rebuilt/export-checked and all targets succeed. Visual/live validation pending;
source assertions are not rendered parity tests. No pak/engine changes.

Knife magic-ammo refill now follows original BG_AddMagicAmmo: clip storage,
capacity one without Light Weapons reward32, configured maxammo with reward,
ownership granted on actual refill even if previously absent. Probe leaves clip
and ownership unchanged; reserve unchanged throughout. 2560 mask/count/clip
production WASM cases pass, including over-capacity and no-ownership cases.
Existing fixtures now fill the knife clip when isolating other weapons; all pass.
All three WASM builds/export checks pass. HUD and live original-server/local
throw/pickup verification remain open; no pak/engine changes.

Knife spawn now selects configured defaultStartingClip only with Light Weapons
reward32, otherwise one, reserve zero. Reference SetWolfSpawnWeapons_part_5
client+0xee0 bit32 and ammoTableMP+88. Shared static knife table corrected to
original maxammo8/maxclip8/startReserve0/startClip4; scripts may still override.
Source wiring and WASM table assertions pass with existing ammo fixtures; all
three module builds/exports pass. Knife pack refill/HUD and live spawn/pickup
tests remain open. This supersedes the prior audit's default/spawn findings.

Knife pickup and PM_NitmodThrowKnife now consistently use ammoclip, matching
original Pickup_Weapon client+0x294. Add_Ammo has an explicit knife clip path
with original Light Weapons bit32 capacity selection and ownership grant.
Spawn keeps its existing quantity one but moves it from reserve to clip; full
original starting/reward quantity semantics remain OPEN, as do magic refill,
HUD count display and legacy static table defaults. Source regression checks
pass and all WASM targets build; no live throw/pickup parity claim yet.

Knife layout audit found an unresolved reserve/clip mismatch across pickup,
throw and spawn; see reference/knife-ammunition-layout.md. Both hash-pinned
original module tables confirm maxammo/maxclip8, initial reserve0/clip4.
No production change or new build in this audit; prior claims of full thrown
knife pickup parity are not justified until the storage paths are reconciled.

Adrenaline refill now uses explicit options in shared BG_AddMagicAmmoOptions and
BG_CanItemBeGrabbedOptions, supplied by server g_adrenaline in both eligibility
and credit. Original weapon43 branch: option2 disables, option4 caps at one,
otherwise weapon maxammo plus First Aid reward bit4 bonus; owned weapon required.
Legacy wrappers retain disabled refill until callers supply synchronized options.
8192 production WASM option/mask/ownership/count cases pass with prior fixtures.
Client item prediction remains disabled, live pickup parity and remaining
knife/class-grenade behavior remain open. No pak/engine modifications.

Poison syringe magic-ammo refill ported: owned weapon only, clip += pack count,
clamped to weapon maxammo, no First Aid bonus and no reserve mutation. Zero-count
probe reports missing capacity without adding ammo. Reference: original
BG_AddMagicAmmo weapon47 branch, ammoTableMP+3384 (47*72). Production WASM test
adds 816 ownership/count/capacity cases including overfull clips and custom
limits; existing tests pass. All three modules build/export-check successfully.
Live pickup parity remains pending. Adrenaline refill still needs its options
contract; client prediction investigation is not concluded. No pak/engine edits.

Server Touch_Item eligibility now passes the same session reward masks as the
subsequent ammo credit, via BG_CanItemBeGrabbedRewards. Legacy callers retain
their wrapper. Production WASM tests add 384 probe/credit/full-capacity sequences
with independent heavy levels and masks; all pass. Corrected obsolete claim
that zero-clip probes never mutate state (helmet flag does change).
CG_TouchItem currently returns immediately, disabling item prediction; no
unverified enablement or dead-path client patch made. Live parity remains open.

Explicit ammo reward capacity now covers pistol/SMG/rifle/scoped, syringe and
adrenaline, rifle grenades and hand grenade branches in addition to heavy guns.
Original reference: BG_MaxAmmoForWeapon in sorted nitmod_bg.c:4945; native enums
used, independent masks bit2/4/32 preserved. Server Add_Ammo (except knife) and
BG_AddMagicAmmoRewards reloadable-weapon loop use the helper. No global mask
state or new engine imports. 28672 helper mask cases pass alongside prior WASM
fixtures; all three builds/export checks pass. This does NOT complete client
prediction, class grenade count, knife clip/reserve mapping or adrenaline refill.
Live and original-module replay parity remain open. No pak/engine edits.

Server AddMagicAmmo now supplies authoritative session reward masks through
BG_AddMagicAmmoRewards. Heavy capacities and syringe +2 use bits32/4, independent
of numeric level. Legacy BG_AddMagicAmmo remains a level-based wrapper for
unmigrated callers; grenade/other weapon rewards and client prediction are OPEN.
WASM production pickup fixture adds 1536 independent level/mask/probe cases for
flame and syringe, all passing alongside existing tests. No engine/pak changes.

Add_Ammo heavy capacity now overrides the legacy level result using authoritative
sess.nitmodSkillMasks[SK_HEAVY_WEAPONS] bit32. The isolated typed helper covers
flame/MG42/mortar carried and set variants; other weapons retain their route.
WASM fixture checks 1152 mask/table/weapon combinations plus prior 492 cases.
All build targets pass (qagame rebuilt). This closes only Add_Ammo's heavy mask
gap: BG_AddMagicAmmo, prediction and other capacity consumers still use level
adapters and require further integration. No full cross-module parity claim.

Heavy ammo capacity branches restored in shared BG_MaxAmmoForWeapon: flame +50,
mobile MG42 (carried/set) +maxclip, mortar (carried/set) +2. Panzer remains base.
Original nitmod_bg.c:4945 tests heavy reward bit32; current shared numeric API
adapts this via level>=5. Independent reward-mask equivalence remains OPEN.
Removed obsolete commented ET heavy bonus block. Production WASM tests cover
108 heavy custom-table/level combinations plus prior 384 cases; all pass.
All three WASM modules build/export-check successfully. Live pickup/reload and
custom script synchronization still need verification. No pak/engine changes.

BG_MaxAmmoForWeapon: scoped Garand/K43/FG42 now accepts the Light Weapons
bonus as well as Covert Ops; adrenaline shares the syringe First Aid bonus.
Hand grenade maxammo no longer gains the ET engineer +4: original cases 4/9
only add one for First Aid when engineer reward is absent. Class grenade counts
remain in their separate helper. Reference: sorted nitmod_bg.c:4945, original
cases 39/40/41, 43, 4/9. Existing numeric-level adapters remain; independent
reward-mask parity is NOT claimed. Production WASM fixture passes 216 maxammo
combinations plus 168 pickup/probe cases; all three module builds/exports pass.
Knife and adrenaline refill branches still require reward/config integration;
live verification remains open. No engine/pak changes.

Magic ammo now restores EF_HEADSHOT (helmet) before ammo checks and counts that
as success, matching original BG_AddMagicAmmo entry (playerState+0x68 bit0x1000).
This includes the zero-clip probe side effect observed in the reference; it is
not claimed to be a pure query. Shared production-code WASM fixture checks full
ammo + missing helmet, unchanged other flags/ammo, and subsequent rejection for
all 168 existing cases. All three WASM builds and export checks pass. Live helmet
render/pickup interaction remains pending; no pak or engine edits.

BG_AddMagicAmmo syringe capacity now uses the weapon table maxammo plus the
existing First Aid bonus instead of fixed 10/12. Original BG_AddMagicAmmo reads
ammoTableMP+792 (11*72, maxammo) and adds two for First Aid reward bit4.
The current numeric skill adapter is retained: independent reward-mask parity
and the remaining magic-ammo branches are still OPEN. WASM fixture executes
production bg_misc.c: 168 custom-limit/level/amount combinations, probe without
mutation and full-capacity rejection. All three WASM builds/export checks pass.
Live custom-script synchronization and pickup testing remain pending.

Huge Ammo Pack is now appended to the shared item table without shifting native
indices. Original qagame/cgame item 34 uses weapon_magicammo3, WP_AMMO, quantity
50 and the same model placeholders as Mega Ammo Pack (verified in both hashed
ELFs). Client wire item 34 now resolves to that distinct item. Manual and limbo
ammo selection gives Signals bit32 precedence over bit2; count/density still
uses bit2, as in Weapon_MagicAmmo_Ext. Pickup sound uses the existing native
file-path convention. All three WASM modules build and export checks pass;
original item reference test passes. Live pickup/render parity and charge tables
remain pending; this does not claim full ammo pickup parity.

Ammo pack normal/mega selection and count/density now read Signals reward bit 2
for manual throws and limbo drops, rather than inferring the reward from level.
Reference: original Weapon_MagicAmmo_Ext, client+0xedc, count = bit2 ? 2 : 1.
Original bit32 selects Huge Ammo Pack, but this item is absent from the current
shared item table: that selection remains OPEN pending item/protocol mapping.
Charge cost tables remain OPEN; their existing level-based route is unchanged.
All three WASM targets build successfully; live pickup/reward testing pending.

FirstAidUnlocks now reads the authoritative sess.nitmodSkillMasks instead of
synthesizing bits from numeric levels. G_SetPlayerSkill maintains this mask,
including session initialization. Consumers (adrenaline, poison cure, optional
regeneration) retain their bit tests. WASM abilities fixture tests all 64 masks
against six independent numeric levels plus existing adrenaline eligibility.
All WASM build targets pass; live session/skill-update behavior remains pending.

Mine snapshot Battle Sense grant now reads sess.nitmodSkillMasks bit 4 instead
of numeric skill >=4. Original callback reads client+0xed0 &0x10; g_stats already
maintains independent masks through progress.unlocked. Production callback
WASM test covers 2048 PVS/armed/spotted/team/level/mask combinations including
level-mask disagreement. All WASM targets pass. Spectator branch parity and live
skill-update/snapshot replay remain open; PVS still precedes every grant.

Mine snapshot callback now applies original outer trap_InPVS(viewer,mine)
before skill/unarmed/spotted/team grants. Indices/client pointer validated first.
Original sorted nitmod_weapons.c G_LandmineSnapshotCallback is the reference.
WASM production callback covers 32 visibility combinations plus invalid inputs.
Original skill-mask and spectator branch differences remain explicitly open;
no spectator visibility expansion made. All WASM targets pass, live PVS pending.

Post-pliers mine audit: prime uses common contact policy; poison trigger already
schedules gas explosion separately; registry cleanup includes both mine types.
Existing mine-contact fixture run under WASM (without q_math, since it supplies
its own VectorLengthSquared). No production changes in this audit. Snapshot
visibility and live arm/trigger/defuse sequence still require original comparison.

Poison-mine pliers integration fixed: producer uses MOD_POISON_GAS_MINE but
engineer branch accepted only MOD_LANDMINE. Both now enter the existing mine
arming/defusing path. All three ammo refunds retain the actual mine weapon,
saved before entity freeing. Source wiring regression and WASM build pass;
this is a typed integration fix, not original engineer disassembly parity.
Live poison-mine arm/defuse, charge refunds and owner-transfer parity remain open.

Native mine owner hints wired: qagame initializes landmine/poison-mine clientNum
to thrower; cgame native scan uses clientNum/teamNum, original scan retains
otherEntityNum/otherEntityNum2. Hint presentation accepts both layouts while
armed/team/trace gates remain unchanged. WASM scan test covers distinct owner
fields, enemy rejection and unarmed rejection; all WASM targets pass. Native
servers need the matching updated qagame. Rendering/snapshot visibility policy
was not changed; live mine hint and ownership-transfer checks remain pending.

Dynamite hint production draw now tested under WASM alongside scanning: both
layouts, owner text, full/half fuse bars, centered anchor restoration, armed
one-shot consumption, unarmed no-bar and one-second expiration. Trace/render
sinks remain stubs, so no live visual parity claim. Entity call site confirmed
unconditional for dynamite. No production modification in this verification.

Dynamite crosshair hints enabled for reconstructed Nitmod: qagame sets clientNum
to the thrower; cgame privately normalizes native time fuse to the hint's time2.
Original time2 remains untouched. Team/trace/distance gates retained. Production
scan WASM fixture verifies layout gates, owner retention and nonmutating fuse
normalization. cgame/qagame rebuilt/export-checked; UI current. Live rendered
bar and network spawn-to-hint replay remain pending. Older native servers lacking
owner metadata require updated qagame; no original-server wire change.

Production G_NITMOD_HealthTimer now exercised under WASM: 72 rate/health-limit
cases with multi-tick residuals, war/medic gates preserving residual time,
overhealth decay and the corrected DM sixth-reward route. Effective-max-health
and unlock readers are stubs. No additional production change in this audit;
all build targets current. Live regeneration replay remains pending.

Regeneration eligibility corrected: in Deathmatch without DMOptions bit 1,
g_medics bit 4 plus sixth First Aid reward still permits regeneration.
Original sorted ClientTimerActions LAB_0004e400 jumps to LAB_0004e399 (reward
check), not directly to decay. Typed pure predicate now preserves that route.
WASM tests cover 32768 eligibility combinations; actual health/rate/war gates
unchanged, full gameplay replay pending. Legacy orders/voiceOrders strings are
absent from the original UI binary, so they are not counted as Nitmod recovery.

Legacy UI orders/voiceOrders/voiceOrdersTeam now share a bounded team-selection
reader, rejecting negative/nonfinite/out-of-range cvar input before integer cast
or roster indexing. Count remains the broadcast sentinel; valid fractional input
retains truncation. WASM helper tests cover team counts 0..64 and invalid values.
This is safety work, not a newly recovered original action; legacy command-format
handling is unchanged and still requires separate audit.

Campaign setup/play actions moved from unchecked UI_RunMenuScript branches into
the typed menu-action dispatcher. Preserves existing progress-to-cvar and quoted
spmap commands; validates campaign/map bounds, progress, pointers and map tokens
before access. Production-action WASM test covers setup, unlocked/locked maps,
invalid selection and missing map record; all WASM build targets pass.
This is migration/hardening of existing actions, not newly recovered functionality
or an original-binary runtime parity claim. Interactive campaign launch pending.

UI campaign visibility verified under WASM using the production helper:
392 selected-map/progress combinations, six existence flags and invalid
catalog/NaN inputs pass. Cvar input is a stub, not an interactive menu replay.
No production change or newly ported feature in this audit; all targets current.

Poison scheduler now has direct production-function WASM coverage: 48 combinations
of default/custom interval and damage, stacks and attacker identity. Verifies
strict nextTick < time boundary, one tick per call, rescheduling and spectator
cleanup. Overrides and G_Damage use sinks; this is not full gameplay replay.
All WASM build targets current. No production code change in this verification.

Poison tick interval now consumes cached poison.weap spread when nonzero.
Original ClientThink reads BG_Weapons+81960: 47*0x6b0+0x5d8; original parser
stores spread at +0x5d8. Zero retains g_poison-selected 50/1500 ms defaults.
Typed integer getter avoids float spread conversion. WASM getter test checks
overrides, zero and unavailable records; scheduler/browser replay still pending.
No protocol change or pak edits.

Poison attack now checks ps.powerups[PW_INVULNERABLE], the field populated by
NITMOD_SetSpawnProtection, instead of the unused client invulnerabilityTime.
Original Weapon_Poison compares client+0x154 expiry >= level time. Standalone
WASM attack tests cover expiry before/at/after current time, independence from
the legacy field, miss, invalid target, dead target and absent client without
sound/stack side effects. Existing muzzle/team/timing tests and all WASM build
targets pass. Live spawn/revive protection replay remains pending.

Poison muzzle posture branch completed: original Weapon_Poison tests eFlags
0x10 (EF_CROUCHING), not EF_PRONE. Living crouched attacker with pitch >30
uses height 30; other living attackers use viewheight; health <=0 uses 25.
ELF branches 0xf3590..0xf35c8, 0xf3770 and 0xf3820 agree with sorted reference.
Production attack WASM fixture adds 29.99/30/30.01 across standing/crouched/prone,
and health -1/0, checking trace origin and length. Existing lean/team/timer
tests and all WASM build targets pass. Supersedes unresolved posture note below;
live hitbox comparison remains open, and no movement-delay cvar was touched.

Poison syringe muzzle no longer uses the rounded ET activation origin.
Original Weapon_Poison retains trBase fractions and applies lateral lean plus
vertical -abs(lean/3.5); typed attack now does the same. WASM production attack
fixture checks left/zero/right lean, fractional origin and 64-unit trace.
Special original posture flag/height branch remains unresolved; this is partial
muzzle parity, not complete Weapon_Poison parity. Existing team/timer tests and
all WASM build targets pass. Live trace comparison remains pending.

Poison syringe team restriction corrected from any nonzero friendly-fire value
and LMS exemption to bit 0 and Deathmatch exemption. Direct original ELF
Weapon_Poison disassembly: 0xf36b4 testb $1; 0xf3736 compares gametype to 8;
otherwise OnSameTeam rejects. Production WASM attack test passes 112 combinations
of gameplay modes 2..8, friendly-fire masks 0..7 and team relationship, checking
sound and poison-state side effects. Existing timer/attribution tests pass;
all WASM targets build. This affects reconstructed qagame only, no wire change.

Poison syringe repeated-hit timing aligned with original Weapon_Poison
(sorted nitmod_weapons.c: first infection initializes client+0x53a0;
already-poisoned branch changes attacker+0x5300 and stack count+0x5304 only).
Reconstructed attack no longer overwrites nitmodPoisonNextTick on repeat hits.
Production WASM attack test covers first infection, attribution transfer,
unchanged scheduled tick, cure and reinfection; trace/sound are stubs.
All WASM build targets pass. Camera-bit audit also confirms original medic
regeneration tests 0x200001; that poison exclusion was deliberately retained.
No client/UI wire change; live damage-timing comparison remains pending.

qagame camera-freeze integration corrected: ClientThink now requires the
cameraPortal as well as EF_VIEWING_CAMERA before discarding input/freezing.
The shared bit alone is also NITMOD_EF_POISONED, set by the reconstructed poison
producer. Cmd_StartCamera creates the portal before setting the flag; StopCamera
clears it. Standalone production-helper WASM test covers all flag/portal pairs
and null client. This is a typed integration correction, not a disassembly
parity claim for ClientThink. Live poison/movement/camera regression is pending;
other legacy camera-bit consumers and poison visual gates still need audit.

UI player-action WASM runtime coverage now executes all 21 recovered vote,
referee, RCON and ignore commands: 210 cases for selected-player identity,
quoted colored names, invalid roster indices/counts, unsafe names and missing
termination. Existing binary-reference test verifies original action strings.
No production behavior changed in this audit; this adds executable evidence
for existing port code, not 21 newly ported features. All build targets current.
Server execution and live menu interaction are not exercised by these sinks.

UI map/campaign vote, referee and rcon actions now check fixed array capacity
as well as reported counts, and reject unsafe unquoted metadata tokens. Valid
command formatting is unchanged; this is hardening of the recovered actions,
not a newly recovered gameplay feature. Production-action WASM test covers
five valid map/campaign commands, malformed identifiers and oversized/negative
selections. Original UI action reference test and all WASM build targets pass.
Console/cvar sinks are stubs; live menu-to-server execution remains unverified.

Crosshair health now consumes the existing negotiated CLASS_HEALTH/nch path
on reconstructed servers, instead of always using ET defaults. Original
configstring 39 is read only on the original layout; native class overrides
come from nch. Nonpositive helper results preserve the existing calculation.
Standalone WASM helper test covers all five classes, capability combinations,
overrides, medic/skill bonuses and invalid inputs with protocol stubs. Test
snapshot is static to avoid exceeding the standalone default WASM stack.
All three WASM build targets pass; browser health-bar comparison remains open.

Crosshair player name/class/rank presentation now also accepts the reconstructed
Nitmod server layout for ordinary identified players. Native health calculation
and original-only disguise decoding remain separate; ET presentation is retained
for native disguises. Extended production-helper WASM test checks both Nitmod
gates, player text/icon coordinates, invalid clients and native disguise rejection.
This verifies rendering calls with stubs, not visual parity in the browser.

Crosshair entity labels and tank health bars now use Nitmod presentation for
both server layouts, rather than falling back to ET rendering on localhost.
Three entity-label call sites use gamename predicate; entity-type selection
still uses original/native layout distinction. Draw helpers accept both Nitmod
layouts. Standalone production-helper WASM test verifies label coordinates,
health clamping, centered-anchor scope/restoration and invalid inputs using
renderer/predicate sinks. cgame rebuild/export check passes; no ui/qagame change.
Actual wide-screen rendering and entity/name synchronization need live checks.

Score receiver runtime verification added: production static CG_ParseScore
executed under WASM for both framing layouts, negotiated/unnegotiated KD and
same/reassigned clients. Confirms retention/clear, original flags, native team
totals, sc1 append and atomic rejection of malformed tail, invalid client and
short packet. Supersedes previous source-only retention verification. Protocol
predicates/arguments are stubs, not live negotiation. No production change in
this audit; sender and KD-parser tests remain separate from browser E2E.

KD receiver isolated as NITMOD_KDCommand, retaining original positional mapping
(transmitted client token ignored), transactional parsing and append cursor.
Direct production-parser WASM test passes reordered client mapping, malformed
append then retry, overflow append/count and unknown commands. Score refresh
now retains same-player KD for negotiated reconstructed servers as for original
servers; reassigned rows still clear. Preservation gate source-checked only,
not runtime-tested here. cgame rebuild/export check passes; ui/qagame unchanged.
No live server/browser end-to-end parity claim.

Full-update ordering aligned: score pages -> team scores -> KD pages -> team
info, matching original fu dispatch ordering. Supersedes the ordering caveat
below, but reconstructed packet framing remains intentionally distinct.
Production WASM sender test now checks this order, reverse sorted clients,
POW filtering and INT_MAX/INT_MIN KD values spanning two KD packets (54 rows).
Existing 0..64-player and capacity cases still pass. qagame rebuild/export
check passes; ui/cgame unchanged. Receiver/browser end-to-end replay pending.

Immediate fu refresh implemented in qagame ClientCommand, following original
nitmod_client.c fu branch: score refresh plus both team-info senders. Existing
G_SendScore supplies negotiated KD and team scores. cgame score-key request
uses fu only with SCORE_KD capability; legacy/original non-negotiating servers
retain score request. Demo/multiview guards remain. WASM production handler
fixture passes 40 score/KD rows plus ordered Axis/Allies updates; source wiring
check passes. All three modules rebuild/export-check successfully with existing
warnings. Reconstructed wire framing and team-score/KD ordering remain distinct
from original; no claim of original-client support on reconstructed server or
browser end-to-end parity. Teaminfo still suppresses unchanged cached data.

Reconstructed qagame now sends kd0/kd1 after score pages, gated by new
NITMOD_FEATURE_SCORE_KD bit 14 advertised by both sides. Existing cgame
receiver consumes these triples in score order. Sender records exactly the
rows accepted into sc0/sc1, preventing drift from POW filtering or packet
capacity. Typed sess.kills/deaths feed triples; original G_SendKD_Add uses
client/kills/deaths order. Byte-bounded KD packets retain current protocol
score framing, not original packet boundaries. WASM sender fixture checks
40 matching KD rows and unsupported clients receive no KD. All three WASM
modules rebuild/export-check successfully; existing format warnings remain.
Original fu command and end-to-end browser KD validation remain open.

G_SendScore packet continuation fixed: unappended row retries same index;
appended row at count limit advances to next index. Previous i-- duplicated
rows and omitted tail players. Original sorted G_SendScore uses first-unsent
index; retained this layout's 32-row limit and sc0 team-score header (original
uses different framing). Production WASM test covers 0..64 clients plus a
40-client byte-capacity split with exact-once delivery. qagame rebuild/export
check passes. Two-packet capacity remains finite; this does not port original
score flags/KD or the missing fu command and does not claim browser parity.

TeamplayInfoMessage aligned with original sorted nitmod_unknown.c: refresh
coordinates directly in sender, include POW-marked team members, skip bot
recipients while keeping them in the roster. Preserve reconstructed five-field
wire format and matching cgame decoder; original six-field XYZ remains separate.
Entry capacity now reserves NUL. Production-function WASM fixture passes exact
packet, fractional XY truncation, health clamp/limbo, POW inclusion, bot recipient
exclusion and unchanged-message suppression. qagame relink/export check passes;
cgame/ui unchanged. Full original XYZ transport and browser checks not claimed.

Wounded/medic name queue and draw gates now accept both Nitmod layouts via
gamename, not just original configstring numbering. Consumers already use
typed team/class/health data; no wire decoder changed. Null entity rejected
before dereference as hardening. 600 standalone production-queue WASM cases
cover medic/dead-player roles, teams, range endpoints and mod eligibility;
predicate is stubbed there. Full-source fixture expanded to et260 layout but
not executed this pass. cgame relink/export checks pass. Live visibility,
health synchronization and rendering on localhost remain to be verified.

Missile-camera selection now accepts reconstructed Nitmod servers as well as
original-layout servers: use gamename predicate, not original-CS-layout predicate.
Tracking consumes native weapon enums and entity clientNum; qagame already sends
simple.missileCams from g_missileCams. Original weapon-mask/owner logic retained.
Production tracking TU WASM test passes 192 mod/mask/weapon/owner combinations
and null/no-snapshot/non-missile checks. Three Python wiring checks run directly
(pytest unavailable). cgame relink/export check passes; ui/qagame build-current.
This closes a client protocol gate, not full localhost camera rendering parity;
renderer restoration and real qagame projectile ownership still need live checks.

cgame hit samples now register in CG_RegisterSounds, matching original
cgs+131996..132008: head.wav, nit/hs.wav, body.wav, team.wav. Snapshot and
explicit event consumers retain separate samples; neither loads assets during
playback. Removed duplicate event-time cg_hitSounds registration (main cvar
table already owns it). Invalid explicit-event handles are suppressed as safety
hardening. Production-function WASM test passes four-path registration order,
repeated head/team events, cvar, invalid client/type and failed-load checks.
Full event/snapshot fixtures adjusted for eager loading but not executed here.
cgame build/export check passes; ui/qagame unchanged. Live audio still pending.

cgame PM sound registration moved from event handling to CG_RegisterSounds,
matching original eager asset loading (sorted cgame_client.c CG_RegisterSounds,
cgs+69656). Events only use the registered handle and retain local-recipient,
live cg_pmSounds, channel 3 and volume 255 behavior. Invalid sound handles are
suppressed as hardening. Standalone production-function WASM test covers loading,
repeated events, disabled cvar, other recipient and missing asset. Full-source
event fixture updated but not executed here. cgame rebuild/export check passes;
ui/qagame build-current. Browser audio verification remains open.

UI system staging audited against UI_RunMenuScript ELF branches 0x25926
(get), 0x2607d (reset), 0x26223 (apply). Original 0x26741..0x26759
confirms zero-rate substitution 5000/30/1; apply clears staged fields afterward.
Existing production implementation retained. New standalone WASM test executes
126 get/apply/reset combinations over 21 settings, zero/nonzero rate and NaN
in each numeric field. NaN atomic rejection is port hardening, not original
parity. Engine cvar IO is stubbed; this is not browser menu verification.

GlobalAccum error-path parity: missing index/command, range and unknown-command
diagnostics now identify globalaccum, and operand validation precedes dispatch
as in original sorted G_ScriptAction_GlobalAccum (Ghidra 0xc2450). Local/global
range diagnostics both report 9, not 10. Nine production-function WASM error
cases capture G_Error with setjmp, including unknown commands with/without
operands; existing command/trigger tests also pass. Negative-index rejection
remains deliberate safety hardening. qagame rebuilt/export-checked; cgame/ui
build-current. No new UI or cgame behavior was changed in this step.

Clamp helpers corrected in cgame and qagame through shared nitmod_clamp.h.
Original cgame ELF 0xdb4a0 and qagame 0x103280 explicitly set x87 RC=0x0c00
before FISTP: truncate toward zero, not the former half-away rounding.
Both bounds are evaluated sequentially, including reversed bounds; float
helper follows the same order (cgame ELF 0xdb460). Double comparisons retain
the original exact integer comparison precision. Out-of-range conversion
returns INT_MIN, matching masked x87 integer-indefinite rather than invoking
undefined WASM conversion. Null-pointer tolerance remains deliberate hardening.
Standalone production-helper WASM cases pass; cgame/qagame relink and export
checks pass, ui remains build-current. No browser replay or UI feature claimed.

Accumulator command regression coverage expanded: production local/global actions
now execute 38 set/inc/random/bit/comparison/wait cases at slot 9, plus four
trigger fanout/caller-change cases under WASM. Both use the target-name hash,
unlike the separately verified original cvar trigger's event-name hash.
Reference: sorted nitmod_script.c G_ScriptAction_GlobalAccum trigger branch;
no new gameplay implementation change was needed for these tested paths.
Engine event/lookup operations remain test sinks, not original runtime parity.

Global accumulator capacity fixed: level.globalAccumBuffer used eight slots
while GlobalAccum accepted ten. Storage now uses G_MAX_SCRIPT_ACCUM_BUFFERS
(10), matching original 0..9. Local/global print guards also accept ten;
separate bot accumulator capacity is unchanged. Negative local/global action
indices now rejected as safety hardening. Production WASM test verifies slot
9 writes in both stores and both print commands accepting index 9. Print-error
diagnostics now report the correct upper bound 9. Engine output is a test sink;
this is not a browser replay or complete script-system parity claim.

Production G_FreeEntity now exercised by standalone WASM test: deletion
notifications/callback precede clearing; flag and dynamite objective clear
while spawnCount/freetime survive; neverFree retains state after callback and
unlink. Engine/bot notifications are test sinks. Passes with two pre-existing
g_utils array-address warnings. No production change needed. This covers
freeing, not full engineer defuse/explosion timing or original engine replay.

Dynamite count consumer ported: scan non-client entity slots for etpro_misc_1
bit 1 and matching nitmodDynamiteObjective. Replaces proximity-based bot count.
Original post-store numeric-targetname comparison confirmed at ELF
0xb1ec2..0xb1f1f and retained, including abort-on-unequal. Production-function
WASM test covers two charges, wrong target, absent flag, client exclusion and
both continuation outcomes. WASM build/export checks pass. Live planting,
defuse/explosion/reuse parity still pending; no end-to-end parity claim.

Dynamite association state introduced as server-only nitmodDynamiteObjective.
Primary objective planting records hit->s.number after etpro_misc_1 bit 1,
matching inspected original planting sequence. Constructible path leaves it
unchanged as original; G_InitGentity resets it and G_FreeEntity's existing
whole-entity memset clears it. Association consumer/counting and original
post-count comparison remain pending. Source lifecycle wiring test added;
not a gameplay parity claim. No network/shared entity-prefix change.

Dynamite-count investigation: flag maps to etpro_misc_1 bit 1, but original
also stores an objective entity number absent from the current planting path.
Current spatial BotGetTargetDynamite counting is not equivalent. Recovery
findings and required lifecycle/test work recorded in
reference/dynamite-count-recovery.md. No production change or completed
dynamite-count parity claimed for this investigation.

Local accum set_to_dynamitecount target lookup now matches original ELF
0xb1e34/0xb1e48: BG_StringHashValue followed by G_FindByTargetnameFast.
Counting still uses the existing BotGetTargetDynamite and is NOT claimed
original-parity: original scans an entity flag and target association directly,
and its apparent subsequent compare needs further verification. No change to
those unverified semantics. Existing production-script WASM regression passes;
the dynamite branch remains an aborting test sink, not covered by that test.

Resolved local accum index ambiguity by disassembly: ELF 0xb1f3f computes
entity + index*4, then 0xb1f47/0xb1f65 read/write at +0x3d4. Ghidra's apparent
slot-zero inc was misleading; existing selected-buffer behavior is correct.
Local inc now uses unsigned 32-bit addition before signed storage. Extended
production-function WASM test checks both overflow directions at buffer 3
and preservation of buffers 0/2. Unexercised dynamite lookup sinks abort.

Global accum inc now performs unsigned 32-bit addition before signed storage,
matching original G_ScriptAction_GlobalAccum arithmetic without signed-add UB.
Production-function WASM tests cover INT_MAX + 1, INT_MIN - 1, neighboring
buffer preservation and wait_while_equal. Test and qagame build/export checks
pass. Local accum arithmetic is unchanged: its decompiled inc branch appears
to use slot zero, requiring direct disassembly before deciding index parity.

Executable WASM coverage added for production G_ScriptAction_Cvar and parser:
set/inc/random/bitset/bitreset writeback, bit comparisons, wait, unmatched and
matched triggers, ordered two-recipient fanout and deferred caller termination.
Engine cvars/hash lookup/event delivery are test sinks, not an engine replay.
Inc now uses unsigned addition before signed output to match original 32-bit
wrap without signed-add UB; INT_MAX -> INT_MIN test passes. Source checks and
WASM qagame build pass. No cgame/ui or pak mutation in this step.

Cvar trigger_if_equal now uses original hash lookup. Important original quirk:
the SECOND parsed token is hashed, not the first target-name token. Verified
in ELF: second COM_ParseExt result saved in EDI at 0xb5988, supplied to
BG_StringHashValue at 0xb59a7/0xb59ac and lookup at 0xb59e0. Port hashes `name`
and keeps ordered fanout/deferred caller termination. Accum paths unchanged.
Reference-byte/source wiring checks added; full script runtime comparison
remains pending. This behavior intentionally preserves the original quirk.

Script cvar writeback restored for set/random/bitset/bitreset. Previously these
only modified a local value. Original G_ScriptAction_Cvar writes `%i` through
trap_Cvar_Set after modifying cases; comparisons do not write. Inc remains
plus one (original case 0x9a), not the supplied operand. All four cvar bit
operations now use the same low-five-bit mask as accum. Source wiring test
covers five write paths; mask WASM tests and qagame build pass. Full engine
cvar-store/script execution remains to be tested.

Script accum bit operations: local/global bitset, bitreset, abort_if_bitset
and abort_if_not_bitset now share an unsigned 32-bit mask using low five
index bits, matching original nitmod_script.c shift semantics. Avoids signed
shift UB at bit 31 and out-of-width inputs without changing buffer layouts.
Standalone WASM test executes 257 shift cases plus integer endpoints; passes.
qagame WASM build/export validation passes. Full script execution tests were
not run this turn; cvar script bit operations remain separately unaudited.

UI_Update behavior audit against original ui_ui_misc.c / ELF 0x20cf0:
existing settings implementation matches the inspected rate thresholds,
color-depth/stencil branches, LOD, preset and name actions. Added standalone
Emscripten/Node execution of production UI_Update with cvar/command sinks
stubbed. Boundary rates 3999/4000/4999/5000/25000, 16/32-bit depth behavior,
LOD 2, valid/invalid presets and name copy pass. No production change in
this audit; this is not full menu/browser parity or full UI_Update coverage.

UI registration audit: read original ELF cvarTable at 0x57d40, size 0x1068,
20-byte entries. No additional missing UI cvar names found in the UI sources.
Added executable Python reference comparison for all 18 vote_allow registration
rows, checking names, defaults and CVAR_ARCHIVE (including the original duplicate
kick row). This is registration coverage, not proof of each cvar's behavior.
No production change needed in this audit; no additional UI feature claimed.

Location debug localhost follow-up: CG_NitmodAddLocationMarkers and
CG_NitmodQueueLocationName now use the gamename-based Nitmod predicate,
consistent with the already shared draw pass and asset loading. No entity
wire fields are used for these file-based points. Executable WASM tests cover
marker/label dispatch, far/behind/PVS rejection and disabled/no-snapshot
conditions with renderer/label sinks stubbed. Test snapshot storage is static
to fit the standalone 64 KiB stack. Test exits successfully; cgame WASM build
and exports pass. Actual label projection/rendering still needs browser QA.

Localhost location integration: loading location files and resolving display
names now use the Nitmod gamename predicate (NITMOD_UsesNitmodHud), not the
original configstring-layout predicate. Reconstructed et260-layout Nitmod
servers therefore use the same location assets and naming policy. No wire
indices changed. Standalone WASM test executes named/grid formatting with
Nitmod enabled and disabled; file-loading behavior still needs a browser
test. WASM cgame build/export verification passed. Debug location markers
retain their existing original-layout gates and are not claimed completed.

Location follow-up: standalone Emscripten/Node test now executes production
location parser/lookup and q_shared/q_math code, with engine services stubbed.
Covers repeated/multiword names, zero origins, invalid coordinates and short
names. Name-plus-grid formatting corrected to `%s ^3(%s)`, verified at original
cgame ELF 0x10d97b; test also covers formatted and grid-only output. WASM
module build/export checks pass; this does not replace browser visual testing.

Location parser parity: CG_LoadLocations consumes the remaining line as the
name, strips quotes and repeats the preceding name for @ (literal verified
at original cgame ELF 0x106fd7). Port now accepts unquoted multiword names
and repeats names even after a skipped zero origin. Coordinate parsing cannot
cross a line. Existing finite-number checks and 64-byte name limits remain
intentional hardening. CG_GetLocationMsg also treats one-character names as
Unknown, now matched. Added full-source test fixtures for multiword/repeated
names; that test executable was not run this turn. WASM cgame build and export
validation passed; live map-location verification remains pending.

Voice location presentation: CG_VoiceChatLocal now uses existing
CG_NitmodLocationText with enable bit 2 (named location, Unknown policy bit 8,
grid suffix bit 16) instead of unconditional grid coordinates. Original
cgame_ents.c CG_VoiceChatLocal establishes the bit policy. Team format
`(%s^7)^3(%s)^7:^%c%s` verified directly at original ELF address 0x10d985;
fireteam format restores the original ^7 reset after the player name.
Source wiring regression added; live location/voice rendering remains pending.

Client voice command parity: removed inherited ET260 spectator rejection
from CG_VoiceChat_f, CG_TeamVoiceChat_f and CG_BuddyVoiceChat_f. Original
cgame_client.c implementations only require argc == 2, copy argument 1
with a 64-byte limit and forward the respective vsay command. Those limits
remain unchanged; server mute/team/fireteam/ignore filtering is untouched.
Source regression checks cover all three command bodies. Browser spectator
voice playback against original and reconstructed servers remains pending.

Custom voice text ported server-side from original ClientCommand/G_Voice:
vsay and vsay_team read a 32-byte voice id at argument 1 and text from 2;
vsay_buddy reads id at recipient-count + 3 and text from +4. Text longer
than one byte goes through G_Say with the same chat mode and sets voiceonly
to suppress the script subtitle. Plain voice and bot call interfaces remain
unchanged via a wrapper. Invalid buddy counts above MAX_CLIENTS are rejected
as deliberate bounds hardening. Existing cgame understands chat plus voiceonly;
no new message type or asset change. Source tests cover parsing/wiring, not
live playback; browser tests of custom voice text remain pending.

Voice recipient ignore filtering restored in qagame G_Voice (original ELF
0x58860): global/team and both fireteam recipient modes check the recipient's
ignore bitset against the sender before delivery. Existing class/fireteam
membership filtering stays intact. Explicit targeted delivery remains outside
this filter, matching the original function. Uses typed sess.ignoreClients;
no structure or wire-format change. Source wiring tests cover both broadcast
branches and the targeted exception; runtime ignore/unignore test is pending.

Completed the qagame voice-variant send path: original G_Voice (reference
`qagame/sorted/nitmod_game.c`) generates one `(rand() & 0x7fff) / 32767.0f` selection;
G_VoiceTo appends it with `%f` after the global id or
team/buddy coordinates. Targeted and both broadcast paths now share that
value. The client consumes this optional field independently of configstring
layout, including reconstructed localhost servers. Legacy messages without
the field still work. Source wiring checks and WASM build validation cover
this change; original-server/localhost playback comparison remains pending.

Original-server voice variant selector ported through CG_VoiceChat,
CG_VoiceChatLocal and CG_GetVoiceChat. Global argument 5 / team-buddy argument
8 now selects the same sound/sprite/text tuple as the server specifies.
Original CG_GetVoiceChat disassembly uses truncation (x87 control word 0xc00).
Empty variant lists, nonfinite/out-of-range selectors are rejected; rounded
endpoint 1 is clamped to the last variant as hardening. Messages without the
field retain local random selection. Reconstructed qagame emission was
completed in the follow-up above; no runtime parity claim. WASM cgame
build/export and source wiring test pass; browser voice transcripts pending.

Client chat audit: normal chat/tchat formatting, team storage and 70-column
wrapping match inspected original paths. Added byte-capacity wrapping to
CG_AddToTeamChat because color escapes do not increment visible width and
could overflow its 211-byte row. Reserve space for an escape and terminator;
ordinary width wrapping remains unchanged. This is deliberate hardening,
not original overflow parity. WASM cgame build/export check and source guard
test pass; color-heavy browser rendering remains untested. No pak changes.

Chat location/weapon fields aligned with original G_Shortcuts (ELF 0x56520):
location uses ps.origin, and location/weapon labels each retain at most 31
bytes before expansion. Source regressions updated. Three chat/voice varargs
call sites now explicitly pass integer client IDs to integer formats rather
than ptrdiff_t; wire spelling is unchanged. WASM qagame build/export check
passes without the previous g_cmds format warnings. Runtime transcripts
remain pending; no pak/engine edits or new cgame/ui feature claimed.

Original chat name sanitation ported: G_ShortcutSanitize's literal table at
ELF 0x2357e0 converts [a/d/h/k/l/n/r/p/s/w] to parentheses before G_Shortcuts
copies names into 36-byte fields. Typed name substitution now performs that
sequence for self and referenced players; [t]/unknown codes are untouched.
Expansion remains bounded/nonrecursive. WASM qagame build/export and source
regressions pass; runtime name/transcript parity remains unverified.

Chat shortcut weapon parity: original G_Shortcuts computes [t] as clip plus
reserve, but excludes only reserve for the knife. Removed reconstruction's
unconditional knife zero. Added weapon-ID guard before [w] item lookup as
hardening. WASM qagame build/export and chat shortcut source tests pass;
existing format warnings remain. Runtime chat transcript comparison pending.
No cgame/ui wire changes, pak or engine edits.

Pickup supplier/chat attribution: original Pickup_Weapon/Health save supplier
before IsClass/team reward gates. Moved health supplier recording before its
Medic gate and removed team/self filters for last-ammo supplier. These typed
fields feed g_cmds chat substitutions, not reward eligibility. Parent-client
validation remains; absent parents leave the previous supplier unchanged.
WASM qagame rebuild/export and pickup/reward source checks pass. Live chat
substitution after self/enemy/same-class packs remains untested. No wire,
pak, or engine changes.

Pack reward cadence corrected for both ammo and health: original client
field +0xff8 increments inside the g_misc bit 8/4 reward gates, before skill
points. Moved typed PCSpecialPickedUpCount into these gates. Disabled rewards
no longer advance the subsequent score cadence; supplies/healing remain
outside. Earlier claims that this counter intentionally advances while
rewards are disabled were incorrect. Distinct original statistics counters
outside the gates are not conflated with this cadence field. WASM qagame
build/export check passes; reward source tests now inspect brace-delimited
blocks instead of their previous tautological offset assertion.

Reachable Pickup_Weapon parity: original already-owned branch excludes wire
23/24 (Carbine/Garand) from clip-quantity Add_Ammo; added typed exclusions,
retaining separate reserve/alternate ammo grants. WP_AMMO now returns after
the magic-ammo branch for Field Ops as well, matching the original early
return instead of falling through to primary weapon acquisition. WASM
qagame build/export and pickup source regressions pass. Gameplay pickup
transcripts remain pending; no pak or engine changes.

Pickup audit: G_CanPickupWeapon class/war allowlists match the typed
G_NITMOD_PickupPolicy for mapped weapon IDs. Pickup_Ammo remains ET base code,
but neither this tree nor the sorted original has a direct caller (definition
only). Touch_Item dispatch currently handles WEAPON/HEALTH/TEAM, not AMMO.
Do not wire this function in merely because its original implementation
exists. Before porting it, establish an original reachable call path, map
the +0xfe8 client cooldown field, and verify quantity/partial-respawn semantics.
No production code or WASM artifact changed in this audit; this is not a
completed ammo feature. Existing reported dropped-pack checks remain open.

Binding layout audit correction: original Controls_GetConfig/SetConfig use
active fields at +24/+28 (two keys, not three). Controls_SetDefaults right
branch reads +8/+12 and left branch +16/+20. Consequently the previous raw
table interpretation of words +4 onward as four defaults is NOT sufficient
evidence of runtime default parity. The +attack2 MOUSE2 observation below is
only a raw table observation, not validated default-reset behavior. Preserve
current defaults pending analysis of the extra word and initialization path.
Added instruction-level regression evidence; no production/binary changes
in this audit. Original exclusion of mvactivate from the table still stands.

Controls default parity: decoded all 61 records of original UI g_bindings
(ELF 0x593e0, size 0x7a0, stride 32). Original has no mvactivate record;
removed inherited ET260 M defaults from the retained compatibility action.
Manual binding remains possible. Original +attack2 defaults are MOUSE2 on
both layouts. Binary-backed binding test and WASM ui/cgame build/export
checks pass. Controls-reset runtime testing remains pending; pak unchanged.

Remaining UI configstring call-site audit: UI_BuildPlayerList uses base 689
for both the local player and roster iteration, confirmed by original ELF
instructions at 0x15d06 and 0x15dcb. This matches this tree's CS_PLAYERS;
no roster remapping is needed. Remaining reads are CS_SERVERINFO (0), except
the previously corrected voteInitToggles. Regression checks pin both original
player-base instructions and local call sites. This audit does not add a
feature or certify player-menu runtime parity; no production code changed.

UI voteInitToggles layout parity: original UI_RunMenuScript ELF 0x2362b
reads configstring 29, while the ET260 base defines CS_SERVERTOGGLES as 32.
UI now follows cgame's gamename/nitmod_csLayout detection to select 29 for
original Nitmod and 32 for reconstructed et260-layout servers. This corrects
the warmup-damage menu initialization without changing server protocol.
Original instruction bytes and source wiring are regression-checked. WASM
ui rebuild/export check passes; original-server/local menu runtime comparison
remains pending. pak and engine are unchanged.

UI stability review: clientCheckVote now bounds-checks cg_ui_voteFlags before
float-to-int conversion, consistently with other typed menu actions. Double
comparison avoids rounding INT_MAX upward; NaN, infinities and out-of-range
values preserve existing menu state. Valid flag handling is unchanged.
This is defensive hardening, not an original feature/parity completion claim.
WASM ui build/export check and original UI action source checks pass; malformed
cvar runtime scenarios remain untested. No pak/engine changes.

Intermission polling aligned with original CG_Debriefing_InfoRequests/Draw:
list requests and visible-page tally requests now have separate entry points.
Tally polling no longer waits for list receipt, uses the original >1000 ms
threshold, and remains after the UI-catcher early return on mapvote page 0.
Clock rollback recovery is retained as hardening. WASM cgame rebuild/export
check passes; source-contract checks cover the independent polling. Delayed
list response and page-switch browser scenarios remain untested. qagame/ui
wire formats and pak remain unchanged.

Mapvote command dispatch: G_IntermissionMapVote accepts exactly two arguments
for single voting and three for weighted voting, independently of the menu
flag. Reconstructed qagame now matches that dispatch instead of requiring or
ignoring the slot based on g_mapVoteFlags. Extra arguments are rejected and
cross-slot duplicate checks apply to the weighted form, as in the reference.
Strict numeric/map bounds checks remain deliberate hardening. Existing cgame
single and multi commands already use these forms. WASM qagame rebuild/export
check and mapvote source-contract tests pass; runtime command transcripts
against the original are still pending. No separate ui change in this step.

Original-server multi-mapvote compatibility fixed: G_IntermissionMapList
sends g_mapVoteFlags & 4 (0 or 4); CG_parseMapVoteListInfo interprets any
nonzero mode as multi-vote. Reconstruction cgame incorrectly rejected modes
above 1, discarding original-server multi-vote lists. Removed that limit
while retaining integer validation; reconstructed qagame now sends the raw
mask too. Previous reconstructed servers sending 1 remain accepted. WASM
cgame/qagame rebuild and export checks pass, with source-contract regressions.
Browser intermission against a multi-vote original server remains pending.
No separate ui module feature or pak change is claimed.

Mapvote history staging aligned with original BeginIntermission (Ghidra
0x899xx) and ExitLevel: current-map play count increments during list setup;
rejected maps age there, offered maps age at exit, eligible maps outside the
offered prefix do not age. Removed the exit-time current-map reset to zero.
An empty ballot now still writes history before normal nextmap rotation.
The receiver's list format is unchanged. WASM qagame build/export checks and
source-contract regressions pass; persistent-history browser scenarios are
not yet validated. The capacity-limited offered prefix remains documented
hardening rather than exact original list-size behavior.

Voted-map rotation preservation implemented: ExitLevel ELF 0x7ae7a adds
0x2b937cc to EBX (0x2a4614), resolving g_nextmap at 0x2e37de0,
then adds 0x10 for vmCvar_t.string. The emitted command now matches the
original `map %s;set nextmap %s` rather than dropping the rotation after a
successful vote. Ghidra's corresponding address is 0x8ae7a; earlier 0x8ae72
references below are Ghidra addresses, not raw ELF addresses. WASM rebuild
and mapvote source-contract tests pass. Browser rotation testing remains
pending. No cgame/ui wire change or pak modification is involved.

Mapvote no-vote exit parity: original ExitLevel at 0x8ae72 only overrides
nextmap for a positive winning tally. The reconstruction previously selected
a map even with zero votes. It now writes history and returns false for that
case, allowing g_main's existing vstr nextmap path to run. Positive-tally
selection and cgame/ui message formats are unchanged. WASM qagame rebuild and
side-module/export check pass, as do mapvote server/flag source checks; no-vote
browser round-transition testing remains outstanding. Exact history timing
still needs comparison; voted-map nextmap preservation is addressed above.

WASM validation: cgame, qagame and ui rebuilt successfully with the installed
Emscripten SDK; all three pass the side-module framing and vmMain/dllEntry/
vmWasmAbi1 export checks. Compiler warnings remain; browser runtime parity is
not certified. The old cache toolchain path C:/emsdk was corrected locally to
C:/Users/micha/emsdk. No native build was run for this validation.
Map enumeration now rejects names that cannot fit the local MAX_QPATH buffer
before indexing its suffix with the original VFS length, avoiding an out-of-bounds
access. A source regression check records the guard; runtime VFS fixtures remain
pending. pak and the engine are unchanged.

The mapvote ordering implementation now uses a per-map random key rather than
sorting by vote_eligible. Original G_SortMapsByzOrder (ELF 0x76030, symbol
size 151) compares signed record +0x94 descending; the initialization in
sorted nitmod_unknown.c assigns rand() there, while vote_eligible is +0x90.
Flag 8 returns equality. A typed comparator covers 1152 combinations of flags,
equal keys and signed endpoints in an executable CTest; qagame Windows x64
build passes. The existing stable insertion order is retained for equal keys;
exact cross-platform rand sequences and original libc qsort tie order are not
claimed. Server list IDs and cgame/ui wire fields remain unchanged.

Mapvote reliable-command capacity is now accounted for by the shared visible
count used for list/tally generation and eligibility accounting. Previously
only the list sender stopped at the buffer limit, while other consumers retained
the larger count. The cgame tally receiver clamps excess totals, so this was
inconsistent server accounting rather than a demonstrated client crash. The
original cgame tally contract (CG_parseMapVoteTally, 0x454e0) remains unchanged.
This capacity guard is a documented reconstruction hardening, not a claim that
the original server used this exact budgeting algorithm. Existing mapvote
source-contract checks and Windows x64 qagame build pass; runtime long-name
fixtures remain pending. No additional ui feature is claimed for this change.

Mapvote history loading now follows original `G_mapvoteinfo_read` (around
0x89400, sorted qagame/nitmod_game.c): allocate file length plus terminator,
read the complete VFS file, close it, parse using a separate cursor and free
the original allocation. The previous 16 KiB truncation was a reconstruction
limitation. Allocation failure closes the file and preserves history; an empty
file also closes correctly. Windows x64 qagame builds and existing client/server
mapvote source-contract checks pass. Large-file runtime and allocation-failure
fixtures remain unverified; cgame/ui wire formats are unchanged.

The historical rows below are incremental evidence, not a current completion
percentage: several earlier "not gameplay-active" entries were superseded by
later integrations. Do not total these rows as completed/uncompleted features.
`reference/open-port-bugs.md` still requires live verification for weapon
pickups, poison lifecycle, HUD layout and original-server custom PK3 behavior.
Movement delay Cvars remain explicitly deferred at the user's request.

The cgame arena parser was compared with original `CG_FindArenaInfo` in
`src_nitmod_decompiled/cgame/sorted/cgame_client.c` (routine around 0x98000).
Timelimit and team respawn fields are parsed as integers and discarded. The
portable implementation now uses a separate `int` instead of writing through
an `int *` alias into a string pointer. This preserves parsing/output behavior
without depending on the original 32-bit stack-slot reuse. Windows x64 cgame,
qagame and ui build successfully; this is not a macOS/Android or runtime parity
certification. No new ui/qagame gameplay behavior was activated in this review.

The original i386 shared objects are retained in
`original_nitmod_shared_objects_32bit/`; their SHA-256 values are in
`reference/original_nitmod_i386.sha256`.

| Area | Source reference | Product implementation | Evidence |
| --- | --- | --- | --- |
| Original TAGCONNECT range | original startup loop 777..840 vs ET 829..892 | selected startup/update range; reconstructed server layout marker | stock/original/reconstructed full-source cases and endpoint/update tests; other original configstring ranges and real remote join remain pending |
| Animation-condition execution | original script rules on typed condition storage | full-source update/evaluate and idle-selection fixture | 13,824 non-aliasing evaluations and seven exact idle-name selections; synthetic model metadata only, gameplay/MDX/browser unverified |
| Complete original animation-script grammar | unchanged human_base.script | full-source BG_AnimParseAnimScript test with synthetic model-name metadata | complete script parsed and generated animation references checked; real MDX loading, rendering and browser map startup remain unverified |
| Localhost identity and animation vocabulary | original poison/Bomb names; native 64-bit condition storage | gamename nitmod; four distinct animation-only bits and bounded string table | full-source original definitions/weapon-condition fixture; no asset changes; extra weapon gameplay and original wire-ID integration remain unported |
| Original-server team-score reception | original unconditional tsc branch | validated two-score reception without reconstructed handshake | full-source dispatcher tests cover signed endpoints, malformed atomicity and charge-state preservation; original score-change presentation pending |
| Original-server charge reception | original unconditional ct dispatch | receive ten validated charge values without reconstructed handshake | full-source cgame dispatcher test; no capability inference; other original-server messages and snapshot compatibility pending; reference/original-charge-reception.md |
| Original animation weapon contract | cgame/qagame item tables and BG_InitWeaponStrings | read-only identity and script-operand tests | all 53 records agree; 52-entry loops pinned; original script operands resolve; reference/original-animation-weapon-contract.md; runtime identity translation remains open |
| Native artifact format correction | local MZ header in misleading .mp.i386.so host output | Windows x86 uses *_mp_x86.dll; Darwin *_mac; Windows x64 host tests separate; Linux/WASM names retained | naming matrix and PE/WASM rejection tests; reference/linux-invalid-elf-header.md; actual Linux build blocked by unavailable Docker/WSL |
| Map-load blockers and UI bit flags | native fireteam info string; original UI parser/action/checkbox | NCS accepts backslashes; shared UI bitflag support; asset override approach withdrawn | real UI parser and 160 toggle/paint cases, config store regression; original PK3 must load unchanged; poison weapons and referee-menu warnings unresolved |
| Named script trigger | original ELF 0xb0cbd..0xb0d2d | cached named lookup and original bot-skip behavior | 32 full-source cases including bot-only matches, unused slots and caller yielding; special trigger targets remain unchanged |
| Global accum trigger hash iteration | original ELF 0xb2931/0xb2960/0xb2982 | typed cached lookup in global trigger_if_equal | 16 global and 16 local full-source scenarios with independent storage, ordered dispatch and deferred caller termination; other globalaccum branches pending |
| WASM engine ABI fix | ET:Legacy marker and thirteen-slot VM_EntryPoint_t | all modules export vmWasmAbi1; WASM qagame gains five trailing slots | real Emscripten build/load/entrypoint probes and 83 native tests; reference/wasm-vm-abi.md; website deployment/browser gameplay pending |
| Local accum trigger hash iteration | original calls 0xb2335/0xb235c/0xb237e | cached script-name iteration in trigger_if_equal | 16 real script scenarios verify all recipients and deferred caller termination; other accum branches/globalaccum pending |
| attachtotag hash fallback | original G_ScriptAction_TagConnect 0xb2fd0 | cached script-name fallback after targetname lookup | 8 real tag/configstring scenarios and angle/client flag checks; renderer/runtime parity pending |
| Script-trigger hash caller | original target_script_trigger_use 0xd8130 | cached first-match lookup in native target use | 10 real script/action/target scenarios; self fallback and ordering checked; other callers and G_ModifyTOI pending |
| Cached classname/script-name searches | original 0x10e820/0x10e890 | typed forward live-slot searches | 6144 slot/hash/method profiles plus multiple matches and defensive boundaries; caller migration pending |
| Target/script-name cache lifecycle | original fields 0x5bc/0x5b0 | typed private fields; pre-spawn initialization and script set updates | 45 spawn-name combinations plus real script parsing/free fixtures; hash consumers and G_ModifyTOI pending |
| Script set classname cache | original 0xb61a0 | sticky classname_nospawn alias; changed-class refresh before relink | 16 real-parser/link scenarios; other script caches/TOI handling remain pending |
| Bot world AABB | original slot 21, 0x2248f0 | typed selected abs bounds/client shift/MG42 fallback | 72 profiles with six outside planes and inclusive boundary; original versus selected entity tested; script cache writers pending |
| Team-item cached classname writes | original bg_itemlist tuples and LaunchItem/G_CallSpawn stores | native IT_TEAM/red-blue mapping before spawn rejection and drop callbacks | exhaustive native type/tag/cache cases and real LMS spawn rejection; script SetValues and full drop runtime parity pending |
| Map-spawn classname cache / local AABB adapter | original init 0xe6e10 and spawn 0xcd087..0xcd219 | typed private cache, post-spawn refresh, selected-entity local AABB | init-retention and free/neverFree tests; dynamic item/script writers and world AABB pending |
| Bot AABB internal stages | local AABB 0x223ca0 and spawn hash write 0xcd219 | typed construction selection and explicit-cache local bounds | 256 selection/14 bounds cases; complete adapter and cached-classname lifecycle pending |
| Bot oriented world bounds | ETInterface slot 22, ELF 0x223b20 | typed center/axes/half-extents adapter | 48 profiles plus required-output/handle errors and unused-world success; local/world AABB special cases still pending |
| Bot eye/bone positions | ETInterface slots 15/16, ELF 0x224750/0x2245d0 | typed position reuse; client viewheight addition; bone ID ignored as original | 60 valid profiles plus errors; signed height offset and original delegation pinned; no loaded C++ interface |
| Bot entity orientation | ETInterface slot 17, ELF 0x2240e0 | typed viewangles/currentAngles adapter with optional forward/right/up | 192 profiles check client selection, cardinal rotations and output masks; original instructions pinned; no loaded C++ interface |
| Bot entity velocity | ETInterface slot 18 and G_RunEntity oldOrigin write/read sequence | typed trajectory delta / fixed-factor mover velocity adapter | 24 profiles cover slot 63/64 boundary and distinct candidate fields; original instructions/constants pinned; no loaded C++ interface |
| Bot entity position | ETInterface slot 19, ELF 0x223ec0 | typed client origin / rotated local bounds center adapter | 48 geometry profiles plus stale/unused/world/error paths; original half constant and instructions pinned; no loaded C++ interface |
| Four basic bot engine adapters | ETInterface slots 29/43/45/46 | typed time/ID/handle/existence methods use runtime table | 1024 live/stale/unused slot tests and signed times; native/WASM builds and 83 tests; C++ interface installation pending |
| Omni-bot engine vtable inventory | original ETInterface 0x2a4240 with R_386_32 relocations | 55-slot versioned JSON and validated extractor | every method address/code hash recorded; report equality and malformed-relocation tests; 83 tests; adapter signatures/ABI pending |
| Omni-bot loader contract extraction | original Init/LoadLibrary PIC operands | hash-pinned read-only extractor and regression test | version 17, 44-byte i386 table, export name and path formats recovered; 83 tests; C++ engine vtable/loader not implemented |
| Bot serial table runtime hooks | original vmMain reset before G_InitGame and early G_FreeEntity deletion | module-owned table with typed reset/free/resolve adapters | full-source old-handle invalidation before callbacks and neverFree tested; native/WASM builds and 82 tests; actual bot event/library pending |
| Bot handle free-hook ordering audit | original G_FreeEntity deletion call precedes callback/unlink/neverFree | full-source free/reuse regression, no runtime bot hook yet | four callback/neverFree profiles; pinned original ordering; native build/82 tests; loader/reset/event integration pending |
| Omni-bot serial table mutation, isolated | original InitHandles and EntityDeleted | typed reset/advance functions with explicit record fields | all serial inputs/flag bytes and 1024 reset slots tested; native/WASM builds and 82 tests; event-before-mutation/runtime hooks pending |
| Omni-bot handle codec, isolated | original HandleFromEntity/EntityFromHandle ELF 0x21e520/0x21e490 | fixed-width typed codec built but not gameplay-connected | exhaustive serial/index tests; native/WASM builds and 82 tests; lifecycle and loaded interface pending |
| Full-source mine eligibility pipeline | real G_LandmineThink and recovered filter/geometry functions | 16 native query-to-trigger fixtures | first rejection/second candidate, 11 triggers/5 exclusions, link ordering and full state checked; 81 tests; bot handle/interface dependency documented |
| Landmine bot eligibility | original Omni-bot bit 0x20 and team/spotted branches | typed filter and original-default omnibot_flags registration | 2048 cases; original Cvar/bytes and hook order; native/WASM builds and 81 tests; bot event/runtime pending |
| Landmine owner exclusion | original bit 0x100 and weapon 0x14; original pliers.weap identity | owner excluded except with native WP_PLIERS in entityState | 12288 flag/team/owner/weapon cases; original-byte/path evidence; native/WASM builds and 81 tests; Omni-bot rules/live replay pending |
| Landmine teammate exclusion | original G_LandmineThink bit 0x20/clientNum comparison | typed filter before initial contact geometry, not post-trigger | 4096 policy cases, instruction/source checks, native/WASM builds and 81 tests; owner bit 0x100 and Omni-bot rules pending |
| Precise landmine contact policy active | original sEntWillTriggerMine 0x8e180 and Cvar registration | separate typed g_nitmod_mine_contact.c; default-off/archive Cvar; existing mine callers | 400 policy cases plus bounds/guards, original instruction checks, native/WASM builds and 81 tests; private caller rules/live parity pending |
| Landmine trigger latch | original store 0x8ded2 and reader 0x8e1cf; compiled offset 0xfc | LandMineTrigger writes typed s.onFireStart=1 | 36 transition profiles, 60-row shared-layout comparison, native/WASM builds and 80 tests; precise-contact consumer/private mine variant pending |
| Landmine trigger collision transition | original LandMineTrigger ELF 0x8de73/0x8de93 | trigger retains CONTENTS_BODY before linking | original bytes and 12 full-source transition profiles; native/WASM builds, 80 tests; private mine variant and field 0xfc unported, live replay pending |
| Landmine/satchel initial collision correction | original ELF 0x8f12d/0x8ee09 instruction pairs | native spawn branches initialize CONTENTS_BODY | hash-pinned bytes and source invariants; native/WASM builds and 80/80 tests; engine collision/settling/arming replay pending |
| Dynamite spawn collision correction | original fire_grenade ELF 0x8f246/0x8f251 | WP_DYNAMITE initializes CONTENTS_BODY instead of CONTENTS_CORPSE | hash-pinned instruction/source regression, native/WASM builds, 80/80 tests; actual collision/arming replay pending |
| Deferred projectile chain integration | real radius damage, G_NITMOD_WeaponDie and G_RunThink | typed damageable smoke secondary in clear/blocked visibility fixtures | 720 profiles, 20 secondary explosions; next-tick scheduling, one event/link and unchanged primary/owner checked; other secondary families and original/browser replay pending |
| Non-client splash victim integration | current G_RadiusDamage/etpro_RadiusDamage/CanDamage/G_Damage | full-source populated and blocked-visibility fixtures | 480 profiles; 20 real 75-point victim hits; radius/non-damageable/source exclusions and satchel pass filtering; original/player/browser parity pending |
| Weapon-specific explosion and empty-world splash integration | real G_ExplodeMissile, G_TempEntity, G_RadiusDamage and etpro_RadiusDamage | full-source native fixture with five weapon identities and zero/nonzero splash | 240 profiles, 40 explosions, 32 shake entities, 20 traces/24 queries; team counter and temporary-link restoration checks; actual victims/original/browser parity pending |
| Delayed projectile think integration | real G_RunThink and G_ExplodeMissile | full-source test checks before/due/repeated timer execution | 288 timer calls, 16 common explosion transitions, single link request and event; 80/80 tests; zero-splash/weapon-id-0 fixture excludes weapon-specific effects |
| Projectile damage admission integration | real G_Damage early gates and four active option families | full-source test expanded to six states and protection-bypass flag | 96 profiles/192 hits, blocked target/owner byte preservation; native build and 80/80 tests; live engine/team-damage parity pending |
| Full-source projectile damage integration | actual G_Damage, new handlers and G_AddEvent | native test links full qagame source target | eight enabled/disabled profiles, 16 real damage calls; satchel playerState event/inventory checked; host build and 80/80 tests; explosion/physics replay pending |
| Airstrike-marker damage option | original case 0x15, mask 0x4 and AirstrikeEntities registration | WP_SMOKE_MARKER spawn uses typed 40-HP small-canister/death setup | 768 combined independent-mask cases; native/WASM builds and 79/79 tests; registry/kicking/live airstrike replay pending |
| Hand-grenade damage option | original shared grenade cases 4/9, mask 0x1 | both native hand-grenade spawn hooks share typed small-canister setup | 512 combined smoke/grenade mask cases, native/WASM builds and 79/79 tests; private damage tables/kicking/engine replay still pending |
| Smoke-bomb damage option | original mask 0x8 spawn branch and Nit_WeapDie 0x89390 | typed 40-HP/bounds setup and next-tick death handler linked to WP_SMOKE_BOMB | 256 masks/8 callback cases, native/WASM builds and 79/79 tests; other damage options and live gameplay pending |
| Satchel damage option activated | original g_damageweapons registration and spawn mask 0x2 | native Cvar table plus typed satchel spawn configuration | default 0/flags 0 hash-verified; 256 masks and 32 callback cases; native/WASM builds; other damageweapons masks remain unported |
| Satchel destruction handler, inactive | original Nit_SatchelDie 0x8a5f0 and g_damageweapons mask 0x2 spawn gate | typed g_nitmod_satchel_die.c compiled but not assigned to entities | 32 state/timer/event cases; native/WASM builds and 78/78 tests; configuration gate and activation pending |
| Active satchel-free inventory port | original qagame G_FreeSatchel ELF 0x8a570 | g_nitmod_satchel_free.c, native extra EV_NOAMMO removed, defensive index checks | 600 executable cases; native/WASM builds and 77/77 tests; original gameplay replay pending |
| Active HQ mine-warning sweep port | original qagame ELF 0x8dbe0 and sorted client caller | g_nitmod_mine_sweep.c replaces native detection loop; CMake/SCons linked | query-and-false semantics, 80 executable cases; native/WASM builds pass; caller timing gates and original runtime replay remain pending |
| WASM Cvar writeback consumption | BotAIStartFrame memorydump branch and G_CVAR_UPDATE adapter | isolated typed callback writes module-owned vmCvar_t | real module observes integer=1 and emits expected set/reset sequence; baseline zero probe and 75/75 host tests pass; no live registry/Botlib implementation |
| Snapshot/config/Cvar memory layout | each tree's q_shared and cg_public headers | expanded independently compiled WASM probes | all six sizes, 45 field pairs and two constants match; snapshot 148964/gameState 20100/vmCvar 272 bytes; 75/75 host tests; no real data transfer claimed |
| Compiled WASM shared-layout sample | separate ET 2.60 and Legacy q_shared headers | same probe built/run separately under Emscripten/Node | usercmd 28/playerState 1452/entityState 288 bytes on both sides; 28 field offsets/sizes match; not full ABI or existing-engine-binary verification |
| Engine extension gates and cgame error callback | Legacy completion/snapshot/demo call sites and VM extension flags | isolated cgame command-1338 negative probe | exact CG_ERROR string observed through actual array callback; completion lookup opts in, snapshot flag gates extended call; all demo paths not certified |
| Engine-to-module command audit | ET 2.60 and Legacy export enums | schema-v2 bidirectional export report with numeric collision details | all 39 common commands match; four Legacy-only commands, three old mod-only bot commands; no collisions; extension gating not yet verified |
| Botlib frame reachability | BotAIStartFrame, native trap adapters and current qagame WASM | isolated bounded diagnostic in entrypoint harness | actual seven Cvar updates then syscall 205 observed; AAS world helper confirmed no-op; no normal engine-loop invocation or bot functionality claimed |
| Engine syscall number audit | ET 2.60 and local Legacy public import enums | strict read-only parser and hashed JSON report | cgame 147/ui 121/qagame 65 common names match numbers; 147 qagame names absent; reachability and behavioral support not established |
| WASM array syscall ABI correction | local Legacy VM_DllSyscall and Sys_LoadGameDll array callback | shared conditional adapter in all three syscall files, native ABI preserved | real three-module WASM rebuild and array callback probes pass; native build and 73/73 host tests; remaining engine ABI and browser runtime unverified |
| WASM variadic argv round trips | qagame/UI console dispatch and trap_Argv adapters | typed harness validates int/pointer/int callback arguments and writes module-owned buffers | real individual/concurrent probes pass, exactly four callbacks across runs; cgame callback and actual engine transport remain untested |
| WASM pre-init entrypoint execution | current ET 2.60 dispatchers and public command enums | optional typed entrypoint harness, rejecting syscall callback | real dllEntry calls and seven vmMain probes pass individually and together; 73/73 host tests; no initialization or engine syscall exercised |
| Actual WASM dynamic loading | same built side modules, Emscripten 4.0.23 and Node 24.19.0 | standalone MAIN_MODULE harness reuses shared dlopen/dlsym checker | three individual and simultaneous loads succeed; missing-file negative control passes; no ET entrypoint or browser execution |
| WASM import-provider audit | actual side modules and local Legacy engine WASM/JS | read-only hashed JSON audit with explicit provider classifications | all 91 imports have static provider candidates; nine classifier cases and 72/72 host tests pass; signatures, loader execution and browser gameplay not verified |
| First actual three-module WASM build | existing Emscripten 4.0.23 SDK found via Legacy cache | corrected shared ReviveEntity prototype; WASM linker warnings fatal | real build, all artifact checks and Node WebAssembly validation pass; module hashes/import counts recorded; Windows build and 71/71 tests; browser instantiation pending |
| Executable WASM build driver | three side-module build/output requirements | run_wasm_build.py checks tools, configures/builds all modules and rechecks each artifact | mocked success/failure and per-output rejection tests; host build and 71/71 tests; real preflight fails on absent emcmake/emcc |
| WASM post-link artifact checks | WebAssembly binary framing/export and dylink conventions | bounded parser invoked after linking each side module | synthetic header/truncation/export/duplicate metadata rejection tests; host build and 70/70 tests; no real WASM output or browser validation yet |
| WASM side-module and entrypoint correction | local ET:Legacy ETLEmscripten.cmake / ETLBuildMod.cmake | enable shared support before targets; explicit WASM-only default visibility on all six entrypoints | new source contracts, 69/69 host tests; no active SDK found and no WASM binary/browser validation claimed |
| Successful-build hash evidence | release reference integrity requirement | Linux driver emits unique atomic JSON only after checks, verifies original manifest and separates artifact hashes | synthetic success/failure tests, real original hashes verified; Windows build and 68/68 tests; no real Linux report generated |
| Native Linux module-load smoke tests | dynamic loader/entrypoint contract | Linux-only compiler-matched loader, per-module and concurrent tests, RTLD_NOW/LOCAL | portable shared-orchestration failure/cleanup tests pass; Windows build and 68/68 CTests; real Linux loading not executed |
| Strict Linux-i386 configure gate | release data-model requirements | container enables NITMOD_REQUIRE_LINUX_I386; target policy and fresh compiler probe | seven executed CMake policy cases; complete Windows build and 67/67 tests; successful Linux toolchain probe still unavailable |
| Linux link and entrypoint gates | native syscall-pointer adapters and ET module exports | Linux targets link libm and reject unresolved symbols; driver verifies public dynamic vmMain/dllEntry | host fixture tests and all three original ELF export checks pass; 67/67 host tests; actual Linux link still blocked by local environment |
| Linux-i386 build-driver repair | existing container workflow built modules only before CTest; Dockerfile was Git-ignored | tracked tools/linux-i386/Dockerfile and fail-fast Python driver build all targets, test, validate three ELF32/i386 headers | new host orchestration tests; complete Windows build and 67/67 CTests; actual Linux run blocked by unavailable Docker engine and WSL virtualization |
| Full/overfull reload completion integration | actual migrated begin and native transition/transfer paths | outer-clip matrix expanded from 216 to 7776 scenarios, 5472 completed reloads | independent akimbo clip levels, reserve amounts, animation gates, whole-state and ammunition conservation checks; no product change; 66/66 host tests |
| Active outer-only full-magazine gate for reviewed light weapons | original begin has no inner full-magazine veto | explicit twelve-identity migration predicate; eight additional light weapons beyond prior akimbo fix | 216 direct/outer cases, updated FG42 scoped-handoff coverage; ordinary full requests still rejected; host build and 66/66 tests |
| Executed akimbo consumption-to-reload cycles | actual native availability, consumption and transition stage | 1944 deterministic multi-action test scenarios | four variants, every 0..8 initial clip pairing, reserve 0/1/30, normal/alternate input; per-shot conservation and exact reload events; 66/66 host tests; no product changes |
| Shared active firing-clip selection | existing native alias and reviewed akimbo rules | PM_WeaponFiringClip used by actual availability/consumption functions | 4224 native whole-state cases including asymmetric clips, sentinel/overspend and reserve mode; 66/66 host tests; refill policy not activated |
| Active defined drop/raise time addition | qagame 0x2a410 / 0x2be48; cgame 0x198f0 / 0x1b328 | common NITMOD_AddWeaponTime32 for switch phases and READY reload | 504 extreme-timer executions across 18 alternate pairs, both phases and reload intent; whole-state comparisons; host build and 66/66 tests |
| Active defined READY reload addition | original qagame 0x288a0 / cgame 0x17db0 32-bit ADD | NITMOD_AddReloadTime32 used by shared native begin | 98 added READY cases, 294 total timer-extreme executions; explicit wrap without signed overflow; hardened opt-in API unchanged; 66/66 tests |
| Active firing reload timer compare/store | qagame 0x288d0 / cgame 0x17de0 | shared begin replaces subtract/add with original direct maximum assignment | 196 whole-state signed-extreme/fast-reload cases; source contract rejects overflowing expression; host build and 66/66 tests |
| Shared reload animation selection | previously inspected original begin animation branches | pure NITMOD_ReloadAnimation used by native selector and recovered feedback | 468 selector/wrapper cases plus existing feedback tests; native skill versus recovered ability kept separate; complete host build and 66/66 tests |
| Transition-stage timer and animation boundaries | current native completion contract | 3168 additional executed integration scenarios, no product changes | all 44 mapped identities, independent -1/0/1 timers, held input and four animation gates; whole-state/event-ring preservation; 66/66 host tests |
| Executed multi-phase reload/switch cycles | existing typed PM_Weapon transition stage | PM_ProcessWeaponTransitions preserves order and return semantics; generated verbatim test body | 64 repeated-input/timer/drop/raise/reload cycles, eight weapon identities, switch veto and exact final inventory; 66/66 host tests; no new gameplay rule |
| Active alternate-key reload preference | qagame 0x2a7d4..0x2a7f9 / cgame 0x19cb4..0x19cd9 | common request predicate in native PM_CheckForReload and recovered policy builders, using existing synchronized preferences | 6336 actual request comparisons with ordinary reload, state/time/inventory/scoped cases; existing capability producer contracts; 66/66 host tests |
| Active akimbo reload with full opposite hand | original manual either-hand check qagame 0x2a9e8 / cgame 0x19ec8; no inner full-clip veto | shared native begin bypasses legacy sidearm-only guard for four mapped akimbo identities | failure reproduced before fix; 1296 manual/auto inventory/state/lean scenarios through actual completion; 66/66 host tests |
| Active reload while leaning for mapped weapons | complete original begin bodies qagame 0x28730 / cgame 0x17c40 have no lean veto | shared native begin keeps lean veto only outside 39 reviewed eligible identities | 4212 whole-state differential cases; manual/auto/direct, left/right, state/inventory/prone; 66/66 host tests; other inventory gates retained |
| Executed native reload completion and full cycles | actual PM_FinishWeaponReload/PM_ReloadClip/idle functions | expanded native integration test, product source unchanged | 6336 completion cases and 840 begin-to-finish cycles; shared akimbo reserve, overfull return and whole-state/no-event checks; native adrenaline alias explicitly retained |
| Active exact fast-reload arithmetic | original binary32 factor / extended-product truncation in both modules | shared arithmetic primitive used by native and recovered duration paths; native eligibility retained | 840 real begin cases plus existing 352352 duration cases; 20-to-12 / 1000-to-649 boundaries; no recovered ability-word activation |
| Active tripmine reload body-animation correction | 47-entry body dispatch in each original (qagame 0x22e128 / cgame 0xff468) | common body-event selector used by native and reconstructed begin paths | 168 executed native cases, 94 original jump destinations pinned; tripmine skips body event, landmine retains it; timing/first-person/event preserved |
| Active empty-current-reserve reset | original current ammo lookup/zero reset qagame 0x28782/0x287f2; cgame 0x17c92/0x17d02 | shared native begin invokes alias-agreement migration adapter before target restrictions | 1800 current/state/reserve and 600 target-precedence cases; whole-state isolation; 43 agreed identities enabled, adrenaline/unmapped deliberately unchanged |
| Active alternate-fire reload acceptance | original ready/fire/altfire gate qagame 0x28756 / cgame 0x17c66 | shared native PM_BeginWeaponReload now uses NITMOD_ReloadStateAllowed | 288 direct/outer native reload cases, exact add/max timers/events and preserved blockers; narrow gameplay correction, full recovered dispatcher still inactive |
| Active raise completion and native reload handoff | original READY-before-idle/reload qagame 0x2bd55/0x2bd39; cgame 0x1b237/0x1b21b | shared PM_FinishWeaponRaise called by PM_Weapon at existing phase position | 144 real scoped-return/reload cycles, timer/repeated/state checks; verbatim native begin-reload executed; recovered dispatcher remains inactive |
| Ordinary-switch and mortar-veto integration coverage | actual product begin/finish; original nextWeapon-before-veto ordering in both modules | extended nitmod_weapon_change host executable | 38128 ordinary-pair scenarios plus 16 water/prone/reload cases; bytewise inventory/extended-state preservation, event boundary and native animation checks; no product behavior change |
| Executed native weapon-change integration | verbatim product begin/finish/transfer/animation functions, regenerated from bg_pmove.c | new host CTest target nitmod_weapon_change | 576 transition/gate combinations plus nine guard, two ownership-loss and three reselection cases; real native inventory/events/math; body-script and condition boundaries doubled; 66/66 host tests |
| Active MG42/mortar deployment switch plan | original alternate pairs 29/46 and 33/42, both modules' raise branches | typed deploy plan used by shared begin/finish; duplicate direction blocks consolidated | 2704 pair plans plus null/extreme rejection; eight original raise immediates pinned, native direction/guard source contracts; placement replays pending |
| Active rifle-grenade switch policy | both originals' drop transfer gate, 2350/1347/0 raise branches and mode bit | typed drop request, raise plan and remembered-mode helper replace duplicated shared Pmove cases | 45000 drop/raise inventory combinations, 468 mode cases and live source contracts; existing native transfer retained, not full recovered reload activation |
| Active single-pistol silencer transitions | original drop 0x2a670/0x19b50; raise 0x2c714/0x1bbd4; remembered mode bit | typed pistol plan replaces eight duplicate begin/finish cases; shared committed-mode helper | 2704 pair plans and 572 mode cases, null/extreme rejection and active-call ordering; ET-equivalent extraction, engine animation replay pending |
| Active shared scope-switch durations and alternate-table proof | original weapAlts qagame 0x2a5300 / cgame 0x12e660; FG42 drop/raise branches | NITMOD_ScopeSwitchDuration replaces duplicate FG42 cases in shared begin/finish | 44 native alternate entries match both hash-pinned originals; 2500 executed pair lookups, boundary cases and both drop dispatch tables checked; no timing changes or full engine parity claim |
| Active knife/smoke reselection raise | qagame 0x2c6a6/0x2c74e; cgame 0x1bb66/0x1bc0e | shared finish now preserves original same-weapon exceptions for typed knife and smoke bomb | 2500 pair predicates and 10000 commit/ownership/reload compositions; original IDs 48/50 explicitly unported; no full animation replay claim |
| Active weapon-change commit extraction | qagame 0x2bd93 / cgame 0x1b275 and owned/missing branches | shared PM_FinishWeaponChange calls typed NITMOD_CommitWeaponChange | all native targets/states, ownership masks, extreme invalid targets and whole-state mutation checks; existing ET-equivalent behavior preserved; times/animations not changed |
| Active switch-during-reload exclusion | PM_BeginWeaponChange qagame 0x2a2c5..0x2a2dd / cgame 0x197a5..0x197bd | shared native switch function now rejects WEAPON_RELOADING as well as dropping states | native-enum predicate tests and actual-call/guard-order source contract; gameplay-active narrow fix, full dispatcher still inactive |
| Reload decision dispatcher | original scoped reload-intent call into PM_BeginWeaponChange | NITMOD_ProcessReloadRequest connects decision, composed begin and explicit switch boundary | all three scoped pairs under ordinary/ability/war=2 policy; exact callback and repeated-request checks; live native switch binding still pending |
| Per-call reload preference input | typed continuation of cg_uinfo transport | appended mod-local pmove_t input populated in both client and both server setup paths | 102400 projection comparisons plus reset independence and four-hook source checks; playerState/usercmd/pmoveExt unchanged; gameplay dispatch still inactive |
| Live reload preference transport | recovered cg_uinfo bit 0x10 | archived cvar/update hook, capability-gated encoder/refresh, passive server bAltReloadAux storage | host build and source contracts plus exhaustive codec tests; default 0 is conservative port choice; gameplay remains unchanged and engine join/reconnect tests pending |
| Reload preference codec | CG_setClientFlags_part_0 and ClientUserinfoChanged ELF 0x4b5a2..0x4b5bf | typed auto/secondary-attack preference codec and flag-to-policy projection | 3200 cvar/flag cases and 102400 local/server-policy comparisons; cg_uinfo tuple unchanged; live publication/parsing hook pending |
| Auto-reload preference defaults | ammoTableMP +0x38 qagame 0x2a69a0 / cgame 0x12fd00 | separate NITMOD_WeaponAutoReloadDefault lookup for 44 typed identities | executed flags match both hash-pinned originals; 21 preference-dependent / 23 exempt; 88 input-policy composition checks; live overrides/settings pending |
| Reload input/settings predicate | PM_CheckForReload wbuttons/pmext and ammo +0x38 branches | NITMOD_BuildReloadPolicy uses native wbuttons/bAutoReload plus explicit extra setting/weapon flag | 6912 cases and decision composition; primary fire kept separate; original private offsets never applied to native state; live extra-setting/default binding pending |
| Outer reload/scoped decision | PM_CheckForReload qagame 0x2a870..0x2a8da / cgame 0x19d50..0x19dbd | NITMOD_DecideReload returns NONE/BEGIN/UNSCOPE using native targets and explicit request policy | 28512 combinations, scoped-before-timer order and exact war=2 exception; read-only, no weapon-change hook or live policy binding |
| Composed reload begin and body event | PM_BeginWeaponReload body table 0x22e128 / call 0x2885d | NITMOD_BeginWeaponReload composes checks, duration, typed body event and weapon feedback | 176 composition cases plus missing-model/overflow/order tests; animation-system boundary double, real event ring; no active gameplay hook |
| Reload start first-person feedback | PM_BeginWeaponReload animation 0x288e2..0x2894c, event 0x288b8 | nitmod_weapon_reload_feedback.c composes timing, gated animation and native predictable EV_FILL_CLIP | 4224 combinations, real event ring and repeated/invalid-call checks; body-script animation and active hook pending |
| Reload completion and idle animation | PM_Weapon qagame 0x2bbdf/0x2bbec; cgame 0x1b0be/0x1b0cb | NITMOD_FinishWeaponReload composes atomic transfer, READY and gated idle animation with native enums | 3168 combinations plus pending/failure/repeated-call checks; no completion event invented; no active PM_Weapon hook |
| Fast reload duration | qagame 0x28974..0x28994 / cgame 0x17e84..0x17ea4, eight supported identities | NITMOD_ReloadDuration uses exact binary32 factor rational and explicit ability bit | 352352 combinations, hash-pinned factor in both modules, integer boundaries and timing composition; not gameplay-active |
| Reload state gate and timer effects | original normal/alt fire stores 0x2cc19/0x2cdbc; begin-reload timing 0x288a0/0x288d0 | native enum gate, empty-reserve ready reset and isolated add/max reload timing | 420 state/timing and 36 state/reserve cases; no active hook, duration calculation or event/animation effects |
| Begin-reload inventory sequence | PM_BeginWeaponReload current reserve 0x28782, range 0x287c0, reset 0x287f2 | explicit result composes current-weapon reserve, target midclip restriction and translated weapon eligibility without mutation | 46464 current/target combinations; 39/44 range-eligible identities checked through original ID map; state gate/reset and reload effects not activated |
| Midclip restriction and MG42 override | PM_BeginWeaponReload qagame 0x28808/0x28812; cgame 0x17d18/0x17d22 | NITMOD_MidclipReloadAllowed consumes typed option and explicit ability word | 95744 cases plus loaded-registry composition; no active gameplay or skill-word binding |
| noMidclipReload definition flag | parser stores qagame 0x35b1e / cgame 0x2620e | typed options parsed and loaded atomically into caller-owned weapon registry | repeated/absent flags, section selection, 30 truncations, fallback, malformed/quoted data and forced reload rollback; consumer remains inactive |
| Reload request inventory predicate | PM_CheckForReload qagame 0x2a7a0 / cgame 0x19c80 | NITMOD_ReloadInventoryReady separates manual under-capacity from automatic empty-magazine checks, including both akimbo hands | 34136 predicate checks plus malformed-input rejection; state/time, scopes, abilities and begin-reload restrictions explicitly not covered |
| Recovered reload transfer | PM_ReloadClip qagame 0x12bf0 / cgame 0xa500 | nitmod_weapon_reload.c stages weapon-indexed capacity transfers, akimbo first then sidearm | 17068 inventory cases plus atomic failure/overflow boundaries; overfull return preserved; no active reload/prediction hook |
| Recovered client/server inventory aliases | qagame item table 0x2a59a0; cgame 0x12ed00, lookup 0x106e0/0x10730 | nitmod_weapon_inventory.c provides typed slots and opt-in recovered clip selection, including independent adrenaline | all 44 pairs checked against both hash-pinned originals; 1156 akimbo and 289 adrenaline/syringe pairs; host-only, no active prediction hook |
| Adrenaline class-tool spawn subset | G_AddClassSpecificTools war gate ELF 0x49f60 and grant 0x480b0 | G_NITMOD_GrantAdrenalineSpawn uses loaded ammo defaults, option overrides and bonus with independent slots | 286720 spawn cases plus real default/source/registry composition; overflow/unchanged-state checks; no active spawn hook or Omni-bot event |
| Adrenaline upgrade inventory subset | G_UpgradeSkill grant and AddWeaponToPlayer ELF 0x49d90, bonus 0x49ed0 | G_NITMOD_GrantAdrenalineUpgrade uses explicit eligibility/options/war and independent native adrenaline slots | 286720 combinations plus repeated grants and syringe-preservation tests; not gameplay-active; upgrade ordering, bot event and alias-consumer integration pending |
| Original/native item aliases | BG_FindAmmoForWeapon/BG_FindClipForWeapon ELF 0x211f0/0x211a0 | hash-pinned item extractor plus real native table/lookup diagnostic | 43/44 ammo+clip alias pairs match; adrenaline's native syringe-sharing explicitly pinned as a difference; 1156 akimbo cases now also tested with actual native data |
| Native clip/akimbo selection | BG_AkimboFireSequence ELF 0x21240 and sidearm table 0x22dfa0 | native helpers split to nitmod_weapon_akimbo.c with overflow-safe parity; isolated selector/consumption adapter uses native item aliases | 1156 clip pairs plus state/alias/error/bounds checks; helper move active in all three modules, new consumption adapter not gameplay-active |
| Resolved-clip consumption/refill | PM_WeaponUseAmmo ELF 0x2aa40 | nitmod_weapon_consumption.c writes one native ammoclip slot; exact-zero refill from defaultStartingClip for g_noReload bit 0 or panzer war=1 | 20580 combinations and invalid/sentinel/overflow cases; no gameplay hook, akimbo selection and knife state mapping pending |
| Original ammo/timing defaults | ammoTableMP ELF 0x2a69a0 and PM_Weapon uses consumer at 0x2cc30 | nitmod_weapon_defaults.c copies ten recovered fields for 44 native identities; native mod preserved | all 440 values hash-pinned; all consumption values and registry/empty-load integration tested; no global table writes, mod and state-specific consumption remain pending |
| Caller-owned weapon subset registry | BG_RegisterWeapon cached/forced load gate | g_nitmod_weapon_registry.c stores typed ammo/mask/recoil records with reset and read-only lookup | real loader/parser integration tests for cache hits, forced reload, rollback, distinct variants and retry; no global instance or gameplay hook; last-good retention is deliberate hardening |
| Composed recoil source loading | original filename/alternate selection and custom recoil parser | G_NITMOD_LoadNativeWeaponRecoil connects verified path table and engine token adapter to atomic ammo/mask/recoil parser | actual parser/application with engine-source doubles; fallback, every-token truncation, token corruption and stale-override clearing tested; global registry and gameplay hooks pending |
| Custom recoil subset | BG_RW_ParseDefinition +0x5dc..0x5e8 and PM_Weapon ELF 0x2d3be..0x2d448 | typed recoil config/parser and NITMOD_ApplyWeaponRecoil to native pmoveExt_t; helper built for cgame/qagame | transactional parsing and state-boundary/arithmetic tests; registry/loader integration and active PM_Weapon hook pending; invalid duration hardening documented |
| Weapon parser integer/resource boundaries | PC_Int_Parse ELF 0x25a10 minus-token path; port resource limits | shared ReadInteger supports split INT_MIN without overflow and rejects repeated signs | all nine ammo destinations, mask and composed loader tested; exact 64-depth/65536-read limits verified; no new gameplay attributes activated |
| Weapon ammo-definition subset | BG_RW_ParseDefinition ELF 0x35320: separate ammo destination | NITMOD_ParseWeaponAmmo and G_NITMOD_LoadNativeWeaponAmmo update caller-owned native ammotable_t and class mask transactionally | nine field mappings checked in disassembly; per-field/combined/section/truncation/overflow and loader tests; defaults ownership, remaining grammar and gameplay activation pending |
| Native weapon-definition paths | BG_RegisterWeapon ELF 0x363c0, jump table and case operands | nitmod_weapon_paths.c maps 44 named ET identities; G_NITMOD_LoadNativeWeaponClassMask selects file/section and bounded preferred/fallback paths | all 44 filenames/selectors checked against hash-pinned original; C path/boundary/loader tests; four private weapons, full attribute grammar and registry lifecycle excluded |
| Weapon source/token adapter | original preferred directory then weapons fallback | g_nitmod_weapon_definition.c opens/frees engine sources for strict mask parser with quoted-token handling and native filename selection | fallback/parse-failure/handle-lifetime/path-boundary tests; complete grammar and registration/reload ownership remain pending |
| Weapon class-mask parser subset | original weaponDef/both/both_altweap and classes field | nitmod_weapon_definition.c validates selected mask-only blocks and skips bounded opaque client/unselected blocks | section/repeat/negative/empty/truncation/unknown-field tests; complete attribute grammar and engine loader unconnected |
| Composed pickup adapter | original restriction-before-class-policy ordering | G_NITMOD_CanPickupWeapon connects Cvars, cached/live counts, Medic rules and notification; explicit validated mask required | integration precedence/error/mutation tests; both/both_altweap loader selection and native pickup hookup pending |
| Pickup configuration ownership | original classes parser field +0x6ac and g_medics registration | g_medics actively registered with verified default/flags; strict bitmask reader | hash-pinned ninth registration and malformed/bounds tests; .weap parser/reload lifecycle still pending |
| Pickup policy | original G_CanPickupWeapon after G_IsWeaponDisabled | g_nitmod_pickup.c with final war allowlists, class masks and Medic rules; not gameplay-active | 192000 rule combinations plus DENY/DEFER and mutation checks; BG_Weapons mask/g_medics ownership and pickup integration pending |
| Weapon-settings snapshot | original nitmod_SendNCS # fields | active atomic mapping of panzer percentage, five caps and g_weapons from registered Cvars; corrected previous heavy/panzer source mix-up | exact/preserved-field tests, malformed-input retention and source hook check; wire layout unchanged, runtime transcript pending |
| SetTeam population timing | original inline recount in setweapons branch | active refresh after session-team assignment and before native weapon setter | source ordering/condition check and real policy test contrasting stale/refreshed target-team count; native setter replacement pending |
| Class/loadout composition | original post-SetTeam weapon setter | disabled class handler now invokes typed loadout transaction after cache refresh | real config/count/policy/loadout integration tests with output doubles; SetTeam internals and dispatch remain native/disabled |
| Typed loadout transaction | original G_SetClientWeapons | g_nitmod_loadout.c composes policy/notification and latch publication; native setter unchanged | full client mutation boundaries, publication order, allow/deny/repeat/invalid cases; Omni-bot ABI and gameplay integration pending |
| Setclass handler | original Cmd_SetClass_f in nitmod_cmds.c | g_nitmod_class_command.c replaces empty stub; command dispatch deliberately remains disabled | query/team/latch/ordering and invalid-input spy tests; native weapon setter retained pending full restriction activation |
| Weapon decision notification | recovered limit reasons and nitmod_cp call conditions | G_NITMOD_CheckWeaponAndNotify joins server evaluation to targeted gated sender; not called by native restrictions | sender-spy tests for single send, silent/limbo/non-primary/allowed/invalid cases and client ownership; gameplay activation pending |
| Weapon-limit messages | qagame nitmod_cp and cgame SrvMsgs 19..25 | capability-bit-10 gated ncp sender/receiver, original text table and bounded parsing | original ELF text comparison, ID bounds and protocol source checks; restriction producer hookup and engine transcript pending |
| Server weapon adapter | composed recovered restriction data flow | g_nitmod_weapon_adapter.c connects config, cached population, live weapon counts and policy without mutations/messages | executable integration scenarios and client-state checks; native restriction activation pending |
| Team command cache refresh | original Cmd_Team_f inline recount after false SetTeam result | active refresh before subsequent G_SetClientWeapons | source hook test; separate class/Omni-bot paths pending |
| Team population cache lifecycle | original G_TeamCountPlayers and three client lifecycle tails | cache reset at map start; refresh after Connect/Begin/Disconnect CalculateRanks; isolated cached policy reader | transition/invalid-list tests and hook checks; bot/team-command refresh and restriction activation pending |
| Weapon Cvar registration | original gameCvarTable at ELF 0x2a7e20 | eight missing Cvars actively registered at G_RegisterCvars with original defaults and flags; three existing native entries retained | hash-pinned ELF extraction, source-to-original comparison and repeated-registration trap tests; gameplay activation/update timing pending |
| Weapon configuration reader | recovered restriction Cvar dependencies | g_nitmod_weapon_config.c atomically reads eleven existing Cvars, without registering defaults; not gameplay-active | exact mapping and preservation tests, 66 field-level malformed cases plus truncation and bitmask checks; defaults/flags/update semantics pending |
| Atomic team/weapon-count snapshot | original CalculateRanks, team-cache producer and ordinary/rifle loops | G_NITMOD_ReadWeaponCounts fills teamSize and weapon counts using distinct connected/non-spectator lengths; not gameplay-active | 450 rifle cases, 18 equivalent-pair cases, differing list lengths, connecting state, spectator fallback and atomic failure checks; cache refresh timing remains unhooked |
| Original primary classification | qagame ELF 0x32470 and Axis/Allies class records | typed G_NITMOD_IsClassPrimary called by composed weapon policy; native loadout tables unchanged | 4000 class/team/weapon/pickup cases plus invalid boundaries; gameplay activation pending |
| Rifle count session adapter | original nonzero equipment-status predicate | G_NITMOD_CountSessionRifleGrenades reads reconstructed session state for isolated counter | 450 combinations plus invalid input cases; native restriction caller not switched |
| Composed weapon policy | original G_IsWeaponDisabled branch order, heavy table and rifle-count sum | g_nitmod_weapon_policy.c composes typed snapshot inputs without side effects; not gameplay-active | all 50 weapon mappings in three cap scenarios, 3240 rifle combinations and ordering/invalid-input tests; engine snapshot, primary classifier and message adapter pending |
| STEN and restriction notifications | original G_IsWeaponDisabled class/pickup and nitmod_cp branches | isolated typed eligibility and message-reason selection; not gameplay-active | 20480 STEN and 4000 notification cases; g_weapons bit 0x200 verified from byte-offset test; full caller/configuration/transport integration pending |
| Numeric weapon limits | original G_IsWeaponDisabled heavy/panzer/cap branches | isolated ordered evaluator with explicit failure reasons | 426725 heavy and 4420 fixed-cap cases plus precedence/boundaries; caller policy/configuration integration pending |
| Rifle-grenade restriction revocation | original ClientThink_checkWeapons owned/disabled branch | g_nitmod_rifle.c clears one grenade bit/status and republishes changed clientinfo; not gameplay-active | both weapons, status/ownership combinations, mutation boundaries, callback ordering and repeats tested; full restriction producer pending |
| Rifle-grenade state lifecycle | original equipment assignment, session and rn | active native spawn assignment/reset, versioned equipment session Cvar, post-assignment rn publication and existing cgame receiver | adapter roundtrip/invalid-data tests and producer/consumer hook checks; mid-life revocation and limits pending |
| Rifle-grenade receive field | original rn emission and cgame token 0x89 | active optional signed rifleGrenadeStatus parsing in CG_NewClientInfo | original 279-token dictionary extraction and receive/reset hook checks; server/session/UI integration pending |
| Rifle-grenade team count | original G_TeamCount alternate/base-rifle branch | isolated typed counter with explicit per-slot equipment state | 450 combinations plus boundary cases; session flag write/read/userinfo ownership identified but not integrated |
| Team weapon count | original G_TeamCount and weapTeamConversion | active typed G_TeamCount in g_nitmod_teamcount.c, nine equivalent-weapon pairs | selected/latched, both directions, requester/team filtering and empty lists tested; rifle-grenade special branch retains native ET behavior |
| Weapon restriction precheck | original G_IsWeaponDisabled early branches | typed spectator/bot precedence and mode exemptions with explicit DEFER; not gameplay-active | 2800 combinations; team caps, pickup/class and notification branches pending |
| War-mode entry transaction | original mode-4 branch and cgame event 0x19 | g_nitmod_war.c composes guards/removal/knife/EV_NOAMMO/latch; not gameplay-active | event order, repeat calls, guards, mode changes and explicit reset tested; native lifecycle/configuration integration pending |
| Weapon removal | G_RemoveWeapons and original ELF item table | 42 mapped native weapon removals in g_nitmod_weapons.c; not gameplay-active | all 64 inventory bits and idempotence tested; four mod-only variants excluded; war latch/event integration pending |
| Weapon-check guards | original ClientThink_checkWeapons; connect/userinfo demo marker | typed demo classification and guarded adrenaline reconciliation; not gameplay-active | all 65536 flag patterns with demo/health combinations; cached state lifecycle and war/restriction paths pending |
| Adrenaline inventory reconciliation | original ClientThink_checkWeapons inner branch | typed weapon-bit removal in g_nitmod_abilities.c, not gameplay-active | 20480 combinations, class/unlock transitions and idempotence; full client mutation boundaries checked; outer guards and generic weapon restrictions pending |
| Adrenaline prerequisites | original EntHasAdren, ClientHasAdren and G_UpgradeSkill clip branch | typed g_nitmod_abilities.c wrappers with explicit unlock/configuration inputs; not gameplay-active | 122880 eligibility combinations and 512 option cases; inventory and private state integration pending |
| Player score | original G_SetPlayerScore 0x000cec00 and G_SetPlayerSkill inline tail | active typed adapter in g_nitmod_score.c, pure ordered/truncated calculation in nitmod_score.c | 823543 combinations plus range/nonfinite tests; CMake/SCons integrated; double/x87 edge differences documented |
| Skill rank | original ELF G_CalcRank / G_UpgradeSkill and rankTable | isolated NITMOD_CalculateRank in nitmod_skills.c | all 279936 valid level combinations tested; compiled results compared with original ELF table; native rank/ability logic remains active |
| Skill XP loss | qagame G_LoseSkillPoints | isolated typed loss transaction, recomputes progress and reports actual XP delta | executable threshold/limit/rounding tests; native level retention still active until downgrade side effects are ported |
| Air spawn/pause lifecycle | original ClientSpawn air-bit check and native ET pause/movement paths | common deadline, shift and remaining-time helpers used by spawn, match pause, movement and world effects | executable spawn/pause/resume tests, signed time limits and source hooks; no new skill activation |
| Battle-sense air reserve | original P_WorldEffects air branch | nitmod_air.c with active native g_nitmod_air.c adapter; zero unlock bits until skill integration; ET breather retained | timeline tests and adapter comparison against baseline ET; i386 12s/15s constants verified; perk activation and engine replay pending |
| Nitmod skill reward texts | original cgame cg_skillRewards at ELF 0x138a00 | separate bounded 7x5 table in cg_nitmod_skill_rewards.c, linked but not used by native popups | all 35 compiled strings compared directly with hash-pinned ELF; abilities and six-level activation pending |
| Native client skill safety | ET CS_PLAYERS skill digits and client XP/reward consumers | atomic seven-digit validation capped at current native maximum; bounded reward and next-XP lookups | executable digit tests and source hook checks; deliberate input hardening, no sixth-level activation |
| Skill progress calculation | qagame G_SetPlayerSkill numeric branch | isolated `NITMOD_EvaluateSkill`: highest level and independent unlock mask, per-skill cap and disable semantics | executable tests across all skills and thresholds; activation blocked by coordinated client-state/XP/reward migration, see skill-level-integration.md |
| Original function symbols | three hash-verified i386 modules | reproducible `original_function_symbols.csv`, 6549 defined function symbols with addresses, offsets, sizes and byte hashes | standard-library ELF reader and regeneration/bounds tests; addresses kept separate from unverified Ghidra mappings |
| Mine map-marker cleanup | qagame `nitrox_FadeLandmines` | separate `g_nitmod_map_cleanup.c` adapter used by owner cleanup | executable adapter tests with engine test doubles: missing/one/both markers, unrelated markers, last slot and free ordering; engine rendering pending |
| Spatial mine detection | qagame `G_SweepForLandmines` | existing ET team/radius detection retained as known difference | original i386 disassembly confirms constant-zero return; original caller/gameplay review pending |
| Satchel detonation | qagame `G_ExplodeSatchels` | typed owner/radius selection through a stable registry snapshot with generation/membership checks | executable boundary and callback-mutation tests; list-skip behavior deliberately not reproduced; chain-reaction replay pending |
| Owner explosive cleanup | qagame `nitrox_FadeLandmines` / `nitrox_FadeSatchels` | reverse typed registry traversal through existing `G_FadeItems`; clears ownership, removes both mine map markers and frees entities | executable owner/reuse tests plus source integration checks; existing timeout gates retained; engine replay pending |
| Landmine entity lifecycle | qagame `landmine_setup`, `fire_grenade`, `G_CountTeamLandmines`, explosion/free/reset | typed registry in `g_nitmod_entities.c`; armed team count capped at native `MAX_TEAM_LANDMINES` | executable lifecycle tests and source hook checks; Nitmod configurable limit and engine replay pending |
| Satchel entity lifecycle | qagame `fire_grenade`, `G_ExplodeMissile`, `G_FreeEntity`, `G_FindSatchel`, `G_InitGame` | dedicated `g_nitmod_entities.c/.h` registry: register on throw, unregister on explosion/free, reset on map start; lookup in creation order | executable tests with native `gentity_t` plus source hook checks; detonation now uses a mutation-safe snapshot with documented parity differences |
| Entity-array helpers | qagame `nitmod_core.c` 2350-2408 | `nitmod_entity_array.c/.h`: ordered, unique borrowed `gentity_s` pointers, capacity 1024 | executable C tests for capacity, duplicates, removal order and reset; satchel consumer and fatal overflow adapter integrated; spawn/mine/trigger consumers pending |
| cgame split | `src_nitmod_decompiled/cgame/sorted` | split and mechanically cleaned | generated source review |
| qagame split | `src_nitmod_decompiled/qagame/sorted` | split and mechanically cleaned | generated source review |
| ui split | `src_nitmod_decompiled/ui/sorted` | split and mechanically cleaned | generated source review |
| NCS transport | qagame/cgame sorted core | typed store, handshake, immediate+dirty delivery, and engine-to-NCS mirrors for assets, shader state, OIDs, spawns (including runtime ownership changes), and fireteams | source/build validation |
| NCS storage | qagame `nitrox_SetConfigstring` / `nitrox_UpdateConfigstrings` | engine-independent `nitmod_config_store.c/.h` with atomic validation and dirty tracking; qagame retains immediate and end-of-frame transmission | executable C tests cover all 655 slots, empty/repeated writes, size boundaries, rejected values and reset; engine network transcript pending |
| Protocol number validation | port handshake and NCS/hit/announcement input | shared strict decimal parsing in `nitmod_protocol.c`; rejects partial tokens and overflow before state changes | executable C boundary cases; intentional validation improvement over permissive conversions |
| Snapshot decoding | recovered `ct`, `tsc`, `mes`, `scs`, `#`, `ob` layouts | `nitmod_snapshots.c/.h` parses complete typed values before applying client state; common settings types shared with qagame; unsigned counters match server serialization | executable C cases for field order, signed/unsigned limits, finite float validation, actor bounds, score preservation and rejection at every field without partial updates |
| NCS asset indices | qagame `nitrox_CSIndex` and four asset wrappers | shared tested search in `nitmod_config_index.c`; typed native/NCS range adapter used by model, sound, skin and shader registration | executable C tests; original private sound +84 numbering translated to native indices; arbitrary NCS ranges unsupported |
| Predicted fall damage | qagame/cgame sorted pmove/core | typed shared `playerState` damage feedback at the recovered 50/25/15/10 fall tiers | source/build validation; replay pending |
| Spatial sound events | qagame `nitmod_core.c` | typed `NITMOD_PlaySoundEvent` adapter over ET's native `EV_GENERAL_SOUND` temporary entity | source/control-flow validation; reference entity-pool allocation optimization intentionally omitted |
| Global sound events | qagame `nitmod_core.c` | typed `nitmod_Sound_Global` adapter over native broadcast `EV_GLOBAL_SOUND` | source/control-flow validation |
| Platform path building | qagame `nitmod_core.c` | bounded typed `NITMOD_BuildFilePath` helper | source/control-flow validation; native filesystem actions remain behind future platform backends |
| Spree/revive announcements | qagame/cgame sorted core/events | shared validated announcement decoder, correct kill/death/revive counts and capability-gated `nsp`; positive kill-spree delivery respects `g_announcer & 1` | executable C decoder tests and host build; full producer options, original Cvar defaults and private phrase/sound tables remain pending |
| Hit sounds | qagame/cgame sorted core/events | capability-gated `nhs` transport and client assets only | generic damage producer removed after review: head event requires Sniperwar, team events depend on private protection/award state; producer parity remains pending |
| Simple config and game state | qagame/cgame sorted core | typed `scs`/`#` serializers and client parsers; known base settings synchronized | wire layout + source/build validation; custom gameplay cvars pending |
| Map-end statistics | qagame/cgame sorted core | typed `mes` parser plus LogExit delivery; combat bodyshots derive from hits minus headshots, with native headshot, kill, death and successful-revive counters | original-vs-port gameplay transcript pending |
| Team score transport | qagame/cgame sorted core | capability-gated `tsc` server/client transport | source/build validation |
| Objective events | qagame/cgame sorted core | typed `ob` transport and client presentation; checkpoints, dynamite plant/defuse, OID destruction/damage, single-stage construction, and staged constructible damage/destruction hooked | runtime transcript pending |
| Charge times | qagame/cgame sorted core | qagame/cgame adapters; initial, Cvar-change and scripted-factor update paths | protocol tests pending |
| Skill-level snapshot | qagame `nitrox_SendSkillLevels`, cgame `CG_UpdateSkills` | seven named Cvar strings resolved from i386 symbols; isolated typed 7x6 threshold parser and binary initial values | executable parser tests; not activated: Nitmod has six levels versus native ET's five, requiring coordinated XP/UI/state changes |
| Admin, database, Lua, anti-cheat | qagame sorted modules | not yet ported | pending function inventory |
| HUD, stats, objectives, scoreboards | cgame sorted modules | not yet ported | pending function inventory |
| Nitmod UI | ui sorted modules | Nitmod and asynchronous `sv_NxAC` browser filters reconstructed; existing menus bind both cvars | browser runtime transcript pending |

The complete CMake source manifests for cgame, qagame and ui compile on the
current Windows host. This establishes source/header integration only; it is
not evidence of Linux-i386 ABI, original-binary parity, or WASM loading.

`status` is deliberately feature-oriented. A recovered function is not marked
ported until it has a typed implementation and at least one of: an instruction
comparison, a protocol transcript, or a deterministic behavior test.

The confirmed `scs` and `#` argument ordering is recorded in
[`protocol-reference.md`](protocol-reference.md).  This prevents later gameplay
ports from silently changing the client/server contract.

The per-path reference and evidence ledger is in
[`parity-matrix.md`](parity-matrix.md).
