# Original planted tripmine presentation

Reference: CG_Bomb in sorted/cgame_client.c. The local spectator/team
field at client+0x9494 and shoutcaster field at +0x95a8 gate the whole
model. Entity offsets 0x108/0x10c map to teamNum/effect1Time. A zero
effect1Time draws the model without a laser. State 1 uses intensity 50;
other nonzero states use 255. Axis beams are red, other team beams blue.

For an enemy mine, the viewed client's Battle Sense unlock bit 16 is
required for the beam and forces intensity 50. Authorized local spectator
shoutcasters bypass that enemy gate. The typed renderer now implements
these rules before tracing/drawing the beam; stock ET retains its existing
red beam path. Original model orientation, 4096-unit ray and MASK_SHOT
trace remain unchanged.

Tests enumerate local/viewed teams, mine teams, caster flag, three states
and every six-bit unlock mask (6912 combinations), plus invalid client
indices. Hidden/model-only results leave the output color untouched.
No server grants, placement/damage behavior or pak assets are changed.
Actual browser rendering and original-server comparison remain open.
