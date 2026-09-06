# Knife ammunition layout audit

Original qagame and cgame ammoTableMP weapon 1 agree:
maxammo=8, maxclip=8, starting reserve=0, starting clip=4, uses=0.
Verified with tools/extract_weapon_ammo.py against its SHA-256-pinned binaries.

Original Pickup_Weapon (sorted nitmod_weapons.c) rejects pickups when
client+0x294 exceeds 7. BG_AddMagicAmmo accesses clips at playerState+0x290;
this is knife clip slot 1, not reserve slot 1 (reserve base is +0x190).

Current port discrepancies, NOT fixed by this audit:
- Pickup_Weapon tests ps.ammo and Add_Ammo credits reserve.
- PM_NitmodThrowKnife consumes ps.ammo.
- Spawn calls AddWeaponToPlayer(client, WP_KNIFE, 1, 0, qtrue).
- Snapshot translation keeps ammo and ammoclip separate, without a knife swap.
- The static native knife table still has legacy 999 capacity; runtime weapon
  table initialization must be checked before changing defaults.

Required atomic follow-up: inspect original Add_Ammo knife branch, align spawn,
pickup, refill, throw and HUD on clip storage, update source tests which currently
pin the reserve implementation, and test original-server snapshots plus localhost.
Do not compensate by swapping the original snapshot arrays: preserve wire meaning.
