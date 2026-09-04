# Original vector diagnostic events 104–106

Original CG_EntityEvent in sorted cgame_events.c dispatches three additional
diagnostic primitives to CG_BotDebugLine (ELF 0x5efe0). Ghidra loses call
arguments here; the call at 0x62000 establishes start=entity+0x68 (origin2),
end=entity+0x18 (pos.trBase), color=entity+0x80 (angles2).

The new typed decoder handles:

- 104: one line, float RGB from angles2.
- 105: three RGB axes from pos.trBase, with endpoints at five times the
  origin2/angles/angles2 basis vectors added to the start.
- 106: twelve edges of a box transformed by that same basis and translated
  by pos.trBase. Dimensions are effect1Time/effect2Time/effect3Time, divided
  by two as integers before conversion. otherEntityNum selects color 0–31.

The existing original-protocol extended-event dispatcher now consumes these
events. No native ET event mapping or server command is modified. A shared
builder validates all geometry before allocating local entities. The active
renderer lazily registers railCore, creates LE_FADE_RGB/RT_RAIL_CORE entries,
uses cg_railTrailTime, and leaves fade/expiry/freeing to native local entities.

Differences: malformed/nonfinite/overflowing vectors, negative box dimensions,
and invalid or overflowing lifetimes are rejected; negative palette indices
clamp to zero (original only bounded above). RGB is clamped to 0–1 before byte
conversion. Box edge submission order differs, but the same twelve edges are
drawn. Keyed rail replacement used by other original rail paths is not part
of these events and remains separate work.

Tests cover 34 palette indices, axis endpoints/colors, line field mapping,
identity and rotated box bases with odd integer dimensions, actual extended
event dispatch, lazy shader registration, native half-life RGBA submission,
expiry/freeing, zero lifetime and invalid geometry. Original-gameplay and live
browser comparison remain unverified. No pak or original binary changes.
