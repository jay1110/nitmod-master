# Disguised-enemy identification

Original CG_DrawCrosshairNames in sorted/cgame_ui.c around line 7886 checks
the viewed client's Signals ability word (0x9598), bit 0x10, then requires
Field Ops OR bit 2 of cgs+0x2038628. nitmod_ParseNCS in cgame_nitrox.c
maps that word to argument 8 of #, represented by the existing keepAwards
field. That historical name is not used as evidence of the field's semantics.

The crosshair now uses both recovered conditions. Original-protocol display
levels no longer substitute for ability masks. ET retains Signals level >=4
and Field Ops. Existing enemy/disguise/spectator gates and distance behavior
are unchanged. Only server-transmitted information is consumed.

Tests cover both protocols, five classes, 64 masks and four option words,
with native levels opposite the mask, plus invalid client indices. This
tests the predicate; live crosshair rendering parity remains outstanding.
No pak or server wire format changes.
