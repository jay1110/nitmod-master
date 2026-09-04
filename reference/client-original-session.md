# Original Nitmod session synchronization

The original startup/map-restart path invokes `nitmod_ClientCheck`, which
loads the player key and sends `imhere`. Original qagame's ClientCommand
responds with `handshake`. Original cgame answers in order:

1. `rhs`: clear qagame's per-client handshake latch.
2. `handshake`: set the latch and call nitrox_SendNewGameState.
3. `getdata`: request SimpleCS, NCS, skill levels, charge times, and team scores.

Evidence: sorted `cgame_nitrox.c` nitmod_ClientCheck; `cgame_client.c`
startup call; `cgame_servercmds.c` handshake and restart branches; and
`qagame/sorted/nitmod_client.c` ClientCommand around lines 5263–5305.
The opaque first response literal was read as `rhs` from original cgame
ELF VA 0x10dad8 (Ghidra address 0x11dad8), using its ELF section mapping.

Implementation hooks cgame initialization and map_restart, and routes exact
`handshake` server commands through the original-protocol handler. Restart
also resets the two original spawn-timer cvars. The native/reconstructed
capability negotiation remains separate and unchanged; this legacy exchange
does not grant NITMOD_FEATURE_* capabilities. Repeated requests retain the
reset/ack/data order rather than suppressing a needed server resync.

Boundaries / deviations:

- No traffic or key IO from these new hooks during demo playback.
- Extra handshake arguments are rejected. Case-sensitive matching follows
  the original string comparison.
- Original sessions require fs_game nitmod; a mismatch warns and skips the
  initiation, rather than forcibly disconnecting as the original does.
- Existing key generation/import runs before imhere. No hardware MAC
  collection and no fabricated version, NxAC, or integrity attestation.
- getdata can cause the original server to schedule its cvar scan. The
  existing `cvs` handler replies with actual cvar values; see
  client-cvar-scan.md for its independently tested boundaries. This is not
  a promise of admission to servers requiring unported anti-cheat features.

Tests cover 24 startup combinations (protocol/demo/folder), 72 challenge
combinations including malformed arity, exact reply ordering through the
actual server-command dispatcher, repeated requests, and invalid commands.
The reconstructed qagame intentionally does not gain legacy commands: it
continues to advertise and use its own capability contract. No pak, menu,
PK3 or original binary changes. Dedicated/browser session parity is untested.
