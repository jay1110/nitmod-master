# Weapon cycling timestamp safety

The existing command gates match original CG_LastWeaponUsed_f and the
next/previous weapon/bank commands: elapsed time must reach the configured
cycle delay. Seven typed command paths now compute that subtraction in
double precision, avoiding signed integer overflow without changing the
ordinary threshold or equality behavior. This is defensive hardening,
not a newly reconstructed gameplay feature or exact x86 overflow emulation.

Tests exercise the exact boundary, one millisecond before it, and both
INT_MIN/INT_MAX directions through the real last-weapon command. Existing
no-snapshot, frozen-player and weapon-bank checks remain in the full suite.
No assets, inventory rules, network layout or server behavior changes.
