# Projectile presentation: traveled direction and active bounds

Evidence: sorted/cgame_effects.c CG_Missile, LAB_00065c3c through
LAB_00065c99. Original weapon IDs 5, 42, 36 and 37 select the displacement
branch (Panzerfaust, deployed mortar, GPG40 and M7). Other weapons use launch
trDelta. This code runs after the existing wire-to-ET weapon translation.

cg_nitmod_projectiles.c/h contains a typed orientation helper. First use
subtracts pos.trBase; later frames subtract rawOrigin and retain/update that
history as in the original. A zero movement vector points upward. Original
protocol records AxisToAngles before visual spin; native ET keeps its prior
lerpAngles behavior and its mortar-only displacement branch. Stationary models
spin by entity time, moving models by cg.time/4. The helper is active in
CG_Missile and included by both CMake and SCons.

The active renderer also rejects invalid weapon/entity/current-client indices
before dereferencing arrays, rather than changing the network weapon to zero.
Fragment model indices are bounded, artillery owners cannot index outside
their client arrays, and nonpositive looping-sound handles are not submitted.
These are defensive differences, not original feature reconstruction. Valid
sound timing, trail dispatch, team media and mine handling are retained.

Full-cgame tests exercise every native weapon under both protocol modes,
stationary/moving trajectories and four successive positions, including an
unchanged final position. Axis, stored direction and raw-position history are
checked. Real CG_Missile calls verify model submission, negative sound
suppression, invalid weapons/entity IDs, both fragment model paths and valid/
invalid artillery owners, with source state preservation on rejected weapons.
All 97 native tests pass. WASM builds and Node load/entrypoint probes are used
separately from browser verification.

No pak, menus, original artifacts, network layouts or qagame behavior changed.
The missile-camera selection/render/reentrant-state subsystem is NOT ported by
this orientation prerequisite. Poison/bomb weapons and original-server visual
parity also remain open; this is not a complete CG_Missile or Nitmod port.
