# Active map-config startup

qagame now registers original `g_mapConfigs` (empty default, flags 0) and
calls `G_NITMOD_LoadMapConfigs` during G_InitGame, after log initialization
and before G_InitWorldSession. If the directory is nonempty, it appends:

1. `exec <directory>/default.cfg`
2. `exec <directory>/<level.rawmapname>.cfg`

Original evidence: `nitmod_game.c` G_InitGame, lines 12534 onward,
uses trap_SendConsoleCommand mode 2 for these two commands in this order,
before G_InitWorldSession. Cvar-table record 0x2a90b8 refers to vmCvar
0x2e4a140. The raw map name is populated earlier from the server info string.
Deferred execution is preserved: this does not promise that queued settings
take effect synchronously within this initialization call.

The engine owns file lookup and missing-file diagnostics. The port does not
open, create or modify configs or pak assets, and does not add map_restart.
An empty setting is silent. Invalid/nonterminated input rejects the entire
pair, emits one warning, and queues no partial command.

Intentional hardening: relative directory components only; ASCII letters,
digits, underscore, hyphen and non-traversal dots; slash-separated directory
components are supported. Absolute paths, backslashes, whitespace, quotes,
command delimiters, empty components and dot/traversal components reject.
Trailing directory slashes reject rather than being silently normalized.
Map names cannot contain directory separators. Both command buffers can hold
the complete bounded cvar plus bounded map name without truncation.

Tests call the active adapter with real game syscall wrappers: 15 directories
x 9 map names, plus terminated/nonterminated buffer limits. They check exact
command text, EXEC_APPEND, default-before-map order, disabled behavior and
atomic rejection. Native/full-suite and WASM loading tests are separate from
engine/browser file-execution and map-transition end-to-end parity.

Remaining work: G_LoadConfig's structured `.config` parser, custom-config
selection, config metadata transmission, and vote-cycle-specific config
selection. These are not implemented by the plain `.cfg` startup path and
must not be advertised as complete. UI and cgame are unchanged in this step.
