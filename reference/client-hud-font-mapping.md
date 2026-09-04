# Recovered HUD font mapping and banner metrics

Original cgame_client.c registers ariblk/27 at Ghidra address 0x1100f64,
ariblk/16 at 0x1105fa8 and courbd/30 at 0x110afec. The corresponding typed
registrations are limboFont1, limboFont1_lo and limboFont2 in cg_main.c.
The original banner, kill, spree, special and announcer renderers explicitly
use 0x1100f64. This corrects the provisional limboFont2 mapping used by the
recent typed HUD ports. Generic notification rendering was subsequently
verified independently: cgame_nitrox.c's notification path uses 0x110afec
(courbd/30, limboFont2), unlike the other HUD messages. Its existing font
selection therefore remains unchanged.

Banner row metrics: original ELF CG_DrawBannerPrint at 0x40720 calculates
the height of the first glyph from a string at virtual address 0xfdbdb.
This points to the terminal A of GPG40A, followed by NUL in .rodata. The
PIC base 0x12dc44 minus 0x30069 resolves that address. The renderer uses
scale .2 and integer truncation, then multiplies the integer height by 1.5
and truncates again for each row. The typed renderer now uses
`(int)(CG_Text_Height_Ext("A", .2f, 1, &limboFont1) * 1.5f)` as its step,
with the first baseline one step from the top. Horizontal centering is also
truncated to an integer, matching the original path.

Defensive difference: zero/invalid font height yields a minimum one-pixel
step. Existing screen-height clipping remains. Aspect-aware original
CG_HudPlacement is still not reconstructed; browser screenshots are needed
to verify end-to-end layout and actual font assets.

The full-cgame render fixture supplies a distinct shader and synthetic
ariblk metrics at two A heights. It verifies the selected font, exact x/y
for two colored lines, inherited red color, full opacity, half-fade and
expiry. All 90 native tests pass; WASM build and Node entrypoint/load probes
pass. No pak assets or protocol contracts are changed.
