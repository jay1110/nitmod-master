# Active READY reload timer addition

The helper is now named `NITMOD_AddWeaponTime32`, shared with weapon drop
and raise; see `weapon-switch-timer-arithmetic.md`. References to its earlier
name below describe the original reload-only increment.

Original qagame uses a 32-bit ADD at `0x288a0`; cgame uses the equivalent
instruction at `0x17db0`. Unlike the firing-state maximum, READY adds the
duration to the existing timer. Machine addition wraps modulo 2^32.
Plain signed C addition does not define that overflow behavior.

The active shared begin path now calls `NITMOD_AddReloadTime32`. It adds
the two signed 32-bit inputs in int64_t, adjusts a result outside signed
32-bit range by 2^32, and converts the now-representable result to int.
This preserves the original result without signed overflow or an
out-of-range unsigned-to-signed cast on the supported 32-bit-int targets.

The isolated hardened `NITMOD_ApplyReloadTiming` API still rejects negative
durations and READY overflow; its deliberate validation contract has not
been weakened or silently made equivalent to the active legacy path.
No other weapon timer additions were changed.

`TestReloadTimerExtremes` now covers 294 actual begin executions: seven
timer values, seven duration values, READY/FIRING/FIRINGALT and fast reload
off/on. The 98 added READY cases use an independent unsigned modulo oracle
with only representable signed conversions, including positive overflow,
negative underflow and INT_MIN + INT_MIN. Whole-state, extension, body-event
and predictable-event assertions remain in place. Timing fixtures are
restored before assertions. The source contract verifies the active helper.

Complete host Debug build and 66/66 tests pass. This provides instruction
and host execution evidence, not sanitizer, original-ELF replay or final
Linux-i386/WASM verification. Extreme timer scenarios are regression probes,
not a claim that normal gameplay produces these input values.
