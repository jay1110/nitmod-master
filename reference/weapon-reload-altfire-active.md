# Active alternate-fire reload state correction

Original PM_BeginWeaponReload accepts original states 0, 5 and 6:
qagame 0x28756..0x28766 / cgame 0x17c66..0x17c76. The existing
state reconstruction identifies these as ready, firing and alternate firing
(see weapon-reload-start.md for the PM_AltFire state stores). They are NOT
native numeric states 5/6, which mean readying/relaxing.

Stock ET's begin-reload rejected alternate firing even though its outer
PM_CheckForReload could request a reload in that state. Shared native
PM_BeginWeaponReload now calls NITMOD_ReloadStateAllowed, accepting named
WEAPON_READY, WEAPON_FIRING and WEAPON_FIRINGALT only. This is a narrow active
behavior correction in both cgame and qagame, not just helper extraction.

The original outer state mask (qagame 0x2a7fb..0x2a810 / cgame
0x19cdb..0x19cf0) excludes original raising/dropping/reloading states and
allows both firing states. Its range-mask behavior also allows values outside
the original state range; this increment does not replace the native outer
predicate with a whitelist or claim parity for invalid outer states.

All other native checks remain: noWeapClips, launcher exclusions, outer timer
gate, midclip restrictions, full-magazine/lean checks and native ammo/ability
handling. A reload request while alternate firing is therefore not an
unconditional reload. When allowed, the existing timer logic overlaps firing
time with reload duration via max(), rather than adding both durations.
READY retains additive timing. Full recovered dispatcher activation is still
pending ammo/settings/ability integration.

The test harness now extracts and executes real PM_CheckForReload as well as
PM_BeginWeaponReload. 288 combinations cover 12 native/adjacent invalid states,
four times (-1, 0, 1, 10000), direct/outer entry and allowed/full/lean cases.
Checks include preserved input on rejection, exact add/max timing, one real
EV_FILL_CLIP, first-person reload animation and unchanged inventory. The
body-animation boundary records the state at invocation: direct firing entry
keeps the firing state until timing commit, whereas raising-to-reload must
already have reset READY. Previously tested scoped handoffs retain the latter
assertion explicitly. Source contracts pin the active gate and check order.

Host build and all 66 CTests pass. These are shared native-source tests, not
live engine input replays or original ELF execution. Linux-i386 and WASM
release and full reconstructed reload parity remain outstanding.
