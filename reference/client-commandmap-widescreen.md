# Command-map widescreen continuation

Original `CG_DrawExpandedAutoMap` (Ghidra cgame_ui.c, entry near 0x3dd59)
selects CG_HudPlacement(2): the right anchor. Its 352-square map slides from
x=650 to x=268 over 250 ms, at y=20; closing reverses that trajectory.
The compact map selects the left anchor. The port now scopes the expanded
map's right anchor and restores its caller's anchor, including when drawn
inside the compact-map pass. Hidden-map early returns do not change anchors.

All four command-map grid paths now use the same CG_AdjustFrom640 transform
as the map texture, labels and markers. Lines retain one physical pixel of
thickness. Previously their direct screenXScale multiplication stretched
and displaced the grid relative to an anchored map on wide screens.

Original expanded-map entity traversal accepts either the snapshot team or
TEAM_SPECTATOR (original snapshot offset 0x158). The shared typed map renderer
now admits both transmitted teams for original-protocol spectators; ordinary
players and the ET protocol retain their team filter. This only displays
markers received from the server, not undisclosed entity information.

CheckAutomapLayout exercises actual CG_DrawAutoMap/CG_DrawExpandedAutoMap
renderer calls at 1920x1080: compact grid bounds and pixel thickness, opening
at 0/125/250 ms, closing, hidden state, and restoration of the left anchor.
Existing command-map protocol and marker presentation tests remain active.
Live spectator replay and browser screenshot parity are still outstanding.
No pak or original reference assets were changed.
