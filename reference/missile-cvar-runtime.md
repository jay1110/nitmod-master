# Missile cvar runtime

Original qagame `fire_rocket` uses `g_missileSpeed`, `g_missileHealth` and
`g_missileGravity`. The reconstructed Panzerfaust entity now preserves its
observed defaults and typed field mappings:

- speed values above zero replace the original 2500-unit velocity;
- gravity 0 is linear, 1 uses `TR_GRAVITY`, 2 uses `TR_GRAVITY_LOW`, and other
  nonzero values use `TR_GRAVITY_FLOAT` while ordinary rocket mode is active;
- positive health enables damage, `G_MissileDie`, `CONTENTS_CORPSE`, and the
  original `(-10,-3,0)` to `(10,3,6)` collision bounds.

`g_rockets` bit 1 now installs the guided think routine and bit 2 installs the
homing routine. Guided missiles follow the owner's view at the original
300-unit default/cap. Homing missiles select the nearest visible enemy within
768 units and a 0.9 forward dot-product cone, then turn by the recovered 0.05
factor at the server-frame rate and use the original 750-unit default/cap.
`g_missileCams` also creates the recovered owner-only `ET_PORTAL` camera:
bit 1 follows Panzerfaust rockets, bit 2 follows mortar shells, and bit 4
follows rifle grenades. The portal tracks the projectile in `origin2`, is
visible only to its owner, and removes itself when its owner, projectile, or
matching option becomes invalid. Bit 1 additionally selects the direct-view
guided aiming branch.

`g_mortarBBox` is handled in the same projectile factory. A nonzero value
installs the original two-unit symmetric bounding box; zero preserves the
point-sized mortar trace.
