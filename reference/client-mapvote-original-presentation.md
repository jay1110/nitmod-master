# Original map-vote presentation and weighted controls

Recovered from immutable cgame ELF and sorted `cgame_client.c`:

- `CG_MapVoteList_Draw` ELF 0x35dd0: 19 rows, names x=15, scores x=225,
  250x12 selection highlight, last-played and accumulated-vote information.
  The prior invented percentage/checkbox columns are removed.
- `mapVoteNamesList` 0x131300: (15,56,250,240). Interactive rows are bounded
  to the 19 drawn rows; header labels at 0x132b80/0x132b20 are Name/Score.
- Selected levelshot at (524,50,96,72), command-map image at
  (428,154,192,192), with original `_cc.tga` naming. Selection registers
  these once rather than registering again every draw. A BSP is not required
  for preview availability. Missing levelshots keep the unknownmap fallback.
- Button records 0x131240/0x1311e0/0x131180/0x131120: x=15, width=64,
  height=16, y=296/316/336. Multi-vote rows send slots 3/2/1 while labels
  display ranks 1/2/3. These are weighted protocol slots, not list indices.
- `CG_MapVote_VoteButton_Draw` ELF 0x38d30 and MultiVote draw 0x3b850:
  VOTE/RE-VOTE labels, selected map beside the button, hover background,
  single-vote EF_VOTED handling versus per-slot multi-vote state.

Existing command encoding and duplicate rejection are retained. Enter is a
convenience shortcut for the first displayed button; arrow/wheel scrolling
also remains. Button-gap clicks and coordinates outside actual rows are
rejected. Input/draw counts are bounded to typed storage.

Full-cgame tests cover all valid/invalid button rows, both modes, voted and
unvoted states, actual click-to-command slot order, duplicate rejection,
button gaps, row selection, caching, scroll bounds, and real renderer
submission of both preview rectangles.

Not complete debriefing parity: map-cycle/XP-reset indicators, original
scrollbar drawing/dragging and final font/window styling remain open.
The legacy typed field named `nitmodMapVoteTimesPlayed` is displayed with
the original "Total Accumulated Votes" label; no wire-record changes were
made. No pak assets, menus, original binaries or qagame emissions changed.
