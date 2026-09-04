# Nitmod FPS sampling window

Original reference: CG_DrawUpperRight in cgame_ui.c; original ELF function
0x44b50, FPS branch at 0x44ed8. Original cgame SHA-256:
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.

The previous typed implementation always sampled four frames and displayed
nothing during warmup. Nitmod instead clamps nonzero cg_drawFPS to 4..500,
restarts the ring when the clamped window changes, displays `estimating`
for the first N calls and then displays integer `1000*N/sum(last N deltas)`.
The original replaces a zero sum with one. Disassembly at 0x44ef9..0x44f30
confirms the bounds and window-change reset; the split decompile shows the
ring, warmup comparison and sum. Time comes from trap_Milliseconds, not the
server snapshot clock. Disabled display does not sample or clear history.

CG_NitmodFPSText now owns a typed 500-element ring. CG_DrawFPS uses this
formatter with the actual cvar and engine clock; existing font, colors and
row positioning remain intact. No new cvar or protocol field is introduced.

Intentional robustness differences: ring cursor and fill count stay bounded
instead of eventually overflowing the original monotonically incremented
index; the sum uses double to avoid signed integer overflow; backward or
unrepresentably large time deltas restart warmup. HUD reset clears sampling
state. Full aspect-aware placement and browser screenshot parity remain open.

Regression fixtures exercise all cvar values -1..501 (except disabled zero),
every warmup sample and two full-window samples, an uneven frame window,
window-size changes, disabled mode, clock rollback, zero-duration frames and
HUD reset. Native and WASM builds are checked separately from live gameplay.
Original binaries and pak content remain unchanged.
