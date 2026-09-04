# Original objective and artillery hints

This batch adds the missing `cg_objectiveHints` and `cg_artilleryHints`
(original defaults 1, flags 1/CVAR_ARCHIVE) with their actual rendering paths.
It does not merely register placeholder cvars.

Evidence: sorted/cgame_nitrox.c nitmod_DrawObjectiveHint,
nitmod_CheckArtilleryHint and nitmod_DrawArtilleryHint; cgame_client.c entity
dispatcher cases 13/31/58 and media registration. Original shader fields
131976 and 131980 are awards[12]/awards[13] (base 0x20358), hence the existing
PK3 paths gfx/awards/12 and gfx/awards/13. Arrow uses gfx/2d/objArrow;
explosive targets use the existing dynamiteHintShader.

`cg_nitmod_hints.c` intercepts only these original wire entity types before
the native entity switch. It does not renumber native ET enums. Type 13 is
the explosive indicator, not ET_EXPLOSIVE. Original 31 is the constructible
indicator; original 58 is the artillery hint. This distinction matters
because the original/native entity enums are not interchangeable.

Objective rendering requires enabled 2D/hints, non-spectator state, a valid
local engineer, a nonzero target team and PVS visibility. Friendly build
targets (or team 3) and enemy explosive targets receive a white icon and a
team-colored arrow. Icons bob 50–60 units above the entity, then another 24
units; radii are 10/16. Distance thresholds are 256, 784 and 2304, controlling
near blinking, arrow suppression and depth hack. All origin reads use typed
entityState.pos.trBase and predictedPlayerState.origin; no offset globals.

Artillery markers match the local team. Within 400 units the blink period
is 150ms, within 576 units 300ms; farther markers clear the warning, matching
original last-processed-marker semantics. The centered 36x36 warning at
(302,320) uses the scoped HUD placement adapter. A consumed warning clears;
frame and HUD resets also clear state to prevent stale warnings.

Verification includes 1,920 objective combinations (protocol, team, class,
target ownership, visibility and exact distance boundaries), submitted
sprite shaders/radii/positions/depth flags, 178 artillery distances and
one-shot consumption. Media registrations are checked through engine doubles.
Native CTest and WASM build/load checks are run. Live visual comparison and
the rest of original entity-type reconciliation remain outstanding.

Original binaries and all pak/menu/PK3 files remain unchanged. Reconstructed
qagame emission of the new private marker type is not added in this batch;
the receiver is for existing original Nitmod servers.
