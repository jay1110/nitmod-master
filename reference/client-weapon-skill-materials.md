# Weapon skill material selection

Original CG_AddPlayerWeapon in sorted/cgame_ents.c uses client ability word
0x9598 bit 2 for the ammo-pack material, selecting the playerState client
for a view model and entity client for a world model (around lines 8419–8426).
Syringe material checks use word 0x9594 bit 8 in the world-model branch
(around 8205) and first-person branch (around 8669).

All four typed cg_weapons.c checks now call NITMOD_ClientSkillUnlocked with
Signals/1 or First Aid/3. Thus original skill masks control presentation even
when display levels disagree; ET retains its >= level behavior. The helper
also rejects invalid client indices. Existing shaders and geometry remain
unchanged; this does not implement new ammo/healing behavior.

Tests exercise both abilities for all 64 masks and client slots under both
protocols with deliberately contradictory native levels, plus invalid clients.
These test the predicate, not an original-engine visual replay; model rendering
and browser visual parity remain unverified. No pak files were changed.
