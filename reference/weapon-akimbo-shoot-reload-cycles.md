# Executed akimbo consumption/reload cycles

`TestAkimboShootReloadCycles` joins the actual availability, consumption
and transition-stage functions into 1944 deterministic scenarios:
four akimbo variants, both initial clips independently 0..8, reserve
0/1/30 and ordinary/enabled-alternate reload input.

Each scenario drains both hands, attempts reload, waits through the active
reload timer gate, completes transfer, then drains the resulting clips.
The test supplies individual admitted consumption calls and explicitly
expires the timer. It does not execute the full firing scheduler, projectile
creation or engine animation scripts.

An independent zero-first/parity oracle selects the expected hand before
each consumption. Whole-state comparisons check availability purity and
single-slot subtraction. A conservation assertion after every shot checks
that shots plus remaining clip/reserve ammunition equal the initial total.
Reload initiation does not move ammunition; completion transfers main hand
first from shared reserve. Empty reserve does not start reload. Repeated
input during the timer gate must preserve the complete state. Exactly one
fill event is produced for a started reload and completion adds none.

No production code changed in this increment. Complete host Debug build
and 66/66 tests pass. The coverage does not activate Nitmod refill rules,
certify original binary gameplay parity or replace Linux-i386/WASM release
and full-engine replay checks.
