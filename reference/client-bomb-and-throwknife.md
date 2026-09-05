# Bomb inventory and original-server throw-knife fallback

## Evidence and implementation

- Both hash-pinned original ELF32 item tables identify weapon 48 as `weapon_bomb`,
  pickup name `Bomb`, with independent ammo/clip slot 48. Its item index is 54:
  qagame address `0x2a6570`, cgame address `0x12f8d0`.
- Original cgame bank table at `0x12e7a0` places it after Axis/Allied grenades in
  bank 4. Native `WP_BOMB` is appended at 50, leaving all existing native IDs
  intact. Snapshot inventory, ammo, heat, weapon selection and outgoing command
  mapping translate original 48 to/from this private native identity.
- `bomb.weap` is registered through the existing typed weapon-file parser;
  the original PK3 supplies hand/world models and animations. Item index 54
  now resolves to a typed bomb item rather than disappearing. Bomb has no
  muzzle flash. No assets or original reference binaries were modified.
- The original bomb defaults are 1/1/1 ammo/uses/clip, starting reserve 0,
  starting clip 1, reload 1000 ms, fire delay 250 ms, shot interval 1600 ms,
  heat/cooling 0. Both ELF tables verify these values. Bomb reload suppresses
  the body reload event, as does original weapon 48.

## Throw knife / prediction boundary

Original cgame `PM_Weapon` tests `WBUTTON_ATTACK2` and held `grenadeTimeLeft`;
the release path at `0x1b588` selects weapon animation 4 (`WEAP_ATTACK_LASTSHOT`).
The unchanged knife asset separates stabbing from hold/release frames.
ET's generic weapon predictor must not manufacture a stab before this throw.

On original servers only, `pmove_t.nitmodAuthoritativeWeapons` makes `PM_Weapon`
retain authoritative weapon state during bomb use and knife alternate attack,
held-throw state, or throw hold/release animations. Normal knife primary attack
and other weapons retain prediction; movement and outgoing input are untouched.
This is a server-authoritative compatibility fallback, not the complete original
throw-knife/bomb prediction state machine. Input feedback may incur network latency.

The localhost qagame entity now also reproduces the original typed ownership and
trajectory fields: it is broadcast, records owner client/team, uses configured
knife damage and `TR_GRAVITY_LOW`, and remains a live pickup for 20 seconds.

## Remaining work and validation

- Bomb selection requires the server to grant ownership and ammo. No forced
  loadout, bomb damage/explosion logic or localhost qagame granting was added.
- Follow-up: poison syringe (47), poison bomb (50), poison mine (51) now have
  typed selectable client inventories; see `client-poison-weapons.md` for scope
  and remaining authoritative/local-server gameplay work.
- The shared engine player-state weapon arrays remain 64 slots. All three
  reconstructed modules must be rebuilt together after this private enum change.
- Tests cover all bank orders against original bytes, both bomb item identities,
  ammo/defaults/aliases, bank-4 cycling and empty-bomb skipping, snapshot/input
  translation, animation condition separation and the knife prediction gate.
- Native test suite and WASM load/ABI smoke tests do not replace a dedicated-server
  browser test of selection, throwing, switching back and rendering.
