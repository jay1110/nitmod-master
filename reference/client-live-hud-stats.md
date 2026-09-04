# Original live HUD statistics

Implemented the five-line live statistics panel in cg_nitmod_hud.c:
Spree, BS (bodyshots), HS (headshots), K and D. cg_drawHUDStats defaults to
1/CVAR_ARCHIVE. The existing scoreboard-suppressed 2D path calls the panel;
no second scoreboard draw is introduced. Original HUD flag bit 1 selects
left versus right placement, scoped through the widescreen HUD adapter.
The panel uses the existing HUD background/border colors, limboFont1 at
.17, style 3, y=335, height=50, and text baselines 343/353/363/373/383.
Width is measured from the spree line, matching the original.

## Binary evidence and typed mapping

Reference cgame SHA-256:
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.
Nit_LiveStats ELF 0xf4430, size 955; BG_GetKillSpree 0x23a10, size 19.
The latter reads playerState+0x14c. Nit_LiveStats reads snapshot offsets
0x148/0x14c/0x150/0x154 for kills/deaths/headshots/bodyshots respectively.
snapshot.ps starts at 44, playerState.persistant at 272; therefore original
wire slots are 3/4/5/6, and spree is slot 15. Tests assert these offsets.
The original BS format string is at ELF file offset 0x111549.
Ghidra addresses in sorted files have a 0x10000 bias relative to this ELF.

Original CG_NewClientInfo token 0x5a stores the tv flag in the final
clientInfo field (cgs+client*0x1a4+0x95ac). The token table entry at ELF
file offset 0x12c5d8 names tv. A typed nitmodTV field now preserves this
configstring value and suppresses the panel for TV clients.

Snapshot transitions compare old/new bodyshot and headshot counters.
Increments highlight the corresponding number green for 100ms. Equal or
decreasing counters do not rearm it. Defensive differences: fresh state
does not falsely flash at time zero; negative time deltas and a change of
followed client do not retain a misleading highlight. HUD reset clears it.

## Boundaries / remaining work

This is a receiver for original Nitmod servers, not reconstructed qagame
statistics emission. It deliberately reads original persistant slots by
separate named constants, NOT native PERS_TEAM etc. Existing snapshot weapon
translation leaves these slots unchanged. The subsequent persistant adapter
now preserves them in per-snapshot sidecars while normalizing the native
consumer array; see client-snapshot-persistant.md. Live-stat readers use
those wire copies, not the normalized native team/spawn slots.

Tests exercise all five rows, highlight boundaries, unchanged/decreasing
counters, protocol gating, follow changes, invalid arguments and 16 render
combinations (protocol, placement, TV, enabled). Live visual comparison is
still required. No pak, menu, PK3, original binary or server message edits.
