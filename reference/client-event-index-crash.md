# Dedicated-server WASM event-index investigation (2026-09-03)

## Evidence and scope

Reported stack: `CG_EntityEventForProtocol -> CG_EntityEvent ->
CG_CheckEvents -> CG_TransitionSnapshot`, preceded by invalid sound handles.
The user no longer has the loaded historical WASM artifact. Its exact faulting
instruction and a successful live reconnect therefore remain unverified.
The missing `nkey.dat` diagnostic is a separate identity-provisioning limitation.

Original reference: `original_nitmod_shared_objects_32bit/cgame.mp.i386.so`,
SHA-256 `45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f`.
No original binary or `pak` content was edited.

## Identified defects and changes

- Dispatch translation previously stopped at wire ID 64. Original 65–93
  were mostly dispatched as unrelated native ET IDs. For example, original
  82 (gun sparks) became native explode, 83 (flame effect) became rubble,
  and 86 (camera shake) became weapon spinup. These are verified enum
  collisions, not proof of which event triggered the reported crash.
- Extend the dispatch table through 93 using original name pointers at ELF
  `0x1346c0` and jump offsets at `0x105370` (base `0x12dc44`). The corresponding
  cases in `sorted/cgame_events.c` establish the called effect handlers and
  payload fields. Snapshot IDs/repetition bits remain unchanged. Original
  temporary events 67/70/71 now translate their weapon and nextWeapon fields;
  effect payloads overloading those fields are left untouched.
- Validate sound-table indices, grenade surface IDs, effect material IDs,
  weapon IDs, debris models, and explode/rubble custom sound indices before
  access. Negative fire-weapon IDs previously could reach an out-of-bounds
  weapon record and its brass-ejection function pointer.
- Share bounds-checked mounted-tank parent traversal between firing,
  overheat and echo paths. An invalid chain falls back to the ordinary tank
  gun sound rather than dereferencing an invalid parent.
- Replace three `random() * fxSounds[material].max` selections with bounded
  integer selection. ET's `random()` can equal 1; the old expression then
  selected index `max`, reading uninitialized entries/pointers and potentially
  writing outside `sound[3]`. Nonpositive material handles are not played.
- Reject zero/negative shake radii to avoid division by zero.

## Verification

- ELF test checks all 93 original event names and dispatch entries, including
  the seven reserved original IDs (still explicit errors).
- Whole-cgame harness exercises malformed original/native/predicted event
  indices (negative, exact upper bound, INT_MIN, INT_MAX); invalid material,
  custom sound and model IDs; and mounted-parent bounds.
- 393,216 valid material-sound events must remain within the registered sound
  set of their material. Original and native panzer spinup must both play the
  selected weapon's sound. Temporary and attached 67/70/71 events translate
  weapon IDs; 82/86 do not.
- Native CMake/CTest and WASM build/load checks are run for this change. The
  WASM load harness checks exports/callbacks, not a dedicated-server session.

## Still open

Full payload/gameplay parity is not established by dispatch coverage. In
particular original artillery/airstrike chat additions and complete popup
presentation remain pending. Original IDs above 93 still need a complete
typed dispatcher beyond the existing special handlers. These changes are
not a claim that the entire Nitmod port or all join-time crashes are fixed.
