# Active headshot definition options

Original G_Damage in sorted/nitmod_weapons.c consults HeadshotWeapon
(+0x684) using BG_WeaponForMOD. Yes=1 enables, no=2 disables and zero keeps
the built-in policy. Its head-damage branch reads minimum (+0x698) and
ratio (+0x69c) using the attacker's selected weapon, defaulting zero values
to 50 and 2 respectively, then selects max(minimum, scaled damage).

The live native IsHeadShotWeapon now checks the typed cached policy before
its existing fallback list. G_Damage uses the cached ratio/minimum at the
existing headshot multiplication point, before distance and helmet scaling.
No extra event, duplicate damage call or change to client hit feedback is
introduced. Cache loading/reset follows the existing map lifecycle.

Intentional hardening: extreme products saturate at signed-int bounds before
conversion rather than overflowing. No configured value is written back to
the original asset. The native default headshot list and hitbox detection
remain; original g_weapons additions and full hitbox parity are not claimed.

The loader/cache fixture exercises all three options, default/yes/no/invalid
policy, zero/nonzero ratios/minima, negative minimum, invalid identities,
map reset, overflow and preservation of no-I/O lookup behavior. These are
not complete shot/helmet/distance gameplay replays. UI/cgame are unchanged;
native and browser gameplay verification remains pending.
