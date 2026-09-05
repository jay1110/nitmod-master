# Bomb projectile reconstruction

Source: original qagame `fire_grenade`, case 48 (`nitmod_unknown.c`),
`G_WeaponIsExplosive` case 65 (`nitmod_weapons.c`); original cgame
`Obituaries_killedby` case 65. Reference binaries remain unchanged.

The typed `fire_grenade(WP_BOMB)` factory now sets classname, missile/bounce
state, ownership, timed explosion, separate 0/350/300 damage defaults and
cached weapon-definition overrides. `g_damageweapons & 16` supplies 40 health,
the original (-11,-11,0)/(11,11,10) bounds and Nit_WeapDie behavior. Kick
bounds remain independent. Cooked fuses are consumed through the existing
factory path. Original explosive classification depends on `g_weapons & 16`,
not unconditionally on the bomb identity.

MOD_BOMB is appended, preserving existing native cause numbers. The ammo
record maps it back to WP_BOMB. Native obituary transport uses the established
safe-cause-plus-marker approach (grenade cause plus 0x4e470002); reconstructed
cgame restores Bomb text. Original-server cause 65 maps directly to MOD_BOMB.
This transport is a documented reconstruction choice, not original wire parity.

Tests exercise eight factory combinations (damage, kick, cooked fuse) and
client/server cause mapping. Direct obituary rendering still needs a broader
sound-capable client engine fixture.

The real `weapon_grenadelauncher_fire` adapter now includes the original bomb
throw policy: 900 speed factor, launch clearance (-12,-12,0)/(12,12,20), the
same clearance on startsolid recovery, and effect1Time=1. This launch box is
intentionally larger than the resting bomb's damage/kick box. Normal grenades
keep the small launch box. Poison bomb speed and poison mine clearance are
also mapped, but their incomplete factory/think paths are not activated.
`check_bomb_launch.h` exercises 36 real throw calls across six pitches, three
collision outcomes and bomb/grenade identities, including velocity magnitude,
trace arguments, ownership, fuse and presentation state.

Not complete: player weapon grants, FireWeapon/charge integration,
bomb-specific XP policy, and gameplay/browser explosion replay.
The factory alone does not make a localhost player able to select/fire a bomb.
No pak or asset modifications.

## Poison gas canister

Original weapon 50 / death cause 67 is now a typed WP_POISON_BOMB and
MOD_POISON_GAS path. It uses the recovered 900 throw factor, 20 direct gas
damage, radius 250, bouncing smoke entity and 16-second smoke lifecycle.
After the smoke radius becomes active, the server applies radius damage every
800 ms. `g_damageweapons & 64` independently enables the 40-health shootable
canister and `g_canisterKick` independently enables collision/kicking. Cgame
already renders the recovered poison smoke style; cause 67 and reconstructed
marker transport now produce the Poison Gas obituary. Shared pmove now predicts
the timed throw and emits the same fire event on client and server.

## Poison gas mine

Original weapon 51 now shares the normal landmine placement, collision,
registration, snapshot visibility and trigger pipeline. Its factory retains
the original five health, 32-unit bounds, team encoding and shootability while
using MOD 68. Once triggered it waits 1000 ms and enters the poison smoke
lifecycle instead of the ordinary 300 ms explosion path. Active gas deals the
recovered 20 radius damage within radius 250 every 800 ms. Cgame already uses
the separate poison-mine model, smoke tint and mine hint/visibility policy;
cause 68 now maps to its original poison-gas-landmine obituary. Shared pmove
now owns placement prediction on both cgame and qagame.

Poison syringe remains authoritative and is not enabled by this increment.

UI player-model previews resolve all private weapon identities through the
shared appended item records. Bomb, poison bomb, poison mine and tripmine now
retain their valid world model without probing a non-existent `_flash.md3`
companion or falling back to MP40. This changes UI code only; no assets or menu
files are modified.
