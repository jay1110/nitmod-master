# Weapon flash smoke and view offset

## Implemented

The client weapon parser now consumes offset (three floats), flashSmokeShader,
flashSmokeLife (integer), flashSmokeAlpha and flashSmokeSize (floats).
Storage belongs to weaponInfo_t and is cleared by its existing registration
reset. No shared gameplay structure, protocol number or asset file changed.

CG_AddViewWeapon adds the weapon offset to cg_gun_x/y/z before applying the
current view axes and FOV offset. The user's cvars are not modified.

CG_AddPlayerWeapon invokes the custom smoke emitter at the existing barrel
smoke point, preserving the surrounding first/third-person and flash-time
gates. It uses CG_ParticleImpactSmokePuffExtended with velocity 8, acceleration
20 and max roll 30. A custom shader enables this path; zero numerical fields
default independently to life 500 ms, alpha 0.25 and size 8.

Without a custom shader only STEN emits here, with age strictly below 100 ms
and all three fixed defaults, even if numerical custom settings were supplied.
Custom-shader STEN uses the custom/defaulted values just like other weapons.
The existing cg_smokeparticles gate still prevents particle allocation.
Overheat smoke, panzer smoke and mortar smoke remain separate existing paths.

## Original evidence

Decompiled parser: cgame_weapons.c, fields 0x177c (shader), 0x1780 (size),
0x1784 (life), 0x1788 (alpha), 0x17a0..0x17a8 (offset).
Decompiled consumers: cgame_ents.c, CG_AddPlayerWeapon/CG_AddViewWeapon.

Also checked the supplied cgame.mp.i386.so with llvm-objdump:

- CG_AddPlayerWeapon reads shader at 0xcb1bb, alpha at 0xcb1d4 and addresses
  size/life at 0xcb1fe, matching the field grouping and defaults above.
- CG_AddViewWeapon reads offset components at 0xcd165, 0xcd17a and 0xcd187;
  addition of y/z offsets is visible at 0xcd1cc/0xcd1d5.

These addresses refer to the local reference ELF, not the decompiler's
different function address layout.

## Tests and remaining work

The full-cgame fixture parses all five fields, verifies offset addition with
aliased input/output, and checks registration reset. Smoke tests cover 192
combinations (eight default masks, two weapon classes, shader absent/present,
ages 99/100/101), each with particles enabled and disabled. They verify
resolved parameters and actual free/active particle list transitions.
Seven malformed/truncated new-field cases run 100 times each and check source
closure and diagnostics.

Native build and 89 CTest tests, WASM build and Node loading/entrypoint probes
are used for verification. These do not establish complete original render
parity or a successful real-server browser join. The recoil fields and new
poison/bomb gameplay remain separate outstanding reconstruction work.
