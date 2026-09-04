# Player diagnostic and demo presentation

The formerly registration-only cg_drawHitbox and demo_wallHack cvars now
have typed consumers. Both retain CVAR_CHEAT. No menu, pak, protocol, or
original binary changes. New cg_nitmod_debug.c/.h is included in CMake and
the historical cgame SCons list.

## Evidence and geometry

Original sorted cgame_players.c CG_Player, lines 1656-1743, uses this mask:

- 4: entityState.solid packed radius/down/up bounds at lerpOrigin.
- 2: tag_head origin and its three transformed 32-unit axes.
- 1: predicted player bounds, crouch height, or prone body plus leg/head boxes.

The original explicitly uses predicted stance/bounds even for another
displayed entity. The port preserves that diagnostic behavior, not a claim
that the boxes represent the remote server's authoritative hit volumes.
The prone legs use playerlegsProneMins/Maxs, the horizontal forward vector,
-32 displacement and pmext.proneLegsOffset. The prone head uses +12 forward
displacement and (-6,-6,-22)..(6,6,-10) extents.

The original blue tint is (0.25,0.5,1). Rendering uses railCore and 12 edges
per box, plus three head axes. Defensive differences: malformed/nonfinite
or inverted boxes, absent models/tags/shaders and SOLID_BMODEL are skipped.
Diagnostics only run for the original protocol. Geometry does not modify
the entity, prediction, collision or damage state.

Lifetime deviation: these constantly updated diagnostic lines are submitted
directly for the current frame. The original caches/fades local rail
entities using entity-derived IDs; that keyed lifetime subsystem is not
ported here. Therefore trails after disabling the cvar or losing visibility
are not reproduced. At most 51 lines are submitted per player per call,
without allocations or accumulation in the gameplay local-entity pool.

## Demo rendering

Original CG_Player at lines 1567-1572 assigns the red shader for Axis and
blue otherwise to body, head and accessories, with render flag 8
(RF_DEPTHHACK), only during demo playback. Shader registrations are directly
visible in cgame_client.c lines 14945/14947:
textures/sfx/transgunRed and textures/sfx/transgunBlue.

The port registers those existing assets during graphics initialization,
resets cached handles there, and applies the same per-player shader to the
three ref entities. Live play, native ET sessions, disabled cvar and failed
shader registration never enable this style. Demo playback is checked
explicitly, in addition to engine cheat-cvar enforcement.

## Verification

Full linked cgame fixture: 96 protocol/stance/mask combinations (including
unknown mask bits), expected bounds, all edge endpoints and head axes,
missing model/tag, invalid solid and nonfinite coordinates. Another 48
protocol/demo/cvar/team combinations exercise actual shader selection and
registration/reset/failure behavior. Renderer syscall capture checks line
type, asset and color. Browser visuals, keyed rail fading and complete
CG_Player parity remain unverified; this is not a full client-port claim.
