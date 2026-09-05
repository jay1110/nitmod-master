# XP decay runtime

Original qagame function `G_XPDecay` at ELF address `0x000df300` is now mapped
to typed ET 2.60 client session fields. `ClientEndFrame` invokes it at the
original 60-second boundary when option bit 1 is enabled.

The recovered option mask is:

- bit 1 enables decay;
- bit 4 protects the player's current class skill;
- bit 8 protects spectators;
- bit 16 permits decay only while the match is playing;
- bit 32 restricts decay to spectators while the match is playing;
- bit 64 protects Battle Sense;
- bit 128 protects Light Weapons.

The loss per pass is `60 * g_XPDecayRate`, clamped to
`g_XPDecayFloor`. Skill levels and active-team aggregates are recomputed after
each loss. Spectator decay deliberately does not index the two-column team XP
array. LMS remains excluded, matching the original.
