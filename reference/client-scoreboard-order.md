# Team scoreboard ordering and key lifecycle

Recovered from `cgame_client.c` CG_ScoresDown_f and CG_SortPlayersByKD,
and `cgame_ui.c` WM_TeamScoreboard. Original comparator reads score-row
offsets +32/+36 (kills/deaths populated by the kd command). The typed port
uses score_t kills/deaths populated atomically by kd0/kd1. The old
clientInfo_t mirrors are no longer authoritative for rendering or sorting:
userinfo replacement can clear them without losing scoreboard counters.
Changing a row's client resets its counters until a new kd update arrives;
unchanged rows retain them. Native score updates clear these extension fields.

A released second score-key press within 249 ms toggles sorting, provided
the last toggle is more than 500 ms old. Held-key repeats do not toggle.
The state resides in cg, so map initialization clears it. Native ET does not
use the extension. Defensive deviations: no fictitious double press on first
input, no negative-time/overflow toggle after clock rollback.

Both normal and compact team rows use a bounded index view: kills descending,
then deaths ascending, not a K/D ratio. Equal pairs preserve server ordering.
Score storage is never rearranged: sc0/sc1 and kd0/kd1 continue to target their
original row positions. The FFA renderer is unchanged, matching its separate
original unsorted traversal. Spectators retain original raw-row parity for
the two panels, use compact text when the team panel is compact, and reject
invalid client IDs. Repeated unguarded team-count traversal was removed.

The former native class-text column now displays kills/deaths for original
servers, in both row sizes, as original WM_DrawClientScore does at x+132.
This port retains the existing x+134 native column boundary and clips long
counter strings to that column; full original class-icon/name placement is
not claimed. Native servers retain the Class heading and class text.

Native fixture tests exercise ordering, ties, unchanged score storage,
protocol gating, invalid clients/counts/capacities, double-press boundaries,
cooldown, held keys and clock rollback. Browser visual and keyboard tests
remain required; no pixel parity claim. No pak or wire protocol modifications.
