# Precise landmine contact policy

Original sEntWillTriggerMine is ELF 0x8e180 (0x1ee bytes). Typed port lives in
game/g_nitmod_mine_contact.c, linked by CMake and SCons. Existing G_LandmineThink
and LandminePostThink call it; their separate filtering/queue logic is unchanged.

The original Cvar table record for n_preciseLandmineTrigger has default "0",
flags 1 (CVAR_ARCHIVE), no change tracking or reset. Its native registration
now matches that hash-pinned record. Default zero selects the previous 64-unit
spherical contact test with strict vertical distance below 45. The same broad
test applies if the mine's onFireStart latch is nonzero or playerState.eFlags
contains any bit in 0x880001. The native names are EF_DEAD, EF_PRONE, EF_SPARE0;
no undocumented Nitmod meaning is assigned to the reserved bit.

The precise branch subtracts mine mins/maxs from mine origin, then player
origin. It is not a bounds-center calculation. For horizontal axes the original
adds/subtracts 3 and truncates toward zero via x87 control-word bits 0xc00 before
accepting integer results [-23,23]. Ghidra's ROUND rendering is misleading here.
For finite inputs this accepts the open interval (-24,24), which the port checks
directly, avoiding undefined integer conversion for NaN/overflow. Vertical
separation uses origin-mins-maxs-playerOrigin and strict absolute value below 45.

The port uses double intermediates for the precise calculation; exact x87
extended-precision behavior for pathological/extreme coordinates is not claimed.
Null entity/mine pointers reject defensively. No private weapon variant, friendly
fire policy or caller-level rules from original G_LandmineThink are inferred.

Tests cover 400 option/latch/flag/axis/boundary combinations, vertical boundaries,
asymmetric bounds, non-player/client-null and null-pointer guards. Original byte
checks pin the flag mask, truncating rounding mode and comparison constants.
The compiled ET/Legacy layout probe adds playerState.eFlags at offset 104 (size 4),
bringing its comparison to 61 rows. No entity layout or wire command is changed;
cgame/ui need no new parser for this server-side contact policy.

Native and WASM builds, 81 CTests and protocol checks pass. Actual original-engine
contact replay, map geometry, visibility and browser gameplay remain outstanding.
