# Original corpse animation timing

New cg_nitmod_animation.c/.h reconstructs the two original corpse-specific
animation routines in typed ET structures. CMake and SCons both include it.
CG_RunLerpFrameRate dispatches original-protocol corpses to this path before
the native freeze-last-frame and cg_animSpeed branches. Consequently both
legs and torso use the original timing; native sessions and ordinary players
retain the existing code. cg_noPlayerAnims still acts in CG_PlayerAnimation.

Evidence: original cgame ELF CG_SetLerpFrameAnimationRateCorpse at 0x910a0
and CG_RunLerpFrameRateCorpse at 0x91250; sorted cgame_client.c 17427-17600.
The original animation callers around 18107/18124 dispatch legs and torso
when the wire entity type is corpse (38, normalized by the existing port).

Mapping:

- entityState offset 0x10c is effect1Time, the death-animation end time.
- onFireStart (0xfc) selects a registered character, or modelindex/modelindex2
  select the corpse team/class (team values >=4 subtract 4).
- animation firstFrame/numFrames/loopFrames/frameLerp/duration and mdxFile
  replace decompiler array offsets 0x11/0x12/0x13/0x14/0x18/0.
- lerpFrame animationNumber, animationTime, old/current frames and model
  handles retain their typed ownership; no original memory offsets are used.

An animation starts at its elapsed position when a corpse arrives late.
The end time is clamped against animation duration when initializing, frames
advance with the original cadence and loop-tail rule, and expired corpses
hold the final frame/model with zero interpolation. The original 200ms
future-frame guard and old-time clamp are preserved. ANIM_TOGGLEBIT switches
and changed animation assets reinitialize the sequence.

Defensive differences: invalid characters/animations/frame intervals/counts
produce no stale animation rather than indexing invalid memory or dividing
by zero. The initial old frame cannot exceed the animation's last frame.
Time arithmetic uses double differences and saturated integer results rather
than overflowing signed clocks. Character team/class/registered-index bounds
are validated in the shared corpse lookup. No qagame messages, enum values,
PK3 data or animation scripts are modified.

Tests: 979 independently calculated initial time/loop profiles (0..2200ms,
25ms increments, loop-tail lengths 0..10), progressing 1000/1050/1100ms frames,
expiry, toggle/asset changes, native/live-player bypass, malformed animation
fields, invalid character selection and extreme clocks. The linked fixture
also enters through the actual CG_RunLerpFrameRate dispatcher with
cg_animSpeed=0, matching the original corpse-specific exception.

These tests establish the reconstructed timing paths, not complete rendered
model parity. Live dedicated-server death/revive demos and browser visual
comparison remain unverified. Full Nitmod port completion is not claimed.
