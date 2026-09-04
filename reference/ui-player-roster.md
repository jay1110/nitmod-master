# UI player roster integration

Original UI_BuildPlayerList (sorted ui_ui_misc.c) reads CS_PLAYERS (689),
compacts populated server slots, carries name/mute/referee fields and builds
a same-team list with server client numbers. The native ET implementation
already supplies these fields to Nitmod vote/referee/ignore menu actions.

This integration bounds sv_maxclients to the local MAX_CLIENTS capacity,
does not read a player configstring for an invalid local client number,
clears stale roster rows and invalidates out-of-range menu selections.
Team membership is not inferred when the local client is invalid. Empty
team lists clear cg_selectedPlayerName; the native everyone sentinel uses
Everyone. Existing ET team-leader selection behavior is retained, not
claimed as original Nitmod parity.

UI_CheckExecKey additionally rejects negative and out-of-array key indices.
Source-contract assertions and native/WASM builds cover these changes;
interactive menu and reconnect replay tests remain pending. No pak assets
or original menu scripts are changed.

## Identity-preserving refresh

Player rows now carry internal server client numbers, like the existing
team rows. Refresh captures the selected slot and displayed name, rebuilds
both lists, then reselects only an exact slot/name match. A departed or
renamed selection becomes -1, rather than silently targeting the new row
occupant. Missing local player data no longer creates an inferred team list.
All loaded player/team listboxes receive the matching cursor position without
re-entering feeder callbacks; visual selection and menu-action selection
therefore stay aligned after compaction. Other feeders are untouched.

This is an integration correction, not a claim of newly recovered original
selection semantics. Existing name-based command formats are unchanged.
Duplicate displayed names remain ambiguous to an original server's name
resolver, and same-slot/same-name reconnects cannot be distinguished without
an additional server identity. The separate cg_selectedPlayer team-order
cvar retains its existing behavior; no authentication or protocol is added.

Linked UI tests exercise 384 selection/update combinations across all 64
slots, including departure, row compaction, replacement name, team switch,
duplicate displayed names and unchanged mute/referee state. Each checks both
listbox cursors and the generated voteKick command (or no command after
selection invalidation). Additional malformed count/local-client tests
verify bounded configstring reads and empty team lists. Live UI replay and
full original-server parity remain unverified.
