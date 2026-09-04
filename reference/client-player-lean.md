# Original lean input, replication and body pose

## Evidence

Original cgame ELF symbols: PM_UpdateLean 0x1d440, CG_PredictLean 0x915b0,
BG_PlayerStateToEntityState 0x13000, CG_EntityEffects 0x568c0.
Sorted references: cgame_pmove.c, cgame_predict.c, cgame_bg.c,
cgame_players.c, cgame_ents.c and cgame_nitrox.c.

The previously unresolved fields have concrete mappings:

- Entity +0x98 is currentState.constantLight. Its **integer sign**, not a
  float reinterpretation, is the requested lean direction.
- PlayerState +0x398 is holdable[2]. PM_UpdateLean writes the direction there;
  BG_PlayerStateToEntityState copies it into constantLight except for spectators.
- Original cgs +33787496 is # argument 14, the existing typed weapons flags.
  Bit 256 enables the alternate pose and permits input lean while firing.
- Original cg global 0x010ef1dc is scs argument 7, the existing typed misc
  field; bit 32 enables ordinary body-lean rendering.
- Original cent +0x564 is the cached head refEntity; +0x5d4 is its origin[2].
  CG_PlayerAngles passes this value for remote players and snapshot viewheight
  for the viewed client. The port deliberately preserves the remote world-Z
  value, even though adding it to lerpOrigin again looks unusual.

No offsets or new network structure members are used in production code.

## Integrated behavior

The shared PM_UpdateLean now has an explicit mod-local Nitmod mode, supplied
by cgame prediction and both qagame movement setup paths. Its native ET mode
remains unchanged. Nitmod spectators may lean while moving and retain strafe;
mounted/dead/prone/EF_SPARE0, deployed mortar and dynamite-throw restrictions
are respected. Firing prevents input lean unless weapons bit 256 is present.
The signed button result is stored in the named holdable slot. Existing trace,
leanf interpolation and eye-position collision handling are reused.

Server normal and extrapolated entity conversion paths copy the direction
after conversion. Predicted cgame entities do the same only on original-protocol
servers. Received remote entity fields need no remapping. g_weapons is read
from the existing tracked Cvar cache, not through a new per-frame engine call.

cg_nitmod_lean.c adds body pose before pain twitch and hierarchical angle
subtraction. State is private per centity and resets with CG_ResetPlayerEntity:
direction change starts with a 1ms sample; elapsed time clamps to 1..200ms;
outward motion is 28 units/200ms and return motion 28 units/300ms. Active lean
traces an (-8,-8,-7)..(8,8,4) box along the rolled right vector with
MASK_PLAYERSOLID and the player excluded. Return motion performs no trace.

Ordinary pose: torso roll += amount*1.25, head roll += amount when misc bit32
is set. Alternate pose: torso += amount*1.9 for right input, otherwise *2.35;
head += amount. Both presentation flags may be off while the state advances.
The body's original firing restriction remains unconditional even when the
input path permits firing lean; this asymmetry is present in the reference.

Original player constantLight is no longer also interpreted as packed RGB:
left lean (-1) previously generated a white light with a radius of 1020.
The entity-effects integration preserves real lights on non-player entities
and the native ET path.

## Safe deviations and limits

Timestamp subtraction uses double to avoid signed overflow. Nonfinite or
out-of-range persisted amounts reset; invalid trace fractions cannot poison
pose state. Null angle destinations and invalid remote height conversion are
handled without dereference/undefined conversion. Pose reset on entity reset
prevents stale state crossing respawn/teleport reuse.

This does not reconstruct the entire original prediction cache or movement
system. Standalone PM_UpdateViewAngles without an active matching pmove still
uses the existing native fallback. Broader gun-position/recoil semantics are
not claimed by this body-pose port. Browser visual parity remains unverified.

## Tests

CheckPlayerLean: 1,080 timeline samples across direction, mode and collision
fractions; six eFlag restrictions plus deployed mortar; extreme clocks;
real config-reading adapter/local and remote trace origins; native bypass;
12 real CG_AddCEntity light/no-light cases.

check_lean.h: the same 1,024-case PM_UpdateLean matrix runs in both full cgame
and full qagame test links, covering button combinations, forward/up movement,
spectator state, firing option, eight flag profiles, strafe behavior and the
named direction slot. Tests verify collision calls and resulting leanf.

Native Debug and the complete CTest suite, WASM build, and Node side-module
load/ABI smoke probes are run. These are not original-binary replays or a
live dedicated-server/browser gameplay test. Original PK3/assets remain read-only.
