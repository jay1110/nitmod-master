# Canister kick: mapped native subset

Original qagame G_CanisterKick 0xfd070, 1284 bytes; sorted nitmod_admin.c.
g_canisterKick and g_canisterKickOwner both default to zero with flags,
trackChange and reset zero. Activate2 calls the helper before its traces.

Limbo, PM_DEAD and prone reject. Search center is currentOrigin + yaw-forward
24; bounds relative to it are (-32,-32,-24) through (32,32,8). The first missile
in engine query order wins; an unsupported first missile terminates selection.
Four mapped weapons are supported: the two hand grenades, smoke marker and
smoke bomb. Original IDs 48/50 are not assigned to unrelated native weapons.

Pitch is capped at -15 degrees; trajectory switches to gravity, time becomes
now-50, base height increases 30, currentOrigin copies base, and velocity is
forward * strength * 10 plus strength * 2 vertically. Existing fuse/think
state is preserved. Disassembly 0xfd441-0xfd499 overrides the x87 rounding mode
to truncation (OR 0xc00 at 0xfd44a), despite Ghidra spelling this ROUND.
The port truncates explicitly and saturates extreme results rather than
overflowing integer conversions. Underflowing trajectory timestamps saturate.

Ownership optionally changes parent, ownerNum and teamNum for grenades and
smoke bombs, and for smoke markers only before activation. Original entity
+0x368 maps to gentity_t.active: sorted weapon_callAirStrike sets word index
0xda (0x368) to 1, matching native ent->active = qtrue before counters/sound;
the denial/abort branches clear the same field in both implementations.
G_CanisterKick ELF 0xfd4ab..0xfd569 tests weapon 0x15 and that field before
changing parent/owner/team. Kicking an active marker still moves it but leaves
ownership and active state intact. The kick does not update airstrike counters.
Poison projectile definitions, debug rail-box rendering and
canister collision/spawn extensions elsewhere in Nitmod remain unported.
No new network events, asset changes or shared playerState fields are needed.

One hundred full-qagame fixture profiles exercise weapon/owner/gate/active combinations,
query bounds, truncation, trajectory, fuse preservation and ownership. Engine
box queries are doubled; real collision-world selection/browser play remains
unverified. This is an experimental subset, not full CanisterKick parity.

## Spawn collision integration

fire_grenade now calls G_NITMOD_ConfigureCanisterKick after its weapon switch.
For the four mapped canisters, nonzero kick strength selects CONTENTS_CORPSE,
mins (-4,-4,0), maxs (4,4,6), and initial absolute bounds. Damageability,
die callback, fuse and weapon policy are untouched. Disabled kicking does not
undo collision/damage state configured by another option. No existing airborne
missiles are retroactively rewritten when the Cvar changes.

The earlier small-canister damage helper incorrectly called original value
0x04000000 CONTENTS_BODY. It is CONTENTS_CORPSE in this ET tree. Corrected
for all three damage-mask adapters. The original ELF smoke/marker setup around
0x8ef6c-0x8f011 confirms the literal value written to entity +0x14c; the sorted
grenade and smoke paths agree. This correction does not alter other missile
families or their still separately audited collision settings.

Thirty additional profiles execute the real fire_grenade allocator/setup for
five weapons, three kick values and two damage settings, verifying bounds,
contents, preserved owner/team, position, normal fuse/think and rifle-grenade
exclusion. The existing damage-helper matrix tests the corrected mask too.
World linking and engine collision queries remain outside these host fixtures.
