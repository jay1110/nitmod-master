# Extended original server events

This batch implements original client events 94, 95, 97, 100, 102 and 103 in
`cg_nitmod_events.c`, plus the missing team-chat additions for 91/92.
It does not change qagame's native ET wire enum, original binaries or pak files.

Evidence: original cgame ELF, event-name table 0x1346c0, CG_EntityEvent at
0x61d60; corresponding `sorted/cgame_events.c` cases 0x5b/0x5c/0x5f/0x61/
100/0x66/0x67 and `sorted/cgame_weapons.c` CG_FireWeapon branch 0x5f.

| Wire | Behavior now connected |
| --- | --- |
| 94 | Clears the referenced corpse's typed `playerEntity_t` presentation cache without altering its snapshot state |
| 91 | Three artillery replies in team chat, alongside existing radio scripts |
| 92 | Airstrike denied/aborted replies; accepted strike deliberately has no chat line |
| 95 | Ordinary firing state updates, then dedicated knife throw sound; no ordinary flash/echo sounds or brass |
| 97 | Local-player-only weapon change using eventParm, translated from original weapon ID |
| 100 | Registered game sound at the event entity, CHAN_AUTO, volume 255 |
| 102 | Barbwire pain sound at the listener, CHAN_ANNOUNCER, default volume; distance-scaled camera shake |
| 103 | Registered game sound at the snapshot local client, CHAN_AUTO, volume 255 |

Original media registrations establish `sound/weapons/knife/throw.wav`
(cgs+131904) and `sound/player/hurt_barbwire.wav` (cgs+132356). Sound events
use the same original cgs+0x2038f84 array as GENERAL_SOUND, mapped to the
existing typed gameSounds/NCS storage. They do not parse script names or
register arbitrary paths. Weapon event 95 is included in snapshot weapon
translation; 97's eventParm is translated at dispatch, without mutating it.

Safety differences: invalid indices, absent snapshots and nonpositive sound
handles do not play; unsupported weapon IDs do not change selection. Slap
with a nonpositive radius or zero resulting strength does not start a
zero-duration shake. No native ET event is redirected to these handlers.

Event 94 is original `EV_BODY_DP`. Its disassembly clears 0x514 bytes at the
original `centity_t.pe` offset for `otherEntityNum`. The portable port uses
`sizeof(cg_entities[index].pe)` instead, because native and WASM structure
sizes are ABI-dependent, and rejects references outside `MAX_GENTITIES`.

Tests cover repetition bits, sound indices and recipients/volumes, missing
sound handles, slap range, knife sound and muzzle time, local/remote/invalid
weapon changes, chat status boundaries, and temporary/attached knife-event
weapon translation. ELF tests verify all five additional IDs. Full native
CTest and WASM build/load checks are used; live server gameplay is not claimed.

Still open: remaining debug events, full knife weapon physics/animation
parity, original popup rendering, and the
larger UI/admin/database/backend port. This is a client behavior batch,
not completion of the entire reconstruction.
