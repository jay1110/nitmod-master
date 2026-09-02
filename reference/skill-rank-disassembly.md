# Skill rank: original i386 evidence

Reference: `original_nitmod_shared_objects_32bit/qagame.mp.i386.so`, SHA-256
`84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49`.
Addresses below are ELF virtual addresses, not Ghidra's rebased addresses.

`rankTable` is a 44-byte .data symbol at `0x002ab360`. Eleven signed
little-endian integers are `1,2,3,4,5,7,9,11,14,17,20`.

`G_CalcRank` (`0x000b7010`, 0x156 bytes) clears rank at client offset
0xc4c, invokes G_SetPlayerSkill for seven skill indices and sums the numeric
levels at 0xc30..0xc48. At 0xb705d the table is addressed using PIC base
0x2a4614 plus 0x6d4c. The highest read is table+0x24 (17), yielding rank 10.
Descending comparisons select ranks 9..1; sum zero leaves rank zero.
No read at table+0x28 occurs: the trailing 20 does not create rank 11.
The rank-seven store reuses esi=7 from the completed seven-skill loop.

`G_UpgradeSkill` (`0x000ce310`, 0x4da bytes) invokes the Lua upgrade hook
before normal processing. At 0xce373..0xce3a7 it sums the same seven levels,
clears rank, then compares the same table, starting with PIC+0x6d70 at
0xce3ab. Afterwards it updates userinfo and applies ability-specific changes.
These side effects are not part of the recovered numeric helper.

`NITMOD_CalculateRank` implements the sum and ten comparisons with typed
levels 0..5. Invalid levels or pointers are rejected without modifying the
output; this is deliberate hardening. There is no old-rank retention.
Native G_CalcRank/G_UpgradeSkill remain unchanged until coordinated skill,
Lua, userinfo and ability integration. The helper is not gameplay-active.

Verification: C test covers all 6^7 = 279936 level combinations, every
possible total 0..35 and invalid arguments. A separate Python test reads the
hash-pinned ELF table and compares all 36 totals against the compiled helper.
The ten-entry boundary is established by disassembly, not merely symbol size.
This is numeric/data evidence, not original-module execution or replay parity.
