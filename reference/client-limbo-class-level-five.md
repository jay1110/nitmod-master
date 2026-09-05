# Level-five Limbo class wedges

Original CG_LimboPanel_RenderClassButton in sorted/cgame_ui.c still draws
at most four atlas quadrants. At displayed skill level five it switches
the on/off atlas handles from media 131624/131628 to 131652/131656.
Original registration in sorted/cgame_client.c names the latter
gfx/limbo/sk_5_on.tga and gfx/limbo/sk_5_off.tga.

The typed client now registers these assets for original Nitmod and selects
them using nitmodSkillLevels. Native ET retains its existing atlas and
levels. Selection/hover/spectator state continues to choose on/off tinting.
Missing level-five shaders fall back to the ordinary atlas; invalid button
or client/class indices are rejected. No pak assets are edited.

Renderer tests cover five classes, all supported levels, both protocols,
selected/spectator states, shader identity, quadrant counts and invalid
buttons. Browser screenshots remain necessary for final visual parity.
