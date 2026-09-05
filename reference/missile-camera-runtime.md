# Missile-camera runtime mapping

The original cgame selects the local player's rendered missile in
`CG_Missile` (ELF `0x65bde..0x65c99`) and renders the secondary view in
`CG_DrawMissileCamera` (ELF `0x7ee70`).  The recovered typed mapping is:

- `entityState_t::clientNum` identifies the projectile owner;
- `weapon` selects `g_missileCams` bit 1 (Panzerfaust), bit 2 (mortar) or
  bit 4 (GPG40/M7);
- `centity_t::lerpOrigin` and `lerpAngles` provide camera position/direction;
- the original virtual rectangle is `(16, 160, 160, 120)` and is converted by
  `CG_AdjustFrom640` before rendering.

No new snapshot field or custom portal marker is introduced, so this path also
works with original Nitmod dedicated-server binaries.
