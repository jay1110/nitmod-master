# Nitmod parity matrix

This matrix records evidence for code reconstructed from the supplied i386
reference modules. `Build` means that all three source modules compile from
the current tree; it does **not** claim i386 ABI or byte parity.

| Area | Reference location | Product path | Evidence | Remaining difference |
| --- | --- | --- | --- | --- |
| Original TAGCONNECT selection | original CG_ParseTagConnects 0x309..0x348 | NITMOD_TagConnectBase and startup/update routing | reference/original-tagconnect-layout.md; three layout fixtures, endpoint/decoy/update cases | original gamestate not captured remotely; other ranges and engine rendering pending |
| Original-server tsc reception | original CG_ServerCommand t/s/c branch | typed team-score parser and dispatch | reference/original-team-score-reception.md; no-handshake full-source cases | score-change timing/direction presentation and browser session parity pending |
| Original-server ct reception | original cgame command dispatch | cg_servercmds.c, existing typed charge parser | no-handshake full-source fixture; ten fields and malformed atomicity | original full-session/browser parity pending; no other gates removed |
| Map-load compatibility | original UI bitflag and native fireteam strings | config store and shared UI; no asset workaround | reference/map-load-compatibility.md; parser/input/paint and store tests | original PK3 compatibility required; poison weapons, referee-menu parsing and original-server browser gameplay pending |
| Named trigger cached lookup | original G_ScriptAction_Trigger ordinary-name branch | G_ScriptAction_Trigger | 32 actual script-dispatch cases and pinned hash/search/bot-flag instructions; reference/named-trigger-hash-lookup.md | special targets and original/browser gameplay parity not certified |
| globalaccum trigger_if_equal lookup | original global branch 0xb28a0 onward | G_ScriptAction_GlobalAccum | reference/globalaccum-trigger-hash-lookup.md; 16 global/16 local script scenarios and pinned original calls | other globalaccum commands and original/browser runtime parity not certified |
| WASM VM ABI declaration/signature | local ET:Legacy VM_WASM_ABI_EXPORT and VM_EntryPoint_t | shared syscall adapters and WASM-only qagame vmMain tail | three real side modules loaded; marker return checked and thirteen-slot calls passed; reference/wasm-vm-abi.md | browser deployment and gameplay unverified; native signature unchanged |
| accum trigger_if_equal lookup | original local accum branch 0xb2335 onward | G_ScriptAction_Accum | 16 full-source dispatch/yield scenarios; reference/accum-trigger-hash-lookup.md | other accum behavior/globalaccum and real engine parity unverified |
| Tag attachment hash fallback | original 0xb2fd0 | G_ScriptAction_TagConnect | 8 full-source tag/configstring scenarios; reference/tag-connect-hash-lookup.md | client renderer, malformed fatal paths and full runtime parity not newly verified |
| Script-trigger cached lookup | original 0xd8130 | target_script_trigger_use | 10 full-source scenarios; reference/script-trigger-hash-lookup.md | other callers and actual engine runtime parity remain pending |
| Cached-name searches | original 0x10e820/0x10e890 | G_NITMOD_FindByClassNameHash / G_NITMOD_FindByScriptNameHash | all slots and three hash values; reference/cached-name-search.md | invalid input guards differ defensively; original caller migration pending |
| Target/script-name hashes | original spawn alias and set field stores | G_NITMOD_InitSpawnNameHashes / script set | 45 initialization cases, repeated script keys and no-alias update; reference/target-script-name-hashes.md | original lookup consumers and G_ModifyTOI remain unported |
| Script set classname handling | original 0xb61a0 | etpro_ScriptAction_SetValues | 16 real-parser scenarios; cache checked at link boundary; reference/script-classname-cache.md | target/scriptname caches and G_ModifyTOI not reconstructed; full script/gameplay parity unverified |
| Bot world AABB | original 0x2248f0 | G_NITMOD_BotEntityWorldAABB | 72 profiles; reference/bot-world-aabb.md; pinned original-handle fallback | script cache lifecycle, virtual override dispatch, x87/aliasing and loaded interface pending |
| Team-item cache lifecycle | original 0x72c06/1d and 0xccbf6/0xccc1b | typed helper in G_CallSpawn and LaunchItem (also native Drop_Item) | pinned original records; exhaustive helper and real spawn-rejection tests; reference/team-item-classname-cache.md | LaunchItem ordering source-checked only; script cache writers pending |
| Map-spawn cache and local AABB adapter | original 0x5c0 cache lifecycle subset | nitmodClassnameHash, post-spawn refresh, G_NITMOD_BotEntityLocalAABB | reference/bot-classname-cache.md; case/null/empty, init retention, free and selected-target cache tests | dynamic item/script cache writers remain unported; no loaded C++ interface |
| Bot construction/local bounds stages | original 0x223ca0, 0x88ec0, 0xcd219 | G_NITMOD_BotBoundsEntity / G_NITMOD_BotLocalBounds | 256 selection and 14 cache-sensitive bounds cases; reference/bot-aabb-stages.md | internal stages only; cached hash lifecycle and complete world/local adapters pending |
| Bot oriented world bounds | original 0x223b20 | G_NITMOD_BotEntityWorldOBB | 48 full-source profiles; original control flow and subtraction pinned; reference/bot-world-obb.md | defensive null checks; x87/aliasing parity and installed C++ interface pending |
| Bot eye/bone positions | original 0x224750/0x2245d0 | G_NITMOD_BotEntityEyePosition / G_NITMOD_BotEntityBonePosition | 60 valid profiles plus invalid handles; reference/bot-eye-bone-position.md | concrete class semantics only; custom virtual overrides, x87 bit parity and installed interface pending |
| Bot entity orientation | original 0x2240e0, AngleVectors 0xfeda0 | G_NITMOD_BotEntityOrientation | 192 profiles; native viewangles offset check; reference/bot-entity-orientation.md | arbitrary-angle x87 bit parity and installed C++ interface pending |
| Bot entity velocity | original 0x224010; oldOrigin writes 0x7ea13/29/3b | G_NITMOD_BotEntityVelocity | 24 full-source profiles plus handle errors; reference/bot-entity-velocity.md | null-output defense; x87 extreme-value parity and installed C++ vtable pending |
| Bot entity position | original 0x223ec0 | G_NITMOD_BotEntityPosition | 48 full-source geometry profiles; original instruction/constant checks; reference/bot-entity-position.md | defensive null-output rejection; double vs x87 arithmetic; no installed C++ vtable |
| Bot time and entity lookup methods | original 0x2220d0/0x224e00/0x223900/0x2238c0 | typed C adapters, no C++ shim | all slots/lifecycle states and world exception tested; pinned instructions | malformed inputs reject defensively; library vtable/ABI not connected |
| Bot engine virtual method order | original ETInterface relocation table | schema-2 loader report/extractor | all 55 slots resolved and code-hashed, wrong relocation rejected; 83 tests | order/symbol evidence only; return types/struct ABI and runtime adapters unfinished |
| Bot loader ABI prerequisites | original 0x21f430/0x22a090 | tools/extract_bot_loader.py | exact version/size/string operands, altered-artifact rejection; host build/83 tests | forensic evidence only; export signatures and C++ engine interface incomplete; no runtime compatibility claim |
| Runtime bot serial maintenance | original reset 0x812de and deletion 0xe71f5 | g_nitmod_bot_entities.c, GAME_INIT and free hooks | serial invalidation/neverFree/reuse integration; original calls and source hook order pinned | no loaded-interface event or smoke-cache cleanup; full init/browser runtime untested |
| Entity free ordering prerequisite | original G_FreeEntity 0xe71f5/0xe7292/0xe7297 | full-source callback/unlink/neverFree/reuse fixture | four profiles, whole-object preservation/clearing and spawnCount reuse checks | bot table/events not connected; populated registry and engine replay unverified |
| Bot serial lifecycle primitives | original 0x21f415 and 0x221956 | isolated typed table reset/increment | original bytes, exhaustive serial/flag tests, reserved/neighbor preservation | no runtime table ownership, event dispatch or smoke-cache cleanup; original wrap aliases retained |
| Bot entity handle representation | original two-half stores and serial/world resolution | isolated nitmod_bot_handle.c/.h | all 65536 serials/index bit patterns, stale/inuse/world cases, pinned bytes | defensive invalid-index rejection; no lifetime table, C++ ABI replacement or event delivery |
| Mine filter composition | current full-source G_LandmineThink | controlled engine query with actual typed filters/trigger | 16 profiles verify candidate fallback and complete state/link boundary; native build/81 tests | no collision/original replay; Bot_Event_PreTriggerMine requires missing handle codec and loaded interface |
| Bot mine trigger exclusions | original G_LandmineThink 0x8ac87 | initial-trigger typed bot filter | 2048 cases; original registration/instruction checks; native/WASM builds and 81 tests | no pretrigger event delivery or full Omni-bot/gameplay parity |
| Mine owner/pliers exception | original G_LandmineThink 0x8ac60/0x8ade0 and BG_RegisterWeapon path | typed bit-0x100 filter in existing initial-trigger policy | 12288 cases including deliberate entityState/playerState weapon mismatch; original mask/identity checks | isolated policy and source hook only; bot callbacks/filters and engine replay pending |
| Mine initial-trigger team filter | original G_LandmineThink 0x8ad17/0x8af54 | typed bit-0x20 filter with parent/clientNum owner exception | 4096 cases, native offset assertion, original bytes and caller-hook checks | other owner/bot rules and live candidate-query replay pending; not full caller parity |
| Precise mine contact | original sEntWillTriggerMine ELF 0x8e180 | typed helper and original-default Cvar registration | latch/eFlags fallback, truncation-equivalent open bounds, 400 policy cases; native/WASM builds, 81 tests | extreme-coordinate x87, other caller rules and original/browser gameplay parity unverified |
| Landmine latched trigger state | original field 0xfc store/read, compiled onFireStart offset | typed s.onFireStart assignment after linking/timestamp | 36 whole-entity transition profiles, original bytes, 60-row compiled layout match | precise contact policy remains unported; no original/browser gameplay parity |
| Landmine trigger contents | original ELF LandMineTrigger 0x8de70 | game/g_missile.c | BODY correction; 12 real trigger/post-trigger profiles check link ordering, timestamps and 100/300ms timers | extra field 0xfc and private weapon 0x33 omitted; no original-engine collision/visibility parity |
| Landmine/satchel initial contents | original fire_grenade ELF 0x8f12d/0x8ee09 | native WP_LANDMINE/WP_SATCHEL spawn branches | BODY assignments corrected, exact instruction pairs pinned; baseline damage/registry/snapshot hooks retained; native/WASM builds and 80 tests pass | source/instruction checks only; no live spawn/collision/arming or browser parity |
| Dynamite initial contents | original ELF 0x8f246..0x8f256 | native fire_grenade WP_DYNAMITE branch | BODY field assignment corrected; original instruction bytes pinned, native/WASM builds and 80 tests pass | source/instruction evidence only; engine collision/settling/arming and full spawn parity pending |
| Delayed secondary destruction | current typed radius damage and ported WeaponDie | full-source smoke-secondary fixture | 720 profiles; 20 clear chains, blocked cases, deferred once-only event/link, primary/owner byte preservation | zero-splash secondary only; no multi-hop/player/original/browser parity; production unchanged |
| Splash victims and visibility gates | typed ET radius and CanDamage paths | full-source native fixture with deterministic candidates/traces | 480 profiles, 80 explosions; 75-point non-client damage, boundary/source exclusions, blocked rays and satchel pass filtering | synthetic collision responses, no player/near-wall/original/browser parity; production unchanged |
| Weapon-specific explosion integration | current typed ET grenade/smoke/marker/satchel paths | full-source fixture with real weapon identities and empty splash query results | 240 profiles/40 explosions; shake allocation/strength, Axis/Allies counters, trace bounds/order and satchel link restoration | no real victim/occlusion, engine linking/rendering, original binary or browser gameplay comparison; production unchanged |
| Common delayed explosion transition | current G_RunThink/G_ExplodeMissile | native full-source no-splash fixture | deadline/event/state/link-request/duplicate suppression verified; 80/80 tests | weapon id 0, no radius/shake/world-link simulation or original/browser gameplay comparison |
| Projectile admission-gate behavior | current G_Damage visibility/construction/intermission/warmup checks | full-source native integration matrix | 96 profiles/192 hits, exact blocked-state preservation even with DAMAGE_NO_PROTECTION; 80/80 tests | world attacker fixture only, not original-engine/team-protection or WASM gameplay comparison |
| Damage-to-handler integration | current qagame G_Damage and G_AddEvent | complete-source native executable, rejecting engine callbacks | 39+1 damage threshold, schedules and satchel playerState event verified across eight profiles; 80/80 tests | native host fixture only; no scheduled explosion, physics, WASM or original-engine parity run |
| Airstrike-marker shootability | original mask 4 case 0x15 (not bomb case 0x30) | dedicated marker configuration hook | 40 HP/bounds/delayed-death selection, 768 combined mask cases, 79/79 tests | original registry/kicking and complete airstrike damage-chain parity remain unverified |
| Hand-grenade shootability | original grenade spawn mask 1 | both native hand-grenade spawn branches use typed 40-HP/bounds/death setup | independent smoke/grenade masks checked across 512 cases; native/WASM builds, 79/79 tests | baseline damage/radius retained; no rifle-grenade/marker activation or engine gameplay replay |
| Smoke-bomb shootability/death | original smoke spawn mask 8 and Nit_WeapDie ELF 0x89390 | g_nitmod_weapon_damage.c and spawn hook | 40 HP, original bounds, no owner changes, 256 masks/8 death cases; 79/79 tests | null guard defensive; original-engine collision/damage/replay not yet tested |
| Satchel damage spawn gate | original Cvar table and mask 0x2 spawn branch | g_damageweapons registration and G_NITMOD_ConfigureSatchelDamage | 40 HP/damageable/callback only when enabled; 256 masks and 32 handler cases; hash-pinned registration | other masks not implemented; live damage-chain and gameplay replay not performed |
| Satchel damage-death semantics | Nit_SatchelDie ELF 0x8a5f0 | separate typed handler, not spawn-activated | scheduled explosion, inventory/event order, timer wrap; 32 cases and 78/78 tests | g_damageweapons mask 0x2 gate unported; defensive owner guards; no gameplay parity claim |
| Satchel-free inventory/event behavior | original G_FreeSatchel 0x8a570 | separate typed release callback linked in both build manifests | three inventory writes, no event, 600 state cases; native/WASM builds and 77/77 tests | null/index safety guards deliberately added; no complete original private-layout or gameplay replay proof |
| HQ mine proximity warning sweep | ELF 0x8dbe0, constant-zero epilogue and conditional warning caller | typed standalone G_SweepForLandmines adapter | exact box/capacity/callback/false tests across 80 cases; native and WASM build | native caller timing gates retained; no gameplay replay or exhaustive floating-point equivalence |
| Typed Cvar output consumption | actual qagame G_CVAR_UPDATE pointer and memorydump branch | --cvar-probe with strict callback sequence | real WASM branch changes after typed write; 75/75 host tests | pre-init engine double only, integer consumption demonstrated; no registry/initialization/browser parity |
| Snapshot and initialization-buffer layout | snapshot_t, gameState_t, vmCvar_t in both source trees | compiled layout audit schema 2 | all named fields in these three additional structures match, including snapshot entity capacity; 75/75 host tests | no snapshot transfer, engine binary extraction, serialization or gameplay verification |
| Shared wasm32 layout sample | actual headers compiled in separate probes | run_wasm_layout_audit.py | three aggregate sizes and 28 field offset/size pairs match in real WASM runs | incomplete field coverage, build flags/serialization/semantics and existing engine binary remain unverified |
| cgame unsupported-extension boundary | actual cgame vmMain default and local engine gates | isolated command-1338 error-callback probe | real CG_ERROR with exact formatted string, 74/74 host tests | no extension implementation, engine error recovery or browser lifecycle verification |
| vmMain command numbering | local engine/module export headers | bidirectional export-number audit | 39 shared command numbers match, no cross-name slot collisions; 74/74 host tests | four engine-only extensions remain unsupported; source comparison is not runtime/argument/gating parity |
| Missing Botlib syscall reachability | compiled BOTAI_START_FRAME dispatch | --botlib-probe diagnostic stops at BOTLIB_START_FRAME | actual syscall 205 reached after seven Cvar updates, with zero time bits | direct pre-init probe only; default startup/engine scheduling, real Botlib and original parity unverified |
| Engine import numbering | local Legacy and ET 2.60 import headers | audit_engine_syscall_numbers.py | 333 shared entries match numerically; no shifted common names; four parser/classifier tests | 147 qagame names absent, mostly old Botlib; no dispatcher/reachability/layout/runtime verification |
| WASM syscall transport correction | actual web engine source expects intptr_t array, not variadic callback | nitmod_syscall_abi.h shared by cgame/qagame/ui; native branch unchanged | real rebuild, array packing and qagame/UI round trips, host build and 73/73 tests | engine enums/layouts, cgame callbacks and browser/gameplay still require validation |
| WASM argv callback ABI smoke | G_ARGV and UI_ARGV adapters in compiled modules | scoped console probes with checked variadic callback and bounded buffer output | qagame unknown-command and UI ui_cdkey return values pass individually and concurrently | harness callback only, not Legacy engine syscall implementation; no cgame callback or gameplay coverage |
| WASM typed entrypoint calls | qagame eight-int and cgame/ui thirteen-int vmMain definitions | test_wasm_entrypoints.c via --entrypoints smoke mode | six dllEntry and fourteen checked vmMain calls across individual/concurrent runs; 73/73 host tests | no syscall callback invocation, game initialization, engine/browser or original behavioral parity |
| Actual WASM loader smoke | built cgame/qagame/ui side modules | run_wasm_load_smoke.py and shared loader harness | real SDK/Node instantiation and entrypoint lookups, simultaneous loading and missing-file rejection | fresh broad MAIN_MODULE runtime, not actual engine/browser; syscall and gameplay parity unverified |
| WASM import providers | actual modules and local Legacy etl.wasm/etl.js | audit_wasm_imports.cjs, no Legacy source changes | 91 imports classified; input hashes and counts in wasm-import-audit.md; 72/72 host tests | name/kind and textual JS candidates only, not signature/relocation/syscall/browser parity |
| Actual WASM compilation and binary validation | src_2.60 and local Emscripten 4.0.23 | three Debug side modules, shared revive signature fixed, fatal linker warnings | real build and Node WebAssembly.Module validation; exports/hash/size/import counts in wasm-first-build.md; 71/71 host tests | imports not instantiated against engine, no browser/gameplay/bridge verification; not a completed Nitmod release |
| WASM build orchestration | side-module targets and output contract | SDK preflight, explicit three-target Debug build, post-build artifact rechecks | command/failure fixtures and each missing/wrong-output test; 71/71 host tests | actual compiler not run: emcmake/emcc unavailable; browser/ABI/gameplay validation pending |
| WASM artifact framing/export gate | core binary sections and dynamic-link marker | verify_wasm_module.py on all WASM target post-link steps | positive/minimal fixtures and malformed-format tests; 70/70 host tests | not a full validator of instructions, indices, imports or metadata contents; real compiler/browser verification pending |
| WASM link/export setup | local Legacy side-module build reference only | CMake shared support and NITMOD_MODULE_EXPORT on vmMain/dllEntry | six definition checks, conditional macro and CMake source contracts; 69/69 host tests | actual Emscripten output, import compatibility and browser integration remain unverified |
| Build verification record | original SHA-256 manifest and built artifacts | post-validation unique JSON with hashes and explicit full_parity_verified=false | success fixture and no-report-on-build/export/reference-failure tests; actual originals rehashed | real Linux build still unavailable; record is not ABI/gameplay/release certification |
| Linux load-smoke infrastructure | native dynamic module loading | compiler-matched dlopen/dlsym/dlclose test and host-testable orchestration | host tests cover failed opens/lookups/closes and reverse cleanup; 68/68 host CTests | Linux adapter/module load still unexecuted; no engine entrypoint invocation or gameplay parity claim |
| Linux-i386 toolchain identity | target/data-model contract | strict opt-in configure checks and compiler macro/size probe, enabled by container | seven CMake policy fixtures pass; host build and 67/67 tests | successful Linux compilation/probe remains blocked; no full ABI or behavior parity claim |
| Native link/export validation | vmMain/dllEntry entrypoint contract | Linux-only strict linking plus readelf dynamic-export validation | parser rejection fixtures and all three original modules verified; 67/67 host tests | reconstructed Linux link not run; visibility checks do not certify full ABI/calling convention or gameplay parity |
| Linux-i386 build orchestration | release workflow requirements | tracked container recipe, all-target build/test driver, output header checks | host tests verify sequence, each stage failure and wrong/missing artifacts; 67/67 CTests | Linux compiler not executed: Docker unavailable, WSL virtualization error; header checks are not full ABI/export parity |
| Full/overfull begin-to-finish integration | native begin, transition stage and main-first transfer | expanded TestOuterClipGate | 7776 scenarios: 5472 completions and 2304 rejected outer requests; ammo conservation and exact event/state checks | explicit timer expiry and native capacities; not original scheduler/ELF or Linux/WASM verification |
| Reviewed light-weapon full-magazine gating | original begin bodies versus outer request capacity test | NITMOD_ReloadUsesOuterClipGate, shared native begin | 216 direct/outer inventory cases plus state/scoped-return regressions | twelve-identity migration only; other native gates and definition/ability integration remain pending; no original/platform replay |
| Akimbo shoot/reload consumption integration | current typed product functions | TestAkimboShootReloadCycles | 1944 two-drain-cycle scenarios, per-shot hand oracle, ammo conservation and one reload event | admitted consumption calls and explicit timer expiry, not full firing scheduler/original replay; refill rules and release remain open |
| Active firing-clip integration | existing native consumers and reviewed akimbo sequence | shared PM_WeaponFiringClip | 4224 actual availability/consumption cases; independent parity oracle, one-slot changes and state preservation | native aliases/sentinels retained; refill settings/fire admission and original/platform replay pending |
| Drop/raise timer addition | original drop/raise 32-bit ADD in both modules | NITMOD_AddWeaponTime32 used by both weapon-change phases | 504 native boundary executions with independent modulo oracle and whole-state checks | direct phase tests, not full scheduler/original replay; other timer sites and platform release remain open |
| READY reload timer arithmetic | original 32-bit ADD qagame 0x288a0 / cgame 0x17db0 | NITMOD_AddReloadTime32 and active begin | 98 READY boundary cases within 294 begin executions; independent modulo oracle and whole-state checks | isolated hardened API intentionally still rejects overflow; other timer sites and platform release remain unverified |
| Firing reload timer overlap | original compare/store qagame 0x288d0..0x288d8 / cgame 0x17de0..0x17de8 | PM_BeginWeaponReload direct assignment | 196 signed-boundary executions with state/event isolation; removes undefined intermediate subtraction | READY addition unchanged; no sanitizer/original-ELF or platform release proof |
| Shared reload animation selector | original cgame 0x17df0 and following; existing native/recovered selectors | NITMOD_ReloadAnimation with both callers | 468 mapping and native-wrapper checks; existing animation-gate tests; no engine dependency | eligibility sources deliberately remain separate; full original playback and release parity pending |
| Transition completion boundaries | native stage delay/time and completion behavior | TestTransitionTimerBoundaries | 3168 cases with independent timer signs, animation suppression, held keys and event-ring preservation | native inventory regression, adrenaline alias retained; original replay and platform release not established |
| Multi-phase transition integration | current PM_Weapon delay/request/timer/finish ordering | extracted PM_ProcessWeaponTransitions called in original position | 64 complete stage cycles with repeated held input, scope return, attempted switch and final inventory/event checks | tests expire timers explicitly; full PM_Weapon firing/time advancement and original engine execution not covered; see reference/weapon-transition-cycles.md |
| Active alternate-key reload input | original wbuttons bits 8/1 and separate preference, both original outer reload functions | NITMOD_ManualReloadRequested and shared PM_CheckForReload | 6336 whole-state input equivalence scenarios; existing preference codec and capability source contracts | no full scheduler/network/original-ELF replay; native ability and other reload policies retained; see reference/weapon-alt-reload-input-active.md |
| Active akimbo either-hand reload | qagame 0x2a9e8..0x2aa38, cgame 0x19ec8..0x19f18 and original begin bodies | bg_pmove.c mapped-akimbo exception to legacy full-magazine guard | red/green reproduced defect; 1296 request/complete-cycle scenarios, reserve sharing and event isolation | other weapons keep legacy guard; native capacities and full engine/platform parity remain separate; see reference/weapon-akimbo-reload-active.md |
| Active reload while leaning | complete qagame 0x28730..0x28a4f and cgame 0x17c40..0x17f5f begin bodies | shared bg_pmove.c, mapped-eligibility fallback | 4212 native differential comparisons plus updated state/scoped-cycle expectations; source fallback contract | native inventory/definition/ability differences retained; no original ELF or full movement replay; see reference/weapon-reload-lean-active.md |
| Native reload completion integration | product finish/recursive transfer/idle source | test_nitmod_weapon_change.c and generated verbatim bodies | 6336 completion cases, 840 extended complete reload cycles; bytewise state and no-extra-event checks | tests native aliases/defaults, not complete original Nitmod parity; scheduler/original ELF and release validation pending |
| Active fast-reload rounding | original factor 0x3f266666, x87 multiply then truncate | NITMOD_ScaleFastReloadDuration in bg_pmove.c and recovered duration helper | 840 native begin cases, signed boundaries and existing exhaustive arithmetic tests | native skill eligibility intentionally retained; original ability integration and engine/platform replay pending |
| Active reload body-event exceptions | original skip IDs 4/9/15/28/48/49/50 | NITMOD_ReloadBodyEventRequired, native begin and recovered feedback adapter | both 47-entry tables pinned; 168 native begin cases including model-free exceptions and landmine control | only mapped tripmine changes native behavior; model playback, remaining reload gates and platform parity pending |
| Empty-current-reserve begin reset | qagame 0x28796..0x287f8 / cgame 0x17ca6..0x17d08 | bg_pmove.c, NITMOD_ResetReloadWithoutReserve | 2400 actual begin ordering/state cases plus helper boundaries; current native/recovered alias agreement required | adrenaline/unmapped identities intentionally not enabled; remaining reload and platform parity pending |
| Active alternate-fire begin-reload gate | qagame 0x28756..0x28766 / cgame 0x17c66..0x17c76 | bg_pmove.c shared PM_BeginWeaponReload | 288 real direct/PM_CheckForReload cases; both firing enums, native blockers and event/timing checks | only state gate corrected; remaining native reload restrictions/defaults not full Nitmod parity; engine replay pending |
| Raise completion / reload-intent handoff | qagame 0x2bd39 and 0x2bd55; cgame 0x1b21b and 0x1b237 | bg_pmove.c PM_FinishWeaponRaise and executed integration harness | 144 phase cycles with real native reload entry, timer and duplicate-call guards; READY-before-call verified | native reload restrictions retained, not complete Nitmod reload parity; scheduler and original ELF execution pending |
| Ordinary-switch isolation and mortar late veto | qagame 0x2a2f4 then 0x2a30b; cgame 0x197d4 then 0x197eb | test_nitmod_weapon_change.c | 38128 non-alternate scenarios, 16 water/prone cases; standard timing, untouched inventory/direction, exact late-veto mutation | native regression includes unmapped enum identities without original parity claims; no engine/platform replay |
| Native switch integration execution | product PM_BeginWeaponChange / PM_FinishWeaponChange and dependencies | test_nitmod_weapon_change.c, generated verbatim function header | 576 combined scenarios and guard/ownership/reselection tests, real transfer and event ring | native host source only; original binaries, model scripts, whole PM_Weapon and engine replay not executed |
| MG42/mortar deployment switch | original 1250/1722/1667/1000 raise branches and drop direction sequence | bg_pmove.c, nitmod_weapon_reload.c | four typed transitions, 2704 pair plans, eight hash-pinned immediates and guarded native-axis construction | ET-equivalent extraction; placement/movement and numerical engine replay proof pending |
| Rifle-grenade switch phases / mode | drop 0x2a61c/0x19afc; return magazine read 0x2c87d/0x1bd3d; attach 0x2c959/0x1be19 | bg_pmove.c, nitmod_weapon_reload.c | 45000 pair/magazine/reserve cases and 468 mode checks; read-only plans and active consumer order | native clip transfer remains separate; engine replay and platform release proof pending |
| Single-pistol silencer timing/mode | alternate IDs 2/14 and 7/38, both original modules' drop/raise branches | bg_pmove.c, nitmod_weapon_reload.c | four typed transitions; 2704 pair plans and 572 remembered-bit cases; live consumer/order contracts | body/first-person engine replay pending; no akimbo inference or protocol change |
| Scope-switch durations / alternate identity table | weapAlts 0x2a5300 / 0x12e660; original drop tables and raise branches | bg_pmove.c, nitmod_weapon_reload.c, extract_weapon_switch.py | all 44 reviewed native alternates match both modules; six directed timings and 2500 pair lookups; dispatch-table checks | behavior-preserving live extraction; non-scope switch reconstruction and engine replay pending |
| Active same-weapon raise exceptions | equal-target branches 0x2c6a6/0x2c74e and 0x1bb66/0x1bc0e | bg_pmove.c, nitmod_weapon_reload.c | knife/smoke mapping; 2500 pair cases and 10000 commit/ownership/reload compositions, source-order check | original IDs 48/50 not mapped; engine timing/animation replay still pending |
| Active target/raising commit | original inlined finish qagame 0x2bd93 / cgame 0x1b275 | bg_pmove.c and nitmod_weapon_reload.c | both original control-flow branches, exhaustive native state/target ownership tests and active-call source contract | behavior-preserving extraction; full switch timings, animations and engine replay still pending |
| Active switch-during-reload exclusion | original state mask 0x13 over states 3..7 | bg_pmove.c and nitmod_weapon_reload.c | typed-state predicate tests, native guard-order contract and host build | narrow active parity correction only; full switching/time/animation and engine replay not completed |
| Reload decision dispatcher | PM_CheckForReload reload=true weapon-change call | nitmod_weapon_reload_feedback.c | nine scoped dispatch paths plus missing-callback/invalid/repeated cases; real begin effects and event helper | callback requests only, not successful switch; full native change parity and active Pmove dispatch pending |
| Per-call reload preference input | client cvars/server persistent flags | cg_predict.c, g_active.c, nitmod_weapon_reload.c | shared-policy projection and refresh contracts | mod-local pmove_t expanded, all modules rebuilt; no serialized ABI change or engine E2E claim; gameplay dispatcher pending |
| Live reload preference transport | cg_weapAltReloads / cg_uinfo bit 0x10 | cg_main.c, cg_nitmod_config.c, g_client.c | source contract checks and existing codec tests; all host modules build | new transport-only capability and conservative default 0; passive storage, no recovered gameplay hook; no engine E2E claim |
| Reload preference codec | cg_uinfo bits 0x01/0x10, cvar >0 producer and server bit extraction | nitmod_weapon_reload.c | 3200 encoding cases, 102400 policy comparisons, unrelated-bit preservation | codec only; live cvar/userinfo wiring and runtime weapon-flag overrides not activated |
| Auto-reload preference defaults | original 72-byte ammo record +0x38 in both modules | nitmod_weapon_defaults.c | all 44 executed flags compared with both originals, unchanged-invalid output and 88 policy checks | static defaults only; extra setting/live override binding not activated |
| Reload input/settings predicate | qagame extra setting +0x88 vs cgame +0x80; automatic ammo flag +0x38 | nitmod_weapon_reload.c | 6912 input combinations, unchanged contexts and downstream decision checks | explicit extra inputs; defaults/settings synchronization and active dispatch pending |
| Outer reload/scoped decision | PM_CheckForReload scoped/manual and ordinary timer branches | nitmod_weapon_reload.c | 28512 cases across request, inventory, timing, scoped ability and war modes | pure decision; request/settings resolution, unscope dispatch and live ability integration pending |
| Composed reload begin | PM_BeginWeaponReload body-event exclusions, prone selection and effect order | nitmod_weapon_reload_feedback.c | 176 current implementation composition cases, typed script-event dispatch and retained torso effect | animation system mocked at boundary; real model/replay and outer reload policy/live abilities pending |
| Reload start first-person feedback | PM_BeginWeaponReload current animation / target mortar suppression / event 0x1c | nitmod_weapon_reload_feedback.c | 4224 cases with real native predictable-event helper and full-state comparisons | no body-script animation or active hook; timing validated before effects; invalid event-sequence hardening |
| Reload completion | PM_Weapon transfer/ready/idle branch in both modules | nitmod_weapon_reload.c | 3168 cases, six IDLE2 identities, animation gates/toggle and context immutability | opt-in only; start event/animations, outer gameplay checks and live integration pending |
| Fast reload duration | binary32 factor 0x3f266666, x87 truncation and eight-weapon predicate | nitmod_weapon_reload.c | 352352 cases, original factor bytes, 20-to-12 edge and timing integration | exact-product truncation; changed x87 precision mode not emulated; live abilities/events/animations pending |
| Reload state gate and timer effects | PM_AltFire branch establishes original 5/6; PM_BeginWeaponReload stores 7 after timer update | nitmod_weapon_reload.c | 420 timer boundary combinations, 36 reserve/state combinations and whole-state comparisons | native enums used; negative-duration/overflow hardening; duration scaling and engine effects pending |
| Begin-reload inventory sequence | qagame 0x28782..0x287f2; cgame 0x17c92..0x17d02 | nitmod_weapon_reload.c | 46464 current/target inventory cases, empty-reserve precedence and translated range checks | result only; accepted original state mapping, ready reset and animation/event/timing effects remain pending |
| Midclip restriction and MG42 override | PM_BeginWeaponReload MG42 branches before noMidclipReload | nitmod_weapon_reload.c | 95744 state/option/ability cases; source-to-registry-to-consumer tests | partial gate only; live ability binding, state/range eligibility and events remain pending |
| noMidclipReload definition flag | BG_RW_ParseDefinition +0x5fc qagame 0x35b1e / cgame 0x2620e | nitmod_weapon_definition.c and g_nitmod_weapon_registry.c | real source adapter/registry tests, bare-token semantics, default zero and atomic rollback | data path only; MG42 ability exception and complete begin-reload policy not activated |
| Reload request inventory predicate | PM_CheckForReload qagame 0x2a7a0 / cgame 0x19c80 | nitmod_weapon_reload.c | manual/automatic predicates across 17068 states, no mutation | inventory only; not a complete permission gate; state IDs, scoped switching, settings and noMidclipReload integration pending |
| Recovered reload transfer | PM_ReloadClip qagame 0x12bf0 / cgame 0xa500 | nitmod_weapon_reload.c | 11560 single-weapon and 5508 akimbo cases, whole-state checks and overflow rollback | opt-in transfer only; invalid-state atomic rejection is hardening; reload timing/events and active prediction pending |
| Recovered inventory slots and selector | qagame 0x2a59a0; cgame 0x12ed00 and BG_FindClipForWeapon 0x106e0 | nitmod_weapon_inventory.c | 44 executed slot mappings match both hash-pinned originals; 1156 akimbo pairs and 289 independent adrenaline/syringe pairs | opt-in only; native lookup unchanged; no active prediction, reserve-mode, pickup or reload integration |
| Adrenaline spawn versus upgrade | class-tool grant ELF 0x480b0, wrapper 0x49f60 | g_nitmod_adrenaline_grant.c | loaded-default variation, 286720 spawn combinations, registry-to-grant test and overflow rollback | isolated effect; complete tools, bot API and active alias consumers pending |
| Adrenaline upgrade grant effect | G_UpgradeSkill and AddWeaponToPlayer bonus branch ELF 0x49ed0 | g_nitmod_adrenaline_grant.c | eligibility/options/war combinations, whole-client mutation boundary and no cumulative bonus | isolated effect only; native syringe aliases unchanged; active callers and bot notification omitted pending full integration |
| Ammo/clip item aliases | original item +0x30/+0x34, first-match lookup | extract_weapon_items.py and actual native bg_misc diagnostic | 43 matching pairs; real-native-table selector/consumer tests across 1156 akimbo pairs | adrenaline uses its own original slots but native syringe slots; difference retained and explicitly tested, not declared parity |
| Akimbo helpers/clip adapter | BG_AkimboFireSequence ELF 0x21240; sidearm map ELF 0x22dfa0 | nitmod_weapon_akimbo.c, nitmod_weapon_clip.c | actual helpers, 1156 clip pairs, parity bounds and selected-slot refill tests | native helper split preserves behavior with defined overflow-safe parity; aliases mocked for adapter tests; new consumption not gameplay-active |
| Consumption/exact-zero refill | PM_WeaponUseAmmo ELF 0x2aa40 | nitmod_weapon_consumption.c | full-state mutation checks over 20580 combinations plus limits/errors | caller resolves clip and supplies configuration; negative/overspent clips rejected; no live Cvar, akimbo or gameplay integration |
| Ammo baseline subset | qagame ammoTableMP ELF 0x2a69a0; uses consumer ELF 0x2cc30 | nitmod_weapon_defaults.c | 440 values compared with original bytes, all native IDs/consumption and explicit-default registry loading tested | native mod retained, private weapons excluded; state-specific consumption and gameplay activation pending; no post-.weap runtime parity claim |
| Weapon subset registration lifecycle | BG_RegisterWeapon ELF 0x363c0 | g_nitmod_weapon_registry.c | cached/no-I/O load, force, reset, retry and whole-registry preservation checks with real parser | caller-owned subset only; failures retain last good state instead of clearing/marking before parsing; no engine initialization hook |
| Recoil source adapter integration | BG_RegisterWeapon/FromWeaponFile recovered selection and resource flow | G_NITMOD_LoadNativeWeaponRecoil | real path/parser/application composition with mocked source syscalls; all outputs preserved on failure, empty-load reset tested | strict recovered subset only; no original engine lexer transcript or global registry lifecycle |
| Custom recoil definition/application | qagame BG_RW_ParseDefinition and PM_Weapon ELF 0x2d3be..0x2d448 | nitmod_weapon_definition.c, nitmod_weapon_recoil.c | both/alternate parser tests; native-state mutation boundary and fixed-time arithmetic checks | not gameplay-active; nonpositive duration rejected; double vs x87/libm precision not bit-parity validated; loader/lifecycle pending |
| Weapon parser signed tokens and bounds | PC_Int_Parse ELF 0x25a10 | nitmod_weapon_definition.c | split INT_MIN, double-sign rejection, all ammo fields, loader rollback and exact depth/read-budget tests | strict decimal conversion instead of engine intvalue coercion; bounded parsing is deliberate hardening |
| Weapon ammo-definition fields | qagame BG_RW_ParseDefinition ELF 0x35320, nine PC_Int_Parse destinations | nitmod_weapon_definition.c, g_nitmod_weapon_definition.c | native ammotable_t member mapping; sentinel-preservation, selection, reusable-token, malformed-input and loader tests | strict nine-field-plus-classes subset; transactional failure instead of partial writes; no global ammo/prediction modification or runtime parity claim |
| Weapon definition filename/section mapping | qagame BG_RegisterWeapon ELF 0x363c0 | nitmod_weapon_paths.c, G_NITMOD_LoadNativeWeaponClassMask | hash-pinned machine operand extraction for 44 typed identities; C lookup and composed loader tests | four private weapons excluded; no full metadata registration or gameplay activation; overlong paths rejected instead of truncated |
| Capability handshake | qagame `nitmod_client.c`, cgame protocol dispatch | `g_cmds.c`, `g_nitmod_config.c`, `cg_nitmod_config.c` | command names and field order recovered; Build | Original did not protect stock clients with this negotiation; the port deliberately does |
| Extended configstrings | qagame `nitmod_core.c` 2688–2821 | `g_nitmod_config.c`, `cg_nitmod_config.c` | 655 slots, 1018-byte payload slots, range layout, source/build | runtime transcript pending |
| Asset index lookup | qagame `nitmod_core.c` 2763–2835; `nitmod_game.c` 22616–22640 | `nitmod_config_index.c`, `g_utils.c`, `g_nitmod_config.c` | executable C cases for case-sensitive lookup, holes, reserved zero, last slot and overflow; host Build | Native configstrings own indices and mirror writes to NCS. Original G_SoundIndex adds 84 for its private sound namespace; native ET consumers require the native index. Only the four recovered asset ranges are accepted |
| NCS cvar changes | qagame `nitmod_core.c` 59–69; cvar update path | `g_main.c`, `g_nitmod_config.c` | recovered change-triggered delivery for the typed 2.60 subset; Build | remaining Nitmod-only cvars await typed gameplay owners |
| NCS engine mirrors | qagame configstring writers | `g_utils.c`, `g_trigger.c`, `g_cmds.c`, `g_fireteams.c`, `g_script_actions.c`, `g_team.c`, `g_nitmod_config.c` | source control-flow comparison, runtime spawn-target updates, map-start engine snapshot; Build | native configstrings are retained for stock compatibility |
| Predicted fall damage | qagame/cgame `nitrox_AddPredictableDamage`; shared pmove call sites | `bg_misc.c`, `bg_pmove.c` | typed `playerState` mapping and four recovered fall tiers; Build | gameplay replay pending |
| Chunked print and spatial sound | qagame `nitmod_core.c` 225–270, 1657–1693 | `g_nitmod_config.c`, native `G_Sound` | recovered print framing/chunking and `EV_GENERAL_SOUND` control flow; Build | print now escapes delimiters; reference's 32-entry temp-entity allocation pool is an internal optimization, not wire behavior |
| Global sounds | qagame `nitmod_core.c` 1255–1280 | `g_nitmod_config.c` | recovered `EV_GLOBAL_SOUND`, sound-index and broadcast fields; Build | reference entity-pool allocation optimization is intentionally left to normal ET temp-entity lifecycle |
| Spree/revive announcements | qagame `nitmod_core.c` 1692–1727; `G_UpdateKillingSpree`; cgame event 101 | `g_combat.c`, `g_nitmod_config.c`, `cg_nitmod_config.c` | recovered actor/detail/type tuple, typed enemy-kill state and 5/10/.../30 thresholds; Build | uses negotiated `nsp` instead of colliding with native `EV_GENERAL_SOUND_VOLUME`; custom death/revive option Cvars and phrase/sound tables pending |
| Hit sounds | qagame `Nit_HitSound`; `nitmod_weapons.c` 1407, 1684–1718; cgame event 99 | `g_nitmod_config.c`, `cg_nitmod_config.c` | transport values team=3/head=4 and client assets; Build | producer NOT ported: head event is scoped to Sniperwar; team branches require private protection/award state. The previous generic G_Damage hook was incorrect and removed |
| Client address cache | qagame `nitmod_core.c` 2436–2588 | `g_client.c`, `g_nitmod_config.c`, `g_local.h` | typed full address, host and port extraction; Build | IPv4-style `host:port` reference behavior; IPv6 needs an explicit future protocol decision |
| NGUID validation | qagame `nitmod_core.c` 1777–1842 | `g_nitmod_config.c` | recovered 33-byte checksum and ASCII-alphanumeric validation; Build | connection-time NGUID enforcement awaits the separate Nitmod identity handshake |
| Charge times | qagame `nitmod_core.c` 1241 and `nitmod_game.c` Cvar paths | `g_nitmod_config.c`, `g_main.c`, `g_script_actions.c` | exact ten-field wire order and source-path comparison; Build | runtime transcript pending |
| Objectives | qagame `nitmod_core.c` 1389; `nitmod_weapons.c`; `nitmod_unknown.c` | `g_weapon.c`, `g_missile.c`, `g_mover.c`, `g_team.c`, `cg_nitmod_config.c` | event tuple and `MOD_*` attribution recovered; Build | player-private objective counters pending |
| Map-end statistics | qagame `nitmod_core.c` 1462; LogExit call site | `g_main.c`, `g_nitmod_config.c`, `g_weapon.c`, `cg_nitmod_config.c` | exact five-field wire order and LogExit placement; native combat hits minus headshots and successful syringe revives; Build | an original-vs-port gameplay transcript is still required |
| Team scores | qagame `nitmod_core.c` 1729 | `g_cmds.c`, `g_nitmod_config.c`, `cg_nitmod_config.c` | exact two-field wire order and score refresh source path; Build | TDM gameplay mode pending |
| Skill-level snapshot | qagame `nitmod_core.c` 2656–2684, original ELF sender 0x10f640 | isolated `nitmod_skills.c/.h` parser, not protocol-active | seven vmCvar string sources resolved; original 7x6 initial matrix inspected; executable parser tests | native ET has five levels; XP/UI/network consumers require coordinated migration |
| UI server filter | ui `ui_ui_misc.c` 6773–7043 | `ui_main.c` | `game=nitmod` comparison plus asynchronous `sv_NxAC` status cache and 0/1/2 semantics; Build | browser runtime transcript pending |
| Reference artifacts | original i386 modules | `reference/original_nitmod_i386.sha256` | `tools/verify_original_modules.ps1` | reconstructed binaries are not byte-identical replacements |

## Required release evidence

The strict mask parser now has an engine source/token adapter with preferred
and fallback paths, atomic output and exactly-once source release. Quoted
braces remain data. Engine-token-double tests cover open/parse failures and
selection; actual engine lexer transcripts and registry/reload handling remain
pending, and unsupported selected attributes still reject explicitly.

A strict engine-tokenized class-mask parser subset now selects both versus
both_altweap, skips balanced client/unselected blocks and commits output only
at a closed weaponDef. Unknown selected attributes reject explicitly; this is
not full weapon-file parsing. Section, truncation and invalid-value tests pass;
engine token adaptation, complete grammar and reload handling remain pending.

The composed pickup adapter now uses real configuration, counts, restriction
and pickup rules with an explicitly supplied class mask. Tests cover STEN,
Medic masks, pickAny/war precedence and targeted heavy denial, with engine
outputs stubbed. Native item handling is unchanged. Loader review confirms
normal/alternate definitions select both/both_altweap, so masks cannot be
recovered safely by a global classes-token search.

Pickup configuration review identifies the per-weapon `classes` parser field
at +0x6ac, zeroed by weapon registration. Its full parser/reload owner remains
unported. g_medics is now registered with original 0/default flags and has a
tested strict bitmask reader. This alone activates no Medic pickup behavior.

The pickup-specific rule helper is reconstructed separately from spawn
restriction rules: war modes are final allowlists, including only base rifles
for mode 3. Explicit weapon-class masks and Medic options follow afterward.
192000 deterministic cases plus DENY/DEFER guards pass. Native pickup is
unchanged pending per-weapon configuration ownership and runtime validation.

The active # snapshot now sources panzerRestriction from team_panzerRestriction,
correcting the earlier heavy-weapon-percentage substitution. Five caps and
g_weapons also map atomically from validated registered values. Wire order and
client parsing are unchanged; malformed input preserves previous snapshot
fields. Field-level and hook tests pass, while engine transcripts are pending.

SetTeam now refreshes the population cache after assigning the new team,
only in its setweapons branch, before its still-native weapon setter. Source
checks pin the placement before ClientBegin; a real policy integration test
shows the different heavy-limit result before/after target-team refresh.
No premature CalculateRanks or global setter replacement was introduced.

The disabled class handler's post-SetTeam branch now uses the typed loadout
transaction. Integration tests link real Cvar parsing, cached/live counts,
policy and latch updates, replacing only engine/notification/publication
boundaries. Accepted/denied repeats, invalid configuration and reset cache
are covered. SetTeam internals are unchanged; command dispatch remains off.

The typed loadout transaction now connects policy/notification with primary
and secondary latch updates and conditional clientinfo publication. Spy tests
cover allow/deny, repeats and invalid input with full-client comparisons.
Evaluation precedes latch writes for atomic failure (a documented original
ordering difference). Native setter replacement remains pending; original
Omni-bot C++ callbacks have no direct native ET bot-AI counterpart.

The original setclass handler is reconstructed in its own C file with typed
native arguments and explicit population refresh before the post-SetTeam
weapon setter. The command remains disabled in dispatch. Spy tests verify
queries, team/latch handling, call ordering and safety rejection; native
loadout tables and weapon setter behavior have not been replaced.

The decision-to-notification wrapper now invokes the gated sender at most
once after a denied, non-silent policy result. Tests use a sender spy to check
target/reason, suppression paths and invalid entity/client ownership without
inventory changes. Native restriction callers remain unchanged; this is not
engine-level end-to-end parity evidence.

Weapon-limit ncp reasons 19..25 now have matching capability-bit-10 gated
server/client transport and the original seven center-print texts. ID bounds
and strict argument parsing intentionally harden the original unchecked
SrvMsgs indexing. Source checks and hash-pinned original text comparison pass;
gameplay producer hookup and engine-level protocol transcripts remain pending.

The read-only server adapter now connects configuration, cached population,
live weapon counts and policy. Integration tests link all real implementations
with Cvar trap doubles. Early war/spectator decisions bypass missing cache;
invalid configuration rejects safely. Native restriction replacement and
message transmission remain pending. Cmd_Team_f's explicit post-SetTeam
refresh is also integrated and pinned by a source hook check.

The explicit two-team population cache is reset at map start and refreshed
after CalculateRanks in Connect/Begin/Disconnect. A cached snapshot reader
preserves stale population versus live weapon-count semantics between refreshes.
Host transition tests and source hook checks pass; bot/team-command refresh
paths and the gameplay restriction consumer remain unconnected.

Eight missing weapon Cvars are now registered at server initialization with
defaults/flags extracted from the original gameCvarTable. All eight flags are
zero and none tracks changes or resets in the original. Existing native
sv_maxclients/heavy restriction/maxPanzers registrations remain untouched.
A hash-pinned ELF test compares registration source against original records;
trap tests check first/repeated registration. No Cvar_Set or gameplay hook
was introduced. Original mirrored-value update timing still needs integration.

The weapon configuration reader is built in CMake and SCons and tested with
engine trap doubles. Eleven existing Cvars are read atomically; missing or
malformed values reject without changes, and no default/registration is
invented by the reader. This deliberately hardens original atoi-like
conversion. Live engine persistence/update tests and activation are pending.

The read-only weapon-policy composition is built in CMake and SCons. It
preserves heavy/panzer/fixed precedence, deployed-heavy exceptions to fixed
caps and the sum of both equipment-qualified rifle families. Tests exercise
50 weapons across three cap scenarios plus 3240 rifle combinations and
boundary/ordering cases without mutating client/entity/input snapshots.
Primary classification is now connected to the composed evaluator using
recovered original class tables (4000 cases), not native ET loadout tables.
An atomic weapon-count adapter now reads ordinary or session-qualified rifle
counts into policy inputs (450 rifle cases, 18 ordinary-pair cases and failure
boundaries). CalculateRanks identifies the two list lengths as connected and
non-spectator respectively. The snapshot now derives teamSize as at original
cache refresh and uses the shorter prefix for weapon counts; this corrects
the earlier isolated rifle helper's connected-length assumption. Different
lengths, connecting clients and spectator fallback are tested. Original cache
refresh timing, configuration and message emission remain unconnected;
native G_IsWeaponDisabled and active G_TeamCount have not been replaced.

STEN eligibility and limit-notification selection are now isolated typed
helpers with 20480 and 4000 deterministic cases respectively. Original
g_weapons byte-offset test maps to integer bit 0x200. Notifications require
class-primary, non-silent and non-limbo state; returned nitmod_cp reasons
are not engine event IDs and are not yet transmitted. Full restriction
composition and gameplay activation remain pending. See
`reference/weapon-restrictions.md` for ELF branch evidence.

Numeric weapon restrictions now have an ordered evaluator for heavy
percentage, panzer minimum team share and fixed caps. Original upward rounding
and the binary 0.01f coefficient are disassembly-confirmed. Exhaustive ordinary
range tests and precedence checks pass. Cvar/team-count/class/notification
integration and unusual x87 edge comparisons remain pending; no gameplay
restriction call site has been switched to the new evaluator.

The rifle-grenade restriction revocation adapter is reconstructed and tested
with native client fields and a publication spy. It intentionally differs from
ordinary drop/pickup, which does not modify the original persistent equipment
flag. Full restriction/guard integration remains pending; neither generic
drop hooks nor a new per-frame inventory inference were introduced. See
`reference/rifle-grenade-protocol.md` for mutation and publication boundaries.

Rifle-grenade status now has active native spawn assignment, server rn output
and cgame reception. Persistence uses a version-1 equipment Cvar per slot,
leaving the old ET session format intact; original Nitmod session strings are
not imported. Missing/invalid versions reset to zero. Typed adapter tests and
source-hook checks pass; runtime transcript, mid-life revocation and the
corresponding limit activation remain pending.

The original rifle-grenade rn field is now recognized in native cgame using
strict signed parsing and neutral defaults. Its token 0x89 is verified against
the original ELF dictionary. Original session position 26 is documented but
not applied to incompatible native persistence. No qagame producer or UI
behavior is enabled; see `reference/rifle-grenade-protocol.md`.

Rifle-grenade counting is reconstructed separately with caller-supplied
equipment flags: base-rifle selected/latched matching, team filtering and
requester exclusion. 450 combinations and boundary cases pass. Original
equipment assignment, revocation, persistence and userinfo accesses are
identified; their coordinated integration remains pending. Active native
rifle-grenade queries are unchanged; see `reference/team-weapon-count.md`.

Ordinary G_TeamCount is actively reconstructed in g_nitmod_teamcount.c using
native client fields and nine original team-equivalent weapon pairs. Existing
heavy-weapon and sentinel queries preserve their counts. The rifle-grenade
private flag/base-rifle branch remains unported and uses native exact-match
behavior; see `reference/team-weapon-count.md`. Typed host tests do not replace
the required original-engine gameplay comparison.

G_IsWeaponDisabled early decisions are recovered in g_nitmod_restrictions.c:
human spectator rejection and mode-specific exemptions in original order.
Explicit DEFER preserves the need for later restrictions instead of assuming
war modes are blanket allowlists. All native weapon/team/bot combinations
across seven mode values are tested. Native gameplay remains unchanged until
the remaining counts/caps/class/notification branches are integrated; see
`reference/weapon-restrictions.md`.

The mode-4 entry transaction is reconstructed in g_nitmod_war.c: guarded
removal, knife selection, EV_NOAMMO and final latch write. Original event
0x19 is mapped from the cgame consumer, not copied into ET's event enum.
Tests verify ordering, repeats and reset. Full mode configuration/lifecycle
and restrictions are not integrated; original-engine/browser replay pending.

G_RemoveWeapons now has a typed native subset: 42 of the original 46 removals,
mapped by ELF item identity instead of copying numeric weapon IDs. Four
Nitmod-only variants remain excluded. All native inventory bits and mutation
boundaries are tested. The war-mode one-shot latch and event mapping are not
integrated; see `reference/weapon-removal.md` for exact remaining scope.

The weapon-check outer guards are now resolved: server-demo marker,
PMF_FOLLOW and entity health. A typed wrapper composes them with adrenaline
revocation and is tested across all 16-bit flag combinations. Demo-client
classification is recovered from connect/userinfo Cvars, not bot status.
Cached marker lifecycle and the full war/restriction paths remain unintegrated;
this does not establish an active ClientThink port or engine replay parity.

The adrenaline-only inventory revocation is reconstructed from the two
ClientThink_checkWeapons branches. Typed tests check 20480 combinations,
repeated calls and class/unlock changes, including that no unrelated client
field changes. This is not a full weapon-restriction port or an active
ClientThink hook; original private guards and runtime evidence remain pending.

Adrenaline eligibility is reconstructed with actual ET class fields and
explicit first-aid unlock/configuration masks. Both original entry points
share the same typed implementation. Numeric skill levels do not substitute
for unlock bits. Tests cover 122880 combinations and 512 clip-option cases;
see `reference/skill-abilities-disassembly.md`. Gameplay call sites, inventory
grant/removal and class-change reconciliation remain pending.

Player score calculation is active through `g_nitmod_score.c`. The original
i386 x87 control-word changes confirm truncation after each ordered XP
addition. Tests cover 823543 combinations against native ET arithmetic in
the exact range, the real client-field adapter and rejection without mutation.
See `reference/skill-score-disassembly.md` for double/x87 precision and invalid
input differences. This does not enable six-level skills or prove engine replay.

Skill rank arithmetic is recovered in `NITMOD_CalculateRank`: sum seven
numeric levels and apply the original ten thresholds, capped at rank 10.
All 279936 valid input combinations are covered; a separate test compares
compiled results to the hash-pinned original ELF table. The unused eleventh
table entry is explicitly excluded based on both original functions'
disassembly. See `reference/skill-rank-disassembly.md`. Active session and
upgrade routines retain native ET behavior until coordinated integration;
Lua, ability changes and gameplay replay are not claimed complete.

`NITMOD_CalculateSkillLoss` reconstructs the numeric section of qagame
G_LoseSkillPoints (nitmod_game.c, following G_LoseSkillPointsExt). Unlike
native ET it does not restore the previous skill level or threshold floor.
It returns remaining float XP, actual old-minus-new XP and recomputed
level/unlock bits. Tests cover seven skills at all thresholds, disabled
thresholds, level caps, upgrade disable, negative loss/XP and float rounding.
Nonfinite/overflow inputs are rejected atomically as deliberate hardening.
The helper does not update team scores, implement Lua overrides or invoke
G_UpgradeSkill. Its active integration remains pending those side effects;
the current native G_LoseSkillPoints and wire contract are unchanged.

`nitmod_air.c` isolates P_WorldEffects' air branch from the original qagame
ELF at 0x3cbf0. Disassembly at 0x3cc75 tests bit 0x20; 0x3cc85 adds 0x2ee0
(12000), and 0x3cd68 adds 0x3a98 (15000). Noclip uses the same two durations
but returns before resetting drowning damage. Above water resets damage to
2; submerged expiry uses a strict deadline comparison, adds 1000 to the
previous deadline and raises damage by 2 up to 15 when alive. No catch-up
loop is introduced. Tests cover the connection to the skill evaluator,
deadline boundaries, death, refill and noclip. Signed time overflow saturates
as deliberate hardening. The active g_nitmod_air.c adapter now maps native
airOutTime/damage and preserves ET's nonzero PW_BREATHER branch, including
its negative-reserve behavior. Tests compare normal-clock transitions against
the old ET calculation across water levels, noclip, health and reserves.
P_WorldEffects retains native sound/pain/damage and lava/fire handling.
Its adapter call passes zero unlock bits: the level-five perk is still off.
ClientSpawn now also uses the common deadline helper with zero unlock bits,
without changing damage. Match-pause shifts and movement's signed remaining
air use bounded time arithmetic; negative remaining air is retained rather
than clamped to zero. Tests cover spawn/pause/resume and respawn, exact
expiry, signed clock limits and ordinary baseline ET transitions. This is
not a general fix for every engine clock or other pause-adjusted field.
Original Nitmod had no breather branch here; retaining ET compatibility is
a documented difference. Engine replay and extended-skill activation remain pending.

`cg_nitmod_skill_rewards.c` holds the original 7x5 reward strings recovered
from the cgame ELF object at 0x138a00. Its accessor bounds both dimensions.
The reference test executes the accessor and compares all 35 strings with
fresh extraction from the SHA-256-pinned ELF. This establishes text-table
parity only, not reward gameplay or UI rendering parity. Native four-level
popups remain unchanged until corresponding Nitmod abilities are ported.

Native CS_PLAYERS skill digits now pass through `NITMOD_ParseSkillDigits`:
exactly seven digits, each <= NUM_SKILL_LEVELS-1 at the client callsite.
Parsing stops immediately on NUL, so short strings are not read as seven
characters. Invalid or missing fields leave the zero-initialized newInfo
skills neutral; the entire row is rejected rather than partially updated.
`cg_players.c` additionally bounds reward indices, and both XP-statistics
displays reject negative next-threshold indices. Tests cover every invalid
position, all short lengths, extra fields, supported maxima and unchanged
output on failure. Source checks cover client integration. This is defensive
port preparation, not evidence of original malformed-input parity; sl and
the six-level threshold/progress state remain inactive.

The numeric branch of `G_SetPlayerSkill` is isolated in
`NITMOD_EvaluateSkill`, producing a typed highest-level/unlock-mask pair.
It honors level-count caps, negative disabled thresholds and upgrade disable;
nonmonotonic thresholds are evaluated independently as in the reference.
Executable boundary tests cover all seven skills. No Lua hook, score update,
native client-state mutation or sl activation is included. The integration
audit in `docs/skill-level-integration.md` records the remaining XP-loss,
reward-array, rank, persistence and protocol assumptions. Full level-five
gameplay must not be inferred from this numeric unit test.

Mine map cleanup now lives in `g_nitmod_map_cleanup.c` and is exercised by
`test_nitmod_map_cleanup.c` together with the real owner-cleanup registry.
Engine map lookup/free and entity-free calls are test doubles using native
ET types. Cases cover neither/one/both teams' markers, unrelated markers,
last entity slot, repeated owner cleanup and NULL adapter input. Assertions
verify correct slot identity and marker removal before entity release.
This proves adapter orchestration, not the engine's map-list implementation
or client rendering. The adapter requires a valid g_entities slot or NULL.

`G_SweepForLandmines` remains native ET: the supplied decompile calls
EntitiesInBox and returns zero, whereas ET's g_active consumes a real
team/radius detection result. Original i386 disassembly now confirms the
constant-zero return at ELF 0x8dd17. Native detection is retained as a known
difference pending original caller/gameplay review, not decompiler uncertainty.
See `reference/mine-satchel-disassembly.md` for addresses and instructions.

`reference/original_function_symbols.csv` reproducibly indexes 6549 defined
ELF function symbols from all three SHA-256-verified original modules.
Each row records module digest, ELF virtual address, file offset, size and
function-byte digest. `tools/build_reference_symbols.py` needs only Python's
standard library and refuses mismatched reference hashes. The matching test
checks regeneration, malformed ELF rejection and independently disassembled
function bounds/epilogue. ELF addresses are not copied into the Ghidra-address
column: name matching alone does not establish project-base/version identity.

Owner cleanup reconstructs `nitmod_weapons.c:3706-3761` through
`G_NITMOD_FadeLandmines` and `G_NITMOD_FadeSatchels`. Reverse traversal
avoids skipping adjacent entries during list compaction. Mines require
inuse and a matching non-NULL parent; satchels require the matching parent.
Both clear parent and set `r.ownerNum = ENTITYNUM_NONE` before release.
The map adapter removes both teams' mine markers before G_FreeEntity.
The lists detach entries before the release callback, with repeated removal
in G_FreeEntity harmless. This is an intentional lifetime-safety adaptation.
NULL owners are rejected, including for satchels, to avoid deleting unowned
objects on an invalid request. Existing G_FadeItems call sites and native
g_landminetimeout gates remain unchanged; other weapon types retain ET scans.
`test_nitmod_owned_cleanup.c` exercises reverse order, multiple adjacent
matches, foreign owners, map mines, inactive mines, repeated cleanup, slot
reuse and ownership clearing before callback. Map-marker orchestration is
now executable-tested as described above; gameplay replay remains pending.

Landmines now use an independent registry in `g_nitmod_entities.c`.
References: `nitmod_unknown.c:6731` (successful map placement), `:7962`
(throw), `nitmod_weapons.c:2747` (explosion), `:3787-3815` (team count),
and the list reset/free paths in `nitmod_game.c`. The count uses live
`s.teamNum % 4 == team && s.teamNum < 4`, and returns the smaller of the
count and the supplied maximum. The engine adapter supplies the existing
`MAX_TEAM_LANDMINES`, consistent with native placement and HUD consumers;
Nitmod's configurable `team_maxLandmines` is not yet introduced.
Map placement registers only after the ground-validation failure return.
Free and explosion remove idempotently, and map reset clears both registries.
Tests using real `gentity_t` cover arming/disarming, changing teams, caps,
duplicate insertion, removal/reuse, independent satchel state and overflow.
Source tests verify registration/removal hook placement. Original-engine
replay and custom Nitmod mine variants remain pending. Wire format unchanged.

The first entity-list consumer is now connected: `g_nitmod_entities.c`
owns the satchel registry. References are qagame `nitmod_unknown.c:7964-7993`
(creation), `nitmod_weapons.c:2751` (explosion) and `:3853-3875` (lookup),
and `nitmod_game.c:12596` / `:23097` (map reset / free).
`G_FindSatchel` returns the first owner match in registration order, rather
than the original ET baseline's entity-slot order. Tests compile against real
`gentity_t` and exercise two owners, order, duplicate insertion, repeated
removal, slot reuse, map reset and the G_Error overflow adapter. Source tests
verify the four lifecycle hooks. Removal on free/explosion is unconditional
and idempotent, including entities already converted to events, as intentional
stale-pointer protection. Other list classes remain unconnected.
`G_ExplodeSatchels` now uses a stable registration-order snapshot with the
typed owner match and inclusive 2000-unit radius. Before each callback it
rechecks inuse, parent, native missile/satchel classification, list membership
and spawnCount. Entries replaced, transferred or removed by an earlier blast
are skipped; newly registered entries wait for a future command. Current
positions are evaluated immediately before each callback. Tests exercise
adjacent entries, exact radius and diagonal rejection, other owners, inactive
or reclassified entities, removal, generation reuse and new registration.
This deliberately differs from both ET's slot-order scan and the decompiled
Nitmod loop, which increments after list compaction and may skip a charge.
NaN distances are rejected. These are documented safety changes, not claims
of original chain-reaction, floating-point or gameplay parity. Engine replay
is still required; the snapshot adds bounded stack storage for 1024 entries.
No network protocol or cgame/ui change is needed for this server-side registry.

`nitmod_entity_array.c/.h` reconstructs the three `nitrox_*EntityArray`
helpers from qagame `nitmod_core.c:2350-2408`. Call sites pass values from
G_Spawn and existing entities, establishing that the original integer slots
hold pointers rather than entity numbers. The port uses borrowed
`struct gentity_s *` values and pointer-sized memmove, independent of host
pointer width. Capacity is 1024, and a full array is rejected even when the
incoming pointer already exists (the original checks overflow first).
Removal preserves order; reset only clears count. Executable tests cover
every capacity slot, duplicates, first/middle/last removal, missing entries,
NULL values and invalid container counts. Invalid containers are rejected
as deliberate hardening. The helper returns a FULL result instead of calling
G_Error directly. The satchel adapter above now owns its list and supplies
fatal overflow handling. Other list owners and original-engine replay remain
pending; these helpers are recorded as partial ports, not full gameplay parity.

`game/nitmod_snapshots.c` decodes `ct`, `tsc` and `mes` into typed local
snapshots and commits only after every argument passes validation. The
charge-time mapping remains soldier/medic/engineer/fieldops/covertops,
each with Axis then Allies. Team scores and `%i` fields retain signed values;
`mes` bodyshots/headshots/revives now match the server's unsigned `%u` fields,
including UINT_MAX. `tests/test_nitmod_snapshots.c` uses a reusable argv buffer
like CG_Argv and injects malformed fields at every position, checks unchanged
prior state, signed limits, argument counts and exact field ordering.
These tests cover the port protocol and atomicity, not original engine replay.

`game/nitmod_protocol.c` supplies the same strict decimal parser to qagame
and cgame for `nitcap`, `nitcaps`, `ncs` indices, `nhs` and announcement
fields. `tests/test_nitmod_protocol_numbers.c` covers trailing junk, negative
capabilities, combined tokens, whitespace and signed/unsigned overflow.
Malformed fields are ignored before changing negotiated capabilities or
configstrings; well-formed unsupported versions still revoke capabilities.
The full unsigned capability range is accepted and masked by the existing
feature contract. Strict rejection is port hardening, not evidence that
the original accepted the same input language.

The `scs`, `#` and `ob` decoders now use the same atomic snapshot path.
Server and client share their typed structures in `nitmod_snapshots.h`;
the wire order remains unchanged. Negative integer settings remain accepted.
The `#` decoder preserves the local score cache populated by `tsc`, and
`scs` applies the camera-filter side effect only after all fields validate.
`ob` rejects actors outside the engine client range before storing the event;
unknown objective IDs retain the existing presentation fallback.
The jump-height float accepts finite decimal values and rejects malformed
tokens, overflow, and underflow to zero (C numeric locale, as in the sender).
Executable tests cover every field's rejection, exact ordering, negative
settings, score preservation, actor boundaries, and invalid float values.
This is intentional input hardening; original malformed-input parity is
not claimed. Full gameplay semantics of the custom settings remain pending.

`game/nitmod_config_store.c` owns qagame's 655 NCS values and dirty markers.
`tests/test_nitmod_config_store.c` executes the production store for all slots,
1017-byte payload acceptance / 1018-byte rejection, empty updates, duplicate
writes, rejected delimiter characters, overlapping source/destination and reset.
Invalid writes leave the entire store unchanged; duplicate writes retain any
pending dirty bit. The adapter retains immediate sends and the duplicate dirty
pass, including empty values. This tests storage transitions, not network replay
parity. Delimiter/length rejection is the existing port policy and differs from
the original's unchecked/truncated input behavior.

Announcement semantics are exercised by `tests/test_nitmod_announcements.c`,
linked with the same `game/nitmod_announcements.c` used by both modules.
The original `G_UpdateKillingSpree` sends type 1 with `kills / 5 - 1`
(5 through 30) and type 2 with `deaths / 10 - 1` (10 through 30).
Type 2 is a death spree, not a kill-spree termination. `ReviveEntity`
sends type 4 with the actual multiple-of-five count and type 5 with
`revives - 2` for 2 through 5 revives. These count mappings are now shared
by the sender and receiver. Malformed and overflowing decimal fields are
rejected before looking up client information or formatting messages.
The private multi-kill lookup table is unresolved; type 3 still displays a
tier rather than a claimed kill count. Text remains a documented fallback;
these tests do not establish original-binary or rendering parity.

Kill-spree delivery now checks `g_announcer & 1` using the engine Cvar
value. Its original registration/default has not been recovered, and an
unset value disables delivery. Full negative-spree tracking and private
option-dependent producer branches remain pending.

Positive streak accounting is isolated in `game/nitmod_spree.c` and exercised
by `tests/test_nitmod_spree.c`: 100 consecutive kills, exactly six notifications,
option changes without losing counters, independent player state, reset and
saturation at INT_MAX. The death adapter now runs after the native PM_DEAD /
intermission guard. Disconnect and ClientBegin clear slot state; rejected
capability negotiation clears only capabilities. Source contract checks cover
these integration boundaries; an engine replay is still required. Best-spree
persistence and negative streak accounting are not implemented by this subset.

Before a release candidate, every row must gain either an i386
control-flow/disassembly comparison, a captured original-vs-port protocol
transcript, or a deterministic replay test. The Windows host build only
detects source/header integration errors; Linux-i386 and Emscripten builds
remain required release gates.
