# Active medic primary suppression

SetWolfSpawnWeapons reads the existing registered g_medics options for medics.
Bit 4 suppresses their primary MP40/Thompson grant. Medical tools and grenades
remain; the granted native pistol or Akimbo pair becomes selected instead.
Native skill-based secondary selection is retained, not claimed as original
arbitrary ability-table parity. Knife-only mode remains unchanged.

Evidence: original G_AddClassWeapons at ELF 0x4ba20, nitmod_weapons.c:
the selected secondary is granted first, then the primary grant is conditional
on class != medic OR !(g_medics & 4). The subsequent dualSMG branch is
independent and uses the intended primary identity, not the selected pistol.
The port preserves that distinction: enabled dualSMG still grants the opposite
SMG with the existing medic reserve policy, without selecting it.

Full qagame tests execute the actual spawn function across both teams,
g_medics 0..7, dualSMG off/on and native single/Akimbo selection. They check
primary/extra ownership, selected weapon, syringe and medkit retention.
Only the spawn effect of bit 4 is activated here: custom pickup class masks
can override original medic pickup policy and remain a separate open task.
No pak assets or network layout changes; browser gameplay remains unverified.
