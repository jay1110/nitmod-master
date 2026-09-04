# Active magazine transfer and reload completion

Previously isolated NITMOD_ReloadWeaponClips and NITMOD_FinishWeaponReload
are now called by the real PM_ReloadClip and PM_FinishWeaponReload in
bg_pmove.c, shared by cgame prediction and qagame. Original transfer evidence:
cgame ELF 0xa500 and qagame ELF 0x12bf0; completion evidence and animation
mask are recorded in weapon-reload-finish.md. This activates already recovered
behavior; it is not a new reconstruction of those numeric helpers.

pmove_t has a mod-local nitmodReloadEnabled input. Both qagame Pmove setup
paths enable it. Both cgame setup paths enable it for gamename=nitmod,
including reconstructed et260-layout servers. Native etmain prediction stays
on the existing implementation. This does not alter engine playerState,
snapshot layout, user commands or negotiated protocol numbers.

Known typed weapon identities use their original ammo/clip aliases and the
current native ammoTableMP capacities. Akimbo reloads main hand then sidearm
from remaining reserve, staging both before commit. Overfull magazines return
excess rounds to reserve. Invalid negative counts/overflow reject unchanged;
there is no fallback to unchecked partial writes after validation failure.
Unmapped native weapons retain the native implementation, not guessed aliases.

Completion requires expired timers and WEAPON_RELOADING, transfers magazines,
sets READY and selects/toggles the original idle animation with the existing
movement/animation/command gates. Failure leaves RELOADING; the outer transition
stage stops that weapon frame instead of continuing into fire logic. No new
completion event is emitted. Rifle-grenade attachment reload calls also reach
the shared PM_ReloadClip adapter.

The same check_reload_runtime.h runs in both full module links: all 44 mapped
weapons, enabled/disabled paths, 81 reserve/clip combinations per weapon,
movement types, animation timers, command presence and toggle states. Expected
inventory transfers are calculated independently; whole player states are
compared. Tests also cover invalid second-hand atomicity and pending timers.
Existing exhaustive helper tests remain active.

Reload initiation, original dynamic weapon-definition capacities/options,
Lua/custom ability policy and complete weapon gameplay are NOT claimed here.
Full native CTest and WASM/Node checks run; real dedicated-server prediction
replays remain pending. Pak assets and original binaries remain untouched.
