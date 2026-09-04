# Wounded-player and medic names

`cg_nitmod_names.c` ports the transient wounded-name queue and connects it
to player rendering, packet-entity frame resets and normal 2D drawing.
`cg_woundedNames` retains the original default 1 and CVAR_ARCHIVE flag.

Evidence: `sorted/cgame_client.c` CG_WoundedPlayerFloatName (line 17632),
`cgame_players.c` player sprite/name dispatch (lines 1250–1356), and
`cgame_ui.c` CG_DrawOnScreenNames, transient queue branch (line 8528).
Inputs use typed entityState, clientInfo, snapshot playerState, predicted
origin and refdef fields. No raw original global offsets are used.

A wounded player sees living friendly medics; a living medic sees dead
teammates at distances 64–1600 inclusive, except original gametype 8.
Only original-protocol Axis/Allies clients participate. Local-player,
invalid-client, disabled-2D, disabled-cvar and demo paths do not enqueue.
Living medic labels are raised 48 units; wounded labels are lowered 6.

The queue is limited to 32 entries and owns copies of names. Projection
retains the original 96/FOVx and 102/FOVy factors, .01 forward-depth cutoff,
.18 font scale and text centering. The original trace-target adjustment
(world X minus half text height, world Y minus half text width) is retained
rather than silently replacing it with a different occlusion rule.
Drawing uses a solid trace with a +/-1 box, alpha .75 and style 7. Blocked
labels are not painted. Scoped centered HUD placement supports widescreen.
Consumption and frame/HUD resets prevent stale labels.

The engine-double tests cover 1,120 eligibility combinations across
protocol, health, class, team, dead flags and distance boundaries, plus
32-entry capacity, copied names, blocked/unblocked drawing and one-shot
queue consumption. The full native suite passes (91 tests). WASM builds
and entrypoint/load checks are performed separately from live gameplay.

Still outstanding: original spectator/private-field eligibility, the
separate persistent-name/fade branch of CG_DrawOnScreenNames, and visual
comparison on an original dedicated server. This is not a claim that all
floating-name paths or the full client have reached parity.

No server protocol changes, original binaries or pak/PK3/menu edits.
