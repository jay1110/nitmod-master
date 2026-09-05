# Shared six-level gameplay tables

## Evidence

Reference: unchanged `original_nitmod_shared_objects_32bit/qagame.mp.i386.so`.
`BG_GetFromTable`, address `0x21060..0x210f6`, was inspected as i386
disassembly; the decompiler's empty-looking function is NOT authoritative.
It loads one skill's unlock mask from its second argument using the third
argument as a skill index. The typed API instead accepts that mask directly.

Selection starts at row zero. For each following row it compares against
the **previous table row**, then conditionally replaces the result only if
the corresponding unlock bit is set. Consequently an artillery mask of
32 alone still costs 1.0: bit 4, not the highest numeric level, controls the
transition to 0.66. Repeated rows must not silently grant skipped upgrades.

The 20 binary32 tables occupy consecutive 24-byte rows at `0x2a4f64`:

| Address | Original symbol | Base | Transition bit | Changed value |
|---|---|---:|---:|---:|
| 0x2a4f64 | chargeCost_Tripmine | .75 | none | .75 |
| 0x2a4f7c | chargeCost_Mortar | .5 | 2 | .33 |
| 0x2a4f94 | chargeCost_Panzer | 1 | 2 | .66 |
| 0x2a4fac | chargeCost_Artillery | 1 | 4 | .66 |
| 0x2a4fc4 | chargeCost_Adrenaline | 1 | none | 1 |
| 0x2a4fdc | chargeCost_Ammo | .25 | 2 | .15 |
| 0x2a4ff4 | chargeCost_Health | .25 | 2 | .15 |
| 0x2a500c | chargeCost_Smoke | 1 | 4 | .66 |
| 0x2a5024 | chargeCost_Satchel | 1 | 4 | .66 |
| 0x2a503c | chargeCost_Riflenade | .5 | none | .5 |
| 0x2a5054 | chargeCost_Dynamite | 1 | 8 | .66 |
| 0x2a506c | chargeCost_Landmine | .5 | 8 | .33 |
| 0x2a5084 | chargeCost_Construct | 1 | 4 | .66 |
| 0x2a509c | chargeCost_Repair | 1 | 8 | .66 |
| 0x2a50b4 | disarmSpeed_Satchel | 3 | none | 3 |
| 0x2a50cc | artilleryBombs | 5 | 8 | 9 |
| 0x2a50e4 | disarmSpeed_LandMine | 3 | 4 | 6 |
| 0x2a50fc | disarmSpeed_Dynamite | 3 | 4 | 6 |
| 0x2a5114 | armSpeed_Dynamite | 7 | 4 | 14 |
| 0x2a512c | armSpeed_LandMine | 12 | 4 | 24 |

## Implementation and tests

`game/nitmod_skills.c` now supplies a typed selector and immutable table
catalogue shared through the existing build lists. No engine structures,
weapon IDs or wire layouts change. Invalid IDs, null pointers and non-finite
custom rows reject without modifying output; this is deliberate hardening
over the original unchecked routine.

`test_nitmod_skills.c` covers every table with all 64 masks, repeats with
upper bits set, tests synthetic multiple-transition rows, skipped upgrades,
invalid IDs and non-finite values in every row position. This is deterministic
numeric/disassembly verification, not an execution of the original binary.

## Remaining integration

This is a shared reconstruction foundation, **not newly active gameplay**.
The live qagame skill lifecycle still needs authoritative per-client unlock
mask ownership. Do not derive these masks from numeric ET levels: disabled
individual thresholds make that conversion incorrect. Registering g_fieldOps
before its consumers and charge accounting are consistent would be misleading.

Airstrike refund integration must cover both preflight capacity checks,
obstructed sky/flight paths and artillery rejection. Original bits 2 (full)
and 4 (half) use the artillery table, with full taking precedence, the owner's
current team charge time, parent/client validity and g_noCharge guards.
Spectator cancellation with friendly fire disabled is not a refund branch.
Client prediction and server deductions must be migrated together before
claiming original-server parity. UI has no new behaviour in this change.

No pak, PK3, menu, weapon asset or original module was modified.
