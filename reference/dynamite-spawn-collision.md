# Dynamite initial collision contents

The original ELF symbol fire_grenade is at 0x8e480 (size 0xe7f). Its dynamite
branch names the entity dynamite, uses MOD value 0x15, initializes health 5,
disables takedamage, and uses bounds (-12,-12,0) to (12,12,20). These identify
the native WP_DYNAMITE branch without relying on equality of private weapon
enumerations. The sorted pseudocode's address labels are not literal addresses
in the supplied ELF; evidence here uses objdump's ELF symbol/addresses.

At ELF 0x8f246, `mov eax,0x04000000` is followed by the health store and then
`mov [esi+0x14c],eax` at 0x8f251. This is the same contents field mapped in the
previous projectile ports: CONTENTS_BODY, not CONTENTS_CORPSE (0x02000000).
The native dynamite branch already has matching health, takedamage and bounds
but previously assigned corpse contents. That single production assignment is
now corrected. It is unconditional at spawn, not an extra g_damageweapons bit,
and does not make dynamite damageable. No new client message is introduced.

tests/test_weapon_cvars_reference.py pins the original artifact via the
existing SHA-256-checked extractor, maps virtual addresses through the ELF
section table and checks the exact 17 instruction bytes at 0x8f246. Source
checks require the body assignment, retained 5 HP and takedamage=false, and
absence of a g_damageweapons condition in this branch. This is a narrow
instruction/source regression check, not executable engine collision parity.

The change affects engine collision classification; actual player blocking,
throw trajectories, settling and later arming transitions still require a
map/engine replay. Original private damage/radius tables and Nitmod print
message handling in the same branch are not reconstructed here. Masks 0x10
(bomb) and 0x40 (poison bomb) remain unported rather than being mapped to
dynamite. Native and Emscripten builds pass, all 80 host CTests pass.

## Landmine and satchel spawn contents

The adjacent original branches establish the same initial contents for native
landmines and satchels. At 0x8f12d/0x8f132 (landmine) and 0x8ee09/0x8ee0e
(satchel), the original loads 0x04000000 and stores it in the mapped contents
field. The hash-pinned reference test now checks each exact 11-byte pair and
requires a single CONTENTS_BODY assignment in each corresponding native branch.

Both native assignments previously used CONTENTS_CORPSE. They now use BODY.
Landmines retain health 5, takedamage=true, team ownership, bounds, registration
and snapshotCallback=true. Satchels retain baseline health 5/takedamage=false,
the independent mask-2 damage helper, bounds and registration. Initial satchel
contents are BODY whether the damage option is enabled or disabled; the
already ported death callback later changes them to CORPSE. These corrections
do not extend the existing damage masks or map the extra original mine variant.

The regression checks cover original instructions and production source hooks;
they do not execute fire_grenade in an engine. Throw/settle behavior, later
arming-state collision and client prediction remain live-replay obligations.
Native/WASM builds and all 80 CTests pass; no wire-protocol changes were made.
