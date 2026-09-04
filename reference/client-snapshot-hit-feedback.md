# Snapshot hit feedback and pain-source separation

Original CG_CheckLocalSounds reads playerState+0x118, then +0x114 and
plays cgs+132004, then +131996 on channel 3. Media registration in
sorted/cgame_client.c:13407–13409 identifies these as
sound/hitsounds/body.wav and sound/hitsounds/head.wav, respectively.
These are original persistant slots 2 and 1, distinct from the live HUD
body/head totals in slots 6 and 5. The previous description of slot 2 as
team hits was incorrect and has been corrected in code and documentation.
Reference CG_CheckLocalSounds ELF 0x989f0, size 1191, cgame SHA-256
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.

NITMOD_SnapshotHitSounds consumes the two original per-snapshot copies,
before the current snapshot pointer changes. It plays body first, then
head, on CHAN_VOICE (3), once per positive counter change, not once per
delta unit. Equal/decreasing counters, disabled cg_hitSounds, native
protocol, invalid clients, spectator state and changing followed client
do not produce sound. Existing explicit nhs and hit-event routes retain
their own sample selection. Media is cached and reset with config state;
failed/nonpositive registrations are not submitted to the sound engine.

Original CG_CheckLocalSounds contains no ET-2.60 health-delta pain branch.
That branch is now native-only: original pain events remain active, without
an extra sound/pain timer update from the same health loss. Native behavior
is preserved. Snapshot-based feedback avoids using copied normalized
prediction arrays for private counters and avoids replay on rendered frames.

Verification: 600 protocol/cvar/client/team/body-delta/head-delta cases,
with submitted samples, order, channel, entity and volume checked through
engine doubles. Tests also verify only two media registrations and that
an original health decrease does not invoke native pain. Existing tests
for explicit hit events remain active. Native suite and WASM load checks
do not replace a live dedicated-server/audio comparison, still outstanding.

No new server commands, qagame wire changes, pak/PK3 or asset modifications.
