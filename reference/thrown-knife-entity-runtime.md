# Thrown-knife entity reconstruction

Original qagame `ThrowKnife` at the recovered decompilation constructs an
`ET_ITEM` with the normal knife item index, `Touch_Item_Auto`, `Use_Item`, an
active pickup bit and `FL_DROPPED_ITEM`. Its trajectory is `TR_GRAVITY`, starts
50 ms in the past, uses full `EF_BOUNCE`, collides with solid, missile-clip,
body and corpse contents, and expires after 20 seconds.

The reconstructed implementation uses `LaunchItem` only for safe allocation,
origin validation and item linkage, then replaces every generic-drop field
which differs from those observed values. Pickup quantity is the configured
knife `maxammo`, including a value loaded from a custom weapon definition.

Original `Pickup_Weapon` treats `WP_KNIFE` specially before the generic
`g_weaponItems` branches. A pickup restores exactly one knife and is rejected
when the dedicated ammo slot already contains eight. Shared cgame/qagame
prediction consumes that same slot on the attack-2 edge and refuses empty
throws. The thrown entity keeps
`count` zero because that field represents transferred firearm clip ammo, not
the number of recoverable knives.
