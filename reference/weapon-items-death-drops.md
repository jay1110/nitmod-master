# `g_weaponItems` death-drop subset

Recovered `TossClientItems` reads three independently typed bits before
intermission: bit 1 drops the current primary weapon, bit 2 drops binoculars
when owned, and bit 32 drops the knife when its clip count is greater than one.
When the low two `g_dualSMG` bits both are set, the primary lookup/drop is
performed a second time after the first weapon has been removed.

These reads are now active in qagame with bounds-checked `weapon_t` values.
Original `gentity+0x39c` was also proven to be the dropped weapon's reserve
ammo. It is represented by server-only `nitmodDropAmmo`: bit 4 transfers it,
and bit 16 leaves an already-owned pickup in place if clip, reserve and
alternate ammo are all unable to add ammunition. Bit 8 performs the original
ammo-only pickup: it emits normal/quiet pickup feedback, clears all three ammo
quantities and retains the empty weapon entity. Binoculars are excluded from
that branch as in the recovered function.
