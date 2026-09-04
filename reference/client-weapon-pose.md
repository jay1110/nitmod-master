# View weapon pose and snapshot weapon states

## Evidence and actual changes

Original cgame ELF CG_CalculateWeaponPosition 0xbf590 (Ghidra 0xcf590)
is implemented with typed cg_t/playerState_t/refdef_t inputs in
src_2.60/cgame/cg_nitmod_weapon_pose.c. The real first-person weapon path
selects it only for the original Nitmod protocol; et260-layout servers keep
the existing path. Both normal and alternate view-weapon model calls use it.

New behavior relative to the previous port:

- g_weapons bit 256 uses the original right-vector lean offset (lean / 8)
  without normal lean roll/pitch changes.
- Alternate firing suppresses the visual lean adjustment.
- Normal lean preserves fractional pitch movement (fabs rather than abs).
- Snapshot weaponstate 5/6/7 becomes typed WEAPON_FIRING/FIRINGALT/RELOADING.
  Previously only weapon IDs and inventories were translated, leaving these
  states interpreted as READYING/RELAXING/FIRING by native code.

The original PM_Weapon call to PM_AltFire at ELF 0x1c0c4 branches to the
state-6 write at 0x1c27c or state-5 write at 0x1c0d9. PM_BeginWeaponReload
(0x17c40) writes state 7 at 0x17db5..0x17dbc. This establishes all three
translations without guessing from enum names. Unchanged states pass through.
Translation happens once after trap_GetSnapshot in CG_ReadNextSnapshot,
only for original servers. Reconstructed qagame uses et260 layout and retains
native enum values. No engine ABI or outgoing user-command layout changed.

The extracted pose also retains existing mounted pitch, deployed mortar/MG42
pitch, prone transition, bobbing, landing, idle drift and kick subtraction.
These are verified existing behavior, not newly added gameplay features.
Deliberate deviation: time arithmetic widens before subtraction/addition;
negative prone-return and landing ages after clock resets do not extrapolate.

CG_WeaponFireRecoil (original ELF 0xcde60) already matches the native switch,
random draw count and 32767 divisor. The production function is unchanged;
new tests verify it instead of introducing a redundant implementation.
This is visual kick, not the separate weapon-definition movement recoil system.

## Verification and limits

The full cgame fixture checks all native weapon IDs across 2 lean modes,
10 weapon states and 3 lean directions; 52 prone/bob/landing timeline cases;
12 mounted/deployed/third-person cases; 32 recoil seeds per native weapon,
including unsupported weapons leaving kick unchanged and consuming no RNG.
Snapshot tests exercise states -1 through 10 and all existing weapon mappings.
Full native CTest, WASM build and Node loader/entrypoint smoke checks run.
These are deterministic reconstruction fixtures, not original-binary replays.
Live dedicated-server/browser animation parity and the full port remain open.
No pak assets, original binaries or menus are modified.
