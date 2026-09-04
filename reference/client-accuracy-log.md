# WeaponStats accuracy log

The original CG_ServerCommand WeaponStats branch differs from native ET:
it traverses 52 original weapon IDs using BG_ValidStatWeapon, then consumes
suicides, objective count and player/team objective pairs. It does not contain
the four native ET hit-region counters. Those are delivered separately by imhr.

CG_ParseAccuracyLog now separates these variants, translates weapon identities,
consumes unsupported weapon triples without overwriting WP_NONE, bounds the
objective count by both destination arrays, and commits only after complete
numeric parsing with no missing or extra arguments. Signed counters are retained.
Invalid packets leave the previous snapshot unchanged. Native qagame's existing
WeaponStats producer remains unchanged and matches the native branch.

The original weapon filter is reconstructed from cgame_bg.c BG_ValidStatWeapon;
the reference test verifies selected IDs against hash-pinned original ELF item
records. Source-contract tests and builds are not gameplay/replay parity proof.
Unsupported original weapon counters are consumed but not displayed.
