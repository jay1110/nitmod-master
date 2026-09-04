# Keyed rail events

Original wire event 50 maps to EV_RAILTRAIL. Its angles carry RGB/255,
origin2 and pos.trBase are endpoints, dmgFlags selects a box, and effect1Time
is the persistent group ID. References: sorted cgame_client.c CG_RailTrail2
and CG_FindLocalEntity, cgame_ui.c CG_RailTrail, cgame_effects.c
CG_RailTrail_part_5. Box segments preserve original IDs 1..12; single lines
use -1. Zero group always allocates. Refresh restarts the fade lifetime.

The port deliberately searches only the active local-entity list instead
of the original array-prefix scan. Freed slots cannot match. Private key
fields are cleared by the existing allocator and do not change network or
engine structures. Invalid non-finite inputs/durations are rejected; colors
are clamped to the renderer range. Native ET rail behavior is unchanged.

tests/check_keyed_rails.h exercises 100 refreshes of all twelve keyed edges,
negative and zero groups, single-line endpoints, color, recycling and expiry.
Live dedicated-server visual comparison remains outstanding.
