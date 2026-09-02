# Original i386 mine/satchel evidence

Artifact: `qagame.mp.i386.so`, SHA-256
`84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49`.
Addresses below are ELF virtual addresses, not assumed Ghidra project addresses.
Inspected using GNU objdump from the local MSYS2 installation:

```
objdump -d --disassemble=G_SweepForLandmines original_nitmod_shared_objects_32bit/qagame.mp.i386.so
objdump -d --disassemble=G_ExplodeSatchels original_nitmod_shared_objects_32bit/qagame.mp.i386.so
```

## G_SweepForLandmines

Symbol address `0x0008dbe0`, size `0x13c` (316 bytes).
Builds an origin +/- radius box and passes capacity 1024 to the engine query.
The only return path after that query is:

```
8dd0c: e8 6f 90 04 00    call  d6d80 <trap_EntitiesInBox>
8dd11: 81 c4 44 10 00 00 add   $0x1044,%esp
8dd17: 31 c0             xor   %eax,%eax
8dd19: 5b                pop   %ebx
8dd1a: 5e                pop   %esi
8dd1b: c3                ret
```

Thus constant false is real reference behavior, not a decompiler omission.
The port now implements this query-and-false behavior in
`src_2.60/game/g_nitmod_mine_sweep.c`, linked by CMake and SCons. The previous
native entity-distance loop in g_missile.c was removed.

Caller review: sorted `nitmod_client.c` calls the sweep with radius 256 and
the selected team, then calls nitmod_cp only on a nonzero result. The native
g_active.c callers similarly use the result only for the HQ proximity warning
and its last-report timestamp. Thus the constant false suppresses that warning;
it does not disable landmine explosions, spotting or map-marker handling.
The original disassembly epilogue was rechecked before implementation.

The typed adapter constructs origin +/- radius bounds, calls EntitiesInBox
with MAX_GENTITIES (1024) slots, ignores the result and returns qfalse. The
unused native team argument is retained. Eighty executable cases cover four
teams, five radii (including zero/negative), and query results 0/1/1024/-1.
The test checks exact bounds, one callback and full list capacity. Native and
WASM builds pass. Inputs used by the tests are finite and exactly representable;
no exhaustive x87 floating-point equivalence is asserted.

Native caller timing/eligibility gates are unchanged and still differ from
the original surrounding client logic. Query frequency and full gameplay
parity therefore remain unverified; no original-engine replay was performed.

## G_ExplodeSatchels

Symbol address `0x0008dd80`, size `0xe8` (232 bytes).
After invoking G_ExplodeMissile, it reloads the live list count then jumps
to the index increment:

```
8de4f: e8 7c b5 ff ff    call  893d0 <G_ExplodeMissile>
8de54: b8 01 00 00 00    mov   $0x1,%eax
8de59: 8b 93 8c 53 5c 00 mov   0x5c538c(%ebx),%edx
8de5f: 89 44 24 1c       mov   %eax,0x1c(%esp)
8de63: e9 58 ff ff ff    jmp   8ddc0 <G_ExplodeSatchels+0x40>
8ddc0: 46                inc   %esi
```

This confirms the increment-after-callback control flow. Skipping a shifted
entry follows if the callback compacts the list as reconstructed; a full
original-engine chain-reaction replay is still pending. The port's stable
snapshot is an intentional divergence, not claimed instruction parity.

`original_function_symbols.csv` pins complete function bytes by SHA-256.
`test_reference_symbols.py` reproduces that index, checks these symbol bounds
and pins the constant-zero epilogue bytes. It does not emulate instructions.
