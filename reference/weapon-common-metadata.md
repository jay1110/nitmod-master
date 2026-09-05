# Common weapon metadata batch

Reference: qagame `BG_RW_ParseDefinition`, ELF 0x35320 (sorted Ghidra addresses
start around 0x45320), `src_nitmod_decompiled/qagame/sorted/nitmod_bg.c`.
The new members are typed fields, not emulations of private byte offsets.

The existing transactional options parser now also recognizes:

| Original fields | Typed storage / original private offsets |
| --- | --- |
| name, KillMessage, KillMessage2 | 32/64/64-byte strings; +0x5b4/+0x604/+0x644 |
| damage, spread | integers; +0x5d4/+0x5d8 |
| SpreadScaleAdd, SpreadScaleAddRand | integers; +0x5ec/+0x5f0 |
| limboKill | bare flag; +0x5f8 |
| movementSpeedScale | float; +0x600 |
| HeadshotWeapon, GibbingWeapon, DistanceFalloff | tri-state integers; +0x684/+0x688/+0x68c |
| splashdamage, splashdamage_radius, minHeadshotDamage | integers; +0x690/+0x694/+0x698 |
| HeadshotRatio, spreadRatio | floats; +0x69c/+0x6a0 |
| velocity2spread, viewchange2spread | tri-state integers; +0x6a4/+0x6a8 |

The original yes/no mapping is 1/2, with 0 for an unknown value. It is not a
boolean cast: absent and explicit no remain distinct. Invalid choices retain
the original zero result, but the parser does not emit the original console
warning. Numeric overflow/nonfinite float rejection and EOF rejection remain
deliberate hardening. Strings truncate to the original destination capacities.

Engine-quoted tokens now retain their contents with an internal byte-1 prefix.
Only string consumers unwrap it. This supports quoted names and kill messages
without making quoted braces, numbers or keys part of the parser grammar.
Base and alternate sections remain independent. All outputs commit together;
on failure the caller's ammo, mask, recoil and complete metadata remain intact.

## Active versus stored behavior

The qagame pickup cache introduced previously now accepts definitions containing
these common attributes, allowing their class masks to reach the active pickup
policy instead of rejecting the entire file. The registry also stores them.
This batch does **not** activate new damage, headshot, spread, movement, limbo-kill
or obituary calculations. Their consumers require separate parity work, with
client prediction and server decisions kept consistent. The shared source can
compile for each module; compilation is not evidence of active cgame consumers.

Tests cover all added fields, quoted string transport through the real engine
token adapter, alternate separation, each truncation point, atomic rollback,
quoted-number rejection and the full qagame source-to-pickup path for all classes.

## UI connection-screen corrections

Download counters are range-checked before float-to-int conversion. Percentage
calculation clamps before conversion, elapsed-time subtraction uses a wider
intermediate, and the 80-sample ETA sum no longer overflows a signed integer.
GB fractional formatting no longer multiplies a large remainder in int.
Progress-bar input rejects invalid size and clamps invalid/oversized counts.
These are robustness corrections, not claims of new original UI features.

UI tests exercise 1.50 GB formatting, ordinary 50% progress, count exceeding
size, oversized cvars, 80 large ETA samples, negative count and timer rollback.
Counters still saturate at INT_MAX: this is not full 64-bit download support.
The original 80-sample estimator remains; no new per-file reset policy is added.

Pak assets and original modules are untouched. Native tests and WASM ABI/load
checks do not replace browser gameplay, actual downloads or visual comparison.
