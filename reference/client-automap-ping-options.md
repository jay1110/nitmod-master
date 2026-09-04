# Automap and scoreboard options

Original references: CG_AdjustAutomapZoom at ELF32 0x2b9b0 (272 bytes),
pingColor at 0xf5000 (82 bytes), sorted cgame_ents.c/cgame_unknown.c;
scoreboard formatting in sorted cgame_ui.c uses `^%i%4i^7` or `^2CONN.^7`.

cg_automapZoom is now a typed archived Cvar, default 5.159, registered in both
cgame and UI. It replaces the native static float. Both map entity coordinate
transformation and automap scissoring read the same value. Zoom commands scale
by 1.2, clamp to 1..7.43, persist via trap_Cvar_Set, refresh the VM handle and
recalculate coordinates. CG_UpdateCvars also recalculates map coordinates on
modification, so the original menu slider/console updates take effect live.

Intentional hardening: direct values outside the zoom interval are bounded for
rendering, and NaN falls back to 5.159. Direct Cvars are not forcibly rewritten;
zoom button actions persist their bounded result. The original decompile appears
to transform from the stale VM value immediately after setting the Cvar; this
port refreshes before transforming. Native map geometry/scaling is retained.

cg_pingColors default 1, CVAR_ARCHIVE is registered in both modules. Both native
scoreboard sizes use the same formatting helper. Enabled thresholds are <=100:
color 2, 101..200: 3, 201..350: 8, >350: 1. Disabled uses white (7); nonzero
negative modes remain enabled. Ping -1 shows the original green CONN. label.
Original bot-indicator flags are not mapped by this batch; spectator/class/XP
layout stays native and has not been rebuilt as the original Nitmod scoreboard.

Tests cover 36 color/format profiles including exact thresholds and connection
status, plus 12 real zoom-button/Cvar writeback profiles with the engine syscall
seam. Inventory assertions pin defaults. Full browser screenshots, transformed
entity coordinate golden tests and map-reconnect persistence remain outstanding.
No pak/PK3/menu/original-module content changed.
