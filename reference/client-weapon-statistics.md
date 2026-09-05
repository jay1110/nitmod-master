# Original Nitmod weapon statistics

The original cgame ELF `aWeaponInfo` table at 0x12b0e0 contains 26 records
of 12 bytes. Its labels are now used by the original-protocol debriefing.
The decompiled `CG_Debriefing_ParseWeaponStats` consumes arguments 1..78
in shots/hits/kills triples; its next-stat iterator stops at 26.

Unlike ET 2.60's 22-category table, the original has no smoke category
after Syringe. Satchel therefore starts at index 15, followed by
G.Launchr, Landmine, MG-42 Gun, Garand, K43 Rifle, Poison, Bomb,
Tripmine, Poison Gas and Poison Gas Mine.

The client-private storage accepts all 26 categories. Original-protocol
parsing, display labels and scroll counting use that count together.
Native ET retains its 22-category layout and clears the unused tail.
No shared gameplay enum or qagame statistics format is changed.

Reception is transactional: incomplete payloads and negative counters do
not replace the last valid data. The dispatch test exercises both layouts,
every truncated prefix, all triples, tail clearing and scroll counts.

This ports statistics reception/presentation, not the missing gameplay of
the weapons named in the additional categories. Original-server browser
intermission comparison remains necessary.
