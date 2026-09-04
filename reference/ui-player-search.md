# Player search request lifecycle

Original UI_BuildFindPlayerList: ui ELF 0x19d60 (Ghidra 0x29d60).
The typed request-slot pipeline is now in ui_nitmod_search.c, called by the
existing menu actions and refresh loop. ServerStatus parsing is reused via
UI_QueryServerStatus, without the status panel's URL side effects.

Retained behavior: clean color codes from query and player names, match a
case-insensitive substring, query displayed servers through engine LAN APIs,
reuse pending slots after responses/timeouts, set resend time to at least
50 ms, refresh at 25 ms intervals, and show a result summary. Completion
selects the current result through the existing feeder/status-panel path.

Intentional corrections rather than claims of byte-for-byte behavior:

- Only numbered player rows match; the name column header cannot be a hit.
- Each server address appears once, even with multiple matching players.
- Allow 15 unique servers plus one summary row (original left another slot
  unused); reaching capacity cancels pending requests.
- Starting an empty/color-only search cancels old engine requests too.
- Search responses do not change UI URL cvars/buttons. Result selection does.
- Clock rollback rebases active request times; widened timeout arithmetic
  avoids signed overflow. Deadline addition saturates at INT_MAX.
- Validate displayed-server counts and result selection. The status-panel
  currentServer boundary now rejects index == count before querying.

Tests drive real UI_BuildFindPlayerList with strict engine callbacks: 36
search timelines over 0..40 servers, matching names, timeouts, duplicate
addresses and header-only false matches. They verify scheduler gating,
result capacities, cancellation, summary rows, URL isolation and subsequent
selected-server status loading. Further cases cover backward clock and
empty-query cancellation. Existing status parser/menu tests remain active.

Native full CTest and WASM/Node entrypoint checks run. No external servers
are contacted by fixtures. Browser engine LAN transport and live server
search remain unverified; this does not complete the whole Nitmod UI port.
No pak assets, menus or original binaries changed.
