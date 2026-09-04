# Weapon interpolation lifecycle hardening

The active CG_RunWeapLerpFrame path now validates sequence and speed before
mutation and permits transition checks without dereferencing a missing
snapshot. Empty sequences/nonpositive frame durations hold firstFrame with
zero backlerp. Time additions, frame differences and offsets use wide
arithmetic; values stored as int saturate instead of overflowing. Negative
derived frame indices clamp to zero, oversized loops clamp to sequence size,
and interpolation remains in [0,1]. Animation-disabled output also sets the
returned interpolation fraction to zero.

The existing valid timing algorithm is retained: initial lerp, advancing
old/current frames, loop-tail wrapping, holding the final frame and the
200-ms future-frame correction. Full-cgame tests run twenty frames for each
loop size 0..4, check an intermediate half-frame, rejected indices/speeds,
empty/invalid frame durations and initialization at INT_MAX with a toggle
bit and absent snapshot. These tests call the active interpolation routine.

This is defensive integration, not a newly reconstructed original subsystem.
Original inlined weapon animation code in sorted/cgame_ents.c around
CG_SWLFA diagnostics retains unchecked timing operations; saturation and
invalid-input behavior are intentional differences. Browser animation parity,
all raising/transitional gameplay paths and native i386 parity remain open.
No pak assets or network/player-state structures are changed.
