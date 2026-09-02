# Outer reload decision

NITMOD_DecideReload translates the inspected PM_CheckForReload branches into
a read-only decision: NONE, BEGIN or UNSCOPE with an explicit native weapon.
It excludes GPG40/M7 and accepts the mapped ready/normal-fire/alternate-fire
states. The inventory predicate retains manual versus automatic akimbo rules.

Original qagame PM_CheckForReload is at 0x2a7a0, cgame at 0x19c80. The
scoped branch (original IDs 39..41) executes before the weaponTime gate:
manual request, reserve and under-capacity clip are required. Scoped ability
bit 0x20 (qagame pm +0x13c) OR war mode exactly 2 chooses direct begin;
otherwise PM_BeginWeaponChange requests the alternate weapon with reload
intent. Native targets are GARAND_SCOPE -> GARAND, K43_SCOPE -> K43,
FG42SCOPE -> FG42. Evidence: qagame 0x2a870..0x2a8da, cgame
0x19d50..0x19dbd. The MG42 ability word is a DIFFERENT word despite using
the same bit number. Automatic-only requests never select either scoped path.

Non-scoped requests require weaponTime <= 0 (qagame 0x2a848..0x2a84d),
then the previously tested manual or enabled automatic inventory predicate.
No extra weaponDelay or noWeapClips gate is invented in this decision: the
inspected original function does not contain the native stock noWeapClips
early return. Surrounding caller constraints still need integration.

The caller must resolve manualRequested (including the original attack-key
option) and automaticAllowed from the recovered settings/weapon flag. This
change does not infer these values from ET skill levels or stock ammo fields.
Bad pointers/unknown weapon/short table reject without writing the decision;
inventory sentinels rejected by the inventory predicate result in NONE.
Unmapped/blocked weapon states return NONE, not a raw original-state test.

28512 combinations cover 44 identities, three times, manual/automatic request
flags, scoped ability on/off, war modes 1/2/3, empty/partial/full inventories
and ready/alternate-fire/reloading states. Both akimbo clips are initialized;
the earlier predicate tests cover asymmetric pairs. Whole-state comparisons
verify no mutation. Invalid API inputs leave output unchanged.

No weapon-change callback or active PM_CheckForReload hook is installed.
BEGIN is input for the composed begin adapter; UNSCOPE still requires the
engine weapon-change path preserving reload intent. Live request/settings,
ability synchronization and engine replay remain open work.
