# Active original skill and XP HUD

Source: `src_nitmod_decompiled/cgame/sorted/cgame_ui.c`,
`CG_DrawSkillLevels` (decompiler return-address marker 0x57f09).

The original layout is not the ET four-block skill meter. It draws three
13x13 skill icons at (32,387), (32,411), (32,435), with black offset shadows,
and numeric levels at (35,411), (35,434), (35,457). The rows are light weapons,
battle sense, and class skill. Mounted non-soldiers show heavy weapons in
the first row; soldiers keep light weapons. Raw decoded display levels 0..5
are used without changing the native gameplay level projection.

XP is drawn at (75,474), HP at (34,474), using the existing limbo font at
0.2 scale and the left aspect-ratio anchor. LMS omits this original block.
The ET protocol retains its existing HUD code.

Original snapshot offsets 0x108 and 0x11c are stats[3] and stats[8],
respectively: XP = high * 32768 + low. Snapshot transition highlighting now
compares the combined value, including a low-word rollover. Malformed values
outside signed int range saturate defensively rather than overflow.

The original mounted test uses global pm->ps; this port deliberately reads
the displayed, normalized snapshot instead, avoiding stale global prediction
state when following another player. Original persistant[12] is already mapped
to PERS_HWEAPON_USE by the snapshot adapter. EF_MOUNTEDTANK is bit 0x8000.

Tests cover both XP protocols, overflow, null input, all five classes and
mounted/tank row selection, alongside exhaustive seven-skill digit decoding.
Native and WASM compilation and module-load checks are not visual browser
parity. No asset, pak, menu, server wire format or original binary is changed.
