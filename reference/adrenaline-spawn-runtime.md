# Adrenaline spawn integration

The recovered adrenaline helpers are now part of `SetWolfSpawnWeapons` rather
than isolated, uncalled code. First Aid level 2 supplies original unlock bit 2
(the two-clip resource bonus), and level 4 supplies original unlock bit 4 (the
adrenaline reward). `g_adrenClasses` maps Soldier/Medic/Engineer/Field Ops/
Covert Ops to bits 1/2/4/8/16, with the original default `2` remaining Medic
only.

`g_adrenaline` controls the recovered initial-clip variants and the configured
war mode keeps its original suppression. Knife-only retains its pre-existing
special Medic loadout. All inventory writes use the independent typed
`WP_MEDIC_ADRENALINE` ammo and clip slots.

Active, non-limbo players are also reconciled during ClientThink. Losing the
level-4 reward or the configured class bit removes only the adrenaline weapon
ownership bit; it does not corrupt syringe ammunition, cancel an already
active powerup or invent a mid-life grant.
