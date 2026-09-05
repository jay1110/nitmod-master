# Spectator names on the reconstructed server

Original nitmod_SimpleCS in sorted qagame/nitmod_core.c places
g_spectatorNames.integer in the sixth scs field. The original cvar inventory
entry at ELF 0x2a9e9c specifies default 0 and flags 0.

The native server now registers this cvar in gameCvarTable, refreshes the
simple snapshot on its modification and includes the current value in initial
and changed snapshots. The existing SIMPLE_CS capability gate remains intact.

cgame's spectator-name eligibility and floating-name draw gate now accept
both original Nitmod and reconstructed et260 layouts. Entity identity,
spectator-only eligibility, draw2D, server permission, projection, queue limits
and occlusion fades are unchanged. Dynamite/shoutcaster-specific and location
name gates remain original-only; no unported private state is inferred.

Tests: linked qagame snapshot production covers enabled, unchanged, disabled
and capability-revoked states. Client eligibility covers etmain, original
Nitmod and reconstructed Nitmod layouts; existing drawing/occlusion tests now
also execute with the reconstructed layout. WASM module loading is tested,
but a live browser/server visual comparison remains outstanding.

Usage on the reconstructed server: set g_spectatorNames 1. Default remains
off, matching the reference. No menu/PK3 assets or UI-module code are changed.
