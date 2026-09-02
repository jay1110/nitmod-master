# Compiled shared-layout sample

Current probe includes playerState_t.eFlags at offset 104, size 4 in both trees;
the executed comparison now contains 61 matching rows.

Latest extension: six additional entityState_t fields now bring the executed
comparison to 60 matching rows: density (244), dmgFlags (248), onFireStart
(252), onFireEnd (256), nextWeapon (260), teamNum (264), all four bytes. These
were compiled and executed separately against both trees with no differences.
They support the typed landmine trigger-latch mapping; semantic parity is not
inferred from layout agreement alone.

Current extension: the probe now also includes each tree's own cg_public.h
and checks snapshot_t, gameState_t and vmCvar_t. Report schema 2 hashes both
direct headers per tree under inspected_header_sha256. The original results
below are retained; the additional results are recorded at the end.

Executed on 2026-09-02 with Emscripten 4.0.23 and SDK Node 24.19.0:

```powershell
python -B tools/run_wasm_layout_audit.py C:/Users/micha/Documents/GitHub/etlegacy
```

The same C probe is compiled twice, separately including each tree's actual
q_shared.h. Both standalone WASM programs then execute under Node and report
sizeof and selected offsetof/field-size pairs. No Legacy definitions are copied
into the mod and no engine/gameplay program is initialized.

| Structure | ET 2.60 bytes | Legacy bytes | Fields checked |
| --- | --- | --- | --- |
| usercmd_t | 28 | 28 | 11 |
| playerState_t | 1452 | 1452 | 11 |
| entityState_t | 288 | 288 | 6 |

Both pointer sizes are 4. All 28 selected field offsets and sizes match,
including player ammo/ammoclip arrays, origin, velocity, weaponTime, stats,
persistant and ping; entity trajectory fields; and all named usercmd members.
There are 32 output rows per side including aggregate and pointer sizes.

The JSON includes the probe/header hashes, exact compile/run commands, measured
values and differences. Nonempty differences produce CLI exit 1. The header
hashes are not a complete transitive dependency manifest. This is a fresh
default Emscripten probe configuration, not extraction from the existing engine
binary or certification of every build-flag combination.

Unchecked fields, signedness, semantic contracts, network serialization,
renderer structures, snapshots and engine syscall behavior remain open.
Equal aggregate size and sampled offsets are not complete ABI parity.
Host tests cover report parsing, wrong pointer sizes, duplicate/malformed rows,
different key sets and detected offset changes; actual compilation is a separate
SDK integration run, not performed by host CTest.

## Snapshot and initialization buffers

Actual recompiled/rerun comparison: no differences in all 54 reported rows
(six structure sizes, pointer size, 45 field offset/size pairs, two constants).

| Additional structure | Both sizes | Fields checked |
| --- | --- | --- |
| snapshot_t | 148964 | 9 (all named fields) |
| gameState_t | 20100 | 3 (all named fields) |
| vmCvar_t | 272 | 5 (all named fields) |

snapshot_t has ps at 44 (1452 bytes), numEntities at 1496, entities at 1500
(147456 bytes), numServerCommands at 148956 and serverCommandSequence at
148960. MAX_ENTITIES_IN_SNAPSHOT is 512 and baseline CMD_BACKUP is 64 on both
sides. Legacy's separate extended command-backup option is not exercised.

gameState_t has 4096 bytes of offsets followed by 16000 bytes of string data
and dataCount at 20096. vmCvar_t has handle/modificationCount/value/integer at
0/4/8/12 and a 256-byte string at 16. These match at the memory-layout level;
no configuration data or real snapshots were transferred by this test.

A new regression fixture ensures differing snapshot array size/capacity is
reported even when the entities field starts at the same offset. All 75 host
CTests pass. Production definitions and original reference binaries are unchanged.
