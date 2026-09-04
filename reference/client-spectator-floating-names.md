# Spectator floating-name pipeline

References: CG_PlayerFloatText and its CG_Player caller in
sorted/cgame_players.c, and the first branch of CG_DrawOnScreenNames in
sorted/cgame_ui.c. The caller checks snapshot team 3, then either the local
client's shoutcaster field (0x95a8) or simple-config spectatorNames. These
are already mapped to typed client info and the scs message. No new user
cvar, authorization claim, or server message is introduced.

Original player labels now queue from CG_Player alongside (not instead of)
the wounded-name path. Queue capacity is 16, text is copied, player and entity
indices are validated. Corpses/nonplayer entities and missing client data
are excluded. Spectator-only eligibility is rechecked before drawing.
The previously existing wounded queue keeps its separate 32-entry capacity.

Height is 48 for standing players and 8 for dead/prone players; ducking
subtracts 18 using local PMF_DUCKED or remote animMovetype. Projection uses
the original 96/FOVx and 102/FOVy factors and .01 depth cutoff. Font scale
is max(.125, .5 - distance/3000), text is centered using ariblk/27 metrics.
The solid trace uses a +/-1 box. Style 7 and centered aspect placement are
retained. Original 250-ms last-visible/last-hidden fade equations implement
occlusion transitions rather than the wounded path's immediate on/off.

Deliberate state-management differences: fades are keyed by client instead
of transient queue slot, names changing identity reset their fade, first
observation starts transparent, backward time resets state, and all text
is owned. Per-frame queue reset is separate from full map/HUD reset. Thus
one player's alpha cannot transfer to another merely because entity order
changes. This is not a claim of identical initialization artifacts.

Tests exercise protocol/team/shoutcaster/draw gates, distance scale
boundaries, 250-ms fade-in/out, backward time, copied names, 16-entry
capacity, real trace/draw callbacks, behind-camera rejection, bad indices,
and one-shot queue consumption. Existing wounded-name tests still pass.
Native and WASM builds plus Node module-entrypoint probes are run.
Live browser/server and screenshot parity are not established.

Remaining related paths: generic location-debug labels and shoutcaster
dynamite timer labels are not connected by this batch. No pak, PK3, menu,
original module, qagame producer or player permission is modified.
