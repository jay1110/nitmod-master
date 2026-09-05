# Active original cg_gibs effect control

The original cgame uses cg_gibs (default 1, archive) in CG_Bleed (ELF
0x52850), CG_LaunchGib (0x52c50), CG_GibPlayer (0x53550), CG_BloodTrail
(0x7d2f0) and both CG_Bullet blood branches (0xd26d0). The native ET code
still checked cg_blood at these six sites, making the registered Nitmod
setting ineffective. All six now use the original control; screen damage
blend/flash and blood mark duration remain separate settings.

CG_LaunchGib now uses the recovered 40000 +/- 5000 ms lifetime rather than
ET's 20000 +/- 5000 ms. This does not claim identical RNG sequences or x87
rounding. Bleed rejects absent snapshots and out-of-range entity IDs, and
gib launch rejects a missing owner before dereferencing it. Hat loss remains
outside the gib switch, as in the original. Already-created fragments are
not deleted when toggling the setting off.

The linked cgame fixture tests cg_gibs -1/0/1 crossed with cg_blood 0/1,
fragment allocation and fields/lifetime, disabled bleeding/gib/trail paths,
and absent snapshot/owner handling. Bullet geometry, renderer screenshots,
full corpse-model parity and the remaining effect differences are not covered
by these tests. No qagame protocol or pak/menu/asset changes were made.
