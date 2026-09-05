# Spectator instructions

Original CG_Draw2D in sorted cgame_ui.c enables descriptive instructions for
PMF_LIMBO, TEAM_SPECTATOR or PMF_FOLLOW. It selects left HUD placement and
draws the two bound-key messages at (8,150)/(8,158), scale .2, style 7,
limboFont2. The port now uses those coordinates/font and includes follow
mode. Existing binding refresh, Escape fallback and descriptive-text toggle
are preserved. Native ET retains its existing text rendering and visibility.

Renderer tests verify both lines at 1920x1080, invalid row/null input and
restoration of the caller's right HUD anchor. Browser screenshot comparison
is still open; pak is unchanged.

Investigation note: knife/syringe assets contain FASTDROP/FASTRAISE trailing
rows, but the original CG_ParseWeaponConfig loop also stops after 13 rows:
pointer 0x5c to 0x60c in 0x70-byte increments. A tentative enum enlargement
was reverted. Asset comments alone do not establish new animation protocol
IDs; no fast-switch gameplay support is claimed.
