# Weapon team media and presentation

Typed cgame implementation; no changes to pak, shared weapon IDs, server
commands or original reference artifacts. These are presentation prerequisites,
not implementation of the remaining poison/bomb gameplay.

## Evidence

The decompiled client weapon parser supplies the following weaponInfo offsets:

| Fields | Original offsets | Typed storage |
| --- | --- | --- |
| pickupModel, axisPickupModel, alliedPickupModel | 0x5f0, 0x5f4, 0x5f8 | weaponModel[W_PU_MODEL].model, pickupTeamModel |
| pickupSkin, axisPickupSkin, alliedPickupSkin | 0x5fc, 0x600, 0x604 | weaponModel[W_PU_MODEL].skin |
| missileModel, AxisMissileModel, AlliedMissileModel | 0x171c, 0x1720, 0x1724 | missileModel, missileTeamModel |
| allied/axis missile override present | 0x1790, 0x1794 | missileTeamModelDefined |
| weaponIconScale, foreShorten | 0x1798, 0x179c | named integer and float |

Consumers were also inspected with llvm-objdump in the supplied ELF
`original_nitmod_shared_objects_32bit/cgame.mp.i386.so`:

- CG_Item at 0x57e40: loads generic pickup model/skin at 0x58406/0x58419;
  axis overrides at 0x587de/0x587f9, allied at 0x58830/0x5884b.
- CG_Missile at 0x55a20: generic model at 0x55bea; allied presence/model
  at 0x565de/0x565ed, axis presence/model at 0x5664e/0x5665d.
- weaponIconScale at 0x66aa0 reads 0x1798 at 0x66abb. Zero selects the
  stock narrow/wide classification, nonzero is returned unchanged.
- CG_AddViewWeapon at 0xccf90 reads 0x179c at 0xcd31a; zero leaves axes
  unchanged, otherwise scales the forward axis and marks nonNormalizedAxes.

These ELF addresses are not interchangeable with addresses embedded in the
decompiled listing, which uses different function addresses.

## Behavior

Pickup model and skin fall back independently to generic values for missing
team handles. Only Axis/Allies index the three-entry tables. The entity's
explicit modelindex2 override retains precedence. Medkits use weapon pickup
media, as in the original consumer.

Missile override presence is distinct from handle validity: a specified team
model whose registration returns zero remains zero, not the generic model.
Dynamite and landmine team flags are reduced modulo four. Existing special
projectile render paths retain precedence. Poison-mine handling remains open
because it has no typed weapon implementation yet.

weaponIconScale reaches the HUD weapon icon sizing helper; foreShorten reaches
the hand entity before CG_AddPlayerWeapon. Neither changes player movement,
hit detection or projectile physics.

Also corrected the pre-existing pointer-sized memset in CG_RegisterItemVisuals:
the complete itemInfo_t is cleared on registration, preventing stale handles
in reused unregistered slots. This is defensive initialization, not proof of
the cause of any reported browser crash.

## Verification and limits

The full-cgame fixture test_original_charge_dispatch exercises eleven media
registrations, all new tokens, zero missile handles, invalid/non-team values,
independent pickup fallback combinations, mine/dynamite team flags, explicit
and default icon sizes, forward-axis scaling and reload resets. Every weapon
item slot is additionally checked for complete initialization.

Native build, all 89 CTest tests, WASM build and Node module loading/entrypoint
probes are run for this batch. Node probes are not browser gameplay tests.
Real-server join/render comparison is still required. The subsequent smoke and
offset batch is documented in client-weapon-smoke-offset.md. Recoil settings
remain unmapped; accepting them without their original consumers would not
establish functional parity.
