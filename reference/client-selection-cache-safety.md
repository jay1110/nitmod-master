# Client selection and animation-cache safety

This batch corrects typed ET integration defects; it does not claim new
Nitmod weapon gameplay or original UI completeness.

## Changes

- LastWeaponUsed, NextWeaponInBank and PrevWeaponInBank return when cg.snap
  is absent, matching the defensive entry behavior of the other weapon
  commands. Previously each dereferenced cg.snap before checking availability.
- WeaponBank rejects bank >= MAX_WEAP_BANKS_MP. Both lastWeapSelInBank and
  weapBanksMultiPlayer have ten rows, so bank 10 was an out-of-bounds access.
  This is a deliberate safety deviation: the decompiled original bank command
  also accepts values 1 through 10; reproducing an invalid access is not parity.
- CG_CheckForExistingAnimModelInfo clears sizeof(**animModelInfo), not
  sizeof(*animModelInfo). Its output parameter is a pointer-to-pointer;
  the old expression cleared only a pointer-sized prefix of a free slot,
  retaining stale animation tables and metadata after partial registrations.
  Matching complete cache entries retain their data. The helper is exposed
  internally in cg_local.h for direct testing, not exported as an engine ABI.

## Verification

Full-cgame regression coverage includes all eight weapon command entrypoints
with no snapshot, frozen-state smoke checks, six invalid bank arguments,
and valid bank-1 knife selection. State comparisons verify that rejected
commands do not change unrelated state; the existing bank-command selection
timestamp update is preserved.

Animation tests seed a reusable slot with nonzero bytes, verify the complete
typed structure is cleared, check a case-insensitive complete cache hit remains
unchanged, then simulate an incomplete registration and verify another reset.

Native build, all 89 CTest tests, WASM build and Node module/entrypoint probes
are run. No browser crash was reproduced, so these fixes must not be described
as proven explanations of the reported allocation/indirect-call failures.
Pak assets, original binaries and protocol identities remain unchanged.
