# Early entity transition

Source: original `cgame/sorted/cgame_ents.c`, `CG_AddPacketEntities`
(next-snapshot loop around line 2663), and `CG_AddCEntity_Filter`.
The split reference does not provide a function address for this entry.

`cg_earlyTransition` now advances ET_GENERAL (0) and ET_MISSILE (3) entities
from the next snapshot before the current-snapshot rendering pass. Players,
items, movers and event-only entities retain their normal transition timing.
The existing typed `CG_TransitionEntity` performs state copy, initial reset,
fire-direction update and event delivery. The original's write at centity
offset 0x240 maps to `interpolate = qtrue`, preserving event history through
the subsequent regular transition. `CG_AddCEntity` marks `processedFrame` so
the ordinary render filter does not submit the entity again.

Compatibility boundaries / intentional deviations:

- Enabled only for original Nitmod protocol, with the existing cvar enabled.
- Invalid snapshot counts, IDs and mismatched nextState IDs are rejected.
- Teleport/restart/follow discontinuities and multiview use the regular path;
  the original private missile-camera/reentrant rendering state is not ported.
- Entities absent from the next snapshot remain in the regular render pass.
  Unlike the original filter, the port does not suppress them based on an
  old `nextState.eType`: ET 2.60 retains stale nextState data for absent entities.
- No changes to wire layouts, qagame, UI assets, pak or original binaries.

Regression fixture `CheckEarlyTransition` in `test_original_charge_dispatch.c`
exercises all non-event native entity types, early state/position transfer,
real original wire event 59 (stop looping sound), repeated-frame event dedup,
the processed-frame render filter, protocol/cvar/discontinuity/multiview gates
and invalid IDs/counts. This is not a full renderer or dedicated-server replay;
visual parity and private camera behavior remain open.
