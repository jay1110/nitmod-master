# Client ammo warning

CG_CheckAmmo now lives with the other typed ammo handling in cg_nitmod_ammo.c.
The original cgame_client.c function sums reserve ammunition for owned weapons,
clears the warning at five rounds, selects state 1 for low reserves and 2 for
zero, and plays a local sound only when entering a warning from state 0.
Magazine ammo is not included; aliases are counted per owned weapon.

The original disassembly/decompilation masks the shift by 31 but reads only the
first ownership word, including for original IDs 32..51. The native port used
an undefined C shift with the same first word. This is deliberately corrected:
the active function reads weapon/32 and uses an unsigned weapon%32 shift.
This is NOT claimed as exact parity with that original bug. Negative reserves
count as empty, accumulation saturates at the threshold, missing snapshots
leave state unchanged, and nonpositive sound handles are not submitted.

The complete cgame-linked fixture tests every native weapon independently,
reserves -1..6, all three previous warning states and repeated observations.
It verifies sound handle/channel/count plus no weapons, INT_MAX reserve,
invalid sound handle and absent snapshot cases. Native and WASM builds share
this code. Gameplay replay against an original dedicated server remains open.
