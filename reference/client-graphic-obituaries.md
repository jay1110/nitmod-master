# Graphic obituary queue and rendering

Modes 3/4 now use the existing bounded popup pool for valid two-player
kills with a mapped weapon and registered weaponIcon. Mode 3 orders
attacker/icon/victim; mode 4 reverses the names (syringe retains attacker
first). Other/world/self/private causes and missing media retain a text
fallback. This is not complete original weapon-registry reconstruction.

The popup item owns two 128-byte names, icon scale and RGB. Allocation,
waiting/old lists, expiration, cg_numPopups, cg_popupFadeTime and HUD flags
are shared with ordinary notifications. Ordinary allocation explicitly
clears graphic fields on slot reuse. A full waiting-only pool rejects a
new entry; oldest old entries can be recycled. Corrected a pre-existing
unlink bug that orphaned the remaining old entry when recycling a tail
from a two-item old list.

Evidence: sorted/cgame_client.c nitrox_AddGraphicObituary at line 19338;
sorted/cgame_ui.c CG_DrawPMItems at 16642; cgame_events.c modes at 1048.
The original queue owns two strings at +0xc/+0x8c, icon +0x10c, scale
+0x110 and RGB +0x118. Typed fields replace those offsets. Renderer uses
limboFont1 at .2, style 7, first text x=18/y+12, icon x=26+textWidth,
width=16*scale, height=16, second text x=32+textWidth+iconWidth. Both names
and icon use the existing popup fade alpha. Placement is scoped HUD-left.

Current integration uses the typed native MOD-to-weapon lookup after wire
cause translation, registered weaponIcon[0] and weaponIconScale. Standard
yellow/red/green distinguish ordinary/team/syringe icons; full exact OB
palette and original private icon registry parity remain to be audited.
Unsupported scales outside 1–4 and invalid handles fall back to text.
Console text is still emitted once for a successfully queued graphic row.

Tests call the actual obituary adapter and popup renderer for modes 3/4,
checking name order and 32-pixel icon width. Additional checks exercise
invalid inputs, 32-slot capacity, tail recycling without losing the old
head, and ordinary text rendering after reset. Native build/CTest and WASM
load checks are run; live browser visual comparison remains outstanding.
No pak, menu, PK3, original module or qagame protocol changes.
