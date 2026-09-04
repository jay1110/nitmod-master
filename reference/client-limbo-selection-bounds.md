# Bounded selection after weapon quotas

The legacy CG_LimboPanel_GetWeaponNumberForPos advanced a nested while loop
until it found an enabled index, without checking the class-list end. With
empty slots correctly classified as disabled, asking for a row beyond the
remaining enabled weapons could loop indefinitely. Previously the same path
could read out of bounds. The function now scans the finite class list once,
counts enabled rows and returns the existing default index 0 if not found.
This is a defensive correction, not a new original Nitmod feature.

Secondary row mapping now bounds the requested row by its slot count. Weapon
lookup rejects negative indices, unsupported slots and secondary indices past
the available choices rather than treating arbitrary numbers as akimbo choices.
Valid primary/secondary ordering, restriction fallback and default index stay
unchanged.

Tests cover all 16 combinations of the Soldier's four restricted weapons,
eight requested rows per mask, a spectator/all-disabled case, secondary bounds
and an unsupported slot. Requests are exercised through the real limbo helpers
after parsed # quota messages. Existing class/weapon protocol tests remain.

Reference review also confirmed that original rifle-grenade restrictions are
drawn separately: cgame_ui.c CG_LimboPanel_WeaponPanel_DrawWeapon tests original
KAR98/CARBINE wire IDs 22/23 against GPG40/M7 IDs 36/37, using
gfx/limbo/nadesoutofstock registered in cgame_client.c. They must not simply
disable the base rifle. The visual overlay is now implemented separately;
see client-rifle-grenade-card.md.
No pak files or original binaries were changed.
