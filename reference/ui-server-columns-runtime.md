# Server-browser column coherence

The typed UI server-list feeder now caches by engine server index, source and
render time, rather than column. Adjacent columns can reuse one engine lookup;
changing rows, sorting, source, or time invalidates it. The previous timeout
comparison was backwards and same-column calls could show another server's data.

Local network types exclude the terminating NULL entry and fall back to `???`.
Game-type labels are found by `gtEnum`, including sparse catalogs. Ping formatting
has space for a complete signed integer and color prefix. Display row and game
catalog loops are bounded by their actual storage.

`tests/check_ui_server_columns.h` exercises the production feeder through a LAN
syscall fixture: same-column row changes, adjacent-column reuse, reordered rows,
local source, invalid network types, sparse game type 8, maximum integer ping,
and clock rollback. This is a UI correctness fix, not a claim of original-binary
presentation parity. No cgame/qagame wire contract or asset is changed. NxAC icon
presentation remains separate work; no protection capability is fabricated.
