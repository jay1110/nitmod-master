# Server-selected mine highlight colors

Original nitmod_GetSimpleCS argument 7 writes g_unk_010ef1dc. The typed
snapshot already exposes this as misc. CG_Missile in sorted/cgame_effects.c
tests bit 16 only after the hidden-enemy-mine Battle Sense and 256-unit
distance checks. It selects media 131916 for Axis and 131924 for Allies.
CG_RegisterGraphics registers these as textures/sfx/transgunRed and
textures/sfx/transgunBlue, respectively.

The mine renderer now applies these existing original assets when misc bit
16 is enabled. Their handles are shared with the existing diagnostic media
registration; the demo-player accessor remains separately demo-only. The
new accessor does not select entities or grant visibility. Missing shader
handles fall back to the ordinary construction highlight, a defensive
difference from rendering with a missing original shader.

Tests cover all 64 option masks, both protocol modes, all four team values
and missing media. Existing visibility tests continue to exercise skill,
distance, ownership, team and spectator guards. No Cvar, server message,
pak asset or original module changes. Browser visual parity remains open.
