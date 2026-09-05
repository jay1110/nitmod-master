# UI join address pipeline

JoinServer, JoinDirectServer and FoundPlayerJoinServer now use the same
address validation and quoted connect argument as server redirects.
Original menu action names and destination sources are unchanged.
Validation occurs before closing menus or changing connection cvars.
Both list-based actions bound count and selection against their actual
arrays; the server-browser action rejects a negative engine server index.

Tests call UI_RunMenuScript with malformed direct addresses and valid,
malformed, negative-selection and excessive-count player-search results.
The engine mock verifies the exact connect command and cvar side effects.
Address syntax tests also remain in the redirect fixture. Browser-list
engine integration and live connections are not verified by these tests.
This is safety integration, not new Nitmod gameplay. No pak files change.
