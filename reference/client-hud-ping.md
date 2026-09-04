# Original HUD ping modes

Source reference: CG_DrawUpperRight in
`src_nitmod_decompiled/cgame/sorted/cgame_ui.c`.
Binary reference: cgame.mp.i386.so, SHA-256
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f,
ELF function VA 0x44b50.

The port previously rendered only cg_drawPing=1 and left the average mode
unimplemented. The original does not maintain an average history here:

- 0: no row.
- 1: `Ping %d`, clamped only above 999 (negative values are preserved).
- Every other nonzero value: `Avg Ping %0.2f`, with `(ping + 0.0) * 0.5`,
  stored as float before promotion to double for formatting. No 999 clamp.

At 0x44e25..0x44e35 the original converts the snapshot ping, adds the float
at 0x1000b0 (0.0), multiplies by the float at 0xff348 (0.5), and stores it
on the stack. The mode branch follows at 0x44e3e. Format strings reside at
0x1034d4; normal-mode upper clamping is at 0x453af. EBX/PIC base is 0x12dc44.
Despite its name, this is not an exponential or windowed moving average.

CG_NitmodHudPingText now implements those modes and the existing typed HUD
calls it for all nonzero values. It uses cg.snap->ping; no engine structs,
wire messages, cvar registrations, scoreboard ping formatting or pak assets
change. Existing DrawLine layout/font is reused. Full aspect-aware original
HUD placement remains separate work.

Tests exercise 70 text cases in forward/reverse order, including negative,
zero, odd and >999 pings, disabled and nonstandard modes; they assert actual
HUD drawing/16-unit row advancement and absence of drawing without a snapshot.
The protocol reference test pins the ELF hash, arithmetic bytes, constants
and format strings. Browser/screenshot parity is not established by these
fixtures.
