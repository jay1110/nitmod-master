# Wounded HUD instructions

Original CG_Draw2D (sorted cgame_ui.c, near labels 0x5dc41/0x5d1e7) uses
left HUD placement, limboFont2, scale .2/style 7, x=8, and y=118/130/142
for wounded, queue and reinforcement instructions. With descriptive text
disabled the reinforcement line alone uses y=118. Its deployment countdown
uses white text and a yellow number.

The original-protocol draw path now uses those coordinates and font instead
of ET's fixed bitmap text and 18-pixel spacing. Native ET rendering is kept.
Existing respawn/LMS conditions and countdown calculation are retained;
the original LMS exception still requires a verified typed mapping before
changing that condition. Invalid local client indices no longer access the
clientinfo array. No gameplay or respawn rules are changed.

Renderer tests cover all three baselines at 1920x1080, invalid row/null
input, and caller-anchor restoration. Live browser comparison remains open.
Pak and original assets are unchanged.
