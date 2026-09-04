# Original client wire events, commands and loading presentation

## Evidence and changes (2026-09-03)

Reference: original `cgame.mp.i386.so`, SHA-256
`45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f`.
Original binaries and all `pak` content remain untouched.

### Events 1–64

`CG_EntityEvent` starts at ELF VA `0x61d60`. The original event-name table
is at `0x1346c0`; signed jump-table offsets at `0x105370` are relative to
`0x12dc44`. `cg_nitmod_eventmap.h` records every ID 1–64, not just the
reported crash ID. Original 63/64 select explode/rubble, not ET's events
with those numerical IDs. Original 11 uses `eventParm` as the step height.

Only original-protocol dispatch is translated. Native prediction, the
shared ET enum, snapshot event IDs and repetition bits are unchanged.
IDs 2–8 jump to the original error handler `0x644eb`; they remain explicit
unsupported/reserved events instead of being silently swallowed.
The remaining 57 entries have dispatch paths. This establishes dispatch
coverage, **not complete payload/gameplay parity for all 57 handlers**.
In particular weapon aliases, obituary presentation and some effect/sound
payload details still need further comparison. IDs above 64 are not covered
by this batch's new table (previous 93/96/98/99 handlers remain).

Original death events 52–55 (`0x622a8`, distant branch `0x65eee`) now use
typed weapon media arrays. `deathBySound` and `deathBySoundFar` accept up
to four entries each in the existing weapon-file client parser. Selection
is `(wireEvent - 52) % count`. The referenced entity's pain timestamp is
updated. A near sound is required before playing a far sound; far playback
requires distance strictly between 512 and 4096, at 64 units from the
current view origin, on CHAN_VOICE with SND_NOCUT. Invalid indices/counts
and nonpositive handles are rejected instead of indexing arbitrary memory.

### Commands

- `ob`: the original five-integer payload matches the existing typed
  objective snapshot parser. Original servers no longer need this port's
  capability negotiation to reach that parser. Existing popup presentation
  is reused; original centerprint details/icons are not fully reconstructed.
- `z5`: the original `CG_ParsePortalPos` is the eight-integer
  `portalcampos` contract. It now updates the existing `ccCurrentCamObjective`,
  `ccPortalPos`, `ccPortalAngles`, and `ccPortalEnt` fields, consumed by the
  real limbo/view camera code. Both spellings validate the entire tuple
  before changing state. Entity IDs permit -1 or 0..MAX_GENTITIES-1.
- `getnguid`: `nitrox_ReadNKey` at `0xf8e30` reads base64 from `nkey.dat`,
  checks decoded length 32 and character sum divisible by 100, then sets
  `n_guid`. The new reader accepts canonical 44-byte base64 and safe
  alphanumeric identities, with bounded reads and guaranteed file closure.
  `n_guid` is registered with original flags 1090 (USERINFO|ROM|NORESTART).
  Optional request arguments are ignored as in the original. A missing or
  malformed key clears the value and produces one diagnostic per module
  lifetime. **New-key generation and browser persistent-key provisioning
  are not ported here.** No replacement identity is invented; servers may
  still reject clients without a provisioned key. Read-only import never
  overwrites a key, writes PK3 content, or prints the identity to the log.

### Presentation

`CG_DrawConnectScreen` at `0x7bc00`, panel records `0x137820`, `0x137880`,
`0x1378e0`, and font records `0x137940`, `0x137980`, `0x137a00` provide
the loading layout: black background, left description/type, centered
levelshot (224,2,192,144), map/campaign name at (320,160), server at
(320,280), seven MOTD lines, filter icons and red loading meter
(260,458,120,10). Uses existing PK3 assets and the original
`ui/assets/filter_nxac_loading.tga`; the NxAC indicator reads `sv_NxAC`.
The stock parchment/map/pin rendering is no longer used. Nitmod branding
omits the original binary version to avoid misidentifying a reconstruction.
MOTD shading is painted before its text for readability, an intentional
render-order difference from the original decompile.

Scoreboard work in this batch is **partial**: red AXIS/blue ALLIES headers,
current-frame player totals and the original overflow policy of up to 33
compact rows. Full Nitmod row typography, columns, DM scoreboard, awards,
spectator/shoutcaster badges and intermission arrangement remain open.
This is not a claim of screenshot parity.

## Verification

- `test_original_event_map.py`: all 64 names checked directly against the
  immutable ELF plus original reserved-ID jump targets and dispatch table.
- Full-cgame fixture: actual step 11, explode 63, rubble 64, stop-loop 59
  dispatch with all repetition bits; existing landing and water regression
  cases continue to execute.
- 2,000 death-event profiles: four events, all near/far sound counts 0..4,
  five distance boundaries, four repetition-bit combinations; verifies
  handles, channel, far origin, cutoff flags and pain timestamp.
- Real weapon-file parsing with 1..4 near/far death sounds; actual `ob`,
  `z5` and `getnguid` server-command dispatch; malformed tuple, entity bound,
  base64 and missing-key checks.
- Native build and 89 CTests pass. Emscripten side-module build passes.
  Real browser/dedicated-server joining and visual comparison are still
  required; these builds and fixtures do not establish that end-to-end result.
