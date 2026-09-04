# Debriefing/map-vote scrollbar integration

Original `cgame_ui.c` contains four scrollbar data kinds: players (0),
weapon statistics (1), campaign maps (2), map voting (3). The native ET
helpers previously only knew 0–2; the reconstructed map vote bypassed them.

The typed kind-3 adapter now reads/writes the existing map-vote offset and
bounded count, with 19 visible rows. The original scrollbar rectangle
(265,56,16,240) uses the existing shared track/thumb rendering and ratio
calculation. Pressing its thumb captures the shared panel focus; debriefing
mouse movement handles map-vote mode as well as the native stats view.
Release, reset, and leaving map-vote mode clear its capture.

The original wheel up/down branches are restored to the shared scrollbar
handler for all four list types. Native arrow/list shortcuts are retained.
Track-click paging is not invented: the original only captures a thumb hit.

Original drag arithmetic is retained for ordinary inputs, including the
half-speed accumulated movement and cursor offset within the thumb. Explicit
hardening differences: zero-height/empty drags release capture; accumulation
and step conversion use bounded double arithmetic to avoid signed integer
overflow. Kind-3 counts remain capped at the existing 32-slot typed storage;
this is not an expansion of map-list protocol capacity.

Tests run every count 0–32 with offsets below/inside/above range, real capture
and mouse-drag events, extreme mouse deltas, release after tab changes, reset,
and 800 wheel events across all four list types. Existing button-to-wire,
duplicate-vote, preview rendering, and selection tests run in the same fixture.

Map-cycle/XP-reset presentation is covered in client-mapcycle-presentation.md.
Still open: full original debriefing layout/font comparison. No pak files, menu assets, server emissions or
original binary artifacts are changed. This does not establish browser
interaction parity without a live engine test.
