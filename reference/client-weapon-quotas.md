# Original-server limbo weapon quotas

Original CG_LimboPanel_RealWeaponIsDisabled, ELF 0x77ce0; split reference
cgame_ui.c. Field mapping is established by nitrox game-state parsing in
cgame_nitrox.c: the first six # fields are panzerRestriction and five weapon
limits, field 14 is weapons. Reference original cgame SHA-256:
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.

The already parsed typed snapshot now feeds both indexed and direct limbo
restriction checks. Panzerfaust, mobile MG42, flamethrower, mortar and both
rifle-grenade weapons obey their per-weapon maximum; -1 is unlimited, other
limits reject when current/latched teammate weapon count reaches the maximum.
Panzerfaust also checks teamCount/(maxclients*0.5) <= restrictionPercent*0.01.
STEN remains available to Covert Ops; other classes require weapons bit 512.
MP40/Thompson have no added quota. Existing heavy-weapon percentage checking
still runs first. Indexed checks now delegate to the same direct function.

Changes are original-protocol-only and start after a valid # snapshot; clearing
configuration clears that gate. No qagame message format or pak asset changes.
The maxclients=0 division is defensively skipped. Existing team counting and
heavy-weapon classification are retained, not claimed as fully reconstructed.
Rifle selection's translation to rifle-grenade restrictions and all original
skill/unlock/display rules still require further work.

Tests parse actual # snapshots then call real limbo checks: six weapons,
six limits (-2..3), three teammate/current-or-latched counts; all five classes
for STEN, enabling bit 512, indexed Medic STEN selection, MP40 exemption,
panzer ratio bounds and cleared-state gating. These complement the existing
class-list tests. Native/WASM builds and Node ABI tests do not establish live
server spawning or browser visual parity.
