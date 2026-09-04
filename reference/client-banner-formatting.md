# Banner text preparation

The existing original `bp` receiver already routes type 0 to team chat,
type 1 to console and type 2 to the top banner, gated by cg_drawBanners.
This batch replaces the type-2 raw copy with bounded text preparation and
preserves the active color when the renderer begins the next line.

Evidence: sorted cgame_client.c CG_BannerPrint recognizes literal backslash-n
and uses visible-column thresholds 0x37/0x41. CG_DrawBannerPrint in cgame_ui.c
tracks the last color and prefixes it on subsequent lines. Original ELF
symbols are CG_BannerPrint 0x49370 and CG_DrawBannerPrint 0x40720.

The typed preparation converts escaped newlines, resets the column count on
newlines, replaces a space at/after visible column 55 with a newline, and
breaks a continuous word at column 65. Color escapes have zero display width.
It is bounded by destination size, reserves termination, and never splits a
recognized two-byte color escape at the output boundary. Banner storage stays
1024 bytes. The draw scratch buffer allows the inherited two-byte color prefix
in addition to that bounded text. Initial inherited color is white (`^7`).

This is a cleaned reconstruction of the observed wrapping rules, not bytewise
parity with the original in-place scanner's counters or truncation behavior.
The original first copies/truncates input and then inserts breaks; this code
truncates the prepared output instead. Pathological long/color-heavy input
therefore can differ. Font/row placement is now corrected as documented in
client-hud-font-mapping.md. The existing
10-second fade path is unchanged, including its time-zero sentinel behavior.

Tests cover escaped/real newlines, empty/null source, plain/colored word
lengths 1..130, soft/hard boundaries, output sizes 1..1024 with a boundary
canary, size zero and insufficient space for a color token. Existing dispatch
tests cover the cvar gate and banner/console message routing. These do not
constitute original-client screenshot or golden replay verification.

Native 90/90 tests, WASM build and Node load/entrypoint probes pass. No pak,
menu or PK3 changes. Full browser/dedicated parity remains open.
