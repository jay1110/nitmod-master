# Original unarmed selection sentinel

Original CG_WeaponSelectable in sorted/cgame_weapons.c initializes success
and only enters mounted/ownership/ammunition checks when the weapon is
nonzero. WP_NONE therefore means a selectable unarmed state. The typed
adapter now accepts it before those checks only for original Nitmod.
Native ET behavior remains unchanged. Actual weapon ownership is still
authoritative; this does not grant inventory or add missing private weapons.

Tests cover both protocols, mounted/unmounted state, unarmed selection,
invalid indices, unowned/empty/loaded MP40 and owned knife/pliers. Existing
out-of-ammo bank selection tests remain in the full suite. Browser gameplay
comparison is pending. No pak, server protocol or original module changes.
