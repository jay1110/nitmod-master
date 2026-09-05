# Debrief selection boundaries

Original CG_DebriefingPlayerList_KeyDown (sorted cgame_ui.c) uses 12-pixel
rows starting at y=60 and bounds the sorted list by server maxclients.
The original-protocol click path now applies that server limit before and
after looking up the sorted client id. Visible rows and scroll offset are
validated before addition. Native layout keeps its MAX_CLIENTS capacity.

GetSelectedClientInfo retains the original fallback to the local client,
but now returns NULL when neither selected nor local client is valid.
Previously a rejected fallback left an invalid selection used as an array
index. All consumers handle NULL, including the player name draw path.
Selecting a valid fallback still invalidates weapon-stat/hit-region caches.

Tests cover four server-sized rows, upper/lower row edges, malformed sorted
ids, extreme offsets, unavailable local client and cache invalidation on
fallback. This is selection compatibility and defensive handling, not a new
server statistics implementation. Browser join/map-transition replay remains
open; pak and original assets are unchanged.

Continuation: drawing, sorting, click selection and scrollbar counts now
share one protocol-aware client limit. Sorted IDs are checked before the
scrollbar or list dereferences clientinfo. The list searches only received
score entries and clears its per-row score pointer, so a missing score
cannot reuse a previous row's data. Tests cover server-sized counts,
malformed sorted IDs, absent scores, invalid offsets and null list panels.
