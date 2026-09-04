# Shared weapon media registration

## Closed integration gap

The verified game/nitmod_weapon_paths.c table already contained 44 typed weapon
identities, including tripmine.weap, but cgame still had its own filename
switch. That switch omitted WP_TRIPMINE. The renderer and wire adapter could
refer to a typed tripmine without its media having been loaded.

CG_RegisterWeapon now uses NITMOD_WeaponPath for all 44 representable original
weapons. CMake and historical SCons both include the table in cgame. Scoped
variants share their media filename; the descriptor's alternate field selects
server gameplay sections and is deliberately not interpreted as a client
media section. Client parsing of both/both_altweap remains unchanged.

WP_MAPMORTAR retains its ET-native mapmortar.weap entry separately; it is not
an original Nitmod wire identity. WP_ARTY remains a no-file registration.
Unsupported entries retain diagnostics. Existing force/cache semantics remain.
CG_WeaponSelectable now rejects negative and out-of-range IDs before inventory
bit access or ammo-table lookups. In-range selection behavior is unchanged.

## Evidence and verification

- Original cgame CG_RegisterWeapon: local ELF symbol 0xc4580. Decompiled
  cgame_weapons.c maps original weapon 49 (0x31) to tripmine.weap.
- The existing weapon_paths_reference test verifies all 44 shared mappings
  against original qagame filenames and alternate selectors.
- Full-cgame tests now exercise registration of all 44 mappings plus native
  mapmortar, verifying source path, one open/close, media registration and
  suppression of a second non-forced registration.
- 44 weapons x 2 ownership states x 2 reserve-ammo states x 2 clip states x
  3 mounted states = 1,056 selection cases. Knife/pliers exemptions included.
- Negative, end-of-enum and INT_MAX IDs cannot register or select a weapon.
- Native build, all 89 CTest tests and WASM build/load/entrypoint probes are
  run for this change. Browser gameplay remains unverified.

No pak files or original binaries were modified. Loading tripmine media does
not constitute complete tripmine gameplay, weapon-bank integration, original
item-index parity or implementation of the four remaining poison/bomb weapons.
