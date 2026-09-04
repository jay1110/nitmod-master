# Recovered clip reload transfer

Current integration: the transfer now runs in the shared production movement
path; see [active reload completion](active-reload-completion.md). The inventory
request predicate below does not imply a complete reload-initiation port.

## Inventory-side reload request check

`NITMOD_ReloadInventoryReady` reconstructs only the inventory predicate from
PM_CheckForReload (qagame 0x2a7a0, cgame 0x19c80). Manual requests require
reserve and an under-capacity magazine: server 0x2a914..0x2a956 and akimbo
0x2a9e8..0x2aa33; client 0x19dfc..0x19e3e and 0x19ec8..0x19f13.
Automatic requests require reserve, an empty main clip and, for akimbo, an
empty sidearm clip: server 0x2a980..0x2a9e3, client 0x19e60..0x19ec3.
The explicit request enum does not encode engine button bits or auto-reload
settings. Main capacity uses the weapon ID, sidearm capacity its clip alias
(server 0x2aa17..0x2aa29). No weaponstate numbers are translated here.

This predicate does NOT implement the surrounding weapon-state/timer gate,
rifle-grenade exclusion, automatic-reload setting/weapon flag, scoped-rifle
mode change, or PM_BeginWeaponReload restrictions. In particular, a true
inventory result for a scoped weapon is not permission to reload in scope.
The begin routine also has a separately identified noMidclipReload field at
weapon record +0x5fc, not yet part of the loaded definition subset.

All 17068 transfer scenarios additionally test manual and automatic requests
(34136 predicate checks), with whole-state immutability checks. Invalid enum,
null/short table, negative capacity/count and unknown-identity cases reject.
Negative values are hardened to rejection rather than following the original
nonzero tests on invalid inventories. No engine event or active hook is added.

Original qagame `PM_ReloadClip` is at ELF 0x12bf0; cgame at 0xa500.
Both take the private function's weapon argument in EAX (not the missing
argument shown in Ghidra's guessed void signature). Neither signature nor
raw offsets are copied into the typed public adapter.

The server reads reserve via BG_FindAmmoForWeapon at 0x12c10 and clip via
BG_FindClipForWeapon at 0x12c26. It loads maxclip from the current WEAPON's
72-byte ammo record, offset +8 (0x12c2b..0x12c40), not the clip-alias record.
Signed minimum of reserve and maxclip-minus-clip selects the transfer at
0x12c43..0x12c45. Reserve subtraction and clip addition follow at 0x12c5d
and 0x12c77. The client has the corresponding sequence at 0xa520..0xa587.

Original akimbo identities 34/35/44/45 then select their sidearm and repeat
(server 0x12c7e..0x12c9c, client 0xa58e..0xa5ac). This reloads the akimbo
hand first and the sidearm from the remaining shared reserve. It is NOT
the parity-based selection used when firing. An overfull clip produces a
negative transfer and returns excess rounds to reserve, even at zero initial
reserve; this behavior is preserved rather than silently clamped away.

`NITMOD_ReloadWeaponClips` uses native playerState_t, typed original aliases
and caller-provided ammo records. A two-hand operation is staged before any
writes, so an invalid sidearm cannot leave a partial reload. Negative reserve,
clip or capacity values, invalid identities, short tables and reserve overflow
reject unchanged. These are explicit hardening differences outside the tested
nonnegative, representable original domain. Valid no-ops return success.

The existing real-table diagnostic now also executes 11560 single-weapon
cases (40 identities x 17 clip values x 17 reserves) and 5508 akimbo cases
(4 identities x 9 x 9 clip values x 17 reserves). Different capacities by
weapon identity catch weapon-versus-clip alias indexing mistakes. Whole-state
comparisons protect unrelated fields and the independent adrenaline/syringe
inventories. Additional checks cover atomic second-hand failure, negative
values, null arguments, unsupported IDs, short tables and INT_MAX boundaries.

Compiled in cgame and qagame by CMake/SCons and connected to active
PM_ReloadClip. Partial request/start integration is documented in
active-reload-start.md; ammo pickup remains separate work. Evidence is disassembly plus
deterministic host tests, not an original-engine replay or release ABI proof.
