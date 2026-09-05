# Limbo secondary weapon unlocks

Original Limbo selection in sorted/cgame_ui.c tests bit 16 in client
offset 0x959c (Light Weapons) for akimbo and 0x95a0 (Heavy Weapons), plus
Soldier class, for the secondary MP40/Thompson. These are unlock masks,
not the displayed level fields. Both weapon count and row-to-weapon
selection now use the same typed unlock accessor.

Native ET keeps its level >=4 behavior through the accessor. Original
Nitmod uses the exact bit, including when displayed levels disagree.
Existing team/covertops pistol variants, preference restoration, selected
row validation and server team-command encoding remain unchanged.

Tests exercise all class/team combinations and 25 heavy/light combinations
for each protocol, including deliberately contradictory display levels on
original Nitmod. They verify counts, row mappings, invalid rows, saved
secondary preferences and selected-weapon fallback. This does not grant
server inventory, change prediction or port the missing weapon mechanics.
Pak/original artifacts are unchanged; browser/server comparison remains open.
