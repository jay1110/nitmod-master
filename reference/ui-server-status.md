# Server status decoding and UI links

Original UI_GetServerStatusInfo: ui ELF 0x151c0, Ghidra 0x251c0,
ui_ui_misc.c. Reconstructed in ui_nitmod_status.c and used by the existing
status panel, player search and status refresh paths in ui_main.c.

The engine adapter keeps the original request/poll/cancel contract. A pending
request clears the output and returns false; a null output cancels that
address. Completed responses own all mutable text and player-number storage
inside serverStatusInfo_t; row pointers remain valid until the next update.

The decoder retains Address, cvar pairs, a blank/header separator and
number/score/ping/name player rows, preserving colored names and score text.
The priority labels/order remain Name, Address, Game name, Game type, Map,
version, protocol, timelimit, fraglimit. Unknown keys remain available.

Deliberate safety corrections relative to the original/native parser:

- Terminate each player record before looking for spaces, preventing an
  incomplete record from absorbing fields from the next player.
- Stop incomplete rows and cap players at MAX_CLIENTS, with a separate check
  on number-string storage and the 128-row capacity.
- Force text-buffer termination even if the engine filled the whole buffer.
- Process a final URL cvar even without a trailing separator.
- Clear absent URL cvars and hide both matching menu buttons on both
  serverinfo_popmenu and popupError; do not retain a previous server's buttons.
- Priority sorting scans only the remaining suffix, avoiding reprocessing
  already placed records when duplicate keys exist.

Tests run the decoder over every prefix of a mixed response, 100 supplied
players, excess cvars, unterminated input and malformed player boundaries.
The real engine adapter is tested for polling/cancel behavior, labels, URL
replacement and clearing. Actual menu items in both menus are checked for
visibility changes. No URLs are opened and no network service is contacted.

This is a typed reconstruction and correction of the server-info subsystem,
not new asynchronous browser networking or a complete UI port. The existing
search/refresh scheduler remains unchanged. Native CTest and WASM/Node loader
checks are run; live browser/server transcript verification remains pending.
Pak/menu assets and original binary modules remain unchanged.
