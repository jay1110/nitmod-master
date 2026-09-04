# Complete debrief page routing and request lifecycle

Original cgame ELF: CG_Debriefing_NextButton_KeyDown 0x36670,
CG_Debriefing_InfoRequests 0x39290, CG_Debriefing_Draw 0x39410.
Sorted cgame_ui.c provides the corresponding branches.

Original order is Map Vote -> Scoreboard -> Team -> Player -> Map Vote.
Voting is available for game type 6, TDM (7) with tdmOptions bit 8, and
DM (8) with dmOptions bit 0x4000. Without voting the cycle skips that page.
The port previously replaced the scoreboard with voting in type 6 and
cycled only three views, leaving no separate scoreboard for that mode.

The implementation retains native internal IDs (0 primary, 1 team, 2 player)
and adds local ID 3 for the separate scoreboard. Thus the voting sequence is
0 -> 3 -> 1 -> 2 -> 0. These IDs never cross the wire. One capability predicate
now drives request priority, drawing, keyboard and scrollbar mouse routing.
Tab changes clear captured panel focus to avoid interacting with hidden lists.

After the map list is received, the original request chain now continues:
impkd -> imwa -> imws plus optional imhr -> score. Previously the type-6
early return polled only the map list/tally, permanently starving statistics.
Tally polling is separate and runs on the visible voting page, after the UI
key-catcher check. Stats keep the one-second request throttle; optional missing
hit regions do not block scores. Known difference: tally starts only after
the list is available, whereas original draw can request it earlier.

Timer differences: backward engine time resumes requests instead of blocking
them; subtraction uses double to avoid signed overflow. Invalid selected-client
IDs never emit imws/imhr. Existing zero-time sentinel behavior is retained.

Tests: 48 protocol/game/options profiles, 576 real next-button transitions,
1536 received-flag request combinations, throttle suppression, focus release,
backward time for all three timers and invalid-client rejection. Native ET
retains its three pages and does not send original map-vote requests.

No new server command is introduced. These are existing original-server
requests and already implemented cgame reply handlers. This does not port the
still-missing reconstructed-qagame map-vote backend, nor claim full original
debrief font/layout or live browser parity. pak and original binaries unchanged.
