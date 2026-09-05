# Active original team-roster cvars

Original qagame registers Players_Axis / Players_Allies at table addresses
0x2a85c8 / 0x2a85e4, empty default, flags 64 (ROM). CalculateRanks in
`nitmod_unknown.c` around lines 5900..5974 appends each non-spectator's
one-based connected-list position to its team string before SortRanks,
uses `(None)` for empty lists and writes both cvars.

The ET base already assembled matching teaminfo arrays but discarded them.
`game/g_main.c` now registers the original cvars and publishes those arrays
on every existing CalculateRanks invocation: connect, begin, disconnect,
death and team change. The native P cvar is retained unchanged. An invalid
team enum is excluded from the array write rather than indexing outside it.

These are NOT client-slot IDs or score-sorted positions. Connecting clients
contribute; spectators occupy connected-list positions but are not listed
on either team. No new protocol message or configstring range is introduced.
ROM registration is restored; this does not implement the original separate
special-mode re-registration with server-info flags.

`tests/check_team_rosters.h` calls the actual CalculateRanks routine with
all 12^3 combinations of connection state and team at sparse slots 0, 7, 63,
plus all 64 connected Axis clients. It checks both strings, empty resets,
connected counts and the two roster writes plus native P write. Tests use
intermission to retain the real scoreboard-request path without evaluating
map-exit conditions. Other existing rank side effects remain intact.

This change adds active qagame behaviour only. It does not add a UI roster
widget or claim browser/server-list display parity. Pak and original binaries
remain unchanged.
