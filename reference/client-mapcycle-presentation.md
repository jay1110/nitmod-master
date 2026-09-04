# Original map-cycle and XP-reset presentation

The original `#` command stores arguments 19 and 20 as the zero-based map
index and XP-reset cycle length (`cgame_nitrox.c`, offsets 33787484 and
33787488). These are already decoded into `nitmodGameState_t`; no new
message or server capability is required.

`CG_MapVoteList_Draw` in original `cgame_client.c` displays `Map N of M`
at (290,66), and `^1XP Resetting!` at (290,81) when N >= M. The latter
moves Last Played and Total Accumulated Votes down by 15 pixels. The
typed map-vote renderer now implements these paths.

Original `WM_DrawObjectives` in `cgame_ui.c` displays the uppercase cycle
for map vote (6), TDM (7) with tdmOptions bit 8, or DM (8) with dmOptions
bit 0x4000. The scoreboard now uses these same gates; existing native
stopwatch and campaign branches remain intact.

Deliberate hardening: negative map indices and nonpositive cycle lengths
suppress the display. Unsigned addition avoids overflow for INT_MAX.
Tests cover 84 formatting combinations, 704 mode/option combinations,
reset boundaries, truncated buffers and null inputs. They validate typed
presentation decisions, not pixel-perfect browser parity.

No pak assets or original binaries are changed. Full debriefing font/layout
comparison and live dedicated-server visual validation remain open.
