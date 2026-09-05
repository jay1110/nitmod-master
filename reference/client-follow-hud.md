# Follow and limbo HUD

Original CG_Draw2D (sorted cgame_ui.c around 0x5d000) selects the left
HUD anchor for PMF_FOLLOW. Outside limbo it paints the team flag at
(8,124,15,12), class skill icon at (23,124,13,13), and the rank/name line
at x=38,y=134. Nonplaying teams use x=8 without those icons. In limbo the
deployment line is at (8,130), followed by rank/name/class at (8,140) unless
following oneself. Font scale .2, limboFont2/style 7 match the original.

CG_NitmodDrawFollow now provides this original-protocol path, independent
of ET multiview handling. Stock ET keeps the previous path. Typed client,
rank and class indices are checked before indexing tables. Text is bounded;
bonus deployment multiplication uses double and clamps before int conversion.
The existing reinforcement-time computation is reused, not a new respawn
rule. Original optimized decompiler output omits some countdown arguments;
full temporal parity still needs replay validation.

Renderer tests cover five class icons, limbo rendering, extreme penalty,
invalid client/rank and non-follow suppression. Browser layout comparison
and live join/respawn replay remain open. Pak is unchanged.
